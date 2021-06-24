<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2017 Linaro Ltd.
 *
 * Author: Linus Walleij <linus.walleij@linaro.org>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2, as
 * published by the Free Software Foundation.
 *
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <linux/of.h>

#घोषणा GLOBAL_WORD_ID				0x00
#घोषणा GEMINI_GLOBAL_ARB1_CTRL			0x2c
#घोषणा GEMINI_ARB1_BURST_MASK			GENMASK(21, 16)
#घोषणा GEMINI_ARB1_BURST_SHIFT			16
/* These all define the priority on the BUS2 backplane */
#घोषणा GEMINI_ARB1_PRIO_MASK			GENMASK(9, 0)
#घोषणा GEMINI_ARB1_DMAC_HIGH_PRIO		BIT(0)
#घोषणा GEMINI_ARB1_IDE_HIGH_PRIO		BIT(1)
#घोषणा GEMINI_ARB1_RAID_HIGH_PRIO		BIT(2)
#घोषणा GEMINI_ARB1_SECURITY_HIGH_PRIO		BIT(3)
#घोषणा GEMINI_ARB1_GMAC0_HIGH_PRIO		BIT(4)
#घोषणा GEMINI_ARB1_GMAC1_HIGH_PRIO		BIT(5)
#घोषणा GEMINI_ARB1_USB0_HIGH_PRIO		BIT(6)
#घोषणा GEMINI_ARB1_USB1_HIGH_PRIO		BIT(7)
#घोषणा GEMINI_ARB1_PCI_HIGH_PRIO		BIT(8)
#घोषणा GEMINI_ARB1_TVE_HIGH_PRIO		BIT(9)

#घोषणा GEMINI_DEFAULT_BURST_SIZE		0x20
#घोषणा GEMINI_DEFAULT_PRIO			(GEMINI_ARB1_GMAC0_HIGH_PRIO | \
						 GEMINI_ARB1_GMAC1_HIGH_PRIO)

अटल पूर्णांक __init gemini_soc_init(व्योम)
अणु
	काष्ठा regmap *map;
	u32 rev;
	u32 val;
	पूर्णांक ret;

	/* Multiplatक्रमm guard, only proceed on Gemini */
	अगर (!of_machine_is_compatible("cortina,gemini"))
		वापस 0;

	map = syscon_regmap_lookup_by_compatible("cortina,gemini-syscon");
	अगर (IS_ERR(map))
		वापस PTR_ERR(map);
	ret = regmap_पढ़ो(map, GLOBAL_WORD_ID, &rev);
	अगर (ret)
		वापस ret;

	val = (GEMINI_DEFAULT_BURST_SIZE << GEMINI_ARB1_BURST_SHIFT) |
		GEMINI_DEFAULT_PRIO;

	/* Set up प्रणाली arbitration */
	regmap_update_bits(map,
			   GEMINI_GLOBAL_ARB1_CTRL,
			   GEMINI_ARB1_BURST_MASK | GEMINI_ARB1_PRIO_MASK,
			   val);

	pr_info("Gemini SoC %04x revision %02x, set arbitration %08x\n",
		rev >> 8, rev & 0xff, val);

	वापस 0;
पूर्ण
subsys_initcall(gemini_soc_init);
