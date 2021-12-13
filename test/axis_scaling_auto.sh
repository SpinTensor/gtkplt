#!/bin/bash

set -x

binary=axis_scaling_auto

./${binary} timeout || exit 1
