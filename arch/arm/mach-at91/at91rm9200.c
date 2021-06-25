<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Setup code क्रम AT91RM9200
 *
 *  Copyright (C) 2011 Aपंचांगel,
 *                2011 Nicolas Ferre <nicolas.ferre@aपंचांगel.com>
 *                2012 Joachim Eastwood <manabian@gmail.com>
 */

#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/mach/arch.h>

#समावेश "generic.h"

अटल व्योम __init at91rm9200_dt_device_init(व्योम)
अणु
	of_platक्रमm_शेष_populate(शून्य, शून्य, शून्य);

	at91rm9200_pm_init();
पूर्ण

अटल स्थिर अक्षर *स्थिर at91rm9200_dt_board_compat[] __initस्थिर = अणु
	"atmel,at91rm9200",
	शून्य
पूर्ण;

DT_MACHINE_START(at91rm9200_dt, "Atmel AT91RM9200")
	.init_machine	= at91rm9200_dt_device_init,
	.dt_compat	= at91rm9200_dt_board_compat,
MACHINE_END
