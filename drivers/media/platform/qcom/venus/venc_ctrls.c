<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012-2016, The Linux Foundation. All rights reserved.
 * Copyright (C) 2017 Linaro Ltd.
 */
#समावेश <linux/types.h>
#समावेश <media/v4l2-ctrls.h>

#समावेश "core.h"
#समावेश "venc.h"

#घोषणा BITRATE_MIN		32000
#घोषणा BITRATE_MAX		160000000
#घोषणा BITRATE_DEFAULT		1000000
#घोषणा BITRATE_DEFAULT_PEAK	(BITRATE_DEFAULT * 2)
#घोषणा BITRATE_STEP		100
#घोषणा SLICE_BYTE_SIZE_MAX	1024
#घोषणा SLICE_BYTE_SIZE_MIN	1024
#घोषणा SLICE_MB_SIZE_MAX	300
#घोषणा INTRA_REFRESH_MBS_MAX	300
#घोषणा AT_SLICE_BOUNDARY	\
	V4L2_MPEG_VIDEO_H264_LOOP_FILTER_MODE_DISABLED_AT_SLICE_BOUNDARY
#घोषणा MAX_LTR_FRAME_COUNT 4

अटल पूर्णांक venc_calc_bpframes(u32 gop_size, u32 conseq_b, u32 *bf, u32 *pf)
अणु
	u32 half = (gop_size - 1) >> 1;
	u32 b, p, ratio;
	bool found = false;

	अगर (!gop_size)
		वापस -EINVAL;

	*bf = *pf = 0;

	अगर (!conseq_b) अणु
		*pf = gop_size -  1;
		वापस 0;
	पूर्ण

	b = p = half;

	क्रम (; b <= gop_size - 1; b++, p--) अणु
		अगर (b % p)
			जारी;

		ratio = b / p;

		अगर (ratio == conseq_b) अणु
			found = true;
			अवरोध;
		पूर्ण

		अगर (ratio > conseq_b)
			अवरोध;
	पूर्ण

	अगर (!found)
		वापस -EINVAL;

	अगर (b + p + 1 != gop_size)
		वापस -EINVAL;

	*bf = b;
	*pf = p;

	वापस 0;
पूर्ण

अटल पूर्णांक venc_op_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा venus_inst *inst = ctrl_to_inst(ctrl);
	काष्ठा venc_controls *ctr = &inst->controls.enc;
	काष्ठा hfi_enable en = अणु .enable = 1 पूर्ण;
	काष्ठा hfi_bitrate brate;
	काष्ठा hfi_ltr_use ltr_use;
	काष्ठा hfi_ltr_mark ltr_mark;
	u32 bframes;
	u32 ptype;
	पूर्णांक ret;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_MPEG_VIDEO_BITRATE_MODE:
		ctr->bitrate_mode = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_BITRATE:
		ctr->bitrate = ctrl->val;
		mutex_lock(&inst->lock);
		अगर (inst->streamon_out && inst->streamon_cap) अणु
			ptype = HFI_PROPERTY_CONFIG_VENC_TARGET_BITRATE;
			brate.bitrate = ctr->bitrate;
			brate.layer_id = 0;

			ret = hfi_session_set_property(inst, ptype, &brate);
			अगर (ret) अणु
				mutex_unlock(&inst->lock);
				वापस ret;
			पूर्ण
		पूर्ण
		mutex_unlock(&inst->lock);
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_BITRATE_PEAK:
		ctr->bitrate_peak = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_ENTROPY_MODE:
		ctr->h264_entropy_mode = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_MPEG4_PROखाता:
		ctr->profile.mpeg4 = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_PROखाता:
		ctr->profile.h264 = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_PROखाता:
		ctr->profile.hevc = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_VP8_PROखाता:
		ctr->profile.vp8 = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL:
		ctr->level.mpeg4 = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_LEVEL:
		ctr->level.h264 = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_LEVEL:
		ctr->level.hevc = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_I_FRAME_QP:
		ctr->h264_i_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_P_FRAME_QP:
		ctr->h264_p_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_B_FRAME_QP:
		ctr->h264_b_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_MIN_QP:
		ctr->h264_min_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_I_FRAME_MIN_QP:
		ctr->h264_i_min_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_P_FRAME_MIN_QP:
		ctr->h264_p_min_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_B_FRAME_MIN_QP:
		ctr->h264_b_min_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_MAX_QP:
		ctr->h264_max_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_I_FRAME_MAX_QP:
		ctr->h264_i_max_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_P_FRAME_MAX_QP:
		ctr->h264_p_max_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_B_FRAME_MAX_QP:
		ctr->h264_b_max_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_I_FRAME_QP:
		ctr->hevc_i_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_P_FRAME_QP:
		ctr->hevc_p_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_B_FRAME_QP:
		ctr->hevc_b_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_MIN_QP:
		ctr->hevc_min_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_I_FRAME_MIN_QP:
		ctr->hevc_i_min_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_P_FRAME_MIN_QP:
		ctr->hevc_p_min_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_B_FRAME_MIN_QP:
		ctr->hevc_b_min_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_MAX_QP:
		ctr->hevc_max_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_I_FRAME_MAX_QP:
		ctr->hevc_i_max_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_P_FRAME_MAX_QP:
		ctr->hevc_p_max_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEVC_B_FRAME_MAX_QP:
		ctr->hevc_b_max_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MODE:
		ctr->multi_slice_mode = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_BYTES:
		ctr->multi_slice_max_bytes = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_MB:
		ctr->multi_slice_max_mb = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_ALPHA:
		ctr->h264_loop_filter_alpha = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_BETA:
		ctr->h264_loop_filter_beta = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_MODE:
		ctr->h264_loop_filter_mode = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_HEADER_MODE:
		ctr->header_mode = ctrl->val;
		mutex_lock(&inst->lock);
		अगर (inst->streamon_out && inst->streamon_cap) अणु
			अगर (ctrl->val == V4L2_MPEG_VIDEO_HEADER_MODE_SEPARATE)
				en.enable = 0;
			अन्यथा
				en.enable = 1;
			ptype = HFI_PROPERTY_CONFIG_VENC_SYNC_FRAME_SEQUENCE_HEADER;
			ret = hfi_session_set_property(inst, ptype, &en);
			अगर (ret) अणु
				mutex_unlock(&inst->lock);
				वापस ret;
			पूर्ण
		पूर्ण
		mutex_unlock(&inst->lock);
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_CYCLIC_INTRA_REFRESH_MB:
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_GOP_SIZE:
		ret = venc_calc_bpframes(ctrl->val, ctr->num_b_frames, &bframes,
					 &ctr->num_p_frames);
		अगर (ret)
			वापस ret;

		ctr->gop_size = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_I_PERIOD:
		ctr->h264_i_period = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_VPX_MIN_QP:
		ctr->vp8_min_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_VPX_MAX_QP:
		ctr->vp8_max_qp = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_B_FRAMES:
		ret = venc_calc_bpframes(ctr->gop_size, ctrl->val, &bframes,
					 &ctr->num_p_frames);
		अगर (ret)
			वापस ret;

		ctr->num_b_frames = bframes;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_FORCE_KEY_FRAME:
		mutex_lock(&inst->lock);
		अगर (inst->streamon_out && inst->streamon_cap) अणु
			ptype = HFI_PROPERTY_CONFIG_VENC_REQUEST_SYNC_FRAME;
			ret = hfi_session_set_property(inst, ptype, &en);

			अगर (ret) अणु
				mutex_unlock(&inst->lock);
				वापस ret;
			पूर्ण
		पूर्ण
		mutex_unlock(&inst->lock);
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_FRAME_RC_ENABLE:
		ctr->rc_enable = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_CONSTANT_QUALITY:
		ctr->स्थिर_quality = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_FRAME_SKIP_MODE:
		ctr->frame_skip_mode = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_BASELAYER_PRIORITY_ID:
		ctr->base_priority_id = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_AU_DELIMITER:
		ctr->aud_enable = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_LTR_COUNT:
		ctr->ltr_count = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_FRAME_LTR_INDEX:
		mutex_lock(&inst->lock);
		अगर (inst->streamon_out && inst->streamon_cap) अणु
			ptype = HFI_PROPERTY_CONFIG_VENC_MARKLTRFRAME;
			ltr_mark.mark_frame = ctrl->val;
			ret = hfi_session_set_property(inst, ptype, &ltr_mark);
			अगर (ret) अणु
				mutex_unlock(&inst->lock);
				वापस ret;
			पूर्ण
		पूर्ण
		mutex_unlock(&inst->lock);
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_USE_LTR_FRAMES:
		mutex_lock(&inst->lock);
		अगर (inst->streamon_out && inst->streamon_cap) अणु
			ptype = HFI_PROPERTY_CONFIG_VENC_USELTRFRAME;
			ltr_use.ref_ltr = ctrl->val;
			ltr_use.use_स्थिरrnt = true;
			ltr_use.frames = 0;
			ret = hfi_session_set_property(inst, ptype, &ltr_use);
			अगर (ret) अणु
				mutex_unlock(&inst->lock);
				वापस ret;
			पूर्ण
		पूर्ण
		mutex_unlock(&inst->lock);
		अवरोध;
	हाल V4L2_CID_COLORIMETRY_HDR10_CLL_INFO:
		ctr->cll = *ctrl->p_new.p_hdr10_cll;
		अवरोध;
	हाल V4L2_CID_COLORIMETRY_HDR10_MASTERING_DISPLAY:
		ctr->mastering = *ctrl->p_new.p_hdr10_mastering;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops venc_ctrl_ops = अणु
	.s_ctrl = venc_op_s_ctrl,
पूर्ण;

पूर्णांक venc_ctrl_init(काष्ठा venus_inst *inst)
अणु
	पूर्णांक ret;

	ret = v4l2_ctrl_handler_init(&inst->ctrl_handler, 57);
	अगर (ret)
		वापस ret;

	v4l2_ctrl_new_std_menu(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_BITRATE_MODE,
		V4L2_MPEG_VIDEO_BITRATE_MODE_CBR,
		~((1 << V4L2_MPEG_VIDEO_BITRATE_MODE_VBR) |
		  (1 << V4L2_MPEG_VIDEO_BITRATE_MODE_CBR) |
		  (1 << V4L2_MPEG_VIDEO_BITRATE_MODE_CQ)),
		V4L2_MPEG_VIDEO_BITRATE_MODE_VBR);

	v4l2_ctrl_new_std_menu(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_ENTROPY_MODE,
		V4L2_MPEG_VIDEO_H264_ENTROPY_MODE_CABAC,
		0, V4L2_MPEG_VIDEO_H264_ENTROPY_MODE_CAVLC);

	v4l2_ctrl_new_std_menu(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_MPEG4_PROखाता,
		V4L2_MPEG_VIDEO_MPEG4_PROखाता_ADVANCED_CODING_EFFICIENCY,
		~((1 << V4L2_MPEG_VIDEO_MPEG4_PROखाता_SIMPLE) |
		  (1 << V4L2_MPEG_VIDEO_MPEG4_PROखाता_ADVANCED_SIMPLE)),
		V4L2_MPEG_VIDEO_MPEG4_PROखाता_SIMPLE);

	v4l2_ctrl_new_std_menu(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL,
		V4L2_MPEG_VIDEO_MPEG4_LEVEL_5,
		0, V4L2_MPEG_VIDEO_MPEG4_LEVEL_0);

	v4l2_ctrl_new_std_menu(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_HEVC_PROखाता,
		V4L2_MPEG_VIDEO_HEVC_PROखाता_MAIN_10,
		~((1 << V4L2_MPEG_VIDEO_HEVC_PROखाता_MAIN) |
		  (1 << V4L2_MPEG_VIDEO_HEVC_PROखाता_MAIN_STILL_PICTURE) |
		  (1 << V4L2_MPEG_VIDEO_HEVC_PROखाता_MAIN_10)),
		V4L2_MPEG_VIDEO_HEVC_PROखाता_MAIN);

	v4l2_ctrl_new_std_menu(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_HEVC_LEVEL,
		V4L2_MPEG_VIDEO_HEVC_LEVEL_6_2,
		0, V4L2_MPEG_VIDEO_HEVC_LEVEL_1);

	v4l2_ctrl_new_std_menu(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_PROखाता,
		V4L2_MPEG_VIDEO_H264_PROखाता_MULTIVIEW_HIGH,
		~((1 << V4L2_MPEG_VIDEO_H264_PROखाता_BASELINE) |
		  (1 << V4L2_MPEG_VIDEO_H264_PROखाता_CONSTRAINED_BASELINE) |
		  (1 << V4L2_MPEG_VIDEO_H264_PROखाता_MAIN) |
		  (1 << V4L2_MPEG_VIDEO_H264_PROखाता_HIGH) |
		  (1 << V4L2_MPEG_VIDEO_H264_PROखाता_STEREO_HIGH) |
		  (1 << V4L2_MPEG_VIDEO_H264_PROखाता_MULTIVIEW_HIGH)),
		V4L2_MPEG_VIDEO_H264_PROखाता_HIGH);

	v4l2_ctrl_new_std_menu(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_LEVEL,
		V4L2_MPEG_VIDEO_H264_LEVEL_5_1,
		0, V4L2_MPEG_VIDEO_H264_LEVEL_1_0);

	v4l2_ctrl_new_std_menu(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_MODE,
		AT_SLICE_BOUNDARY,
		0, V4L2_MPEG_VIDEO_H264_LOOP_FILTER_MODE_DISABLED);

	v4l2_ctrl_new_std_menu(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_HEADER_MODE,
		V4L2_MPEG_VIDEO_HEADER_MODE_JOINED_WITH_1ST_FRAME,
		~((1 << V4L2_MPEG_VIDEO_HEADER_MODE_SEPARATE) |
		(1 << V4L2_MPEG_VIDEO_HEADER_MODE_JOINED_WITH_1ST_FRAME)),
		V4L2_MPEG_VIDEO_HEADER_MODE_JOINED_WITH_1ST_FRAME);

	v4l2_ctrl_new_std_menu(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MODE,
		V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_MAX_BYTES,
		0, V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_SINGLE);

	v4l2_ctrl_new_std_menu(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_VP8_PROखाता,
		V4L2_MPEG_VIDEO_VP8_PROखाता_3,
		0, V4L2_MPEG_VIDEO_VP8_PROखाता_0);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_BITRATE, BITRATE_MIN, BITRATE_MAX,
		BITRATE_STEP, BITRATE_DEFAULT);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_BITRATE_PEAK, BITRATE_MIN, BITRATE_MAX,
		BITRATE_STEP, BITRATE_DEFAULT_PEAK);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_H264_I_FRAME_QP, 1, 51, 1, 26);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_H264_P_FRAME_QP, 1, 51, 1, 28);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_H264_B_FRAME_QP, 1, 51, 1, 30);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_H264_MIN_QP, 1, 51, 1, 1);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_H264_I_FRAME_MIN_QP, 1, 51, 1, 1);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_H264_P_FRAME_MIN_QP, 1, 51, 1, 1);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_H264_B_FRAME_MIN_QP, 1, 51, 1, 1);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_H264_MAX_QP, 1, 51, 1, 51);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_H264_I_FRAME_MAX_QP, 1, 51, 1, 51);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_H264_P_FRAME_MAX_QP, 1, 51, 1, 51);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_H264_B_FRAME_MAX_QP, 1, 51, 1, 51);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_HEVC_I_FRAME_QP, 1, 63, 1, 26);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_HEVC_P_FRAME_QP, 1, 63, 1, 28);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_HEVC_B_FRAME_QP, 1, 63, 1, 30);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_HEVC_MIN_QP, 1, 63, 1, 1);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_HEVC_I_FRAME_MIN_QP, 1, 63, 1, 1);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_HEVC_P_FRAME_MIN_QP, 1, 63, 1, 1);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_HEVC_B_FRAME_MIN_QP, 1, 63, 1, 1);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_HEVC_MAX_QP, 1, 63, 1, 63);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_HEVC_I_FRAME_MAX_QP, 1, 63, 1, 63);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_HEVC_P_FRAME_MAX_QP, 1, 63, 1, 63);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_HEVC_B_FRAME_MAX_QP, 1, 63, 1, 63);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_BYTES, SLICE_BYTE_SIZE_MIN,
		SLICE_BYTE_SIZE_MAX, 1, SLICE_BYTE_SIZE_MIN);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_MB, 1,
		SLICE_MB_SIZE_MAX, 1, 1);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_ALPHA, -6, 6, 1, 0);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_BETA, -6, 6, 1, 0);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_CYCLIC_INTRA_REFRESH_MB,
		0, INTRA_REFRESH_MBS_MAX, 1, 0);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_GOP_SIZE, 0, (1 << 16) - 1, 1, 30);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_VPX_MIN_QP, 1, 128, 1, 1);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_VPX_MAX_QP, 1, 128, 1, 128);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_B_FRAMES, 0, 4, 1, 0);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_I_PERIOD, 0, (1 << 16) - 1, 1, 0);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_FORCE_KEY_FRAME, 0, 0, 0, 0);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_FRAME_RC_ENABLE, 0, 1, 1, 1);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_CONSTANT_QUALITY, 0, 100, 1, 0);

	v4l2_ctrl_new_std_menu(&inst->ctrl_handler, &venc_ctrl_ops,
			       V4L2_CID_MPEG_VIDEO_FRAME_SKIP_MODE,
			       V4L2_MPEG_VIDEO_FRAME_SKIP_MODE_BUF_LIMIT,
			       ~((1 << V4L2_MPEG_VIDEO_FRAME_SKIP_MODE_DISABLED) |
			       (1 << V4L2_MPEG_VIDEO_FRAME_SKIP_MODE_BUF_LIMIT)),
			       V4L2_MPEG_VIDEO_FRAME_SKIP_MODE_DISABLED);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_BASELAYER_PRIORITY_ID, 0,
			  6, 1, 0);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_AU_DELIMITER, 0, 1, 1, 0);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_USE_LTR_FRAMES, 0,
			  ((1 << MAX_LTR_FRAME_COUNT) - 1), 0, 0);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_LTR_COUNT, 0,
			  MAX_LTR_FRAME_COUNT, 1, 0);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_FRAME_LTR_INDEX, 0,
			  (MAX_LTR_FRAME_COUNT - 1), 1, 0);

	v4l2_ctrl_new_std_compound(&inst->ctrl_handler, &venc_ctrl_ops,
				   V4L2_CID_COLORIMETRY_HDR10_CLL_INFO,
				   v4l2_ctrl_ptr_create(शून्य));

	v4l2_ctrl_new_std_compound(&inst->ctrl_handler, &venc_ctrl_ops,
				   V4L2_CID_COLORIMETRY_HDR10_MASTERING_DISPLAY,
				   v4l2_ctrl_ptr_create(शून्य));

	ret = inst->ctrl_handler.error;
	अगर (ret)
		जाओ err;

	ret = v4l2_ctrl_handler_setup(&inst->ctrl_handler);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	v4l2_ctrl_handler_मुक्त(&inst->ctrl_handler);
	वापस ret;
पूर्ण

व्योम venc_ctrl_deinit(काष्ठा venus_inst *inst)
अणु
	v4l2_ctrl_handler_मुक्त(&inst->ctrl_handler);
पूर्ण
