<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Marvell EBU SoC common घड़ी handling
 *
 * Copyright (C) 2012 Marvell
 *
 * Gregory CLEMENT <gregory.clement@मुक्त-electrons.com>
 * Sebastian Hesselbarth <sebastian.hesselbarth@gmail.com>
 * Andrew Lunn <andrew@lunn.ch>
 *
 */

#अगर_अघोषित __CLK_MVEBU_COMMON_H_
#घोषणा __CLK_MVEBU_COMMON_H_

#समावेश <linux/kernel.h>

बाह्य spinlock_t ctrl_gating_lock;

काष्ठा device_node;

काष्ठा coreclk_ratio अणु
	पूर्णांक id;
	स्थिर अक्षर *name;
पूर्ण;

काष्ठा coreclk_soc_desc अणु
	u32 (*get_tclk_freq)(व्योम __iomem *sar);
	u32 (*get_cpu_freq)(व्योम __iomem *sar);
	व्योम (*get_clk_ratio)(व्योम __iomem *sar, पूर्णांक id, पूर्णांक *mult, पूर्णांक *भाग);
	u32 (*get_refclk_freq)(व्योम __iomem *sar);
	bool (*is_sscg_enabled)(व्योम __iomem *sar);
	u32 (*fix_sscg_deviation)(u32 प्रणाली_clk);
	स्थिर काष्ठा coreclk_ratio *ratios;
	पूर्णांक num_ratios;
पूर्ण;

काष्ठा clk_gating_soc_desc अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *parent;
	पूर्णांक bit_idx;
	अचिन्हित दीर्घ flags;
पूर्ण;

व्योम __init mvebu_coreclk_setup(काष्ठा device_node *np,
				स्थिर काष्ठा coreclk_soc_desc *desc);

व्योम __init mvebu_clk_gating_setup(काष्ठा device_node *np,
				   स्थिर काष्ठा clk_gating_soc_desc *desc);

/*
 * This function is shared among the Kirkwood, Armada 370, Armada XP
 * and Armada 375 SoC
 */
u32 kirkwood_fix_sscg_deviation(u32 प्रणाली_clk);
#पूर्ण_अगर
