<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
#समावेश <net/netlink.h>
#समावेश <net/sch_generic.h>
#समावेश <net/dst.h>
#समावेश <net/ip.h>
#समावेश <net/ip6_fib.h>

काष्ठा sch_frag_data अणु
	अचिन्हित दीर्घ dst;
	काष्ठा qdisc_skb_cb cb;
	__be16 inner_protocol;
	u16 vlan_tci;
	__be16 vlan_proto;
	अचिन्हित पूर्णांक l2_len;
	u8 l2_data[VLAN_ETH_HLEN];
	पूर्णांक (*xmit)(काष्ठा sk_buff *skb);
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा sch_frag_data, sch_frag_data_storage);

अटल पूर्णांक sch_frag_xmit(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा sch_frag_data *data = this_cpu_ptr(&sch_frag_data_storage);

	अगर (skb_cow_head(skb, data->l2_len) < 0) अणु
		kमुक्त_skb(skb);
		वापस -ENOMEM;
	पूर्ण

	__skb_dst_copy(skb, data->dst);
	*qdisc_skb_cb(skb) = data->cb;
	skb->inner_protocol = data->inner_protocol;
	अगर (data->vlan_tci & VLAN_CFI_MASK)
		__vlan_hwaccel_put_tag(skb, data->vlan_proto,
				       data->vlan_tci & ~VLAN_CFI_MASK);
	अन्यथा
		__vlan_hwaccel_clear_tag(skb);

	/* Reस्थिरruct the MAC header.  */
	skb_push(skb, data->l2_len);
	स_नकल(skb->data, &data->l2_data, data->l2_len);
	skb_postpush_rcsum(skb, skb->data, data->l2_len);
	skb_reset_mac_header(skb);

	वापस data->xmit(skb);
पूर्ण

अटल व्योम sch_frag_prepare_frag(काष्ठा sk_buff *skb,
				  पूर्णांक (*xmit)(काष्ठा sk_buff *skb))
अणु
	अचिन्हित पूर्णांक hlen = skb_network_offset(skb);
	काष्ठा sch_frag_data *data;

	data = this_cpu_ptr(&sch_frag_data_storage);
	data->dst = skb->_skb_refdst;
	data->cb = *qdisc_skb_cb(skb);
	data->xmit = xmit;
	data->inner_protocol = skb->inner_protocol;
	अगर (skb_vlan_tag_present(skb))
		data->vlan_tci = skb_vlan_tag_get(skb) | VLAN_CFI_MASK;
	अन्यथा
		data->vlan_tci = 0;
	data->vlan_proto = skb->vlan_proto;
	data->l2_len = hlen;
	स_नकल(&data->l2_data, skb->data, hlen);

	स_रखो(IPCB(skb), 0, माप(काष्ठा inet_skb_parm));
	skb_pull(skb, hlen);
पूर्ण

अटल अचिन्हित पूर्णांक
sch_frag_dst_get_mtu(स्थिर काष्ठा dst_entry *dst)
अणु
	वापस dst->dev->mtu;
पूर्ण

अटल काष्ठा dst_ops sch_frag_dst_ops = अणु
	.family = AF_UNSPEC,
	.mtu = sch_frag_dst_get_mtu,
पूर्ण;

अटल पूर्णांक sch_fragment(काष्ठा net *net, काष्ठा sk_buff *skb,
			u16 mru, पूर्णांक (*xmit)(काष्ठा sk_buff *skb))
अणु
	पूर्णांक ret = -1;

	अगर (skb_network_offset(skb) > VLAN_ETH_HLEN) अणु
		net_warn_ratelimited("L2 header too long to fragment\n");
		जाओ err;
	पूर्ण

	अगर (skb_protocol(skb, true) == htons(ETH_P_IP)) अणु
		काष्ठा rtable sch_frag_rt = अणु 0 पूर्ण;
		अचिन्हित दीर्घ orig_dst;

		sch_frag_prepare_frag(skb, xmit);
		dst_init(&sch_frag_rt.dst, &sch_frag_dst_ops, शून्य, 1,
			 DST_OBSOLETE_NONE, DST_NOCOUNT);
		sch_frag_rt.dst.dev = skb->dev;

		orig_dst = skb->_skb_refdst;
		skb_dst_set_noref(skb, &sch_frag_rt.dst);
		IPCB(skb)->frag_max_size = mru;

		ret = ip_करो_fragment(net, skb->sk, skb, sch_frag_xmit);
		refdst_drop(orig_dst);
	पूर्ण अन्यथा अगर (skb_protocol(skb, true) == htons(ETH_P_IPV6)) अणु
		अचिन्हित दीर्घ orig_dst;
		काष्ठा rt6_info sch_frag_rt;

		sch_frag_prepare_frag(skb, xmit);
		स_रखो(&sch_frag_rt, 0, माप(sch_frag_rt));
		dst_init(&sch_frag_rt.dst, &sch_frag_dst_ops, शून्य, 1,
			 DST_OBSOLETE_NONE, DST_NOCOUNT);
		sch_frag_rt.dst.dev = skb->dev;

		orig_dst = skb->_skb_refdst;
		skb_dst_set_noref(skb, &sch_frag_rt.dst);
		IP6CB(skb)->frag_max_size = mru;

		ret = ipv6_stub->ipv6_fragment(net, skb->sk, skb,
					       sch_frag_xmit);
		refdst_drop(orig_dst);
	पूर्ण अन्यथा अणु
		net_warn_ratelimited("Fail frag %s: eth=%x, MRU=%d, MTU=%d\n",
				     netdev_name(skb->dev),
				     ntohs(skb_protocol(skb, true)), mru,
				     skb->dev->mtu);
		जाओ err;
	पूर्ण

	वापस ret;
err:
	kमुक्त_skb(skb);
	वापस ret;
पूर्ण

पूर्णांक sch_frag_xmit_hook(काष्ठा sk_buff *skb, पूर्णांक (*xmit)(काष्ठा sk_buff *skb))
अणु
	u16 mru = qdisc_skb_cb(skb)->mru;
	पूर्णांक err;

	अगर (mru && skb->len > mru + skb->dev->hard_header_len)
		err = sch_fragment(dev_net(skb->dev), skb, mru, xmit);
	अन्यथा
		err = xmit(skb);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(sch_frag_xmit_hook);
