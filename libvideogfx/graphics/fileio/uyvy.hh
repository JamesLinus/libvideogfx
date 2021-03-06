/*********************************************************************
  fileio/uyvy.hh

  purpose:
    Functions for loading and saving UYVY files of any size.

  notes:

  to do:

  author(s):
   - Dirk Farin, dirk.farin@gmx.de

  modifications:
   26/Jan/2002 - Dirk Farin - reimplementation
   15/Jul/1999 - Dirk Farin - completely rewritten
   18/Jun/9999 - Dirk Farin - first implementation
 ********************************************************************************
    LibVideoGfx - video processing library
    Copyright (C) 2002  Dirk Farin

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 ********************************************************************************/

#ifndef LIBVIDEOGFX_GRAPHICS_FILEIO_UYVY_HH
#define LIBVIDEOGFX_GRAPHICS_FILEIO_UYVY_HH

#include <fstream>
#include <iostream>

#include <libvideogfx/graphics/datatypes/image.hh>

namespace videogfx {

  // Return true if the image file size matches the specified size.
  bool CheckFileSize_UYVY(std::ifstream& istr,int w,int h);

  void ReadImage_UYVY (Image<Pixel>&,std::ifstream& istr,int w,int h);
  void WriteImage_UYVY(std::ofstream& ostr, const Image<Pixel>&);

  // obsolete
  inline void WriteImage_UYVY(const Image<Pixel>& img,std::ofstream& ostr)
  {
    std::cerr << "you're using the old syntax of libvideogfx::WriteImage_UYVY()\n";
    WriteImage_UYVY(ostr,img);
  }

}

#endif
