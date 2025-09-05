del *.wecode-db /s/q
del *.wecode-lock /s/q
del tags-24.wecode-db /s/q
del tags-24.wecode-lock /s/q

del temp.txt /s/q
del VC.DB /s/q
del compile_commands.json /s/q
del missingHeaderFiles.txt /s/q
del pbi.json /s/q

del a.out /s/q
del *.exe /s/q
del test /s/q

del *.o /s/q
del *.ncb /s/q
del *.opt /s/q
del *.plg /s/q

del *.obj /s/q
del *.ib_pdb_index /s/q
del *.idb /s/q
del *.pdb /s/q
del *.lib /s/q

rem del *.exe /s/q
del *.exp /s/q

attrib *.suo -S -H -R /S
del *.suo /s/q
del *.ilk /s/q

del *.tag /s/q
del BuildLog.htm /s/q

del *.ib_tag /s/q
del *.pch /s/q
del *.manifest.res /s/q

del *.manifest /s/q
del *.map /s/q
del *.dep /s/q

del *.user /s/q
del *.sdf /s/q
del *.aps /s/q

set parent_path=%cd%
for /r %parent_path% %%i in (Debug) do rmdir /q /s %%i

set parent_path=%cd%
for /r %parent_path% %%i in (ipch) do rmdir /q /s %%i

rem set parent_path=%cd%
rem for /r %parent_path% %%i in (.vscode) do rmdir /q /s %%i

set parent_path=%cd%
for /r %parent_path% %%i in (build) do rmdir /q /s %%i

set parent_path=%cd%
for /r %parent_path% %%i in (.vs) do rmdir /q /s %%i

set parent_path=%cd%
for /r %parent_path% %%i in (x64) do rmdir /q /s %%i

set parent_path=%cd%
for /r %parent_path% %%i in (.cache) do rmdir /q /s %%i

set parent_path=%cd%
for /r %parent_path% %%i in (.subRepoRulesets) do rmdir /q /s %%i

pause
