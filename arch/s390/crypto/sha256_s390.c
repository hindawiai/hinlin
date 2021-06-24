<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Cryptographic API.
 *
 * s390 implementation of the SHA256 and SHA224 Secure Hash Algorithm.
 *
 * s390 Version:
 *   Copyright IBM Corp. 2005, 2011
 *   Author(s): Jan Glauber (jang@de.ibm.com)
 */
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/cpufeature.h>
#समावेश <crypto/sha2.h>
#समावेश <यंत्र/cpacf.h>

#समावेश "sha.h"

अटल पूर्णांक s390_sha256_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा s390_sha_ctx *sctx = shash_desc_ctx(desc);

	sctx->state[0] = SHA256_H0;
	sctx->state[1] = SHA256_H1;
	sctx->state[2] = SHA256_H2;
	sctx->state[3] = SHA256_H3;
	sctx->state[4] = SHA256_H4;
	sctx->state[5] = SHA256_H5;
	sctx->state[6] = SHA256_H6;
	sctx->state[7] = SHA256_H7;
	sctx->count = 0;
	sctx->func = CPACF_KIMD_SHA_256;

	वापस 0;
पूर्ण

अटल पूर्णांक sha256_export(काष्ठा shash_desc *desc, व्योम *out)
अणु
	काष्ठा s390_sha_ctx *sctx = shash_desc_ctx(desc);
	काष्ठा sha256_state *octx = out;

	octx->count = sctx->count;
	स_नकल(octx->state, sctx->state, माप(octx->state));
	स_नकल(octx->buf, sctx->buf, माप(octx->buf));
	वापस 0;
पूर्ण

अटल पूर्णांक sha256_import(काष्ठा shash_desc *desc, स्थिर व्योम *in)
अणु
	काष्ठा s390_sha_ctx *sctx = shash_desc_ctx(desc);
	स्थिर काष्ठा sha256_state *ictx = in;

	sctx->count = ictx->count;
	स_नकल(sctx->state, ictx->state, माप(ictx->state));
	स_नकल(sctx->buf, ictx->buf, माप(ictx->buf));
	sctx->func = CPACF_KIMD_SHA_256;
	वापस 0;
पूर्ण

अटल काष्ठा shash_alg sha256_alg = अणु
	.digestsize	=	SHA256_DIGEST_SIZE,
	.init		=	s390_sha256_init,
	.update		=	s390_sha_update,
	.final		=	s390_sha_final,
	.export		=	sha256_export,
	.import		=	sha256_import,
	.descsize	=	माप(काष्ठा s390_sha_ctx),
	.statesize	=	माप(काष्ठा sha256_state),
	.base		=	अणु
		.cra_name	=	"sha256",
		.cra_driver_name=	"sha256-s390",
		.cra_priority	=	300,
		.cra_blocksize	=	SHA256_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण;

अटल पूर्णांक s390_sha224_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा s390_sha_ctx *sctx = shash_desc_ctx(desc);

	sctx->state[0] = SHA224_H0;
	sctx->state[1] = SHA224_H1;
	sctx->state[2] = SHA224_H2;
	sctx->state[3] = SHA224_H3;
	sctx->state[4] = SHA224_H4;
	sctx->state[5] = SHA224_H5;
	sctx->state[6] = SHA224_H6;
	sctx->state[7] = SHA224_H7;
	sctx->count = 0;
	sctx->func = CPACF_KIMD_SHA_256;

	वापस 0;
पूर्ण

अटल काष्ठा shash_alg sha224_alg = अणु
	.digestsize	=	SHA224_DIGEST_SIZE,
	.init		=	s390_sha224_init,
	.update		=	s390_sha_update,
	.final		=	s390_sha_final,
	.export		=	sha256_export,
	.import		=	sha256_import,
	.descsize	=	माप(काष्ठा s390_sha_ctx),
	.statesize	=	माप(काष्ठा sha256_state),
	.base		=	अणु
		.cra_name	=	"sha224",
		.cra_driver_name=	"sha224-s390",
		.cra_priority	=	300,
		.cra_blocksize	=	SHA224_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init sha256_s390_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!cpacf_query_func(CPACF_KIMD, CPACF_KIMD_SHA_256))
		वापस -ENODEV;
	ret = crypto_रेजिस्टर_shash(&sha256_alg);
	अगर (ret < 0)
		जाओ out;
	ret = crypto_रेजिस्टर_shash(&sha224_alg);
	अगर (ret < 0)
		crypto_unरेजिस्टर_shash(&sha256_alg);
out:
	वापस ret;
पूर्ण

अटल व्योम __निकास sha256_s390_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&sha224_alg);
	crypto_unरेजिस्टर_shash(&sha256_alg);
पूर्ण

module_cpu_feature_match(MSA, sha256_s390_init);
module_निकास(sha256_s390_fini);

MODULE_ALIAS_CRYPTO("sha256");
MODULE_ALIAS_CRYPTO("sha224");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("SHA256 and SHA224 Secure Hash Algorithm");
