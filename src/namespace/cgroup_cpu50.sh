#!/bin/bash
mkdir -p /sys/fs/cgroup/cpu/test
echo 50000 > /sys/fs/cgroup/cpu/test/cpu.cfs_quota_us
echo $$ > /sys/fs/cgroup/cpu/test/tasks
echo $$

x=0
while [ True ];do
    x=$x+1
done;
