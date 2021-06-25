<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PCI driver क्रम the High Speed UART DMA
 *
 * Copyright (C) 2015 Intel Corporation
 * Author: Andy Shevchenko <andriy.shevchenko@linux.पूर्णांकel.com>
 *
 * Partially based on the bits found in drivers/tty/serial/mfd.c.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश "hsu.h"

#घोषणा HSU_PCI_DMASR		0x00
#घोषणा HSU_PCI_DMAISR		0x04

#घोषणा HSU_PCI_CHAN_OFFSET	0x100

#घोषणा PCI_DEVICE_ID_INTEL_MFLD_HSU_DMA	0x081e
#घोषणा PCI_DEVICE_ID_INTEL_MRFLD_HSU_DMA	0x1192

अटल irqवापस_t hsu_pci_irq(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा hsu_dma_chip *chip = dev;
	u32 dmaisr;
	u32 status;
	अचिन्हित लघु i;
	पूर्णांक ret = 0;
	पूर्णांक err;

	dmaisr = पढ़ोl(chip->regs + HSU_PCI_DMAISR);
	क्रम (i = 0; i < chip->hsu->nr_channels; i++) अणु
		अगर (dmaisr & 0x1) अणु
			err = hsu_dma_get_status(chip, i, &status);
			अगर (err > 0)
				ret |= 1;
			अन्यथा अगर (err == 0)
				ret |= hsu_dma_करो_irq(chip, i, status);
		पूर्ण
		dmaisr >>= 1;
	पूर्ण

	वापस IRQ_RETVAL(ret);
पूर्ण

अटल पूर्णांक hsu_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा hsu_dma_chip *chip;
	पूर्णांक ret;

	ret = pcim_enable_device(pdev);
	अगर (ret)
		वापस ret;

	ret = pcim_iomap_regions(pdev, BIT(0), pci_name(pdev));
	अगर (ret) अणु
		dev_err(&pdev->dev, "I/O memory remapping failed\n");
		वापस ret;
	पूर्ण

	pci_set_master(pdev);
	pci_try_set_mwi(pdev);

	ret = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
	अगर (ret)
		वापस ret;

	ret = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32));
	अगर (ret)
		वापस ret;

	chip = devm_kzalloc(&pdev->dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	ret = pci_alloc_irq_vectors(pdev, 1, 1, PCI_IRQ_ALL_TYPES);
	अगर (ret < 0)
		वापस ret;

	chip->dev = &pdev->dev;
	chip->regs = pcim_iomap_table(pdev)[0];
	chip->length = pci_resource_len(pdev, 0);
	chip->offset = HSU_PCI_CHAN_OFFSET;
	chip->irq = pci_irq_vector(pdev, 0);

	ret = hsu_dma_probe(chip);
	अगर (ret)
		वापस ret;

	ret = request_irq(chip->irq, hsu_pci_irq, 0, "hsu_dma_pci", chip);
	अगर (ret)
		जाओ err_रेजिस्टर_irq;

	/*
	 * On Intel Tangier B0 and Anniedale the पूर्णांकerrupt line, disregarding
	 * to have dअगरferent numbers, is shared between HSU DMA and UART IPs.
	 * Thus on such SoCs we are expecting that IRQ handler is called in
	 * UART driver only. Instead of handling the spurious पूर्णांकerrupt
	 * from HSU DMA here and waste CPU समय and delay HSU UART पूर्णांकerrupt
	 * handling, disable the पूर्णांकerrupt entirely.
	 */
	अगर (pdev->device == PCI_DEVICE_ID_INTEL_MRFLD_HSU_DMA)
		disable_irq_nosync(chip->irq);

	pci_set_drvdata(pdev, chip);

	वापस 0;

err_रेजिस्टर_irq:
	hsu_dma_हटाओ(chip);
	वापस ret;
पूर्ण

अटल व्योम hsu_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा hsu_dma_chip *chip = pci_get_drvdata(pdev);

	मुक्त_irq(chip->irq, chip);
	hsu_dma_हटाओ(chip);
पूर्ण

अटल स्थिर काष्ठा pci_device_id hsu_pci_id_table[] = अणु
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_MFLD_HSU_DMA), 0 पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_MRFLD_HSU_DMA), 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, hsu_pci_id_table);

अटल काष्ठा pci_driver hsu_pci_driver = अणु
	.name		= "hsu_dma_pci",
	.id_table	= hsu_pci_id_table,
	.probe		= hsu_pci_probe,
	.हटाओ		= hsu_pci_हटाओ,
पूर्ण;

module_pci_driver(hsu_pci_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("High Speed UART DMA PCI driver");
MODULE_AUTHOR("Andy Shevchenko <andriy.shevchenko@linux.intel.com>");
