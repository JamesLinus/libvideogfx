#/*********************************************************************
  libvideogfx/graphics/draw/blit.hh

  purpose:
    Functions for copying images, extracting rectangles, ...

  notes:

  to do:

  author(s):
   - Dirk Farin, farin@ti.uni-mannheim.de
     University Mannheim, Dept. Circuitry and Simulation
     B 6,26 EG, room 0.10 / D-68131 Mannheim / Germany

  modifications:
    29/Jan/2002 - Dirk Farin - first implementation
 *********************************************************************/

#ifndef LIBVIDEOGFX_GRAPHICS_DRAW_BLIT_HH
#define LIBVIDEOGFX_GRAPHICS_DRAW_BLIT_HH

#include "libvideogfx/graphics/basic/bitmap.hh"
#include "libvideogfx/graphics/basic/image.hh"
#include "libvideogfx/error.hh"


/* Copy bitmap "src" into "dst". The destination bitmap will be created to have the
   same size as the source bitmap. If the source bitmap is empty, then the destination
   bitmap content is released.
   If the destination is shared, a new bitmap will be created.
*/
template <class Pel> void CopyToNew(Bitmap<Pel>& dst,const Bitmap<Pel>& src);

/* Logically the same as Image.Clone(). However, when the destination image is
   already of the right size and not shared, only the image content is copied
   without allocating new memory. */
template <class Pel> void CopyToNew(Image<Pel>& dst,const Image<Pel>& src);

/* Copy bitmap to destination. Destination bitmap must exist and will not
   be decoupled if it is shared. */
template <class Pel> void Copy(Bitmap<Pel>& dst,const Bitmap<Pel>& src);

/* Copy the image content at the border lines into the border area.
 */
template <class Pel> void ExtrudeIntoBorder(Bitmap<Pel>&);

/* Fill the image border with constant value.
 */
template <class Pel> void FillBorder(Bitmap<Pel>&, Pel value);


// ------------------------------- implementation -----------------------------------

template <class Pel> void CopyToNew(Bitmap<Pel>& dst,const Bitmap<Pel>& src)
{
  if (src.IsEmpty())
    { dst.Release(); return; }

  const int w = src.AskWidth();
  const int h = src.AskHeight();

  dst.Create(w,h);

  Assert(w == dst.AskWidth());
  Assert(h == dst.AskHeight());

  const Pel*const* sp = src.AskFrame();
  Pel*const* dp = dst.AskFrame();

  for (int y=0;y<h;y++)
    memcpy(dp[y],sp[y],w*sizeof(Pel));
}

template <class Pel> void CopyToNew(Image<Pel>& dst,const Image<Pel>& src)
{
  for (int i=0;i<4;i++)
    CopyToNew(dst.AskBitmap((BitmapChannel)i), src.AskBitmap((BitmapChannel)i));

  dst.SetParam(src.AskParam());
}


template <class Pel> void Copy(Bitmap<Pel>& dst,const Bitmap<Pel>& src)
{
  const int w = src.AskWidth();
  const int h = src.AskHeight();

  Assert(w == dst.AskWidth());
  Assert(h == dst.AskHeight());

  const Pel*const* sp = src.AskFrame();
  Pel*const* dp = dst.AskFrame();

  for (int y=0;y<h;y++)
    memcpy(dp[y],sp[y],w*sizeof(Pel));
}

template <class Pel> void ExtrudeIntoBorder(Bitmap<Pel>& bm)
{
  Pel*const* p = bm.AskFrame();
  int w = bm.AskWidth();
  int h = bm.AskHeight();
  int border = bm.AskBorder();

  for (int b=1;b<=border;b++)
    for (int x=0;x<w;x++)
      {
	p[-b][x] = p[0][x];
	p[h+b-1][x] = p[h-1][x];
      }

  for (int y=-border;y<h+border;y++)
    for (int b=1;b<=border;b++)
      {
	p[y][-b] = p[y][0];
	p[y][w+b-1] = p[y][w-1];
      }
}

template <class Pel> void FillBorder(Bitmap<Pel>& bm, Pel value)
{
  Pel*const* p = bm.AskFrame();
  int w = bm.AskWidth();
  int h = bm.AskHeight();
  int border = bm.AskBorder();

  for (int b=1;b<=border;b++)
    for (int x=0;x<w;x++)
      {
	p[-b][x] = p[h+b-1][x] = value;
      }

  for (int y=-border;y<h+border;y++)
    for (int b=1;b<=border;b++)
      {
	p[y][-b] = p[y][w+b-1] = value;
      }
}

#endif
