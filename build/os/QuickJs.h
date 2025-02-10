typedef union JSValueUnion
{
    int int32;
    double float64;
    void *ptr;
} JSValueUnion;

typedef struct JSValue
{
    JSValueUnion u;
    long long tag;
} JSValue;

typedef enum JSErrorEnum
{
    JS_EVAL_ERROR,
    JS_RANGE_ERROR,
    JS_REFERENCE_ERROR,
    JS_SYNTAX_ERROR,
    JS_TYPE_ERROR,
    JS_URI_ERROR,
    JS_INTERNAL_ERROR,
    JS_AGGREGATE_ERROR,

    JS_NATIVE_ERROR_COUNT, /* number of different NativeError objects */
} JSErrorEnum;

typedef void *QuickJS_t;
// 创建
QuickJS_t quickjs_create();
// 释放
void quickjs_free(QuickJS_t quickjs);
// 执行js代码
JSValue quickjs_eval(QuickJS_t quickjs, const char *js_code);
// 判断是否是异常
bool quickjs_is_exception(QuickJS_t quickjs, JSValue val);
// 获取异常信息
const char *quickjs_get_exception(QuickJS_t quickjs);
// 转字符串
const char *quickjs_js_ToCString(QuickJS_t quickjs, JSValue val);
// 转bool
bool quickjs_js_ToBool(QuickJS_t quickjs, JSValue val);
// 转int
int quickjs_js_ToInt(QuickJS_t quickjs, JSValue val);
// 创建一个JS的undefined值
JSValue quickjs_new_undefined(QuickJS_t quickjs);
// 创建一个JS的null值
JSValue quickjs_new_null(QuickJS_t quickjs);
// 创建一个JS的true值
JSValue quickjs_new_true(QuickJS_t quickjs);
// 创建一个JS的false值
JSValue quickjs_new_false(QuickJS_t quickjs);
// 创建一个JS的字符串
JSValue quickjs_new_string(QuickJS_t quickjs, const char *str);
// 创建一个JS的int
JSValue quickjs_new_int(QuickJS_t quickjs, int val);
// 创建一个JS的json对象
JSValue quickjs_new_json(QuickJS_t quickjs, const char *str);
// 创建一个JS的double
JSValue quickjs_new_double(QuickJS_t quickjs, double val);
// 创建一个JS的函数
JSValue quickjs_new_function(QuickJS_t quickjs,
                             const char *name,
                             int length,
                             JSValue (*func)(JSValue this_val, int argc, JSValue *argv));
// 设置全局变量
int quickjs_set_property_str(QuickJS_t quickjs, const char *property_name, JSValue value);