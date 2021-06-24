<शैली गुरु>
/* mpiutil.ac  -  Utility functions क्रम MPI
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

/* Constants allocated right away at startup.  */
अटल MPI स्थिरants[MPI_NUMBER_OF_CONSTANTS];

/* Initialize the MPI subप्रणाली.  This is called early and allows to
 * करो some initialization without taking care of thपढ़ोing issues.
 */
अटल पूर्णांक __init mpi_init(व्योम)
अणु
	पूर्णांक idx;
	अचिन्हित दीर्घ value;

	क्रम (idx = 0; idx < MPI_NUMBER_OF_CONSTANTS; idx++) अणु
		चयन (idx) अणु
		हाल MPI_C_ZERO:
			value = 0;
			अवरोध;
		हाल MPI_C_ONE:
			value = 1;
			अवरोध;
		हाल MPI_C_TWO:
			value = 2;
			अवरोध;
		हाल MPI_C_THREE:
			value = 3;
			अवरोध;
		हाल MPI_C_FOUR:
			value = 4;
			अवरोध;
		हाल MPI_C_EIGHT:
			value = 8;
			अवरोध;
		शेष:
			pr_err("MPI: invalid mpi_const selector %d\n", idx);
			वापस -EFAULT;
		पूर्ण
		स्थिरants[idx] = mpi_alloc_set_ui(value);
		स्थिरants[idx]->flags = (16|32);
	पूर्ण

	वापस 0;
पूर्ण
postcore_initcall(mpi_init);

/* Return a स्थिरant MPI descripbed by NO which is one of the
 * MPI_C_xxx macros.  There is no need to copy this वापसed value; it
 * may be used directly.
 */
MPI mpi_स्थिर(क्रमागत gcry_mpi_स्थिरants no)
अणु
	अगर ((पूर्णांक)no < 0 || no > MPI_NUMBER_OF_CONSTANTS)
		pr_err("MPI: invalid mpi_const selector %d\n", no);
	अगर (!स्थिरants[no])
		pr_err("MPI: MPI subsystem not initialized\n");
	वापस स्थिरants[no];
पूर्ण
EXPORT_SYMBOL_GPL(mpi_स्थिर);

/****************
 * Note:  It was a bad idea to use the number of limbs to allocate
 *	  because on a alpha the limbs are large but we normally need
 *	  पूर्णांकegers of n bits - So we should chnage this to bits (or bytes).
 *
 *	  But mpi_alloc is used in a lot of places :-)
 */
MPI mpi_alloc(अचिन्हित nlimbs)
अणु
	MPI a;

	a = kदो_स्मृति(माप *a, GFP_KERNEL);
	अगर (!a)
		वापस a;

	अगर (nlimbs) अणु
		a->d = mpi_alloc_limb_space(nlimbs);
		अगर (!a->d) अणु
			kमुक्त(a);
			वापस शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		a->d = शून्य;
	पूर्ण

	a->alloced = nlimbs;
	a->nlimbs = 0;
	a->sign = 0;
	a->flags = 0;
	a->nbits = 0;
	वापस a;
पूर्ण
EXPORT_SYMBOL_GPL(mpi_alloc);

mpi_ptr_t mpi_alloc_limb_space(अचिन्हित nlimbs)
अणु
	माप_प्रकार len = nlimbs * माप(mpi_limb_t);

	अगर (!len)
		वापस शून्य;

	वापस kदो_स्मृति(len, GFP_KERNEL);
पूर्ण

व्योम mpi_मुक्त_limb_space(mpi_ptr_t a)
अणु
	अगर (!a)
		वापस;

	kमुक्त_sensitive(a);
पूर्ण

व्योम mpi_assign_limb_space(MPI a, mpi_ptr_t ap, अचिन्हित nlimbs)
अणु
	mpi_मुक्त_limb_space(a->d);
	a->d = ap;
	a->alloced = nlimbs;
पूर्ण

/****************
 * Resize the array of A to NLIMBS. the additional space is cleared
 * (set to 0) [करोne by m_पुनः_स्मृति()]
 */
पूर्णांक mpi_resize(MPI a, अचिन्हित nlimbs)
अणु
	व्योम *p;

	अगर (nlimbs <= a->alloced)
		वापस 0;	/* no need to करो it */

	अगर (a->d) अणु
		p = kदो_स्मृति_array(nlimbs, माप(mpi_limb_t), GFP_KERNEL);
		अगर (!p)
			वापस -ENOMEM;
		स_नकल(p, a->d, a->alloced * माप(mpi_limb_t));
		kमुक्त_sensitive(a->d);
		a->d = p;
	पूर्ण अन्यथा अणु
		a->d = kसुस्मृति(nlimbs, माप(mpi_limb_t), GFP_KERNEL);
		अगर (!a->d)
			वापस -ENOMEM;
	पूर्ण
	a->alloced = nlimbs;
	वापस 0;
पूर्ण

व्योम mpi_clear(MPI a)
अणु
	अगर (!a)
		वापस;
	a->nlimbs = 0;
	a->flags = 0;
पूर्ण
EXPORT_SYMBOL_GPL(mpi_clear);

व्योम mpi_मुक्त(MPI a)
अणु
	अगर (!a)
		वापस;

	अगर (a->flags & 4)
		kमुक्त_sensitive(a->d);
	अन्यथा
		mpi_मुक्त_limb_space(a->d);

	अगर (a->flags & ~7)
		pr_info("invalid flag value in mpi\n");
	kमुक्त(a);
पूर्ण
EXPORT_SYMBOL_GPL(mpi_मुक्त);

/****************
 * Note: This copy function should not पूर्णांकerpret the MPI
 *	 but copy it transparently.
 */
MPI mpi_copy(MPI a)
अणु
	पूर्णांक i;
	MPI b;

	अगर (a) अणु
		b = mpi_alloc(a->nlimbs);
		b->nlimbs = a->nlimbs;
		b->sign = a->sign;
		b->flags = a->flags;
		b->flags &= ~(16|32); /* Reset the immutable and स्थिरant flags. */
		क्रम (i = 0; i < b->nlimbs; i++)
			b->d[i] = a->d[i];
	पूर्ण अन्यथा
		b = शून्य;
	वापस b;
पूर्ण

/****************
 * This function allocates an MPI which is optimized to hold
 * a value as large as the one given in the argument and allocates it
 * with the same flags as A.
 */
MPI mpi_alloc_like(MPI a)
अणु
	MPI b;

	अगर (a) अणु
		b = mpi_alloc(a->nlimbs);
		b->nlimbs = 0;
		b->sign = 0;
		b->flags = a->flags;
	पूर्ण अन्यथा
		b = शून्य;

	वापस b;
पूर्ण


/* Set U पूर्णांकo W and release U.  If W is शून्य only U will be released. */
व्योम mpi_snatch(MPI w, MPI u)
अणु
	अगर (w) अणु
		mpi_assign_limb_space(w, u->d, u->alloced);
		w->nlimbs = u->nlimbs;
		w->sign   = u->sign;
		w->flags  = u->flags;
		u->alloced = 0;
		u->nlimbs = 0;
		u->d = शून्य;
	पूर्ण
	mpi_मुक्त(u);
पूर्ण


MPI mpi_set(MPI w, MPI u)
अणु
	mpi_ptr_t wp, up;
	mpi_माप_प्रकार usize = u->nlimbs;
	पूर्णांक usign = u->sign;

	अगर (!w)
		w = mpi_alloc(mpi_get_nlimbs(u));
	RESIZE_IF_NEEDED(w, usize);
	wp = w->d;
	up = u->d;
	MPN_COPY(wp, up, usize);
	w->nlimbs = usize;
	w->flags = u->flags;
	w->flags &= ~(16|32); /* Reset the immutable and स्थिरant flags.  */
	w->sign = usign;
	वापस w;
पूर्ण
EXPORT_SYMBOL_GPL(mpi_set);

MPI mpi_set_ui(MPI w, अचिन्हित दीर्घ u)
अणु
	अगर (!w)
		w = mpi_alloc(1);
	/* FIXME: If U is 0 we have no need to resize and thus possible
	 * allocating the the limbs.
	 */
	RESIZE_IF_NEEDED(w, 1);
	w->d[0] = u;
	w->nlimbs = u ? 1 : 0;
	w->sign = 0;
	w->flags = 0;
	वापस w;
पूर्ण
EXPORT_SYMBOL_GPL(mpi_set_ui);

MPI mpi_alloc_set_ui(अचिन्हित दीर्घ u)
अणु
	MPI w = mpi_alloc(1);
	w->d[0] = u;
	w->nlimbs = u ? 1 : 0;
	w->sign = 0;
	वापस w;
पूर्ण

/****************
 * Swap the value of A and B, when SWAP is 1.
 * Leave the value when SWAP is 0.
 * This implementation should be स्थिरant-समय regardless of SWAP.
 */
व्योम mpi_swap_cond(MPI a, MPI b, अचिन्हित दीर्घ swap)
अणु
	mpi_माप_प्रकार i;
	mpi_माप_प्रकार nlimbs;
	mpi_limb_t mask = ((mpi_limb_t)0) - swap;
	mpi_limb_t x;

	अगर (a->alloced > b->alloced)
		nlimbs = b->alloced;
	अन्यथा
		nlimbs = a->alloced;
	अगर (a->nlimbs > nlimbs || b->nlimbs > nlimbs)
		वापस;

	क्रम (i = 0; i < nlimbs; i++) अणु
		x = mask & (a->d[i] ^ b->d[i]);
		a->d[i] = a->d[i] ^ x;
		b->d[i] = b->d[i] ^ x;
	पूर्ण

	x = mask & (a->nlimbs ^ b->nlimbs);
	a->nlimbs = a->nlimbs ^ x;
	b->nlimbs = b->nlimbs ^ x;

	x = mask & (a->sign ^ b->sign);
	a->sign = a->sign ^ x;
	b->sign = b->sign ^ x;
पूर्ण

MODULE_DESCRIPTION("Multiprecision maths library");
MODULE_LICENSE("GPL");
