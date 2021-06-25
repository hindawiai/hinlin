<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ASM_X86_TWOFISH_H
#घोषणा ASM_X86_TWOFISH_H

#समावेश <linux/crypto.h>
#समावेश <crypto/twofish.h>
#समावेश <crypto/b128ops.h>

/* regular block cipher functions from twofish_x86_64 module */
यंत्रlinkage व्योम twofish_enc_blk(स्थिर व्योम *ctx, u8 *dst, स्थिर u8 *src);
यंत्रlinkage व्योम twofish_dec_blk(स्थिर व्योम *ctx, u8 *dst, स्थिर u8 *src);

/* 3-way parallel cipher functions */
यंत्रlinkage व्योम __twofish_enc_blk_3way(स्थिर व्योम *ctx, u8 *dst, स्थिर u8 *src,
				       bool xor);
यंत्रlinkage व्योम twofish_dec_blk_3way(स्थिर व्योम *ctx, u8 *dst, स्थिर u8 *src);

/* helpers from twofish_x86_64-3way module */
बाह्य व्योम twofish_dec_blk_cbc_3way(स्थिर व्योम *ctx, u8 *dst, स्थिर u8 *src);

#पूर्ण_अगर /* ASM_X86_TWOFISH_H */
