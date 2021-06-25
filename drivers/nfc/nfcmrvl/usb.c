<शैली गुरु>
/*
 * Marvell NFC-over-USB driver: USB पूर्णांकerface related functions
 *
 * Copyright (C) 2014, Marvell International Ltd.
 *
 * This software file (the "File") is distributed by Marvell International
 * Ltd. under the terms of the GNU General Public License Version 2, June 1991
 * (the "License").  You may use, redistribute and/or modअगरy this File in
 * accordance with the terms and conditions of the License, a copy of which
 * is available on the worldwide web at
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 *
 * THE खाता IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE
 * ARE EXPRESSLY DISCLAIMED.  The License provides additional details about
 * this warranty disclaimer.
 **/

#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/nfc.h>
#समावेश <net/nfc/nci.h>
#समावेश <net/nfc/nci_core.h>
#समावेश "nfcmrvl.h"

अटल काष्ठा usb_device_id nfcmrvl_table[] = अणु
	अणु USB_DEVICE_AND_INTERFACE_INFO(0x1286, 0x2046,
					USB_CLASS_VENDOR_SPEC, 4, 1) पूर्ण,
	अणु पूर्ण	/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, nfcmrvl_table);

#घोषणा NFCMRVL_USB_BULK_RUNNING	1
#घोषणा NFCMRVL_USB_SUSPENDING		2

काष्ठा nfcmrvl_usb_drv_data अणु
	काष्ठा usb_device *udev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	अचिन्हित दीर्घ flags;
	काष्ठा work_काष्ठा waker;
	काष्ठा usb_anchor tx_anchor;
	काष्ठा usb_anchor bulk_anchor;
	काष्ठा usb_anchor deferred;
	पूर्णांक tx_in_flight;
	/* protects tx_in_flight */
	spinlock_t txlock;
	काष्ठा usb_endpoपूर्णांक_descriptor *bulk_tx_ep;
	काष्ठा usb_endpoपूर्णांक_descriptor *bulk_rx_ep;
	पूर्णांक suspend_count;
	काष्ठा nfcmrvl_निजी *priv;
पूर्ण;

अटल पूर्णांक nfcmrvl_inc_tx(काष्ठा nfcmrvl_usb_drv_data *drv_data)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rv;

	spin_lock_irqsave(&drv_data->txlock, flags);
	rv = test_bit(NFCMRVL_USB_SUSPENDING, &drv_data->flags);
	अगर (!rv)
		drv_data->tx_in_flight++;
	spin_unlock_irqrestore(&drv_data->txlock, flags);

	वापस rv;
पूर्ण

अटल व्योम nfcmrvl_bulk_complete(काष्ठा urb *urb)
अणु
	काष्ठा nfcmrvl_usb_drv_data *drv_data = urb->context;
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	dev_dbg(&drv_data->udev->dev, "urb %p status %d count %d\n",
		urb, urb->status, urb->actual_length);

	अगर (!test_bit(NFCMRVL_NCI_RUNNING, &drv_data->flags))
		वापस;

	अगर (!urb->status) अणु
		skb = nci_skb_alloc(drv_data->priv->ndev, urb->actual_length,
				    GFP_ATOMIC);
		अगर (!skb) अणु
			nfc_err(&drv_data->udev->dev, "failed to alloc mem\n");
		पूर्ण अन्यथा अणु
			skb_put_data(skb, urb->transfer_buffer,
				     urb->actual_length);
			अगर (nfcmrvl_nci_recv_frame(drv_data->priv, skb) < 0)
				nfc_err(&drv_data->udev->dev,
					"corrupted Rx packet\n");
		पूर्ण
	पूर्ण

	अगर (!test_bit(NFCMRVL_USB_BULK_RUNNING, &drv_data->flags))
		वापस;

	usb_anchor_urb(urb, &drv_data->bulk_anchor);
	usb_mark_last_busy(drv_data->udev);

	err = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (err) अणु
		/* -EPERM: urb is being समाप्तed;
		 * -ENODEV: device got disconnected
		 */
		अगर (err != -EPERM && err != -ENODEV)
			nfc_err(&drv_data->udev->dev,
				"urb %p failed to resubmit (%d)\n", urb, -err);
		usb_unanchor_urb(urb);
	पूर्ण
पूर्ण

अटल पूर्णांक
nfcmrvl_submit_bulk_urb(काष्ठा nfcmrvl_usb_drv_data *drv_data, gfp_t mem_flags)
अणु
	काष्ठा urb *urb;
	अचिन्हित अक्षर *buf;
	अचिन्हित पूर्णांक pipe;
	पूर्णांक err, size = NFCMRVL_NCI_MAX_EVENT_SIZE;

	अगर (!drv_data->bulk_rx_ep)
		वापस -ENODEV;

	urb = usb_alloc_urb(0, mem_flags);
	अगर (!urb)
		वापस -ENOMEM;

	buf = kदो_स्मृति(size, mem_flags);
	अगर (!buf) अणु
		usb_मुक्त_urb(urb);
		वापस -ENOMEM;
	पूर्ण

	pipe = usb_rcvbulkpipe(drv_data->udev,
			       drv_data->bulk_rx_ep->bEndpoपूर्णांकAddress);

	usb_fill_bulk_urb(urb, drv_data->udev, pipe, buf, size,
			  nfcmrvl_bulk_complete, drv_data);

	urb->transfer_flags |= URB_FREE_BUFFER;

	usb_mark_last_busy(drv_data->udev);
	usb_anchor_urb(urb, &drv_data->bulk_anchor);

	err = usb_submit_urb(urb, mem_flags);
	अगर (err) अणु
		अगर (err != -EPERM && err != -ENODEV)
			nfc_err(&drv_data->udev->dev,
				"urb %p submission failed (%d)\n", urb, -err);
		usb_unanchor_urb(urb);
	पूर्ण

	usb_मुक्त_urb(urb);

	वापस err;
पूर्ण

अटल व्योम nfcmrvl_tx_complete(काष्ठा urb *urb)
अणु
	काष्ठा sk_buff *skb = urb->context;
	काष्ठा nci_dev *ndev = (काष्ठा nci_dev *)skb->dev;
	काष्ठा nfcmrvl_निजी *priv = nci_get_drvdata(ndev);
	काष्ठा nfcmrvl_usb_drv_data *drv_data = priv->drv_data;
	अचिन्हित दीर्घ flags;

	nfc_info(priv->dev, "urb %p status %d count %d\n",
		 urb, urb->status, urb->actual_length);

	spin_lock_irqsave(&drv_data->txlock, flags);
	drv_data->tx_in_flight--;
	spin_unlock_irqrestore(&drv_data->txlock, flags);

	kमुक्त(urb->setup_packet);
	kमुक्त_skb(skb);
पूर्ण

अटल पूर्णांक nfcmrvl_usb_nci_खोलो(काष्ठा nfcmrvl_निजी *priv)
अणु
	काष्ठा nfcmrvl_usb_drv_data *drv_data = priv->drv_data;
	पूर्णांक err;

	err = usb_स्वतःpm_get_पूर्णांकerface(drv_data->पूर्णांकf);
	अगर (err)
		वापस err;

	drv_data->पूर्णांकf->needs_remote_wakeup = 1;

	err = nfcmrvl_submit_bulk_urb(drv_data, GFP_KERNEL);
	अगर (err)
		जाओ failed;

	set_bit(NFCMRVL_USB_BULK_RUNNING, &drv_data->flags);
	nfcmrvl_submit_bulk_urb(drv_data, GFP_KERNEL);

	usb_स्वतःpm_put_पूर्णांकerface(drv_data->पूर्णांकf);
	वापस 0;

failed:
	usb_स्वतःpm_put_पूर्णांकerface(drv_data->पूर्णांकf);
	वापस err;
पूर्ण

अटल व्योम nfcmrvl_usb_stop_traffic(काष्ठा nfcmrvl_usb_drv_data *drv_data)
अणु
	usb_समाप्त_anchored_urbs(&drv_data->bulk_anchor);
पूर्ण

अटल पूर्णांक nfcmrvl_usb_nci_बंद(काष्ठा nfcmrvl_निजी *priv)
अणु
	काष्ठा nfcmrvl_usb_drv_data *drv_data = priv->drv_data;
	पूर्णांक err;

	cancel_work_sync(&drv_data->waker);

	clear_bit(NFCMRVL_USB_BULK_RUNNING, &drv_data->flags);

	nfcmrvl_usb_stop_traffic(drv_data);
	usb_समाप्त_anchored_urbs(&drv_data->tx_anchor);
	err = usb_स्वतःpm_get_पूर्णांकerface(drv_data->पूर्णांकf);
	अगर (err)
		जाओ failed;

	drv_data->पूर्णांकf->needs_remote_wakeup = 0;
	usb_स्वतःpm_put_पूर्णांकerface(drv_data->पूर्णांकf);

failed:
	usb_scuttle_anchored_urbs(&drv_data->deferred);
	वापस 0;
पूर्ण

अटल पूर्णांक nfcmrvl_usb_nci_send(काष्ठा nfcmrvl_निजी *priv,
				काष्ठा sk_buff *skb)
अणु
	काष्ठा nfcmrvl_usb_drv_data *drv_data = priv->drv_data;
	काष्ठा urb *urb;
	अचिन्हित पूर्णांक pipe;
	पूर्णांक err;

	अगर (!drv_data->bulk_tx_ep)
		वापस -ENODEV;

	urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!urb)
		वापस -ENOMEM;

	pipe = usb_sndbulkpipe(drv_data->udev,
				drv_data->bulk_tx_ep->bEndpoपूर्णांकAddress);

	usb_fill_bulk_urb(urb, drv_data->udev, pipe, skb->data, skb->len,
			  nfcmrvl_tx_complete, skb);

	err = nfcmrvl_inc_tx(drv_data);
	अगर (err) अणु
		usb_anchor_urb(urb, &drv_data->deferred);
		schedule_work(&drv_data->waker);
		err = 0;
		जाओ करोne;
	पूर्ण

	usb_anchor_urb(urb, &drv_data->tx_anchor);

	err = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (err) अणु
		अगर (err != -EPERM && err != -ENODEV)
			nfc_err(&drv_data->udev->dev,
				"urb %p submission failed (%d)\n", urb, -err);
		kमुक्त(urb->setup_packet);
		usb_unanchor_urb(urb);
	पूर्ण अन्यथा अणु
		usb_mark_last_busy(drv_data->udev);
	पूर्ण

करोne:
	usb_मुक्त_urb(urb);
	वापस err;
पूर्ण

अटल काष्ठा nfcmrvl_अगर_ops usb_ops = अणु
	.nci_खोलो = nfcmrvl_usb_nci_खोलो,
	.nci_बंद = nfcmrvl_usb_nci_बंद,
	.nci_send = nfcmrvl_usb_nci_send,
पूर्ण;

अटल व्योम nfcmrvl_waker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nfcmrvl_usb_drv_data *drv_data =
			container_of(work, काष्ठा nfcmrvl_usb_drv_data, waker);
	पूर्णांक err;

	err = usb_स्वतःpm_get_पूर्णांकerface(drv_data->पूर्णांकf);
	अगर (err)
		वापस;

	usb_स्वतःpm_put_पूर्णांकerface(drv_data->पूर्णांकf);
पूर्ण

अटल पूर्णांक nfcmrvl_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_endpoपूर्णांक_descriptor *ep_desc;
	काष्ठा nfcmrvl_usb_drv_data *drv_data;
	काष्ठा nfcmrvl_निजी *priv;
	पूर्णांक i;
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा nfcmrvl_platक्रमm_data config;

	/* No configuration क्रम USB */
	स_रखो(&config, 0, माप(config));
	config.reset_n_io = -EINVAL;

	nfc_info(&udev->dev, "intf %p id %p\n", पूर्णांकf, id);

	drv_data = devm_kzalloc(&पूर्णांकf->dev, माप(*drv_data), GFP_KERNEL);
	अगर (!drv_data)
		वापस -ENOMEM;

	क्रम (i = 0; i < पूर्णांकf->cur_altsetting->desc.bNumEndpoपूर्णांकs; i++) अणु
		ep_desc = &पूर्णांकf->cur_altsetting->endpoपूर्णांक[i].desc;

		अगर (!drv_data->bulk_tx_ep &&
		    usb_endpoपूर्णांक_is_bulk_out(ep_desc)) अणु
			drv_data->bulk_tx_ep = ep_desc;
			जारी;
		पूर्ण

		अगर (!drv_data->bulk_rx_ep &&
		    usb_endpoपूर्णांक_is_bulk_in(ep_desc)) अणु
			drv_data->bulk_rx_ep = ep_desc;
			जारी;
		पूर्ण
	पूर्ण

	अगर (!drv_data->bulk_tx_ep || !drv_data->bulk_rx_ep)
		वापस -ENODEV;

	drv_data->udev = udev;
	drv_data->पूर्णांकf = पूर्णांकf;

	INIT_WORK(&drv_data->waker, nfcmrvl_waker);
	spin_lock_init(&drv_data->txlock);

	init_usb_anchor(&drv_data->tx_anchor);
	init_usb_anchor(&drv_data->bulk_anchor);
	init_usb_anchor(&drv_data->deferred);

	priv = nfcmrvl_nci_रेजिस्टर_dev(NFCMRVL_PHY_USB, drv_data, &usb_ops,
					&पूर्णांकf->dev, &config);
	अगर (IS_ERR(priv))
		वापस PTR_ERR(priv);

	drv_data->priv = priv;
	drv_data->priv->support_fw_dnld = false;

	usb_set_पूर्णांकfdata(पूर्णांकf, drv_data);

	वापस 0;
पूर्ण

अटल व्योम nfcmrvl_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा nfcmrvl_usb_drv_data *drv_data = usb_get_पूर्णांकfdata(पूर्णांकf);

	अगर (!drv_data)
		वापस;

	nfc_info(&drv_data->udev->dev, "intf %p\n", पूर्णांकf);

	nfcmrvl_nci_unरेजिस्टर_dev(drv_data->priv);

	usb_set_पूर्णांकfdata(drv_data->पूर्णांकf, शून्य);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक nfcmrvl_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा nfcmrvl_usb_drv_data *drv_data = usb_get_पूर्णांकfdata(पूर्णांकf);

	nfc_info(&drv_data->udev->dev, "intf %p\n", पूर्णांकf);

	अगर (drv_data->suspend_count++)
		वापस 0;

	spin_lock_irq(&drv_data->txlock);
	अगर (!(PMSG_IS_AUTO(message) && drv_data->tx_in_flight)) अणु
		set_bit(NFCMRVL_USB_SUSPENDING, &drv_data->flags);
		spin_unlock_irq(&drv_data->txlock);
	पूर्ण अन्यथा अणु
		spin_unlock_irq(&drv_data->txlock);
		drv_data->suspend_count--;
		वापस -EBUSY;
	पूर्ण

	nfcmrvl_usb_stop_traffic(drv_data);
	usb_समाप्त_anchored_urbs(&drv_data->tx_anchor);

	वापस 0;
पूर्ण

अटल व्योम nfcmrvl_play_deferred(काष्ठा nfcmrvl_usb_drv_data *drv_data)
अणु
	काष्ठा urb *urb;
	पूर्णांक err;

	जबतक ((urb = usb_get_from_anchor(&drv_data->deferred))) अणु
		err = usb_submit_urb(urb, GFP_ATOMIC);
		अगर (err)
			अवरोध;

		drv_data->tx_in_flight++;
	पूर्ण
	usb_scuttle_anchored_urbs(&drv_data->deferred);
पूर्ण

अटल पूर्णांक nfcmrvl_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा nfcmrvl_usb_drv_data *drv_data = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक err = 0;

	nfc_info(&drv_data->udev->dev, "intf %p\n", पूर्णांकf);

	अगर (--drv_data->suspend_count)
		वापस 0;

	अगर (!test_bit(NFCMRVL_NCI_RUNNING, &drv_data->flags))
		जाओ करोne;

	अगर (test_bit(NFCMRVL_USB_BULK_RUNNING, &drv_data->flags)) अणु
		err = nfcmrvl_submit_bulk_urb(drv_data, GFP_NOIO);
		अगर (err) अणु
			clear_bit(NFCMRVL_USB_BULK_RUNNING, &drv_data->flags);
			जाओ failed;
		पूर्ण

		nfcmrvl_submit_bulk_urb(drv_data, GFP_NOIO);
	पूर्ण

	spin_lock_irq(&drv_data->txlock);
	nfcmrvl_play_deferred(drv_data);
	clear_bit(NFCMRVL_USB_SUSPENDING, &drv_data->flags);
	spin_unlock_irq(&drv_data->txlock);

	वापस 0;

failed:
	usb_scuttle_anchored_urbs(&drv_data->deferred);
करोne:
	spin_lock_irq(&drv_data->txlock);
	clear_bit(NFCMRVL_USB_SUSPENDING, &drv_data->flags);
	spin_unlock_irq(&drv_data->txlock);

	वापस err;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा usb_driver nfcmrvl_usb_driver = अणु
	.name		= "nfcmrvl",
	.probe		= nfcmrvl_probe,
	.disconnect	= nfcmrvl_disconnect,
#अगर_घोषित CONFIG_PM
	.suspend	= nfcmrvl_suspend,
	.resume		= nfcmrvl_resume,
	.reset_resume	= nfcmrvl_resume,
#पूर्ण_अगर
	.id_table	= nfcmrvl_table,
	.supports_स्वतःsuspend = 1,
	.disable_hub_initiated_lpm = 1,
	.soft_unbind = 1,
पूर्ण;
module_usb_driver(nfcmrvl_usb_driver);

MODULE_AUTHOR("Marvell International Ltd.");
MODULE_DESCRIPTION("Marvell NFC-over-USB driver");
MODULE_LICENSE("GPL v2");
