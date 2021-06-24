<शैली गुरु>
/*
 * Copyright (C) 2012-2014 Broadcom Corporation
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

#समावेश <linux/घड़ीsource.h>
#समावेश <linux/of_address.h>

#समावेश <यंत्र/mach/arch.h>

#समावेश "kona_l2_cache.h"

#घोषणा SECWDOG_OFFSET			0x00000000
#घोषणा SECWDOG_RESERVED_MASK		0xe2000000
#घोषणा SECWDOG_WD_LOAD_FLAG_MASK	0x10000000
#घोषणा SECWDOG_EN_MASK			0x08000000
#घोषणा SECWDOG_SRSTEN_MASK		0x04000000
#घोषणा SECWDOG_CLKS_SHIFT		20
#घोषणा SECWDOG_COUNT_SHIFT		0

अटल व्योम bcm281xx_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
	uपूर्णांक32_t val;
	व्योम __iomem *base;
	काष्ठा device_node *np_wकरोg;

	np_wकरोg = of_find_compatible_node(शून्य, शून्य, "brcm,kona-wdt");
	अगर (!np_wकरोg) अणु
		pr_emerg("Couldn't find brcm,kona-wdt\n");
		वापस;
	पूर्ण
	base = of_iomap(np_wकरोg, 0);
	of_node_put(np_wकरोg);
	अगर (!base) अणु
		pr_emerg("Couldn't map brcm,kona-wdt\n");
		वापस;
	पूर्ण

	/* Enable watchकरोg with लघु समयout (244us). */
	val = पढ़ोl(base + SECWDOG_OFFSET);
	val &= SECWDOG_RESERVED_MASK | SECWDOG_WD_LOAD_FLAG_MASK;
	val |= SECWDOG_EN_MASK | SECWDOG_SRSTEN_MASK |
		(0x15 << SECWDOG_CLKS_SHIFT) |
		(0x8 << SECWDOG_COUNT_SHIFT);
	ग_लिखोl(val, base + SECWDOG_OFFSET);

	/* Wait क्रम reset */
	जबतक (1);
पूर्ण

अटल व्योम __init bcm281xx_init(व्योम)
अणु
	kona_l2_cache_init();
पूर्ण

अटल स्थिर अक्षर * स्थिर bcm281xx_dt_compat[] = अणु
	"brcm,bcm11351",	/* Have to use the first number upstreamed */
	शून्य,
पूर्ण;

DT_MACHINE_START(BCM281XX_DT, "BCM281xx Broadcom Application Processor")
	.init_machine = bcm281xx_init,
	.restart = bcm281xx_restart,
	.dt_compat = bcm281xx_dt_compat,
MACHINE_END
