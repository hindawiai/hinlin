<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * mpls tunnels	An implementation mpls tunnels using the light weight tunnel
 *		infraकाष्ठाure
 *
 * Authors:	Roopa Prabhu, <roopa@cumulusnetworks.com>
 */
#समावेश <linux/types.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/net.h>
#समावेश <linux/module.h>
#समावेश <linux/mpls.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <net/ip.h>
#समावेश <net/dst.h>
#समावेश <net/lwtunnel.h>
#समावेश <net/netevent.h>
#समावेश <net/netns/generic.h>
#समावेश <net/ip6_fib.h>
#समावेश <net/route.h>
#समावेश <net/mpls_iptunnel.h>
#समावेश <linux/mpls_iptunnel.h>
#समावेश "internal.h"

अटल स्थिर काष्ठा nla_policy mpls_iptunnel_policy[MPLS_IPTUNNEL_MAX + 1] = अणु
	[MPLS_IPTUNNEL_DST]	= अणु .len = माप(u32) पूर्ण,
	[MPLS_IPTUNNEL_TTL]	= अणु .type = NLA_U8 पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक mpls_encap_size(काष्ठा mpls_iptunnel_encap *en)
अणु
	/* The size of the layer 2.5 labels to be added क्रम this route */
	वापस en->labels * माप(काष्ठा mpls_shim_hdr);
पूर्ण

अटल पूर्णांक mpls_xmit(काष्ठा sk_buff *skb)
अणु
	काष्ठा mpls_iptunnel_encap *tun_encap_info;
	काष्ठा mpls_shim_hdr *hdr;
	काष्ठा net_device *out_dev;
	अचिन्हित पूर्णांक hh_len;
	अचिन्हित पूर्णांक new_header_size;
	अचिन्हित पूर्णांक mtu;
	काष्ठा dst_entry *dst = skb_dst(skb);
	काष्ठा rtable *rt = शून्य;
	काष्ठा rt6_info *rt6 = शून्य;
	काष्ठा mpls_dev *out_mdev;
	काष्ठा net *net;
	पूर्णांक err = 0;
	bool bos;
	पूर्णांक i;
	अचिन्हित पूर्णांक ttl;

	/* Find the output device */
	out_dev = dst->dev;
	net = dev_net(out_dev);

	skb_orphan(skb);

	अगर (!mpls_output_possible(out_dev) ||
	    !dst->lwtstate || skb_warn_अगर_lro(skb))
		जाओ drop;

	skb_क्रमward_csum(skb);

	tun_encap_info = mpls_lwtunnel_encap(dst->lwtstate);

	/* Obtain the ttl using the following set of rules.
	 *
	 * LWT ttl propagation setting:
	 *  - disabled => use शेष TTL value from LWT
	 *  - enabled  => use TTL value from IPv4/IPv6 header
	 *  - शेष  =>
	 *   Global ttl propagation setting:
	 *    - disabled => use शेष TTL value from global setting
	 *    - enabled => use TTL value from IPv4/IPv6 header
	 */
	अगर (dst->ops->family == AF_INET) अणु
		अगर (tun_encap_info->ttl_propagate == MPLS_TTL_PROP_DISABLED)
			ttl = tun_encap_info->शेष_ttl;
		अन्यथा अगर (tun_encap_info->ttl_propagate == MPLS_TTL_PROP_DEFAULT &&
			 !net->mpls.ip_ttl_propagate)
			ttl = net->mpls.शेष_ttl;
		अन्यथा
			ttl = ip_hdr(skb)->ttl;
		rt = (काष्ठा rtable *)dst;
	पूर्ण अन्यथा अगर (dst->ops->family == AF_INET6) अणु
		अगर (tun_encap_info->ttl_propagate == MPLS_TTL_PROP_DISABLED)
			ttl = tun_encap_info->शेष_ttl;
		अन्यथा अगर (tun_encap_info->ttl_propagate == MPLS_TTL_PROP_DEFAULT &&
			 !net->mpls.ip_ttl_propagate)
			ttl = net->mpls.शेष_ttl;
		अन्यथा
			ttl = ipv6_hdr(skb)->hop_limit;
		rt6 = (काष्ठा rt6_info *)dst;
	पूर्ण अन्यथा अणु
		जाओ drop;
	पूर्ण

	/* Verअगरy the destination can hold the packet */
	new_header_size = mpls_encap_size(tun_encap_info);
	mtu = mpls_dev_mtu(out_dev);
	अगर (mpls_pkt_too_big(skb, mtu - new_header_size))
		जाओ drop;

	hh_len = LL_RESERVED_SPACE(out_dev);
	अगर (!out_dev->header_ops)
		hh_len = 0;

	/* Ensure there is enough space क्रम the headers in the skb */
	अगर (skb_cow(skb, hh_len + new_header_size))
		जाओ drop;

	skb_set_inner_protocol(skb, skb->protocol);
	skb_reset_inner_network_header(skb);

	skb_push(skb, new_header_size);

	skb_reset_network_header(skb);

	skb->dev = out_dev;
	skb->protocol = htons(ETH_P_MPLS_UC);

	/* Push the new labels */
	hdr = mpls_hdr(skb);
	bos = true;
	क्रम (i = tun_encap_info->labels - 1; i >= 0; i--) अणु
		hdr[i] = mpls_entry_encode(tun_encap_info->label[i],
					   ttl, 0, bos);
		bos = false;
	पूर्ण

	mpls_stats_inc_outucastpkts(out_dev, skb);

	अगर (rt) अणु
		अगर (rt->rt_gw_family == AF_INET6)
			err = neigh_xmit(NEIGH_ND_TABLE, out_dev, &rt->rt_gw6,
					 skb);
		अन्यथा
			err = neigh_xmit(NEIGH_ARP_TABLE, out_dev, &rt->rt_gw4,
					 skb);
	पूर्ण अन्यथा अगर (rt6) अणु
		अगर (ipv6_addr_v4mapped(&rt6->rt6i_gateway)) अणु
			/* 6PE (RFC 4798) */
			err = neigh_xmit(NEIGH_ARP_TABLE, out_dev, &rt6->rt6i_gateway.s6_addr32[3],
					 skb);
		पूर्ण अन्यथा
			err = neigh_xmit(NEIGH_ND_TABLE, out_dev, &rt6->rt6i_gateway,
					 skb);
	पूर्ण
	अगर (err)
		net_dbg_ratelimited("%s: packet transmission failed: %d\n",
				    __func__, err);

	वापस LWTUNNEL_XMIT_DONE;

drop:
	out_mdev = out_dev ? mpls_dev_get(out_dev) : शून्य;
	अगर (out_mdev)
		MPLS_INC_STATS(out_mdev, tx_errors);
	kमुक्त_skb(skb);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mpls_build_state(काष्ठा net *net, काष्ठा nlattr *nla,
			    अचिन्हित पूर्णांक family, स्थिर व्योम *cfg,
			    काष्ठा lwtunnel_state **ts,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mpls_iptunnel_encap *tun_encap_info;
	काष्ठा nlattr *tb[MPLS_IPTUNNEL_MAX + 1];
	काष्ठा lwtunnel_state *newts;
	u8 n_labels;
	पूर्णांक ret;

	ret = nla_parse_nested_deprecated(tb, MPLS_IPTUNNEL_MAX, nla,
					  mpls_iptunnel_policy, extack);
	अगर (ret < 0)
		वापस ret;

	अगर (!tb[MPLS_IPTUNNEL_DST]) अणु
		NL_SET_ERR_MSG(extack, "MPLS_IPTUNNEL_DST attribute is missing");
		वापस -EINVAL;
	पूर्ण

	/* determine number of labels */
	अगर (nla_get_labels(tb[MPLS_IPTUNNEL_DST], MAX_NEW_LABELS,
			   &n_labels, शून्य, extack))
		वापस -EINVAL;

	newts = lwtunnel_state_alloc(काष्ठा_size(tun_encap_info, label,
						 n_labels));
	अगर (!newts)
		वापस -ENOMEM;

	tun_encap_info = mpls_lwtunnel_encap(newts);
	ret = nla_get_labels(tb[MPLS_IPTUNNEL_DST], n_labels,
			     &tun_encap_info->labels, tun_encap_info->label,
			     extack);
	अगर (ret)
		जाओ errout;

	tun_encap_info->ttl_propagate = MPLS_TTL_PROP_DEFAULT;

	अगर (tb[MPLS_IPTUNNEL_TTL]) अणु
		tun_encap_info->शेष_ttl = nla_get_u8(tb[MPLS_IPTUNNEL_TTL]);
		/* TTL 0 implies propagate from IP header */
		tun_encap_info->ttl_propagate = tun_encap_info->शेष_ttl ?
			MPLS_TTL_PROP_DISABLED :
			MPLS_TTL_PROP_ENABLED;
	पूर्ण

	newts->type = LWTUNNEL_ENCAP_MPLS;
	newts->flags |= LWTUNNEL_STATE_XMIT_REसूचीECT;
	newts->headroom = mpls_encap_size(tun_encap_info);

	*ts = newts;

	वापस 0;

errout:
	kमुक्त(newts);
	*ts = शून्य;

	वापस ret;
पूर्ण

अटल पूर्णांक mpls_fill_encap_info(काष्ठा sk_buff *skb,
				काष्ठा lwtunnel_state *lwtstate)
अणु
	काष्ठा mpls_iptunnel_encap *tun_encap_info;

	tun_encap_info = mpls_lwtunnel_encap(lwtstate);

	अगर (nla_put_labels(skb, MPLS_IPTUNNEL_DST, tun_encap_info->labels,
			   tun_encap_info->label))
		जाओ nla_put_failure;

	अगर (tun_encap_info->ttl_propagate != MPLS_TTL_PROP_DEFAULT &&
	    nla_put_u8(skb, MPLS_IPTUNNEL_TTL, tun_encap_info->शेष_ttl))
		जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक mpls_encap_nlsize(काष्ठा lwtunnel_state *lwtstate)
अणु
	काष्ठा mpls_iptunnel_encap *tun_encap_info;
	पूर्णांक nlsize;

	tun_encap_info = mpls_lwtunnel_encap(lwtstate);

	nlsize = nla_total_size(tun_encap_info->labels * 4);

	अगर (tun_encap_info->ttl_propagate != MPLS_TTL_PROP_DEFAULT)
		nlsize += nla_total_size(1);

	वापस nlsize;
पूर्ण

अटल पूर्णांक mpls_encap_cmp(काष्ठा lwtunnel_state *a, काष्ठा lwtunnel_state *b)
अणु
	काष्ठा mpls_iptunnel_encap *a_hdr = mpls_lwtunnel_encap(a);
	काष्ठा mpls_iptunnel_encap *b_hdr = mpls_lwtunnel_encap(b);
	पूर्णांक l;

	अगर (a_hdr->labels != b_hdr->labels ||
	    a_hdr->ttl_propagate != b_hdr->ttl_propagate ||
	    a_hdr->शेष_ttl != b_hdr->शेष_ttl)
		वापस 1;

	क्रम (l = 0; l < a_hdr->labels; l++)
		अगर (a_hdr->label[l] != b_hdr->label[l])
			वापस 1;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा lwtunnel_encap_ops mpls_iptun_ops = अणु
	.build_state = mpls_build_state,
	.xmit = mpls_xmit,
	.fill_encap = mpls_fill_encap_info,
	.get_encap_size = mpls_encap_nlsize,
	.cmp_encap = mpls_encap_cmp,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init mpls_iptunnel_init(व्योम)
अणु
	वापस lwtunnel_encap_add_ops(&mpls_iptun_ops, LWTUNNEL_ENCAP_MPLS);
पूर्ण
module_init(mpls_iptunnel_init);

अटल व्योम __निकास mpls_iptunnel_निकास(व्योम)
अणु
	lwtunnel_encap_del_ops(&mpls_iptun_ops, LWTUNNEL_ENCAP_MPLS);
पूर्ण
module_निकास(mpls_iptunnel_निकास);

MODULE_ALIAS_RTNL_LWT(MPLS);
MODULE_SOFTDEP("post: mpls_gso");
MODULE_DESCRIPTION("MultiProtocol Label Switching IP Tunnels");
MODULE_LICENSE("GPL v2");
