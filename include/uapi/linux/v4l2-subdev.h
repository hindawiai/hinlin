<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * V4L2 subdev userspace API
 *
 * Copyright (C) 2010 Nokia Corporation
 *
 * Contacts: Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *	     Sakari Ailus <sakari.ailus@iki.fi>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#अगर_अघोषित __LINUX_V4L2_SUBDEV_H
#घोषणा __LINUX_V4L2_SUBDEV_H

#समावेश <linux/ioctl.h>
#समावेश <linux/types.h>
#समावेश <linux/v4l2-common.h>
#समावेश <linux/v4l2-mediabus.h>

/**
 * क्रमागत v4l2_subdev_क्रमmat_whence - Media bus क्रमmat type
 * @V4L2_SUBDEV_FORMAT_TRY: try क्रमmat, क्रम negotiation only
 * @V4L2_SUBDEV_FORMAT_ACTIVE: active क्रमmat, applied to the device
 */
क्रमागत v4l2_subdev_क्रमmat_whence अणु
	V4L2_SUBDEV_FORMAT_TRY = 0,
	V4L2_SUBDEV_FORMAT_ACTIVE = 1,
पूर्ण;

/**
 * काष्ठा v4l2_subdev_क्रमmat - Pad-level media bus क्रमmat
 * @which: क्रमmat type (from क्रमागत v4l2_subdev_क्रमmat_whence)
 * @pad: pad number, as reported by the media API
 * @क्रमmat: media bus क्रमmat (क्रमmat code and frame size)
 * @reserved: drivers and applications must zero this array
 */
काष्ठा v4l2_subdev_क्रमmat अणु
	__u32 which;
	__u32 pad;
	काष्ठा v4l2_mbus_framefmt क्रमmat;
	__u32 reserved[8];
पूर्ण;

/**
 * काष्ठा v4l2_subdev_crop - Pad-level crop settings
 * @which: क्रमmat type (from क्रमागत v4l2_subdev_क्रमmat_whence)
 * @pad: pad number, as reported by the media API
 * @rect: pad crop rectangle boundaries
 * @reserved: drivers and applications must zero this array
 */
काष्ठा v4l2_subdev_crop अणु
	__u32 which;
	__u32 pad;
	काष्ठा v4l2_rect rect;
	__u32 reserved[8];
पूर्ण;

#घोषणा V4L2_SUBDEV_MBUS_CODE_CSC_COLORSPACE	0x00000001
#घोषणा V4L2_SUBDEV_MBUS_CODE_CSC_XFER_FUNC	0x00000002
#घोषणा V4L2_SUBDEV_MBUS_CODE_CSC_YCBCR_ENC	0x00000004
#घोषणा V4L2_SUBDEV_MBUS_CODE_CSC_HSV_ENC	V4L2_SUBDEV_MBUS_CODE_CSC_YCBCR_ENC
#घोषणा V4L2_SUBDEV_MBUS_CODE_CSC_QUANTIZATION	0x00000008

/**
 * काष्ठा v4l2_subdev_mbus_code_क्रमागत - Media bus क्रमmat क्रमागतeration
 * @pad: pad number, as reported by the media API
 * @index: क्रमmat index during क्रमागतeration
 * @code: क्रमmat code (MEDIA_BUS_FMT_ definitions)
 * @which: क्रमmat type (from क्रमागत v4l2_subdev_क्रमmat_whence)
 * @flags: flags set by the driver, (V4L2_SUBDEV_MBUS_CODE_*)
 * @reserved: drivers and applications must zero this array
 */
काष्ठा v4l2_subdev_mbus_code_क्रमागत अणु
	__u32 pad;
	__u32 index;
	__u32 code;
	__u32 which;
	__u32 flags;
	__u32 reserved[7];
पूर्ण;

/**
 * काष्ठा v4l2_subdev_frame_size_क्रमागत - Media bus क्रमmat क्रमागतeration
 * @index: क्रमmat index during क्रमागतeration
 * @pad: pad number, as reported by the media API
 * @code: क्रमmat code (MEDIA_BUS_FMT_ definitions)
 * @min_width: minimum frame width, in pixels
 * @max_width: maximum frame width, in pixels
 * @min_height: minimum frame height, in pixels
 * @max_height: maximum frame height, in pixels
 * @which: क्रमmat type (from क्रमागत v4l2_subdev_क्रमmat_whence)
 * @reserved: drivers and applications must zero this array
 */
काष्ठा v4l2_subdev_frame_size_क्रमागत अणु
	__u32 index;
	__u32 pad;
	__u32 code;
	__u32 min_width;
	__u32 max_width;
	__u32 min_height;
	__u32 max_height;
	__u32 which;
	__u32 reserved[8];
पूर्ण;

/**
 * काष्ठा v4l2_subdev_frame_पूर्णांकerval - Pad-level frame rate
 * @pad: pad number, as reported by the media API
 * @पूर्णांकerval: frame पूर्णांकerval in seconds
 * @reserved: drivers and applications must zero this array
 */
काष्ठा v4l2_subdev_frame_पूर्णांकerval अणु
	__u32 pad;
	काष्ठा v4l2_fract पूर्णांकerval;
	__u32 reserved[9];
पूर्ण;

/**
 * काष्ठा v4l2_subdev_frame_पूर्णांकerval_क्रमागत - Frame पूर्णांकerval क्रमागतeration
 * @pad: pad number, as reported by the media API
 * @index: frame पूर्णांकerval index during क्रमागतeration
 * @code: क्रमmat code (MEDIA_BUS_FMT_ definitions)
 * @width: frame width in pixels
 * @height: frame height in pixels
 * @पूर्णांकerval: frame पूर्णांकerval in seconds
 * @which: क्रमmat type (from क्रमागत v4l2_subdev_क्रमmat_whence)
 * @reserved: drivers and applications must zero this array
 */
काष्ठा v4l2_subdev_frame_पूर्णांकerval_क्रमागत अणु
	__u32 index;
	__u32 pad;
	__u32 code;
	__u32 width;
	__u32 height;
	काष्ठा v4l2_fract पूर्णांकerval;
	__u32 which;
	__u32 reserved[8];
पूर्ण;

/**
 * काष्ठा v4l2_subdev_selection - selection info
 *
 * @which: either V4L2_SUBDEV_FORMAT_ACTIVE or V4L2_SUBDEV_FORMAT_TRY
 * @pad: pad number, as reported by the media API
 * @target: Selection target, used to choose one of possible rectangles,
 *	    defined in v4l2-common.h; V4L2_SEL_TGT_* .
 * @flags: स्थिरraपूर्णांक flags, defined in v4l2-common.h; V4L2_SEL_FLAG_*.
 * @r: coordinates of the selection winकरोw
 * @reserved: क्रम future use, set to zero क्रम now
 *
 * Hardware may use multiple helper winकरोws to process a video stream.
 * The काष्ठाure is used to exchange this selection areas between
 * an application and a driver.
 */
काष्ठा v4l2_subdev_selection अणु
	__u32 which;
	__u32 pad;
	__u32 target;
	__u32 flags;
	काष्ठा v4l2_rect r;
	__u32 reserved[8];
पूर्ण;

/**
 * काष्ठा v4l2_subdev_capability - subdev capabilities
 * @version: the driver versioning number
 * @capabilities: the subdev capabilities, see V4L2_SUBDEV_CAP_*
 * @reserved: क्रम future use, set to zero क्रम now
 */
काष्ठा v4l2_subdev_capability अणु
	__u32 version;
	__u32 capabilities;
	__u32 reserved[14];
पूर्ण;

/* The v4l2 sub-device video device node is रेजिस्टरed in पढ़ो-only mode. */
#घोषणा V4L2_SUBDEV_CAP_RO_SUBDEV		0x00000001

/* Backwards compatibility define --- to be हटाओd */
#घोषणा v4l2_subdev_edid v4l2_edid

#घोषणा VIDIOC_SUBDEV_QUERYCAP			_IOR('V',  0, काष्ठा v4l2_subdev_capability)
#घोषणा VIDIOC_SUBDEV_G_FMT			_IOWR('V',  4, काष्ठा v4l2_subdev_क्रमmat)
#घोषणा VIDIOC_SUBDEV_S_FMT			_IOWR('V',  5, काष्ठा v4l2_subdev_क्रमmat)
#घोषणा VIDIOC_SUBDEV_G_FRAME_INTERVAL		_IOWR('V', 21, काष्ठा v4l2_subdev_frame_पूर्णांकerval)
#घोषणा VIDIOC_SUBDEV_S_FRAME_INTERVAL		_IOWR('V', 22, काष्ठा v4l2_subdev_frame_पूर्णांकerval)
#घोषणा VIDIOC_SUBDEV_ENUM_MBUS_CODE		_IOWR('V',  2, काष्ठा v4l2_subdev_mbus_code_क्रमागत)
#घोषणा VIDIOC_SUBDEV_ENUM_FRAME_SIZE		_IOWR('V', 74, काष्ठा v4l2_subdev_frame_size_क्रमागत)
#घोषणा VIDIOC_SUBDEV_ENUM_FRAME_INTERVAL	_IOWR('V', 75, काष्ठा v4l2_subdev_frame_पूर्णांकerval_क्रमागत)
#घोषणा VIDIOC_SUBDEV_G_CROP			_IOWR('V', 59, काष्ठा v4l2_subdev_crop)
#घोषणा VIDIOC_SUBDEV_S_CROP			_IOWR('V', 60, काष्ठा v4l2_subdev_crop)
#घोषणा VIDIOC_SUBDEV_G_SELECTION		_IOWR('V', 61, काष्ठा v4l2_subdev_selection)
#घोषणा VIDIOC_SUBDEV_S_SELECTION		_IOWR('V', 62, काष्ठा v4l2_subdev_selection)
/* The following ioctls are identical to the ioctls in videodev2.h */
#घोषणा VIDIOC_SUBDEV_G_STD			_IOR('V', 23, v4l2_std_id)
#घोषणा VIDIOC_SUBDEV_S_STD			_IOW('V', 24, v4l2_std_id)
#घोषणा VIDIOC_SUBDEV_ENUMSTD			_IOWR('V', 25, काष्ठा v4l2_standard)
#घोषणा VIDIOC_SUBDEV_G_EDID			_IOWR('V', 40, काष्ठा v4l2_edid)
#घोषणा VIDIOC_SUBDEV_S_EDID			_IOWR('V', 41, काष्ठा v4l2_edid)
#घोषणा VIDIOC_SUBDEV_QUERYSTD			_IOR('V', 63, v4l2_std_id)
#घोषणा VIDIOC_SUBDEV_S_DV_TIMINGS		_IOWR('V', 87, काष्ठा v4l2_dv_timings)
#घोषणा VIDIOC_SUBDEV_G_DV_TIMINGS		_IOWR('V', 88, काष्ठा v4l2_dv_timings)
#घोषणा VIDIOC_SUBDEV_ENUM_DV_TIMINGS		_IOWR('V', 98, काष्ठा v4l2_क्रमागत_dv_timings)
#घोषणा VIDIOC_SUBDEV_QUERY_DV_TIMINGS		_IOR('V', 99, काष्ठा v4l2_dv_timings)
#घोषणा VIDIOC_SUBDEV_DV_TIMINGS_CAP		_IOWR('V', 100, काष्ठा v4l2_dv_timings_cap)

#पूर्ण_अगर
