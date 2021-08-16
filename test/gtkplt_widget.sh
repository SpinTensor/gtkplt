#!/bin/bash

set -x

binary=gtkplt_widget

./${binary} || exit 1
