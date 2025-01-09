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
        // 不需要再调用 quick_free()
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
    JSValue quick_eval(const char *js_code)
    {
        JSValue val = JS_Eval(ctx, js_code, strlen(js_code), "quick.js", JS_EVAL_TYPE_GLOBAL);
        JS_FreeValue(ctx, val);
        return val;
    }

    /**
     * @brief json字符串转json对象
     *
     * @param buf
     * @return JSValue
     */
    JSValue quick_js_ParseJSON(const char *buf)
    {
        JSValue val = JS_ParseJSON(ctx, buf, strlen(buf), "parse.json");
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
    bool quick_is_exception(JSValue val)
    {
        return JS_IsException(val);
    }

    /**
     * @brief 转字符串
     *
     * @param val
     * @return const char*
     */
    inline const char *quick_js_ToCString(JSValue val)
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
    int quick_js_ToBool(JSValue val)
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
    int quick_js_ToInt(JSValue val)
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
     * @brief js解析json
     *
     * @param val
     * @return JSValue
     */
    const char *quick_js_JSONStringify(JSValue val)
    {
        JSValue json_str_val = JS_JSONStringify(ctx, val, JS_UNDEFINED, JS_UNDEFINED);
        const char *json_str = JS_ToCString(ctx, json_str_val);
        JS_FreeValue(ctx, val);
        JS_FreeValue(ctx, json_str_val);
        JS_FreeCString(ctx, json_str);
        return json_str;
    }

private:
    JSRuntime *rt;
    JSContext *ctx;
};

typedef void *QuickJS_t;

// ---------------- 导出函数
extern "C"
{
    QuickJS_t quickjs_create();                                         // 创建
    void quickjs_free(QuickJS_t quickjs);                               // 释放
    JSValue quickjs_eval(QuickJS_t quickjs, const char *js_code);       // 执行js代码
    bool quickjs_is_exception(QuickJS_t quickjs, JSValue val);          // 判断是否是异常
    const char *quick_js_ToCString(QuickJS_t quickjs, JSValue val);     // 转字符串
    int quick_js_ToBool(QuickJS_t quickjs, JSValue val);                // 转bool
    int quick_js_ToInt(QuickJS_t quickjs, JSValue val);                 // 转int
    const char *quick_js_JSONStringify(QuickJS_t quickjs, JSValue val); // json对象解析json字符串
    JSValue quick_js_ParseJSON(QuickJS_t quickjs, const char *buf);     // json字符串转json对象

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
        return ((QuickJS *)quickjs)->quick_eval(js_code);
    }

    /**
     * @brief 转字符串
     *
     * @param quickjs
     * @param val
     * @return EXPORT const*
     */
    EXPORT const char *quick_js_ToCString(QuickJS_t quickjs, JSValue val)
    {
        return ((QuickJS *)quickjs)->quick_js_ToCString(val);
    }

    /**
     * @brief 转bool
     *
     * @param quickjs
     * @param val
     * @return EXPORT
     */
    EXPORT int quick_js_ToBool(QuickJS_t quickjs, JSValue val)
    {
        return ((QuickJS *)quickjs)->quick_js_ToBool(val);
    }

    /**
     * @brief 转int
     *
     * @param quickjs
     * @param val
     * @return EXPORT
     */
    EXPORT int quick_js_ToInt(QuickJS_t quickjs, JSValue val)
    {
        return ((QuickJS *)quickjs)->quick_js_ToInt(val);
    }

    /**
     * @brief js解析json
     *
     * @param quickjs
     * @param val
     * @return const*
     */
    EXPORT const char *quick_js_JSONStringify(QuickJS_t quickjs, JSValue val)
    {
        return ((QuickJS *)quickjs)->quick_js_JSONStringify(val);
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
        return ((QuickJS *)quickjs)->quick_is_exception(val);
    }

    /**
     * @brief json字符串转json对象
     *
     * @param quickjs
     * @param buf
     * @return JSValue
     */
    EXPORT JSValue quick_js_ParseJSON(QuickJS_t quickjs, const char *buf)
    {
        return ((QuickJS *)quickjs)->quick_js_ParseJSON(buf);
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
}