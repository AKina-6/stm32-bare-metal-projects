# Day 12 上传说明

目标仓库：

```text
stm32-bare-metal-projects
```

## 自动测试

```bash
cd projects/02-oled-menu-interface
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Git 提交

```bash
git pull
git add .
git commit -m "feat: add OLED menu state machine and display abstraction"
git push
```
