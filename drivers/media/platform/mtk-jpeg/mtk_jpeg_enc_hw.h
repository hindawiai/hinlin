<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2019 MediaTek Inc.
 * Author: Xia Jiang <xia.jiang@mediatek.com>
 *
 */

#अगर_अघोषित _MTK_JPEG_ENC_HW_H
#घोषणा _MTK_JPEG_ENC_HW_H

#समावेश <media/videobuf2-core.h>

#समावेश "mtk_jpeg_core.h"

#घोषणा JPEG_ENC_INT_STATUS_DONE	BIT(0)
#घोषणा JPEG_ENC_INT_STATUS_MASK_ALLIRQ	0x13

#घोषणा JPEG_ENC_DST_ADDR_OFFSET_MASK	GENMASK(3, 0)

#घोषणा JPEG_ENC_CTRL_YUV_FORMAT_MASK	0x18
#घोषणा JPEG_ENC_CTRL_RESTART_EN_BIT	BIT(10)
#घोषणा JPEG_ENC_CTRL_खाता_FORMAT_BIT	BIT(5)
#घोषणा JPEG_ENC_CTRL_INT_EN_BIT	BIT(2)
#घोषणा JPEG_ENC_CTRL_ENABLE_BIT	BIT(0)
#घोषणा JPEG_ENC_RESET_BIT		BIT(0)

#घोषणा JPEG_ENC_YUV_FORMAT_YUYV	0
#घोषणा JPEG_ENC_YUV_FORMAT_YVYU	1
#घोषणा JPEG_ENC_YUV_FORMAT_NV12	2
#घोषणा JEPG_ENC_YUV_FORMAT_NV21	3

#घोषणा JPEG_ENC_QUALITY_Q60		0x0
#घोषणा JPEG_ENC_QUALITY_Q80		0x1
#घोषणा JPEG_ENC_QUALITY_Q90		0x2
#घोषणा JPEG_ENC_QUALITY_Q95		0x3
#घोषणा JPEG_ENC_QUALITY_Q39		0x4
#घोषणा JPEG_ENC_QUALITY_Q68		0x5
#घोषणा JPEG_ENC_QUALITY_Q84		0x6
#घोषणा JPEG_ENC_QUALITY_Q92		0x7
#घोषणा JPEG_ENC_QUALITY_Q48		0x8
#घोषणा JPEG_ENC_QUALITY_Q74		0xa
#घोषणा JPEG_ENC_QUALITY_Q87		0xb
#घोषणा JPEG_ENC_QUALITY_Q34		0xc
#घोषणा JPEG_ENC_QUALITY_Q64		0xe
#घोषणा JPEG_ENC_QUALITY_Q82		0xf
#घोषणा JPEG_ENC_QUALITY_Q97		0x10

#घोषणा JPEG_ENC_RSTB			0x100
#घोषणा JPEG_ENC_CTRL			0x104
#घोषणा JPEG_ENC_QUALITY		0x108
#घोषणा JPEG_ENC_BLK_NUM		0x10C
#घोषणा JPEG_ENC_BLK_CNT		0x110
#घोषणा JPEG_ENC_INT_STS		0x11c
#घोषणा JPEG_ENC_DST_ADDR0		0x120
#घोषणा JPEG_ENC_DMA_ADDR0		0x124
#घोषणा JPEG_ENC_STALL_ADDR0		0x128
#घोषणा JPEG_ENC_OFFSET_ADDR		0x138
#घोषणा JPEG_ENC_RST_MCU_NUM		0x150
#घोषणा JPEG_ENC_IMG_SIZE		0x154
#घोषणा JPEG_ENC_DEBUG_INFO0		0x160
#घोषणा JPEG_ENC_DEBUG_INFO1		0x164
#घोषणा JPEG_ENC_TOTAL_CYCLE		0x168
#घोषणा JPEG_ENC_BYTE_OFFSET_MASK	0x16c
#घोषणा JPEG_ENC_SRC_LUMA_ADDR		0x170
#घोषणा JPEG_ENC_SRC_CHROMA_ADDR	0x174
#घोषणा JPEG_ENC_STRIDE			0x178
#घोषणा JPEG_ENC_IMG_STRIDE		0x17c
#घोषणा JPEG_ENC_DCM_CTRL		0x300
#घोषणा JPEG_ENC_CODEC_SEL		0x314
#घोषणा JPEG_ENC_ULTRA_THRES		0x318

/**
 * काष्ठा mtk_jpeg_enc_qlt - JPEG encoder quality data
 * @quality_param:	quality value
 * @hardware_value:	hardware value of quality
 */
काष्ठा mtk_jpeg_enc_qlt अणु
	u8	quality_param;
	u8	hardware_value;
पूर्ण;

व्योम mtk_jpeg_enc_reset(व्योम __iomem *base);
u32 mtk_jpeg_enc_get_file_size(व्योम __iomem *base);
व्योम mtk_jpeg_enc_start(व्योम __iomem *enc_reg_base);
व्योम mtk_jpeg_set_enc_src(काष्ठा mtk_jpeg_ctx *ctx,  व्योम __iomem *base,
			  काष्ठा vb2_buffer *src_buf);
व्योम mtk_jpeg_set_enc_dst(काष्ठा mtk_jpeg_ctx *ctx, व्योम __iomem *base,
			  काष्ठा vb2_buffer *dst_buf);
व्योम mtk_jpeg_set_enc_params(काष्ठा mtk_jpeg_ctx *ctx,  व्योम __iomem *base);

#पूर्ण_अगर /* _MTK_JPEG_ENC_HW_H */
