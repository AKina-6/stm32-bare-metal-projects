# 分层固件架构学习笔记

`main.c` 中混合 GPIO、传感器、通信和业务逻辑会导致依赖混乱。推荐分层：

```text
App：产品行为与状态机
Driver：器件和协议
BSP：开发板引脚与硬件能力
Platform Adapter：把 App 接口连接到具体平台
```

App 依赖抽象接口，STM32 与 Host Mock 分别实现接口。这样可以在电脑端验证按键边沿、时间调度和 LED 状态变化。
