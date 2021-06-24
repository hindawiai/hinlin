<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/types.h>
#समावेश <linux/ip.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश <linux/netfilter_bridge.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/icmp.h>
#समावेश <linux/sysctl.h>
#समावेश <net/route.h>
#समावेश <net/ip.h>

#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_core.h>
#समावेश <net/netfilter/nf_conntrack_helper.h>
#समावेश <net/netfilter/nf_conntrack_bridge.h>

#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables.h>

#समावेश "../br_private.h"

/* Best efक्रमt variant of ip_करो_fragment which preserves geometry, unless skbuff
 * has been linearized or cloned.
 */
अटल पूर्णांक nf_br_ip_fragment(काष्ठा net *net, काष्ठा sock *sk,
			     काष्ठा sk_buff *skb,
			     काष्ठा nf_bridge_frag_data *data,
			     पूर्णांक (*output)(काष्ठा net *, काष्ठा sock *sk,
					   स्थिर काष्ठा nf_bridge_frag_data *data,
					   काष्ठा sk_buff *))
अणु
	पूर्णांक frag_max_size = BR_INPUT_SKB_CB(skb)->frag_max_size;
	अचिन्हित पूर्णांक hlen, ll_rs, mtu;
	kसमय_प्रकार tstamp = skb->tstamp;
	काष्ठा ip_frag_state state;
	काष्ठा iphdr *iph;
	पूर्णांक err;

	/* क्रम offloaded checksums cleanup checksum beक्रमe fragmentation */
	अगर (skb->ip_summed == CHECKSUM_PARTIAL &&
	    (err = skb_checksum_help(skb)))
		जाओ blackhole;

	iph = ip_hdr(skb);

	/*
	 *	Setup starting values
	 */

	hlen = iph->ihl * 4;
	frag_max_size -= hlen;
	ll_rs = LL_RESERVED_SPACE(skb->dev);
	mtu = skb->dev->mtu;

	अगर (skb_has_frag_list(skb)) अणु
		अचिन्हित पूर्णांक first_len = skb_pagelen(skb);
		काष्ठा ip_fraglist_iter iter;
		काष्ठा sk_buff *frag;

		अगर (first_len - hlen > mtu ||
		    skb_headroom(skb) < ll_rs)
			जाओ blackhole;

		अगर (skb_cloned(skb))
			जाओ slow_path;

		skb_walk_frags(skb, frag) अणु
			अगर (frag->len > mtu ||
			    skb_headroom(frag) < hlen + ll_rs)
				जाओ blackhole;

			अगर (skb_shared(frag))
				जाओ slow_path;
		पूर्ण

		ip_fraglist_init(skb, iph, hlen, &iter);

		क्रम (;;) अणु
			अगर (iter.frag)
				ip_fraglist_prepare(skb, &iter);

			skb->tstamp = tstamp;
			err = output(net, sk, data, skb);
			अगर (err || !iter.frag)
				अवरोध;

			skb = ip_fraglist_next(&iter);
		पूर्ण
		वापस err;
	पूर्ण
slow_path:
	/* This is a linearized skbuff, the original geometry is lost क्रम us.
	 * This may also be a clone skbuff, we could preserve the geometry क्रम
	 * the copies but probably not worth the efक्रमt.
	 */
	ip_frag_init(skb, hlen, ll_rs, frag_max_size, false, &state);

	जबतक (state.left > 0) अणु
		काष्ठा sk_buff *skb2;

		skb2 = ip_frag_next(skb, &state);
		अगर (IS_ERR(skb2)) अणु
			err = PTR_ERR(skb2);
			जाओ blackhole;
		पूर्ण

		skb2->tstamp = tstamp;
		err = output(net, sk, data, skb2);
		अगर (err)
			जाओ blackhole;
	पूर्ण
	consume_skb(skb);
	वापस err;

blackhole:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

/* ip_defrag() expects IPCB() in place. */
अटल व्योम br_skb_cb_save(काष्ठा sk_buff *skb, काष्ठा br_input_skb_cb *cb,
			   माप_प्रकार inet_skb_parm_size)
अणु
	स_नकल(cb, skb->cb, माप(*cb));
	स_रखो(skb->cb, 0, inet_skb_parm_size);
पूर्ण

अटल व्योम br_skb_cb_restore(काष्ठा sk_buff *skb,
			      स्थिर काष्ठा br_input_skb_cb *cb,
			      u16 fragsz)
अणु
	स_नकल(skb->cb, cb, माप(*cb));
	BR_INPUT_SKB_CB(skb)->frag_max_size = fragsz;
पूर्ण

अटल अचिन्हित पूर्णांक nf_ct_br_defrag4(काष्ठा sk_buff *skb,
				     स्थिर काष्ठा nf_hook_state *state)
अणु
	u16 zone_id = NF_CT_DEFAULT_ZONE_ID;
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा br_input_skb_cb cb;
	स्थिर काष्ठा nf_conn *ct;
	पूर्णांक err;

	अगर (!ip_is_fragment(ip_hdr(skb)))
		वापस NF_ACCEPT;

	ct = nf_ct_get(skb, &ctinfo);
	अगर (ct)
		zone_id = nf_ct_zone_id(nf_ct_zone(ct), CTINFO2सूची(ctinfo));

	br_skb_cb_save(skb, &cb, माप(काष्ठा inet_skb_parm));
	local_bh_disable();
	err = ip_defrag(state->net, skb,
			IP_DEFRAG_CONNTRACK_BRIDGE_IN + zone_id);
	local_bh_enable();
	अगर (!err) अणु
		br_skb_cb_restore(skb, &cb, IPCB(skb)->frag_max_size);
		skb->ignore_df = 1;
		वापस NF_ACCEPT;
	पूर्ण

	वापस NF_STOLEN;
पूर्ण

अटल अचिन्हित पूर्णांक nf_ct_br_defrag6(काष्ठा sk_buff *skb,
				     स्थिर काष्ठा nf_hook_state *state)
अणु
#अगर IS_ENABLED(CONFIG_NF_DEFRAG_IPV6)
	u16 zone_id = NF_CT_DEFAULT_ZONE_ID;
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा br_input_skb_cb cb;
	स्थिर काष्ठा nf_conn *ct;
	पूर्णांक err;

	ct = nf_ct_get(skb, &ctinfo);
	अगर (ct)
		zone_id = nf_ct_zone_id(nf_ct_zone(ct), CTINFO2सूची(ctinfo));

	br_skb_cb_save(skb, &cb, माप(काष्ठा inet6_skb_parm));

	err = nf_ct_frag6_gather(state->net, skb,
				 IP_DEFRAG_CONNTRACK_BRIDGE_IN + zone_id);
	/* queued */
	अगर (err == -EINPROGRESS)
		वापस NF_STOLEN;

	br_skb_cb_restore(skb, &cb, IP6CB(skb)->frag_max_size);
	वापस err == 0 ? NF_ACCEPT : NF_DROP;
#अन्यथा
	वापस NF_ACCEPT;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक nf_ct_br_ip_check(स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा iphdr *iph;
	पूर्णांक nhoff, len;

	nhoff = skb_network_offset(skb);
	iph = ip_hdr(skb);
	अगर (iph->ihl < 5 ||
	    iph->version != 4)
		वापस -1;

	len = ntohs(iph->tot_len);
	अगर (skb->len < nhoff + len ||
	    len < (iph->ihl * 4))
                वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक nf_ct_br_ipv6_check(स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा ipv6hdr *hdr;
	पूर्णांक nhoff, len;

	nhoff = skb_network_offset(skb);
	hdr = ipv6_hdr(skb);
	अगर (hdr->version != 6)
		वापस -1;

	len = ntohs(hdr->payload_len) + माप(काष्ठा ipv6hdr) + nhoff;
	अगर (skb->len < len)
		वापस -1;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक nf_ct_bridge_pre(व्योम *priv, काष्ठा sk_buff *skb,
				     स्थिर काष्ठा nf_hook_state *state)
अणु
	काष्ठा nf_hook_state bridge_state = *state;
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct;
	u32 len;
	पूर्णांक ret;

	ct = nf_ct_get(skb, &ctinfo);
	अगर ((ct && !nf_ct_is_ढाँचा(ct)) ||
	    ctinfo == IP_CT_UNTRACKED)
		वापस NF_ACCEPT;

	चयन (skb->protocol) अणु
	हाल htons(ETH_P_IP):
		अगर (!pskb_may_pull(skb, माप(काष्ठा iphdr)))
			वापस NF_ACCEPT;

		len = ntohs(ip_hdr(skb)->tot_len);
		अगर (pskb_trim_rcsum(skb, len))
			वापस NF_ACCEPT;

		अगर (nf_ct_br_ip_check(skb))
			वापस NF_ACCEPT;

		bridge_state.pf = NFPROTO_IPV4;
		ret = nf_ct_br_defrag4(skb, &bridge_state);
		अवरोध;
	हाल htons(ETH_P_IPV6):
		अगर (!pskb_may_pull(skb, माप(काष्ठा ipv6hdr)))
			वापस NF_ACCEPT;

		len = माप(काष्ठा ipv6hdr) + ntohs(ipv6_hdr(skb)->payload_len);
		अगर (pskb_trim_rcsum(skb, len))
			वापस NF_ACCEPT;

		अगर (nf_ct_br_ipv6_check(skb))
			वापस NF_ACCEPT;

		bridge_state.pf = NFPROTO_IPV6;
		ret = nf_ct_br_defrag6(skb, &bridge_state);
		अवरोध;
	शेष:
		nf_ct_set(skb, शून्य, IP_CT_UNTRACKED);
		वापस NF_ACCEPT;
	पूर्ण

	अगर (ret != NF_ACCEPT)
		वापस ret;

	वापस nf_conntrack_in(skb, &bridge_state);
पूर्ण

अटल व्योम nf_ct_bridge_frag_save(काष्ठा sk_buff *skb,
				   काष्ठा nf_bridge_frag_data *data)
अणु
	अगर (skb_vlan_tag_present(skb)) अणु
		data->vlan_present = true;
		data->vlan_tci = skb->vlan_tci;
		data->vlan_proto = skb->vlan_proto;
	पूर्ण अन्यथा अणु
		data->vlan_present = false;
	पूर्ण
	skb_copy_from_linear_data_offset(skb, -ETH_HLEN, data->mac, ETH_HLEN);
पूर्ण

अटल अचिन्हित पूर्णांक
nf_ct_bridge_refrag(काष्ठा sk_buff *skb, स्थिर काष्ठा nf_hook_state *state,
		    पूर्णांक (*output)(काष्ठा net *, काष्ठा sock *sk,
				  स्थिर काष्ठा nf_bridge_frag_data *data,
				  काष्ठा sk_buff *))
अणु
	काष्ठा nf_bridge_frag_data data;

	अगर (!BR_INPUT_SKB_CB(skb)->frag_max_size)
		वापस NF_ACCEPT;

	nf_ct_bridge_frag_save(skb, &data);
	चयन (skb->protocol) अणु
	हाल htons(ETH_P_IP):
		nf_br_ip_fragment(state->net, state->sk, skb, &data, output);
		अवरोध;
	हाल htons(ETH_P_IPV6):
		nf_br_ip6_fragment(state->net, state->sk, skb, &data, output);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		वापस NF_DROP;
	पूर्ण

	वापस NF_STOLEN;
पूर्ण

/* Actually only slow path refragmentation needs this. */
अटल पूर्णांक nf_ct_bridge_frag_restore(काष्ठा sk_buff *skb,
				     स्थिर काष्ठा nf_bridge_frag_data *data)
अणु
	पूर्णांक err;

	err = skb_cow_head(skb, ETH_HLEN);
	अगर (err) अणु
		kमुक्त_skb(skb);
		वापस -ENOMEM;
	पूर्ण
	अगर (data->vlan_present)
		__vlan_hwaccel_put_tag(skb, data->vlan_proto, data->vlan_tci);
	अन्यथा अगर (skb_vlan_tag_present(skb))
		__vlan_hwaccel_clear_tag(skb);

	skb_copy_to_linear_data_offset(skb, -ETH_HLEN, data->mac, ETH_HLEN);
	skb_reset_mac_header(skb);

	वापस 0;
पूर्ण

अटल पूर्णांक nf_ct_bridge_refrag_post(काष्ठा net *net, काष्ठा sock *sk,
				    स्थिर काष्ठा nf_bridge_frag_data *data,
				    काष्ठा sk_buff *skb)
अणु
	पूर्णांक err;

	err = nf_ct_bridge_frag_restore(skb, data);
	अगर (err < 0)
		वापस err;

	वापस br_dev_queue_push_xmit(net, sk, skb);
पूर्ण

अटल अचिन्हित पूर्णांक nf_ct_bridge_confirm(काष्ठा sk_buff *skb)
अणु
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct;
	पूर्णांक protoff;

	ct = nf_ct_get(skb, &ctinfo);
	अगर (!ct || ctinfo == IP_CT_RELATED_REPLY)
		वापस nf_conntrack_confirm(skb);

	चयन (skb->protocol) अणु
	हाल htons(ETH_P_IP):
		protoff = skb_network_offset(skb) + ip_hdrlen(skb);
		अवरोध;
	हाल htons(ETH_P_IPV6): अणु
		 अचिन्हित अक्षर pnum = ipv6_hdr(skb)->nexthdr;
		__be16 frag_off;

		protoff = ipv6_skip_exthdr(skb, माप(काष्ठा ipv6hdr), &pnum,
					   &frag_off);
		अगर (protoff < 0 || (frag_off & htons(~0x7)) != 0)
			वापस nf_conntrack_confirm(skb);
		पूर्ण
		अवरोध;
	शेष:
		वापस NF_ACCEPT;
	पूर्ण
	वापस nf_confirm(skb, protoff, ct, ctinfo);
पूर्ण

अटल अचिन्हित पूर्णांक nf_ct_bridge_post(व्योम *priv, काष्ठा sk_buff *skb,
				      स्थिर काष्ठा nf_hook_state *state)
अणु
	पूर्णांक ret;

	ret = nf_ct_bridge_confirm(skb);
	अगर (ret != NF_ACCEPT)
		वापस ret;

	वापस nf_ct_bridge_refrag(skb, state, nf_ct_bridge_refrag_post);
पूर्ण

अटल काष्ठा nf_hook_ops nf_ct_bridge_hook_ops[] __पढ़ो_mostly = अणु
	अणु
		.hook		= nf_ct_bridge_pre,
		.pf		= NFPROTO_BRIDGE,
		.hooknum	= NF_BR_PRE_ROUTING,
		.priority	= NF_IP_PRI_CONNTRACK,
	पूर्ण,
	अणु
		.hook		= nf_ct_bridge_post,
		.pf		= NFPROTO_BRIDGE,
		.hooknum	= NF_BR_POST_ROUTING,
		.priority	= NF_IP_PRI_CONNTRACK_CONFIRM,
	पूर्ण,
पूर्ण;

अटल काष्ठा nf_ct_bridge_info bridge_info = अणु
	.ops		= nf_ct_bridge_hook_ops,
	.ops_size	= ARRAY_SIZE(nf_ct_bridge_hook_ops),
	.me		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init nf_conntrack_l3proto_bridge_init(व्योम)
अणु
	nf_ct_bridge_रेजिस्टर(&bridge_info);

	वापस 0;
पूर्ण

अटल व्योम __निकास nf_conntrack_l3proto_bridge_fini(व्योम)
अणु
	nf_ct_bridge_unरेजिस्टर(&bridge_info);
पूर्ण

module_init(nf_conntrack_l3proto_bridge_init);
module_निकास(nf_conntrack_l3proto_bridge_fini);

MODULE_ALIAS("nf_conntrack-" __stringअगरy(AF_BRIDGE));
MODULE_LICENSE("GPL");
