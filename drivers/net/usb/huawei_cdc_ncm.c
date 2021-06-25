<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* huawei_cdc_ncm.c - handles Huawei devices using the CDC NCM protocol as
 * transport layer.
 * Copyright (C) 2013	 Enrico Mioso <mrkiko.rs@gmail.com>
 *
 * ABSTRACT:
 * This driver handles devices resembling the CDC NCM standard, but
 * encapsulating another protocol inside it. An example are some Huawei 3G
 * devices, exposing an embedded AT channel where you can set up the NCM
 * connection.
 * This code has been heavily inspired by the cdc_mbim.c driver, which is
 * Copyright (c) 2012  Smith Micro Software, Inc.
 * Copyright (c) 2012  Bjथचrn Mork <bjorn@mork.no>
 */

#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/ip.h>
#समावेश <linux/mii.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/cdc.h>
#समावेश <linux/usb/usbnet.h>
#समावेश <linux/usb/cdc-wdm.h>
#समावेश <linux/usb/cdc_ncm.h>

/* Driver data */
काष्ठा huawei_cdc_ncm_state अणु
	काष्ठा cdc_ncm_ctx *ctx;
	atomic_t pmcount;
	काष्ठा usb_driver *subdriver;
	काष्ठा usb_पूर्णांकerface *control;
	काष्ठा usb_पूर्णांकerface *data;
पूर्ण;

अटल पूर्णांक huawei_cdc_ncm_manage_घातer(काष्ठा usbnet *usbnet_dev, पूर्णांक on)
अणु
	काष्ठा huawei_cdc_ncm_state *drvstate = (व्योम *)&usbnet_dev->data;
	पूर्णांक rv;

	अगर ((on && atomic_add_वापस(1, &drvstate->pmcount) == 1) ||
			(!on && atomic_dec_and_test(&drvstate->pmcount))) अणु
		rv = usb_स्वतःpm_get_पूर्णांकerface(usbnet_dev->पूर्णांकf);
		usbnet_dev->पूर्णांकf->needs_remote_wakeup = on;
		अगर (!rv)
			usb_स्वतःpm_put_पूर्णांकerface(usbnet_dev->पूर्णांकf);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक huawei_cdc_ncm_wdm_manage_घातer(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
					   पूर्णांक status)
अणु
	काष्ठा usbnet *usbnet_dev = usb_get_पूर्णांकfdata(पूर्णांकf);

	/* can be called जबतक disconnecting */
	अगर (!usbnet_dev)
		वापस 0;

	वापस huawei_cdc_ncm_manage_घातer(usbnet_dev, status);
पूर्ण


अटल पूर्णांक huawei_cdc_ncm_bind(काष्ठा usbnet *usbnet_dev,
			       काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा cdc_ncm_ctx *ctx;
	काष्ठा usb_driver *subdriver = ERR_PTR(-ENODEV);
	पूर्णांक ret;
	काष्ठा huawei_cdc_ncm_state *drvstate = (व्योम *)&usbnet_dev->data;
	पूर्णांक drvflags = 0;

	/* altsetting should always be 1 क्रम NCM devices - so we hard-coded
	 * it here. Some huawei devices will need the NDP part of the NCM package to
	 * be at the end of the frame.
	 */
	drvflags |= CDC_NCM_FLAG_NDP_TO_END;

	/* For many Huawei devices the NTB32 mode is the शेष and the best mode
	 * they work with. Huawei E5785 and E5885 devices refuse to work in NTB16 mode at all.
	 */
	drvflags |= CDC_NCM_FLAG_PREFER_NTB32;

	ret = cdc_ncm_bind_common(usbnet_dev, पूर्णांकf, 1, drvflags);
	अगर (ret)
		जाओ err;

	ctx = drvstate->ctx;

	अगर (usbnet_dev->status)
		/* The wMaxCommand buffer must be big enough to hold
		 * any message from the modem. Experience has shown
		 * that some replies are more than 256 bytes दीर्घ
		 */
		subdriver = usb_cdc_wdm_रेजिस्टर(ctx->control,
						 &usbnet_dev->status->desc,
						 1024, /* wMaxCommand */
						 huawei_cdc_ncm_wdm_manage_घातer);
	अगर (IS_ERR(subdriver)) अणु
		ret = PTR_ERR(subdriver);
		cdc_ncm_unbind(usbnet_dev, पूर्णांकf);
		जाओ err;
	पूर्ण

	/* Prevent usbnet from using the status descriptor */
	usbnet_dev->status = शून्य;

	drvstate->subdriver = subdriver;

err:
	वापस ret;
पूर्ण

अटल व्योम huawei_cdc_ncm_unbind(काष्ठा usbnet *usbnet_dev,
				  काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा huawei_cdc_ncm_state *drvstate = (व्योम *)&usbnet_dev->data;
	काष्ठा cdc_ncm_ctx *ctx = drvstate->ctx;

	अगर (drvstate->subdriver && drvstate->subdriver->disconnect)
		drvstate->subdriver->disconnect(ctx->control);
	drvstate->subdriver = शून्य;

	cdc_ncm_unbind(usbnet_dev, पूर्णांकf);
पूर्ण

अटल पूर्णांक huawei_cdc_ncm_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
				  pm_message_t message)
अणु
	पूर्णांक ret = 0;
	काष्ठा usbnet *usbnet_dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा huawei_cdc_ncm_state *drvstate = (व्योम *)&usbnet_dev->data;
	काष्ठा cdc_ncm_ctx *ctx = drvstate->ctx;

	अगर (ctx == शून्य) अणु
		ret = -ENODEV;
		जाओ error;
	पूर्ण

	ret = usbnet_suspend(पूर्णांकf, message);
	अगर (ret < 0)
		जाओ error;

	अगर (पूर्णांकf == ctx->control &&
		drvstate->subdriver &&
		drvstate->subdriver->suspend)
		ret = drvstate->subdriver->suspend(पूर्णांकf, message);
	अगर (ret < 0)
		usbnet_resume(पूर्णांकf);

error:
	वापस ret;
पूर्ण

अटल पूर्णांक huawei_cdc_ncm_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	पूर्णांक ret = 0;
	काष्ठा usbnet *usbnet_dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा huawei_cdc_ncm_state *drvstate = (व्योम *)&usbnet_dev->data;
	bool callsub;
	काष्ठा cdc_ncm_ctx *ctx = drvstate->ctx;

	/* should we call subdriver's resume function? */
	callsub =
		(पूर्णांकf == ctx->control &&
		drvstate->subdriver &&
		drvstate->subdriver->resume);

	अगर (callsub)
		ret = drvstate->subdriver->resume(पूर्णांकf);
	अगर (ret < 0)
		जाओ err;
	ret = usbnet_resume(पूर्णांकf);
	अगर (ret < 0 && callsub)
		drvstate->subdriver->suspend(पूर्णांकf, PMSG_SUSPEND);
err:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा driver_info huawei_cdc_ncm_info = अणु
	.description = "Huawei CDC NCM device",
	.flags = FLAG_NO_SETINT | FLAG_MULTI_PACKET | FLAG_WWAN,
	.bind = huawei_cdc_ncm_bind,
	.unbind = huawei_cdc_ncm_unbind,
	.manage_घातer = huawei_cdc_ncm_manage_घातer,
	.rx_fixup = cdc_ncm_rx_fixup,
	.tx_fixup = cdc_ncm_tx_fixup,
पूर्ण;

अटल स्थिर काष्ठा usb_device_id huawei_cdc_ncm_devs[] = अणु
	/* Huawei NCM devices disguised as venकरोr specअगरic */
	अणु USB_VENDOR_AND_INTERFACE_INFO(0x12d1, 0xff, 0x02, 0x16),
	  .driver_info = (अचिन्हित दीर्घ)&huawei_cdc_ncm_info,
	पूर्ण,
	अणु USB_VENDOR_AND_INTERFACE_INFO(0x12d1, 0xff, 0x02, 0x46),
	  .driver_info = (अचिन्हित दीर्घ)&huawei_cdc_ncm_info,
	पूर्ण,
	अणु USB_VENDOR_AND_INTERFACE_INFO(0x12d1, 0xff, 0x02, 0x76),
	  .driver_info = (अचिन्हित दीर्घ)&huawei_cdc_ncm_info,
	पूर्ण,
	अणु USB_VENDOR_AND_INTERFACE_INFO(0x12d1, 0xff, 0x03, 0x16),
	  .driver_info = (अचिन्हित दीर्घ)&huawei_cdc_ncm_info,
	पूर्ण,

	/* Terminating entry */
	अणु
	पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(usb, huawei_cdc_ncm_devs);

अटल काष्ठा usb_driver huawei_cdc_ncm_driver = अणु
	.name = "huawei_cdc_ncm",
	.id_table = huawei_cdc_ncm_devs,
	.probe = usbnet_probe,
	.disconnect = usbnet_disconnect,
	.suspend = huawei_cdc_ncm_suspend,
	.resume = huawei_cdc_ncm_resume,
	.reset_resume = huawei_cdc_ncm_resume,
	.supports_स्वतःsuspend = 1,
	.disable_hub_initiated_lpm = 1,
पूर्ण;
module_usb_driver(huawei_cdc_ncm_driver);
MODULE_AUTHOR("Enrico Mioso <mrkiko.rs@gmail.com>");
MODULE_DESCRIPTION("USB CDC NCM host driver with encapsulated protocol support");
MODULE_LICENSE("GPL");
