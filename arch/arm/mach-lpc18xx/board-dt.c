<शैली गुरु>
/*
 * Device Tree board file क्रम NXP LPC18xx/43xx
 *
 * Copyright (C) 2015 Joachim Eastwood <manabian@gmail.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <यंत्र/mach/arch.h>

अटल स्थिर अक्षर *स्थिर lpc18xx_43xx_compat[] __initस्थिर = अणु
	"nxp,lpc1850",
	"nxp,lpc4350",
	"nxp,lpc4370",
	शून्य
पूर्ण;

DT_MACHINE_START(LPC18XXDT, "NXP LPC18xx/43xx (Device Tree)")
	.dt_compat = lpc18xx_43xx_compat,
MACHINE_END
