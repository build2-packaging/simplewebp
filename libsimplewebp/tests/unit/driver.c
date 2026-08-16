#include <simplewebp/simplewebp.h>

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#undef NDEBUG
#include <assert.h>

static int
ends_with_webp (const char *name)
{
  size_t n = strlen (name);
  return n > 5 && strcmp (name + n - 5, ".webp") == 0;
}

static int
decode_file (const char *path)
{
  FILE *f;
  unsigned char *buf;
  long size;
  simplewebp *webp = 0;
  simplewebp_error err;
  size_t width = 0;
  size_t height = 0;
  unsigned char *rgba;

  f = fopen (path, "rb");
  if (f == 0)
  {
    fprintf (stderr, "cannot open %s\n", path);
    return 0;
  }

  if (fseek (f, 0, SEEK_END) != 0)
  {
    fclose (f);
    return 0;
  }

  size = ftell (f);
  if (size < 0)
  {
    fclose (f);
    return 0;
  }

  rewind (f);
  buf = malloc ((size_t) size);
  if (buf == 0)
  {
    fclose (f);
    return 0;
  }

  if (fread (buf, 1, (size_t) size, f) != (size_t) size)
  {
    free (buf);
    fclose (f);
    return 0;
  }

  fclose (f);

  err = simplewebp_load_from_memory (buf, (size_t) size, 0, &webp);
  if (err != SIMPLEWEBP_NO_ERROR)
  {
    fprintf (stderr, "load failed %s: %s\n",
             path, simplewebp_get_error_text (err));
    free (buf);
    return 0;
  }

  simplewebp_get_dimensions (webp, &width, &height);
  assert (width > 0);
  assert (height > 0);

  rgba = malloc (width * height * 4);
  assert (rgba != 0);

  err = simplewebp_decode (webp, rgba, 0);
  if (err != SIMPLEWEBP_NO_ERROR)
  {
    fprintf (stderr, "decode failed %s: %s\n",
             path, simplewebp_get_error_text (err));
    free (rgba);
    simplewebp_unload (webp);
    free (buf);
    return 0;
  }

  simplewebp_unload (webp);
  free (rgba);
  free (buf);
  return 1;
}

int
main (int argc, char *argv[])
{
  DIR *dir;
  struct dirent *ent;
  unsigned ok = 0;
  unsigned bad = 0;

  if (argc != 2)
  {
    fprintf (stderr, "usage: %s <data-dir>\n", argv[0]);
    return 2;
  }

  dir = opendir (argv[1]);
  if (dir == 0)
  {
    fprintf (stderr, "cannot open directory %s\n", argv[1]);
    return 2;
  }

  while ((ent = readdir (dir)) != 0)
  {
    char path[4096];
    int n;

    if (!ends_with_webp (ent->d_name))
      continue;

    n = snprintf (path, sizeof (path), "%s/%s", argv[1], ent->d_name);
    if (n < 0 || (size_t) n >= sizeof (path))
    {
      fprintf (stderr, "path too long: %s/%s\n", argv[1], ent->d_name);
      ++bad;
      continue;
    }

    if (decode_file (path))
      ++ok;
    else
      ++bad;
  }

  closedir (dir);

  fprintf (stderr, "Success: %u Failure: %u\n", ok, bad);
  return bad == 0 && ok > 0 ? 0 : 1;
}
