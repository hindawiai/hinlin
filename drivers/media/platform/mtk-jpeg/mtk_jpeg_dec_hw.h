<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2016 MediaTek Inc.
 * Author: Ming Hsiu Tsai <minghsiu.tsai@mediatek.com>
 *         Rick Chang <rick.chang@mediatek.com>
 *         Xia Jiang <xia.jiang@mediatek.com>
 */

#अगर_अघोषित _MTK_JPEG_DEC_HW_H
#घोषणा _MTK_JPEG_DEC_HW_H

#समावेश <media/videobuf2-core.h>

#समावेश "mtk_jpeg_core.h"
#समावेश "mtk_jpeg_dec_reg.h"

क्रमागत अणु
	MTK_JPEG_DEC_RESULT_खातापूर्ण_DONE		= 0,
	MTK_JPEG_DEC_RESULT_PAUSE		= 1,
	MTK_JPEG_DEC_RESULT_UNDERFLOW		= 2,
	MTK_JPEG_DEC_RESULT_OVERFLOW		= 3,
	MTK_JPEG_DEC_RESULT_ERROR_BS		= 4,
	MTK_JPEG_DEC_RESULT_ERROR_UNKNOWN	= 6
पूर्ण;

काष्ठा mtk_jpeg_dec_param अणु
	u32 pic_w;
	u32 pic_h;
	u32 dec_w;
	u32 dec_h;
	u32 src_color;
	u32 dst_fourcc;
	u32 mcu_w;
	u32 mcu_h;
	u32 total_mcu;
	u32 unit_num;
	u32 comp_num;
	u32 comp_id[MTK_JPEG_COMP_MAX];
	u32 sampling_w[MTK_JPEG_COMP_MAX];
	u32 sampling_h[MTK_JPEG_COMP_MAX];
	u32 qtbl_num[MTK_JPEG_COMP_MAX];
	u32 blk_num;
	u32 blk_comp[MTK_JPEG_COMP_MAX];
	u32 membership;
	u32 dma_mcu;
	u32 dma_group;
	u32 dma_last_mcu;
	u32 img_stride[MTK_JPEG_COMP_MAX];
	u32 mem_stride[MTK_JPEG_COMP_MAX];
	u32 comp_w[MTK_JPEG_COMP_MAX];
	u32 comp_size[MTK_JPEG_COMP_MAX];
	u32 y_size;
	u32 uv_size;
	u32 dec_size;
	u8 uv_brz_w;
पूर्ण;

काष्ठा mtk_jpeg_bs अणु
	dma_addr_t	str_addr;
	dma_addr_t	end_addr;
	माप_प्रकार		size;
पूर्ण;

काष्ठा mtk_jpeg_fb अणु
	dma_addr_t	plane_addr[MTK_JPEG_COMP_MAX];
	माप_प्रकार		size;
पूर्ण;

पूर्णांक mtk_jpeg_dec_fill_param(काष्ठा mtk_jpeg_dec_param *param);
u32 mtk_jpeg_dec_get_पूर्णांक_status(व्योम __iomem *dec_reg_base);
u32 mtk_jpeg_dec_क्रमागत_result(u32 irq_result);
व्योम mtk_jpeg_dec_set_config(व्योम __iomem *base,
			     काष्ठा mtk_jpeg_dec_param *config,
			     काष्ठा mtk_jpeg_bs *bs,
			     काष्ठा mtk_jpeg_fb *fb);
व्योम mtk_jpeg_dec_reset(व्योम __iomem *dec_reg_base);
व्योम mtk_jpeg_dec_start(व्योम __iomem *dec_reg_base);

#पूर्ण_अगर /* _MTK_JPEG_HW_H */
