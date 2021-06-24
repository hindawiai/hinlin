<शैली गुरु>
/*
 * Broadcom BCM63xx flash registration
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2008 Maxime Bizon <mbizon@मुक्तbox.fr>
 * Copyright (C) 2008 Florian Fainelli <florian@खोलोwrt.org>
 * Copyright (C) 2012 Jonas Gorski <jonas.gorski@gmail.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/physmap.h>

#समावेश <bcm63xx_cpu.h>
#समावेश <bcm63xx_dev_flash.h>
#समावेश <bcm63xx_regs.h>
#समावेश <bcm63xx_पन.स>

अटल काष्ठा mtd_partition mtd_partitions[] = अणु
	अणु
		.name		= "cfe",
		.offset		= 0x0,
		.size		= 0x40000,
	पूर्ण
पूर्ण;

अटल स्थिर अक्षर *bcm63xx_part_types[] = अणु "bcm63xxpart", शून्य पूर्ण;

अटल काष्ठा physmap_flash_data flash_data = अणु
	.width			= 2,
	.parts			= mtd_partitions,
	.part_probe_types	= bcm63xx_part_types,
पूर्ण;

अटल काष्ठा resource mtd_resources[] = अणु
	अणु
		.start		= 0,	/* filled at runसमय */
		.end		= 0,	/* filled at runसमय */
		.flags		= IORESOURCE_MEM,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device mtd_dev = अणु
	.name			= "physmap-flash",
	.resource		= mtd_resources,
	.num_resources		= ARRAY_SIZE(mtd_resources),
	.dev			= अणु
		.platक्रमm_data	= &flash_data,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init bcm63xx_detect_flash_type(व्योम)
अणु
	u32 val;

	चयन (bcm63xx_get_cpu_id()) अणु
	हाल BCM6328_CPU_ID:
		val = bcm_misc_पढ़ोl(MISC_STRAPBUS_6328_REG);
		अगर (val & STRAPBUS_6328_BOOT_SEL_SERIAL)
			वापस BCM63XX_FLASH_TYPE_SERIAL;
		अन्यथा
			वापस BCM63XX_FLASH_TYPE_न_अंकD;
	हाल BCM6338_CPU_ID:
	हाल BCM6345_CPU_ID:
	हाल BCM6348_CPU_ID:
		/* no way to स्वतः detect so assume parallel */
		वापस BCM63XX_FLASH_TYPE_PARALLEL;
	हाल BCM3368_CPU_ID:
	हाल BCM6358_CPU_ID:
		val = bcm_gpio_पढ़ोl(GPIO_STRAPBUS_REG);
		अगर (val & STRAPBUS_6358_BOOT_SEL_PARALLEL)
			वापस BCM63XX_FLASH_TYPE_PARALLEL;
		अन्यथा
			वापस BCM63XX_FLASH_TYPE_SERIAL;
	हाल BCM6362_CPU_ID:
		val = bcm_misc_पढ़ोl(MISC_STRAPBUS_6362_REG);
		अगर (val & STRAPBUS_6362_BOOT_SEL_SERIAL)
			वापस BCM63XX_FLASH_TYPE_SERIAL;
		अन्यथा
			वापस BCM63XX_FLASH_TYPE_न_अंकD;
	हाल BCM6368_CPU_ID:
		val = bcm_gpio_पढ़ोl(GPIO_STRAPBUS_REG);
		चयन (val & STRAPBUS_6368_BOOT_SEL_MASK) अणु
		हाल STRAPBUS_6368_BOOT_SEL_न_अंकD:
			वापस BCM63XX_FLASH_TYPE_न_अंकD;
		हाल STRAPBUS_6368_BOOT_SEL_SERIAL:
			वापस BCM63XX_FLASH_TYPE_SERIAL;
		हाल STRAPBUS_6368_BOOT_SEL_PARALLEL:
			वापस BCM63XX_FLASH_TYPE_PARALLEL;
		पूर्ण
		fallthrough;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक __init bcm63xx_flash_रेजिस्टर(व्योम)
अणु
	पूर्णांक flash_type;
	u32 val;

	flash_type = bcm63xx_detect_flash_type();

	चयन (flash_type) अणु
	हाल BCM63XX_FLASH_TYPE_PARALLEL:
		/* पढ़ो base address of boot chip select (0) */
		val = bcm_mpi_पढ़ोl(MPI_CSBASE_REG(0));
		val &= MPI_CSBASE_BASE_MASK;

		mtd_resources[0].start = val;
		mtd_resources[0].end = 0x1FFFFFFF;

		वापस platक्रमm_device_रेजिस्टर(&mtd_dev);
	हाल BCM63XX_FLASH_TYPE_SERIAL:
		pr_warn("unsupported serial flash detected\n");
		वापस -ENODEV;
	हाल BCM63XX_FLASH_TYPE_न_अंकD:
		pr_warn("unsupported NAND flash detected\n");
		वापस -ENODEV;
	शेष:
		pr_err("flash detection failed for BCM%x: %d\n",
		       bcm63xx_get_cpu_id(), flash_type);
		वापस -ENODEV;
	पूर्ण
पूर्ण
