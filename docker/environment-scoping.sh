#!/bin/bash

echo 'does the environment where your docker-cli get launched get copied into an execd container?'

MAH_VARIABLE=bananas docker run -it alpine sh -c 'env' | grep MAH_VARIABLE

if [[ $? -eq 0 ]]; then
  echo 'yup!'
else
  echo 'nope!'
fi
