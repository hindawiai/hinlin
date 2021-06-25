<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Renesas Europe EDOSK7760 Board Support
 *
 * Copyright (C) 2008 SPES Societa' Progettazione Elettronica e Software Ltd.
 * Author: Luca Santini <luca.santini@spesonline.com>
 */
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/smc91x.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <यंत्र/machvec.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/i2c-sh7760.h>
#समावेश <linux/sizes.h>

/* Bus state controller रेजिस्टरs क्रम CS4 area */
#घोषणा BSC_CS4BCR	0xA4FD0010
#घोषणा BSC_CS4WCR	0xA4FD0030

#घोषणा SMC_IOBASE	0xA2000000
#घोषणा SMC_IO_OFFSET	0x300
#घोषणा SMC_IOADDR	(SMC_IOBASE + SMC_IO_OFFSET)

/* NOR flash */
अटल काष्ठा mtd_partition eकरोsk7760_nor_flash_partitions[] = अणु
	अणु
		.name = "bootloader",
		.offset = 0,
		.size = SZ_256K,
		.mask_flags = MTD_WRITEABLE,	/* Read-only */
	पूर्ण, अणु
		.name = "kernel",
		.offset = MTDPART_OFS_APPEND,
		.size = SZ_2M,
	पूर्ण, अणु
		.name = "fs",
		.offset = MTDPART_OFS_APPEND,
		.size = (26 << 20),
	पूर्ण, अणु
		.name = "other",
		.offset = MTDPART_OFS_APPEND,
		.size = MTDPART_SIZ_FULL,
	पूर्ण,
पूर्ण;

अटल काष्ठा physmap_flash_data eकरोsk7760_nor_flash_data = अणु
	.width		= 4,
	.parts		= eकरोsk7760_nor_flash_partitions,
	.nr_parts	= ARRAY_SIZE(eकरोsk7760_nor_flash_partitions),
पूर्ण;

अटल काष्ठा resource eकरोsk7760_nor_flash_resources[] = अणु
	[0] = अणु
		.name	= "NOR Flash",
		.start	= 0x00000000,
		.end	= 0x00000000 + SZ_32M - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device eकरोsk7760_nor_flash_device = अणु
	.name		= "physmap-flash",
	.resource	= eकरोsk7760_nor_flash_resources,
	.num_resources	= ARRAY_SIZE(eकरोsk7760_nor_flash_resources),
	.dev		= अणु
		.platक्रमm_data = &eकरोsk7760_nor_flash_data,
	पूर्ण,
पूर्ण;

/* i2c initialization functions */
अटल काष्ठा sh7760_i2c_platdata i2c_pd = अणु
	.speed_khz	= 400,
पूर्ण;

अटल काष्ठा resource sh7760_i2c1_res[] = अणु
	अणु
		.start	= SH7760_I2C1_MMIO,
		.end	= SH7760_I2C1_MMIOEND,
		.flags	= IORESOURCE_MEM,
	पूर्ण,अणु
		.start	= evt2irq(0x9e0),
		.end	= evt2irq(0x9e0),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device sh7760_i2c1_dev = अणु
	.dev    = अणु
		.platक्रमm_data	= &i2c_pd,
	पूर्ण,

	.name		= SH7760_I2C_DEVNAME,
	.id		= 1,
	.resource	= sh7760_i2c1_res,
	.num_resources	= ARRAY_SIZE(sh7760_i2c1_res),
पूर्ण;

अटल काष्ठा resource sh7760_i2c0_res[] = अणु
	अणु
		.start	= SH7760_I2C0_MMIO,
		.end	= SH7760_I2C0_MMIOEND,
		.flags	= IORESOURCE_MEM,
	पूर्ण, अणु
		.start	= evt2irq(0x9c0),
		.end	= evt2irq(0x9c0),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device sh7760_i2c0_dev = अणु
	.dev    = अणु
		.platक्रमm_data	= &i2c_pd,
	पूर्ण,
	.name		= SH7760_I2C_DEVNAME,
	.id		= 0,
	.resource	= sh7760_i2c0_res,
	.num_resources	= ARRAY_SIZE(sh7760_i2c0_res),
पूर्ण;

/* eth initialization functions */
अटल काष्ठा smc91x_platdata smc91x_info = अणु
	.flags = SMC91X_USE_16BIT | SMC91X_IO_SHIFT_1 | IORESOURCE_IRQ_LOWLEVEL,
पूर्ण;

अटल काष्ठा resource smc91x_res[] = अणु
	[0] = अणु
		.start	= SMC_IOADDR,
		.end	= SMC_IOADDR + SZ_32 - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= evt2irq(0x2a0),
		.end	= evt2irq(0x2a0),
		.flags	= IORESOURCE_IRQ ,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device smc91x_dev = अणु
	.name		= "smc91x",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(smc91x_res),
	.resource	= smc91x_res,

	.dev	= अणु
		.platक्रमm_data	= &smc91x_info,
	पूर्ण,
पूर्ण;

/* platक्रमm init code */
अटल काष्ठा platक्रमm_device *eकरोsk7760_devices[] __initdata = अणु
	&smc91x_dev,
	&eकरोsk7760_nor_flash_device,
	&sh7760_i2c0_dev,
	&sh7760_i2c1_dev,
पूर्ण;

अटल पूर्णांक __init init_eकरोsk7760_devices(व्योम)
अणु
	plat_irq_setup_pins(IRQ_MODE_IRQ);

	वापस platक्रमm_add_devices(eकरोsk7760_devices,
				    ARRAY_SIZE(eकरोsk7760_devices));
पूर्ण
device_initcall(init_eकरोsk7760_devices);

/*
 * The Machine Vector
 */
काष्ठा sh_machine_vector mv_eकरोsk7760 __iniपंचांगv = अणु
	.mv_name	= "EDOSK7760",
पूर्ण;
