<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Net1080 based USB host-to-host cables
 * Copyright (C) 2000-2005 by David Brownell
 */

// #घोषणा	DEBUG			// error path messages, extra info
// #घोषणा	VERBOSE			// more; success messages

#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mii.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/usbnet.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/unaligned.h>


/*
 * Netchip 1080 driver ... http://www.netchip.com
 * (Sept 2004:  End-of-lअगरe announcement has been sent.)
 * Used in (some) LapLink cables
 */

#घोषणा frame_errors	data[1]

/*
 * NetChip framing of ethernet packets, supporting additional error
 * checks क्रम links that may drop bulk packets from inside messages.
 * Odd USB length == always लघु पढ़ो क्रम last usb packet.
 *	- nc_header
 *	- Ethernet header (14 bytes)
 *	- payload
 *	- (optional padding byte, अगर needed so length becomes odd)
 *	- nc_trailer
 *
 * This framing is to be aव्योमed क्रम non-NetChip devices.
 */

काष्ठा nc_header अणु		// packed:
	__le16	hdr_len;		// माप nc_header (LE, all)
	__le16	packet_len;		// payload size (including ethhdr)
	__le16	packet_id;		// detects dropped packets
#घोषणा MIN_HEADER	6

	// all अन्यथा is optional, and must start with:
	// __le16	venकरोrId;	// from usb-अगर
	// __le16	productId;
पूर्ण __packed;

#घोषणा	PAD_BYTE	((अचिन्हित अक्षर)0xAC)

काष्ठा nc_trailer अणु
	__le16	packet_id;
पूर्ण __packed;

// packets may use FLAG_FRAMING_NC and optional pad
#घोषणा FRAMED_SIZE(mtu) (माप (काष्ठा nc_header) \
				+ माप (काष्ठा ethhdr) \
				+ (mtu) \
				+ 1 \
				+ माप (काष्ठा nc_trailer))

#घोषणा MIN_FRAMED	FRAMED_SIZE(0)

/* packets _could_ be up to 64KB... */
#घोषणा NC_MAX_PACKET	32767


/*
 * Zero means no समयout; अन्यथा, how दीर्घ a 64 byte bulk packet may be queued
 * beक्रमe the hardware drops it.  If that's करोne, the driver will need to
 * frame network packets to guard against the dropped USB packets.  The win32
 * driver sets this क्रम both sides of the link.
 */
#घोषणा	NC_READ_TTL_MS	((u8)255)	// ms

/*
 * We ignore most रेजिस्टरs and EEPROM contents.
 */
#घोषणा	REG_USBCTL	((u8)0x04)
#घोषणा REG_TTL		((u8)0x10)
#घोषणा REG_STATUS	((u8)0x11)

/*
 * Venकरोr specअगरic requests to पढ़ो/ग_लिखो data
 */
#घोषणा	REQUEST_REGISTER	((u8)0x10)
#घोषणा	REQUEST_EEPROM		((u8)0x11)

अटल पूर्णांक
nc_venकरोr_पढ़ो(काष्ठा usbnet *dev, u8 req, u8 regnum, u16 *retval_ptr)
अणु
	पूर्णांक status = usbnet_पढ़ो_cmd(dev, req,
				     USB_सूची_IN | USB_TYPE_VENDOR |
				     USB_RECIP_DEVICE,
				     0, regnum, retval_ptr,
				     माप *retval_ptr);
	अगर (status > 0)
		status = 0;
	अगर (!status)
		le16_to_cpus(retval_ptr);
	वापस status;
पूर्ण

अटल अंतरभूत पूर्णांक
nc_रेजिस्टर_पढ़ो(काष्ठा usbnet *dev, u8 regnum, u16 *retval_ptr)
अणु
	वापस nc_venकरोr_पढ़ो(dev, REQUEST_REGISTER, regnum, retval_ptr);
पूर्ण

अटल व्योम
nc_venकरोr_ग_लिखो(काष्ठा usbnet *dev, u8 req, u8 regnum, u16 value)
अणु
	usbnet_ग_लिखो_cmd(dev, req,
			 USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			 value, regnum, शून्य, 0);
पूर्ण

अटल अंतरभूत व्योम
nc_रेजिस्टर_ग_लिखो(काष्ठा usbnet *dev, u8 regnum, u16 value)
अणु
	nc_venकरोr_ग_लिखो(dev, REQUEST_REGISTER, regnum, value);
पूर्ण


#अगर 0
अटल व्योम nc_dump_रेजिस्टरs(काष्ठा usbnet *dev)
अणु
	u8	reg;
	u16	*vp = kदो_स्मृति(माप (u16));

	अगर (!vp)
		वापस;

	netdev_dbg(dev->net, "registers:\n");
	क्रम (reg = 0; reg < 0x20; reg++) अणु
		पूर्णांक retval;

		// पढ़ोing some रेजिस्टरs is trouble
		अगर (reg >= 0x08 && reg <= 0xf)
			जारी;
		अगर (reg >= 0x12 && reg <= 0x1e)
			जारी;

		retval = nc_रेजिस्टर_पढ़ो(dev, reg, vp);
		अगर (retval < 0)
			netdev_dbg(dev->net, "reg [0x%x] ==> error %d\n",
				   reg, retval);
		अन्यथा
			netdev_dbg(dev->net, "reg [0x%x] = 0x%x\n", reg, *vp);
	पूर्ण
	kमुक्त(vp);
पूर्ण
#पूर्ण_अगर


/*-------------------------------------------------------------------------*/

/*
 * Control रेजिस्टर
 */

#घोषणा	USBCTL_WRITABLE_MASK	0x1f0f
// bits 15-13 reserved, r/o
#घोषणा	USBCTL_ENABLE_LANG	(1 << 12)
#घोषणा	USBCTL_ENABLE_MFGR	(1 << 11)
#घोषणा	USBCTL_ENABLE_PROD	(1 << 10)
#घोषणा	USBCTL_ENABLE_SERIAL	(1 << 9)
#घोषणा	USBCTL_ENABLE_DEFAULTS	(1 << 8)
// bits 7-4 reserved, r/o
#घोषणा	USBCTL_FLUSH_OTHER	(1 << 3)
#घोषणा	USBCTL_FLUSH_THIS	(1 << 2)
#घोषणा	USBCTL_DISCONN_OTHER	(1 << 1)
#घोषणा	USBCTL_DISCONN_THIS	(1 << 0)

अटल अंतरभूत व्योम nc_dump_usbctl(काष्ठा usbnet *dev, u16 usbctl)
अणु
	netअगर_dbg(dev, link, dev->net,
		  "net1080 %s-%s usbctl 0x%x:%s%s%s%s%s; this%s%s; other%s%s; r/o 0x%x\n",
		  dev->udev->bus->bus_name, dev->udev->devpath,
		  usbctl,
		  (usbctl & USBCTL_ENABLE_LANG) ? " lang" : "",
		  (usbctl & USBCTL_ENABLE_MFGR) ? " mfgr" : "",
		  (usbctl & USBCTL_ENABLE_PROD) ? " prod" : "",
		  (usbctl & USBCTL_ENABLE_SERIAL) ? " serial" : "",
		  (usbctl & USBCTL_ENABLE_DEFAULTS) ? " defaults" : "",

		  (usbctl & USBCTL_FLUSH_THIS) ? " FLUSH" : "",
		  (usbctl & USBCTL_DISCONN_THIS) ? " DIS" : "",

		  (usbctl & USBCTL_FLUSH_OTHER) ? " FLUSH" : "",
		  (usbctl & USBCTL_DISCONN_OTHER) ? " DIS" : "",

		  usbctl & ~USBCTL_WRITABLE_MASK);
पूर्ण

/*-------------------------------------------------------------------------*/

/*
 * Status रेजिस्टर
 */

#घोषणा	STATUS_PORT_A		(1 << 15)

#घोषणा	STATUS_CONN_OTHER	(1 << 14)
#घोषणा	STATUS_SUSPEND_OTHER	(1 << 13)
#घोषणा	STATUS_MAILBOX_OTHER	(1 << 12)
#घोषणा	STATUS_PACKETS_OTHER(n)	(((n) >> 8) & 0x03)

#घोषणा	STATUS_CONN_THIS	(1 << 6)
#घोषणा	STATUS_SUSPEND_THIS	(1 << 5)
#घोषणा	STATUS_MAILBOX_THIS	(1 << 4)
#घोषणा	STATUS_PACKETS_THIS(n)	(((n) >> 0) & 0x03)

#घोषणा	STATUS_UNSPEC_MASK	0x0c8c
#घोषणा	STATUS_NOISE_MASK 	((u16)~(0x0303|STATUS_UNSPEC_MASK))


अटल अंतरभूत व्योम nc_dump_status(काष्ठा usbnet *dev, u16 status)
अणु
	netअगर_dbg(dev, link, dev->net,
		  "net1080 %s-%s status 0x%x: this (%c) PKT=%d%s%s%s; other PKT=%d%s%s%s; unspec 0x%x\n",
		  dev->udev->bus->bus_name, dev->udev->devpath,
		  status,

		  // XXX the packet counts करोn't seem right
		  // (1 at reset, not 0); maybe UNSPEC too

		  (status & STATUS_PORT_A) ? 'A' : 'B',
		  STATUS_PACKETS_THIS(status),
		  (status & STATUS_CONN_THIS) ? " CON" : "",
		  (status & STATUS_SUSPEND_THIS) ? " SUS" : "",
		  (status & STATUS_MAILBOX_THIS) ? " MBOX" : "",

		  STATUS_PACKETS_OTHER(status),
		  (status & STATUS_CONN_OTHER) ? " CON" : "",
		  (status & STATUS_SUSPEND_OTHER) ? " SUS" : "",
		  (status & STATUS_MAILBOX_OTHER) ? " MBOX" : "",

		  status & STATUS_UNSPEC_MASK);
पूर्ण

/*-------------------------------------------------------------------------*/

/*
 * TTL रेजिस्टर
 */

#घोषणा	TTL_OTHER(ttl)	(0x00ff & (ttl >> 8))
#घोषणा MK_TTL(this,other)	((u16)(((other)<<8)|(0x00ff&(this))))

/*-------------------------------------------------------------------------*/

अटल पूर्णांक net1080_reset(काष्ठा usbnet *dev)
अणु
	u16		usbctl, status, ttl;
	u16		vp;
	पूर्णांक		retval;

	// nc_dump_रेजिस्टरs(dev);

	अगर ((retval = nc_रेजिस्टर_पढ़ो(dev, REG_STATUS, &vp)) < 0) अणु
		netdev_dbg(dev->net, "can't read %s-%s status: %d\n",
			   dev->udev->bus->bus_name, dev->udev->devpath, retval);
		जाओ करोne;
	पूर्ण
	status = vp;
	nc_dump_status(dev, status);

	अगर ((retval = nc_रेजिस्टर_पढ़ो(dev, REG_USBCTL, &vp)) < 0) अणु
		netdev_dbg(dev->net, "can't read USBCTL, %d\n", retval);
		जाओ करोne;
	पूर्ण
	usbctl = vp;
	nc_dump_usbctl(dev, usbctl);

	nc_रेजिस्टर_ग_लिखो(dev, REG_USBCTL,
			USBCTL_FLUSH_THIS | USBCTL_FLUSH_OTHER);

	अगर ((retval = nc_रेजिस्टर_पढ़ो(dev, REG_TTL, &vp)) < 0) अणु
		netdev_dbg(dev->net, "can't read TTL, %d\n", retval);
		जाओ करोne;
	पूर्ण
	ttl = vp;

	nc_रेजिस्टर_ग_लिखो(dev, REG_TTL,
			MK_TTL(NC_READ_TTL_MS, TTL_OTHER(ttl)) );
	netdev_dbg(dev->net, "assigned TTL, %d ms\n", NC_READ_TTL_MS);

	netअगर_info(dev, link, dev->net, "port %c, peer %sconnected\n",
		   (status & STATUS_PORT_A) ? 'A' : 'B',
		   (status & STATUS_CONN_OTHER) ? "" : "dis");
	retval = 0;

करोne:
	वापस retval;
पूर्ण

अटल पूर्णांक net1080_check_connect(काष्ठा usbnet *dev)
अणु
	पूर्णांक			retval;
	u16			status;
	u16			vp;

	retval = nc_रेजिस्टर_पढ़ो(dev, REG_STATUS, &vp);
	status = vp;
	अगर (retval != 0) अणु
		netdev_dbg(dev->net, "net1080_check_conn read - %d\n", retval);
		वापस retval;
	पूर्ण
	अगर ((status & STATUS_CONN_OTHER) != STATUS_CONN_OTHER)
		वापस -ENOLINK;
	वापस 0;
पूर्ण

अटल व्योम nc_ensure_sync(काष्ठा usbnet *dev)
अणु
	अगर (++dev->frame_errors <= 5)
		वापस;

	अगर (usbnet_ग_लिखो_cmd_async(dev, REQUEST_REGISTER,
					USB_सूची_OUT | USB_TYPE_VENDOR |
					USB_RECIP_DEVICE,
					USBCTL_FLUSH_THIS |
					USBCTL_FLUSH_OTHER,
					REG_USBCTL, शून्य, 0))
		वापस;

	netअगर_dbg(dev, rx_err, dev->net,
		  "flush net1080; too many framing errors\n");
	dev->frame_errors = 0;
पूर्ण

अटल पूर्णांक net1080_rx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा nc_header	*header;
	काष्ठा nc_trailer	*trailer;
	u16			hdr_len, packet_len;

	/* This check is no दीर्घer करोne by usbnet */
	अगर (skb->len < dev->net->hard_header_len)
		वापस 0;

	अगर (!(skb->len & 0x01)) अणु
		netdev_dbg(dev->net, "rx framesize %d range %d..%d mtu %d\n",
			   skb->len, dev->net->hard_header_len, dev->hard_mtu,
			   dev->net->mtu);
		dev->net->stats.rx_frame_errors++;
		nc_ensure_sync(dev);
		वापस 0;
	पूर्ण

	header = (काष्ठा nc_header *) skb->data;
	hdr_len = le16_to_cpup(&header->hdr_len);
	packet_len = le16_to_cpup(&header->packet_len);
	अगर (FRAMED_SIZE(packet_len) > NC_MAX_PACKET) अणु
		dev->net->stats.rx_frame_errors++;
		netdev_dbg(dev->net, "packet too big, %d\n", packet_len);
		nc_ensure_sync(dev);
		वापस 0;
	पूर्ण अन्यथा अगर (hdr_len < MIN_HEADER) अणु
		dev->net->stats.rx_frame_errors++;
		netdev_dbg(dev->net, "header too short, %d\n", hdr_len);
		nc_ensure_sync(dev);
		वापस 0;
	पूर्ण अन्यथा अगर (hdr_len > MIN_HEADER) अणु
		// out of band data क्रम us?
		netdev_dbg(dev->net, "header OOB, %d bytes\n", hdr_len - MIN_HEADER);
		nc_ensure_sync(dev);
		// चयन (venकरोr/product ids) अणु ... पूर्ण
	पूर्ण
	skb_pull(skb, hdr_len);

	trailer = (काष्ठा nc_trailer *)
		(skb->data + skb->len - माप *trailer);
	skb_trim(skb, skb->len - माप *trailer);

	अगर ((packet_len & 0x01) == 0) अणु
		अगर (skb->data [packet_len] != PAD_BYTE) अणु
			dev->net->stats.rx_frame_errors++;
			netdev_dbg(dev->net, "bad pad\n");
			वापस 0;
		पूर्ण
		skb_trim(skb, skb->len - 1);
	पूर्ण
	अगर (skb->len != packet_len) अणु
		dev->net->stats.rx_frame_errors++;
		netdev_dbg(dev->net, "bad packet len %d (expected %d)\n",
			   skb->len, packet_len);
		nc_ensure_sync(dev);
		वापस 0;
	पूर्ण
	अगर (header->packet_id != get_unaligned(&trailer->packet_id)) अणु
		dev->net->stats.rx_fअगरo_errors++;
		netdev_dbg(dev->net, "(2+ dropped) rx packet_id mismatch 0x%x 0x%x\n",
			   le16_to_cpu(header->packet_id),
			   le16_to_cpu(trailer->packet_id));
		वापस 0;
	पूर्ण
#अगर 0
	netdev_dbg(dev->net, "frame <rx h %d p %d id %d\n", header->hdr_len,
		   header->packet_len, header->packet_id);
#पूर्ण_अगर
	dev->frame_errors = 0;
	वापस 1;
पूर्ण

अटल काष्ठा sk_buff *
net1080_tx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb, gfp_t flags)
अणु
	काष्ठा sk_buff		*skb2;
	काष्ठा nc_header	*header = शून्य;
	काष्ठा nc_trailer	*trailer = शून्य;
	पूर्णांक			padlen = माप (काष्ठा nc_trailer);
	पूर्णांक			len = skb->len;

	अगर (!((len + padlen + माप (काष्ठा nc_header)) & 0x01))
		padlen++;
	अगर (!skb_cloned(skb)) अणु
		पूर्णांक	headroom = skb_headroom(skb);
		पूर्णांक	tailroom = skb_tailroom(skb);

		अगर (padlen <= tailroom &&
		    माप(काष्ठा nc_header) <= headroom)
			/* There's enough head and tail room */
			जाओ encapsulate;

		अगर ((माप (काष्ठा nc_header) + padlen) <
				(headroom + tailroom)) अणु
			/* There's enough total room, so just पढ़ोjust */
			skb->data = स_हटाओ(skb->head
						+ माप (काष्ठा nc_header),
					    skb->data, skb->len);
			skb_set_tail_poपूर्णांकer(skb, len);
			जाओ encapsulate;
		पूर्ण
	पूर्ण

	/* Create a new skb to use with the correct size */
	skb2 = skb_copy_expand(skb,
				माप (काष्ठा nc_header),
				padlen,
				flags);
	dev_kमुक्त_skb_any(skb);
	अगर (!skb2)
		वापस skb2;
	skb = skb2;

encapsulate:
	/* header first */
	header = skb_push(skb, माप *header);
	header->hdr_len = cpu_to_le16(माप (*header));
	header->packet_len = cpu_to_le16(len);
	header->packet_id = cpu_to_le16((u16)dev->xid++);

	/* maybe pad; then trailer */
	अगर (!((skb->len + माप *trailer) & 0x01))
		skb_put_u8(skb, PAD_BYTE);
	trailer = skb_put(skb, माप *trailer);
	put_unaligned(header->packet_id, &trailer->packet_id);
#अगर 0
	netdev_dbg(dev->net, "frame >tx h %d p %d id %d\n",
		   header->hdr_len, header->packet_len,
		   header->packet_id);
#पूर्ण_अगर
	वापस skb;
पूर्ण

अटल पूर्णांक net1080_bind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	अचिन्हित	extra = माप (काष्ठा nc_header)
				+ 1
				+ माप (काष्ठा nc_trailer);

	dev->net->hard_header_len += extra;
	dev->rx_urb_size = dev->net->hard_header_len + dev->net->mtu;
	dev->hard_mtu = NC_MAX_PACKET;
	वापस usbnet_get_endpoपूर्णांकs (dev, पूर्णांकf);
पूर्ण

अटल स्थिर काष्ठा driver_info	net1080_info = अणु
	.description =	"NetChip TurboCONNECT",
	.flags =	FLAG_POINTTOPOINT | FLAG_FRAMING_NC,
	.bind =		net1080_bind,
	.reset =	net1080_reset,
	.check_connect = net1080_check_connect,
	.rx_fixup =	net1080_rx_fixup,
	.tx_fixup =	net1080_tx_fixup,
पूर्ण;

अटल स्थिर काष्ठा usb_device_id	products [] = अणु
अणु
	USB_DEVICE(0x0525, 0x1080),	// NetChip ref design
	.driver_info =	(अचिन्हित दीर्घ) &net1080_info,
पूर्ण, अणु
	USB_DEVICE(0x06D0, 0x0622),	// Laplink Gold
	.driver_info =	(अचिन्हित दीर्घ) &net1080_info,
पूर्ण,
	अणु पूर्ण,		// END
पूर्ण;
MODULE_DEVICE_TABLE(usb, products);

अटल काष्ठा usb_driver net1080_driver = अणु
	.name =		"net1080",
	.id_table =	products,
	.probe =	usbnet_probe,
	.disconnect =	usbnet_disconnect,
	.suspend =	usbnet_suspend,
	.resume =	usbnet_resume,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(net1080_driver);

MODULE_AUTHOR("David Brownell");
MODULE_DESCRIPTION("NetChip 1080 based USB Host-to-Host Links");
MODULE_LICENSE("GPL");
