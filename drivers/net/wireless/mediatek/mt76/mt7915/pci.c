<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2020 MediaTek Inc.
 *
 * Author: Ryder Lee <ryder.lee@mediatek.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश "mt7915.h"
#समावेश "mac.h"
#समावेश "../trace.h"

अटल LIST_HEAD(hअगर_list);
अटल DEFINE_SPINLOCK(hअगर_lock);
अटल u32 hअगर_idx;

अटल स्थिर काष्ठा pci_device_id mt7915_pci_device_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_MEDIATEK, 0x7915) पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id mt7915_hअगर_device_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_MEDIATEK, 0x7916) पूर्ण,
	अणु पूर्ण,
पूर्ण;

व्योम mt7915_dual_hअगर_set_irq_mask(काष्ठा mt7915_dev *dev, bool ग_लिखो_reg,
				  u32 clear, u32 set)
अणु
	काष्ठा mt76_dev *mdev = &dev->mt76;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mdev->mmio.irq_lock, flags);

	mdev->mmio.irqmask &= ~clear;
	mdev->mmio.irqmask |= set;

	अगर (ग_लिखो_reg) अणु
		mt76_wr(dev, MT_INT_MASK_CSR, mdev->mmio.irqmask);
		mt76_wr(dev, MT_INT1_MASK_CSR, mdev->mmio.irqmask);
	पूर्ण

	spin_unlock_irqrestore(&mdev->mmio.irq_lock, flags);
पूर्ण

अटल काष्ठा mt7915_hअगर *
mt7915_pci_get_hअगर2(काष्ठा mt7915_dev *dev)
अणु
	काष्ठा mt7915_hअगर *hअगर;
	u32 val;

	spin_lock_bh(&hअगर_lock);

	list_क्रम_each_entry(hअगर, &hअगर_list, list) अणु
		val = पढ़ोl(hअगर->regs + MT_PCIE_RECOG_ID);
		val &= MT_PCIE_RECOG_ID_MASK;
		अगर (val != dev->hअगर_idx)
			जारी;

		get_device(hअगर->dev);
		जाओ out;
	पूर्ण
	hअगर = शून्य;

out:
	spin_unlock_bh(&hअगर_lock);

	वापस hअगर;
पूर्ण

अटल व्योम mt7915_put_hअगर2(काष्ठा mt7915_hअगर *hअगर)
अणु
	अगर (!hअगर)
		वापस;

	put_device(hअगर->dev);
पूर्ण

अटल व्योम
mt7915_rx_poll_complete(काष्ठा mt76_dev *mdev, क्रमागत mt76_rxq_id q)
अणु
	काष्ठा mt7915_dev *dev = container_of(mdev, काष्ठा mt7915_dev, mt76);
	अटल स्थिर u32 rx_irq_mask[] = अणु
		[MT_RXQ_MAIN] = MT_INT_RX_DONE_DATA0,
		[MT_RXQ_EXT] = MT_INT_RX_DONE_DATA1,
		[MT_RXQ_MCU] = MT_INT_RX_DONE_WM,
		[MT_RXQ_MCU_WA] = MT_INT_RX_DONE_WA,
		[MT_RXQ_EXT_WA] = MT_INT_RX_DONE_WA_EXT,
	पूर्ण;

	mt7915_irq_enable(dev, rx_irq_mask[q]);
पूर्ण

/* TODO: support 2/4/6/8 MSI-X vectors */
अटल irqवापस_t mt7915_irq_handler(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा mt7915_dev *dev = dev_instance;
	u32 पूर्णांकr, पूर्णांकr1, mask;

	पूर्णांकr = mt76_rr(dev, MT_INT_SOURCE_CSR);
	पूर्णांकr &= dev->mt76.mmio.irqmask;
	mt76_wr(dev, MT_INT_SOURCE_CSR, पूर्णांकr);

	अगर (dev->hअगर2) अणु
		पूर्णांकr1 = mt76_rr(dev, MT_INT1_SOURCE_CSR);
		पूर्णांकr1 &= dev->mt76.mmio.irqmask;
		mt76_wr(dev, MT_INT1_SOURCE_CSR, पूर्णांकr1);

		पूर्णांकr |= पूर्णांकr1;
	पूर्ण

	अगर (!test_bit(MT76_STATE_INITIALIZED, &dev->mphy.state))
		वापस IRQ_NONE;

	trace_dev_irq(&dev->mt76, पूर्णांकr, dev->mt76.mmio.irqmask);

	mask = पूर्णांकr & MT_INT_RX_DONE_ALL;
	अगर (पूर्णांकr & MT_INT_TX_DONE_MCU)
		mask |= MT_INT_TX_DONE_MCU;

	mt7915_irq_disable(dev, mask);

	अगर (पूर्णांकr & MT_INT_TX_DONE_MCU)
		napi_schedule(&dev->mt76.tx_napi);

	अगर (पूर्णांकr & MT_INT_RX_DONE_DATA0)
		napi_schedule(&dev->mt76.napi[MT_RXQ_MAIN]);

	अगर (पूर्णांकr & MT_INT_RX_DONE_DATA1)
		napi_schedule(&dev->mt76.napi[MT_RXQ_EXT]);

	अगर (पूर्णांकr & MT_INT_RX_DONE_WM)
		napi_schedule(&dev->mt76.napi[MT_RXQ_MCU]);

	अगर (पूर्णांकr & MT_INT_RX_DONE_WA)
		napi_schedule(&dev->mt76.napi[MT_RXQ_MCU_WA]);

	अगर (पूर्णांकr & MT_INT_RX_DONE_WA_EXT)
		napi_schedule(&dev->mt76.napi[MT_RXQ_EXT_WA]);

	अगर (पूर्णांकr & MT_INT_MCU_CMD) अणु
		u32 val = mt76_rr(dev, MT_MCU_CMD);

		mt76_wr(dev, MT_MCU_CMD, val);
		अगर (val & MT_MCU_CMD_ERROR_MASK) अणु
			dev->reset_state = val;
			ieee80211_queue_work(mt76_hw(dev), &dev->reset_work);
			wake_up(&dev->reset_रुको);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम mt7915_pci_init_hअगर2(काष्ठा mt7915_dev *dev)
अणु
	काष्ठा mt7915_hअगर *hअगर;

	dev->hअगर_idx = ++hअगर_idx;
	अगर (!pci_get_device(PCI_VENDOR_ID_MEDIATEK, 0x7916, शून्य))
		वापस;

	mt76_wr(dev, MT_PCIE_RECOG_ID, dev->hअगर_idx | MT_PCIE_RECOG_ID_SEM);

	hअगर = mt7915_pci_get_hअगर2(dev);
	अगर (!hअगर)
		वापस;

	dev->hअगर2 = hअगर;

	mt76_wr(dev, MT_INT1_MASK_CSR, 0);

	अगर (devm_request_irq(dev->mt76.dev, hअगर->irq, mt7915_irq_handler,
			     IRQF_SHARED, KBUILD_MODNAME "-hif", dev)) अणु
		mt7915_put_hअगर2(hअगर);
		hअगर = शून्य;
	पूर्ण

	/* master चयन of PCIe tnterrupt enable */
	mt76_wr(dev, MT_PCIE1_MAC_INT_ENABLE, 0xff);
पूर्ण

अटल पूर्णांक mt7915_pci_hअगर2_probe(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mt7915_hअगर *hअगर;

	hअगर = devm_kzalloc(&pdev->dev, माप(*hअगर), GFP_KERNEL);
	अगर (!hअगर)
		वापस -ENOMEM;

	hअगर->dev = &pdev->dev;
	hअगर->regs = pcim_iomap_table(pdev)[0];
	hअगर->irq = pdev->irq;
	spin_lock_bh(&hअगर_lock);
	list_add(&hअगर->list, &hअगर_list);
	spin_unlock_bh(&hअगर_lock);
	pci_set_drvdata(pdev, hअगर);

	वापस 0;
पूर्ण

अटल पूर्णांक mt7915_pci_probe(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *id)
अणु
	अटल स्थिर काष्ठा mt76_driver_ops drv_ops = अणु
		/* txwi_size = txd size + txp size */
		.txwi_size = MT_TXD_SIZE + माप(काष्ठा mt7915_txp),
		.drv_flags = MT_DRV_TXWI_NO_FREE | MT_DRV_HW_MGMT_TXQ |
			     MT_DRV_AMSDU_OFFLOAD,
		.survey_flags = SURVEY_INFO_TIME_TX |
				SURVEY_INFO_TIME_RX |
				SURVEY_INFO_TIME_BSS_RX,
		.token_size = MT7915_TOKEN_SIZE,
		.tx_prepare_skb = mt7915_tx_prepare_skb,
		.tx_complete_skb = mt7915_tx_complete_skb,
		.rx_skb = mt7915_queue_rx_skb,
		.rx_poll_complete = mt7915_rx_poll_complete,
		.sta_ps = mt7915_sta_ps,
		.sta_add = mt7915_mac_sta_add,
		.sta_हटाओ = mt7915_mac_sta_हटाओ,
		.update_survey = mt7915_update_channel,
	पूर्ण;
	काष्ठा mt7915_dev *dev;
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

	अगर (id->device == 0x7916)
		वापस mt7915_pci_hअगर2_probe(pdev);

	mdev = mt76_alloc_device(&pdev->dev, माप(*dev), &mt7915_ops,
				 &drv_ops);
	अगर (!mdev)
		वापस -ENOMEM;

	dev = container_of(mdev, काष्ठा mt7915_dev, mt76);

	ret = mt7915_mmio_init(mdev, pcim_iomap_table(pdev)[0], pdev->irq);
	अगर (ret)
		जाओ error;

	/* master चयन of PCIe tnterrupt enable */
	mt76_wr(dev, MT_PCIE_MAC_INT_ENABLE, 0xff);

	ret = devm_request_irq(mdev->dev, pdev->irq, mt7915_irq_handler,
			       IRQF_SHARED, KBUILD_MODNAME, dev);
	अगर (ret)
		जाओ error;

	mt7915_pci_init_hअगर2(dev);

	ret = mt7915_रेजिस्टर_device(dev);
	अगर (ret)
		जाओ error;

	वापस 0;
error:
	mt76_मुक्त_device(&dev->mt76);

	वापस ret;
पूर्ण

अटल व्योम mt7915_hअगर_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mt7915_hअगर *hअगर = pci_get_drvdata(pdev);

	list_del(&hअगर->list);
पूर्ण

अटल व्योम mt7915_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mt76_dev *mdev;
	काष्ठा mt7915_dev *dev;

	mdev = pci_get_drvdata(pdev);
	dev = container_of(mdev, काष्ठा mt7915_dev, mt76);
	mt7915_put_hअगर2(dev->hअगर2);
	mt7915_unरेजिस्टर_device(dev);
पूर्ण

अटल काष्ठा pci_driver mt7915_hअगर_driver = अणु
	.name		= KBUILD_MODNAME "_hif",
	.id_table	= mt7915_hअगर_device_table,
	.probe		= mt7915_pci_probe,
	.हटाओ		= mt7915_hअगर_हटाओ,
पूर्ण;

अटल काष्ठा pci_driver mt7915_pci_driver = अणु
	.name		= KBUILD_MODNAME,
	.id_table	= mt7915_pci_device_table,
	.probe		= mt7915_pci_probe,
	.हटाओ		= mt7915_pci_हटाओ,
पूर्ण;

अटल पूर्णांक __init mt7915_init(व्योम)
अणु
	पूर्णांक ret;

	ret = pci_रेजिस्टर_driver(&mt7915_hअगर_driver);
	अगर (ret)
		वापस ret;

	ret = pci_रेजिस्टर_driver(&mt7915_pci_driver);
	अगर (ret)
		pci_unरेजिस्टर_driver(&mt7915_hअगर_driver);

	वापस ret;
पूर्ण

अटल व्योम __निकास mt7915_निकास(व्योम)
अणु
    pci_unरेजिस्टर_driver(&mt7915_pci_driver);
    pci_unरेजिस्टर_driver(&mt7915_hअगर_driver);
पूर्ण

module_init(mt7915_init);
module_निकास(mt7915_निकास);

MODULE_DEVICE_TABLE(pci, mt7915_pci_device_table);
MODULE_DEVICE_TABLE(pci, mt7915_hअगर_device_table);
MODULE_FIRMWARE(MT7915_FIRMWARE_WA);
MODULE_FIRMWARE(MT7915_FIRMWARE_WM);
MODULE_FIRMWARE(MT7915_ROM_PATCH);
MODULE_LICENSE("Dual BSD/GPL");
