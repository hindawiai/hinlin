<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ichxrom.c
 *
 * Normal mappings of chips in physical memory
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

#घोषणा xstr(s) str(s)
#घोषणा str(s) #s
#घोषणा MOD_NAME xstr(KBUILD_BASENAME)

#घोषणा ADDRESS_NAME_LEN 18

#घोषणा ROM_PROBE_STEP_SIZE (64*1024) /* 64KiB */

#घोषणा BIOS_CNTL	0x4e
#घोषणा FWH_DEC_EN1	0xE3
#घोषणा FWH_DEC_EN2	0xF0
#घोषणा FWH_SEL1	0xE8
#घोषणा FWH_SEL2	0xEE

काष्ठा ichxrom_winकरोw अणु
	व्योम __iomem* virt;
	अचिन्हित दीर्घ phys;
	अचिन्हित दीर्घ size;
	काष्ठा list_head maps;
	काष्ठा resource rsrc;
	काष्ठा pci_dev *pdev;
पूर्ण;

काष्ठा ichxrom_map_info अणु
	काष्ठा list_head list;
	काष्ठा map_info map;
	काष्ठा mtd_info *mtd;
	काष्ठा resource rsrc;
	अक्षर map_name[माप(MOD_NAME) + 2 + ADDRESS_NAME_LEN];
पूर्ण;

अटल काष्ठा ichxrom_winकरोw ichxrom_winकरोw = अणु
	.maps = LIST_HEAD_INIT(ichxrom_winकरोw.maps),
पूर्ण;

अटल व्योम ichxrom_cleanup(काष्ठा ichxrom_winकरोw *winकरोw)
अणु
	काष्ठा ichxrom_map_info *map, *scratch;
	u16 word;
	पूर्णांक ret;

	/* Disable ग_लिखोs through the rom winकरोw */
	ret = pci_पढ़ो_config_word(winकरोw->pdev, BIOS_CNTL, &word);
	अगर (!ret)
		pci_ग_लिखो_config_word(winकरोw->pdev, BIOS_CNTL, word & ~1);
	pci_dev_put(winकरोw->pdev);

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
		winकरोw->pdev = शून्य;
	पूर्ण
पूर्ण


अटल पूर्णांक __init ichxrom_init_one(काष्ठा pci_dev *pdev,
				   स्थिर काष्ठा pci_device_id *ent)
अणु
	अटल अक्षर *rom_probe_types[] = अणु "cfi_probe", "jedec_probe", शून्य पूर्ण;
	काष्ठा ichxrom_winकरोw *winकरोw = &ichxrom_winकरोw;
	काष्ठा ichxrom_map_info *map = शून्य;
	अचिन्हित दीर्घ map_top;
	u8 byte;
	u16 word;

	/* For now I just handle the ichx and I assume there
	 * are not a lot of resources up at the top of the address
	 * space.  It is possible to handle other devices in the
	 * top 16MB but it is very painful.  Also since
	 * you can only really attach a FWH to an ICHX there
	 * a number of simplअगरications you can make.
	 *
	 * Also you can page firmware hubs अगर an 8MB winकरोw isn't enough
	 * but करोn't currently handle that हाल either.
	 */
	winकरोw->pdev = pdev;

	/* Find a region continuous to the end of the ROM winकरोw  */
	winकरोw->phys = 0;
	pci_पढ़ो_config_byte(pdev, FWH_DEC_EN1, &byte);
	अगर (byte == 0xff) अणु
		winकरोw->phys = 0xffc00000;
		pci_पढ़ो_config_byte(pdev, FWH_DEC_EN2, &byte);
		अगर ((byte & 0x0f) == 0x0f) अणु
			winकरोw->phys = 0xff400000;
		पूर्ण
		अन्यथा अगर ((byte & 0x0e) == 0x0e) अणु
			winकरोw->phys = 0xff500000;
		पूर्ण
		अन्यथा अगर ((byte & 0x0c) == 0x0c) अणु
			winकरोw->phys = 0xff600000;
		पूर्ण
		अन्यथा अगर ((byte & 0x08) == 0x08) अणु
			winकरोw->phys = 0xff700000;
		पूर्ण
	पूर्ण
	अन्यथा अगर ((byte & 0xfe) == 0xfe) अणु
		winकरोw->phys = 0xffc80000;
	पूर्ण
	अन्यथा अगर ((byte & 0xfc) == 0xfc) अणु
		winकरोw->phys = 0xffd00000;
	पूर्ण
	अन्यथा अगर ((byte & 0xf8) == 0xf8) अणु
		winकरोw->phys = 0xffd80000;
	पूर्ण
	अन्यथा अगर ((byte & 0xf0) == 0xf0) अणु
		winकरोw->phys = 0xffe00000;
	पूर्ण
	अन्यथा अगर ((byte & 0xe0) == 0xe0) अणु
		winकरोw->phys = 0xffe80000;
	पूर्ण
	अन्यथा अगर ((byte & 0xc0) == 0xc0) अणु
		winकरोw->phys = 0xfff00000;
	पूर्ण
	अन्यथा अगर ((byte & 0x80) == 0x80) अणु
		winकरोw->phys = 0xfff80000;
	पूर्ण

	अगर (winकरोw->phys == 0) अणु
		prपूर्णांकk(KERN_ERR MOD_NAME ": Rom window is closed\n");
		जाओ out;
	पूर्ण
	winकरोw->phys -= 0x400000UL;
	winकरोw->size = (0xffffffffUL - winकरोw->phys) + 1UL;

	/* Enable ग_लिखोs through the rom winकरोw */
	pci_पढ़ो_config_word(pdev, BIOS_CNTL, &word);
	अगर (!(word & 1)  && (word & (1<<1))) अणु
		/* The BIOS will generate an error अगर I enable
		 * this device, so करोn't even try.
		 */
		prपूर्णांकk(KERN_ERR MOD_NAME ": firmware access control, I can't enable writes\n");
		जाओ out;
	पूर्ण
	pci_ग_लिखो_config_word(pdev, BIOS_CNTL, word | 1);

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
		map_top = winकरोw->phys + 0x400000;
	पूर्ण
#अगर 1
	/* The probe sequence run over the firmware hub lock
	 * रेजिस्टरs sets them to 0x7 (no access).
	 * Probe at most the last 4M of the address space.
	 */
	अगर (map_top < 0xffc00000) अणु
		map_top = 0xffc00000;
	पूर्ण
#पूर्ण_अगर
	/* Loop through and look क्रम rom chips */
	जबतक((map_top - 1) < 0xffffffffUL) अणु
		काष्ठा cfi_निजी *cfi;
		अचिन्हित दीर्घ offset;
		पूर्णांक i;

		अगर (!map) अणु
			map = kदो_स्मृति(माप(*map), GFP_KERNEL);
		पूर्ण
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
			map->map.bankwidth >>= 1)
		अणु
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
		क्रम(i = 0; i < cfi->numchips; i++) अणु
			cfi->chips[i].start += offset;
		पूर्ण

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
		ichxrom_cleanup(winकरोw);
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण


अटल व्योम ichxrom_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ichxrom_winकरोw *winकरोw = &ichxrom_winकरोw;
	ichxrom_cleanup(winकरोw);
पूर्ण

अटल स्थिर काष्ठा pci_device_id ichxrom_pci_tbl[] = अणु
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
	अणु 0, पूर्ण,
पूर्ण;

#अगर 0
MODULE_DEVICE_TABLE(pci, ichxrom_pci_tbl);

अटल काष्ठा pci_driver ichxrom_driver = अणु
	.name =		MOD_NAME,
	.id_table =	ichxrom_pci_tbl,
	.probe =	ichxrom_init_one,
	.हटाओ =	ichxrom_हटाओ_one,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init init_ichxrom(व्योम)
अणु
	काष्ठा pci_dev *pdev;
	स्थिर काष्ठा pci_device_id *id;

	pdev = शून्य;
	क्रम (id = ichxrom_pci_tbl; id->venकरोr; id++) अणु
		pdev = pci_get_device(id->venकरोr, id->device, शून्य);
		अगर (pdev) अणु
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (pdev) अणु
		वापस ichxrom_init_one(pdev, &ichxrom_pci_tbl[0]);
	पूर्ण
	वापस -ENXIO;
#अगर 0
	वापस pci_रेजिस्टर_driver(&ichxrom_driver);
#पूर्ण_अगर
पूर्ण

अटल व्योम __निकास cleanup_ichxrom(व्योम)
अणु
	ichxrom_हटाओ_one(ichxrom_winकरोw.pdev);
पूर्ण

module_init(init_ichxrom);
module_निकास(cleanup_ichxrom);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Eric Biederman <ebiederman@lnxi.com>");
MODULE_DESCRIPTION("MTD map driver for BIOS chips on the ICHX southbridge");
