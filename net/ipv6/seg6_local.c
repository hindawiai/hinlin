<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  SR-IPv6 implementation
 *
 *  Authors:
 *  David Lebrun <david.lebrun@uclouvain.be>
 *  eBPF support: Mathieu Xhonneux <m.xhonneux@gmail.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/net.h>
#समावेश <linux/module.h>
#समावेश <net/ip.h>
#समावेश <net/lwtunnel.h>
#समावेश <net/netevent.h>
#समावेश <net/netns/generic.h>
#समावेश <net/ip6_fib.h>
#समावेश <net/route.h>
#समावेश <net/seg6.h>
#समावेश <linux/seg6.h>
#समावेश <linux/seg6_local.h>
#समावेश <net/addrconf.h>
#समावेश <net/ip6_route.h>
#समावेश <net/dst_cache.h>
#समावेश <net/ip_tunnels.h>
#अगर_घोषित CONFIG_IPV6_SEG6_HMAC
#समावेश <net/seg6_hmac.h>
#पूर्ण_अगर
#समावेश <net/seg6_local.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/bpf.h>

#घोषणा SEG6_F_ATTR(i)		BIT(i)

काष्ठा seg6_local_lwt;

/* callbacks used क्रम customizing the creation and deकाष्ठाion of a behavior */
काष्ठा seg6_local_lwtunnel_ops अणु
	पूर्णांक (*build_state)(काष्ठा seg6_local_lwt *slwt, स्थिर व्योम *cfg,
			   काष्ठा netlink_ext_ack *extack);
	व्योम (*destroy_state)(काष्ठा seg6_local_lwt *slwt);
पूर्ण;

काष्ठा seg6_action_desc अणु
	पूर्णांक action;
	अचिन्हित दीर्घ attrs;

	/* The optattrs field is used क्रम specअगरying all the optional
	 * attributes supported by a specअगरic behavior.
	 * It means that अगर one of these attributes is not provided in the
	 * netlink message during the behavior creation, no errors will be
	 * वापसed to the userspace.
	 *
	 * Each attribute can be only of two types (mutually exclusive):
	 * 1) required or 2) optional.
	 * Every user MUST obey to this rule! If you set an attribute as
	 * required the same attribute CANNOT be set as optional and vice
	 * versa.
	 */
	अचिन्हित दीर्घ optattrs;

	पूर्णांक (*input)(काष्ठा sk_buff *skb, काष्ठा seg6_local_lwt *slwt);
	पूर्णांक अटल_headroom;

	काष्ठा seg6_local_lwtunnel_ops slwt_ops;
पूर्ण;

काष्ठा bpf_lwt_prog अणु
	काष्ठा bpf_prog *prog;
	अक्षर *name;
पूर्ण;

क्रमागत seg6_end_dt_mode अणु
	DT_INVALID_MODE	= -EINVAL,
	DT_LEGACY_MODE	= 0,
	DT_VRF_MODE	= 1,
पूर्ण;

काष्ठा seg6_end_dt_info अणु
	क्रमागत seg6_end_dt_mode mode;

	काष्ठा net *net;
	/* VRF device associated to the routing table used by the SRv6
	 * End.DT4/DT6 behavior क्रम routing IPv4/IPv6 packets.
	 */
	पूर्णांक vrf_अगरindex;
	पूर्णांक vrf_table;

	/* tunneled packet proto and family (IPv4 or IPv6) */
	__be16 proto;
	u16 family;
	पूर्णांक hdrlen;
पूर्ण;

काष्ठा pcpu_seg6_local_counters अणु
	u64_stats_t packets;
	u64_stats_t bytes;
	u64_stats_t errors;

	काष्ठा u64_stats_sync syncp;
पूर्ण;

/* This काष्ठा groups all the SRv6 Behavior counters supported so far.
 *
 * put_nla_counters() makes use of this data काष्ठाure to collect all counter
 * values after the per-CPU counter evaluation has been perक्रमmed.
 * Finally, each counter value (in seg6_local_counters) is stored in the
 * corresponding netlink attribute and sent to user space.
 *
 * NB: we करोn't want to expose this काष्ठाure to user space!
 */
काष्ठा seg6_local_counters अणु
	__u64 packets;
	__u64 bytes;
	__u64 errors;
पूर्ण;

#घोषणा seg6_local_alloc_pcpu_counters(__gfp)				\
	__netdev_alloc_pcpu_stats(काष्ठा pcpu_seg6_local_counters,	\
				  ((__gfp) | __GFP_ZERO))

#घोषणा SEG6_F_LOCAL_COUNTERS	SEG6_F_ATTR(SEG6_LOCAL_COUNTERS)

काष्ठा seg6_local_lwt अणु
	पूर्णांक action;
	काष्ठा ipv6_sr_hdr *srh;
	पूर्णांक table;
	काष्ठा in_addr nh4;
	काष्ठा in6_addr nh6;
	पूर्णांक iअगर;
	पूर्णांक oअगर;
	काष्ठा bpf_lwt_prog bpf;
#अगर_घोषित CONFIG_NET_L3_MASTER_DEV
	काष्ठा seg6_end_dt_info dt_info;
#पूर्ण_अगर
	काष्ठा pcpu_seg6_local_counters __percpu *pcpu_counters;

	पूर्णांक headroom;
	काष्ठा seg6_action_desc *desc;
	/* unlike the required attrs, we have to track the optional attributes
	 * that have been effectively parsed.
	 */
	अचिन्हित दीर्घ parsed_optattrs;
पूर्ण;

अटल काष्ठा seg6_local_lwt *seg6_local_lwtunnel(काष्ठा lwtunnel_state *lwt)
अणु
	वापस (काष्ठा seg6_local_lwt *)lwt->data;
पूर्ण

अटल काष्ठा ipv6_sr_hdr *get_srh(काष्ठा sk_buff *skb, पूर्णांक flags)
अणु
	काष्ठा ipv6_sr_hdr *srh;
	पूर्णांक len, srhoff = 0;

	अगर (ipv6_find_hdr(skb, &srhoff, IPPROTO_ROUTING, शून्य, &flags) < 0)
		वापस शून्य;

	अगर (!pskb_may_pull(skb, srhoff + माप(*srh)))
		वापस शून्य;

	srh = (काष्ठा ipv6_sr_hdr *)(skb->data + srhoff);

	len = (srh->hdrlen + 1) << 3;

	अगर (!pskb_may_pull(skb, srhoff + len))
		वापस शून्य;

	/* note that pskb_may_pull may change poपूर्णांकers in header;
	 * क्रम this reason it is necessary to reload them when needed.
	 */
	srh = (काष्ठा ipv6_sr_hdr *)(skb->data + srhoff);

	अगर (!seg6_validate_srh(srh, len, true))
		वापस शून्य;

	वापस srh;
पूर्ण

अटल काष्ठा ipv6_sr_hdr *get_and_validate_srh(काष्ठा sk_buff *skb)
अणु
	काष्ठा ipv6_sr_hdr *srh;

	srh = get_srh(skb, IP6_FH_F_SKIP_RH);
	अगर (!srh)
		वापस शून्य;

#अगर_घोषित CONFIG_IPV6_SEG6_HMAC
	अगर (!seg6_hmac_validate_skb(skb))
		वापस शून्य;
#पूर्ण_अगर

	वापस srh;
पूर्ण

अटल bool decap_and_validate(काष्ठा sk_buff *skb, पूर्णांक proto)
अणु
	काष्ठा ipv6_sr_hdr *srh;
	अचिन्हित पूर्णांक off = 0;

	srh = get_srh(skb, 0);
	अगर (srh && srh->segments_left > 0)
		वापस false;

#अगर_घोषित CONFIG_IPV6_SEG6_HMAC
	अगर (srh && !seg6_hmac_validate_skb(skb))
		वापस false;
#पूर्ण_अगर

	अगर (ipv6_find_hdr(skb, &off, proto, शून्य, शून्य) < 0)
		वापस false;

	अगर (!pskb_pull(skb, off))
		वापस false;

	skb_postpull_rcsum(skb, skb_network_header(skb), off);

	skb_reset_network_header(skb);
	skb_reset_transport_header(skb);
	अगर (iptunnel_pull_offloads(skb))
		वापस false;

	वापस true;
पूर्ण

अटल व्योम advance_nextseg(काष्ठा ipv6_sr_hdr *srh, काष्ठा in6_addr *daddr)
अणु
	काष्ठा in6_addr *addr;

	srh->segments_left--;
	addr = srh->segments + srh->segments_left;
	*daddr = *addr;
पूर्ण

अटल पूर्णांक
seg6_lookup_any_nexthop(काष्ठा sk_buff *skb, काष्ठा in6_addr *nhaddr,
			u32 tbl_id, bool local_delivery)
अणु
	काष्ठा net *net = dev_net(skb->dev);
	काष्ठा ipv6hdr *hdr = ipv6_hdr(skb);
	पूर्णांक flags = RT6_LOOKUP_F_HAS_SADDR;
	काष्ठा dst_entry *dst = शून्य;
	काष्ठा rt6_info *rt;
	काष्ठा flowi6 fl6;
	पूर्णांक dev_flags = 0;

	fl6.flowi6_iअगर = skb->dev->अगरindex;
	fl6.daddr = nhaddr ? *nhaddr : hdr->daddr;
	fl6.saddr = hdr->saddr;
	fl6.flowlabel = ip6_flowinfo(hdr);
	fl6.flowi6_mark = skb->mark;
	fl6.flowi6_proto = hdr->nexthdr;

	अगर (nhaddr)
		fl6.flowi6_flags = FLOWI_FLAG_KNOWN_NH;

	अगर (!tbl_id) अणु
		dst = ip6_route_input_lookup(net, skb->dev, &fl6, skb, flags);
	पूर्ण अन्यथा अणु
		काष्ठा fib6_table *table;

		table = fib6_get_table(net, tbl_id);
		अगर (!table)
			जाओ out;

		rt = ip6_pol_route(net, table, 0, &fl6, skb, flags);
		dst = &rt->dst;
	पूर्ण

	/* we want to discard traffic destined क्रम local packet processing,
	 * अगर @local_delivery is set to false.
	 */
	अगर (!local_delivery)
		dev_flags |= IFF_LOOPBACK;

	अगर (dst && (dst->dev->flags & dev_flags) && !dst->error) अणु
		dst_release(dst);
		dst = शून्य;
	पूर्ण

out:
	अगर (!dst) अणु
		rt = net->ipv6.ip6_blk_hole_entry;
		dst = &rt->dst;
		dst_hold(dst);
	पूर्ण

	skb_dst_drop(skb);
	skb_dst_set(skb, dst);
	वापस dst->error;
पूर्ण

पूर्णांक seg6_lookup_nexthop(काष्ठा sk_buff *skb,
			काष्ठा in6_addr *nhaddr, u32 tbl_id)
अणु
	वापस seg6_lookup_any_nexthop(skb, nhaddr, tbl_id, false);
पूर्ण

/* regular endpoपूर्णांक function */
अटल पूर्णांक input_action_end(काष्ठा sk_buff *skb, काष्ठा seg6_local_lwt *slwt)
अणु
	काष्ठा ipv6_sr_hdr *srh;

	srh = get_and_validate_srh(skb);
	अगर (!srh)
		जाओ drop;

	advance_nextseg(srh, &ipv6_hdr(skb)->daddr);

	seg6_lookup_nexthop(skb, शून्य, 0);

	वापस dst_input(skb);

drop:
	kमुक्त_skb(skb);
	वापस -EINVAL;
पूर्ण

/* regular endpoपूर्णांक, and क्रमward to specअगरied nexthop */
अटल पूर्णांक input_action_end_x(काष्ठा sk_buff *skb, काष्ठा seg6_local_lwt *slwt)
अणु
	काष्ठा ipv6_sr_hdr *srh;

	srh = get_and_validate_srh(skb);
	अगर (!srh)
		जाओ drop;

	advance_nextseg(srh, &ipv6_hdr(skb)->daddr);

	seg6_lookup_nexthop(skb, &slwt->nh6, 0);

	वापस dst_input(skb);

drop:
	kमुक्त_skb(skb);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक input_action_end_t(काष्ठा sk_buff *skb, काष्ठा seg6_local_lwt *slwt)
अणु
	काष्ठा ipv6_sr_hdr *srh;

	srh = get_and_validate_srh(skb);
	अगर (!srh)
		जाओ drop;

	advance_nextseg(srh, &ipv6_hdr(skb)->daddr);

	seg6_lookup_nexthop(skb, शून्य, slwt->table);

	वापस dst_input(skb);

drop:
	kमुक्त_skb(skb);
	वापस -EINVAL;
पूर्ण

/* decapsulate and क्रमward inner L2 frame on specअगरied पूर्णांकerface */
अटल पूर्णांक input_action_end_dx2(काष्ठा sk_buff *skb,
				काष्ठा seg6_local_lwt *slwt)
अणु
	काष्ठा net *net = dev_net(skb->dev);
	काष्ठा net_device *odev;
	काष्ठा ethhdr *eth;

	अगर (!decap_and_validate(skb, IPPROTO_ETHERNET))
		जाओ drop;

	अगर (!pskb_may_pull(skb, ETH_HLEN))
		जाओ drop;

	skb_reset_mac_header(skb);
	eth = (काष्ठा ethhdr *)skb->data;

	/* To determine the frame's protocol, we assume it is 802.3. This aव्योमs
	 * a call to eth_type_trans(), which is not really relevant क्रम our
	 * use हाल.
	 */
	अगर (!eth_proto_is_802_3(eth->h_proto))
		जाओ drop;

	odev = dev_get_by_index_rcu(net, slwt->oअगर);
	अगर (!odev)
		जाओ drop;

	/* As we accept Ethernet frames, make sure the egress device is of
	 * the correct type.
	 */
	अगर (odev->type != ARPHRD_ETHER)
		जाओ drop;

	अगर (!(odev->flags & IFF_UP) || !netअगर_carrier_ok(odev))
		जाओ drop;

	skb_orphan(skb);

	अगर (skb_warn_अगर_lro(skb))
		जाओ drop;

	skb_क्रमward_csum(skb);

	अगर (skb->len - ETH_HLEN > odev->mtu)
		जाओ drop;

	skb->dev = odev;
	skb->protocol = eth->h_proto;

	वापस dev_queue_xmit(skb);

drop:
	kमुक्त_skb(skb);
	वापस -EINVAL;
पूर्ण

/* decapsulate and क्रमward to specअगरied nexthop */
अटल पूर्णांक input_action_end_dx6(काष्ठा sk_buff *skb,
				काष्ठा seg6_local_lwt *slwt)
अणु
	काष्ठा in6_addr *nhaddr = शून्य;

	/* this function accepts IPv6 encapsulated packets, with either
	 * an SRH with SL=0, or no SRH.
	 */

	अगर (!decap_and_validate(skb, IPPROTO_IPV6))
		जाओ drop;

	अगर (!pskb_may_pull(skb, माप(काष्ठा ipv6hdr)))
		जाओ drop;

	/* The inner packet is not associated to any local पूर्णांकerface,
	 * so we करो not call netअगर_rx().
	 *
	 * If slwt->nh6 is set to ::, then lookup the nexthop क्रम the
	 * inner packet's DA. Otherwise, use the specअगरied nexthop.
	 */

	अगर (!ipv6_addr_any(&slwt->nh6))
		nhaddr = &slwt->nh6;

	skb_set_transport_header(skb, माप(काष्ठा ipv6hdr));

	seg6_lookup_nexthop(skb, nhaddr, 0);

	वापस dst_input(skb);
drop:
	kमुक्त_skb(skb);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक input_action_end_dx4(काष्ठा sk_buff *skb,
				काष्ठा seg6_local_lwt *slwt)
अणु
	काष्ठा iphdr *iph;
	__be32 nhaddr;
	पूर्णांक err;

	अगर (!decap_and_validate(skb, IPPROTO_IPIP))
		जाओ drop;

	अगर (!pskb_may_pull(skb, माप(काष्ठा iphdr)))
		जाओ drop;

	skb->protocol = htons(ETH_P_IP);

	iph = ip_hdr(skb);

	nhaddr = slwt->nh4.s_addr ?: iph->daddr;

	skb_dst_drop(skb);

	skb_set_transport_header(skb, माप(काष्ठा iphdr));

	err = ip_route_input(skb, nhaddr, iph->saddr, 0, skb->dev);
	अगर (err)
		जाओ drop;

	वापस dst_input(skb);

drop:
	kमुक्त_skb(skb);
	वापस -EINVAL;
पूर्ण

#अगर_घोषित CONFIG_NET_L3_MASTER_DEV
अटल काष्ठा net *fib6_config_get_net(स्थिर काष्ठा fib6_config *fib6_cfg)
अणु
	स्थिर काष्ठा nl_info *nli = &fib6_cfg->fc_nlinfo;

	वापस nli->nl_net;
पूर्ण

अटल पूर्णांक __seg6_end_dt_vrf_build(काष्ठा seg6_local_lwt *slwt, स्थिर व्योम *cfg,
				   u16 family, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा seg6_end_dt_info *info = &slwt->dt_info;
	पूर्णांक vrf_अगरindex;
	काष्ठा net *net;

	net = fib6_config_get_net(cfg);

	/* note that vrf_table was alपढ़ोy set by parse_nla_vrftable() */
	vrf_अगरindex = l3mdev_अगरindex_lookup_by_table_id(L3MDEV_TYPE_VRF, net,
							info->vrf_table);
	अगर (vrf_अगरindex < 0) अणु
		अगर (vrf_अगरindex == -EPERM) अणु
			NL_SET_ERR_MSG(extack,
				       "Strict mode for VRF is disabled");
		पूर्ण अन्यथा अगर (vrf_अगरindex == -ENODEV) अणु
			NL_SET_ERR_MSG(extack,
				       "Table has no associated VRF device");
		पूर्ण अन्यथा अणु
			pr_debug("seg6local: SRv6 End.DT* creation error=%d\n",
				 vrf_अगरindex);
		पूर्ण

		वापस vrf_अगरindex;
	पूर्ण

	info->net = net;
	info->vrf_अगरindex = vrf_अगरindex;

	चयन (family) अणु
	हाल AF_INET:
		info->proto = htons(ETH_P_IP);
		info->hdrlen = माप(काष्ठा iphdr);
		अवरोध;
	हाल AF_INET6:
		info->proto = htons(ETH_P_IPV6);
		info->hdrlen = माप(काष्ठा ipv6hdr);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	info->family = family;
	info->mode = DT_VRF_MODE;

	वापस 0;
पूर्ण

/* The SRv6 End.DT4/DT6 behavior extracts the inner (IPv4/IPv6) packet and
 * routes the IPv4/IPv6 packet by looking at the configured routing table.
 *
 * In the SRv6 End.DT4/DT6 use हाल, we can receive traffic (IPv6+Segment
 * Routing Header packets) from several पूर्णांकerfaces and the outer IPv6
 * destination address (DA) is used क्रम retrieving the specअगरic instance of the
 * End.DT4/DT6 behavior that should process the packets.
 *
 * However, the inner IPv4/IPv6 packet is not really bound to any receiving
 * पूर्णांकerface and thus the End.DT4/DT6 sets the VRF (associated with the
 * corresponding routing table) as the *receiving* पूर्णांकerface.
 * In other words, the End.DT4/DT6 processes a packet as अगर it has been received
 * directly by the VRF (and not by one of its slave devices, अगर any).
 * In this way, the VRF पूर्णांकerface is used क्रम routing the IPv4/IPv6 packet in
 * according to the routing table configured by the End.DT4/DT6 instance.
 *
 * This design allows you to get some पूर्णांकeresting features like:
 *  1) the statistics on rx packets;
 *  2) the possibility to install a packet snअगरfer on the receiving पूर्णांकerface
 *     (the VRF one) क्रम looking at the incoming packets;
 *  3) the possibility to leverage the netfilter prerouting hook क्रम the inner
 *     IPv4 packet.
 *
 * This function वापसs:
 *  - the sk_buff* when the VRF rcv handler has processed the packet correctly;
 *  - शून्य when the skb is consumed by the VRF rcv handler;
 *  - a poपूर्णांकer which encodes a negative error number in हाल of error.
 *    Note that in this हाल, the function takes care of मुक्तing the skb.
 */
अटल काष्ठा sk_buff *end_dt_vrf_rcv(काष्ठा sk_buff *skb, u16 family,
				      काष्ठा net_device *dev)
अणु
	/* based on l3mdev_ip_rcv; we are only पूर्णांकerested in the master */
	अगर (unlikely(!netअगर_is_l3_master(dev) && !netअगर_has_l3_rx_handler(dev)))
		जाओ drop;

	अगर (unlikely(!dev->l3mdev_ops->l3mdev_l3_rcv))
		जाओ drop;

	/* the decap packet IPv4/IPv6 करोes not come with any mac header info.
	 * We must unset the mac header to allow the VRF device to rebuild it,
	 * just in हाल there is a snअगरfer attached on the device.
	 */
	skb_unset_mac_header(skb);

	skb = dev->l3mdev_ops->l3mdev_l3_rcv(dev, skb, family);
	अगर (!skb)
		/* the skb buffer was consumed by the handler */
		वापस शून्य;

	/* when a packet is received by a VRF or by one of its slaves, the
	 * master device reference is set पूर्णांकo the skb.
	 */
	अगर (unlikely(skb->dev != dev || skb->skb_iअगर != dev->अगरindex))
		जाओ drop;

	वापस skb;

drop:
	kमुक्त_skb(skb);
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल काष्ठा net_device *end_dt_get_vrf_rcu(काष्ठा sk_buff *skb,
					     काष्ठा seg6_end_dt_info *info)
अणु
	पूर्णांक vrf_अगरindex = info->vrf_अगरindex;
	काष्ठा net *net = info->net;

	अगर (unlikely(vrf_अगरindex < 0))
		जाओ error;

	अगर (unlikely(!net_eq(dev_net(skb->dev), net)))
		जाओ error;

	वापस dev_get_by_index_rcu(net, vrf_अगरindex);

error:
	वापस शून्य;
पूर्ण

अटल काष्ठा sk_buff *end_dt_vrf_core(काष्ठा sk_buff *skb,
				       काष्ठा seg6_local_lwt *slwt)
अणु
	काष्ठा seg6_end_dt_info *info = &slwt->dt_info;
	काष्ठा net_device *vrf;

	vrf = end_dt_get_vrf_rcu(skb, info);
	अगर (unlikely(!vrf))
		जाओ drop;

	skb->protocol = info->proto;

	skb_dst_drop(skb);

	skb_set_transport_header(skb, info->hdrlen);

	वापस end_dt_vrf_rcv(skb, info->family, vrf);

drop:
	kमुक्त_skb(skb);
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल पूर्णांक input_action_end_dt4(काष्ठा sk_buff *skb,
				काष्ठा seg6_local_lwt *slwt)
अणु
	काष्ठा iphdr *iph;
	पूर्णांक err;

	अगर (!decap_and_validate(skb, IPPROTO_IPIP))
		जाओ drop;

	अगर (!pskb_may_pull(skb, माप(काष्ठा iphdr)))
		जाओ drop;

	skb = end_dt_vrf_core(skb, slwt);
	अगर (!skb)
		/* packet has been processed and consumed by the VRF */
		वापस 0;

	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	iph = ip_hdr(skb);

	err = ip_route_input(skb, iph->daddr, iph->saddr, 0, skb->dev);
	अगर (unlikely(err))
		जाओ drop;

	वापस dst_input(skb);

drop:
	kमुक्त_skb(skb);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक seg6_end_dt4_build(काष्ठा seg6_local_lwt *slwt, स्थिर व्योम *cfg,
			      काष्ठा netlink_ext_ack *extack)
अणु
	वापस __seg6_end_dt_vrf_build(slwt, cfg, AF_INET, extack);
पूर्ण

अटल क्रमागत
seg6_end_dt_mode seg6_end_dt6_parse_mode(काष्ठा seg6_local_lwt *slwt)
अणु
	अचिन्हित दीर्घ parsed_optattrs = slwt->parsed_optattrs;
	bool legacy, vrभ_शेषe;

	legacy	= !!(parsed_optattrs & SEG6_F_ATTR(SEG6_LOCAL_TABLE));
	vrभ_शेषe	= !!(parsed_optattrs & SEG6_F_ATTR(SEG6_LOCAL_VRFTABLE));

	अगर (!(legacy ^ vrभ_शेषe))
		/* both are असलent or present: invalid DT6 mode */
		वापस DT_INVALID_MODE;

	वापस legacy ? DT_LEGACY_MODE : DT_VRF_MODE;
पूर्ण

अटल क्रमागत seg6_end_dt_mode seg6_end_dt6_get_mode(काष्ठा seg6_local_lwt *slwt)
अणु
	काष्ठा seg6_end_dt_info *info = &slwt->dt_info;

	वापस info->mode;
पूर्ण

अटल पूर्णांक seg6_end_dt6_build(काष्ठा seg6_local_lwt *slwt, स्थिर व्योम *cfg,
			      काष्ठा netlink_ext_ack *extack)
अणु
	क्रमागत seg6_end_dt_mode mode = seg6_end_dt6_parse_mode(slwt);
	काष्ठा seg6_end_dt_info *info = &slwt->dt_info;

	चयन (mode) अणु
	हाल DT_LEGACY_MODE:
		info->mode = DT_LEGACY_MODE;
		वापस 0;
	हाल DT_VRF_MODE:
		वापस __seg6_end_dt_vrf_build(slwt, cfg, AF_INET6, extack);
	शेष:
		NL_SET_ERR_MSG(extack, "table or vrftable must be specified");
		वापस -EINVAL;
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक input_action_end_dt6(काष्ठा sk_buff *skb,
				काष्ठा seg6_local_lwt *slwt)
अणु
	अगर (!decap_and_validate(skb, IPPROTO_IPV6))
		जाओ drop;

	अगर (!pskb_may_pull(skb, माप(काष्ठा ipv6hdr)))
		जाओ drop;

#अगर_घोषित CONFIG_NET_L3_MASTER_DEV
	अगर (seg6_end_dt6_get_mode(slwt) == DT_LEGACY_MODE)
		जाओ legacy_mode;

	/* DT6_VRF_MODE */
	skb = end_dt_vrf_core(skb, slwt);
	अगर (!skb)
		/* packet has been processed and consumed by the VRF */
		वापस 0;

	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	/* note: this समय we करो not need to specअगरy the table because the VRF
	 * takes care of selecting the correct table.
	 */
	seg6_lookup_any_nexthop(skb, शून्य, 0, true);

	वापस dst_input(skb);

legacy_mode:
#पूर्ण_अगर
	skb_set_transport_header(skb, माप(काष्ठा ipv6hdr));

	seg6_lookup_any_nexthop(skb, शून्य, slwt->table, true);

	वापस dst_input(skb);

drop:
	kमुक्त_skb(skb);
	वापस -EINVAL;
पूर्ण

/* push an SRH on top of the current one */
अटल पूर्णांक input_action_end_b6(काष्ठा sk_buff *skb, काष्ठा seg6_local_lwt *slwt)
अणु
	काष्ठा ipv6_sr_hdr *srh;
	पूर्णांक err = -EINVAL;

	srh = get_and_validate_srh(skb);
	अगर (!srh)
		जाओ drop;

	err = seg6_करो_srh_अंतरभूत(skb, slwt->srh);
	अगर (err)
		जाओ drop;

	ipv6_hdr(skb)->payload_len = htons(skb->len - माप(काष्ठा ipv6hdr));
	skb_set_transport_header(skb, माप(काष्ठा ipv6hdr));

	seg6_lookup_nexthop(skb, शून्य, 0);

	वापस dst_input(skb);

drop:
	kमुक्त_skb(skb);
	वापस err;
पूर्ण

/* encapsulate within an outer IPv6 header and a specअगरied SRH */
अटल पूर्णांक input_action_end_b6_encap(काष्ठा sk_buff *skb,
				     काष्ठा seg6_local_lwt *slwt)
अणु
	काष्ठा ipv6_sr_hdr *srh;
	पूर्णांक err = -EINVAL;

	srh = get_and_validate_srh(skb);
	अगर (!srh)
		जाओ drop;

	advance_nextseg(srh, &ipv6_hdr(skb)->daddr);

	skb_reset_inner_headers(skb);
	skb->encapsulation = 1;

	err = seg6_करो_srh_encap(skb, slwt->srh, IPPROTO_IPV6);
	अगर (err)
		जाओ drop;

	ipv6_hdr(skb)->payload_len = htons(skb->len - माप(काष्ठा ipv6hdr));
	skb_set_transport_header(skb, माप(काष्ठा ipv6hdr));

	seg6_lookup_nexthop(skb, शून्य, 0);

	वापस dst_input(skb);

drop:
	kमुक्त_skb(skb);
	वापस err;
पूर्ण

DEFINE_PER_CPU(काष्ठा seg6_bpf_srh_state, seg6_bpf_srh_states);

bool seg6_bpf_has_valid_srh(काष्ठा sk_buff *skb)
अणु
	काष्ठा seg6_bpf_srh_state *srh_state =
		this_cpu_ptr(&seg6_bpf_srh_states);
	काष्ठा ipv6_sr_hdr *srh = srh_state->srh;

	अगर (unlikely(srh == शून्य))
		वापस false;

	अगर (unlikely(!srh_state->valid)) अणु
		अगर ((srh_state->hdrlen & 7) != 0)
			वापस false;

		srh->hdrlen = (u8)(srh_state->hdrlen >> 3);
		अगर (!seg6_validate_srh(srh, (srh->hdrlen + 1) << 3, true))
			वापस false;

		srh_state->valid = true;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक input_action_end_bpf(काष्ठा sk_buff *skb,
				काष्ठा seg6_local_lwt *slwt)
अणु
	काष्ठा seg6_bpf_srh_state *srh_state =
		this_cpu_ptr(&seg6_bpf_srh_states);
	काष्ठा ipv6_sr_hdr *srh;
	पूर्णांक ret;

	srh = get_and_validate_srh(skb);
	अगर (!srh) अणु
		kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण
	advance_nextseg(srh, &ipv6_hdr(skb)->daddr);

	/* preempt_disable is needed to protect the per-CPU buffer srh_state,
	 * which is also accessed by the bpf_lwt_seg6_* helpers
	 */
	preempt_disable();
	srh_state->srh = srh;
	srh_state->hdrlen = srh->hdrlen << 3;
	srh_state->valid = true;

	rcu_पढ़ो_lock();
	bpf_compute_data_poपूर्णांकers(skb);
	ret = bpf_prog_run_save_cb(slwt->bpf.prog, skb);
	rcu_पढ़ो_unlock();

	चयन (ret) अणु
	हाल BPF_OK:
	हाल BPF_REसूचीECT:
		अवरोध;
	हाल BPF_DROP:
		जाओ drop;
	शेष:
		pr_warn_once("bpf-seg6local: Illegal return value %u\n", ret);
		जाओ drop;
	पूर्ण

	अगर (srh_state->srh && !seg6_bpf_has_valid_srh(skb))
		जाओ drop;

	preempt_enable();
	अगर (ret != BPF_REसूचीECT)
		seg6_lookup_nexthop(skb, शून्य, 0);

	वापस dst_input(skb);

drop:
	preempt_enable();
	kमुक्त_skb(skb);
	वापस -EINVAL;
पूर्ण

अटल काष्ठा seg6_action_desc seg6_action_table[] = अणु
	अणु
		.action		= SEG6_LOCAL_ACTION_END,
		.attrs		= 0,
		.optattrs	= SEG6_F_LOCAL_COUNTERS,
		.input		= input_action_end,
	पूर्ण,
	अणु
		.action		= SEG6_LOCAL_ACTION_END_X,
		.attrs		= SEG6_F_ATTR(SEG6_LOCAL_NH6),
		.optattrs	= SEG6_F_LOCAL_COUNTERS,
		.input		= input_action_end_x,
	पूर्ण,
	अणु
		.action		= SEG6_LOCAL_ACTION_END_T,
		.attrs		= SEG6_F_ATTR(SEG6_LOCAL_TABLE),
		.optattrs	= SEG6_F_LOCAL_COUNTERS,
		.input		= input_action_end_t,
	पूर्ण,
	अणु
		.action		= SEG6_LOCAL_ACTION_END_DX2,
		.attrs		= SEG6_F_ATTR(SEG6_LOCAL_OIF),
		.optattrs	= SEG6_F_LOCAL_COUNTERS,
		.input		= input_action_end_dx2,
	पूर्ण,
	अणु
		.action		= SEG6_LOCAL_ACTION_END_DX6,
		.attrs		= SEG6_F_ATTR(SEG6_LOCAL_NH6),
		.optattrs	= SEG6_F_LOCAL_COUNTERS,
		.input		= input_action_end_dx6,
	पूर्ण,
	अणु
		.action		= SEG6_LOCAL_ACTION_END_DX4,
		.attrs		= SEG6_F_ATTR(SEG6_LOCAL_NH4),
		.optattrs	= SEG6_F_LOCAL_COUNTERS,
		.input		= input_action_end_dx4,
	पूर्ण,
	अणु
		.action		= SEG6_LOCAL_ACTION_END_DT4,
		.attrs		= SEG6_F_ATTR(SEG6_LOCAL_VRFTABLE),
		.optattrs	= SEG6_F_LOCAL_COUNTERS,
#अगर_घोषित CONFIG_NET_L3_MASTER_DEV
		.input		= input_action_end_dt4,
		.slwt_ops	= अणु
					.build_state = seg6_end_dt4_build,
				  पूर्ण,
#पूर्ण_अगर
	पूर्ण,
	अणु
		.action		= SEG6_LOCAL_ACTION_END_DT6,
#अगर_घोषित CONFIG_NET_L3_MASTER_DEV
		.attrs		= 0,
		.optattrs	= SEG6_F_LOCAL_COUNTERS		|
				  SEG6_F_ATTR(SEG6_LOCAL_TABLE) |
				  SEG6_F_ATTR(SEG6_LOCAL_VRFTABLE),
		.slwt_ops	= अणु
					.build_state = seg6_end_dt6_build,
				  पूर्ण,
#अन्यथा
		.attrs		= SEG6_F_ATTR(SEG6_LOCAL_TABLE),
		.optattrs	= SEG6_F_LOCAL_COUNTERS,
#पूर्ण_अगर
		.input		= input_action_end_dt6,
	पूर्ण,
	अणु
		.action		= SEG6_LOCAL_ACTION_END_B6,
		.attrs		= SEG6_F_ATTR(SEG6_LOCAL_SRH),
		.optattrs	= SEG6_F_LOCAL_COUNTERS,
		.input		= input_action_end_b6,
	पूर्ण,
	अणु
		.action		= SEG6_LOCAL_ACTION_END_B6_ENCAP,
		.attrs		= SEG6_F_ATTR(SEG6_LOCAL_SRH),
		.optattrs	= SEG6_F_LOCAL_COUNTERS,
		.input		= input_action_end_b6_encap,
		.अटल_headroom	= माप(काष्ठा ipv6hdr),
	पूर्ण,
	अणु
		.action		= SEG6_LOCAL_ACTION_END_BPF,
		.attrs		= SEG6_F_ATTR(SEG6_LOCAL_BPF),
		.optattrs	= SEG6_F_LOCAL_COUNTERS,
		.input		= input_action_end_bpf,
	पूर्ण,

पूर्ण;

अटल काष्ठा seg6_action_desc *__get_action_desc(पूर्णांक action)
अणु
	काष्ठा seg6_action_desc *desc;
	पूर्णांक i, count;

	count = ARRAY_SIZE(seg6_action_table);
	क्रम (i = 0; i < count; i++) अणु
		desc = &seg6_action_table[i];
		अगर (desc->action == action)
			वापस desc;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल bool seg6_lwtunnel_counters_enabled(काष्ठा seg6_local_lwt *slwt)
अणु
	वापस slwt->parsed_optattrs & SEG6_F_LOCAL_COUNTERS;
पूर्ण

अटल व्योम seg6_local_update_counters(काष्ठा seg6_local_lwt *slwt,
				       अचिन्हित पूर्णांक len, पूर्णांक err)
अणु
	काष्ठा pcpu_seg6_local_counters *pcounters;

	pcounters = this_cpu_ptr(slwt->pcpu_counters);
	u64_stats_update_begin(&pcounters->syncp);

	अगर (likely(!err)) अणु
		u64_stats_inc(&pcounters->packets);
		u64_stats_add(&pcounters->bytes, len);
	पूर्ण अन्यथा अणु
		u64_stats_inc(&pcounters->errors);
	पूर्ण

	u64_stats_update_end(&pcounters->syncp);
पूर्ण

अटल पूर्णांक seg6_local_input(काष्ठा sk_buff *skb)
अणु
	काष्ठा dst_entry *orig_dst = skb_dst(skb);
	काष्ठा seg6_action_desc *desc;
	काष्ठा seg6_local_lwt *slwt;
	अचिन्हित पूर्णांक len = skb->len;
	पूर्णांक rc;

	अगर (skb->protocol != htons(ETH_P_IPV6)) अणु
		kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	slwt = seg6_local_lwtunnel(orig_dst->lwtstate);
	desc = slwt->desc;

	rc = desc->input(skb, slwt);

	अगर (!seg6_lwtunnel_counters_enabled(slwt))
		वापस rc;

	seg6_local_update_counters(slwt, len, rc);

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा nla_policy seg6_local_policy[SEG6_LOCAL_MAX + 1] = अणु
	[SEG6_LOCAL_ACTION]	= अणु .type = NLA_U32 पूर्ण,
	[SEG6_LOCAL_SRH]	= अणु .type = NLA_BINARY पूर्ण,
	[SEG6_LOCAL_TABLE]	= अणु .type = NLA_U32 पूर्ण,
	[SEG6_LOCAL_VRFTABLE]	= अणु .type = NLA_U32 पूर्ण,
	[SEG6_LOCAL_NH4]	= अणु .type = NLA_BINARY,
				    .len = माप(काष्ठा in_addr) पूर्ण,
	[SEG6_LOCAL_NH6]	= अणु .type = NLA_BINARY,
				    .len = माप(काष्ठा in6_addr) पूर्ण,
	[SEG6_LOCAL_IIF]	= अणु .type = NLA_U32 पूर्ण,
	[SEG6_LOCAL_OIF]	= अणु .type = NLA_U32 पूर्ण,
	[SEG6_LOCAL_BPF]	= अणु .type = NLA_NESTED पूर्ण,
	[SEG6_LOCAL_COUNTERS]	= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल पूर्णांक parse_nla_srh(काष्ठा nlattr **attrs, काष्ठा seg6_local_lwt *slwt)
अणु
	काष्ठा ipv6_sr_hdr *srh;
	पूर्णांक len;

	srh = nla_data(attrs[SEG6_LOCAL_SRH]);
	len = nla_len(attrs[SEG6_LOCAL_SRH]);

	/* SRH must contain at least one segment */
	अगर (len < माप(*srh) + माप(काष्ठा in6_addr))
		वापस -EINVAL;

	अगर (!seg6_validate_srh(srh, len, false))
		वापस -EINVAL;

	slwt->srh = kmemdup(srh, len, GFP_KERNEL);
	अगर (!slwt->srh)
		वापस -ENOMEM;

	slwt->headroom += len;

	वापस 0;
पूर्ण

अटल पूर्णांक put_nla_srh(काष्ठा sk_buff *skb, काष्ठा seg6_local_lwt *slwt)
अणु
	काष्ठा ipv6_sr_hdr *srh;
	काष्ठा nlattr *nla;
	पूर्णांक len;

	srh = slwt->srh;
	len = (srh->hdrlen + 1) << 3;

	nla = nla_reserve(skb, SEG6_LOCAL_SRH, len);
	अगर (!nla)
		वापस -EMSGSIZE;

	स_नकल(nla_data(nla), srh, len);

	वापस 0;
पूर्ण

अटल पूर्णांक cmp_nla_srh(काष्ठा seg6_local_lwt *a, काष्ठा seg6_local_lwt *b)
अणु
	पूर्णांक len = (a->srh->hdrlen + 1) << 3;

	अगर (len != ((b->srh->hdrlen + 1) << 3))
		वापस 1;

	वापस स_भेद(a->srh, b->srh, len);
पूर्ण

अटल व्योम destroy_attr_srh(काष्ठा seg6_local_lwt *slwt)
अणु
	kमुक्त(slwt->srh);
पूर्ण

अटल पूर्णांक parse_nla_table(काष्ठा nlattr **attrs, काष्ठा seg6_local_lwt *slwt)
अणु
	slwt->table = nla_get_u32(attrs[SEG6_LOCAL_TABLE]);

	वापस 0;
पूर्ण

अटल पूर्णांक put_nla_table(काष्ठा sk_buff *skb, काष्ठा seg6_local_lwt *slwt)
अणु
	अगर (nla_put_u32(skb, SEG6_LOCAL_TABLE, slwt->table))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक cmp_nla_table(काष्ठा seg6_local_lwt *a, काष्ठा seg6_local_lwt *b)
अणु
	अगर (a->table != b->table)
		वापस 1;

	वापस 0;
पूर्ण

अटल काष्ठा
seg6_end_dt_info *seg6_possible_end_dt_info(काष्ठा seg6_local_lwt *slwt)
अणु
#अगर_घोषित CONFIG_NET_L3_MASTER_DEV
	वापस &slwt->dt_info;
#अन्यथा
	वापस ERR_PTR(-EOPNOTSUPP);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक parse_nla_vrftable(काष्ठा nlattr **attrs,
			      काष्ठा seg6_local_lwt *slwt)
अणु
	काष्ठा seg6_end_dt_info *info = seg6_possible_end_dt_info(slwt);

	अगर (IS_ERR(info))
		वापस PTR_ERR(info);

	info->vrf_table = nla_get_u32(attrs[SEG6_LOCAL_VRFTABLE]);

	वापस 0;
पूर्ण

अटल पूर्णांक put_nla_vrftable(काष्ठा sk_buff *skb, काष्ठा seg6_local_lwt *slwt)
अणु
	काष्ठा seg6_end_dt_info *info = seg6_possible_end_dt_info(slwt);

	अगर (IS_ERR(info))
		वापस PTR_ERR(info);

	अगर (nla_put_u32(skb, SEG6_LOCAL_VRFTABLE, info->vrf_table))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक cmp_nla_vrftable(काष्ठा seg6_local_lwt *a, काष्ठा seg6_local_lwt *b)
अणु
	काष्ठा seg6_end_dt_info *info_a = seg6_possible_end_dt_info(a);
	काष्ठा seg6_end_dt_info *info_b = seg6_possible_end_dt_info(b);

	अगर (info_a->vrf_table != info_b->vrf_table)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक parse_nla_nh4(काष्ठा nlattr **attrs, काष्ठा seg6_local_lwt *slwt)
अणु
	स_नकल(&slwt->nh4, nla_data(attrs[SEG6_LOCAL_NH4]),
	       माप(काष्ठा in_addr));

	वापस 0;
पूर्ण

अटल पूर्णांक put_nla_nh4(काष्ठा sk_buff *skb, काष्ठा seg6_local_lwt *slwt)
अणु
	काष्ठा nlattr *nla;

	nla = nla_reserve(skb, SEG6_LOCAL_NH4, माप(काष्ठा in_addr));
	अगर (!nla)
		वापस -EMSGSIZE;

	स_नकल(nla_data(nla), &slwt->nh4, माप(काष्ठा in_addr));

	वापस 0;
पूर्ण

अटल पूर्णांक cmp_nla_nh4(काष्ठा seg6_local_lwt *a, काष्ठा seg6_local_lwt *b)
अणु
	वापस स_भेद(&a->nh4, &b->nh4, माप(काष्ठा in_addr));
पूर्ण

अटल पूर्णांक parse_nla_nh6(काष्ठा nlattr **attrs, काष्ठा seg6_local_lwt *slwt)
अणु
	स_नकल(&slwt->nh6, nla_data(attrs[SEG6_LOCAL_NH6]),
	       माप(काष्ठा in6_addr));

	वापस 0;
पूर्ण

अटल पूर्णांक put_nla_nh6(काष्ठा sk_buff *skb, काष्ठा seg6_local_lwt *slwt)
अणु
	काष्ठा nlattr *nla;

	nla = nla_reserve(skb, SEG6_LOCAL_NH6, माप(काष्ठा in6_addr));
	अगर (!nla)
		वापस -EMSGSIZE;

	स_नकल(nla_data(nla), &slwt->nh6, माप(काष्ठा in6_addr));

	वापस 0;
पूर्ण

अटल पूर्णांक cmp_nla_nh6(काष्ठा seg6_local_lwt *a, काष्ठा seg6_local_lwt *b)
अणु
	वापस स_भेद(&a->nh6, &b->nh6, माप(काष्ठा in6_addr));
पूर्ण

अटल पूर्णांक parse_nla_iअगर(काष्ठा nlattr **attrs, काष्ठा seg6_local_lwt *slwt)
अणु
	slwt->iअगर = nla_get_u32(attrs[SEG6_LOCAL_IIF]);

	वापस 0;
पूर्ण

अटल पूर्णांक put_nla_iअगर(काष्ठा sk_buff *skb, काष्ठा seg6_local_lwt *slwt)
अणु
	अगर (nla_put_u32(skb, SEG6_LOCAL_IIF, slwt->iअगर))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक cmp_nla_iअगर(काष्ठा seg6_local_lwt *a, काष्ठा seg6_local_lwt *b)
अणु
	अगर (a->iअगर != b->iअगर)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक parse_nla_oअगर(काष्ठा nlattr **attrs, काष्ठा seg6_local_lwt *slwt)
अणु
	slwt->oअगर = nla_get_u32(attrs[SEG6_LOCAL_OIF]);

	वापस 0;
पूर्ण

अटल पूर्णांक put_nla_oअगर(काष्ठा sk_buff *skb, काष्ठा seg6_local_lwt *slwt)
अणु
	अगर (nla_put_u32(skb, SEG6_LOCAL_OIF, slwt->oअगर))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक cmp_nla_oअगर(काष्ठा seg6_local_lwt *a, काष्ठा seg6_local_lwt *b)
अणु
	अगर (a->oअगर != b->oअगर)
		वापस 1;

	वापस 0;
पूर्ण

#घोषणा MAX_PROG_NAME 256
अटल स्थिर काष्ठा nla_policy bpf_prog_policy[SEG6_LOCAL_BPF_PROG_MAX + 1] = अणु
	[SEG6_LOCAL_BPF_PROG]	   = अणु .type = NLA_U32, पूर्ण,
	[SEG6_LOCAL_BPF_PROG_NAME] = अणु .type = NLA_NUL_STRING,
				       .len = MAX_PROG_NAME पूर्ण,
पूर्ण;

अटल पूर्णांक parse_nla_bpf(काष्ठा nlattr **attrs, काष्ठा seg6_local_lwt *slwt)
अणु
	काष्ठा nlattr *tb[SEG6_LOCAL_BPF_PROG_MAX + 1];
	काष्ठा bpf_prog *p;
	पूर्णांक ret;
	u32 fd;

	ret = nla_parse_nested_deprecated(tb, SEG6_LOCAL_BPF_PROG_MAX,
					  attrs[SEG6_LOCAL_BPF],
					  bpf_prog_policy, शून्य);
	अगर (ret < 0)
		वापस ret;

	अगर (!tb[SEG6_LOCAL_BPF_PROG] || !tb[SEG6_LOCAL_BPF_PROG_NAME])
		वापस -EINVAL;

	slwt->bpf.name = nla_memdup(tb[SEG6_LOCAL_BPF_PROG_NAME], GFP_KERNEL);
	अगर (!slwt->bpf.name)
		वापस -ENOMEM;

	fd = nla_get_u32(tb[SEG6_LOCAL_BPF_PROG]);
	p = bpf_prog_get_type(fd, BPF_PROG_TYPE_LWT_SEG6LOCAL);
	अगर (IS_ERR(p)) अणु
		kमुक्त(slwt->bpf.name);
		वापस PTR_ERR(p);
	पूर्ण

	slwt->bpf.prog = p;
	वापस 0;
पूर्ण

अटल पूर्णांक put_nla_bpf(काष्ठा sk_buff *skb, काष्ठा seg6_local_lwt *slwt)
अणु
	काष्ठा nlattr *nest;

	अगर (!slwt->bpf.prog)
		वापस 0;

	nest = nla_nest_start_noflag(skb, SEG6_LOCAL_BPF);
	अगर (!nest)
		वापस -EMSGSIZE;

	अगर (nla_put_u32(skb, SEG6_LOCAL_BPF_PROG, slwt->bpf.prog->aux->id))
		वापस -EMSGSIZE;

	अगर (slwt->bpf.name &&
	    nla_put_string(skb, SEG6_LOCAL_BPF_PROG_NAME, slwt->bpf.name))
		वापस -EMSGSIZE;

	वापस nla_nest_end(skb, nest);
पूर्ण

अटल पूर्णांक cmp_nla_bpf(काष्ठा seg6_local_lwt *a, काष्ठा seg6_local_lwt *b)
अणु
	अगर (!a->bpf.name && !b->bpf.name)
		वापस 0;

	अगर (!a->bpf.name || !b->bpf.name)
		वापस 1;

	वापस म_भेद(a->bpf.name, b->bpf.name);
पूर्ण

अटल व्योम destroy_attr_bpf(काष्ठा seg6_local_lwt *slwt)
अणु
	kमुक्त(slwt->bpf.name);
	अगर (slwt->bpf.prog)
		bpf_prog_put(slwt->bpf.prog);
पूर्ण

अटल स्थिर काष्ठा
nla_policy seg6_local_counters_policy[SEG6_LOCAL_CNT_MAX + 1] = अणु
	[SEG6_LOCAL_CNT_PACKETS]	= अणु .type = NLA_U64 पूर्ण,
	[SEG6_LOCAL_CNT_BYTES]		= अणु .type = NLA_U64 पूर्ण,
	[SEG6_LOCAL_CNT_ERRORS]		= अणु .type = NLA_U64 पूर्ण,
पूर्ण;

अटल पूर्णांक parse_nla_counters(काष्ठा nlattr **attrs,
			      काष्ठा seg6_local_lwt *slwt)
अणु
	काष्ठा pcpu_seg6_local_counters __percpu *pcounters;
	काष्ठा nlattr *tb[SEG6_LOCAL_CNT_MAX + 1];
	पूर्णांक ret;

	ret = nla_parse_nested_deprecated(tb, SEG6_LOCAL_CNT_MAX,
					  attrs[SEG6_LOCAL_COUNTERS],
					  seg6_local_counters_policy, शून्य);
	अगर (ret < 0)
		वापस ret;

	/* basic support क्रम SRv6 Behavior counters requires at least:
	 * packets, bytes and errors.
	 */
	अगर (!tb[SEG6_LOCAL_CNT_PACKETS] || !tb[SEG6_LOCAL_CNT_BYTES] ||
	    !tb[SEG6_LOCAL_CNT_ERRORS])
		वापस -EINVAL;

	/* counters are always zero initialized */
	pcounters = seg6_local_alloc_pcpu_counters(GFP_KERNEL);
	अगर (!pcounters)
		वापस -ENOMEM;

	slwt->pcpu_counters = pcounters;

	वापस 0;
पूर्ण

अटल पूर्णांक seg6_local_fill_nla_counters(काष्ठा sk_buff *skb,
					काष्ठा seg6_local_counters *counters)
अणु
	अगर (nla_put_u64_64bit(skb, SEG6_LOCAL_CNT_PACKETS, counters->packets,
			      SEG6_LOCAL_CNT_PAD))
		वापस -EMSGSIZE;

	अगर (nla_put_u64_64bit(skb, SEG6_LOCAL_CNT_BYTES, counters->bytes,
			      SEG6_LOCAL_CNT_PAD))
		वापस -EMSGSIZE;

	अगर (nla_put_u64_64bit(skb, SEG6_LOCAL_CNT_ERRORS, counters->errors,
			      SEG6_LOCAL_CNT_PAD))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक put_nla_counters(काष्ठा sk_buff *skb, काष्ठा seg6_local_lwt *slwt)
अणु
	काष्ठा seg6_local_counters counters = अणु 0, 0, 0 पूर्ण;
	काष्ठा nlattr *nest;
	पूर्णांक rc, i;

	nest = nla_nest_start(skb, SEG6_LOCAL_COUNTERS);
	अगर (!nest)
		वापस -EMSGSIZE;

	क्रम_each_possible_cpu(i) अणु
		काष्ठा pcpu_seg6_local_counters *pcounters;
		u64 packets, bytes, errors;
		अचिन्हित पूर्णांक start;

		pcounters = per_cpu_ptr(slwt->pcpu_counters, i);
		करो अणु
			start = u64_stats_fetch_begin_irq(&pcounters->syncp);

			packets = u64_stats_पढ़ो(&pcounters->packets);
			bytes = u64_stats_पढ़ो(&pcounters->bytes);
			errors = u64_stats_पढ़ो(&pcounters->errors);

		पूर्ण जबतक (u64_stats_fetch_retry_irq(&pcounters->syncp, start));

		counters.packets += packets;
		counters.bytes += bytes;
		counters.errors += errors;
	पूर्ण

	rc = seg6_local_fill_nla_counters(skb, &counters);
	अगर (rc < 0) अणु
		nla_nest_cancel(skb, nest);
		वापस rc;
	पूर्ण

	वापस nla_nest_end(skb, nest);
पूर्ण

अटल पूर्णांक cmp_nla_counters(काष्ठा seg6_local_lwt *a, काष्ठा seg6_local_lwt *b)
अणु
	/* a and b are equal अगर both have pcpu_counters set or not */
	वापस (!!((अचिन्हित दीर्घ)a->pcpu_counters)) ^
		(!!((अचिन्हित दीर्घ)b->pcpu_counters));
पूर्ण

अटल व्योम destroy_attr_counters(काष्ठा seg6_local_lwt *slwt)
अणु
	मुक्त_percpu(slwt->pcpu_counters);
पूर्ण

काष्ठा seg6_action_param अणु
	पूर्णांक (*parse)(काष्ठा nlattr **attrs, काष्ठा seg6_local_lwt *slwt);
	पूर्णांक (*put)(काष्ठा sk_buff *skb, काष्ठा seg6_local_lwt *slwt);
	पूर्णांक (*cmp)(काष्ठा seg6_local_lwt *a, काष्ठा seg6_local_lwt *b);

	/* optional destroy() callback useful क्रम releasing resources which
	 * have been previously acquired in the corresponding parse()
	 * function.
	 */
	व्योम (*destroy)(काष्ठा seg6_local_lwt *slwt);
पूर्ण;

अटल काष्ठा seg6_action_param seg6_action_params[SEG6_LOCAL_MAX + 1] = अणु
	[SEG6_LOCAL_SRH]	= अणु .parse = parse_nla_srh,
				    .put = put_nla_srh,
				    .cmp = cmp_nla_srh,
				    .destroy = destroy_attr_srh पूर्ण,

	[SEG6_LOCAL_TABLE]	= अणु .parse = parse_nla_table,
				    .put = put_nla_table,
				    .cmp = cmp_nla_table पूर्ण,

	[SEG6_LOCAL_NH4]	= अणु .parse = parse_nla_nh4,
				    .put = put_nla_nh4,
				    .cmp = cmp_nla_nh4 पूर्ण,

	[SEG6_LOCAL_NH6]	= अणु .parse = parse_nla_nh6,
				    .put = put_nla_nh6,
				    .cmp = cmp_nla_nh6 पूर्ण,

	[SEG6_LOCAL_IIF]	= अणु .parse = parse_nla_iअगर,
				    .put = put_nla_iअगर,
				    .cmp = cmp_nla_iअगर पूर्ण,

	[SEG6_LOCAL_OIF]	= अणु .parse = parse_nla_oअगर,
				    .put = put_nla_oअगर,
				    .cmp = cmp_nla_oअगर पूर्ण,

	[SEG6_LOCAL_BPF]	= अणु .parse = parse_nla_bpf,
				    .put = put_nla_bpf,
				    .cmp = cmp_nla_bpf,
				    .destroy = destroy_attr_bpf पूर्ण,

	[SEG6_LOCAL_VRFTABLE]	= अणु .parse = parse_nla_vrftable,
				    .put = put_nla_vrftable,
				    .cmp = cmp_nla_vrftable पूर्ण,

	[SEG6_LOCAL_COUNTERS]	= अणु .parse = parse_nla_counters,
				    .put = put_nla_counters,
				    .cmp = cmp_nla_counters,
				    .destroy = destroy_attr_counters पूर्ण,
पूर्ण;

/* call the destroy() callback (अगर available) क्रम each set attribute in
 * @parsed_attrs, starting from the first attribute up to the @max_parsed
 * (excluded) attribute.
 */
अटल व्योम __destroy_attrs(अचिन्हित दीर्घ parsed_attrs, पूर्णांक max_parsed,
			    काष्ठा seg6_local_lwt *slwt)
अणु
	काष्ठा seg6_action_param *param;
	पूर्णांक i;

	/* Every required seg6local attribute is identअगरied by an ID which is
	 * encoded as a flag (i.e: 1 << ID) in the 'attrs' biपंचांगask;
	 *
	 * We scan the 'parsed_attrs' biपंचांगask, starting from the first attribute
	 * up to the @max_parsed (excluded) attribute.
	 * For each set attribute, we retrieve the corresponding destroy()
	 * callback. If the callback is not available, then we skip to the next
	 * attribute; otherwise, we call the destroy() callback.
	 */
	क्रम (i = 0; i < max_parsed; ++i) अणु
		अगर (!(parsed_attrs & SEG6_F_ATTR(i)))
			जारी;

		param = &seg6_action_params[i];

		अगर (param->destroy)
			param->destroy(slwt);
	पूर्ण
पूर्ण

/* release all the resources that may have been acquired during parsing
 * operations.
 */
अटल व्योम destroy_attrs(काष्ठा seg6_local_lwt *slwt)
अणु
	अचिन्हित दीर्घ attrs = slwt->desc->attrs | slwt->parsed_optattrs;

	__destroy_attrs(attrs, SEG6_LOCAL_MAX + 1, slwt);
पूर्ण

अटल पूर्णांक parse_nla_optional_attrs(काष्ठा nlattr **attrs,
				    काष्ठा seg6_local_lwt *slwt)
अणु
	काष्ठा seg6_action_desc *desc = slwt->desc;
	अचिन्हित दीर्घ parsed_optattrs = 0;
	काष्ठा seg6_action_param *param;
	पूर्णांक err, i;

	क्रम (i = 0; i < SEG6_LOCAL_MAX + 1; ++i) अणु
		अगर (!(desc->optattrs & SEG6_F_ATTR(i)) || !attrs[i])
			जारी;

		/* once here, the i-th attribute is provided by the
		 * userspace AND it is identअगरied optional as well.
		 */
		param = &seg6_action_params[i];

		err = param->parse(attrs, slwt);
		अगर (err < 0)
			जाओ parse_optattrs_err;

		/* current attribute has been correctly parsed */
		parsed_optattrs |= SEG6_F_ATTR(i);
	पूर्ण

	/* store in the tunnel state all the optional attributed successfully
	 * parsed.
	 */
	slwt->parsed_optattrs = parsed_optattrs;

	वापस 0;

parse_optattrs_err:
	__destroy_attrs(parsed_optattrs, i, slwt);

	वापस err;
पूर्ण

/* call the custom स्थिरructor of the behavior during its initialization phase
 * and after that all its attributes have been parsed successfully.
 */
अटल पूर्णांक
seg6_local_lwtunnel_build_state(काष्ठा seg6_local_lwt *slwt, स्थिर व्योम *cfg,
				काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा seg6_action_desc *desc = slwt->desc;
	काष्ठा seg6_local_lwtunnel_ops *ops;

	ops = &desc->slwt_ops;
	अगर (!ops->build_state)
		वापस 0;

	वापस ops->build_state(slwt, cfg, extack);
पूर्ण

/* call the custom deकाष्ठाor of the behavior which is invoked beक्रमe the
 * tunnel is going to be destroyed.
 */
अटल व्योम seg6_local_lwtunnel_destroy_state(काष्ठा seg6_local_lwt *slwt)
अणु
	काष्ठा seg6_action_desc *desc = slwt->desc;
	काष्ठा seg6_local_lwtunnel_ops *ops;

	ops = &desc->slwt_ops;
	अगर (!ops->destroy_state)
		वापस;

	ops->destroy_state(slwt);
पूर्ण

अटल पूर्णांक parse_nla_action(काष्ठा nlattr **attrs, काष्ठा seg6_local_lwt *slwt)
अणु
	काष्ठा seg6_action_param *param;
	काष्ठा seg6_action_desc *desc;
	अचिन्हित दीर्घ invalid_attrs;
	पूर्णांक i, err;

	desc = __get_action_desc(slwt->action);
	अगर (!desc)
		वापस -EINVAL;

	अगर (!desc->input)
		वापस -EOPNOTSUPP;

	slwt->desc = desc;
	slwt->headroom += desc->अटल_headroom;

	/* Forcing the desc->optattrs *set* and the desc->attrs *set* to be
	 * disjoined, this allow us to release acquired resources by optional
	 * attributes and by required attributes independently from each other
	 * without any पूर्णांकerference.
	 * In other terms, we are sure that we करो not release some the acquired
	 * resources twice.
	 *
	 * Note that अगर an attribute is configured both as required and as
	 * optional, it means that the user has messed something up in the
	 * seg6_action_table. Thereक्रमe, this check is required क्रम SRv6
	 * behaviors to work properly.
	 */
	invalid_attrs = desc->attrs & desc->optattrs;
	अगर (invalid_attrs) अणु
		WARN_ONCE(1,
			  "An attribute cannot be both required AND optional");
		वापस -EINVAL;
	पूर्ण

	/* parse the required attributes */
	क्रम (i = 0; i < SEG6_LOCAL_MAX + 1; i++) अणु
		अगर (desc->attrs & SEG6_F_ATTR(i)) अणु
			अगर (!attrs[i])
				वापस -EINVAL;

			param = &seg6_action_params[i];

			err = param->parse(attrs, slwt);
			अगर (err < 0)
				जाओ parse_attrs_err;
		पूर्ण
	पूर्ण

	/* parse the optional attributes, अगर any */
	err = parse_nla_optional_attrs(attrs, slwt);
	अगर (err < 0)
		जाओ parse_attrs_err;

	वापस 0;

parse_attrs_err:
	/* release any resource that may have been acquired during the i-1
	 * parse() operations.
	 */
	__destroy_attrs(desc->attrs, i, slwt);

	वापस err;
पूर्ण

अटल पूर्णांक seg6_local_build_state(काष्ठा net *net, काष्ठा nlattr *nla,
				  अचिन्हित पूर्णांक family, स्थिर व्योम *cfg,
				  काष्ठा lwtunnel_state **ts,
				  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[SEG6_LOCAL_MAX + 1];
	काष्ठा lwtunnel_state *newts;
	काष्ठा seg6_local_lwt *slwt;
	पूर्णांक err;

	अगर (family != AF_INET6)
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(tb, SEG6_LOCAL_MAX, nla,
					  seg6_local_policy, extack);

	अगर (err < 0)
		वापस err;

	अगर (!tb[SEG6_LOCAL_ACTION])
		वापस -EINVAL;

	newts = lwtunnel_state_alloc(माप(*slwt));
	अगर (!newts)
		वापस -ENOMEM;

	slwt = seg6_local_lwtunnel(newts);
	slwt->action = nla_get_u32(tb[SEG6_LOCAL_ACTION]);

	err = parse_nla_action(tb, slwt);
	अगर (err < 0)
		जाओ out_मुक्त;

	err = seg6_local_lwtunnel_build_state(slwt, cfg, extack);
	अगर (err < 0)
		जाओ out_destroy_attrs;

	newts->type = LWTUNNEL_ENCAP_SEG6_LOCAL;
	newts->flags = LWTUNNEL_STATE_INPUT_REसूचीECT;
	newts->headroom = slwt->headroom;

	*ts = newts;

	वापस 0;

out_destroy_attrs:
	destroy_attrs(slwt);
out_मुक्त:
	kमुक्त(newts);
	वापस err;
पूर्ण

अटल व्योम seg6_local_destroy_state(काष्ठा lwtunnel_state *lwt)
अणु
	काष्ठा seg6_local_lwt *slwt = seg6_local_lwtunnel(lwt);

	seg6_local_lwtunnel_destroy_state(slwt);

	destroy_attrs(slwt);

	वापस;
पूर्ण

अटल पूर्णांक seg6_local_fill_encap(काष्ठा sk_buff *skb,
				 काष्ठा lwtunnel_state *lwt)
अणु
	काष्ठा seg6_local_lwt *slwt = seg6_local_lwtunnel(lwt);
	काष्ठा seg6_action_param *param;
	अचिन्हित दीर्घ attrs;
	पूर्णांक i, err;

	अगर (nla_put_u32(skb, SEG6_LOCAL_ACTION, slwt->action))
		वापस -EMSGSIZE;

	attrs = slwt->desc->attrs | slwt->parsed_optattrs;

	क्रम (i = 0; i < SEG6_LOCAL_MAX + 1; i++) अणु
		अगर (attrs & SEG6_F_ATTR(i)) अणु
			param = &seg6_action_params[i];
			err = param->put(skb, slwt);
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक seg6_local_get_encap_size(काष्ठा lwtunnel_state *lwt)
अणु
	काष्ठा seg6_local_lwt *slwt = seg6_local_lwtunnel(lwt);
	अचिन्हित दीर्घ attrs;
	पूर्णांक nlsize;

	nlsize = nla_total_size(4); /* action */

	attrs = slwt->desc->attrs | slwt->parsed_optattrs;

	अगर (attrs & SEG6_F_ATTR(SEG6_LOCAL_SRH))
		nlsize += nla_total_size((slwt->srh->hdrlen + 1) << 3);

	अगर (attrs & SEG6_F_ATTR(SEG6_LOCAL_TABLE))
		nlsize += nla_total_size(4);

	अगर (attrs & SEG6_F_ATTR(SEG6_LOCAL_NH4))
		nlsize += nla_total_size(4);

	अगर (attrs & SEG6_F_ATTR(SEG6_LOCAL_NH6))
		nlsize += nla_total_size(16);

	अगर (attrs & SEG6_F_ATTR(SEG6_LOCAL_IIF))
		nlsize += nla_total_size(4);

	अगर (attrs & SEG6_F_ATTR(SEG6_LOCAL_OIF))
		nlsize += nla_total_size(4);

	अगर (attrs & SEG6_F_ATTR(SEG6_LOCAL_BPF))
		nlsize += nla_total_size(माप(काष्ठा nlattr)) +
		       nla_total_size(MAX_PROG_NAME) +
		       nla_total_size(4);

	अगर (attrs & SEG6_F_ATTR(SEG6_LOCAL_VRFTABLE))
		nlsize += nla_total_size(4);

	अगर (attrs & SEG6_F_LOCAL_COUNTERS)
		nlsize += nla_total_size(0) + /* nest SEG6_LOCAL_COUNTERS */
			  /* SEG6_LOCAL_CNT_PACKETS */
			  nla_total_size_64bit(माप(__u64)) +
			  /* SEG6_LOCAL_CNT_BYTES */
			  nla_total_size_64bit(माप(__u64)) +
			  /* SEG6_LOCAL_CNT_ERRORS */
			  nla_total_size_64bit(माप(__u64));

	वापस nlsize;
पूर्ण

अटल पूर्णांक seg6_local_cmp_encap(काष्ठा lwtunnel_state *a,
				काष्ठा lwtunnel_state *b)
अणु
	काष्ठा seg6_local_lwt *slwt_a, *slwt_b;
	काष्ठा seg6_action_param *param;
	अचिन्हित दीर्घ attrs_a, attrs_b;
	पूर्णांक i;

	slwt_a = seg6_local_lwtunnel(a);
	slwt_b = seg6_local_lwtunnel(b);

	अगर (slwt_a->action != slwt_b->action)
		वापस 1;

	attrs_a = slwt_a->desc->attrs | slwt_a->parsed_optattrs;
	attrs_b = slwt_b->desc->attrs | slwt_b->parsed_optattrs;

	अगर (attrs_a != attrs_b)
		वापस 1;

	क्रम (i = 0; i < SEG6_LOCAL_MAX + 1; i++) अणु
		अगर (attrs_a & SEG6_F_ATTR(i)) अणु
			param = &seg6_action_params[i];
			अगर (param->cmp(slwt_a, slwt_b))
				वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा lwtunnel_encap_ops seg6_local_ops = अणु
	.build_state	= seg6_local_build_state,
	.destroy_state	= seg6_local_destroy_state,
	.input		= seg6_local_input,
	.fill_encap	= seg6_local_fill_encap,
	.get_encap_size	= seg6_local_get_encap_size,
	.cmp_encap	= seg6_local_cmp_encap,
	.owner		= THIS_MODULE,
पूर्ण;

पूर्णांक __init seg6_local_init(व्योम)
अणु
	/* If the max total number of defined attributes is reached, then your
	 * kernel build stops here.
	 *
	 * This check is required to aव्योम arithmetic overflows when processing
	 * behavior attributes and the maximum number of defined attributes
	 * exceeds the allowed value.
	 */
	BUILD_BUG_ON(SEG6_LOCAL_MAX + 1 > BITS_PER_TYPE(अचिन्हित दीर्घ));

	वापस lwtunnel_encap_add_ops(&seg6_local_ops,
				      LWTUNNEL_ENCAP_SEG6_LOCAL);
पूर्ण

व्योम seg6_local_निकास(व्योम)
अणु
	lwtunnel_encap_del_ops(&seg6_local_ops, LWTUNNEL_ENCAP_SEG6_LOCAL);
पूर्ण
