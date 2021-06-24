<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Linaro Ltd.
 *
 * Author: Linus Walleij <linus.walleij@linaro.org>
 */
#समावेश <linux/of_platक्रमm.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/hardware/cache-l2x0.h>

अटल स्थिर अक्षर *स्थिर realview_dt_platक्रमm_compat[] __initस्थिर = अणु
	"arm,realview-eb",
	"arm,realview-pb1176",
	"arm,realview-pb11mp",
	"arm,realview-pba8",
	"arm,realview-pbx",
	शून्य,
पूर्ण;

DT_MACHINE_START(REALVIEW_DT, "ARM RealView Machine (Device Tree Support)")
#अगर_घोषित CONFIG_ZONE_DMA
	.dma_zone_size	= SZ_256M,
#पूर्ण_अगर
	.dt_compat	= realview_dt_platक्रमm_compat,
	.l2c_aux_val = 0x0,
	.l2c_aux_mask = ~0x0,
MACHINE_END
