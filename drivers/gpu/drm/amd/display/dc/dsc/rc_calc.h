<शैली गुरु>

/*
 * Copyright 2017 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */

#अगर_अघोषित __RC_CALC_H__
#घोषणा __RC_CALC_H__


#घोषणा QP_SET_SIZE 15

प्रकार पूर्णांक qp_set[QP_SET_SIZE];

काष्ठा rc_params अणु
	पूर्णांक      rc_quant_incr_limit0;
	पूर्णांक      rc_quant_incr_limit1;
	पूर्णांक      initial_fullness_offset;
	पूर्णांक      initial_xmit_delay;
	पूर्णांक      first_line_bpg_offset;
	पूर्णांक      second_line_bpg_offset;
	पूर्णांक      flatness_min_qp;
	पूर्णांक      flatness_max_qp;
	पूर्णांक      flatness_det_thresh;
	qp_set   qp_min;
	qp_set   qp_max;
	qp_set   ofs;
	पूर्णांक      rc_model_size;
	पूर्णांक      rc_edge_factor;
	पूर्णांक      rc_tgt_offset_hi;
	पूर्णांक      rc_tgt_offset_lo;
	पूर्णांक      rc_buf_thresh[QP_SET_SIZE - 1];
पूर्ण;

क्रमागत colour_mode अणु
	CM_RGB,   /* 444 RGB */
	CM_444,   /* 444 YUV or simple 422 */
	CM_422,   /* native 422 */
	CM_420    /* native 420 */
पूर्ण;

क्रमागत bits_per_comp अणु
	BPC_8  =  8,
	BPC_10 = 10,
	BPC_12 = 12
पूर्ण;

क्रमागत max_min अणु
	DAL_MM_MIN = 0,
	DAL_MM_MAX = 1
पूर्ण;

काष्ठा qp_entry अणु
	भग्न         bpp;
	स्थिर qp_set  qps;
पूर्ण;

प्रकार काष्ठा qp_entry qp_table[];

व्योम calc_rc_params(काष्ठा rc_params *rc, स्थिर काष्ठा drm_dsc_config *pps);
u32 calc_dsc_bytes_per_pixel(स्थिर काष्ठा drm_dsc_config *pps);
u32 calc_dsc_bpp_x16(u32 stream_bandwidth_kbps, u32 pix_clk_100hz,
		     u32 bpp_increment_भाग);

#पूर्ण_अगर

