<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Cryptographic API.
 *
 * s390 implementation of the SHA1 Secure Hash Algorithm.
 *
 * Derived from cryptoapi implementation, adapted क्रम in-place
 * scatterlist पूर्णांकerface.  Originally based on the खुला करोमुख्य
 * implementation written by Steve Reid.
 *
 * s390 Version:
 *   Copyright IBM Corp. 2003, 2007
 *   Author(s): Thomas Spatzier
 *		Jan Glauber (jan.glauber@de.ibm.com)
 *
 * Derived from "crypto/sha1_generic.c"
 *   Copyright (c) Alan Smithee.
 *   Copyright (c) Andrew McDonald <andrew@mcकरोnald.org.uk>
 *   Copyright (c) Jean-Francois Dive <jef@linuxbe.org>
 */
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/cpufeature.h>
#समावेश <crypto/sha1.h>
#समावेश <यंत्र/cpacf.h>

#समावेश "sha.h"

अटल पूर्णांक s390_sha1_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा s390_sha_ctx *sctx = shash_desc_ctx(desc);

	sctx->state[0] = SHA1_H0;
	sctx->state[1] = SHA1_H1;
	sctx->state[2] = SHA1_H2;
	sctx->state[3] = SHA1_H3;
	sctx->state[4] = SHA1_H4;
	sctx->count = 0;
	sctx->func = CPACF_KIMD_SHA_1;

	वापस 0;
पूर्ण

अटल पूर्णांक s390_sha1_export(काष्ठा shash_desc *desc, व्योम *out)
अणु
	काष्ठा s390_sha_ctx *sctx = shash_desc_ctx(desc);
	काष्ठा sha1_state *octx = out;

	octx->count = sctx->count;
	स_नकल(octx->state, sctx->state, माप(octx->state));
	स_नकल(octx->buffer, sctx->buf, माप(octx->buffer));
	वापस 0;
पूर्ण

अटल पूर्णांक s390_sha1_import(काष्ठा shash_desc *desc, स्थिर व्योम *in)
अणु
	काष्ठा s390_sha_ctx *sctx = shash_desc_ctx(desc);
	स्थिर काष्ठा sha1_state *ictx = in;

	sctx->count = ictx->count;
	स_नकल(sctx->state, ictx->state, माप(ictx->state));
	स_नकल(sctx->buf, ictx->buffer, माप(ictx->buffer));
	sctx->func = CPACF_KIMD_SHA_1;
	वापस 0;
पूर्ण

अटल काष्ठा shash_alg alg = अणु
	.digestsize	=	SHA1_DIGEST_SIZE,
	.init		=	s390_sha1_init,
	.update		=	s390_sha_update,
	.final		=	s390_sha_final,
	.export		=	s390_sha1_export,
	.import		=	s390_sha1_import,
	.descsize	=	माप(काष्ठा s390_sha_ctx),
	.statesize	=	माप(काष्ठा sha1_state),
	.base		=	अणु
		.cra_name	=	"sha1",
		.cra_driver_name=	"sha1-s390",
		.cra_priority	=	300,
		.cra_blocksize	=	SHA1_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init sha1_s390_init(व्योम)
अणु
	अगर (!cpacf_query_func(CPACF_KIMD, CPACF_KIMD_SHA_1))
		वापस -ENODEV;
	वापस crypto_रेजिस्टर_shash(&alg);
पूर्ण

अटल व्योम __निकास sha1_s390_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&alg);
पूर्ण

module_cpu_feature_match(MSA, sha1_s390_init);
module_निकास(sha1_s390_fini);

MODULE_ALIAS_CRYPTO("sha1");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("SHA1 Secure Hash Algorithm");
