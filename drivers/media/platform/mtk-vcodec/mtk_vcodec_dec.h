<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2016 MediaTek Inc.
 * Author: PC Chen <pc.chen@mediatek.com>
 *         Tअगरfany Lin <tअगरfany.lin@mediatek.com>
 */

#अगर_अघोषित _MTK_VCODEC_DEC_H_
#घोषणा _MTK_VCODEC_DEC_H_

#समावेश <media/videobuf2-core.h>
#समावेश <media/v4l2-mem2स्मृति.स>

#घोषणा VCODEC_CAPABILITY_4K_DISABLED	0x10
#घोषणा VCODEC_DEC_4K_CODED_WIDTH	4096U
#घोषणा VCODEC_DEC_4K_CODED_HEIGHT	2304U
#घोषणा MTK_VDEC_MAX_W	2048U
#घोषणा MTK_VDEC_MAX_H	1088U

#घोषणा MTK_VDEC_IRQ_STATUS_DEC_SUCCESS        0x10000

/**
 * काष्ठा vdec_fb  - decoder frame buffer
 * @base_y	: Y plane memory info
 * @base_c	: C plane memory info
 * @status      : frame buffer status (vdec_fb_status)
 */
काष्ठा vdec_fb अणु
	काष्ठा mtk_vcodec_mem	base_y;
	काष्ठा mtk_vcodec_mem	base_c;
	अचिन्हित पूर्णांक	status;
पूर्ण;

/**
 * काष्ठा mtk_video_dec_buf - Private data related to each VB2 buffer.
 * @m2m_buf:	M2M buffer
 * @list:	link list
 * @used:	Capture buffer contain decoded frame data and keep in
 *			codec data काष्ठाure
 * @queued_in_vb2:	Capture buffer is queue in vb2
 * @queued_in_v4l2:	Capture buffer is in v4l2 driver, but not in vb2
 *			queue yet
 * @lastframe:		Intput buffer is last buffer - EOS
 * @error:		An unrecoverable error occurs on this buffer.
 * @frame_buffer:	Decode status, and buffer inक्रमmation of Capture buffer
 *
 * Note : These status inक्रमmation help us track and debug buffer state
 */
काष्ठा mtk_video_dec_buf अणु
	काष्ठा v4l2_m2m_buffer	m2m_buf;

	bool	used;
	bool	queued_in_vb2;
	bool	queued_in_v4l2;
	bool	lastframe;
	bool	error;
	काष्ठा vdec_fb	frame_buffer;
पूर्ण;

बाह्य स्थिर काष्ठा v4l2_ioctl_ops mtk_vdec_ioctl_ops;
बाह्य स्थिर काष्ठा v4l2_m2m_ops mtk_vdec_m2m_ops;


/*
 * mtk_vdec_lock/mtk_vdec_unlock are क्रम ctx instance to
 * get/release lock beक्रमe/after access decoder hw.
 * mtk_vdec_lock get decoder hw lock and set curr_ctx
 * to ctx instance that get lock
 */
व्योम mtk_vdec_unlock(काष्ठा mtk_vcodec_ctx *ctx);
व्योम mtk_vdec_lock(काष्ठा mtk_vcodec_ctx *ctx);
पूर्णांक mtk_vcodec_dec_queue_init(व्योम *priv, काष्ठा vb2_queue *src_vq,
			   काष्ठा vb2_queue *dst_vq);
व्योम mtk_vcodec_dec_set_शेष_params(काष्ठा mtk_vcodec_ctx *ctx);
व्योम mtk_vcodec_dec_release(काष्ठा mtk_vcodec_ctx *ctx);
पूर्णांक mtk_vcodec_dec_ctrls_setup(काष्ठा mtk_vcodec_ctx *ctx);


#पूर्ण_अगर /* _MTK_VCODEC_DEC_H_ */
