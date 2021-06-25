<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2016 Qualcomm Atheros, Inc
 *
 * Based on net/sched/sch_fq_codel.c
 */
#अगर_अघोषित __NET_SCHED_FQ_H
#घोषणा __NET_SCHED_FQ_H

काष्ठा fq_tin;

/**
 * काष्ठा fq_flow - per traffic flow queue
 *
 * @tin: owner of this flow. Used to manage collisions, i.e. when a packet
 *	hashes to an index which poपूर्णांकs to a flow that is alपढ़ोy owned by a
 *	dअगरferent tin the packet is destined to. In such हाल the implementer
 *	must provide a fallback flow
 * @flowchain: can be linked to fq_tin's new_flows or old_flows. Used क्रम DRR++
 *	(deficit round robin) based round robin queuing similar to the one
 *	found in net/sched/sch_fq_codel.c
 * @queue: sk_buff queue to hold packets
 * @backlog: number of bytes pending in the queue. The number of packets can be
 *	found in @queue.qlen
 * @deficit: used क्रम DRR++
 */
काष्ठा fq_flow अणु
	काष्ठा fq_tin *tin;
	काष्ठा list_head flowchain;
	काष्ठा sk_buff_head queue;
	u32 backlog;
	पूर्णांक deficit;
पूर्ण;

/**
 * काष्ठा fq_tin - a logical container of fq_flows
 *
 * Used to group fq_flows पूर्णांकo a logical aggregate. DRR++ scheme is used to
 * pull पूर्णांकerleaved packets out of the associated flows.
 *
 * @new_flows: linked list of fq_flow
 * @old_flows: linked list of fq_flow
 */
काष्ठा fq_tin अणु
	काष्ठा list_head new_flows;
	काष्ठा list_head old_flows;
	काष्ठा list_head tin_list;
	काष्ठा fq_flow शेष_flow;
	u32 backlog_bytes;
	u32 backlog_packets;
	u32 overlimit;
	u32 collisions;
	u32 flows;
	u32 tx_bytes;
	u32 tx_packets;
पूर्ण;

/**
 * काष्ठा fq - मुख्य container क्रम fair queuing purposes
 *
 * @limit: max number of packets that can be queued across all flows
 * @backlog: number of packets queued across all flows
 */
काष्ठा fq अणु
	काष्ठा fq_flow *flows;
	अचिन्हित दीर्घ *flows_biपंचांगap;

	काष्ठा list_head tin_backlog;
	spinlock_t lock;
	u32 flows_cnt;
	u32 limit;
	u32 memory_limit;
	u32 memory_usage;
	u32 quantum;
	u32 backlog;
	u32 overlimit;
	u32 overmemory;
	u32 collisions;
पूर्ण;

प्रकार काष्ठा sk_buff *fq_tin_dequeue_t(काष्ठा fq *,
					 काष्ठा fq_tin *,
					 काष्ठा fq_flow *flow);

प्रकार व्योम fq_skb_मुक्त_t(काष्ठा fq *,
			   काष्ठा fq_tin *,
			   काष्ठा fq_flow *,
			   काष्ठा sk_buff *);

/* Return %true to filter (drop) the frame. */
प्रकार bool fq_skb_filter_t(काष्ठा fq *,
			     काष्ठा fq_tin *,
			     काष्ठा fq_flow *,
			     काष्ठा sk_buff *,
			     व्योम *);

प्रकार काष्ठा fq_flow *fq_flow_get_शेष_t(काष्ठा fq *,
					      काष्ठा fq_tin *,
					      पूर्णांक idx,
					      काष्ठा sk_buff *);

#पूर्ण_अगर
