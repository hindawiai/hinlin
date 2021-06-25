<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NET_DST_OPS_H
#घोषणा _NET_DST_OPS_H
#समावेश <linux/types.h>
#समावेश <linux/percpu_counter.h>
#समावेश <linux/cache.h>

काष्ठा dst_entry;
काष्ठा kmem_cachep;
काष्ठा net_device;
काष्ठा sk_buff;
काष्ठा sock;
काष्ठा net;

काष्ठा dst_ops अणु
	अचिन्हित लघु		family;
	अचिन्हित पूर्णांक		gc_thresh;

	पूर्णांक			(*gc)(काष्ठा dst_ops *ops);
	काष्ठा dst_entry *	(*check)(काष्ठा dst_entry *, __u32 cookie);
	अचिन्हित पूर्णांक		(*शेष_advmss)(स्थिर काष्ठा dst_entry *);
	अचिन्हित पूर्णांक		(*mtu)(स्थिर काष्ठा dst_entry *);
	u32 *			(*cow_metrics)(काष्ठा dst_entry *, अचिन्हित दीर्घ);
	व्योम			(*destroy)(काष्ठा dst_entry *);
	व्योम			(*अगरकरोwn)(काष्ठा dst_entry *,
					  काष्ठा net_device *dev, पूर्णांक how);
	काष्ठा dst_entry *	(*negative_advice)(काष्ठा dst_entry *);
	व्योम			(*link_failure)(काष्ठा sk_buff *);
	व्योम			(*update_pmtu)(काष्ठा dst_entry *dst, काष्ठा sock *sk,
					       काष्ठा sk_buff *skb, u32 mtu,
					       bool confirm_neigh);
	व्योम			(*redirect)(काष्ठा dst_entry *dst, काष्ठा sock *sk,
					    काष्ठा sk_buff *skb);
	पूर्णांक			(*local_out)(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb);
	काष्ठा neighbour *	(*neigh_lookup)(स्थिर काष्ठा dst_entry *dst,
						काष्ठा sk_buff *skb,
						स्थिर व्योम *daddr);
	व्योम			(*confirm_neigh)(स्थिर काष्ठा dst_entry *dst,
						 स्थिर व्योम *daddr);

	काष्ठा kmem_cache	*kmem_cachep;

	काष्ठा percpu_counter	pcpuc_entries ____cacheline_aligned_in_smp;
पूर्ण;

अटल अंतरभूत पूर्णांक dst_entries_get_fast(काष्ठा dst_ops *dst)
अणु
	वापस percpu_counter_पढ़ो_positive(&dst->pcpuc_entries);
पूर्ण

अटल अंतरभूत पूर्णांक dst_entries_get_slow(काष्ठा dst_ops *dst)
अणु
	वापस percpu_counter_sum_positive(&dst->pcpuc_entries);
पूर्ण

#घोषणा DST_PERCPU_COUNTER_BATCH 32
अटल अंतरभूत व्योम dst_entries_add(काष्ठा dst_ops *dst, पूर्णांक val)
अणु
	percpu_counter_add_batch(&dst->pcpuc_entries, val,
				 DST_PERCPU_COUNTER_BATCH);
पूर्ण

अटल अंतरभूत पूर्णांक dst_entries_init(काष्ठा dst_ops *dst)
अणु
	वापस percpu_counter_init(&dst->pcpuc_entries, 0, GFP_KERNEL);
पूर्ण

अटल अंतरभूत व्योम dst_entries_destroy(काष्ठा dst_ops *dst)
अणु
	percpu_counter_destroy(&dst->pcpuc_entries);
पूर्ण

#पूर्ण_अगर
