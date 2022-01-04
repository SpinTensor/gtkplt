#!/bin/bash

set -x

binary=linepointplot

./${binary} timeout || exit 1
