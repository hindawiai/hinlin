<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * USB CDC EEM network पूर्णांकerface driver
 * Copyright (C) 2009 Oberthur Technologies
 * by Omar Laazimani, Olivier Condemine
 */

#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/ethtool.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mii.h>
#समावेश <linux/usb.h>
#समावेश <linux/crc32.h>
#समावेश <linux/usb/cdc.h>
#समावेश <linux/usb/usbnet.h>
#समावेश <linux/gfp.h>
#समावेश <linux/अगर_vlan.h>


/*
 * This driver is an implementation of the CDC "Ethernet Emulation
 * Model" (EEM) specअगरication, which encapsulates Ethernet frames
 * क्रम transport over USB using a simpler USB device model than the
 * previous CDC "Ethernet Control Model" (ECM, or "CDC Ethernet").
 *
 * For details, see https://usb.org/sites/शेष/files/CDC_EEM10.pdf
 *
 * This version has been tested with GIGAntIC WuaoW SIM Smart Card on 2.6.24,
 * 2.6.27 and 2.6.30rc2 kernel.
 * It has also been validated on Openmoko Om 2008.12 (based on 2.6.24 kernel).
 * build on 23-April-2009
 */

#घोषणा EEM_HEAD	2		/* 2 byte header */

/*-------------------------------------------------------------------------*/

अटल व्योम eem_linkcmd_complete(काष्ठा urb *urb)
अणु
	dev_kमुक्त_skb(urb->context);
	usb_मुक्त_urb(urb);
पूर्ण

अटल व्योम eem_linkcmd(काष्ठा usbnet *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा urb		*urb;
	पूर्णांक			status;

	urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!urb)
		जाओ fail;

	usb_fill_bulk_urb(urb, dev->udev, dev->out,
			skb->data, skb->len, eem_linkcmd_complete, skb);

	status = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (status) अणु
		usb_मुक्त_urb(urb);
fail:
		dev_kमुक्त_skb(skb);
		netdev_warn(dev->net, "link cmd failure\n");
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक eem_bind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	पूर्णांक status = 0;

	status = usbnet_get_endpoपूर्णांकs(dev, पूर्णांकf);
	अगर (status < 0)
		वापस status;

	/* no jumbogram (16K) support क्रम now */

	dev->net->hard_header_len += EEM_HEAD + ETH_FCS_LEN + VLAN_HLEN;
	dev->hard_mtu = dev->net->mtu + dev->net->hard_header_len;

	वापस 0;
पूर्ण

/*
 * EEM permits packing multiple Ethernet frames पूर्णांकo USB transfers
 * (a "bundle"), but क्रम TX we करोn't try to करो that.
 */
अटल काष्ठा sk_buff *eem_tx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb,
				       gfp_t flags)
अणु
	काष्ठा sk_buff	*skb2 = शून्य;
	u16		len = skb->len;
	u32		crc = 0;
	पूर्णांक		padlen = 0;

	/* When ((len + EEM_HEAD + ETH_FCS_LEN) % dev->maxpacket) is
	 * zero, stick two bytes of zero length EEM packet on the end.
	 * Else the framework would add invalid single byte padding,
	 * since it can't know whether ZLPs will be handled right by
	 * all the relevant hardware and software.
	 */
	अगर (!((len + EEM_HEAD + ETH_FCS_LEN) % dev->maxpacket))
		padlen += 2;

	अगर (!skb_cloned(skb)) अणु
		पूर्णांक	headroom = skb_headroom(skb);
		पूर्णांक	tailroom = skb_tailroom(skb);

		अगर ((tailroom >= ETH_FCS_LEN + padlen) &&
		    (headroom >= EEM_HEAD))
			जाओ करोne;

		अगर ((headroom + tailroom)
				> (EEM_HEAD + ETH_FCS_LEN + padlen)) अणु
			skb->data = स_हटाओ(skb->head +
					EEM_HEAD,
					skb->data,
					skb->len);
			skb_set_tail_poपूर्णांकer(skb, len);
			जाओ करोne;
		पूर्ण
	पूर्ण

	skb2 = skb_copy_expand(skb, EEM_HEAD, ETH_FCS_LEN + padlen, flags);
	dev_kमुक्त_skb_any(skb);
	अगर (!skb2)
		वापस शून्य;

	skb = skb2;

करोne:
	/* we करोn't use the "no Ethernet CRC" option */
	crc = crc32_le(~0, skb->data, skb->len);
	crc = ~crc;

	put_unaligned_le32(crc, skb_put(skb, 4));

	/* EEM packet header क्रमmat:
	 * b0..13:	length of ethernet frame
	 * b14:		bmCRC (1 == valid Ethernet CRC)
	 * b15:		bmType (0 == data)
	 */
	len = skb->len;
	put_unaligned_le16(BIT(14) | len, skb_push(skb, 2));

	/* Bundle a zero length EEM packet अगर needed */
	अगर (padlen)
		put_unaligned_le16(0, skb_put(skb, 2));

	वापस skb;
पूर्ण

अटल पूर्णांक eem_rx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb)
अणु
	/*
	 * Our task here is to strip off framing, leaving skb with one
	 * data frame क्रम the usbnet framework code to process.  But we
	 * may have received multiple EEM payloads, or command payloads.
	 * So we must process _everything_ as अगर it's a header, except
	 * maybe the last data payload
	 *
	 * REVISIT the framework needs updating so that when we consume
	 * all payloads (the last or only message was a command, or a
	 * zero length EEM packet) that is not accounted as an rx_error.
	 */
	करो अणु
		काष्ठा sk_buff	*skb2 = शून्य;
		u16		header;
		u16		len = 0;

		/* incomplete EEM header? */
		अगर (skb->len < EEM_HEAD)
			वापस 0;

		/*
		 * EEM packet header क्रमmat:
		 * b0..14:	EEM type dependent (Data or Command)
		 * b15:		bmType
		 */
		header = get_unaligned_le16(skb->data);
		skb_pull(skb, EEM_HEAD);

		/*
		 * The bmType bit helps to denote when EEM
		 * packet is data or command :
		 *	bmType = 0	: EEM data payload
		 *	bmType = 1	: EEM (link) command
		 */
		अगर (header & BIT(15)) अणु
			u16	bmEEMCmd;

			/*
			 * EEM (link) command packet:
			 * b0..10:	bmEEMCmdParam
			 * b11..13:	bmEEMCmd
			 * b14:		bmReserved (must be 0)
			 * b15:		1 (EEM command)
			 */
			अगर (header & BIT(14)) अणु
				netdev_dbg(dev->net, "reserved command %04x\n",
					   header);
				जारी;
			पूर्ण

			bmEEMCmd = (header >> 11) & 0x7;
			चयन (bmEEMCmd) अणु

			/* Responding to echo requests is mandatory. */
			हाल 0:		/* Echo command */
				len = header & 0x7FF;

				/* bogus command? */
				अगर (skb->len < len)
					वापस 0;

				skb2 = skb_clone(skb, GFP_ATOMIC);
				अगर (unlikely(!skb2))
					जाओ next;
				skb_trim(skb2, len);
				put_unaligned_le16(BIT(15) | (1 << 11) | len,
						skb_push(skb2, 2));
				eem_linkcmd(dev, skb2);
				अवरोध;

			/*
			 * Host may choose to ignore hपूर्णांकs.
			 *  - suspend: peripheral पढ़ोy to suspend
			 *  - response: suggest N millisec polling
			 *  - response complete: suggest N sec polling
			 *
			 * Suspend is reported and maybe heeded.
			 */
			हाल 2:		/* Suspend hपूर्णांक */
				usbnet_device_suggests_idle(dev);
				जारी;
			हाल 3:		/* Response hपूर्णांक */
			हाल 4:		/* Response complete hपूर्णांक */
				जारी;

			/*
			 * Hosts should never receive host-to-peripheral
			 * or reserved command codes; or responses to an
			 * echo command we didn't send.
			 */
			हाल 1:		/* Echo response */
			हाल 5:		/* Tickle */
			शेष:	/* reserved */
				netdev_warn(dev->net,
					    "unexpected link command %d\n",
					    bmEEMCmd);
				जारी;
			पूर्ण

		पूर्ण अन्यथा अणु
			u32	crc, crc2;
			पूर्णांक	is_last;

			/* zero length EEM packet? */
			अगर (header == 0)
				जारी;

			/*
			 * EEM data packet header :
			 * b0..13:	length of ethernet frame
			 * b14:		bmCRC
			 * b15:		0 (EEM data)
			 */
			len = header & 0x3FFF;

			/* bogus EEM payload? */
			अगर (skb->len < len)
				वापस 0;

			/* bogus ethernet frame? */
			अगर (len < (ETH_HLEN + ETH_FCS_LEN))
				जाओ next;

			/*
			 * Treat the last payload dअगरferently: framework
			 * code expects our "fixup" to have stripped off
			 * headers, so "skb" is a data packet (or error).
			 * Else अगर it's not the last payload, keep "skb"
			 * क्रम further processing.
			 */
			is_last = (len == skb->len);
			अगर (is_last)
				skb2 = skb;
			अन्यथा अणु
				skb2 = skb_clone(skb, GFP_ATOMIC);
				अगर (unlikely(!skb2))
					वापस 0;
			पूर्ण

			/*
			 * The bmCRC helps to denote when the CRC field in
			 * the Ethernet frame contains a calculated CRC:
			 *	bmCRC = 1	: CRC is calculated
			 *	bmCRC = 0	: CRC = 0xDEADBEEF
			 */
			अगर (header & BIT(14)) अणु
				crc = get_unaligned_le32(skb2->data
						+ len - ETH_FCS_LEN);
				crc2 = ~crc32_le(~0, skb2->data, skb2->len
						- ETH_FCS_LEN);
			पूर्ण अन्यथा अणु
				crc = get_unaligned_be32(skb2->data
						+ len - ETH_FCS_LEN);
				crc2 = 0xdeadbeef;
			पूर्ण
			skb_trim(skb2, len - ETH_FCS_LEN);

			अगर (is_last)
				वापस crc == crc2;

			अगर (unlikely(crc != crc2)) अणु
				dev->net->stats.rx_errors++;
				dev_kमुक्त_skb_any(skb2);
			पूर्ण अन्यथा
				usbnet_skb_वापस(dev, skb2);
		पूर्ण

next:
		skb_pull(skb, len);
	पूर्ण जबतक (skb->len);

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा driver_info eem_info = अणु
	.description =	"CDC EEM Device",
	.flags =	FLAG_ETHER | FLAG_POINTTOPOINT,
	.bind =		eem_bind,
	.rx_fixup =	eem_rx_fixup,
	.tx_fixup =	eem_tx_fixup,
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल स्थिर काष्ठा usb_device_id products[] = अणु
अणु
	USB_INTERFACE_INFO(USB_CLASS_COMM, USB_CDC_SUBCLASS_EEM,
			USB_CDC_PROTO_EEM),
	.driver_info = (अचिन्हित दीर्घ) &eem_info,
पूर्ण,
अणु
	/* EMPTY == end of list */
पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(usb, products);

अटल काष्ठा usb_driver eem_driver = अणु
	.name =		"cdc_eem",
	.id_table =	products,
	.probe =	usbnet_probe,
	.disconnect =	usbnet_disconnect,
	.suspend =	usbnet_suspend,
	.resume =	usbnet_resume,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(eem_driver);

MODULE_AUTHOR("Omar Laazimani <omar.oberthur@gmail.com>");
MODULE_DESCRIPTION("USB CDC EEM");
MODULE_LICENSE("GPL");
