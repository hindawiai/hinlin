<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* mpihelp-sub.c  -  MPI helper functions
 *	Copyright (C) 1994, 1996 Free Software Foundation, Inc.
 *	Copyright (C) 1998, 1999, 2000, 2001 Free Software Foundation, Inc.
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

/****************
 * Compare OP1_PTR/OP1_SIZE with OP2_PTR/OP2_SIZE.
 * There are no restrictions on the relative sizes of
 * the two arguments.
 * Return 1 अगर OP1 > OP2, 0 अगर they are equal, and -1 अगर OP1 < OP2.
 */
पूर्णांक mpihelp_cmp(mpi_ptr_t op1_ptr, mpi_ptr_t op2_ptr, mpi_माप_प्रकार size)
अणु
	mpi_माप_प्रकार i;
	mpi_limb_t op1_word, op2_word;

	क्रम (i = size - 1; i >= 0; i--) अणु
		op1_word = op1_ptr[i];
		op2_word = op2_ptr[i];
		अगर (op1_word != op2_word)
			जाओ dअगरf;
	पूर्ण
	वापस 0;

dअगरf:
	/* This can *not* be simplअगरied to
	 *   op2_word - op2_word
	 * since that expression might give चिन्हित overflow.  */
	वापस (op1_word > op2_word) ? 1 : -1;
पूर्ण
