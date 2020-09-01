




diskRead=$(cat /proc/diskstats | grep "sda " | awk '{print $8 ,2*$9,$10}')
#echo $diskRead

sectorWriten[0]=$(cat /proc/diskstats | grep "sda " | awk '{print $10}')
time_spend_writing[0]=$(cat /proc/diskstats | grep "sda " | awk '{print $11}')

sleep 2

sectorWriten[1]=$(cat /proc/diskstats | grep "sda " | awk '{print $10 }')
time_spend_writing[1]=$(cat /proc/diskstats | grep "sda " | awk '{print $11}')


for ((i=0;i<2;i++))
    do
        echo ${sectorWriten[i]} ${time_spend_writing[i]}
    done

sectorSize=4096

awk "BEGIN { printf \" write speed : %d \",1000*$sectorSize*(${sectorWriten[1]} - ${sectorWriten[0]})/(${time_spend_writing[1]} - ${time_spend_writing[0]})}"



    
    
