<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * SM2 asymmetric खुला-key algorithm
 * as specअगरied by OSCCA GM/T 0003.1-2012 -- 0003.5-2012 SM2 and
 * described at https://tools.ietf.org/hपंचांगl/draft-shen-sm2-ecdsa-02
 *
 * Copyright (c) 2020, Alibaba Group.
 * Authors: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/mpi.h>
#समावेश <crypto/पूर्णांकernal/akcipher.h>
#समावेश <crypto/akcipher.h>
#समावेश <crypto/hash.h>
#समावेश <crypto/sm3_base.h>
#समावेश <crypto/rng.h>
#समावेश <crypto/sm2.h>
#समावेश "sm2signature.asn1.h"

#घोषणा MPI_NBYTES(m)   ((mpi_get_nbits(m) + 7) / 8)

काष्ठा ecc_करोमुख्य_parms अणु
	स्थिर अक्षर *desc;           /* Description of the curve.  */
	अचिन्हित पूर्णांक nbits;         /* Number of bits.  */
	अचिन्हित पूर्णांक fips:1; /* True अगर this is a FIPS140-2 approved curve */

	/* The model describing this curve.  This is मुख्यly used to select
	 * the group equation.
	 */
	क्रमागत gcry_mpi_ec_models model;

	/* The actual ECC dialect used.  This is used क्रम curve specअगरic
	 * optimizations and to select encodings etc.
	 */
	क्रमागत ecc_dialects dialect;

	स्थिर अक्षर *p;              /* The prime defining the field.  */
	स्थिर अक्षर *a, *b;          /* The coefficients.  For Twisted Edwards
				     * Curves b is used क्रम d.  For Montgomery
				     * Curves (a,b) has ((A-2)/4,B^-1).
				     */
	स्थिर अक्षर *n;              /* The order of the base poपूर्णांक.  */
	स्थिर अक्षर *g_x, *g_y;      /* Base poपूर्णांक.  */
	अचिन्हित पूर्णांक h;             /* Cofactor.  */
पूर्ण;

अटल स्थिर काष्ठा ecc_करोमुख्य_parms sm2_ecp = अणु
	.desc = "sm2p256v1",
	.nbits = 256,
	.fips = 0,
	.model = MPI_EC_WEIERSTRASS,
	.dialect = ECC_DIALECT_STANDARD,
	.p   = "0xfffffffeffffffffffffffffffffffffffffffff00000000ffffffffffffffff",
	.a   = "0xfffffffeffffffffffffffffffffffffffffffff00000000fffffffffffffffc",
	.b   = "0x28e9fa9e9d9f5e344d5a9e4bcf6509a7f39789f515ab8f92ddbcbd414d940e93",
	.n   = "0xfffffffeffffffffffffffffffffffff7203df6b21c6052b53bbf40939d54123",
	.g_x = "0x32c4ae2c1f1981195f9904466a39c9948fe30bbff2660be1715a4589334c74c7",
	.g_y = "0xbc3736a2f4f6779c59bdcee36b692153d0a9877cc62a474002df32e52139f0a0",
	.h = 1
पूर्ण;

अटल पूर्णांक sm2_ec_ctx_init(काष्ठा mpi_ec_ctx *ec)
अणु
	स्थिर काष्ठा ecc_करोमुख्य_parms *ecp = &sm2_ecp;
	MPI p, a, b;
	MPI x, y;
	पूर्णांक rc = -EINVAL;

	p = mpi_scanval(ecp->p);
	a = mpi_scanval(ecp->a);
	b = mpi_scanval(ecp->b);
	अगर (!p || !a || !b)
		जाओ मुक्त_p;

	x = mpi_scanval(ecp->g_x);
	y = mpi_scanval(ecp->g_y);
	अगर (!x || !y)
		जाओ मुक्त;

	rc = -ENOMEM;
	/* mpi_ec_setup_elliptic_curve */
	ec->G = mpi_poपूर्णांक_new(0);
	अगर (!ec->G)
		जाओ मुक्त;

	mpi_set(ec->G->x, x);
	mpi_set(ec->G->y, y);
	mpi_set_ui(ec->G->z, 1);

	rc = -EINVAL;
	ec->n = mpi_scanval(ecp->n);
	अगर (!ec->n) अणु
		mpi_poपूर्णांक_release(ec->G);
		जाओ मुक्त;
	पूर्ण

	ec->h = ecp->h;
	ec->name = ecp->desc;
	mpi_ec_init(ec, ecp->model, ecp->dialect, 0, p, a, b);

	rc = 0;

मुक्त:
	mpi_मुक्त(x);
	mpi_मुक्त(y);
मुक्त_p:
	mpi_मुक्त(p);
	mpi_मुक्त(a);
	mpi_मुक्त(b);

	वापस rc;
पूर्ण

अटल व्योम sm2_ec_ctx_deinit(काष्ठा mpi_ec_ctx *ec)
अणु
	mpi_ec_deinit(ec);

	स_रखो(ec, 0, माप(*ec));
पूर्ण

/* RESULT must have been initialized and is set on success to the
 * poपूर्णांक given by VALUE.
 */
अटल पूर्णांक sm2_ecc_os2ec(MPI_POINT result, MPI value)
अणु
	पूर्णांक rc;
	माप_प्रकार n;
	अचिन्हित अक्षर *buf;
	MPI x, y;

	n = MPI_NBYTES(value);
	buf = kदो_स्मृति(n, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	rc = mpi_prपूर्णांक(GCRYMPI_FMT_USG, buf, n, &n, value);
	अगर (rc)
		जाओ err_मुक्तbuf;

	rc = -EINVAL;
	अगर (n < 1 || ((n - 1) % 2))
		जाओ err_मुक्तbuf;
	/* No support क्रम poपूर्णांक compression */
	अगर (*buf != 0x4)
		जाओ err_मुक्तbuf;

	rc = -ENOMEM;
	n = (n - 1) / 2;
	x = mpi_पढ़ो_raw_data(buf + 1, n);
	अगर (!x)
		जाओ err_मुक्तbuf;
	y = mpi_पढ़ो_raw_data(buf + 1 + n, n);
	अगर (!y)
		जाओ err_मुक्तx;

	mpi_normalize(x);
	mpi_normalize(y);
	mpi_set(result->x, x);
	mpi_set(result->y, y);
	mpi_set_ui(result->z, 1);

	rc = 0;

	mpi_मुक्त(y);
err_मुक्तx:
	mpi_मुक्त(x);
err_मुक्तbuf:
	kमुक्त(buf);
	वापस rc;
पूर्ण

काष्ठा sm2_signature_ctx अणु
	MPI sig_r;
	MPI sig_s;
पूर्ण;

पूर्णांक sm2_get_signature_r(व्योम *context, माप_प्रकार hdrlen, अचिन्हित अक्षर tag,
				स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा sm2_signature_ctx *sig = context;

	अगर (!value || !vlen)
		वापस -EINVAL;

	sig->sig_r = mpi_पढ़ो_raw_data(value, vlen);
	अगर (!sig->sig_r)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

पूर्णांक sm2_get_signature_s(व्योम *context, माप_प्रकार hdrlen, अचिन्हित अक्षर tag,
				स्थिर व्योम *value, माप_प्रकार vlen)
अणु
	काष्ठा sm2_signature_ctx *sig = context;

	अगर (!value || !vlen)
		वापस -EINVAL;

	sig->sig_s = mpi_पढ़ो_raw_data(value, vlen);
	अगर (!sig->sig_s)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक sm2_z_digest_update(काष्ठा shash_desc *desc,
			MPI m, अचिन्हित पूर्णांक pbytes)
अणु
	अटल स्थिर अचिन्हित अक्षर zero[32];
	अचिन्हित अक्षर *in;
	अचिन्हित पूर्णांक inlen;

	in = mpi_get_buffer(m, &inlen, शून्य);
	अगर (!in)
		वापस -EINVAL;

	अगर (inlen < pbytes) अणु
		/* padding with zero */
		crypto_sm3_update(desc, zero, pbytes - inlen);
		crypto_sm3_update(desc, in, inlen);
	पूर्ण अन्यथा अगर (inlen > pbytes) अणु
		/* skip the starting zero */
		crypto_sm3_update(desc, in + inlen - pbytes, pbytes);
	पूर्ण अन्यथा अणु
		crypto_sm3_update(desc, in, inlen);
	पूर्ण

	kमुक्त(in);
	वापस 0;
पूर्ण

अटल पूर्णांक sm2_z_digest_update_poपूर्णांक(काष्ठा shash_desc *desc,
		MPI_POINT poपूर्णांक, काष्ठा mpi_ec_ctx *ec, अचिन्हित पूर्णांक pbytes)
अणु
	MPI x, y;
	पूर्णांक ret = -EINVAL;

	x = mpi_new(0);
	y = mpi_new(0);

	अगर (!mpi_ec_get_affine(x, y, poपूर्णांक, ec) &&
		!sm2_z_digest_update(desc, x, pbytes) &&
		!sm2_z_digest_update(desc, y, pbytes))
		ret = 0;

	mpi_मुक्त(x);
	mpi_मुक्त(y);
	वापस ret;
पूर्ण

पूर्णांक sm2_compute_z_digest(काष्ठा crypto_akcipher *tfm,
			स्थिर अचिन्हित अक्षर *id, माप_प्रकार id_len,
			अचिन्हित अक्षर dgst[SM3_DIGEST_SIZE])
अणु
	काष्ठा mpi_ec_ctx *ec = akcipher_tfm_ctx(tfm);
	uपूर्णांक16_t bits_len;
	अचिन्हित अक्षर entl[2];
	SHASH_DESC_ON_STACK(desc, शून्य);
	अचिन्हित पूर्णांक pbytes;

	अगर (id_len > (अच_लघु_उच्च / 8) || !ec->Q)
		वापस -EINVAL;

	bits_len = (uपूर्णांक16_t)(id_len * 8);
	entl[0] = bits_len >> 8;
	entl[1] = bits_len & 0xff;

	pbytes = MPI_NBYTES(ec->p);

	/* ZA = H256(ENTLA | IDA | a | b | xG | yG | xA | yA) */
	sm3_base_init(desc);
	crypto_sm3_update(desc, entl, 2);
	crypto_sm3_update(desc, id, id_len);

	अगर (sm2_z_digest_update(desc, ec->a, pbytes) ||
		sm2_z_digest_update(desc, ec->b, pbytes) ||
		sm2_z_digest_update_poपूर्णांक(desc, ec->G, ec, pbytes) ||
		sm2_z_digest_update_poपूर्णांक(desc, ec->Q, ec, pbytes))
		वापस -EINVAL;

	crypto_sm3_final(desc, dgst);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(sm2_compute_z_digest);

अटल पूर्णांक _sm2_verअगरy(काष्ठा mpi_ec_ctx *ec, MPI hash, MPI sig_r, MPI sig_s)
अणु
	पूर्णांक rc = -EINVAL;
	काष्ठा gcry_mpi_poपूर्णांक sG, tP;
	MPI t = शून्य;
	MPI x1 = शून्य, y1 = शून्य;

	mpi_poपूर्णांक_init(&sG);
	mpi_poपूर्णांक_init(&tP);
	x1 = mpi_new(0);
	y1 = mpi_new(0);
	t = mpi_new(0);

	/* r, s in [1, n-1] */
	अगर (mpi_cmp_ui(sig_r, 1) < 0 || mpi_cmp(sig_r, ec->n) > 0 ||
		mpi_cmp_ui(sig_s, 1) < 0 || mpi_cmp(sig_s, ec->n) > 0) अणु
		जाओ leave;
	पूर्ण

	/* t = (r + s) % n, t == 0 */
	mpi_addm(t, sig_r, sig_s, ec->n);
	अगर (mpi_cmp_ui(t, 0) == 0)
		जाओ leave;

	/* sG + tP = (x1, y1) */
	rc = -EBADMSG;
	mpi_ec_mul_poपूर्णांक(&sG, sig_s, ec->G, ec);
	mpi_ec_mul_poपूर्णांक(&tP, t, ec->Q, ec);
	mpi_ec_add_poपूर्णांकs(&sG, &sG, &tP, ec);
	अगर (mpi_ec_get_affine(x1, y1, &sG, ec))
		जाओ leave;

	/* R = (e + x1) % n */
	mpi_addm(t, hash, x1, ec->n);

	/* check R == r */
	rc = -EKEYREJECTED;
	अगर (mpi_cmp(t, sig_r))
		जाओ leave;

	rc = 0;

leave:
	mpi_poपूर्णांक_मुक्त_parts(&sG);
	mpi_poपूर्णांक_मुक्त_parts(&tP);
	mpi_मुक्त(x1);
	mpi_मुक्त(y1);
	mpi_मुक्त(t);

	वापस rc;
पूर्ण

अटल पूर्णांक sm2_verअगरy(काष्ठा akcipher_request *req)
अणु
	काष्ठा crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	काष्ठा mpi_ec_ctx *ec = akcipher_tfm_ctx(tfm);
	अचिन्हित अक्षर *buffer;
	काष्ठा sm2_signature_ctx sig;
	MPI hash;
	पूर्णांक ret;

	अगर (unlikely(!ec->Q))
		वापस -EINVAL;

	buffer = kदो_स्मृति(req->src_len + req->dst_len, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	sg_pcopy_to_buffer(req->src,
		sg_nents_क्रम_len(req->src, req->src_len + req->dst_len),
		buffer, req->src_len + req->dst_len, 0);

	sig.sig_r = शून्य;
	sig.sig_s = शून्य;
	ret = asn1_ber_decoder(&sm2signature_decoder, &sig,
				buffer, req->src_len);
	अगर (ret)
		जाओ error;

	ret = -ENOMEM;
	hash = mpi_पढ़ो_raw_data(buffer + req->src_len, req->dst_len);
	अगर (!hash)
		जाओ error;

	ret = _sm2_verअगरy(ec, hash, sig.sig_r, sig.sig_s);

	mpi_मुक्त(hash);
error:
	mpi_मुक्त(sig.sig_r);
	mpi_मुक्त(sig.sig_s);
	kमुक्त(buffer);
	वापस ret;
पूर्ण

अटल पूर्णांक sm2_set_pub_key(काष्ठा crypto_akcipher *tfm,
			स्थिर व्योम *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा mpi_ec_ctx *ec = akcipher_tfm_ctx(tfm);
	MPI a;
	पूर्णांक rc;

	ec->Q = mpi_poपूर्णांक_new(0);
	अगर (!ec->Q)
		वापस -ENOMEM;

	/* include the uncompressed flag '0x04' */
	rc = -ENOMEM;
	a = mpi_पढ़ो_raw_data(key, keylen);
	अगर (!a)
		जाओ error;

	mpi_normalize(a);
	rc = sm2_ecc_os2ec(ec->Q, a);
	mpi_मुक्त(a);
	अगर (rc)
		जाओ error;

	वापस 0;

error:
	mpi_poपूर्णांक_release(ec->Q);
	ec->Q = शून्य;
	वापस rc;
पूर्ण

अटल अचिन्हित पूर्णांक sm2_max_size(काष्ठा crypto_akcipher *tfm)
अणु
	/* Unlimited max size */
	वापस PAGE_SIZE;
पूर्ण

अटल पूर्णांक sm2_init_tfm(काष्ठा crypto_akcipher *tfm)
अणु
	काष्ठा mpi_ec_ctx *ec = akcipher_tfm_ctx(tfm);

	वापस sm2_ec_ctx_init(ec);
पूर्ण

अटल व्योम sm2_निकास_tfm(काष्ठा crypto_akcipher *tfm)
अणु
	काष्ठा mpi_ec_ctx *ec = akcipher_tfm_ctx(tfm);

	sm2_ec_ctx_deinit(ec);
पूर्ण

अटल काष्ठा akcipher_alg sm2 = अणु
	.verअगरy = sm2_verअगरy,
	.set_pub_key = sm2_set_pub_key,
	.max_size = sm2_max_size,
	.init = sm2_init_tfm,
	.निकास = sm2_निकास_tfm,
	.base = अणु
		.cra_name = "sm2",
		.cra_driver_name = "sm2-generic",
		.cra_priority = 100,
		.cra_module = THIS_MODULE,
		.cra_ctxsize = माप(काष्ठा mpi_ec_ctx),
	पूर्ण,
पूर्ण;

अटल पूर्णांक sm2_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_akcipher(&sm2);
पूर्ण

अटल व्योम sm2_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_akcipher(&sm2);
पूर्ण

subsys_initcall(sm2_init);
module_निकास(sm2_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tianjia Zhang <tianjia.zhang@linux.alibaba.com>");
MODULE_DESCRIPTION("SM2 generic algorithm");
MODULE_ALIAS_CRYPTO("sm2-generic");
