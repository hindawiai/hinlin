<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Handle firewalling
 *	Linux ethernet bridge
 *
 *	Authors:
 *	Lennert Buytenhek		<buytenh@gnu.org>
 *	Bart De Schuymer		<bdschuym@panकरोra.be>
 *
 *	Lennert dedicates this file to Kerstin Wurdinger.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/ip.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/अगर_pppox.h>
#समावेश <linux/ppp_defs.h>
#समावेश <linux/netfilter_bridge.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश <linux/netfilter_arp.h>
#समावेश <linux/in_route.h>
#समावेश <linux/inetdevice.h>

#समावेश <net/ip.h>
#समावेश <net/ipv6.h>
#समावेश <net/addrconf.h>
#समावेश <net/route.h>
#समावेश <net/netfilter/br_netfilter.h>

#समावेश <linux/uaccess.h>
#समावेश "br_private.h"
#अगर_घोषित CONFIG_SYSCTL
#समावेश <linux/sysctl.h>
#पूर्ण_अगर

/* We only check the length. A bridge shouldn't करो any hop-by-hop stuff
 * anyway
 */
अटल पूर्णांक br_nf_check_hbh_len(काष्ठा sk_buff *skb)
अणु
	अचिन्हित अक्षर *raw = (u8 *)(ipv6_hdr(skb) + 1);
	u32 pkt_len;
	स्थिर अचिन्हित अक्षर *nh = skb_network_header(skb);
	पूर्णांक off = raw - nh;
	पूर्णांक len = (raw[1] + 1) << 3;

	अगर ((raw + len) - skb->data > skb_headlen(skb))
		जाओ bad;

	off += 2;
	len -= 2;

	जबतक (len > 0) अणु
		पूर्णांक optlen = nh[off + 1] + 2;

		चयन (nh[off]) अणु
		हाल IPV6_TLV_PAD1:
			optlen = 1;
			अवरोध;

		हाल IPV6_TLV_PADN:
			अवरोध;

		हाल IPV6_TLV_JUMBO:
			अगर (nh[off + 1] != 4 || (off & 3) != 2)
				जाओ bad;
			pkt_len = ntohl(*(__be32 *)(nh + off + 2));
			अगर (pkt_len <= IPV6_MAXPLEN ||
			    ipv6_hdr(skb)->payload_len)
				जाओ bad;
			अगर (pkt_len > skb->len - माप(काष्ठा ipv6hdr))
				जाओ bad;
			अगर (pskb_trim_rcsum(skb,
					    pkt_len + माप(काष्ठा ipv6hdr)))
				जाओ bad;
			nh = skb_network_header(skb);
			अवरोध;
		शेष:
			अगर (optlen > len)
				जाओ bad;
			अवरोध;
		पूर्ण
		off += optlen;
		len -= optlen;
	पूर्ण
	अगर (len == 0)
		वापस 0;
bad:
	वापस -1;
पूर्ण

पूर्णांक br_validate_ipv6(काष्ठा net *net, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा ipv6hdr *hdr;
	काष्ठा inet6_dev *idev = __in6_dev_get(skb->dev);
	u32 pkt_len;
	u8 ip6h_len = माप(काष्ठा ipv6hdr);

	अगर (!pskb_may_pull(skb, ip6h_len))
		जाओ inhdr_error;

	अगर (skb->len < ip6h_len)
		जाओ drop;

	hdr = ipv6_hdr(skb);

	अगर (hdr->version != 6)
		जाओ inhdr_error;

	pkt_len = ntohs(hdr->payload_len);

	अगर (pkt_len || hdr->nexthdr != NEXTHDR_HOP) अणु
		अगर (pkt_len + ip6h_len > skb->len) अणु
			__IP6_INC_STATS(net, idev,
					IPSTATS_MIB_INTRUNCATEDPKTS);
			जाओ drop;
		पूर्ण
		अगर (pskb_trim_rcsum(skb, pkt_len + ip6h_len)) अणु
			__IP6_INC_STATS(net, idev,
					IPSTATS_MIB_INDISCARDS);
			जाओ drop;
		पूर्ण
		hdr = ipv6_hdr(skb);
	पूर्ण
	अगर (hdr->nexthdr == NEXTHDR_HOP && br_nf_check_hbh_len(skb))
		जाओ drop;

	स_रखो(IP6CB(skb), 0, माप(काष्ठा inet6_skb_parm));
	/* No IP options in IPv6 header; however it should be
	 * checked अगर some next headers need special treaपंचांगent
	 */
	वापस 0;

inhdr_error:
	__IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDRERRORS);
drop:
	वापस -1;
पूर्ण

अटल अंतरभूत bool
br_nf_ipv6_daddr_was_changed(स्थिर काष्ठा sk_buff *skb,
			     स्थिर काष्ठा nf_bridge_info *nf_bridge)
अणु
	वापस स_भेद(&nf_bridge->ipv6_daddr, &ipv6_hdr(skb)->daddr,
		      माप(ipv6_hdr(skb)->daddr)) != 0;
पूर्ण

/* PF_BRIDGE/PRE_ROUTING: Unकरो the changes made क्रम ip6tables
 * PREROUTING and जारी the bridge PRE_ROUTING hook. See comment
 * क्रम br_nf_pre_routing_finish(), same logic is used here but
 * equivalent IPv6 function ip6_route_input() called indirectly.
 */
अटल पूर्णांक br_nf_pre_routing_finish_ipv6(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा nf_bridge_info *nf_bridge = nf_bridge_info_get(skb);
	काष्ठा rtable *rt;
	काष्ठा net_device *dev = skb->dev;
	स्थिर काष्ठा nf_ipv6_ops *v6ops = nf_get_ipv6_ops();

	nf_bridge->frag_max_size = IP6CB(skb)->frag_max_size;

	अगर (nf_bridge->pkt_otherhost) अणु
		skb->pkt_type = PACKET_OTHERHOST;
		nf_bridge->pkt_otherhost = false;
	पूर्ण
	nf_bridge->in_prerouting = 0;
	अगर (br_nf_ipv6_daddr_was_changed(skb, nf_bridge)) अणु
		skb_dst_drop(skb);
		v6ops->route_input(skb);

		अगर (skb_dst(skb)->error) अणु
			kमुक्त_skb(skb);
			वापस 0;
		पूर्ण

		अगर (skb_dst(skb)->dev == dev) अणु
			skb->dev = nf_bridge->physindev;
			nf_bridge_update_protocol(skb);
			nf_bridge_push_encap_header(skb);
			br_nf_hook_thresh(NF_BR_PRE_ROUTING,
					  net, sk, skb, skb->dev, शून्य,
					  br_nf_pre_routing_finish_bridge);
			वापस 0;
		पूर्ण
		ether_addr_copy(eth_hdr(skb)->h_dest, dev->dev_addr);
		skb->pkt_type = PACKET_HOST;
	पूर्ण अन्यथा अणु
		rt = bridge_parent_rtable(nf_bridge->physindev);
		अगर (!rt) अणु
			kमुक्त_skb(skb);
			वापस 0;
		पूर्ण
		skb_dst_set_noref(skb, &rt->dst);
	पूर्ण

	skb->dev = nf_bridge->physindev;
	nf_bridge_update_protocol(skb);
	nf_bridge_push_encap_header(skb);
	br_nf_hook_thresh(NF_BR_PRE_ROUTING, net, sk, skb,
			  skb->dev, शून्य, br_handle_frame_finish);

	वापस 0;
पूर्ण

/* Replicate the checks that IPv6 करोes on packet reception and pass the packet
 * to ip6tables.
 */
अचिन्हित पूर्णांक br_nf_pre_routing_ipv6(व्योम *priv,
				    काष्ठा sk_buff *skb,
				    स्थिर काष्ठा nf_hook_state *state)
अणु
	काष्ठा nf_bridge_info *nf_bridge;

	अगर (br_validate_ipv6(state->net, skb))
		वापस NF_DROP;

	nf_bridge = nf_bridge_alloc(skb);
	अगर (!nf_bridge)
		वापस NF_DROP;
	अगर (!setup_pre_routing(skb, state->net))
		वापस NF_DROP;

	nf_bridge = nf_bridge_info_get(skb);
	nf_bridge->ipv6_daddr = ipv6_hdr(skb)->daddr;

	skb->protocol = htons(ETH_P_IPV6);
	skb->transport_header = skb->network_header + माप(काष्ठा ipv6hdr);

	NF_HOOK(NFPROTO_IPV6, NF_INET_PRE_ROUTING, state->net, state->sk, skb,
		skb->dev, शून्य,
		br_nf_pre_routing_finish_ipv6);

	वापस NF_STOLEN;
पूर्ण
