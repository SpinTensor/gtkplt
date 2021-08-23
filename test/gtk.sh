#!/bin/bash

set -x

binary=gtk

./${binary} timeout || exit 1
