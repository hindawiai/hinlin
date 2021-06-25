<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2012 GCT Semiconductor, Inc. All rights reserved. */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/usb.h>
#समावेश <linux/sched.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/usb/cdc.h>
#समावेश <linux/रुको.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "gdm_usb.h"
#समावेश "gdm_lte.h"
#समावेश "hci.h"
#समावेश "hci_packet.h"
#समावेश "gdm_endian.h"

#घोषणा USB_DEVICE_CDC_DATA(vid, pid) \
	.match_flags = USB_DEVICE_ID_MATCH_DEVICE | \
		USB_DEVICE_ID_MATCH_INT_CLASS | \
		USB_DEVICE_ID_MATCH_INT_SUBCLASS,\
	.idVenकरोr = vid,\
	.idProduct = pid,\
	.bInterfaceClass = USB_CLASS_COMM,\
	.bInterfaceSubClass = USB_CDC_SUBCLASS_ETHERNET

#घोषणा USB_DEVICE_MASS_DATA(vid, pid) \
	.match_flags = USB_DEVICE_ID_MATCH_DEVICE | \
		USB_DEVICE_ID_MATCH_INT_INFO,\
	.idVenकरोr = vid,\
	.idProduct = pid,\
	.bInterfaceSubClass = USB_SC_SCSI, \
	.bInterfaceClass = USB_CLASS_MASS_STORAGE,\
	.bInterfaceProtocol = USB_PR_BULK

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु USB_DEVICE_CDC_DATA(VID_GCT, PID_GDM7240) पूर्ण, /* GCT GDM7240 */
	अणु USB_DEVICE_CDC_DATA(VID_GCT, PID_GDM7243) पूर्ण, /* GCT GDM7243 */
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, id_table);

अटल व्योम करो_tx(काष्ठा work_काष्ठा *work);
अटल व्योम करो_rx(काष्ठा work_काष्ठा *work);

अटल पूर्णांक gdm_usb_recv(व्योम *priv_dev,
			पूर्णांक (*cb)(व्योम *cb_data,
				  व्योम *data, पूर्णांक len, पूर्णांक context),
			व्योम *cb_data,
			पूर्णांक context);

अटल पूर्णांक request_mac_address(काष्ठा lte_udev *udev)
अणु
	काष्ठा hci_packet *hci;
	काष्ठा usb_device *usbdev = udev->usbdev;
	पूर्णांक actual;
	पूर्णांक ret = -1;

	hci = kदो_स्मृति(काष्ठा_size(hci, data, 1), GFP_KERNEL);
	अगर (!hci)
		वापस -ENOMEM;

	hci->cmd_evt = gdm_cpu_to_dev16(udev->gdm_ed, LTE_GET_INFORMATION);
	hci->len = gdm_cpu_to_dev16(udev->gdm_ed, 1);
	hci->data[0] = MAC_ADDRESS;

	ret = usb_bulk_msg(usbdev, usb_sndbulkpipe(usbdev, 2), hci, 5,
			   &actual, 1000);

	udev->request_mac_addr = 1;
	kमुक्त(hci);

	वापस ret;
पूर्ण

अटल काष्ठा usb_tx *alloc_tx_काष्ठा(पूर्णांक len)
अणु
	काष्ठा usb_tx *t = शून्य;
	पूर्णांक ret = 0;

	t = kzalloc(माप(*t), GFP_ATOMIC);
	अगर (!t) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	t->urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!(len % 512))
		len++;

	t->buf = kदो_स्मृति(len, GFP_ATOMIC);
	अगर (!t->urb || !t->buf) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

out:
	अगर (ret < 0) अणु
		अगर (t) अणु
			usb_मुक्त_urb(t->urb);
			kमुक्त(t->buf);
			kमुक्त(t);
		पूर्ण
		वापस शून्य;
	पूर्ण

	वापस t;
पूर्ण

अटल काष्ठा usb_tx_sdu *alloc_tx_sdu_काष्ठा(व्योम)
अणु
	काष्ठा usb_tx_sdu *t_sdu;

	t_sdu = kzalloc(माप(*t_sdu), GFP_KERNEL);
	अगर (!t_sdu)
		वापस शून्य;

	t_sdu->buf = kदो_स्मृति(SDU_BUF_SIZE, GFP_KERNEL);
	अगर (!t_sdu->buf) अणु
		kमुक्त(t_sdu);
		वापस शून्य;
	पूर्ण

	वापस t_sdu;
पूर्ण

अटल व्योम मुक्त_tx_काष्ठा(काष्ठा usb_tx *t)
अणु
	अगर (t) अणु
		usb_मुक्त_urb(t->urb);
		kमुक्त(t->buf);
		kमुक्त(t);
	पूर्ण
पूर्ण

अटल व्योम मुक्त_tx_sdu_काष्ठा(काष्ठा usb_tx_sdu *t_sdu)
अणु
	अगर (t_sdu) अणु
		kमुक्त(t_sdu->buf);
		kमुक्त(t_sdu);
	पूर्ण
पूर्ण

अटल काष्ठा usb_tx_sdu *get_tx_sdu_काष्ठा(काष्ठा tx_cxt *tx, पूर्णांक *no_spc)
अणु
	काष्ठा usb_tx_sdu *t_sdu;

	अगर (list_empty(&tx->मुक्त_list))
		वापस शून्य;

	t_sdu = list_entry(tx->मुक्त_list.next, काष्ठा usb_tx_sdu, list);
	list_del(&t_sdu->list);

	tx->avail_count--;

	*no_spc = list_empty(&tx->मुक्त_list) ? 1 : 0;

	वापस t_sdu;
पूर्ण

अटल व्योम put_tx_काष्ठा(काष्ठा tx_cxt *tx, काष्ठा usb_tx_sdu *t_sdu)
अणु
	list_add_tail(&t_sdu->list, &tx->मुक्त_list);
	tx->avail_count++;
पूर्ण

अटल काष्ठा usb_rx *alloc_rx_काष्ठा(व्योम)
अणु
	काष्ठा usb_rx *r = शून्य;
	पूर्णांक ret = 0;

	r = kदो_स्मृति(माप(*r), GFP_KERNEL);
	अगर (!r) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	r->urb = usb_alloc_urb(0, GFP_KERNEL);
	r->buf = kदो_स्मृति(RX_BUF_SIZE, GFP_KERNEL);
	अगर (!r->urb || !r->buf) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
out:

	अगर (ret < 0) अणु
		अगर (r) अणु
			usb_मुक्त_urb(r->urb);
			kमुक्त(r->buf);
			kमुक्त(r);
		पूर्ण
		वापस शून्य;
	पूर्ण

	वापस r;
पूर्ण

अटल व्योम मुक्त_rx_काष्ठा(काष्ठा usb_rx *r)
अणु
	अगर (r) अणु
		usb_मुक्त_urb(r->urb);
		kमुक्त(r->buf);
		kमुक्त(r);
	पूर्ण
पूर्ण

अटल काष्ठा usb_rx *get_rx_काष्ठा(काष्ठा rx_cxt *rx, पूर्णांक *no_spc)
अणु
	काष्ठा usb_rx *r;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rx->rx_lock, flags);

	अगर (list_empty(&rx->मुक्त_list)) अणु
		spin_unlock_irqrestore(&rx->rx_lock, flags);
		वापस शून्य;
	पूर्ण

	r = list_entry(rx->मुक्त_list.next, काष्ठा usb_rx, मुक्त_list);
	list_del(&r->मुक्त_list);

	rx->avail_count--;

	*no_spc = list_empty(&rx->मुक्त_list) ? 1 : 0;

	spin_unlock_irqrestore(&rx->rx_lock, flags);

	वापस r;
पूर्ण

अटल व्योम put_rx_काष्ठा(काष्ठा rx_cxt *rx, काष्ठा usb_rx *r)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rx->rx_lock, flags);

	list_add_tail(&r->मुक्त_list, &rx->मुक्त_list);
	rx->avail_count++;

	spin_unlock_irqrestore(&rx->rx_lock, flags);
पूर्ण

अटल व्योम release_usb(काष्ठा lte_udev *udev)
अणु
	काष्ठा rx_cxt	*rx = &udev->rx;
	काष्ठा tx_cxt	*tx = &udev->tx;
	काष्ठा usb_tx	*t, *t_next;
	काष्ठा usb_rx	*r, *r_next;
	काष्ठा usb_tx_sdu	*t_sdu, *t_sdu_next;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tx->lock, flags);
	list_क्रम_each_entry_safe(t_sdu, t_sdu_next, &tx->sdu_list, list) अणु
		list_del(&t_sdu->list);
		मुक्त_tx_sdu_काष्ठा(t_sdu);
	पूर्ण

	list_क्रम_each_entry_safe(t, t_next, &tx->hci_list, list) अणु
		list_del(&t->list);
		मुक्त_tx_काष्ठा(t);
	पूर्ण

	list_क्रम_each_entry_safe(t_sdu, t_sdu_next, &tx->मुक्त_list, list) अणु
		list_del(&t_sdu->list);
		मुक्त_tx_sdu_काष्ठा(t_sdu);
	पूर्ण
	spin_unlock_irqrestore(&tx->lock, flags);

	spin_lock_irqsave(&rx->submit_lock, flags);
	list_क्रम_each_entry_safe(r, r_next, &rx->rx_submit_list,
				 rx_submit_list) अणु
		spin_unlock_irqrestore(&rx->submit_lock, flags);
		usb_समाप्त_urb(r->urb);
		spin_lock_irqsave(&rx->submit_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&rx->submit_lock, flags);

	spin_lock_irqsave(&rx->rx_lock, flags);
	list_क्रम_each_entry_safe(r, r_next, &rx->मुक्त_list, मुक्त_list) अणु
		list_del(&r->मुक्त_list);
		मुक्त_rx_काष्ठा(r);
	पूर्ण
	spin_unlock_irqrestore(&rx->rx_lock, flags);

	spin_lock_irqsave(&rx->to_host_lock, flags);
	list_क्रम_each_entry_safe(r, r_next, &rx->to_host_list, to_host_list) अणु
		अगर (r->index == (व्योम *)udev) अणु
			list_del(&r->to_host_list);
			मुक्त_rx_काष्ठा(r);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&rx->to_host_lock, flags);
पूर्ण

अटल पूर्णांक init_usb(काष्ठा lte_udev *udev)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i;
	काष्ठा tx_cxt *tx = &udev->tx;
	काष्ठा rx_cxt *rx = &udev->rx;
	काष्ठा usb_tx_sdu *t_sdu = शून्य;
	काष्ठा usb_rx *r = शून्य;

	udev->send_complete = 1;
	udev->tx_stop = 0;
	udev->request_mac_addr = 0;
	udev->usb_state = PM_NORMAL;

	INIT_LIST_HEAD(&tx->sdu_list);
	INIT_LIST_HEAD(&tx->hci_list);
	INIT_LIST_HEAD(&tx->मुक्त_list);
	INIT_LIST_HEAD(&rx->rx_submit_list);
	INIT_LIST_HEAD(&rx->मुक्त_list);
	INIT_LIST_HEAD(&rx->to_host_list);
	spin_lock_init(&tx->lock);
	spin_lock_init(&rx->rx_lock);
	spin_lock_init(&rx->submit_lock);
	spin_lock_init(&rx->to_host_lock);

	tx->avail_count = 0;
	rx->avail_count = 0;

	udev->rx_cb = शून्य;

	क्रम (i = 0; i < MAX_NUM_SDU_BUF; i++) अणु
		t_sdu = alloc_tx_sdu_काष्ठा();
		अगर (!t_sdu) अणु
			ret = -ENOMEM;
			जाओ fail;
		पूर्ण

		list_add(&t_sdu->list, &tx->मुक्त_list);
		tx->avail_count++;
	पूर्ण

	क्रम (i = 0; i < MAX_RX_SUBMIT_COUNT * 2; i++) अणु
		r = alloc_rx_काष्ठा();
		अगर (!r) अणु
			ret = -ENOMEM;
			जाओ fail;
		पूर्ण

		list_add(&r->मुक्त_list, &rx->मुक्त_list);
		rx->avail_count++;
	पूर्ण
	INIT_DELAYED_WORK(&udev->work_tx, करो_tx);
	INIT_DELAYED_WORK(&udev->work_rx, करो_rx);
	वापस 0;
fail:
	release_usb(udev);
	वापस ret;
पूर्ण

अटल पूर्णांक set_mac_address(u8 *data, व्योम *arg)
अणु
	काष्ठा phy_dev *phy_dev = arg;
	काष्ठा lte_udev *udev = phy_dev->priv_dev;
	काष्ठा tlv *tlv = (काष्ठा tlv *)data;
	u8 mac_address[ETH_ALEN] = अणु0, पूर्ण;

	अगर (tlv->type == MAC_ADDRESS && udev->request_mac_addr) अणु
		स_नकल(mac_address, tlv->data, tlv->len);

		अगर (रेजिस्टर_lte_device(phy_dev,
					&udev->पूर्णांकf->dev, mac_address) < 0)
			pr_err("register lte device failed\n");

		udev->request_mac_addr = 0;

		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम करो_rx(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा lte_udev *udev =
		container_of(work, काष्ठा lte_udev, work_rx.work);
	काष्ठा rx_cxt *rx = &udev->rx;
	काष्ठा usb_rx *r;
	काष्ठा hci_packet *hci;
	काष्ठा phy_dev *phy_dev;
	u16 cmd_evt;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	जबतक (1) अणु
		spin_lock_irqsave(&rx->to_host_lock, flags);
		अगर (list_empty(&rx->to_host_list)) अणु
			spin_unlock_irqrestore(&rx->to_host_lock, flags);
			अवरोध;
		पूर्ण
		r = list_entry(rx->to_host_list.next,
			       काष्ठा usb_rx, to_host_list);
		list_del(&r->to_host_list);
		spin_unlock_irqrestore(&rx->to_host_lock, flags);

		phy_dev = r->cb_data;
		udev = phy_dev->priv_dev;
		hci = (काष्ठा hci_packet *)r->buf;
		cmd_evt = gdm_dev16_to_cpu(udev->gdm_ed, hci->cmd_evt);

		चयन (cmd_evt) अणु
		हाल LTE_GET_INFORMATION_RESULT:
			अगर (set_mac_address(hci->data, r->cb_data) == 0) अणु
				r->callback(r->cb_data,
					    r->buf,
					    r->urb->actual_length,
					    KERNEL_THREAD);
			पूर्ण
			अवरोध;

		शेष:
			अगर (r->callback) अणु
				ret = r->callback(r->cb_data,
						  r->buf,
						  r->urb->actual_length,
						  KERNEL_THREAD);

				अगर (ret == -EAGAIN)
					pr_err("failed to send received data\n");
			पूर्ण
			अवरोध;
		पूर्ण

		put_rx_काष्ठा(rx, r);

		gdm_usb_recv(udev,
			     r->callback,
			     r->cb_data,
			     USB_COMPLETE);
	पूर्ण
पूर्ण

अटल व्योम हटाओ_rx_submit_list(काष्ठा usb_rx *r, काष्ठा rx_cxt *rx)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा usb_rx	*r_हटाओ, *r_हटाओ_next;

	spin_lock_irqsave(&rx->submit_lock, flags);
	list_क्रम_each_entry_safe(r_हटाओ, r_हटाओ_next,
				 &rx->rx_submit_list, rx_submit_list) अणु
		अगर (r == r_हटाओ) अणु
			list_del(&r->rx_submit_list);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&rx->submit_lock, flags);
पूर्ण

अटल व्योम gdm_usb_rcv_complete(काष्ठा urb *urb)
अणु
	काष्ठा usb_rx *r = urb->context;
	काष्ठा rx_cxt *rx = r->rx;
	अचिन्हित दीर्घ flags;
	काष्ठा lte_udev *udev = container_of(r->rx, काष्ठा lte_udev, rx);
	काष्ठा usb_device *usbdev = udev->usbdev;

	हटाओ_rx_submit_list(r, rx);

	अगर (!urb->status && r->callback) अणु
		spin_lock_irqsave(&rx->to_host_lock, flags);
		list_add_tail(&r->to_host_list, &rx->to_host_list);
		schedule_work(&udev->work_rx.work);
		spin_unlock_irqrestore(&rx->to_host_lock, flags);
	पूर्ण अन्यथा अणु
		अगर (urb->status && udev->usb_state == PM_NORMAL)
			dev_err(&urb->dev->dev, "%s: urb status error %d\n",
				__func__, urb->status);

		put_rx_काष्ठा(rx, r);
	पूर्ण

	usb_mark_last_busy(usbdev);
पूर्ण

अटल पूर्णांक gdm_usb_recv(व्योम *priv_dev,
			पूर्णांक (*cb)(व्योम *cb_data,
				  व्योम *data, पूर्णांक len, पूर्णांक context),
			व्योम *cb_data,
			पूर्णांक context)
अणु
	काष्ठा lte_udev *udev = priv_dev;
	काष्ठा usb_device *usbdev = udev->usbdev;
	काष्ठा rx_cxt *rx = &udev->rx;
	काष्ठा usb_rx *r;
	पूर्णांक no_spc;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	अगर (!udev->usbdev) अणु
		pr_err("invalid device\n");
		वापस -ENODEV;
	पूर्ण

	r = get_rx_काष्ठा(rx, &no_spc);
	अगर (!r) अणु
		pr_err("Out of Memory\n");
		वापस -ENOMEM;
	पूर्ण

	udev->rx_cb = cb;
	r->callback = cb;
	r->cb_data = cb_data;
	r->index = (व्योम *)udev;
	r->rx = rx;

	usb_fill_bulk_urb(r->urb,
			  usbdev,
			  usb_rcvbulkpipe(usbdev, 0x83),
			  r->buf,
			  RX_BUF_SIZE,
			  gdm_usb_rcv_complete,
			  r);

	spin_lock_irqsave(&rx->submit_lock, flags);
	list_add_tail(&r->rx_submit_list, &rx->rx_submit_list);
	spin_unlock_irqrestore(&rx->submit_lock, flags);

	अगर (context == KERNEL_THREAD)
		ret = usb_submit_urb(r->urb, GFP_KERNEL);
	अन्यथा
		ret = usb_submit_urb(r->urb, GFP_ATOMIC);

	अगर (ret) अणु
		spin_lock_irqsave(&rx->submit_lock, flags);
		list_del(&r->rx_submit_list);
		spin_unlock_irqrestore(&rx->submit_lock, flags);

		pr_err("usb_submit_urb failed (%p)\n", r);
		put_rx_काष्ठा(rx, r);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम gdm_usb_send_complete(काष्ठा urb *urb)
अणु
	काष्ठा usb_tx *t = urb->context;
	काष्ठा tx_cxt *tx = t->tx;
	काष्ठा lte_udev *udev = container_of(tx, काष्ठा lte_udev, tx);
	अचिन्हित दीर्घ flags;

	अगर (urb->status == -ECONNRESET) अणु
		dev_info(&urb->dev->dev, "CONNRESET\n");
		वापस;
	पूर्ण

	अगर (t->callback)
		t->callback(t->cb_data);

	मुक्त_tx_काष्ठा(t);

	spin_lock_irqsave(&tx->lock, flags);
	udev->send_complete = 1;
	schedule_work(&udev->work_tx.work);
	spin_unlock_irqrestore(&tx->lock, flags);
पूर्ण

अटल पूर्णांक send_tx_packet(काष्ठा usb_device *usbdev, काष्ठा usb_tx *t, u32 len)
अणु
	पूर्णांक ret = 0;

	अगर (!(len % 512))
		len++;

	usb_fill_bulk_urb(t->urb,
			  usbdev,
			  usb_sndbulkpipe(usbdev, 2),
			  t->buf,
			  len,
			  gdm_usb_send_complete,
			  t);

	ret = usb_submit_urb(t->urb, GFP_ATOMIC);

	अगर (ret)
		dev_err(&usbdev->dev, "usb_submit_urb failed: %d\n",
			ret);

	usb_mark_last_busy(usbdev);

	वापस ret;
पूर्ण

अटल u32 packet_aggregation(काष्ठा lte_udev *udev, u8 *send_buf)
अणु
	काष्ठा tx_cxt *tx = &udev->tx;
	काष्ठा usb_tx_sdu *t_sdu = शून्य;
	काष्ठा multi_sdu *multi_sdu = (काष्ठा multi_sdu *)send_buf;
	u16 send_len = 0;
	u16 num_packet = 0;
	अचिन्हित दीर्घ flags;

	multi_sdu->cmd_evt = gdm_cpu_to_dev16(udev->gdm_ed, LTE_TX_MULTI_SDU);

	जबतक (num_packet < MAX_PACKET_IN_MULTI_SDU) अणु
		spin_lock_irqsave(&tx->lock, flags);
		अगर (list_empty(&tx->sdu_list)) अणु
			spin_unlock_irqrestore(&tx->lock, flags);
			अवरोध;
		पूर्ण

		t_sdu = list_entry(tx->sdu_list.next, काष्ठा usb_tx_sdu, list);
		अगर (send_len + t_sdu->len > MAX_SDU_SIZE) अणु
			spin_unlock_irqrestore(&tx->lock, flags);
			अवरोध;
		पूर्ण

		list_del(&t_sdu->list);
		spin_unlock_irqrestore(&tx->lock, flags);

		स_नकल(multi_sdu->data + send_len, t_sdu->buf, t_sdu->len);

		send_len += (t_sdu->len + 3) & 0xfffc;
		num_packet++;

		अगर (tx->avail_count > 10)
			t_sdu->callback(t_sdu->cb_data);

		spin_lock_irqsave(&tx->lock, flags);
		put_tx_काष्ठा(tx, t_sdu);
		spin_unlock_irqrestore(&tx->lock, flags);
	पूर्ण

	multi_sdu->len = gdm_cpu_to_dev16(udev->gdm_ed, send_len);
	multi_sdu->num_packet = gdm_cpu_to_dev16(udev->gdm_ed, num_packet);

	वापस send_len + दुरत्व(काष्ठा multi_sdu, data);
पूर्ण

अटल व्योम करो_tx(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा lte_udev *udev =
		container_of(work, काष्ठा lte_udev, work_tx.work);
	काष्ठा usb_device *usbdev = udev->usbdev;
	काष्ठा tx_cxt *tx = &udev->tx;
	काष्ठा usb_tx *t = शून्य;
	पूर्णांक is_send = 0;
	u32 len = 0;
	अचिन्हित दीर्घ flags;

	अगर (!usb_स्वतःpm_get_पूर्णांकerface(udev->पूर्णांकf))
		usb_स्वतःpm_put_पूर्णांकerface(udev->पूर्णांकf);

	अगर (udev->usb_state == PM_SUSPEND)
		वापस;

	spin_lock_irqsave(&tx->lock, flags);
	अगर (!udev->send_complete) अणु
		spin_unlock_irqrestore(&tx->lock, flags);
		वापस;
	पूर्ण
	udev->send_complete = 0;

	अगर (!list_empty(&tx->hci_list)) अणु
		t = list_entry(tx->hci_list.next, काष्ठा usb_tx, list);
		list_del(&t->list);
		len = t->len;
		t->is_sdu = 0;
		is_send = 1;
	पूर्ण अन्यथा अगर (!list_empty(&tx->sdu_list)) अणु
		अगर (udev->tx_stop) अणु
			udev->send_complete = 1;
			spin_unlock_irqrestore(&tx->lock, flags);
			वापस;
		पूर्ण

		t = alloc_tx_काष्ठा(TX_BUF_SIZE);
		अगर (!t) अणु
			spin_unlock_irqrestore(&tx->lock, flags);
			वापस;
		पूर्ण
		t->callback = शून्य;
		t->tx = tx;
		t->is_sdu = 1;
		is_send = 1;
	पूर्ण

	अगर (!is_send) अणु
		udev->send_complete = 1;
		spin_unlock_irqrestore(&tx->lock, flags);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&tx->lock, flags);

	अगर (t->is_sdu)
		len = packet_aggregation(udev, t->buf);

	अगर (send_tx_packet(usbdev, t, len)) अणु
		pr_err("send_tx_packet failed\n");
		t->callback = शून्य;
		gdm_usb_send_complete(t->urb);
	पूर्ण
पूर्ण

#घोषणा SDU_PARAM_LEN 12
अटल पूर्णांक gdm_usb_sdu_send(व्योम *priv_dev, व्योम *data, पूर्णांक len,
			    अचिन्हित पूर्णांक dft_eps_ID, अचिन्हित पूर्णांक eps_ID,
			    व्योम (*cb)(व्योम *data), व्योम *cb_data,
			    पूर्णांक dev_idx, पूर्णांक nic_type)
अणु
	काष्ठा lte_udev *udev = priv_dev;
	काष्ठा tx_cxt *tx = &udev->tx;
	काष्ठा usb_tx_sdu *t_sdu;
	काष्ठा sdu *sdu = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक no_spc = 0;
	u16 send_len;

	अगर (!udev->usbdev) अणु
		pr_err("sdu send - invalid device\n");
		वापस TX_NO_DEV;
	पूर्ण

	spin_lock_irqsave(&tx->lock, flags);
	t_sdu = get_tx_sdu_काष्ठा(tx, &no_spc);
	spin_unlock_irqrestore(&tx->lock, flags);

	अगर (!t_sdu) अणु
		pr_err("sdu send - free list empty\n");
		वापस TX_NO_SPC;
	पूर्ण

	sdu = (काष्ठा sdu *)t_sdu->buf;
	sdu->cmd_evt = gdm_cpu_to_dev16(udev->gdm_ed, LTE_TX_SDU);
	अगर (nic_type == NIC_TYPE_ARP) अणु
		send_len = len + SDU_PARAM_LEN;
		स_नकल(sdu->data, data, len);
	पूर्ण अन्यथा अणु
		send_len = len - ETH_HLEN;
		send_len += SDU_PARAM_LEN;
		स_नकल(sdu->data, data + ETH_HLEN, len - ETH_HLEN);
	पूर्ण

	sdu->len = gdm_cpu_to_dev16(udev->gdm_ed, send_len);
	sdu->dft_eps_ID = gdm_cpu_to_dev32(udev->gdm_ed, dft_eps_ID);
	sdu->bearer_ID = gdm_cpu_to_dev32(udev->gdm_ed, eps_ID);
	sdu->nic_type = gdm_cpu_to_dev32(udev->gdm_ed, nic_type);

	t_sdu->len = send_len + HCI_HEADER_SIZE;
	t_sdu->callback = cb;
	t_sdu->cb_data = cb_data;

	spin_lock_irqsave(&tx->lock, flags);
	list_add_tail(&t_sdu->list, &tx->sdu_list);
	schedule_work(&udev->work_tx.work);
	spin_unlock_irqrestore(&tx->lock, flags);

	अगर (no_spc)
		वापस TX_NO_BUFFER;

	वापस 0;
पूर्ण

अटल पूर्णांक gdm_usb_hci_send(व्योम *priv_dev, व्योम *data, पूर्णांक len,
			    व्योम (*cb)(व्योम *data), व्योम *cb_data)
अणु
	काष्ठा lte_udev *udev = priv_dev;
	काष्ठा tx_cxt *tx = &udev->tx;
	काष्ठा usb_tx *t;
	अचिन्हित दीर्घ flags;

	अगर (!udev->usbdev) अणु
		pr_err("hci send - invalid device\n");
		वापस -ENODEV;
	पूर्ण

	t = alloc_tx_काष्ठा(len);
	अगर (!t) अणु
		pr_err("hci_send - out of memory\n");
		वापस -ENOMEM;
	पूर्ण

	स_नकल(t->buf, data, len);
	t->callback = cb;
	t->cb_data = cb_data;
	t->len = len;
	t->tx = tx;
	t->is_sdu = 0;

	spin_lock_irqsave(&tx->lock, flags);
	list_add_tail(&t->list, &tx->hci_list);
	schedule_work(&udev->work_tx.work);
	spin_unlock_irqrestore(&tx->lock, flags);

	वापस 0;
पूर्ण

अटल u8 gdm_usb_get_endian(व्योम *priv_dev)
अणु
	काष्ठा lte_udev *udev = priv_dev;

	वापस udev->gdm_ed;
पूर्ण

अटल पूर्णांक gdm_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	पूर्णांक ret = 0;
	काष्ठा phy_dev *phy_dev = शून्य;
	काष्ठा lte_udev *udev = शून्य;
	u16 idVenकरोr, idProduct;
	पूर्णांक bInterfaceNumber;
	काष्ठा usb_device *usbdev = पूर्णांकerface_to_usbdev(पूर्णांकf);

	bInterfaceNumber = पूर्णांकf->cur_altsetting->desc.bInterfaceNumber;
	idVenकरोr = __le16_to_cpu(usbdev->descriptor.idVenकरोr);
	idProduct = __le16_to_cpu(usbdev->descriptor.idProduct);

	pr_info("net vid = 0x%04x pid = 0x%04x\n", idVenकरोr, idProduct);

	अगर (bInterfaceNumber > NETWORK_INTERFACE) अणु
		pr_info("not a network device\n");
		वापस -ENODEV;
	पूर्ण

	phy_dev = kzalloc(माप(*phy_dev), GFP_KERNEL);
	अगर (!phy_dev)
		वापस -ENOMEM;

	udev = kzalloc(माप(*udev), GFP_KERNEL);
	अगर (!udev) अणु
		ret = -ENOMEM;
		जाओ err_udev;
	पूर्ण

	phy_dev->priv_dev = (व्योम *)udev;
	phy_dev->send_hci_func = gdm_usb_hci_send;
	phy_dev->send_sdu_func = gdm_usb_sdu_send;
	phy_dev->rcv_func = gdm_usb_recv;
	phy_dev->get_endian = gdm_usb_get_endian;

	udev->usbdev = usbdev;
	ret = init_usb(udev);
	अगर (ret < 0) अणु
		dev_err(पूर्णांकf->usb_dev, "init_usb func failed\n");
		जाओ err_init_usb;
	पूर्ण
	udev->पूर्णांकf = पूर्णांकf;

	पूर्णांकf->needs_remote_wakeup = 1;
	usb_enable_स्वतःsuspend(usbdev);
	pm_runसमय_set_स्वतःsuspend_delay(&usbdev->dev, AUTO_SUSPEND_TIMER);

	/* List up hosts with big endians, otherwise,
	 * शेषs to little endian
	 */
	अगर (idProduct == PID_GDM7243)
		udev->gdm_ed = ENDIANNESS_BIG;
	अन्यथा
		udev->gdm_ed = ENDIANNESS_LITTLE;

	ret = request_mac_address(udev);
	अगर (ret < 0) अणु
		dev_err(पूर्णांकf->usb_dev, "request Mac address failed\n");
		जाओ err_mac_address;
	पूर्ण

	start_rx_proc(phy_dev);
	usb_get_dev(usbdev);
	usb_set_पूर्णांकfdata(पूर्णांकf, phy_dev);

	वापस 0;

err_mac_address:
	release_usb(udev);
err_init_usb:
	kमुक्त(udev);
err_udev:
	kमुक्त(phy_dev);

	वापस ret;
पूर्ण

अटल व्योम gdm_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा phy_dev *phy_dev;
	काष्ठा lte_udev *udev;
	काष्ठा usb_device *usbdev;

	usbdev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	phy_dev = usb_get_पूर्णांकfdata(पूर्णांकf);

	udev = phy_dev->priv_dev;
	unरेजिस्टर_lte_device(phy_dev);

	release_usb(udev);

	kमुक्त(udev);
	udev = शून्य;

	kमुक्त(phy_dev);
	phy_dev = शून्य;

	usb_put_dev(usbdev);
पूर्ण

अटल पूर्णांक gdm_usb_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t pm_msg)
अणु
	काष्ठा phy_dev *phy_dev;
	काष्ठा lte_udev *udev;
	काष्ठा rx_cxt *rx;
	काष्ठा usb_rx *r;
	काष्ठा usb_rx *r_next;
	अचिन्हित दीर्घ flags;

	phy_dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	udev = phy_dev->priv_dev;
	rx = &udev->rx;
	अगर (udev->usb_state != PM_NORMAL) अणु
		dev_err(पूर्णांकf->usb_dev, "usb suspend - invalid state\n");
		वापस -1;
	पूर्ण

	udev->usb_state = PM_SUSPEND;

	spin_lock_irqsave(&rx->submit_lock, flags);
	list_क्रम_each_entry_safe(r, r_next, &rx->rx_submit_list,
				 rx_submit_list) अणु
		spin_unlock_irqrestore(&rx->submit_lock, flags);
		usb_समाप्त_urb(r->urb);
		spin_lock_irqsave(&rx->submit_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&rx->submit_lock, flags);

	cancel_work_sync(&udev->work_tx.work);
	cancel_work_sync(&udev->work_rx.work);

	वापस 0;
पूर्ण

अटल पूर्णांक gdm_usb_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा phy_dev *phy_dev;
	काष्ठा lte_udev *udev;
	काष्ठा tx_cxt *tx;
	काष्ठा rx_cxt *rx;
	अचिन्हित दीर्घ flags;
	पूर्णांक issue_count;
	पूर्णांक i;

	phy_dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	udev = phy_dev->priv_dev;
	rx = &udev->rx;

	अगर (udev->usb_state != PM_SUSPEND) अणु
		dev_err(पूर्णांकf->usb_dev, "usb resume - invalid state\n");
		वापस -1;
	पूर्ण
	udev->usb_state = PM_NORMAL;

	spin_lock_irqsave(&rx->rx_lock, flags);
	issue_count = rx->avail_count - MAX_RX_SUBMIT_COUNT;
	spin_unlock_irqrestore(&rx->rx_lock, flags);

	अगर (issue_count >= 0) अणु
		क्रम (i = 0; i < issue_count; i++)
			gdm_usb_recv(phy_dev->priv_dev,
				     udev->rx_cb,
				     phy_dev,
				     USB_COMPLETE);
	पूर्ण

	tx = &udev->tx;
	spin_lock_irqsave(&tx->lock, flags);
	schedule_work(&udev->work_tx.work);
	spin_unlock_irqrestore(&tx->lock, flags);

	वापस 0;
पूर्ण

अटल काष्ठा usb_driver gdm_usb_lte_driver = अणु
	.name = "gdm_lte",
	.probe = gdm_usb_probe,
	.disconnect = gdm_usb_disconnect,
	.id_table = id_table,
	.supports_स्वतःsuspend = 1,
	.suspend = gdm_usb_suspend,
	.resume = gdm_usb_resume,
	.reset_resume = gdm_usb_resume,
पूर्ण;

अटल पूर्णांक __init gdm_usb_lte_init(व्योम)
अणु
	अगर (gdm_lte_event_init() < 0) अणु
		pr_err("error creating event\n");
		वापस -1;
	पूर्ण

	वापस usb_रेजिस्टर(&gdm_usb_lte_driver);
पूर्ण

अटल व्योम __निकास gdm_usb_lte_निकास(व्योम)
अणु
	gdm_lte_event_निकास();

	usb_deरेजिस्टर(&gdm_usb_lte_driver);
पूर्ण

module_init(gdm_usb_lte_init);
module_निकास(gdm_usb_lte_निकास);

MODULE_VERSION(DRIVER_VERSION);
MODULE_DESCRIPTION("GCT LTE USB Device Driver");
MODULE_LICENSE("GPL");
