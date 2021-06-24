<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2005-2008, PA Semi, Inc
 *
 * Maपूर्णांकained by: Olof Johansson <olof@lixom.net>
 */

#अघोषित DEBUG

#समावेश <linux/memblock.h>
#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/pci.h>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/firmware.h>

#समावेश "pasemi.h"

#घोषणा IOBMAP_PAGE_SHIFT	12
#घोषणा IOBMAP_PAGE_SIZE	(1 << IOBMAP_PAGE_SHIFT)
#घोषणा IOBMAP_PAGE_MASK	(IOBMAP_PAGE_SIZE - 1)

#घोषणा IOB_BASE		0xe0000000
#घोषणा IOB_SIZE		0x3000
/* Configuration रेजिस्टरs */
#घोषणा IOBCAP_REG		0x40
#घोषणा IOBCOM_REG		0x100
/* Enable IOB address translation */
#घोषणा IOBCOM_ATEN		0x00000100

/* Address decode configuration रेजिस्टर */
#घोषणा IOB_AD_REG		0x14c
/* IOBCOM_AD_REG fields */
#घोषणा IOB_AD_VGPRT		0x00000e00
#घोषणा IOB_AD_VGAEN		0x00000100
/* Direct mapping settings */
#घोषणा IOB_AD_MPSEL_MASK	0x00000030
#घोषणा IOB_AD_MPSEL_B38	0x00000000
#घोषणा IOB_AD_MPSEL_B40	0x00000010
#घोषणा IOB_AD_MPSEL_B42	0x00000020
/* Translation winकरोw size / enable */
#घोषणा IOB_AD_TRNG_MASK	0x00000003
#घोषणा IOB_AD_TRNG_256M	0x00000000
#घोषणा IOB_AD_TRNG_2G		0x00000001
#घोषणा IOB_AD_TRNG_128G	0x00000003

#घोषणा IOB_TABLEBASE_REG	0x154

/* Base of the 64 4-byte L1 रेजिस्टरs */
#घोषणा IOB_XLT_L1_REGBASE	0x2b00

/* Register to invalidate TLB entries */
#घोषणा IOB_AT_INVAL_TLB_REG	0x2d00

/* The top two bits of the level 1 entry contains valid and type flags */
#घोषणा IOBMAP_L1E_V		0x40000000
#घोषणा IOBMAP_L1E_V_B		0x80000000

/* For big page entries, the bottom two bits contains flags */
#घोषणा IOBMAP_L1E_BIG_CACHED	0x00000002
#घोषणा IOBMAP_L1E_BIG_PRIORITY	0x00000001

/* For regular level 2 entries, top 2 bits contain valid and cache flags */
#घोषणा IOBMAP_L2E_V		0x80000000
#घोषणा IOBMAP_L2E_V_CACHED	0xc0000000

अटल व्योम __iomem *iob;
अटल u32 iob_l1_emptyval;
अटल u32 iob_l2_emptyval;
अटल u32 *iob_l2_base;

अटल काष्ठा iommu_table iommu_table_iobmap;
अटल पूर्णांक iommu_table_iobmap_inited;

अटल पूर्णांक iobmap_build(काष्ठा iommu_table *tbl, दीर्घ index,
			 दीर्घ npages, अचिन्हित दीर्घ uaddr,
			 क्रमागत dma_data_direction direction,
			 अचिन्हित दीर्घ attrs)
अणु
	u32 *ip;
	u32 rpn;
	अचिन्हित दीर्घ bus_addr;

	pr_debug("iobmap: build at: %lx, %lx, addr: %lx\n", index, npages, uaddr);

	bus_addr = (tbl->it_offset + index) << IOBMAP_PAGE_SHIFT;

	ip = ((u32 *)tbl->it_base) + index;

	जबतक (npages--) अणु
		rpn = __pa(uaddr) >> IOBMAP_PAGE_SHIFT;

		*(ip++) = IOBMAP_L2E_V | rpn;
		/* invalidate tlb, can be optimized more */
		out_le32(iob+IOB_AT_INVAL_TLB_REG, bus_addr >> 14);

		uaddr += IOBMAP_PAGE_SIZE;
		bus_addr += IOBMAP_PAGE_SIZE;
	पूर्ण
	वापस 0;
पूर्ण


अटल व्योम iobmap_मुक्त(काष्ठा iommu_table *tbl, दीर्घ index,
			दीर्घ npages)
अणु
	u32 *ip;
	अचिन्हित दीर्घ bus_addr;

	pr_debug("iobmap: free at: %lx, %lx\n", index, npages);

	bus_addr = (tbl->it_offset + index) << IOBMAP_PAGE_SHIFT;

	ip = ((u32 *)tbl->it_base) + index;

	जबतक (npages--) अणु
		*(ip++) = iob_l2_emptyval;
		/* invalidate tlb, can be optimized more */
		out_le32(iob+IOB_AT_INVAL_TLB_REG, bus_addr >> 14);
		bus_addr += IOBMAP_PAGE_SIZE;
	पूर्ण
पूर्ण

अटल काष्ठा iommu_table_ops iommu_table_iobmap_ops = अणु
	.set = iobmap_build,
	.clear  = iobmap_मुक्त
पूर्ण;

अटल व्योम iommu_table_iobmap_setup(व्योम)
अणु
	pr_debug(" -> %s\n", __func__);
	iommu_table_iobmap.it_busno = 0;
	iommu_table_iobmap.it_offset = 0;
	iommu_table_iobmap.it_page_shअगरt = IOBMAP_PAGE_SHIFT;

	/* it_size is in number of entries */
	iommu_table_iobmap.it_size =
		0x80000000 >> iommu_table_iobmap.it_page_shअगरt;

	/* Initialize the common IOMMU code */
	iommu_table_iobmap.it_base = (अचिन्हित दीर्घ)iob_l2_base;
	iommu_table_iobmap.it_index = 0;
	/* XXXOJN tune this to aव्योम IOB cache invals.
	 * Should probably be 8 (64 bytes)
	 */
	iommu_table_iobmap.it_blocksize = 4;
	iommu_table_iobmap.it_ops = &iommu_table_iobmap_ops;
	अगर (!iommu_init_table(&iommu_table_iobmap, 0, 0, 0))
		panic("Failed to initialize iommu table");

	pr_debug(" <- %s\n", __func__);
पूर्ण



अटल व्योम pci_dma_bus_setup_pasemi(काष्ठा pci_bus *bus)
अणु
	pr_debug("pci_dma_bus_setup, bus %p, bus->self %p\n", bus, bus->self);

	अगर (!iommu_table_iobmap_inited) अणु
		iommu_table_iobmap_inited = 1;
		iommu_table_iobmap_setup();
	पूर्ण
पूर्ण


अटल व्योम pci_dma_dev_setup_pasemi(काष्ठा pci_dev *dev)
अणु
	pr_debug("pci_dma_dev_setup, dev %p (%s)\n", dev, pci_name(dev));

#अगर !defined(CONFIG_PPC_PASEMI_IOMMU_DMA_FORCE)
	/* For non-LPAR environment, करोn't translate anything क्रम the DMA
	 * engine. The exception to this is अगर the user has enabled
	 * CONFIG_PPC_PASEMI_IOMMU_DMA_FORCE at build समय.
	 */
	अगर (dev->venकरोr == 0x1959 && dev->device == 0xa007 &&
	    !firmware_has_feature(FW_FEATURE_LPAR)) अणु
		dev->dev.dma_ops = शून्य;
		/*
		 * Set the coherent DMA mask to prevent the iommu
		 * being used unnecessarily
		 */
		dev->dev.coherent_dma_mask = DMA_BIT_MASK(44);
		वापस;
	पूर्ण
#पूर्ण_अगर

	set_iommu_table_base(&dev->dev, &iommu_table_iobmap);
पूर्ण

अटल पूर्णांक __init iob_init(काष्ठा device_node *dn)
अणु
	अचिन्हित दीर्घ पंचांगp;
	u32 regword;
	पूर्णांक i;

	pr_debug(" -> %s\n", __func__);

	/* For 2G space, 8x64 pages (2^21 bytes) is max total l2 size */
	iob_l2_base = memblock_alloc_try_nid_raw(1UL << 21, 1UL << 21,
					MEMBLOCK_LOW_LIMIT, 0x80000000,
					NUMA_NO_NODE);
	अगर (!iob_l2_base)
		panic("%s: Failed to allocate %lu bytes align=0x%lx max_addr=%x\n",
		      __func__, 1UL << 21, 1UL << 21, 0x80000000);

	pr_info("IOBMAP L2 allocated at: %p\n", iob_l2_base);

	/* Allocate a spare page to map all invalid IOTLB pages. */
	पंचांगp = memblock_phys_alloc(IOBMAP_PAGE_SIZE, IOBMAP_PAGE_SIZE);
	अगर (!पंचांगp)
		panic("IOBMAP: Cannot allocate spare page!");
	/* Empty l1 is marked invalid */
	iob_l1_emptyval = 0;
	/* Empty l2 is mapped to dummy page */
	iob_l2_emptyval = IOBMAP_L2E_V | (पंचांगp >> IOBMAP_PAGE_SHIFT);

	iob = ioremap(IOB_BASE, IOB_SIZE);
	अगर (!iob)
		panic("IOBMAP: Cannot map registers!");

	/* setup direct mapping of the L1 entries */
	क्रम (i = 0; i < 64; i++) अणु
		/* Each L1 covers 32MB, i.e. 8K entries = 32K of ram */
		regword = IOBMAP_L1E_V | (__pa(iob_l2_base + i*0x2000) >> 12);
		out_le32(iob+IOB_XLT_L1_REGBASE+i*4, regword);
	पूर्ण

	/* set 2GB translation winकरोw, based at 0 */
	regword = in_le32(iob+IOB_AD_REG);
	regword &= ~IOB_AD_TRNG_MASK;
	regword |= IOB_AD_TRNG_2G;
	out_le32(iob+IOB_AD_REG, regword);

	/* Enable translation */
	regword = in_le32(iob+IOBCOM_REG);
	regword |= IOBCOM_ATEN;
	out_le32(iob+IOBCOM_REG, regword);

	pr_debug(" <- %s\n", __func__);

	वापस 0;
पूर्ण


/* These are called very early. */
व्योम __init iommu_init_early_pasemi(व्योम)
अणु
	पूर्णांक iommu_off;

#अगर_अघोषित CONFIG_PPC_PASEMI_IOMMU
	iommu_off = 1;
#अन्यथा
	iommu_off = of_chosen &&
			of_get_property(of_chosen, "linux,iommu-off", शून्य);
#पूर्ण_अगर
	अगर (iommu_off)
		वापस;

	iob_init(शून्य);

	pasemi_pci_controller_ops.dma_dev_setup = pci_dma_dev_setup_pasemi;
	pasemi_pci_controller_ops.dma_bus_setup = pci_dma_bus_setup_pasemi;
	set_pci_dma_ops(&dma_iommu_ops);
पूर्ण
