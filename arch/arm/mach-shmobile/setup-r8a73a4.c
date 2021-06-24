<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * r8a73a4 processor support
 *
 * Copyright (C) 2013  Renesas Solutions Corp.
 * Copyright (C) 2013  Magnus Damm
 */

#समावेश <linux/init.h>

#समावेश <यंत्र/mach/arch.h>

#समावेश "common.h"

अटल स्थिर अक्षर *स्थिर r8a73a4_boards_compat_dt[] __initस्थिर = अणु
	"renesas,r8a73a4",
	शून्य,
पूर्ण;

DT_MACHINE_START(R8A73A4_DT, "Generic R8A73A4 (Flattened Device Tree)")
	.init_late	= shmobile_init_late,
	.dt_compat	= r8a73a4_boards_compat_dt,
MACHINE_END
