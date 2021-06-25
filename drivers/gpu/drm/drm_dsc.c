<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2018 Intel Corp
 *
 * Author:
 * Manasi Navare <manasi.d.navare@पूर्णांकel.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/byteorder/generic.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_dp_helper.h>
#समावेश <drm/drm_dsc.h>

/**
 * DOC: dsc helpers
 *
 * VESA specअगरication क्रम DP 1.4 adds a new feature called Display Stream
 * Compression (DSC) used to compress the pixel bits beक्रमe sending it on
 * DP/eDP/MIPI DSI पूर्णांकerface. DSC is required to be enabled so that the existing
 * display पूर्णांकerfaces can support high resolutions at higher frames rates uisng
 * the maximum available link capacity of these पूर्णांकerfaces.
 *
 * These functions contain some common logic and helpers to deal with VESA
 * Display Stream Compression standard required क्रम DSC on Display Port/eDP or
 * MIPI display पूर्णांकerfaces.
 */

/**
 * drm_dsc_dp_pps_header_init() - Initializes the PPS Header
 * क्रम DisplayPort as per the DP 1.4 spec.
 * @pps_header: Secondary data packet header क्रम DSC Picture
 *              Parameter Set as defined in &काष्ठा dp_sdp_header
 *
 * DP 1.4 spec defines the secondary data packet क्रम sending the
 * picture parameter infoframes from the source to the sink.
 * This function populates the SDP header defined in
 * &काष्ठा dp_sdp_header.
 */
व्योम drm_dsc_dp_pps_header_init(काष्ठा dp_sdp_header *pps_header)
अणु
	स_रखो(pps_header, 0, माप(*pps_header));

	pps_header->HB1 = DP_SDP_PPS;
	pps_header->HB2 = DP_SDP_PPS_HEADER_PAYLOAD_BYTES_MINUS_1;
पूर्ण
EXPORT_SYMBOL(drm_dsc_dp_pps_header_init);

/**
 * drm_dsc_dp_rc_buffer_size - get rc buffer size in bytes
 * @rc_buffer_block_size: block size code, according to DPCD offset 62h
 * @rc_buffer_size: number of blocks - 1, according to DPCD offset 63h
 *
 * वापस:
 * buffer size in bytes, or 0 on invalid input
 */
पूर्णांक drm_dsc_dp_rc_buffer_size(u8 rc_buffer_block_size, u8 rc_buffer_size)
अणु
	पूर्णांक size = 1024 * (rc_buffer_size + 1);

	चयन (rc_buffer_block_size) अणु
	हाल DP_DSC_RC_BUF_BLK_SIZE_1:
		वापस 1 * size;
	हाल DP_DSC_RC_BUF_BLK_SIZE_4:
		वापस 4 * size;
	हाल DP_DSC_RC_BUF_BLK_SIZE_16:
		वापस 16 * size;
	हाल DP_DSC_RC_BUF_BLK_SIZE_64:
		वापस 64 * size;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_dsc_dp_rc_buffer_size);

/**
 * drm_dsc_pps_payload_pack() - Populates the DSC PPS
 *
 * @pps_payload:
 * Bitwise काष्ठा क्रम DSC Picture Parameter Set. This is defined
 * by &काष्ठा drm_dsc_picture_parameter_set
 * @dsc_cfg:
 * DSC Configuration data filled by driver as defined by
 * &काष्ठा drm_dsc_config
 *
 * DSC source device sends a picture parameter set (PPS) containing the
 * inक्रमmation required by the sink to decode the compressed frame. Driver
 * populates the DSC PPS काष्ठा using the DSC configuration parameters in
 * the order expected by the DSC Display Sink device. For the DSC, the sink
 * device expects the PPS payload in big endian क्रमmat क्रम fields
 * that span more than 1 byte.
 */
व्योम drm_dsc_pps_payload_pack(काष्ठा drm_dsc_picture_parameter_set *pps_payload,
				स्थिर काष्ठा drm_dsc_config *dsc_cfg)
अणु
	पूर्णांक i;

	/* Protect against someone accidently changing काष्ठा size */
	BUILD_BUG_ON(माप(*pps_payload) !=
		     DP_SDP_PPS_HEADER_PAYLOAD_BYTES_MINUS_1 + 1);

	स_रखो(pps_payload, 0, माप(*pps_payload));

	/* PPS 0 */
	pps_payload->dsc_version =
		dsc_cfg->dsc_version_minor |
		dsc_cfg->dsc_version_major << DSC_PPS_VERSION_MAJOR_SHIFT;

	/* PPS 1, 2 is 0 */

	/* PPS 3 */
	pps_payload->pps_3 =
		dsc_cfg->line_buf_depth |
		dsc_cfg->bits_per_component << DSC_PPS_BPC_SHIFT;

	/* PPS 4 */
	pps_payload->pps_4 =
		((dsc_cfg->bits_per_pixel & DSC_PPS_BPP_HIGH_MASK) >>
		 DSC_PPS_MSB_SHIFT) |
		dsc_cfg->vbr_enable << DSC_PPS_VBR_EN_SHIFT |
		dsc_cfg->simple_422 << DSC_PPS_SIMPLE422_SHIFT |
		dsc_cfg->convert_rgb << DSC_PPS_CONVERT_RGB_SHIFT |
		dsc_cfg->block_pred_enable << DSC_PPS_BLOCK_PRED_EN_SHIFT;

	/* PPS 5 */
	pps_payload->bits_per_pixel_low =
		(dsc_cfg->bits_per_pixel & DSC_PPS_LSB_MASK);

	/*
	 * The DSC panel expects the PPS packet to have big endian क्रमmat
	 * क्रम data spanning 2 bytes. Use a macro cpu_to_be16() to convert
	 * to big endian क्रमmat. If क्रमmat is little endian, it will swap
	 * bytes to convert to Big endian अन्यथा keep it unchanged.
	 */

	/* PPS 6, 7 */
	pps_payload->pic_height = cpu_to_be16(dsc_cfg->pic_height);

	/* PPS 8, 9 */
	pps_payload->pic_width = cpu_to_be16(dsc_cfg->pic_width);

	/* PPS 10, 11 */
	pps_payload->slice_height = cpu_to_be16(dsc_cfg->slice_height);

	/* PPS 12, 13 */
	pps_payload->slice_width = cpu_to_be16(dsc_cfg->slice_width);

	/* PPS 14, 15 */
	pps_payload->chunk_size = cpu_to_be16(dsc_cfg->slice_chunk_size);

	/* PPS 16 */
	pps_payload->initial_xmit_delay_high =
		((dsc_cfg->initial_xmit_delay &
		  DSC_PPS_INIT_XMIT_DELAY_HIGH_MASK) >>
		 DSC_PPS_MSB_SHIFT);

	/* PPS 17 */
	pps_payload->initial_xmit_delay_low =
		(dsc_cfg->initial_xmit_delay & DSC_PPS_LSB_MASK);

	/* PPS 18, 19 */
	pps_payload->initial_dec_delay =
		cpu_to_be16(dsc_cfg->initial_dec_delay);

	/* PPS 20 is 0 */

	/* PPS 21 */
	pps_payload->initial_scale_value =
		dsc_cfg->initial_scale_value;

	/* PPS 22, 23 */
	pps_payload->scale_increment_पूर्णांकerval =
		cpu_to_be16(dsc_cfg->scale_increment_पूर्णांकerval);

	/* PPS 24 */
	pps_payload->scale_decrement_पूर्णांकerval_high =
		((dsc_cfg->scale_decrement_पूर्णांकerval &
		  DSC_PPS_SCALE_DEC_INT_HIGH_MASK) >>
		 DSC_PPS_MSB_SHIFT);

	/* PPS 25 */
	pps_payload->scale_decrement_पूर्णांकerval_low =
		(dsc_cfg->scale_decrement_पूर्णांकerval & DSC_PPS_LSB_MASK);

	/* PPS 26[7:0], PPS 27[7:5] RESERVED */

	/* PPS 27 */
	pps_payload->first_line_bpg_offset =
		dsc_cfg->first_line_bpg_offset;

	/* PPS 28, 29 */
	pps_payload->nfl_bpg_offset =
		cpu_to_be16(dsc_cfg->nfl_bpg_offset);

	/* PPS 30, 31 */
	pps_payload->slice_bpg_offset =
		cpu_to_be16(dsc_cfg->slice_bpg_offset);

	/* PPS 32, 33 */
	pps_payload->initial_offset =
		cpu_to_be16(dsc_cfg->initial_offset);

	/* PPS 34, 35 */
	pps_payload->final_offset = cpu_to_be16(dsc_cfg->final_offset);

	/* PPS 36 */
	pps_payload->flatness_min_qp = dsc_cfg->flatness_min_qp;

	/* PPS 37 */
	pps_payload->flatness_max_qp = dsc_cfg->flatness_max_qp;

	/* PPS 38, 39 */
	pps_payload->rc_model_size = cpu_to_be16(dsc_cfg->rc_model_size);

	/* PPS 40 */
	pps_payload->rc_edge_factor = DSC_RC_EDGE_FACTOR_CONST;

	/* PPS 41 */
	pps_payload->rc_quant_incr_limit0 =
		dsc_cfg->rc_quant_incr_limit0;

	/* PPS 42 */
	pps_payload->rc_quant_incr_limit1 =
		dsc_cfg->rc_quant_incr_limit1;

	/* PPS 43 */
	pps_payload->rc_tgt_offset = DSC_RC_TGT_OFFSET_LO_CONST |
		DSC_RC_TGT_OFFSET_HI_CONST << DSC_PPS_RC_TGT_OFFSET_HI_SHIFT;

	/* PPS 44 - 57 */
	क्रम (i = 0; i < DSC_NUM_BUF_RANGES - 1; i++)
		pps_payload->rc_buf_thresh[i] =
			dsc_cfg->rc_buf_thresh[i];

	/* PPS 58 - 87 */
	/*
	 * For DSC sink programming the RC Range parameter fields
	 * are as follows: Min_qp[15:11], max_qp[10:6], offset[5:0]
	 */
	क्रम (i = 0; i < DSC_NUM_BUF_RANGES; i++) अणु
		pps_payload->rc_range_parameters[i] =
			cpu_to_be16((dsc_cfg->rc_range_params[i].range_min_qp <<
				     DSC_PPS_RC_RANGE_MINQP_SHIFT) |
				    (dsc_cfg->rc_range_params[i].range_max_qp <<
				     DSC_PPS_RC_RANGE_MAXQP_SHIFT) |
				    (dsc_cfg->rc_range_params[i].range_bpg_offset));
	पूर्ण

	/* PPS 88 */
	pps_payload->native_422_420 = dsc_cfg->native_422 |
		dsc_cfg->native_420 << DSC_PPS_NATIVE_420_SHIFT;

	/* PPS 89 */
	pps_payload->second_line_bpg_offset =
		dsc_cfg->second_line_bpg_offset;

	/* PPS 90, 91 */
	pps_payload->nsl_bpg_offset =
		cpu_to_be16(dsc_cfg->nsl_bpg_offset);

	/* PPS 92, 93 */
	pps_payload->second_line_offset_adj =
		cpu_to_be16(dsc_cfg->second_line_offset_adj);

	/* PPS 94 - 127 are O */
पूर्ण
EXPORT_SYMBOL(drm_dsc_pps_payload_pack);

/**
 * drm_dsc_compute_rc_parameters() - Write rate control
 * parameters to the dsc configuration defined in
 * &काष्ठा drm_dsc_config in accordance with the DSC 1.2
 * specअगरication. Some configuration fields must be present
 * beक्रमehand.
 *
 * @vdsc_cfg:
 * DSC Configuration data partially filled by driver
 */
पूर्णांक drm_dsc_compute_rc_parameters(काष्ठा drm_dsc_config *vdsc_cfg)
अणु
	अचिन्हित दीर्घ groups_per_line = 0;
	अचिन्हित दीर्घ groups_total = 0;
	अचिन्हित दीर्घ num_extra_mux_bits = 0;
	अचिन्हित दीर्घ slice_bits = 0;
	अचिन्हित दीर्घ hrd_delay = 0;
	अचिन्हित दीर्घ final_scale = 0;
	अचिन्हित दीर्घ rbs_min = 0;

	अगर (vdsc_cfg->native_420 || vdsc_cfg->native_422) अणु
		/* Number of groups used to code each line of a slice */
		groups_per_line = DIV_ROUND_UP(vdsc_cfg->slice_width / 2,
					       DSC_RC_PIXELS_PER_GROUP);

		/* chunksize in Bytes */
		vdsc_cfg->slice_chunk_size = DIV_ROUND_UP(vdsc_cfg->slice_width / 2 *
							  vdsc_cfg->bits_per_pixel,
							  (8 * 16));
	पूर्ण अन्यथा अणु
		/* Number of groups used to code each line of a slice */
		groups_per_line = DIV_ROUND_UP(vdsc_cfg->slice_width,
					       DSC_RC_PIXELS_PER_GROUP);

		/* chunksize in Bytes */
		vdsc_cfg->slice_chunk_size = DIV_ROUND_UP(vdsc_cfg->slice_width *
							  vdsc_cfg->bits_per_pixel,
							  (8 * 16));
	पूर्ण

	अगर (vdsc_cfg->convert_rgb)
		num_extra_mux_bits = 3 * (vdsc_cfg->mux_word_size +
					  (4 * vdsc_cfg->bits_per_component + 4)
					  - 2);
	अन्यथा अगर (vdsc_cfg->native_422)
		num_extra_mux_bits = 4 * vdsc_cfg->mux_word_size +
			(4 * vdsc_cfg->bits_per_component + 4) +
			3 * (4 * vdsc_cfg->bits_per_component) - 2;
	अन्यथा
		num_extra_mux_bits = 3 * vdsc_cfg->mux_word_size +
			(4 * vdsc_cfg->bits_per_component + 4) +
			2 * (4 * vdsc_cfg->bits_per_component) - 2;
	/* Number of bits in one Slice */
	slice_bits = 8 * vdsc_cfg->slice_chunk_size * vdsc_cfg->slice_height;

	जबतक ((num_extra_mux_bits > 0) &&
	       ((slice_bits - num_extra_mux_bits) % vdsc_cfg->mux_word_size))
		num_extra_mux_bits--;

	अगर (groups_per_line < vdsc_cfg->initial_scale_value - 8)
		vdsc_cfg->initial_scale_value = groups_per_line + 8;

	/* scale_decrement_पूर्णांकerval calculation according to DSC spec 1.11 */
	अगर (vdsc_cfg->initial_scale_value > 8)
		vdsc_cfg->scale_decrement_पूर्णांकerval = groups_per_line /
			(vdsc_cfg->initial_scale_value - 8);
	अन्यथा
		vdsc_cfg->scale_decrement_पूर्णांकerval = DSC_SCALE_DECREMENT_INTERVAL_MAX;

	vdsc_cfg->final_offset = vdsc_cfg->rc_model_size -
		(vdsc_cfg->initial_xmit_delay *
		 vdsc_cfg->bits_per_pixel + 8) / 16 + num_extra_mux_bits;

	अगर (vdsc_cfg->final_offset >= vdsc_cfg->rc_model_size) अणु
		DRM_DEBUG_KMS("FinalOfs < RcModelSze for this InitialXmitDelay\n");
		वापस -दुस्फल;
	पूर्ण

	final_scale = (vdsc_cfg->rc_model_size * 8) /
		(vdsc_cfg->rc_model_size - vdsc_cfg->final_offset);
	अगर (vdsc_cfg->slice_height > 1)
		/*
		 * NflBpgOffset is 16 bit value with 11 fractional bits
		 * hence we multiply by 2^11 क्रम preserving the
		 * fractional part
		 */
		vdsc_cfg->nfl_bpg_offset = DIV_ROUND_UP((vdsc_cfg->first_line_bpg_offset << 11),
							(vdsc_cfg->slice_height - 1));
	अन्यथा
		vdsc_cfg->nfl_bpg_offset = 0;

	/* Number of groups used to code the entire slice */
	groups_total = groups_per_line * vdsc_cfg->slice_height;

	/* slice_bpg_offset is 16 bit value with 11 fractional bits */
	vdsc_cfg->slice_bpg_offset = DIV_ROUND_UP(((vdsc_cfg->rc_model_size -
						    vdsc_cfg->initial_offset +
						    num_extra_mux_bits) << 11),
						  groups_total);

	अगर (final_scale > 9) अणु
		/*
		 * ScaleIncrementInterval =
		 * finaloffset/((NflBpgOffset + SliceBpgOffset)*8(finalscale - 1.125))
		 * as (NflBpgOffset + SliceBpgOffset) has 11 bit fractional value,
		 * we need भागide by 2^11 from pstDscCfg values
		 */
		vdsc_cfg->scale_increment_पूर्णांकerval =
				(vdsc_cfg->final_offset * (1 << 11)) /
				((vdsc_cfg->nfl_bpg_offset +
				vdsc_cfg->slice_bpg_offset) *
				(final_scale - 9));
	पूर्ण अन्यथा अणु
		/*
		 * If finalScaleValue is less than or equal to 9, a value of 0 should
		 * be used to disable the scale increment at the end of the slice
		 */
		vdsc_cfg->scale_increment_पूर्णांकerval = 0;
	पूर्ण

	/*
	 * DSC spec mentions that bits_per_pixel specअगरies the target
	 * bits/pixel (bpp) rate that is used by the encoder,
	 * in steps of 1/16 of a bit per pixel
	 */
	rbs_min = vdsc_cfg->rc_model_size - vdsc_cfg->initial_offset +
		DIV_ROUND_UP(vdsc_cfg->initial_xmit_delay *
			     vdsc_cfg->bits_per_pixel, 16) +
		groups_per_line * vdsc_cfg->first_line_bpg_offset;

	hrd_delay = DIV_ROUND_UP((rbs_min * 16), vdsc_cfg->bits_per_pixel);
	vdsc_cfg->rc_bits = (hrd_delay * vdsc_cfg->bits_per_pixel) / 16;
	vdsc_cfg->initial_dec_delay = hrd_delay - vdsc_cfg->initial_xmit_delay;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_dsc_compute_rc_parameters);
