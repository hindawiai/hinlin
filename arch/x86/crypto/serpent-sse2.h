<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ASM_X86_SERPENT_SSE2_H
#घोषणा ASM_X86_SERPENT_SSE2_H

#समावेश <linux/crypto.h>
#समावेश <crypto/serpent.h>

#अगर_घोषित CONFIG_X86_32

#घोषणा SERPENT_PARALLEL_BLOCKS 4

यंत्रlinkage व्योम __serpent_enc_blk_4way(स्थिर काष्ठा serpent_ctx *ctx, u8 *dst,
				       स्थिर u8 *src, bool xor);
यंत्रlinkage व्योम serpent_dec_blk_4way(स्थिर काष्ठा serpent_ctx *ctx, u8 *dst,
				     स्थिर u8 *src);

अटल अंतरभूत व्योम serpent_enc_blk_xway(स्थिर व्योम *ctx, u8 *dst, स्थिर u8 *src)
अणु
	__serpent_enc_blk_4way(ctx, dst, src, false);
पूर्ण

अटल अंतरभूत व्योम serpent_enc_blk_xway_xor(स्थिर काष्ठा serpent_ctx *ctx,
					    u8 *dst, स्थिर u8 *src)
अणु
	__serpent_enc_blk_4way(ctx, dst, src, true);
पूर्ण

अटल अंतरभूत व्योम serpent_dec_blk_xway(स्थिर व्योम *ctx, u8 *dst, स्थिर u8 *src)
अणु
	serpent_dec_blk_4way(ctx, dst, src);
पूर्ण

#अन्यथा

#घोषणा SERPENT_PARALLEL_BLOCKS 8

यंत्रlinkage व्योम __serpent_enc_blk_8way(स्थिर काष्ठा serpent_ctx *ctx, u8 *dst,
				       स्थिर u8 *src, bool xor);
यंत्रlinkage व्योम serpent_dec_blk_8way(स्थिर काष्ठा serpent_ctx *ctx, u8 *dst,
				     स्थिर u8 *src);

अटल अंतरभूत व्योम serpent_enc_blk_xway(स्थिर व्योम *ctx, u8 *dst, स्थिर u8 *src)
अणु
	__serpent_enc_blk_8way(ctx, dst, src, false);
पूर्ण

अटल अंतरभूत व्योम serpent_enc_blk_xway_xor(स्थिर काष्ठा serpent_ctx *ctx,
					    u8 *dst, स्थिर u8 *src)
अणु
	__serpent_enc_blk_8way(ctx, dst, src, true);
पूर्ण

अटल अंतरभूत व्योम serpent_dec_blk_xway(स्थिर व्योम *ctx, u8 *dst, स्थिर u8 *src)
अणु
	serpent_dec_blk_8way(ctx, dst, src);
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
