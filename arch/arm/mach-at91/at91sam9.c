<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Setup code क्रम AT91SAM9
 *
 *  Copyright (C) 2011 Aपंचांगel,
 *                2011 Nicolas Ferre <nicolas.ferre@aपंचांगel.com>
 */

#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/प्रणाली_misc.h>

#समावेश "generic.h"

अटल व्योम __init at91sam9_init(व्योम)
अणु
	of_platक्रमm_शेष_populate(शून्य, शून्य, शून्य);

	at91sam9_pm_init();
पूर्ण

अटल स्थिर अक्षर *स्थिर at91_dt_board_compat[] __initस्थिर = अणु
	"atmel,at91sam9",
	शून्य
पूर्ण;

DT_MACHINE_START(at91sam_dt, "Atmel AT91SAM9")
	/* Maपूर्णांकainer: Aपंचांगel */
	.init_machine	= at91sam9_init,
	.dt_compat	= at91_dt_board_compat,
MACHINE_END
