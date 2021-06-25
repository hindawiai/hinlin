<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Cryptographic API.
 *
 * s390 implementation of the SHA512 and SHA384 Secure Hash Algorithm.
 *
 * Copyright IBM Corp. 2019
 * Author(s): Joerg Schmidbauer (jschmidb@de.ibm.com)
 */
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/cpufeature.h>
#समावेश <crypto/sha3.h>
#समावेश <यंत्र/cpacf.h>

#समावेश "sha.h"

अटल पूर्णांक sha3_512_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा s390_sha_ctx *sctx = shash_desc_ctx(desc);

	स_रखो(sctx->state, 0, माप(sctx->state));
	sctx->count = 0;
	sctx->func = CPACF_KIMD_SHA3_512;

	वापस 0;
पूर्ण

अटल पूर्णांक sha3_512_export(काष्ठा shash_desc *desc, व्योम *out)
अणु
	काष्ठा s390_sha_ctx *sctx = shash_desc_ctx(desc);
	काष्ठा sha3_state *octx = out;

	octx->rsiz = sctx->count;
	octx->rsizw = sctx->count >> 32;

	स_नकल(octx->st, sctx->state, माप(octx->st));
	स_नकल(octx->buf, sctx->buf, माप(octx->buf));

	वापस 0;
पूर्ण

अटल पूर्णांक sha3_512_import(काष्ठा shash_desc *desc, स्थिर व्योम *in)
अणु
	काष्ठा s390_sha_ctx *sctx = shash_desc_ctx(desc);
	स्थिर काष्ठा sha3_state *ictx = in;

	अगर (unlikely(ictx->rsizw))
		वापस -दुस्फल;
	sctx->count = ictx->rsiz;

	स_नकल(sctx->state, ictx->st, माप(ictx->st));
	स_नकल(sctx->buf, ictx->buf, माप(ictx->buf));
	sctx->func = CPACF_KIMD_SHA3_512;

	वापस 0;
पूर्ण

अटल पूर्णांक sha3_384_import(काष्ठा shash_desc *desc, स्थिर व्योम *in)
अणु
	काष्ठा s390_sha_ctx *sctx = shash_desc_ctx(desc);
	स्थिर काष्ठा sha3_state *ictx = in;

	अगर (unlikely(ictx->rsizw))
		वापस -दुस्फल;
	sctx->count = ictx->rsiz;

	स_नकल(sctx->state, ictx->st, माप(ictx->st));
	स_नकल(sctx->buf, ictx->buf, माप(ictx->buf));
	sctx->func = CPACF_KIMD_SHA3_384;

	वापस 0;
पूर्ण

अटल काष्ठा shash_alg sha3_512_alg = अणु
	.digestsize	=	SHA3_512_DIGEST_SIZE,
	.init		=	sha3_512_init,
	.update		=	s390_sha_update,
	.final		=	s390_sha_final,
	.export		=	sha3_512_export,
	.import		=	sha3_512_import,
	.descsize	=	माप(काष्ठा s390_sha_ctx),
	.statesize	=	माप(काष्ठा sha3_state),
	.base		=	अणु
		.cra_name	 =	"sha3-512",
		.cra_driver_name =	"sha3-512-s390",
		.cra_priority	 =	300,
		.cra_blocksize	 =	SHA3_512_BLOCK_SIZE,
		.cra_module	 =	THIS_MODULE,
	पूर्ण
पूर्ण;

MODULE_ALIAS_CRYPTO("sha3-512");

अटल पूर्णांक sha3_384_init(काष्ठा shash_desc *desc)
अणु
	काष्ठा s390_sha_ctx *sctx = shash_desc_ctx(desc);

	स_रखो(sctx->state, 0, माप(sctx->state));
	sctx->count = 0;
	sctx->func = CPACF_KIMD_SHA3_384;

	वापस 0;
पूर्ण

अटल काष्ठा shash_alg sha3_384_alg = अणु
	.digestsize	=	SHA3_384_DIGEST_SIZE,
	.init		=	sha3_384_init,
	.update		=	s390_sha_update,
	.final		=	s390_sha_final,
	.export		=	sha3_512_export, /* same as क्रम 512 */
	.import		=	sha3_384_import, /* function code dअगरferent! */
	.descsize	=	माप(काष्ठा s390_sha_ctx),
	.statesize	=	माप(काष्ठा sha3_state),
	.base		=	अणु
		.cra_name	 =	"sha3-384",
		.cra_driver_name =	"sha3-384-s390",
		.cra_priority	 =	300,
		.cra_blocksize	 =	SHA3_384_BLOCK_SIZE,
		.cra_ctxsize	 =	माप(काष्ठा s390_sha_ctx),
		.cra_module	 =	THIS_MODULE,
	पूर्ण
पूर्ण;

MODULE_ALIAS_CRYPTO("sha3-384");

अटल पूर्णांक __init init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!cpacf_query_func(CPACF_KIMD, CPACF_KIMD_SHA3_512))
		वापस -ENODEV;
	ret = crypto_रेजिस्टर_shash(&sha3_512_alg);
	अगर (ret < 0)
		जाओ out;
	ret = crypto_रेजिस्टर_shash(&sha3_384_alg);
	अगर (ret < 0)
		crypto_unरेजिस्टर_shash(&sha3_512_alg);
out:
	वापस ret;
पूर्ण

अटल व्योम __निकास fini(व्योम)
अणु
	crypto_unरेजिस्टर_shash(&sha3_512_alg);
	crypto_unरेजिस्टर_shash(&sha3_384_alg);
पूर्ण

module_cpu_feature_match(MSA, init);
module_निकास(fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("SHA3-512 and SHA3-384 Secure Hash Algorithm");
