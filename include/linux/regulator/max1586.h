<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * max1586.h  --  Voltage regulation क्रम the Maxim 1586
 *
 * Copyright (C) 2008 Robert Jarzmik
 */

#अगर_अघोषित REGULATOR_MAX1586
#घोषणा REGULATOR_MAX1586

#समावेश <linux/regulator/machine.h>

#घोषणा MAX1586_V3 0
#घोषणा MAX1586_V6 1

/* precalculated values क्रम v3_gain */
#घोषणा MAX1586_GAIN_NO_R24   1000000  /* 700000 .. 1475000 mV */
#घोषणा MAX1586_GAIN_R24_3k32 1051098  /* 735768 .. 1550369 mV */
#घोषणा MAX1586_GAIN_R24_5k11 1078648  /* 755053 .. 1591005 mV */
#घोषणा MAX1586_GAIN_R24_7k5  1115432  /* 780802 .. 1645262 mV */

/**
 * max1586_subdev_data - regulator data
 * @id: regulator Id (either MAX1586_V3 or MAX1586_V6)
 * @name: regulator cute name (example क्रम V3: "vcc_core")
 * @platक्रमm_data: regulator init data (स्थिरraपूर्णांकs, supplies, ...)
 */
काष्ठा max1586_subdev_data अणु
	पूर्णांक				id;
	स्थिर अक्षर			*name;
	काष्ठा regulator_init_data	*platक्रमm_data;
पूर्ण;

/**
 * max1586_platक्रमm_data - platक्रमm data क्रम max1586
 * @num_subdevs: number of regulators used (may be 1 or 2)
 * @subdevs: regulator used
 *           At most, there will be a regulator क्रम V3 and one क्रम V6 voltages.
 * @v3_gain: gain on the V3 voltage output multiplied by 1e6.
 *           This can be calculated as ((1 + R24/R25 + R24/185.5kOhm) * 1e6)
 *           क्रम an बाह्यal resistor configuration as described in the
 *           data sheet (R25=100kOhm).
 */
काष्ठा max1586_platक्रमm_data अणु
	पूर्णांक num_subdevs;
	काष्ठा max1586_subdev_data *subdevs;
	पूर्णांक v3_gain;
पूर्ण;

#पूर्ण_अगर
