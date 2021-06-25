<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2019 Stefan Wahren
 */

#समावेश <linux/of_address.h>

#समावेश <यंत्र/mach/arch.h>

#समावेश "platsmp.h"

अटल स्थिर अक्षर * स्थिर bcm2711_compat[] = अणु
#अगर_घोषित CONFIG_ARCH_MULTI_V7
	"brcm,bcm2711",
#पूर्ण_अगर
	शून्य
पूर्ण;

DT_MACHINE_START(BCM2711, "BCM2711")
#अगर_घोषित CONFIG_ZONE_DMA
	.dma_zone_size	= SZ_1G,
#पूर्ण_अगर
	.dt_compat = bcm2711_compat,
	.smp = smp_ops(bcm2836_smp_ops),
MACHINE_END
