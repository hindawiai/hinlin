<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2014      Protonic Holland,
 *                         David Jander
 * Copyright (C) 2014-2017 Pengutronix,
 *                         Marc Kleine-Budde <kernel@pengutronix.de>
 */

#समावेश <linux/can/dev.h>
#समावेश <linux/can/rx-offload.h>

काष्ठा can_rx_offload_cb अणु
	u32 बारtamp;
पूर्ण;

अटल अंतरभूत काष्ठा can_rx_offload_cb *
can_rx_offload_get_cb(काष्ठा sk_buff *skb)
अणु
	BUILD_BUG_ON(माप(काष्ठा can_rx_offload_cb) > माप(skb->cb));

	वापस (काष्ठा can_rx_offload_cb *)skb->cb;
पूर्ण

अटल अंतरभूत bool
can_rx_offload_le(काष्ठा can_rx_offload *offload,
		  अचिन्हित पूर्णांक a, अचिन्हित पूर्णांक b)
अणु
	अगर (offload->inc)
		वापस a <= b;
	अन्यथा
		वापस a >= b;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
can_rx_offload_inc(काष्ठा can_rx_offload *offload, अचिन्हित पूर्णांक *val)
अणु
	अगर (offload->inc)
		वापस (*val)++;
	अन्यथा
		वापस (*val)--;
पूर्ण

अटल पूर्णांक can_rx_offload_napi_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक quota)
अणु
	काष्ठा can_rx_offload *offload = container_of(napi,
						      काष्ठा can_rx_offload,
						      napi);
	काष्ठा net_device *dev = offload->dev;
	काष्ठा net_device_stats *stats = &dev->stats;
	काष्ठा sk_buff *skb;
	पूर्णांक work_करोne = 0;

	जबतक ((work_करोne < quota) &&
	       (skb = skb_dequeue(&offload->skb_queue))) अणु
		काष्ठा can_frame *cf = (काष्ठा can_frame *)skb->data;

		work_करोne++;
		stats->rx_packets++;
		stats->rx_bytes += cf->len;
		netअगर_receive_skb(skb);
	पूर्ण

	अगर (work_करोne < quota) अणु
		napi_complete_करोne(napi, work_करोne);

		/* Check अगर there was another पूर्णांकerrupt */
		अगर (!skb_queue_empty(&offload->skb_queue))
			napi_reschedule(&offload->napi);
	पूर्ण

	can_led_event(offload->dev, CAN_LED_EVENT_RX);

	वापस work_करोne;
पूर्ण

अटल अंतरभूत व्योम
__skb_queue_add_sort(काष्ठा sk_buff_head *head, काष्ठा sk_buff *new,
		     पूर्णांक (*compare)(काष्ठा sk_buff *a, काष्ठा sk_buff *b))
अणु
	काष्ठा sk_buff *pos, *insert = शून्य;

	skb_queue_reverse_walk(head, pos) अणु
		स्थिर काष्ठा can_rx_offload_cb *cb_pos, *cb_new;

		cb_pos = can_rx_offload_get_cb(pos);
		cb_new = can_rx_offload_get_cb(new);

		netdev_dbg(new->dev,
			   "%s: pos=0x%08x, new=0x%08x, diff=%10d, queue_len=%d\n",
			   __func__,
			   cb_pos->बारtamp, cb_new->बारtamp,
			   cb_new->बारtamp - cb_pos->बारtamp,
			   skb_queue_len(head));

		अगर (compare(pos, new) < 0)
			जारी;
		insert = pos;
		अवरोध;
	पूर्ण
	अगर (!insert)
		__skb_queue_head(head, new);
	अन्यथा
		__skb_queue_after(head, insert, new);
पूर्ण

अटल पूर्णांक can_rx_offload_compare(काष्ठा sk_buff *a, काष्ठा sk_buff *b)
अणु
	स्थिर काष्ठा can_rx_offload_cb *cb_a, *cb_b;

	cb_a = can_rx_offload_get_cb(a);
	cb_b = can_rx_offload_get_cb(b);

	/* Subtract two u32 and वापस result as पूर्णांक, to keep
	 * dअगरference steady around the u32 overflow.
	 */
	वापस cb_b->बारtamp - cb_a->बारtamp;
पूर्ण

/**
 * can_rx_offload_offload_one() - Read one CAN frame from HW
 * @offload: poपूर्णांकer to rx_offload context
 * @n: number of mailbox to पढ़ो
 *
 * The task of this function is to पढ़ो a CAN frame from mailbox @n
 * from the device and वापस the mailbox's content as a काष्ठा
 * sk_buff.
 *
 * If the काष्ठा can_rx_offload::skb_queue exceeds the maximal queue
 * length (काष्ठा can_rx_offload::skb_queue_len_max) or no skb can be
 * allocated, the mailbox contents is discarded by पढ़ोing it पूर्णांकo an
 * overflow buffer. This way the mailbox is marked as मुक्त by the
 * driver.
 *
 * Return: A poपूर्णांकer to skb containing the CAN frame on success.
 *
 *         शून्य अगर the mailbox @n is empty.
 *
 *         ERR_PTR() in हाल of an error
 */
अटल काष्ठा sk_buff *
can_rx_offload_offload_one(काष्ठा can_rx_offload *offload, अचिन्हित पूर्णांक n)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा can_rx_offload_cb *cb;
	bool drop = false;
	u32 बारtamp;

	/* If queue is full drop frame */
	अगर (unlikely(skb_queue_len(&offload->skb_queue) >
		     offload->skb_queue_len_max))
		drop = true;

	skb = offload->mailbox_पढ़ो(offload, n, &बारtamp, drop);
	/* Mailbox was empty. */
	अगर (unlikely(!skb))
		वापस शून्य;

	/* There was a problem पढ़ोing the mailbox, propagate
	 * error value.
	 */
	अगर (IS_ERR(skb)) अणु
		offload->dev->stats.rx_dropped++;
		offload->dev->stats.rx_fअगरo_errors++;

		वापस skb;
	पूर्ण

	/* Mailbox was पढ़ो. */
	cb = can_rx_offload_get_cb(skb);
	cb->बारtamp = बारtamp;

	वापस skb;
पूर्ण

पूर्णांक can_rx_offload_irq_offload_बारtamp(काष्ठा can_rx_offload *offload,
					 u64 pending)
अणु
	काष्ठा sk_buff_head skb_queue;
	अचिन्हित पूर्णांक i;

	__skb_queue_head_init(&skb_queue);

	क्रम (i = offload->mb_first;
	     can_rx_offload_le(offload, i, offload->mb_last);
	     can_rx_offload_inc(offload, &i)) अणु
		काष्ठा sk_buff *skb;

		अगर (!(pending & BIT_ULL(i)))
			जारी;

		skb = can_rx_offload_offload_one(offload, i);
		अगर (IS_ERR_OR_शून्य(skb))
			जारी;

		__skb_queue_add_sort(&skb_queue, skb, can_rx_offload_compare);
	पूर्ण

	अगर (!skb_queue_empty(&skb_queue)) अणु
		अचिन्हित दीर्घ flags;
		u32 queue_len;

		spin_lock_irqsave(&offload->skb_queue.lock, flags);
		skb_queue_splice_tail(&skb_queue, &offload->skb_queue);
		spin_unlock_irqrestore(&offload->skb_queue.lock, flags);

		queue_len = skb_queue_len(&offload->skb_queue);
		अगर (queue_len > offload->skb_queue_len_max / 8)
			netdev_dbg(offload->dev, "%s: queue_len=%d\n",
				   __func__, queue_len);

		can_rx_offload_schedule(offload);
	पूर्ण

	वापस skb_queue_len(&skb_queue);
पूर्ण
EXPORT_SYMBOL_GPL(can_rx_offload_irq_offload_बारtamp);

पूर्णांक can_rx_offload_irq_offload_fअगरo(काष्ठा can_rx_offload *offload)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक received = 0;

	जबतक (1) अणु
		skb = can_rx_offload_offload_one(offload, 0);
		अगर (IS_ERR(skb))
			जारी;
		अगर (!skb)
			अवरोध;

		skb_queue_tail(&offload->skb_queue, skb);
		received++;
	पूर्ण

	अगर (received)
		can_rx_offload_schedule(offload);

	वापस received;
पूर्ण
EXPORT_SYMBOL_GPL(can_rx_offload_irq_offload_fअगरo);

पूर्णांक can_rx_offload_queue_sorted(काष्ठा can_rx_offload *offload,
				काष्ठा sk_buff *skb, u32 बारtamp)
अणु
	काष्ठा can_rx_offload_cb *cb;
	अचिन्हित दीर्घ flags;

	अगर (skb_queue_len(&offload->skb_queue) >
	    offload->skb_queue_len_max) अणु
		dev_kमुक्त_skb_any(skb);
		वापस -ENOBUFS;
	पूर्ण

	cb = can_rx_offload_get_cb(skb);
	cb->बारtamp = बारtamp;

	spin_lock_irqsave(&offload->skb_queue.lock, flags);
	__skb_queue_add_sort(&offload->skb_queue, skb, can_rx_offload_compare);
	spin_unlock_irqrestore(&offload->skb_queue.lock, flags);

	can_rx_offload_schedule(offload);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(can_rx_offload_queue_sorted);

अचिन्हित पूर्णांक can_rx_offload_get_echo_skb(काष्ठा can_rx_offload *offload,
					 अचिन्हित पूर्णांक idx, u32 बारtamp,
					 अचिन्हित पूर्णांक *frame_len_ptr)
अणु
	काष्ठा net_device *dev = offload->dev;
	काष्ठा net_device_stats *stats = &dev->stats;
	काष्ठा sk_buff *skb;
	u8 len;
	पूर्णांक err;

	skb = __can_get_echo_skb(dev, idx, &len, frame_len_ptr);
	अगर (!skb)
		वापस 0;

	err = can_rx_offload_queue_sorted(offload, skb, बारtamp);
	अगर (err) अणु
		stats->rx_errors++;
		stats->tx_fअगरo_errors++;
	पूर्ण

	वापस len;
पूर्ण
EXPORT_SYMBOL_GPL(can_rx_offload_get_echo_skb);

पूर्णांक can_rx_offload_queue_tail(काष्ठा can_rx_offload *offload,
			      काष्ठा sk_buff *skb)
अणु
	अगर (skb_queue_len(&offload->skb_queue) >
	    offload->skb_queue_len_max) अणु
		dev_kमुक्त_skb_any(skb);
		वापस -ENOBUFS;
	पूर्ण

	skb_queue_tail(&offload->skb_queue, skb);
	can_rx_offload_schedule(offload);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(can_rx_offload_queue_tail);

अटल पूर्णांक can_rx_offload_init_queue(काष्ठा net_device *dev,
				     काष्ठा can_rx_offload *offload,
				     अचिन्हित पूर्णांक weight)
अणु
	offload->dev = dev;

	/* Limit queue len to 4x the weight (rounted to next घातer of two) */
	offload->skb_queue_len_max = 2 << fls(weight);
	offload->skb_queue_len_max *= 4;
	skb_queue_head_init(&offload->skb_queue);

	netअगर_napi_add(dev, &offload->napi, can_rx_offload_napi_poll, weight);

	dev_dbg(dev->dev.parent, "%s: skb_queue_len_max=%d\n",
		__func__, offload->skb_queue_len_max);

	वापस 0;
पूर्ण

पूर्णांक can_rx_offload_add_बारtamp(काष्ठा net_device *dev,
				 काष्ठा can_rx_offload *offload)
अणु
	अचिन्हित पूर्णांक weight;

	अगर (offload->mb_first > BITS_PER_LONG_LONG ||
	    offload->mb_last > BITS_PER_LONG_LONG || !offload->mailbox_पढ़ो)
		वापस -EINVAL;

	अगर (offload->mb_first < offload->mb_last) अणु
		offload->inc = true;
		weight = offload->mb_last - offload->mb_first;
	पूर्ण अन्यथा अणु
		offload->inc = false;
		weight = offload->mb_first - offload->mb_last;
	पूर्ण

	वापस can_rx_offload_init_queue(dev, offload, weight);
पूर्ण
EXPORT_SYMBOL_GPL(can_rx_offload_add_बारtamp);

पूर्णांक can_rx_offload_add_fअगरo(काष्ठा net_device *dev,
			    काष्ठा can_rx_offload *offload, अचिन्हित पूर्णांक weight)
अणु
	अगर (!offload->mailbox_पढ़ो)
		वापस -EINVAL;

	वापस can_rx_offload_init_queue(dev, offload, weight);
पूर्ण
EXPORT_SYMBOL_GPL(can_rx_offload_add_fअगरo);

पूर्णांक can_rx_offload_add_manual(काष्ठा net_device *dev,
			      काष्ठा can_rx_offload *offload,
			      अचिन्हित पूर्णांक weight)
अणु
	अगर (offload->mailbox_पढ़ो)
		वापस -EINVAL;

	वापस can_rx_offload_init_queue(dev, offload, weight);
पूर्ण
EXPORT_SYMBOL_GPL(can_rx_offload_add_manual);

व्योम can_rx_offload_enable(काष्ठा can_rx_offload *offload)
अणु
	napi_enable(&offload->napi);
पूर्ण
EXPORT_SYMBOL_GPL(can_rx_offload_enable);

व्योम can_rx_offload_del(काष्ठा can_rx_offload *offload)
अणु
	netअगर_napi_del(&offload->napi);
	skb_queue_purge(&offload->skb_queue);
पूर्ण
EXPORT_SYMBOL_GPL(can_rx_offload_del);
