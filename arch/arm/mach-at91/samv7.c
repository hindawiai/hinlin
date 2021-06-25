<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Setup code क्रम SAMv7x
 *
 *  Copyright (C) 2013 Aपंचांगel,
 *                2016 Andras Szemzo <szemzo.andras@gmail.com>
 */
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/प्रणाली_misc.h>
#समावेश "generic.h"

अटल स्थिर अक्षर *स्थिर samv7_dt_board_compat[] __initस्थिर = अणु
	"atmel,samv7",
	शून्य
पूर्ण;

DT_MACHINE_START(samv7_dt, "Atmel SAMV7")
	.dt_compat	= samv7_dt_board_compat,
MACHINE_END
