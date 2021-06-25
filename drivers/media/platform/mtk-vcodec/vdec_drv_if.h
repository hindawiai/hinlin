<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2016 MediaTek Inc.
 * Author: PC Chen <pc.chen@mediatek.com>
 *		   Tअगरfany Lin <tअगरfany.lin@mediatek.com>
 */

#अगर_अघोषित _VDEC_DRV_IF_H_
#घोषणा _VDEC_DRV_IF_H_

#समावेश "mtk_vcodec_drv.h"
#समावेश "mtk_vcodec_dec.h"
#समावेश "mtk_vcodec_util.h"


/**
 * क्रमागत vdec_fb_status  - decoder frame buffer status
 * @FB_ST_NORMAL: initial state
 * @FB_ST_DISPLAY: frame buffer is पढ़ोy to be displayed
 * @FB_ST_FREE: frame buffer is not used by decoder any more
 */
क्रमागत vdec_fb_status अणु
	FB_ST_NORMAL		= 0,
	FB_ST_DISPLAY		= (1 << 0),
	FB_ST_FREE		= (1 << 1)
पूर्ण;

/* For GET_PARAM_DISP_FRAME_BUFFER and GET_PARAM_FREE_FRAME_BUFFER,
 * the caller करोes not own the वापसed buffer. The buffer will not be
 *				released beक्रमe vdec_अगर_deinit.
 * GET_PARAM_DISP_FRAME_BUFFER	: get next displayable frame buffer,
 *				काष्ठा vdec_fb**
 * GET_PARAM_FREE_FRAME_BUFFER	: get non-referenced framebuffer, vdec_fb**
 * GET_PARAM_PIC_INFO		: get picture info, काष्ठा vdec_pic_info*
 * GET_PARAM_CROP_INFO		: get crop info, काष्ठा v4l2_crop*
 * GET_PARAM_DPB_SIZE		: get dpb size, अचिन्हित पूर्णांक*
 */
क्रमागत vdec_get_param_type अणु
	GET_PARAM_DISP_FRAME_BUFFER,
	GET_PARAM_FREE_FRAME_BUFFER,
	GET_PARAM_PIC_INFO,
	GET_PARAM_CROP_INFO,
	GET_PARAM_DPB_SIZE
पूर्ण;

/**
 * काष्ठा vdec_fb_node  - decoder frame buffer node
 * @list	: list to hold this node
 * @fb	: poपूर्णांक to frame buffer (vdec_fb), fb could poपूर्णांक to frame buffer and
 *	working buffer this is क्रम मुख्यtain buffers in dअगरferent state
 */
काष्ठा vdec_fb_node अणु
	काष्ठा list_head list;
	काष्ठा vdec_fb *fb;
पूर्ण;

बाह्य स्थिर काष्ठा vdec_common_अगर vdec_h264_अगर;
बाह्य स्थिर काष्ठा vdec_common_अगर vdec_vp8_अगर;
बाह्य स्थिर काष्ठा vdec_common_अगर vdec_vp9_अगर;

/**
 * vdec_अगर_init() - initialize decode driver
 * @ctx	: [in] v4l2 context
 * @fourcc	: [in] video क्रमmat fourcc, V4L2_PIX_FMT_H264/VP8/VP9..
 */
पूर्णांक vdec_अगर_init(काष्ठा mtk_vcodec_ctx *ctx, अचिन्हित पूर्णांक fourcc);

/**
 * vdec_अगर_deinit() - deinitialize decode driver
 * @ctx	: [in] v4l2 context
 *
 */
व्योम vdec_अगर_deinit(काष्ठा mtk_vcodec_ctx *ctx);

/**
 * vdec_अगर_decode() - trigger decode
 * @ctx	: [in] v4l2 context
 * @bs	: [in] input bitstream
 * @fb	: [in] frame buffer to store decoded frame, when null means parse
 *	header only
 * @res_chg	: [out] resolution change happens अगर current bs have dअगरferent
 *	picture width/height
 * Note: To flush the decoder when reaching खातापूर्ण, set input bitstream as शून्य.
 *
 * Return: 0 on success. -EIO on unrecoverable error.
 */
पूर्णांक vdec_अगर_decode(काष्ठा mtk_vcodec_ctx *ctx, काष्ठा mtk_vcodec_mem *bs,
		   काष्ठा vdec_fb *fb, bool *res_chg);

/**
 * vdec_अगर_get_param() - get driver's parameter
 * @ctx	: [in] v4l2 context
 * @type	: [in] input parameter type
 * @out	: [out] buffer to store query result
 */
पूर्णांक vdec_अगर_get_param(काष्ठा mtk_vcodec_ctx *ctx, क्रमागत vdec_get_param_type type,
		      व्योम *out);

#पूर्ण_अगर
