<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Copyright (C) 2010 Willow Garage <http://www.willowgarage.com>
	Copyright (C) 2004 - 2010 Ivo van Doorn <IvDoorn@gmail.com>
	<http://rt2x00.serialmonkey.com>

 */

/*
	Module: rt2x00usb
	Abstract: rt2x00 generic usb device routines.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <linux/bug.h>

#समावेश "rt2x00.h"
#समावेश "rt2x00usb.h"

अटल bool rt2x00usb_check_usb_error(काष्ठा rt2x00_dev *rt2x00dev, पूर्णांक status)
अणु
	अगर (status == -ENODEV || status == -ENOENT)
		वापस true;

	अगर (status == -EPROTO || status == -ETIMEDOUT)
		rt2x00dev->num_proto_errs++;
	अन्यथा
		rt2x00dev->num_proto_errs = 0;

	अगर (rt2x00dev->num_proto_errs > 3)
		वापस true;

	वापस false;
पूर्ण

/*
 * Interfacing with the HW.
 */
पूर्णांक rt2x00usb_venकरोr_request(काष्ठा rt2x00_dev *rt2x00dev,
			     स्थिर u8 request, स्थिर u8 requesttype,
			     स्थिर u16 offset, स्थिर u16 value,
			     व्योम *buffer, स्थिर u16 buffer_length,
			     स्थिर पूर्णांक समयout)
अणु
	काष्ठा usb_device *usb_dev = to_usb_device_पूर्णांकf(rt2x00dev->dev);
	पूर्णांक status;
	अचिन्हित पूर्णांक pipe =
	    (requesttype == USB_VENDOR_REQUEST_IN) ?
	    usb_rcvctrlpipe(usb_dev, 0) : usb_sndctrlpipe(usb_dev, 0);
	अचिन्हित दीर्घ expire = jअगरfies + msecs_to_jअगरfies(समयout);

	अगर (!test_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags))
		वापस -ENODEV;

	करो अणु
		status = usb_control_msg(usb_dev, pipe, request, requesttype,
					 value, offset, buffer, buffer_length,
					 समयout / 2);
		अगर (status >= 0)
			वापस 0;

		अगर (rt2x00usb_check_usb_error(rt2x00dev, status)) अणु
			/* Device has disappeared. */
			clear_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, expire));

	rt2x00_err(rt2x00dev,
		   "Vendor Request 0x%02x failed for offset 0x%04x with error %d\n",
		   request, offset, status);

	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00usb_venकरोr_request);

पूर्णांक rt2x00usb_venकरोr_req_buff_lock(काष्ठा rt2x00_dev *rt2x00dev,
				   स्थिर u8 request, स्थिर u8 requesttype,
				   स्थिर u16 offset, व्योम *buffer,
				   स्थिर u16 buffer_length, स्थिर पूर्णांक समयout)
अणु
	पूर्णांक status;

	BUG_ON(!mutex_is_locked(&rt2x00dev->csr_mutex));

	/*
	 * Check क्रम Cache availability.
	 */
	अगर (unlikely(!rt2x00dev->csr.cache || buffer_length > CSR_CACHE_SIZE)) अणु
		rt2x00_err(rt2x00dev, "CSR cache not available\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (requesttype == USB_VENDOR_REQUEST_OUT)
		स_नकल(rt2x00dev->csr.cache, buffer, buffer_length);

	status = rt2x00usb_venकरोr_request(rt2x00dev, request, requesttype,
					  offset, 0, rt2x00dev->csr.cache,
					  buffer_length, समयout);

	अगर (!status && requesttype == USB_VENDOR_REQUEST_IN)
		स_नकल(buffer, rt2x00dev->csr.cache, buffer_length);

	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00usb_venकरोr_req_buff_lock);

पूर्णांक rt2x00usb_venकरोr_request_buff(काष्ठा rt2x00_dev *rt2x00dev,
				  स्थिर u8 request, स्थिर u8 requesttype,
				  स्थिर u16 offset, व्योम *buffer,
				  स्थिर u16 buffer_length)
अणु
	पूर्णांक status = 0;
	अचिन्हित अक्षर *tb;
	u16 off, len, bsize;

	mutex_lock(&rt2x00dev->csr_mutex);

	tb  = (अक्षर *)buffer;
	off = offset;
	len = buffer_length;
	जबतक (len && !status) अणु
		bsize = min_t(u16, CSR_CACHE_SIZE, len);
		status = rt2x00usb_venकरोr_req_buff_lock(rt2x00dev, request,
							requesttype, off, tb,
							bsize, REGISTER_TIMEOUT);

		tb  += bsize;
		len -= bsize;
		off += bsize;
	पूर्ण

	mutex_unlock(&rt2x00dev->csr_mutex);

	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00usb_venकरोr_request_buff);

पूर्णांक rt2x00usb_regbusy_पढ़ो(काष्ठा rt2x00_dev *rt2x00dev,
			   स्थिर अचिन्हित पूर्णांक offset,
			   स्थिर काष्ठा rt2x00_field32 field,
			   u32 *reg)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!test_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags))
		वापस -ENODEV;

	क्रम (i = 0; i < REGISTER_USB_BUSY_COUNT; i++) अणु
		*reg = rt2x00usb_रेजिस्टर_पढ़ो_lock(rt2x00dev, offset);
		अगर (!rt2x00_get_field32(*reg, field))
			वापस 1;
		udelay(REGISTER_BUSY_DELAY);
	पूर्ण

	rt2x00_err(rt2x00dev, "Indirect register access failed: offset=0x%.08x, value=0x%.08x\n",
		   offset, *reg);
	*reg = ~0;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00usb_regbusy_पढ़ो);


काष्ठा rt2x00_async_पढ़ो_data अणु
	__le32 reg;
	काष्ठा usb_ctrlrequest cr;
	काष्ठा rt2x00_dev *rt2x00dev;
	bool (*callback)(काष्ठा rt2x00_dev *, पूर्णांक, u32);
पूर्ण;

अटल व्योम rt2x00usb_रेजिस्टर_पढ़ो_async_cb(काष्ठा urb *urb)
अणु
	काष्ठा rt2x00_async_पढ़ो_data *rd = urb->context;
	अगर (rd->callback(rd->rt2x00dev, urb->status, le32_to_cpu(rd->reg))) अणु
		usb_anchor_urb(urb, rd->rt2x00dev->anchor);
		अगर (usb_submit_urb(urb, GFP_ATOMIC) < 0) अणु
			usb_unanchor_urb(urb);
			kमुक्त(rd);
		पूर्ण
	पूर्ण अन्यथा
		kमुक्त(rd);
पूर्ण

व्योम rt2x00usb_रेजिस्टर_पढ़ो_async(काष्ठा rt2x00_dev *rt2x00dev,
				   स्थिर अचिन्हित पूर्णांक offset,
				   bool (*callback)(काष्ठा rt2x00_dev*, पूर्णांक, u32))
अणु
	काष्ठा usb_device *usb_dev = to_usb_device_पूर्णांकf(rt2x00dev->dev);
	काष्ठा urb *urb;
	काष्ठा rt2x00_async_पढ़ो_data *rd;

	rd = kदो_स्मृति(माप(*rd), GFP_ATOMIC);
	अगर (!rd)
		वापस;

	urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!urb) अणु
		kमुक्त(rd);
		वापस;
	पूर्ण

	rd->rt2x00dev = rt2x00dev;
	rd->callback = callback;
	rd->cr.bRequestType = USB_VENDOR_REQUEST_IN;
	rd->cr.bRequest = USB_MULTI_READ;
	rd->cr.wValue = 0;
	rd->cr.wIndex = cpu_to_le16(offset);
	rd->cr.wLength = cpu_to_le16(माप(u32));

	usb_fill_control_urb(urb, usb_dev, usb_rcvctrlpipe(usb_dev, 0),
			     (अचिन्हित अक्षर *)(&rd->cr), &rd->reg, माप(rd->reg),
			     rt2x00usb_रेजिस्टर_पढ़ो_async_cb, rd);
	usb_anchor_urb(urb, rt2x00dev->anchor);
	अगर (usb_submit_urb(urb, GFP_ATOMIC) < 0) अणु
		usb_unanchor_urb(urb);
		kमुक्त(rd);
	पूर्ण
	usb_मुक्त_urb(urb);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00usb_रेजिस्टर_पढ़ो_async);

/*
 * TX data handlers.
 */
अटल व्योम rt2x00usb_work_txकरोne_entry(काष्ठा queue_entry *entry)
अणु
	/*
	 * If the transfer to hardware succeeded, it करोes not mean the
	 * frame was send out correctly. It only means the frame
	 * was successfully pushed to the hardware, we have no
	 * way to determine the transmission status right now.
	 * (Only indirectly by looking at the failed TX counters
	 * in the रेजिस्टर).
	 */
	अगर (test_bit(ENTRY_DATA_IO_FAILED, &entry->flags))
		rt2x00lib_txकरोne_noinfo(entry, TXDONE_FAILURE);
	अन्यथा
		rt2x00lib_txकरोne_noinfo(entry, TXDONE_UNKNOWN);
पूर्ण

अटल व्योम rt2x00usb_work_txकरोne(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rt2x00_dev *rt2x00dev =
	    container_of(work, काष्ठा rt2x00_dev, txकरोne_work);
	काष्ठा data_queue *queue;
	काष्ठा queue_entry *entry;

	tx_queue_क्रम_each(rt2x00dev, queue) अणु
		जबतक (!rt2x00queue_empty(queue)) अणु
			entry = rt2x00queue_get_entry(queue, Q_INDEX_DONE);

			अगर (test_bit(ENTRY_OWNER_DEVICE_DATA, &entry->flags) ||
			    !test_bit(ENTRY_DATA_STATUS_PENDING, &entry->flags))
				अवरोध;

			rt2x00usb_work_txकरोne_entry(entry);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rt2x00usb_पूर्णांकerrupt_txकरोne(काष्ठा urb *urb)
अणु
	काष्ठा queue_entry *entry = (काष्ठा queue_entry *)urb->context;
	काष्ठा rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;

	अगर (!test_bit(ENTRY_OWNER_DEVICE_DATA, &entry->flags))
		वापस;
	/*
	 * Check अगर the frame was correctly uploaded
	 */
	अगर (urb->status)
		set_bit(ENTRY_DATA_IO_FAILED, &entry->flags);
	/*
	 * Report the frame as DMA करोne
	 */
	rt2x00lib_dmaकरोne(entry);

	अगर (rt2x00dev->ops->lib->tx_dma_करोne)
		rt2x00dev->ops->lib->tx_dma_करोne(entry);
	/*
	 * Schedule the delayed work क्रम पढ़ोing the TX status
	 * from the device.
	 */
	अगर (!rt2x00_has_cap_flag(rt2x00dev, REQUIRE_TXSTATUS_FIFO) ||
	    !kfअगरo_is_empty(&rt2x00dev->txstatus_fअगरo))
		queue_work(rt2x00dev->workqueue, &rt2x00dev->txकरोne_work);
पूर्ण

अटल bool rt2x00usb_kick_tx_entry(काष्ठा queue_entry *entry, व्योम *data)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;
	काष्ठा usb_device *usb_dev = to_usb_device_पूर्णांकf(rt2x00dev->dev);
	काष्ठा queue_entry_priv_usb *entry_priv = entry->priv_data;
	u32 length;
	पूर्णांक status;

	अगर (!test_and_clear_bit(ENTRY_DATA_PENDING, &entry->flags) ||
	    test_bit(ENTRY_DATA_STATUS_PENDING, &entry->flags))
		वापस false;

	/*
	 * USB devices require certain padding at the end of each frame
	 * and urb. Those paddings are not included in skbs. Pass entry
	 * to the driver to determine what the overall length should be.
	 */
	length = rt2x00dev->ops->lib->get_tx_data_len(entry);

	status = skb_padto(entry->skb, length);
	अगर (unlikely(status)) अणु
		/* TODO: report something more appropriate than IO_FAILED. */
		rt2x00_warn(rt2x00dev, "TX SKB padding error, out of memory\n");
		set_bit(ENTRY_DATA_IO_FAILED, &entry->flags);
		rt2x00lib_dmaकरोne(entry);

		वापस false;
	पूर्ण

	usb_fill_bulk_urb(entry_priv->urb, usb_dev,
			  usb_sndbulkpipe(usb_dev, entry->queue->usb_endpoपूर्णांक),
			  entry->skb->data, length,
			  rt2x00usb_पूर्णांकerrupt_txकरोne, entry);

	status = usb_submit_urb(entry_priv->urb, GFP_ATOMIC);
	अगर (status) अणु
		अगर (rt2x00usb_check_usb_error(rt2x00dev, status))
			clear_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags);
		set_bit(ENTRY_DATA_IO_FAILED, &entry->flags);
		rt2x00lib_dmaकरोne(entry);
	पूर्ण

	वापस false;
पूर्ण

/*
 * RX data handlers.
 */
अटल व्योम rt2x00usb_work_rxकरोne(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rt2x00_dev *rt2x00dev =
	    container_of(work, काष्ठा rt2x00_dev, rxकरोne_work);
	काष्ठा queue_entry *entry;
	काष्ठा skb_frame_desc *skbdesc;
	u8 rxd[32];

	जबतक (!rt2x00queue_empty(rt2x00dev->rx)) अणु
		entry = rt2x00queue_get_entry(rt2x00dev->rx, Q_INDEX_DONE);

		अगर (test_bit(ENTRY_OWNER_DEVICE_DATA, &entry->flags))
			अवरोध;

		/*
		 * Fill in desc fields of the skb descriptor
		 */
		skbdesc = get_skb_frame_desc(entry->skb);
		skbdesc->desc = rxd;
		skbdesc->desc_len = entry->queue->desc_size;

		/*
		 * Send the frame to rt2x00lib क्रम further processing.
		 */
		rt2x00lib_rxकरोne(entry, GFP_KERNEL);
	पूर्ण
पूर्ण

अटल व्योम rt2x00usb_पूर्णांकerrupt_rxकरोne(काष्ठा urb *urb)
अणु
	काष्ठा queue_entry *entry = (काष्ठा queue_entry *)urb->context;
	काष्ठा rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;

	अगर (!test_bit(ENTRY_OWNER_DEVICE_DATA, &entry->flags))
		वापस;

	/*
	 * Check अगर the received data is simply too small
	 * to be actually valid, or अगर the urb is संकेतing
	 * a problem.
	 */
	अगर (urb->actual_length < entry->queue->desc_size || urb->status)
		set_bit(ENTRY_DATA_IO_FAILED, &entry->flags);

	/*
	 * Report the frame as DMA करोne
	 */
	rt2x00lib_dmaकरोne(entry);

	/*
	 * Schedule the delayed work क्रम processing RX data
	 */
	queue_work(rt2x00dev->workqueue, &rt2x00dev->rxकरोne_work);
पूर्ण

अटल bool rt2x00usb_kick_rx_entry(काष्ठा queue_entry *entry, व्योम *data)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;
	काष्ठा usb_device *usb_dev = to_usb_device_पूर्णांकf(rt2x00dev->dev);
	काष्ठा queue_entry_priv_usb *entry_priv = entry->priv_data;
	पूर्णांक status;

	अगर (test_and_set_bit(ENTRY_OWNER_DEVICE_DATA, &entry->flags))
		वापस false;

	rt2x00lib_dmastart(entry);

	usb_fill_bulk_urb(entry_priv->urb, usb_dev,
			  usb_rcvbulkpipe(usb_dev, entry->queue->usb_endpoपूर्णांक),
			  entry->skb->data, entry->skb->len,
			  rt2x00usb_पूर्णांकerrupt_rxकरोne, entry);

	status = usb_submit_urb(entry_priv->urb, GFP_ATOMIC);
	अगर (status) अणु
		अगर (rt2x00usb_check_usb_error(rt2x00dev, status))
			clear_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags);
		set_bit(ENTRY_DATA_IO_FAILED, &entry->flags);
		rt2x00lib_dmaकरोne(entry);
	पूर्ण

	वापस false;
पूर्ण

व्योम rt2x00usb_kick_queue(काष्ठा data_queue *queue)
अणु
	चयन (queue->qid) अणु
	हाल QID_AC_VO:
	हाल QID_AC_VI:
	हाल QID_AC_BE:
	हाल QID_AC_BK:
		अगर (!rt2x00queue_empty(queue))
			rt2x00queue_क्रम_each_entry(queue,
						   Q_INDEX_DONE,
						   Q_INDEX,
						   शून्य,
						   rt2x00usb_kick_tx_entry);
		अवरोध;
	हाल QID_RX:
		अगर (!rt2x00queue_full(queue))
			rt2x00queue_क्रम_each_entry(queue,
						   Q_INDEX,
						   Q_INDEX_DONE,
						   शून्य,
						   rt2x00usb_kick_rx_entry);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00usb_kick_queue);

अटल bool rt2x00usb_flush_entry(काष्ठा queue_entry *entry, व्योम *data)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;
	काष्ठा queue_entry_priv_usb *entry_priv = entry->priv_data;
	काष्ठा queue_entry_priv_usb_bcn *bcn_priv = entry->priv_data;

	अगर (!test_bit(ENTRY_OWNER_DEVICE_DATA, &entry->flags))
		वापस false;

	usb_समाप्त_urb(entry_priv->urb);

	/*
	 * Kill guardian urb (अगर required by driver).
	 */
	अगर ((entry->queue->qid == QID_BEACON) &&
	    (rt2x00_has_cap_flag(rt2x00dev, REQUIRE_BEACON_GUARD)))
		usb_समाप्त_urb(bcn_priv->guardian_urb);

	वापस false;
पूर्ण

व्योम rt2x00usb_flush_queue(काष्ठा data_queue *queue, bool drop)
अणु
	काष्ठा work_काष्ठा *completion;
	अचिन्हित पूर्णांक i;

	अगर (drop)
		rt2x00queue_क्रम_each_entry(queue, Q_INDEX_DONE, Q_INDEX, शून्य,
					   rt2x00usb_flush_entry);

	/*
	 * Obtain the queue completion handler
	 */
	चयन (queue->qid) अणु
	हाल QID_AC_VO:
	हाल QID_AC_VI:
	हाल QID_AC_BE:
	हाल QID_AC_BK:
		completion = &queue->rt2x00dev->txकरोne_work;
		अवरोध;
	हाल QID_RX:
		completion = &queue->rt2x00dev->rxकरोne_work;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	क्रम (i = 0; i < 10; i++) अणु
		/*
		 * Check अगर the driver is alपढ़ोy करोne, otherwise we
		 * have to sleep a little जबतक to give the driver/hw
		 * the oppurtunity to complete पूर्णांकerrupt process itself.
		 */
		अगर (rt2x00queue_empty(queue))
			अवरोध;

		/*
		 * Schedule the completion handler manually, when this
		 * worker function runs, it should cleanup the queue.
		 */
		queue_work(queue->rt2x00dev->workqueue, completion);

		/*
		 * Wait क्रम a little जबतक to give the driver
		 * the oppurtunity to recover itself.
		 */
		msleep(50);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00usb_flush_queue);

अटल व्योम rt2x00usb_watchकरोg_tx_dma(काष्ठा data_queue *queue)
अणु
	rt2x00_warn(queue->rt2x00dev, "TX queue %d DMA timed out, invoke forced reset\n",
		    queue->qid);

	rt2x00queue_stop_queue(queue);
	rt2x00queue_flush_queue(queue, true);
	rt2x00queue_start_queue(queue);
पूर्ण

अटल पूर्णांक rt2x00usb_dma_समयout(काष्ठा data_queue *queue)
अणु
	काष्ठा queue_entry *entry;

	entry = rt2x00queue_get_entry(queue, Q_INDEX_DMA_DONE);
	वापस rt2x00queue_dma_समयout(entry);
पूर्ण

व्योम rt2x00usb_watchकरोg(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा data_queue *queue;

	tx_queue_क्रम_each(rt2x00dev, queue) अणु
		अगर (!rt2x00queue_empty(queue)) अणु
			अगर (rt2x00usb_dma_समयout(queue))
				rt2x00usb_watchकरोg_tx_dma(queue);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00usb_watchकरोg);

/*
 * Radio handlers
 */
व्योम rt2x00usb_disable_radio(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	rt2x00usb_venकरोr_request_sw(rt2x00dev, USB_RX_CONTROL, 0, 0,
				    REGISTER_TIMEOUT);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00usb_disable_radio);

/*
 * Device initialization handlers.
 */
व्योम rt2x00usb_clear_entry(काष्ठा queue_entry *entry)
अणु
	entry->flags = 0;

	अगर (entry->queue->qid == QID_RX)
		rt2x00usb_kick_rx_entry(entry, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00usb_clear_entry);

अटल व्योम rt2x00usb_assign_endpoपूर्णांक(काष्ठा data_queue *queue,
				      काष्ठा usb_endpoपूर्णांक_descriptor *ep_desc)
अणु
	काष्ठा usb_device *usb_dev = to_usb_device_पूर्णांकf(queue->rt2x00dev->dev);
	पूर्णांक pipe;

	queue->usb_endpoपूर्णांक = usb_endpoपूर्णांक_num(ep_desc);

	अगर (queue->qid == QID_RX) अणु
		pipe = usb_rcvbulkpipe(usb_dev, queue->usb_endpoपूर्णांक);
		queue->usb_maxpacket = usb_maxpacket(usb_dev, pipe, 0);
	पूर्ण अन्यथा अणु
		pipe = usb_sndbulkpipe(usb_dev, queue->usb_endpoपूर्णांक);
		queue->usb_maxpacket = usb_maxpacket(usb_dev, pipe, 1);
	पूर्ण

	अगर (!queue->usb_maxpacket)
		queue->usb_maxpacket = 1;
पूर्ण

अटल पूर्णांक rt2x00usb_find_endpoपूर्णांकs(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(rt2x00dev->dev);
	काष्ठा usb_host_पूर्णांकerface *पूर्णांकf_desc = पूर्णांकf->cur_altsetting;
	काष्ठा usb_endpoपूर्णांक_descriptor *ep_desc;
	काष्ठा data_queue *queue = rt2x00dev->tx;
	काष्ठा usb_endpoपूर्णांक_descriptor *tx_ep_desc = शून्य;
	अचिन्हित पूर्णांक i;

	/*
	 * Walk through all available endpoपूर्णांकs to search क्रम "bulk in"
	 * and "bulk out" endpoपूर्णांकs. When we find such endpoपूर्णांकs collect
	 * the inक्रमmation we need from the descriptor and assign it
	 * to the queue.
	 */
	क्रम (i = 0; i < पूर्णांकf_desc->desc.bNumEndpoपूर्णांकs; i++) अणु
		ep_desc = &पूर्णांकf_desc->endpoपूर्णांक[i].desc;

		अगर (usb_endpoपूर्णांक_is_bulk_in(ep_desc)) अणु
			rt2x00usb_assign_endpoपूर्णांक(rt2x00dev->rx, ep_desc);
		पूर्ण अन्यथा अगर (usb_endpoपूर्णांक_is_bulk_out(ep_desc) &&
			   (queue != queue_end(rt2x00dev))) अणु
			rt2x00usb_assign_endpoपूर्णांक(queue, ep_desc);
			queue = queue_next(queue);

			tx_ep_desc = ep_desc;
		पूर्ण
	पूर्ण

	/*
	 * At least 1 endpoपूर्णांक क्रम RX and 1 endpoपूर्णांक क्रम TX must be available.
	 */
	अगर (!rt2x00dev->rx->usb_endpoपूर्णांक || !rt2x00dev->tx->usb_endpoपूर्णांक) अणु
		rt2x00_err(rt2x00dev, "Bulk-in/Bulk-out endpoints not found\n");
		वापस -EPIPE;
	पूर्ण

	/*
	 * It might be possible not all queues have a dedicated endpoपूर्णांक.
	 * Loop through all TX queues and copy the endpoपूर्णांक inक्रमmation
	 * which we have gathered from alपढ़ोy asचिन्हित endpoपूर्णांकs.
	 */
	txall_queue_क्रम_each(rt2x00dev, queue) अणु
		अगर (!queue->usb_endpoपूर्णांक)
			rt2x00usb_assign_endpoपूर्णांक(queue, tx_ep_desc);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt2x00usb_alloc_entries(काष्ठा data_queue *queue)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = queue->rt2x00dev;
	काष्ठा queue_entry_priv_usb *entry_priv;
	काष्ठा queue_entry_priv_usb_bcn *bcn_priv;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < queue->limit; i++) अणु
		entry_priv = queue->entries[i].priv_data;
		entry_priv->urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!entry_priv->urb)
			वापस -ENOMEM;
	पूर्ण

	/*
	 * If this is not the beacon queue or
	 * no guardian byte was required क्रम the beacon,
	 * then we are करोne.
	 */
	अगर (queue->qid != QID_BEACON ||
	    !rt2x00_has_cap_flag(rt2x00dev, REQUIRE_BEACON_GUARD))
		वापस 0;

	क्रम (i = 0; i < queue->limit; i++) अणु
		bcn_priv = queue->entries[i].priv_data;
		bcn_priv->guardian_urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!bcn_priv->guardian_urb)
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rt2x00usb_मुक्त_entries(काष्ठा data_queue *queue)
अणु
	काष्ठा rt2x00_dev *rt2x00dev = queue->rt2x00dev;
	काष्ठा queue_entry_priv_usb *entry_priv;
	काष्ठा queue_entry_priv_usb_bcn *bcn_priv;
	अचिन्हित पूर्णांक i;

	अगर (!queue->entries)
		वापस;

	क्रम (i = 0; i < queue->limit; i++) अणु
		entry_priv = queue->entries[i].priv_data;
		usb_समाप्त_urb(entry_priv->urb);
		usb_मुक्त_urb(entry_priv->urb);
	पूर्ण

	/*
	 * If this is not the beacon queue or
	 * no guardian byte was required क्रम the beacon,
	 * then we are करोne.
	 */
	अगर (queue->qid != QID_BEACON ||
	    !rt2x00_has_cap_flag(rt2x00dev, REQUIRE_BEACON_GUARD))
		वापस;

	क्रम (i = 0; i < queue->limit; i++) अणु
		bcn_priv = queue->entries[i].priv_data;
		usb_समाप्त_urb(bcn_priv->guardian_urb);
		usb_मुक्त_urb(bcn_priv->guardian_urb);
	पूर्ण
पूर्ण

पूर्णांक rt2x00usb_initialize(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा data_queue *queue;
	पूर्णांक status;

	/*
	 * Find endpoपूर्णांकs क्रम each queue
	 */
	status = rt2x00usb_find_endpoपूर्णांकs(rt2x00dev);
	अगर (status)
		जाओ निकास;

	/*
	 * Allocate DMA
	 */
	queue_क्रम_each(rt2x00dev, queue) अणु
		status = rt2x00usb_alloc_entries(queue);
		अगर (status)
			जाओ निकास;
	पूर्ण

	वापस 0;

निकास:
	rt2x00usb_uninitialize(rt2x00dev);

	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00usb_initialize);

व्योम rt2x00usb_uninitialize(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा data_queue *queue;

	usb_समाप्त_anchored_urbs(rt2x00dev->anchor);
	hrसमयr_cancel(&rt2x00dev->txstatus_समयr);
	cancel_work_sync(&rt2x00dev->rxकरोne_work);
	cancel_work_sync(&rt2x00dev->txकरोne_work);

	queue_क्रम_each(rt2x00dev, queue)
		rt2x00usb_मुक्त_entries(queue);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00usb_uninitialize);

/*
 * USB driver handlers.
 */
अटल व्योम rt2x00usb_मुक्त_reg(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	kमुक्त(rt2x00dev->rf);
	rt2x00dev->rf = शून्य;

	kमुक्त(rt2x00dev->eeprom);
	rt2x00dev->eeprom = शून्य;

	kमुक्त(rt2x00dev->csr.cache);
	rt2x00dev->csr.cache = शून्य;
पूर्ण

अटल पूर्णांक rt2x00usb_alloc_reg(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	rt2x00dev->csr.cache = kzalloc(CSR_CACHE_SIZE, GFP_KERNEL);
	अगर (!rt2x00dev->csr.cache)
		जाओ निकास;

	rt2x00dev->eeprom = kzalloc(rt2x00dev->ops->eeprom_size, GFP_KERNEL);
	अगर (!rt2x00dev->eeprom)
		जाओ निकास;

	rt2x00dev->rf = kzalloc(rt2x00dev->ops->rf_size, GFP_KERNEL);
	अगर (!rt2x00dev->rf)
		जाओ निकास;

	वापस 0;

निकास:
	rt2x00_probe_err("Failed to allocate registers\n");

	rt2x00usb_मुक्त_reg(rt2x00dev);

	वापस -ENOMEM;
पूर्ण

पूर्णांक rt2x00usb_probe(काष्ठा usb_पूर्णांकerface *usb_पूर्णांकf,
		    स्थिर काष्ठा rt2x00_ops *ops)
अणु
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(usb_पूर्णांकf);
	काष्ठा ieee80211_hw *hw;
	काष्ठा rt2x00_dev *rt2x00dev;
	पूर्णांक retval;

	usb_dev = usb_get_dev(usb_dev);
	usb_reset_device(usb_dev);

	hw = ieee80211_alloc_hw(माप(काष्ठा rt2x00_dev), ops->hw);
	अगर (!hw) अणु
		rt2x00_probe_err("Failed to allocate hardware\n");
		retval = -ENOMEM;
		जाओ निकास_put_device;
	पूर्ण

	usb_set_पूर्णांकfdata(usb_पूर्णांकf, hw);

	rt2x00dev = hw->priv;
	rt2x00dev->dev = &usb_पूर्णांकf->dev;
	rt2x00dev->ops = ops;
	rt2x00dev->hw = hw;

	rt2x00_set_chip_पूर्णांकf(rt2x00dev, RT2X00_CHIP_INTF_USB);

	INIT_WORK(&rt2x00dev->rxकरोne_work, rt2x00usb_work_rxकरोne);
	INIT_WORK(&rt2x00dev->txकरोne_work, rt2x00usb_work_txकरोne);
	hrसमयr_init(&rt2x00dev->txstatus_समयr, CLOCK_MONOTONIC,
		     HRTIMER_MODE_REL);

	retval = rt2x00usb_alloc_reg(rt2x00dev);
	अगर (retval)
		जाओ निकास_मुक्त_device;

	rt2x00dev->anchor = devm_kदो_स्मृति(&usb_dev->dev,
					माप(काष्ठा usb_anchor),
					GFP_KERNEL);
	अगर (!rt2x00dev->anchor) अणु
		retval = -ENOMEM;
		जाओ निकास_मुक्त_reg;
	पूर्ण
	init_usb_anchor(rt2x00dev->anchor);

	retval = rt2x00lib_probe_dev(rt2x00dev);
	अगर (retval)
		जाओ निकास_मुक्त_anchor;

	वापस 0;

निकास_मुक्त_anchor:
	usb_समाप्त_anchored_urbs(rt2x00dev->anchor);

निकास_मुक्त_reg:
	rt2x00usb_मुक्त_reg(rt2x00dev);

निकास_मुक्त_device:
	ieee80211_मुक्त_hw(hw);

निकास_put_device:
	usb_put_dev(usb_dev);

	usb_set_पूर्णांकfdata(usb_पूर्णांकf, शून्य);

	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00usb_probe);

व्योम rt2x00usb_disconnect(काष्ठा usb_पूर्णांकerface *usb_पूर्णांकf)
अणु
	काष्ठा ieee80211_hw *hw = usb_get_पूर्णांकfdata(usb_पूर्णांकf);
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;

	/*
	 * Free all allocated data.
	 */
	rt2x00lib_हटाओ_dev(rt2x00dev);
	rt2x00usb_मुक्त_reg(rt2x00dev);
	ieee80211_मुक्त_hw(hw);

	/*
	 * Free the USB device data.
	 */
	usb_set_पूर्णांकfdata(usb_पूर्णांकf, शून्य);
	usb_put_dev(पूर्णांकerface_to_usbdev(usb_पूर्णांकf));
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00usb_disconnect);

#अगर_घोषित CONFIG_PM
पूर्णांक rt2x00usb_suspend(काष्ठा usb_पूर्णांकerface *usb_पूर्णांकf, pm_message_t state)
अणु
	काष्ठा ieee80211_hw *hw = usb_get_पूर्णांकfdata(usb_पूर्णांकf);
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;

	वापस rt2x00lib_suspend(rt2x00dev);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00usb_suspend);

पूर्णांक rt2x00usb_resume(काष्ठा usb_पूर्णांकerface *usb_पूर्णांकf)
अणु
	काष्ठा ieee80211_hw *hw = usb_get_पूर्णांकfdata(usb_पूर्णांकf);
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;

	वापस rt2x00lib_resume(rt2x00dev);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00usb_resume);
#पूर्ण_अगर /* CONFIG_PM */

/*
 * rt2x00usb module inक्रमmation.
 */
MODULE_AUTHOR(DRV_PROJECT);
MODULE_VERSION(DRV_VERSION);
MODULE_DESCRIPTION("rt2x00 usb library");
MODULE_LICENSE("GPL");
