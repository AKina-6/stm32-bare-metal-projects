# OLED 菜单状态机学习笔记

## 核心状态

- 当前选择项；
- 当前页面；
- 页面是否打开；
- 输入事件计数。

## 输入事件

```text
UP
DOWN
SELECT
BACK
```

事件可以来自 GPIO、EXTI、UART 或编码器。

## 显示抽象

菜单核心只依赖：

```c
clear();
draw_text();
present();
```

因此可连接 SSD1306、LCD 或电脑端模拟显示。

## 刷新策略

持续全屏刷新会增加 I²C 占用。推荐在菜单状态或页面数据变化时设置 `redraw_required`，主循环按需刷新。
