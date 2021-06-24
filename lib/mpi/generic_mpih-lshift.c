<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* mpihelp-lshअगरt.c  -	MPI helper functions
 * Copyright (C) 1994, 1996, 1998, 2001 Free Software Foundation, Inc.
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

/* Shअगरt U (poपूर्णांकed to by UP and USIZE digits दीर्घ) CNT bits to the left
 * and store the USIZE least signअगरicant digits of the result at WP.
 * Return the bits shअगरted out from the most signअगरicant digit.
 *
 * Argument स्थिरraपूर्णांकs:
 * 1. 0 < CNT < BITS_PER_MP_LIMB
 * 2. If the result is to be written over the input, WP must be >= UP.
 */

mpi_limb_t
mpihelp_lshअगरt(mpi_ptr_t wp, mpi_ptr_t up, mpi_माप_प्रकार usize, अचिन्हित पूर्णांक cnt)
अणु
	mpi_limb_t high_limb, low_limb;
	अचिन्हित sh_1, sh_2;
	mpi_माप_प्रकार i;
	mpi_limb_t retval;

	sh_1 = cnt;
	wp += 1;
	sh_2 = BITS_PER_MPI_LIMB - sh_1;
	i = usize - 1;
	low_limb = up[i];
	retval = low_limb >> sh_2;
	high_limb = low_limb;
	जबतक (--i >= 0) अणु
		low_limb = up[i];
		wp[i] = (high_limb << sh_1) | (low_limb >> sh_2);
		high_limb = low_limb;
	पूर्ण
	wp[i] = high_limb << sh_1;

	वापस retval;
पूर्ण
