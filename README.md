# 🐇 quickjs 引 擎 绑 定 到 PHP, 实 现 运 行 JS。

| 要求 | 版本 |
| ---- | ---- |
| Windows | * |
| Linux | * |
| PHP-FFI | * |
| PHP | 8.1+ |

### 例子

```php

use Bunny\QuickJs\QuickJs;

// 实例化
$quick_js = new QuickJs();

// 创建运行时
$run_time = $quick_js->create();

// js代码
$code = <<<JS
    var a = 7;
    function add(x,y){
        return x+y
    }
    add(a,3)
JS;

// 执行js代码
$js_eval = $quick_js->eval($run_time, $code);

// 判断是否运行成功
if ($quick_js->isException($run_time, $js_eval)) {
    echo $quick_js->toString($run_time, $js_eval) . PHP_EOL;
} else {
    echo "运行失败!" . PHP_EOL;
}

// 释放
$quick_js->free($run_time);

// 结果：10
```

### 说明

类`QuickJs`

```php
/**
 * QuickJs class
 */
class QuickJs
{   
    /**
     * 构造 function
     *
     * @param string $dir library文件夹
     */
    public function __construct(string $dir = "")
    {}

    /**
     * 创建JS运行时 function
     *
     * @return \FFI\CData JS运行时对象
     */
    public function create(): \FFI\CData
    {}

    /**
     * 执行代码 function
     *
     * @param \FFI\CData $run_time JS运行时对象
     * @param string $code JS代码
     * @return \FFI\CData 结果对象
     */
    public function eval(\FFI\CData $run_time, string $code): \FFI\CData
    {}

    /**
     * 是否是异常 function
     *
     * @param \FFI\CData $run_time JS运行时对象
     * @param \FFI\CData $js_eval JS对象
     * @return boolean
     */
    public function isException(\FFI\CData $run_time, \FFI\CData $js_eval): bool
    {}

    /**
     * js对象转字符串 function
     *
     * @param \FFI\CData $run_time
     * @param \FFI\CData $js_obj
     * @return string
     */
    public function toString(\FFI\CData $run_time, \FFI\CData $js_obj): string
    {}

    /**
     * js对象转bool function
     *
     * @param \FFI\CData $run_time
     * @param \FFI\CData $js_obj
     * @return bool
     */
    public function toBool(\FFI\CData $run_time, \FFI\CData $js_obj): bool
    {}

    /**
     * js对象转int function
     *
     * @param \FFI\CData $run_time 
     * @param \FFI\CData $js_obj
     * @param integer $pres
     * @return integer
     */
    public function toInt(\FFI\CData $run_time, \FFI\CData $js_obj): int
    {}

    /**
     * js对象转json字符串 function
     *
     * @param \FFI\CData $run_time 
     * @param \FFI\CData $js_obj
     * @return string
     */
    public function JSONStringify(\FFI\CData $run_time, \FFI\CData $js_obj): string
    {}

    /**
     * json字符串转json对象 function
     *
     * @param \FFI\CData $run_time
     * @param string $json
     * @return \FFI\CData
     */
    public function ParseJSON(\FFI\CData $run_time, string $json): \FFI\CData
    {}

    /**
     * 释放JS运行时 function
     *
     * @param \FFI\CData $run_time JS运行时对象
     * @return void
     */
    public function free(\FFI\CData $run_time): void
    {}
}
```