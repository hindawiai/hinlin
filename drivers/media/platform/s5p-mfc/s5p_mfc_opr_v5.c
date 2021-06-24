<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/media/platक्रमm/samsung/mfc5/s5p_mfc_opr_v5.c
 *
 * Samsung MFC (Multi Function Codec - FIMV) driver
 * This file contains hw related functions.
 *
 * Kamil Debski, Copyright (c) 2011 Samsung Electronics
 * http://www.samsung.com/
 */

#समावेश "s5p_mfc_common.h"
#समावेश "s5p_mfc_cmd.h"
#समावेश "s5p_mfc_ctrl.h"
#समावेश "s5p_mfc_debug.h"
#समावेश "s5p_mfc_intr.h"
#समावेश "s5p_mfc_pm.h"
#समावेश "s5p_mfc_opr.h"
#समावेश "s5p_mfc_opr_v5.h"
#समावेश <यंत्र/cacheflush.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/firmware.h>
#समावेश <linux/पन.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>

#घोषणा OFFSETA(x)		(((x) - dev->dma_base[BANK_L_CTX]) >> MFC_OFFSET_SHIFT)
#घोषणा OFFSETB(x)		(((x) - dev->dma_base[BANK_R_CTX]) >> MFC_OFFSET_SHIFT)

/* Allocate temporary buffers क्रम decoding */
अटल पूर्णांक s5p_mfc_alloc_dec_temp_buffers_v5(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	काष्ठा s5p_mfc_buf_size_v5 *buf_size = dev->variant->buf_size->priv;
	पूर्णांक ret;

	ctx->dsc.size = buf_size->dsc;
	ret =  s5p_mfc_alloc_priv_buf(dev, BANK_L_CTX, &ctx->dsc);
	अगर (ret) अणु
		mfc_err("Failed to allocate temporary buffer\n");
		वापस ret;
	पूर्ण

	BUG_ON(ctx->dsc.dma & ((1 << MFC_BANK1_ALIGN_ORDER) - 1));
	स_रखो(ctx->dsc.virt, 0, ctx->dsc.size);
	wmb();
	वापस 0;
पूर्ण


/* Release temporary buffers क्रम decoding */
अटल व्योम s5p_mfc_release_dec_desc_buffer_v5(काष्ठा s5p_mfc_ctx *ctx)
अणु
	s5p_mfc_release_priv_buf(ctx->dev, &ctx->dsc);
पूर्ण

/* Allocate codec buffers */
अटल पूर्णांक s5p_mfc_alloc_codec_buffers_v5(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	अचिन्हित पूर्णांक enc_ref_y_size = 0;
	अचिन्हित पूर्णांक enc_ref_c_size = 0;
	अचिन्हित पूर्णांक guard_width, guard_height;
	पूर्णांक ret;

	अगर (ctx->type == MFCINST_DECODER) अणु
		mfc_debug(2, "Luma size:%d Chroma size:%d MV size:%d\n",
			  ctx->luma_size, ctx->chroma_size, ctx->mv_size);
		mfc_debug(2, "Totals bufs: %d\n", ctx->total_dpb_count);
	पूर्ण अन्यथा अगर (ctx->type == MFCINST_ENCODER) अणु
		enc_ref_y_size = ALIGN(ctx->img_width, S5P_FIMV_NV12MT_HALIGN)
			* ALIGN(ctx->img_height, S5P_FIMV_NV12MT_VALIGN);
		enc_ref_y_size = ALIGN(enc_ref_y_size, S5P_FIMV_NV12MT_SALIGN);

		अगर (ctx->codec_mode == S5P_MFC_CODEC_H264_ENC) अणु
			enc_ref_c_size = ALIGN(ctx->img_width,
						S5P_FIMV_NV12MT_HALIGN)
						* ALIGN(ctx->img_height >> 1,
						S5P_FIMV_NV12MT_VALIGN);
			enc_ref_c_size = ALIGN(enc_ref_c_size,
							S5P_FIMV_NV12MT_SALIGN);
		पूर्ण अन्यथा अणु
			guard_width = ALIGN(ctx->img_width + 16,
							S5P_FIMV_NV12MT_HALIGN);
			guard_height = ALIGN((ctx->img_height >> 1) + 4,
							S5P_FIMV_NV12MT_VALIGN);
			enc_ref_c_size = ALIGN(guard_width * guard_height,
					       S5P_FIMV_NV12MT_SALIGN);
		पूर्ण
		mfc_debug(2, "recon luma size: %d chroma size: %d\n",
			  enc_ref_y_size, enc_ref_c_size);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
	/* Codecs have dअगरferent memory requirements */
	चयन (ctx->codec_mode) अणु
	हाल S5P_MFC_CODEC_H264_DEC:
		ctx->bank1.size =
		    ALIGN(S5P_FIMV_DEC_NB_IP_SIZE +
					S5P_FIMV_DEC_VERT_NB_MV_SIZE,
					S5P_FIMV_DEC_BUF_ALIGN);
		ctx->bank2.size = ctx->total_dpb_count * ctx->mv_size;
		अवरोध;
	हाल S5P_MFC_CODEC_MPEG4_DEC:
		ctx->bank1.size =
		    ALIGN(S5P_FIMV_DEC_NB_DCAC_SIZE +
				     S5P_FIMV_DEC_UPNB_MV_SIZE +
				     S5P_FIMV_DEC_SUB_ANCHOR_MV_SIZE +
				     S5P_FIMV_DEC_STX_PARSER_SIZE +
				     S5P_FIMV_DEC_OVERLAP_TRANSFORM_SIZE,
				     S5P_FIMV_DEC_BUF_ALIGN);
		ctx->bank2.size = 0;
		अवरोध;
	हाल S5P_MFC_CODEC_VC1RCV_DEC:
	हाल S5P_MFC_CODEC_VC1_DEC:
		ctx->bank1.size =
		    ALIGN(S5P_FIMV_DEC_OVERLAP_TRANSFORM_SIZE +
			     S5P_FIMV_DEC_UPNB_MV_SIZE +
			     S5P_FIMV_DEC_SUB_ANCHOR_MV_SIZE +
			     S5P_FIMV_DEC_NB_DCAC_SIZE +
			     3 * S5P_FIMV_DEC_VC1_BITPLANE_SIZE,
			     S5P_FIMV_DEC_BUF_ALIGN);
		ctx->bank2.size = 0;
		अवरोध;
	हाल S5P_MFC_CODEC_MPEG2_DEC:
		ctx->bank1.size = 0;
		ctx->bank2.size = 0;
		अवरोध;
	हाल S5P_MFC_CODEC_H263_DEC:
		ctx->bank1.size =
		    ALIGN(S5P_FIMV_DEC_OVERLAP_TRANSFORM_SIZE +
			     S5P_FIMV_DEC_UPNB_MV_SIZE +
			     S5P_FIMV_DEC_SUB_ANCHOR_MV_SIZE +
			     S5P_FIMV_DEC_NB_DCAC_SIZE,
			     S5P_FIMV_DEC_BUF_ALIGN);
		ctx->bank2.size = 0;
		अवरोध;
	हाल S5P_MFC_CODEC_H264_ENC:
		ctx->bank1.size = (enc_ref_y_size * 2) +
				   S5P_FIMV_ENC_UPMV_SIZE +
				   S5P_FIMV_ENC_COLFLG_SIZE +
				   S5P_FIMV_ENC_INTRAMD_SIZE +
				   S5P_FIMV_ENC_NBORINFO_SIZE;
		ctx->bank2.size = (enc_ref_y_size * 2) +
				   (enc_ref_c_size * 4) +
				   S5P_FIMV_ENC_INTRAPRED_SIZE;
		अवरोध;
	हाल S5P_MFC_CODEC_MPEG4_ENC:
		ctx->bank1.size = (enc_ref_y_size * 2) +
				   S5P_FIMV_ENC_UPMV_SIZE +
				   S5P_FIMV_ENC_COLFLG_SIZE +
				   S5P_FIMV_ENC_ACDCCOEF_SIZE;
		ctx->bank2.size = (enc_ref_y_size * 2) +
				   (enc_ref_c_size * 4);
		अवरोध;
	हाल S5P_MFC_CODEC_H263_ENC:
		ctx->bank1.size = (enc_ref_y_size * 2) +
				   S5P_FIMV_ENC_UPMV_SIZE +
				   S5P_FIMV_ENC_ACDCCOEF_SIZE;
		ctx->bank2.size = (enc_ref_y_size * 2) +
				   (enc_ref_c_size * 4);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	/* Allocate only अगर memory from bank 1 is necessary */
	अगर (ctx->bank1.size > 0) अणु

		ret = s5p_mfc_alloc_priv_buf(dev, BANK_L_CTX, &ctx->bank1);
		अगर (ret) अणु
			mfc_err("Failed to allocate Bank1 temporary buffer\n");
			वापस ret;
		पूर्ण
		BUG_ON(ctx->bank1.dma & ((1 << MFC_BANK1_ALIGN_ORDER) - 1));
	पूर्ण
	/* Allocate only अगर memory from bank 2 is necessary */
	अगर (ctx->bank2.size > 0) अणु
		ret = s5p_mfc_alloc_priv_buf(dev, BANK_R_CTX, &ctx->bank2);
		अगर (ret) अणु
			mfc_err("Failed to allocate Bank2 temporary buffer\n");
			s5p_mfc_release_priv_buf(ctx->dev, &ctx->bank1);
			वापस ret;
		पूर्ण
		BUG_ON(ctx->bank2.dma & ((1 << MFC_BANK2_ALIGN_ORDER) - 1));
	पूर्ण
	वापस 0;
पूर्ण

/* Release buffers allocated क्रम codec */
अटल व्योम s5p_mfc_release_codec_buffers_v5(काष्ठा s5p_mfc_ctx *ctx)
अणु
	s5p_mfc_release_priv_buf(ctx->dev, &ctx->bank1);
	s5p_mfc_release_priv_buf(ctx->dev, &ctx->bank2);
पूर्ण

/* Allocate memory क्रम instance data buffer */
अटल पूर्णांक s5p_mfc_alloc_instance_buffer_v5(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	काष्ठा s5p_mfc_buf_size_v5 *buf_size = dev->variant->buf_size->priv;
	पूर्णांक ret;

	अगर (ctx->codec_mode == S5P_MFC_CODEC_H264_DEC ||
		ctx->codec_mode == S5P_MFC_CODEC_H264_ENC)
		ctx->ctx.size = buf_size->h264_ctx;
	अन्यथा
		ctx->ctx.size = buf_size->non_h264_ctx;

	ret = s5p_mfc_alloc_priv_buf(dev, BANK_L_CTX, &ctx->ctx);
	अगर (ret) अणु
		mfc_err("Failed to allocate instance buffer\n");
		वापस ret;
	पूर्ण
	ctx->ctx.ofs = OFFSETA(ctx->ctx.dma);

	/* Zero content of the allocated memory */
	स_रखो(ctx->ctx.virt, 0, ctx->ctx.size);
	wmb();

	/* Initialize shared memory */
	ctx->shm.size = buf_size->shm;
	ret = s5p_mfc_alloc_priv_buf(dev, BANK_L_CTX, &ctx->shm);
	अगर (ret) अणु
		mfc_err("Failed to allocate shared memory buffer\n");
		s5p_mfc_release_priv_buf(dev, &ctx->ctx);
		वापस ret;
	पूर्ण

	/* shared memory offset only keeps the offset from base (port a) */
	ctx->shm.ofs = ctx->shm.dma - dev->dma_base[BANK_L_CTX];
	BUG_ON(ctx->shm.ofs & ((1 << MFC_BANK1_ALIGN_ORDER) - 1));

	स_रखो(ctx->shm.virt, 0, buf_size->shm);
	wmb();
	वापस 0;
पूर्ण

/* Release instance buffer */
अटल व्योम s5p_mfc_release_instance_buffer_v5(काष्ठा s5p_mfc_ctx *ctx)
अणु
	s5p_mfc_release_priv_buf(ctx->dev, &ctx->ctx);
	s5p_mfc_release_priv_buf(ctx->dev, &ctx->shm);
पूर्ण

अटल पूर्णांक s5p_mfc_alloc_dev_context_buffer_v5(काष्ठा s5p_mfc_dev *dev)
अणु
	/* NOP */

	वापस 0;
पूर्ण

अटल व्योम s5p_mfc_release_dev_context_buffer_v5(काष्ठा s5p_mfc_dev *dev)
अणु
	/* NOP */
पूर्ण

अटल व्योम s5p_mfc_ग_लिखो_info_v5(काष्ठा s5p_mfc_ctx *ctx, अचिन्हित पूर्णांक data,
			अचिन्हित पूर्णांक ofs)
अणु
	*(u32 *)(ctx->shm.virt + ofs) = data;
	wmb();
पूर्ण

अटल अचिन्हित पूर्णांक s5p_mfc_पढ़ो_info_v5(काष्ठा s5p_mfc_ctx *ctx,
				अचिन्हित दीर्घ ofs)
अणु
	rmb();
	वापस *(u32 *)(ctx->shm.virt + ofs);
पूर्ण

अटल व्योम s5p_mfc_dec_calc_dpb_size_v5(काष्ठा s5p_mfc_ctx *ctx)
अणु
	अचिन्हित पूर्णांक guard_width, guard_height;

	ctx->buf_width = ALIGN(ctx->img_width, S5P_FIMV_NV12MT_HALIGN);
	ctx->buf_height = ALIGN(ctx->img_height, S5P_FIMV_NV12MT_VALIGN);
	mfc_debug(2,
		"SEQ Done: Movie dimensions %dx%d, buffer dimensions: %dx%d\n",
		ctx->img_width,	ctx->img_height, ctx->buf_width,
		ctx->buf_height);

	अगर (ctx->codec_mode == S5P_MFC_CODEC_H264_DEC) अणु
		ctx->luma_size = ALIGN(ctx->buf_width * ctx->buf_height,
				S5P_FIMV_DEC_BUF_ALIGN);
		ctx->chroma_size = ALIGN(ctx->buf_width *
				ALIGN((ctx->img_height >> 1),
					S5P_FIMV_NV12MT_VALIGN),
				S5P_FIMV_DEC_BUF_ALIGN);
		ctx->mv_size = ALIGN(ctx->buf_width *
				ALIGN((ctx->buf_height >> 2),
					S5P_FIMV_NV12MT_VALIGN),
				S5P_FIMV_DEC_BUF_ALIGN);
	पूर्ण अन्यथा अणु
		guard_width =
			ALIGN(ctx->img_width + 24, S5P_FIMV_NV12MT_HALIGN);
		guard_height =
			ALIGN(ctx->img_height + 16, S5P_FIMV_NV12MT_VALIGN);
		ctx->luma_size = ALIGN(guard_width * guard_height,
				S5P_FIMV_DEC_BUF_ALIGN);

		guard_width =
			ALIGN(ctx->img_width + 16, S5P_FIMV_NV12MT_HALIGN);
		guard_height =
			ALIGN((ctx->img_height >> 1) + 4,
					S5P_FIMV_NV12MT_VALIGN);
		ctx->chroma_size = ALIGN(guard_width * guard_height,
				S5P_FIMV_DEC_BUF_ALIGN);

		ctx->mv_size = 0;
	पूर्ण
पूर्ण

अटल व्योम s5p_mfc_enc_calc_src_size_v5(काष्ठा s5p_mfc_ctx *ctx)
अणु
	अगर (ctx->src_fmt->fourcc == V4L2_PIX_FMT_NV12M) अणु
		ctx->buf_width = ALIGN(ctx->img_width, S5P_FIMV_NV12M_HALIGN);

		ctx->luma_size = ALIGN(ctx->img_width, S5P_FIMV_NV12M_HALIGN)
			* ALIGN(ctx->img_height, S5P_FIMV_NV12M_LVALIGN);
		ctx->chroma_size = ALIGN(ctx->img_width, S5P_FIMV_NV12M_HALIGN)
			* ALIGN((ctx->img_height >> 1), S5P_FIMV_NV12M_CVALIGN);

		ctx->luma_size = ALIGN(ctx->luma_size, S5P_FIMV_NV12M_SALIGN);
		ctx->chroma_size =
			ALIGN(ctx->chroma_size, S5P_FIMV_NV12M_SALIGN);
	पूर्ण अन्यथा अगर (ctx->src_fmt->fourcc == V4L2_PIX_FMT_NV12MT) अणु
		ctx->buf_width = ALIGN(ctx->img_width, S5P_FIMV_NV12MT_HALIGN);

		ctx->luma_size = ALIGN(ctx->img_width, S5P_FIMV_NV12MT_HALIGN)
			* ALIGN(ctx->img_height, S5P_FIMV_NV12MT_VALIGN);
		ctx->chroma_size =
			ALIGN(ctx->img_width, S5P_FIMV_NV12MT_HALIGN)
			* ALIGN((ctx->img_height >> 1), S5P_FIMV_NV12MT_VALIGN);

		ctx->luma_size = ALIGN(ctx->luma_size, S5P_FIMV_NV12MT_SALIGN);
		ctx->chroma_size =
			ALIGN(ctx->chroma_size, S5P_FIMV_NV12MT_SALIGN);
	पूर्ण
पूर्ण

/* Set रेजिस्टरs क्रम decoding temporary buffers */
अटल व्योम s5p_mfc_set_dec_desc_buffer(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	काष्ठा s5p_mfc_buf_size_v5 *buf_size = dev->variant->buf_size->priv;

	mfc_ग_लिखो(dev, OFFSETA(ctx->dsc.dma), S5P_FIMV_SI_CH0_DESC_ADR);
	mfc_ग_लिखो(dev, buf_size->dsc, S5P_FIMV_SI_CH0_DESC_SIZE);
पूर्ण

/* Set रेजिस्टरs क्रम shared buffer */
अटल व्योम s5p_mfc_set_shared_buffer(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	mfc_ग_लिखो(dev, ctx->shm.ofs, S5P_FIMV_SI_CH0_HOST_WR_ADR);
पूर्ण

/* Set रेजिस्टरs क्रम decoding stream buffer */
अटल पूर्णांक s5p_mfc_set_dec_stream_buffer_v5(काष्ठा s5p_mfc_ctx *ctx,
		पूर्णांक buf_addr, अचिन्हित पूर्णांक start_num_byte,
		अचिन्हित पूर्णांक buf_size)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;

	mfc_ग_लिखो(dev, OFFSETA(buf_addr), S5P_FIMV_SI_CH0_SB_ST_ADR);
	mfc_ग_लिखो(dev, ctx->dec_src_buf_size, S5P_FIMV_SI_CH0_CPB_SIZE);
	mfc_ग_लिखो(dev, buf_size, S5P_FIMV_SI_CH0_SB_FRM_SIZE);
	s5p_mfc_ग_लिखो_info_v5(ctx, start_num_byte, START_BYTE_NUM);
	वापस 0;
पूर्ण

/* Set decoding frame buffer */
अटल पूर्णांक s5p_mfc_set_dec_frame_buffer_v5(काष्ठा s5p_mfc_ctx *ctx)
अणु
	अचिन्हित पूर्णांक frame_size_lu, i;
	अचिन्हित पूर्णांक frame_size_ch, frame_size_mv;
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	अचिन्हित पूर्णांक dpb;
	माप_प्रकार buf_addr1, buf_addr2;
	पूर्णांक buf_size1, buf_size2;

	buf_addr1 = ctx->bank1.dma;
	buf_size1 = ctx->bank1.size;
	buf_addr2 = ctx->bank2.dma;
	buf_size2 = ctx->bank2.size;
	dpb = mfc_पढ़ो(dev, S5P_FIMV_SI_CH0_DPB_CONF_CTRL) &
						~S5P_FIMV_DPB_COUNT_MASK;
	mfc_ग_लिखो(dev, ctx->total_dpb_count | dpb,
						S5P_FIMV_SI_CH0_DPB_CONF_CTRL);
	s5p_mfc_set_shared_buffer(ctx);
	चयन (ctx->codec_mode) अणु
	हाल S5P_MFC_CODEC_H264_DEC:
		mfc_ग_लिखो(dev, OFFSETA(buf_addr1),
						S5P_FIMV_H264_VERT_NB_MV_ADR);
		buf_addr1 += S5P_FIMV_DEC_VERT_NB_MV_SIZE;
		buf_size1 -= S5P_FIMV_DEC_VERT_NB_MV_SIZE;
		mfc_ग_लिखो(dev, OFFSETA(buf_addr1), S5P_FIMV_H264_NB_IP_ADR);
		buf_addr1 += S5P_FIMV_DEC_NB_IP_SIZE;
		buf_size1 -= S5P_FIMV_DEC_NB_IP_SIZE;
		अवरोध;
	हाल S5P_MFC_CODEC_MPEG4_DEC:
		mfc_ग_लिखो(dev, OFFSETA(buf_addr1), S5P_FIMV_MPEG4_NB_DCAC_ADR);
		buf_addr1 += S5P_FIMV_DEC_NB_DCAC_SIZE;
		buf_size1 -= S5P_FIMV_DEC_NB_DCAC_SIZE;
		mfc_ग_लिखो(dev, OFFSETA(buf_addr1), S5P_FIMV_MPEG4_UP_NB_MV_ADR);
		buf_addr1 += S5P_FIMV_DEC_UPNB_MV_SIZE;
		buf_size1 -= S5P_FIMV_DEC_UPNB_MV_SIZE;
		mfc_ग_लिखो(dev, OFFSETA(buf_addr1), S5P_FIMV_MPEG4_SA_MV_ADR);
		buf_addr1 += S5P_FIMV_DEC_SUB_ANCHOR_MV_SIZE;
		buf_size1 -= S5P_FIMV_DEC_SUB_ANCHOR_MV_SIZE;
		mfc_ग_लिखो(dev, OFFSETA(buf_addr1), S5P_FIMV_MPEG4_SP_ADR);
		buf_addr1 += S5P_FIMV_DEC_STX_PARSER_SIZE;
		buf_size1 -= S5P_FIMV_DEC_STX_PARSER_SIZE;
		mfc_ग_लिखो(dev, OFFSETA(buf_addr1), S5P_FIMV_MPEG4_OT_LINE_ADR);
		buf_addr1 += S5P_FIMV_DEC_OVERLAP_TRANSFORM_SIZE;
		buf_size1 -= S5P_FIMV_DEC_OVERLAP_TRANSFORM_SIZE;
		अवरोध;
	हाल S5P_MFC_CODEC_H263_DEC:
		mfc_ग_लिखो(dev, OFFSETA(buf_addr1), S5P_FIMV_H263_OT_LINE_ADR);
		buf_addr1 += S5P_FIMV_DEC_OVERLAP_TRANSFORM_SIZE;
		buf_size1 -= S5P_FIMV_DEC_OVERLAP_TRANSFORM_SIZE;
		mfc_ग_लिखो(dev, OFFSETA(buf_addr1), S5P_FIMV_H263_UP_NB_MV_ADR);
		buf_addr1 += S5P_FIMV_DEC_UPNB_MV_SIZE;
		buf_size1 -= S5P_FIMV_DEC_UPNB_MV_SIZE;
		mfc_ग_लिखो(dev, OFFSETA(buf_addr1), S5P_FIMV_H263_SA_MV_ADR);
		buf_addr1 += S5P_FIMV_DEC_SUB_ANCHOR_MV_SIZE;
		buf_size1 -= S5P_FIMV_DEC_SUB_ANCHOR_MV_SIZE;
		mfc_ग_लिखो(dev, OFFSETA(buf_addr1), S5P_FIMV_H263_NB_DCAC_ADR);
		buf_addr1 += S5P_FIMV_DEC_NB_DCAC_SIZE;
		buf_size1 -= S5P_FIMV_DEC_NB_DCAC_SIZE;
		अवरोध;
	हाल S5P_MFC_CODEC_VC1_DEC:
	हाल S5P_MFC_CODEC_VC1RCV_DEC:
		mfc_ग_लिखो(dev, OFFSETA(buf_addr1), S5P_FIMV_VC1_NB_DCAC_ADR);
		buf_addr1 += S5P_FIMV_DEC_NB_DCAC_SIZE;
		buf_size1 -= S5P_FIMV_DEC_NB_DCAC_SIZE;
		mfc_ग_लिखो(dev, OFFSETA(buf_addr1), S5P_FIMV_VC1_OT_LINE_ADR);
		buf_addr1 += S5P_FIMV_DEC_OVERLAP_TRANSFORM_SIZE;
		buf_size1 -= S5P_FIMV_DEC_OVERLAP_TRANSFORM_SIZE;
		mfc_ग_लिखो(dev, OFFSETA(buf_addr1), S5P_FIMV_VC1_UP_NB_MV_ADR);
		buf_addr1 += S5P_FIMV_DEC_UPNB_MV_SIZE;
		buf_size1 -= S5P_FIMV_DEC_UPNB_MV_SIZE;
		mfc_ग_लिखो(dev, OFFSETA(buf_addr1), S5P_FIMV_VC1_SA_MV_ADR);
		buf_addr1 += S5P_FIMV_DEC_SUB_ANCHOR_MV_SIZE;
		buf_size1 -= S5P_FIMV_DEC_SUB_ANCHOR_MV_SIZE;
		mfc_ग_लिखो(dev, OFFSETA(buf_addr1), S5P_FIMV_VC1_BITPLANE3_ADR);
		buf_addr1 += S5P_FIMV_DEC_VC1_BITPLANE_SIZE;
		buf_size1 -= S5P_FIMV_DEC_VC1_BITPLANE_SIZE;
		mfc_ग_लिखो(dev, OFFSETA(buf_addr1), S5P_FIMV_VC1_BITPLANE2_ADR);
		buf_addr1 += S5P_FIMV_DEC_VC1_BITPLANE_SIZE;
		buf_size1 -= S5P_FIMV_DEC_VC1_BITPLANE_SIZE;
		mfc_ग_लिखो(dev, OFFSETA(buf_addr1), S5P_FIMV_VC1_BITPLANE1_ADR);
		buf_addr1 += S5P_FIMV_DEC_VC1_BITPLANE_SIZE;
		buf_size1 -= S5P_FIMV_DEC_VC1_BITPLANE_SIZE;
		अवरोध;
	हाल S5P_MFC_CODEC_MPEG2_DEC:
		अवरोध;
	शेष:
		mfc_err("Unknown codec for decoding (%x)\n",
			ctx->codec_mode);
		वापस -EINVAL;
	पूर्ण
	frame_size_lu = ctx->luma_size;
	frame_size_ch = ctx->chroma_size;
	frame_size_mv = ctx->mv_size;
	mfc_debug(2, "Frm size: %d ch: %d mv: %d\n", frame_size_lu, frame_size_ch,
								frame_size_mv);
	क्रम (i = 0; i < ctx->total_dpb_count; i++) अणु
		/* Bank2 */
		mfc_debug(2, "Luma %d: %zx\n", i,
					ctx->dst_bufs[i].cookie.raw.luma);
		mfc_ग_लिखो(dev, OFFSETB(ctx->dst_bufs[i].cookie.raw.luma),
						S5P_FIMV_DEC_LUMA_ADR + i * 4);
		mfc_debug(2, "\tChroma %d: %zx\n", i,
					ctx->dst_bufs[i].cookie.raw.chroma);
		mfc_ग_लिखो(dev, OFFSETA(ctx->dst_bufs[i].cookie.raw.chroma),
					       S5P_FIMV_DEC_CHROMA_ADR + i * 4);
		अगर (ctx->codec_mode == S5P_MFC_CODEC_H264_DEC) अणु
			mfc_debug(2, "\tBuf2: %zx, size: %d\n",
							buf_addr2, buf_size2);
			mfc_ग_लिखो(dev, OFFSETB(buf_addr2),
						S5P_FIMV_H264_MV_ADR + i * 4);
			buf_addr2 += frame_size_mv;
			buf_size2 -= frame_size_mv;
		पूर्ण
	पूर्ण
	mfc_debug(2, "Buf1: %zu, buf_size1: %d\n", buf_addr1, buf_size1);
	mfc_debug(2, "Buf 1/2 size after: %d/%d (frames %d)\n",
			buf_size1,  buf_size2, ctx->total_dpb_count);
	अगर (buf_size1 < 0 || buf_size2 < 0) अणु
		mfc_debug(2, "Not enough memory has been allocated\n");
		वापस -ENOMEM;
	पूर्ण
	s5p_mfc_ग_लिखो_info_v5(ctx, frame_size_lu, ALLOC_LUMA_DPB_SIZE);
	s5p_mfc_ग_लिखो_info_v5(ctx, frame_size_ch, ALLOC_CHROMA_DPB_SIZE);
	अगर (ctx->codec_mode == S5P_MFC_CODEC_H264_DEC)
		s5p_mfc_ग_लिखो_info_v5(ctx, frame_size_mv, ALLOC_MV_SIZE);
	mfc_ग_लिखो(dev, ((S5P_FIMV_CH_INIT_BUFS & S5P_FIMV_CH_MASK)
					<< S5P_FIMV_CH_SHIFT) | (ctx->inst_no),
						S5P_FIMV_SI_CH0_INST_ID);
	वापस 0;
पूर्ण

/* Set रेजिस्टरs क्रम encoding stream buffer */
अटल पूर्णांक s5p_mfc_set_enc_stream_buffer_v5(काष्ठा s5p_mfc_ctx *ctx,
		अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक size)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;

	mfc_ग_लिखो(dev, OFFSETA(addr), S5P_FIMV_ENC_SI_CH0_SB_ADR);
	mfc_ग_लिखो(dev, size, S5P_FIMV_ENC_SI_CH0_SB_SIZE);
	वापस 0;
पूर्ण

अटल व्योम s5p_mfc_set_enc_frame_buffer_v5(काष्ठा s5p_mfc_ctx *ctx,
		अचिन्हित दीर्घ y_addr, अचिन्हित दीर्घ c_addr)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;

	mfc_ग_लिखो(dev, OFFSETB(y_addr), S5P_FIMV_ENC_SI_CH0_CUR_Y_ADR);
	mfc_ग_लिखो(dev, OFFSETB(c_addr), S5P_FIMV_ENC_SI_CH0_CUR_C_ADR);
पूर्ण

अटल व्योम s5p_mfc_get_enc_frame_buffer_v5(काष्ठा s5p_mfc_ctx *ctx,
		अचिन्हित दीर्घ *y_addr, अचिन्हित दीर्घ *c_addr)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;

	*y_addr = dev->dma_base[BANK_R_CTX] +
		  (mfc_पढ़ो(dev, S5P_FIMV_ENCODED_Y_ADDR) << MFC_OFFSET_SHIFT);
	*c_addr = dev->dma_base[BANK_R_CTX] +
		  (mfc_पढ़ो(dev, S5P_FIMV_ENCODED_C_ADDR) << MFC_OFFSET_SHIFT);
पूर्ण

/* Set encoding ref & codec buffer */
अटल पूर्णांक s5p_mfc_set_enc_ref_buffer_v5(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	माप_प्रकार buf_addr1, buf_addr2;
	माप_प्रकार buf_size1, buf_size2;
	अचिन्हित पूर्णांक enc_ref_y_size, enc_ref_c_size;
	अचिन्हित पूर्णांक guard_width, guard_height;
	पूर्णांक i;

	buf_addr1 = ctx->bank1.dma;
	buf_size1 = ctx->bank1.size;
	buf_addr2 = ctx->bank2.dma;
	buf_size2 = ctx->bank2.size;
	enc_ref_y_size = ALIGN(ctx->img_width, S5P_FIMV_NV12MT_HALIGN)
		* ALIGN(ctx->img_height, S5P_FIMV_NV12MT_VALIGN);
	enc_ref_y_size = ALIGN(enc_ref_y_size, S5P_FIMV_NV12MT_SALIGN);
	अगर (ctx->codec_mode == S5P_MFC_CODEC_H264_ENC) अणु
		enc_ref_c_size = ALIGN(ctx->img_width, S5P_FIMV_NV12MT_HALIGN)
			* ALIGN((ctx->img_height >> 1), S5P_FIMV_NV12MT_VALIGN);
		enc_ref_c_size = ALIGN(enc_ref_c_size, S5P_FIMV_NV12MT_SALIGN);
	पूर्ण अन्यथा अणु
		guard_width = ALIGN(ctx->img_width + 16,
						S5P_FIMV_NV12MT_HALIGN);
		guard_height = ALIGN((ctx->img_height >> 1) + 4,
						S5P_FIMV_NV12MT_VALIGN);
		enc_ref_c_size = ALIGN(guard_width * guard_height,
				       S5P_FIMV_NV12MT_SALIGN);
	पूर्ण
	mfc_debug(2, "buf_size1: %zu, buf_size2: %zu\n", buf_size1, buf_size2);
	चयन (ctx->codec_mode) अणु
	हाल S5P_MFC_CODEC_H264_ENC:
		क्रम (i = 0; i < 2; i++) अणु
			mfc_ग_लिखो(dev, OFFSETA(buf_addr1),
				S5P_FIMV_ENC_REF0_LUMA_ADR + (4 * i));
			buf_addr1 += enc_ref_y_size;
			buf_size1 -= enc_ref_y_size;

			mfc_ग_लिखो(dev, OFFSETB(buf_addr2),
				S5P_FIMV_ENC_REF2_LUMA_ADR + (4 * i));
			buf_addr2 += enc_ref_y_size;
			buf_size2 -= enc_ref_y_size;
		पूर्ण
		क्रम (i = 0; i < 4; i++) अणु
			mfc_ग_लिखो(dev, OFFSETB(buf_addr2),
				S5P_FIMV_ENC_REF0_CHROMA_ADR + (4 * i));
			buf_addr2 += enc_ref_c_size;
			buf_size2 -= enc_ref_c_size;
		पूर्ण
		mfc_ग_लिखो(dev, OFFSETA(buf_addr1), S5P_FIMV_H264_UP_MV_ADR);
		buf_addr1 += S5P_FIMV_ENC_UPMV_SIZE;
		buf_size1 -= S5P_FIMV_ENC_UPMV_SIZE;
		mfc_ग_लिखो(dev, OFFSETA(buf_addr1),
					S5P_FIMV_H264_COZERO_FLAG_ADR);
		buf_addr1 += S5P_FIMV_ENC_COLFLG_SIZE;
		buf_size1 -= S5P_FIMV_ENC_COLFLG_SIZE;
		mfc_ग_लिखो(dev, OFFSETA(buf_addr1),
					S5P_FIMV_H264_UP_INTRA_MD_ADR);
		buf_addr1 += S5P_FIMV_ENC_INTRAMD_SIZE;
		buf_size1 -= S5P_FIMV_ENC_INTRAMD_SIZE;
		mfc_ग_लिखो(dev, OFFSETB(buf_addr2),
					S5P_FIMV_H264_UP_INTRA_PRED_ADR);
		buf_addr2 += S5P_FIMV_ENC_INTRAPRED_SIZE;
		buf_size2 -= S5P_FIMV_ENC_INTRAPRED_SIZE;
		mfc_ग_लिखो(dev, OFFSETA(buf_addr1),
					S5P_FIMV_H264_NBOR_INFO_ADR);
		buf_addr1 += S5P_FIMV_ENC_NBORINFO_SIZE;
		buf_size1 -= S5P_FIMV_ENC_NBORINFO_SIZE;
		mfc_debug(2, "buf_size1: %zu, buf_size2: %zu\n",
			buf_size1, buf_size2);
		अवरोध;
	हाल S5P_MFC_CODEC_MPEG4_ENC:
		क्रम (i = 0; i < 2; i++) अणु
			mfc_ग_लिखो(dev, OFFSETA(buf_addr1),
				S5P_FIMV_ENC_REF0_LUMA_ADR + (4 * i));
			buf_addr1 += enc_ref_y_size;
			buf_size1 -= enc_ref_y_size;
			mfc_ग_लिखो(dev, OFFSETB(buf_addr2),
				S5P_FIMV_ENC_REF2_LUMA_ADR + (4 * i));
			buf_addr2 += enc_ref_y_size;
			buf_size2 -= enc_ref_y_size;
		पूर्ण
		क्रम (i = 0; i < 4; i++) अणु
			mfc_ग_लिखो(dev, OFFSETB(buf_addr2),
				S5P_FIMV_ENC_REF0_CHROMA_ADR + (4 * i));
			buf_addr2 += enc_ref_c_size;
			buf_size2 -= enc_ref_c_size;
		पूर्ण
		mfc_ग_लिखो(dev, OFFSETA(buf_addr1), S5P_FIMV_MPEG4_UP_MV_ADR);
		buf_addr1 += S5P_FIMV_ENC_UPMV_SIZE;
		buf_size1 -= S5P_FIMV_ENC_UPMV_SIZE;
		mfc_ग_लिखो(dev, OFFSETA(buf_addr1),
						S5P_FIMV_MPEG4_COZERO_FLAG_ADR);
		buf_addr1 += S5P_FIMV_ENC_COLFLG_SIZE;
		buf_size1 -= S5P_FIMV_ENC_COLFLG_SIZE;
		mfc_ग_लिखो(dev, OFFSETA(buf_addr1),
						S5P_FIMV_MPEG4_ACDC_COEF_ADR);
		buf_addr1 += S5P_FIMV_ENC_ACDCCOEF_SIZE;
		buf_size1 -= S5P_FIMV_ENC_ACDCCOEF_SIZE;
		mfc_debug(2, "buf_size1: %zu, buf_size2: %zu\n",
			buf_size1, buf_size2);
		अवरोध;
	हाल S5P_MFC_CODEC_H263_ENC:
		क्रम (i = 0; i < 2; i++) अणु
			mfc_ग_लिखो(dev, OFFSETA(buf_addr1),
				S5P_FIMV_ENC_REF0_LUMA_ADR + (4 * i));
			buf_addr1 += enc_ref_y_size;
			buf_size1 -= enc_ref_y_size;
			mfc_ग_लिखो(dev, OFFSETB(buf_addr2),
				S5P_FIMV_ENC_REF2_LUMA_ADR + (4 * i));
			buf_addr2 += enc_ref_y_size;
			buf_size2 -= enc_ref_y_size;
		पूर्ण
		क्रम (i = 0; i < 4; i++) अणु
			mfc_ग_लिखो(dev, OFFSETB(buf_addr2),
				S5P_FIMV_ENC_REF0_CHROMA_ADR + (4 * i));
			buf_addr2 += enc_ref_c_size;
			buf_size2 -= enc_ref_c_size;
		पूर्ण
		mfc_ग_लिखो(dev, OFFSETA(buf_addr1), S5P_FIMV_H263_UP_MV_ADR);
		buf_addr1 += S5P_FIMV_ENC_UPMV_SIZE;
		buf_size1 -= S5P_FIMV_ENC_UPMV_SIZE;
		mfc_ग_लिखो(dev, OFFSETA(buf_addr1), S5P_FIMV_H263_ACDC_COEF_ADR);
		buf_addr1 += S5P_FIMV_ENC_ACDCCOEF_SIZE;
		buf_size1 -= S5P_FIMV_ENC_ACDCCOEF_SIZE;
		mfc_debug(2, "buf_size1: %zu, buf_size2: %zu\n",
			buf_size1, buf_size2);
		अवरोध;
	शेष:
		mfc_err("Unknown codec set for encoding: %d\n",
			ctx->codec_mode);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक s5p_mfc_set_enc_params(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	काष्ठा s5p_mfc_enc_params *p = &ctx->enc_params;
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक shm;

	/* width */
	mfc_ग_लिखो(dev, ctx->img_width, S5P_FIMV_ENC_HSIZE_PX);
	/* height */
	mfc_ग_लिखो(dev, ctx->img_height, S5P_FIMV_ENC_VSIZE_PX);
	/* pictype : enable, IDR period */
	reg = mfc_पढ़ो(dev, S5P_FIMV_ENC_PIC_TYPE_CTRL);
	reg |= (1 << 18);
	reg &= ~(0xFFFF);
	reg |= p->gop_size;
	mfc_ग_लिखो(dev, reg, S5P_FIMV_ENC_PIC_TYPE_CTRL);
	mfc_ग_लिखो(dev, 0, S5P_FIMV_ENC_B_RECON_WRITE_ON);
	/* multi-slice control */
	/* multi-slice MB number or bit size */
	mfc_ग_लिखो(dev, p->slice_mode, S5P_FIMV_ENC_MSLICE_CTRL);
	अगर (p->slice_mode == V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_MAX_MB) अणु
		mfc_ग_लिखो(dev, p->slice_mb, S5P_FIMV_ENC_MSLICE_MB);
	पूर्ण अन्यथा अगर (p->slice_mode == V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_MAX_BYTES) अणु
		mfc_ग_लिखो(dev, p->slice_bit, S5P_FIMV_ENC_MSLICE_BIT);
	पूर्ण अन्यथा अणु
		mfc_ग_लिखो(dev, 0, S5P_FIMV_ENC_MSLICE_MB);
		mfc_ग_लिखो(dev, 0, S5P_FIMV_ENC_MSLICE_BIT);
	पूर्ण
	/* cyclic पूर्णांकra refresh */
	mfc_ग_लिखो(dev, p->पूर्णांकra_refresh_mb, S5P_FIMV_ENC_CIR_CTRL);
	/* memory काष्ठाure cur. frame */
	अगर (ctx->src_fmt->fourcc == V4L2_PIX_FMT_NV12M)
		mfc_ग_लिखो(dev, 0, S5P_FIMV_ENC_MAP_FOR_CUR);
	अन्यथा अगर (ctx->src_fmt->fourcc == V4L2_PIX_FMT_NV12MT)
		mfc_ग_लिखो(dev, 3, S5P_FIMV_ENC_MAP_FOR_CUR);
	/* padding control & value */
	reg = mfc_पढ़ो(dev, S5P_FIMV_ENC_PADDING_CTRL);
	अगर (p->pad) अणु
		/** enable */
		reg |= (1UL << 31);
		/** cr value */
		reg &= ~(0xFF << 16);
		reg |= (p->pad_cr << 16);
		/** cb value */
		reg &= ~(0xFF << 8);
		reg |= (p->pad_cb << 8);
		/** y value */
		reg &= ~(0xFF);
		reg |= (p->pad_luma);
	पूर्ण अन्यथा अणु
		/** disable & all value clear */
		reg = 0;
	पूर्ण
	mfc_ग_लिखो(dev, reg, S5P_FIMV_ENC_PADDING_CTRL);
	/* rate control config. */
	reg = mfc_पढ़ो(dev, S5P_FIMV_ENC_RC_CONFIG);
	/** frame-level rate control */
	reg &= ~(0x1 << 9);
	reg |= (p->rc_frame << 9);
	mfc_ग_लिखो(dev, reg, S5P_FIMV_ENC_RC_CONFIG);
	/* bit rate */
	अगर (p->rc_frame)
		mfc_ग_लिखो(dev, p->rc_bitrate,
			S5P_FIMV_ENC_RC_BIT_RATE);
	अन्यथा
		mfc_ग_लिखो(dev, 0, S5P_FIMV_ENC_RC_BIT_RATE);
	/* reaction coefficient */
	अगर (p->rc_frame)
		mfc_ग_लिखो(dev, p->rc_reaction_coeff, S5P_FIMV_ENC_RC_RPARA);
	shm = s5p_mfc_पढ़ो_info_v5(ctx, EXT_ENC_CONTROL);
	/* seq header ctrl */
	shm &= ~(0x1 << 3);
	shm |= (p->seq_hdr_mode << 3);
	/* frame skip mode */
	shm &= ~(0x3 << 1);
	shm |= (p->frame_skip_mode << 1);
	s5p_mfc_ग_लिखो_info_v5(ctx, shm, EXT_ENC_CONTROL);
	/* fixed target bit */
	s5p_mfc_ग_लिखो_info_v5(ctx, p->fixed_target_bit, RC_CONTROL_CONFIG);
	वापस 0;
पूर्ण

अटल पूर्णांक s5p_mfc_set_enc_params_h264(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	काष्ठा s5p_mfc_enc_params *p = &ctx->enc_params;
	काष्ठा s5p_mfc_h264_enc_params *p_264 = &p->codec.h264;
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक shm;

	s5p_mfc_set_enc_params(ctx);
	/* pictype : number of B */
	reg = mfc_पढ़ो(dev, S5P_FIMV_ENC_PIC_TYPE_CTRL);
	/* num_b_frame - 0 ~ 2 */
	reg &= ~(0x3 << 16);
	reg |= (p->num_b_frame << 16);
	mfc_ग_लिखो(dev, reg, S5P_FIMV_ENC_PIC_TYPE_CTRL);
	/* profile & level */
	reg = mfc_पढ़ो(dev, S5P_FIMV_ENC_PROखाता);
	/* level */
	reg &= ~(0xFF << 8);
	reg |= (p_264->level << 8);
	/* profile - 0 ~ 2 */
	reg &= ~(0x3F);
	reg |= p_264->profile;
	mfc_ग_लिखो(dev, reg, S5P_FIMV_ENC_PROखाता);
	/* पूर्णांकerlace  */
	mfc_ग_लिखो(dev, p_264->पूर्णांकerlace, S5P_FIMV_ENC_PIC_STRUCT);
	/* height */
	अगर (p_264->पूर्णांकerlace)
		mfc_ग_लिखो(dev, ctx->img_height >> 1, S5P_FIMV_ENC_VSIZE_PX);
	/* loopfilter ctrl */
	mfc_ग_लिखो(dev, p_264->loop_filter_mode, S5P_FIMV_ENC_LF_CTRL);
	/* loopfilter alpha offset */
	अगर (p_264->loop_filter_alpha < 0) अणु
		reg = 0x10;
		reg |= (0xFF - p_264->loop_filter_alpha) + 1;
	पूर्ण अन्यथा अणु
		reg = 0x00;
		reg |= (p_264->loop_filter_alpha & 0xF);
	पूर्ण
	mfc_ग_लिखो(dev, reg, S5P_FIMV_ENC_ALPHA_OFF);
	/* loopfilter beta offset */
	अगर (p_264->loop_filter_beta < 0) अणु
		reg = 0x10;
		reg |= (0xFF - p_264->loop_filter_beta) + 1;
	पूर्ण अन्यथा अणु
		reg = 0x00;
		reg |= (p_264->loop_filter_beta & 0xF);
	पूर्ण
	mfc_ग_लिखो(dev, reg, S5P_FIMV_ENC_BETA_OFF);
	/* entropy coding mode */
	अगर (p_264->entropy_mode == V4L2_MPEG_VIDEO_H264_ENTROPY_MODE_CABAC)
		mfc_ग_लिखो(dev, 1, S5P_FIMV_ENC_H264_ENTROPY_MODE);
	अन्यथा
		mfc_ग_लिखो(dev, 0, S5P_FIMV_ENC_H264_ENTROPY_MODE);
	/* number of ref. picture */
	reg = mfc_पढ़ो(dev, S5P_FIMV_ENC_H264_NUM_OF_REF);
	/* num of ref. pictures of P */
	reg &= ~(0x3 << 5);
	reg |= (p_264->num_ref_pic_4p << 5);
	/* max number of ref. pictures */
	reg &= ~(0x1F);
	reg |= p_264->max_ref_pic;
	mfc_ग_लिखो(dev, reg, S5P_FIMV_ENC_H264_NUM_OF_REF);
	/* 8x8 transक्रमm enable */
	mfc_ग_लिखो(dev, p_264->_8x8_transक्रमm, S5P_FIMV_ENC_H264_TRANS_FLAG);
	/* rate control config. */
	reg = mfc_पढ़ो(dev, S5P_FIMV_ENC_RC_CONFIG);
	/* macroblock level rate control */
	reg &= ~(0x1 << 8);
	reg |= (p->rc_mb << 8);
	/* frame QP */
	reg &= ~(0x3F);
	reg |= p_264->rc_frame_qp;
	mfc_ग_लिखो(dev, reg, S5P_FIMV_ENC_RC_CONFIG);
	/* frame rate */
	अगर (p->rc_frame && p->rc_framerate_denom)
		mfc_ग_लिखो(dev, p->rc_framerate_num * 1000
			/ p->rc_framerate_denom, S5P_FIMV_ENC_RC_FRAME_RATE);
	अन्यथा
		mfc_ग_लिखो(dev, 0, S5P_FIMV_ENC_RC_FRAME_RATE);
	/* max & min value of QP */
	reg = mfc_पढ़ो(dev, S5P_FIMV_ENC_RC_QBOUND);
	/* max QP */
	reg &= ~(0x3F << 8);
	reg |= (p_264->rc_max_qp << 8);
	/* min QP */
	reg &= ~(0x3F);
	reg |= p_264->rc_min_qp;
	mfc_ग_लिखो(dev, reg, S5P_FIMV_ENC_RC_QBOUND);
	/* macroblock adaptive scaling features */
	अगर (p->rc_mb) अणु
		reg = mfc_पढ़ो(dev, S5P_FIMV_ENC_RC_MB_CTRL);
		/* dark region */
		reg &= ~(0x1 << 3);
		reg |= (p_264->rc_mb_dark << 3);
		/* smooth region */
		reg &= ~(0x1 << 2);
		reg |= (p_264->rc_mb_smooth << 2);
		/* अटल region */
		reg &= ~(0x1 << 1);
		reg |= (p_264->rc_mb_अटल << 1);
		/* high activity region */
		reg &= ~(0x1);
		reg |= p_264->rc_mb_activity;
		mfc_ग_लिखो(dev, reg, S5P_FIMV_ENC_RC_MB_CTRL);
	पूर्ण
	अगर (!p->rc_frame && !p->rc_mb) अणु
		shm = s5p_mfc_पढ़ो_info_v5(ctx, P_B_FRAME_QP);
		shm &= ~(0xFFF);
		shm |= ((p_264->rc_b_frame_qp & 0x3F) << 6);
		shm |= (p_264->rc_p_frame_qp & 0x3F);
		s5p_mfc_ग_लिखो_info_v5(ctx, shm, P_B_FRAME_QP);
	पूर्ण
	/* extended encoder ctrl */
	shm = s5p_mfc_पढ़ो_info_v5(ctx, EXT_ENC_CONTROL);
	/* AR VUI control */
	shm &= ~(0x1 << 15);
	shm |= (p_264->vui_sar << 1);
	s5p_mfc_ग_लिखो_info_v5(ctx, shm, EXT_ENC_CONTROL);
	अगर (p_264->vui_sar) अणु
		/* aspect ration IDC */
		shm = s5p_mfc_पढ़ो_info_v5(ctx, SAMPLE_ASPECT_RATIO_IDC);
		shm &= ~(0xFF);
		shm |= p_264->vui_sar_idc;
		s5p_mfc_ग_लिखो_info_v5(ctx, shm, SAMPLE_ASPECT_RATIO_IDC);
		अगर (p_264->vui_sar_idc == 0xFF) अणु
			/* sample  AR info */
			shm = s5p_mfc_पढ़ो_info_v5(ctx, EXTENDED_SAR);
			shm &= ~(0xFFFFFFFF);
			shm |= p_264->vui_ext_sar_width << 16;
			shm |= p_264->vui_ext_sar_height;
			s5p_mfc_ग_लिखो_info_v5(ctx, shm, EXTENDED_SAR);
		पूर्ण
	पूर्ण
	/* पूर्णांकra picture period क्रम H.264 */
	shm = s5p_mfc_पढ़ो_info_v5(ctx, H264_I_PERIOD);
	/* control */
	shm &= ~(0x1 << 16);
	shm |= (p_264->खोलो_gop << 16);
	/* value */
	अगर (p_264->खोलो_gop) अणु
		shm &= ~(0xFFFF);
		shm |= p_264->खोलो_gop_size;
	पूर्ण
	s5p_mfc_ग_लिखो_info_v5(ctx, shm, H264_I_PERIOD);
	/* extended encoder ctrl */
	shm = s5p_mfc_पढ़ो_info_v5(ctx, EXT_ENC_CONTROL);
	/* vbv buffer size */
	अगर (p->frame_skip_mode ==
			V4L2_MPEG_MFC51_VIDEO_FRAME_SKIP_MODE_BUF_LIMIT) अणु
		shm &= ~(0xFFFF << 16);
		shm |= (p_264->cpb_size << 16);
	पूर्ण
	s5p_mfc_ग_लिखो_info_v5(ctx, shm, EXT_ENC_CONTROL);
	वापस 0;
पूर्ण

अटल पूर्णांक s5p_mfc_set_enc_params_mpeg4(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	काष्ठा s5p_mfc_enc_params *p = &ctx->enc_params;
	काष्ठा s5p_mfc_mpeg4_enc_params *p_mpeg4 = &p->codec.mpeg4;
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक shm;
	अचिन्हित पूर्णांक framerate;

	s5p_mfc_set_enc_params(ctx);
	/* pictype : number of B */
	reg = mfc_पढ़ो(dev, S5P_FIMV_ENC_PIC_TYPE_CTRL);
	/* num_b_frame - 0 ~ 2 */
	reg &= ~(0x3 << 16);
	reg |= (p->num_b_frame << 16);
	mfc_ग_लिखो(dev, reg, S5P_FIMV_ENC_PIC_TYPE_CTRL);
	/* profile & level */
	reg = mfc_पढ़ो(dev, S5P_FIMV_ENC_PROखाता);
	/* level */
	reg &= ~(0xFF << 8);
	reg |= (p_mpeg4->level << 8);
	/* profile - 0 ~ 2 */
	reg &= ~(0x3F);
	reg |= p_mpeg4->profile;
	mfc_ग_लिखो(dev, reg, S5P_FIMV_ENC_PROखाता);
	/* quarter_pixel */
	mfc_ग_लिखो(dev, p_mpeg4->quarter_pixel, S5P_FIMV_ENC_MPEG4_QUART_PXL);
	/* qp */
	अगर (!p->rc_frame) अणु
		shm = s5p_mfc_पढ़ो_info_v5(ctx, P_B_FRAME_QP);
		shm &= ~(0xFFF);
		shm |= ((p_mpeg4->rc_b_frame_qp & 0x3F) << 6);
		shm |= (p_mpeg4->rc_p_frame_qp & 0x3F);
		s5p_mfc_ग_लिखो_info_v5(ctx, shm, P_B_FRAME_QP);
	पूर्ण
	/* frame rate */
	अगर (p->rc_frame) अणु
		अगर (p->rc_framerate_denom > 0) अणु
			framerate = p->rc_framerate_num * 1000 /
						p->rc_framerate_denom;
			mfc_ग_लिखो(dev, framerate,
				S5P_FIMV_ENC_RC_FRAME_RATE);
			shm = s5p_mfc_पढ़ो_info_v5(ctx, RC_VOP_TIMING);
			shm &= ~(0xFFFFFFFF);
			shm |= (1UL << 31);
			shm |= ((p->rc_framerate_num & 0x7FFF) << 16);
			shm |= (p->rc_framerate_denom & 0xFFFF);
			s5p_mfc_ग_लिखो_info_v5(ctx, shm, RC_VOP_TIMING);
		पूर्ण
	पूर्ण अन्यथा अणु
		mfc_ग_लिखो(dev, 0, S5P_FIMV_ENC_RC_FRAME_RATE);
	पूर्ण
	/* rate control config. */
	reg = mfc_पढ़ो(dev, S5P_FIMV_ENC_RC_CONFIG);
	/* frame QP */
	reg &= ~(0x3F);
	reg |= p_mpeg4->rc_frame_qp;
	mfc_ग_लिखो(dev, reg, S5P_FIMV_ENC_RC_CONFIG);
	/* max & min value of QP */
	reg = mfc_पढ़ो(dev, S5P_FIMV_ENC_RC_QBOUND);
	/* max QP */
	reg &= ~(0x3F << 8);
	reg |= (p_mpeg4->rc_max_qp << 8);
	/* min QP */
	reg &= ~(0x3F);
	reg |= p_mpeg4->rc_min_qp;
	mfc_ग_लिखो(dev, reg, S5P_FIMV_ENC_RC_QBOUND);
	/* extended encoder ctrl */
	shm = s5p_mfc_पढ़ो_info_v5(ctx, EXT_ENC_CONTROL);
	/* vbv buffer size */
	अगर (p->frame_skip_mode ==
			V4L2_MPEG_MFC51_VIDEO_FRAME_SKIP_MODE_BUF_LIMIT) अणु
		shm &= ~(0xFFFF << 16);
		shm |= (p->vbv_size << 16);
	पूर्ण
	s5p_mfc_ग_लिखो_info_v5(ctx, shm, EXT_ENC_CONTROL);
	वापस 0;
पूर्ण

अटल पूर्णांक s5p_mfc_set_enc_params_h263(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	काष्ठा s5p_mfc_enc_params *p = &ctx->enc_params;
	काष्ठा s5p_mfc_mpeg4_enc_params *p_h263 = &p->codec.mpeg4;
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक shm;

	s5p_mfc_set_enc_params(ctx);
	/* qp */
	अगर (!p->rc_frame) अणु
		shm = s5p_mfc_पढ़ो_info_v5(ctx, P_B_FRAME_QP);
		shm &= ~(0xFFF);
		shm |= (p_h263->rc_p_frame_qp & 0x3F);
		s5p_mfc_ग_लिखो_info_v5(ctx, shm, P_B_FRAME_QP);
	पूर्ण
	/* frame rate */
	अगर (p->rc_frame && p->rc_framerate_denom)
		mfc_ग_लिखो(dev, p->rc_framerate_num * 1000
			/ p->rc_framerate_denom, S5P_FIMV_ENC_RC_FRAME_RATE);
	अन्यथा
		mfc_ग_लिखो(dev, 0, S5P_FIMV_ENC_RC_FRAME_RATE);
	/* rate control config. */
	reg = mfc_पढ़ो(dev, S5P_FIMV_ENC_RC_CONFIG);
	/* frame QP */
	reg &= ~(0x3F);
	reg |= p_h263->rc_frame_qp;
	mfc_ग_लिखो(dev, reg, S5P_FIMV_ENC_RC_CONFIG);
	/* max & min value of QP */
	reg = mfc_पढ़ो(dev, S5P_FIMV_ENC_RC_QBOUND);
	/* max QP */
	reg &= ~(0x3F << 8);
	reg |= (p_h263->rc_max_qp << 8);
	/* min QP */
	reg &= ~(0x3F);
	reg |= p_h263->rc_min_qp;
	mfc_ग_लिखो(dev, reg, S5P_FIMV_ENC_RC_QBOUND);
	/* extended encoder ctrl */
	shm = s5p_mfc_पढ़ो_info_v5(ctx, EXT_ENC_CONTROL);
	/* vbv buffer size */
	अगर (p->frame_skip_mode ==
			V4L2_MPEG_MFC51_VIDEO_FRAME_SKIP_MODE_BUF_LIMIT) अणु
		shm &= ~(0xFFFF << 16);
		shm |= (p->vbv_size << 16);
	पूर्ण
	s5p_mfc_ग_लिखो_info_v5(ctx, shm, EXT_ENC_CONTROL);
	वापस 0;
पूर्ण

/* Initialize decoding */
अटल पूर्णांक s5p_mfc_init_decode_v5(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;

	s5p_mfc_set_shared_buffer(ctx);
	/* Setup loop filter, क्रम decoding this is only valid क्रम MPEG4 */
	अगर (ctx->codec_mode == S5P_MFC_CODEC_MPEG4_DEC)
		mfc_ग_लिखो(dev, ctx->loop_filter_mpeg4, S5P_FIMV_ENC_LF_CTRL);
	अन्यथा
		mfc_ग_लिखो(dev, 0, S5P_FIMV_ENC_LF_CTRL);
	mfc_ग_लिखो(dev, ((ctx->slice_पूर्णांकerface & S5P_FIMV_SLICE_INT_MASK) <<
		S5P_FIMV_SLICE_INT_SHIFT) | (ctx->display_delay_enable <<
		S5P_FIMV_DDELAY_ENA_SHIFT) | ((ctx->display_delay &
		S5P_FIMV_DDELAY_VAL_MASK) << S5P_FIMV_DDELAY_VAL_SHIFT),
		S5P_FIMV_SI_CH0_DPB_CONF_CTRL);
	mfc_ग_लिखो(dev,
	((S5P_FIMV_CH_SEQ_HEADER & S5P_FIMV_CH_MASK) << S5P_FIMV_CH_SHIFT)
				| (ctx->inst_no), S5P_FIMV_SI_CH0_INST_ID);
	वापस 0;
पूर्ण

अटल व्योम s5p_mfc_set_flush(काष्ठा s5p_mfc_ctx *ctx, पूर्णांक flush)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	अचिन्हित पूर्णांक dpb;

	अगर (flush)
		dpb = mfc_पढ़ो(dev, S5P_FIMV_SI_CH0_DPB_CONF_CTRL) | (
			S5P_FIMV_DPB_FLUSH_MASK << S5P_FIMV_DPB_FLUSH_SHIFT);
	अन्यथा
		dpb = mfc_पढ़ो(dev, S5P_FIMV_SI_CH0_DPB_CONF_CTRL) &
			~(S5P_FIMV_DPB_FLUSH_MASK << S5P_FIMV_DPB_FLUSH_SHIFT);
	mfc_ग_लिखो(dev, dpb, S5P_FIMV_SI_CH0_DPB_CONF_CTRL);
पूर्ण

/* Decode a single frame */
अटल पूर्णांक s5p_mfc_decode_one_frame_v5(काष्ठा s5p_mfc_ctx *ctx,
					क्रमागत s5p_mfc_decode_arg last_frame)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;

	mfc_ग_लिखो(dev, ctx->dec_dst_flag, S5P_FIMV_SI_CH0_RELEASE_BUF);
	s5p_mfc_set_shared_buffer(ctx);
	s5p_mfc_set_flush(ctx, ctx->dpb_flush_flag);
	/* Issue dअगरferent commands to instance basing on whether it
	 * is the last frame or not. */
	चयन (last_frame) अणु
	हाल MFC_DEC_FRAME:
		mfc_ग_लिखो(dev, ((S5P_FIMV_CH_FRAME_START & S5P_FIMV_CH_MASK) <<
		S5P_FIMV_CH_SHIFT) | (ctx->inst_no), S5P_FIMV_SI_CH0_INST_ID);
		अवरोध;
	हाल MFC_DEC_LAST_FRAME:
		mfc_ग_लिखो(dev, ((S5P_FIMV_CH_LAST_FRAME & S5P_FIMV_CH_MASK) <<
		S5P_FIMV_CH_SHIFT) | (ctx->inst_no), S5P_FIMV_SI_CH0_INST_ID);
		अवरोध;
	हाल MFC_DEC_RES_CHANGE:
		mfc_ग_लिखो(dev, ((S5P_FIMV_CH_FRAME_START_REALLOC &
		S5P_FIMV_CH_MASK) << S5P_FIMV_CH_SHIFT) | (ctx->inst_no),
		S5P_FIMV_SI_CH0_INST_ID);
		अवरोध;
	पूर्ण
	mfc_debug(2, "Decoding a usual frame\n");
	वापस 0;
पूर्ण

अटल पूर्णांक s5p_mfc_init_encode_v5(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;

	अगर (ctx->codec_mode == S5P_MFC_CODEC_H264_ENC)
		s5p_mfc_set_enc_params_h264(ctx);
	अन्यथा अगर (ctx->codec_mode == S5P_MFC_CODEC_MPEG4_ENC)
		s5p_mfc_set_enc_params_mpeg4(ctx);
	अन्यथा अगर (ctx->codec_mode == S5P_MFC_CODEC_H263_ENC)
		s5p_mfc_set_enc_params_h263(ctx);
	अन्यथा अणु
		mfc_err("Unknown codec for encoding (%x)\n",
			ctx->codec_mode);
		वापस -EINVAL;
	पूर्ण
	s5p_mfc_set_shared_buffer(ctx);
	mfc_ग_लिखो(dev, ((S5P_FIMV_CH_SEQ_HEADER << 16) & 0x70000) |
		(ctx->inst_no), S5P_FIMV_SI_CH0_INST_ID);
	वापस 0;
पूर्ण

/* Encode a single frame */
अटल पूर्णांक s5p_mfc_encode_one_frame_v5(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	पूर्णांक cmd;
	/* memory काष्ठाure cur. frame */
	अगर (ctx->src_fmt->fourcc == V4L2_PIX_FMT_NV12M)
		mfc_ग_लिखो(dev, 0, S5P_FIMV_ENC_MAP_FOR_CUR);
	अन्यथा अगर (ctx->src_fmt->fourcc == V4L2_PIX_FMT_NV12MT)
		mfc_ग_लिखो(dev, 3, S5P_FIMV_ENC_MAP_FOR_CUR);
	s5p_mfc_set_shared_buffer(ctx);

	अगर (ctx->state == MFCINST_FINISHING)
		cmd = S5P_FIMV_CH_LAST_FRAME;
	अन्यथा
		cmd = S5P_FIMV_CH_FRAME_START;
	mfc_ग_लिखो(dev, ((cmd & S5P_FIMV_CH_MASK) << S5P_FIMV_CH_SHIFT)
				| (ctx->inst_no), S5P_FIMV_SI_CH0_INST_ID);

	वापस 0;
पूर्ण

अटल व्योम s5p_mfc_run_res_change(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;

	s5p_mfc_set_dec_stream_buffer_v5(ctx, 0, 0, 0);
	dev->curr_ctx = ctx->num;
	s5p_mfc_decode_one_frame_v5(ctx, MFC_DEC_RES_CHANGE);
पूर्ण

अटल पूर्णांक s5p_mfc_run_dec_frame(काष्ठा s5p_mfc_ctx *ctx, पूर्णांक last_frame)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	काष्ठा s5p_mfc_buf *temp_vb;

	अगर (ctx->state == MFCINST_FINISHING) अणु
		last_frame = MFC_DEC_LAST_FRAME;
		s5p_mfc_set_dec_stream_buffer_v5(ctx, 0, 0, 0);
		dev->curr_ctx = ctx->num;
		s5p_mfc_decode_one_frame_v5(ctx, last_frame);
		वापस 0;
	पूर्ण

	/* Frames are being decoded */
	अगर (list_empty(&ctx->src_queue)) अणु
		mfc_debug(2, "No src buffers\n");
		वापस -EAGAIN;
	पूर्ण
	/* Get the next source buffer */
	temp_vb = list_entry(ctx->src_queue.next, काष्ठा s5p_mfc_buf, list);
	temp_vb->flags |= MFC_BUF_FLAG_USED;
	s5p_mfc_set_dec_stream_buffer_v5(ctx,
		vb2_dma_contig_plane_dma_addr(&temp_vb->b->vb2_buf, 0),
		ctx->consumed_stream, temp_vb->b->vb2_buf.planes[0].bytesused);
	dev->curr_ctx = ctx->num;
	अगर (temp_vb->b->vb2_buf.planes[0].bytesused == 0) अणु
		last_frame = MFC_DEC_LAST_FRAME;
		mfc_debug(2, "Setting ctx->state to FINISHING\n");
		ctx->state = MFCINST_FINISHING;
	पूर्ण
	s5p_mfc_decode_one_frame_v5(ctx, last_frame);
	वापस 0;
पूर्ण

अटल पूर्णांक s5p_mfc_run_enc_frame(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	काष्ठा s5p_mfc_buf *dst_mb;
	काष्ठा s5p_mfc_buf *src_mb;
	अचिन्हित दीर्घ src_y_addr, src_c_addr, dst_addr;
	अचिन्हित पूर्णांक dst_size;

	अगर (list_empty(&ctx->src_queue) && ctx->state != MFCINST_FINISHING) अणु
		mfc_debug(2, "no src buffers\n");
		वापस -EAGAIN;
	पूर्ण
	अगर (list_empty(&ctx->dst_queue)) अणु
		mfc_debug(2, "no dst buffers\n");
		वापस -EAGAIN;
	पूर्ण
	अगर (list_empty(&ctx->src_queue)) अणु
		/* send null frame */
		s5p_mfc_set_enc_frame_buffer_v5(ctx, dev->dma_base[BANK_R_CTX],
						dev->dma_base[BANK_R_CTX]);
		src_mb = शून्य;
	पूर्ण अन्यथा अणु
		src_mb = list_entry(ctx->src_queue.next, काष्ठा s5p_mfc_buf,
									list);
		src_mb->flags |= MFC_BUF_FLAG_USED;
		अगर (src_mb->b->vb2_buf.planes[0].bytesused == 0) अणु
			/* send null frame */
			s5p_mfc_set_enc_frame_buffer_v5(ctx,
						dev->dma_base[BANK_R_CTX],
						dev->dma_base[BANK_R_CTX]);
			ctx->state = MFCINST_FINISHING;
		पूर्ण अन्यथा अणु
			src_y_addr = vb2_dma_contig_plane_dma_addr(
					&src_mb->b->vb2_buf, 0);
			src_c_addr = vb2_dma_contig_plane_dma_addr(
					&src_mb->b->vb2_buf, 1);
			s5p_mfc_set_enc_frame_buffer_v5(ctx, src_y_addr,
								src_c_addr);
			अगर (src_mb->flags & MFC_BUF_FLAG_EOS)
				ctx->state = MFCINST_FINISHING;
		पूर्ण
	पूर्ण
	dst_mb = list_entry(ctx->dst_queue.next, काष्ठा s5p_mfc_buf, list);
	dst_mb->flags |= MFC_BUF_FLAG_USED;
	dst_addr = vb2_dma_contig_plane_dma_addr(&dst_mb->b->vb2_buf, 0);
	dst_size = vb2_plane_size(&dst_mb->b->vb2_buf, 0);
	s5p_mfc_set_enc_stream_buffer_v5(ctx, dst_addr, dst_size);
	dev->curr_ctx = ctx->num;
	mfc_debug(2, "encoding buffer with index=%d state=%d\n",
		  src_mb ? src_mb->b->vb2_buf.index : -1, ctx->state);
	s5p_mfc_encode_one_frame_v5(ctx);
	वापस 0;
पूर्ण

अटल व्योम s5p_mfc_run_init_dec(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	काष्ठा s5p_mfc_buf *temp_vb;

	/* Initializing decoding - parsing header */
	mfc_debug(2, "Preparing to init decoding\n");
	temp_vb = list_entry(ctx->src_queue.next, काष्ठा s5p_mfc_buf, list);
	s5p_mfc_set_dec_desc_buffer(ctx);
	mfc_debug(2, "Header size: %d\n",
			temp_vb->b->vb2_buf.planes[0].bytesused);
	s5p_mfc_set_dec_stream_buffer_v5(ctx,
			vb2_dma_contig_plane_dma_addr(&temp_vb->b->vb2_buf, 0),
			0, temp_vb->b->vb2_buf.planes[0].bytesused);
	dev->curr_ctx = ctx->num;
	s5p_mfc_init_decode_v5(ctx);
पूर्ण

अटल व्योम s5p_mfc_run_init_enc(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	काष्ठा s5p_mfc_buf *dst_mb;
	अचिन्हित दीर्घ dst_addr;
	अचिन्हित पूर्णांक dst_size;

	s5p_mfc_set_enc_ref_buffer_v5(ctx);
	dst_mb = list_entry(ctx->dst_queue.next, काष्ठा s5p_mfc_buf, list);
	dst_addr = vb2_dma_contig_plane_dma_addr(&dst_mb->b->vb2_buf, 0);
	dst_size = vb2_plane_size(&dst_mb->b->vb2_buf, 0);
	s5p_mfc_set_enc_stream_buffer_v5(ctx, dst_addr, dst_size);
	dev->curr_ctx = ctx->num;
	s5p_mfc_init_encode_v5(ctx);
पूर्ण

अटल पूर्णांक s5p_mfc_run_init_dec_buffers(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	काष्ठा s5p_mfc_buf *temp_vb;
	पूर्णांक ret;

	/*
	 * Header was parsed now starting processing
	 * First set the output frame buffers
	 */
	अगर (ctx->capture_state != QUEUE_BUFS_MMAPED) अणु
		mfc_err("It seems that not all destination buffers were mmapped\nMFC requires that all destination are mmapped before starting processing\n");
		वापस -EAGAIN;
	पूर्ण
	अगर (list_empty(&ctx->src_queue)) अणु
		mfc_err("Header has been deallocated in the middle of initialization\n");
		वापस -EIO;
	पूर्ण
	temp_vb = list_entry(ctx->src_queue.next, काष्ठा s5p_mfc_buf, list);
	mfc_debug(2, "Header size: %d\n",
			temp_vb->b->vb2_buf.planes[0].bytesused);
	s5p_mfc_set_dec_stream_buffer_v5(ctx,
			vb2_dma_contig_plane_dma_addr(&temp_vb->b->vb2_buf, 0),
			0, temp_vb->b->vb2_buf.planes[0].bytesused);
	dev->curr_ctx = ctx->num;
	ret = s5p_mfc_set_dec_frame_buffer_v5(ctx);
	अगर (ret) अणु
		mfc_err("Failed to alloc frame mem\n");
		ctx->state = MFCINST_ERROR;
	पूर्ण
	वापस ret;
पूर्ण

/* Try running an operation on hardware */
अटल व्योम s5p_mfc_try_run_v5(काष्ठा s5p_mfc_dev *dev)
अणु
	काष्ठा s5p_mfc_ctx *ctx;
	पूर्णांक new_ctx;
	अचिन्हित पूर्णांक ret = 0;

	अगर (test_bit(0, &dev->enter_suspend)) अणु
		mfc_debug(1, "Entering suspend so do not schedule any jobs\n");
		वापस;
	पूर्ण
	/* Check whether hardware is not running */
	अगर (test_and_set_bit(0, &dev->hw_lock) != 0) अणु
		/* This is perfectly ok, the scheduled ctx should रुको */
		mfc_debug(1, "Couldn't lock HW\n");
		वापस;
	पूर्ण
	/* Choose the context to run */
	new_ctx = s5p_mfc_get_new_ctx(dev);
	अगर (new_ctx < 0) अणु
		/* No contexts to run */
		अगर (test_and_clear_bit(0, &dev->hw_lock) == 0) अणु
			mfc_err("Failed to unlock hardware\n");
			वापस;
		पूर्ण
		mfc_debug(1, "No ctx is scheduled to be run\n");
		वापस;
	पूर्ण
	ctx = dev->ctx[new_ctx];
	/* Got context to run in ctx */
	/*
	 * Last frame has alपढ़ोy been sent to MFC.
	 * Now obtaining frames from MFC buffer
	 */
	s5p_mfc_घड़ी_on();
	s5p_mfc_clean_ctx_पूर्णांक_flags(ctx);

	अगर (ctx->type == MFCINST_DECODER) अणु
		s5p_mfc_set_dec_desc_buffer(ctx);
		चयन (ctx->state) अणु
		हाल MFCINST_FINISHING:
			s5p_mfc_run_dec_frame(ctx, MFC_DEC_LAST_FRAME);
			अवरोध;
		हाल MFCINST_RUNNING:
			ret = s5p_mfc_run_dec_frame(ctx, MFC_DEC_FRAME);
			अवरोध;
		हाल MFCINST_INIT:
			ret = s5p_mfc_hw_call(dev->mfc_cmds, खोलो_inst_cmd,
					ctx);
			अवरोध;
		हाल MFCINST_RETURN_INST:
			ret = s5p_mfc_hw_call(dev->mfc_cmds, बंद_inst_cmd,
					ctx);
			अवरोध;
		हाल MFCINST_GOT_INST:
			s5p_mfc_run_init_dec(ctx);
			अवरोध;
		हाल MFCINST_HEAD_PARSED:
			ret = s5p_mfc_run_init_dec_buffers(ctx);
			mfc_debug(1, "head parsed\n");
			अवरोध;
		हाल MFCINST_RES_CHANGE_INIT:
			s5p_mfc_run_res_change(ctx);
			अवरोध;
		हाल MFCINST_RES_CHANGE_FLUSH:
			s5p_mfc_run_dec_frame(ctx, MFC_DEC_FRAME);
			अवरोध;
		हाल MFCINST_RES_CHANGE_END:
			mfc_debug(2, "Finished remaining frames after resolution change\n");
			ctx->capture_state = QUEUE_FREE;
			mfc_debug(2, "Will re-init the codec\n");
			s5p_mfc_run_init_dec(ctx);
			अवरोध;
		शेष:
			ret = -EAGAIN;
		पूर्ण
	पूर्ण अन्यथा अगर (ctx->type == MFCINST_ENCODER) अणु
		चयन (ctx->state) अणु
		हाल MFCINST_FINISHING:
		हाल MFCINST_RUNNING:
			ret = s5p_mfc_run_enc_frame(ctx);
			अवरोध;
		हाल MFCINST_INIT:
			ret = s5p_mfc_hw_call(dev->mfc_cmds, खोलो_inst_cmd,
					ctx);
			अवरोध;
		हाल MFCINST_RETURN_INST:
			ret = s5p_mfc_hw_call(dev->mfc_cmds, बंद_inst_cmd,
					ctx);
			अवरोध;
		हाल MFCINST_GOT_INST:
			s5p_mfc_run_init_enc(ctx);
			अवरोध;
		शेष:
			ret = -EAGAIN;
		पूर्ण
	पूर्ण अन्यथा अणु
		mfc_err("Invalid context type: %d\n", ctx->type);
		ret = -EAGAIN;
	पूर्ण

	अगर (ret) अणु
		/* Free hardware lock */
		अगर (test_and_clear_bit(0, &dev->hw_lock) == 0)
			mfc_err("Failed to unlock hardware\n");

		/* This is in deed imporant, as no operation has been
		 * scheduled, reduce the घड़ी count as no one will
		 * ever करो this, because no पूर्णांकerrupt related to this try_run
		 * will ever come from hardware. */
		s5p_mfc_घड़ी_off();
	पूर्ण
पूर्ण

अटल व्योम s5p_mfc_clear_पूर्णांक_flags_v5(काष्ठा s5p_mfc_dev *dev)
अणु
	mfc_ग_लिखो(dev, 0, S5P_FIMV_RISC_HOST_INT);
	mfc_ग_लिखो(dev, 0, S5P_FIMV_RISC2HOST_CMD);
	mfc_ग_लिखो(dev, 0xffff, S5P_FIMV_SI_RTN_CHID);
पूर्ण

अटल पूर्णांक s5p_mfc_get_dspl_y_adr_v5(काष्ठा s5p_mfc_dev *dev)
अणु
	वापस mfc_पढ़ो(dev, S5P_FIMV_SI_DISPLAY_Y_ADR) << MFC_OFFSET_SHIFT;
पूर्ण

अटल पूर्णांक s5p_mfc_get_dec_y_adr_v5(काष्ठा s5p_mfc_dev *dev)
अणु
	वापस mfc_पढ़ो(dev, S5P_FIMV_SI_DECODE_Y_ADR) << MFC_OFFSET_SHIFT;
पूर्ण

अटल पूर्णांक s5p_mfc_get_dspl_status_v5(काष्ठा s5p_mfc_dev *dev)
अणु
	वापस mfc_पढ़ो(dev, S5P_FIMV_SI_DISPLAY_STATUS);
पूर्ण

अटल पूर्णांक s5p_mfc_get_dec_status_v5(काष्ठा s5p_mfc_dev *dev)
अणु
	वापस mfc_पढ़ो(dev, S5P_FIMV_SI_DECODE_STATUS);
पूर्ण

अटल पूर्णांक s5p_mfc_get_dec_frame_type_v5(काष्ठा s5p_mfc_dev *dev)
अणु
	वापस mfc_पढ़ो(dev, S5P_FIMV_DECODE_FRAME_TYPE) &
		S5P_FIMV_DECODE_FRAME_MASK;
पूर्ण

अटल पूर्णांक s5p_mfc_get_disp_frame_type_v5(काष्ठा s5p_mfc_ctx *ctx)
अणु
	वापस (s5p_mfc_पढ़ो_info_v5(ctx, DISP_PIC_FRAME_TYPE) >>
			S5P_FIMV_SHARED_DISP_FRAME_TYPE_SHIFT) &
			S5P_FIMV_DECODE_FRAME_MASK;
पूर्ण

अटल पूर्णांक s5p_mfc_get_consumed_stream_v5(काष्ठा s5p_mfc_dev *dev)
अणु
	वापस mfc_पढ़ो(dev, S5P_FIMV_SI_CONSUMED_BYTES);
पूर्ण

अटल पूर्णांक s5p_mfc_get_पूर्णांक_reason_v5(काष्ठा s5p_mfc_dev *dev)
अणु
	पूर्णांक reason;
	reason = mfc_पढ़ो(dev, S5P_FIMV_RISC2HOST_CMD) &
		S5P_FIMV_RISC2HOST_CMD_MASK;
	चयन (reason) अणु
	हाल S5P_FIMV_R2H_CMD_OPEN_INSTANCE_RET:
		reason = S5P_MFC_R2H_CMD_OPEN_INSTANCE_RET;
		अवरोध;
	हाल S5P_FIMV_R2H_CMD_CLOSE_INSTANCE_RET:
		reason = S5P_MFC_R2H_CMD_CLOSE_INSTANCE_RET;
		अवरोध;
	हाल S5P_FIMV_R2H_CMD_SEQ_DONE_RET:
		reason = S5P_MFC_R2H_CMD_SEQ_DONE_RET;
		अवरोध;
	हाल S5P_FIMV_R2H_CMD_FRAME_DONE_RET:
		reason = S5P_MFC_R2H_CMD_FRAME_DONE_RET;
		अवरोध;
	हाल S5P_FIMV_R2H_CMD_SLICE_DONE_RET:
		reason = S5P_MFC_R2H_CMD_SLICE_DONE_RET;
		अवरोध;
	हाल S5P_FIMV_R2H_CMD_SYS_INIT_RET:
		reason = S5P_MFC_R2H_CMD_SYS_INIT_RET;
		अवरोध;
	हाल S5P_FIMV_R2H_CMD_FW_STATUS_RET:
		reason = S5P_MFC_R2H_CMD_FW_STATUS_RET;
		अवरोध;
	हाल S5P_FIMV_R2H_CMD_SLEEP_RET:
		reason = S5P_MFC_R2H_CMD_SLEEP_RET;
		अवरोध;
	हाल S5P_FIMV_R2H_CMD_WAKEUP_RET:
		reason = S5P_MFC_R2H_CMD_WAKEUP_RET;
		अवरोध;
	हाल S5P_FIMV_R2H_CMD_INIT_BUFFERS_RET:
		reason = S5P_MFC_R2H_CMD_INIT_BUFFERS_RET;
		अवरोध;
	हाल S5P_FIMV_R2H_CMD_ENC_COMPLETE_RET:
		reason = S5P_MFC_R2H_CMD_COMPLETE_SEQ_RET;
		अवरोध;
	हाल S5P_FIMV_R2H_CMD_ERR_RET:
		reason = S5P_MFC_R2H_CMD_ERR_RET;
		अवरोध;
	शेष:
		reason = S5P_MFC_R2H_CMD_EMPTY;
	पूर्ण
	वापस reason;
पूर्ण

अटल पूर्णांक s5p_mfc_get_पूर्णांक_err_v5(काष्ठा s5p_mfc_dev *dev)
अणु
	वापस mfc_पढ़ो(dev, S5P_FIMV_RISC2HOST_ARG2);
पूर्ण

अटल पूर्णांक s5p_mfc_err_dec_v5(अचिन्हित पूर्णांक err)
अणु
	वापस (err & S5P_FIMV_ERR_DEC_MASK) >> S5P_FIMV_ERR_DEC_SHIFT;
पूर्ण

अटल पूर्णांक s5p_mfc_get_img_width_v5(काष्ठा s5p_mfc_dev *dev)
अणु
	वापस mfc_पढ़ो(dev, S5P_FIMV_SI_HRESOL);
पूर्ण

अटल पूर्णांक s5p_mfc_get_img_height_v5(काष्ठा s5p_mfc_dev *dev)
अणु
	वापस mfc_पढ़ो(dev, S5P_FIMV_SI_VRESOL);
पूर्ण

अटल पूर्णांक s5p_mfc_get_dpb_count_v5(काष्ठा s5p_mfc_dev *dev)
अणु
	वापस mfc_पढ़ो(dev, S5P_FIMV_SI_BUF_NUMBER);
पूर्ण

अटल पूर्णांक s5p_mfc_get_mv_count_v5(काष्ठा s5p_mfc_dev *dev)
अणु
	/* NOP */
	वापस -1;
पूर्ण

अटल पूर्णांक s5p_mfc_get_inst_no_v5(काष्ठा s5p_mfc_dev *dev)
अणु
	वापस mfc_पढ़ो(dev, S5P_FIMV_RISC2HOST_ARG1);
पूर्ण

अटल पूर्णांक s5p_mfc_get_enc_strm_size_v5(काष्ठा s5p_mfc_dev *dev)
अणु
	वापस mfc_पढ़ो(dev, S5P_FIMV_ENC_SI_STRM_SIZE);
पूर्ण

अटल पूर्णांक s5p_mfc_get_enc_slice_type_v5(काष्ठा s5p_mfc_dev *dev)
अणु
	वापस mfc_पढ़ो(dev, S5P_FIMV_ENC_SI_SLICE_TYPE);
पूर्ण

अटल पूर्णांक s5p_mfc_get_enc_dpb_count_v5(काष्ठा s5p_mfc_dev *dev)
अणु
	वापस -1;
पूर्ण

अटल अचिन्हित पूर्णांक s5p_mfc_get_pic_type_top_v5(काष्ठा s5p_mfc_ctx *ctx)
अणु
	वापस s5p_mfc_पढ़ो_info_v5(ctx, PIC_TIME_TOP);
पूर्ण

अटल अचिन्हित पूर्णांक s5p_mfc_get_pic_type_bot_v5(काष्ठा s5p_mfc_ctx *ctx)
अणु
	वापस s5p_mfc_पढ़ो_info_v5(ctx, PIC_TIME_BOT);
पूर्ण

अटल अचिन्हित पूर्णांक s5p_mfc_get_crop_info_h_v5(काष्ठा s5p_mfc_ctx *ctx)
अणु
	वापस s5p_mfc_पढ़ो_info_v5(ctx, CROP_INFO_H);
पूर्ण

अटल अचिन्हित पूर्णांक s5p_mfc_get_crop_info_v_v5(काष्ठा s5p_mfc_ctx *ctx)
अणु
	वापस s5p_mfc_पढ़ो_info_v5(ctx, CROP_INFO_V);
पूर्ण

/* Initialize opr function poपूर्णांकers क्रम MFC v5 */
अटल काष्ठा s5p_mfc_hw_ops s5p_mfc_ops_v5 = अणु
	.alloc_dec_temp_buffers = s5p_mfc_alloc_dec_temp_buffers_v5,
	.release_dec_desc_buffer = s5p_mfc_release_dec_desc_buffer_v5,
	.alloc_codec_buffers = s5p_mfc_alloc_codec_buffers_v5,
	.release_codec_buffers = s5p_mfc_release_codec_buffers_v5,
	.alloc_instance_buffer = s5p_mfc_alloc_instance_buffer_v5,
	.release_instance_buffer = s5p_mfc_release_instance_buffer_v5,
	.alloc_dev_context_buffer = s5p_mfc_alloc_dev_context_buffer_v5,
	.release_dev_context_buffer = s5p_mfc_release_dev_context_buffer_v5,
	.dec_calc_dpb_size = s5p_mfc_dec_calc_dpb_size_v5,
	.enc_calc_src_size = s5p_mfc_enc_calc_src_size_v5,
	.set_enc_stream_buffer = s5p_mfc_set_enc_stream_buffer_v5,
	.set_enc_frame_buffer = s5p_mfc_set_enc_frame_buffer_v5,
	.get_enc_frame_buffer = s5p_mfc_get_enc_frame_buffer_v5,
	.try_run = s5p_mfc_try_run_v5,
	.clear_पूर्णांक_flags = s5p_mfc_clear_पूर्णांक_flags_v5,
	.get_dspl_y_adr = s5p_mfc_get_dspl_y_adr_v5,
	.get_dec_y_adr = s5p_mfc_get_dec_y_adr_v5,
	.get_dspl_status = s5p_mfc_get_dspl_status_v5,
	.get_dec_status = s5p_mfc_get_dec_status_v5,
	.get_dec_frame_type = s5p_mfc_get_dec_frame_type_v5,
	.get_disp_frame_type = s5p_mfc_get_disp_frame_type_v5,
	.get_consumed_stream = s5p_mfc_get_consumed_stream_v5,
	.get_पूर्णांक_reason = s5p_mfc_get_पूर्णांक_reason_v5,
	.get_पूर्णांक_err = s5p_mfc_get_पूर्णांक_err_v5,
	.err_dec = s5p_mfc_err_dec_v5,
	.get_img_width = s5p_mfc_get_img_width_v5,
	.get_img_height = s5p_mfc_get_img_height_v5,
	.get_dpb_count = s5p_mfc_get_dpb_count_v5,
	.get_mv_count = s5p_mfc_get_mv_count_v5,
	.get_inst_no = s5p_mfc_get_inst_no_v5,
	.get_enc_strm_size = s5p_mfc_get_enc_strm_size_v5,
	.get_enc_slice_type = s5p_mfc_get_enc_slice_type_v5,
	.get_enc_dpb_count = s5p_mfc_get_enc_dpb_count_v5,
	.get_pic_type_top = s5p_mfc_get_pic_type_top_v5,
	.get_pic_type_bot = s5p_mfc_get_pic_type_bot_v5,
	.get_crop_info_h = s5p_mfc_get_crop_info_h_v5,
	.get_crop_info_v = s5p_mfc_get_crop_info_v_v5,
पूर्ण;

काष्ठा s5p_mfc_hw_ops *s5p_mfc_init_hw_ops_v5(व्योम)
अणु
	वापस &s5p_mfc_ops_v5;
पूर्ण
