<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * mtu3_gadget_ep0.c - MediaTek USB3 DRD peripheral driver ep0 handling
 *
 * Copyright (c) 2016 MediaTek Inc.
 *
 * Author:  Chunfeng.Yun <chunfeng.yun@mediatek.com>
 */

#समावेश <linux/iopoll.h>
#समावेश <linux/usb/composite.h>

#समावेश "mtu3.h"
#समावेश "mtu3_debug.h"
#समावेश "mtu3_trace.h"

/* ep0 is always mtu3->in_eps[0] */
#घोषणा	next_ep0_request(mtu)	next_request((mtu)->ep0)

/* क्रम high speed test mode; see USB 2.0 spec 7.1.20 */
अटल स्थिर u8 mtu3_test_packet[53] = अणु
	/* implicit SYNC then DATA0 to start */

	/* JKJKJKJK x9 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	/* JJKKJJKK x8 */
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	/* JJJJKKKK x8 */
	0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee,
	/* JJJJJJJKKKKKKK x8 */
	0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	/* JJJJJJJK x8 */
	0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd,
	/* JKKKKKKK x10, JK */
	0xfc, 0x7e, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0x7e,
	/* implicit CRC16 then EOP to end */
पूर्ण;

अटल अक्षर *decode_ep0_state(काष्ठा mtu3 *mtu)
अणु
	चयन (mtu->ep0_state) अणु
	हाल MU3D_EP0_STATE_SETUP:
		वापस "SETUP";
	हाल MU3D_EP0_STATE_TX:
		वापस "IN";
	हाल MU3D_EP0_STATE_RX:
		वापस "OUT";
	हाल MU3D_EP0_STATE_TX_END:
		वापस "TX-END";
	हाल MU3D_EP0_STATE_STALL:
		वापस "STALL";
	शेष:
		वापस "??";
	पूर्ण
पूर्ण

अटल व्योम ep0_req_giveback(काष्ठा mtu3 *mtu, काष्ठा usb_request *req)
अणु
	mtu3_req_complete(mtu->ep0, req, 0);
पूर्ण

अटल पूर्णांक
क्रमward_to_driver(काष्ठा mtu3 *mtu, स्थिर काष्ठा usb_ctrlrequest *setup)
__releases(mtu->lock)
__acquires(mtu->lock)
अणु
	पूर्णांक ret;

	अगर (!mtu->gadget_driver)
		वापस -EOPNOTSUPP;

	spin_unlock(&mtu->lock);
	ret = mtu->gadget_driver->setup(&mtu->g, setup);
	spin_lock(&mtu->lock);

	dev_dbg(mtu->dev, "%s ret %d\n", __func__, ret);
	वापस ret;
पूर्ण

अटल व्योम ep0_ग_लिखो_fअगरo(काष्ठा mtu3_ep *mep, स्थिर u8 *src, u16 len)
अणु
	व्योम __iomem *fअगरo = mep->mtu->mac_base + U3D_FIFO0;
	u16 index = 0;

	dev_dbg(mep->mtu->dev, "%s: ep%din, len=%d, buf=%p\n",
		__func__, mep->epnum, len, src);

	अगर (len >= 4) अणु
		ioग_लिखो32_rep(fअगरo, src, len >> 2);
		index = len & ~0x03;
	पूर्ण
	अगर (len & 0x02) अणु
		ग_लिखोw(*(u16 *)&src[index], fअगरo);
		index += 2;
	पूर्ण
	अगर (len & 0x01)
		ग_लिखोb(src[index], fअगरo);
पूर्ण

अटल व्योम ep0_पढ़ो_fअगरo(काष्ठा mtu3_ep *mep, u8 *dst, u16 len)
अणु
	व्योम __iomem *fअगरo = mep->mtu->mac_base + U3D_FIFO0;
	u32 value;
	u16 index = 0;

	dev_dbg(mep->mtu->dev, "%s: ep%dout len=%d buf=%p\n",
		 __func__, mep->epnum, len, dst);

	अगर (len >= 4) अणु
		ioपढ़ो32_rep(fअगरo, dst, len >> 2);
		index = len & ~0x03;
	पूर्ण
	अगर (len & 0x3) अणु
		value = पढ़ोl(fअगरo);
		स_नकल(&dst[index], &value, len & 0x3);
	पूर्ण

पूर्ण

अटल व्योम ep0_load_test_packet(काष्ठा mtu3 *mtu)
अणु
	/*
	 * because the length of test packet is less than max packet of HS ep0,
	 * ग_लिखो it पूर्णांकo fअगरo directly.
	 */
	ep0_ग_लिखो_fअगरo(mtu->ep0, mtu3_test_packet, माप(mtu3_test_packet));
पूर्ण

/*
 * A. send STALL क्रम setup transfer without data stage:
 *		set SENDSTALL and SETUPPKTRDY at the same समय;
 * B. send STALL क्रम other हालs:
 *		set SENDSTALL only.
 */
अटल व्योम ep0_stall_set(काष्ठा mtu3_ep *mep0, bool set, u32 pktrdy)
अणु
	काष्ठा mtu3 *mtu = mep0->mtu;
	व्योम __iomem *mbase = mtu->mac_base;
	u32 csr;

	/* EP0_SENTSTALL is W1C */
	csr = mtu3_पढ़ोl(mbase, U3D_EP0CSR) & EP0_W1C_BITS;
	अगर (set)
		csr |= EP0_SENDSTALL | pktrdy;
	अन्यथा
		csr = (csr & ~EP0_SENDSTALL) | EP0_SENTSTALL;
	mtu3_ग_लिखोl(mtu->mac_base, U3D_EP0CSR, csr);

	mtu->delayed_status = false;
	mtu->ep0_state = MU3D_EP0_STATE_SETUP;

	dev_dbg(mtu->dev, "ep0: %s STALL, ep0_state: %s\n",
		set ? "SEND" : "CLEAR", decode_ep0_state(mtu));
पूर्ण

अटल व्योम ep0_करो_status_stage(काष्ठा mtu3 *mtu)
अणु
	व्योम __iomem *mbase = mtu->mac_base;
	u32 value;

	value = mtu3_पढ़ोl(mbase, U3D_EP0CSR) & EP0_W1C_BITS;
	mtu3_ग_लिखोl(mbase, U3D_EP0CSR, value | EP0_SETUPPKTRDY | EP0_DATAEND);
पूर्ण

अटल पूर्णांक ep0_queue(काष्ठा mtu3_ep *mep0, काष्ठा mtu3_request *mreq);

अटल व्योम ep0_dummy_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणुपूर्ण

अटल व्योम ep0_set_sel_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा mtu3_request *mreq;
	काष्ठा mtu3 *mtu;
	काष्ठा usb_set_sel_req sel;

	स_नकल(&sel, req->buf, माप(sel));

	mreq = to_mtu3_request(req);
	mtu = mreq->mtu;
	dev_dbg(mtu->dev, "u1sel:%d, u1pel:%d, u2sel:%d, u2pel:%d\n",
		sel.u1_sel, sel.u1_pel, sel.u2_sel, sel.u2_pel);
पूर्ण

/* queue data stage to handle 6 byte SET_SEL request */
अटल पूर्णांक ep0_set_sel(काष्ठा mtu3 *mtu, काष्ठा usb_ctrlrequest *setup)
अणु
	पूर्णांक ret;
	u16 length = le16_to_cpu(setup->wLength);

	अगर (unlikely(length != 6)) अणु
		dev_err(mtu->dev, "%s wrong wLength:%d\n",
			__func__, length);
		वापस -EINVAL;
	पूर्ण

	mtu->ep0_req.mep = mtu->ep0;
	mtu->ep0_req.request.length = 6;
	mtu->ep0_req.request.buf = mtu->setup_buf;
	mtu->ep0_req.request.complete = ep0_set_sel_complete;
	ret = ep0_queue(mtu->ep0, &mtu->ep0_req);

	वापस ret < 0 ? ret : 1;
पूर्ण

अटल पूर्णांक
ep0_get_status(काष्ठा mtu3 *mtu, स्थिर काष्ठा usb_ctrlrequest *setup)
अणु
	काष्ठा mtu3_ep *mep = शून्य;
	पूर्णांक handled = 1;
	u8 result[2] = अणु0, 0पूर्ण;
	u8 epnum = 0;
	पूर्णांक is_in;

	चयन (setup->bRequestType & USB_RECIP_MASK) अणु
	हाल USB_RECIP_DEVICE:
		result[0] = mtu->is_self_घातered << USB_DEVICE_SELF_POWERED;
		result[0] |= mtu->may_wakeup << USB_DEVICE_REMOTE_WAKEUP;

		अगर (mtu->g.speed >= USB_SPEED_SUPER) अणु
			result[0] |= mtu->u1_enable << USB_DEV_STAT_U1_ENABLED;
			result[0] |= mtu->u2_enable << USB_DEV_STAT_U2_ENABLED;
		पूर्ण

		dev_dbg(mtu->dev, "%s result=%x, U1=%x, U2=%x\n", __func__,
			result[0], mtu->u1_enable, mtu->u2_enable);

		अवरोध;
	हाल USB_RECIP_INTERFACE:
		अवरोध;
	हाल USB_RECIP_ENDPOINT:
		epnum = (u8) le16_to_cpu(setup->wIndex);
		is_in = epnum & USB_सूची_IN;
		epnum &= USB_ENDPOINT_NUMBER_MASK;

		अगर (epnum >= mtu->num_eps) अणु
			handled = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (!epnum)
			अवरोध;

		mep = (is_in ? mtu->in_eps : mtu->out_eps) + epnum;
		अगर (!mep->desc) अणु
			handled = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (mep->flags & MTU3_EP_STALL)
			result[0] |= 1 << USB_ENDPOINT_HALT;

		अवरोध;
	शेष:
		/* class, venकरोr, etc ... delegate */
		handled = 0;
		अवरोध;
	पूर्ण

	अगर (handled > 0) अणु
		पूर्णांक ret;

		/* prepare a data stage क्रम GET_STATUS */
		dev_dbg(mtu->dev, "get_status=%x\n", *(u16 *)result);
		स_नकल(mtu->setup_buf, result, माप(result));
		mtu->ep0_req.mep = mtu->ep0;
		mtu->ep0_req.request.length = 2;
		mtu->ep0_req.request.buf = &mtu->setup_buf;
		mtu->ep0_req.request.complete = ep0_dummy_complete;
		ret = ep0_queue(mtu->ep0, &mtu->ep0_req);
		अगर (ret < 0)
			handled = ret;
	पूर्ण
	वापस handled;
पूर्ण

अटल पूर्णांक handle_test_mode(काष्ठा mtu3 *mtu, काष्ठा usb_ctrlrequest *setup)
अणु
	व्योम __iomem *mbase = mtu->mac_base;
	पूर्णांक handled = 1;
	u32 value;

	चयन (le16_to_cpu(setup->wIndex) >> 8) अणु
	हाल USB_TEST_J:
		dev_dbg(mtu->dev, "USB_TEST_J\n");
		mtu->test_mode_nr = TEST_J_MODE;
		अवरोध;
	हाल USB_TEST_K:
		dev_dbg(mtu->dev, "USB_TEST_K\n");
		mtu->test_mode_nr = TEST_K_MODE;
		अवरोध;
	हाल USB_TEST_SE0_NAK:
		dev_dbg(mtu->dev, "USB_TEST_SE0_NAK\n");
		mtu->test_mode_nr = TEST_SE0_NAK_MODE;
		अवरोध;
	हाल USB_TEST_PACKET:
		dev_dbg(mtu->dev, "USB_TEST_PACKET\n");
		mtu->test_mode_nr = TEST_PACKET_MODE;
		अवरोध;
	शेष:
		handled = -EINVAL;
		जाओ out;
	पूर्ण

	mtu->test_mode = true;

	/* no TX completion पूर्णांकerrupt, and need restart platक्रमm after test */
	अगर (mtu->test_mode_nr == TEST_PACKET_MODE)
		ep0_load_test_packet(mtu);

	/* send status beक्रमe entering test mode. */
	ep0_करो_status_stage(mtu);

	/* रुको क्रम ACK status sent by host */
	पढ़ोl_poll_समयout_atomic(mbase + U3D_EP0CSR, value,
			!(value & EP0_DATAEND), 100, 5000);

	mtu3_ग_लिखोl(mbase, U3D_USB2_TEST_MODE, mtu->test_mode_nr);

	mtu->ep0_state = MU3D_EP0_STATE_SETUP;

out:
	वापस handled;
पूर्ण

अटल पूर्णांक ep0_handle_feature_dev(काष्ठा mtu3 *mtu,
		काष्ठा usb_ctrlrequest *setup, bool set)
अणु
	व्योम __iomem *mbase = mtu->mac_base;
	पूर्णांक handled = -EINVAL;
	u32 lpc;

	चयन (le16_to_cpu(setup->wValue)) अणु
	हाल USB_DEVICE_REMOTE_WAKEUP:
		mtu->may_wakeup = !!set;
		handled = 1;
		अवरोध;
	हाल USB_DEVICE_TEST_MODE:
		अगर (!set || (mtu->g.speed != USB_SPEED_HIGH) ||
			(le16_to_cpu(setup->wIndex) & 0xff))
			अवरोध;

		handled = handle_test_mode(mtu, setup);
		अवरोध;
	हाल USB_DEVICE_U1_ENABLE:
		अगर (mtu->g.speed < USB_SPEED_SUPER ||
		    mtu->g.state != USB_STATE_CONFIGURED)
			अवरोध;

		lpc = mtu3_पढ़ोl(mbase, U3D_LINK_POWER_CONTROL);
		अगर (set)
			lpc |= SW_U1_REQUEST_ENABLE;
		अन्यथा
			lpc &= ~SW_U1_REQUEST_ENABLE;
		mtu3_ग_लिखोl(mbase, U3D_LINK_POWER_CONTROL, lpc);

		mtu->u1_enable = !!set;
		handled = 1;
		अवरोध;
	हाल USB_DEVICE_U2_ENABLE:
		अगर (mtu->g.speed < USB_SPEED_SUPER ||
		    mtu->g.state != USB_STATE_CONFIGURED)
			अवरोध;

		lpc = mtu3_पढ़ोl(mbase, U3D_LINK_POWER_CONTROL);
		अगर (set)
			lpc |= SW_U2_REQUEST_ENABLE;
		अन्यथा
			lpc &= ~SW_U2_REQUEST_ENABLE;
		mtu3_ग_लिखोl(mbase, U3D_LINK_POWER_CONTROL, lpc);

		mtu->u2_enable = !!set;
		handled = 1;
		अवरोध;
	शेष:
		handled = -EINVAL;
		अवरोध;
	पूर्ण
	वापस handled;
पूर्ण

अटल पूर्णांक ep0_handle_feature(काष्ठा mtu3 *mtu,
		काष्ठा usb_ctrlrequest *setup, bool set)
अणु
	काष्ठा mtu3_ep *mep;
	पूर्णांक handled = -EINVAL;
	पूर्णांक is_in;
	u16 value;
	u16 index;
	u8 epnum;

	value = le16_to_cpu(setup->wValue);
	index = le16_to_cpu(setup->wIndex);

	चयन (setup->bRequestType & USB_RECIP_MASK) अणु
	हाल USB_RECIP_DEVICE:
		handled = ep0_handle_feature_dev(mtu, setup, set);
		अवरोध;
	हाल USB_RECIP_INTERFACE:
		/* superspeed only */
		अगर (value == USB_INTRF_FUNC_SUSPEND &&
		    mtu->g.speed >= USB_SPEED_SUPER) अणु
			/*
			 * क्रमward the request because function drivers
			 * should handle it
			 */
			handled = 0;
		पूर्ण
		अवरोध;
	हाल USB_RECIP_ENDPOINT:
		epnum = index & USB_ENDPOINT_NUMBER_MASK;
		अगर (epnum == 0 || epnum >= mtu->num_eps ||
			value != USB_ENDPOINT_HALT)
			अवरोध;

		is_in = index & USB_सूची_IN;
		mep = (is_in ? mtu->in_eps : mtu->out_eps) + epnum;
		अगर (!mep->desc)
			अवरोध;

		handled = 1;
		/* ignore request अगर endpoपूर्णांक is wedged */
		अगर (mep->flags & MTU3_EP_WEDGE)
			अवरोध;

		mtu3_ep_stall_set(mep, set);
		अवरोध;
	शेष:
		/* class, venकरोr, etc ... delegate */
		handled = 0;
		अवरोध;
	पूर्ण
	वापस handled;
पूर्ण

/*
 * handle all control requests can be handled
 * वापसs:
 *	negative त्रुटि_सं - error happened
 *	zero - need delegate SETUP to gadget driver
 *	positive - alपढ़ोy handled
 */
अटल पूर्णांक handle_standard_request(काष्ठा mtu3 *mtu,
			  काष्ठा usb_ctrlrequest *setup)
अणु
	व्योम __iomem *mbase = mtu->mac_base;
	क्रमागत usb_device_state state = mtu->g.state;
	पूर्णांक handled = -EINVAL;
	u32 dev_conf;
	u16 value;

	value = le16_to_cpu(setup->wValue);

	/* the gadget driver handles everything except what we must handle */
	चयन (setup->bRequest) अणु
	हाल USB_REQ_SET_ADDRESS:
		/* change it after the status stage */
		mtu->address = (u8) (value & 0x7f);
		dev_dbg(mtu->dev, "set address to 0x%x\n", mtu->address);

		dev_conf = mtu3_पढ़ोl(mbase, U3D_DEVICE_CONF);
		dev_conf &= ~DEV_ADDR_MSK;
		dev_conf |= DEV_ADDR(mtu->address);
		mtu3_ग_लिखोl(mbase, U3D_DEVICE_CONF, dev_conf);

		अगर (mtu->address)
			usb_gadget_set_state(&mtu->g, USB_STATE_ADDRESS);
		अन्यथा
			usb_gadget_set_state(&mtu->g, USB_STATE_DEFAULT);

		handled = 1;
		अवरोध;
	हाल USB_REQ_SET_CONFIGURATION:
		अगर (state == USB_STATE_ADDRESS) अणु
			usb_gadget_set_state(&mtu->g,
					USB_STATE_CONFIGURED);
		पूर्ण अन्यथा अगर (state == USB_STATE_CONFIGURED) अणु
			/*
			 * USB2 spec sec 9.4.7, अगर wValue is 0 then dev
			 * is moved to addressed state
			 */
			अगर (!value)
				usb_gadget_set_state(&mtu->g,
						USB_STATE_ADDRESS);
		पूर्ण
		handled = 0;
		अवरोध;
	हाल USB_REQ_CLEAR_FEATURE:
		handled = ep0_handle_feature(mtu, setup, 0);
		अवरोध;
	हाल USB_REQ_SET_FEATURE:
		handled = ep0_handle_feature(mtu, setup, 1);
		अवरोध;
	हाल USB_REQ_GET_STATUS:
		handled = ep0_get_status(mtu, setup);
		अवरोध;
	हाल USB_REQ_SET_SEL:
		handled = ep0_set_sel(mtu, setup);
		अवरोध;
	हाल USB_REQ_SET_ISOCH_DELAY:
		handled = 1;
		अवरोध;
	शेष:
		/* delegate SET_CONFIGURATION, etc */
		handled = 0;
	पूर्ण

	वापस handled;
पूर्ण

/* receive an data packet (OUT) */
अटल व्योम ep0_rx_state(काष्ठा mtu3 *mtu)
अणु
	काष्ठा mtu3_request *mreq;
	काष्ठा usb_request *req;
	व्योम __iomem *mbase = mtu->mac_base;
	u32 maxp;
	u32 csr;
	u16 count = 0;

	dev_dbg(mtu->dev, "%s\n", __func__);

	csr = mtu3_पढ़ोl(mbase, U3D_EP0CSR) & EP0_W1C_BITS;
	mreq = next_ep0_request(mtu);
	req = &mreq->request;

	/* पढ़ो packet and ack; or stall because of gadget driver bug */
	अगर (req) अणु
		व्योम *buf = req->buf + req->actual;
		अचिन्हित पूर्णांक len = req->length - req->actual;

		/* पढ़ो the buffer */
		count = mtu3_पढ़ोl(mbase, U3D_RXCOUNT0);
		अगर (count > len) अणु
			req->status = -EOVERFLOW;
			count = len;
		पूर्ण
		ep0_पढ़ो_fअगरo(mtu->ep0, buf, count);
		req->actual += count;
		csr |= EP0_RXPKTRDY;

		maxp = mtu->g.ep0->maxpacket;
		अगर (count < maxp || req->actual == req->length) अणु
			mtu->ep0_state = MU3D_EP0_STATE_SETUP;
			dev_dbg(mtu->dev, "ep0 state: %s\n",
				decode_ep0_state(mtu));

			csr |= EP0_DATAEND;
		पूर्ण अन्यथा अणु
			req = शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		csr |= EP0_RXPKTRDY | EP0_SENDSTALL;
		dev_dbg(mtu->dev, "%s: SENDSTALL\n", __func__);
	पूर्ण

	mtu3_ग_लिखोl(mbase, U3D_EP0CSR, csr);

	/* give back the request अगर have received all data */
	अगर (req)
		ep0_req_giveback(mtu, req);

पूर्ण

/* transmitting to the host (IN) */
अटल व्योम ep0_tx_state(काष्ठा mtu3 *mtu)
अणु
	काष्ठा mtu3_request *mreq = next_ep0_request(mtu);
	काष्ठा usb_request *req;
	u32 csr;
	u8 *src;
	u32 count;
	u32 maxp;

	dev_dbg(mtu->dev, "%s\n", __func__);

	अगर (!mreq)
		वापस;

	maxp = mtu->g.ep0->maxpacket;
	req = &mreq->request;

	/* load the data */
	src = (u8 *)req->buf + req->actual;
	count = min(maxp, req->length - req->actual);
	अगर (count)
		ep0_ग_लिखो_fअगरo(mtu->ep0, src, count);

	dev_dbg(mtu->dev, "%s act=%d, len=%d, cnt=%d, maxp=%d zero=%d\n",
		 __func__, req->actual, req->length, count, maxp, req->zero);

	req->actual += count;

	अगर ((count < maxp)
		|| ((req->actual == req->length) && !req->zero))
		mtu->ep0_state = MU3D_EP0_STATE_TX_END;

	/* send it out, triggering a "txpktrdy cleared" irq */
	csr = mtu3_पढ़ोl(mtu->mac_base, U3D_EP0CSR) & EP0_W1C_BITS;
	mtu3_ग_लिखोl(mtu->mac_base, U3D_EP0CSR, csr | EP0_TXPKTRDY);

	dev_dbg(mtu->dev, "%s ep0csr=0x%x\n", __func__,
		mtu3_पढ़ोl(mtu->mac_base, U3D_EP0CSR));
पूर्ण

अटल व्योम ep0_पढ़ो_setup(काष्ठा mtu3 *mtu, काष्ठा usb_ctrlrequest *setup)
अणु
	काष्ठा mtu3_request *mreq;
	u32 count;
	u32 csr;

	csr = mtu3_पढ़ोl(mtu->mac_base, U3D_EP0CSR) & EP0_W1C_BITS;
	count = mtu3_पढ़ोl(mtu->mac_base, U3D_RXCOUNT0);

	ep0_पढ़ो_fअगरo(mtu->ep0, (u8 *)setup, count);

	dev_dbg(mtu->dev, "SETUP req%02x.%02x v%04x i%04x l%04x\n",
		 setup->bRequestType, setup->bRequest,
		 le16_to_cpu(setup->wValue), le16_to_cpu(setup->wIndex),
		 le16_to_cpu(setup->wLength));

	/* clean up any leftover transfers */
	mreq = next_ep0_request(mtu);
	अगर (mreq)
		ep0_req_giveback(mtu, &mreq->request);

	अगर (le16_to_cpu(setup->wLength) == 0) अणु
		;	/* no data stage, nothing to करो */
	पूर्ण अन्यथा अगर (setup->bRequestType & USB_सूची_IN) अणु
		mtu3_ग_लिखोl(mtu->mac_base, U3D_EP0CSR,
			csr | EP0_SETUPPKTRDY | EP0_DPHTX);
		mtu->ep0_state = MU3D_EP0_STATE_TX;
	पूर्ण अन्यथा अणु
		mtu3_ग_लिखोl(mtu->mac_base, U3D_EP0CSR,
			(csr | EP0_SETUPPKTRDY) & (~EP0_DPHTX));
		mtu->ep0_state = MU3D_EP0_STATE_RX;
	पूर्ण
पूर्ण

अटल पूर्णांक ep0_handle_setup(काष्ठा mtu3 *mtu)
__releases(mtu->lock)
__acquires(mtu->lock)
अणु
	काष्ठा usb_ctrlrequest setup;
	काष्ठा mtu3_request *mreq;
	पूर्णांक handled = 0;

	ep0_पढ़ो_setup(mtu, &setup);
	trace_mtu3_handle_setup(&setup);

	अगर ((setup.bRequestType & USB_TYPE_MASK) == USB_TYPE_STANDARD)
		handled = handle_standard_request(mtu, &setup);

	dev_dbg(mtu->dev, "handled %d, ep0_state: %s\n",
		 handled, decode_ep0_state(mtu));

	अगर (handled < 0)
		जाओ stall;
	अन्यथा अगर (handled > 0)
		जाओ finish;

	handled = क्रमward_to_driver(mtu, &setup);
	अगर (handled < 0) अणु
stall:
		dev_dbg(mtu->dev, "%s stall (%d)\n", __func__, handled);

		ep0_stall_set(mtu->ep0, true,
			le16_to_cpu(setup.wLength) ? 0 : EP0_SETUPPKTRDY);

		वापस 0;
	पूर्ण

finish:
	अगर (mtu->test_mode) अणु
		;	/* nothing to करो */
	पूर्ण अन्यथा अगर (handled == USB_GADGET_DELAYED_STATUS) अणु

		mreq = next_ep0_request(mtu);
		अगर (mreq) अणु
			/* alपढ़ोy asked us to जारी delayed status */
			ep0_करो_status_stage(mtu);
			ep0_req_giveback(mtu, &mreq->request);
		पूर्ण अन्यथा अणु
			/* करो delayed STATUS stage till receive ep0_queue */
			mtu->delayed_status = true;
		पूर्ण
	पूर्ण अन्यथा अगर (le16_to_cpu(setup.wLength) == 0) अणु /* no data stage */

		ep0_करो_status_stage(mtu);
		/* complete zlp request directly */
		mreq = next_ep0_request(mtu);
		अगर (mreq && !mreq->request.length)
			ep0_req_giveback(mtu, &mreq->request);
	पूर्ण

	वापस 0;
पूर्ण

irqवापस_t mtu3_ep0_isr(काष्ठा mtu3 *mtu)
अणु
	व्योम __iomem *mbase = mtu->mac_base;
	काष्ठा mtu3_request *mreq;
	u32 पूर्णांक_status;
	irqवापस_t ret = IRQ_NONE;
	u32 csr;
	u32 len;

	पूर्णांक_status = mtu3_पढ़ोl(mbase, U3D_EPISR);
	पूर्णांक_status &= mtu3_पढ़ोl(mbase, U3D_EPIER);
	mtu3_ग_लिखोl(mbase, U3D_EPISR, पूर्णांक_status); /* W1C */

	/* only handle ep0's */
	अगर (!(पूर्णांक_status & (EP0ISR | SETUPENDISR)))
		वापस IRQ_NONE;

	/* पात current SETUP, and process new one */
	अगर (पूर्णांक_status & SETUPENDISR)
		mtu->ep0_state = MU3D_EP0_STATE_SETUP;

	csr = mtu3_पढ़ोl(mbase, U3D_EP0CSR);

	dev_dbg(mtu->dev, "%s csr=0x%x\n", __func__, csr);

	/* we sent a stall.. need to clear it now.. */
	अगर (csr & EP0_SENTSTALL) अणु
		ep0_stall_set(mtu->ep0, false, 0);
		csr = mtu3_पढ़ोl(mbase, U3D_EP0CSR);
		ret = IRQ_HANDLED;
	पूर्ण
	dev_dbg(mtu->dev, "ep0_state: %s\n", decode_ep0_state(mtu));
	mtu3_dbg_trace(mtu->dev, "ep0_state %s", decode_ep0_state(mtu));

	चयन (mtu->ep0_state) अणु
	हाल MU3D_EP0_STATE_TX:
		/* irq on clearing txpktrdy */
		अगर ((csr & EP0_FIFOFULL) == 0) अणु
			ep0_tx_state(mtu);
			ret = IRQ_HANDLED;
		पूर्ण
		अवरोध;
	हाल MU3D_EP0_STATE_RX:
		/* irq on set rxpktrdy */
		अगर (csr & EP0_RXPKTRDY) अणु
			ep0_rx_state(mtu);
			ret = IRQ_HANDLED;
		पूर्ण
		अवरोध;
	हाल MU3D_EP0_STATE_TX_END:
		mtu3_ग_लिखोl(mbase, U3D_EP0CSR,
			(csr & EP0_W1C_BITS) | EP0_DATAEND);

		mreq = next_ep0_request(mtu);
		अगर (mreq)
			ep0_req_giveback(mtu, &mreq->request);

		mtu->ep0_state = MU3D_EP0_STATE_SETUP;
		ret = IRQ_HANDLED;
		dev_dbg(mtu->dev, "ep0_state: %s\n", decode_ep0_state(mtu));
		अवरोध;
	हाल MU3D_EP0_STATE_SETUP:
		अगर (!(csr & EP0_SETUPPKTRDY))
			अवरोध;

		len = mtu3_पढ़ोl(mbase, U3D_RXCOUNT0);
		अगर (len != 8) अणु
			dev_err(mtu->dev, "SETUP packet len %d != 8 ?\n", len);
			अवरोध;
		पूर्ण

		ep0_handle_setup(mtu);
		ret = IRQ_HANDLED;
		अवरोध;
	शेष:
		/* can't happen */
		ep0_stall_set(mtu->ep0, true, 0);
		WARN_ON(1);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण


अटल पूर्णांक mtu3_ep0_enable(काष्ठा usb_ep *ep,
	स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	/* always enabled */
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mtu3_ep0_disable(काष्ठा usb_ep *ep)
अणु
	/* always enabled */
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ep0_queue(काष्ठा mtu3_ep *mep, काष्ठा mtu3_request *mreq)
अणु
	काष्ठा mtu3 *mtu = mep->mtu;

	mreq->mtu = mtu;
	mreq->request.actual = 0;
	mreq->request.status = -EINPROGRESS;

	dev_dbg(mtu->dev, "%s %s (ep0_state: %s), len#%d\n", __func__,
		mep->name, decode_ep0_state(mtu), mreq->request.length);

	चयन (mtu->ep0_state) अणु
	हाल MU3D_EP0_STATE_SETUP:
	हाल MU3D_EP0_STATE_RX:	/* control-OUT data */
	हाल MU3D_EP0_STATE_TX:	/* control-IN data */
		अवरोध;
	शेष:
		dev_err(mtu->dev, "%s, error in ep0 state %s\n", __func__,
			decode_ep0_state(mtu));
		वापस -EINVAL;
	पूर्ण

	अगर (mtu->delayed_status) अणु

		mtu->delayed_status = false;
		ep0_करो_status_stage(mtu);
		/* needn't giveback the request क्रम handling delay STATUS */
		वापस 0;
	पूर्ण

	अगर (!list_empty(&mep->req_list))
		वापस -EBUSY;

	list_add_tail(&mreq->list, &mep->req_list);

	/* sequence #1, IN ... start writing the data */
	अगर (mtu->ep0_state == MU3D_EP0_STATE_TX)
		ep0_tx_state(mtu);

	वापस 0;
पूर्ण

अटल पूर्णांक mtu3_ep0_queue(काष्ठा usb_ep *ep,
	काष्ठा usb_request *req, gfp_t gfp)
अणु
	काष्ठा mtu3_ep *mep;
	काष्ठा mtu3_request *mreq;
	काष्ठा mtu3 *mtu;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (!ep || !req)
		वापस -EINVAL;

	mep = to_mtu3_ep(ep);
	mtu = mep->mtu;
	mreq = to_mtu3_request(req);

	spin_lock_irqsave(&mtu->lock, flags);
	ret = ep0_queue(mep, mreq);
	spin_unlock_irqrestore(&mtu->lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक mtu3_ep0_dequeue(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	/* we just won't support this */
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mtu3_ep0_halt(काष्ठा usb_ep *ep, पूर्णांक value)
अणु
	काष्ठा mtu3_ep *mep;
	काष्ठा mtu3 *mtu;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (!ep || !value)
		वापस -EINVAL;

	mep = to_mtu3_ep(ep);
	mtu = mep->mtu;

	dev_dbg(mtu->dev, "%s\n", __func__);

	spin_lock_irqsave(&mtu->lock, flags);

	अगर (!list_empty(&mep->req_list)) अणु
		ret = -EBUSY;
		जाओ cleanup;
	पूर्ण

	चयन (mtu->ep0_state) अणु
	/*
	 * stalls are usually issued after parsing SETUP packet, either
	 * directly in irq context from setup() or अन्यथा later.
	 */
	हाल MU3D_EP0_STATE_TX:
	हाल MU3D_EP0_STATE_TX_END:
	हाल MU3D_EP0_STATE_RX:
	हाल MU3D_EP0_STATE_SETUP:
		ep0_stall_set(mtu->ep0, true, 0);
		अवरोध;
	शेष:
		dev_dbg(mtu->dev, "ep0 can't halt in state %s\n",
			decode_ep0_state(mtu));
		ret = -EINVAL;
	पूर्ण

cleanup:
	spin_unlock_irqrestore(&mtu->lock, flags);
	वापस ret;
पूर्ण

स्थिर काष्ठा usb_ep_ops mtu3_ep0_ops = अणु
	.enable = mtu3_ep0_enable,
	.disable = mtu3_ep0_disable,
	.alloc_request = mtu3_alloc_request,
	.मुक्त_request = mtu3_मुक्त_request,
	.queue = mtu3_ep0_queue,
	.dequeue = mtu3_ep0_dequeue,
	.set_halt = mtu3_ep0_halt,
पूर्ण;
