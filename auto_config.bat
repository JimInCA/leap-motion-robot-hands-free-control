@ECHO OFF

REM Verify that the Leap Motion Samples directory exists
IF NOT EXIST "..\LeapC-samples" (
	echo Leap Motion source directory ..\LeapC-samples does not exist
	GOTO END
)

REM Make sure that the redbot application directory exists
IF NOT EXIST ".\redbot-application" (
	echo Redbot Application directory .\redbot-application does not exist
	GOTO END
)

REM Verify that the application include directory exists and copy *.h files from samples
IF NOT EXIST ".\redbot-application\include" (
	mkdir .\redbot-application\include
)
copy ..\LeapC-samples\include\* .\redbot-application\include\.

REM Verify that the library directory exists and copy all library files from samples
IF NOT EXIST .\redbot-application\lib (
	mkdir .\redbot-application\lib
)
xcopy /E /Y /Q ..\LeapC-samples\lib\* .\redbot-application\lib\.

REM Copy specific header and source files from samples and update where required
copy ..\LeapC-samples\samples\C\ExampleConnection.h .\redbot-application\include\connection.h
copy ..\LeapC-samples\samples\C\ExampleConnection.c .\redbot-application\src\connection.c

REM sed 's\ExampleConnection.h\connection.h\' ..\LeapC-samples\samples\C\ExampleConnection.c > .\redbot-application\src\connection.c
@ECHO Please Note:
@ECHO You will need to edit .\redbot-application\src\connection.c
@ECHO replace -
@ECHO   #include "ExampleConnection.h"
@ECHO with -
@ECHO   #include "connection.h"

:END
