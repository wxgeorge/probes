# I'm writing a deploy script to deploy proof's app in a docker environment.
#
# I want to parameterize this script, and trying to figure out how to pass in those parameters.
# I know I can use environment variables, but that means my parameterized script runs in a
# separate process. Which is fine, but seems to be using bash poorly.
#
# This probe was to test visibility of bash variables.
# I suspect that variable set in this script would be visible to a sub-script that is _sourced_
# as source is a very simple include (as if the contents of the file were pasted in).
#

echo "Hello from main.sh!"
echo "Let's start by calling sourced.sh"
. sourced.sh
echo ""

echo "Hello again from main.sh! Let's set MAH_VARIABLE=bananas"
MAH_VARIABLE=bananas
echo "now we'll call sourced.sh again"
. sourced.sh
echo ""

echo "Now let's try an alternative invocation of sourced.sh, when it's in it's a subshell"
echo "I'm expecting that in the subshell, the variable MAH_VARIABLE will not have been set"
echo $(/bin/bash sourced.sh)
