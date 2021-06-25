<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012  Smith Micro Software, Inc.
 * Copyright (c) 2012  Bjथचrn Mork <bjorn@mork.no>
 *
 * This driver is based on and reuse most of cdc_ncm, which is
 * Copyright (C) ST-Ericsson 2010-2012
 */

#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/ip.h>
#समावेश <linux/mii.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/cdc.h>
#समावेश <linux/usb/usbnet.h>
#समावेश <linux/usb/cdc-wdm.h>
#समावेश <linux/usb/cdc_ncm.h>
#समावेश <net/ipv6.h>
#समावेश <net/addrconf.h>
#समावेश <net/ipv6_stubs.h>

/* alternative VLAN क्रम IP session 0 अगर not untagged */
#घोषणा MBIM_IPS0_VID	4094

/* driver specअगरic data - must match cdc_ncm usage */
काष्ठा cdc_mbim_state अणु
	काष्ठा cdc_ncm_ctx *ctx;
	atomic_t pmcount;
	काष्ठा usb_driver *subdriver;
	अचिन्हित दीर्घ _unused;
	अचिन्हित दीर्घ flags;
पूर्ण;

/* flags क्रम the cdc_mbim_state.flags field */
क्रमागत cdc_mbim_flags अणु
	FLAG_IPS0_VLAN = 1 << 0,	/* IP session 0 is tagged  */
पूर्ण;

/* using a counter to merge subdriver requests with our own पूर्णांकo a combined state */
अटल पूर्णांक cdc_mbim_manage_घातer(काष्ठा usbnet *dev, पूर्णांक on)
अणु
	काष्ठा cdc_mbim_state *info = (व्योम *)&dev->data;
	पूर्णांक rv = 0;

	dev_dbg(&dev->पूर्णांकf->dev, "%s() pmcount=%d, on=%d\n", __func__, atomic_पढ़ो(&info->pmcount), on);

	अगर ((on && atomic_add_वापस(1, &info->pmcount) == 1) || (!on && atomic_dec_and_test(&info->pmcount))) अणु
		/* need स्वतःpm_get/put here to ensure the usbcore sees the new value */
		rv = usb_स्वतःpm_get_पूर्णांकerface(dev->पूर्णांकf);
		dev->पूर्णांकf->needs_remote_wakeup = on;
		अगर (!rv)
			usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकf);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cdc_mbim_wdm_manage_घातer(काष्ठा usb_पूर्णांकerface *पूर्णांकf, पूर्णांक status)
अणु
	काष्ठा usbnet *dev = usb_get_पूर्णांकfdata(पूर्णांकf);

	/* can be called जबतक disconnecting */
	अगर (!dev)
		वापस 0;

	वापस cdc_mbim_manage_घातer(dev, status);
पूर्ण

अटल पूर्णांक cdc_mbim_rx_add_vid(काष्ठा net_device *netdev, __be16 proto, u16 vid)
अणु
	काष्ठा usbnet *dev = netdev_priv(netdev);
	काष्ठा cdc_mbim_state *info = (व्योम *)&dev->data;

	/* creation of this VLAN is a request to tag IP session 0 */
	अगर (vid == MBIM_IPS0_VID)
		info->flags |= FLAG_IPS0_VLAN;
	अन्यथा
		अगर (vid >= 512)	/* we करोn't map these to MBIM session */
			वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक cdc_mbim_rx_समाप्त_vid(काष्ठा net_device *netdev, __be16 proto, u16 vid)
अणु
	काष्ठा usbnet *dev = netdev_priv(netdev);
	काष्ठा cdc_mbim_state *info = (व्योम *)&dev->data;

	/* this is a request क्रम an untagged IP session 0 */
	अगर (vid == MBIM_IPS0_VID)
		info->flags &= ~FLAG_IPS0_VLAN;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops cdc_mbim_netdev_ops = अणु
	.nकरो_खोलो             = usbnet_खोलो,
	.nकरो_stop             = usbnet_stop,
	.nकरो_start_xmit       = usbnet_start_xmit,
	.nकरो_tx_समयout       = usbnet_tx_समयout,
	.nकरो_get_stats64      = dev_get_tstats64,
	.nकरो_change_mtu       = cdc_ncm_change_mtu,
	.nकरो_set_mac_address  = eth_mac_addr,
	.nकरो_validate_addr    = eth_validate_addr,
	.nकरो_vlan_rx_add_vid  = cdc_mbim_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid = cdc_mbim_rx_समाप्त_vid,
पूर्ण;

/* Change the control पूर्णांकerface altsetting and update the .driver_info
 * poपूर्णांकer अगर the matching entry after changing class codes poपूर्णांकs to
 * a dअगरferent काष्ठा
 */
अटल पूर्णांक cdc_mbim_set_ctrlalt(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf, u8 alt)
अणु
	काष्ठा usb_driver *driver = to_usb_driver(पूर्णांकf->dev.driver);
	स्थिर काष्ठा usb_device_id *id;
	काष्ठा driver_info *info;
	पूर्णांक ret;

	ret = usb_set_पूर्णांकerface(dev->udev,
				पूर्णांकf->cur_altsetting->desc.bInterfaceNumber,
				alt);
	अगर (ret)
		वापस ret;

	id = usb_match_id(पूर्णांकf, driver->id_table);
	अगर (!id)
		वापस -ENODEV;

	info = (काष्ठा driver_info *)id->driver_info;
	अगर (info != dev->driver_info) अणु
		dev_dbg(&पूर्णांकf->dev, "driver_info updated to '%s'\n",
			info->description);
		dev->driver_info = info;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cdc_mbim_bind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा cdc_ncm_ctx *ctx;
	काष्ठा usb_driver *subdriver = ERR_PTR(-ENODEV);
	पूर्णांक ret = -ENODEV;
	u8 data_altsetting = 1;
	काष्ठा cdc_mbim_state *info = (व्योम *)&dev->data;

	/* should we change control altsetting on a NCM/MBIM function? */
	अगर (cdc_ncm_select_altsetting(पूर्णांकf) == CDC_NCM_COMM_ALTSETTING_MBIM) अणु
		data_altsetting = CDC_NCM_DATA_ALTSETTING_MBIM;
		ret = cdc_mbim_set_ctrlalt(dev, पूर्णांकf, CDC_NCM_COMM_ALTSETTING_MBIM);
		अगर (ret)
			जाओ err;
		ret = -ENODEV;
	पूर्ण

	/* we will hit this क्रम NCM/MBIM functions अगर prefer_mbim is false */
	अगर (!cdc_ncm_comm_पूर्णांकf_is_mbim(पूर्णांकf->cur_altsetting))
		जाओ err;

	ret = cdc_ncm_bind_common(dev, पूर्णांकf, data_altsetting, dev->driver_info->data);
	अगर (ret)
		जाओ err;

	ctx = info->ctx;

	/* The MBIM descriptor and the status endpoपूर्णांक are required */
	अगर (ctx->mbim_desc && dev->status)
		subdriver = usb_cdc_wdm_रेजिस्टर(ctx->control,
						 &dev->status->desc,
						 le16_to_cpu(ctx->mbim_desc->wMaxControlMessage),
						 cdc_mbim_wdm_manage_घातer);
	अगर (IS_ERR(subdriver)) अणु
		ret = PTR_ERR(subdriver);
		cdc_ncm_unbind(dev, पूर्णांकf);
		जाओ err;
	पूर्ण

	/* can't let usbnet use the पूर्णांकerrupt endpoपूर्णांक */
	dev->status = शून्य;
	info->subdriver = subdriver;

	/* MBIM cannot करो ARP */
	dev->net->flags |= IFF_NOARP;

	/* no need to put the VLAN tci in the packet headers */
	dev->net->features |= NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_FILTER;

	/* monitor VLAN additions and removals */
	dev->net->netdev_ops = &cdc_mbim_netdev_ops;
err:
	वापस ret;
पूर्ण

अटल व्योम cdc_mbim_unbind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा cdc_mbim_state *info = (व्योम *)&dev->data;
	काष्ठा cdc_ncm_ctx *ctx = info->ctx;

	/* disconnect subdriver from control पूर्णांकerface */
	अगर (info->subdriver && info->subdriver->disconnect)
		info->subdriver->disconnect(ctx->control);
	info->subdriver = शून्य;

	/* let NCM unbind clean up both control and data पूर्णांकerface */
	cdc_ncm_unbind(dev, पूर्णांकf);
पूर्ण

/* verअगरy that the ethernet protocol is IPv4 or IPv6 */
अटल bool is_ip_proto(__be16 proto)
अणु
	चयन (proto) अणु
	हाल htons(ETH_P_IP):
	हाल htons(ETH_P_IPV6):
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल काष्ठा sk_buff *cdc_mbim_tx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb, gfp_t flags)
अणु
	काष्ठा sk_buff *skb_out;
	काष्ठा cdc_mbim_state *info = (व्योम *)&dev->data;
	काष्ठा cdc_ncm_ctx *ctx = info->ctx;
	__le32 sign = cpu_to_le32(USB_CDC_MBIM_NDP16_IPS_SIGN);
	u16 tci = 0;
	bool is_ip;
	u8 *c;

	अगर (!ctx)
		जाओ error;

	अगर (skb) अणु
		अगर (skb->len <= ETH_HLEN)
			जाओ error;

		/* Some applications using e.g. packet sockets will
		 * bypass the VLAN acceleration and create tagged
		 * ethernet frames directly.  We primarily look क्रम
		 * the accelerated out-of-band tag, but fall back अगर
		 * required
		 */
		skb_reset_mac_header(skb);
		अगर (vlan_get_tag(skb, &tci) < 0 && skb->len > VLAN_ETH_HLEN &&
		    __vlan_get_tag(skb, &tci) == 0) अणु
			is_ip = is_ip_proto(vlan_eth_hdr(skb)->h_vlan_encapsulated_proto);
			skb_pull(skb, VLAN_ETH_HLEN);
		पूर्ण अन्यथा अणु
			is_ip = is_ip_proto(eth_hdr(skb)->h_proto);
			skb_pull(skb, ETH_HLEN);
		पूर्ण

		/* Is IP session <0> tagged too? */
		अगर (info->flags & FLAG_IPS0_VLAN) अणु
			/* drop all untagged packets */
			अगर (!tci)
				जाओ error;
			/* map MBIM_IPS0_VID to IPS<0> */
			अगर (tci == MBIM_IPS0_VID)
				tci = 0;
		पूर्ण

		/* mapping VLANs to MBIM sessions:
		 *   no tag     => IPS session <0> अगर !FLAG_IPS0_VLAN
		 *   1 - 255    => IPS session <vlanid>
		 *   256 - 511  => DSS session <vlanid - 256>
		 *   512 - 4093 => unsupported, drop
		 *   4094       => IPS session <0> अगर FLAG_IPS0_VLAN
		 */

		चयन (tci & 0x0f00) अणु
		हाल 0x0000: /* VLAN ID 0 - 255 */
			अगर (!is_ip)
				जाओ error;
			c = (u8 *)&sign;
			c[3] = tci;
			अवरोध;
		हाल 0x0100: /* VLAN ID 256 - 511 */
			अगर (is_ip)
				जाओ error;
			sign = cpu_to_le32(USB_CDC_MBIM_NDP16_DSS_SIGN);
			c = (u8 *)&sign;
			c[3] = tci;
			अवरोध;
		शेष:
			netअगर_err(dev, tx_err, dev->net,
				  "unsupported tci=0x%04x\n", tci);
			जाओ error;
		पूर्ण
	पूर्ण

	spin_lock_bh(&ctx->mtx);
	skb_out = cdc_ncm_fill_tx_frame(dev, skb, sign);
	spin_unlock_bh(&ctx->mtx);
	वापस skb_out;

error:
	अगर (skb)
		dev_kमुक्त_skb_any(skb);

	वापस शून्य;
पूर्ण

/* Some devices are known to send Neigbor Solicitation messages and
 * require Neigbor Advertisement replies.  The IPv6 core will not
 * respond since IFF_NOARP is set, so we must handle them ourselves.
 */
अटल व्योम करो_neigh_solicit(काष्ठा usbnet *dev, u8 *buf, u16 tci)
अणु
	काष्ठा ipv6hdr *iph = (व्योम *)buf;
	काष्ठा nd_msg *msg = (व्योम *)(iph + 1);
	काष्ठा net_device *netdev;
	काष्ठा inet6_dev *in6_dev;
	bool is_router;

	/* we'll only respond to requests from unicast addresses to
	 * our solicited node addresses.
	 */
	अगर (!ipv6_addr_is_solict_mult(&iph->daddr) ||
	    !(ipv6_addr_type(&iph->saddr) & IPV6_ADDR_UNICAST))
		वापस;

	/* need to send the NA on the VLAN dev, अगर any */
	rcu_पढ़ो_lock();
	अगर (tci) अणु
		netdev = __vlan_find_dev_deep_rcu(dev->net, htons(ETH_P_8021Q),
						  tci);
		अगर (!netdev) अणु
			rcu_पढ़ो_unlock();
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		netdev = dev->net;
	पूर्ण
	dev_hold(netdev);
	rcu_पढ़ो_unlock();

	in6_dev = in6_dev_get(netdev);
	अगर (!in6_dev)
		जाओ out;
	is_router = !!in6_dev->cnf.क्रमwarding;
	in6_dev_put(in6_dev);

	/* ipv6_stub != शून्य अगर in6_dev_get वापसed an inet6_dev */
	ipv6_stub->ndisc_send_na(netdev, &iph->saddr, &msg->target,
				 is_router /* router */,
				 true /* solicited */,
				 false /* override */,
				 true /* inc_opt */);
out:
	dev_put(netdev);
पूर्ण

अटल bool is_neigh_solicit(u8 *buf, माप_प्रकार len)
अणु
	काष्ठा ipv6hdr *iph = (व्योम *)buf;
	काष्ठा nd_msg *msg = (व्योम *)(iph + 1);

	वापस (len >= माप(काष्ठा ipv6hdr) + माप(काष्ठा nd_msg) &&
		iph->nexthdr == IPPROTO_ICMPV6 &&
		msg->icmph.icmp6_code == 0 &&
		msg->icmph.icmp6_type == NDISC_NEIGHBOUR_SOLICITATION);
पूर्ण


अटल काष्ठा sk_buff *cdc_mbim_process_dgram(काष्ठा usbnet *dev, u8 *buf, माप_प्रकार len, u16 tci)
अणु
	__be16 proto = htons(ETH_P_802_3);
	काष्ठा sk_buff *skb = शून्य;

	अगर (tci < 256 || tci == MBIM_IPS0_VID) अणु /* IPS session? */
		अगर (len < माप(काष्ठा iphdr))
			जाओ err;

		चयन (*buf & 0xf0) अणु
		हाल 0x40:
			proto = htons(ETH_P_IP);
			अवरोध;
		हाल 0x60:
			अगर (is_neigh_solicit(buf, len))
				करो_neigh_solicit(dev, buf, tci);
			proto = htons(ETH_P_IPV6);
			अवरोध;
		शेष:
			जाओ err;
		पूर्ण
	पूर्ण

	skb = netdev_alloc_skb_ip_align(dev->net,  len + ETH_HLEN);
	अगर (!skb)
		जाओ err;

	/* add an ethernet header */
	skb_put(skb, ETH_HLEN);
	skb_reset_mac_header(skb);
	eth_hdr(skb)->h_proto = proto;
	eth_zero_addr(eth_hdr(skb)->h_source);
	स_नकल(eth_hdr(skb)->h_dest, dev->net->dev_addr, ETH_ALEN);

	/* add datagram */
	skb_put_data(skb, buf, len);

	/* map MBIM session to VLAN */
	अगर (tci)
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), tci);
err:
	वापस skb;
पूर्ण

अटल पूर्णांक cdc_mbim_rx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb_in)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा cdc_mbim_state *info = (व्योम *)&dev->data;
	काष्ठा cdc_ncm_ctx *ctx = info->ctx;
	पूर्णांक len;
	पूर्णांक nframes;
	पूर्णांक x;
	पूर्णांक offset;
	काष्ठा usb_cdc_ncm_ndp16 *ndp16;
	काष्ठा usb_cdc_ncm_dpe16 *dpe16;
	पूर्णांक ndpoffset;
	पूर्णांक loopcount = 50; /* arbitrary max preventing infinite loop */
	u32 payload = 0;
	u8 *c;
	u16 tci;

	ndpoffset = cdc_ncm_rx_verअगरy_nth16(ctx, skb_in);
	अगर (ndpoffset < 0)
		जाओ error;

next_ndp:
	nframes = cdc_ncm_rx_verअगरy_ndp16(skb_in, ndpoffset);
	अगर (nframes < 0)
		जाओ error;

	ndp16 = (काष्ठा usb_cdc_ncm_ndp16 *)(skb_in->data + ndpoffset);

	चयन (ndp16->dwSignature & cpu_to_le32(0x00ffffff)) अणु
	हाल cpu_to_le32(USB_CDC_MBIM_NDP16_IPS_SIGN):
		c = (u8 *)&ndp16->dwSignature;
		tci = c[3];
		/* tag IPS<0> packets too अगर MBIM_IPS0_VID exists */
		अगर (!tci && info->flags & FLAG_IPS0_VLAN)
			tci = MBIM_IPS0_VID;
		अवरोध;
	हाल cpu_to_le32(USB_CDC_MBIM_NDP16_DSS_SIGN):
		c = (u8 *)&ndp16->dwSignature;
		tci = c[3] + 256;
		अवरोध;
	शेष:
		netअगर_dbg(dev, rx_err, dev->net,
			  "unsupported NDP signature <0x%08x>\n",
			  le32_to_cpu(ndp16->dwSignature));
		जाओ err_ndp;

	पूर्ण

	dpe16 = ndp16->dpe16;
	क्रम (x = 0; x < nframes; x++, dpe16++) अणु
		offset = le16_to_cpu(dpe16->wDatagramIndex);
		len = le16_to_cpu(dpe16->wDatagramLength);

		/*
		 * CDC NCM ch. 3.7
		 * All entries after first शून्य entry are to be ignored
		 */
		अगर ((offset == 0) || (len == 0)) अणु
			अगर (!x)
				जाओ err_ndp; /* empty NTB */
			अवरोध;
		पूर्ण

		/* sanity checking */
		अगर (((offset + len) > skb_in->len) || (len > ctx->rx_max)) अणु
			netअगर_dbg(dev, rx_err, dev->net,
				  "invalid frame detected (ignored) offset[%u]=%u, length=%u, skb=%p\n",
				  x, offset, len, skb_in);
			अगर (!x)
				जाओ err_ndp;
			अवरोध;
		पूर्ण अन्यथा अणु
			skb = cdc_mbim_process_dgram(dev, skb_in->data + offset, len, tci);
			अगर (!skb)
				जाओ error;
			usbnet_skb_वापस(dev, skb);
			payload += len;	/* count payload bytes in this NTB */
		पूर्ण
	पूर्ण
err_ndp:
	/* are there more NDPs to process? */
	ndpoffset = le16_to_cpu(ndp16->wNextNdpIndex);
	अगर (ndpoffset && loopcount--)
		जाओ next_ndp;

	/* update stats */
	ctx->rx_overhead += skb_in->len - payload;
	ctx->rx_ntbs++;

	वापस 1;
error:
	वापस 0;
पूर्ण

अटल पूर्णांक cdc_mbim_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	पूर्णांक ret = -ENODEV;
	काष्ठा usbnet *dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा cdc_mbim_state *info = (व्योम *)&dev->data;
	काष्ठा cdc_ncm_ctx *ctx = info->ctx;

	अगर (!ctx)
		जाओ error;

	/*
	 * Both usbnet_suspend() and subdriver->suspend() MUST वापस 0
	 * in प्रणाली sleep context, otherwise, the resume callback has
	 * to recover device from previous suspend failure.
	 */
	ret = usbnet_suspend(पूर्णांकf, message);
	अगर (ret < 0)
		जाओ error;

	अगर (पूर्णांकf == ctx->control && info->subdriver && info->subdriver->suspend)
		ret = info->subdriver->suspend(पूर्णांकf, message);
	अगर (ret < 0)
		usbnet_resume(पूर्णांकf);

error:
	वापस ret;
पूर्ण

अटल पूर्णांक cdc_mbim_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	पूर्णांक  ret = 0;
	काष्ठा usbnet *dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा cdc_mbim_state *info = (व्योम *)&dev->data;
	काष्ठा cdc_ncm_ctx *ctx = info->ctx;
	bool callsub = (पूर्णांकf == ctx->control && info->subdriver && info->subdriver->resume);

	अगर (callsub)
		ret = info->subdriver->resume(पूर्णांकf);
	अगर (ret < 0)
		जाओ err;
	ret = usbnet_resume(पूर्णांकf);
	अगर (ret < 0 && callsub)
		info->subdriver->suspend(पूर्णांकf, PMSG_SUSPEND);
err:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा driver_info cdc_mbim_info = अणु
	.description = "CDC MBIM",
	.flags = FLAG_NO_SETINT | FLAG_MULTI_PACKET | FLAG_WWAN,
	.bind = cdc_mbim_bind,
	.unbind = cdc_mbim_unbind,
	.manage_घातer = cdc_mbim_manage_घातer,
	.rx_fixup = cdc_mbim_rx_fixup,
	.tx_fixup = cdc_mbim_tx_fixup,
पूर्ण;

/* MBIM and NCM devices should not need a ZLP after NTBs with
 * dwNtbOutMaxSize length. Nevertheless, a number of devices from
 * dअगरferent venकरोr IDs will fail unless we send ZLPs, क्रमcing us
 * to make this the शेष.
 *
 * This शेष may cause a perक्रमmance penalty क्रम spec conक्रमming
 * devices wanting to take advantage of optimizations possible without
 * ZLPs.  A whitelist is added in an attempt to aव्योम this क्रम devices
 * known to conक्रमm to the MBIM specअगरication.
 *
 * All known devices supporting NCM compatibility mode are also
 * conक्रमming to the NCM and MBIM specअगरications. For this reason, the
 * NCM subclass entry is also in the ZLP whitelist.
 */
अटल स्थिर काष्ठा driver_info cdc_mbim_info_zlp = अणु
	.description = "CDC MBIM",
	.flags = FLAG_NO_SETINT | FLAG_MULTI_PACKET | FLAG_WWAN | FLAG_SEND_ZLP,
	.bind = cdc_mbim_bind,
	.unbind = cdc_mbim_unbind,
	.manage_घातer = cdc_mbim_manage_घातer,
	.rx_fixup = cdc_mbim_rx_fixup,
	.tx_fixup = cdc_mbim_tx_fixup,
पूर्ण;

/* The spefication explicitly allows NDPs to be placed anywhere in the
 * frame, but some devices fail unless the NDP is placed after the IP
 * packets.  Using the CDC_NCM_FLAG_NDP_TO_END flags to क्रमce this
 * behaviour.
 *
 * Note: The current implementation of this feature restricts each NTB
 * to a single NDP, implying that multiplexed sessions cannot share an
 * NTB. This might affect perक्रमmace क्रम multiplexed sessions.
 */
अटल स्थिर काष्ठा driver_info cdc_mbim_info_ndp_to_end = अणु
	.description = "CDC MBIM",
	.flags = FLAG_NO_SETINT | FLAG_MULTI_PACKET | FLAG_WWAN,
	.bind = cdc_mbim_bind,
	.unbind = cdc_mbim_unbind,
	.manage_घातer = cdc_mbim_manage_घातer,
	.rx_fixup = cdc_mbim_rx_fixup,
	.tx_fixup = cdc_mbim_tx_fixup,
	.data = CDC_NCM_FLAG_NDP_TO_END,
पूर्ण;

/* Some modems (e.g. Telit LE922A6) करो not work properly with altsetting
 * toggle करोne in cdc_ncm_bind_common. CDC_MBIM_FLAG_AVOID_ALTSETTING_TOGGLE
 * flag is used to aव्योम this procedure.
 */
अटल स्थिर काष्ठा driver_info cdc_mbim_info_aव्योम_altsetting_toggle = अणु
	.description = "CDC MBIM",
	.flags = FLAG_NO_SETINT | FLAG_MULTI_PACKET | FLAG_WWAN | FLAG_SEND_ZLP,
	.bind = cdc_mbim_bind,
	.unbind = cdc_mbim_unbind,
	.manage_घातer = cdc_mbim_manage_घातer,
	.rx_fixup = cdc_mbim_rx_fixup,
	.tx_fixup = cdc_mbim_tx_fixup,
	.data = CDC_MBIM_FLAG_AVOID_ALTSETTING_TOGGLE,
पूर्ण;

अटल स्थिर काष्ठा usb_device_id mbim_devs[] = अणु
	/* This duplicate NCM entry is पूर्णांकentional. MBIM devices can
	 * be disguised as NCM by शेष, and this is necessary to
	 * allow us to bind the correct driver_info to such devices.
	 *
	 * bind() will sort out this क्रम us, selecting the correct
	 * entry and reject the other
	 */
	अणु USB_INTERFACE_INFO(USB_CLASS_COMM, USB_CDC_SUBCLASS_NCM, USB_CDC_PROTO_NONE),
	  .driver_info = (अचिन्हित दीर्घ)&cdc_mbim_info,
	पूर्ण,
	/* ZLP conक्रमmance whitelist: All Ericsson MBIM devices */
	अणु USB_VENDOR_AND_INTERFACE_INFO(0x0bdb, USB_CLASS_COMM, USB_CDC_SUBCLASS_MBIM, USB_CDC_PROTO_NONE),
	  .driver_info = (अचिन्हित दीर्घ)&cdc_mbim_info,
	पूर्ण,

	/* Some Huawei devices, ME906s-158 (12d1:15c1) and E3372
	 * (12d1:157d), are known to fail unless the NDP is placed
	 * after the IP packets.  Applying the quirk to all Huawei
	 * devices is broader than necessary, but harmless.
	 */
	अणु USB_VENDOR_AND_INTERFACE_INFO(0x12d1, USB_CLASS_COMM, USB_CDC_SUBCLASS_MBIM, USB_CDC_PROTO_NONE),
	  .driver_info = (अचिन्हित दीर्घ)&cdc_mbim_info_ndp_to_end,
	पूर्ण,

	/* The HP lt4132 (03f0:a31d) is a rebअक्रमed Huawei ME906s-158,
	 * thereक्रमe it too requires the above "NDP to end" quirk.
	 */
	अणु USB_DEVICE_AND_INTERFACE_INFO(0x03f0, 0xa31d, USB_CLASS_COMM, USB_CDC_SUBCLASS_MBIM, USB_CDC_PROTO_NONE),
	  .driver_info = (अचिन्हित दीर्घ)&cdc_mbim_info_ndp_to_end,
	पूर्ण,

	/* Telit LE922A6 in MBIM composition */
	अणु USB_DEVICE_AND_INTERFACE_INFO(0x1bc7, 0x1041, USB_CLASS_COMM, USB_CDC_SUBCLASS_MBIM, USB_CDC_PROTO_NONE),
	  .driver_info = (अचिन्हित दीर्घ)&cdc_mbim_info_aव्योम_altsetting_toggle,
	पूर्ण,

	/* शेष entry */
	अणु USB_INTERFACE_INFO(USB_CLASS_COMM, USB_CDC_SUBCLASS_MBIM, USB_CDC_PROTO_NONE),
	  .driver_info = (अचिन्हित दीर्घ)&cdc_mbim_info_zlp,
	पूर्ण,
	अणु
	पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(usb, mbim_devs);

अटल काष्ठा usb_driver cdc_mbim_driver = अणु
	.name = "cdc_mbim",
	.id_table = mbim_devs,
	.probe = usbnet_probe,
	.disconnect = usbnet_disconnect,
	.suspend = cdc_mbim_suspend,
	.resume = cdc_mbim_resume,
	.reset_resume =	cdc_mbim_resume,
	.supports_स्वतःsuspend = 1,
	.disable_hub_initiated_lpm = 1,
पूर्ण;
module_usb_driver(cdc_mbim_driver);

MODULE_AUTHOR("Greg Suarez <gsuarez@smithmicro.com>");
MODULE_AUTHOR("Bjथचrn Mork <bjorn@mork.no>");
MODULE_DESCRIPTION("USB CDC MBIM host driver");
MODULE_LICENSE("GPL");
