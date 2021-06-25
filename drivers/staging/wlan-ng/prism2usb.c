<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "hfa384x_usb.c"
#समावेश "prism2mgmt.c"
#समावेश "prism2mib.c"
#समावेश "prism2sta.c"
#समावेश "prism2fw.c"

#घोषणा PRISM_DEV(vid, pid, name)		\
	अणु USB_DEVICE(vid, pid),			\
	.driver_info = (अचिन्हित दीर्घ)name पूर्ण

अटल स्थिर काष्ठा usb_device_id usb_prism_tbl[] = अणु
	PRISM_DEV(0x04bb, 0x0922, "IOData AirPort WN-B11/USBS"),
	PRISM_DEV(0x07aa, 0x0012, "Corega Wireless LAN USB Stick-11"),
	PRISM_DEV(0x09aa, 0x3642, "Prism2.x 11Mbps WLAN USB Adapter"),
	PRISM_DEV(0x1668, 0x0408, "Actiontec Prism2.5 11Mbps WLAN USB Adapter"),
	PRISM_DEV(0x1668, 0x0421, "Actiontec Prism2.5 11Mbps WLAN USB Adapter"),
	PRISM_DEV(0x1915, 0x2236, "Linksys WUSB11v3.0 11Mbps WLAN USB Adapter"),
	PRISM_DEV(0x066b, 0x2212, "Linksys WUSB11v2.5 11Mbps WLAN USB Adapter"),
	PRISM_DEV(0x066b, 0x2213, "Linksys WUSB12v1.1 11Mbps WLAN USB Adapter"),
	PRISM_DEV(0x0411, 0x0016, "Melco WLI-USB-S11 11Mbps WLAN Adapter"),
	PRISM_DEV(0x08de, 0x7a01, "PRISM25 IEEE 802.11 Mini USB Adapter"),
	PRISM_DEV(0x8086, 0x1111, "Intel PRO/Wireless 2011B LAN USB Adapter"),
	PRISM_DEV(0x0d8e, 0x7a01, "PRISM25 IEEE 802.11 Mini USB Adapter"),
	PRISM_DEV(0x045e, 0x006e, "Microsoft MN510 Wireless USB Adapter"),
	PRISM_DEV(0x0967, 0x0204, "Acer Warplink USB Adapter"),
	PRISM_DEV(0x0cde, 0x0002, "Z-Com 725/726 Prism2.5 USB/USB Integrated"),
	PRISM_DEV(0x0cde, 0x0005, "Z-Com Xl735 Wireless 802.11b USB Adapter"),
	PRISM_DEV(0x413c, 0x8100, "Dell TrueMobile 1180 Wireless USB Adapter"),
	PRISM_DEV(0x0b3b, 0x1601, "ALLNET 0193 11Mbps WLAN USB Adapter"),
	PRISM_DEV(0x0b3b, 0x1602, "ZyXEL ZyAIR B200 Wireless USB Adapter"),
	PRISM_DEV(0x0baf, 0x00eb, "USRobotics USR1120 Wireless USB Adapter"),
	PRISM_DEV(0x0411, 0x0027, "Melco WLI-USB-KS11G 11Mbps WLAN Adapter"),
	PRISM_DEV(0x04f1, 0x3009, "JVC MP-XP7250 Builtin USB WLAN Adapter"),
	PRISM_DEV(0x0846, 0x4110, "NetGear MA111"),
	PRISM_DEV(0x03f3, 0x0020, "Adaptec AWN-8020 USB WLAN Adapter"),
	PRISM_DEV(0x2821, 0x3300, "ASUS-WL140 Wireless USB Adapter"),
	PRISM_DEV(0x2001, 0x3700, "DWL-122 Wireless USB Adapter"),
	PRISM_DEV(0x2001, 0x3702, "DWL-120 Rev F Wireless USB Adapter"),
	PRISM_DEV(0x50c2, 0x4013, "Averatec USB WLAN Adapter"),
	PRISM_DEV(0x2c02, 0x14ea, "Planex GW-US11H WLAN USB Adapter"),
	PRISM_DEV(0x124a, 0x168b, "Airvast PRISM3 WLAN USB Adapter"),
	PRISM_DEV(0x083a, 0x3503, "T-Sinus 111 USB WLAN Adapter"),
	PRISM_DEV(0x2821, 0x3300, "Hawking HighDB USB Adapter"),
	PRISM_DEV(0x0411, 0x0044, "Melco WLI-USB-KB11 11Mbps WLAN Adapter"),
	PRISM_DEV(0x1668, 0x6106, "ROPEX FreeLan 802.11b USB Adapter"),
	PRISM_DEV(0x124a, 0x4017, "Pheenet WL-503IA 802.11b USB Adapter"),
	PRISM_DEV(0x0bb2, 0x0302, "Ambit Microsystems Corp."),
	PRISM_DEV(0x9016, 0x182d, "Sitecom WL-022 802.11b USB Adapter"),
	PRISM_DEV(0x0543, 0x0f01,
		  "ViewSonic Airsync USB Adapter 11Mbps (Prism2.5)"),
	PRISM_DEV(0x067c, 0x1022,
		  "Siemens SpeedStream 1022 11Mbps WLAN USB Adapter"),
	PRISM_DEV(0x049f, 0x0033,
		  "Compaq/Intel W100 PRO/Wireless 11Mbps multiport WLAN Adapter"),
	अणु पूर्ण /* terminator */
पूर्ण;
MODULE_DEVICE_TABLE(usb, usb_prism_tbl);

अटल पूर्णांक prism2sta_probe_usb(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
			       स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *dev;
	काष्ठा usb_endpoपूर्णांक_descriptor *bulk_in, *bulk_out;
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc = पूर्णांकerface->cur_altsetting;
	काष्ठा wlandevice *wlandev = शून्य;
	काष्ठा hfa384x *hw = शून्य;
	पूर्णांक result = 0;

	result = usb_find_common_endpoपूर्णांकs(अगरace_desc, &bulk_in, &bulk_out, शून्य, शून्य);
	अगर (result)
		जाओ failed;

	dev = पूर्णांकerface_to_usbdev(पूर्णांकerface);
	wlandev = create_wlan();
	अगर (!wlandev) अणु
		dev_err(&पूर्णांकerface->dev, "Memory allocation failure.\n");
		result = -EIO;
		जाओ failed;
	पूर्ण
	hw = wlandev->priv;

	अगर (wlan_setup(wlandev, &पूर्णांकerface->dev) != 0) अणु
		dev_err(&पूर्णांकerface->dev, "wlan_setup() failed.\n");
		result = -EIO;
		जाओ failed;
	पूर्ण

	/* Initialize the hw data */
	hw->endp_in = usb_rcvbulkpipe(dev, bulk_in->bEndpoपूर्णांकAddress);
	hw->endp_out = usb_sndbulkpipe(dev, bulk_out->bEndpoपूर्णांकAddress);
	hfa384x_create(hw, dev);
	hw->wlandev = wlandev;

	/* Register the wlandev, this माला_लो us a name and रेजिस्टरs the
	 * linux netdevice.
	 */
	SET_NETDEV_DEV(wlandev->netdev, &पूर्णांकerface->dev);

	/* Do a chip-level reset on the MAC */
	अगर (prism2_करोreset) अणु
		result = hfa384x_corereset(hw,
					   prism2_reset_holdसमय,
					   prism2_reset_settleसमय, 0);
		अगर (result != 0) अणु
			result = -EIO;
			dev_err(&पूर्णांकerface->dev,
				"hfa384x_corereset() failed.\n");
			जाओ failed_reset;
		पूर्ण
	पूर्ण

	usb_get_dev(dev);

	wlandev->msdstate = WLAN_MSD_HWPRESENT;

	/* Try and load firmware, then enable card beक्रमe we रेजिस्टर */
	prism2_fwtry(dev, wlandev);
	prism2sta_अगरstate(wlandev, P80211ENUM_अगरstate_enable);

	अगर (रेजिस्टर_wlandev(wlandev) != 0) अणु
		dev_err(&पूर्णांकerface->dev, "register_wlandev() failed.\n");
		result = -EIO;
		जाओ failed_रेजिस्टर;
	पूर्ण

	जाओ करोne;

failed_रेजिस्टर:
	usb_put_dev(dev);
failed_reset:
	wlan_unsetup(wlandev);
failed:
	kमुक्त(wlandev);
	kमुक्त(hw);
	wlandev = शून्य;

करोne:
	usb_set_पूर्णांकfdata(पूर्णांकerface, wlandev);
	वापस result;
पूर्ण

अटल व्योम prism2sta_disconnect_usb(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा wlandevice *wlandev;

	wlandev = usb_get_पूर्णांकfdata(पूर्णांकerface);
	अगर (wlandev) अणु
		LIST_HEAD(cleanlist);
		काष्ठा hfa384x_usbctlx *ctlx, *temp;
		अचिन्हित दीर्घ flags;

		काष्ठा hfa384x *hw = wlandev->priv;

		अगर (!hw)
			जाओ निकास;

		spin_lock_irqsave(&hw->ctlxq.lock, flags);

		p80211netdev_hwहटाओd(wlandev);
		list_splice_init(&hw->ctlxq.reapable, &cleanlist);
		list_splice_init(&hw->ctlxq.completing, &cleanlist);
		list_splice_init(&hw->ctlxq.pending, &cleanlist);
		list_splice_init(&hw->ctlxq.active, &cleanlist);

		spin_unlock_irqrestore(&hw->ctlxq.lock, flags);

		/* There's no hardware to shutकरोwn, but the driver
		 * might have some tasks or tasklets that must be
		 * stopped beक्रमe we can tear everything करोwn.
		 */
		prism2sta_अगरstate(wlandev, P80211ENUM_अगरstate_disable);

		del_singleshot_समयr_sync(&hw->throttle);
		del_singleshot_समयr_sync(&hw->reqसमयr);
		del_singleshot_समयr_sync(&hw->respसमयr);

		/* Unlink all the URBs. This "removes the wheels"
		 * from the entire CTLX handling mechanism.
		 */
		usb_समाप्त_urb(&hw->rx_urb);
		usb_समाप्त_urb(&hw->tx_urb);
		usb_समाप्त_urb(&hw->ctlx_urb);

		tasklet_समाप्त(&hw->completion_bh);
		tasklet_समाप्त(&hw->reaper_bh);

		cancel_work_sync(&hw->link_bh);
		cancel_work_sync(&hw->commsqual_bh);
		cancel_work_sync(&hw->usb_work);

		/* Now we complete any outstanding commands
		 * and tell everyone who is रुकोing क्रम their
		 * responses that we have shut करोwn.
		 */
		list_क्रम_each_entry(ctlx, &cleanlist, list)
			complete(&ctlx->करोne);

		/* Give any outstanding synchronous commands
		 * a chance to complete. All they need to करो
		 * is "wake up", so that's easy.
		 * (I'd like a better way to करो this, really.)
		 */
		msleep(100);

		/* Now delete the CTLXs, because no-one अन्यथा can now. */
		list_क्रम_each_entry_safe(ctlx, temp, &cleanlist, list)
			kमुक्त(ctlx);

		/* Unhook the wlandev */
		unरेजिस्टर_wlandev(wlandev);
		wlan_unsetup(wlandev);

		usb_put_dev(hw->usb);

		hfa384x_destroy(hw);
		kमुक्त(hw);

		kमुक्त(wlandev);
	पूर्ण

निकास:
	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक prism2sta_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
			     pm_message_t message)
अणु
	काष्ठा hfa384x *hw = शून्य;
	काष्ठा wlandevice *wlandev;

	wlandev = usb_get_पूर्णांकfdata(पूर्णांकerface);
	अगर (!wlandev)
		वापस -ENODEV;

	hw = wlandev->priv;
	अगर (!hw)
		वापस -ENODEV;

	prism2sta_अगरstate(wlandev, P80211ENUM_अगरstate_disable);

	usb_समाप्त_urb(&hw->rx_urb);
	usb_समाप्त_urb(&hw->tx_urb);
	usb_समाप्त_urb(&hw->ctlx_urb);

	वापस 0;
पूर्ण

अटल पूर्णांक prism2sta_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	पूर्णांक result = 0;
	काष्ठा hfa384x *hw = शून्य;
	काष्ठा wlandevice *wlandev;

	wlandev = usb_get_पूर्णांकfdata(पूर्णांकerface);
	अगर (!wlandev)
		वापस -ENODEV;

	hw = wlandev->priv;
	अगर (!hw)
		वापस -ENODEV;

	/* Do a chip-level reset on the MAC */
	अगर (prism2_करोreset) अणु
		result = hfa384x_corereset(hw,
					   prism2_reset_holdसमय,
					   prism2_reset_settleसमय, 0);
		अगर (result != 0) अणु
			unरेजिस्टर_wlandev(wlandev);
			hfa384x_destroy(hw);
			dev_err(&पूर्णांकerface->dev, "hfa384x_corereset() failed.\n");
			kमुक्त(wlandev);
			kमुक्त(hw);
			wlandev = शून्य;
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	prism2sta_अगरstate(wlandev, P80211ENUM_अगरstate_enable);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा prism2sta_suspend शून्य
#घोषणा prism2sta_resume शून्य
#पूर्ण_अगर /* CONFIG_PM */

अटल काष्ठा usb_driver prism2_usb_driver = अणु
	.name = "prism2_usb",
	.probe = prism2sta_probe_usb,
	.disconnect = prism2sta_disconnect_usb,
	.id_table = usb_prism_tbl,
	.suspend = prism2sta_suspend,
	.resume = prism2sta_resume,
	.reset_resume = prism2sta_resume,
	/* fops, minor? */
पूर्ण;

module_usb_driver(prism2_usb_driver);
