<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ck804xrom.c
 *
 * Normal mappings of chips in physical memory
 *
 * Dave Olsen <करोlsen@lnxi.com>
 * Ryan Jackson <rjackson@lnxi.com>
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

#घोषणा ROM_PROBE_STEP_SIZE (64*1024)

#घोषणा DEV_CK804 1
#घोषणा DEV_MCP55 2

काष्ठा ck804xrom_winकरोw अणु
	व्योम __iomem *virt;
	अचिन्हित दीर्घ phys;
	अचिन्हित दीर्घ size;
	काष्ठा list_head maps;
	काष्ठा resource rsrc;
	काष्ठा pci_dev *pdev;
पूर्ण;

काष्ठा ck804xrom_map_info अणु
	काष्ठा list_head list;
	काष्ठा map_info map;
	काष्ठा mtd_info *mtd;
	काष्ठा resource rsrc;
	अक्षर map_name[माप(MOD_NAME) + 2 + ADDRESS_NAME_LEN];
पूर्ण;

/*
 * The following applies to ck804 only:
 * The 2 bits controlling the winकरोw size are often set to allow पढ़ोing
 * the BIOS, but too small to allow writing, since the lock रेजिस्टरs are
 * 4MiB lower in the address space than the data.
 *
 * This is पूर्णांकended to prevent flashing the bios, perhaps accidentally.
 *
 * This parameter allows the normal driver to override the BIOS settings.
 *
 * The bits are 6 and 7.  If both bits are set, it is a 5MiB winकरोw.
 * If only the 7 Bit is set, it is a 4MiB winकरोw.  Otherwise, a
 * 64KiB winकरोw.
 *
 * The following applies to mcp55 only:
 * The 15 bits controlling the winकरोw size are distributed as follows: 
 * byte @0x88: bit 0..7
 * byte @0x8c: bit 8..15
 * word @0x90: bit 16..30
 * If all bits are enabled, we have a 16? MiB winकरोw
 * Please set win_size_bits to 0x7fffffff अगर you actually want to करो something
 */
अटल uपूर्णांक win_size_bits = 0;
module_param(win_size_bits, uपूर्णांक, 0);
MODULE_PARM_DESC(win_size_bits, "ROM window size bits override, normally set by BIOS.");

अटल काष्ठा ck804xrom_winकरोw ck804xrom_winकरोw = अणु
	.maps = LIST_HEAD_INIT(ck804xrom_winकरोw.maps),
पूर्ण;

अटल व्योम ck804xrom_cleanup(काष्ठा ck804xrom_winकरोw *winकरोw)
अणु
	काष्ठा ck804xrom_map_info *map, *scratch;
	u8 byte;

	अगर (winकरोw->pdev) अणु
		/* Disable ग_लिखोs through the rom winकरोw */
		pci_पढ़ो_config_byte(winकरोw->pdev, 0x6d, &byte);
		pci_ग_लिखो_config_byte(winकरोw->pdev, 0x6d, byte & ~1);
	पूर्ण

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


अटल पूर्णांक __init ck804xrom_init_one(काष्ठा pci_dev *pdev,
				     स्थिर काष्ठा pci_device_id *ent)
अणु
	अटल अक्षर *rom_probe_types[] = अणु "cfi_probe", "jedec_probe", शून्य पूर्ण;
	u8 byte;
	u16 word;
	काष्ठा ck804xrom_winकरोw *winकरोw = &ck804xrom_winकरोw;
	काष्ठा ck804xrom_map_info *map = शून्य;
	अचिन्हित दीर्घ map_top;

	/* Remember the pci dev I find the winकरोw in */
	winकरोw->pdev = pci_dev_get(pdev);

	चयन (ent->driver_data) अणु
	हाल DEV_CK804:
		/* Enable the selected rom winकरोw.  This is often incorrectly
		 * set up by the BIOS, and the 4MiB offset क्रम the lock रेजिस्टरs
		 * requires the full 5MiB of winकरोw space.
		 *
		 * This 'write, then read' approach leaves the bits क्रम
		 * other uses of the hardware info.
		 */
		pci_पढ़ो_config_byte(pdev, 0x88, &byte);
		pci_ग_लिखो_config_byte(pdev, 0x88, byte | win_size_bits );

		/* Assume the rom winकरोw is properly setup, and find it's size */
		pci_पढ़ो_config_byte(pdev, 0x88, &byte);

		अगर ((byte & ((1<<7)|(1<<6))) == ((1<<7)|(1<<6)))
			winकरोw->phys = 0xffb00000; /* 5MiB */
		अन्यथा अगर ((byte & (1<<7)) == (1<<7))
			winकरोw->phys = 0xffc00000; /* 4MiB */
		अन्यथा
			winकरोw->phys = 0xffff0000; /* 64KiB */
		अवरोध;

	हाल DEV_MCP55:
		pci_पढ़ो_config_byte(pdev, 0x88, &byte);
		pci_ग_लिखो_config_byte(pdev, 0x88, byte | (win_size_bits & 0xff));

		pci_पढ़ो_config_byte(pdev, 0x8c, &byte);
		pci_ग_लिखो_config_byte(pdev, 0x8c, byte | ((win_size_bits & 0xff00) >> 8));

		pci_पढ़ो_config_word(pdev, 0x90, &word);
		pci_ग_लिखो_config_word(pdev, 0x90, word | ((win_size_bits & 0x7fff0000) >> 16));

		winकरोw->phys = 0xff000000; /* 16MiB, hardcoded क्रम now */
		अवरोध;
	पूर्ण

	winकरोw->size = 0xffffffffUL - winकरोw->phys + 1UL;

	/*
	 * Try to reserve the winकरोw mem region.  If this fails then
	 * it is likely due to a fragment of the winकरोw being
	 * "reserved" by the BIOS.  In the हाल that the
	 * request_mem_region() fails then once the rom size is
	 * discovered we will try to reserve the unreserved fragment.
	 */
	winकरोw->rsrc.name = MOD_NAME;
	winकरोw->rsrc.start = winकरोw->phys;
	winकरोw->rsrc.end   = winकरोw->phys + winकरोw->size - 1;
	winकरोw->rsrc.flags = IORESOURCE_MEM | IORESOURCE_BUSY;
	अगर (request_resource(&iomem_resource, &winकरोw->rsrc)) अणु
		winकरोw->rsrc.parent = शून्य;
		prपूर्णांकk(KERN_ERR MOD_NAME
		       " %s(): Unable to register resource %pR - kernel bug?\n",
			__func__, &winकरोw->rsrc);
	पूर्ण


	/* Enable ग_लिखोs through the rom winकरोw */
	pci_पढ़ो_config_byte(pdev, 0x6d, &byte);
	pci_ग_लिखो_config_byte(pdev, 0x6d, byte | 1);

	/* FIXME handle रेजिस्टरs 0x80 - 0x8C the bios region locks */

	/* For ग_लिखो accesses caches are useless */
	winकरोw->virt = ioremap(winकरोw->phys, winकरोw->size);
	अगर (!winकरोw->virt) अणु
		prपूर्णांकk(KERN_ERR MOD_NAME ": ioremap(%08lx, %08lx) failed\n",
			winकरोw->phys, winकरोw->size);
		जाओ out;
	पूर्ण

	/* Get the first address to look क्रम a rom chip at */
	map_top = winकरोw->phys;
#अगर 1
	/* The probe sequence run over the firmware hub lock
	 * रेजिस्टरs sets them to 0x7 (no access).
	 * Probe at most the last 4MiB of the address space.
	 */
	अगर (map_top < 0xffc00000)
		map_top = 0xffc00000;
#पूर्ण_अगर
	/* Loop  through and look क्रम rom chips.  Since we करोn't know the
	 * starting address क्रम each chip, probe every ROM_PROBE_STEP_SIZE
	 * bytes from the starting address of the winकरोw.
	 */
	जबतक((map_top - 1) < 0xffffffffUL) अणु
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

		/* There is no generic VPP support */
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
		ck804xrom_cleanup(winकरोw);
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण


अटल व्योम ck804xrom_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ck804xrom_winकरोw *winकरोw = &ck804xrom_winकरोw;

	ck804xrom_cleanup(winकरोw);
पूर्ण

अटल स्थिर काष्ठा pci_device_id ck804xrom_pci_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_NVIDIA, 0x0051), .driver_data = DEV_CK804 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_NVIDIA, 0x0360), .driver_data = DEV_MCP55 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_NVIDIA, 0x0361), .driver_data = DEV_MCP55 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_NVIDIA, 0x0362), .driver_data = DEV_MCP55 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_NVIDIA, 0x0363), .driver_data = DEV_MCP55 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_NVIDIA, 0x0364), .driver_data = DEV_MCP55 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_NVIDIA, 0x0365), .driver_data = DEV_MCP55 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_NVIDIA, 0x0366), .driver_data = DEV_MCP55 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_NVIDIA, 0x0367), .driver_data = DEV_MCP55 पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

#अगर 0
MODULE_DEVICE_TABLE(pci, ck804xrom_pci_tbl);

अटल काष्ठा pci_driver ck804xrom_driver = अणु
	.name =		MOD_NAME,
	.id_table =	ck804xrom_pci_tbl,
	.probe =	ck804xrom_init_one,
	.हटाओ =	ck804xrom_हटाओ_one,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init init_ck804xrom(व्योम)
अणु
	काष्ठा pci_dev *pdev;
	स्थिर काष्ठा pci_device_id *id;
	पूर्णांक retVal;
	pdev = शून्य;

	क्रम(id = ck804xrom_pci_tbl; id->venकरोr; id++) अणु
		pdev = pci_get_device(id->venकरोr, id->device, शून्य);
		अगर (pdev)
			अवरोध;
	पूर्ण
	अगर (pdev) अणु
		retVal = ck804xrom_init_one(pdev, id);
		pci_dev_put(pdev);
		वापस retVal;
	पूर्ण
	वापस -ENXIO;
#अगर 0
	वापस pci_रेजिस्टर_driver(&ck804xrom_driver);
#पूर्ण_अगर
पूर्ण

अटल व्योम __निकास cleanup_ck804xrom(व्योम)
अणु
	ck804xrom_हटाओ_one(ck804xrom_winकरोw.pdev);
पूर्ण

module_init(init_ck804xrom);
module_निकास(cleanup_ck804xrom);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Eric Biederman <ebiederman@lnxi.com>, Dave Olsen <dolsen@lnxi.com>");
MODULE_DESCRIPTION("MTD map driver for BIOS chips on the Nvidia ck804 southbridge");

