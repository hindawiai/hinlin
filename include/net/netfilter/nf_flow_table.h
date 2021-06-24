<शैली गुरु>
#अगर_अघोषित _NF_FLOW_TABLE_H
#घोषणा _NF_FLOW_TABLE_H

#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/rhashtable-types.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_conntrack_tuple_common.h>
#समावेश <net/flow_offload.h>
#समावेश <net/dst.h>

काष्ठा nf_flowtable;
काष्ठा nf_flow_rule;
काष्ठा flow_offload;
क्रमागत flow_offload_tuple_dir;

काष्ठा nf_flow_key अणु
	काष्ठा flow_dissector_key_meta			meta;
	काष्ठा flow_dissector_key_control		control;
	काष्ठा flow_dissector_key_control		enc_control;
	काष्ठा flow_dissector_key_basic			basic;
	काष्ठा flow_dissector_key_vlan			vlan;
	काष्ठा flow_dissector_key_vlan			cvlan;
	जोड़ अणु
		काष्ठा flow_dissector_key_ipv4_addrs	ipv4;
		काष्ठा flow_dissector_key_ipv6_addrs	ipv6;
	पूर्ण;
	काष्ठा flow_dissector_key_keyid			enc_key_id;
	जोड़ अणु
		काष्ठा flow_dissector_key_ipv4_addrs	enc_ipv4;
		काष्ठा flow_dissector_key_ipv6_addrs	enc_ipv6;
	पूर्ण;
	काष्ठा flow_dissector_key_tcp			tcp;
	काष्ठा flow_dissector_key_ports			tp;
पूर्ण __aligned(BITS_PER_LONG / 8); /* Ensure that we can करो comparisons as दीर्घs. */

काष्ठा nf_flow_match अणु
	काष्ठा flow_dissector	dissector;
	काष्ठा nf_flow_key	key;
	काष्ठा nf_flow_key	mask;
पूर्ण;

काष्ठा nf_flow_rule अणु
	काष्ठा nf_flow_match	match;
	काष्ठा flow_rule	*rule;
पूर्ण;

काष्ठा nf_flowtable_type अणु
	काष्ठा list_head		list;
	पूर्णांक				family;
	पूर्णांक				(*init)(काष्ठा nf_flowtable *ft);
	पूर्णांक				(*setup)(काष्ठा nf_flowtable *ft,
						 काष्ठा net_device *dev,
						 क्रमागत flow_block_command cmd);
	पूर्णांक				(*action)(काष्ठा net *net,
						  स्थिर काष्ठा flow_offload *flow,
						  क्रमागत flow_offload_tuple_dir dir,
						  काष्ठा nf_flow_rule *flow_rule);
	व्योम				(*मुक्त)(काष्ठा nf_flowtable *ft);
	nf_hookfn			*hook;
	काष्ठा module			*owner;
पूर्ण;

क्रमागत nf_flowtable_flags अणु
	NF_FLOWTABLE_HW_OFFLOAD		= 0x1,	/* NFT_FLOWTABLE_HW_OFFLOAD */
	NF_FLOWTABLE_COUNTER		= 0x2,	/* NFT_FLOWTABLE_COUNTER */
पूर्ण;

काष्ठा nf_flowtable अणु
	काष्ठा list_head		list;
	काष्ठा rhashtable		rhashtable;
	पूर्णांक				priority;
	स्थिर काष्ठा nf_flowtable_type	*type;
	काष्ठा delayed_work		gc_work;
	अचिन्हित पूर्णांक			flags;
	काष्ठा flow_block		flow_block;
	काष्ठा rw_semaphore		flow_block_lock; /* Guards flow_block */
	possible_net_t			net;
पूर्ण;

अटल अंतरभूत bool nf_flowtable_hw_offload(काष्ठा nf_flowtable *flowtable)
अणु
	वापस flowtable->flags & NF_FLOWTABLE_HW_OFFLOAD;
पूर्ण

क्रमागत flow_offload_tuple_dir अणु
	FLOW_OFFLOAD_सूची_ORIGINAL = IP_CT_सूची_ORIGINAL,
	FLOW_OFFLOAD_सूची_REPLY = IP_CT_सूची_REPLY,
पूर्ण;
#घोषणा FLOW_OFFLOAD_सूची_MAX	IP_CT_सूची_MAX

क्रमागत flow_offload_xmit_type अणु
	FLOW_OFFLOAD_XMIT_UNSPEC	= 0,
	FLOW_OFFLOAD_XMIT_NEIGH,
	FLOW_OFFLOAD_XMIT_XFRM,
	FLOW_OFFLOAD_XMIT_सूचीECT,
पूर्ण;

#घोषणा NF_FLOW_TABLE_ENCAP_MAX		2

काष्ठा flow_offload_tuple अणु
	जोड़ अणु
		काष्ठा in_addr		src_v4;
		काष्ठा in6_addr		src_v6;
	पूर्ण;
	जोड़ अणु
		काष्ठा in_addr		dst_v4;
		काष्ठा in6_addr		dst_v6;
	पूर्ण;
	काष्ठा अणु
		__be16			src_port;
		__be16			dst_port;
	पूर्ण;

	पूर्णांक				iअगरidx;

	u8				l3proto;
	u8				l4proto;
	काष्ठा अणु
		u16			id;
		__be16			proto;
	पूर्ण encap[NF_FLOW_TABLE_ENCAP_MAX];

	/* All members above are keys क्रम lookups, see flow_offload_hash(). */
	काष्ठा अणु पूर्ण			__hash;

	u8				dir:2,
					xmit_type:2,
					encap_num:2,
					in_vlan_ingress:2;
	u16				mtu;
	जोड़ अणु
		काष्ठा अणु
			काष्ठा dst_entry *dst_cache;
			u32		dst_cookie;
		पूर्ण;
		काष्ठा अणु
			u32		अगरidx;
			u32		hw_अगरidx;
			u8		h_source[ETH_ALEN];
			u8		h_dest[ETH_ALEN];
		पूर्ण out;
	पूर्ण;
पूर्ण;

काष्ठा flow_offload_tuple_rhash अणु
	काष्ठा rhash_head		node;
	काष्ठा flow_offload_tuple	tuple;
पूर्ण;

क्रमागत nf_flow_flags अणु
	NF_FLOW_SNAT,
	NF_FLOW_DNAT,
	NF_FLOW_TEARDOWN,
	NF_FLOW_HW,
	NF_FLOW_HW_DYING,
	NF_FLOW_HW_DEAD,
	NF_FLOW_HW_PENDING,
पूर्ण;

क्रमागत flow_offload_type अणु
	NF_FLOW_OFFLOAD_UNSPEC	= 0,
	NF_FLOW_OFFLOAD_ROUTE,
पूर्ण;

काष्ठा flow_offload अणु
	काष्ठा flow_offload_tuple_rhash		tuplehash[FLOW_OFFLOAD_सूची_MAX];
	काष्ठा nf_conn				*ct;
	अचिन्हित दीर्घ				flags;
	u16					type;
	u32					समयout;
	काष्ठा rcu_head				rcu_head;
पूर्ण;

#घोषणा NF_FLOW_TIMEOUT (30 * HZ)
#घोषणा nf_flowtable_समय_stamp	(u32)jअगरfies

अटल अंतरभूत __s32 nf_flow_समयout_delta(अचिन्हित पूर्णांक समयout)
अणु
	वापस (__s32)(समयout - nf_flowtable_समय_stamp);
पूर्ण

काष्ठा nf_flow_route अणु
	काष्ठा अणु
		काष्ठा dst_entry		*dst;
		काष्ठा अणु
			u32			अगरindex;
			काष्ठा अणु
				u16		id;
				__be16		proto;
			पूर्ण encap[NF_FLOW_TABLE_ENCAP_MAX];
			u8			num_encaps:2,
						ingress_vlans:2;
		पूर्ण in;
		काष्ठा अणु
			u32			अगरindex;
			u32			hw_अगरindex;
			u8			h_source[ETH_ALEN];
			u8			h_dest[ETH_ALEN];
		पूर्ण out;
		क्रमागत flow_offload_xmit_type	xmit_type;
	पूर्ण tuple[FLOW_OFFLOAD_सूची_MAX];
पूर्ण;

काष्ठा flow_offload *flow_offload_alloc(काष्ठा nf_conn *ct);
व्योम flow_offload_मुक्त(काष्ठा flow_offload *flow);

अटल अंतरभूत पूर्णांक
nf_flow_table_offload_add_cb(काष्ठा nf_flowtable *flow_table,
			     flow_setup_cb_t *cb, व्योम *cb_priv)
अणु
	काष्ठा flow_block *block = &flow_table->flow_block;
	काष्ठा flow_block_cb *block_cb;
	पूर्णांक err = 0;

	करोwn_ग_लिखो(&flow_table->flow_block_lock);
	block_cb = flow_block_cb_lookup(block, cb, cb_priv);
	अगर (block_cb) अणु
		err = -EEXIST;
		जाओ unlock;
	पूर्ण

	block_cb = flow_block_cb_alloc(cb, cb_priv, cb_priv, शून्य);
	अगर (IS_ERR(block_cb)) अणु
		err = PTR_ERR(block_cb);
		जाओ unlock;
	पूर्ण

	list_add_tail(&block_cb->list, &block->cb_list);

unlock:
	up_ग_लिखो(&flow_table->flow_block_lock);
	वापस err;
पूर्ण

अटल अंतरभूत व्योम
nf_flow_table_offload_del_cb(काष्ठा nf_flowtable *flow_table,
			     flow_setup_cb_t *cb, व्योम *cb_priv)
अणु
	काष्ठा flow_block *block = &flow_table->flow_block;
	काष्ठा flow_block_cb *block_cb;

	करोwn_ग_लिखो(&flow_table->flow_block_lock);
	block_cb = flow_block_cb_lookup(block, cb, cb_priv);
	अगर (block_cb) अणु
		list_del(&block_cb->list);
		flow_block_cb_मुक्त(block_cb);
	पूर्ण अन्यथा अणु
		WARN_ON(true);
	पूर्ण
	up_ग_लिखो(&flow_table->flow_block_lock);
पूर्ण

पूर्णांक flow_offload_route_init(काष्ठा flow_offload *flow,
			    स्थिर काष्ठा nf_flow_route *route);

पूर्णांक flow_offload_add(काष्ठा nf_flowtable *flow_table, काष्ठा flow_offload *flow);
व्योम flow_offload_refresh(काष्ठा nf_flowtable *flow_table,
			  काष्ठा flow_offload *flow);

काष्ठा flow_offload_tuple_rhash *flow_offload_lookup(काष्ठा nf_flowtable *flow_table,
						     काष्ठा flow_offload_tuple *tuple);
व्योम nf_flow_table_gc_cleanup(काष्ठा nf_flowtable *flowtable,
			      काष्ठा net_device *dev);
व्योम nf_flow_table_cleanup(काष्ठा net_device *dev);

पूर्णांक nf_flow_table_init(काष्ठा nf_flowtable *flow_table);
व्योम nf_flow_table_मुक्त(काष्ठा nf_flowtable *flow_table);

व्योम flow_offload_tearकरोwn(काष्ठा flow_offload *flow);

व्योम nf_flow_snat_port(स्थिर काष्ठा flow_offload *flow,
		       काष्ठा sk_buff *skb, अचिन्हित पूर्णांक thoff,
		       u8 protocol, क्रमागत flow_offload_tuple_dir dir);
व्योम nf_flow_dnat_port(स्थिर काष्ठा flow_offload *flow,
		       काष्ठा sk_buff *skb, अचिन्हित पूर्णांक thoff,
		       u8 protocol, क्रमागत flow_offload_tuple_dir dir);

काष्ठा flow_ports अणु
	__be16 source, dest;
पूर्ण;

अचिन्हित पूर्णांक nf_flow_offload_ip_hook(व्योम *priv, काष्ठा sk_buff *skb,
				     स्थिर काष्ठा nf_hook_state *state);
अचिन्हित पूर्णांक nf_flow_offload_ipv6_hook(व्योम *priv, काष्ठा sk_buff *skb,
				       स्थिर काष्ठा nf_hook_state *state);

#घोषणा MODULE_ALIAS_NF_FLOWTABLE(family)	\
	MODULE_ALIAS("nf-flowtable-" __stringअगरy(family))

व्योम nf_flow_offload_add(काष्ठा nf_flowtable *flowtable,
			 काष्ठा flow_offload *flow);
व्योम nf_flow_offload_del(काष्ठा nf_flowtable *flowtable,
			 काष्ठा flow_offload *flow);
व्योम nf_flow_offload_stats(काष्ठा nf_flowtable *flowtable,
			   काष्ठा flow_offload *flow);

व्योम nf_flow_table_offload_flush(काष्ठा nf_flowtable *flowtable);
पूर्णांक nf_flow_table_offload_setup(काष्ठा nf_flowtable *flowtable,
				काष्ठा net_device *dev,
				क्रमागत flow_block_command cmd);
पूर्णांक nf_flow_rule_route_ipv4(काष्ठा net *net, स्थिर काष्ठा flow_offload *flow,
			    क्रमागत flow_offload_tuple_dir dir,
			    काष्ठा nf_flow_rule *flow_rule);
पूर्णांक nf_flow_rule_route_ipv6(काष्ठा net *net, स्थिर काष्ठा flow_offload *flow,
			    क्रमागत flow_offload_tuple_dir dir,
			    काष्ठा nf_flow_rule *flow_rule);

पूर्णांक nf_flow_table_offload_init(व्योम);
व्योम nf_flow_table_offload_निकास(व्योम);

#पूर्ण_अगर /* _NF_FLOW_TABLE_H */
