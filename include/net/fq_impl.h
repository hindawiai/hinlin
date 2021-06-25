<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2016 Qualcomm Atheros, Inc
 *
 * Based on net/sched/sch_fq_codel.c
 */
#अगर_अघोषित __NET_SCHED_FQ_IMPL_H
#घोषणा __NET_SCHED_FQ_IMPL_H

#समावेश <net/fq.h>

/* functions that are embedded पूर्णांकo includer */


अटल व्योम
__fq_adjust_removal(काष्ठा fq *fq, काष्ठा fq_flow *flow, अचिन्हित पूर्णांक packets,
		    अचिन्हित पूर्णांक bytes, अचिन्हित पूर्णांक truesize)
अणु
	काष्ठा fq_tin *tin = flow->tin;
	पूर्णांक idx;

	tin->backlog_bytes -= bytes;
	tin->backlog_packets -= packets;
	flow->backlog -= bytes;
	fq->backlog -= packets;
	fq->memory_usage -= truesize;

	अगर (flow->backlog)
		वापस;

	अगर (flow == &tin->शेष_flow) अणु
		list_del_init(&tin->tin_list);
		वापस;
	पूर्ण

	idx = flow - fq->flows;
	__clear_bit(idx, fq->flows_biपंचांगap);
पूर्ण

अटल व्योम fq_adjust_removal(काष्ठा fq *fq,
			      काष्ठा fq_flow *flow,
			      काष्ठा sk_buff *skb)
अणु
	__fq_adjust_removal(fq, flow, 1, skb->len, skb->truesize);
पूर्ण

अटल काष्ठा sk_buff *fq_flow_dequeue(काष्ठा fq *fq,
				       काष्ठा fq_flow *flow)
अणु
	काष्ठा sk_buff *skb;

	lockdep_निश्चित_held(&fq->lock);

	skb = __skb_dequeue(&flow->queue);
	अगर (!skb)
		वापस शून्य;

	fq_adjust_removal(fq, flow, skb);

	वापस skb;
पूर्ण

अटल पूर्णांक fq_flow_drop(काष्ठा fq *fq, काष्ठा fq_flow *flow,
			fq_skb_मुक्त_t मुक्त_func)
अणु
	अचिन्हित पूर्णांक packets = 0, bytes = 0, truesize = 0;
	काष्ठा fq_tin *tin = flow->tin;
	काष्ठा sk_buff *skb;
	पूर्णांक pending;

	lockdep_निश्चित_held(&fq->lock);

	pending = min_t(पूर्णांक, 32, skb_queue_len(&flow->queue) / 2);
	करो अणु
		skb = __skb_dequeue(&flow->queue);
		अगर (!skb)
			अवरोध;

		packets++;
		bytes += skb->len;
		truesize += skb->truesize;
		मुक्त_func(fq, tin, flow, skb);
	पूर्ण जबतक (packets < pending);

	__fq_adjust_removal(fq, flow, packets, bytes, truesize);

	वापस packets;
पूर्ण

अटल काष्ठा sk_buff *fq_tin_dequeue(काष्ठा fq *fq,
				      काष्ठा fq_tin *tin,
				      fq_tin_dequeue_t dequeue_func)
अणु
	काष्ठा fq_flow *flow;
	काष्ठा list_head *head;
	काष्ठा sk_buff *skb;

	lockdep_निश्चित_held(&fq->lock);

begin:
	head = &tin->new_flows;
	अगर (list_empty(head)) अणु
		head = &tin->old_flows;
		अगर (list_empty(head))
			वापस शून्य;
	पूर्ण

	flow = list_first_entry(head, काष्ठा fq_flow, flowchain);

	अगर (flow->deficit <= 0) अणु
		flow->deficit += fq->quantum;
		list_move_tail(&flow->flowchain,
			       &tin->old_flows);
		जाओ begin;
	पूर्ण

	skb = dequeue_func(fq, tin, flow);
	अगर (!skb) अणु
		/* क्रमce a pass through old_flows to prevent starvation */
		अगर ((head == &tin->new_flows) &&
		    !list_empty(&tin->old_flows)) अणु
			list_move_tail(&flow->flowchain, &tin->old_flows);
		पूर्ण अन्यथा अणु
			list_del_init(&flow->flowchain);
			flow->tin = शून्य;
		पूर्ण
		जाओ begin;
	पूर्ण

	flow->deficit -= skb->len;
	tin->tx_bytes += skb->len;
	tin->tx_packets++;

	वापस skb;
पूर्ण

अटल u32 fq_flow_idx(काष्ठा fq *fq, काष्ठा sk_buff *skb)
अणु
	u32 hash = skb_get_hash(skb);

	वापस reciprocal_scale(hash, fq->flows_cnt);
पूर्ण

अटल काष्ठा fq_flow *fq_flow_classअगरy(काष्ठा fq *fq,
					काष्ठा fq_tin *tin, u32 idx,
					काष्ठा sk_buff *skb)
अणु
	काष्ठा fq_flow *flow;

	lockdep_निश्चित_held(&fq->lock);

	flow = &fq->flows[idx];
	अगर (flow->tin && flow->tin != tin) अणु
		flow = &tin->शेष_flow;
		tin->collisions++;
		fq->collisions++;
	पूर्ण

	अगर (!flow->tin)
		tin->flows++;

	वापस flow;
पूर्ण

अटल काष्ठा fq_flow *fq_find_fattest_flow(काष्ठा fq *fq)
अणु
	काष्ठा fq_tin *tin;
	काष्ठा fq_flow *flow = शून्य;
	u32 len = 0;
	पूर्णांक i;

	क्रम_each_set_bit(i, fq->flows_biपंचांगap, fq->flows_cnt) अणु
		काष्ठा fq_flow *cur = &fq->flows[i];
		अचिन्हित पूर्णांक cur_len;

		cur_len = cur->backlog;
		अगर (cur_len <= len)
			जारी;

		flow = cur;
		len = cur_len;
	पूर्ण

	list_क्रम_each_entry(tin, &fq->tin_backlog, tin_list) अणु
		अचिन्हित पूर्णांक cur_len = tin->शेष_flow.backlog;

		अगर (cur_len <= len)
			जारी;

		flow = &tin->शेष_flow;
		len = cur_len;
	पूर्ण

	वापस flow;
पूर्ण

अटल व्योम fq_tin_enqueue(काष्ठा fq *fq,
			   काष्ठा fq_tin *tin, u32 idx,
			   काष्ठा sk_buff *skb,
			   fq_skb_मुक्त_t मुक्त_func)
अणु
	काष्ठा fq_flow *flow;
	bool oom;

	lockdep_निश्चित_held(&fq->lock);

	flow = fq_flow_classअगरy(fq, tin, idx, skb);

	अगर (!flow->backlog) अणु
		अगर (flow != &tin->शेष_flow)
			__set_bit(idx, fq->flows_biपंचांगap);
		अन्यथा अगर (list_empty(&tin->tin_list))
			list_add(&tin->tin_list, &fq->tin_backlog);
	पूर्ण

	flow->tin = tin;
	flow->backlog += skb->len;
	tin->backlog_bytes += skb->len;
	tin->backlog_packets++;
	fq->memory_usage += skb->truesize;
	fq->backlog++;

	अगर (list_empty(&flow->flowchain)) अणु
		flow->deficit = fq->quantum;
		list_add_tail(&flow->flowchain,
			      &tin->new_flows);
	पूर्ण

	__skb_queue_tail(&flow->queue, skb);
	oom = (fq->memory_usage > fq->memory_limit);
	जबतक (fq->backlog > fq->limit || oom) अणु
		flow = fq_find_fattest_flow(fq);
		अगर (!flow)
			वापस;

		अगर (!fq_flow_drop(fq, flow, मुक्त_func))
			वापस;

		flow->tin->overlimit++;
		fq->overlimit++;
		अगर (oom) अणु
			fq->overmemory++;
			oom = (fq->memory_usage > fq->memory_limit);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम fq_flow_filter(काष्ठा fq *fq,
			   काष्ठा fq_flow *flow,
			   fq_skb_filter_t filter_func,
			   व्योम *filter_data,
			   fq_skb_मुक्त_t मुक्त_func)
अणु
	काष्ठा fq_tin *tin = flow->tin;
	काष्ठा sk_buff *skb, *पंचांगp;

	lockdep_निश्चित_held(&fq->lock);

	skb_queue_walk_safe(&flow->queue, skb, पंचांगp) अणु
		अगर (!filter_func(fq, tin, flow, skb, filter_data))
			जारी;

		__skb_unlink(skb, &flow->queue);
		fq_adjust_removal(fq, flow, skb);
		मुक्त_func(fq, tin, flow, skb);
	पूर्ण
पूर्ण

अटल व्योम fq_tin_filter(काष्ठा fq *fq,
			  काष्ठा fq_tin *tin,
			  fq_skb_filter_t filter_func,
			  व्योम *filter_data,
			  fq_skb_मुक्त_t मुक्त_func)
अणु
	काष्ठा fq_flow *flow;

	lockdep_निश्चित_held(&fq->lock);

	list_क्रम_each_entry(flow, &tin->new_flows, flowchain)
		fq_flow_filter(fq, flow, filter_func, filter_data, मुक्त_func);
	list_क्रम_each_entry(flow, &tin->old_flows, flowchain)
		fq_flow_filter(fq, flow, filter_func, filter_data, मुक्त_func);
पूर्ण

अटल व्योम fq_flow_reset(काष्ठा fq *fq,
			  काष्ठा fq_flow *flow,
			  fq_skb_मुक्त_t मुक्त_func)
अणु
	काष्ठा fq_tin *tin = flow->tin;
	काष्ठा sk_buff *skb;

	जबतक ((skb = fq_flow_dequeue(fq, flow)))
		मुक्त_func(fq, tin, flow, skb);

	अगर (!list_empty(&flow->flowchain)) अणु
		list_del_init(&flow->flowchain);
		अगर (list_empty(&tin->new_flows) &&
		    list_empty(&tin->old_flows))
			list_del_init(&tin->tin_list);
	पूर्ण

	flow->tin = शून्य;

	WARN_ON_ONCE(flow->backlog);
पूर्ण

अटल व्योम fq_tin_reset(काष्ठा fq *fq,
			 काष्ठा fq_tin *tin,
			 fq_skb_मुक्त_t मुक्त_func)
अणु
	काष्ठा list_head *head;
	काष्ठा fq_flow *flow;

	क्रम (;;) अणु
		head = &tin->new_flows;
		अगर (list_empty(head)) अणु
			head = &tin->old_flows;
			अगर (list_empty(head))
				अवरोध;
		पूर्ण

		flow = list_first_entry(head, काष्ठा fq_flow, flowchain);
		fq_flow_reset(fq, flow, मुक्त_func);
	पूर्ण

	WARN_ON_ONCE(!list_empty(&tin->tin_list));
	WARN_ON_ONCE(tin->backlog_bytes);
	WARN_ON_ONCE(tin->backlog_packets);
पूर्ण

अटल व्योम fq_flow_init(काष्ठा fq_flow *flow)
अणु
	INIT_LIST_HEAD(&flow->flowchain);
	__skb_queue_head_init(&flow->queue);
पूर्ण

अटल व्योम fq_tin_init(काष्ठा fq_tin *tin)
अणु
	INIT_LIST_HEAD(&tin->new_flows);
	INIT_LIST_HEAD(&tin->old_flows);
	INIT_LIST_HEAD(&tin->tin_list);
	fq_flow_init(&tin->शेष_flow);
पूर्ण

अटल पूर्णांक fq_init(काष्ठा fq *fq, पूर्णांक flows_cnt)
अणु
	पूर्णांक i;

	स_रखो(fq, 0, माप(fq[0]));
	spin_lock_init(&fq->lock);
	INIT_LIST_HEAD(&fq->tin_backlog);
	fq->flows_cnt = max_t(u32, flows_cnt, 1);
	fq->quantum = 300;
	fq->limit = 8192;
	fq->memory_limit = 16 << 20; /* 16 MBytes */

	fq->flows = kvसुस्मृति(fq->flows_cnt, माप(fq->flows[0]), GFP_KERNEL);
	अगर (!fq->flows)
		वापस -ENOMEM;

	fq->flows_biपंचांगap = kसुस्मृति(BITS_TO_LONGS(fq->flows_cnt), माप(दीर्घ),
				   GFP_KERNEL);
	अगर (!fq->flows_biपंचांगap) अणु
		kvमुक्त(fq->flows);
		fq->flows = शून्य;
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < fq->flows_cnt; i++)
		fq_flow_init(&fq->flows[i]);

	वापस 0;
पूर्ण

अटल व्योम fq_reset(काष्ठा fq *fq,
		     fq_skb_मुक्त_t मुक्त_func)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < fq->flows_cnt; i++)
		fq_flow_reset(fq, &fq->flows[i], मुक्त_func);

	kvमुक्त(fq->flows);
	fq->flows = शून्य;

	kमुक्त(fq->flows_biपंचांगap);
	fq->flows_biपंचांगap = शून्य;
पूर्ण

#पूर्ण_अगर
