<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/boards/landisk/setup.c
 *
 * I-O DATA Device, Inc. LANDISK Support.
 *
 * Copyright (C) 2000 Kazumoto Kojima
 * Copyright (C) 2002 Paul Mundt
 * Copylight (C) 2002 Atom Create Engineering Co., Ltd.
 * Copyright (C) 2005-2007 kogiidena
 */
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ata_platक्रमm.h>
#समावेश <linux/pm.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र/machvec.h>
#समावेश <mach-landisk/mach/iodata_landisk.h>
#समावेश <यंत्र/पन.स>

अटल व्योम landisk_घातer_off(व्योम)
अणु
	__raw_ग_लिखोb(0x01, PA_SHUTDOWN);
पूर्ण

अटल काष्ठा resource cf_ide_resources[3];

अटल काष्ठा pata_platक्रमm_info pata_info = अणु
	.ioport_shअगरt	= 1,
पूर्ण;

अटल काष्ठा platक्रमm_device cf_ide_device = अणु
	.name		= "pata_platform",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(cf_ide_resources),
	.resource	= cf_ide_resources,
	.dev		= अणु
		.platक्रमm_data = &pata_info,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device rtc_device = अणु
	.name		= "rs5c313",
	.id		= -1,
पूर्ण;

अटल काष्ठा platक्रमm_device *landisk_devices[] __initdata = अणु
	&cf_ide_device,
	&rtc_device,
पूर्ण;

अटल पूर्णांक __init landisk_devices_setup(व्योम)
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
	cf_ide_resources[0].start = (अचिन्हित दीर्घ)cf_ide_base + 0x40;
	cf_ide_resources[0].end   = (अचिन्हित दीर्घ)cf_ide_base + 0x40 + 0x0f;
	cf_ide_resources[0].flags = IORESOURCE_IO;
	cf_ide_resources[1].start = (अचिन्हित दीर्घ)cf_ide_base + 0x2c;
	cf_ide_resources[1].end   = (अचिन्हित दीर्घ)cf_ide_base + 0x2c + 0x03;
	cf_ide_resources[1].flags = IORESOURCE_IO;
	cf_ide_resources[2].start = IRQ_FATA;
	cf_ide_resources[2].flags = IORESOURCE_IRQ;

	वापस platक्रमm_add_devices(landisk_devices,
				    ARRAY_SIZE(landisk_devices));
पूर्ण

device_initcall(landisk_devices_setup);

अटल व्योम __init landisk_setup(अक्षर **cmdline_p)
अणु
	/* I/O port identity mapping */
	__set_io_port_base(0);

	/* LED ON */
	__raw_ग_लिखोb(__raw_पढ़ोb(PA_LED) | 0x03, PA_LED);

	prपूर्णांकk(KERN_INFO "I-O DATA DEVICE, INC. \"LANDISK Series\" support.\n");
	pm_घातer_off = landisk_घातer_off;
पूर्ण

/*
 * The Machine Vector
 */
अटल काष्ठा sh_machine_vector mv_landisk __iniपंचांगv = अणु
	.mv_name = "LANDISK",
	.mv_setup = landisk_setup,
	.mv_init_irq = init_landisk_IRQ,
पूर्ण;
