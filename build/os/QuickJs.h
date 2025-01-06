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

typedef void *QuickJS_t;
// 创建
QuickJS_t quickjs_create();      
// 释放                               
void quickjs_free(QuickJS_t quickjs);          
// 执行js代码                 
JSValue quickjs_eval(QuickJS_t quickjs, const char *js_code);   
// 判断是否是异常
bool quickjs_is_exception(QuickJS_t quickjs, JSValue val);      
// 返回字符串
const char *quick_js_ToCString(QuickJS_t quickjs, JSValue val); 