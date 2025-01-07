# 编译
g++ -fPIC QuickJs.cc \
-shared -o ./os/QuickJs.so \
-I./quickjs -L./quickjs -l:libquickjs.so \
-rdynamic -lm -ldl -lpthread
# 导出so库
# gcc-ar rcs ./quickjs/libquickjs.so \
# ./quickjs/.obj_linux/quickjs.nolto.o \
# ./quickjs/.obj_linux/libregexp.nolto.o \
# ./quickjs/.obj_linux/libunicode.nolto.o \
# ./quickjs/.obj_linux/cutils.nolto.o \
# ./quickjs/.obj_linux/quickjs-libc.nolto.o \
# ./quickjs/.obj_linux/libbf.nolto.o
# 导出so库 end