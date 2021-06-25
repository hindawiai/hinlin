<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012-2016, The Linux Foundation. All rights reserved.
 * Copyright (C) 2017 Linaro Ltd.
 */
#समावेश <linux/types.h>
#समावेश <media/v4l2-ctrls.h>

#समावेश "core.h"
#समावेश "helpers.h"
#समावेश "vdec.h"

अटल पूर्णांक vdec_op_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा venus_inst *inst = ctrl_to_inst(ctrl);
	काष्ठा vdec_controls *ctr = &inst->controls.dec;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_MPEG_VIDEO_DECODER_MPEG4_DEBLOCK_FILTER:
		ctr->post_loop_deb_mode = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_PROखाता:
	हाल V4L2_CID_MPEG_VIDEO_MPEG4_PROखाता:
	हाल V4L2_CID_MPEG_VIDEO_VP8_PROखाता:
	हाल V4L2_CID_MPEG_VIDEO_VP9_PROखाता:
		ctr->profile = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_LEVEL:
	हाल V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL:
	हाल V4L2_CID_MPEG_VIDEO_VP9_LEVEL:
		ctr->level = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_DEC_DISPLAY_DELAY:
		ctr->display_delay = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_DEC_DISPLAY_DELAY_ENABLE:
		ctr->display_delay_enable = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_DEC_CONCEAL_COLOR:
		ctr->conceal_color = *ctrl->p_new.p_s64;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vdec_op_g_अस्थिर_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा venus_inst *inst = ctrl_to_inst(ctrl);
	काष्ठा vdec_controls *ctr = &inst->controls.dec;
	काष्ठा hfi_buffer_requirements bufreq;
	क्रमागत hfi_version ver = inst->core->res->hfi_version;
	u32 profile, level;
	पूर्णांक ret;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_MPEG_VIDEO_H264_PROखाता:
	हाल V4L2_CID_MPEG_VIDEO_MPEG4_PROखाता:
	हाल V4L2_CID_MPEG_VIDEO_VP8_PROखाता:
	हाल V4L2_CID_MPEG_VIDEO_VP9_PROखाता:
		ret = venus_helper_get_profile_level(inst, &profile, &level);
		अगर (!ret)
			ctr->profile = profile;
		ctrl->val = ctr->profile;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_H264_LEVEL:
	हाल V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL:
	हाल V4L2_CID_MPEG_VIDEO_VP9_LEVEL:
		ret = venus_helper_get_profile_level(inst, &profile, &level);
		अगर (!ret)
			ctr->level = level;
		ctrl->val = ctr->level;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_DECODER_MPEG4_DEBLOCK_FILTER:
		ctrl->val = ctr->post_loop_deb_mode;
		अवरोध;
	हाल V4L2_CID_MIN_BUFFERS_FOR_CAPTURE:
		ret = venus_helper_get_bufreq(inst, HFI_BUFFER_OUTPUT, &bufreq);
		अगर (!ret)
			ctrl->val = HFI_BUFREQ_COUNT_MIN(&bufreq, ver);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops vdec_ctrl_ops = अणु
	.s_ctrl = vdec_op_s_ctrl,
	.g_अस्थिर_ctrl = vdec_op_g_अस्थिर_ctrl,
पूर्ण;

पूर्णांक vdec_ctrl_init(काष्ठा venus_inst *inst)
अणु
	काष्ठा v4l2_ctrl *ctrl;
	पूर्णांक ret;

	ret = v4l2_ctrl_handler_init(&inst->ctrl_handler, 12);
	अगर (ret)
		वापस ret;

	ctrl = v4l2_ctrl_new_std_menu(&inst->ctrl_handler, &vdec_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_MPEG4_PROखाता,
		V4L2_MPEG_VIDEO_MPEG4_PROखाता_ADVANCED_CODING_EFFICIENCY,
		~((1 << V4L2_MPEG_VIDEO_MPEG4_PROखाता_SIMPLE) |
		  (1 << V4L2_MPEG_VIDEO_MPEG4_PROखाता_ADVANCED_SIMPLE)),
		V4L2_MPEG_VIDEO_MPEG4_PROखाता_SIMPLE);
	अगर (ctrl)
		ctrl->flags |= V4L2_CTRL_FLAG_VOLATILE;

	ctrl = v4l2_ctrl_new_std_menu(&inst->ctrl_handler, &vdec_ctrl_ops,
				      V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL,
				      V4L2_MPEG_VIDEO_MPEG4_LEVEL_5,
				      0, V4L2_MPEG_VIDEO_MPEG4_LEVEL_0);
	अगर (ctrl)
		ctrl->flags |= V4L2_CTRL_FLAG_VOLATILE;

	ctrl = v4l2_ctrl_new_std_menu(&inst->ctrl_handler, &vdec_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_PROखाता,
		V4L2_MPEG_VIDEO_H264_PROखाता_MULTIVIEW_HIGH,
		~((1 << V4L2_MPEG_VIDEO_H264_PROखाता_BASELINE) |
		  (1 << V4L2_MPEG_VIDEO_H264_PROखाता_CONSTRAINED_BASELINE) |
		  (1 << V4L2_MPEG_VIDEO_H264_PROखाता_MAIN) |
		  (1 << V4L2_MPEG_VIDEO_H264_PROखाता_HIGH) |
		  (1 << V4L2_MPEG_VIDEO_H264_PROखाता_STEREO_HIGH) |
		  (1 << V4L2_MPEG_VIDEO_H264_PROखाता_MULTIVIEW_HIGH)),
		V4L2_MPEG_VIDEO_H264_PROखाता_BASELINE);
	अगर (ctrl)
		ctrl->flags |= V4L2_CTRL_FLAG_VOLATILE;

	ctrl = v4l2_ctrl_new_std_menu(&inst->ctrl_handler, &vdec_ctrl_ops,
				      V4L2_CID_MPEG_VIDEO_H264_LEVEL,
				      V4L2_MPEG_VIDEO_H264_LEVEL_5_1,
				      0, V4L2_MPEG_VIDEO_H264_LEVEL_1_0);
	अगर (ctrl)
		ctrl->flags |= V4L2_CTRL_FLAG_VOLATILE;

	ctrl = v4l2_ctrl_new_std_menu(&inst->ctrl_handler, &vdec_ctrl_ops,
				      V4L2_CID_MPEG_VIDEO_VP8_PROखाता,
				      V4L2_MPEG_VIDEO_VP8_PROखाता_3,
				      0, V4L2_MPEG_VIDEO_VP8_PROखाता_0);
	अगर (ctrl)
		ctrl->flags |= V4L2_CTRL_FLAG_VOLATILE;

	ctrl = v4l2_ctrl_new_std_menu(&inst->ctrl_handler, &vdec_ctrl_ops,
				      V4L2_CID_MPEG_VIDEO_VP9_PROखाता,
				      V4L2_MPEG_VIDEO_VP9_PROखाता_3,
				      0, V4L2_MPEG_VIDEO_VP9_PROखाता_0);
	अगर (ctrl)
		ctrl->flags |= V4L2_CTRL_FLAG_VOLATILE;

	ctrl = v4l2_ctrl_new_std_menu(&inst->ctrl_handler, &vdec_ctrl_ops,
				      V4L2_CID_MPEG_VIDEO_VP9_LEVEL,
				      V4L2_MPEG_VIDEO_VP9_LEVEL_6_2,
				      0, V4L2_MPEG_VIDEO_VP9_LEVEL_1_0);
	अगर (ctrl)
		ctrl->flags |= V4L2_CTRL_FLAG_VOLATILE;

	v4l2_ctrl_new_std(&inst->ctrl_handler, &vdec_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_DECODER_MPEG4_DEBLOCK_FILTER, 0, 1, 1, 0);

	ctrl = v4l2_ctrl_new_std(&inst->ctrl_handler, &vdec_ctrl_ops,
		V4L2_CID_MIN_BUFFERS_FOR_CAPTURE, 1, 32, 1, 1);
	अगर (ctrl)
		ctrl->flags |= V4L2_CTRL_FLAG_VOLATILE;

	v4l2_ctrl_new_std(&inst->ctrl_handler, &vdec_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_DEC_DISPLAY_DELAY,
			  0, 16383, 1, 0);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &vdec_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_DEC_DISPLAY_DELAY_ENABLE,
			  0, 1, 1, 0);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &vdec_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_DEC_CONCEAL_COLOR, 0,
			  0xffffffffffffLL, 1, 0x8000800010LL);

	ret = inst->ctrl_handler.error;
	अगर (ret) अणु
		v4l2_ctrl_handler_मुक्त(&inst->ctrl_handler);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

व्योम vdec_ctrl_deinit(काष्ठा venus_inst *inst)
अणु
	v4l2_ctrl_handler_मुक्त(&inst->ctrl_handler);
पूर्ण
