<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Pinctrl क्रम Cirrus Logic CS47L85
 *
 * Copyright (C) 2016-2017 Cirrus Logic
 */

#समावेश <linux/err.h>
#समावेश <linux/mfd/madera/core.h>

#समावेश "pinctrl-madera.h"

/*
 * The alt func groups are the most commonly used functions we place these at
 * the lower function indexes क्रम convenience, and the less commonly used gpio
 * functions at higher indexes.
 *
 * To stay consistent with the datasheet the function names are the same as
 * the group names क्रम that function's pins
 *
 * Note - all 1 less than in datasheet because these are zero-indexed
 */
अटल स्थिर अचिन्हित पूर्णांक cs47l85_mअगर1_pins[] = अणु 8, 9 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक cs47l85_mअगर2_pins[] = अणु 10, 11 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक cs47l85_mअगर3_pins[] = अणु 12, 13 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक cs47l85_aअगर1_pins[] = अणु 14, 15, 16, 17 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक cs47l85_aअगर2_pins[] = अणु 18, 19, 20, 21 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक cs47l85_aअगर3_pins[] = अणु 22, 23, 24, 25 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक cs47l85_aअगर4_pins[] = अणु 26, 27, 28, 29 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक cs47l85_dmic4_pins[] = अणु 30, 31 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक cs47l85_dmic5_pins[] = अणु 32, 33 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक cs47l85_dmic6_pins[] = अणु 34, 35 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक cs47l85_spk1_pins[] = अणु 36, 38 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक cs47l85_spk2_pins[] = अणु 37, 39 पूर्ण;

अटल स्थिर काष्ठा madera_pin_groups cs47l85_pin_groups[] = अणु
	अणु "aif1", cs47l85_aअगर1_pins, ARRAY_SIZE(cs47l85_aअगर1_pins) पूर्ण,
	अणु "aif2", cs47l85_aअगर2_pins, ARRAY_SIZE(cs47l85_aअगर2_pins) पूर्ण,
	अणु "aif3", cs47l85_aअगर3_pins, ARRAY_SIZE(cs47l85_aअगर3_pins) पूर्ण,
	अणु "aif4", cs47l85_aअगर4_pins, ARRAY_SIZE(cs47l85_aअगर4_pins) पूर्ण,
	अणु "mif1", cs47l85_mअगर1_pins, ARRAY_SIZE(cs47l85_mअगर1_pins) पूर्ण,
	अणु "mif2", cs47l85_mअगर2_pins, ARRAY_SIZE(cs47l85_mअगर2_pins) पूर्ण,
	अणु "mif3", cs47l85_mअगर3_pins, ARRAY_SIZE(cs47l85_mअगर3_pins) पूर्ण,
	अणु "dmic4", cs47l85_dmic4_pins, ARRAY_SIZE(cs47l85_dmic4_pins) पूर्ण,
	अणु "dmic5", cs47l85_dmic5_pins, ARRAY_SIZE(cs47l85_dmic5_pins) पूर्ण,
	अणु "dmic6", cs47l85_dmic6_pins, ARRAY_SIZE(cs47l85_dmic6_pins) पूर्ण,
	अणु "pdmspk1", cs47l85_spk1_pins, ARRAY_SIZE(cs47l85_spk1_pins) पूर्ण,
	अणु "pdmspk2", cs47l85_spk2_pins, ARRAY_SIZE(cs47l85_spk2_pins) पूर्ण,
पूर्ण;

स्थिर काष्ठा madera_pin_chip cs47l85_pin_chip = अणु
	.n_pins = CS47L85_NUM_GPIOS,
	.pin_groups = cs47l85_pin_groups,
	.n_pin_groups = ARRAY_SIZE(cs47l85_pin_groups),
पूर्ण;
