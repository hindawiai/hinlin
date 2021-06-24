<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/sh/boards/sh03/setup.c
 *
 * Copyright (C) 2004  Interface Co.,Ltd. Saito.K
 *
 */

#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ata_platक्रमm.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/rtc.h>
#समावेश <mach-sh03/mach/पन.स>
#समावेश <mach-sh03/mach/sh03.h>
#समावेश <यंत्र/addrspace.h>

अटल व्योम __init init_sh03_IRQ(व्योम)
अणु
	plat_irq_setup_pins(IRQ_MODE_IRQ);
पूर्ण

अटल काष्ठा resource cf_ide_resources[] = अणु
	[0] = अणु
		.start  = 0x1f0,
		.end    = 0x1f0 + 8,
		.flags  = IORESOURCE_IO,
	पूर्ण,
	[1] = अणु
		.start  = 0x1f0 + 0x206,
		.end    = 0x1f0 +8 + 0x206 + 8,
		.flags  = IORESOURCE_IO,
	पूर्ण,
	[2] = अणु
		.start  = IRL2_IRQ,
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device cf_ide_device = अणु
	.name		= "pata_platform",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(cf_ide_resources),
	.resource	= cf_ide_resources,
पूर्ण;

अटल काष्ठा resource heartbeat_resources[] = अणु
	[0] = अणु
		.start	= 0xa0800000,
		.end	= 0xa0800000,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device heartbeat_device = अणु
	.name		= "heartbeat",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(heartbeat_resources),
	.resource	= heartbeat_resources,
पूर्ण;

अटल काष्ठा platक्रमm_device *sh03_devices[] __initdata = अणु
	&heartbeat_device,
	&cf_ide_device,
पूर्ण;

अटल पूर्णांक __init sh03_devices_setup(व्योम)
अणु
	pgprot_t prot;
	अचिन्हित दीर्घ paddrbase;
	व्योम *cf_ide_base;

	/* खोलो I/O area winकरोw */
	paddrbase = virt_to_phys((व्योम *)PA_AREA5_IO);
	prot = PAGE_KERNEL_PCC(1, _PAGE_PCC_IO16);
	cf_ide_base = ioremap_prot(paddrbase, PAGE_SIZE, pgprot_val(prot));
	अगर (!cf_ide_base) अणु
		prपूर्णांकk("allocate_cf_area : can't open CF I/O window!\n");
		वापस -ENOMEM;
	पूर्ण

	/* IDE cmd address : 0x1f0-0x1f7 and 0x3f6 */
	cf_ide_resources[0].start += (अचिन्हित दीर्घ)cf_ide_base;
	cf_ide_resources[0].end   += (अचिन्हित दीर्घ)cf_ide_base;
	cf_ide_resources[1].start += (अचिन्हित दीर्घ)cf_ide_base;
	cf_ide_resources[1].end   += (अचिन्हित दीर्घ)cf_ide_base;

	वापस platक्रमm_add_devices(sh03_devices, ARRAY_SIZE(sh03_devices));
पूर्ण
device_initcall(sh03_devices_setup);

अटल काष्ठा sh_machine_vector mv_sh03 __iniपंचांगv = अणु
	.mv_name		= "Interface (CTP/PCI-SH03)",
	.mv_init_irq		= init_sh03_IRQ,
पूर्ण;
