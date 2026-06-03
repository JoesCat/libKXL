		libKXL, a visual,sound library
		Copyright (C) 2001, Katsuyoshi Sato
			fc3srx7@mwnet.or.jp

[![Coverage Status](https://coveralls.io/repos/github/Quipyowert2/libKXL/badge.svg?branch=master)](https://coveralls.io/github/Quipyowert2/libKXL?branch=master)

KXL (Kacchan X Windows System Library) is a multimedia library targeted at
game development that provides functions for simple image and sound output
as well as higher level functions for text drawing, timer and events
handling and image manipulation.

This package contains the header files and static library needed to
compile applications that use libKXL

--------------------------------------------------------------------------

This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
675 Mass Ave, Cambridge, MA 02139, USA.

--------------------------------------------------------------------------

# Install
```bash
cd libKXL
autoreconf -i
automake
./configure
make
make check
sudo make install
```
--------------------------------------------------------------------------
# Requirements

* libX11-devel (required)
* pipewire (default, 1.3 or higher)
* pipewire-pulse (default, 1.3 or higher)
* pipewire-devel (default, 1.3 or higher)
* pulseaudio (1.2.4 or lower)
* libpulse-devel (1.2.4 or lower)
--------------------------------------------------------------------------

**Note**: Until Dec 4, 2022, the sources used the euc-jp encoding. To use this encoding in Vim,
edit a file and then run this command to switch the encoding:
```vim
:edit ++encoding=euc-jp
```
