<शैली गुरु>
/*
 * Flash and EPROM on Hitachi Solution Engine and similar boards.
 *
 * (C) 2001 Red Hat, Inc.
 *
 * GPL'd
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/त्रुटिसं.स>

अटल काष्ठा mtd_info *flash_mtd;
अटल काष्ठा mtd_info *eprom_mtd;

काष्ठा map_info soleng_eprom_map = अणु
	.name = "Solution Engine EPROM",
	.size = 0x400000,
	.bankwidth = 4,
पूर्ण;

काष्ठा map_info soleng_flash_map = अणु
	.name = "Solution Engine FLASH",
	.size = 0x400000,
	.bankwidth = 4,
पूर्ण;

अटल स्थिर अक्षर * स्थिर probes[] = अणु "RedBoot", "cmdlinepart", शून्य पूर्ण;

अटल पूर्णांक __init init_soleng_maps(व्योम)
अणु
	/* First probe at offset 0 */
	soleng_flash_map.phys = 0;
	soleng_flash_map.virt = (व्योम __iomem *)P2SEGADDR(0);
	soleng_eprom_map.phys = 0x01000000;
	soleng_eprom_map.virt = (व्योम __iomem *)P1SEGADDR(0x01000000);
	simple_map_init(&soleng_eprom_map);
	simple_map_init(&soleng_flash_map);

	prपूर्णांकk(KERN_NOTICE "Probing for flash chips at 0x00000000:\n");
	flash_mtd = करो_map_probe("cfi_probe", &soleng_flash_map);
	अगर (!flash_mtd) अणु
		/* Not there. Try swapping */
		prपूर्णांकk(KERN_NOTICE "Probing for flash chips at 0x01000000:\n");
		soleng_flash_map.phys = 0x01000000;
		soleng_flash_map.virt = P2SEGADDR(0x01000000);
		soleng_eprom_map.phys = 0;
		soleng_eprom_map.virt = P1SEGADDR(0);
		flash_mtd = करो_map_probe("cfi_probe", &soleng_flash_map);
		अगर (!flash_mtd) अणु
			/* Eep. */
			prपूर्णांकk(KERN_NOTICE "Flash chips not detected at either possible location.\n");
			वापस -ENXIO;
		पूर्ण
	पूर्ण
	prपूर्णांकk(KERN_NOTICE "Solution Engine: Flash at 0x%pap, EPROM at 0x%pap\n",
	       &soleng_flash_map.phys,
	       &soleng_eprom_map.phys);
	flash_mtd->owner = THIS_MODULE;

	eprom_mtd = करो_map_probe("map_rom", &soleng_eprom_map);
	अगर (eprom_mtd) अणु
		eprom_mtd->owner = THIS_MODULE;
		mtd_device_रेजिस्टर(eprom_mtd, शून्य, 0);
	पूर्ण

	mtd_device_parse_रेजिस्टर(flash_mtd, probes, शून्य, शून्य, 0);

	वापस 0;
पूर्ण

अटल व्योम __निकास cleanup_soleng_maps(व्योम)
अणु
	अगर (eprom_mtd) अणु
		mtd_device_unरेजिस्टर(eprom_mtd);
		map_destroy(eprom_mtd);
	पूर्ण

	mtd_device_unरेजिस्टर(flash_mtd);
	map_destroy(flash_mtd);
पूर्ण

module_init(init_soleng_maps);
module_निकास(cleanup_soleng_maps);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Woodhouse <dwmw2@infradead.org>");
MODULE_DESCRIPTION("MTD map driver for Hitachi SolutionEngine (and similar) boards");

