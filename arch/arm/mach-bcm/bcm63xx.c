<शैली गुरु>
/*
 * Copyright (C) 2014 Broadcom Corporation
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

#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/mach/arch.h>

अटल स्थिर अक्षर * स्थिर bcm63xx_dt_compat[] = अणु
	"brcm,bcm63138",
	शून्य
पूर्ण;

DT_MACHINE_START(BCM63XXX_DT, "BCM63xx DSL SoC")
	.dt_compat	= bcm63xx_dt_compat,
	.l2c_aux_val	= 0,
	.l2c_aux_mask	= ~0,
MACHINE_END
