<शैली गुरु>
/* mpi-inv.c  -  MPI functions
 *	Copyright (C) 1998, 2001, 2002, 2003 Free Software Foundation, Inc.
 *
 * This file is part of Libgcrypt.
 *
 * Libgcrypt is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * Libgcrypt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License क्रम more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License aदीर्घ with this program; अगर not, see <http://www.gnu.org/licenses/>.
 */

#समावेश "mpi-internal.h"

/****************
 * Calculate the multiplicative inverse X of A mod N
 * That is: Find the solution x क्रम
 *		1 = (a*x) mod n
 */
पूर्णांक mpi_invm(MPI x, MPI a, MPI n)
अणु
	/* Extended Euclid's algorithm (See TAOCP Vol II, 4.5.2, Alg X)
	 * modअगरied according to Michael Penk's solution क्रम Exercise 35
	 * with further enhancement
	 */
	MPI u, v, u1, u2 = शून्य, u3, v1, v2 = शून्य, v3, t1, t2 = शून्य, t3;
	अचिन्हित पूर्णांक k;
	पूर्णांक sign;
	पूर्णांक odd;

	अगर (!mpi_cmp_ui(a, 0))
		वापस 0; /* Inverse करोes not exists.  */
	अगर (!mpi_cmp_ui(n, 1))
		वापस 0; /* Inverse करोes not exists.  */

	u = mpi_copy(a);
	v = mpi_copy(n);

	क्रम (k = 0; !mpi_test_bit(u, 0) && !mpi_test_bit(v, 0); k++) अणु
		mpi_rshअगरt(u, u, 1);
		mpi_rshअगरt(v, v, 1);
	पूर्ण
	odd = mpi_test_bit(v, 0);

	u1 = mpi_alloc_set_ui(1);
	अगर (!odd)
		u2 = mpi_alloc_set_ui(0);
	u3 = mpi_copy(u);
	v1 = mpi_copy(v);
	अगर (!odd) अणु
		v2 = mpi_alloc(mpi_get_nlimbs(u));
		mpi_sub(v2, u1, u); /* U is used as स्थिर 1 */
	पूर्ण
	v3 = mpi_copy(v);
	अगर (mpi_test_bit(u, 0)) अणु /* u is odd */
		t1 = mpi_alloc_set_ui(0);
		अगर (!odd) अणु
			t2 = mpi_alloc_set_ui(1);
			t2->sign = 1;
		पूर्ण
		t3 = mpi_copy(v);
		t3->sign = !t3->sign;
		जाओ Y4;
	पूर्ण अन्यथा अणु
		t1 = mpi_alloc_set_ui(1);
		अगर (!odd)
			t2 = mpi_alloc_set_ui(0);
		t3 = mpi_copy(u);
	पूर्ण

	करो अणु
		करो अणु
			अगर (!odd) अणु
				अगर (mpi_test_bit(t1, 0) || mpi_test_bit(t2, 0)) अणु
					/* one is odd */
					mpi_add(t1, t1, v);
					mpi_sub(t2, t2, u);
				पूर्ण
				mpi_rshअगरt(t1, t1, 1);
				mpi_rshअगरt(t2, t2, 1);
				mpi_rshअगरt(t3, t3, 1);
			पूर्ण अन्यथा अणु
				अगर (mpi_test_bit(t1, 0))
					mpi_add(t1, t1, v);
				mpi_rshअगरt(t1, t1, 1);
				mpi_rshअगरt(t3, t3, 1);
			पूर्ण
Y4:
			;
		पूर्ण जबतक (!mpi_test_bit(t3, 0)); /* जबतक t3 is even */

		अगर (!t3->sign) अणु
			mpi_set(u1, t1);
			अगर (!odd)
				mpi_set(u2, t2);
			mpi_set(u3, t3);
		पूर्ण अन्यथा अणु
			mpi_sub(v1, v, t1);
			sign = u->sign; u->sign = !u->sign;
			अगर (!odd)
				mpi_sub(v2, u, t2);
			u->sign = sign;
			sign = t3->sign; t3->sign = !t3->sign;
			mpi_set(v3, t3);
			t3->sign = sign;
		पूर्ण
		mpi_sub(t1, u1, v1);
		अगर (!odd)
			mpi_sub(t2, u2, v2);
		mpi_sub(t3, u3, v3);
		अगर (t1->sign) अणु
			mpi_add(t1, t1, v);
			अगर (!odd)
				mpi_sub(t2, t2, u);
		पूर्ण
	पूर्ण जबतक (mpi_cmp_ui(t3, 0)); /* जबतक t3 != 0 */
	/* mpi_lshअगरt( u3, k ); */
	mpi_set(x, u1);

	mpi_मुक्त(u1);
	mpi_मुक्त(v1);
	mpi_मुक्त(t1);
	अगर (!odd) अणु
		mpi_मुक्त(u2);
		mpi_मुक्त(v2);
		mpi_मुक्त(t2);
	पूर्ण
	mpi_मुक्त(u3);
	mpi_मुक्त(v3);
	mpi_मुक्त(t3);

	mpi_मुक्त(u);
	mpi_मुक्त(v);
	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(mpi_invm);
