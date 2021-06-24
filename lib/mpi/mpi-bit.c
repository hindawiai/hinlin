<शैली गुरु>
/* mpi-bit.c  -  MPI bit level functions
 * Copyright (C) 1998, 1999 Free Software Foundation, Inc.
 *
 * This file is part of GnuPG.
 *
 * GnuPG is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * GnuPG is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */

#समावेश "mpi-internal.h"
#समावेश "longlong.h"

#घोषणा A_LIMB_1 ((mpi_limb_t) 1)

/****************
 * Someबार we have MSL (most signअगरicant limbs) which are 0;
 * this is क्रम some reasons not good, so this function हटाओs them.
 */
व्योम mpi_normalize(MPI a)
अणु
	क्रम (; a->nlimbs && !a->d[a->nlimbs - 1]; a->nlimbs--)
		;
पूर्ण
EXPORT_SYMBOL_GPL(mpi_normalize);

/****************
 * Return the number of bits in A.
 */
अचिन्हित mpi_get_nbits(MPI a)
अणु
	अचिन्हित n;

	mpi_normalize(a);

	अगर (a->nlimbs) अणु
		mpi_limb_t alimb = a->d[a->nlimbs - 1];
		अगर (alimb)
			n = count_leading_zeros(alimb);
		अन्यथा
			n = BITS_PER_MPI_LIMB;
		n = BITS_PER_MPI_LIMB - n + (a->nlimbs - 1) * BITS_PER_MPI_LIMB;
	पूर्ण अन्यथा
		n = 0;
	वापस n;
पूर्ण
EXPORT_SYMBOL_GPL(mpi_get_nbits);

/****************
 * Test whether bit N is set.
 */
पूर्णांक mpi_test_bit(MPI a, अचिन्हित पूर्णांक n)
अणु
	अचिन्हित पूर्णांक limbno, bitno;
	mpi_limb_t limb;

	limbno = n / BITS_PER_MPI_LIMB;
	bitno  = n % BITS_PER_MPI_LIMB;

	अगर (limbno >= a->nlimbs)
		वापस 0; /* too far left: this is a 0 */
	limb = a->d[limbno];
	वापस (limb & (A_LIMB_1 << bitno)) ? 1 : 0;
पूर्ण
EXPORT_SYMBOL_GPL(mpi_test_bit);

/****************
 * Set bit N of A.
 */
व्योम mpi_set_bit(MPI a, अचिन्हित पूर्णांक n)
अणु
	अचिन्हित पूर्णांक i, limbno, bitno;

	limbno = n / BITS_PER_MPI_LIMB;
	bitno  = n % BITS_PER_MPI_LIMB;

	अगर (limbno >= a->nlimbs) अणु
		क्रम (i = a->nlimbs; i < a->alloced; i++)
			a->d[i] = 0;
		mpi_resize(a, limbno+1);
		a->nlimbs = limbno+1;
	पूर्ण
	a->d[limbno] |= (A_LIMB_1<<bitno);
पूर्ण

/****************
 * Set bit N of A. and clear all bits above
 */
व्योम mpi_set_highbit(MPI a, अचिन्हित पूर्णांक n)
अणु
	अचिन्हित पूर्णांक i, limbno, bitno;

	limbno = n / BITS_PER_MPI_LIMB;
	bitno  = n % BITS_PER_MPI_LIMB;

	अगर (limbno >= a->nlimbs) अणु
		क्रम (i = a->nlimbs; i < a->alloced; i++)
			a->d[i] = 0;
		mpi_resize(a, limbno+1);
		a->nlimbs = limbno+1;
	पूर्ण
	a->d[limbno] |= (A_LIMB_1<<bitno);
	क्रम (bitno++; bitno < BITS_PER_MPI_LIMB; bitno++)
		a->d[limbno] &= ~(A_LIMB_1 << bitno);
	a->nlimbs = limbno+1;
पूर्ण
EXPORT_SYMBOL_GPL(mpi_set_highbit);

/****************
 * clear bit N of A and all bits above
 */
व्योम mpi_clear_highbit(MPI a, अचिन्हित पूर्णांक n)
अणु
	अचिन्हित पूर्णांक limbno, bitno;

	limbno = n / BITS_PER_MPI_LIMB;
	bitno  = n % BITS_PER_MPI_LIMB;

	अगर (limbno >= a->nlimbs)
		वापस; /* not allocated, thereक्रमe no need to clear bits :-) */

	क्रम ( ; bitno < BITS_PER_MPI_LIMB; bitno++)
		a->d[limbno] &= ~(A_LIMB_1 << bitno);
	a->nlimbs = limbno+1;
पूर्ण

/****************
 * Clear bit N of A.
 */
व्योम mpi_clear_bit(MPI a, अचिन्हित पूर्णांक n)
अणु
	अचिन्हित पूर्णांक limbno, bitno;

	limbno = n / BITS_PER_MPI_LIMB;
	bitno  = n % BITS_PER_MPI_LIMB;

	अगर (limbno >= a->nlimbs)
		वापस; /* Don't need to clear this bit, it's far too left.  */
	a->d[limbno] &= ~(A_LIMB_1 << bitno);
पूर्ण
EXPORT_SYMBOL_GPL(mpi_clear_bit);


/****************
 * Shअगरt A by COUNT limbs to the right
 * This is used only within the MPI library
 */
व्योम mpi_rshअगरt_limbs(MPI a, अचिन्हित पूर्णांक count)
अणु
	mpi_ptr_t ap = a->d;
	mpi_माप_प्रकार n = a->nlimbs;
	अचिन्हित पूर्णांक i;

	अगर (count >= n) अणु
		a->nlimbs = 0;
		वापस;
	पूर्ण

	क्रम (i = 0; i < n - count; i++)
		ap[i] = ap[i+count];
	ap[i] = 0;
	a->nlimbs -= count;
पूर्ण

/*
 * Shअगरt A by N bits to the right.
 */
व्योम mpi_rshअगरt(MPI x, MPI a, अचिन्हित पूर्णांक n)
अणु
	mpi_माप_प्रकार xsize;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक nlimbs = (n/BITS_PER_MPI_LIMB);
	अचिन्हित पूर्णांक nbits = (n%BITS_PER_MPI_LIMB);

	अगर (x == a) अणु
		/* In-place operation.  */
		अगर (nlimbs >= x->nlimbs) अणु
			x->nlimbs = 0;
			वापस;
		पूर्ण

		अगर (nlimbs) अणु
			क्रम (i = 0; i < x->nlimbs - nlimbs; i++)
				x->d[i] = x->d[i+nlimbs];
			x->d[i] = 0;
			x->nlimbs -= nlimbs;
		पूर्ण
		अगर (x->nlimbs && nbits)
			mpihelp_rshअगरt(x->d, x->d, x->nlimbs, nbits);
	पूर्ण अन्यथा अगर (nlimbs) अणु
		/* Copy and shअगरt by more or equal bits than in a limb. */
		xsize = a->nlimbs;
		x->sign = a->sign;
		RESIZE_IF_NEEDED(x, xsize);
		x->nlimbs = xsize;
		क्रम (i = 0; i < a->nlimbs; i++)
			x->d[i] = a->d[i];
		x->nlimbs = i;

		अगर (nlimbs >= x->nlimbs) अणु
			x->nlimbs = 0;
			वापस;
		पूर्ण

		अगर (nlimbs) अणु
			क्रम (i = 0; i < x->nlimbs - nlimbs; i++)
				x->d[i] = x->d[i+nlimbs];
			x->d[i] = 0;
			x->nlimbs -= nlimbs;
		पूर्ण

		अगर (x->nlimbs && nbits)
			mpihelp_rshअगरt(x->d, x->d, x->nlimbs, nbits);
	पूर्ण अन्यथा अणु
		/* Copy and shअगरt by less than bits in a limb.  */
		xsize = a->nlimbs;
		x->sign = a->sign;
		RESIZE_IF_NEEDED(x, xsize);
		x->nlimbs = xsize;

		अगर (xsize) अणु
			अगर (nbits)
				mpihelp_rshअगरt(x->d, a->d, x->nlimbs, nbits);
			अन्यथा अणु
				/* The rshअगरt helper function is not specअगरied क्रम
				 * NBITS==0, thus we करो a plain copy here.
				 */
				क्रम (i = 0; i < x->nlimbs; i++)
					x->d[i] = a->d[i];
			पूर्ण
		पूर्ण
	पूर्ण
	MPN_NORMALIZE(x->d, x->nlimbs);
पूर्ण

/****************
 * Shअगरt A by COUNT limbs to the left
 * This is used only within the MPI library
 */
व्योम mpi_lshअगरt_limbs(MPI a, अचिन्हित पूर्णांक count)
अणु
	mpi_ptr_t ap;
	पूर्णांक n = a->nlimbs;
	पूर्णांक i;

	अगर (!count || !n)
		वापस;

	RESIZE_IF_NEEDED(a, n+count);

	ap = a->d;
	क्रम (i = n-1; i >= 0; i--)
		ap[i+count] = ap[i];
	क्रम (i = 0; i < count; i++)
		ap[i] = 0;
	a->nlimbs += count;
पूर्ण

/*
 * Shअगरt A by N bits to the left.
 */
व्योम mpi_lshअगरt(MPI x, MPI a, अचिन्हित पूर्णांक n)
अणु
	अचिन्हित पूर्णांक nlimbs = (n/BITS_PER_MPI_LIMB);
	अचिन्हित पूर्णांक nbits = (n%BITS_PER_MPI_LIMB);

	अगर (x == a && !n)
		वापस;  /* In-place shअगरt with an amount of zero.  */

	अगर (x != a) अणु
		/* Copy A to X.  */
		अचिन्हित पूर्णांक alimbs = a->nlimbs;
		पूर्णांक asign = a->sign;
		mpi_ptr_t xp, ap;

		RESIZE_IF_NEEDED(x, alimbs+nlimbs+1);
		xp = x->d;
		ap = a->d;
		MPN_COPY(xp, ap, alimbs);
		x->nlimbs = alimbs;
		x->flags = a->flags;
		x->sign = asign;
	पूर्ण

	अगर (nlimbs && !nbits) अणु
		/* Shअगरt a full number of limbs.  */
		mpi_lshअगरt_limbs(x, nlimbs);
	पूर्ण अन्यथा अगर (n) अणु
		/* We use a very dump approach: Shअगरt left by the number of
		 * limbs plus one and than fix it up by an rshअगरt.
		 */
		mpi_lshअगरt_limbs(x, nlimbs+1);
		mpi_rshअगरt(x, x, BITS_PER_MPI_LIMB - nbits);
	पूर्ण

	MPN_NORMALIZE(x->d, x->nlimbs);
पूर्ण
