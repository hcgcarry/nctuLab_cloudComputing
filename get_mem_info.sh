totalMem=$(cat /proc/meminfo | awk '/MemTotal/ {print $2}')
#echo $diskRead

freeMem=$(cat /proc/meminfo |  awk '/MemFree/ {print $2}')

awk "BEGIN { printf \"%d/%d  \",$freeMem,$totalMem}"
