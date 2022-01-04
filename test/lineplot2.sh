#!/bin/bash

set -x

binary=lineplot2

./${binary} timeout || exit 1
