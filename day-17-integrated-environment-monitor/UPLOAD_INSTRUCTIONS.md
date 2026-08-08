# Day 17 上传说明

目标仓库：`stm32-bare-metal-projects`

```bash
cd projects/07-integrated-environment-monitor
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/environment_monitor_sim
```

Git：

```bash
git pull
git add .
git commit -m "feat: integrate environmental monitor application with sensors UI servo and settings"
git push
```
