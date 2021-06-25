<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2019 MediaTek Inc.
 *
 * Author: Felix Fietkau <nbd@nbd.name>
 *	   Lorenzo Bianconi <lorenzo@kernel.org>
 *	   Sean Wang <sean.wang@mediatek.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>

#समावेश "mt7615.h"
#समावेश "mac.h"
#समावेश "mcu.h"
#समावेश "regs.h"

अटल स्थिर काष्ठा usb_device_id mt7615_device_table[] = अणु
	अणु USB_DEVICE_AND_INTERFACE_INFO(0x0e8d, 0x7663, 0xff, 0xff, 0xff) पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल व्योम mt7663u_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा mt7615_phy *phy = mt7615_hw_phy(hw);
	काष्ठा mt7615_dev *dev = hw->priv;

	clear_bit(MT76_STATE_RUNNING, &dev->mphy.state);
	del_समयr_sync(&phy->roc_समयr);
	cancel_work_sync(&phy->roc_work);
	cancel_delayed_work_sync(&phy->scan_work);
	cancel_delayed_work_sync(&phy->mt76->mac_work);
	mt76u_stop_tx(&dev->mt76);
पूर्ण

अटल व्योम mt7663u_cleanup(काष्ठा mt7615_dev *dev)
अणु
	clear_bit(MT76_STATE_INITIALIZED, &dev->mphy.state);
	mt76u_queues_deinit(&dev->mt76);
पूर्ण

अटल व्योम mt7663u_init_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mt7615_dev *dev;

	dev = container_of(work, काष्ठा mt7615_dev, mcu_work);
	अगर (mt7663u_mcu_init(dev))
		वापस;

	mt7615_init_work(dev);
पूर्ण

अटल पूर्णांक mt7663u_probe(काष्ठा usb_पूर्णांकerface *usb_पूर्णांकf,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	अटल स्थिर काष्ठा mt76_driver_ops drv_ops = अणु
		.txwi_size = MT_USB_TXD_SIZE,
		.drv_flags = MT_DRV_RX_DMA_HDR | MT_DRV_HW_MGMT_TXQ,
		.tx_prepare_skb = mt7663_usb_sdio_tx_prepare_skb,
		.tx_complete_skb = mt7663_usb_sdio_tx_complete_skb,
		.tx_status_data = mt7663_usb_sdio_tx_status_data,
		.rx_skb = mt7615_queue_rx_skb,
		.sta_ps = mt7615_sta_ps,
		.sta_add = mt7615_mac_sta_add,
		.sta_हटाओ = mt7615_mac_sta_हटाओ,
		.update_survey = mt7615_update_channel,
	पूर्ण;
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(usb_पूर्णांकf);
	काष्ठा ieee80211_ops *ops;
	काष्ठा mt7615_dev *dev;
	काष्ठा mt76_dev *mdev;
	पूर्णांक ret;

	ops = devm_kmemdup(&usb_पूर्णांकf->dev, &mt7615_ops, माप(mt7615_ops),
			   GFP_KERNEL);
	अगर (!ops)
		वापस -ENOMEM;

	ops->stop = mt7663u_stop;

	mdev = mt76_alloc_device(&usb_पूर्णांकf->dev, माप(*dev), ops, &drv_ops);
	अगर (!mdev)
		वापस -ENOMEM;

	dev = container_of(mdev, काष्ठा mt7615_dev, mt76);
	udev = usb_get_dev(udev);
	usb_reset_device(udev);

	usb_set_पूर्णांकfdata(usb_पूर्णांकf, dev);

	INIT_WORK(&dev->mcu_work, mt7663u_init_work);
	dev->reg_map = mt7663_usb_sdio_reg_map;
	dev->ops = ops;
	ret = mt76u_init(mdev, usb_पूर्णांकf, true);
	अगर (ret < 0)
		जाओ error;

	mdev->rev = (mt76_rr(dev, MT_HW_CHIPID) << 16) |
		    (mt76_rr(dev, MT_HW_REV) & 0xff);
	dev_dbg(mdev->dev, "ASIC revision: %04x\n", mdev->rev);

	अगर (mt76_poll_msec(dev, MT_CONN_ON_MISC, MT_TOP_MISC2_FW_PWR_ON,
			   FW_STATE_PWR_ON << 1, 500)) अणु
		dev_dbg(dev->mt76.dev, "Usb device already powered on\n");
		set_bit(MT76_STATE_POWER_OFF, &dev->mphy.state);
		जाओ alloc_queues;
	पूर्ण

	ret = mt76u_venकरोr_request(&dev->mt76, MT_VEND_POWER_ON,
				   USB_सूची_OUT | USB_TYPE_VENDOR,
				   0x0, 0x1, शून्य, 0);
	अगर (ret)
		जाओ error;

	अगर (!mt76_poll_msec(dev, MT_CONN_ON_MISC, MT_TOP_MISC2_FW_PWR_ON,
			    FW_STATE_PWR_ON << 1, 500)) अणु
		dev_err(dev->mt76.dev, "Timeout for power on\n");
		ret = -EIO;
		जाओ error;
	पूर्ण

alloc_queues:
	ret = mt76u_alloc_mcu_queue(&dev->mt76);
	अगर (ret)
		जाओ error;

	ret = mt76u_alloc_queues(&dev->mt76);
	अगर (ret)
		जाओ error;

	ret = mt7663_usb_sdio_रेजिस्टर_device(dev);
	अगर (ret)
		जाओ error;

	वापस 0;

error:
	mt76u_queues_deinit(&dev->mt76);
	usb_set_पूर्णांकfdata(usb_पूर्णांकf, शून्य);
	usb_put_dev(पूर्णांकerface_to_usbdev(usb_पूर्णांकf));

	mt76_मुक्त_device(&dev->mt76);

	वापस ret;
पूर्ण

अटल व्योम mt7663u_disconnect(काष्ठा usb_पूर्णांकerface *usb_पूर्णांकf)
अणु
	काष्ठा mt7615_dev *dev = usb_get_पूर्णांकfdata(usb_पूर्णांकf);

	अगर (!test_bit(MT76_STATE_INITIALIZED, &dev->mphy.state))
		वापस;

	ieee80211_unरेजिस्टर_hw(dev->mt76.hw);
	mt7663u_cleanup(dev);

	usb_set_पूर्णांकfdata(usb_पूर्णांकf, शून्य);
	usb_put_dev(पूर्णांकerface_to_usbdev(usb_पूर्णांकf));

	mt76_मुक्त_device(&dev->mt76);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक mt7663u_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t state)
अणु
	काष्ठा mt7615_dev *dev = usb_get_पूर्णांकfdata(पूर्णांकf);

	अगर (!test_bit(MT76_STATE_SUSPEND, &dev->mphy.state) &&
	    mt7615_firmware_offload(dev)) अणु
		पूर्णांक err;

		err = mt76_connac_mcu_set_hअगर_suspend(&dev->mt76, true);
		अगर (err < 0)
			वापस err;
	पूर्ण

	mt76u_stop_rx(&dev->mt76);
	mt76u_stop_tx(&dev->mt76);

	वापस 0;
पूर्ण

अटल पूर्णांक mt7663u_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा mt7615_dev *dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक err;

	err = mt76u_venकरोr_request(&dev->mt76, MT_VEND_FEATURE_SET,
				   USB_सूची_OUT | USB_TYPE_VENDOR,
				   0x5, 0x0, शून्य, 0);
	अगर (err)
		वापस err;

	err = mt76u_resume_rx(&dev->mt76);
	अगर (err < 0)
		वापस err;

	अगर (!test_bit(MT76_STATE_SUSPEND, &dev->mphy.state) &&
	    mt7615_firmware_offload(dev))
		err = mt76_connac_mcu_set_hअगर_suspend(&dev->mt76, false);

	वापस err;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

MODULE_DEVICE_TABLE(usb, mt7615_device_table);
MODULE_FIRMWARE(MT7663_OFFLOAD_FIRMWARE_N9);
MODULE_FIRMWARE(MT7663_OFFLOAD_ROM_PATCH);
MODULE_FIRMWARE(MT7663_FIRMWARE_N9);
MODULE_FIRMWARE(MT7663_ROM_PATCH);

अटल काष्ठा usb_driver mt7663u_driver = अणु
	.name		= KBUILD_MODNAME,
	.id_table	= mt7615_device_table,
	.probe		= mt7663u_probe,
	.disconnect	= mt7663u_disconnect,
#अगर_घोषित CONFIG_PM
	.suspend	= mt7663u_suspend,
	.resume		= mt7663u_resume,
	.reset_resume	= mt7663u_resume,
#पूर्ण_अगर /* CONFIG_PM */
	.soft_unbind	= 1,
	.disable_hub_initiated_lpm = 1,
पूर्ण;
module_usb_driver(mt7663u_driver);

MODULE_AUTHOR("Sean Wang <sean.wang@mediatek.com>");
MODULE_AUTHOR("Lorenzo Bianconi <lorenzo@kernel.org>");
MODULE_LICENSE("Dual BSD/GPL");
