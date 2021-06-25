<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * (C) 2015 Red Hat GmbH
 * Author: Florian Westphal <fw@म_माप.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/अटल_key.h>
#समावेश <linux/hash.h>
#समावेश <linux/jhash.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/init.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nfnetlink.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables_core.h>
#समावेश <net/netfilter/nf_tables.h>

#घोषणा NFT_TRACETYPE_LL_HSIZE		20
#घोषणा NFT_TRACETYPE_NETWORK_HSIZE	40
#घोषणा NFT_TRACETYPE_TRANSPORT_HSIZE	20

DEFINE_STATIC_KEY_FALSE(nft_trace_enabled);
EXPORT_SYMBOL_GPL(nft_trace_enabled);

अटल पूर्णांक trace_fill_id(काष्ठा sk_buff *nlskb, काष्ठा sk_buff *skb)
अणु
	__be32 id;

	/* using skb address as ID results in a limited number of
	 * values (and quick reuse).
	 *
	 * So we attempt to use as many skb members that will not
	 * change जबतक skb is with netfilter.
	 */
	id = (__be32)jhash_2words(hash32_ptr(skb), skb_get_hash(skb),
				  skb->skb_iअगर);

	वापस nla_put_be32(nlskb, NFTA_TRACE_ID, id);
पूर्ण

अटल पूर्णांक trace_fill_header(काष्ठा sk_buff *nlskb, u16 type,
			     स्थिर काष्ठा sk_buff *skb,
			     पूर्णांक off, अचिन्हित पूर्णांक len)
अणु
	काष्ठा nlattr *nla;

	अगर (len == 0)
		वापस 0;

	nla = nla_reserve(nlskb, type, len);
	अगर (!nla || skb_copy_bits(skb, off, nla_data(nla), len))
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक nf_trace_fill_ll_header(काष्ठा sk_buff *nlskb,
				   स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा vlan_ethhdr veth;
	पूर्णांक off;

	BUILD_BUG_ON(माप(veth) > NFT_TRACETYPE_LL_HSIZE);

	off = skb_mac_header(skb) - skb->data;
	अगर (off != -ETH_HLEN)
		वापस -1;

	अगर (skb_copy_bits(skb, off, &veth, ETH_HLEN))
		वापस -1;

	veth.h_vlan_proto = skb->vlan_proto;
	veth.h_vlan_TCI = htons(skb_vlan_tag_get(skb));
	veth.h_vlan_encapsulated_proto = skb->protocol;

	वापस nla_put(nlskb, NFTA_TRACE_LL_HEADER, माप(veth), &veth);
पूर्ण

अटल पूर्णांक nf_trace_fill_dev_info(काष्ठा sk_buff *nlskb,
				  स्थिर काष्ठा net_device *indev,
				  स्थिर काष्ठा net_device *outdev)
अणु
	अगर (indev) अणु
		अगर (nla_put_be32(nlskb, NFTA_TRACE_IIF,
				 htonl(indev->अगरindex)))
			वापस -1;

		अगर (nla_put_be16(nlskb, NFTA_TRACE_IIFTYPE,
				 htons(indev->type)))
			वापस -1;
	पूर्ण

	अगर (outdev) अणु
		अगर (nla_put_be32(nlskb, NFTA_TRACE_OIF,
				 htonl(outdev->अगरindex)))
			वापस -1;

		अगर (nla_put_be16(nlskb, NFTA_TRACE_OIFTYPE,
				 htons(outdev->type)))
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nf_trace_fill_pkt_info(काष्ठा sk_buff *nlskb,
				  स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा sk_buff *skb = pkt->skb;
	पूर्णांक off = skb_network_offset(skb);
	अचिन्हित पूर्णांक len, nh_end;

	nh_end = pkt->tprot_set ? pkt->xt.thoff : skb->len;
	len = min_t(अचिन्हित पूर्णांक, nh_end - skb_network_offset(skb),
		    NFT_TRACETYPE_NETWORK_HSIZE);
	अगर (trace_fill_header(nlskb, NFTA_TRACE_NETWORK_HEADER, skb, off, len))
		वापस -1;

	अगर (pkt->tprot_set) अणु
		len = min_t(अचिन्हित पूर्णांक, skb->len - pkt->xt.thoff,
			    NFT_TRACETYPE_TRANSPORT_HSIZE);
		अगर (trace_fill_header(nlskb, NFTA_TRACE_TRANSPORT_HEADER, skb,
				      pkt->xt.thoff, len))
			वापस -1;
	पूर्ण

	अगर (!skb_mac_header_was_set(skb))
		वापस 0;

	अगर (skb_vlan_tag_get(skb))
		वापस nf_trace_fill_ll_header(nlskb, skb);

	off = skb_mac_header(skb) - skb->data;
	len = min_t(अचिन्हित पूर्णांक, -off, NFT_TRACETYPE_LL_HSIZE);
	वापस trace_fill_header(nlskb, NFTA_TRACE_LL_HEADER,
				 skb, off, len);
पूर्ण

अटल पूर्णांक nf_trace_fill_rule_info(काष्ठा sk_buff *nlskb,
				   स्थिर काष्ठा nft_traceinfo *info)
अणु
	अगर (!info->rule)
		वापस 0;

	/* a जारी verdict with ->type == RETURN means that this is
	 * an implicit वापस (end of chain reached).
	 *
	 * Since no rule matched, the ->rule poपूर्णांकer is invalid.
	 */
	अगर (info->type == NFT_TRACETYPE_RETURN &&
	    info->verdict->code == NFT_CONTINUE)
		वापस 0;

	वापस nla_put_be64(nlskb, NFTA_TRACE_RULE_HANDLE,
			    cpu_to_be64(info->rule->handle),
			    NFTA_TRACE_PAD);
पूर्ण

अटल bool nft_trace_have_verdict_chain(काष्ठा nft_traceinfo *info)
अणु
	चयन (info->type) अणु
	हाल NFT_TRACETYPE_RETURN:
	हाल NFT_TRACETYPE_RULE:
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	चयन (info->verdict->code) अणु
	हाल NFT_JUMP:
	हाल NFT_GOTO:
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

व्योम nft_trace_notअगरy(काष्ठा nft_traceinfo *info)
अणु
	स्थिर काष्ठा nft_pktinfo *pkt = info->pkt;
	काष्ठा nlmsghdr *nlh;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक size;
	u16 event;

	अगर (!nfnetlink_has_listeners(nft_net(pkt), NFNLGRP_NFTRACE))
		वापस;

	size = nlmsg_total_size(माप(काष्ठा nfgenmsg)) +
		nla_total_size(म_माप(info->chain->table->name)) +
		nla_total_size(म_माप(info->chain->name)) +
		nla_total_size_64bit(माप(__be64)) +	/* rule handle */
		nla_total_size(माप(__be32)) +	/* trace type */
		nla_total_size(0) +			/* VERDICT, nested */
			nla_total_size(माप(u32)) +	/* verdict code */
		nla_total_size(माप(u32)) +		/* id */
		nla_total_size(NFT_TRACETYPE_LL_HSIZE) +
		nla_total_size(NFT_TRACETYPE_NETWORK_HSIZE) +
		nla_total_size(NFT_TRACETYPE_TRANSPORT_HSIZE) +
		nla_total_size(माप(u32)) +		/* iअगर */
		nla_total_size(माप(__be16)) +	/* iअगरtype */
		nla_total_size(माप(u32)) +		/* oअगर */
		nla_total_size(माप(__be16)) +	/* oअगरtype */
		nla_total_size(माप(u32)) +		/* mark */
		nla_total_size(माप(u32)) +		/* nfproto */
		nla_total_size(माप(u32));		/* policy */

	अगर (nft_trace_have_verdict_chain(info))
		size += nla_total_size(म_माप(info->verdict->chain->name)); /* jump target */

	skb = nlmsg_new(size, GFP_ATOMIC);
	अगर (!skb)
		वापस;

	event = nfnl_msg_type(NFNL_SUBSYS_NFTABLES, NFT_MSG_TRACE);
	nlh = nfnl_msg_put(skb, 0, 0, event, 0, info->basechain->type->family,
			   NFNETLINK_V0, 0);
	अगर (!nlh)
		जाओ nla_put_failure;

	अगर (nla_put_be32(skb, NFTA_TRACE_NFPROTO, htonl(nft_pf(pkt))))
		जाओ nla_put_failure;

	अगर (nla_put_be32(skb, NFTA_TRACE_TYPE, htonl(info->type)))
		जाओ nla_put_failure;

	अगर (trace_fill_id(skb, pkt->skb))
		जाओ nla_put_failure;

	अगर (nla_put_string(skb, NFTA_TRACE_CHAIN, info->chain->name))
		जाओ nla_put_failure;

	अगर (nla_put_string(skb, NFTA_TRACE_TABLE, info->chain->table->name))
		जाओ nla_put_failure;

	अगर (nf_trace_fill_rule_info(skb, info))
		जाओ nla_put_failure;

	चयन (info->type) अणु
	हाल NFT_TRACETYPE_UNSPEC:
	हाल __NFT_TRACETYPE_MAX:
		अवरोध;
	हाल NFT_TRACETYPE_RETURN:
	हाल NFT_TRACETYPE_RULE:
		अगर (nft_verdict_dump(skb, NFTA_TRACE_VERDICT, info->verdict))
			जाओ nla_put_failure;
		अवरोध;
	हाल NFT_TRACETYPE_POLICY:
		अगर (nla_put_be32(skb, NFTA_TRACE_POLICY,
				 htonl(info->basechain->policy)))
			जाओ nla_put_failure;
		अवरोध;
	पूर्ण

	अगर (pkt->skb->mark &&
	    nla_put_be32(skb, NFTA_TRACE_MARK, htonl(pkt->skb->mark)))
		जाओ nla_put_failure;

	अगर (!info->packet_dumped) अणु
		अगर (nf_trace_fill_dev_info(skb, nft_in(pkt), nft_out(pkt)))
			जाओ nla_put_failure;

		अगर (nf_trace_fill_pkt_info(skb, pkt))
			जाओ nla_put_failure;
		info->packet_dumped = true;
	पूर्ण

	nlmsg_end(skb, nlh);
	nfnetlink_send(skb, nft_net(pkt), 0, NFNLGRP_NFTRACE, 0, GFP_ATOMIC);
	वापस;

 nla_put_failure:
	WARN_ON_ONCE(1);
	kमुक्त_skb(skb);
पूर्ण

व्योम nft_trace_init(काष्ठा nft_traceinfo *info, स्थिर काष्ठा nft_pktinfo *pkt,
		    स्थिर काष्ठा nft_verdict *verdict,
		    स्थिर काष्ठा nft_chain *chain)
अणु
	info->basechain = nft_base_chain(chain);
	info->trace = true;
	info->packet_dumped = false;
	info->pkt = pkt;
	info->verdict = verdict;
पूर्ण
