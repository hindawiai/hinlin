<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2019 MediaTek Inc.
 *
 * Author: Ryder Lee <ryder.lee@mediatek.com>
 *         Felix Fietkau <nbd@nbd.name>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश "mt7615.h"
#समावेश "mcu.h"

अटल स्थिर काष्ठा pci_device_id mt7615_pci_device_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_MEDIATEK, 0x7615) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_MEDIATEK, 0x7663) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_MEDIATEK, 0x7611) पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक mt7615_pci_probe(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *id)
अणु
	स्थिर u32 *map;
	पूर्णांक ret;

	ret = pcim_enable_device(pdev);
	अगर (ret)
		वापस ret;

	ret = pcim_iomap_regions(pdev, BIT(0), pci_name(pdev));
	अगर (ret)
		वापस ret;

	pci_set_master(pdev);

	ret = pci_alloc_irq_vectors(pdev, 1, 1, PCI_IRQ_ALL_TYPES);
	अगर (ret < 0)
		वापस ret;

	ret = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
	अगर (ret)
		जाओ error;

	mt76_pci_disable_aspm(pdev);

	map = id->device == 0x7663 ? mt7663e_reg_map : mt7615e_reg_map;
	ret = mt7615_mmio_probe(&pdev->dev, pcim_iomap_table(pdev)[0],
				pdev->irq, map);
	अगर (ret)
		जाओ error;

	वापस 0;
error:
	pci_मुक्त_irq_vectors(pdev);

	वापस ret;
पूर्ण

अटल व्योम mt7615_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mt76_dev *mdev = pci_get_drvdata(pdev);
	काष्ठा mt7615_dev *dev = container_of(mdev, काष्ठा mt7615_dev, mt76);

	mt7615_unरेजिस्टर_device(dev);
	devm_मुक्त_irq(&pdev->dev, pdev->irq, dev);
	pci_मुक्त_irq_vectors(pdev);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक mt7615_pci_suspend(काष्ठा pci_dev *pdev, pm_message_t state)
अणु
	काष्ठा mt76_dev *mdev = pci_get_drvdata(pdev);
	काष्ठा mt7615_dev *dev = container_of(mdev, काष्ठा mt7615_dev, mt76);
	bool hअगर_suspend;
	पूर्णांक i, err;

	err = mt76_connac_pm_wake(&dev->mphy, &dev->pm);
	अगर (err < 0)
		वापस err;

	hअगर_suspend = !test_bit(MT76_STATE_SUSPEND, &dev->mphy.state) &&
		      mt7615_firmware_offload(dev);
	अगर (hअगर_suspend) अणु
		err = mt76_connac_mcu_set_hअगर_suspend(mdev, true);
		अगर (err)
			वापस err;
	पूर्ण

	napi_disable(&mdev->tx_napi);
	mt76_worker_disable(&mdev->tx_worker);

	mt76_क्रम_each_q_rx(mdev, i) अणु
		napi_disable(&mdev->napi[i]);
	पूर्ण
	tasklet_समाप्त(&dev->irq_tasklet);

	mt7615_dma_reset(dev);

	err = mt7615_रुको_pdma_busy(dev);
	अगर (err)
		जाओ restore;

	अगर (is_mt7663(mdev)) अणु
		mt76_set(dev, MT_PDMA_SLP_PROT, MT_PDMA_AXI_SLPPROT_ENABLE);
		अगर (!mt76_poll_msec(dev, MT_PDMA_SLP_PROT,
				    MT_PDMA_AXI_SLPPROT_RDY,
				    MT_PDMA_AXI_SLPPROT_RDY, 1000)) अणु
			dev_err(mdev->dev, "PDMA sleep protection failed\n");
			err = -EIO;
			जाओ restore;
		पूर्ण
	पूर्ण

	pci_enable_wake(pdev, pci_choose_state(pdev, state), true);
	pci_save_state(pdev);
	err = pci_set_घातer_state(pdev, pci_choose_state(pdev, state));
	अगर (err)
		जाओ restore;

	err = mt7615_mcu_set_fw_ctrl(dev);
	अगर (err)
		जाओ restore;

	वापस 0;

restore:
	mt76_क्रम_each_q_rx(mdev, i) अणु
		napi_enable(&mdev->napi[i]);
	पूर्ण
	napi_enable(&mdev->tx_napi);
	अगर (hअगर_suspend)
		mt76_connac_mcu_set_hअगर_suspend(mdev, false);

	वापस err;
पूर्ण

अटल पूर्णांक mt7615_pci_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mt76_dev *mdev = pci_get_drvdata(pdev);
	काष्ठा mt7615_dev *dev = container_of(mdev, काष्ठा mt7615_dev, mt76);
	bool pdma_reset;
	पूर्णांक i, err;

	err = mt7615_mcu_set_drv_ctrl(dev);
	अगर (err < 0)
		वापस err;

	err = pci_set_घातer_state(pdev, PCI_D0);
	अगर (err)
		वापस err;

	pci_restore_state(pdev);

	अगर (is_mt7663(&dev->mt76)) अणु
		mt76_clear(dev, MT_PDMA_SLP_PROT, MT_PDMA_AXI_SLPPROT_ENABLE);
		mt76_wr(dev, MT_PCIE_IRQ_ENABLE, 1);
	पूर्ण

	pdma_reset = !mt76_rr(dev, MT_WPDMA_TX_RING0_CTRL0) &&
		     !mt76_rr(dev, MT_WPDMA_TX_RING0_CTRL1);
	अगर (pdma_reset)
		dev_err(mdev->dev, "PDMA engine must be reinitialized\n");

	mt76_worker_enable(&mdev->tx_worker);
	mt76_क्रम_each_q_rx(mdev, i) अणु
		napi_enable(&mdev->napi[i]);
		napi_schedule(&mdev->napi[i]);
	पूर्ण
	napi_enable(&mdev->tx_napi);
	napi_schedule(&mdev->tx_napi);

	अगर (!test_bit(MT76_STATE_SUSPEND, &dev->mphy.state) &&
	    mt7615_firmware_offload(dev))
		err = mt76_connac_mcu_set_hअगर_suspend(mdev, false);

	वापस err;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

काष्ठा pci_driver mt7615_pci_driver = अणु
	.name		= KBUILD_MODNAME,
	.id_table	= mt7615_pci_device_table,
	.probe		= mt7615_pci_probe,
	.हटाओ		= mt7615_pci_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= mt7615_pci_suspend,
	.resume		= mt7615_pci_resume,
#पूर्ण_अगर /* CONFIG_PM */
पूर्ण;

MODULE_DEVICE_TABLE(pci, mt7615_pci_device_table);
MODULE_FIRMWARE(MT7615_FIRMWARE_CR4);
MODULE_FIRMWARE(MT7615_FIRMWARE_N9);
MODULE_FIRMWARE(MT7615_ROM_PATCH);
MODULE_FIRMWARE(MT7663_OFFLOAD_FIRMWARE_N9);
MODULE_FIRMWARE(MT7663_OFFLOAD_ROM_PATCH);
MODULE_FIRMWARE(MT7663_FIRMWARE_N9);
MODULE_FIRMWARE(MT7663_ROM_PATCH);
