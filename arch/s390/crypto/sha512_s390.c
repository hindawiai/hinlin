<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Cryptographic API.
 *
 * s390 implementation of the SHA512 and SHA38 Secure Hash Algorithm.
 *
 * Copyright IBM Corp. 2007
 * Author(s): Jan Glauber (jang@de.ibm.com)
 */
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/sha2.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/cpufeature.h>
#समावेश <यंत्र/cpacf.h>

#समावेश "sha.h"

अटल पूर्णांक sha512_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा s390_sha_ctx *ctx = shash_desc_ctx(desc);

	*(__u64 *)&ctx->state[0] = 0x6a09e667f3bcc908ULL;
	*(__u64 *)&ctx->state[2] = 0xbb67ae8584caa73bULL;
	*(__u64 *)&ctx->state[4] = 0x3c6ef372fe94f82bULL;
	*(__u64 *)&ctx->state[6] = 0xa54ff53a5f1d36f1ULL;
	*(__u64 *)&ctx->state[8] = 0x510e527fade682d1ULL;
	*(__u64 *)&ctx->state[10] = 0x9b05688c2b3e6c1fULL;
	*(__u64 *)&ctx->state[12] = 0x1f83d9abfb41bd6bULL;
	*(__u64 *)&ctx->state[14] = 0x5be0cd19137e2179ULL;
	ctx->count = 0;
	ctx->func = CPACF_KIMD_SHA_512;

	वापस 0;
पूर्ण

अटल पूर्णांक sha512_export(काष्ठा shash_desc *desc, व्योम *out)
अणु
	काष्ठा s390_sha_ctx *sctx = shash_desc_ctx(desc);
	काष्ठा sha512_state *octx = out;

	octx->count[0] = sctx->count;
	octx->count[1] = 0;
	स_नकल(octx->state, sctx->state, माप(octx->state));
	स_नकल(octx->buf, sctx->buf, माप(octx->buf));
	वापस 0;
पूर्ण

अटल पूर्णांक sha512_import(काष्ठा shash_desc *desc, स्थिर व्योम *in)
अणु
	काष्ठा s390_sha_ctx *sctx = shash_desc_ctx(desc);
	स्थिर काष्ठा sha512_state *ictx = in;

	अगर (unlikely(ictx->count[1]))
		वापस -दुस्फल;
	sctx->count = ictx->count[0];

	स_नकल(sctx->state, ictx->state, माप(ictx->state));
	स_नकल(sctx->buf, ictx->buf, माप(ictx->buf));
	sctx->func = CPACF_KIMD_SHA_512;
	वापस 0;
पूर्ण

अटल काष्ठा shash_alg sha512_alg = अणु
	.digestsize	=	SHA512_DIGEST_SIZE,
	.init		=	sha512_init,
	.update		=	s390_sha_update,
	.final		=	s390_sha_final,
	.export		=	sha512_export,
	.import		=	sha512_import,
	.descsize	=	माप(काष्ठा s390_sha_ctx),
	.statesize	=	माप(काष्ठा sha512_state),
	.base		=	अणु
		.cra_name	=	"sha512",
		.cra_driver_name=	"sha512-s390",
		.cra_priority	=	300,
		.cra_blocksize	=	SHA512_BLOCK_SIZE,
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण;

MODULE_ALIAS_CRYPTO("sha512");

अटल पूर्णांक sha384_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा s390_sha_ctx *ctx = shash_desc_ctx(desc);

	*(__u64 *)&ctx->state[0] = 0xcbbb9d5dc1059ed8ULL;
	*(__u64 *)&ctx->state[2] = 0x629a292a367cd507ULL;
	*(__u64 *)&ctx->state[4] = 0x9159015a3070dd17ULL;
	*(__u64 *)&ctx->state[6] = 0x152fecd8f70e5939ULL;
	*(__u64 *)&ctx->state[8] = 0x67332667ffc00b31ULL;
	*(__u64 *)&ctx->state[10] = 0x8eb44a8768581511ULL;
	*(__u64 *)&ctx->state[12] = 0xdb0c2e0d64f98fa7ULL;
	*(__u64 *)&ctx->state[14] = 0x47b5481dbefa4fa4ULL;
	ctx->count = 0;
	ctx->func = CPACF_KIMD_SHA_512;

	वापस 0;
पूर्ण

अटल काष्ठा shash_alg sha384_alg = अणु
	.digestsize	=	SHA384_DIGEST_SIZE,
	.init		=	sha384_init,
	.update		=	s390_sha_update,
	.final		=	s390_sha_final,
	.export		=	sha512_export,
	.import		=	sha512_import,
	.descsize	=	माप(काष्ठा s390_sha_ctx),
	.statesize	=	माप(काष्ठा sha512_state),
	.base		=	अणु
		.cra_name	=	"sha384",
		.cra_driver_name=	"sha384-s390",
		.cra_priority	=	300,
		.cra_blocksize	=	SHA384_BLOCK_SIZE,
		.cra_ctxsize	=	माप(काष्ठा s390_sha_ctx),
		.cra_module	=	THIS_MODULE,
	पूर्ण
पूर्ण;

MODULE_ALIAS_CRYPTO("sha384");

अटल पूर्णांक __init init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!cpacf_query_func(CPACF_KIMD, CPACF_KIMD_SHA_512))
		वापस -ENODEV;
	अगर ((ret = crypto_रेजिस्टर_shash(&sha512_alg)) < 0)
		जाओ out;
	अगर ((ret = crypto_रेजिस्टर_shash(&sha384_alg)) < 0)
		crypto_unरेजिस्टर_shash(&sha512_alg);
out:
	वापस ret;
पूर्ण

अटल व्योम __निकास fini(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&sha512_alg);
	crypto_unरेजिस्टर_shash(&sha384_alg);
पूर्ण

module_cpu_feature_match(MSA, init);
module_निकास(fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("SHA512 and SHA-384 Secure Hash Algorithm");
