Welcome to giac_history
=======================

Giac/Xcas is a free computer algebra system for Windows, Mac OSX and Linux/Unix under the GPL3 license <https://xcas.univ-grenoble-alpes.fr/en.html>. Sadly, even if Giac/Xcas (in particular, the command line programs giac and icas) makes use of the GNU readline library for command line editing and the internal history function, the author(s) "forgot" to add a couple of code lines to make the history permanent, like Bash. 

giac\_history is a small shared library that aims at adding this functionality at least to the Linux/Unix version - and potentially to the MacOS version because it is based on BSD Unix as well. As for Windows, I don't care for the moment. giac\_history can used in a very simple way by prepending the giac or icas command with "LD_PRELOAD=/path/to/giac\_history.so". 


Motivation
==========

I wrote giac\_history for two reasons: 

* even if the change to implement a permanent history is a very simple one (really, an handful of code lines), such a change is not necessarily cross-platform. In particular, I doubt it will work on Windows, and I do not have the skills and the motivation to implement this on Windows as well. Since the author(s) of Ciac/Xcas aim at providing a cross-platform tool, I very much doubt they would accept a change as simple as this one. 

* Even if I accept a Giac/Xcas fork just for my own purposes, I seem to be unable to compile the package on Ubuntu 22.04 LTS which is my main working platform. Regardless of the configure settings or the GCC/GXX standard, the compiler eventually throws fatal errors that I am not willing to troubleshoot, also because the Giac/Xcas source code is very sparsely documented. A shared library overwriting the GNU readline functions add\_history() and using\_history() was a much simpler and straightforward solution. 

* the use case is a small handheld CAS device using the GiantBoard module <https://www.crowdsupply.com/groboards/giant-board> from Groboard and the Keyboard Featherwing gadget <https://www.solder.party/docs/keyboard-featherwing/> from Solder Party. The OS is the armhf version of Debian Buster for now. Sadly, both parts are out of production and/or unsupported but they were still lying around collecting dust. Boy did I have to reverse engineer stuff. 



Build and Install
=================

A local copy of the Git Repository can be obtained by cloning it from
the original repository using

    git clone https://github.com/h-milz/giac_history.git 

After obtaining the source, simply invoke

    make ; make install

The default installation path for the shared library is /usr/local/lib, which can be adapted in the Makefile.

That's it. The build process requires that the development packages libreadline-dev and libc6-dev (Debian/Ubuntu) are installed. 


Usage
=====

Simply invoke giac like this:

    LD_PRELOAD=/path/to/giac_history.so giac

The default filename for the history is ~/.giac_history which can be overridden by the environment variable GIAC_HISTFILE. The default maximum length is 100 entries which can be overridden by the environment variable GIAC_HISTFILESIZE. Best, put both in your ~/.bashrc like so, together with a shell alias simplifying the command invocation: 

    GIAC_HISTFILE="/path/to/your_fancy_giac_history_file_name"
    GIAC_HISTFILESIZE=500
    alias giac='LD_PRELOAD=/path/to/giac_history.so /usr/bin/giac'




License
=======

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

Copyright
=========

Copyright (C) 2024 Harald Milz <hm@seneca.muc.de>

All rights reserved.



Have fun! 
