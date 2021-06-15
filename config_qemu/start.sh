#!/bin/sh
cd ../host/etc
mkdir qemu
cd qemu
touch bridge.conf
echo 'allow br0'>bridge.conf
cd ../../../images
ip link add name br0 type bridge
ip link set dev br0 up
ip link set dev ens33 up
ip link set dev ens33 master br0
sh ./start-qemu.sh
