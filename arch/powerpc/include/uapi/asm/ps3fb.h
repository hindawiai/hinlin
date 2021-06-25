<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (C) 2006 Sony Computer Entertainment Inc.
 * Copyright 2006, 2007 Sony Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published
 * by the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License aदीर्घ
 * with this program; अगर not, ग_लिखो to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fअगरth Floor, Boston, MA 02110-1301 USA.
 */

#अगर_अघोषित _ASM_POWERPC_PS3FB_H_
#घोषणा _ASM_POWERPC_PS3FB_H_

#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>

/* ioctl */
#घोषणा PS3FB_IOCTL_SETMODE       _IOW('r',  1, पूर्णांक) /* set video mode */
#घोषणा PS3FB_IOCTL_GETMODE       _IOR('r',  2, पूर्णांक) /* get video mode */
#घोषणा PS3FB_IOCTL_SCREENINFO    _IOR('r',  3, पूर्णांक) /* get screen info */
#घोषणा PS3FB_IOCTL_ON            _IO('r', 4)        /* use IOCTL_FSEL */
#घोषणा PS3FB_IOCTL_OFF           _IO('r', 5)        /* वापस to normal-flip */
#घोषणा PS3FB_IOCTL_FSEL          _IOW('r', 6, पूर्णांक)  /* blit and flip request */

#अगर_अघोषित FBIO_WAITFORVSYNC
#घोषणा FBIO_WAITFORVSYNC         _IOW('F', 0x20, __u32) /* रुको क्रम vsync */
#पूर्ण_अगर

काष्ठा ps3fb_ioctl_res अणु
	__u32 xres; /* frame buffer x_size */
	__u32 yres; /* frame buffer y_size */
	__u32 xoff; /* margine x  */
	__u32 yoff; /* margine y */
	__u32 num_frames; /* num of frame buffers */
पूर्ण;

#पूर्ण_अगर /* _ASM_POWERPC_PS3FB_H_ */
