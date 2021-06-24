<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* ECDH key-agreement protocol
 *
 * Copyright (c) 2016, Intel Corporation
 * Authors: Salvator Benedetto <salvatore.benedetto@पूर्णांकel.com>
 */

#समावेश <linux/module.h>
#समावेश <crypto/पूर्णांकernal/kpp.h>
#समावेश <crypto/kpp.h>
#समावेश <crypto/ecdh.h>
#समावेश <linux/scatterlist.h>
#समावेश "ecc.h"

काष्ठा ecdh_ctx अणु
	अचिन्हित पूर्णांक curve_id;
	अचिन्हित पूर्णांक ndigits;
	u64 निजी_key[ECC_MAX_DIGITS];
पूर्ण;

अटल अंतरभूत काष्ठा ecdh_ctx *ecdh_get_ctx(काष्ठा crypto_kpp *tfm)
अणु
	वापस kpp_tfm_ctx(tfm);
पूर्ण

अटल पूर्णांक ecdh_set_secret(काष्ठा crypto_kpp *tfm, स्थिर व्योम *buf,
			   अचिन्हित पूर्णांक len)
अणु
	काष्ठा ecdh_ctx *ctx = ecdh_get_ctx(tfm);
	काष्ठा ecdh params;

	अगर (crypto_ecdh_decode_key(buf, len, &params) < 0 ||
	    params.key_size > माप(u64) * ctx->ndigits)
		वापस -EINVAL;

	अगर (!params.key || !params.key_size)
		वापस ecc_gen_privkey(ctx->curve_id, ctx->ndigits,
				       ctx->निजी_key);

	स_नकल(ctx->निजी_key, params.key, params.key_size);

	अगर (ecc_is_key_valid(ctx->curve_id, ctx->ndigits,
			     ctx->निजी_key, params.key_size) < 0) अणु
		memzero_explicit(ctx->निजी_key, params.key_size);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ecdh_compute_value(काष्ठा kpp_request *req)
अणु
	काष्ठा crypto_kpp *tfm = crypto_kpp_reqtfm(req);
	काष्ठा ecdh_ctx *ctx = ecdh_get_ctx(tfm);
	u64 *खुला_key;
	u64 *shared_secret = शून्य;
	व्योम *buf;
	माप_प्रकार copied, nbytes, खुला_key_sz;
	पूर्णांक ret = -ENOMEM;

	nbytes = ctx->ndigits << ECC_DIGITS_TO_BYTES_SHIFT;
	/* Public part is a poपूर्णांक thus it has both coordinates */
	खुला_key_sz = 2 * nbytes;

	खुला_key = kदो_स्मृति(खुला_key_sz, GFP_KERNEL);
	अगर (!खुला_key)
		वापस -ENOMEM;

	अगर (req->src) अणु
		shared_secret = kदो_स्मृति(nbytes, GFP_KERNEL);
		अगर (!shared_secret)
			जाओ मुक्त_pubkey;

		/* from here on it's invalid parameters */
		ret = -EINVAL;

		/* must have exactly two poपूर्णांकs to be on the curve */
		अगर (खुला_key_sz != req->src_len)
			जाओ मुक्त_all;

		copied = sg_copy_to_buffer(req->src,
					   sg_nents_क्रम_len(req->src,
							    खुला_key_sz),
					   खुला_key, खुला_key_sz);
		अगर (copied != खुला_key_sz)
			जाओ मुक्त_all;

		ret = crypto_ecdh_shared_secret(ctx->curve_id, ctx->ndigits,
						ctx->निजी_key, खुला_key,
						shared_secret);

		buf = shared_secret;
	पूर्ण अन्यथा अणु
		ret = ecc_make_pub_key(ctx->curve_id, ctx->ndigits,
				       ctx->निजी_key, खुला_key);
		buf = खुला_key;
		nbytes = खुला_key_sz;
	पूर्ण

	अगर (ret < 0)
		जाओ मुक्त_all;

	/* might want less than we've got */
	nbytes = min_t(माप_प्रकार, nbytes, req->dst_len);
	copied = sg_copy_from_buffer(req->dst, sg_nents_क्रम_len(req->dst,
								nbytes),
				     buf, nbytes);
	अगर (copied != nbytes)
		ret = -EINVAL;

	/* fall through */
मुक्त_all:
	kमुक्त_sensitive(shared_secret);
मुक्त_pubkey:
	kमुक्त(खुला_key);
	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक ecdh_max_size(काष्ठा crypto_kpp *tfm)
अणु
	काष्ठा ecdh_ctx *ctx = ecdh_get_ctx(tfm);

	/* Public key is made of two coordinates, add one to the left shअगरt */
	वापस ctx->ndigits << (ECC_DIGITS_TO_BYTES_SHIFT + 1);
पूर्ण

अटल पूर्णांक ecdh_nist_p192_init_tfm(काष्ठा crypto_kpp *tfm)
अणु
	काष्ठा ecdh_ctx *ctx = ecdh_get_ctx(tfm);

	ctx->curve_id = ECC_CURVE_NIST_P192;
	ctx->ndigits = ECC_CURVE_NIST_P192_DIGITS;

	वापस 0;
पूर्ण

अटल काष्ठा kpp_alg ecdh_nist_p192 = अणु
	.set_secret = ecdh_set_secret,
	.generate_खुला_key = ecdh_compute_value,
	.compute_shared_secret = ecdh_compute_value,
	.max_size = ecdh_max_size,
	.init = ecdh_nist_p192_init_tfm,
	.base = अणु
		.cra_name = "ecdh-nist-p192",
		.cra_driver_name = "ecdh-generic",
		.cra_priority = 100,
		.cra_module = THIS_MODULE,
		.cra_ctxsize = माप(काष्ठा ecdh_ctx),
	पूर्ण,
पूर्ण;

अटल पूर्णांक ecdh_nist_p256_init_tfm(काष्ठा crypto_kpp *tfm)
अणु
	काष्ठा ecdh_ctx *ctx = ecdh_get_ctx(tfm);

	ctx->curve_id = ECC_CURVE_NIST_P256;
	ctx->ndigits = ECC_CURVE_NIST_P256_DIGITS;

	वापस 0;
पूर्ण

अटल काष्ठा kpp_alg ecdh_nist_p256 = अणु
	.set_secret = ecdh_set_secret,
	.generate_खुला_key = ecdh_compute_value,
	.compute_shared_secret = ecdh_compute_value,
	.max_size = ecdh_max_size,
	.init = ecdh_nist_p256_init_tfm,
	.base = अणु
		.cra_name = "ecdh-nist-p256",
		.cra_driver_name = "ecdh-generic",
		.cra_priority = 100,
		.cra_module = THIS_MODULE,
		.cra_ctxsize = माप(काष्ठा ecdh_ctx),
	पूर्ण,
पूर्ण;

अटल bool ecdh_nist_p192_रेजिस्टरed;

अटल पूर्णांक ecdh_init(व्योम)
अणु
	पूर्णांक ret;

	ret = crypto_रेजिस्टर_kpp(&ecdh_nist_p192);
	ecdh_nist_p192_रेजिस्टरed = ret == 0;

	वापस crypto_रेजिस्टर_kpp(&ecdh_nist_p256);
पूर्ण

अटल व्योम ecdh_निकास(व्योम)
अणु
	अगर (ecdh_nist_p192_रेजिस्टरed)
		crypto_unरेजिस्टर_kpp(&ecdh_nist_p192);
	crypto_unरेजिस्टर_kpp(&ecdh_nist_p256);
पूर्ण

subsys_initcall(ecdh_init);
module_निकास(ecdh_निकास);
MODULE_ALIAS_CRYPTO("ecdh");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("ECDH generic algorithm");
