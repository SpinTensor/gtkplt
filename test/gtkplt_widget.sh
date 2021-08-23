#!/bin/bash

set -x

binary=gtkplt_widget

./${binary} timeout || exit 1
