<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* mpi.h  -  Multi Precision Integers
 *	Copyright (C) 1994, 1996, 1998, 1999,
 *                    2000, 2001 Free Software Foundation, Inc.
 *
 * This file is part of GNUPG.
 *
 * Note: This code is heavily based on the GNU MP Library.
 *	 Actually it's the same code with only minor changes in the
 *	 way the data is stored; this is to support the असलtraction
 *	 of an optional secure memory allocation which may be used
 *	 to aव्योम revealing of sensitive data due to paging etc.
 *	 The GNU MP Library itself is published under the LGPL;
 *	 however I decided to publish this code under the plain GPL.
 */

#अगर_अघोषित G10_MPI_H
#घोषणा G10_MPI_H

#समावेश <linux/types.h>
#समावेश <linux/scatterlist.h>

#घोषणा BYTES_PER_MPI_LIMB	(BITS_PER_LONG / 8)
#घोषणा BITS_PER_MPI_LIMB	BITS_PER_LONG

प्रकार अचिन्हित दीर्घ पूर्णांक mpi_limb_t;
प्रकार चिन्हित दीर्घ पूर्णांक mpi_limb_चिन्हित_t;

काष्ठा gcry_mpi अणु
	पूर्णांक alloced;		/* array size (# of allocated limbs) */
	पूर्णांक nlimbs;		/* number of valid limbs */
	पूर्णांक nbits;		/* the real number of valid bits (info only) */
	पूर्णांक sign;		/* indicates a negative number */
	अचिन्हित flags;		/* bit 0: array must be allocated in secure memory space */
	/* bit 1: not used */
	/* bit 2: the limb is a poपूर्णांकer to some m_alloced data */
	mpi_limb_t *d;		/* array with the limbs */
पूर्ण;

प्रकार काष्ठा gcry_mpi *MPI;

#घोषणा mpi_get_nlimbs(a)     ((a)->nlimbs)
#घोषणा mpi_has_sign(a)       ((a)->sign)

/*-- mpiutil.c --*/
MPI mpi_alloc(अचिन्हित nlimbs);
व्योम mpi_clear(MPI a);
व्योम mpi_मुक्त(MPI a);
पूर्णांक mpi_resize(MPI a, अचिन्हित nlimbs);

अटल अंतरभूत MPI mpi_new(अचिन्हित पूर्णांक nbits)
अणु
	वापस mpi_alloc((nbits + BITS_PER_MPI_LIMB - 1) / BITS_PER_MPI_LIMB);
पूर्ण

MPI mpi_copy(MPI a);
MPI mpi_alloc_like(MPI a);
व्योम mpi_snatch(MPI w, MPI u);
MPI mpi_set(MPI w, MPI u);
MPI mpi_set_ui(MPI w, अचिन्हित दीर्घ u);
MPI mpi_alloc_set_ui(अचिन्हित दीर्घ u);
व्योम mpi_swap_cond(MPI a, MPI b, अचिन्हित दीर्घ swap);

/* Constants used to वापस स्थिरant MPIs.  See mpi_init अगर you
 * want to add more स्थिरants.
 */
#घोषणा MPI_NUMBER_OF_CONSTANTS 6
क्रमागत gcry_mpi_स्थिरants अणु
	MPI_C_ZERO,
	MPI_C_ONE,
	MPI_C_TWO,
	MPI_C_THREE,
	MPI_C_FOUR,
	MPI_C_EIGHT
पूर्ण;

MPI mpi_स्थिर(क्रमागत gcry_mpi_स्थिरants no);

/*-- mpicoder.c --*/

/* Dअगरferent क्रमmats of बाह्यal big पूर्णांकeger representation. */
क्रमागत gcry_mpi_क्रमmat अणु
	GCRYMPI_FMT_NONE = 0,
	GCRYMPI_FMT_STD = 1,    /* Twos complement stored without length. */
	GCRYMPI_FMT_PGP = 2,    /* As used by OpenPGP (अचिन्हित only). */
	GCRYMPI_FMT_SSH = 3,    /* As used by SSH (like STD but with length). */
	GCRYMPI_FMT_HEX = 4,    /* Hex क्रमmat. */
	GCRYMPI_FMT_USG = 5,    /* Like STD but अचिन्हित. */
	GCRYMPI_FMT_OPAQUE = 8  /* Opaque क्रमmat (some functions only). */
पूर्ण;

MPI mpi_पढ़ो_raw_data(स्थिर व्योम *xbuffer, माप_प्रकार nbytes);
MPI mpi_पढ़ो_from_buffer(स्थिर व्योम *buffer, अचिन्हित *ret_nपढ़ो);
पूर्णांक mpi_fromstr(MPI val, स्थिर अक्षर *str);
MPI mpi_scanval(स्थिर अक्षर *string);
MPI mpi_पढ़ो_raw_from_sgl(काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक len);
व्योम *mpi_get_buffer(MPI a, अचिन्हित *nbytes, पूर्णांक *sign);
पूर्णांक mpi_पढ़ो_buffer(MPI a, uपूर्णांक8_t *buf, अचिन्हित buf_len, अचिन्हित *nbytes,
		    पूर्णांक *sign);
पूर्णांक mpi_ग_लिखो_to_sgl(MPI a, काष्ठा scatterlist *sg, अचिन्हित nbytes,
		     पूर्णांक *sign);
पूर्णांक mpi_prपूर्णांक(क्रमागत gcry_mpi_क्रमmat क्रमmat, अचिन्हित अक्षर *buffer,
			माप_प्रकार buflen, माप_प्रकार *nwritten, MPI a);

/*-- mpi-mod.c --*/
व्योम mpi_mod(MPI rem, MPI भागidend, MPI भागisor);

/* Context used with Barrett reduction.  */
काष्ठा barrett_ctx_s;
प्रकार काष्ठा barrett_ctx_s *mpi_barrett_t;

mpi_barrett_t mpi_barrett_init(MPI m, पूर्णांक copy);
व्योम mpi_barrett_मुक्त(mpi_barrett_t ctx);
व्योम mpi_mod_barrett(MPI r, MPI x, mpi_barrett_t ctx);
व्योम mpi_mul_barrett(MPI w, MPI u, MPI v, mpi_barrett_t ctx);

/*-- mpi-घात.c --*/
पूर्णांक mpi_घातm(MPI res, MPI base, MPI exp, MPI mod);

/*-- mpi-cmp.c --*/
पूर्णांक mpi_cmp_ui(MPI u, uदीर्घ v);
पूर्णांक mpi_cmp(MPI u, MPI v);
पूर्णांक mpi_cmpअसल(MPI u, MPI v);

/*-- mpi-sub-ui.c --*/
पूर्णांक mpi_sub_ui(MPI w, MPI u, अचिन्हित दीर्घ vval);

/*-- mpi-bit.c --*/
व्योम mpi_normalize(MPI a);
अचिन्हित mpi_get_nbits(MPI a);
पूर्णांक mpi_test_bit(MPI a, अचिन्हित पूर्णांक n);
व्योम mpi_set_bit(MPI a, अचिन्हित पूर्णांक n);
व्योम mpi_set_highbit(MPI a, अचिन्हित पूर्णांक n);
व्योम mpi_clear_highbit(MPI a, अचिन्हित पूर्णांक n);
व्योम mpi_clear_bit(MPI a, अचिन्हित पूर्णांक n);
व्योम mpi_rshअगरt_limbs(MPI a, अचिन्हित पूर्णांक count);
व्योम mpi_rshअगरt(MPI x, MPI a, अचिन्हित पूर्णांक n);
व्योम mpi_lshअगरt_limbs(MPI a, अचिन्हित पूर्णांक count);
व्योम mpi_lshअगरt(MPI x, MPI a, अचिन्हित पूर्णांक n);

/*-- mpi-add.c --*/
व्योम mpi_add_ui(MPI w, MPI u, अचिन्हित दीर्घ v);
व्योम mpi_add(MPI w, MPI u, MPI v);
व्योम mpi_sub(MPI w, MPI u, MPI v);
व्योम mpi_addm(MPI w, MPI u, MPI v, MPI m);
व्योम mpi_subm(MPI w, MPI u, MPI v, MPI m);

/*-- mpi-mul.c --*/
व्योम mpi_mul(MPI w, MPI u, MPI v);
व्योम mpi_mulm(MPI w, MPI u, MPI v, MPI m);

/*-- mpi-भाग.c --*/
व्योम mpi_tभाग_r(MPI rem, MPI num, MPI den);
व्योम mpi_fभाग_r(MPI rem, MPI भागidend, MPI भागisor);
व्योम mpi_fभाग_q(MPI quot, MPI भागidend, MPI भागisor);

/*-- mpi-inv.c --*/
पूर्णांक mpi_invm(MPI x, MPI a, MPI n);

/*-- ec.c --*/

/* Object to represent a poपूर्णांक in projective coordinates */
काष्ठा gcry_mpi_poपूर्णांक अणु
	MPI x;
	MPI y;
	MPI z;
पूर्ण;

प्रकार काष्ठा gcry_mpi_poपूर्णांक *MPI_POINT;

/* Models describing an elliptic curve */
क्रमागत gcry_mpi_ec_models अणु
	/* The Short Weierstrass equation is
	 *      y^2 = x^3 + ax + b
	 */
	MPI_EC_WEIERSTRASS = 0,
	/* The Montgomery equation is
	 *      by^2 = x^3 + ax^2 + x
	 */
	MPI_EC_MONTGOMERY,
	/* The Twisted Edwards equation is
	 *      ax^2 + y^2 = 1 + bx^2y^2
	 * Note that we use 'b' instead of the commonly used 'd'.
	 */
	MPI_EC_EDWARDS
पूर्ण;

/* Dialects used with elliptic curves */
क्रमागत ecc_dialects अणु
	ECC_DIALECT_STANDARD = 0,
	ECC_DIALECT_ED25519,
	ECC_DIALECT_SAFECURVE
पूर्ण;

/* This context is used with all our EC functions. */
काष्ठा mpi_ec_ctx अणु
	क्रमागत gcry_mpi_ec_models model; /* The model describing this curve. */
	क्रमागत ecc_dialects dialect;     /* The ECC dialect used with the curve. */
	पूर्णांक flags;                     /* Public key flags (not always used). */
	अचिन्हित पूर्णांक nbits;            /* Number of bits.  */

	/* Doमुख्य parameters.  Note that they may not all be set and अगर set
	 * the MPIs may be flaged as स्थिरant.
	 */
	MPI p;         /* Prime specअगरying the field GF(p).  */
	MPI a;         /* First coefficient of the Weierstrass equation.  */
	MPI b;         /* Second coefficient of the Weierstrass equation.  */
	MPI_POINT G;   /* Base poपूर्णांक (generator).  */
	MPI n;         /* Order of G.  */
	अचिन्हित पूर्णांक h;       /* Cofactor.  */

	/* The actual key.  May not be set.  */
	MPI_POINT Q;   /* Public key.   */
	MPI d;         /* Private key.  */

	स्थिर अक्षर *name;      /* Name of the curve.  */

	/* This काष्ठाure is निजी to mpi/ec.c! */
	काष्ठा अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक a_is_pminus3:1;
			अचिन्हित पूर्णांक two_inv_p:1;
		पूर्ण valid; /* Flags to help setting the helper vars below.  */

		पूर्णांक a_is_pminus3;  /* True अगर A = P - 3. */

		MPI two_inv_p;

		mpi_barrett_t p_barrett;

		/* Scratch variables.  */
		MPI scratch[11];

		/* Helper क्रम fast reduction.  */
		/*   पूर्णांक nist_nbits; /\* If this is a NIST curve, the # of bits. *\/ */
		/*   MPI s[10]; */
		/*   MPI c; */
	पूर्ण t;

	/* Curve specअगरic computation routines क्रम the field.  */
	व्योम (*addm)(MPI w, MPI u, MPI v, काष्ठा mpi_ec_ctx *ctx);
	व्योम (*subm)(MPI w, MPI u, MPI v, काष्ठा mpi_ec_ctx *ec);
	व्योम (*mulm)(MPI w, MPI u, MPI v, काष्ठा mpi_ec_ctx *ctx);
	व्योम (*घात2)(MPI w, स्थिर MPI b, काष्ठा mpi_ec_ctx *ctx);
	व्योम (*mul2)(MPI w, MPI u, काष्ठा mpi_ec_ctx *ctx);
पूर्ण;

व्योम mpi_ec_init(काष्ठा mpi_ec_ctx *ctx, क्रमागत gcry_mpi_ec_models model,
			क्रमागत ecc_dialects dialect,
			पूर्णांक flags, MPI p, MPI a, MPI b);
व्योम mpi_ec_deinit(काष्ठा mpi_ec_ctx *ctx);
MPI_POINT mpi_poपूर्णांक_new(अचिन्हित पूर्णांक nbits);
व्योम mpi_poपूर्णांक_release(MPI_POINT p);
व्योम mpi_poपूर्णांक_init(MPI_POINT p);
व्योम mpi_poपूर्णांक_मुक्त_parts(MPI_POINT p);
पूर्णांक mpi_ec_get_affine(MPI x, MPI y, MPI_POINT poपूर्णांक, काष्ठा mpi_ec_ctx *ctx);
व्योम mpi_ec_add_poपूर्णांकs(MPI_POINT result,
			MPI_POINT p1, MPI_POINT p2,
			काष्ठा mpi_ec_ctx *ctx);
व्योम mpi_ec_mul_poपूर्णांक(MPI_POINT result,
			MPI scalar, MPI_POINT poपूर्णांक,
			काष्ठा mpi_ec_ctx *ctx);
पूर्णांक mpi_ec_curve_poपूर्णांक(MPI_POINT poपूर्णांक, काष्ठा mpi_ec_ctx *ctx);

/* अंतरभूत functions */

/**
 * mpi_get_size() - वापसs max size required to store the number
 *
 * @a:	A multi precision पूर्णांकeger क्रम which we want to allocate a bufer
 *
 * Return: size required to store the number
 */
अटल अंतरभूत अचिन्हित पूर्णांक mpi_get_size(MPI a)
अणु
	वापस a->nlimbs * BYTES_PER_MPI_LIMB;
पूर्ण
#पूर्ण_अगर /*G10_MPI_H */
