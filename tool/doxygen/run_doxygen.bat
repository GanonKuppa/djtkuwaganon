echo ===== run doxygen =====
rmdir /s /q html > NUL 2>&1 & if ERRORLEVEL 1 cmd /c exit 0
doxygen DoxyFile
start html/index.html
