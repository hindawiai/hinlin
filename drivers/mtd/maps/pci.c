<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/mtd/maps/pci.c
 *
 *  Copyright (C) 2001 Russell King, All rights reserved.
 *
 * Generic PCI memory map driver.  We support the following boards:
 *  - Intel IQ80310 ATU.
 *  - Intel EBSA285 (blank rom programming mode). Tested working 27/09/2001
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/partitions.h>

काष्ठा map_pci_info;

काष्ठा mtd_pci_info अणु
	पूर्णांक  (*init)(काष्ठा pci_dev *dev, काष्ठा map_pci_info *map);
	व्योम (*निकास)(काष्ठा pci_dev *dev, काष्ठा map_pci_info *map);
	अचिन्हित दीर्घ (*translate)(काष्ठा map_pci_info *map, अचिन्हित दीर्घ ofs);
	स्थिर अक्षर *map_name;
पूर्ण;

काष्ठा map_pci_info अणु
	काष्ठा map_info map;
	व्योम __iomem *base;
	व्योम (*निकास)(काष्ठा pci_dev *dev, काष्ठा map_pci_info *map);
	अचिन्हित दीर्घ (*translate)(काष्ठा map_pci_info *map, अचिन्हित दीर्घ ofs);
	काष्ठा pci_dev *dev;
पूर्ण;

अटल map_word mtd_pci_पढ़ो8(काष्ठा map_info *_map, अचिन्हित दीर्घ ofs)
अणु
	काष्ठा map_pci_info *map = (काष्ठा map_pci_info *)_map;
	map_word val;
	val.x[0]= पढ़ोb(map->base + map->translate(map, ofs));
	वापस val;
पूर्ण

अटल map_word mtd_pci_पढ़ो32(काष्ठा map_info *_map, अचिन्हित दीर्घ ofs)
अणु
	काष्ठा map_pci_info *map = (काष्ठा map_pci_info *)_map;
	map_word val;
	val.x[0] = पढ़ोl(map->base + map->translate(map, ofs));
	वापस val;
पूर्ण

अटल व्योम mtd_pci_copyfrom(काष्ठा map_info *_map, व्योम *to, अचिन्हित दीर्घ from, sमाप_प्रकार len)
अणु
	काष्ठा map_pci_info *map = (काष्ठा map_pci_info *)_map;
	स_नकल_fromio(to, map->base + map->translate(map, from), len);
पूर्ण

अटल व्योम mtd_pci_ग_लिखो8(काष्ठा map_info *_map, map_word val, अचिन्हित दीर्घ ofs)
अणु
	काष्ठा map_pci_info *map = (काष्ठा map_pci_info *)_map;
	ग_लिखोb(val.x[0], map->base + map->translate(map, ofs));
पूर्ण

अटल व्योम mtd_pci_ग_लिखो32(काष्ठा map_info *_map, map_word val, अचिन्हित दीर्घ ofs)
अणु
	काष्ठा map_pci_info *map = (काष्ठा map_pci_info *)_map;
	ग_लिखोl(val.x[0], map->base + map->translate(map, ofs));
पूर्ण

अटल व्योम mtd_pci_copyto(काष्ठा map_info *_map, अचिन्हित दीर्घ to, स्थिर व्योम *from, sमाप_प्रकार len)
अणु
	काष्ठा map_pci_info *map = (काष्ठा map_pci_info *)_map;
	स_नकल_toio(map->base + map->translate(map, to), from, len);
पूर्ण

अटल स्थिर काष्ठा map_info mtd_pci_map = अणु
	.phys =		NO_XIP,
	.copy_from =	mtd_pci_copyfrom,
	.copy_to =	mtd_pci_copyto,
पूर्ण;

/*
 * Intel IOP80310 Flash driver
 */

अटल पूर्णांक
पूर्णांकel_iq80310_init(काष्ठा pci_dev *dev, काष्ठा map_pci_info *map)
अणु
	u32 win_base;

	map->map.bankwidth = 1;
	map->map.पढ़ो = mtd_pci_पढ़ो8;
	map->map.ग_लिखो = mtd_pci_ग_लिखो8;

	map->map.size     = 0x00800000;
	map->base         = ioremap(pci_resource_start(dev, 0),
					    pci_resource_len(dev, 0));

	अगर (!map->base)
		वापस -ENOMEM;

	/*
	 * We want to base the memory winकरोw at Xscale
	 * bus address 0, not 0x1000.
	 */
	pci_पढ़ो_config_dword(dev, 0x44, &win_base);
	pci_ग_लिखो_config_dword(dev, 0x44, 0);

	map->map.map_priv_2 = win_base;

	वापस 0;
पूर्ण

अटल व्योम
पूर्णांकel_iq80310_निकास(काष्ठा pci_dev *dev, काष्ठा map_pci_info *map)
अणु
	अगर (map->base)
		iounmap(map->base);
	pci_ग_लिखो_config_dword(dev, 0x44, map->map.map_priv_2);
पूर्ण

अटल अचिन्हित दीर्घ
पूर्णांकel_iq80310_translate(काष्ठा map_pci_info *map, अचिन्हित दीर्घ ofs)
अणु
	अचिन्हित दीर्घ page_addr = ofs & 0x00400000;

	/*
	 * This mundges the flash location so we aव्योम
	 * the first 80 bytes (they appear to पढ़ो nonsense).
	 */
	अगर (page_addr) अणु
		ग_लिखोl(0x00000008, map->base + 0x1558);
		ग_लिखोl(0x00000000, map->base + 0x1550);
	पूर्ण अन्यथा अणु
		ग_लिखोl(0x00000007, map->base + 0x1558);
		ग_लिखोl(0x00800000, map->base + 0x1550);
		ofs += 0x00800000;
	पूर्ण

	वापस ofs;
पूर्ण

अटल काष्ठा mtd_pci_info पूर्णांकel_iq80310_info = अणु
	.init =		पूर्णांकel_iq80310_init,
	.निकास =		पूर्णांकel_iq80310_निकास,
	.translate =	पूर्णांकel_iq80310_translate,
	.map_name =	"cfi_probe",
पूर्ण;

/*
 * Intel DC21285 driver
 */

अटल पूर्णांक
पूर्णांकel_dc21285_init(काष्ठा pci_dev *dev, काष्ठा map_pci_info *map)
अणु
	अचिन्हित दीर्घ base, len;

	base = pci_resource_start(dev, PCI_ROM_RESOURCE);
	len  = pci_resource_len(dev, PCI_ROM_RESOURCE);

	अगर (!len || !base) अणु
		/*
		 * No ROM resource
		 */
		base = pci_resource_start(dev, 2);
		len  = pci_resource_len(dev, 2);

		/*
		 * We need to re-allocate PCI BAR2 address range to the
		 * PCI ROM BAR, and disable PCI BAR2.
		 */
	पूर्ण अन्यथा अणु
		/*
		 * Hmm, अगर an address was allocated to the ROM resource, but
		 * not enabled, should we be allocating a new resource क्रम it
		 * or simply enabling it?
		 */
		pci_enable_rom(dev);
		prपूर्णांकk("%s: enabling expansion ROM\n", pci_name(dev));
	पूर्ण

	अगर (!len || !base)
		वापस -ENXIO;

	map->map.bankwidth = 4;
	map->map.पढ़ो = mtd_pci_पढ़ो32;
	map->map.ग_लिखो = mtd_pci_ग_लिखो32;
	map->map.size     = len;
	map->base         = ioremap(base, len);

	अगर (!map->base)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम
पूर्णांकel_dc21285_निकास(काष्ठा pci_dev *dev, काष्ठा map_pci_info *map)
अणु
	अगर (map->base)
		iounmap(map->base);

	/*
	 * We need to unकरो the PCI BAR2/PCI ROM BAR address alteration.
	 */
	pci_disable_rom(dev);
पूर्ण

अटल अचिन्हित दीर्घ
पूर्णांकel_dc21285_translate(काष्ठा map_pci_info *map, अचिन्हित दीर्घ ofs)
अणु
	वापस ofs & 0x00ffffc0 ? ofs : (ofs ^ (1 << 5));
पूर्ण

अटल काष्ठा mtd_pci_info पूर्णांकel_dc21285_info = अणु
	.init =		पूर्णांकel_dc21285_init,
	.निकास =		पूर्णांकel_dc21285_निकास,
	.translate =	पूर्णांकel_dc21285_translate,
	.map_name =	"jedec_probe",
पूर्ण;

/*
 * PCI device ID table
 */

अटल स्थिर काष्ठा pci_device_id mtd_pci_ids[] = अणु
	अणु
		.venकरोr =	PCI_VENDOR_ID_INTEL,
		.device =	0x530d,
		.subvenकरोr =	PCI_ANY_ID,
		.subdevice =	PCI_ANY_ID,
		.class =	PCI_CLASS_MEMORY_OTHER << 8,
		.class_mask =	0xffff00,
		.driver_data =	(अचिन्हित दीर्घ)&पूर्णांकel_iq80310_info,
	पूर्ण,
	अणु
		.venकरोr =	PCI_VENDOR_ID_DEC,
		.device =	PCI_DEVICE_ID_DEC_21285,
		.subvenकरोr =	0,	/* DC21285 शेषs to 0 on reset */
		.subdevice =	0,	/* DC21285 शेषs to 0 on reset */
		.driver_data =	(अचिन्हित दीर्घ)&पूर्णांकel_dc21285_info,
	पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

/*
 * Generic code follows.
 */

अटल पूर्णांक mtd_pci_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा mtd_pci_info *info = (काष्ठा mtd_pci_info *)id->driver_data;
	काष्ठा map_pci_info *map = शून्य;
	काष्ठा mtd_info *mtd = शून्य;
	पूर्णांक err;

	err = pci_enable_device(dev);
	अगर (err)
		जाओ out;

	err = pci_request_regions(dev, "pci mtd");
	अगर (err)
		जाओ out;

	map = kदो_स्मृति(माप(*map), GFP_KERNEL);
	err = -ENOMEM;
	अगर (!map)
		जाओ release;

	map->map       = mtd_pci_map;
	map->map.name  = pci_name(dev);
	map->dev       = dev;
	map->निकास      = info->निकास;
	map->translate = info->translate;

	err = info->init(dev, map);
	अगर (err)
		जाओ release;

	mtd = करो_map_probe(info->map_name, &map->map);
	err = -ENODEV;
	अगर (!mtd)
		जाओ release;

	mtd->owner = THIS_MODULE;
	mtd_device_रेजिस्टर(mtd, शून्य, 0);

	pci_set_drvdata(dev, mtd);

	वापस 0;

release:
	अगर (map) अणु
		map->निकास(dev, map);
		kमुक्त(map);
	पूर्ण

	pci_release_regions(dev);
out:
	वापस err;
पूर्ण

अटल व्योम mtd_pci_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा mtd_info *mtd = pci_get_drvdata(dev);
	काष्ठा map_pci_info *map = mtd->priv;

	mtd_device_unरेजिस्टर(mtd);
	map_destroy(mtd);
	map->निकास(dev, map);
	kमुक्त(map);

	pci_release_regions(dev);
पूर्ण

अटल काष्ठा pci_driver mtd_pci_driver = अणु
	.name =		"MTD PCI",
	.probe =	mtd_pci_probe,
	.हटाओ =	mtd_pci_हटाओ,
	.id_table =	mtd_pci_ids,
पूर्ण;

module_pci_driver(mtd_pci_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Russell King <rmk@arm.linux.org.uk>");
MODULE_DESCRIPTION("Generic PCI map driver");
MODULE_DEVICE_TABLE(pci, mtd_pci_ids);
