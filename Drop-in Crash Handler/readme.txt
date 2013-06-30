Author: Branden Turner
Integrating Crash Logger with an existing visual studio project ( supported on windows for ides with symbols ):

To integrate the crash logger into an existing VS project, drag the source files ( handler.cpp and handler.h ) into the project's source, the include "handler.h" and declare a CrashHandler before the startup of your program.  It will wait patiently in its own thread unti your program blows up, then create a nice mini dump for you to examine after the fact.  If you want this to work WITH a live debugger attached ( as in you have it open in a debugger AND want the crash dump for later ), you'll need to wrap whatever code you're testing in __try, __except blocks as this method uses SetUHEF ( google it for more info ).


To use the exampleDump file, you'll need to browse to CrashHandler.exe to see the integer divison by zero with call-stack.  The solution is a simple example of how to get started with the handler.

brandencturner@gmail.com