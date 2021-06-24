<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

/*
 * Linux device driver क्रम USB based Prism54
 *
 * Copyright (c) 2006, Michael Wu <flamingice@sourmilk.net>
 *
 * Based on the islsm (sofपंचांगac prism54) driver, which is:
 * Copyright 2004-2006 Jean-Baptiste Note <jbnote@gmail.com>, et al.
 */

#समावेश <linux/usb.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/firmware.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/crc32.h>
#समावेश <linux/module.h>
#समावेश <net/mac80211.h>

#समावेश "p54.h"
#समावेश "lmac.h"
#समावेश "p54usb.h"

MODULE_AUTHOR("Michael Wu <flamingice@sourmilk.net>");
MODULE_DESCRIPTION("Prism54 USB wireless driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("prism54usb");
MODULE_FIRMWARE("isl3886usb");
MODULE_FIRMWARE("isl3887usb");

अटल काष्ठा usb_driver p54u_driver;

/*
 * Note:
 *
 * Always update our wiki's device list (located at:
 * http://wireless.wiki.kernel.org/en/users/Drivers/p54/devices ),
 * whenever you add a new device.
 */

अटल स्थिर काष्ठा usb_device_id p54u_table[] = अणु
	/* Version 1 devices (pci chip + net2280) */
	अणुUSB_DEVICE(0x0411, 0x0050)पूर्ण,	/* Buffalo WLI2-USB2-G54 */
	अणुUSB_DEVICE(0x045e, 0x00c2)पूर्ण,	/* Microsoft MN-710 */
	अणुUSB_DEVICE(0x0506, 0x0a11)पूर्ण,	/* 3COM 3CRWE254G72 */
	अणुUSB_DEVICE(0x0675, 0x0530)पूर्ण,	/* DrayTek Vigor 530 */
	अणुUSB_DEVICE(0x06b9, 0x0120)पूर्ण,	/* Thomson SpeedTouch 120g */
	अणुUSB_DEVICE(0x0707, 0xee06)पूर्ण,	/* SMC 2862W-G */
	अणुUSB_DEVICE(0x07aa, 0x001c)पूर्ण,	/* Corega CG-WLUSB2GT */
	अणुUSB_DEVICE(0x083a, 0x4501)पूर्ण,	/* Accton 802.11g WN4501 USB */
	अणुUSB_DEVICE(0x083a, 0x4502)पूर्ण,	/* Siemens Gigaset USB Adapter */
	अणुUSB_DEVICE(0x083a, 0x5501)पूर्ण,	/* Phillips CPWUA054 */
	अणुUSB_DEVICE(0x0846, 0x4200)पूर्ण,	/* Netgear WG121 */
	अणुUSB_DEVICE(0x0846, 0x4210)पूर्ण,	/* Netgear WG121 the second ? */
	अणुUSB_DEVICE(0x0846, 0x4220)पूर्ण,	/* Netgear WG111 */
	अणुUSB_DEVICE(0x09aa, 0x1000)पूर्ण,	/* Spinnaker Proto board */
	अणुUSB_DEVICE(0x0bf8, 0x1007)पूर्ण,	/* Fujitsu E-5400 USB */
	अणुUSB_DEVICE(0x0cde, 0x0006)पूर्ण,	/* Medion 40900, Roper Europe */
	अणुUSB_DEVICE(0x0db0, 0x6826)पूर्ण,	/* MSI UB54G (MS-6826) */
	अणुUSB_DEVICE(0x107b, 0x55f2)पूर्ण,	/* Gateway WGU-210 (Gemtek) */
	अणुUSB_DEVICE(0x124a, 0x4023)पूर्ण,	/* Shuttle PN15, Airvast WM168g, IOGear GWU513 */
	अणुUSB_DEVICE(0x124a, 0x4026)पूर्ण,	/* AirVasT USB wireless device */
	अणुUSB_DEVICE(0x1435, 0x0210)पूर्ण,	/* Inventel UR054G */
	अणुUSB_DEVICE(0x15a9, 0x0002)पूर्ण,	/* Gemtek WUBI-100GW 802.11g */
	अणुUSB_DEVICE(0x1630, 0x0005)पूर्ण,	/* 2Wire 802.11g USB (v1) / Z-Com */
	अणुUSB_DEVICE(0x182d, 0x096b)पूर्ण,	/* Sitecom WL-107 */
	अणुUSB_DEVICE(0x1915, 0x2234)पूर्ण,	/* Linksys WUSB54G OEM */
	अणुUSB_DEVICE(0x1915, 0x2235)पूर्ण,	/* Linksys WUSB54G Portable OEM */
	अणुUSB_DEVICE(0x2001, 0x3701)पूर्ण,	/* DLink DWL-G120 Spinnaker */
	अणुUSB_DEVICE(0x2001, 0x3703)पूर्ण,	/* DLink DWL-G122 */
	अणुUSB_DEVICE(0x2001, 0x3762)पूर्ण,	/* Conceptronic C54U */
	अणुUSB_DEVICE(0x5041, 0x2234)पूर्ण,	/* Linksys WUSB54G */
	अणुUSB_DEVICE(0x5041, 0x2235)पूर्ण,	/* Linksys WUSB54G Portable */

	/* Version 2 devices (3887) */
	अणुUSB_DEVICE(0x0471, 0x1230)पूर्ण,   /* Philips CPWUA054/00 */
	अणुUSB_DEVICE(0x050d, 0x7050)पूर्ण,	/* Belkin F5D7050 ver 1000 */
	अणुUSB_DEVICE(0x0572, 0x2000)पूर्ण,	/* Cohiba Proto board */
	अणुUSB_DEVICE(0x0572, 0x2002)पूर्ण,	/* Cohiba Proto board */
	अणुUSB_DEVICE(0x06a9, 0x000e)पूर्ण,	/* Westell 802.11g USB (A90-211WG-01) */
	अणुUSB_DEVICE(0x06b9, 0x0121)पूर्ण,	/* Thomson SpeedTouch 121g */
	अणुUSB_DEVICE(0x0707, 0xee13)पूर्ण,   /* SMC 2862W-G version 2 */
	अणुUSB_DEVICE(0x07aa, 0x0020)पूर्ण,	/* Corega WLUSB2GTST USB */
	अणुUSB_DEVICE(0x0803, 0x4310)पूर्ण,	/* Zoom 4410a */
	अणुUSB_DEVICE(0x083a, 0x4521)पूर्ण,   /* Siemens Gigaset USB Adapter 54 version 2 */
	अणुUSB_DEVICE(0x083a, 0x4531)पूर्ण,	/* T-Com Sinus 154 data II */
	अणुUSB_DEVICE(0x083a, 0xc501)पूर्ण,	/* Zoom Wireless-G 4410 */
	अणुUSB_DEVICE(0x083a, 0xf503)पूर्ण,	/* Accton FD7050E ver 1010ec  */
	अणुUSB_DEVICE(0x0846, 0x4240)पूर्ण,	/* Netgear WG111 (v2) */
	अणुUSB_DEVICE(0x0915, 0x2000)पूर्ण,	/* Cohiba Proto board */
	अणुUSB_DEVICE(0x0915, 0x2002)पूर्ण,	/* Cohiba Proto board */
	अणुUSB_DEVICE(0x0baf, 0x0118)पूर्ण,   /* U.S. Robotics U5 802.11g Adapter*/
	अणुUSB_DEVICE(0x0bf8, 0x1009)पूर्ण,   /* FUJITSU E-5400 USB D1700*/
	/* अणुUSB_DEVICE(0x0cde, 0x0006)पूर्ण, * Medion MD40900 alपढ़ोy listed above,
					 * just noting it here क्रम clarity */
	अणुUSB_DEVICE(0x0cde, 0x0008)पूर्ण,	/* Sagem XG703A */
	अणुUSB_DEVICE(0x0cde, 0x0015)पूर्ण,	/* Zcomax XG-705A */
	अणुUSB_DEVICE(0x0d8e, 0x3762)पूर्ण,	/* DLink DWL-G120 Cohiba */
	अणुUSB_DEVICE(0x124a, 0x4025)पूर्ण,	/* IOGear GWU513 (GW3887IK chip) */
	अणुUSB_DEVICE(0x1260, 0xee22)पूर्ण,	/* SMC 2862W-G version 2 */
	अणुUSB_DEVICE(0x13b1, 0x000a)पूर्ण,	/* Linksys WUSB54G ver 2 */
	अणुUSB_DEVICE(0x13B1, 0x000C)पूर्ण,	/* Linksys WUSB54AG */
	अणुUSB_DEVICE(0x1413, 0x5400)पूर्ण,   /* Tअन्यथाy 802.11g USB2.0 Adapter */
	अणुUSB_DEVICE(0x1435, 0x0427)पूर्ण,	/* Inventel UR054G */
	/* अणुUSB_DEVICE(0x15a9, 0x0002)पूर्ण, * Also SparkLAN WL-682 with 3887 */
	अणुUSB_DEVICE(0x1668, 0x1050)पूर्ण,	/* Actiontec 802UIG-1 */
	अणुUSB_DEVICE(0x1740, 0x1000)पूर्ण,	/* Senao NUB-350 */
	अणुUSB_DEVICE(0x2001, 0x3704)पूर्ण,	/* DLink DWL-G122 rev A2 */
	अणुUSB_DEVICE(0x2001, 0x3705)पूर्ण,	/* D-Link DWL-G120 rev C1 */
	अणुUSB_DEVICE(0x413c, 0x5513)पूर्ण,	/* Dell WLA3310 USB Wireless Adapter */
	अणुUSB_DEVICE(0x413c, 0x8102)पूर्ण,	/* Spinnaker DUT */
	अणुUSB_DEVICE(0x413c, 0x8104)पूर्ण,	/* Cohiba Proto board */
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, p54u_table);

अटल स्थिर काष्ठा अणु
	u32 पूर्णांकf;
	क्रमागत p54u_hw_type type;
	स्थिर अक्षर *fw;
	अक्षर hw[20];
पूर्ण p54u_fwlist[__NUM_P54U_HWTYPES] = अणु
	अणु
		.type = P54U_NET2280,
		.पूर्णांकf = FW_LM86,
		.fw = "isl3886usb",
		.hw = "ISL3886 + net2280",
	पूर्ण,
	अणु
		.type = P54U_3887,
		.पूर्णांकf = FW_LM87,
		.fw = "isl3887usb",
		.hw = "ISL3887",
	पूर्ण,
पूर्ण;

अटल व्योम p54u_rx_cb(काष्ठा urb *urb)
अणु
	काष्ठा sk_buff *skb = (काष्ठा sk_buff *) urb->context;
	काष्ठा p54u_rx_info *info = (काष्ठा p54u_rx_info *)skb->cb;
	काष्ठा ieee80211_hw *dev = info->dev;
	काष्ठा p54u_priv *priv = dev->priv;

	skb_unlink(skb, &priv->rx_queue);

	अगर (unlikely(urb->status)) अणु
		dev_kमुक्त_skb_irq(skb);
		वापस;
	पूर्ण

	skb_put(skb, urb->actual_length);

	अगर (priv->hw_type == P54U_NET2280)
		skb_pull(skb, priv->common.tx_hdr_len);
	अगर (priv->common.fw_पूर्णांकerface == FW_LM87) अणु
		skb_pull(skb, 4);
		skb_put(skb, 4);
	पूर्ण

	अगर (p54_rx(dev, skb)) अणु
		skb = dev_alloc_skb(priv->common.rx_mtu + 32);
		अगर (unlikely(!skb)) अणु
			/* TODO check rx queue length and refill *somewhere* */
			वापस;
		पूर्ण

		info = (काष्ठा p54u_rx_info *) skb->cb;
		info->urb = urb;
		info->dev = dev;
		urb->transfer_buffer = skb_tail_poपूर्णांकer(skb);
		urb->context = skb;
	पूर्ण अन्यथा अणु
		अगर (priv->hw_type == P54U_NET2280)
			skb_push(skb, priv->common.tx_hdr_len);
		अगर (priv->common.fw_पूर्णांकerface == FW_LM87) अणु
			skb_push(skb, 4);
			skb_put(skb, 4);
		पूर्ण
		skb_reset_tail_poपूर्णांकer(skb);
		skb_trim(skb, 0);
		urb->transfer_buffer = skb_tail_poपूर्णांकer(skb);
	पूर्ण
	skb_queue_tail(&priv->rx_queue, skb);
	usb_anchor_urb(urb, &priv->submitted);
	अगर (usb_submit_urb(urb, GFP_ATOMIC)) अणु
		skb_unlink(skb, &priv->rx_queue);
		usb_unanchor_urb(urb);
		dev_kमुक्त_skb_irq(skb);
	पूर्ण
पूर्ण

अटल व्योम p54u_tx_cb(काष्ठा urb *urb)
अणु
	काष्ठा sk_buff *skb = urb->context;
	काष्ठा ieee80211_hw *dev =
		usb_get_पूर्णांकfdata(usb_अगरnum_to_अगर(urb->dev, 0));

	p54_मुक्त_skb(dev, skb);
पूर्ण

अटल व्योम p54u_tx_dummy_cb(काष्ठा urb *urb) अणु पूर्ण

अटल व्योम p54u_मुक्त_urbs(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा p54u_priv *priv = dev->priv;
	usb_समाप्त_anchored_urbs(&priv->submitted);
पूर्ण

अटल व्योम p54u_stop(काष्ठा ieee80211_hw *dev)
अणु
	/*
	 * TODO: figure out how to reliably stop the 3887 and net2280 so
	 * the hardware is still usable next समय we want to start it.
	 * until then, we just stop listening to the hardware..
	 */
	p54u_मुक्त_urbs(dev);
पूर्ण

अटल पूर्णांक p54u_init_urbs(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा p54u_priv *priv = dev->priv;
	काष्ठा urb *entry = शून्य;
	काष्ठा sk_buff *skb;
	काष्ठा p54u_rx_info *info;
	पूर्णांक ret = 0;

	जबतक (skb_queue_len(&priv->rx_queue) < 32) अणु
		skb = __dev_alloc_skb(priv->common.rx_mtu + 32, GFP_KERNEL);
		अगर (!skb) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण
		entry = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!entry) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण

		usb_fill_bulk_urb(entry, priv->udev,
				  usb_rcvbulkpipe(priv->udev, P54U_PIPE_DATA),
				  skb_tail_poपूर्णांकer(skb),
				  priv->common.rx_mtu + 32, p54u_rx_cb, skb);
		info = (काष्ठा p54u_rx_info *) skb->cb;
		info->urb = entry;
		info->dev = dev;
		skb_queue_tail(&priv->rx_queue, skb);

		usb_anchor_urb(entry, &priv->submitted);
		ret = usb_submit_urb(entry, GFP_KERNEL);
		अगर (ret) अणु
			skb_unlink(skb, &priv->rx_queue);
			usb_unanchor_urb(entry);
			जाओ err;
		पूर्ण
		usb_मुक्त_urb(entry);
		entry = शून्य;
	पूर्ण

	वापस 0;

 err:
	usb_मुक्त_urb(entry);
	kमुक्त_skb(skb);
	p54u_मुक्त_urbs(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक p54u_खोलो(काष्ठा ieee80211_hw *dev)
अणु
	/*
	 * TODO: Because we करोn't know how to reliably stop the 3887 and
	 * the isl3886+net2280, other than brutally cut off all
	 * communications. We have to reinitialize the urbs on every start.
	 */
	वापस p54u_init_urbs(dev);
पूर्ण

अटल __le32 p54u_lm87_chksum(स्थिर __le32 *data, माप_प्रकार length)
अणु
	u32 chk = 0;

	length >>= 2;
	जबतक (length--) अणु
		chk ^= le32_to_cpu(*data++);
		chk = (chk >> 5) ^ (chk << 3);
	पूर्ण

	वापस cpu_to_le32(chk);
पूर्ण

अटल व्योम p54u_tx_lm87(काष्ठा ieee80211_hw *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा p54u_priv *priv = dev->priv;
	काष्ठा urb *data_urb;
	काष्ठा lm87_tx_hdr *hdr = (व्योम *)skb->data - माप(*hdr);

	data_urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!data_urb) अणु
		p54_मुक्त_skb(dev, skb);
		वापस;
	पूर्ण

	hdr->chksum = p54u_lm87_chksum((__le32 *)skb->data, skb->len);
	hdr->device_addr = ((काष्ठा p54_hdr *)skb->data)->req_id;

	usb_fill_bulk_urb(data_urb, priv->udev,
			  usb_sndbulkpipe(priv->udev, P54U_PIPE_DATA),
			  hdr, skb->len + माप(*hdr),  FREE_AFTER_TX(skb) ?
			  p54u_tx_cb : p54u_tx_dummy_cb, skb);
	data_urb->transfer_flags |= URB_ZERO_PACKET;

	usb_anchor_urb(data_urb, &priv->submitted);
	अगर (usb_submit_urb(data_urb, GFP_ATOMIC)) अणु
		usb_unanchor_urb(data_urb);
		p54_मुक्त_skb(dev, skb);
	पूर्ण
	usb_मुक्त_urb(data_urb);
पूर्ण

अटल व्योम p54u_tx_net2280(काष्ठा ieee80211_hw *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा p54u_priv *priv = dev->priv;
	काष्ठा urb *पूर्णांक_urb = शून्य, *data_urb = शून्य;
	काष्ठा net2280_tx_hdr *hdr = (व्योम *)skb->data - माप(*hdr);
	काष्ठा net2280_reg_ग_लिखो *reg = शून्य;
	पूर्णांक err = -ENOMEM;

	reg = kदो_स्मृति(माप(*reg), GFP_ATOMIC);
	अगर (!reg)
		जाओ out;

	पूर्णांक_urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!पूर्णांक_urb)
		जाओ out;

	data_urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!data_urb)
		जाओ out;

	reg->port = cpu_to_le16(NET2280_DEV_U32);
	reg->addr = cpu_to_le32(P54U_DEV_BASE);
	reg->val = cpu_to_le32(ISL38XX_DEV_INT_DATA);

	स_रखो(hdr, 0, माप(*hdr));
	hdr->len = cpu_to_le16(skb->len);
	hdr->device_addr = ((काष्ठा p54_hdr *) skb->data)->req_id;

	usb_fill_bulk_urb(पूर्णांक_urb, priv->udev,
		usb_sndbulkpipe(priv->udev, P54U_PIPE_DEV), reg, माप(*reg),
		p54u_tx_dummy_cb, dev);

	/*
	 * URB_FREE_BUFFER triggers a code path in the USB subप्रणाली that will
	 * मुक्त what is inside the transfer_buffer after the last reference to
	 * the पूर्णांक_urb is dropped.
	 */
	पूर्णांक_urb->transfer_flags |= URB_FREE_BUFFER | URB_ZERO_PACKET;
	reg = शून्य;

	usb_fill_bulk_urb(data_urb, priv->udev,
			  usb_sndbulkpipe(priv->udev, P54U_PIPE_DATA),
			  hdr, skb->len + माप(*hdr), FREE_AFTER_TX(skb) ?
			  p54u_tx_cb : p54u_tx_dummy_cb, skb);
	data_urb->transfer_flags |= URB_ZERO_PACKET;

	usb_anchor_urb(पूर्णांक_urb, &priv->submitted);
	err = usb_submit_urb(पूर्णांक_urb, GFP_ATOMIC);
	अगर (err) अणु
		usb_unanchor_urb(पूर्णांक_urb);
		जाओ out;
	पूर्ण

	usb_anchor_urb(data_urb, &priv->submitted);
	err = usb_submit_urb(data_urb, GFP_ATOMIC);
	अगर (err) अणु
		usb_unanchor_urb(data_urb);
		जाओ out;
	पूर्ण
out:
	usb_मुक्त_urb(पूर्णांक_urb);
	usb_मुक्त_urb(data_urb);

	अगर (err) अणु
		kमुक्त(reg);
		p54_मुक्त_skb(dev, skb);
	पूर्ण
पूर्ण

अटल पूर्णांक p54u_ग_लिखो(काष्ठा p54u_priv *priv,
		      काष्ठा net2280_reg_ग_लिखो *buf,
		      क्रमागत net2280_op_type type,
		      __le32 addr, __le32 val)
अणु
	अचिन्हित पूर्णांक ep;
	पूर्णांक alen;

	अगर (type & 0x0800)
		ep = usb_sndbulkpipe(priv->udev, P54U_PIPE_DEV);
	अन्यथा
		ep = usb_sndbulkpipe(priv->udev, P54U_PIPE_BRG);

	buf->port = cpu_to_le16(type);
	buf->addr = addr;
	buf->val = val;

	वापस usb_bulk_msg(priv->udev, ep, buf, माप(*buf), &alen, 1000);
पूर्ण

अटल पूर्णांक p54u_पढ़ो(काष्ठा p54u_priv *priv, व्योम *buf,
		     क्रमागत net2280_op_type type,
		     __le32 addr, __le32 *val)
अणु
	काष्ठा net2280_reg_पढ़ो *पढ़ो = buf;
	__le32 *reg = buf;
	अचिन्हित पूर्णांक ep;
	पूर्णांक alen, err;

	अगर (type & 0x0800)
		ep = P54U_PIPE_DEV;
	अन्यथा
		ep = P54U_PIPE_BRG;

	पढ़ो->port = cpu_to_le16(type);
	पढ़ो->addr = addr;

	err = usb_bulk_msg(priv->udev, usb_sndbulkpipe(priv->udev, ep),
			   पढ़ो, माप(*पढ़ो), &alen, 1000);
	अगर (err)
		वापस err;

	err = usb_bulk_msg(priv->udev, usb_rcvbulkpipe(priv->udev, ep),
			   reg, माप(*reg), &alen, 1000);
	अगर (err)
		वापस err;

	*val = *reg;
	वापस 0;
पूर्ण

अटल पूर्णांक p54u_bulk_msg(काष्ठा p54u_priv *priv, अचिन्हित पूर्णांक ep,
			 व्योम *data, माप_प्रकार len)
अणु
	पूर्णांक alen;
	वापस usb_bulk_msg(priv->udev, usb_sndbulkpipe(priv->udev, ep),
			    data, len, &alen, 2000);
पूर्ण

अटल पूर्णांक p54u_device_reset(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा p54u_priv *priv = dev->priv;
	पूर्णांक ret, lock = (priv->पूर्णांकf->condition != USB_INTERFACE_BINDING);

	अगर (lock) अणु
		ret = usb_lock_device_क्रम_reset(priv->udev, priv->पूर्णांकf);
		अगर (ret < 0) अणु
			dev_err(&priv->udev->dev, "(p54usb) unable to lock "
				"device for reset (%d)!\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = usb_reset_device(priv->udev);
	अगर (lock)
		usb_unlock_device(priv->udev);

	अगर (ret)
		dev_err(&priv->udev->dev, "(p54usb) unable to reset "
			"device (%d)!\n", ret);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर p54u_romboot_3887[] = "~~~~";
अटल पूर्णांक p54u_firmware_reset_3887(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा p54u_priv *priv = dev->priv;
	u8 *buf;
	पूर्णांक ret;

	buf = kmemdup(p54u_romboot_3887, 4, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;
	ret = p54u_bulk_msg(priv, P54U_PIPE_DATA,
			    buf, 4);
	kमुक्त(buf);
	अगर (ret)
		dev_err(&priv->udev->dev, "(p54usb) unable to jump to "
			"boot ROM (%d)!\n", ret);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर p54u_firmware_upload_3887[] = "<\r";
अटल पूर्णांक p54u_upload_firmware_3887(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा p54u_priv *priv = dev->priv;
	पूर्णांक err, alen;
	u8 carry = 0;
	u8 *buf, *पंचांगp;
	स्थिर u8 *data;
	अचिन्हित पूर्णांक left, reमुख्यs, block_size;
	काष्ठा x2_header *hdr;
	अचिन्हित दीर्घ समयout;

	err = p54u_firmware_reset_3887(dev);
	अगर (err)
		वापस err;

	पंचांगp = buf = kदो_स्मृति(P54U_FW_BLOCK, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	left = block_size = min_t(माप_प्रकार, P54U_FW_BLOCK, priv->fw->size);
	म_नकल(buf, p54u_firmware_upload_3887);
	left -= म_माप(p54u_firmware_upload_3887);
	पंचांगp += म_माप(p54u_firmware_upload_3887);

	data = priv->fw->data;
	reमुख्यs = priv->fw->size;

	hdr = (काष्ठा x2_header *)(buf + म_माप(p54u_firmware_upload_3887));
	स_नकल(hdr->signature, X2_SIGNATURE, X2_SIGNATURE_SIZE);
	hdr->fw_load_addr = cpu_to_le32(ISL38XX_DEV_FIRMWARE_ADDR);
	hdr->fw_length = cpu_to_le32(priv->fw->size);
	hdr->crc = cpu_to_le32(~crc32_le(~0, (व्योम *)&hdr->fw_load_addr,
					 माप(u32)*2));
	left -= माप(*hdr);
	पंचांगp += माप(*hdr);

	जबतक (reमुख्यs) अणु
		जबतक (left--) अणु
			अगर (carry) अणु
				*पंचांगp++ = carry;
				carry = 0;
				reमुख्यs--;
				जारी;
			पूर्ण
			चयन (*data) अणु
			हाल '~':
				*पंचांगp++ = '}';
				carry = '^';
				अवरोध;
			हाल '}':
				*पंचांगp++ = '}';
				carry = ']';
				अवरोध;
			शेष:
				*पंचांगp++ = *data;
				reमुख्यs--;
				अवरोध;
			पूर्ण
			data++;
		पूर्ण

		err = p54u_bulk_msg(priv, P54U_PIPE_DATA, buf, block_size);
		अगर (err) अणु
			dev_err(&priv->udev->dev, "(p54usb) firmware "
						  "upload failed!\n");
			जाओ err_upload_failed;
		पूर्ण

		पंचांगp = buf;
		left = block_size = min((अचिन्हित पूर्णांक)P54U_FW_BLOCK, reमुख्यs);
	पूर्ण

	*((__le32 *)buf) = cpu_to_le32(~crc32_le(~0, priv->fw->data,
						 priv->fw->size));
	err = p54u_bulk_msg(priv, P54U_PIPE_DATA, buf, माप(u32));
	अगर (err) अणु
		dev_err(&priv->udev->dev, "(p54usb) firmware upload failed!\n");
		जाओ err_upload_failed;
	पूर्ण
	समयout = jअगरfies + msecs_to_jअगरfies(1000);
	जबतक (!(err = usb_bulk_msg(priv->udev,
		usb_rcvbulkpipe(priv->udev, P54U_PIPE_DATA), buf, 128, &alen, 1000))) अणु
		अगर (alen > 2 && !स_भेद(buf, "OK", 2))
			अवरोध;

		अगर (alen > 5 && !स_भेद(buf, "ERROR", 5)) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (समय_after(jअगरfies, समयout)) अणु
			dev_err(&priv->udev->dev, "(p54usb) firmware boot "
						  "timed out!\n");
			err = -ETIMEDOUT;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (err) अणु
		dev_err(&priv->udev->dev, "(p54usb) firmware upload failed!\n");
		जाओ err_upload_failed;
	पूर्ण

	buf[0] = 'g';
	buf[1] = '\r';
	err = p54u_bulk_msg(priv, P54U_PIPE_DATA, buf, 2);
	अगर (err) अणु
		dev_err(&priv->udev->dev, "(p54usb) firmware boot failed!\n");
		जाओ err_upload_failed;
	पूर्ण

	समयout = jअगरfies + msecs_to_jअगरfies(1000);
	जबतक (!(err = usb_bulk_msg(priv->udev,
		usb_rcvbulkpipe(priv->udev, P54U_PIPE_DATA), buf, 128, &alen, 1000))) अणु
		अगर (alen > 0 && buf[0] == 'g')
			अवरोध;

		अगर (समय_after(jअगरfies, समयout)) अणु
			err = -ETIMEDOUT;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (err)
		जाओ err_upload_failed;

err_upload_failed:
	kमुक्त(buf);
	वापस err;
पूर्ण

अटल पूर्णांक p54u_upload_firmware_net2280(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा p54u_priv *priv = dev->priv;
	स्थिर काष्ठा p54p_csr *devreg = (स्थिर काष्ठा p54p_csr *) P54U_DEV_BASE;
	पूर्णांक err, alen;
	व्योम *buf;
	__le32 reg;
	अचिन्हित पूर्णांक reमुख्यs, offset;
	स्थिर u8 *data;

	buf = kदो_स्मृति(512, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

#घोषणा P54U_WRITE(type, addr, data) \
	करो अणु\
		err = p54u_ग_लिखो(priv, buf, type,\
				 cpu_to_le32((u32)(अचिन्हित दीर्घ)addr), data);\
		अगर (err) \
			जाओ fail;\
	पूर्ण जबतक (0)

#घोषणा P54U_READ(type, addr) \
	करो अणु\
		err = p54u_पढ़ो(priv, buf, type,\
				cpu_to_le32((u32)(अचिन्हित दीर्घ)addr), &reg);\
		अगर (err)\
			जाओ fail;\
	पूर्ण जबतक (0)

	/* घातer करोwn net2280 bridge */
	P54U_READ(NET2280_BRG_U32, NET2280_GPIOCTL);
	reg |= cpu_to_le32(P54U_BRG_POWER_DOWN);
	reg &= cpu_to_le32(~P54U_BRG_POWER_UP);
	P54U_WRITE(NET2280_BRG_U32, NET2280_GPIOCTL, reg);

	mdelay(100);

	/* घातer up bridge */
	reg |= cpu_to_le32(P54U_BRG_POWER_UP);
	reg &= cpu_to_le32(~P54U_BRG_POWER_DOWN);
	P54U_WRITE(NET2280_BRG_U32, NET2280_GPIOCTL, reg);

	mdelay(100);

	P54U_WRITE(NET2280_BRG_U32, NET2280_DEVINIT,
		   cpu_to_le32(NET2280_CLK_30Mhz |
			       NET2280_PCI_ENABLE |
			       NET2280_PCI_SOFT_RESET));

	mdelay(20);

	P54U_WRITE(NET2280_BRG_CFG_U16, PCI_COMMAND,
		   cpu_to_le32(PCI_COMMAND_MEMORY |
			       PCI_COMMAND_MASTER));

	P54U_WRITE(NET2280_BRG_CFG_U32, PCI_BASE_ADDRESS_0,
		   cpu_to_le32(NET2280_BASE));

	P54U_READ(NET2280_BRG_CFG_U16, PCI_STATUS);
	reg |= cpu_to_le32(PCI_STATUS_REC_MASTER_ABORT);
	P54U_WRITE(NET2280_BRG_CFG_U16, PCI_STATUS, reg);

	// TODO: we really need this?
	P54U_READ(NET2280_BRG_U32, NET2280_RELNUM);

	P54U_WRITE(NET2280_BRG_U32, NET2280_EPA_RSP,
		   cpu_to_le32(NET2280_CLEAR_NAK_OUT_PACKETS_MODE));
	P54U_WRITE(NET2280_BRG_U32, NET2280_EPC_RSP,
		   cpu_to_le32(NET2280_CLEAR_NAK_OUT_PACKETS_MODE));

	P54U_WRITE(NET2280_BRG_CFG_U32, PCI_BASE_ADDRESS_2,
		   cpu_to_le32(NET2280_BASE2));

	/* finally करोne setting up the bridge */

	P54U_WRITE(NET2280_DEV_CFG_U16, 0x10000 | PCI_COMMAND,
		   cpu_to_le32(PCI_COMMAND_MEMORY |
			       PCI_COMMAND_MASTER));

	P54U_WRITE(NET2280_DEV_CFG_U16, 0x10000 | 0x40 /* TRDY समयout */, 0);
	P54U_WRITE(NET2280_DEV_CFG_U32, 0x10000 | PCI_BASE_ADDRESS_0,
		   cpu_to_le32(P54U_DEV_BASE));

	P54U_WRITE(NET2280_BRG_U32, NET2280_USBIRQENB1, 0);
	P54U_WRITE(NET2280_BRG_U32, NET2280_IRQSTAT1,
		   cpu_to_le32(NET2280_PCI_INTA_INTERRUPT));

	/* करो romboot */
	P54U_WRITE(NET2280_DEV_U32, &devreg->पूर्णांक_enable, 0);

	P54U_READ(NET2280_DEV_U32, &devreg->ctrl_stat);
	reg &= cpu_to_le32(~ISL38XX_CTRL_STAT_RESET);
	reg &= cpu_to_le32(~ISL38XX_CTRL_STAT_RAMBOOT);
	reg &= cpu_to_le32(~ISL38XX_CTRL_STAT_CLKRUN);
	P54U_WRITE(NET2280_DEV_U32, &devreg->ctrl_stat, reg);

	mdelay(20);

	reg |= cpu_to_le32(ISL38XX_CTRL_STAT_RESET);
	P54U_WRITE(NET2280_DEV_U32, &devreg->ctrl_stat, reg);

	mdelay(20);

	reg &= cpu_to_le32(~ISL38XX_CTRL_STAT_RESET);
	P54U_WRITE(NET2280_DEV_U32, &devreg->ctrl_stat, reg);

	mdelay(100);

	P54U_READ(NET2280_DEV_U32, &devreg->पूर्णांक_ident);
	P54U_WRITE(NET2280_DEV_U32, &devreg->पूर्णांक_ack, reg);

	/* finally, we can upload firmware now! */
	reमुख्यs = priv->fw->size;
	data = priv->fw->data;
	offset = ISL38XX_DEV_FIRMWARE_ADDR;

	जबतक (reमुख्यs) अणु
		अचिन्हित पूर्णांक block_len = min(reमुख्यs, (अचिन्हित पूर्णांक)512);
		स_नकल(buf, data, block_len);

		err = p54u_bulk_msg(priv, P54U_PIPE_DATA, buf, block_len);
		अगर (err) अणु
			dev_err(&priv->udev->dev, "(p54usb) firmware block "
						  "upload failed\n");
			जाओ fail;
		पूर्ण

		P54U_WRITE(NET2280_DEV_U32, &devreg->direct_mem_base,
			   cpu_to_le32(0xc0000f00));

		P54U_WRITE(NET2280_DEV_U32,
			   0x0020 | (अचिन्हित दीर्घ)&devreg->direct_mem_win, 0);
		P54U_WRITE(NET2280_DEV_U32,
			   0x0020 | (अचिन्हित दीर्घ)&devreg->direct_mem_win,
			   cpu_to_le32(1));

		P54U_WRITE(NET2280_DEV_U32,
			   0x0024 | (अचिन्हित दीर्घ)&devreg->direct_mem_win,
			   cpu_to_le32(block_len));
		P54U_WRITE(NET2280_DEV_U32,
			   0x0028 | (अचिन्हित दीर्घ)&devreg->direct_mem_win,
			   cpu_to_le32(offset));

		P54U_WRITE(NET2280_DEV_U32, &devreg->dma_addr,
			   cpu_to_le32(NET2280_EPA_FIFO_PCI_ADDR));
		P54U_WRITE(NET2280_DEV_U32, &devreg->dma_len,
			   cpu_to_le32(block_len >> 2));
		P54U_WRITE(NET2280_DEV_U32, &devreg->dma_ctrl,
			   cpu_to_le32(ISL38XX_DMA_MASTER_CONTROL_TRIGGER));

		mdelay(10);

		P54U_READ(NET2280_DEV_U32,
			  0x002C | (अचिन्हित दीर्घ)&devreg->direct_mem_win);
		अगर (!(reg & cpu_to_le32(ISL38XX_DMA_STATUS_DONE)) ||
		    !(reg & cpu_to_le32(ISL38XX_DMA_STATUS_READY))) अणु
			dev_err(&priv->udev->dev, "(p54usb) firmware DMA "
						  "transfer failed\n");
			जाओ fail;
		पूर्ण

		P54U_WRITE(NET2280_BRG_U32, NET2280_EPA_STAT,
			   cpu_to_le32(NET2280_FIFO_FLUSH));

		reमुख्यs -= block_len;
		data += block_len;
		offset += block_len;
	पूर्ण

	/* करो ramboot */
	P54U_READ(NET2280_DEV_U32, &devreg->ctrl_stat);
	reg &= cpu_to_le32(~ISL38XX_CTRL_STAT_RESET);
	reg &= cpu_to_le32(~ISL38XX_CTRL_STAT_CLKRUN);
	reg |= cpu_to_le32(ISL38XX_CTRL_STAT_RAMBOOT);
	P54U_WRITE(NET2280_DEV_U32, &devreg->ctrl_stat, reg);

	mdelay(20);

	reg |= cpu_to_le32(ISL38XX_CTRL_STAT_RESET);
	P54U_WRITE(NET2280_DEV_U32, &devreg->ctrl_stat, reg);

	reg &= cpu_to_le32(~ISL38XX_CTRL_STAT_RESET);
	P54U_WRITE(NET2280_DEV_U32, &devreg->ctrl_stat, reg);

	mdelay(100);

	P54U_READ(NET2280_DEV_U32, &devreg->पूर्णांक_ident);
	P54U_WRITE(NET2280_DEV_U32, &devreg->पूर्णांक_ack, reg);

	/* start up the firmware */
	P54U_WRITE(NET2280_DEV_U32, &devreg->पूर्णांक_enable,
		   cpu_to_le32(ISL38XX_INT_IDENT_INIT));

	P54U_WRITE(NET2280_BRG_U32, NET2280_IRQSTAT1,
		   cpu_to_le32(NET2280_PCI_INTA_INTERRUPT));

	P54U_WRITE(NET2280_BRG_U32, NET2280_USBIRQENB1,
		   cpu_to_le32(NET2280_PCI_INTA_INTERRUPT_ENABLE |
			       NET2280_USB_INTERRUPT_ENABLE));

	P54U_WRITE(NET2280_DEV_U32, &devreg->dev_पूर्णांक,
		   cpu_to_le32(ISL38XX_DEV_INT_RESET));

	err = usb_पूर्णांकerrupt_msg(priv->udev,
				usb_rcvbulkpipe(priv->udev, P54U_PIPE_INT),
				buf, माप(__le32), &alen, 1000);
	अगर (err || alen != माप(__le32))
		जाओ fail;

	P54U_READ(NET2280_DEV_U32, &devreg->पूर्णांक_ident);
	P54U_WRITE(NET2280_DEV_U32, &devreg->पूर्णांक_ack, reg);

	अगर (!(reg & cpu_to_le32(ISL38XX_INT_IDENT_INIT)))
		err = -EINVAL;

	P54U_WRITE(NET2280_BRG_U32, NET2280_USBIRQENB1, 0);
	P54U_WRITE(NET2280_BRG_U32, NET2280_IRQSTAT1,
		   cpu_to_le32(NET2280_PCI_INTA_INTERRUPT));

#अघोषित P54U_WRITE
#अघोषित P54U_READ

fail:
	kमुक्त(buf);
	वापस err;
पूर्ण

अटल पूर्णांक p54_find_type(काष्ठा p54u_priv *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < __NUM_P54U_HWTYPES; i++)
		अगर (p54u_fwlist[i].type == priv->hw_type)
			अवरोध;
	अगर (i == __NUM_P54U_HWTYPES)
		वापस -EOPNOTSUPP;

	वापस i;
पूर्ण

अटल पूर्णांक p54u_start_ops(काष्ठा p54u_priv *priv)
अणु
	काष्ठा ieee80211_hw *dev = priv->common.hw;
	पूर्णांक ret;

	ret = p54_parse_firmware(dev, priv->fw);
	अगर (ret)
		जाओ err_out;

	ret = p54_find_type(priv);
	अगर (ret < 0)
		जाओ err_out;

	अगर (priv->common.fw_पूर्णांकerface != p54u_fwlist[ret].पूर्णांकf) अणु
		dev_err(&priv->udev->dev, "wrong firmware, please get "
			"a firmware for \"%s\" and try again.\n",
			p54u_fwlist[ret].hw);
		ret = -ENODEV;
		जाओ err_out;
	पूर्ण

	ret = priv->upload_fw(dev);
	अगर (ret)
		जाओ err_out;

	ret = p54u_खोलो(dev);
	अगर (ret)
		जाओ err_out;

	ret = p54_पढ़ो_eeprom(dev);
	अगर (ret)
		जाओ err_stop;

	p54u_stop(dev);

	ret = p54_रेजिस्टर_common(dev, &priv->udev->dev);
	अगर (ret)
		जाओ err_stop;

	वापस 0;

err_stop:
	p54u_stop(dev);

err_out:
	/*
	 * p54u_disconnect will करो the rest of the
	 * cleanup
	 */
	वापस ret;
पूर्ण

अटल व्योम p54u_load_firmware_cb(स्थिर काष्ठा firmware *firmware,
				  व्योम *context)
अणु
	काष्ठा p54u_priv *priv = context;
	काष्ठा usb_device *udev = priv->udev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = priv->पूर्णांकf;
	पूर्णांक err;

	अगर (firmware) अणु
		priv->fw = firmware;
		err = p54u_start_ops(priv);
	पूर्ण अन्यथा अणु
		err = -ENOENT;
		dev_err(&udev->dev, "Firmware not found.\n");
	पूर्ण

	complete(&priv->fw_रुको_load);
	/*
	 * At this poपूर्णांक p54u_disconnect may have alपढ़ोy मुक्तd
	 * the "priv" context. Do not use it anymore!
	 */
	priv = शून्य;

	अगर (err) अणु
		dev_err(&पूर्णांकf->dev, "failed to initialize device (%d)\n", err);

		usb_lock_device(udev);
		usb_driver_release_पूर्णांकerface(&p54u_driver, पूर्णांकf);
		usb_unlock_device(udev);
	पूर्ण

	usb_put_पूर्णांकf(पूर्णांकf);
पूर्ण

अटल पूर्णांक p54u_load_firmware(काष्ठा ieee80211_hw *dev,
			      काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा p54u_priv *priv = dev->priv;
	काष्ठा device *device = &udev->dev;
	पूर्णांक err, i;

	BUILD_BUG_ON(ARRAY_SIZE(p54u_fwlist) != __NUM_P54U_HWTYPES);

	init_completion(&priv->fw_रुको_load);
	i = p54_find_type(priv);
	अगर (i < 0)
		वापस i;

	dev_info(&priv->udev->dev, "Loading firmware file %s\n",
	       p54u_fwlist[i].fw);

	usb_get_पूर्णांकf(पूर्णांकf);
	err = request_firmware_noरुको(THIS_MODULE, 1, p54u_fwlist[i].fw,
				      device, GFP_KERNEL, priv,
				      p54u_load_firmware_cb);
	अगर (err) अणु
		dev_err(&priv->udev->dev, "(p54usb) cannot load firmware %s "
					  "(%d)!\n", p54u_fwlist[i].fw, err);
		usb_put_पूर्णांकf(पूर्णांकf);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक p54u_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
				स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा ieee80211_hw *dev;
	काष्ठा p54u_priv *priv;
	पूर्णांक err;
	अचिन्हित पूर्णांक i, recognized_pipes;

	dev = p54_init_common(माप(*priv));

	अगर (!dev) अणु
		dev_err(&udev->dev, "(p54usb) ieee80211 alloc failed\n");
		वापस -ENOMEM;
	पूर्ण

	priv = dev->priv;
	priv->hw_type = P54U_INVALID_HW;

	SET_IEEE80211_DEV(dev, &पूर्णांकf->dev);
	usb_set_पूर्णांकfdata(पूर्णांकf, dev);
	priv->udev = udev;
	priv->पूर्णांकf = पूर्णांकf;
	skb_queue_head_init(&priv->rx_queue);
	init_usb_anchor(&priv->submitted);

	/* really lazy and simple way of figuring out अगर we're a 3887 */
	/* TODO: should just stick the identअगरication in the device table */
	i = पूर्णांकf->altsetting->desc.bNumEndpoपूर्णांकs;
	recognized_pipes = 0;
	जबतक (i--) अणु
		चयन (पूर्णांकf->altsetting->endpoपूर्णांक[i].desc.bEndpoपूर्णांकAddress) अणु
		हाल P54U_PIPE_DATA:
		हाल P54U_PIPE_MGMT:
		हाल P54U_PIPE_BRG:
		हाल P54U_PIPE_DEV:
		हाल P54U_PIPE_DATA | USB_सूची_IN:
		हाल P54U_PIPE_MGMT | USB_सूची_IN:
		हाल P54U_PIPE_BRG | USB_सूची_IN:
		हाल P54U_PIPE_DEV | USB_सूची_IN:
		हाल P54U_PIPE_INT | USB_सूची_IN:
			recognized_pipes++;
		पूर्ण
	पूर्ण
	priv->common.खोलो = p54u_खोलो;
	priv->common.stop = p54u_stop;
	अगर (recognized_pipes < P54U_PIPE_NUMBER) अणु
#अगर_घोषित CONFIG_PM
		/* ISL3887 needs a full reset on resume */
		udev->reset_resume = 1;
#पूर्ण_अगर /* CONFIG_PM */
		err = p54u_device_reset(dev);

		priv->hw_type = P54U_3887;
		dev->extra_tx_headroom += माप(काष्ठा lm87_tx_hdr);
		priv->common.tx_hdr_len = माप(काष्ठा lm87_tx_hdr);
		priv->common.tx = p54u_tx_lm87;
		priv->upload_fw = p54u_upload_firmware_3887;
	पूर्ण अन्यथा अणु
		priv->hw_type = P54U_NET2280;
		dev->extra_tx_headroom += माप(काष्ठा net2280_tx_hdr);
		priv->common.tx_hdr_len = माप(काष्ठा net2280_tx_hdr);
		priv->common.tx = p54u_tx_net2280;
		priv->upload_fw = p54u_upload_firmware_net2280;
	पूर्ण
	err = p54u_load_firmware(dev, पूर्णांकf);
	अगर (err)
		p54_मुक्त_common(dev);
	वापस err;
पूर्ण

अटल व्योम p54u_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा ieee80211_hw *dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा p54u_priv *priv;

	अगर (!dev)
		वापस;

	priv = dev->priv;
	रुको_क्रम_completion(&priv->fw_रुको_load);
	p54_unरेजिस्टर_common(dev);

	release_firmware(priv->fw);
	p54_मुक्त_common(dev);
पूर्ण

अटल पूर्णांक p54u_pre_reset(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा ieee80211_hw *dev = usb_get_पूर्णांकfdata(पूर्णांकf);

	अगर (!dev)
		वापस -ENODEV;

	p54u_stop(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक p54u_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा ieee80211_hw *dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा p54u_priv *priv;

	अगर (!dev)
		वापस -ENODEV;

	priv = dev->priv;
	अगर (unlikely(!(priv->upload_fw && priv->fw)))
		वापस 0;

	वापस priv->upload_fw(dev);
पूर्ण

अटल पूर्णांक p54u_post_reset(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा ieee80211_hw *dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा p54u_priv *priv;
	पूर्णांक err;

	err = p54u_resume(पूर्णांकf);
	अगर (err)
		वापस err;

	/* reinitialize old device state */
	priv = dev->priv;
	अगर (priv->common.mode != NL80211_IFTYPE_UNSPECIFIED)
		ieee80211_restart_hw(dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक p54u_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	वापस p54u_pre_reset(पूर्णांकf);
पूर्ण

#पूर्ण_अगर /* CONFIG_PM */

अटल काष्ठा usb_driver p54u_driver = अणु
	.name	= "p54usb",
	.id_table = p54u_table,
	.probe = p54u_probe,
	.disconnect = p54u_disconnect,
	.pre_reset = p54u_pre_reset,
	.post_reset = p54u_post_reset,
#अगर_घोषित CONFIG_PM
	.suspend = p54u_suspend,
	.resume = p54u_resume,
	.reset_resume = p54u_resume,
#पूर्ण_अगर /* CONFIG_PM */
	.soft_unbind = 1,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(p54u_driver);
