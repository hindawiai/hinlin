<शैली गुरु>
/*
 * arch/arm/mach-spear13xx/spear1340.c
 *
 * SPEAr1340 machine source file
 *
 * Copyright (C) 2012 ST Microelectronics
 * Viresh Kumar <vireshk@kernel.org>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#घोषणा pr_fmt(fmt) "SPEAr1340: " fmt

#समावेश <linux/of_platक्रमm.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश "generic.h"

अटल व्योम __init spear1340_dt_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर_simple("spear-cpufreq", -1, शून्य, 0);
पूर्ण

अटल स्थिर अक्षर * स्थिर spear1340_dt_board_compat[] = अणु
	"st,spear1340",
	"st,spear1340-evb",
	शून्य,
पूर्ण;

DT_MACHINE_START(SPEAR1340_DT, "ST SPEAr1340 SoC with Flattened Device Tree")
	.smp		=	smp_ops(spear13xx_smp_ops),
	.map_io		=	spear13xx_map_io,
	.init_समय	=	spear13xx_समयr_init,
	.init_machine	=	spear1340_dt_init,
	.restart	=	spear_restart,
	.dt_compat	=	spear1340_dt_board_compat,
MACHINE_END
