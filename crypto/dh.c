<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*  Dअगरfie-Hellman Key Agreement Method [RFC2631]
 *
 * Copyright (c) 2016, Intel Corporation
 * Authors: Salvatore Benedetto <salvatore.benedetto@पूर्णांकel.com>
 */

#समावेश <linux/module.h>
#समावेश <crypto/पूर्णांकernal/kpp.h>
#समावेश <crypto/kpp.h>
#समावेश <crypto/dh.h>
#समावेश <linux/fips.h>
#समावेश <linux/mpi.h>

काष्ठा dh_ctx अणु
	MPI p;	/* Value is guaranteed to be set. */
	MPI q;	/* Value is optional. */
	MPI g;	/* Value is guaranteed to be set. */
	MPI xa;	/* Value is guaranteed to be set. */
पूर्ण;

अटल व्योम dh_clear_ctx(काष्ठा dh_ctx *ctx)
अणु
	mpi_मुक्त(ctx->p);
	mpi_मुक्त(ctx->q);
	mpi_मुक्त(ctx->g);
	mpi_मुक्त(ctx->xa);
	स_रखो(ctx, 0, माप(*ctx));
पूर्ण

/*
 * If base is g we compute the खुला key
 *	ya = g^xa mod p; [RFC2631 sec 2.1.1]
 * अन्यथा अगर base अगर the counterpart खुला key we compute the shared secret
 *	ZZ = yb^xa mod p; [RFC2631 sec 2.1.1]
 */
अटल पूर्णांक _compute_val(स्थिर काष्ठा dh_ctx *ctx, MPI base, MPI val)
अणु
	/* val = base^xa mod p */
	वापस mpi_घातm(val, base, ctx->xa, ctx->p);
पूर्ण

अटल अंतरभूत काष्ठा dh_ctx *dh_get_ctx(काष्ठा crypto_kpp *tfm)
अणु
	वापस kpp_tfm_ctx(tfm);
पूर्ण

अटल पूर्णांक dh_check_params_length(अचिन्हित पूर्णांक p_len)
अणु
	वापस (p_len < 1536) ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक dh_set_params(काष्ठा dh_ctx *ctx, काष्ठा dh *params)
अणु
	अगर (dh_check_params_length(params->p_size << 3))
		वापस -EINVAL;

	ctx->p = mpi_पढ़ो_raw_data(params->p, params->p_size);
	अगर (!ctx->p)
		वापस -EINVAL;

	अगर (params->q && params->q_size) अणु
		ctx->q = mpi_पढ़ो_raw_data(params->q, params->q_size);
		अगर (!ctx->q)
			वापस -EINVAL;
	पूर्ण

	ctx->g = mpi_पढ़ो_raw_data(params->g, params->g_size);
	अगर (!ctx->g)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक dh_set_secret(काष्ठा crypto_kpp *tfm, स्थिर व्योम *buf,
			 अचिन्हित पूर्णांक len)
अणु
	काष्ठा dh_ctx *ctx = dh_get_ctx(tfm);
	काष्ठा dh params;

	/* Free the old MPI key अगर any */
	dh_clear_ctx(ctx);

	अगर (crypto_dh_decode_key(buf, len, &params) < 0)
		जाओ err_clear_ctx;

	अगर (dh_set_params(ctx, &params) < 0)
		जाओ err_clear_ctx;

	ctx->xa = mpi_पढ़ो_raw_data(params.key, params.key_size);
	अगर (!ctx->xa)
		जाओ err_clear_ctx;

	वापस 0;

err_clear_ctx:
	dh_clear_ctx(ctx);
	वापस -EINVAL;
पूर्ण

/*
 * SP800-56A खुला key verअगरication:
 *
 * * If Q is provided as part of the करोमुख्य paramenters, a full validation
 *   according to SP800-56A section 5.6.2.3.1 is perक्रमmed.
 *
 * * If Q is not provided, a partial validation according to SP800-56A section
 *   5.6.2.3.2 is perक्रमmed.
 */
अटल पूर्णांक dh_is_pubkey_valid(काष्ठा dh_ctx *ctx, MPI y)
अणु
	अगर (unlikely(!ctx->p))
		वापस -EINVAL;

	/*
	 * Step 1: Verअगरy that 2 <= y <= p - 2.
	 *
	 * The upper limit check is actually y < p instead of y < p - 1
	 * as the mpi_sub_ui function is yet missing.
	 */
	अगर (mpi_cmp_ui(y, 1) < 1 || mpi_cmp(y, ctx->p) >= 0)
		वापस -EINVAL;

	/* Step 2: Verअगरy that 1 = y^q mod p */
	अगर (ctx->q) अणु
		MPI val = mpi_alloc(0);
		पूर्णांक ret;

		अगर (!val)
			वापस -ENOMEM;

		ret = mpi_घातm(val, y, ctx->q, ctx->p);

		अगर (ret) अणु
			mpi_मुक्त(val);
			वापस ret;
		पूर्ण

		ret = mpi_cmp_ui(val, 1);

		mpi_मुक्त(val);

		अगर (ret != 0)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dh_compute_value(काष्ठा kpp_request *req)
अणु
	काष्ठा crypto_kpp *tfm = crypto_kpp_reqtfm(req);
	काष्ठा dh_ctx *ctx = dh_get_ctx(tfm);
	MPI base, val = mpi_alloc(0);
	पूर्णांक ret = 0;
	पूर्णांक sign;

	अगर (!val)
		वापस -ENOMEM;

	अगर (unlikely(!ctx->xa)) अणु
		ret = -EINVAL;
		जाओ err_मुक्त_val;
	पूर्ण

	अगर (req->src) अणु
		base = mpi_पढ़ो_raw_from_sgl(req->src, req->src_len);
		अगर (!base) अणु
			ret = -EINVAL;
			जाओ err_मुक्त_val;
		पूर्ण
		ret = dh_is_pubkey_valid(ctx, base);
		अगर (ret)
			जाओ err_मुक्त_base;
	पूर्ण अन्यथा अणु
		base = ctx->g;
	पूर्ण

	ret = _compute_val(ctx, base, val);
	अगर (ret)
		जाओ err_मुक्त_base;

	अगर (fips_enabled) अणु
		/* SP800-56A rev3 5.7.1.1 check: Validation of shared secret */
		अगर (req->src) अणु
			MPI pone;

			/* z <= 1 */
			अगर (mpi_cmp_ui(val, 1) < 1) अणु
				ret = -EBADMSG;
				जाओ err_मुक्त_base;
			पूर्ण

			/* z == p - 1 */
			pone = mpi_alloc(0);

			अगर (!pone) अणु
				ret = -ENOMEM;
				जाओ err_मुक्त_base;
			पूर्ण

			ret = mpi_sub_ui(pone, ctx->p, 1);
			अगर (!ret && !mpi_cmp(pone, val))
				ret = -EBADMSG;

			mpi_मुक्त(pone);

			अगर (ret)
				जाओ err_मुक्त_base;

		/* SP800-56A rev 3 5.6.2.1.3 key check */
		पूर्ण अन्यथा अणु
			अगर (dh_is_pubkey_valid(ctx, val)) अणु
				ret = -EAGAIN;
				जाओ err_मुक्त_val;
			पूर्ण
		पूर्ण
	पूर्ण

	ret = mpi_ग_लिखो_to_sgl(val, req->dst, req->dst_len, &sign);
	अगर (ret)
		जाओ err_मुक्त_base;

	अगर (sign < 0)
		ret = -EBADMSG;
err_मुक्त_base:
	अगर (req->src)
		mpi_मुक्त(base);
err_मुक्त_val:
	mpi_मुक्त(val);
	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक dh_max_size(काष्ठा crypto_kpp *tfm)
अणु
	काष्ठा dh_ctx *ctx = dh_get_ctx(tfm);

	वापस mpi_get_size(ctx->p);
पूर्ण

अटल व्योम dh_निकास_tfm(काष्ठा crypto_kpp *tfm)
अणु
	काष्ठा dh_ctx *ctx = dh_get_ctx(tfm);

	dh_clear_ctx(ctx);
पूर्ण

अटल काष्ठा kpp_alg dh = अणु
	.set_secret = dh_set_secret,
	.generate_खुला_key = dh_compute_value,
	.compute_shared_secret = dh_compute_value,
	.max_size = dh_max_size,
	.निकास = dh_निकास_tfm,
	.base = अणु
		.cra_name = "dh",
		.cra_driver_name = "dh-generic",
		.cra_priority = 100,
		.cra_module = THIS_MODULE,
		.cra_ctxsize = माप(काष्ठा dh_ctx),
	पूर्ण,
पूर्ण;

अटल पूर्णांक dh_init(व्योम)
अणु
	वापस crypto_रेजिस्टर_kpp(&dh);
पूर्ण

अटल व्योम dh_निकास(व्योम)
अणु
	crypto_unरेजिस्टर_kpp(&dh);
पूर्ण

subsys_initcall(dh_init);
module_निकास(dh_निकास);
MODULE_ALIAS_CRYPTO("dh");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("DH generic algorithm");
