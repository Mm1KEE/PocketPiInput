# PocketPiInput
PocketPi驱动，包含键盘、触摸、大写锁定灯、电量指示灯.

# 食用姿势
1.在Arduino ide的库管理中安装[SimpleFilter](https://github.com/Mm1KEE/SimpleFilter),[SmoothTouch](https://github.com/Mm1KEE/SmoothTouch)这两个库。    
这两个库是我写出来用于触摸数据处理和触摸动作处理的，属于为了PocketPi这碟醋包了两顿饺子。SimpleFilter理论上也可用于其他数据降噪，SmoothTouch目前只兼容XPT2046，后面会优化成可自定义事件和兼容其他触摸，大概。
2.下载本库的文件，打开PocketPiAll文件夹中。    
其中PocketPiAll.ino为主程序，PPiKeyboard.h为键盘驱动，键盘使用Caps代替Shift和Fn。   
3.开发板选择Lenardo，使用ide烧录。或者使用烧录器直接烧录hex文件。
