<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/export.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <net/dsa.h>
#समावेश <net/dst_metadata.h>
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>
#समावेश <net/gre.h>
#समावेश <net/pptp.h>
#समावेश <net/tipc.h>
#समावेश <linux/igmp.h>
#समावेश <linux/icmp.h>
#समावेश <linux/sctp.h>
#समावेश <linux/dccp.h>
#समावेश <linux/अगर_tunnel.h>
#समावेश <linux/अगर_pppox.h>
#समावेश <linux/ppp_defs.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/mpls.h>
#समावेश <linux/tcp.h>
#समावेश <linux/ptp_classअगरy.h>
#समावेश <net/flow_dissector.h>
#समावेश <scsi/fc/fc_fcoe.h>
#समावेश <uapi/linux/batadv_packet.h>
#समावेश <linux/bpf.h>
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
#समावेश <net/netfilter/nf_conntrack_core.h>
#समावेश <net/netfilter/nf_conntrack_labels.h>
#पूर्ण_अगर
#समावेश <linux/bpf-netns.h>

अटल व्योम dissector_set_key(काष्ठा flow_dissector *flow_dissector,
			      क्रमागत flow_dissector_key_id key_id)
अणु
	flow_dissector->used_keys |= (1 << key_id);
पूर्ण

व्योम skb_flow_dissector_init(काष्ठा flow_dissector *flow_dissector,
			     स्थिर काष्ठा flow_dissector_key *key,
			     अचिन्हित पूर्णांक key_count)
अणु
	अचिन्हित पूर्णांक i;

	स_रखो(flow_dissector, 0, माप(*flow_dissector));

	क्रम (i = 0; i < key_count; i++, key++) अणु
		/* User should make sure that every key target offset is within
		 * boundaries of अचिन्हित लघु.
		 */
		BUG_ON(key->offset > अच_लघु_उच्च);
		BUG_ON(dissector_uses_key(flow_dissector,
					  key->key_id));

		dissector_set_key(flow_dissector, key->key_id);
		flow_dissector->offset[key->key_id] = key->offset;
	पूर्ण

	/* Ensure that the dissector always includes control and basic key.
	 * That way we are able to aव्योम handling lack of these in fast path.
	 */
	BUG_ON(!dissector_uses_key(flow_dissector,
				   FLOW_DISSECTOR_KEY_CONTROL));
	BUG_ON(!dissector_uses_key(flow_dissector,
				   FLOW_DISSECTOR_KEY_BASIC));
पूर्ण
EXPORT_SYMBOL(skb_flow_dissector_init);

#अगर_घोषित CONFIG_BPF_SYSCALL
पूर्णांक flow_dissector_bpf_prog_attach_check(काष्ठा net *net,
					 काष्ठा bpf_prog *prog)
अणु
	क्रमागत netns_bpf_attach_type type = NETNS_BPF_FLOW_DISSECTOR;

	अगर (net == &init_net) अणु
		/* BPF flow dissector in the root namespace overrides
		 * any per-net-namespace one. When attaching to root,
		 * make sure we करोn't have any BPF program attached
		 * to the non-root namespaces.
		 */
		काष्ठा net *ns;

		क्रम_each_net(ns) अणु
			अगर (ns == &init_net)
				जारी;
			अगर (rcu_access_poपूर्णांकer(ns->bpf.run_array[type]))
				वापस -EEXIST;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Make sure root flow dissector is not attached
		 * when attaching to the non-root namespace.
		 */
		अगर (rcu_access_poपूर्णांकer(init_net.bpf.run_array[type]))
			वापस -EEXIST;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_BPF_SYSCALL */

/**
 * __skb_flow_get_ports - extract the upper layer ports and वापस them
 * @skb: sk_buff to extract the ports from
 * @thoff: transport header offset
 * @ip_proto: protocol क्रम which to get port offset
 * @data: raw buffer poपूर्णांकer to the packet, अगर शून्य use skb->data
 * @hlen: packet header length, अगर @data is शून्य use skb_headlen(skb)
 *
 * The function will try to retrieve the ports at offset thoff + poff where poff
 * is the protocol port offset वापसed from proto_ports_offset
 */
__be32 __skb_flow_get_ports(स्थिर काष्ठा sk_buff *skb, पूर्णांक thoff, u8 ip_proto,
			    स्थिर व्योम *data, पूर्णांक hlen)
अणु
	पूर्णांक poff = proto_ports_offset(ip_proto);

	अगर (!data) अणु
		data = skb->data;
		hlen = skb_headlen(skb);
	पूर्ण

	अगर (poff >= 0) अणु
		__be32 *ports, _ports;

		ports = __skb_header_poपूर्णांकer(skb, thoff + poff,
					     माप(_ports), data, hlen, &_ports);
		अगर (ports)
			वापस *ports;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(__skb_flow_get_ports);

अटल bool icmp_has_id(u8 type)
अणु
	चयन (type) अणु
	हाल ICMP_ECHO:
	हाल ICMP_ECHOREPLY:
	हाल ICMP_TIMESTAMP:
	हाल ICMP_TIMESTAMPREPLY:
	हाल ICMPV6_ECHO_REQUEST:
	हाल ICMPV6_ECHO_REPLY:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * skb_flow_get_icmp_tci - extract ICMP(6) Type, Code and Identअगरier fields
 * @skb: sk_buff to extract from
 * @key_icmp: काष्ठा flow_dissector_key_icmp to fill
 * @data: raw buffer poपूर्णांकer to the packet
 * @thoff: offset to extract at
 * @hlen: packet header length
 */
व्योम skb_flow_get_icmp_tci(स्थिर काष्ठा sk_buff *skb,
			   काष्ठा flow_dissector_key_icmp *key_icmp,
			   स्थिर व्योम *data, पूर्णांक thoff, पूर्णांक hlen)
अणु
	काष्ठा icmphdr *ih, _ih;

	ih = __skb_header_poपूर्णांकer(skb, thoff, माप(_ih), data, hlen, &_ih);
	अगर (!ih)
		वापस;

	key_icmp->type = ih->type;
	key_icmp->code = ih->code;

	/* As we use 0 to संकेत that the Id field is not present,
	 * aव्योम confusion with packets without such field
	 */
	अगर (icmp_has_id(ih->type))
		key_icmp->id = ih->un.echo.id ? ntohs(ih->un.echo.id) : 1;
	अन्यथा
		key_icmp->id = 0;
पूर्ण
EXPORT_SYMBOL(skb_flow_get_icmp_tci);

/* If FLOW_DISSECTOR_KEY_ICMP is set, dissect an ICMP packet
 * using skb_flow_get_icmp_tci().
 */
अटल व्योम __skb_flow_dissect_icmp(स्थिर काष्ठा sk_buff *skb,
				    काष्ठा flow_dissector *flow_dissector,
				    व्योम *target_container, स्थिर व्योम *data,
				    पूर्णांक thoff, पूर्णांक hlen)
अणु
	काष्ठा flow_dissector_key_icmp *key_icmp;

	अगर (!dissector_uses_key(flow_dissector, FLOW_DISSECTOR_KEY_ICMP))
		वापस;

	key_icmp = skb_flow_dissector_target(flow_dissector,
					     FLOW_DISSECTOR_KEY_ICMP,
					     target_container);

	skb_flow_get_icmp_tci(skb, key_icmp, data, thoff, hlen);
पूर्ण

व्योम skb_flow_dissect_meta(स्थिर काष्ठा sk_buff *skb,
			   काष्ठा flow_dissector *flow_dissector,
			   व्योम *target_container)
अणु
	काष्ठा flow_dissector_key_meta *meta;

	अगर (!dissector_uses_key(flow_dissector, FLOW_DISSECTOR_KEY_META))
		वापस;

	meta = skb_flow_dissector_target(flow_dissector,
					 FLOW_DISSECTOR_KEY_META,
					 target_container);
	meta->ingress_अगरindex = skb->skb_iअगर;
पूर्ण
EXPORT_SYMBOL(skb_flow_dissect_meta);

अटल व्योम
skb_flow_dissect_set_enc_addr_type(क्रमागत flow_dissector_key_id type,
				   काष्ठा flow_dissector *flow_dissector,
				   व्योम *target_container)
अणु
	काष्ठा flow_dissector_key_control *ctrl;

	अगर (!dissector_uses_key(flow_dissector, FLOW_DISSECTOR_KEY_ENC_CONTROL))
		वापस;

	ctrl = skb_flow_dissector_target(flow_dissector,
					 FLOW_DISSECTOR_KEY_ENC_CONTROL,
					 target_container);
	ctrl->addr_type = type;
पूर्ण

व्योम
skb_flow_dissect_ct(स्थिर काष्ठा sk_buff *skb,
		    काष्ठा flow_dissector *flow_dissector,
		    व्योम *target_container, u16 *ctinfo_map,
		    माप_प्रकार mapsize, bool post_ct)
अणु
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
	काष्ठा flow_dissector_key_ct *key;
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn_labels *cl;
	काष्ठा nf_conn *ct;

	अगर (!dissector_uses_key(flow_dissector, FLOW_DISSECTOR_KEY_CT))
		वापस;

	ct = nf_ct_get(skb, &ctinfo);
	अगर (!ct && !post_ct)
		वापस;

	key = skb_flow_dissector_target(flow_dissector,
					FLOW_DISSECTOR_KEY_CT,
					target_container);

	अगर (!ct) अणु
		key->ct_state = TCA_FLOWER_KEY_CT_FLAGS_TRACKED |
				TCA_FLOWER_KEY_CT_FLAGS_INVALID;
		वापस;
	पूर्ण

	अगर (ctinfo < mapsize)
		key->ct_state = ctinfo_map[ctinfo];
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK_ZONES)
	key->ct_zone = ct->zone.id;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK_MARK)
	key->ct_mark = ct->mark;
#पूर्ण_अगर

	cl = nf_ct_labels_find(ct);
	अगर (cl)
		स_नकल(key->ct_labels, cl->bits, माप(key->ct_labels));
#पूर्ण_अगर /* CONFIG_NF_CONNTRACK */
पूर्ण
EXPORT_SYMBOL(skb_flow_dissect_ct);

व्योम
skb_flow_dissect_tunnel_info(स्थिर काष्ठा sk_buff *skb,
			     काष्ठा flow_dissector *flow_dissector,
			     व्योम *target_container)
अणु
	काष्ठा ip_tunnel_info *info;
	काष्ठा ip_tunnel_key *key;

	/* A quick check to see अगर there might be something to करो. */
	अगर (!dissector_uses_key(flow_dissector,
				FLOW_DISSECTOR_KEY_ENC_KEYID) &&
	    !dissector_uses_key(flow_dissector,
				FLOW_DISSECTOR_KEY_ENC_IPV4_ADDRS) &&
	    !dissector_uses_key(flow_dissector,
				FLOW_DISSECTOR_KEY_ENC_IPV6_ADDRS) &&
	    !dissector_uses_key(flow_dissector,
				FLOW_DISSECTOR_KEY_ENC_CONTROL) &&
	    !dissector_uses_key(flow_dissector,
				FLOW_DISSECTOR_KEY_ENC_PORTS) &&
	    !dissector_uses_key(flow_dissector,
				FLOW_DISSECTOR_KEY_ENC_IP) &&
	    !dissector_uses_key(flow_dissector,
				FLOW_DISSECTOR_KEY_ENC_OPTS))
		वापस;

	info = skb_tunnel_info(skb);
	अगर (!info)
		वापस;

	key = &info->key;

	चयन (ip_tunnel_info_af(info)) अणु
	हाल AF_INET:
		skb_flow_dissect_set_enc_addr_type(FLOW_DISSECTOR_KEY_IPV4_ADDRS,
						   flow_dissector,
						   target_container);
		अगर (dissector_uses_key(flow_dissector,
				       FLOW_DISSECTOR_KEY_ENC_IPV4_ADDRS)) अणु
			काष्ठा flow_dissector_key_ipv4_addrs *ipv4;

			ipv4 = skb_flow_dissector_target(flow_dissector,
							 FLOW_DISSECTOR_KEY_ENC_IPV4_ADDRS,
							 target_container);
			ipv4->src = key->u.ipv4.src;
			ipv4->dst = key->u.ipv4.dst;
		पूर्ण
		अवरोध;
	हाल AF_INET6:
		skb_flow_dissect_set_enc_addr_type(FLOW_DISSECTOR_KEY_IPV6_ADDRS,
						   flow_dissector,
						   target_container);
		अगर (dissector_uses_key(flow_dissector,
				       FLOW_DISSECTOR_KEY_ENC_IPV6_ADDRS)) अणु
			काष्ठा flow_dissector_key_ipv6_addrs *ipv6;

			ipv6 = skb_flow_dissector_target(flow_dissector,
							 FLOW_DISSECTOR_KEY_ENC_IPV6_ADDRS,
							 target_container);
			ipv6->src = key->u.ipv6.src;
			ipv6->dst = key->u.ipv6.dst;
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (dissector_uses_key(flow_dissector, FLOW_DISSECTOR_KEY_ENC_KEYID)) अणु
		काष्ठा flow_dissector_key_keyid *keyid;

		keyid = skb_flow_dissector_target(flow_dissector,
						  FLOW_DISSECTOR_KEY_ENC_KEYID,
						  target_container);
		keyid->keyid = tunnel_id_to_key32(key->tun_id);
	पूर्ण

	अगर (dissector_uses_key(flow_dissector, FLOW_DISSECTOR_KEY_ENC_PORTS)) अणु
		काष्ठा flow_dissector_key_ports *tp;

		tp = skb_flow_dissector_target(flow_dissector,
					       FLOW_DISSECTOR_KEY_ENC_PORTS,
					       target_container);
		tp->src = key->tp_src;
		tp->dst = key->tp_dst;
	पूर्ण

	अगर (dissector_uses_key(flow_dissector, FLOW_DISSECTOR_KEY_ENC_IP)) अणु
		काष्ठा flow_dissector_key_ip *ip;

		ip = skb_flow_dissector_target(flow_dissector,
					       FLOW_DISSECTOR_KEY_ENC_IP,
					       target_container);
		ip->tos = key->tos;
		ip->ttl = key->ttl;
	पूर्ण

	अगर (dissector_uses_key(flow_dissector, FLOW_DISSECTOR_KEY_ENC_OPTS)) अणु
		काष्ठा flow_dissector_key_enc_opts *enc_opt;

		enc_opt = skb_flow_dissector_target(flow_dissector,
						    FLOW_DISSECTOR_KEY_ENC_OPTS,
						    target_container);

		अगर (info->options_len) अणु
			enc_opt->len = info->options_len;
			ip_tunnel_info_opts_get(enc_opt->data, info);
			enc_opt->dst_opt_type = info->key.tun_flags &
						TUNNEL_OPTIONS_PRESENT;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(skb_flow_dissect_tunnel_info);

व्योम skb_flow_dissect_hash(स्थिर काष्ठा sk_buff *skb,
			   काष्ठा flow_dissector *flow_dissector,
			   व्योम *target_container)
अणु
	काष्ठा flow_dissector_key_hash *key;

	अगर (!dissector_uses_key(flow_dissector, FLOW_DISSECTOR_KEY_HASH))
		वापस;

	key = skb_flow_dissector_target(flow_dissector,
					FLOW_DISSECTOR_KEY_HASH,
					target_container);

	key->hash = skb_get_hash_raw(skb);
पूर्ण
EXPORT_SYMBOL(skb_flow_dissect_hash);

अटल क्रमागत flow_dissect_ret
__skb_flow_dissect_mpls(स्थिर काष्ठा sk_buff *skb,
			काष्ठा flow_dissector *flow_dissector,
			व्योम *target_container, स्थिर व्योम *data, पूर्णांक nhoff,
			पूर्णांक hlen, पूर्णांक lse_index, bool *entropy_label)
अणु
	काष्ठा mpls_label *hdr, _hdr;
	u32 entry, label, bos;

	अगर (!dissector_uses_key(flow_dissector,
				FLOW_DISSECTOR_KEY_MPLS_ENTROPY) &&
	    !dissector_uses_key(flow_dissector, FLOW_DISSECTOR_KEY_MPLS))
		वापस FLOW_DISSECT_RET_OUT_GOOD;

	अगर (lse_index >= FLOW_DIS_MPLS_MAX)
		वापस FLOW_DISSECT_RET_OUT_GOOD;

	hdr = __skb_header_poपूर्णांकer(skb, nhoff, माप(_hdr), data,
				   hlen, &_hdr);
	अगर (!hdr)
		वापस FLOW_DISSECT_RET_OUT_BAD;

	entry = ntohl(hdr->entry);
	label = (entry & MPLS_LS_LABEL_MASK) >> MPLS_LS_LABEL_SHIFT;
	bos = (entry & MPLS_LS_S_MASK) >> MPLS_LS_S_SHIFT;

	अगर (dissector_uses_key(flow_dissector, FLOW_DISSECTOR_KEY_MPLS)) अणु
		काष्ठा flow_dissector_key_mpls *key_mpls;
		काष्ठा flow_dissector_mpls_lse *lse;

		key_mpls = skb_flow_dissector_target(flow_dissector,
						     FLOW_DISSECTOR_KEY_MPLS,
						     target_container);
		lse = &key_mpls->ls[lse_index];

		lse->mpls_ttl = (entry & MPLS_LS_TTL_MASK) >> MPLS_LS_TTL_SHIFT;
		lse->mpls_bos = bos;
		lse->mpls_tc = (entry & MPLS_LS_TC_MASK) >> MPLS_LS_TC_SHIFT;
		lse->mpls_label = label;
		dissector_set_mpls_lse(key_mpls, lse_index);
	पूर्ण

	अगर (*entropy_label &&
	    dissector_uses_key(flow_dissector,
			       FLOW_DISSECTOR_KEY_MPLS_ENTROPY)) अणु
		काष्ठा flow_dissector_key_keyid *key_keyid;

		key_keyid = skb_flow_dissector_target(flow_dissector,
						      FLOW_DISSECTOR_KEY_MPLS_ENTROPY,
						      target_container);
		key_keyid->keyid = cpu_to_be32(label);
	पूर्ण

	*entropy_label = label == MPLS_LABEL_ENTROPY;

	वापस bos ? FLOW_DISSECT_RET_OUT_GOOD : FLOW_DISSECT_RET_PROTO_AGAIN;
पूर्ण

अटल क्रमागत flow_dissect_ret
__skb_flow_dissect_arp(स्थिर काष्ठा sk_buff *skb,
		       काष्ठा flow_dissector *flow_dissector,
		       व्योम *target_container, स्थिर व्योम *data,
		       पूर्णांक nhoff, पूर्णांक hlen)
अणु
	काष्ठा flow_dissector_key_arp *key_arp;
	काष्ठा अणु
		अचिन्हित अक्षर ar_sha[ETH_ALEN];
		अचिन्हित अक्षर ar_sip[4];
		अचिन्हित अक्षर ar_tha[ETH_ALEN];
		अचिन्हित अक्षर ar_tip[4];
	पूर्ण *arp_eth, _arp_eth;
	स्थिर काष्ठा arphdr *arp;
	काष्ठा arphdr _arp;

	अगर (!dissector_uses_key(flow_dissector, FLOW_DISSECTOR_KEY_ARP))
		वापस FLOW_DISSECT_RET_OUT_GOOD;

	arp = __skb_header_poपूर्णांकer(skb, nhoff, माप(_arp), data,
				   hlen, &_arp);
	अगर (!arp)
		वापस FLOW_DISSECT_RET_OUT_BAD;

	अगर (arp->ar_hrd != htons(ARPHRD_ETHER) ||
	    arp->ar_pro != htons(ETH_P_IP) ||
	    arp->ar_hln != ETH_ALEN ||
	    arp->ar_pln != 4 ||
	    (arp->ar_op != htons(ARPOP_REPLY) &&
	     arp->ar_op != htons(ARPOP_REQUEST)))
		वापस FLOW_DISSECT_RET_OUT_BAD;

	arp_eth = __skb_header_poपूर्णांकer(skb, nhoff + माप(_arp),
				       माप(_arp_eth), data,
				       hlen, &_arp_eth);
	अगर (!arp_eth)
		वापस FLOW_DISSECT_RET_OUT_BAD;

	key_arp = skb_flow_dissector_target(flow_dissector,
					    FLOW_DISSECTOR_KEY_ARP,
					    target_container);

	स_नकल(&key_arp->sip, arp_eth->ar_sip, माप(key_arp->sip));
	स_नकल(&key_arp->tip, arp_eth->ar_tip, माप(key_arp->tip));

	/* Only store the lower byte of the opcode;
	 * this covers ARPOP_REPLY and ARPOP_REQUEST.
	 */
	key_arp->op = ntohs(arp->ar_op) & 0xff;

	ether_addr_copy(key_arp->sha, arp_eth->ar_sha);
	ether_addr_copy(key_arp->tha, arp_eth->ar_tha);

	वापस FLOW_DISSECT_RET_OUT_GOOD;
पूर्ण

अटल क्रमागत flow_dissect_ret
__skb_flow_dissect_gre(स्थिर काष्ठा sk_buff *skb,
		       काष्ठा flow_dissector_key_control *key_control,
		       काष्ठा flow_dissector *flow_dissector,
		       व्योम *target_container, स्थिर व्योम *data,
		       __be16 *p_proto, पूर्णांक *p_nhoff, पूर्णांक *p_hlen,
		       अचिन्हित पूर्णांक flags)
अणु
	काष्ठा flow_dissector_key_keyid *key_keyid;
	काष्ठा gre_base_hdr *hdr, _hdr;
	पूर्णांक offset = 0;
	u16 gre_ver;

	hdr = __skb_header_poपूर्णांकer(skb, *p_nhoff, माप(_hdr),
				   data, *p_hlen, &_hdr);
	अगर (!hdr)
		वापस FLOW_DISSECT_RET_OUT_BAD;

	/* Only look inside GRE without routing */
	अगर (hdr->flags & GRE_ROUTING)
		वापस FLOW_DISSECT_RET_OUT_GOOD;

	/* Only look inside GRE क्रम version 0 and 1 */
	gre_ver = ntohs(hdr->flags & GRE_VERSION);
	अगर (gre_ver > 1)
		वापस FLOW_DISSECT_RET_OUT_GOOD;

	*p_proto = hdr->protocol;
	अगर (gre_ver) अणु
		/* Version1 must be PPTP, and check the flags */
		अगर (!(*p_proto == GRE_PROTO_PPP && (hdr->flags & GRE_KEY)))
			वापस FLOW_DISSECT_RET_OUT_GOOD;
	पूर्ण

	offset += माप(काष्ठा gre_base_hdr);

	अगर (hdr->flags & GRE_CSUM)
		offset += माप_field(काष्ठा gre_full_hdr, csum) +
			  माप_field(काष्ठा gre_full_hdr, reserved1);

	अगर (hdr->flags & GRE_KEY) अणु
		स्थिर __be32 *keyid;
		__be32 _keyid;

		keyid = __skb_header_poपूर्णांकer(skb, *p_nhoff + offset,
					     माप(_keyid),
					     data, *p_hlen, &_keyid);
		अगर (!keyid)
			वापस FLOW_DISSECT_RET_OUT_BAD;

		अगर (dissector_uses_key(flow_dissector,
				       FLOW_DISSECTOR_KEY_GRE_KEYID)) अणु
			key_keyid = skb_flow_dissector_target(flow_dissector,
							      FLOW_DISSECTOR_KEY_GRE_KEYID,
							      target_container);
			अगर (gre_ver == 0)
				key_keyid->keyid = *keyid;
			अन्यथा
				key_keyid->keyid = *keyid & GRE_PPTP_KEY_MASK;
		पूर्ण
		offset += माप_field(काष्ठा gre_full_hdr, key);
	पूर्ण

	अगर (hdr->flags & GRE_SEQ)
		offset += माप_field(काष्ठा pptp_gre_header, seq);

	अगर (gre_ver == 0) अणु
		अगर (*p_proto == htons(ETH_P_TEB)) अणु
			स्थिर काष्ठा ethhdr *eth;
			काष्ठा ethhdr _eth;

			eth = __skb_header_poपूर्णांकer(skb, *p_nhoff + offset,
						   माप(_eth),
						   data, *p_hlen, &_eth);
			अगर (!eth)
				वापस FLOW_DISSECT_RET_OUT_BAD;
			*p_proto = eth->h_proto;
			offset += माप(*eth);

			/* Cap headers that we access via poपूर्णांकers at the
			 * end of the Ethernet header as our maximum alignment
			 * at that poपूर्णांक is only 2 bytes.
			 */
			अगर (NET_IP_ALIGN)
				*p_hlen = *p_nhoff + offset;
		पूर्ण
	पूर्ण अन्यथा अणु /* version 1, must be PPTP */
		u8 _ppp_hdr[PPP_HDRLEN];
		u8 *ppp_hdr;

		अगर (hdr->flags & GRE_ACK)
			offset += माप_field(काष्ठा pptp_gre_header, ack);

		ppp_hdr = __skb_header_poपूर्णांकer(skb, *p_nhoff + offset,
					       माप(_ppp_hdr),
					       data, *p_hlen, _ppp_hdr);
		अगर (!ppp_hdr)
			वापस FLOW_DISSECT_RET_OUT_BAD;

		चयन (PPP_PROTOCOL(ppp_hdr)) अणु
		हाल PPP_IP:
			*p_proto = htons(ETH_P_IP);
			अवरोध;
		हाल PPP_IPV6:
			*p_proto = htons(ETH_P_IPV6);
			अवरोध;
		शेष:
			/* Could probably catch some more like MPLS */
			अवरोध;
		पूर्ण

		offset += PPP_HDRLEN;
	पूर्ण

	*p_nhoff += offset;
	key_control->flags |= FLOW_DIS_ENCAPSULATION;
	अगर (flags & FLOW_DISSECTOR_F_STOP_AT_ENCAP)
		वापस FLOW_DISSECT_RET_OUT_GOOD;

	वापस FLOW_DISSECT_RET_PROTO_AGAIN;
पूर्ण

/**
 * __skb_flow_dissect_batadv() - dissect baपंचांगan-adv header
 * @skb: sk_buff to with the baपंचांगan-adv header
 * @key_control: flow dissectors control key
 * @data: raw buffer poपूर्णांकer to the packet, अगर शून्य use skb->data
 * @p_proto: poपूर्णांकer used to update the protocol to process next
 * @p_nhoff: poपूर्णांकer used to update inner network header offset
 * @hlen: packet header length
 * @flags: any combination of FLOW_DISSECTOR_F_*
 *
 * ETH_P_BATMAN packets are tried to be dissected. Only
 * &काष्ठा batadv_unicast packets are actually processed because they contain an
 * inner ethernet header and are usually followed by actual network header. This
 * allows the flow dissector to जारी processing the packet.
 *
 * Return: FLOW_DISSECT_RET_PROTO_AGAIN when &काष्ठा batadv_unicast was found,
 *  FLOW_DISSECT_RET_OUT_GOOD when dissector should stop after encapsulation,
 *  otherwise FLOW_DISSECT_RET_OUT_BAD
 */
अटल क्रमागत flow_dissect_ret
__skb_flow_dissect_batadv(स्थिर काष्ठा sk_buff *skb,
			  काष्ठा flow_dissector_key_control *key_control,
			  स्थिर व्योम *data, __be16 *p_proto, पूर्णांक *p_nhoff,
			  पूर्णांक hlen, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा अणु
		काष्ठा batadv_unicast_packet batadv_unicast;
		काष्ठा ethhdr eth;
	पूर्ण *hdr, _hdr;

	hdr = __skb_header_poपूर्णांकer(skb, *p_nhoff, माप(_hdr), data, hlen,
				   &_hdr);
	अगर (!hdr)
		वापस FLOW_DISSECT_RET_OUT_BAD;

	अगर (hdr->batadv_unicast.version != BATADV_COMPAT_VERSION)
		वापस FLOW_DISSECT_RET_OUT_BAD;

	अगर (hdr->batadv_unicast.packet_type != BATADV_UNICAST)
		वापस FLOW_DISSECT_RET_OUT_BAD;

	*p_proto = hdr->eth.h_proto;
	*p_nhoff += माप(*hdr);

	key_control->flags |= FLOW_DIS_ENCAPSULATION;
	अगर (flags & FLOW_DISSECTOR_F_STOP_AT_ENCAP)
		वापस FLOW_DISSECT_RET_OUT_GOOD;

	वापस FLOW_DISSECT_RET_PROTO_AGAIN;
पूर्ण

अटल व्योम
__skb_flow_dissect_tcp(स्थिर काष्ठा sk_buff *skb,
		       काष्ठा flow_dissector *flow_dissector,
		       व्योम *target_container, स्थिर व्योम *data,
		       पूर्णांक thoff, पूर्णांक hlen)
अणु
	काष्ठा flow_dissector_key_tcp *key_tcp;
	काष्ठा tcphdr *th, _th;

	अगर (!dissector_uses_key(flow_dissector, FLOW_DISSECTOR_KEY_TCP))
		वापस;

	th = __skb_header_poपूर्णांकer(skb, thoff, माप(_th), data, hlen, &_th);
	अगर (!th)
		वापस;

	अगर (unlikely(__tcp_hdrlen(th) < माप(_th)))
		वापस;

	key_tcp = skb_flow_dissector_target(flow_dissector,
					    FLOW_DISSECTOR_KEY_TCP,
					    target_container);
	key_tcp->flags = (*(__be16 *) &tcp_flag_word(th) & htons(0x0FFF));
पूर्ण

अटल व्योम
__skb_flow_dissect_ports(स्थिर काष्ठा sk_buff *skb,
			 काष्ठा flow_dissector *flow_dissector,
			 व्योम *target_container, स्थिर व्योम *data,
			 पूर्णांक nhoff, u8 ip_proto, पूर्णांक hlen)
अणु
	क्रमागत flow_dissector_key_id dissector_ports = FLOW_DISSECTOR_KEY_MAX;
	काष्ठा flow_dissector_key_ports *key_ports;

	अगर (dissector_uses_key(flow_dissector, FLOW_DISSECTOR_KEY_PORTS))
		dissector_ports = FLOW_DISSECTOR_KEY_PORTS;
	अन्यथा अगर (dissector_uses_key(flow_dissector,
				    FLOW_DISSECTOR_KEY_PORTS_RANGE))
		dissector_ports = FLOW_DISSECTOR_KEY_PORTS_RANGE;

	अगर (dissector_ports == FLOW_DISSECTOR_KEY_MAX)
		वापस;

	key_ports = skb_flow_dissector_target(flow_dissector,
					      dissector_ports,
					      target_container);
	key_ports->ports = __skb_flow_get_ports(skb, nhoff, ip_proto,
						data, hlen);
पूर्ण

अटल व्योम
__skb_flow_dissect_ipv4(स्थिर काष्ठा sk_buff *skb,
			काष्ठा flow_dissector *flow_dissector,
			व्योम *target_container, स्थिर व्योम *data,
			स्थिर काष्ठा iphdr *iph)
अणु
	काष्ठा flow_dissector_key_ip *key_ip;

	अगर (!dissector_uses_key(flow_dissector, FLOW_DISSECTOR_KEY_IP))
		वापस;

	key_ip = skb_flow_dissector_target(flow_dissector,
					   FLOW_DISSECTOR_KEY_IP,
					   target_container);
	key_ip->tos = iph->tos;
	key_ip->ttl = iph->ttl;
पूर्ण

अटल व्योम
__skb_flow_dissect_ipv6(स्थिर काष्ठा sk_buff *skb,
			काष्ठा flow_dissector *flow_dissector,
			व्योम *target_container, स्थिर व्योम *data,
			स्थिर काष्ठा ipv6hdr *iph)
अणु
	काष्ठा flow_dissector_key_ip *key_ip;

	अगर (!dissector_uses_key(flow_dissector, FLOW_DISSECTOR_KEY_IP))
		वापस;

	key_ip = skb_flow_dissector_target(flow_dissector,
					   FLOW_DISSECTOR_KEY_IP,
					   target_container);
	key_ip->tos = ipv6_get_dsfield(iph);
	key_ip->ttl = iph->hop_limit;
पूर्ण

/* Maximum number of protocol headers that can be parsed in
 * __skb_flow_dissect
 */
#घोषणा MAX_FLOW_DISSECT_HDRS	15

अटल bool skb_flow_dissect_allowed(पूर्णांक *num_hdrs)
अणु
	++*num_hdrs;

	वापस (*num_hdrs <= MAX_FLOW_DISSECT_HDRS);
पूर्ण

अटल व्योम __skb_flow_bpf_to_target(स्थिर काष्ठा bpf_flow_keys *flow_keys,
				     काष्ठा flow_dissector *flow_dissector,
				     व्योम *target_container)
अणु
	काष्ठा flow_dissector_key_ports *key_ports = शून्य;
	काष्ठा flow_dissector_key_control *key_control;
	काष्ठा flow_dissector_key_basic *key_basic;
	काष्ठा flow_dissector_key_addrs *key_addrs;
	काष्ठा flow_dissector_key_tags *key_tags;

	key_control = skb_flow_dissector_target(flow_dissector,
						FLOW_DISSECTOR_KEY_CONTROL,
						target_container);
	key_control->thoff = flow_keys->thoff;
	अगर (flow_keys->is_frag)
		key_control->flags |= FLOW_DIS_IS_FRAGMENT;
	अगर (flow_keys->is_first_frag)
		key_control->flags |= FLOW_DIS_FIRST_FRAG;
	अगर (flow_keys->is_encap)
		key_control->flags |= FLOW_DIS_ENCAPSULATION;

	key_basic = skb_flow_dissector_target(flow_dissector,
					      FLOW_DISSECTOR_KEY_BASIC,
					      target_container);
	key_basic->n_proto = flow_keys->n_proto;
	key_basic->ip_proto = flow_keys->ip_proto;

	अगर (flow_keys->addr_proto == ETH_P_IP &&
	    dissector_uses_key(flow_dissector, FLOW_DISSECTOR_KEY_IPV4_ADDRS)) अणु
		key_addrs = skb_flow_dissector_target(flow_dissector,
						      FLOW_DISSECTOR_KEY_IPV4_ADDRS,
						      target_container);
		key_addrs->v4addrs.src = flow_keys->ipv4_src;
		key_addrs->v4addrs.dst = flow_keys->ipv4_dst;
		key_control->addr_type = FLOW_DISSECTOR_KEY_IPV4_ADDRS;
	पूर्ण अन्यथा अगर (flow_keys->addr_proto == ETH_P_IPV6 &&
		   dissector_uses_key(flow_dissector,
				      FLOW_DISSECTOR_KEY_IPV6_ADDRS)) अणु
		key_addrs = skb_flow_dissector_target(flow_dissector,
						      FLOW_DISSECTOR_KEY_IPV6_ADDRS,
						      target_container);
		स_नकल(&key_addrs->v6addrs.src, &flow_keys->ipv6_src,
		       माप(key_addrs->v6addrs.src));
		स_नकल(&key_addrs->v6addrs.dst, &flow_keys->ipv6_dst,
		       माप(key_addrs->v6addrs.dst));
		key_control->addr_type = FLOW_DISSECTOR_KEY_IPV6_ADDRS;
	पूर्ण

	अगर (dissector_uses_key(flow_dissector, FLOW_DISSECTOR_KEY_PORTS))
		key_ports = skb_flow_dissector_target(flow_dissector,
						      FLOW_DISSECTOR_KEY_PORTS,
						      target_container);
	अन्यथा अगर (dissector_uses_key(flow_dissector,
				    FLOW_DISSECTOR_KEY_PORTS_RANGE))
		key_ports = skb_flow_dissector_target(flow_dissector,
						      FLOW_DISSECTOR_KEY_PORTS_RANGE,
						      target_container);

	अगर (key_ports) अणु
		key_ports->src = flow_keys->sport;
		key_ports->dst = flow_keys->dport;
	पूर्ण

	अगर (dissector_uses_key(flow_dissector,
			       FLOW_DISSECTOR_KEY_FLOW_LABEL)) अणु
		key_tags = skb_flow_dissector_target(flow_dissector,
						     FLOW_DISSECTOR_KEY_FLOW_LABEL,
						     target_container);
		key_tags->flow_label = ntohl(flow_keys->flow_label);
	पूर्ण
पूर्ण

bool bpf_flow_dissect(काष्ठा bpf_prog *prog, काष्ठा bpf_flow_dissector *ctx,
		      __be16 proto, पूर्णांक nhoff, पूर्णांक hlen, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा bpf_flow_keys *flow_keys = ctx->flow_keys;
	u32 result;

	/* Pass parameters to the BPF program */
	स_रखो(flow_keys, 0, माप(*flow_keys));
	flow_keys->n_proto = proto;
	flow_keys->nhoff = nhoff;
	flow_keys->thoff = flow_keys->nhoff;

	BUILD_BUG_ON((पूर्णांक)BPF_FLOW_DISSECTOR_F_PARSE_1ST_FRAG !=
		     (पूर्णांक)FLOW_DISSECTOR_F_PARSE_1ST_FRAG);
	BUILD_BUG_ON((पूर्णांक)BPF_FLOW_DISSECTOR_F_STOP_AT_FLOW_LABEL !=
		     (पूर्णांक)FLOW_DISSECTOR_F_STOP_AT_FLOW_LABEL);
	BUILD_BUG_ON((पूर्णांक)BPF_FLOW_DISSECTOR_F_STOP_AT_ENCAP !=
		     (पूर्णांक)FLOW_DISSECTOR_F_STOP_AT_ENCAP);
	flow_keys->flags = flags;

	result = bpf_prog_run_pin_on_cpu(prog, ctx);

	flow_keys->nhoff = clamp_t(u16, flow_keys->nhoff, nhoff, hlen);
	flow_keys->thoff = clamp_t(u16, flow_keys->thoff,
				   flow_keys->nhoff, hlen);

	वापस result == BPF_OK;
पूर्ण

/**
 * __skb_flow_dissect - extract the flow_keys काष्ठा and वापस it
 * @net: associated network namespace, derived from @skb अगर शून्य
 * @skb: sk_buff to extract the flow from, can be शून्य अगर the rest are specअगरied
 * @flow_dissector: list of keys to dissect
 * @target_container: target काष्ठाure to put dissected values पूर्णांकo
 * @data: raw buffer poपूर्णांकer to the packet, अगर शून्य use skb->data
 * @proto: protocol क्रम which to get the flow, अगर @data is शून्य use skb->protocol
 * @nhoff: network header offset, अगर @data is शून्य use skb_network_offset(skb)
 * @hlen: packet header length, अगर @data is शून्य use skb_headlen(skb)
 * @flags: flags that control the dissection process, e.g.
 *         FLOW_DISSECTOR_F_STOP_AT_ENCAP.
 *
 * The function will try to retrieve inभागidual keys पूर्णांकo target specअगरied
 * by flow_dissector from either the skbuff or a raw buffer specअगरied by the
 * rest parameters.
 *
 * Caller must take care of zeroing target container memory.
 */
bool __skb_flow_dissect(स्थिर काष्ठा net *net,
			स्थिर काष्ठा sk_buff *skb,
			काष्ठा flow_dissector *flow_dissector,
			व्योम *target_container, स्थिर व्योम *data,
			__be16 proto, पूर्णांक nhoff, पूर्णांक hlen, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा flow_dissector_key_control *key_control;
	काष्ठा flow_dissector_key_basic *key_basic;
	काष्ठा flow_dissector_key_addrs *key_addrs;
	काष्ठा flow_dissector_key_tags *key_tags;
	काष्ठा flow_dissector_key_vlan *key_vlan;
	क्रमागत flow_dissect_ret fdret;
	क्रमागत flow_dissector_key_id dissector_vlan = FLOW_DISSECTOR_KEY_MAX;
	bool mpls_el = false;
	पूर्णांक mpls_lse = 0;
	पूर्णांक num_hdrs = 0;
	u8 ip_proto = 0;
	bool ret;

	अगर (!data) अणु
		data = skb->data;
		proto = skb_vlan_tag_present(skb) ?
			 skb->vlan_proto : skb->protocol;
		nhoff = skb_network_offset(skb);
		hlen = skb_headlen(skb);
#अगर IS_ENABLED(CONFIG_NET_DSA)
		अगर (unlikely(skb->dev && netdev_uses_dsa(skb->dev) &&
			     proto == htons(ETH_P_XDSA))) अणु
			स्थिर काष्ठा dsa_device_ops *ops;
			पूर्णांक offset = 0;

			ops = skb->dev->dsa_ptr->tag_ops;
			/* Tail taggers करोn't अवरोध flow dissection */
			अगर (!ops->tail_tag) अणु
				अगर (ops->flow_dissect)
					ops->flow_dissect(skb, &proto, &offset);
				अन्यथा
					dsa_tag_generic_flow_dissect(skb,
								     &proto,
								     &offset);
				hlen -= offset;
				nhoff += offset;
			पूर्ण
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	/* It is ensured by skb_flow_dissector_init() that control key will
	 * be always present.
	 */
	key_control = skb_flow_dissector_target(flow_dissector,
						FLOW_DISSECTOR_KEY_CONTROL,
						target_container);

	/* It is ensured by skb_flow_dissector_init() that basic key will
	 * be always present.
	 */
	key_basic = skb_flow_dissector_target(flow_dissector,
					      FLOW_DISSECTOR_KEY_BASIC,
					      target_container);

	अगर (skb) अणु
		अगर (!net) अणु
			अगर (skb->dev)
				net = dev_net(skb->dev);
			अन्यथा अगर (skb->sk)
				net = sock_net(skb->sk);
		पूर्ण
	पूर्ण

	WARN_ON_ONCE(!net);
	अगर (net) अणु
		क्रमागत netns_bpf_attach_type type = NETNS_BPF_FLOW_DISSECTOR;
		काष्ठा bpf_prog_array *run_array;

		rcu_पढ़ो_lock();
		run_array = rcu_dereference(init_net.bpf.run_array[type]);
		अगर (!run_array)
			run_array = rcu_dereference(net->bpf.run_array[type]);

		अगर (run_array) अणु
			काष्ठा bpf_flow_keys flow_keys;
			काष्ठा bpf_flow_dissector ctx = अणु
				.flow_keys = &flow_keys,
				.data = data,
				.data_end = data + hlen,
			पूर्ण;
			__be16 n_proto = proto;
			काष्ठा bpf_prog *prog;

			अगर (skb) अणु
				ctx.skb = skb;
				/* we can't use 'proto' in the skb हाल
				 * because it might be set to skb->vlan_proto
				 * which has been pulled from the data
				 */
				n_proto = skb->protocol;
			पूर्ण

			prog = READ_ONCE(run_array->items[0].prog);
			ret = bpf_flow_dissect(prog, &ctx, n_proto, nhoff,
					       hlen, flags);
			__skb_flow_bpf_to_target(&flow_keys, flow_dissector,
						 target_container);
			rcu_पढ़ो_unlock();
			वापस ret;
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

	अगर (dissector_uses_key(flow_dissector,
			       FLOW_DISSECTOR_KEY_ETH_ADDRS)) अणु
		काष्ठा ethhdr *eth = eth_hdr(skb);
		काष्ठा flow_dissector_key_eth_addrs *key_eth_addrs;

		key_eth_addrs = skb_flow_dissector_target(flow_dissector,
							  FLOW_DISSECTOR_KEY_ETH_ADDRS,
							  target_container);
		स_नकल(key_eth_addrs, &eth->h_dest, माप(*key_eth_addrs));
	पूर्ण

proto_again:
	fdret = FLOW_DISSECT_RET_CONTINUE;

	चयन (proto) अणु
	हाल htons(ETH_P_IP): अणु
		स्थिर काष्ठा iphdr *iph;
		काष्ठा iphdr _iph;

		iph = __skb_header_poपूर्णांकer(skb, nhoff, माप(_iph), data, hlen, &_iph);
		अगर (!iph || iph->ihl < 5) अणु
			fdret = FLOW_DISSECT_RET_OUT_BAD;
			अवरोध;
		पूर्ण

		nhoff += iph->ihl * 4;

		ip_proto = iph->protocol;

		अगर (dissector_uses_key(flow_dissector,
				       FLOW_DISSECTOR_KEY_IPV4_ADDRS)) अणु
			key_addrs = skb_flow_dissector_target(flow_dissector,
							      FLOW_DISSECTOR_KEY_IPV4_ADDRS,
							      target_container);

			स_नकल(&key_addrs->v4addrs, &iph->saddr,
			       माप(key_addrs->v4addrs));
			key_control->addr_type = FLOW_DISSECTOR_KEY_IPV4_ADDRS;
		पूर्ण

		__skb_flow_dissect_ipv4(skb, flow_dissector,
					target_container, data, iph);

		अगर (ip_is_fragment(iph)) अणु
			key_control->flags |= FLOW_DIS_IS_FRAGMENT;

			अगर (iph->frag_off & htons(IP_OFFSET)) अणु
				fdret = FLOW_DISSECT_RET_OUT_GOOD;
				अवरोध;
			पूर्ण अन्यथा अणु
				key_control->flags |= FLOW_DIS_FIRST_FRAG;
				अगर (!(flags &
				      FLOW_DISSECTOR_F_PARSE_1ST_FRAG)) अणु
					fdret = FLOW_DISSECT_RET_OUT_GOOD;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

		अवरोध;
	पूर्ण
	हाल htons(ETH_P_IPV6): अणु
		स्थिर काष्ठा ipv6hdr *iph;
		काष्ठा ipv6hdr _iph;

		iph = __skb_header_poपूर्णांकer(skb, nhoff, माप(_iph), data, hlen, &_iph);
		अगर (!iph) अणु
			fdret = FLOW_DISSECT_RET_OUT_BAD;
			अवरोध;
		पूर्ण

		ip_proto = iph->nexthdr;
		nhoff += माप(काष्ठा ipv6hdr);

		अगर (dissector_uses_key(flow_dissector,
				       FLOW_DISSECTOR_KEY_IPV6_ADDRS)) अणु
			key_addrs = skb_flow_dissector_target(flow_dissector,
							      FLOW_DISSECTOR_KEY_IPV6_ADDRS,
							      target_container);

			स_नकल(&key_addrs->v6addrs, &iph->saddr,
			       माप(key_addrs->v6addrs));
			key_control->addr_type = FLOW_DISSECTOR_KEY_IPV6_ADDRS;
		पूर्ण

		अगर ((dissector_uses_key(flow_dissector,
					FLOW_DISSECTOR_KEY_FLOW_LABEL) ||
		     (flags & FLOW_DISSECTOR_F_STOP_AT_FLOW_LABEL)) &&
		    ip6_flowlabel(iph)) अणु
			__be32 flow_label = ip6_flowlabel(iph);

			अगर (dissector_uses_key(flow_dissector,
					       FLOW_DISSECTOR_KEY_FLOW_LABEL)) अणु
				key_tags = skb_flow_dissector_target(flow_dissector,
								     FLOW_DISSECTOR_KEY_FLOW_LABEL,
								     target_container);
				key_tags->flow_label = ntohl(flow_label);
			पूर्ण
			अगर (flags & FLOW_DISSECTOR_F_STOP_AT_FLOW_LABEL) अणु
				fdret = FLOW_DISSECT_RET_OUT_GOOD;
				अवरोध;
			पूर्ण
		पूर्ण

		__skb_flow_dissect_ipv6(skb, flow_dissector,
					target_container, data, iph);

		अवरोध;
	पूर्ण
	हाल htons(ETH_P_8021AD):
	हाल htons(ETH_P_8021Q): अणु
		स्थिर काष्ठा vlan_hdr *vlan = शून्य;
		काष्ठा vlan_hdr _vlan;
		__be16 saved_vlan_tpid = proto;

		अगर (dissector_vlan == FLOW_DISSECTOR_KEY_MAX &&
		    skb && skb_vlan_tag_present(skb)) अणु
			proto = skb->protocol;
		पूर्ण अन्यथा अणु
			vlan = __skb_header_poपूर्णांकer(skb, nhoff, माप(_vlan),
						    data, hlen, &_vlan);
			अगर (!vlan) अणु
				fdret = FLOW_DISSECT_RET_OUT_BAD;
				अवरोध;
			पूर्ण

			proto = vlan->h_vlan_encapsulated_proto;
			nhoff += माप(*vlan);
		पूर्ण

		अगर (dissector_vlan == FLOW_DISSECTOR_KEY_MAX) अणु
			dissector_vlan = FLOW_DISSECTOR_KEY_VLAN;
		पूर्ण अन्यथा अगर (dissector_vlan == FLOW_DISSECTOR_KEY_VLAN) अणु
			dissector_vlan = FLOW_DISSECTOR_KEY_CVLAN;
		पूर्ण अन्यथा अणु
			fdret = FLOW_DISSECT_RET_PROTO_AGAIN;
			अवरोध;
		पूर्ण

		अगर (dissector_uses_key(flow_dissector, dissector_vlan)) अणु
			key_vlan = skb_flow_dissector_target(flow_dissector,
							     dissector_vlan,
							     target_container);

			अगर (!vlan) अणु
				key_vlan->vlan_id = skb_vlan_tag_get_id(skb);
				key_vlan->vlan_priority = skb_vlan_tag_get_prio(skb);
			पूर्ण अन्यथा अणु
				key_vlan->vlan_id = ntohs(vlan->h_vlan_TCI) &
					VLAN_VID_MASK;
				key_vlan->vlan_priority =
					(ntohs(vlan->h_vlan_TCI) &
					 VLAN_PRIO_MASK) >> VLAN_PRIO_SHIFT;
			पूर्ण
			key_vlan->vlan_tpid = saved_vlan_tpid;
		पूर्ण

		fdret = FLOW_DISSECT_RET_PROTO_AGAIN;
		अवरोध;
	पूर्ण
	हाल htons(ETH_P_PPP_SES): अणु
		काष्ठा अणु
			काष्ठा pppoe_hdr hdr;
			__be16 proto;
		पूर्ण *hdr, _hdr;
		hdr = __skb_header_poपूर्णांकer(skb, nhoff, माप(_hdr), data, hlen, &_hdr);
		अगर (!hdr) अणु
			fdret = FLOW_DISSECT_RET_OUT_BAD;
			अवरोध;
		पूर्ण

		proto = hdr->proto;
		nhoff += PPPOE_SES_HLEN;
		चयन (proto) अणु
		हाल htons(PPP_IP):
			proto = htons(ETH_P_IP);
			fdret = FLOW_DISSECT_RET_PROTO_AGAIN;
			अवरोध;
		हाल htons(PPP_IPV6):
			proto = htons(ETH_P_IPV6);
			fdret = FLOW_DISSECT_RET_PROTO_AGAIN;
			अवरोध;
		शेष:
			fdret = FLOW_DISSECT_RET_OUT_BAD;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल htons(ETH_P_TIPC): अणु
		काष्ठा tipc_basic_hdr *hdr, _hdr;

		hdr = __skb_header_poपूर्णांकer(skb, nhoff, माप(_hdr),
					   data, hlen, &_hdr);
		अगर (!hdr) अणु
			fdret = FLOW_DISSECT_RET_OUT_BAD;
			अवरोध;
		पूर्ण

		अगर (dissector_uses_key(flow_dissector,
				       FLOW_DISSECTOR_KEY_TIPC)) अणु
			key_addrs = skb_flow_dissector_target(flow_dissector,
							      FLOW_DISSECTOR_KEY_TIPC,
							      target_container);
			key_addrs->tipckey.key = tipc_hdr_rps_key(hdr);
			key_control->addr_type = FLOW_DISSECTOR_KEY_TIPC;
		पूर्ण
		fdret = FLOW_DISSECT_RET_OUT_GOOD;
		अवरोध;
	पूर्ण

	हाल htons(ETH_P_MPLS_UC):
	हाल htons(ETH_P_MPLS_MC):
		fdret = __skb_flow_dissect_mpls(skb, flow_dissector,
						target_container, data,
						nhoff, hlen, mpls_lse,
						&mpls_el);
		nhoff += माप(काष्ठा mpls_label);
		mpls_lse++;
		अवरोध;
	हाल htons(ETH_P_FCOE):
		अगर ((hlen - nhoff) < FCOE_HEADER_LEN) अणु
			fdret = FLOW_DISSECT_RET_OUT_BAD;
			अवरोध;
		पूर्ण

		nhoff += FCOE_HEADER_LEN;
		fdret = FLOW_DISSECT_RET_OUT_GOOD;
		अवरोध;

	हाल htons(ETH_P_ARP):
	हाल htons(ETH_P_RARP):
		fdret = __skb_flow_dissect_arp(skb, flow_dissector,
					       target_container, data,
					       nhoff, hlen);
		अवरोध;

	हाल htons(ETH_P_BATMAN):
		fdret = __skb_flow_dissect_batadv(skb, key_control, data,
						  &proto, &nhoff, hlen, flags);
		अवरोध;

	हाल htons(ETH_P_1588): अणु
		काष्ठा ptp_header *hdr, _hdr;

		hdr = __skb_header_poपूर्णांकer(skb, nhoff, माप(_hdr), data,
					   hlen, &_hdr);
		अगर (!hdr) अणु
			fdret = FLOW_DISSECT_RET_OUT_BAD;
			अवरोध;
		पूर्ण

		nhoff += ntohs(hdr->message_length);
		fdret = FLOW_DISSECT_RET_OUT_GOOD;
		अवरोध;
	पूर्ण

	शेष:
		fdret = FLOW_DISSECT_RET_OUT_BAD;
		अवरोध;
	पूर्ण

	/* Process result of proto processing */
	चयन (fdret) अणु
	हाल FLOW_DISSECT_RET_OUT_GOOD:
		जाओ out_good;
	हाल FLOW_DISSECT_RET_PROTO_AGAIN:
		अगर (skb_flow_dissect_allowed(&num_hdrs))
			जाओ proto_again;
		जाओ out_good;
	हाल FLOW_DISSECT_RET_CONTINUE:
	हाल FLOW_DISSECT_RET_IPPROTO_AGAIN:
		अवरोध;
	हाल FLOW_DISSECT_RET_OUT_BAD:
	शेष:
		जाओ out_bad;
	पूर्ण

ip_proto_again:
	fdret = FLOW_DISSECT_RET_CONTINUE;

	चयन (ip_proto) अणु
	हाल IPPROTO_GRE:
		fdret = __skb_flow_dissect_gre(skb, key_control, flow_dissector,
					       target_container, data,
					       &proto, &nhoff, &hlen, flags);
		अवरोध;

	हाल NEXTHDR_HOP:
	हाल NEXTHDR_ROUTING:
	हाल NEXTHDR_DEST: अणु
		u8 _opthdr[2], *opthdr;

		अगर (proto != htons(ETH_P_IPV6))
			अवरोध;

		opthdr = __skb_header_poपूर्णांकer(skb, nhoff, माप(_opthdr),
					      data, hlen, &_opthdr);
		अगर (!opthdr) अणु
			fdret = FLOW_DISSECT_RET_OUT_BAD;
			अवरोध;
		पूर्ण

		ip_proto = opthdr[0];
		nhoff += (opthdr[1] + 1) << 3;

		fdret = FLOW_DISSECT_RET_IPPROTO_AGAIN;
		अवरोध;
	पूर्ण
	हाल NEXTHDR_FRAGMENT: अणु
		काष्ठा frag_hdr _fh, *fh;

		अगर (proto != htons(ETH_P_IPV6))
			अवरोध;

		fh = __skb_header_poपूर्णांकer(skb, nhoff, माप(_fh),
					  data, hlen, &_fh);

		अगर (!fh) अणु
			fdret = FLOW_DISSECT_RET_OUT_BAD;
			अवरोध;
		पूर्ण

		key_control->flags |= FLOW_DIS_IS_FRAGMENT;

		nhoff += माप(_fh);
		ip_proto = fh->nexthdr;

		अगर (!(fh->frag_off & htons(IP6_OFFSET))) अणु
			key_control->flags |= FLOW_DIS_FIRST_FRAG;
			अगर (flags & FLOW_DISSECTOR_F_PARSE_1ST_FRAG) अणु
				fdret = FLOW_DISSECT_RET_IPPROTO_AGAIN;
				अवरोध;
			पूर्ण
		पूर्ण

		fdret = FLOW_DISSECT_RET_OUT_GOOD;
		अवरोध;
	पूर्ण
	हाल IPPROTO_IPIP:
		proto = htons(ETH_P_IP);

		key_control->flags |= FLOW_DIS_ENCAPSULATION;
		अगर (flags & FLOW_DISSECTOR_F_STOP_AT_ENCAP) अणु
			fdret = FLOW_DISSECT_RET_OUT_GOOD;
			अवरोध;
		पूर्ण

		fdret = FLOW_DISSECT_RET_PROTO_AGAIN;
		अवरोध;

	हाल IPPROTO_IPV6:
		proto = htons(ETH_P_IPV6);

		key_control->flags |= FLOW_DIS_ENCAPSULATION;
		अगर (flags & FLOW_DISSECTOR_F_STOP_AT_ENCAP) अणु
			fdret = FLOW_DISSECT_RET_OUT_GOOD;
			अवरोध;
		पूर्ण

		fdret = FLOW_DISSECT_RET_PROTO_AGAIN;
		अवरोध;


	हाल IPPROTO_MPLS:
		proto = htons(ETH_P_MPLS_UC);
		fdret = FLOW_DISSECT_RET_PROTO_AGAIN;
		अवरोध;

	हाल IPPROTO_TCP:
		__skb_flow_dissect_tcp(skb, flow_dissector, target_container,
				       data, nhoff, hlen);
		अवरोध;

	हाल IPPROTO_ICMP:
	हाल IPPROTO_ICMPV6:
		__skb_flow_dissect_icmp(skb, flow_dissector, target_container,
					data, nhoff, hlen);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	अगर (!(key_control->flags & FLOW_DIS_IS_FRAGMENT))
		__skb_flow_dissect_ports(skb, flow_dissector, target_container,
					 data, nhoff, ip_proto, hlen);

	/* Process result of IP proto processing */
	चयन (fdret) अणु
	हाल FLOW_DISSECT_RET_PROTO_AGAIN:
		अगर (skb_flow_dissect_allowed(&num_hdrs))
			जाओ proto_again;
		अवरोध;
	हाल FLOW_DISSECT_RET_IPPROTO_AGAIN:
		अगर (skb_flow_dissect_allowed(&num_hdrs))
			जाओ ip_proto_again;
		अवरोध;
	हाल FLOW_DISSECT_RET_OUT_GOOD:
	हाल FLOW_DISSECT_RET_CONTINUE:
		अवरोध;
	हाल FLOW_DISSECT_RET_OUT_BAD:
	शेष:
		जाओ out_bad;
	पूर्ण

out_good:
	ret = true;

out:
	key_control->thoff = min_t(u16, nhoff, skb ? skb->len : hlen);
	key_basic->n_proto = proto;
	key_basic->ip_proto = ip_proto;

	वापस ret;

out_bad:
	ret = false;
	जाओ out;
पूर्ण
EXPORT_SYMBOL(__skb_flow_dissect);

अटल siphash_key_t hashrnd __पढ़ो_mostly;
अटल __always_अंतरभूत व्योम __flow_hash_secret_init(व्योम)
अणु
	net_get_अक्रमom_once(&hashrnd, माप(hashrnd));
पूर्ण

अटल स्थिर व्योम *flow_keys_hash_start(स्थिर काष्ठा flow_keys *flow)
अणु
	BUILD_BUG_ON(FLOW_KEYS_HASH_OFFSET % SIPHASH_ALIGNMENT);
	वापस &flow->FLOW_KEYS_HASH_START_FIELD;
पूर्ण

अटल अंतरभूत माप_प्रकार flow_keys_hash_length(स्थिर काष्ठा flow_keys *flow)
अणु
	माप_प्रकार dअगरf = FLOW_KEYS_HASH_OFFSET + माप(flow->addrs);

	BUILD_BUG_ON((माप(*flow) - FLOW_KEYS_HASH_OFFSET) % माप(u32));

	चयन (flow->control.addr_type) अणु
	हाल FLOW_DISSECTOR_KEY_IPV4_ADDRS:
		dअगरf -= माप(flow->addrs.v4addrs);
		अवरोध;
	हाल FLOW_DISSECTOR_KEY_IPV6_ADDRS:
		dअगरf -= माप(flow->addrs.v6addrs);
		अवरोध;
	हाल FLOW_DISSECTOR_KEY_TIPC:
		dअगरf -= माप(flow->addrs.tipckey);
		अवरोध;
	पूर्ण
	वापस माप(*flow) - dअगरf;
पूर्ण

__be32 flow_get_u32_src(स्थिर काष्ठा flow_keys *flow)
अणु
	चयन (flow->control.addr_type) अणु
	हाल FLOW_DISSECTOR_KEY_IPV4_ADDRS:
		वापस flow->addrs.v4addrs.src;
	हाल FLOW_DISSECTOR_KEY_IPV6_ADDRS:
		वापस (__क्रमce __be32)ipv6_addr_hash(
			&flow->addrs.v6addrs.src);
	हाल FLOW_DISSECTOR_KEY_TIPC:
		वापस flow->addrs.tipckey.key;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(flow_get_u32_src);

__be32 flow_get_u32_dst(स्थिर काष्ठा flow_keys *flow)
अणु
	चयन (flow->control.addr_type) अणु
	हाल FLOW_DISSECTOR_KEY_IPV4_ADDRS:
		वापस flow->addrs.v4addrs.dst;
	हाल FLOW_DISSECTOR_KEY_IPV6_ADDRS:
		वापस (__क्रमce __be32)ipv6_addr_hash(
			&flow->addrs.v6addrs.dst);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(flow_get_u32_dst);

/* Sort the source and destination IP (and the ports अगर the IP are the same),
 * to have consistent hash within the two directions
 */
अटल अंतरभूत व्योम __flow_hash_consistentअगरy(काष्ठा flow_keys *keys)
अणु
	पूर्णांक addr_dअगरf, i;

	चयन (keys->control.addr_type) अणु
	हाल FLOW_DISSECTOR_KEY_IPV4_ADDRS:
		addr_dअगरf = (__क्रमce u32)keys->addrs.v4addrs.dst -
			    (__क्रमce u32)keys->addrs.v4addrs.src;
		अगर ((addr_dअगरf < 0) ||
		    (addr_dअगरf == 0 &&
		     ((__क्रमce u16)keys->ports.dst <
		      (__क्रमce u16)keys->ports.src))) अणु
			swap(keys->addrs.v4addrs.src, keys->addrs.v4addrs.dst);
			swap(keys->ports.src, keys->ports.dst);
		पूर्ण
		अवरोध;
	हाल FLOW_DISSECTOR_KEY_IPV6_ADDRS:
		addr_dअगरf = स_भेद(&keys->addrs.v6addrs.dst,
				   &keys->addrs.v6addrs.src,
				   माप(keys->addrs.v6addrs.dst));
		अगर ((addr_dअगरf < 0) ||
		    (addr_dअगरf == 0 &&
		     ((__क्रमce u16)keys->ports.dst <
		      (__क्रमce u16)keys->ports.src))) अणु
			क्रम (i = 0; i < 4; i++)
				swap(keys->addrs.v6addrs.src.s6_addr32[i],
				     keys->addrs.v6addrs.dst.s6_addr32[i]);
			swap(keys->ports.src, keys->ports.dst);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत u32 __flow_hash_from_keys(काष्ठा flow_keys *keys,
					स्थिर siphash_key_t *keyval)
अणु
	u32 hash;

	__flow_hash_consistentअगरy(keys);

	hash = siphash(flow_keys_hash_start(keys),
		       flow_keys_hash_length(keys), keyval);
	अगर (!hash)
		hash = 1;

	वापस hash;
पूर्ण

u32 flow_hash_from_keys(काष्ठा flow_keys *keys)
अणु
	__flow_hash_secret_init();
	वापस __flow_hash_from_keys(keys, &hashrnd);
पूर्ण
EXPORT_SYMBOL(flow_hash_from_keys);

अटल अंतरभूत u32 ___skb_get_hash(स्थिर काष्ठा sk_buff *skb,
				  काष्ठा flow_keys *keys,
				  स्थिर siphash_key_t *keyval)
अणु
	skb_flow_dissect_flow_keys(skb, keys,
				   FLOW_DISSECTOR_F_STOP_AT_FLOW_LABEL);

	वापस __flow_hash_from_keys(keys, keyval);
पूर्ण

काष्ठा _flow_keys_digest_data अणु
	__be16	n_proto;
	u8	ip_proto;
	u8	padding;
	__be32	ports;
	__be32	src;
	__be32	dst;
पूर्ण;

व्योम make_flow_keys_digest(काष्ठा flow_keys_digest *digest,
			   स्थिर काष्ठा flow_keys *flow)
अणु
	काष्ठा _flow_keys_digest_data *data =
	    (काष्ठा _flow_keys_digest_data *)digest;

	BUILD_BUG_ON(माप(*data) > माप(*digest));

	स_रखो(digest, 0, माप(*digest));

	data->n_proto = flow->basic.n_proto;
	data->ip_proto = flow->basic.ip_proto;
	data->ports = flow->ports.ports;
	data->src = flow->addrs.v4addrs.src;
	data->dst = flow->addrs.v4addrs.dst;
पूर्ण
EXPORT_SYMBOL(make_flow_keys_digest);

अटल काष्ठा flow_dissector flow_keys_dissector_symmetric __पढ़ो_mostly;

u32 __skb_get_hash_symmetric(स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा flow_keys keys;

	__flow_hash_secret_init();

	स_रखो(&keys, 0, माप(keys));
	__skb_flow_dissect(शून्य, skb, &flow_keys_dissector_symmetric,
			   &keys, शून्य, 0, 0, 0,
			   FLOW_DISSECTOR_F_STOP_AT_FLOW_LABEL);

	वापस __flow_hash_from_keys(&keys, &hashrnd);
पूर्ण
EXPORT_SYMBOL_GPL(__skb_get_hash_symmetric);

/**
 * __skb_get_hash: calculate a flow hash
 * @skb: sk_buff to calculate flow hash from
 *
 * This function calculates a flow hash based on src/dst addresses
 * and src/dst port numbers.  Sets hash in skb to non-zero hash value
 * on success, zero indicates no valid hash.  Also, sets l4_hash in skb
 * अगर hash is a canonical 4-tuple hash over transport ports.
 */
व्योम __skb_get_hash(काष्ठा sk_buff *skb)
अणु
	काष्ठा flow_keys keys;
	u32 hash;

	__flow_hash_secret_init();

	hash = ___skb_get_hash(skb, &keys, &hashrnd);

	__skb_set_sw_hash(skb, hash, flow_keys_have_l4(&keys));
पूर्ण
EXPORT_SYMBOL(__skb_get_hash);

__u32 skb_get_hash_perturb(स्थिर काष्ठा sk_buff *skb,
			   स्थिर siphash_key_t *perturb)
अणु
	काष्ठा flow_keys keys;

	वापस ___skb_get_hash(skb, &keys, perturb);
पूर्ण
EXPORT_SYMBOL(skb_get_hash_perturb);

u32 __skb_get_poff(स्थिर काष्ठा sk_buff *skb, स्थिर व्योम *data,
		   स्थिर काष्ठा flow_keys_basic *keys, पूर्णांक hlen)
अणु
	u32 poff = keys->control.thoff;

	/* skip L4 headers क्रम fragments after the first */
	अगर ((keys->control.flags & FLOW_DIS_IS_FRAGMENT) &&
	    !(keys->control.flags & FLOW_DIS_FIRST_FRAG))
		वापस poff;

	चयन (keys->basic.ip_proto) अणु
	हाल IPPROTO_TCP: अणु
		/* access करोff as u8 to aव्योम unaligned access */
		स्थिर u8 *करोff;
		u8 _करोff;

		करोff = __skb_header_poपूर्णांकer(skb, poff + 12, माप(_करोff),
					    data, hlen, &_करोff);
		अगर (!करोff)
			वापस poff;

		poff += max_t(u32, माप(काष्ठा tcphdr), (*करोff & 0xF0) >> 2);
		अवरोध;
	पूर्ण
	हाल IPPROTO_UDP:
	हाल IPPROTO_UDPLITE:
		poff += माप(काष्ठा udphdr);
		अवरोध;
	/* For the rest, we करो not really care about header
	 * extensions at this poपूर्णांक क्रम now.
	 */
	हाल IPPROTO_ICMP:
		poff += माप(काष्ठा icmphdr);
		अवरोध;
	हाल IPPROTO_ICMPV6:
		poff += माप(काष्ठा icmp6hdr);
		अवरोध;
	हाल IPPROTO_IGMP:
		poff += माप(काष्ठा igmphdr);
		अवरोध;
	हाल IPPROTO_DCCP:
		poff += माप(काष्ठा dccp_hdr);
		अवरोध;
	हाल IPPROTO_SCTP:
		poff += माप(काष्ठा sctphdr);
		अवरोध;
	पूर्ण

	वापस poff;
पूर्ण

/**
 * skb_get_poff - get the offset to the payload
 * @skb: sk_buff to get the payload offset from
 *
 * The function will get the offset to the payload as far as it could
 * be dissected.  The मुख्य user is currently BPF, so that we can dynamically
 * truncate packets without needing to push actual payload to the user
 * space and can analyze headers only, instead.
 */
u32 skb_get_poff(स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा flow_keys_basic keys;

	अगर (!skb_flow_dissect_flow_keys_basic(शून्य, skb, &keys,
					      शून्य, 0, 0, 0, 0))
		वापस 0;

	वापस __skb_get_poff(skb, skb->data, &keys, skb_headlen(skb));
पूर्ण

__u32 __get_hash_from_flowi6(स्थिर काष्ठा flowi6 *fl6, काष्ठा flow_keys *keys)
अणु
	स_रखो(keys, 0, माप(*keys));

	स_नकल(&keys->addrs.v6addrs.src, &fl6->saddr,
	    माप(keys->addrs.v6addrs.src));
	स_नकल(&keys->addrs.v6addrs.dst, &fl6->daddr,
	    माप(keys->addrs.v6addrs.dst));
	keys->control.addr_type = FLOW_DISSECTOR_KEY_IPV6_ADDRS;
	keys->ports.src = fl6->fl6_sport;
	keys->ports.dst = fl6->fl6_dport;
	keys->keyid.keyid = fl6->fl6_gre_key;
	keys->tags.flow_label = (__क्रमce u32)flowi6_get_flowlabel(fl6);
	keys->basic.ip_proto = fl6->flowi6_proto;

	वापस flow_hash_from_keys(keys);
पूर्ण
EXPORT_SYMBOL(__get_hash_from_flowi6);

अटल स्थिर काष्ठा flow_dissector_key flow_keys_dissector_keys[] = अणु
	अणु
		.key_id = FLOW_DISSECTOR_KEY_CONTROL,
		.offset = दुरत्व(काष्ठा flow_keys, control),
	पूर्ण,
	अणु
		.key_id = FLOW_DISSECTOR_KEY_BASIC,
		.offset = दुरत्व(काष्ठा flow_keys, basic),
	पूर्ण,
	अणु
		.key_id = FLOW_DISSECTOR_KEY_IPV4_ADDRS,
		.offset = दुरत्व(काष्ठा flow_keys, addrs.v4addrs),
	पूर्ण,
	अणु
		.key_id = FLOW_DISSECTOR_KEY_IPV6_ADDRS,
		.offset = दुरत्व(काष्ठा flow_keys, addrs.v6addrs),
	पूर्ण,
	अणु
		.key_id = FLOW_DISSECTOR_KEY_TIPC,
		.offset = दुरत्व(काष्ठा flow_keys, addrs.tipckey),
	पूर्ण,
	अणु
		.key_id = FLOW_DISSECTOR_KEY_PORTS,
		.offset = दुरत्व(काष्ठा flow_keys, ports),
	पूर्ण,
	अणु
		.key_id = FLOW_DISSECTOR_KEY_VLAN,
		.offset = दुरत्व(काष्ठा flow_keys, vlan),
	पूर्ण,
	अणु
		.key_id = FLOW_DISSECTOR_KEY_FLOW_LABEL,
		.offset = दुरत्व(काष्ठा flow_keys, tags),
	पूर्ण,
	अणु
		.key_id = FLOW_DISSECTOR_KEY_GRE_KEYID,
		.offset = दुरत्व(काष्ठा flow_keys, keyid),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा flow_dissector_key flow_keys_dissector_symmetric_keys[] = अणु
	अणु
		.key_id = FLOW_DISSECTOR_KEY_CONTROL,
		.offset = दुरत्व(काष्ठा flow_keys, control),
	पूर्ण,
	अणु
		.key_id = FLOW_DISSECTOR_KEY_BASIC,
		.offset = दुरत्व(काष्ठा flow_keys, basic),
	पूर्ण,
	अणु
		.key_id = FLOW_DISSECTOR_KEY_IPV4_ADDRS,
		.offset = दुरत्व(काष्ठा flow_keys, addrs.v4addrs),
	पूर्ण,
	अणु
		.key_id = FLOW_DISSECTOR_KEY_IPV6_ADDRS,
		.offset = दुरत्व(काष्ठा flow_keys, addrs.v6addrs),
	पूर्ण,
	अणु
		.key_id = FLOW_DISSECTOR_KEY_PORTS,
		.offset = दुरत्व(काष्ठा flow_keys, ports),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा flow_dissector_key flow_keys_basic_dissector_keys[] = अणु
	अणु
		.key_id = FLOW_DISSECTOR_KEY_CONTROL,
		.offset = दुरत्व(काष्ठा flow_keys, control),
	पूर्ण,
	अणु
		.key_id = FLOW_DISSECTOR_KEY_BASIC,
		.offset = दुरत्व(काष्ठा flow_keys, basic),
	पूर्ण,
पूर्ण;

काष्ठा flow_dissector flow_keys_dissector __पढ़ो_mostly;
EXPORT_SYMBOL(flow_keys_dissector);

काष्ठा flow_dissector flow_keys_basic_dissector __पढ़ो_mostly;
EXPORT_SYMBOL(flow_keys_basic_dissector);

अटल पूर्णांक __init init_शेष_flow_dissectors(व्योम)
अणु
	skb_flow_dissector_init(&flow_keys_dissector,
				flow_keys_dissector_keys,
				ARRAY_SIZE(flow_keys_dissector_keys));
	skb_flow_dissector_init(&flow_keys_dissector_symmetric,
				flow_keys_dissector_symmetric_keys,
				ARRAY_SIZE(flow_keys_dissector_symmetric_keys));
	skb_flow_dissector_init(&flow_keys_basic_dissector,
				flow_keys_basic_dissector_keys,
				ARRAY_SIZE(flow_keys_basic_dissector_keys));
	वापस 0;
पूर्ण
core_initcall(init_शेष_flow_dissectors);
