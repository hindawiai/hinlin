<शैली गुरु>
/*
 * Utility to set the DAVINCI MUX रेजिस्टर from a table in mux.h
 *
 * Author: Vladimir Barinov, MontaVista Software, Inc. <source@mvista.com>
 *
 * Based on linux/arch/arm/plat-omap/mux.c:
 * Copyright (C) 2003 - 2005 Nokia Corporation
 *
 * Written by Tony Lindgren
 *
 * 2007 (c) MontaVista Software, Inc. This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 *
 * Copyright (C) 2008 Texas Instruments.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>

#समावेश <mach/mux.h>
#समावेश <mach/common.h>

अटल व्योम __iomem *pinmux_base;

/*
 * Sets the DAVINCI MUX रेजिस्टर based on the table
 */
पूर्णांक davinci_cfg_reg(स्थिर अचिन्हित दीर्घ index)
अणु
	अटल DEFINE_SPINLOCK(mux_spin_lock);
	काष्ठा davinci_soc_info *soc_info = &davinci_soc_info;
	अचिन्हित दीर्घ flags;
	स्थिर काष्ठा mux_config *cfg;
	अचिन्हित पूर्णांक reg_orig = 0, reg = 0;
	अचिन्हित पूर्णांक mask, warn = 0;

	अगर (WARN_ON(!soc_info->pinmux_pins))
		वापस -ENODEV;

	अगर (!pinmux_base) अणु
		pinmux_base = ioremap(soc_info->pinmux_base, SZ_4K);
		अगर (WARN_ON(!pinmux_base))
			वापस -ENOMEM;
	पूर्ण

	अगर (index >= soc_info->pinmux_pins_num) अणु
		pr_err("Invalid pin mux index: %lu (%lu)\n",
		       index, soc_info->pinmux_pins_num);
		dump_stack();
		वापस -ENODEV;
	पूर्ण

	cfg = &soc_info->pinmux_pins[index];

	अगर (cfg->name == शून्य) अणु
		pr_err("No entry for the specified index\n");
		वापस -ENODEV;
	पूर्ण

	/* Update the mux रेजिस्टर in question */
	अगर (cfg->mask) अणु
		अचिन्हित	पंचांगp1, पंचांगp2;

		spin_lock_irqsave(&mux_spin_lock, flags);
		reg_orig = __raw_पढ़ोl(pinmux_base + cfg->mux_reg);

		mask = (cfg->mask << cfg->mask_offset);
		पंचांगp1 = reg_orig & mask;
		reg = reg_orig & ~mask;

		पंचांगp2 = (cfg->mode << cfg->mask_offset);
		reg |= पंचांगp2;

		अगर (पंचांगp1 != पंचांगp2)
			warn = 1;

		__raw_ग_लिखोl(reg, pinmux_base + cfg->mux_reg);
		spin_unlock_irqrestore(&mux_spin_lock, flags);
	पूर्ण

	अगर (warn) अणु
#अगर_घोषित CONFIG_DAVINCI_MUX_WARNINGS
		pr_warn("initialized %s\n", cfg->name);
#पूर्ण_अगर
	पूर्ण

#अगर_घोषित CONFIG_DAVINCI_MUX_DEBUG
	अगर (cfg->debug || warn) अणु
		pr_warn("Setting register %s\n", cfg->name);
		pr_warn("   %s (0x%08x) = 0x%08x -> 0x%08x\n",
			cfg->mux_reg_name, cfg->mux_reg, reg_orig, reg);
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण
EXPORT_SYMBOL(davinci_cfg_reg);

पूर्णांक davinci_cfg_reg_list(स्थिर लघु pins[])
अणु
	पूर्णांक i, error = -EINVAL;

	अगर (pins)
		क्रम (i = 0; pins[i] >= 0; i++) अणु
			error = davinci_cfg_reg(pins[i]);
			अगर (error)
				अवरोध;
		पूर्ण

	वापस error;
पूर्ण
