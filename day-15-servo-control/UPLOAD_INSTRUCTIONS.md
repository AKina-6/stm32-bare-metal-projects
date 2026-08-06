# Day 15上传说明

目标仓库：`stm32-bare-metal-projects`

```bash
cd projects/05-servo-control
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

STM32配置TIM3_CH1/PA6、PSC=71、ARR=19999；舵机独立5 V供电并共地。

```bash
git pull
git add .
git commit -m "feat: add servo PWM angle mapping and safe motion controller"
git push
```
