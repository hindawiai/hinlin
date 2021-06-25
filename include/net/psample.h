<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NET_PSAMPLE_H
#घोषणा __NET_PSAMPLE_H

#समावेश <uapi/linux/psample.h>
#समावेश <linux/list.h>

काष्ठा psample_group अणु
	काष्ठा list_head list;
	काष्ठा net *net;
	u32 group_num;
	u32 refcount;
	u32 seq;
	काष्ठा rcu_head rcu;
पूर्ण;

काष्ठा psample_metadata अणु
	u32 trunc_size;
	पूर्णांक in_अगरindex;
	पूर्णांक out_अगरindex;
	u16 out_tc;
	u64 out_tc_occ;	/* bytes */
	u64 latency;	/* nanoseconds */
	u8 out_tc_valid:1,
	   out_tc_occ_valid:1,
	   latency_valid:1,
	   unused:5;
पूर्ण;

काष्ठा psample_group *psample_group_get(काष्ठा net *net, u32 group_num);
व्योम psample_group_take(काष्ठा psample_group *group);
व्योम psample_group_put(काष्ठा psample_group *group);

#अगर IS_ENABLED(CONFIG_PSAMPLE)

व्योम psample_sample_packet(काष्ठा psample_group *group, काष्ठा sk_buff *skb,
			   u32 sample_rate, स्थिर काष्ठा psample_metadata *md);

#अन्यथा

अटल अंतरभूत व्योम psample_sample_packet(काष्ठा psample_group *group,
					 काष्ठा sk_buff *skb, u32 sample_rate,
					 स्थिर काष्ठा psample_metadata *md)
अणु
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* __NET_PSAMPLE_H */
