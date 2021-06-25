<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018-2019 Synopsys, Inc. and/or its affiliates.
 * Synopsys DesignWare eDMA PCIe driver
 *
 * Author: Gustavo Pimentel <gustavo.pimentel@synopsys.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/device.h>
#समावेश <linux/dma/edma.h>
#समावेश <linux/pci-epf.h>
#समावेश <linux/msi.h>
#समावेश <linux/bitfield.h>

#समावेश "dw-edma-core.h"

#घोषणा DW_PCIE_VSEC_DMA_ID			0x6
#घोषणा DW_PCIE_VSEC_DMA_BAR			GENMASK(10, 8)
#घोषणा DW_PCIE_VSEC_DMA_MAP			GENMASK(2, 0)
#घोषणा DW_PCIE_VSEC_DMA_WR_CH			GENMASK(9, 0)
#घोषणा DW_PCIE_VSEC_DMA_RD_CH			GENMASK(25, 16)

#घोषणा DW_BLOCK(a, b, c) \
	अणु \
		.bar = a, \
		.off = b, \
		.sz = c, \
	पूर्ण,

काष्ठा dw_edma_block अणु
	क्रमागत pci_barno			bar;
	off_t				off;
	माप_प्रकार				sz;
पूर्ण;

काष्ठा dw_edma_pcie_data अणु
	/* eDMA रेजिस्टरs location */
	काष्ठा dw_edma_block		rg;
	/* eDMA memory linked list location */
	काष्ठा dw_edma_block		ll_wr[EDMA_MAX_WR_CH];
	काष्ठा dw_edma_block		ll_rd[EDMA_MAX_RD_CH];
	/* eDMA memory data location */
	काष्ठा dw_edma_block		dt_wr[EDMA_MAX_WR_CH];
	काष्ठा dw_edma_block		dt_rd[EDMA_MAX_RD_CH];
	/* Other */
	क्रमागत dw_edma_map_क्रमmat		mf;
	u8				irqs;
	u16				wr_ch_cnt;
	u16				rd_ch_cnt;
पूर्ण;

अटल स्थिर काष्ठा dw_edma_pcie_data snps_edda_data = अणु
	/* eDMA रेजिस्टरs location */
	.rg.bar				= BAR_0,
	.rg.off				= 0x00001000,	/*  4 Kbytes */
	.rg.sz				= 0x00002000,	/*  8 Kbytes */
	/* eDMA memory linked list location */
	.ll_wr = अणु
		/* Channel 0 - BAR 2, offset 0 Mbytes, size 2 Kbytes */
		DW_BLOCK(BAR_2, 0x00000000, 0x00000800)
		/* Channel 1 - BAR 2, offset 2 Mbytes, size 2 Kbytes */
		DW_BLOCK(BAR_2, 0x00200000, 0x00000800)
	पूर्ण,
	.ll_rd = अणु
		/* Channel 0 - BAR 2, offset 4 Mbytes, size 2 Kbytes */
		DW_BLOCK(BAR_2, 0x00400000, 0x00000800)
		/* Channel 1 - BAR 2, offset 6 Mbytes, size 2 Kbytes */
		DW_BLOCK(BAR_2, 0x00600000, 0x00000800)
	पूर्ण,
	/* eDMA memory data location */
	.dt_wr = अणु
		/* Channel 0 - BAR 2, offset 8 Mbytes, size 2 Kbytes */
		DW_BLOCK(BAR_2, 0x00800000, 0x00000800)
		/* Channel 1 - BAR 2, offset 9 Mbytes, size 2 Kbytes */
		DW_BLOCK(BAR_2, 0x00900000, 0x00000800)
	पूर्ण,
	.dt_rd = अणु
		/* Channel 0 - BAR 2, offset 10 Mbytes, size 2 Kbytes */
		DW_BLOCK(BAR_2, 0x00a00000, 0x00000800)
		/* Channel 1 - BAR 2, offset 11 Mbytes, size 2 Kbytes */
		DW_BLOCK(BAR_2, 0x00b00000, 0x00000800)
	पूर्ण,
	/* Other */
	.mf				= EDMA_MF_EDMA_UNROLL,
	.irqs				= 1,
	.wr_ch_cnt			= 2,
	.rd_ch_cnt			= 2,
पूर्ण;

अटल पूर्णांक dw_edma_pcie_irq_vector(काष्ठा device *dev, अचिन्हित पूर्णांक nr)
अणु
	वापस pci_irq_vector(to_pci_dev(dev), nr);
पूर्ण

अटल स्थिर काष्ठा dw_edma_core_ops dw_edma_pcie_core_ops = अणु
	.irq_vector = dw_edma_pcie_irq_vector,
पूर्ण;

अटल व्योम dw_edma_pcie_get_vsec_dma_data(काष्ठा pci_dev *pdev,
					   काष्ठा dw_edma_pcie_data *pdata)
अणु
	u32 val, map;
	u16 vsec;
	u64 off;

	vsec = pci_find_vsec_capability(pdev, PCI_VENDOR_ID_SYNOPSYS,
					DW_PCIE_VSEC_DMA_ID);
	अगर (!vsec)
		वापस;

	pci_पढ़ो_config_dword(pdev, vsec + PCI_VNDR_HEADER, &val);
	अगर (PCI_VNDR_HEADER_REV(val) != 0x00 ||
	    PCI_VNDR_HEADER_LEN(val) != 0x18)
		वापस;

	pci_dbg(pdev, "Detected PCIe Vendor-Specific Extended Capability DMA\n");
	pci_पढ़ो_config_dword(pdev, vsec + 0x8, &val);
	map = FIELD_GET(DW_PCIE_VSEC_DMA_MAP, val);
	अगर (map != EDMA_MF_EDMA_LEGACY &&
	    map != EDMA_MF_EDMA_UNROLL &&
	    map != EDMA_MF_HDMA_COMPAT)
		वापस;

	pdata->mf = map;
	pdata->rg.bar = FIELD_GET(DW_PCIE_VSEC_DMA_BAR, val);

	pci_पढ़ो_config_dword(pdev, vsec + 0xc, &val);
	pdata->wr_ch_cnt = min_t(u16, pdata->wr_ch_cnt,
				 FIELD_GET(DW_PCIE_VSEC_DMA_WR_CH, val));
	pdata->rd_ch_cnt = min_t(u16, pdata->rd_ch_cnt,
				 FIELD_GET(DW_PCIE_VSEC_DMA_RD_CH, val));

	pci_पढ़ो_config_dword(pdev, vsec + 0x14, &val);
	off = val;
	pci_पढ़ो_config_dword(pdev, vsec + 0x10, &val);
	off <<= 32;
	off |= val;
	pdata->rg.off = off;
पूर्ण

अटल पूर्णांक dw_edma_pcie_probe(काष्ठा pci_dev *pdev,
			      स्थिर काष्ठा pci_device_id *pid)
अणु
	काष्ठा dw_edma_pcie_data *pdata = (व्योम *)pid->driver_data;
	काष्ठा dw_edma_pcie_data vsec_data;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा dw_edma_chip *chip;
	काष्ठा dw_edma *dw;
	पूर्णांक err, nr_irqs;
	पूर्णांक i, mask;

	/* Enable PCI device */
	err = pcim_enable_device(pdev);
	अगर (err) अणु
		pci_err(pdev, "enabling device failed\n");
		वापस err;
	पूर्ण

	स_नकल(&vsec_data, pdata, माप(काष्ठा dw_edma_pcie_data));

	/*
	 * Tries to find अगर exists a PCIe Venकरोr-Specअगरic Extended Capability
	 * क्रम the DMA, अगर one exists, then reconfigures it.
	 */
	dw_edma_pcie_get_vsec_dma_data(pdev, &vsec_data);

	/* Mapping PCI BAR regions */
	mask = BIT(vsec_data.rg.bar);
	क्रम (i = 0; i < vsec_data.wr_ch_cnt; i++) अणु
		mask |= BIT(vsec_data.ll_wr[i].bar);
		mask |= BIT(vsec_data.dt_wr[i].bar);
	पूर्ण
	क्रम (i = 0; i < vsec_data.rd_ch_cnt; i++) अणु
		mask |= BIT(vsec_data.ll_rd[i].bar);
		mask |= BIT(vsec_data.dt_rd[i].bar);
	पूर्ण
	err = pcim_iomap_regions(pdev, mask, pci_name(pdev));
	अगर (err) अणु
		pci_err(pdev, "eDMA BAR I/O remapping failed\n");
		वापस err;
	पूर्ण

	pci_set_master(pdev);

	/* DMA configuration */
	err = pci_set_dma_mask(pdev, DMA_BIT_MASK(64));
	अगर (!err) अणु
		err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64));
		अगर (err) अणु
			pci_err(pdev, "consistent DMA mask 64 set failed\n");
			वापस err;
		पूर्ण
	पूर्ण अन्यथा अणु
		pci_err(pdev, "DMA mask 64 set failed\n");

		err = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
		अगर (err) अणु
			pci_err(pdev, "DMA mask 32 set failed\n");
			वापस err;
		पूर्ण

		err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32));
		अगर (err) अणु
			pci_err(pdev, "consistent DMA mask 32 set failed\n");
			वापस err;
		पूर्ण
	पूर्ण

	/* Data काष्ठाure allocation */
	chip = devm_kzalloc(dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	dw = devm_kzalloc(dev, माप(*dw), GFP_KERNEL);
	अगर (!dw)
		वापस -ENOMEM;

	/* IRQs allocation */
	nr_irqs = pci_alloc_irq_vectors(pdev, 1, vsec_data.irqs,
					PCI_IRQ_MSI | PCI_IRQ_MSIX);
	अगर (nr_irqs < 1) अणु
		pci_err(pdev, "fail to alloc IRQ vector (number of IRQs=%u)\n",
			nr_irqs);
		वापस -EPERM;
	पूर्ण

	/* Data काष्ठाure initialization */
	chip->dw = dw;
	chip->dev = dev;
	chip->id = pdev->devfn;
	chip->irq = pdev->irq;

	dw->mf = vsec_data.mf;
	dw->nr_irqs = nr_irqs;
	dw->ops = &dw_edma_pcie_core_ops;
	dw->wr_ch_cnt = vsec_data.wr_ch_cnt;
	dw->rd_ch_cnt = vsec_data.rd_ch_cnt;

	dw->rg_region.vaddr = pcim_iomap_table(pdev)[vsec_data.rg.bar];
	अगर (!dw->rg_region.vaddr)
		वापस -ENOMEM;

	dw->rg_region.vaddr += vsec_data.rg.off;
	dw->rg_region.paddr = pdev->resource[vsec_data.rg.bar].start;
	dw->rg_region.paddr += vsec_data.rg.off;
	dw->rg_region.sz = vsec_data.rg.sz;

	क्रम (i = 0; i < dw->wr_ch_cnt; i++) अणु
		काष्ठा dw_edma_region *ll_region = &dw->ll_region_wr[i];
		काष्ठा dw_edma_region *dt_region = &dw->dt_region_wr[i];
		काष्ठा dw_edma_block *ll_block = &vsec_data.ll_wr[i];
		काष्ठा dw_edma_block *dt_block = &vsec_data.dt_wr[i];

		ll_region->vaddr = pcim_iomap_table(pdev)[ll_block->bar];
		अगर (!ll_region->vaddr)
			वापस -ENOMEM;

		ll_region->vaddr += ll_block->off;
		ll_region->paddr = pdev->resource[ll_block->bar].start;
		ll_region->paddr += ll_block->off;
		ll_region->sz = ll_block->sz;

		dt_region->vaddr = pcim_iomap_table(pdev)[dt_block->bar];
		अगर (!dt_region->vaddr)
			वापस -ENOMEM;

		dt_region->vaddr += dt_block->off;
		dt_region->paddr = pdev->resource[dt_block->bar].start;
		dt_region->paddr += dt_block->off;
		dt_region->sz = dt_block->sz;
	पूर्ण

	क्रम (i = 0; i < dw->rd_ch_cnt; i++) अणु
		काष्ठा dw_edma_region *ll_region = &dw->ll_region_rd[i];
		काष्ठा dw_edma_region *dt_region = &dw->dt_region_rd[i];
		काष्ठा dw_edma_block *ll_block = &vsec_data.ll_rd[i];
		काष्ठा dw_edma_block *dt_block = &vsec_data.dt_rd[i];

		ll_region->vaddr = pcim_iomap_table(pdev)[ll_block->bar];
		अगर (!ll_region->vaddr)
			वापस -ENOMEM;

		ll_region->vaddr += ll_block->off;
		ll_region->paddr = pdev->resource[ll_block->bar].start;
		ll_region->paddr += ll_block->off;
		ll_region->sz = ll_block->sz;

		dt_region->vaddr = pcim_iomap_table(pdev)[dt_block->bar];
		अगर (!dt_region->vaddr)
			वापस -ENOMEM;

		dt_region->vaddr += dt_block->off;
		dt_region->paddr = pdev->resource[dt_block->bar].start;
		dt_region->paddr += dt_block->off;
		dt_region->sz = dt_block->sz;
	पूर्ण

	/* Debug info */
	अगर (dw->mf == EDMA_MF_EDMA_LEGACY)
		pci_dbg(pdev, "Version:\teDMA Port Logic (0x%x)\n", dw->mf);
	अन्यथा अगर (dw->mf == EDMA_MF_EDMA_UNROLL)
		pci_dbg(pdev, "Version:\teDMA Unroll (0x%x)\n", dw->mf);
	अन्यथा अगर (dw->mf == EDMA_MF_HDMA_COMPAT)
		pci_dbg(pdev, "Version:\tHDMA Compatible (0x%x)\n", dw->mf);
	अन्यथा
		pci_dbg(pdev, "Version:\tUnknown (0x%x)\n", dw->mf);

	pci_dbg(pdev, "Registers:\tBAR=%u, off=0x%.8lx, sz=0x%zx bytes, addr(v=%p, p=%pa)\n",
		vsec_data.rg.bar, vsec_data.rg.off, vsec_data.rg.sz,
		dw->rg_region.vaddr, &dw->rg_region.paddr);


	क्रम (i = 0; i < dw->wr_ch_cnt; i++) अणु
		pci_dbg(pdev, "L. List:\tWRITE CH%.2u, BAR=%u, off=0x%.8lx, sz=0x%zx bytes, addr(v=%p, p=%pa)\n",
			i, vsec_data.ll_wr[i].bar,
			vsec_data.ll_wr[i].off, dw->ll_region_wr[i].sz,
			dw->ll_region_wr[i].vaddr, &dw->ll_region_wr[i].paddr);

		pci_dbg(pdev, "Data:\tWRITE CH%.2u, BAR=%u, off=0x%.8lx, sz=0x%zx bytes, addr(v=%p, p=%pa)\n",
			i, vsec_data.dt_wr[i].bar,
			vsec_data.dt_wr[i].off, dw->dt_region_wr[i].sz,
			dw->dt_region_wr[i].vaddr, &dw->dt_region_wr[i].paddr);
	पूर्ण

	क्रम (i = 0; i < dw->rd_ch_cnt; i++) अणु
		pci_dbg(pdev, "L. List:\tREAD CH%.2u, BAR=%u, off=0x%.8lx, sz=0x%zx bytes, addr(v=%p, p=%pa)\n",
			i, vsec_data.ll_rd[i].bar,
			vsec_data.ll_rd[i].off, dw->ll_region_rd[i].sz,
			dw->ll_region_rd[i].vaddr, &dw->ll_region_rd[i].paddr);

		pci_dbg(pdev, "Data:\tREAD CH%.2u, BAR=%u, off=0x%.8lx, sz=0x%zx bytes, addr(v=%p, p=%pa)\n",
			i, vsec_data.dt_rd[i].bar,
			vsec_data.dt_rd[i].off, dw->dt_region_rd[i].sz,
			dw->dt_region_rd[i].vaddr, &dw->dt_region_rd[i].paddr);
	पूर्ण

	pci_dbg(pdev, "Nr. IRQs:\t%u\n", dw->nr_irqs);

	/* Validating अगर PCI पूर्णांकerrupts were enabled */
	अगर (!pci_dev_msi_enabled(pdev)) अणु
		pci_err(pdev, "enable interrupt failed\n");
		वापस -EPERM;
	पूर्ण

	dw->irq = devm_kसुस्मृति(dev, nr_irqs, माप(*dw->irq), GFP_KERNEL);
	अगर (!dw->irq)
		वापस -ENOMEM;

	/* Starting eDMA driver */
	err = dw_edma_probe(chip);
	अगर (err) अणु
		pci_err(pdev, "eDMA probe failed\n");
		वापस err;
	पूर्ण

	/* Saving data काष्ठाure reference */
	pci_set_drvdata(pdev, chip);

	वापस 0;
पूर्ण

अटल व्योम dw_edma_pcie_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा dw_edma_chip *chip = pci_get_drvdata(pdev);
	पूर्णांक err;

	/* Stopping eDMA driver */
	err = dw_edma_हटाओ(chip);
	अगर (err)
		pci_warn(pdev, "can't remove device properly: %d\n", err);

	/* Freeing IRQs */
	pci_मुक्त_irq_vectors(pdev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id dw_edma_pcie_id_table[] = अणु
	अणु PCI_DEVICE_DATA(SYNOPSYS, EDDA, &snps_edda_data) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, dw_edma_pcie_id_table);

अटल काष्ठा pci_driver dw_edma_pcie_driver = अणु
	.name		= "dw-edma-pcie",
	.id_table	= dw_edma_pcie_id_table,
	.probe		= dw_edma_pcie_probe,
	.हटाओ		= dw_edma_pcie_हटाओ,
पूर्ण;

module_pci_driver(dw_edma_pcie_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Synopsys DesignWare eDMA PCIe driver");
MODULE_AUTHOR("Gustavo Pimentel <gustavo.pimentel@synopsys.com>");
