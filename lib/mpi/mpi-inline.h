<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* mpi-अंतरभूत.h  -  Internal to the Multi Precision Integers
 *	Copyright (C) 1994, 1996, 1998, 1999 Free Software Foundation, Inc.
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

#अगर_अघोषित G10_MPI_INLINE_H
#घोषणा G10_MPI_INLINE_H

#अगर_अघोषित G10_MPI_INLINE_DECL
#घोषणा G10_MPI_INLINE_DECL  अटल अंतरभूत
#पूर्ण_अगर

G10_MPI_INLINE_DECL mpi_limb_t
mpihelp_add_1(mpi_ptr_t res_ptr, mpi_ptr_t s1_ptr,
	      mpi_माप_प्रकार s1_size, mpi_limb_t s2_limb)
अणु
	mpi_limb_t x;

	x = *s1_ptr++;
	s2_limb += x;
	*res_ptr++ = s2_limb;
	अगर (s2_limb < x) अणु	/* sum is less than the left opeअक्रम: handle carry */
		जबतक (--s1_size) अणु
			x = *s1_ptr++ + 1;	/* add carry */
			*res_ptr++ = x;	/* and store */
			अगर (x)	/* not 0 (no overflow): we can stop */
				जाओ leave;
		पूर्ण
		वापस 1;	/* वापस carry (size of s1 to small) */
	पूर्ण

leave:
	अगर (res_ptr != s1_ptr) अणु	/* not the same variable */
		mpi_माप_प्रकार i;	/* copy the rest */
		क्रम (i = 0; i < s1_size - 1; i++)
			res_ptr[i] = s1_ptr[i];
	पूर्ण
	वापस 0;		/* no carry */
पूर्ण

G10_MPI_INLINE_DECL mpi_limb_t
mpihelp_add(mpi_ptr_t res_ptr, mpi_ptr_t s1_ptr, mpi_माप_प्रकार s1_size,
	    mpi_ptr_t s2_ptr, mpi_माप_प्रकार s2_size)
अणु
	mpi_limb_t cy = 0;

	अगर (s2_size)
		cy = mpihelp_add_n(res_ptr, s1_ptr, s2_ptr, s2_size);

	अगर (s1_size - s2_size)
		cy = mpihelp_add_1(res_ptr + s2_size, s1_ptr + s2_size,
				   s1_size - s2_size, cy);
	वापस cy;
पूर्ण

G10_MPI_INLINE_DECL mpi_limb_t
mpihelp_sub_1(mpi_ptr_t res_ptr, mpi_ptr_t s1_ptr,
	      mpi_माप_प्रकार s1_size, mpi_limb_t s2_limb)
अणु
	mpi_limb_t x;

	x = *s1_ptr++;
	s2_limb = x - s2_limb;
	*res_ptr++ = s2_limb;
	अगर (s2_limb > x) अणु
		जबतक (--s1_size) अणु
			x = *s1_ptr++;
			*res_ptr++ = x - 1;
			अगर (x)
				जाओ leave;
		पूर्ण
		वापस 1;
	पूर्ण

leave:
	अगर (res_ptr != s1_ptr) अणु
		mpi_माप_प्रकार i;
		क्रम (i = 0; i < s1_size - 1; i++)
			res_ptr[i] = s1_ptr[i];
	पूर्ण
	वापस 0;
पूर्ण

G10_MPI_INLINE_DECL mpi_limb_t
mpihelp_sub(mpi_ptr_t res_ptr, mpi_ptr_t s1_ptr, mpi_माप_प्रकार s1_size,
	    mpi_ptr_t s2_ptr, mpi_माप_प्रकार s2_size)
अणु
	mpi_limb_t cy = 0;

	अगर (s2_size)
		cy = mpihelp_sub_n(res_ptr, s1_ptr, s2_ptr, s2_size);

	अगर (s1_size - s2_size)
		cy = mpihelp_sub_1(res_ptr + s2_size, s1_ptr + s2_size,
				   s1_size - s2_size, cy);
	वापस cy;
पूर्ण

#पूर्ण_अगर /*G10_MPI_INLINE_H */
