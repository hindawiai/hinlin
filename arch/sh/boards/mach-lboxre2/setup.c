<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/sh/boards/lbox/setup.c
 *
 * Copyright (C) 2007 Nobuhiro Iwamatsu
 *
 * NTT COMWARE L-BOX RE2 Support
 */

#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ata_platक्रमm.h>
#समावेश <यंत्र/machvec.h>
#समावेश <यंत्र/addrspace.h>
#समावेश <mach/lboxre2.h>
#समावेश <यंत्र/पन.स>

अटल काष्ठा resource cf_ide_resources[] = अणु
	[0] = अणु
		.start  = 0x1f0,
		.end    = 0x1f0 + 8 ,
		.flags  = IORESOURCE_IO,
	पूर्ण,
	[1] = अणु
		.start  = 0x1f0 + 0x206,
		.end    = 0x1f0 +8 + 0x206 + 8,
		.flags  = IORESOURCE_IO,
	पूर्ण,
	[2] = अणु
		.start  = IRQ_CF0,
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device cf_ide_device  = अणु
	.name           = "pata_platform",
	.id             = -1,
	.num_resources  = ARRAY_SIZE(cf_ide_resources),
	.resource       = cf_ide_resources,
पूर्ण;

अटल काष्ठा platक्रमm_device *lboxre2_devices[] __initdata = अणु
       &cf_ide_device,
पूर्ण;

अटल पूर्णांक __init lboxre2_devices_setup(व्योम)
अणु
	u32 cf0_io_base;	/* Boot CF base address */
	pgprot_t prot;
	अचिन्हित दीर्घ paddrbase, psize;

	/* खोलो I/O area winकरोw */
	paddrbase = virt_to_phys((व्योम*)PA_AREA5_IO);
	psize = PAGE_SIZE;
	prot = PAGE_KERNEL_PCC(1, _PAGE_PCC_IO16);
	cf0_io_base = (u32)ioremap_prot(paddrbase, psize, pgprot_val(prot));
	अगर (!cf0_io_base) अणु
		prपूर्णांकk(KERN_ERR "%s : can't open CF I/O window!\n" , __func__ );
		वापस -ENOMEM;
	पूर्ण

	cf_ide_resources[0].start += cf0_io_base ;
	cf_ide_resources[0].end   += cf0_io_base ;
	cf_ide_resources[1].start += cf0_io_base ;
	cf_ide_resources[1].end   += cf0_io_base ;

	वापस platक्रमm_add_devices(lboxre2_devices,
			ARRAY_SIZE(lboxre2_devices));

पूर्ण
device_initcall(lboxre2_devices_setup);

/*
 * The Machine Vector
 */
अटल काष्ठा sh_machine_vector mv_lboxre2 __iniपंचांगv = अणु
	.mv_name		= "L-BOX RE2",
	.mv_init_irq		= init_lboxre2_IRQ,
पूर्ण;
