#!/bin/bash
totalCount=0
function countFile()
    for fileName in `ls $1` 
    do
	fullPath=$1"/"$fileName
	if [ -d $fullPath ] 
	then
	    countFile $fullPath
	else
	    tempstr=$(echo $fileName | grep '\(\.h$\)\|\(\.cpp$\)\|\(\.vs$\)|\(\.frag$\)')
	    #echo $fileName":"${#tempstr}
	    if [ ${#tempstr} -ne 0 ]
	    then
		cfile=`grep -c "" $fullPath`
		if [ ${#cfile} -eq 0 ] 
		then
		cfile=0
		fi
		totalCount=`expr $totalCount + $cfile`
		echo -e "\033[36m $fileName \033[0m : \033[31m $cfile \033[0m"
	    fi
	fi
    done

echo -e "\033[32;5m 统计中...\033[0m"
curPath=`dirname $0`
countFile $curPath
echo -e "\033[32;4m 总的代码行数为\033[0;4m: \033[35;4m $totalCount \033[0;25m"

