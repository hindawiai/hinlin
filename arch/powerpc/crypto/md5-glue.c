<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Glue code क्रम MD5 implementation क्रम PPC assembler
 *
 * Based on generic implementation.
 *
 * Copyright (c) 2015 Markus Stockhausen <stockhausen@collogia.de>
 */

#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/types.h>
#समावेश <crypto/md5.h>
#समावेश <यंत्र/byteorder.h>

बाह्य व्योम ppc_md5_transक्रमm(u32 *state, स्थिर u8 *src, u32 blocks);

अटल अंतरभूत व्योम ppc_md5_clear_context(काष्ठा md5_state *sctx)
अणु
	पूर्णांक count = माप(काष्ठा md5_state) >> 2;
	u32 *ptr = (u32 *)sctx;

	/* make sure we can clear the fast way */
	BUILD_BUG_ON(माप(काष्ठा md5_state) % 4);
	करो अणु *ptr++ = 0; पूर्ण जबतक (--count);
पूर्ण

अटल पूर्णांक ppc_md5_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा md5_state *sctx = shash_desc_ctx(desc);

	sctx->hash[0] = MD5_H0;
	sctx->hash[1] = MD5_H1;
	sctx->hash[2] = MD5_H2;
	sctx->hash[3] =	MD5_H3;
	sctx->byte_count = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक ppc_md5_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			अचिन्हित पूर्णांक len)
अणु
	काष्ठा md5_state *sctx = shash_desc_ctx(desc);
	स्थिर अचिन्हित पूर्णांक offset = sctx->byte_count & 0x3f;
	अचिन्हित पूर्णांक avail = 64 - offset;
	स्थिर u8 *src = data;

	sctx->byte_count += len;

	अगर (avail > len) अणु
		स_नकल((अक्षर *)sctx->block + offset, src, len);
		वापस 0;
	पूर्ण

	अगर (offset) अणु
		स_नकल((अक्षर *)sctx->block + offset, src, avail);
		ppc_md5_transक्रमm(sctx->hash, (स्थिर u8 *)sctx->block, 1);
		len -= avail;
		src += avail;
	पूर्ण

	अगर (len > 63) अणु
		ppc_md5_transक्रमm(sctx->hash, src, len >> 6);
		src += len & ~0x3f;
		len &= 0x3f;
	पूर्ण

	स_नकल((अक्षर *)sctx->block, src, len);
	वापस 0;
पूर्ण

अटल पूर्णांक ppc_md5_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	काष्ठा md5_state *sctx = shash_desc_ctx(desc);
	स्थिर अचिन्हित पूर्णांक offset = sctx->byte_count & 0x3f;
	स्थिर u8 *src = (स्थिर u8 *)sctx->block;
	u8 *p = (u8 *)src + offset;
	पूर्णांक padlen = 55 - offset;
	__le64 *pbits = (__le64 *)((अक्षर *)sctx->block + 56);
	__le32 *dst = (__le32 *)out;

	*p++ = 0x80;

	अगर (padlen < 0) अणु
		स_रखो(p, 0x00, padlen + माप (u64));
		ppc_md5_transक्रमm(sctx->hash, src, 1);
		p = (अक्षर *)sctx->block;
		padlen = 56;
	पूर्ण

	स_रखो(p, 0, padlen);
	*pbits = cpu_to_le64(sctx->byte_count << 3);
	ppc_md5_transक्रमm(sctx->hash, src, 1);

	dst[0] = cpu_to_le32(sctx->hash[0]);
	dst[1] = cpu_to_le32(sctx->hash[1]);
	dst[2] = cpu_to_le32(sctx->hash[2]);
	dst[3] = cpu_to_le32(sctx->hash[3]);

	ppc_md5_clear_context(sctx);
	वापस 0;
पूर्ण

अटल पूर्णांक ppc_md5_export(काष्ठा shash_desc *desc, व्योम *out)
अणु
	काष्ठा md5_state *sctx = shash_desc_ctx(desc);

	स_नकल(out, sctx, माप(*sctx));
	वापस 0;
पूर्ण

अटल पूर्णांक ppc_md5_import(काष्ठा shash_desc *desc, स्थिर व्योम *in)
अणु
	काष्ठा md5_state *sctx = shash_desc_ctx(desc);

	स_नकल(sctx, in, माप(*sctx));
	वापस 0;
पूर्ण

अटल काष्ठा shash_alg alg = अणु
	.digestsize	=	MD5_DIGEST_SIZE,
	.init		=	ppc_md5_init,
	.update		=	ppc_md5_update,
	.final		=	ppc_md5_final,
	.export		=	ppc_md5_export,
	.import		=	ppc_md5_import,
	.descsize	=	माप(काष्ठा md5_state),
	.statesize	=	माप(काष्ठा md5_state),
	.base		=	अणु
		.cra_name	=	"md5",
		.cra_driver_name=	"md5-ppc",
		.cra_priority	=	200,
		.cra_blocksize	=	MD5_HMAC_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init ppc_md5_mod_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_shash(&alg);
पूर्ण

अटल व्योम __निकास ppc_md5_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&alg);
पूर्ण

module_init(ppc_md5_mod_init);
module_निकास(ppc_md5_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("MD5 Secure Hash Algorithm, PPC assembler");

MODULE_ALIAS_CRYPTO("md5");
MODULE_ALIAS_CRYPTO("md5-ppc");
