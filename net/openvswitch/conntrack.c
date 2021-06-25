<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015 Nicira, Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/खोलोvचयन.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/sctp.h>
#समावेश <linux/अटल_key.h>
#समावेश <net/ip.h>
#समावेश <net/genetlink.h>
#समावेश <net/netfilter/nf_conntrack_core.h>
#समावेश <net/netfilter/nf_conntrack_count.h>
#समावेश <net/netfilter/nf_conntrack_helper.h>
#समावेश <net/netfilter/nf_conntrack_labels.h>
#समावेश <net/netfilter/nf_conntrack_seqadj.h>
#समावेश <net/netfilter/nf_conntrack_समयout.h>
#समावेश <net/netfilter/nf_conntrack_zones.h>
#समावेश <net/netfilter/ipv6/nf_defrag_ipv6.h>
#समावेश <net/ipv6_frag.h>

#अगर IS_ENABLED(CONFIG_NF_NAT)
#समावेश <net/netfilter/nf_nat.h>
#पूर्ण_अगर

#समावेश "datapath.h"
#समावेश "conntrack.h"
#समावेश "flow.h"
#समावेश "flow_netlink.h"

काष्ठा ovs_ct_len_tbl अणु
	पूर्णांक maxlen;
	पूर्णांक minlen;
पूर्ण;

/* Metadata mark क्रम masked ग_लिखो to conntrack mark */
काष्ठा md_mark अणु
	u32 value;
	u32 mask;
पूर्ण;

/* Metadata label क्रम masked ग_लिखो to conntrack label. */
काष्ठा md_labels अणु
	काष्ठा ovs_key_ct_labels value;
	काष्ठा ovs_key_ct_labels mask;
पूर्ण;

क्रमागत ovs_ct_nat अणु
	OVS_CT_NAT = 1 << 0,     /* NAT क्रम committed connections only. */
	OVS_CT_SRC_NAT = 1 << 1, /* Source NAT क्रम NEW connections. */
	OVS_CT_DST_NAT = 1 << 2, /* Destination NAT क्रम NEW connections. */
पूर्ण;

/* Conntrack action context क्रम execution. */
काष्ठा ovs_conntrack_info अणु
	काष्ठा nf_conntrack_helper *helper;
	काष्ठा nf_conntrack_zone zone;
	काष्ठा nf_conn *ct;
	u8 commit : 1;
	u8 nat : 3;                 /* क्रमागत ovs_ct_nat */
	u8 क्रमce : 1;
	u8 have_evenपंचांगask : 1;
	u16 family;
	u32 evenपंचांगask;              /* Mask of 1 << IPCT_*. */
	काष्ठा md_mark mark;
	काष्ठा md_labels labels;
	अक्षर समयout[CTNL_TIMEOUT_NAME_MAX];
	काष्ठा nf_ct_समयout *nf_ct_समयout;
#अगर IS_ENABLED(CONFIG_NF_NAT)
	काष्ठा nf_nat_range2 range;  /* Only present क्रम SRC NAT and DST NAT. */
#पूर्ण_अगर
पूर्ण;

#अगर	IS_ENABLED(CONFIG_NETFILTER_CONNCOUNT)
#घोषणा OVS_CT_LIMIT_UNLIMITED	0
#घोषणा OVS_CT_LIMIT_DEFAULT OVS_CT_LIMIT_UNLIMITED
#घोषणा CT_LIMIT_HASH_BUCKETS 512
अटल DEFINE_STATIC_KEY_FALSE(ovs_ct_limit_enabled);

काष्ठा ovs_ct_limit अणु
	/* Elements in ovs_ct_limit_info->limits hash table */
	काष्ठा hlist_node hlist_node;
	काष्ठा rcu_head rcu;
	u16 zone;
	u32 limit;
पूर्ण;

काष्ठा ovs_ct_limit_info अणु
	u32 शेष_limit;
	काष्ठा hlist_head *limits;
	काष्ठा nf_conncount_data *data;
पूर्ण;

अटल स्थिर काष्ठा nla_policy ct_limit_policy[OVS_CT_LIMIT_ATTR_MAX + 1] = अणु
	[OVS_CT_LIMIT_ATTR_ZONE_LIMIT] = अणु .type = NLA_NESTED, पूर्ण,
पूर्ण;
#पूर्ण_अगर

अटल bool labels_nonzero(स्थिर काष्ठा ovs_key_ct_labels *labels);

अटल व्योम __ovs_ct_मुक्त_action(काष्ठा ovs_conntrack_info *ct_info);

अटल u16 key_to_nfproto(स्थिर काष्ठा sw_flow_key *key)
अणु
	चयन (ntohs(key->eth.type)) अणु
	हाल ETH_P_IP:
		वापस NFPROTO_IPV4;
	हाल ETH_P_IPV6:
		वापस NFPROTO_IPV6;
	शेष:
		वापस NFPROTO_UNSPEC;
	पूर्ण
पूर्ण

/* Map SKB connection state पूर्णांकo the values used by flow definition. */
अटल u8 ovs_ct_get_state(क्रमागत ip_conntrack_info ctinfo)
अणु
	u8 ct_state = OVS_CS_F_TRACKED;

	चयन (ctinfo) अणु
	हाल IP_CT_ESTABLISHED_REPLY:
	हाल IP_CT_RELATED_REPLY:
		ct_state |= OVS_CS_F_REPLY_सूची;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	चयन (ctinfo) अणु
	हाल IP_CT_ESTABLISHED:
	हाल IP_CT_ESTABLISHED_REPLY:
		ct_state |= OVS_CS_F_ESTABLISHED;
		अवरोध;
	हाल IP_CT_RELATED:
	हाल IP_CT_RELATED_REPLY:
		ct_state |= OVS_CS_F_RELATED;
		अवरोध;
	हाल IP_CT_NEW:
		ct_state |= OVS_CS_F_NEW;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ct_state;
पूर्ण

अटल u32 ovs_ct_get_mark(स्थिर काष्ठा nf_conn *ct)
अणु
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK_MARK)
	वापस ct ? ct->mark : 0;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

/* Guard against conntrack labels max size shrinking below 128 bits. */
#अगर NF_CT_LABELS_MAX_SIZE < 16
#त्रुटि NF_CT_LABELS_MAX_SIZE must be at least 16 bytes
#पूर्ण_अगर

अटल व्योम ovs_ct_get_labels(स्थिर काष्ठा nf_conn *ct,
			      काष्ठा ovs_key_ct_labels *labels)
अणु
	काष्ठा nf_conn_labels *cl = ct ? nf_ct_labels_find(ct) : शून्य;

	अगर (cl)
		स_नकल(labels, cl->bits, OVS_CT_LABELS_LEN);
	अन्यथा
		स_रखो(labels, 0, OVS_CT_LABELS_LEN);
पूर्ण

अटल व्योम __ovs_ct_update_key_orig_tp(काष्ठा sw_flow_key *key,
					स्थिर काष्ठा nf_conntrack_tuple *orig,
					u8 icmp_proto)
अणु
	key->ct_orig_proto = orig->dst.protonum;
	अगर (orig->dst.protonum == icmp_proto) अणु
		key->ct.orig_tp.src = htons(orig->dst.u.icmp.type);
		key->ct.orig_tp.dst = htons(orig->dst.u.icmp.code);
	पूर्ण अन्यथा अणु
		key->ct.orig_tp.src = orig->src.u.all;
		key->ct.orig_tp.dst = orig->dst.u.all;
	पूर्ण
पूर्ण

अटल व्योम __ovs_ct_update_key(काष्ठा sw_flow_key *key, u8 state,
				स्थिर काष्ठा nf_conntrack_zone *zone,
				स्थिर काष्ठा nf_conn *ct)
अणु
	key->ct_state = state;
	key->ct_zone = zone->id;
	key->ct.mark = ovs_ct_get_mark(ct);
	ovs_ct_get_labels(ct, &key->ct.labels);

	अगर (ct) अणु
		स्थिर काष्ठा nf_conntrack_tuple *orig;

		/* Use the master अगर we have one. */
		अगर (ct->master)
			ct = ct->master;
		orig = &ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple;

		/* IP version must match with the master connection. */
		अगर (key->eth.type == htons(ETH_P_IP) &&
		    nf_ct_l3num(ct) == NFPROTO_IPV4) अणु
			key->ipv4.ct_orig.src = orig->src.u3.ip;
			key->ipv4.ct_orig.dst = orig->dst.u3.ip;
			__ovs_ct_update_key_orig_tp(key, orig, IPPROTO_ICMP);
			वापस;
		पूर्ण अन्यथा अगर (key->eth.type == htons(ETH_P_IPV6) &&
			   !sw_flow_key_is_nd(key) &&
			   nf_ct_l3num(ct) == NFPROTO_IPV6) अणु
			key->ipv6.ct_orig.src = orig->src.u3.in6;
			key->ipv6.ct_orig.dst = orig->dst.u3.in6;
			__ovs_ct_update_key_orig_tp(key, orig, NEXTHDR_ICMP);
			वापस;
		पूर्ण
	पूर्ण
	/* Clear 'ct_orig_proto' to mark the non-existence of conntrack
	 * original direction key fields.
	 */
	key->ct_orig_proto = 0;
पूर्ण

/* Update 'key' based on skb->_nfct.  If 'post_ct' is true, then OVS has
 * previously sent the packet to conntrack via the ct action.  If
 * 'keep_nat_flags' is true, the existing NAT flags retained, अन्यथा they are
 * initialized from the connection status.
 */
अटल व्योम ovs_ct_update_key(स्थिर काष्ठा sk_buff *skb,
			      स्थिर काष्ठा ovs_conntrack_info *info,
			      काष्ठा sw_flow_key *key, bool post_ct,
			      bool keep_nat_flags)
अणु
	स्थिर काष्ठा nf_conntrack_zone *zone = &nf_ct_zone_dflt;
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct;
	u8 state = 0;

	ct = nf_ct_get(skb, &ctinfo);
	अगर (ct) अणु
		state = ovs_ct_get_state(ctinfo);
		/* All unconfirmed entries are NEW connections. */
		अगर (!nf_ct_is_confirmed(ct))
			state |= OVS_CS_F_NEW;
		/* OVS persists the related flag क्रम the duration of the
		 * connection.
		 */
		अगर (ct->master)
			state |= OVS_CS_F_RELATED;
		अगर (keep_nat_flags) अणु
			state |= key->ct_state & OVS_CS_F_NAT_MASK;
		पूर्ण अन्यथा अणु
			अगर (ct->status & IPS_SRC_NAT)
				state |= OVS_CS_F_SRC_NAT;
			अगर (ct->status & IPS_DST_NAT)
				state |= OVS_CS_F_DST_NAT;
		पूर्ण
		zone = nf_ct_zone(ct);
	पूर्ण अन्यथा अगर (post_ct) अणु
		state = OVS_CS_F_TRACKED | OVS_CS_F_INVALID;
		अगर (info)
			zone = &info->zone;
	पूर्ण
	__ovs_ct_update_key(key, state, zone, ct);
पूर्ण

/* This is called to initialize CT key fields possibly coming in from the local
 * stack.
 */
व्योम ovs_ct_fill_key(स्थिर काष्ठा sk_buff *skb,
		     काष्ठा sw_flow_key *key,
		     bool post_ct)
अणु
	ovs_ct_update_key(skb, शून्य, key, post_ct, false);
पूर्ण

पूर्णांक ovs_ct_put_key(स्थिर काष्ठा sw_flow_key *swkey,
		   स्थिर काष्ठा sw_flow_key *output, काष्ठा sk_buff *skb)
अणु
	अगर (nla_put_u32(skb, OVS_KEY_ATTR_CT_STATE, output->ct_state))
		वापस -EMSGSIZE;

	अगर (IS_ENABLED(CONFIG_NF_CONNTRACK_ZONES) &&
	    nla_put_u16(skb, OVS_KEY_ATTR_CT_ZONE, output->ct_zone))
		वापस -EMSGSIZE;

	अगर (IS_ENABLED(CONFIG_NF_CONNTRACK_MARK) &&
	    nla_put_u32(skb, OVS_KEY_ATTR_CT_MARK, output->ct.mark))
		वापस -EMSGSIZE;

	अगर (IS_ENABLED(CONFIG_NF_CONNTRACK_LABELS) &&
	    nla_put(skb, OVS_KEY_ATTR_CT_LABELS, माप(output->ct.labels),
		    &output->ct.labels))
		वापस -EMSGSIZE;

	अगर (swkey->ct_orig_proto) अणु
		अगर (swkey->eth.type == htons(ETH_P_IP)) अणु
			काष्ठा ovs_key_ct_tuple_ipv4 orig;

			स_रखो(&orig, 0, माप(orig));
			orig.ipv4_src = output->ipv4.ct_orig.src;
			orig.ipv4_dst = output->ipv4.ct_orig.dst;
			orig.src_port = output->ct.orig_tp.src;
			orig.dst_port = output->ct.orig_tp.dst;
			orig.ipv4_proto = output->ct_orig_proto;

			अगर (nla_put(skb, OVS_KEY_ATTR_CT_ORIG_TUPLE_IPV4,
				    माप(orig), &orig))
				वापस -EMSGSIZE;
		पूर्ण अन्यथा अगर (swkey->eth.type == htons(ETH_P_IPV6)) अणु
			काष्ठा ovs_key_ct_tuple_ipv6 orig;

			स_रखो(&orig, 0, माप(orig));
			स_नकल(orig.ipv6_src, output->ipv6.ct_orig.src.s6_addr32,
			       माप(orig.ipv6_src));
			स_नकल(orig.ipv6_dst, output->ipv6.ct_orig.dst.s6_addr32,
			       माप(orig.ipv6_dst));
			orig.src_port = output->ct.orig_tp.src;
			orig.dst_port = output->ct.orig_tp.dst;
			orig.ipv6_proto = output->ct_orig_proto;

			अगर (nla_put(skb, OVS_KEY_ATTR_CT_ORIG_TUPLE_IPV6,
				    माप(orig), &orig))
				वापस -EMSGSIZE;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ovs_ct_set_mark(काष्ठा nf_conn *ct, काष्ठा sw_flow_key *key,
			   u32 ct_mark, u32 mask)
अणु
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK_MARK)
	u32 new_mark;

	new_mark = ct_mark | (ct->mark & ~(mask));
	अगर (ct->mark != new_mark) अणु
		ct->mark = new_mark;
		अगर (nf_ct_is_confirmed(ct))
			nf_conntrack_event_cache(IPCT_MARK, ct);
		key->ct.mark = new_mark;
	पूर्ण

	वापस 0;
#अन्यथा
	वापस -ENOTSUPP;
#पूर्ण_अगर
पूर्ण

अटल काष्ठा nf_conn_labels *ovs_ct_get_conn_labels(काष्ठा nf_conn *ct)
अणु
	काष्ठा nf_conn_labels *cl;

	cl = nf_ct_labels_find(ct);
	अगर (!cl) अणु
		nf_ct_labels_ext_add(ct);
		cl = nf_ct_labels_find(ct);
	पूर्ण

	वापस cl;
पूर्ण

/* Initialize labels क्रम a new, yet to be committed conntrack entry.  Note that
 * since the new connection is not yet confirmed, and thus no-one अन्यथा has
 * access to it's labels, we simply ग_लिखो them over.
 */
अटल पूर्णांक ovs_ct_init_labels(काष्ठा nf_conn *ct, काष्ठा sw_flow_key *key,
			      स्थिर काष्ठा ovs_key_ct_labels *labels,
			      स्थिर काष्ठा ovs_key_ct_labels *mask)
अणु
	काष्ठा nf_conn_labels *cl, *master_cl;
	bool have_mask = labels_nonzero(mask);

	/* Inherit master's labels to the related connection? */
	master_cl = ct->master ? nf_ct_labels_find(ct->master) : शून्य;

	अगर (!master_cl && !have_mask)
		वापस 0;   /* Nothing to करो. */

	cl = ovs_ct_get_conn_labels(ct);
	अगर (!cl)
		वापस -ENOSPC;

	/* Inherit the master's labels, अगर any. */
	अगर (master_cl)
		*cl = *master_cl;

	अगर (have_mask) अणु
		u32 *dst = (u32 *)cl->bits;
		पूर्णांक i;

		क्रम (i = 0; i < OVS_CT_LABELS_LEN_32; i++)
			dst[i] = (dst[i] & ~mask->ct_labels_32[i]) |
				(labels->ct_labels_32[i]
				 & mask->ct_labels_32[i]);
	पूर्ण

	/* Labels are included in the IPCTNL_MSG_CT_NEW event only अगर the
	 * IPCT_LABEL bit is set in the event cache.
	 */
	nf_conntrack_event_cache(IPCT_LABEL, ct);

	स_नकल(&key->ct.labels, cl->bits, OVS_CT_LABELS_LEN);

	वापस 0;
पूर्ण

अटल पूर्णांक ovs_ct_set_labels(काष्ठा nf_conn *ct, काष्ठा sw_flow_key *key,
			     स्थिर काष्ठा ovs_key_ct_labels *labels,
			     स्थिर काष्ठा ovs_key_ct_labels *mask)
अणु
	काष्ठा nf_conn_labels *cl;
	पूर्णांक err;

	cl = ovs_ct_get_conn_labels(ct);
	अगर (!cl)
		वापस -ENOSPC;

	err = nf_connlabels_replace(ct, labels->ct_labels_32,
				    mask->ct_labels_32,
				    OVS_CT_LABELS_LEN_32);
	अगर (err)
		वापस err;

	स_नकल(&key->ct.labels, cl->bits, OVS_CT_LABELS_LEN);

	वापस 0;
पूर्ण

/* 'skb' should alपढ़ोy be pulled to nh_ofs. */
अटल पूर्णांक ovs_ct_helper(काष्ठा sk_buff *skb, u16 proto)
अणु
	स्थिर काष्ठा nf_conntrack_helper *helper;
	स्थिर काष्ठा nf_conn_help *help;
	क्रमागत ip_conntrack_info ctinfo;
	अचिन्हित पूर्णांक protoff;
	काष्ठा nf_conn *ct;
	पूर्णांक err;

	ct = nf_ct_get(skb, &ctinfo);
	अगर (!ct || ctinfo == IP_CT_RELATED_REPLY)
		वापस NF_ACCEPT;

	help = nfct_help(ct);
	अगर (!help)
		वापस NF_ACCEPT;

	helper = rcu_dereference(help->helper);
	अगर (!helper)
		वापस NF_ACCEPT;

	चयन (proto) अणु
	हाल NFPROTO_IPV4:
		protoff = ip_hdrlen(skb);
		अवरोध;
	हाल NFPROTO_IPV6: अणु
		u8 nexthdr = ipv6_hdr(skb)->nexthdr;
		__be16 frag_off;
		पूर्णांक ofs;

		ofs = ipv6_skip_exthdr(skb, माप(काष्ठा ipv6hdr), &nexthdr,
				       &frag_off);
		अगर (ofs < 0 || (frag_off & htons(~0x7)) != 0) अणु
			pr_debug("proto header not found\n");
			वापस NF_ACCEPT;
		पूर्ण
		protoff = ofs;
		अवरोध;
	पूर्ण
	शेष:
		WARN_ONCE(1, "helper invoked on non-IP family!");
		वापस NF_DROP;
	पूर्ण

	err = helper->help(skb, protoff, ct, ctinfo);
	अगर (err != NF_ACCEPT)
		वापस err;

	/* Adjust seqs after helper.  This is needed due to some helpers (e.g.,
	 * FTP with NAT) adusting the TCP payload size when mangling IP
	 * addresses and/or port numbers in the text-based control connection.
	 */
	अगर (test_bit(IPS_SEQ_ADJUST_BIT, &ct->status) &&
	    !nf_ct_seq_adjust(skb, ct, ctinfo, protoff))
		वापस NF_DROP;
	वापस NF_ACCEPT;
पूर्ण

/* Returns 0 on success, -EINPROGRESS अगर 'skb' is stolen, or other nonzero
 * value अगर 'skb' is मुक्तd.
 */
अटल पूर्णांक handle_fragments(काष्ठा net *net, काष्ठा sw_flow_key *key,
			    u16 zone, काष्ठा sk_buff *skb)
अणु
	काष्ठा ovs_skb_cb ovs_cb = *OVS_CB(skb);
	पूर्णांक err;

	अगर (key->eth.type == htons(ETH_P_IP)) अणु
		क्रमागत ip_defrag_users user = IP_DEFRAG_CONNTRACK_IN + zone;

		स_रखो(IPCB(skb), 0, माप(काष्ठा inet_skb_parm));
		err = ip_defrag(net, skb, user);
		अगर (err)
			वापस err;

		ovs_cb.mru = IPCB(skb)->frag_max_size;
#अगर IS_ENABLED(CONFIG_NF_DEFRAG_IPV6)
	पूर्ण अन्यथा अगर (key->eth.type == htons(ETH_P_IPV6)) अणु
		क्रमागत ip6_defrag_users user = IP6_DEFRAG_CONNTRACK_IN + zone;

		स_रखो(IP6CB(skb), 0, माप(काष्ठा inet6_skb_parm));
		err = nf_ct_frag6_gather(net, skb, user);
		अगर (err) अणु
			अगर (err != -EINPROGRESS)
				kमुक्त_skb(skb);
			वापस err;
		पूर्ण

		key->ip.proto = ipv6_hdr(skb)->nexthdr;
		ovs_cb.mru = IP6CB(skb)->frag_max_size;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		kमुक्त_skb(skb);
		वापस -EPFNOSUPPORT;
	पूर्ण

	/* The key extracted from the fragment that completed this datagram
	 * likely didn't have an L4 header, so regenerate it.
	 */
	ovs_flow_key_update_l3l4(skb, key);

	key->ip.frag = OVS_FRAG_TYPE_NONE;
	skb_clear_hash(skb);
	skb->ignore_df = 1;
	*OVS_CB(skb) = ovs_cb;

	वापस 0;
पूर्ण

अटल काष्ठा nf_conntrack_expect *
ovs_ct_expect_find(काष्ठा net *net, स्थिर काष्ठा nf_conntrack_zone *zone,
		   u16 proto, स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा nf_conntrack_tuple tuple;
	काष्ठा nf_conntrack_expect *exp;

	अगर (!nf_ct_get_tuplepr(skb, skb_network_offset(skb), proto, net, &tuple))
		वापस शून्य;

	exp = __nf_ct_expect_find(net, zone, &tuple);
	अगर (exp) अणु
		काष्ठा nf_conntrack_tuple_hash *h;

		/* Delete existing conntrack entry, अगर it clashes with the
		 * expectation.  This can happen since conntrack ALGs करो not
		 * check क्रम clashes between (new) expectations and existing
		 * conntrack entries.  nf_conntrack_in() will check the
		 * expectations only अगर a conntrack entry can not be found,
		 * which can lead to OVS finding the expectation (here) in the
		 * init direction, but which will not be हटाओd by the
		 * nf_conntrack_in() call, अगर a matching conntrack entry is
		 * found instead.  In this हाल all init direction packets
		 * would be reported as new related packets, जबतक reply
		 * direction packets would be reported as un-related
		 * established packets.
		 */
		h = nf_conntrack_find_get(net, zone, &tuple);
		अगर (h) अणु
			काष्ठा nf_conn *ct = nf_ct_tuplehash_to_ctrack(h);

			nf_ct_delete(ct, 0, 0);
			nf_conntrack_put(&ct->ct_general);
		पूर्ण
	पूर्ण

	वापस exp;
पूर्ण

/* This replicates logic from nf_conntrack_core.c that is not exported. */
अटल क्रमागत ip_conntrack_info
ovs_ct_get_info(स्थिर काष्ठा nf_conntrack_tuple_hash *h)
अणु
	स्थिर काष्ठा nf_conn *ct = nf_ct_tuplehash_to_ctrack(h);

	अगर (NF_CT_सूचीECTION(h) == IP_CT_सूची_REPLY)
		वापस IP_CT_ESTABLISHED_REPLY;
	/* Once we've had two way comms, always ESTABLISHED. */
	अगर (test_bit(IPS_SEEN_REPLY_BIT, &ct->status))
		वापस IP_CT_ESTABLISHED;
	अगर (test_bit(IPS_EXPECTED_BIT, &ct->status))
		वापस IP_CT_RELATED;
	वापस IP_CT_NEW;
पूर्ण

/* Find an existing connection which this packet beदीर्घs to without
 * re-attributing statistics or modअगरying the connection state.  This allows an
 * skb->_nfct lost due to an upcall to be recovered during actions execution.
 *
 * Must be called with rcu_पढ़ो_lock.
 *
 * On success, populates skb->_nfct and वापसs the connection.  Returns शून्य
 * अगर there is no existing entry.
 */
अटल काष्ठा nf_conn *
ovs_ct_find_existing(काष्ठा net *net, स्थिर काष्ठा nf_conntrack_zone *zone,
		     u8 l3num, काष्ठा sk_buff *skb, bool natted)
अणु
	काष्ठा nf_conntrack_tuple tuple;
	काष्ठा nf_conntrack_tuple_hash *h;
	काष्ठा nf_conn *ct;

	अगर (!nf_ct_get_tuplepr(skb, skb_network_offset(skb), l3num,
			       net, &tuple)) अणु
		pr_debug("ovs_ct_find_existing: Can't get tuple\n");
		वापस शून्य;
	पूर्ण

	/* Must invert the tuple अगर skb has been transक्रमmed by NAT. */
	अगर (natted) अणु
		काष्ठा nf_conntrack_tuple inverse;

		अगर (!nf_ct_invert_tuple(&inverse, &tuple)) अणु
			pr_debug("ovs_ct_find_existing: Inversion failed!\n");
			वापस शून्य;
		पूर्ण
		tuple = inverse;
	पूर्ण

	/* look क्रम tuple match */
	h = nf_conntrack_find_get(net, zone, &tuple);
	अगर (!h)
		वापस शून्य;   /* Not found. */

	ct = nf_ct_tuplehash_to_ctrack(h);

	/* Inverted packet tuple matches the reverse direction conntrack tuple,
	 * select the other tuplehash to get the right 'ctinfo' bits क्रम this
	 * packet.
	 */
	अगर (natted)
		h = &ct->tuplehash[!h->tuple.dst.dir];

	nf_ct_set(skb, ct, ovs_ct_get_info(h));
	वापस ct;
पूर्ण

अटल
काष्ठा nf_conn *ovs_ct_executed(काष्ठा net *net,
				स्थिर काष्ठा sw_flow_key *key,
				स्थिर काष्ठा ovs_conntrack_info *info,
				काष्ठा sk_buff *skb,
				bool *ct_executed)
अणु
	काष्ठा nf_conn *ct = शून्य;

	/* If no ct, check अगर we have evidence that an existing conntrack entry
	 * might be found क्रम this skb.  This happens when we lose a skb->_nfct
	 * due to an upcall, or अगर the direction is being क्रमced.  If the
	 * connection was not confirmed, it is not cached and needs to be run
	 * through conntrack again.
	 */
	*ct_executed = (key->ct_state & OVS_CS_F_TRACKED) &&
		       !(key->ct_state & OVS_CS_F_INVALID) &&
		       (key->ct_zone == info->zone.id);

	अगर (*ct_executed || (!key->ct_state && info->क्रमce)) अणु
		ct = ovs_ct_find_existing(net, &info->zone, info->family, skb,
					  !!(key->ct_state &
					  OVS_CS_F_NAT_MASK));
	पूर्ण

	वापस ct;
पूर्ण

/* Determine whether skb->_nfct is equal to the result of conntrack lookup. */
अटल bool skb_nfct_cached(काष्ठा net *net,
			    स्थिर काष्ठा sw_flow_key *key,
			    स्थिर काष्ठा ovs_conntrack_info *info,
			    काष्ठा sk_buff *skb)
अणु
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct;
	bool ct_executed = true;

	ct = nf_ct_get(skb, &ctinfo);
	अगर (!ct)
		ct = ovs_ct_executed(net, key, info, skb, &ct_executed);

	अगर (ct)
		nf_ct_get(skb, &ctinfo);
	अन्यथा
		वापस false;

	अगर (!net_eq(net, पढ़ो_pnet(&ct->ct_net)))
		वापस false;
	अगर (!nf_ct_zone_equal_any(info->ct, nf_ct_zone(ct)))
		वापस false;
	अगर (info->helper) अणु
		काष्ठा nf_conn_help *help;

		help = nf_ct_ext_find(ct, NF_CT_EXT_HELPER);
		अगर (help && rcu_access_poपूर्णांकer(help->helper) != info->helper)
			वापस false;
	पूर्ण
	अगर (info->nf_ct_समयout) अणु
		काष्ठा nf_conn_समयout *समयout_ext;

		समयout_ext = nf_ct_समयout_find(ct);
		अगर (!समयout_ext || info->nf_ct_समयout !=
		    rcu_dereference(समयout_ext->समयout))
			वापस false;
	पूर्ण
	/* Force conntrack entry direction to the current packet? */
	अगर (info->क्रमce && CTINFO2सूची(ctinfo) != IP_CT_सूची_ORIGINAL) अणु
		/* Delete the conntrack entry अगर confirmed, अन्यथा just release
		 * the reference.
		 */
		अगर (nf_ct_is_confirmed(ct))
			nf_ct_delete(ct, 0, 0);

		nf_conntrack_put(&ct->ct_general);
		nf_ct_set(skb, शून्य, 0);
		वापस false;
	पूर्ण

	वापस ct_executed;
पूर्ण

#अगर IS_ENABLED(CONFIG_NF_NAT)
/* Modelled after nf_nat_ipv[46]_fn().
 * range is only used क्रम new, uninitialized NAT state.
 * Returns either NF_ACCEPT or NF_DROP.
 */
अटल पूर्णांक ovs_ct_nat_execute(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
			      क्रमागत ip_conntrack_info ctinfo,
			      स्थिर काष्ठा nf_nat_range2 *range,
			      क्रमागत nf_nat_manip_type maniptype)
अणु
	पूर्णांक hooknum, nh_off, err = NF_ACCEPT;

	nh_off = skb_network_offset(skb);
	skb_pull_rcsum(skb, nh_off);

	/* See HOOK2MANIP(). */
	अगर (maniptype == NF_NAT_MANIP_SRC)
		hooknum = NF_INET_LOCAL_IN; /* Source NAT */
	अन्यथा
		hooknum = NF_INET_LOCAL_OUT; /* Destination NAT */

	चयन (ctinfo) अणु
	हाल IP_CT_RELATED:
	हाल IP_CT_RELATED_REPLY:
		अगर (IS_ENABLED(CONFIG_NF_NAT) &&
		    skb->protocol == htons(ETH_P_IP) &&
		    ip_hdr(skb)->protocol == IPPROTO_ICMP) अणु
			अगर (!nf_nat_icmp_reply_translation(skb, ct, ctinfo,
							   hooknum))
				err = NF_DROP;
			जाओ push;
		पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_IPV6) &&
			   skb->protocol == htons(ETH_P_IPV6)) अणु
			__be16 frag_off;
			u8 nexthdr = ipv6_hdr(skb)->nexthdr;
			पूर्णांक hdrlen = ipv6_skip_exthdr(skb,
						      माप(काष्ठा ipv6hdr),
						      &nexthdr, &frag_off);

			अगर (hdrlen >= 0 && nexthdr == IPPROTO_ICMPV6) अणु
				अगर (!nf_nat_icmpv6_reply_translation(skb, ct,
								     ctinfo,
								     hooknum,
								     hdrlen))
					err = NF_DROP;
				जाओ push;
			पूर्ण
		पूर्ण
		/* Non-ICMP, fall thru to initialize अगर needed. */
		fallthrough;
	हाल IP_CT_NEW:
		/* Seen it beक्रमe?  This can happen क्रम loopback, retrans,
		 * or local packets.
		 */
		अगर (!nf_nat_initialized(ct, maniptype)) अणु
			/* Initialize according to the NAT action. */
			err = (range && range->flags & NF_NAT_RANGE_MAP_IPS)
				/* Action is set up to establish a new
				 * mapping.
				 */
				? nf_nat_setup_info(ct, range, maniptype)
				: nf_nat_alloc_null_binding(ct, hooknum);
			अगर (err != NF_ACCEPT)
				जाओ push;
		पूर्ण
		अवरोध;

	हाल IP_CT_ESTABLISHED:
	हाल IP_CT_ESTABLISHED_REPLY:
		अवरोध;

	शेष:
		err = NF_DROP;
		जाओ push;
	पूर्ण

	err = nf_nat_packet(ct, ctinfo, hooknum, skb);
push:
	skb_push_rcsum(skb, nh_off);

	वापस err;
पूर्ण

अटल व्योम ovs_nat_update_key(काष्ठा sw_flow_key *key,
			       स्थिर काष्ठा sk_buff *skb,
			       क्रमागत nf_nat_manip_type maniptype)
अणु
	अगर (maniptype == NF_NAT_MANIP_SRC) अणु
		__be16 src;

		key->ct_state |= OVS_CS_F_SRC_NAT;
		अगर (key->eth.type == htons(ETH_P_IP))
			key->ipv4.addr.src = ip_hdr(skb)->saddr;
		अन्यथा अगर (key->eth.type == htons(ETH_P_IPV6))
			स_नकल(&key->ipv6.addr.src, &ipv6_hdr(skb)->saddr,
			       माप(key->ipv6.addr.src));
		अन्यथा
			वापस;

		अगर (key->ip.proto == IPPROTO_UDP)
			src = udp_hdr(skb)->source;
		अन्यथा अगर (key->ip.proto == IPPROTO_TCP)
			src = tcp_hdr(skb)->source;
		अन्यथा अगर (key->ip.proto == IPPROTO_SCTP)
			src = sctp_hdr(skb)->source;
		अन्यथा
			वापस;

		key->tp.src = src;
	पूर्ण अन्यथा अणु
		__be16 dst;

		key->ct_state |= OVS_CS_F_DST_NAT;
		अगर (key->eth.type == htons(ETH_P_IP))
			key->ipv4.addr.dst = ip_hdr(skb)->daddr;
		अन्यथा अगर (key->eth.type == htons(ETH_P_IPV6))
			स_नकल(&key->ipv6.addr.dst, &ipv6_hdr(skb)->daddr,
			       माप(key->ipv6.addr.dst));
		अन्यथा
			वापस;

		अगर (key->ip.proto == IPPROTO_UDP)
			dst = udp_hdr(skb)->dest;
		अन्यथा अगर (key->ip.proto == IPPROTO_TCP)
			dst = tcp_hdr(skb)->dest;
		अन्यथा अगर (key->ip.proto == IPPROTO_SCTP)
			dst = sctp_hdr(skb)->dest;
		अन्यथा
			वापस;

		key->tp.dst = dst;
	पूर्ण
पूर्ण

/* Returns NF_DROP अगर the packet should be dropped, NF_ACCEPT otherwise. */
अटल पूर्णांक ovs_ct_nat(काष्ठा net *net, काष्ठा sw_flow_key *key,
		      स्थिर काष्ठा ovs_conntrack_info *info,
		      काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
		      क्रमागत ip_conntrack_info ctinfo)
अणु
	क्रमागत nf_nat_manip_type maniptype;
	पूर्णांक err;

	/* Add NAT extension अगर not confirmed yet. */
	अगर (!nf_ct_is_confirmed(ct) && !nf_ct_nat_ext_add(ct))
		वापस NF_ACCEPT;   /* Can't NAT. */

	/* Determine NAT type.
	 * Check अगर the NAT type can be deduced from the tracked connection.
	 * Make sure new expected connections (IP_CT_RELATED) are NATted only
	 * when committing.
	 */
	अगर (info->nat & OVS_CT_NAT && ctinfo != IP_CT_NEW &&
	    ct->status & IPS_NAT_MASK &&
	    (ctinfo != IP_CT_RELATED || info->commit)) अणु
		/* NAT an established or related connection like beक्रमe. */
		अगर (CTINFO2सूची(ctinfo) == IP_CT_सूची_REPLY)
			/* This is the REPLY direction क्रम a connection
			 * क्रम which NAT was applied in the क्रमward
			 * direction.  Do the reverse NAT.
			 */
			maniptype = ct->status & IPS_SRC_NAT
				? NF_NAT_MANIP_DST : NF_NAT_MANIP_SRC;
		अन्यथा
			maniptype = ct->status & IPS_SRC_NAT
				? NF_NAT_MANIP_SRC : NF_NAT_MANIP_DST;
	पूर्ण अन्यथा अगर (info->nat & OVS_CT_SRC_NAT) अणु
		maniptype = NF_NAT_MANIP_SRC;
	पूर्ण अन्यथा अगर (info->nat & OVS_CT_DST_NAT) अणु
		maniptype = NF_NAT_MANIP_DST;
	पूर्ण अन्यथा अणु
		वापस NF_ACCEPT; /* Connection is not NATed. */
	पूर्ण
	err = ovs_ct_nat_execute(skb, ct, ctinfo, &info->range, maniptype);

	अगर (err == NF_ACCEPT && ct->status & IPS_DST_NAT) अणु
		अगर (ct->status & IPS_SRC_NAT) अणु
			अगर (maniptype == NF_NAT_MANIP_SRC)
				maniptype = NF_NAT_MANIP_DST;
			अन्यथा
				maniptype = NF_NAT_MANIP_SRC;

			err = ovs_ct_nat_execute(skb, ct, ctinfo, &info->range,
						 maniptype);
		पूर्ण अन्यथा अगर (CTINFO2सूची(ctinfo) == IP_CT_सूची_ORIGINAL) अणु
			err = ovs_ct_nat_execute(skb, ct, ctinfo, शून्य,
						 NF_NAT_MANIP_SRC);
		पूर्ण
	पूर्ण

	/* Mark NAT करोne अगर successful and update the flow key. */
	अगर (err == NF_ACCEPT)
		ovs_nat_update_key(key, skb, maniptype);

	वापस err;
पूर्ण
#अन्यथा /* !CONFIG_NF_NAT */
अटल पूर्णांक ovs_ct_nat(काष्ठा net *net, काष्ठा sw_flow_key *key,
		      स्थिर काष्ठा ovs_conntrack_info *info,
		      काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
		      क्रमागत ip_conntrack_info ctinfo)
अणु
	वापस NF_ACCEPT;
पूर्ण
#पूर्ण_अगर

/* Pass 'skb' through conntrack in 'net', using zone configured in 'info', अगर
 * not करोne alपढ़ोy.  Update key with new CT state after passing the packet
 * through conntrack.
 * Note that अगर the packet is deemed invalid by conntrack, skb->_nfct will be
 * set to शून्य and 0 will be वापसed.
 */
अटल पूर्णांक __ovs_ct_lookup(काष्ठा net *net, काष्ठा sw_flow_key *key,
			   स्थिर काष्ठा ovs_conntrack_info *info,
			   काष्ठा sk_buff *skb)
अणु
	/* If we are recirculating packets to match on conntrack fields and
	 * committing with a separate conntrack action,  then we करोn't need to
	 * actually run the packet through conntrack twice unless it's क्रम a
	 * dअगरferent zone.
	 */
	bool cached = skb_nfct_cached(net, key, info, skb);
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct;

	अगर (!cached) अणु
		काष्ठा nf_hook_state state = अणु
			.hook = NF_INET_PRE_ROUTING,
			.pf = info->family,
			.net = net,
		पूर्ण;
		काष्ठा nf_conn *पंचांगpl = info->ct;
		पूर्णांक err;

		/* Associate skb with specअगरied zone. */
		अगर (पंचांगpl) अणु
			अगर (skb_nfct(skb))
				nf_conntrack_put(skb_nfct(skb));
			nf_conntrack_get(&पंचांगpl->ct_general);
			nf_ct_set(skb, पंचांगpl, IP_CT_NEW);
		पूर्ण

		err = nf_conntrack_in(skb, &state);
		अगर (err != NF_ACCEPT)
			वापस -ENOENT;

		/* Clear CT state NAT flags to mark that we have not yet करोne
		 * NAT after the nf_conntrack_in() call.  We can actually clear
		 * the whole state, as it will be re-initialized below.
		 */
		key->ct_state = 0;

		/* Update the key, but keep the NAT flags. */
		ovs_ct_update_key(skb, info, key, true, true);
	पूर्ण

	ct = nf_ct_get(skb, &ctinfo);
	अगर (ct) अणु
		bool add_helper = false;

		/* Packets starting a new connection must be NATted beक्रमe the
		 * helper, so that the helper knows about the NAT.  We enक्रमce
		 * this by delaying both NAT and helper calls क्रम unconfirmed
		 * connections until the committing CT action.  For later
		 * packets NAT and Helper may be called in either order.
		 *
		 * NAT will be करोne only अगर the CT action has NAT, and only
		 * once per packet (per zone), as guarded by the NAT bits in
		 * the key->ct_state.
		 */
		अगर (info->nat && !(key->ct_state & OVS_CS_F_NAT_MASK) &&
		    (nf_ct_is_confirmed(ct) || info->commit) &&
		    ovs_ct_nat(net, key, info, skb, ct, ctinfo) != NF_ACCEPT) अणु
			वापस -EINVAL;
		पूर्ण

		/* Userspace may decide to perक्रमm a ct lookup without a helper
		 * specअगरied followed by a (recirculate and) commit with one,
		 * or attach a helper in a later commit.  Thereक्रमe, क्रम
		 * connections which we will commit, we may need to attach
		 * the helper here.
		 */
		अगर (info->commit && info->helper && !nfct_help(ct)) अणु
			पूर्णांक err = __nf_ct_try_assign_helper(ct, info->ct,
							    GFP_ATOMIC);
			अगर (err)
				वापस err;
			add_helper = true;

			/* helper installed, add seqadj अगर NAT is required */
			अगर (info->nat && !nfct_seqadj(ct)) अणु
				अगर (!nfct_seqadj_ext_add(ct))
					वापस -EINVAL;
			पूर्ण
		पूर्ण

		/* Call the helper only अगर:
		 * - nf_conntrack_in() was executed above ("!cached") or a
		 *   helper was just attached ("add_helper") क्रम a confirmed
		 *   connection, or
		 * - When committing an unconfirmed connection.
		 */
		अगर ((nf_ct_is_confirmed(ct) ? !cached || add_helper :
					      info->commit) &&
		    ovs_ct_helper(skb, info->family) != NF_ACCEPT) अणु
			वापस -EINVAL;
		पूर्ण

		अगर (nf_ct_protonum(ct) == IPPROTO_TCP &&
		    nf_ct_is_confirmed(ct) && nf_conntrack_tcp_established(ct)) अणु
			/* Be liberal क्रम tcp packets so that out-of-winकरोw
			 * packets are not marked invalid.
			 */
			nf_ct_set_tcp_be_liberal(ct);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Lookup connection and पढ़ो fields पूर्णांकo key. */
अटल पूर्णांक ovs_ct_lookup(काष्ठा net *net, काष्ठा sw_flow_key *key,
			 स्थिर काष्ठा ovs_conntrack_info *info,
			 काष्ठा sk_buff *skb)
अणु
	काष्ठा nf_conntrack_expect *exp;

	/* If we pass an expected packet through nf_conntrack_in() the
	 * expectation is typically हटाओd, but the packet could still be
	 * lost in upcall processing.  To prevent this from happening we
	 * perक्रमm an explicit expectation lookup.  Expected connections are
	 * always new, and will be passed through conntrack only when they are
	 * committed, as it is OK to हटाओ the expectation at that समय.
	 */
	exp = ovs_ct_expect_find(net, &info->zone, info->family, skb);
	अगर (exp) अणु
		u8 state;

		/* NOTE: New connections are NATted and Helped only when
		 * committed, so we are not calling पूर्णांकo NAT here.
		 */
		state = OVS_CS_F_TRACKED | OVS_CS_F_NEW | OVS_CS_F_RELATED;
		__ovs_ct_update_key(key, state, &info->zone, exp->master);
	पूर्ण अन्यथा अणु
		काष्ठा nf_conn *ct;
		पूर्णांक err;

		err = __ovs_ct_lookup(net, key, info, skb);
		अगर (err)
			वापस err;

		ct = (काष्ठा nf_conn *)skb_nfct(skb);
		अगर (ct)
			nf_ct_deliver_cached_events(ct);
	पूर्ण

	वापस 0;
पूर्ण

अटल bool labels_nonzero(स्थिर काष्ठा ovs_key_ct_labels *labels)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < OVS_CT_LABELS_LEN_32; i++)
		अगर (labels->ct_labels_32[i])
			वापस true;

	वापस false;
पूर्ण

#अगर	IS_ENABLED(CONFIG_NETFILTER_CONNCOUNT)
अटल काष्ठा hlist_head *ct_limit_hash_bucket(
	स्थिर काष्ठा ovs_ct_limit_info *info, u16 zone)
अणु
	वापस &info->limits[zone & (CT_LIMIT_HASH_BUCKETS - 1)];
पूर्ण

/* Call with ovs_mutex */
अटल व्योम ct_limit_set(स्थिर काष्ठा ovs_ct_limit_info *info,
			 काष्ठा ovs_ct_limit *new_ct_limit)
अणु
	काष्ठा ovs_ct_limit *ct_limit;
	काष्ठा hlist_head *head;

	head = ct_limit_hash_bucket(info, new_ct_limit->zone);
	hlist_क्रम_each_entry_rcu(ct_limit, head, hlist_node) अणु
		अगर (ct_limit->zone == new_ct_limit->zone) अणु
			hlist_replace_rcu(&ct_limit->hlist_node,
					  &new_ct_limit->hlist_node);
			kमुक्त_rcu(ct_limit, rcu);
			वापस;
		पूर्ण
	पूर्ण

	hlist_add_head_rcu(&new_ct_limit->hlist_node, head);
पूर्ण

/* Call with ovs_mutex */
अटल व्योम ct_limit_del(स्थिर काष्ठा ovs_ct_limit_info *info, u16 zone)
अणु
	काष्ठा ovs_ct_limit *ct_limit;
	काष्ठा hlist_head *head;
	काष्ठा hlist_node *n;

	head = ct_limit_hash_bucket(info, zone);
	hlist_क्रम_each_entry_safe(ct_limit, n, head, hlist_node) अणु
		अगर (ct_limit->zone == zone) अणु
			hlist_del_rcu(&ct_limit->hlist_node);
			kमुक्त_rcu(ct_limit, rcu);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

/* Call with RCU पढ़ो lock */
अटल u32 ct_limit_get(स्थिर काष्ठा ovs_ct_limit_info *info, u16 zone)
अणु
	काष्ठा ovs_ct_limit *ct_limit;
	काष्ठा hlist_head *head;

	head = ct_limit_hash_bucket(info, zone);
	hlist_क्रम_each_entry_rcu(ct_limit, head, hlist_node) अणु
		अगर (ct_limit->zone == zone)
			वापस ct_limit->limit;
	पूर्ण

	वापस info->शेष_limit;
पूर्ण

अटल पूर्णांक ovs_ct_check_limit(काष्ठा net *net,
			      स्थिर काष्ठा ovs_conntrack_info *info,
			      स्थिर काष्ठा nf_conntrack_tuple *tuple)
अणु
	काष्ठा ovs_net *ovs_net = net_generic(net, ovs_net_id);
	स्थिर काष्ठा ovs_ct_limit_info *ct_limit_info = ovs_net->ct_limit_info;
	u32 per_zone_limit, connections;
	u32 conncount_key;

	conncount_key = info->zone.id;

	per_zone_limit = ct_limit_get(ct_limit_info, info->zone.id);
	अगर (per_zone_limit == OVS_CT_LIMIT_UNLIMITED)
		वापस 0;

	connections = nf_conncount_count(net, ct_limit_info->data,
					 &conncount_key, tuple, &info->zone);
	अगर (connections > per_zone_limit)
		वापस -ENOMEM;

	वापस 0;
पूर्ण
#पूर्ण_अगर

/* Lookup connection and confirm अगर unconfirmed. */
अटल पूर्णांक ovs_ct_commit(काष्ठा net *net, काष्ठा sw_flow_key *key,
			 स्थिर काष्ठा ovs_conntrack_info *info,
			 काष्ठा sk_buff *skb)
अणु
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct;
	पूर्णांक err;

	err = __ovs_ct_lookup(net, key, info, skb);
	अगर (err)
		वापस err;

	/* The connection could be invalid, in which हाल this is a no-op.*/
	ct = nf_ct_get(skb, &ctinfo);
	अगर (!ct)
		वापस 0;

#अगर	IS_ENABLED(CONFIG_NETFILTER_CONNCOUNT)
	अगर (अटल_branch_unlikely(&ovs_ct_limit_enabled)) अणु
		अगर (!nf_ct_is_confirmed(ct)) अणु
			err = ovs_ct_check_limit(net, info,
				&ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple);
			अगर (err) अणु
				net_warn_ratelimited("openvswitch: zone: %u "
					"exceeds conntrack limit\n",
					info->zone.id);
				वापस err;
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/* Set the conntrack event mask अगर given.  NEW and DELETE events have
	 * their own groups, but the NFNLGRP_CONNTRACK_UPDATE group listener
	 * typically would receive many kinds of updates.  Setting the event
	 * mask allows those events to be filtered.  The set event mask will
	 * reमुख्य in effect क्रम the lअगरeसमय of the connection unless changed
	 * by a further CT action with both the commit flag and the evenपंचांगask
	 * option. */
	अगर (info->have_evenपंचांगask) अणु
		काष्ठा nf_conntrack_ecache *cache = nf_ct_ecache_find(ct);

		अगर (cache)
			cache->cपंचांगask = info->evenपंचांगask;
	पूर्ण

	/* Apply changes beक्रमe confirming the connection so that the initial
	 * conntrack NEW netlink event carries the values given in the CT
	 * action.
	 */
	अगर (info->mark.mask) अणु
		err = ovs_ct_set_mark(ct, key, info->mark.value,
				      info->mark.mask);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (!nf_ct_is_confirmed(ct)) अणु
		err = ovs_ct_init_labels(ct, key, &info->labels.value,
					 &info->labels.mask);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_NF_CONNTRACK_LABELS) &&
		   labels_nonzero(&info->labels.mask)) अणु
		err = ovs_ct_set_labels(ct, key, &info->labels.value,
					&info->labels.mask);
		अगर (err)
			वापस err;
	पूर्ण
	/* This will take care of sending queued events even अगर the connection
	 * is alपढ़ोy confirmed.
	 */
	अगर (nf_conntrack_confirm(skb) != NF_ACCEPT)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/* Trim the skb to the length specअगरied by the IP/IPv6 header,
 * removing any trailing lower-layer padding. This prepares the skb
 * क्रम higher-layer processing that assumes skb->len excludes padding
 * (such as nf_ip_checksum). The caller needs to pull the skb to the
 * network header, and ensure ip_hdr/ipv6_hdr poपूर्णांकs to valid data.
 */
अटल पूर्णांक ovs_skb_network_trim(काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक len;
	पूर्णांक err;

	चयन (skb->protocol) अणु
	हाल htons(ETH_P_IP):
		len = ntohs(ip_hdr(skb)->tot_len);
		अवरोध;
	हाल htons(ETH_P_IPV6):
		len = माप(काष्ठा ipv6hdr)
			+ ntohs(ipv6_hdr(skb)->payload_len);
		अवरोध;
	शेष:
		len = skb->len;
	पूर्ण

	err = pskb_trim_rcsum(skb, len);
	अगर (err)
		kमुक्त_skb(skb);

	वापस err;
पूर्ण

/* Returns 0 on success, -EINPROGRESS अगर 'skb' is stolen, or other nonzero
 * value अगर 'skb' is मुक्तd.
 */
पूर्णांक ovs_ct_execute(काष्ठा net *net, काष्ठा sk_buff *skb,
		   काष्ठा sw_flow_key *key,
		   स्थिर काष्ठा ovs_conntrack_info *info)
अणु
	पूर्णांक nh_ofs;
	पूर्णांक err;

	/* The conntrack module expects to be working at L3. */
	nh_ofs = skb_network_offset(skb);
	skb_pull_rcsum(skb, nh_ofs);

	err = ovs_skb_network_trim(skb);
	अगर (err)
		वापस err;

	अगर (key->ip.frag != OVS_FRAG_TYPE_NONE) अणु
		err = handle_fragments(net, key, info->zone.id, skb);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (info->commit)
		err = ovs_ct_commit(net, key, info, skb);
	अन्यथा
		err = ovs_ct_lookup(net, key, info, skb);

	skb_push_rcsum(skb, nh_ofs);
	अगर (err)
		kमुक्त_skb(skb);
	वापस err;
पूर्ण

पूर्णांक ovs_ct_clear(काष्ठा sk_buff *skb, काष्ठा sw_flow_key *key)
अणु
	अगर (skb_nfct(skb)) अणु
		nf_conntrack_put(skb_nfct(skb));
		nf_ct_set(skb, शून्य, IP_CT_UNTRACKED);
		ovs_ct_fill_key(skb, key, false);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ovs_ct_add_helper(काष्ठा ovs_conntrack_info *info, स्थिर अक्षर *name,
			     स्थिर काष्ठा sw_flow_key *key, bool log)
अणु
	काष्ठा nf_conntrack_helper *helper;
	काष्ठा nf_conn_help *help;
	पूर्णांक ret = 0;

	helper = nf_conntrack_helper_try_module_get(name, info->family,
						    key->ip.proto);
	अगर (!helper) अणु
		OVS_NLERR(log, "Unknown helper \"%s\"", name);
		वापस -EINVAL;
	पूर्ण

	help = nf_ct_helper_ext_add(info->ct, GFP_KERNEL);
	अगर (!help) अणु
		nf_conntrack_helper_put(helper);
		वापस -ENOMEM;
	पूर्ण

#अगर IS_ENABLED(CONFIG_NF_NAT)
	अगर (info->nat) अणु
		ret = nf_nat_helper_try_module_get(name, info->family,
						   key->ip.proto);
		अगर (ret) अणु
			nf_conntrack_helper_put(helper);
			OVS_NLERR(log, "Failed to load \"%s\" NAT helper, error: %d",
				  name, ret);
			वापस ret;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	rcu_assign_poपूर्णांकer(help->helper, helper);
	info->helper = helper;
	वापस ret;
पूर्ण

#अगर IS_ENABLED(CONFIG_NF_NAT)
अटल पूर्णांक parse_nat(स्थिर काष्ठा nlattr *attr,
		     काष्ठा ovs_conntrack_info *info, bool log)
अणु
	काष्ठा nlattr *a;
	पूर्णांक rem;
	bool have_ip_max = false;
	bool have_proto_max = false;
	bool ip_vers = (info->family == NFPROTO_IPV6);

	nla_क्रम_each_nested(a, attr, rem) अणु
		अटल स्थिर पूर्णांक ovs_nat_attr_lens[OVS_NAT_ATTR_MAX + 1][2] = अणु
			[OVS_NAT_ATTR_SRC] = अणु0, 0पूर्ण,
			[OVS_NAT_ATTR_DST] = अणु0, 0पूर्ण,
			[OVS_NAT_ATTR_IP_MIN] = अणुमाप(काष्ठा in_addr),
						 माप(काष्ठा in6_addr)पूर्ण,
			[OVS_NAT_ATTR_IP_MAX] = अणुमाप(काष्ठा in_addr),
						 माप(काष्ठा in6_addr)पूर्ण,
			[OVS_NAT_ATTR_PROTO_MIN] = अणुमाप(u16), माप(u16)पूर्ण,
			[OVS_NAT_ATTR_PROTO_MAX] = अणुमाप(u16), माप(u16)पूर्ण,
			[OVS_NAT_ATTR_PERSISTENT] = अणु0, 0पूर्ण,
			[OVS_NAT_ATTR_PROTO_HASH] = अणु0, 0पूर्ण,
			[OVS_NAT_ATTR_PROTO_RANDOM] = अणु0, 0पूर्ण,
		पूर्ण;
		पूर्णांक type = nla_type(a);

		अगर (type > OVS_NAT_ATTR_MAX) अणु
			OVS_NLERR(log, "Unknown NAT attribute (type=%d, max=%d)",
				  type, OVS_NAT_ATTR_MAX);
			वापस -EINVAL;
		पूर्ण

		अगर (nla_len(a) != ovs_nat_attr_lens[type][ip_vers]) अणु
			OVS_NLERR(log, "NAT attribute type %d has unexpected length (%d != %d)",
				  type, nla_len(a),
				  ovs_nat_attr_lens[type][ip_vers]);
			वापस -EINVAL;
		पूर्ण

		चयन (type) अणु
		हाल OVS_NAT_ATTR_SRC:
		हाल OVS_NAT_ATTR_DST:
			अगर (info->nat) अणु
				OVS_NLERR(log, "Only one type of NAT may be specified");
				वापस -दुस्फल;
			पूर्ण
			info->nat |= OVS_CT_NAT;
			info->nat |= ((type == OVS_NAT_ATTR_SRC)
					? OVS_CT_SRC_NAT : OVS_CT_DST_NAT);
			अवरोध;

		हाल OVS_NAT_ATTR_IP_MIN:
			nla_स_नकल(&info->range.min_addr, a,
				   माप(info->range.min_addr));
			info->range.flags |= NF_NAT_RANGE_MAP_IPS;
			अवरोध;

		हाल OVS_NAT_ATTR_IP_MAX:
			have_ip_max = true;
			nla_स_नकल(&info->range.max_addr, a,
				   माप(info->range.max_addr));
			info->range.flags |= NF_NAT_RANGE_MAP_IPS;
			अवरोध;

		हाल OVS_NAT_ATTR_PROTO_MIN:
			info->range.min_proto.all = htons(nla_get_u16(a));
			info->range.flags |= NF_NAT_RANGE_PROTO_SPECIFIED;
			अवरोध;

		हाल OVS_NAT_ATTR_PROTO_MAX:
			have_proto_max = true;
			info->range.max_proto.all = htons(nla_get_u16(a));
			info->range.flags |= NF_NAT_RANGE_PROTO_SPECIFIED;
			अवरोध;

		हाल OVS_NAT_ATTR_PERSISTENT:
			info->range.flags |= NF_NAT_RANGE_PERSISTENT;
			अवरोध;

		हाल OVS_NAT_ATTR_PROTO_HASH:
			info->range.flags |= NF_NAT_RANGE_PROTO_RANDOM;
			अवरोध;

		हाल OVS_NAT_ATTR_PROTO_RANDOM:
			info->range.flags |= NF_NAT_RANGE_PROTO_RANDOM_FULLY;
			अवरोध;

		शेष:
			OVS_NLERR(log, "Unknown nat attribute (%d)", type);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (rem > 0) अणु
		OVS_NLERR(log, "NAT attribute has %d unknown bytes", rem);
		वापस -EINVAL;
	पूर्ण
	अगर (!info->nat) अणु
		/* Do not allow flags अगर no type is given. */
		अगर (info->range.flags) अणु
			OVS_NLERR(log,
				  "NAT flags may be given only when NAT range (SRC or DST) is also specified."
				  );
			वापस -EINVAL;
		पूर्ण
		info->nat = OVS_CT_NAT;   /* NAT existing connections. */
	पूर्ण अन्यथा अगर (!info->commit) अणु
		OVS_NLERR(log,
			  "NAT attributes may be specified only when CT COMMIT flag is also specified."
			  );
		वापस -EINVAL;
	पूर्ण
	/* Allow missing IP_MAX. */
	अगर (info->range.flags & NF_NAT_RANGE_MAP_IPS && !have_ip_max) अणु
		स_नकल(&info->range.max_addr, &info->range.min_addr,
		       माप(info->range.max_addr));
	पूर्ण
	/* Allow missing PROTO_MAX. */
	अगर (info->range.flags & NF_NAT_RANGE_PROTO_SPECIFIED &&
	    !have_proto_max) अणु
		info->range.max_proto.all = info->range.min_proto.all;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा ovs_ct_len_tbl ovs_ct_attr_lens[OVS_CT_ATTR_MAX + 1] = अणु
	[OVS_CT_ATTR_COMMIT]	= अणु .minlen = 0, .maxlen = 0 पूर्ण,
	[OVS_CT_ATTR_FORCE_COMMIT]	= अणु .minlen = 0, .maxlen = 0 पूर्ण,
	[OVS_CT_ATTR_ZONE]	= अणु .minlen = माप(u16),
				    .maxlen = माप(u16) पूर्ण,
	[OVS_CT_ATTR_MARK]	= अणु .minlen = माप(काष्ठा md_mark),
				    .maxlen = माप(काष्ठा md_mark) पूर्ण,
	[OVS_CT_ATTR_LABELS]	= अणु .minlen = माप(काष्ठा md_labels),
				    .maxlen = माप(काष्ठा md_labels) पूर्ण,
	[OVS_CT_ATTR_HELPER]	= अणु .minlen = 1,
				    .maxlen = NF_CT_HELPER_NAME_LEN पूर्ण,
#अगर IS_ENABLED(CONFIG_NF_NAT)
	/* NAT length is checked when parsing the nested attributes. */
	[OVS_CT_ATTR_NAT]	= अणु .minlen = 0, .maxlen = पूर्णांक_उच्च पूर्ण,
#पूर्ण_अगर
	[OVS_CT_ATTR_EVENTMASK]	= अणु .minlen = माप(u32),
				    .maxlen = माप(u32) पूर्ण,
	[OVS_CT_ATTR_TIMEOUT] = अणु .minlen = 1,
				  .maxlen = CTNL_TIMEOUT_NAME_MAX पूर्ण,
पूर्ण;

अटल पूर्णांक parse_ct(स्थिर काष्ठा nlattr *attr, काष्ठा ovs_conntrack_info *info,
		    स्थिर अक्षर **helper, bool log)
अणु
	काष्ठा nlattr *a;
	पूर्णांक rem;

	nla_क्रम_each_nested(a, attr, rem) अणु
		पूर्णांक type = nla_type(a);
		पूर्णांक maxlen;
		पूर्णांक minlen;

		अगर (type > OVS_CT_ATTR_MAX) अणु
			OVS_NLERR(log,
				  "Unknown conntrack attr (type=%d, max=%d)",
				  type, OVS_CT_ATTR_MAX);
			वापस -EINVAL;
		पूर्ण

		maxlen = ovs_ct_attr_lens[type].maxlen;
		minlen = ovs_ct_attr_lens[type].minlen;
		अगर (nla_len(a) < minlen || nla_len(a) > maxlen) अणु
			OVS_NLERR(log,
				  "Conntrack attr type has unexpected length (type=%d, length=%d, expected=%d)",
				  type, nla_len(a), maxlen);
			वापस -EINVAL;
		पूर्ण

		चयन (type) अणु
		हाल OVS_CT_ATTR_FORCE_COMMIT:
			info->क्रमce = true;
			fallthrough;
		हाल OVS_CT_ATTR_COMMIT:
			info->commit = true;
			अवरोध;
#अगर_घोषित CONFIG_NF_CONNTRACK_ZONES
		हाल OVS_CT_ATTR_ZONE:
			info->zone.id = nla_get_u16(a);
			अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CONNTRACK_MARK
		हाल OVS_CT_ATTR_MARK: अणु
			काष्ठा md_mark *mark = nla_data(a);

			अगर (!mark->mask) अणु
				OVS_NLERR(log, "ct_mark mask cannot be 0");
				वापस -EINVAL;
			पूर्ण
			info->mark = *mark;
			अवरोध;
		पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CONNTRACK_LABELS
		हाल OVS_CT_ATTR_LABELS: अणु
			काष्ठा md_labels *labels = nla_data(a);

			अगर (!labels_nonzero(&labels->mask)) अणु
				OVS_NLERR(log, "ct_labels mask cannot be 0");
				वापस -EINVAL;
			पूर्ण
			info->labels = *labels;
			अवरोध;
		पूर्ण
#पूर्ण_अगर
		हाल OVS_CT_ATTR_HELPER:
			*helper = nla_data(a);
			अगर (!स_प्रथम(*helper, '\0', nla_len(a))) अणु
				OVS_NLERR(log, "Invalid conntrack helper");
				वापस -EINVAL;
			पूर्ण
			अवरोध;
#अगर IS_ENABLED(CONFIG_NF_NAT)
		हाल OVS_CT_ATTR_NAT: अणु
			पूर्णांक err = parse_nat(a, info, log);

			अगर (err)
				वापस err;
			अवरोध;
		पूर्ण
#पूर्ण_अगर
		हाल OVS_CT_ATTR_EVENTMASK:
			info->have_evenपंचांगask = true;
			info->evenपंचांगask = nla_get_u32(a);
			अवरोध;
#अगर_घोषित CONFIG_NF_CONNTRACK_TIMEOUT
		हाल OVS_CT_ATTR_TIMEOUT:
			स_नकल(info->समयout, nla_data(a), nla_len(a));
			अगर (!स_प्रथम(info->समयout, '\0', nla_len(a))) अणु
				OVS_NLERR(log, "Invalid conntrack timeout");
				वापस -EINVAL;
			पूर्ण
			अवरोध;
#पूर्ण_अगर

		शेष:
			OVS_NLERR(log, "Unknown conntrack attr (%d)",
				  type);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_NF_CONNTRACK_MARK
	अगर (!info->commit && info->mark.mask) अणु
		OVS_NLERR(log,
			  "Setting conntrack mark requires 'commit' flag.");
		वापस -EINVAL;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CONNTRACK_LABELS
	अगर (!info->commit && labels_nonzero(&info->labels.mask)) अणु
		OVS_NLERR(log,
			  "Setting conntrack labels requires 'commit' flag.");
		वापस -EINVAL;
	पूर्ण
#पूर्ण_अगर
	अगर (rem > 0) अणु
		OVS_NLERR(log, "Conntrack attr has %d unknown bytes", rem);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

bool ovs_ct_verअगरy(काष्ठा net *net, क्रमागत ovs_key_attr attr)
अणु
	अगर (attr == OVS_KEY_ATTR_CT_STATE)
		वापस true;
	अगर (IS_ENABLED(CONFIG_NF_CONNTRACK_ZONES) &&
	    attr == OVS_KEY_ATTR_CT_ZONE)
		वापस true;
	अगर (IS_ENABLED(CONFIG_NF_CONNTRACK_MARK) &&
	    attr == OVS_KEY_ATTR_CT_MARK)
		वापस true;
	अगर (IS_ENABLED(CONFIG_NF_CONNTRACK_LABELS) &&
	    attr == OVS_KEY_ATTR_CT_LABELS) अणु
		काष्ठा ovs_net *ovs_net = net_generic(net, ovs_net_id);

		वापस ovs_net->xt_label;
	पूर्ण

	वापस false;
पूर्ण

पूर्णांक ovs_ct_copy_action(काष्ठा net *net, स्थिर काष्ठा nlattr *attr,
		       स्थिर काष्ठा sw_flow_key *key,
		       काष्ठा sw_flow_actions **sfa,  bool log)
अणु
	काष्ठा ovs_conntrack_info ct_info;
	स्थिर अक्षर *helper = शून्य;
	u16 family;
	पूर्णांक err;

	family = key_to_nfproto(key);
	अगर (family == NFPROTO_UNSPEC) अणु
		OVS_NLERR(log, "ct family unspecified");
		वापस -EINVAL;
	पूर्ण

	स_रखो(&ct_info, 0, माप(ct_info));
	ct_info.family = family;

	nf_ct_zone_init(&ct_info.zone, NF_CT_DEFAULT_ZONE_ID,
			NF_CT_DEFAULT_ZONE_सूची, 0);

	err = parse_ct(attr, &ct_info, &helper, log);
	अगर (err)
		वापस err;

	/* Set up ढाँचा क्रम tracking connections in specअगरic zones. */
	ct_info.ct = nf_ct_पंचांगpl_alloc(net, &ct_info.zone, GFP_KERNEL);
	अगर (!ct_info.ct) अणु
		OVS_NLERR(log, "Failed to allocate conntrack template");
		वापस -ENOMEM;
	पूर्ण

	अगर (ct_info.समयout[0]) अणु
		अगर (nf_ct_set_समयout(net, ct_info.ct, family, key->ip.proto,
				      ct_info.समयout))
			pr_info_ratelimited("Failed to associated timeout "
					    "policy `%s'\n", ct_info.समयout);
		अन्यथा
			ct_info.nf_ct_समयout = rcu_dereference(
				nf_ct_समयout_find(ct_info.ct)->समयout);

	पूर्ण

	अगर (helper) अणु
		err = ovs_ct_add_helper(&ct_info, helper, key, log);
		अगर (err)
			जाओ err_मुक्त_ct;
	पूर्ण

	err = ovs_nla_add_action(sfa, OVS_ACTION_ATTR_CT, &ct_info,
				 माप(ct_info), log);
	अगर (err)
		जाओ err_मुक्त_ct;

	__set_bit(IPS_CONFIRMED_BIT, &ct_info.ct->status);
	nf_conntrack_get(&ct_info.ct->ct_general);
	वापस 0;
err_मुक्त_ct:
	__ovs_ct_मुक्त_action(&ct_info);
	वापस err;
पूर्ण

#अगर IS_ENABLED(CONFIG_NF_NAT)
अटल bool ovs_ct_nat_to_attr(स्थिर काष्ठा ovs_conntrack_info *info,
			       काष्ठा sk_buff *skb)
अणु
	काष्ठा nlattr *start;

	start = nla_nest_start_noflag(skb, OVS_CT_ATTR_NAT);
	अगर (!start)
		वापस false;

	अगर (info->nat & OVS_CT_SRC_NAT) अणु
		अगर (nla_put_flag(skb, OVS_NAT_ATTR_SRC))
			वापस false;
	पूर्ण अन्यथा अगर (info->nat & OVS_CT_DST_NAT) अणु
		अगर (nla_put_flag(skb, OVS_NAT_ATTR_DST))
			वापस false;
	पूर्ण अन्यथा अणु
		जाओ out;
	पूर्ण

	अगर (info->range.flags & NF_NAT_RANGE_MAP_IPS) अणु
		अगर (IS_ENABLED(CONFIG_NF_NAT) &&
		    info->family == NFPROTO_IPV4) अणु
			अगर (nla_put_in_addr(skb, OVS_NAT_ATTR_IP_MIN,
					    info->range.min_addr.ip) ||
			    (info->range.max_addr.ip
			     != info->range.min_addr.ip &&
			     (nla_put_in_addr(skb, OVS_NAT_ATTR_IP_MAX,
					      info->range.max_addr.ip))))
				वापस false;
		पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_IPV6) &&
			   info->family == NFPROTO_IPV6) अणु
			अगर (nla_put_in6_addr(skb, OVS_NAT_ATTR_IP_MIN,
					     &info->range.min_addr.in6) ||
			    (स_भेद(&info->range.max_addr.in6,
				    &info->range.min_addr.in6,
				    माप(info->range.max_addr.in6)) &&
			     (nla_put_in6_addr(skb, OVS_NAT_ATTR_IP_MAX,
					       &info->range.max_addr.in6))))
				वापस false;
		पूर्ण अन्यथा अणु
			वापस false;
		पूर्ण
	पूर्ण
	अगर (info->range.flags & NF_NAT_RANGE_PROTO_SPECIFIED &&
	    (nla_put_u16(skb, OVS_NAT_ATTR_PROTO_MIN,
			 ntohs(info->range.min_proto.all)) ||
	     (info->range.max_proto.all != info->range.min_proto.all &&
	      nla_put_u16(skb, OVS_NAT_ATTR_PROTO_MAX,
			  ntohs(info->range.max_proto.all)))))
		वापस false;

	अगर (info->range.flags & NF_NAT_RANGE_PERSISTENT &&
	    nla_put_flag(skb, OVS_NAT_ATTR_PERSISTENT))
		वापस false;
	अगर (info->range.flags & NF_NAT_RANGE_PROTO_RANDOM &&
	    nla_put_flag(skb, OVS_NAT_ATTR_PROTO_HASH))
		वापस false;
	अगर (info->range.flags & NF_NAT_RANGE_PROTO_RANDOM_FULLY &&
	    nla_put_flag(skb, OVS_NAT_ATTR_PROTO_RANDOM))
		वापस false;
out:
	nla_nest_end(skb, start);

	वापस true;
पूर्ण
#पूर्ण_अगर

पूर्णांक ovs_ct_action_to_attr(स्थिर काष्ठा ovs_conntrack_info *ct_info,
			  काष्ठा sk_buff *skb)
अणु
	काष्ठा nlattr *start;

	start = nla_nest_start_noflag(skb, OVS_ACTION_ATTR_CT);
	अगर (!start)
		वापस -EMSGSIZE;

	अगर (ct_info->commit && nla_put_flag(skb, ct_info->क्रमce
					    ? OVS_CT_ATTR_FORCE_COMMIT
					    : OVS_CT_ATTR_COMMIT))
		वापस -EMSGSIZE;
	अगर (IS_ENABLED(CONFIG_NF_CONNTRACK_ZONES) &&
	    nla_put_u16(skb, OVS_CT_ATTR_ZONE, ct_info->zone.id))
		वापस -EMSGSIZE;
	अगर (IS_ENABLED(CONFIG_NF_CONNTRACK_MARK) && ct_info->mark.mask &&
	    nla_put(skb, OVS_CT_ATTR_MARK, माप(ct_info->mark),
		    &ct_info->mark))
		वापस -EMSGSIZE;
	अगर (IS_ENABLED(CONFIG_NF_CONNTRACK_LABELS) &&
	    labels_nonzero(&ct_info->labels.mask) &&
	    nla_put(skb, OVS_CT_ATTR_LABELS, माप(ct_info->labels),
		    &ct_info->labels))
		वापस -EMSGSIZE;
	अगर (ct_info->helper) अणु
		अगर (nla_put_string(skb, OVS_CT_ATTR_HELPER,
				   ct_info->helper->name))
			वापस -EMSGSIZE;
	पूर्ण
	अगर (ct_info->have_evenपंचांगask &&
	    nla_put_u32(skb, OVS_CT_ATTR_EVENTMASK, ct_info->evenपंचांगask))
		वापस -EMSGSIZE;
	अगर (ct_info->समयout[0]) अणु
		अगर (nla_put_string(skb, OVS_CT_ATTR_TIMEOUT, ct_info->समयout))
			वापस -EMSGSIZE;
	पूर्ण

#अगर IS_ENABLED(CONFIG_NF_NAT)
	अगर (ct_info->nat && !ovs_ct_nat_to_attr(ct_info, skb))
		वापस -EMSGSIZE;
#पूर्ण_अगर
	nla_nest_end(skb, start);

	वापस 0;
पूर्ण

व्योम ovs_ct_मुक्त_action(स्थिर काष्ठा nlattr *a)
अणु
	काष्ठा ovs_conntrack_info *ct_info = nla_data(a);

	__ovs_ct_मुक्त_action(ct_info);
पूर्ण

अटल व्योम __ovs_ct_मुक्त_action(काष्ठा ovs_conntrack_info *ct_info)
अणु
	अगर (ct_info->helper) अणु
#अगर IS_ENABLED(CONFIG_NF_NAT)
		अगर (ct_info->nat)
			nf_nat_helper_put(ct_info->helper);
#पूर्ण_अगर
		nf_conntrack_helper_put(ct_info->helper);
	पूर्ण
	अगर (ct_info->ct) अणु
		अगर (ct_info->समयout[0])
			nf_ct_destroy_समयout(ct_info->ct);
		nf_ct_पंचांगpl_मुक्त(ct_info->ct);
	पूर्ण
पूर्ण

#अगर	IS_ENABLED(CONFIG_NETFILTER_CONNCOUNT)
अटल पूर्णांक ovs_ct_limit_init(काष्ठा net *net, काष्ठा ovs_net *ovs_net)
अणु
	पूर्णांक i, err;

	ovs_net->ct_limit_info = kदो_स्मृति(माप(*ovs_net->ct_limit_info),
					 GFP_KERNEL);
	अगर (!ovs_net->ct_limit_info)
		वापस -ENOMEM;

	ovs_net->ct_limit_info->शेष_limit = OVS_CT_LIMIT_DEFAULT;
	ovs_net->ct_limit_info->limits =
		kदो_स्मृति_array(CT_LIMIT_HASH_BUCKETS, माप(काष्ठा hlist_head),
			      GFP_KERNEL);
	अगर (!ovs_net->ct_limit_info->limits) अणु
		kमुक्त(ovs_net->ct_limit_info);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < CT_LIMIT_HASH_BUCKETS; i++)
		INIT_HLIST_HEAD(&ovs_net->ct_limit_info->limits[i]);

	ovs_net->ct_limit_info->data =
		nf_conncount_init(net, NFPROTO_INET, माप(u32));

	अगर (IS_ERR(ovs_net->ct_limit_info->data)) अणु
		err = PTR_ERR(ovs_net->ct_limit_info->data);
		kमुक्त(ovs_net->ct_limit_info->limits);
		kमुक्त(ovs_net->ct_limit_info);
		pr_err("openvswitch: failed to init nf_conncount %d\n", err);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ovs_ct_limit_निकास(काष्ठा net *net, काष्ठा ovs_net *ovs_net)
अणु
	स्थिर काष्ठा ovs_ct_limit_info *info = ovs_net->ct_limit_info;
	पूर्णांक i;

	nf_conncount_destroy(net, NFPROTO_INET, info->data);
	क्रम (i = 0; i < CT_LIMIT_HASH_BUCKETS; ++i) अणु
		काष्ठा hlist_head *head = &info->limits[i];
		काष्ठा ovs_ct_limit *ct_limit;

		hlist_क्रम_each_entry_rcu(ct_limit, head, hlist_node,
					 lockdep_ovsl_is_held())
			kमुक्त_rcu(ct_limit, rcu);
	पूर्ण
	kमुक्त(info->limits);
	kमुक्त(info);
पूर्ण

अटल काष्ठा sk_buff *
ovs_ct_limit_cmd_reply_start(काष्ठा genl_info *info, u8 cmd,
			     काष्ठा ovs_header **ovs_reply_header)
अणु
	काष्ठा ovs_header *ovs_header = info->userhdr;
	काष्ठा sk_buff *skb;

	skb = genlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	*ovs_reply_header = genlmsg_put(skb, info->snd_portid,
					info->snd_seq,
					&dp_ct_limit_genl_family, 0, cmd);

	अगर (!*ovs_reply_header) अणु
		nlmsg_मुक्त(skb);
		वापस ERR_PTR(-EMSGSIZE);
	पूर्ण
	(*ovs_reply_header)->dp_अगरindex = ovs_header->dp_अगरindex;

	वापस skb;
पूर्ण

अटल bool check_zone_id(पूर्णांक zone_id, u16 *pzone)
अणु
	अगर (zone_id >= 0 && zone_id <= 65535) अणु
		*pzone = (u16)zone_id;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक ovs_ct_limit_set_zone_limit(काष्ठा nlattr *nla_zone_limit,
				       काष्ठा ovs_ct_limit_info *info)
अणु
	काष्ठा ovs_zone_limit *zone_limit;
	पूर्णांक rem;
	u16 zone;

	rem = NLA_ALIGN(nla_len(nla_zone_limit));
	zone_limit = (काष्ठा ovs_zone_limit *)nla_data(nla_zone_limit);

	जबतक (rem >= माप(*zone_limit)) अणु
		अगर (unlikely(zone_limit->zone_id ==
				OVS_ZONE_LIMIT_DEFAULT_ZONE)) अणु
			ovs_lock();
			info->शेष_limit = zone_limit->limit;
			ovs_unlock();
		पूर्ण अन्यथा अगर (unlikely(!check_zone_id(
				zone_limit->zone_id, &zone))) अणु
			OVS_NLERR(true, "zone id is out of range");
		पूर्ण अन्यथा अणु
			काष्ठा ovs_ct_limit *ct_limit;

			ct_limit = kदो_स्मृति(माप(*ct_limit), GFP_KERNEL);
			अगर (!ct_limit)
				वापस -ENOMEM;

			ct_limit->zone = zone;
			ct_limit->limit = zone_limit->limit;

			ovs_lock();
			ct_limit_set(info, ct_limit);
			ovs_unlock();
		पूर्ण
		rem -= NLA_ALIGN(माप(*zone_limit));
		zone_limit = (काष्ठा ovs_zone_limit *)((u8 *)zone_limit +
				NLA_ALIGN(माप(*zone_limit)));
	पूर्ण

	अगर (rem)
		OVS_NLERR(true, "set zone limit has %d unknown bytes", rem);

	वापस 0;
पूर्ण

अटल पूर्णांक ovs_ct_limit_del_zone_limit(काष्ठा nlattr *nla_zone_limit,
				       काष्ठा ovs_ct_limit_info *info)
अणु
	काष्ठा ovs_zone_limit *zone_limit;
	पूर्णांक rem;
	u16 zone;

	rem = NLA_ALIGN(nla_len(nla_zone_limit));
	zone_limit = (काष्ठा ovs_zone_limit *)nla_data(nla_zone_limit);

	जबतक (rem >= माप(*zone_limit)) अणु
		अगर (unlikely(zone_limit->zone_id ==
				OVS_ZONE_LIMIT_DEFAULT_ZONE)) अणु
			ovs_lock();
			info->शेष_limit = OVS_CT_LIMIT_DEFAULT;
			ovs_unlock();
		पूर्ण अन्यथा अगर (unlikely(!check_zone_id(
				zone_limit->zone_id, &zone))) अणु
			OVS_NLERR(true, "zone id is out of range");
		पूर्ण अन्यथा अणु
			ovs_lock();
			ct_limit_del(info, zone);
			ovs_unlock();
		पूर्ण
		rem -= NLA_ALIGN(माप(*zone_limit));
		zone_limit = (काष्ठा ovs_zone_limit *)((u8 *)zone_limit +
				NLA_ALIGN(माप(*zone_limit)));
	पूर्ण

	अगर (rem)
		OVS_NLERR(true, "del zone limit has %d unknown bytes", rem);

	वापस 0;
पूर्ण

अटल पूर्णांक ovs_ct_limit_get_शेष_limit(काष्ठा ovs_ct_limit_info *info,
					  काष्ठा sk_buff *reply)
अणु
	काष्ठा ovs_zone_limit zone_limit = अणु
		.zone_id = OVS_ZONE_LIMIT_DEFAULT_ZONE,
		.limit   = info->शेष_limit,
	पूर्ण;

	वापस nla_put_nohdr(reply, माप(zone_limit), &zone_limit);
पूर्ण

अटल पूर्णांक __ovs_ct_limit_get_zone_limit(काष्ठा net *net,
					 काष्ठा nf_conncount_data *data,
					 u16 zone_id, u32 limit,
					 काष्ठा sk_buff *reply)
अणु
	काष्ठा nf_conntrack_zone ct_zone;
	काष्ठा ovs_zone_limit zone_limit;
	u32 conncount_key = zone_id;

	zone_limit.zone_id = zone_id;
	zone_limit.limit = limit;
	nf_ct_zone_init(&ct_zone, zone_id, NF_CT_DEFAULT_ZONE_सूची, 0);

	zone_limit.count = nf_conncount_count(net, data, &conncount_key, शून्य,
					      &ct_zone);
	वापस nla_put_nohdr(reply, माप(zone_limit), &zone_limit);
पूर्ण

अटल पूर्णांक ovs_ct_limit_get_zone_limit(काष्ठा net *net,
				       काष्ठा nlattr *nla_zone_limit,
				       काष्ठा ovs_ct_limit_info *info,
				       काष्ठा sk_buff *reply)
अणु
	काष्ठा ovs_zone_limit *zone_limit;
	पूर्णांक rem, err;
	u32 limit;
	u16 zone;

	rem = NLA_ALIGN(nla_len(nla_zone_limit));
	zone_limit = (काष्ठा ovs_zone_limit *)nla_data(nla_zone_limit);

	जबतक (rem >= माप(*zone_limit)) अणु
		अगर (unlikely(zone_limit->zone_id ==
				OVS_ZONE_LIMIT_DEFAULT_ZONE)) अणु
			err = ovs_ct_limit_get_शेष_limit(info, reply);
			अगर (err)
				वापस err;
		पूर्ण अन्यथा अगर (unlikely(!check_zone_id(zone_limit->zone_id,
							&zone))) अणु
			OVS_NLERR(true, "zone id is out of range");
		पूर्ण अन्यथा अणु
			rcu_पढ़ो_lock();
			limit = ct_limit_get(info, zone);
			rcu_पढ़ो_unlock();

			err = __ovs_ct_limit_get_zone_limit(
				net, info->data, zone, limit, reply);
			अगर (err)
				वापस err;
		पूर्ण
		rem -= NLA_ALIGN(माप(*zone_limit));
		zone_limit = (काष्ठा ovs_zone_limit *)((u8 *)zone_limit +
				NLA_ALIGN(माप(*zone_limit)));
	पूर्ण

	अगर (rem)
		OVS_NLERR(true, "get zone limit has %d unknown bytes", rem);

	वापस 0;
पूर्ण

अटल पूर्णांक ovs_ct_limit_get_all_zone_limit(काष्ठा net *net,
					   काष्ठा ovs_ct_limit_info *info,
					   काष्ठा sk_buff *reply)
अणु
	काष्ठा ovs_ct_limit *ct_limit;
	काष्ठा hlist_head *head;
	पूर्णांक i, err = 0;

	err = ovs_ct_limit_get_शेष_limit(info, reply);
	अगर (err)
		वापस err;

	rcu_पढ़ो_lock();
	क्रम (i = 0; i < CT_LIMIT_HASH_BUCKETS; ++i) अणु
		head = &info->limits[i];
		hlist_क्रम_each_entry_rcu(ct_limit, head, hlist_node) अणु
			err = __ovs_ct_limit_get_zone_limit(net, info->data,
				ct_limit->zone, ct_limit->limit, reply);
			अगर (err)
				जाओ निकास_err;
		पूर्ण
	पूर्ण

निकास_err:
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण

अटल पूर्णांक ovs_ct_limit_cmd_set(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nlattr **a = info->attrs;
	काष्ठा sk_buff *reply;
	काष्ठा ovs_header *ovs_reply_header;
	काष्ठा ovs_net *ovs_net = net_generic(sock_net(skb->sk), ovs_net_id);
	काष्ठा ovs_ct_limit_info *ct_limit_info = ovs_net->ct_limit_info;
	पूर्णांक err;

	reply = ovs_ct_limit_cmd_reply_start(info, OVS_CT_LIMIT_CMD_SET,
					     &ovs_reply_header);
	अगर (IS_ERR(reply))
		वापस PTR_ERR(reply);

	अगर (!a[OVS_CT_LIMIT_ATTR_ZONE_LIMIT]) अणु
		err = -EINVAL;
		जाओ निकास_err;
	पूर्ण

	err = ovs_ct_limit_set_zone_limit(a[OVS_CT_LIMIT_ATTR_ZONE_LIMIT],
					  ct_limit_info);
	अगर (err)
		जाओ निकास_err;

	अटल_branch_enable(&ovs_ct_limit_enabled);

	genlmsg_end(reply, ovs_reply_header);
	वापस genlmsg_reply(reply, info);

निकास_err:
	nlmsg_मुक्त(reply);
	वापस err;
पूर्ण

अटल पूर्णांक ovs_ct_limit_cmd_del(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nlattr **a = info->attrs;
	काष्ठा sk_buff *reply;
	काष्ठा ovs_header *ovs_reply_header;
	काष्ठा ovs_net *ovs_net = net_generic(sock_net(skb->sk), ovs_net_id);
	काष्ठा ovs_ct_limit_info *ct_limit_info = ovs_net->ct_limit_info;
	पूर्णांक err;

	reply = ovs_ct_limit_cmd_reply_start(info, OVS_CT_LIMIT_CMD_DEL,
					     &ovs_reply_header);
	अगर (IS_ERR(reply))
		वापस PTR_ERR(reply);

	अगर (!a[OVS_CT_LIMIT_ATTR_ZONE_LIMIT]) अणु
		err = -EINVAL;
		जाओ निकास_err;
	पूर्ण

	err = ovs_ct_limit_del_zone_limit(a[OVS_CT_LIMIT_ATTR_ZONE_LIMIT],
					  ct_limit_info);
	अगर (err)
		जाओ निकास_err;

	genlmsg_end(reply, ovs_reply_header);
	वापस genlmsg_reply(reply, info);

निकास_err:
	nlmsg_मुक्त(reply);
	वापस err;
पूर्ण

अटल पूर्णांक ovs_ct_limit_cmd_get(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nlattr **a = info->attrs;
	काष्ठा nlattr *nla_reply;
	काष्ठा sk_buff *reply;
	काष्ठा ovs_header *ovs_reply_header;
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा ovs_net *ovs_net = net_generic(net, ovs_net_id);
	काष्ठा ovs_ct_limit_info *ct_limit_info = ovs_net->ct_limit_info;
	पूर्णांक err;

	reply = ovs_ct_limit_cmd_reply_start(info, OVS_CT_LIMIT_CMD_GET,
					     &ovs_reply_header);
	अगर (IS_ERR(reply))
		वापस PTR_ERR(reply);

	nla_reply = nla_nest_start_noflag(reply, OVS_CT_LIMIT_ATTR_ZONE_LIMIT);
	अगर (!nla_reply) अणु
		err = -EMSGSIZE;
		जाओ निकास_err;
	पूर्ण

	अगर (a[OVS_CT_LIMIT_ATTR_ZONE_LIMIT]) अणु
		err = ovs_ct_limit_get_zone_limit(
			net, a[OVS_CT_LIMIT_ATTR_ZONE_LIMIT], ct_limit_info,
			reply);
		अगर (err)
			जाओ निकास_err;
	पूर्ण अन्यथा अणु
		err = ovs_ct_limit_get_all_zone_limit(net, ct_limit_info,
						      reply);
		अगर (err)
			जाओ निकास_err;
	पूर्ण

	nla_nest_end(reply, nla_reply);
	genlmsg_end(reply, ovs_reply_header);
	वापस genlmsg_reply(reply, info);

निकास_err:
	nlmsg_मुक्त(reply);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा genl_small_ops ct_limit_genl_ops[] = अणु
	अणु .cmd = OVS_CT_LIMIT_CMD_SET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags = GENL_ADMIN_PERM, /* Requires CAP_NET_ADMIN
					   * privilege. */
		.करोit = ovs_ct_limit_cmd_set,
	पूर्ण,
	अणु .cmd = OVS_CT_LIMIT_CMD_DEL,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags = GENL_ADMIN_PERM, /* Requires CAP_NET_ADMIN
					   * privilege. */
		.करोit = ovs_ct_limit_cmd_del,
	पूर्ण,
	अणु .cmd = OVS_CT_LIMIT_CMD_GET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags = 0,		  /* OK क्रम unprivileged users. */
		.करोit = ovs_ct_limit_cmd_get,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा genl_multicast_group ovs_ct_limit_multicast_group = अणु
	.name = OVS_CT_LIMIT_MCGROUP,
पूर्ण;

काष्ठा genl_family dp_ct_limit_genl_family __ro_after_init = अणु
	.hdrsize = माप(काष्ठा ovs_header),
	.name = OVS_CT_LIMIT_FAMILY,
	.version = OVS_CT_LIMIT_VERSION,
	.maxattr = OVS_CT_LIMIT_ATTR_MAX,
	.policy = ct_limit_policy,
	.netnsok = true,
	.parallel_ops = true,
	.small_ops = ct_limit_genl_ops,
	.n_small_ops = ARRAY_SIZE(ct_limit_genl_ops),
	.mcgrps = &ovs_ct_limit_multicast_group,
	.n_mcgrps = 1,
	.module = THIS_MODULE,
पूर्ण;
#पूर्ण_अगर

पूर्णांक ovs_ct_init(काष्ठा net *net)
अणु
	अचिन्हित पूर्णांक n_bits = माप(काष्ठा ovs_key_ct_labels) * BITS_PER_BYTE;
	काष्ठा ovs_net *ovs_net = net_generic(net, ovs_net_id);

	अगर (nf_connlabels_get(net, n_bits - 1)) अणु
		ovs_net->xt_label = false;
		OVS_NLERR(true, "Failed to set connlabel length");
	पूर्ण अन्यथा अणु
		ovs_net->xt_label = true;
	पूर्ण

#अगर	IS_ENABLED(CONFIG_NETFILTER_CONNCOUNT)
	वापस ovs_ct_limit_init(net, ovs_net);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

व्योम ovs_ct_निकास(काष्ठा net *net)
अणु
	काष्ठा ovs_net *ovs_net = net_generic(net, ovs_net_id);

#अगर	IS_ENABLED(CONFIG_NETFILTER_CONNCOUNT)
	ovs_ct_limit_निकास(net, ovs_net);
#पूर्ण_अगर

	अगर (ovs_net->xt_label)
		nf_connlabels_put(net);
पूर्ण
