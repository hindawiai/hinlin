<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2020 MediaTek Inc.
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश "mt7921.h"
#समावेश "mac.h"
#समावेश "mcu.h"
#समावेश "../trace.h"

अटल स्थिर काष्ठा pci_device_id mt7921_pci_device_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_MEDIATEK, 0x7961) पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल व्योम
mt7921_rx_poll_complete(काष्ठा mt76_dev *mdev, क्रमागत mt76_rxq_id q)
अणु
	काष्ठा mt7921_dev *dev = container_of(mdev, काष्ठा mt7921_dev, mt76);

	अगर (q == MT_RXQ_MAIN)
		mt7921_irq_enable(dev, MT_INT_RX_DONE_DATA);
	अन्यथा अगर (q == MT_RXQ_MCU_WA)
		mt7921_irq_enable(dev, MT_INT_RX_DONE_WM2);
	अन्यथा
		mt7921_irq_enable(dev, MT_INT_RX_DONE_WM);
पूर्ण

अटल irqवापस_t mt7921_irq_handler(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा mt7921_dev *dev = dev_instance;

	mt76_wr(dev, MT_WFDMA0_HOST_INT_ENA, 0);

	अगर (!test_bit(MT76_STATE_INITIALIZED, &dev->mphy.state))
		वापस IRQ_NONE;

	tasklet_schedule(&dev->irq_tasklet);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम mt7921_irq_tasklet(अचिन्हित दीर्घ data)
अणु
	काष्ठा mt7921_dev *dev = (काष्ठा mt7921_dev *)data;
	u32 पूर्णांकr, mask = 0;

	mt76_wr(dev, MT_WFDMA0_HOST_INT_ENA, 0);

	पूर्णांकr = mt76_rr(dev, MT_WFDMA0_HOST_INT_STA);
	पूर्णांकr &= dev->mt76.mmio.irqmask;
	mt76_wr(dev, MT_WFDMA0_HOST_INT_STA, पूर्णांकr);

	trace_dev_irq(&dev->mt76, पूर्णांकr, dev->mt76.mmio.irqmask);

	mask |= पूर्णांकr & MT_INT_RX_DONE_ALL;
	अगर (पूर्णांकr & MT_INT_TX_DONE_MCU)
		mask |= MT_INT_TX_DONE_MCU;

	अगर (पूर्णांकr & MT_INT_MCU_CMD) अणु
		u32 पूर्णांकr_sw;

		पूर्णांकr_sw = mt76_rr(dev, MT_MCU_CMD);
		/* ack MCU2HOST_SW_INT_STA */
		mt76_wr(dev, MT_MCU_CMD, पूर्णांकr_sw);
		अगर (पूर्णांकr_sw & MT_MCU_CMD_WAKE_RX_PCIE) अणु
			mask |= MT_INT_RX_DONE_DATA;
			पूर्णांकr |= MT_INT_RX_DONE_DATA;
		पूर्ण
	पूर्ण

	mt76_set_irq_mask(&dev->mt76, MT_WFDMA0_HOST_INT_ENA, mask, 0);

	अगर (पूर्णांकr & MT_INT_TX_DONE_ALL)
		napi_schedule(&dev->mt76.tx_napi);

	अगर (पूर्णांकr & MT_INT_RX_DONE_WM)
		napi_schedule(&dev->mt76.napi[MT_RXQ_MCU]);

	अगर (पूर्णांकr & MT_INT_RX_DONE_WM2)
		napi_schedule(&dev->mt76.napi[MT_RXQ_MCU_WA]);

	अगर (पूर्णांकr & MT_INT_RX_DONE_DATA)
		napi_schedule(&dev->mt76.napi[MT_RXQ_MAIN]);
पूर्ण

अटल पूर्णांक mt7921_pci_probe(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *id)
अणु
	अटल स्थिर काष्ठा mt76_driver_ops drv_ops = अणु
		/* txwi_size = txd size + txp size */
		.txwi_size = MT_TXD_SIZE + माप(काष्ठा mt7921_txp_common),
		.drv_flags = MT_DRV_TXWI_NO_FREE | MT_DRV_HW_MGMT_TXQ |
			     MT_DRV_AMSDU_OFFLOAD,
		.survey_flags = SURVEY_INFO_TIME_TX |
				SURVEY_INFO_TIME_RX |
				SURVEY_INFO_TIME_BSS_RX,
		.token_size = MT7921_TOKEN_SIZE,
		.tx_prepare_skb = mt7921_tx_prepare_skb,
		.tx_complete_skb = mt7921_tx_complete_skb,
		.rx_skb = mt7921_queue_rx_skb,
		.rx_poll_complete = mt7921_rx_poll_complete,
		.sta_ps = mt7921_sta_ps,
		.sta_add = mt7921_mac_sta_add,
		.sta_हटाओ = mt7921_mac_sta_हटाओ,
		.update_survey = mt7921_update_channel,
	पूर्ण;
	काष्ठा mt7921_dev *dev;
	काष्ठा mt76_dev *mdev;
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
		जाओ err_मुक्त_pci_vec;

	mt76_pci_disable_aspm(pdev);

	mdev = mt76_alloc_device(&pdev->dev, माप(*dev), &mt7921_ops,
				 &drv_ops);
	अगर (!mdev) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_pci_vec;
	पूर्ण

	dev = container_of(mdev, काष्ठा mt7921_dev, mt76);

	mt76_mmio_init(&dev->mt76, pcim_iomap_table(pdev)[0]);
	tasklet_init(&dev->irq_tasklet, mt7921_irq_tasklet, (अचिन्हित दीर्घ)dev);
	mdev->rev = (mt7921_l1_rr(dev, MT_HW_CHIPID) << 16) |
		    (mt7921_l1_rr(dev, MT_HW_REV) & 0xff);
	dev_err(mdev->dev, "ASIC revision: %04x\n", mdev->rev);

	mt76_wr(dev, MT_WFDMA0_HOST_INT_ENA, 0);

	mt76_wr(dev, MT_PCIE_MAC_INT_ENABLE, 0xff);

	ret = devm_request_irq(mdev->dev, pdev->irq, mt7921_irq_handler,
			       IRQF_SHARED, KBUILD_MODNAME, dev);
	अगर (ret)
		जाओ err_मुक्त_dev;

	ret = mt7921_रेजिस्टर_device(dev);
	अगर (ret)
		जाओ err_मुक्त_irq;

	वापस 0;

err_मुक्त_irq:
	devm_मुक्त_irq(&pdev->dev, pdev->irq, dev);
err_मुक्त_dev:
	mt76_मुक्त_device(&dev->mt76);
err_मुक्त_pci_vec:
	pci_मुक्त_irq_vectors(pdev);

	वापस ret;
पूर्ण

अटल व्योम mt7921_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mt76_dev *mdev = pci_get_drvdata(pdev);
	काष्ठा mt7921_dev *dev = container_of(mdev, काष्ठा mt7921_dev, mt76);

	mt7921_unरेजिस्टर_device(dev);
	devm_मुक्त_irq(&pdev->dev, pdev->irq, dev);
	pci_मुक्त_irq_vectors(pdev);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक mt7921_pci_suspend(काष्ठा pci_dev *pdev, pm_message_t state)
अणु
	काष्ठा mt76_dev *mdev = pci_get_drvdata(pdev);
	काष्ठा mt7921_dev *dev = container_of(mdev, काष्ठा mt7921_dev, mt76);
	bool hअगर_suspend;
	पूर्णांक i, err;

	err = mt76_connac_pm_wake(&dev->mphy, &dev->pm);
	अगर (err < 0)
		वापस err;

	hअगर_suspend = !test_bit(MT76_STATE_SUSPEND, &dev->mphy.state);
	अगर (hअगर_suspend) अणु
		err = mt76_connac_mcu_set_hअगर_suspend(mdev, true);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (!dev->pm.enable)
		mt76_connac_mcu_set_deep_sleep(&dev->mt76, true);

	napi_disable(&mdev->tx_napi);
	mt76_worker_disable(&mdev->tx_worker);

	mt76_क्रम_each_q_rx(mdev, i) अणु
		napi_disable(&mdev->napi[i]);
	पूर्ण

	pci_enable_wake(pdev, pci_choose_state(pdev, state), true);

	/* रुको until dma is idle  */
	mt76_poll(dev, MT_WFDMA0_GLO_CFG,
		  MT_WFDMA0_GLO_CFG_TX_DMA_BUSY |
		  MT_WFDMA0_GLO_CFG_RX_DMA_BUSY, 0, 1000);

	/* put dma disabled */
	mt76_clear(dev, MT_WFDMA0_GLO_CFG,
		   MT_WFDMA0_GLO_CFG_TX_DMA_EN | MT_WFDMA0_GLO_CFG_RX_DMA_EN);

	/* disable पूर्णांकerrupt */
	mt76_wr(dev, MT_WFDMA0_HOST_INT_ENA, 0);
	mt76_wr(dev, MT_PCIE_MAC_INT_ENABLE, 0x0);
	synchronize_irq(pdev->irq);
	tasklet_समाप्त(&dev->irq_tasklet);

	err = mt7921_mcu_fw_pmctrl(dev);
	अगर (err)
		जाओ restore;

	pci_save_state(pdev);
	err = pci_set_घातer_state(pdev, pci_choose_state(pdev, state));
	अगर (err)
		जाओ restore;

	वापस 0;

restore:
	mt76_क्रम_each_q_rx(mdev, i) अणु
		napi_enable(&mdev->napi[i]);
	पूर्ण
	napi_enable(&mdev->tx_napi);

	अगर (!dev->pm.enable)
		mt76_connac_mcu_set_deep_sleep(&dev->mt76, false);

	अगर (hअगर_suspend)
		mt76_connac_mcu_set_hअगर_suspend(mdev, false);

	वापस err;
पूर्ण

अटल पूर्णांक mt7921_pci_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mt76_dev *mdev = pci_get_drvdata(pdev);
	काष्ठा mt7921_dev *dev = container_of(mdev, काष्ठा mt7921_dev, mt76);
	पूर्णांक i, err;

	err = pci_set_घातer_state(pdev, PCI_D0);
	अगर (err)
		वापस err;

	pci_restore_state(pdev);

	err = mt7921_mcu_drv_pmctrl(dev);
	अगर (err < 0)
		वापस err;

	mt7921_wpdma_reinit_cond(dev);

	/* enable पूर्णांकerrupt */
	mt76_wr(dev, MT_PCIE_MAC_INT_ENABLE, 0xff);
	mt7921_irq_enable(dev, MT_INT_RX_DONE_ALL | MT_INT_TX_DONE_ALL |
			  MT_INT_MCU_CMD);
	mt76_set(dev, MT_MCU2HOST_SW_INT_ENA, MT_MCU_CMD_WAKE_RX_PCIE);

	/* put dma enabled */
	mt76_set(dev, MT_WFDMA0_GLO_CFG,
		 MT_WFDMA0_GLO_CFG_TX_DMA_EN | MT_WFDMA0_GLO_CFG_RX_DMA_EN);

	mt76_worker_enable(&mdev->tx_worker);
	mt76_क्रम_each_q_rx(mdev, i) अणु
		napi_enable(&mdev->napi[i]);
		napi_schedule(&mdev->napi[i]);
	पूर्ण
	napi_enable(&mdev->tx_napi);
	napi_schedule(&mdev->tx_napi);

	अगर (!dev->pm.enable)
		mt76_connac_mcu_set_deep_sleep(&dev->mt76, false);

	अगर (!test_bit(MT76_STATE_SUSPEND, &dev->mphy.state))
		err = mt76_connac_mcu_set_hअगर_suspend(mdev, false);

	वापस err;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

काष्ठा pci_driver mt7921_pci_driver = अणु
	.name		= KBUILD_MODNAME,
	.id_table	= mt7921_pci_device_table,
	.probe		= mt7921_pci_probe,
	.हटाओ		= mt7921_pci_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= mt7921_pci_suspend,
	.resume		= mt7921_pci_resume,
#पूर्ण_अगर /* CONFIG_PM */
पूर्ण;

module_pci_driver(mt7921_pci_driver);

MODULE_DEVICE_TABLE(pci, mt7921_pci_device_table);
MODULE_FIRMWARE(MT7921_FIRMWARE_WM);
MODULE_FIRMWARE(MT7921_ROM_PATCH);
MODULE_AUTHOR("Sean Wang <sean.wang@mediatek.com>");
MODULE_AUTHOR("Lorenzo Bianconi <lorenzo@kernel.org>");
MODULE_LICENSE("Dual BSD/GPL");
