#!/bin/bash

set -x

binary=axis_scaling

./${binary} timeout || exit 1
