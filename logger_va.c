bool_t gStoreToFlash = false;
bool_t gPrintOverSerial = true;
bool_t gLoggerInitialize = true;

#include <string.h>
#include <stdbool.h>

/*
 * List of severities the logger can choose from. If the global severity is set to
 * a higher value than a log with a particular severity, that specific log will be
 * skipped.
 */
typedef enum SeverityLevel {
	SEVERITY_DEBUG = 0,
	SEVERITY_INFO,
	SEVERITY_WARN,
	SEVERITY_ERROR,
	SEVERITY_FATAL,
	SEVERITY_OFF,
	// If adding a module, please add it before the LAST_SEVERITY Severity.
	SEVERITY_LAST_SEVERITY
} SeverityLevel;

// severity level name strings
const char* severityLevels[SEVERITY_LAST_SEVERITY] =
	{	"DEBUG",
		"INFO",
		"WARN",
		"ERROR",
		"FATAL",
		"OFF"
};

status_code_t Logger_Log(const char* module_tag, SeverityLevel level, const char* format, ...){
	if(!gLoggerInitialized){
		return STATUS_FAIL;
	}
	
	status_code_t status = STATUS_OK;
	
	// skips everything if severity level is lower than global severity level or logging is disabled
	if ((level >= gSeverity) && (gStoreToFlash || gPrintOverSerial)){
		uint32_t len;
		uint32_t tickCount;
		char logBuffer[SERIAL_FLASH_PAGE_SIZE];
		
		
		tickCount = (PowerManager_IsPowerManagerRunning() ? 
			AsynchronousTimer_GetTickCount() :
			Scheduler_GetTickCount());
		// Scheduler has higher resolution.
		
		char * module_tag_ = (module_tag == 0x0) ? "" : module_tag;
=		len = snprintf(logBuffer, NUM_INFO_BYTES, "[%010u][%s][%s] ", tickCount, severityLevels[level], module_tag);
		len = (len > NUM_INFO_BYTES) ? NUM_INFO_BYTES : len;

		{
			// format variable arguments into the log buffer.
			va_list arglist;
			va_start(arglist, format);
			vsnprintf(logBuffer + len, SERIAL_FLASH_PAGE_SIZE - len, format, arglist);
			va_end(arglist);
		}

		logBuffer[SERIAL_FLASH_PAGE_SIZE-1] = 0;
		
		
		// Remove any unwanted newlines
		// Do twice to catch \r\n, \r or \n
		len = strlen(logBuffer);
			
		if((len) && ((logBuffer[len-1] == '\r') || (logBuffer[len-1] == '\n'))) {
			logBuffer[len-1] = 0;
			len--;
		}
			
		if((len) && ((logBuffer[len-1] == '\r') || (logBuffer[len-1] == '\n'))) {
			logBuffer[len-1] = 0;
			len--;
		}
		
#ifndef STRIP_LOGGER
		if (gStoreToFlash){
			// updates gCurrentLoggingAddress variable if necessary
			status |= checkWriteLocation(&gCurrentTempSessionIdx, gCurrentLoggingAddress);
			status |= SerialFlash_Program(gCurrentLoggingAddress, len+1, (uint8_t*)logBuffer);
			gCurrentLoggingAddress = gCurrentLoggingAddress + len + 1;
			if (level == SEVERITY_FATAL || level == SEVERITY_ERROR){
				markAsFatal(gCurrentTempSessionIdx);
			}
		}
#endif
		// only print over serial in the Debug build configuration
		if (gPrintOverSerial){
			printf("%s\r\n", logBuffer);
		}
	}
	return (status == STATUS_OK) ? STATUS_OK : STATUS_FAIL;
}

int main() {
	Logger_Log("MAIN", SEVERITY_DEBUG)
}
