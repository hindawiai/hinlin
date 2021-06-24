<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2007-2014 Nicira, Inc.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/jhash.h>
#समावेश <linux/delay.h>
#समावेश <linux/समय.स>
#समावेश <linux/etherdevice.h>
#समावेश <linux/genetlink.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/mutex.h>
#समावेश <linux/percpu.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/रुको.h>
#समावेश <यंत्र/भाग64.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/netfilter_bridge.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/list.h>
#समावेश <linux/खोलोvचयन.h>
#समावेश <linux/rculist.h>
#समावेश <linux/dmi.h>
#समावेश <net/genetlink.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>

#समावेश "datapath.h"
#समावेश "flow.h"
#समावेश "flow_table.h"
#समावेश "flow_netlink.h"
#समावेश "meter.h"
#समावेश "vport-internal_dev.h"
#समावेश "vport-netdev.h"

अचिन्हित पूर्णांक ovs_net_id __पढ़ो_mostly;

अटल काष्ठा genl_family dp_packet_genl_family;
अटल काष्ठा genl_family dp_flow_genl_family;
अटल काष्ठा genl_family dp_datapath_genl_family;

अटल स्थिर काष्ठा nla_policy flow_policy[];

अटल स्थिर काष्ठा genl_multicast_group ovs_dp_flow_multicast_group = अणु
	.name = OVS_FLOW_MCGROUP,
पूर्ण;

अटल स्थिर काष्ठा genl_multicast_group ovs_dp_datapath_multicast_group = अणु
	.name = OVS_DATAPATH_MCGROUP,
पूर्ण;

अटल स्थिर काष्ठा genl_multicast_group ovs_dp_vport_multicast_group = अणु
	.name = OVS_VPORT_MCGROUP,
पूर्ण;

/* Check अगर need to build a reply message.
 * OVS userspace sets the NLM_F_ECHO flag अगर it needs the reply. */
अटल bool ovs_must_notअगरy(काष्ठा genl_family *family, काष्ठा genl_info *info,
			    अचिन्हित पूर्णांक group)
अणु
	वापस info->nlhdr->nlmsg_flags & NLM_F_ECHO ||
	       genl_has_listeners(family, genl_info_net(info), group);
पूर्ण

अटल व्योम ovs_notअगरy(काष्ठा genl_family *family,
		       काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	genl_notअगरy(family, skb, info, 0, GFP_KERNEL);
पूर्ण

/**
 * DOC: Locking:
 *
 * All ग_लिखोs e.g. Writes to device state (add/हटाओ datapath, port, set
 * operations on vports, etc.), Writes to other state (flow table
 * modअगरications, set miscellaneous datapath parameters, etc.) are रक्षित
 * by ovs_lock.
 *
 * Reads are रक्षित by RCU.
 *
 * There are a few special हालs (mostly stats) that have their own
 * synchronization but they nest under all of above and करोn't पूर्णांकeract with
 * each other.
 *
 * The RTNL lock nests inside ovs_mutex.
 */

अटल DEFINE_MUTEX(ovs_mutex);

व्योम ovs_lock(व्योम)
अणु
	mutex_lock(&ovs_mutex);
पूर्ण

व्योम ovs_unlock(व्योम)
अणु
	mutex_unlock(&ovs_mutex);
पूर्ण

#अगर_घोषित CONFIG_LOCKDEP
पूर्णांक lockdep_ovsl_is_held(व्योम)
अणु
	अगर (debug_locks)
		वापस lockdep_is_held(&ovs_mutex);
	अन्यथा
		वापस 1;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा vport *new_vport(स्थिर काष्ठा vport_parms *);
अटल पूर्णांक queue_gso_packets(काष्ठा datapath *dp, काष्ठा sk_buff *,
			     स्थिर काष्ठा sw_flow_key *,
			     स्थिर काष्ठा dp_upcall_info *,
			     uपूर्णांक32_t cutlen);
अटल पूर्णांक queue_userspace_packet(काष्ठा datapath *dp, काष्ठा sk_buff *,
				  स्थिर काष्ठा sw_flow_key *,
				  स्थिर काष्ठा dp_upcall_info *,
				  uपूर्णांक32_t cutlen);

अटल व्योम ovs_dp_masks_rebalance(काष्ठा work_काष्ठा *work);

/* Must be called with rcu_पढ़ो_lock or ovs_mutex. */
स्थिर अक्षर *ovs_dp_name(स्थिर काष्ठा datapath *dp)
अणु
	काष्ठा vport *vport = ovs_vport_ovsl_rcu(dp, OVSP_LOCAL);
	वापस ovs_vport_name(vport);
पूर्ण

अटल पूर्णांक get_dpअगरindex(स्थिर काष्ठा datapath *dp)
अणु
	काष्ठा vport *local;
	पूर्णांक अगरindex;

	rcu_पढ़ो_lock();

	local = ovs_vport_rcu(dp, OVSP_LOCAL);
	अगर (local)
		अगरindex = local->dev->अगरindex;
	अन्यथा
		अगरindex = 0;

	rcu_पढ़ो_unlock();

	वापस अगरindex;
पूर्ण

अटल व्योम destroy_dp_rcu(काष्ठा rcu_head *rcu)
अणु
	काष्ठा datapath *dp = container_of(rcu, काष्ठा datapath, rcu);

	ovs_flow_tbl_destroy(&dp->table);
	मुक्त_percpu(dp->stats_percpu);
	kमुक्त(dp->ports);
	ovs_meters_निकास(dp);
	kमुक्त(dp);
पूर्ण

अटल काष्ठा hlist_head *vport_hash_bucket(स्थिर काष्ठा datapath *dp,
					    u16 port_no)
अणु
	वापस &dp->ports[port_no & (DP_VPORT_HASH_BUCKETS - 1)];
पूर्ण

/* Called with ovs_mutex or RCU पढ़ो lock. */
काष्ठा vport *ovs_lookup_vport(स्थिर काष्ठा datapath *dp, u16 port_no)
अणु
	काष्ठा vport *vport;
	काष्ठा hlist_head *head;

	head = vport_hash_bucket(dp, port_no);
	hlist_क्रम_each_entry_rcu(vport, head, dp_hash_node,
				 lockdep_ovsl_is_held()) अणु
		अगर (vport->port_no == port_no)
			वापस vport;
	पूर्ण
	वापस शून्य;
पूर्ण

/* Called with ovs_mutex. */
अटल काष्ठा vport *new_vport(स्थिर काष्ठा vport_parms *parms)
अणु
	काष्ठा vport *vport;

	vport = ovs_vport_add(parms);
	अगर (!IS_ERR(vport)) अणु
		काष्ठा datapath *dp = parms->dp;
		काष्ठा hlist_head *head = vport_hash_bucket(dp, vport->port_no);

		hlist_add_head_rcu(&vport->dp_hash_node, head);
	पूर्ण
	वापस vport;
पूर्ण

व्योम ovs_dp_detach_port(काष्ठा vport *p)
अणु
	ASSERT_OVSL();

	/* First drop references to device. */
	hlist_del_rcu(&p->dp_hash_node);

	/* Then destroy it. */
	ovs_vport_del(p);
पूर्ण

/* Must be called with rcu_पढ़ो_lock. */
व्योम ovs_dp_process_packet(काष्ठा sk_buff *skb, काष्ठा sw_flow_key *key)
अणु
	स्थिर काष्ठा vport *p = OVS_CB(skb)->input_vport;
	काष्ठा datapath *dp = p->dp;
	काष्ठा sw_flow *flow;
	काष्ठा sw_flow_actions *sf_acts;
	काष्ठा dp_stats_percpu *stats;
	u64 *stats_counter;
	u32 n_mask_hit;
	u32 n_cache_hit;
	पूर्णांक error;

	stats = this_cpu_ptr(dp->stats_percpu);

	/* Look up flow. */
	flow = ovs_flow_tbl_lookup_stats(&dp->table, key, skb_get_hash(skb),
					 &n_mask_hit, &n_cache_hit);
	अगर (unlikely(!flow)) अणु
		काष्ठा dp_upcall_info upcall;

		स_रखो(&upcall, 0, माप(upcall));
		upcall.cmd = OVS_PACKET_CMD_MISS;
		upcall.portid = ovs_vport_find_upcall_portid(p, skb);
		upcall.mru = OVS_CB(skb)->mru;
		error = ovs_dp_upcall(dp, skb, key, &upcall, 0);
		अगर (unlikely(error))
			kमुक्त_skb(skb);
		अन्यथा
			consume_skb(skb);
		stats_counter = &stats->n_missed;
		जाओ out;
	पूर्ण

	ovs_flow_stats_update(flow, key->tp.flags, skb);
	sf_acts = rcu_dereference(flow->sf_acts);
	error = ovs_execute_actions(dp, skb, sf_acts, key);
	अगर (unlikely(error))
		net_dbg_ratelimited("ovs: action execution error on datapath %s: %d\n",
				    ovs_dp_name(dp), error);

	stats_counter = &stats->n_hit;

out:
	/* Update datapath statistics. */
	u64_stats_update_begin(&stats->syncp);
	(*stats_counter)++;
	stats->n_mask_hit += n_mask_hit;
	stats->n_cache_hit += n_cache_hit;
	u64_stats_update_end(&stats->syncp);
पूर्ण

पूर्णांक ovs_dp_upcall(काष्ठा datapath *dp, काष्ठा sk_buff *skb,
		  स्थिर काष्ठा sw_flow_key *key,
		  स्थिर काष्ठा dp_upcall_info *upcall_info,
		  uपूर्णांक32_t cutlen)
अणु
	काष्ठा dp_stats_percpu *stats;
	पूर्णांक err;

	अगर (upcall_info->portid == 0) अणु
		err = -ENOTCONN;
		जाओ err;
	पूर्ण

	अगर (!skb_is_gso(skb))
		err = queue_userspace_packet(dp, skb, key, upcall_info, cutlen);
	अन्यथा
		err = queue_gso_packets(dp, skb, key, upcall_info, cutlen);
	अगर (err)
		जाओ err;

	वापस 0;

err:
	stats = this_cpu_ptr(dp->stats_percpu);

	u64_stats_update_begin(&stats->syncp);
	stats->n_lost++;
	u64_stats_update_end(&stats->syncp);

	वापस err;
पूर्ण

अटल पूर्णांक queue_gso_packets(काष्ठा datapath *dp, काष्ठा sk_buff *skb,
			     स्थिर काष्ठा sw_flow_key *key,
			     स्थिर काष्ठा dp_upcall_info *upcall_info,
			     uपूर्णांक32_t cutlen)
अणु
	अचिन्हित पूर्णांक gso_type = skb_shinfo(skb)->gso_type;
	काष्ठा sw_flow_key later_key;
	काष्ठा sk_buff *segs, *nskb;
	पूर्णांक err;

	BUILD_BUG_ON(माप(*OVS_CB(skb)) > SKB_GSO_CB_OFFSET);
	segs = __skb_gso_segment(skb, NETIF_F_SG, false);
	अगर (IS_ERR(segs))
		वापस PTR_ERR(segs);
	अगर (segs == शून्य)
		वापस -EINVAL;

	अगर (gso_type & SKB_GSO_UDP) अणु
		/* The initial flow key extracted by ovs_flow_key_extract()
		 * in this हाल is क्रम a first fragment, so we need to
		 * properly mark later fragments.
		 */
		later_key = *key;
		later_key.ip.frag = OVS_FRAG_TYPE_LATER;
	पूर्ण

	/* Queue all of the segments. */
	skb_list_walk_safe(segs, skb, nskb) अणु
		अगर (gso_type & SKB_GSO_UDP && skb != segs)
			key = &later_key;

		err = queue_userspace_packet(dp, skb, key, upcall_info, cutlen);
		अगर (err)
			अवरोध;

	पूर्ण

	/* Free all of the segments. */
	skb_list_walk_safe(segs, skb, nskb) अणु
		अगर (err)
			kमुक्त_skb(skb);
		अन्यथा
			consume_skb(skb);
	पूर्ण
	वापस err;
पूर्ण

अटल माप_प्रकार upcall_msg_size(स्थिर काष्ठा dp_upcall_info *upcall_info,
			      अचिन्हित पूर्णांक hdrlen, पूर्णांक actions_attrlen)
अणु
	माप_प्रकार size = NLMSG_ALIGN(माप(काष्ठा ovs_header))
		+ nla_total_size(hdrlen) /* OVS_PACKET_ATTR_PACKET */
		+ nla_total_size(ovs_key_attr_size()) /* OVS_PACKET_ATTR_KEY */
		+ nla_total_size(माप(अचिन्हित पूर्णांक)) /* OVS_PACKET_ATTR_LEN */
		+ nla_total_size(माप(u64)); /* OVS_PACKET_ATTR_HASH */

	/* OVS_PACKET_ATTR_USERDATA */
	अगर (upcall_info->userdata)
		size += NLA_ALIGN(upcall_info->userdata->nla_len);

	/* OVS_PACKET_ATTR_EGRESS_TUN_KEY */
	अगर (upcall_info->egress_tun_info)
		size += nla_total_size(ovs_tun_key_attr_size());

	/* OVS_PACKET_ATTR_ACTIONS */
	अगर (upcall_info->actions_len)
		size += nla_total_size(actions_attrlen);

	/* OVS_PACKET_ATTR_MRU */
	अगर (upcall_info->mru)
		size += nla_total_size(माप(upcall_info->mru));

	वापस size;
पूर्ण

अटल व्योम pad_packet(काष्ठा datapath *dp, काष्ठा sk_buff *skb)
अणु
	अगर (!(dp->user_features & OVS_DP_F_UNALIGNED)) अणु
		माप_प्रकार plen = NLA_ALIGN(skb->len) - skb->len;

		अगर (plen > 0)
			skb_put_zero(skb, plen);
	पूर्ण
पूर्ण

अटल पूर्णांक queue_userspace_packet(काष्ठा datapath *dp, काष्ठा sk_buff *skb,
				  स्थिर काष्ठा sw_flow_key *key,
				  स्थिर काष्ठा dp_upcall_info *upcall_info,
				  uपूर्णांक32_t cutlen)
अणु
	काष्ठा ovs_header *upcall;
	काष्ठा sk_buff *nskb = शून्य;
	काष्ठा sk_buff *user_skb = शून्य; /* to be queued to userspace */
	काष्ठा nlattr *nla;
	माप_प्रकार len;
	अचिन्हित पूर्णांक hlen;
	पूर्णांक err, dp_अगरindex;
	u64 hash;

	dp_अगरindex = get_dpअगरindex(dp);
	अगर (!dp_अगरindex)
		वापस -ENODEV;

	अगर (skb_vlan_tag_present(skb)) अणु
		nskb = skb_clone(skb, GFP_ATOMIC);
		अगर (!nskb)
			वापस -ENOMEM;

		nskb = __vlan_hwaccel_push_inside(nskb);
		अगर (!nskb)
			वापस -ENOMEM;

		skb = nskb;
	पूर्ण

	अगर (nla_attr_size(skb->len) > अच_लघु_उच्च) अणु
		err = -EFBIG;
		जाओ out;
	पूर्ण

	/* Complete checksum अगर needed */
	अगर (skb->ip_summed == CHECKSUM_PARTIAL &&
	    (err = skb_csum_hwoffload_help(skb, 0)))
		जाओ out;

	/* Older versions of OVS user space enक्रमce alignment of the last
	 * Netlink attribute to NLA_ALIGNTO which would require extensive
	 * padding logic. Only perक्रमm zerocopy अगर padding is not required.
	 */
	अगर (dp->user_features & OVS_DP_F_UNALIGNED)
		hlen = skb_zerocopy_headlen(skb);
	अन्यथा
		hlen = skb->len;

	len = upcall_msg_size(upcall_info, hlen - cutlen,
			      OVS_CB(skb)->acts_origlen);
	user_skb = genlmsg_new(len, GFP_ATOMIC);
	अगर (!user_skb) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	upcall = genlmsg_put(user_skb, 0, 0, &dp_packet_genl_family,
			     0, upcall_info->cmd);
	अगर (!upcall) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण
	upcall->dp_अगरindex = dp_अगरindex;

	err = ovs_nla_put_key(key, key, OVS_PACKET_ATTR_KEY, false, user_skb);
	अगर (err)
		जाओ out;

	अगर (upcall_info->userdata)
		__nla_put(user_skb, OVS_PACKET_ATTR_USERDATA,
			  nla_len(upcall_info->userdata),
			  nla_data(upcall_info->userdata));

	अगर (upcall_info->egress_tun_info) अणु
		nla = nla_nest_start_noflag(user_skb,
					    OVS_PACKET_ATTR_EGRESS_TUN_KEY);
		अगर (!nla) अणु
			err = -EMSGSIZE;
			जाओ out;
		पूर्ण
		err = ovs_nla_put_tunnel_info(user_skb,
					      upcall_info->egress_tun_info);
		अगर (err)
			जाओ out;

		nla_nest_end(user_skb, nla);
	पूर्ण

	अगर (upcall_info->actions_len) अणु
		nla = nla_nest_start_noflag(user_skb, OVS_PACKET_ATTR_ACTIONS);
		अगर (!nla) अणु
			err = -EMSGSIZE;
			जाओ out;
		पूर्ण
		err = ovs_nla_put_actions(upcall_info->actions,
					  upcall_info->actions_len,
					  user_skb);
		अगर (!err)
			nla_nest_end(user_skb, nla);
		अन्यथा
			nla_nest_cancel(user_skb, nla);
	पूर्ण

	/* Add OVS_PACKET_ATTR_MRU */
	अगर (upcall_info->mru &&
	    nla_put_u16(user_skb, OVS_PACKET_ATTR_MRU, upcall_info->mru)) अणु
		err = -ENOBUFS;
		जाओ out;
	पूर्ण

	/* Add OVS_PACKET_ATTR_LEN when packet is truncated */
	अगर (cutlen > 0 &&
	    nla_put_u32(user_skb, OVS_PACKET_ATTR_LEN, skb->len)) अणु
		err = -ENOBUFS;
		जाओ out;
	पूर्ण

	/* Add OVS_PACKET_ATTR_HASH */
	hash = skb_get_hash_raw(skb);
	अगर (skb->sw_hash)
		hash |= OVS_PACKET_HASH_SW_BIT;

	अगर (skb->l4_hash)
		hash |= OVS_PACKET_HASH_L4_BIT;

	अगर (nla_put(user_skb, OVS_PACKET_ATTR_HASH, माप (u64), &hash)) अणु
		err = -ENOBUFS;
		जाओ out;
	पूर्ण

	/* Only reserve room क्रम attribute header, packet data is added
	 * in skb_zerocopy() */
	अगर (!(nla = nla_reserve(user_skb, OVS_PACKET_ATTR_PACKET, 0))) अणु
		err = -ENOBUFS;
		जाओ out;
	पूर्ण
	nla->nla_len = nla_attr_size(skb->len - cutlen);

	err = skb_zerocopy(user_skb, skb, skb->len - cutlen, hlen);
	अगर (err)
		जाओ out;

	/* Pad OVS_PACKET_ATTR_PACKET अगर linear copy was perक्रमmed */
	pad_packet(dp, user_skb);

	((काष्ठा nlmsghdr *) user_skb->data)->nlmsg_len = user_skb->len;

	err = genlmsg_unicast(ovs_dp_get_net(dp), user_skb, upcall_info->portid);
	user_skb = शून्य;
out:
	अगर (err)
		skb_tx_error(skb);
	kमुक्त_skb(user_skb);
	kमुक्त_skb(nskb);
	वापस err;
पूर्ण

अटल पूर्णांक ovs_packet_cmd_execute(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा ovs_header *ovs_header = info->userhdr;
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा nlattr **a = info->attrs;
	काष्ठा sw_flow_actions *acts;
	काष्ठा sk_buff *packet;
	काष्ठा sw_flow *flow;
	काष्ठा sw_flow_actions *sf_acts;
	काष्ठा datapath *dp;
	काष्ठा vport *input_vport;
	u16 mru = 0;
	u64 hash;
	पूर्णांक len;
	पूर्णांक err;
	bool log = !a[OVS_PACKET_ATTR_PROBE];

	err = -EINVAL;
	अगर (!a[OVS_PACKET_ATTR_PACKET] || !a[OVS_PACKET_ATTR_KEY] ||
	    !a[OVS_PACKET_ATTR_ACTIONS])
		जाओ err;

	len = nla_len(a[OVS_PACKET_ATTR_PACKET]);
	packet = __dev_alloc_skb(NET_IP_ALIGN + len, GFP_KERNEL);
	err = -ENOMEM;
	अगर (!packet)
		जाओ err;
	skb_reserve(packet, NET_IP_ALIGN);

	nla_स_नकल(__skb_put(packet, len), a[OVS_PACKET_ATTR_PACKET], len);

	/* Set packet's mru */
	अगर (a[OVS_PACKET_ATTR_MRU]) अणु
		mru = nla_get_u16(a[OVS_PACKET_ATTR_MRU]);
		packet->ignore_df = 1;
	पूर्ण
	OVS_CB(packet)->mru = mru;

	अगर (a[OVS_PACKET_ATTR_HASH]) अणु
		hash = nla_get_u64(a[OVS_PACKET_ATTR_HASH]);

		__skb_set_hash(packet, hash & 0xFFFFFFFFULL,
			       !!(hash & OVS_PACKET_HASH_SW_BIT),
			       !!(hash & OVS_PACKET_HASH_L4_BIT));
	पूर्ण

	/* Build an sw_flow क्रम sending this packet. */
	flow = ovs_flow_alloc();
	err = PTR_ERR(flow);
	अगर (IS_ERR(flow))
		जाओ err_kमुक्त_skb;

	err = ovs_flow_key_extract_userspace(net, a[OVS_PACKET_ATTR_KEY],
					     packet, &flow->key, log);
	अगर (err)
		जाओ err_flow_मुक्त;

	err = ovs_nla_copy_actions(net, a[OVS_PACKET_ATTR_ACTIONS],
				   &flow->key, &acts, log);
	अगर (err)
		जाओ err_flow_मुक्त;

	rcu_assign_poपूर्णांकer(flow->sf_acts, acts);
	packet->priority = flow->key.phy.priority;
	packet->mark = flow->key.phy.skb_mark;

	rcu_पढ़ो_lock();
	dp = get_dp_rcu(net, ovs_header->dp_अगरindex);
	err = -ENODEV;
	अगर (!dp)
		जाओ err_unlock;

	input_vport = ovs_vport_rcu(dp, flow->key.phy.in_port);
	अगर (!input_vport)
		input_vport = ovs_vport_rcu(dp, OVSP_LOCAL);

	अगर (!input_vport)
		जाओ err_unlock;

	packet->dev = input_vport->dev;
	OVS_CB(packet)->input_vport = input_vport;
	sf_acts = rcu_dereference(flow->sf_acts);

	local_bh_disable();
	err = ovs_execute_actions(dp, packet, sf_acts, &flow->key);
	local_bh_enable();
	rcu_पढ़ो_unlock();

	ovs_flow_मुक्त(flow, false);
	वापस err;

err_unlock:
	rcu_पढ़ो_unlock();
err_flow_मुक्त:
	ovs_flow_मुक्त(flow, false);
err_kमुक्त_skb:
	kमुक्त_skb(packet);
err:
	वापस err;
पूर्ण

अटल स्थिर काष्ठा nla_policy packet_policy[OVS_PACKET_ATTR_MAX + 1] = अणु
	[OVS_PACKET_ATTR_PACKET] = अणु .len = ETH_HLEN पूर्ण,
	[OVS_PACKET_ATTR_KEY] = अणु .type = NLA_NESTED पूर्ण,
	[OVS_PACKET_ATTR_ACTIONS] = अणु .type = NLA_NESTED पूर्ण,
	[OVS_PACKET_ATTR_PROBE] = अणु .type = NLA_FLAG पूर्ण,
	[OVS_PACKET_ATTR_MRU] = अणु .type = NLA_U16 पूर्ण,
	[OVS_PACKET_ATTR_HASH] = अणु .type = NLA_U64 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा genl_small_ops dp_packet_genl_ops[] = अणु
	अणु .cmd = OVS_PACKET_CMD_EXECUTE,
	  .validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
	  .flags = GENL_UNS_ADMIN_PERM, /* Requires CAP_NET_ADMIN privilege. */
	  .करोit = ovs_packet_cmd_execute
	पूर्ण
पूर्ण;

अटल काष्ठा genl_family dp_packet_genl_family __ro_after_init = अणु
	.hdrsize = माप(काष्ठा ovs_header),
	.name = OVS_PACKET_FAMILY,
	.version = OVS_PACKET_VERSION,
	.maxattr = OVS_PACKET_ATTR_MAX,
	.policy = packet_policy,
	.netnsok = true,
	.parallel_ops = true,
	.small_ops = dp_packet_genl_ops,
	.n_small_ops = ARRAY_SIZE(dp_packet_genl_ops),
	.module = THIS_MODULE,
पूर्ण;

अटल व्योम get_dp_stats(स्थिर काष्ठा datapath *dp, काष्ठा ovs_dp_stats *stats,
			 काष्ठा ovs_dp_megaflow_stats *mega_stats)
अणु
	पूर्णांक i;

	स_रखो(mega_stats, 0, माप(*mega_stats));

	stats->n_flows = ovs_flow_tbl_count(&dp->table);
	mega_stats->n_masks = ovs_flow_tbl_num_masks(&dp->table);

	stats->n_hit = stats->n_missed = stats->n_lost = 0;

	क्रम_each_possible_cpu(i) अणु
		स्थिर काष्ठा dp_stats_percpu *percpu_stats;
		काष्ठा dp_stats_percpu local_stats;
		अचिन्हित पूर्णांक start;

		percpu_stats = per_cpu_ptr(dp->stats_percpu, i);

		करो अणु
			start = u64_stats_fetch_begin_irq(&percpu_stats->syncp);
			local_stats = *percpu_stats;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&percpu_stats->syncp, start));

		stats->n_hit += local_stats.n_hit;
		stats->n_missed += local_stats.n_missed;
		stats->n_lost += local_stats.n_lost;
		mega_stats->n_mask_hit += local_stats.n_mask_hit;
		mega_stats->n_cache_hit += local_stats.n_cache_hit;
	पूर्ण
पूर्ण

अटल bool should_fill_key(स्थिर काष्ठा sw_flow_id *sfid, uपूर्णांक32_t ufid_flags)
अणु
	वापस ovs_identअगरier_is_ufid(sfid) &&
	       !(ufid_flags & OVS_UFID_F_OMIT_KEY);
पूर्ण

अटल bool should_fill_mask(uपूर्णांक32_t ufid_flags)
अणु
	वापस !(ufid_flags & OVS_UFID_F_OMIT_MASK);
पूर्ण

अटल bool should_fill_actions(uपूर्णांक32_t ufid_flags)
अणु
	वापस !(ufid_flags & OVS_UFID_F_OMIT_ACTIONS);
पूर्ण

अटल माप_प्रकार ovs_flow_cmd_msg_size(स्थिर काष्ठा sw_flow_actions *acts,
				    स्थिर काष्ठा sw_flow_id *sfid,
				    uपूर्णांक32_t ufid_flags)
अणु
	माप_प्रकार len = NLMSG_ALIGN(माप(काष्ठा ovs_header));

	/* OVS_FLOW_ATTR_UFID, or unmasked flow key as fallback
	 * see ovs_nla_put_identअगरier()
	 */
	अगर (sfid && ovs_identअगरier_is_ufid(sfid))
		len += nla_total_size(sfid->ufid_len);
	अन्यथा
		len += nla_total_size(ovs_key_attr_size());

	/* OVS_FLOW_ATTR_KEY */
	अगर (!sfid || should_fill_key(sfid, ufid_flags))
		len += nla_total_size(ovs_key_attr_size());

	/* OVS_FLOW_ATTR_MASK */
	अगर (should_fill_mask(ufid_flags))
		len += nla_total_size(ovs_key_attr_size());

	/* OVS_FLOW_ATTR_ACTIONS */
	अगर (should_fill_actions(ufid_flags))
		len += nla_total_size(acts->orig_len);

	वापस len
		+ nla_total_size_64bit(माप(काष्ठा ovs_flow_stats)) /* OVS_FLOW_ATTR_STATS */
		+ nla_total_size(1) /* OVS_FLOW_ATTR_TCP_FLAGS */
		+ nla_total_size_64bit(8); /* OVS_FLOW_ATTR_USED */
पूर्ण

/* Called with ovs_mutex or RCU पढ़ो lock. */
अटल पूर्णांक ovs_flow_cmd_fill_stats(स्थिर काष्ठा sw_flow *flow,
				   काष्ठा sk_buff *skb)
अणु
	काष्ठा ovs_flow_stats stats;
	__be16 tcp_flags;
	अचिन्हित दीर्घ used;

	ovs_flow_stats_get(flow, &stats, &used, &tcp_flags);

	अगर (used &&
	    nla_put_u64_64bit(skb, OVS_FLOW_ATTR_USED, ovs_flow_used_समय(used),
			      OVS_FLOW_ATTR_PAD))
		वापस -EMSGSIZE;

	अगर (stats.n_packets &&
	    nla_put_64bit(skb, OVS_FLOW_ATTR_STATS,
			  माप(काष्ठा ovs_flow_stats), &stats,
			  OVS_FLOW_ATTR_PAD))
		वापस -EMSGSIZE;

	अगर ((u8)ntohs(tcp_flags) &&
	     nla_put_u8(skb, OVS_FLOW_ATTR_TCP_FLAGS, (u8)ntohs(tcp_flags)))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

/* Called with ovs_mutex or RCU पढ़ो lock. */
अटल पूर्णांक ovs_flow_cmd_fill_actions(स्थिर काष्ठा sw_flow *flow,
				     काष्ठा sk_buff *skb, पूर्णांक skb_orig_len)
अणु
	काष्ठा nlattr *start;
	पूर्णांक err;

	/* If OVS_FLOW_ATTR_ACTIONS करोesn't fit, skip dumping the actions अगर
	 * this is the first flow to be dumped पूर्णांकo 'skb'.  This is unusual क्रम
	 * Netlink but inभागidual action lists can be दीर्घer than
	 * NLMSG_GOODSIZE and thus entirely undumpable अगर we didn't करो this.
	 * The userspace caller can always fetch the actions separately अगर it
	 * really wants them.  (Most userspace callers in fact करोn't care.)
	 *
	 * This can only fail क्रम dump operations because the skb is always
	 * properly sized क्रम single flows.
	 */
	start = nla_nest_start_noflag(skb, OVS_FLOW_ATTR_ACTIONS);
	अगर (start) अणु
		स्थिर काष्ठा sw_flow_actions *sf_acts;

		sf_acts = rcu_dereference_ovsl(flow->sf_acts);
		err = ovs_nla_put_actions(sf_acts->actions,
					  sf_acts->actions_len, skb);

		अगर (!err)
			nla_nest_end(skb, start);
		अन्यथा अणु
			अगर (skb_orig_len)
				वापस err;

			nla_nest_cancel(skb, start);
		पूर्ण
	पूर्ण अन्यथा अगर (skb_orig_len) अणु
		वापस -EMSGSIZE;
	पूर्ण

	वापस 0;
पूर्ण

/* Called with ovs_mutex or RCU पढ़ो lock. */
अटल पूर्णांक ovs_flow_cmd_fill_info(स्थिर काष्ठा sw_flow *flow, पूर्णांक dp_अगरindex,
				  काष्ठा sk_buff *skb, u32 portid,
				  u32 seq, u32 flags, u8 cmd, u32 ufid_flags)
अणु
	स्थिर पूर्णांक skb_orig_len = skb->len;
	काष्ठा ovs_header *ovs_header;
	पूर्णांक err;

	ovs_header = genlmsg_put(skb, portid, seq, &dp_flow_genl_family,
				 flags, cmd);
	अगर (!ovs_header)
		वापस -EMSGSIZE;

	ovs_header->dp_अगरindex = dp_अगरindex;

	err = ovs_nla_put_identअगरier(flow, skb);
	अगर (err)
		जाओ error;

	अगर (should_fill_key(&flow->id, ufid_flags)) अणु
		err = ovs_nla_put_masked_key(flow, skb);
		अगर (err)
			जाओ error;
	पूर्ण

	अगर (should_fill_mask(ufid_flags)) अणु
		err = ovs_nla_put_mask(flow, skb);
		अगर (err)
			जाओ error;
	पूर्ण

	err = ovs_flow_cmd_fill_stats(flow, skb);
	अगर (err)
		जाओ error;

	अगर (should_fill_actions(ufid_flags)) अणु
		err = ovs_flow_cmd_fill_actions(flow, skb, skb_orig_len);
		अगर (err)
			जाओ error;
	पूर्ण

	genlmsg_end(skb, ovs_header);
	वापस 0;

error:
	genlmsg_cancel(skb, ovs_header);
	वापस err;
पूर्ण

/* May not be called with RCU पढ़ो lock. */
अटल काष्ठा sk_buff *ovs_flow_cmd_alloc_info(स्थिर काष्ठा sw_flow_actions *acts,
					       स्थिर काष्ठा sw_flow_id *sfid,
					       काष्ठा genl_info *info,
					       bool always,
					       uपूर्णांक32_t ufid_flags)
अणु
	काष्ठा sk_buff *skb;
	माप_प्रकार len;

	अगर (!always && !ovs_must_notअगरy(&dp_flow_genl_family, info, 0))
		वापस शून्य;

	len = ovs_flow_cmd_msg_size(acts, sfid, ufid_flags);
	skb = genlmsg_new(len, GFP_KERNEL);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	वापस skb;
पूर्ण

/* Called with ovs_mutex. */
अटल काष्ठा sk_buff *ovs_flow_cmd_build_info(स्थिर काष्ठा sw_flow *flow,
					       पूर्णांक dp_अगरindex,
					       काष्ठा genl_info *info, u8 cmd,
					       bool always, u32 ufid_flags)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक retval;

	skb = ovs_flow_cmd_alloc_info(ovsl_dereference(flow->sf_acts),
				      &flow->id, info, always, ufid_flags);
	अगर (IS_ERR_OR_शून्य(skb))
		वापस skb;

	retval = ovs_flow_cmd_fill_info(flow, dp_अगरindex, skb,
					info->snd_portid, info->snd_seq, 0,
					cmd, ufid_flags);
	अगर (WARN_ON_ONCE(retval < 0)) अणु
		kमुक्त_skb(skb);
		skb = ERR_PTR(retval);
	पूर्ण
	वापस skb;
पूर्ण

अटल पूर्णांक ovs_flow_cmd_new(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा nlattr **a = info->attrs;
	काष्ठा ovs_header *ovs_header = info->userhdr;
	काष्ठा sw_flow *flow = शून्य, *new_flow;
	काष्ठा sw_flow_mask mask;
	काष्ठा sk_buff *reply;
	काष्ठा datapath *dp;
	काष्ठा sw_flow_actions *acts;
	काष्ठा sw_flow_match match;
	u32 ufid_flags = ovs_nla_get_ufid_flags(a[OVS_FLOW_ATTR_UFID_FLAGS]);
	पूर्णांक error;
	bool log = !a[OVS_FLOW_ATTR_PROBE];

	/* Must have key and actions. */
	error = -EINVAL;
	अगर (!a[OVS_FLOW_ATTR_KEY]) अणु
		OVS_NLERR(log, "Flow key attr not present in new flow.");
		जाओ error;
	पूर्ण
	अगर (!a[OVS_FLOW_ATTR_ACTIONS]) अणु
		OVS_NLERR(log, "Flow actions attr not present in new flow.");
		जाओ error;
	पूर्ण

	/* Most of the समय we need to allocate a new flow, करो it beक्रमe
	 * locking.
	 */
	new_flow = ovs_flow_alloc();
	अगर (IS_ERR(new_flow)) अणु
		error = PTR_ERR(new_flow);
		जाओ error;
	पूर्ण

	/* Extract key. */
	ovs_match_init(&match, &new_flow->key, false, &mask);
	error = ovs_nla_get_match(net, &match, a[OVS_FLOW_ATTR_KEY],
				  a[OVS_FLOW_ATTR_MASK], log);
	अगर (error)
		जाओ err_kमुक्त_flow;

	/* Extract flow identअगरier. */
	error = ovs_nla_get_identअगरier(&new_flow->id, a[OVS_FLOW_ATTR_UFID],
				       &new_flow->key, log);
	अगर (error)
		जाओ err_kमुक्त_flow;

	/* unmasked key is needed to match when ufid is not used. */
	अगर (ovs_identअगरier_is_key(&new_flow->id))
		match.key = new_flow->id.unmasked_key;

	ovs_flow_mask_key(&new_flow->key, &new_flow->key, true, &mask);

	/* Validate actions. */
	error = ovs_nla_copy_actions(net, a[OVS_FLOW_ATTR_ACTIONS],
				     &new_flow->key, &acts, log);
	अगर (error) अणु
		OVS_NLERR(log, "Flow actions may not be safe on all matching packets.");
		जाओ err_kमुक्त_flow;
	पूर्ण

	reply = ovs_flow_cmd_alloc_info(acts, &new_flow->id, info, false,
					ufid_flags);
	अगर (IS_ERR(reply)) अणु
		error = PTR_ERR(reply);
		जाओ err_kमुक्त_acts;
	पूर्ण

	ovs_lock();
	dp = get_dp(net, ovs_header->dp_अगरindex);
	अगर (unlikely(!dp)) अणु
		error = -ENODEV;
		जाओ err_unlock_ovs;
	पूर्ण

	/* Check अगर this is a duplicate flow */
	अगर (ovs_identअगरier_is_ufid(&new_flow->id))
		flow = ovs_flow_tbl_lookup_ufid(&dp->table, &new_flow->id);
	अगर (!flow)
		flow = ovs_flow_tbl_lookup(&dp->table, &new_flow->key);
	अगर (likely(!flow)) अणु
		rcu_assign_poपूर्णांकer(new_flow->sf_acts, acts);

		/* Put flow in bucket. */
		error = ovs_flow_tbl_insert(&dp->table, new_flow, &mask);
		अगर (unlikely(error)) अणु
			acts = शून्य;
			जाओ err_unlock_ovs;
		पूर्ण

		अगर (unlikely(reply)) अणु
			error = ovs_flow_cmd_fill_info(new_flow,
						       ovs_header->dp_अगरindex,
						       reply, info->snd_portid,
						       info->snd_seq, 0,
						       OVS_FLOW_CMD_NEW,
						       ufid_flags);
			BUG_ON(error < 0);
		पूर्ण
		ovs_unlock();
	पूर्ण अन्यथा अणु
		काष्ठा sw_flow_actions *old_acts;

		/* Bail out अगर we're not allowed to modअगरy an existing flow.
		 * We accept NLM_F_CREATE in place of the पूर्णांकended NLM_F_EXCL
		 * because Generic Netlink treats the latter as a dump
		 * request.  We also accept NLM_F_EXCL in हाल that bug ever
		 * माला_लो fixed.
		 */
		अगर (unlikely(info->nlhdr->nlmsg_flags & (NLM_F_CREATE
							 | NLM_F_EXCL))) अणु
			error = -EEXIST;
			जाओ err_unlock_ovs;
		पूर्ण
		/* The flow identअगरier has to be the same क्रम flow updates.
		 * Look क्रम any overlapping flow.
		 */
		अगर (unlikely(!ovs_flow_cmp(flow, &match))) अणु
			अगर (ovs_identअगरier_is_key(&flow->id))
				flow = ovs_flow_tbl_lookup_exact(&dp->table,
								 &match);
			अन्यथा /* UFID matches but key is dअगरferent */
				flow = शून्य;
			अगर (!flow) अणु
				error = -ENOENT;
				जाओ err_unlock_ovs;
			पूर्ण
		पूर्ण
		/* Update actions. */
		old_acts = ovsl_dereference(flow->sf_acts);
		rcu_assign_poपूर्णांकer(flow->sf_acts, acts);

		अगर (unlikely(reply)) अणु
			error = ovs_flow_cmd_fill_info(flow,
						       ovs_header->dp_अगरindex,
						       reply, info->snd_portid,
						       info->snd_seq, 0,
						       OVS_FLOW_CMD_NEW,
						       ufid_flags);
			BUG_ON(error < 0);
		पूर्ण
		ovs_unlock();

		ovs_nla_मुक्त_flow_actions_rcu(old_acts);
		ovs_flow_मुक्त(new_flow, false);
	पूर्ण

	अगर (reply)
		ovs_notअगरy(&dp_flow_genl_family, reply, info);
	वापस 0;

err_unlock_ovs:
	ovs_unlock();
	kमुक्त_skb(reply);
err_kमुक्त_acts:
	ovs_nla_मुक्त_flow_actions(acts);
err_kमुक्त_flow:
	ovs_flow_मुक्त(new_flow, false);
error:
	वापस error;
पूर्ण

/* Factor out action copy to aव्योम "Wframe-larger-than=1024" warning. */
अटल noअंतरभूत_क्रम_stack
काष्ठा sw_flow_actions *get_flow_actions(काष्ठा net *net,
					 स्थिर काष्ठा nlattr *a,
					 स्थिर काष्ठा sw_flow_key *key,
					 स्थिर काष्ठा sw_flow_mask *mask,
					 bool log)
अणु
	काष्ठा sw_flow_actions *acts;
	काष्ठा sw_flow_key masked_key;
	पूर्णांक error;

	ovs_flow_mask_key(&masked_key, key, true, mask);
	error = ovs_nla_copy_actions(net, a, &masked_key, &acts, log);
	अगर (error) अणु
		OVS_NLERR(log,
			  "Actions may not be safe on all matching packets");
		वापस ERR_PTR(error);
	पूर्ण

	वापस acts;
पूर्ण

/* Factor out match-init and action-copy to aव्योम
 * "Wframe-larger-than=1024" warning. Because mask is only
 * used to get actions, we new a function to save some
 * stack space.
 *
 * If there are not key and action attrs, we वापस 0
 * directly. In the हाल, the caller will also not use the
 * match as beक्रमe. If there is action attr, we try to get
 * actions and save them to *acts. Beक्रमe वापसing from
 * the function, we reset the match->mask poपूर्णांकer. Because
 * we should not to वापस match object with dangling reference
 * to mask.
 * */
अटल noअंतरभूत_क्रम_stack पूर्णांक
ovs_nla_init_match_and_action(काष्ठा net *net,
			      काष्ठा sw_flow_match *match,
			      काष्ठा sw_flow_key *key,
			      काष्ठा nlattr **a,
			      काष्ठा sw_flow_actions **acts,
			      bool log)
अणु
	काष्ठा sw_flow_mask mask;
	पूर्णांक error = 0;

	अगर (a[OVS_FLOW_ATTR_KEY]) अणु
		ovs_match_init(match, key, true, &mask);
		error = ovs_nla_get_match(net, match, a[OVS_FLOW_ATTR_KEY],
					  a[OVS_FLOW_ATTR_MASK], log);
		अगर (error)
			जाओ error;
	पूर्ण

	अगर (a[OVS_FLOW_ATTR_ACTIONS]) अणु
		अगर (!a[OVS_FLOW_ATTR_KEY]) अणु
			OVS_NLERR(log,
				  "Flow key attribute not present in set flow.");
			error = -EINVAL;
			जाओ error;
		पूर्ण

		*acts = get_flow_actions(net, a[OVS_FLOW_ATTR_ACTIONS], key,
					 &mask, log);
		अगर (IS_ERR(*acts)) अणु
			error = PTR_ERR(*acts);
			जाओ error;
		पूर्ण
	पूर्ण

	/* On success, error is 0. */
error:
	match->mask = शून्य;
	वापस error;
पूर्ण

अटल पूर्णांक ovs_flow_cmd_set(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा nlattr **a = info->attrs;
	काष्ठा ovs_header *ovs_header = info->userhdr;
	काष्ठा sw_flow_key key;
	काष्ठा sw_flow *flow;
	काष्ठा sk_buff *reply = शून्य;
	काष्ठा datapath *dp;
	काष्ठा sw_flow_actions *old_acts = शून्य, *acts = शून्य;
	काष्ठा sw_flow_match match;
	काष्ठा sw_flow_id sfid;
	u32 ufid_flags = ovs_nla_get_ufid_flags(a[OVS_FLOW_ATTR_UFID_FLAGS]);
	पूर्णांक error = 0;
	bool log = !a[OVS_FLOW_ATTR_PROBE];
	bool ufid_present;

	ufid_present = ovs_nla_get_ufid(&sfid, a[OVS_FLOW_ATTR_UFID], log);
	अगर (!a[OVS_FLOW_ATTR_KEY] && !ufid_present) अणु
		OVS_NLERR(log,
			  "Flow set message rejected, Key attribute missing.");
		वापस -EINVAL;
	पूर्ण

	error = ovs_nla_init_match_and_action(net, &match, &key, a,
					      &acts, log);
	अगर (error)
		जाओ error;

	अगर (acts) अणु
		/* Can allocate beक्रमe locking अगर have acts. */
		reply = ovs_flow_cmd_alloc_info(acts, &sfid, info, false,
						ufid_flags);
		अगर (IS_ERR(reply)) अणु
			error = PTR_ERR(reply);
			जाओ err_kमुक्त_acts;
		पूर्ण
	पूर्ण

	ovs_lock();
	dp = get_dp(net, ovs_header->dp_अगरindex);
	अगर (unlikely(!dp)) अणु
		error = -ENODEV;
		जाओ err_unlock_ovs;
	पूर्ण
	/* Check that the flow exists. */
	अगर (ufid_present)
		flow = ovs_flow_tbl_lookup_ufid(&dp->table, &sfid);
	अन्यथा
		flow = ovs_flow_tbl_lookup_exact(&dp->table, &match);
	अगर (unlikely(!flow)) अणु
		error = -ENOENT;
		जाओ err_unlock_ovs;
	पूर्ण

	/* Update actions, अगर present. */
	अगर (likely(acts)) अणु
		old_acts = ovsl_dereference(flow->sf_acts);
		rcu_assign_poपूर्णांकer(flow->sf_acts, acts);

		अगर (unlikely(reply)) अणु
			error = ovs_flow_cmd_fill_info(flow,
						       ovs_header->dp_अगरindex,
						       reply, info->snd_portid,
						       info->snd_seq, 0,
						       OVS_FLOW_CMD_SET,
						       ufid_flags);
			BUG_ON(error < 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Could not alloc without acts beक्रमe locking. */
		reply = ovs_flow_cmd_build_info(flow, ovs_header->dp_अगरindex,
						info, OVS_FLOW_CMD_SET, false,
						ufid_flags);

		अगर (IS_ERR(reply)) अणु
			error = PTR_ERR(reply);
			जाओ err_unlock_ovs;
		पूर्ण
	पूर्ण

	/* Clear stats. */
	अगर (a[OVS_FLOW_ATTR_CLEAR])
		ovs_flow_stats_clear(flow);
	ovs_unlock();

	अगर (reply)
		ovs_notअगरy(&dp_flow_genl_family, reply, info);
	अगर (old_acts)
		ovs_nla_मुक्त_flow_actions_rcu(old_acts);

	वापस 0;

err_unlock_ovs:
	ovs_unlock();
	kमुक्त_skb(reply);
err_kमुक्त_acts:
	ovs_nla_मुक्त_flow_actions(acts);
error:
	वापस error;
पूर्ण

अटल पूर्णांक ovs_flow_cmd_get(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nlattr **a = info->attrs;
	काष्ठा ovs_header *ovs_header = info->userhdr;
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा sw_flow_key key;
	काष्ठा sk_buff *reply;
	काष्ठा sw_flow *flow;
	काष्ठा datapath *dp;
	काष्ठा sw_flow_match match;
	काष्ठा sw_flow_id ufid;
	u32 ufid_flags = ovs_nla_get_ufid_flags(a[OVS_FLOW_ATTR_UFID_FLAGS]);
	पूर्णांक err = 0;
	bool log = !a[OVS_FLOW_ATTR_PROBE];
	bool ufid_present;

	ufid_present = ovs_nla_get_ufid(&ufid, a[OVS_FLOW_ATTR_UFID], log);
	अगर (a[OVS_FLOW_ATTR_KEY]) अणु
		ovs_match_init(&match, &key, true, शून्य);
		err = ovs_nla_get_match(net, &match, a[OVS_FLOW_ATTR_KEY], शून्य,
					log);
	पूर्ण अन्यथा अगर (!ufid_present) अणु
		OVS_NLERR(log,
			  "Flow get message rejected, Key attribute missing.");
		err = -EINVAL;
	पूर्ण
	अगर (err)
		वापस err;

	ovs_lock();
	dp = get_dp(sock_net(skb->sk), ovs_header->dp_अगरindex);
	अगर (!dp) अणु
		err = -ENODEV;
		जाओ unlock;
	पूर्ण

	अगर (ufid_present)
		flow = ovs_flow_tbl_lookup_ufid(&dp->table, &ufid);
	अन्यथा
		flow = ovs_flow_tbl_lookup_exact(&dp->table, &match);
	अगर (!flow) अणु
		err = -ENOENT;
		जाओ unlock;
	पूर्ण

	reply = ovs_flow_cmd_build_info(flow, ovs_header->dp_अगरindex, info,
					OVS_FLOW_CMD_GET, true, ufid_flags);
	अगर (IS_ERR(reply)) अणु
		err = PTR_ERR(reply);
		जाओ unlock;
	पूर्ण

	ovs_unlock();
	वापस genlmsg_reply(reply, info);
unlock:
	ovs_unlock();
	वापस err;
पूर्ण

अटल पूर्णांक ovs_flow_cmd_del(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nlattr **a = info->attrs;
	काष्ठा ovs_header *ovs_header = info->userhdr;
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा sw_flow_key key;
	काष्ठा sk_buff *reply;
	काष्ठा sw_flow *flow = शून्य;
	काष्ठा datapath *dp;
	काष्ठा sw_flow_match match;
	काष्ठा sw_flow_id ufid;
	u32 ufid_flags = ovs_nla_get_ufid_flags(a[OVS_FLOW_ATTR_UFID_FLAGS]);
	पूर्णांक err;
	bool log = !a[OVS_FLOW_ATTR_PROBE];
	bool ufid_present;

	ufid_present = ovs_nla_get_ufid(&ufid, a[OVS_FLOW_ATTR_UFID], log);
	अगर (a[OVS_FLOW_ATTR_KEY]) अणु
		ovs_match_init(&match, &key, true, शून्य);
		err = ovs_nla_get_match(net, &match, a[OVS_FLOW_ATTR_KEY],
					शून्य, log);
		अगर (unlikely(err))
			वापस err;
	पूर्ण

	ovs_lock();
	dp = get_dp(sock_net(skb->sk), ovs_header->dp_अगरindex);
	अगर (unlikely(!dp)) अणु
		err = -ENODEV;
		जाओ unlock;
	पूर्ण

	अगर (unlikely(!a[OVS_FLOW_ATTR_KEY] && !ufid_present)) अणु
		err = ovs_flow_tbl_flush(&dp->table);
		जाओ unlock;
	पूर्ण

	अगर (ufid_present)
		flow = ovs_flow_tbl_lookup_ufid(&dp->table, &ufid);
	अन्यथा
		flow = ovs_flow_tbl_lookup_exact(&dp->table, &match);
	अगर (unlikely(!flow)) अणु
		err = -ENOENT;
		जाओ unlock;
	पूर्ण

	ovs_flow_tbl_हटाओ(&dp->table, flow);
	ovs_unlock();

	reply = ovs_flow_cmd_alloc_info((स्थिर काष्ठा sw_flow_actions __क्रमce *) flow->sf_acts,
					&flow->id, info, false, ufid_flags);
	अगर (likely(reply)) अणु
		अगर (!IS_ERR(reply)) अणु
			rcu_पढ़ो_lock();	/*To keep RCU checker happy. */
			err = ovs_flow_cmd_fill_info(flow, ovs_header->dp_अगरindex,
						     reply, info->snd_portid,
						     info->snd_seq, 0,
						     OVS_FLOW_CMD_DEL,
						     ufid_flags);
			rcu_पढ़ो_unlock();
			अगर (WARN_ON_ONCE(err < 0)) अणु
				kमुक्त_skb(reply);
				जाओ out_मुक्त;
			पूर्ण

			ovs_notअगरy(&dp_flow_genl_family, reply, info);
		पूर्ण अन्यथा अणु
			netlink_set_err(sock_net(skb->sk)->genl_sock, 0, 0,
					PTR_ERR(reply));
		पूर्ण
	पूर्ण

out_मुक्त:
	ovs_flow_मुक्त(flow, true);
	वापस 0;
unlock:
	ovs_unlock();
	वापस err;
पूर्ण

अटल पूर्णांक ovs_flow_cmd_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा nlattr *a[__OVS_FLOW_ATTR_MAX];
	काष्ठा ovs_header *ovs_header = genlmsg_data(nlmsg_data(cb->nlh));
	काष्ठा table_instance *ti;
	काष्ठा datapath *dp;
	u32 ufid_flags;
	पूर्णांक err;

	err = genlmsg_parse_deprecated(cb->nlh, &dp_flow_genl_family, a,
				       OVS_FLOW_ATTR_MAX, flow_policy, शून्य);
	अगर (err)
		वापस err;
	ufid_flags = ovs_nla_get_ufid_flags(a[OVS_FLOW_ATTR_UFID_FLAGS]);

	rcu_पढ़ो_lock();
	dp = get_dp_rcu(sock_net(skb->sk), ovs_header->dp_अगरindex);
	अगर (!dp) अणु
		rcu_पढ़ो_unlock();
		वापस -ENODEV;
	पूर्ण

	ti = rcu_dereference(dp->table.ti);
	क्रम (;;) अणु
		काष्ठा sw_flow *flow;
		u32 bucket, obj;

		bucket = cb->args[0];
		obj = cb->args[1];
		flow = ovs_flow_tbl_dump_next(ti, &bucket, &obj);
		अगर (!flow)
			अवरोध;

		अगर (ovs_flow_cmd_fill_info(flow, ovs_header->dp_अगरindex, skb,
					   NETLINK_CB(cb->skb).portid,
					   cb->nlh->nlmsg_seq, NLM_F_MULTI,
					   OVS_FLOW_CMD_GET, ufid_flags) < 0)
			अवरोध;

		cb->args[0] = bucket;
		cb->args[1] = obj;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस skb->len;
पूर्ण

अटल स्थिर काष्ठा nla_policy flow_policy[OVS_FLOW_ATTR_MAX + 1] = अणु
	[OVS_FLOW_ATTR_KEY] = अणु .type = NLA_NESTED पूर्ण,
	[OVS_FLOW_ATTR_MASK] = अणु .type = NLA_NESTED पूर्ण,
	[OVS_FLOW_ATTR_ACTIONS] = अणु .type = NLA_NESTED पूर्ण,
	[OVS_FLOW_ATTR_CLEAR] = अणु .type = NLA_FLAG पूर्ण,
	[OVS_FLOW_ATTR_PROBE] = अणु .type = NLA_FLAG पूर्ण,
	[OVS_FLOW_ATTR_UFID] = अणु .type = NLA_UNSPEC, .len = 1 पूर्ण,
	[OVS_FLOW_ATTR_UFID_FLAGS] = अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा genl_small_ops dp_flow_genl_ops[] = अणु
	अणु .cmd = OVS_FLOW_CMD_NEW,
	  .validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
	  .flags = GENL_UNS_ADMIN_PERM, /* Requires CAP_NET_ADMIN privilege. */
	  .करोit = ovs_flow_cmd_new
	पूर्ण,
	अणु .cmd = OVS_FLOW_CMD_DEL,
	  .validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
	  .flags = GENL_UNS_ADMIN_PERM, /* Requires CAP_NET_ADMIN privilege. */
	  .करोit = ovs_flow_cmd_del
	पूर्ण,
	अणु .cmd = OVS_FLOW_CMD_GET,
	  .validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
	  .flags = 0,		    /* OK क्रम unprivileged users. */
	  .करोit = ovs_flow_cmd_get,
	  .dumpit = ovs_flow_cmd_dump
	पूर्ण,
	अणु .cmd = OVS_FLOW_CMD_SET,
	  .validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
	  .flags = GENL_UNS_ADMIN_PERM, /* Requires CAP_NET_ADMIN privilege. */
	  .करोit = ovs_flow_cmd_set,
	पूर्ण,
पूर्ण;

अटल काष्ठा genl_family dp_flow_genl_family __ro_after_init = अणु
	.hdrsize = माप(काष्ठा ovs_header),
	.name = OVS_FLOW_FAMILY,
	.version = OVS_FLOW_VERSION,
	.maxattr = OVS_FLOW_ATTR_MAX,
	.policy = flow_policy,
	.netnsok = true,
	.parallel_ops = true,
	.small_ops = dp_flow_genl_ops,
	.n_small_ops = ARRAY_SIZE(dp_flow_genl_ops),
	.mcgrps = &ovs_dp_flow_multicast_group,
	.n_mcgrps = 1,
	.module = THIS_MODULE,
पूर्ण;

अटल माप_प्रकार ovs_dp_cmd_msg_size(व्योम)
अणु
	माप_प्रकार msgsize = NLMSG_ALIGN(माप(काष्ठा ovs_header));

	msgsize += nla_total_size(IFNAMSIZ);
	msgsize += nla_total_size_64bit(माप(काष्ठा ovs_dp_stats));
	msgsize += nla_total_size_64bit(माप(काष्ठा ovs_dp_megaflow_stats));
	msgsize += nla_total_size(माप(u32)); /* OVS_DP_ATTR_USER_FEATURES */
	msgsize += nla_total_size(माप(u32)); /* OVS_DP_ATTR_MASKS_CACHE_SIZE */

	वापस msgsize;
पूर्ण

/* Called with ovs_mutex. */
अटल पूर्णांक ovs_dp_cmd_fill_info(काष्ठा datapath *dp, काष्ठा sk_buff *skb,
				u32 portid, u32 seq, u32 flags, u8 cmd)
अणु
	काष्ठा ovs_header *ovs_header;
	काष्ठा ovs_dp_stats dp_stats;
	काष्ठा ovs_dp_megaflow_stats dp_megaflow_stats;
	पूर्णांक err;

	ovs_header = genlmsg_put(skb, portid, seq, &dp_datapath_genl_family,
				 flags, cmd);
	अगर (!ovs_header)
		जाओ error;

	ovs_header->dp_अगरindex = get_dpअगरindex(dp);

	err = nla_put_string(skb, OVS_DP_ATTR_NAME, ovs_dp_name(dp));
	अगर (err)
		जाओ nla_put_failure;

	get_dp_stats(dp, &dp_stats, &dp_megaflow_stats);
	अगर (nla_put_64bit(skb, OVS_DP_ATTR_STATS, माप(काष्ठा ovs_dp_stats),
			  &dp_stats, OVS_DP_ATTR_PAD))
		जाओ nla_put_failure;

	अगर (nla_put_64bit(skb, OVS_DP_ATTR_MEGAFLOW_STATS,
			  माप(काष्ठा ovs_dp_megaflow_stats),
			  &dp_megaflow_stats, OVS_DP_ATTR_PAD))
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, OVS_DP_ATTR_USER_FEATURES, dp->user_features))
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, OVS_DP_ATTR_MASKS_CACHE_SIZE,
			ovs_flow_tbl_masks_cache_size(&dp->table)))
		जाओ nla_put_failure;

	genlmsg_end(skb, ovs_header);
	वापस 0;

nla_put_failure:
	genlmsg_cancel(skb, ovs_header);
error:
	वापस -EMSGSIZE;
पूर्ण

अटल काष्ठा sk_buff *ovs_dp_cmd_alloc_info(व्योम)
अणु
	वापस genlmsg_new(ovs_dp_cmd_msg_size(), GFP_KERNEL);
पूर्ण

/* Called with rcu_पढ़ो_lock or ovs_mutex. */
अटल काष्ठा datapath *lookup_datapath(काष्ठा net *net,
					स्थिर काष्ठा ovs_header *ovs_header,
					काष्ठा nlattr *a[OVS_DP_ATTR_MAX + 1])
अणु
	काष्ठा datapath *dp;

	अगर (!a[OVS_DP_ATTR_NAME])
		dp = get_dp(net, ovs_header->dp_अगरindex);
	अन्यथा अणु
		काष्ठा vport *vport;

		vport = ovs_vport_locate(net, nla_data(a[OVS_DP_ATTR_NAME]));
		dp = vport && vport->port_no == OVSP_LOCAL ? vport->dp : शून्य;
	पूर्ण
	वापस dp ? dp : ERR_PTR(-ENODEV);
पूर्ण

अटल व्योम ovs_dp_reset_user_features(काष्ठा sk_buff *skb,
				       काष्ठा genl_info *info)
अणु
	काष्ठा datapath *dp;

	dp = lookup_datapath(sock_net(skb->sk), info->userhdr,
			     info->attrs);
	अगर (IS_ERR(dp))
		वापस;

	WARN(dp->user_features, "Dropping previously announced user features\n");
	dp->user_features = 0;
पूर्ण

DEFINE_STATIC_KEY_FALSE(tc_recirc_sharing_support);

अटल पूर्णांक ovs_dp_change(काष्ठा datapath *dp, काष्ठा nlattr *a[])
अणु
	u32 user_features = 0;

	अगर (a[OVS_DP_ATTR_USER_FEATURES]) अणु
		user_features = nla_get_u32(a[OVS_DP_ATTR_USER_FEATURES]);

		अगर (user_features & ~(OVS_DP_F_VPORT_PIDS |
				      OVS_DP_F_UNALIGNED |
				      OVS_DP_F_TC_RECIRC_SHARING))
			वापस -EOPNOTSUPP;

#अगर !IS_ENABLED(CONFIG_NET_TC_SKB_EXT)
		अगर (user_features & OVS_DP_F_TC_RECIRC_SHARING)
			वापस -EOPNOTSUPP;
#पूर्ण_अगर
	पूर्ण

	अगर (a[OVS_DP_ATTR_MASKS_CACHE_SIZE]) अणु
		पूर्णांक err;
		u32 cache_size;

		cache_size = nla_get_u32(a[OVS_DP_ATTR_MASKS_CACHE_SIZE]);
		err = ovs_flow_tbl_masks_cache_resize(&dp->table, cache_size);
		अगर (err)
			वापस err;
	पूर्ण

	dp->user_features = user_features;

	अगर (dp->user_features & OVS_DP_F_TC_RECIRC_SHARING)
		अटल_branch_enable(&tc_recirc_sharing_support);
	अन्यथा
		अटल_branch_disable(&tc_recirc_sharing_support);

	वापस 0;
पूर्ण

अटल पूर्णांक ovs_dp_stats_init(काष्ठा datapath *dp)
अणु
	dp->stats_percpu = netdev_alloc_pcpu_stats(काष्ठा dp_stats_percpu);
	अगर (!dp->stats_percpu)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक ovs_dp_vport_init(काष्ठा datapath *dp)
अणु
	पूर्णांक i;

	dp->ports = kदो_स्मृति_array(DP_VPORT_HASH_BUCKETS,
				  माप(काष्ठा hlist_head),
				  GFP_KERNEL);
	अगर (!dp->ports)
		वापस -ENOMEM;

	क्रम (i = 0; i < DP_VPORT_HASH_BUCKETS; i++)
		INIT_HLIST_HEAD(&dp->ports[i]);

	वापस 0;
पूर्ण

अटल पूर्णांक ovs_dp_cmd_new(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nlattr **a = info->attrs;
	काष्ठा vport_parms parms;
	काष्ठा sk_buff *reply;
	काष्ठा datapath *dp;
	काष्ठा vport *vport;
	काष्ठा ovs_net *ovs_net;
	पूर्णांक err;

	err = -EINVAL;
	अगर (!a[OVS_DP_ATTR_NAME] || !a[OVS_DP_ATTR_UPCALL_PID])
		जाओ err;

	reply = ovs_dp_cmd_alloc_info();
	अगर (!reply)
		वापस -ENOMEM;

	err = -ENOMEM;
	dp = kzalloc(माप(*dp), GFP_KERNEL);
	अगर (dp == शून्य)
		जाओ err_destroy_reply;

	ovs_dp_set_net(dp, sock_net(skb->sk));

	/* Allocate table. */
	err = ovs_flow_tbl_init(&dp->table);
	अगर (err)
		जाओ err_destroy_dp;

	err = ovs_dp_stats_init(dp);
	अगर (err)
		जाओ err_destroy_table;

	err = ovs_dp_vport_init(dp);
	अगर (err)
		जाओ err_destroy_stats;

	err = ovs_meters_init(dp);
	अगर (err)
		जाओ err_destroy_ports;

	/* Set up our datapath device. */
	parms.name = nla_data(a[OVS_DP_ATTR_NAME]);
	parms.type = OVS_VPORT_TYPE_INTERNAL;
	parms.options = शून्य;
	parms.dp = dp;
	parms.port_no = OVSP_LOCAL;
	parms.upcall_portids = a[OVS_DP_ATTR_UPCALL_PID];

	/* So far only local changes have been made, now need the lock. */
	ovs_lock();

	err = ovs_dp_change(dp, a);
	अगर (err)
		जाओ err_unlock_and_destroy_meters;

	vport = new_vport(&parms);
	अगर (IS_ERR(vport)) अणु
		err = PTR_ERR(vport);
		अगर (err == -EBUSY)
			err = -EEXIST;

		अगर (err == -EEXIST) अणु
			/* An outdated user space instance that करोes not understand
			 * the concept of user_features has attempted to create a new
			 * datapath and is likely to reuse it. Drop all user features.
			 */
			अगर (info->genlhdr->version < OVS_DP_VER_FEATURES)
				ovs_dp_reset_user_features(skb, info);
		पूर्ण

		जाओ err_unlock_and_destroy_meters;
	पूर्ण

	err = ovs_dp_cmd_fill_info(dp, reply, info->snd_portid,
				   info->snd_seq, 0, OVS_DP_CMD_NEW);
	BUG_ON(err < 0);

	ovs_net = net_generic(ovs_dp_get_net(dp), ovs_net_id);
	list_add_tail_rcu(&dp->list_node, &ovs_net->dps);

	ovs_unlock();

	ovs_notअगरy(&dp_datapath_genl_family, reply, info);
	वापस 0;

err_unlock_and_destroy_meters:
	ovs_unlock();
	ovs_meters_निकास(dp);
err_destroy_ports:
	kमुक्त(dp->ports);
err_destroy_stats:
	मुक्त_percpu(dp->stats_percpu);
err_destroy_table:
	ovs_flow_tbl_destroy(&dp->table);
err_destroy_dp:
	kमुक्त(dp);
err_destroy_reply:
	kमुक्त_skb(reply);
err:
	वापस err;
पूर्ण

/* Called with ovs_mutex. */
अटल व्योम __dp_destroy(काष्ठा datapath *dp)
अणु
	काष्ठा flow_table *table = &dp->table;
	पूर्णांक i;

	क्रम (i = 0; i < DP_VPORT_HASH_BUCKETS; i++) अणु
		काष्ठा vport *vport;
		काष्ठा hlist_node *n;

		hlist_क्रम_each_entry_safe(vport, n, &dp->ports[i], dp_hash_node)
			अगर (vport->port_no != OVSP_LOCAL)
				ovs_dp_detach_port(vport);
	पूर्ण

	list_del_rcu(&dp->list_node);

	/* OVSP_LOCAL is datapath पूर्णांकernal port. We need to make sure that
	 * all ports in datapath are destroyed first beक्रमe मुक्तing datapath.
	 */
	ovs_dp_detach_port(ovs_vport_ovsl(dp, OVSP_LOCAL));

	/* Flush sw_flow in the tables. RCU cb only releases resource
	 * such as dp, ports and tables. That may aव्योम some issues
	 * such as RCU usage warning.
	 */
	table_instance_flow_flush(table, ovsl_dereference(table->ti),
				  ovsl_dereference(table->ufid_ti));

	/* RCU destroy the ports, meters and flow tables. */
	call_rcu(&dp->rcu, destroy_dp_rcu);
पूर्ण

अटल पूर्णांक ovs_dp_cmd_del(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा sk_buff *reply;
	काष्ठा datapath *dp;
	पूर्णांक err;

	reply = ovs_dp_cmd_alloc_info();
	अगर (!reply)
		वापस -ENOMEM;

	ovs_lock();
	dp = lookup_datapath(sock_net(skb->sk), info->userhdr, info->attrs);
	err = PTR_ERR(dp);
	अगर (IS_ERR(dp))
		जाओ err_unlock_मुक्त;

	err = ovs_dp_cmd_fill_info(dp, reply, info->snd_portid,
				   info->snd_seq, 0, OVS_DP_CMD_DEL);
	BUG_ON(err < 0);

	__dp_destroy(dp);
	ovs_unlock();

	ovs_notअगरy(&dp_datapath_genl_family, reply, info);

	वापस 0;

err_unlock_मुक्त:
	ovs_unlock();
	kमुक्त_skb(reply);
	वापस err;
पूर्ण

अटल पूर्णांक ovs_dp_cmd_set(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा sk_buff *reply;
	काष्ठा datapath *dp;
	पूर्णांक err;

	reply = ovs_dp_cmd_alloc_info();
	अगर (!reply)
		वापस -ENOMEM;

	ovs_lock();
	dp = lookup_datapath(sock_net(skb->sk), info->userhdr, info->attrs);
	err = PTR_ERR(dp);
	अगर (IS_ERR(dp))
		जाओ err_unlock_मुक्त;

	err = ovs_dp_change(dp, info->attrs);
	अगर (err)
		जाओ err_unlock_मुक्त;

	err = ovs_dp_cmd_fill_info(dp, reply, info->snd_portid,
				   info->snd_seq, 0, OVS_DP_CMD_SET);
	BUG_ON(err < 0);

	ovs_unlock();
	ovs_notअगरy(&dp_datapath_genl_family, reply, info);

	वापस 0;

err_unlock_मुक्त:
	ovs_unlock();
	kमुक्त_skb(reply);
	वापस err;
पूर्ण

अटल पूर्णांक ovs_dp_cmd_get(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा sk_buff *reply;
	काष्ठा datapath *dp;
	पूर्णांक err;

	reply = ovs_dp_cmd_alloc_info();
	अगर (!reply)
		वापस -ENOMEM;

	ovs_lock();
	dp = lookup_datapath(sock_net(skb->sk), info->userhdr, info->attrs);
	अगर (IS_ERR(dp)) अणु
		err = PTR_ERR(dp);
		जाओ err_unlock_मुक्त;
	पूर्ण
	err = ovs_dp_cmd_fill_info(dp, reply, info->snd_portid,
				   info->snd_seq, 0, OVS_DP_CMD_GET);
	BUG_ON(err < 0);
	ovs_unlock();

	वापस genlmsg_reply(reply, info);

err_unlock_मुक्त:
	ovs_unlock();
	kमुक्त_skb(reply);
	वापस err;
पूर्ण

अटल पूर्णांक ovs_dp_cmd_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा ovs_net *ovs_net = net_generic(sock_net(skb->sk), ovs_net_id);
	काष्ठा datapath *dp;
	पूर्णांक skip = cb->args[0];
	पूर्णांक i = 0;

	ovs_lock();
	list_क्रम_each_entry(dp, &ovs_net->dps, list_node) अणु
		अगर (i >= skip &&
		    ovs_dp_cmd_fill_info(dp, skb, NETLINK_CB(cb->skb).portid,
					 cb->nlh->nlmsg_seq, NLM_F_MULTI,
					 OVS_DP_CMD_GET) < 0)
			अवरोध;
		i++;
	पूर्ण
	ovs_unlock();

	cb->args[0] = i;

	वापस skb->len;
पूर्ण

अटल स्थिर काष्ठा nla_policy datapath_policy[OVS_DP_ATTR_MAX + 1] = अणु
	[OVS_DP_ATTR_NAME] = अणु .type = NLA_NUL_STRING, .len = IFNAMSIZ - 1 पूर्ण,
	[OVS_DP_ATTR_UPCALL_PID] = अणु .type = NLA_U32 पूर्ण,
	[OVS_DP_ATTR_USER_FEATURES] = अणु .type = NLA_U32 पूर्ण,
	[OVS_DP_ATTR_MASKS_CACHE_SIZE] =  NLA_POLICY_RANGE(NLA_U32, 0,
		PCPU_MIN_UNIT_SIZE / माप(काष्ठा mask_cache_entry)),
पूर्ण;

अटल स्थिर काष्ठा genl_small_ops dp_datapath_genl_ops[] = अणु
	अणु .cmd = OVS_DP_CMD_NEW,
	  .validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
	  .flags = GENL_UNS_ADMIN_PERM, /* Requires CAP_NET_ADMIN privilege. */
	  .करोit = ovs_dp_cmd_new
	पूर्ण,
	अणु .cmd = OVS_DP_CMD_DEL,
	  .validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
	  .flags = GENL_UNS_ADMIN_PERM, /* Requires CAP_NET_ADMIN privilege. */
	  .करोit = ovs_dp_cmd_del
	पूर्ण,
	अणु .cmd = OVS_DP_CMD_GET,
	  .validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
	  .flags = 0,		    /* OK क्रम unprivileged users. */
	  .करोit = ovs_dp_cmd_get,
	  .dumpit = ovs_dp_cmd_dump
	पूर्ण,
	अणु .cmd = OVS_DP_CMD_SET,
	  .validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
	  .flags = GENL_UNS_ADMIN_PERM, /* Requires CAP_NET_ADMIN privilege. */
	  .करोit = ovs_dp_cmd_set,
	पूर्ण,
पूर्ण;

अटल काष्ठा genl_family dp_datapath_genl_family __ro_after_init = अणु
	.hdrsize = माप(काष्ठा ovs_header),
	.name = OVS_DATAPATH_FAMILY,
	.version = OVS_DATAPATH_VERSION,
	.maxattr = OVS_DP_ATTR_MAX,
	.policy = datapath_policy,
	.netnsok = true,
	.parallel_ops = true,
	.small_ops = dp_datapath_genl_ops,
	.n_small_ops = ARRAY_SIZE(dp_datapath_genl_ops),
	.mcgrps = &ovs_dp_datapath_multicast_group,
	.n_mcgrps = 1,
	.module = THIS_MODULE,
पूर्ण;

/* Called with ovs_mutex or RCU पढ़ो lock. */
अटल पूर्णांक ovs_vport_cmd_fill_info(काष्ठा vport *vport, काष्ठा sk_buff *skb,
				   काष्ठा net *net, u32 portid, u32 seq,
				   u32 flags, u8 cmd, gfp_t gfp)
अणु
	काष्ठा ovs_header *ovs_header;
	काष्ठा ovs_vport_stats vport_stats;
	पूर्णांक err;

	ovs_header = genlmsg_put(skb, portid, seq, &dp_vport_genl_family,
				 flags, cmd);
	अगर (!ovs_header)
		वापस -EMSGSIZE;

	ovs_header->dp_अगरindex = get_dpअगरindex(vport->dp);

	अगर (nla_put_u32(skb, OVS_VPORT_ATTR_PORT_NO, vport->port_no) ||
	    nla_put_u32(skb, OVS_VPORT_ATTR_TYPE, vport->ops->type) ||
	    nla_put_string(skb, OVS_VPORT_ATTR_NAME,
			   ovs_vport_name(vport)) ||
	    nla_put_u32(skb, OVS_VPORT_ATTR_IFINDEX, vport->dev->अगरindex))
		जाओ nla_put_failure;

	अगर (!net_eq(net, dev_net(vport->dev))) अणु
		पूर्णांक id = peernet2id_alloc(net, dev_net(vport->dev), gfp);

		अगर (nla_put_s32(skb, OVS_VPORT_ATTR_NETNSID, id))
			जाओ nla_put_failure;
	पूर्ण

	ovs_vport_get_stats(vport, &vport_stats);
	अगर (nla_put_64bit(skb, OVS_VPORT_ATTR_STATS,
			  माप(काष्ठा ovs_vport_stats), &vport_stats,
			  OVS_VPORT_ATTR_PAD))
		जाओ nla_put_failure;

	अगर (ovs_vport_get_upcall_portids(vport, skb))
		जाओ nla_put_failure;

	err = ovs_vport_get_options(vport, skb);
	अगर (err == -EMSGSIZE)
		जाओ error;

	genlmsg_end(skb, ovs_header);
	वापस 0;

nla_put_failure:
	err = -EMSGSIZE;
error:
	genlmsg_cancel(skb, ovs_header);
	वापस err;
पूर्ण

अटल काष्ठा sk_buff *ovs_vport_cmd_alloc_info(व्योम)
अणु
	वापस nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
पूर्ण

/* Called with ovs_mutex, only via ovs_dp_notअगरy_wq(). */
काष्ठा sk_buff *ovs_vport_cmd_build_info(काष्ठा vport *vport, काष्ठा net *net,
					 u32 portid, u32 seq, u8 cmd)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक retval;

	skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	retval = ovs_vport_cmd_fill_info(vport, skb, net, portid, seq, 0, cmd,
					 GFP_KERNEL);
	BUG_ON(retval < 0);

	वापस skb;
पूर्ण

/* Called with ovs_mutex or RCU पढ़ो lock. */
अटल काष्ठा vport *lookup_vport(काष्ठा net *net,
				  स्थिर काष्ठा ovs_header *ovs_header,
				  काष्ठा nlattr *a[OVS_VPORT_ATTR_MAX + 1])
अणु
	काष्ठा datapath *dp;
	काष्ठा vport *vport;

	अगर (a[OVS_VPORT_ATTR_IFINDEX])
		वापस ERR_PTR(-EOPNOTSUPP);
	अगर (a[OVS_VPORT_ATTR_NAME]) अणु
		vport = ovs_vport_locate(net, nla_data(a[OVS_VPORT_ATTR_NAME]));
		अगर (!vport)
			वापस ERR_PTR(-ENODEV);
		अगर (ovs_header->dp_अगरindex &&
		    ovs_header->dp_अगरindex != get_dpअगरindex(vport->dp))
			वापस ERR_PTR(-ENODEV);
		वापस vport;
	पूर्ण अन्यथा अगर (a[OVS_VPORT_ATTR_PORT_NO]) अणु
		u32 port_no = nla_get_u32(a[OVS_VPORT_ATTR_PORT_NO]);

		अगर (port_no >= DP_MAX_PORTS)
			वापस ERR_PTR(-EFBIG);

		dp = get_dp(net, ovs_header->dp_अगरindex);
		अगर (!dp)
			वापस ERR_PTR(-ENODEV);

		vport = ovs_vport_ovsl_rcu(dp, port_no);
		अगर (!vport)
			वापस ERR_PTR(-ENODEV);
		वापस vport;
	पूर्ण अन्यथा
		वापस ERR_PTR(-EINVAL);

पूर्ण

अटल अचिन्हित पूर्णांक ovs_get_max_headroom(काष्ठा datapath *dp)
अणु
	अचिन्हित पूर्णांक dev_headroom, max_headroom = 0;
	काष्ठा net_device *dev;
	काष्ठा vport *vport;
	पूर्णांक i;

	क्रम (i = 0; i < DP_VPORT_HASH_BUCKETS; i++) अणु
		hlist_क्रम_each_entry_rcu(vport, &dp->ports[i], dp_hash_node,
					 lockdep_ovsl_is_held()) अणु
			dev = vport->dev;
			dev_headroom = netdev_get_fwd_headroom(dev);
			अगर (dev_headroom > max_headroom)
				max_headroom = dev_headroom;
		पूर्ण
	पूर्ण

	वापस max_headroom;
पूर्ण

/* Called with ovs_mutex */
अटल व्योम ovs_update_headroom(काष्ठा datapath *dp, अचिन्हित पूर्णांक new_headroom)
अणु
	काष्ठा vport *vport;
	पूर्णांक i;

	dp->max_headroom = new_headroom;
	क्रम (i = 0; i < DP_VPORT_HASH_BUCKETS; i++) अणु
		hlist_क्रम_each_entry_rcu(vport, &dp->ports[i], dp_hash_node,
					 lockdep_ovsl_is_held())
			netdev_set_rx_headroom(vport->dev, new_headroom);
	पूर्ण
पूर्ण

अटल पूर्णांक ovs_vport_cmd_new(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nlattr **a = info->attrs;
	काष्ठा ovs_header *ovs_header = info->userhdr;
	काष्ठा vport_parms parms;
	काष्ठा sk_buff *reply;
	काष्ठा vport *vport;
	काष्ठा datapath *dp;
	अचिन्हित पूर्णांक new_headroom;
	u32 port_no;
	पूर्णांक err;

	अगर (!a[OVS_VPORT_ATTR_NAME] || !a[OVS_VPORT_ATTR_TYPE] ||
	    !a[OVS_VPORT_ATTR_UPCALL_PID])
		वापस -EINVAL;
	अगर (a[OVS_VPORT_ATTR_IFINDEX])
		वापस -EOPNOTSUPP;

	port_no = a[OVS_VPORT_ATTR_PORT_NO]
		? nla_get_u32(a[OVS_VPORT_ATTR_PORT_NO]) : 0;
	अगर (port_no >= DP_MAX_PORTS)
		वापस -EFBIG;

	reply = ovs_vport_cmd_alloc_info();
	अगर (!reply)
		वापस -ENOMEM;

	ovs_lock();
restart:
	dp = get_dp(sock_net(skb->sk), ovs_header->dp_अगरindex);
	err = -ENODEV;
	अगर (!dp)
		जाओ निकास_unlock_मुक्त;

	अगर (port_no) अणु
		vport = ovs_vport_ovsl(dp, port_no);
		err = -EBUSY;
		अगर (vport)
			जाओ निकास_unlock_मुक्त;
	पूर्ण अन्यथा अणु
		क्रम (port_no = 1; ; port_no++) अणु
			अगर (port_no >= DP_MAX_PORTS) अणु
				err = -EFBIG;
				जाओ निकास_unlock_मुक्त;
			पूर्ण
			vport = ovs_vport_ovsl(dp, port_no);
			अगर (!vport)
				अवरोध;
		पूर्ण
	पूर्ण

	parms.name = nla_data(a[OVS_VPORT_ATTR_NAME]);
	parms.type = nla_get_u32(a[OVS_VPORT_ATTR_TYPE]);
	parms.options = a[OVS_VPORT_ATTR_OPTIONS];
	parms.dp = dp;
	parms.port_no = port_no;
	parms.upcall_portids = a[OVS_VPORT_ATTR_UPCALL_PID];

	vport = new_vport(&parms);
	err = PTR_ERR(vport);
	अगर (IS_ERR(vport)) अणु
		अगर (err == -EAGAIN)
			जाओ restart;
		जाओ निकास_unlock_मुक्त;
	पूर्ण

	err = ovs_vport_cmd_fill_info(vport, reply, genl_info_net(info),
				      info->snd_portid, info->snd_seq, 0,
				      OVS_VPORT_CMD_NEW, GFP_KERNEL);

	new_headroom = netdev_get_fwd_headroom(vport->dev);

	अगर (new_headroom > dp->max_headroom)
		ovs_update_headroom(dp, new_headroom);
	अन्यथा
		netdev_set_rx_headroom(vport->dev, dp->max_headroom);

	BUG_ON(err < 0);
	ovs_unlock();

	ovs_notअगरy(&dp_vport_genl_family, reply, info);
	वापस 0;

निकास_unlock_मुक्त:
	ovs_unlock();
	kमुक्त_skb(reply);
	वापस err;
पूर्ण

अटल पूर्णांक ovs_vport_cmd_set(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nlattr **a = info->attrs;
	काष्ठा sk_buff *reply;
	काष्ठा vport *vport;
	पूर्णांक err;

	reply = ovs_vport_cmd_alloc_info();
	अगर (!reply)
		वापस -ENOMEM;

	ovs_lock();
	vport = lookup_vport(sock_net(skb->sk), info->userhdr, a);
	err = PTR_ERR(vport);
	अगर (IS_ERR(vport))
		जाओ निकास_unlock_मुक्त;

	अगर (a[OVS_VPORT_ATTR_TYPE] &&
	    nla_get_u32(a[OVS_VPORT_ATTR_TYPE]) != vport->ops->type) अणु
		err = -EINVAL;
		जाओ निकास_unlock_मुक्त;
	पूर्ण

	अगर (a[OVS_VPORT_ATTR_OPTIONS]) अणु
		err = ovs_vport_set_options(vport, a[OVS_VPORT_ATTR_OPTIONS]);
		अगर (err)
			जाओ निकास_unlock_मुक्त;
	पूर्ण


	अगर (a[OVS_VPORT_ATTR_UPCALL_PID]) अणु
		काष्ठा nlattr *ids = a[OVS_VPORT_ATTR_UPCALL_PID];

		err = ovs_vport_set_upcall_portids(vport, ids);
		अगर (err)
			जाओ निकास_unlock_मुक्त;
	पूर्ण

	err = ovs_vport_cmd_fill_info(vport, reply, genl_info_net(info),
				      info->snd_portid, info->snd_seq, 0,
				      OVS_VPORT_CMD_SET, GFP_KERNEL);
	BUG_ON(err < 0);

	ovs_unlock();
	ovs_notअगरy(&dp_vport_genl_family, reply, info);
	वापस 0;

निकास_unlock_मुक्त:
	ovs_unlock();
	kमुक्त_skb(reply);
	वापस err;
पूर्ण

अटल पूर्णांक ovs_vport_cmd_del(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	bool update_headroom = false;
	काष्ठा nlattr **a = info->attrs;
	काष्ठा sk_buff *reply;
	काष्ठा datapath *dp;
	काष्ठा vport *vport;
	अचिन्हित पूर्णांक new_headroom;
	पूर्णांक err;

	reply = ovs_vport_cmd_alloc_info();
	अगर (!reply)
		वापस -ENOMEM;

	ovs_lock();
	vport = lookup_vport(sock_net(skb->sk), info->userhdr, a);
	err = PTR_ERR(vport);
	अगर (IS_ERR(vport))
		जाओ निकास_unlock_मुक्त;

	अगर (vport->port_no == OVSP_LOCAL) अणु
		err = -EINVAL;
		जाओ निकास_unlock_मुक्त;
	पूर्ण

	err = ovs_vport_cmd_fill_info(vport, reply, genl_info_net(info),
				      info->snd_portid, info->snd_seq, 0,
				      OVS_VPORT_CMD_DEL, GFP_KERNEL);
	BUG_ON(err < 0);

	/* the vport deletion may trigger dp headroom update */
	dp = vport->dp;
	अगर (netdev_get_fwd_headroom(vport->dev) == dp->max_headroom)
		update_headroom = true;

	netdev_reset_rx_headroom(vport->dev);
	ovs_dp_detach_port(vport);

	अगर (update_headroom) अणु
		new_headroom = ovs_get_max_headroom(dp);

		अगर (new_headroom < dp->max_headroom)
			ovs_update_headroom(dp, new_headroom);
	पूर्ण
	ovs_unlock();

	ovs_notअगरy(&dp_vport_genl_family, reply, info);
	वापस 0;

निकास_unlock_मुक्त:
	ovs_unlock();
	kमुक्त_skb(reply);
	वापस err;
पूर्ण

अटल पूर्णांक ovs_vport_cmd_get(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nlattr **a = info->attrs;
	काष्ठा ovs_header *ovs_header = info->userhdr;
	काष्ठा sk_buff *reply;
	काष्ठा vport *vport;
	पूर्णांक err;

	reply = ovs_vport_cmd_alloc_info();
	अगर (!reply)
		वापस -ENOMEM;

	rcu_पढ़ो_lock();
	vport = lookup_vport(sock_net(skb->sk), ovs_header, a);
	err = PTR_ERR(vport);
	अगर (IS_ERR(vport))
		जाओ निकास_unlock_मुक्त;
	err = ovs_vport_cmd_fill_info(vport, reply, genl_info_net(info),
				      info->snd_portid, info->snd_seq, 0,
				      OVS_VPORT_CMD_GET, GFP_ATOMIC);
	BUG_ON(err < 0);
	rcu_पढ़ो_unlock();

	वापस genlmsg_reply(reply, info);

निकास_unlock_मुक्त:
	rcu_पढ़ो_unlock();
	kमुक्त_skb(reply);
	वापस err;
पूर्ण

अटल पूर्णांक ovs_vport_cmd_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा ovs_header *ovs_header = genlmsg_data(nlmsg_data(cb->nlh));
	काष्ठा datapath *dp;
	पूर्णांक bucket = cb->args[0], skip = cb->args[1];
	पूर्णांक i, j = 0;

	rcu_पढ़ो_lock();
	dp = get_dp_rcu(sock_net(skb->sk), ovs_header->dp_अगरindex);
	अगर (!dp) अणु
		rcu_पढ़ो_unlock();
		वापस -ENODEV;
	पूर्ण
	क्रम (i = bucket; i < DP_VPORT_HASH_BUCKETS; i++) अणु
		काष्ठा vport *vport;

		j = 0;
		hlist_क्रम_each_entry_rcu(vport, &dp->ports[i], dp_hash_node) अणु
			अगर (j >= skip &&
			    ovs_vport_cmd_fill_info(vport, skb,
						    sock_net(skb->sk),
						    NETLINK_CB(cb->skb).portid,
						    cb->nlh->nlmsg_seq,
						    NLM_F_MULTI,
						    OVS_VPORT_CMD_GET,
						    GFP_ATOMIC) < 0)
				जाओ out;

			j++;
		पूर्ण
		skip = 0;
	पूर्ण
out:
	rcu_पढ़ो_unlock();

	cb->args[0] = i;
	cb->args[1] = j;

	वापस skb->len;
पूर्ण

अटल व्योम ovs_dp_masks_rebalance(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ovs_net *ovs_net = container_of(work, काष्ठा ovs_net,
					       masks_rebalance.work);
	काष्ठा datapath *dp;

	ovs_lock();

	list_क्रम_each_entry(dp, &ovs_net->dps, list_node)
		ovs_flow_masks_rebalance(&dp->table);

	ovs_unlock();

	schedule_delayed_work(&ovs_net->masks_rebalance,
			      msecs_to_jअगरfies(DP_MASKS_REBALANCE_INTERVAL));
पूर्ण

अटल स्थिर काष्ठा nla_policy vport_policy[OVS_VPORT_ATTR_MAX + 1] = अणु
	[OVS_VPORT_ATTR_NAME] = अणु .type = NLA_NUL_STRING, .len = IFNAMSIZ - 1 पूर्ण,
	[OVS_VPORT_ATTR_STATS] = अणु .len = माप(काष्ठा ovs_vport_stats) पूर्ण,
	[OVS_VPORT_ATTR_PORT_NO] = अणु .type = NLA_U32 पूर्ण,
	[OVS_VPORT_ATTR_TYPE] = अणु .type = NLA_U32 पूर्ण,
	[OVS_VPORT_ATTR_UPCALL_PID] = अणु .type = NLA_UNSPEC पूर्ण,
	[OVS_VPORT_ATTR_OPTIONS] = अणु .type = NLA_NESTED पूर्ण,
	[OVS_VPORT_ATTR_IFINDEX] = अणु .type = NLA_U32 पूर्ण,
	[OVS_VPORT_ATTR_NETNSID] = अणु .type = NLA_S32 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा genl_small_ops dp_vport_genl_ops[] = अणु
	अणु .cmd = OVS_VPORT_CMD_NEW,
	  .validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
	  .flags = GENL_UNS_ADMIN_PERM, /* Requires CAP_NET_ADMIN privilege. */
	  .करोit = ovs_vport_cmd_new
	पूर्ण,
	अणु .cmd = OVS_VPORT_CMD_DEL,
	  .validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
	  .flags = GENL_UNS_ADMIN_PERM, /* Requires CAP_NET_ADMIN privilege. */
	  .करोit = ovs_vport_cmd_del
	पूर्ण,
	अणु .cmd = OVS_VPORT_CMD_GET,
	  .validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
	  .flags = 0,		    /* OK क्रम unprivileged users. */
	  .करोit = ovs_vport_cmd_get,
	  .dumpit = ovs_vport_cmd_dump
	पूर्ण,
	अणु .cmd = OVS_VPORT_CMD_SET,
	  .validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
	  .flags = GENL_UNS_ADMIN_PERM, /* Requires CAP_NET_ADMIN privilege. */
	  .करोit = ovs_vport_cmd_set,
	पूर्ण,
पूर्ण;

काष्ठा genl_family dp_vport_genl_family __ro_after_init = अणु
	.hdrsize = माप(काष्ठा ovs_header),
	.name = OVS_VPORT_FAMILY,
	.version = OVS_VPORT_VERSION,
	.maxattr = OVS_VPORT_ATTR_MAX,
	.policy = vport_policy,
	.netnsok = true,
	.parallel_ops = true,
	.small_ops = dp_vport_genl_ops,
	.n_small_ops = ARRAY_SIZE(dp_vport_genl_ops),
	.mcgrps = &ovs_dp_vport_multicast_group,
	.n_mcgrps = 1,
	.module = THIS_MODULE,
पूर्ण;

अटल काष्ठा genl_family * स्थिर dp_genl_families[] = अणु
	&dp_datapath_genl_family,
	&dp_vport_genl_family,
	&dp_flow_genl_family,
	&dp_packet_genl_family,
	&dp_meter_genl_family,
#अगर	IS_ENABLED(CONFIG_NETFILTER_CONNCOUNT)
	&dp_ct_limit_genl_family,
#पूर्ण_अगर
पूर्ण;

अटल व्योम dp_unरेजिस्टर_genl(पूर्णांक n_families)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < n_families; i++)
		genl_unरेजिस्टर_family(dp_genl_families[i]);
पूर्ण

अटल पूर्णांक __init dp_रेजिस्टर_genl(व्योम)
अणु
	पूर्णांक err;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(dp_genl_families); i++) अणु

		err = genl_रेजिस्टर_family(dp_genl_families[i]);
		अगर (err)
			जाओ error;
	पूर्ण

	वापस 0;

error:
	dp_unरेजिस्टर_genl(i);
	वापस err;
पूर्ण

अटल पूर्णांक __net_init ovs_init_net(काष्ठा net *net)
अणु
	काष्ठा ovs_net *ovs_net = net_generic(net, ovs_net_id);
	पूर्णांक err;

	INIT_LIST_HEAD(&ovs_net->dps);
	INIT_WORK(&ovs_net->dp_notअगरy_work, ovs_dp_notअगरy_wq);
	INIT_DELAYED_WORK(&ovs_net->masks_rebalance, ovs_dp_masks_rebalance);

	err = ovs_ct_init(net);
	अगर (err)
		वापस err;

	schedule_delayed_work(&ovs_net->masks_rebalance,
			      msecs_to_jअगरfies(DP_MASKS_REBALANCE_INTERVAL));
	वापस 0;
पूर्ण

अटल व्योम __net_निकास list_vports_from_net(काष्ठा net *net, काष्ठा net *dnet,
					    काष्ठा list_head *head)
अणु
	काष्ठा ovs_net *ovs_net = net_generic(net, ovs_net_id);
	काष्ठा datapath *dp;

	list_क्रम_each_entry(dp, &ovs_net->dps, list_node) अणु
		पूर्णांक i;

		क्रम (i = 0; i < DP_VPORT_HASH_BUCKETS; i++) अणु
			काष्ठा vport *vport;

			hlist_क्रम_each_entry(vport, &dp->ports[i], dp_hash_node) अणु
				अगर (vport->ops->type != OVS_VPORT_TYPE_INTERNAL)
					जारी;

				अगर (dev_net(vport->dev) == dnet)
					list_add(&vport->detach_list, head);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __net_निकास ovs_निकास_net(काष्ठा net *dnet)
अणु
	काष्ठा datapath *dp, *dp_next;
	काष्ठा ovs_net *ovs_net = net_generic(dnet, ovs_net_id);
	काष्ठा vport *vport, *vport_next;
	काष्ठा net *net;
	LIST_HEAD(head);

	ovs_lock();

	ovs_ct_निकास(dnet);

	list_क्रम_each_entry_safe(dp, dp_next, &ovs_net->dps, list_node)
		__dp_destroy(dp);

	करोwn_पढ़ो(&net_rwsem);
	क्रम_each_net(net)
		list_vports_from_net(net, dnet, &head);
	up_पढ़ो(&net_rwsem);

	/* Detach all vports from given namespace. */
	list_क्रम_each_entry_safe(vport, vport_next, &head, detach_list) अणु
		list_del(&vport->detach_list);
		ovs_dp_detach_port(vport);
	पूर्ण

	ovs_unlock();

	cancel_delayed_work_sync(&ovs_net->masks_rebalance);
	cancel_work_sync(&ovs_net->dp_notअगरy_work);
पूर्ण

अटल काष्ठा pernet_operations ovs_net_ops = अणु
	.init = ovs_init_net,
	.निकास = ovs_निकास_net,
	.id   = &ovs_net_id,
	.size = माप(काष्ठा ovs_net),
पूर्ण;

अटल पूर्णांक __init dp_init(व्योम)
अणु
	पूर्णांक err;

	BUILD_BUG_ON(माप(काष्ठा ovs_skb_cb) >
		     माप_field(काष्ठा sk_buff, cb));

	pr_info("Open vSwitch switching datapath\n");

	err = action_fअगरos_init();
	अगर (err)
		जाओ error;

	err = ovs_पूर्णांकernal_dev_rtnl_link_रेजिस्टर();
	अगर (err)
		जाओ error_action_fअगरos_निकास;

	err = ovs_flow_init();
	अगर (err)
		जाओ error_unreg_rtnl_link;

	err = ovs_vport_init();
	अगर (err)
		जाओ error_flow_निकास;

	err = रेजिस्टर_pernet_device(&ovs_net_ops);
	अगर (err)
		जाओ error_vport_निकास;

	err = रेजिस्टर_netdevice_notअगरier(&ovs_dp_device_notअगरier);
	अगर (err)
		जाओ error_netns_निकास;

	err = ovs_netdev_init();
	अगर (err)
		जाओ error_unreg_notअगरier;

	err = dp_रेजिस्टर_genl();
	अगर (err < 0)
		जाओ error_unreg_netdev;

	वापस 0;

error_unreg_netdev:
	ovs_netdev_निकास();
error_unreg_notअगरier:
	unरेजिस्टर_netdevice_notअगरier(&ovs_dp_device_notअगरier);
error_netns_निकास:
	unरेजिस्टर_pernet_device(&ovs_net_ops);
error_vport_निकास:
	ovs_vport_निकास();
error_flow_निकास:
	ovs_flow_निकास();
error_unreg_rtnl_link:
	ovs_पूर्णांकernal_dev_rtnl_link_unरेजिस्टर();
error_action_fअगरos_निकास:
	action_fअगरos_निकास();
error:
	वापस err;
पूर्ण

अटल व्योम dp_cleanup(व्योम)
अणु
	dp_unरेजिस्टर_genl(ARRAY_SIZE(dp_genl_families));
	ovs_netdev_निकास();
	unरेजिस्टर_netdevice_notअगरier(&ovs_dp_device_notअगरier);
	unरेजिस्टर_pernet_device(&ovs_net_ops);
	rcu_barrier();
	ovs_vport_निकास();
	ovs_flow_निकास();
	ovs_पूर्णांकernal_dev_rtnl_link_unरेजिस्टर();
	action_fअगरos_निकास();
पूर्ण

module_init(dp_init);
module_निकास(dp_cleanup);

MODULE_DESCRIPTION("Open vSwitch switching datapath");
MODULE_LICENSE("GPL");
MODULE_ALIAS_GENL_FAMILY(OVS_DATAPATH_FAMILY);
MODULE_ALIAS_GENL_FAMILY(OVS_VPORT_FAMILY);
MODULE_ALIAS_GENL_FAMILY(OVS_FLOW_FAMILY);
MODULE_ALIAS_GENL_FAMILY(OVS_PACKET_FAMILY);
MODULE_ALIAS_GENL_FAMILY(OVS_METER_FAMILY);
MODULE_ALIAS_GENL_FAMILY(OVS_CT_LIMIT_FAMILY);
