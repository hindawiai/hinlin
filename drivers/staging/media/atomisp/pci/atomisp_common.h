<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Medअगरield PNW Camera Imaging ISP subप्रणाली.
 *
 * Copyright (c) 2010 Intel Corporation. All Rights Reserved.
 *
 * Copyright (c) 2010 Silicon Hive www.siliconhive.com.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 *
 */

#अगर_अघोषित	__ATOMISP_COMMON_H__
#घोषणा	__ATOMISP_COMMON_H__

#समावेश "../../include/linux/atomisp.h"

#समावेश <linux/v4l2-mediabus.h>

#समावेश <media/videobuf-core.h>

#समावेश "atomisp_compat.h"

#समावेश "ia_css.h"

बाह्य पूर्णांक dbg_level;
बाह्य पूर्णांक dbg_func;
बाह्य पूर्णांक mipicsi_flag;
बाह्य पूर्णांक pad_w;
बाह्य पूर्णांक pad_h;

#घोषणा CSS_DTRACE_VERBOSITY_LEVEL	5	/* Controls trace verbosity */
#घोषणा CSS_DTRACE_VERBOSITY_TIMEOUT	9	/* Verbosity on ISP समयout */
#घोषणा MRFLD_MAX_ZOOM_FACTOR	1024

/* ISP2401 */
#घोषणा ATOMISP_CSS_ISP_PIPE_VERSION_2_7    1

काष्ठा atomisp_क्रमmat_bridge अणु
	अचिन्हित पूर्णांक pixelक्रमmat;
	अचिन्हित पूर्णांक depth;
	u32 mbus_code;
	क्रमागत ia_css_frame_क्रमmat sh_fmt;
	अचिन्हित अक्षर description[32];	/* the same as काष्ठा v4l2_fmtdesc */
	bool planar;
पूर्ण;

काष्ठा atomisp_fmt अणु
	u32 pixelक्रमmat;
	u32 depth;
	u32 bytesperline;
	u32 framesize;
	u32 imagesize;
	u32 width;
	u32 height;
	u32 bayer_order;
पूर्ण;

काष्ठा atomisp_buffer अणु
	काष्ठा videobuf_buffer	vb;
पूर्ण;

#पूर्ण_अगर
