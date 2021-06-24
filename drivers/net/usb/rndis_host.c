<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Host Side support क्रम RNDIS Networking Links
 * Copyright (C) 2005 by David Brownell
 */
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/slab.h>
#समावेश <linux/mii.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/cdc.h>
#समावेश <linux/usb/usbnet.h>
#समावेश <linux/usb/rndis_host.h>


/*
 * RNDIS is NDIS remoted over USB.  It's a MSFT variant of CDC ACM ... of
 * course ACM was पूर्णांकended क्रम modems, not Ethernet links!  USB's standard
 * क्रम Ethernet links is "CDC Ethernet", which is signअगरicantly simpler.
 *
 * NOTE that Microsoft's "RNDIS 1.0" specअगरication is incomplete.  Issues
 * include:
 *    - Power management in particular relies on inक्रमmation that's scattered
 *	through other करोcumentation, and which is incomplete or incorrect even
 *	there.
 *    - There are various unकरोcumented protocol requirements, such as the
 *	need to send unused garbage in control-OUT messages.
 *    - In some हालs, MS-Winकरोws will emit unकरोcumented requests; this
 *	matters more to peripheral implementations than host ones.
 *
 * Moreover there's a no-खोलो-specs variant of RNDIS called "ActiveSync".
 *
 * For these reasons and others, ** USE OF RNDIS IS STRONGLY DISCOURAGED ** in
 * favor of such non-proprietary alternatives as CDC Ethernet or the newer (and
 * currently rare) "Ethernet Emulation Model" (EEM).
 */

/*
 * RNDIS notअगरications from device: command completion; "reverse"
 * keepalives; etc
 */
व्योम rndis_status(काष्ठा usbnet *dev, काष्ठा urb *urb)
अणु
	netdev_dbg(dev->net, "rndis status urb, len %d stat %d\n",
		   urb->actual_length, urb->status);
	// FIXME क्रम keepalives, respond immediately (asynchronously)
	// अगर not an RNDIS status, करो like cdc_status(dev,urb) करोes
पूर्ण
EXPORT_SYMBOL_GPL(rndis_status);

/*
 * RNDIS indicate messages.
 */
अटल व्योम rndis_msg_indicate(काष्ठा usbnet *dev, काष्ठा rndis_indicate *msg,
				पूर्णांक buflen)
अणु
	काष्ठा cdc_state *info = (व्योम *)&dev->data;
	काष्ठा device *udev = &info->control->dev;

	अगर (dev->driver_info->indication) अणु
		dev->driver_info->indication(dev, msg, buflen);
	पूर्ण अन्यथा अणु
		u32 status = le32_to_cpu(msg->status);

		चयन (status) अणु
		हाल RNDIS_STATUS_MEDIA_CONNECT:
			dev_info(udev, "rndis media connect\n");
			अवरोध;
		हाल RNDIS_STATUS_MEDIA_DISCONNECT:
			dev_info(udev, "rndis media disconnect\n");
			अवरोध;
		शेष:
			dev_info(udev, "rndis indication: 0x%08x\n", status);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * RPC करोne RNDIS-style.  Caller guarantees:
 * - message is properly byteswapped
 * - there's no other request pending
 * - buf can hold up to 1KB response (required by RNDIS spec)
 * On वापस, the first few entries are alपढ़ोy byteswapped.
 *
 * Call context is likely probe(), beक्रमe पूर्णांकerface name is known,
 * which is why we won't try to use it in the diagnostics.
 */
पूर्णांक rndis_command(काष्ठा usbnet *dev, काष्ठा rndis_msg_hdr *buf, पूर्णांक buflen)
अणु
	काष्ठा cdc_state	*info = (व्योम *) &dev->data;
	काष्ठा usb_cdc_notअगरication notअगरication;
	पूर्णांक			master_अगरnum;
	पूर्णांक			retval;
	पूर्णांक			partial;
	अचिन्हित		count;
	u32			xid = 0, msg_len, request_id, msg_type, rsp,
				status;

	/* REVISIT when this माला_लो called from contexts other than probe() or
	 * disconnect(): either serialize, or dispatch responses on xid
	 */

	msg_type = le32_to_cpu(buf->msg_type);

	/* Issue the request; xid is unique, करोn't bother byteswapping it */
	अगर (likely(msg_type != RNDIS_MSG_HALT && msg_type != RNDIS_MSG_RESET)) अणु
		xid = dev->xid++;
		अगर (!xid)
			xid = dev->xid++;
		buf->request_id = (__क्रमce __le32) xid;
	पूर्ण
	master_अगरnum = info->control->cur_altsetting->desc.bInterfaceNumber;
	retval = usb_control_msg(dev->udev,
		usb_sndctrlpipe(dev->udev, 0),
		USB_CDC_SEND_ENCAPSULATED_COMMAND,
		USB_TYPE_CLASS | USB_RECIP_INTERFACE,
		0, master_अगरnum,
		buf, le32_to_cpu(buf->msg_len),
		RNDIS_CONTROL_TIMEOUT_MS);
	अगर (unlikely(retval < 0 || xid == 0))
		वापस retval;

	/* Some devices करोn't respond on the control channel until
	 * polled on the status channel, so करो that first. */
	अगर (dev->driver_info->data & RNDIS_DRIVER_DATA_POLL_STATUS) अणु
		retval = usb_पूर्णांकerrupt_msg(
			dev->udev,
			usb_rcvपूर्णांकpipe(dev->udev,
				       dev->status->desc.bEndpoपूर्णांकAddress),
			&notअगरication, माप(notअगरication), &partial,
			RNDIS_CONTROL_TIMEOUT_MS);
		अगर (unlikely(retval < 0))
			वापस retval;
	पूर्ण

	/* Poll the control channel; the request probably completed immediately */
	rsp = le32_to_cpu(buf->msg_type) | RNDIS_MSG_COMPLETION;
	क्रम (count = 0; count < 10; count++) अणु
		स_रखो(buf, 0, CONTROL_BUFFER_SIZE);
		retval = usb_control_msg(dev->udev,
			usb_rcvctrlpipe(dev->udev, 0),
			USB_CDC_GET_ENCAPSULATED_RESPONSE,
			USB_सूची_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
			0, master_अगरnum,
			buf, buflen,
			RNDIS_CONTROL_TIMEOUT_MS);
		अगर (likely(retval >= 8)) अणु
			msg_type = le32_to_cpu(buf->msg_type);
			msg_len = le32_to_cpu(buf->msg_len);
			status = le32_to_cpu(buf->status);
			request_id = (__क्रमce u32) buf->request_id;
			अगर (likely(msg_type == rsp)) अणु
				अगर (likely(request_id == xid)) अणु
					अगर (unlikely(rsp == RNDIS_MSG_RESET_C))
						वापस 0;
					अगर (likely(RNDIS_STATUS_SUCCESS ==
							status))
						वापस 0;
					dev_dbg(&info->control->dev,
						"rndis reply status %08x\n",
						status);
					वापस -EL3RST;
				पूर्ण
				dev_dbg(&info->control->dev,
					"rndis reply id %d expected %d\n",
					request_id, xid);
				/* then likely retry */
			पूर्ण अन्यथा चयन (msg_type) अणु
			हाल RNDIS_MSG_INDICATE: /* fault/event */
				rndis_msg_indicate(dev, (व्योम *)buf, buflen);
				अवरोध;
			हाल RNDIS_MSG_KEEPALIVE: अणु /* ping */
				काष्ठा rndis_keepalive_c *msg = (व्योम *)buf;

				msg->msg_type = cpu_to_le32(RNDIS_MSG_KEEPALIVE_C);
				msg->msg_len = cpu_to_le32(माप *msg);
				msg->status = cpu_to_le32(RNDIS_STATUS_SUCCESS);
				retval = usb_control_msg(dev->udev,
					usb_sndctrlpipe(dev->udev, 0),
					USB_CDC_SEND_ENCAPSULATED_COMMAND,
					USB_TYPE_CLASS | USB_RECIP_INTERFACE,
					0, master_अगरnum,
					msg, माप *msg,
					RNDIS_CONTROL_TIMEOUT_MS);
				अगर (unlikely(retval < 0))
					dev_dbg(&info->control->dev,
						"rndis keepalive err %d\n",
						retval);
				पूर्ण
				अवरोध;
			शेष:
				dev_dbg(&info->control->dev,
					"unexpected rndis msg %08x len %d\n",
					le32_to_cpu(buf->msg_type), msg_len);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* device probably issued a protocol stall; ignore */
			dev_dbg(&info->control->dev,
				"rndis response error, code %d\n", retval);
		पूर्ण
		msleep(40);
	पूर्ण
	dev_dbg(&info->control->dev, "rndis response timeout\n");
	वापस -ETIMEDOUT;
पूर्ण
EXPORT_SYMBOL_GPL(rndis_command);

/*
 * rndis_query:
 *
 * Perक्रमms a query क्रम @oid aदीर्घ with 0 or more bytes of payload as
 * specअगरied by @in_len. If @reply_len is not set to -1 then the reply
 * length is checked against this value, resulting in an error अगर it
 * करोesn't match.
 *
 * NOTE: Adding a payload exactly or greater than the size of the expected
 * response payload is an evident requirement MSFT added क्रम ActiveSync.
 *
 * The only exception is क्रम OIDs that वापस a variably sized response,
 * in which हाल no payload should be added.  This unकरोcumented (and
 * nonsensical!) issue was found by snअगरfing protocol requests from the
 * ActiveSync 4.1 Winकरोws driver.
 */
अटल पूर्णांक rndis_query(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		व्योम *buf, u32 oid, u32 in_len,
		व्योम **reply, पूर्णांक *reply_len)
अणु
	पूर्णांक retval;
	जोड़ अणु
		व्योम			*buf;
		काष्ठा rndis_msg_hdr	*header;
		काष्ठा rndis_query	*get;
		काष्ठा rndis_query_c	*get_c;
	पूर्ण u;
	u32 off, len;

	u.buf = buf;

	स_रखो(u.get, 0, माप *u.get + in_len);
	u.get->msg_type = cpu_to_le32(RNDIS_MSG_QUERY);
	u.get->msg_len = cpu_to_le32(माप *u.get + in_len);
	u.get->oid = cpu_to_le32(oid);
	u.get->len = cpu_to_le32(in_len);
	u.get->offset = cpu_to_le32(20);

	retval = rndis_command(dev, u.header, CONTROL_BUFFER_SIZE);
	अगर (unlikely(retval < 0)) अणु
		dev_err(&पूर्णांकf->dev, "RNDIS_MSG_QUERY(0x%08x) failed, %d\n",
				oid, retval);
		वापस retval;
	पूर्ण

	off = le32_to_cpu(u.get_c->offset);
	len = le32_to_cpu(u.get_c->len);
	अगर (unlikely((8 + off + len) > CONTROL_BUFFER_SIZE))
		जाओ response_error;

	अगर (*reply_len != -1 && len != *reply_len)
		जाओ response_error;

	*reply = (अचिन्हित अक्षर *) &u.get_c->request_id + off;
	*reply_len = len;

	वापस retval;

response_error:
	dev_err(&पूर्णांकf->dev, "RNDIS_MSG_QUERY(0x%08x) "
			"invalid response - off %d len %d\n",
		oid, off, len);
	वापस -गलत_तर्क;
पूर्ण

/* same as usbnet_netdev_ops but MTU change not allowed */
अटल स्थिर काष्ठा net_device_ops rndis_netdev_ops = अणु
	.nकरो_खोलो		= usbnet_खोलो,
	.nकरो_stop		= usbnet_stop,
	.nकरो_start_xmit		= usbnet_start_xmit,
	.nकरो_tx_समयout		= usbnet_tx_समयout,
	.nकरो_get_stats64	= dev_get_tstats64,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

पूर्णांक
generic_rndis_bind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf, पूर्णांक flags)
अणु
	पूर्णांक			retval;
	काष्ठा net_device	*net = dev->net;
	काष्ठा cdc_state	*info = (व्योम *) &dev->data;
	जोड़ अणु
		व्योम			*buf;
		काष्ठा rndis_msg_hdr	*header;
		काष्ठा rndis_init	*init;
		काष्ठा rndis_init_c	*init_c;
		काष्ठा rndis_query	*get;
		काष्ठा rndis_query_c	*get_c;
		काष्ठा rndis_set	*set;
		काष्ठा rndis_set_c	*set_c;
		काष्ठा rndis_halt	*halt;
	पूर्ण u;
	u32			पंचांगp;
	__le32			phym_unspec, *phym;
	पूर्णांक			reply_len;
	अचिन्हित अक्षर		*bp;

	/* we can't rely on i/o from stack working, or stack allocation */
	u.buf = kदो_स्मृति(CONTROL_BUFFER_SIZE, GFP_KERNEL);
	अगर (!u.buf)
		वापस -ENOMEM;
	retval = usbnet_generic_cdc_bind(dev, पूर्णांकf);
	अगर (retval < 0)
		जाओ fail;

	u.init->msg_type = cpu_to_le32(RNDIS_MSG_INIT);
	u.init->msg_len = cpu_to_le32(माप *u.init);
	u.init->major_version = cpu_to_le32(1);
	u.init->minor_version = cpu_to_le32(0);

	/* max transfer (in spec) is 0x4000 at full speed, but क्रम
	 * TX we'll stick to one Ethernet packet plus RNDIS framing.
	 * For RX we handle drivers that zero-pad to end-of-packet.
	 * Don't let userspace change these settings.
	 *
	 * NOTE: there still seems to be wierdness here, as अगर we need
	 * to करो some more things to make sure WinCE tarमाला_लो accept this.
	 * They शेष to jumbograms of 8KB or 16KB, which is असलurd
	 * क्रम such low data rates and which is also more than Linux
	 * can usually expect to allocate क्रम SKB data...
	 */
	net->hard_header_len += माप (काष्ठा rndis_data_hdr);
	dev->hard_mtu = net->mtu + net->hard_header_len;

	dev->maxpacket = usb_maxpacket(dev->udev, dev->out, 1);
	अगर (dev->maxpacket == 0) अणु
		netअगर_dbg(dev, probe, dev->net,
			  "dev->maxpacket can't be 0\n");
		retval = -EINVAL;
		जाओ fail_and_release;
	पूर्ण

	dev->rx_urb_size = dev->hard_mtu + (dev->maxpacket + 1);
	dev->rx_urb_size &= ~(dev->maxpacket - 1);
	u.init->max_transfer_size = cpu_to_le32(dev->rx_urb_size);

	net->netdev_ops = &rndis_netdev_ops;

	retval = rndis_command(dev, u.header, CONTROL_BUFFER_SIZE);
	अगर (unlikely(retval < 0)) अणु
		/* it might not even be an RNDIS device!! */
		dev_err(&पूर्णांकf->dev, "RNDIS init failed, %d\n", retval);
		जाओ fail_and_release;
	पूर्ण
	पंचांगp = le32_to_cpu(u.init_c->max_transfer_size);
	अगर (पंचांगp < dev->hard_mtu) अणु
		अगर (पंचांगp <= net->hard_header_len) अणु
			dev_err(&पूर्णांकf->dev,
				"dev can't take %u byte packets (max %u)\n",
				dev->hard_mtu, पंचांगp);
			retval = -EINVAL;
			जाओ halt_fail_and_release;
		पूर्ण
		dev_warn(&पूर्णांकf->dev,
			 "dev can't take %u byte packets (max %u), "
			 "adjusting MTU to %u\n",
			 dev->hard_mtu, पंचांगp, पंचांगp - net->hard_header_len);
		dev->hard_mtu = पंचांगp;
		net->mtu = dev->hard_mtu - net->hard_header_len;
	पूर्ण

	/* REVISIT:  peripheral "alignment" request is ignored ... */
	dev_dbg(&पूर्णांकf->dev,
		"hard mtu %u (%u from dev), rx buflen %zu, align %d\n",
		dev->hard_mtu, पंचांगp, dev->rx_urb_size,
		1 << le32_to_cpu(u.init_c->packet_alignment));

	/* module has some device initialization code needs to be करोne right
	 * after RNDIS_INIT */
	अगर (dev->driver_info->early_init &&
			dev->driver_info->early_init(dev) != 0)
		जाओ halt_fail_and_release;

	/* Check physical medium */
	phym = शून्य;
	reply_len = माप *phym;
	retval = rndis_query(dev, पूर्णांकf, u.buf,
			     RNDIS_OID_GEN_PHYSICAL_MEDIUM,
			     reply_len, (व्योम **)&phym, &reply_len);
	अगर (retval != 0 || !phym) अणु
		/* OID is optional so करोn't fail here. */
		phym_unspec = cpu_to_le32(RNDIS_PHYSICAL_MEDIUM_UNSPECIFIED);
		phym = &phym_unspec;
	पूर्ण
	अगर ((flags & FLAG_RNDIS_PHYM_WIRELESS) &&
	    le32_to_cpup(phym) != RNDIS_PHYSICAL_MEDIUM_WIRELESS_LAN) अणु
		netअगर_dbg(dev, probe, dev->net,
			  "driver requires wireless physical medium, but device is not\n");
		retval = -ENODEV;
		जाओ halt_fail_and_release;
	पूर्ण
	अगर ((flags & FLAG_RNDIS_PHYM_NOT_WIRELESS) &&
	    le32_to_cpup(phym) == RNDIS_PHYSICAL_MEDIUM_WIRELESS_LAN) अणु
		netअगर_dbg(dev, probe, dev->net,
			  "driver requires non-wireless physical medium, but device is wireless.\n");
		retval = -ENODEV;
		जाओ halt_fail_and_release;
	पूर्ण

	/* Get designated host ethernet address */
	reply_len = ETH_ALEN;
	retval = rndis_query(dev, पूर्णांकf, u.buf,
			     RNDIS_OID_802_3_PERMANENT_ADDRESS,
			     48, (व्योम **) &bp, &reply_len);
	अगर (unlikely(retval< 0)) अणु
		dev_err(&पूर्णांकf->dev, "rndis get ethaddr, %d\n", retval);
		जाओ halt_fail_and_release;
	पूर्ण

	अगर (bp[0] & 0x02)
		eth_hw_addr_अक्रमom(net);
	अन्यथा
		ether_addr_copy(net->dev_addr, bp);

	/* set a nonzero filter to enable data transfers */
	स_रखो(u.set, 0, माप *u.set);
	u.set->msg_type = cpu_to_le32(RNDIS_MSG_SET);
	u.set->msg_len = cpu_to_le32(4 + माप *u.set);
	u.set->oid = cpu_to_le32(RNDIS_OID_GEN_CURRENT_PACKET_FILTER);
	u.set->len = cpu_to_le32(4);
	u.set->offset = cpu_to_le32((माप *u.set) - 8);
	*(__le32 *)(u.buf + माप *u.set) = cpu_to_le32(RNDIS_DEFAULT_FILTER);

	retval = rndis_command(dev, u.header, CONTROL_BUFFER_SIZE);
	अगर (unlikely(retval < 0)) अणु
		dev_err(&पूर्णांकf->dev, "rndis set packet filter, %d\n", retval);
		जाओ halt_fail_and_release;
	पूर्ण

	retval = 0;

	kमुक्त(u.buf);
	वापस retval;

halt_fail_and_release:
	स_रखो(u.halt, 0, माप *u.halt);
	u.halt->msg_type = cpu_to_le32(RNDIS_MSG_HALT);
	u.halt->msg_len = cpu_to_le32(माप *u.halt);
	(व्योम) rndis_command(dev, (व्योम *)u.halt, CONTROL_BUFFER_SIZE);
fail_and_release:
	usb_set_पूर्णांकfdata(info->data, शून्य);
	usb_driver_release_पूर्णांकerface(driver_of(पूर्णांकf), info->data);
	info->data = शून्य;
fail:
	kमुक्त(u.buf);
	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(generic_rndis_bind);

अटल पूर्णांक rndis_bind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	वापस generic_rndis_bind(dev, पूर्णांकf, FLAG_RNDIS_PHYM_NOT_WIRELESS);
पूर्ण

व्योम rndis_unbind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा rndis_halt	*halt;

	/* try to clear any rndis state/activity (no i/o from stack!) */
	halt = kzalloc(CONTROL_BUFFER_SIZE, GFP_KERNEL);
	अगर (halt) अणु
		halt->msg_type = cpu_to_le32(RNDIS_MSG_HALT);
		halt->msg_len = cpu_to_le32(माप *halt);
		(व्योम) rndis_command(dev, (व्योम *)halt, CONTROL_BUFFER_SIZE);
		kमुक्त(halt);
	पूर्ण

	usbnet_cdc_unbind(dev, पूर्णांकf);
पूर्ण
EXPORT_SYMBOL_GPL(rndis_unbind);

/*
 * DATA -- host must not ग_लिखो zlps
 */
पूर्णांक rndis_rx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb)
अणु
	/* This check is no दीर्घer करोne by usbnet */
	अगर (skb->len < dev->net->hard_header_len)
		वापस 0;

	/* peripheral may have batched packets to us... */
	जबतक (likely(skb->len)) अणु
		काष्ठा rndis_data_hdr	*hdr = (व्योम *)skb->data;
		काष्ठा sk_buff		*skb2;
		u32			msg_type, msg_len, data_offset, data_len;

		msg_type = le32_to_cpu(hdr->msg_type);
		msg_len = le32_to_cpu(hdr->msg_len);
		data_offset = le32_to_cpu(hdr->data_offset);
		data_len = le32_to_cpu(hdr->data_len);

		/* करोn't choke अगर we see oob, per-packet data, etc */
		अगर (unlikely(msg_type != RNDIS_MSG_PACKET || skb->len < msg_len
				|| (data_offset + data_len + 8) > msg_len)) अणु
			dev->net->stats.rx_frame_errors++;
			netdev_dbg(dev->net, "bad rndis message %d/%d/%d/%d, len %d\n",
				   le32_to_cpu(hdr->msg_type),
				   msg_len, data_offset, data_len, skb->len);
			वापस 0;
		पूर्ण
		skb_pull(skb, 8 + data_offset);

		/* at most one packet left? */
		अगर (likely((data_len - skb->len) <= माप *hdr)) अणु
			skb_trim(skb, data_len);
			अवरोध;
		पूर्ण

		/* try to वापस all the packets in the batch */
		skb2 = skb_clone(skb, GFP_ATOMIC);
		अगर (unlikely(!skb2))
			अवरोध;
		skb_pull(skb, msg_len - माप *hdr);
		skb_trim(skb2, data_len);
		usbnet_skb_वापस(dev, skb2);
	पूर्ण

	/* caller will usbnet_skb_वापस the reमुख्यing packet */
	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(rndis_rx_fixup);

काष्ठा sk_buff *
rndis_tx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb, gfp_t flags)
अणु
	काष्ठा rndis_data_hdr	*hdr;
	काष्ठा sk_buff		*skb2;
	अचिन्हित		len = skb->len;

	अगर (likely(!skb_cloned(skb))) अणु
		पूर्णांक	room = skb_headroom(skb);

		/* enough head room as-is? */
		अगर (unlikely((माप *hdr) <= room))
			जाओ fill;

		/* enough room, but needs to be पढ़ोjusted? */
		room += skb_tailroom(skb);
		अगर (likely((माप *hdr) <= room)) अणु
			skb->data = स_हटाओ(skb->head + माप *hdr,
					    skb->data, len);
			skb_set_tail_poपूर्णांकer(skb, len);
			जाओ fill;
		पूर्ण
	पूर्ण

	/* create a new skb, with the correct size (and tailpad) */
	skb2 = skb_copy_expand(skb, माप *hdr, 1, flags);
	dev_kमुक्त_skb_any(skb);
	अगर (unlikely(!skb2))
		वापस skb2;
	skb = skb2;

	/* fill out the RNDIS header.  we won't bother trying to batch
	 * packets; Linux minimizes wasted bandwidth through tx queues.
	 */
fill:
	hdr = __skb_push(skb, माप *hdr);
	स_रखो(hdr, 0, माप *hdr);
	hdr->msg_type = cpu_to_le32(RNDIS_MSG_PACKET);
	hdr->msg_len = cpu_to_le32(skb->len);
	hdr->data_offset = cpu_to_le32(माप(*hdr) - 8);
	hdr->data_len = cpu_to_le32(len);

	/* FIXME make the last packet always be लघु ... */
	वापस skb;
पूर्ण
EXPORT_SYMBOL_GPL(rndis_tx_fixup);


अटल स्थिर काष्ठा driver_info	rndis_info = अणु
	.description =	"RNDIS device",
	.flags =	FLAG_ETHER | FLAG_POINTTOPOINT | FLAG_FRAMING_RN | FLAG_NO_SETINT,
	.bind =		rndis_bind,
	.unbind =	rndis_unbind,
	.status =	rndis_status,
	.rx_fixup =	rndis_rx_fixup,
	.tx_fixup =	rndis_tx_fixup,
पूर्ण;

अटल स्थिर काष्ठा driver_info	rndis_poll_status_info = अणु
	.description =	"RNDIS device (poll status before control)",
	.flags =	FLAG_ETHER | FLAG_POINTTOPOINT | FLAG_FRAMING_RN | FLAG_NO_SETINT,
	.data =		RNDIS_DRIVER_DATA_POLL_STATUS,
	.bind =		rndis_bind,
	.unbind =	rndis_unbind,
	.status =	rndis_status,
	.rx_fixup =	rndis_rx_fixup,
	.tx_fixup =	rndis_tx_fixup,
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल स्थिर काष्ठा usb_device_id	products [] = अणु
अणु
	/* 2Wire HomePortal 1000SW */
	USB_DEVICE_AND_INTERFACE_INFO(0x1630, 0x0042,
				      USB_CLASS_COMM, 2 /* ACM */, 0x0ff),
	.driver_info = (अचिन्हित दीर्घ) &rndis_poll_status_info,
पूर्ण, अणु
	/* RNDIS is MSFT's un-official variant of CDC ACM */
	USB_INTERFACE_INFO(USB_CLASS_COMM, 2 /* ACM */, 0x0ff),
	.driver_info = (अचिन्हित दीर्घ) &rndis_info,
पूर्ण, अणु
	/* "ActiveSync" is an unकरोcumented variant of RNDIS, used in WM5 */
	USB_INTERFACE_INFO(USB_CLASS_MISC, 1, 1),
	.driver_info = (अचिन्हित दीर्घ) &rndis_poll_status_info,
पूर्ण, अणु
	/* RNDIS क्रम tethering */
	USB_INTERFACE_INFO(USB_CLASS_WIRELESS_CONTROLLER, 1, 3),
	.driver_info = (अचिन्हित दीर्घ) &rndis_info,
पूर्ण, अणु
	/* Novatel Verizon USB730L */
	USB_INTERFACE_INFO(USB_CLASS_MISC, 4, 1),
	.driver_info = (अचिन्हित दीर्घ) &rndis_info,
पूर्ण,
	अणु पूर्ण,		// END
पूर्ण;
MODULE_DEVICE_TABLE(usb, products);

अटल काष्ठा usb_driver rndis_driver = अणु
	.name =		"rndis_host",
	.id_table =	products,
	.probe =	usbnet_probe,
	.disconnect =	usbnet_disconnect,
	.suspend =	usbnet_suspend,
	.resume =	usbnet_resume,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(rndis_driver);

MODULE_AUTHOR("David Brownell");
MODULE_DESCRIPTION("USB Host side RNDIS driver");
MODULE_LICENSE("GPL");
