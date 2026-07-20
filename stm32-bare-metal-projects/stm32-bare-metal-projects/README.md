# STM32 Bare-Metal Projects

本仓库收录基于 STM32F103C8T6 的裸机项目，展示如何将多个外设驱动组合成完整应用。

## 项目方向

- LED 与按键交互
- OLED 菜单
- 温湿度与光照采集
- 舵机和电机控制
- Flash 参数保存
- 多传感器监测终端

## 目录

```text
projects/
├── 01-led-button/
├── 02-oled-menu/
├── 03-dht11-monitor/
├── 04-bh1750-light-meter/
├── 05-servo-control/
├── 06-flash-settings/
└── 07-mini-environment-monitor/
shared/
docs/
learning-log/
```

每个项目应包含独立 README、接线表、关键代码和运行结果。
