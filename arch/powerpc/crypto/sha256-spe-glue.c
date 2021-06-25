<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Glue code क्रम SHA-256 implementation क्रम SPE inकाष्ठाions (PPC)
 *
 * Based on generic implementation. The assembler module takes care 
 * about the SPE रेजिस्टरs so it can run from पूर्णांकerrupt context.
 *
 * Copyright (c) 2015 Markus Stockhausen <stockhausen@collogia.de>
 */

#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/types.h>
#समावेश <crypto/sha2.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश <linux/hardirq.h>

/*
 * MAX_BYTES defines the number of bytes that are allowed to be processed
 * between preempt_disable() and preempt_enable(). SHA256 takes ~2,000
 * operations per 64 bytes. e500 cores can issue two arithmetic inकाष्ठाions
 * per घड़ी cycle using one 32/64 bit unit (SU1) and one 32 bit unit (SU2).
 * Thus 1KB of input data will need an estimated maximum of 18,000 cycles.
 * Headroom क्रम cache misses included. Even with the low end model घड़ीed
 * at 667 MHz this equals to a critical समय winकरोw of less than 27us.
 *
 */
#घोषणा MAX_BYTES 1024

बाह्य व्योम ppc_spe_sha256_transक्रमm(u32 *state, स्थिर u8 *src, u32 blocks);

अटल व्योम spe_begin(व्योम)
अणु
	/* We just start SPE operations and will save SPE रेजिस्टरs later. */
	preempt_disable();
	enable_kernel_spe();
पूर्ण

अटल व्योम spe_end(व्योम)
अणु
	disable_kernel_spe();
	/* reenable preemption */
	preempt_enable();
पूर्ण

अटल अंतरभूत व्योम ppc_sha256_clear_context(काष्ठा sha256_state *sctx)
अणु
	पूर्णांक count = माप(काष्ठा sha256_state) >> 2;
	u32 *ptr = (u32 *)sctx;

	/* make sure we can clear the fast way */
	BUILD_BUG_ON(माप(काष्ठा sha256_state) % 4);
	करो अणु *ptr++ = 0; पूर्ण जबतक (--count);
पूर्ण

अटल पूर्णांक ppc_spe_sha256_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा sha256_state *sctx = shash_desc_ctx(desc);

	sctx->state[0] = SHA256_H0;
	sctx->state[1] = SHA256_H1;
	sctx->state[2] = SHA256_H2;
	sctx->state[3] = SHA256_H3;
	sctx->state[4] = SHA256_H4;
	sctx->state[5] = SHA256_H5;
	sctx->state[6] = SHA256_H6;
	sctx->state[7] = SHA256_H7;
	sctx->count = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक ppc_spe_sha224_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा sha256_state *sctx = shash_desc_ctx(desc);

	sctx->state[0] = SHA224_H0;
	sctx->state[1] = SHA224_H1;
	sctx->state[2] = SHA224_H2;
	sctx->state[3] = SHA224_H3;
	sctx->state[4] = SHA224_H4;
	sctx->state[5] = SHA224_H5;
	sctx->state[6] = SHA224_H6;
	sctx->state[7] = SHA224_H7;
	sctx->count = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक ppc_spe_sha256_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			अचिन्हित पूर्णांक len)
अणु
	काष्ठा sha256_state *sctx = shash_desc_ctx(desc);
	स्थिर अचिन्हित पूर्णांक offset = sctx->count & 0x3f;
	स्थिर अचिन्हित पूर्णांक avail = 64 - offset;
	अचिन्हित पूर्णांक bytes;
	स्थिर u8 *src = data;

	अगर (avail > len) अणु
		sctx->count += len;
		स_नकल((अक्षर *)sctx->buf + offset, src, len);
		वापस 0;
	पूर्ण

	sctx->count += len;

	अगर (offset) अणु
		स_नकल((अक्षर *)sctx->buf + offset, src, avail);

		spe_begin();
		ppc_spe_sha256_transक्रमm(sctx->state, (स्थिर u8 *)sctx->buf, 1);
		spe_end();

		len -= avail;
		src += avail;
	पूर्ण

	जबतक (len > 63) अणु
		/* cut input data पूर्णांकo smaller blocks */
		bytes = (len > MAX_BYTES) ? MAX_BYTES : len;
		bytes = bytes & ~0x3f;

		spe_begin();
		ppc_spe_sha256_transक्रमm(sctx->state, src, bytes >> 6);
		spe_end();

		src += bytes;
		len -= bytes;
	पूर्ण

	स_नकल((अक्षर *)sctx->buf, src, len);
	वापस 0;
पूर्ण

अटल पूर्णांक ppc_spe_sha256_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	काष्ठा sha256_state *sctx = shash_desc_ctx(desc);
	स्थिर अचिन्हित पूर्णांक offset = sctx->count & 0x3f;
	अक्षर *p = (अक्षर *)sctx->buf + offset;
	पूर्णांक padlen;
	__be64 *pbits = (__be64 *)(((अक्षर *)&sctx->buf) + 56);
	__be32 *dst = (__be32 *)out;

	padlen = 55 - offset;
	*p++ = 0x80;

	spe_begin();

	अगर (padlen < 0) अणु
		स_रखो(p, 0x00, padlen + माप (u64));
		ppc_spe_sha256_transक्रमm(sctx->state, sctx->buf, 1);
		p = (अक्षर *)sctx->buf;
		padlen = 56;
	पूर्ण

	स_रखो(p, 0, padlen);
	*pbits = cpu_to_be64(sctx->count << 3);
	ppc_spe_sha256_transक्रमm(sctx->state, sctx->buf, 1);

	spe_end();

	dst[0] = cpu_to_be32(sctx->state[0]);
	dst[1] = cpu_to_be32(sctx->state[1]);
	dst[2] = cpu_to_be32(sctx->state[2]);
	dst[3] = cpu_to_be32(sctx->state[3]);
	dst[4] = cpu_to_be32(sctx->state[4]);
	dst[5] = cpu_to_be32(sctx->state[5]);
	dst[6] = cpu_to_be32(sctx->state[6]);
	dst[7] = cpu_to_be32(sctx->state[7]);

	ppc_sha256_clear_context(sctx);
	वापस 0;
पूर्ण

अटल पूर्णांक ppc_spe_sha224_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	__be32 D[SHA256_DIGEST_SIZE >> 2];
	__be32 *dst = (__be32 *)out;

	ppc_spe_sha256_final(desc, (u8 *)D);

	/* aव्योम bytewise स_नकल */
	dst[0] = D[0];
	dst[1] = D[1];
	dst[2] = D[2];
	dst[3] = D[3];
	dst[4] = D[4];
	dst[5] = D[5];
	dst[6] = D[6];

	/* clear sensitive data */
	memzero_explicit(D, SHA256_DIGEST_SIZE);
	वापस 0;
पूर्ण

अटल पूर्णांक ppc_spe_sha256_export(काष्ठा shash_desc *desc, व्योम *out)
अणु
	काष्ठा sha256_state *sctx = shash_desc_ctx(desc);

	स_नकल(out, sctx, माप(*sctx));
	वापस 0;
पूर्ण

अटल पूर्णांक ppc_spe_sha256_import(काष्ठा shash_desc *desc, स्थिर व्योम *in)
अणु
	काष्ठा sha256_state *sctx = shash_desc_ctx(desc);

	स_नकल(sctx, in, माप(*sctx));
	वापस 0;
पूर्ण

अटल काष्ठा shash_alg algs[2] = अणु अणु
	.digestsize	=	SHA256_DIGEST_SIZE,
	.init		=	ppc_spe_sha256_init,
	.update		=	ppc_spe_sha256_update,
	.final		=	ppc_spe_sha256_final,
	.export		=	ppc_spe_sha256_export,
	.import		=	ppc_spe_sha256_import,
	.descsize	=	माप(काष्ठा sha256_state),
	.statesize	=	माप(काष्ठा sha256_state),
	.base		=	अणु
		.cra_name	=	"sha256",
		.cra_driver_name=	"sha256-ppc-spe",
		.cra_priority	=	300,
		.cra_blocksize	=	SHA256_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण, अणु
	.digestsize	=	SHA224_DIGEST_SIZE,
	.init		=	ppc_spe_sha224_init,
	.update		=	ppc_spe_sha256_update,
	.final		=	ppc_spe_sha224_final,
	.export		=	ppc_spe_sha256_export,
	.import		=	ppc_spe_sha256_import,
	.descsize	=	माप(काष्ठा sha256_state),
	.statesize	=	माप(काष्ठा sha256_state),
	.base		=	अणु
		.cra_name	=	"sha224",
		.cra_driver_name=	"sha224-ppc-spe",
		.cra_priority	=	300,
		.cra_blocksize	=	SHA224_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण पूर्ण;

अटल पूर्णांक __init ppc_spe_sha256_mod_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_shashes(algs, ARRAY_SIZE(algs));
पूर्ण

अटल व्योम __निकास ppc_spe_sha256_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shashes(algs, ARRAY_SIZE(algs));
पूर्ण

module_init(ppc_spe_sha256_mod_init);
module_निकास(ppc_spe_sha256_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("SHA-224 and SHA-256 Secure Hash Algorithm, SPE optimized");

MODULE_ALIAS_CRYPTO("sha224");
MODULE_ALIAS_CRYPTO("sha224-ppc-spe");
MODULE_ALIAS_CRYPTO("sha256");
MODULE_ALIAS_CRYPTO("sha256-ppc-spe");
