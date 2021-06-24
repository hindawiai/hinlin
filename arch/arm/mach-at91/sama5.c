<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Setup code क्रम SAMA5
 *
 *  Copyright (C) 2013 Aपंचांगel,
 *                2013 Luकरोvic Desroches <luकरोvic.desroches@aपंचांगel.com>
 */

#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/प्रणाली_misc.h>

#समावेश "generic.h"

अटल व्योम __init sama5_dt_device_init(व्योम)
अणु
	of_platक्रमm_शेष_populate(शून्य, शून्य, शून्य);
	sama5_pm_init();
पूर्ण

अटल स्थिर अक्षर *स्थिर sama5_dt_board_compat[] __initस्थिर = अणु
	"atmel,sama5",
	शून्य
पूर्ण;

DT_MACHINE_START(sama5_dt, "Atmel SAMA5")
	/* Maपूर्णांकainer: Aपंचांगel */
	.init_machine	= sama5_dt_device_init,
	.dt_compat	= sama5_dt_board_compat,
MACHINE_END

अटल स्थिर अक्षर *स्थिर sama5_alt_dt_board_compat[] __initस्थिर = अणु
	"atmel,sama5d4",
	शून्य
पूर्ण;

DT_MACHINE_START(sama5_alt_dt, "Atmel SAMA5")
	/* Maपूर्णांकainer: Aपंचांगel */
	.init_machine	= sama5_dt_device_init,
	.dt_compat	= sama5_alt_dt_board_compat,
	.l2c_aux_mask	= ~0UL,
MACHINE_END

अटल व्योम __init sama5d2_init(व्योम)
अणु
	of_platक्रमm_शेष_populate(शून्य, शून्य, शून्य);
	sama5d2_pm_init();
पूर्ण

अटल स्थिर अक्षर *स्थिर sama5d2_compat[] __initस्थिर = अणु
	"atmel,sama5d2",
	शून्य
पूर्ण;

DT_MACHINE_START(sama5d2, "Atmel SAMA5")
	/* Maपूर्णांकainer: Aपंचांगel */
	.init_machine	= sama5d2_init,
	.dt_compat	= sama5d2_compat,
	.l2c_aux_mask	= ~0UL,
MACHINE_END
