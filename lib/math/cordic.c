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
#समावेश <linux/module.h>
#समावेश <linux/cordic.h>

अटल स्थिर s32 arctan_table[] = अणु
	2949120,
	1740967,
	919879,
	466945,
	234379,
	117304,
	58666,
	29335,
	14668,
	7334,
	3667,
	1833,
	917,
	458,
	229,
	115,
	57,
	29
पूर्ण;

/*
 * cordic_calc_iq() - calculates the i/q coordinate क्रम given angle
 *
 * theta: angle in degrees क्रम which i/q coordinate is to be calculated
 * coord: function output parameter holding the i/q coordinate
 */
काष्ठा cordic_iq cordic_calc_iq(s32 theta)
अणु
	काष्ठा cordic_iq coord;
	s32 angle, valपंचांगp;
	अचिन्हित iter;
	पूर्णांक signx = 1;
	पूर्णांक signtheta;

	coord.i = CORDIC_ANGLE_GEN;
	coord.q = 0;
	angle = 0;

	theta = CORDIC_FIXED(theta);
	signtheta = (theta < 0) ? -1 : 1;
	theta = ((theta + CORDIC_FIXED(180) * signtheta) % CORDIC_FIXED(360)) -
		CORDIC_FIXED(180) * signtheta;

	अगर (CORDIC_FLOAT(theta) > 90) अणु
		theta -= CORDIC_FIXED(180);
		signx = -1;
	पूर्ण अन्यथा अगर (CORDIC_FLOAT(theta) < -90) अणु
		theta += CORDIC_FIXED(180);
		signx = -1;
	पूर्ण

	क्रम (iter = 0; iter < CORDIC_NUM_ITER; iter++) अणु
		अगर (theta > angle) अणु
			valपंचांगp = coord.i - (coord.q >> iter);
			coord.q += (coord.i >> iter);
			angle += arctan_table[iter];
		पूर्ण अन्यथा अणु
			valपंचांगp = coord.i + (coord.q >> iter);
			coord.q -= (coord.i >> iter);
			angle -= arctan_table[iter];
		पूर्ण
		coord.i = valपंचांगp;
	पूर्ण

	coord.i *= signx;
	coord.q *= signx;
	वापस coord;
पूर्ण
EXPORT_SYMBOL(cordic_calc_iq);

MODULE_DESCRIPTION("CORDIC algorithm");
MODULE_AUTHOR("Broadcom Corporation");
MODULE_LICENSE("Dual BSD/GPL");
