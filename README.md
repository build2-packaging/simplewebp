# simplewebp - WebP image decoder C library

This is a `build2` package repository for
[`simplewebp`](https://github.com/MikuAuahDark/simplewebp), a single-file WebP
decoder.

This file contains setup instructions and other details that are more
appropriate for development rather than consumption. If you want to use
`simplewebp` in your `build2`-based project, then instead see the accompanying
[`PACKAGE-README.md`](libsimplewebp/PACKAGE-README.md) file.

The development setup uses the standard `bdep`-based workflow. For example:

```
git clone --recurse-submodules https://github.com/build2-packaging/simplewebp.git
cd simplewebp

bdep init -C @gcc cc config.c=gcc
bdep update
bdep test
```
