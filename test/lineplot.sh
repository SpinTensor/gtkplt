#!/bin/bash

set -x

binary=lineplot

./${binary} timeout || exit 1
