<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AMD Secure Processor device driver
 *
 * Copyright (C) 2013,2019 Advanced Micro Devices, Inc.
 *
 * Author: Tom Lendacky <thomas.lendacky@amd.com>
 * Author: Gary R Hook <gary.hook@amd.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/delay.h>
#समावेश <linux/ccp.h>

#समावेश "ccp-dev.h"
#समावेश "psp-dev.h"

#घोषणा MSIX_VECTORS			2

काष्ठा sp_pci अणु
	पूर्णांक msix_count;
	काष्ठा msix_entry msix_entry[MSIX_VECTORS];
पूर्ण;
अटल काष्ठा sp_device *sp_dev_master;

अटल पूर्णांक sp_get_msix_irqs(काष्ठा sp_device *sp)
अणु
	काष्ठा sp_pci *sp_pci = sp->dev_specअगरic;
	काष्ठा device *dev = sp->dev;
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	पूर्णांक v, ret;

	क्रम (v = 0; v < ARRAY_SIZE(sp_pci->msix_entry); v++)
		sp_pci->msix_entry[v].entry = v;

	ret = pci_enable_msix_range(pdev, sp_pci->msix_entry, 1, v);
	अगर (ret < 0)
		वापस ret;

	sp_pci->msix_count = ret;
	sp->use_tasklet = true;

	sp->psp_irq = sp_pci->msix_entry[0].vector;
	sp->ccp_irq = (sp_pci->msix_count > 1) ? sp_pci->msix_entry[1].vector
					       : sp_pci->msix_entry[0].vector;
	वापस 0;
पूर्ण

अटल पूर्णांक sp_get_msi_irq(काष्ठा sp_device *sp)
अणु
	काष्ठा device *dev = sp->dev;
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	पूर्णांक ret;

	ret = pci_enable_msi(pdev);
	अगर (ret)
		वापस ret;

	sp->ccp_irq = pdev->irq;
	sp->psp_irq = pdev->irq;

	वापस 0;
पूर्ण

अटल पूर्णांक sp_get_irqs(काष्ठा sp_device *sp)
अणु
	काष्ठा device *dev = sp->dev;
	पूर्णांक ret;

	ret = sp_get_msix_irqs(sp);
	अगर (!ret)
		वापस 0;

	/* Couldn't get MSI-X vectors, try MSI */
	dev_notice(dev, "could not enable MSI-X (%d), trying MSI\n", ret);
	ret = sp_get_msi_irq(sp);
	अगर (!ret)
		वापस 0;

	/* Couldn't get MSI पूर्णांकerrupt */
	dev_notice(dev, "could not enable MSI (%d)\n", ret);

	वापस ret;
पूर्ण

अटल व्योम sp_मुक्त_irqs(काष्ठा sp_device *sp)
अणु
	काष्ठा sp_pci *sp_pci = sp->dev_specअगरic;
	काष्ठा device *dev = sp->dev;
	काष्ठा pci_dev *pdev = to_pci_dev(dev);

	अगर (sp_pci->msix_count)
		pci_disable_msix(pdev);
	अन्यथा अगर (sp->psp_irq)
		pci_disable_msi(pdev);

	sp->ccp_irq = 0;
	sp->psp_irq = 0;
पूर्ण

अटल bool sp_pci_is_master(काष्ठा sp_device *sp)
अणु
	काष्ठा device *dev_cur, *dev_new;
	काष्ठा pci_dev *pdev_cur, *pdev_new;

	dev_new = sp->dev;
	dev_cur = sp_dev_master->dev;

	pdev_new = to_pci_dev(dev_new);
	pdev_cur = to_pci_dev(dev_cur);

	अगर (pdev_new->bus->number < pdev_cur->bus->number)
		वापस true;

	अगर (PCI_SLOT(pdev_new->devfn) < PCI_SLOT(pdev_cur->devfn))
		वापस true;

	अगर (PCI_FUNC(pdev_new->devfn) < PCI_FUNC(pdev_cur->devfn))
		वापस true;

	वापस false;
पूर्ण

अटल व्योम psp_set_master(काष्ठा sp_device *sp)
अणु
	अगर (!sp_dev_master) अणु
		sp_dev_master = sp;
		वापस;
	पूर्ण

	अगर (sp_pci_is_master(sp))
		sp_dev_master = sp;
पूर्ण

अटल काष्ठा sp_device *psp_get_master(व्योम)
अणु
	वापस sp_dev_master;
पूर्ण

अटल व्योम psp_clear_master(काष्ठा sp_device *sp)
अणु
	अगर (sp == sp_dev_master) अणु
		sp_dev_master = शून्य;
		dev_dbg(sp->dev, "Cleared sp_dev_master\n");
	पूर्ण
पूर्ण

अटल पूर्णांक sp_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा sp_device *sp;
	काष्ठा sp_pci *sp_pci;
	काष्ठा device *dev = &pdev->dev;
	व्योम __iomem * स्थिर *iomap_table;
	पूर्णांक bar_mask;
	पूर्णांक ret;

	ret = -ENOMEM;
	sp = sp_alloc_काष्ठा(dev);
	अगर (!sp)
		जाओ e_err;

	sp_pci = devm_kzalloc(dev, माप(*sp_pci), GFP_KERNEL);
	अगर (!sp_pci)
		जाओ e_err;

	sp->dev_specअगरic = sp_pci;
	sp->dev_vdata = (काष्ठा sp_dev_vdata *)id->driver_data;
	अगर (!sp->dev_vdata) अणु
		ret = -ENODEV;
		dev_err(dev, "missing driver data\n");
		जाओ e_err;
	पूर्ण

	ret = pcim_enable_device(pdev);
	अगर (ret) अणु
		dev_err(dev, "pcim_enable_device failed (%d)\n", ret);
		जाओ e_err;
	पूर्ण

	bar_mask = pci_select_bars(pdev, IORESOURCE_MEM);
	ret = pcim_iomap_regions(pdev, bar_mask, "ccp");
	अगर (ret) अणु
		dev_err(dev, "pcim_iomap_regions failed (%d)\n", ret);
		जाओ e_err;
	पूर्ण

	iomap_table = pcim_iomap_table(pdev);
	अगर (!iomap_table) अणु
		dev_err(dev, "pcim_iomap_table failed\n");
		ret = -ENOMEM;
		जाओ e_err;
	पूर्ण

	sp->io_map = iomap_table[sp->dev_vdata->bar];
	अगर (!sp->io_map) अणु
		dev_err(dev, "ioremap failed\n");
		ret = -ENOMEM;
		जाओ e_err;
	पूर्ण

	ret = sp_get_irqs(sp);
	अगर (ret)
		जाओ e_err;

	pci_set_master(pdev);
	sp->set_psp_master_device = psp_set_master;
	sp->get_psp_master_device = psp_get_master;
	sp->clear_psp_master_device = psp_clear_master;

	ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(48));
	अगर (ret) अणु
		ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32));
		अगर (ret) अणु
			dev_err(dev, "dma_set_mask_and_coherent failed (%d)\n",
				ret);
			जाओ e_err;
		पूर्ण
	पूर्ण

	dev_set_drvdata(dev, sp);

	ret = sp_init(sp);
	अगर (ret)
		जाओ e_err;

	वापस 0;

e_err:
	dev_notice(dev, "initialization failed\n");
	वापस ret;
पूर्ण

अटल व्योम sp_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sp_device *sp = dev_get_drvdata(dev);

	अगर (!sp)
		वापस;

	sp_destroy(sp);

	sp_मुक्त_irqs(sp);
पूर्ण

अटल पूर्णांक __maybe_unused sp_pci_suspend(काष्ठा device *dev)
अणु
	काष्ठा sp_device *sp = dev_get_drvdata(dev);

	वापस sp_suspend(sp);
पूर्ण

अटल पूर्णांक __maybe_unused sp_pci_resume(काष्ठा device *dev)
अणु
	काष्ठा sp_device *sp = dev_get_drvdata(dev);

	वापस sp_resume(sp);
पूर्ण

#अगर_घोषित CONFIG_CRYPTO_DEV_SP_PSP
अटल स्थिर काष्ठा sev_vdata sevv1 = अणु
	.cmdresp_reg		= 0x10580,
	.cmdbuff_addr_lo_reg	= 0x105e0,
	.cmdbuff_addr_hi_reg	= 0x105e4,
पूर्ण;

अटल स्थिर काष्ठा sev_vdata sevv2 = अणु
	.cmdresp_reg		= 0x10980,
	.cmdbuff_addr_lo_reg	= 0x109e0,
	.cmdbuff_addr_hi_reg	= 0x109e4,
पूर्ण;

अटल स्थिर काष्ठा tee_vdata teev1 = अणु
	.cmdresp_reg		= 0x10544,
	.cmdbuff_addr_lo_reg	= 0x10548,
	.cmdbuff_addr_hi_reg	= 0x1054c,
	.ring_wptr_reg          = 0x10550,
	.ring_rptr_reg          = 0x10554,
पूर्ण;

अटल स्थिर काष्ठा psp_vdata pspv1 = अणु
	.sev			= &sevv1,
	.feature_reg		= 0x105fc,
	.पूर्णांकen_reg		= 0x10610,
	.पूर्णांकsts_reg		= 0x10614,
पूर्ण;

अटल स्थिर काष्ठा psp_vdata pspv2 = अणु
	.sev			= &sevv2,
	.feature_reg		= 0x109fc,
	.पूर्णांकen_reg		= 0x10690,
	.पूर्णांकsts_reg		= 0x10694,
पूर्ण;

अटल स्थिर काष्ठा psp_vdata pspv3 = अणु
	.tee			= &teev1,
	.feature_reg		= 0x109fc,
	.पूर्णांकen_reg		= 0x10690,
	.पूर्णांकsts_reg		= 0x10694,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा sp_dev_vdata dev_vdata[] = अणु
	अणु	/* 0 */
		.bar = 2,
#अगर_घोषित CONFIG_CRYPTO_DEV_SP_CCP
		.ccp_vdata = &ccpv3,
#पूर्ण_अगर
	पूर्ण,
	अणु	/* 1 */
		.bar = 2,
#अगर_घोषित CONFIG_CRYPTO_DEV_SP_CCP
		.ccp_vdata = &ccpv5a,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CRYPTO_DEV_SP_PSP
		.psp_vdata = &pspv1,
#पूर्ण_अगर
	पूर्ण,
	अणु	/* 2 */
		.bar = 2,
#अगर_घोषित CONFIG_CRYPTO_DEV_SP_CCP
		.ccp_vdata = &ccpv5b,
#पूर्ण_अगर
	पूर्ण,
	अणु	/* 3 */
		.bar = 2,
#अगर_घोषित CONFIG_CRYPTO_DEV_SP_CCP
		.ccp_vdata = &ccpv5a,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CRYPTO_DEV_SP_PSP
		.psp_vdata = &pspv2,
#पूर्ण_अगर
	पूर्ण,
	अणु	/* 4 */
		.bar = 2,
#अगर_घोषित CONFIG_CRYPTO_DEV_SP_CCP
		.ccp_vdata = &ccpv5a,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CRYPTO_DEV_SP_PSP
		.psp_vdata = &pspv3,
#पूर्ण_अगर
	पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा pci_device_id sp_pci_table[] = अणु
	अणु PCI_VDEVICE(AMD, 0x1537), (kernel_uदीर्घ_t)&dev_vdata[0] पूर्ण,
	अणु PCI_VDEVICE(AMD, 0x1456), (kernel_uदीर्घ_t)&dev_vdata[1] पूर्ण,
	अणु PCI_VDEVICE(AMD, 0x1468), (kernel_uदीर्घ_t)&dev_vdata[2] पूर्ण,
	अणु PCI_VDEVICE(AMD, 0x1486), (kernel_uदीर्घ_t)&dev_vdata[3] पूर्ण,
	अणु PCI_VDEVICE(AMD, 0x15DF), (kernel_uदीर्घ_t)&dev_vdata[4] पूर्ण,
	अणु PCI_VDEVICE(AMD, 0x1649), (kernel_uदीर्घ_t)&dev_vdata[4] पूर्ण,
	/* Last entry must be zero */
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, sp_pci_table);

अटल SIMPLE_DEV_PM_OPS(sp_pci_pm_ops, sp_pci_suspend, sp_pci_resume);

अटल काष्ठा pci_driver sp_pci_driver = अणु
	.name = "ccp",
	.id_table = sp_pci_table,
	.probe = sp_pci_probe,
	.हटाओ = sp_pci_हटाओ,
	.driver.pm = &sp_pci_pm_ops,
पूर्ण;

पूर्णांक sp_pci_init(व्योम)
अणु
	वापस pci_रेजिस्टर_driver(&sp_pci_driver);
पूर्ण

व्योम sp_pci_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&sp_pci_driver);
पूर्ण
