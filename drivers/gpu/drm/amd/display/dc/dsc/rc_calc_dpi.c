<शैली गुरु>
/*
 * Copyright 2012-17 Advanced Micro Devices, Inc.
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
#समावेश "os_types.h"
#समावेश <drm/drm_dsc.h>
#समावेश "dscc_types.h"
#समावेश "rc_calc.h"

अटल व्योम copy_pps_fields(काष्ठा drm_dsc_config *to, स्थिर काष्ठा drm_dsc_config *from)
अणु
	to->line_buf_depth           = from->line_buf_depth;
	to->bits_per_component       = from->bits_per_component;
	to->convert_rgb              = from->convert_rgb;
	to->slice_width              = from->slice_width;
	to->slice_height             = from->slice_height;
	to->simple_422               = from->simple_422;
	to->native_422               = from->native_422;
	to->native_420               = from->native_420;
	to->pic_width                = from->pic_width;
	to->pic_height               = from->pic_height;
	to->rc_tgt_offset_high       = from->rc_tgt_offset_high;
	to->rc_tgt_offset_low        = from->rc_tgt_offset_low;
	to->bits_per_pixel           = from->bits_per_pixel;
	to->rc_edge_factor           = from->rc_edge_factor;
	to->rc_quant_incr_limit1     = from->rc_quant_incr_limit1;
	to->rc_quant_incr_limit0     = from->rc_quant_incr_limit0;
	to->initial_xmit_delay       = from->initial_xmit_delay;
	to->initial_dec_delay        = from->initial_dec_delay;
	to->block_pred_enable        = from->block_pred_enable;
	to->first_line_bpg_offset    = from->first_line_bpg_offset;
	to->second_line_bpg_offset   = from->second_line_bpg_offset;
	to->initial_offset           = from->initial_offset;
	स_नकल(&to->rc_buf_thresh, &from->rc_buf_thresh, माप(from->rc_buf_thresh));
	स_नकल(&to->rc_range_params, &from->rc_range_params, माप(from->rc_range_params));
	to->rc_model_size            = from->rc_model_size;
	to->flatness_min_qp          = from->flatness_min_qp;
	to->flatness_max_qp          = from->flatness_max_qp;
	to->initial_scale_value      = from->initial_scale_value;
	to->scale_decrement_पूर्णांकerval = from->scale_decrement_पूर्णांकerval;
	to->scale_increment_पूर्णांकerval = from->scale_increment_पूर्णांकerval;
	to->nfl_bpg_offset           = from->nfl_bpg_offset;
	to->nsl_bpg_offset           = from->nsl_bpg_offset;
	to->slice_bpg_offset         = from->slice_bpg_offset;
	to->final_offset             = from->final_offset;
	to->vbr_enable               = from->vbr_enable;
	to->slice_chunk_size         = from->slice_chunk_size;
	to->second_line_offset_adj   = from->second_line_offset_adj;
	to->dsc_version_minor        = from->dsc_version_minor;
पूर्ण

अटल व्योम copy_rc_to_cfg(काष्ठा drm_dsc_config *dsc_cfg, स्थिर काष्ठा rc_params *rc)
अणु
	पूर्णांक i;

	dsc_cfg->rc_quant_incr_limit0   = rc->rc_quant_incr_limit0;
	dsc_cfg->rc_quant_incr_limit1   = rc->rc_quant_incr_limit1;
	dsc_cfg->initial_offset         = rc->initial_fullness_offset;
	dsc_cfg->initial_xmit_delay     = rc->initial_xmit_delay;
	dsc_cfg->first_line_bpg_offset  = rc->first_line_bpg_offset;
	dsc_cfg->second_line_bpg_offset = rc->second_line_bpg_offset;
	dsc_cfg->flatness_min_qp        = rc->flatness_min_qp;
	dsc_cfg->flatness_max_qp        = rc->flatness_max_qp;
	क्रम (i = 0; i < QP_SET_SIZE; ++i) अणु
		dsc_cfg->rc_range_params[i].range_min_qp     = rc->qp_min[i];
		dsc_cfg->rc_range_params[i].range_max_qp     = rc->qp_max[i];
		/* Truncate 8-bit चिन्हित value to 6-bit चिन्हित value */
		dsc_cfg->rc_range_params[i].range_bpg_offset = 0x3f & rc->ofs[i];
	पूर्ण
	dsc_cfg->rc_model_size    = rc->rc_model_size;
	dsc_cfg->rc_edge_factor   = rc->rc_edge_factor;
	dsc_cfg->rc_tgt_offset_high = rc->rc_tgt_offset_hi;
	dsc_cfg->rc_tgt_offset_low = rc->rc_tgt_offset_lo;

	क्रम (i = 0; i < QP_SET_SIZE - 1; ++i)
		dsc_cfg->rc_buf_thresh[i] = rc->rc_buf_thresh[i];
पूर्ण

पूर्णांक dscc_compute_dsc_parameters(स्थिर काष्ठा drm_dsc_config *pps, काष्ठा dsc_parameters *dsc_params)
अणु
	पूर्णांक              ret;
	काष्ठा rc_params rc;
	काष्ठा drm_dsc_config   dsc_cfg;

	dsc_params->bytes_per_pixel = calc_dsc_bytes_per_pixel(pps);

	calc_rc_params(&rc, pps);
	dsc_params->pps = *pps;
	dsc_params->pps.initial_scale_value = 8 * rc.rc_model_size / (rc.rc_model_size - rc.initial_fullness_offset);

	copy_pps_fields(&dsc_cfg, &dsc_params->pps);
	copy_rc_to_cfg(&dsc_cfg, &rc);

	dsc_cfg.mux_word_size = dsc_params->pps.bits_per_component <= 10 ? 48 : 64;

	ret = drm_dsc_compute_rc_parameters(&dsc_cfg);

	copy_pps_fields(&dsc_params->pps, &dsc_cfg);
	dsc_params->rc_buffer_model_size = dsc_cfg.rc_bits;
	वापस ret;
पूर्ण

