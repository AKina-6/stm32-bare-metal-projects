# Project 05：舵机 PWM 控制、角度映射与安全限幅

## 功能

- 0°～180°角度映射到500～2500 us脉宽；
- 越界角度自动限幅并累计次数；
- 分步移动，降低机械冲击；
- 1 MHz定时器下直接将脉宽换算为CCR；
- STM32 TIM3_CH1集成示例；
- 电脑端单元测试和运动模拟。

## 默认配置

| 项目 | 配置 |
|---|---|
| PWM引脚 | PA6 / TIM3_CH1 |
| PWM频率 | 50 Hz |
| 定时器Tick | 1 MHz |
| PSC | 71 |
| ARR | 19999 |
| 0° | 500 us |
| 90° | 1500 us |
| 180° | 2500 us |

## 测试

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/servo_control_sim
```

## 供电

舵机使用独立5 V电源，并与STM32共地。避免直接使用开发板3.3 V引脚为舵机供电。
