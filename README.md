# simplewebp - WebP image decoder C library

This is a `build2` package repository for
[`simplewebp`](https://github.com/MikuAuahDark/simplewebp), a single-file WebP
decoder.

This file contains setup instructions and other details that are more
appropriate for development rather than consumption. If you want to use
`simplewebp` in your `build2`-based project, then instead see the accompanying
[`PACKAGE-README.md`](libsimplewebp/PACKAGE-README.md) file.

Upstream does not tag releases. `upstream/` is pinned to commit `d1a728a`
(`SIMPLEWEBP_VERSION` `20260718`). The package version is placeholder semver
`0.0.1` so a later real upstream version is not blocked.

Upstream test fixtures live in `libsimplewebp/tests/unit/data/` as
symlinks into `upstream/test/data` (the nested `libwebp-test-data`
submodule). They are excluded from the published archive. Clone with
`--recurse-submodules` to run them.

The development setup for `simplewebp` uses the standard `bdep`-based workflow.
For example:

```
git clone --recurse-submodules .../simplewebp.git
cd simplewebp

bdep init -C @gcc cc config.c=gcc
bdep update
bdep test
```
