<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* mpih-rshअगरt.c  -  MPI helper functions
 * Copyright (C) 1994, 1996, 1998, 1999,
 *               2000, 2001 Free Software Foundation, Inc.
 *
 * This file is part of GNUPG
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

/* Shअगरt U (poपूर्णांकed to by UP and USIZE limbs दीर्घ) CNT bits to the right
 * and store the USIZE least signअगरicant limbs of the result at WP.
 * The bits shअगरted out to the right are वापसed.
 *
 * Argument स्थिरraपूर्णांकs:
 * 1. 0 < CNT < BITS_PER_MP_LIMB
 * 2. If the result is to be written over the input, WP must be <= UP.
 */

mpi_limb_t
mpihelp_rshअगरt(mpi_ptr_t wp, mpi_ptr_t up, mpi_माप_प्रकार usize, अचिन्हित cnt)
अणु
	mpi_limb_t high_limb, low_limb;
	अचिन्हित sh_1, sh_2;
	mpi_माप_प्रकार i;
	mpi_limb_t retval;

	sh_1 = cnt;
	wp -= 1;
	sh_2 = BITS_PER_MPI_LIMB - sh_1;
	high_limb = up[0];
	retval = high_limb << sh_2;
	low_limb = high_limb;
	क्रम (i = 1; i < usize; i++) अणु
		high_limb = up[i];
		wp[i] = (low_limb >> sh_1) | (high_limb << sh_2);
		low_limb = high_limb;
	पूर्ण
	wp[i] = low_limb >> sh_1;

	वापस retval;
पूर्ण
