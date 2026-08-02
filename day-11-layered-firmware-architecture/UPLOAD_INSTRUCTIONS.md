# Day 11 上传说明

目标仓库：`stm32-bare-metal-projects`

复制整个 `projects/01-layered-firmware-architecture/` 以及 docs、learning-log、进度文件。

```bash
cd projects/01-layered-firmware-architecture
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

提交：

```bash
git pull
git add .
git commit -m "feat: add layered BSP driver and application firmware architecture"
git push
```
