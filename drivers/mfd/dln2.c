<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम the Diolan DLN-2 USB adapter
 *
 * Copyright (c) 2014 Intel Corporation
 *
 * Derived from:
 *  i2c-diolan-u2c.c
 *  Copyright (c) 2010-2011 Ericsson AB
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/dln2.h>
#समावेश <linux/rculist.h>

काष्ठा dln2_header अणु
	__le16 size;
	__le16 id;
	__le16 echo;
	__le16 handle;
पूर्ण;

काष्ठा dln2_response अणु
	काष्ठा dln2_header hdr;
	__le16 result;
पूर्ण;

#घोषणा DLN2_GENERIC_MODULE_ID		0x00
#घोषणा DLN2_GENERIC_CMD(cmd)		DLN2_CMD(cmd, DLN2_GENERIC_MODULE_ID)
#घोषणा CMD_GET_DEVICE_VER		DLN2_GENERIC_CMD(0x30)
#घोषणा CMD_GET_DEVICE_SN		DLN2_GENERIC_CMD(0x31)

#घोषणा DLN2_HW_ID			0x200
#घोषणा DLN2_USB_TIMEOUT		200	/* in ms */
#घोषणा DLN2_MAX_RX_SLOTS		16
#घोषणा DLN2_MAX_URBS			16
#घोषणा DLN2_RX_BUF_SIZE		512

क्रमागत dln2_handle अणु
	DLN2_HANDLE_EVENT = 0,		/* करोn't change, hardware defined */
	DLN2_HANDLE_CTRL,
	DLN2_HANDLE_GPIO,
	DLN2_HANDLE_I2C,
	DLN2_HANDLE_SPI,
	DLN2_HANDLES
पूर्ण;

/*
 * Receive context used between the receive demultiplexer and the transfer
 * routine. While sending a request the transfer routine will look क्रम a मुक्त
 * receive context and use it to रुको क्रम a response and to receive the URB and
 * thus the response data.
 */
काष्ठा dln2_rx_context अणु
	/* completion used to रुको क्रम a response */
	काष्ठा completion करोne;

	/* अगर non-शून्य the URB contains the response */
	काष्ठा urb *urb;

	/* अगर true then this context is used to रुको क्रम a response */
	bool in_use;
पूर्ण;

/*
 * Receive contexts क्रम a particular DLN2 module (i2c, gpio, etc.). We use the
 * handle header field to identअगरy the module in dln2_dev.mod_rx_slots and then
 * the echo header field to index the slots field and find the receive context
 * क्रम a particular request.
 */
काष्ठा dln2_mod_rx_slots अणु
	/* RX slots biपंचांगap */
	DECLARE_BITMAP(bmap, DLN2_MAX_RX_SLOTS);

	/* used to रुको क्रम a मुक्त RX slot */
	रुको_queue_head_t wq;

	/* used to रुको क्रम an RX operation to complete */
	काष्ठा dln2_rx_context slots[DLN2_MAX_RX_SLOTS];

	/* aव्योम races between alloc/मुक्त_rx_slot and dln2_rx_transfer */
	spinlock_t lock;
पूर्ण;

क्रमागत dln2_endpoपूर्णांक अणु
	DLN2_EP_OUT	= 0,
	DLN2_EP_IN	= 1,
पूर्ण;

काष्ठा dln2_dev अणु
	काष्ठा usb_device *usb_dev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface;
	u8 ep_in;
	u8 ep_out;

	काष्ठा urb *rx_urb[DLN2_MAX_URBS];
	व्योम *rx_buf[DLN2_MAX_URBS];

	काष्ठा dln2_mod_rx_slots mod_rx_slots[DLN2_HANDLES];

	काष्ठा list_head event_cb_list;
	spinlock_t event_cb_lock;

	bool disconnect;
	पूर्णांक active_transfers;
	रुको_queue_head_t disconnect_wq;
	spinlock_t disconnect_lock;
पूर्ण;

काष्ठा dln2_event_cb_entry अणु
	काष्ठा list_head list;
	u16 id;
	काष्ठा platक्रमm_device *pdev;
	dln2_event_cb_t callback;
पूर्ण;

पूर्णांक dln2_रेजिस्टर_event_cb(काष्ठा platक्रमm_device *pdev, u16 id,
			   dln2_event_cb_t event_cb)
अणु
	काष्ठा dln2_dev *dln2 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा dln2_event_cb_entry *i, *entry;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	entry->id = id;
	entry->callback = event_cb;
	entry->pdev = pdev;

	spin_lock_irqsave(&dln2->event_cb_lock, flags);

	list_क्रम_each_entry(i, &dln2->event_cb_list, list) अणु
		अगर (i->id == id) अणु
			ret = -EBUSY;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!ret)
		list_add_rcu(&entry->list, &dln2->event_cb_list);

	spin_unlock_irqrestore(&dln2->event_cb_lock, flags);

	अगर (ret)
		kमुक्त(entry);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(dln2_रेजिस्टर_event_cb);

व्योम dln2_unरेजिस्टर_event_cb(काष्ठा platक्रमm_device *pdev, u16 id)
अणु
	काष्ठा dln2_dev *dln2 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा dln2_event_cb_entry *i;
	अचिन्हित दीर्घ flags;
	bool found = false;

	spin_lock_irqsave(&dln2->event_cb_lock, flags);

	list_क्रम_each_entry(i, &dln2->event_cb_list, list) अणु
		अगर (i->id == id) अणु
			list_del_rcu(&i->list);
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&dln2->event_cb_lock, flags);

	अगर (found) अणु
		synchronize_rcu();
		kमुक्त(i);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(dln2_unरेजिस्टर_event_cb);

/*
 * Returns true अगर a valid transfer slot is found. In this हाल the URB must not
 * be resubmitted immediately in dln2_rx as we need the data when dln2_transfer
 * is woke up. It will be resubmitted there.
 */
अटल bool dln2_transfer_complete(काष्ठा dln2_dev *dln2, काष्ठा urb *urb,
				   u16 handle, u16 rx_slot)
अणु
	काष्ठा device *dev = &dln2->पूर्णांकerface->dev;
	काष्ठा dln2_mod_rx_slots *rxs = &dln2->mod_rx_slots[handle];
	काष्ठा dln2_rx_context *rxc;
	अचिन्हित दीर्घ flags;
	bool valid_slot = false;

	अगर (rx_slot >= DLN2_MAX_RX_SLOTS)
		जाओ out;

	rxc = &rxs->slots[rx_slot];

	spin_lock_irqsave(&rxs->lock, flags);
	अगर (rxc->in_use && !rxc->urb) अणु
		rxc->urb = urb;
		complete(&rxc->करोne);
		valid_slot = true;
	पूर्ण
	spin_unlock_irqrestore(&rxs->lock, flags);

out:
	अगर (!valid_slot)
		dev_warn(dev, "bad/late response %d/%d\n", handle, rx_slot);

	वापस valid_slot;
पूर्ण

अटल व्योम dln2_run_event_callbacks(काष्ठा dln2_dev *dln2, u16 id, u16 echo,
				     व्योम *data, पूर्णांक len)
अणु
	काष्ठा dln2_event_cb_entry *i;

	rcu_पढ़ो_lock();

	list_क्रम_each_entry_rcu(i, &dln2->event_cb_list, list) अणु
		अगर (i->id == id) अणु
			i->callback(i->pdev, echo, data, len);
			अवरोध;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम dln2_rx(काष्ठा urb *urb)
अणु
	काष्ठा dln2_dev *dln2 = urb->context;
	काष्ठा dln2_header *hdr = urb->transfer_buffer;
	काष्ठा device *dev = &dln2->पूर्णांकerface->dev;
	u16 id, echo, handle, size;
	u8 *data;
	पूर्णांक len;
	पूर्णांक err;

	चयन (urb->status) अणु
	हाल 0:
		/* success */
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
	हाल -EPIPE:
		/* this urb is terminated, clean up */
		dev_dbg(dev, "urb shutting down with status %d\n", urb->status);
		वापस;
	शेष:
		dev_dbg(dev, "nonzero urb status received %d\n", urb->status);
		जाओ out;
	पूर्ण

	अगर (urb->actual_length < माप(काष्ठा dln2_header)) अणु
		dev_err(dev, "short response: %d\n", urb->actual_length);
		जाओ out;
	पूर्ण

	handle = le16_to_cpu(hdr->handle);
	id = le16_to_cpu(hdr->id);
	echo = le16_to_cpu(hdr->echo);
	size = le16_to_cpu(hdr->size);

	अगर (size != urb->actual_length) अणु
		dev_err(dev, "size mismatch: handle %x cmd %x echo %x size %d actual %d\n",
			handle, id, echo, size, urb->actual_length);
		जाओ out;
	पूर्ण

	अगर (handle >= DLN2_HANDLES) अणु
		dev_warn(dev, "invalid handle %d\n", handle);
		जाओ out;
	पूर्ण

	data = urb->transfer_buffer + माप(काष्ठा dln2_header);
	len = urb->actual_length - माप(काष्ठा dln2_header);

	अगर (handle == DLN2_HANDLE_EVENT) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&dln2->event_cb_lock, flags);
		dln2_run_event_callbacks(dln2, id, echo, data, len);
		spin_unlock_irqrestore(&dln2->event_cb_lock, flags);
	पूर्ण अन्यथा अणु
		/* URB will be re-submitted in _dln2_transfer (मुक्त_rx_slot) */
		अगर (dln2_transfer_complete(dln2, urb, handle, echo))
			वापस;
	पूर्ण

out:
	err = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (err < 0)
		dev_err(dev, "failed to resubmit RX URB: %d\n", err);
पूर्ण

अटल व्योम *dln2_prep_buf(u16 handle, u16 cmd, u16 echo, स्थिर व्योम *obuf,
			   पूर्णांक *obuf_len, gfp_t gfp)
अणु
	पूर्णांक len;
	व्योम *buf;
	काष्ठा dln2_header *hdr;

	len = *obuf_len + माप(*hdr);
	buf = kदो_स्मृति(len, gfp);
	अगर (!buf)
		वापस शून्य;

	hdr = (काष्ठा dln2_header *)buf;
	hdr->id = cpu_to_le16(cmd);
	hdr->size = cpu_to_le16(len);
	hdr->echo = cpu_to_le16(echo);
	hdr->handle = cpu_to_le16(handle);

	स_नकल(buf + माप(*hdr), obuf, *obuf_len);

	*obuf_len = len;

	वापस buf;
पूर्ण

अटल पूर्णांक dln2_send_रुको(काष्ठा dln2_dev *dln2, u16 handle, u16 cmd, u16 echo,
			  स्थिर व्योम *obuf, पूर्णांक obuf_len)
अणु
	पूर्णांक ret = 0;
	पूर्णांक len = obuf_len;
	व्योम *buf;
	पूर्णांक actual;

	buf = dln2_prep_buf(handle, cmd, echo, obuf, &len, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = usb_bulk_msg(dln2->usb_dev,
			   usb_sndbulkpipe(dln2->usb_dev, dln2->ep_out),
			   buf, len, &actual, DLN2_USB_TIMEOUT);

	kमुक्त(buf);

	वापस ret;
पूर्ण

अटल bool find_मुक्त_slot(काष्ठा dln2_dev *dln2, u16 handle, पूर्णांक *slot)
अणु
	काष्ठा dln2_mod_rx_slots *rxs;
	अचिन्हित दीर्घ flags;

	अगर (dln2->disconnect) अणु
		*slot = -ENODEV;
		वापस true;
	पूर्ण

	rxs = &dln2->mod_rx_slots[handle];

	spin_lock_irqsave(&rxs->lock, flags);

	*slot = find_first_zero_bit(rxs->bmap, DLN2_MAX_RX_SLOTS);

	अगर (*slot < DLN2_MAX_RX_SLOTS) अणु
		काष्ठा dln2_rx_context *rxc = &rxs->slots[*slot];

		set_bit(*slot, rxs->bmap);
		rxc->in_use = true;
	पूर्ण

	spin_unlock_irqrestore(&rxs->lock, flags);

	वापस *slot < DLN2_MAX_RX_SLOTS;
पूर्ण

अटल पूर्णांक alloc_rx_slot(काष्ठा dln2_dev *dln2, u16 handle)
अणु
	पूर्णांक ret;
	पूर्णांक slot;

	/*
	 * No need to समयout here, the रुको is bounded by the समयout in
	 * _dln2_transfer.
	 */
	ret = रुको_event_पूर्णांकerruptible(dln2->mod_rx_slots[handle].wq,
				       find_मुक्त_slot(dln2, handle, &slot));
	अगर (ret < 0)
		वापस ret;

	वापस slot;
पूर्ण

अटल व्योम मुक्त_rx_slot(काष्ठा dln2_dev *dln2, u16 handle, पूर्णांक slot)
अणु
	काष्ठा dln2_mod_rx_slots *rxs;
	काष्ठा urb *urb = शून्य;
	अचिन्हित दीर्घ flags;
	काष्ठा dln2_rx_context *rxc;

	rxs = &dln2->mod_rx_slots[handle];

	spin_lock_irqsave(&rxs->lock, flags);

	clear_bit(slot, rxs->bmap);

	rxc = &rxs->slots[slot];
	rxc->in_use = false;
	urb = rxc->urb;
	rxc->urb = शून्य;
	reinit_completion(&rxc->करोne);

	spin_unlock_irqrestore(&rxs->lock, flags);

	अगर (urb) अणु
		पूर्णांक err;
		काष्ठा device *dev = &dln2->पूर्णांकerface->dev;

		err = usb_submit_urb(urb, GFP_KERNEL);
		अगर (err < 0)
			dev_err(dev, "failed to resubmit RX URB: %d\n", err);
	पूर्ण

	wake_up_पूर्णांकerruptible(&rxs->wq);
पूर्ण

अटल पूर्णांक _dln2_transfer(काष्ठा dln2_dev *dln2, u16 handle, u16 cmd,
			  स्थिर व्योम *obuf, अचिन्हित obuf_len,
			  व्योम *ibuf, अचिन्हित *ibuf_len)
अणु
	पूर्णांक ret = 0;
	पूर्णांक rx_slot;
	काष्ठा dln2_response *rsp;
	काष्ठा dln2_rx_context *rxc;
	काष्ठा device *dev = &dln2->पूर्णांकerface->dev;
	स्थिर अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(DLN2_USB_TIMEOUT);
	काष्ठा dln2_mod_rx_slots *rxs = &dln2->mod_rx_slots[handle];
	पूर्णांक size;

	spin_lock(&dln2->disconnect_lock);
	अगर (!dln2->disconnect)
		dln2->active_transfers++;
	अन्यथा
		ret = -ENODEV;
	spin_unlock(&dln2->disconnect_lock);

	अगर (ret)
		वापस ret;

	rx_slot = alloc_rx_slot(dln2, handle);
	अगर (rx_slot < 0) अणु
		ret = rx_slot;
		जाओ out_decr;
	पूर्ण

	ret = dln2_send_रुको(dln2, handle, cmd, rx_slot, obuf, obuf_len);
	अगर (ret < 0) अणु
		dev_err(dev, "USB write failed: %d\n", ret);
		जाओ out_मुक्त_rx_slot;
	पूर्ण

	rxc = &rxs->slots[rx_slot];

	ret = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&rxc->करोne, समयout);
	अगर (ret <= 0) अणु
		अगर (!ret)
			ret = -ETIMEDOUT;
		जाओ out_मुक्त_rx_slot;
	पूर्ण अन्यथा अणु
		ret = 0;
	पूर्ण

	अगर (dln2->disconnect) अणु
		ret = -ENODEV;
		जाओ out_मुक्त_rx_slot;
	पूर्ण

	/* अगर we got here we know that the response header has been checked */
	rsp = rxc->urb->transfer_buffer;
	size = le16_to_cpu(rsp->hdr.size);

	अगर (size < माप(*rsp)) अणु
		ret = -EPROTO;
		जाओ out_मुक्त_rx_slot;
	पूर्ण

	अगर (le16_to_cpu(rsp->result) > 0x80) अणु
		dev_dbg(dev, "%d received response with error %d\n",
			handle, le16_to_cpu(rsp->result));
		ret = -EREMOTEIO;
		जाओ out_मुक्त_rx_slot;
	पूर्ण

	अगर (!ibuf)
		जाओ out_मुक्त_rx_slot;

	अगर (*ibuf_len > size - माप(*rsp))
		*ibuf_len = size - माप(*rsp);

	स_नकल(ibuf, rsp + 1, *ibuf_len);

out_मुक्त_rx_slot:
	मुक्त_rx_slot(dln2, handle, rx_slot);
out_decr:
	spin_lock(&dln2->disconnect_lock);
	dln2->active_transfers--;
	spin_unlock(&dln2->disconnect_lock);
	अगर (dln2->disconnect)
		wake_up(&dln2->disconnect_wq);

	वापस ret;
पूर्ण

पूर्णांक dln2_transfer(काष्ठा platक्रमm_device *pdev, u16 cmd,
		  स्थिर व्योम *obuf, अचिन्हित obuf_len,
		  व्योम *ibuf, अचिन्हित *ibuf_len)
अणु
	काष्ठा dln2_platक्रमm_data *dln2_pdata;
	काष्ठा dln2_dev *dln2;
	u16 handle;

	dln2 = dev_get_drvdata(pdev->dev.parent);
	dln2_pdata = dev_get_platdata(&pdev->dev);
	handle = dln2_pdata->handle;

	वापस _dln2_transfer(dln2, handle, cmd, obuf, obuf_len, ibuf,
			      ibuf_len);
पूर्ण
EXPORT_SYMBOL(dln2_transfer);

अटल पूर्णांक dln2_check_hw(काष्ठा dln2_dev *dln2)
अणु
	पूर्णांक ret;
	__le32 hw_type;
	पूर्णांक len = माप(hw_type);

	ret = _dln2_transfer(dln2, DLN2_HANDLE_CTRL, CMD_GET_DEVICE_VER,
			     शून्य, 0, &hw_type, &len);
	अगर (ret < 0)
		वापस ret;
	अगर (len < माप(hw_type))
		वापस -EREMOTEIO;

	अगर (le32_to_cpu(hw_type) != DLN2_HW_ID) अणु
		dev_err(&dln2->पूर्णांकerface->dev, "Device ID 0x%x not supported\n",
			le32_to_cpu(hw_type));
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dln2_prपूर्णांक_serialno(काष्ठा dln2_dev *dln2)
अणु
	पूर्णांक ret;
	__le32 serial_no;
	पूर्णांक len = माप(serial_no);
	काष्ठा device *dev = &dln2->पूर्णांकerface->dev;

	ret = _dln2_transfer(dln2, DLN2_HANDLE_CTRL, CMD_GET_DEVICE_SN, शून्य, 0,
			     &serial_no, &len);
	अगर (ret < 0)
		वापस ret;
	अगर (len < माप(serial_no))
		वापस -EREMOTEIO;

	dev_info(dev, "Diolan DLN2 serial %u\n", le32_to_cpu(serial_no));

	वापस 0;
पूर्ण

अटल पूर्णांक dln2_hw_init(काष्ठा dln2_dev *dln2)
अणु
	पूर्णांक ret;

	ret = dln2_check_hw(dln2);
	अगर (ret < 0)
		वापस ret;

	वापस dln2_prपूर्णांक_serialno(dln2);
पूर्ण

अटल व्योम dln2_मुक्त_rx_urbs(काष्ठा dln2_dev *dln2)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < DLN2_MAX_URBS; i++) अणु
		usb_मुक्त_urb(dln2->rx_urb[i]);
		kमुक्त(dln2->rx_buf[i]);
	पूर्ण
पूर्ण

अटल व्योम dln2_stop_rx_urbs(काष्ठा dln2_dev *dln2)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < DLN2_MAX_URBS; i++)
		usb_समाप्त_urb(dln2->rx_urb[i]);
पूर्ण

अटल व्योम dln2_मुक्त(काष्ठा dln2_dev *dln2)
अणु
	dln2_मुक्त_rx_urbs(dln2);
	usb_put_dev(dln2->usb_dev);
	kमुक्त(dln2);
पूर्ण

अटल पूर्णांक dln2_setup_rx_urbs(काष्ठा dln2_dev *dln2,
			      काष्ठा usb_host_पूर्णांकerface *hostअगर)
अणु
	पूर्णांक i;
	स्थिर पूर्णांक rx_max_size = DLN2_RX_BUF_SIZE;

	क्रम (i = 0; i < DLN2_MAX_URBS; i++) अणु
		dln2->rx_buf[i] = kदो_स्मृति(rx_max_size, GFP_KERNEL);
		अगर (!dln2->rx_buf[i])
			वापस -ENOMEM;

		dln2->rx_urb[i] = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!dln2->rx_urb[i])
			वापस -ENOMEM;

		usb_fill_bulk_urb(dln2->rx_urb[i], dln2->usb_dev,
				  usb_rcvbulkpipe(dln2->usb_dev, dln2->ep_in),
				  dln2->rx_buf[i], rx_max_size, dln2_rx, dln2);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dln2_start_rx_urbs(काष्ठा dln2_dev *dln2, gfp_t gfp)
अणु
	काष्ठा device *dev = &dln2->पूर्णांकerface->dev;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < DLN2_MAX_URBS; i++) अणु
		ret = usb_submit_urb(dln2->rx_urb[i], gfp);
		अगर (ret < 0) अणु
			dev_err(dev, "failed to submit RX URB: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

क्रमागत अणु
	DLN2_ACPI_MATCH_GPIO	= 0,
	DLN2_ACPI_MATCH_I2C	= 1,
	DLN2_ACPI_MATCH_SPI	= 2,
पूर्ण;

अटल काष्ठा dln2_platक्रमm_data dln2_pdata_gpio = अणु
	.handle = DLN2_HANDLE_GPIO,
पूर्ण;

अटल काष्ठा mfd_cell_acpi_match dln2_acpi_match_gpio = अणु
	.adr = DLN2_ACPI_MATCH_GPIO,
पूर्ण;

/* Only one I2C port seems to be supported on current hardware */
अटल काष्ठा dln2_platक्रमm_data dln2_pdata_i2c = अणु
	.handle = DLN2_HANDLE_I2C,
	.port = 0,
पूर्ण;

अटल काष्ठा mfd_cell_acpi_match dln2_acpi_match_i2c = अणु
	.adr = DLN2_ACPI_MATCH_I2C,
पूर्ण;

/* Only one SPI port supported */
अटल काष्ठा dln2_platक्रमm_data dln2_pdata_spi = अणु
	.handle = DLN2_HANDLE_SPI,
	.port = 0,
पूर्ण;

अटल काष्ठा mfd_cell_acpi_match dln2_acpi_match_spi = अणु
	.adr = DLN2_ACPI_MATCH_SPI,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell dln2_devs[] = अणु
	अणु
		.name = "dln2-gpio",
		.acpi_match = &dln2_acpi_match_gpio,
		.platक्रमm_data = &dln2_pdata_gpio,
		.pdata_size = माप(काष्ठा dln2_platक्रमm_data),
	पूर्ण,
	अणु
		.name = "dln2-i2c",
		.acpi_match = &dln2_acpi_match_i2c,
		.platक्रमm_data = &dln2_pdata_i2c,
		.pdata_size = माप(काष्ठा dln2_platक्रमm_data),
	पूर्ण,
	अणु
		.name = "dln2-spi",
		.acpi_match = &dln2_acpi_match_spi,
		.platक्रमm_data = &dln2_pdata_spi,
		.pdata_size = माप(काष्ठा dln2_platक्रमm_data),
	पूर्ण,
पूर्ण;

अटल व्योम dln2_stop(काष्ठा dln2_dev *dln2)
अणु
	पूर्णांक i, j;

	/* करोn't allow starting new transfers */
	spin_lock(&dln2->disconnect_lock);
	dln2->disconnect = true;
	spin_unlock(&dln2->disconnect_lock);

	/* cancel in progress transfers */
	क्रम (i = 0; i < DLN2_HANDLES; i++) अणु
		काष्ठा dln2_mod_rx_slots *rxs = &dln2->mod_rx_slots[i];
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&rxs->lock, flags);

		/* cancel all response रुकोers */
		क्रम (j = 0; j < DLN2_MAX_RX_SLOTS; j++) अणु
			काष्ठा dln2_rx_context *rxc = &rxs->slots[j];

			अगर (rxc->in_use)
				complete(&rxc->करोne);
		पूर्ण

		spin_unlock_irqrestore(&rxs->lock, flags);
	पूर्ण

	/* रुको क्रम transfers to end */
	रुको_event(dln2->disconnect_wq, !dln2->active_transfers);

	dln2_stop_rx_urbs(dln2);
पूर्ण

अटल व्योम dln2_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा dln2_dev *dln2 = usb_get_पूर्णांकfdata(पूर्णांकerface);

	dln2_stop(dln2);

	mfd_हटाओ_devices(&पूर्णांकerface->dev);

	dln2_मुक्त(dln2);
पूर्ण

अटल पूर्णांक dln2_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
		      स्थिर काष्ठा usb_device_id *usb_id)
अणु
	काष्ठा usb_host_पूर्णांकerface *hostअगर = पूर्णांकerface->cur_altsetting;
	काष्ठा usb_endpoपूर्णांक_descriptor *epin;
	काष्ठा usb_endpoपूर्णांक_descriptor *epout;
	काष्ठा device *dev = &पूर्णांकerface->dev;
	काष्ठा dln2_dev *dln2;
	पूर्णांक ret;
	पूर्णांक i, j;

	अगर (hostअगर->desc.bInterfaceNumber != 0 ||
	    hostअगर->desc.bNumEndpoपूर्णांकs < 2)
		वापस -ENODEV;

	epout = &hostअगर->endpoपूर्णांक[DLN2_EP_OUT].desc;
	अगर (!usb_endpoपूर्णांक_is_bulk_out(epout))
		वापस -ENODEV;
	epin = &hostअगर->endpoपूर्णांक[DLN2_EP_IN].desc;
	अगर (!usb_endpoपूर्णांक_is_bulk_in(epin))
		वापस -ENODEV;

	dln2 = kzalloc(माप(*dln2), GFP_KERNEL);
	अगर (!dln2)
		वापस -ENOMEM;

	dln2->ep_out = epout->bEndpoपूर्णांकAddress;
	dln2->ep_in = epin->bEndpoपूर्णांकAddress;
	dln2->usb_dev = usb_get_dev(पूर्णांकerface_to_usbdev(पूर्णांकerface));
	dln2->पूर्णांकerface = पूर्णांकerface;
	usb_set_पूर्णांकfdata(पूर्णांकerface, dln2);
	init_रुकोqueue_head(&dln2->disconnect_wq);

	क्रम (i = 0; i < DLN2_HANDLES; i++) अणु
		init_रुकोqueue_head(&dln2->mod_rx_slots[i].wq);
		spin_lock_init(&dln2->mod_rx_slots[i].lock);
		क्रम (j = 0; j < DLN2_MAX_RX_SLOTS; j++)
			init_completion(&dln2->mod_rx_slots[i].slots[j].करोne);
	पूर्ण

	spin_lock_init(&dln2->event_cb_lock);
	spin_lock_init(&dln2->disconnect_lock);
	INIT_LIST_HEAD(&dln2->event_cb_list);

	ret = dln2_setup_rx_urbs(dln2, hostअगर);
	अगर (ret)
		जाओ out_मुक्त;

	ret = dln2_start_rx_urbs(dln2, GFP_KERNEL);
	अगर (ret)
		जाओ out_stop_rx;

	ret = dln2_hw_init(dln2);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to initialize hardware\n");
		जाओ out_stop_rx;
	पूर्ण

	ret = mfd_add_hotplug_devices(dev, dln2_devs, ARRAY_SIZE(dln2_devs));
	अगर (ret != 0) अणु
		dev_err(dev, "failed to add mfd devices to core\n");
		जाओ out_stop_rx;
	पूर्ण

	वापस 0;

out_stop_rx:
	dln2_stop_rx_urbs(dln2);

out_मुक्त:
	dln2_मुक्त(dln2);

	वापस ret;
पूर्ण

अटल पूर्णांक dln2_suspend(काष्ठा usb_पूर्णांकerface *अगरace, pm_message_t message)
अणु
	काष्ठा dln2_dev *dln2 = usb_get_पूर्णांकfdata(अगरace);

	dln2_stop(dln2);

	वापस 0;
पूर्ण

अटल पूर्णांक dln2_resume(काष्ठा usb_पूर्णांकerface *अगरace)
अणु
	काष्ठा dln2_dev *dln2 = usb_get_पूर्णांकfdata(अगरace);

	dln2->disconnect = false;

	वापस dln2_start_rx_urbs(dln2, GFP_NOIO);
पूर्ण

अटल स्थिर काष्ठा usb_device_id dln2_table[] = अणु
	अणु USB_DEVICE(0xa257, 0x2013) पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, dln2_table);

अटल काष्ठा usb_driver dln2_driver = अणु
	.name = "dln2",
	.probe = dln2_probe,
	.disconnect = dln2_disconnect,
	.id_table = dln2_table,
	.suspend = dln2_suspend,
	.resume = dln2_resume,
पूर्ण;

module_usb_driver(dln2_driver);

MODULE_AUTHOR("Octavian Purdila <octavian.purdila@intel.com>");
MODULE_DESCRIPTION("Core driver for the Diolan DLN2 interface adapter");
MODULE_LICENSE("GPL v2");
