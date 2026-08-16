#include <simplewebp/simplewebp.h>

#include <stdlib.h>
#include <string.h>

#undef NDEBUG
#include <assert.h>

/* 100x100 one-color lossless WebP (libwebp-test-data
 * one_color_no_palette.webp).
 */
static const unsigned char one_color_no_palette_webp[] = {
  0x52, 0x49, 0x46, 0x46, 0x14, 0x00, 0x00, 0x00, 0x57, 0x45, 0x42, 0x50,
  0x56, 0x50, 0x38, 0x4c, 0x08, 0x00, 0x00, 0x00, 0x2f, 0x63, 0xc0, 0x18,
  0x10, 0x88, 0x88, 0x08
};

int
main (void)
{
  simplewebp *webp = 0;
  simplewebp_error err;
  size_t width = 0;
  size_t height = 0;
  unsigned char *rgba;
  const char *garbage = "not a webp";

  assert (simplewebp_version () == 20260718);
  assert (SIMPLEWEBP_VERSION == 20260718);
  assert (simplewebp_get_error_text (SIMPLEWEBP_NO_ERROR) != 0);
  assert (simplewebp_get_error_text (SIMPLEWEBP_NO_ERROR)[0] != '\0');

  err = simplewebp_load_from_memory ((void *) garbage,
                                     strlen (garbage),
                                     0,
                                     &webp);
  assert (err == SIMPLEWEBP_NOT_WEBP_ERROR);
  assert (webp == 0);

  err = simplewebp_load_from_memory ((void *) one_color_no_palette_webp,
                                     sizeof (one_color_no_palette_webp),
                                     0,
                                     &webp);
  assert (err == SIMPLEWEBP_NO_ERROR);
  assert (webp != 0);

  simplewebp_get_dimensions (webp, &width, &height);
  assert (width == 100);
  assert (height == 100);
  assert (simplewebp_is_lossless (webp));

  rgba = malloc (width * height * 4);
  assert (rgba != 0);
  err = simplewebp_decode (webp, rgba, 0);
  assert (err == SIMPLEWEBP_NO_ERROR);

  simplewebp_unload (webp);
  free (rgba);
  return 0;
}
