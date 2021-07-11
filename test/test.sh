#!/bin/bash

set -x

binary=test

./${binary} || exit 1
