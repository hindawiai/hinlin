<शैली गुरु>
/*
 * amcore.c -- Support क्रम Sysam AMCORE खोलो board
 *
 * (C) Copyright 2016, Angelo Dureghello <angelo@sysam.it>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dm9000.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/i2c.h>

#समावेश <यंत्र/coldfire.h>
#समावेश <यंत्र/mcfsim.h>
#समावेश <यंत्र/पन.स>

#अगर IS_ENABLED(CONFIG_DM9000)

#घोषणा DM9000_IRQ	25
#घोषणा DM9000_ADDR	0x30000000

/*
 * DEVICES and related device RESOURCES
 */
अटल काष्ठा resource dm9000_resources[] = अणु
	/* physical address of the address रेजिस्टर (CMD [A2] to 0)*/
	[0] = अणु
		.start  = DM9000_ADDR,
		.end    = DM9000_ADDR,
		.flags  = IORESOURCE_MEM,
	पूर्ण,
	/*
	 * physical address of the data रेजिस्टर (CMD [A2] to 1),
	 * driver wants a range >=4 to assume a 32bit data bus
	 */
	[1] = अणु
		.start  = DM9000_ADDR + 4,
		.end    = DM9000_ADDR + 7,
		.flags  = IORESOURCE_MEM,
	पूर्ण,
	/* IRQ line the device's पूर्णांकerrupt pin is connected to */
	[2] = अणु
		.start  = DM9000_IRQ,
		.end    = DM9000_IRQ,
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा dm9000_plat_data dm9000_platdata = अणु
	.flags		= DM9000_PLATF_32BITONLY,
पूर्ण;

अटल काष्ठा platक्रमm_device dm9000_device = अणु
	.name           = "dm9000",
	.id             = 0,
	.num_resources  = ARRAY_SIZE(dm9000_resources),
	.resource       = dm9000_resources,
	.dev = अणु
		.platक्रमm_data = &dm9000_platdata,
	पूर्ण
पूर्ण;
#पूर्ण_अगर

अटल व्योम __init dm9000_pre_init(व्योम)
अणु
	/* Set the dm9000 पूर्णांकerrupt to be स्वतः-vectored */
	mcf_स्वतःvector(DM9000_IRQ);
पूर्ण

/*
 * Partitioning of parallel NOR flash (39VF3201B)
 */
अटल काष्ठा mtd_partition amcore_partitions[] = अणु
	अणु
		.name	= "U-Boot (128K)",
		.size	= 0x20000,
		.offset	= 0x0
	पूर्ण,
	अणु
		.name	= "Kernel+ROMfs (2994K)",
		.size	= 0x2E0000,
		.offset	= MTDPART_OFS_APPEND
	पूर्ण,
	अणु
		.name	= "Flash Free Space (1024K)",
		.size	= MTDPART_SIZ_FULL,
		.offset	= MTDPART_OFS_APPEND
	पूर्ण
पूर्ण;

अटल काष्ठा physmap_flash_data flash_data = अणु
	.parts		= amcore_partitions,
	.nr_parts	= ARRAY_SIZE(amcore_partitions),
	.width		= 2,
पूर्ण;

अटल काष्ठा resource flash_resource = अणु
	.start		= 0xffc00000,
	.end		= 0xffffffff,
	.flags		= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device flash_device = अणु
	.name		= "physmap-flash",
	.id		= -1,
	.resource	= &flash_resource,
	.num_resources	= 1,
	.dev		= अणु
		.platक्रमm_data	= &flash_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device rtc_device = अणु
	.name	= "rtc-ds1307",
	.id	= -1,
पूर्ण;

अटल काष्ठा i2c_board_info amcore_i2c_info[] __initdata = अणु
	अणु
		I2C_BOARD_INFO("ds1338", 0x68),
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *amcore_devices[] __initdata = अणु
#अगर IS_ENABLED(CONFIG_DM9000)
	&dm9000_device,
#पूर्ण_अगर
	&flash_device,
	&rtc_device,
पूर्ण;

अटल पूर्णांक __init init_amcore(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_DM9000)
	dm9000_pre_init();
#पूर्ण_अगर

	/* Add i2c RTC Dallas chip supprt */
	i2c_रेजिस्टर_board_info(0, amcore_i2c_info,
				ARRAY_SIZE(amcore_i2c_info));

	platक्रमm_add_devices(amcore_devices, ARRAY_SIZE(amcore_devices));

	वापस 0;
पूर्ण

arch_initcall(init_amcore);
