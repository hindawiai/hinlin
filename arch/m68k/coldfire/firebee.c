<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/***************************************************************************/

/*
 *	firebee.c -- extra startup code support क्रम the FireBee boards
 *
 *	Copyright (C) 2011, Greg Ungerer (gerg@snapgear.com)
 */

/***************************************************************************/

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <यंत्र/coldfire.h>
#समावेश <यंत्र/mcfsim.h>

/***************************************************************************/

/*
 *	8MB of NOR flash fitted to the FireBee board.
 */
#घोषणा	FLASH_PHYS_ADDR		0xe0000000	/* Physical address of flash */
#घोषणा	FLASH_PHYS_SIZE		0x00800000	/* Size of flash */

#घोषणा	PART_BOOT_START		0x00000000	/* Start at bottom of flash */
#घोषणा	PART_BOOT_SIZE		0x00040000	/* 256k in size */
#घोषणा	PART_IMAGE_START	0x00040000	/* Start after boot loader */
#घोषणा	PART_IMAGE_SIZE		0x006c0000	/* Most of flash */
#घोषणा	PART_FPGA_START		0x00700000	/* Start at offset 7MB */
#घोषणा	PART_FPGA_SIZE		0x00100000	/* 1MB in size */

अटल काष्ठा mtd_partition firebee_flash_parts[] = अणु
	अणु
		.name	= "dBUG",
		.offset	= PART_BOOT_START,
		.size	= PART_BOOT_SIZE,
	पूर्ण,
	अणु
		.name	= "FPGA",
		.offset	= PART_FPGA_START,
		.size	= PART_FPGA_SIZE,
	पूर्ण,
	अणु
		.name	= "image",
		.offset	= PART_IMAGE_START,
		.size	= PART_IMAGE_SIZE,
	पूर्ण,
पूर्ण;

अटल काष्ठा physmap_flash_data firebee_flash_data = अणु
	.width		= 2,
	.nr_parts	= ARRAY_SIZE(firebee_flash_parts),
	.parts		= firebee_flash_parts,
पूर्ण;

अटल काष्ठा resource firebee_flash_resource = अणु
	.start		= FLASH_PHYS_ADDR,
	.end		= FLASH_PHYS_ADDR + FLASH_PHYS_SIZE,
	.flags		= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device firebee_flash = अणु
	.name		= "physmap-flash",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data = &firebee_flash_data,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &firebee_flash_resource,
पूर्ण;

/***************************************************************************/

अटल पूर्णांक __init init_firebee(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&firebee_flash);
	वापस 0;
पूर्ण

arch_initcall(init_firebee);

/***************************************************************************/
