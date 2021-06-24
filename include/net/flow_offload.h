<शैली गुरु>
#अगर_अघोषित _NET_FLOW_OFFLOAD_H
#घोषणा _NET_FLOW_OFFLOAD_H

#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/netlink.h>
#समावेश <net/flow_dissector.h>

काष्ठा flow_match अणु
	काष्ठा flow_dissector	*dissector;
	व्योम			*mask;
	व्योम			*key;
पूर्ण;

काष्ठा flow_match_meta अणु
	काष्ठा flow_dissector_key_meta *key, *mask;
पूर्ण;

काष्ठा flow_match_basic अणु
	काष्ठा flow_dissector_key_basic *key, *mask;
पूर्ण;

काष्ठा flow_match_control अणु
	काष्ठा flow_dissector_key_control *key, *mask;
पूर्ण;

काष्ठा flow_match_eth_addrs अणु
	काष्ठा flow_dissector_key_eth_addrs *key, *mask;
पूर्ण;

काष्ठा flow_match_vlan अणु
	काष्ठा flow_dissector_key_vlan *key, *mask;
पूर्ण;

काष्ठा flow_match_ipv4_addrs अणु
	काष्ठा flow_dissector_key_ipv4_addrs *key, *mask;
पूर्ण;

काष्ठा flow_match_ipv6_addrs अणु
	काष्ठा flow_dissector_key_ipv6_addrs *key, *mask;
पूर्ण;

काष्ठा flow_match_ip अणु
	काष्ठा flow_dissector_key_ip *key, *mask;
पूर्ण;

काष्ठा flow_match_ports अणु
	काष्ठा flow_dissector_key_ports *key, *mask;
पूर्ण;

काष्ठा flow_match_icmp अणु
	काष्ठा flow_dissector_key_icmp *key, *mask;
पूर्ण;

काष्ठा flow_match_tcp अणु
	काष्ठा flow_dissector_key_tcp *key, *mask;
पूर्ण;

काष्ठा flow_match_mpls अणु
	काष्ठा flow_dissector_key_mpls *key, *mask;
पूर्ण;

काष्ठा flow_match_enc_keyid अणु
	काष्ठा flow_dissector_key_keyid *key, *mask;
पूर्ण;

काष्ठा flow_match_enc_opts अणु
	काष्ठा flow_dissector_key_enc_opts *key, *mask;
पूर्ण;

काष्ठा flow_match_ct अणु
	काष्ठा flow_dissector_key_ct *key, *mask;
पूर्ण;

काष्ठा flow_rule;

व्योम flow_rule_match_meta(स्थिर काष्ठा flow_rule *rule,
			  काष्ठा flow_match_meta *out);
व्योम flow_rule_match_basic(स्थिर काष्ठा flow_rule *rule,
			   काष्ठा flow_match_basic *out);
व्योम flow_rule_match_control(स्थिर काष्ठा flow_rule *rule,
			     काष्ठा flow_match_control *out);
व्योम flow_rule_match_eth_addrs(स्थिर काष्ठा flow_rule *rule,
			       काष्ठा flow_match_eth_addrs *out);
व्योम flow_rule_match_vlan(स्थिर काष्ठा flow_rule *rule,
			  काष्ठा flow_match_vlan *out);
व्योम flow_rule_match_cvlan(स्थिर काष्ठा flow_rule *rule,
			   काष्ठा flow_match_vlan *out);
व्योम flow_rule_match_ipv4_addrs(स्थिर काष्ठा flow_rule *rule,
				काष्ठा flow_match_ipv4_addrs *out);
व्योम flow_rule_match_ipv6_addrs(स्थिर काष्ठा flow_rule *rule,
				काष्ठा flow_match_ipv6_addrs *out);
व्योम flow_rule_match_ip(स्थिर काष्ठा flow_rule *rule,
			काष्ठा flow_match_ip *out);
व्योम flow_rule_match_ports(स्थिर काष्ठा flow_rule *rule,
			   काष्ठा flow_match_ports *out);
व्योम flow_rule_match_tcp(स्थिर काष्ठा flow_rule *rule,
			 काष्ठा flow_match_tcp *out);
व्योम flow_rule_match_icmp(स्थिर काष्ठा flow_rule *rule,
			  काष्ठा flow_match_icmp *out);
व्योम flow_rule_match_mpls(स्थिर काष्ठा flow_rule *rule,
			  काष्ठा flow_match_mpls *out);
व्योम flow_rule_match_enc_control(स्थिर काष्ठा flow_rule *rule,
				 काष्ठा flow_match_control *out);
व्योम flow_rule_match_enc_ipv4_addrs(स्थिर काष्ठा flow_rule *rule,
				    काष्ठा flow_match_ipv4_addrs *out);
व्योम flow_rule_match_enc_ipv6_addrs(स्थिर काष्ठा flow_rule *rule,
				    काष्ठा flow_match_ipv6_addrs *out);
व्योम flow_rule_match_enc_ip(स्थिर काष्ठा flow_rule *rule,
			    काष्ठा flow_match_ip *out);
व्योम flow_rule_match_enc_ports(स्थिर काष्ठा flow_rule *rule,
			       काष्ठा flow_match_ports *out);
व्योम flow_rule_match_enc_keyid(स्थिर काष्ठा flow_rule *rule,
			       काष्ठा flow_match_enc_keyid *out);
व्योम flow_rule_match_enc_opts(स्थिर काष्ठा flow_rule *rule,
			      काष्ठा flow_match_enc_opts *out);
व्योम flow_rule_match_ct(स्थिर काष्ठा flow_rule *rule,
			काष्ठा flow_match_ct *out);

क्रमागत flow_action_id अणु
	FLOW_ACTION_ACCEPT		= 0,
	FLOW_ACTION_DROP,
	FLOW_ACTION_TRAP,
	FLOW_ACTION_GOTO,
	FLOW_ACTION_REसूचीECT,
	FLOW_ACTION_MIRRED,
	FLOW_ACTION_REसूचीECT_INGRESS,
	FLOW_ACTION_MIRRED_INGRESS,
	FLOW_ACTION_VLAN_PUSH,
	FLOW_ACTION_VLAN_POP,
	FLOW_ACTION_VLAN_MANGLE,
	FLOW_ACTION_TUNNEL_ENCAP,
	FLOW_ACTION_TUNNEL_DECAP,
	FLOW_ACTION_MANGLE,
	FLOW_ACTION_ADD,
	FLOW_ACTION_CSUM,
	FLOW_ACTION_MARK,
	FLOW_ACTION_PTYPE,
	FLOW_ACTION_PRIORITY,
	FLOW_ACTION_WAKE,
	FLOW_ACTION_QUEUE,
	FLOW_ACTION_SAMPLE,
	FLOW_ACTION_POLICE,
	FLOW_ACTION_CT,
	FLOW_ACTION_CT_METADATA,
	FLOW_ACTION_MPLS_PUSH,
	FLOW_ACTION_MPLS_POP,
	FLOW_ACTION_MPLS_MANGLE,
	FLOW_ACTION_GATE,
	FLOW_ACTION_PPPOE_PUSH,
	NUM_FLOW_ACTIONS,
पूर्ण;

/* This is mirroring क्रमागत pedit_header_type definition क्रम easy mapping between
 * tc pedit action. Legacy TCA_PEDIT_KEY_EX_HDR_TYPE_NETWORK is mapped to
 * FLOW_ACT_MANGLE_UNSPEC, which is supported by no driver.
 */
क्रमागत flow_action_mangle_base अणु
	FLOW_ACT_MANGLE_UNSPEC		= 0,
	FLOW_ACT_MANGLE_HDR_TYPE_ETH,
	FLOW_ACT_MANGLE_HDR_TYPE_IP4,
	FLOW_ACT_MANGLE_HDR_TYPE_IP6,
	FLOW_ACT_MANGLE_HDR_TYPE_TCP,
	FLOW_ACT_MANGLE_HDR_TYPE_UDP,
पूर्ण;

क्रमागत flow_action_hw_stats_bit अणु
	FLOW_ACTION_HW_STATS_IMMEDIATE_BIT,
	FLOW_ACTION_HW_STATS_DELAYED_BIT,
	FLOW_ACTION_HW_STATS_DISABLED_BIT,

	FLOW_ACTION_HW_STATS_NUM_BITS
पूर्ण;

क्रमागत flow_action_hw_stats अणु
	FLOW_ACTION_HW_STATS_IMMEDIATE =
		BIT(FLOW_ACTION_HW_STATS_IMMEDIATE_BIT),
	FLOW_ACTION_HW_STATS_DELAYED = BIT(FLOW_ACTION_HW_STATS_DELAYED_BIT),
	FLOW_ACTION_HW_STATS_ANY = FLOW_ACTION_HW_STATS_IMMEDIATE |
				   FLOW_ACTION_HW_STATS_DELAYED,
	FLOW_ACTION_HW_STATS_DISABLED =
		BIT(FLOW_ACTION_HW_STATS_DISABLED_BIT),
	FLOW_ACTION_HW_STATS_DONT_CARE = BIT(FLOW_ACTION_HW_STATS_NUM_BITS) - 1,
पूर्ण;

प्रकार व्योम (*action_destr)(व्योम *priv);

काष्ठा flow_action_cookie अणु
	u32 cookie_len;
	u8 cookie[];
पूर्ण;

काष्ठा flow_action_cookie *flow_action_cookie_create(व्योम *data,
						     अचिन्हित पूर्णांक len,
						     gfp_t gfp);
व्योम flow_action_cookie_destroy(काष्ठा flow_action_cookie *cookie);

काष्ठा flow_action_entry अणु
	क्रमागत flow_action_id		id;
	क्रमागत flow_action_hw_stats	hw_stats;
	action_destr			deकाष्ठाor;
	व्योम				*deकाष्ठाor_priv;
	जोड़ अणु
		u32			chain_index;	/* FLOW_ACTION_GOTO */
		काष्ठा net_device	*dev;		/* FLOW_ACTION_REसूचीECT */
		काष्ठा अणु				/* FLOW_ACTION_VLAN */
			u16		vid;
			__be16		proto;
			u8		prio;
		पूर्ण vlan;
		काष्ठा अणु				/* FLOW_ACTION_MANGLE */
							/* FLOW_ACTION_ADD */
			क्रमागत flow_action_mangle_base htype;
			u32		offset;
			u32		mask;
			u32		val;
		पूर्ण mangle;
		काष्ठा ip_tunnel_info	*tunnel;	/* FLOW_ACTION_TUNNEL_ENCAP */
		u32			csum_flags;	/* FLOW_ACTION_CSUM */
		u32			mark;		/* FLOW_ACTION_MARK */
		u16                     ptype;          /* FLOW_ACTION_PTYPE */
		u32			priority;	/* FLOW_ACTION_PRIORITY */
		काष्ठा अणु				/* FLOW_ACTION_QUEUE */
			u32		ctx;
			u32		index;
			u8		vf;
		पूर्ण queue;
		काष्ठा अणु				/* FLOW_ACTION_SAMPLE */
			काष्ठा psample_group	*psample_group;
			u32			rate;
			u32			trunc_size;
			bool			truncate;
		पूर्ण sample;
		काष्ठा अणु				/* FLOW_ACTION_POLICE */
			u32			index;
			u32			burst;
			u64			rate_bytes_ps;
			u64			burst_pkt;
			u64			rate_pkt_ps;
			u32			mtu;
		पूर्ण police;
		काष्ठा अणु				/* FLOW_ACTION_CT */
			पूर्णांक action;
			u16 zone;
			काष्ठा nf_flowtable *flow_table;
		पूर्ण ct;
		काष्ठा अणु
			अचिन्हित दीर्घ cookie;
			u32 mark;
			u32 labels[4];
			bool orig_dir;
		पूर्ण ct_metadata;
		काष्ठा अणु				/* FLOW_ACTION_MPLS_PUSH */
			u32		label;
			__be16		proto;
			u8		tc;
			u8		bos;
			u8		ttl;
		पूर्ण mpls_push;
		काष्ठा अणु				/* FLOW_ACTION_MPLS_POP */
			__be16		proto;
		पूर्ण mpls_pop;
		काष्ठा अणु				/* FLOW_ACTION_MPLS_MANGLE */
			u32		label;
			u8		tc;
			u8		bos;
			u8		ttl;
		पूर्ण mpls_mangle;
		काष्ठा अणु
			u32		index;
			s32		prio;
			u64		baseसमय;
			u64		cycleसमय;
			u64		cycleसमयext;
			u32		num_entries;
			काष्ठा action_gate_entry *entries;
		पूर्ण gate;
		काष्ठा अणु				/* FLOW_ACTION_PPPOE_PUSH */
			u16		sid;
		पूर्ण pppoe;
	पूर्ण;
	काष्ठा flow_action_cookie *cookie; /* user defined action cookie */
पूर्ण;

काष्ठा flow_action अणु
	अचिन्हित पूर्णांक			num_entries;
	काष्ठा flow_action_entry	entries[];
पूर्ण;

अटल अंतरभूत bool flow_action_has_entries(स्थिर काष्ठा flow_action *action)
अणु
	वापस action->num_entries;
पूर्ण

/**
 * flow_action_has_one_action() - check अगर exactly one action is present
 * @action: tc filter flow offload action
 *
 * Returns true अगर exactly one action is present.
 */
अटल अंतरभूत bool flow_offload_has_one_action(स्थिर काष्ठा flow_action *action)
अणु
	वापस action->num_entries == 1;
पूर्ण

#घोषणा flow_action_क्रम_each(__i, __act, __actions)			\
        क्रम (__i = 0, __act = &(__actions)->entries[0];			\
	     __i < (__actions)->num_entries;				\
	     __act = &(__actions)->entries[++__i])

अटल अंतरभूत bool
flow_action_mixed_hw_stats_check(स्थिर काष्ठा flow_action *action,
				 काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर काष्ठा flow_action_entry *action_entry;
	u8 last_hw_stats;
	पूर्णांक i;

	अगर (flow_offload_has_one_action(action))
		वापस true;

	flow_action_क्रम_each(i, action_entry, action) अणु
		अगर (i && action_entry->hw_stats != last_hw_stats) अणु
			NL_SET_ERR_MSG_MOD(extack, "Mixing HW stats types for actions is not supported");
			वापस false;
		पूर्ण
		last_hw_stats = action_entry->hw_stats;
	पूर्ण
	वापस true;
पूर्ण

अटल अंतरभूत स्थिर काष्ठा flow_action_entry *
flow_action_first_entry_get(स्थिर काष्ठा flow_action *action)
अणु
	WARN_ON(!flow_action_has_entries(action));
	वापस &action->entries[0];
पूर्ण

अटल अंतरभूत bool
__flow_action_hw_stats_check(स्थिर काष्ठा flow_action *action,
			     काष्ठा netlink_ext_ack *extack,
			     bool check_allow_bit,
			     क्रमागत flow_action_hw_stats_bit allow_bit)
अणु
	स्थिर काष्ठा flow_action_entry *action_entry;

	अगर (!flow_action_has_entries(action))
		वापस true;
	अगर (!flow_action_mixed_hw_stats_check(action, extack))
		वापस false;

	action_entry = flow_action_first_entry_get(action);

	/* Zero is not a legal value क्रम hw_stats, catch anyone passing it */
	WARN_ON_ONCE(!action_entry->hw_stats);

	अगर (!check_allow_bit &&
	    ~action_entry->hw_stats & FLOW_ACTION_HW_STATS_ANY) अणु
		NL_SET_ERR_MSG_MOD(extack, "Driver supports only default HW stats type \"any\"");
		वापस false;
	पूर्ण अन्यथा अगर (check_allow_bit &&
		   !(action_entry->hw_stats & BIT(allow_bit))) अणु
		NL_SET_ERR_MSG_MOD(extack, "Driver does not support selected HW stats type");
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल अंतरभूत bool
flow_action_hw_stats_check(स्थिर काष्ठा flow_action *action,
			   काष्ठा netlink_ext_ack *extack,
			   क्रमागत flow_action_hw_stats_bit allow_bit)
अणु
	वापस __flow_action_hw_stats_check(action, extack, true, allow_bit);
पूर्ण

अटल अंतरभूत bool
flow_action_basic_hw_stats_check(स्थिर काष्ठा flow_action *action,
				 काष्ठा netlink_ext_ack *extack)
अणु
	वापस __flow_action_hw_stats_check(action, extack, false, 0);
पूर्ण

काष्ठा flow_rule अणु
	काष्ठा flow_match	match;
	काष्ठा flow_action	action;
पूर्ण;

काष्ठा flow_rule *flow_rule_alloc(अचिन्हित पूर्णांक num_actions);

अटल अंतरभूत bool flow_rule_match_key(स्थिर काष्ठा flow_rule *rule,
				       क्रमागत flow_dissector_key_id key)
अणु
	वापस dissector_uses_key(rule->match.dissector, key);
पूर्ण

काष्ठा flow_stats अणु
	u64	pkts;
	u64	bytes;
	u64	drops;
	u64	lastused;
	क्रमागत flow_action_hw_stats used_hw_stats;
	bool used_hw_stats_valid;
पूर्ण;

अटल अंतरभूत व्योम flow_stats_update(काष्ठा flow_stats *flow_stats,
				     u64 bytes, u64 pkts,
				     u64 drops, u64 lastused,
				     क्रमागत flow_action_hw_stats used_hw_stats)
अणु
	flow_stats->pkts	+= pkts;
	flow_stats->bytes	+= bytes;
	flow_stats->drops	+= drops;
	flow_stats->lastused	= max_t(u64, flow_stats->lastused, lastused);

	/* The driver should pass value with a maximum of one bit set.
	 * Passing FLOW_ACTION_HW_STATS_ANY is invalid.
	 */
	WARN_ON(used_hw_stats == FLOW_ACTION_HW_STATS_ANY);
	flow_stats->used_hw_stats |= used_hw_stats;
	flow_stats->used_hw_stats_valid = true;
पूर्ण

क्रमागत flow_block_command अणु
	FLOW_BLOCK_BIND,
	FLOW_BLOCK_UNBIND,
पूर्ण;

क्रमागत flow_block_binder_type अणु
	FLOW_BLOCK_BINDER_TYPE_UNSPEC,
	FLOW_BLOCK_BINDER_TYPE_CLSACT_INGRESS,
	FLOW_BLOCK_BINDER_TYPE_CLSACT_EGRESS,
	FLOW_BLOCK_BINDER_TYPE_RED_EARLY_DROP,
	FLOW_BLOCK_BINDER_TYPE_RED_MARK,
पूर्ण;

काष्ठा flow_block अणु
	काष्ठा list_head cb_list;
पूर्ण;

काष्ठा netlink_ext_ack;

काष्ठा flow_block_offload अणु
	क्रमागत flow_block_command command;
	क्रमागत flow_block_binder_type binder_type;
	bool block_shared;
	bool unlocked_driver_cb;
	काष्ठा net *net;
	काष्ठा flow_block *block;
	काष्ठा list_head cb_list;
	काष्ठा list_head *driver_block_list;
	काष्ठा netlink_ext_ack *extack;
	काष्ठा Qdisc *sch;
पूर्ण;

क्रमागत tc_setup_type;
प्रकार पूर्णांक flow_setup_cb_t(क्रमागत tc_setup_type type, व्योम *type_data,
			    व्योम *cb_priv);

काष्ठा flow_block_cb;

काष्ठा flow_block_indr अणु
	काष्ठा list_head		list;
	काष्ठा net_device		*dev;
	काष्ठा Qdisc			*sch;
	क्रमागत flow_block_binder_type	binder_type;
	व्योम				*data;
	व्योम				*cb_priv;
	व्योम				(*cleanup)(काष्ठा flow_block_cb *block_cb);
पूर्ण;

काष्ठा flow_block_cb अणु
	काष्ठा list_head	driver_list;
	काष्ठा list_head	list;
	flow_setup_cb_t		*cb;
	व्योम			*cb_ident;
	व्योम			*cb_priv;
	व्योम			(*release)(व्योम *cb_priv);
	काष्ठा flow_block_indr	indr;
	अचिन्हित पूर्णांक		refcnt;
पूर्ण;

काष्ठा flow_block_cb *flow_block_cb_alloc(flow_setup_cb_t *cb,
					  व्योम *cb_ident, व्योम *cb_priv,
					  व्योम (*release)(व्योम *cb_priv));
काष्ठा flow_block_cb *flow_indr_block_cb_alloc(flow_setup_cb_t *cb,
					       व्योम *cb_ident, व्योम *cb_priv,
					       व्योम (*release)(व्योम *cb_priv),
					       काष्ठा flow_block_offload *bo,
					       काष्ठा net_device *dev,
					       काष्ठा Qdisc *sch, व्योम *data,
					       व्योम *indr_cb_priv,
					       व्योम (*cleanup)(काष्ठा flow_block_cb *block_cb));
व्योम flow_block_cb_मुक्त(काष्ठा flow_block_cb *block_cb);

काष्ठा flow_block_cb *flow_block_cb_lookup(काष्ठा flow_block *block,
					   flow_setup_cb_t *cb, व्योम *cb_ident);

व्योम *flow_block_cb_priv(काष्ठा flow_block_cb *block_cb);
व्योम flow_block_cb_incref(काष्ठा flow_block_cb *block_cb);
अचिन्हित पूर्णांक flow_block_cb_decref(काष्ठा flow_block_cb *block_cb);

अटल अंतरभूत व्योम flow_block_cb_add(काष्ठा flow_block_cb *block_cb,
				     काष्ठा flow_block_offload *offload)
अणु
	list_add_tail(&block_cb->list, &offload->cb_list);
पूर्ण

अटल अंतरभूत व्योम flow_block_cb_हटाओ(काष्ठा flow_block_cb *block_cb,
					काष्ठा flow_block_offload *offload)
अणु
	list_move(&block_cb->list, &offload->cb_list);
पूर्ण

अटल अंतरभूत व्योम flow_indr_block_cb_हटाओ(काष्ठा flow_block_cb *block_cb,
					     काष्ठा flow_block_offload *offload)
अणु
	list_del(&block_cb->indr.list);
	list_move(&block_cb->list, &offload->cb_list);
पूर्ण

bool flow_block_cb_is_busy(flow_setup_cb_t *cb, व्योम *cb_ident,
			   काष्ठा list_head *driver_block_list);

पूर्णांक flow_block_cb_setup_simple(काष्ठा flow_block_offload *f,
			       काष्ठा list_head *driver_list,
			       flow_setup_cb_t *cb,
			       व्योम *cb_ident, व्योम *cb_priv, bool ingress_only);

क्रमागत flow_cls_command अणु
	FLOW_CLS_REPLACE,
	FLOW_CLS_DESTROY,
	FLOW_CLS_STATS,
	FLOW_CLS_TMPLT_CREATE,
	FLOW_CLS_TMPLT_DESTROY,
पूर्ण;

काष्ठा flow_cls_common_offload अणु
	u32 chain_index;
	__be16 protocol;
	u32 prio;
	काष्ठा netlink_ext_ack *extack;
पूर्ण;

काष्ठा flow_cls_offload अणु
	काष्ठा flow_cls_common_offload common;
	क्रमागत flow_cls_command command;
	अचिन्हित दीर्घ cookie;
	काष्ठा flow_rule *rule;
	काष्ठा flow_stats stats;
	u32 classid;
पूर्ण;

अटल अंतरभूत काष्ठा flow_rule *
flow_cls_offload_flow_rule(काष्ठा flow_cls_offload *flow_cmd)
अणु
	वापस flow_cmd->rule;
पूर्ण

अटल अंतरभूत व्योम flow_block_init(काष्ठा flow_block *flow_block)
अणु
	INIT_LIST_HEAD(&flow_block->cb_list);
पूर्ण

प्रकार पूर्णांक flow_indr_block_bind_cb_t(काष्ठा net_device *dev, काष्ठा Qdisc *sch, व्योम *cb_priv,
				      क्रमागत tc_setup_type type, व्योम *type_data,
				      व्योम *data,
				      व्योम (*cleanup)(काष्ठा flow_block_cb *block_cb));

पूर्णांक flow_indr_dev_रेजिस्टर(flow_indr_block_bind_cb_t *cb, व्योम *cb_priv);
व्योम flow_indr_dev_unरेजिस्टर(flow_indr_block_bind_cb_t *cb, व्योम *cb_priv,
			      व्योम (*release)(व्योम *cb_priv));
पूर्णांक flow_indr_dev_setup_offload(काष्ठा net_device *dev, काष्ठा Qdisc *sch,
				क्रमागत tc_setup_type type, व्योम *data,
				काष्ठा flow_block_offload *bo,
				व्योम (*cleanup)(काष्ठा flow_block_cb *block_cb));

#पूर्ण_अगर /* _NET_FLOW_OFFLOAD_H */
