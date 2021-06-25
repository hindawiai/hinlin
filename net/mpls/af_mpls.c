<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/types.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/socket.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/net.h>
#समावेश <linux/module.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/mpls.h>
#समावेश <linux/netconf.h>
#समावेश <linux/nospec.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/percpu.h>
#समावेश <net/ip.h>
#समावेश <net/dst.h>
#समावेश <net/sock.h>
#समावेश <net/arp.h>
#समावेश <net/ip_fib.h>
#समावेश <net/netevent.h>
#समावेश <net/ip_tunnels.h>
#समावेश <net/netns/generic.h>
#अगर IS_ENABLED(CONFIG_IPV6)
#समावेश <net/ipv6.h>
#पूर्ण_अगर
#समावेश <net/ipv6_stubs.h>
#समावेश <net/rtnh.h>
#समावेश "internal.h"

/* max memory we will use क्रम mpls_route */
#घोषणा MAX_MPLS_ROUTE_MEM	4096

/* Maximum number of labels to look ahead at when selecting a path of
 * a multipath route
 */
#घोषणा MAX_MP_SELECT_LABELS 4

#घोषणा MPLS_NEIGH_TABLE_UNSPEC (NEIGH_LINK_TABLE + 1)

अटल पूर्णांक label_limit = (1 << 20) - 1;
अटल पूर्णांक ttl_max = 255;

#अगर IS_ENABLED(CONFIG_NET_IP_TUNNEL)
अटल माप_प्रकार ipgre_mpls_encap_hlen(काष्ठा ip_tunnel_encap *e)
अणु
	वापस माप(काष्ठा mpls_shim_hdr);
पूर्ण

अटल स्थिर काष्ठा ip_tunnel_encap_ops mpls_iptun_ops = अणु
	.encap_hlen	= ipgre_mpls_encap_hlen,
पूर्ण;

अटल पूर्णांक ipgre_tunnel_encap_add_mpls_ops(व्योम)
अणु
	वापस ip_tunnel_encap_add_ops(&mpls_iptun_ops, TUNNEL_ENCAP_MPLS);
पूर्ण

अटल व्योम ipgre_tunnel_encap_del_mpls_ops(व्योम)
अणु
	ip_tunnel_encap_del_ops(&mpls_iptun_ops, TUNNEL_ENCAP_MPLS);
पूर्ण
#अन्यथा
अटल पूर्णांक ipgre_tunnel_encap_add_mpls_ops(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम ipgre_tunnel_encap_del_mpls_ops(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम rपंचांगsg_lfib(पूर्णांक event, u32 label, काष्ठा mpls_route *rt,
		       काष्ठा nlmsghdr *nlh, काष्ठा net *net, u32 portid,
		       अचिन्हित पूर्णांक nlm_flags);

अटल काष्ठा mpls_route *mpls_route_input_rcu(काष्ठा net *net, अचिन्हित index)
अणु
	काष्ठा mpls_route *rt = शून्य;

	अगर (index < net->mpls.platक्रमm_labels) अणु
		काष्ठा mpls_route __rcu **platक्रमm_label =
			rcu_dereference(net->mpls.platक्रमm_label);
		rt = rcu_dereference(platक्रमm_label[index]);
	पूर्ण
	वापस rt;
पूर्ण

bool mpls_output_possible(स्थिर काष्ठा net_device *dev)
अणु
	वापस dev && (dev->flags & IFF_UP) && netअगर_carrier_ok(dev);
पूर्ण
EXPORT_SYMBOL_GPL(mpls_output_possible);

अटल u8 *__mpls_nh_via(काष्ठा mpls_route *rt, काष्ठा mpls_nh *nh)
अणु
	वापस (u8 *)nh + rt->rt_via_offset;
पूर्ण

अटल स्थिर u8 *mpls_nh_via(स्थिर काष्ठा mpls_route *rt,
			     स्थिर काष्ठा mpls_nh *nh)
अणु
	वापस __mpls_nh_via((काष्ठा mpls_route *)rt, (काष्ठा mpls_nh *)nh);
पूर्ण

अटल अचिन्हित पूर्णांक mpls_nh_header_size(स्थिर काष्ठा mpls_nh *nh)
अणु
	/* The size of the layer 2.5 labels to be added क्रम this route */
	वापस nh->nh_labels * माप(काष्ठा mpls_shim_hdr);
पूर्ण

अचिन्हित पूर्णांक mpls_dev_mtu(स्थिर काष्ठा net_device *dev)
अणु
	/* The amount of data the layer 2 frame can hold */
	वापस dev->mtu;
पूर्ण
EXPORT_SYMBOL_GPL(mpls_dev_mtu);

bool mpls_pkt_too_big(स्थिर काष्ठा sk_buff *skb, अचिन्हित पूर्णांक mtu)
अणु
	अगर (skb->len <= mtu)
		वापस false;

	अगर (skb_is_gso(skb) && skb_gso_validate_network_len(skb, mtu))
		वापस false;

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(mpls_pkt_too_big);

व्योम mpls_stats_inc_outucastpkts(काष्ठा net_device *dev,
				 स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा mpls_dev *mdev;

	अगर (skb->protocol == htons(ETH_P_MPLS_UC)) अणु
		mdev = mpls_dev_get(dev);
		अगर (mdev)
			MPLS_INC_STATS_LEN(mdev, skb->len,
					   tx_packets,
					   tx_bytes);
	पूर्ण अन्यथा अगर (skb->protocol == htons(ETH_P_IP)) अणु
		IP_UPD_PO_STATS(dev_net(dev), IPSTATS_MIB_OUT, skb->len);
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6)) अणु
		काष्ठा inet6_dev *in6dev = __in6_dev_get(dev);

		अगर (in6dev)
			IP6_UPD_PO_STATS(dev_net(dev), in6dev,
					 IPSTATS_MIB_OUT, skb->len);
#पूर्ण_अगर
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mpls_stats_inc_outucastpkts);

अटल u32 mpls_multipath_hash(काष्ठा mpls_route *rt, काष्ठा sk_buff *skb)
अणु
	काष्ठा mpls_entry_decoded dec;
	अचिन्हित पूर्णांक mpls_hdr_len = 0;
	काष्ठा mpls_shim_hdr *hdr;
	bool eli_seen = false;
	पूर्णांक label_index;
	u32 hash = 0;

	क्रम (label_index = 0; label_index < MAX_MP_SELECT_LABELS;
	     label_index++) अणु
		mpls_hdr_len += माप(*hdr);
		अगर (!pskb_may_pull(skb, mpls_hdr_len))
			अवरोध;

		/* Read and decode the current label */
		hdr = mpls_hdr(skb) + label_index;
		dec = mpls_entry_decode(hdr);

		/* RFC6790 - reserved labels MUST NOT be used as keys
		 * क्रम the load-balancing function
		 */
		अगर (likely(dec.label >= MPLS_LABEL_FIRST_UNRESERVED)) अणु
			hash = jhash_1word(dec.label, hash);

			/* The entropy label follows the entropy label
			 * indicator, so this means that the entropy
			 * label was just added to the hash - no need to
			 * go any deeper either in the label stack or in the
			 * payload
			 */
			अगर (eli_seen)
				अवरोध;
		पूर्ण अन्यथा अगर (dec.label == MPLS_LABEL_ENTROPY) अणु
			eli_seen = true;
		पूर्ण

		अगर (!dec.bos)
			जारी;

		/* found bottom label; करोes skb have room क्रम a header? */
		अगर (pskb_may_pull(skb, mpls_hdr_len + माप(काष्ठा iphdr))) अणु
			स्थिर काष्ठा iphdr *v4hdr;

			v4hdr = (स्थिर काष्ठा iphdr *)(hdr + 1);
			अगर (v4hdr->version == 4) अणु
				hash = jhash_3words(ntohl(v4hdr->saddr),
						    ntohl(v4hdr->daddr),
						    v4hdr->protocol, hash);
			पूर्ण अन्यथा अगर (v4hdr->version == 6 &&
				   pskb_may_pull(skb, mpls_hdr_len +
						 माप(काष्ठा ipv6hdr))) अणु
				स्थिर काष्ठा ipv6hdr *v6hdr;

				v6hdr = (स्थिर काष्ठा ipv6hdr *)(hdr + 1);
				hash = __ipv6_addr_jhash(&v6hdr->saddr, hash);
				hash = __ipv6_addr_jhash(&v6hdr->daddr, hash);
				hash = jhash_1word(v6hdr->nexthdr, hash);
			पूर्ण
		पूर्ण

		अवरोध;
	पूर्ण

	वापस hash;
पूर्ण

अटल काष्ठा mpls_nh *mpls_get_nexthop(काष्ठा mpls_route *rt, u8 index)
अणु
	वापस (काष्ठा mpls_nh *)((u8 *)rt->rt_nh + index * rt->rt_nh_size);
पूर्ण

/* number of alive nexthops (rt->rt_nhn_alive) and the flags क्रम
 * a next hop (nh->nh_flags) are modअगरied by netdev event handlers.
 * Since those fields can change at any moment, use READ_ONCE to
 * access both.
 */
अटल काष्ठा mpls_nh *mpls_select_multipath(काष्ठा mpls_route *rt,
					     काष्ठा sk_buff *skb)
अणु
	u32 hash = 0;
	पूर्णांक nh_index = 0;
	पूर्णांक n = 0;
	u8 alive;

	/* No need to look further पूर्णांकo packet अगर there's only
	 * one path
	 */
	अगर (rt->rt_nhn == 1)
		वापस rt->rt_nh;

	alive = READ_ONCE(rt->rt_nhn_alive);
	अगर (alive == 0)
		वापस शून्य;

	hash = mpls_multipath_hash(rt, skb);
	nh_index = hash % alive;
	अगर (alive == rt->rt_nhn)
		जाओ out;
	क्रम_nexthops(rt) अणु
		अचिन्हित पूर्णांक nh_flags = READ_ONCE(nh->nh_flags);

		अगर (nh_flags & (RTNH_F_DEAD | RTNH_F_LINKDOWN))
			जारी;
		अगर (n == nh_index)
			वापस nh;
		n++;
	पूर्ण endक्रम_nexthops(rt);

out:
	वापस mpls_get_nexthop(rt, nh_index);
पूर्ण

अटल bool mpls_egress(काष्ठा net *net, काष्ठा mpls_route *rt,
			काष्ठा sk_buff *skb, काष्ठा mpls_entry_decoded dec)
अणु
	क्रमागत mpls_payload_type payload_type;
	bool success = false;

	/* The IPv4 code below accesses through the IPv4 header
	 * checksum, which is 12 bytes पूर्णांकo the packet.
	 * The IPv6 code below accesses through the IPv6 hop limit
	 * which is 8 bytes पूर्णांकo the packet.
	 *
	 * For all supported हालs there should always be at least 12
	 * bytes of packet data present.  The IPv4 header is 20 bytes
	 * without options and the IPv6 header is always 40 bytes
	 * दीर्घ.
	 */
	अगर (!pskb_may_pull(skb, 12))
		वापस false;

	payload_type = rt->rt_payload_type;
	अगर (payload_type == MPT_UNSPEC)
		payload_type = ip_hdr(skb)->version;

	चयन (payload_type) अणु
	हाल MPT_IPV4: अणु
		काष्ठा iphdr *hdr4 = ip_hdr(skb);
		u8 new_ttl;
		skb->protocol = htons(ETH_P_IP);

		/* If propagating TTL, take the decremented TTL from
		 * the incoming MPLS header, otherwise decrement the
		 * TTL, but only अगर not 0 to aव्योम underflow.
		 */
		अगर (rt->rt_ttl_propagate == MPLS_TTL_PROP_ENABLED ||
		    (rt->rt_ttl_propagate == MPLS_TTL_PROP_DEFAULT &&
		     net->mpls.ip_ttl_propagate))
			new_ttl = dec.ttl;
		अन्यथा
			new_ttl = hdr4->ttl ? hdr4->ttl - 1 : 0;

		csum_replace2(&hdr4->check,
			      htons(hdr4->ttl << 8),
			      htons(new_ttl << 8));
		hdr4->ttl = new_ttl;
		success = true;
		अवरोध;
	पूर्ण
	हाल MPT_IPV6: अणु
		काष्ठा ipv6hdr *hdr6 = ipv6_hdr(skb);
		skb->protocol = htons(ETH_P_IPV6);

		/* If propagating TTL, take the decremented TTL from
		 * the incoming MPLS header, otherwise decrement the
		 * hop limit, but only अगर not 0 to aव्योम underflow.
		 */
		अगर (rt->rt_ttl_propagate == MPLS_TTL_PROP_ENABLED ||
		    (rt->rt_ttl_propagate == MPLS_TTL_PROP_DEFAULT &&
		     net->mpls.ip_ttl_propagate))
			hdr6->hop_limit = dec.ttl;
		अन्यथा अगर (hdr6->hop_limit)
			hdr6->hop_limit = hdr6->hop_limit - 1;
		success = true;
		अवरोध;
	पूर्ण
	हाल MPT_UNSPEC:
		/* Should have decided which protocol it is by now */
		अवरोध;
	पूर्ण

	वापस success;
पूर्ण

अटल पूर्णांक mpls_क्रमward(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			काष्ठा packet_type *pt, काष्ठा net_device *orig_dev)
अणु
	काष्ठा net *net = dev_net(dev);
	काष्ठा mpls_shim_hdr *hdr;
	काष्ठा mpls_route *rt;
	काष्ठा mpls_nh *nh;
	काष्ठा mpls_entry_decoded dec;
	काष्ठा net_device *out_dev;
	काष्ठा mpls_dev *out_mdev;
	काष्ठा mpls_dev *mdev;
	अचिन्हित पूर्णांक hh_len;
	अचिन्हित पूर्णांक new_header_size;
	अचिन्हित पूर्णांक mtu;
	पूर्णांक err;

	/* Careful this entire function runs inside of an rcu critical section */

	mdev = mpls_dev_get(dev);
	अगर (!mdev)
		जाओ drop;

	MPLS_INC_STATS_LEN(mdev, skb->len, rx_packets,
			   rx_bytes);

	अगर (!mdev->input_enabled) अणु
		MPLS_INC_STATS(mdev, rx_dropped);
		जाओ drop;
	पूर्ण

	अगर (skb->pkt_type != PACKET_HOST)
		जाओ err;

	अगर ((skb = skb_share_check(skb, GFP_ATOMIC)) == शून्य)
		जाओ err;

	अगर (!pskb_may_pull(skb, माप(*hdr)))
		जाओ err;

	skb_dst_drop(skb);

	/* Read and decode the label */
	hdr = mpls_hdr(skb);
	dec = mpls_entry_decode(hdr);

	rt = mpls_route_input_rcu(net, dec.label);
	अगर (!rt) अणु
		MPLS_INC_STATS(mdev, rx_noroute);
		जाओ drop;
	पूर्ण

	nh = mpls_select_multipath(rt, skb);
	अगर (!nh)
		जाओ err;

	/* Pop the label */
	skb_pull(skb, माप(*hdr));
	skb_reset_network_header(skb);

	skb_orphan(skb);

	अगर (skb_warn_अगर_lro(skb))
		जाओ err;

	skb_क्रमward_csum(skb);

	/* Verअगरy ttl is valid */
	अगर (dec.ttl <= 1)
		जाओ err;
	dec.ttl -= 1;

	/* Find the output device */
	out_dev = rcu_dereference(nh->nh_dev);
	अगर (!mpls_output_possible(out_dev))
		जाओ tx_err;

	/* Verअगरy the destination can hold the packet */
	new_header_size = mpls_nh_header_size(nh);
	mtu = mpls_dev_mtu(out_dev);
	अगर (mpls_pkt_too_big(skb, mtu - new_header_size))
		जाओ tx_err;

	hh_len = LL_RESERVED_SPACE(out_dev);
	अगर (!out_dev->header_ops)
		hh_len = 0;

	/* Ensure there is enough space क्रम the headers in the skb */
	अगर (skb_cow(skb, hh_len + new_header_size))
		जाओ tx_err;

	skb->dev = out_dev;
	skb->protocol = htons(ETH_P_MPLS_UC);

	अगर (unlikely(!new_header_size && dec.bos)) अणु
		/* Penultimate hop popping */
		अगर (!mpls_egress(dev_net(out_dev), rt, skb, dec))
			जाओ err;
	पूर्ण अन्यथा अणु
		bool bos;
		पूर्णांक i;
		skb_push(skb, new_header_size);
		skb_reset_network_header(skb);
		/* Push the new labels */
		hdr = mpls_hdr(skb);
		bos = dec.bos;
		क्रम (i = nh->nh_labels - 1; i >= 0; i--) अणु
			hdr[i] = mpls_entry_encode(nh->nh_label[i],
						   dec.ttl, 0, bos);
			bos = false;
		पूर्ण
	पूर्ण

	mpls_stats_inc_outucastpkts(out_dev, skb);

	/* If via wasn't specअगरied then send out using device address */
	अगर (nh->nh_via_table == MPLS_NEIGH_TABLE_UNSPEC)
		err = neigh_xmit(NEIGH_LINK_TABLE, out_dev,
				 out_dev->dev_addr, skb);
	अन्यथा
		err = neigh_xmit(nh->nh_via_table, out_dev,
				 mpls_nh_via(rt, nh), skb);
	अगर (err)
		net_dbg_ratelimited("%s: packet transmission failed: %d\n",
				    __func__, err);
	वापस 0;

tx_err:
	out_mdev = out_dev ? mpls_dev_get(out_dev) : शून्य;
	अगर (out_mdev)
		MPLS_INC_STATS(out_mdev, tx_errors);
	जाओ drop;
err:
	MPLS_INC_STATS(mdev, rx_errors);
drop:
	kमुक्त_skb(skb);
	वापस NET_RX_DROP;
पूर्ण

अटल काष्ठा packet_type mpls_packet_type __पढ़ो_mostly = अणु
	.type = cpu_to_be16(ETH_P_MPLS_UC),
	.func = mpls_क्रमward,
पूर्ण;

अटल स्थिर काष्ठा nla_policy rपंचांग_mpls_policy[RTA_MAX+1] = अणु
	[RTA_DST]		= अणु .type = NLA_U32 पूर्ण,
	[RTA_OIF]		= अणु .type = NLA_U32 पूर्ण,
	[RTA_TTL_PROPAGATE]	= अणु .type = NLA_U8 पूर्ण,
पूर्ण;

काष्ठा mpls_route_config अणु
	u32			rc_protocol;
	u32			rc_अगरindex;
	u8			rc_via_table;
	u8			rc_via_alen;
	u8			rc_via[MAX_VIA_ALEN];
	u32			rc_label;
	u8			rc_ttl_propagate;
	u8			rc_output_labels;
	u32			rc_output_label[MAX_NEW_LABELS];
	u32			rc_nlflags;
	क्रमागत mpls_payload_type	rc_payload_type;
	काष्ठा nl_info		rc_nlinfo;
	काष्ठा rtnexthop	*rc_mp;
	पूर्णांक			rc_mp_len;
पूर्ण;

/* all nexthops within a route have the same size based on max
 * number of labels and max via length क्रम a hop
 */
अटल काष्ठा mpls_route *mpls_rt_alloc(u8 num_nh, u8 max_alen, u8 max_labels)
अणु
	u8 nh_size = MPLS_NH_SIZE(max_labels, max_alen);
	काष्ठा mpls_route *rt;
	माप_प्रकार size;

	size = माप(*rt) + num_nh * nh_size;
	अगर (size > MAX_MPLS_ROUTE_MEM)
		वापस ERR_PTR(-EINVAL);

	rt = kzalloc(size, GFP_KERNEL);
	अगर (!rt)
		वापस ERR_PTR(-ENOMEM);

	rt->rt_nhn = num_nh;
	rt->rt_nhn_alive = num_nh;
	rt->rt_nh_size = nh_size;
	rt->rt_via_offset = MPLS_NH_VIA_OFF(max_labels);

	वापस rt;
पूर्ण

अटल व्योम mpls_rt_मुक्त(काष्ठा mpls_route *rt)
अणु
	अगर (rt)
		kमुक्त_rcu(rt, rt_rcu);
पूर्ण

अटल व्योम mpls_notअगरy_route(काष्ठा net *net, अचिन्हित index,
			      काष्ठा mpls_route *old, काष्ठा mpls_route *new,
			      स्थिर काष्ठा nl_info *info)
अणु
	काष्ठा nlmsghdr *nlh = info ? info->nlh : शून्य;
	अचिन्हित portid = info ? info->portid : 0;
	पूर्णांक event = new ? RTM_NEWROUTE : RTM_DELROUTE;
	काष्ठा mpls_route *rt = new ? new : old;
	अचिन्हित nlm_flags = (old && new) ? NLM_F_REPLACE : 0;
	/* Ignore reserved labels क्रम now */
	अगर (rt && (index >= MPLS_LABEL_FIRST_UNRESERVED))
		rपंचांगsg_lfib(event, index, rt, nlh, net, portid, nlm_flags);
पूर्ण

अटल व्योम mpls_route_update(काष्ठा net *net, अचिन्हित index,
			      काष्ठा mpls_route *new,
			      स्थिर काष्ठा nl_info *info)
अणु
	काष्ठा mpls_route __rcu **platक्रमm_label;
	काष्ठा mpls_route *rt;

	ASSERT_RTNL();

	platक्रमm_label = rtnl_dereference(net->mpls.platक्रमm_label);
	rt = rtnl_dereference(platक्रमm_label[index]);
	rcu_assign_poपूर्णांकer(platक्रमm_label[index], new);

	mpls_notअगरy_route(net, index, rt, new, info);

	/* If we हटाओd a route मुक्त it now */
	mpls_rt_मुक्त(rt);
पूर्ण

अटल अचिन्हित find_मुक्त_label(काष्ठा net *net)
अणु
	काष्ठा mpls_route __rcu **platक्रमm_label;
	माप_प्रकार platक्रमm_labels;
	अचिन्हित index;

	platक्रमm_label = rtnl_dereference(net->mpls.platक्रमm_label);
	platक्रमm_labels = net->mpls.platक्रमm_labels;
	क्रम (index = MPLS_LABEL_FIRST_UNRESERVED; index < platक्रमm_labels;
	     index++) अणु
		अगर (!rtnl_dereference(platक्रमm_label[index]))
			वापस index;
	पूर्ण
	वापस LABEL_NOT_SPECIFIED;
पूर्ण

#अगर IS_ENABLED(CONFIG_INET)
अटल काष्ठा net_device *inet_fib_lookup_dev(काष्ठा net *net,
					      स्थिर व्योम *addr)
अणु
	काष्ठा net_device *dev;
	काष्ठा rtable *rt;
	काष्ठा in_addr daddr;

	स_नकल(&daddr, addr, माप(काष्ठा in_addr));
	rt = ip_route_output(net, daddr.s_addr, 0, 0, 0);
	अगर (IS_ERR(rt))
		वापस ERR_CAST(rt);

	dev = rt->dst.dev;
	dev_hold(dev);

	ip_rt_put(rt);

	वापस dev;
पूर्ण
#अन्यथा
अटल काष्ठा net_device *inet_fib_lookup_dev(काष्ठा net *net,
					      स्थिर व्योम *addr)
अणु
	वापस ERR_PTR(-EAFNOSUPPORT);
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_IPV6)
अटल काष्ठा net_device *inet6_fib_lookup_dev(काष्ठा net *net,
					       स्थिर व्योम *addr)
अणु
	काष्ठा net_device *dev;
	काष्ठा dst_entry *dst;
	काष्ठा flowi6 fl6;

	अगर (!ipv6_stub)
		वापस ERR_PTR(-EAFNOSUPPORT);

	स_रखो(&fl6, 0, माप(fl6));
	स_नकल(&fl6.daddr, addr, माप(काष्ठा in6_addr));
	dst = ipv6_stub->ipv6_dst_lookup_flow(net, शून्य, &fl6, शून्य);
	अगर (IS_ERR(dst))
		वापस ERR_CAST(dst);

	dev = dst->dev;
	dev_hold(dev);
	dst_release(dst);

	वापस dev;
पूर्ण
#अन्यथा
अटल काष्ठा net_device *inet6_fib_lookup_dev(काष्ठा net *net,
					       स्थिर व्योम *addr)
अणु
	वापस ERR_PTR(-EAFNOSUPPORT);
पूर्ण
#पूर्ण_अगर

अटल काष्ठा net_device *find_outdev(काष्ठा net *net,
				      काष्ठा mpls_route *rt,
				      काष्ठा mpls_nh *nh, पूर्णांक oअगर)
अणु
	काष्ठा net_device *dev = शून्य;

	अगर (!oअगर) अणु
		चयन (nh->nh_via_table) अणु
		हाल NEIGH_ARP_TABLE:
			dev = inet_fib_lookup_dev(net, mpls_nh_via(rt, nh));
			अवरोध;
		हाल NEIGH_ND_TABLE:
			dev = inet6_fib_lookup_dev(net, mpls_nh_via(rt, nh));
			अवरोध;
		हाल NEIGH_LINK_TABLE:
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev = dev_get_by_index(net, oअगर);
	पूर्ण

	अगर (!dev)
		वापस ERR_PTR(-ENODEV);

	अगर (IS_ERR(dev))
		वापस dev;

	/* The caller is holding rtnl anyways, so release the dev reference */
	dev_put(dev);

	वापस dev;
पूर्ण

अटल पूर्णांक mpls_nh_assign_dev(काष्ठा net *net, काष्ठा mpls_route *rt,
			      काष्ठा mpls_nh *nh, पूर्णांक oअगर)
अणु
	काष्ठा net_device *dev = शून्य;
	पूर्णांक err = -ENODEV;

	dev = find_outdev(net, rt, nh, oअगर);
	अगर (IS_ERR(dev)) अणु
		err = PTR_ERR(dev);
		dev = शून्य;
		जाओ errout;
	पूर्ण

	/* Ensure this is a supported device */
	err = -EINVAL;
	अगर (!mpls_dev_get(dev))
		जाओ errout;

	अगर ((nh->nh_via_table == NEIGH_LINK_TABLE) &&
	    (dev->addr_len != nh->nh_via_alen))
		जाओ errout;

	RCU_INIT_POINTER(nh->nh_dev, dev);

	अगर (!(dev->flags & IFF_UP)) अणु
		nh->nh_flags |= RTNH_F_DEAD;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक flags;

		flags = dev_get_flags(dev);
		अगर (!(flags & (IFF_RUNNING | IFF_LOWER_UP)))
			nh->nh_flags |= RTNH_F_LINKDOWN;
	पूर्ण

	वापस 0;

errout:
	वापस err;
पूर्ण

अटल पूर्णांक nla_get_via(स्थिर काष्ठा nlattr *nla, u8 *via_alen, u8 *via_table,
		       u8 via_addr[], काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा rtvia *via = nla_data(nla);
	पूर्णांक err = -EINVAL;
	पूर्णांक alen;

	अगर (nla_len(nla) < दुरत्व(काष्ठा rtvia, rtvia_addr)) अणु
		NL_SET_ERR_MSG_ATTR(extack, nla,
				    "Invalid attribute length for RTA_VIA");
		जाओ errout;
	पूर्ण
	alen = nla_len(nla) -
			दुरत्व(काष्ठा rtvia, rtvia_addr);
	अगर (alen > MAX_VIA_ALEN) अणु
		NL_SET_ERR_MSG_ATTR(extack, nla,
				    "Invalid address length for RTA_VIA");
		जाओ errout;
	पूर्ण

	/* Validate the address family */
	चयन (via->rtvia_family) अणु
	हाल AF_PACKET:
		*via_table = NEIGH_LINK_TABLE;
		अवरोध;
	हाल AF_INET:
		*via_table = NEIGH_ARP_TABLE;
		अगर (alen != 4)
			जाओ errout;
		अवरोध;
	हाल AF_INET6:
		*via_table = NEIGH_ND_TABLE;
		अगर (alen != 16)
			जाओ errout;
		अवरोध;
	शेष:
		/* Unsupported address family */
		जाओ errout;
	पूर्ण

	स_नकल(via_addr, via->rtvia_addr, alen);
	*via_alen = alen;
	err = 0;

errout:
	वापस err;
पूर्ण

अटल पूर्णांक mpls_nh_build_from_cfg(काष्ठा mpls_route_config *cfg,
				  काष्ठा mpls_route *rt)
अणु
	काष्ठा net *net = cfg->rc_nlinfo.nl_net;
	काष्ठा mpls_nh *nh = rt->rt_nh;
	पूर्णांक err;
	पूर्णांक i;

	अगर (!nh)
		वापस -ENOMEM;

	nh->nh_labels = cfg->rc_output_labels;
	क्रम (i = 0; i < nh->nh_labels; i++)
		nh->nh_label[i] = cfg->rc_output_label[i];

	nh->nh_via_table = cfg->rc_via_table;
	स_नकल(__mpls_nh_via(rt, nh), cfg->rc_via, cfg->rc_via_alen);
	nh->nh_via_alen = cfg->rc_via_alen;

	err = mpls_nh_assign_dev(net, rt, nh, cfg->rc_अगरindex);
	अगर (err)
		जाओ errout;

	अगर (nh->nh_flags & (RTNH_F_DEAD | RTNH_F_LINKDOWN))
		rt->rt_nhn_alive--;

	वापस 0;

errout:
	वापस err;
पूर्ण

अटल पूर्णांक mpls_nh_build(काष्ठा net *net, काष्ठा mpls_route *rt,
			 काष्ठा mpls_nh *nh, पूर्णांक oअगर, काष्ठा nlattr *via,
			 काष्ठा nlattr *newdst, u8 max_labels,
			 काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err = -ENOMEM;

	अगर (!nh)
		जाओ errout;

	अगर (newdst) अणु
		err = nla_get_labels(newdst, max_labels, &nh->nh_labels,
				     nh->nh_label, extack);
		अगर (err)
			जाओ errout;
	पूर्ण

	अगर (via) अणु
		err = nla_get_via(via, &nh->nh_via_alen, &nh->nh_via_table,
				  __mpls_nh_via(rt, nh), extack);
		अगर (err)
			जाओ errout;
	पूर्ण अन्यथा अणु
		nh->nh_via_table = MPLS_NEIGH_TABLE_UNSPEC;
	पूर्ण

	err = mpls_nh_assign_dev(net, rt, nh, oअगर);
	अगर (err)
		जाओ errout;

	वापस 0;

errout:
	वापस err;
पूर्ण

अटल u8 mpls_count_nexthops(काष्ठा rtnexthop *rtnh, पूर्णांक len,
			      u8 cfg_via_alen, u8 *max_via_alen,
			      u8 *max_labels)
अणु
	पूर्णांक reमुख्यing = len;
	u8 nhs = 0;

	*max_via_alen = 0;
	*max_labels = 0;

	जबतक (rtnh_ok(rtnh, reमुख्यing)) अणु
		काष्ठा nlattr *nla, *attrs = rtnh_attrs(rtnh);
		पूर्णांक attrlen;
		u8 n_labels = 0;

		attrlen = rtnh_attrlen(rtnh);
		nla = nla_find(attrs, attrlen, RTA_VIA);
		अगर (nla && nla_len(nla) >=
		    दुरत्व(काष्ठा rtvia, rtvia_addr)) अणु
			पूर्णांक via_alen = nla_len(nla) -
				दुरत्व(काष्ठा rtvia, rtvia_addr);

			अगर (via_alen <= MAX_VIA_ALEN)
				*max_via_alen = max_t(u16, *max_via_alen,
						      via_alen);
		पूर्ण

		nla = nla_find(attrs, attrlen, RTA_NEWDST);
		अगर (nla &&
		    nla_get_labels(nla, MAX_NEW_LABELS, &n_labels,
				   शून्य, शून्य) != 0)
			वापस 0;

		*max_labels = max_t(u8, *max_labels, n_labels);

		/* number of nexthops is tracked by a u8.
		 * Check क्रम overflow.
		 */
		अगर (nhs == 255)
			वापस 0;
		nhs++;

		rtnh = rtnh_next(rtnh, &reमुख्यing);
	पूर्ण

	/* leftover implies invalid nexthop configuration, discard it */
	वापस reमुख्यing > 0 ? 0 : nhs;
पूर्ण

अटल पूर्णांक mpls_nh_build_multi(काष्ठा mpls_route_config *cfg,
			       काष्ठा mpls_route *rt, u8 max_labels,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा rtnexthop *rtnh = cfg->rc_mp;
	काष्ठा nlattr *nla_via, *nla_newdst;
	पूर्णांक reमुख्यing = cfg->rc_mp_len;
	पूर्णांक err = 0;
	u8 nhs = 0;

	change_nexthops(rt) अणु
		पूर्णांक attrlen;

		nla_via = शून्य;
		nla_newdst = शून्य;

		err = -EINVAL;
		अगर (!rtnh_ok(rtnh, reमुख्यing))
			जाओ errout;

		/* neither weighted multipath nor any flags
		 * are supported
		 */
		अगर (rtnh->rtnh_hops || rtnh->rtnh_flags)
			जाओ errout;

		attrlen = rtnh_attrlen(rtnh);
		अगर (attrlen > 0) अणु
			काष्ठा nlattr *attrs = rtnh_attrs(rtnh);

			nla_via = nla_find(attrs, attrlen, RTA_VIA);
			nla_newdst = nla_find(attrs, attrlen, RTA_NEWDST);
		पूर्ण

		err = mpls_nh_build(cfg->rc_nlinfo.nl_net, rt, nh,
				    rtnh->rtnh_अगरindex, nla_via, nla_newdst,
				    max_labels, extack);
		अगर (err)
			जाओ errout;

		अगर (nh->nh_flags & (RTNH_F_DEAD | RTNH_F_LINKDOWN))
			rt->rt_nhn_alive--;

		rtnh = rtnh_next(rtnh, &reमुख्यing);
		nhs++;
	पूर्ण endक्रम_nexthops(rt);

	rt->rt_nhn = nhs;

	वापस 0;

errout:
	वापस err;
पूर्ण

अटल bool mpls_label_ok(काष्ठा net *net, अचिन्हित पूर्णांक *index,
			  काष्ठा netlink_ext_ack *extack)
अणु
	bool is_ok = true;

	/* Reserved labels may not be set */
	अगर (*index < MPLS_LABEL_FIRST_UNRESERVED) अणु
		NL_SET_ERR_MSG(extack,
			       "Invalid label - must be MPLS_LABEL_FIRST_UNRESERVED or higher");
		is_ok = false;
	पूर्ण

	/* The full 20 bit range may not be supported. */
	अगर (is_ok && *index >= net->mpls.platक्रमm_labels) अणु
		NL_SET_ERR_MSG(extack,
			       "Label >= configured maximum in platform_labels");
		is_ok = false;
	पूर्ण

	*index = array_index_nospec(*index, net->mpls.platक्रमm_labels);
	वापस is_ok;
पूर्ण

अटल पूर्णांक mpls_route_add(काष्ठा mpls_route_config *cfg,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mpls_route __rcu **platक्रमm_label;
	काष्ठा net *net = cfg->rc_nlinfo.nl_net;
	काष्ठा mpls_route *rt, *old;
	पूर्णांक err = -EINVAL;
	u8 max_via_alen;
	अचिन्हित index;
	u8 max_labels;
	u8 nhs;

	index = cfg->rc_label;

	/* If a label was not specअगरied during insert pick one */
	अगर ((index == LABEL_NOT_SPECIFIED) &&
	    (cfg->rc_nlflags & NLM_F_CREATE)) अणु
		index = find_मुक्त_label(net);
	पूर्ण

	अगर (!mpls_label_ok(net, &index, extack))
		जाओ errout;

	/* Append makes no sense with mpls */
	err = -EOPNOTSUPP;
	अगर (cfg->rc_nlflags & NLM_F_APPEND) अणु
		NL_SET_ERR_MSG(extack, "MPLS does not support route append");
		जाओ errout;
	पूर्ण

	err = -EEXIST;
	platक्रमm_label = rtnl_dereference(net->mpls.platक्रमm_label);
	old = rtnl_dereference(platक्रमm_label[index]);
	अगर ((cfg->rc_nlflags & NLM_F_EXCL) && old)
		जाओ errout;

	err = -EEXIST;
	अगर (!(cfg->rc_nlflags & NLM_F_REPLACE) && old)
		जाओ errout;

	err = -ENOENT;
	अगर (!(cfg->rc_nlflags & NLM_F_CREATE) && !old)
		जाओ errout;

	err = -EINVAL;
	अगर (cfg->rc_mp) अणु
		nhs = mpls_count_nexthops(cfg->rc_mp, cfg->rc_mp_len,
					  cfg->rc_via_alen, &max_via_alen,
					  &max_labels);
	पूर्ण अन्यथा अणु
		max_via_alen = cfg->rc_via_alen;
		max_labels = cfg->rc_output_labels;
		nhs = 1;
	पूर्ण

	अगर (nhs == 0) अणु
		NL_SET_ERR_MSG(extack, "Route does not contain a nexthop");
		जाओ errout;
	पूर्ण

	rt = mpls_rt_alloc(nhs, max_via_alen, max_labels);
	अगर (IS_ERR(rt)) अणु
		err = PTR_ERR(rt);
		जाओ errout;
	पूर्ण

	rt->rt_protocol = cfg->rc_protocol;
	rt->rt_payload_type = cfg->rc_payload_type;
	rt->rt_ttl_propagate = cfg->rc_ttl_propagate;

	अगर (cfg->rc_mp)
		err = mpls_nh_build_multi(cfg, rt, max_labels, extack);
	अन्यथा
		err = mpls_nh_build_from_cfg(cfg, rt);
	अगर (err)
		जाओ मुक्तrt;

	mpls_route_update(net, index, rt, &cfg->rc_nlinfo);

	वापस 0;

मुक्तrt:
	mpls_rt_मुक्त(rt);
errout:
	वापस err;
पूर्ण

अटल पूर्णांक mpls_route_del(काष्ठा mpls_route_config *cfg,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = cfg->rc_nlinfo.nl_net;
	अचिन्हित index;
	पूर्णांक err = -EINVAL;

	index = cfg->rc_label;

	अगर (!mpls_label_ok(net, &index, extack))
		जाओ errout;

	mpls_route_update(net, index, शून्य, &cfg->rc_nlinfo);

	err = 0;
errout:
	वापस err;
पूर्ण

अटल व्योम mpls_get_stats(काष्ठा mpls_dev *mdev,
			   काष्ठा mpls_link_stats *stats)
अणु
	काष्ठा mpls_pcpu_stats *p;
	पूर्णांक i;

	स_रखो(stats, 0, माप(*stats));

	क्रम_each_possible_cpu(i) अणु
		काष्ठा mpls_link_stats local;
		अचिन्हित पूर्णांक start;

		p = per_cpu_ptr(mdev->stats, i);
		करो अणु
			start = u64_stats_fetch_begin(&p->syncp);
			local = p->stats;
		पूर्ण जबतक (u64_stats_fetch_retry(&p->syncp, start));

		stats->rx_packets	+= local.rx_packets;
		stats->rx_bytes		+= local.rx_bytes;
		stats->tx_packets	+= local.tx_packets;
		stats->tx_bytes		+= local.tx_bytes;
		stats->rx_errors	+= local.rx_errors;
		stats->tx_errors	+= local.tx_errors;
		stats->rx_dropped	+= local.rx_dropped;
		stats->tx_dropped	+= local.tx_dropped;
		stats->rx_noroute	+= local.rx_noroute;
	पूर्ण
पूर्ण

अटल पूर्णांक mpls_fill_stats_af(काष्ठा sk_buff *skb,
			      स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा mpls_link_stats *stats;
	काष्ठा mpls_dev *mdev;
	काष्ठा nlattr *nla;

	mdev = mpls_dev_get(dev);
	अगर (!mdev)
		वापस -ENODATA;

	nla = nla_reserve_64bit(skb, MPLS_STATS_LINK,
				माप(काष्ठा mpls_link_stats),
				MPLS_STATS_UNSPEC);
	अगर (!nla)
		वापस -EMSGSIZE;

	stats = nla_data(nla);
	mpls_get_stats(mdev, stats);

	वापस 0;
पूर्ण

अटल माप_प्रकार mpls_get_stats_af_size(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा mpls_dev *mdev;

	mdev = mpls_dev_get(dev);
	अगर (!mdev)
		वापस 0;

	वापस nla_total_size_64bit(माप(काष्ठा mpls_link_stats));
पूर्ण

अटल पूर्णांक mpls_netconf_fill_devconf(काष्ठा sk_buff *skb, काष्ठा mpls_dev *mdev,
				     u32 portid, u32 seq, पूर्णांक event,
				     अचिन्हित पूर्णांक flags, पूर्णांक type)
अणु
	काष्ठा nlmsghdr  *nlh;
	काष्ठा netconfmsg *ncm;
	bool all = false;

	nlh = nlmsg_put(skb, portid, seq, event, माप(काष्ठा netconfmsg),
			flags);
	अगर (!nlh)
		वापस -EMSGSIZE;

	अगर (type == NETCONFA_ALL)
		all = true;

	ncm = nlmsg_data(nlh);
	ncm->ncm_family = AF_MPLS;

	अगर (nla_put_s32(skb, NETCONFA_IFINDEX, mdev->dev->अगरindex) < 0)
		जाओ nla_put_failure;

	अगर ((all || type == NETCONFA_INPUT) &&
	    nla_put_s32(skb, NETCONFA_INPUT,
			mdev->input_enabled) < 0)
		जाओ nla_put_failure;

	nlmsg_end(skb, nlh);
	वापस 0;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक mpls_netconf_msgsize_devconf(पूर्णांक type)
अणु
	पूर्णांक size = NLMSG_ALIGN(माप(काष्ठा netconfmsg))
			+ nla_total_size(4); /* NETCONFA_IFINDEX */
	bool all = false;

	अगर (type == NETCONFA_ALL)
		all = true;

	अगर (all || type == NETCONFA_INPUT)
		size += nla_total_size(4);

	वापस size;
पूर्ण

अटल व्योम mpls_netconf_notअगरy_devconf(काष्ठा net *net, पूर्णांक event,
					पूर्णांक type, काष्ठा mpls_dev *mdev)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक err = -ENOBUFS;

	skb = nlmsg_new(mpls_netconf_msgsize_devconf(type), GFP_KERNEL);
	अगर (!skb)
		जाओ errout;

	err = mpls_netconf_fill_devconf(skb, mdev, 0, 0, event, 0, type);
	अगर (err < 0) अणु
		/* -EMSGSIZE implies BUG in mpls_netconf_msgsize_devconf() */
		WARN_ON(err == -EMSGSIZE);
		kमुक्त_skb(skb);
		जाओ errout;
	पूर्ण

	rtnl_notअगरy(skb, net, 0, RTNLGRP_MPLS_NETCONF, शून्य, GFP_KERNEL);
	वापस;
errout:
	अगर (err < 0)
		rtnl_set_sk_err(net, RTNLGRP_MPLS_NETCONF, err);
पूर्ण

अटल स्थिर काष्ठा nla_policy devconf_mpls_policy[NETCONFA_MAX + 1] = अणु
	[NETCONFA_IFINDEX]	= अणु .len = माप(पूर्णांक) पूर्ण,
पूर्ण;

अटल पूर्णांक mpls_netconf_valid_get_req(काष्ठा sk_buff *skb,
				      स्थिर काष्ठा nlmsghdr *nlh,
				      काष्ठा nlattr **tb,
				      काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक i, err;

	अगर (nlh->nlmsg_len < nlmsg_msg_size(माप(काष्ठा netconfmsg))) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Invalid header for netconf get request");
		वापस -EINVAL;
	पूर्ण

	अगर (!netlink_strict_get_check(skb))
		वापस nlmsg_parse_deprecated(nlh, माप(काष्ठा netconfmsg),
					      tb, NETCONFA_MAX,
					      devconf_mpls_policy, extack);

	err = nlmsg_parse_deprecated_strict(nlh, माप(काष्ठा netconfmsg),
					    tb, NETCONFA_MAX,
					    devconf_mpls_policy, extack);
	अगर (err)
		वापस err;

	क्रम (i = 0; i <= NETCONFA_MAX; i++) अणु
		अगर (!tb[i])
			जारी;

		चयन (i) अणु
		हाल NETCONFA_IFINDEX:
			अवरोध;
		शेष:
			NL_SET_ERR_MSG_MOD(extack, "Unsupported attribute in netconf get request");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mpls_netconf_get_devconf(काष्ठा sk_buff *in_skb,
				    काष्ठा nlmsghdr *nlh,
				    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(in_skb->sk);
	काष्ठा nlattr *tb[NETCONFA_MAX + 1];
	काष्ठा net_device *dev;
	काष्ठा mpls_dev *mdev;
	काष्ठा sk_buff *skb;
	पूर्णांक अगरindex;
	पूर्णांक err;

	err = mpls_netconf_valid_get_req(in_skb, nlh, tb, extack);
	अगर (err < 0)
		जाओ errout;

	err = -EINVAL;
	अगर (!tb[NETCONFA_IFINDEX])
		जाओ errout;

	अगरindex = nla_get_s32(tb[NETCONFA_IFINDEX]);
	dev = __dev_get_by_index(net, अगरindex);
	अगर (!dev)
		जाओ errout;

	mdev = mpls_dev_get(dev);
	अगर (!mdev)
		जाओ errout;

	err = -ENOBUFS;
	skb = nlmsg_new(mpls_netconf_msgsize_devconf(NETCONFA_ALL), GFP_KERNEL);
	अगर (!skb)
		जाओ errout;

	err = mpls_netconf_fill_devconf(skb, mdev,
					NETLINK_CB(in_skb).portid,
					nlh->nlmsg_seq, RTM_NEWNETCONF, 0,
					NETCONFA_ALL);
	अगर (err < 0) अणु
		/* -EMSGSIZE implies BUG in mpls_netconf_msgsize_devconf() */
		WARN_ON(err == -EMSGSIZE);
		kमुक्त_skb(skb);
		जाओ errout;
	पूर्ण
	err = rtnl_unicast(skb, net, NETLINK_CB(in_skb).portid);
errout:
	वापस err;
पूर्ण

अटल पूर्णांक mpls_netconf_dump_devconf(काष्ठा sk_buff *skb,
				     काष्ठा netlink_callback *cb)
अणु
	स्थिर काष्ठा nlmsghdr *nlh = cb->nlh;
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा hlist_head *head;
	काष्ठा net_device *dev;
	काष्ठा mpls_dev *mdev;
	पूर्णांक idx, s_idx;
	पूर्णांक h, s_h;

	अगर (cb->strict_check) अणु
		काष्ठा netlink_ext_ack *extack = cb->extack;
		काष्ठा netconfmsg *ncm;

		अगर (nlh->nlmsg_len < nlmsg_msg_size(माप(*ncm))) अणु
			NL_SET_ERR_MSG_MOD(extack, "Invalid header for netconf dump request");
			वापस -EINVAL;
		पूर्ण

		अगर (nlmsg_attrlen(nlh, माप(*ncm))) अणु
			NL_SET_ERR_MSG_MOD(extack, "Invalid data after header in netconf dump request");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	s_h = cb->args[0];
	s_idx = idx = cb->args[1];

	क्रम (h = s_h; h < NETDEV_HASHENTRIES; h++, s_idx = 0) अणु
		idx = 0;
		head = &net->dev_index_head[h];
		rcu_पढ़ो_lock();
		cb->seq = net->dev_base_seq;
		hlist_क्रम_each_entry_rcu(dev, head, index_hlist) अणु
			अगर (idx < s_idx)
				जाओ cont;
			mdev = mpls_dev_get(dev);
			अगर (!mdev)
				जाओ cont;
			अगर (mpls_netconf_fill_devconf(skb, mdev,
						      NETLINK_CB(cb->skb).portid,
						      nlh->nlmsg_seq,
						      RTM_NEWNETCONF,
						      NLM_F_MULTI,
						      NETCONFA_ALL) < 0) अणु
				rcu_पढ़ो_unlock();
				जाओ करोne;
			पूर्ण
			nl_dump_check_consistent(cb, nlmsg_hdr(skb));
cont:
			idx++;
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण
करोne:
	cb->args[0] = h;
	cb->args[1] = idx;

	वापस skb->len;
पूर्ण

#घोषणा MPLS_PERDEV_SYSCTL_OFFSET(field)	\
	(&((काष्ठा mpls_dev *)0)->field)

अटल पूर्णांक mpls_conf_proc(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
			  व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक oval = *(पूर्णांक *)ctl->data;
	पूर्णांक ret = proc_करोपूर्णांकvec(ctl, ग_लिखो, buffer, lenp, ppos);

	अगर (ग_लिखो) अणु
		काष्ठा mpls_dev *mdev = ctl->extra1;
		पूर्णांक i = (पूर्णांक *)ctl->data - (पूर्णांक *)mdev;
		काष्ठा net *net = ctl->extra2;
		पूर्णांक val = *(पूर्णांक *)ctl->data;

		अगर (i == दुरत्व(काष्ठा mpls_dev, input_enabled) &&
		    val != oval) अणु
			mpls_netconf_notअगरy_devconf(net, RTM_NEWNETCONF,
						    NETCONFA_INPUT, mdev);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा ctl_table mpls_dev_table[] = अणु
	अणु
		.procname	= "input",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= mpls_conf_proc,
		.data		= MPLS_PERDEV_SYSCTL_OFFSET(input_enabled),
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक mpls_dev_sysctl_रेजिस्टर(काष्ठा net_device *dev,
				    काष्ठा mpls_dev *mdev)
अणु
	अक्षर path[माप("net/mpls/conf/") + IFNAMSIZ];
	काष्ठा net *net = dev_net(dev);
	काष्ठा ctl_table *table;
	पूर्णांक i;

	table = kmemdup(&mpls_dev_table, माप(mpls_dev_table), GFP_KERNEL);
	अगर (!table)
		जाओ out;

	/* Table data contains only offsets relative to the base of
	 * the mdev at this poपूर्णांक, so make them असलolute.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(mpls_dev_table); i++) अणु
		table[i].data = (अक्षर *)mdev + (uपूर्णांकptr_t)table[i].data;
		table[i].extra1 = mdev;
		table[i].extra2 = net;
	पूर्ण

	snम_लिखो(path, माप(path), "net/mpls/conf/%s", dev->name);

	mdev->sysctl = रेजिस्टर_net_sysctl(net, path, table);
	अगर (!mdev->sysctl)
		जाओ मुक्त;

	mpls_netconf_notअगरy_devconf(net, RTM_NEWNETCONF, NETCONFA_ALL, mdev);
	वापस 0;

मुक्त:
	kमुक्त(table);
out:
	वापस -ENOBUFS;
पूर्ण

अटल व्योम mpls_dev_sysctl_unरेजिस्टर(काष्ठा net_device *dev,
				       काष्ठा mpls_dev *mdev)
अणु
	काष्ठा net *net = dev_net(dev);
	काष्ठा ctl_table *table;

	table = mdev->sysctl->ctl_table_arg;
	unरेजिस्टर_net_sysctl_table(mdev->sysctl);
	kमुक्त(table);

	mpls_netconf_notअगरy_devconf(net, RTM_DELNETCONF, 0, mdev);
पूर्ण

अटल काष्ठा mpls_dev *mpls_add_dev(काष्ठा net_device *dev)
अणु
	काष्ठा mpls_dev *mdev;
	पूर्णांक err = -ENOMEM;
	पूर्णांक i;

	ASSERT_RTNL();

	mdev = kzalloc(माप(*mdev), GFP_KERNEL);
	अगर (!mdev)
		वापस ERR_PTR(err);

	mdev->stats = alloc_percpu(काष्ठा mpls_pcpu_stats);
	अगर (!mdev->stats)
		जाओ मुक्त;

	क्रम_each_possible_cpu(i) अणु
		काष्ठा mpls_pcpu_stats *mpls_stats;

		mpls_stats = per_cpu_ptr(mdev->stats, i);
		u64_stats_init(&mpls_stats->syncp);
	पूर्ण

	mdev->dev = dev;

	err = mpls_dev_sysctl_रेजिस्टर(dev, mdev);
	अगर (err)
		जाओ मुक्त;

	rcu_assign_poपूर्णांकer(dev->mpls_ptr, mdev);

	वापस mdev;

मुक्त:
	मुक्त_percpu(mdev->stats);
	kमुक्त(mdev);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम mpls_dev_destroy_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा mpls_dev *mdev = container_of(head, काष्ठा mpls_dev, rcu);

	मुक्त_percpu(mdev->stats);
	kमुक्त(mdev);
पूर्ण

अटल व्योम mpls_अगरकरोwn(काष्ठा net_device *dev, पूर्णांक event)
अणु
	काष्ठा mpls_route __rcu **platक्रमm_label;
	काष्ठा net *net = dev_net(dev);
	u8 alive, deleted;
	अचिन्हित index;

	platक्रमm_label = rtnl_dereference(net->mpls.platक्रमm_label);
	क्रम (index = 0; index < net->mpls.platक्रमm_labels; index++) अणु
		काष्ठा mpls_route *rt = rtnl_dereference(platक्रमm_label[index]);

		अगर (!rt)
			जारी;

		alive = 0;
		deleted = 0;
		change_nexthops(rt) अणु
			अचिन्हित पूर्णांक nh_flags = nh->nh_flags;

			अगर (rtnl_dereference(nh->nh_dev) != dev)
				जाओ next;

			चयन (event) अणु
			हाल NETDEV_DOWN:
			हाल NETDEV_UNREGISTER:
				nh_flags |= RTNH_F_DEAD;
				fallthrough;
			हाल NETDEV_CHANGE:
				nh_flags |= RTNH_F_LINKDOWN;
				अवरोध;
			पूर्ण
			अगर (event == NETDEV_UNREGISTER)
				RCU_INIT_POINTER(nh->nh_dev, शून्य);

			अगर (nh->nh_flags != nh_flags)
				WRITE_ONCE(nh->nh_flags, nh_flags);
next:
			अगर (!(nh_flags & (RTNH_F_DEAD | RTNH_F_LINKDOWN)))
				alive++;
			अगर (!rtnl_dereference(nh->nh_dev))
				deleted++;
		पूर्ण endक्रम_nexthops(rt);

		WRITE_ONCE(rt->rt_nhn_alive, alive);

		/* अगर there are no more nexthops, delete the route */
		अगर (event == NETDEV_UNREGISTER && deleted == rt->rt_nhn)
			mpls_route_update(net, index, शून्य, शून्य);
	पूर्ण
पूर्ण

अटल व्योम mpls_अगरup(काष्ठा net_device *dev, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा mpls_route __rcu **platक्रमm_label;
	काष्ठा net *net = dev_net(dev);
	अचिन्हित index;
	u8 alive;

	platक्रमm_label = rtnl_dereference(net->mpls.platक्रमm_label);
	क्रम (index = 0; index < net->mpls.platक्रमm_labels; index++) अणु
		काष्ठा mpls_route *rt = rtnl_dereference(platक्रमm_label[index]);

		अगर (!rt)
			जारी;

		alive = 0;
		change_nexthops(rt) अणु
			अचिन्हित पूर्णांक nh_flags = nh->nh_flags;
			काष्ठा net_device *nh_dev =
				rtnl_dereference(nh->nh_dev);

			अगर (!(nh_flags & flags)) अणु
				alive++;
				जारी;
			पूर्ण
			अगर (nh_dev != dev)
				जारी;
			alive++;
			nh_flags &= ~flags;
			WRITE_ONCE(nh->nh_flags, nh_flags);
		पूर्ण endक्रम_nexthops(rt);

		WRITE_ONCE(rt->rt_nhn_alive, alive);
	पूर्ण
पूर्ण

अटल पूर्णांक mpls_dev_notअगरy(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event,
			   व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा mpls_dev *mdev;
	अचिन्हित पूर्णांक flags;

	अगर (event == NETDEV_REGISTER) अणु
		mdev = mpls_add_dev(dev);
		अगर (IS_ERR(mdev))
			वापस notअगरier_from_त्रुटि_सं(PTR_ERR(mdev));

		वापस NOTIFY_OK;
	पूर्ण

	mdev = mpls_dev_get(dev);
	अगर (!mdev)
		वापस NOTIFY_OK;

	चयन (event) अणु
	हाल NETDEV_DOWN:
		mpls_अगरकरोwn(dev, event);
		अवरोध;
	हाल NETDEV_UP:
		flags = dev_get_flags(dev);
		अगर (flags & (IFF_RUNNING | IFF_LOWER_UP))
			mpls_अगरup(dev, RTNH_F_DEAD | RTNH_F_LINKDOWN);
		अन्यथा
			mpls_अगरup(dev, RTNH_F_DEAD);
		अवरोध;
	हाल NETDEV_CHANGE:
		flags = dev_get_flags(dev);
		अगर (flags & (IFF_RUNNING | IFF_LOWER_UP))
			mpls_अगरup(dev, RTNH_F_DEAD | RTNH_F_LINKDOWN);
		अन्यथा
			mpls_अगरकरोwn(dev, event);
		अवरोध;
	हाल NETDEV_UNREGISTER:
		mpls_अगरकरोwn(dev, event);
		mdev = mpls_dev_get(dev);
		अगर (mdev) अणु
			mpls_dev_sysctl_unरेजिस्टर(dev, mdev);
			RCU_INIT_POINTER(dev->mpls_ptr, शून्य);
			call_rcu(&mdev->rcu, mpls_dev_destroy_rcu);
		पूर्ण
		अवरोध;
	हाल NETDEV_CHANGENAME:
		mdev = mpls_dev_get(dev);
		अगर (mdev) अणु
			पूर्णांक err;

			mpls_dev_sysctl_unरेजिस्टर(dev, mdev);
			err = mpls_dev_sysctl_रेजिस्टर(dev, mdev);
			अगर (err)
				वापस notअगरier_from_त्रुटि_सं(err);
		पूर्ण
		अवरोध;
	पूर्ण
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block mpls_dev_notअगरier = अणु
	.notअगरier_call = mpls_dev_notअगरy,
पूर्ण;

अटल पूर्णांक nla_put_via(काष्ठा sk_buff *skb,
		       u8 table, स्थिर व्योम *addr, पूर्णांक alen)
अणु
	अटल स्थिर पूर्णांक table_to_family[NEIGH_NR_TABLES + 1] = अणु
		AF_INET, AF_INET6, AF_DECnet, AF_PACKET,
	पूर्ण;
	काष्ठा nlattr *nla;
	काष्ठा rtvia *via;
	पूर्णांक family = AF_UNSPEC;

	nla = nla_reserve(skb, RTA_VIA, alen + 2);
	अगर (!nla)
		वापस -EMSGSIZE;

	अगर (table <= NEIGH_NR_TABLES)
		family = table_to_family[table];

	via = nla_data(nla);
	via->rtvia_family = family;
	स_नकल(via->rtvia_addr, addr, alen);
	वापस 0;
पूर्ण

पूर्णांक nla_put_labels(काष्ठा sk_buff *skb, पूर्णांक attrtype,
		   u8 labels, स्थिर u32 label[])
अणु
	काष्ठा nlattr *nla;
	काष्ठा mpls_shim_hdr *nla_label;
	bool bos;
	पूर्णांक i;
	nla = nla_reserve(skb, attrtype, labels*4);
	अगर (!nla)
		वापस -EMSGSIZE;

	nla_label = nla_data(nla);
	bos = true;
	क्रम (i = labels - 1; i >= 0; i--) अणु
		nla_label[i] = mpls_entry_encode(label[i], 0, 0, bos);
		bos = false;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nla_put_labels);

पूर्णांक nla_get_labels(स्थिर काष्ठा nlattr *nla, u8 max_labels, u8 *labels,
		   u32 label[], काष्ठा netlink_ext_ack *extack)
अणु
	अचिन्हित len = nla_len(nla);
	काष्ठा mpls_shim_hdr *nla_label;
	u8 nla_labels;
	bool bos;
	पूर्णांक i;

	/* len needs to be an even multiple of 4 (the label size). Number
	 * of labels is a u8 so check क्रम overflow.
	 */
	अगर (len & 3 || len / 4 > 255) अणु
		NL_SET_ERR_MSG_ATTR(extack, nla,
				    "Invalid length for labels attribute");
		वापस -EINVAL;
	पूर्ण

	/* Limit the number of new labels allowed */
	nla_labels = len/4;
	अगर (nla_labels > max_labels) अणु
		NL_SET_ERR_MSG(extack, "Too many labels");
		वापस -EINVAL;
	पूर्ण

	/* when label == शून्य, caller wants number of labels */
	अगर (!label)
		जाओ out;

	nla_label = nla_data(nla);
	bos = true;
	क्रम (i = nla_labels - 1; i >= 0; i--, bos = false) अणु
		काष्ठा mpls_entry_decoded dec;
		dec = mpls_entry_decode(nla_label + i);

		/* Ensure the bottom of stack flag is properly set
		 * and ttl and tc are both clear.
		 */
		अगर (dec.ttl) अणु
			NL_SET_ERR_MSG_ATTR(extack, nla,
					    "TTL in label must be 0");
			वापस -EINVAL;
		पूर्ण

		अगर (dec.tc) अणु
			NL_SET_ERR_MSG_ATTR(extack, nla,
					    "Traffic class in label must be 0");
			वापस -EINVAL;
		पूर्ण

		अगर (dec.bos != bos) अणु
			NL_SET_BAD_ATTR(extack, nla);
			अगर (bos) अणु
				NL_SET_ERR_MSG(extack,
					       "BOS bit must be set in first label");
			पूर्ण अन्यथा अणु
				NL_SET_ERR_MSG(extack,
					       "BOS bit can only be set in first label");
			पूर्ण
			वापस -EINVAL;
		पूर्ण

		चयन (dec.label) अणु
		हाल MPLS_LABEL_IMPLशून्य:
			/* RFC3032: This is a label that an LSR may
			 * assign and distribute, but which never
			 * actually appears in the encapsulation.
			 */
			NL_SET_ERR_MSG_ATTR(extack, nla,
					    "Implicit NULL Label (3) can not be used in encapsulation");
			वापस -EINVAL;
		पूर्ण

		label[i] = dec.label;
	पूर्ण
out:
	*labels = nla_labels;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nla_get_labels);

अटल पूर्णांक rपंचांग_to_route_config(काष्ठा sk_buff *skb,
			       काष्ठा nlmsghdr *nlh,
			       काष्ठा mpls_route_config *cfg,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा rपंचांगsg *rपंचांग;
	काष्ठा nlattr *tb[RTA_MAX+1];
	पूर्णांक index;
	पूर्णांक err;

	err = nlmsg_parse_deprecated(nlh, माप(*rपंचांग), tb, RTA_MAX,
				     rपंचांग_mpls_policy, extack);
	अगर (err < 0)
		जाओ errout;

	err = -EINVAL;
	rपंचांग = nlmsg_data(nlh);

	अगर (rपंचांग->rपंचांग_family != AF_MPLS) अणु
		NL_SET_ERR_MSG(extack, "Invalid address family in rtmsg");
		जाओ errout;
	पूर्ण
	अगर (rपंचांग->rपंचांग_dst_len != 20) अणु
		NL_SET_ERR_MSG(extack, "rtm_dst_len must be 20 for MPLS");
		जाओ errout;
	पूर्ण
	अगर (rपंचांग->rपंचांग_src_len != 0) अणु
		NL_SET_ERR_MSG(extack, "rtm_src_len must be 0 for MPLS");
		जाओ errout;
	पूर्ण
	अगर (rपंचांग->rपंचांग_tos != 0) अणु
		NL_SET_ERR_MSG(extack, "rtm_tos must be 0 for MPLS");
		जाओ errout;
	पूर्ण
	अगर (rपंचांग->rपंचांग_table != RT_TABLE_MAIN) अणु
		NL_SET_ERR_MSG(extack,
			       "MPLS only supports the main route table");
		जाओ errout;
	पूर्ण
	/* Any value is acceptable क्रम rपंचांग_protocol */

	/* As mpls uses destination specअगरic addresses
	 * (or source specअगरic address in the हाल of multicast)
	 * all addresses have universal scope.
	 */
	अगर (rपंचांग->rपंचांग_scope != RT_SCOPE_UNIVERSE) अणु
		NL_SET_ERR_MSG(extack,
			       "Invalid route scope  - MPLS only supports UNIVERSE");
		जाओ errout;
	पूर्ण
	अगर (rपंचांग->rपंचांग_type != RTN_UNICAST) अणु
		NL_SET_ERR_MSG(extack,
			       "Invalid route type - MPLS only supports UNICAST");
		जाओ errout;
	पूर्ण
	अगर (rपंचांग->rपंचांग_flags != 0) अणु
		NL_SET_ERR_MSG(extack, "rtm_flags must be 0 for MPLS");
		जाओ errout;
	पूर्ण

	cfg->rc_label		= LABEL_NOT_SPECIFIED;
	cfg->rc_protocol	= rपंचांग->rपंचांग_protocol;
	cfg->rc_via_table	= MPLS_NEIGH_TABLE_UNSPEC;
	cfg->rc_ttl_propagate	= MPLS_TTL_PROP_DEFAULT;
	cfg->rc_nlflags		= nlh->nlmsg_flags;
	cfg->rc_nlinfo.portid	= NETLINK_CB(skb).portid;
	cfg->rc_nlinfo.nlh	= nlh;
	cfg->rc_nlinfo.nl_net	= sock_net(skb->sk);

	क्रम (index = 0; index <= RTA_MAX; index++) अणु
		काष्ठा nlattr *nla = tb[index];
		अगर (!nla)
			जारी;

		चयन (index) अणु
		हाल RTA_OIF:
			cfg->rc_अगरindex = nla_get_u32(nla);
			अवरोध;
		हाल RTA_NEWDST:
			अगर (nla_get_labels(nla, MAX_NEW_LABELS,
					   &cfg->rc_output_labels,
					   cfg->rc_output_label, extack))
				जाओ errout;
			अवरोध;
		हाल RTA_DST:
		अणु
			u8 label_count;
			अगर (nla_get_labels(nla, 1, &label_count,
					   &cfg->rc_label, extack))
				जाओ errout;

			अगर (!mpls_label_ok(cfg->rc_nlinfo.nl_net,
					   &cfg->rc_label, extack))
				जाओ errout;
			अवरोध;
		पूर्ण
		हाल RTA_GATEWAY:
			NL_SET_ERR_MSG(extack, "MPLS does not support RTA_GATEWAY attribute");
			जाओ errout;
		हाल RTA_VIA:
		अणु
			अगर (nla_get_via(nla, &cfg->rc_via_alen,
					&cfg->rc_via_table, cfg->rc_via,
					extack))
				जाओ errout;
			अवरोध;
		पूर्ण
		हाल RTA_MULTIPATH:
		अणु
			cfg->rc_mp = nla_data(nla);
			cfg->rc_mp_len = nla_len(nla);
			अवरोध;
		पूर्ण
		हाल RTA_TTL_PROPAGATE:
		अणु
			u8 ttl_propagate = nla_get_u8(nla);

			अगर (ttl_propagate > 1) अणु
				NL_SET_ERR_MSG_ATTR(extack, nla,
						    "RTA_TTL_PROPAGATE can only be 0 or 1");
				जाओ errout;
			पूर्ण
			cfg->rc_ttl_propagate = ttl_propagate ?
				MPLS_TTL_PROP_ENABLED :
				MPLS_TTL_PROP_DISABLED;
			अवरोध;
		पूर्ण
		शेष:
			NL_SET_ERR_MSG_ATTR(extack, nla, "Unknown attribute");
			/* Unsupported attribute */
			जाओ errout;
		पूर्ण
	पूर्ण

	err = 0;
errout:
	वापस err;
पूर्ण

अटल पूर्णांक mpls_rपंचांग_delroute(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mpls_route_config *cfg;
	पूर्णांक err;

	cfg = kzalloc(माप(*cfg), GFP_KERNEL);
	अगर (!cfg)
		वापस -ENOMEM;

	err = rपंचांग_to_route_config(skb, nlh, cfg, extack);
	अगर (err < 0)
		जाओ out;

	err = mpls_route_del(cfg, extack);
out:
	kमुक्त(cfg);

	वापस err;
पूर्ण


अटल पूर्णांक mpls_rपंचांग_newroute(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mpls_route_config *cfg;
	पूर्णांक err;

	cfg = kzalloc(माप(*cfg), GFP_KERNEL);
	अगर (!cfg)
		वापस -ENOMEM;

	err = rपंचांग_to_route_config(skb, nlh, cfg, extack);
	अगर (err < 0)
		जाओ out;

	err = mpls_route_add(cfg, extack);
out:
	kमुक्त(cfg);

	वापस err;
पूर्ण

अटल पूर्णांक mpls_dump_route(काष्ठा sk_buff *skb, u32 portid, u32 seq, पूर्णांक event,
			   u32 label, काष्ठा mpls_route *rt, पूर्णांक flags)
अणु
	काष्ठा net_device *dev;
	काष्ठा nlmsghdr *nlh;
	काष्ठा rपंचांगsg *rपंचांग;

	nlh = nlmsg_put(skb, portid, seq, event, माप(*rपंचांग), flags);
	अगर (nlh == शून्य)
		वापस -EMSGSIZE;

	rपंचांग = nlmsg_data(nlh);
	rपंचांग->rपंचांग_family = AF_MPLS;
	rपंचांग->rपंचांग_dst_len = 20;
	rपंचांग->rपंचांग_src_len = 0;
	rपंचांग->rपंचांग_tos = 0;
	rपंचांग->rपंचांग_table = RT_TABLE_MAIN;
	rपंचांग->rपंचांग_protocol = rt->rt_protocol;
	rपंचांग->rपंचांग_scope = RT_SCOPE_UNIVERSE;
	rपंचांग->rपंचांग_type = RTN_UNICAST;
	rपंचांग->rपंचांग_flags = 0;

	अगर (nla_put_labels(skb, RTA_DST, 1, &label))
		जाओ nla_put_failure;

	अगर (rt->rt_ttl_propagate != MPLS_TTL_PROP_DEFAULT) अणु
		bool ttl_propagate =
			rt->rt_ttl_propagate == MPLS_TTL_PROP_ENABLED;

		अगर (nla_put_u8(skb, RTA_TTL_PROPAGATE,
			       ttl_propagate))
			जाओ nla_put_failure;
	पूर्ण
	अगर (rt->rt_nhn == 1) अणु
		स्थिर काष्ठा mpls_nh *nh = rt->rt_nh;

		अगर (nh->nh_labels &&
		    nla_put_labels(skb, RTA_NEWDST, nh->nh_labels,
				   nh->nh_label))
			जाओ nla_put_failure;
		अगर (nh->nh_via_table != MPLS_NEIGH_TABLE_UNSPEC &&
		    nla_put_via(skb, nh->nh_via_table, mpls_nh_via(rt, nh),
				nh->nh_via_alen))
			जाओ nla_put_failure;
		dev = rtnl_dereference(nh->nh_dev);
		अगर (dev && nla_put_u32(skb, RTA_OIF, dev->अगरindex))
			जाओ nla_put_failure;
		अगर (nh->nh_flags & RTNH_F_LINKDOWN)
			rपंचांग->rपंचांग_flags |= RTNH_F_LINKDOWN;
		अगर (nh->nh_flags & RTNH_F_DEAD)
			rपंचांग->rपंचांग_flags |= RTNH_F_DEAD;
	पूर्ण अन्यथा अणु
		काष्ठा rtnexthop *rtnh;
		काष्ठा nlattr *mp;
		u8 linkकरोwn = 0;
		u8 dead = 0;

		mp = nla_nest_start_noflag(skb, RTA_MULTIPATH);
		अगर (!mp)
			जाओ nla_put_failure;

		क्रम_nexthops(rt) अणु
			dev = rtnl_dereference(nh->nh_dev);
			अगर (!dev)
				जारी;

			rtnh = nla_reserve_nohdr(skb, माप(*rtnh));
			अगर (!rtnh)
				जाओ nla_put_failure;

			rtnh->rtnh_अगरindex = dev->अगरindex;
			अगर (nh->nh_flags & RTNH_F_LINKDOWN) अणु
				rtnh->rtnh_flags |= RTNH_F_LINKDOWN;
				linkकरोwn++;
			पूर्ण
			अगर (nh->nh_flags & RTNH_F_DEAD) अणु
				rtnh->rtnh_flags |= RTNH_F_DEAD;
				dead++;
			पूर्ण

			अगर (nh->nh_labels && nla_put_labels(skb, RTA_NEWDST,
							    nh->nh_labels,
							    nh->nh_label))
				जाओ nla_put_failure;
			अगर (nh->nh_via_table != MPLS_NEIGH_TABLE_UNSPEC &&
			    nla_put_via(skb, nh->nh_via_table,
					mpls_nh_via(rt, nh),
					nh->nh_via_alen))
				जाओ nla_put_failure;

			/* length of rtnetlink header + attributes */
			rtnh->rtnh_len = nlmsg_get_pos(skb) - (व्योम *)rtnh;
		पूर्ण endक्रम_nexthops(rt);

		अगर (linkकरोwn == rt->rt_nhn)
			rपंचांग->rपंचांग_flags |= RTNH_F_LINKDOWN;
		अगर (dead == rt->rt_nhn)
			rपंचांग->rपंचांग_flags |= RTNH_F_DEAD;

		nla_nest_end(skb, mp);
	पूर्ण

	nlmsg_end(skb, nlh);
	वापस 0;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

#अगर IS_ENABLED(CONFIG_INET)
अटल पूर्णांक mpls_valid_fib_dump_req(काष्ठा net *net, स्थिर काष्ठा nlmsghdr *nlh,
				   काष्ठा fib_dump_filter *filter,
				   काष्ठा netlink_callback *cb)
अणु
	वापस ip_valid_fib_dump_req(net, nlh, filter, cb);
पूर्ण
#अन्यथा
अटल पूर्णांक mpls_valid_fib_dump_req(काष्ठा net *net, स्थिर काष्ठा nlmsghdr *nlh,
				   काष्ठा fib_dump_filter *filter,
				   काष्ठा netlink_callback *cb)
अणु
	काष्ठा netlink_ext_ack *extack = cb->extack;
	काष्ठा nlattr *tb[RTA_MAX + 1];
	काष्ठा rपंचांगsg *rपंचांग;
	पूर्णांक err, i;

	अगर (nlh->nlmsg_len < nlmsg_msg_size(माप(*rपंचांग))) अणु
		NL_SET_ERR_MSG_MOD(extack, "Invalid header for FIB dump request");
		वापस -EINVAL;
	पूर्ण

	rपंचांग = nlmsg_data(nlh);
	अगर (rपंचांग->rपंचांग_dst_len || rपंचांग->rपंचांग_src_len  || rपंचांग->rपंचांग_tos   ||
	    rपंचांग->rपंचांग_table   || rपंचांग->rपंचांग_scope    || rपंचांग->rपंचांग_type  ||
	    rपंचांग->rपंचांग_flags) अणु
		NL_SET_ERR_MSG_MOD(extack, "Invalid values in header for FIB dump request");
		वापस -EINVAL;
	पूर्ण

	अगर (rपंचांग->rपंचांग_protocol) अणु
		filter->protocol = rपंचांग->rपंचांग_protocol;
		filter->filter_set = 1;
		cb->answer_flags = NLM_F_DUMP_FILTERED;
	पूर्ण

	err = nlmsg_parse_deprecated_strict(nlh, माप(*rपंचांग), tb, RTA_MAX,
					    rपंचांग_mpls_policy, extack);
	अगर (err < 0)
		वापस err;

	क्रम (i = 0; i <= RTA_MAX; ++i) अणु
		पूर्णांक अगरindex;

		अगर (i == RTA_OIF) अणु
			अगरindex = nla_get_u32(tb[i]);
			filter->dev = __dev_get_by_index(net, अगरindex);
			अगर (!filter->dev)
				वापस -ENODEV;
			filter->filter_set = 1;
		पूर्ण अन्यथा अगर (tb[i]) अणु
			NL_SET_ERR_MSG_MOD(extack, "Unsupported attribute in dump request");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल bool mpls_rt_uses_dev(काष्ठा mpls_route *rt,
			     स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा net_device *nh_dev;

	अगर (rt->rt_nhn == 1) अणु
		काष्ठा mpls_nh *nh = rt->rt_nh;

		nh_dev = rtnl_dereference(nh->nh_dev);
		अगर (dev == nh_dev)
			वापस true;
	पूर्ण अन्यथा अणु
		क्रम_nexthops(rt) अणु
			nh_dev = rtnl_dereference(nh->nh_dev);
			अगर (nh_dev == dev)
				वापस true;
		पूर्ण endक्रम_nexthops(rt);
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक mpls_dump_routes(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	स्थिर काष्ठा nlmsghdr *nlh = cb->nlh;
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा mpls_route __rcu **platक्रमm_label;
	काष्ठा fib_dump_filter filter = अणुपूर्ण;
	अचिन्हित पूर्णांक flags = NLM_F_MULTI;
	माप_प्रकार platक्रमm_labels;
	अचिन्हित पूर्णांक index;

	ASSERT_RTNL();

	अगर (cb->strict_check) अणु
		पूर्णांक err;

		err = mpls_valid_fib_dump_req(net, nlh, &filter, cb);
		अगर (err < 0)
			वापस err;

		/* क्रम MPLS, there is only 1 table with fixed type and flags.
		 * If either are set in the filter then वापस nothing.
		 */
		अगर ((filter.table_id && filter.table_id != RT_TABLE_MAIN) ||
		    (filter.rt_type && filter.rt_type != RTN_UNICAST) ||
		     filter.flags)
			वापस skb->len;
	पूर्ण

	index = cb->args[0];
	अगर (index < MPLS_LABEL_FIRST_UNRESERVED)
		index = MPLS_LABEL_FIRST_UNRESERVED;

	platक्रमm_label = rtnl_dereference(net->mpls.platक्रमm_label);
	platक्रमm_labels = net->mpls.platक्रमm_labels;

	अगर (filter.filter_set)
		flags |= NLM_F_DUMP_FILTERED;

	क्रम (; index < platक्रमm_labels; index++) अणु
		काष्ठा mpls_route *rt;

		rt = rtnl_dereference(platक्रमm_label[index]);
		अगर (!rt)
			जारी;

		अगर ((filter.dev && !mpls_rt_uses_dev(rt, filter.dev)) ||
		    (filter.protocol && rt->rt_protocol != filter.protocol))
			जारी;

		अगर (mpls_dump_route(skb, NETLINK_CB(cb->skb).portid,
				    cb->nlh->nlmsg_seq, RTM_NEWROUTE,
				    index, rt, flags) < 0)
			अवरोध;
	पूर्ण
	cb->args[0] = index;

	वापस skb->len;
पूर्ण

अटल अंतरभूत माप_प्रकार lfib_nlmsg_size(काष्ठा mpls_route *rt)
अणु
	माप_प्रकार payload =
		NLMSG_ALIGN(माप(काष्ठा rपंचांगsg))
		+ nla_total_size(4)			/* RTA_DST */
		+ nla_total_size(1);			/* RTA_TTL_PROPAGATE */

	अगर (rt->rt_nhn == 1) अणु
		काष्ठा mpls_nh *nh = rt->rt_nh;

		अगर (nh->nh_dev)
			payload += nla_total_size(4); /* RTA_OIF */
		अगर (nh->nh_via_table != MPLS_NEIGH_TABLE_UNSPEC) /* RTA_VIA */
			payload += nla_total_size(2 + nh->nh_via_alen);
		अगर (nh->nh_labels) /* RTA_NEWDST */
			payload += nla_total_size(nh->nh_labels * 4);
	पूर्ण अन्यथा अणु
		/* each nexthop is packed in an attribute */
		माप_प्रकार nhsize = 0;

		क्रम_nexthops(rt) अणु
			अगर (!rtnl_dereference(nh->nh_dev))
				जारी;
			nhsize += nla_total_size(माप(काष्ठा rtnexthop));
			/* RTA_VIA */
			अगर (nh->nh_via_table != MPLS_NEIGH_TABLE_UNSPEC)
				nhsize += nla_total_size(2 + nh->nh_via_alen);
			अगर (nh->nh_labels)
				nhsize += nla_total_size(nh->nh_labels * 4);
		पूर्ण endक्रम_nexthops(rt);
		/* nested attribute */
		payload += nla_total_size(nhsize);
	पूर्ण

	वापस payload;
पूर्ण

अटल व्योम rपंचांगsg_lfib(पूर्णांक event, u32 label, काष्ठा mpls_route *rt,
		       काष्ठा nlmsghdr *nlh, काष्ठा net *net, u32 portid,
		       अचिन्हित पूर्णांक nlm_flags)
अणु
	काष्ठा sk_buff *skb;
	u32 seq = nlh ? nlh->nlmsg_seq : 0;
	पूर्णांक err = -ENOBUFS;

	skb = nlmsg_new(lfib_nlmsg_size(rt), GFP_KERNEL);
	अगर (skb == शून्य)
		जाओ errout;

	err = mpls_dump_route(skb, portid, seq, event, label, rt, nlm_flags);
	अगर (err < 0) अणु
		/* -EMSGSIZE implies BUG in lfib_nlmsg_size */
		WARN_ON(err == -EMSGSIZE);
		kमुक्त_skb(skb);
		जाओ errout;
	पूर्ण
	rtnl_notअगरy(skb, net, portid, RTNLGRP_MPLS_ROUTE, nlh, GFP_KERNEL);

	वापस;
errout:
	अगर (err < 0)
		rtnl_set_sk_err(net, RTNLGRP_MPLS_ROUTE, err);
पूर्ण

अटल पूर्णांक mpls_valid_getroute_req(काष्ठा sk_buff *skb,
				   स्थिर काष्ठा nlmsghdr *nlh,
				   काष्ठा nlattr **tb,
				   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा rपंचांगsg *rपंचांग;
	पूर्णांक i, err;

	अगर (nlh->nlmsg_len < nlmsg_msg_size(माप(*rपंचांग))) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Invalid header for get route request");
		वापस -EINVAL;
	पूर्ण

	अगर (!netlink_strict_get_check(skb))
		वापस nlmsg_parse_deprecated(nlh, माप(*rपंचांग), tb, RTA_MAX,
					      rपंचांग_mpls_policy, extack);

	rपंचांग = nlmsg_data(nlh);
	अगर ((rपंचांग->rपंचांग_dst_len && rपंचांग->rपंचांग_dst_len != 20) ||
	    rपंचांग->rपंचांग_src_len || rपंचांग->rपंचांग_tos || rपंचांग->rपंचांग_table ||
	    rपंचांग->rपंचांग_protocol || rपंचांग->rपंचांग_scope || rपंचांग->rपंचांग_type) अणु
		NL_SET_ERR_MSG_MOD(extack, "Invalid values in header for get route request");
		वापस -EINVAL;
	पूर्ण
	अगर (rपंचांग->rपंचांग_flags & ~RTM_F_FIB_MATCH) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Invalid flags for get route request");
		वापस -EINVAL;
	पूर्ण

	err = nlmsg_parse_deprecated_strict(nlh, माप(*rपंचांग), tb, RTA_MAX,
					    rपंचांग_mpls_policy, extack);
	अगर (err)
		वापस err;

	अगर ((tb[RTA_DST] || tb[RTA_NEWDST]) && !rपंचांग->rपंचांग_dst_len) अणु
		NL_SET_ERR_MSG_MOD(extack, "rtm_dst_len must be 20 for MPLS");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i <= RTA_MAX; i++) अणु
		अगर (!tb[i])
			जारी;

		चयन (i) अणु
		हाल RTA_DST:
		हाल RTA_NEWDST:
			अवरोध;
		शेष:
			NL_SET_ERR_MSG_MOD(extack, "Unsupported attribute in get route request");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mpls_getroute(काष्ठा sk_buff *in_skb, काष्ठा nlmsghdr *in_nlh,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(in_skb->sk);
	u32 portid = NETLINK_CB(in_skb).portid;
	u32 in_label = LABEL_NOT_SPECIFIED;
	काष्ठा nlattr *tb[RTA_MAX + 1];
	u32 labels[MAX_NEW_LABELS];
	काष्ठा mpls_shim_hdr *hdr;
	अचिन्हित पूर्णांक hdr_size = 0;
	काष्ठा net_device *dev;
	काष्ठा mpls_route *rt;
	काष्ठा rपंचांगsg *rपंचांग, *r;
	काष्ठा nlmsghdr *nlh;
	काष्ठा sk_buff *skb;
	काष्ठा mpls_nh *nh;
	u8 n_labels;
	पूर्णांक err;

	err = mpls_valid_getroute_req(in_skb, in_nlh, tb, extack);
	अगर (err < 0)
		जाओ errout;

	rपंचांग = nlmsg_data(in_nlh);

	अगर (tb[RTA_DST]) अणु
		u8 label_count;

		अगर (nla_get_labels(tb[RTA_DST], 1, &label_count,
				   &in_label, extack)) अणु
			err = -EINVAL;
			जाओ errout;
		पूर्ण

		अगर (!mpls_label_ok(net, &in_label, extack)) अणु
			err = -EINVAL;
			जाओ errout;
		पूर्ण
	पूर्ण

	rt = mpls_route_input_rcu(net, in_label);
	अगर (!rt) अणु
		err = -ENETUNREACH;
		जाओ errout;
	पूर्ण

	अगर (rपंचांग->rपंचांग_flags & RTM_F_FIB_MATCH) अणु
		skb = nlmsg_new(lfib_nlmsg_size(rt), GFP_KERNEL);
		अगर (!skb) अणु
			err = -ENOBUFS;
			जाओ errout;
		पूर्ण

		err = mpls_dump_route(skb, portid, in_nlh->nlmsg_seq,
				      RTM_NEWROUTE, in_label, rt, 0);
		अगर (err < 0) अणु
			/* -EMSGSIZE implies BUG in lfib_nlmsg_size */
			WARN_ON(err == -EMSGSIZE);
			जाओ errout_मुक्त;
		पूर्ण

		वापस rtnl_unicast(skb, net, portid);
	पूर्ण

	अगर (tb[RTA_NEWDST]) अणु
		अगर (nla_get_labels(tb[RTA_NEWDST], MAX_NEW_LABELS, &n_labels,
				   labels, extack) != 0) अणु
			err = -EINVAL;
			जाओ errout;
		पूर्ण

		hdr_size = n_labels * माप(काष्ठा mpls_shim_hdr);
	पूर्ण

	skb = alloc_skb(NLMSG_GOODSIZE, GFP_KERNEL);
	अगर (!skb) अणु
		err = -ENOBUFS;
		जाओ errout;
	पूर्ण

	skb->protocol = htons(ETH_P_MPLS_UC);

	अगर (hdr_size) अणु
		bool bos;
		पूर्णांक i;

		अगर (skb_cow(skb, hdr_size)) अणु
			err = -ENOBUFS;
			जाओ errout_मुक्त;
		पूर्ण

		skb_reserve(skb, hdr_size);
		skb_push(skb, hdr_size);
		skb_reset_network_header(skb);

		/* Push new labels */
		hdr = mpls_hdr(skb);
		bos = true;
		क्रम (i = n_labels - 1; i >= 0; i--) अणु
			hdr[i] = mpls_entry_encode(labels[i],
						   1, 0, bos);
			bos = false;
		पूर्ण
	पूर्ण

	nh = mpls_select_multipath(rt, skb);
	अगर (!nh) अणु
		err = -ENETUNREACH;
		जाओ errout_मुक्त;
	पूर्ण

	अगर (hdr_size) अणु
		skb_pull(skb, hdr_size);
		skb_reset_network_header(skb);
	पूर्ण

	nlh = nlmsg_put(skb, portid, in_nlh->nlmsg_seq,
			RTM_NEWROUTE, माप(*r), 0);
	अगर (!nlh) अणु
		err = -EMSGSIZE;
		जाओ errout_मुक्त;
	पूर्ण

	r = nlmsg_data(nlh);
	r->rपंचांग_family	 = AF_MPLS;
	r->rपंचांग_dst_len	= 20;
	r->rपंचांग_src_len	= 0;
	r->rपंचांग_table	= RT_TABLE_MAIN;
	r->rपंचांग_type	= RTN_UNICAST;
	r->rपंचांग_scope	= RT_SCOPE_UNIVERSE;
	r->rपंचांग_protocol = rt->rt_protocol;
	r->rपंचांग_flags	= 0;

	अगर (nla_put_labels(skb, RTA_DST, 1, &in_label))
		जाओ nla_put_failure;

	अगर (nh->nh_labels &&
	    nla_put_labels(skb, RTA_NEWDST, nh->nh_labels,
			   nh->nh_label))
		जाओ nla_put_failure;

	अगर (nh->nh_via_table != MPLS_NEIGH_TABLE_UNSPEC &&
	    nla_put_via(skb, nh->nh_via_table, mpls_nh_via(rt, nh),
			nh->nh_via_alen))
		जाओ nla_put_failure;
	dev = rtnl_dereference(nh->nh_dev);
	अगर (dev && nla_put_u32(skb, RTA_OIF, dev->अगरindex))
		जाओ nla_put_failure;

	nlmsg_end(skb, nlh);

	err = rtnl_unicast(skb, net, portid);
errout:
	वापस err;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	err = -EMSGSIZE;
errout_मुक्त:
	kमुक्त_skb(skb);
	वापस err;
पूर्ण

अटल पूर्णांक resize_platक्रमm_label_table(काष्ठा net *net, माप_प्रकार limit)
अणु
	माप_प्रकार size = माप(काष्ठा mpls_route *) * limit;
	माप_प्रकार old_limit;
	माप_प्रकार cp_size;
	काष्ठा mpls_route __rcu **labels = शून्य, **old;
	काष्ठा mpls_route *rt0 = शून्य, *rt2 = शून्य;
	अचिन्हित index;

	अगर (size) अणु
		labels = kvzalloc(size, GFP_KERNEL);
		अगर (!labels)
			जाओ nolabels;
	पूर्ण

	/* In हाल the predefined labels need to be populated */
	अगर (limit > MPLS_LABEL_IPV4शून्य) अणु
		काष्ठा net_device *lo = net->loopback_dev;
		rt0 = mpls_rt_alloc(1, lo->addr_len, 0);
		अगर (IS_ERR(rt0))
			जाओ nort0;
		RCU_INIT_POINTER(rt0->rt_nh->nh_dev, lo);
		rt0->rt_protocol = RTPROT_KERNEL;
		rt0->rt_payload_type = MPT_IPV4;
		rt0->rt_ttl_propagate = MPLS_TTL_PROP_DEFAULT;
		rt0->rt_nh->nh_via_table = NEIGH_LINK_TABLE;
		rt0->rt_nh->nh_via_alen = lo->addr_len;
		स_नकल(__mpls_nh_via(rt0, rt0->rt_nh), lo->dev_addr,
		       lo->addr_len);
	पूर्ण
	अगर (limit > MPLS_LABEL_IPV6शून्य) अणु
		काष्ठा net_device *lo = net->loopback_dev;
		rt2 = mpls_rt_alloc(1, lo->addr_len, 0);
		अगर (IS_ERR(rt2))
			जाओ nort2;
		RCU_INIT_POINTER(rt2->rt_nh->nh_dev, lo);
		rt2->rt_protocol = RTPROT_KERNEL;
		rt2->rt_payload_type = MPT_IPV6;
		rt2->rt_ttl_propagate = MPLS_TTL_PROP_DEFAULT;
		rt2->rt_nh->nh_via_table = NEIGH_LINK_TABLE;
		rt2->rt_nh->nh_via_alen = lo->addr_len;
		स_नकल(__mpls_nh_via(rt2, rt2->rt_nh), lo->dev_addr,
		       lo->addr_len);
	पूर्ण

	rtnl_lock();
	/* Remember the original table */
	old = rtnl_dereference(net->mpls.platक्रमm_label);
	old_limit = net->mpls.platक्रमm_labels;

	/* Free any labels beyond the new table */
	क्रम (index = limit; index < old_limit; index++)
		mpls_route_update(net, index, शून्य, शून्य);

	/* Copy over the old labels */
	cp_size = size;
	अगर (old_limit < limit)
		cp_size = old_limit * माप(काष्ठा mpls_route *);

	स_नकल(labels, old, cp_size);

	/* If needed set the predefined labels */
	अगर ((old_limit <= MPLS_LABEL_IPV6शून्य) &&
	    (limit > MPLS_LABEL_IPV6शून्य)) अणु
		RCU_INIT_POINTER(labels[MPLS_LABEL_IPV6शून्य], rt2);
		rt2 = शून्य;
	पूर्ण

	अगर ((old_limit <= MPLS_LABEL_IPV4शून्य) &&
	    (limit > MPLS_LABEL_IPV4शून्य)) अणु
		RCU_INIT_POINTER(labels[MPLS_LABEL_IPV4शून्य], rt0);
		rt0 = शून्य;
	पूर्ण

	/* Update the global poपूर्णांकers */
	net->mpls.platक्रमm_labels = limit;
	rcu_assign_poपूर्णांकer(net->mpls.platक्रमm_label, labels);

	rtnl_unlock();

	mpls_rt_मुक्त(rt2);
	mpls_rt_मुक्त(rt0);

	अगर (old) अणु
		synchronize_rcu();
		kvमुक्त(old);
	पूर्ण
	वापस 0;

nort2:
	mpls_rt_मुक्त(rt0);
nort0:
	kvमुक्त(labels);
nolabels:
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक mpls_platक्रमm_labels(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
				व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा net *net = table->data;
	पूर्णांक platक्रमm_labels = net->mpls.platक्रमm_labels;
	पूर्णांक ret;
	काष्ठा ctl_table पंचांगp = अणु
		.procname	= table->procname,
		.data		= &platक्रमm_labels,
		.maxlen		= माप(पूर्णांक),
		.mode		= table->mode,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &label_limit,
	पूर्ण;

	ret = proc_करोपूर्णांकvec_minmax(&पंचांगp, ग_लिखो, buffer, lenp, ppos);

	अगर (ग_लिखो && ret == 0)
		ret = resize_platक्रमm_label_table(net, platक्रमm_labels);

	वापस ret;
पूर्ण

#घोषणा MPLS_NS_SYSCTL_OFFSET(field)		\
	(&((काष्ठा net *)0)->field)

अटल स्थिर काष्ठा ctl_table mpls_table[] = अणु
	अणु
		.procname	= "platform_labels",
		.data		= शून्य,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= mpls_platक्रमm_labels,
	पूर्ण,
	अणु
		.procname	= "ip_ttl_propagate",
		.data		= MPLS_NS_SYSCTL_OFFSET(mpls.ip_ttl_propagate),
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
	अणु
		.procname	= "default_ttl",
		.data		= MPLS_NS_SYSCTL_OFFSET(mpls.शेष_ttl),
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ONE,
		.extra2		= &ttl_max,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक mpls_net_init(काष्ठा net *net)
अणु
	काष्ठा ctl_table *table;
	पूर्णांक i;

	net->mpls.platक्रमm_labels = 0;
	net->mpls.platक्रमm_label = शून्य;
	net->mpls.ip_ttl_propagate = 1;
	net->mpls.शेष_ttl = 255;

	table = kmemdup(mpls_table, माप(mpls_table), GFP_KERNEL);
	अगर (table == शून्य)
		वापस -ENOMEM;

	/* Table data contains only offsets relative to the base of
	 * the mdev at this poपूर्णांक, so make them असलolute.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(mpls_table) - 1; i++)
		table[i].data = (अक्षर *)net + (uपूर्णांकptr_t)table[i].data;

	net->mpls.ctl = रेजिस्टर_net_sysctl(net, "net/mpls", table);
	अगर (net->mpls.ctl == शून्य) अणु
		kमुक्त(table);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mpls_net_निकास(काष्ठा net *net)
अणु
	काष्ठा mpls_route __rcu **platक्रमm_label;
	माप_प्रकार platक्रमm_labels;
	काष्ठा ctl_table *table;
	अचिन्हित पूर्णांक index;

	table = net->mpls.ctl->ctl_table_arg;
	unरेजिस्टर_net_sysctl_table(net->mpls.ctl);
	kमुक्त(table);

	/* An rcu grace period has passed since there was a device in
	 * the network namespace (and thus the last in flight packet)
	 * left this network namespace.  This is because
	 * unरेजिस्टर_netdevice_many and netdev_run_toकरो has completed
	 * क्रम each network device that was in this network namespace.
	 *
	 * As such no additional rcu synchronization is necessary when
	 * मुक्तing the platक्रमm_label table.
	 */
	rtnl_lock();
	platक्रमm_label = rtnl_dereference(net->mpls.platक्रमm_label);
	platक्रमm_labels = net->mpls.platक्रमm_labels;
	क्रम (index = 0; index < platक्रमm_labels; index++) अणु
		काष्ठा mpls_route *rt = rtnl_dereference(platक्रमm_label[index]);
		RCU_INIT_POINTER(platक्रमm_label[index], शून्य);
		mpls_notअगरy_route(net, index, rt, शून्य, शून्य);
		mpls_rt_मुक्त(rt);
	पूर्ण
	rtnl_unlock();

	kvमुक्त(platक्रमm_label);
पूर्ण

अटल काष्ठा pernet_operations mpls_net_ops = अणु
	.init = mpls_net_init,
	.निकास = mpls_net_निकास,
पूर्ण;

अटल काष्ठा rtnl_af_ops mpls_af_ops __पढ़ो_mostly = अणु
	.family		   = AF_MPLS,
	.fill_stats_af	   = mpls_fill_stats_af,
	.get_stats_af_size = mpls_get_stats_af_size,
पूर्ण;

अटल पूर्णांक __init mpls_init(व्योम)
अणु
	पूर्णांक err;

	BUILD_BUG_ON(माप(काष्ठा mpls_shim_hdr) != 4);

	err = रेजिस्टर_pernet_subsys(&mpls_net_ops);
	अगर (err)
		जाओ out;

	err = रेजिस्टर_netdevice_notअगरier(&mpls_dev_notअगरier);
	अगर (err)
		जाओ out_unरेजिस्टर_pernet;

	dev_add_pack(&mpls_packet_type);

	rtnl_af_रेजिस्टर(&mpls_af_ops);

	rtnl_रेजिस्टर_module(THIS_MODULE, PF_MPLS, RTM_NEWROUTE,
			     mpls_rपंचांग_newroute, शून्य, 0);
	rtnl_रेजिस्टर_module(THIS_MODULE, PF_MPLS, RTM_DELROUTE,
			     mpls_rपंचांग_delroute, शून्य, 0);
	rtnl_रेजिस्टर_module(THIS_MODULE, PF_MPLS, RTM_GETROUTE,
			     mpls_getroute, mpls_dump_routes, 0);
	rtnl_रेजिस्टर_module(THIS_MODULE, PF_MPLS, RTM_GETNETCONF,
			     mpls_netconf_get_devconf,
			     mpls_netconf_dump_devconf, 0);
	err = ipgre_tunnel_encap_add_mpls_ops();
	अगर (err)
		pr_err("Can't add mpls over gre tunnel ops\n");

	err = 0;
out:
	वापस err;

out_unरेजिस्टर_pernet:
	unरेजिस्टर_pernet_subsys(&mpls_net_ops);
	जाओ out;
पूर्ण
module_init(mpls_init);

अटल व्योम __निकास mpls_निकास(व्योम)
अणु
	rtnl_unरेजिस्टर_all(PF_MPLS);
	rtnl_af_unरेजिस्टर(&mpls_af_ops);
	dev_हटाओ_pack(&mpls_packet_type);
	unरेजिस्टर_netdevice_notअगरier(&mpls_dev_notअगरier);
	unरेजिस्टर_pernet_subsys(&mpls_net_ops);
	ipgre_tunnel_encap_del_mpls_ops();
पूर्ण
module_निकास(mpls_निकास);

MODULE_DESCRIPTION("MultiProtocol Label Switching");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS_NETPROTO(PF_MPLS);
