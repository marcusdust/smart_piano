# 智能钢琴版freepinao说明

## 软件简介
该软件在开源钢琴软件pianobooster的代码上修改而来，运行在linux上，在ubuntu14.2和16.4上测试过。
用usb线连接电钢琴，该软件会捕捉用户按键情况，并将反馈信息通过串口发送给stm32板，再由stm32板驱动ws2182b灯带控制
每个led灯的亮暗和颜色。

## 代码简介
代码在src文件夹下，Makefile在build文件夹下，在build文件夹下运行make即可编译出可执行文件pianobooster。
按键 index -- led index映射表在文件src/Conductor.cpp中的get_led_index函数里，需根据真实情况修改。
所有名称带有led的变量和函数都是为设置led灯带添加的。运行时注意打印信息，里面会打印出调试信息，包括了文件名和行号，主要内容有：
led_set_update: led_on_list: 需要亮灯的led编号。
led_set_update: write data: 在串口写入了led相关信息，包括led编号，颜色。
led_set_update: write -1 bytes to com，在串口写入了 -1 bytes的数据（串口没有正确打开）。
pcKeyPress: keynote: 60：用户按了60号键。



## 注意事项
- linux需要root权限才能打开串口，所以必须sudo ./pianobooster打开才能正确运行。
- build/Makefile中的几个目录名需要改为对应实际放置代码的目录。





