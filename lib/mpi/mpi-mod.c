<शैली गुरु>
/* mpi-mod.c -  Modular reduction
 * Copyright (C) 1998, 1999, 2001, 2002, 2003,
 *               2007  Free Software Foundation, Inc.
 *
 * This file is part of Libgcrypt.
 */


#समावेश "mpi-internal.h"
#समावेश "longlong.h"

/* Context used with Barrett reduction.  */
काष्ठा barrett_ctx_s अणु
	MPI m;   /* The modulus - may not be modअगरied. */
	पूर्णांक m_copied;   /* If true, M needs to be released.  */
	पूर्णांक k;
	MPI y;
	MPI r1;  /* Helper MPI. */
	MPI r2;  /* Helper MPI. */
	MPI r3;  /* Helper MPI allocated on demand. */
पूर्ण;



व्योम mpi_mod(MPI rem, MPI भागidend, MPI भागisor)
अणु
	mpi_fभाग_r(rem, भागidend, भागisor);
पूर्ण

/* This function वापसs a new context क्रम Barrett based operations on
 * the modulus M.  This context needs to be released using
 * _gcry_mpi_barrett_मुक्त.  If COPY is true M will be transferred to
 * the context and the user may change M.  If COPY is false, M may not
 * be changed until gcry_mpi_barrett_मुक्त has been called.
 */
mpi_barrett_t mpi_barrett_init(MPI m, पूर्णांक copy)
अणु
	mpi_barrett_t ctx;
	MPI पंचांगp;

	mpi_normalize(m);
	ctx = kसुस्मृति(1, माप(*ctx), GFP_KERNEL);

	अगर (copy) अणु
		ctx->m = mpi_copy(m);
		ctx->m_copied = 1;
	पूर्ण अन्यथा
		ctx->m = m;

	ctx->k = mpi_get_nlimbs(m);
	पंचांगp = mpi_alloc(ctx->k + 1);

	/* Barrett precalculation: y = न्यूनमान(b^(2k) / m). */
	mpi_set_ui(पंचांगp, 1);
	mpi_lshअगरt_limbs(पंचांगp, 2 * ctx->k);
	mpi_fभाग_q(पंचांगp, पंचांगp, m);

	ctx->y  = पंचांगp;
	ctx->r1 = mpi_alloc(2 * ctx->k + 1);
	ctx->r2 = mpi_alloc(2 * ctx->k + 1);

	वापस ctx;
पूर्ण

व्योम mpi_barrett_मुक्त(mpi_barrett_t ctx)
अणु
	अगर (ctx) अणु
		mpi_मुक्त(ctx->y);
		mpi_मुक्त(ctx->r1);
		mpi_मुक्त(ctx->r2);
		अगर (ctx->r3)
			mpi_मुक्त(ctx->r3);
		अगर (ctx->m_copied)
			mpi_मुक्त(ctx->m);
		kमुक्त(ctx);
	पूर्ण
पूर्ण


/* R = X mod M
 *
 * Using Barrett reduction.  Beक्रमe using this function
 * _gcry_mpi_barrett_init must have been called to करो the
 * precalculations.  CTX is the context created by this precalculation
 * and also conveys M.  If the Barret reduction could no be करोne a
 * straightक्रमward reduction method is used.
 *
 * We assume that these conditions are met:
 * Input:  x =(x_2k-1 ...x_0)_b
 *     m =(m_k-1 ....m_0)_b	  with m_k-1 != 0
 * Output: r = x mod m
 */
व्योम mpi_mod_barrett(MPI r, MPI x, mpi_barrett_t ctx)
अणु
	MPI m = ctx->m;
	पूर्णांक k = ctx->k;
	MPI y = ctx->y;
	MPI r1 = ctx->r1;
	MPI r2 = ctx->r2;
	पूर्णांक sign;

	mpi_normalize(x);
	अगर (mpi_get_nlimbs(x) > 2*k) अणु
		mpi_mod(r, x, m);
		वापस;
	पूर्ण

	sign = x->sign;
	x->sign = 0;

	/* 1. q1 = न्यूनमान( x / b^k-1)
	 *    q2 = q1 * y
	 *    q3 = न्यूनमान( q2 / b^k+1 )
	 * Actually, we करोn't need qx, we can work direct on r2
	 */
	mpi_set(r2, x);
	mpi_rshअगरt_limbs(r2, k-1);
	mpi_mul(r2, r2, y);
	mpi_rshअगरt_limbs(r2, k+1);

	/* 2. r1 = x mod b^k+1
	 *	r2 = q3 * m mod b^k+1
	 *	r  = r1 - r2
	 * 3. अगर r < 0 then  r = r + b^k+1
	 */
	mpi_set(r1, x);
	अगर (r1->nlimbs > k+1) /* Quick modulo operation.  */
		r1->nlimbs = k+1;
	mpi_mul(r2, r2, m);
	अगर (r2->nlimbs > k+1) /* Quick modulo operation. */
		r2->nlimbs = k+1;
	mpi_sub(r, r1, r2);

	अगर (mpi_has_sign(r)) अणु
		अगर (!ctx->r3) अणु
			ctx->r3 = mpi_alloc(k + 2);
			mpi_set_ui(ctx->r3, 1);
			mpi_lshअगरt_limbs(ctx->r3, k + 1);
		पूर्ण
		mpi_add(r, r, ctx->r3);
	पूर्ण

	/* 4. जबतक r >= m करो r = r - m */
	जबतक (mpi_cmp(r, m) >= 0)
		mpi_sub(r, r, m);

	x->sign = sign;
पूर्ण


व्योम mpi_mul_barrett(MPI w, MPI u, MPI v, mpi_barrett_t ctx)
अणु
	mpi_mul(w, u, v);
	mpi_mod_barrett(w, w, ctx);
पूर्ण
