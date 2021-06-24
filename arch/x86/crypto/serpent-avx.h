<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ASM_X86_SERPENT_AVX_H
#घोषणा ASM_X86_SERPENT_AVX_H

#समावेश <crypto/b128ops.h>
#समावेश <crypto/serpent.h>
#समावेश <linux/types.h>

काष्ठा crypto_skcipher;

#घोषणा SERPENT_PARALLEL_BLOCKS 8

यंत्रlinkage व्योम serpent_ecb_enc_8way_avx(स्थिर व्योम *ctx, u8 *dst,
					 स्थिर u8 *src);
यंत्रlinkage व्योम serpent_ecb_dec_8way_avx(स्थिर व्योम *ctx, u8 *dst,
					 स्थिर u8 *src);

यंत्रlinkage व्योम serpent_cbc_dec_8way_avx(स्थिर व्योम *ctx, u8 *dst,
					 स्थिर u8 *src);

#पूर्ण_अगर
