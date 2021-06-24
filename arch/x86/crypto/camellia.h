<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ASM_X86_CAMELLIA_H
#घोषणा ASM_X86_CAMELLIA_H

#समावेश <crypto/b128ops.h>
#समावेश <linux/crypto.h>
#समावेश <linux/kernel.h>

#घोषणा CAMELLIA_MIN_KEY_SIZE	16
#घोषणा CAMELLIA_MAX_KEY_SIZE	32
#घोषणा CAMELLIA_BLOCK_SIZE	16
#घोषणा CAMELLIA_TABLE_BYTE_LEN	272
#घोषणा CAMELLIA_PARALLEL_BLOCKS 2

काष्ठा crypto_skcipher;

काष्ठा camellia_ctx अणु
	u64 key_table[CAMELLIA_TABLE_BYTE_LEN / माप(u64)];
	u32 key_length;
पूर्ण;

बाह्य पूर्णांक __camellia_setkey(काष्ठा camellia_ctx *cctx,
			     स्थिर अचिन्हित अक्षर *key,
			     अचिन्हित पूर्णांक key_len);

/* regular block cipher functions */
यंत्रlinkage व्योम __camellia_enc_blk(स्थिर व्योम *ctx, u8 *dst, स्थिर u8 *src,
				   bool xor);
यंत्रlinkage व्योम camellia_dec_blk(स्थिर व्योम *ctx, u8 *dst, स्थिर u8 *src);

/* 2-way parallel cipher functions */
यंत्रlinkage व्योम __camellia_enc_blk_2way(स्थिर व्योम *ctx, u8 *dst, स्थिर u8 *src,
					bool xor);
यंत्रlinkage व्योम camellia_dec_blk_2way(स्थिर व्योम *ctx, u8 *dst, स्थिर u8 *src);

/* 16-way parallel cipher functions (avx/aes-ni) */
यंत्रlinkage व्योम camellia_ecb_enc_16way(स्थिर व्योम *ctx, u8 *dst, स्थिर u8 *src);
यंत्रlinkage व्योम camellia_ecb_dec_16way(स्थिर व्योम *ctx, u8 *dst, स्थिर u8 *src);

यंत्रlinkage व्योम camellia_cbc_dec_16way(स्थिर व्योम *ctx, u8 *dst, स्थिर u8 *src);

अटल अंतरभूत व्योम camellia_enc_blk(स्थिर व्योम *ctx, u8 *dst, स्थिर u8 *src)
अणु
	__camellia_enc_blk(ctx, dst, src, false);
पूर्ण

अटल अंतरभूत व्योम camellia_enc_blk_xor(स्थिर व्योम *ctx, u8 *dst, स्थिर u8 *src)
अणु
	__camellia_enc_blk(ctx, dst, src, true);
पूर्ण

अटल अंतरभूत व्योम camellia_enc_blk_2way(स्थिर व्योम *ctx, u8 *dst,
					 स्थिर u8 *src)
अणु
	__camellia_enc_blk_2way(ctx, dst, src, false);
पूर्ण

अटल अंतरभूत व्योम camellia_enc_blk_xor_2way(स्थिर व्योम *ctx, u8 *dst,
					     स्थिर u8 *src)
अणु
	__camellia_enc_blk_2way(ctx, dst, src, true);
पूर्ण

/* glue helpers */
बाह्य व्योम camellia_decrypt_cbc_2way(स्थिर व्योम *ctx, u8 *dst, स्थिर u8 *src);

#पूर्ण_अगर /* ASM_X86_CAMELLIA_H */
