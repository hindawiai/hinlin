<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2019 MediaTek Inc.
 * Author: Xia Jiang <xia.jiang@mediatek.com>
 *
 */

#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <media/videobuf2-core.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "mtk_jpeg_enc_hw.h"

अटल स्थिर काष्ठा mtk_jpeg_enc_qlt mtk_jpeg_enc_quality[] = अणु
	अणु.quality_param = 34, .hardware_value = JPEG_ENC_QUALITY_Q34पूर्ण,
	अणु.quality_param = 39, .hardware_value = JPEG_ENC_QUALITY_Q39पूर्ण,
	अणु.quality_param = 48, .hardware_value = JPEG_ENC_QUALITY_Q48पूर्ण,
	अणु.quality_param = 60, .hardware_value = JPEG_ENC_QUALITY_Q60पूर्ण,
	अणु.quality_param = 64, .hardware_value = JPEG_ENC_QUALITY_Q64पूर्ण,
	अणु.quality_param = 68, .hardware_value = JPEG_ENC_QUALITY_Q68पूर्ण,
	अणु.quality_param = 74, .hardware_value = JPEG_ENC_QUALITY_Q74पूर्ण,
	अणु.quality_param = 80, .hardware_value = JPEG_ENC_QUALITY_Q80पूर्ण,
	अणु.quality_param = 82, .hardware_value = JPEG_ENC_QUALITY_Q82पूर्ण,
	अणु.quality_param = 84, .hardware_value = JPEG_ENC_QUALITY_Q84पूर्ण,
	अणु.quality_param = 87, .hardware_value = JPEG_ENC_QUALITY_Q87पूर्ण,
	अणु.quality_param = 90, .hardware_value = JPEG_ENC_QUALITY_Q90पूर्ण,
	अणु.quality_param = 92, .hardware_value = JPEG_ENC_QUALITY_Q92पूर्ण,
	अणु.quality_param = 95, .hardware_value = JPEG_ENC_QUALITY_Q95पूर्ण,
	अणु.quality_param = 97, .hardware_value = JPEG_ENC_QUALITY_Q97पूर्ण,
पूर्ण;

व्योम mtk_jpeg_enc_reset(व्योम __iomem *base)
अणु
	ग_लिखोl(0, base + JPEG_ENC_RSTB);
	ग_लिखोl(JPEG_ENC_RESET_BIT, base + JPEG_ENC_RSTB);
	ग_लिखोl(0, base + JPEG_ENC_CODEC_SEL);
पूर्ण

u32 mtk_jpeg_enc_get_file_size(व्योम __iomem *base)
अणु
	वापस पढ़ोl(base + JPEG_ENC_DMA_ADDR0) -
	       पढ़ोl(base + JPEG_ENC_DST_ADDR0);
पूर्ण

व्योम mtk_jpeg_enc_start(व्योम __iomem *base)
अणु
	u32 value;

	value = पढ़ोl(base + JPEG_ENC_CTRL);
	value |= JPEG_ENC_CTRL_INT_EN_BIT | JPEG_ENC_CTRL_ENABLE_BIT;
	ग_लिखोl(value, base + JPEG_ENC_CTRL);
पूर्ण

व्योम mtk_jpeg_set_enc_src(काष्ठा mtk_jpeg_ctx *ctx,  व्योम __iomem *base,
			  काष्ठा vb2_buffer *src_buf)
अणु
	पूर्णांक i;
	dma_addr_t dma_addr;

	क्रम (i = 0; i < src_buf->num_planes; i++) अणु
		dma_addr = vb2_dma_contig_plane_dma_addr(src_buf, i) +
			   src_buf->planes[i].data_offset;
		अगर (!i)
			ग_लिखोl(dma_addr, base + JPEG_ENC_SRC_LUMA_ADDR);
		अन्यथा
			ग_लिखोl(dma_addr, base + JPEG_ENC_SRC_CHROMA_ADDR);
	पूर्ण
पूर्ण

व्योम mtk_jpeg_set_enc_dst(काष्ठा mtk_jpeg_ctx *ctx, व्योम __iomem *base,
			  काष्ठा vb2_buffer *dst_buf)
अणु
	dma_addr_t dma_addr;
	माप_प्रकार size;
	u32 dma_addr_offset;
	u32 dma_addr_offseपंचांगask;

	dma_addr = vb2_dma_contig_plane_dma_addr(dst_buf, 0);
	dma_addr_offset = ctx->enable_exअगर ? MTK_JPEG_MAX_EXIF_SIZE : 0;
	dma_addr_offseपंचांगask = dma_addr & JPEG_ENC_DST_ADDR_OFFSET_MASK;
	size = vb2_plane_size(dst_buf, 0);

	ग_लिखोl(dma_addr_offset & ~0xf, base + JPEG_ENC_OFFSET_ADDR);
	ग_लिखोl(dma_addr_offseपंचांगask & 0xf, base + JPEG_ENC_BYTE_OFFSET_MASK);
	ग_लिखोl(dma_addr & ~0xf, base + JPEG_ENC_DST_ADDR0);
	ग_लिखोl((dma_addr + size) & ~0xf, base + JPEG_ENC_STALL_ADDR0);
पूर्ण

व्योम mtk_jpeg_set_enc_params(काष्ठा mtk_jpeg_ctx *ctx,  व्योम __iomem *base)
अणु
	u32 value;
	u32 width = ctx->out_q.enc_crop_rect.width;
	u32 height = ctx->out_q.enc_crop_rect.height;
	u32 enc_क्रमmat = ctx->out_q.fmt->fourcc;
	u32 bytesperline = ctx->out_q.pix_mp.plane_fmt[0].bytesperline;
	u32 blk_num;
	u32 img_stride;
	u32 mem_stride;
	u32 i, enc_quality;

	value = width << 16 | height;
	ग_लिखोl(value, base + JPEG_ENC_IMG_SIZE);

	अगर (enc_क्रमmat == V4L2_PIX_FMT_NV12M ||
	    enc_क्रमmat == V4L2_PIX_FMT_NV21M)
	    /*
	     * Total 8 x 8 block number of luma and chroma.
	     * The number of blocks is counted from 0.
	     */
		blk_num = DIV_ROUND_UP(width, 16) *
			  DIV_ROUND_UP(height, 16) * 6 - 1;
	अन्यथा
		blk_num = DIV_ROUND_UP(width, 16) *
			  DIV_ROUND_UP(height, 8) * 4 - 1;
	ग_लिखोl(blk_num, base + JPEG_ENC_BLK_NUM);

	अगर (enc_क्रमmat == V4L2_PIX_FMT_NV12M ||
	    enc_क्रमmat == V4L2_PIX_FMT_NV21M) अणु
		/* 4:2:0 */
		img_stride = round_up(width, 16);
		mem_stride = bytesperline;
	पूर्ण अन्यथा अणु
		/* 4:2:2 */
		img_stride = round_up(width * 2, 32);
		mem_stride = img_stride;
	पूर्ण
	ग_लिखोl(img_stride, base + JPEG_ENC_IMG_STRIDE);
	ग_लिखोl(mem_stride, base + JPEG_ENC_STRIDE);

	enc_quality = mtk_jpeg_enc_quality[0].hardware_value;
	क्रम (i = 0; i < ARRAY_SIZE(mtk_jpeg_enc_quality); i++) अणु
		अगर (ctx->enc_quality <= mtk_jpeg_enc_quality[i].quality_param) अणु
			enc_quality = mtk_jpeg_enc_quality[i].hardware_value;
			अवरोध;
		पूर्ण
	पूर्ण
	ग_लिखोl(enc_quality, base + JPEG_ENC_QUALITY);

	value = पढ़ोl(base + JPEG_ENC_CTRL);
	value &= ~JPEG_ENC_CTRL_YUV_FORMAT_MASK;
	value |= (ctx->out_q.fmt->hw_क्रमmat & 3) << 3;
	अगर (ctx->enable_exअगर)
		value |= JPEG_ENC_CTRL_खाता_FORMAT_BIT;
	अन्यथा
		value &= ~JPEG_ENC_CTRL_खाता_FORMAT_BIT;
	अगर (ctx->restart_पूर्णांकerval)
		value |= JPEG_ENC_CTRL_RESTART_EN_BIT;
	अन्यथा
		value &= ~JPEG_ENC_CTRL_RESTART_EN_BIT;
	ग_लिखोl(value, base + JPEG_ENC_CTRL);

	ग_लिखोl(ctx->restart_पूर्णांकerval, base + JPEG_ENC_RST_MCU_NUM);
पूर्ण
