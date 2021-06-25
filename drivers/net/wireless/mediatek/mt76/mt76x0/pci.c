<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2016 Felix Fietkau <nbd@nbd.name>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश "mt76x0.h"
#समावेश "mcu.h"

अटल पूर्णांक mt76x0e_start(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mt76x02_dev *dev = hw->priv;

	mt76x02_mac_start(dev);
	mt76x0_phy_calibrate(dev, true);
	ieee80211_queue_delayed_work(dev->mt76.hw, &dev->mphy.mac_work,
				     MT_MAC_WORK_INTERVAL);
	ieee80211_queue_delayed_work(dev->mt76.hw, &dev->cal_work,
				     MT_CALIBRATE_INTERVAL);
	set_bit(MT76_STATE_RUNNING, &dev->mphy.state);

	वापस 0;
पूर्ण

अटल व्योम mt76x0e_stop_hw(काष्ठा mt76x02_dev *dev)
अणु
	cancel_delayed_work_sync(&dev->cal_work);
	cancel_delayed_work_sync(&dev->mphy.mac_work);
	clear_bit(MT76_RESTART, &dev->mphy.state);

	अगर (!mt76_poll(dev, MT_WPDMA_GLO_CFG, MT_WPDMA_GLO_CFG_TX_DMA_BUSY,
		       0, 1000))
		dev_warn(dev->mt76.dev, "TX DMA did not stop\n");
	mt76_clear(dev, MT_WPDMA_GLO_CFG, MT_WPDMA_GLO_CFG_TX_DMA_EN);

	mt76x0_mac_stop(dev);

	अगर (!mt76_poll(dev, MT_WPDMA_GLO_CFG, MT_WPDMA_GLO_CFG_RX_DMA_BUSY,
		       0, 1000))
		dev_warn(dev->mt76.dev, "TX DMA did not stop\n");
	mt76_clear(dev, MT_WPDMA_GLO_CFG, MT_WPDMA_GLO_CFG_RX_DMA_EN);
पूर्ण

अटल व्योम mt76x0e_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mt76x02_dev *dev = hw->priv;

	clear_bit(MT76_STATE_RUNNING, &dev->mphy.state);
	mt76x0e_stop_hw(dev);
पूर्ण

अटल व्योम
mt76x0e_flush(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
	      u32 queues, bool drop)
अणु
पूर्ण

अटल स्थिर काष्ठा ieee80211_ops mt76x0e_ops = अणु
	.tx = mt76x02_tx,
	.start = mt76x0e_start,
	.stop = mt76x0e_stop,
	.add_पूर्णांकerface = mt76x02_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface = mt76x02_हटाओ_पूर्णांकerface,
	.config = mt76x0_config,
	.configure_filter = mt76x02_configure_filter,
	.bss_info_changed = mt76x02_bss_info_changed,
	.sta_state = mt76_sta_state,
	.sta_pre_rcu_हटाओ = mt76_sta_pre_rcu_हटाओ,
	.set_key = mt76x02_set_key,
	.conf_tx = mt76x02_conf_tx,
	.sw_scan_start = mt76_sw_scan,
	.sw_scan_complete = mt76x02_sw_scan_complete,
	.ampdu_action = mt76x02_ampdu_action,
	.sta_rate_tbl_update = mt76x02_sta_rate_tbl_update,
	.wake_tx_queue = mt76_wake_tx_queue,
	.get_survey = mt76_get_survey,
	.get_txघातer = mt76_get_txघातer,
	.flush = mt76x0e_flush,
	.set_tim = mt76_set_tim,
	.release_buffered_frames = mt76_release_buffered_frames,
	.set_coverage_class = mt76x02_set_coverage_class,
	.set_rts_threshold = mt76x02_set_rts_threshold,
	.get_antenna = mt76_get_antenna,
	.reconfig_complete = mt76x02_reconfig_complete,
पूर्ण;

अटल पूर्णांक mt76x0e_init_hardware(काष्ठा mt76x02_dev *dev, bool resume)
अणु
	पूर्णांक err;

	mt76x0_chip_onoff(dev, true, false);
	अगर (!mt76x02_रुको_क्रम_mac(&dev->mt76))
		वापस -ETIMEDOUT;

	mt76x02_dma_disable(dev);
	err = mt76x0e_mcu_init(dev);
	अगर (err < 0)
		वापस err;

	अगर (!resume) अणु
		err = mt76x02_dma_init(dev);
		अगर (err < 0)
			वापस err;
	पूर्ण

	err = mt76x0_init_hardware(dev);
	अगर (err < 0)
		वापस err;

	mt76x02e_init_beacon_config(dev);

	अगर (mt76_chip(&dev->mt76) == 0x7610) अणु
		u16 val;

		mt76_clear(dev, MT_COEXCFG0, BIT(0));

		val = mt76x02_eeprom_get(dev, MT_EE_NIC_CONF_0);
		अगर (!(val & MT_EE_NIC_CONF_0_PA_IO_CURRENT))
			mt76_set(dev, MT_XO_CTRL7, 0xc03);
	पूर्ण

	mt76_clear(dev, 0x110, BIT(9));
	mt76_set(dev, MT_MAX_LEN_CFG, BIT(13));

	वापस 0;
पूर्ण

अटल पूर्णांक mt76x0e_रेजिस्टर_device(काष्ठा mt76x02_dev *dev)
अणु
	पूर्णांक err;

	err = mt76x0e_init_hardware(dev, false);
	अगर (err < 0)
		वापस err;

	err = mt76x0_रेजिस्टर_device(dev);
	अगर (err < 0)
		वापस err;

	set_bit(MT76_STATE_INITIALIZED, &dev->mphy.state);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt76x0e_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
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

	mt76_pci_disable_aspm(pdev);

	mdev = mt76_alloc_device(&pdev->dev, माप(*dev), &mt76x0e_ops,
				 &drv_ops);
	अगर (!mdev)
		वापस -ENOMEM;

	dev = container_of(mdev, काष्ठा mt76x02_dev, mt76);
	mutex_init(&dev->phy_mutex);

	mt76_mmio_init(mdev, pcim_iomap_table(pdev)[0]);

	mdev->rev = mt76_rr(dev, MT_ASIC_VERSION);
	dev_info(mdev->dev, "ASIC revision: %08x\n", mdev->rev);

	mt76_wr(dev, MT_INT_MASK_CSR, 0);

	ret = devm_request_irq(mdev->dev, pdev->irq, mt76x02_irq_handler,
			       IRQF_SHARED, KBUILD_MODNAME, dev);
	अगर (ret)
		जाओ error;

	ret = mt76x0e_रेजिस्टर_device(dev);
	अगर (ret < 0)
		जाओ error;

	वापस 0;

error:
	mt76_मुक्त_device(&dev->mt76);

	वापस ret;
पूर्ण

अटल व्योम mt76x0e_cleanup(काष्ठा mt76x02_dev *dev)
अणु
	clear_bit(MT76_STATE_INITIALIZED, &dev->mphy.state);
	tasklet_disable(&dev->mt76.pre_tbtt_tasklet);
	mt76x0_chip_onoff(dev, false, false);
	mt76x0e_stop_hw(dev);
	mt76_dma_cleanup(&dev->mt76);
	mt76x02_mcu_cleanup(dev);
पूर्ण

अटल व्योम
mt76x0e_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mt76_dev *mdev = pci_get_drvdata(pdev);
	काष्ठा mt76x02_dev *dev = container_of(mdev, काष्ठा mt76x02_dev, mt76);

	mt76_unरेजिस्टर_device(mdev);
	mt76x0e_cleanup(dev);
	mt76_मुक्त_device(mdev);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक mt76x0e_suspend(काष्ठा pci_dev *pdev, pm_message_t state)
अणु
	काष्ठा mt76_dev *mdev = pci_get_drvdata(pdev);
	काष्ठा mt76x02_dev *dev = container_of(mdev, काष्ठा mt76x02_dev, mt76);
	पूर्णांक i;

	mt76_worker_disable(&mdev->tx_worker);
	क्रम (i = 0; i < ARRAY_SIZE(mdev->phy.q_tx); i++)
		mt76_queue_tx_cleanup(dev, mdev->phy.q_tx[i], true);
	क्रम (i = 0; i < ARRAY_SIZE(mdev->q_mcu); i++)
		mt76_queue_tx_cleanup(dev, mdev->q_mcu[i], true);
	napi_disable(&mdev->tx_napi);

	mt76_क्रम_each_q_rx(mdev, i)
		napi_disable(&mdev->napi[i]);

	mt76x02_dma_disable(dev);
	mt76x02_mcu_cleanup(dev);
	mt76x0_chip_onoff(dev, false, false);

	pci_enable_wake(pdev, pci_choose_state(pdev, state), true);
	pci_save_state(pdev);

	वापस pci_set_घातer_state(pdev, pci_choose_state(pdev, state));
पूर्ण

अटल पूर्णांक mt76x0e_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mt76_dev *mdev = pci_get_drvdata(pdev);
	काष्ठा mt76x02_dev *dev = container_of(mdev, काष्ठा mt76x02_dev, mt76);
	पूर्णांक err, i;

	err = pci_set_घातer_state(pdev, PCI_D0);
	अगर (err)
		वापस err;

	pci_restore_state(pdev);

	mt76_worker_enable(&mdev->tx_worker);

	mt76_क्रम_each_q_rx(mdev, i) अणु
		mt76_queue_rx_reset(dev, i);
		napi_enable(&mdev->napi[i]);
		napi_schedule(&mdev->napi[i]);
	पूर्ण

	napi_enable(&mdev->tx_napi);
	napi_schedule(&mdev->tx_napi);

	वापस mt76x0e_init_hardware(dev, true);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा pci_device_id mt76x0e_device_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_MEDIATEK, 0x7610) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_MEDIATEK, 0x7630) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_MEDIATEK, 0x7650) पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, mt76x0e_device_table);
MODULE_FIRMWARE(MT7610E_FIRMWARE);
MODULE_FIRMWARE(MT7650E_FIRMWARE);
MODULE_LICENSE("Dual BSD/GPL");

अटल काष्ठा pci_driver mt76x0e_driver = अणु
	.name		= KBUILD_MODNAME,
	.id_table	= mt76x0e_device_table,
	.probe		= mt76x0e_probe,
	.हटाओ		= mt76x0e_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= mt76x0e_suspend,
	.resume		= mt76x0e_resume,
#पूर्ण_अगर /* CONFIG_PM */
पूर्ण;

module_pci_driver(mt76x0e_driver);
