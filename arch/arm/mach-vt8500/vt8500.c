<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  arch/arm/mach-vt8500/vt8500.c
 *
 *  Copyright (C) 2012 Tony Prisk <linux@prisktech.co.nz>
 */

#समावेश <linux/पन.स>
#समावेश <linux/pm.h>
#समावेश <linux/reboot.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/समय.स>
#समावेश <यंत्र/mach/map.h>

#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>

#घोषणा LEGACY_GPIO_BASE	0xD8110000
#घोषणा LEGACY_PMC_BASE		0xD8130000

/* Registers in GPIO Controller */
#घोषणा VT8500_GPIO_MUX_REG	0x200

/* Registers in Power Management Controller */
#घोषणा VT8500_HCR_REG		0x12
#घोषणा VT8500_PMSR_REG		0x60

अटल व्योम __iomem *pmc_base;

अटल व्योम vt8500_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
	अगर (pmc_base)
		ग_लिखोl(1, pmc_base + VT8500_PMSR_REG);
पूर्ण

अटल काष्ठा map_desc vt8500_io_desc[] __initdata = अणु
	/* SoC MMIO रेजिस्टरs */
	[0] = अणु
		.भव	= 0xf8000000,
		.pfn		= __phys_to_pfn(0xd8000000),
		.length		= 0x00390000, /* max of all chip variants */
		.type		= MT_DEVICE
	पूर्ण,
पूर्ण;

अटल व्योम __init vt8500_map_io(व्योम)
अणु
	iotable_init(vt8500_io_desc, ARRAY_SIZE(vt8500_io_desc));
पूर्ण

अटल व्योम vt8500_घातer_off(व्योम)
अणु
	local_irq_disable();
	ग_लिखोw(5, pmc_base + VT8500_HCR_REG);
	यंत्र("mcr p15, 0, %0, c7, c0, 4" : : "r" (0));
पूर्ण

अटल व्योम __init vt8500_init(व्योम)
अणु
	काष्ठा device_node *np;
#अगर defined(CONFIG_FB_VT8500) || defined(CONFIG_FB_WM8505)
	काष्ठा device_node *fb;
	व्योम __iomem *gpio_base;
#पूर्ण_अगर

#अगर_घोषित CONFIG_FB_VT8500
	fb = of_find_compatible_node(शून्य, शून्य, "via,vt8500-fb");
	अगर (fb) अणु
		np = of_find_compatible_node(शून्य, शून्य, "via,vt8500-gpio");
		अगर (np) अणु
			gpio_base = of_iomap(np, 0);

			अगर (!gpio_base)
				pr_err("%s: of_iomap(gpio_mux) failed\n",
								__func__);

			of_node_put(np);
		पूर्ण अन्यथा अणु
			gpio_base = ioremap(LEGACY_GPIO_BASE, 0x1000);
			अगर (!gpio_base)
				pr_err("%s: ioremap(legacy_gpio_mux) failed\n",
								__func__);
		पूर्ण
		अगर (gpio_base) अणु
			ग_लिखोl(पढ़ोl(gpio_base + VT8500_GPIO_MUX_REG) | 1,
				gpio_base + VT8500_GPIO_MUX_REG);
			iounmap(gpio_base);
		पूर्ण अन्यथा
			pr_err("%s: Could not remap GPIO mux\n", __func__);

		of_node_put(fb);
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_FB_WM8505
	fb = of_find_compatible_node(शून्य, शून्य, "wm,wm8505-fb");
	अगर (fb) अणु
		np = of_find_compatible_node(शून्य, शून्य, "wm,wm8505-gpio");
		अगर (!np)
			np = of_find_compatible_node(शून्य, शून्य,
							"wm,wm8650-gpio");
		अगर (np) अणु
			gpio_base = of_iomap(np, 0);

			अगर (!gpio_base)
				pr_err("%s: of_iomap(gpio_mux) failed\n",
								__func__);

			of_node_put(np);
		पूर्ण अन्यथा अणु
			gpio_base = ioremap(LEGACY_GPIO_BASE, 0x1000);
			अगर (!gpio_base)
				pr_err("%s: ioremap(legacy_gpio_mux) failed\n",
								__func__);
		पूर्ण
		अगर (gpio_base) अणु
			ग_लिखोl(पढ़ोl(gpio_base + VT8500_GPIO_MUX_REG) |
				0x80000000, gpio_base + VT8500_GPIO_MUX_REG);
			iounmap(gpio_base);
		पूर्ण अन्यथा
			pr_err("%s: Could not remap GPIO mux\n", __func__);

		of_node_put(fb);
	पूर्ण
#पूर्ण_अगर

	np = of_find_compatible_node(शून्य, शून्य, "via,vt8500-pmc");
	अगर (np) अणु
		pmc_base = of_iomap(np, 0);

		अगर (!pmc_base)
			pr_err("%s:of_iomap(pmc) failed\n", __func__);

		of_node_put(np);
	पूर्ण अन्यथा अणु
		pmc_base = ioremap(LEGACY_PMC_BASE, 0x1000);
		अगर (!pmc_base)
			pr_err("%s:ioremap(power_off) failed\n", __func__);
	पूर्ण
	अगर (pmc_base)
		pm_घातer_off = &vt8500_घातer_off;
	अन्यथा
		pr_err("%s: PMC Hibernation register could not be remapped, not enabling power off!\n", __func__);
पूर्ण

अटल स्थिर अक्षर * स्थिर vt8500_dt_compat[] = अणु
	"via,vt8500",
	"wm,wm8650",
	"wm,wm8505",
	"wm,wm8750",
	"wm,wm8850",
	शून्य
पूर्ण;

DT_MACHINE_START(WMT_DT, "VIA/Wondermedia SoC (Device Tree Support)")
	.dt_compat	= vt8500_dt_compat,
	.map_io		= vt8500_map_io,
	.init_machine	= vt8500_init,
	.restart	= vt8500_restart,
MACHINE_END

