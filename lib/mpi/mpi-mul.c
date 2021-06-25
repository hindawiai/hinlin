<शैली गुरु>
/* mpi-mul.c  -  MPI functions
 * Copyright (C) 1994, 1996, 1998, 2001, 2002,
 *               2003 Free Software Foundation, Inc.
 *
 * This file is part of Libgcrypt.
 *
 * Note: This code is heavily based on the GNU MP Library.
 *	 Actually it's the same code with only minor changes in the
 *	 way the data is stored; this is to support the असलtraction
 *	 of an optional secure memory allocation which may be used
 *	 to aव्योम revealing of sensitive data due to paging etc.
 */

#समावेश "mpi-internal.h"

व्योम mpi_mul(MPI w, MPI u, MPI v)
अणु
	mpi_माप_प्रकार usize, vsize, wsize;
	mpi_ptr_t up, vp, wp;
	mpi_limb_t cy;
	पूर्णांक usign, vsign, sign_product;
	पूर्णांक assign_wp = 0;
	mpi_ptr_t पंचांगp_limb = शून्य;

	अगर (u->nlimbs < v->nlimbs) अणु
		/* Swap U and V. */
		usize = v->nlimbs;
		usign = v->sign;
		up    = v->d;
		vsize = u->nlimbs;
		vsign = u->sign;
		vp    = u->d;
	पूर्ण अन्यथा अणु
		usize = u->nlimbs;
		usign = u->sign;
		up    = u->d;
		vsize = v->nlimbs;
		vsign = v->sign;
		vp    = v->d;
	पूर्ण
	sign_product = usign ^ vsign;
	wp = w->d;

	/* Ensure W has space enough to store the result.  */
	wsize = usize + vsize;
	अगर (w->alloced < wsize) अणु
		अगर (wp == up || wp == vp) अणु
			wp = mpi_alloc_limb_space(wsize);
			assign_wp = 1;
		पूर्ण अन्यथा अणु
			mpi_resize(w, wsize);
			wp = w->d;
		पूर्ण
	पूर्ण अन्यथा अणु /* Make U and V not overlap with W.	*/
		अगर (wp == up) अणु
			/* W and U are identical.  Allocate temporary space क्रम U. */
			up = पंचांगp_limb = mpi_alloc_limb_space(usize);
			/* Is V identical too?  Keep it identical with U.  */
			अगर (wp == vp)
				vp = up;
			/* Copy to the temporary space.  */
			MPN_COPY(up, wp, usize);
		पूर्ण अन्यथा अगर (wp == vp) अणु
			/* W and V are identical.  Allocate temporary space क्रम V. */
			vp = पंचांगp_limb = mpi_alloc_limb_space(vsize);
			/* Copy to the temporary space.  */
			MPN_COPY(vp, wp, vsize);
		पूर्ण
	पूर्ण

	अगर (!vsize)
		wsize = 0;
	अन्यथा अणु
		mpihelp_mul(wp, up, usize, vp, vsize, &cy);
		wsize -= cy ? 0:1;
	पूर्ण

	अगर (assign_wp)
		mpi_assign_limb_space(w, wp, wsize);
	w->nlimbs = wsize;
	w->sign = sign_product;
	अगर (पंचांगp_limb)
		mpi_मुक्त_limb_space(पंचांगp_limb);
पूर्ण

व्योम mpi_mulm(MPI w, MPI u, MPI v, MPI m)
अणु
	mpi_mul(w, u, v);
	mpi_tभाग_r(w, w, m);
पूर्ण
EXPORT_SYMBOL_GPL(mpi_mulm);
