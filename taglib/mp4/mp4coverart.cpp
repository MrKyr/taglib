/**************************************************************************
    copyright            : (C) 2009 by Lukáš Lalinský
    email                : lalinsky@gmail.com
 **************************************************************************/

/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <taglib.h>
#include <tdebug.h>
#include "mp4coverart.h"

using namespace TagLib;

class MP4::CoverArt::CoverArtPrivate : public RefCounter
{
public:
  CoverArtPrivate() : RefCounter(), format(MP4::CoverArt::JPEG) {}

  Format format;
  ByteVector data;
};

MP4::CoverArt::CoverArt(Format format, const ByteVector &data)
  : d(new CoverArtPrivate())
{
  d->format = format;
  d->data = data;
}

MP4::CoverArt::CoverArt(const CoverArt &item) : d(item.d)
{
#ifndef TAGLIB_USE_CXX11

  d->ref();

#endif
}

MP4::CoverArt &
  MP4::CoverArt::operator=(const CoverArt &item)
{
#ifdef TAGLIB_USE_CXX11

  d = item.d;

#else

  if(d->deref()) {
    delete d;
  }
  d = item.d;
  d->ref();

#endif

  return *this;
}

#ifdef TAGLIB_USE_CXX11

MP4::CoverArt &
  MP4::CoverArt::operator=(CoverArt &&item)
{
  d = std::move(item.d);
  return *this;
}

#endif

MP4::CoverArt::~CoverArt()
{
#ifndef TAGLIB_USE_CXX11

  if(d->deref()) {
    delete d;
  }

#endif
}

MP4::CoverArt::Format
MP4::CoverArt::format() const
{
  return d->format;
}

ByteVector
MP4::CoverArt::data() const
{
  return d->data;
}

