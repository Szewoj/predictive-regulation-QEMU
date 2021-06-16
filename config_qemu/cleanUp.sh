#!/bin/sh
ip link set dev ens33 nomaster
ip link set dev br0 down
ip link delete br0 type bridge
