#!/bin/bash

set -x

binary=gtk_cairo

./${binary} || exit 1
