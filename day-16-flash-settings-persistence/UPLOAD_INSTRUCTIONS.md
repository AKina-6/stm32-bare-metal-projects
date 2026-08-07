# Day 16 上传说明
目标仓库：`stm32-bare-metal-projects`

```bash
cd projects/06-flash-settings
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
git add .
git commit -m "feat: add flash settings persistence with CRC and recovery"
git push
```

STM32 上线前必须核对 Flash 容量、页大小、程序占用范围，并在链接脚本中保留两个参数页。
