<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2010 Broadcom
 */

#समावेश <linux/init.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/of_address.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "platsmp.h"

अटल स्थिर अक्षर * स्थिर bcm2835_compat[] = अणु
#अगर_घोषित CONFIG_ARCH_MULTI_V6
	"brcm,bcm2835",
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_MULTI_V7
	"brcm,bcm2836",
	"brcm,bcm2837",
#पूर्ण_अगर
	शून्य
पूर्ण;

DT_MACHINE_START(BCM2835, "BCM2835")
	.dt_compat = bcm2835_compat,
	.smp = smp_ops(bcm2836_smp_ops),
MACHINE_END
