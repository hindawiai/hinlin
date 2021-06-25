<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright 2007 Simtec Electronics
//	http://www.simtec.co.uk/products/EB2410ITX/
//	http://armlinux.simtec.co.uk/
//	Ben Dooks <ben@simtec.co.uk>

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ata_platक्रमm.h>

#समावेश <यंत्र/mach-types.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश "map.h"
#समावेश <mach/irqs.h>

#समावेश "bast.h"

/* IDE ports */

अटल काष्ठा pata_platक्रमm_info bast_ide_platdata = अणु
	.ioport_shअगरt	= 5,
पूर्ण;

अटल काष्ठा resource bast_ide0_resource[] = अणु
	[0] = DEFINE_RES_MEM(BAST_IDE_CS + BAST_PA_IDEPRI, 8 * 0x20),
	[1] = DEFINE_RES_MEM(BAST_IDE_CS + BAST_PA_IDEPRIAUX + (6 * 0x20), 0x20),
	[2] = DEFINE_RES_IRQ(BAST_IRQ_IDE0),
पूर्ण;

अटल काष्ठा platक्रमm_device bast_device_ide0 = अणु
	.name		= "pata_platform",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(bast_ide0_resource),
	.resource	= bast_ide0_resource,
	.dev		= अणु
		.platक्रमm_data = &bast_ide_platdata,
		.coherent_dma_mask = ~0,
	पूर्ण

पूर्ण;

अटल काष्ठा resource bast_ide1_resource[] = अणु
	[0] = DEFINE_RES_MEM(BAST_IDE_CS + BAST_PA_IDESEC, 8 * 0x20),
	[1] = DEFINE_RES_MEM(BAST_IDE_CS + BAST_PA_IDESECAUX + (6 * 0x20), 0x20),
	[2] = DEFINE_RES_IRQ(BAST_IRQ_IDE1),
पूर्ण;

अटल काष्ठा platक्रमm_device bast_device_ide1 = अणु
	.name		= "pata_platform",
	.id		= 1,
	.num_resources	= ARRAY_SIZE(bast_ide1_resource),
	.resource	= bast_ide1_resource,
	.dev		= अणु
		.platक्रमm_data = &bast_ide_platdata,
		.coherent_dma_mask = ~0,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device *bast_ide_devices[] __initdata = अणु
	&bast_device_ide0,
	&bast_device_ide1,
पूर्ण;

अटल __init पूर्णांक bast_ide_init(व्योम)
अणु
	अगर (machine_is_bast() || machine_is_vr1000())
		वापस platक्रमm_add_devices(bast_ide_devices,
					    ARRAY_SIZE(bast_ide_devices));

	वापस 0;
पूर्ण

fs_initcall(bast_ide_init);
