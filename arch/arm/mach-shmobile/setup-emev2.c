<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Emma Mobile EV2 processor support
 *
 * Copyright (C) 2012  Magnus Damm
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "common.h"
#समावेश "emev2.h"

अटल स्थिर अक्षर *स्थिर emev2_boards_compat_dt[] __initस्थिर = अणु
	"renesas,emev2",
	शून्य,
पूर्ण;

DT_MACHINE_START(EMEV2_DT, "Generic Emma Mobile EV2 (Flattened Device Tree)")
	.smp		= smp_ops(emev2_smp_ops),
	.init_early	= shmobile_init_delay,
	.init_late	= shmobile_init_late,
	.dt_compat	= emev2_boards_compat_dt,
MACHINE_END
