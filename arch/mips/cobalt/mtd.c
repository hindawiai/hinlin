<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Registration of Cobalt MTD device.
 *
 *  Copyright (C) 2006  Yoichi Yuasa <yuasa@linux-mips.org>
 */
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/physmap.h>

अटल काष्ठा mtd_partition cobalt_mtd_partitions[] = अणु
	अणु
		.name	= "firmware",
		.offset = 0x0,
		.size	= 0x80000,
	पूर्ण,
पूर्ण;

अटल काष्ठा physmap_flash_data cobalt_flash_data = अणु
	.width		= 1,
	.nr_parts	= 1,
	.parts		= cobalt_mtd_partitions,
पूर्ण;

अटल काष्ठा resource cobalt_mtd_resource = अणु
	.start	= 0x1fc00000,
	.end	= 0x1fc7ffff,
	.flags	= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device cobalt_mtd = अणु
	.name		= "physmap-flash",
	.dev		= अणु
		.platक्रमm_data	= &cobalt_flash_data,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &cobalt_mtd_resource,
पूर्ण;

अटल पूर्णांक __init cobalt_mtd_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&cobalt_mtd);

	वापस 0;
पूर्ण
device_initcall(cobalt_mtd_init);
