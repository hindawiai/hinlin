<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Elliptic Curve (Russian) Digital Signature Algorithm क्रम Cryptographic API
 *
 * Copyright (c) 2019 Vitaly Chikunov <vt@altlinux.org>
 *
 * References:
 * GOST 34.10-2018, GOST R 34.10-2012, RFC 7091, ISO/IEC 14888-3:2018.
 *
 * Historical references:
 * GOST R 34.10-2001, RFC 4357, ISO/IEC 14888-3:2006/Amd 1:2010.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#समावेश <linux/module.h>
#समावेश <linux/crypto.h>
#समावेश <crypto/streebog.h>
#समावेश <crypto/पूर्णांकernal/akcipher.h>
#समावेश <crypto/akcipher.h>
#समावेश <linux/oid_registry.h>
#समावेश <linux/scatterlist.h>
#समावेश "ecrdsa_params.asn1.h"
#समावेश "ecrdsa_pub_key.asn1.h"
#समावेश "ecc.h"
#समावेश "ecrdsa_defs.h"

#घोषणा ECRDSA_MAX_SIG_SIZE (2 * 512 / 8)
#घोषणा ECRDSA_MAX_DIGITS (512 / 64)

काष्ठा ecrdsa_ctx अणु
	क्रमागत OID algo_oid; /* overall खुला key oid */
	क्रमागत OID curve_oid; /* parameter */
	क्रमागत OID digest_oid; /* parameter */
	स्थिर काष्ठा ecc_curve *curve; /* curve from oid */
	अचिन्हित पूर्णांक digest_len; /* parameter (bytes) */
	स्थिर अक्षर *digest; /* digest name from oid */
	अचिन्हित पूर्णांक key_len; /* @key length (bytes) */
	स्थिर अक्षर *key; /* raw खुला key */
	काष्ठा ecc_poपूर्णांक pub_key;
	u64 _pubp[2][ECRDSA_MAX_DIGITS]; /* poपूर्णांक storage क्रम @pub_key */
पूर्ण;

अटल स्थिर काष्ठा ecc_curve *get_curve_by_oid(क्रमागत OID oid)
अणु
	चयन (oid) अणु
	हाल OID_gostCPSignA:
	हाल OID_gostTC26Sign256B:
		वापस &gost_cp256a;
	हाल OID_gostCPSignB:
	हाल OID_gostTC26Sign256C:
		वापस &gost_cp256b;
	हाल OID_gostCPSignC:
	हाल OID_gostTC26Sign256D:
		वापस &gost_cp256c;
	हाल OID_gostTC26Sign512A:
		वापस &gost_tc512a;
	हाल OID_gostTC26Sign512B:
		वापस &gost_tc512b;
	/* The following two aren't implemented: */
	हाल OID_gostTC26Sign256A:
	हाल OID_gostTC26Sign512C:
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक ecrdsa_verअगरy(काष्ठा akcipher_request *req)
अणु
	काष्ठा crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	काष्ठा ecrdsa_ctx *ctx = akcipher_tfm_ctx(tfm);
	अचिन्हित अक्षर sig[ECRDSA_MAX_SIG_SIZE];
	अचिन्हित अक्षर digest[STREEBOG512_DIGEST_SIZE];
	अचिन्हित पूर्णांक ndigits = req->dst_len / माप(u64);
	u64 r[ECRDSA_MAX_DIGITS]; /* witness (r) */
	u64 _r[ECRDSA_MAX_DIGITS]; /* -r */
	u64 s[ECRDSA_MAX_DIGITS]; /* second part of sig (s) */
	u64 e[ECRDSA_MAX_DIGITS]; /* h \mod q */
	u64 *v = e;		  /* e^अणु-1पूर्ण \mod q */
	u64 z1[ECRDSA_MAX_DIGITS];
	u64 *z2 = _r;
	काष्ठा ecc_poपूर्णांक cc = ECC_POINT_INIT(s, e, ndigits); /* reuse s, e */

	/*
	 * Digest value, digest algorithm, and curve (modulus) should have the
	 * same length (256 or 512 bits), खुला key and signature should be
	 * twice bigger.
	 */
	अगर (!ctx->curve ||
	    !ctx->digest ||
	    !req->src ||
	    !ctx->pub_key.x ||
	    req->dst_len != ctx->digest_len ||
	    req->dst_len != ctx->curve->g.ndigits * माप(u64) ||
	    ctx->pub_key.ndigits != ctx->curve->g.ndigits ||
	    req->dst_len * 2 != req->src_len ||
	    WARN_ON(req->src_len > माप(sig)) ||
	    WARN_ON(req->dst_len > माप(digest)))
		वापस -EBADMSG;

	sg_copy_to_buffer(req->src, sg_nents_क्रम_len(req->src, req->src_len),
			  sig, req->src_len);
	sg_pcopy_to_buffer(req->src,
			   sg_nents_क्रम_len(req->src,
					    req->src_len + req->dst_len),
			   digest, req->dst_len, req->src_len);

	vli_from_be64(s, sig, ndigits);
	vli_from_be64(r, sig + ndigits * माप(u64), ndigits);

	/* Step 1: verअगरy that 0 < r < q, 0 < s < q */
	अगर (vli_is_zero(r, ndigits) ||
	    vli_cmp(r, ctx->curve->n, ndigits) == 1 ||
	    vli_is_zero(s, ndigits) ||
	    vli_cmp(s, ctx->curve->n, ndigits) == 1)
		वापस -EKEYREJECTED;

	/* Step 2: calculate hash (h) of the message (passed as input) */
	/* Step 3: calculate e = h \mod q */
	vli_from_le64(e, digest, ndigits);
	अगर (vli_cmp(e, ctx->curve->n, ndigits) == 1)
		vli_sub(e, e, ctx->curve->n, ndigits);
	अगर (vli_is_zero(e, ndigits))
		e[0] = 1;

	/* Step 4: calculate v = e^अणु-1पूर्ण \mod q */
	vli_mod_inv(v, e, ctx->curve->n, ndigits);

	/* Step 5: calculate z_1 = sv \mod q, z_2 = -rv \mod q */
	vli_mod_mult_slow(z1, s, v, ctx->curve->n, ndigits);
	vli_sub(_r, ctx->curve->n, r, ndigits);
	vli_mod_mult_slow(z2, _r, v, ctx->curve->n, ndigits);

	/* Step 6: calculate poपूर्णांक C = z_1P + z_2Q, and R = x_c \mod q */
	ecc_poपूर्णांक_mult_shamir(&cc, z1, &ctx->curve->g, z2, &ctx->pub_key,
			      ctx->curve);
	अगर (vli_cmp(cc.x, ctx->curve->n, ndigits) == 1)
		vli_sub(cc.x, cc.x, ctx->curve->n, ndigits);

	/* Step 7: अगर R == r signature is valid */
	अगर (!vli_cmp(cc.x, r, ndigits))
		वापस 0;
	अन्यथा
		वापस -EKEYREJECTED;
पूर्ण

पूर्णांक ecrdsa_param_curve(व्योम *context, माप_प्रकार hdrlen, अचिन्हित अक्षर tag,
		       स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा ecrdsa_ctx *ctx = context;

	ctx->curve_oid = look_up_OID(value, vlen);
	अगर (!ctx->curve_oid)
		वापस -EINVAL;
	ctx->curve = get_curve_by_oid(ctx->curve_oid);
	वापस 0;
पूर्ण

/* Optional. If present should match expected digest algo OID. */
पूर्णांक ecrdsa_param_digest(व्योम *context, माप_प्रकार hdrlen, अचिन्हित अक्षर tag,
			स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा ecrdsa_ctx *ctx = context;
	पूर्णांक digest_oid = look_up_OID(value, vlen);

	अगर (digest_oid != ctx->digest_oid)
		वापस -EINVAL;
	वापस 0;
पूर्ण

पूर्णांक ecrdsa_parse_pub_key(व्योम *context, माप_प्रकार hdrlen, अचिन्हित अक्षर tag,
			 स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा ecrdsa_ctx *ctx = context;

	ctx->key = value;
	ctx->key_len = vlen;
	वापस 0;
पूर्ण

अटल u8 *ecrdsa_unpack_u32(u32 *dst, व्योम *src)
अणु
	स_नकल(dst, src, माप(u32));
	वापस src + माप(u32);
पूर्ण

/* Parse BER encoded subjectPublicKey. */
अटल पूर्णांक ecrdsa_set_pub_key(काष्ठा crypto_akcipher *tfm, स्थिर व्योम *key,
			      अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा ecrdsa_ctx *ctx = akcipher_tfm_ctx(tfm);
	अचिन्हित पूर्णांक ndigits;
	u32 algo, paramlen;
	u8 *params;
	पूर्णांक err;

	err = asn1_ber_decoder(&ecrdsa_pub_key_decoder, ctx, key, keylen);
	अगर (err < 0)
		वापस err;

	/* Key parameters is in the key after keylen. */
	params = ecrdsa_unpack_u32(&paramlen,
			  ecrdsa_unpack_u32(&algo, (u8 *)key + keylen));

	अगर (algo == OID_gost2012PKey256) अणु
		ctx->digest	= "streebog256";
		ctx->digest_oid	= OID_gost2012Digest256;
		ctx->digest_len	= 256 / 8;
	पूर्ण अन्यथा अगर (algo == OID_gost2012PKey512) अणु
		ctx->digest	= "streebog512";
		ctx->digest_oid	= OID_gost2012Digest512;
		ctx->digest_len	= 512 / 8;
	पूर्ण अन्यथा
		वापस -ENOPKG;
	ctx->algo_oid = algo;

	/* Parse SubjectPublicKeyInfo.AlgorithmIdentअगरier.parameters. */
	err = asn1_ber_decoder(&ecrdsa_params_decoder, ctx, params, paramlen);
	अगर (err < 0)
		वापस err;
	/*
	 * Sizes of algo (set in digest_len) and curve should match
	 * each other.
	 */
	अगर (!ctx->curve ||
	    ctx->curve->g.ndigits * माप(u64) != ctx->digest_len)
		वापस -ENOPKG;
	/*
	 * Key is two 256- or 512-bit coordinates which should match
	 * curve size.
	 */
	अगर ((ctx->key_len != (2 * 256 / 8) &&
	     ctx->key_len != (2 * 512 / 8)) ||
	    ctx->key_len != ctx->curve->g.ndigits * माप(u64) * 2)
		वापस -ENOPKG;

	ndigits = ctx->key_len / माप(u64) / 2;
	ctx->pub_key = ECC_POINT_INIT(ctx->_pubp[0], ctx->_pubp[1], ndigits);
	vli_from_le64(ctx->pub_key.x, ctx->key, ndigits);
	vli_from_le64(ctx->pub_key.y, ctx->key + ndigits * माप(u64),
		      ndigits);

	अगर (ecc_is_pubkey_valid_partial(ctx->curve, &ctx->pub_key))
		वापस -EKEYREJECTED;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक ecrdsa_max_size(काष्ठा crypto_akcipher *tfm)
अणु
	काष्ठा ecrdsa_ctx *ctx = akcipher_tfm_ctx(tfm);

	/*
	 * Verअगरy करोesn't need any output, so it's just inक्रमmational
	 * क्रम keyctl to determine the key bit size.
	 */
	वापस ctx->pub_key.ndigits * माप(u64);
पूर्ण

अटल व्योम ecrdsa_निकास_tfm(काष्ठा crypto_akcipher *tfm)
अणु
पूर्ण

अटल काष्ठा akcipher_alg ecrdsa_alg = अणु
	.verअगरy		= ecrdsa_verअगरy,
	.set_pub_key	= ecrdsa_set_pub_key,
	.max_size	= ecrdsa_max_size,
	.निकास		= ecrdsa_निकास_tfm,
	.base = अणु
		.cra_name	 = "ecrdsa",
		.cra_driver_name = "ecrdsa-generic",
		.cra_priority	 = 100,
		.cra_module	 = THIS_MODULE,
		.cra_ctxsize	 = माप(काष्ठा ecrdsa_ctx),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ecrdsa_mod_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_akcipher(&ecrdsa_alg);
पूर्ण

अटल व्योम __निकास ecrdsa_mod_fini(व्योम)
अणु
	crypto_unरेजिस्टर_akcipher(&ecrdsa_alg);
पूर्ण

module_init(ecrdsa_mod_init);
module_निकास(ecrdsa_mod_fini);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vitaly Chikunov <vt@altlinux.org>");
MODULE_DESCRIPTION("EC-RDSA generic algorithm");
MODULE_ALIAS_CRYPTO("ecrdsa-generic");
