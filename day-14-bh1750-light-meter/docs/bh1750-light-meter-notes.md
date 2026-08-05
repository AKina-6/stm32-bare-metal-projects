# BH1750 光照计学习笔记

## 滑动平均

滑动平均保留最近 N 个样本：

```text
Average = 最近 N 个 lux 之和 / N
```

本项目使用长度为 8 的环形数组，更新复杂度为 O(1)。

## 状态管理

- `OK`：最近读取成功；
- `SENSOR_ERROR`：最新读取失败；
- `STALE`：有效数据超过 3000 ms 未更新。

## 分层结构

```text
BH1750 Driver
→ Light Meter Application
→ UART / OLED Output
```

驱动负责通信和换算，应用层负责滤波、等级和状态。
