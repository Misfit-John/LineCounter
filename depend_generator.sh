#!/bin/sh

flags=$1
cur_path=`pwd`
output_file=${cur_path}/depend

gen_depend()
{
	for file in $1/*
	do
		if [ -d $file ]
		then
			echo "in $file"
			gen_depend $file
		elif [ -f $file ]
		then
			if [ "${file##*.}" = "cpp" -o "${file##*.}" = "c" ]
			then
				echo $1/`clang++ -MM ${flags} $file`|sed 's/\\//g' >> $output_file
			fi
		fi
	done
}

gen_depend "."

