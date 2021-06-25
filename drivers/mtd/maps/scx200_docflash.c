<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* linux/drivers/mtd/maps/scx200_करोcflash.c

   Copyright (c) 2001,2002 Christer Weinigel <wingel@nano-प्रणाली.com>

   National Semiconductor SCx200 flash mapped with DOCCS
*/

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/partitions.h>

#समावेश <linux/pci.h>
#समावेश <linux/scx200.h>

#घोषणा NAME "scx200_docflash"

MODULE_AUTHOR("Christer Weinigel <wingel@hack.org>");
MODULE_DESCRIPTION("NatSemi SCx200 DOCCS Flash Driver");
MODULE_LICENSE("GPL");

अटल पूर्णांक probe = 0;		/* Don't स्वतःprobe */
अटल अचिन्हित size = 0x1000000; /* 16 MiB the whole ISA address space */
अटल अचिन्हित width = 8;	/* Default to 8 bits wide */
अटल अक्षर *flashtype = "cfi_probe";

module_param(probe, पूर्णांक, 0);
MODULE_PARM_DESC(probe, "Probe for a BIOS mapping");
module_param(size, पूर्णांक, 0);
MODULE_PARM_DESC(size, "Size of the flash mapping");
module_param(width, पूर्णांक, 0);
MODULE_PARM_DESC(width, "Data width of the flash mapping (8/16)");
module_param(flashtype, अक्षरp, 0);
MODULE_PARM_DESC(flashtype, "Type of MTD probe to do");

अटल काष्ठा resource करोcmem = अणु
	.flags = IORESOURCE_MEM,
	.name  = "NatSemi SCx200 DOCCS Flash",
पूर्ण;

अटल काष्ठा mtd_info *mymtd;

अटल काष्ठा mtd_partition partition_info[] = अणु
	अणु
		.name   = "DOCCS Boot kernel",
		.offset = 0,
		.size   = 0xc0000
	पूर्ण,
	अणु
		.name   = "DOCCS Low BIOS",
		.offset = 0xc0000,
		.size   = 0x40000
	पूर्ण,
	अणु
		.name   = "DOCCS File system",
		.offset = 0x100000,
		.size   = ~0	/* calculate from flash size */
	पूर्ण,
	अणु
		.name   = "DOCCS High BIOS",
		.offset = ~0, 	/* calculate from flash size */
		.size   = 0x80000
	पूर्ण,
पूर्ण;
#घोषणा NUM_PARTITIONS ARRAY_SIZE(partition_info)

अटल काष्ठा map_info scx200_करोcflash_map = अणु
	.name      = "NatSemi SCx200 DOCCS Flash",
पूर्ण;

अटल पूर्णांक __init init_scx200_करोcflash(व्योम)
अणु
	अचिन्हित u;
	अचिन्हित base;
	अचिन्हित ctrl;
	अचिन्हित pmr;
	काष्ठा pci_dev *bridge;

	prपूर्णांकk(KERN_DEBUG NAME ": NatSemi SCx200 DOCCS Flash Driver\n");

	अगर ((bridge = pci_get_device(PCI_VENDOR_ID_NS,
				      PCI_DEVICE_ID_NS_SCx200_BRIDGE,
				      शून्य)) == शून्य)
		वापस -ENODEV;

	/* check that we have found the configuration block */
	अगर (!scx200_cb_present()) अणु
		pci_dev_put(bridge);
		वापस -ENODEV;
	पूर्ण

	अगर (probe) अणु
		/* Try to use the present flash mapping अगर any */
		pci_पढ़ो_config_dword(bridge, SCx200_DOCCS_BASE, &base);
		pci_पढ़ो_config_dword(bridge, SCx200_DOCCS_CTRL, &ctrl);
		pci_dev_put(bridge);

		pmr = inl(scx200_cb_base + SCx200_PMR);

		अगर (base == 0
		    || (ctrl & 0x07000000) != 0x07000000
		    || (ctrl & 0x0007ffff) == 0)
			वापस -ENODEV;

		size = ((ctrl&0x1fff)<<13) + (1<<13);

		क्रम (u = size; u > 1; u >>= 1)
			;
		अगर (u != 1)
			वापस -ENODEV;

		अगर (pmr & (1<<6))
			width = 16;
		अन्यथा
			width = 8;

		करोcmem.start = base;
		करोcmem.end = base + size;

		अगर (request_resource(&iomem_resource, &करोcmem)) अणु
			prपूर्णांकk(KERN_ERR NAME ": unable to allocate memory for flash mapping\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अणु
		pci_dev_put(bridge);
		क्रम (u = size; u > 1; u >>= 1)
			;
		अगर (u != 1) अणु
			prपूर्णांकk(KERN_ERR NAME ": invalid size for flash mapping\n");
			वापस -EINVAL;
		पूर्ण

		अगर (width != 8 && width != 16) अणु
			prपूर्णांकk(KERN_ERR NAME ": invalid bus width for flash mapping\n");
			वापस -EINVAL;
		पूर्ण

		अगर (allocate_resource(&iomem_resource, &करोcmem,
				      size,
				      0xc0000000, 0xffffffff,
				      size, शून्य, शून्य)) अणु
			prपूर्णांकk(KERN_ERR NAME ": unable to allocate memory for flash mapping\n");
			वापस -ENOMEM;
		पूर्ण

		ctrl = 0x07000000 | ((size-1) >> 13);

		prपूर्णांकk(KERN_INFO "DOCCS BASE=0x%08lx, CTRL=0x%08lx\n", (दीर्घ)करोcmem.start, (दीर्घ)ctrl);

		pci_ग_लिखो_config_dword(bridge, SCx200_DOCCS_BASE, करोcmem.start);
		pci_ग_लिखो_config_dword(bridge, SCx200_DOCCS_CTRL, ctrl);
		pmr = inl(scx200_cb_base + SCx200_PMR);

		अगर (width == 8) अणु
			pmr &= ~(1<<6);
		पूर्ण अन्यथा अणु
			pmr |= (1<<6);
		पूर्ण
		outl(pmr, scx200_cb_base + SCx200_PMR);
	पूर्ण

	prपूर्णांकk(KERN_INFO NAME ": DOCCS mapped at %pR, width %d\n",
	       &करोcmem, width);

	scx200_करोcflash_map.size = size;
	अगर (width == 8)
		scx200_करोcflash_map.bankwidth = 1;
	अन्यथा
		scx200_करोcflash_map.bankwidth = 2;

	simple_map_init(&scx200_करोcflash_map);

	scx200_करोcflash_map.phys = करोcmem.start;
	scx200_करोcflash_map.virt = ioremap(करोcmem.start, scx200_करोcflash_map.size);
	अगर (!scx200_करोcflash_map.virt) अणु
		prपूर्णांकk(KERN_ERR NAME ": failed to ioremap the flash\n");
		release_resource(&करोcmem);
		वापस -EIO;
	पूर्ण

	mymtd = करो_map_probe(flashtype, &scx200_करोcflash_map);
	अगर (!mymtd) अणु
		prपूर्णांकk(KERN_ERR NAME ": unable to detect flash\n");
		iounmap(scx200_करोcflash_map.virt);
		release_resource(&करोcmem);
		वापस -ENXIO;
	पूर्ण

	अगर (size < mymtd->size)
		prपूर्णांकk(KERN_WARNING NAME ": warning, flash mapping is smaller than flash size\n");

	mymtd->owner = THIS_MODULE;

	partition_info[3].offset = mymtd->size-partition_info[3].size;
	partition_info[2].size = partition_info[3].offset-partition_info[2].offset;
	mtd_device_रेजिस्टर(mymtd, partition_info, NUM_PARTITIONS);

	वापस 0;
पूर्ण

अटल व्योम __निकास cleanup_scx200_करोcflash(व्योम)
अणु
	अगर (mymtd) अणु
		mtd_device_unरेजिस्टर(mymtd);
		map_destroy(mymtd);
	पूर्ण
	अगर (scx200_करोcflash_map.virt) अणु
		iounmap(scx200_करोcflash_map.virt);
		release_resource(&करोcmem);
	पूर्ण
पूर्ण

module_init(init_scx200_करोcflash);
module_निकास(cleanup_scx200_करोcflash);
