# libsimplewebp - WebP image decoder C library

This is a `build2` package for the
[`simplewebp`](https://github.com/MikuAuahDark/simplewebp) C library. It is a
single-file WebP decoder (lossy, lossless, and alpha) with no third-party
dependencies.


## Usage

To start using `libsimplewebp` in your project, add the following `depends`
value to your `manifest`, adjusting the version constraint as appropriate:

```
depends: libsimplewebp == 2026.7.18
```

The package version is a semver-shaped coercion of the upstream date version
(`upstream-version: 20260718`, from `SIMPLEWEBP_VERSION`). Use an exact or
revision constraint rather than `^` or `~`.

Then import the library in your `buildfile`:

```
import libs = libsimplewebp%lib{simplewebp}
```

Include the public header as:

```
#include <simplewebp.h>
```

Do not define `SIMPLEWEBP_IMPLEMENTATION` when linking this package. The
implementation is already compiled into `lib{simplewebp}`.


## Importable targets

This package provides the following importable targets:

```
lib{simplewebp}
```

The compiled WebP decoder. Load from memory or stdio, then decode to RGBA
or planar YUVA.


## Configuration variables

This package has no configuration variables.
