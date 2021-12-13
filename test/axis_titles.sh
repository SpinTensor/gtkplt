#!/bin/bash

set -x

binary=axis_titles

./${binary} timeout || exit 1
