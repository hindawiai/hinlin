<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
    Public ivtv API header
    Copyright (C) 2003-2004  Kevin Thayer <nufan_wfk at yahoo.com>
    Copyright (C) 2004-2007  Hans Verkuil <hverkuil@xs4all.nl>

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

#अगर_अघोषित __LINUX_IVTV_H__
#घोषणा __LINUX_IVTV_H__

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
#समावेश <linux/videodev2.h>

/* ivtv knows several distinct output modes: MPEG streaming,
   YUV streaming, YUV updates through user DMA and the passthrough
   mode.

   In order to clearly tell the driver that we are in user DMA
   YUV mode you need to call IVTV_IOC_DMA_FRAME with y_source == शून्य
   first (althrough अगर you करोn't then the first समय
   DMA_FRAME is called the mode चयन is करोne स्वतःmatically).

   When you बंद the file handle the user DMA mode is निकासed again.

   While in one mode, you cannot use another mode (EBUSY is वापसed).

   All this means that अगर you want to change the YUV पूर्णांकerlacing
   क्रम the user DMA YUV mode you first need to करो call IVTV_IOC_DMA_FRAME
   with y_source == शून्य beक्रमe you can set the correct क्रमmat using
   VIDIOC_S_FMT.

   Eventually all this should be replaced with a proper V4L2 API,
   but क्रम now we have to करो it this way. */

काष्ठा ivtv_dma_frame अणु
	क्रमागत v4l2_buf_type type; /* V4L2_BUF_TYPE_VIDEO_OUTPUT */
	__u32 pixelक्रमmat;	 /* 0 == same as destination */
	व्योम __user *y_source;   /* अगर शून्य and type == V4L2_BUF_TYPE_VIDEO_OUTPUT,
				    then just चयन to user DMA YUV output mode */
	व्योम __user *uv_source;  /* Unused क्रम RGB pixelक्रमmats */
	काष्ठा v4l2_rect src;
	काष्ठा v4l2_rect dst;
	__u32 src_width;
	__u32 src_height;
पूर्ण;

#घोषणा IVTV_IOC_DMA_FRAME		_IOW ('V', BASE_VIDIOC_PRIVATE+0, काष्ठा ivtv_dma_frame)

/* Select the passthrough mode (अगर the argument is non-zero). In the passthrough
   mode the output of the encoder is passed immediately पूर्णांकo the decoder. */
#घोषणा IVTV_IOC_PASSTHROUGH_MODE	_IOW ('V', BASE_VIDIOC_PRIVATE+1, पूर्णांक)

/* Deprecated defines: applications should use the defines from videodev2.h */
#घोषणा IVTV_SLICED_TYPE_TELETEXT_B     V4L2_MPEG_VBI_IVTV_TELETEXT_B
#घोषणा IVTV_SLICED_TYPE_CAPTION_525    V4L2_MPEG_VBI_IVTV_CAPTION_525
#घोषणा IVTV_SLICED_TYPE_WSS_625        V4L2_MPEG_VBI_IVTV_WSS_625
#घोषणा IVTV_SLICED_TYPE_VPS            V4L2_MPEG_VBI_IVTV_VPS

#पूर्ण_अगर /* _LINUX_IVTV_H */
