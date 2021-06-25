<शैली गुरु>
/*
 * Copyright (C) 2017 Broadcom
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <यंत्र/mach/arch.h>

अटल स्थिर अक्षर * स्थिर bcm_hr2_dt_compat[] __initस्थिर = अणु
	"brcm,hr2",
	शून्य,
पूर्ण;

DT_MACHINE_START(BCM_HR2_DT, "Broadcom Hurricane 2 SoC")
	.l2c_aux_val	= 0,
	.l2c_aux_mask	= ~0,
	.dt_compat = bcm_hr2_dt_compat,
MACHINE_END
