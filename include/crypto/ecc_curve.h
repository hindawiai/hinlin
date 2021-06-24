<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2021 HiSilicon */

#अगर_अघोषित _CRYTO_ECC_CURVE_H
#घोषणा _CRYTO_ECC_CURVE_H

#समावेश <linux/types.h>

/**
 * काष्ठा ecc_poपूर्णांक - elliptic curve poपूर्णांक in affine coordinates
 *
 * @x:		X coordinate in vli क्रमm.
 * @y:		Y coordinate in vli क्रमm.
 * @ndigits:	Length of vlis in u64 qwords.
 */
काष्ठा ecc_poपूर्णांक अणु
	u64 *x;
	u64 *y;
	u8 ndigits;
पूर्ण;

/**
 * काष्ठा ecc_curve - definition of elliptic curve
 *
 * @name:	Short name of the curve.
 * @g:		Generator poपूर्णांक of the curve.
 * @p:		Prime number, अगर Barrett's reduction is used क्रम this curve
 *		pre-calculated value 'mu' is appended to the @p after ndigits.
 *		Use of Barrett's reduction is heuristically determined in
 *		vli_mmod_fast().
 * @n:		Order of the curve group.
 * @a:		Curve parameter a.
 * @b:		Curve parameter b.
 */
काष्ठा ecc_curve अणु
	अक्षर *name;
	काष्ठा ecc_poपूर्णांक g;
	u64 *p;
	u64 *n;
	u64 *a;
	u64 *b;
पूर्ण;

/**
 * ecc_get_curve() - get elliptic curve;
 * @curve_id:           Curves IDs:
 *                      defined in 'include/crypto/ecdh.h';
 *
 * Returns curve अगर get curve succssful, शून्य otherwise
 */
स्थिर काष्ठा ecc_curve *ecc_get_curve(अचिन्हित पूर्णांक curve_id);

/**
 * ecc_get_curve25519() - get curve25519 curve;
 *
 * Returns curve25519
 */
स्थिर काष्ठा ecc_curve *ecc_get_curve25519(व्योम);

#पूर्ण_अगर
