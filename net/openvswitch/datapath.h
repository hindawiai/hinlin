<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2007-2014 Nicira, Inc.
 */

#अगर_अघोषित DATAPATH_H
#घोषणा DATAPATH_H 1

#समावेश <यंत्र/page.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mutex.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/u64_stats_sync.h>
#समावेश <net/ip_tunnels.h>

#समावेश "conntrack.h"
#समावेश "flow.h"
#समावेश "flow_table.h"
#समावेश "meter.h"
#समावेश "vport-internal_dev.h"

#घोषणा DP_MAX_PORTS                अच_लघु_उच्च
#घोषणा DP_VPORT_HASH_BUCKETS       1024
#घोषणा DP_MASKS_REBALANCE_INTERVAL 4000

/**
 * काष्ठा dp_stats_percpu - per-cpu packet processing statistics क्रम a given
 * datapath.
 * @n_hit: Number of received packets क्रम which a matching flow was found in
 * the flow table.
 * @n_miss: Number of received packets that had no matching flow in the flow
 * table.  The sum of @n_hit and @n_miss is the number of packets that have
 * been received by the datapath.
 * @n_lost: Number of received packets that had no matching flow in the flow
 * table that could not be sent to userspace (normally due to an overflow in
 * one of the datapath's queues).
 * @n_mask_hit: Number of masks looked up क्रम flow match.
 *   @n_mask_hit / (@n_hit + @n_missed)  will be the average masks looked
 *   up per packet.
 * @n_cache_hit: The number of received packets that had their mask found using
 * the mask cache.
 */
काष्ठा dp_stats_percpu अणु
	u64 n_hit;
	u64 n_missed;
	u64 n_lost;
	u64 n_mask_hit;
	u64 n_cache_hit;
	काष्ठा u64_stats_sync syncp;
पूर्ण;

/**
 * काष्ठा datapath - datapath क्रम flow-based packet चयनing
 * @rcu: RCU callback head क्रम deferred deकाष्ठाion.
 * @list_node: Element in global 'dps' list.
 * @table: flow table.
 * @ports: Hash table क्रम ports.  %OVSP_LOCAL port always exists.  Protected by
 * ovs_mutex and RCU.
 * @stats_percpu: Per-CPU datapath statistics.
 * @net: Reference to net namespace.
 * @max_headroom: the maximum headroom of all vports in this datapath; it will
 * be used by all the पूर्णांकernal vports in this dp.
 *
 * Context: See the comment on locking at the top of datapath.c क्रम additional
 * locking inक्रमmation.
 */
काष्ठा datapath अणु
	काष्ठा rcu_head rcu;
	काष्ठा list_head list_node;

	/* Flow table. */
	काष्ठा flow_table table;

	/* Switch ports. */
	काष्ठा hlist_head *ports;

	/* Stats. */
	काष्ठा dp_stats_percpu __percpu *stats_percpu;

	/* Network namespace ref. */
	possible_net_t net;

	u32 user_features;

	u32 max_headroom;

	/* Switch meters. */
	काष्ठा dp_meter_table meter_tbl;
पूर्ण;

/**
 * काष्ठा ovs_skb_cb - OVS data in skb CB
 * @input_vport: The original vport packet came in on. This value is cached
 * when a packet is received by OVS.
 * @mru: The maximum received fragement size; 0 अगर the packet is not
 * fragmented.
 * @acts_origlen: The netlink size of the flow actions applied to this skb.
 * @cutlen: The number of bytes from the packet end to be हटाओd.
 */
काष्ठा ovs_skb_cb अणु
	काष्ठा vport		*input_vport;
	u16			mru;
	u16			acts_origlen;
	u32			cutlen;
पूर्ण;
#घोषणा OVS_CB(skb) ((काष्ठा ovs_skb_cb *)(skb)->cb)

/**
 * काष्ठा dp_upcall - metadata to include with a packet to send to userspace
 * @cmd: One of %OVS_PACKET_CMD_*.
 * @userdata: If nonnull, its variable-length value is passed to userspace as
 * %OVS_PACKET_ATTR_USERDATA.
 * @portid: Netlink portid to which packet should be sent.  If @portid is 0
 * then no packet is sent and the packet is accounted in the datapath's @n_lost
 * counter.
 * @egress_tun_info: If nonnull, becomes %OVS_PACKET_ATTR_EGRESS_TUN_KEY.
 * @mru: If not zero, Maximum received IP fragment size.
 */
काष्ठा dp_upcall_info अणु
	काष्ठा ip_tunnel_info *egress_tun_info;
	स्थिर काष्ठा nlattr *userdata;
	स्थिर काष्ठा nlattr *actions;
	पूर्णांक actions_len;
	u32 portid;
	u8 cmd;
	u16 mru;
पूर्ण;

/**
 * काष्ठा ovs_net - Per net-namespace data क्रम ovs.
 * @dps: List of datapaths to enable dumping them all out.
 * Protected by genl_mutex.
 */
काष्ठा ovs_net अणु
	काष्ठा list_head dps;
	काष्ठा work_काष्ठा dp_notअगरy_work;
	काष्ठा delayed_work masks_rebalance;
#अगर	IS_ENABLED(CONFIG_NETFILTER_CONNCOUNT)
	काष्ठा ovs_ct_limit_info *ct_limit_info;
#पूर्ण_अगर

	/* Module reference क्रम configuring conntrack. */
	bool xt_label;
पूर्ण;

/**
 * क्रमागत ovs_pkt_hash_types - hash info to include with a packet
 * to send to userspace.
 * @OVS_PACKET_HASH_SW_BIT: indicates hash was computed in software stack.
 * @OVS_PACKET_HASH_L4_BIT: indicates hash is a canonical 4-tuple hash
 * over transport ports.
 */
क्रमागत ovs_pkt_hash_types अणु
	OVS_PACKET_HASH_SW_BIT = (1ULL << 32),
	OVS_PACKET_HASH_L4_BIT = (1ULL << 33),
पूर्ण;

बाह्य अचिन्हित पूर्णांक ovs_net_id;
व्योम ovs_lock(व्योम);
व्योम ovs_unlock(व्योम);

#अगर_घोषित CONFIG_LOCKDEP
पूर्णांक lockdep_ovsl_is_held(व्योम);
#अन्यथा
#घोषणा lockdep_ovsl_is_held()	1
#पूर्ण_अगर

#घोषणा ASSERT_OVSL()		WARN_ON(!lockdep_ovsl_is_held())
#घोषणा ovsl_dereference(p)					\
	rcu_dereference_रक्षित(p, lockdep_ovsl_is_held())
#घोषणा rcu_dereference_ovsl(p)					\
	rcu_dereference_check(p, lockdep_ovsl_is_held())

अटल अंतरभूत काष्ठा net *ovs_dp_get_net(स्थिर काष्ठा datapath *dp)
अणु
	वापस पढ़ो_pnet(&dp->net);
पूर्ण

अटल अंतरभूत व्योम ovs_dp_set_net(काष्ठा datapath *dp, काष्ठा net *net)
अणु
	ग_लिखो_pnet(&dp->net, net);
पूर्ण

काष्ठा vport *ovs_lookup_vport(स्थिर काष्ठा datapath *dp, u16 port_no);

अटल अंतरभूत काष्ठा vport *ovs_vport_rcu(स्थिर काष्ठा datapath *dp, पूर्णांक port_no)
अणु
	WARN_ON_ONCE(!rcu_पढ़ो_lock_held());
	वापस ovs_lookup_vport(dp, port_no);
पूर्ण

अटल अंतरभूत काष्ठा vport *ovs_vport_ovsl_rcu(स्थिर काष्ठा datapath *dp, पूर्णांक port_no)
अणु
	WARN_ON_ONCE(!rcu_पढ़ो_lock_held() && !lockdep_ovsl_is_held());
	वापस ovs_lookup_vport(dp, port_no);
पूर्ण

अटल अंतरभूत काष्ठा vport *ovs_vport_ovsl(स्थिर काष्ठा datapath *dp, पूर्णांक port_no)
अणु
	ASSERT_OVSL();
	वापस ovs_lookup_vport(dp, port_no);
पूर्ण

/* Must be called with rcu_पढ़ो_lock. */
अटल अंतरभूत काष्ठा datapath *get_dp_rcu(काष्ठा net *net, पूर्णांक dp_अगरindex)
अणु
	काष्ठा net_device *dev = dev_get_by_index_rcu(net, dp_अगरindex);

	अगर (dev) अणु
		काष्ठा vport *vport = ovs_पूर्णांकernal_dev_get_vport(dev);

		अगर (vport)
			वापस vport->dp;
	पूर्ण

	वापस शून्य;
पूर्ण

/* The caller must hold either ovs_mutex or rcu_पढ़ो_lock to keep the
 * वापसed dp poपूर्णांकer valid.
 */
अटल अंतरभूत काष्ठा datapath *get_dp(काष्ठा net *net, पूर्णांक dp_अगरindex)
अणु
	काष्ठा datapath *dp;

	WARN_ON_ONCE(!rcu_पढ़ो_lock_held() && !lockdep_ovsl_is_held());
	rcu_पढ़ो_lock();
	dp = get_dp_rcu(net, dp_अगरindex);
	rcu_पढ़ो_unlock();

	वापस dp;
पूर्ण

बाह्य काष्ठा notअगरier_block ovs_dp_device_notअगरier;
बाह्य काष्ठा genl_family dp_vport_genl_family;

DECLARE_STATIC_KEY_FALSE(tc_recirc_sharing_support);

व्योम ovs_dp_process_packet(काष्ठा sk_buff *skb, काष्ठा sw_flow_key *key);
व्योम ovs_dp_detach_port(काष्ठा vport *);
पूर्णांक ovs_dp_upcall(काष्ठा datapath *, काष्ठा sk_buff *,
		  स्थिर काष्ठा sw_flow_key *, स्थिर काष्ठा dp_upcall_info *,
		  uपूर्णांक32_t cutlen);

स्थिर अक्षर *ovs_dp_name(स्थिर काष्ठा datapath *dp);
काष्ठा sk_buff *ovs_vport_cmd_build_info(काष्ठा vport *vport, काष्ठा net *net,
					 u32 portid, u32 seq, u8 cmd);

पूर्णांक ovs_execute_actions(काष्ठा datapath *dp, काष्ठा sk_buff *skb,
			स्थिर काष्ठा sw_flow_actions *, काष्ठा sw_flow_key *);

व्योम ovs_dp_notअगरy_wq(काष्ठा work_काष्ठा *work);

पूर्णांक action_fअगरos_init(व्योम);
व्योम action_fअगरos_निकास(व्योम);

/* 'KEY' must not have any bits set outside of the 'MASK' */
#घोषणा OVS_MASKED(OLD, KEY, MASK) ((KEY) | ((OLD) & ~(MASK)))
#घोषणा OVS_SET_MASKED(OLD, KEY, MASK) ((OLD) = OVS_MASKED(OLD, KEY, MASK))

#घोषणा OVS_NLERR(logging_allowed, fmt, ...)			\
करो अणु								\
	अगर (logging_allowed && net_ratelimit())			\
		pr_info("netlink: " fmt "\n", ##__VA_ARGS__);	\
पूर्ण जबतक (0)
#पूर्ण_अगर /* datapath.h */
