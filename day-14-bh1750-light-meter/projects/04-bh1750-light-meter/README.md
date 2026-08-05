# Project 04：BH1750 光照计

## 项目目标

- 使用 I²C1 读取 BH1750 光照数据。
- 将原始值转换为 lux。
- 使用 8 点滑动平均降低波动。
- 将环境亮度划分为五个等级。
- 记录成功读取、失败读取和数据过期状态。
- 通过 UART 输出实时值和平均值。
- 使用 Mock I²C 在电脑端验证驱动与应用逻辑。

## 默认硬件

| 项目 | 配置 |
|---|---|
| MCU | STM32F103C8T6 |
| I²C | I2C1 |
| SCL | PB6 |
| SDA | PB7 |
| BH1750 地址 | `0x23` |
| 读取周期 | 500 ms |
| 滑动平均窗口 | 8 个样本 |
| 数据过期阈值 | 3000 ms |
| UART | USART1，115200 |

## 亮度等级

| 平均光照 | 等级 |
|---:|---|
| `< 10 lux` | DARK |
| `< 100 lux` | DIM |
| `< 500 lux` | NORMAL |
| `< 1000 lux` | BRIGHT |
| `≥ 1000 lux` | VERY_BRIGHT |

## 初始化命令

```text
0x01 → Power On
0x07 → Reset
0x10 → Continuous High Resolution
```

## 光照换算

```text
Lux = Raw / 1.2
```

## 自动测试

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/bh1750_light_meter_sim
```

## 实物预期输出

```text
LIGHT latest=245.83 avg=231.42 level=NORMAL
```

遮挡传感器时亮度下降，手机闪光灯照射时亮度上升。
