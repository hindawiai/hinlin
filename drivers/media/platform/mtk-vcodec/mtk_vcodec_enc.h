<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
* Copyright (c) 2016 MediaTek Inc.
* Author: PC Chen <pc.chen@mediatek.com>
*         Tअगरfany Lin <tअगरfany.lin@mediatek.com>
*/

#अगर_अघोषित _MTK_VCODEC_ENC_H_
#घोषणा _MTK_VCODEC_ENC_H_

#समावेश <media/videobuf2-core.h>
#समावेश <media/v4l2-mem2स्मृति.स>

#घोषणा MTK_VENC_IRQ_STATUS_SPS	0x1
#घोषणा MTK_VENC_IRQ_STATUS_PPS	0x2
#घोषणा MTK_VENC_IRQ_STATUS_FRM	0x4
#घोषणा MTK_VENC_IRQ_STATUS_DRAM	0x8
#घोषणा MTK_VENC_IRQ_STATUS_PAUSE	0x10
#घोषणा MTK_VENC_IRQ_STATUS_SWITCH	0x20

#घोषणा MTK_VENC_IRQ_STATUS_OFFSET	0x05C
#घोषणा MTK_VENC_IRQ_ACK_OFFSET	0x060

/**
 * काष्ठा mtk_video_enc_buf - Private data related to each VB2 buffer.
 * @m2m_buf:	M2M buffer
 * @list:	list that buffer link to
 * @param_change: Types of encode parameter change beक्रमe encoding this
 *				buffer
 * @enc_params: Encode parameters changed beक्रमe encode this buffer
 */
काष्ठा mtk_video_enc_buf अणु
	काष्ठा v4l2_m2m_buffer m2m_buf;

	u32 param_change;
	काष्ठा mtk_enc_params enc_params;
पूर्ण;

बाह्य स्थिर काष्ठा v4l2_ioctl_ops mtk_venc_ioctl_ops;
बाह्य स्थिर काष्ठा v4l2_m2m_ops mtk_venc_m2m_ops;

पूर्णांक mtk_venc_unlock(काष्ठा mtk_vcodec_ctx *ctx);
पूर्णांक mtk_venc_lock(काष्ठा mtk_vcodec_ctx *ctx);
पूर्णांक mtk_vcodec_enc_queue_init(व्योम *priv, काष्ठा vb2_queue *src_vq,
			      काष्ठा vb2_queue *dst_vq);
व्योम mtk_vcodec_enc_release(काष्ठा mtk_vcodec_ctx *ctx);
पूर्णांक mtk_vcodec_enc_ctrls_setup(काष्ठा mtk_vcodec_ctx *ctx);
व्योम mtk_vcodec_enc_set_शेष_params(काष्ठा mtk_vcodec_ctx *ctx);

#पूर्ण_अगर /* _MTK_VCODEC_ENC_H_ */
