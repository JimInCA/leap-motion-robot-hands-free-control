#!/bin/sh

# Verify that the Leap Motion Samples directory exists
if [ ! -d ../LeapC-samples ]; then
	echo Leap Motion source directory ../LeapC-samples does not exist
	exit -1
fi

# Make sure that the redbot application directory exists
if [ ! -d ./redbot-application ]; then
	echo Redbot Application directory ./redbot-application does not exist
	exit -2
fi

# Verify that the application include directory exists and copy *.h files from samples
if [ ! -d ./redbot-application/include ]; then
	mkdir ./redbot-application/include
fi
cp -rf ../LeapC-samples/include/* ./redbot-application/include/.

# Verify that the library directory exists and copy all library files from samples
if [ ! -d ./redbot-application/lib ]; then
	mkdir ./redbot-application/lib
fi
cp -rf ../LeapC-samples/lib/* ./redbot-application/lib/.

# Copy specific header and source files from samples and update where required
cp ../LeapC-samples/samples/C/ExampleConnection.h ./redbot-application/include/connection.h
sed 's/ExampleConnection.h/connection.h/' ../LeapC-samples/samples/C/ExampleConnection.c > ./redbot-application/src/connection.c

