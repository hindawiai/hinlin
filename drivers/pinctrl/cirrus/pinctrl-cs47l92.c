<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Pinctrl क्रम Cirrus Logic CS47L92
 *
 * Copyright (C) 2018-2019 Cirrus Logic, Inc. and
 *                         Cirrus Logic International Semiconductor Ltd.
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
अटल स्थिर अचिन्हित पूर्णांक cs47l92_spk1_pins[] = अणु 2, 3 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक cs47l92_aअगर1_pins[] = अणु 4, 5, 6, 7 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक cs47l92_aअगर2_pins[] = अणु 8, 9, 10, 11 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक cs47l92_aअगर3_pins[] = अणु 12, 13, 14, 15 पूर्ण;

अटल स्थिर काष्ठा madera_pin_groups cs47l92_pin_groups[] = अणु
	अणु "aif1", cs47l92_aअगर1_pins, ARRAY_SIZE(cs47l92_aअगर1_pins) पूर्ण,
	अणु "aif2", cs47l92_aअगर2_pins, ARRAY_SIZE(cs47l92_aअगर2_pins) पूर्ण,
	अणु "aif3", cs47l92_aअगर3_pins, ARRAY_SIZE(cs47l92_aअगर3_pins) पूर्ण,
	अणु "pdmspk1", cs47l92_spk1_pins, ARRAY_SIZE(cs47l92_spk1_pins) पूर्ण,
पूर्ण;

स्थिर काष्ठा madera_pin_chip cs47l92_pin_chip = अणु
	.n_pins = CS47L92_NUM_GPIOS,
	.pin_groups = cs47l92_pin_groups,
	.n_pin_groups = ARRAY_SIZE(cs47l92_pin_groups),
पूर्ण;
