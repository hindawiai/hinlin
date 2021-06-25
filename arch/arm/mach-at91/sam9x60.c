<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Setup code क्रम SAM9X60.
 *
 * Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries
 *
 * Author: Claudiu Beznea <claudiu.beznea@microchip.com>
 */

#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/प्रणाली_misc.h>

#समावेश "generic.h"

अटल व्योम __init sam9x60_init(व्योम)
अणु
	of_platक्रमm_शेष_populate(शून्य, शून्य, शून्य);

	sam9x60_pm_init();
पूर्ण

अटल स्थिर अक्षर *स्थिर sam9x60_dt_board_compat[] __initस्थिर = अणु
	"microchip,sam9x60",
	शून्य
पूर्ण;

DT_MACHINE_START(sam9x60_dt, "Microchip SAM9X60")
	/* Maपूर्णांकainer: Microchip */
	.init_machine	= sam9x60_init,
	.dt_compat	= sam9x60_dt_board_compat,
MACHINE_END
