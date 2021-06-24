<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * USB-to-WWAN Driver क्रम Sierra Wireless modems
 *
 * Copyright (C) 2008, 2009, 2010 Paxton Smith, Matthew Safar, Rory Filer
 *                          <linux@sierrawireless.com>
 *
 * Portions of this based on the cdc_ether driver by David Brownell (2003-2005)
 * and Ole Andre Vadla Ravnas (ActiveSync) (2006).
 *
 * IMPORTANT DISCLAIMER: This driver is not commercially supported by
 * Sierra Wireless. Use at your own risk.
 */

#घोषणा DRIVER_VERSION "v.2.0"
#घोषणा DRIVER_AUTHOR "Paxton Smith, Matthew Safar, Rory Filer"
#घोषणा DRIVER_DESC "USB-to-WWAN Driver for Sierra Wireless modems"
अटल स्थिर अक्षर driver_name[] = "sierra_net";

/* अगर defined debug messages enabled */
/*#घोषणा	DEBUG*/

#समावेश <linux/module.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>
#समावेश <linux/sched.h>
#समावेश <linux/समयr.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/cdc.h>
#समावेश <net/ip.h>
#समावेश <net/udp.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/usb/usbnet.h>

#घोषणा SWI_USB_REQUEST_GET_FW_ATTR	0x06
#घोषणा SWI_GET_FW_ATTR_MASK		0x08

/* atomic counter partially included in MAC address to make sure 2 devices
 * करो not end up with the same MAC - concept अवरोधs in हाल of > 255 अगरaces
 */
अटल	atomic_t अगरace_counter = ATOMIC_INIT(0);

/*
 * SYNC Timer Delay definition used to set the expiry समय
 */
#घोषणा SIERRA_NET_SYNCDELAY (2*HZ)

/* Max. MTU supported. The modem buffers are limited to 1500 */
#घोषणा SIERRA_NET_MAX_SUPPORTED_MTU	1500

/* The SIERRA_NET_USBCTL_BUF_LEN defines a buffer size allocated क्रम control
 * message reception ... and thus the max. received packet.
 * (May be the cause क्रम parse_hip वापसing -EINVAL)
 */
#घोषणा SIERRA_NET_USBCTL_BUF_LEN	1024

/* Overriding the शेष usbnet rx_urb_size */
#घोषणा SIERRA_NET_RX_URB_SIZE		(8 * 1024)

/* Private data काष्ठाure */
काष्ठा sierra_net_data अणु

	u16 link_up;		/* air link up or करोwn */
	u8 tx_hdr_ढाँचा[4];	/* part of HIP hdr क्रम tx'd packets */

	u8 sync_msg[4];		/* SYNC message */
	u8 shdwn_msg[4];	/* Shutकरोwn message */

	/* Backpoपूर्णांकer to the container */
	काष्ठा usbnet *usbnet;

	u8 अगरnum;	/* पूर्णांकerface number */

/* Bit masks, must be a घातer of 2 */
#घोषणा SIERRA_NET_EVENT_RESP_AVAIL    0x01
#घोषणा SIERRA_NET_TIMER_EXPIRY        0x02
	अचिन्हित दीर्घ kevent_flags;
	काष्ठा work_काष्ठा sierra_net_kevent;
	काष्ठा समयr_list sync_समयr; /* For retrying SYNC sequence */
पूर्ण;

काष्ठा param अणु
	पूर्णांक is_present;
	जोड़ अणु
		व्योम  *ptr;
		u32    dword;
		u16    word;
		u8     byte;
	पूर्ण;
पूर्ण;

/* HIP message type */
#घोषणा SIERRA_NET_HIP_EXTENDEDID	0x7F
#घोषणा SIERRA_NET_HIP_HSYNC_ID		0x60	/* Modem -> host */
#घोषणा SIERRA_NET_HIP_RESTART_ID	0x62	/* Modem -> host */
#घोषणा SIERRA_NET_HIP_MSYNC_ID		0x20	/* Host -> modem */
#घोषणा SIERRA_NET_HIP_SHUTD_ID		0x26	/* Host -> modem */

#घोषणा SIERRA_NET_HIP_EXT_IP_IN_ID   0x0202
#घोषणा SIERRA_NET_HIP_EXT_IP_OUT_ID  0x0002

/* 3G UMTS Link Sense Indication definitions */
#घोषणा SIERRA_NET_HIP_LSI_UMTSID	0x78

/* Reverse Channel Grant Indication HIP message */
#घोषणा SIERRA_NET_HIP_RCGI		0x64

/* LSI Protocol types */
#घोषणा SIERRA_NET_PROTOCOL_UMTS      0x01
#घोषणा SIERRA_NET_PROTOCOL_UMTS_DS   0x04
/* LSI Coverage */
#घोषणा SIERRA_NET_COVERAGE_NONE      0x00
#घोषणा SIERRA_NET_COVERAGE_NOPACKET  0x01

/* LSI Session */
#घोषणा SIERRA_NET_SESSION_IDLE       0x00
/* LSI Link types */
#घोषणा SIERRA_NET_AS_LINK_TYPE_IPV4  0x00
#घोषणा SIERRA_NET_AS_LINK_TYPE_IPV6  0x02

काष्ठा lsi_umts अणु
	u8 protocol;
	u8 unused1;
	__be16 length;
	/* eventually use a जोड़ क्रम the rest - assume umts क्रम now */
	u8 coverage;
	u8 network_len; /* network name len */
	u8 network[40]; /* network name (UCS2, bigendian) */
	u8 session_state;
	u8 unused3[33];
पूर्ण __packed;

काष्ठा lsi_umts_single अणु
	काष्ठा lsi_umts lsi;
	u8 link_type;
	u8 pdp_addr_len; /* NW-supplied PDP address len */
	u8 pdp_addr[16]; /* NW-supplied PDP address (bigendian)) */
	u8 unused4[23];
	u8 dns1_addr_len; /* NW-supplied 1st DNS address len (bigendian) */
	u8 dns1_addr[16]; /* NW-supplied 1st DNS address */
	u8 dns2_addr_len; /* NW-supplied 2nd DNS address len */
	u8 dns2_addr[16]; /* NW-supplied 2nd DNS address (bigendian)*/
	u8 wins1_addr_len; /* NW-supplied 1st Wins address len */
	u8 wins1_addr[16]; /* NW-supplied 1st Wins address (bigendian)*/
	u8 wins2_addr_len; /* NW-supplied 2nd Wins address len */
	u8 wins2_addr[16]; /* NW-supplied 2nd Wins address (bigendian) */
	u8 unused5[4];
	u8 gw_addr_len; /* NW-supplied GW address len */
	u8 gw_addr[16]; /* NW-supplied GW address (bigendian) */
	u8 reserved[8];
पूर्ण __packed;

काष्ठा lsi_umts_dual अणु
	काष्ठा lsi_umts lsi;
	u8 pdp_addr4_len; /* NW-supplied PDP IPv4 address len */
	u8 pdp_addr4[4];  /* NW-supplied PDP IPv4 address (bigendian)) */
	u8 pdp_addr6_len; /* NW-supplied PDP IPv6 address len */
	u8 pdp_addr6[16]; /* NW-supplied PDP IPv6 address (bigendian)) */
	u8 unused4[23];
	u8 dns1_addr4_len; /* NW-supplied 1st DNS v4 address len (bigendian) */
	u8 dns1_addr4[4];  /* NW-supplied 1st DNS v4 address */
	u8 dns1_addr6_len; /* NW-supplied 1st DNS v6 address len */
	u8 dns1_addr6[16]; /* NW-supplied 1st DNS v6 address (bigendian)*/
	u8 dns2_addr4_len; /* NW-supplied 2nd DNS v4 address len (bigendian) */
	u8 dns2_addr4[4];  /* NW-supplied 2nd DNS v4 address */
	u8 dns2_addr6_len; /* NW-supplied 2nd DNS v6 address len */
	u8 dns2_addr6[16]; /* NW-supplied 2nd DNS v6 address (bigendian)*/
	u8 unused5[68];
पूर्ण __packed;

#घोषणा SIERRA_NET_LSI_COMMON_LEN      4
#घोषणा SIERRA_NET_LSI_UMTS_LEN        (माप(काष्ठा lsi_umts_single))
#घोषणा SIERRA_NET_LSI_UMTS_STATUS_LEN \
	(SIERRA_NET_LSI_UMTS_LEN - SIERRA_NET_LSI_COMMON_LEN)
#घोषणा SIERRA_NET_LSI_UMTS_DS_LEN     (माप(काष्ठा lsi_umts_dual))
#घोषणा SIERRA_NET_LSI_UMTS_DS_STATUS_LEN \
	(SIERRA_NET_LSI_UMTS_DS_LEN - SIERRA_NET_LSI_COMMON_LEN)

/* Our own net device operations काष्ठाure */
अटल स्थिर काष्ठा net_device_ops sierra_net_device_ops = अणु
	.nकरो_खोलो               = usbnet_खोलो,
	.nकरो_stop               = usbnet_stop,
	.nकरो_start_xmit         = usbnet_start_xmit,
	.nकरो_tx_समयout         = usbnet_tx_समयout,
	.nकरो_change_mtu         = usbnet_change_mtu,
	.nकरो_get_stats64        = dev_get_tstats64,
	.nकरो_set_mac_address    = eth_mac_addr,
	.nकरो_validate_addr      = eth_validate_addr,
पूर्ण;

/* get निजी data associated with passed in usbnet device */
अटल अंतरभूत काष्ठा sierra_net_data *sierra_net_get_निजी(काष्ठा usbnet *dev)
अणु
	वापस (काष्ठा sierra_net_data *)dev->data[0];
पूर्ण

/* set निजी data associated with passed in usbnet device */
अटल अंतरभूत व्योम sierra_net_set_निजी(काष्ठा usbnet *dev,
			काष्ठा sierra_net_data *priv)
अणु
	dev->data[0] = (अचिन्हित दीर्घ)priv;
पूर्ण

/* is packet IPv4/IPv6 */
अटल अंतरभूत पूर्णांक is_ip(काष्ठा sk_buff *skb)
अणु
	वापस skb->protocol == cpu_to_be16(ETH_P_IP) ||
	       skb->protocol == cpu_to_be16(ETH_P_IPV6);
पूर्ण

/*
 * check passed in packet and make sure that:
 *  - it is linear (no scatter/gather)
 *  - it is ethernet (mac_header properly set)
 */
अटल पूर्णांक check_ethip_packet(काष्ठा sk_buff *skb, काष्ठा usbnet *dev)
अणु
	skb_reset_mac_header(skb); /* ethernet header */

	अगर (skb_is_nonlinear(skb)) अणु
		netdev_err(dev->net, "Non linear buffer-dropping\n");
		वापस 0;
	पूर्ण

	अगर (!pskb_may_pull(skb, ETH_HLEN))
		वापस 0;
	skb->protocol = eth_hdr(skb)->h_proto;

	वापस 1;
पूर्ण

अटल स्थिर u8 *save16bit(काष्ठा param *p, स्थिर u8 *datap)
अणु
	p->is_present = 1;
	p->word = get_unaligned_be16(datap);
	वापस datap + माप(p->word);
पूर्ण

अटल स्थिर u8 *save8bit(काष्ठा param *p, स्थिर u8 *datap)
अणु
	p->is_present = 1;
	p->byte = *datap;
	वापस datap + माप(p->byte);
पूर्ण

/*----------------------------------------------------------------------------*
 *                              BEGIN HIP                                     *
 *----------------------------------------------------------------------------*/
/* HIP header */
#घोषणा SIERRA_NET_HIP_HDR_LEN 4
/* Extended HIP header */
#घोषणा SIERRA_NET_HIP_EXT_HDR_LEN 6

काष्ठा hip_hdr अणु
	पूर्णांक    hdrlen;
	काष्ठा param payload_len;
	काष्ठा param msgid;
	काष्ठा param msgspecअगरic;
	काष्ठा param exपंचांगsgid;
पूर्ण;

अटल पूर्णांक parse_hip(स्थिर u8 *buf, स्थिर u32 buflen, काष्ठा hip_hdr *hh)
अणु
	स्थिर u8 *curp = buf;
	पूर्णांक    padded;

	अगर (buflen < SIERRA_NET_HIP_HDR_LEN)
		वापस -EPROTO;

	curp = save16bit(&hh->payload_len, curp);
	curp = save8bit(&hh->msgid, curp);
	curp = save8bit(&hh->msgspecअगरic, curp);

	padded = hh->msgid.byte & 0x80;
	hh->msgid.byte &= 0x7F;			/* 7 bits */

	hh->exपंचांगsgid.is_present = (hh->msgid.byte == SIERRA_NET_HIP_EXTENDEDID);
	अगर (hh->exपंचांगsgid.is_present) अणु
		अगर (buflen < SIERRA_NET_HIP_EXT_HDR_LEN)
			वापस -EPROTO;

		hh->payload_len.word &= 0x3FFF; /* 14 bits */

		curp = save16bit(&hh->exपंचांगsgid, curp);
		hh->exपंचांगsgid.word &= 0x03FF;	/* 10 bits */

		hh->hdrlen = SIERRA_NET_HIP_EXT_HDR_LEN;
	पूर्ण अन्यथा अणु
		hh->payload_len.word &= 0x07FF;	/* 11 bits */
		hh->hdrlen = SIERRA_NET_HIP_HDR_LEN;
	पूर्ण

	अगर (padded) अणु
		hh->hdrlen++;
		hh->payload_len.word--;
	पूर्ण

	/* अगर real packet लघुer than the claimed length */
	अगर (buflen < (hh->hdrlen + hh->payload_len.word))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम build_hip(u8 *buf, स्थिर u16 payloadlen,
		काष्ठा sierra_net_data *priv)
अणु
	/* the following करोesn't have the full functionality. We
	 * currently build only one kind of header, so it is faster this way
	 */
	put_unaligned_be16(payloadlen, buf);
	स_नकल(buf+2, priv->tx_hdr_ढाँचा, माप(priv->tx_hdr_ढाँचा));
पूर्ण
/*----------------------------------------------------------------------------*
 *                              END HIP                                       *
 *----------------------------------------------------------------------------*/

अटल पूर्णांक sierra_net_send_cmd(काष्ठा usbnet *dev,
		u8 *cmd, पूर्णांक cmdlen, स्थिर अक्षर * cmd_name)
अणु
	काष्ठा sierra_net_data *priv = sierra_net_get_निजी(dev);
	पूर्णांक  status;

	status = usbnet_ग_लिखो_cmd(dev, USB_CDC_SEND_ENCAPSULATED_COMMAND,
				  USB_सूची_OUT|USB_TYPE_CLASS|USB_RECIP_INTERFACE,
				  0, priv->अगरnum, cmd, cmdlen);

	अगर (status != cmdlen && status != -ENODEV)
		netdev_err(dev->net, "Submit %s failed %d\n", cmd_name, status);

	वापस status;
पूर्ण

अटल पूर्णांक sierra_net_send_sync(काष्ठा usbnet *dev)
अणु
	पूर्णांक  status;
	काष्ठा sierra_net_data *priv = sierra_net_get_निजी(dev);

	dev_dbg(&dev->udev->dev, "%s", __func__);

	status = sierra_net_send_cmd(dev, priv->sync_msg,
			माप(priv->sync_msg), "SYNC");

	वापस status;
पूर्ण

अटल व्योम sierra_net_set_ctx_index(काष्ठा sierra_net_data *priv, u8 ctx_ix)
अणु
	dev_dbg(&(priv->usbnet->udev->dev), "%s %d", __func__, ctx_ix);
	priv->tx_hdr_ढाँचा[0] = 0x3F;
	priv->tx_hdr_ढाँचा[1] = ctx_ix;
	*((__be16 *)&priv->tx_hdr_ढाँचा[2]) =
		cpu_to_be16(SIERRA_NET_HIP_EXT_IP_OUT_ID);
पूर्ण

अटल पूर्णांक sierra_net_parse_lsi(काष्ठा usbnet *dev, अक्षर *data, पूर्णांक datalen)
अणु
	काष्ठा lsi_umts *lsi = (काष्ठा lsi_umts *)data;
	u32 expected_length;

	अगर (datalen < माप(काष्ठा lsi_umts_single)) अणु
		netdev_err(dev->net, "%s: Data length %d, exp >= %zu\n",
			   __func__, datalen, माप(काष्ठा lsi_umts_single));
		वापस -1;
	पूर्ण

	/* Validate the session state */
	अगर (lsi->session_state == SIERRA_NET_SESSION_IDLE) अणु
		netdev_err(dev->net, "Session idle, 0x%02x\n",
			   lsi->session_state);
		वापस 0;
	पूर्ण

	/* Validate the protocol  - only support UMTS क्रम now */
	अगर (lsi->protocol == SIERRA_NET_PROTOCOL_UMTS) अणु
		काष्ठा lsi_umts_single *single = (काष्ठा lsi_umts_single *)lsi;

		/* Validate the link type */
		अगर (single->link_type != SIERRA_NET_AS_LINK_TYPE_IPV4 &&
		    single->link_type != SIERRA_NET_AS_LINK_TYPE_IPV6) अणु
			netdev_err(dev->net, "Link type unsupported: 0x%02x\n",
				   single->link_type);
			वापस -1;
		पूर्ण
		expected_length = SIERRA_NET_LSI_UMTS_STATUS_LEN;
	पूर्ण अन्यथा अगर (lsi->protocol == SIERRA_NET_PROTOCOL_UMTS_DS) अणु
		expected_length = SIERRA_NET_LSI_UMTS_DS_STATUS_LEN;
	पूर्ण अन्यथा अणु
		netdev_err(dev->net, "Protocol unsupported, 0x%02x\n",
			   lsi->protocol);
		वापस -1;
	पूर्ण

	अगर (be16_to_cpu(lsi->length) != expected_length) अणु
		netdev_err(dev->net, "%s: LSI_UMTS_STATUS_LEN %d, exp %u\n",
			   __func__, be16_to_cpu(lsi->length), expected_length);
		वापस -1;
	पूर्ण

	/* Validate the coverage */
	अगर (lsi->coverage == SIERRA_NET_COVERAGE_NONE ||
	    lsi->coverage == SIERRA_NET_COVERAGE_NOPACKET) अणु
		netdev_err(dev->net, "No coverage, 0x%02x\n", lsi->coverage);
		वापस 0;
	पूर्ण

	/* Set link_sense true */
	वापस 1;
पूर्ण

अटल व्योम sierra_net_handle_lsi(काष्ठा usbnet *dev, अक्षर *data,
		काष्ठा hip_hdr	*hh)
अणु
	काष्ठा sierra_net_data *priv = sierra_net_get_निजी(dev);
	पूर्णांक link_up;

	link_up = sierra_net_parse_lsi(dev, data + hh->hdrlen,
					hh->payload_len.word);
	अगर (link_up < 0) अणु
		netdev_err(dev->net, "Invalid LSI\n");
		वापस;
	पूर्ण
	अगर (link_up) अणु
		sierra_net_set_ctx_index(priv, hh->msgspecअगरic.byte);
		priv->link_up = 1;
	पूर्ण अन्यथा अणु
		priv->link_up = 0;
	पूर्ण
	usbnet_link_change(dev, link_up, 0);
पूर्ण

अटल व्योम sierra_net_करोsync(काष्ठा usbnet *dev)
अणु
	पूर्णांक status;
	काष्ठा sierra_net_data *priv = sierra_net_get_निजी(dev);

	dev_dbg(&dev->udev->dev, "%s", __func__);

	/* The SIERRA_NET_HIP_MSYNC_ID command appears to request that the
	 * firmware restart itself.  After restarting, the modem will respond
	 * with the SIERRA_NET_HIP_RESTART_ID indication.  The driver जारीs
	 * sending MSYNC commands every few seconds until it receives the
	 * RESTART event from the firmware
	 */

	/* tell modem we are पढ़ोy */
	status = sierra_net_send_sync(dev);
	अगर (status < 0)
		netdev_err(dev->net,
			"Send SYNC failed, status %d\n", status);
	status = sierra_net_send_sync(dev);
	अगर (status < 0)
		netdev_err(dev->net,
			"Send SYNC failed, status %d\n", status);

	/* Now, start a समयr and make sure we get the Restart Indication */
	priv->sync_समयr.expires = jअगरfies + SIERRA_NET_SYNCDELAY;
	add_समयr(&priv->sync_समयr);
पूर्ण

अटल व्योम sierra_net_kevent(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sierra_net_data *priv =
		container_of(work, काष्ठा sierra_net_data, sierra_net_kevent);
	काष्ठा usbnet *dev = priv->usbnet;
	पूर्णांक  len;
	पूर्णांक  err;
	u8  *buf;
	u8   अगरnum;

	अगर (test_bit(SIERRA_NET_EVENT_RESP_AVAIL, &priv->kevent_flags)) अणु
		clear_bit(SIERRA_NET_EVENT_RESP_AVAIL, &priv->kevent_flags);

		/* Query the modem क्रम the LSI message */
		buf = kzalloc(SIERRA_NET_USBCTL_BUF_LEN, GFP_KERNEL);
		अगर (!buf)
			वापस;

		अगरnum = priv->अगरnum;
		len = usb_control_msg(dev->udev, usb_rcvctrlpipe(dev->udev, 0),
				USB_CDC_GET_ENCAPSULATED_RESPONSE,
				USB_सूची_IN|USB_TYPE_CLASS|USB_RECIP_INTERFACE,
				0, अगरnum, buf, SIERRA_NET_USBCTL_BUF_LEN,
				USB_CTRL_SET_TIMEOUT);

		अगर (len < 0) अणु
			netdev_err(dev->net,
				"usb_control_msg failed, status %d\n", len);
		पूर्ण अन्यथा अणु
			काष्ठा hip_hdr	hh;

			dev_dbg(&dev->udev->dev, "%s: Received status message,"
				" %04x bytes", __func__, len);

			err = parse_hip(buf, len, &hh);
			अगर (err) अणु
				netdev_err(dev->net, "%s: Bad packet,"
					" parse result %d\n", __func__, err);
				kमुक्त(buf);
				वापस;
			पूर्ण

			/* Validate packet length */
			अगर (len != hh.hdrlen + hh.payload_len.word) अणु
				netdev_err(dev->net, "%s: Bad packet, received"
					" %d, expected %d\n",	__func__, len,
					hh.hdrlen + hh.payload_len.word);
				kमुक्त(buf);
				वापस;
			पूर्ण

			/* Switch on received message types */
			चयन (hh.msgid.byte) अणु
			हाल SIERRA_NET_HIP_LSI_UMTSID:
				dev_dbg(&dev->udev->dev, "LSI for ctx:%d",
					hh.msgspecअगरic.byte);
				sierra_net_handle_lsi(dev, buf, &hh);
				अवरोध;
			हाल SIERRA_NET_HIP_RESTART_ID:
				dev_dbg(&dev->udev->dev, "Restart reported: %d,"
						" stopping sync timer",
						hh.msgspecअगरic.byte);
				/* Got sync resp - stop समयr & clear mask */
				del_समयr_sync(&priv->sync_समयr);
				clear_bit(SIERRA_NET_TIMER_EXPIRY,
					  &priv->kevent_flags);
				अवरोध;
			हाल SIERRA_NET_HIP_HSYNC_ID:
				dev_dbg(&dev->udev->dev, "SYNC received");
				err = sierra_net_send_sync(dev);
				अगर (err < 0)
					netdev_err(dev->net,
						"Send SYNC failed %d\n", err);
				अवरोध;
			हाल SIERRA_NET_HIP_EXTENDEDID:
				netdev_err(dev->net, "Unrecognized HIP msg, "
					"extmsgid 0x%04x\n", hh.exपंचांगsgid.word);
				अवरोध;
			हाल SIERRA_NET_HIP_RCGI:
				/* Ignored */
				अवरोध;
			शेष:
				netdev_err(dev->net, "Unrecognized HIP msg, "
					"msgid 0x%02x\n", hh.msgid.byte);
				अवरोध;
			पूर्ण
		पूर्ण
		kमुक्त(buf);
	पूर्ण
	/* The sync समयr bit might be set */
	अगर (test_bit(SIERRA_NET_TIMER_EXPIRY, &priv->kevent_flags)) अणु
		clear_bit(SIERRA_NET_TIMER_EXPIRY, &priv->kevent_flags);
		dev_dbg(&dev->udev->dev, "Deferred sync timer expiry");
		sierra_net_करोsync(priv->usbnet);
	पूर्ण

	अगर (priv->kevent_flags)
		dev_dbg(&dev->udev->dev, "sierra_net_kevent done, "
			"kevent_flags = 0x%lx", priv->kevent_flags);
पूर्ण

अटल व्योम sierra_net_defer_kevent(काष्ठा usbnet *dev, पूर्णांक work)
अणु
	काष्ठा sierra_net_data *priv = sierra_net_get_निजी(dev);

	set_bit(work, &priv->kevent_flags);
	schedule_work(&priv->sierra_net_kevent);
पूर्ण

/*
 * Sync Retransmit Timer Handler. On expiry, kick the work queue
 */
अटल व्योम sierra_sync_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा sierra_net_data *priv = from_समयr(priv, t, sync_समयr);
	काष्ठा usbnet *dev = priv->usbnet;

	dev_dbg(&dev->udev->dev, "%s", __func__);
	/* Kick the tasklet */
	sierra_net_defer_kevent(dev, SIERRA_NET_TIMER_EXPIRY);
पूर्ण

अटल व्योम sierra_net_status(काष्ठा usbnet *dev, काष्ठा urb *urb)
अणु
	काष्ठा usb_cdc_notअगरication *event;

	dev_dbg(&dev->udev->dev, "%s", __func__);

	अगर (urb->actual_length < माप *event)
		वापस;

	/* Add हालs to handle other standard notअगरications. */
	event = urb->transfer_buffer;
	चयन (event->bNotअगरicationType) अणु
	हाल USB_CDC_NOTIFY_NETWORK_CONNECTION:
	हाल USB_CDC_NOTIFY_SPEED_CHANGE:
		/* USB 305 sends those */
		अवरोध;
	हाल USB_CDC_NOTIFY_RESPONSE_AVAILABLE:
		sierra_net_defer_kevent(dev, SIERRA_NET_EVENT_RESP_AVAIL);
		अवरोध;
	शेष:
		netdev_err(dev->net, ": unexpected notification %02x!\n",
				event->bNotअगरicationType);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम sierra_net_get_drvinfo(काष्ठा net_device *net,
		काष्ठा ethtool_drvinfo *info)
अणु
	/* Inherit standard device info */
	usbnet_get_drvinfo(net, info);
	strlcpy(info->driver, driver_name, माप(info->driver));
	strlcpy(info->version, DRIVER_VERSION, माप(info->version));
पूर्ण

अटल u32 sierra_net_get_link(काष्ठा net_device *net)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	/* Report link is करोwn whenever the पूर्णांकerface is करोwn */
	वापस sierra_net_get_निजी(dev)->link_up && netअगर_running(net);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops sierra_net_ethtool_ops = अणु
	.get_drvinfo = sierra_net_get_drvinfo,
	.get_link = sierra_net_get_link,
	.get_msglevel = usbnet_get_msglevel,
	.set_msglevel = usbnet_set_msglevel,
	.nway_reset = usbnet_nway_reset,
	.get_link_ksettings = usbnet_get_link_ksettings_mii,
	.set_link_ksettings = usbnet_set_link_ksettings_mii,
पूर्ण;

अटल पूर्णांक sierra_net_get_fw_attr(काष्ठा usbnet *dev, u16 *datap)
अणु
	पूर्णांक result = 0;
	__le16 attrdata;

	result = usbnet_पढ़ो_cmd(dev,
				/* _u8 venकरोr specअगरic request */
				SWI_USB_REQUEST_GET_FW_ATTR,
				USB_सूची_IN | USB_TYPE_VENDOR,	/* __u8 request type */
				0x0000,		/* __u16 value not used */
				0x0000,		/* __u16 index  not used */
				&attrdata,	/* अक्षर *data */
				माप(attrdata)	/* __u16 size */
				);

	अगर (result < 0)
		वापस -EIO;

	*datap = le16_to_cpu(attrdata);
	वापस result;
पूर्ण

/*
 * collects the bulk endpoपूर्णांकs, the status endpoपूर्णांक.
 */
अटल पूर्णांक sierra_net_bind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	u8	अगरacक्रमागत;
	u8	numendpoपूर्णांकs;
	u16	fwattr = 0;
	पूर्णांक	status;
	काष्ठा sierra_net_data *priv;
	अटल स्थिर u8 sync_पंचांगplate[माप(priv->sync_msg)] = अणु
		0x00, 0x00, SIERRA_NET_HIP_MSYNC_ID, 0x00पूर्ण;
	अटल स्थिर u8 shdwn_पंचांगplate[माप(priv->shdwn_msg)] = अणु
		0x00, 0x00, SIERRA_NET_HIP_SHUTD_ID, 0x00पूर्ण;

	dev_dbg(&dev->udev->dev, "%s", __func__);

	अगरacक्रमागत = पूर्णांकf->cur_altsetting->desc.bInterfaceNumber;
	numendpoपूर्णांकs = पूर्णांकf->cur_altsetting->desc.bNumEndpoपूर्णांकs;
	/* We have three endpoपूर्णांकs, bulk in and out, and a status */
	अगर (numendpoपूर्णांकs != 3) अणु
		dev_err(&dev->udev->dev, "Expected 3 endpoints, found: %d",
			numendpoपूर्णांकs);
		वापस -ENODEV;
	पूर्ण
	/* Status endpoपूर्णांक set in usbnet_get_endpoपूर्णांकs() */
	dev->status = शून्य;
	status = usbnet_get_endpoपूर्णांकs(dev, पूर्णांकf);
	अगर (status < 0) अणु
		dev_err(&dev->udev->dev, "Error in usbnet_get_endpoints (%d)",
			status);
		वापस -ENODEV;
	पूर्ण
	/* Initialize sierra निजी data */
	priv = kzalloc(माप *priv, GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->usbnet = dev;
	priv->अगरnum = अगरacक्रमागत;
	dev->net->netdev_ops = &sierra_net_device_ops;

	/* change MAC addr to include, अगरacक्रमागत, and to be unique */
	dev->net->dev_addr[ETH_ALEN-2] = atomic_inc_वापस(&अगरace_counter);
	dev->net->dev_addr[ETH_ALEN-1] = अगरacक्रमागत;

	/* prepare shutकरोwn message ढाँचा */
	स_नकल(priv->shdwn_msg, shdwn_पंचांगplate, माप(priv->shdwn_msg));
	/* set context index initially to 0 - prepares tx hdr ढाँचा */
	sierra_net_set_ctx_index(priv, 0);

	/* prepare sync message ढाँचा */
	स_नकल(priv->sync_msg, sync_पंचांगplate, माप(priv->sync_msg));

	/* decrease the rx_urb_size and max_tx_size to 4k on USB 1.1 */
	dev->rx_urb_size  = SIERRA_NET_RX_URB_SIZE;
	अगर (dev->udev->speed != USB_SPEED_HIGH)
		dev->rx_urb_size  = min_t(माप_प्रकार, 4096, SIERRA_NET_RX_URB_SIZE);

	dev->net->hard_header_len += SIERRA_NET_HIP_EXT_HDR_LEN;
	dev->hard_mtu = dev->net->mtu + dev->net->hard_header_len;
	dev->net->max_mtu = SIERRA_NET_MAX_SUPPORTED_MTU;

	/* Set up the netdev */
	dev->net->flags |= IFF_NOARP;
	dev->net->ethtool_ops = &sierra_net_ethtool_ops;
	netअगर_carrier_off(dev->net);

	sierra_net_set_निजी(dev, priv);

	priv->kevent_flags = 0;

	/* Use the shared workqueue */
	INIT_WORK(&priv->sierra_net_kevent, sierra_net_kevent);

	/* Only need to करो this once */
	समयr_setup(&priv->sync_समयr, sierra_sync_समयr, 0);

	/* verअगरy fw attributes */
	status = sierra_net_get_fw_attr(dev, &fwattr);
	dev_dbg(&dev->udev->dev, "Fw attr: %x\n", fwattr);

	/* test whether firmware supports DHCP */
	अगर (!(status == माप(fwattr) && (fwattr & SWI_GET_FW_ATTR_MASK))) अणु
		/* found incompatible firmware version */
		dev_err(&dev->udev->dev, "Incompatible driver and firmware"
			" versions\n");
		kमुक्त(priv);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sierra_net_unbind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	पूर्णांक status;
	काष्ठा sierra_net_data *priv = sierra_net_get_निजी(dev);

	dev_dbg(&dev->udev->dev, "%s", __func__);

	/* समाप्त the समयr and work */
	del_समयr_sync(&priv->sync_समयr);
	cancel_work_sync(&priv->sierra_net_kevent);

	/* tell modem we are going away */
	status = sierra_net_send_cmd(dev, priv->shdwn_msg,
			माप(priv->shdwn_msg), "Shutdown");
	अगर (status < 0)
		netdev_err(dev->net,
			"usb_control_msg failed, status %d\n", status);

	usbnet_status_stop(dev);

	sierra_net_set_निजी(dev, शून्य);
	kमुक्त(priv);
पूर्ण

अटल काष्ठा sk_buff *sierra_net_skb_clone(काष्ठा usbnet *dev,
		काष्ठा sk_buff *skb, पूर्णांक len)
अणु
	काष्ठा sk_buff *new_skb;

	/* clone skb */
	new_skb = skb_clone(skb, GFP_ATOMIC);

	/* हटाओ len bytes from original */
	skb_pull(skb, len);

	/* trim next packet to it's length */
	अगर (new_skb) अणु
		skb_trim(new_skb, len);
	पूर्ण अन्यथा अणु
		अगर (netअगर_msg_rx_err(dev))
			netdev_err(dev->net, "failed to get skb\n");
		dev->net->stats.rx_dropped++;
	पूर्ण

	वापस new_skb;
पूर्ण

/* ---------------------------- Receive data path ----------------------*/
अटल पूर्णांक sierra_net_rx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb)
अणु
	पूर्णांक err;
	काष्ठा hip_hdr  hh;
	काष्ठा sk_buff *new_skb;

	dev_dbg(&dev->udev->dev, "%s", __func__);

	/* could contain multiple packets */
	जबतक (likely(skb->len)) अणु
		err = parse_hip(skb->data, skb->len, &hh);
		अगर (err) अणु
			अगर (netअगर_msg_rx_err(dev))
				netdev_err(dev->net, "Invalid HIP header %d\n",
					err);
			/* dev->net->stats.rx_errors incremented by caller */
			dev->net->stats.rx_length_errors++;
			वापस 0;
		पूर्ण

		/* Validate Extended HIP header */
		अगर (!hh.exपंचांगsgid.is_present
		    || hh.exपंचांगsgid.word != SIERRA_NET_HIP_EXT_IP_IN_ID) अणु
			अगर (netअगर_msg_rx_err(dev))
				netdev_err(dev->net, "HIP/ETH: Invalid pkt\n");

			dev->net->stats.rx_frame_errors++;
			/* dev->net->stats.rx_errors incremented by caller */
			वापस 0;
		पूर्ण

		skb_pull(skb, hh.hdrlen);

		/* We are going to accept this packet, prepare it.
		 * In हाल protocol is IPv6, keep it, otherwise क्रमce IPv4.
		 */
		skb_reset_mac_header(skb);
		अगर (eth_hdr(skb)->h_proto != cpu_to_be16(ETH_P_IPV6))
			eth_hdr(skb)->h_proto = cpu_to_be16(ETH_P_IP);
		eth_zero_addr(eth_hdr(skb)->h_source);
		स_नकल(eth_hdr(skb)->h_dest, dev->net->dev_addr, ETH_ALEN);

		/* Last packet in batch handled by usbnet */
		अगर (hh.payload_len.word == skb->len)
			वापस 1;

		new_skb = sierra_net_skb_clone(dev, skb, hh.payload_len.word);
		अगर (new_skb)
			usbnet_skb_वापस(dev, new_skb);

	पूर्ण /* जबतक */

	वापस 0;
पूर्ण

/* ---------------------------- Transmit data path ----------------------*/
अटल काष्ठा sk_buff *sierra_net_tx_fixup(काष्ठा usbnet *dev,
					   काष्ठा sk_buff *skb, gfp_t flags)
अणु
	काष्ठा sierra_net_data *priv = sierra_net_get_निजी(dev);
	u16 len;
	bool need_tail;

	BUILD_BUG_ON(माप_field(काष्ठा usbnet, data)
				< माप(काष्ठा cdc_state));

	dev_dbg(&dev->udev->dev, "%s", __func__);
	अगर (priv->link_up && check_ethip_packet(skb, dev) && is_ip(skb)) अणु
		/* enough head room as is? */
		अगर (SIERRA_NET_HIP_EXT_HDR_LEN <= skb_headroom(skb)) अणु
			/* Save the Eth/IP length and set up HIP hdr */
			len = skb->len;
			skb_push(skb, SIERRA_NET_HIP_EXT_HDR_LEN);
			/* Handle ZLP issue */
			need_tail = ((len + SIERRA_NET_HIP_EXT_HDR_LEN)
				% dev->maxpacket == 0);
			अगर (need_tail) अणु
				अगर (unlikely(skb_tailroom(skb) == 0)) अणु
					netdev_err(dev->net, "tx_fixup:"
						"no room for packet\n");
					dev_kमुक्त_skb_any(skb);
					वापस शून्य;
				पूर्ण अन्यथा अणु
					skb->data[skb->len] = 0;
					__skb_put(skb, 1);
					len = len + 1;
				पूर्ण
			पूर्ण
			build_hip(skb->data, len, priv);
			वापस skb;
		पूर्ण अन्यथा अणु
			/*
			 * compensate in the future अगर necessary
			 */
			netdev_err(dev->net, "tx_fixup: no room for HIP\n");
		पूर्ण /* headroom */
	पूर्ण

	अगर (!priv->link_up)
		dev->net->stats.tx_carrier_errors++;

	/* tx_dropped incremented by usbnet */

	/* filter the packet out, release it  */
	dev_kमुक्त_skb_any(skb);
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा driver_info sierra_net_info_direct_ip = अणु
	.description = "Sierra Wireless USB-to-WWAN Modem",
	.flags = FLAG_WWAN | FLAG_SEND_ZLP,
	.bind = sierra_net_bind,
	.unbind = sierra_net_unbind,
	.status = sierra_net_status,
	.rx_fixup = sierra_net_rx_fixup,
	.tx_fixup = sierra_net_tx_fixup,
पूर्ण;

अटल पूर्णांक
sierra_net_probe(काष्ठा usb_पूर्णांकerface *udev, स्थिर काष्ठा usb_device_id *prod)
अणु
	पूर्णांक ret;

	ret = usbnet_probe(udev, prod);
	अगर (ret == 0) अणु
		काष्ठा usbnet *dev = usb_get_पूर्णांकfdata(udev);

		ret = usbnet_status_start(dev, GFP_KERNEL);
		अगर (ret == 0) अणु
			/* Interrupt URB now set up; initiate sync sequence */
			sierra_net_करोsync(dev);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

#घोषणा सूचीECT_IP_DEVICE(vend, prod) \
	अणुUSB_DEVICE_INTERFACE_NUMBER(vend, prod, 7), \
	.driver_info = (अचिन्हित दीर्घ)&sierra_net_info_direct_ipपूर्ण, \
	अणुUSB_DEVICE_INTERFACE_NUMBER(vend, prod, 10), \
	.driver_info = (अचिन्हित दीर्घ)&sierra_net_info_direct_ipपूर्ण, \
	अणुUSB_DEVICE_INTERFACE_NUMBER(vend, prod, 11), \
	.driver_info = (अचिन्हित दीर्घ)&sierra_net_info_direct_ipपूर्ण

अटल स्थिर काष्ठा usb_device_id products[] = अणु
	सूचीECT_IP_DEVICE(0x1199, 0x68A3), /* Sierra Wireless USB-to-WWAN modem */
	सूचीECT_IP_DEVICE(0x0F3D, 0x68A3), /* AT&T Direct IP modem */
	सूचीECT_IP_DEVICE(0x1199, 0x68AA), /* Sierra Wireless Direct IP LTE modem */
	सूचीECT_IP_DEVICE(0x0F3D, 0x68AA), /* AT&T Direct IP LTE modem */

	अणुपूर्ण, /* last item */
पूर्ण;
MODULE_DEVICE_TABLE(usb, products);

/* We are based on usbnet, so let it handle the USB driver specअगरics */
अटल काष्ठा usb_driver sierra_net_driver = अणु
	.name = "sierra_net",
	.id_table = products,
	.probe = sierra_net_probe,
	.disconnect = usbnet_disconnect,
	.suspend = usbnet_suspend,
	.resume = usbnet_resume,
	.no_dynamic_id = 1,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(sierra_net_driver);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION(DRIVER_VERSION);
MODULE_LICENSE("GPL");
