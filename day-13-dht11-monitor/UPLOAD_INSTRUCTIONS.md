# Day 13 上传说明

目标仓库：`stm32-bare-metal-projects`

```bash
cd projects/03-dht11-monitor
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

提交：

```bash
git add .
git commit -m "feat: add DHT11 frame parser and temperature humidity monitor"
git push
```
