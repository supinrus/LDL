call "c:\Program Files (x86)\DevStudio\VC\bin\VCVARS32.BAT"

cl /O2 -Fevc5_test.exe -GX ..\test.cpp /I..\include /link gdi32.lib winmm.lib user32.lib opengl32.lib

del *.obj

pause