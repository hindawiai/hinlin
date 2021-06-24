<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Jakub Kicinski <kubakici@wp.pl>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>

#समावेश "mt76x0.h"
#समावेश "mcu.h"
#समावेश "../mt76x02_usb.h"

अटल काष्ठा usb_device_id mt76x0_device_table[] = अणु
	अणु USB_DEVICE(0x148F, 0x7610) पूर्ण,	/* MT7610U */
	अणु USB_DEVICE(0x13B1, 0x003E) पूर्ण,	/* Linksys AE6000 */
	अणु USB_DEVICE(0x0E8D, 0x7610) पूर्ण,	/* Sabrent NTWLAC */
	अणु USB_DEVICE(0x7392, 0xa711) पूर्ण,	/* Edimax 7711mac */
	अणु USB_DEVICE(0x7392, 0xb711) पूर्ण,	/* Edimax / Elecom  */
	अणु USB_DEVICE(0x148f, 0x761a) पूर्ण,	/* TP-Link TL-WDN5200 */
	अणु USB_DEVICE(0x148f, 0x760a) पूर्ण,	/* TP-Link unknown */
	अणु USB_DEVICE(0x0b05, 0x17d1) पूर्ण,	/* Asus USB-AC51 */
	अणु USB_DEVICE(0x0b05, 0x17db) पूर्ण,	/* Asus USB-AC50 */
	अणु USB_DEVICE(0x0df6, 0x0075) पूर्ण,	/* Sitecom WLA-3100 */
	अणु USB_DEVICE(0x2019, 0xab31) पूर्ण,	/* Planex GW-450D */
	अणु USB_DEVICE(0x2001, 0x3d02) पूर्ण,	/* D-LINK DWA-171 rev B1 */
	अणु USB_DEVICE(0x0586, 0x3425) पूर्ण,	/* Zyxel NWD6505 */
	अणु USB_DEVICE(0x07b8, 0x7610) पूर्ण,	/* AboCom AU7212 */
	अणु USB_DEVICE(0x04bb, 0x0951) पूर्ण,	/* I-O DATA WN-AC433UK */
	अणु USB_DEVICE(0x057c, 0x8502) पूर्ण,	/* AVM FRITZ!WLAN USB Stick AC 430 */
	अणु USB_DEVICE(0x293c, 0x5702) पूर्ण,	/* Comcast Xfinity KXW02AAA  */
	अणु USB_DEVICE(0x20f4, 0x806b) पूर्ण,	/* TRENDnet TEW-806UBH  */
	अणु USB_DEVICE(0x7392, 0xc711) पूर्ण, /* Devolo Wअगरi ac Stick */
	अणु USB_DEVICE(0x0df6, 0x0079) पूर्ण, /* Sitecom Europe B.V. ac  Stick */
	अणु USB_DEVICE(0x2357, 0x0123) पूर्ण, /* TP-LINK T2UHP_US_v1 */
	अणु USB_DEVICE(0x2357, 0x010b) पूर्ण, /* TP-LINK T2UHP_UN_v1 */
	/* TP-LINK Archer T1U */
	अणु USB_DEVICE(0x2357, 0x0105), .driver_info = 1, पूर्ण,
	/* MT7630U */
	अणु USB_DEVICE_AND_INTERFACE_INFO(0x0E8D, 0x7630, 0xff, 0x2, 0xff)पूर्ण,
	/* MT7650U */
	अणु USB_DEVICE_AND_INTERFACE_INFO(0x0E8D, 0x7650, 0xff, 0x2, 0xff)पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

अटल व्योम mt76x0_init_usb_dma(काष्ठा mt76x02_dev *dev)
अणु
	u32 val;

	val = mt76_rr(dev, MT_USB_DMA_CFG);

	val |= MT_USB_DMA_CFG_RX_BULK_EN |
	       MT_USB_DMA_CFG_TX_BULK_EN;

	/* disable AGGR_BULK_RX in order to receive one
	 * frame in each rx urb and aव्योम copies
	 */
	val &= ~MT_USB_DMA_CFG_RX_BULK_AGG_EN;
	mt76_wr(dev, MT_USB_DMA_CFG, val);

	val = mt76_rr(dev, MT_COM_REG0);
	अगर (val & 1)
		dev_dbg(dev->mt76.dev, "MCU not ready\n");

	val = mt76_rr(dev, MT_USB_DMA_CFG);

	val |= MT_USB_DMA_CFG_RX_DROP_OR_PAD;
	mt76_wr(dev, MT_USB_DMA_CFG, val);
	val &= ~MT_USB_DMA_CFG_RX_DROP_OR_PAD;
	mt76_wr(dev, MT_USB_DMA_CFG, val);
पूर्ण

अटल व्योम mt76x0u_cleanup(काष्ठा mt76x02_dev *dev)
अणु
	clear_bit(MT76_STATE_INITIALIZED, &dev->mphy.state);
	mt76x0_chip_onoff(dev, false, false);
	mt76u_queues_deinit(&dev->mt76);
पूर्ण

अटल व्योम mt76x0u_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mt76x02_dev *dev = hw->priv;

	clear_bit(MT76_STATE_RUNNING, &dev->mphy.state);
	cancel_delayed_work_sync(&dev->cal_work);
	cancel_delayed_work_sync(&dev->mphy.mac_work);
	mt76u_stop_tx(&dev->mt76);
	mt76x02u_निकास_beacon_config(dev);

	अगर (test_bit(MT76_REMOVED, &dev->mphy.state))
		वापस;

	अगर (!mt76_poll(dev, MT_USB_DMA_CFG, MT_USB_DMA_CFG_TX_BUSY, 0, 1000))
		dev_warn(dev->mt76.dev, "TX DMA did not stop\n");

	mt76x0_mac_stop(dev);

	अगर (!mt76_poll(dev, MT_USB_DMA_CFG, MT_USB_DMA_CFG_RX_BUSY, 0, 1000))
		dev_warn(dev->mt76.dev, "RX DMA did not stop\n");
पूर्ण

अटल पूर्णांक mt76x0u_start(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mt76x02_dev *dev = hw->priv;
	पूर्णांक ret;

	ret = mt76x02u_mac_start(dev);
	अगर (ret)
		वापस ret;

	mt76x0_phy_calibrate(dev, true);
	ieee80211_queue_delayed_work(dev->mt76.hw, &dev->mphy.mac_work,
				     MT_MAC_WORK_INTERVAL);
	ieee80211_queue_delayed_work(dev->mt76.hw, &dev->cal_work,
				     MT_CALIBRATE_INTERVAL);
	set_bit(MT76_STATE_RUNNING, &dev->mphy.state);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ieee80211_ops mt76x0u_ops = अणु
	.tx = mt76x02_tx,
	.start = mt76x0u_start,
	.stop = mt76x0u_stop,
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
	.set_rts_threshold = mt76x02_set_rts_threshold,
	.wake_tx_queue = mt76_wake_tx_queue,
	.get_txघातer = mt76_get_txघातer,
	.get_survey = mt76_get_survey,
	.set_tim = mt76_set_tim,
	.release_buffered_frames = mt76_release_buffered_frames,
	.get_antenna = mt76_get_antenna,
पूर्ण;

अटल पूर्णांक mt76x0u_init_hardware(काष्ठा mt76x02_dev *dev, bool reset)
अणु
	पूर्णांक err;

	mt76x0_chip_onoff(dev, true, reset);

	अगर (!mt76x02_रुको_क्रम_mac(&dev->mt76))
		वापस -ETIMEDOUT;

	err = mt76x0u_mcu_init(dev);
	अगर (err < 0)
		वापस err;

	mt76x0_init_usb_dma(dev);
	err = mt76x0_init_hardware(dev);
	अगर (err < 0)
		वापस err;

	mt76x02u_init_beacon_config(dev);

	mt76_rmw(dev, MT_US_CYC_CFG, MT_US_CYC_CNT, 0x1e);
	mt76_wr(dev, MT_TXOP_CTRL_CFG,
		FIELD_PREP(MT_TXOP_TRUN_EN, 0x3f) |
		FIELD_PREP(MT_TXOP_EXT_CCA_DLY, 0x58));

	वापस 0;
पूर्ण

अटल पूर्णांक mt76x0u_रेजिस्टर_device(काष्ठा mt76x02_dev *dev)
अणु
	काष्ठा ieee80211_hw *hw = dev->mt76.hw;
	काष्ठा mt76_usb *usb = &dev->mt76.usb;
	पूर्णांक err;

	usb->mcu.data = devm_kदो_स्मृति(dev->mt76.dev, MCU_RESP_URB_SIZE,
				     GFP_KERNEL);
	अगर (!usb->mcu.data)
		वापस -ENOMEM;

	err = mt76u_alloc_queues(&dev->mt76);
	अगर (err < 0)
		जाओ out_err;

	err = mt76x0u_init_hardware(dev, true);
	अगर (err < 0)
		जाओ out_err;

	/* check hw sg support in order to enable AMSDU */
	hw->max_tx_fragments = dev->mt76.usb.sg_en ? MT_TX_SG_MAX_SIZE : 1;
	err = mt76x0_रेजिस्टर_device(dev);
	अगर (err < 0)
		जाओ out_err;

	set_bit(MT76_STATE_INITIALIZED, &dev->mphy.state);

	वापस 0;

out_err:
	mt76x0u_cleanup(dev);
	वापस err;
पूर्ण

अटल पूर्णांक mt76x0u_probe(काष्ठा usb_पूर्णांकerface *usb_पूर्णांकf,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	अटल स्थिर काष्ठा mt76_driver_ops drv_ops = अणु
		.drv_flags = MT_DRV_SW_RX_AIRTIME,
		.survey_flags = SURVEY_INFO_TIME_TX,
		.update_survey = mt76x02_update_channel,
		.tx_prepare_skb = mt76x02u_tx_prepare_skb,
		.tx_complete_skb = mt76x02u_tx_complete_skb,
		.tx_status_data = mt76x02_tx_status_data,
		.rx_skb = mt76x02_queue_rx_skb,
		.sta_ps = mt76x02_sta_ps,
		.sta_add = mt76x02_sta_add,
		.sta_हटाओ = mt76x02_sta_हटाओ,
	पूर्ण;
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(usb_पूर्णांकf);
	काष्ठा mt76x02_dev *dev;
	काष्ठा mt76_dev *mdev;
	u32 mac_rev;
	पूर्णांक ret;

	mdev = mt76_alloc_device(&usb_पूर्णांकf->dev, माप(*dev), &mt76x0u_ops,
				 &drv_ops);
	अगर (!mdev)
		वापस -ENOMEM;

	dev = container_of(mdev, काष्ठा mt76x02_dev, mt76);
	mutex_init(&dev->phy_mutex);

	/* Quirk क्रम Archer T1U */
	अगर (id->driver_info)
		dev->no_2ghz = true;

	usb_dev = usb_get_dev(usb_dev);
	usb_reset_device(usb_dev);

	usb_set_पूर्णांकfdata(usb_पूर्णांकf, dev);

	mt76x02u_init_mcu(mdev);
	ret = mt76u_init(mdev, usb_पूर्णांकf, false);
	अगर (ret)
		जाओ err;

	/* Disable the HW, otherwise MCU fail to initialize on hot reboot */
	mt76x0_chip_onoff(dev, false, false);

	अगर (!mt76x02_रुको_क्रम_mac(mdev)) अणु
		ret = -ETIMEDOUT;
		जाओ err;
	पूर्ण

	mdev->rev = mt76_rr(dev, MT_ASIC_VERSION);
	mac_rev = mt76_rr(dev, MT_MAC_CSR0);
	dev_info(mdev->dev, "ASIC revision: %08x MAC revision: %08x\n",
		 mdev->rev, mac_rev);
	अगर (!is_mt76x0(dev)) अणु
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	/* Note: venकरोr driver skips this check क्रम MT76X0U */
	अगर (!(mt76_rr(dev, MT_EFUSE_CTRL) & MT_EFUSE_CTRL_SEL))
		dev_warn(mdev->dev, "Warning: eFUSE not present\n");

	ret = mt76x0u_रेजिस्टर_device(dev);
	अगर (ret < 0)
		जाओ err;

	वापस 0;

err:
	usb_set_पूर्णांकfdata(usb_पूर्णांकf, शून्य);
	usb_put_dev(पूर्णांकerface_to_usbdev(usb_पूर्णांकf));
	mt76u_queues_deinit(&dev->mt76);
	mt76_मुक्त_device(&dev->mt76);

	वापस ret;
पूर्ण

अटल व्योम mt76x0_disconnect(काष्ठा usb_पूर्णांकerface *usb_पूर्णांकf)
अणु
	काष्ठा mt76x02_dev *dev = usb_get_पूर्णांकfdata(usb_पूर्णांकf);
	bool initialized = test_bit(MT76_STATE_INITIALIZED, &dev->mphy.state);

	अगर (!initialized)
		वापस;

	ieee80211_unरेजिस्टर_hw(dev->mt76.hw);
	mt76x0u_cleanup(dev);

	usb_set_पूर्णांकfdata(usb_पूर्णांकf, शून्य);
	usb_put_dev(पूर्णांकerface_to_usbdev(usb_पूर्णांकf));

	mt76_मुक्त_device(&dev->mt76);
पूर्ण

अटल पूर्णांक __maybe_unused mt76x0_suspend(काष्ठा usb_पूर्णांकerface *usb_पूर्णांकf,
					 pm_message_t state)
अणु
	काष्ठा mt76x02_dev *dev = usb_get_पूर्णांकfdata(usb_पूर्णांकf);

	mt76u_stop_rx(&dev->mt76);
	clear_bit(MT76_STATE_MCU_RUNNING, &dev->mphy.state);
	mt76x0_chip_onoff(dev, false, false);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mt76x0_resume(काष्ठा usb_पूर्णांकerface *usb_पूर्णांकf)
अणु
	काष्ठा mt76x02_dev *dev = usb_get_पूर्णांकfdata(usb_पूर्णांकf);
	पूर्णांक ret;

	ret = mt76u_resume_rx(&dev->mt76);
	अगर (ret < 0)
		जाओ err;

	ret = mt76x0u_init_hardware(dev, false);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	mt76x0u_cleanup(dev);
	वापस ret;
पूर्ण

MODULE_DEVICE_TABLE(usb, mt76x0_device_table);
MODULE_FIRMWARE(MT7610E_FIRMWARE);
MODULE_FIRMWARE(MT7610U_FIRMWARE);
MODULE_LICENSE("GPL");

अटल काष्ठा usb_driver mt76x0_driver = अणु
	.name		= KBUILD_MODNAME,
	.id_table	= mt76x0_device_table,
	.probe		= mt76x0u_probe,
	.disconnect	= mt76x0_disconnect,
	.suspend	= mt76x0_suspend,
	.resume		= mt76x0_resume,
	.reset_resume	= mt76x0_resume,
	.soft_unbind	= 1,
	.disable_hub_initiated_lpm = 1,
पूर्ण;
module_usb_driver(mt76x0_driver);
