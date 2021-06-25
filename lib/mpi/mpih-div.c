<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* mpihelp-भाग.c  -  MPI helper functions
 *	Copyright (C) 1994, 1996 Free Software Foundation, Inc.
 *	Copyright (C) 1998, 1999 Free Software Foundation, Inc.
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

#समावेश "mpi-internal.h"
#समावेश "longlong.h"

#अगर_अघोषित UMUL_TIME
#घोषणा UMUL_TIME 1
#पूर्ण_अगर
#अगर_अघोषित UDIV_TIME
#घोषणा UDIV_TIME UMUL_TIME
#पूर्ण_अगर


mpi_limb_t
mpihelp_mod_1(mpi_ptr_t भागidend_ptr, mpi_माप_प्रकार भागidend_size,
			mpi_limb_t भागisor_limb)
अणु
	mpi_माप_प्रकार i;
	mpi_limb_t n1, n0, r;
	mpi_limb_t dummy __maybe_unused;

	/* Botch: Should this be handled at all?  Rely on callers?	*/
	अगर (!भागidend_size)
		वापस 0;

	/* If multiplication is much faster than भागision, and the
	 * भागidend is large, pre-invert the भागisor, and use
	 * only multiplications in the inner loop.
	 *
	 * This test should be पढ़ो:
	 *	 Does it ever help to use uभाग_qrnnd_preinv?
	 *	   && Does what we save compensate क्रम the inversion overhead?
	 */
	अगर (UDIV_TIME > (2 * UMUL_TIME + 6)
			&& (UDIV_TIME - (2 * UMUL_TIME + 6)) * भागidend_size > UDIV_TIME) अणु
		पूर्णांक normalization_steps;

		normalization_steps = count_leading_zeros(भागisor_limb);
		अगर (normalization_steps) अणु
			mpi_limb_t भागisor_limb_inverted;

			भागisor_limb <<= normalization_steps;

			/* Compute (2**2N - 2**N * DIVISOR_LIMB) / DIVISOR_LIMB.  The
			 * result is a (N+1)-bit approximation to 1/DIVISOR_LIMB, with the
			 * most signअगरicant bit (with weight 2**N) implicit.
			 *
			 * Special हाल क्रम DIVISOR_LIMB == 100...000.
			 */
			अगर (!(भागisor_limb << 1))
				भागisor_limb_inverted = ~(mpi_limb_t)0;
			अन्यथा
				uभाग_qrnnd(भागisor_limb_inverted, dummy,
						-भागisor_limb, 0, भागisor_limb);

			n1 = भागidend_ptr[भागidend_size - 1];
			r = n1 >> (BITS_PER_MPI_LIMB - normalization_steps);

			/* Possible optimization:
			 * अगर (r == 0
			 * && भागisor_limb > ((n1 << normalization_steps)
			 *		       | (भागidend_ptr[भागidend_size - 2] >> ...)))
			 * ...one भागision less...
			 */
			क्रम (i = भागidend_size - 2; i >= 0; i--) अणु
				n0 = भागidend_ptr[i];
				UDIV_QRNND_PREINV(dummy, r, r,
						((n1 << normalization_steps)
						 | (n0 >> (BITS_PER_MPI_LIMB - normalization_steps))),
						भागisor_limb, भागisor_limb_inverted);
				n1 = n0;
			पूर्ण
			UDIV_QRNND_PREINV(dummy, r, r,
					n1 << normalization_steps,
					भागisor_limb, भागisor_limb_inverted);
			वापस r >> normalization_steps;
		पूर्ण अन्यथा अणु
			mpi_limb_t भागisor_limb_inverted;

			/* Compute (2**2N - 2**N * DIVISOR_LIMB) / DIVISOR_LIMB.  The
			 * result is a (N+1)-bit approximation to 1/DIVISOR_LIMB, with the
			 * most signअगरicant bit (with weight 2**N) implicit.
			 *
			 * Special हाल क्रम DIVISOR_LIMB == 100...000.
			 */
			अगर (!(भागisor_limb << 1))
				भागisor_limb_inverted = ~(mpi_limb_t)0;
			अन्यथा
				uभाग_qrnnd(भागisor_limb_inverted, dummy,
						-भागisor_limb, 0, भागisor_limb);

			i = भागidend_size - 1;
			r = भागidend_ptr[i];

			अगर (r >= भागisor_limb)
				r = 0;
			अन्यथा
				i--;

			क्रम ( ; i >= 0; i--) अणु
				n0 = भागidend_ptr[i];
				UDIV_QRNND_PREINV(dummy, r, r,
						n0, भागisor_limb, भागisor_limb_inverted);
			पूर्ण
			वापस r;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (UDIV_NEEDS_NORMALIZATION) अणु
			पूर्णांक normalization_steps;

			normalization_steps = count_leading_zeros(भागisor_limb);
			अगर (normalization_steps) अणु
				भागisor_limb <<= normalization_steps;

				n1 = भागidend_ptr[भागidend_size - 1];
				r = n1 >> (BITS_PER_MPI_LIMB - normalization_steps);

				/* Possible optimization:
				 * अगर (r == 0
				 * && भागisor_limb > ((n1 << normalization_steps)
				 *		   | (भागidend_ptr[भागidend_size - 2] >> ...)))
				 * ...one भागision less...
				 */
				क्रम (i = भागidend_size - 2; i >= 0; i--) अणु
					n0 = भागidend_ptr[i];
					uभाग_qrnnd(dummy, r, r,
						((n1 << normalization_steps)
						 | (n0 >> (BITS_PER_MPI_LIMB - normalization_steps))),
						भागisor_limb);
					n1 = n0;
				पूर्ण
				uभाग_qrnnd(dummy, r, r,
						n1 << normalization_steps,
						भागisor_limb);
				वापस r >> normalization_steps;
			पूर्ण
		पूर्ण
		/* No normalization needed, either because uभाग_qrnnd करोesn't require
		 * it, or because DIVISOR_LIMB is alपढ़ोy normalized.
		 */
		i = भागidend_size - 1;
		r = भागidend_ptr[i];

		अगर (r >= भागisor_limb)
			r = 0;
		अन्यथा
			i--;

		क्रम (; i >= 0; i--) अणु
			n0 = भागidend_ptr[i];
			uभाग_qrnnd(dummy, r, r, n0, भागisor_limb);
		पूर्ण
		वापस r;
	पूर्ण
पूर्ण

/* Divide num (NP/NSIZE) by den (DP/DSIZE) and ग_लिखो
 * the NSIZE-DSIZE least signअगरicant quotient limbs at QP
 * and the DSIZE दीर्घ reमुख्यder at NP.	If QEXTRA_LIMBS is
 * non-zero, generate that many fraction bits and append them after the
 * other quotient limbs.
 * Return the most signअगरicant limb of the quotient, this is always 0 or 1.
 *
 * Preconditions:
 * 0. NSIZE >= DSIZE.
 * 1. The most signअगरicant bit of the भागisor must be set.
 * 2. QP must either not overlap with the input opeअक्रमs at all, or
 *    QP + DSIZE >= NP must hold true.	(This means that it's
 *    possible to put the quotient in the high part of NUM, right after the
 *    reमुख्यder in NUM.
 * 3. NSIZE >= DSIZE, even अगर QEXTRA_LIMBS is non-zero.
 */

mpi_limb_t
mpihelp_भागrem(mpi_ptr_t qp, mpi_माप_प्रकार qextra_limbs,
	       mpi_ptr_t np, mpi_माप_प्रकार nsize, mpi_ptr_t dp, mpi_माप_प्रकार dsize)
अणु
	mpi_limb_t most_signअगरicant_q_limb = 0;

	चयन (dsize) अणु
	हाल 0:
		/* We are asked to भागide by zero, so go ahead and करो it!  (To make
		   the compiler not हटाओ this statement, वापस the value.)  */
		/*
		 * existing clients of this function have been modअगरied
		 * not to call it with dsize == 0, so this should not happen
		 */
		वापस 1 / dsize;

	हाल 1:
		अणु
			mpi_माप_प्रकार i;
			mpi_limb_t n1;
			mpi_limb_t d;

			d = dp[0];
			n1 = np[nsize - 1];

			अगर (n1 >= d) अणु
				n1 -= d;
				most_signअगरicant_q_limb = 1;
			पूर्ण

			qp += qextra_limbs;
			क्रम (i = nsize - 2; i >= 0; i--)
				uभाग_qrnnd(qp[i], n1, n1, np[i], d);
			qp -= qextra_limbs;

			क्रम (i = qextra_limbs - 1; i >= 0; i--)
				uभाग_qrnnd(qp[i], n1, n1, 0, d);

			np[0] = n1;
		पूर्ण
		अवरोध;

	हाल 2:
		अणु
			mpi_माप_प्रकार i;
			mpi_limb_t n1, n0, n2;
			mpi_limb_t d1, d0;

			np += nsize - 2;
			d1 = dp[1];
			d0 = dp[0];
			n1 = np[1];
			n0 = np[0];

			अगर (n1 >= d1 && (n1 > d1 || n0 >= d0)) अणु
				sub_ddmmss(n1, n0, n1, n0, d1, d0);
				most_signअगरicant_q_limb = 1;
			पूर्ण

			क्रम (i = qextra_limbs + nsize - 2 - 1; i >= 0; i--) अणु
				mpi_limb_t q;
				mpi_limb_t r;

				अगर (i >= qextra_limbs)
					np--;
				अन्यथा
					np[0] = 0;

				अगर (n1 == d1) अणु
					/* Q should be either 111..111 or 111..110.  Need special
					 * treaपंचांगent of this rare हाल as normal भागision would
					 * give overflow.  */
					q = ~(mpi_limb_t) 0;

					r = n0 + d1;
					अगर (r < d1) अणु	/* Carry in the addition? */
						add_ssaaaa(n1, n0, r - d0,
							   np[0], 0, d0);
						qp[i] = q;
						जारी;
					पूर्ण
					n1 = d0 - (d0 != 0 ? 1 : 0);
					n0 = -d0;
				पूर्ण अन्यथा अणु
					uभाग_qrnnd(q, r, n1, n0, d1);
					umul_ppmm(n1, n0, d0, q);
				पूर्ण

				n2 = np[0];
q_test:
				अगर (n1 > r || (n1 == r && n0 > n2)) अणु
					/* The estimated Q was too large.  */
					q--;
					sub_ddmmss(n1, n0, n1, n0, 0, d0);
					r += d1;
					अगर (r >= d1)	/* If not carry, test Q again.  */
						जाओ q_test;
				पूर्ण

				qp[i] = q;
				sub_ddmmss(n1, n0, r, n2, n1, n0);
			पूर्ण
			np[1] = n1;
			np[0] = n0;
		पूर्ण
		अवरोध;

	शेष:
		अणु
			mpi_माप_प्रकार i;
			mpi_limb_t dX, d1, n0;

			np += nsize - dsize;
			dX = dp[dsize - 1];
			d1 = dp[dsize - 2];
			n0 = np[dsize - 1];

			अगर (n0 >= dX) अणु
				अगर (n0 > dX
				    || mpihelp_cmp(np, dp, dsize - 1) >= 0) अणु
					mpihelp_sub_n(np, np, dp, dsize);
					n0 = np[dsize - 1];
					most_signअगरicant_q_limb = 1;
				पूर्ण
			पूर्ण

			क्रम (i = qextra_limbs + nsize - dsize - 1; i >= 0; i--) अणु
				mpi_limb_t q;
				mpi_limb_t n1, n2;
				mpi_limb_t cy_limb;

				अगर (i >= qextra_limbs) अणु
					np--;
					n2 = np[dsize];
				पूर्ण अन्यथा अणु
					n2 = np[dsize - 1];
					MPN_COPY_DECR(np + 1, np, dsize - 1);
					np[0] = 0;
				पूर्ण

				अगर (n0 == dX) अणु
					/* This might over-estimate q, but it's probably not worth
					 * the extra code here to find out.  */
					q = ~(mpi_limb_t) 0;
				पूर्ण अन्यथा अणु
					mpi_limb_t r;

					uभाग_qrnnd(q, r, n0, np[dsize - 1], dX);
					umul_ppmm(n1, n0, d1, q);

					जबतक (n1 > r
					       || (n1 == r
						   && n0 > np[dsize - 2])) अणु
						q--;
						r += dX;
						अगर (r < dX)	/* I.e. "carry in previous addition?" */
							अवरोध;
						n1 -= n0 < d1;
						n0 -= d1;
					पूर्ण
				पूर्ण

				/* Possible optimization: We alपढ़ोy have (q * n0) and (1 * n1)
				 * after the calculation of q.  Taking advantage of that, we
				 * could make this loop make two iterations less.  */
				cy_limb = mpihelp_submul_1(np, dp, dsize, q);

				अगर (n2 != cy_limb) अणु
					mpihelp_add_n(np, np, dp, dsize);
					q--;
				पूर्ण

				qp[i] = q;
				n0 = np[dsize - 1];
			पूर्ण
		पूर्ण
	पूर्ण

	वापस most_signअगरicant_q_limb;
पूर्ण

/****************
 * Divide (DIVIDEND_PTR,,DIVIDEND_SIZE) by DIVISOR_LIMB.
 * Write DIVIDEND_SIZE limbs of quotient at QUOT_PTR.
 * Return the single-limb reमुख्यder.
 * There are no स्थिरraपूर्णांकs on the value of the भागisor.
 *
 * QUOT_PTR and DIVIDEND_PTR might poपूर्णांक to the same limb.
 */

mpi_limb_t
mpihelp_भागmod_1(mpi_ptr_t quot_ptr,
		mpi_ptr_t भागidend_ptr, mpi_माप_प्रकार भागidend_size,
		mpi_limb_t भागisor_limb)
अणु
	mpi_माप_प्रकार i;
	mpi_limb_t n1, n0, r;
	mpi_limb_t dummy __maybe_unused;

	अगर (!भागidend_size)
		वापस 0;

	/* If multiplication is much faster than भागision, and the
	 * भागidend is large, pre-invert the भागisor, and use
	 * only multiplications in the inner loop.
	 *
	 * This test should be पढ़ो:
	 * Does it ever help to use uभाग_qrnnd_preinv?
	 * && Does what we save compensate क्रम the inversion overhead?
	 */
	अगर (UDIV_TIME > (2 * UMUL_TIME + 6)
			&& (UDIV_TIME - (2 * UMUL_TIME + 6)) * भागidend_size > UDIV_TIME) अणु
		पूर्णांक normalization_steps;

		normalization_steps = count_leading_zeros(भागisor_limb);
		अगर (normalization_steps) अणु
			mpi_limb_t भागisor_limb_inverted;

			भागisor_limb <<= normalization_steps;

			/* Compute (2**2N - 2**N * DIVISOR_LIMB) / DIVISOR_LIMB.  The
			 * result is a (N+1)-bit approximation to 1/DIVISOR_LIMB, with the
			 * most signअगरicant bit (with weight 2**N) implicit.
			 */
			/* Special हाल क्रम DIVISOR_LIMB == 100...000.  */
			अगर (!(भागisor_limb << 1))
				भागisor_limb_inverted = ~(mpi_limb_t)0;
			अन्यथा
				uभाग_qrnnd(भागisor_limb_inverted, dummy,
						-भागisor_limb, 0, भागisor_limb);

			n1 = भागidend_ptr[भागidend_size - 1];
			r = n1 >> (BITS_PER_MPI_LIMB - normalization_steps);

			/* Possible optimization:
			 * अगर (r == 0
			 * && भागisor_limb > ((n1 << normalization_steps)
			 *		       | (भागidend_ptr[भागidend_size - 2] >> ...)))
			 * ...one भागision less...
			 */
			क्रम (i = भागidend_size - 2; i >= 0; i--) अणु
				n0 = भागidend_ptr[i];
				UDIV_QRNND_PREINV(quot_ptr[i + 1], r, r,
						((n1 << normalization_steps)
						 | (n0 >> (BITS_PER_MPI_LIMB - normalization_steps))),
						भागisor_limb, भागisor_limb_inverted);
				n1 = n0;
			पूर्ण
			UDIV_QRNND_PREINV(quot_ptr[0], r, r,
					n1 << normalization_steps,
					भागisor_limb, भागisor_limb_inverted);
			वापस r >> normalization_steps;
		पूर्ण अन्यथा अणु
			mpi_limb_t भागisor_limb_inverted;

			/* Compute (2**2N - 2**N * DIVISOR_LIMB) / DIVISOR_LIMB.  The
			 * result is a (N+1)-bit approximation to 1/DIVISOR_LIMB, with the
			 * most signअगरicant bit (with weight 2**N) implicit.
			 */
			/* Special हाल क्रम DIVISOR_LIMB == 100...000.  */
			अगर (!(भागisor_limb << 1))
				भागisor_limb_inverted = ~(mpi_limb_t) 0;
			अन्यथा
				uभाग_qrnnd(भागisor_limb_inverted, dummy,
						-भागisor_limb, 0, भागisor_limb);

			i = भागidend_size - 1;
			r = भागidend_ptr[i];

			अगर (r >= भागisor_limb)
				r = 0;
			अन्यथा
				quot_ptr[i--] = 0;

			क्रम ( ; i >= 0; i--) अणु
				n0 = भागidend_ptr[i];
				UDIV_QRNND_PREINV(quot_ptr[i], r, r,
						n0, भागisor_limb, भागisor_limb_inverted);
			पूर्ण
			वापस r;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (UDIV_NEEDS_NORMALIZATION) अणु
			पूर्णांक normalization_steps;

			normalization_steps = count_leading_zeros(भागisor_limb);
			अगर (normalization_steps) अणु
				भागisor_limb <<= normalization_steps;

				n1 = भागidend_ptr[भागidend_size - 1];
				r = n1 >> (BITS_PER_MPI_LIMB - normalization_steps);

				/* Possible optimization:
				 * अगर (r == 0
				 * && भागisor_limb > ((n1 << normalization_steps)
				 *		   | (भागidend_ptr[भागidend_size - 2] >> ...)))
				 * ...one भागision less...
				 */
				क्रम (i = भागidend_size - 2; i >= 0; i--) अणु
					n0 = भागidend_ptr[i];
					uभाग_qrnnd(quot_ptr[i + 1], r, r,
						((n1 << normalization_steps)
						 | (n0 >> (BITS_PER_MPI_LIMB - normalization_steps))),
						भागisor_limb);
					n1 = n0;
				पूर्ण
				uभाग_qrnnd(quot_ptr[0], r, r,
						n1 << normalization_steps,
						भागisor_limb);
				वापस r >> normalization_steps;
			पूर्ण
		पूर्ण
		/* No normalization needed, either because uभाग_qrnnd करोesn't require
		 * it, or because DIVISOR_LIMB is alपढ़ोy normalized.
		 */
		i = भागidend_size - 1;
		r = भागidend_ptr[i];

		अगर (r >= भागisor_limb)
			r = 0;
		अन्यथा
			quot_ptr[i--] = 0;

		क्रम (; i >= 0; i--) अणु
			n0 = भागidend_ptr[i];
			uभाग_qrnnd(quot_ptr[i], r, r, n0, भागisor_limb);
		पूर्ण
		वापस r;
	पूर्ण
पूर्ण
