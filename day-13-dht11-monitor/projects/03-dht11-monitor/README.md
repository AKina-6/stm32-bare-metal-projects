# Project 03：DHT11 温湿度监测

## 已实现

- 5 字节 DHT11 数据帧；
- 校验和计算与错误帧拒绝；
- 温度、湿度转换；
- 成功/失败次数统计；
- OK、SENSOR_ERROR、STALE 状态；
- 电脑端编译、测试和模拟；
- STM32 集成说明。

## 默认硬件

| 项目 | 配置 |
|---|---|
| MCU | STM32F103C8T6 |
| DHT11 DATA | PA1 |
| 微秒计时 | TIM2，1 MHz |
| UART | USART1，115200 |
| 读取周期 | 2000 ms |
| 过期阈值 | 5000 ms |

## 数据格式

```text
湿度整数 + 湿度小数 + 温度整数 + 温度小数 + 校验和
```

校验和为前四字节之和的低 8 位。

## 测试

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/dht11_sim
```

## 实物预期

```text
TEMP 26.0 C HUM 58.0 %
```

DHT11 读取间隔建议不小于 1 秒，本项目采用 2 秒。
