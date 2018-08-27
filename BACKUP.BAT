@echo off
rem echo Press any key to continue or Ctrl-Break to cancel
rem pause
rem rar a D -agY_MMDD_HHMM -r -m5 -xCore.lib -x*.obj -x*.exp -x*.rar -x*.mk -x*.res -x*.dep -x*.pdb -x*.tds -x*.exe -x*.dll -x*.bak -xafterdoc\html\*.*
rar a TEST -agY_MMDD_HHMM -r -m5 -x@xbackup.opt
