<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Cryptographic API
 *
 * Michael MIC (IEEE 802.11i/TKIP) keyed digest
 *
 * Copyright (c) 2004 Jouni Malinen <j@w1.fi>
 */
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>


काष्ठा michael_mic_ctx अणु
	u32 l, r;
पूर्ण;

काष्ठा michael_mic_desc_ctx अणु
	__le32 pending;
	माप_प्रकार pending_len;

	u32 l, r;
पूर्ण;

अटल अंतरभूत u32 xswap(u32 val)
अणु
	वापस ((val & 0x00ff00ff) << 8) | ((val & 0xff00ff00) >> 8);
पूर्ण


#घोषणा michael_block(l, r)	\
करो अणु				\
	r ^= rol32(l, 17);	\
	l += r;			\
	r ^= xswap(l);		\
	l += r;			\
	r ^= rol32(l, 3);	\
	l += r;			\
	r ^= ror32(l, 2);	\
	l += r;			\
पूर्ण जबतक (0)


अटल पूर्णांक michael_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा michael_mic_desc_ctx *mctx = shash_desc_ctx(desc);
	काष्ठा michael_mic_ctx *ctx = crypto_shash_ctx(desc->tfm);
	mctx->pending_len = 0;
	mctx->l = ctx->l;
	mctx->r = ctx->r;

	वापस 0;
पूर्ण


अटल पूर्णांक michael_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			   अचिन्हित पूर्णांक len)
अणु
	काष्ठा michael_mic_desc_ctx *mctx = shash_desc_ctx(desc);

	अगर (mctx->pending_len) अणु
		पूर्णांक flen = 4 - mctx->pending_len;
		अगर (flen > len)
			flen = len;
		स_नकल((u8 *)&mctx->pending + mctx->pending_len, data, flen);
		mctx->pending_len += flen;
		data += flen;
		len -= flen;

		अगर (mctx->pending_len < 4)
			वापस 0;

		mctx->l ^= le32_to_cpu(mctx->pending);
		michael_block(mctx->l, mctx->r);
		mctx->pending_len = 0;
	पूर्ण

	जबतक (len >= 4) अणु
		mctx->l ^= get_unaligned_le32(data);
		michael_block(mctx->l, mctx->r);
		data += 4;
		len -= 4;
	पूर्ण

	अगर (len > 0) अणु
		mctx->pending_len = len;
		स_नकल(&mctx->pending, data, len);
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक michael_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	काष्ठा michael_mic_desc_ctx *mctx = shash_desc_ctx(desc);
	u8 *data = (u8 *)&mctx->pending;

	/* Last block and padding (0x5a, 4..7 x 0) */
	चयन (mctx->pending_len) अणु
	हाल 0:
		mctx->l ^= 0x5a;
		अवरोध;
	हाल 1:
		mctx->l ^= data[0] | 0x5a00;
		अवरोध;
	हाल 2:
		mctx->l ^= data[0] | (data[1] << 8) | 0x5a0000;
		अवरोध;
	हाल 3:
		mctx->l ^= data[0] | (data[1] << 8) | (data[2] << 16) |
			0x5a000000;
		अवरोध;
	पूर्ण
	michael_block(mctx->l, mctx->r);
	/* l ^= 0; */
	michael_block(mctx->l, mctx->r);

	put_unaligned_le32(mctx->l, out);
	put_unaligned_le32(mctx->r, out + 4);

	वापस 0;
पूर्ण


अटल पूर्णांक michael_setkey(काष्ठा crypto_shash *tfm, स्थिर u8 *key,
			  अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा michael_mic_ctx *mctx = crypto_shash_ctx(tfm);

	अगर (keylen != 8)
		वापस -EINVAL;

	mctx->l = get_unaligned_le32(key);
	mctx->r = get_unaligned_le32(key + 4);
	वापस 0;
पूर्ण

अटल काष्ठा shash_alg alg = अणु
	.digestsize		=	8,
	.setkey			=	michael_setkey,
	.init			=	michael_init,
	.update			=	michael_update,
	.final			=	michael_final,
	.descsize		=	माप(काष्ठा michael_mic_desc_ctx),
	.base			=	अणु
		.cra_name		=	"michael_mic",
		.cra_driver_name	=	"michael_mic-generic",
		.cra_blocksize		=	8,
		.cra_ctxsize		=	माप(काष्ठा michael_mic_ctx),
		.cra_module		=	THIS_MODULE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init michael_mic_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_shash(&alg);
पूर्ण


अटल व्योम __निकास michael_mic_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&alg);
पूर्ण


subsys_initcall(michael_mic_init);
module_निकास(michael_mic_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Michael MIC");
MODULE_AUTHOR("Jouni Malinen <j@w1.fi>");
MODULE_ALIAS_CRYPTO("michael_mic");
