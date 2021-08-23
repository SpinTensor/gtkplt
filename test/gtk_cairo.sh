#!/bin/bash

set -x

binary=gtk_cairo

./${binary} timeout || exit 1
