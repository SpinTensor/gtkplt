#!/bin/bash

set -x

binary=axis_scaling_half_auto

./${binary} timeout || exit 1
