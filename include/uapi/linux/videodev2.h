<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0+ WITH Linux-syscall-note) OR BSD-3-Clause) */
/*
 *  Video क्रम Linux Two header file
 *
 *  Copyright (C) 1999-2012 the contributors
 *
 *  This program is मुक्त software; you can redistribute it and/or modअगरy
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License क्रम more details.
 *
 *  Alternatively you can redistribute this file under the terms of the
 *  BSD license as stated below:
 *
 *  Redistribution and use in source and binary क्रमms, with or without
 *  modअगरication, are permitted provided that the following conditions
 *  are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary क्रमm must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the करोcumentation and/or other materials provided with the
 *     distribution.
 *  3. The names of its contributors may not be used to enकरोrse or promote
 *     products derived from this software without specअगरic prior written
 *     permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 *  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 *  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *	Header file क्रम v4l or V4L2 drivers and applications
 * with खुला API.
 * All kernel-specअगरic stuff were moved to media/v4l2-dev.h, so
 * no #अगर __KERNEL tests are allowed here
 *
 *	See https://linuxtv.org क्रम more info
 *
 *	Author: Bill Dirks <bill@thedirks.org>
 *		Justin Schoeman
 *              Hans Verkuil <hverkuil@xs4all.nl>
 *		et al.
 */
#अगर_अघोषित _UAPI__LINUX_VIDEODEV2_H
#घोषणा _UAPI__LINUX_VIDEODEV2_H

#अगर_अघोषित __KERNEL__
#समावेश <sys/समय.स>
#पूर्ण_अगर
#समावेश <linux/compiler.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/types.h>
#समावेश <linux/v4l2-common.h>
#समावेश <linux/v4l2-controls.h>

/*
 * Common stuff क्रम both V4L1 and V4L2
 * Moved from videodev.h
 */
#घोषणा VIDEO_MAX_FRAME               32
#घोषणा VIDEO_MAX_PLANES               8

/*
 *	M I S C E L L A N E O U S
 */

/*  Four-अक्षरacter-code (FOURCC) */
#घोषणा v4l2_fourcc(a, b, c, d)\
	((__u32)(a) | ((__u32)(b) << 8) | ((__u32)(c) << 16) | ((__u32)(d) << 24))
#घोषणा v4l2_fourcc_be(a, b, c, d)	(v4l2_fourcc(a, b, c, d) | (1U << 31))

/*
 *	E N U M S
 */
क्रमागत v4l2_field अणु
	V4L2_FIELD_ANY           = 0, /* driver can choose from none,
					 top, bottom, पूर्णांकerlaced
					 depending on whatever it thinks
					 is approximate ... */
	V4L2_FIELD_NONE          = 1, /* this device has no fields ... */
	V4L2_FIELD_TOP           = 2, /* top field only */
	V4L2_FIELD_BOTTOM        = 3, /* bottom field only */
	V4L2_FIELD_INTERLACED    = 4, /* both fields पूर्णांकerlaced */
	V4L2_FIELD_SEQ_TB        = 5, /* both fields sequential पूर्णांकo one
					 buffer, top-bottom order */
	V4L2_FIELD_SEQ_BT        = 6, /* same as above + bottom-top order */
	V4L2_FIELD_ALTERNATE     = 7, /* both fields alternating पूर्णांकo
					 separate buffers */
	V4L2_FIELD_INTERLACED_TB = 8, /* both fields पूर्णांकerlaced, top field
					 first and the top field is
					 transmitted first */
	V4L2_FIELD_INTERLACED_BT = 9, /* both fields पूर्णांकerlaced, top field
					 first and the bottom field is
					 transmitted first */
पूर्ण;
#घोषणा V4L2_FIELD_HAS_TOP(field)	\
	((field) == V4L2_FIELD_TOP	||\
	 (field) == V4L2_FIELD_INTERLACED ||\
	 (field) == V4L2_FIELD_INTERLACED_TB ||\
	 (field) == V4L2_FIELD_INTERLACED_BT ||\
	 (field) == V4L2_FIELD_SEQ_TB	||\
	 (field) == V4L2_FIELD_SEQ_BT)
#घोषणा V4L2_FIELD_HAS_BOTTOM(field)	\
	((field) == V4L2_FIELD_BOTTOM	||\
	 (field) == V4L2_FIELD_INTERLACED ||\
	 (field) == V4L2_FIELD_INTERLACED_TB ||\
	 (field) == V4L2_FIELD_INTERLACED_BT ||\
	 (field) == V4L2_FIELD_SEQ_TB	||\
	 (field) == V4L2_FIELD_SEQ_BT)
#घोषणा V4L2_FIELD_HAS_BOTH(field)	\
	((field) == V4L2_FIELD_INTERLACED ||\
	 (field) == V4L2_FIELD_INTERLACED_TB ||\
	 (field) == V4L2_FIELD_INTERLACED_BT ||\
	 (field) == V4L2_FIELD_SEQ_TB ||\
	 (field) == V4L2_FIELD_SEQ_BT)
#घोषणा V4L2_FIELD_HAS_T_OR_B(field)	\
	((field) == V4L2_FIELD_BOTTOM ||\
	 (field) == V4L2_FIELD_TOP ||\
	 (field) == V4L2_FIELD_ALTERNATE)
#घोषणा V4L2_FIELD_IS_INTERLACED(field) \
	((field) == V4L2_FIELD_INTERLACED ||\
	 (field) == V4L2_FIELD_INTERLACED_TB ||\
	 (field) == V4L2_FIELD_INTERLACED_BT)
#घोषणा V4L2_FIELD_IS_SEQUENTIAL(field) \
	((field) == V4L2_FIELD_SEQ_TB ||\
	 (field) == V4L2_FIELD_SEQ_BT)

क्रमागत v4l2_buf_type अणु
	V4L2_BUF_TYPE_VIDEO_CAPTURE        = 1,
	V4L2_BUF_TYPE_VIDEO_OUTPUT         = 2,
	V4L2_BUF_TYPE_VIDEO_OVERLAY        = 3,
	V4L2_BUF_TYPE_VBI_CAPTURE          = 4,
	V4L2_BUF_TYPE_VBI_OUTPUT           = 5,
	V4L2_BUF_TYPE_SLICED_VBI_CAPTURE   = 6,
	V4L2_BUF_TYPE_SLICED_VBI_OUTPUT    = 7,
	V4L2_BUF_TYPE_VIDEO_OUTPUT_OVERLAY = 8,
	V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE = 9,
	V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE  = 10,
	V4L2_BUF_TYPE_SDR_CAPTURE          = 11,
	V4L2_BUF_TYPE_SDR_OUTPUT           = 12,
	V4L2_BUF_TYPE_META_CAPTURE         = 13,
	V4L2_BUF_TYPE_META_OUTPUT	   = 14,
	/* Deprecated, करो not use */
	V4L2_BUF_TYPE_PRIVATE              = 0x80,
पूर्ण;

#घोषणा V4L2_TYPE_IS_MULTIPLANAR(type)			\
	((type) == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE	\
	 || (type) == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)

#घोषणा V4L2_TYPE_IS_OUTPUT(type)				\
	((type) == V4L2_BUF_TYPE_VIDEO_OUTPUT			\
	 || (type) == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE		\
	 || (type) == V4L2_BUF_TYPE_VIDEO_OVERLAY		\
	 || (type) == V4L2_BUF_TYPE_VIDEO_OUTPUT_OVERLAY	\
	 || (type) == V4L2_BUF_TYPE_VBI_OUTPUT			\
	 || (type) == V4L2_BUF_TYPE_SLICED_VBI_OUTPUT		\
	 || (type) == V4L2_BUF_TYPE_SDR_OUTPUT			\
	 || (type) == V4L2_BUF_TYPE_META_OUTPUT)

#घोषणा V4L2_TYPE_IS_CAPTURE(type) (!V4L2_TYPE_IS_OUTPUT(type))

क्रमागत v4l2_tuner_type अणु
	V4L2_TUNER_RADIO	     = 1,
	V4L2_TUNER_ANALOG_TV	     = 2,
	V4L2_TUNER_DIGITAL_TV	     = 3,
	V4L2_TUNER_SDR               = 4,
	V4L2_TUNER_RF                = 5,
पूर्ण;

/* Deprecated, करो not use */
#घोषणा V4L2_TUNER_ADC  V4L2_TUNER_SDR

क्रमागत v4l2_memory अणु
	V4L2_MEMORY_MMAP             = 1,
	V4L2_MEMORY_USERPTR          = 2,
	V4L2_MEMORY_OVERLAY          = 3,
	V4L2_MEMORY_DMABUF           = 4,
पूर्ण;

/* see also http://vektor.theorem.ca/graphics/ycbcr/ */
क्रमागत v4l2_colorspace अणु
	/*
	 * Default colorspace, i.e. let the driver figure it out.
	 * Can only be used with video capture.
	 */
	V4L2_COLORSPACE_DEFAULT       = 0,

	/* SMPTE 170M: used क्रम broadcast NTSC/PAL SDTV */
	V4L2_COLORSPACE_SMPTE170M     = 1,

	/* Obsolete pre-1998 SMPTE 240M HDTV standard, superseded by Rec 709 */
	V4L2_COLORSPACE_SMPTE240M     = 2,

	/* Rec.709: used क्रम HDTV */
	V4L2_COLORSPACE_REC709        = 3,

	/*
	 * Deprecated, करो not use. No driver will ever वापस this. This was
	 * based on a misunderstanding of the bt878 datasheet.
	 */
	V4L2_COLORSPACE_BT878         = 4,

	/*
	 * NTSC 1953 colorspace. This only makes sense when dealing with
	 * really, really old NTSC recordings. Superseded by SMPTE 170M.
	 */
	V4L2_COLORSPACE_470_SYSTEM_M  = 5,

	/*
	 * EBU Tech 3213 PAL/SECAM colorspace.
	 */
	V4L2_COLORSPACE_470_SYSTEM_BG = 6,

	/*
	 * Effectively लघुhand क्रम V4L2_COLORSPACE_SRGB, V4L2_YCBCR_ENC_601
	 * and V4L2_QUANTIZATION_FULL_RANGE. To be used क्रम (Motion-)JPEG.
	 */
	V4L2_COLORSPACE_JPEG          = 7,

	/* For RGB colorspaces such as produces by most webcams. */
	V4L2_COLORSPACE_SRGB          = 8,

	/* opRGB colorspace */
	V4L2_COLORSPACE_OPRGB         = 9,

	/* BT.2020 colorspace, used क्रम UHDTV. */
	V4L2_COLORSPACE_BT2020        = 10,

	/* Raw colorspace: क्रम RAW unprocessed images */
	V4L2_COLORSPACE_RAW           = 11,

	/* DCI-P3 colorspace, used by cinema projectors */
	V4L2_COLORSPACE_DCI_P3        = 12,
पूर्ण;

/*
 * Determine how COLORSPACE_DEFAULT should map to a proper colorspace.
 * This depends on whether this is a SDTV image (use SMPTE 170M), an
 * HDTV image (use Rec. 709), or something अन्यथा (use sRGB).
 */
#घोषणा V4L2_MAP_COLORSPACE_DEFAULT(is_sdtv, is_hdtv) \
	((is_sdtv) ? V4L2_COLORSPACE_SMPTE170M : \
	 ((is_hdtv) ? V4L2_COLORSPACE_REC709 : V4L2_COLORSPACE_SRGB))

क्रमागत v4l2_xfer_func अणु
	/*
	 * Mapping of V4L2_XFER_FUNC_DEFAULT to actual transfer functions
	 * क्रम the various colorspaces:
	 *
	 * V4L2_COLORSPACE_SMPTE170M, V4L2_COLORSPACE_470_SYSTEM_M,
	 * V4L2_COLORSPACE_470_SYSTEM_BG, V4L2_COLORSPACE_REC709 and
	 * V4L2_COLORSPACE_BT2020: V4L2_XFER_FUNC_709
	 *
	 * V4L2_COLORSPACE_SRGB, V4L2_COLORSPACE_JPEG: V4L2_XFER_FUNC_SRGB
	 *
	 * V4L2_COLORSPACE_OPRGB: V4L2_XFER_FUNC_OPRGB
	 *
	 * V4L2_COLORSPACE_SMPTE240M: V4L2_XFER_FUNC_SMPTE240M
	 *
	 * V4L2_COLORSPACE_RAW: V4L2_XFER_FUNC_NONE
	 *
	 * V4L2_COLORSPACE_DCI_P3: V4L2_XFER_FUNC_DCI_P3
	 */
	V4L2_XFER_FUNC_DEFAULT     = 0,
	V4L2_XFER_FUNC_709         = 1,
	V4L2_XFER_FUNC_SRGB        = 2,
	V4L2_XFER_FUNC_OPRGB       = 3,
	V4L2_XFER_FUNC_SMPTE240M   = 4,
	V4L2_XFER_FUNC_NONE        = 5,
	V4L2_XFER_FUNC_DCI_P3      = 6,
	V4L2_XFER_FUNC_SMPTE2084   = 7,
पूर्ण;

/*
 * Determine how XFER_FUNC_DEFAULT should map to a proper transfer function.
 * This depends on the colorspace.
 */
#घोषणा V4L2_MAP_XFER_FUNC_DEFAULT(colsp) \
	((colsp) == V4L2_COLORSPACE_OPRGB ? V4L2_XFER_FUNC_OPRGB : \
	 ((colsp) == V4L2_COLORSPACE_SMPTE240M ? V4L2_XFER_FUNC_SMPTE240M : \
	  ((colsp) == V4L2_COLORSPACE_DCI_P3 ? V4L2_XFER_FUNC_DCI_P3 : \
	   ((colsp) == V4L2_COLORSPACE_RAW ? V4L2_XFER_FUNC_NONE : \
	    ((colsp) == V4L2_COLORSPACE_SRGB || (colsp) == V4L2_COLORSPACE_JPEG ? \
	     V4L2_XFER_FUNC_SRGB : V4L2_XFER_FUNC_709)))))

क्रमागत v4l2_ycbcr_encoding अणु
	/*
	 * Mapping of V4L2_YCBCR_ENC_DEFAULT to actual encodings क्रम the
	 * various colorspaces:
	 *
	 * V4L2_COLORSPACE_SMPTE170M, V4L2_COLORSPACE_470_SYSTEM_M,
	 * V4L2_COLORSPACE_470_SYSTEM_BG, V4L2_COLORSPACE_SRGB,
	 * V4L2_COLORSPACE_OPRGB and V4L2_COLORSPACE_JPEG: V4L2_YCBCR_ENC_601
	 *
	 * V4L2_COLORSPACE_REC709 and V4L2_COLORSPACE_DCI_P3: V4L2_YCBCR_ENC_709
	 *
	 * V4L2_COLORSPACE_BT2020: V4L2_YCBCR_ENC_BT2020
	 *
	 * V4L2_COLORSPACE_SMPTE240M: V4L2_YCBCR_ENC_SMPTE240M
	 */
	V4L2_YCBCR_ENC_DEFAULT        = 0,

	/* ITU-R 601 -- SDTV */
	V4L2_YCBCR_ENC_601            = 1,

	/* Rec. 709 -- HDTV */
	V4L2_YCBCR_ENC_709            = 2,

	/* ITU-R 601/EN 61966-2-4 Extended Gamut -- SDTV */
	V4L2_YCBCR_ENC_XV601          = 3,

	/* Rec. 709/EN 61966-2-4 Extended Gamut -- HDTV */
	V4L2_YCBCR_ENC_XV709          = 4,

#अगर_अघोषित __KERNEL__
	/*
	 * sYCC (Y'CbCr encoding of sRGB), identical to ENC_601. It was added
	 * originally due to a misunderstanding of the sYCC standard. It should
	 * not be used, instead use V4L2_YCBCR_ENC_601.
	 */
	V4L2_YCBCR_ENC_SYCC           = 5,
#पूर्ण_अगर

	/* BT.2020 Non-स्थिरant Luminance Y'CbCr */
	V4L2_YCBCR_ENC_BT2020         = 6,

	/* BT.2020 Constant Luminance Y'CbcCrc */
	V4L2_YCBCR_ENC_BT2020_CONST_LUM = 7,

	/* SMPTE 240M -- Obsolete HDTV */
	V4L2_YCBCR_ENC_SMPTE240M      = 8,
पूर्ण;

/*
 * क्रमागत v4l2_hsv_encoding values should not collide with the ones from
 * क्रमागत v4l2_ycbcr_encoding.
 */
क्रमागत v4l2_hsv_encoding अणु

	/* Hue mapped to 0 - 179 */
	V4L2_HSV_ENC_180		= 128,

	/* Hue mapped to 0-255 */
	V4L2_HSV_ENC_256		= 129,
पूर्ण;

/*
 * Determine how YCBCR_ENC_DEFAULT should map to a proper Y'CbCr encoding.
 * This depends on the colorspace.
 */
#घोषणा V4L2_MAP_YCBCR_ENC_DEFAULT(colsp) \
	(((colsp) == V4L2_COLORSPACE_REC709 || \
	  (colsp) == V4L2_COLORSPACE_DCI_P3) ? V4L2_YCBCR_ENC_709 : \
	 ((colsp) == V4L2_COLORSPACE_BT2020 ? V4L2_YCBCR_ENC_BT2020 : \
	  ((colsp) == V4L2_COLORSPACE_SMPTE240M ? V4L2_YCBCR_ENC_SMPTE240M : \
	   V4L2_YCBCR_ENC_601)))

क्रमागत v4l2_quantization अणु
	/*
	 * The शेष क्रम R'G'B' quantization is always full range.
	 * For Y'CbCr the quantization is always limited range, except
	 * क्रम COLORSPACE_JPEG: this is full range.
	 */
	V4L2_QUANTIZATION_DEFAULT     = 0,
	V4L2_QUANTIZATION_FULL_RANGE  = 1,
	V4L2_QUANTIZATION_LIM_RANGE   = 2,
पूर्ण;

/*
 * Determine how QUANTIZATION_DEFAULT should map to a proper quantization.
 * This depends on whether the image is RGB or not, the colorspace.
 * The Y'CbCr encoding is not used anymore, but is still there क्रम backwards
 * compatibility.
 */
#घोषणा V4L2_MAP_QUANTIZATION_DEFAULT(is_rgb_or_hsv, colsp, ycbcr_enc) \
	(((is_rgb_or_hsv) || (colsp) == V4L2_COLORSPACE_JPEG) ? \
	 V4L2_QUANTIZATION_FULL_RANGE : V4L2_QUANTIZATION_LIM_RANGE)

/*
 * Deprecated names क्रम opRGB colorspace (IEC 61966-2-5)
 *
 * WARNING: Please करोn't use these deprecated defines in your code, as
 * there is a chance we have to हटाओ them in the future.
 */
#अगर_अघोषित __KERNEL__
#घोषणा V4L2_COLORSPACE_ADOBERGB V4L2_COLORSPACE_OPRGB
#घोषणा V4L2_XFER_FUNC_ADOBERGB  V4L2_XFER_FUNC_OPRGB
#पूर्ण_अगर

क्रमागत v4l2_priority अणु
	V4L2_PRIORITY_UNSET       = 0,  /* not initialized */
	V4L2_PRIORITY_BACKGROUND  = 1,
	V4L2_PRIORITY_INTERACTIVE = 2,
	V4L2_PRIORITY_RECORD      = 3,
	V4L2_PRIORITY_DEFAULT     = V4L2_PRIORITY_INTERACTIVE,
पूर्ण;

काष्ठा v4l2_rect अणु
	__s32   left;
	__s32   top;
	__u32   width;
	__u32   height;
पूर्ण;

काष्ठा v4l2_fract अणु
	__u32   numerator;
	__u32   denominator;
पूर्ण;

काष्ठा v4l2_area अणु
	__u32   width;
	__u32   height;
पूर्ण;

/**
  * काष्ठा v4l2_capability - Describes V4L2 device caps वापसed by VIDIOC_QUERYCAP
  *
  * @driver:	   name of the driver module (e.g. "bttv")
  * @card:	   name of the card (e.g. "Hauppauge WinTV")
  * @bus_info:	   name of the bus (e.g. "PCI:" + pci_name(pci_dev) )
  * @version:	   KERNEL_VERSION
  * @capabilities: capabilities of the physical device as a whole
  * @device_caps:  capabilities accessed via this particular device (node)
  * @reserved:	   reserved fields क्रम future extensions
  */
काष्ठा v4l2_capability अणु
	__u8	driver[16];
	__u8	card[32];
	__u8	bus_info[32];
	__u32   version;
	__u32	capabilities;
	__u32	device_caps;
	__u32	reserved[3];
पूर्ण;

/* Values क्रम 'capabilities' field */
#घोषणा V4L2_CAP_VIDEO_CAPTURE		0x00000001  /* Is a video capture device */
#घोषणा V4L2_CAP_VIDEO_OUTPUT		0x00000002  /* Is a video output device */
#घोषणा V4L2_CAP_VIDEO_OVERLAY		0x00000004  /* Can करो video overlay */
#घोषणा V4L2_CAP_VBI_CAPTURE		0x00000010  /* Is a raw VBI capture device */
#घोषणा V4L2_CAP_VBI_OUTPUT		0x00000020  /* Is a raw VBI output device */
#घोषणा V4L2_CAP_SLICED_VBI_CAPTURE	0x00000040  /* Is a sliced VBI capture device */
#घोषणा V4L2_CAP_SLICED_VBI_OUTPUT	0x00000080  /* Is a sliced VBI output device */
#घोषणा V4L2_CAP_RDS_CAPTURE		0x00000100  /* RDS data capture */
#घोषणा V4L2_CAP_VIDEO_OUTPUT_OVERLAY	0x00000200  /* Can करो video output overlay */
#घोषणा V4L2_CAP_HW_FREQ_SEEK		0x00000400  /* Can करो hardware frequency seek  */
#घोषणा V4L2_CAP_RDS_OUTPUT		0x00000800  /* Is an RDS encoder */

/* Is a video capture device that supports multiplanar क्रमmats */
#घोषणा V4L2_CAP_VIDEO_CAPTURE_MPLANE	0x00001000
/* Is a video output device that supports multiplanar क्रमmats */
#घोषणा V4L2_CAP_VIDEO_OUTPUT_MPLANE	0x00002000
/* Is a video mem-to-mem device that supports multiplanar क्रमmats */
#घोषणा V4L2_CAP_VIDEO_M2M_MPLANE	0x00004000
/* Is a video mem-to-mem device */
#घोषणा V4L2_CAP_VIDEO_M2M		0x00008000

#घोषणा V4L2_CAP_TUNER			0x00010000  /* has a tuner */
#घोषणा V4L2_CAP_AUDIO			0x00020000  /* has audio support */
#घोषणा V4L2_CAP_RADIO			0x00040000  /* is a radio device */
#घोषणा V4L2_CAP_MODULATOR		0x00080000  /* has a modulator */

#घोषणा V4L2_CAP_SDR_CAPTURE		0x00100000  /* Is a SDR capture device */
#घोषणा V4L2_CAP_EXT_PIX_FORMAT		0x00200000  /* Supports the extended pixel क्रमmat */
#घोषणा V4L2_CAP_SDR_OUTPUT		0x00400000  /* Is a SDR output device */
#घोषणा V4L2_CAP_META_CAPTURE		0x00800000  /* Is a metadata capture device */

#घोषणा V4L2_CAP_READWRITE              0x01000000  /* पढ़ो/ग_लिखो प्रणालीcalls */
#घोषणा V4L2_CAP_ASYNCIO                0x02000000  /* async I/O */
#घोषणा V4L2_CAP_STREAMING              0x04000000  /* streaming I/O ioctls */
#घोषणा V4L2_CAP_META_OUTPUT		0x08000000  /* Is a metadata output device */

#घोषणा V4L2_CAP_TOUCH                  0x10000000  /* Is a touch device */

#घोषणा V4L2_CAP_IO_MC			0x20000000  /* Is input/output controlled by the media controller */

#घोषणा V4L2_CAP_DEVICE_CAPS            0x80000000  /* sets device capabilities field */

/*
 *	V I D E O   I M A G E   F O R M A T
 */
काष्ठा v4l2_pix_क्रमmat अणु
	__u32			width;
	__u32			height;
	__u32			pixelक्रमmat;
	__u32			field;		/* क्रमागत v4l2_field */
	__u32			bytesperline;	/* क्रम padding, zero अगर unused */
	__u32			sizeimage;
	__u32			colorspace;	/* क्रमागत v4l2_colorspace */
	__u32			priv;		/* निजी data, depends on pixelक्रमmat */
	__u32			flags;		/* क्रमmat flags (V4L2_PIX_FMT_FLAG_*) */
	जोड़ अणु
		/* क्रमागत v4l2_ycbcr_encoding */
		__u32			ycbcr_enc;
		/* क्रमागत v4l2_hsv_encoding */
		__u32			hsv_enc;
	पूर्ण;
	__u32			quantization;	/* क्रमागत v4l2_quantization */
	__u32			xfer_func;	/* क्रमागत v4l2_xfer_func */
पूर्ण;

/*      Pixel क्रमmat         FOURCC                          depth  Description  */

/* RGB क्रमmats (1 or 2 bytes per pixel) */
#घोषणा V4L2_PIX_FMT_RGB332  v4l2_fourcc('R', 'G', 'B', '1') /*  8  RGB-3-3-2     */
#घोषणा V4L2_PIX_FMT_RGB444  v4l2_fourcc('R', '4', '4', '4') /* 16  xxxxrrrr ggggbbbb */
#घोषणा V4L2_PIX_FMT_ARGB444 v4l2_fourcc('A', 'R', '1', '2') /* 16  aaaarrrr ggggbbbb */
#घोषणा V4L2_PIX_FMT_XRGB444 v4l2_fourcc('X', 'R', '1', '2') /* 16  xxxxrrrr ggggbbbb */
#घोषणा V4L2_PIX_FMT_RGBA444 v4l2_fourcc('R', 'A', '1', '2') /* 16  rrrrgggg bbbbaaaa */
#घोषणा V4L2_PIX_FMT_RGBX444 v4l2_fourcc('R', 'X', '1', '2') /* 16  rrrrgggg bbbbxxxx */
#घोषणा V4L2_PIX_FMT_ABGR444 v4l2_fourcc('A', 'B', '1', '2') /* 16  aaaabbbb ggggrrrr */
#घोषणा V4L2_PIX_FMT_XBGR444 v4l2_fourcc('X', 'B', '1', '2') /* 16  xxxxbbbb ggggrrrr */
#घोषणा V4L2_PIX_FMT_BGRA444 v4l2_fourcc('G', 'A', '1', '2') /* 16  bbbbgggg rrrraaaa */
#घोषणा V4L2_PIX_FMT_BGRX444 v4l2_fourcc('B', 'X', '1', '2') /* 16  bbbbgggg rrrrxxxx */
#घोषणा V4L2_PIX_FMT_RGB555  v4l2_fourcc('R', 'G', 'B', 'O') /* 16  RGB-5-5-5     */
#घोषणा V4L2_PIX_FMT_ARGB555 v4l2_fourcc('A', 'R', '1', '5') /* 16  ARGB-1-5-5-5  */
#घोषणा V4L2_PIX_FMT_XRGB555 v4l2_fourcc('X', 'R', '1', '5') /* 16  XRGB-1-5-5-5  */
#घोषणा V4L2_PIX_FMT_RGBA555 v4l2_fourcc('R', 'A', '1', '5') /* 16  RGBA-5-5-5-1  */
#घोषणा V4L2_PIX_FMT_RGBX555 v4l2_fourcc('R', 'X', '1', '5') /* 16  RGBX-5-5-5-1  */
#घोषणा V4L2_PIX_FMT_ABGR555 v4l2_fourcc('A', 'B', '1', '5') /* 16  ABGR-1-5-5-5  */
#घोषणा V4L2_PIX_FMT_XBGR555 v4l2_fourcc('X', 'B', '1', '5') /* 16  XBGR-1-5-5-5  */
#घोषणा V4L2_PIX_FMT_BGRA555 v4l2_fourcc('B', 'A', '1', '5') /* 16  BGRA-5-5-5-1  */
#घोषणा V4L2_PIX_FMT_BGRX555 v4l2_fourcc('B', 'X', '1', '5') /* 16  BGRX-5-5-5-1  */
#घोषणा V4L2_PIX_FMT_RGB565  v4l2_fourcc('R', 'G', 'B', 'P') /* 16  RGB-5-6-5     */
#घोषणा V4L2_PIX_FMT_RGB555X v4l2_fourcc('R', 'G', 'B', 'Q') /* 16  RGB-5-5-5 BE  */
#घोषणा V4L2_PIX_FMT_ARGB555X v4l2_fourcc_be('A', 'R', '1', '5') /* 16  ARGB-5-5-5 BE */
#घोषणा V4L2_PIX_FMT_XRGB555X v4l2_fourcc_be('X', 'R', '1', '5') /* 16  XRGB-5-5-5 BE */
#घोषणा V4L2_PIX_FMT_RGB565X v4l2_fourcc('R', 'G', 'B', 'R') /* 16  RGB-5-6-5 BE  */

/* RGB क्रमmats (3 or 4 bytes per pixel) */
#घोषणा V4L2_PIX_FMT_BGR666  v4l2_fourcc('B', 'G', 'R', 'H') /* 18  BGR-6-6-6	  */
#घोषणा V4L2_PIX_FMT_BGR24   v4l2_fourcc('B', 'G', 'R', '3') /* 24  BGR-8-8-8     */
#घोषणा V4L2_PIX_FMT_RGB24   v4l2_fourcc('R', 'G', 'B', '3') /* 24  RGB-8-8-8     */
#घोषणा V4L2_PIX_FMT_BGR32   v4l2_fourcc('B', 'G', 'R', '4') /* 32  BGR-8-8-8-8   */
#घोषणा V4L2_PIX_FMT_ABGR32  v4l2_fourcc('A', 'R', '2', '4') /* 32  BGRA-8-8-8-8  */
#घोषणा V4L2_PIX_FMT_XBGR32  v4l2_fourcc('X', 'R', '2', '4') /* 32  BGRX-8-8-8-8  */
#घोषणा V4L2_PIX_FMT_BGRA32  v4l2_fourcc('R', 'A', '2', '4') /* 32  ABGR-8-8-8-8  */
#घोषणा V4L2_PIX_FMT_BGRX32  v4l2_fourcc('R', 'X', '2', '4') /* 32  XBGR-8-8-8-8  */
#घोषणा V4L2_PIX_FMT_RGB32   v4l2_fourcc('R', 'G', 'B', '4') /* 32  RGB-8-8-8-8   */
#घोषणा V4L2_PIX_FMT_RGBA32  v4l2_fourcc('A', 'B', '2', '4') /* 32  RGBA-8-8-8-8  */
#घोषणा V4L2_PIX_FMT_RGBX32  v4l2_fourcc('X', 'B', '2', '4') /* 32  RGBX-8-8-8-8  */
#घोषणा V4L2_PIX_FMT_ARGB32  v4l2_fourcc('B', 'A', '2', '4') /* 32  ARGB-8-8-8-8  */
#घोषणा V4L2_PIX_FMT_XRGB32  v4l2_fourcc('B', 'X', '2', '4') /* 32  XRGB-8-8-8-8  */

/* Grey क्रमmats */
#घोषणा V4L2_PIX_FMT_GREY    v4l2_fourcc('G', 'R', 'E', 'Y') /*  8  Greyscale     */
#घोषणा V4L2_PIX_FMT_Y4      v4l2_fourcc('Y', '0', '4', ' ') /*  4  Greyscale     */
#घोषणा V4L2_PIX_FMT_Y6      v4l2_fourcc('Y', '0', '6', ' ') /*  6  Greyscale     */
#घोषणा V4L2_PIX_FMT_Y10     v4l2_fourcc('Y', '1', '0', ' ') /* 10  Greyscale     */
#घोषणा V4L2_PIX_FMT_Y12     v4l2_fourcc('Y', '1', '2', ' ') /* 12  Greyscale     */
#घोषणा V4L2_PIX_FMT_Y14     v4l2_fourcc('Y', '1', '4', ' ') /* 14  Greyscale     */
#घोषणा V4L2_PIX_FMT_Y16     v4l2_fourcc('Y', '1', '6', ' ') /* 16  Greyscale     */
#घोषणा V4L2_PIX_FMT_Y16_BE  v4l2_fourcc_be('Y', '1', '6', ' ') /* 16  Greyscale BE  */

/* Grey bit-packed क्रमmats */
#घोषणा V4L2_PIX_FMT_Y10BPACK    v4l2_fourcc('Y', '1', '0', 'B') /* 10  Greyscale bit-packed */
#घोषणा V4L2_PIX_FMT_Y10P    v4l2_fourcc('Y', '1', '0', 'P') /* 10  Greyscale, MIPI RAW10 packed */

/* Palette क्रमmats */
#घोषणा V4L2_PIX_FMT_PAL8    v4l2_fourcc('P', 'A', 'L', '8') /*  8  8-bit palette */

/* Chrominance क्रमmats */
#घोषणा V4L2_PIX_FMT_UV8     v4l2_fourcc('U', 'V', '8', ' ') /*  8  UV 4:4 */

/* Luminance+Chrominance क्रमmats */
#घोषणा V4L2_PIX_FMT_YUYV    v4l2_fourcc('Y', 'U', 'Y', 'V') /* 16  YUV 4:2:2     */
#घोषणा V4L2_PIX_FMT_YYUV    v4l2_fourcc('Y', 'Y', 'U', 'V') /* 16  YUV 4:2:2     */
#घोषणा V4L2_PIX_FMT_YVYU    v4l2_fourcc('Y', 'V', 'Y', 'U') /* 16 YVU 4:2:2 */
#घोषणा V4L2_PIX_FMT_UYVY    v4l2_fourcc('U', 'Y', 'V', 'Y') /* 16  YUV 4:2:2     */
#घोषणा V4L2_PIX_FMT_VYUY    v4l2_fourcc('V', 'Y', 'U', 'Y') /* 16  YUV 4:2:2     */
#घोषणा V4L2_PIX_FMT_Y41P    v4l2_fourcc('Y', '4', '1', 'P') /* 12  YUV 4:1:1     */
#घोषणा V4L2_PIX_FMT_YUV444  v4l2_fourcc('Y', '4', '4', '4') /* 16  xxxxyyyy uuuuvvvv */
#घोषणा V4L2_PIX_FMT_YUV555  v4l2_fourcc('Y', 'U', 'V', 'O') /* 16  YUV-5-5-5     */
#घोषणा V4L2_PIX_FMT_YUV565  v4l2_fourcc('Y', 'U', 'V', 'P') /* 16  YUV-5-6-5     */
#घोषणा V4L2_PIX_FMT_YUV24   v4l2_fourcc('Y', 'U', 'V', '3') /* 24  YUV-8-8-8     */
#घोषणा V4L2_PIX_FMT_YUV32   v4l2_fourcc('Y', 'U', 'V', '4') /* 32  YUV-8-8-8-8   */
#घोषणा V4L2_PIX_FMT_AYUV32  v4l2_fourcc('A', 'Y', 'U', 'V') /* 32  AYUV-8-8-8-8  */
#घोषणा V4L2_PIX_FMT_XYUV32  v4l2_fourcc('X', 'Y', 'U', 'V') /* 32  XYUV-8-8-8-8  */
#घोषणा V4L2_PIX_FMT_VUYA32  v4l2_fourcc('V', 'U', 'Y', 'A') /* 32  VUYA-8-8-8-8  */
#घोषणा V4L2_PIX_FMT_VUYX32  v4l2_fourcc('V', 'U', 'Y', 'X') /* 32  VUYX-8-8-8-8  */
#घोषणा V4L2_PIX_FMT_M420    v4l2_fourcc('M', '4', '2', '0') /* 12  YUV 4:2:0 2 lines y, 1 line uv पूर्णांकerleaved */

/* two planes -- one Y, one Cr + Cb पूर्णांकerleaved  */
#घोषणा V4L2_PIX_FMT_NV12    v4l2_fourcc('N', 'V', '1', '2') /* 12  Y/CbCr 4:2:0  */
#घोषणा V4L2_PIX_FMT_NV21    v4l2_fourcc('N', 'V', '2', '1') /* 12  Y/CrCb 4:2:0  */
#घोषणा V4L2_PIX_FMT_NV16    v4l2_fourcc('N', 'V', '1', '6') /* 16  Y/CbCr 4:2:2  */
#घोषणा V4L2_PIX_FMT_NV61    v4l2_fourcc('N', 'V', '6', '1') /* 16  Y/CrCb 4:2:2  */
#घोषणा V4L2_PIX_FMT_NV24    v4l2_fourcc('N', 'V', '2', '4') /* 24  Y/CbCr 4:4:4  */
#घोषणा V4L2_PIX_FMT_NV42    v4l2_fourcc('N', 'V', '4', '2') /* 24  Y/CrCb 4:4:4  */
#घोषणा V4L2_PIX_FMT_HM12    v4l2_fourcc('H', 'M', '1', '2') /*  8  YUV 4:2:0 16x16 macroblocks */

/* two non contiguous planes - one Y, one Cr + Cb पूर्णांकerleaved  */
#घोषणा V4L2_PIX_FMT_NV12M   v4l2_fourcc('N', 'M', '1', '2') /* 12  Y/CbCr 4:2:0  */
#घोषणा V4L2_PIX_FMT_NV21M   v4l2_fourcc('N', 'M', '2', '1') /* 21  Y/CrCb 4:2:0  */
#घोषणा V4L2_PIX_FMT_NV16M   v4l2_fourcc('N', 'M', '1', '6') /* 16  Y/CbCr 4:2:2  */
#घोषणा V4L2_PIX_FMT_NV61M   v4l2_fourcc('N', 'M', '6', '1') /* 16  Y/CrCb 4:2:2  */
#घोषणा V4L2_PIX_FMT_NV12MT  v4l2_fourcc('T', 'M', '1', '2') /* 12  Y/CbCr 4:2:0 64x32 macroblocks */
#घोषणा V4L2_PIX_FMT_NV12MT_16X16 v4l2_fourcc('V', 'M', '1', '2') /* 12  Y/CbCr 4:2:0 16x16 macroblocks */

/* three planes - Y Cb, Cr */
#घोषणा V4L2_PIX_FMT_YUV410  v4l2_fourcc('Y', 'U', 'V', '9') /*  9  YUV 4:1:0     */
#घोषणा V4L2_PIX_FMT_YVU410  v4l2_fourcc('Y', 'V', 'U', '9') /*  9  YVU 4:1:0     */
#घोषणा V4L2_PIX_FMT_YUV411P v4l2_fourcc('4', '1', '1', 'P') /* 12  YVU411 planar */
#घोषणा V4L2_PIX_FMT_YUV420  v4l2_fourcc('Y', 'U', '1', '2') /* 12  YUV 4:2:0     */
#घोषणा V4L2_PIX_FMT_YVU420  v4l2_fourcc('Y', 'V', '1', '2') /* 12  YVU 4:2:0     */
#घोषणा V4L2_PIX_FMT_YUV422P v4l2_fourcc('4', '2', '2', 'P') /* 16  YVU422 planar */

/* three non contiguous planes - Y, Cb, Cr */
#घोषणा V4L2_PIX_FMT_YUV420M v4l2_fourcc('Y', 'M', '1', '2') /* 12  YUV420 planar */
#घोषणा V4L2_PIX_FMT_YVU420M v4l2_fourcc('Y', 'M', '2', '1') /* 12  YVU420 planar */
#घोषणा V4L2_PIX_FMT_YUV422M v4l2_fourcc('Y', 'M', '1', '6') /* 16  YUV422 planar */
#घोषणा V4L2_PIX_FMT_YVU422M v4l2_fourcc('Y', 'M', '6', '1') /* 16  YVU422 planar */
#घोषणा V4L2_PIX_FMT_YUV444M v4l2_fourcc('Y', 'M', '2', '4') /* 24  YUV444 planar */
#घोषणा V4L2_PIX_FMT_YVU444M v4l2_fourcc('Y', 'M', '4', '2') /* 24  YVU444 planar */

/* Bayer क्रमmats - see http://www.siliconimaging.com/RGB%20Bayer.hपंचांग */
#घोषणा V4L2_PIX_FMT_SBGGR8  v4l2_fourcc('B', 'A', '8', '1') /*  8  BGBG.. GRGR.. */
#घोषणा V4L2_PIX_FMT_SGBRG8  v4l2_fourcc('G', 'B', 'R', 'G') /*  8  GBGB.. RGRG.. */
#घोषणा V4L2_PIX_FMT_SGRBG8  v4l2_fourcc('G', 'R', 'B', 'G') /*  8  GRGR.. BGBG.. */
#घोषणा V4L2_PIX_FMT_SRGGB8  v4l2_fourcc('R', 'G', 'G', 'B') /*  8  RGRG.. GBGB.. */
#घोषणा V4L2_PIX_FMT_SBGGR10 v4l2_fourcc('B', 'G', '1', '0') /* 10  BGBG.. GRGR.. */
#घोषणा V4L2_PIX_FMT_SGBRG10 v4l2_fourcc('G', 'B', '1', '0') /* 10  GBGB.. RGRG.. */
#घोषणा V4L2_PIX_FMT_SGRBG10 v4l2_fourcc('B', 'A', '1', '0') /* 10  GRGR.. BGBG.. */
#घोषणा V4L2_PIX_FMT_SRGGB10 v4l2_fourcc('R', 'G', '1', '0') /* 10  RGRG.. GBGB.. */
	/* 10bit raw bayer packed, 5 bytes क्रम every 4 pixels */
#घोषणा V4L2_PIX_FMT_SBGGR10P v4l2_fourcc('p', 'B', 'A', 'A')
#घोषणा V4L2_PIX_FMT_SGBRG10P v4l2_fourcc('p', 'G', 'A', 'A')
#घोषणा V4L2_PIX_FMT_SGRBG10P v4l2_fourcc('p', 'g', 'A', 'A')
#घोषणा V4L2_PIX_FMT_SRGGB10P v4l2_fourcc('p', 'R', 'A', 'A')
	/* 10bit raw bayer a-law compressed to 8 bits */
#घोषणा V4L2_PIX_FMT_SBGGR10ALAW8 v4l2_fourcc('a', 'B', 'A', '8')
#घोषणा V4L2_PIX_FMT_SGBRG10ALAW8 v4l2_fourcc('a', 'G', 'A', '8')
#घोषणा V4L2_PIX_FMT_SGRBG10ALAW8 v4l2_fourcc('a', 'g', 'A', '8')
#घोषणा V4L2_PIX_FMT_SRGGB10ALAW8 v4l2_fourcc('a', 'R', 'A', '8')
	/* 10bit raw bayer DPCM compressed to 8 bits */
#घोषणा V4L2_PIX_FMT_SBGGR10DPCM8 v4l2_fourcc('b', 'B', 'A', '8')
#घोषणा V4L2_PIX_FMT_SGBRG10DPCM8 v4l2_fourcc('b', 'G', 'A', '8')
#घोषणा V4L2_PIX_FMT_SGRBG10DPCM8 v4l2_fourcc('B', 'D', '1', '0')
#घोषणा V4L2_PIX_FMT_SRGGB10DPCM8 v4l2_fourcc('b', 'R', 'A', '8')
#घोषणा V4L2_PIX_FMT_SBGGR12 v4l2_fourcc('B', 'G', '1', '2') /* 12  BGBG.. GRGR.. */
#घोषणा V4L2_PIX_FMT_SGBRG12 v4l2_fourcc('G', 'B', '1', '2') /* 12  GBGB.. RGRG.. */
#घोषणा V4L2_PIX_FMT_SGRBG12 v4l2_fourcc('B', 'A', '1', '2') /* 12  GRGR.. BGBG.. */
#घोषणा V4L2_PIX_FMT_SRGGB12 v4l2_fourcc('R', 'G', '1', '2') /* 12  RGRG.. GBGB.. */
	/* 12bit raw bayer packed, 6 bytes क्रम every 4 pixels */
#घोषणा V4L2_PIX_FMT_SBGGR12P v4l2_fourcc('p', 'B', 'C', 'C')
#घोषणा V4L2_PIX_FMT_SGBRG12P v4l2_fourcc('p', 'G', 'C', 'C')
#घोषणा V4L2_PIX_FMT_SGRBG12P v4l2_fourcc('p', 'g', 'C', 'C')
#घोषणा V4L2_PIX_FMT_SRGGB12P v4l2_fourcc('p', 'R', 'C', 'C')
#घोषणा V4L2_PIX_FMT_SBGGR14 v4l2_fourcc('B', 'G', '1', '4') /* 14  BGBG.. GRGR.. */
#घोषणा V4L2_PIX_FMT_SGBRG14 v4l2_fourcc('G', 'B', '1', '4') /* 14  GBGB.. RGRG.. */
#घोषणा V4L2_PIX_FMT_SGRBG14 v4l2_fourcc('G', 'R', '1', '4') /* 14  GRGR.. BGBG.. */
#घोषणा V4L2_PIX_FMT_SRGGB14 v4l2_fourcc('R', 'G', '1', '4') /* 14  RGRG.. GBGB.. */
	/* 14bit raw bayer packed, 7 bytes क्रम every 4 pixels */
#घोषणा V4L2_PIX_FMT_SBGGR14P v4l2_fourcc('p', 'B', 'E', 'E')
#घोषणा V4L2_PIX_FMT_SGBRG14P v4l2_fourcc('p', 'G', 'E', 'E')
#घोषणा V4L2_PIX_FMT_SGRBG14P v4l2_fourcc('p', 'g', 'E', 'E')
#घोषणा V4L2_PIX_FMT_SRGGB14P v4l2_fourcc('p', 'R', 'E', 'E')
#घोषणा V4L2_PIX_FMT_SBGGR16 v4l2_fourcc('B', 'Y', 'R', '2') /* 16  BGBG.. GRGR.. */
#घोषणा V4L2_PIX_FMT_SGBRG16 v4l2_fourcc('G', 'B', '1', '6') /* 16  GBGB.. RGRG.. */
#घोषणा V4L2_PIX_FMT_SGRBG16 v4l2_fourcc('G', 'R', '1', '6') /* 16  GRGR.. BGBG.. */
#घोषणा V4L2_PIX_FMT_SRGGB16 v4l2_fourcc('R', 'G', '1', '6') /* 16  RGRG.. GBGB.. */

/* HSV क्रमmats */
#घोषणा V4L2_PIX_FMT_HSV24 v4l2_fourcc('H', 'S', 'V', '3')
#घोषणा V4L2_PIX_FMT_HSV32 v4l2_fourcc('H', 'S', 'V', '4')

/* compressed क्रमmats */
#घोषणा V4L2_PIX_FMT_MJPEG    v4l2_fourcc('M', 'J', 'P', 'G') /* Motion-JPEG   */
#घोषणा V4L2_PIX_FMT_JPEG     v4l2_fourcc('J', 'P', 'E', 'G') /* JFIF JPEG     */
#घोषणा V4L2_PIX_FMT_DV       v4l2_fourcc('d', 'v', 's', 'd') /* 1394          */
#घोषणा V4L2_PIX_FMT_MPEG     v4l2_fourcc('M', 'P', 'E', 'G') /* MPEG-1/2/4 Multiplexed */
#घोषणा V4L2_PIX_FMT_H264     v4l2_fourcc('H', '2', '6', '4') /* H264 with start codes */
#घोषणा V4L2_PIX_FMT_H264_NO_SC v4l2_fourcc('A', 'V', 'C', '1') /* H264 without start codes */
#घोषणा V4L2_PIX_FMT_H264_MVC v4l2_fourcc('M', '2', '6', '4') /* H264 MVC */
#घोषणा V4L2_PIX_FMT_H263     v4l2_fourcc('H', '2', '6', '3') /* H263          */
#घोषणा V4L2_PIX_FMT_MPEG1    v4l2_fourcc('M', 'P', 'G', '1') /* MPEG-1 ES     */
#घोषणा V4L2_PIX_FMT_MPEG2    v4l2_fourcc('M', 'P', 'G', '2') /* MPEG-2 ES     */
#घोषणा V4L2_PIX_FMT_MPEG2_SLICE v4l2_fourcc('M', 'G', '2', 'S') /* MPEG-2 parsed slice data */
#घोषणा V4L2_PIX_FMT_MPEG4    v4l2_fourcc('M', 'P', 'G', '4') /* MPEG-4 part 2 ES */
#घोषणा V4L2_PIX_FMT_XVID     v4l2_fourcc('X', 'V', 'I', 'D') /* Xvid           */
#घोषणा V4L2_PIX_FMT_VC1_ANNEX_G v4l2_fourcc('V', 'C', '1', 'G') /* SMPTE 421M Annex G compliant stream */
#घोषणा V4L2_PIX_FMT_VC1_ANNEX_L v4l2_fourcc('V', 'C', '1', 'L') /* SMPTE 421M Annex L compliant stream */
#घोषणा V4L2_PIX_FMT_VP8      v4l2_fourcc('V', 'P', '8', '0') /* VP8 */
#घोषणा V4L2_PIX_FMT_VP8_FRAME v4l2_fourcc('V', 'P', '8', 'F') /* VP8 parsed frame */
#घोषणा V4L2_PIX_FMT_VP9      v4l2_fourcc('V', 'P', '9', '0') /* VP9 */
#घोषणा V4L2_PIX_FMT_HEVC     v4l2_fourcc('H', 'E', 'V', 'C') /* HEVC aka H.265 */
#घोषणा V4L2_PIX_FMT_FWHT     v4l2_fourcc('F', 'W', 'H', 'T') /* Fast Walsh Hadamard Transक्रमm (vicodec) */
#घोषणा V4L2_PIX_FMT_FWHT_STATELESS     v4l2_fourcc('S', 'F', 'W', 'H') /* Stateless FWHT (vicodec) */
#घोषणा V4L2_PIX_FMT_H264_SLICE v4l2_fourcc('S', '2', '6', '4') /* H264 parsed slices */

/*  Venकरोr-specअगरic क्रमmats   */
#घोषणा V4L2_PIX_FMT_CPIA1    v4l2_fourcc('C', 'P', 'I', 'A') /* cpia1 YUV */
#घोषणा V4L2_PIX_FMT_WNVA     v4l2_fourcc('W', 'N', 'V', 'A') /* Winnov hw compress */
#घोषणा V4L2_PIX_FMT_SN9C10X  v4l2_fourcc('S', '9', '1', '0') /* SN9C10x compression */
#घोषणा V4L2_PIX_FMT_SN9C20X_I420 v4l2_fourcc('S', '9', '2', '0') /* SN9C20x YUV 4:2:0 */
#घोषणा V4L2_PIX_FMT_PWC1     v4l2_fourcc('P', 'W', 'C', '1') /* pwc older webcam */
#घोषणा V4L2_PIX_FMT_PWC2     v4l2_fourcc('P', 'W', 'C', '2') /* pwc newer webcam */
#घोषणा V4L2_PIX_FMT_ET61X251 v4l2_fourcc('E', '6', '2', '5') /* ET61X251 compression */
#घोषणा V4L2_PIX_FMT_SPCA501  v4l2_fourcc('S', '5', '0', '1') /* YUYV per line */
#घोषणा V4L2_PIX_FMT_SPCA505  v4l2_fourcc('S', '5', '0', '5') /* YYUV per line */
#घोषणा V4L2_PIX_FMT_SPCA508  v4l2_fourcc('S', '5', '0', '8') /* YUVY per line */
#घोषणा V4L2_PIX_FMT_SPCA561  v4l2_fourcc('S', '5', '6', '1') /* compressed GBRG bayer */
#घोषणा V4L2_PIX_FMT_PAC207   v4l2_fourcc('P', '2', '0', '7') /* compressed BGGR bayer */
#घोषणा V4L2_PIX_FMT_MR97310A v4l2_fourcc('M', '3', '1', '0') /* compressed BGGR bayer */
#घोषणा V4L2_PIX_FMT_JL2005BCD v4l2_fourcc('J', 'L', '2', '0') /* compressed RGGB bayer */
#घोषणा V4L2_PIX_FMT_SN9C2028 v4l2_fourcc('S', 'O', 'N', 'X') /* compressed GBRG bayer */
#घोषणा V4L2_PIX_FMT_SQ905C   v4l2_fourcc('9', '0', '5', 'C') /* compressed RGGB bayer */
#घोषणा V4L2_PIX_FMT_PJPG     v4l2_fourcc('P', 'J', 'P', 'G') /* Pixart 73xx JPEG */
#घोषणा V4L2_PIX_FMT_OV511    v4l2_fourcc('O', '5', '1', '1') /* ov511 JPEG */
#घोषणा V4L2_PIX_FMT_OV518    v4l2_fourcc('O', '5', '1', '8') /* ov518 JPEG */
#घोषणा V4L2_PIX_FMT_STV0680  v4l2_fourcc('S', '6', '8', '0') /* stv0680 bayer */
#घोषणा V4L2_PIX_FMT_TM6000   v4l2_fourcc('T', 'M', '6', '0') /* पंचांग5600/पंचांग60x0 */
#घोषणा V4L2_PIX_FMT_CIT_YYVYUY v4l2_fourcc('C', 'I', 'T', 'V') /* one line of Y then 1 line of VYUY */
#घोषणा V4L2_PIX_FMT_KONICA420  v4l2_fourcc('K', 'O', 'N', 'I') /* YUV420 planar in blocks of 256 pixels */
#घोषणा V4L2_PIX_FMT_JPGL	v4l2_fourcc('J', 'P', 'G', 'L') /* JPEG-Lite */
#घोषणा V4L2_PIX_FMT_SE401      v4l2_fourcc('S', '4', '0', '1') /* se401 janggu compressed rgb */
#घोषणा V4L2_PIX_FMT_S5C_UYVY_JPG v4l2_fourcc('S', '5', 'C', 'I') /* S5C73M3 पूर्णांकerleaved UYVY/JPEG */
#घोषणा V4L2_PIX_FMT_Y8I      v4l2_fourcc('Y', '8', 'I', ' ') /* Greyscale 8-bit L/R पूर्णांकerleaved */
#घोषणा V4L2_PIX_FMT_Y12I     v4l2_fourcc('Y', '1', '2', 'I') /* Greyscale 12-bit L/R पूर्णांकerleaved */
#घोषणा V4L2_PIX_FMT_Z16      v4l2_fourcc('Z', '1', '6', ' ') /* Depth data 16-bit */
#घोषणा V4L2_PIX_FMT_MT21C    v4l2_fourcc('M', 'T', '2', '1') /* Mediatek compressed block mode  */
#घोषणा V4L2_PIX_FMT_INZI     v4l2_fourcc('I', 'N', 'Z', 'I') /* Intel Planar Greyscale 10-bit and Depth 16-bit */
#घोषणा V4L2_PIX_FMT_SUNXI_TILED_NV12 v4l2_fourcc('S', 'T', '1', '2') /* Sunxi Tiled NV12 Format */
#घोषणा V4L2_PIX_FMT_CNF4     v4l2_fourcc('C', 'N', 'F', '4') /* Intel 4-bit packed depth confidence inक्रमmation */
#घोषणा V4L2_PIX_FMT_HI240    v4l2_fourcc('H', 'I', '2', '4') /* BTTV 8-bit dithered RGB */

/* 10bit raw bayer packed, 32 bytes क्रम every 25 pixels, last LSB 6 bits unused */
#घोषणा V4L2_PIX_FMT_IPU3_SBGGR10	v4l2_fourcc('i', 'p', '3', 'b') /* IPU3 packed 10-bit BGGR bayer */
#घोषणा V4L2_PIX_FMT_IPU3_SGBRG10	v4l2_fourcc('i', 'p', '3', 'g') /* IPU3 packed 10-bit GBRG bayer */
#घोषणा V4L2_PIX_FMT_IPU3_SGRBG10	v4l2_fourcc('i', 'p', '3', 'G') /* IPU3 packed 10-bit GRBG bayer */
#घोषणा V4L2_PIX_FMT_IPU3_SRGGB10	v4l2_fourcc('i', 'p', '3', 'r') /* IPU3 packed 10-bit RGGB bayer */

/* SDR क्रमmats - used only क्रम Software Defined Radio devices */
#घोषणा V4L2_SDR_FMT_CU8          v4l2_fourcc('C', 'U', '0', '8') /* IQ u8 */
#घोषणा V4L2_SDR_FMT_CU16LE       v4l2_fourcc('C', 'U', '1', '6') /* IQ u16le */
#घोषणा V4L2_SDR_FMT_CS8          v4l2_fourcc('C', 'S', '0', '8') /* complex s8 */
#घोषणा V4L2_SDR_FMT_CS14LE       v4l2_fourcc('C', 'S', '1', '4') /* complex s14le */
#घोषणा V4L2_SDR_FMT_RU12LE       v4l2_fourcc('R', 'U', '1', '2') /* real u12le */
#घोषणा V4L2_SDR_FMT_PCU16BE	  v4l2_fourcc('P', 'C', '1', '6') /* planar complex u16be */
#घोषणा V4L2_SDR_FMT_PCU18BE	  v4l2_fourcc('P', 'C', '1', '8') /* planar complex u18be */
#घोषणा V4L2_SDR_FMT_PCU20BE	  v4l2_fourcc('P', 'C', '2', '0') /* planar complex u20be */

/* Touch क्रमmats - used क्रम Touch devices */
#घोषणा V4L2_TCH_FMT_DELTA_TD16	v4l2_fourcc('T', 'D', '1', '6') /* 16-bit चिन्हित deltas */
#घोषणा V4L2_TCH_FMT_DELTA_TD08	v4l2_fourcc('T', 'D', '0', '8') /* 8-bit चिन्हित deltas */
#घोषणा V4L2_TCH_FMT_TU16	v4l2_fourcc('T', 'U', '1', '6') /* 16-bit अचिन्हित touch data */
#घोषणा V4L2_TCH_FMT_TU08	v4l2_fourcc('T', 'U', '0', '8') /* 8-bit अचिन्हित touch data */

/* Meta-data क्रमmats */
#घोषणा V4L2_META_FMT_VSP1_HGO    v4l2_fourcc('V', 'S', 'P', 'H') /* R-Car VSP1 1-D Histogram */
#घोषणा V4L2_META_FMT_VSP1_HGT    v4l2_fourcc('V', 'S', 'P', 'T') /* R-Car VSP1 2-D Histogram */
#घोषणा V4L2_META_FMT_UVC         v4l2_fourcc('U', 'V', 'C', 'H') /* UVC Payload Header metadata */
#घोषणा V4L2_META_FMT_D4XX        v4l2_fourcc('D', '4', 'X', 'X') /* D4XX Payload Header metadata */
#घोषणा V4L2_META_FMT_VIVID	  v4l2_fourcc('V', 'I', 'V', 'D') /* Vivid Metadata */

/* Venकरोr specअगरic - used क्रम RK_ISP1 camera sub-प्रणाली */
#घोषणा V4L2_META_FMT_RK_ISP1_PARAMS	v4l2_fourcc('R', 'K', '1', 'P') /* Rockchip ISP1 3A Parameters */
#घोषणा V4L2_META_FMT_RK_ISP1_STAT_3A	v4l2_fourcc('R', 'K', '1', 'S') /* Rockchip ISP1 3A Statistics */

/* priv field value to indicates that subsequent fields are valid. */
#घोषणा V4L2_PIX_FMT_PRIV_MAGIC		0xfeedcafe

/* Flags */
#घोषणा V4L2_PIX_FMT_FLAG_PREMUL_ALPHA	0x00000001
#घोषणा V4L2_PIX_FMT_FLAG_SET_CSC	0x00000002

/*
 *	F O R M A T   E N U M E R A T I O N
 */
काष्ठा v4l2_fmtdesc अणु
	__u32		    index;             /* Format number      */
	__u32		    type;              /* क्रमागत v4l2_buf_type */
	__u32               flags;
	__u8		    description[32];   /* Description string */
	__u32		    pixelक्रमmat;       /* Format fourcc      */
	__u32		    mbus_code;		/* Media bus code    */
	__u32		    reserved[3];
पूर्ण;

#घोषणा V4L2_FMT_FLAG_COMPRESSED		0x0001
#घोषणा V4L2_FMT_FLAG_EMULATED			0x0002
#घोषणा V4L2_FMT_FLAG_CONTINUOUS_BYTESTREAM	0x0004
#घोषणा V4L2_FMT_FLAG_DYN_RESOLUTION		0x0008
#घोषणा V4L2_FMT_FLAG_ENC_CAP_FRAME_INTERVAL	0x0010
#घोषणा V4L2_FMT_FLAG_CSC_COLORSPACE		0x0020
#घोषणा V4L2_FMT_FLAG_CSC_XFER_FUNC		0x0040
#घोषणा V4L2_FMT_FLAG_CSC_YCBCR_ENC		0x0080
#घोषणा V4L2_FMT_FLAG_CSC_HSV_ENC		V4L2_FMT_FLAG_CSC_YCBCR_ENC
#घोषणा V4L2_FMT_FLAG_CSC_QUANTIZATION		0x0100

	/* Frame Size and frame rate क्रमागतeration */
/*
 *	F R A M E   S I Z E   E N U M E R A T I O N
 */
क्रमागत v4l2_frmsizetypes अणु
	V4L2_FRMSIZE_TYPE_DISCRETE	= 1,
	V4L2_FRMSIZE_TYPE_CONTINUOUS	= 2,
	V4L2_FRMSIZE_TYPE_STEPWISE	= 3,
पूर्ण;

काष्ठा v4l2_frmsize_discrete अणु
	__u32			width;		/* Frame width [pixel] */
	__u32			height;		/* Frame height [pixel] */
पूर्ण;

काष्ठा v4l2_frmsize_stepwise अणु
	__u32			min_width;	/* Minimum frame width [pixel] */
	__u32			max_width;	/* Maximum frame width [pixel] */
	__u32			step_width;	/* Frame width step size [pixel] */
	__u32			min_height;	/* Minimum frame height [pixel] */
	__u32			max_height;	/* Maximum frame height [pixel] */
	__u32			step_height;	/* Frame height step size [pixel] */
पूर्ण;

काष्ठा v4l2_frmsizeक्रमागत अणु
	__u32			index;		/* Frame size number */
	__u32			pixel_क्रमmat;	/* Pixel क्रमmat */
	__u32			type;		/* Frame size type the device supports. */

	जोड़ अणु					/* Frame size */
		काष्ठा v4l2_frmsize_discrete	discrete;
		काष्ठा v4l2_frmsize_stepwise	stepwise;
	पूर्ण;

	__u32   reserved[2];			/* Reserved space क्रम future use */
पूर्ण;

/*
 *	F R A M E   R A T E   E N U M E R A T I O N
 */
क्रमागत v4l2_frmivaltypes अणु
	V4L2_FRMIVAL_TYPE_DISCRETE	= 1,
	V4L2_FRMIVAL_TYPE_CONTINUOUS	= 2,
	V4L2_FRMIVAL_TYPE_STEPWISE	= 3,
पूर्ण;

काष्ठा v4l2_frmival_stepwise अणु
	काष्ठा v4l2_fract	min;		/* Minimum frame पूर्णांकerval [s] */
	काष्ठा v4l2_fract	max;		/* Maximum frame पूर्णांकerval [s] */
	काष्ठा v4l2_fract	step;		/* Frame पूर्णांकerval step size [s] */
पूर्ण;

काष्ठा v4l2_frmivalक्रमागत अणु
	__u32			index;		/* Frame क्रमmat index */
	__u32			pixel_क्रमmat;	/* Pixel क्रमmat */
	__u32			width;		/* Frame width */
	__u32			height;		/* Frame height */
	__u32			type;		/* Frame पूर्णांकerval type the device supports. */

	जोड़ अणु					/* Frame पूर्णांकerval */
		काष्ठा v4l2_fract		discrete;
		काष्ठा v4l2_frmival_stepwise	stepwise;
	पूर्ण;

	__u32	reserved[2];			/* Reserved space क्रम future use */
पूर्ण;

/*
 *	T I M E C O D E
 */
काष्ठा v4l2_समयcode अणु
	__u32	type;
	__u32	flags;
	__u8	frames;
	__u8	seconds;
	__u8	minutes;
	__u8	hours;
	__u8	userbits[4];
पूर्ण;

/*  Type  */
#घोषणा V4L2_TC_TYPE_24FPS		1
#घोषणा V4L2_TC_TYPE_25FPS		2
#घोषणा V4L2_TC_TYPE_30FPS		3
#घोषणा V4L2_TC_TYPE_50FPS		4
#घोषणा V4L2_TC_TYPE_60FPS		5

/*  Flags  */
#घोषणा V4L2_TC_FLAG_DROPFRAME		0x0001 /* "drop-frame" mode */
#घोषणा V4L2_TC_FLAG_COLORFRAME		0x0002
#घोषणा V4L2_TC_USERBITS_field		0x000C
#घोषणा V4L2_TC_USERBITS_USERDEFINED	0x0000
#घोषणा V4L2_TC_USERBITS_8BITCHARS	0x0008
/* The above is based on SMPTE समयcodes */

काष्ठा v4l2_jpegcompression अणु
	पूर्णांक quality;

	पूर्णांक  APPn;              /* Number of APP segment to be written,
				 * must be 0..15 */
	पूर्णांक  APP_len;           /* Length of data in JPEG APPn segment */
	अक्षर APP_data[60];      /* Data in the JPEG APPn segment. */

	पूर्णांक  COM_len;           /* Length of data in JPEG COM segment */
	अक्षर COM_data[60];      /* Data in JPEG COM segment */

	__u32 jpeg_markers;     /* Which markers should go पूर्णांकo the JPEG
				 * output. Unless you exactly know what
				 * you करो, leave them untouched.
				 * Including less markers will make the
				 * resulting code smaller, but there will
				 * be fewer applications which can पढ़ो it.
				 * The presence of the APP and COM marker
				 * is influenced by APP_len and COM_len
				 * ONLY, not by this property! */

#घोषणा V4L2_JPEG_MARKER_DHT (1<<3)    /* Define Huffman Tables */
#घोषणा V4L2_JPEG_MARKER_DQT (1<<4)    /* Define Quantization Tables */
#घोषणा V4L2_JPEG_MARKER_DRI (1<<5)    /* Define Restart Interval */
#घोषणा V4L2_JPEG_MARKER_COM (1<<6)    /* Comment segment */
#घोषणा V4L2_JPEG_MARKER_APP (1<<7)    /* App segment, driver will
					* always use APP0 */
पूर्ण;

/*
 *	M E M O R Y - M A P P I N G   B U F F E R S
 */

#अगर_घोषित __KERNEL__
/*
 * This corresponds to the user space version of समयval
 * क्रम 64-bit समय_प्रकार. sparc64 is dअगरferent from everyone
 * अन्यथा, using the microseconds in the wrong half of the
 * second 64-bit word.
 */
काष्ठा __kernel_v4l2_समयval अणु
	दीर्घ दीर्घ	tv_sec;
#अगर defined(__sparc__) && defined(__arch64__)
	पूर्णांक		tv_usec;
	पूर्णांक		__pad;
#अन्यथा
	दीर्घ दीर्घ	tv_usec;
#पूर्ण_अगर
पूर्ण;
#पूर्ण_अगर

काष्ठा v4l2_requestbuffers अणु
	__u32			count;
	__u32			type;		/* क्रमागत v4l2_buf_type */
	__u32			memory;		/* क्रमागत v4l2_memory */
	__u32			capabilities;
	__u32			reserved[1];
पूर्ण;

/* capabilities क्रम काष्ठा v4l2_requestbuffers and v4l2_create_buffers */
#घोषणा V4L2_BUF_CAP_SUPPORTS_MMAP			(1 << 0)
#घोषणा V4L2_BUF_CAP_SUPPORTS_USERPTR			(1 << 1)
#घोषणा V4L2_BUF_CAP_SUPPORTS_DMABUF			(1 << 2)
#घोषणा V4L2_BUF_CAP_SUPPORTS_REQUESTS			(1 << 3)
#घोषणा V4L2_BUF_CAP_SUPPORTS_ORPHANED_BUFS		(1 << 4)
#घोषणा V4L2_BUF_CAP_SUPPORTS_M2M_HOLD_CAPTURE_BUF	(1 << 5)
#घोषणा V4L2_BUF_CAP_SUPPORTS_MMAP_CACHE_HINTS		(1 << 6)

/**
 * काष्ठा v4l2_plane - plane info क्रम multi-planar buffers
 * @bytesused:		number of bytes occupied by data in the plane (payload)
 * @length:		size of this plane (NOT the payload) in bytes
 * @mem_offset:		when memory in the associated काष्ठा v4l2_buffer is
 *			V4L2_MEMORY_MMAP, equals the offset from the start of
 *			the device memory क्रम this plane (or is a "cookie" that
 *			should be passed to mmap() called on the video node)
 * @userptr:		when memory is V4L2_MEMORY_USERPTR, a userspace poपूर्णांकer
 *			poपूर्णांकing to this plane
 * @fd:			when memory is V4L2_MEMORY_DMABUF, a userspace file
 *			descriptor associated with this plane
 * @m:			जोड़ of @mem_offset, @userptr and @fd
 * @data_offset:	offset in the plane to the start of data; usually 0,
 *			unless there is a header in front of the data
 * @reserved:		drivers and applications must zero this array
 *
 * Multi-planar buffers consist of one or more planes, e.g. an YCbCr buffer
 * with two planes can have one plane क्रम Y, and another क्रम पूर्णांकerleaved CbCr
 * components. Each plane can reside in a separate memory buffer, or even in
 * a completely separate memory node (e.g. in embedded devices).
 */
काष्ठा v4l2_plane अणु
	__u32			bytesused;
	__u32			length;
	जोड़ अणु
		__u32		mem_offset;
		अचिन्हित दीर्घ	userptr;
		__s32		fd;
	पूर्ण m;
	__u32			data_offset;
	__u32			reserved[11];
पूर्ण;

/**
 * काष्ठा v4l2_buffer - video buffer info
 * @index:	id number of the buffer
 * @type:	क्रमागत v4l2_buf_type; buffer type (type == *_MPLANE क्रम
 *		multiplanar buffers);
 * @bytesused:	number of bytes occupied by data in the buffer (payload);
 *		unused (set to 0) क्रम multiplanar buffers
 * @flags:	buffer inक्रमmational flags
 * @field:	क्रमागत v4l2_field; field order of the image in the buffer
 * @बारtamp:	frame बारtamp
 * @समयcode:	frame समयcode
 * @sequence:	sequence count of this frame
 * @memory:	क्रमागत v4l2_memory; the method, in which the actual video data is
 *		passed
 * @offset:	क्रम non-multiplanar buffers with memory == V4L2_MEMORY_MMAP;
 *		offset from the start of the device memory क्रम this plane,
 *		(or a "cookie" that should be passed to mmap() as offset)
 * @userptr:	क्रम non-multiplanar buffers with memory == V4L2_MEMORY_USERPTR;
 *		a userspace poपूर्णांकer poपूर्णांकing to this buffer
 * @fd:		क्रम non-multiplanar buffers with memory == V4L2_MEMORY_DMABUF;
 *		a userspace file descriptor associated with this buffer
 * @planes:	क्रम multiplanar buffers; userspace poपूर्णांकer to the array of plane
 *		info काष्ठाs क्रम this buffer
 * @m:		जोड़ of @offset, @userptr, @planes and @fd
 * @length:	size in bytes of the buffer (NOT its payload) क्रम single-plane
 *		buffers (when type != *_MPLANE); number of elements in the
 *		planes array क्रम multi-plane buffers
 * @reserved2:	drivers and applications must zero this field
 * @request_fd: fd of the request that this buffer should use
 * @reserved:	क्रम backwards compatibility with applications that करो not know
 *		about @request_fd
 *
 * Contains data exchanged by application and driver using one of the Streaming
 * I/O methods.
 */
काष्ठा v4l2_buffer अणु
	__u32			index;
	__u32			type;
	__u32			bytesused;
	__u32			flags;
	__u32			field;
#अगर_घोषित __KERNEL__
	काष्ठा __kernel_v4l2_समयval बारtamp;
#अन्यथा
	काष्ठा समयval		बारtamp;
#पूर्ण_अगर
	काष्ठा v4l2_समयcode	समयcode;
	__u32			sequence;

	/* memory location */
	__u32			memory;
	जोड़ अणु
		__u32           offset;
		अचिन्हित दीर्घ   userptr;
		काष्ठा v4l2_plane *planes;
		__s32		fd;
	पूर्ण m;
	__u32			length;
	__u32			reserved2;
	जोड़ अणु
		__s32		request_fd;
		__u32		reserved;
	पूर्ण;
पूर्ण;

#अगर_अघोषित __KERNEL__
/**
 * v4l2_समयval_to_ns - Convert समयval to nanoseconds
 * @tv:		poपूर्णांकer to the समयval variable to be converted
 *
 * Returns the scalar nanosecond representation of the समयval
 * parameter.
 */
अटल अंतरभूत __u64 v4l2_समयval_to_ns(स्थिर काष्ठा समयval *tv)
अणु
	वापस (__u64)tv->tv_sec * 1000000000ULL + tv->tv_usec * 1000;
पूर्ण
#पूर्ण_अगर

/*  Flags क्रम 'flags' field */
/* Buffer is mapped (flag) */
#घोषणा V4L2_BUF_FLAG_MAPPED			0x00000001
/* Buffer is queued क्रम processing */
#घोषणा V4L2_BUF_FLAG_QUEUED			0x00000002
/* Buffer is पढ़ोy */
#घोषणा V4L2_BUF_FLAG_DONE			0x00000004
/* Image is a keyframe (I-frame) */
#घोषणा V4L2_BUF_FLAG_KEYFRAME			0x00000008
/* Image is a P-frame */
#घोषणा V4L2_BUF_FLAG_PFRAME			0x00000010
/* Image is a B-frame */
#घोषणा V4L2_BUF_FLAG_BFRAME			0x00000020
/* Buffer is पढ़ोy, but the data contained within is corrupted. */
#घोषणा V4L2_BUF_FLAG_ERROR			0x00000040
/* Buffer is added to an unqueued request */
#घोषणा V4L2_BUF_FLAG_IN_REQUEST		0x00000080
/* समयcode field is valid */
#घोषणा V4L2_BUF_FLAG_TIMECODE			0x00000100
/* Don't वापस the capture buffer until OUTPUT बारtamp changes */
#घोषणा V4L2_BUF_FLAG_M2M_HOLD_CAPTURE_BUF	0x00000200
/* Buffer is prepared क्रम queuing */
#घोषणा V4L2_BUF_FLAG_PREPARED			0x00000400
/* Cache handling flags */
#घोषणा V4L2_BUF_FLAG_NO_CACHE_INVALIDATE	0x00000800
#घोषणा V4L2_BUF_FLAG_NO_CACHE_CLEAN		0x00001000
/* Timestamp type */
#घोषणा V4L2_BUF_FLAG_TIMESTAMP_MASK		0x0000e000
#घोषणा V4L2_BUF_FLAG_TIMESTAMP_UNKNOWN		0x00000000
#घोषणा V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC	0x00002000
#घोषणा V4L2_BUF_FLAG_TIMESTAMP_COPY		0x00004000
/* Timestamp sources. */
#घोषणा V4L2_BUF_FLAG_TSTAMP_SRC_MASK		0x00070000
#घोषणा V4L2_BUF_FLAG_TSTAMP_SRC_खातापूर्ण		0x00000000
#घोषणा V4L2_BUF_FLAG_TSTAMP_SRC_SOE		0x00010000
/* mem2mem encoder/decoder */
#घोषणा V4L2_BUF_FLAG_LAST			0x00100000
/* request_fd is valid */
#घोषणा V4L2_BUF_FLAG_REQUEST_FD		0x00800000

/**
 * काष्ठा v4l2_exportbuffer - export of video buffer as DMABUF file descriptor
 *
 * @index:	id number of the buffer
 * @type:	क्रमागत v4l2_buf_type; buffer type (type == *_MPLANE क्रम
 *		multiplanar buffers);
 * @plane:	index of the plane to be exported, 0 क्रम single plane queues
 * @flags:	flags क्रम newly created file, currently only O_CLOEXEC is
 *		supported, refer to manual of खोलो syscall क्रम more details
 * @fd:		file descriptor associated with DMABUF (set by driver)
 * @reserved:	drivers and applications must zero this array
 *
 * Contains data used क्रम exporting a video buffer as DMABUF file descriptor.
 * The buffer is identअगरied by a 'cookie' वापसed by VIDIOC_QUERYBUF
 * (identical to the cookie used to mmap() the buffer to userspace). All
 * reserved fields must be set to zero. The field reserved0 is expected to
 * become a काष्ठाure 'type' allowing an alternative layout of the काष्ठाure
 * content. Thereक्रमe this field should not be used क्रम any other extensions.
 */
काष्ठा v4l2_exportbuffer अणु
	__u32		type; /* क्रमागत v4l2_buf_type */
	__u32		index;
	__u32		plane;
	__u32		flags;
	__s32		fd;
	__u32		reserved[11];
पूर्ण;

/*
 *	O V E R L A Y   P R E V I E W
 */
काष्ठा v4l2_framebuffer अणु
	__u32			capability;
	__u32			flags;
/* FIXME: in theory we should pass something like PCI device + memory
 * region + offset instead of some physical address */
	व्योम                    *base;
	काष्ठा अणु
		__u32		width;
		__u32		height;
		__u32		pixelक्रमmat;
		__u32		field;		/* क्रमागत v4l2_field */
		__u32		bytesperline;	/* क्रम padding, zero अगर unused */
		__u32		sizeimage;
		__u32		colorspace;	/* क्रमागत v4l2_colorspace */
		__u32		priv;		/* reserved field, set to 0 */
	पूर्ण fmt;
पूर्ण;
/*  Flags क्रम the 'capability' field. Read only */
#घोषणा V4L2_FBUF_CAP_EXTERNOVERLAY	0x0001
#घोषणा V4L2_FBUF_CAP_CHROMAKEY		0x0002
#घोषणा V4L2_FBUF_CAP_LIST_CLIPPING     0x0004
#घोषणा V4L2_FBUF_CAP_BITMAP_CLIPPING	0x0008
#घोषणा V4L2_FBUF_CAP_LOCAL_ALPHA	0x0010
#घोषणा V4L2_FBUF_CAP_GLOBAL_ALPHA	0x0020
#घोषणा V4L2_FBUF_CAP_LOCAL_INV_ALPHA	0x0040
#घोषणा V4L2_FBUF_CAP_SRC_CHROMAKEY	0x0080
/*  Flags क्रम the 'flags' field. */
#घोषणा V4L2_FBUF_FLAG_PRIMARY		0x0001
#घोषणा V4L2_FBUF_FLAG_OVERLAY		0x0002
#घोषणा V4L2_FBUF_FLAG_CHROMAKEY	0x0004
#घोषणा V4L2_FBUF_FLAG_LOCAL_ALPHA	0x0008
#घोषणा V4L2_FBUF_FLAG_GLOBAL_ALPHA	0x0010
#घोषणा V4L2_FBUF_FLAG_LOCAL_INV_ALPHA	0x0020
#घोषणा V4L2_FBUF_FLAG_SRC_CHROMAKEY	0x0040

काष्ठा v4l2_clip अणु
	काष्ठा v4l2_rect        c;
	काष्ठा v4l2_clip	__user *next;
पूर्ण;

काष्ठा v4l2_winकरोw अणु
	काष्ठा v4l2_rect        w;
	__u32			field;	 /* क्रमागत v4l2_field */
	__u32			chromakey;
	काष्ठा v4l2_clip	*clips;
	__u32			clipcount;
	व्योम			__user *biपंचांगap;
	__u8                    global_alpha;
पूर्ण;

/*
 *	C A P T U R E   P A R A M E T E R S
 */
काष्ठा v4l2_captureparm अणु
	__u32		   capability;	  /*  Supported modes */
	__u32		   capturemode;	  /*  Current mode */
	काष्ठा v4l2_fract  समयperframe;  /*  Time per frame in seconds */
	__u32		   extendedmode;  /*  Driver-specअगरic extensions */
	__u32              पढ़ोbuffers;   /*  # of buffers क्रम पढ़ो */
	__u32		   reserved[4];
पूर्ण;

/*  Flags क्रम 'capability' and 'capturemode' fields */
#घोषणा V4L2_MODE_HIGHQUALITY	0x0001	/*  High quality imaging mode */
#घोषणा V4L2_CAP_TIMEPERFRAME	0x1000	/*  समयperframe field is supported */

काष्ठा v4l2_outputparm अणु
	__u32		   capability;	 /*  Supported modes */
	__u32		   outpuपंचांगode;	 /*  Current mode */
	काष्ठा v4l2_fract  समयperframe; /*  Time per frame in seconds */
	__u32		   extendedmode; /*  Driver-specअगरic extensions */
	__u32              ग_लिखोbuffers; /*  # of buffers क्रम ग_लिखो */
	__u32		   reserved[4];
पूर्ण;

/*
 *	I N P U T   I M A G E   C R O P P I N G
 */
काष्ठा v4l2_cropcap अणु
	__u32			type;	/* क्रमागत v4l2_buf_type */
	काष्ठा v4l2_rect        bounds;
	काष्ठा v4l2_rect        defrect;
	काष्ठा v4l2_fract       pixelaspect;
पूर्ण;

काष्ठा v4l2_crop अणु
	__u32			type;	/* क्रमागत v4l2_buf_type */
	काष्ठा v4l2_rect        c;
पूर्ण;

/**
 * काष्ठा v4l2_selection - selection info
 * @type:	buffer type (करो not use *_MPLANE types)
 * @target:	Selection target, used to choose one of possible rectangles;
 *		defined in v4l2-common.h; V4L2_SEL_TGT_* .
 * @flags:	स्थिरraपूर्णांकs flags, defined in v4l2-common.h; V4L2_SEL_FLAG_*.
 * @r:		coordinates of selection winकरोw
 * @reserved:	क्रम future use, rounds काष्ठाure size to 64 bytes, set to zero
 *
 * Hardware may use multiple helper winकरोws to process a video stream.
 * The काष्ठाure is used to exchange this selection areas between
 * an application and a driver.
 */
काष्ठा v4l2_selection अणु
	__u32			type;
	__u32			target;
	__u32                   flags;
	काष्ठा v4l2_rect        r;
	__u32                   reserved[9];
पूर्ण;


/*
 *      A N A L O G   V I D E O   S T A N D A R D
 */

प्रकार __u64 v4l2_std_id;

/*
 * Attention: Keep the V4L2_STD_* bit definitions in sync with
 * include/dt-bindings/display/sdtv-standards.h SDTV_STD_* bit definitions.
 */
/* one bit क्रम each */
#घोषणा V4L2_STD_PAL_B          ((v4l2_std_id)0x00000001)
#घोषणा V4L2_STD_PAL_B1         ((v4l2_std_id)0x00000002)
#घोषणा V4L2_STD_PAL_G          ((v4l2_std_id)0x00000004)
#घोषणा V4L2_STD_PAL_H          ((v4l2_std_id)0x00000008)
#घोषणा V4L2_STD_PAL_I          ((v4l2_std_id)0x00000010)
#घोषणा V4L2_STD_PAL_D          ((v4l2_std_id)0x00000020)
#घोषणा V4L2_STD_PAL_D1         ((v4l2_std_id)0x00000040)
#घोषणा V4L2_STD_PAL_K          ((v4l2_std_id)0x00000080)

#घोषणा V4L2_STD_PAL_M          ((v4l2_std_id)0x00000100)
#घोषणा V4L2_STD_PAL_N          ((v4l2_std_id)0x00000200)
#घोषणा V4L2_STD_PAL_Nc         ((v4l2_std_id)0x00000400)
#घोषणा V4L2_STD_PAL_60         ((v4l2_std_id)0x00000800)

#घोषणा V4L2_STD_NTSC_M         ((v4l2_std_id)0x00001000)	/* BTSC */
#घोषणा V4L2_STD_NTSC_M_JP      ((v4l2_std_id)0x00002000)	/* EIA-J */
#घोषणा V4L2_STD_NTSC_443       ((v4l2_std_id)0x00004000)
#घोषणा V4L2_STD_NTSC_M_KR      ((v4l2_std_id)0x00008000)	/* FM A2 */

#घोषणा V4L2_STD_SECAM_B        ((v4l2_std_id)0x00010000)
#घोषणा V4L2_STD_SECAM_D        ((v4l2_std_id)0x00020000)
#घोषणा V4L2_STD_SECAM_G        ((v4l2_std_id)0x00040000)
#घोषणा V4L2_STD_SECAM_H        ((v4l2_std_id)0x00080000)
#घोषणा V4L2_STD_SECAM_K        ((v4l2_std_id)0x00100000)
#घोषणा V4L2_STD_SECAM_K1       ((v4l2_std_id)0x00200000)
#घोषणा V4L2_STD_SECAM_L        ((v4l2_std_id)0x00400000)
#घोषणा V4L2_STD_SECAM_LC       ((v4l2_std_id)0x00800000)

/* ATSC/HDTV */
#घोषणा V4L2_STD_ATSC_8_VSB     ((v4l2_std_id)0x01000000)
#घोषणा V4L2_STD_ATSC_16_VSB    ((v4l2_std_id)0x02000000)

/* FIXME:
   Although std_id is 64 bits, there is an issue on PPC32 architecture that
   makes चयन(__u64) to अवरोध. So, there's a hack on v4l2-common.c rounding
   this value to 32 bits.
   As, currently, the max value is क्रम V4L2_STD_ATSC_16_VSB (30 bits wide),
   it should work fine. However, अगर needed to add more than two standards,
   v4l2-common.c should be fixed.
 */

/*
 * Some macros to merge video standards in order to make live easier क्रम the
 * drivers and V4L2 applications
 */

/*
 * "Common" NTSC/M - It should be noticed that V4L2_STD_NTSC_443 is
 * Missing here.
 */
#घोषणा V4L2_STD_NTSC           (V4L2_STD_NTSC_M	|\
				 V4L2_STD_NTSC_M_JP     |\
				 V4L2_STD_NTSC_M_KR)
/* Secam macros */
#घोषणा V4L2_STD_SECAM_DK	(V4L2_STD_SECAM_D	|\
				 V4L2_STD_SECAM_K	|\
				 V4L2_STD_SECAM_K1)
/* All Secam Standards */
#घोषणा V4L2_STD_SECAM		(V4L2_STD_SECAM_B	|\
				 V4L2_STD_SECAM_G	|\
				 V4L2_STD_SECAM_H	|\
				 V4L2_STD_SECAM_DK	|\
				 V4L2_STD_SECAM_L       |\
				 V4L2_STD_SECAM_LC)
/* PAL macros */
#घोषणा V4L2_STD_PAL_BG		(V4L2_STD_PAL_B		|\
				 V4L2_STD_PAL_B1	|\
				 V4L2_STD_PAL_G)
#घोषणा V4L2_STD_PAL_DK		(V4L2_STD_PAL_D		|\
				 V4L2_STD_PAL_D1	|\
				 V4L2_STD_PAL_K)
/*
 * "Common" PAL - This macro is there to be compatible with the old
 * V4L1 concept of "PAL": /BGDKHI.
 * Several PAL standards are missing here: /M, /N and /Nc
 */
#घोषणा V4L2_STD_PAL		(V4L2_STD_PAL_BG	|\
				 V4L2_STD_PAL_DK	|\
				 V4L2_STD_PAL_H		|\
				 V4L2_STD_PAL_I)
/* Chroma "agnostic" standards */
#घोषणा V4L2_STD_B		(V4L2_STD_PAL_B		|\
				 V4L2_STD_PAL_B1	|\
				 V4L2_STD_SECAM_B)
#घोषणा V4L2_STD_G		(V4L2_STD_PAL_G		|\
				 V4L2_STD_SECAM_G)
#घोषणा V4L2_STD_H		(V4L2_STD_PAL_H		|\
				 V4L2_STD_SECAM_H)
#घोषणा V4L2_STD_L		(V4L2_STD_SECAM_L	|\
				 V4L2_STD_SECAM_LC)
#घोषणा V4L2_STD_GH		(V4L2_STD_G		|\
				 V4L2_STD_H)
#घोषणा V4L2_STD_DK		(V4L2_STD_PAL_DK	|\
				 V4L2_STD_SECAM_DK)
#घोषणा V4L2_STD_BG		(V4L2_STD_B		|\
				 V4L2_STD_G)
#घोषणा V4L2_STD_MN		(V4L2_STD_PAL_M		|\
				 V4L2_STD_PAL_N		|\
				 V4L2_STD_PAL_Nc	|\
				 V4L2_STD_NTSC)

/* Standards where MTS/BTSC stereo could be found */
#घोषणा V4L2_STD_MTS		(V4L2_STD_NTSC_M	|\
				 V4L2_STD_PAL_M		|\
				 V4L2_STD_PAL_N		|\
				 V4L2_STD_PAL_Nc)

/* Standards क्रम Countries with 60Hz Line frequency */
#घोषणा V4L2_STD_525_60		(V4L2_STD_PAL_M		|\
				 V4L2_STD_PAL_60	|\
				 V4L2_STD_NTSC		|\
				 V4L2_STD_NTSC_443)
/* Standards क्रम Countries with 50Hz Line frequency */
#घोषणा V4L2_STD_625_50		(V4L2_STD_PAL		|\
				 V4L2_STD_PAL_N		|\
				 V4L2_STD_PAL_Nc	|\
				 V4L2_STD_SECAM)

#घोषणा V4L2_STD_ATSC           (V4L2_STD_ATSC_8_VSB    |\
				 V4L2_STD_ATSC_16_VSB)
/* Macros with none and all analog standards */
#घोषणा V4L2_STD_UNKNOWN        0
#घोषणा V4L2_STD_ALL            (V4L2_STD_525_60	|\
				 V4L2_STD_625_50)

काष्ठा v4l2_standard अणु
	__u32		     index;
	v4l2_std_id          id;
	__u8		     name[24];
	काष्ठा v4l2_fract    frameperiod; /* Frames, not fields */
	__u32		     framelines;
	__u32		     reserved[4];
पूर्ण;

/*
 *	D V	B T	T I M I N G S
 */

/** काष्ठा v4l2_bt_timings - BT.656/BT.1120 timing data
 * @width:	total width of the active video in pixels
 * @height:	total height of the active video in lines
 * @पूर्णांकerlaced:	Interlaced or progressive
 * @polarities:	Positive or negative polarities
 * @pixelघड़ी:	Pixel घड़ी in HZ. Ex. 74.25MHz->74250000
 * @hfrontporch:Horizontal front porch in pixels
 * @hsync:	Horizontal Sync length in pixels
 * @hbackporch:	Horizontal back porch in pixels
 * @vfrontporch:Vertical front porch in lines
 * @vsync:	Vertical Sync length in lines
 * @vbackporch:	Vertical back porch in lines
 * @il_vfrontporch:Vertical front porch क्रम the even field
 *		(aka field 2) of पूर्णांकerlaced field क्रमmats
 * @il_vsync:	Vertical Sync length क्रम the even field
 *		(aka field 2) of पूर्णांकerlaced field क्रमmats
 * @il_vbackporch:Vertical back porch क्रम the even field
 *		(aka field 2) of पूर्णांकerlaced field क्रमmats
 * @standards:	Standards the timing beदीर्घs to
 * @flags:	Flags
 * @picture_aspect: The picture aspect ratio (hor/vert).
 * @cea861_vic:	VIC code as per the CEA-861 standard.
 * @hdmi_vic:	VIC code as per the HDMI standard.
 * @reserved:	Reserved fields, must be zeroed.
 *
 * A note regarding vertical पूर्णांकerlaced timings: height refers to the total
 * height of the active video frame (= two fields). The blanking timings refer
 * to the blanking of each field. So the height of the total frame is
 * calculated as follows:
 *
 * tot_height = height + vfrontporch + vsync + vbackporch +
 *                       il_vfrontporch + il_vsync + il_vbackporch
 *
 * The active height of each field is height / 2.
 */
काष्ठा v4l2_bt_timings अणु
	__u32	width;
	__u32	height;
	__u32	पूर्णांकerlaced;
	__u32	polarities;
	__u64	pixelघड़ी;
	__u32	hfrontporch;
	__u32	hsync;
	__u32	hbackporch;
	__u32	vfrontporch;
	__u32	vsync;
	__u32	vbackporch;
	__u32	il_vfrontporch;
	__u32	il_vsync;
	__u32	il_vbackporch;
	__u32	standards;
	__u32	flags;
	काष्ठा v4l2_fract picture_aspect;
	__u8	cea861_vic;
	__u8	hdmi_vic;
	__u8	reserved[46];
पूर्ण __attribute__ ((packed));

/* Interlaced or progressive क्रमmat */
#घोषणा	V4L2_DV_PROGRESSIVE	0
#घोषणा	V4L2_DV_INTERLACED	1

/* Polarities. If bit is not set, it is assumed to be negative polarity */
#घोषणा V4L2_DV_VSYNC_POS_POL	0x00000001
#घोषणा V4L2_DV_HSYNC_POS_POL	0x00000002

/* Timings standards */
#घोषणा V4L2_DV_BT_STD_CEA861	(1 << 0)  /* CEA-861 Digital TV Profile */
#घोषणा V4L2_DV_BT_STD_DMT	(1 << 1)  /* VESA Discrete Monitor Timings */
#घोषणा V4L2_DV_BT_STD_CVT	(1 << 2)  /* VESA Coordinated Video Timings */
#घोषणा V4L2_DV_BT_STD_GTF	(1 << 3)  /* VESA Generalized Timings Formula */
#घोषणा V4L2_DV_BT_STD_SDI	(1 << 4)  /* SDI Timings */

/* Flags */

/*
 * CVT/GTF specअगरic: timing uses reduced blanking (CVT) or the 'Secondary
 * GTF' curve (GTF). In both हालs the horizontal and/or vertical blanking
 * पूर्णांकervals are reduced, allowing a higher resolution over the same
 * bandwidth. This is a पढ़ो-only flag.
 */
#घोषणा V4L2_DV_FL_REDUCED_BLANKING		(1 << 0)
/*
 * CEA-861 specअगरic: set क्रम CEA-861 क्रमmats with a framerate of a multiple
 * of six. These क्रमmats can be optionally played at 1 / 1.001 speed.
 * This is a पढ़ो-only flag.
 */
#घोषणा V4L2_DV_FL_CAN_REDUCE_FPS		(1 << 1)
/*
 * CEA-861 specअगरic: only valid क्रम video transmitters, the flag is cleared
 * by receivers.
 * If the framerate of the क्रमmat is a multiple of six, then the pixelघड़ी
 * used to set up the transmitter is भागided by 1.001 to make it compatible
 * with 60 Hz based standards such as NTSC and PAL-M that use a framerate of
 * 29.97 Hz. Otherwise this flag is cleared. If the transmitter can't generate
 * such frequencies, then the flag will also be cleared.
 */
#घोषणा V4L2_DV_FL_REDUCED_FPS			(1 << 2)
/*
 * Specअगरic to पूर्णांकerlaced क्रमmats: अगर set, then field 1 is really one half-line
 * दीर्घer and field 2 is really one half-line लघुer, so each field has
 * exactly the same number of half-lines. Whether half-lines can be detected
 * or used depends on the hardware.
 */
#घोषणा V4L2_DV_FL_HALF_LINE			(1 << 3)
/*
 * If set, then this is a Consumer Electronics (CE) video क्रमmat. Such क्रमmats
 * dअगरfer from other क्रमmats (commonly called IT क्रमmats) in that अगर RGB
 * encoding is used then by शेष the RGB values use limited range (i.e.
 * use the range 16-235) as opposed to 0-255. All क्रमmats defined in CEA-861
 * except क्रम the 640x480 क्रमmat are CE क्रमmats.
 */
#घोषणा V4L2_DV_FL_IS_CE_VIDEO			(1 << 4)
/* Some क्रमmats like SMPTE-125M have an पूर्णांकerlaced संकेत with a odd
 * total height. For these क्रमmats, अगर this flag is set, the first
 * field has the extra line. If not, it is the second field.
 */
#घोषणा V4L2_DV_FL_FIRST_FIELD_EXTRA_LINE	(1 << 5)
/*
 * If set, then the picture_aspect field is valid. Otherwise assume that the
 * pixels are square, so the picture aspect ratio is the same as the width to
 * height ratio.
 */
#घोषणा V4L2_DV_FL_HAS_PICTURE_ASPECT		(1 << 6)
/*
 * If set, then the cea861_vic field is valid and contains the Video
 * Identअगरication Code as per the CEA-861 standard.
 */
#घोषणा V4L2_DV_FL_HAS_CEA861_VIC		(1 << 7)
/*
 * If set, then the hdmi_vic field is valid and contains the Video
 * Identअगरication Code as per the HDMI standard (HDMI Venकरोr Specअगरic
 * InfoFrame).
 */
#घोषणा V4L2_DV_FL_HAS_HDMI_VIC			(1 << 8)
/*
 * CEA-861 specअगरic: only valid क्रम video receivers.
 * If set, then HW can detect the dअगरference between regular FPS and
 * 1000/1001 FPS. Note: This flag is only valid क्रम HDMI VIC codes with
 * the V4L2_DV_FL_CAN_REDUCE_FPS flag set.
 */
#घोषणा V4L2_DV_FL_CAN_DETECT_REDUCED_FPS	(1 << 9)

/* A few useful defines to calculate the total blanking and frame sizes */
#घोषणा V4L2_DV_BT_BLANKING_WIDTH(bt) \
	((bt)->hfrontporch + (bt)->hsync + (bt)->hbackporch)
#घोषणा V4L2_DV_BT_FRAME_WIDTH(bt) \
	((bt)->width + V4L2_DV_BT_BLANKING_WIDTH(bt))
#घोषणा V4L2_DV_BT_BLANKING_HEIGHT(bt) \
	((bt)->vfrontporch + (bt)->vsync + (bt)->vbackporch + \
	 (bt)->il_vfrontporch + (bt)->il_vsync + (bt)->il_vbackporch)
#घोषणा V4L2_DV_BT_FRAME_HEIGHT(bt) \
	((bt)->height + V4L2_DV_BT_BLANKING_HEIGHT(bt))

/** काष्ठा v4l2_dv_timings - DV timings
 * @type:	the type of the timings
 * @bt:	BT656/1120 timings
 */
काष्ठा v4l2_dv_timings अणु
	__u32 type;
	जोड़ अणु
		काष्ठा v4l2_bt_timings	bt;
		__u32	reserved[32];
	पूर्ण;
पूर्ण __attribute__ ((packed));

/* Values क्रम the type field */
#घोषणा V4L2_DV_BT_656_1120	0	/* BT.656/1120 timing type */


/** काष्ठा v4l2_क्रमागत_dv_timings - DV timings क्रमागतeration
 * @index:	क्रमागतeration index
 * @pad:	the pad number क्रम which to क्रमागतerate timings (used with
 *		v4l-subdev nodes only)
 * @reserved:	must be zeroed
 * @timings:	the timings क्रम the given index
 */
काष्ठा v4l2_क्रमागत_dv_timings अणु
	__u32 index;
	__u32 pad;
	__u32 reserved[2];
	काष्ठा v4l2_dv_timings timings;
पूर्ण;

/** काष्ठा v4l2_bt_timings_cap - BT.656/BT.1120 timing capabilities
 * @min_width:		width in pixels
 * @max_width:		width in pixels
 * @min_height:		height in lines
 * @max_height:		height in lines
 * @min_pixelघड़ी:	Pixel घड़ी in HZ. Ex. 74.25MHz->74250000
 * @max_pixelघड़ी:	Pixel घड़ी in HZ. Ex. 74.25MHz->74250000
 * @standards:		Supported standards
 * @capabilities:	Supported capabilities
 * @reserved:		Must be zeroed
 */
काष्ठा v4l2_bt_timings_cap अणु
	__u32	min_width;
	__u32	max_width;
	__u32	min_height;
	__u32	max_height;
	__u64	min_pixelघड़ी;
	__u64	max_pixelघड़ी;
	__u32	standards;
	__u32	capabilities;
	__u32	reserved[16];
पूर्ण __attribute__ ((packed));

/* Supports पूर्णांकerlaced क्रमmats */
#घोषणा V4L2_DV_BT_CAP_INTERLACED	(1 << 0)
/* Supports progressive क्रमmats */
#घोषणा V4L2_DV_BT_CAP_PROGRESSIVE	(1 << 1)
/* Supports CVT/GTF reduced blanking */
#घोषणा V4L2_DV_BT_CAP_REDUCED_BLANKING	(1 << 2)
/* Supports custom क्रमmats */
#घोषणा V4L2_DV_BT_CAP_CUSTOM		(1 << 3)

/** काष्ठा v4l2_dv_timings_cap - DV timings capabilities
 * @type:	the type of the timings (same as in काष्ठा v4l2_dv_timings)
 * @pad:	the pad number क्रम which to query capabilities (used with
 *		v4l-subdev nodes only)
 * @bt:		the BT656/1120 timings capabilities
 */
काष्ठा v4l2_dv_timings_cap अणु
	__u32 type;
	__u32 pad;
	__u32 reserved[2];
	जोड़ अणु
		काष्ठा v4l2_bt_timings_cap bt;
		__u32 raw_data[32];
	पूर्ण;
पूर्ण;


/*
 *	V I D E O   I N P U T S
 */
काष्ठा v4l2_input अणु
	__u32	     index;		/*  Which input */
	__u8	     name[32];		/*  Label */
	__u32	     type;		/*  Type of input */
	__u32	     audioset;		/*  Associated audios (bitfield) */
	__u32        tuner;             /*  क्रमागत v4l2_tuner_type */
	v4l2_std_id  std;
	__u32	     status;
	__u32	     capabilities;
	__u32	     reserved[3];
पूर्ण;

/*  Values क्रम the 'type' field */
#घोषणा V4L2_INPUT_TYPE_TUNER		1
#घोषणा V4L2_INPUT_TYPE_CAMERA		2
#घोषणा V4L2_INPUT_TYPE_TOUCH		3

/* field 'status' - general */
#घोषणा V4L2_IN_ST_NO_POWER    0x00000001  /* Attached device is off */
#घोषणा V4L2_IN_ST_NO_SIGNAL   0x00000002
#घोषणा V4L2_IN_ST_NO_COLOR    0x00000004

/* field 'status' - sensor orientation */
/* If sensor is mounted upside करोwn set both bits */
#घोषणा V4L2_IN_ST_HFLIP       0x00000010 /* Frames are flipped horizontally */
#घोषणा V4L2_IN_ST_VFLIP       0x00000020 /* Frames are flipped vertically */

/* field 'status' - analog */
#घोषणा V4L2_IN_ST_NO_H_LOCK   0x00000100  /* No horizontal sync lock */
#घोषणा V4L2_IN_ST_COLOR_KILL  0x00000200  /* Color समाप्तer is active */
#घोषणा V4L2_IN_ST_NO_V_LOCK   0x00000400  /* No vertical sync lock */
#घोषणा V4L2_IN_ST_NO_STD_LOCK 0x00000800  /* No standard क्रमmat lock */

/* field 'status' - digital */
#घोषणा V4L2_IN_ST_NO_SYNC     0x00010000  /* No synchronization lock */
#घोषणा V4L2_IN_ST_NO_EQU      0x00020000  /* No equalizer lock */
#घोषणा V4L2_IN_ST_NO_CARRIER  0x00040000  /* Carrier recovery failed */

/* field 'status' - VCR and set-top box */
#घोषणा V4L2_IN_ST_MACROVISION 0x01000000  /* Macrovision detected */
#घोषणा V4L2_IN_ST_NO_ACCESS   0x02000000  /* Conditional access denied */
#घोषणा V4L2_IN_ST_VTR         0x04000000  /* VTR समय स्थिरant */

/* capabilities flags */
#घोषणा V4L2_IN_CAP_DV_TIMINGS		0x00000002 /* Supports S_DV_TIMINGS */
#घोषणा V4L2_IN_CAP_CUSTOM_TIMINGS	V4L2_IN_CAP_DV_TIMINGS /* For compatibility */
#घोषणा V4L2_IN_CAP_STD			0x00000004 /* Supports S_STD */
#घोषणा V4L2_IN_CAP_NATIVE_SIZE		0x00000008 /* Supports setting native size */

/*
 *	V I D E O   O U T P U T S
 */
काष्ठा v4l2_output अणु
	__u32	     index;		/*  Which output */
	__u8	     name[32];		/*  Label */
	__u32	     type;		/*  Type of output */
	__u32	     audioset;		/*  Associated audios (bitfield) */
	__u32	     modulator;         /*  Associated modulator */
	v4l2_std_id  std;
	__u32	     capabilities;
	__u32	     reserved[3];
पूर्ण;
/*  Values क्रम the 'type' field */
#घोषणा V4L2_OUTPUT_TYPE_MODULATOR		1
#घोषणा V4L2_OUTPUT_TYPE_ANALOG			2
#घोषणा V4L2_OUTPUT_TYPE_ANALOGVGAOVERLAY	3

/* capabilities flags */
#घोषणा V4L2_OUT_CAP_DV_TIMINGS		0x00000002 /* Supports S_DV_TIMINGS */
#घोषणा V4L2_OUT_CAP_CUSTOM_TIMINGS	V4L2_OUT_CAP_DV_TIMINGS /* For compatibility */
#घोषणा V4L2_OUT_CAP_STD		0x00000004 /* Supports S_STD */
#घोषणा V4L2_OUT_CAP_NATIVE_SIZE	0x00000008 /* Supports setting native size */

/*
 *	C O N T R O L S
 */
काष्ठा v4l2_control अणु
	__u32		     id;
	__s32		     value;
पूर्ण;

काष्ठा v4l2_ext_control अणु
	__u32 id;
	__u32 size;
	__u32 reserved2[1];
	जोड़ अणु
		__s32 value;
		__s64 value64;
		अक्षर __user *string;
		__u8 __user *p_u8;
		__u16 __user *p_u16;
		__u32 __user *p_u32;
		काष्ठा v4l2_area __user *p_area;
		काष्ठा v4l2_ctrl_h264_sps __user *p_h264_sps;
		काष्ठा v4l2_ctrl_h264_pps *p_h264_pps;
		काष्ठा v4l2_ctrl_h264_scaling_matrix __user *p_h264_scaling_matrix;
		काष्ठा v4l2_ctrl_h264_pred_weights __user *p_h264_pred_weights;
		काष्ठा v4l2_ctrl_h264_slice_params __user *p_h264_slice_params;
		काष्ठा v4l2_ctrl_h264_decode_params __user *p_h264_decode_params;
		काष्ठा v4l2_ctrl_fwht_params __user *p_fwht_params;
		काष्ठा v4l2_ctrl_vp8_frame __user *p_vp8_frame;
		व्योम __user *ptr;
	पूर्ण;
पूर्ण __attribute__ ((packed));

काष्ठा v4l2_ext_controls अणु
	जोड़ अणु
#अगर_अघोषित __KERNEL__
		__u32 ctrl_class;
#पूर्ण_अगर
		__u32 which;
	पूर्ण;
	__u32 count;
	__u32 error_idx;
	__s32 request_fd;
	__u32 reserved[1];
	काष्ठा v4l2_ext_control *controls;
पूर्ण;

#घोषणा V4L2_CTRL_ID_MASK	  (0x0fffffff)
#अगर_अघोषित __KERNEL__
#घोषणा V4L2_CTRL_ID2CLASS(id)    ((id) & 0x0fff0000UL)
#पूर्ण_अगर
#घोषणा V4L2_CTRL_ID2WHICH(id)    ((id) & 0x0fff0000UL)
#घोषणा V4L2_CTRL_DRIVER_PRIV(id) (((id) & 0xffff) >= 0x1000)
#घोषणा V4L2_CTRL_MAX_DIMS	  (4)
#घोषणा V4L2_CTRL_WHICH_CUR_VAL   0
#घोषणा V4L2_CTRL_WHICH_DEF_VAL   0x0f000000
#घोषणा V4L2_CTRL_WHICH_REQUEST_VAL 0x0f010000

क्रमागत v4l2_ctrl_type अणु
	V4L2_CTRL_TYPE_INTEGER	     = 1,
	V4L2_CTRL_TYPE_BOOLEAN	     = 2,
	V4L2_CTRL_TYPE_MENU	     = 3,
	V4L2_CTRL_TYPE_BUTTON	     = 4,
	V4L2_CTRL_TYPE_INTEGER64     = 5,
	V4L2_CTRL_TYPE_CTRL_CLASS    = 6,
	V4L2_CTRL_TYPE_STRING        = 7,
	V4L2_CTRL_TYPE_BITMASK       = 8,
	V4L2_CTRL_TYPE_INTEGER_MENU  = 9,

	/* Compound types are >= 0x0100 */
	V4L2_CTRL_COMPOUND_TYPES     = 0x0100,
	V4L2_CTRL_TYPE_U8	     = 0x0100,
	V4L2_CTRL_TYPE_U16	     = 0x0101,
	V4L2_CTRL_TYPE_U32	     = 0x0102,
	V4L2_CTRL_TYPE_AREA          = 0x0106,

	V4L2_CTRL_TYPE_HDR10_CLL_INFO		= 0x0110,
	V4L2_CTRL_TYPE_HDR10_MASTERING_DISPLAY	= 0x0111,

	V4L2_CTRL_TYPE_H264_SPS             = 0x0200,
	V4L2_CTRL_TYPE_H264_PPS		    = 0x0201,
	V4L2_CTRL_TYPE_H264_SCALING_MATRIX  = 0x0202,
	V4L2_CTRL_TYPE_H264_SLICE_PARAMS    = 0x0203,
	V4L2_CTRL_TYPE_H264_DECODE_PARAMS   = 0x0204,
	V4L2_CTRL_TYPE_H264_PRED_WEIGHTS    = 0x0205,

	V4L2_CTRL_TYPE_FWHT_PARAMS	    = 0x0220,

	V4L2_CTRL_TYPE_VP8_FRAME            = 0x0240,
पूर्ण;

/*  Used in the VIDIOC_QUERYCTRL ioctl क्रम querying controls */
काष्ठा v4l2_queryctrl अणु
	__u32		     id;
	__u32		     type;	/* क्रमागत v4l2_ctrl_type */
	__u8		     name[32];	/* Whatever */
	__s32		     minimum;	/* Note चिन्हितness */
	__s32		     maximum;
	__s32		     step;
	__s32		     शेष_value;
	__u32                flags;
	__u32		     reserved[2];
पूर्ण;

/*  Used in the VIDIOC_QUERY_EXT_CTRL ioctl क्रम querying extended controls */
काष्ठा v4l2_query_ext_ctrl अणु
	__u32		     id;
	__u32		     type;
	अक्षर		     name[32];
	__s64		     minimum;
	__s64		     maximum;
	__u64		     step;
	__s64		     शेष_value;
	__u32                flags;
	__u32                elem_size;
	__u32                elems;
	__u32                nr_of_dims;
	__u32                dims[V4L2_CTRL_MAX_DIMS];
	__u32		     reserved[32];
पूर्ण;

/*  Used in the VIDIOC_QUERYMENU ioctl क्रम querying menu items */
काष्ठा v4l2_querymenu अणु
	__u32		id;
	__u32		index;
	जोड़ अणु
		__u8	name[32];	/* Whatever */
		__s64	value;
	पूर्ण;
	__u32		reserved;
पूर्ण __attribute__ ((packed));

/*  Control flags  */
#घोषणा V4L2_CTRL_FLAG_DISABLED		0x0001
#घोषणा V4L2_CTRL_FLAG_GRABBED		0x0002
#घोषणा V4L2_CTRL_FLAG_READ_ONLY	0x0004
#घोषणा V4L2_CTRL_FLAG_UPDATE		0x0008
#घोषणा V4L2_CTRL_FLAG_INACTIVE		0x0010
#घोषणा V4L2_CTRL_FLAG_SLIDER		0x0020
#घोषणा V4L2_CTRL_FLAG_WRITE_ONLY	0x0040
#घोषणा V4L2_CTRL_FLAG_VOLATILE		0x0080
#घोषणा V4L2_CTRL_FLAG_HAS_PAYLOAD	0x0100
#घोषणा V4L2_CTRL_FLAG_EXECUTE_ON_WRITE	0x0200
#घोषणा V4L2_CTRL_FLAG_MODIFY_LAYOUT	0x0400

/*  Query flags, to be ORed with the control ID */
#घोषणा V4L2_CTRL_FLAG_NEXT_CTRL	0x80000000
#घोषणा V4L2_CTRL_FLAG_NEXT_COMPOUND	0x40000000

/*  User-class control IDs defined by V4L2 */
#घोषणा V4L2_CID_MAX_CTRLS		1024
/*  IDs reserved क्रम driver specअगरic controls */
#घोषणा V4L2_CID_PRIVATE_BASE		0x08000000


/*
 *	T U N I N G
 */
काष्ठा v4l2_tuner अणु
	__u32                   index;
	__u8			name[32];
	__u32			type;	/* क्रमागत v4l2_tuner_type */
	__u32			capability;
	__u32			rangelow;
	__u32			rangehigh;
	__u32			rxsubchans;
	__u32			audmode;
	__s32			संकेत;
	__s32			afc;
	__u32			reserved[4];
पूर्ण;

काष्ठा v4l2_modulator अणु
	__u32			index;
	__u8			name[32];
	__u32			capability;
	__u32			rangelow;
	__u32			rangehigh;
	__u32			txsubchans;
	__u32			type;	/* क्रमागत v4l2_tuner_type */
	__u32			reserved[3];
पूर्ण;

/*  Flags क्रम the 'capability' field */
#घोषणा V4L2_TUNER_CAP_LOW		0x0001
#घोषणा V4L2_TUNER_CAP_NORM		0x0002
#घोषणा V4L2_TUNER_CAP_HWSEEK_BOUNDED	0x0004
#घोषणा V4L2_TUNER_CAP_HWSEEK_WRAP	0x0008
#घोषणा V4L2_TUNER_CAP_STEREO		0x0010
#घोषणा V4L2_TUNER_CAP_LANG2		0x0020
#घोषणा V4L2_TUNER_CAP_SAP		0x0020
#घोषणा V4L2_TUNER_CAP_LANG1		0x0040
#घोषणा V4L2_TUNER_CAP_RDS		0x0080
#घोषणा V4L2_TUNER_CAP_RDS_BLOCK_IO	0x0100
#घोषणा V4L2_TUNER_CAP_RDS_CONTROLS	0x0200
#घोषणा V4L2_TUNER_CAP_FREQ_BANDS	0x0400
#घोषणा V4L2_TUNER_CAP_HWSEEK_PROG_LIM	0x0800
#घोषणा V4L2_TUNER_CAP_1HZ		0x1000

/*  Flags क्रम the 'rxsubchans' field */
#घोषणा V4L2_TUNER_SUB_MONO		0x0001
#घोषणा V4L2_TUNER_SUB_STEREO		0x0002
#घोषणा V4L2_TUNER_SUB_LANG2		0x0004
#घोषणा V4L2_TUNER_SUB_SAP		0x0004
#घोषणा V4L2_TUNER_SUB_LANG1		0x0008
#घोषणा V4L2_TUNER_SUB_RDS		0x0010

/*  Values क्रम the 'audmode' field */
#घोषणा V4L2_TUNER_MODE_MONO		0x0000
#घोषणा V4L2_TUNER_MODE_STEREO		0x0001
#घोषणा V4L2_TUNER_MODE_LANG2		0x0002
#घोषणा V4L2_TUNER_MODE_SAP		0x0002
#घोषणा V4L2_TUNER_MODE_LANG1		0x0003
#घोषणा V4L2_TUNER_MODE_LANG1_LANG2	0x0004

काष्ठा v4l2_frequency अणु
	__u32	tuner;
	__u32	type;	/* क्रमागत v4l2_tuner_type */
	__u32	frequency;
	__u32	reserved[8];
पूर्ण;

#घोषणा V4L2_BAND_MODULATION_VSB	(1 << 1)
#घोषणा V4L2_BAND_MODULATION_FM		(1 << 2)
#घोषणा V4L2_BAND_MODULATION_AM		(1 << 3)

काष्ठा v4l2_frequency_band अणु
	__u32	tuner;
	__u32	type;	/* क्रमागत v4l2_tuner_type */
	__u32	index;
	__u32	capability;
	__u32	rangelow;
	__u32	rangehigh;
	__u32	modulation;
	__u32	reserved[9];
पूर्ण;

काष्ठा v4l2_hw_freq_seek अणु
	__u32	tuner;
	__u32	type;	/* क्रमागत v4l2_tuner_type */
	__u32	seek_upward;
	__u32	wrap_around;
	__u32	spacing;
	__u32	rangelow;
	__u32	rangehigh;
	__u32	reserved[5];
पूर्ण;

/*
 *	R D S
 */

काष्ठा v4l2_rds_data अणु
	__u8	lsb;
	__u8	msb;
	__u8	block;
पूर्ण __attribute__ ((packed));

#घोषणा V4L2_RDS_BLOCK_MSK	 0x7
#घोषणा V4L2_RDS_BLOCK_A	 0
#घोषणा V4L2_RDS_BLOCK_B	 1
#घोषणा V4L2_RDS_BLOCK_C	 2
#घोषणा V4L2_RDS_BLOCK_D	 3
#घोषणा V4L2_RDS_BLOCK_C_ALT	 4
#घोषणा V4L2_RDS_BLOCK_INVALID	 7

#घोषणा V4L2_RDS_BLOCK_CORRECTED 0x40
#घोषणा V4L2_RDS_BLOCK_ERROR	 0x80

/*
 *	A U D I O
 */
काष्ठा v4l2_audio अणु
	__u32	index;
	__u8	name[32];
	__u32	capability;
	__u32	mode;
	__u32	reserved[2];
पूर्ण;

/*  Flags क्रम the 'capability' field */
#घोषणा V4L2_AUDCAP_STEREO		0x00001
#घोषणा V4L2_AUDCAP_AVL			0x00002

/*  Flags क्रम the 'mode' field */
#घोषणा V4L2_AUDMODE_AVL		0x00001

काष्ठा v4l2_audioout अणु
	__u32	index;
	__u8	name[32];
	__u32	capability;
	__u32	mode;
	__u32	reserved[2];
पूर्ण;

/*
 *	M P E G   S E R V I C E S
 */
#अगर 1
#घोषणा V4L2_ENC_IDX_FRAME_I    (0)
#घोषणा V4L2_ENC_IDX_FRAME_P    (1)
#घोषणा V4L2_ENC_IDX_FRAME_B    (2)
#घोषणा V4L2_ENC_IDX_FRAME_MASK (0xf)

काष्ठा v4l2_enc_idx_entry अणु
	__u64 offset;
	__u64 pts;
	__u32 length;
	__u32 flags;
	__u32 reserved[2];
पूर्ण;

#घोषणा V4L2_ENC_IDX_ENTRIES (64)
काष्ठा v4l2_enc_idx अणु
	__u32 entries;
	__u32 entries_cap;
	__u32 reserved[4];
	काष्ठा v4l2_enc_idx_entry entry[V4L2_ENC_IDX_ENTRIES];
पूर्ण;


#घोषणा V4L2_ENC_CMD_START      (0)
#घोषणा V4L2_ENC_CMD_STOP       (1)
#घोषणा V4L2_ENC_CMD_PAUSE      (2)
#घोषणा V4L2_ENC_CMD_RESUME     (3)

/* Flags क्रम V4L2_ENC_CMD_STOP */
#घोषणा V4L2_ENC_CMD_STOP_AT_GOP_END    (1 << 0)

काष्ठा v4l2_encoder_cmd अणु
	__u32 cmd;
	__u32 flags;
	जोड़ अणु
		काष्ठा अणु
			__u32 data[8];
		पूर्ण raw;
	पूर्ण;
पूर्ण;

/* Decoder commands */
#घोषणा V4L2_DEC_CMD_START       (0)
#घोषणा V4L2_DEC_CMD_STOP        (1)
#घोषणा V4L2_DEC_CMD_PAUSE       (2)
#घोषणा V4L2_DEC_CMD_RESUME      (3)
#घोषणा V4L2_DEC_CMD_FLUSH       (4)

/* Flags क्रम V4L2_DEC_CMD_START */
#घोषणा V4L2_DEC_CMD_START_MUTE_AUDIO	(1 << 0)

/* Flags क्रम V4L2_DEC_CMD_PAUSE */
#घोषणा V4L2_DEC_CMD_PAUSE_TO_BLACK	(1 << 0)

/* Flags क्रम V4L2_DEC_CMD_STOP */
#घोषणा V4L2_DEC_CMD_STOP_TO_BLACK	(1 << 0)
#घोषणा V4L2_DEC_CMD_STOP_IMMEDIATELY	(1 << 1)

/* Play क्रमmat requirements (वापसed by the driver): */

/* The decoder has no special क्रमmat requirements */
#घोषणा V4L2_DEC_START_FMT_NONE		(0)
/* The decoder requires full GOPs */
#घोषणा V4L2_DEC_START_FMT_GOP		(1)

/* The काष्ठाure must be zeroed beक्रमe use by the application
   This ensures it can be extended safely in the future. */
काष्ठा v4l2_decoder_cmd अणु
	__u32 cmd;
	__u32 flags;
	जोड़ अणु
		काष्ठा अणु
			__u64 pts;
		पूर्ण stop;

		काष्ठा अणु
			/* 0 or 1000 specअगरies normal speed,
			   1 specअगरies क्रमward single stepping,
			   -1 specअगरies backward single stepping,
			   >1: playback at speed/1000 of the normal speed,
			   <-1: reverse playback at (-speed/1000) of the normal speed. */
			__s32 speed;
			__u32 क्रमmat;
		पूर्ण start;

		काष्ठा अणु
			__u32 data[16];
		पूर्ण raw;
	पूर्ण;
पूर्ण;
#पूर्ण_अगर


/*
 *	D A T A   S E R V I C E S   ( V B I )
 *
 *	Data services API by Michael Schimek
 */

/* Raw VBI */
काष्ठा v4l2_vbi_क्रमmat अणु
	__u32	sampling_rate;		/* in 1 Hz */
	__u32	offset;
	__u32	samples_per_line;
	__u32	sample_क्रमmat;		/* V4L2_PIX_FMT_* */
	__s32	start[2];
	__u32	count[2];
	__u32	flags;			/* V4L2_VBI_* */
	__u32	reserved[2];		/* must be zero */
पूर्ण;

/*  VBI flags  */
#घोषणा V4L2_VBI_UNSYNC		(1 << 0)
#घोषणा V4L2_VBI_INTERLACED	(1 << 1)

/* ITU-R start lines क्रम each field */
#घोषणा V4L2_VBI_ITU_525_F1_START (1)
#घोषणा V4L2_VBI_ITU_525_F2_START (264)
#घोषणा V4L2_VBI_ITU_625_F1_START (1)
#घोषणा V4L2_VBI_ITU_625_F2_START (314)

/* Sliced VBI
 *
 *    This implements is a proposal V4L2 API to allow SLICED VBI
 * required क्रम some hardware encoders. It should change without
 * notice in the definitive implementation.
 */

काष्ठा v4l2_sliced_vbi_क्रमmat अणु
	__u16   service_set;
	/* service_lines[0][...] specअगरies lines 0-23 (1-23 used) of the first field
	   service_lines[1][...] specअगरies lines 0-23 (1-23 used) of the second field
				 (equals frame lines 313-336 क्रम 625 line video
				  standards, 263-286 क्रम 525 line standards) */
	__u16   service_lines[2][24];
	__u32   io_size;
	__u32   reserved[2];            /* must be zero */
पूर्ण;

/* Teletext World System Teletext
   (WST), defined on ITU-R BT.653-2 */
#घोषणा V4L2_SLICED_TELETEXT_B          (0x0001)
/* Video Program System, defined on ETS 300 231*/
#घोषणा V4L2_SLICED_VPS                 (0x0400)
/* Closed Caption, defined on EIA-608 */
#घोषणा V4L2_SLICED_CAPTION_525         (0x1000)
/* Wide Screen System, defined on ITU-R BT1119.1 */
#घोषणा V4L2_SLICED_WSS_625             (0x4000)

#घोषणा V4L2_SLICED_VBI_525             (V4L2_SLICED_CAPTION_525)
#घोषणा V4L2_SLICED_VBI_625             (V4L2_SLICED_TELETEXT_B | V4L2_SLICED_VPS | V4L2_SLICED_WSS_625)

काष्ठा v4l2_sliced_vbi_cap अणु
	__u16   service_set;
	/* service_lines[0][...] specअगरies lines 0-23 (1-23 used) of the first field
	   service_lines[1][...] specअगरies lines 0-23 (1-23 used) of the second field
				 (equals frame lines 313-336 क्रम 625 line video
				  standards, 263-286 क्रम 525 line standards) */
	__u16   service_lines[2][24];
	__u32	type;		/* क्रमागत v4l2_buf_type */
	__u32   reserved[3];    /* must be 0 */
पूर्ण;

काष्ठा v4l2_sliced_vbi_data अणु
	__u32   id;
	__u32   field;          /* 0: first field, 1: second field */
	__u32   line;           /* 1-23 */
	__u32   reserved;       /* must be 0 */
	__u8    data[48];
पूर्ण;

/*
 * Sliced VBI data inserted पूर्णांकo MPEG Streams
 */

/*
 * V4L2_MPEG_STREAM_VBI_FMT_IVTV:
 *
 * Structure of payload contained in an MPEG 2 Private Stream 1 PES Packet in an
 * MPEG-2 Program Pack that contains V4L2_MPEG_STREAM_VBI_FMT_IVTV Sliced VBI
 * data
 *
 * Note, the MPEG-2 Program Pack and Private Stream 1 PES packet header
 * definitions are not included here.  See the MPEG-2 specअगरications क्रम details
 * on these headers.
 */

/* Line type IDs */
#घोषणा V4L2_MPEG_VBI_IVTV_TELETEXT_B     (1)
#घोषणा V4L2_MPEG_VBI_IVTV_CAPTION_525    (4)
#घोषणा V4L2_MPEG_VBI_IVTV_WSS_625        (5)
#घोषणा V4L2_MPEG_VBI_IVTV_VPS            (7)

काष्ठा v4l2_mpeg_vbi_itv0_line अणु
	__u8 id;	/* One of V4L2_MPEG_VBI_IVTV_* above */
	__u8 data[42];	/* Sliced VBI data क्रम the line */
पूर्ण __attribute__ ((packed));

काष्ठा v4l2_mpeg_vbi_itv0 अणु
	__le32 linemask[2]; /* Biपंचांगasks of VBI service lines present */
	काष्ठा v4l2_mpeg_vbi_itv0_line line[35];
पूर्ण __attribute__ ((packed));

काष्ठा v4l2_mpeg_vbi_ITV0 अणु
	काष्ठा v4l2_mpeg_vbi_itv0_line line[36];
पूर्ण __attribute__ ((packed));

#घोषणा V4L2_MPEG_VBI_IVTV_MAGIC0	"itv0"
#घोषणा V4L2_MPEG_VBI_IVTV_MAGIC1	"ITV0"

काष्ठा v4l2_mpeg_vbi_fmt_ivtv अणु
	__u8 magic[4];
	जोड़ अणु
		काष्ठा v4l2_mpeg_vbi_itv0 itv0;
		काष्ठा v4l2_mpeg_vbi_ITV0 ITV0;
	पूर्ण;
पूर्ण __attribute__ ((packed));

/*
 *	A G G R E G A T E   S T R U C T U R E S
 */

/**
 * काष्ठा v4l2_plane_pix_क्रमmat - additional, per-plane क्रमmat definition
 * @sizeimage:		maximum size in bytes required क्रम data, क्रम which
 *			this plane will be used
 * @bytesperline:	distance in bytes between the lefपंचांगost pixels in two
 *			adjacent lines
 * @reserved:		drivers and applications must zero this array
 */
काष्ठा v4l2_plane_pix_क्रमmat अणु
	__u32		sizeimage;
	__u32		bytesperline;
	__u16		reserved[6];
पूर्ण __attribute__ ((packed));

/**
 * काष्ठा v4l2_pix_क्रमmat_mplane - multiplanar क्रमmat definition
 * @width:		image width in pixels
 * @height:		image height in pixels
 * @pixelक्रमmat:	little endian four अक्षरacter code (fourcc)
 * @field:		क्रमागत v4l2_field; field order (क्रम पूर्णांकerlaced video)
 * @colorspace:		क्रमागत v4l2_colorspace; supplemental to pixelक्रमmat
 * @plane_fmt:		per-plane inक्रमmation
 * @num_planes:		number of planes क्रम this क्रमmat
 * @flags:		क्रमmat flags (V4L2_PIX_FMT_FLAG_*)
 * @ycbcr_enc:		क्रमागत v4l2_ycbcr_encoding, Y'CbCr encoding
 * @hsv_enc:		क्रमागत v4l2_hsv_encoding, HSV encoding
 * @quantization:	क्रमागत v4l2_quantization, colorspace quantization
 * @xfer_func:		क्रमागत v4l2_xfer_func, colorspace transfer function
 * @reserved:		drivers and applications must zero this array
 */
काष्ठा v4l2_pix_क्रमmat_mplane अणु
	__u32				width;
	__u32				height;
	__u32				pixelक्रमmat;
	__u32				field;
	__u32				colorspace;

	काष्ठा v4l2_plane_pix_क्रमmat	plane_fmt[VIDEO_MAX_PLANES];
	__u8				num_planes;
	__u8				flags;
	 जोड़ अणु
		__u8				ycbcr_enc;
		__u8				hsv_enc;
	पूर्ण;
	__u8				quantization;
	__u8				xfer_func;
	__u8				reserved[7];
पूर्ण __attribute__ ((packed));

/**
 * काष्ठा v4l2_sdr_क्रमmat - SDR क्रमmat definition
 * @pixelक्रमmat:	little endian four अक्षरacter code (fourcc)
 * @buffersize:		maximum size in bytes required क्रम data
 * @reserved:		drivers and applications must zero this array
 */
काष्ठा v4l2_sdr_क्रमmat अणु
	__u32				pixelक्रमmat;
	__u32				buffersize;
	__u8				reserved[24];
पूर्ण __attribute__ ((packed));

/**
 * काष्ठा v4l2_meta_क्रमmat - metadata क्रमmat definition
 * @dataक्रमmat:		little endian four अक्षरacter code (fourcc)
 * @buffersize:		maximum size in bytes required क्रम data
 */
काष्ठा v4l2_meta_क्रमmat अणु
	__u32				dataक्रमmat;
	__u32				buffersize;
पूर्ण __attribute__ ((packed));

/**
 * काष्ठा v4l2_क्रमmat - stream data क्रमmat
 * @type:	क्रमागत v4l2_buf_type; type of the data stream
 * @pix:	definition of an image क्रमmat
 * @pix_mp:	definition of a multiplanar image क्रमmat
 * @win:	definition of an overlaid image
 * @vbi:	raw VBI capture or output parameters
 * @sliced:	sliced VBI capture or output parameters
 * @raw_data:	placeholder क्रम future extensions and custom क्रमmats
 * @fmt:	जोड़ of @pix, @pix_mp, @win, @vbi, @sliced, @sdr, @meta
 *		and @raw_data
 */
काष्ठा v4l2_क्रमmat अणु
	__u32	 type;
	जोड़ अणु
		काष्ठा v4l2_pix_क्रमmat		pix;     /* V4L2_BUF_TYPE_VIDEO_CAPTURE */
		काष्ठा v4l2_pix_क्रमmat_mplane	pix_mp;  /* V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE */
		काष्ठा v4l2_winकरोw		win;     /* V4L2_BUF_TYPE_VIDEO_OVERLAY */
		काष्ठा v4l2_vbi_क्रमmat		vbi;     /* V4L2_BUF_TYPE_VBI_CAPTURE */
		काष्ठा v4l2_sliced_vbi_क्रमmat	sliced;  /* V4L2_BUF_TYPE_SLICED_VBI_CAPTURE */
		काष्ठा v4l2_sdr_क्रमmat		sdr;     /* V4L2_BUF_TYPE_SDR_CAPTURE */
		काष्ठा v4l2_meta_क्रमmat		meta;    /* V4L2_BUF_TYPE_META_CAPTURE */
		__u8	raw_data[200];                   /* user-defined */
	पूर्ण fmt;
पूर्ण;

/*	Stream type-dependent parameters
 */
काष्ठा v4l2_streamparm अणु
	__u32	 type;			/* क्रमागत v4l2_buf_type */
	जोड़ अणु
		काष्ठा v4l2_captureparm	capture;
		काष्ठा v4l2_outputparm	output;
		__u8	raw_data[200];  /* user-defined */
	पूर्ण parm;
पूर्ण;

/*
 *	E V E N T S
 */

#घोषणा V4L2_EVENT_ALL				0
#घोषणा V4L2_EVENT_VSYNC			1
#घोषणा V4L2_EVENT_EOS				2
#घोषणा V4L2_EVENT_CTRL				3
#घोषणा V4L2_EVENT_FRAME_SYNC			4
#घोषणा V4L2_EVENT_SOURCE_CHANGE		5
#घोषणा V4L2_EVENT_MOTION_DET			6
#घोषणा V4L2_EVENT_PRIVATE_START		0x08000000

/* Payload क्रम V4L2_EVENT_VSYNC */
काष्ठा v4l2_event_vsync अणु
	/* Can be V4L2_FIELD_ANY, _NONE, _TOP or _BOTTOM */
	__u8 field;
पूर्ण __attribute__ ((packed));

/* Payload क्रम V4L2_EVENT_CTRL */
#घोषणा V4L2_EVENT_CTRL_CH_VALUE		(1 << 0)
#घोषणा V4L2_EVENT_CTRL_CH_FLAGS		(1 << 1)
#घोषणा V4L2_EVENT_CTRL_CH_RANGE		(1 << 2)

काष्ठा v4l2_event_ctrl अणु
	__u32 changes;
	__u32 type;
	जोड़ अणु
		__s32 value;
		__s64 value64;
	पूर्ण;
	__u32 flags;
	__s32 minimum;
	__s32 maximum;
	__s32 step;
	__s32 शेष_value;
पूर्ण;

काष्ठा v4l2_event_frame_sync अणु
	__u32 frame_sequence;
पूर्ण;

#घोषणा V4L2_EVENT_SRC_CH_RESOLUTION		(1 << 0)

काष्ठा v4l2_event_src_change अणु
	__u32 changes;
पूर्ण;

#घोषणा V4L2_EVENT_MD_FL_HAVE_FRAME_SEQ	(1 << 0)

/**
 * काष्ठा v4l2_event_motion_det - motion detection event
 * @flags:             अगर V4L2_EVENT_MD_FL_HAVE_FRAME_SEQ is set, then the
 *                     frame_sequence field is valid.
 * @frame_sequence:    the frame sequence number associated with this event.
 * @region_mask:       which regions detected motion.
 */
काष्ठा v4l2_event_motion_det अणु
	__u32 flags;
	__u32 frame_sequence;
	__u32 region_mask;
पूर्ण;

काष्ठा v4l2_event अणु
	__u32				type;
	जोड़ अणु
		काष्ठा v4l2_event_vsync		vsync;
		काष्ठा v4l2_event_ctrl		ctrl;
		काष्ठा v4l2_event_frame_sync	frame_sync;
		काष्ठा v4l2_event_src_change	src_change;
		काष्ठा v4l2_event_motion_det	motion_det;
		__u8				data[64];
	पूर्ण u;
	__u32				pending;
	__u32				sequence;
#अगर_घोषित __KERNEL__
	काष्ठा __kernel_बारpec	बारtamp;
#अन्यथा
	काष्ठा बारpec			बारtamp;
#पूर्ण_अगर
	__u32				id;
	__u32				reserved[8];
पूर्ण;

#घोषणा V4L2_EVENT_SUB_FL_SEND_INITIAL		(1 << 0)
#घोषणा V4L2_EVENT_SUB_FL_ALLOW_FEEDBACK	(1 << 1)

काष्ठा v4l2_event_subscription अणु
	__u32				type;
	__u32				id;
	__u32				flags;
	__u32				reserved[5];
पूर्ण;

/*
 *	A D V A N C E D   D E B U G G I N G
 *
 *	NOTE: EXPERIMENTAL API, NEVER RELY ON THIS IN APPLICATIONS!
 *	FOR DEBUGGING, TESTING AND INTERNAL USE ONLY!
 */

/* VIDIOC_DBG_G_REGISTER and VIDIOC_DBG_S_REGISTER */

#घोषणा V4L2_CHIP_MATCH_BRIDGE      0  /* Match against chip ID on the bridge (0 क्रम the bridge) */
#घोषणा V4L2_CHIP_MATCH_SUBDEV      4  /* Match against subdev index */

/* The following four defines are no दीर्घer in use */
#घोषणा V4L2_CHIP_MATCH_HOST V4L2_CHIP_MATCH_BRIDGE
#घोषणा V4L2_CHIP_MATCH_I2C_DRIVER  1  /* Match against I2C driver name */
#घोषणा V4L2_CHIP_MATCH_I2C_ADDR    2  /* Match against I2C 7-bit address */
#घोषणा V4L2_CHIP_MATCH_AC97        3  /* Match against ancillary AC97 chip */

काष्ठा v4l2_dbg_match अणु
	__u32 type; /* Match type */
	जोड़ अणु     /* Match this chip, meaning determined by type */
		__u32 addr;
		अक्षर name[32];
	पूर्ण;
पूर्ण __attribute__ ((packed));

काष्ठा v4l2_dbg_रेजिस्टर अणु
	काष्ठा v4l2_dbg_match match;
	__u32 size;	/* रेजिस्टर size in bytes */
	__u64 reg;
	__u64 val;
पूर्ण __attribute__ ((packed));

#घोषणा V4L2_CHIP_FL_READABLE (1 << 0)
#घोषणा V4L2_CHIP_FL_WRITABLE (1 << 1)

/* VIDIOC_DBG_G_CHIP_INFO */
काष्ठा v4l2_dbg_chip_info अणु
	काष्ठा v4l2_dbg_match match;
	अक्षर name[32];
	__u32 flags;
	__u32 reserved[32];
पूर्ण __attribute__ ((packed));

/**
 * काष्ठा v4l2_create_buffers - VIDIOC_CREATE_BUFS argument
 * @index:	on वापस, index of the first created buffer
 * @count:	entry: number of requested buffers,
 *		वापस: number of created buffers
 * @memory:	क्रमागत v4l2_memory; buffer memory type
 * @क्रमmat:	frame क्रमmat, क्रम which buffers are requested
 * @capabilities: capabilities of this buffer type.
 * @reserved:	future extensions
 */
काष्ठा v4l2_create_buffers अणु
	__u32			index;
	__u32			count;
	__u32			memory;
	काष्ठा v4l2_क्रमmat	क्रमmat;
	__u32			capabilities;
	__u32			reserved[7];
पूर्ण;

/*
 *	I O C T L   C O D E S   F O R   V I D E O   D E V I C E S
 *
 */
#घोषणा VIDIOC_QUERYCAP		 _IOR('V',  0, काष्ठा v4l2_capability)
#घोषणा VIDIOC_ENUM_FMT         _IOWR('V',  2, काष्ठा v4l2_fmtdesc)
#घोषणा VIDIOC_G_FMT		_IOWR('V',  4, काष्ठा v4l2_क्रमmat)
#घोषणा VIDIOC_S_FMT		_IOWR('V',  5, काष्ठा v4l2_क्रमmat)
#घोषणा VIDIOC_REQBUFS		_IOWR('V',  8, काष्ठा v4l2_requestbuffers)
#घोषणा VIDIOC_QUERYBUF		_IOWR('V',  9, काष्ठा v4l2_buffer)
#घोषणा VIDIOC_G_FBUF		 _IOR('V', 10, काष्ठा v4l2_framebuffer)
#घोषणा VIDIOC_S_FBUF		 _IOW('V', 11, काष्ठा v4l2_framebuffer)
#घोषणा VIDIOC_OVERLAY		 _IOW('V', 14, पूर्णांक)
#घोषणा VIDIOC_QBUF		_IOWR('V', 15, काष्ठा v4l2_buffer)
#घोषणा VIDIOC_EXPBUF		_IOWR('V', 16, काष्ठा v4l2_exportbuffer)
#घोषणा VIDIOC_DQBUF		_IOWR('V', 17, काष्ठा v4l2_buffer)
#घोषणा VIDIOC_STREAMON		 _IOW('V', 18, पूर्णांक)
#घोषणा VIDIOC_STREAMOFF	 _IOW('V', 19, पूर्णांक)
#घोषणा VIDIOC_G_PARM		_IOWR('V', 21, काष्ठा v4l2_streamparm)
#घोषणा VIDIOC_S_PARM		_IOWR('V', 22, काष्ठा v4l2_streamparm)
#घोषणा VIDIOC_G_STD		 _IOR('V', 23, v4l2_std_id)
#घोषणा VIDIOC_S_STD		 _IOW('V', 24, v4l2_std_id)
#घोषणा VIDIOC_ENUMSTD		_IOWR('V', 25, काष्ठा v4l2_standard)
#घोषणा VIDIOC_ENUMINPUT	_IOWR('V', 26, काष्ठा v4l2_input)
#घोषणा VIDIOC_G_CTRL		_IOWR('V', 27, काष्ठा v4l2_control)
#घोषणा VIDIOC_S_CTRL		_IOWR('V', 28, काष्ठा v4l2_control)
#घोषणा VIDIOC_G_TUNER		_IOWR('V', 29, काष्ठा v4l2_tuner)
#घोषणा VIDIOC_S_TUNER		 _IOW('V', 30, काष्ठा v4l2_tuner)
#घोषणा VIDIOC_G_AUDIO		 _IOR('V', 33, काष्ठा v4l2_audio)
#घोषणा VIDIOC_S_AUDIO		 _IOW('V', 34, काष्ठा v4l2_audio)
#घोषणा VIDIOC_QUERYCTRL	_IOWR('V', 36, काष्ठा v4l2_queryctrl)
#घोषणा VIDIOC_QUERYMENU	_IOWR('V', 37, काष्ठा v4l2_querymenu)
#घोषणा VIDIOC_G_INPUT		 _IOR('V', 38, पूर्णांक)
#घोषणा VIDIOC_S_INPUT		_IOWR('V', 39, पूर्णांक)
#घोषणा VIDIOC_G_EDID		_IOWR('V', 40, काष्ठा v4l2_edid)
#घोषणा VIDIOC_S_EDID		_IOWR('V', 41, काष्ठा v4l2_edid)
#घोषणा VIDIOC_G_OUTPUT		 _IOR('V', 46, पूर्णांक)
#घोषणा VIDIOC_S_OUTPUT		_IOWR('V', 47, पूर्णांक)
#घोषणा VIDIOC_ENUMOUTPUT	_IOWR('V', 48, काष्ठा v4l2_output)
#घोषणा VIDIOC_G_AUDOUT		 _IOR('V', 49, काष्ठा v4l2_audioout)
#घोषणा VIDIOC_S_AUDOUT		 _IOW('V', 50, काष्ठा v4l2_audioout)
#घोषणा VIDIOC_G_MODULATOR	_IOWR('V', 54, काष्ठा v4l2_modulator)
#घोषणा VIDIOC_S_MODULATOR	 _IOW('V', 55, काष्ठा v4l2_modulator)
#घोषणा VIDIOC_G_FREQUENCY	_IOWR('V', 56, काष्ठा v4l2_frequency)
#घोषणा VIDIOC_S_FREQUENCY	 _IOW('V', 57, काष्ठा v4l2_frequency)
#घोषणा VIDIOC_CROPCAP		_IOWR('V', 58, काष्ठा v4l2_cropcap)
#घोषणा VIDIOC_G_CROP		_IOWR('V', 59, काष्ठा v4l2_crop)
#घोषणा VIDIOC_S_CROP		 _IOW('V', 60, काष्ठा v4l2_crop)
#घोषणा VIDIOC_G_JPEGCOMP	 _IOR('V', 61, काष्ठा v4l2_jpegcompression)
#घोषणा VIDIOC_S_JPEGCOMP	 _IOW('V', 62, काष्ठा v4l2_jpegcompression)
#घोषणा VIDIOC_QUERYSTD		 _IOR('V', 63, v4l2_std_id)
#घोषणा VIDIOC_TRY_FMT		_IOWR('V', 64, काष्ठा v4l2_क्रमmat)
#घोषणा VIDIOC_ENUMAUDIO	_IOWR('V', 65, काष्ठा v4l2_audio)
#घोषणा VIDIOC_ENUMAUDOUT	_IOWR('V', 66, काष्ठा v4l2_audioout)
#घोषणा VIDIOC_G_PRIORITY	 _IOR('V', 67, __u32) /* क्रमागत v4l2_priority */
#घोषणा VIDIOC_S_PRIORITY	 _IOW('V', 68, __u32) /* क्रमागत v4l2_priority */
#घोषणा VIDIOC_G_SLICED_VBI_CAP _IOWR('V', 69, काष्ठा v4l2_sliced_vbi_cap)
#घोषणा VIDIOC_LOG_STATUS         _IO('V', 70)
#घोषणा VIDIOC_G_EXT_CTRLS	_IOWR('V', 71, काष्ठा v4l2_ext_controls)
#घोषणा VIDIOC_S_EXT_CTRLS	_IOWR('V', 72, काष्ठा v4l2_ext_controls)
#घोषणा VIDIOC_TRY_EXT_CTRLS	_IOWR('V', 73, काष्ठा v4l2_ext_controls)
#घोषणा VIDIOC_ENUM_FRAMESIZES	_IOWR('V', 74, काष्ठा v4l2_frmsizeक्रमागत)
#घोषणा VIDIOC_ENUM_FRAMEINTERVALS _IOWR('V', 75, काष्ठा v4l2_frmivalक्रमागत)
#घोषणा VIDIOC_G_ENC_INDEX       _IOR('V', 76, काष्ठा v4l2_enc_idx)
#घोषणा VIDIOC_ENCODER_CMD      _IOWR('V', 77, काष्ठा v4l2_encoder_cmd)
#घोषणा VIDIOC_TRY_ENCODER_CMD  _IOWR('V', 78, काष्ठा v4l2_encoder_cmd)

/*
 * Experimental, meant क्रम debugging, testing and पूर्णांकernal use.
 * Only implemented अगर CONFIG_VIDEO_ADV_DEBUG is defined.
 * You must be root to use these ioctls. Never use these in applications!
 */
#घोषणा	VIDIOC_DBG_S_REGISTER	 _IOW('V', 79, काष्ठा v4l2_dbg_रेजिस्टर)
#घोषणा	VIDIOC_DBG_G_REGISTER	_IOWR('V', 80, काष्ठा v4l2_dbg_रेजिस्टर)

#घोषणा VIDIOC_S_HW_FREQ_SEEK	 _IOW('V', 82, काष्ठा v4l2_hw_freq_seek)
#घोषणा	VIDIOC_S_DV_TIMINGS	_IOWR('V', 87, काष्ठा v4l2_dv_timings)
#घोषणा	VIDIOC_G_DV_TIMINGS	_IOWR('V', 88, काष्ठा v4l2_dv_timings)
#घोषणा	VIDIOC_DQEVENT		 _IOR('V', 89, काष्ठा v4l2_event)
#घोषणा	VIDIOC_SUBSCRIBE_EVENT	 _IOW('V', 90, काष्ठा v4l2_event_subscription)
#घोषणा	VIDIOC_UNSUBSCRIBE_EVENT _IOW('V', 91, काष्ठा v4l2_event_subscription)
#घोषणा VIDIOC_CREATE_BUFS	_IOWR('V', 92, काष्ठा v4l2_create_buffers)
#घोषणा VIDIOC_PREPARE_BUF	_IOWR('V', 93, काष्ठा v4l2_buffer)
#घोषणा VIDIOC_G_SELECTION	_IOWR('V', 94, काष्ठा v4l2_selection)
#घोषणा VIDIOC_S_SELECTION	_IOWR('V', 95, काष्ठा v4l2_selection)
#घोषणा VIDIOC_DECODER_CMD	_IOWR('V', 96, काष्ठा v4l2_decoder_cmd)
#घोषणा VIDIOC_TRY_DECODER_CMD	_IOWR('V', 97, काष्ठा v4l2_decoder_cmd)
#घोषणा VIDIOC_ENUM_DV_TIMINGS  _IOWR('V', 98, काष्ठा v4l2_क्रमागत_dv_timings)
#घोषणा VIDIOC_QUERY_DV_TIMINGS  _IOR('V', 99, काष्ठा v4l2_dv_timings)
#घोषणा VIDIOC_DV_TIMINGS_CAP   _IOWR('V', 100, काष्ठा v4l2_dv_timings_cap)
#घोषणा VIDIOC_ENUM_FREQ_BANDS	_IOWR('V', 101, काष्ठा v4l2_frequency_band)

/*
 * Experimental, meant क्रम debugging, testing and पूर्णांकernal use.
 * Never use this in applications!
 */
#घोषणा VIDIOC_DBG_G_CHIP_INFO  _IOWR('V', 102, काष्ठा v4l2_dbg_chip_info)

#घोषणा VIDIOC_QUERY_EXT_CTRL	_IOWR('V', 103, काष्ठा v4l2_query_ext_ctrl)

/* Reminder: when adding new ioctls please add support क्रम them to
   drivers/media/v4l2-core/v4l2-compat-ioctl32.c as well! */

#घोषणा BASE_VIDIOC_PRIVATE	192		/* 192-255 are निजी */

#पूर्ण_अगर /* _UAPI__LINUX_VIDEODEV2_H */
