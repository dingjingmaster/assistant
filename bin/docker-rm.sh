#!/bin/bash

sudo su

cid=`docker ps -a | grep assistant | awk '{print $1}'`
[[ x'' != x"$cid" ]] && docker container stop $cid && docker container rm $cid 

exit
