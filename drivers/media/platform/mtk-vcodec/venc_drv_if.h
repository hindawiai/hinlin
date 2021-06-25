<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2016 MediaTek Inc.
 * Author: Daniel Hsiao <daniel.hsiao@mediatek.com>
 *		Jungchang Tsao <jungchang.tsao@mediatek.com>
 *		Tअगरfany Lin <tअगरfany.lin@mediatek.com>
 */

#अगर_अघोषित _VENC_DRV_IF_H_
#घोषणा _VENC_DRV_IF_H_

#समावेश "mtk_vcodec_drv.h"
#समावेश "mtk_vcodec_util.h"

/*
 * क्रमागत venc_yuv_fmt - The type of input yuv क्रमmat
 * (VPU related: If you change the order, you must also update the VPU codes.)
 * @VENC_YUV_FORMAT_I420: I420 YUV क्रमmat
 * @VENC_YUV_FORMAT_YV12: YV12 YUV क्रमmat
 * @VENC_YUV_FORMAT_NV12: NV12 YUV क्रमmat
 * @VENC_YUV_FORMAT_NV21: NV21 YUV क्रमmat
 */
क्रमागत venc_yuv_fmt अणु
	VENC_YUV_FORMAT_I420 = 3,
	VENC_YUV_FORMAT_YV12 = 5,
	VENC_YUV_FORMAT_NV12 = 6,
	VENC_YUV_FORMAT_NV21 = 7,
पूर्ण;

/*
 * क्रमागत venc_start_opt - encode frame option used in venc_अगर_encode()
 * @VENC_START_OPT_ENCODE_SEQUENCE_HEADER: encode SPS/PPS क्रम H264
 * @VENC_START_OPT_ENCODE_FRAME: encode normal frame
 */
क्रमागत venc_start_opt अणु
	VENC_START_OPT_ENCODE_SEQUENCE_HEADER,
	VENC_START_OPT_ENCODE_FRAME,
पूर्ण;

/*
 * क्रमागत venc_set_param_type - The type of set parameter used in
 *						      venc_अगर_set_param()
 * (VPU related: If you change the order, you must also update the VPU codes.)
 * @VENC_SET_PARAM_ENC: set encoder parameters
 * @VENC_SET_PARAM_FORCE_INTRA: क्रमce an पूर्णांकra frame
 * @VENC_SET_PARAM_ADJUST_BITRATE: adjust bitrate (in bps)
 * @VENC_SET_PARAM_ADJUST_FRAMERATE: set frame rate
 * @VENC_SET_PARAM_GOP_SIZE: set IDR पूर्णांकerval
 * @VENC_SET_PARAM_INTRA_PERIOD: set I frame पूर्णांकerval
 * @VENC_SET_PARAM_SKIP_FRAME: set H264 skip one frame
 * @VENC_SET_PARAM_PREPEND_HEADER: set H264 prepend SPS/PPS beक्रमe IDR
 * @VENC_SET_PARAM_TS_MODE: set VP8 temporal scalability mode
 */
क्रमागत venc_set_param_type अणु
	VENC_SET_PARAM_ENC,
	VENC_SET_PARAM_FORCE_INTRA,
	VENC_SET_PARAM_ADJUST_BITRATE,
	VENC_SET_PARAM_ADJUST_FRAMERATE,
	VENC_SET_PARAM_GOP_SIZE,
	VENC_SET_PARAM_INTRA_PERIOD,
	VENC_SET_PARAM_SKIP_FRAME,
	VENC_SET_PARAM_PREPEND_HEADER,
	VENC_SET_PARAM_TS_MODE,
पूर्ण;

/*
 * काष्ठा venc_enc_prm - encoder settings क्रम VENC_SET_PARAM_ENC used in
 *					  venc_अगर_set_param()
 * @input_fourcc: input yuv क्रमmat
 * @h264_profile: V4L2 defined H.264 profile
 * @h264_level: V4L2 defined H.264 level
 * @width: image width
 * @height: image height
 * @buf_width: buffer width
 * @buf_height: buffer height
 * @frm_rate: frame rate in fps
 * @पूर्णांकra_period: पूर्णांकra frame period
 * @bitrate: target bitrate in bps
 * @gop_size: group of picture size
 */
काष्ठा venc_enc_param अणु
	क्रमागत venc_yuv_fmt input_yuv_fmt;
	अचिन्हित पूर्णांक h264_profile;
	अचिन्हित पूर्णांक h264_level;
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक height;
	अचिन्हित पूर्णांक buf_width;
	अचिन्हित पूर्णांक buf_height;
	अचिन्हित पूर्णांक frm_rate;
	अचिन्हित पूर्णांक पूर्णांकra_period;
	अचिन्हित पूर्णांक bitrate;
	अचिन्हित पूर्णांक gop_size;
पूर्ण;

/**
 * काष्ठा venc_frame_info - per-frame inक्रमmation to pass to the firmware.
 *
 * @frm_count:		sequential number क्रम this frame
 * @skip_frm_count:	number of frames skipped so far जबतक decoding
 * @frm_type:		type of the frame, from क्रमागत venc_h264_frame_type
 */
काष्ठा venc_frame_info अणु
	अचिन्हित पूर्णांक frm_count;		/* per frame update */
	अचिन्हित पूर्णांक skip_frm_count;	/* per frame update */
	अचिन्हित पूर्णांक frm_type;		/* per frame update */
पूर्ण;

/*
 * काष्ठा venc_frm_buf - frame buffer inक्रमmation used in venc_अगर_encode()
 * @fb_addr: plane frame buffer addresses
 */
काष्ठा venc_frm_buf अणु
	काष्ठा mtk_vcodec_fb fb_addr[MTK_VCODEC_MAX_PLANES];
पूर्ण;

/*
 * काष्ठा venc_करोne_result - This is वापस inक्रमmation used in venc_अगर_encode()
 * @bs_size: output bitstream size
 * @is_key_frm: output is key frame or not
 */
काष्ठा venc_करोne_result अणु
	अचिन्हित पूर्णांक bs_size;
	bool is_key_frm;
पूर्ण;

बाह्य स्थिर काष्ठा venc_common_अगर venc_h264_अगर;
बाह्य स्थिर काष्ठा venc_common_अगर venc_vp8_अगर;

/*
 * venc_अगर_init - Create the driver handle
 * @ctx: device context
 * @fourcc: encoder input क्रमmat
 * Return: 0 अगर creating handle successfully, otherwise it is failed.
 */
पूर्णांक venc_अगर_init(काष्ठा mtk_vcodec_ctx *ctx, अचिन्हित पूर्णांक fourcc);

/*
 * venc_अगर_deinit - Release the driver handle
 * @ctx: device context
 * Return: 0 अगर releasing handle successfully, otherwise it is failed.
 */
पूर्णांक venc_अगर_deinit(काष्ठा mtk_vcodec_ctx *ctx);

/*
 * venc_अगर_set_param - Set parameter to driver
 * @ctx: device context
 * @type: parameter type
 * @in: input parameter
 * Return: 0 अगर setting param successfully, otherwise it is failed.
 */
पूर्णांक venc_अगर_set_param(काष्ठा mtk_vcodec_ctx *ctx,
		      क्रमागत venc_set_param_type type,
		      काष्ठा venc_enc_param *in);

/*
 * venc_अगर_encode - Encode one frame
 * @ctx: device context
 * @opt: encode frame option
 * @frm_buf: input frame buffer inक्रमmation
 * @bs_buf: output bitstream buffer infomraiton
 * @result: encode result
 * Return: 0 अगर encoding frame successfully, otherwise it is failed.
 */
पूर्णांक venc_अगर_encode(काष्ठा mtk_vcodec_ctx *ctx,
		   क्रमागत venc_start_opt opt,
		   काष्ठा venc_frm_buf *frm_buf,
		   काष्ठा mtk_vcodec_mem *bs_buf,
		   काष्ठा venc_करोne_result *result);

#पूर्ण_अगर /* _VENC_DRV_IF_H_ */
