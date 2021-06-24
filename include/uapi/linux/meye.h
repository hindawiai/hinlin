<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * Motion Eye video4linux driver क्रम Sony Vaio PictureBook
 *
 * Copyright (C) 2001-2003 Stelian Pop <stelian@popies.net>
 *
 * Copyright (C) 2001-2002 Alcथखve <www.alcove.com>
 *
 * Copyright (C) 2000 Andrew Tridgell <tridge@valinux.com>
 *
 * Earlier work by Werner Almesberger, Paul `Rusty' Russell and Paul Mackerras.
 *
 * Some parts borrowed from various video4linux drivers, especially
 * bttv-driver.c and zoran.c, see original files क्रम credits.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#अगर_अघोषित _MEYE_H_
#घोषणा _MEYE_H_

/****************************************************************************/
/* Private API क्रम handling mjpeg capture / playback.                       */
/****************************************************************************/

काष्ठा meye_params अणु
	अचिन्हित अक्षर subsample;
	अचिन्हित अक्षर quality;
	अचिन्हित अक्षर sharpness;
	अचिन्हित अक्षर agc;
	अचिन्हित अक्षर picture;
	अचिन्हित अक्षर framerate;
पूर्ण;

/* query the extended parameters */
#घोषणा MEYEIOC_G_PARAMS	_IOR ('v', BASE_VIDIOC_PRIVATE+0, काष्ठा meye_params)
/* set the extended parameters */
#घोषणा MEYEIOC_S_PARAMS	_IOW ('v', BASE_VIDIOC_PRIVATE+1, काष्ठा meye_params)
/* queue a buffer क्रम mjpeg capture */
#घोषणा MEYEIOC_QBUF_CAPT	_IOW ('v', BASE_VIDIOC_PRIVATE+2, पूर्णांक)
/* sync a previously queued mjpeg buffer */
#घोषणा MEYEIOC_SYNC		_IOWR('v', BASE_VIDIOC_PRIVATE+3, पूर्णांक)
/* get a still uncompressed snapshot */
#घोषणा MEYEIOC_STILLCAPT	_IO  ('v', BASE_VIDIOC_PRIVATE+4)
/* get a jpeg compressed snapshot */
#घोषणा MEYEIOC_STILLJCAPT	_IOR ('v', BASE_VIDIOC_PRIVATE+5, पूर्णांक)

/* V4L2 निजी controls */
#घोषणा V4L2_CID_MEYE_AGC		(V4L2_CID_USER_MEYE_BASE + 0)
#घोषणा V4L2_CID_MEYE_PICTURE		(V4L2_CID_USER_MEYE_BASE + 1)
#घोषणा V4L2_CID_MEYE_FRAMERATE		(V4L2_CID_USER_MEYE_BASE + 2)

#पूर्ण_अगर
