<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * r7s9210 processor support
 *
 * Copyright (C) 2018  Renesas Electronics Corporation
 * Copyright (C) 2018  Chris Bअक्रमt
 *
 */

#समावेश <linux/kernel.h>

#समावेश <यंत्र/mach/arch.h>

#समावेश "common.h"

अटल स्थिर अक्षर *स्थिर r7s9210_boards_compat_dt[] __initस्थिर = अणु
	"renesas,r7s9210",
	शून्य,
पूर्ण;

DT_MACHINE_START(R7S72100_DT, "Generic R7S9210 (Flattened Device Tree)")
	.l2c_aux_val    = 0,
	.l2c_aux_mask   = ~0,
	.init_early	= shmobile_init_delay,
	.init_late	= shmobile_init_late,
	.dt_compat	= r7s9210_boards_compat_dt,
MACHINE_END
