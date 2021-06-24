<शैली गुरु>
// SPDX-License-Identअगरier: ISC

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश "mt7603.h"

अटल स्थिर काष्ठा pci_device_id mt76pci_device_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_MEDIATEK, 0x7603) पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक
mt76pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा mt7603_dev *dev;
	काष्ठा mt76_dev *mdev;
	पूर्णांक ret;

	ret = pcim_enable_device(pdev);
	अगर (ret)
		वापस ret;

	ret = pcim_iomap_regions(pdev, BIT(0), pci_name(pdev));
	अगर (ret)
		वापस ret;

	pci_set_master(pdev);

	ret = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
	अगर (ret)
		वापस ret;

	mdev = mt76_alloc_device(&pdev->dev, माप(*dev), &mt7603_ops,
				 &mt7603_drv_ops);
	अगर (!mdev)
		वापस -ENOMEM;

	dev = container_of(mdev, काष्ठा mt7603_dev, mt76);
	mt76_mmio_init(mdev, pcim_iomap_table(pdev)[0]);

	mdev->rev = (mt76_rr(dev, MT_HW_CHIPID) << 16) |
		    (mt76_rr(dev, MT_HW_REV) & 0xff);
	dev_info(mdev->dev, "ASIC revision: %04x\n", mdev->rev);

	mt76_wr(dev, MT_INT_MASK_CSR, 0);

	ret = devm_request_irq(mdev->dev, pdev->irq, mt7603_irq_handler,
			       IRQF_SHARED, KBUILD_MODNAME, dev);
	अगर (ret)
		जाओ error;

	ret = mt7603_रेजिस्टर_device(dev);
	अगर (ret)
		जाओ error;

	वापस 0;
error:
	mt76_मुक्त_device(&dev->mt76);

	वापस ret;
पूर्ण

अटल व्योम
mt76pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mt76_dev *mdev = pci_get_drvdata(pdev);
	काष्ठा mt7603_dev *dev = container_of(mdev, काष्ठा mt7603_dev, mt76);

	mt7603_unरेजिस्टर_device(dev);
पूर्ण

MODULE_DEVICE_TABLE(pci, mt76pci_device_table);
MODULE_FIRMWARE(MT7603_FIRMWARE_E1);
MODULE_FIRMWARE(MT7603_FIRMWARE_E2);

काष्ठा pci_driver mt7603_pci_driver = अणु
	.name		= KBUILD_MODNAME,
	.id_table	= mt76pci_device_table,
	.probe		= mt76pci_probe,
	.हटाओ		= mt76pci_हटाओ,
पूर्ण;
