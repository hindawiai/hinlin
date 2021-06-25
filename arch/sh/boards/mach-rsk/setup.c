<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas Technology Europe RSK+ Support.
 *
 * Copyright (C) 2008 Paul Mundt
 * Copyright (C) 2008 Peter Grअगरfin <pgrअगरfin@mpc-data.co.uk>
 */
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/regulator/fixed.h>
#समावेश <linux/regulator/machine.h>
#समावेश <यंत्र/machvec.h>
#समावेश <यंत्र/पन.स>

/* Dummy supplies, where voltage करोesn't matter */
अटल काष्ठा regulator_consumer_supply dummy_supplies[] = अणु
	REGULATOR_SUPPLY("vddvario", "smsc911x"),
	REGULATOR_SUPPLY("vdd33a", "smsc911x"),
पूर्ण;

अटल काष्ठा mtd_partition rsk_partitions[] = अणु
	अणु
		.name		= "Bootloader",
		.offset		= 0x00000000,
		.size		= 0x00040000,
		.mask_flags	= MTD_WRITEABLE,
	पूर्ण, अणु
		.name		= "Kernel",
		.offset		= MTDPART_OFS_NXTBLK,
		.size		= 0x001c0000,
	पूर्ण, अणु
		.name		= "Flash_FS",
		.offset		= MTDPART_OFS_NXTBLK,
		.size		= MTDPART_SIZ_FULL,
	पूर्ण
पूर्ण;

अटल काष्ठा physmap_flash_data flash_data = अणु
	.parts			= rsk_partitions,
	.nr_parts		= ARRAY_SIZE(rsk_partitions),
	.width			= 2,
पूर्ण;

अटल काष्ठा resource flash_resource = अणु
	.start		= 0x20000000,
	.end		= 0x20400000,
	.flags		= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device flash_device = अणु
	.name		= "physmap-flash",
	.id		= -1,
	.resource	= &flash_resource,
	.num_resources	= 1,
	.dev		= अणु
		.platक्रमm_data = &flash_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *rsk_devices[] __initdata = अणु
	&flash_device,
पूर्ण;

अटल पूर्णांक __init rsk_devices_setup(व्योम)
अणु
	regulator_रेजिस्टर_fixed(0, dummy_supplies, ARRAY_SIZE(dummy_supplies));

	वापस platक्रमm_add_devices(rsk_devices,
				    ARRAY_SIZE(rsk_devices));
पूर्ण
device_initcall(rsk_devices_setup);

/*
 * The Machine Vector
 */
अटल काष्ठा sh_machine_vector mv_rsk __iniपंचांगv = अणु
	.mv_name        = "RSK+",
पूर्ण;
