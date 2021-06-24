<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Jakub Kicinski <kubakici@wp.pl>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>

#समावेश "mt7601u.h"
#समावेश "usb.h"
#समावेश "trace.h"

अटल स्थिर काष्ठा usb_device_id mt7601u_device_table[] = अणु
	अणु USB_DEVICE(0x0b05, 0x17d3) पूर्ण,
	अणु USB_DEVICE(0x0e8d, 0x760a) पूर्ण,
	अणु USB_DEVICE(0x0e8d, 0x760b) पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3431) पूर्ण,
	अणु USB_DEVICE(0x13d3, 0x3434) पूर्ण,
	अणु USB_DEVICE(0x148f, 0x7601) पूर्ण,
	अणु USB_DEVICE(0x148f, 0x760a) पूर्ण,
	अणु USB_DEVICE(0x148f, 0x760b) पूर्ण,
	अणु USB_DEVICE(0x148f, 0x760c) पूर्ण,
	अणु USB_DEVICE(0x148f, 0x760d) पूर्ण,
	अणु USB_DEVICE(0x2001, 0x3d04) पूर्ण,
	अणु USB_DEVICE(0x2717, 0x4106) पूर्ण,
	अणु USB_DEVICE(0x2955, 0x0001) पूर्ण,
	अणु USB_DEVICE(0x2955, 0x1001) पूर्ण,
	अणु USB_DEVICE(0x2a5f, 0x1000) पूर्ण,
	अणु USB_DEVICE(0x7392, 0x7710) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

bool mt7601u_usb_alloc_buf(काष्ठा mt7601u_dev *dev, माप_प्रकार len,
			   काष्ठा mt7601u_dma_buf *buf)
अणु
	काष्ठा usb_device *usb_dev = mt7601u_to_usb_dev(dev);

	buf->len = len;
	buf->urb = usb_alloc_urb(0, GFP_KERNEL);
	buf->buf = usb_alloc_coherent(usb_dev, buf->len, GFP_KERNEL, &buf->dma);

	वापस !buf->urb || !buf->buf;
पूर्ण

व्योम mt7601u_usb_मुक्त_buf(काष्ठा mt7601u_dev *dev, काष्ठा mt7601u_dma_buf *buf)
अणु
	काष्ठा usb_device *usb_dev = mt7601u_to_usb_dev(dev);

	usb_मुक्त_coherent(usb_dev, buf->len, buf->buf, buf->dma);
	usb_मुक्त_urb(buf->urb);
पूर्ण

पूर्णांक mt7601u_usb_submit_buf(काष्ठा mt7601u_dev *dev, पूर्णांक dir, पूर्णांक ep_idx,
			   काष्ठा mt7601u_dma_buf *buf, gfp_t gfp,
			   usb_complete_t complete_fn, व्योम *context)
अणु
	काष्ठा usb_device *usb_dev = mt7601u_to_usb_dev(dev);
	अचिन्हित pipe;
	पूर्णांक ret;

	अगर (dir == USB_सूची_IN)
		pipe = usb_rcvbulkpipe(usb_dev, dev->in_eps[ep_idx]);
	अन्यथा
		pipe = usb_sndbulkpipe(usb_dev, dev->out_eps[ep_idx]);

	usb_fill_bulk_urb(buf->urb, usb_dev, pipe, buf->buf, buf->len,
			  complete_fn, context);
	buf->urb->transfer_dma = buf->dma;
	buf->urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	trace_mt_submit_urb(dev, buf->urb);
	ret = usb_submit_urb(buf->urb, gfp);
	अगर (ret)
		dev_err(dev->dev, "Error: submit URB dir:%d ep:%d failed:%d\n",
			dir, ep_idx, ret);
	वापस ret;
पूर्ण

व्योम mt7601u_complete_urb(काष्ठा urb *urb)
अणु
	काष्ठा completion *cmpl = urb->context;

	complete(cmpl);
पूर्ण

पूर्णांक mt7601u_venकरोr_request(काष्ठा mt7601u_dev *dev, स्थिर u8 req,
			   स्थिर u8 direction, स्थिर u16 val, स्थिर u16 offset,
			   व्योम *buf, स्थिर माप_प्रकार buflen)
अणु
	पूर्णांक i, ret;
	काष्ठा usb_device *usb_dev = mt7601u_to_usb_dev(dev);
	स्थिर u8 req_type = direction | USB_TYPE_VENDOR | USB_RECIP_DEVICE;
	स्थिर अचिन्हित पूर्णांक pipe = (direction == USB_सूची_IN) ?
		usb_rcvctrlpipe(usb_dev, 0) : usb_sndctrlpipe(usb_dev, 0);

	क्रम (i = 0; i < MT_VEND_REQ_MAX_RETRY; i++) अणु
		ret = usb_control_msg(usb_dev, pipe, req, req_type,
				      val, offset, buf, buflen,
				      MT_VEND_REQ_TOUT_MS);
		trace_mt_vend_req(dev, pipe, req, req_type, val, offset,
				  buf, buflen, ret);

		अगर (ret == -ENODEV)
			set_bit(MT7601U_STATE_REMOVED, &dev->state);
		अगर (ret >= 0 || ret == -ENODEV)
			वापस ret;

		msleep(5);
	पूर्ण

	dev_err(dev->dev, "Vendor request req:%02x off:%04x failed:%d\n",
		req, offset, ret);

	वापस ret;
पूर्ण

व्योम mt7601u_venकरोr_reset(काष्ठा mt7601u_dev *dev)
अणु
	mt7601u_venकरोr_request(dev, MT_VEND_DEV_MODE, USB_सूची_OUT,
			       MT_VEND_DEV_MODE_RESET, 0, शून्य, 0);
पूर्ण

/* should be called with venकरोr_req_mutex held */
अटल u32 __mt7601u_rr(काष्ठा mt7601u_dev *dev, u32 offset)
अणु
	पूर्णांक ret;
	u32 val = ~0;

	WARN_ONCE(offset > अच_लघु_उच्च, "read high off:%08x", offset);

	ret = mt7601u_venकरोr_request(dev, MT_VEND_MULTI_READ, USB_सूची_IN,
				     0, offset, dev->vend_buf, MT_VEND_BUF);
	अगर (ret == MT_VEND_BUF)
		val = get_unaligned_le32(dev->vend_buf);
	अन्यथा अगर (ret > 0)
		dev_err(dev->dev, "Error: wrong size read:%d off:%08x\n",
			ret, offset);

	trace_reg_पढ़ो(dev, offset, val);
	वापस val;
पूर्ण

u32 mt7601u_rr(काष्ठा mt7601u_dev *dev, u32 offset)
अणु
	u32 ret;

	mutex_lock(&dev->venकरोr_req_mutex);
	ret = __mt7601u_rr(dev, offset);
	mutex_unlock(&dev->venकरोr_req_mutex);

	वापस ret;
पूर्ण

/* should be called with venकरोr_req_mutex held */
अटल पूर्णांक __mt7601u_venकरोr_single_wr(काष्ठा mt7601u_dev *dev, स्थिर u8 req,
				      स्थिर u16 offset, स्थिर u32 val)
अणु
	पूर्णांक ret = mt7601u_venकरोr_request(dev, req, USB_सूची_OUT,
					 val & 0xffff, offset, शून्य, 0);
	अगर (!ret)
		ret = mt7601u_venकरोr_request(dev, req, USB_सूची_OUT,
					     val >> 16, offset + 2, शून्य, 0);
	trace_reg_ग_लिखो(dev, offset, val);
	वापस ret;
पूर्ण

पूर्णांक mt7601u_venकरोr_single_wr(काष्ठा mt7601u_dev *dev, स्थिर u8 req,
			     स्थिर u16 offset, स्थिर u32 val)
अणु
	पूर्णांक ret;

	mutex_lock(&dev->venकरोr_req_mutex);
	ret = __mt7601u_venकरोr_single_wr(dev, req, offset, val);
	mutex_unlock(&dev->venकरोr_req_mutex);

	वापस ret;
पूर्ण

व्योम mt7601u_wr(काष्ठा mt7601u_dev *dev, u32 offset, u32 val)
अणु
	WARN_ONCE(offset > अच_लघु_उच्च, "write high off:%08x", offset);

	mt7601u_venकरोr_single_wr(dev, MT_VEND_WRITE, offset, val);
पूर्ण

u32 mt7601u_rmw(काष्ठा mt7601u_dev *dev, u32 offset, u32 mask, u32 val)
अणु
	mutex_lock(&dev->venकरोr_req_mutex);
	val |= __mt7601u_rr(dev, offset) & ~mask;
	__mt7601u_venकरोr_single_wr(dev, MT_VEND_WRITE, offset, val);
	mutex_unlock(&dev->venकरोr_req_mutex);

	वापस val;
पूर्ण

u32 mt7601u_rmc(काष्ठा mt7601u_dev *dev, u32 offset, u32 mask, u32 val)
अणु
	u32 reg;

	mutex_lock(&dev->venकरोr_req_mutex);
	reg = __mt7601u_rr(dev, offset);
	val |= reg & ~mask;
	अगर (reg != val)
		__mt7601u_venकरोr_single_wr(dev, MT_VEND_WRITE,
					   offset, val);
	mutex_unlock(&dev->venकरोr_req_mutex);

	वापस val;
पूर्ण

व्योम mt7601u_wr_copy(काष्ठा mt7601u_dev *dev, u32 offset,
		     स्थिर व्योम *data, पूर्णांक len)
अणु
	WARN_ONCE(offset & 3, "unaligned write copy off:%08x", offset);
	WARN_ONCE(len & 3, "short write copy off:%08x", offset);

	mt7601u_burst_ग_लिखो_regs(dev, offset, data, len / 4);
पूर्ण

व्योम mt7601u_addr_wr(काष्ठा mt7601u_dev *dev, स्थिर u32 offset, स्थिर u8 *addr)
अणु
	mt7601u_wr(dev, offset, get_unaligned_le32(addr));
	mt7601u_wr(dev, offset + 4, addr[4] | addr[5] << 8);
पूर्ण

अटल पूर्णांक mt7601u_assign_pipes(काष्ठा usb_पूर्णांकerface *usb_पूर्णांकf,
				काष्ठा mt7601u_dev *dev)
अणु
	काष्ठा usb_endpoपूर्णांक_descriptor *ep_desc;
	काष्ठा usb_host_पूर्णांकerface *पूर्णांकf_desc = usb_पूर्णांकf->cur_altsetting;
	अचिन्हित i, ep_i = 0, ep_o = 0;

	BUILD_BUG_ON(माप(dev->in_eps) < __MT_EP_IN_MAX);
	BUILD_BUG_ON(माप(dev->out_eps) < __MT_EP_OUT_MAX);

	क्रम (i = 0; i < पूर्णांकf_desc->desc.bNumEndpoपूर्णांकs; i++) अणु
		ep_desc = &पूर्णांकf_desc->endpoपूर्णांक[i].desc;

		अगर (usb_endpoपूर्णांक_is_bulk_in(ep_desc) &&
		    ep_i++ < __MT_EP_IN_MAX) अणु
			dev->in_eps[ep_i - 1] = usb_endpoपूर्णांक_num(ep_desc);
			dev->in_max_packet = usb_endpoपूर्णांक_maxp(ep_desc);
			/* Note: this is ignored by usb sub-प्रणाली but venकरोr
			 *	 code करोes it. We can drop this at some poपूर्णांक.
			 */
			dev->in_eps[ep_i - 1] |= USB_सूची_IN;
		पूर्ण अन्यथा अगर (usb_endpoपूर्णांक_is_bulk_out(ep_desc) &&
			   ep_o++ < __MT_EP_OUT_MAX) अणु
			dev->out_eps[ep_o - 1] = usb_endpoपूर्णांक_num(ep_desc);
			dev->out_max_packet = usb_endpoपूर्णांक_maxp(ep_desc);
		पूर्ण
	पूर्ण

	अगर (ep_i != __MT_EP_IN_MAX || ep_o != __MT_EP_OUT_MAX) अणु
		dev_err(dev->dev, "Error: wrong pipe number in:%d out:%d\n",
			ep_i, ep_o);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt7601u_probe(काष्ठा usb_पूर्णांकerface *usb_पूर्णांकf,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(usb_पूर्णांकf);
	काष्ठा mt7601u_dev *dev;
	u32 asic_rev, mac_rev;
	पूर्णांक ret;

	dev = mt7601u_alloc_device(&usb_पूर्णांकf->dev);
	अगर (!dev)
		वापस -ENOMEM;

	usb_dev = usb_get_dev(usb_dev);
	usb_reset_device(usb_dev);

	usb_set_पूर्णांकfdata(usb_पूर्णांकf, dev);

	dev->vend_buf = devm_kदो_स्मृति(dev->dev, MT_VEND_BUF, GFP_KERNEL);
	अगर (!dev->vend_buf) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	ret = mt7601u_assign_pipes(usb_पूर्णांकf, dev);
	अगर (ret)
		जाओ err;
	ret = mt7601u_रुको_asic_पढ़ोy(dev);
	अगर (ret)
		जाओ err;

	asic_rev = mt7601u_rr(dev, MT_ASIC_VERSION);
	mac_rev = mt7601u_rr(dev, MT_MAC_CSR0);
	dev_info(dev->dev, "ASIC revision: %08x MAC revision: %08x\n",
		 asic_rev, mac_rev);
	अगर ((asic_rev >> 16) != 0x7601) अणु
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	/* Note: venकरोr driver skips this check क्रम MT7601U */
	अगर (!(mt7601u_rr(dev, MT_EFUSE_CTRL) & MT_EFUSE_CTRL_SEL))
		dev_warn(dev->dev, "Warning: eFUSE not present\n");

	ret = mt7601u_init_hardware(dev);
	अगर (ret)
		जाओ err;
	ret = mt7601u_रेजिस्टर_device(dev);
	अगर (ret)
		जाओ err_hw;

	set_bit(MT7601U_STATE_INITIALIZED, &dev->state);

	वापस 0;
err_hw:
	mt7601u_cleanup(dev);
err:
	usb_set_पूर्णांकfdata(usb_पूर्णांकf, शून्य);
	usb_put_dev(पूर्णांकerface_to_usbdev(usb_पूर्णांकf));

	destroy_workqueue(dev->stat_wq);
	ieee80211_मुक्त_hw(dev->hw);
	वापस ret;
पूर्ण

अटल व्योम mt7601u_disconnect(काष्ठा usb_पूर्णांकerface *usb_पूर्णांकf)
अणु
	काष्ठा mt7601u_dev *dev = usb_get_पूर्णांकfdata(usb_पूर्णांकf);

	ieee80211_unरेजिस्टर_hw(dev->hw);
	mt7601u_cleanup(dev);

	usb_set_पूर्णांकfdata(usb_पूर्णांकf, शून्य);
	usb_put_dev(पूर्णांकerface_to_usbdev(usb_पूर्णांकf));

	destroy_workqueue(dev->stat_wq);
	ieee80211_मुक्त_hw(dev->hw);
पूर्ण

अटल पूर्णांक mt7601u_suspend(काष्ठा usb_पूर्णांकerface *usb_पूर्णांकf, pm_message_t state)
अणु
	काष्ठा mt7601u_dev *dev = usb_get_पूर्णांकfdata(usb_पूर्णांकf);

	mt7601u_cleanup(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक mt7601u_resume(काष्ठा usb_पूर्णांकerface *usb_पूर्णांकf)
अणु
	काष्ठा mt7601u_dev *dev = usb_get_पूर्णांकfdata(usb_पूर्णांकf);
	पूर्णांक ret;

	ret = mt7601u_init_hardware(dev);
	अगर (ret)
		वापस ret;

	set_bit(MT7601U_STATE_INITIALIZED, &dev->state);

	वापस 0;
पूर्ण

MODULE_DEVICE_TABLE(usb, mt7601u_device_table);
MODULE_FIRMWARE(MT7601U_FIRMWARE);
MODULE_LICENSE("GPL");

अटल काष्ठा usb_driver mt7601u_driver = अणु
	.name		= KBUILD_MODNAME,
	.id_table	= mt7601u_device_table,
	.probe		= mt7601u_probe,
	.disconnect	= mt7601u_disconnect,
	.suspend	= mt7601u_suspend,
	.resume		= mt7601u_resume,
	.reset_resume	= mt7601u_resume,
	.soft_unbind	= 1,
	.disable_hub_initiated_lpm = 1,
पूर्ण;
module_usb_driver(mt7601u_driver);
