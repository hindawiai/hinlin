<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* mpi-घात.c  -  MPI functions
 *	Copyright (C) 1994, 1996, 1998, 2000 Free Software Foundation, Inc.
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

#समावेश <linux/sched.h>
#समावेश <linux/माला.स>
#समावेश "mpi-internal.h"
#समावेश "longlong.h"

/****************
 * RES = BASE ^ EXP mod MOD
 */
पूर्णांक mpi_घातm(MPI res, MPI base, MPI exp, MPI mod)
अणु
	mpi_ptr_t mp_marker = शून्य, bp_marker = शून्य, ep_marker = शून्य;
	काष्ठा karatsuba_ctx karactx = अणुपूर्ण;
	mpi_ptr_t xp_marker = शून्य;
	mpi_ptr_t tspace = शून्य;
	mpi_ptr_t rp, ep, mp, bp;
	mpi_माप_प्रकार esize, msize, bsize, rsize;
	पूर्णांक msign, bsign, rsign;
	mpi_माप_प्रकार size;
	पूर्णांक mod_shअगरt_cnt;
	पूर्णांक negative_result;
	पूर्णांक assign_rp = 0;
	mpi_माप_प्रकार tsize = 0;	/* to aव्योम compiler warning */
	/* fixme: we should check that the warning is व्योम */
	पूर्णांक rc = -ENOMEM;

	esize = exp->nlimbs;
	msize = mod->nlimbs;
	size = 2 * msize;
	msign = mod->sign;

	rp = res->d;
	ep = exp->d;

	अगर (!msize)
		वापस -EINVAL;

	अगर (!esize) अणु
		/* Exponent is zero, result is 1 mod MOD, i.e., 1 or 0
		 * depending on अगर MOD equals 1.  */
		res->nlimbs = (msize == 1 && mod->d[0] == 1) ? 0 : 1;
		अगर (res->nlimbs) अणु
			अगर (mpi_resize(res, 1) < 0)
				जाओ enomem;
			rp = res->d;
			rp[0] = 1;
		पूर्ण
		res->sign = 0;
		जाओ leave;
	पूर्ण

	/* Normalize MOD (i.e. make its most signअगरicant bit set) as required by
	 * mpn_भागrem.  This will make the पूर्णांकermediate values in the calculation
	 * slightly larger, but the correct result is obtained after a final
	 * reduction using the original MOD value.  */
	mp = mp_marker = mpi_alloc_limb_space(msize);
	अगर (!mp)
		जाओ enomem;
	mod_shअगरt_cnt = count_leading_zeros(mod->d[msize - 1]);
	अगर (mod_shअगरt_cnt)
		mpihelp_lshअगरt(mp, mod->d, msize, mod_shअगरt_cnt);
	अन्यथा
		MPN_COPY(mp, mod->d, msize);

	bsize = base->nlimbs;
	bsign = base->sign;
	अगर (bsize > msize) अणु	/* The base is larger than the module. Reduce it. */
		/* Allocate (BSIZE + 1) with space क्रम reमुख्यder and quotient.
		 * (The quotient is (bsize - msize + 1) limbs.)  */
		bp = bp_marker = mpi_alloc_limb_space(bsize + 1);
		अगर (!bp)
			जाओ enomem;
		MPN_COPY(bp, base->d, bsize);
		/* We करोn't care about the quotient, store it above the reमुख्यder,
		 * at BP + MSIZE.  */
		mpihelp_भागrem(bp + msize, 0, bp, bsize, mp, msize);
		bsize = msize;
		/* Canonicalize the base, since we are going to multiply with it
		 * quite a few बार.  */
		MPN_NORMALIZE(bp, bsize);
	पूर्ण अन्यथा
		bp = base->d;

	अगर (!bsize) अणु
		res->nlimbs = 0;
		res->sign = 0;
		जाओ leave;
	पूर्ण

	अगर (res->alloced < size) अणु
		/* We have to allocate more space क्रम RES.  If any of the input
		 * parameters are identical to RES, defer deallocation of the old
		 * space.  */
		अगर (rp == ep || rp == mp || rp == bp) अणु
			rp = mpi_alloc_limb_space(size);
			अगर (!rp)
				जाओ enomem;
			assign_rp = 1;
		पूर्ण अन्यथा अणु
			अगर (mpi_resize(res, size) < 0)
				जाओ enomem;
			rp = res->d;
		पूर्ण
	पूर्ण अन्यथा अणु		/* Make BASE, EXP and MOD not overlap with RES.  */
		अगर (rp == bp) अणु
			/* RES and BASE are identical.  Allocate temp. space क्रम BASE.  */
			BUG_ON(bp_marker);
			bp = bp_marker = mpi_alloc_limb_space(bsize);
			अगर (!bp)
				जाओ enomem;
			MPN_COPY(bp, rp, bsize);
		पूर्ण
		अगर (rp == ep) अणु
			/* RES and EXP are identical.  Allocate temp. space क्रम EXP.  */
			ep = ep_marker = mpi_alloc_limb_space(esize);
			अगर (!ep)
				जाओ enomem;
			MPN_COPY(ep, rp, esize);
		पूर्ण
		अगर (rp == mp) अणु
			/* RES and MOD are identical.  Allocate temporary space क्रम MOD. */
			BUG_ON(mp_marker);
			mp = mp_marker = mpi_alloc_limb_space(msize);
			अगर (!mp)
				जाओ enomem;
			MPN_COPY(mp, rp, msize);
		पूर्ण
	पूर्ण

	MPN_COPY(rp, bp, bsize);
	rsize = bsize;
	rsign = bsign;

	अणु
		mpi_माप_प्रकार i;
		mpi_ptr_t xp;
		पूर्णांक c;
		mpi_limb_t e;
		mpi_limb_t carry_limb;

		xp = xp_marker = mpi_alloc_limb_space(2 * (msize + 1));
		अगर (!xp)
			जाओ enomem;

		negative_result = (ep[0] & 1) && base->sign;

		i = esize - 1;
		e = ep[i];
		c = count_leading_zeros(e);
		e = (e << c) << 1;	/* shअगरt the exp bits to the left, lose msb */
		c = BITS_PER_MPI_LIMB - 1 - c;

		/* Main loop.
		 *
		 * Make the result be poपूर्णांकed to alternately by XP and RP.  This
		 * helps us aव्योम block copying, which would otherwise be necessary
		 * with the overlap restrictions of mpihelp_भागmod. With 50% probability
		 * the result after this loop will be in the area originally poपूर्णांकed
		 * by RP (==RES->d), and with 50% probability in the area originally
		 * poपूर्णांकed to by XP.
		 */

		क्रम (;;) अणु
			जबतक (c) अणु
				mpi_ptr_t tp;
				mpi_माप_प्रकार xsize;

				/*अगर (mpihelp_mul_n(xp, rp, rp, rsize) < 0) जाओ enomem */
				अगर (rsize < KARATSUBA_THRESHOLD)
					mpih_sqr_n_baseहाल(xp, rp, rsize);
				अन्यथा अणु
					अगर (!tspace) अणु
						tsize = 2 * rsize;
						tspace =
						    mpi_alloc_limb_space(tsize);
						अगर (!tspace)
							जाओ enomem;
					पूर्ण अन्यथा अगर (tsize < (2 * rsize)) अणु
						mpi_मुक्त_limb_space(tspace);
						tsize = 2 * rsize;
						tspace =
						    mpi_alloc_limb_space(tsize);
						अगर (!tspace)
							जाओ enomem;
					पूर्ण
					mpih_sqr_n(xp, rp, rsize, tspace);
				पूर्ण

				xsize = 2 * rsize;
				अगर (xsize > msize) अणु
					mpihelp_भागrem(xp + msize, 0, xp, xsize,
						       mp, msize);
					xsize = msize;
				पूर्ण

				tp = rp;
				rp = xp;
				xp = tp;
				rsize = xsize;

				अगर ((mpi_limb_चिन्हित_t) e < 0) अणु
					/*mpihelp_mul( xp, rp, rsize, bp, bsize ); */
					अगर (bsize < KARATSUBA_THRESHOLD) अणु
						mpi_limb_t पंचांगp;
						अगर (mpihelp_mul
						    (xp, rp, rsize, bp, bsize,
						     &पंचांगp) < 0)
							जाओ enomem;
					पूर्ण अन्यथा अणु
						अगर (mpihelp_mul_karatsuba_हाल
						    (xp, rp, rsize, bp, bsize,
						     &karactx) < 0)
							जाओ enomem;
					पूर्ण

					xsize = rsize + bsize;
					अगर (xsize > msize) अणु
						mpihelp_भागrem(xp + msize, 0,
							       xp, xsize, mp,
							       msize);
						xsize = msize;
					पूर्ण

					tp = rp;
					rp = xp;
					xp = tp;
					rsize = xsize;
				पूर्ण
				e <<= 1;
				c--;
				cond_resched();
			पूर्ण

			i--;
			अगर (i < 0)
				अवरोध;
			e = ep[i];
			c = BITS_PER_MPI_LIMB;
		पूर्ण

		/* We shअगरted MOD, the modulo reduction argument, left MOD_SHIFT_CNT
		 * steps.  Adjust the result by reducing it with the original MOD.
		 *
		 * Also make sure the result is put in RES->d (where it alपढ़ोy
		 * might be, see above).
		 */
		अगर (mod_shअगरt_cnt) अणु
			carry_limb =
			    mpihelp_lshअगरt(res->d, rp, rsize, mod_shअगरt_cnt);
			rp = res->d;
			अगर (carry_limb) अणु
				rp[rsize] = carry_limb;
				rsize++;
			पूर्ण
		पूर्ण अन्यथा अणु
			MPN_COPY(res->d, rp, rsize);
			rp = res->d;
		पूर्ण

		अगर (rsize >= msize) अणु
			mpihelp_भागrem(rp + msize, 0, rp, rsize, mp, msize);
			rsize = msize;
		पूर्ण

		/* Remove any leading zero words from the result.  */
		अगर (mod_shअगरt_cnt)
			mpihelp_rshअगरt(rp, rp, rsize, mod_shअगरt_cnt);
		MPN_NORMALIZE(rp, rsize);
	पूर्ण

	अगर (negative_result && rsize) अणु
		अगर (mod_shअगरt_cnt)
			mpihelp_rshअगरt(mp, mp, msize, mod_shअगरt_cnt);
		mpihelp_sub(rp, mp, msize, rp, rsize);
		rsize = msize;
		rsign = msign;
		MPN_NORMALIZE(rp, rsize);
	पूर्ण
	res->nlimbs = rsize;
	res->sign = rsign;

leave:
	rc = 0;
enomem:
	mpihelp_release_karatsuba_ctx(&karactx);
	अगर (assign_rp)
		mpi_assign_limb_space(res, rp, size);
	अगर (mp_marker)
		mpi_मुक्त_limb_space(mp_marker);
	अगर (bp_marker)
		mpi_मुक्त_limb_space(bp_marker);
	अगर (ep_marker)
		mpi_मुक्त_limb_space(ep_marker);
	अगर (xp_marker)
		mpi_मुक्त_limb_space(xp_marker);
	अगर (tspace)
		mpi_मुक्त_limb_space(tspace);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(mpi_घातm);
