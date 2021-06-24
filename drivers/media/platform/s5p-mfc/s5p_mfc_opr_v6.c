<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/media/platक्रमm/s5p-mfc/s5p_mfc_opr_v6.c
 *
 * Samsung MFC (Multi Function Codec - FIMV) driver
 * This file contains hw related functions.
 *
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 */

#अघोषित DEBUG

#समावेश <linux/delay.h>
#समावेश <linux/mm.h>
#समावेश <linux/पन.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/firmware.h>
#समावेश <linux/err.h>
#समावेश <linux/sched.h>
#समावेश <linux/dma-mapping.h>

#समावेश <यंत्र/cacheflush.h>

#समावेश "s5p_mfc_common.h"
#समावेश "s5p_mfc_cmd.h"
#समावेश "s5p_mfc_intr.h"
#समावेश "s5p_mfc_pm.h"
#समावेश "s5p_mfc_debug.h"
#समावेश "s5p_mfc_opr.h"
#समावेश "s5p_mfc_opr_v6.h"

/* #घोषणा S5P_MFC_DEBUG_REGWRITE  */
#अगर_घोषित S5P_MFC_DEBUG_REGWRITE
#अघोषित ग_लिखोl
#घोषणा ग_लिखोl(v, r)							\
	करो अणु								\
		pr_err("MFCWRITE(%p): %08x\n", r, (अचिन्हित पूर्णांक)v);	\
	__raw_ग_लिखोl(v, r);						\
	पूर्ण जबतक (0)
#पूर्ण_अगर /* S5P_MFC_DEBUG_REGWRITE */

#घोषणा IS_MFCV6_V2(dev) (!IS_MFCV7_PLUS(dev) && dev->fw_ver == MFC_FW_V2)

/* Allocate temporary buffers क्रम decoding */
अटल पूर्णांक s5p_mfc_alloc_dec_temp_buffers_v6(काष्ठा s5p_mfc_ctx *ctx)
अणु
	/* NOP */

	वापस 0;
पूर्ण

/* Release temporary buffers क्रम decoding */
अटल व्योम s5p_mfc_release_dec_desc_buffer_v6(काष्ठा s5p_mfc_ctx *ctx)
अणु
	/* NOP */
पूर्ण

/* Allocate codec buffers */
अटल पूर्णांक s5p_mfc_alloc_codec_buffers_v6(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	अचिन्हित पूर्णांक mb_width, mb_height;
	अचिन्हित पूर्णांक lcu_width = 0, lcu_height = 0;
	पूर्णांक ret;

	mb_width = MB_WIDTH(ctx->img_width);
	mb_height = MB_HEIGHT(ctx->img_height);

	अगर (ctx->type == MFCINST_DECODER) अणु
		mfc_debug(2, "Luma size:%d Chroma size:%d MV size:%d\n",
			  ctx->luma_size, ctx->chroma_size, ctx->mv_size);
		mfc_debug(2, "Totals bufs: %d\n", ctx->total_dpb_count);
	पूर्ण अन्यथा अगर (ctx->type == MFCINST_ENCODER) अणु
		अगर (IS_MFCV10(dev)) अणु
			ctx->पंचांगv_buffer_size = 0;
		पूर्ण अन्यथा अगर (IS_MFCV8_PLUS(dev))
			ctx->पंचांगv_buffer_size = S5P_FIMV_NUM_TMV_BUFFERS_V6 *
			ALIGN(S5P_FIMV_TMV_BUFFER_SIZE_V8(mb_width, mb_height),
			S5P_FIMV_TMV_BUFFER_ALIGN_V6);
		अन्यथा
			ctx->पंचांगv_buffer_size = S5P_FIMV_NUM_TMV_BUFFERS_V6 *
			ALIGN(S5P_FIMV_TMV_BUFFER_SIZE_V6(mb_width, mb_height),
			S5P_FIMV_TMV_BUFFER_ALIGN_V6);
		अगर (IS_MFCV10(dev)) अणु
			lcu_width = S5P_MFC_LCU_WIDTH(ctx->img_width);
			lcu_height = S5P_MFC_LCU_HEIGHT(ctx->img_height);
			अगर (ctx->codec_mode != S5P_FIMV_CODEC_HEVC_ENC) अणु
				ctx->luma_dpb_size =
					ALIGN((mb_width * 16), 64)
					* ALIGN((mb_height * 16), 32)
						+ 64;
				ctx->chroma_dpb_size =
					ALIGN((mb_width * 16), 64)
							* (mb_height * 8)
							+ 64;
			पूर्ण अन्यथा अणु
				ctx->luma_dpb_size =
					ALIGN((lcu_width * 32), 64)
					* ALIGN((lcu_height * 32), 32)
						+ 64;
				ctx->chroma_dpb_size =
					ALIGN((lcu_width * 32), 64)
							* (lcu_height * 16)
							+ 64;
			पूर्ण
		पूर्ण अन्यथा अणु
			ctx->luma_dpb_size = ALIGN((mb_width * mb_height) *
					S5P_FIMV_LUMA_MB_TO_PIXEL_V6,
					S5P_FIMV_LUMA_DPB_BUFFER_ALIGN_V6);
			ctx->chroma_dpb_size = ALIGN((mb_width * mb_height) *
					S5P_FIMV_CHROMA_MB_TO_PIXEL_V6,
					S5P_FIMV_CHROMA_DPB_BUFFER_ALIGN_V6);
		पूर्ण
		अगर (IS_MFCV8_PLUS(dev))
			ctx->me_buffer_size = ALIGN(S5P_FIMV_ME_BUFFER_SIZE_V8(
						ctx->img_width, ctx->img_height,
						mb_width, mb_height),
						S5P_FIMV_ME_BUFFER_ALIGN_V6);
		अन्यथा
			ctx->me_buffer_size = ALIGN(S5P_FIMV_ME_BUFFER_SIZE_V6(
						ctx->img_width, ctx->img_height,
						mb_width, mb_height),
						S5P_FIMV_ME_BUFFER_ALIGN_V6);

		mfc_debug(2, "recon luma size: %zu chroma size: %zu\n",
			  ctx->luma_dpb_size, ctx->chroma_dpb_size);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	/* Codecs have dअगरferent memory requirements */
	चयन (ctx->codec_mode) अणु
	हाल S5P_MFC_CODEC_H264_DEC:
	हाल S5P_MFC_CODEC_H264_MVC_DEC:
		अगर (IS_MFCV10(dev))
			mfc_debug(2, "Use min scratch buffer size\n");
		अन्यथा अगर (IS_MFCV8_PLUS(dev))
			ctx->scratch_buf_size =
				S5P_FIMV_SCRATCH_BUF_SIZE_H264_DEC_V8(
					mb_width,
					mb_height);
		अन्यथा
			ctx->scratch_buf_size =
				S5P_FIMV_SCRATCH_BUF_SIZE_H264_DEC_V6(
					mb_width,
					mb_height);
		ctx->scratch_buf_size = ALIGN(ctx->scratch_buf_size,
				S5P_FIMV_SCRATCH_BUFFER_ALIGN_V6);
		ctx->bank1.size =
			ctx->scratch_buf_size +
			(ctx->mv_count * ctx->mv_size);
		अवरोध;
	हाल S5P_MFC_CODEC_MPEG4_DEC:
		अगर (IS_MFCV10(dev))
			mfc_debug(2, "Use min scratch buffer size\n");
		अन्यथा अगर (IS_MFCV7_PLUS(dev)) अणु
			ctx->scratch_buf_size =
				S5P_FIMV_SCRATCH_BUF_SIZE_MPEG4_DEC_V7(
						mb_width,
						mb_height);
		पूर्ण अन्यथा अणु
			ctx->scratch_buf_size =
				S5P_FIMV_SCRATCH_BUF_SIZE_MPEG4_DEC_V6(
						mb_width,
						mb_height);
		पूर्ण

		ctx->scratch_buf_size = ALIGN(ctx->scratch_buf_size,
				S5P_FIMV_SCRATCH_BUFFER_ALIGN_V6);
		ctx->bank1.size = ctx->scratch_buf_size;
		अवरोध;
	हाल S5P_MFC_CODEC_VC1RCV_DEC:
	हाल S5P_MFC_CODEC_VC1_DEC:
		अगर (IS_MFCV10(dev))
			mfc_debug(2, "Use min scratch buffer size\n");
		अन्यथा
			ctx->scratch_buf_size =
				S5P_FIMV_SCRATCH_BUF_SIZE_VC1_DEC_V6(
						mb_width,
						mb_height);

		ctx->scratch_buf_size = ALIGN(ctx->scratch_buf_size,
				S5P_FIMV_SCRATCH_BUFFER_ALIGN_V6);
		ctx->bank1.size = ctx->scratch_buf_size;
		अवरोध;
	हाल S5P_MFC_CODEC_MPEG2_DEC:
		ctx->bank1.size = 0;
		ctx->bank2.size = 0;
		अवरोध;
	हाल S5P_MFC_CODEC_H263_DEC:
		अगर (IS_MFCV10(dev))
			mfc_debug(2, "Use min scratch buffer size\n");
		अन्यथा
			ctx->scratch_buf_size =
				S5P_FIMV_SCRATCH_BUF_SIZE_H263_DEC_V6(
						mb_width,
						mb_height);
		ctx->scratch_buf_size = ALIGN(ctx->scratch_buf_size,
				S5P_FIMV_SCRATCH_BUFFER_ALIGN_V6);
		ctx->bank1.size = ctx->scratch_buf_size;
		अवरोध;
	हाल S5P_MFC_CODEC_VP8_DEC:
		अगर (IS_MFCV10(dev))
			mfc_debug(2, "Use min scratch buffer size\n");
		अन्यथा अगर (IS_MFCV8_PLUS(dev))
			ctx->scratch_buf_size =
				S5P_FIMV_SCRATCH_BUF_SIZE_VP8_DEC_V8(
						mb_width,
						mb_height);
		अन्यथा
			ctx->scratch_buf_size =
				S5P_FIMV_SCRATCH_BUF_SIZE_VP8_DEC_V6(
						mb_width,
						mb_height);
		ctx->scratch_buf_size = ALIGN(ctx->scratch_buf_size,
				S5P_FIMV_SCRATCH_BUFFER_ALIGN_V6);
		ctx->bank1.size = ctx->scratch_buf_size;
		अवरोध;
	हाल S5P_MFC_CODEC_HEVC_DEC:
		mfc_debug(2, "Use min scratch buffer size\n");
		ctx->bank1.size =
			ctx->scratch_buf_size +
			(ctx->mv_count * ctx->mv_size);
		अवरोध;
	हाल S5P_MFC_CODEC_VP9_DEC:
		mfc_debug(2, "Use min scratch buffer size\n");
		ctx->bank1.size =
			ctx->scratch_buf_size +
			DEC_VP9_STATIC_BUFFER_SIZE;
		अवरोध;
	हाल S5P_MFC_CODEC_H264_ENC:
		अगर (IS_MFCV10(dev)) अणु
			mfc_debug(2, "Use min scratch buffer size\n");
			ctx->me_buffer_size =
			ALIGN(ENC_V100_H264_ME_SIZE(mb_width, mb_height), 16);
		पूर्ण अन्यथा अगर (IS_MFCV8_PLUS(dev))
			ctx->scratch_buf_size =
				S5P_FIMV_SCRATCH_BUF_SIZE_H264_ENC_V8(
					mb_width,
					mb_height);
		अन्यथा
			ctx->scratch_buf_size =
				S5P_FIMV_SCRATCH_BUF_SIZE_H264_ENC_V6(
						mb_width,
						mb_height);
		ctx->scratch_buf_size = ALIGN(ctx->scratch_buf_size,
				S5P_FIMV_SCRATCH_BUFFER_ALIGN_V6);
		ctx->bank1.size =
			ctx->scratch_buf_size + ctx->पंचांगv_buffer_size +
			(ctx->pb_count * (ctx->luma_dpb_size +
			ctx->chroma_dpb_size + ctx->me_buffer_size));
		ctx->bank2.size = 0;
		अवरोध;
	हाल S5P_MFC_CODEC_MPEG4_ENC:
	हाल S5P_MFC_CODEC_H263_ENC:
		अगर (IS_MFCV10(dev)) अणु
			mfc_debug(2, "Use min scratch buffer size\n");
			ctx->me_buffer_size =
				ALIGN(ENC_V100_MPEG4_ME_SIZE(mb_width,
							mb_height), 16);
		पूर्ण अन्यथा
			ctx->scratch_buf_size =
				S5P_FIMV_SCRATCH_BUF_SIZE_MPEG4_ENC_V6(
						mb_width,
						mb_height);
		ctx->scratch_buf_size = ALIGN(ctx->scratch_buf_size,
				S5P_FIMV_SCRATCH_BUFFER_ALIGN_V6);
		ctx->bank1.size =
			ctx->scratch_buf_size + ctx->पंचांगv_buffer_size +
			(ctx->pb_count * (ctx->luma_dpb_size +
			ctx->chroma_dpb_size + ctx->me_buffer_size));
		ctx->bank2.size = 0;
		अवरोध;
	हाल S5P_MFC_CODEC_VP8_ENC:
		अगर (IS_MFCV10(dev)) अणु
			mfc_debug(2, "Use min scratch buffer size\n");
			ctx->me_buffer_size =
				ALIGN(ENC_V100_VP8_ME_SIZE(mb_width, mb_height),
						16);
		पूर्ण अन्यथा अगर (IS_MFCV8_PLUS(dev))
			ctx->scratch_buf_size =
				S5P_FIMV_SCRATCH_BUF_SIZE_VP8_ENC_V8(
					mb_width,
					mb_height);
		अन्यथा
			ctx->scratch_buf_size =
				S5P_FIMV_SCRATCH_BUF_SIZE_VP8_ENC_V7(
						mb_width,
						mb_height);
		ctx->scratch_buf_size = ALIGN(ctx->scratch_buf_size,
				S5P_FIMV_SCRATCH_BUFFER_ALIGN_V6);
		ctx->bank1.size =
			ctx->scratch_buf_size + ctx->पंचांगv_buffer_size +
			(ctx->pb_count * (ctx->luma_dpb_size +
			ctx->chroma_dpb_size + ctx->me_buffer_size));
		ctx->bank2.size = 0;
		अवरोध;
	हाल S5P_MFC_CODEC_HEVC_ENC:
		mfc_debug(2, "Use min scratch buffer size\n");
		ctx->me_buffer_size =
			ALIGN(ENC_V100_HEVC_ME_SIZE(lcu_width, lcu_height), 16);
		ctx->scratch_buf_size = ALIGN(ctx->scratch_buf_size, 256);
		ctx->bank1.size =
			ctx->scratch_buf_size + ctx->पंचांगv_buffer_size +
			(ctx->pb_count * (ctx->luma_dpb_size +
			ctx->chroma_dpb_size + ctx->me_buffer_size));
		ctx->bank2.size = 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Allocate only अगर memory from bank 1 is necessary */
	अगर (ctx->bank1.size > 0) अणु
		ret = s5p_mfc_alloc_generic_buf(dev, BANK_L_CTX, &ctx->bank1);
		अगर (ret) अणु
			mfc_err("Failed to allocate Bank1 memory\n");
			वापस ret;
		पूर्ण
		BUG_ON(ctx->bank1.dma & ((1 << MFC_BANK1_ALIGN_ORDER) - 1));
	पूर्ण
	वापस 0;
पूर्ण

/* Release buffers allocated क्रम codec */
अटल व्योम s5p_mfc_release_codec_buffers_v6(काष्ठा s5p_mfc_ctx *ctx)
अणु
	s5p_mfc_release_generic_buf(ctx->dev, &ctx->bank1);
पूर्ण

/* Allocate memory क्रम instance data buffer */
अटल पूर्णांक s5p_mfc_alloc_instance_buffer_v6(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	काष्ठा s5p_mfc_buf_size_v6 *buf_size = dev->variant->buf_size->priv;
	पूर्णांक ret;

	mfc_debug_enter();

	चयन (ctx->codec_mode) अणु
	हाल S5P_MFC_CODEC_H264_DEC:
	हाल S5P_MFC_CODEC_H264_MVC_DEC:
	हाल S5P_MFC_CODEC_HEVC_DEC:
		ctx->ctx.size = buf_size->h264_dec_ctx;
		अवरोध;
	हाल S5P_MFC_CODEC_MPEG4_DEC:
	हाल S5P_MFC_CODEC_H263_DEC:
	हाल S5P_MFC_CODEC_VC1RCV_DEC:
	हाल S5P_MFC_CODEC_VC1_DEC:
	हाल S5P_MFC_CODEC_MPEG2_DEC:
	हाल S5P_MFC_CODEC_VP8_DEC:
	हाल S5P_MFC_CODEC_VP9_DEC:
		ctx->ctx.size = buf_size->other_dec_ctx;
		अवरोध;
	हाल S5P_MFC_CODEC_H264_ENC:
		ctx->ctx.size = buf_size->h264_enc_ctx;
		अवरोध;
	हाल S5P_MFC_CODEC_HEVC_ENC:
		ctx->ctx.size = buf_size->hevc_enc_ctx;
		अवरोध;
	हाल S5P_MFC_CODEC_MPEG4_ENC:
	हाल S5P_MFC_CODEC_H263_ENC:
	हाल S5P_MFC_CODEC_VP8_ENC:
		ctx->ctx.size = buf_size->other_enc_ctx;
		अवरोध;
	शेष:
		ctx->ctx.size = 0;
		mfc_err("Codec type(%d) should be checked!\n", ctx->codec_mode);
		अवरोध;
	पूर्ण

	ret = s5p_mfc_alloc_priv_buf(dev, BANK_L_CTX, &ctx->ctx);
	अगर (ret) अणु
		mfc_err("Failed to allocate instance buffer\n");
		वापस ret;
	पूर्ण

	स_रखो(ctx->ctx.virt, 0, ctx->ctx.size);
	wmb();

	mfc_debug_leave();

	वापस 0;
पूर्ण

/* Release instance buffer */
अटल व्योम s5p_mfc_release_instance_buffer_v6(काष्ठा s5p_mfc_ctx *ctx)
अणु
	s5p_mfc_release_priv_buf(ctx->dev, &ctx->ctx);
पूर्ण

/* Allocate context buffers क्रम SYS_INIT */
अटल पूर्णांक s5p_mfc_alloc_dev_context_buffer_v6(काष्ठा s5p_mfc_dev *dev)
अणु
	काष्ठा s5p_mfc_buf_size_v6 *buf_size = dev->variant->buf_size->priv;
	पूर्णांक ret;

	mfc_debug_enter();

	dev->ctx_buf.size = buf_size->dev_ctx;
	ret = s5p_mfc_alloc_priv_buf(dev, BANK_L_CTX, &dev->ctx_buf);
	अगर (ret) अणु
		mfc_err("Failed to allocate device context buffer\n");
		वापस ret;
	पूर्ण

	स_रखो(dev->ctx_buf.virt, 0, buf_size->dev_ctx);
	wmb();

	mfc_debug_leave();

	वापस 0;
पूर्ण

/* Release context buffers क्रम SYS_INIT */
अटल व्योम s5p_mfc_release_dev_context_buffer_v6(काष्ठा s5p_mfc_dev *dev)
अणु
	s5p_mfc_release_priv_buf(dev, &dev->ctx_buf);
पूर्ण

अटल पूर्णांक calc_plane(पूर्णांक width, पूर्णांक height)
अणु
	पूर्णांक mbX, mbY;

	mbX = DIV_ROUND_UP(width, S5P_FIMV_NUM_PIXELS_IN_MB_ROW_V6);
	mbY = DIV_ROUND_UP(height, S5P_FIMV_NUM_PIXELS_IN_MB_COL_V6);

	अगर (width * height < S5P_FIMV_MAX_FRAME_SIZE_V6)
		mbY = (mbY + 1) / 2 * 2;

	वापस (mbX * S5P_FIMV_NUM_PIXELS_IN_MB_COL_V6) *
		(mbY * S5P_FIMV_NUM_PIXELS_IN_MB_ROW_V6);
पूर्ण

अटल व्योम s5p_mfc_dec_calc_dpb_size_v6(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	ctx->buf_width = ALIGN(ctx->img_width, S5P_FIMV_NV12MT_HALIGN_V6);
	ctx->buf_height = ALIGN(ctx->img_height, S5P_FIMV_NV12MT_VALIGN_V6);
	mfc_debug(2, "SEQ Done: Movie dimensions %dx%d,\n"
			"buffer dimensions: %dx%d\n", ctx->img_width,
			ctx->img_height, ctx->buf_width, ctx->buf_height);

	ctx->luma_size = calc_plane(ctx->img_width, ctx->img_height);
	ctx->chroma_size = calc_plane(ctx->img_width, (ctx->img_height >> 1));
	अगर (IS_MFCV8_PLUS(ctx->dev)) अणु
		/* MFCv8 needs additional 64 bytes क्रम luma,chroma dpb*/
		ctx->luma_size += S5P_FIMV_D_ALIGN_PLANE_SIZE_V8;
		ctx->chroma_size += S5P_FIMV_D_ALIGN_PLANE_SIZE_V8;
	पूर्ण

	अगर (ctx->codec_mode == S5P_MFC_CODEC_H264_DEC ||
			ctx->codec_mode == S5P_MFC_CODEC_H264_MVC_DEC) अणु
		अगर (IS_MFCV10(dev)) अणु
			ctx->mv_size = S5P_MFC_DEC_MV_SIZE_V10(ctx->img_width,
					ctx->img_height);
		पूर्ण अन्यथा अणु
			ctx->mv_size = S5P_MFC_DEC_MV_SIZE_V6(ctx->img_width,
					ctx->img_height);
		पूर्ण
	पूर्ण अन्यथा अगर (ctx->codec_mode == S5P_MFC_CODEC_HEVC_DEC) अणु
		ctx->mv_size = s5p_mfc_dec_hevc_mv_size(ctx->img_width,
				ctx->img_height);
		ctx->mv_size = ALIGN(ctx->mv_size, 32);
	पूर्ण अन्यथा अणु
		ctx->mv_size = 0;
	पूर्ण
पूर्ण

अटल व्योम s5p_mfc_enc_calc_src_size_v6(काष्ठा s5p_mfc_ctx *ctx)
अणु
	अचिन्हित पूर्णांक mb_width, mb_height;

	mb_width = MB_WIDTH(ctx->img_width);
	mb_height = MB_HEIGHT(ctx->img_height);

	ctx->buf_width = ALIGN(ctx->img_width, S5P_FIMV_NV12M_HALIGN_V6);
	ctx->luma_size = ALIGN((mb_width * mb_height) * 256, 256);
	ctx->chroma_size = ALIGN((mb_width * mb_height) * 128, 256);

	/* MFCv7 needs pad bytes क्रम Luma and Chroma */
	अगर (IS_MFCV7_PLUS(ctx->dev)) अणु
		ctx->luma_size += MFC_LUMA_PAD_BYTES_V7;
		ctx->chroma_size += MFC_CHROMA_PAD_BYTES_V7;
	पूर्ण
पूर्ण

/* Set रेजिस्टरs क्रम decoding stream buffer */
अटल पूर्णांक s5p_mfc_set_dec_stream_buffer_v6(काष्ठा s5p_mfc_ctx *ctx,
			पूर्णांक buf_addr, अचिन्हित पूर्णांक start_num_byte,
			अचिन्हित पूर्णांक strm_size)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	स्थिर काष्ठा s5p_mfc_regs *mfc_regs = dev->mfc_regs;
	काष्ठा s5p_mfc_buf_size *buf_size = dev->variant->buf_size;

	mfc_debug_enter();
	mfc_debug(2, "inst_no: %d, buf_addr: 0x%08x,\n"
		"buf_size: 0x%08x (%d)\n",
		ctx->inst_no, buf_addr, strm_size, strm_size);
	ग_लिखोl(strm_size, mfc_regs->d_stream_data_size);
	ग_लिखोl(buf_addr, mfc_regs->d_cpb_buffer_addr);
	ग_लिखोl(buf_size->cpb, mfc_regs->d_cpb_buffer_size);
	ग_लिखोl(start_num_byte, mfc_regs->d_cpb_buffer_offset);

	mfc_debug_leave();
	वापस 0;
पूर्ण

/* Set decoding frame buffer */
अटल पूर्णांक s5p_mfc_set_dec_frame_buffer_v6(काष्ठा s5p_mfc_ctx *ctx)
अणु
	अचिन्हित पूर्णांक frame_size, i;
	अचिन्हित पूर्णांक frame_size_ch, frame_size_mv;
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	स्थिर काष्ठा s5p_mfc_regs *mfc_regs = dev->mfc_regs;
	माप_प्रकार buf_addr1;
	पूर्णांक buf_size1;
	पूर्णांक align_gap;

	buf_addr1 = ctx->bank1.dma;
	buf_size1 = ctx->bank1.size;

	mfc_debug(2, "Buf1: %p (%d)\n", (व्योम *)buf_addr1, buf_size1);
	mfc_debug(2, "Total DPB COUNT: %d\n", ctx->total_dpb_count);
	mfc_debug(2, "Setting display delay to %d\n", ctx->display_delay);

	ग_लिखोl(ctx->total_dpb_count, mfc_regs->d_num_dpb);
	ग_लिखोl(ctx->luma_size, mfc_regs->d_first_plane_dpb_size);
	ग_लिखोl(ctx->chroma_size, mfc_regs->d_second_plane_dpb_size);

	ग_लिखोl(buf_addr1, mfc_regs->d_scratch_buffer_addr);
	ग_लिखोl(ctx->scratch_buf_size, mfc_regs->d_scratch_buffer_size);

	अगर (IS_MFCV8_PLUS(dev)) अणु
		ग_लिखोl(ctx->img_width,
			mfc_regs->d_first_plane_dpb_stride_size);
		ग_लिखोl(ctx->img_width,
			mfc_regs->d_second_plane_dpb_stride_size);
	पूर्ण

	buf_addr1 += ctx->scratch_buf_size;
	buf_size1 -= ctx->scratch_buf_size;

	अगर (ctx->codec_mode == S5P_FIMV_CODEC_H264_DEC ||
			ctx->codec_mode == S5P_FIMV_CODEC_H264_MVC_DEC ||
			ctx->codec_mode == S5P_FIMV_CODEC_HEVC_DEC) अणु
		ग_लिखोl(ctx->mv_size, mfc_regs->d_mv_buffer_size);
		ग_लिखोl(ctx->mv_count, mfc_regs->d_num_mv);
	पूर्ण

	frame_size = ctx->luma_size;
	frame_size_ch = ctx->chroma_size;
	frame_size_mv = ctx->mv_size;
	mfc_debug(2, "Frame size: %d ch: %d mv: %d\n",
			frame_size, frame_size_ch, frame_size_mv);

	क्रम (i = 0; i < ctx->total_dpb_count; i++) अणु
		/* Bank2 */
		mfc_debug(2, "Luma %d: %zx\n", i,
					ctx->dst_bufs[i].cookie.raw.luma);
		ग_लिखोl(ctx->dst_bufs[i].cookie.raw.luma,
				mfc_regs->d_first_plane_dpb + i * 4);
		mfc_debug(2, "\tChroma %d: %zx\n", i,
					ctx->dst_bufs[i].cookie.raw.chroma);
		ग_लिखोl(ctx->dst_bufs[i].cookie.raw.chroma,
				mfc_regs->d_second_plane_dpb + i * 4);
	पूर्ण
	अगर (ctx->codec_mode == S5P_MFC_CODEC_H264_DEC ||
			ctx->codec_mode == S5P_MFC_CODEC_H264_MVC_DEC ||
			ctx->codec_mode == S5P_MFC_CODEC_HEVC_DEC) अणु
		क्रम (i = 0; i < ctx->mv_count; i++) अणु
			/* To test alignment */
			align_gap = buf_addr1;
			buf_addr1 = ALIGN(buf_addr1, 16);
			align_gap = buf_addr1 - align_gap;
			buf_size1 -= align_gap;

			mfc_debug(2, "\tBuf1: %zx, size: %d\n",
					buf_addr1, buf_size1);
			ग_लिखोl(buf_addr1, mfc_regs->d_mv_buffer + i * 4);
			buf_addr1 += frame_size_mv;
			buf_size1 -= frame_size_mv;
		पूर्ण
	पूर्ण
	अगर (ctx->codec_mode == S5P_FIMV_CODEC_VP9_DEC) अणु
		ग_लिखोl(buf_addr1, mfc_regs->d_अटल_buffer_addr);
		ग_लिखोl(DEC_VP9_STATIC_BUFFER_SIZE,
				mfc_regs->d_अटल_buffer_size);
		buf_addr1 += DEC_VP9_STATIC_BUFFER_SIZE;
		buf_size1 -= DEC_VP9_STATIC_BUFFER_SIZE;
	पूर्ण

	mfc_debug(2, "Buf1: %zx, buf_size1: %d (frames %d)\n",
			buf_addr1, buf_size1, ctx->total_dpb_count);
	अगर (buf_size1 < 0) अणु
		mfc_debug(2, "Not enough memory has been allocated.\n");
		वापस -ENOMEM;
	पूर्ण

	ग_लिखोl(ctx->inst_no, mfc_regs->instance_id);
	s5p_mfc_hw_call(dev->mfc_cmds, cmd_host2risc, dev,
			S5P_FIMV_CH_INIT_BUFS_V6, शून्य);

	mfc_debug(2, "After setting buffers.\n");
	वापस 0;
पूर्ण

/* Set रेजिस्टरs क्रम encoding stream buffer */
अटल पूर्णांक s5p_mfc_set_enc_stream_buffer_v6(काष्ठा s5p_mfc_ctx *ctx,
		अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक size)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	स्थिर काष्ठा s5p_mfc_regs *mfc_regs = dev->mfc_regs;

	ग_लिखोl(addr, mfc_regs->e_stream_buffer_addr); /* 16B align */
	ग_लिखोl(size, mfc_regs->e_stream_buffer_size);

	mfc_debug(2, "stream buf addr: 0x%08lx, size: 0x%x\n",
		  addr, size);

	वापस 0;
पूर्ण

अटल व्योम s5p_mfc_set_enc_frame_buffer_v6(काष्ठा s5p_mfc_ctx *ctx,
		अचिन्हित दीर्घ y_addr, अचिन्हित दीर्घ c_addr)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	स्थिर काष्ठा s5p_mfc_regs *mfc_regs = dev->mfc_regs;

	ग_लिखोl(y_addr, mfc_regs->e_source_first_plane_addr);
	ग_लिखोl(c_addr, mfc_regs->e_source_second_plane_addr);

	mfc_debug(2, "enc src y buf addr: 0x%08lx\n", y_addr);
	mfc_debug(2, "enc src c buf addr: 0x%08lx\n", c_addr);
पूर्ण

अटल व्योम s5p_mfc_get_enc_frame_buffer_v6(काष्ठा s5p_mfc_ctx *ctx,
		अचिन्हित दीर्घ *y_addr, अचिन्हित दीर्घ *c_addr)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	स्थिर काष्ठा s5p_mfc_regs *mfc_regs = dev->mfc_regs;
	अचिन्हित दीर्घ enc_recon_y_addr, enc_recon_c_addr;

	*y_addr = पढ़ोl(mfc_regs->e_encoded_source_first_plane_addr);
	*c_addr = पढ़ोl(mfc_regs->e_encoded_source_second_plane_addr);

	enc_recon_y_addr = पढ़ोl(mfc_regs->e_recon_luma_dpb_addr);
	enc_recon_c_addr = पढ़ोl(mfc_regs->e_recon_chroma_dpb_addr);

	mfc_debug(2, "recon y addr: 0x%08lx y_addr: 0x%08lx\n", enc_recon_y_addr, *y_addr);
	mfc_debug(2, "recon c addr: 0x%08lx\n", enc_recon_c_addr);
पूर्ण

/* Set encoding ref & codec buffer */
अटल पूर्णांक s5p_mfc_set_enc_ref_buffer_v6(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	स्थिर काष्ठा s5p_mfc_regs *mfc_regs = dev->mfc_regs;
	माप_प्रकार buf_addr1;
	पूर्णांक i, buf_size1;

	mfc_debug_enter();

	buf_addr1 = ctx->bank1.dma;
	buf_size1 = ctx->bank1.size;

	mfc_debug(2, "Buf1: %p (%d)\n", (व्योम *)buf_addr1, buf_size1);

	अगर (IS_MFCV10(dev)) अणु
		/* start address of per buffer is aligned */
		क्रम (i = 0; i < ctx->pb_count; i++) अणु
			ग_लिखोl(buf_addr1, mfc_regs->e_luma_dpb + (4 * i));
			buf_addr1 += ctx->luma_dpb_size;
			buf_size1 -= ctx->luma_dpb_size;
		पूर्ण
		क्रम (i = 0; i < ctx->pb_count; i++) अणु
			ग_लिखोl(buf_addr1, mfc_regs->e_chroma_dpb + (4 * i));
			buf_addr1 += ctx->chroma_dpb_size;
			buf_size1 -= ctx->chroma_dpb_size;
		पूर्ण
		क्रम (i = 0; i < ctx->pb_count; i++) अणु
			ग_लिखोl(buf_addr1, mfc_regs->e_me_buffer + (4 * i));
			buf_addr1 += ctx->me_buffer_size;
			buf_size1 -= ctx->me_buffer_size;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < ctx->pb_count; i++) अणु
			ग_लिखोl(buf_addr1, mfc_regs->e_luma_dpb + (4 * i));
			buf_addr1 += ctx->luma_dpb_size;
			ग_लिखोl(buf_addr1, mfc_regs->e_chroma_dpb + (4 * i));
			buf_addr1 += ctx->chroma_dpb_size;
			ग_लिखोl(buf_addr1, mfc_regs->e_me_buffer + (4 * i));
			buf_addr1 += ctx->me_buffer_size;
			buf_size1 -= (ctx->luma_dpb_size + ctx->chroma_dpb_size
					+ ctx->me_buffer_size);
		पूर्ण
	पूर्ण

	ग_लिखोl(buf_addr1, mfc_regs->e_scratch_buffer_addr);
	ग_लिखोl(ctx->scratch_buf_size, mfc_regs->e_scratch_buffer_size);
	buf_addr1 += ctx->scratch_buf_size;
	buf_size1 -= ctx->scratch_buf_size;

	ग_लिखोl(buf_addr1, mfc_regs->e_पंचांगv_buffer0);
	buf_addr1 += ctx->पंचांगv_buffer_size >> 1;
	ग_लिखोl(buf_addr1, mfc_regs->e_पंचांगv_buffer1);
	buf_addr1 += ctx->पंचांगv_buffer_size >> 1;
	buf_size1 -= ctx->पंचांगv_buffer_size;

	mfc_debug(2, "Buf1: %zu, buf_size1: %d (ref frames %d)\n",
			buf_addr1, buf_size1, ctx->pb_count);
	अगर (buf_size1 < 0) अणु
		mfc_debug(2, "Not enough memory has been allocated.\n");
		वापस -ENOMEM;
	पूर्ण

	ग_लिखोl(ctx->inst_no, mfc_regs->instance_id);
	s5p_mfc_hw_call(dev->mfc_cmds, cmd_host2risc, dev,
			S5P_FIMV_CH_INIT_BUFS_V6, शून्य);

	mfc_debug_leave();

	वापस 0;
पूर्ण

अटल पूर्णांक s5p_mfc_set_slice_mode(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	स्थिर काष्ठा s5p_mfc_regs *mfc_regs = dev->mfc_regs;

	/* multi-slice control */
	/* multi-slice MB number or bit size */
	ग_लिखोl(ctx->slice_mode, mfc_regs->e_mslice_mode);
	अगर (ctx->slice_mode == V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_MAX_MB) अणु
		ग_लिखोl(ctx->slice_size.mb, mfc_regs->e_mslice_size_mb);
	पूर्ण अन्यथा अगर (ctx->slice_mode ==
			V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_MAX_BYTES) अणु
		ग_लिखोl(ctx->slice_size.bits, mfc_regs->e_mslice_size_bits);
	पूर्ण अन्यथा अणु
		ग_लिखोl(0x0, mfc_regs->e_mslice_size_mb);
		ग_लिखोl(0x0, mfc_regs->e_mslice_size_bits);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s5p_mfc_set_enc_params(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	स्थिर काष्ठा s5p_mfc_regs *mfc_regs = dev->mfc_regs;
	काष्ठा s5p_mfc_enc_params *p = &ctx->enc_params;
	अचिन्हित पूर्णांक reg = 0;

	mfc_debug_enter();

	/* width */
	ग_लिखोl(ctx->img_width, mfc_regs->e_frame_width); /* 16 align */
	/* height */
	ग_लिखोl(ctx->img_height, mfc_regs->e_frame_height); /* 16 align */

	/* cropped width */
	ग_लिखोl(ctx->img_width, mfc_regs->e_cropped_frame_width);
	/* cropped height */
	ग_लिखोl(ctx->img_height, mfc_regs->e_cropped_frame_height);
	/* cropped offset */
	ग_लिखोl(0x0, mfc_regs->e_frame_crop_offset);

	/* pictype : IDR period */
	reg = 0;
	reg |= p->gop_size & 0xFFFF;
	ग_लिखोl(reg, mfc_regs->e_gop_config);

	/* multi-slice control */
	/* multi-slice MB number or bit size */
	ctx->slice_mode = p->slice_mode;
	reg = 0;
	अगर (p->slice_mode == V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_MAX_MB) अणु
		reg |= (0x1 << 3);
		ग_लिखोl(reg, mfc_regs->e_enc_options);
		ctx->slice_size.mb = p->slice_mb;
	पूर्ण अन्यथा अगर (p->slice_mode == V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_MAX_BYTES) अणु
		reg |= (0x1 << 3);
		ग_लिखोl(reg, mfc_regs->e_enc_options);
		ctx->slice_size.bits = p->slice_bit;
	पूर्ण अन्यथा अणु
		reg &= ~(0x1 << 3);
		ग_लिखोl(reg, mfc_regs->e_enc_options);
	पूर्ण

	s5p_mfc_set_slice_mode(ctx);

	/* cyclic पूर्णांकra refresh */
	ग_लिखोl(p->पूर्णांकra_refresh_mb, mfc_regs->e_ir_size);
	reg = पढ़ोl(mfc_regs->e_enc_options);
	अगर (p->पूर्णांकra_refresh_mb == 0)
		reg &= ~(0x1 << 4);
	अन्यथा
		reg |= (0x1 << 4);
	ग_लिखोl(reg, mfc_regs->e_enc_options);

	/* 'NON_REFERENCE_STORE_ENABLE' क्रम debugging */
	reg = पढ़ोl(mfc_regs->e_enc_options);
	reg &= ~(0x1 << 9);
	ग_लिखोl(reg, mfc_regs->e_enc_options);

	/* memory काष्ठाure cur. frame */
	अगर (ctx->src_fmt->fourcc == V4L2_PIX_FMT_NV12M) अणु
		/* 0: Linear, 1: 2D tiled*/
		reg = पढ़ोl(mfc_regs->e_enc_options);
		reg &= ~(0x1 << 7);
		ग_लिखोl(reg, mfc_regs->e_enc_options);
		/* 0: NV12(CbCr), 1: NV21(CrCb) */
		ग_लिखोl(0x0, mfc_regs->pixel_क्रमmat);
	पूर्ण अन्यथा अगर (ctx->src_fmt->fourcc == V4L2_PIX_FMT_NV21M) अणु
		/* 0: Linear, 1: 2D tiled*/
		reg = पढ़ोl(mfc_regs->e_enc_options);
		reg &= ~(0x1 << 7);
		ग_लिखोl(reg, mfc_regs->e_enc_options);
		/* 0: NV12(CbCr), 1: NV21(CrCb) */
		ग_लिखोl(0x1, mfc_regs->pixel_क्रमmat);
	पूर्ण अन्यथा अगर (ctx->src_fmt->fourcc == V4L2_PIX_FMT_NV12MT_16X16) अणु
		/* 0: Linear, 1: 2D tiled*/
		reg = पढ़ोl(mfc_regs->e_enc_options);
		reg |= (0x1 << 7);
		ग_लिखोl(reg, mfc_regs->e_enc_options);
		/* 0: NV12(CbCr), 1: NV21(CrCb) */
		ग_लिखोl(0x0, mfc_regs->pixel_क्रमmat);
	पूर्ण

	/* memory काष्ठाure recon. frame */
	/* 0: Linear, 1: 2D tiled */
	reg = पढ़ोl(mfc_regs->e_enc_options);
	reg |= (0x1 << 8);
	ग_लिखोl(reg, mfc_regs->e_enc_options);

	/* padding control & value */
	ग_लिखोl(0x0, mfc_regs->e_padding_ctrl);
	अगर (p->pad) अणु
		reg = 0;
		/** enable */
		reg |= (1UL << 31);
		/** cr value */
		reg |= ((p->pad_cr & 0xFF) << 16);
		/** cb value */
		reg |= ((p->pad_cb & 0xFF) << 8);
		/** y value */
		reg |= p->pad_luma & 0xFF;
		ग_लिखोl(reg, mfc_regs->e_padding_ctrl);
	पूर्ण

	/* rate control config. */
	reg = 0;
	/* frame-level rate control */
	reg |= ((p->rc_frame & 0x1) << 9);
	ग_लिखोl(reg, mfc_regs->e_rc_config);

	/* bit rate */
	अगर (p->rc_frame)
		ग_लिखोl(p->rc_bitrate,
			mfc_regs->e_rc_bit_rate);
	अन्यथा
		ग_लिखोl(1, mfc_regs->e_rc_bit_rate);

	/* reaction coefficient */
	अगर (p->rc_frame) अणु
		अगर (p->rc_reaction_coeff < TIGHT_CBR_MAX) /* tight CBR */
			ग_लिखोl(1, mfc_regs->e_rc_mode);
		अन्यथा					  /* loose CBR */
			ग_लिखोl(2, mfc_regs->e_rc_mode);
	पूर्ण

	/* seq header ctrl */
	reg = पढ़ोl(mfc_regs->e_enc_options);
	reg &= ~(0x1 << 2);
	reg |= ((p->seq_hdr_mode & 0x1) << 2);

	/* frame skip mode */
	reg &= ~(0x3);
	reg |= (p->frame_skip_mode & 0x3);
	ग_लिखोl(reg, mfc_regs->e_enc_options);

	/* 'DROP_CONTROL_ENABLE', disable */
	reg = पढ़ोl(mfc_regs->e_rc_config);
	reg &= ~(0x1 << 10);
	ग_लिखोl(reg, mfc_regs->e_rc_config);

	/* setting क्रम MV range [16, 256] */
	reg = (p->mv_h_range & S5P_FIMV_E_MV_RANGE_V6_MASK);
	ग_लिखोl(reg, mfc_regs->e_mv_hor_range);

	reg = (p->mv_v_range & S5P_FIMV_E_MV_RANGE_V6_MASK);
	ग_लिखोl(reg, mfc_regs->e_mv_ver_range);

	ग_लिखोl(0x0, mfc_regs->e_frame_insertion);
	ग_लिखोl(0x0, mfc_regs->e_roi_buffer_addr);
	ग_लिखोl(0x0, mfc_regs->e_param_change);
	ग_लिखोl(0x0, mfc_regs->e_rc_roi_ctrl);
	ग_लिखोl(0x0, mfc_regs->e_picture_tag);

	ग_लिखोl(0x0, mfc_regs->e_bit_count_enable);
	ग_लिखोl(0x0, mfc_regs->e_max_bit_count);
	ग_लिखोl(0x0, mfc_regs->e_min_bit_count);

	ग_लिखोl(0x0, mfc_regs->e_metadata_buffer_addr);
	ग_लिखोl(0x0, mfc_regs->e_metadata_buffer_size);

	mfc_debug_leave();

	वापस 0;
पूर्ण

अटल पूर्णांक s5p_mfc_set_enc_params_h264(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	स्थिर काष्ठा s5p_mfc_regs *mfc_regs = dev->mfc_regs;
	काष्ठा s5p_mfc_enc_params *p = &ctx->enc_params;
	काष्ठा s5p_mfc_h264_enc_params *p_h264 = &p->codec.h264;
	अचिन्हित पूर्णांक reg = 0;
	पूर्णांक i;

	mfc_debug_enter();

	s5p_mfc_set_enc_params(ctx);

	/* pictype : number of B */
	reg = पढ़ोl(mfc_regs->e_gop_config);
	reg &= ~(0x3 << 16);
	reg |= ((p->num_b_frame & 0x3) << 16);
	ग_लिखोl(reg, mfc_regs->e_gop_config);

	/* profile & level */
	reg = 0;
	/** level */
	reg |= ((p_h264->level & 0xFF) << 8);
	/** profile - 0 ~ 3 */
	reg |= p_h264->profile & 0x3F;
	ग_लिखोl(reg, mfc_regs->e_picture_profile);

	/* rate control config. */
	reg = पढ़ोl(mfc_regs->e_rc_config);
	/** macroblock level rate control */
	reg &= ~(0x1 << 8);
	reg |= ((p->rc_mb & 0x1) << 8);
	ग_लिखोl(reg, mfc_regs->e_rc_config);

	/** frame QP */
	reg &= ~(0x3F);
	reg |= p_h264->rc_frame_qp & 0x3F;
	ग_लिखोl(reg, mfc_regs->e_rc_config);

	/* max & min value of QP */
	reg = 0;
	/** max QP */
	reg |= ((p_h264->rc_max_qp & 0x3F) << 8);
	/** min QP */
	reg |= p_h264->rc_min_qp & 0x3F;
	ग_लिखोl(reg, mfc_regs->e_rc_qp_bound);

	/* other QPs */
	ग_लिखोl(0x0, mfc_regs->e_fixed_picture_qp);
	अगर (!p->rc_frame && !p->rc_mb) अणु
		reg = 0;
		reg |= ((p_h264->rc_b_frame_qp & 0x3F) << 16);
		reg |= ((p_h264->rc_p_frame_qp & 0x3F) << 8);
		reg |= p_h264->rc_frame_qp & 0x3F;
		ग_लिखोl(reg, mfc_regs->e_fixed_picture_qp);
	पूर्ण

	/* frame rate */
	अगर (p->rc_frame && p->rc_framerate_num && p->rc_framerate_denom) अणु
		reg = 0;
		reg |= ((p->rc_framerate_num & 0xFFFF) << 16);
		reg |= p->rc_framerate_denom & 0xFFFF;
		ग_लिखोl(reg, mfc_regs->e_rc_frame_rate);
	पूर्ण

	/* vbv buffer size */
	अगर (p->frame_skip_mode ==
			V4L2_MPEG_MFC51_VIDEO_FRAME_SKIP_MODE_BUF_LIMIT) अणु
		ग_लिखोl(p_h264->cpb_size & 0xFFFF,
				mfc_regs->e_vbv_buffer_size);

		अगर (p->rc_frame)
			ग_लिखोl(p->vbv_delay, mfc_regs->e_vbv_init_delay);
	पूर्ण

	/* पूर्णांकerlace */
	reg = 0;
	reg |= ((p_h264->पूर्णांकerlace & 0x1) << 3);
	ग_लिखोl(reg, mfc_regs->e_h264_options);

	/* height */
	अगर (p_h264->पूर्णांकerlace) अणु
		ग_लिखोl(ctx->img_height >> 1,
				mfc_regs->e_frame_height); /* 32 align */
		/* cropped height */
		ग_लिखोl(ctx->img_height >> 1,
				mfc_regs->e_cropped_frame_height);
	पूर्ण

	/* loop filter ctrl */
	reg = पढ़ोl(mfc_regs->e_h264_options);
	reg &= ~(0x3 << 1);
	reg |= ((p_h264->loop_filter_mode & 0x3) << 1);
	ग_लिखोl(reg, mfc_regs->e_h264_options);

	/* loopfilter alpha offset */
	अगर (p_h264->loop_filter_alpha < 0) अणु
		reg = 0x10;
		reg |= (0xFF - p_h264->loop_filter_alpha) + 1;
	पूर्ण अन्यथा अणु
		reg = 0x00;
		reg |= (p_h264->loop_filter_alpha & 0xF);
	पूर्ण
	ग_लिखोl(reg, mfc_regs->e_h264_lf_alpha_offset);

	/* loopfilter beta offset */
	अगर (p_h264->loop_filter_beta < 0) अणु
		reg = 0x10;
		reg |= (0xFF - p_h264->loop_filter_beta) + 1;
	पूर्ण अन्यथा अणु
		reg = 0x00;
		reg |= (p_h264->loop_filter_beta & 0xF);
	पूर्ण
	ग_लिखोl(reg, mfc_regs->e_h264_lf_beta_offset);

	/* entropy coding mode */
	reg = पढ़ोl(mfc_regs->e_h264_options);
	reg &= ~(0x1);
	reg |= p_h264->entropy_mode & 0x1;
	ग_लिखोl(reg, mfc_regs->e_h264_options);

	/* number of ref. picture */
	reg = पढ़ोl(mfc_regs->e_h264_options);
	reg &= ~(0x1 << 7);
	reg |= (((p_h264->num_ref_pic_4p - 1) & 0x1) << 7);
	ग_लिखोl(reg, mfc_regs->e_h264_options);

	/* 8x8 transक्रमm enable */
	reg = पढ़ोl(mfc_regs->e_h264_options);
	reg &= ~(0x3 << 12);
	reg |= ((p_h264->_8x8_transक्रमm & 0x3) << 12);
	ग_लिखोl(reg, mfc_regs->e_h264_options);

	/* macroblock adaptive scaling features */
	ग_लिखोl(0x0, mfc_regs->e_mb_rc_config);
	अगर (p->rc_mb) अणु
		reg = 0;
		/** dark region */
		reg |= ((p_h264->rc_mb_dark & 0x1) << 3);
		/** smooth region */
		reg |= ((p_h264->rc_mb_smooth & 0x1) << 2);
		/** अटल region */
		reg |= ((p_h264->rc_mb_अटल & 0x1) << 1);
		/** high activity region */
		reg |= p_h264->rc_mb_activity & 0x1;
		ग_लिखोl(reg, mfc_regs->e_mb_rc_config);
	पूर्ण

	/* aspect ratio VUI */
	पढ़ोl(mfc_regs->e_h264_options);
	reg &= ~(0x1 << 5);
	reg |= ((p_h264->vui_sar & 0x1) << 5);
	ग_लिखोl(reg, mfc_regs->e_h264_options);

	ग_लिखोl(0x0, mfc_regs->e_aspect_ratio);
	ग_लिखोl(0x0, mfc_regs->e_extended_sar);
	अगर (p_h264->vui_sar) अणु
		/* aspect ration IDC */
		reg = 0;
		reg |= p_h264->vui_sar_idc & 0xFF;
		ग_लिखोl(reg, mfc_regs->e_aspect_ratio);
		अगर (p_h264->vui_sar_idc == 0xFF) अणु
			/* extended SAR */
			reg = 0;
			reg |= (p_h264->vui_ext_sar_width & 0xFFFF) << 16;
			reg |= p_h264->vui_ext_sar_height & 0xFFFF;
			ग_लिखोl(reg, mfc_regs->e_extended_sar);
		पूर्ण
	पूर्ण

	/* पूर्णांकra picture period क्रम H.264 खोलो GOP */
	/* control */
	पढ़ोl(mfc_regs->e_h264_options);
	reg &= ~(0x1 << 4);
	reg |= ((p_h264->खोलो_gop & 0x1) << 4);
	ग_लिखोl(reg, mfc_regs->e_h264_options);

	/* value */
	ग_लिखोl(0x0, mfc_regs->e_h264_i_period);
	अगर (p_h264->खोलो_gop) अणु
		reg = 0;
		reg |= p_h264->खोलो_gop_size & 0xFFFF;
		ग_लिखोl(reg, mfc_regs->e_h264_i_period);
	पूर्ण

	/* 'WEIGHTED_BI_PREDICTION' क्रम B is disable */
	पढ़ोl(mfc_regs->e_h264_options);
	reg &= ~(0x3 << 9);
	ग_लिखोl(reg, mfc_regs->e_h264_options);

	/* 'CONSTRAINED_INTRA_PRED_ENABLE' is disable */
	पढ़ोl(mfc_regs->e_h264_options);
	reg &= ~(0x1 << 14);
	ग_लिखोl(reg, mfc_regs->e_h264_options);

	/* ASO */
	पढ़ोl(mfc_regs->e_h264_options);
	reg &= ~(0x1 << 6);
	reg |= ((p_h264->aso & 0x1) << 6);
	ग_लिखोl(reg, mfc_regs->e_h264_options);

	/* hier qp enable */
	पढ़ोl(mfc_regs->e_h264_options);
	reg &= ~(0x1 << 8);
	reg |= ((p_h264->खोलो_gop & 0x1) << 8);
	ग_लिखोl(reg, mfc_regs->e_h264_options);
	reg = 0;
	अगर (p_h264->hier_qp && p_h264->hier_qp_layer) अणु
		reg |= (p_h264->hier_qp_type & 0x1) << 0x3;
		reg |= p_h264->hier_qp_layer & 0x7;
		ग_लिखोl(reg, mfc_regs->e_h264_num_t_layer);
		/* QP value क्रम each layer */
		क्रम (i = 0; i < p_h264->hier_qp_layer &&
				i < ARRAY_SIZE(p_h264->hier_qp_layer_qp); i++) अणु
			ग_लिखोl(p_h264->hier_qp_layer_qp[i],
				mfc_regs->e_h264_hierarchical_qp_layer0
				+ i * 4);
		पूर्ण
	पूर्ण
	/* number of coding layer should be zero when hierarchical is disable */
	ग_लिखोl(reg, mfc_regs->e_h264_num_t_layer);

	/* frame packing SEI generation */
	पढ़ोl(mfc_regs->e_h264_options);
	reg &= ~(0x1 << 25);
	reg |= ((p_h264->sei_frame_packing & 0x1) << 25);
	ग_लिखोl(reg, mfc_regs->e_h264_options);
	अगर (p_h264->sei_frame_packing) अणु
		reg = 0;
		/** current frame0 flag */
		reg |= ((p_h264->sei_fp_curr_frame_0 & 0x1) << 2);
		/** arrangement type */
		reg |= p_h264->sei_fp_arrangement_type & 0x3;
		ग_लिखोl(reg, mfc_regs->e_h264_frame_packing_sei_info);
	पूर्ण

	अगर (p_h264->fmo) अणु
		चयन (p_h264->fmo_map_type) अणु
		हाल V4L2_MPEG_VIDEO_H264_FMO_MAP_TYPE_INTERLEAVED_SLICES:
			अगर (p_h264->fmo_slice_grp > 4)
				p_h264->fmo_slice_grp = 4;
			क्रम (i = 0; i < (p_h264->fmo_slice_grp & 0xF); i++)
				ग_लिखोl(p_h264->fmo_run_len[i] - 1,
					mfc_regs->e_h264_fmo_run_length_minus1_0
					+ i * 4);
			अवरोध;
		हाल V4L2_MPEG_VIDEO_H264_FMO_MAP_TYPE_SCATTERED_SLICES:
			अगर (p_h264->fmo_slice_grp > 4)
				p_h264->fmo_slice_grp = 4;
			अवरोध;
		हाल V4L2_MPEG_VIDEO_H264_FMO_MAP_TYPE_RASTER_SCAN:
		हाल V4L2_MPEG_VIDEO_H264_FMO_MAP_TYPE_WIPE_SCAN:
			अगर (p_h264->fmo_slice_grp > 2)
				p_h264->fmo_slice_grp = 2;
			ग_लिखोl(p_h264->fmo_chg_dir & 0x1,
				mfc_regs->e_h264_fmo_slice_grp_change_dir);
			/* the valid range is 0 ~ number of macroblocks -1 */
			ग_लिखोl(p_h264->fmo_chg_rate,
			mfc_regs->e_h264_fmo_slice_grp_change_rate_minus1);
			अवरोध;
		शेष:
			mfc_err("Unsupported map type for FMO: %d\n",
					p_h264->fmo_map_type);
			p_h264->fmo_map_type = 0;
			p_h264->fmo_slice_grp = 1;
			अवरोध;
		पूर्ण

		ग_लिखोl(p_h264->fmo_map_type,
				mfc_regs->e_h264_fmo_slice_grp_map_type);
		ग_लिखोl(p_h264->fmo_slice_grp - 1,
				mfc_regs->e_h264_fmo_num_slice_grp_minus1);
	पूर्ण अन्यथा अणु
		ग_लिखोl(0, mfc_regs->e_h264_fmo_num_slice_grp_minus1);
	पूर्ण

	mfc_debug_leave();

	वापस 0;
पूर्ण

अटल पूर्णांक s5p_mfc_set_enc_params_mpeg4(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	स्थिर काष्ठा s5p_mfc_regs *mfc_regs = dev->mfc_regs;
	काष्ठा s5p_mfc_enc_params *p = &ctx->enc_params;
	काष्ठा s5p_mfc_mpeg4_enc_params *p_mpeg4 = &p->codec.mpeg4;
	अचिन्हित पूर्णांक reg = 0;

	mfc_debug_enter();

	s5p_mfc_set_enc_params(ctx);

	/* pictype : number of B */
	reg = पढ़ोl(mfc_regs->e_gop_config);
	reg &= ~(0x3 << 16);
	reg |= ((p->num_b_frame & 0x3) << 16);
	ग_लिखोl(reg, mfc_regs->e_gop_config);

	/* profile & level */
	reg = 0;
	/** level */
	reg |= ((p_mpeg4->level & 0xFF) << 8);
	/** profile - 0 ~ 1 */
	reg |= p_mpeg4->profile & 0x3F;
	ग_लिखोl(reg, mfc_regs->e_picture_profile);

	/* rate control config. */
	reg = पढ़ोl(mfc_regs->e_rc_config);
	/** macroblock level rate control */
	reg &= ~(0x1 << 8);
	reg |= ((p->rc_mb & 0x1) << 8);
	ग_लिखोl(reg, mfc_regs->e_rc_config);

	/** frame QP */
	reg &= ~(0x3F);
	reg |= p_mpeg4->rc_frame_qp & 0x3F;
	ग_लिखोl(reg, mfc_regs->e_rc_config);

	/* max & min value of QP */
	reg = 0;
	/** max QP */
	reg |= ((p_mpeg4->rc_max_qp & 0x3F) << 8);
	/** min QP */
	reg |= p_mpeg4->rc_min_qp & 0x3F;
	ग_लिखोl(reg, mfc_regs->e_rc_qp_bound);

	/* other QPs */
	ग_लिखोl(0x0, mfc_regs->e_fixed_picture_qp);
	अगर (!p->rc_frame && !p->rc_mb) अणु
		reg = 0;
		reg |= ((p_mpeg4->rc_b_frame_qp & 0x3F) << 16);
		reg |= ((p_mpeg4->rc_p_frame_qp & 0x3F) << 8);
		reg |= p_mpeg4->rc_frame_qp & 0x3F;
		ग_लिखोl(reg, mfc_regs->e_fixed_picture_qp);
	पूर्ण

	/* frame rate */
	अगर (p->rc_frame && p->rc_framerate_num && p->rc_framerate_denom) अणु
		reg = 0;
		reg |= ((p->rc_framerate_num & 0xFFFF) << 16);
		reg |= p->rc_framerate_denom & 0xFFFF;
		ग_लिखोl(reg, mfc_regs->e_rc_frame_rate);
	पूर्ण

	/* vbv buffer size */
	अगर (p->frame_skip_mode ==
			V4L2_MPEG_MFC51_VIDEO_FRAME_SKIP_MODE_BUF_LIMIT) अणु
		ग_लिखोl(p->vbv_size & 0xFFFF, mfc_regs->e_vbv_buffer_size);

		अगर (p->rc_frame)
			ग_लिखोl(p->vbv_delay, mfc_regs->e_vbv_init_delay);
	पूर्ण

	/* Disable HEC */
	ग_लिखोl(0x0, mfc_regs->e_mpeg4_options);
	ग_लिखोl(0x0, mfc_regs->e_mpeg4_hec_period);

	mfc_debug_leave();

	वापस 0;
पूर्ण

अटल पूर्णांक s5p_mfc_set_enc_params_h263(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	स्थिर काष्ठा s5p_mfc_regs *mfc_regs = dev->mfc_regs;
	काष्ठा s5p_mfc_enc_params *p = &ctx->enc_params;
	काष्ठा s5p_mfc_mpeg4_enc_params *p_h263 = &p->codec.mpeg4;
	अचिन्हित पूर्णांक reg = 0;

	mfc_debug_enter();

	s5p_mfc_set_enc_params(ctx);

	/* profile & level */
	reg = 0;
	/** profile */
	reg |= (0x1 << 4);
	ग_लिखोl(reg, mfc_regs->e_picture_profile);

	/* rate control config. */
	reg = पढ़ोl(mfc_regs->e_rc_config);
	/** macroblock level rate control */
	reg &= ~(0x1 << 8);
	reg |= ((p->rc_mb & 0x1) << 8);
	ग_लिखोl(reg, mfc_regs->e_rc_config);

	/** frame QP */
	reg &= ~(0x3F);
	reg |= p_h263->rc_frame_qp & 0x3F;
	ग_लिखोl(reg, mfc_regs->e_rc_config);

	/* max & min value of QP */
	reg = 0;
	/** max QP */
	reg |= ((p_h263->rc_max_qp & 0x3F) << 8);
	/** min QP */
	reg |= p_h263->rc_min_qp & 0x3F;
	ग_लिखोl(reg, mfc_regs->e_rc_qp_bound);

	/* other QPs */
	ग_लिखोl(0x0, mfc_regs->e_fixed_picture_qp);
	अगर (!p->rc_frame && !p->rc_mb) अणु
		reg = 0;
		reg |= ((p_h263->rc_b_frame_qp & 0x3F) << 16);
		reg |= ((p_h263->rc_p_frame_qp & 0x3F) << 8);
		reg |= p_h263->rc_frame_qp & 0x3F;
		ग_लिखोl(reg, mfc_regs->e_fixed_picture_qp);
	पूर्ण

	/* frame rate */
	अगर (p->rc_frame && p->rc_framerate_num && p->rc_framerate_denom) अणु
		reg = 0;
		reg |= ((p->rc_framerate_num & 0xFFFF) << 16);
		reg |= p->rc_framerate_denom & 0xFFFF;
		ग_लिखोl(reg, mfc_regs->e_rc_frame_rate);
	पूर्ण

	/* vbv buffer size */
	अगर (p->frame_skip_mode ==
			V4L2_MPEG_MFC51_VIDEO_FRAME_SKIP_MODE_BUF_LIMIT) अणु
		ग_लिखोl(p->vbv_size & 0xFFFF, mfc_regs->e_vbv_buffer_size);

		अगर (p->rc_frame)
			ग_लिखोl(p->vbv_delay, mfc_regs->e_vbv_init_delay);
	पूर्ण

	mfc_debug_leave();

	वापस 0;
पूर्ण

अटल पूर्णांक s5p_mfc_set_enc_params_vp8(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	स्थिर काष्ठा s5p_mfc_regs *mfc_regs = dev->mfc_regs;
	काष्ठा s5p_mfc_enc_params *p = &ctx->enc_params;
	काष्ठा s5p_mfc_vp8_enc_params *p_vp8 = &p->codec.vp8;
	अचिन्हित पूर्णांक reg = 0;
	अचिन्हित पूर्णांक val = 0;

	mfc_debug_enter();

	s5p_mfc_set_enc_params(ctx);

	/* pictype : number of B */
	reg = पढ़ोl(mfc_regs->e_gop_config);
	reg &= ~(0x3 << 16);
	reg |= ((p->num_b_frame & 0x3) << 16);
	ग_लिखोl(reg, mfc_regs->e_gop_config);

	/* profile - 0 ~ 3 */
	reg = p_vp8->profile & 0x3;
	ग_लिखोl(reg, mfc_regs->e_picture_profile);

	/* rate control config. */
	reg = पढ़ोl(mfc_regs->e_rc_config);
	/** macroblock level rate control */
	reg &= ~(0x1 << 8);
	reg |= ((p->rc_mb & 0x1) << 8);
	ग_लिखोl(reg, mfc_regs->e_rc_config);

	/* frame rate */
	अगर (p->rc_frame && p->rc_framerate_num && p->rc_framerate_denom) अणु
		reg = 0;
		reg |= ((p->rc_framerate_num & 0xFFFF) << 16);
		reg |= p->rc_framerate_denom & 0xFFFF;
		ग_लिखोl(reg, mfc_regs->e_rc_frame_rate);
	पूर्ण

	/* frame QP */
	reg &= ~(0x7F);
	reg |= p_vp8->rc_frame_qp & 0x7F;
	ग_लिखोl(reg, mfc_regs->e_rc_config);

	/* other QPs */
	ग_लिखोl(0x0, mfc_regs->e_fixed_picture_qp);
	अगर (!p->rc_frame && !p->rc_mb) अणु
		reg = 0;
		reg |= ((p_vp8->rc_p_frame_qp & 0x7F) << 8);
		reg |= p_vp8->rc_frame_qp & 0x7F;
		ग_लिखोl(reg, mfc_regs->e_fixed_picture_qp);
	पूर्ण

	/* max QP */
	reg = ((p_vp8->rc_max_qp & 0x7F) << 8);
	/* min QP */
	reg |= p_vp8->rc_min_qp & 0x7F;
	ग_लिखोl(reg, mfc_regs->e_rc_qp_bound);

	/* vbv buffer size */
	अगर (p->frame_skip_mode ==
			V4L2_MPEG_MFC51_VIDEO_FRAME_SKIP_MODE_BUF_LIMIT) अणु
		ग_लिखोl(p->vbv_size & 0xFFFF, mfc_regs->e_vbv_buffer_size);

		अगर (p->rc_frame)
			ग_लिखोl(p->vbv_delay, mfc_regs->e_vbv_init_delay);
	पूर्ण

	/* VP8 specअगरic params */
	reg = 0;
	reg |= (p_vp8->imd_4x4 & 0x1) << 10;
	चयन (p_vp8->num_partitions) अणु
	हाल V4L2_CID_MPEG_VIDEO_VPX_1_PARTITION:
		val = 0;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_VPX_2_PARTITIONS:
		val = 2;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_VPX_4_PARTITIONS:
		val = 4;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_VPX_8_PARTITIONS:
		val = 8;
		अवरोध;
	पूर्ण
	reg |= (val & 0xF) << 3;
	reg |= (p_vp8->num_ref & 0x2);
	ग_लिखोl(reg, mfc_regs->e_vp8_options);

	mfc_debug_leave();

	वापस 0;
पूर्ण

अटल पूर्णांक s5p_mfc_set_enc_params_hevc(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	स्थिर काष्ठा s5p_mfc_regs *mfc_regs = dev->mfc_regs;
	काष्ठा s5p_mfc_enc_params *p = &ctx->enc_params;
	काष्ठा s5p_mfc_hevc_enc_params *p_hevc = &p->codec.hevc;
	अचिन्हित पूर्णांक reg = 0;
	पूर्णांक i;

	mfc_debug_enter();

	s5p_mfc_set_enc_params(ctx);

	/* pictype : number of B */
	reg = पढ़ोl(mfc_regs->e_gop_config);
	/* num_b_frame - 0 ~ 2 */
	reg &= ~(0x3 << 16);
	reg |= (p->num_b_frame << 16);
	ग_लिखोl(reg, mfc_regs->e_gop_config);

	/* UHD encoding हाल */
	अगर ((ctx->img_width == 3840) && (ctx->img_height == 2160)) अणु
		p_hevc->level = 51;
		p_hevc->tier = 0;
	/* this tier can be changed */
	पूर्ण

	/* tier & level */
	reg = 0;
	/* profile */
	reg |= p_hevc->profile & 0x3;
	/* level */
	reg &= ~(0xFF << 8);
	reg |= (p_hevc->level << 8);
	/* tier - 0 ~ 1 */
	reg |= (p_hevc->tier << 16);
	ग_लिखोl(reg, mfc_regs->e_picture_profile);

	चयन (p_hevc->loopfilter) अणु
	हाल V4L2_MPEG_VIDEO_HEVC_LOOP_FILTER_MODE_DISABLED:
		p_hevc->loopfilter_disable = 1;
		अवरोध;
	हाल V4L2_MPEG_VIDEO_HEVC_LOOP_FILTER_MODE_ENABLED:
		p_hevc->loopfilter_disable = 0;
		p_hevc->loopfilter_across = 1;
		अवरोध;
	हाल V4L2_MPEG_VIDEO_HEVC_LOOP_FILTER_MODE_DISABLED_AT_SLICE_BOUNDARY:
		p_hevc->loopfilter_disable = 0;
		p_hevc->loopfilter_across = 0;
		अवरोध;
	पूर्ण

	/* max partition depth */
	reg = 0;
	reg |= (p_hevc->max_partition_depth & 0x1);
	reg |= (p_hevc->num_refs_क्रम_p-1) << 2;
	reg |= (p_hevc->refreshtype & 0x3) << 3;
	reg |= (p_hevc->स्थिर_पूर्णांकra_period_enable & 0x1) << 5;
	reg |= (p_hevc->lossless_cu_enable & 0x1) << 6;
	reg |= (p_hevc->wavefront_enable & 0x1) << 7;
	reg |= (p_hevc->loopfilter_disable & 0x1) << 8;
	reg |= (p_hevc->loopfilter_across & 0x1) << 9;
	reg |= (p_hevc->enable_ltr & 0x1) << 10;
	reg |= (p_hevc->hier_qp_enable & 0x1) << 11;
	reg |= (p_hevc->general_pb_enable & 0x1) << 13;
	reg |= (p_hevc->temporal_id_enable & 0x1) << 14;
	reg |= (p_hevc->strong_पूर्णांकra_smooth & 0x1) << 15;
	reg |= (p_hevc->पूर्णांकra_pu_split_disable & 0x1) << 16;
	reg |= (p_hevc->पंचांगv_prediction_disable & 0x1) << 17;
	reg |= (p_hevc->max_num_merge_mv & 0x7) << 18;
	reg |= (p_hevc->encoding_nostartcode_enable & 0x1) << 23;
	reg |= (p_hevc->prepend_sps_pps_to_idr << 26);

	ग_लिखोl(reg, mfc_regs->e_hevc_options);
	/* refresh period */
	अगर (p_hevc->refreshtype) अणु
		reg = 0;
		reg |= (p_hevc->refreshperiod & 0xFFFF);
		ग_लिखोl(reg, mfc_regs->e_hevc_refresh_period);
	पूर्ण
	/* loop filter setting */
	अगर (!(p_hevc->loopfilter_disable & 0x1)) अणु
		reg = 0;
		reg |= (p_hevc->lf_beta_offset_भाग2);
		ग_लिखोl(reg, mfc_regs->e_hevc_lf_beta_offset_भाग2);
		reg = 0;
		reg |= (p_hevc->lf_tc_offset_भाग2);
		ग_लिखोl(reg, mfc_regs->e_hevc_lf_tc_offset_भाग2);
	पूर्ण
	/* hier qp enable */
	अगर (p_hevc->num_hier_layer) अणु
		reg = 0;
		reg |= (p_hevc->hier_qp_type & 0x1) << 0x3;
		reg |= p_hevc->num_hier_layer & 0x7;
		ग_लिखोl(reg, mfc_regs->e_num_t_layer);
		/* QP value क्रम each layer */
		अगर (p_hevc->hier_qp_enable) अणु
			क्रम (i = 0; i < 7; i++)
				ग_लिखोl(p_hevc->hier_qp_layer[i],
					mfc_regs->e_hier_qp_layer0 + i * 4);
		पूर्ण
		अगर (p->rc_frame) अणु
			क्रम (i = 0; i < 7; i++)
				ग_लिखोl(p_hevc->hier_bit_layer[i],
						mfc_regs->e_hier_bit_rate_layer0
						+ i * 4);
		पूर्ण
	पूर्ण

	/* rate control config. */
	reg = पढ़ोl(mfc_regs->e_rc_config);
	/* macroblock level rate control */
	reg &= ~(0x1 << 8);
	reg |= (p->rc_mb << 8);
	ग_लिखोl(reg, mfc_regs->e_rc_config);
	/* frame QP */
	reg &= ~(0xFF);
	reg |= p_hevc->rc_frame_qp;
	ग_लिखोl(reg, mfc_regs->e_rc_config);

	/* frame rate */
	अगर (p->rc_frame) अणु
		reg = 0;
		reg &= ~(0xFFFF << 16);
		reg |= ((p_hevc->rc_framerate) << 16);
		reg &= ~(0xFFFF);
		reg |= FRAME_DELTA_DEFAULT;
		ग_लिखोl(reg, mfc_regs->e_rc_frame_rate);
	पूर्ण

	/* max & min value of QP */
	reg = 0;
	/* max QP */
	reg &= ~(0xFF << 8);
	reg |= (p_hevc->rc_max_qp << 8);
	/* min QP */
	reg &= ~(0xFF);
	reg |= p_hevc->rc_min_qp;
	ग_लिखोl(reg, mfc_regs->e_rc_qp_bound);

	ग_लिखोl(0x0, mfc_regs->e_fixed_picture_qp);
	अगर (!p->rc_frame && !p->rc_mb) अणु
		reg = 0;
		reg &= ~(0xFF << 16);
		reg |= (p_hevc->rc_b_frame_qp << 16);
		reg &= ~(0xFF << 8);
		reg |= (p_hevc->rc_p_frame_qp << 8);
		reg &= ~(0xFF);
		reg |= p_hevc->rc_frame_qp;
		ग_लिखोl(reg, mfc_regs->e_fixed_picture_qp);
	पूर्ण
	mfc_debug_leave();

	वापस 0;
पूर्ण

/* Initialize decoding */
अटल पूर्णांक s5p_mfc_init_decode_v6(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	स्थिर काष्ठा s5p_mfc_regs *mfc_regs = dev->mfc_regs;
	अचिन्हित पूर्णांक reg = 0;
	पूर्णांक fmo_aso_ctrl = 0;

	mfc_debug_enter();
	mfc_debug(2, "InstNo: %d/%d\n", ctx->inst_no,
			S5P_FIMV_CH_SEQ_HEADER_V6);
	mfc_debug(2, "BUFs: %08x %08x %08x\n",
		  पढ़ोl(mfc_regs->d_cpb_buffer_addr),
		  पढ़ोl(mfc_regs->d_cpb_buffer_addr),
		  पढ़ोl(mfc_regs->d_cpb_buffer_addr));

	/* FMO_ASO_CTRL - 0: Enable, 1: Disable */
	reg |= (fmo_aso_ctrl << S5P_FIMV_D_OPT_FMO_ASO_CTRL_MASK_V6);

	अगर (ctx->display_delay_enable) अणु
		reg |= (0x1 << S5P_FIMV_D_OPT_DDELAY_EN_SHIFT_V6);
		ग_लिखोl(ctx->display_delay, mfc_regs->d_display_delay);
	पूर्ण

	अगर (IS_MFCV7_PLUS(dev) || IS_MFCV6_V2(dev)) अणु
		ग_लिखोl(reg, mfc_regs->d_dec_options);
		reg = 0;
	पूर्ण

	/* Setup loop filter, क्रम decoding this is only valid क्रम MPEG4 */
	अगर (ctx->codec_mode == S5P_MFC_CODEC_MPEG4_DEC) अणु
		mfc_debug(2, "Set loop filter to: %d\n",
				ctx->loop_filter_mpeg4);
		reg |= (ctx->loop_filter_mpeg4 <<
				S5P_FIMV_D_OPT_LF_CTRL_SHIFT_V6);
	पूर्ण
	अगर (ctx->dst_fmt->fourcc == V4L2_PIX_FMT_NV12MT_16X16)
		reg |= (0x1 << S5P_FIMV_D_OPT_TILE_MODE_SHIFT_V6);

	अगर (IS_MFCV7_PLUS(dev) || IS_MFCV6_V2(dev))
		ग_लिखोl(reg, mfc_regs->d_init_buffer_options);
	अन्यथा
		ग_लिखोl(reg, mfc_regs->d_dec_options);

	/* 0: NV12(CbCr), 1: NV21(CrCb) */
	अगर (ctx->dst_fmt->fourcc == V4L2_PIX_FMT_NV21M)
		ग_लिखोl(0x1, mfc_regs->pixel_क्रमmat);
	अन्यथा
		ग_लिखोl(0x0, mfc_regs->pixel_क्रमmat);


	/* sei parse */
	ग_लिखोl(ctx->sei_fp_parse & 0x1, mfc_regs->d_sei_enable);

	ग_लिखोl(ctx->inst_no, mfc_regs->instance_id);
	s5p_mfc_hw_call(dev->mfc_cmds, cmd_host2risc, dev,
			S5P_FIMV_CH_SEQ_HEADER_V6, शून्य);

	mfc_debug_leave();
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम s5p_mfc_set_flush(काष्ठा s5p_mfc_ctx *ctx, पूर्णांक flush)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	स्थिर काष्ठा s5p_mfc_regs *mfc_regs = dev->mfc_regs;

	अगर (flush) अणु
		dev->curr_ctx = ctx->num;
		ग_लिखोl(ctx->inst_no, mfc_regs->instance_id);
		s5p_mfc_hw_call(dev->mfc_cmds, cmd_host2risc, dev,
				S5P_FIMV_H2R_CMD_FLUSH_V6, शून्य);
	पूर्ण
पूर्ण

/* Decode a single frame */
अटल पूर्णांक s5p_mfc_decode_one_frame_v6(काष्ठा s5p_mfc_ctx *ctx,
			क्रमागत s5p_mfc_decode_arg last_frame)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	स्थिर काष्ठा s5p_mfc_regs *mfc_regs = dev->mfc_regs;

	ग_लिखोl(ctx->dec_dst_flag, mfc_regs->d_available_dpb_flag_lower);
	ग_लिखोl(ctx->slice_पूर्णांकerface & 0x1, mfc_regs->d_slice_अगर_enable);

	ग_लिखोl(ctx->inst_no, mfc_regs->instance_id);
	/* Issue dअगरferent commands to instance basing on whether it
	 * is the last frame or not. */
	चयन (last_frame) अणु
	हाल 0:
		s5p_mfc_hw_call(dev->mfc_cmds, cmd_host2risc, dev,
				S5P_FIMV_CH_FRAME_START_V6, शून्य);
		अवरोध;
	हाल 1:
		s5p_mfc_hw_call(dev->mfc_cmds, cmd_host2risc, dev,
				S5P_FIMV_CH_LAST_FRAME_V6, शून्य);
		अवरोध;
	शेष:
		mfc_err("Unsupported last frame arg.\n");
		वापस -EINVAL;
	पूर्ण

	mfc_debug(2, "Decoding a usual frame.\n");
	वापस 0;
पूर्ण

अटल पूर्णांक s5p_mfc_init_encode_v6(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	स्थिर काष्ठा s5p_mfc_regs *mfc_regs = dev->mfc_regs;

	अगर (ctx->codec_mode == S5P_MFC_CODEC_H264_ENC)
		s5p_mfc_set_enc_params_h264(ctx);
	अन्यथा अगर (ctx->codec_mode == S5P_MFC_CODEC_MPEG4_ENC)
		s5p_mfc_set_enc_params_mpeg4(ctx);
	अन्यथा अगर (ctx->codec_mode == S5P_MFC_CODEC_H263_ENC)
		s5p_mfc_set_enc_params_h263(ctx);
	अन्यथा अगर (ctx->codec_mode == S5P_MFC_CODEC_VP8_ENC)
		s5p_mfc_set_enc_params_vp8(ctx);
	अन्यथा अगर (ctx->codec_mode == S5P_FIMV_CODEC_HEVC_ENC)
		s5p_mfc_set_enc_params_hevc(ctx);
	अन्यथा अणु
		mfc_err("Unknown codec for encoding (%x).\n",
			ctx->codec_mode);
		वापस -EINVAL;
	पूर्ण

	/* Set stride lengths क्रम v7 & above */
	अगर (IS_MFCV7_PLUS(dev)) अणु
		ग_लिखोl(ctx->img_width, mfc_regs->e_source_first_plane_stride);
		ग_लिखोl(ctx->img_width, mfc_regs->e_source_second_plane_stride);
	पूर्ण

	ग_लिखोl(ctx->inst_no, mfc_regs->instance_id);
	s5p_mfc_hw_call(dev->mfc_cmds, cmd_host2risc, dev,
			S5P_FIMV_CH_SEQ_HEADER_V6, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक s5p_mfc_h264_set_aso_slice_order_v6(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	स्थिर काष्ठा s5p_mfc_regs *mfc_regs = dev->mfc_regs;
	काष्ठा s5p_mfc_enc_params *p = &ctx->enc_params;
	काष्ठा s5p_mfc_h264_enc_params *p_h264 = &p->codec.h264;
	पूर्णांक i;

	अगर (p_h264->aso) अणु
		क्रम (i = 0; i < ARRAY_SIZE(p_h264->aso_slice_order); i++) अणु
			ग_लिखोl(p_h264->aso_slice_order[i],
				mfc_regs->e_h264_aso_slice_order_0 + i * 4);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* Encode a single frame */
अटल पूर्णांक s5p_mfc_encode_one_frame_v6(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	स्थिर काष्ठा s5p_mfc_regs *mfc_regs = dev->mfc_regs;
	पूर्णांक cmd;

	mfc_debug(2, "++\n");

	/* memory काष्ठाure cur. frame */

	अगर (ctx->codec_mode == S5P_MFC_CODEC_H264_ENC)
		s5p_mfc_h264_set_aso_slice_order_v6(ctx);

	s5p_mfc_set_slice_mode(ctx);

	अगर (ctx->state != MFCINST_FINISHING)
		cmd = S5P_FIMV_CH_FRAME_START_V6;
	अन्यथा
		cmd = S5P_FIMV_CH_LAST_FRAME_V6;

	ग_लिखोl(ctx->inst_no, mfc_regs->instance_id);
	s5p_mfc_hw_call(dev->mfc_cmds, cmd_host2risc, dev, cmd, शून्य);

	mfc_debug(2, "--\n");

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम s5p_mfc_run_dec_last_frames(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;

	s5p_mfc_set_dec_stream_buffer_v6(ctx, 0, 0, 0);
	dev->curr_ctx = ctx->num;
	s5p_mfc_decode_one_frame_v6(ctx, MFC_DEC_LAST_FRAME);
पूर्ण

अटल अंतरभूत पूर्णांक s5p_mfc_run_dec_frame(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	काष्ठा s5p_mfc_buf *temp_vb;
	पूर्णांक last_frame = 0;

	अगर (ctx->state == MFCINST_FINISHING) अणु
		last_frame = MFC_DEC_LAST_FRAME;
		s5p_mfc_set_dec_stream_buffer_v6(ctx, 0, 0, 0);
		dev->curr_ctx = ctx->num;
		s5p_mfc_clean_ctx_पूर्णांक_flags(ctx);
		s5p_mfc_decode_one_frame_v6(ctx, last_frame);
		वापस 0;
	पूर्ण

	/* Frames are being decoded */
	अगर (list_empty(&ctx->src_queue)) अणु
		mfc_debug(2, "No src buffers.\n");
		वापस -EAGAIN;
	पूर्ण
	/* Get the next source buffer */
	temp_vb = list_entry(ctx->src_queue.next, काष्ठा s5p_mfc_buf, list);
	temp_vb->flags |= MFC_BUF_FLAG_USED;
	s5p_mfc_set_dec_stream_buffer_v6(ctx,
		vb2_dma_contig_plane_dma_addr(&temp_vb->b->vb2_buf, 0),
			ctx->consumed_stream,
			temp_vb->b->vb2_buf.planes[0].bytesused);

	dev->curr_ctx = ctx->num;
	अगर (temp_vb->b->vb2_buf.planes[0].bytesused == 0) अणु
		last_frame = 1;
		mfc_debug(2, "Setting ctx->state to FINISHING\n");
		ctx->state = MFCINST_FINISHING;
	पूर्ण
	s5p_mfc_decode_one_frame_v6(ctx, last_frame);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक s5p_mfc_run_enc_frame(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	काष्ठा s5p_mfc_buf *dst_mb;
	काष्ठा s5p_mfc_buf *src_mb;
	अचिन्हित दीर्घ src_y_addr, src_c_addr, dst_addr;
	/*
	अचिन्हित पूर्णांक src_y_size, src_c_size;
	*/
	अचिन्हित पूर्णांक dst_size;

	अगर (list_empty(&ctx->src_queue) && ctx->state != MFCINST_FINISHING) अणु
		mfc_debug(2, "no src buffers.\n");
		वापस -EAGAIN;
	पूर्ण

	अगर (list_empty(&ctx->dst_queue)) अणु
		mfc_debug(2, "no dst buffers.\n");
		वापस -EAGAIN;
	पूर्ण

	अगर (list_empty(&ctx->src_queue)) अणु
		/* send null frame */
		s5p_mfc_set_enc_frame_buffer_v6(ctx, 0, 0);
		src_mb = शून्य;
	पूर्ण अन्यथा अणु
		src_mb = list_entry(ctx->src_queue.next, काष्ठा s5p_mfc_buf, list);
		src_mb->flags |= MFC_BUF_FLAG_USED;
		अगर (src_mb->b->vb2_buf.planes[0].bytesused == 0) अणु
			s5p_mfc_set_enc_frame_buffer_v6(ctx, 0, 0);
			ctx->state = MFCINST_FINISHING;
		पूर्ण अन्यथा अणु
			src_y_addr = vb2_dma_contig_plane_dma_addr(&src_mb->b->vb2_buf, 0);
			src_c_addr = vb2_dma_contig_plane_dma_addr(&src_mb->b->vb2_buf, 1);

			mfc_debug(2, "enc src y addr: 0x%08lx\n", src_y_addr);
			mfc_debug(2, "enc src c addr: 0x%08lx\n", src_c_addr);

			s5p_mfc_set_enc_frame_buffer_v6(ctx, src_y_addr, src_c_addr);
			अगर (src_mb->flags & MFC_BUF_FLAG_EOS)
				ctx->state = MFCINST_FINISHING;
		पूर्ण
	पूर्ण

	dst_mb = list_entry(ctx->dst_queue.next, काष्ठा s5p_mfc_buf, list);
	dst_mb->flags |= MFC_BUF_FLAG_USED;
	dst_addr = vb2_dma_contig_plane_dma_addr(&dst_mb->b->vb2_buf, 0);
	dst_size = vb2_plane_size(&dst_mb->b->vb2_buf, 0);

	s5p_mfc_set_enc_stream_buffer_v6(ctx, dst_addr, dst_size);

	dev->curr_ctx = ctx->num;
	s5p_mfc_encode_one_frame_v6(ctx);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम s5p_mfc_run_init_dec(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	काष्ठा s5p_mfc_buf *temp_vb;

	/* Initializing decoding - parsing header */
	mfc_debug(2, "Preparing to init decoding.\n");
	temp_vb = list_entry(ctx->src_queue.next, काष्ठा s5p_mfc_buf, list);
	mfc_debug(2, "Header size: %d\n", temp_vb->b->vb2_buf.planes[0].bytesused);
	s5p_mfc_set_dec_stream_buffer_v6(ctx,
		vb2_dma_contig_plane_dma_addr(&temp_vb->b->vb2_buf, 0), 0,
			temp_vb->b->vb2_buf.planes[0].bytesused);
	dev->curr_ctx = ctx->num;
	s5p_mfc_init_decode_v6(ctx);
पूर्ण

अटल अंतरभूत व्योम s5p_mfc_run_init_enc(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	काष्ठा s5p_mfc_buf *dst_mb;
	अचिन्हित दीर्घ dst_addr;
	अचिन्हित पूर्णांक dst_size;

	dst_mb = list_entry(ctx->dst_queue.next, काष्ठा s5p_mfc_buf, list);
	dst_addr = vb2_dma_contig_plane_dma_addr(&dst_mb->b->vb2_buf, 0);
	dst_size = vb2_plane_size(&dst_mb->b->vb2_buf, 0);
	s5p_mfc_set_enc_stream_buffer_v6(ctx, dst_addr, dst_size);
	dev->curr_ctx = ctx->num;
	s5p_mfc_init_encode_v6(ctx);
पूर्ण

अटल अंतरभूत पूर्णांक s5p_mfc_run_init_dec_buffers(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	पूर्णांक ret;
	/* Header was parsed now start processing
	 * First set the output frame buffers
	 * s5p_mfc_alloc_dec_buffers(ctx); */

	अगर (ctx->capture_state != QUEUE_BUFS_MMAPED) अणु
		mfc_err("It seems that not all destination buffers were\n"
			"mmapped.MFC requires that all destination are mmapped\n"
			"before starting processing.\n");
		वापस -EAGAIN;
	पूर्ण

	dev->curr_ctx = ctx->num;
	ret = s5p_mfc_set_dec_frame_buffer_v6(ctx);
	अगर (ret) अणु
		mfc_err("Failed to alloc frame mem.\n");
		ctx->state = MFCINST_ERROR;
	पूर्ण
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक s5p_mfc_run_init_enc_buffers(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	पूर्णांक ret;

	dev->curr_ctx = ctx->num;
	ret = s5p_mfc_set_enc_ref_buffer_v6(ctx);
	अगर (ret) अणु
		mfc_err("Failed to alloc frame mem.\n");
		ctx->state = MFCINST_ERROR;
	पूर्ण
	वापस ret;
पूर्ण

/* Try running an operation on hardware */
अटल व्योम s5p_mfc_try_run_v6(काष्ठा s5p_mfc_dev *dev)
अणु
	काष्ठा s5p_mfc_ctx *ctx;
	पूर्णांक new_ctx;
	अचिन्हित पूर्णांक ret = 0;

	mfc_debug(1, "Try run dev: %p\n", dev);

	/* Check whether hardware is not running */
	अगर (test_and_set_bit(0, &dev->hw_lock) != 0) अणु
		/* This is perfectly ok, the scheduled ctx should रुको */
		mfc_debug(1, "Couldn't lock HW.\n");
		वापस;
	पूर्ण

	/* Choose the context to run */
	new_ctx = s5p_mfc_get_new_ctx(dev);
	अगर (new_ctx < 0) अणु
		/* No contexts to run */
		अगर (test_and_clear_bit(0, &dev->hw_lock) == 0) अणु
			mfc_err("Failed to unlock hardware.\n");
			वापस;
		पूर्ण

		mfc_debug(1, "No ctx is scheduled to be run.\n");
		वापस;
	पूर्ण

	mfc_debug(1, "New context: %d\n", new_ctx);
	ctx = dev->ctx[new_ctx];
	mfc_debug(1, "Setting new context to %p\n", ctx);
	/* Got context to run in ctx */
	mfc_debug(1, "ctx->dst_queue_cnt=%d ctx->dpb_count=%d ctx->src_queue_cnt=%d\n",
		ctx->dst_queue_cnt, ctx->pb_count, ctx->src_queue_cnt);
	mfc_debug(1, "ctx->state=%d\n", ctx->state);
	/* Last frame has alपढ़ोy been sent to MFC
	 * Now obtaining frames from MFC buffer */

	s5p_mfc_घड़ी_on();
	s5p_mfc_clean_ctx_पूर्णांक_flags(ctx);

	अगर (ctx->type == MFCINST_DECODER) अणु
		चयन (ctx->state) अणु
		हाल MFCINST_FINISHING:
			s5p_mfc_run_dec_last_frames(ctx);
			अवरोध;
		हाल MFCINST_RUNNING:
			ret = s5p_mfc_run_dec_frame(ctx);
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
			अवरोध;
		हाल MFCINST_FLUSH:
			s5p_mfc_set_flush(ctx, ctx->dpb_flush_flag);
			अवरोध;
		हाल MFCINST_RES_CHANGE_INIT:
			s5p_mfc_run_dec_last_frames(ctx);
			अवरोध;
		हाल MFCINST_RES_CHANGE_FLUSH:
			s5p_mfc_run_dec_last_frames(ctx);
			अवरोध;
		हाल MFCINST_RES_CHANGE_END:
			mfc_debug(2, "Finished remaining frames after resolution change.\n");
			ctx->capture_state = QUEUE_FREE;
			mfc_debug(2, "Will re-init the codec`.\n");
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
		हाल MFCINST_HEAD_PRODUCED:
			ret = s5p_mfc_run_init_enc_buffers(ctx);
			अवरोध;
		शेष:
			ret = -EAGAIN;
		पूर्ण
	पूर्ण अन्यथा अणु
		mfc_err("invalid context type: %d\n", ctx->type);
		ret = -EAGAIN;
	पूर्ण

	अगर (ret) अणु
		/* Free hardware lock */
		अगर (test_and_clear_bit(0, &dev->hw_lock) == 0)
			mfc_err("Failed to unlock hardware.\n");

		/* This is in deed imporant, as no operation has been
		 * scheduled, reduce the घड़ी count as no one will
		 * ever करो this, because no पूर्णांकerrupt related to this try_run
		 * will ever come from hardware. */
		s5p_mfc_घड़ी_off();
	पूर्ण
पूर्ण

अटल व्योम s5p_mfc_clear_पूर्णांक_flags_v6(काष्ठा s5p_mfc_dev *dev)
अणु
	स्थिर काष्ठा s5p_mfc_regs *mfc_regs = dev->mfc_regs;
	ग_लिखोl(0, mfc_regs->risc2host_command);
	ग_लिखोl(0, mfc_regs->risc2host_पूर्णांक);
पूर्ण

अटल अचिन्हित पूर्णांक
s5p_mfc_पढ़ो_info_v6(काष्ठा s5p_mfc_ctx *ctx, अचिन्हित दीर्घ ofs)
अणु
	पूर्णांक ret;

	s5p_mfc_घड़ी_on();
	ret = पढ़ोl((व्योम __iomem *)ofs);
	s5p_mfc_घड़ी_off();

	वापस ret;
पूर्ण

अटल पूर्णांक s5p_mfc_get_dspl_y_adr_v6(काष्ठा s5p_mfc_dev *dev)
अणु
	वापस पढ़ोl(dev->mfc_regs->d_display_first_plane_addr);
पूर्ण

अटल पूर्णांक s5p_mfc_get_dec_y_adr_v6(काष्ठा s5p_mfc_dev *dev)
अणु
	वापस पढ़ोl(dev->mfc_regs->d_decoded_first_plane_addr);
पूर्ण

अटल पूर्णांक s5p_mfc_get_dspl_status_v6(काष्ठा s5p_mfc_dev *dev)
अणु
	वापस पढ़ोl(dev->mfc_regs->d_display_status);
पूर्ण

अटल पूर्णांक s5p_mfc_get_dec_status_v6(काष्ठा s5p_mfc_dev *dev)
अणु
	वापस पढ़ोl(dev->mfc_regs->d_decoded_status);
पूर्ण

अटल पूर्णांक s5p_mfc_get_dec_frame_type_v6(काष्ठा s5p_mfc_dev *dev)
अणु
	वापस पढ़ोl(dev->mfc_regs->d_decoded_frame_type) &
		S5P_FIMV_DECODE_FRAME_MASK_V6;
पूर्ण

अटल पूर्णांक s5p_mfc_get_disp_frame_type_v6(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	वापस पढ़ोl(dev->mfc_regs->d_display_frame_type) &
		S5P_FIMV_DECODE_FRAME_MASK_V6;
पूर्ण

अटल पूर्णांक s5p_mfc_get_consumed_stream_v6(काष्ठा s5p_mfc_dev *dev)
अणु
	वापस पढ़ोl(dev->mfc_regs->d_decoded_nal_size);
पूर्ण

अटल पूर्णांक s5p_mfc_get_पूर्णांक_reason_v6(काष्ठा s5p_mfc_dev *dev)
अणु
	वापस पढ़ोl(dev->mfc_regs->risc2host_command) &
		S5P_FIMV_RISC2HOST_CMD_MASK;
पूर्ण

अटल पूर्णांक s5p_mfc_get_पूर्णांक_err_v6(काष्ठा s5p_mfc_dev *dev)
अणु
	वापस पढ़ोl(dev->mfc_regs->error_code);
पूर्ण

अटल पूर्णांक s5p_mfc_err_dec_v6(अचिन्हित पूर्णांक err)
अणु
	वापस (err & S5P_FIMV_ERR_DEC_MASK_V6) >> S5P_FIMV_ERR_DEC_SHIFT_V6;
पूर्ण

अटल पूर्णांक s5p_mfc_get_img_width_v6(काष्ठा s5p_mfc_dev *dev)
अणु
	वापस पढ़ोl(dev->mfc_regs->d_display_frame_width);
पूर्ण

अटल पूर्णांक s5p_mfc_get_img_height_v6(काष्ठा s5p_mfc_dev *dev)
अणु
	वापस पढ़ोl(dev->mfc_regs->d_display_frame_height);
पूर्ण

अटल पूर्णांक s5p_mfc_get_dpb_count_v6(काष्ठा s5p_mfc_dev *dev)
अणु
	वापस पढ़ोl(dev->mfc_regs->d_min_num_dpb);
पूर्ण

अटल पूर्णांक s5p_mfc_get_mv_count_v6(काष्ठा s5p_mfc_dev *dev)
अणु
	वापस पढ़ोl(dev->mfc_regs->d_min_num_mv);
पूर्ण

अटल पूर्णांक s5p_mfc_get_min_scratch_buf_size(काष्ठा s5p_mfc_dev *dev)
अणु
	वापस पढ़ोl(dev->mfc_regs->d_min_scratch_buffer_size);
पूर्ण

अटल पूर्णांक s5p_mfc_get_e_min_scratch_buf_size(काष्ठा s5p_mfc_dev *dev)
अणु
	वापस पढ़ोl(dev->mfc_regs->e_min_scratch_buffer_size);
पूर्ण

अटल पूर्णांक s5p_mfc_get_inst_no_v6(काष्ठा s5p_mfc_dev *dev)
अणु
	वापस पढ़ोl(dev->mfc_regs->ret_instance_id);
पूर्ण

अटल पूर्णांक s5p_mfc_get_enc_dpb_count_v6(काष्ठा s5p_mfc_dev *dev)
अणु
	वापस पढ़ोl(dev->mfc_regs->e_num_dpb);
पूर्ण

अटल पूर्णांक s5p_mfc_get_enc_strm_size_v6(काष्ठा s5p_mfc_dev *dev)
अणु
	वापस पढ़ोl(dev->mfc_regs->e_stream_size);
पूर्ण

अटल पूर्णांक s5p_mfc_get_enc_slice_type_v6(काष्ठा s5p_mfc_dev *dev)
अणु
	वापस पढ़ोl(dev->mfc_regs->e_slice_type);
पूर्ण

अटल अचिन्हित पूर्णांक s5p_mfc_get_pic_type_top_v6(काष्ठा s5p_mfc_ctx *ctx)
अणु
	वापस s5p_mfc_पढ़ो_info_v6(ctx,
		(__क्रमce अचिन्हित दीर्घ) ctx->dev->mfc_regs->d_ret_picture_tag_top);
पूर्ण

अटल अचिन्हित पूर्णांक s5p_mfc_get_pic_type_bot_v6(काष्ठा s5p_mfc_ctx *ctx)
अणु
	वापस s5p_mfc_पढ़ो_info_v6(ctx,
		(__क्रमce अचिन्हित दीर्घ) ctx->dev->mfc_regs->d_ret_picture_tag_bot);
पूर्ण

अटल अचिन्हित पूर्णांक s5p_mfc_get_crop_info_h_v6(काष्ठा s5p_mfc_ctx *ctx)
अणु
	वापस s5p_mfc_पढ़ो_info_v6(ctx,
		(__क्रमce अचिन्हित दीर्घ) ctx->dev->mfc_regs->d_display_crop_info1);
पूर्ण

अटल अचिन्हित पूर्णांक s5p_mfc_get_crop_info_v_v6(काष्ठा s5p_mfc_ctx *ctx)
अणु
	वापस s5p_mfc_पढ़ो_info_v6(ctx,
		(__क्रमce अचिन्हित दीर्घ) ctx->dev->mfc_regs->d_display_crop_info2);
पूर्ण

अटल काष्ठा s5p_mfc_regs mfc_regs;

/* Initialize रेजिस्टरs क्रम MFC v6 onwards */
स्थिर काष्ठा s5p_mfc_regs *s5p_mfc_init_regs_v6_plus(काष्ठा s5p_mfc_dev *dev)
अणु
	स_रखो(&mfc_regs, 0, माप(mfc_regs));

#घोषणा S5P_MFC_REG_ADDR(dev, reg) ((dev)->regs_base + (reg))
#घोषणा R(m, r) mfc_regs.m = S5P_MFC_REG_ADDR(dev, r)
	/* codec common रेजिस्टरs */
	R(risc_on, S5P_FIMV_RISC_ON_V6);
	R(risc2host_पूर्णांक, S5P_FIMV_RISC2HOST_INT_V6);
	R(host2risc_पूर्णांक, S5P_FIMV_HOST2RISC_INT_V6);
	R(risc_base_address, S5P_FIMV_RISC_BASE_ADDRESS_V6);
	R(mfc_reset, S5P_FIMV_MFC_RESET_V6);
	R(host2risc_command, S5P_FIMV_HOST2RISC_CMD_V6);
	R(risc2host_command, S5P_FIMV_RISC2HOST_CMD_V6);
	R(firmware_version, S5P_FIMV_FW_VERSION_V6);
	R(instance_id, S5P_FIMV_INSTANCE_ID_V6);
	R(codec_type, S5P_FIMV_CODEC_TYPE_V6);
	R(context_mem_addr, S5P_FIMV_CONTEXT_MEM_ADDR_V6);
	R(context_mem_size, S5P_FIMV_CONTEXT_MEM_SIZE_V6);
	R(pixel_क्रमmat, S5P_FIMV_PIXEL_FORMAT_V6);
	R(ret_instance_id, S5P_FIMV_RET_INSTANCE_ID_V6);
	R(error_code, S5P_FIMV_ERROR_CODE_V6);

	/* decoder रेजिस्टरs */
	R(d_crc_ctrl, S5P_FIMV_D_CRC_CTRL_V6);
	R(d_dec_options, S5P_FIMV_D_DEC_OPTIONS_V6);
	R(d_display_delay, S5P_FIMV_D_DISPLAY_DELAY_V6);
	R(d_sei_enable, S5P_FIMV_D_SEI_ENABLE_V6);
	R(d_min_num_dpb, S5P_FIMV_D_MIN_NUM_DPB_V6);
	R(d_min_num_mv, S5P_FIMV_D_MIN_NUM_MV_V6);
	R(d_mvc_num_views, S5P_FIMV_D_MVC_NUM_VIEWS_V6);
	R(d_num_dpb, S5P_FIMV_D_NUM_DPB_V6);
	R(d_num_mv, S5P_FIMV_D_NUM_MV_V6);
	R(d_init_buffer_options, S5P_FIMV_D_INIT_BUFFER_OPTIONS_V6);
	R(d_first_plane_dpb_size, S5P_FIMV_D_LUMA_DPB_SIZE_V6);
	R(d_second_plane_dpb_size, S5P_FIMV_D_CHROMA_DPB_SIZE_V6);
	R(d_mv_buffer_size, S5P_FIMV_D_MV_BUFFER_SIZE_V6);
	R(d_first_plane_dpb, S5P_FIMV_D_LUMA_DPB_V6);
	R(d_second_plane_dpb, S5P_FIMV_D_CHROMA_DPB_V6);
	R(d_mv_buffer, S5P_FIMV_D_MV_BUFFER_V6);
	R(d_scratch_buffer_addr, S5P_FIMV_D_SCRATCH_BUFFER_ADDR_V6);
	R(d_scratch_buffer_size, S5P_FIMV_D_SCRATCH_BUFFER_SIZE_V6);
	R(d_cpb_buffer_addr, S5P_FIMV_D_CPB_BUFFER_ADDR_V6);
	R(d_cpb_buffer_size, S5P_FIMV_D_CPB_BUFFER_SIZE_V6);
	R(d_available_dpb_flag_lower, S5P_FIMV_D_AVAILABLE_DPB_FLAG_LOWER_V6);
	R(d_cpb_buffer_offset, S5P_FIMV_D_CPB_BUFFER_OFFSET_V6);
	R(d_slice_अगर_enable, S5P_FIMV_D_SLICE_IF_ENABLE_V6);
	R(d_stream_data_size, S5P_FIMV_D_STREAM_DATA_SIZE_V6);
	R(d_display_frame_width, S5P_FIMV_D_DISPLAY_FRAME_WIDTH_V6);
	R(d_display_frame_height, S5P_FIMV_D_DISPLAY_FRAME_HEIGHT_V6);
	R(d_display_status, S5P_FIMV_D_DISPLAY_STATUS_V6);
	R(d_display_first_plane_addr, S5P_FIMV_D_DISPLAY_LUMA_ADDR_V6);
	R(d_display_second_plane_addr, S5P_FIMV_D_DISPLAY_CHROMA_ADDR_V6);
	R(d_display_frame_type, S5P_FIMV_D_DISPLAY_FRAME_TYPE_V6);
	R(d_display_crop_info1, S5P_FIMV_D_DISPLAY_CROP_INFO1_V6);
	R(d_display_crop_info2, S5P_FIMV_D_DISPLAY_CROP_INFO2_V6);
	R(d_display_aspect_ratio, S5P_FIMV_D_DISPLAY_ASPECT_RATIO_V6);
	R(d_display_extended_ar, S5P_FIMV_D_DISPLAY_EXTENDED_AR_V6);
	R(d_decoded_status, S5P_FIMV_D_DECODED_STATUS_V6);
	R(d_decoded_first_plane_addr, S5P_FIMV_D_DECODED_LUMA_ADDR_V6);
	R(d_decoded_second_plane_addr, S5P_FIMV_D_DECODED_CHROMA_ADDR_V6);
	R(d_decoded_frame_type, S5P_FIMV_D_DECODED_FRAME_TYPE_V6);
	R(d_decoded_nal_size, S5P_FIMV_D_DECODED_NAL_SIZE_V6);
	R(d_ret_picture_tag_top, S5P_FIMV_D_RET_PICTURE_TAG_TOP_V6);
	R(d_ret_picture_tag_bot, S5P_FIMV_D_RET_PICTURE_TAG_BOT_V6);
	R(d_h264_info, S5P_FIMV_D_H264_INFO_V6);
	R(d_mvc_view_id, S5P_FIMV_D_MVC_VIEW_ID_V6);
	R(d_frame_pack_sei_avail, S5P_FIMV_D_FRAME_PACK_SEI_AVAIL_V6);

	/* encoder रेजिस्टरs */
	R(e_frame_width, S5P_FIMV_E_FRAME_WIDTH_V6);
	R(e_frame_height, S5P_FIMV_E_FRAME_HEIGHT_V6);
	R(e_cropped_frame_width, S5P_FIMV_E_CROPPED_FRAME_WIDTH_V6);
	R(e_cropped_frame_height, S5P_FIMV_E_CROPPED_FRAME_HEIGHT_V6);
	R(e_frame_crop_offset, S5P_FIMV_E_FRAME_CROP_OFFSET_V6);
	R(e_enc_options, S5P_FIMV_E_ENC_OPTIONS_V6);
	R(e_picture_profile, S5P_FIMV_E_PICTURE_PROखाता_V6);
	R(e_vbv_buffer_size, S5P_FIMV_E_VBV_BUFFER_SIZE_V6);
	R(e_vbv_init_delay, S5P_FIMV_E_VBV_INIT_DELAY_V6);
	R(e_fixed_picture_qp, S5P_FIMV_E_FIXED_PICTURE_QP_V6);
	R(e_rc_config, S5P_FIMV_E_RC_CONFIG_V6);
	R(e_rc_qp_bound, S5P_FIMV_E_RC_QP_BOUND_V6);
	R(e_rc_mode, S5P_FIMV_E_RC_RPARAM_V6);
	R(e_mb_rc_config, S5P_FIMV_E_MB_RC_CONFIG_V6);
	R(e_padding_ctrl, S5P_FIMV_E_PADDING_CTRL_V6);
	R(e_mv_hor_range, S5P_FIMV_E_MV_HOR_RANGE_V6);
	R(e_mv_ver_range, S5P_FIMV_E_MV_VER_RANGE_V6);
	R(e_num_dpb, S5P_FIMV_E_NUM_DPB_V6);
	R(e_luma_dpb, S5P_FIMV_E_LUMA_DPB_V6);
	R(e_chroma_dpb, S5P_FIMV_E_CHROMA_DPB_V6);
	R(e_me_buffer, S5P_FIMV_E_ME_BUFFER_V6);
	R(e_scratch_buffer_addr, S5P_FIMV_E_SCRATCH_BUFFER_ADDR_V6);
	R(e_scratch_buffer_size, S5P_FIMV_E_SCRATCH_BUFFER_SIZE_V6);
	R(e_पंचांगv_buffer0, S5P_FIMV_E_TMV_BUFFER0_V6);
	R(e_पंचांगv_buffer1, S5P_FIMV_E_TMV_BUFFER1_V6);
	R(e_source_first_plane_addr, S5P_FIMV_E_SOURCE_LUMA_ADDR_V6);
	R(e_source_second_plane_addr, S5P_FIMV_E_SOURCE_CHROMA_ADDR_V6);
	R(e_stream_buffer_addr, S5P_FIMV_E_STREAM_BUFFER_ADDR_V6);
	R(e_stream_buffer_size, S5P_FIMV_E_STREAM_BUFFER_SIZE_V6);
	R(e_roi_buffer_addr, S5P_FIMV_E_ROI_BUFFER_ADDR_V6);
	R(e_param_change, S5P_FIMV_E_PARAM_CHANGE_V6);
	R(e_ir_size, S5P_FIMV_E_IR_SIZE_V6);
	R(e_gop_config, S5P_FIMV_E_GOP_CONFIG_V6);
	R(e_mslice_mode, S5P_FIMV_E_MSLICE_MODE_V6);
	R(e_mslice_size_mb, S5P_FIMV_E_MSLICE_SIZE_MB_V6);
	R(e_mslice_size_bits, S5P_FIMV_E_MSLICE_SIZE_BITS_V6);
	R(e_frame_insertion, S5P_FIMV_E_FRAME_INSERTION_V6);
	R(e_rc_frame_rate, S5P_FIMV_E_RC_FRAME_RATE_V6);
	R(e_rc_bit_rate, S5P_FIMV_E_RC_BIT_RATE_V6);
	R(e_rc_roi_ctrl, S5P_FIMV_E_RC_ROI_CTRL_V6);
	R(e_picture_tag, S5P_FIMV_E_PICTURE_TAG_V6);
	R(e_bit_count_enable, S5P_FIMV_E_BIT_COUNT_ENABLE_V6);
	R(e_max_bit_count, S5P_FIMV_E_MAX_BIT_COUNT_V6);
	R(e_min_bit_count, S5P_FIMV_E_MIN_BIT_COUNT_V6);
	R(e_metadata_buffer_addr, S5P_FIMV_E_METADATA_BUFFER_ADDR_V6);
	R(e_metadata_buffer_size, S5P_FIMV_E_METADATA_BUFFER_SIZE_V6);
	R(e_encoded_source_first_plane_addr,
			S5P_FIMV_E_ENCODED_SOURCE_LUMA_ADDR_V6);
	R(e_encoded_source_second_plane_addr,
			S5P_FIMV_E_ENCODED_SOURCE_CHROMA_ADDR_V6);
	R(e_stream_size, S5P_FIMV_E_STREAM_SIZE_V6);
	R(e_slice_type, S5P_FIMV_E_SLICE_TYPE_V6);
	R(e_picture_count, S5P_FIMV_E_PICTURE_COUNT_V6);
	R(e_ret_picture_tag, S5P_FIMV_E_RET_PICTURE_TAG_V6);
	R(e_recon_luma_dpb_addr, S5P_FIMV_E_RECON_LUMA_DPB_ADDR_V6);
	R(e_recon_chroma_dpb_addr, S5P_FIMV_E_RECON_CHROMA_DPB_ADDR_V6);
	R(e_mpeg4_options, S5P_FIMV_E_MPEG4_OPTIONS_V6);
	R(e_mpeg4_hec_period, S5P_FIMV_E_MPEG4_HEC_PERIOD_V6);
	R(e_aspect_ratio, S5P_FIMV_E_ASPECT_RATIO_V6);
	R(e_extended_sar, S5P_FIMV_E_EXTENDED_SAR_V6);
	R(e_h264_options, S5P_FIMV_E_H264_OPTIONS_V6);
	R(e_h264_lf_alpha_offset, S5P_FIMV_E_H264_LF_ALPHA_OFFSET_V6);
	R(e_h264_lf_beta_offset, S5P_FIMV_E_H264_LF_BETA_OFFSET_V6);
	R(e_h264_i_period, S5P_FIMV_E_H264_I_PERIOD_V6);
	R(e_h264_fmo_slice_grp_map_type,
			S5P_FIMV_E_H264_FMO_SLICE_GRP_MAP_TYPE_V6);
	R(e_h264_fmo_num_slice_grp_minus1,
			S5P_FIMV_E_H264_FMO_NUM_SLICE_GRP_MINUS1_V6);
	R(e_h264_fmo_slice_grp_change_dir,
			S5P_FIMV_E_H264_FMO_SLICE_GRP_CHANGE_सूची_V6);
	R(e_h264_fmo_slice_grp_change_rate_minus1,
			S5P_FIMV_E_H264_FMO_SLICE_GRP_CHANGE_RATE_MINUS1_V6);
	R(e_h264_fmo_run_length_minus1_0,
			S5P_FIMV_E_H264_FMO_RUN_LENGTH_MINUS1_0_V6);
	R(e_h264_aso_slice_order_0, S5P_FIMV_E_H264_ASO_SLICE_ORDER_0_V6);
	R(e_h264_num_t_layer, S5P_FIMV_E_H264_NUM_T_LAYER_V6);
	R(e_h264_hierarchical_qp_layer0,
			S5P_FIMV_E_H264_HIERARCHICAL_QP_LAYER0_V6);
	R(e_h264_frame_packing_sei_info,
			S5P_FIMV_E_H264_FRAME_PACKING_SEI_INFO_V6);

	अगर (!IS_MFCV7_PLUS(dev))
		जाओ करोne;

	/* Initialize रेजिस्टरs used in MFC v7+ */
	R(e_source_first_plane_addr, S5P_FIMV_E_SOURCE_FIRST_ADDR_V7);
	R(e_source_second_plane_addr, S5P_FIMV_E_SOURCE_SECOND_ADDR_V7);
	R(e_source_third_plane_addr, S5P_FIMV_E_SOURCE_THIRD_ADDR_V7);
	R(e_source_first_plane_stride, S5P_FIMV_E_SOURCE_FIRST_STRIDE_V7);
	R(e_source_second_plane_stride, S5P_FIMV_E_SOURCE_SECOND_STRIDE_V7);
	R(e_source_third_plane_stride, S5P_FIMV_E_SOURCE_THIRD_STRIDE_V7);
	R(e_encoded_source_first_plane_addr,
			S5P_FIMV_E_ENCODED_SOURCE_FIRST_ADDR_V7);
	R(e_encoded_source_second_plane_addr,
			S5P_FIMV_E_ENCODED_SOURCE_SECOND_ADDR_V7);
	R(e_vp8_options, S5P_FIMV_E_VP8_OPTIONS_V7);

	अगर (!IS_MFCV8_PLUS(dev))
		जाओ करोne;

	/* Initialize रेजिस्टरs used in MFC v8 only.
	 * Also, over-ग_लिखो the रेजिस्टरs which have
	 * a dअगरferent offset क्रम MFC v8. */
	R(d_stream_data_size, S5P_FIMV_D_STREAM_DATA_SIZE_V8);
	R(d_cpb_buffer_addr, S5P_FIMV_D_CPB_BUFFER_ADDR_V8);
	R(d_cpb_buffer_size, S5P_FIMV_D_CPB_BUFFER_SIZE_V8);
	R(d_cpb_buffer_offset, S5P_FIMV_D_CPB_BUFFER_OFFSET_V8);
	R(d_first_plane_dpb_size, S5P_FIMV_D_FIRST_PLANE_DPB_SIZE_V8);
	R(d_second_plane_dpb_size, S5P_FIMV_D_SECOND_PLANE_DPB_SIZE_V8);
	R(d_scratch_buffer_addr, S5P_FIMV_D_SCRATCH_BUFFER_ADDR_V8);
	R(d_scratch_buffer_size, S5P_FIMV_D_SCRATCH_BUFFER_SIZE_V8);
	R(d_first_plane_dpb_stride_size,
			S5P_FIMV_D_FIRST_PLANE_DPB_STRIDE_SIZE_V8);
	R(d_second_plane_dpb_stride_size,
			S5P_FIMV_D_SECOND_PLANE_DPB_STRIDE_SIZE_V8);
	R(d_mv_buffer_size, S5P_FIMV_D_MV_BUFFER_SIZE_V8);
	R(d_num_mv, S5P_FIMV_D_NUM_MV_V8);
	R(d_first_plane_dpb, S5P_FIMV_D_FIRST_PLANE_DPB_V8);
	R(d_second_plane_dpb, S5P_FIMV_D_SECOND_PLANE_DPB_V8);
	R(d_mv_buffer, S5P_FIMV_D_MV_BUFFER_V8);
	R(d_init_buffer_options, S5P_FIMV_D_INIT_BUFFER_OPTIONS_V8);
	R(d_available_dpb_flag_lower, S5P_FIMV_D_AVAILABLE_DPB_FLAG_LOWER_V8);
	R(d_slice_अगर_enable, S5P_FIMV_D_SLICE_IF_ENABLE_V8);
	R(d_display_first_plane_addr, S5P_FIMV_D_DISPLAY_FIRST_PLANE_ADDR_V8);
	R(d_display_second_plane_addr, S5P_FIMV_D_DISPLAY_SECOND_PLANE_ADDR_V8);
	R(d_decoded_first_plane_addr, S5P_FIMV_D_DECODED_FIRST_PLANE_ADDR_V8);
	R(d_decoded_second_plane_addr, S5P_FIMV_D_DECODED_SECOND_PLANE_ADDR_V8);
	R(d_display_status, S5P_FIMV_D_DISPLAY_STATUS_V8);
	R(d_decoded_status, S5P_FIMV_D_DECODED_STATUS_V8);
	R(d_decoded_frame_type, S5P_FIMV_D_DECODED_FRAME_TYPE_V8);
	R(d_display_frame_type, S5P_FIMV_D_DISPLAY_FRAME_TYPE_V8);
	R(d_decoded_nal_size, S5P_FIMV_D_DECODED_NAL_SIZE_V8);
	R(d_display_frame_width, S5P_FIMV_D_DISPLAY_FRAME_WIDTH_V8);
	R(d_display_frame_height, S5P_FIMV_D_DISPLAY_FRAME_HEIGHT_V8);
	R(d_frame_pack_sei_avail, S5P_FIMV_D_FRAME_PACK_SEI_AVAIL_V8);
	R(d_mvc_num_views, S5P_FIMV_D_MVC_NUM_VIEWS_V8);
	R(d_mvc_view_id, S5P_FIMV_D_MVC_VIEW_ID_V8);
	R(d_ret_picture_tag_top, S5P_FIMV_D_RET_PICTURE_TAG_TOP_V8);
	R(d_ret_picture_tag_bot, S5P_FIMV_D_RET_PICTURE_TAG_BOT_V8);
	R(d_display_crop_info1, S5P_FIMV_D_DISPLAY_CROP_INFO1_V8);
	R(d_display_crop_info2, S5P_FIMV_D_DISPLAY_CROP_INFO2_V8);
	R(d_min_scratch_buffer_size, S5P_FIMV_D_MIN_SCRATCH_BUFFER_SIZE_V8);

	/* encoder रेजिस्टरs */
	R(e_padding_ctrl, S5P_FIMV_E_PADDING_CTRL_V8);
	R(e_rc_config, S5P_FIMV_E_RC_CONFIG_V8);
	R(e_rc_mode, S5P_FIMV_E_RC_RPARAM_V8);
	R(e_mv_hor_range, S5P_FIMV_E_MV_HOR_RANGE_V8);
	R(e_mv_ver_range, S5P_FIMV_E_MV_VER_RANGE_V8);
	R(e_rc_qp_bound, S5P_FIMV_E_RC_QP_BOUND_V8);
	R(e_fixed_picture_qp, S5P_FIMV_E_FIXED_PICTURE_QP_V8);
	R(e_vbv_buffer_size, S5P_FIMV_E_VBV_BUFFER_SIZE_V8);
	R(e_vbv_init_delay, S5P_FIMV_E_VBV_INIT_DELAY_V8);
	R(e_mb_rc_config, S5P_FIMV_E_MB_RC_CONFIG_V8);
	R(e_aspect_ratio, S5P_FIMV_E_ASPECT_RATIO_V8);
	R(e_extended_sar, S5P_FIMV_E_EXTENDED_SAR_V8);
	R(e_h264_options, S5P_FIMV_E_H264_OPTIONS_V8);
	R(e_min_scratch_buffer_size, S5P_FIMV_E_MIN_SCRATCH_BUFFER_SIZE_V8);

	अगर (!IS_MFCV10(dev))
		जाओ करोne;

	/* Initialize रेजिस्टरs used in MFC v10 only.
	 * Also, over-ग_लिखो the रेजिस्टरs which have
	 * a dअगरferent offset क्रम MFC v10.
	 */

	/* decoder रेजिस्टरs */
	R(d_अटल_buffer_addr, S5P_FIMV_D_STATIC_BUFFER_ADDR_V10);
	R(d_अटल_buffer_size, S5P_FIMV_D_STATIC_BUFFER_SIZE_V10);

	/* encoder रेजिस्टरs */
	R(e_num_t_layer, S5P_FIMV_E_NUM_T_LAYER_V10);
	R(e_hier_qp_layer0, S5P_FIMV_E_HIERARCHICAL_QP_LAYER0_V10);
	R(e_hier_bit_rate_layer0, S5P_FIMV_E_HIERARCHICAL_BIT_RATE_LAYER0_V10);
	R(e_hevc_options, S5P_FIMV_E_HEVC_OPTIONS_V10);
	R(e_hevc_refresh_period, S5P_FIMV_E_HEVC_REFRESH_PERIOD_V10);
	R(e_hevc_lf_beta_offset_भाग2, S5P_FIMV_E_HEVC_LF_BETA_OFFSET_DIV2_V10);
	R(e_hevc_lf_tc_offset_भाग2, S5P_FIMV_E_HEVC_LF_TC_OFFSET_DIV2_V10);
	R(e_hevc_nal_control, S5P_FIMV_E_HEVC_NAL_CONTROL_V10);

करोne:
	वापस &mfc_regs;
#अघोषित S5P_MFC_REG_ADDR
#अघोषित R
पूर्ण

/* Initialize opr function poपूर्णांकers क्रम MFC v6 */
अटल काष्ठा s5p_mfc_hw_ops s5p_mfc_ops_v6 = अणु
	.alloc_dec_temp_buffers = s5p_mfc_alloc_dec_temp_buffers_v6,
	.release_dec_desc_buffer = s5p_mfc_release_dec_desc_buffer_v6,
	.alloc_codec_buffers = s5p_mfc_alloc_codec_buffers_v6,
	.release_codec_buffers = s5p_mfc_release_codec_buffers_v6,
	.alloc_instance_buffer = s5p_mfc_alloc_instance_buffer_v6,
	.release_instance_buffer = s5p_mfc_release_instance_buffer_v6,
	.alloc_dev_context_buffer =
		s5p_mfc_alloc_dev_context_buffer_v6,
	.release_dev_context_buffer =
		s5p_mfc_release_dev_context_buffer_v6,
	.dec_calc_dpb_size = s5p_mfc_dec_calc_dpb_size_v6,
	.enc_calc_src_size = s5p_mfc_enc_calc_src_size_v6,
	.set_enc_stream_buffer = s5p_mfc_set_enc_stream_buffer_v6,
	.set_enc_frame_buffer = s5p_mfc_set_enc_frame_buffer_v6,
	.get_enc_frame_buffer = s5p_mfc_get_enc_frame_buffer_v6,
	.try_run = s5p_mfc_try_run_v6,
	.clear_पूर्णांक_flags = s5p_mfc_clear_पूर्णांक_flags_v6,
	.get_dspl_y_adr = s5p_mfc_get_dspl_y_adr_v6,
	.get_dec_y_adr = s5p_mfc_get_dec_y_adr_v6,
	.get_dspl_status = s5p_mfc_get_dspl_status_v6,
	.get_dec_status = s5p_mfc_get_dec_status_v6,
	.get_dec_frame_type = s5p_mfc_get_dec_frame_type_v6,
	.get_disp_frame_type = s5p_mfc_get_disp_frame_type_v6,
	.get_consumed_stream = s5p_mfc_get_consumed_stream_v6,
	.get_पूर्णांक_reason = s5p_mfc_get_पूर्णांक_reason_v6,
	.get_पूर्णांक_err = s5p_mfc_get_पूर्णांक_err_v6,
	.err_dec = s5p_mfc_err_dec_v6,
	.get_img_width = s5p_mfc_get_img_width_v6,
	.get_img_height = s5p_mfc_get_img_height_v6,
	.get_dpb_count = s5p_mfc_get_dpb_count_v6,
	.get_mv_count = s5p_mfc_get_mv_count_v6,
	.get_inst_no = s5p_mfc_get_inst_no_v6,
	.get_enc_strm_size = s5p_mfc_get_enc_strm_size_v6,
	.get_enc_slice_type = s5p_mfc_get_enc_slice_type_v6,
	.get_enc_dpb_count = s5p_mfc_get_enc_dpb_count_v6,
	.get_pic_type_top = s5p_mfc_get_pic_type_top_v6,
	.get_pic_type_bot = s5p_mfc_get_pic_type_bot_v6,
	.get_crop_info_h = s5p_mfc_get_crop_info_h_v6,
	.get_crop_info_v = s5p_mfc_get_crop_info_v_v6,
	.get_min_scratch_buf_size = s5p_mfc_get_min_scratch_buf_size,
	.get_e_min_scratch_buf_size = s5p_mfc_get_e_min_scratch_buf_size,
पूर्ण;

काष्ठा s5p_mfc_hw_ops *s5p_mfc_init_hw_ops_v6(व्योम)
अणु
	वापस &s5p_mfc_ops_v6;
पूर्ण
