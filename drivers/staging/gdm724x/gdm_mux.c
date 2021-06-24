<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2012 GCT Semiconductor, Inc. All rights reserved. */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/usb.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb/cdc.h>

#समावेश "gdm_mux.h"

अटल u16 packet_type_क्रम_tty_index[TTY_MAX_COUNT] = अणु0xF011, 0xF010पूर्ण;

#घोषणा USB_DEVICE_CDC_DATA(vid, pid) \
	.match_flags = \
		USB_DEVICE_ID_MATCH_DEVICE |\
		USB_DEVICE_ID_MATCH_INT_CLASS |\
		USB_DEVICE_ID_MATCH_INT_SUBCLASS,\
	.idVenकरोr = vid,\
	.idProduct = pid,\
	.bInterfaceClass = USB_CLASS_COMM,\
	.bInterfaceSubClass = USB_CDC_SUBCLASS_ACM

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु USB_DEVICE_CDC_DATA(0x1076, 0x8000) पूर्ण, /* GCT GDM7240 */
	अणु USB_DEVICE_CDC_DATA(0x1076, 0x8f00) पूर्ण, /* GCT GDM7243 */
	अणु USB_DEVICE_CDC_DATA(0x1076, 0x9000) पूर्ण, /* GCT GDM7243 */
	अणु USB_DEVICE_CDC_DATA(0x1d74, 0x2300) पूर्ण, /* LGIT Phoenix */
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, id_table);

अटल पूर्णांक packet_type_to_tty_index(u16 packet_type)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < TTY_MAX_COUNT; i++) अणु
		अगर (packet_type_क्रम_tty_index[i] == packet_type)
			वापस i;
	पूर्ण

	वापस -1;
पूर्ण

अटल काष्ठा mux_tx *alloc_mux_tx(पूर्णांक len)
अणु
	काष्ठा mux_tx *t;

	t = kzalloc(माप(*t), GFP_ATOMIC);
	अगर (!t)
		वापस शून्य;

	t->urb = usb_alloc_urb(0, GFP_ATOMIC);
	t->buf = kदो_स्मृति(MUX_TX_MAX_SIZE, GFP_ATOMIC);
	अगर (!t->urb || !t->buf) अणु
		usb_मुक्त_urb(t->urb);
		kमुक्त(t->buf);
		kमुक्त(t);
		वापस शून्य;
	पूर्ण

	वापस t;
पूर्ण

अटल व्योम मुक्त_mux_tx(काष्ठा mux_tx *t)
अणु
	अगर (t) अणु
		usb_मुक्त_urb(t->urb);
		kमुक्त(t->buf);
		kमुक्त(t);
	पूर्ण
पूर्ण

अटल काष्ठा mux_rx *alloc_mux_rx(व्योम)
अणु
	काष्ठा mux_rx *r;

	r = kzalloc(माप(*r), GFP_KERNEL);
	अगर (!r)
		वापस शून्य;

	r->urb = usb_alloc_urb(0, GFP_KERNEL);
	r->buf = kदो_स्मृति(MUX_RX_MAX_SIZE, GFP_KERNEL);
	अगर (!r->urb || !r->buf) अणु
		usb_मुक्त_urb(r->urb);
		kमुक्त(r->buf);
		kमुक्त(r);
		वापस शून्य;
	पूर्ण

	वापस r;
पूर्ण

अटल व्योम मुक्त_mux_rx(काष्ठा mux_rx *r)
अणु
	अगर (r) अणु
		usb_मुक्त_urb(r->urb);
		kमुक्त(r->buf);
		kमुक्त(r);
	पूर्ण
पूर्ण

अटल काष्ठा mux_rx *get_rx_काष्ठा(काष्ठा rx_cxt *rx)
अणु
	काष्ठा mux_rx *r;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rx->मुक्त_list_lock, flags);

	अगर (list_empty(&rx->rx_मुक्त_list)) अणु
		spin_unlock_irqrestore(&rx->मुक्त_list_lock, flags);
		वापस शून्य;
	पूर्ण

	r = list_entry(rx->rx_मुक्त_list.prev, काष्ठा mux_rx, मुक्त_list);
	list_del(&r->मुक्त_list);

	spin_unlock_irqrestore(&rx->मुक्त_list_lock, flags);

	वापस r;
पूर्ण

अटल व्योम put_rx_काष्ठा(काष्ठा rx_cxt *rx, काष्ठा mux_rx *r)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rx->मुक्त_list_lock, flags);
	list_add_tail(&r->मुक्त_list, &rx->rx_मुक्त_list);
	spin_unlock_irqrestore(&rx->मुक्त_list_lock, flags);
पूर्ण

अटल पूर्णांक up_to_host(काष्ठा mux_rx *r)
अणु
	काष्ठा mux_dev *mux_dev = r->mux_dev;
	काष्ठा mux_pkt_header *mux_header;
	अचिन्हित पूर्णांक start_flag;
	अचिन्हित पूर्णांक payload_size;
	अचिन्हित लघु packet_type;
	पूर्णांक total_len;
	u32 packet_size_sum = r->offset;
	पूर्णांक index;
	पूर्णांक ret = TO_HOST_INVALID_PACKET;
	पूर्णांक len = r->len;

	जबतक (1) अणु
		mux_header = (काष्ठा mux_pkt_header *)(r->buf +
						       packet_size_sum);
		start_flag = __le32_to_cpu(mux_header->start_flag);
		payload_size = __le32_to_cpu(mux_header->payload_size);
		packet_type = __le16_to_cpu(mux_header->packet_type);

		अगर (start_flag != START_FLAG) अणु
			pr_err("invalid START_FLAG %x\n", start_flag);
			अवरोध;
		पूर्ण

		total_len = ALIGN(MUX_HEADER_SIZE + payload_size, 4);

		अगर (len - packet_size_sum < total_len) अणु
			pr_err("invalid payload : %d %d %04x\n",
			       payload_size, len, packet_type);
			अवरोध;
		पूर्ण

		index = packet_type_to_tty_index(packet_type);
		अगर (index < 0) अणु
			pr_err("invalid index %d\n", index);
			अवरोध;
		पूर्ण

		ret = r->callback(mux_header->data,
				payload_size,
				index,
				mux_dev->tty_dev,
				RECV_PACKET_PROCESS_CONTINUE
				);
		अगर (ret == TO_HOST_BUFFER_REQUEST_FAIL) अणु
			r->offset += packet_size_sum;
			अवरोध;
		पूर्ण

		packet_size_sum += total_len;
		अगर (len - packet_size_sum <= MUX_HEADER_SIZE + 2) अणु
			ret = r->callback(शून्य,
					0,
					index,
					mux_dev->tty_dev,
					RECV_PACKET_PROCESS_COMPLETE
					);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम करो_rx(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mux_dev *mux_dev =
		container_of(work, काष्ठा mux_dev, work_rx.work);
	काष्ठा mux_rx *r;
	काष्ठा rx_cxt *rx = &mux_dev->rx;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	जबतक (1) अणु
		spin_lock_irqsave(&rx->to_host_lock, flags);
		अगर (list_empty(&rx->to_host_list)) अणु
			spin_unlock_irqrestore(&rx->to_host_lock, flags);
			अवरोध;
		पूर्ण
		r = list_entry(rx->to_host_list.next, काष्ठा mux_rx,
			       to_host_list);
		list_del(&r->to_host_list);
		spin_unlock_irqrestore(&rx->to_host_lock, flags);

		ret = up_to_host(r);
		अगर (ret == TO_HOST_BUFFER_REQUEST_FAIL)
			pr_err("failed to send mux data to host\n");
		अन्यथा
			put_rx_काष्ठा(rx, r);
	पूर्ण
पूर्ण

अटल व्योम हटाओ_rx_submit_list(काष्ठा mux_rx *r, काष्ठा rx_cxt *rx)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा mux_rx	*r_हटाओ, *r_हटाओ_next;

	spin_lock_irqsave(&rx->submit_list_lock, flags);
	list_क्रम_each_entry_safe(r_हटाओ, r_हटाओ_next, &rx->rx_submit_list,
				 rx_submit_list) अणु
		अगर (r == r_हटाओ)
			list_del(&r->rx_submit_list);
	पूर्ण
	spin_unlock_irqrestore(&rx->submit_list_lock, flags);
पूर्ण

अटल व्योम gdm_mux_rcv_complete(काष्ठा urb *urb)
अणु
	काष्ठा mux_rx *r = urb->context;
	काष्ठा mux_dev *mux_dev = r->mux_dev;
	काष्ठा rx_cxt *rx = &mux_dev->rx;
	अचिन्हित दीर्घ flags;

	हटाओ_rx_submit_list(r, rx);

	अगर (urb->status) अणु
		अगर (mux_dev->usb_state == PM_NORMAL)
			dev_err(&urb->dev->dev, "%s: urb status error %d\n",
				__func__, urb->status);
		put_rx_काष्ठा(rx, r);
	पूर्ण अन्यथा अणु
		r->len = r->urb->actual_length;
		spin_lock_irqsave(&rx->to_host_lock, flags);
		list_add_tail(&r->to_host_list, &rx->to_host_list);
		schedule_work(&mux_dev->work_rx.work);
		spin_unlock_irqrestore(&rx->to_host_lock, flags);
	पूर्ण
पूर्ण

अटल पूर्णांक gdm_mux_recv(व्योम *priv_dev,
			पूर्णांक (*cb)(व्योम *data, पूर्णांक len, पूर्णांक tty_index,
				  काष्ठा tty_dev *tty_dev, पूर्णांक complete))
अणु
	काष्ठा mux_dev *mux_dev = priv_dev;
	काष्ठा usb_device *usbdev = mux_dev->usbdev;
	काष्ठा mux_rx *r;
	काष्ठा rx_cxt *rx = &mux_dev->rx;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (!usbdev) अणु
		pr_err("device is disconnected\n");
		वापस -ENODEV;
	पूर्ण

	r = get_rx_काष्ठा(rx);
	अगर (!r) अणु
		pr_err("get_rx_struct fail\n");
		वापस -ENOMEM;
	पूर्ण

	r->offset = 0;
	r->mux_dev = (व्योम *)mux_dev;
	r->callback = cb;
	mux_dev->rx_cb = cb;

	usb_fill_bulk_urb(r->urb,
			  usbdev,
			  usb_rcvbulkpipe(usbdev, 0x86),
			  r->buf,
			  MUX_RX_MAX_SIZE,
			  gdm_mux_rcv_complete,
			  r);

	spin_lock_irqsave(&rx->submit_list_lock, flags);
	list_add_tail(&r->rx_submit_list, &rx->rx_submit_list);
	spin_unlock_irqrestore(&rx->submit_list_lock, flags);

	ret = usb_submit_urb(r->urb, GFP_KERNEL);

	अगर (ret) अणु
		spin_lock_irqsave(&rx->submit_list_lock, flags);
		list_del(&r->rx_submit_list);
		spin_unlock_irqrestore(&rx->submit_list_lock, flags);

		put_rx_काष्ठा(rx, r);

		pr_err("usb_submit_urb ret=%d\n", ret);
	पूर्ण

	usb_mark_last_busy(usbdev);

	वापस ret;
पूर्ण

अटल व्योम gdm_mux_send_complete(काष्ठा urb *urb)
अणु
	काष्ठा mux_tx *t = urb->context;

	अगर (urb->status == -ECONNRESET) अणु
		dev_info(&urb->dev->dev, "CONNRESET\n");
		मुक्त_mux_tx(t);
		वापस;
	पूर्ण

	अगर (t->callback)
		t->callback(t->cb_data);

	मुक्त_mux_tx(t);
पूर्ण

अटल पूर्णांक gdm_mux_send(व्योम *priv_dev, व्योम *data, पूर्णांक len, पूर्णांक tty_index,
			व्योम (*cb)(व्योम *data), व्योम *cb_data)
अणु
	काष्ठा mux_dev *mux_dev = priv_dev;
	काष्ठा usb_device *usbdev = mux_dev->usbdev;
	काष्ठा mux_pkt_header *mux_header;
	काष्ठा mux_tx *t = शून्य;
	अटल u32 seq_num = 1;
	पूर्णांक total_len;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	अगर (mux_dev->usb_state == PM_SUSPEND) अणु
		ret = usb_स्वतःpm_get_पूर्णांकerface(mux_dev->पूर्णांकf);
		अगर (!ret)
			usb_स्वतःpm_put_पूर्णांकerface(mux_dev->पूर्णांकf);
	पूर्ण

	spin_lock_irqsave(&mux_dev->ग_लिखो_lock, flags);

	total_len = ALIGN(MUX_HEADER_SIZE + len, 4);

	t = alloc_mux_tx(total_len);
	अगर (!t) अणु
		pr_err("alloc_mux_tx fail\n");
		spin_unlock_irqrestore(&mux_dev->ग_लिखो_lock, flags);
		वापस -ENOMEM;
	पूर्ण

	mux_header = (काष्ठा mux_pkt_header *)t->buf;
	mux_header->start_flag = __cpu_to_le32(START_FLAG);
	mux_header->seq_num = __cpu_to_le32(seq_num++);
	mux_header->payload_size = __cpu_to_le32((u32)len);
	mux_header->packet_type = __cpu_to_le16(packet_type_क्रम_tty_index[tty_index]);

	स_नकल(t->buf + MUX_HEADER_SIZE, data, len);
	स_रखो(t->buf + MUX_HEADER_SIZE + len, 0,
	       total_len - MUX_HEADER_SIZE - len);

	t->len = total_len;
	t->callback = cb;
	t->cb_data = cb_data;

	usb_fill_bulk_urb(t->urb,
			  usbdev,
			  usb_sndbulkpipe(usbdev, 5),
			  t->buf,
			  total_len,
			  gdm_mux_send_complete,
			  t);

	ret = usb_submit_urb(t->urb, GFP_ATOMIC);

	spin_unlock_irqrestore(&mux_dev->ग_लिखो_lock, flags);

	अगर (ret)
		pr_err("usb_submit_urb Error: %d\n", ret);

	usb_mark_last_busy(usbdev);

	वापस ret;
पूर्ण

अटल पूर्णांक gdm_mux_send_control(व्योम *priv_dev, पूर्णांक request, पूर्णांक value,
				व्योम *buf, पूर्णांक len)
अणु
	काष्ठा mux_dev *mux_dev = priv_dev;
	काष्ठा usb_device *usbdev = mux_dev->usbdev;
	पूर्णांक ret;

	ret = usb_control_msg(usbdev,
			      usb_sndctrlpipe(usbdev, 0),
			      request,
			      USB_RT_ACM,
			      value,
			      2,
			      buf,
			      len,
			      5000
			     );

	अगर (ret < 0)
		pr_err("usb_control_msg error: %d\n", ret);

	वापस min(ret, 0);
पूर्ण

अटल व्योम release_usb(काष्ठा mux_dev *mux_dev)
अणु
	काष्ठा rx_cxt		*rx = &mux_dev->rx;
	काष्ठा mux_rx		*r, *r_next;
	अचिन्हित दीर्घ		flags;

	cancel_delayed_work(&mux_dev->work_rx);

	spin_lock_irqsave(&rx->submit_list_lock, flags);
	list_क्रम_each_entry_safe(r, r_next, &rx->rx_submit_list,
				 rx_submit_list) अणु
		spin_unlock_irqrestore(&rx->submit_list_lock, flags);
		usb_समाप्त_urb(r->urb);
		spin_lock_irqsave(&rx->submit_list_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&rx->submit_list_lock, flags);

	spin_lock_irqsave(&rx->मुक्त_list_lock, flags);
	list_क्रम_each_entry_safe(r, r_next, &rx->rx_मुक्त_list, मुक्त_list) अणु
		list_del(&r->मुक्त_list);
		मुक्त_mux_rx(r);
	पूर्ण
	spin_unlock_irqrestore(&rx->मुक्त_list_lock, flags);

	spin_lock_irqsave(&rx->to_host_lock, flags);
	list_क्रम_each_entry_safe(r, r_next, &rx->to_host_list, to_host_list) अणु
		अगर (r->mux_dev == (व्योम *)mux_dev) अणु
			list_del(&r->to_host_list);
			मुक्त_mux_rx(r);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&rx->to_host_lock, flags);
पूर्ण

अटल पूर्णांक init_usb(काष्ठा mux_dev *mux_dev)
अणु
	काष्ठा mux_rx *r;
	काष्ठा rx_cxt *rx = &mux_dev->rx;
	पूर्णांक ret = 0;
	पूर्णांक i;

	spin_lock_init(&mux_dev->ग_लिखो_lock);
	INIT_LIST_HEAD(&rx->to_host_list);
	INIT_LIST_HEAD(&rx->rx_submit_list);
	INIT_LIST_HEAD(&rx->rx_मुक्त_list);
	spin_lock_init(&rx->to_host_lock);
	spin_lock_init(&rx->submit_list_lock);
	spin_lock_init(&rx->मुक्त_list_lock);

	क्रम (i = 0; i < MAX_ISSUE_NUM * 2; i++) अणु
		r = alloc_mux_rx();
		अगर (!r) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण

		list_add(&r->मुक्त_list, &rx->rx_मुक्त_list);
	पूर्ण

	INIT_DELAYED_WORK(&mux_dev->work_rx, करो_rx);

	वापस ret;
पूर्ण

अटल पूर्णांक gdm_mux_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा mux_dev *mux_dev;
	काष्ठा tty_dev *tty_dev;
	u16 idVenकरोr, idProduct;
	पूर्णांक bInterfaceNumber;
	पूर्णांक ret;
	पूर्णांक i;
	काष्ठा usb_device *usbdev = पूर्णांकerface_to_usbdev(पूर्णांकf);

	bInterfaceNumber = पूर्णांकf->cur_altsetting->desc.bInterfaceNumber;

	idVenकरोr = __le16_to_cpu(usbdev->descriptor.idVenकरोr);
	idProduct = __le16_to_cpu(usbdev->descriptor.idProduct);

	pr_info("mux vid = 0x%04x pid = 0x%04x\n", idVenकरोr, idProduct);

	अगर (bInterfaceNumber != 2)
		वापस -ENODEV;

	mux_dev = kzalloc(माप(*mux_dev), GFP_KERNEL);
	अगर (!mux_dev)
		वापस -ENOMEM;

	tty_dev = kzalloc(माप(*tty_dev), GFP_KERNEL);
	अगर (!tty_dev) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_mux;
	पूर्ण

	mux_dev->usbdev = usbdev;
	mux_dev->control_पूर्णांकf = पूर्णांकf;

	ret = init_usb(mux_dev);
	अगर (ret)
		जाओ err_मुक्त_usb;

	tty_dev->priv_dev = (व्योम *)mux_dev;
	tty_dev->send_func = gdm_mux_send;
	tty_dev->recv_func = gdm_mux_recv;
	tty_dev->send_control = gdm_mux_send_control;

	ret = रेजिस्टर_lte_tty_device(tty_dev, &पूर्णांकf->dev);
	अगर (ret)
		जाओ err_unरेजिस्टर_tty;

	क्रम (i = 0; i < TTY_MAX_COUNT; i++)
		mux_dev->tty_dev = tty_dev;

	mux_dev->पूर्णांकf = पूर्णांकf;
	mux_dev->usb_state = PM_NORMAL;

	usb_get_dev(usbdev);
	usb_set_पूर्णांकfdata(पूर्णांकf, tty_dev);

	वापस 0;

err_unरेजिस्टर_tty:
	unरेजिस्टर_lte_tty_device(tty_dev);
err_मुक्त_usb:
	release_usb(mux_dev);
	kमुक्त(tty_dev);
err_मुक्त_mux:
	kमुक्त(mux_dev);

	वापस ret;
पूर्ण

अटल व्योम gdm_mux_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा tty_dev *tty_dev;
	काष्ठा mux_dev *mux_dev;
	काष्ठा usb_device *usbdev = पूर्णांकerface_to_usbdev(पूर्णांकf);

	tty_dev = usb_get_पूर्णांकfdata(पूर्णांकf);

	mux_dev = tty_dev->priv_dev;

	release_usb(mux_dev);
	unरेजिस्टर_lte_tty_device(tty_dev);

	kमुक्त(mux_dev);
	kमुक्त(tty_dev);

	usb_put_dev(usbdev);
पूर्ण

अटल पूर्णांक gdm_mux_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t pm_msg)
अणु
	काष्ठा tty_dev *tty_dev;
	काष्ठा mux_dev *mux_dev;
	काष्ठा rx_cxt *rx;
	काष्ठा mux_rx *r, *r_next;
	अचिन्हित दीर्घ flags;

	tty_dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	mux_dev = tty_dev->priv_dev;
	rx = &mux_dev->rx;

	cancel_work_sync(&mux_dev->work_rx.work);

	अगर (mux_dev->usb_state != PM_NORMAL) अणु
		dev_err(पूर्णांकf->usb_dev, "usb suspend - invalid state\n");
		वापस -1;
	पूर्ण

	mux_dev->usb_state = PM_SUSPEND;

	spin_lock_irqsave(&rx->submit_list_lock, flags);
	list_क्रम_each_entry_safe(r, r_next, &rx->rx_submit_list,
				 rx_submit_list) अणु
		spin_unlock_irqrestore(&rx->submit_list_lock, flags);
		usb_समाप्त_urb(r->urb);
		spin_lock_irqsave(&rx->submit_list_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&rx->submit_list_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक gdm_mux_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा tty_dev *tty_dev;
	काष्ठा mux_dev *mux_dev;
	u8 i;

	tty_dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	mux_dev = tty_dev->priv_dev;

	अगर (mux_dev->usb_state != PM_SUSPEND) अणु
		dev_err(पूर्णांकf->usb_dev, "usb resume - invalid state\n");
		वापस -1;
	पूर्ण

	mux_dev->usb_state = PM_NORMAL;

	क्रम (i = 0; i < MAX_ISSUE_NUM; i++)
		gdm_mux_recv(mux_dev, mux_dev->rx_cb);

	वापस 0;
पूर्ण

अटल काष्ठा usb_driver gdm_mux_driver = अणु
	.name = "gdm_mux",
	.probe = gdm_mux_probe,
	.disconnect = gdm_mux_disconnect,
	.id_table = id_table,
	.supports_स्वतःsuspend = 1,
	.suspend = gdm_mux_suspend,
	.resume = gdm_mux_resume,
	.reset_resume = gdm_mux_resume,
पूर्ण;

अटल पूर्णांक __init gdm_usb_mux_init(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_lte_tty_driver();
	अगर (ret)
		वापस ret;

	वापस usb_रेजिस्टर(&gdm_mux_driver);
पूर्ण

अटल व्योम __निकास gdm_usb_mux_निकास(व्योम)
अणु
	usb_deरेजिस्टर(&gdm_mux_driver);
	unरेजिस्टर_lte_tty_driver();
पूर्ण

module_init(gdm_usb_mux_init);
module_निकास(gdm_usb_mux_निकास);

MODULE_DESCRIPTION("GCT LTE TTY Device Driver");
MODULE_LICENSE("GPL");
