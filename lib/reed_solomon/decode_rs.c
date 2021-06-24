<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Generic Reed Solomon encoder / decoder library
 *
 * Copyright 2002, Phil Karn, KA9Q
 * May be used under the terms of the GNU General Public License (GPL)
 *
 * Adaption to the kernel by Thomas Gleixner (tglx@linutronix.de)
 *
 * Generic data width independent code which is included by the wrappers.
 */
अणु
	काष्ठा rs_codec *rs = rsc->codec;
	पूर्णांक deg_lambda, el, deg_omega;
	पूर्णांक i, j, r, k, pad;
	पूर्णांक nn = rs->nn;
	पूर्णांक nroots = rs->nroots;
	पूर्णांक fcr = rs->fcr;
	पूर्णांक prim = rs->prim;
	पूर्णांक iprim = rs->iprim;
	uपूर्णांक16_t *alpha_to = rs->alpha_to;
	uपूर्णांक16_t *index_of = rs->index_of;
	uपूर्णांक16_t u, q, पंचांगp, num1, num2, den, discr_r, syn_error;
	पूर्णांक count = 0;
	पूर्णांक num_corrected;
	uपूर्णांक16_t msk = (uपूर्णांक16_t) rs->nn;

	/*
	 * The decoder buffers are in the rs control काष्ठा. They are
	 * arrays sized [nroots + 1]
	 */
	uपूर्णांक16_t *lambda = rsc->buffers + RS_DECODE_LAMBDA * (nroots + 1);
	uपूर्णांक16_t *syn = rsc->buffers + RS_DECODE_SYN * (nroots + 1);
	uपूर्णांक16_t *b = rsc->buffers + RS_DECODE_B * (nroots + 1);
	uपूर्णांक16_t *t = rsc->buffers + RS_DECODE_T * (nroots + 1);
	uपूर्णांक16_t *omega = rsc->buffers + RS_DECODE_OMEGA * (nroots + 1);
	uपूर्णांक16_t *root = rsc->buffers + RS_DECODE_ROOT * (nroots + 1);
	uपूर्णांक16_t *reg = rsc->buffers + RS_DECODE_REG * (nroots + 1);
	uपूर्णांक16_t *loc = rsc->buffers + RS_DECODE_LOC * (nroots + 1);

	/* Check length parameter क्रम validity */
	pad = nn - nroots - len;
	BUG_ON(pad < 0 || pad >= nn - nroots);

	/* Does the caller provide the syndrome ? */
	अगर (s != शून्य) अणु
		क्रम (i = 0; i < nroots; i++) अणु
			/* The syndrome is in index क्रमm,
			 * so nn represents zero
			 */
			अगर (s[i] != nn)
				जाओ decode;
		पूर्ण

		/* syndrome is zero, no errors to correct  */
		वापस 0;
	पूर्ण

	/* क्रमm the syndromes; i.e., evaluate data(x) at roots of
	 * g(x) */
	क्रम (i = 0; i < nroots; i++)
		syn[i] = (((uपूर्णांक16_t) data[0]) ^ invmsk) & msk;

	क्रम (j = 1; j < len; j++) अणु
		क्रम (i = 0; i < nroots; i++) अणु
			अगर (syn[i] == 0) अणु
				syn[i] = (((uपूर्णांक16_t) data[j]) ^
					  invmsk) & msk;
			पूर्ण अन्यथा अणु
				syn[i] = ((((uपूर्णांक16_t) data[j]) ^
					   invmsk) & msk) ^
					alpha_to[rs_modnn(rs, index_of[syn[i]] +
						       (fcr + i) * prim)];
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (j = 0; j < nroots; j++) अणु
		क्रम (i = 0; i < nroots; i++) अणु
			अगर (syn[i] == 0) अणु
				syn[i] = ((uपूर्णांक16_t) par[j]) & msk;
			पूर्ण अन्यथा अणु
				syn[i] = (((uपूर्णांक16_t) par[j]) & msk) ^
					alpha_to[rs_modnn(rs, index_of[syn[i]] +
						       (fcr+i)*prim)];
			पूर्ण
		पूर्ण
	पूर्ण
	s = syn;

	/* Convert syndromes to index क्रमm, checking क्रम nonzero condition */
	syn_error = 0;
	क्रम (i = 0; i < nroots; i++) अणु
		syn_error |= s[i];
		s[i] = index_of[s[i]];
	पूर्ण

	अगर (!syn_error) अणु
		/* अगर syndrome is zero, data[] is a codeword and there are no
		 * errors to correct. So वापस data[] unmodअगरied
		 */
		वापस 0;
	पूर्ण

 decode:
	स_रखो(&lambda[1], 0, nroots * माप(lambda[0]));
	lambda[0] = 1;

	अगर (no_eras > 0) अणु
		/* Init lambda to be the erasure locator polynomial */
		lambda[1] = alpha_to[rs_modnn(rs,
					prim * (nn - 1 - (eras_pos[0] + pad)))];
		क्रम (i = 1; i < no_eras; i++) अणु
			u = rs_modnn(rs, prim * (nn - 1 - (eras_pos[i] + pad)));
			क्रम (j = i + 1; j > 0; j--) अणु
				पंचांगp = index_of[lambda[j - 1]];
				अगर (पंचांगp != nn) अणु
					lambda[j] ^=
						alpha_to[rs_modnn(rs, u + पंचांगp)];
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < nroots + 1; i++)
		b[i] = index_of[lambda[i]];

	/*
	 * Begin Berlekamp-Massey algorithm to determine error+erasure
	 * locator polynomial
	 */
	r = no_eras;
	el = no_eras;
	जबतक (++r <= nroots) अणु	/* r is the step number */
		/* Compute discrepancy at the r-th step in poly-क्रमm */
		discr_r = 0;
		क्रम (i = 0; i < r; i++) अणु
			अगर ((lambda[i] != 0) && (s[r - i - 1] != nn)) अणु
				discr_r ^=
					alpha_to[rs_modnn(rs,
							  index_of[lambda[i]] +
							  s[r - i - 1])];
			पूर्ण
		पूर्ण
		discr_r = index_of[discr_r];	/* Index क्रमm */
		अगर (discr_r == nn) अणु
			/* 2 lines below: B(x) <-- x*B(x) */
			स_हटाओ (&b[1], b, nroots * माप (b[0]));
			b[0] = nn;
		पूर्ण अन्यथा अणु
			/* 7 lines below: T(x) <-- lambda(x)-discr_r*x*b(x) */
			t[0] = lambda[0];
			क्रम (i = 0; i < nroots; i++) अणु
				अगर (b[i] != nn) अणु
					t[i + 1] = lambda[i + 1] ^
						alpha_to[rs_modnn(rs, discr_r +
								  b[i])];
				पूर्ण अन्यथा
					t[i + 1] = lambda[i + 1];
			पूर्ण
			अगर (2 * el <= r + no_eras - 1) अणु
				el = r + no_eras - el;
				/*
				 * 2 lines below: B(x) <-- inv(discr_r) *
				 * lambda(x)
				 */
				क्रम (i = 0; i <= nroots; i++) अणु
					b[i] = (lambda[i] == 0) ? nn :
						rs_modnn(rs, index_of[lambda[i]]
							 - discr_r + nn);
				पूर्ण
			पूर्ण अन्यथा अणु
				/* 2 lines below: B(x) <-- x*B(x) */
				स_हटाओ(&b[1], b, nroots * माप(b[0]));
				b[0] = nn;
			पूर्ण
			स_नकल(lambda, t, (nroots + 1) * माप(t[0]));
		पूर्ण
	पूर्ण

	/* Convert lambda to index क्रमm and compute deg(lambda(x)) */
	deg_lambda = 0;
	क्रम (i = 0; i < nroots + 1; i++) अणु
		lambda[i] = index_of[lambda[i]];
		अगर (lambda[i] != nn)
			deg_lambda = i;
	पूर्ण

	अगर (deg_lambda == 0) अणु
		/*
		 * deg(lambda) is zero even though the syndrome is non-zero
		 * => uncorrectable error detected
		 */
		वापस -EBADMSG;
	पूर्ण

	/* Find roots of error+erasure locator polynomial by Chien search */
	स_नकल(&reg[1], &lambda[1], nroots * माप(reg[0]));
	count = 0;		/* Number of roots of lambda(x) */
	क्रम (i = 1, k = iprim - 1; i <= nn; i++, k = rs_modnn(rs, k + iprim)) अणु
		q = 1;		/* lambda[0] is always 0 */
		क्रम (j = deg_lambda; j > 0; j--) अणु
			अगर (reg[j] != nn) अणु
				reg[j] = rs_modnn(rs, reg[j] + j);
				q ^= alpha_to[reg[j]];
			पूर्ण
		पूर्ण
		अगर (q != 0)
			जारी;	/* Not a root */

		अगर (k < pad) अणु
			/* Impossible error location. Uncorrectable error. */
			वापस -EBADMSG;
		पूर्ण

		/* store root (index-क्रमm) and error location number */
		root[count] = i;
		loc[count] = k;
		/* If we've alपढ़ोy found max possible roots,
		 * पात the search to save समय
		 */
		अगर (++count == deg_lambda)
			अवरोध;
	पूर्ण
	अगर (deg_lambda != count) अणु
		/*
		 * deg(lambda) unequal to number of roots => uncorrectable
		 * error detected
		 */
		वापस -EBADMSG;
	पूर्ण
	/*
	 * Compute err+eras evaluator poly omega(x) = s(x)*lambda(x) (modulo
	 * x**nroots). in index क्रमm. Also find deg(omega).
	 */
	deg_omega = deg_lambda - 1;
	क्रम (i = 0; i <= deg_omega; i++) अणु
		पंचांगp = 0;
		क्रम (j = i; j >= 0; j--) अणु
			अगर ((s[i - j] != nn) && (lambda[j] != nn))
				पंचांगp ^=
				    alpha_to[rs_modnn(rs, s[i - j] + lambda[j])];
		पूर्ण
		omega[i] = index_of[पंचांगp];
	पूर्ण

	/*
	 * Compute error values in poly-क्रमm. num1 = omega(inv(X(l))), num2 =
	 * inv(X(l))**(fcr-1) and den = lambda_pr(inv(X(l))) all in poly-क्रमm
	 * Note: we reuse the buffer क्रम b to store the correction pattern
	 */
	num_corrected = 0;
	क्रम (j = count - 1; j >= 0; j--) अणु
		num1 = 0;
		क्रम (i = deg_omega; i >= 0; i--) अणु
			अगर (omega[i] != nn)
				num1 ^= alpha_to[rs_modnn(rs, omega[i] +
							i * root[j])];
		पूर्ण

		अगर (num1 == 0) अणु
			/* Nothing to correct at this position */
			b[j] = 0;
			जारी;
		पूर्ण

		num2 = alpha_to[rs_modnn(rs, root[j] * (fcr - 1) + nn)];
		den = 0;

		/* lambda[i+1] क्रम i even is the क्रमmal derivative
		 * lambda_pr of lambda[i] */
		क्रम (i = min(deg_lambda, nroots - 1) & ~1; i >= 0; i -= 2) अणु
			अगर (lambda[i + 1] != nn) अणु
				den ^= alpha_to[rs_modnn(rs, lambda[i + 1] +
						       i * root[j])];
			पूर्ण
		पूर्ण

		b[j] = alpha_to[rs_modnn(rs, index_of[num1] +
					       index_of[num2] +
					       nn - index_of[den])];
		num_corrected++;
	पूर्ण

	/*
	 * We compute the syndrome of the 'error' and check that it matches
	 * the syndrome of the received word
	 */
	क्रम (i = 0; i < nroots; i++) अणु
		पंचांगp = 0;
		क्रम (j = 0; j < count; j++) अणु
			अगर (b[j] == 0)
				जारी;

			k = (fcr + i) * prim * (nn-loc[j]-1);
			पंचांगp ^= alpha_to[rs_modnn(rs, index_of[b[j]] + k)];
		पूर्ण

		अगर (पंचांगp != alpha_to[s[i]])
			वापस -EBADMSG;
	पूर्ण

	/*
	 * Store the error correction pattern, अगर a
	 * correction buffer is available
	 */
	अगर (corr && eras_pos) अणु
		j = 0;
		क्रम (i = 0; i < count; i++) अणु
			अगर (b[i]) अणु
				corr[j] = b[i];
				eras_pos[j++] = loc[i] - pad;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (data && par) अणु
		/* Apply error to data and parity */
		क्रम (i = 0; i < count; i++) अणु
			अगर (loc[i] < (nn - nroots))
				data[loc[i] - pad] ^= b[i];
			अन्यथा
				par[loc[i] - pad - len] ^= b[i];
		पूर्ण
	पूर्ण

	वापस  num_corrected;
पूर्ण
