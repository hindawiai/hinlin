<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * BIOS Flash chip on Intel 440GX board.
 *
 * Bugs this currently करोes not work under linuxBIOS.
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/map.h>

#घोषणा PIIXE_IOBASE_RESOURCE	11

#घोषणा WINDOW_ADDR 0xfff00000
#घोषणा WINDOW_SIZE 0x00100000
#घोषणा BUSWIDTH 1

अटल u32 iobase;
#घोषणा IOBASE iobase
#घोषणा TRIBUF_PORT (IOBASE+0x37)
#घोषणा VPP_PORT (IOBASE+0x28)

अटल काष्ठा mtd_info *mymtd;


/* Is this really the vpp port? */
अटल DEFINE_SPINLOCK(l440gx_vpp_lock);
अटल पूर्णांक l440gx_vpp_refcnt;
अटल व्योम l440gx_set_vpp(काष्ठा map_info *map, पूर्णांक vpp)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&l440gx_vpp_lock, flags);
	अगर (vpp) अणु
		अगर (++l440gx_vpp_refcnt == 1)   /* first nested 'on' */
			outl(inl(VPP_PORT) | 1, VPP_PORT);
	पूर्ण अन्यथा अणु
		अगर (--l440gx_vpp_refcnt == 0)   /* last nested 'off' */
			outl(inl(VPP_PORT) & ~1, VPP_PORT);
	पूर्ण
	spin_unlock_irqrestore(&l440gx_vpp_lock, flags);
पूर्ण

अटल काष्ठा map_info l440gx_map = अणु
	.name = "L440GX BIOS",
	.size = WINDOW_SIZE,
	.bankwidth = BUSWIDTH,
	.phys = WINDOW_ADDR,
#अगर 0
	/* FIXME verअगरy that this is the
	 * appripriate code क्रम vpp enable/disable
	 */
	.set_vpp = l440gx_set_vpp
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init init_l440gx(व्योम)
अणु
	काष्ठा pci_dev *dev, *pm_dev;
	काष्ठा resource *pm_iobase;
	__u16 word;

	dev = pci_get_device(PCI_VENDOR_ID_INTEL,
		PCI_DEVICE_ID_INTEL_82371AB_0, शून्य);

	pm_dev = pci_get_device(PCI_VENDOR_ID_INTEL,
		PCI_DEVICE_ID_INTEL_82371AB_3, शून्य);

	pci_dev_put(dev);

	अगर (!dev || !pm_dev) अणु
		prपूर्णांकk(KERN_NOTICE "L440GX flash mapping: failed to find PIIX4 ISA bridge, cannot continue\n");
		pci_dev_put(pm_dev);
		वापस -ENODEV;
	पूर्ण

	l440gx_map.virt = ioremap(WINDOW_ADDR, WINDOW_SIZE);

	अगर (!l440gx_map.virt) अणु
		prपूर्णांकk(KERN_WARNING "Failed to ioremap L440GX flash region\n");
		pci_dev_put(pm_dev);
		वापस -ENOMEM;
	पूर्ण
	simple_map_init(&l440gx_map);
	pr_debug("window_addr = %p\n", l440gx_map.virt);

	/* Setup the pm iobase resource
	 * This code should move पूर्णांकo some kind of generic bridge
	 * driver but क्रम the moment I'm content with getting the
	 * allocation correct.
	 */
	pm_iobase = &pm_dev->resource[PIIXE_IOBASE_RESOURCE];
	अगर (!(pm_iobase->flags & IORESOURCE_IO)) अणु
		pm_iobase->name = "pm iobase";
		pm_iobase->start = 0;
		pm_iobase->end = 63;
		pm_iobase->flags = IORESOURCE_IO;

		/* Put the current value in the resource */
		pci_पढ़ो_config_dword(pm_dev, 0x40, &iobase);
		iobase &= ~1;
		pm_iobase->start += iobase & ~1;
		pm_iobase->end += iobase & ~1;

		pci_dev_put(pm_dev);

		/* Allocate the resource region */
		अगर (pci_assign_resource(pm_dev, PIIXE_IOBASE_RESOURCE) != 0) अणु
			pci_dev_put(dev);
			pci_dev_put(pm_dev);
			prपूर्णांकk(KERN_WARNING "Could not allocate pm iobase resource\n");
			iounmap(l440gx_map.virt);
			वापस -ENXIO;
		पूर्ण
	पूर्ण
	/* Set the iobase */
	iobase = pm_iobase->start;
	pci_ग_लिखो_config_dword(pm_dev, 0x40, iobase | 1);


	/* Set XBCS# */
	pci_पढ़ो_config_word(dev, 0x4e, &word);
	word |= 0x4;
        pci_ग_लिखो_config_word(dev, 0x4e, word);

	/* Supply ग_लिखो voltage to the chip */
	l440gx_set_vpp(&l440gx_map, 1);

	/* Enable the gate on the WE line */
	outb(inb(TRIBUF_PORT) & ~1, TRIBUF_PORT);

       	prपूर्णांकk(KERN_NOTICE "Enabled WE line to L440GX BIOS flash chip.\n");

	mymtd = करो_map_probe("jedec_probe", &l440gx_map);
	अगर (!mymtd) अणु
		prपूर्णांकk(KERN_NOTICE "JEDEC probe on BIOS chip failed. Using ROM\n");
		mymtd = करो_map_probe("map_rom", &l440gx_map);
	पूर्ण
	अगर (mymtd) अणु
		mymtd->owner = THIS_MODULE;

		mtd_device_रेजिस्टर(mymtd, शून्य, 0);
		वापस 0;
	पूर्ण

	iounmap(l440gx_map.virt);
	वापस -ENXIO;
पूर्ण

अटल व्योम __निकास cleanup_l440gx(व्योम)
अणु
	mtd_device_unरेजिस्टर(mymtd);
	map_destroy(mymtd);

	iounmap(l440gx_map.virt);
पूर्ण

module_init(init_l440gx);
module_निकास(cleanup_l440gx);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Woodhouse <dwmw2@infradead.org>");
MODULE_DESCRIPTION("MTD map driver for BIOS chips on Intel L440GX motherboards");
