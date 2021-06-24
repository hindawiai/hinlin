<शैली गुरु>
/* ec.c -  Elliptic Curve functions
 * Copyright (C) 2007 Free Software Foundation, Inc.
 * Copyright (C) 2013 g10 Code GmbH
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
#समावेश "longlong.h"

#घोषणा poपूर्णांक_init(a)  mpi_poपूर्णांक_init((a))
#घोषणा poपूर्णांक_मुक्त(a)  mpi_poपूर्णांक_मुक्त_parts((a))

#घोषणा log_error(fmt, ...) pr_err(fmt, ##__VA_ARGS__)
#घोषणा log_fatal(fmt, ...) pr_err(fmt, ##__VA_ARGS__)

#घोषणा DIM(v) (माप(v)/माप((v)[0]))


/* Create a new poपूर्णांक option.  NBITS gives the size in bits of one
 * coordinate; it is only used to pre-allocate some resources and
 * might also be passed as 0 to use a शेष value.
 */
MPI_POINT mpi_poपूर्णांक_new(अचिन्हित पूर्णांक nbits)
अणु
	MPI_POINT p;

	(व्योम)nbits;  /* Currently not used.  */

	p = kदो_स्मृति(माप(*p), GFP_KERNEL);
	अगर (p)
		mpi_poपूर्णांक_init(p);
	वापस p;
पूर्ण
EXPORT_SYMBOL_GPL(mpi_poपूर्णांक_new);

/* Release the poपूर्णांक object P.  P may be शून्य. */
व्योम mpi_poपूर्णांक_release(MPI_POINT p)
अणु
	अगर (p) अणु
		mpi_poपूर्णांक_मुक्त_parts(p);
		kमुक्त(p);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mpi_poपूर्णांक_release);

/* Initialize the fields of a poपूर्णांक object.  gcry_mpi_poपूर्णांक_मुक्त_parts
 * may be used to release the fields.
 */
व्योम mpi_poपूर्णांक_init(MPI_POINT p)
अणु
	p->x = mpi_new(0);
	p->y = mpi_new(0);
	p->z = mpi_new(0);
पूर्ण
EXPORT_SYMBOL_GPL(mpi_poपूर्णांक_init);

/* Release the parts of a poपूर्णांक object. */
व्योम mpi_poपूर्णांक_मुक्त_parts(MPI_POINT p)
अणु
	mpi_मुक्त(p->x); p->x = शून्य;
	mpi_मुक्त(p->y); p->y = शून्य;
	mpi_मुक्त(p->z); p->z = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(mpi_poपूर्णांक_मुक्त_parts);

/* Set the value from S पूर्णांकo D.  */
अटल व्योम poपूर्णांक_set(MPI_POINT d, MPI_POINT s)
अणु
	mpi_set(d->x, s->x);
	mpi_set(d->y, s->y);
	mpi_set(d->z, s->z);
पूर्ण

अटल व्योम poपूर्णांक_resize(MPI_POINT p, काष्ठा mpi_ec_ctx *ctx)
अणु
	माप_प्रकार nlimbs = ctx->p->nlimbs;

	mpi_resize(p->x, nlimbs);
	p->x->nlimbs = nlimbs;
	mpi_resize(p->z, nlimbs);
	p->z->nlimbs = nlimbs;

	अगर (ctx->model != MPI_EC_MONTGOMERY) अणु
		mpi_resize(p->y, nlimbs);
		p->y->nlimbs = nlimbs;
	पूर्ण
पूर्ण

अटल व्योम poपूर्णांक_swap_cond(MPI_POINT d, MPI_POINT s, अचिन्हित दीर्घ swap,
		काष्ठा mpi_ec_ctx *ctx)
अणु
	mpi_swap_cond(d->x, s->x, swap);
	अगर (ctx->model != MPI_EC_MONTGOMERY)
		mpi_swap_cond(d->y, s->y, swap);
	mpi_swap_cond(d->z, s->z, swap);
पूर्ण


/* W = W mod P.  */
अटल व्योम ec_mod(MPI w, काष्ठा mpi_ec_ctx *ec)
अणु
	अगर (ec->t.p_barrett)
		mpi_mod_barrett(w, w, ec->t.p_barrett);
	अन्यथा
		mpi_mod(w, w, ec->p);
पूर्ण

अटल व्योम ec_addm(MPI w, MPI u, MPI v, काष्ठा mpi_ec_ctx *ctx)
अणु
	mpi_add(w, u, v);
	ec_mod(w, ctx);
पूर्ण

अटल व्योम ec_subm(MPI w, MPI u, MPI v, काष्ठा mpi_ec_ctx *ec)
अणु
	mpi_sub(w, u, v);
	जबतक (w->sign)
		mpi_add(w, w, ec->p);
	/*ec_mod(w, ec);*/
पूर्ण

अटल व्योम ec_mulm(MPI w, MPI u, MPI v, काष्ठा mpi_ec_ctx *ctx)
अणु
	mpi_mul(w, u, v);
	ec_mod(w, ctx);
पूर्ण

/* W = 2 * U mod P.  */
अटल व्योम ec_mul2(MPI w, MPI u, काष्ठा mpi_ec_ctx *ctx)
अणु
	mpi_lshअगरt(w, u, 1);
	ec_mod(w, ctx);
पूर्ण

अटल व्योम ec_घातm(MPI w, स्थिर MPI b, स्थिर MPI e,
		काष्ठा mpi_ec_ctx *ctx)
अणु
	mpi_घातm(w, b, e, ctx->p);
	/* mpi_असल(w); */
पूर्ण

/* Shortcut क्रम
 * ec_घातm(B, B, mpi_स्थिर(MPI_C_TWO), ctx);
 * क्रम easier optimization.
 */
अटल व्योम ec_घात2(MPI w, स्थिर MPI b, काष्ठा mpi_ec_ctx *ctx)
अणु
	/* Using mpi_mul is slightly faster (at least on amd64).  */
	/* mpi_घातm(w, b, mpi_स्थिर(MPI_C_TWO), ctx->p); */
	ec_mulm(w, b, b, ctx);
पूर्ण

/* Shortcut क्रम
 * ec_घातm(B, B, mpi_स्थिर(MPI_C_THREE), ctx);
 * क्रम easier optimization.
 */
अटल व्योम ec_घात3(MPI w, स्थिर MPI b, काष्ठा mpi_ec_ctx *ctx)
अणु
	mpi_घातm(w, b, mpi_स्थिर(MPI_C_THREE), ctx->p);
पूर्ण

अटल व्योम ec_invm(MPI x, MPI a, काष्ठा mpi_ec_ctx *ctx)
अणु
	अगर (!mpi_invm(x, a, ctx->p))
		log_error("ec_invm: inverse does not exist:\n");
पूर्ण

अटल व्योम mpih_set_cond(mpi_ptr_t wp, mpi_ptr_t up,
		mpi_माप_प्रकार usize, अचिन्हित दीर्घ set)
अणु
	mpi_माप_प्रकार i;
	mpi_limb_t mask = ((mpi_limb_t)0) - set;
	mpi_limb_t x;

	क्रम (i = 0; i < usize; i++) अणु
		x = mask & (wp[i] ^ up[i]);
		wp[i] = wp[i] ^ x;
	पूर्ण
पूर्ण

/* Routines क्रम 2^255 - 19.  */

#घोषणा LIMB_SIZE_25519 ((256+BITS_PER_MPI_LIMB-1)/BITS_PER_MPI_LIMB)

अटल व्योम ec_addm_25519(MPI w, MPI u, MPI v, काष्ठा mpi_ec_ctx *ctx)
अणु
	mpi_ptr_t wp, up, vp;
	mpi_माप_प्रकार wsize = LIMB_SIZE_25519;
	mpi_limb_t n[LIMB_SIZE_25519];
	mpi_limb_t borrow;

	अगर (w->nlimbs != wsize || u->nlimbs != wsize || v->nlimbs != wsize)
		log_bug("addm_25519: different sizes\n");

	स_रखो(n, 0, माप(n));
	up = u->d;
	vp = v->d;
	wp = w->d;

	mpihelp_add_n(wp, up, vp, wsize);
	borrow = mpihelp_sub_n(wp, wp, ctx->p->d, wsize);
	mpih_set_cond(n, ctx->p->d, wsize, (borrow != 0UL));
	mpihelp_add_n(wp, wp, n, wsize);
	wp[LIMB_SIZE_25519-1] &= ~((mpi_limb_t)1 << (255 % BITS_PER_MPI_LIMB));
पूर्ण

अटल व्योम ec_subm_25519(MPI w, MPI u, MPI v, काष्ठा mpi_ec_ctx *ctx)
अणु
	mpi_ptr_t wp, up, vp;
	mpi_माप_प्रकार wsize = LIMB_SIZE_25519;
	mpi_limb_t n[LIMB_SIZE_25519];
	mpi_limb_t borrow;

	अगर (w->nlimbs != wsize || u->nlimbs != wsize || v->nlimbs != wsize)
		log_bug("subm_25519: different sizes\n");

	स_रखो(n, 0, माप(n));
	up = u->d;
	vp = v->d;
	wp = w->d;

	borrow = mpihelp_sub_n(wp, up, vp, wsize);
	mpih_set_cond(n, ctx->p->d, wsize, (borrow != 0UL));
	mpihelp_add_n(wp, wp, n, wsize);
	wp[LIMB_SIZE_25519-1] &= ~((mpi_limb_t)1 << (255 % BITS_PER_MPI_LIMB));
पूर्ण

अटल व्योम ec_mulm_25519(MPI w, MPI u, MPI v, काष्ठा mpi_ec_ctx *ctx)
अणु
	mpi_ptr_t wp, up, vp;
	mpi_माप_प्रकार wsize = LIMB_SIZE_25519;
	mpi_limb_t n[LIMB_SIZE_25519*2];
	mpi_limb_t m[LIMB_SIZE_25519+1];
	mpi_limb_t cy;
	पूर्णांक msb;

	(व्योम)ctx;
	अगर (w->nlimbs != wsize || u->nlimbs != wsize || v->nlimbs != wsize)
		log_bug("mulm_25519: different sizes\n");

	up = u->d;
	vp = v->d;
	wp = w->d;

	mpihelp_mul_n(n, up, vp, wsize);
	स_नकल(wp, n, wsize * BYTES_PER_MPI_LIMB);
	wp[LIMB_SIZE_25519-1] &= ~((mpi_limb_t)1 << (255 % BITS_PER_MPI_LIMB));

	स_नकल(m, n+LIMB_SIZE_25519-1, (wsize+1) * BYTES_PER_MPI_LIMB);
	mpihelp_rshअगरt(m, m, LIMB_SIZE_25519+1, (255 % BITS_PER_MPI_LIMB));

	स_नकल(n, m, wsize * BYTES_PER_MPI_LIMB);
	cy = mpihelp_lshअगरt(m, m, LIMB_SIZE_25519, 4);
	m[LIMB_SIZE_25519] = cy;
	cy = mpihelp_add_n(m, m, n, wsize);
	m[LIMB_SIZE_25519] += cy;
	cy = mpihelp_add_n(m, m, n, wsize);
	m[LIMB_SIZE_25519] += cy;
	cy = mpihelp_add_n(m, m, n, wsize);
	m[LIMB_SIZE_25519] += cy;

	cy = mpihelp_add_n(wp, wp, m, wsize);
	m[LIMB_SIZE_25519] += cy;

	स_रखो(m, 0, wsize * BYTES_PER_MPI_LIMB);
	msb = (wp[LIMB_SIZE_25519-1] >> (255 % BITS_PER_MPI_LIMB));
	m[0] = (m[LIMB_SIZE_25519] * 2 + msb) * 19;
	wp[LIMB_SIZE_25519-1] &= ~((mpi_limb_t)1 << (255 % BITS_PER_MPI_LIMB));
	mpihelp_add_n(wp, wp, m, wsize);

	m[0] = 0;
	cy = mpihelp_sub_n(wp, wp, ctx->p->d, wsize);
	mpih_set_cond(m, ctx->p->d, wsize, (cy != 0UL));
	mpihelp_add_n(wp, wp, m, wsize);
पूर्ण

अटल व्योम ec_mul2_25519(MPI w, MPI u, काष्ठा mpi_ec_ctx *ctx)
अणु
	ec_addm_25519(w, u, u, ctx);
पूर्ण

अटल व्योम ec_घात2_25519(MPI w, स्थिर MPI b, काष्ठा mpi_ec_ctx *ctx)
अणु
	ec_mulm_25519(w, b, b, ctx);
पूर्ण

/* Routines क्रम 2^448 - 2^224 - 1.  */

#घोषणा LIMB_SIZE_448 ((448+BITS_PER_MPI_LIMB-1)/BITS_PER_MPI_LIMB)
#घोषणा LIMB_SIZE_HALF_448 ((LIMB_SIZE_448+1)/2)

अटल व्योम ec_addm_448(MPI w, MPI u, MPI v, काष्ठा mpi_ec_ctx *ctx)
अणु
	mpi_ptr_t wp, up, vp;
	mpi_माप_प्रकार wsize = LIMB_SIZE_448;
	mpi_limb_t n[LIMB_SIZE_448];
	mpi_limb_t cy;

	अगर (w->nlimbs != wsize || u->nlimbs != wsize || v->nlimbs != wsize)
		log_bug("addm_448: different sizes\n");

	स_रखो(n, 0, माप(n));
	up = u->d;
	vp = v->d;
	wp = w->d;

	cy = mpihelp_add_n(wp, up, vp, wsize);
	mpih_set_cond(n, ctx->p->d, wsize, (cy != 0UL));
	mpihelp_sub_n(wp, wp, n, wsize);
पूर्ण

अटल व्योम ec_subm_448(MPI w, MPI u, MPI v, काष्ठा mpi_ec_ctx *ctx)
अणु
	mpi_ptr_t wp, up, vp;
	mpi_माप_प्रकार wsize = LIMB_SIZE_448;
	mpi_limb_t n[LIMB_SIZE_448];
	mpi_limb_t borrow;

	अगर (w->nlimbs != wsize || u->nlimbs != wsize || v->nlimbs != wsize)
		log_bug("subm_448: different sizes\n");

	स_रखो(n, 0, माप(n));
	up = u->d;
	vp = v->d;
	wp = w->d;

	borrow = mpihelp_sub_n(wp, up, vp, wsize);
	mpih_set_cond(n, ctx->p->d, wsize, (borrow != 0UL));
	mpihelp_add_n(wp, wp, n, wsize);
पूर्ण

अटल व्योम ec_mulm_448(MPI w, MPI u, MPI v, काष्ठा mpi_ec_ctx *ctx)
अणु
	mpi_ptr_t wp, up, vp;
	mpi_माप_प्रकार wsize = LIMB_SIZE_448;
	mpi_limb_t n[LIMB_SIZE_448*2];
	mpi_limb_t a2[LIMB_SIZE_HALF_448];
	mpi_limb_t a3[LIMB_SIZE_HALF_448];
	mpi_limb_t b0[LIMB_SIZE_HALF_448];
	mpi_limb_t b1[LIMB_SIZE_HALF_448];
	mpi_limb_t cy;
	पूर्णांक i;
#अगर (LIMB_SIZE_HALF_448 > LIMB_SIZE_448/2)
	mpi_limb_t b1_rest, a3_rest;
#पूर्ण_अगर

	अगर (w->nlimbs != wsize || u->nlimbs != wsize || v->nlimbs != wsize)
		log_bug("mulm_448: different sizes\n");

	up = u->d;
	vp = v->d;
	wp = w->d;

	mpihelp_mul_n(n, up, vp, wsize);

	क्रम (i = 0; i < (wsize + 1) / 2; i++) अणु
		b0[i] = n[i];
		b1[i] = n[i+wsize/2];
		a2[i] = n[i+wsize];
		a3[i] = n[i+wsize+wsize/2];
	पूर्ण

#अगर (LIMB_SIZE_HALF_448 > LIMB_SIZE_448/2)
	b0[LIMB_SIZE_HALF_448-1] &= ((mpi_limb_t)1UL << 32)-1;
	a2[LIMB_SIZE_HALF_448-1] &= ((mpi_limb_t)1UL << 32)-1;

	b1_rest = 0;
	a3_rest = 0;

	क्रम (i = (wsize + 1) / 2 - 1; i >= 0; i--) अणु
		mpi_limb_t b1v, a3v;
		b1v = b1[i];
		a3v = a3[i];
		b1[i] = (b1_rest << 32) | (b1v >> 32);
		a3[i] = (a3_rest << 32) | (a3v >> 32);
		b1_rest = b1v & (((mpi_limb_t)1UL << 32)-1);
		a3_rest = a3v & (((mpi_limb_t)1UL << 32)-1);
	पूर्ण
#पूर्ण_अगर

	cy = mpihelp_add_n(b0, b0, a2, LIMB_SIZE_HALF_448);
	cy += mpihelp_add_n(b0, b0, a3, LIMB_SIZE_HALF_448);
	क्रम (i = 0; i < (wsize + 1) / 2; i++)
		wp[i] = b0[i];
#अगर (LIMB_SIZE_HALF_448 > LIMB_SIZE_448/2)
	wp[LIMB_SIZE_HALF_448-1] &= (((mpi_limb_t)1UL << 32)-1);
#पूर्ण_अगर

#अगर (LIMB_SIZE_HALF_448 > LIMB_SIZE_448/2)
	cy = b0[LIMB_SIZE_HALF_448-1] >> 32;
#पूर्ण_अगर

	cy = mpihelp_add_1(b1, b1, LIMB_SIZE_HALF_448, cy);
	cy += mpihelp_add_n(b1, b1, a2, LIMB_SIZE_HALF_448);
	cy += mpihelp_add_n(b1, b1, a3, LIMB_SIZE_HALF_448);
	cy += mpihelp_add_n(b1, b1, a3, LIMB_SIZE_HALF_448);
#अगर (LIMB_SIZE_HALF_448 > LIMB_SIZE_448/2)
	b1_rest = 0;
	क्रम (i = (wsize + 1) / 2 - 1; i >= 0; i--) अणु
		mpi_limb_t b1v = b1[i];
		b1[i] = (b1_rest << 32) | (b1v >> 32);
		b1_rest = b1v & (((mpi_limb_t)1UL << 32)-1);
	पूर्ण
	wp[LIMB_SIZE_HALF_448-1] |= (b1_rest << 32);
#पूर्ण_अगर
	क्रम (i = 0; i < wsize / 2; i++)
		wp[i+(wsize + 1) / 2] = b1[i];

#अगर (LIMB_SIZE_HALF_448 > LIMB_SIZE_448/2)
	cy = b1[LIMB_SIZE_HALF_448-1];
#पूर्ण_अगर

	स_रखो(n, 0, wsize * BYTES_PER_MPI_LIMB);

#अगर (LIMB_SIZE_HALF_448 > LIMB_SIZE_448/2)
	n[LIMB_SIZE_HALF_448-1] = cy << 32;
#अन्यथा
	n[LIMB_SIZE_HALF_448] = cy;
#पूर्ण_अगर
	n[0] = cy;
	mpihelp_add_n(wp, wp, n, wsize);

	स_रखो(n, 0, wsize * BYTES_PER_MPI_LIMB);
	cy = mpihelp_sub_n(wp, wp, ctx->p->d, wsize);
	mpih_set_cond(n, ctx->p->d, wsize, (cy != 0UL));
	mpihelp_add_n(wp, wp, n, wsize);
पूर्ण

अटल व्योम ec_mul2_448(MPI w, MPI u, काष्ठा mpi_ec_ctx *ctx)
अणु
	ec_addm_448(w, u, u, ctx);
पूर्ण

अटल व्योम ec_घात2_448(MPI w, स्थिर MPI b, काष्ठा mpi_ec_ctx *ctx)
अणु
	ec_mulm_448(w, b, b, ctx);
पूर्ण

काष्ठा field_table अणु
	स्थिर अक्षर *p;

	/* computation routines क्रम the field.  */
	व्योम (*addm)(MPI w, MPI u, MPI v, काष्ठा mpi_ec_ctx *ctx);
	व्योम (*subm)(MPI w, MPI u, MPI v, काष्ठा mpi_ec_ctx *ctx);
	व्योम (*mulm)(MPI w, MPI u, MPI v, काष्ठा mpi_ec_ctx *ctx);
	व्योम (*mul2)(MPI w, MPI u, काष्ठा mpi_ec_ctx *ctx);
	व्योम (*घात2)(MPI w, स्थिर MPI b, काष्ठा mpi_ec_ctx *ctx);
पूर्ण;

अटल स्थिर काष्ठा field_table field_table[] = अणु
	अणु
		"0x7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFED",
		ec_addm_25519,
		ec_subm_25519,
		ec_mulm_25519,
		ec_mul2_25519,
		ec_घात2_25519
	पूर्ण,
	अणु
		"0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE"
		"FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
		ec_addm_448,
		ec_subm_448,
		ec_mulm_448,
		ec_mul2_448,
		ec_घात2_448
	पूर्ण,
	अणु शून्य, शून्य, शून्य, शून्य, शून्य, शून्य पूर्ण,
पूर्ण;

/* Force recomputation of all helper variables.  */
अटल व्योम mpi_ec_get_reset(काष्ठा mpi_ec_ctx *ec)
अणु
	ec->t.valid.a_is_pminus3 = 0;
	ec->t.valid.two_inv_p = 0;
पूर्ण

/* Accessor क्रम helper variable.  */
अटल पूर्णांक ec_get_a_is_pminus3(काष्ठा mpi_ec_ctx *ec)
अणु
	MPI पंचांगp;

	अगर (!ec->t.valid.a_is_pminus3) अणु
		ec->t.valid.a_is_pminus3 = 1;
		पंचांगp = mpi_alloc_like(ec->p);
		mpi_sub_ui(पंचांगp, ec->p, 3);
		ec->t.a_is_pminus3 = !mpi_cmp(ec->a, पंचांगp);
		mpi_मुक्त(पंचांगp);
	पूर्ण

	वापस ec->t.a_is_pminus3;
पूर्ण

/* Accessor क्रम helper variable.  */
अटल MPI ec_get_two_inv_p(काष्ठा mpi_ec_ctx *ec)
अणु
	अगर (!ec->t.valid.two_inv_p) अणु
		ec->t.valid.two_inv_p = 1;
		अगर (!ec->t.two_inv_p)
			ec->t.two_inv_p = mpi_alloc(0);
		ec_invm(ec->t.two_inv_p, mpi_स्थिर(MPI_C_TWO), ec);
	पूर्ण
	वापस ec->t.two_inv_p;
पूर्ण

अटल स्थिर अक्षर *स्थिर curve25519_bad_poपूर्णांकs[] = अणु
	"0x7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffed",
	"0x0000000000000000000000000000000000000000000000000000000000000000",
	"0x0000000000000000000000000000000000000000000000000000000000000001",
	"0x00b8495f16056286fdb1329ceb8d09da6ac49ff1fae35616aeb8413b7c7aebe0",
	"0x57119fd0dd4e22d8868e1c58c45c44045bef839c55b1d0b1248c50a3bc959c5f",
	"0x7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffec",
	"0x7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffee",
	शून्य
पूर्ण;

अटल स्थिर अक्षर *स्थिर curve448_bad_poपूर्णांकs[] = अणु
	"0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffe"
	"ffffffffffffffffffffffffffffffffffffffffffffffffffffffff",
	"0x00000000000000000000000000000000000000000000000000000000"
	"00000000000000000000000000000000000000000000000000000000",
	"0x00000000000000000000000000000000000000000000000000000000"
	"00000000000000000000000000000000000000000000000000000001",
	"0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffe"
	"fffffffffffffffffffffffffffffffffffffffffffffffffffffffe",
	"0xffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
	"00000000000000000000000000000000000000000000000000000000",
	शून्य
पूर्ण;

अटल स्थिर अक्षर *स्थिर *bad_poपूर्णांकs_table[] = अणु
	curve25519_bad_poपूर्णांकs,
	curve448_bad_poपूर्णांकs,
पूर्ण;

अटल व्योम mpi_ec_coefficient_normalize(MPI a, MPI p)
अणु
	अगर (a->sign) अणु
		mpi_resize(a, p->nlimbs);
		mpihelp_sub_n(a->d, p->d, a->d, p->nlimbs);
		a->nlimbs = p->nlimbs;
		a->sign = 0;
	पूर्ण
पूर्ण

/* This function initialized a context क्रम elliptic curve based on the
 * field GF(p).  P is the prime specअगरying this field, A is the first
 * coefficient.  CTX is expected to be zeroized.
 */
व्योम mpi_ec_init(काष्ठा mpi_ec_ctx *ctx, क्रमागत gcry_mpi_ec_models model,
			क्रमागत ecc_dialects dialect,
			पूर्णांक flags, MPI p, MPI a, MPI b)
अणु
	पूर्णांक i;
	अटल पूर्णांक use_barrett = -1 /* TODO: 1 or -1 */;

	mpi_ec_coefficient_normalize(a, p);
	mpi_ec_coefficient_normalize(b, p);

	/* Fixme: Do we want to check some स्थिरraपूर्णांकs? e.g.  a < p  */

	ctx->model = model;
	ctx->dialect = dialect;
	ctx->flags = flags;
	अगर (dialect == ECC_DIALECT_ED25519)
		ctx->nbits = 256;
	अन्यथा
		ctx->nbits = mpi_get_nbits(p);
	ctx->p = mpi_copy(p);
	ctx->a = mpi_copy(a);
	ctx->b = mpi_copy(b);

	ctx->t.p_barrett = use_barrett > 0 ? mpi_barrett_init(ctx->p, 0) : शून्य;

	mpi_ec_get_reset(ctx);

	अगर (model == MPI_EC_MONTGOMERY) अणु
		क्रम (i = 0; i < DIM(bad_poपूर्णांकs_table); i++) अणु
			MPI p_candidate = mpi_scanval(bad_poपूर्णांकs_table[i][0]);
			पूर्णांक match_p = !mpi_cmp(ctx->p, p_candidate);
			पूर्णांक j;

			mpi_मुक्त(p_candidate);
			अगर (!match_p)
				जारी;

			क्रम (j = 0; i < DIM(ctx->t.scratch) && bad_poपूर्णांकs_table[i][j]; j++)
				ctx->t.scratch[j] = mpi_scanval(bad_poपूर्णांकs_table[i][j]);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Allocate scratch variables.  */
		क्रम (i = 0; i < DIM(ctx->t.scratch); i++)
			ctx->t.scratch[i] = mpi_alloc_like(ctx->p);
	पूर्ण

	ctx->addm = ec_addm;
	ctx->subm = ec_subm;
	ctx->mulm = ec_mulm;
	ctx->mul2 = ec_mul2;
	ctx->घात2 = ec_घात2;

	क्रम (i = 0; field_table[i].p; i++) अणु
		MPI f_p;

		f_p = mpi_scanval(field_table[i].p);
		अगर (!f_p)
			अवरोध;

		अगर (!mpi_cmp(p, f_p)) अणु
			ctx->addm = field_table[i].addm;
			ctx->subm = field_table[i].subm;
			ctx->mulm = field_table[i].mulm;
			ctx->mul2 = field_table[i].mul2;
			ctx->घात2 = field_table[i].घात2;
			mpi_मुक्त(f_p);

			mpi_resize(ctx->a, ctx->p->nlimbs);
			ctx->a->nlimbs = ctx->p->nlimbs;

			mpi_resize(ctx->b, ctx->p->nlimbs);
			ctx->b->nlimbs = ctx->p->nlimbs;

			क्रम (i = 0; i < DIM(ctx->t.scratch) && ctx->t.scratch[i]; i++)
				ctx->t.scratch[i]->nlimbs = ctx->p->nlimbs;

			अवरोध;
		पूर्ण

		mpi_मुक्त(f_p);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mpi_ec_init);

व्योम mpi_ec_deinit(काष्ठा mpi_ec_ctx *ctx)
अणु
	पूर्णांक i;

	mpi_barrett_मुक्त(ctx->t.p_barrett);

	/* Doमुख्य parameter.  */
	mpi_मुक्त(ctx->p);
	mpi_मुक्त(ctx->a);
	mpi_मुक्त(ctx->b);
	mpi_poपूर्णांक_release(ctx->G);
	mpi_मुक्त(ctx->n);

	/* The key.  */
	mpi_poपूर्णांक_release(ctx->Q);
	mpi_मुक्त(ctx->d);

	/* Private data of ec.c.  */
	mpi_मुक्त(ctx->t.two_inv_p);

	क्रम (i = 0; i < DIM(ctx->t.scratch); i++)
		mpi_मुक्त(ctx->t.scratch[i]);
पूर्ण
EXPORT_SYMBOL_GPL(mpi_ec_deinit);

/* Compute the affine coordinates from the projective coordinates in
 * POINT.  Set them पूर्णांकo X and Y.  If one coordinate is not required,
 * X or Y may be passed as शून्य.  CTX is the usual context. Returns: 0
 * on success or !0 अगर POINT is at infinity.
 */
पूर्णांक mpi_ec_get_affine(MPI x, MPI y, MPI_POINT poपूर्णांक, काष्ठा mpi_ec_ctx *ctx)
अणु
	अगर (!mpi_cmp_ui(poपूर्णांक->z, 0))
		वापस -1;

	चयन (ctx->model) अणु
	हाल MPI_EC_WEIERSTRASS: /* Using Jacobian coordinates.  */
		अणु
			MPI z1, z2, z3;

			z1 = mpi_new(0);
			z2 = mpi_new(0);
			ec_invm(z1, poपूर्णांक->z, ctx);  /* z1 = z^(-1) mod p  */
			ec_mulm(z2, z1, z1, ctx);    /* z2 = z^(-2) mod p  */

			अगर (x)
				ec_mulm(x, poपूर्णांक->x, z2, ctx);

			अगर (y) अणु
				z3 = mpi_new(0);
				ec_mulm(z3, z2, z1, ctx);      /* z3 = z^(-3) mod p */
				ec_mulm(y, poपूर्णांक->y, z3, ctx);
				mpi_मुक्त(z3);
			पूर्ण

			mpi_मुक्त(z2);
			mpi_मुक्त(z1);
		पूर्ण
		वापस 0;

	हाल MPI_EC_MONTGOMERY:
		अणु
			अगर (x)
				mpi_set(x, poपूर्णांक->x);

			अगर (y) अणु
				log_fatal("%s: Getting Y-coordinate on %s is not supported\n",
						"mpi_ec_get_affine", "Montgomery");
				वापस -1;
			पूर्ण
		पूर्ण
		वापस 0;

	हाल MPI_EC_EDWARDS:
		अणु
			MPI z;

			z = mpi_new(0);
			ec_invm(z, poपूर्णांक->z, ctx);

			mpi_resize(z, ctx->p->nlimbs);
			z->nlimbs = ctx->p->nlimbs;

			अगर (x) अणु
				mpi_resize(x, ctx->p->nlimbs);
				x->nlimbs = ctx->p->nlimbs;
				ctx->mulm(x, poपूर्णांक->x, z, ctx);
			पूर्ण
			अगर (y) अणु
				mpi_resize(y, ctx->p->nlimbs);
				y->nlimbs = ctx->p->nlimbs;
				ctx->mulm(y, poपूर्णांक->y, z, ctx);
			पूर्ण

			mpi_मुक्त(z);
		पूर्ण
		वापस 0;

	शेष:
		वापस -1;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mpi_ec_get_affine);

/*  RESULT = 2 * POINT  (Weierstrass version). */
अटल व्योम dup_poपूर्णांक_weierstrass(MPI_POINT result,
		MPI_POINT poपूर्णांक, काष्ठा mpi_ec_ctx *ctx)
अणु
#घोषणा x3 (result->x)
#घोषणा y3 (result->y)
#घोषणा z3 (result->z)
#घोषणा t1 (ctx->t.scratch[0])
#घोषणा t2 (ctx->t.scratch[1])
#घोषणा t3 (ctx->t.scratch[2])
#घोषणा l1 (ctx->t.scratch[3])
#घोषणा l2 (ctx->t.scratch[4])
#घोषणा l3 (ctx->t.scratch[5])

	अगर (!mpi_cmp_ui(poपूर्णांक->y, 0) || !mpi_cmp_ui(poपूर्णांक->z, 0)) अणु
		/* P_y == 0 || P_z == 0 => [1:1:0] */
		mpi_set_ui(x3, 1);
		mpi_set_ui(y3, 1);
		mpi_set_ui(z3, 0);
	पूर्ण अन्यथा अणु
		अगर (ec_get_a_is_pminus3(ctx)) अणु
			/* Use the faster हाल.  */
			/* L1 = 3(X - Z^2)(X + Z^2) */
			/*                          T1: used क्रम Z^2. */
			/*                          T2: used क्रम the right term. */
			ec_घात2(t1, poपूर्णांक->z, ctx);
			ec_subm(l1, poपूर्णांक->x, t1, ctx);
			ec_mulm(l1, l1, mpi_स्थिर(MPI_C_THREE), ctx);
			ec_addm(t2, poपूर्णांक->x, t1, ctx);
			ec_mulm(l1, l1, t2, ctx);
		पूर्ण अन्यथा अणु
			/* Standard हाल. */
			/* L1 = 3X^2 + aZ^4 */
			/*                          T1: used क्रम aZ^4. */
			ec_घात2(l1, poपूर्णांक->x, ctx);
			ec_mulm(l1, l1, mpi_स्थिर(MPI_C_THREE), ctx);
			ec_घातm(t1, poपूर्णांक->z, mpi_स्थिर(MPI_C_FOUR), ctx);
			ec_mulm(t1, t1, ctx->a, ctx);
			ec_addm(l1, l1, t1, ctx);
		पूर्ण
		/* Z3 = 2YZ */
		ec_mulm(z3, poपूर्णांक->y, poपूर्णांक->z, ctx);
		ec_mul2(z3, z3, ctx);

		/* L2 = 4XY^2 */
		/*                              T2: used क्रम Y2; required later. */
		ec_घात2(t2, poपूर्णांक->y, ctx);
		ec_mulm(l2, t2, poपूर्णांक->x, ctx);
		ec_mulm(l2, l2, mpi_स्थिर(MPI_C_FOUR), ctx);

		/* X3 = L1^2 - 2L2 */
		/*                              T1: used क्रम L2^2. */
		ec_घात2(x3, l1, ctx);
		ec_mul2(t1, l2, ctx);
		ec_subm(x3, x3, t1, ctx);

		/* L3 = 8Y^4 */
		/*                              T2: taken from above. */
		ec_घात2(t2, t2, ctx);
		ec_mulm(l3, t2, mpi_स्थिर(MPI_C_EIGHT), ctx);

		/* Y3 = L1(L2 - X3) - L3 */
		ec_subm(y3, l2, x3, ctx);
		ec_mulm(y3, y3, l1, ctx);
		ec_subm(y3, y3, l3, ctx);
	पूर्ण

#अघोषित x3
#अघोषित y3
#अघोषित z3
#अघोषित t1
#अघोषित t2
#अघोषित t3
#अघोषित l1
#अघोषित l2
#अघोषित l3
पूर्ण

/*  RESULT = 2 * POINT  (Montgomery version). */
अटल व्योम dup_poपूर्णांक_montgomery(MPI_POINT result,
				MPI_POINT poपूर्णांक, काष्ठा mpi_ec_ctx *ctx)
अणु
	(व्योम)result;
	(व्योम)poपूर्णांक;
	(व्योम)ctx;
	log_fatal("%s: %s not yet supported\n",
			"mpi_ec_dup_point", "Montgomery");
पूर्ण

/*  RESULT = 2 * POINT  (Twisted Edwards version). */
अटल व्योम dup_poपूर्णांक_edwards(MPI_POINT result,
		MPI_POINT poपूर्णांक, काष्ठा mpi_ec_ctx *ctx)
अणु
#घोषणा X1 (poपूर्णांक->x)
#घोषणा Y1 (poपूर्णांक->y)
#घोषणा Z1 (poपूर्णांक->z)
#घोषणा X3 (result->x)
#घोषणा Y3 (result->y)
#घोषणा Z3 (result->z)
#घोषणा B (ctx->t.scratch[0])
#घोषणा C (ctx->t.scratch[1])
#घोषणा D (ctx->t.scratch[2])
#घोषणा E (ctx->t.scratch[3])
#घोषणा F (ctx->t.scratch[4])
#घोषणा H (ctx->t.scratch[5])
#घोषणा J (ctx->t.scratch[6])

	/* Compute: (X_3 : Y_3 : Z_3) = 2( X_1 : Y_1 : Z_1 ) */

	/* B = (X_1 + Y_1)^2  */
	ctx->addm(B, X1, Y1, ctx);
	ctx->घात2(B, B, ctx);

	/* C = X_1^2 */
	/* D = Y_1^2 */
	ctx->घात2(C, X1, ctx);
	ctx->घात2(D, Y1, ctx);

	/* E = aC */
	अगर (ctx->dialect == ECC_DIALECT_ED25519)
		ctx->subm(E, ctx->p, C, ctx);
	अन्यथा
		ctx->mulm(E, ctx->a, C, ctx);

	/* F = E + D */
	ctx->addm(F, E, D, ctx);

	/* H = Z_1^2 */
	ctx->घात2(H, Z1, ctx);

	/* J = F - 2H */
	ctx->mul2(J, H, ctx);
	ctx->subm(J, F, J, ctx);

	/* X_3 = (B - C - D) तङ J */
	ctx->subm(X3, B, C, ctx);
	ctx->subm(X3, X3, D, ctx);
	ctx->mulm(X3, X3, J, ctx);

	/* Y_3 = F तङ (E - D) */
	ctx->subm(Y3, E, D, ctx);
	ctx->mulm(Y3, Y3, F, ctx);

	/* Z_3 = F तङ J */
	ctx->mulm(Z3, F, J, ctx);

#अघोषित X1
#अघोषित Y1
#अघोषित Z1
#अघोषित X3
#अघोषित Y3
#अघोषित Z3
#अघोषित B
#अघोषित C
#अघोषित D
#अघोषित E
#अघोषित F
#अघोषित H
#अघोषित J
पूर्ण

/*  RESULT = 2 * POINT  */
अटल व्योम
mpi_ec_dup_poपूर्णांक(MPI_POINT result, MPI_POINT poपूर्णांक, काष्ठा mpi_ec_ctx *ctx)
अणु
	चयन (ctx->model) अणु
	हाल MPI_EC_WEIERSTRASS:
		dup_poपूर्णांक_weierstrass(result, poपूर्णांक, ctx);
		अवरोध;
	हाल MPI_EC_MONTGOMERY:
		dup_poपूर्णांक_montgomery(result, poपूर्णांक, ctx);
		अवरोध;
	हाल MPI_EC_EDWARDS:
		dup_poपूर्णांक_edwards(result, poपूर्णांक, ctx);
		अवरोध;
	पूर्ण
पूर्ण

/* RESULT = P1 + P2  (Weierstrass version).*/
अटल व्योम add_poपूर्णांकs_weierstrass(MPI_POINT result,
		MPI_POINT p1, MPI_POINT p2,
		काष्ठा mpi_ec_ctx *ctx)
अणु
#घोषणा x1 (p1->x)
#घोषणा y1 (p1->y)
#घोषणा z1 (p1->z)
#घोषणा x2 (p2->x)
#घोषणा y2 (p2->y)
#घोषणा z2 (p2->z)
#घोषणा x3 (result->x)
#घोषणा y3 (result->y)
#घोषणा z3 (result->z)
#घोषणा l1 (ctx->t.scratch[0])
#घोषणा l2 (ctx->t.scratch[1])
#घोषणा l3 (ctx->t.scratch[2])
#घोषणा l4 (ctx->t.scratch[3])
#घोषणा l5 (ctx->t.scratch[4])
#घोषणा l6 (ctx->t.scratch[5])
#घोषणा l7 (ctx->t.scratch[6])
#घोषणा l8 (ctx->t.scratch[7])
#घोषणा l9 (ctx->t.scratch[8])
#घोषणा t1 (ctx->t.scratch[9])
#घोषणा t2 (ctx->t.scratch[10])

	अगर ((!mpi_cmp(x1, x2)) && (!mpi_cmp(y1, y2)) && (!mpi_cmp(z1, z2))) अणु
		/* Same poपूर्णांक; need to call the duplicate function.  */
		mpi_ec_dup_poपूर्णांक(result, p1, ctx);
	पूर्ण अन्यथा अगर (!mpi_cmp_ui(z1, 0)) अणु
		/* P1 is at infinity.  */
		mpi_set(x3, p2->x);
		mpi_set(y3, p2->y);
		mpi_set(z3, p2->z);
	पूर्ण अन्यथा अगर (!mpi_cmp_ui(z2, 0)) अणु
		/* P2 is at infinity.  */
		mpi_set(x3, p1->x);
		mpi_set(y3, p1->y);
		mpi_set(z3, p1->z);
	पूर्ण अन्यथा अणु
		पूर्णांक z1_is_one = !mpi_cmp_ui(z1, 1);
		पूर्णांक z2_is_one = !mpi_cmp_ui(z2, 1);

		/* l1 = x1 z2^2  */
		/* l2 = x2 z1^2  */
		अगर (z2_is_one)
			mpi_set(l1, x1);
		अन्यथा अणु
			ec_घात2(l1, z2, ctx);
			ec_mulm(l1, l1, x1, ctx);
		पूर्ण
		अगर (z1_is_one)
			mpi_set(l2, x2);
		अन्यथा अणु
			ec_घात2(l2, z1, ctx);
			ec_mulm(l2, l2, x2, ctx);
		पूर्ण
		/* l3 = l1 - l2 */
		ec_subm(l3, l1, l2, ctx);
		/* l4 = y1 z2^3  */
		ec_घातm(l4, z2, mpi_स्थिर(MPI_C_THREE), ctx);
		ec_mulm(l4, l4, y1, ctx);
		/* l5 = y2 z1^3  */
		ec_घातm(l5, z1, mpi_स्थिर(MPI_C_THREE), ctx);
		ec_mulm(l5, l5, y2, ctx);
		/* l6 = l4 - l5  */
		ec_subm(l6, l4, l5, ctx);

		अगर (!mpi_cmp_ui(l3, 0)) अणु
			अगर (!mpi_cmp_ui(l6, 0)) अणु
				/* P1 and P2 are the same - use duplicate function. */
				mpi_ec_dup_poपूर्णांक(result, p1, ctx);
			पूर्ण अन्यथा अणु
				/* P1 is the inverse of P2.  */
				mpi_set_ui(x3, 1);
				mpi_set_ui(y3, 1);
				mpi_set_ui(z3, 0);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* l7 = l1 + l2  */
			ec_addm(l7, l1, l2, ctx);
			/* l8 = l4 + l5  */
			ec_addm(l8, l4, l5, ctx);
			/* z3 = z1 z2 l3  */
			ec_mulm(z3, z1, z2, ctx);
			ec_mulm(z3, z3, l3, ctx);
			/* x3 = l6^2 - l7 l3^2  */
			ec_घात2(t1, l6, ctx);
			ec_घात2(t2, l3, ctx);
			ec_mulm(t2, t2, l7, ctx);
			ec_subm(x3, t1, t2, ctx);
			/* l9 = l7 l3^2 - 2 x3  */
			ec_mul2(t1, x3, ctx);
			ec_subm(l9, t2, t1, ctx);
			/* y3 = (l9 l6 - l8 l3^3)/2  */
			ec_mulm(l9, l9, l6, ctx);
			ec_घातm(t1, l3, mpi_स्थिर(MPI_C_THREE), ctx); /* fixme: Use saved value*/
			ec_mulm(t1, t1, l8, ctx);
			ec_subm(y3, l9, t1, ctx);
			ec_mulm(y3, y3, ec_get_two_inv_p(ctx), ctx);
		पूर्ण
	पूर्ण

#अघोषित x1
#अघोषित y1
#अघोषित z1
#अघोषित x2
#अघोषित y2
#अघोषित z2
#अघोषित x3
#अघोषित y3
#अघोषित z3
#अघोषित l1
#अघोषित l2
#अघोषित l3
#अघोषित l4
#अघोषित l5
#अघोषित l6
#अघोषित l7
#अघोषित l8
#अघोषित l9
#अघोषित t1
#अघोषित t2
पूर्ण

/* RESULT = P1 + P2  (Montgomery version).*/
अटल व्योम add_poपूर्णांकs_montgomery(MPI_POINT result,
		MPI_POINT p1, MPI_POINT p2,
		काष्ठा mpi_ec_ctx *ctx)
अणु
	(व्योम)result;
	(व्योम)p1;
	(व्योम)p2;
	(व्योम)ctx;
	log_fatal("%s: %s not yet supported\n",
			"mpi_ec_add_points", "Montgomery");
पूर्ण

/* RESULT = P1 + P2  (Twisted Edwards version).*/
अटल व्योम add_poपूर्णांकs_edwards(MPI_POINT result,
		MPI_POINT p1, MPI_POINT p2,
		काष्ठा mpi_ec_ctx *ctx)
अणु
#घोषणा X1 (p1->x)
#घोषणा Y1 (p1->y)
#घोषणा Z1 (p1->z)
#घोषणा X2 (p2->x)
#घोषणा Y2 (p2->y)
#घोषणा Z2 (p2->z)
#घोषणा X3 (result->x)
#घोषणा Y3 (result->y)
#घोषणा Z3 (result->z)
#घोषणा A (ctx->t.scratch[0])
#घोषणा B (ctx->t.scratch[1])
#घोषणा C (ctx->t.scratch[2])
#घोषणा D (ctx->t.scratch[3])
#घोषणा E (ctx->t.scratch[4])
#घोषणा F (ctx->t.scratch[5])
#घोषणा G (ctx->t.scratch[6])
#घोषणा पंचांगp (ctx->t.scratch[7])

	poपूर्णांक_resize(result, ctx);

	/* Compute: (X_3 : Y_3 : Z_3) = (X_1 : Y_1 : Z_1) + (X_2 : Y_2 : Z_3) */

	/* A = Z1 तङ Z2 */
	ctx->mulm(A, Z1, Z2, ctx);

	/* B = A^2 */
	ctx->घात2(B, A, ctx);

	/* C = X1 तङ X2 */
	ctx->mulm(C, X1, X2, ctx);

	/* D = Y1 तङ Y2 */
	ctx->mulm(D, Y1, Y2, ctx);

	/* E = d तङ C तङ D */
	ctx->mulm(E, ctx->b, C, ctx);
	ctx->mulm(E, E, D, ctx);

	/* F = B - E */
	ctx->subm(F, B, E, ctx);

	/* G = B + E */
	ctx->addm(G, B, E, ctx);

	/* X_3 = A तङ F तङ ((X_1 + Y_1) तङ (X_2 + Y_2) - C - D) */
	ctx->addm(पंचांगp, X1, Y1, ctx);
	ctx->addm(X3, X2, Y2, ctx);
	ctx->mulm(X3, X3, पंचांगp, ctx);
	ctx->subm(X3, X3, C, ctx);
	ctx->subm(X3, X3, D, ctx);
	ctx->mulm(X3, X3, F, ctx);
	ctx->mulm(X3, X3, A, ctx);

	/* Y_3 = A तङ G तङ (D - aC) */
	अगर (ctx->dialect == ECC_DIALECT_ED25519) अणु
		ctx->addm(Y3, D, C, ctx);
	पूर्ण अन्यथा अणु
		ctx->mulm(Y3, ctx->a, C, ctx);
		ctx->subm(Y3, D, Y3, ctx);
	पूर्ण
	ctx->mulm(Y3, Y3, G, ctx);
	ctx->mulm(Y3, Y3, A, ctx);

	/* Z_3 = F तङ G */
	ctx->mulm(Z3, F, G, ctx);


#अघोषित X1
#अघोषित Y1
#अघोषित Z1
#अघोषित X2
#अघोषित Y2
#अघोषित Z2
#अघोषित X3
#अघोषित Y3
#अघोषित Z3
#अघोषित A
#अघोषित B
#अघोषित C
#अघोषित D
#अघोषित E
#अघोषित F
#अघोषित G
#अघोषित पंचांगp
पूर्ण

/* Compute a step of Montgomery Ladder (only use X and Z in the poपूर्णांक).
 * Inमाला_दो:  P1, P2, and x-coordinate of DIF = P1 - P1.
 * Outमाला_दो: PRD = 2 * P1 and  SUM = P1 + P2.
 */
अटल व्योम montgomery_ladder(MPI_POINT prd, MPI_POINT sum,
		MPI_POINT p1, MPI_POINT p2, MPI dअगर_x,
		काष्ठा mpi_ec_ctx *ctx)
अणु
	ctx->addm(sum->x, p2->x, p2->z, ctx);
	ctx->subm(p2->z, p2->x, p2->z, ctx);
	ctx->addm(prd->x, p1->x, p1->z, ctx);
	ctx->subm(p1->z, p1->x, p1->z, ctx);
	ctx->mulm(p2->x, p1->z, sum->x, ctx);
	ctx->mulm(p2->z, prd->x, p2->z, ctx);
	ctx->घात2(p1->x, prd->x, ctx);
	ctx->घात2(p1->z, p1->z, ctx);
	ctx->addm(sum->x, p2->x, p2->z, ctx);
	ctx->subm(p2->z, p2->x, p2->z, ctx);
	ctx->mulm(prd->x, p1->x, p1->z, ctx);
	ctx->subm(p1->z, p1->x, p1->z, ctx);
	ctx->घात2(sum->x, sum->x, ctx);
	ctx->घात2(sum->z, p2->z, ctx);
	ctx->mulm(prd->z, p1->z, ctx->a, ctx); /* CTX->A: (a-2)/4 */
	ctx->mulm(sum->z, sum->z, dअगर_x, ctx);
	ctx->addm(prd->z, p1->x, prd->z, ctx);
	ctx->mulm(prd->z, prd->z, p1->z, ctx);
पूर्ण

/* RESULT = P1 + P2 */
व्योम mpi_ec_add_poपूर्णांकs(MPI_POINT result,
		MPI_POINT p1, MPI_POINT p2,
		काष्ठा mpi_ec_ctx *ctx)
अणु
	चयन (ctx->model) अणु
	हाल MPI_EC_WEIERSTRASS:
		add_poपूर्णांकs_weierstrass(result, p1, p2, ctx);
		अवरोध;
	हाल MPI_EC_MONTGOMERY:
		add_poपूर्णांकs_montgomery(result, p1, p2, ctx);
		अवरोध;
	हाल MPI_EC_EDWARDS:
		add_poपूर्णांकs_edwards(result, p1, p2, ctx);
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mpi_ec_add_poपूर्णांकs);

/* Scalar poपूर्णांक multiplication - the मुख्य function क्रम ECC.  If takes
 * an पूर्णांकeger SCALAR and a POINT as well as the usual context CTX.
 * RESULT will be set to the resulting poपूर्णांक.
 */
व्योम mpi_ec_mul_poपूर्णांक(MPI_POINT result,
			MPI scalar, MPI_POINT poपूर्णांक,
			काष्ठा mpi_ec_ctx *ctx)
अणु
	MPI x1, y1, z1, k, h, yy;
	अचिन्हित पूर्णांक i, loops;
	काष्ठा gcry_mpi_poपूर्णांक p1, p2, p1inv;

	अगर (ctx->model == MPI_EC_EDWARDS) अणु
		/* Simple left to right binary method.  Algorithm 3.27 from
		 * अणुauthor=अणुHankerson, Darrel and Menezes, Alfred J. and Vanstone, Scottपूर्ण,
		 *  title = अणुGuide to Elliptic Curve Cryptographyपूर्ण,
		 *  year = अणु2003पूर्ण, isbn = अणु038795273Xपूर्ण,
		 *  url = अणुhttp://www.cacr.math.uwaterloo.ca/ecc/पूर्ण,
		 *  publisher = अणुSpringer-Verlag New York, Inc.पूर्णपूर्ण
		 */
		अचिन्हित पूर्णांक nbits;
		पूर्णांक j;

		अगर (mpi_cmp(scalar, ctx->p) >= 0)
			nbits = mpi_get_nbits(scalar);
		अन्यथा
			nbits = mpi_get_nbits(ctx->p);

		mpi_set_ui(result->x, 0);
		mpi_set_ui(result->y, 1);
		mpi_set_ui(result->z, 1);
		poपूर्णांक_resize(poपूर्णांक, ctx);

		poपूर्णांक_resize(result, ctx);
		poपूर्णांक_resize(poपूर्णांक, ctx);

		क्रम (j = nbits-1; j >= 0; j--) अणु
			mpi_ec_dup_poपूर्णांक(result, result, ctx);
			अगर (mpi_test_bit(scalar, j))
				mpi_ec_add_poपूर्णांकs(result, result, poपूर्णांक, ctx);
		पूर्ण
		वापस;
	पूर्ण अन्यथा अगर (ctx->model == MPI_EC_MONTGOMERY) अणु
		अचिन्हित पूर्णांक nbits;
		पूर्णांक j;
		काष्ठा gcry_mpi_poपूर्णांक p1_, p2_;
		MPI_POINT q1, q2, prd, sum;
		अचिन्हित दीर्घ sw;
		mpi_माप_प्रकार rsize;

		/* Compute scalar poपूर्णांक multiplication with Montgomery Ladder.
		 * Note that we करोn't use Y-coordinate in the poपूर्णांकs at all.
		 * RESULT->Y will be filled by zero.
		 */

		nbits = mpi_get_nbits(scalar);
		poपूर्णांक_init(&p1);
		poपूर्णांक_init(&p2);
		poपूर्णांक_init(&p1_);
		poपूर्णांक_init(&p2_);
		mpi_set_ui(p1.x, 1);
		mpi_मुक्त(p2.x);
		p2.x = mpi_copy(poपूर्णांक->x);
		mpi_set_ui(p2.z, 1);

		poपूर्णांक_resize(&p1, ctx);
		poपूर्णांक_resize(&p2, ctx);
		poपूर्णांक_resize(&p1_, ctx);
		poपूर्णांक_resize(&p2_, ctx);

		mpi_resize(poपूर्णांक->x, ctx->p->nlimbs);
		poपूर्णांक->x->nlimbs = ctx->p->nlimbs;

		q1 = &p1;
		q2 = &p2;
		prd = &p1_;
		sum = &p2_;

		क्रम (j = nbits-1; j >= 0; j--) अणु
			MPI_POINT t;

			sw = mpi_test_bit(scalar, j);
			poपूर्णांक_swap_cond(q1, q2, sw, ctx);
			montgomery_ladder(prd, sum, q1, q2, poपूर्णांक->x, ctx);
			poपूर्णांक_swap_cond(prd, sum, sw, ctx);
			t = q1;  q1 = prd;  prd = t;
			t = q2;  q2 = sum;  sum = t;
		पूर्ण

		mpi_clear(result->y);
		sw = (nbits & 1);
		poपूर्णांक_swap_cond(&p1, &p1_, sw, ctx);

		rsize = p1.z->nlimbs;
		MPN_NORMALIZE(p1.z->d, rsize);
		अगर (rsize == 0) अणु
			mpi_set_ui(result->x, 1);
			mpi_set_ui(result->z, 0);
		पूर्ण अन्यथा अणु
			z1 = mpi_new(0);
			ec_invm(z1, p1.z, ctx);
			ec_mulm(result->x, p1.x, z1, ctx);
			mpi_set_ui(result->z, 1);
			mpi_मुक्त(z1);
		पूर्ण

		poपूर्णांक_मुक्त(&p1);
		poपूर्णांक_मुक्त(&p2);
		poपूर्णांक_मुक्त(&p1_);
		poपूर्णांक_मुक्त(&p2_);
		वापस;
	पूर्ण

	x1 = mpi_alloc_like(ctx->p);
	y1 = mpi_alloc_like(ctx->p);
	h  = mpi_alloc_like(ctx->p);
	k  = mpi_copy(scalar);
	yy = mpi_copy(poपूर्णांक->y);

	अगर (mpi_has_sign(k)) अणु
		k->sign = 0;
		ec_invm(yy, yy, ctx);
	पूर्ण

	अगर (!mpi_cmp_ui(poपूर्णांक->z, 1)) अणु
		mpi_set(x1, poपूर्णांक->x);
		mpi_set(y1, yy);
	पूर्ण अन्यथा अणु
		MPI z2, z3;

		z2 = mpi_alloc_like(ctx->p);
		z3 = mpi_alloc_like(ctx->p);
		ec_mulm(z2, poपूर्णांक->z, poपूर्णांक->z, ctx);
		ec_mulm(z3, poपूर्णांक->z, z2, ctx);
		ec_invm(z2, z2, ctx);
		ec_mulm(x1, poपूर्णांक->x, z2, ctx);
		ec_invm(z3, z3, ctx);
		ec_mulm(y1, yy, z3, ctx);
		mpi_मुक्त(z2);
		mpi_मुक्त(z3);
	पूर्ण
	z1 = mpi_copy(mpi_स्थिर(MPI_C_ONE));

	mpi_mul(h, k, mpi_स्थिर(MPI_C_THREE)); /* h = 3k */
	loops = mpi_get_nbits(h);
	अगर (loops < 2) अणु
		/* If SCALAR is zero, the above mpi_mul sets H to zero and thus
		 * LOOPs will be zero.  To aव्योम an underflow of I in the मुख्य
		 * loop we set LOOP to 2 and the result to (0,0,0).
		 */
		loops = 2;
		mpi_clear(result->x);
		mpi_clear(result->y);
		mpi_clear(result->z);
	पूर्ण अन्यथा अणु
		mpi_set(result->x, poपूर्णांक->x);
		mpi_set(result->y, yy);
		mpi_set(result->z, poपूर्णांक->z);
	पूर्ण
	mpi_मुक्त(yy); yy = शून्य;

	p1.x = x1; x1 = शून्य;
	p1.y = y1; y1 = शून्य;
	p1.z = z1; z1 = शून्य;
	poपूर्णांक_init(&p2);
	poपूर्णांक_init(&p1inv);

	/* Invert poपूर्णांक: y = p - y mod p  */
	poपूर्णांक_set(&p1inv, &p1);
	ec_subm(p1inv.y, ctx->p, p1inv.y, ctx);

	क्रम (i = loops-2; i > 0; i--) अणु
		mpi_ec_dup_poपूर्णांक(result, result, ctx);
		अगर (mpi_test_bit(h, i) == 1 && mpi_test_bit(k, i) == 0) अणु
			poपूर्णांक_set(&p2, result);
			mpi_ec_add_poपूर्णांकs(result, &p2, &p1, ctx);
		पूर्ण
		अगर (mpi_test_bit(h, i) == 0 && mpi_test_bit(k, i) == 1) अणु
			poपूर्णांक_set(&p2, result);
			mpi_ec_add_poपूर्णांकs(result, &p2, &p1inv, ctx);
		पूर्ण
	पूर्ण

	poपूर्णांक_मुक्त(&p1);
	poपूर्णांक_मुक्त(&p2);
	poपूर्णांक_मुक्त(&p1inv);
	mpi_मुक्त(h);
	mpi_मुक्त(k);
पूर्ण
EXPORT_SYMBOL_GPL(mpi_ec_mul_poपूर्णांक);

/* Return true अगर POINT is on the curve described by CTX.  */
पूर्णांक mpi_ec_curve_poपूर्णांक(MPI_POINT poपूर्णांक, काष्ठा mpi_ec_ctx *ctx)
अणु
	पूर्णांक res = 0;
	MPI x, y, w;

	x = mpi_new(0);
	y = mpi_new(0);
	w = mpi_new(0);

	/* Check that the poपूर्णांक is in range.  This needs to be करोne here and
	 * not after conversion to affine coordinates.
	 */
	अगर (mpi_cmpअसल(poपूर्णांक->x, ctx->p) >= 0)
		जाओ leave;
	अगर (mpi_cmpअसल(poपूर्णांक->y, ctx->p) >= 0)
		जाओ leave;
	अगर (mpi_cmpअसल(poपूर्णांक->z, ctx->p) >= 0)
		जाओ leave;

	चयन (ctx->model) अणु
	हाल MPI_EC_WEIERSTRASS:
		अणु
			MPI xxx;

			अगर (mpi_ec_get_affine(x, y, poपूर्णांक, ctx))
				जाओ leave;

			xxx = mpi_new(0);

			/* y^2 == x^3 + aतङx + b */
			ec_घात2(y, y, ctx);

			ec_घात3(xxx, x, ctx);
			ec_mulm(w, ctx->a, x, ctx);
			ec_addm(w, w, ctx->b, ctx);
			ec_addm(w, w, xxx, ctx);

			अगर (!mpi_cmp(y, w))
				res = 1;

			mpi_मुक्त(xxx);
		पूर्ण
		अवरोध;

	हाल MPI_EC_MONTGOMERY:
		अणु
#घोषणा xx y
			/* With Montgomery curve, only X-coordinate is valid. */
			अगर (mpi_ec_get_affine(x, शून्य, poपूर्णांक, ctx))
				जाओ leave;

			/* The equation is: b * y^2 == x^3 + a तङ x^2 + x */
			/* We check अगर right hand is quadratic residue or not by
			 * Euler's criterion.
			 */
			/* CTX->A has (a-2)/4 and CTX->B has b^-1 */
			ec_mulm(w, ctx->a, mpi_स्थिर(MPI_C_FOUR), ctx);
			ec_addm(w, w, mpi_स्थिर(MPI_C_TWO), ctx);
			ec_mulm(w, w, x, ctx);
			ec_घात2(xx, x, ctx);
			ec_addm(w, w, xx, ctx);
			ec_addm(w, w, mpi_स्थिर(MPI_C_ONE), ctx);
			ec_mulm(w, w, x, ctx);
			ec_mulm(w, w, ctx->b, ctx);
#अघोषित xx
			/* Compute Euler's criterion: w^(p-1)/2 */
#घोषणा p_minus1 y
			ec_subm(p_minus1, ctx->p, mpi_स्थिर(MPI_C_ONE), ctx);
			mpi_rshअगरt(p_minus1, p_minus1, 1);
			ec_घातm(w, w, p_minus1, ctx);

			res = !mpi_cmp_ui(w, 1);
#अघोषित p_minus1
		पूर्ण
		अवरोध;

	हाल MPI_EC_EDWARDS:
		अणु
			अगर (mpi_ec_get_affine(x, y, poपूर्णांक, ctx))
				जाओ leave;

			mpi_resize(w, ctx->p->nlimbs);
			w->nlimbs = ctx->p->nlimbs;

			/* a तङ x^2 + y^2 - 1 - b तङ x^2 तङ y^2 == 0 */
			ctx->घात2(x, x, ctx);
			ctx->घात2(y, y, ctx);
			अगर (ctx->dialect == ECC_DIALECT_ED25519)
				ctx->subm(w, ctx->p, x, ctx);
			अन्यथा
				ctx->mulm(w, ctx->a, x, ctx);
			ctx->addm(w, w, y, ctx);
			ctx->mulm(x, x, y, ctx);
			ctx->mulm(x, x, ctx->b, ctx);
			ctx->subm(w, w, x, ctx);
			अगर (!mpi_cmp_ui(w, 1))
				res = 1;
		पूर्ण
		अवरोध;
	पूर्ण

leave:
	mpi_मुक्त(w);
	mpi_मुक्त(x);
	mpi_मुक्त(y);

	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(mpi_ec_curve_poपूर्णांक);
