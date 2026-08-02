# Project 01：BSP、Drivers、App 分层固件架构

## 目标

将应用逻辑与 STM32 HAL 解耦，使同一套 App 逻辑既能运行在开发板上，也能在电脑端自动测试。

## 架构

```text
App → Platform Interface ← STM32 BSP / Host Mock
```

App 层只描述：LED 每 500 ms 翻转、按键按下时立即切换 LED、长按只触发一次。App 层不直接出现 GPIO 端口、引脚或 HAL 调用。

## 默认硬件

| 功能 | 引脚 | 配置 |
|---|---|---|
| LED | PB0 | 推挽输出 |
| Button | PA0 | 内部上拉输入 |
| Tick | SysTick | 1 ms |

## 自动测试

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/layered_firmware_sim
```

## 结果含义

- 500 ms 时自动翻转 LED；
- 600 ms 首次按下时再次翻转；
- 650 ms 长按不重复触发；
- 松开后再次按下，按键计数增加。
