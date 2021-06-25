<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2013-2014 Freescale Semiconductor, Inc.
 */

#समावेश <यंत्र/mach/arch.h>

#समावेश "common.h"

अटल स्थिर अक्षर * स्थिर ls1021a_dt_compat[] __initस्थिर = अणु
	"fsl,ls1021a",
	शून्य,
पूर्ण;

DT_MACHINE_START(LS1021A, "Freescale LS1021A")
	.smp		= smp_ops(ls1021a_smp_ops),
	.dt_compat	= ls1021a_dt_compat,
MACHINE_END
