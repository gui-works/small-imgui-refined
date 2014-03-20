del b2cpp.exe
del b2hpp.exe
cl b2cpp.cpp /Ox /Oy /MT /DNDEBUG %* /link setargv.obj
cl b2hpp.cpp /Ox /Oy /MT /DNDEBUG %* /link setargv.obj
b2cpp *.ttf ..\fontbase\entypo\wq\*.ttf ..\fontbase\extra\wq\*.ttf
b2hpp *.ttf ..\fontbase\entypo\wq\*.ttf ..\fontbase\extra\wq\*.ttf

