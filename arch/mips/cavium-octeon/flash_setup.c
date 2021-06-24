<शैली गुरु>
/*
 *   Octeon Bootbus flash setup
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2007, 2008 Cavium Networks
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/mtd/partitions.h>

#समावेश <यंत्र/octeon/octeon.h>

अटल काष्ठा map_info flash_map;
अटल काष्ठा mtd_info *mymtd;
अटल स्थिर अक्षर *part_probe_types[] = अणु
	"cmdlinepart",
#अगर_घोषित CONFIG_MTD_REDBOOT_PARTS
	"RedBoot",
#पूर्ण_अगर
	शून्य
पूर्ण;

अटल map_word octeon_flash_map_पढ़ो(काष्ठा map_info *map, अचिन्हित दीर्घ ofs)
अणु
	map_word r;

	करोwn(&octeon_bootbus_sem);
	r = अंतरभूत_map_पढ़ो(map, ofs);
	up(&octeon_bootbus_sem);

	वापस r;
पूर्ण

अटल व्योम octeon_flash_map_ग_लिखो(काष्ठा map_info *map, स्थिर map_word datum,
				   अचिन्हित दीर्घ ofs)
अणु
	करोwn(&octeon_bootbus_sem);
	अंतरभूत_map_ग_लिखो(map, datum, ofs);
	up(&octeon_bootbus_sem);
पूर्ण

अटल व्योम octeon_flash_map_copy_from(काष्ठा map_info *map, व्योम *to,
				       अचिन्हित दीर्घ from, sमाप_प्रकार len)
अणु
	करोwn(&octeon_bootbus_sem);
	अंतरभूत_map_copy_from(map, to, from, len);
	up(&octeon_bootbus_sem);
पूर्ण

अटल व्योम octeon_flash_map_copy_to(काष्ठा map_info *map, अचिन्हित दीर्घ to,
				     स्थिर व्योम *from, sमाप_प्रकार len)
अणु
	करोwn(&octeon_bootbus_sem);
	अंतरभूत_map_copy_to(map, to, from, len);
	up(&octeon_bootbus_sem);
पूर्ण

/**
 * Module/ driver initialization.
 *
 * Returns Zero on success
 */
अटल पूर्णांक octeon_flash_probe(काष्ठा platक्रमm_device *pdev)
अणु
	जोड़ cvmx_mio_boot_reg_cfgx region_cfg;
	u32 cs;
	पूर्णांक r;
	काष्ठा device_node *np = pdev->dev.of_node;

	r = of_property_पढ़ो_u32(np, "reg", &cs);
	अगर (r)
		वापस r;

	/*
	 * Read the bootbus region 0 setup to determine the base
	 * address of the flash.
	 */
	region_cfg.u64 = cvmx_पढ़ो_csr(CVMX_MIO_BOOT_REG_CFGX(cs));
	अगर (region_cfg.s.en) अणु
		/*
		 * The bootloader always takes the flash and sets its
		 * address so the entire flash fits below
		 * 0x1fc00000. This way the flash aliases to
		 * 0x1fc00000 क्रम booting. Software can access the
		 * full flash at the true address, जबतक core boot can
		 * access 4MB.
		 */
		/* Use this name so old part lines work */
		flash_map.name = "phys_mapped_flash";
		flash_map.phys = region_cfg.s.base << 16;
		flash_map.size = 0x1fc00000 - flash_map.phys;
		/* 8-bit bus (0 + 1) or 16-bit bus (1 + 1) */
		flash_map.bankwidth = region_cfg.s.width + 1;
		flash_map.virt = ioremap(flash_map.phys, flash_map.size);
		pr_notice("Bootbus flash: Setting flash for %luMB flash at "
			  "0x%08llx\n", flash_map.size >> 20, flash_map.phys);
		WARN_ON(!map_bankwidth_supported(flash_map.bankwidth));
		flash_map.पढ़ो = octeon_flash_map_पढ़ो;
		flash_map.ग_लिखो = octeon_flash_map_ग_लिखो;
		flash_map.copy_from = octeon_flash_map_copy_from;
		flash_map.copy_to = octeon_flash_map_copy_to;
		mymtd = करो_map_probe("cfi_probe", &flash_map);
		अगर (mymtd) अणु
			mymtd->owner = THIS_MODULE;
			mtd_device_parse_रेजिस्टर(mymtd, part_probe_types,
						  शून्य, शून्य, 0);
		पूर्ण अन्यथा अणु
			pr_err("Failed to register MTD device for flash\n");
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_flash_match[] = अणु
	अणु
		.compatible	= "cfi-flash",
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_flash_match);

अटल काष्ठा platक्रमm_driver of_flash_driver = अणु
	.driver = अणु
		.name = "octeon-of-flash",
		.of_match_table = of_flash_match,
	पूर्ण,
	.probe		= octeon_flash_probe,
पूर्ण;

अटल पूर्णांक octeon_flash_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&of_flash_driver);
पूर्ण
late_initcall(octeon_flash_init);

MODULE_LICENSE("GPL");
