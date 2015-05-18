#!/bin/sh

cwd=`pwd`

for hf in `find ./src -name '*.h'`
do
	echo $hf
	file="${hf##*/}"
	cp -s $cwd/$hf ./include/$file
done
