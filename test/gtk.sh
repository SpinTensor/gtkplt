#!/bin/bash

set -x

binary=gtk

./${binary} || exit 1
