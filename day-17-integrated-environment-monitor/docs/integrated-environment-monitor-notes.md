# 综合环境监测器架构笔记

核心链路：Drivers -> Data Model -> Decision Logic -> UI / Telemetry / Actuator。

应用层只负责数据有效性、阈值判断、系统状态和舵机目标，不直接操作 GPIO、I2C、UART、PWM 或 Flash。

推荐周期：DHT11 2000 ms，BH1750 500 ms，Servo 20 ms，Telemetry 2000 ms，OLED 按需刷新，Flash 参数稳定 2000 ms 后保存。
