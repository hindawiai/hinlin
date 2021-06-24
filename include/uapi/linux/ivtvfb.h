<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
    On Screen Display cx23415 Framebuffer driver

    Copyright (C) 2006, 2007  Ian Armstrong <ian@iarmst.demon.co.uk>

    This program is मुक्त software; you can redistribute it and/or modअगरy
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License क्रम more details.

    You should have received a copy of the GNU General Public License
    aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#अगर_अघोषित __LINUX_IVTVFB_H__
#घोषणा __LINUX_IVTVFB_H__

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>

/* Framebuffer बाह्यal API */

काष्ठा ivtvfb_dma_frame अणु
	व्योम __user *source;
	अचिन्हित दीर्घ dest_offset;
	पूर्णांक count;
पूर्ण;

#घोषणा IVTVFB_IOC_DMA_FRAME 	_IOW('V', BASE_VIDIOC_PRIVATE+0, काष्ठा ivtvfb_dma_frame)

#पूर्ण_अगर
