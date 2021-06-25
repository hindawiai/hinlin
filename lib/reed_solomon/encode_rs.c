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
	पूर्णांक i, j, pad;
	पूर्णांक nn = rs->nn;
	पूर्णांक nroots = rs->nroots;
	uपूर्णांक16_t *alpha_to = rs->alpha_to;
	uपूर्णांक16_t *index_of = rs->index_of;
	uपूर्णांक16_t *genpoly = rs->genpoly;
	uपूर्णांक16_t fb;
	uपूर्णांक16_t msk = (uपूर्णांक16_t) rs->nn;

	/* Check length parameter क्रम validity */
	pad = nn - nroots - len;
	अगर (pad < 0 || pad >= nn)
		वापस -दुस्फल;

	क्रम (i = 0; i < len; i++) अणु
		fb = index_of[((((uपूर्णांक16_t) data[i])^invmsk) & msk) ^ par[0]];
		/* feedback term is non-zero */
		अगर (fb != nn) अणु
			क्रम (j = 1; j < nroots; j++) अणु
				par[j] ^= alpha_to[rs_modnn(rs, fb +
							 genpoly[nroots - j])];
			पूर्ण
		पूर्ण
		/* Shअगरt */
		स_हटाओ(&par[0], &par[1], माप(uपूर्णांक16_t) * (nroots - 1));
		अगर (fb != nn) अणु
			par[nroots - 1] = alpha_to[rs_modnn(rs,
							    fb + genpoly[0])];
		पूर्ण अन्यथा अणु
			par[nroots - 1] = 0;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
