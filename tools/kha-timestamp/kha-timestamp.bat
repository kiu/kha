echo WScript.Echo(Math.floor(new Date().getTime() / 1000)); > %temp%\time.js
echo | set /p dummyName="#define KHA_VERSION " > kha-version.h
cscript //nologo %temp%\time.js >> kha-version.h
del %temp%\time.js

