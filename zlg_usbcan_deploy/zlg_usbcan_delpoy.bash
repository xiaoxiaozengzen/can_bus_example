#!/bin/bash

set -e

script_path=$(cd $(dirname $0); pwd)
echo "script_path: ${script_path}"
home_path=${HOME}

# usbcanfd200_400u工作目录
work_dir=${HOME}/usbcanfd200_400u

# 检查工作目录是否存在
if [ ! -d ${work_dir} ]; then
    echo "work_dir: ${work_dir} is not exist"
    exit 1
fi

# 检查工作目录是否为空
if [ "$(ls -A ${work_dir})" ]; then
    echo "work_dir: ${work_dir} is not empty"
    echo "please remove the work_dir"
    exit 1
fi

echo "work_dir: ${work_dir}"

# 解压usbcanfd200_400u.zip到HOME目录
if [ -f ${script_path}/usbcanfd200_400u.zip ]; then
    unzip -o ${script_path}/usbcanfd200_400u.zip -d ${HOME}
else
    echo "usbcanfd200_400u.zip is not exist"
    exit 1
fi

# 编译usbcanfd200_400u
cd ${work_dir}
make

# 拷贝radar启动脚本到HOME目录
cp ${script_path}/radar_can_init.sh ${home_path}
sudo chmod 777 ${home_path}/radar_can_init.sh

# 注册开机自启动服务
sudo cp ${script_path}/radar_can_init.service /etc/systemd/system
sudo systemctl daemon-reload
sudo systemctl enable radar_can_init.service
sudo systemctl start radar_can_init.service
