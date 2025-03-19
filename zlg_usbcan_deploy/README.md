# zlg_usb_can

用于在工控机上部署周立功的usbcan设备

# 使用

进到当前目录：

```bash
# 进到当前仓库所在目录
cd <zlg_usb_can_path>

bash deploy/zlg_usbcan_delpoy.bash
```

检查是否成功部署：

```bash
# 1.检查服务状态
sudo systemctl status radar_can_init.service

# 2.检查是否有can，下列结果输出需要大于等于4
ll /sys/class/net | grep can | wc -l
```
