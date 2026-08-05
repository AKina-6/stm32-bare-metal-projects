# Day 14 上传说明

目标仓库：

```text
stm32-bare-metal-projects
```

## 自动测试

```bash
cd projects/04-bh1750-light-meter
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## STM32 集成

1. PB6/PB7 配置为 I2C1。
2. BH1750 ADDR 接 GND，使用地址 `0x23`。
3. USART1 配置为 115200。
4. 每 500 ms 读取一次光照。
5. 测试遮挡、普通室内和强光场景。
6. 补充串口截图和实物照片。

## Git 提交

```bash
git pull
git add .
git commit -m "feat: add BH1750 light meter with filtering and level classification"
git push
```
