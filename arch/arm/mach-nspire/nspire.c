<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	linux/arch/arm/mach-nspire/nspire.c
 *
 *	Copyright (C) 2013 Daniel Tang <tangrs@tangrs.id.au>
 */
#समावेश <linux/init.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/arm-vic.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/amba/bus.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "mmio.h"

अटल स्थिर अक्षर *स्थिर nspire_dt_match[] __initस्थिर = अणु
	"ti,nspire",
	"ti,nspire-cx",
	"ti,nspire-tp",
	"ti,nspire-clp",
	शून्य,
पूर्ण;

अटल व्योम nspire_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
	व्योम __iomem *base = ioremap(NSPIRE_MISC_PHYS_BASE, SZ_4K);
	अगर (!base)
		वापस;

	ग_लिखोl(2, base + NSPIRE_MISC_HWRESET);
पूर्ण

DT_MACHINE_START(NSPIRE, "TI-NSPIRE")
	.dt_compat	= nspire_dt_match,
	.restart	= nspire_restart,
MACHINE_END
