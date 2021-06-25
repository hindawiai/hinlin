<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Versatile board support using the device tree
 *
 *  Copyright (C) 2010 Secret Lab Technologies Ltd.
 *  Copyright (C) 2009 Jeremy Kerr <jeremy.kerr@canonical.com>
 *  Copyright (C) 2004 ARM Limited
 *  Copyright (C) 2000 Deep Blue Solutions Ltd
 */

#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/slab.h>
#समावेश <linux/amba/bus.h>
#समावेश <linux/amba/mmci.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

/* macro to get at MMIO space when running भवly */
#घोषणा IO_ADDRESS(x)		(((x) & 0x0fffffff) + (((x) >> 4) & 0x0f000000) + 0xf0000000)
#घोषणा __io_address(n)		((व्योम __iomem __क्रमce *)IO_ADDRESS(n))

/*
 * ------------------------------------------------------------------------
 *  Versatile Registers
 * ------------------------------------------------------------------------
 */
#घोषणा VERSATILE_SYS_PCICTL_OFFSET           0x44
#घोषणा VERSATILE_SYS_MCI_OFFSET              0x48

/*
 * VERSATILE peripheral addresses
 */
#घोषणा VERSATILE_MMCI0_BASE           0x10005000	/* MMC पूर्णांकerface */
#घोषणा VERSATILE_MMCI1_BASE           0x1000B000	/* MMC Interface */
#घोषणा VERSATILE_SCTL_BASE            0x101E0000	/* System controller */

/*
 * System controller bit assignment
 */
#घोषणा VERSATILE_REFCLK	0
#घोषणा VERSATILE_TIMCLK	1

#घोषणा VERSATILE_TIMER1_EnSel	15
#घोषणा VERSATILE_TIMER2_EnSel	17
#घोषणा VERSATILE_TIMER3_EnSel	19
#घोषणा VERSATILE_TIMER4_EnSel	21

अटल व्योम __iomem *versatile_sys_base;

अचिन्हित पूर्णांक mmc_status(काष्ठा device *dev)
अणु
	काष्ठा amba_device *adev = container_of(dev, काष्ठा amba_device, dev);
	u32 mask;

	अगर (adev->res.start == VERSATILE_MMCI0_BASE)
		mask = 1;
	अन्यथा
		mask = 2;

	वापस पढ़ोl(versatile_sys_base + VERSATILE_SYS_MCI_OFFSET) & mask;
पूर्ण

अटल काष्ठा mmci_platक्रमm_data mmc0_plat_data = अणु
	.ocr_mask	= MMC_VDD_32_33|MMC_VDD_33_34,
	.status		= mmc_status,
पूर्ण;

अटल काष्ठा mmci_platक्रमm_data mmc1_plat_data = अणु
	.ocr_mask	= MMC_VDD_32_33|MMC_VDD_33_34,
	.status		= mmc_status,
पूर्ण;

/*
 * Lookup table क्रम attaching a specअगरic name and platक्रमm_data poपूर्णांकer to
 * devices as they get created by of_platक्रमm_populate().  Ideally this table
 * would not exist, but the current घड़ी implementation depends on some devices
 * having a specअगरic name.
 */
काष्ठा of_dev_auxdata versatile_auxdata_lookup[] __initdata = अणु
	OF_DEV_AUXDATA("arm,primecell", VERSATILE_MMCI0_BASE, "fpga:05", &mmc0_plat_data),
	OF_DEV_AUXDATA("arm,primecell", VERSATILE_MMCI1_BASE, "fpga:0b", &mmc1_plat_data),
	अणुपूर्ण
पूर्ण;

अटल काष्ठा map_desc versatile_io_desc[] __initdata __maybe_unused = अणु
	अणु
		.भव	=  IO_ADDRESS(VERSATILE_SCTL_BASE),
		.pfn		= __phys_to_pfn(VERSATILE_SCTL_BASE),
		.length		= SZ_4K * 9,
		.type		= MT_DEVICE
	पूर्ण
पूर्ण;

अटल व्योम __init versatile_map_io(व्योम)
अणु
	debug_ll_io_init();
	iotable_init(versatile_io_desc, ARRAY_SIZE(versatile_io_desc));
पूर्ण

अटल व्योम __init versatile_init_early(व्योम)
अणु
	u32 val;

	/*
	 * set घड़ी frequency:
	 *	VERSATILE_REFCLK is 32KHz
	 *	VERSATILE_TIMCLK is 1MHz
	 */
	val = पढ़ोl(__io_address(VERSATILE_SCTL_BASE));
	ग_लिखोl((VERSATILE_TIMCLK << VERSATILE_TIMER1_EnSel) |
	       (VERSATILE_TIMCLK << VERSATILE_TIMER2_EnSel) |
	       (VERSATILE_TIMCLK << VERSATILE_TIMER3_EnSel) |
	       (VERSATILE_TIMCLK << VERSATILE_TIMER4_EnSel) | val,
	       __io_address(VERSATILE_SCTL_BASE));
पूर्ण

अटल व्योम __init versatile_dt_pci_init(व्योम)
अणु
	u32 val;
	काष्ठा device_node *np;
	काष्ठा property *newprop;

	np = of_find_compatible_node(शून्य, शून्य, "arm,versatile-pci");
	अगर (!np)
		वापस;

	/* Check अगर PCI backplane is detected */
	val = पढ़ोl(versatile_sys_base + VERSATILE_SYS_PCICTL_OFFSET);
	अगर (val & 1) अणु
		/*
		 * Enable PCI accesses. Note that the करोcumentaton is
		 * inconsistent whether or not this is needed, but the old
		 * driver had it so we will keep it.
		 */
		ग_लिखोl(1, versatile_sys_base + VERSATILE_SYS_PCICTL_OFFSET);
		जाओ out_put_node;
	पूर्ण

	newprop = kzalloc(माप(*newprop), GFP_KERNEL);
	अगर (!newprop)
		जाओ out_put_node;

	newprop->name = kstrdup("status", GFP_KERNEL);
	newprop->value = kstrdup("disabled", GFP_KERNEL);
	newprop->length = माप("disabled");
	of_update_property(np, newprop);

	pr_info("Not plugged into PCI backplane!\n");

out_put_node:
	of_node_put(np);
पूर्ण

अटल व्योम __init versatile_dt_init(व्योम)
अणु
	काष्ठा device_node *np;

	np = of_find_compatible_node(शून्य, शून्य, "arm,core-module-versatile");
	अगर (np)
		versatile_sys_base = of_iomap(np, 0);
	WARN_ON(!versatile_sys_base);

	versatile_dt_pci_init();

	of_platक्रमm_शेष_populate(शून्य, versatile_auxdata_lookup, शून्य);
पूर्ण

अटल स्थिर अक्षर *स्थिर versatile_dt_match[] __initस्थिर = अणु
	"arm,versatile-ab",
	"arm,versatile-pb",
	शून्य,
पूर्ण;

DT_MACHINE_START(VERSATILE_PB, "ARM-Versatile (Device Tree Support)")
	.map_io		= versatile_map_io,
	.init_early	= versatile_init_early,
	.init_machine	= versatile_dt_init,
	.dt_compat	= versatile_dt_match,
MACHINE_END
