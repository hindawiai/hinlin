<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 2021 IBM Corporation
 */

#समावेश <linux/module.h>
#समावेश <crypto/पूर्णांकernal/akcipher.h>
#समावेश <crypto/akcipher.h>
#समावेश <crypto/ecdh.h>
#समावेश <linux/asn1_decoder.h>
#समावेश <linux/scatterlist.h>

#समावेश "ecc.h"
#समावेश "ecdsasignature.asn1.h"

काष्ठा ecc_ctx अणु
	अचिन्हित पूर्णांक curve_id;
	स्थिर काष्ठा ecc_curve *curve;

	bool pub_key_set;
	u64 x[ECC_MAX_DIGITS]; /* pub key x and y coordinates */
	u64 y[ECC_MAX_DIGITS];
	काष्ठा ecc_poपूर्णांक pub_key;
पूर्ण;

काष्ठा ecdsa_signature_ctx अणु
	स्थिर काष्ठा ecc_curve *curve;
	u64 r[ECC_MAX_DIGITS];
	u64 s[ECC_MAX_DIGITS];
पूर्ण;

/*
 * Get the r and s components of a signature from the X509 certअगरicate.
 */
अटल पूर्णांक ecdsa_get_signature_rs(u64 *dest, माप_प्रकार hdrlen, अचिन्हित अक्षर tag,
				  स्थिर व्योम *value, माप_प्रकार vlen, अचिन्हित पूर्णांक ndigits)
अणु
	माप_प्रकार keylen = ndigits * माप(u64);
	sमाप_प्रकार dअगरf = vlen - keylen;
	स्थिर अक्षर *d = value;
	u8 rs[ECC_MAX_BYTES];

	अगर (!value || !vlen)
		वापस -EINVAL;

	/* dअगरf = 0: 'value' has exacly the right size
	 * dअगरf > 0: 'value' has too many bytes; one leading zero is allowed that
	 *           makes the value a positive पूर्णांकeger; error on more
	 * dअगरf < 0: 'value' is missing leading zeros, which we add
	 */
	अगर (dअगरf > 0) अणु
		/* skip over leading zeros that make 'value' a positive पूर्णांक */
		अगर (*d == 0) अणु
			vlen -= 1;
			dअगरf--;
			d++;
		पूर्ण
		अगर (dअगरf)
			वापस -EINVAL;
	पूर्ण
	अगर (-dअगरf >= keylen)
		वापस -EINVAL;

	अगर (dअगरf) अणु
		/* leading zeros not given in 'value' */
		स_रखो(rs, 0, -dअगरf);
	पूर्ण

	स_नकल(&rs[-dअगरf], d, vlen);

	ecc_swap_digits((u64 *)rs, dest, ndigits);

	वापस 0;
पूर्ण

पूर्णांक ecdsa_get_signature_r(व्योम *context, माप_प्रकार hdrlen, अचिन्हित अक्षर tag,
			  स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा ecdsa_signature_ctx *sig = context;

	वापस ecdsa_get_signature_rs(sig->r, hdrlen, tag, value, vlen,
				      sig->curve->g.ndigits);
पूर्ण

पूर्णांक ecdsa_get_signature_s(व्योम *context, माप_प्रकार hdrlen, अचिन्हित अक्षर tag,
			  स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा ecdsa_signature_ctx *sig = context;

	वापस ecdsa_get_signature_rs(sig->s, hdrlen, tag, value, vlen,
				      sig->curve->g.ndigits);
पूर्ण

अटल पूर्णांक _ecdsa_verअगरy(काष्ठा ecc_ctx *ctx, स्थिर u64 *hash, स्थिर u64 *r, स्थिर u64 *s)
अणु
	स्थिर काष्ठा ecc_curve *curve = ctx->curve;
	अचिन्हित पूर्णांक ndigits = curve->g.ndigits;
	u64 s1[ECC_MAX_DIGITS];
	u64 u1[ECC_MAX_DIGITS];
	u64 u2[ECC_MAX_DIGITS];
	u64 x1[ECC_MAX_DIGITS];
	u64 y1[ECC_MAX_DIGITS];
	काष्ठा ecc_poपूर्णांक res = ECC_POINT_INIT(x1, y1, ndigits);

	/* 0 < r < n  and 0 < s < n */
	अगर (vli_is_zero(r, ndigits) || vli_cmp(r, curve->n, ndigits) >= 0 ||
	    vli_is_zero(s, ndigits) || vli_cmp(s, curve->n, ndigits) >= 0)
		वापस -EBADMSG;

	/* hash is given */
	pr_devel("hash : %016llx %016llx ... %016llx\n",
		 hash[ndigits - 1], hash[ndigits - 2], hash[0]);

	/* s1 = (s^-1) mod n */
	vli_mod_inv(s1, s, curve->n, ndigits);
	/* u1 = (hash * s1) mod n */
	vli_mod_mult_slow(u1, hash, s1, curve->n, ndigits);
	/* u2 = (r * s1) mod n */
	vli_mod_mult_slow(u2, r, s1, curve->n, ndigits);
	/* res = u1*G + u2 * pub_key */
	ecc_poपूर्णांक_mult_shamir(&res, u1, &curve->g, u2, &ctx->pub_key, curve);

	/* res.x = res.x mod n (अगर res.x > order) */
	अगर (unlikely(vli_cmp(res.x, curve->n, ndigits) == 1))
		/* faster alternative क्रम NIST p384, p256 & p192 */
		vli_sub(res.x, res.x, curve->n, ndigits);

	अगर (!vli_cmp(res.x, r, ndigits))
		वापस 0;

	वापस -EKEYREJECTED;
पूर्ण

/*
 * Verअगरy an ECDSA signature.
 */
अटल पूर्णांक ecdsa_verअगरy(काष्ठा akcipher_request *req)
अणु
	काष्ठा crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	काष्ठा ecc_ctx *ctx = akcipher_tfm_ctx(tfm);
	माप_प्रकार keylen = ctx->curve->g.ndigits * माप(u64);
	काष्ठा ecdsa_signature_ctx sig_ctx = अणु
		.curve = ctx->curve,
	पूर्ण;
	u8 rawhash[ECC_MAX_BYTES];
	u64 hash[ECC_MAX_DIGITS];
	अचिन्हित अक्षर *buffer;
	sमाप_प्रकार dअगरf;
	पूर्णांक ret;

	अगर (unlikely(!ctx->pub_key_set))
		वापस -EINVAL;

	buffer = kदो_स्मृति(req->src_len + req->dst_len, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	sg_pcopy_to_buffer(req->src,
		sg_nents_क्रम_len(req->src, req->src_len + req->dst_len),
		buffer, req->src_len + req->dst_len, 0);

	ret = asn1_ber_decoder(&ecdsasignature_decoder, &sig_ctx,
			       buffer, req->src_len);
	अगर (ret < 0)
		जाओ error;

	/* अगर the hash is लघुer then we will add leading zeros to fit to ndigits */
	dअगरf = keylen - req->dst_len;
	अगर (dअगरf >= 0) अणु
		अगर (dअगरf)
			स_रखो(rawhash, 0, dअगरf);
		स_नकल(&rawhash[dअगरf], buffer + req->src_len, req->dst_len);
	पूर्ण अन्यथा अगर (dअगरf < 0) अणु
		/* given hash is दीर्घer, we take the left-most bytes */
		स_नकल(&rawhash, buffer + req->src_len, keylen);
	पूर्ण

	ecc_swap_digits((u64 *)rawhash, hash, ctx->curve->g.ndigits);

	ret = _ecdsa_verअगरy(ctx, hash, sig_ctx.r, sig_ctx.s);

error:
	kमुक्त(buffer);

	वापस ret;
पूर्ण

अटल पूर्णांक ecdsa_ecc_ctx_init(काष्ठा ecc_ctx *ctx, अचिन्हित पूर्णांक curve_id)
अणु
	ctx->curve_id = curve_id;
	ctx->curve = ecc_get_curve(curve_id);
	अगर (!ctx->curve)
		वापस -EINVAL;

	वापस 0;
पूर्ण


अटल व्योम ecdsa_ecc_ctx_deinit(काष्ठा ecc_ctx *ctx)
अणु
	ctx->pub_key_set = false;
पूर्ण

अटल पूर्णांक ecdsa_ecc_ctx_reset(काष्ठा ecc_ctx *ctx)
अणु
	अचिन्हित पूर्णांक curve_id = ctx->curve_id;
	पूर्णांक ret;

	ecdsa_ecc_ctx_deinit(ctx);
	ret = ecdsa_ecc_ctx_init(ctx, curve_id);
	अगर (ret == 0)
		ctx->pub_key = ECC_POINT_INIT(ctx->x, ctx->y,
					      ctx->curve->g.ndigits);
	वापस ret;
पूर्ण

/*
 * Set the खुला key given the raw uncompressed key data from an X509
 * certअगरicate. The key data contain the concatenated X and Y coordinates of
 * the खुला key.
 */
अटल पूर्णांक ecdsa_set_pub_key(काष्ठा crypto_akcipher *tfm, स्थिर व्योम *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा ecc_ctx *ctx = akcipher_tfm_ctx(tfm);
	स्थिर अचिन्हित अक्षर *d = key;
	स्थिर u64 *digits = (स्थिर u64 *)&d[1];
	अचिन्हित पूर्णांक ndigits;
	पूर्णांक ret;

	ret = ecdsa_ecc_ctx_reset(ctx);
	अगर (ret < 0)
		वापस ret;

	अगर (keylen < 1 || (((keylen - 1) >> 1) % माप(u64)) != 0)
		वापस -EINVAL;
	/* we only accept uncompressed क्रमmat indicated by '4' */
	अगर (d[0] != 4)
		वापस -EINVAL;

	keylen--;
	ndigits = (keylen >> 1) / माप(u64);
	अगर (ndigits != ctx->curve->g.ndigits)
		वापस -EINVAL;

	ecc_swap_digits(digits, ctx->pub_key.x, ndigits);
	ecc_swap_digits(&digits[ndigits], ctx->pub_key.y, ndigits);
	ret = ecc_is_pubkey_valid_full(ctx->curve, &ctx->pub_key);

	ctx->pub_key_set = ret == 0;

	वापस ret;
पूर्ण

अटल व्योम ecdsa_निकास_tfm(काष्ठा crypto_akcipher *tfm)
अणु
	काष्ठा ecc_ctx *ctx = akcipher_tfm_ctx(tfm);

	ecdsa_ecc_ctx_deinit(ctx);
पूर्ण

अटल अचिन्हित पूर्णांक ecdsa_max_size(काष्ठा crypto_akcipher *tfm)
अणु
	काष्ठा ecc_ctx *ctx = akcipher_tfm_ctx(tfm);

	वापस ctx->pub_key.ndigits << ECC_DIGITS_TO_BYTES_SHIFT;
पूर्ण

अटल पूर्णांक ecdsa_nist_p384_init_tfm(काष्ठा crypto_akcipher *tfm)
अणु
	काष्ठा ecc_ctx *ctx = akcipher_tfm_ctx(tfm);

	वापस ecdsa_ecc_ctx_init(ctx, ECC_CURVE_NIST_P384);
पूर्ण

अटल काष्ठा akcipher_alg ecdsa_nist_p384 = अणु
	.verअगरy = ecdsa_verअगरy,
	.set_pub_key = ecdsa_set_pub_key,
	.max_size = ecdsa_max_size,
	.init = ecdsa_nist_p384_init_tfm,
	.निकास = ecdsa_निकास_tfm,
	.base = अणु
		.cra_name = "ecdsa-nist-p384",
		.cra_driver_name = "ecdsa-nist-p384-generic",
		.cra_priority = 100,
		.cra_module = THIS_MODULE,
		.cra_ctxsize = माप(काष्ठा ecc_ctx),
	पूर्ण,
पूर्ण;

अटल पूर्णांक ecdsa_nist_p256_init_tfm(काष्ठा crypto_akcipher *tfm)
अणु
	काष्ठा ecc_ctx *ctx = akcipher_tfm_ctx(tfm);

	वापस ecdsa_ecc_ctx_init(ctx, ECC_CURVE_NIST_P256);
पूर्ण

अटल काष्ठा akcipher_alg ecdsa_nist_p256 = अणु
	.verअगरy = ecdsa_verअगरy,
	.set_pub_key = ecdsa_set_pub_key,
	.max_size = ecdsa_max_size,
	.init = ecdsa_nist_p256_init_tfm,
	.निकास = ecdsa_निकास_tfm,
	.base = अणु
		.cra_name = "ecdsa-nist-p256",
		.cra_driver_name = "ecdsa-nist-p256-generic",
		.cra_priority = 100,
		.cra_module = THIS_MODULE,
		.cra_ctxsize = माप(काष्ठा ecc_ctx),
	पूर्ण,
पूर्ण;

अटल पूर्णांक ecdsa_nist_p192_init_tfm(काष्ठा crypto_akcipher *tfm)
अणु
	काष्ठा ecc_ctx *ctx = akcipher_tfm_ctx(tfm);

	वापस ecdsa_ecc_ctx_init(ctx, ECC_CURVE_NIST_P192);
पूर्ण

अटल काष्ठा akcipher_alg ecdsa_nist_p192 = अणु
	.verअगरy = ecdsa_verअगरy,
	.set_pub_key = ecdsa_set_pub_key,
	.max_size = ecdsa_max_size,
	.init = ecdsa_nist_p192_init_tfm,
	.निकास = ecdsa_निकास_tfm,
	.base = अणु
		.cra_name = "ecdsa-nist-p192",
		.cra_driver_name = "ecdsa-nist-p192-generic",
		.cra_priority = 100,
		.cra_module = THIS_MODULE,
		.cra_ctxsize = माप(काष्ठा ecc_ctx),
	पूर्ण,
पूर्ण;
अटल bool ecdsa_nist_p192_रेजिस्टरed;

अटल पूर्णांक ecdsa_init(व्योम)
अणु
	पूर्णांक ret;

	/* NIST p192 may not be available in FIPS mode */
	ret = crypto_रेजिस्टर_akcipher(&ecdsa_nist_p192);
	ecdsa_nist_p192_रेजिस्टरed = ret == 0;

	ret = crypto_रेजिस्टर_akcipher(&ecdsa_nist_p256);
	अगर (ret)
		जाओ nist_p256_error;

	ret = crypto_रेजिस्टर_akcipher(&ecdsa_nist_p384);
	अगर (ret)
		जाओ nist_p384_error;

	वापस 0;

nist_p384_error:
	crypto_unरेजिस्टर_akcipher(&ecdsa_nist_p256);

nist_p256_error:
	अगर (ecdsa_nist_p192_रेजिस्टरed)
		crypto_unरेजिस्टर_akcipher(&ecdsa_nist_p192);
	वापस ret;
पूर्ण

अटल व्योम ecdsa_निकास(व्योम)
अणु
	अगर (ecdsa_nist_p192_रेजिस्टरed)
		crypto_unरेजिस्टर_akcipher(&ecdsa_nist_p192);
	crypto_unरेजिस्टर_akcipher(&ecdsa_nist_p256);
	crypto_unरेजिस्टर_akcipher(&ecdsa_nist_p384);
पूर्ण

subsys_initcall(ecdsa_init);
module_निकास(ecdsa_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Stefan Berger <stefanb@linux.ibm.com>");
MODULE_DESCRIPTION("ECDSA generic algorithm");
MODULE_ALIAS_CRYPTO("ecdsa-generic");
