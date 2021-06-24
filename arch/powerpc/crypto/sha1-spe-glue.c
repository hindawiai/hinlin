<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Glue code क्रम SHA-1 implementation क्रम SPE inकाष्ठाions (PPC)
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
#समावेश <crypto/sha1.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश <linux/hardirq.h>

/*
 * MAX_BYTES defines the number of bytes that are allowed to be processed
 * between preempt_disable() and preempt_enable(). SHA1 takes ~1000
 * operations per 64 bytes. e500 cores can issue two arithmetic inकाष्ठाions
 * per घड़ी cycle using one 32/64 bit unit (SU1) and one 32 bit unit (SU2).
 * Thus 2KB of input data will need an estimated maximum of 18,000 cycles.
 * Headroom क्रम cache misses included. Even with the low end model घड़ीed
 * at 667 MHz this equals to a critical समय winकरोw of less than 27us.
 *
 */
#घोषणा MAX_BYTES 2048

बाह्य व्योम ppc_spe_sha1_transक्रमm(u32 *state, स्थिर u8 *src, u32 blocks);

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

अटल अंतरभूत व्योम ppc_sha1_clear_context(काष्ठा sha1_state *sctx)
अणु
	पूर्णांक count = माप(काष्ठा sha1_state) >> 2;
	u32 *ptr = (u32 *)sctx;

	/* make sure we can clear the fast way */
	BUILD_BUG_ON(माप(काष्ठा sha1_state) % 4);
	करो अणु *ptr++ = 0; पूर्ण जबतक (--count);
पूर्ण

अटल पूर्णांक ppc_spe_sha1_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा sha1_state *sctx = shash_desc_ctx(desc);

	sctx->state[0] = SHA1_H0;
	sctx->state[1] = SHA1_H1;
	sctx->state[2] = SHA1_H2;
	sctx->state[3] = SHA1_H3;
	sctx->state[4] = SHA1_H4;
	sctx->count = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक ppc_spe_sha1_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			अचिन्हित पूर्णांक len)
अणु
	काष्ठा sha1_state *sctx = shash_desc_ctx(desc);
	स्थिर अचिन्हित पूर्णांक offset = sctx->count & 0x3f;
	स्थिर अचिन्हित पूर्णांक avail = 64 - offset;
	अचिन्हित पूर्णांक bytes;
	स्थिर u8 *src = data;

	अगर (avail > len) अणु
		sctx->count += len;
		स_नकल((अक्षर *)sctx->buffer + offset, src, len);
		वापस 0;
	पूर्ण

	sctx->count += len;

	अगर (offset) अणु
		स_नकल((अक्षर *)sctx->buffer + offset, src, avail);

		spe_begin();
		ppc_spe_sha1_transक्रमm(sctx->state, (स्थिर u8 *)sctx->buffer, 1);
		spe_end();

		len -= avail;
		src += avail;
	पूर्ण

	जबतक (len > 63) अणु
		bytes = (len > MAX_BYTES) ? MAX_BYTES : len;
		bytes = bytes & ~0x3f;

		spe_begin();
		ppc_spe_sha1_transक्रमm(sctx->state, src, bytes >> 6);
		spe_end();

		src += bytes;
		len -= bytes;
	पूर्ण

	स_नकल((अक्षर *)sctx->buffer, src, len);
	वापस 0;
पूर्ण

अटल पूर्णांक ppc_spe_sha1_final(काष्ठा shash_desc *desc, u8 *out)
अणु
	काष्ठा sha1_state *sctx = shash_desc_ctx(desc);
	स्थिर अचिन्हित पूर्णांक offset = sctx->count & 0x3f;
	अक्षर *p = (अक्षर *)sctx->buffer + offset;
	पूर्णांक padlen;
	__be64 *pbits = (__be64 *)(((अक्षर *)&sctx->buffer) + 56);
	__be32 *dst = (__be32 *)out;

	padlen = 55 - offset;
	*p++ = 0x80;

	spe_begin();

	अगर (padlen < 0) अणु
		स_रखो(p, 0x00, padlen + माप (u64));
		ppc_spe_sha1_transक्रमm(sctx->state, sctx->buffer, 1);
		p = (अक्षर *)sctx->buffer;
		padlen = 56;
	पूर्ण

	स_रखो(p, 0, padlen);
	*pbits = cpu_to_be64(sctx->count << 3);
	ppc_spe_sha1_transक्रमm(sctx->state, sctx->buffer, 1);

	spe_end();

	dst[0] = cpu_to_be32(sctx->state[0]);
	dst[1] = cpu_to_be32(sctx->state[1]);
	dst[2] = cpu_to_be32(sctx->state[2]);
	dst[3] = cpu_to_be32(sctx->state[3]);
	dst[4] = cpu_to_be32(sctx->state[4]);

	ppc_sha1_clear_context(sctx);
	वापस 0;
पूर्ण

अटल पूर्णांक ppc_spe_sha1_export(काष्ठा shash_desc *desc, व्योम *out)
अणु
	काष्ठा sha1_state *sctx = shash_desc_ctx(desc);

	स_नकल(out, sctx, माप(*sctx));
	वापस 0;
पूर्ण

अटल पूर्णांक ppc_spe_sha1_import(काष्ठा shash_desc *desc, स्थिर व्योम *in)
अणु
	काष्ठा sha1_state *sctx = shash_desc_ctx(desc);

	स_नकल(sctx, in, माप(*sctx));
	वापस 0;
पूर्ण

अटल काष्ठा shash_alg alg = अणु
	.digestsize	=	SHA1_DIGEST_SIZE,
	.init		=	ppc_spe_sha1_init,
	.update		=	ppc_spe_sha1_update,
	.final		=	ppc_spe_sha1_final,
	.export		=	ppc_spe_sha1_export,
	.import		=	ppc_spe_sha1_import,
	.descsize	=	माप(काष्ठा sha1_state),
	.statesize	=	माप(काष्ठा sha1_state),
	.base		=	अणु
		.cra_name	=	"sha1",
		.cra_driver_name=	"sha1-ppc-spe",
		.cra_priority	=	300,
		.cra_blocksize	=	SHA1_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init ppc_spe_sha1_mod_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_shash(&alg);
पूर्ण

अटल व्योम __निकास ppc_spe_sha1_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&alg);
पूर्ण

module_init(ppc_spe_sha1_mod_init);
module_निकास(ppc_spe_sha1_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("SHA1 Secure Hash Algorithm, SPE optimized");

MODULE_ALIAS_CRYPTO("sha1");
MODULE_ALIAS_CRYPTO("sha1-ppc-spe");
