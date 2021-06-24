<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2019 Synopsys, Inc. and/or its affiliates.
 * sपंचांगmac Selftests Support
 *
 * Author: Jose Abreu <joabreu@synopsys.com>
 */

#समावेश <linux/bitrev.h>
#समावेश <linux/completion.h>
#समावेश <linux/crc32.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/ip.h>
#समावेश <linux/phy.h>
#समावेश <linux/udp.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/tcp.h>
#समावेश <net/udp.h>
#समावेश <net/tc_act/tc_gact.h>
#समावेश "stmmac.h"

काष्ठा sपंचांगmachdr अणु
	__be32 version;
	__be64 magic;
	u8 id;
पूर्ण __packed;

#घोषणा STMMAC_TEST_PKT_SIZE (माप(काष्ठा ethhdr) + माप(काष्ठा iphdr) + \
			      माप(काष्ठा sपंचांगmachdr))
#घोषणा STMMAC_TEST_PKT_MAGIC	0xdeadcafecafedeadULL
#घोषणा STMMAC_LB_TIMEOUT	msecs_to_jअगरfies(200)

काष्ठा sपंचांगmac_packet_attrs अणु
	पूर्णांक vlan;
	पूर्णांक vlan_id_in;
	पूर्णांक vlan_id_out;
	अचिन्हित अक्षर *src;
	अचिन्हित अक्षर *dst;
	u32 ip_src;
	u32 ip_dst;
	पूर्णांक tcp;
	पूर्णांक sport;
	पूर्णांक dport;
	u32 exp_hash;
	पूर्णांक करोnt_रुको;
	पूर्णांक समयout;
	पूर्णांक size;
	पूर्णांक max_size;
	पूर्णांक हटाओ_sa;
	u8 id;
	पूर्णांक sarc;
	u16 queue_mapping;
	u64 बारtamp;
पूर्ण;

अटल u8 sपंचांगmac_test_next_id;

अटल काष्ठा sk_buff *sपंचांगmac_test_get_udp_skb(काष्ठा sपंचांगmac_priv *priv,
					       काष्ठा sपंचांगmac_packet_attrs *attr)
अणु
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा udphdr *uhdr = शून्य;
	काष्ठा tcphdr *thdr = शून्य;
	काष्ठा sपंचांगmachdr *shdr;
	काष्ठा ethhdr *ehdr;
	काष्ठा iphdr *ihdr;
	पूर्णांक iplen, size;

	size = attr->size + STMMAC_TEST_PKT_SIZE;
	अगर (attr->vlan) अणु
		size += 4;
		अगर (attr->vlan > 1)
			size += 4;
	पूर्ण

	अगर (attr->tcp)
		size += माप(काष्ठा tcphdr);
	अन्यथा
		size += माप(काष्ठा udphdr);

	अगर (attr->max_size && (attr->max_size > size))
		size = attr->max_size;

	skb = netdev_alloc_skb(priv->dev, size);
	अगर (!skb)
		वापस शून्य;

	prefetchw(skb->data);

	अगर (attr->vlan > 1)
		ehdr = skb_push(skb, ETH_HLEN + 8);
	अन्यथा अगर (attr->vlan)
		ehdr = skb_push(skb, ETH_HLEN + 4);
	अन्यथा अगर (attr->हटाओ_sa)
		ehdr = skb_push(skb, ETH_HLEN - 6);
	अन्यथा
		ehdr = skb_push(skb, ETH_HLEN);
	skb_reset_mac_header(skb);

	skb_set_network_header(skb, skb->len);
	ihdr = skb_put(skb, माप(*ihdr));

	skb_set_transport_header(skb, skb->len);
	अगर (attr->tcp)
		thdr = skb_put(skb, माप(*thdr));
	अन्यथा
		uhdr = skb_put(skb, माप(*uhdr));

	अगर (!attr->हटाओ_sa)
		eth_zero_addr(ehdr->h_source);
	eth_zero_addr(ehdr->h_dest);
	अगर (attr->src && !attr->हटाओ_sa)
		ether_addr_copy(ehdr->h_source, attr->src);
	अगर (attr->dst)
		ether_addr_copy(ehdr->h_dest, attr->dst);

	अगर (!attr->हटाओ_sa) अणु
		ehdr->h_proto = htons(ETH_P_IP);
	पूर्ण अन्यथा अणु
		__be16 *ptr = (__be16 *)ehdr;

		/* HACK */
		ptr[3] = htons(ETH_P_IP);
	पूर्ण

	अगर (attr->vlan) अणु
		__be16 *tag, *proto;

		अगर (!attr->हटाओ_sa) अणु
			tag = (व्योम *)ehdr + ETH_HLEN;
			proto = (व्योम *)ehdr + (2 * ETH_ALEN);
		पूर्ण अन्यथा अणु
			tag = (व्योम *)ehdr + ETH_HLEN - 6;
			proto = (व्योम *)ehdr + ETH_ALEN;
		पूर्ण

		proto[0] = htons(ETH_P_8021Q);
		tag[0] = htons(attr->vlan_id_out);
		tag[1] = htons(ETH_P_IP);
		अगर (attr->vlan > 1) अणु
			proto[0] = htons(ETH_P_8021AD);
			tag[1] = htons(ETH_P_8021Q);
			tag[2] = htons(attr->vlan_id_in);
			tag[3] = htons(ETH_P_IP);
		पूर्ण
	पूर्ण

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
	shdr->magic = cpu_to_be64(STMMAC_TEST_PKT_MAGIC);
	attr->id = sपंचांगmac_test_next_id;
	shdr->id = sपंचांगmac_test_next_id++;

	अगर (attr->size)
		skb_put(skb, attr->size);
	अगर (attr->max_size && (attr->max_size > skb->len))
		skb_put(skb, attr->max_size - skb->len);

	skb->csum = 0;
	skb->ip_summed = CHECKSUM_PARTIAL;
	अगर (attr->tcp) अणु
		thdr->check = ~tcp_v4_check(skb->len, ihdr->saddr, ihdr->daddr, 0);
		skb->csum_start = skb_transport_header(skb) - skb->head;
		skb->csum_offset = दुरत्व(काष्ठा tcphdr, check);
	पूर्ण अन्यथा अणु
		udp4_hwcsum(skb, ihdr->saddr, ihdr->daddr);
	पूर्ण

	skb->protocol = htons(ETH_P_IP);
	skb->pkt_type = PACKET_HOST;
	skb->dev = priv->dev;

	अगर (attr->बारtamp)
		skb->tstamp = ns_to_kसमय(attr->बारtamp);

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *sपंचांगmac_test_get_arp_skb(काष्ठा sपंचांगmac_priv *priv,
					       काष्ठा sपंचांगmac_packet_attrs *attr)
अणु
	__be32 ip_src = htonl(attr->ip_src);
	__be32 ip_dst = htonl(attr->ip_dst);
	काष्ठा sk_buff *skb = शून्य;

	skb = arp_create(ARPOP_REQUEST, ETH_P_ARP, ip_dst, priv->dev, ip_src,
			 शून्य, attr->src, attr->dst);
	अगर (!skb)
		वापस शून्य;

	skb->pkt_type = PACKET_HOST;
	skb->dev = priv->dev;

	वापस skb;
पूर्ण

काष्ठा sपंचांगmac_test_priv अणु
	काष्ठा sपंचांगmac_packet_attrs *packet;
	काष्ठा packet_type pt;
	काष्ठा completion comp;
	पूर्णांक द्विगुन_vlan;
	पूर्णांक vlan_id;
	पूर्णांक ok;
पूर्ण;

अटल पूर्णांक sपंचांगmac_test_loopback_validate(काष्ठा sk_buff *skb,
					 काष्ठा net_device *ndev,
					 काष्ठा packet_type *pt,
					 काष्ठा net_device *orig_ndev)
अणु
	काष्ठा sपंचांगmac_test_priv *tpriv = pt->af_packet_priv;
	अचिन्हित अक्षर *src = tpriv->packet->src;
	अचिन्हित अक्षर *dst = tpriv->packet->dst;
	काष्ठा sपंचांगmachdr *shdr;
	काष्ठा ethhdr *ehdr;
	काष्ठा udphdr *uhdr;
	काष्ठा tcphdr *thdr;
	काष्ठा iphdr *ihdr;

	skb = skb_unshare(skb, GFP_ATOMIC);
	अगर (!skb)
		जाओ out;

	अगर (skb_linearize(skb))
		जाओ out;
	अगर (skb_headlen(skb) < (STMMAC_TEST_PKT_SIZE - ETH_HLEN))
		जाओ out;

	ehdr = (काष्ठा ethhdr *)skb_mac_header(skb);
	अगर (dst) अणु
		अगर (!ether_addr_equal_unaligned(ehdr->h_dest, dst))
			जाओ out;
	पूर्ण
	अगर (tpriv->packet->sarc) अणु
		अगर (!ether_addr_equal_unaligned(ehdr->h_source, ehdr->h_dest))
			जाओ out;
	पूर्ण अन्यथा अगर (src) अणु
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

		shdr = (काष्ठा sपंचांगmachdr *)((u8 *)thdr + माप(*thdr));
	पूर्ण अन्यथा अणु
		अगर (ihdr->protocol != IPPROTO_UDP)
			जाओ out;

		uhdr = (काष्ठा udphdr *)((u8 *)ihdr + 4 * ihdr->ihl);
		अगर (uhdr->dest != htons(tpriv->packet->dport))
			जाओ out;

		shdr = (काष्ठा sपंचांगmachdr *)((u8 *)uhdr + माप(*uhdr));
	पूर्ण

	अगर (shdr->magic != cpu_to_be64(STMMAC_TEST_PKT_MAGIC))
		जाओ out;
	अगर (tpriv->packet->exp_hash && !skb->hash)
		जाओ out;
	अगर (tpriv->packet->id != shdr->id)
		जाओ out;

	tpriv->ok = true;
	complete(&tpriv->comp);
out:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक __sपंचांगmac_test_loopback(काष्ठा sपंचांगmac_priv *priv,
				  काष्ठा sपंचांगmac_packet_attrs *attr)
अणु
	काष्ठा sपंचांगmac_test_priv *tpriv;
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक ret = 0;

	tpriv = kzalloc(माप(*tpriv), GFP_KERNEL);
	अगर (!tpriv)
		वापस -ENOMEM;

	tpriv->ok = false;
	init_completion(&tpriv->comp);

	tpriv->pt.type = htons(ETH_P_IP);
	tpriv->pt.func = sपंचांगmac_test_loopback_validate;
	tpriv->pt.dev = priv->dev;
	tpriv->pt.af_packet_priv = tpriv;
	tpriv->packet = attr;

	अगर (!attr->करोnt_रुको)
		dev_add_pack(&tpriv->pt);

	skb = sपंचांगmac_test_get_udp_skb(priv, attr);
	अगर (!skb) अणु
		ret = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	ret = dev_direct_xmit(skb, attr->queue_mapping);
	अगर (ret)
		जाओ cleanup;

	अगर (attr->करोnt_रुको)
		जाओ cleanup;

	अगर (!attr->समयout)
		attr->समयout = STMMAC_LB_TIMEOUT;

	रुको_क्रम_completion_समयout(&tpriv->comp, attr->समयout);
	ret = tpriv->ok ? 0 : -ETIMEDOUT;

cleanup:
	अगर (!attr->करोnt_रुको)
		dev_हटाओ_pack(&tpriv->pt);
	kमुक्त(tpriv);
	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांगmac_test_mac_loopback(काष्ठा sपंचांगmac_priv *priv)
अणु
	काष्ठा sपंचांगmac_packet_attrs attr = अणु पूर्ण;

	attr.dst = priv->dev->dev_addr;
	वापस __sपंचांगmac_test_loopback(priv, &attr);
पूर्ण

अटल पूर्णांक sपंचांगmac_test_phy_loopback(काष्ठा sपंचांगmac_priv *priv)
अणु
	काष्ठा sपंचांगmac_packet_attrs attr = अणु पूर्ण;
	पूर्णांक ret;

	अगर (!priv->dev->phydev)
		वापस -EOPNOTSUPP;

	ret = phy_loopback(priv->dev->phydev, true);
	अगर (ret)
		वापस ret;

	attr.dst = priv->dev->dev_addr;
	ret = __sपंचांगmac_test_loopback(priv, &attr);

	phy_loopback(priv->dev->phydev, false);
	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांगmac_test_mmc(काष्ठा sपंचांगmac_priv *priv)
अणु
	काष्ठा sपंचांगmac_counters initial, final;
	पूर्णांक ret;

	स_रखो(&initial, 0, माप(initial));
	स_रखो(&final, 0, माप(final));

	अगर (!priv->dma_cap.rmon)
		वापस -EOPNOTSUPP;

	/* Save previous results पूर्णांकo पूर्णांकernal काष्ठा */
	sपंचांगmac_mmc_पढ़ो(priv, priv->mmcaddr, &priv->mmc);

	ret = sपंचांगmac_test_mac_loopback(priv);
	अगर (ret)
		वापस ret;

	/* These will be loopback results so no need to save them */
	sपंचांगmac_mmc_पढ़ो(priv, priv->mmcaddr, &final);

	/*
	 * The number of MMC counters available depends on HW configuration
	 * so we just use this one to validate the feature. I hope there is
	 * not a version without this counter.
	 */
	अगर (final.mmc_tx_framecount_g <= initial.mmc_tx_framecount_g)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगmac_test_eee(काष्ठा sपंचांगmac_priv *priv)
अणु
	काष्ठा sपंचांगmac_extra_stats *initial, *final;
	पूर्णांक retries = 10;
	पूर्णांक ret;

	अगर (!priv->dma_cap.eee || !priv->eee_active)
		वापस -EOPNOTSUPP;

	initial = kzalloc(माप(*initial), GFP_KERNEL);
	अगर (!initial)
		वापस -ENOMEM;

	final = kzalloc(माप(*final), GFP_KERNEL);
	अगर (!final) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_initial;
	पूर्ण

	स_नकल(initial, &priv->xstats, माप(*initial));

	ret = sपंचांगmac_test_mac_loopback(priv);
	अगर (ret)
		जाओ out_मुक्त_final;

	/* We have no traffic in the line so, sooner or later it will go LPI */
	जबतक (--retries) अणु
		स_नकल(final, &priv->xstats, माप(*final));

		अगर (final->irq_tx_path_in_lpi_mode_n >
		    initial->irq_tx_path_in_lpi_mode_n)
			अवरोध;
		msleep(100);
	पूर्ण

	अगर (!retries) अणु
		ret = -ETIMEDOUT;
		जाओ out_मुक्त_final;
	पूर्ण

	अगर (final->irq_tx_path_in_lpi_mode_n <=
	    initial->irq_tx_path_in_lpi_mode_n) अणु
		ret = -EINVAL;
		जाओ out_मुक्त_final;
	पूर्ण

	अगर (final->irq_tx_path_निकास_lpi_mode_n <=
	    initial->irq_tx_path_निकास_lpi_mode_n) अणु
		ret = -EINVAL;
		जाओ out_मुक्त_final;
	पूर्ण

out_मुक्त_final:
	kमुक्त(final);
out_मुक्त_initial:
	kमुक्त(initial);
	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांगmac_filter_check(काष्ठा sपंचांगmac_priv *priv)
अणु
	अगर (!(priv->dev->flags & IFF_PROMISC))
		वापस 0;

	netdev_warn(priv->dev, "Test can't be run in promiscuous mode!\n");
	वापस -EOPNOTSUPP;
पूर्ण

अटल bool sपंचांगmac_hash_check(काष्ठा sपंचांगmac_priv *priv, अचिन्हित अक्षर *addr)
अणु
	पूर्णांक mc_offset = 32 - priv->hw->mcast_bits_log2;
	काष्ठा netdev_hw_addr *ha;
	u32 hash, hash_nr;

	/* First compute the hash क्रम desired addr */
	hash = bitrev32(~crc32_le(~0, addr, 6)) >> mc_offset;
	hash_nr = hash >> 5;
	hash = 1 << (hash & 0x1f);

	/* Now, check अगर it collides with any existing one */
	netdev_क्रम_each_mc_addr(ha, priv->dev) अणु
		u32 nr = bitrev32(~crc32_le(~0, ha->addr, ETH_ALEN)) >> mc_offset;
		अगर (((nr >> 5) == hash_nr) && ((1 << (nr & 0x1f)) == hash))
			वापस false;
	पूर्ण

	/* No collisions, address is good to go */
	वापस true;
पूर्ण

अटल bool sपंचांगmac_perfect_check(काष्ठा sपंचांगmac_priv *priv, अचिन्हित अक्षर *addr)
अणु
	काष्ठा netdev_hw_addr *ha;

	/* Check अगर it collides with any existing one */
	netdev_क्रम_each_uc_addr(ha, priv->dev) अणु
		अगर (!स_भेद(ha->addr, addr, ETH_ALEN))
			वापस false;
	पूर्ण

	/* No collisions, address is good to go */
	वापस true;
पूर्ण

अटल पूर्णांक sपंचांगmac_test_hfilt(काष्ठा sपंचांगmac_priv *priv)
अणु
	अचिन्हित अक्षर gd_addr[ETH_ALEN] = अणु0xf1, 0xee, 0xdd, 0xcc, 0xbb, 0xaaपूर्ण;
	अचिन्हित अक्षर bd_addr[ETH_ALEN] = अणु0xf1, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;
	काष्ठा sपंचांगmac_packet_attrs attr = अणु पूर्ण;
	पूर्णांक ret, tries = 256;

	ret = sपंचांगmac_filter_check(priv);
	अगर (ret)
		वापस ret;

	अगर (netdev_mc_count(priv->dev) >= priv->hw->multicast_filter_bins)
		वापस -EOPNOTSUPP;

	जबतक (--tries) अणु
		/* We only need to check the bd_addr क्रम collisions */
		bd_addr[ETH_ALEN - 1] = tries;
		अगर (sपंचांगmac_hash_check(priv, bd_addr))
			अवरोध;
	पूर्ण

	अगर (!tries)
		वापस -EOPNOTSUPP;

	ret = dev_mc_add(priv->dev, gd_addr);
	अगर (ret)
		वापस ret;

	attr.dst = gd_addr;

	/* Shall receive packet */
	ret = __sपंचांगmac_test_loopback(priv, &attr);
	अगर (ret)
		जाओ cleanup;

	attr.dst = bd_addr;

	/* Shall NOT receive packet */
	ret = __sपंचांगmac_test_loopback(priv, &attr);
	ret = ret ? 0 : -EINVAL;

cleanup:
	dev_mc_del(priv->dev, gd_addr);
	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांगmac_test_pfilt(काष्ठा sपंचांगmac_priv *priv)
अणु
	अचिन्हित अक्षर gd_addr[ETH_ALEN] = अणु0xf0, 0x01, 0x44, 0x55, 0x66, 0x77पूर्ण;
	अचिन्हित अक्षर bd_addr[ETH_ALEN] = अणु0xf0, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;
	काष्ठा sपंचांगmac_packet_attrs attr = अणु पूर्ण;
	पूर्णांक ret, tries = 256;

	अगर (sपंचांगmac_filter_check(priv))
		वापस -EOPNOTSUPP;
	अगर (netdev_uc_count(priv->dev) >= priv->hw->unicast_filter_entries)
		वापस -EOPNOTSUPP;

	जबतक (--tries) अणु
		/* We only need to check the bd_addr क्रम collisions */
		bd_addr[ETH_ALEN - 1] = tries;
		अगर (sपंचांगmac_perfect_check(priv, bd_addr))
			अवरोध;
	पूर्ण

	अगर (!tries)
		वापस -EOPNOTSUPP;

	ret = dev_uc_add(priv->dev, gd_addr);
	अगर (ret)
		वापस ret;

	attr.dst = gd_addr;

	/* Shall receive packet */
	ret = __sपंचांगmac_test_loopback(priv, &attr);
	अगर (ret)
		जाओ cleanup;

	attr.dst = bd_addr;

	/* Shall NOT receive packet */
	ret = __sपंचांगmac_test_loopback(priv, &attr);
	ret = ret ? 0 : -EINVAL;

cleanup:
	dev_uc_del(priv->dev, gd_addr);
	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांगmac_test_mcfilt(काष्ठा sपंचांगmac_priv *priv)
अणु
	अचिन्हित अक्षर uc_addr[ETH_ALEN] = अणु0xf0, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;
	अचिन्हित अक्षर mc_addr[ETH_ALEN] = अणु0xf1, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;
	काष्ठा sपंचांगmac_packet_attrs attr = अणु पूर्ण;
	पूर्णांक ret, tries = 256;

	अगर (sपंचांगmac_filter_check(priv))
		वापस -EOPNOTSUPP;
	अगर (netdev_uc_count(priv->dev) >= priv->hw->unicast_filter_entries)
		वापस -EOPNOTSUPP;
	अगर (netdev_mc_count(priv->dev) >= priv->hw->multicast_filter_bins)
		वापस -EOPNOTSUPP;

	जबतक (--tries) अणु
		/* We only need to check the mc_addr क्रम collisions */
		mc_addr[ETH_ALEN - 1] = tries;
		अगर (sपंचांगmac_hash_check(priv, mc_addr))
			अवरोध;
	पूर्ण

	अगर (!tries)
		वापस -EOPNOTSUPP;

	ret = dev_uc_add(priv->dev, uc_addr);
	अगर (ret)
		वापस ret;

	attr.dst = uc_addr;

	/* Shall receive packet */
	ret = __sपंचांगmac_test_loopback(priv, &attr);
	अगर (ret)
		जाओ cleanup;

	attr.dst = mc_addr;

	/* Shall NOT receive packet */
	ret = __sपंचांगmac_test_loopback(priv, &attr);
	ret = ret ? 0 : -EINVAL;

cleanup:
	dev_uc_del(priv->dev, uc_addr);
	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांगmac_test_ucfilt(काष्ठा sपंचांगmac_priv *priv)
अणु
	अचिन्हित अक्षर uc_addr[ETH_ALEN] = अणु0xf0, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;
	अचिन्हित अक्षर mc_addr[ETH_ALEN] = अणु0xf1, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;
	काष्ठा sपंचांगmac_packet_attrs attr = अणु पूर्ण;
	पूर्णांक ret, tries = 256;

	अगर (sपंचांगmac_filter_check(priv))
		वापस -EOPNOTSUPP;
	अगर (netdev_uc_count(priv->dev) >= priv->hw->unicast_filter_entries)
		वापस -EOPNOTSUPP;
	अगर (netdev_mc_count(priv->dev) >= priv->hw->multicast_filter_bins)
		वापस -EOPNOTSUPP;

	जबतक (--tries) अणु
		/* We only need to check the uc_addr क्रम collisions */
		uc_addr[ETH_ALEN - 1] = tries;
		अगर (sपंचांगmac_perfect_check(priv, uc_addr))
			अवरोध;
	पूर्ण

	अगर (!tries)
		वापस -EOPNOTSUPP;

	ret = dev_mc_add(priv->dev, mc_addr);
	अगर (ret)
		वापस ret;

	attr.dst = mc_addr;

	/* Shall receive packet */
	ret = __sपंचांगmac_test_loopback(priv, &attr);
	अगर (ret)
		जाओ cleanup;

	attr.dst = uc_addr;

	/* Shall NOT receive packet */
	ret = __sपंचांगmac_test_loopback(priv, &attr);
	ret = ret ? 0 : -EINVAL;

cleanup:
	dev_mc_del(priv->dev, mc_addr);
	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांगmac_test_flowctrl_validate(काष्ठा sk_buff *skb,
					 काष्ठा net_device *ndev,
					 काष्ठा packet_type *pt,
					 काष्ठा net_device *orig_ndev)
अणु
	काष्ठा sपंचांगmac_test_priv *tpriv = pt->af_packet_priv;
	काष्ठा ethhdr *ehdr;

	ehdr = (काष्ठा ethhdr *)skb_mac_header(skb);
	अगर (!ether_addr_equal_unaligned(ehdr->h_source, orig_ndev->dev_addr))
		जाओ out;
	अगर (ehdr->h_proto != htons(ETH_P_PAUSE))
		जाओ out;

	tpriv->ok = true;
	complete(&tpriv->comp);
out:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगmac_test_flowctrl(काष्ठा sपंचांगmac_priv *priv)
अणु
	अचिन्हित अक्षर paddr[ETH_ALEN] = अणु0x01, 0x80, 0xC2, 0x00, 0x00, 0x01पूर्ण;
	काष्ठा phy_device *phydev = priv->dev->phydev;
	u32 rx_cnt = priv->plat->rx_queues_to_use;
	काष्ठा sपंचांगmac_test_priv *tpriv;
	अचिन्हित पूर्णांक pkt_count;
	पूर्णांक i, ret = 0;

	अगर (!phydev || (!phydev->छोड़ो && !phydev->asym_छोड़ो))
		वापस -EOPNOTSUPP;

	tpriv = kzalloc(माप(*tpriv), GFP_KERNEL);
	अगर (!tpriv)
		वापस -ENOMEM;

	tpriv->ok = false;
	init_completion(&tpriv->comp);
	tpriv->pt.type = htons(ETH_P_PAUSE);
	tpriv->pt.func = sपंचांगmac_test_flowctrl_validate;
	tpriv->pt.dev = priv->dev;
	tpriv->pt.af_packet_priv = tpriv;
	dev_add_pack(&tpriv->pt);

	/* Compute minimum number of packets to make FIFO full */
	pkt_count = priv->plat->rx_fअगरo_size;
	अगर (!pkt_count)
		pkt_count = priv->dma_cap.rx_fअगरo_size;
	pkt_count /= 1400;
	pkt_count *= 2;

	क्रम (i = 0; i < rx_cnt; i++)
		sपंचांगmac_stop_rx(priv, priv->ioaddr, i);

	ret = dev_set_promiscuity(priv->dev, 1);
	अगर (ret)
		जाओ cleanup;

	ret = dev_mc_add(priv->dev, paddr);
	अगर (ret)
		जाओ cleanup;

	क्रम (i = 0; i < pkt_count; i++) अणु
		काष्ठा sपंचांगmac_packet_attrs attr = अणु पूर्ण;

		attr.dst = priv->dev->dev_addr;
		attr.करोnt_रुको = true;
		attr.size = 1400;

		ret = __sपंचांगmac_test_loopback(priv, &attr);
		अगर (ret)
			जाओ cleanup;
		अगर (tpriv->ok)
			अवरोध;
	पूर्ण

	/* Wait क्रम some समय in हाल RX Watchकरोg is enabled */
	msleep(200);

	क्रम (i = 0; i < rx_cnt; i++) अणु
		काष्ठा sपंचांगmac_channel *ch = &priv->channel[i];
		u32 tail;

		tail = priv->rx_queue[i].dma_rx_phy +
			(priv->dma_rx_size * माप(काष्ठा dma_desc));

		sपंचांगmac_set_rx_tail_ptr(priv, priv->ioaddr, tail, i);
		sपंचांगmac_start_rx(priv, priv->ioaddr, i);

		local_bh_disable();
		napi_reschedule(&ch->rx_napi);
		local_bh_enable();
	पूर्ण

	रुको_क्रम_completion_समयout(&tpriv->comp, STMMAC_LB_TIMEOUT);
	ret = tpriv->ok ? 0 : -ETIMEDOUT;

cleanup:
	dev_mc_del(priv->dev, paddr);
	dev_set_promiscuity(priv->dev, -1);
	dev_हटाओ_pack(&tpriv->pt);
	kमुक्त(tpriv);
	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांगmac_test_rss(काष्ठा sपंचांगmac_priv *priv)
अणु
	काष्ठा sपंचांगmac_packet_attrs attr = अणु पूर्ण;

	अगर (!priv->dma_cap.rssen || !priv->rss.enable)
		वापस -EOPNOTSUPP;

	attr.dst = priv->dev->dev_addr;
	attr.exp_hash = true;
	attr.sport = 0x321;
	attr.dport = 0x123;

	वापस __sपंचांगmac_test_loopback(priv, &attr);
पूर्ण

अटल पूर्णांक sपंचांगmac_test_vlan_validate(काष्ठा sk_buff *skb,
				     काष्ठा net_device *ndev,
				     काष्ठा packet_type *pt,
				     काष्ठा net_device *orig_ndev)
अणु
	काष्ठा sपंचांगmac_test_priv *tpriv = pt->af_packet_priv;
	काष्ठा sपंचांगmachdr *shdr;
	काष्ठा ethhdr *ehdr;
	काष्ठा udphdr *uhdr;
	काष्ठा iphdr *ihdr;
	u16 proto;

	proto = tpriv->द्विगुन_vlan ? ETH_P_8021AD : ETH_P_8021Q;

	skb = skb_unshare(skb, GFP_ATOMIC);
	अगर (!skb)
		जाओ out;

	अगर (skb_linearize(skb))
		जाओ out;
	अगर (skb_headlen(skb) < (STMMAC_TEST_PKT_SIZE - ETH_HLEN))
		जाओ out;
	अगर (tpriv->vlan_id) अणु
		अगर (skb->vlan_proto != htons(proto))
			जाओ out;
		अगर (skb->vlan_tci != tpriv->vlan_id) अणु
			/* Means filter did not work. */
			tpriv->ok = false;
			complete(&tpriv->comp);
			जाओ out;
		पूर्ण
	पूर्ण

	ehdr = (काष्ठा ethhdr *)skb_mac_header(skb);
	अगर (!ether_addr_equal_unaligned(ehdr->h_dest, tpriv->packet->dst))
		जाओ out;

	ihdr = ip_hdr(skb);
	अगर (tpriv->द्विगुन_vlan)
		ihdr = (काष्ठा iphdr *)(skb_network_header(skb) + 4);
	अगर (ihdr->protocol != IPPROTO_UDP)
		जाओ out;

	uhdr = (काष्ठा udphdr *)((u8 *)ihdr + 4 * ihdr->ihl);
	अगर (uhdr->dest != htons(tpriv->packet->dport))
		जाओ out;

	shdr = (काष्ठा sपंचांगmachdr *)((u8 *)uhdr + माप(*uhdr));
	अगर (shdr->magic != cpu_to_be64(STMMAC_TEST_PKT_MAGIC))
		जाओ out;

	tpriv->ok = true;
	complete(&tpriv->comp);

out:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक __sपंचांगmac_test_vlanfilt(काष्ठा sपंचांगmac_priv *priv)
अणु
	काष्ठा sपंचांगmac_packet_attrs attr = अणु पूर्ण;
	काष्ठा sपंचांगmac_test_priv *tpriv;
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक ret = 0, i;

	tpriv = kzalloc(माप(*tpriv), GFP_KERNEL);
	अगर (!tpriv)
		वापस -ENOMEM;

	tpriv->ok = false;
	init_completion(&tpriv->comp);

	tpriv->pt.type = htons(ETH_P_IP);
	tpriv->pt.func = sपंचांगmac_test_vlan_validate;
	tpriv->pt.dev = priv->dev;
	tpriv->pt.af_packet_priv = tpriv;
	tpriv->packet = &attr;

	/*
	 * As we use HASH filtering, false positives may appear. This is a
	 * specially chosen ID so that adjacent IDs (+4) have dअगरferent
	 * HASH values.
	 */
	tpriv->vlan_id = 0x123;
	dev_add_pack(&tpriv->pt);

	ret = vlan_vid_add(priv->dev, htons(ETH_P_8021Q), tpriv->vlan_id);
	अगर (ret)
		जाओ cleanup;

	क्रम (i = 0; i < 4; i++) अणु
		attr.vlan = 1;
		attr.vlan_id_out = tpriv->vlan_id + i;
		attr.dst = priv->dev->dev_addr;
		attr.sport = 9;
		attr.dport = 9;

		skb = sपंचांगmac_test_get_udp_skb(priv, &attr);
		अगर (!skb) अणु
			ret = -ENOMEM;
			जाओ vlan_del;
		पूर्ण

		ret = dev_direct_xmit(skb, 0);
		अगर (ret)
			जाओ vlan_del;

		रुको_क्रम_completion_समयout(&tpriv->comp, STMMAC_LB_TIMEOUT);
		ret = tpriv->ok ? 0 : -ETIMEDOUT;
		अगर (ret && !i) अणु
			जाओ vlan_del;
		पूर्ण अन्यथा अगर (!ret && i) अणु
			ret = -EINVAL;
			जाओ vlan_del;
		पूर्ण अन्यथा अणु
			ret = 0;
		पूर्ण

		tpriv->ok = false;
	पूर्ण

vlan_del:
	vlan_vid_del(priv->dev, htons(ETH_P_8021Q), tpriv->vlan_id);
cleanup:
	dev_हटाओ_pack(&tpriv->pt);
	kमुक्त(tpriv);
	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांगmac_test_vlanfilt(काष्ठा sपंचांगmac_priv *priv)
अणु
	अगर (!priv->dma_cap.vlhash)
		वापस -EOPNOTSUPP;

	वापस __sपंचांगmac_test_vlanfilt(priv);
पूर्ण

अटल पूर्णांक sपंचांगmac_test_vlanfilt_perfect(काष्ठा sपंचांगmac_priv *priv)
अणु
	पूर्णांक ret, prev_cap = priv->dma_cap.vlhash;

	अगर (!(priv->dev->features & NETIF_F_HW_VLAN_CTAG_FILTER))
		वापस -EOPNOTSUPP;

	priv->dma_cap.vlhash = 0;
	ret = __sपंचांगmac_test_vlanfilt(priv);
	priv->dma_cap.vlhash = prev_cap;

	वापस ret;
पूर्ण

अटल पूर्णांक __sपंचांगmac_test_dvlanfilt(काष्ठा sपंचांगmac_priv *priv)
अणु
	काष्ठा sपंचांगmac_packet_attrs attr = अणु पूर्ण;
	काष्ठा sपंचांगmac_test_priv *tpriv;
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक ret = 0, i;

	tpriv = kzalloc(माप(*tpriv), GFP_KERNEL);
	अगर (!tpriv)
		वापस -ENOMEM;

	tpriv->ok = false;
	tpriv->द्विगुन_vlan = true;
	init_completion(&tpriv->comp);

	tpriv->pt.type = htons(ETH_P_8021Q);
	tpriv->pt.func = sपंचांगmac_test_vlan_validate;
	tpriv->pt.dev = priv->dev;
	tpriv->pt.af_packet_priv = tpriv;
	tpriv->packet = &attr;

	/*
	 * As we use HASH filtering, false positives may appear. This is a
	 * specially chosen ID so that adjacent IDs (+4) have dअगरferent
	 * HASH values.
	 */
	tpriv->vlan_id = 0x123;
	dev_add_pack(&tpriv->pt);

	ret = vlan_vid_add(priv->dev, htons(ETH_P_8021AD), tpriv->vlan_id);
	अगर (ret)
		जाओ cleanup;

	क्रम (i = 0; i < 4; i++) अणु
		attr.vlan = 2;
		attr.vlan_id_out = tpriv->vlan_id + i;
		attr.dst = priv->dev->dev_addr;
		attr.sport = 9;
		attr.dport = 9;

		skb = sपंचांगmac_test_get_udp_skb(priv, &attr);
		अगर (!skb) अणु
			ret = -ENOMEM;
			जाओ vlan_del;
		पूर्ण

		ret = dev_direct_xmit(skb, 0);
		अगर (ret)
			जाओ vlan_del;

		रुको_क्रम_completion_समयout(&tpriv->comp, STMMAC_LB_TIMEOUT);
		ret = tpriv->ok ? 0 : -ETIMEDOUT;
		अगर (ret && !i) अणु
			जाओ vlan_del;
		पूर्ण अन्यथा अगर (!ret && i) अणु
			ret = -EINVAL;
			जाओ vlan_del;
		पूर्ण अन्यथा अणु
			ret = 0;
		पूर्ण

		tpriv->ok = false;
	पूर्ण

vlan_del:
	vlan_vid_del(priv->dev, htons(ETH_P_8021AD), tpriv->vlan_id);
cleanup:
	dev_हटाओ_pack(&tpriv->pt);
	kमुक्त(tpriv);
	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांगmac_test_dvlanfilt(काष्ठा sपंचांगmac_priv *priv)
अणु
	अगर (!priv->dma_cap.vlhash)
		वापस -EOPNOTSUPP;

	वापस __sपंचांगmac_test_dvlanfilt(priv);
पूर्ण

अटल पूर्णांक sपंचांगmac_test_dvlanfilt_perfect(काष्ठा sपंचांगmac_priv *priv)
अणु
	पूर्णांक ret, prev_cap = priv->dma_cap.vlhash;

	अगर (!(priv->dev->features & NETIF_F_HW_VLAN_STAG_FILTER))
		वापस -EOPNOTSUPP;

	priv->dma_cap.vlhash = 0;
	ret = __sपंचांगmac_test_dvlanfilt(priv);
	priv->dma_cap.vlhash = prev_cap;

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_NET_CLS_ACT
अटल पूर्णांक sपंचांगmac_test_rxp(काष्ठा sपंचांगmac_priv *priv)
अणु
	अचिन्हित अक्षर addr[ETH_ALEN] = अणु0xde, 0xad, 0xbe, 0xef, 0x00, 0x00पूर्ण;
	काष्ठा tc_cls_u32_offload cls_u32 = अणु पूर्ण;
	काष्ठा sपंचांगmac_packet_attrs attr = अणु पूर्ण;
	काष्ठा tc_action **actions, *act;
	काष्ठा tc_u32_sel *sel;
	काष्ठा tcf_exts *exts;
	पूर्णांक ret, i, nk = 1;

	अगर (!tc_can_offload(priv->dev))
		वापस -EOPNOTSUPP;
	अगर (!priv->dma_cap.frpsel)
		वापस -EOPNOTSUPP;

	sel = kzalloc(काष्ठा_size(sel, keys, nk), GFP_KERNEL);
	अगर (!sel)
		वापस -ENOMEM;

	exts = kzalloc(माप(*exts), GFP_KERNEL);
	अगर (!exts) अणु
		ret = -ENOMEM;
		जाओ cleanup_sel;
	पूर्ण

	actions = kzalloc(nk * माप(*actions), GFP_KERNEL);
	अगर (!actions) अणु
		ret = -ENOMEM;
		जाओ cleanup_exts;
	पूर्ण

	act = kzalloc(nk * माप(*act), GFP_KERNEL);
	अगर (!act) अणु
		ret = -ENOMEM;
		जाओ cleanup_actions;
	पूर्ण

	cls_u32.command = TC_CLSU32_NEW_KNODE;
	cls_u32.common.chain_index = 0;
	cls_u32.common.protocol = htons(ETH_P_ALL);
	cls_u32.knode.exts = exts;
	cls_u32.knode.sel = sel;
	cls_u32.knode.handle = 0x123;

	exts->nr_actions = nk;
	exts->actions = actions;
	क्रम (i = 0; i < nk; i++) अणु
		काष्ठा tcf_gact *gact = to_gact(&act[i]);

		actions[i] = &act[i];
		gact->tcf_action = TC_ACT_SHOT;
	पूर्ण

	sel->nkeys = nk;
	sel->offshअगरt = 0;
	sel->keys[0].off = 6;
	sel->keys[0].val = htonl(0xdeadbeef);
	sel->keys[0].mask = ~0x0;

	ret = sपंचांगmac_tc_setup_cls_u32(priv, priv, &cls_u32);
	अगर (ret)
		जाओ cleanup_act;

	attr.dst = priv->dev->dev_addr;
	attr.src = addr;

	ret = __sपंचांगmac_test_loopback(priv, &attr);
	ret = ret ? 0 : -EINVAL; /* Shall NOT receive packet */

	cls_u32.command = TC_CLSU32_DELETE_KNODE;
	sपंचांगmac_tc_setup_cls_u32(priv, priv, &cls_u32);

cleanup_act:
	kमुक्त(act);
cleanup_actions:
	kमुक्त(actions);
cleanup_exts:
	kमुक्त(exts);
cleanup_sel:
	kमुक्त(sel);
	वापस ret;
पूर्ण
#अन्यथा
अटल पूर्णांक sपंचांगmac_test_rxp(काष्ठा sपंचांगmac_priv *priv)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक sपंचांगmac_test_desc_sai(काष्ठा sपंचांगmac_priv *priv)
अणु
	अचिन्हित अक्षर src[ETH_ALEN] = अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x00पूर्ण;
	काष्ठा sपंचांगmac_packet_attrs attr = अणु पूर्ण;
	पूर्णांक ret;

	अगर (!priv->dma_cap.vlins)
		वापस -EOPNOTSUPP;

	attr.हटाओ_sa = true;
	attr.sarc = true;
	attr.src = src;
	attr.dst = priv->dev->dev_addr;

	priv->sarc_type = 0x1;

	ret = __sपंचांगmac_test_loopback(priv, &attr);

	priv->sarc_type = 0x0;
	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांगmac_test_desc_sar(काष्ठा sपंचांगmac_priv *priv)
अणु
	अचिन्हित अक्षर src[ETH_ALEN] = अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x00पूर्ण;
	काष्ठा sपंचांगmac_packet_attrs attr = अणु पूर्ण;
	पूर्णांक ret;

	अगर (!priv->dma_cap.vlins)
		वापस -EOPNOTSUPP;

	attr.sarc = true;
	attr.src = src;
	attr.dst = priv->dev->dev_addr;

	priv->sarc_type = 0x2;

	ret = __sपंचांगmac_test_loopback(priv, &attr);

	priv->sarc_type = 0x0;
	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांगmac_test_reg_sai(काष्ठा sपंचांगmac_priv *priv)
अणु
	अचिन्हित अक्षर src[ETH_ALEN] = अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x00पूर्ण;
	काष्ठा sपंचांगmac_packet_attrs attr = अणु पूर्ण;
	पूर्णांक ret;

	अगर (!priv->dma_cap.vlins)
		वापस -EOPNOTSUPP;

	attr.हटाओ_sa = true;
	attr.sarc = true;
	attr.src = src;
	attr.dst = priv->dev->dev_addr;

	अगर (sपंचांगmac_sarc_configure(priv, priv->ioaddr, 0x2))
		वापस -EOPNOTSUPP;

	ret = __sपंचांगmac_test_loopback(priv, &attr);

	sपंचांगmac_sarc_configure(priv, priv->ioaddr, 0x0);
	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांगmac_test_reg_sar(काष्ठा sपंचांगmac_priv *priv)
अणु
	अचिन्हित अक्षर src[ETH_ALEN] = अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x00पूर्ण;
	काष्ठा sपंचांगmac_packet_attrs attr = अणु पूर्ण;
	पूर्णांक ret;

	अगर (!priv->dma_cap.vlins)
		वापस -EOPNOTSUPP;

	attr.sarc = true;
	attr.src = src;
	attr.dst = priv->dev->dev_addr;

	अगर (sपंचांगmac_sarc_configure(priv, priv->ioaddr, 0x3))
		वापस -EOPNOTSUPP;

	ret = __sपंचांगmac_test_loopback(priv, &attr);

	sपंचांगmac_sarc_configure(priv, priv->ioaddr, 0x0);
	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांगmac_test_vlanoff_common(काष्ठा sपंचांगmac_priv *priv, bool svlan)
अणु
	काष्ठा sपंचांगmac_packet_attrs attr = अणु पूर्ण;
	काष्ठा sपंचांगmac_test_priv *tpriv;
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक ret = 0;
	u16 proto;

	अगर (!priv->dma_cap.vlins)
		वापस -EOPNOTSUPP;

	tpriv = kzalloc(माप(*tpriv), GFP_KERNEL);
	अगर (!tpriv)
		वापस -ENOMEM;

	proto = svlan ? ETH_P_8021AD : ETH_P_8021Q;

	tpriv->ok = false;
	tpriv->द्विगुन_vlan = svlan;
	init_completion(&tpriv->comp);

	tpriv->pt.type = svlan ? htons(ETH_P_8021Q) : htons(ETH_P_IP);
	tpriv->pt.func = sपंचांगmac_test_vlan_validate;
	tpriv->pt.dev = priv->dev;
	tpriv->pt.af_packet_priv = tpriv;
	tpriv->packet = &attr;
	tpriv->vlan_id = 0x123;
	dev_add_pack(&tpriv->pt);

	ret = vlan_vid_add(priv->dev, htons(proto), tpriv->vlan_id);
	अगर (ret)
		जाओ cleanup;

	attr.dst = priv->dev->dev_addr;

	skb = sपंचांगmac_test_get_udp_skb(priv, &attr);
	अगर (!skb) अणु
		ret = -ENOMEM;
		जाओ vlan_del;
	पूर्ण

	__vlan_hwaccel_put_tag(skb, htons(proto), tpriv->vlan_id);
	skb->protocol = htons(proto);

	ret = dev_direct_xmit(skb, 0);
	अगर (ret)
		जाओ vlan_del;

	रुको_क्रम_completion_समयout(&tpriv->comp, STMMAC_LB_TIMEOUT);
	ret = tpriv->ok ? 0 : -ETIMEDOUT;

vlan_del:
	vlan_vid_del(priv->dev, htons(proto), tpriv->vlan_id);
cleanup:
	dev_हटाओ_pack(&tpriv->pt);
	kमुक्त(tpriv);
	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांगmac_test_vlanoff(काष्ठा sपंचांगmac_priv *priv)
अणु
	वापस sपंचांगmac_test_vlanoff_common(priv, false);
पूर्ण

अटल पूर्णांक sपंचांगmac_test_svlanoff(काष्ठा sपंचांगmac_priv *priv)
अणु
	अगर (!priv->dma_cap.dvlan)
		वापस -EOPNOTSUPP;
	वापस sपंचांगmac_test_vlanoff_common(priv, true);
पूर्ण

#अगर_घोषित CONFIG_NET_CLS_ACT
अटल पूर्णांक __sपंचांगmac_test_l3filt(काष्ठा sपंचांगmac_priv *priv, u32 dst, u32 src,
				u32 dst_mask, u32 src_mask)
अणु
	काष्ठा flow_dissector_key_ipv4_addrs key, mask;
	अचिन्हित दीर्घ dummy_cookie = 0xdeadbeef;
	काष्ठा sपंचांगmac_packet_attrs attr = अणु पूर्ण;
	काष्ठा flow_dissector *dissector;
	काष्ठा flow_cls_offload *cls;
	पूर्णांक ret, old_enable = 0;
	काष्ठा flow_rule *rule;

	अगर (!tc_can_offload(priv->dev))
		वापस -EOPNOTSUPP;
	अगर (!priv->dma_cap.l3l4fnum)
		वापस -EOPNOTSUPP;
	अगर (priv->rss.enable) अणु
		old_enable = priv->rss.enable;
		priv->rss.enable = false;
		sपंचांगmac_rss_configure(priv, priv->hw, शून्य,
				     priv->plat->rx_queues_to_use);
	पूर्ण

	dissector = kzalloc(माप(*dissector), GFP_KERNEL);
	अगर (!dissector) अणु
		ret = -ENOMEM;
		जाओ cleanup_rss;
	पूर्ण

	dissector->used_keys |= (1 << FLOW_DISSECTOR_KEY_IPV4_ADDRS);
	dissector->offset[FLOW_DISSECTOR_KEY_IPV4_ADDRS] = 0;

	cls = kzalloc(माप(*cls), GFP_KERNEL);
	अगर (!cls) अणु
		ret = -ENOMEM;
		जाओ cleanup_dissector;
	पूर्ण

	cls->common.chain_index = 0;
	cls->command = FLOW_CLS_REPLACE;
	cls->cookie = dummy_cookie;

	rule = kzalloc(काष्ठा_size(rule, action.entries, 1), GFP_KERNEL);
	अगर (!rule) अणु
		ret = -ENOMEM;
		जाओ cleanup_cls;
	पूर्ण

	rule->match.dissector = dissector;
	rule->match.key = (व्योम *)&key;
	rule->match.mask = (व्योम *)&mask;

	key.src = htonl(src);
	key.dst = htonl(dst);
	mask.src = src_mask;
	mask.dst = dst_mask;

	cls->rule = rule;

	rule->action.entries[0].id = FLOW_ACTION_DROP;
	rule->action.entries[0].hw_stats = FLOW_ACTION_HW_STATS_ANY;
	rule->action.num_entries = 1;

	attr.dst = priv->dev->dev_addr;
	attr.ip_dst = dst;
	attr.ip_src = src;

	/* Shall receive packet */
	ret = __sपंचांगmac_test_loopback(priv, &attr);
	अगर (ret)
		जाओ cleanup_rule;

	ret = sपंचांगmac_tc_setup_cls(priv, priv, cls);
	अगर (ret)
		जाओ cleanup_rule;

	/* Shall NOT receive packet */
	ret = __sपंचांगmac_test_loopback(priv, &attr);
	ret = ret ? 0 : -EINVAL;

	cls->command = FLOW_CLS_DESTROY;
	sपंचांगmac_tc_setup_cls(priv, priv, cls);
cleanup_rule:
	kमुक्त(rule);
cleanup_cls:
	kमुक्त(cls);
cleanup_dissector:
	kमुक्त(dissector);
cleanup_rss:
	अगर (old_enable) अणु
		priv->rss.enable = old_enable;
		sपंचांगmac_rss_configure(priv, priv->hw, &priv->rss,
				     priv->plat->rx_queues_to_use);
	पूर्ण

	वापस ret;
पूर्ण
#अन्यथा
अटल पूर्णांक __sपंचांगmac_test_l3filt(काष्ठा sपंचांगmac_priv *priv, u32 dst, u32 src,
				u32 dst_mask, u32 src_mask)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक sपंचांगmac_test_l3filt_da(काष्ठा sपंचांगmac_priv *priv)
अणु
	u32 addr = 0x10203040;

	वापस __sपंचांगmac_test_l3filt(priv, addr, 0, ~0, 0);
पूर्ण

अटल पूर्णांक sपंचांगmac_test_l3filt_sa(काष्ठा sपंचांगmac_priv *priv)
अणु
	u32 addr = 0x10203040;

	वापस __sपंचांगmac_test_l3filt(priv, 0, addr, 0, ~0);
पूर्ण

#अगर_घोषित CONFIG_NET_CLS_ACT
अटल पूर्णांक __sपंचांगmac_test_l4filt(काष्ठा sपंचांगmac_priv *priv, u32 dst, u32 src,
				u32 dst_mask, u32 src_mask, bool udp)
अणु
	काष्ठा अणु
		काष्ठा flow_dissector_key_basic bkey;
		काष्ठा flow_dissector_key_ports key;
	पूर्ण __aligned(BITS_PER_LONG / 8) keys;
	काष्ठा अणु
		काष्ठा flow_dissector_key_basic bmask;
		काष्ठा flow_dissector_key_ports mask;
	पूर्ण __aligned(BITS_PER_LONG / 8) masks;
	अचिन्हित दीर्घ dummy_cookie = 0xdeadbeef;
	काष्ठा sपंचांगmac_packet_attrs attr = अणु पूर्ण;
	काष्ठा flow_dissector *dissector;
	काष्ठा flow_cls_offload *cls;
	पूर्णांक ret, old_enable = 0;
	काष्ठा flow_rule *rule;

	अगर (!tc_can_offload(priv->dev))
		वापस -EOPNOTSUPP;
	अगर (!priv->dma_cap.l3l4fnum)
		वापस -EOPNOTSUPP;
	अगर (priv->rss.enable) अणु
		old_enable = priv->rss.enable;
		priv->rss.enable = false;
		sपंचांगmac_rss_configure(priv, priv->hw, शून्य,
				     priv->plat->rx_queues_to_use);
	पूर्ण

	dissector = kzalloc(माप(*dissector), GFP_KERNEL);
	अगर (!dissector) अणु
		ret = -ENOMEM;
		जाओ cleanup_rss;
	पूर्ण

	dissector->used_keys |= (1 << FLOW_DISSECTOR_KEY_BASIC);
	dissector->used_keys |= (1 << FLOW_DISSECTOR_KEY_PORTS);
	dissector->offset[FLOW_DISSECTOR_KEY_BASIC] = 0;
	dissector->offset[FLOW_DISSECTOR_KEY_PORTS] = दुरत्व(typeof(keys), key);

	cls = kzalloc(माप(*cls), GFP_KERNEL);
	अगर (!cls) अणु
		ret = -ENOMEM;
		जाओ cleanup_dissector;
	पूर्ण

	cls->common.chain_index = 0;
	cls->command = FLOW_CLS_REPLACE;
	cls->cookie = dummy_cookie;

	rule = kzalloc(काष्ठा_size(rule, action.entries, 1), GFP_KERNEL);
	अगर (!rule) अणु
		ret = -ENOMEM;
		जाओ cleanup_cls;
	पूर्ण

	rule->match.dissector = dissector;
	rule->match.key = (व्योम *)&keys;
	rule->match.mask = (व्योम *)&masks;

	keys.bkey.ip_proto = udp ? IPPROTO_UDP : IPPROTO_TCP;
	keys.key.src = htons(src);
	keys.key.dst = htons(dst);
	masks.mask.src = src_mask;
	masks.mask.dst = dst_mask;

	cls->rule = rule;

	rule->action.entries[0].id = FLOW_ACTION_DROP;
	rule->action.entries[0].hw_stats = FLOW_ACTION_HW_STATS_ANY;
	rule->action.num_entries = 1;

	attr.dst = priv->dev->dev_addr;
	attr.tcp = !udp;
	attr.sport = src;
	attr.dport = dst;
	attr.ip_dst = 0;

	/* Shall receive packet */
	ret = __sपंचांगmac_test_loopback(priv, &attr);
	अगर (ret)
		जाओ cleanup_rule;

	ret = sपंचांगmac_tc_setup_cls(priv, priv, cls);
	अगर (ret)
		जाओ cleanup_rule;

	/* Shall NOT receive packet */
	ret = __sपंचांगmac_test_loopback(priv, &attr);
	ret = ret ? 0 : -EINVAL;

	cls->command = FLOW_CLS_DESTROY;
	sपंचांगmac_tc_setup_cls(priv, priv, cls);
cleanup_rule:
	kमुक्त(rule);
cleanup_cls:
	kमुक्त(cls);
cleanup_dissector:
	kमुक्त(dissector);
cleanup_rss:
	अगर (old_enable) अणु
		priv->rss.enable = old_enable;
		sपंचांगmac_rss_configure(priv, priv->hw, &priv->rss,
				     priv->plat->rx_queues_to_use);
	पूर्ण

	वापस ret;
पूर्ण
#अन्यथा
अटल पूर्णांक __sपंचांगmac_test_l4filt(काष्ठा sपंचांगmac_priv *priv, u32 dst, u32 src,
				u32 dst_mask, u32 src_mask, bool udp)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक sपंचांगmac_test_l4filt_da_tcp(काष्ठा sपंचांगmac_priv *priv)
अणु
	u16 dummy_port = 0x123;

	वापस __sपंचांगmac_test_l4filt(priv, dummy_port, 0, ~0, 0, false);
पूर्ण

अटल पूर्णांक sपंचांगmac_test_l4filt_sa_tcp(काष्ठा sपंचांगmac_priv *priv)
अणु
	u16 dummy_port = 0x123;

	वापस __sपंचांगmac_test_l4filt(priv, 0, dummy_port, 0, ~0, false);
पूर्ण

अटल पूर्णांक sपंचांगmac_test_l4filt_da_udp(काष्ठा sपंचांगmac_priv *priv)
अणु
	u16 dummy_port = 0x123;

	वापस __sपंचांगmac_test_l4filt(priv, dummy_port, 0, ~0, 0, true);
पूर्ण

अटल पूर्णांक sपंचांगmac_test_l4filt_sa_udp(काष्ठा sपंचांगmac_priv *priv)
अणु
	u16 dummy_port = 0x123;

	वापस __sपंचांगmac_test_l4filt(priv, 0, dummy_port, 0, ~0, true);
पूर्ण

अटल पूर्णांक sपंचांगmac_test_arp_validate(काष्ठा sk_buff *skb,
				    काष्ठा net_device *ndev,
				    काष्ठा packet_type *pt,
				    काष्ठा net_device *orig_ndev)
अणु
	काष्ठा sपंचांगmac_test_priv *tpriv = pt->af_packet_priv;
	काष्ठा ethhdr *ehdr;
	काष्ठा arphdr *ahdr;

	ehdr = (काष्ठा ethhdr *)skb_mac_header(skb);
	अगर (!ether_addr_equal_unaligned(ehdr->h_dest, tpriv->packet->src))
		जाओ out;

	ahdr = arp_hdr(skb);
	अगर (ahdr->ar_op != htons(ARPOP_REPLY))
		जाओ out;

	tpriv->ok = true;
	complete(&tpriv->comp);
out:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगmac_test_arpoffload(काष्ठा sपंचांगmac_priv *priv)
अणु
	अचिन्हित अक्षर src[ETH_ALEN] = अणु0x01, 0x02, 0x03, 0x04, 0x05, 0x06पूर्ण;
	अचिन्हित अक्षर dst[ETH_ALEN] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;
	काष्ठा sपंचांगmac_packet_attrs attr = अणु पूर्ण;
	काष्ठा sपंचांगmac_test_priv *tpriv;
	काष्ठा sk_buff *skb = शून्य;
	u32 ip_addr = 0xdeadcafe;
	u32 ip_src = 0xdeadbeef;
	पूर्णांक ret;

	अगर (!priv->dma_cap.arpoffsel)
		वापस -EOPNOTSUPP;

	tpriv = kzalloc(माप(*tpriv), GFP_KERNEL);
	अगर (!tpriv)
		वापस -ENOMEM;

	tpriv->ok = false;
	init_completion(&tpriv->comp);

	tpriv->pt.type = htons(ETH_P_ARP);
	tpriv->pt.func = sपंचांगmac_test_arp_validate;
	tpriv->pt.dev = priv->dev;
	tpriv->pt.af_packet_priv = tpriv;
	tpriv->packet = &attr;
	dev_add_pack(&tpriv->pt);

	attr.src = src;
	attr.ip_src = ip_src;
	attr.dst = dst;
	attr.ip_dst = ip_addr;

	skb = sपंचांगmac_test_get_arp_skb(priv, &attr);
	अगर (!skb) अणु
		ret = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	ret = sपंचांगmac_set_arp_offload(priv, priv->hw, true, ip_addr);
	अगर (ret)
		जाओ cleanup;

	ret = dev_set_promiscuity(priv->dev, 1);
	अगर (ret)
		जाओ cleanup;

	ret = dev_direct_xmit(skb, 0);
	अगर (ret)
		जाओ cleanup_promisc;

	रुको_क्रम_completion_समयout(&tpriv->comp, STMMAC_LB_TIMEOUT);
	ret = tpriv->ok ? 0 : -ETIMEDOUT;

cleanup_promisc:
	dev_set_promiscuity(priv->dev, -1);
cleanup:
	sपंचांगmac_set_arp_offload(priv, priv->hw, false, 0x0);
	dev_हटाओ_pack(&tpriv->pt);
	kमुक्त(tpriv);
	वापस ret;
पूर्ण

अटल पूर्णांक __sपंचांगmac_test_jumbo(काष्ठा sपंचांगmac_priv *priv, u16 queue)
अणु
	काष्ठा sपंचांगmac_packet_attrs attr = अणु पूर्ण;
	पूर्णांक size = priv->dma_buf_sz;

	attr.dst = priv->dev->dev_addr;
	attr.max_size = size - ETH_FCS_LEN;
	attr.queue_mapping = queue;

	वापस __sपंचांगmac_test_loopback(priv, &attr);
पूर्ण

अटल पूर्णांक sपंचांगmac_test_jumbo(काष्ठा sपंचांगmac_priv *priv)
अणु
	वापस __sपंचांगmac_test_jumbo(priv, 0);
पूर्ण

अटल पूर्णांक sपंचांगmac_test_mjumbo(काष्ठा sपंचांगmac_priv *priv)
अणु
	u32 chan, tx_cnt = priv->plat->tx_queues_to_use;
	पूर्णांक ret;

	अगर (tx_cnt <= 1)
		वापस -EOPNOTSUPP;

	क्रम (chan = 0; chan < tx_cnt; chan++) अणु
		ret = __sपंचांगmac_test_jumbo(priv, chan);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगmac_test_sph(काष्ठा sपंचांगmac_priv *priv)
अणु
	अचिन्हित दीर्घ cnt_end, cnt_start = priv->xstats.rx_split_hdr_pkt_n;
	काष्ठा sपंचांगmac_packet_attrs attr = अणु पूर्ण;
	पूर्णांक ret;

	अगर (!priv->sph)
		वापस -EOPNOTSUPP;

	/* Check क्रम UDP first */
	attr.dst = priv->dev->dev_addr;
	attr.tcp = false;

	ret = __sपंचांगmac_test_loopback(priv, &attr);
	अगर (ret)
		वापस ret;

	cnt_end = priv->xstats.rx_split_hdr_pkt_n;
	अगर (cnt_end <= cnt_start)
		वापस -EINVAL;

	/* Check क्रम TCP now */
	cnt_start = cnt_end;

	attr.dst = priv->dev->dev_addr;
	attr.tcp = true;

	ret = __sपंचांगmac_test_loopback(priv, &attr);
	अगर (ret)
		वापस ret;

	cnt_end = priv->xstats.rx_split_hdr_pkt_n;
	अगर (cnt_end <= cnt_start)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगmac_test_tbs(काष्ठा sपंचांगmac_priv *priv)
अणु
#घोषणा STMMAC_TBS_LT_OFFSET		(500 * 1000 * 1000) /* 500 ms*/
	काष्ठा sपंचांगmac_packet_attrs attr = अणु पूर्ण;
	काष्ठा tc_etf_qopt_offload qopt;
	u64 start_समय, curr_समय = 0;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret, i;

	अगर (!priv->hwts_tx_en)
		वापस -EOPNOTSUPP;

	/* Find first TBS enabled Queue, अगर any */
	क्रम (i = 0; i < priv->plat->tx_queues_to_use; i++)
		अगर (priv->tx_queue[i].tbs & STMMAC_TBS_AVAIL)
			अवरोध;

	अगर (i >= priv->plat->tx_queues_to_use)
		वापस -EOPNOTSUPP;

	qopt.enable = true;
	qopt.queue = i;

	ret = sपंचांगmac_tc_setup_etf(priv, priv, &qopt);
	अगर (ret)
		वापस ret;

	spin_lock_irqsave(&priv->ptp_lock, flags);
	sपंचांगmac_get_sysसमय(priv, priv->ptpaddr, &curr_समय);
	spin_unlock_irqrestore(&priv->ptp_lock, flags);

	अगर (!curr_समय) अणु
		ret = -EOPNOTSUPP;
		जाओ fail_disable;
	पूर्ण

	start_समय = curr_समय;
	curr_समय += STMMAC_TBS_LT_OFFSET;

	attr.dst = priv->dev->dev_addr;
	attr.बारtamp = curr_समय;
	attr.समयout = nsecs_to_jअगरfies(2 * STMMAC_TBS_LT_OFFSET);
	attr.queue_mapping = i;

	ret = __sपंचांगmac_test_loopback(priv, &attr);
	अगर (ret)
		जाओ fail_disable;

	/* Check अगर expected समय has elapsed */
	spin_lock_irqsave(&priv->ptp_lock, flags);
	sपंचांगmac_get_sysसमय(priv, priv->ptpaddr, &curr_समय);
	spin_unlock_irqrestore(&priv->ptp_lock, flags);

	अगर ((curr_समय - start_समय) < STMMAC_TBS_LT_OFFSET)
		ret = -EINVAL;

fail_disable:
	qopt.enable = false;
	sपंचांगmac_tc_setup_etf(priv, priv, &qopt);
	वापस ret;
पूर्ण

#घोषणा STMMAC_LOOPBACK_NONE	0
#घोषणा STMMAC_LOOPBACK_MAC	1
#घोषणा STMMAC_LOOPBACK_PHY	2

अटल स्थिर काष्ठा sपंचांगmac_test अणु
	अक्षर name[ETH_GSTRING_LEN];
	पूर्णांक lb;
	पूर्णांक (*fn)(काष्ठा sपंचांगmac_priv *priv);
पूर्ण sपंचांगmac_selftests[] = अणु
	अणु
		.name = "MAC Loopback               ",
		.lb = STMMAC_LOOPBACK_MAC,
		.fn = sपंचांगmac_test_mac_loopback,
	पूर्ण, अणु
		.name = "PHY Loopback               ",
		.lb = STMMAC_LOOPBACK_NONE, /* Test will handle it */
		.fn = sपंचांगmac_test_phy_loopback,
	पूर्ण, अणु
		.name = "MMC Counters               ",
		.lb = STMMAC_LOOPBACK_PHY,
		.fn = sपंचांगmac_test_mmc,
	पूर्ण, अणु
		.name = "EEE                        ",
		.lb = STMMAC_LOOPBACK_PHY,
		.fn = sपंचांगmac_test_eee,
	पूर्ण, अणु
		.name = "Hash Filter MC             ",
		.lb = STMMAC_LOOPBACK_PHY,
		.fn = sपंचांगmac_test_hfilt,
	पूर्ण, अणु
		.name = "Perfect Filter UC          ",
		.lb = STMMAC_LOOPBACK_PHY,
		.fn = sपंचांगmac_test_pfilt,
	पूर्ण, अणु
		.name = "MC Filter                  ",
		.lb = STMMAC_LOOPBACK_PHY,
		.fn = sपंचांगmac_test_mcfilt,
	पूर्ण, अणु
		.name = "UC Filter                  ",
		.lb = STMMAC_LOOPBACK_PHY,
		.fn = sपंचांगmac_test_ucfilt,
	पूर्ण, अणु
		.name = "Flow Control               ",
		.lb = STMMAC_LOOPBACK_PHY,
		.fn = sपंचांगmac_test_flowctrl,
	पूर्ण, अणु
		.name = "RSS                        ",
		.lb = STMMAC_LOOPBACK_PHY,
		.fn = sपंचांगmac_test_rss,
	पूर्ण, अणु
		.name = "VLAN Filtering             ",
		.lb = STMMAC_LOOPBACK_PHY,
		.fn = sपंचांगmac_test_vlanfilt,
	पूर्ण, अणु
		.name = "VLAN Filtering (perf)      ",
		.lb = STMMAC_LOOPBACK_PHY,
		.fn = sपंचांगmac_test_vlanfilt_perfect,
	पूर्ण, अणु
		.name = "Double VLAN Filter         ",
		.lb = STMMAC_LOOPBACK_PHY,
		.fn = sपंचांगmac_test_dvlanfilt,
	पूर्ण, अणु
		.name = "Double VLAN Filter (perf)  ",
		.lb = STMMAC_LOOPBACK_PHY,
		.fn = sपंचांगmac_test_dvlanfilt_perfect,
	पूर्ण, अणु
		.name = "Flexible RX Parser         ",
		.lb = STMMAC_LOOPBACK_PHY,
		.fn = sपंचांगmac_test_rxp,
	पूर्ण, अणु
		.name = "SA Insertion (desc)        ",
		.lb = STMMAC_LOOPBACK_PHY,
		.fn = sपंचांगmac_test_desc_sai,
	पूर्ण, अणु
		.name = "SA Replacement (desc)      ",
		.lb = STMMAC_LOOPBACK_PHY,
		.fn = sपंचांगmac_test_desc_sar,
	पूर्ण, अणु
		.name = "SA Insertion (reg)         ",
		.lb = STMMAC_LOOPBACK_PHY,
		.fn = sपंचांगmac_test_reg_sai,
	पूर्ण, अणु
		.name = "SA Replacement (reg)       ",
		.lb = STMMAC_LOOPBACK_PHY,
		.fn = sपंचांगmac_test_reg_sar,
	पूर्ण, अणु
		.name = "VLAN TX Insertion          ",
		.lb = STMMAC_LOOPBACK_PHY,
		.fn = sपंचांगmac_test_vlanoff,
	पूर्ण, अणु
		.name = "SVLAN TX Insertion         ",
		.lb = STMMAC_LOOPBACK_PHY,
		.fn = sपंचांगmac_test_svlanoff,
	पूर्ण, अणु
		.name = "L3 DA Filtering            ",
		.lb = STMMAC_LOOPBACK_PHY,
		.fn = sपंचांगmac_test_l3filt_da,
	पूर्ण, अणु
		.name = "L3 SA Filtering            ",
		.lb = STMMAC_LOOPBACK_PHY,
		.fn = sपंचांगmac_test_l3filt_sa,
	पूर्ण, अणु
		.name = "L4 DA TCP Filtering        ",
		.lb = STMMAC_LOOPBACK_PHY,
		.fn = sपंचांगmac_test_l4filt_da_tcp,
	पूर्ण, अणु
		.name = "L4 SA TCP Filtering        ",
		.lb = STMMAC_LOOPBACK_PHY,
		.fn = sपंचांगmac_test_l4filt_sa_tcp,
	पूर्ण, अणु
		.name = "L4 DA UDP Filtering        ",
		.lb = STMMAC_LOOPBACK_PHY,
		.fn = sपंचांगmac_test_l4filt_da_udp,
	पूर्ण, अणु
		.name = "L4 SA UDP Filtering        ",
		.lb = STMMAC_LOOPBACK_PHY,
		.fn = sपंचांगmac_test_l4filt_sa_udp,
	पूर्ण, अणु
		.name = "ARP Offload                ",
		.lb = STMMAC_LOOPBACK_PHY,
		.fn = sपंचांगmac_test_arpoffload,
	पूर्ण, अणु
		.name = "Jumbo Frame                ",
		.lb = STMMAC_LOOPBACK_PHY,
		.fn = sपंचांगmac_test_jumbo,
	पूर्ण, अणु
		.name = "Multichannel Jumbo         ",
		.lb = STMMAC_LOOPBACK_PHY,
		.fn = sपंचांगmac_test_mjumbo,
	पूर्ण, अणु
		.name = "Split Header               ",
		.lb = STMMAC_LOOPBACK_PHY,
		.fn = sपंचांगmac_test_sph,
	पूर्ण, अणु
		.name = "TBS (ETF Scheduler)        ",
		.lb = STMMAC_LOOPBACK_PHY,
		.fn = sपंचांगmac_test_tbs,
	पूर्ण,
पूर्ण;

व्योम sपंचांगmac_selftest_run(काष्ठा net_device *dev,
			 काष्ठा ethtool_test *etest, u64 *buf)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);
	पूर्णांक count = sपंचांगmac_selftest_get_count(priv);
	पूर्णांक i, ret;

	स_रखो(buf, 0, माप(*buf) * count);
	sपंचांगmac_test_next_id = 0;

	अगर (etest->flags != ETH_TEST_FL_OFFLINE) अणु
		netdev_err(priv->dev, "Only offline tests are supported\n");
		etest->flags |= ETH_TEST_FL_FAILED;
		वापस;
	पूर्ण अन्यथा अगर (!netअगर_carrier_ok(dev)) अणु
		netdev_err(priv->dev, "You need valid Link to execute tests\n");
		etest->flags |= ETH_TEST_FL_FAILED;
		वापस;
	पूर्ण

	/* Wait क्रम queues drain */
	msleep(200);

	क्रम (i = 0; i < count; i++) अणु
		ret = 0;

		चयन (sपंचांगmac_selftests[i].lb) अणु
		हाल STMMAC_LOOPBACK_PHY:
			ret = -EOPNOTSUPP;
			अगर (dev->phydev)
				ret = phy_loopback(dev->phydev, true);
			अगर (!ret)
				अवरोध;
			fallthrough;
		हाल STMMAC_LOOPBACK_MAC:
			ret = sपंचांगmac_set_mac_loopback(priv, priv->ioaddr, true);
			अवरोध;
		हाल STMMAC_LOOPBACK_NONE:
			अवरोध;
		शेष:
			ret = -EOPNOTSUPP;
			अवरोध;
		पूर्ण

		/*
		 * First tests will always be MAC / PHY loobpack. If any of
		 * them is not supported we पात earlier.
		 */
		अगर (ret) अणु
			netdev_err(priv->dev, "Loopback is not supported\n");
			etest->flags |= ETH_TEST_FL_FAILED;
			अवरोध;
		पूर्ण

		ret = sपंचांगmac_selftests[i].fn(priv);
		अगर (ret && (ret != -EOPNOTSUPP))
			etest->flags |= ETH_TEST_FL_FAILED;
		buf[i] = ret;

		चयन (sपंचांगmac_selftests[i].lb) अणु
		हाल STMMAC_LOOPBACK_PHY:
			ret = -EOPNOTSUPP;
			अगर (dev->phydev)
				ret = phy_loopback(dev->phydev, false);
			अगर (!ret)
				अवरोध;
			fallthrough;
		हाल STMMAC_LOOPBACK_MAC:
			sपंचांगmac_set_mac_loopback(priv, priv->ioaddr, false);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम sपंचांगmac_selftest_get_strings(काष्ठा sपंचांगmac_priv *priv, u8 *data)
अणु
	u8 *p = data;
	पूर्णांक i;

	क्रम (i = 0; i < sपंचांगmac_selftest_get_count(priv); i++) अणु
		snम_लिखो(p, ETH_GSTRING_LEN, "%2d. %s", i + 1,
			 sपंचांगmac_selftests[i].name);
		p += ETH_GSTRING_LEN;
	पूर्ण
पूर्ण

पूर्णांक sपंचांगmac_selftest_get_count(काष्ठा sपंचांगmac_priv *priv)
अणु
	वापस ARRAY_SIZE(sपंचांगmac_selftests);
पूर्ण
