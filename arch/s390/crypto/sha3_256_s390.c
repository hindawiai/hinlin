<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Cryptographic API.
 *
 * s390 implementation of the SHA256 and SHA224 Secure Hash Algorithm.
 *
 * s390 Version:
 *   Copyright IBM Corp. 2019
 *   Author(s): Joerg Schmidbauer (jschmidb@de.ibm.com)
 */
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/cpufeature.h>
#समावेश <crypto/sha3.h>
#समावेश <यंत्र/cpacf.h>

#समावेश "sha.h"

अटल पूर्णांक sha3_256_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा s390_sha_ctx *sctx = shash_desc_ctx(desc);

	स_रखो(sctx->state, 0, माप(sctx->state));
	sctx->count = 0;
	sctx->func = CPACF_KIMD_SHA3_256;

	वापस 0;
पूर्ण

अटल पूर्णांक sha3_256_export(काष्ठा shash_desc *desc, व्योम *out)
अणु
	काष्ठा s390_sha_ctx *sctx = shash_desc_ctx(desc);
	काष्ठा sha3_state *octx = out;

	octx->rsiz = sctx->count;
	स_नकल(octx->st, sctx->state, माप(octx->st));
	स_नकल(octx->buf, sctx->buf, माप(octx->buf));

	वापस 0;
पूर्ण

अटल पूर्णांक sha3_256_import(काष्ठा shash_desc *desc, स्थिर व्योम *in)
अणु
	काष्ठा s390_sha_ctx *sctx = shash_desc_ctx(desc);
	स्थिर काष्ठा sha3_state *ictx = in;

	sctx->count = ictx->rsiz;
	स_नकल(sctx->state, ictx->st, माप(ictx->st));
	स_नकल(sctx->buf, ictx->buf, माप(ictx->buf));
	sctx->func = CPACF_KIMD_SHA3_256;

	वापस 0;
पूर्ण

अटल पूर्णांक sha3_224_import(काष्ठा shash_desc *desc, स्थिर व्योम *in)
अणु
	काष्ठा s390_sha_ctx *sctx = shash_desc_ctx(desc);
	स्थिर काष्ठा sha3_state *ictx = in;

	sctx->count = ictx->rsiz;
	स_नकल(sctx->state, ictx->st, माप(ictx->st));
	स_नकल(sctx->buf, ictx->buf, माप(ictx->buf));
	sctx->func = CPACF_KIMD_SHA3_224;

	वापस 0;
पूर्ण

अटल काष्ठा shash_alg sha3_256_alg = अणु
	.digestsize	=	SHA3_256_DIGEST_SIZE,	   /* = 32 */
	.init		=	sha3_256_init,
	.update		=	s390_sha_update,
	.final		=	s390_sha_final,
	.export		=	sha3_256_export,
	.import		=	sha3_256_import,
	.descsize	=	माप(काष्ठा s390_sha_ctx),
	.statesize	=	माप(काष्ठा sha3_state),
	.base		=	अणु
		.cra_name	 =	"sha3-256",
		.cra_driver_name =	"sha3-256-s390",
		.cra_priority	 =	300,
		.cra_blocksize	 =	SHA3_256_BLOCK_SIZE,
		.cra_module	 =	THIS_MODULE,
	पूर्ण
पूर्ण;

अटल पूर्णांक sha3_224_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा s390_sha_ctx *sctx = shash_desc_ctx(desc);

	स_रखो(sctx->state, 0, माप(sctx->state));
	sctx->count = 0;
	sctx->func = CPACF_KIMD_SHA3_224;

	वापस 0;
पूर्ण

अटल काष्ठा shash_alg sha3_224_alg = अणु
	.digestsize	=	SHA3_224_DIGEST_SIZE,
	.init		=	sha3_224_init,
	.update		=	s390_sha_update,
	.final		=	s390_sha_final,
	.export		=	sha3_256_export, /* same as क्रम 256 */
	.import		=	sha3_224_import, /* function code dअगरferent! */
	.descsize	=	माप(काष्ठा s390_sha_ctx),
	.statesize	=	माप(काष्ठा sha3_state),
	.base		=	अणु
		.cra_name	 =	"sha3-224",
		.cra_driver_name =	"sha3-224-s390",
		.cra_priority	 =	300,
		.cra_blocksize	 =	SHA3_224_BLOCK_SIZE,
		.cra_module	 =	THIS_MODULE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init sha3_256_s390_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!cpacf_query_func(CPACF_KIMD, CPACF_KIMD_SHA3_256))
		वापस -ENODEV;

	ret = crypto_रेजिस्टर_shash(&sha3_256_alg);
	अगर (ret < 0)
		जाओ out;

	ret = crypto_रेजिस्टर_shash(&sha3_224_alg);
	अगर (ret < 0)
		crypto_unरेजिस्टर_shash(&sha3_256_alg);
out:
	वापस ret;
पूर्ण

अटल व्योम __निकास sha3_256_s390_fini(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&sha3_224_alg);
	crypto_unरेजिस्टर_shash(&sha3_256_alg);
पूर्ण

module_cpu_feature_match(MSA, sha3_256_s390_init);
module_निकास(sha3_256_s390_fini);

MODULE_ALIAS_CRYPTO("sha3-256");
MODULE_ALIAS_CRYPTO("sha3-224");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("SHA3-256 and SHA3-224 Secure Hash Algorithm");
