<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015-2016 MediaTek Inc.
 * Author: Houदीर्घ Wei <houदीर्घ.wei@mediatek.com>
 *         Ming Hsiu Tsai <minghsiu.tsai@mediatek.com>
 */

#समावेश <linux/platक्रमm_device.h>

#समावेश "mtk_mdp_core.h"
#समावेश "mtk_mdp_regs.h"


#घोषणा MDP_COLORFMT_PACK(VIDEO, PLANE, COPLANE, HF, VF, BITS, GROUP, SWAP, ID)\
	(((VIDEO) << 27) | ((PLANE) << 24) | ((COPLANE) << 22) |\
	((HF) << 20) | ((VF) << 18) | ((BITS) << 8) | ((GROUP) << 6) |\
	((SWAP) << 5) | ((ID) << 0))

क्रमागत MDP_COLOR_ENUM अणु
	MDP_COLOR_UNKNOWN = 0,
	MDP_COLOR_NV12 = MDP_COLORFMT_PACK(0, 2, 1, 1, 1, 8, 1, 0, 12),
	MDP_COLOR_I420 = MDP_COLORFMT_PACK(0, 3, 0, 1, 1, 8, 1, 0, 8),
	MDP_COLOR_YV12 = MDP_COLORFMT_PACK(0, 3, 0, 1, 1, 8, 1, 1, 8),
	/* Mediatek proprietary क्रमmat */
	MDP_COLOR_420_MT21 = MDP_COLORFMT_PACK(5, 2, 1, 1, 1, 256, 1, 0, 12),
पूर्ण;

अटल पूर्णांक32_t mtk_mdp_map_color_क्रमmat(पूर्णांक v4l2_क्रमmat)
अणु
	चयन (v4l2_क्रमmat) अणु
	हाल V4L2_PIX_FMT_NV12M:
	हाल V4L2_PIX_FMT_NV12:
		वापस MDP_COLOR_NV12;
	हाल V4L2_PIX_FMT_MT21C:
		वापस MDP_COLOR_420_MT21;
	हाल V4L2_PIX_FMT_YUV420M:
	हाल V4L2_PIX_FMT_YUV420:
		वापस MDP_COLOR_I420;
	हाल V4L2_PIX_FMT_YVU420:
		वापस MDP_COLOR_YV12;
	पूर्ण

	mtk_mdp_err("Unknown format 0x%x", v4l2_क्रमmat);

	वापस MDP_COLOR_UNKNOWN;
पूर्ण

व्योम mtk_mdp_hw_set_input_addr(काष्ठा mtk_mdp_ctx *ctx,
			       काष्ठा mtk_mdp_addr *addr)
अणु
	काष्ठा mdp_buffer *src_buf = &ctx->vpu.vsi->src_buffer;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(addr->addr); i++)
		src_buf->addr_mva[i] = (uपूर्णांक64_t)addr->addr[i];
पूर्ण

व्योम mtk_mdp_hw_set_output_addr(काष्ठा mtk_mdp_ctx *ctx,
				काष्ठा mtk_mdp_addr *addr)
अणु
	काष्ठा mdp_buffer *dst_buf = &ctx->vpu.vsi->dst_buffer;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(addr->addr); i++)
		dst_buf->addr_mva[i] = (uपूर्णांक64_t)addr->addr[i];
पूर्ण

व्योम mtk_mdp_hw_set_in_size(काष्ठा mtk_mdp_ctx *ctx)
अणु
	काष्ठा mtk_mdp_frame *frame = &ctx->s_frame;
	काष्ठा mdp_config *config = &ctx->vpu.vsi->src_config;

	/* Set input pixel offset */
	config->crop_x = frame->crop.left;
	config->crop_y = frame->crop.top;

	/* Set input cropped size */
	config->crop_w = frame->crop.width;
	config->crop_h = frame->crop.height;

	/* Set input original size */
	config->x = 0;
	config->y = 0;
	config->w = frame->width;
	config->h = frame->height;
पूर्ण

व्योम mtk_mdp_hw_set_in_image_क्रमmat(काष्ठा mtk_mdp_ctx *ctx)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा mtk_mdp_frame *frame = &ctx->s_frame;
	काष्ठा mdp_config *config = &ctx->vpu.vsi->src_config;
	काष्ठा mdp_buffer *src_buf = &ctx->vpu.vsi->src_buffer;

	src_buf->plane_num = frame->fmt->num_comp;
	config->क्रमmat = mtk_mdp_map_color_क्रमmat(frame->fmt->pixelक्रमmat);
	config->w_stride = 0; /* MDP will calculate it by color क्रमmat. */
	config->h_stride = 0; /* MDP will calculate it by color क्रमmat. */

	क्रम (i = 0; i < src_buf->plane_num; i++)
		src_buf->plane_size[i] = frame->payload[i];
पूर्ण

व्योम mtk_mdp_hw_set_out_size(काष्ठा mtk_mdp_ctx *ctx)
अणु
	काष्ठा mtk_mdp_frame *frame = &ctx->d_frame;
	काष्ठा mdp_config *config = &ctx->vpu.vsi->dst_config;

	config->crop_x = frame->crop.left;
	config->crop_y = frame->crop.top;
	config->crop_w = frame->crop.width;
	config->crop_h = frame->crop.height;
	config->x = 0;
	config->y = 0;
	config->w = frame->width;
	config->h = frame->height;
पूर्ण

व्योम mtk_mdp_hw_set_out_image_क्रमmat(काष्ठा mtk_mdp_ctx *ctx)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा mtk_mdp_frame *frame = &ctx->d_frame;
	काष्ठा mdp_config *config = &ctx->vpu.vsi->dst_config;
	काष्ठा mdp_buffer *dst_buf = &ctx->vpu.vsi->dst_buffer;

	dst_buf->plane_num = frame->fmt->num_comp;
	config->क्रमmat = mtk_mdp_map_color_क्रमmat(frame->fmt->pixelक्रमmat);
	config->w_stride = 0; /* MDP will calculate it by color क्रमmat. */
	config->h_stride = 0; /* MDP will calculate it by color क्रमmat. */
	क्रम (i = 0; i < dst_buf->plane_num; i++)
		dst_buf->plane_size[i] = frame->payload[i];
पूर्ण

व्योम mtk_mdp_hw_set_rotation(काष्ठा mtk_mdp_ctx *ctx)
अणु
	काष्ठा mdp_config_misc *misc = &ctx->vpu.vsi->misc;

	misc->orientation = ctx->ctrls.rotate->val;
	misc->hflip = ctx->ctrls.hflip->val;
	misc->vflip = ctx->ctrls.vflip->val;
पूर्ण

व्योम mtk_mdp_hw_set_global_alpha(काष्ठा mtk_mdp_ctx *ctx)
अणु
	काष्ठा mdp_config_misc *misc = &ctx->vpu.vsi->misc;

	misc->alpha = ctx->ctrls.global_alpha->val;
पूर्ण
