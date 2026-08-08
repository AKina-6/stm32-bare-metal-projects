# Project 07：综合环境监测器

## 项目目标

整合 DHT11、BH1750、SSD1306 OLED、USART1、舵机和 Flash 参数管理。

## 状态逻辑

```text
Sensor Fault > Too Hot > Too Dark > Normal
```

默认阈值：光照 200 lux，温度 30.0 C。正常状态舵机 90°，报警/故障状态 150°。

## 数据流

```text
DHT11 + BH1750 -> Environment App -> OLED / UART / Servo
Flash Settings ---------------------> Config
```

## 自动验证

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/environment_monitor_sim
```

模拟四种场景：NORMAL、TOO_DARK、TOO_HOT、SENSOR_FAULT。
