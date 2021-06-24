<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2018 Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश "mt76.h"
#समावेश "usb_trace.h"
#समावेश "dma.h"

#घोषणा MT_VEND_REQ_MAX_RETRY	10
#घोषणा MT_VEND_REQ_TOUT_MS	300

अटल bool disable_usb_sg;
module_param_named(disable_usb_sg, disable_usb_sg, bool, 0644);
MODULE_PARM_DESC(disable_usb_sg, "Disable usb scatter-gather support");

अटल पूर्णांक __mt76u_venकरोr_request(काष्ठा mt76_dev *dev, u8 req,
				  u8 req_type, u16 val, u16 offset,
				  व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा usb_पूर्णांकerface *uपूर्णांकf = to_usb_पूर्णांकerface(dev->dev);
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(uपूर्णांकf);
	अचिन्हित पूर्णांक pipe;
	पूर्णांक i, ret;

	lockdep_निश्चित_held(&dev->usb.usb_ctrl_mtx);

	pipe = (req_type & USB_सूची_IN) ? usb_rcvctrlpipe(udev, 0)
				       : usb_sndctrlpipe(udev, 0);
	क्रम (i = 0; i < MT_VEND_REQ_MAX_RETRY; i++) अणु
		अगर (test_bit(MT76_REMOVED, &dev->phy.state))
			वापस -EIO;

		ret = usb_control_msg(udev, pipe, req, req_type, val,
				      offset, buf, len, MT_VEND_REQ_TOUT_MS);
		अगर (ret == -ENODEV)
			set_bit(MT76_REMOVED, &dev->phy.state);
		अगर (ret >= 0 || ret == -ENODEV)
			वापस ret;
		usleep_range(5000, 10000);
	पूर्ण

	dev_err(dev->dev, "vendor request req:%02x off:%04x failed:%d\n",
		req, offset, ret);
	वापस ret;
पूर्ण

पूर्णांक mt76u_venकरोr_request(काष्ठा mt76_dev *dev, u8 req,
			 u8 req_type, u16 val, u16 offset,
			 व्योम *buf, माप_प्रकार len)
अणु
	पूर्णांक ret;

	mutex_lock(&dev->usb.usb_ctrl_mtx);
	ret = __mt76u_venकरोr_request(dev, req, req_type,
				     val, offset, buf, len);
	trace_usb_reg_wr(dev, offset, val);
	mutex_unlock(&dev->usb.usb_ctrl_mtx);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mt76u_venकरोr_request);

अटल u32 ___mt76u_rr(काष्ठा mt76_dev *dev, u8 req, u32 addr)
अणु
	काष्ठा mt76_usb *usb = &dev->usb;
	u32 data = ~0;
	पूर्णांक ret;

	ret = __mt76u_venकरोr_request(dev, req,
				     USB_सूची_IN | USB_TYPE_VENDOR,
				     addr >> 16, addr, usb->data,
				     माप(__le32));
	अगर (ret == माप(__le32))
		data = get_unaligned_le32(usb->data);
	trace_usb_reg_rr(dev, addr, data);

	वापस data;
पूर्ण

अटल u32 __mt76u_rr(काष्ठा mt76_dev *dev, u32 addr)
अणु
	u8 req;

	चयन (addr & MT_VEND_TYPE_MASK) अणु
	हाल MT_VEND_TYPE_EEPROM:
		req = MT_VEND_READ_EEPROM;
		अवरोध;
	हाल MT_VEND_TYPE_CFG:
		req = MT_VEND_READ_CFG;
		अवरोध;
	शेष:
		req = MT_VEND_MULTI_READ;
		अवरोध;
	पूर्ण

	वापस ___mt76u_rr(dev, req, addr & ~MT_VEND_TYPE_MASK);
पूर्ण

अटल u32 mt76u_rr(काष्ठा mt76_dev *dev, u32 addr)
अणु
	u32 ret;

	mutex_lock(&dev->usb.usb_ctrl_mtx);
	ret = __mt76u_rr(dev, addr);
	mutex_unlock(&dev->usb.usb_ctrl_mtx);

	वापस ret;
पूर्ण

अटल u32 mt76u_rr_ext(काष्ठा mt76_dev *dev, u32 addr)
अणु
	u32 ret;

	mutex_lock(&dev->usb.usb_ctrl_mtx);
	ret = ___mt76u_rr(dev, MT_VEND_READ_EXT, addr);
	mutex_unlock(&dev->usb.usb_ctrl_mtx);

	वापस ret;
पूर्ण

अटल व्योम ___mt76u_wr(काष्ठा mt76_dev *dev, u8 req,
			u32 addr, u32 val)
अणु
	काष्ठा mt76_usb *usb = &dev->usb;

	put_unaligned_le32(val, usb->data);
	__mt76u_venकरोr_request(dev, req,
			       USB_सूची_OUT | USB_TYPE_VENDOR,
			       addr >> 16, addr, usb->data,
			       माप(__le32));
	trace_usb_reg_wr(dev, addr, val);
पूर्ण

अटल व्योम __mt76u_wr(काष्ठा mt76_dev *dev, u32 addr, u32 val)
अणु
	u8 req;

	चयन (addr & MT_VEND_TYPE_MASK) अणु
	हाल MT_VEND_TYPE_CFG:
		req = MT_VEND_WRITE_CFG;
		अवरोध;
	शेष:
		req = MT_VEND_MULTI_WRITE;
		अवरोध;
	पूर्ण
	___mt76u_wr(dev, req, addr & ~MT_VEND_TYPE_MASK, val);
पूर्ण

अटल व्योम mt76u_wr(काष्ठा mt76_dev *dev, u32 addr, u32 val)
अणु
	mutex_lock(&dev->usb.usb_ctrl_mtx);
	__mt76u_wr(dev, addr, val);
	mutex_unlock(&dev->usb.usb_ctrl_mtx);
पूर्ण

अटल व्योम mt76u_wr_ext(काष्ठा mt76_dev *dev, u32 addr, u32 val)
अणु
	mutex_lock(&dev->usb.usb_ctrl_mtx);
	___mt76u_wr(dev, MT_VEND_WRITE_EXT, addr, val);
	mutex_unlock(&dev->usb.usb_ctrl_mtx);
पूर्ण

अटल u32 mt76u_rmw(काष्ठा mt76_dev *dev, u32 addr,
		     u32 mask, u32 val)
अणु
	mutex_lock(&dev->usb.usb_ctrl_mtx);
	val |= __mt76u_rr(dev, addr) & ~mask;
	__mt76u_wr(dev, addr, val);
	mutex_unlock(&dev->usb.usb_ctrl_mtx);

	वापस val;
पूर्ण

अटल u32 mt76u_rmw_ext(काष्ठा mt76_dev *dev, u32 addr,
			 u32 mask, u32 val)
अणु
	mutex_lock(&dev->usb.usb_ctrl_mtx);
	val |= ___mt76u_rr(dev, MT_VEND_READ_EXT, addr) & ~mask;
	___mt76u_wr(dev, MT_VEND_WRITE_EXT, addr, val);
	mutex_unlock(&dev->usb.usb_ctrl_mtx);

	वापस val;
पूर्ण

अटल व्योम mt76u_copy(काष्ठा mt76_dev *dev, u32 offset,
		       स्थिर व्योम *data, पूर्णांक len)
अणु
	काष्ठा mt76_usb *usb = &dev->usb;
	स्थिर u8 *val = data;
	पूर्णांक ret;
	पूर्णांक current_batch_size;
	पूर्णांक i = 0;

	/* Assure that always a multiple of 4 bytes are copied,
	 * otherwise beacons can be corrupted.
	 * See: "mt76: round up length on mt76_wr_copy"
	 * Commit 850e8f6fbd5d0003b0
	 */
	len = round_up(len, 4);

	mutex_lock(&usb->usb_ctrl_mtx);
	जबतक (i < len) अणु
		current_batch_size = min_t(पूर्णांक, usb->data_len, len - i);
		स_नकल(usb->data, val + i, current_batch_size);
		ret = __mt76u_venकरोr_request(dev, MT_VEND_MULTI_WRITE,
					     USB_सूची_OUT | USB_TYPE_VENDOR,
					     0, offset + i, usb->data,
					     current_batch_size);
		अगर (ret < 0)
			अवरोध;

		i += current_batch_size;
	पूर्ण
	mutex_unlock(&usb->usb_ctrl_mtx);
पूर्ण

अटल व्योम mt76u_copy_ext(काष्ठा mt76_dev *dev, u32 offset,
			   स्थिर व्योम *data, पूर्णांक len)
अणु
	काष्ठा mt76_usb *usb = &dev->usb;
	पूर्णांक ret, i = 0, batch_len;
	स्थिर u8 *val = data;

	len = round_up(len, 4);
	mutex_lock(&usb->usb_ctrl_mtx);
	जबतक (i < len) अणु
		batch_len = min_t(पूर्णांक, usb->data_len, len - i);
		स_नकल(usb->data, val + i, batch_len);
		ret = __mt76u_venकरोr_request(dev, MT_VEND_WRITE_EXT,
					     USB_सूची_OUT | USB_TYPE_VENDOR,
					     (offset + i) >> 16, offset + i,
					     usb->data, batch_len);
		अगर (ret < 0)
			अवरोध;

		i += batch_len;
	पूर्ण
	mutex_unlock(&usb->usb_ctrl_mtx);
पूर्ण

अटल व्योम
mt76u_पढ़ो_copy_ext(काष्ठा mt76_dev *dev, u32 offset,
		    व्योम *data, पूर्णांक len)
अणु
	काष्ठा mt76_usb *usb = &dev->usb;
	पूर्णांक i = 0, batch_len, ret;
	u8 *val = data;

	len = round_up(len, 4);
	mutex_lock(&usb->usb_ctrl_mtx);
	जबतक (i < len) अणु
		batch_len = min_t(पूर्णांक, usb->data_len, len - i);
		ret = __mt76u_venकरोr_request(dev, MT_VEND_READ_EXT,
					     USB_सूची_IN | USB_TYPE_VENDOR,
					     (offset + i) >> 16, offset + i,
					     usb->data, batch_len);
		अगर (ret < 0)
			अवरोध;

		स_नकल(val + i, usb->data, batch_len);
		i += batch_len;
	पूर्ण
	mutex_unlock(&usb->usb_ctrl_mtx);
पूर्ण

व्योम mt76u_single_wr(काष्ठा mt76_dev *dev, स्थिर u8 req,
		     स्थिर u16 offset, स्थिर u32 val)
अणु
	mutex_lock(&dev->usb.usb_ctrl_mtx);
	__mt76u_venकरोr_request(dev, req,
			       USB_सूची_OUT | USB_TYPE_VENDOR,
			       val & 0xffff, offset, शून्य, 0);
	__mt76u_venकरोr_request(dev, req,
			       USB_सूची_OUT | USB_TYPE_VENDOR,
			       val >> 16, offset + 2, शून्य, 0);
	mutex_unlock(&dev->usb.usb_ctrl_mtx);
पूर्ण
EXPORT_SYMBOL_GPL(mt76u_single_wr);

अटल पूर्णांक
mt76u_req_wr_rp(काष्ठा mt76_dev *dev, u32 base,
		स्थिर काष्ठा mt76_reg_pair *data, पूर्णांक len)
अणु
	काष्ठा mt76_usb *usb = &dev->usb;

	mutex_lock(&usb->usb_ctrl_mtx);
	जबतक (len > 0) अणु
		__mt76u_wr(dev, base + data->reg, data->value);
		len--;
		data++;
	पूर्ण
	mutex_unlock(&usb->usb_ctrl_mtx);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt76u_wr_rp(काष्ठा mt76_dev *dev, u32 base,
	    स्थिर काष्ठा mt76_reg_pair *data, पूर्णांक n)
अणु
	अगर (test_bit(MT76_STATE_MCU_RUNNING, &dev->phy.state))
		वापस dev->mcu_ops->mcu_wr_rp(dev, base, data, n);
	अन्यथा
		वापस mt76u_req_wr_rp(dev, base, data, n);
पूर्ण

अटल पूर्णांक
mt76u_req_rd_rp(काष्ठा mt76_dev *dev, u32 base, काष्ठा mt76_reg_pair *data,
		पूर्णांक len)
अणु
	काष्ठा mt76_usb *usb = &dev->usb;

	mutex_lock(&usb->usb_ctrl_mtx);
	जबतक (len > 0) अणु
		data->value = __mt76u_rr(dev, base + data->reg);
		len--;
		data++;
	पूर्ण
	mutex_unlock(&usb->usb_ctrl_mtx);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt76u_rd_rp(काष्ठा mt76_dev *dev, u32 base,
	    काष्ठा mt76_reg_pair *data, पूर्णांक n)
अणु
	अगर (test_bit(MT76_STATE_MCU_RUNNING, &dev->phy.state))
		वापस dev->mcu_ops->mcu_rd_rp(dev, base, data, n);
	अन्यथा
		वापस mt76u_req_rd_rp(dev, base, data, n);
पूर्ण

अटल bool mt76u_check_sg(काष्ठा mt76_dev *dev)
अणु
	काष्ठा usb_पूर्णांकerface *uपूर्णांकf = to_usb_पूर्णांकerface(dev->dev);
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(uपूर्णांकf);

	वापस (!disable_usb_sg && udev->bus->sg_tablesize > 0 &&
		(udev->bus->no_sg_स्थिरraपूर्णांक ||
		 udev->speed == USB_SPEED_WIRELESS));
पूर्ण

अटल पूर्णांक
mt76u_set_endpoपूर्णांकs(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		    काष्ठा mt76_usb *usb)
अणु
	काष्ठा usb_host_पूर्णांकerface *पूर्णांकf_desc = पूर्णांकf->cur_altsetting;
	काष्ठा usb_endpoपूर्णांक_descriptor *ep_desc;
	पूर्णांक i, in_ep = 0, out_ep = 0;

	क्रम (i = 0; i < पूर्णांकf_desc->desc.bNumEndpoपूर्णांकs; i++) अणु
		ep_desc = &पूर्णांकf_desc->endpoपूर्णांक[i].desc;

		अगर (usb_endpoपूर्णांक_is_bulk_in(ep_desc) &&
		    in_ep < __MT_EP_IN_MAX) अणु
			usb->in_ep[in_ep] = usb_endpoपूर्णांक_num(ep_desc);
			in_ep++;
		पूर्ण अन्यथा अगर (usb_endpoपूर्णांक_is_bulk_out(ep_desc) &&
			   out_ep < __MT_EP_OUT_MAX) अणु
			usb->out_ep[out_ep] = usb_endpoपूर्णांक_num(ep_desc);
			out_ep++;
		पूर्ण
	पूर्ण

	अगर (in_ep != __MT_EP_IN_MAX || out_ep != __MT_EP_OUT_MAX)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक
mt76u_fill_rx_sg(काष्ठा mt76_dev *dev, काष्ठा mt76_queue *q, काष्ठा urb *urb,
		 पूर्णांक nsgs, gfp_t gfp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nsgs; i++) अणु
		काष्ठा page *page;
		व्योम *data;
		पूर्णांक offset;

		data = page_frag_alloc(&q->rx_page, q->buf_size, gfp);
		अगर (!data)
			अवरोध;

		page = virt_to_head_page(data);
		offset = data - page_address(page);
		sg_set_page(&urb->sg[i], page, q->buf_size, offset);
	पूर्ण

	अगर (i < nsgs) अणु
		पूर्णांक j;

		क्रम (j = nsgs; j < urb->num_sgs; j++)
			skb_मुक्त_frag(sg_virt(&urb->sg[j]));
		urb->num_sgs = i;
	पूर्ण

	urb->num_sgs = max_t(पूर्णांक, i, urb->num_sgs);
	urb->transfer_buffer_length = urb->num_sgs * q->buf_size;
	sg_init_marker(urb->sg, urb->num_sgs);

	वापस i ? : -ENOMEM;
पूर्ण

अटल पूर्णांक
mt76u_refill_rx(काष्ठा mt76_dev *dev, काष्ठा mt76_queue *q,
		काष्ठा urb *urb, पूर्णांक nsgs, gfp_t gfp)
अणु
	क्रमागत mt76_rxq_id qid = q - &dev->q_rx[MT_RXQ_MAIN];

	अगर (qid == MT_RXQ_MAIN && dev->usb.sg_en)
		वापस mt76u_fill_rx_sg(dev, q, urb, nsgs, gfp);

	urb->transfer_buffer_length = q->buf_size;
	urb->transfer_buffer = page_frag_alloc(&q->rx_page, q->buf_size, gfp);

	वापस urb->transfer_buffer ? 0 : -ENOMEM;
पूर्ण

अटल पूर्णांक
mt76u_urb_alloc(काष्ठा mt76_dev *dev, काष्ठा mt76_queue_entry *e,
		पूर्णांक sg_max_size)
अणु
	अचिन्हित पूर्णांक size = माप(काष्ठा urb);

	अगर (dev->usb.sg_en)
		size += sg_max_size * माप(काष्ठा scatterlist);

	e->urb = kzalloc(size, GFP_KERNEL);
	अगर (!e->urb)
		वापस -ENOMEM;

	usb_init_urb(e->urb);

	अगर (dev->usb.sg_en && sg_max_size > 0)
		e->urb->sg = (काष्ठा scatterlist *)(e->urb + 1);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt76u_rx_urb_alloc(काष्ठा mt76_dev *dev, काष्ठा mt76_queue *q,
		   काष्ठा mt76_queue_entry *e)
अणु
	क्रमागत mt76_rxq_id qid = q - &dev->q_rx[MT_RXQ_MAIN];
	पूर्णांक err, sg_size;

	sg_size = qid == MT_RXQ_MAIN ? MT_RX_SG_MAX_SIZE : 0;
	err = mt76u_urb_alloc(dev, e, sg_size);
	अगर (err)
		वापस err;

	वापस mt76u_refill_rx(dev, q, e->urb, sg_size, GFP_KERNEL);
पूर्ण

अटल व्योम mt76u_urb_मुक्त(काष्ठा urb *urb)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < urb->num_sgs; i++)
		skb_मुक्त_frag(sg_virt(&urb->sg[i]));

	अगर (urb->transfer_buffer)
		skb_मुक्त_frag(urb->transfer_buffer);

	usb_मुक्त_urb(urb);
पूर्ण

अटल व्योम
mt76u_fill_bulk_urb(काष्ठा mt76_dev *dev, पूर्णांक dir, पूर्णांक index,
		    काष्ठा urb *urb, usb_complete_t complete_fn,
		    व्योम *context)
अणु
	काष्ठा usb_पूर्णांकerface *uपूर्णांकf = to_usb_पूर्णांकerface(dev->dev);
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(uपूर्णांकf);
	अचिन्हित पूर्णांक pipe;

	अगर (dir == USB_सूची_IN)
		pipe = usb_rcvbulkpipe(udev, dev->usb.in_ep[index]);
	अन्यथा
		pipe = usb_sndbulkpipe(udev, dev->usb.out_ep[index]);

	urb->dev = udev;
	urb->pipe = pipe;
	urb->complete = complete_fn;
	urb->context = context;
पूर्ण

अटल काष्ठा urb *
mt76u_get_next_rx_entry(काष्ठा mt76_queue *q)
अणु
	काष्ठा urb *urb = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&q->lock, flags);
	अगर (q->queued > 0) अणु
		urb = q->entry[q->tail].urb;
		q->tail = (q->tail + 1) % q->ndesc;
		q->queued--;
	पूर्ण
	spin_unlock_irqrestore(&q->lock, flags);

	वापस urb;
पूर्ण

अटल पूर्णांक
mt76u_get_rx_entry_len(काष्ठा mt76_dev *dev, u8 *data,
		       u32 data_len)
अणु
	u16 dma_len, min_len;

	dma_len = get_unaligned_le16(data);
	अगर (dev->drv->drv_flags & MT_DRV_RX_DMA_HDR)
		वापस dma_len;

	min_len = MT_DMA_HDR_LEN + MT_RX_RXWI_LEN + MT_FCE_INFO_LEN;
	अगर (data_len < min_len || !dma_len ||
	    dma_len + MT_DMA_HDR_LEN > data_len ||
	    (dma_len & 0x3))
		वापस -EINVAL;
	वापस dma_len;
पूर्ण

अटल काष्ठा sk_buff *
mt76u_build_rx_skb(काष्ठा mt76_dev *dev, व्योम *data,
		   पूर्णांक len, पूर्णांक buf_size)
अणु
	पूर्णांक head_room, drv_flags = dev->drv->drv_flags;
	काष्ठा sk_buff *skb;

	head_room = drv_flags & MT_DRV_RX_DMA_HDR ? 0 : MT_DMA_HDR_LEN;
	अगर (SKB_WITH_OVERHEAD(buf_size) < head_room + len) अणु
		काष्ठा page *page;

		/* slow path, not enough space क्रम data and
		 * skb_shared_info
		 */
		skb = alloc_skb(MT_SKB_HEAD_LEN, GFP_ATOMIC);
		अगर (!skb)
			वापस शून्य;

		skb_put_data(skb, data + head_room, MT_SKB_HEAD_LEN);
		data += head_room + MT_SKB_HEAD_LEN;
		page = virt_to_head_page(data);
		skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags,
				page, data - page_address(page),
				len - MT_SKB_HEAD_LEN, buf_size);

		वापस skb;
	पूर्ण

	/* fast path */
	skb = build_skb(data, buf_size);
	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, head_room);
	__skb_put(skb, len);

	वापस skb;
पूर्ण

अटल पूर्णांक
mt76u_process_rx_entry(काष्ठा mt76_dev *dev, काष्ठा urb *urb,
		       पूर्णांक buf_size)
अणु
	u8 *data = urb->num_sgs ? sg_virt(&urb->sg[0]) : urb->transfer_buffer;
	पूर्णांक data_len = urb->num_sgs ? urb->sg[0].length : urb->actual_length;
	पूर्णांक len, nsgs = 1, head_room, drv_flags = dev->drv->drv_flags;
	काष्ठा sk_buff *skb;

	अगर (!test_bit(MT76_STATE_INITIALIZED, &dev->phy.state))
		वापस 0;

	len = mt76u_get_rx_entry_len(dev, data, urb->actual_length);
	अगर (len < 0)
		वापस 0;

	head_room = drv_flags & MT_DRV_RX_DMA_HDR ? 0 : MT_DMA_HDR_LEN;
	data_len = min_t(पूर्णांक, len, data_len - head_room);
	skb = mt76u_build_rx_skb(dev, data, data_len, buf_size);
	अगर (!skb)
		वापस 0;

	len -= data_len;
	जबतक (len > 0 && nsgs < urb->num_sgs) अणु
		data_len = min_t(पूर्णांक, len, urb->sg[nsgs].length);
		skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags,
				sg_page(&urb->sg[nsgs]),
				urb->sg[nsgs].offset, data_len,
				buf_size);
		len -= data_len;
		nsgs++;
	पूर्ण
	dev->drv->rx_skb(dev, MT_RXQ_MAIN, skb);

	वापस nsgs;
पूर्ण

अटल व्योम mt76u_complete_rx(काष्ठा urb *urb)
अणु
	काष्ठा mt76_dev *dev = dev_get_drvdata(&urb->dev->dev);
	काष्ठा mt76_queue *q = urb->context;
	अचिन्हित दीर्घ flags;

	trace_rx_urb(dev, urb);

	चयन (urb->status) अणु
	हाल -ECONNRESET:
	हाल -ESHUTDOWN:
	हाल -ENOENT:
	हाल -EPROTO:
		वापस;
	शेष:
		dev_err_ratelimited(dev->dev, "rx urb failed: %d\n",
				    urb->status);
		fallthrough;
	हाल 0:
		अवरोध;
	पूर्ण

	spin_lock_irqsave(&q->lock, flags);
	अगर (WARN_ONCE(q->entry[q->head].urb != urb, "rx urb mismatch"))
		जाओ out;

	q->head = (q->head + 1) % q->ndesc;
	q->queued++;
	mt76_worker_schedule(&dev->usb.rx_worker);
out:
	spin_unlock_irqrestore(&q->lock, flags);
पूर्ण

अटल पूर्णांक
mt76u_submit_rx_buf(काष्ठा mt76_dev *dev, क्रमागत mt76_rxq_id qid,
		    काष्ठा urb *urb)
अणु
	पूर्णांक ep = qid == MT_RXQ_MAIN ? MT_EP_IN_PKT_RX : MT_EP_IN_CMD_RESP;

	mt76u_fill_bulk_urb(dev, USB_सूची_IN, ep, urb,
			    mt76u_complete_rx, &dev->q_rx[qid]);
	trace_submit_urb(dev, urb);

	वापस usb_submit_urb(urb, GFP_ATOMIC);
पूर्ण

अटल व्योम
mt76u_process_rx_queue(काष्ठा mt76_dev *dev, काष्ठा mt76_queue *q)
अणु
	पूर्णांक qid = q - &dev->q_rx[MT_RXQ_MAIN];
	काष्ठा urb *urb;
	पूर्णांक err, count;

	जबतक (true) अणु
		urb = mt76u_get_next_rx_entry(q);
		अगर (!urb)
			अवरोध;

		count = mt76u_process_rx_entry(dev, urb, q->buf_size);
		अगर (count > 0) अणु
			err = mt76u_refill_rx(dev, q, urb, count, GFP_ATOMIC);
			अगर (err < 0)
				अवरोध;
		पूर्ण
		mt76u_submit_rx_buf(dev, qid, urb);
	पूर्ण
	अगर (qid == MT_RXQ_MAIN) अणु
		local_bh_disable();
		mt76_rx_poll_complete(dev, MT_RXQ_MAIN, शून्य);
		local_bh_enable();
	पूर्ण
पूर्ण

अटल व्योम mt76u_rx_worker(काष्ठा mt76_worker *w)
अणु
	काष्ठा mt76_usb *usb = container_of(w, काष्ठा mt76_usb, rx_worker);
	काष्ठा mt76_dev *dev = container_of(usb, काष्ठा mt76_dev, usb);
	पूर्णांक i;

	rcu_पढ़ो_lock();
	mt76_क्रम_each_q_rx(dev, i)
		mt76u_process_rx_queue(dev, &dev->q_rx[i]);
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक
mt76u_submit_rx_buffers(काष्ठा mt76_dev *dev, क्रमागत mt76_rxq_id qid)
अणु
	काष्ठा mt76_queue *q = &dev->q_rx[qid];
	अचिन्हित दीर्घ flags;
	पूर्णांक i, err = 0;

	spin_lock_irqsave(&q->lock, flags);
	क्रम (i = 0; i < q->ndesc; i++) अणु
		err = mt76u_submit_rx_buf(dev, qid, q->entry[i].urb);
		अगर (err < 0)
			अवरोध;
	पूर्ण
	q->head = q->tail = 0;
	q->queued = 0;
	spin_unlock_irqrestore(&q->lock, flags);

	वापस err;
पूर्ण

अटल पूर्णांक
mt76u_alloc_rx_queue(काष्ठा mt76_dev *dev, क्रमागत mt76_rxq_id qid)
अणु
	काष्ठा mt76_queue *q = &dev->q_rx[qid];
	पूर्णांक i, err;

	spin_lock_init(&q->lock);
	q->entry = devm_kसुस्मृति(dev->dev,
				MT_NUM_RX_ENTRIES, माप(*q->entry),
				GFP_KERNEL);
	अगर (!q->entry)
		वापस -ENOMEM;

	q->ndesc = MT_NUM_RX_ENTRIES;
	q->buf_size = PAGE_SIZE;

	क्रम (i = 0; i < q->ndesc; i++) अणु
		err = mt76u_rx_urb_alloc(dev, q, &q->entry[i]);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस mt76u_submit_rx_buffers(dev, qid);
पूर्ण

पूर्णांक mt76u_alloc_mcu_queue(काष्ठा mt76_dev *dev)
अणु
	वापस mt76u_alloc_rx_queue(dev, MT_RXQ_MCU);
पूर्ण
EXPORT_SYMBOL_GPL(mt76u_alloc_mcu_queue);

अटल व्योम
mt76u_मुक्त_rx_queue(काष्ठा mt76_dev *dev, काष्ठा mt76_queue *q)
अणु
	काष्ठा page *page;
	पूर्णांक i;

	क्रम (i = 0; i < q->ndesc; i++) अणु
		अगर (!q->entry[i].urb)
			जारी;

		mt76u_urb_मुक्त(q->entry[i].urb);
		q->entry[i].urb = शून्य;
	पूर्ण

	अगर (!q->rx_page.va)
		वापस;

	page = virt_to_page(q->rx_page.va);
	__page_frag_cache_drain(page, q->rx_page.pagecnt_bias);
	स_रखो(&q->rx_page, 0, माप(q->rx_page));
पूर्ण

अटल व्योम mt76u_मुक्त_rx(काष्ठा mt76_dev *dev)
अणु
	पूर्णांक i;

	mt76_worker_tearकरोwn(&dev->usb.rx_worker);

	mt76_क्रम_each_q_rx(dev, i)
		mt76u_मुक्त_rx_queue(dev, &dev->q_rx[i]);
पूर्ण

व्योम mt76u_stop_rx(काष्ठा mt76_dev *dev)
अणु
	पूर्णांक i;

	mt76_worker_disable(&dev->usb.rx_worker);

	mt76_क्रम_each_q_rx(dev, i) अणु
		काष्ठा mt76_queue *q = &dev->q_rx[i];
		पूर्णांक j;

		क्रम (j = 0; j < q->ndesc; j++)
			usb_poison_urb(q->entry[j].urb);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mt76u_stop_rx);

पूर्णांक mt76u_resume_rx(काष्ठा mt76_dev *dev)
अणु
	पूर्णांक i;

	mt76_क्रम_each_q_rx(dev, i) अणु
		काष्ठा mt76_queue *q = &dev->q_rx[i];
		पूर्णांक err, j;

		क्रम (j = 0; j < q->ndesc; j++)
			usb_unpoison_urb(q->entry[j].urb);

		err = mt76u_submit_rx_buffers(dev, i);
		अगर (err < 0)
			वापस err;
	पूर्ण

	mt76_worker_enable(&dev->usb.rx_worker);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt76u_resume_rx);

अटल व्योम mt76u_status_worker(काष्ठा mt76_worker *w)
अणु
	काष्ठा mt76_usb *usb = container_of(w, काष्ठा mt76_usb, status_worker);
	काष्ठा mt76_dev *dev = container_of(usb, काष्ठा mt76_dev, usb);
	काष्ठा mt76_queue_entry entry;
	काष्ठा mt76_queue *q;
	पूर्णांक i;

	क्रम (i = 0; i < IEEE80211_NUM_ACS; i++) अणु
		q = dev->phy.q_tx[i];
		अगर (!q)
			जारी;

		जबतक (q->queued > 0) अणु
			अगर (!q->entry[q->tail].करोne)
				अवरोध;

			entry = q->entry[q->tail];
			q->entry[q->tail].करोne = false;

			mt76_queue_tx_complete(dev, q, &entry);
		पूर्ण

		अगर (!q->queued)
			wake_up(&dev->tx_रुको);

		mt76_worker_schedule(&dev->tx_worker);

		अगर (dev->drv->tx_status_data &&
		    !test_and_set_bit(MT76_READING_STATS, &dev->phy.state))
			queue_work(dev->wq, &dev->usb.stat_work);
	पूर्ण
पूर्ण

अटल व्योम mt76u_tx_status_data(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mt76_usb *usb;
	काष्ठा mt76_dev *dev;
	u8 update = 1;
	u16 count = 0;

	usb = container_of(work, काष्ठा mt76_usb, stat_work);
	dev = container_of(usb, काष्ठा mt76_dev, usb);

	जबतक (true) अणु
		अगर (test_bit(MT76_REMOVED, &dev->phy.state))
			अवरोध;

		अगर (!dev->drv->tx_status_data(dev, &update))
			अवरोध;
		count++;
	पूर्ण

	अगर (count && test_bit(MT76_STATE_RUNNING, &dev->phy.state))
		queue_work(dev->wq, &usb->stat_work);
	अन्यथा
		clear_bit(MT76_READING_STATS, &dev->phy.state);
पूर्ण

अटल व्योम mt76u_complete_tx(काष्ठा urb *urb)
अणु
	काष्ठा mt76_dev *dev = dev_get_drvdata(&urb->dev->dev);
	काष्ठा mt76_queue_entry *e = urb->context;

	अगर (mt76u_urb_error(urb))
		dev_err(dev->dev, "tx urb failed: %d\n", urb->status);
	e->करोne = true;

	mt76_worker_schedule(&dev->usb.status_worker);
पूर्ण

अटल पूर्णांक
mt76u_tx_setup_buffers(काष्ठा mt76_dev *dev, काष्ठा sk_buff *skb,
		       काष्ठा urb *urb)
अणु
	urb->transfer_buffer_length = skb->len;

	अगर (!dev->usb.sg_en) अणु
		urb->transfer_buffer = skb->data;
		वापस 0;
	पूर्ण

	sg_init_table(urb->sg, MT_TX_SG_MAX_SIZE);
	urb->num_sgs = skb_to_sgvec(skb, urb->sg, 0, skb->len);
	अगर (!urb->num_sgs)
		वापस -ENOMEM;

	वापस urb->num_sgs;
पूर्ण

अटल पूर्णांक
mt76u_tx_queue_skb(काष्ठा mt76_dev *dev, काष्ठा mt76_queue *q,
		   काष्ठा sk_buff *skb, काष्ठा mt76_wcid *wcid,
		   काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा mt76_tx_info tx_info = अणु
		.skb = skb,
	पूर्ण;
	u16 idx = q->head;
	पूर्णांक err;

	अगर (q->queued == q->ndesc)
		वापस -ENOSPC;

	skb->prev = skb->next = शून्य;
	err = dev->drv->tx_prepare_skb(dev, शून्य, q->qid, wcid, sta, &tx_info);
	अगर (err < 0)
		वापस err;

	err = mt76u_tx_setup_buffers(dev, tx_info.skb, q->entry[idx].urb);
	अगर (err < 0)
		वापस err;

	mt76u_fill_bulk_urb(dev, USB_सूची_OUT, q2ep(q->hw_idx),
			    q->entry[idx].urb, mt76u_complete_tx,
			    &q->entry[idx]);

	q->head = (q->head + 1) % q->ndesc;
	q->entry[idx].skb = tx_info.skb;
	q->queued++;

	वापस idx;
पूर्ण

अटल व्योम mt76u_tx_kick(काष्ठा mt76_dev *dev, काष्ठा mt76_queue *q)
अणु
	काष्ठा urb *urb;
	पूर्णांक err;

	जबतक (q->first != q->head) अणु
		urb = q->entry[q->first].urb;

		trace_submit_urb(dev, urb);
		err = usb_submit_urb(urb, GFP_ATOMIC);
		अगर (err < 0) अणु
			अगर (err == -ENODEV)
				set_bit(MT76_REMOVED, &dev->phy.state);
			अन्यथा
				dev_err(dev->dev, "tx urb submit failed:%d\n",
					err);
			अवरोध;
		पूर्ण
		q->first = (q->first + 1) % q->ndesc;
	पूर्ण
पूर्ण

अटल u8 mt76u_ac_to_hwq(काष्ठा mt76_dev *dev, u8 ac)
अणु
	अगर (mt76_chip(dev) == 0x7663) अणु
		अटल स्थिर u8 lmac_queue_map[] = अणु
			/* ac to lmac mapping */
			[IEEE80211_AC_BK] = 0,
			[IEEE80211_AC_BE] = 1,
			[IEEE80211_AC_VI] = 2,
			[IEEE80211_AC_VO] = 4,
		पूर्ण;

		अगर (WARN_ON(ac >= ARRAY_SIZE(lmac_queue_map)))
			वापस 1; /* BE */

		वापस lmac_queue_map[ac];
	पूर्ण

	वापस mt76_ac_to_hwq(ac);
पूर्ण

अटल पूर्णांक mt76u_alloc_tx(काष्ठा mt76_dev *dev)
अणु
	काष्ठा mt76_queue *q;
	पूर्णांक i, j, err;

	क्रम (i = 0; i <= MT_TXQ_PSD; i++) अणु
		अगर (i >= IEEE80211_NUM_ACS) अणु
			dev->phy.q_tx[i] = dev->phy.q_tx[0];
			जारी;
		पूर्ण

		q = devm_kzalloc(dev->dev, माप(*q), GFP_KERNEL);
		अगर (!q)
			वापस -ENOMEM;

		spin_lock_init(&q->lock);
		q->hw_idx = mt76u_ac_to_hwq(dev, i);
		q->qid = i;

		dev->phy.q_tx[i] = q;

		q->entry = devm_kसुस्मृति(dev->dev,
					MT_NUM_TX_ENTRIES, माप(*q->entry),
					GFP_KERNEL);
		अगर (!q->entry)
			वापस -ENOMEM;

		q->ndesc = MT_NUM_TX_ENTRIES;
		क्रम (j = 0; j < q->ndesc; j++) अणु
			err = mt76u_urb_alloc(dev, &q->entry[j],
					      MT_TX_SG_MAX_SIZE);
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम mt76u_मुक्त_tx(काष्ठा mt76_dev *dev)
अणु
	पूर्णांक i;

	mt76_worker_tearकरोwn(&dev->usb.status_worker);

	क्रम (i = 0; i < IEEE80211_NUM_ACS; i++) अणु
		काष्ठा mt76_queue *q;
		पूर्णांक j;

		q = dev->phy.q_tx[i];
		अगर (!q)
			जारी;

		क्रम (j = 0; j < q->ndesc; j++) अणु
			usb_मुक्त_urb(q->entry[j].urb);
			q->entry[j].urb = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

व्योम mt76u_stop_tx(काष्ठा mt76_dev *dev)
अणु
	पूर्णांक ret;

	mt76_worker_disable(&dev->usb.status_worker);

	ret = रुको_event_समयout(dev->tx_रुको, !mt76_has_tx_pending(&dev->phy),
				 HZ / 5);
	अगर (!ret) अणु
		काष्ठा mt76_queue_entry entry;
		काष्ठा mt76_queue *q;
		पूर्णांक i, j;

		dev_err(dev->dev, "timed out waiting for pending tx\n");

		क्रम (i = 0; i < IEEE80211_NUM_ACS; i++) अणु
			q = dev->phy.q_tx[i];
			अगर (!q)
				जारी;

			क्रम (j = 0; j < q->ndesc; j++)
				usb_समाप्त_urb(q->entry[j].urb);
		पूर्ण

		mt76_worker_disable(&dev->tx_worker);

		/* On device removal we maight queue skb's, but mt76u_tx_kick()
		 * will fail to submit urb, cleanup those skb's manually.
		 */
		क्रम (i = 0; i < IEEE80211_NUM_ACS; i++) अणु
			q = dev->phy.q_tx[i];
			अगर (!q)
				जारी;

			जबतक (q->queued > 0) अणु
				entry = q->entry[q->tail];
				q->entry[q->tail].करोne = false;
				mt76_queue_tx_complete(dev, q, &entry);
			पूर्ण
		पूर्ण

		mt76_worker_enable(&dev->tx_worker);
	पूर्ण

	cancel_work_sync(&dev->usb.stat_work);
	clear_bit(MT76_READING_STATS, &dev->phy.state);

	mt76_worker_enable(&dev->usb.status_worker);

	mt76_tx_status_check(dev, शून्य, true);
पूर्ण
EXPORT_SYMBOL_GPL(mt76u_stop_tx);

व्योम mt76u_queues_deinit(काष्ठा mt76_dev *dev)
अणु
	mt76u_stop_rx(dev);
	mt76u_stop_tx(dev);

	mt76u_मुक्त_rx(dev);
	mt76u_मुक्त_tx(dev);
पूर्ण
EXPORT_SYMBOL_GPL(mt76u_queues_deinit);

पूर्णांक mt76u_alloc_queues(काष्ठा mt76_dev *dev)
अणु
	पूर्णांक err;

	err = mt76u_alloc_rx_queue(dev, MT_RXQ_MAIN);
	अगर (err < 0)
		वापस err;

	वापस mt76u_alloc_tx(dev);
पूर्ण
EXPORT_SYMBOL_GPL(mt76u_alloc_queues);

अटल स्थिर काष्ठा mt76_queue_ops usb_queue_ops = अणु
	.tx_queue_skb = mt76u_tx_queue_skb,
	.kick = mt76u_tx_kick,
पूर्ण;

पूर्णांक mt76u_init(काष्ठा mt76_dev *dev,
	       काष्ठा usb_पूर्णांकerface *पूर्णांकf, bool ext)
अणु
	अटल काष्ठा mt76_bus_ops mt76u_ops = अणु
		.पढ़ो_copy = mt76u_पढ़ो_copy_ext,
		.wr_rp = mt76u_wr_rp,
		.rd_rp = mt76u_rd_rp,
		.type = MT76_BUS_USB,
	पूर्ण;
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा mt76_usb *usb = &dev->usb;
	पूर्णांक err;

	mt76u_ops.rr = ext ? mt76u_rr_ext : mt76u_rr;
	mt76u_ops.wr = ext ? mt76u_wr_ext : mt76u_wr;
	mt76u_ops.rmw = ext ? mt76u_rmw_ext : mt76u_rmw;
	mt76u_ops.ग_लिखो_copy = ext ? mt76u_copy_ext : mt76u_copy;

	INIT_WORK(&usb->stat_work, mt76u_tx_status_data);

	usb->data_len = usb_maxpacket(udev, usb_sndctrlpipe(udev, 0), 1);
	अगर (usb->data_len < 32)
		usb->data_len = 32;

	usb->data = devm_kदो_स्मृति(dev->dev, usb->data_len, GFP_KERNEL);
	अगर (!usb->data)
		वापस -ENOMEM;

	mutex_init(&usb->usb_ctrl_mtx);
	dev->bus = &mt76u_ops;
	dev->queue_ops = &usb_queue_ops;

	dev_set_drvdata(&udev->dev, dev);

	usb->sg_en = mt76u_check_sg(dev);

	err = mt76u_set_endpoपूर्णांकs(पूर्णांकf, usb);
	अगर (err < 0)
		वापस err;

	err = mt76_worker_setup(dev->hw, &usb->rx_worker, mt76u_rx_worker,
				"usb-rx");
	अगर (err)
		वापस err;

	err = mt76_worker_setup(dev->hw, &usb->status_worker,
				mt76u_status_worker, "usb-status");
	अगर (err)
		वापस err;

	sched_set_fअगरo_low(usb->rx_worker.task);
	sched_set_fअगरo_low(usb->status_worker.task);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt76u_init);

MODULE_AUTHOR("Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>");
MODULE_LICENSE("Dual BSD/GPL");
