<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Ethernet पूर्णांकerface part of the LG VL600 LTE modem (4G करोngle)
 *
 * Copyright (C) 2011 Intel Corporation
 * Author: Andrzej Zaborowski <balrogg@gmail.com>
 */
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/cdc.h>
#समावेश <linux/usb/usbnet.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/module.h>

/*
 * The device has a CDC ACM port क्रम modem control (it claims to be
 * CDC ACM anyway) and a CDC Ethernet port क्रम actual network data.
 * It will however ignore data on both ports that is not encapsulated
 * in a specअगरic way, any data वापसed is also encapsulated the same
 * way.  The headers करोn't seem to follow any popular standard.
 *
 * This driver adds and strips these headers from the ethernet frames
 * sent/received from the CDC Ethernet port.  The proprietary header
 * replaces the standard ethernet header in a packet so only actual
 * ethernet frames are allowed.  The headers allow some क्रमm of
 * multiplexing by using non standard values of the .h_proto field.
 * Winकरोws/Mac drivers करो send a couple of such frames to the device
 * during initialisation, with protocol set to 0x0906 or 0x0b06 and (what
 * seems to be) a flag in the .dummy_flags.  This करोesn't seem necessary
 * क्रम modem operation but can possibly be used क्रम GPS or other funcitons.
 */

काष्ठा vl600_frame_hdr अणु
	__le32 len;
	__le32 serial;
	__le32 pkt_cnt;
	__le32 dummy_flags;
	__le32 dummy;
	__le32 magic;
पूर्ण __attribute__((packed));

काष्ठा vl600_pkt_hdr अणु
	__le32 dummy[2];
	__le32 len;
	__be16 h_proto;
पूर्ण __attribute__((packed));

काष्ठा vl600_state अणु
	काष्ठा sk_buff *current_rx_buf;
पूर्ण;

अटल पूर्णांक vl600_bind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	पूर्णांक ret;
	काष्ठा vl600_state *s = kzalloc(माप(काष्ठा vl600_state), GFP_KERNEL);

	अगर (!s)
		वापस -ENOMEM;

	ret = usbnet_cdc_bind(dev, पूर्णांकf);
	अगर (ret) अणु
		kमुक्त(s);
		वापस ret;
	पूर्ण

	dev->driver_priv = s;

	/* ARP packets करोn't go through, but they're also of no use.  The
	 * subnet has only two hosts anyway: us and the gateway / DHCP
	 * server (probably simulated by modem firmware or network चालक)
	 * whose address changes everyसमय we connect to the पूर्णांकarwebz and
	 * who करोesn't bother answering ARP requests either.  So hardware
	 * addresses have no meaning, the destination and the source of every
	 * packet depend only on whether it is on the IN or OUT endpoपूर्णांक.  */
	dev->net->flags |= IFF_NOARP;
	/* IPv6 NDP relies on multicast.  Enable it by शेष. */
	dev->net->flags |= IFF_MULTICAST;

	वापस ret;
पूर्ण

अटल व्योम vl600_unbind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा vl600_state *s = dev->driver_priv;

	dev_kमुक्त_skb(s->current_rx_buf);
	kमुक्त(s);

	वापस usbnet_cdc_unbind(dev, पूर्णांकf);
पूर्ण

अटल पूर्णांक vl600_rx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा vl600_frame_hdr *frame;
	काष्ठा vl600_pkt_hdr *packet;
	काष्ठा ethhdr *ethhdr;
	पूर्णांक packet_len, count;
	काष्ठा sk_buff *buf = skb;
	काष्ठा sk_buff *clone;
	काष्ठा vl600_state *s = dev->driver_priv;

	/* Frame lengths are generally 4B multiplies but every couple of
	 * hours there's an odd number of bytes sized yet correct frame,
	 * so करोn't require this.  */

	/* Allow a packet (or multiple packets batched together) to be
	 * split across many frames.  We करोn't allow a new batch to
	 * begin in the same frame another one is ending however, and no
	 * leading or trailing pad bytes.  */
	अगर (s->current_rx_buf) अणु
		frame = (काष्ठा vl600_frame_hdr *) s->current_rx_buf->data;
		अगर (skb->len + s->current_rx_buf->len >
				le32_to_cpup(&frame->len)) अणु
			netअगर_err(dev, अगरup, dev->net, "Fragment too long\n");
			dev->net->stats.rx_length_errors++;
			जाओ error;
		पूर्ण

		buf = s->current_rx_buf;
		skb_put_data(buf, skb->data, skb->len);
	पूर्ण अन्यथा अगर (skb->len < 4) अणु
		netअगर_err(dev, अगरup, dev->net, "Frame too short\n");
		dev->net->stats.rx_length_errors++;
		जाओ error;
	पूर्ण

	frame = (काष्ठा vl600_frame_hdr *) buf->data;
	/* Yes, check that frame->magic == 0x53544448 (or 0x44544d48),
	 * otherwise we may run out of memory w/a bad packet */
	अगर (ntohl(frame->magic) != 0x53544448 &&
			ntohl(frame->magic) != 0x44544d48)
		जाओ error;

	अगर (buf->len < माप(*frame) ||
			buf->len != le32_to_cpup(&frame->len)) अणु
		/* Save this fragment क्रम later assembly */
		अगर (s->current_rx_buf)
			वापस 0;

		s->current_rx_buf = skb_copy_expand(skb, 0,
				le32_to_cpup(&frame->len), GFP_ATOMIC);
		अगर (!s->current_rx_buf)
			dev->net->stats.rx_errors++;

		वापस 0;
	पूर्ण

	count = le32_to_cpup(&frame->pkt_cnt);

	skb_pull(buf, माप(*frame));

	जबतक (count--) अणु
		अगर (buf->len < माप(*packet)) अणु
			netअगर_err(dev, अगरup, dev->net, "Packet too short\n");
			जाओ error;
		पूर्ण

		packet = (काष्ठा vl600_pkt_hdr *) buf->data;
		packet_len = माप(*packet) + le32_to_cpup(&packet->len);
		अगर (packet_len > buf->len) अणु
			netअगर_err(dev, अगरup, dev->net,
					"Bad packet length stored in header\n");
			जाओ error;
		पूर्ण

		/* Packet header is same size as the ethernet header
		 * (माप(*packet) == माप(*ethhdr)), additionally
		 * the h_proto field is in the same place so we just leave it
		 * alone and fill in the reमुख्यing fields.
		 */
		ethhdr = (काष्ठा ethhdr *) skb->data;
		अगर (be16_to_cpup(&ethhdr->h_proto) == ETH_P_ARP &&
				buf->len > 0x26) अणु
			/* Copy the addresses from packet contents */
			स_नकल(ethhdr->h_source,
					&buf->data[माप(*ethhdr) + 0x8],
					ETH_ALEN);
			स_नकल(ethhdr->h_dest,
					&buf->data[माप(*ethhdr) + 0x12],
					ETH_ALEN);
		पूर्ण अन्यथा अणु
			eth_zero_addr(ethhdr->h_source);
			स_नकल(ethhdr->h_dest, dev->net->dev_addr, ETH_ALEN);

			/* Inbound IPv6 packets have an IPv4 ethertype (0x800)
			 * क्रम some reason.  Peek at the L3 header to check
			 * क्रम IPv6 packets, and set the ethertype to IPv6
			 * (0x86dd) so Linux can understand it.
			 */
			अगर ((buf->data[माप(*ethhdr)] & 0xf0) == 0x60)
				ethhdr->h_proto = htons(ETH_P_IPV6);
		पूर्ण

		अगर (count) अणु
			/* Not the last packet in this batch */
			clone = skb_clone(buf, GFP_ATOMIC);
			अगर (!clone)
				जाओ error;

			skb_trim(clone, packet_len);
			usbnet_skb_वापस(dev, clone);

			skb_pull(buf, (packet_len + 3) & ~3);
		पूर्ण अन्यथा अणु
			skb_trim(buf, packet_len);

			अगर (s->current_rx_buf) अणु
				usbnet_skb_वापस(dev, buf);
				s->current_rx_buf = शून्य;
				वापस 0;
			पूर्ण

			वापस 1;
		पूर्ण
	पूर्ण

error:
	अगर (s->current_rx_buf) अणु
		dev_kमुक्त_skb_any(s->current_rx_buf);
		s->current_rx_buf = शून्य;
	पूर्ण
	dev->net->stats.rx_errors++;
	वापस 0;
पूर्ण

अटल काष्ठा sk_buff *vl600_tx_fixup(काष्ठा usbnet *dev,
		काष्ठा sk_buff *skb, gfp_t flags)
अणु
	काष्ठा sk_buff *ret;
	काष्ठा vl600_frame_hdr *frame;
	काष्ठा vl600_pkt_hdr *packet;
	अटल uपूर्णांक32_t serial = 1;
	पूर्णांक orig_len = skb->len - माप(काष्ठा ethhdr);
	पूर्णांक full_len = (skb->len + माप(काष्ठा vl600_frame_hdr) + 3) & ~3;

	frame = (काष्ठा vl600_frame_hdr *) skb->data;
	अगर (skb->len > माप(*frame) && skb->len == le32_to_cpup(&frame->len))
		वापस skb; /* Alपढ़ोy encapsulated? */

	अगर (skb->len < माप(काष्ठा ethhdr))
		/* Drop, device can only deal with ethernet packets */
		वापस शून्य;

	अगर (!skb_cloned(skb)) अणु
		पूर्णांक headroom = skb_headroom(skb);
		पूर्णांक tailroom = skb_tailroom(skb);

		अगर (tailroom >= full_len - skb->len - माप(*frame) &&
				headroom >= माप(*frame))
			/* There's enough head and tail room */
			जाओ encapsulate;

		अगर (headroom + tailroom + skb->len >= full_len) अणु
			/* There's enough total room, just पढ़ोjust */
			skb->data = स_हटाओ(skb->head + माप(*frame),
					skb->data, skb->len);
			skb_set_tail_poपूर्णांकer(skb, skb->len);
			जाओ encapsulate;
		पूर्ण
	पूर्ण

	/* Alloc a new skb with the required size */
	ret = skb_copy_expand(skb, माप(काष्ठा vl600_frame_hdr), full_len -
			skb->len - माप(काष्ठा vl600_frame_hdr), flags);
	dev_kमुक्त_skb_any(skb);
	अगर (!ret)
		वापस ret;
	skb = ret;

encapsulate:
	/* Packet header is same size as ethernet packet header
	 * (माप(*packet) == माप(काष्ठा ethhdr)), additionally the
	 * h_proto field is in the same place so we just leave it alone and
	 * overग_लिखो the reमुख्यing fields.
	 */
	packet = (काष्ठा vl600_pkt_hdr *) skb->data;
	/* The VL600 wants IPv6 packets to have an IPv4 ethertype
	 * Since this modem only supports IPv4 and IPv6, just set all
	 * frames to 0x0800 (ETH_P_IP)
	 */
	packet->h_proto = htons(ETH_P_IP);
	स_रखो(&packet->dummy, 0, माप(packet->dummy));
	packet->len = cpu_to_le32(orig_len);

	frame = skb_push(skb, माप(*frame));
	स_रखो(frame, 0, माप(*frame));
	frame->len = cpu_to_le32(full_len);
	frame->serial = cpu_to_le32(serial++);
	frame->pkt_cnt = cpu_to_le32(1);

	अगर (skb->len < full_len) /* Pad */
		skb_put(skb, full_len - skb->len);

	वापस skb;
पूर्ण

अटल स्थिर काष्ठा driver_info	vl600_info = अणु
	.description	= "LG VL600 modem",
	.flags		= FLAG_RX_ASSEMBLE | FLAG_WWAN,
	.bind		= vl600_bind,
	.unbind		= vl600_unbind,
	.status		= usbnet_cdc_status,
	.rx_fixup	= vl600_rx_fixup,
	.tx_fixup	= vl600_tx_fixup,
पूर्ण;

अटल स्थिर काष्ठा usb_device_id products[] = अणु
	अणु
		USB_DEVICE_AND_INTERFACE_INFO(0x1004, 0x61aa, USB_CLASS_COMM,
				USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
		.driver_info	= (अचिन्हित दीर्घ) &vl600_info,
	पूर्ण,
	अणुपूर्ण,	/* End */
पूर्ण;
MODULE_DEVICE_TABLE(usb, products);

अटल काष्ठा usb_driver lg_vl600_driver = अणु
	.name		= "lg-vl600",
	.id_table	= products,
	.probe		= usbnet_probe,
	.disconnect	= usbnet_disconnect,
	.suspend	= usbnet_suspend,
	.resume		= usbnet_resume,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(lg_vl600_driver);

MODULE_AUTHOR("Anrzej Zaborowski");
MODULE_DESCRIPTION("LG-VL600 modem's ethernet link");
MODULE_LICENSE("GPL");
