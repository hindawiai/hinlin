<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* mpihelp-mul.c  -  MPI helper functions
 * Copyright (C) 1994, 1996, 1998, 1999,
 *               2000 Free Software Foundation, Inc.
 *
 * This file is part of GnuPG.
 *
 * Note: This code is heavily based on the GNU MP Library.
 *	 Actually it's the same code with only minor changes in the
 *	 way the data is stored; this is to support the असलtraction
 *	 of an optional secure memory allocation which may be used
 *	 to aव्योम revealing of sensitive data due to paging etc.
 *	 The GNU MP Library itself is published under the LGPL;
 *	 however I decided to publish this code under the plain GPL.
 */

#समावेश <linux/माला.स>
#समावेश "mpi-internal.h"
#समावेश "longlong.h"

#घोषणा MPN_MUL_N_RECURSE(prodp, up, vp, size, tspace)		\
	करो अणु							\
		अगर ((size) < KARATSUBA_THRESHOLD)		\
			mul_n_baseहाल(prodp, up, vp, size);	\
		अन्यथा						\
			mul_n(prodp, up, vp, size, tspace);	\
	पूर्ण जबतक (0);

#घोषणा MPN_SQR_N_RECURSE(prodp, up, size, tspace)		\
	करो अणु							\
		अगर ((size) < KARATSUBA_THRESHOLD)		\
			mpih_sqr_n_baseहाल(prodp, up, size);	\
		अन्यथा						\
			mpih_sqr_n(prodp, up, size, tspace);	\
	पूर्ण जबतक (0);

/* Multiply the natural numbers u (poपूर्णांकed to by UP) and v (poपूर्णांकed to by VP),
 * both with SIZE limbs, and store the result at PRODP.  2 * SIZE limbs are
 * always stored.  Return the most signअगरicant limb.
 *
 * Argument स्थिरraपूर्णांकs:
 * 1. PRODP != UP and PRODP != VP, i.e. the destination
 *    must be distinct from the multiplier and the multiplicand.
 *
 *
 * Handle simple हालs with traditional multiplication.
 *
 * This is the most critical code of multiplication.  All multiplies rely
 * on this, both small and huge.  Small ones arrive here immediately.  Huge
 * ones arrive here as this is the base हाल क्रम Karatsuba's recursive
 * algorithm below.
 */

अटल mpi_limb_t
mul_n_baseहाल(mpi_ptr_t prodp, mpi_ptr_t up, mpi_ptr_t vp, mpi_माप_प्रकार size)
अणु
	mpi_माप_प्रकार i;
	mpi_limb_t cy;
	mpi_limb_t v_limb;

	/* Multiply by the first limb in V separately, as the result can be
	 * stored (not added) to PROD.  We also aव्योम a loop क्रम zeroing.  */
	v_limb = vp[0];
	अगर (v_limb <= 1) अणु
		अगर (v_limb == 1)
			MPN_COPY(prodp, up, size);
		अन्यथा
			MPN_ZERO(prodp, size);
		cy = 0;
	पूर्ण अन्यथा
		cy = mpihelp_mul_1(prodp, up, size, v_limb);

	prodp[size] = cy;
	prodp++;

	/* For each iteration in the outer loop, multiply one limb from
	 * U with one limb from V, and add it to PROD.  */
	क्रम (i = 1; i < size; i++) अणु
		v_limb = vp[i];
		अगर (v_limb <= 1) अणु
			cy = 0;
			अगर (v_limb == 1)
				cy = mpihelp_add_n(prodp, prodp, up, size);
		पूर्ण अन्यथा
			cy = mpihelp_addmul_1(prodp, up, size, v_limb);

		prodp[size] = cy;
		prodp++;
	पूर्ण

	वापस cy;
पूर्ण

अटल व्योम
mul_n(mpi_ptr_t prodp, mpi_ptr_t up, mpi_ptr_t vp,
		mpi_माप_प्रकार size, mpi_ptr_t tspace)
अणु
	अगर (size & 1) अणु
		/* The size is odd, and the code below करोesn't handle that.
		 * Multiply the least signअगरicant (size - 1) limbs with a recursive
		 * call, and handle the most signअगरicant limb of S1 and S2
		 * separately.
		 * A slightly faster way to करो this would be to make the Karatsuba
		 * code below behave as अगर the size were even, and let it check क्रम
		 * odd size in the end.  I.e., in essence move this code to the end.
		 * Doing so would save us a recursive call, and potentially make the
		 * stack grow a lot less.
		 */
		mpi_माप_प्रकार esize = size - 1;	/* even size */
		mpi_limb_t cy_limb;

		MPN_MUL_N_RECURSE(prodp, up, vp, esize, tspace);
		cy_limb = mpihelp_addmul_1(prodp + esize, up, esize, vp[esize]);
		prodp[esize + esize] = cy_limb;
		cy_limb = mpihelp_addmul_1(prodp + esize, vp, size, up[esize]);
		prodp[esize + size] = cy_limb;
	पूर्ण अन्यथा अणु
		/* Anम_से_दij Alekseevich Karatsuba's भागide-and-conquer algorithm.
		 *
		 * Split U in two pieces, U1 and U0, such that
		 * U = U0 + U1*(B**n),
		 * and V in V1 and V0, such that
		 * V = V0 + V1*(B**n).
		 *
		 * UV is then computed recursively using the identity
		 *
		 *        2n   n          n                     n
		 * UV = (B  + B )U V  +  B (U -U )(V -V )  +  (B + 1)U V
		 *                1 1        1  0   0  1              0 0
		 *
		 * Where B = 2**BITS_PER_MP_LIMB.
		 */
		mpi_माप_प्रकार hsize = size >> 1;
		mpi_limb_t cy;
		पूर्णांक negflg;

		/* Product H.      ________________  ________________
		 *                |_____U1 x V1____||____U0 x V0_____|
		 * Put result in upper part of PROD and pass low part of TSPACE
		 * as new TSPACE.
		 */
		MPN_MUL_N_RECURSE(prodp + size, up + hsize, vp + hsize, hsize,
				  tspace);

		/* Product M.      ________________
		 *                |_(U1-U0)(V0-V1)_|
		 */
		अगर (mpihelp_cmp(up + hsize, up, hsize) >= 0) अणु
			mpihelp_sub_n(prodp, up + hsize, up, hsize);
			negflg = 0;
		पूर्ण अन्यथा अणु
			mpihelp_sub_n(prodp, up, up + hsize, hsize);
			negflg = 1;
		पूर्ण
		अगर (mpihelp_cmp(vp + hsize, vp, hsize) >= 0) अणु
			mpihelp_sub_n(prodp + hsize, vp + hsize, vp, hsize);
			negflg ^= 1;
		पूर्ण अन्यथा अणु
			mpihelp_sub_n(prodp + hsize, vp, vp + hsize, hsize);
			/* No change of NEGFLG.  */
		पूर्ण
		/* Read temporary opeअक्रमs from low part of PROD.
		 * Put result in low part of TSPACE using upper part of TSPACE
		 * as new TSPACE.
		 */
		MPN_MUL_N_RECURSE(tspace, prodp, prodp + hsize, hsize,
				  tspace + size);

		/* Add/copy product H. */
		MPN_COPY(prodp + hsize, prodp + size, hsize);
		cy = mpihelp_add_n(prodp + size, prodp + size,
				   prodp + size + hsize, hsize);

		/* Add product M (अगर NEGFLG M is a negative number) */
		अगर (negflg)
			cy -=
			    mpihelp_sub_n(prodp + hsize, prodp + hsize, tspace,
					  size);
		अन्यथा
			cy +=
			    mpihelp_add_n(prodp + hsize, prodp + hsize, tspace,
					  size);

		/* Product L.      ________________  ________________
		 *                |________________||____U0 x V0_____|
		 * Read temporary opeअक्रमs from low part of PROD.
		 * Put result in low part of TSPACE using upper part of TSPACE
		 * as new TSPACE.
		 */
		MPN_MUL_N_RECURSE(tspace, up, vp, hsize, tspace + size);

		/* Add/copy Product L (twice) */

		cy += mpihelp_add_n(prodp + hsize, prodp + hsize, tspace, size);
		अगर (cy)
			mpihelp_add_1(prodp + hsize + size,
				      prodp + hsize + size, hsize, cy);

		MPN_COPY(prodp, tspace, hsize);
		cy = mpihelp_add_n(prodp + hsize, prodp + hsize, tspace + hsize,
				   hsize);
		अगर (cy)
			mpihelp_add_1(prodp + size, prodp + size, size, 1);
	पूर्ण
पूर्ण

व्योम mpih_sqr_n_baseहाल(mpi_ptr_t prodp, mpi_ptr_t up, mpi_माप_प्रकार size)
अणु
	mpi_माप_प्रकार i;
	mpi_limb_t cy_limb;
	mpi_limb_t v_limb;

	/* Multiply by the first limb in V separately, as the result can be
	 * stored (not added) to PROD.  We also aव्योम a loop क्रम zeroing.  */
	v_limb = up[0];
	अगर (v_limb <= 1) अणु
		अगर (v_limb == 1)
			MPN_COPY(prodp, up, size);
		अन्यथा
			MPN_ZERO(prodp, size);
		cy_limb = 0;
	पूर्ण अन्यथा
		cy_limb = mpihelp_mul_1(prodp, up, size, v_limb);

	prodp[size] = cy_limb;
	prodp++;

	/* For each iteration in the outer loop, multiply one limb from
	 * U with one limb from V, and add it to PROD.  */
	क्रम (i = 1; i < size; i++) अणु
		v_limb = up[i];
		अगर (v_limb <= 1) अणु
			cy_limb = 0;
			अगर (v_limb == 1)
				cy_limb = mpihelp_add_n(prodp, prodp, up, size);
		पूर्ण अन्यथा
			cy_limb = mpihelp_addmul_1(prodp, up, size, v_limb);

		prodp[size] = cy_limb;
		prodp++;
	पूर्ण
पूर्ण

व्योम
mpih_sqr_n(mpi_ptr_t prodp, mpi_ptr_t up, mpi_माप_प्रकार size, mpi_ptr_t tspace)
अणु
	अगर (size & 1) अणु
		/* The size is odd, and the code below करोesn't handle that.
		 * Multiply the least signअगरicant (size - 1) limbs with a recursive
		 * call, and handle the most signअगरicant limb of S1 and S2
		 * separately.
		 * A slightly faster way to करो this would be to make the Karatsuba
		 * code below behave as अगर the size were even, and let it check क्रम
		 * odd size in the end.  I.e., in essence move this code to the end.
		 * Doing so would save us a recursive call, and potentially make the
		 * stack grow a lot less.
		 */
		mpi_माप_प्रकार esize = size - 1;	/* even size */
		mpi_limb_t cy_limb;

		MPN_SQR_N_RECURSE(prodp, up, esize, tspace);
		cy_limb = mpihelp_addmul_1(prodp + esize, up, esize, up[esize]);
		prodp[esize + esize] = cy_limb;
		cy_limb = mpihelp_addmul_1(prodp + esize, up, size, up[esize]);

		prodp[esize + size] = cy_limb;
	पूर्ण अन्यथा अणु
		mpi_माप_प्रकार hsize = size >> 1;
		mpi_limb_t cy;

		/* Product H.      ________________  ________________
		 *                |_____U1 x U1____||____U0 x U0_____|
		 * Put result in upper part of PROD and pass low part of TSPACE
		 * as new TSPACE.
		 */
		MPN_SQR_N_RECURSE(prodp + size, up + hsize, hsize, tspace);

		/* Product M.      ________________
		 *                |_(U1-U0)(U0-U1)_|
		 */
		अगर (mpihelp_cmp(up + hsize, up, hsize) >= 0)
			mpihelp_sub_n(prodp, up + hsize, up, hsize);
		अन्यथा
			mpihelp_sub_n(prodp, up, up + hsize, hsize);

		/* Read temporary opeअक्रमs from low part of PROD.
		 * Put result in low part of TSPACE using upper part of TSPACE
		 * as new TSPACE.  */
		MPN_SQR_N_RECURSE(tspace, prodp, hsize, tspace + size);

		/* Add/copy product H  */
		MPN_COPY(prodp + hsize, prodp + size, hsize);
		cy = mpihelp_add_n(prodp + size, prodp + size,
				   prodp + size + hsize, hsize);

		/* Add product M (अगर NEGFLG M is a negative number).  */
		cy -= mpihelp_sub_n(prodp + hsize, prodp + hsize, tspace, size);

		/* Product L.      ________________  ________________
		 *                |________________||____U0 x U0_____|
		 * Read temporary opeअक्रमs from low part of PROD.
		 * Put result in low part of TSPACE using upper part of TSPACE
		 * as new TSPACE.  */
		MPN_SQR_N_RECURSE(tspace, up, hsize, tspace + size);

		/* Add/copy Product L (twice).  */
		cy += mpihelp_add_n(prodp + hsize, prodp + hsize, tspace, size);
		अगर (cy)
			mpihelp_add_1(prodp + hsize + size,
				      prodp + hsize + size, hsize, cy);

		MPN_COPY(prodp, tspace, hsize);
		cy = mpihelp_add_n(prodp + hsize, prodp + hsize, tspace + hsize,
				   hsize);
		अगर (cy)
			mpihelp_add_1(prodp + size, prodp + size, size, 1);
	पूर्ण
पूर्ण


व्योम mpihelp_mul_n(mpi_ptr_t prodp,
		mpi_ptr_t up, mpi_ptr_t vp, mpi_माप_प्रकार size)
अणु
	अगर (up == vp) अणु
		अगर (size < KARATSUBA_THRESHOLD)
			mpih_sqr_n_baseहाल(prodp, up, size);
		अन्यथा अणु
			mpi_ptr_t tspace;
			tspace = mpi_alloc_limb_space(2 * size);
			mpih_sqr_n(prodp, up, size, tspace);
			mpi_मुक्त_limb_space(tspace);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (size < KARATSUBA_THRESHOLD)
			mul_n_baseहाल(prodp, up, vp, size);
		अन्यथा अणु
			mpi_ptr_t tspace;
			tspace = mpi_alloc_limb_space(2 * size);
			mul_n(prodp, up, vp, size, tspace);
			mpi_मुक्त_limb_space(tspace);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक
mpihelp_mul_karatsuba_हाल(mpi_ptr_t prodp,
			   mpi_ptr_t up, mpi_माप_प्रकार usize,
			   mpi_ptr_t vp, mpi_माप_प्रकार vsize,
			   काष्ठा karatsuba_ctx *ctx)
अणु
	mpi_limb_t cy;

	अगर (!ctx->tspace || ctx->tspace_size < vsize) अणु
		अगर (ctx->tspace)
			mpi_मुक्त_limb_space(ctx->tspace);
		ctx->tspace = mpi_alloc_limb_space(2 * vsize);
		अगर (!ctx->tspace)
			वापस -ENOMEM;
		ctx->tspace_size = vsize;
	पूर्ण

	MPN_MUL_N_RECURSE(prodp, up, vp, vsize, ctx->tspace);

	prodp += vsize;
	up += vsize;
	usize -= vsize;
	अगर (usize >= vsize) अणु
		अगर (!ctx->tp || ctx->tp_size < vsize) अणु
			अगर (ctx->tp)
				mpi_मुक्त_limb_space(ctx->tp);
			ctx->tp = mpi_alloc_limb_space(2 * vsize);
			अगर (!ctx->tp) अणु
				अगर (ctx->tspace)
					mpi_मुक्त_limb_space(ctx->tspace);
				ctx->tspace = शून्य;
				वापस -ENOMEM;
			पूर्ण
			ctx->tp_size = vsize;
		पूर्ण

		करो अणु
			MPN_MUL_N_RECURSE(ctx->tp, up, vp, vsize, ctx->tspace);
			cy = mpihelp_add_n(prodp, prodp, ctx->tp, vsize);
			mpihelp_add_1(prodp + vsize, ctx->tp + vsize, vsize,
				      cy);
			prodp += vsize;
			up += vsize;
			usize -= vsize;
		पूर्ण जबतक (usize >= vsize);
	पूर्ण

	अगर (usize) अणु
		अगर (usize < KARATSUBA_THRESHOLD) अणु
			mpi_limb_t पंचांगp;
			अगर (mpihelp_mul(ctx->tspace, vp, vsize, up, usize, &पंचांगp)
			    < 0)
				वापस -ENOMEM;
		पूर्ण अन्यथा अणु
			अगर (!ctx->next) अणु
				ctx->next = kzalloc(माप *ctx, GFP_KERNEL);
				अगर (!ctx->next)
					वापस -ENOMEM;
			पूर्ण
			अगर (mpihelp_mul_karatsuba_हाल(ctx->tspace,
						       vp, vsize,
						       up, usize,
						       ctx->next) < 0)
				वापस -ENOMEM;
		पूर्ण

		cy = mpihelp_add_n(prodp, prodp, ctx->tspace, vsize);
		mpihelp_add_1(prodp + vsize, ctx->tspace + vsize, usize, cy);
	पूर्ण

	वापस 0;
पूर्ण

व्योम mpihelp_release_karatsuba_ctx(काष्ठा karatsuba_ctx *ctx)
अणु
	काष्ठा karatsuba_ctx *ctx2;

	अगर (ctx->tp)
		mpi_मुक्त_limb_space(ctx->tp);
	अगर (ctx->tspace)
		mpi_मुक्त_limb_space(ctx->tspace);
	क्रम (ctx = ctx->next; ctx; ctx = ctx2) अणु
		ctx2 = ctx->next;
		अगर (ctx->tp)
			mpi_मुक्त_limb_space(ctx->tp);
		अगर (ctx->tspace)
			mpi_मुक्त_limb_space(ctx->tspace);
		kमुक्त(ctx);
	पूर्ण
पूर्ण

/* Multiply the natural numbers u (poपूर्णांकed to by UP, with USIZE limbs)
 * and v (poपूर्णांकed to by VP, with VSIZE limbs), and store the result at
 * PRODP.  USIZE + VSIZE limbs are always stored, but अगर the input
 * opeअक्रमs are normalized.  Return the most signअगरicant limb of the
 * result.
 *
 * NOTE: The space poपूर्णांकed to by PRODP is overwritten beक्रमe finished
 * with U and V, so overlap is an error.
 *
 * Argument स्थिरraपूर्णांकs:
 * 1. USIZE >= VSIZE.
 * 2. PRODP != UP and PRODP != VP, i.e. the destination
 *    must be distinct from the multiplier and the multiplicand.
 */

पूर्णांक
mpihelp_mul(mpi_ptr_t prodp, mpi_ptr_t up, mpi_माप_प्रकार usize,
	    mpi_ptr_t vp, mpi_माप_प्रकार vsize, mpi_limb_t *_result)
अणु
	mpi_ptr_t prod_endp = prodp + usize + vsize - 1;
	mpi_limb_t cy;
	काष्ठा karatsuba_ctx ctx;

	अगर (vsize < KARATSUBA_THRESHOLD) अणु
		mpi_माप_प्रकार i;
		mpi_limb_t v_limb;

		अगर (!vsize) अणु
			*_result = 0;
			वापस 0;
		पूर्ण

		/* Multiply by the first limb in V separately, as the result can be
		 * stored (not added) to PROD.  We also aव्योम a loop क्रम zeroing.  */
		v_limb = vp[0];
		अगर (v_limb <= 1) अणु
			अगर (v_limb == 1)
				MPN_COPY(prodp, up, usize);
			अन्यथा
				MPN_ZERO(prodp, usize);
			cy = 0;
		पूर्ण अन्यथा
			cy = mpihelp_mul_1(prodp, up, usize, v_limb);

		prodp[usize] = cy;
		prodp++;

		/* For each iteration in the outer loop, multiply one limb from
		 * U with one limb from V, and add it to PROD.  */
		क्रम (i = 1; i < vsize; i++) अणु
			v_limb = vp[i];
			अगर (v_limb <= 1) अणु
				cy = 0;
				अगर (v_limb == 1)
					cy = mpihelp_add_n(prodp, prodp, up,
							   usize);
			पूर्ण अन्यथा
				cy = mpihelp_addmul_1(prodp, up, usize, v_limb);

			prodp[usize] = cy;
			prodp++;
		पूर्ण

		*_result = cy;
		वापस 0;
	पूर्ण

	स_रखो(&ctx, 0, माप ctx);
	अगर (mpihelp_mul_karatsuba_हाल(prodp, up, usize, vp, vsize, &ctx) < 0)
		वापस -ENOMEM;
	mpihelp_release_karatsuba_ctx(&ctx);
	*_result = *prod_endp;
	वापस 0;
पूर्ण
