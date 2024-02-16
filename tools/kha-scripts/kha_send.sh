#!/bin/sh
echo $1 | nc -u -w 1 192.168.1.1 5005
