#!/bin/bash

set -x

binary=graphcolor

./${binary} timeout || exit 1
