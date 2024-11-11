#!/bin/bash

sudo su

cid=`docker ps -a | grep assistant | awk '{print $1}'`
[[ x'' != x"$cid" ]] && docker container stop $cid && docker container rm $cid \
	&& docker run -idt --privileged=true --name assistant --restart=always --network=host \
        -v /tmp:/tmp \
        assistant:v1
exit
