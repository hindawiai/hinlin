<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012  Bjथचrn Mork <bjorn@mork.no>
 *
 * The probing code is heavily inspired by cdc_ether, which is:
 * Copyright (C) 2003-2005 by David Brownell
 * Copyright (C) 2006 by Ole Andre Vadla Ravnas (ActiveSync)
 */

#समावेश <linux/module.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/mii.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/cdc.h>
#समावेश <linux/usb/usbnet.h>
#समावेश <linux/usb/cdc-wdm.h>
#समावेश <linux/u64_stats_sync.h>

/* This driver supports wwan (3G/LTE/?) devices using a venकरोr
 * specअगरic management protocol called Qualcomm MSM Interface (QMI) -
 * in addition to the more common AT commands over serial पूर्णांकerface
 * management
 *
 * QMI is wrapped in CDC, using CDC encapsulated commands on the
 * control ("master") पूर्णांकerface of a two-पूर्णांकerface CDC Union
 * resembling standard CDC ECM.  The devices करो not use the control
 * पूर्णांकerface क्रम any other CDC messages.  Most likely because the
 * management protocol is used in place of the standard CDC
 * notअगरications NOTIFY_NETWORK_CONNECTION and NOTIFY_SPEED_CHANGE
 *
 * Alternatively, control and data functions can be combined in a
 * single USB पूर्णांकerface.
 *
 * Handling a protocol like QMI is out of the scope क्रम any driver.
 * It is exported as a अक्षरacter device using the cdc-wdm driver as
 * a subdriver, enabling userspace applications ("modem managers") to
 * handle it.
 *
 * These devices may alternatively/additionally be configured using AT
 * commands on a serial पूर्णांकerface
 */

/* driver specअगरic data */
काष्ठा qmi_wwan_state अणु
	काष्ठा usb_driver *subdriver;
	atomic_t pmcount;
	अचिन्हित दीर्घ flags;
	काष्ठा usb_पूर्णांकerface *control;
	काष्ठा usb_पूर्णांकerface *data;
पूर्ण;

क्रमागत qmi_wwan_flags अणु
	QMI_WWAN_FLAG_RAWIP = 1 << 0,
	QMI_WWAN_FLAG_MUX = 1 << 1,
	QMI_WWAN_FLAG_PASS_THROUGH = 1 << 2,
पूर्ण;

क्रमागत qmi_wwan_quirks अणु
	QMI_WWAN_QUIRK_DTR = 1 << 0,	/* needs "set DTR" request */
पूर्ण;

काष्ठा qmimux_hdr अणु
	u8 pad;
	u8 mux_id;
	__be16 pkt_len;
पूर्ण;

काष्ठा qmimux_priv अणु
	काष्ठा net_device *real_dev;
	u8 mux_id;
पूर्ण;

अटल पूर्णांक qmimux_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा qmimux_priv *priv = netdev_priv(dev);
	काष्ठा net_device *real_dev = priv->real_dev;

	अगर (!(priv->real_dev->flags & IFF_UP))
		वापस -ENETDOWN;

	अगर (netअगर_carrier_ok(real_dev))
		netअगर_carrier_on(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक qmimux_stop(काष्ठा net_device *dev)
अणु
	netअगर_carrier_off(dev);
	वापस 0;
पूर्ण

अटल netdev_tx_t qmimux_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा qmimux_priv *priv = netdev_priv(dev);
	अचिन्हित पूर्णांक len = skb->len;
	काष्ठा qmimux_hdr *hdr;
	netdev_tx_t ret;

	hdr = skb_push(skb, माप(काष्ठा qmimux_hdr));
	hdr->pad = 0;
	hdr->mux_id = priv->mux_id;
	hdr->pkt_len = cpu_to_be16(len);
	skb->dev = priv->real_dev;
	ret = dev_queue_xmit(skb);

	अगर (likely(ret == NET_XMIT_SUCCESS || ret == NET_XMIT_CN))
		dev_sw_netstats_tx_add(dev, 1, len);
	अन्यथा
		dev->stats.tx_dropped++;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा net_device_ops qmimux_netdev_ops = अणु
	.nकरो_खोलो        = qmimux_खोलो,
	.nकरो_stop        = qmimux_stop,
	.nकरो_start_xmit  = qmimux_start_xmit,
	.nकरो_get_stats64 = dev_get_tstats64,
पूर्ण;

अटल व्योम qmimux_setup(काष्ठा net_device *dev)
अणु
	dev->header_ops      = शून्य;  /* No header */
	dev->type            = ARPHRD_NONE;
	dev->hard_header_len = 0;
	dev->addr_len        = 0;
	dev->flags           = IFF_POINTOPOINT | IFF_NOARP | IFF_MULTICAST;
	dev->netdev_ops      = &qmimux_netdev_ops;
	dev->mtu             = 1500;
	dev->needs_मुक्त_netdev = true;
पूर्ण

अटल काष्ठा net_device *qmimux_find_dev(काष्ठा usbnet *dev, u8 mux_id)
अणु
	काष्ठा qmimux_priv *priv;
	काष्ठा list_head *iter;
	काष्ठा net_device *ldev;

	rcu_पढ़ो_lock();
	netdev_क्रम_each_upper_dev_rcu(dev->net, ldev, iter) अणु
		priv = netdev_priv(ldev);
		अगर (priv->mux_id == mux_id) अणु
			rcu_पढ़ो_unlock();
			वापस ldev;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस शून्य;
पूर्ण

अटल bool qmimux_has_slaves(काष्ठा usbnet *dev)
अणु
	वापस !list_empty(&dev->net->adj_list.upper);
पूर्ण

अटल पूर्णांक qmimux_rx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक len, offset = 0, pad_len, pkt_len;
	काष्ठा qmimux_hdr *hdr;
	काष्ठा net_device *net;
	काष्ठा sk_buff *skbn;
	u8 qmimux_hdr_sz = माप(*hdr);

	जबतक (offset + qmimux_hdr_sz < skb->len) अणु
		hdr = (काष्ठा qmimux_hdr *)(skb->data + offset);
		len = be16_to_cpu(hdr->pkt_len);

		/* drop the packet, bogus length */
		अगर (offset + len + qmimux_hdr_sz > skb->len)
			वापस 0;

		/* control packet, we करो not know what to करो */
		अगर (hdr->pad & 0x80)
			जाओ skip;

		/* extract padding length and check क्रम valid length info */
		pad_len = hdr->pad & 0x3f;
		अगर (len == 0 || pad_len >= len)
			जाओ skip;
		pkt_len = len - pad_len;

		net = qmimux_find_dev(dev, hdr->mux_id);
		अगर (!net)
			जाओ skip;
		skbn = netdev_alloc_skb(net, pkt_len + LL_MAX_HEADER);
		अगर (!skbn)
			वापस 0;
		skbn->dev = net;

		चयन (skb->data[offset + qmimux_hdr_sz] & 0xf0) अणु
		हाल 0x40:
			skbn->protocol = htons(ETH_P_IP);
			अवरोध;
		हाल 0x60:
			skbn->protocol = htons(ETH_P_IPV6);
			अवरोध;
		शेष:
			/* not ip - करो not know what to करो */
			जाओ skip;
		पूर्ण

		skb_reserve(skbn, LL_MAX_HEADER);
		skb_put_data(skbn, skb->data + offset + qmimux_hdr_sz, pkt_len);
		अगर (netअगर_rx(skbn) != NET_RX_SUCCESS) अणु
			net->stats.rx_errors++;
			वापस 0;
		पूर्ण अन्यथा अणु
			dev_sw_netstats_rx_add(net, pkt_len);
		पूर्ण

skip:
		offset += len + qmimux_hdr_sz;
	पूर्ण
	वापस 1;
पूर्ण

अटल sमाप_प्रकार mux_id_show(काष्ठा device *d, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा net_device *dev = to_net_dev(d);
	काष्ठा qmimux_priv *priv;

	priv = netdev_priv(dev);

	वापस sysfs_emit(buf, "0x%02x\n", priv->mux_id);
पूर्ण

अटल DEVICE_ATTR_RO(mux_id);

अटल काष्ठा attribute *qmi_wwan_sysfs_qmimux_attrs[] = अणु
	&dev_attr_mux_id.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group qmi_wwan_sysfs_qmimux_attr_group = अणु
	.name = "qmap",
	.attrs = qmi_wwan_sysfs_qmimux_attrs,
पूर्ण;

अटल पूर्णांक qmimux_रेजिस्टर_device(काष्ठा net_device *real_dev, u8 mux_id)
अणु
	काष्ठा net_device *new_dev;
	काष्ठा qmimux_priv *priv;
	पूर्णांक err;

	new_dev = alloc_netdev(माप(काष्ठा qmimux_priv),
			       "qmimux%d", NET_NAME_UNKNOWN, qmimux_setup);
	अगर (!new_dev)
		वापस -ENOBUFS;

	dev_net_set(new_dev, dev_net(real_dev));
	priv = netdev_priv(new_dev);
	priv->mux_id = mux_id;
	priv->real_dev = real_dev;

	new_dev->tstats = netdev_alloc_pcpu_stats(काष्ठा pcpu_sw_netstats);
	अगर (!new_dev->tstats) अणु
		err = -ENOBUFS;
		जाओ out_मुक्त_newdev;
	पूर्ण

	new_dev->sysfs_groups[0] = &qmi_wwan_sysfs_qmimux_attr_group;

	err = रेजिस्टर_netdevice(new_dev);
	अगर (err < 0)
		जाओ out_मुक्त_newdev;

	/* Account क्रम reference in काष्ठा qmimux_priv_priv */
	dev_hold(real_dev);

	err = netdev_upper_dev_link(real_dev, new_dev, शून्य);
	अगर (err)
		जाओ out_unरेजिस्टर_netdev;

	netअगर_stacked_transfer_operstate(real_dev, new_dev);

	वापस 0;

out_unरेजिस्टर_netdev:
	unरेजिस्टर_netdevice(new_dev);
	dev_put(real_dev);

out_मुक्त_newdev:
	मुक्त_netdev(new_dev);
	वापस err;
पूर्ण

अटल व्योम qmimux_unरेजिस्टर_device(काष्ठा net_device *dev,
				     काष्ठा list_head *head)
अणु
	काष्ठा qmimux_priv *priv = netdev_priv(dev);
	काष्ठा net_device *real_dev = priv->real_dev;

	मुक्त_percpu(dev->tstats);
	netdev_upper_dev_unlink(real_dev, dev);
	unरेजिस्टर_netdevice_queue(dev, head);

	/* Get rid of the reference to real_dev */
	dev_put(real_dev);
पूर्ण

अटल व्योम qmi_wwan_netdev_setup(काष्ठा net_device *net)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	काष्ठा qmi_wwan_state *info = (व्योम *)&dev->data;

	अगर (info->flags & QMI_WWAN_FLAG_RAWIP) अणु
		net->header_ops      = शून्य;  /* No header */
		net->type            = ARPHRD_NONE;
		net->hard_header_len = 0;
		net->addr_len        = 0;
		net->flags           = IFF_POINTOPOINT | IFF_NOARP | IFF_MULTICAST;
		set_bit(EVENT_NO_IP_ALIGN, &dev->flags);
		netdev_dbg(net, "mode: raw IP\n");
	पूर्ण अन्यथा अगर (!net->header_ops) अणु /* करोn't bother अगर alपढ़ोy set */
		ether_setup(net);
		/* Restoring min/max mtu values set originally by usbnet */
		net->min_mtu = 0;
		net->max_mtu = ETH_MAX_MTU;
		clear_bit(EVENT_NO_IP_ALIGN, &dev->flags);
		netdev_dbg(net, "mode: Ethernet\n");
	पूर्ण

	/* recalculate buffers after changing hard_header_len */
	usbnet_change_mtu(net, net->mtu);
पूर्ण

अटल sमाप_प्रकार raw_ip_show(काष्ठा device *d, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usbnet *dev = netdev_priv(to_net_dev(d));
	काष्ठा qmi_wwan_state *info = (व्योम *)&dev->data;

	वापस प्र_लिखो(buf, "%c\n", info->flags & QMI_WWAN_FLAG_RAWIP ? 'Y' : 'N');
पूर्ण

अटल sमाप_प्रकार raw_ip_store(काष्ठा device *d,  काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा usbnet *dev = netdev_priv(to_net_dev(d));
	काष्ठा qmi_wwan_state *info = (व्योम *)&dev->data;
	bool enable;
	पूर्णांक ret;

	अगर (strtobool(buf, &enable))
		वापस -EINVAL;

	/* no change? */
	अगर (enable == (info->flags & QMI_WWAN_FLAG_RAWIP))
		वापस len;

	/* ip mode cannot be cleared when pass through mode is set */
	अगर (!enable && (info->flags & QMI_WWAN_FLAG_PASS_THROUGH)) अणु
		netdev_err(dev->net,
			   "Cannot clear ip mode on pass through device\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!rtnl_trylock())
		वापस restart_syscall();

	/* we करोn't want to modअगरy a running netdev */
	अगर (netअगर_running(dev->net)) अणु
		netdev_err(dev->net, "Cannot change a running device\n");
		ret = -EBUSY;
		जाओ err;
	पूर्ण

	/* let other drivers deny the change */
	ret = call_netdevice_notअगरiers(NETDEV_PRE_TYPE_CHANGE, dev->net);
	ret = notअगरier_to_त्रुटि_सं(ret);
	अगर (ret) अणु
		netdev_err(dev->net, "Type change was refused\n");
		जाओ err;
	पूर्ण

	अगर (enable)
		info->flags |= QMI_WWAN_FLAG_RAWIP;
	अन्यथा
		info->flags &= ~QMI_WWAN_FLAG_RAWIP;
	qmi_wwan_netdev_setup(dev->net);
	call_netdevice_notअगरiers(NETDEV_POST_TYPE_CHANGE, dev->net);
	ret = len;
err:
	rtnl_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार add_mux_show(काष्ठा device *d, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा net_device *dev = to_net_dev(d);
	काष्ठा qmimux_priv *priv;
	काष्ठा list_head *iter;
	काष्ठा net_device *ldev;
	sमाप_प्रकार count = 0;

	rcu_पढ़ो_lock();
	netdev_क्रम_each_upper_dev_rcu(dev, ldev, iter) अणु
		priv = netdev_priv(ldev);
		count += scnम_लिखो(&buf[count], PAGE_SIZE - count,
				   "0x%02x\n", priv->mux_id);
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस count;
पूर्ण

अटल sमाप_प्रकार add_mux_store(काष्ठा device *d,  काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा usbnet *dev = netdev_priv(to_net_dev(d));
	काष्ठा qmi_wwan_state *info = (व्योम *)&dev->data;
	u8 mux_id;
	पूर्णांक ret;

	अगर (kstrtou8(buf, 0, &mux_id))
		वापस -EINVAL;

	/* mux_id [1 - 254] क्रम compatibility with ip(8) and the rmnet driver */
	अगर (mux_id < 1 || mux_id > 254)
		वापस -EINVAL;

	अगर (!rtnl_trylock())
		वापस restart_syscall();

	अगर (qmimux_find_dev(dev, mux_id)) अणु
		netdev_err(dev->net, "mux_id already present\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	ret = qmimux_रेजिस्टर_device(dev->net, mux_id);
	अगर (!ret) अणु
		info->flags |= QMI_WWAN_FLAG_MUX;
		ret = len;
	पूर्ण
err:
	rtnl_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार del_mux_show(काष्ठा device *d, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस add_mux_show(d, attr, buf);
पूर्ण

अटल sमाप_प्रकार del_mux_store(काष्ठा device *d,  काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा usbnet *dev = netdev_priv(to_net_dev(d));
	काष्ठा qmi_wwan_state *info = (व्योम *)&dev->data;
	काष्ठा net_device *del_dev;
	u8 mux_id;
	पूर्णांक ret = 0;

	अगर (kstrtou8(buf, 0, &mux_id))
		वापस -EINVAL;

	अगर (!rtnl_trylock())
		वापस restart_syscall();

	del_dev = qmimux_find_dev(dev, mux_id);
	अगर (!del_dev) अणु
		netdev_err(dev->net, "mux_id not present\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण
	qmimux_unरेजिस्टर_device(del_dev, शून्य);

	अगर (!qmimux_has_slaves(dev))
		info->flags &= ~QMI_WWAN_FLAG_MUX;
	ret = len;
err:
	rtnl_unlock();
	वापस ret;
पूर्ण

अटल sमाप_प्रकार pass_through_show(काष्ठा device *d,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usbnet *dev = netdev_priv(to_net_dev(d));
	काष्ठा qmi_wwan_state *info;

	info = (व्योम *)&dev->data;
	वापस प्र_लिखो(buf, "%c\n",
		       info->flags & QMI_WWAN_FLAG_PASS_THROUGH ? 'Y' : 'N');
पूर्ण

अटल sमाप_प्रकार pass_through_store(काष्ठा device *d,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा usbnet *dev = netdev_priv(to_net_dev(d));
	काष्ठा qmi_wwan_state *info;
	bool enable;

	अगर (strtobool(buf, &enable))
		वापस -EINVAL;

	info = (व्योम *)&dev->data;

	/* no change? */
	अगर (enable == (info->flags & QMI_WWAN_FLAG_PASS_THROUGH))
		वापस len;

	/* pass through mode can be set क्रम raw ip devices only */
	अगर (!(info->flags & QMI_WWAN_FLAG_RAWIP)) अणु
		netdev_err(dev->net,
			   "Cannot set pass through mode on non ip device\n");
		वापस -EINVAL;
	पूर्ण

	अगर (enable)
		info->flags |= QMI_WWAN_FLAG_PASS_THROUGH;
	अन्यथा
		info->flags &= ~QMI_WWAN_FLAG_PASS_THROUGH;

	वापस len;
पूर्ण

अटल DEVICE_ATTR_RW(raw_ip);
अटल DEVICE_ATTR_RW(add_mux);
अटल DEVICE_ATTR_RW(del_mux);
अटल DEVICE_ATTR_RW(pass_through);

अटल काष्ठा attribute *qmi_wwan_sysfs_attrs[] = अणु
	&dev_attr_raw_ip.attr,
	&dev_attr_add_mux.attr,
	&dev_attr_del_mux.attr,
	&dev_attr_pass_through.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group qmi_wwan_sysfs_attr_group = अणु
	.name = "qmi",
	.attrs = qmi_wwan_sysfs_attrs,
पूर्ण;

/* शेष ethernet address used by the modem */
अटल स्थिर u8 शेष_modem_addr[ETH_ALEN] = अणु0x02, 0x50, 0xf3पूर्ण;

अटल स्थिर u8 buggy_fw_addr[ETH_ALEN] = अणु0x00, 0xa0, 0xc6, 0x00, 0x00, 0x00पूर्ण;

/* Make up an ethernet header अगर the packet करोesn't have one.
 *
 * A firmware bug common among several devices cause them to send raw
 * IP packets under some circumstances.  There is no way क्रम the
 * driver/host to know when this will happen.  And even when the bug
 * hits, some packets will still arrive with an पूर्णांकact header.
 *
 * The supported devices are only capably of sending IPv4, IPv6 and
 * ARP packets on a poपूर्णांक-to-poपूर्णांक link. Any packet with an ethernet
 * header will have either our address or a broadcast/multicast
 * address as destination.  ARP packets will always have a header.
 *
 * This means that this function will reliably add the appropriate
 * header अगरf necessary, provided our hardware address करोes not start
 * with 4 or 6.
 *
 * Another common firmware bug results in all packets being addressed
 * to 00:a0:c6:00:00:00 despite the host address being dअगरferent.
 * This function will also fixup such packets.
 */
अटल पूर्णांक qmi_wwan_rx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा qmi_wwan_state *info = (व्योम *)&dev->data;
	bool rawip = info->flags & QMI_WWAN_FLAG_RAWIP;
	__be16 proto;

	/* This check is no दीर्घer करोne by usbnet */
	अगर (skb->len < dev->net->hard_header_len)
		वापस 0;

	अगर (info->flags & QMI_WWAN_FLAG_MUX)
		वापस qmimux_rx_fixup(dev, skb);

	अगर (info->flags & QMI_WWAN_FLAG_PASS_THROUGH) अणु
		skb->protocol = htons(ETH_P_MAP);
		वापस 1;
	पूर्ण

	चयन (skb->data[0] & 0xf0) अणु
	हाल 0x40:
		proto = htons(ETH_P_IP);
		अवरोध;
	हाल 0x60:
		proto = htons(ETH_P_IPV6);
		अवरोध;
	हाल 0x00:
		अगर (rawip)
			वापस 0;
		अगर (is_multicast_ether_addr(skb->data))
			वापस 1;
		/* possibly bogus destination - reग_लिखो just in हाल */
		skb_reset_mac_header(skb);
		जाओ fix_dest;
	शेष:
		अगर (rawip)
			वापस 0;
		/* pass aदीर्घ other packets without modअगरications */
		वापस 1;
	पूर्ण
	अगर (rawip) अणु
		skb_reset_mac_header(skb);
		skb->dev = dev->net; /* normally set by eth_type_trans */
		skb->protocol = proto;
		वापस 1;
	पूर्ण

	अगर (skb_headroom(skb) < ETH_HLEN)
		वापस 0;
	skb_push(skb, ETH_HLEN);
	skb_reset_mac_header(skb);
	eth_hdr(skb)->h_proto = proto;
	eth_zero_addr(eth_hdr(skb)->h_source);
fix_dest:
	स_नकल(eth_hdr(skb)->h_dest, dev->net->dev_addr, ETH_ALEN);
	वापस 1;
पूर्ण

/* very simplistic detection of IPv4 or IPv6 headers */
अटल bool possibly_iphdr(स्थिर अक्षर *data)
अणु
	वापस (data[0] & 0xd0) == 0x40;
पूर्ण

/* disallow addresses which may be confused with IP headers */
अटल पूर्णांक qmi_wwan_mac_addr(काष्ठा net_device *dev, व्योम *p)
अणु
	पूर्णांक ret;
	काष्ठा sockaddr *addr = p;

	ret = eth_prepare_mac_addr_change(dev, p);
	अगर (ret < 0)
		वापस ret;
	अगर (possibly_iphdr(addr->sa_data))
		वापस -EADDRNOTAVAIL;
	eth_commit_mac_addr_change(dev, p);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops qmi_wwan_netdev_ops = अणु
	.nकरो_खोलो		= usbnet_खोलो,
	.nकरो_stop		= usbnet_stop,
	.nकरो_start_xmit		= usbnet_start_xmit,
	.nकरो_tx_समयout		= usbnet_tx_समयout,
	.nकरो_change_mtu		= usbnet_change_mtu,
	.nकरो_get_stats64	= dev_get_tstats64,
	.nकरो_set_mac_address	= qmi_wwan_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

/* using a counter to merge subdriver requests with our own पूर्णांकo a
 * combined state
 */
अटल पूर्णांक qmi_wwan_manage_घातer(काष्ठा usbnet *dev, पूर्णांक on)
अणु
	काष्ठा qmi_wwan_state *info = (व्योम *)&dev->data;
	पूर्णांक rv;

	dev_dbg(&dev->पूर्णांकf->dev, "%s() pmcount=%d, on=%d\n", __func__,
		atomic_पढ़ो(&info->pmcount), on);

	अगर ((on && atomic_add_वापस(1, &info->pmcount) == 1) ||
	    (!on && atomic_dec_and_test(&info->pmcount))) अणु
		/* need स्वतःpm_get/put here to ensure the usbcore sees
		 * the new value
		 */
		rv = usb_स्वतःpm_get_पूर्णांकerface(dev->पूर्णांकf);
		dev->पूर्णांकf->needs_remote_wakeup = on;
		अगर (!rv)
			usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकf);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qmi_wwan_cdc_wdm_manage_घातer(काष्ठा usb_पूर्णांकerface *पूर्णांकf, पूर्णांक on)
अणु
	काष्ठा usbnet *dev = usb_get_पूर्णांकfdata(पूर्णांकf);

	/* can be called जबतक disconnecting */
	अगर (!dev)
		वापस 0;
	वापस qmi_wwan_manage_घातer(dev, on);
पूर्ण

/* collect all three endpoपूर्णांकs and रेजिस्टर subdriver */
अटल पूर्णांक qmi_wwan_रेजिस्टर_subdriver(काष्ठा usbnet *dev)
अणु
	पूर्णांक rv;
	काष्ठा usb_driver *subdriver = शून्य;
	काष्ठा qmi_wwan_state *info = (व्योम *)&dev->data;

	/* collect bulk endpoपूर्णांकs */
	rv = usbnet_get_endpoपूर्णांकs(dev, info->data);
	अगर (rv < 0)
		जाओ err;

	/* update status endpoपूर्णांक अगर separate control पूर्णांकerface */
	अगर (info->control != info->data)
		dev->status = &info->control->cur_altsetting->endpoपूर्णांक[0];

	/* require पूर्णांकerrupt endpoपूर्णांक क्रम subdriver */
	अगर (!dev->status) अणु
		rv = -EINVAL;
		जाओ err;
	पूर्ण

	/* क्रम subdriver घातer management */
	atomic_set(&info->pmcount, 0);

	/* रेजिस्टर subdriver */
	subdriver = usb_cdc_wdm_रेजिस्टर(info->control, &dev->status->desc,
					 4096, &qmi_wwan_cdc_wdm_manage_घातer);
	अगर (IS_ERR(subdriver)) अणु
		dev_err(&info->control->dev, "subdriver registration failed\n");
		rv = PTR_ERR(subdriver);
		जाओ err;
	पूर्ण

	/* prevent usbnet from using status endpoपूर्णांक */
	dev->status = शून्य;

	/* save subdriver काष्ठा क्रम suspend/resume wrappers */
	info->subdriver = subdriver;

err:
	वापस rv;
पूर्ण

/* Send CDC SetControlLineState request, setting or clearing the DTR.
 * "Required for Autoconnect and 9x30 to wake up" according to the
 * GobiNet driver. The requirement has been verअगरied on an MDM9230
 * based Sierra Wireless MC7455
 */
अटल पूर्णांक qmi_wwan_change_dtr(काष्ठा usbnet *dev, bool on)
अणु
	u8 पूर्णांकf = dev->पूर्णांकf->cur_altsetting->desc.bInterfaceNumber;

	वापस usbnet_ग_लिखो_cmd(dev, USB_CDC_REQ_SET_CONTROL_LINE_STATE,
				USB_सूची_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
				on ? 0x01 : 0x00, पूर्णांकf, शून्य, 0);
पूर्ण

अटल पूर्णांक qmi_wwan_bind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	पूर्णांक status;
	u8 *buf = पूर्णांकf->cur_altsetting->extra;
	पूर्णांक len = पूर्णांकf->cur_altsetting->extralen;
	काष्ठा usb_पूर्णांकerface_descriptor *desc = &पूर्णांकf->cur_altsetting->desc;
	काष्ठा usb_cdc_जोड़_desc *cdc_जोड़;
	काष्ठा usb_cdc_ether_desc *cdc_ether;
	काष्ठा usb_driver *driver = driver_of(पूर्णांकf);
	काष्ठा qmi_wwan_state *info = (व्योम *)&dev->data;
	काष्ठा usb_cdc_parsed_header hdr;

	BUILD_BUG_ON((माप(((काष्ठा usbnet *)0)->data) <
		      माप(काष्ठा qmi_wwan_state)));

	/* set up initial state */
	info->control = पूर्णांकf;
	info->data = पूर्णांकf;

	/* and a number of CDC descriptors */
	cdc_parse_cdc_header(&hdr, पूर्णांकf, buf, len);
	cdc_जोड़ = hdr.usb_cdc_जोड़_desc;
	cdc_ether = hdr.usb_cdc_ether_desc;

	/* Use separate control and data पूर्णांकerfaces अगर we found a CDC Union */
	अगर (cdc_जोड़) अणु
		info->data = usb_अगरnum_to_अगर(dev->udev,
					     cdc_जोड़->bSlaveInterface0);
		अगर (desc->bInterfaceNumber != cdc_जोड़->bMasterInterface0 ||
		    !info->data) अणु
			dev_err(&पूर्णांकf->dev,
				"bogus CDC Union: master=%u, slave=%u\n",
				cdc_जोड़->bMasterInterface0,
				cdc_जोड़->bSlaveInterface0);

			/* ignore and जारी... */
			cdc_जोड़ = शून्य;
			info->data = पूर्णांकf;
		पूर्ण
	पूर्ण

	/* errors aren't fatal - we can live with the dynamic address */
	अगर (cdc_ether && cdc_ether->wMaxSegmentSize) अणु
		dev->hard_mtu = le16_to_cpu(cdc_ether->wMaxSegmentSize);
		usbnet_get_ethernet_addr(dev, cdc_ether->iMACAddress);
	पूर्ण

	/* claim data पूर्णांकerface and set it up */
	अगर (info->control != info->data) अणु
		status = usb_driver_claim_पूर्णांकerface(driver, info->data, dev);
		अगर (status < 0)
			जाओ err;
	पूर्ण

	status = qmi_wwan_रेजिस्टर_subdriver(dev);
	अगर (status < 0 && info->control != info->data) अणु
		usb_set_पूर्णांकfdata(info->data, शून्य);
		usb_driver_release_पूर्णांकerface(driver, info->data);
	पूर्ण

	/* disabling remote wakeup on MDM9x30 devices has the same
	 * effect as clearing DTR. The device will not respond to QMI
	 * requests until we set DTR again.  This is similar to a
	 * QMI_CTL SYNC request, clearing a lot of firmware state
	 * including the client ID allocations.
	 *
	 * Our usage model allows a session to span multiple
	 * खोलो/बंद events, so we must prevent the firmware from
	 * clearing out state the clients might need.
	 *
	 * MDM9x30 is the first QMI chipset with USB3 support. Abuse
	 * this fact to enable the quirk क्रम all USB3 devices.
	 *
	 * There are also chipsets with the same "set DTR" requirement
	 * but without USB3 support.  Devices based on these chips
	 * need a quirk flag in the device ID table.
	 */
	अगर (dev->driver_info->data & QMI_WWAN_QUIRK_DTR ||
	    le16_to_cpu(dev->udev->descriptor.bcdUSB) >= 0x0201) अणु
		qmi_wwan_manage_घातer(dev, 1);
		qmi_wwan_change_dtr(dev, true);
	पूर्ण

	/* Never use the same address on both ends of the link, even अगर the
	 * buggy firmware told us to. Or, अगर device is asचिन्हित the well-known
	 * buggy firmware MAC address, replace it with a अक्रमom address,
	 */
	अगर (ether_addr_equal(dev->net->dev_addr, शेष_modem_addr) ||
	    ether_addr_equal(dev->net->dev_addr, buggy_fw_addr))
		eth_hw_addr_अक्रमom(dev->net);

	/* make MAC addr easily distinguishable from an IP header */
	अगर (possibly_iphdr(dev->net->dev_addr)) अणु
		dev->net->dev_addr[0] |= 0x02;	/* set local assignment bit */
		dev->net->dev_addr[0] &= 0xbf;	/* clear "IP" bit */
	पूर्ण
	dev->net->netdev_ops = &qmi_wwan_netdev_ops;
	dev->net->sysfs_groups[0] = &qmi_wwan_sysfs_attr_group;
err:
	वापस status;
पूर्ण

अटल व्योम qmi_wwan_unbind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा qmi_wwan_state *info = (व्योम *)&dev->data;
	काष्ठा usb_driver *driver = driver_of(पूर्णांकf);
	काष्ठा usb_पूर्णांकerface *other;

	अगर (info->subdriver && info->subdriver->disconnect)
		info->subdriver->disconnect(info->control);

	/* disable MDM9x30 quirk */
	अगर (le16_to_cpu(dev->udev->descriptor.bcdUSB) >= 0x0201) अणु
		qmi_wwan_change_dtr(dev, false);
		qmi_wwan_manage_घातer(dev, 0);
	पूर्ण

	/* allow user to unbind using either control or data */
	अगर (पूर्णांकf == info->control)
		other = info->data;
	अन्यथा
		other = info->control;

	/* only अगर not shared */
	अगर (other && पूर्णांकf != other) अणु
		usb_set_पूर्णांकfdata(other, शून्य);
		usb_driver_release_पूर्णांकerface(driver, other);
	पूर्ण

	info->subdriver = शून्य;
	info->data = शून्य;
	info->control = शून्य;
पूर्ण

/* suspend/resume wrappers calling both usbnet and the cdc-wdm
 * subdriver अगर present.
 *
 * NOTE: cdc-wdm also supports pre/post_reset, but we cannot provide
 * wrappers क्रम those without adding usbnet reset support first.
 */
अटल पूर्णांक qmi_wwan_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा usbnet *dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा qmi_wwan_state *info = (व्योम *)&dev->data;
	पूर्णांक ret;

	/* Both usbnet_suspend() and subdriver->suspend() MUST वापस 0
	 * in प्रणाली sleep context, otherwise, the resume callback has
	 * to recover device from previous suspend failure.
	 */
	ret = usbnet_suspend(पूर्णांकf, message);
	अगर (ret < 0)
		जाओ err;

	अगर (पूर्णांकf == info->control && info->subdriver &&
	    info->subdriver->suspend)
		ret = info->subdriver->suspend(पूर्णांकf, message);
	अगर (ret < 0)
		usbnet_resume(पूर्णांकf);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक qmi_wwan_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usbnet *dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा qmi_wwan_state *info = (व्योम *)&dev->data;
	पूर्णांक ret = 0;
	bool callsub = (पूर्णांकf == info->control && info->subdriver &&
			info->subdriver->resume);

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

अटल स्थिर काष्ठा driver_info	qmi_wwan_info = अणु
	.description	= "WWAN/QMI device",
	.flags		= FLAG_WWAN | FLAG_SEND_ZLP,
	.bind		= qmi_wwan_bind,
	.unbind		= qmi_wwan_unbind,
	.manage_घातer	= qmi_wwan_manage_घातer,
	.rx_fixup       = qmi_wwan_rx_fixup,
पूर्ण;

अटल स्थिर काष्ठा driver_info	qmi_wwan_info_quirk_dtr = अणु
	.description	= "WWAN/QMI device",
	.flags		= FLAG_WWAN | FLAG_SEND_ZLP,
	.bind		= qmi_wwan_bind,
	.unbind		= qmi_wwan_unbind,
	.manage_घातer	= qmi_wwan_manage_घातer,
	.rx_fixup       = qmi_wwan_rx_fixup,
	.data           = QMI_WWAN_QUIRK_DTR,
पूर्ण;

#घोषणा HUAWEI_VENDOR_ID	0x12D1

/* map QMI/wwan function by a fixed पूर्णांकerface number */
#घोषणा QMI_FIXED_INTF(vend, prod, num) \
	USB_DEVICE_INTERFACE_NUMBER(vend, prod, num), \
	.driver_info = (अचिन्हित दीर्घ)&qmi_wwan_info

/* devices requiring "set DTR" quirk */
#घोषणा QMI_QUIRK_SET_DTR(vend, prod, num) \
	USB_DEVICE_INTERFACE_NUMBER(vend, prod, num), \
	.driver_info = (अचिन्हित दीर्घ)&qmi_wwan_info_quirk_dtr

/* Gobi 1000 QMI/wwan पूर्णांकerface number is 3 according to qcserial */
#घोषणा QMI_GOBI1K_DEVICE(vend, prod) \
	QMI_FIXED_INTF(vend, prod, 3)

/* Gobi 2000/3000 QMI/wwan पूर्णांकerface number is 0 according to qcserial */
#घोषणा QMI_GOBI_DEVICE(vend, prod) \
	QMI_FIXED_INTF(vend, prod, 0)

/* Many devices have QMI and DIAG functions which are distinguishable
 * from other venकरोr specअगरic functions by class, subclass and
 * protocol all being 0xff. The DIAG function has exactly 2 endpoपूर्णांकs
 * and is silently rejected when probed.
 *
 * This makes it possible to match dynamically numbered QMI functions
 * as seen on e.g. many Quectel modems.
 */
#घोषणा QMI_MATCH_FF_FF_FF(vend, prod) \
	USB_DEVICE_AND_INTERFACE_INFO(vend, prod, USB_CLASS_VENDOR_SPEC, \
				      USB_SUBCLASS_VENDOR_SPEC, 0xff), \
	.driver_info = (अचिन्हित दीर्घ)&qmi_wwan_info_quirk_dtr

अटल स्थिर काष्ठा usb_device_id products[] = अणु
	/* 1. CDC ECM like devices match on the control पूर्णांकerface */
	अणु	/* Huawei E392, E398 and possibly others sharing both device id and more... */
		USB_VENDOR_AND_INTERFACE_INFO(HUAWEI_VENDOR_ID, USB_CLASS_VENDOR_SPEC, 1, 9),
		.driver_info        = (अचिन्हित दीर्घ)&qmi_wwan_info,
	पूर्ण,
	अणु	/* Vodafone/Huawei K5005 (12d1:14c8) and similar modems */
		USB_VENDOR_AND_INTERFACE_INFO(HUAWEI_VENDOR_ID, USB_CLASS_VENDOR_SPEC, 1, 57),
		.driver_info        = (अचिन्हित दीर्घ)&qmi_wwan_info,
	पूर्ण,
	अणु	/* HUAWEI_INTERFACE_NDIS_CONTROL_QUALCOMM */
		USB_VENDOR_AND_INTERFACE_INFO(HUAWEI_VENDOR_ID, USB_CLASS_VENDOR_SPEC, 0x01, 0x69),
		.driver_info        = (अचिन्हित दीर्घ)&qmi_wwan_info,
	पूर्ण,
	अणु	/* Motorola Mapphone devices with MDM6600 */
		USB_VENDOR_AND_INTERFACE_INFO(0x22b8, USB_CLASS_VENDOR_SPEC, 0xfb, 0xff),
		.driver_info        = (अचिन्हित दीर्घ)&qmi_wwan_info,
	पूर्ण,

	/* 2. Combined पूर्णांकerface devices matching on class+protocol */
	अणु	/* Huawei E367 and possibly others in "Windows mode" */
		USB_VENDOR_AND_INTERFACE_INFO(HUAWEI_VENDOR_ID, USB_CLASS_VENDOR_SPEC, 1, 7),
		.driver_info        = (अचिन्हित दीर्घ)&qmi_wwan_info,
	पूर्ण,
	अणु	/* Huawei E392, E398 and possibly others in "Windows mode" */
		USB_VENDOR_AND_INTERFACE_INFO(HUAWEI_VENDOR_ID, USB_CLASS_VENDOR_SPEC, 1, 17),
		.driver_info        = (अचिन्हित दीर्घ)&qmi_wwan_info,
	पूर्ण,
	अणु	/* HUAWEI_NDIS_SINGLE_INTERFACE_VDF */
		USB_VENDOR_AND_INTERFACE_INFO(HUAWEI_VENDOR_ID, USB_CLASS_VENDOR_SPEC, 0x01, 0x37),
		.driver_info        = (अचिन्हित दीर्घ)&qmi_wwan_info,
	पूर्ण,
	अणु	/* HUAWEI_INTERFACE_NDIS_HW_QUALCOMM */
		USB_VENDOR_AND_INTERFACE_INFO(HUAWEI_VENDOR_ID, USB_CLASS_VENDOR_SPEC, 0x01, 0x67),
		.driver_info        = (अचिन्हित दीर्घ)&qmi_wwan_info,
	पूर्ण,
	अणु	/* Pantech UML290, P4200 and more */
		USB_VENDOR_AND_INTERFACE_INFO(0x106c, USB_CLASS_VENDOR_SPEC, 0xf0, 0xff),
		.driver_info        = (अचिन्हित दीर्घ)&qmi_wwan_info,
	पूर्ण,
	अणु	/* Pantech UML290 - newer firmware */
		USB_VENDOR_AND_INTERFACE_INFO(0x106c, USB_CLASS_VENDOR_SPEC, 0xf1, 0xff),
		.driver_info        = (अचिन्हित दीर्घ)&qmi_wwan_info,
	पूर्ण,
	अणु	/* Novatel USB551L and MC551 */
		USB_DEVICE_AND_INTERFACE_INFO(0x1410, 0xb001,
		                              USB_CLASS_COMM,
		                              USB_CDC_SUBCLASS_ETHERNET,
		                              USB_CDC_PROTO_NONE),
		.driver_info        = (अचिन्हित दीर्घ)&qmi_wwan_info,
	पूर्ण,
	अणु	/* Novatel E362 */
		USB_DEVICE_AND_INTERFACE_INFO(0x1410, 0x9010,
		                              USB_CLASS_COMM,
		                              USB_CDC_SUBCLASS_ETHERNET,
		                              USB_CDC_PROTO_NONE),
		.driver_info        = (अचिन्हित दीर्घ)&qmi_wwan_info,
	पूर्ण,
	अणु	/* Novatel Expedite E371 */
		USB_DEVICE_AND_INTERFACE_INFO(0x1410, 0x9011,
		                              USB_CLASS_COMM,
		                              USB_CDC_SUBCLASS_ETHERNET,
		                              USB_CDC_PROTO_NONE),
		.driver_info        = (अचिन्हित दीर्घ)&qmi_wwan_info,
	पूर्ण,
	अणु	/* Dell Wireless 5800 (Novatel E362) */
		USB_DEVICE_AND_INTERFACE_INFO(0x413C, 0x8195,
					      USB_CLASS_COMM,
					      USB_CDC_SUBCLASS_ETHERNET,
					      USB_CDC_PROTO_NONE),
		.driver_info        = (अचिन्हित दीर्घ)&qmi_wwan_info,
	पूर्ण,
	अणु	/* Dell Wireless 5800 V2 (Novatel E362) */
		USB_DEVICE_AND_INTERFACE_INFO(0x413C, 0x8196,
					      USB_CLASS_COMM,
					      USB_CDC_SUBCLASS_ETHERNET,
					      USB_CDC_PROTO_NONE),
		.driver_info        = (अचिन्हित दीर्घ)&qmi_wwan_info,
	पूर्ण,
	अणु	/* Dell Wireless 5804 (Novatel E371) */
		USB_DEVICE_AND_INTERFACE_INFO(0x413C, 0x819b,
					      USB_CLASS_COMM,
					      USB_CDC_SUBCLASS_ETHERNET,
					      USB_CDC_PROTO_NONE),
		.driver_info        = (अचिन्हित दीर्घ)&qmi_wwan_info,
	पूर्ण,
	अणु	/* ADU960S */
		USB_DEVICE_AND_INTERFACE_INFO(0x16d5, 0x650a,
					      USB_CLASS_COMM,
					      USB_CDC_SUBCLASS_ETHERNET,
					      USB_CDC_PROTO_NONE),
		.driver_info        = (अचिन्हित दीर्घ)&qmi_wwan_info,
	पूर्ण,
	अणु	/* HP lt2523 (Novatel E371) */
		USB_DEVICE_AND_INTERFACE_INFO(0x03f0, 0x421d,
					      USB_CLASS_COMM,
					      USB_CDC_SUBCLASS_ETHERNET,
					      USB_CDC_PROTO_NONE),
		.driver_info        = (अचिन्हित दीर्घ)&qmi_wwan_info,
	पूर्ण,
	अणु	/* HP lt4112 LTE/HSPA+ Gobi 4G Module (Huawei me906e) */
		USB_DEVICE_AND_INTERFACE_INFO(0x03f0, 0x581d, USB_CLASS_VENDOR_SPEC, 1, 7),
		.driver_info = (अचिन्हित दीर्घ)&qmi_wwan_info,
	पूर्ण,
	अणुQMI_MATCH_FF_FF_FF(0x2c7c, 0x0125)पूर्ण,	/* Quectel EC25, EC20 R2.0  Mini PCIe */
	अणुQMI_MATCH_FF_FF_FF(0x2c7c, 0x0306)पूर्ण,	/* Quectel EP06/EG06/EM06 */
	अणुQMI_MATCH_FF_FF_FF(0x2c7c, 0x0512)पूर्ण,	/* Quectel EG12/EM12 */
	अणुQMI_MATCH_FF_FF_FF(0x2c7c, 0x0620)पूर्ण,	/* Quectel EM160R-GL */
	अणुQMI_MATCH_FF_FF_FF(0x2c7c, 0x0800)पूर्ण,	/* Quectel RM500Q-GL */

	/* 3. Combined पूर्णांकerface devices matching on पूर्णांकerface number */
	अणुQMI_FIXED_INTF(0x0408, 0xea42, 4)पूर्ण,	/* Yota / Megafon M100-1 */
	अणुQMI_FIXED_INTF(0x05c6, 0x6001, 3)पूर्ण,	/* 4G LTE usb-modem U901 */
	अणुQMI_FIXED_INTF(0x05c6, 0x7000, 0)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x7001, 1)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x7002, 1)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x7101, 1)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x7101, 2)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x7101, 3)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x7102, 1)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x7102, 2)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x7102, 3)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x8000, 7)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x8001, 6)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9000, 4)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9003, 4)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9005, 2)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x900a, 4)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x900b, 2)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x900c, 4)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x900c, 5)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x900c, 6)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x900d, 5)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x900f, 3)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x900f, 4)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x900f, 5)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9010, 4)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9010, 5)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9011, 3)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9011, 4)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9021, 1)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9022, 2)पूर्ण,
	अणुQMI_QUIRK_SET_DTR(0x05c6, 0x9025, 4)पूर्ण,	/* Alcatel-sbell ASB TL131 TDD LTE (China Mobile) */
	अणुQMI_FIXED_INTF(0x05c6, 0x9026, 3)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x902e, 5)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9031, 5)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9032, 4)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9033, 3)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9033, 4)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9033, 5)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9033, 6)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9034, 3)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9034, 4)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9034, 5)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9034, 6)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9034, 7)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9035, 4)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9036, 3)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9037, 5)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9038, 4)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x903b, 7)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x903c, 6)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x903d, 6)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x903e, 5)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9043, 3)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9046, 3)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9046, 4)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9046, 5)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9047, 2)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9047, 3)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9047, 4)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9048, 4)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9048, 5)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9048, 6)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9048, 7)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9048, 8)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x904c, 5)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x904c, 6)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x904c, 7)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x904c, 8)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9050, 3)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9052, 4)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9053, 6)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9053, 7)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9054, 5)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9054, 6)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9055, 3)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9055, 4)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9055, 5)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9055, 6)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9055, 7)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9056, 3)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9062, 2)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9062, 3)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9062, 4)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9062, 5)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9062, 6)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9062, 7)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9062, 8)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9062, 9)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9064, 3)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9065, 6)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9065, 7)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9066, 5)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9066, 6)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9067, 1)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9068, 2)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9068, 3)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9068, 4)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9068, 5)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9068, 6)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9068, 7)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9069, 5)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9069, 6)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9069, 7)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9069, 8)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9070, 4)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9070, 5)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9075, 5)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9076, 4)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9076, 5)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9076, 6)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9076, 7)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9076, 8)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9077, 3)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9077, 4)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9077, 5)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9077, 6)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9078, 3)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9079, 4)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9079, 5)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9079, 6)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9079, 7)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9079, 8)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9080, 5)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9080, 6)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9080, 7)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9080, 8)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9083, 3)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x9084, 4)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x90b2, 3)पूर्ण,    /* ublox R410M */
	अणुQMI_FIXED_INTF(0x05c6, 0x920d, 0)पूर्ण,
	अणुQMI_FIXED_INTF(0x05c6, 0x920d, 5)पूर्ण,
	अणुQMI_QUIRK_SET_DTR(0x05c6, 0x9625, 4)पूर्ण,	/* YUGA CLM920-NC5 */
	अणुQMI_FIXED_INTF(0x0846, 0x68a2, 8)पूर्ण,
	अणुQMI_FIXED_INTF(0x0846, 0x68d3, 8)पूर्ण,	/* Netgear Aircard 779S */
	अणुQMI_FIXED_INTF(0x12d1, 0x140c, 1)पूर्ण,	/* Huawei E173 */
	अणुQMI_FIXED_INTF(0x12d1, 0x14ac, 1)पूर्ण,	/* Huawei E1820 */
	अणुQMI_FIXED_INTF(0x1435, 0x0918, 3)पूर्ण,	/* Wistron NeWeb D16Q1 */
	अणुQMI_FIXED_INTF(0x1435, 0x0918, 4)पूर्ण,	/* Wistron NeWeb D16Q1 */
	अणुQMI_FIXED_INTF(0x1435, 0x0918, 5)पूर्ण,	/* Wistron NeWeb D16Q1 */
	अणुQMI_FIXED_INTF(0x1435, 0x3185, 4)पूर्ण,	/* Wistron NeWeb M18Q5 */
	अणुQMI_FIXED_INTF(0x1435, 0xd111, 4)पूर्ण,	/* M9615A DM11-1 D51QC */
	अणुQMI_FIXED_INTF(0x1435, 0xd181, 3)पूर्ण,	/* Wistron NeWeb D18Q1 */
	अणुQMI_FIXED_INTF(0x1435, 0xd181, 4)पूर्ण,	/* Wistron NeWeb D18Q1 */
	अणुQMI_FIXED_INTF(0x1435, 0xd181, 5)पूर्ण,	/* Wistron NeWeb D18Q1 */
	अणुQMI_FIXED_INTF(0x1435, 0xd182, 4)पूर्ण,	/* Wistron NeWeb D18 */
	अणुQMI_FIXED_INTF(0x1435, 0xd182, 5)पूर्ण,	/* Wistron NeWeb D18 */
	अणुQMI_FIXED_INTF(0x1435, 0xd191, 4)पूर्ण,	/* Wistron NeWeb D19Q1 */
	अणुQMI_QUIRK_SET_DTR(0x1508, 0x1001, 4)पूर्ण,	/* Fibocom NL668 series */
	अणुQMI_FIXED_INTF(0x1690, 0x7588, 4)पूर्ण,    /* ASKEY WWHC050 */
	अणुQMI_FIXED_INTF(0x16d8, 0x6003, 0)पूर्ण,	/* CMOTech 6003 */
	अणुQMI_FIXED_INTF(0x16d8, 0x6007, 0)पूर्ण,	/* CMOTech CHE-628S */
	अणुQMI_FIXED_INTF(0x16d8, 0x6008, 0)पूर्ण,	/* CMOTech CMU-301 */
	अणुQMI_FIXED_INTF(0x16d8, 0x6280, 0)पूर्ण,	/* CMOTech CHU-628 */
	अणुQMI_FIXED_INTF(0x16d8, 0x7001, 0)पूर्ण,	/* CMOTech CHU-720S */
	अणुQMI_FIXED_INTF(0x16d8, 0x7002, 0)पूर्ण,	/* CMOTech 7002 */
	अणुQMI_FIXED_INTF(0x16d8, 0x7003, 4)पूर्ण,	/* CMOTech CHU-629K */
	अणुQMI_FIXED_INTF(0x16d8, 0x7004, 3)पूर्ण,	/* CMOTech 7004 */
	अणुQMI_FIXED_INTF(0x16d8, 0x7006, 5)पूर्ण,	/* CMOTech CGU-629 */
	अणुQMI_FIXED_INTF(0x16d8, 0x700a, 4)पूर्ण,	/* CMOTech CHU-629S */
	अणुQMI_FIXED_INTF(0x16d8, 0x7211, 0)पूर्ण,	/* CMOTech CHU-720I */
	अणुQMI_FIXED_INTF(0x16d8, 0x7212, 0)पूर्ण,	/* CMOTech 7212 */
	अणुQMI_FIXED_INTF(0x16d8, 0x7213, 0)पूर्ण,	/* CMOTech 7213 */
	अणुQMI_FIXED_INTF(0x16d8, 0x7251, 1)पूर्ण,	/* CMOTech 7251 */
	अणुQMI_FIXED_INTF(0x16d8, 0x7252, 1)पूर्ण,	/* CMOTech 7252 */
	अणुQMI_FIXED_INTF(0x16d8, 0x7253, 1)पूर्ण,	/* CMOTech 7253 */
	अणुQMI_FIXED_INTF(0x19d2, 0x0002, 1)पूर्ण,
	अणुQMI_FIXED_INTF(0x19d2, 0x0012, 1)पूर्ण,
	अणुQMI_FIXED_INTF(0x19d2, 0x0017, 3)पूर्ण,
	अणुQMI_FIXED_INTF(0x19d2, 0x0019, 3)पूर्ण,	/* ONDA MT689DC */
	अणुQMI_FIXED_INTF(0x19d2, 0x0021, 4)पूर्ण,
	अणुQMI_FIXED_INTF(0x19d2, 0x0025, 1)पूर्ण,
	अणुQMI_FIXED_INTF(0x19d2, 0x0031, 4)पूर्ण,
	अणुQMI_FIXED_INTF(0x19d2, 0x0042, 4)पूर्ण,
	अणुQMI_FIXED_INTF(0x19d2, 0x0049, 5)पूर्ण,
	अणुQMI_FIXED_INTF(0x19d2, 0x0052, 4)पूर्ण,
	अणुQMI_FIXED_INTF(0x19d2, 0x0055, 1)पूर्ण,	/* ZTE (Vodafone) K3520-Z */
	अणुQMI_FIXED_INTF(0x19d2, 0x0058, 4)पूर्ण,
	अणुQMI_FIXED_INTF(0x19d2, 0x0063, 4)पूर्ण,	/* ZTE (Vodafone) K3565-Z */
	अणुQMI_FIXED_INTF(0x19d2, 0x0104, 4)पूर्ण,	/* ZTE (Vodafone) K4505-Z */
	अणुQMI_FIXED_INTF(0x19d2, 0x0113, 5)पूर्ण,
	अणुQMI_FIXED_INTF(0x19d2, 0x0118, 5)पूर्ण,
	अणुQMI_FIXED_INTF(0x19d2, 0x0121, 5)पूर्ण,
	अणुQMI_FIXED_INTF(0x19d2, 0x0123, 4)पूर्ण,
	अणुQMI_FIXED_INTF(0x19d2, 0x0124, 5)पूर्ण,
	अणुQMI_FIXED_INTF(0x19d2, 0x0125, 6)पूर्ण,
	अणुQMI_FIXED_INTF(0x19d2, 0x0126, 5)पूर्ण,
	अणुQMI_FIXED_INTF(0x19d2, 0x0130, 1)पूर्ण,
	अणुQMI_FIXED_INTF(0x19d2, 0x0133, 3)पूर्ण,
	अणुQMI_FIXED_INTF(0x19d2, 0x0141, 5)पूर्ण,
	अणुQMI_FIXED_INTF(0x19d2, 0x0157, 5)पूर्ण,	/* ZTE MF683 */
	अणुQMI_FIXED_INTF(0x19d2, 0x0158, 3)पूर्ण,
	अणुQMI_FIXED_INTF(0x19d2, 0x0167, 4)पूर्ण,	/* ZTE MF820D */
	अणुQMI_FIXED_INTF(0x19d2, 0x0168, 4)पूर्ण,
	अणुQMI_FIXED_INTF(0x19d2, 0x0176, 3)पूर्ण,
	अणुQMI_FIXED_INTF(0x19d2, 0x0178, 3)पूर्ण,
	अणुQMI_FIXED_INTF(0x19d2, 0x0191, 4)पूर्ण,	/* ZTE EuFi890 */
	अणुQMI_FIXED_INTF(0x19d2, 0x0199, 1)पूर्ण,	/* ZTE MF820S */
	अणुQMI_FIXED_INTF(0x19d2, 0x0200, 1)पूर्ण,
	अणुQMI_FIXED_INTF(0x19d2, 0x0257, 3)पूर्ण,	/* ZTE MF821 */
	अणुQMI_FIXED_INTF(0x19d2, 0x0265, 4)पूर्ण,	/* ONDA MT8205 4G LTE */
	अणुQMI_FIXED_INTF(0x19d2, 0x0284, 4)पूर्ण,	/* ZTE MF880 */
	अणुQMI_FIXED_INTF(0x19d2, 0x0326, 4)पूर्ण,	/* ZTE MF821D */
	अणुQMI_FIXED_INTF(0x19d2, 0x0396, 3)पूर्ण,	/* ZTE ZM8620 */
	अणुQMI_FIXED_INTF(0x19d2, 0x0412, 4)पूर्ण,	/* Telewell TW-LTE 4G */
	अणुQMI_FIXED_INTF(0x19d2, 0x1008, 4)पूर्ण,	/* ZTE (Vodafone) K3570-Z */
	अणुQMI_FIXED_INTF(0x19d2, 0x1010, 4)पूर्ण,	/* ZTE (Vodafone) K3571-Z */
	अणुQMI_FIXED_INTF(0x19d2, 0x1012, 4)पूर्ण,
	अणुQMI_FIXED_INTF(0x19d2, 0x1018, 3)पूर्ण,	/* ZTE (Vodafone) K5006-Z */
	अणुQMI_FIXED_INTF(0x19d2, 0x1021, 2)पूर्ण,
	अणुQMI_FIXED_INTF(0x19d2, 0x1245, 4)पूर्ण,
	अणुQMI_FIXED_INTF(0x19d2, 0x1247, 4)पूर्ण,
	अणुQMI_FIXED_INTF(0x19d2, 0x1252, 4)पूर्ण,
	अणुQMI_FIXED_INTF(0x19d2, 0x1254, 4)पूर्ण,
	अणुQMI_FIXED_INTF(0x19d2, 0x1255, 3)पूर्ण,
	अणुQMI_FIXED_INTF(0x19d2, 0x1255, 4)पूर्ण,
	अणुQMI_FIXED_INTF(0x19d2, 0x1256, 4)पूर्ण,
	अणुQMI_FIXED_INTF(0x19d2, 0x1270, 5)पूर्ण,	/* ZTE MF667 */
	अणुQMI_FIXED_INTF(0x19d2, 0x1275, 3)पूर्ण,	/* ZTE P685M */
	अणुQMI_FIXED_INTF(0x19d2, 0x1401, 2)पूर्ण,
	अणुQMI_FIXED_INTF(0x19d2, 0x1402, 2)पूर्ण,	/* ZTE MF60 */
	अणुQMI_FIXED_INTF(0x19d2, 0x1424, 2)पूर्ण,
	अणुQMI_FIXED_INTF(0x19d2, 0x1425, 2)पूर्ण,
	अणुQMI_FIXED_INTF(0x19d2, 0x1426, 2)पूर्ण,	/* ZTE MF91 */
	अणुQMI_FIXED_INTF(0x19d2, 0x1428, 2)पूर्ण,	/* Telewell TW-LTE 4G v2 */
	अणुQMI_FIXED_INTF(0x19d2, 0x1432, 3)पूर्ण,	/* ZTE ME3620 */
	अणुQMI_FIXED_INTF(0x19d2, 0x2002, 4)पूर्ण,	/* ZTE (Vodafone) K3765-Z */
	अणुQMI_FIXED_INTF(0x2001, 0x7e16, 3)पूर्ण,	/* D-Link DWM-221 */
	अणुQMI_FIXED_INTF(0x2001, 0x7e19, 4)पूर्ण,	/* D-Link DWM-221 B1 */
	अणुQMI_FIXED_INTF(0x2001, 0x7e35, 4)पूर्ण,	/* D-Link DWM-222 */
	अणुQMI_FIXED_INTF(0x2001, 0x7e3d, 4)पूर्ण,	/* D-Link DWM-222 A2 */
	अणुQMI_FIXED_INTF(0x2020, 0x2031, 4)पूर्ण,	/* Olicard 600 */
	अणुQMI_FIXED_INTF(0x2020, 0x2033, 4)पूर्ण,	/* BroadMobi BM806U */
	अणुQMI_FIXED_INTF(0x2020, 0x2060, 4)पूर्ण,	/* BroadMobi BM818 */
	अणुQMI_FIXED_INTF(0x0f3d, 0x68a2, 8)पूर्ण,    /* Sierra Wireless MC7700 */
	अणुQMI_FIXED_INTF(0x114f, 0x68a2, 8)पूर्ण,    /* Sierra Wireless MC7750 */
	अणुQMI_FIXED_INTF(0x1199, 0x68a2, 8)पूर्ण,	/* Sierra Wireless MC7710 in QMI mode */
	अणुQMI_FIXED_INTF(0x1199, 0x68a2, 19)पूर्ण,	/* Sierra Wireless MC7710 in QMI mode */
	अणुQMI_QUIRK_SET_DTR(0x1199, 0x68c0, 8)पूर्ण,	/* Sierra Wireless MC7304/MC7354, WP76xx */
	अणुQMI_QUIRK_SET_DTR(0x1199, 0x68c0, 10)पूर्ण,/* Sierra Wireless MC7304/MC7354 */
	अणुQMI_FIXED_INTF(0x1199, 0x901c, 8)पूर्ण,    /* Sierra Wireless EM7700 */
	अणुQMI_FIXED_INTF(0x1199, 0x901f, 8)पूर्ण,    /* Sierra Wireless EM7355 */
	अणुQMI_FIXED_INTF(0x1199, 0x9041, 8)पूर्ण,	/* Sierra Wireless MC7305/MC7355 */
	अणुQMI_FIXED_INTF(0x1199, 0x9041, 10)पूर्ण,	/* Sierra Wireless MC7305/MC7355 */
	अणुQMI_FIXED_INTF(0x1199, 0x9051, 8)पूर्ण,	/* Netgear AirCard 340U */
	अणुQMI_FIXED_INTF(0x1199, 0x9053, 8)पूर्ण,	/* Sierra Wireless Modem */
	अणुQMI_FIXED_INTF(0x1199, 0x9054, 8)पूर्ण,	/* Sierra Wireless Modem */
	अणुQMI_FIXED_INTF(0x1199, 0x9055, 8)पूर्ण,	/* Netgear AirCard 341U */
	अणुQMI_FIXED_INTF(0x1199, 0x9056, 8)पूर्ण,	/* Sierra Wireless Modem */
	अणुQMI_FIXED_INTF(0x1199, 0x9057, 8)पूर्ण,
	अणुQMI_FIXED_INTF(0x1199, 0x9061, 8)पूर्ण,	/* Sierra Wireless Modem */
	अणुQMI_FIXED_INTF(0x1199, 0x9063, 8)पूर्ण,	/* Sierra Wireless EM7305 */
	अणुQMI_FIXED_INTF(0x1199, 0x9063, 10)पूर्ण,	/* Sierra Wireless EM7305 */
	अणुQMI_QUIRK_SET_DTR(0x1199, 0x9071, 8)पूर्ण,	/* Sierra Wireless MC74xx */
	अणुQMI_QUIRK_SET_DTR(0x1199, 0x9071, 10)पूर्ण,/* Sierra Wireless MC74xx */
	अणुQMI_QUIRK_SET_DTR(0x1199, 0x9079, 8)पूर्ण,	/* Sierra Wireless EM74xx */
	अणुQMI_QUIRK_SET_DTR(0x1199, 0x9079, 10)पूर्ण,/* Sierra Wireless EM74xx */
	अणुQMI_QUIRK_SET_DTR(0x1199, 0x907b, 8)पूर्ण,	/* Sierra Wireless EM74xx */
	अणुQMI_QUIRK_SET_DTR(0x1199, 0x907b, 10)पूर्ण,/* Sierra Wireless EM74xx */
	अणुQMI_QUIRK_SET_DTR(0x1199, 0x9091, 8)पूर्ण,	/* Sierra Wireless EM7565 */
	अणुQMI_FIXED_INTF(0x1bbb, 0x011e, 4)पूर्ण,	/* Telekom Speedstick LTE II (Alcatel One Touch L100V LTE) */
	अणुQMI_FIXED_INTF(0x1bbb, 0x0203, 2)पूर्ण,	/* Alcatel L800MA */
	अणुQMI_FIXED_INTF(0x2357, 0x0201, 4)पूर्ण,	/* TP-LINK HSUPA Modem MA180 */
	अणुQMI_FIXED_INTF(0x2357, 0x9000, 4)पूर्ण,	/* TP-LINK MA260 */
	अणुQMI_QUIRK_SET_DTR(0x1bc7, 0x1031, 3)पूर्ण, /* Telit LE910C1-EUX */
	अणुQMI_QUIRK_SET_DTR(0x1bc7, 0x1040, 2)पूर्ण,	/* Telit LE922A */
	अणुQMI_QUIRK_SET_DTR(0x1bc7, 0x1050, 2)पूर्ण,	/* Telit FN980 */
	अणुQMI_FIXED_INTF(0x1bc7, 0x1100, 3)पूर्ण,	/* Telit ME910 */
	अणुQMI_FIXED_INTF(0x1bc7, 0x1101, 3)पूर्ण,	/* Telit ME910 dual modem */
	अणुQMI_FIXED_INTF(0x1bc7, 0x1200, 5)पूर्ण,	/* Telit LE920 */
	अणुQMI_QUIRK_SET_DTR(0x1bc7, 0x1201, 2)पूर्ण,	/* Telit LE920, LE920A4 */
	अणुQMI_QUIRK_SET_DTR(0x1bc7, 0x1230, 2)पूर्ण,	/* Telit LE910Cx */
	अणुQMI_QUIRK_SET_DTR(0x1bc7, 0x1260, 2)पूर्ण,	/* Telit LE910Cx */
	अणुQMI_QUIRK_SET_DTR(0x1bc7, 0x1261, 2)पूर्ण,	/* Telit LE910Cx */
	अणुQMI_QUIRK_SET_DTR(0x1bc7, 0x1900, 1)पूर्ण,	/* Telit LN940 series */
	अणुQMI_FIXED_INTF(0x1c9e, 0x9801, 3)पूर्ण,	/* Telewell TW-3G HSPA+ */
	अणुQMI_FIXED_INTF(0x1c9e, 0x9803, 4)पूर्ण,	/* Telewell TW-3G HSPA+ */
	अणुQMI_FIXED_INTF(0x1c9e, 0x9b01, 3)पूर्ण,	/* XS Stick W100-2 from 4G Systems */
	अणुQMI_FIXED_INTF(0x0b3c, 0xc000, 4)पूर्ण,	/* Olivetti Olicard 100 */
	अणुQMI_FIXED_INTF(0x0b3c, 0xc001, 4)पूर्ण,	/* Olivetti Olicard 120 */
	अणुQMI_FIXED_INTF(0x0b3c, 0xc002, 4)पूर्ण,	/* Olivetti Olicard 140 */
	अणुQMI_FIXED_INTF(0x0b3c, 0xc004, 6)पूर्ण,	/* Olivetti Olicard 155 */
	अणुQMI_FIXED_INTF(0x0b3c, 0xc005, 6)पूर्ण,	/* Olivetti Olicard 200 */
	अणुQMI_FIXED_INTF(0x0b3c, 0xc00a, 6)पूर्ण,	/* Olivetti Olicard 160 */
	अणुQMI_FIXED_INTF(0x0b3c, 0xc00b, 4)पूर्ण,	/* Olivetti Olicard 500 */
	अणुQMI_FIXED_INTF(0x1e2d, 0x0060, 4)पूर्ण,	/* Cपूर्णांकerion PLxx */
	अणुQMI_QUIRK_SET_DTR(0x1e2d, 0x006f, 8)पूर्ण, /* Cपूर्णांकerion PLS83/PLS63 */
	अणुQMI_FIXED_INTF(0x1e2d, 0x0053, 4)पूर्ण,	/* Cपूर्णांकerion PHxx,PXxx */
	अणुQMI_FIXED_INTF(0x1e2d, 0x0063, 10)पूर्ण,	/* Cपूर्णांकerion ALASxx (1 RmNet) */
	अणुQMI_FIXED_INTF(0x1e2d, 0x0082, 4)पूर्ण,	/* Cपूर्णांकerion PHxx,PXxx (2 RmNet) */
	अणुQMI_FIXED_INTF(0x1e2d, 0x0082, 5)पूर्ण,	/* Cपूर्णांकerion PHxx,PXxx (2 RmNet) */
	अणुQMI_FIXED_INTF(0x1e2d, 0x0083, 4)पूर्ण,	/* Cपूर्णांकerion PHxx,PXxx (1 RmNet + USB Audio)*/
	अणुQMI_QUIRK_SET_DTR(0x1e2d, 0x00b0, 4)पूर्ण,	/* Cपूर्णांकerion CLS8 */
	अणुQMI_FIXED_INTF(0x1e2d, 0x00b7, 0)पूर्ण,	/* Cपूर्णांकerion MV31 RmNet */
	अणुQMI_FIXED_INTF(0x413c, 0x81a2, 8)पूर्ण,	/* Dell Wireless 5806 Gobi(TM) 4G LTE Mobile Broadband Card */
	अणुQMI_FIXED_INTF(0x413c, 0x81a3, 8)पूर्ण,	/* Dell Wireless 5570 HSPA+ (42Mbps) Mobile Broadband Card */
	अणुQMI_FIXED_INTF(0x413c, 0x81a4, 8)पूर्ण,	/* Dell Wireless 5570e HSPA+ (42Mbps) Mobile Broadband Card */
	अणुQMI_FIXED_INTF(0x413c, 0x81a8, 8)पूर्ण,	/* Dell Wireless 5808 Gobi(TM) 4G LTE Mobile Broadband Card */
	अणुQMI_FIXED_INTF(0x413c, 0x81a9, 8)पूर्ण,	/* Dell Wireless 5808e Gobi(TM) 4G LTE Mobile Broadband Card */
	अणुQMI_FIXED_INTF(0x413c, 0x81b1, 8)पूर्ण,	/* Dell Wireless 5809e Gobi(TM) 4G LTE Mobile Broadband Card */
	अणुQMI_FIXED_INTF(0x413c, 0x81b3, 8)पूर्ण,	/* Dell Wireless 5809e Gobi(TM) 4G LTE Mobile Broadband Card (rev3) */
	अणुQMI_FIXED_INTF(0x413c, 0x81b6, 8)पूर्ण,	/* Dell Wireless 5811e */
	अणुQMI_FIXED_INTF(0x413c, 0x81b6, 10)पूर्ण,	/* Dell Wireless 5811e */
	अणुQMI_FIXED_INTF(0x413c, 0x81cc, 8)पूर्ण,	/* Dell Wireless 5816e */
	अणुQMI_FIXED_INTF(0x413c, 0x81d7, 0)पूर्ण,	/* Dell Wireless 5821e */
	अणुQMI_FIXED_INTF(0x413c, 0x81d7, 1)पूर्ण,	/* Dell Wireless 5821e preproduction config */
	अणुQMI_FIXED_INTF(0x413c, 0x81e0, 0)पूर्ण,	/* Dell Wireless 5821e with eSIM support*/
	अणुQMI_FIXED_INTF(0x03f0, 0x4e1d, 8)पूर्ण,	/* HP lt4111 LTE/EV-DO/HSPA+ Gobi 4G Module */
	अणुQMI_FIXED_INTF(0x03f0, 0x9d1d, 1)पूर्ण,	/* HP lt4120 Snapdragon X5 LTE */
	अणुQMI_FIXED_INTF(0x22de, 0x9061, 3)पूर्ण,	/* WeTelecom WPD-600N */
	अणुQMI_QUIRK_SET_DTR(0x1e0e, 0x9001, 5)पूर्ण,	/* SIMCom 7100E, 7230E, 7600E ++ */
	अणुQMI_QUIRK_SET_DTR(0x2c7c, 0x0121, 4)पूर्ण,	/* Quectel EC21 Mini PCIe */
	अणुQMI_QUIRK_SET_DTR(0x2c7c, 0x0191, 4)पूर्ण,	/* Quectel EG91 */
	अणुQMI_QUIRK_SET_DTR(0x2c7c, 0x0195, 4)पूर्ण,	/* Quectel EG95 */
	अणुQMI_FIXED_INTF(0x2c7c, 0x0296, 4)पूर्ण,	/* Quectel BG96 */
	अणुQMI_QUIRK_SET_DTR(0x2cb7, 0x0104, 4)पूर्ण,	/* Fibocom NL678 series */
	अणुQMI_FIXED_INTF(0x0489, 0xe0b4, 0)पूर्ण,	/* Foxconn T77W968 LTE */
	अणुQMI_FIXED_INTF(0x0489, 0xe0b5, 0)पूर्ण,	/* Foxconn T77W968 LTE with eSIM support*/
	अणुQMI_FIXED_INTF(0x2692, 0x9025, 4)पूर्ण,    /* Cellient MPL200 (rebअक्रमed Qualcomm 05c6:9025) */

	/* 4. Gobi 1000 devices */
	अणुQMI_GOBI1K_DEVICE(0x05c6, 0x9212)पूर्ण,	/* Acer Gobi Modem Device */
	अणुQMI_GOBI1K_DEVICE(0x03f0, 0x1f1d)पूर्ण,	/* HP un2400 Gobi Modem Device */
	अणुQMI_GOBI1K_DEVICE(0x04da, 0x250d)पूर्ण,	/* Panasonic Gobi Modem device */
	अणुQMI_GOBI1K_DEVICE(0x413c, 0x8172)पूर्ण,	/* Dell Gobi Modem device */
	अणुQMI_GOBI1K_DEVICE(0x1410, 0xa001)पूर्ण,	/* Novatel/Verizon USB-1000 */
	अणुQMI_GOBI1K_DEVICE(0x1410, 0xa002)पूर्ण,	/* Novatel Gobi Modem device */
	अणुQMI_GOBI1K_DEVICE(0x1410, 0xa003)पूर्ण,	/* Novatel Gobi Modem device */
	अणुQMI_GOBI1K_DEVICE(0x1410, 0xa004)पूर्ण,	/* Novatel Gobi Modem device */
	अणुQMI_GOBI1K_DEVICE(0x1410, 0xa005)पूर्ण,	/* Novatel Gobi Modem device */
	अणुQMI_GOBI1K_DEVICE(0x1410, 0xa006)पूर्ण,	/* Novatel Gobi Modem device */
	अणुQMI_GOBI1K_DEVICE(0x1410, 0xa007)पूर्ण,	/* Novatel Gobi Modem device */
	अणुQMI_GOBI1K_DEVICE(0x0b05, 0x1776)पूर्ण,	/* Asus Gobi Modem device */
	अणुQMI_GOBI1K_DEVICE(0x19d2, 0xfff3)पूर्ण,	/* ONDA Gobi Modem device */
	अणुQMI_GOBI1K_DEVICE(0x05c6, 0x9001)पूर्ण,	/* Generic Gobi Modem device */
	अणुQMI_GOBI1K_DEVICE(0x05c6, 0x9002)पूर्ण,	/* Generic Gobi Modem device */
	अणुQMI_GOBI1K_DEVICE(0x05c6, 0x9202)पूर्ण,	/* Generic Gobi Modem device */
	अणुQMI_GOBI1K_DEVICE(0x05c6, 0x9203)पूर्ण,	/* Generic Gobi Modem device */
	अणुQMI_GOBI1K_DEVICE(0x05c6, 0x9222)पूर्ण,	/* Generic Gobi Modem device */
	अणुQMI_GOBI1K_DEVICE(0x05c6, 0x9009)पूर्ण,	/* Generic Gobi Modem device */

	/* 5. Gobi 2000 and 3000 devices */
	अणुQMI_GOBI_DEVICE(0x413c, 0x8186)पूर्ण,	/* Dell Gobi 2000 Modem device (N0218, VU936) */
	अणुQMI_GOBI_DEVICE(0x413c, 0x8194)पूर्ण,	/* Dell Gobi 3000 Composite */
	अणुQMI_GOBI_DEVICE(0x05c6, 0x920b)पूर्ण,	/* Generic Gobi 2000 Modem device */
	अणुQMI_GOBI_DEVICE(0x05c6, 0x9225)पूर्ण,	/* Sony Gobi 2000 Modem device (N0279, VU730) */
	अणुQMI_GOBI_DEVICE(0x05c6, 0x9245)पूर्ण,	/* Samsung Gobi 2000 Modem device (VL176) */
	अणुQMI_GOBI_DEVICE(0x03f0, 0x251d)पूर्ण,	/* HP Gobi 2000 Modem device (VP412) */
	अणुQMI_GOBI_DEVICE(0x05c6, 0x9215)पूर्ण,	/* Acer Gobi 2000 Modem device (VP413) */
	अणुQMI_FIXED_INTF(0x05c6, 0x9215, 4)पूर्ण,	/* Quectel EC20 Mini PCIe */
	अणुQMI_GOBI_DEVICE(0x05c6, 0x9265)पूर्ण,	/* Asus Gobi 2000 Modem device (VR305) */
	अणुQMI_GOBI_DEVICE(0x05c6, 0x9235)पूर्ण,	/* Top Global Gobi 2000 Modem device (VR306) */
	अणुQMI_GOBI_DEVICE(0x05c6, 0x9275)पूर्ण,	/* iRex Technologies Gobi 2000 Modem device (VR307) */
	अणुQMI_GOBI_DEVICE(0x0af0, 0x8120)पूर्ण,	/* Option GTM681W */
	अणुQMI_GOBI_DEVICE(0x1199, 0x68a5)पूर्ण,	/* Sierra Wireless Modem */
	अणुQMI_GOBI_DEVICE(0x1199, 0x68a9)पूर्ण,	/* Sierra Wireless Modem */
	अणुQMI_GOBI_DEVICE(0x1199, 0x9001)पूर्ण,	/* Sierra Wireless Gobi 2000 Modem device (VT773) */
	अणुQMI_GOBI_DEVICE(0x1199, 0x9002)पूर्ण,	/* Sierra Wireless Gobi 2000 Modem device (VT773) */
	अणुQMI_GOBI_DEVICE(0x1199, 0x9003)पूर्ण,	/* Sierra Wireless Gobi 2000 Modem device (VT773) */
	अणुQMI_GOBI_DEVICE(0x1199, 0x9004)पूर्ण,	/* Sierra Wireless Gobi 2000 Modem device (VT773) */
	अणुQMI_GOBI_DEVICE(0x1199, 0x9005)पूर्ण,	/* Sierra Wireless Gobi 2000 Modem device (VT773) */
	अणुQMI_GOBI_DEVICE(0x1199, 0x9006)पूर्ण,	/* Sierra Wireless Gobi 2000 Modem device (VT773) */
	अणुQMI_GOBI_DEVICE(0x1199, 0x9007)पूर्ण,	/* Sierra Wireless Gobi 2000 Modem device (VT773) */
	अणुQMI_GOBI_DEVICE(0x1199, 0x9008)पूर्ण,	/* Sierra Wireless Gobi 2000 Modem device (VT773) */
	अणुQMI_GOBI_DEVICE(0x1199, 0x9009)पूर्ण,	/* Sierra Wireless Gobi 2000 Modem device (VT773) */
	अणुQMI_GOBI_DEVICE(0x1199, 0x900a)पूर्ण,	/* Sierra Wireless Gobi 2000 Modem device (VT773) */
	अणुQMI_GOBI_DEVICE(0x1199, 0x9011)पूर्ण,	/* Sierra Wireless Gobi 2000 Modem device (MC8305) */
	अणुQMI_GOBI_DEVICE(0x16d8, 0x8002)पूर्ण,	/* CMDTech Gobi 2000 Modem device (VU922) */
	अणुQMI_GOBI_DEVICE(0x05c6, 0x9205)पूर्ण,	/* Gobi 2000 Modem device */
	अणुQMI_GOBI_DEVICE(0x1199, 0x9013)पूर्ण,	/* Sierra Wireless Gobi 3000 Modem device (MC8355) */
	अणुQMI_GOBI_DEVICE(0x03f0, 0x371d)पूर्ण,	/* HP un2430 Mobile Broadband Module */
	अणुQMI_GOBI_DEVICE(0x1199, 0x9015)पूर्ण,	/* Sierra Wireless Gobi 3000 Modem device */
	अणुQMI_GOBI_DEVICE(0x1199, 0x9019)पूर्ण,	/* Sierra Wireless Gobi 3000 Modem device */
	अणुQMI_GOBI_DEVICE(0x1199, 0x901b)पूर्ण,	/* Sierra Wireless MC7770 */
	अणुQMI_GOBI_DEVICE(0x12d1, 0x14f1)पूर्ण,	/* Sony Gobi 3000 Composite */
	अणुQMI_GOBI_DEVICE(0x1410, 0xa021)पूर्ण,	/* Foxconn Gobi 3000 Modem device (Novatel E396) */

	अणु पूर्ण					/* END */
पूर्ण;
MODULE_DEVICE_TABLE(usb, products);

अटल bool quectel_ec20_detected(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_device *dev = पूर्णांकerface_to_usbdev(पूर्णांकf);

	अगर (dev->actconfig &&
	    le16_to_cpu(dev->descriptor.idVenकरोr) == 0x05c6 &&
	    le16_to_cpu(dev->descriptor.idProduct) == 0x9215 &&
	    dev->actconfig->desc.bNumInterfaces == 5)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक qmi_wwan_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			  स्थिर काष्ठा usb_device_id *prod)
अणु
	काष्ठा usb_device_id *id = (काष्ठा usb_device_id *)prod;
	काष्ठा usb_पूर्णांकerface_descriptor *desc = &पूर्णांकf->cur_altsetting->desc;

	/* Workaround to enable dynamic IDs.  This disables usbnet
	 * blacklisting functionality.  Which, अगर required, can be
	 * reimplemented here by using a magic "blacklist" value
	 * instead of 0 in the अटल device id table
	 */
	अगर (!id->driver_info) अणु
		dev_dbg(&पूर्णांकf->dev, "setting defaults for dynamic device id\n");
		id->driver_info = (अचिन्हित दीर्घ)&qmi_wwan_info;
	पूर्ण

	/* There are devices where the same पूर्णांकerface number can be
	 * configured as dअगरferent functions. We should only bind to
	 * venकरोr specअगरic functions when matching on पूर्णांकerface number
	 */
	अगर (id->match_flags & USB_DEVICE_ID_MATCH_INT_NUMBER &&
	    desc->bInterfaceClass != USB_CLASS_VENDOR_SPEC) अणु
		dev_dbg(&पूर्णांकf->dev,
			"Rejecting interface number match for class %02x\n",
			desc->bInterfaceClass);
		वापस -ENODEV;
	पूर्ण

	/* Quectel EC20 quirk where we've QMI on पूर्णांकerface 4 instead of 0 */
	अगर (quectel_ec20_detected(पूर्णांकf) && desc->bInterfaceNumber == 0) अणु
		dev_dbg(&पूर्णांकf->dev, "Quectel EC20 quirk, skipping interface 0\n");
		वापस -ENODEV;
	पूर्ण

	/* Several Quectel modems supports dynamic पूर्णांकerface configuration, so
	 * we need to match on class/subclass/protocol. These values are
	 * identical क्रम the diagnostic- and QMI-पूर्णांकerface, but bNumEndpoपूर्णांकs is
	 * dअगरferent. Ignore the current पूर्णांकerface अगर the number of endpoपूर्णांकs
	 * equals the number क्रम the diag पूर्णांकerface (two).
	 */
	अगर (desc->bNumEndpoपूर्णांकs == 2)
		वापस -ENODEV;

	वापस usbnet_probe(पूर्णांकf, id);
पूर्ण

अटल व्योम qmi_wwan_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usbnet *dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा qmi_wwan_state *info;
	काष्ठा list_head *iter;
	काष्ठा net_device *ldev;
	LIST_HEAD(list);

	/* called twice अगर separate control and data पूर्णांकf */
	अगर (!dev)
		वापस;
	info = (व्योम *)&dev->data;
	अगर (info->flags & QMI_WWAN_FLAG_MUX) अणु
		अगर (!rtnl_trylock()) अणु
			restart_syscall();
			वापस;
		पूर्ण
		rcu_पढ़ो_lock();
		netdev_क्रम_each_upper_dev_rcu(dev->net, ldev, iter)
			qmimux_unरेजिस्टर_device(ldev, &list);
		rcu_पढ़ो_unlock();
		unरेजिस्टर_netdevice_many(&list);
		rtnl_unlock();
		info->flags &= ~QMI_WWAN_FLAG_MUX;
	पूर्ण
	usbnet_disconnect(पूर्णांकf);
पूर्ण

अटल काष्ठा usb_driver qmi_wwan_driver = अणु
	.name		      = "qmi_wwan",
	.id_table	      = products,
	.probe		      = qmi_wwan_probe,
	.disconnect	      = qmi_wwan_disconnect,
	.suspend	      = qmi_wwan_suspend,
	.resume		      =	qmi_wwan_resume,
	.reset_resume         = qmi_wwan_resume,
	.supports_स्वतःsuspend = 1,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(qmi_wwan_driver);

MODULE_AUTHOR("Bjथचrn Mork <bjorn@mork.no>");
MODULE_DESCRIPTION("Qualcomm MSM Interface (QMI) WWAN driver");
MODULE_LICENSE("GPL");
