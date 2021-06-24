<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* mpi-sub-ui.c - Subtract an अचिन्हित पूर्णांकeger from an MPI.
 *
 * Copyright 1991, 1993, 1994, 1996, 1999-2002, 2004, 2012, 2013, 2015
 * Free Software Foundation, Inc.
 *
 * This file was based on the GNU MP Library source file:
 * https://gmplib.org/repo/gmp-6.2/file/510b83519d1c/mpz/aors_ui.h
 *
 * The GNU MP Library is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of either:
 *
 *   * the GNU Lesser General Public License as published by the Free
 *     Software Foundation; either version 3 of the License, or (at your
 *     option) any later version.
 *
 * or
 *
 *   * the GNU General Public License as published by the Free Software
 *     Foundation; either version 2 of the License, or (at your option) any
 *     later version.
 *
 * or both in parallel, as here.
 *
 * The GNU MP Library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * क्रम more details.
 *
 * You should have received copies of the GNU General Public License and the
 * GNU Lesser General Public License aदीर्घ with the GNU MP Library.  If not,
 * see https://www.gnu.org/licenses/.
 */

#समावेश "mpi-internal.h"

पूर्णांक mpi_sub_ui(MPI w, MPI u, अचिन्हित दीर्घ vval)
अणु
	अगर (u->nlimbs == 0) अणु
		अगर (mpi_resize(w, 1) < 0)
			वापस -ENOMEM;
		w->d[0] = vval;
		w->nlimbs = (vval != 0);
		w->sign = (vval != 0);
		वापस 0;
	पूर्ण

	/* If not space क्रम W (and possible carry), increase space. */
	अगर (mpi_resize(w, u->nlimbs + 1))
		वापस -ENOMEM;

	अगर (u->sign) अणु
		mpi_limb_t cy;

		cy = mpihelp_add_1(w->d, u->d, u->nlimbs, (mpi_limb_t) vval);
		w->d[u->nlimbs] = cy;
		w->nlimbs = u->nlimbs + cy;
		w->sign = 1;
	पूर्ण अन्यथा अणु
		/* The signs are dअगरferent.  Need exact comparison to determine
		 * which opeअक्रम to subtract from which.
		 */
		अगर (u->nlimbs == 1 && u->d[0] < vval) अणु
			w->d[0] = vval - u->d[0];
			w->nlimbs = 1;
			w->sign = 1;
		पूर्ण अन्यथा अणु
			mpihelp_sub_1(w->d, u->d, u->nlimbs, (mpi_limb_t) vval);
			/* Size can decrease with at most one limb. */
			w->nlimbs = (u->nlimbs - (w->d[u->nlimbs - 1] == 0));
			w->sign = 0;
		पूर्ण
	पूर्ण

	mpi_normalize(w);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mpi_sub_ui);
