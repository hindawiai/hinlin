<शैली गुरु>
/*
 * Copyright (c) 2011 Broadcom Corporation
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#अगर_अघोषित __CORDIC_H_
#घोषणा __CORDIC_H_

#समावेश <linux/types.h>

#घोषणा CORDIC_ANGLE_GEN	39797
#घोषणा CORDIC_PRECISION_SHIFT	16
#घोषणा CORDIC_NUM_ITER	(CORDIC_PRECISION_SHIFT + 2)

#घोषणा CORDIC_FIXED(X)	((s32)((X) << CORDIC_PRECISION_SHIFT))
#घोषणा CORDIC_FLOAT(X)	(((X) >= 0) \
		? ((((X) >> (CORDIC_PRECISION_SHIFT - 1)) + 1) >> 1) \
		: -((((-(X)) >> (CORDIC_PRECISION_SHIFT - 1)) + 1) >> 1))

/**
 * काष्ठा cordic_iq - i/q coordinate.
 *
 * @i: real part of coordinate (in phase).
 * @q: imaginary part of coordinate (quadrature).
 */
काष्ठा cordic_iq अणु
	s32 i;
	s32 q;
पूर्ण;

/**
 * cordic_calc_iq() - calculates the i/q coordinate क्रम given angle.
 *
 * @theta: angle in degrees क्रम which i/q coordinate is to be calculated.
 * @coord: function output parameter holding the i/q coordinate.
 *
 * The function calculates the i/q coordinate क्रम a given angle using the
 * CORDIC algorithm. The coordinate consists of a real (i) and an
 * imaginary (q) part. The real part is essentially the cosine of the
 * angle and the imaginary part is the sine of the angle. The वापसed
 * values are scaled by 2^16 क्रम precision. The range क्रम theta is
 * क्रम -180 degrees to +180 degrees. Passed values outside this range are
 * converted beक्रमe करोing the actual calculation.
 */
काष्ठा cordic_iq cordic_calc_iq(s32 theta);

#पूर्ण_अगर /* __CORDIC_H_ */
