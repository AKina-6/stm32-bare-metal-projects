# Project 02：OLED 菜单界面与页面状态机

## 项目目标

完成一个与具体 OLED 库解耦的菜单系统，支持：

- UP/DOWN 循环选择；
- SELECT 进入页面；
- BACK 返回菜单；
- 当前菜单项高亮；
- 页面内容渲染；
- 状态变化后再刷新 OLED。

## 菜单结构

```text
Home
Sensor
Settings
About
```

## 分层结构

```text
Menu State Machine
        ↓
Display Interface
        ↓
SSD1306 Adapter / Host Display
```

## 默认硬件

| 模块 | 配置 |
|---|---|
| OLED | SSD1306 128×64 |
| I²C | I2C1 |
| SCL | PB6 |
| SDA | PB7 |
| 输入 | 按键或 UART 命令 |

## 电脑端测试

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/oled_menu_sim
```

模拟流程：

```text
INIT → DOWN → SELECT → BACK
```

## STM32 集成

1. 配置 I2C1。
2. 集成 SSD1306 库。
3. 根据实际库修改 `ssd1306_menu_adapter.c`。
4. 将按键事件映射为菜单事件。
5. 状态变化后调用 `menu_render()`。
