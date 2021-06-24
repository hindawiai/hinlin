<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Hantro VPU codec driver
 *
 * Copyright (C) 2018 Rockchip Electronics Co., Ltd.
 */

#समावेश "hantro.h"

अटल स्थिर u8 zigzag[64] = अणु
	0,   1,  8, 16,  9,  2,  3, 10,
	17, 24, 32, 25, 18, 11,  4,  5,
	12, 19, 26, 33, 40, 48, 41, 34,
	27, 20, 13,  6,  7, 14, 21, 28,
	35, 42, 49, 56, 57, 50, 43, 36,
	29, 22, 15, 23, 30, 37, 44, 51,
	58, 59, 52, 45, 38, 31, 39, 46,
	53, 60, 61, 54, 47, 55, 62, 63
पूर्ण;

व्योम hantro_mpeg2_dec_copy_qtable(u8 *qtable,
	स्थिर काष्ठा v4l2_ctrl_mpeg2_quantization *ctrl)
अणु
	पूर्णांक i, n;

	अगर (!qtable || !ctrl)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(zigzag); i++) अणु
		n = zigzag[i];
		qtable[n + 0] = ctrl->पूर्णांकra_quantiser_matrix[i];
		qtable[n + 64] = ctrl->non_पूर्णांकra_quantiser_matrix[i];
		qtable[n + 128] = ctrl->chroma_पूर्णांकra_quantiser_matrix[i];
		qtable[n + 192] = ctrl->chroma_non_पूर्णांकra_quantiser_matrix[i];
	पूर्ण
पूर्ण

पूर्णांक hantro_mpeg2_dec_init(काष्ठा hantro_ctx *ctx)
अणु
	काष्ठा hantro_dev *vpu = ctx->dev;

	ctx->mpeg2_dec.qtable.size = ARRAY_SIZE(zigzag) * 4;
	ctx->mpeg2_dec.qtable.cpu =
		dma_alloc_coherent(vpu->dev,
				   ctx->mpeg2_dec.qtable.size,
				   &ctx->mpeg2_dec.qtable.dma,
				   GFP_KERNEL);
	अगर (!ctx->mpeg2_dec.qtable.cpu)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम hantro_mpeg2_dec_निकास(काष्ठा hantro_ctx *ctx)
अणु
	काष्ठा hantro_dev *vpu = ctx->dev;

	dma_मुक्त_coherent(vpu->dev,
			  ctx->mpeg2_dec.qtable.size,
			  ctx->mpeg2_dec.qtable.cpu,
			  ctx->mpeg2_dec.qtable.dma);
पूर्ण
