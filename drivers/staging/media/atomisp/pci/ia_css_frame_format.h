<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#अगर_अघोषित __IA_CSS_FRAME_FORMAT_H
#घोषणा __IA_CSS_FRAME_FORMAT_H

/* @file
 * This file contains inक्रमmation about क्रमmats supported in the ISP
 */

/* Frame क्रमmats, some of these come from fourcc.org, others are
   better explained by video4linux2. The NV11 seems to be described only
   on MSDN pages, but even those seem to be gone now.
   Frames can come in many क्रमms, the मुख्य categories are RAW, RGB and YUV
   (or YCbCr). The YUV frames come in 4 flavors, determined by how the U and V
   values are subsampled:
   1. YUV420: hor = 2, ver = 2
   2. YUV411: hor = 4, ver = 1
   3. YUV422: hor = 2, ver = 1
   4. YUV444: hor = 1, ver = 1

  Warning: not all frame क्रमmats are supported as input or output to/from ISP.
    Some of these क्रमmats are thereक्रमe not defined in the output table module.
    Modअगरications in below frame क्रमmat क्रमागत can require modअगरications in the
    output table module.

  Warning2: Throughout the CSS code assumptions are made on the order
	of क्रमmats in this क्रमागतeration type, or some sort of copy is मुख्यtained.
	The following files are identअगरied:
	- FileSupport.h
	- css/isp/kernels/fc/fc_1.0/क्रमmats.isp.c
	- css/isp/kernels/output/output_1.0/output_table.isp.c
	- css/isp/kernels/output/sc_output_1.0/क्रमmats.hive.c
	- css/isp/modes/पूर्णांकerface/isp_क्रमmats.isp.h
	- css/bxt_sandbox/psyspoc/पूर्णांकerface/ia_css_pg_info.h
	- css/bxt_sandbox/psysapi/data/पूर्णांकerface/ia_css_program_group_data.h
	- css/bxt_sandbox/isysapi/पूर्णांकerface/ia_css_isysapi_fw_types.h
*/
क्रमागत ia_css_frame_क्रमmat अणु
	IA_CSS_FRAME_FORMAT_NV11 = 0,   /** 12 bit YUV 411, Y, UV plane */
	IA_CSS_FRAME_FORMAT_NV12,       /** 12 bit YUV 420, Y, UV plane */
	IA_CSS_FRAME_FORMAT_NV12_16,    /** 16 bit YUV 420, Y, UV plane */
	IA_CSS_FRAME_FORMAT_NV12_TILEY, /** 12 bit YUV 420, Intel proprietary tiled क्रमmat, TileY */
	IA_CSS_FRAME_FORMAT_NV16,       /** 16 bit YUV 422, Y, UV plane */
	IA_CSS_FRAME_FORMAT_NV21,       /** 12 bit YUV 420, Y, VU plane */
	IA_CSS_FRAME_FORMAT_NV61,       /** 16 bit YUV 422, Y, VU plane */
	IA_CSS_FRAME_FORMAT_YV12,       /** 12 bit YUV 420, Y, V, U plane */
	IA_CSS_FRAME_FORMAT_YV16,       /** 16 bit YUV 422, Y, V, U plane */
	IA_CSS_FRAME_FORMAT_YUV420,     /** 12 bit YUV 420, Y, U, V plane */
	IA_CSS_FRAME_FORMAT_YUV420_16,  /** yuv420, 16 bits per subpixel */
	IA_CSS_FRAME_FORMAT_YUV422,     /** 16 bit YUV 422, Y, U, V plane */
	IA_CSS_FRAME_FORMAT_YUV422_16,  /** yuv422, 16 bits per subpixel */
	IA_CSS_FRAME_FORMAT_UYVY,       /** 16 bit YUV 422, UYVY पूर्णांकerleaved */
	IA_CSS_FRAME_FORMAT_YUYV,       /** 16 bit YUV 422, YUYV पूर्णांकerleaved */
	IA_CSS_FRAME_FORMAT_YUV444,     /** 24 bit YUV 444, Y, U, V plane */
	IA_CSS_FRAME_FORMAT_YUV_LINE,   /** Internal क्रमmat, 2 y lines followed
					     by a uvपूर्णांकerleaved line */
	IA_CSS_FRAME_FORMAT_RAW,	/** RAW, 1 plane */
	IA_CSS_FRAME_FORMAT_RGB565,     /** 16 bit RGB, 1 plane. Each 3 sub
					     pixels are packed पूर्णांकo one 16 bit
					     value, 5 bits क्रम R, 6 bits क्रम G
					     and 5 bits क्रम B. */
	IA_CSS_FRAME_FORMAT_PLANAR_RGB888, /** 24 bit RGB, 3 planes */
	IA_CSS_FRAME_FORMAT_RGBA888,	/** 32 bit RGBA, 1 plane, A=Alpha
					     (alpha is unused) */
	IA_CSS_FRAME_FORMAT_QPLANE6, /** Internal, क्रम advanced ISP */
	IA_CSS_FRAME_FORMAT_BINARY_8,	/** byte stream, used क्रम jpeg. For
					     frames of this type, we set the
					     height to 1 and the width to the
					     number of allocated bytes. */
	IA_CSS_FRAME_FORMAT_MIPI,	/** MIPI frame, 1 plane */
	IA_CSS_FRAME_FORMAT_RAW_PACKED, /** RAW, 1 plane, packed */
	IA_CSS_FRAME_FORMAT_CSI_MIPI_YUV420_8,	      /** 8 bit per Y/U/V.
							   Y odd line; UYVY
							   पूर्णांकerleaved even line */
	IA_CSS_FRAME_FORMAT_CSI_MIPI_LEGACY_YUV420_8, /** Legacy YUV420. UY odd
							   line; VY even line */
	IA_CSS_FRAME_FORMAT_CSI_MIPI_YUV420_10       /** 10 bit per Y/U/V. Y odd
							   line; UYVY पूर्णांकerleaved
							   even line */
पूर्ण;

/* NOTE: IA_CSS_FRAME_FORMAT_NUM was purposely defined outside of क्रमागत type ia_css_frame_क्रमmat, */
/*       because of issues this would cause with the Clockwork code checking tool.               */
#घोषणा IA_CSS_FRAME_FORMAT_NUM (IA_CSS_FRAME_FORMAT_CSI_MIPI_YUV420_10 + 1)

/* Number of valid output frame क्रमmats क्रम ISP **/
#घोषणा IA_CSS_FRAME_OUT_FORMAT_NUM	(IA_CSS_FRAME_FORMAT_RGBA888 + 1)

#पूर्ण_अगर /* __IA_CSS_FRAME_FORMAT_H */
