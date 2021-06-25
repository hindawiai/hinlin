<शैली गुरु>
/* mpi-भाग.c  -  MPI functions
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
#समावेश "longlong.h"

व्योम mpi_tभाग_qr(MPI quot, MPI rem, MPI num, MPI den);
व्योम mpi_fभाग_qr(MPI quot, MPI rem, MPI भागidend, MPI भागisor);

व्योम mpi_fभाग_r(MPI rem, MPI भागidend, MPI भागisor)
अणु
	पूर्णांक भागisor_sign = भागisor->sign;
	MPI temp_भागisor = शून्य;

	/* We need the original value of the भागisor after the reमुख्यder has been
	 * preliminary calculated.	We have to copy it to temporary space अगर it's
	 * the same variable as REM.
	 */
	अगर (rem == भागisor) अणु
		temp_भागisor = mpi_copy(भागisor);
		भागisor = temp_भागisor;
	पूर्ण

	mpi_tभाग_r(rem, भागidend, भागisor);

	अगर (((भागisor_sign?1:0) ^ (भागidend->sign?1:0)) && rem->nlimbs)
		mpi_add(rem, rem, भागisor);

	अगर (temp_भागisor)
		mpi_मुक्त(temp_भागisor);
पूर्ण

व्योम mpi_fभाग_q(MPI quot, MPI भागidend, MPI भागisor)
अणु
	MPI पंचांगp = mpi_alloc(mpi_get_nlimbs(quot));
	mpi_fभाग_qr(quot, पंचांगp, भागidend, भागisor);
	mpi_मुक्त(पंचांगp);
पूर्ण

व्योम mpi_fभाग_qr(MPI quot, MPI rem, MPI भागidend, MPI भागisor)
अणु
	पूर्णांक भागisor_sign = भागisor->sign;
	MPI temp_भागisor = शून्य;

	अगर (quot == भागisor || rem == भागisor) अणु
		temp_भागisor = mpi_copy(भागisor);
		भागisor = temp_भागisor;
	पूर्ण

	mpi_tभाग_qr(quot, rem, भागidend, भागisor);

	अगर ((भागisor_sign ^ भागidend->sign) && rem->nlimbs) अणु
		mpi_sub_ui(quot, quot, 1);
		mpi_add(rem, rem, भागisor);
	पूर्ण

	अगर (temp_भागisor)
		mpi_मुक्त(temp_भागisor);
पूर्ण

/* If den == quot, den needs temporary storage.
 * If den == rem, den needs temporary storage.
 * If num == quot, num needs temporary storage.
 * If den has temporary storage, it can be normalized जबतक being copied,
 *   i.e no extra storage should be allocated.
 */

व्योम mpi_tभाग_r(MPI rem, MPI num, MPI den)
अणु
	mpi_tभाग_qr(शून्य, rem, num, den);
पूर्ण

व्योम mpi_tभाग_qr(MPI quot, MPI rem, MPI num, MPI den)
अणु
	mpi_ptr_t np, dp;
	mpi_ptr_t qp, rp;
	mpi_माप_प्रकार nsize = num->nlimbs;
	mpi_माप_प्रकार dsize = den->nlimbs;
	mpi_माप_प्रकार qsize, rsize;
	mpi_माप_प्रकार sign_reमुख्यder = num->sign;
	mpi_माप_प्रकार sign_quotient = num->sign ^ den->sign;
	अचिन्हित पूर्णांक normalization_steps;
	mpi_limb_t q_limb;
	mpi_ptr_t marker[5];
	पूर्णांक markidx = 0;

	/* Ensure space is enough क्रम quotient and reमुख्यder.
	 * We need space क्रम an extra limb in the reमुख्यder, because it's
	 * up-shअगरted (normalized) below.
	 */
	rsize = nsize + 1;
	mpi_resize(rem, rsize);

	qsize = rsize - dsize;	  /* qsize cannot be bigger than this.	*/
	अगर (qsize <= 0) अणु
		अगर (num != rem) अणु
			rem->nlimbs = num->nlimbs;
			rem->sign = num->sign;
			MPN_COPY(rem->d, num->d, nsize);
		पूर्ण
		अगर (quot) अणु
			/* This needs to follow the assignment to rem, in हाल the
			 * numerator and quotient are the same.
			 */
			quot->nlimbs = 0;
			quot->sign = 0;
		पूर्ण
		वापस;
	पूर्ण

	अगर (quot)
		mpi_resize(quot, qsize);

	/* Read poपूर्णांकers here, when पुनः_स्मृतिation is finished.  */
	np = num->d;
	dp = den->d;
	rp = rem->d;

	/* Optimize भागision by a single-limb भागisor.  */
	अगर (dsize == 1) अणु
		mpi_limb_t rlimb;
		अगर (quot) अणु
			qp = quot->d;
			rlimb = mpihelp_भागmod_1(qp, np, nsize, dp[0]);
			qsize -= qp[qsize - 1] == 0;
			quot->nlimbs = qsize;
			quot->sign = sign_quotient;
		पूर्ण अन्यथा
			rlimb = mpihelp_mod_1(np, nsize, dp[0]);
		rp[0] = rlimb;
		rsize = rlimb != 0?1:0;
		rem->nlimbs = rsize;
		rem->sign = sign_reमुख्यder;
		वापस;
	पूर्ण


	अगर (quot) अणु
		qp = quot->d;
		/* Make sure QP and NP poपूर्णांक to dअगरferent objects.  Otherwise the
		 * numerator would be gradually overwritten by the quotient limbs.
		 */
		अगर (qp == np) अणु /* Copy NP object to temporary space.  */
			np = marker[markidx++] = mpi_alloc_limb_space(nsize);
			MPN_COPY(np, qp, nsize);
		पूर्ण
	पूर्ण अन्यथा /* Put quotient at top of reमुख्यder. */
		qp = rp + dsize;

	normalization_steps = count_leading_zeros(dp[dsize - 1]);

	/* Normalize the denominator, i.e. make its most signअगरicant bit set by
	 * shअगरting it NORMALIZATION_STEPS bits to the left.  Also shअगरt the
	 * numerator the same number of steps (to keep the quotient the same!).
	 */
	अगर (normalization_steps) अणु
		mpi_ptr_t tp;
		mpi_limb_t nlimb;

		/* Shअगरt up the denominator setting the most signअगरicant bit of
		 * the most signअगरicant word.  Use temporary storage not to clobber
		 * the original contents of the denominator.
		 */
		tp = marker[markidx++] = mpi_alloc_limb_space(dsize);
		mpihelp_lshअगरt(tp, dp, dsize, normalization_steps);
		dp = tp;

		/* Shअगरt up the numerator, possibly पूर्णांकroducing a new most
		 * signअगरicant word.  Move the shअगरted numerator in the reमुख्यder
		 * meanजबतक.
		 */
		nlimb = mpihelp_lshअगरt(rp, np, nsize, normalization_steps);
		अगर (nlimb) अणु
			rp[nsize] = nlimb;
			rsize = nsize + 1;
		पूर्ण अन्यथा
			rsize = nsize;
	पूर्ण अन्यथा अणु
		/* The denominator is alपढ़ोy normalized, as required.	Copy it to
		 * temporary space अगर it overlaps with the quotient or reमुख्यder.
		 */
		अगर (dp == rp || (quot && (dp == qp))) अणु
			mpi_ptr_t tp;

			tp = marker[markidx++] = mpi_alloc_limb_space(dsize);
			MPN_COPY(tp, dp, dsize);
			dp = tp;
		पूर्ण

		/* Move the numerator to the reमुख्यder.  */
		अगर (rp != np)
			MPN_COPY(rp, np, nsize);

		rsize = nsize;
	पूर्ण

	q_limb = mpihelp_भागrem(qp, 0, rp, rsize, dp, dsize);

	अगर (quot) अणु
		qsize = rsize - dsize;
		अगर (q_limb) अणु
			qp[qsize] = q_limb;
			qsize += 1;
		पूर्ण

		quot->nlimbs = qsize;
		quot->sign = sign_quotient;
	पूर्ण

	rsize = dsize;
	MPN_NORMALIZE(rp, rsize);

	अगर (normalization_steps && rsize) अणु
		mpihelp_rshअगरt(rp, rp, rsize, normalization_steps);
		rsize -= rp[rsize - 1] == 0?1:0;
	पूर्ण

	rem->nlimbs = rsize;
	rem->sign	= sign_reमुख्यder;
	जबतक (markidx) अणु
		markidx--;
		mpi_मुक्त_limb_space(marker[markidx]);
	पूर्ण
पूर्ण
