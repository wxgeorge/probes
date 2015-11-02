#!/usr/bin/env python

# this sketch is intended to illustrate what might be called
# "the javascript model of computation".
#
# Javascript grew up in the browser.
# Something you have to do all the time is operate on the results
# of a url, but fetching server resources takes a lot of time,
# so we need a model of computation of defering execution.
#
# How do we specify what to do once a function returns?
# For javascript, the answer is often with a function.
#
# This file is a transcription of an imaginary javascript interpreter
# and program into python.

import time, threading, datetime
def execute_in_background(task, callback):
	def background_activity():
		o = task()
		callback(o)

	my_thread = threading.Thread(target=background_activity)
	my_thread.start()

def some_long_running_task(sleep_time, rvalue):
	time.sleep(sleep_time)
	return rvalue


def print_something(something):
	print something
	print datetime.datetime.now()


if __name__ == "__main__":
	print "Hello world! @ %s" % datetime.datetime.now()

	def task_one():
		return some_long_running_task(0.1, "something")

	def task_two():
		return some_long_running_task(0.01, "something quicker")

	execute_in_background(task_one, print_something)
	execute_in_background(task_two, print_something)
