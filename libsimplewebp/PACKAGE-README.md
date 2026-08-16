# libsimplewebp - WebP image decoder C library

This is a `build2` package for the
[`simplewebp`](https://github.com/MikuAuahDark/simplewebp) C library. It is a
single-file WebP decoder (lossy, lossless, and alpha) with no third-party
dependencies.

Upstream does not tag releases. The source identifies itself as
`SIMPLEWEBP_VERSION` `20260718` (also recorded as `upstream-version`). This
package uses placeholder semver `0.0.1` so a later real upstream version such
as `0.1.0` or `1.0.0` still sorts after it.


## Usage

To start using `libsimplewebp` in your project, add the following `depends`
value to your `manifest`, adjusting the version constraint as appropriate:

```
depends: libsimplewebp ^0.0.1
```

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
