<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2016 Felix Fietkau <nbd@nbd.name>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश "mt76x2.h"

अटल स्थिर काष्ठा pci_device_id mt76x2e_device_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_MEDIATEK, 0x7662) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_MEDIATEK, 0x7612) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_MEDIATEK, 0x7602) पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक
mt76x2e_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	अटल स्थिर काष्ठा mt76_driver_ops drv_ops = अणु
		.txwi_size = माप(काष्ठा mt76x02_txwi),
		.drv_flags = MT_DRV_TX_ALIGNED4_SKBS |
			     MT_DRV_SW_RX_AIRTIME,
		.survey_flags = SURVEY_INFO_TIME_TX,
		.update_survey = mt76x02_update_channel,
		.tx_prepare_skb = mt76x02_tx_prepare_skb,
		.tx_complete_skb = mt76x02_tx_complete_skb,
		.rx_skb = mt76x02_queue_rx_skb,
		.rx_poll_complete = mt76x02_rx_poll_complete,
		.sta_ps = mt76x02_sta_ps,
		.sta_add = mt76x02_sta_add,
		.sta_हटाओ = mt76x02_sta_हटाओ,
	पूर्ण;
	काष्ठा mt76x02_dev *dev;
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

	mdev = mt76_alloc_device(&pdev->dev, माप(*dev), &mt76x2_ops,
				 &drv_ops);
	अगर (!mdev)
		वापस -ENOMEM;

	dev = container_of(mdev, काष्ठा mt76x02_dev, mt76);
	mt76_mmio_init(mdev, pcim_iomap_table(pdev)[0]);
	mt76x2_reset_wlan(dev, false);

	mdev->rev = mt76_rr(dev, MT_ASIC_VERSION);
	dev_info(mdev->dev, "ASIC revision: %08x\n", mdev->rev);

	mt76_wr(dev, MT_INT_MASK_CSR, 0);

	ret = devm_request_irq(mdev->dev, pdev->irq, mt76x02_irq_handler,
			       IRQF_SHARED, KBUILD_MODNAME, dev);
	अगर (ret)
		जाओ error;

	ret = mt76x2_रेजिस्टर_device(dev);
	अगर (ret)
		जाओ error;

	/* Fix up ASPM configuration */

	/* RG_SSUSB_G1_CDR_BIR_LTR = 0x9 */
	mt76_rmw_field(dev, 0x15a10, 0x1f << 16, 0x9);

	/* RG_SSUSB_G1_CDR_BIC_LTR = 0xf */
	mt76_rmw_field(dev, 0x15a0c, 0xf << 28, 0xf);

	/* RG_SSUSB_CDR_BR_PE1D = 0x3 */
	mt76_rmw_field(dev, 0x15c58, 0x3 << 6, 0x3);

	mt76_pci_disable_aspm(pdev);

	वापस 0;

error:
	mt76_मुक्त_device(&dev->mt76);

	वापस ret;
पूर्ण

अटल व्योम
mt76x2e_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mt76_dev *mdev = pci_get_drvdata(pdev);
	काष्ठा mt76x02_dev *dev = container_of(mdev, काष्ठा mt76x02_dev, mt76);

	mt76_unरेजिस्टर_device(mdev);
	mt76x2_cleanup(dev);
	mt76_मुक्त_device(mdev);
पूर्ण

अटल पूर्णांक __maybe_unused
mt76x2e_suspend(काष्ठा pci_dev *pdev, pm_message_t state)
अणु
	काष्ठा mt76_dev *mdev = pci_get_drvdata(pdev);
	पूर्णांक i, err;

	napi_disable(&mdev->tx_napi);
	tasklet_समाप्त(&mdev->pre_tbtt_tasklet);
	mt76_worker_disable(&mdev->tx_worker);

	mt76_क्रम_each_q_rx(mdev, i)
		napi_disable(&mdev->napi[i]);

	pci_enable_wake(pdev, pci_choose_state(pdev, state), true);
	pci_save_state(pdev);
	err = pci_set_घातer_state(pdev, pci_choose_state(pdev, state));
	अगर (err)
		जाओ restore;

	वापस 0;

restore:
	mt76_क्रम_each_q_rx(mdev, i)
		napi_enable(&mdev->napi[i]);
	napi_enable(&mdev->tx_napi);

	वापस err;
पूर्ण

अटल पूर्णांक __maybe_unused
mt76x2e_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mt76_dev *mdev = pci_get_drvdata(pdev);
	काष्ठा mt76x02_dev *dev = container_of(mdev, काष्ठा mt76x02_dev, mt76);
	पूर्णांक i, err;

	err = pci_set_घातer_state(pdev, PCI_D0);
	अगर (err)
		वापस err;

	pci_restore_state(pdev);

	mt76_worker_enable(&mdev->tx_worker);
	mt76_क्रम_each_q_rx(mdev, i) अणु
		napi_enable(&mdev->napi[i]);
		napi_schedule(&mdev->napi[i]);
	पूर्ण
	napi_enable(&mdev->tx_napi);
	napi_schedule(&mdev->tx_napi);

	वापस mt76x2_resume_device(dev);
पूर्ण

MODULE_DEVICE_TABLE(pci, mt76x2e_device_table);
MODULE_FIRMWARE(MT7662_FIRMWARE);
MODULE_FIRMWARE(MT7662_ROM_PATCH);
MODULE_LICENSE("Dual BSD/GPL");

अटल काष्ठा pci_driver mt76pci_driver = अणु
	.name		= KBUILD_MODNAME,
	.id_table	= mt76x2e_device_table,
	.probe		= mt76x2e_probe,
	.हटाओ		= mt76x2e_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= mt76x2e_suspend,
	.resume		= mt76x2e_resume,
#पूर्ण_अगर /* CONFIG_PM */
पूर्ण;

module_pci_driver(mt76pci_driver);
