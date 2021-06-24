<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2018 Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश "../mt76x02_usb.h"
#समावेश "mt76x2u.h"

अटल स्थिर काष्ठा usb_device_id mt76x2u_device_table[] = अणु
	अणु USB_DEVICE(0x0b05, 0x1833) पूर्ण,	/* Asus USB-AC54 */
	अणु USB_DEVICE(0x0b05, 0x17eb) पूर्ण,	/* Asus USB-AC55 */
	अणु USB_DEVICE(0x0b05, 0x180b) पूर्ण,	/* Asus USB-N53 B1 */
	अणु USB_DEVICE(0x0e8d, 0x7612) पूर्ण,	/* Aukey USBAC1200 - Alfa AWUS036ACM */
	अणु USB_DEVICE(0x057c, 0x8503) पूर्ण,	/* Avm FRITZ!WLAN AC860 */
	अणु USB_DEVICE(0x7392, 0xb711) पूर्ण,	/* Edimax EW 7722 UAC */
	अणु USB_DEVICE(0x0e8d, 0x7632) पूर्ण,	/* HC-M7662BU1 */
	अणु USB_DEVICE(0x2c4e, 0x0103) पूर्ण,	/* Mercury UD13 */
	अणु USB_DEVICE(0x0846, 0x9053) पूर्ण,	/* Netgear A6210 */
	अणु USB_DEVICE(0x045e, 0x02e6) पूर्ण,	/* XBox One Wireless Adapter */
	अणु USB_DEVICE(0x045e, 0x02fe) पूर्ण,	/* XBox One Wireless Adapter */
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक mt76x2u_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
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
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा mt76x02_dev *dev;
	काष्ठा mt76_dev *mdev;
	पूर्णांक err;

	mdev = mt76_alloc_device(&पूर्णांकf->dev, माप(*dev), &mt76x2u_ops,
				 &drv_ops);
	अगर (!mdev)
		वापस -ENOMEM;

	dev = container_of(mdev, काष्ठा mt76x02_dev, mt76);

	udev = usb_get_dev(udev);
	usb_reset_device(udev);

	usb_set_पूर्णांकfdata(पूर्णांकf, dev);

	mt76x02u_init_mcu(mdev);
	err = mt76u_init(mdev, पूर्णांकf, false);
	अगर (err < 0)
		जाओ err;

	mdev->rev = mt76_rr(dev, MT_ASIC_VERSION);
	dev_info(mdev->dev, "ASIC revision: %08x\n", mdev->rev);
	अगर (!is_mt76x2(dev)) अणु
		err = -ENODEV;
		जाओ err;
	पूर्ण

	err = mt76x2u_रेजिस्टर_device(dev);
	अगर (err < 0)
		जाओ err;

	वापस 0;

err:
	mt76u_queues_deinit(&dev->mt76);
	mt76_मुक्त_device(&dev->mt76);
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	usb_put_dev(udev);

	वापस err;
पूर्ण

अटल व्योम mt76x2u_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा mt76x02_dev *dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा ieee80211_hw *hw = mt76_hw(dev);

	set_bit(MT76_REMOVED, &dev->mphy.state);
	ieee80211_unरेजिस्टर_hw(hw);
	mt76x2u_cleanup(dev);
	mt76_मुक्त_device(&dev->mt76);
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	usb_put_dev(udev);
पूर्ण

अटल पूर्णांक __maybe_unused mt76x2u_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
					  pm_message_t state)
अणु
	काष्ठा mt76x02_dev *dev = usb_get_पूर्णांकfdata(पूर्णांकf);

	mt76u_stop_rx(&dev->mt76);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mt76x2u_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा mt76x02_dev *dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक err;

	err = mt76u_resume_rx(&dev->mt76);
	अगर (err < 0)
		जाओ err;

	err = mt76x2u_init_hardware(dev);
	अगर (err < 0)
		जाओ err;

	वापस 0;

err:
	mt76x2u_cleanup(dev);
	वापस err;
पूर्ण

MODULE_DEVICE_TABLE(usb, mt76x2u_device_table);
MODULE_FIRMWARE(MT7662_FIRMWARE);
MODULE_FIRMWARE(MT7662_ROM_PATCH);

अटल काष्ठा usb_driver mt76x2u_driver = अणु
	.name		= KBUILD_MODNAME,
	.id_table	= mt76x2u_device_table,
	.probe		= mt76x2u_probe,
	.disconnect	= mt76x2u_disconnect,
#अगर_घोषित CONFIG_PM
	.suspend	= mt76x2u_suspend,
	.resume		= mt76x2u_resume,
	.reset_resume	= mt76x2u_resume,
#पूर्ण_अगर /* CONFIG_PM */
	.soft_unbind	= 1,
	.disable_hub_initiated_lpm = 1,
पूर्ण;
module_usb_driver(mt76x2u_driver);

MODULE_AUTHOR("Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>");
MODULE_LICENSE("Dual BSD/GPL");
