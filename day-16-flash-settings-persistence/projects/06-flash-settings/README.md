# Project 06：Flash 参数保存、CRC 校验与掉电恢复

## 功能
- 保存光照阈值、温度报警阈值、遥测周期、舵机 Home 角度。
- 双槽 A/B 记录，使用 `sequence` 选择最新有效记录。
- 每条记录包含 Magic、Version、Payload Size、CRC32。
- 最新记录损坏时自动回退到上一份有效记录。
- 空 Flash 首次启动时写入默认配置。
- 参数修改后延迟 2 秒保存，减少 Flash 擦写。

## 记录格式
```text
Magic | Version | Payload Size | Sequence | Settings | CRC32
```

## 自动验证
```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/flash_settings_sim
```

## STM32 实物集成
在 STM32F103 上应预留两个完整 Flash 页作为 Slot 0 / Slot 1。地址必须根据实际芯片容量、Flash 页大小和链接脚本确定，禁止直接复制未经核对的固定地址。
