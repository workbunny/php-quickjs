<?php

// 严格模式
declare(strict_types=1);

namespace Bunny\QuickJs;

/**
 * QuickJs class
 */
class QuickJs
{
    /**
     * FFI variable
     *
     * @var \FFI
     */
    protected \FFI $ffi;

    /**
     * 构造 function
     *
     * @param string $dir library文件夹
     */
    public function __construct(string $dir = "")
    {
        if ($dir === "") {
            $dir = dirname(__DIR__) . DIRECTORY_SEPARATOR . "build" . DIRECTORY_SEPARATOR . "os";
        }
        switch (\PHP_OS_FAMILY) {
            case "Linux":
                $suffix = "so";
                break;
            case "Windows":
                $suffix = "dll";
                break;
            default:
                throw new \Exception("QuickJs仅支持windows系统和linux系统。" . PHP_EOL
                    . "QuickJs supports only windows and linux.");
        }

        $header_content =  file_get_contents($dir . DIRECTORY_SEPARATOR . "QuickJs.h");
        $library_file = $dir . DIRECTORY_SEPARATOR . "QuickJs." . $suffix;
        $this->ffi = \FFI::cdef($header_content, $library_file);
    }

    /**
     * 创建JS运行时 function
     *
     * @return \FFI\CData JS运行时对象
     */
    public function create(): \FFI\CData
    {
        return $this->ffi->quickjs_create();
    }

    /**
     * 执行代码 function
     *
     * @param \FFI\CData $run_time JS运行时对象
     * @param string $code JS代码
     * @return \FFI\CData 结果对象
     */
    public function eval(\FFI\CData $run_time, string $code): \FFI\CData
    {
        return $this->ffi->quickjs_eval($run_time, $code);
    }

    /**
     * 是否是异常 function
     *
     * @param \FFI\CData $run_time JS运行时对象
     * @param \FFI\CData $js_eval JS对象
     * @return boolean
     */
    public function isException(\FFI\CData $run_time, \FFI\CData $js_eval): bool
    {
        return !$this->ffi->quickjs_is_exception($run_time, $js_eval);
    }

    /**
     * 获取异常信息 function
     *
     * @param \FFI\CData $run_time
     * @return string
     */
    public function getException(\FFI\CData $run_time): string
    {
        return $this->ffi->quickjs_get_exception($run_time);
    }

    /**
     * js对象转字符串 function
     *
     * @param \FFI\CData $run_time
     * @param \FFI\CData $js_obj
     * @return string
     */
    public function toString(\FFI\CData $run_time, \FFI\CData $js_obj): string
    {
        return $this->ffi->quickjs_js_ToCString($run_time, $js_obj);
    }

    /**
     * js对象转bool function
     *
     * @param \FFI\CData $run_time
     * @param \FFI\CData $js_obj
     * @return bool
     */
    public function toBool(\FFI\CData $run_time, \FFI\CData $js_obj): bool
    {
        return $this->ffi->quickjs_js_ToBool($run_time, $js_obj);
    }

    /**
     * js对象转int function
     *
     * @param \FFI\CData $run_time 
     * @param \FFI\CData $js_obj
     * @param integer $pres
     * @return integer
     */
    public function toInt(\FFI\CData $run_time, \FFI\CData $js_obj): int
    {
        return $this->ffi->quickjs_js_ToInt($run_time, $js_obj);
    }

    /**
     * 释放JS运行时 function
     *
     * @param \FFI\CData $run_time JS运行时对象
     * @return void
     */
    public function free(\FFI\CData $run_time): void
    {
        $this->ffi->quickjs_free($run_time);
    }

    /**
     * 创建JS的undefined值 function
     *
     * @param \FFI\CData $run_time JS运行时对象
     * @return \FFI\CData
     */
    public function newUndefined(\FFI\CData $run_time): \FFI\CData
    {
        return $this->ffi->quickjs_new_undefined($run_time);
    }

    /**
     * 创建JS的null值 function
     *
     * @param \FFI\CData $run_time JS运行时对象
     * @return \FFI\CData
     */
    public function newNull(\FFI\CData $run_time): \FFI\CData
    {
        return $this->ffi->quickjs_new_null($run_time);
    }

    /**
     * 创建JS的true值 function
     *
     * @param \FFI\CData $run_time JS运行时对象
     * @return \FFI\CData
     */
    public function newTrue(\FFI\CData $run_time): \FFI\CData
    {
        return $this->ffi->quickjs_new_true($run_time);
    }

    /**
     * 创建JS的false值 function
     *
     * @param \FFI\CData $run_time JS运行时对象
     * @return \FFI\CData
     */
    public function newFalse(\FFI\CData $run_time): \FFI\CData
    {
        return $this->ffi->quickjs_new_false($run_time);
    }

    /**
     * 创建JS的字符串值 function
     *
     * @param \FFI\CData $run_time JS运行时对象
     * @param string $str 字符串
     * @return \FFI\CData
     */
    public function newString(\FFI\CData $run_time, string $str): \FFI\CData
    {
        return $this->ffi->quickjs_new_string($run_time, $str);
    }

    /**
     * 创建JS的int值 function
     *
     * @param \FFI\CData $run_time JS运行时对象
     * @param integer $int int值
     * @return \FFI\CData
     */
    public function newInt(\FFI\CData $run_time, int $int): \FFI\CData
    {
        return $this->ffi->quickjs_new_int($run_time, $int);
    }

    /**
     * 创建JS的json值 function
     *
     * @param \FFI\CData $run_time JS运行时对象
     * @param string $json json字符串
     * @return \FFI\CData
     */
    public function newJson(\FFI\CData $run_time, string $json): \FFI\CData
    {
        return $this->ffi->quickjs_new_json($run_time, $json);
    }

    /**
     * 创建JS的double值 function
     *
     * @param \FFI\CData $run_time JS运行时对象
     * @param float $float double值
     * @return \FFI\CData
     */
    public function newFloat(\FFI\CData $run_time, float $float): \FFI\CData
    {
        return $this->ffi->quickjs_new_float($run_time, $float);
    }
}
