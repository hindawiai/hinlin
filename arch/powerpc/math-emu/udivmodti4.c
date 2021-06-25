<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* This has so very few changes over libgcc2's __udivmoddi4 it isn't funny.  */

#समावेश <math-emu/soft-fp.h>

#अघोषित count_leading_zeros
#घोषणा count_leading_zeros  __FP_CLZ

व्योम
_fp_uभागmodti4(_FP_W_TYPE q[2], _FP_W_TYPE r[2],
	       _FP_W_TYPE n1, _FP_W_TYPE n0,
	       _FP_W_TYPE d1, _FP_W_TYPE d0)
अणु
  _FP_W_TYPE q0, q1, r0, r1;
  _FP_I_TYPE b, bm;

  अगर (d1 == 0)
    अणु
#अगर !UDIV_NEEDS_NORMALIZATION
      अगर (d0 > n1)
	अणु
	  /* 0q = nn / 0D */

	  uभाग_qrnnd (q0, n0, n1, n0, d0);
	  q1 = 0;

	  /* Reमुख्यder in n0.  */
	पूर्ण
      अन्यथा
	अणु
	  /* qq = NN / 0d */

	  अगर (d0 == 0)
	    d0 = 1 / d0;	/* Divide पूर्णांकentionally by zero.  */

	  uभाग_qrnnd (q1, n1, 0, n1, d0);
	  uभाग_qrnnd (q0, n0, n1, n0, d0);

	  /* Reमुख्यder in n0.  */
	पूर्ण

      r0 = n0;
      r1 = 0;

#अन्यथा /* UDIV_NEEDS_NORMALIZATION */

      अगर (d0 > n1)
	अणु
	  /* 0q = nn / 0D */

	  count_leading_zeros (bm, d0);

	  अगर (bm != 0)
	    अणु
	      /* Normalize, i.e. make the most signअगरicant bit of the
		 denominator set.  */

	      d0 = d0 << bm;
	      n1 = (n1 << bm) | (n0 >> (_FP_W_TYPE_SIZE - bm));
	      n0 = n0 << bm;
	    पूर्ण

	  uभाग_qrnnd (q0, n0, n1, n0, d0);
	  q1 = 0;

	  /* Reमुख्यder in n0 >> bm.  */
	पूर्ण
      अन्यथा
	अणु
	  /* qq = NN / 0d */

	  अगर (d0 == 0)
	    d0 = 1 / d0;	/* Divide पूर्णांकentionally by zero.  */

	  count_leading_zeros (bm, d0);

	  अगर (bm == 0)
	    अणु
	      /* From (n1 >= d0) /\ (the most signअगरicant bit of d0 is set),
		 conclude (the most signअगरicant bit of n1 is set) /\ (the
		 leading quotient digit q1 = 1).

		 This special हाल is necessary, not an optimization.
		 (Shअगरts counts of SI_TYPE_SIZE are undefined.)  */

	      n1 -= d0;
	      q1 = 1;
	    पूर्ण
	  अन्यथा
	    अणु
	      _FP_W_TYPE n2;

	      /* Normalize.  */

	      b = _FP_W_TYPE_SIZE - bm;

	      d0 = d0 << bm;
	      n2 = n1 >> b;
	      n1 = (n1 << bm) | (n0 >> b);
	      n0 = n0 << bm;

	      uभाग_qrnnd (q1, n1, n2, n1, d0);
	    पूर्ण

	  /* n1 != d0...  */

	  uभाग_qrnnd (q0, n0, n1, n0, d0);

	  /* Reमुख्यder in n0 >> bm.  */
	पूर्ण

      r0 = n0 >> bm;
      r1 = 0;
#पूर्ण_अगर /* UDIV_NEEDS_NORMALIZATION */
    पूर्ण
  अन्यथा
    अणु
      अगर (d1 > n1)
	अणु
	  /* 00 = nn / DD */

	  q0 = 0;
	  q1 = 0;

	  /* Reमुख्यder in n1n0.  */
	  r0 = n0;
	  r1 = n1;
	पूर्ण
      अन्यथा
	अणु
	  /* 0q = NN / dd */

	  count_leading_zeros (bm, d1);
	  अगर (bm == 0)
	    अणु
	      /* From (n1 >= d1) /\ (the most signअगरicant bit of d1 is set),
		 conclude (the most signअगरicant bit of n1 is set) /\ (the
		 quotient digit q0 = 0 or 1).

		 This special हाल is necessary, not an optimization.  */

	      /* The condition on the next line takes advantage of that
		 n1 >= d1 (true due to program flow).  */
	      अगर (n1 > d1 || n0 >= d0)
		अणु
		  q0 = 1;
		  sub_ddmmss (n1, n0, n1, n0, d1, d0);
		पूर्ण
	      अन्यथा
		q0 = 0;

	      q1 = 0;

	      r0 = n0;
	      r1 = n1;
	    पूर्ण
	  अन्यथा
	    अणु
	      _FP_W_TYPE m1, m0, n2;

	      /* Normalize.  */

	      b = _FP_W_TYPE_SIZE - bm;

	      d1 = (d1 << bm) | (d0 >> b);
	      d0 = d0 << bm;
	      n2 = n1 >> b;
	      n1 = (n1 << bm) | (n0 >> b);
	      n0 = n0 << bm;

	      uभाग_qrnnd (q0, n1, n2, n1, d1);
	      umul_ppmm (m1, m0, q0, d0);

	      अगर (m1 > n1 || (m1 == n1 && m0 > n0))
		अणु
		  q0--;
		  sub_ddmmss (m1, m0, m1, m0, d1, d0);
		पूर्ण

	      q1 = 0;

	      /* Reमुख्यder in (n1n0 - m1m0) >> bm.  */
	      sub_ddmmss (n1, n0, n1, n0, m1, m0);
	      r0 = (n1 << b) | (n0 >> bm);
	      r1 = n1 >> bm;
	    पूर्ण
	पूर्ण
    पूर्ण

  q[0] = q0; q[1] = q1;
  r[0] = r0, r[1] = r1;
पूर्ण
