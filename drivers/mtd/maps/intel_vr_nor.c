<शैली गुरु>
/*
 * drivers/mtd/maps/पूर्णांकel_vr_nor.c
 *
 * An MTD map driver क्रम a NOR flash bank on the Expansion Bus of the Intel
 * Vermilion Range chipset.
 *
 * The Vermilion Range Expansion Bus supports four chip selects, each of which
 * has 64MiB of address space.  The 2nd BAR of the Expansion Bus PCI Device
 * is a 256MiB memory region containing the address spaces क्रम all four of the
 * chip selects, with start addresses hardcoded on 64MiB boundaries.
 *
 * This map driver only supports NOR flash on chip select 0.  The buswidth
 * (either 8 bits or 16 bits) is determined by पढ़ोing the Expansion Bus Timing
 * and Control Register क्रम Chip Select 0 (EXP_TIMING_CS0).  This driver करोes
 * not modअगरy the value in the EXP_TIMING_CS0 रेजिस्टर except to enable writing
 * and disable boot acceleration.  The timing parameters in the रेजिस्टर are
 * assumed to have been properly initialized by the BIOS.  The reset शेष
 * timing parameters are maximally conservative (slow), so access to the flash
 * will be slower than it should be अगर the BIOS has not initialized the timing
 * parameters.
 *
 * Author: Andy Lowe <alowe@mvista.com>
 *
 * 2006 (c) MontaVista Software, Inc. This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/cfi.h>
#समावेश <linux/mtd/flashchip.h>

#घोषणा DRV_NAME "vr_nor"

काष्ठा vr_nor_mtd अणु
	व्योम __iomem *csr_base;
	काष्ठा map_info map;
	काष्ठा mtd_info *info;
	काष्ठा pci_dev *dev;
पूर्ण;

/* Expansion Bus Configuration and Status Registers are in BAR 0 */
#घोषणा EXP_CSR_MBAR 0
/* Expansion Bus Memory Winकरोw is BAR 1 */
#घोषणा EXP_WIN_MBAR 1
/* Maximum address space क्रम Chip Select 0 is 64MiB */
#घोषणा CS0_SIZE 0x04000000
/* Chip Select 0 is at offset 0 in the Memory Winकरोw */
#घोषणा CS0_START 0x0
/* Chip Select 0 Timing Register is at offset 0 in CSR */
#घोषणा EXP_TIMING_CS0 0x00
#घोषणा TIMING_CS_EN		(1 << 31)	/* Chip Select Enable */
#घोषणा TIMING_BOOT_ACCEL_DIS	(1 <<  8)	/* Boot Acceleration Disable */
#घोषणा TIMING_WR_EN		(1 <<  1)	/* Write Enable */
#घोषणा TIMING_BYTE_EN		(1 <<  0)	/* 8-bit vs 16-bit bus */
#घोषणा TIMING_MASK		0x3FFF0000

अटल व्योम vr_nor_destroy_partitions(काष्ठा vr_nor_mtd *p)
अणु
	mtd_device_unरेजिस्टर(p->info);
पूर्ण

अटल पूर्णांक vr_nor_init_partitions(काष्ठा vr_nor_mtd *p)
अणु
	/* रेजिस्टर the flash bank */
	/* partition the flash bank */
	वापस mtd_device_रेजिस्टर(p->info, शून्य, 0);
पूर्ण

अटल व्योम vr_nor_destroy_mtd_setup(काष्ठा vr_nor_mtd *p)
अणु
	map_destroy(p->info);
पूर्ण

अटल पूर्णांक vr_nor_mtd_setup(काष्ठा vr_nor_mtd *p)
अणु
	अटल स्थिर अक्षर * स्थिर probe_types[] =
	    अणु "cfi_probe", "jedec_probe", शून्य पूर्ण;
	स्थिर अक्षर * स्थिर *type;

	क्रम (type = probe_types; !p->info && *type; type++)
		p->info = करो_map_probe(*type, &p->map);
	अगर (!p->info)
		वापस -ENODEV;

	p->info->dev.parent = &p->dev->dev;

	वापस 0;
पूर्ण

अटल व्योम vr_nor_destroy_maps(काष्ठा vr_nor_mtd *p)
अणु
	अचिन्हित पूर्णांक exp_timing_cs0;

	/* ग_लिखो-protect the flash bank */
	exp_timing_cs0 = पढ़ोl(p->csr_base + EXP_TIMING_CS0);
	exp_timing_cs0 &= ~TIMING_WR_EN;
	ग_लिखोl(exp_timing_cs0, p->csr_base + EXP_TIMING_CS0);

	/* unmap the flash winकरोw */
	iounmap(p->map.virt);

	/* unmap the csr winकरोw */
	iounmap(p->csr_base);
पूर्ण

/*
 * Initialize the map_info काष्ठाure and map the flash.
 * Returns 0 on success, nonzero otherwise.
 */
अटल पूर्णांक vr_nor_init_maps(काष्ठा vr_nor_mtd *p)
अणु
	अचिन्हित दीर्घ csr_phys, csr_len;
	अचिन्हित दीर्घ win_phys, win_len;
	अचिन्हित पूर्णांक exp_timing_cs0;
	पूर्णांक err;

	csr_phys = pci_resource_start(p->dev, EXP_CSR_MBAR);
	csr_len = pci_resource_len(p->dev, EXP_CSR_MBAR);
	win_phys = pci_resource_start(p->dev, EXP_WIN_MBAR);
	win_len = pci_resource_len(p->dev, EXP_WIN_MBAR);

	अगर (!csr_phys || !csr_len || !win_phys || !win_len)
		वापस -ENODEV;

	अगर (win_len < (CS0_START + CS0_SIZE))
		वापस -ENXIO;

	p->csr_base = ioremap(csr_phys, csr_len);
	अगर (!p->csr_base)
		वापस -ENOMEM;

	exp_timing_cs0 = पढ़ोl(p->csr_base + EXP_TIMING_CS0);
	अगर (!(exp_timing_cs0 & TIMING_CS_EN)) अणु
		dev_warn(&p->dev->dev, "Expansion Bus Chip Select 0 "
		       "is disabled.\n");
		err = -ENODEV;
		जाओ release;
	पूर्ण
	अगर ((exp_timing_cs0 & TIMING_MASK) == TIMING_MASK) अणु
		dev_warn(&p->dev->dev, "Expansion Bus Chip Select 0 "
		       "is configured for maximally slow access times.\n");
	पूर्ण
	p->map.name = DRV_NAME;
	p->map.bankwidth = (exp_timing_cs0 & TIMING_BYTE_EN) ? 1 : 2;
	p->map.phys = win_phys + CS0_START;
	p->map.size = CS0_SIZE;
	p->map.virt = ioremap(p->map.phys, p->map.size);
	अगर (!p->map.virt) अणु
		err = -ENOMEM;
		जाओ release;
	पूर्ण
	simple_map_init(&p->map);

	/* Enable ग_लिखोs to flash bank */
	exp_timing_cs0 |= TIMING_BOOT_ACCEL_DIS | TIMING_WR_EN;
	ग_लिखोl(exp_timing_cs0, p->csr_base + EXP_TIMING_CS0);

	वापस 0;

      release:
	iounmap(p->csr_base);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा pci_device_id vr_nor_pci_ids[] = अणु
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x500D)पूर्ण,
	अणु0,पूर्ण
पूर्ण;

अटल व्योम vr_nor_pci_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा vr_nor_mtd *p = pci_get_drvdata(dev);

	vr_nor_destroy_partitions(p);
	vr_nor_destroy_mtd_setup(p);
	vr_nor_destroy_maps(p);
	kमुक्त(p);
	pci_release_regions(dev);
	pci_disable_device(dev);
पूर्ण

अटल पूर्णांक vr_nor_pci_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा vr_nor_mtd *p = शून्य;
	अचिन्हित पूर्णांक exp_timing_cs0;
	पूर्णांक err;

	err = pci_enable_device(dev);
	अगर (err)
		जाओ out;

	err = pci_request_regions(dev, DRV_NAME);
	अगर (err)
		जाओ disable_dev;

	p = kzalloc(माप(*p), GFP_KERNEL);
	err = -ENOMEM;
	अगर (!p)
		जाओ release;

	p->dev = dev;

	err = vr_nor_init_maps(p);
	अगर (err)
		जाओ release;

	err = vr_nor_mtd_setup(p);
	अगर (err)
		जाओ destroy_maps;

	err = vr_nor_init_partitions(p);
	अगर (err)
		जाओ destroy_mtd_setup;

	pci_set_drvdata(dev, p);

	वापस 0;

      destroy_mtd_setup:
	map_destroy(p->info);

      destroy_maps:
	/* ग_लिखो-protect the flash bank */
	exp_timing_cs0 = पढ़ोl(p->csr_base + EXP_TIMING_CS0);
	exp_timing_cs0 &= ~TIMING_WR_EN;
	ग_लिखोl(exp_timing_cs0, p->csr_base + EXP_TIMING_CS0);

	/* unmap the flash winकरोw */
	iounmap(p->map.virt);

	/* unmap the csr winकरोw */
	iounmap(p->csr_base);

      release:
	kमुक्त(p);
	pci_release_regions(dev);

      disable_dev:
	pci_disable_device(dev);

      out:
	वापस err;
पूर्ण

अटल काष्ठा pci_driver vr_nor_pci_driver = अणु
	.name = DRV_NAME,
	.probe = vr_nor_pci_probe,
	.हटाओ = vr_nor_pci_हटाओ,
	.id_table = vr_nor_pci_ids,
पूर्ण;

module_pci_driver(vr_nor_pci_driver);

MODULE_AUTHOR("Andy Lowe");
MODULE_DESCRIPTION("MTD map driver for NOR flash on Intel Vermilion Range");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, vr_nor_pci_ids);
