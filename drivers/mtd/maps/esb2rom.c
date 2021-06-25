<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * esb2rom.c
 *
 * Normal mappings of flash chips in physical memory
 * through the Intel ESB2 Southbridge.
 *
 * This was derived from ichxrom.c in May 2006 by
 *	Lew Glendenning <lglendenning@lnxi.com>
 *
 * Eric Biederman, of course, was a major help in this efक्रमt.
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/cfi.h>
#समावेश <linux/mtd/flashchip.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/list.h>

#घोषणा MOD_NAME KBUILD_BASENAME

#घोषणा ADDRESS_NAME_LEN 18

#घोषणा ROM_PROBE_STEP_SIZE (64*1024) /* 64KiB */

#घोषणा BIOS_CNTL		0xDC
#घोषणा BIOS_LOCK_ENABLE	0x02
#घोषणा BIOS_WRITE_ENABLE	0x01

/* This became a 16-bit रेजिस्टर, and EN2 has disappeared */
#घोषणा FWH_DEC_EN1	0xD8
#घोषणा FWH_F8_EN	0x8000
#घोषणा FWH_F0_EN	0x4000
#घोषणा FWH_E8_EN	0x2000
#घोषणा FWH_E0_EN	0x1000
#घोषणा FWH_D8_EN	0x0800
#घोषणा FWH_D0_EN	0x0400
#घोषणा FWH_C8_EN	0x0200
#घोषणा FWH_C0_EN	0x0100
#घोषणा FWH_LEGACY_F_EN	0x0080
#घोषणा FWH_LEGACY_E_EN	0x0040
/* reserved  0x0020 and 0x0010 */
#घोषणा FWH_70_EN	0x0008
#घोषणा FWH_60_EN	0x0004
#घोषणा FWH_50_EN	0x0002
#घोषणा FWH_40_EN	0x0001

/* these are 32-bit values */
#घोषणा FWH_SEL1	0xD0
#घोषणा FWH_SEL2	0xD4

#घोषणा FWH_8MiB	(FWH_F8_EN | FWH_F0_EN | FWH_E8_EN | FWH_E0_EN | \
			 FWH_D8_EN | FWH_D0_EN | FWH_C8_EN | FWH_C0_EN | \
			 FWH_70_EN | FWH_60_EN | FWH_50_EN | FWH_40_EN)

#घोषणा FWH_7MiB	(FWH_F8_EN | FWH_F0_EN | FWH_E8_EN | FWH_E0_EN | \
			 FWH_D8_EN | FWH_D0_EN | FWH_C8_EN | FWH_C0_EN | \
			 FWH_70_EN | FWH_60_EN | FWH_50_EN)

#घोषणा FWH_6MiB	(FWH_F8_EN | FWH_F0_EN | FWH_E8_EN | FWH_E0_EN | \
			 FWH_D8_EN | FWH_D0_EN | FWH_C8_EN | FWH_C0_EN | \
			 FWH_70_EN | FWH_60_EN)

#घोषणा FWH_5MiB	(FWH_F8_EN | FWH_F0_EN | FWH_E8_EN | FWH_E0_EN | \
			 FWH_D8_EN | FWH_D0_EN | FWH_C8_EN | FWH_C0_EN | \
			 FWH_70_EN)

#घोषणा FWH_4MiB	(FWH_F8_EN | FWH_F0_EN | FWH_E8_EN | FWH_E0_EN | \
			 FWH_D8_EN | FWH_D0_EN | FWH_C8_EN | FWH_C0_EN)

#घोषणा FWH_3_5MiB	(FWH_F8_EN | FWH_F0_EN | FWH_E8_EN | FWH_E0_EN | \
			 FWH_D8_EN | FWH_D0_EN | FWH_C8_EN)

#घोषणा FWH_3MiB	(FWH_F8_EN | FWH_F0_EN | FWH_E8_EN | FWH_E0_EN | \
			 FWH_D8_EN | FWH_D0_EN)

#घोषणा FWH_2_5MiB	(FWH_F8_EN | FWH_F0_EN | FWH_E8_EN | FWH_E0_EN | \
			 FWH_D8_EN)

#घोषणा FWH_2MiB	(FWH_F8_EN | FWH_F0_EN | FWH_E8_EN | FWH_E0_EN)

#घोषणा FWH_1_5MiB	(FWH_F8_EN | FWH_F0_EN | FWH_E8_EN)

#घोषणा FWH_1MiB	(FWH_F8_EN | FWH_F0_EN)

#घोषणा FWH_0_5MiB	(FWH_F8_EN)


काष्ठा esb2rom_winकरोw अणु
	व्योम __iomem* virt;
	अचिन्हित दीर्घ phys;
	अचिन्हित दीर्घ size;
	काष्ठा list_head maps;
	काष्ठा resource rsrc;
	काष्ठा pci_dev *pdev;
पूर्ण;

काष्ठा esb2rom_map_info अणु
	काष्ठा list_head list;
	काष्ठा map_info map;
	काष्ठा mtd_info *mtd;
	काष्ठा resource rsrc;
	अक्षर map_name[माप(MOD_NAME) + 2 + ADDRESS_NAME_LEN];
पूर्ण;

अटल काष्ठा esb2rom_winकरोw esb2rom_winकरोw = अणु
	.maps = LIST_HEAD_INIT(esb2rom_winकरोw.maps),
पूर्ण;

अटल व्योम esb2rom_cleanup(काष्ठा esb2rom_winकरोw *winकरोw)
अणु
	काष्ठा esb2rom_map_info *map, *scratch;
	u8 byte;

	/* Disable ग_लिखोs through the rom winकरोw */
	pci_पढ़ो_config_byte(winकरोw->pdev, BIOS_CNTL, &byte);
	pci_ग_लिखो_config_byte(winकरोw->pdev, BIOS_CNTL,
		byte & ~BIOS_WRITE_ENABLE);

	/* Free all of the mtd devices */
	list_क्रम_each_entry_safe(map, scratch, &winकरोw->maps, list) अणु
		अगर (map->rsrc.parent)
			release_resource(&map->rsrc);
		mtd_device_unरेजिस्टर(map->mtd);
		map_destroy(map->mtd);
		list_del(&map->list);
		kमुक्त(map);
	पूर्ण
	अगर (winकरोw->rsrc.parent)
		release_resource(&winकरोw->rsrc);
	अगर (winकरोw->virt) अणु
		iounmap(winकरोw->virt);
		winकरोw->virt = शून्य;
		winकरोw->phys = 0;
		winकरोw->size = 0;
	पूर्ण
	pci_dev_put(winकरोw->pdev);
पूर्ण

अटल पूर्णांक __init esb2rom_init_one(काष्ठा pci_dev *pdev,
				   स्थिर काष्ठा pci_device_id *ent)
अणु
	अटल अक्षर *rom_probe_types[] = अणु "cfi_probe", "jedec_probe", शून्य पूर्ण;
	काष्ठा esb2rom_winकरोw *winकरोw = &esb2rom_winकरोw;
	काष्ठा esb2rom_map_info *map = शून्य;
	अचिन्हित दीर्घ map_top;
	u8 byte;
	u16 word;

	/* For now I just handle the ecb2 and I assume there
	 * are not a lot of resources up at the top of the address
	 * space.  It is possible to handle other devices in the
	 * top 16MiB but it is very painful.  Also since
	 * you can only really attach a FWH to an ICHX there
	 * a number of simplअगरications you can make.
	 *
	 * Also you can page firmware hubs अगर an 8MiB winकरोw isn't enough
	 * but करोn't currently handle that हाल either.
	 */
	winकरोw->pdev = pci_dev_get(pdev);

	/* RLG:  experiment 2.  Force the winकरोw रेजिस्टरs to the widest values */

/*
	pci_पढ़ो_config_word(pdev, FWH_DEC_EN1, &word);
	prपूर्णांकk(KERN_DEBUG "Original FWH_DEC_EN1 : %x\n", word);
	pci_ग_लिखो_config_byte(pdev, FWH_DEC_EN1, 0xff);
	pci_पढ़ो_config_byte(pdev, FWH_DEC_EN1, &byte);
	prपूर्णांकk(KERN_DEBUG "New FWH_DEC_EN1 : %x\n", byte);

	pci_पढ़ो_config_byte(pdev, FWH_DEC_EN2, &byte);
	prपूर्णांकk(KERN_DEBUG "Original FWH_DEC_EN2 : %x\n", byte);
	pci_ग_लिखो_config_byte(pdev, FWH_DEC_EN2, 0x0f);
	pci_पढ़ो_config_byte(pdev, FWH_DEC_EN2, &byte);
	prपूर्णांकk(KERN_DEBUG "New FWH_DEC_EN2 : %x\n", byte);
*/

	/* Find a region continuous to the end of the ROM winकरोw  */
	winकरोw->phys = 0;
	pci_पढ़ो_config_word(pdev, FWH_DEC_EN1, &word);
	prपूर्णांकk(KERN_DEBUG "pci_read_config_word : %x\n", word);

	अगर ((word & FWH_8MiB) == FWH_8MiB)
		winकरोw->phys = 0xff400000;
	अन्यथा अगर ((word & FWH_7MiB) == FWH_7MiB)
		winकरोw->phys = 0xff500000;
	अन्यथा अगर ((word & FWH_6MiB) == FWH_6MiB)
		winकरोw->phys = 0xff600000;
	अन्यथा अगर ((word & FWH_5MiB) == FWH_5MiB)
		winकरोw->phys = 0xFF700000;
	अन्यथा अगर ((word & FWH_4MiB) == FWH_4MiB)
		winकरोw->phys = 0xffc00000;
	अन्यथा अगर ((word & FWH_3_5MiB) == FWH_3_5MiB)
		winकरोw->phys = 0xffc80000;
	अन्यथा अगर ((word & FWH_3MiB) == FWH_3MiB)
		winकरोw->phys = 0xffd00000;
	अन्यथा अगर ((word & FWH_2_5MiB) == FWH_2_5MiB)
		winकरोw->phys = 0xffd80000;
	अन्यथा अगर ((word & FWH_2MiB) == FWH_2MiB)
		winकरोw->phys = 0xffe00000;
	अन्यथा अगर ((word & FWH_1_5MiB) == FWH_1_5MiB)
		winकरोw->phys = 0xffe80000;
	अन्यथा अगर ((word & FWH_1MiB) == FWH_1MiB)
		winकरोw->phys = 0xfff00000;
	अन्यथा अगर ((word & FWH_0_5MiB) == FWH_0_5MiB)
		winकरोw->phys = 0xfff80000;

	अगर (winकरोw->phys == 0) अणु
		prपूर्णांकk(KERN_ERR MOD_NAME ": Rom window is closed\n");
		जाओ out;
	पूर्ण

	/* reserved  0x0020 and 0x0010 */
	winकरोw->phys -= 0x400000UL;
	winकरोw->size = (0xffffffffUL - winकरोw->phys) + 1UL;

	/* Enable ग_लिखोs through the rom winकरोw */
	pci_पढ़ो_config_byte(pdev, BIOS_CNTL, &byte);
	अगर (!(byte & BIOS_WRITE_ENABLE)  && (byte & (BIOS_LOCK_ENABLE))) अणु
		/* The BIOS will generate an error अगर I enable
		 * this device, so करोn't even try.
		 */
		prपूर्णांकk(KERN_ERR MOD_NAME ": firmware access control, I can't enable writes\n");
		जाओ out;
	पूर्ण
	pci_ग_लिखो_config_byte(pdev, BIOS_CNTL, byte | BIOS_WRITE_ENABLE);

	/*
	 * Try to reserve the winकरोw mem region.  If this fails then
	 * it is likely due to the winकरोw being "reserved" by the BIOS.
	 */
	winकरोw->rsrc.name = MOD_NAME;
	winकरोw->rsrc.start = winकरोw->phys;
	winकरोw->rsrc.end   = winकरोw->phys + winकरोw->size - 1;
	winकरोw->rsrc.flags = IORESOURCE_MEM | IORESOURCE_BUSY;
	अगर (request_resource(&iomem_resource, &winकरोw->rsrc)) अणु
		winकरोw->rsrc.parent = शून्य;
		prपूर्णांकk(KERN_DEBUG MOD_NAME ": "
		       "%s(): Unable to register resource %pR - kernel bug?\n",
			__func__, &winकरोw->rsrc);
	पूर्ण

	/* Map the firmware hub पूर्णांकo my address space. */
	winकरोw->virt = ioremap(winकरोw->phys, winकरोw->size);
	अगर (!winकरोw->virt) अणु
		prपूर्णांकk(KERN_ERR MOD_NAME ": ioremap(%08lx, %08lx) failed\n",
			winकरोw->phys, winकरोw->size);
		जाओ out;
	पूर्ण

	/* Get the first address to look क्रम an rom chip at */
	map_top = winकरोw->phys;
	अगर ((winकरोw->phys & 0x3fffff) != 0) अणु
		/* अगर not aligned on 4MiB, look 4MiB lower in address space */
		map_top = winकरोw->phys + 0x400000;
	पूर्ण
#अगर 1
	/* The probe sequence run over the firmware hub lock
	 * रेजिस्टरs sets them to 0x7 (no access).
	 * (Insane hardware design, but most copied Intel's.)
	 * ==> Probe at most the last 4M of the address space.
	 */
	अगर (map_top < 0xffc00000)
		map_top = 0xffc00000;
#पूर्ण_अगर
	/* Loop through and look क्रम rom chips */
	जबतक ((map_top - 1) < 0xffffffffUL) अणु
		काष्ठा cfi_निजी *cfi;
		अचिन्हित दीर्घ offset;
		पूर्णांक i;

		अगर (!map)
			map = kदो_स्मृति(माप(*map), GFP_KERNEL);
		अगर (!map) अणु
			prपूर्णांकk(KERN_ERR MOD_NAME ": kmalloc failed");
			जाओ out;
		पूर्ण
		स_रखो(map, 0, माप(*map));
		INIT_LIST_HEAD(&map->list);
		map->map.name = map->map_name;
		map->map.phys = map_top;
		offset = map_top - winकरोw->phys;
		map->map.virt = (व्योम __iomem *)
			(((अचिन्हित दीर्घ)(winकरोw->virt)) + offset);
		map->map.size = 0xffffffffUL - map_top + 1UL;
		/* Set the name of the map to the address I am trying */
		प्र_लिखो(map->map_name, "%s @%08Lx",
			MOD_NAME, (अचिन्हित दीर्घ दीर्घ)map->map.phys);

		/* Firmware hubs only use vpp when being programmed
		 * in a factory setting.  So in-place programming
		 * needs to use a dअगरferent method.
		 */
		क्रम(map->map.bankwidth = 32; map->map.bankwidth;
			map->map.bankwidth >>= 1) अणु
			अक्षर **probe_type;
			/* Skip bankwidths that are not supported */
			अगर (!map_bankwidth_supported(map->map.bankwidth))
				जारी;

			/* Setup the map methods */
			simple_map_init(&map->map);

			/* Try all of the probe methods */
			probe_type = rom_probe_types;
			क्रम(; *probe_type; probe_type++) अणु
				map->mtd = करो_map_probe(*probe_type, &map->map);
				अगर (map->mtd)
					जाओ found;
			पूर्ण
		पूर्ण
		map_top += ROM_PROBE_STEP_SIZE;
		जारी;
	found:
		/* Trim the size अगर we are larger than the map */
		अगर (map->mtd->size > map->map.size) अणु
			prपूर्णांकk(KERN_WARNING MOD_NAME
				" rom(%llu) larger than window(%lu). fixing...\n",
				(अचिन्हित दीर्घ दीर्घ)map->mtd->size, map->map.size);
			map->mtd->size = map->map.size;
		पूर्ण
		अगर (winकरोw->rsrc.parent) अणु
			/*
			 * Registering the MTD device in iomem may not be possible
			 * अगर there is a BIOS "reserved" and BUSY range.  If this
			 * fails then जारी anyway.
			 */
			map->rsrc.name  = map->map_name;
			map->rsrc.start = map->map.phys;
			map->rsrc.end   = map->map.phys + map->mtd->size - 1;
			map->rsrc.flags = IORESOURCE_MEM | IORESOURCE_BUSY;
			अगर (request_resource(&winकरोw->rsrc, &map->rsrc)) अणु
				prपूर्णांकk(KERN_ERR MOD_NAME
					": cannot reserve MTD resource\n");
				map->rsrc.parent = शून्य;
			पूर्ण
		पूर्ण

		/* Make the whole region visible in the map */
		map->map.virt = winकरोw->virt;
		map->map.phys = winकरोw->phys;
		cfi = map->map.fldrv_priv;
		क्रम(i = 0; i < cfi->numchips; i++)
			cfi->chips[i].start += offset;

		/* Now that the mtd devices is complete claim and export it */
		map->mtd->owner = THIS_MODULE;
		अगर (mtd_device_रेजिस्टर(map->mtd, शून्य, 0)) अणु
			map_destroy(map->mtd);
			map->mtd = शून्य;
			जाओ out;
		पूर्ण

		/* Calculate the new value of map_top */
		map_top += map->mtd->size;

		/* File away the map काष्ठाure */
		list_add(&map->list, &winकरोw->maps);
		map = शून्य;
	पूर्ण

 out:
	/* Free any left over map काष्ठाures */
	kमुक्त(map);

	/* See अगर I have any map काष्ठाures */
	अगर (list_empty(&winकरोw->maps)) अणु
		esb2rom_cleanup(winकरोw);
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम esb2rom_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा esb2rom_winकरोw *winकरोw = &esb2rom_winकरोw;
	esb2rom_cleanup(winकरोw);
पूर्ण

अटल स्थिर काष्ठा pci_device_id esb2rom_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82801BA_0,
	  PCI_ANY_ID, PCI_ANY_ID, पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82801CA_0,
	  PCI_ANY_ID, PCI_ANY_ID, पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82801DB_0,
	  PCI_ANY_ID, PCI_ANY_ID, पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82801EB_0,
	  PCI_ANY_ID, PCI_ANY_ID, पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_ESB_1,
	  PCI_ANY_ID, PCI_ANY_ID, पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_ESB2_0,
	  PCI_ANY_ID, PCI_ANY_ID, पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;

#अगर 0
MODULE_DEVICE_TABLE(pci, esb2rom_pci_tbl);

अटल काष्ठा pci_driver esb2rom_driver = अणु
	.name =		MOD_NAME,
	.id_table =	esb2rom_pci_tbl,
	.probe =	esb2rom_init_one,
	.हटाओ =	esb2rom_हटाओ_one,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init init_esb2rom(व्योम)
अणु
	काष्ठा pci_dev *pdev;
	स्थिर काष्ठा pci_device_id *id;
	पूर्णांक retVal;

	pdev = शून्य;
	क्रम (id = esb2rom_pci_tbl; id->venकरोr; id++) अणु
		prपूर्णांकk(KERN_DEBUG "device id = %x\n", id->device);
		pdev = pci_get_device(id->venकरोr, id->device, शून्य);
		अगर (pdev) अणु
			prपूर्णांकk(KERN_DEBUG "matched device = %x\n", id->device);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (pdev) अणु
		prपूर्णांकk(KERN_DEBUG "matched device id %x\n", id->device);
		retVal = esb2rom_init_one(pdev, &esb2rom_pci_tbl[0]);
		pci_dev_put(pdev);
		prपूर्णांकk(KERN_DEBUG "retVal = %d\n", retVal);
		वापस retVal;
	पूर्ण
	वापस -ENXIO;
#अगर 0
	वापस pci_रेजिस्टर_driver(&esb2rom_driver);
#पूर्ण_अगर
पूर्ण

अटल व्योम __निकास cleanup_esb2rom(व्योम)
अणु
	esb2rom_हटाओ_one(esb2rom_winकरोw.pdev);
पूर्ण

module_init(init_esb2rom);
module_निकास(cleanup_esb2rom);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lew Glendenning <lglendenning@lnxi.com>");
MODULE_DESCRIPTION("MTD map driver for BIOS chips on the ESB2 southbridge");
