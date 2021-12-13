#!/bin/bash

set -x

binary=plot_title

./${binary} timeout || exit 1
