#!/bin/sh
IMAGE_DIR="${0%/*}/"

if [ "${1}" = "serial-only" ]; then
    EXTRA_ARGS='-nographic'
else
    EXTRA_ARGS=''
fi

export PATH="/home/dumono/Desktop/buildroot-2020.11.3/output/host/bin:${PATH}"
exec   qemu-system-aarch64 -M virt -cpu cortex-a53 -nographic -smp 1 -kernel ${IMAGE_DIR}/Image -append "rootwait root=/dev/vda console=ttyAMA0" -net nic -net bridge,br=br0 -drive file=${IMAGE_DIR}/rootfs.ext4,if=none,format=raw,id=hd0 -device virtio-blk-device,drive=hd0  ${EXTRA_ARGS}
