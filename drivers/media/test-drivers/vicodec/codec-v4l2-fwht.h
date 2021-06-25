<शैली गुरु>
/* SPDX-License-Identअगरier: LGPL-2.1 */
/*
 * Copyright 2018 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#अगर_अघोषित CODEC_V4L2_FWHT_H
#घोषणा CODEC_V4L2_FWHT_H

#समावेश "codec-fwht.h"

काष्ठा v4l2_fwht_pixfmt_info अणु
	u32 id;
	अचिन्हित पूर्णांक bytesperline_mult;
	अचिन्हित पूर्णांक sizeimage_mult;
	अचिन्हित पूर्णांक sizeimage_भाग;
	अचिन्हित पूर्णांक luma_alpha_step;
	अचिन्हित पूर्णांक chroma_step;
	/* Chroma plane subsampling */
	अचिन्हित पूर्णांक width_भाग;
	अचिन्हित पूर्णांक height_भाग;
	अचिन्हित पूर्णांक components_num;
	अचिन्हित पूर्णांक planes_num;
	अचिन्हित पूर्णांक pixenc;
पूर्ण;

काष्ठा v4l2_fwht_state अणु
	स्थिर काष्ठा v4l2_fwht_pixfmt_info *info;
	अचिन्हित पूर्णांक visible_width;
	अचिन्हित पूर्णांक visible_height;
	अचिन्हित पूर्णांक coded_width;
	अचिन्हित पूर्णांक coded_height;
	अचिन्हित पूर्णांक stride;
	अचिन्हित पूर्णांक ref_stride;
	अचिन्हित पूर्णांक gop_size;
	अचिन्हित पूर्णांक gop_cnt;
	u16 i_frame_qp;
	u16 p_frame_qp;

	क्रमागत v4l2_colorspace colorspace;
	क्रमागत v4l2_ycbcr_encoding ycbcr_enc;
	क्रमागत v4l2_xfer_func xfer_func;
	क्रमागत v4l2_quantization quantization;

	काष्ठा fwht_raw_frame ref_frame;
	काष्ठा fwht_cframe_hdr header;
	u8 *compressed_frame;
	u64 ref_frame_ts;
पूर्ण;

स्थिर काष्ठा v4l2_fwht_pixfmt_info *v4l2_fwht_find_pixfmt(u32 pixelक्रमmat);
स्थिर काष्ठा v4l2_fwht_pixfmt_info *v4l2_fwht_get_pixfmt(u32 idx);
bool v4l2_fwht_validate_fmt(स्थिर काष्ठा v4l2_fwht_pixfmt_info *info,
			    u32 width_भाग, u32 height_भाग, u32 components_num,
			    u32 pixenc);
स्थिर काष्ठा v4l2_fwht_pixfmt_info *v4l2_fwht_find_nth_fmt(u32 width_भाग,
							  u32 height_भाग,
							  u32 components_num,
							  u32 pixenc,
							  अचिन्हित पूर्णांक start_idx);

पूर्णांक v4l2_fwht_encode(काष्ठा v4l2_fwht_state *state, u8 *p_in, u8 *p_out);
पूर्णांक v4l2_fwht_decode(काष्ठा v4l2_fwht_state *state, u8 *p_in, u8 *p_out);

#पूर्ण_अगर
