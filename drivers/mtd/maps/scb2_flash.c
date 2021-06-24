<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MTD map driver क्रम BIOS Flash on Intel SCB2 boards
 * Copyright (C) 2002 Sun Microप्रणालीs, Inc.
 * Tim Hockin <thockin@sun.com>
 *
 * A few notes on this MTD map:
 *
 * This was developed with a small number of SCB2 boards to test on.
 * Hopefully, Intel has not पूर्णांकroducted too many unaccounted variables in the
 * making of this board.
 *
 * The BIOS marks its own memory region as 'reserved' in the e820 map.  We
 * try to request it here, but अगर it fails, we carry on anyway.
 *
 * This is how the chip is attached, so said the schematic:
 * * a 4 MiB (32 Mib) 16 bit chip
 * * a 1 MiB memory region
 * * A20 and A21 pulled up
 * * D8-D15 ignored
 * What this means is that, जबतक we are addressing bytes linearly, we are
 * really addressing words, and discarding the other byte.  This means that
 * the chip MUST BE at least 2 MiB.  This also means that every block is
 * actually half as big as the chip reports.  It also means that accesses of
 * logical address 0 hit higher-address sections of the chip, not physical 0.
 * One can only hope that these 4MiB x16 chips were a lot cheaper than 1MiB x8
 * chips.
 *
 * This driver assumes the chip is not ग_लिखो-रक्षित by an बाह्यal संकेत.
 * As of the this writing, that is true, but may change, just to spite me.
 *
 * The actual BIOS layout has been mostly reverse engineered.  Intel BIOS
 * updates क्रम this board include 10 related (*.bio - &.bi9) binary files and
 * another separate (*.bbo) binary file.  The 10 files are 64k of data + a
 * small header.  If the headers are stripped off, the 10 64k files can be
 * concatenated पूर्णांकo a 640k image.  This is your BIOS image, proper.  The
 * separate .bbo file also has a small header.  It is the 'Boot Block'
 * recovery BIOS.  Once the header is stripped, no further prep is needed.
 * As best I can tell, the BIOS is arranged as such:
 * offset 0x00000 to 0x4ffff (320k):  unknown - SCSI BIOS, etc?
 * offset 0x50000 to 0xeffff (640k):  BIOS proper
 * offset 0xf0000 ty 0xfffff (64k):   Boot Block region
 *
 * Intel's BIOS update program flashes the BIOS and Boot Block in separate
 * steps.  Probably a wise thing to करो.
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/cfi.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>

#घोषणा MODNAME		"scb2_flash"
#घोषणा SCB2_ADDR	0xfff00000
#घोषणा SCB2_WINDOW	0x00100000


अटल व्योम __iomem *scb2_ioaddr;
अटल काष्ठा mtd_info *scb2_mtd;
अटल काष्ठा map_info scb2_map = अणु
	.name =      "SCB2 BIOS Flash",
	.size =      0,
	.bankwidth =  1,
पूर्ण;
अटल पूर्णांक region_fail;

अटल पूर्णांक scb2_fixup_mtd(काष्ठा mtd_info *mtd)
अणु
	पूर्णांक i;
	पूर्णांक करोne = 0;
	काष्ठा map_info *map = mtd->priv;
	काष्ठा cfi_निजी *cfi = map->fldrv_priv;

	/* barf अगर this करोesn't look right */
	अगर (cfi->cfiq->InterfaceDesc != CFI_INTERFACE_X16_ASYNC) अणु
		prपूर्णांकk(KERN_ERR MODNAME ": unsupported InterfaceDesc: %#x\n",
		    cfi->cfiq->InterfaceDesc);
		वापस -1;
	पूर्ण

	/* I wasn't here. I didn't see. dwmw2. */

	/* the chip is someबार bigger than the map - what a waste */
	mtd->size = map->size;

	/*
	 * We only REALLY get half the chip, due to the way it is
	 * wired up - D8-D15 are tossed away.  We पढ़ो linear bytes,
	 * but in reality we are getting 1/2 of each 16-bit पढ़ो,
	 * which LOOKS linear to us.  Because CFI code accounts क्रम
	 * things like lock/unlock/erase by eraseregions, we need to
	 * fudge them to reflect this.  Erases go like this:
	 *   * send an erase to an address
	 *   * the chip samples the address and erases the block
	 *   * add the block erasesize to the address and repeat
	 *   -- the problem is that addresses are 16-bit addressable
	 *   -- we end up erasing every-other block
	 */
	mtd->erasesize /= 2;
	क्रम (i = 0; i < mtd->numeraseregions; i++) अणु
		काष्ठा mtd_erase_region_info *region = &mtd->eraseregions[i];
		region->erasesize /= 2;
	पूर्ण

	/*
	 * If the chip is bigger than the map, it is wired with the high
	 * address lines pulled up.  This makes us access the top portion of
	 * the chip, so all our erase-region info is wrong.  Start cutting from
	 * the bottom.
	 */
	क्रम (i = 0; !करोne && i < mtd->numeraseregions; i++) अणु
		काष्ठा mtd_erase_region_info *region = &mtd->eraseregions[i];

		अगर (region->numblocks * region->erasesize > mtd->size) अणु
			region->numblocks = ((अचिन्हित दीर्घ)mtd->size /
						region->erasesize);
			करोne = 1;
		पूर्ण अन्यथा अणु
			region->numblocks = 0;
		पूर्ण
		region->offset = 0;
	पूर्ण

	वापस 0;
पूर्ण

/* CSB5's 'Function Control Register' has bits क्रम decoding @ >= 0xffc00000 */
#घोषणा CSB5_FCR	0x41
#घोषणा CSB5_FCR_DECODE_ALL 0x0e
अटल पूर्णांक scb2_flash_probe(काष्ठा pci_dev *dev,
			    स्थिर काष्ठा pci_device_id *ent)
अणु
	u8 reg;

	/* enable decoding of the flash region in the south bridge */
	pci_पढ़ो_config_byte(dev, CSB5_FCR, &reg);
	pci_ग_लिखो_config_byte(dev, CSB5_FCR, reg | CSB5_FCR_DECODE_ALL);

	अगर (!request_mem_region(SCB2_ADDR, SCB2_WINDOW, scb2_map.name)) अणु
		/*
		 * The BIOS seems to mark the flash region as 'reserved'
		 * in the e820 map.  Warn and go about our business.
		 */
		prपूर्णांकk(KERN_WARNING MODNAME
		    ": warning - can't reserve rom window, continuing\n");
		region_fail = 1;
	पूर्ण

	/* remap the IO winकरोw (w/o caching) */
	scb2_ioaddr = ioremap(SCB2_ADDR, SCB2_WINDOW);
	अगर (!scb2_ioaddr) अणु
		prपूर्णांकk(KERN_ERR MODNAME ": Failed to ioremap window!\n");
		अगर (!region_fail)
			release_mem_region(SCB2_ADDR, SCB2_WINDOW);
		वापस -ENOMEM;
	पूर्ण

	scb2_map.phys = SCB2_ADDR;
	scb2_map.virt = scb2_ioaddr;
	scb2_map.size = SCB2_WINDOW;

	simple_map_init(&scb2_map);

	/* try to find a chip */
	scb2_mtd = करो_map_probe("cfi_probe", &scb2_map);

	अगर (!scb2_mtd) अणु
		prपूर्णांकk(KERN_ERR MODNAME ": flash probe failed!\n");
		iounmap(scb2_ioaddr);
		अगर (!region_fail)
			release_mem_region(SCB2_ADDR, SCB2_WINDOW);
		वापस -ENODEV;
	पूर्ण

	scb2_mtd->owner = THIS_MODULE;
	अगर (scb2_fixup_mtd(scb2_mtd) < 0) अणु
		mtd_device_unरेजिस्टर(scb2_mtd);
		map_destroy(scb2_mtd);
		iounmap(scb2_ioaddr);
		अगर (!region_fail)
			release_mem_region(SCB2_ADDR, SCB2_WINDOW);
		वापस -ENODEV;
	पूर्ण

	prपूर्णांकk(KERN_NOTICE MODNAME ": chip size 0x%llx at offset 0x%llx\n",
	       (अचिन्हित दीर्घ दीर्घ)scb2_mtd->size,
	       (अचिन्हित दीर्घ दीर्घ)(SCB2_WINDOW - scb2_mtd->size));

	mtd_device_रेजिस्टर(scb2_mtd, शून्य, 0);

	वापस 0;
पूर्ण

अटल व्योम scb2_flash_हटाओ(काष्ठा pci_dev *dev)
अणु
	अगर (!scb2_mtd)
		वापस;

	/* disable flash ग_लिखोs */
	mtd_lock(scb2_mtd, 0, scb2_mtd->size);

	mtd_device_unरेजिस्टर(scb2_mtd);
	map_destroy(scb2_mtd);

	iounmap(scb2_ioaddr);
	scb2_ioaddr = शून्य;

	अगर (!region_fail)
		release_mem_region(SCB2_ADDR, SCB2_WINDOW);
पूर्ण

अटल काष्ठा pci_device_id scb2_flash_pci_ids[] = अणु
	अणु
	  .venकरोr = PCI_VENDOR_ID_SERVERWORKS,
	  .device = PCI_DEVICE_ID_SERVERWORKS_CSB5,
	  .subvenकरोr = PCI_ANY_ID,
	  .subdevice = PCI_ANY_ID
	पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

अटल काष्ठा pci_driver scb2_flash_driver = अणु
	.name =     "Intel SCB2 BIOS Flash",
	.id_table = scb2_flash_pci_ids,
	.probe =    scb2_flash_probe,
	.हटाओ =   scb2_flash_हटाओ,
पूर्ण;

module_pci_driver(scb2_flash_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tim Hockin <thockin@sun.com>");
MODULE_DESCRIPTION("MTD map driver for Intel SCB2 BIOS Flash");
MODULE_DEVICE_TABLE(pci, scb2_flash_pci_ids);
