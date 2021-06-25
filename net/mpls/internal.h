<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित MPLS_INTERNAL_H
#घोषणा MPLS_INTERNAL_H
#समावेश <net/mpls.h>

/* put a reasonable limit on the number of labels
 * we will accept from userspace
 */
#घोषणा MAX_NEW_LABELS 30

काष्ठा mpls_entry_decoded अणु
	u32 label;
	u8 ttl;
	u8 tc;
	u8 bos;
पूर्ण;

काष्ठा mpls_pcpu_stats अणु
	काष्ठा mpls_link_stats	stats;
	काष्ठा u64_stats_sync	syncp;
पूर्ण;

काष्ठा mpls_dev अणु
	पूर्णांक				input_enabled;
	काष्ठा net_device		*dev;
	काष्ठा mpls_pcpu_stats __percpu	*stats;

	काष्ठा ctl_table_header		*sysctl;
	काष्ठा rcu_head			rcu;
पूर्ण;

#अगर BITS_PER_LONG == 32

#घोषणा MPLS_INC_STATS_LEN(mdev, len, pkts_field, bytes_field)		\
	करो अणु								\
		__typeof__(*(mdev)->stats) *ptr =			\
			raw_cpu_ptr((mdev)->stats);			\
		local_bh_disable();					\
		u64_stats_update_begin(&ptr->syncp);			\
		ptr->stats.pkts_field++;				\
		ptr->stats.bytes_field += (len);			\
		u64_stats_update_end(&ptr->syncp);			\
		local_bh_enable();					\
	पूर्ण जबतक (0)

#घोषणा MPLS_INC_STATS(mdev, field)					\
	करो अणु								\
		__typeof__(*(mdev)->stats) *ptr =			\
			raw_cpu_ptr((mdev)->stats);			\
		local_bh_disable();					\
		u64_stats_update_begin(&ptr->syncp);			\
		ptr->stats.field++;					\
		u64_stats_update_end(&ptr->syncp);			\
		local_bh_enable();					\
	पूर्ण जबतक (0)

#अन्यथा

#घोषणा MPLS_INC_STATS_LEN(mdev, len, pkts_field, bytes_field)		\
	करो अणु								\
		this_cpu_inc((mdev)->stats->stats.pkts_field);		\
		this_cpu_add((mdev)->stats->stats.bytes_field, (len));	\
	पूर्ण जबतक (0)

#घोषणा MPLS_INC_STATS(mdev, field)			\
	this_cpu_inc((mdev)->stats->stats.field)

#पूर्ण_अगर

काष्ठा sk_buff;

#घोषणा LABEL_NOT_SPECIFIED (1 << 20)

/* This maximum ha length copied from the definition of काष्ठा neighbour */
#घोषणा VIA_ALEN_ALIGN माप(अचिन्हित दीर्घ)
#घोषणा MAX_VIA_ALEN (ALIGN(MAX_ADDR_LEN, VIA_ALEN_ALIGN))

क्रमागत mpls_payload_type अणु
	MPT_UNSPEC, /* IPv4 or IPv6 */
	MPT_IPV4 = 4,
	MPT_IPV6 = 6,

	/* Other types not implemented:
	 *  - Pseuकरो-wire with or without control word (RFC4385)
	 *  - GAL (RFC5586)
	 */
पूर्ण;

काष्ठा mpls_nh अणु /* next hop label क्रमwarding entry */
	काष्ठा net_device __rcu *nh_dev;

	/* nh_flags is accessed under RCU in the packet path; it is
	 * modअगरied handling netdev events with rtnl lock held
	 */
	अचिन्हित पूर्णांक		nh_flags;
	u8			nh_labels;
	u8			nh_via_alen;
	u8			nh_via_table;
	u8			nh_reserved1;

	u32			nh_label[];
पूर्ण;

/* offset of via from beginning of mpls_nh */
#घोषणा MPLS_NH_VIA_OFF(num_labels) \
		ALIGN(माप(काष्ठा mpls_nh) + (num_labels) * माप(u32), \
		      VIA_ALEN_ALIGN)

/* all nexthops within a route have the same size based on the
 * max number of labels and max via length across all nexthops
 */
#घोषणा MPLS_NH_SIZE(num_labels, max_via_alen)		\
		(MPLS_NH_VIA_OFF((num_labels)) +	\
		ALIGN((max_via_alen), VIA_ALEN_ALIGN))

क्रमागत mpls_ttl_propagation अणु
	MPLS_TTL_PROP_DEFAULT,
	MPLS_TTL_PROP_ENABLED,
	MPLS_TTL_PROP_DISABLED,
पूर्ण;

/* The route, nexthops and vias are stored together in the same memory
 * block:
 *
 * +----------------------+
 * | mpls_route           |
 * +----------------------+
 * | mpls_nh 0            |
 * +----------------------+
 * | alignment padding    |   4 bytes क्रम odd number of labels
 * +----------------------+
 * | via[rt_max_alen] 0   |
 * +----------------------+
 * | alignment padding    |   via's aligned on माप(अचिन्हित दीर्घ)
 * +----------------------+
 * | ...                  |
 * +----------------------+
 * | mpls_nh n-1          |
 * +----------------------+
 * | via[rt_max_alen] n-1 |
 * +----------------------+
 */
काष्ठा mpls_route अणु /* next hop label क्रमwarding entry */
	काष्ठा rcu_head		rt_rcu;
	u8			rt_protocol;
	u8			rt_payload_type;
	u8			rt_max_alen;
	u8			rt_ttl_propagate;
	u8			rt_nhn;
	/* rt_nhn_alive is accessed under RCU in the packet path; it
	 * is modअगरied handling netdev events with rtnl lock held
	 */
	u8			rt_nhn_alive;
	u8			rt_nh_size;
	u8			rt_via_offset;
	u8			rt_reserved1;
	काष्ठा mpls_nh		rt_nh[];
पूर्ण;

#घोषणा क्रम_nexthops(rt) अणु						\
	पूर्णांक nhsel; काष्ठा mpls_nh *nh;  u8 *__nh;			\
	क्रम (nhsel = 0, nh = (rt)->rt_nh, __nh = (u8 *)((rt)->rt_nh);	\
	     nhsel < (rt)->rt_nhn;					\
	     __nh += rt->rt_nh_size, nh = (काष्ठा mpls_nh *)__nh, nhsel++)

#घोषणा change_nexthops(rt) अणु						\
	पूर्णांक nhsel; काष्ठा mpls_nh *nh; u8 *__nh;			\
	क्रम (nhsel = 0, nh = (काष्ठा mpls_nh *)((rt)->rt_nh),		\
			__nh = (u8 *)((rt)->rt_nh);			\
	     nhsel < (rt)->rt_nhn;					\
	     __nh += rt->rt_nh_size, nh = (काष्ठा mpls_nh *)__nh, nhsel++)

#घोषणा endक्रम_nexthops(rt) पूर्ण

अटल अंतरभूत काष्ठा mpls_entry_decoded mpls_entry_decode(काष्ठा mpls_shim_hdr *hdr)
अणु
	काष्ठा mpls_entry_decoded result;
	अचिन्हित entry = be32_to_cpu(hdr->label_stack_entry);

	result.label = (entry & MPLS_LS_LABEL_MASK) >> MPLS_LS_LABEL_SHIFT;
	result.ttl = (entry & MPLS_LS_TTL_MASK) >> MPLS_LS_TTL_SHIFT;
	result.tc =  (entry & MPLS_LS_TC_MASK) >> MPLS_LS_TC_SHIFT;
	result.bos = (entry & MPLS_LS_S_MASK) >> MPLS_LS_S_SHIFT;

	वापस result;
पूर्ण

अटल अंतरभूत काष्ठा mpls_dev *mpls_dev_get(स्थिर काष्ठा net_device *dev)
अणु
	वापस rcu_dereference_rtnl(dev->mpls_ptr);
पूर्ण

पूर्णांक nla_put_labels(काष्ठा sk_buff *skb, पूर्णांक attrtype,  u8 labels,
		   स्थिर u32 label[]);
पूर्णांक nla_get_labels(स्थिर काष्ठा nlattr *nla, u8 max_labels, u8 *labels,
		   u32 label[], काष्ठा netlink_ext_ack *extack);
bool mpls_output_possible(स्थिर काष्ठा net_device *dev);
अचिन्हित पूर्णांक mpls_dev_mtu(स्थिर काष्ठा net_device *dev);
bool mpls_pkt_too_big(स्थिर काष्ठा sk_buff *skb, अचिन्हित पूर्णांक mtu);
व्योम mpls_stats_inc_outucastpkts(काष्ठा net_device *dev,
				 स्थिर काष्ठा sk_buff *skb);

#पूर्ण_अगर /* MPLS_INTERNAL_H */
