#include "quickjs-libc.h"
#include <string>
#include <cstring>

//---------------- 设置导出名 `EXPORT` (全大写可加下划线、可自定义,例如 ASD_API)
#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

class QuickJS
{
public:
    QuickJS() : rt(JS_NewRuntime()), ctx(JS_NewContext(rt)) {}
    ~QuickJS()
    {
        // 不需要再调用 quickjs_free()
        JS_FreeContext(ctx);
        JS_FreeRuntime(rt);
    }

    // 禁用拷贝构造函数和赋值操作符以防止资源双重释放等问题
    QuickJS(const QuickJS &) = delete;
    QuickJS &operator=(const QuickJS &) = delete;

    /**
     * @brief 执行js代码
     *
     * @param js_code
     * @return JSValue
     */
    JSValue quickjs_eval(const char *js_code)
    {
        JSValue val = JS_Eval(ctx, js_code, strlen(js_code), "quick.js", JS_EVAL_TYPE_GLOBAL);
        JS_FreeValue(ctx, val);
        return val;
    }

    /**
     * @brief 判断是否是异常
     *
     * @param val
     * @return true
     * @return false
     */
    bool quickjs_is_exception(JSValue val)
    {
        return JS_IsException(val);
    }

    /**
     * @brief 获取异常信息
     *
     * @return const char *
     */
    const char *quickjs_get_exception()
    {
        JSValue val = JS_GetException(ctx);
        const char *error = JS_ToCString(ctx, val);
        JS_FreeCString(ctx, error);
        JS_FreeValue(ctx, val);
        return error;
    }

    /**
     * @brief 转字符串
     *
     * @param val
     * @return const char*
     */
    inline const char *quickjs_js_ToCString(JSValue val)
    {
        const char *str = JS_ToCString(ctx, val);
        JS_FreeValue(ctx, val);
        JS_FreeCString(ctx, str);
        return str;
    }

    /**
     * @brief 转bool
     *
     * @param val
     * @return int
     */
    int quickjs_js_ToBool(JSValue val)
    {
        int b = JS_ToBool(ctx, val);
        JS_FreeValue(ctx, val);
        return b;
    }

    /**
     * @brief 转int
     *
     * @param val
     * @param pres
     * @return int
     */
    int quickjs_js_ToInt(JSValue val)
    {
        int32_t pres;
        if (JS_ToInt32(ctx, &pres, val))
        {
            fprintf(stderr, "Error: failed to convert JS value to int.\n");
        }
        JS_FreeValue(ctx, val);
        return pres;
    }

    /**
     * @brief 创建一个JS函数
     *
     * @param func 函数指针
     * @param name 函数名
     * @param length 参数个数
     * @return JSValue
     */
    JSValue quickjs_new_function(JSCFunction *func, const char *name,
                                 int length)
    {
        JSValue func_val = JS_NewCFunction(ctx, func, name, length);
        JS_FreeValue(ctx, func_val);
        return func_val;
    }

    /**
     * @brief 创建一个JS的undefined值
     *
     * @return JSValue
     */
    JSValue quickjs_new_undefined()
    {
        JSValue val = JS_UNDEFINED;
        JS_FreeValue(ctx, val);
        return val;
    }

    /**
     * @brief 创建一个JS的null值
     *
     * @return JSValue
     */
    JSValue quickjs_new_null()
    {
        JSValue val = JS_NULL;
        JS_FreeValue(ctx, val);
        return val;
    }

    /**
     * @brief 创建一个JS的true值
     *
     * @return JSValue
     */
    JSValue quickjs_new_true()
    {
        JSValue val = JS_TRUE;
        JS_FreeValue(ctx, val);
        return val;
    }

    /**
     * @brief 创建一个JS的false值
     *
     * @return JSValue
     */
    JSValue quickjs_new_false()
    {
        JSValue val = JS_FALSE;
        JS_FreeValue(ctx, val);
        return val;
    }

    /**
     * @brief 创建一个JS的字符串
     *
     * @param str
     * @return JSValue
     */
    JSValue quickjs_new_string(const char *str)
    {
        JSValue val = JS_NewString(ctx, str);
        JS_FreeValue(ctx, val);
        return val;
    }

    /**
     * @brief 创建一个JS的int
     *
     * @param val
     * @return JSValue
     */
    JSValue quickjs_new_int(int val)
    {
        JSValue js_val = JS_NewInt32(ctx, val);
        JS_FreeValue(ctx, js_val);
        return js_val;
    }

    /**
     * @brief 字符串转json对象
     *
     * @param str
     * @return JSValue
     */
    JSValue quickjs_str_to_json(const char *str)
    {
        JSValue js_val = JS_ParseJSON(ctx, str, strlen(str), NULL);
        JS_FreeValue(ctx, js_val);
        return js_val;
    }

    /**
     * @brief 创建一个JS的double
     *
     * @param val
     * @return JSValue
     */
    JSValue quickjs_new_double(double val)
    {
        JSValue js_val = JS_NewFloat64(ctx, val);
        JS_FreeValue(ctx, js_val);
        return js_val;
    }

    /**
     * @brief 设置全局变量
     *
     * @param property_name 变量名
     * @param value         值
     * @return int
     */
    int quickjs_set_property_str(const char *property_name, JSValue value)
    {
        JSValue global_obj = JS_GetGlobalObject(ctx);
        int sps = JS_SetPropertyStr(ctx, global_obj, property_name, value);
        JS_FreeValue(ctx, global_obj);
        return sps;
    }

private:
    JSRuntime *rt;
    JSContext *ctx;
};

typedef void *QuickJS_t;

// ---------------- 导出函数
extern "C"
{
    QuickJS_t quickjs_create();                                                                                                                // 创建
    void quickjs_free(QuickJS_t quickjs);                                                                                                      // 释放
    JSValue quickjs_eval(QuickJS_t quickjs, const char *js_code);                                                                              // 执行js代码
    bool quickjs_is_exception(QuickJS_t quickjs, JSValue val);                                                                                 // 判断是否是异常
    const char *quickjs_js_ToCString(QuickJS_t quickjs, JSValue val);                                                                          // 转字符串
    int quickjs_js_ToBool(QuickJS_t quickjs, JSValue val);                                                                                     // 转bool
    int quickjs_js_ToInt(QuickJS_t quickjs, JSValue val);                                                                                      // 转int
    const char *quickjs_get_exception(QuickJS_t quickjs);                                                                                      // 获取异常信息
    JSValue quickjs_new_undefined(QuickJS_t quickjs);                                                                                          // 创建一个JS的undefined值
    JSValue quickjs_new_null(QuickJS_t quickjs);                                                                                               // 创建一个JS的null值
    JSValue quickjs_new_true(QuickJS_t quickjs);                                                                                               // 创建一个JS的true值
    JSValue quickjs_new_false(QuickJS_t quickjs);                                                                                              // 创建一个JS的false值
    JSValue quickjs_new_string(QuickJS_t quickjs, const char *str);                                                                            // 创建一个JS的字符串
    JSValue quickjs_new_int(QuickJS_t quickjs, int val);                                                                                       // 创建一个JS的int
    JSValue quickjs_new_json(QuickJS_t quickjs, const char *str);                                                                              // 字符串转json对象
    JSValue quickjs_new_double(QuickJS_t quickjs, double val);                                                                                 // 创建一个JS的double
    int quickjs_set_property_str(QuickJS_t quickjs, const char *property_name, JSValue value);                                                 // 设置全局变量

    /**
     * @brief 创建
     *
     * @return QuickJS_t
     */
    EXPORT QuickJS_t quickjs_create()
    {
        return new QuickJS();
    }

    /**
     * @brief 执行js代码
     *
     * @param quickjs
     * @param js_code
     * @return JSValue
     */
    EXPORT JSValue quickjs_eval(QuickJS_t quickjs, const char *js_code)
    {
        return ((QuickJS *)quickjs)->quickjs_eval(js_code);
    }

    /**
     * @brief 转字符串
     *
     * @param quickjs
     * @param val
     * @return EXPORT const*
     */
    EXPORT const char *quickjs_js_ToCString(QuickJS_t quickjs, JSValue val)
    {
        return ((QuickJS *)quickjs)->quickjs_js_ToCString(val);
    }

    /**
     * @brief 转bool
     *
     * @param quickjs
     * @param val
     * @return EXPORT
     */
    EXPORT int quickjs_js_ToBool(QuickJS_t quickjs, JSValue val)
    {
        return ((QuickJS *)quickjs)->quickjs_js_ToBool(val);
    }

    /**
     * @brief 转int
     *
     * @param quickjs
     * @param val
     * @return EXPORT
     */
    EXPORT int quickjs_js_ToInt(QuickJS_t quickjs, JSValue val)
    {
        return ((QuickJS *)quickjs)->quickjs_js_ToInt(val);
    }

    /**
     * @brief 判断是否是异常
     *
     * @param quickjs
     * @param val
     * @return true
     * @return false
     */
    EXPORT bool quickjs_is_exception(QuickJS_t quickjs, JSValue val)
    {
        return ((QuickJS *)quickjs)->quickjs_is_exception(val);
    }

    /**
     * @brief 获取异常信息
     *
     * @param quickjs
     * @return const char *
     */
    EXPORT const char *quickjs_get_exception(QuickJS_t quickjs)
    {
        return ((QuickJS *)quickjs)->quickjs_get_exception();
    }

    /**
     * @brief 释放
     *
     * @param quickjs
     */
    EXPORT void quickjs_free(QuickJS_t quickjs)
    {
        delete static_cast<QuickJS *>(quickjs);
    }

    /**
     * @brief 创建一个JS的undefined值
     *
     * @param quickjs
     * @return JSValue
     */
    EXPORT JSValue quickjs_new_undefined(QuickJS_t quickjs)
    {
        return ((QuickJS *)quickjs)->quickjs_new_undefined();
    }

    /**
     * @brief 创建一个JS的null值
     *
     * @param quickjs
     * @return JSValue
     */
    EXPORT JSValue quickjs_new_null(QuickJS_t quickjs)
    {
        return ((QuickJS *)quickjs)->quickjs_new_null();
    }

    /**
     * @brief 创建一个JS的true值
     *
     * @param quickjs
     * @return JSValue
     */
    EXPORT JSValue quickjs_new_true(QuickJS_t quickjs)
    {
        return ((QuickJS *)quickjs)->quickjs_new_true();
    }

    /**
     * @brief 创建一个JS的false值
     *
     * @param quickjs
     * @return JSValue
     */
    EXPORT JSValue quickjs_new_false(QuickJS_t quickjs)
    {
        return ((QuickJS *)quickjs)->quickjs_new_false();
    }

    /**
     * @brief 创建一个JS的字符串
     *
     * @param quickjs
     * @param str
     * @return JSValue
     */
    EXPORT JSValue quickjs_new_string(QuickJS_t quickjs, const char *str)
    {
        return ((QuickJS *)quickjs)->quickjs_new_string(str);
    }

    /**
     * @brief 创建一个JS的int
     *
     * @param quickjs
     * @param val
     * @return JSValue
     */
    EXPORT JSValue quickjs_new_int(QuickJS_t quickjs, int val)
    {
        return ((QuickJS *)quickjs)->quickjs_new_int(val);
    }

    /**
     * @brief 字符串转json对象
     *
     * @param quickjs
     * @param str
     * @return JSValue
     */
    EXPORT JSValue quickjs_new_json(QuickJS_t quickjs, const char *str)
    {
        return ((QuickJS *)quickjs)->quickjs_str_to_json(str);
    }

    /**
     * @brief 创建一个JS的double
     *
     * @param quickjs
     * @param val
     * @return JSValue
     */
    EXPORT JSValue quickjs_new_double(QuickJS_t quickjs, double val)
    {
        return ((QuickJS *)quickjs)->quickjs_new_double(val);
    }

    /**
     * @brief 设置全局变量
     *
     * @param quickjs
     * @param property_name 变量名
     * @param value 值
     * @return int
     */
    EXPORT int quickjs_set_property_str(QuickJS_t quickjs, const char *property_name, JSValue value)
    {
        return ((QuickJS *)quickjs)->quickjs_set_property_str(property_name, value);
    }
}