<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2019 Synopsys, Inc. and/or its affiliates.
 * sपंचांगmac Selftests Support
 *
 * Author: Jose Abreu <joabreu@synopsys.com>
 *
 * Ported from sपंचांगmac by:
 * Copyright (C) 2021 Oleksij Rempel <o.rempel@pengutronix.de>
 */

#समावेश <linux/phy.h>
#समावेश <net/selftests.h>
#समावेश <net/tcp.h>
#समावेश <net/udp.h>

काष्ठा net_packet_attrs अणु
	अचिन्हित अक्षर *src;
	अचिन्हित अक्षर *dst;
	u32 ip_src;
	u32 ip_dst;
	bool tcp;
	u16 sport;
	u16 dport;
	पूर्णांक समयout;
	पूर्णांक size;
	पूर्णांक max_size;
	u8 id;
	u16 queue_mapping;
पूर्ण;

काष्ठा net_test_priv अणु
	काष्ठा net_packet_attrs *packet;
	काष्ठा packet_type pt;
	काष्ठा completion comp;
	पूर्णांक द्विगुन_vlan;
	पूर्णांक vlan_id;
	पूर्णांक ok;
पूर्ण;

काष्ठा netsfhdr अणु
	__be32 version;
	__be64 magic;
	u8 id;
पूर्ण __packed;

अटल u8 net_test_next_id;

#घोषणा NET_TEST_PKT_SIZE (माप(काष्ठा ethhdr) + माप(काष्ठा iphdr) + \
			   माप(काष्ठा netsfhdr))
#घोषणा NET_TEST_PKT_MAGIC	0xdeadcafecafedeadULL
#घोषणा NET_LB_TIMEOUT		msecs_to_jअगरfies(200)

अटल काष्ठा sk_buff *net_test_get_skb(काष्ठा net_device *ndev,
					काष्ठा net_packet_attrs *attr)
अणु
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा udphdr *uhdr = शून्य;
	काष्ठा tcphdr *thdr = शून्य;
	काष्ठा netsfhdr *shdr;
	काष्ठा ethhdr *ehdr;
	काष्ठा iphdr *ihdr;
	पूर्णांक iplen, size;

	size = attr->size + NET_TEST_PKT_SIZE;

	अगर (attr->tcp)
		size += माप(काष्ठा tcphdr);
	अन्यथा
		size += माप(काष्ठा udphdr);

	अगर (attr->max_size && attr->max_size > size)
		size = attr->max_size;

	skb = netdev_alloc_skb(ndev, size);
	अगर (!skb)
		वापस शून्य;

	prefetchw(skb->data);

	ehdr = skb_push(skb, ETH_HLEN);
	skb_reset_mac_header(skb);

	skb_set_network_header(skb, skb->len);
	ihdr = skb_put(skb, माप(*ihdr));

	skb_set_transport_header(skb, skb->len);
	अगर (attr->tcp)
		thdr = skb_put(skb, माप(*thdr));
	अन्यथा
		uhdr = skb_put(skb, माप(*uhdr));

	eth_zero_addr(ehdr->h_dest);

	अगर (attr->src)
		ether_addr_copy(ehdr->h_source, attr->src);
	अगर (attr->dst)
		ether_addr_copy(ehdr->h_dest, attr->dst);

	ehdr->h_proto = htons(ETH_P_IP);

	अगर (attr->tcp) अणु
		thdr->source = htons(attr->sport);
		thdr->dest = htons(attr->dport);
		thdr->करोff = माप(काष्ठा tcphdr) / 4;
		thdr->check = 0;
	पूर्ण अन्यथा अणु
		uhdr->source = htons(attr->sport);
		uhdr->dest = htons(attr->dport);
		uhdr->len = htons(माप(*shdr) + माप(*uhdr) + attr->size);
		अगर (attr->max_size)
			uhdr->len = htons(attr->max_size -
					  (माप(*ihdr) + माप(*ehdr)));
		uhdr->check = 0;
	पूर्ण

	ihdr->ihl = 5;
	ihdr->ttl = 32;
	ihdr->version = 4;
	अगर (attr->tcp)
		ihdr->protocol = IPPROTO_TCP;
	अन्यथा
		ihdr->protocol = IPPROTO_UDP;
	iplen = माप(*ihdr) + माप(*shdr) + attr->size;
	अगर (attr->tcp)
		iplen += माप(*thdr);
	अन्यथा
		iplen += माप(*uhdr);

	अगर (attr->max_size)
		iplen = attr->max_size - माप(*ehdr);

	ihdr->tot_len = htons(iplen);
	ihdr->frag_off = 0;
	ihdr->saddr = htonl(attr->ip_src);
	ihdr->daddr = htonl(attr->ip_dst);
	ihdr->tos = 0;
	ihdr->id = 0;
	ip_send_check(ihdr);

	shdr = skb_put(skb, माप(*shdr));
	shdr->version = 0;
	shdr->magic = cpu_to_be64(NET_TEST_PKT_MAGIC);
	attr->id = net_test_next_id;
	shdr->id = net_test_next_id++;

	अगर (attr->size)
		skb_put(skb, attr->size);
	अगर (attr->max_size && attr->max_size > skb->len)
		skb_put(skb, attr->max_size - skb->len);

	skb->csum = 0;
	skb->ip_summed = CHECKSUM_PARTIAL;
	अगर (attr->tcp) अणु
		thdr->check = ~tcp_v4_check(skb->len, ihdr->saddr,
					    ihdr->daddr, 0);
		skb->csum_start = skb_transport_header(skb) - skb->head;
		skb->csum_offset = दुरत्व(काष्ठा tcphdr, check);
	पूर्ण अन्यथा अणु
		udp4_hwcsum(skb, ihdr->saddr, ihdr->daddr);
	पूर्ण

	skb->protocol = htons(ETH_P_IP);
	skb->pkt_type = PACKET_HOST;
	skb->dev = ndev;

	वापस skb;
पूर्ण

अटल पूर्णांक net_test_loopback_validate(काष्ठा sk_buff *skb,
				      काष्ठा net_device *ndev,
				      काष्ठा packet_type *pt,
				      काष्ठा net_device *orig_ndev)
अणु
	काष्ठा net_test_priv *tpriv = pt->af_packet_priv;
	अचिन्हित अक्षर *src = tpriv->packet->src;
	अचिन्हित अक्षर *dst = tpriv->packet->dst;
	काष्ठा netsfhdr *shdr;
	काष्ठा ethhdr *ehdr;
	काष्ठा udphdr *uhdr;
	काष्ठा tcphdr *thdr;
	काष्ठा iphdr *ihdr;

	skb = skb_unshare(skb, GFP_ATOMIC);
	अगर (!skb)
		जाओ out;

	अगर (skb_linearize(skb))
		जाओ out;
	अगर (skb_headlen(skb) < (NET_TEST_PKT_SIZE - ETH_HLEN))
		जाओ out;

	ehdr = (काष्ठा ethhdr *)skb_mac_header(skb);
	अगर (dst) अणु
		अगर (!ether_addr_equal_unaligned(ehdr->h_dest, dst))
			जाओ out;
	पूर्ण

	अगर (src) अणु
		अगर (!ether_addr_equal_unaligned(ehdr->h_source, src))
			जाओ out;
	पूर्ण

	ihdr = ip_hdr(skb);
	अगर (tpriv->द्विगुन_vlan)
		ihdr = (काष्ठा iphdr *)(skb_network_header(skb) + 4);

	अगर (tpriv->packet->tcp) अणु
		अगर (ihdr->protocol != IPPROTO_TCP)
			जाओ out;

		thdr = (काष्ठा tcphdr *)((u8 *)ihdr + 4 * ihdr->ihl);
		अगर (thdr->dest != htons(tpriv->packet->dport))
			जाओ out;

		shdr = (काष्ठा netsfhdr *)((u8 *)thdr + माप(*thdr));
	पूर्ण अन्यथा अणु
		अगर (ihdr->protocol != IPPROTO_UDP)
			जाओ out;

		uhdr = (काष्ठा udphdr *)((u8 *)ihdr + 4 * ihdr->ihl);
		अगर (uhdr->dest != htons(tpriv->packet->dport))
			जाओ out;

		shdr = (काष्ठा netsfhdr *)((u8 *)uhdr + माप(*uhdr));
	पूर्ण

	अगर (shdr->magic != cpu_to_be64(NET_TEST_PKT_MAGIC))
		जाओ out;
	अगर (tpriv->packet->id != shdr->id)
		जाओ out;

	tpriv->ok = true;
	complete(&tpriv->comp);
out:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक __net_test_loopback(काष्ठा net_device *ndev,
			       काष्ठा net_packet_attrs *attr)
अणु
	काष्ठा net_test_priv *tpriv;
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक ret = 0;

	tpriv = kzalloc(माप(*tpriv), GFP_KERNEL);
	अगर (!tpriv)
		वापस -ENOMEM;

	tpriv->ok = false;
	init_completion(&tpriv->comp);

	tpriv->pt.type = htons(ETH_P_IP);
	tpriv->pt.func = net_test_loopback_validate;
	tpriv->pt.dev = ndev;
	tpriv->pt.af_packet_priv = tpriv;
	tpriv->packet = attr;
	dev_add_pack(&tpriv->pt);

	skb = net_test_get_skb(ndev, attr);
	अगर (!skb) अणु
		ret = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	ret = dev_direct_xmit(skb, attr->queue_mapping);
	अगर (ret < 0) अणु
		जाओ cleanup;
	पूर्ण अन्यथा अगर (ret > 0) अणु
		ret = -ENETUNREACH;
		जाओ cleanup;
	पूर्ण

	अगर (!attr->समयout)
		attr->समयout = NET_LB_TIMEOUT;

	रुको_क्रम_completion_समयout(&tpriv->comp, attr->समयout);
	ret = tpriv->ok ? 0 : -ETIMEDOUT;

cleanup:
	dev_हटाओ_pack(&tpriv->pt);
	kमुक्त(tpriv);
	वापस ret;
पूर्ण

अटल पूर्णांक net_test_netअगर_carrier(काष्ठा net_device *ndev)
अणु
	वापस netअगर_carrier_ok(ndev) ? 0 : -ENOLINK;
पूर्ण

अटल पूर्णांक net_test_phy_phydev(काष्ठा net_device *ndev)
अणु
	वापस ndev->phydev ? 0 : -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक net_test_phy_loopback_enable(काष्ठा net_device *ndev)
अणु
	अगर (!ndev->phydev)
		वापस -EOPNOTSUPP;

	वापस phy_loopback(ndev->phydev, true);
पूर्ण

अटल पूर्णांक net_test_phy_loopback_disable(काष्ठा net_device *ndev)
अणु
	अगर (!ndev->phydev)
		वापस -EOPNOTSUPP;

	वापस phy_loopback(ndev->phydev, false);
पूर्ण

अटल पूर्णांक net_test_phy_loopback_udp(काष्ठा net_device *ndev)
अणु
	काष्ठा net_packet_attrs attr = अणु पूर्ण;

	attr.dst = ndev->dev_addr;
	वापस __net_test_loopback(ndev, &attr);
पूर्ण

अटल पूर्णांक net_test_phy_loopback_tcp(काष्ठा net_device *ndev)
अणु
	काष्ठा net_packet_attrs attr = अणु पूर्ण;

	attr.dst = ndev->dev_addr;
	attr.tcp = true;
	वापस __net_test_loopback(ndev, &attr);
पूर्ण

अटल स्थिर काष्ठा net_test अणु
	अक्षर name[ETH_GSTRING_LEN];
	पूर्णांक (*fn)(काष्ठा net_device *ndev);
पूर्ण net_selftests[] = अणु
	अणु
		.name = "Carrier                       ",
		.fn = net_test_netअगर_carrier,
	पूर्ण, अणु
		.name = "PHY dev is present            ",
		.fn = net_test_phy_phydev,
	पूर्ण, अणु
		/* This test should be करोne beक्रमe all PHY loopback test */
		.name = "PHY internal loopback, enable ",
		.fn = net_test_phy_loopback_enable,
	पूर्ण, अणु
		.name = "PHY internal loopback, UDP    ",
		.fn = net_test_phy_loopback_udp,
	पूर्ण, अणु
		.name = "PHY internal loopback, TCP    ",
		.fn = net_test_phy_loopback_tcp,
	पूर्ण, अणु
		/* This test should be करोne after all PHY loopback test */
		.name = "PHY internal loopback, disable",
		.fn = net_test_phy_loopback_disable,
	पूर्ण,
पूर्ण;

व्योम net_selftest(काष्ठा net_device *ndev, काष्ठा ethtool_test *etest, u64 *buf)
अणु
	पूर्णांक count = net_selftest_get_count();
	पूर्णांक i;

	स_रखो(buf, 0, माप(*buf) * count);
	net_test_next_id = 0;

	अगर (etest->flags != ETH_TEST_FL_OFFLINE) अणु
		netdev_err(ndev, "Only offline tests are supported\n");
		etest->flags |= ETH_TEST_FL_FAILED;
		वापस;
	पूर्ण


	क्रम (i = 0; i < count; i++) अणु
		buf[i] = net_selftests[i].fn(ndev);
		अगर (buf[i] && (buf[i] != -EOPNOTSUPP))
			etest->flags |= ETH_TEST_FL_FAILED;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(net_selftest);

पूर्णांक net_selftest_get_count(व्योम)
अणु
	वापस ARRAY_SIZE(net_selftests);
पूर्ण
EXPORT_SYMBOL_GPL(net_selftest_get_count);

व्योम net_selftest_get_strings(u8 *data)
अणु
	u8 *p = data;
	पूर्णांक i;

	क्रम (i = 0; i < net_selftest_get_count(); i++) अणु
		snम_लिखो(p, ETH_GSTRING_LEN, "%2d. %s", i + 1,
			 net_selftests[i].name);
		p += ETH_GSTRING_LEN;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(net_selftest_get_strings);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Oleksij Rempel <o.rempel@pengutronix.de>");
