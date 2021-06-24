<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/* Copyright 2019 NXP */

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/fsl/ptp_qoriq.h>

#समावेश "enetc.h"

पूर्णांक enetc_phc_index = -1;
EXPORT_SYMBOL(enetc_phc_index);

अटल काष्ठा ptp_घड़ी_info enetc_ptp_caps = अणु
	.owner		= THIS_MODULE,
	.name		= "ENETC PTP clock",
	.max_adj	= 512000,
	.n_alarm	= 0,
	.n_ext_ts	= 2,
	.n_per_out	= 0,
	.n_pins		= 0,
	.pps		= 1,
	.adjfine	= ptp_qoriq_adjfine,
	.adjसमय	= ptp_qoriq_adjसमय,
	.समय_लो64	= ptp_qoriq_समय_लो,
	.समय_रखो64	= ptp_qoriq_समय_रखो,
	.enable		= ptp_qoriq_enable,
पूर्ण;

अटल पूर्णांक enetc_ptp_probe(काष्ठा pci_dev *pdev,
			   स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा ptp_qoriq *ptp_qoriq;
	व्योम __iomem *base;
	पूर्णांक err, len, n;

	अगर (pdev->dev.of_node && !of_device_is_available(pdev->dev.of_node)) अणु
		dev_info(&pdev->dev, "device is disabled, skipping\n");
		वापस -ENODEV;
	पूर्ण

	err = pci_enable_device_mem(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "device enable failed\n");
		वापस err;
	पूर्ण

	/* set up क्रम high or low dma */
	err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	अगर (err) अणु
		err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
		अगर (err) अणु
			dev_err(&pdev->dev,
				"DMA configuration failed: 0x%x\n", err);
			जाओ err_dma;
		पूर्ण
	पूर्ण

	err = pci_request_mem_regions(pdev, KBUILD_MODNAME);
	अगर (err) अणु
		dev_err(&pdev->dev, "pci_request_regions failed err=%d\n", err);
		जाओ err_pci_mem_reg;
	पूर्ण

	pci_set_master(pdev);

	ptp_qoriq = kzalloc(माप(*ptp_qoriq), GFP_KERNEL);
	अगर (!ptp_qoriq) अणु
		err = -ENOMEM;
		जाओ err_alloc_ptp;
	पूर्ण

	len = pci_resource_len(pdev, ENETC_BAR_REGS);

	base = ioremap(pci_resource_start(pdev, ENETC_BAR_REGS), len);
	अगर (!base) अणु
		err = -ENXIO;
		dev_err(&pdev->dev, "ioremap() failed\n");
		जाओ err_ioremap;
	पूर्ण

	/* Allocate 1 पूर्णांकerrupt */
	n = pci_alloc_irq_vectors(pdev, 1, 1, PCI_IRQ_MSIX);
	अगर (n != 1) अणु
		err = -EPERM;
		जाओ err_irq_vectors;
	पूर्ण

	ptp_qoriq->irq = pci_irq_vector(pdev, 0);

	err = request_irq(ptp_qoriq->irq, ptp_qoriq_isr, 0, DRIVER, ptp_qoriq);
	अगर (err) अणु
		dev_err(&pdev->dev, "request_irq() failed!\n");
		जाओ err_irq;
	पूर्ण

	ptp_qoriq->dev = &pdev->dev;

	err = ptp_qoriq_init(ptp_qoriq, base, &enetc_ptp_caps);
	अगर (err)
		जाओ err_no_घड़ी;

	enetc_phc_index = ptp_qoriq->phc_index;
	pci_set_drvdata(pdev, ptp_qoriq);

	वापस 0;

err_no_घड़ी:
	मुक्त_irq(ptp_qoriq->irq, ptp_qoriq);
err_irq:
	pci_मुक्त_irq_vectors(pdev);
err_irq_vectors:
	iounmap(base);
err_ioremap:
	kमुक्त(ptp_qoriq);
err_alloc_ptp:
	pci_release_mem_regions(pdev);
err_pci_mem_reg:
err_dma:
	pci_disable_device(pdev);

	वापस err;
पूर्ण

अटल व्योम enetc_ptp_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ptp_qoriq *ptp_qoriq = pci_get_drvdata(pdev);

	enetc_phc_index = -1;
	ptp_qoriq_मुक्त(ptp_qoriq);
	pci_मुक्त_irq_vectors(pdev);
	kमुक्त(ptp_qoriq);

	pci_release_mem_regions(pdev);
	pci_disable_device(pdev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id enetc_ptp_id_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_FREESCALE, ENETC_DEV_ID_PTP) पूर्ण,
	अणु 0, पूर्ण /* End of table. */
पूर्ण;
MODULE_DEVICE_TABLE(pci, enetc_ptp_id_table);

अटल काष्ठा pci_driver enetc_ptp_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = enetc_ptp_id_table,
	.probe = enetc_ptp_probe,
	.हटाओ = enetc_ptp_हटाओ,
पूर्ण;
module_pci_driver(enetc_ptp_driver);

MODULE_DESCRIPTION("ENETC PTP clock driver");
MODULE_LICENSE("Dual BSD/GPL");
