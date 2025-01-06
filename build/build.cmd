@REM 导出lib库
@REM gcc-ar rcs libquickjs.lib ^
@REM ./quickjs/.obj_win/quickjs.nolto.o ^
@REM ./quickjs/.obj_win/libregexp.nolto.o ^
@REM ./quickjs/.obj_win/libunicode.nolto.o ^
@REM ./quickjs/.obj_win/cutils.nolto.o ^
@REM ./quickjs/.obj_win/quickjs-libc.nolto.o ^
@REM ./quickjs/.obj_win/libbf.nolto.o
@REM 导出lib库  end

@REM 编译
c++ QuickJs.cc ^
-shared -o ./os/QuickJs.dll ^
-I./quickjs -L./quickjs -l:libquickjs.lib ^
-static