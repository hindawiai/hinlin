<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* mpi-पूर्णांकernal.h  -  Internal to the Multi Precision Integers
 *	Copyright (C) 1994, 1996 Free Software Foundation, Inc.
 *	Copyright (C) 1998, 2000 Free Software Foundation, Inc.
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

#अगर_अघोषित G10_MPI_INTERNAL_H
#घोषणा G10_MPI_INTERNAL_H

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/mpi.h>
#समावेश <linux/त्रुटिसं.स>

#घोषणा log_debug prपूर्णांकk
#घोषणा log_bug prपूर्णांकk

#घोषणा निश्चित(x) \
	करो अणु \
		अगर (!x) \
			log_bug("failed assertion\n"); \
	पूर्ण जबतक (0);

/* If KARATSUBA_THRESHOLD is not alपढ़ोy defined, define it to a
 * value which is good on most machines.  */

/* tested 4, 16, 32 and 64, where 16 gave the best perक्रमmance when
 * checking a 768 and a 1024 bit ElGamal signature.
 * (wk 22.12.97) */
#अगर_अघोषित KARATSUBA_THRESHOLD
#घोषणा KARATSUBA_THRESHOLD 16
#पूर्ण_अगर

/* The code can't handle KARATSUBA_THRESHOLD smaller than 2.  */
#अगर KARATSUBA_THRESHOLD < 2
#अघोषित KARATSUBA_THRESHOLD
#घोषणा KARATSUBA_THRESHOLD 2
#पूर्ण_अगर

प्रकार mpi_limb_t *mpi_ptr_t;	/* poपूर्णांकer to a limb */
प्रकार पूर्णांक mpi_माप_प्रकार;		/* (must be a चिन्हित type) */

#घोषणा RESIZE_IF_NEEDED(a, b)			\
	करो अणु					\
		अगर ((a)->alloced < (b))		\
			mpi_resize((a), (b));	\
	पूर्ण जबतक (0)

/* Copy N limbs from S to D.  */
#घोषणा MPN_COPY(d, s, n) \
	करो अणु					\
		mpi_माप_प्रकार _i;			\
		क्रम (_i = 0; _i < (n); _i++)	\
			(d)[_i] = (s)[_i];	\
	पूर्ण जबतक (0)

#घोषणा MPN_COPY_INCR(d, s, n)		\
	करो अणु					\
		mpi_माप_प्रकार _i;			\
		क्रम (_i = 0; _i < (n); _i++)	\
			(d)[_i] = (s)[_i];	\
	पूर्ण जबतक (0)


#घोषणा MPN_COPY_DECR(d, s, n) \
	करो अणु					\
		mpi_माप_प्रकार _i;			\
		क्रम (_i = (n)-1; _i >= 0; _i--) \
			(d)[_i] = (s)[_i];	\
	पूर्ण जबतक (0)

/* Zero N limbs at D */
#घोषणा MPN_ZERO(d, n) \
	करो अणु					\
		पूर्णांक  _i;			\
		क्रम (_i = 0; _i < (n); _i++)	\
			(d)[_i] = 0;		\
	पूर्ण जबतक (0)

#घोषणा MPN_NORMALIZE(d, n)  \
	करो अणु					\
		जबतक ((n) > 0) अणु		\
			अगर ((d)[(n)-1])		\
				अवरोध;		\
			(n)--;			\
		पूर्ण				\
	पूर्ण जबतक (0)

#घोषणा MPN_MUL_N_RECURSE(prodp, up, vp, size, tspace) \
	करो अणु							\
		अगर ((size) < KARATSUBA_THRESHOLD)		\
			mul_n_baseहाल(prodp, up, vp, size);	\
		अन्यथा						\
			mul_n(prodp, up, vp, size, tspace);	\
	पूर्ण जबतक (0);

/* Divide the two-limb number in (NH,,NL) by D, with DI being the largest
 * limb not larger than (2**(2*BITS_PER_MP_LIMB))/D - (2**BITS_PER_MP_LIMB).
 * If this would yield overflow, DI should be the largest possible number
 * (i.e., only ones).  For correct operation, the most signअगरicant bit of D
 * has to be set.  Put the quotient in Q and the reमुख्यder in R.
 */
#घोषणा UDIV_QRNND_PREINV(q, r, nh, nl, d, di)				\
	करो अणु								\
		mpi_limb_t _ql __maybe_unused;				\
		mpi_limb_t _q, _r;					\
		mpi_limb_t _xh, _xl;					\
		umul_ppmm(_q, _ql, (nh), (di));				\
		_q += (nh);	/* DI is 2**BITS_PER_MPI_LIMB too small */ \
		umul_ppmm(_xh, _xl, _q, (d));				\
		sub_ddmmss(_xh, _r, (nh), (nl), _xh, _xl);		\
		अगर (_xh) अणु						\
			sub_ddmmss(_xh, _r, _xh, _r, 0, (d));		\
			_q++;						\
			अगर (_xh) अणु					\
				sub_ddmmss(_xh, _r, _xh, _r, 0, (d));	\
				_q++;					\
			पूर्ण						\
		पूर्ण							\
		अगर (_r >= (d)) अणु					\
			_r -= (d);					\
			_q++;						\
		पूर्ण							\
		(r) = _r;						\
		(q) = _q;						\
	पूर्ण जबतक (0)


/*-- mpiutil.c --*/
mpi_ptr_t mpi_alloc_limb_space(अचिन्हित nlimbs);
व्योम mpi_मुक्त_limb_space(mpi_ptr_t a);
व्योम mpi_assign_limb_space(MPI a, mpi_ptr_t ap, अचिन्हित nlimbs);

अटल अंतरभूत mpi_limb_t mpihelp_add_1(mpi_ptr_t res_ptr, mpi_ptr_t s1_ptr,
			 mpi_माप_प्रकार s1_size, mpi_limb_t s2_limb);
mpi_limb_t mpihelp_add_n(mpi_ptr_t res_ptr, mpi_ptr_t s1_ptr,
			 mpi_ptr_t s2_ptr, mpi_माप_प्रकार size);
अटल अंतरभूत mpi_limb_t mpihelp_add(mpi_ptr_t res_ptr, mpi_ptr_t s1_ptr, mpi_माप_प्रकार s1_size,
		       mpi_ptr_t s2_ptr, mpi_माप_प्रकार s2_size);

अटल अंतरभूत mpi_limb_t mpihelp_sub_1(mpi_ptr_t res_ptr, mpi_ptr_t s1_ptr,
			 mpi_माप_प्रकार s1_size, mpi_limb_t s2_limb);
mpi_limb_t mpihelp_sub_n(mpi_ptr_t res_ptr, mpi_ptr_t s1_ptr,
			 mpi_ptr_t s2_ptr, mpi_माप_प्रकार size);
अटल अंतरभूत mpi_limb_t mpihelp_sub(mpi_ptr_t res_ptr, mpi_ptr_t s1_ptr, mpi_माप_प्रकार s1_size,
		       mpi_ptr_t s2_ptr, mpi_माप_प्रकार s2_size);

/*-- mpih-cmp.c --*/
पूर्णांक mpihelp_cmp(mpi_ptr_t op1_ptr, mpi_ptr_t op2_ptr, mpi_माप_प्रकार size);

/*-- mpih-mul.c --*/

काष्ठा karatsuba_ctx अणु
	काष्ठा karatsuba_ctx *next;
	mpi_ptr_t tspace;
	mpi_माप_प्रकार tspace_size;
	mpi_ptr_t tp;
	mpi_माप_प्रकार tp_size;
पूर्ण;

व्योम mpihelp_release_karatsuba_ctx(काष्ठा karatsuba_ctx *ctx);

mpi_limb_t mpihelp_addmul_1(mpi_ptr_t res_ptr, mpi_ptr_t s1_ptr,
			    mpi_माप_प्रकार s1_size, mpi_limb_t s2_limb);
mpi_limb_t mpihelp_submul_1(mpi_ptr_t res_ptr, mpi_ptr_t s1_ptr,
			    mpi_माप_प्रकार s1_size, mpi_limb_t s2_limb);
पूर्णांक mpihelp_mul(mpi_ptr_t prodp, mpi_ptr_t up, mpi_माप_प्रकार usize,
		mpi_ptr_t vp, mpi_माप_प्रकार vsize, mpi_limb_t *_result);
व्योम mpih_sqr_n_baseहाल(mpi_ptr_t prodp, mpi_ptr_t up, mpi_माप_प्रकार size);
व्योम mpih_sqr_n(mpi_ptr_t prodp, mpi_ptr_t up, mpi_माप_प्रकार size,
		mpi_ptr_t tspace);
व्योम mpihelp_mul_n(mpi_ptr_t prodp,
		mpi_ptr_t up, mpi_ptr_t vp, mpi_माप_प्रकार size);

पूर्णांक mpihelp_mul_karatsuba_हाल(mpi_ptr_t prodp,
			       mpi_ptr_t up, mpi_माप_प्रकार usize,
			       mpi_ptr_t vp, mpi_माप_प्रकार vsize,
			       काष्ठा karatsuba_ctx *ctx);

/*-- generic_mpih-mul1.c --*/
mpi_limb_t mpihelp_mul_1(mpi_ptr_t res_ptr, mpi_ptr_t s1_ptr,
			 mpi_माप_प्रकार s1_size, mpi_limb_t s2_limb);

/*-- mpih-भाग.c --*/
mpi_limb_t mpihelp_mod_1(mpi_ptr_t भागidend_ptr, mpi_माप_प्रकार भागidend_size,
			 mpi_limb_t भागisor_limb);
mpi_limb_t mpihelp_भागrem(mpi_ptr_t qp, mpi_माप_प्रकार qextra_limbs,
			  mpi_ptr_t np, mpi_माप_प्रकार nsize,
			  mpi_ptr_t dp, mpi_माप_प्रकार dsize);
mpi_limb_t mpihelp_भागmod_1(mpi_ptr_t quot_ptr,
			    mpi_ptr_t भागidend_ptr, mpi_माप_प्रकार भागidend_size,
			    mpi_limb_t भागisor_limb);

/*-- generic_mpih-[lr]shअगरt.c --*/
mpi_limb_t mpihelp_lshअगरt(mpi_ptr_t wp, mpi_ptr_t up, mpi_माप_प्रकार usize,
			  अचिन्हित cnt);
mpi_limb_t mpihelp_rshअगरt(mpi_ptr_t wp, mpi_ptr_t up, mpi_माप_प्रकार usize,
			  अचिन्हित cnt);

/* Define stuff क्रम दीर्घदीर्घ.h.  */
#घोषणा W_TYPE_SIZE BITS_PER_MPI_LIMB
प्रकार mpi_limb_t UWtype;
प्रकार अचिन्हित पूर्णांक UHWtype;
#अगर defined(__GNUC__)
प्रकार अचिन्हित पूर्णांक UQItype __attribute__ ((mode(QI)));
प्रकार पूर्णांक SItype __attribute__ ((mode(SI)));
प्रकार अचिन्हित पूर्णांक USItype __attribute__ ((mode(SI)));
प्रकार पूर्णांक DItype __attribute__ ((mode(DI)));
प्रकार अचिन्हित पूर्णांक UDItype __attribute__ ((mode(DI)));
#अन्यथा
प्रकार अचिन्हित अक्षर UQItype;
प्रकार दीर्घ SItype;
प्रकार अचिन्हित दीर्घ USItype;
#पूर्ण_अगर

#अगर_घोषित __GNUC__
#समावेश "mpi-inline.h"
#पूर्ण_अगर

#पूर्ण_अगर /*G10_MPI_INTERNAL_H */
