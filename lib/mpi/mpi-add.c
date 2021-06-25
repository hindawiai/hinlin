<शैली गुरु>
/* mpi-add.c  -  MPI functions
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

/****************
 * Add the अचिन्हित पूर्णांकeger V to the mpi-पूर्णांकeger U and store the
 * result in W. U and V may be the same.
 */
व्योम mpi_add_ui(MPI w, MPI u, अचिन्हित दीर्घ v)
अणु
	mpi_ptr_t wp, up;
	mpi_माप_प्रकार usize, wsize;
	पूर्णांक usign, wsign;

	usize = u->nlimbs;
	usign = u->sign;
	wsign = 0;

	/* If not space क्रम W (and possible carry), increase space.  */
	wsize = usize + 1;
	अगर (w->alloced < wsize)
		mpi_resize(w, wsize);

	/* These must be after पुनः_स्मृति (U may be the same as W).  */
	up = u->d;
	wp = w->d;

	अगर (!usize) अणु  /* simple */
		wp[0] = v;
		wsize = v ? 1:0;
	पूर्ण अन्यथा अगर (!usign) अणु  /* mpi is not negative */
		mpi_limb_t cy;
		cy = mpihelp_add_1(wp, up, usize, v);
		wp[usize] = cy;
		wsize = usize + cy;
	पूर्ण अन्यथा अणु
		/* The signs are dअगरferent.  Need exact comparison to determine
		 * which opeअक्रम to subtract from which.
		 */
		अगर (usize == 1 && up[0] < v) अणु
			wp[0] = v - up[0];
			wsize = 1;
		पूर्ण अन्यथा अणु
			mpihelp_sub_1(wp, up, usize, v);
			/* Size can decrease with at most one limb. */
			wsize = usize - (wp[usize-1] == 0);
			wsign = 1;
		पूर्ण
	पूर्ण

	w->nlimbs = wsize;
	w->sign   = wsign;
पूर्ण


व्योम mpi_add(MPI w, MPI u, MPI v)
अणु
	mpi_ptr_t wp, up, vp;
	mpi_माप_प्रकार usize, vsize, wsize;
	पूर्णांक usign, vsign, wsign;

	अगर (u->nlimbs < v->nlimbs) अणु /* Swap U and V. */
		usize = v->nlimbs;
		usign = v->sign;
		vsize = u->nlimbs;
		vsign = u->sign;
		wsize = usize + 1;
		RESIZE_IF_NEEDED(w, wsize);
		/* These must be after पुनः_स्मृति (u or v may be the same as w).  */
		up = v->d;
		vp = u->d;
	पूर्ण अन्यथा अणु
		usize = u->nlimbs;
		usign = u->sign;
		vsize = v->nlimbs;
		vsign = v->sign;
		wsize = usize + 1;
		RESIZE_IF_NEEDED(w, wsize);
		/* These must be after पुनः_स्मृति (u or v may be the same as w).  */
		up = u->d;
		vp = v->d;
	पूर्ण
	wp = w->d;
	wsign = 0;

	अगर (!vsize) अणु  /* simple */
		MPN_COPY(wp, up, usize);
		wsize = usize;
		wsign = usign;
	पूर्ण अन्यथा अगर (usign != vsign) अणु /* dअगरferent sign */
		/* This test is right since USIZE >= VSIZE */
		अगर (usize != vsize) अणु
			mpihelp_sub(wp, up, usize, vp, vsize);
			wsize = usize;
			MPN_NORMALIZE(wp, wsize);
			wsign = usign;
		पूर्ण अन्यथा अगर (mpihelp_cmp(up, vp, usize) < 0) अणु
			mpihelp_sub_n(wp, vp, up, usize);
			wsize = usize;
			MPN_NORMALIZE(wp, wsize);
			अगर (!usign)
				wsign = 1;
		पूर्ण अन्यथा अणु
			mpihelp_sub_n(wp, up, vp, usize);
			wsize = usize;
			MPN_NORMALIZE(wp, wsize);
			अगर (usign)
				wsign = 1;
		पूर्ण
	पूर्ण अन्यथा अणु /* U and V have same sign. Add them. */
		mpi_limb_t cy = mpihelp_add(wp, up, usize, vp, vsize);
		wp[usize] = cy;
		wsize = usize + cy;
		अगर (usign)
			wsign = 1;
	पूर्ण

	w->nlimbs = wsize;
	w->sign = wsign;
पूर्ण
EXPORT_SYMBOL_GPL(mpi_add);

व्योम mpi_sub(MPI w, MPI u, MPI v)
अणु
	MPI vv = mpi_copy(v);
	vv->sign = !vv->sign;
	mpi_add(w, u, vv);
	mpi_मुक्त(vv);
पूर्ण


व्योम mpi_addm(MPI w, MPI u, MPI v, MPI m)
अणु
	mpi_add(w, u, v);
	mpi_mod(w, w, m);
पूर्ण
EXPORT_SYMBOL_GPL(mpi_addm);

व्योम mpi_subm(MPI w, MPI u, MPI v, MPI m)
अणु
	mpi_sub(w, u, v);
	mpi_mod(w, w, m);
पूर्ण
EXPORT_SYMBOL_GPL(mpi_subm);
