<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * TI Common Platक्रमm Time Sync
 *
 * Copyright (C) 2012 Riअक्षरd Cochran <riअक्षरdcochran@gmail.com>
 *
 */
#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/अगर.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/module.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/ptp_classअगरy.h>
#समावेश <linux/समय.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>

#समावेश "cpts.h"

#घोषणा CPTS_SKB_TX_WORK_TIMEOUT 1 /* jअगरfies */
#घोषणा CPTS_SKB_RX_TX_TMO 100 /*ms */
#घोषणा CPTS_EVENT_RX_TX_TIMEOUT (100) /* ms */

काष्ठा cpts_skb_cb_data अणु
	u32 skb_mtype_seqid;
	अचिन्हित दीर्घ पंचांगo;
पूर्ण;

#घोषणा cpts_पढ़ो32(c, r)	पढ़ोl_relaxed(&c->reg->r)
#घोषणा cpts_ग_लिखो32(c, v, r)	ग_लिखोl_relaxed(v, &c->reg->r)

अटल पूर्णांक cpts_event_port(काष्ठा cpts_event *event)
अणु
	वापस (event->high >> PORT_NUMBER_SHIFT) & PORT_NUMBER_MASK;
पूर्ण

अटल पूर्णांक event_expired(काष्ठा cpts_event *event)
अणु
	वापस समय_after(jअगरfies, event->पंचांगo);
पूर्ण

अटल पूर्णांक event_type(काष्ठा cpts_event *event)
अणु
	वापस (event->high >> EVENT_TYPE_SHIFT) & EVENT_TYPE_MASK;
पूर्ण

अटल पूर्णांक cpts_fअगरo_pop(काष्ठा cpts *cpts, u32 *high, u32 *low)
अणु
	u32 r = cpts_पढ़ो32(cpts, पूर्णांकstat_raw);

	अगर (r & TS_PEND_RAW) अणु
		*high = cpts_पढ़ो32(cpts, event_high);
		*low  = cpts_पढ़ो32(cpts, event_low);
		cpts_ग_लिखो32(cpts, EVENT_POP, event_pop);
		वापस 0;
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक cpts_purge_events(काष्ठा cpts *cpts)
अणु
	काष्ठा list_head *this, *next;
	काष्ठा cpts_event *event;
	पूर्णांक हटाओd = 0;

	list_क्रम_each_safe(this, next, &cpts->events) अणु
		event = list_entry(this, काष्ठा cpts_event, list);
		अगर (event_expired(event)) अणु
			list_del_init(&event->list);
			list_add(&event->list, &cpts->pool);
			++हटाओd;
		पूर्ण
	पूर्ण

	अगर (हटाओd)
		dev_dbg(cpts->dev, "cpts: event pool cleaned up %d\n", हटाओd);
	वापस हटाओd ? 0 : -1;
पूर्ण

अटल व्योम cpts_purge_txq(काष्ठा cpts *cpts)
अणु
	काष्ठा cpts_skb_cb_data *skb_cb;
	काष्ठा sk_buff *skb, *पंचांगp;
	पूर्णांक हटाओd = 0;

	skb_queue_walk_safe(&cpts->txq, skb, पंचांगp) अणु
		skb_cb = (काष्ठा cpts_skb_cb_data *)skb->cb;
		अगर (समय_after(jअगरfies, skb_cb->पंचांगo)) अणु
			__skb_unlink(skb, &cpts->txq);
			dev_consume_skb_any(skb);
			++हटाओd;
		पूर्ण
	पूर्ण

	अगर (हटाओd)
		dev_dbg(cpts->dev, "txq cleaned up %d\n", हटाओd);
पूर्ण

/*
 * Returns zero अगर matching event type was found.
 */
अटल पूर्णांक cpts_fअगरo_पढ़ो(काष्ठा cpts *cpts, पूर्णांक match)
अणु
	काष्ठा ptp_घड़ी_event pevent;
	bool need_schedule = false;
	काष्ठा cpts_event *event;
	अचिन्हित दीर्घ flags;
	पूर्णांक i, type = -1;
	u32 hi, lo;

	spin_lock_irqsave(&cpts->lock, flags);

	क्रम (i = 0; i < CPTS_FIFO_DEPTH; i++) अणु
		अगर (cpts_fअगरo_pop(cpts, &hi, &lo))
			अवरोध;

		अगर (list_empty(&cpts->pool) && cpts_purge_events(cpts)) अणु
			dev_warn(cpts->dev, "cpts: event pool empty\n");
			अवरोध;
		पूर्ण

		event = list_first_entry(&cpts->pool, काष्ठा cpts_event, list);
		event->high = hi;
		event->low = lo;
		event->बारtamp = समयcounter_cyc2समय(&cpts->tc, event->low);
		type = event_type(event);

		dev_dbg(cpts->dev, "CPTS_EV: %d high:%08X low:%08x\n",
			type, event->high, event->low);
		चयन (type) अणु
		हाल CPTS_EV_PUSH:
			WRITE_ONCE(cpts->cur_बारtamp, lo);
			समयcounter_पढ़ो(&cpts->tc);
			अगर (cpts->mult_new) अणु
				cpts->cc.mult = cpts->mult_new;
				cpts->mult_new = 0;
			पूर्ण
			अगर (!cpts->irq_poll)
				complete(&cpts->ts_push_complete);
			अवरोध;
		हाल CPTS_EV_TX:
		हाल CPTS_EV_RX:
			event->पंचांगo = jअगरfies +
				msecs_to_jअगरfies(CPTS_EVENT_RX_TX_TIMEOUT);

			list_del_init(&event->list);
			list_add_tail(&event->list, &cpts->events);
			need_schedule = true;
			अवरोध;
		हाल CPTS_EV_ROLL:
		हाल CPTS_EV_HALF:
			अवरोध;
		हाल CPTS_EV_HW:
			pevent.बारtamp = event->बारtamp;
			pevent.type = PTP_CLOCK_EXTTS;
			pevent.index = cpts_event_port(event) - 1;
			ptp_घड़ी_event(cpts->घड़ी, &pevent);
			अवरोध;
		शेष:
			dev_err(cpts->dev, "cpts: unknown event type\n");
			अवरोध;
		पूर्ण
		अगर (type == match)
			अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&cpts->lock, flags);

	अगर (!cpts->irq_poll && need_schedule)
		ptp_schedule_worker(cpts->घड़ी, 0);

	वापस type == match ? 0 : -1;
पूर्ण

व्योम cpts_misc_पूर्णांकerrupt(काष्ठा cpts *cpts)
अणु
	cpts_fअगरo_पढ़ो(cpts, -1);
पूर्ण
EXPORT_SYMBOL_GPL(cpts_misc_पूर्णांकerrupt);

अटल u64 cpts_systim_पढ़ो(स्थिर काष्ठा cyclecounter *cc)
अणु
	काष्ठा cpts *cpts = container_of(cc, काष्ठा cpts, cc);

	वापस READ_ONCE(cpts->cur_बारtamp);
पूर्ण

अटल व्योम cpts_update_cur_समय(काष्ठा cpts *cpts, पूर्णांक match,
				 काष्ठा ptp_प्रणाली_बारtamp *sts)
अणु
	अचिन्हित दीर्घ flags;

	reinit_completion(&cpts->ts_push_complete);

	/* use spin_lock_irqsave() here as it has to run very fast */
	spin_lock_irqsave(&cpts->lock, flags);
	ptp_पढ़ो_प्रणाली_prets(sts);
	cpts_ग_लिखो32(cpts, TS_PUSH, ts_push);
	cpts_पढ़ो32(cpts, ts_push);
	ptp_पढ़ो_प्रणाली_postts(sts);
	spin_unlock_irqrestore(&cpts->lock, flags);

	अगर (cpts->irq_poll && cpts_fअगरo_पढ़ो(cpts, match) && match != -1)
		dev_err(cpts->dev, "cpts: unable to obtain a time stamp\n");

	अगर (!cpts->irq_poll &&
	    !रुको_क्रम_completion_समयout(&cpts->ts_push_complete, HZ))
		dev_err(cpts->dev, "cpts: obtain a time stamp timeout\n");
पूर्ण

/* PTP घड़ी operations */

अटल पूर्णांक cpts_ptp_adjfreq(काष्ठा ptp_घड़ी_info *ptp, s32 ppb)
अणु
	काष्ठा cpts *cpts = container_of(ptp, काष्ठा cpts, info);
	पूर्णांक neg_adj = 0;
	u32 dअगरf, mult;
	u64 adj;

	अगर (ppb < 0) अणु
		neg_adj = 1;
		ppb = -ppb;
	पूर्ण
	mult = cpts->cc_mult;
	adj = mult;
	adj *= ppb;
	dअगरf = भाग_u64(adj, 1000000000ULL);

	mutex_lock(&cpts->ptp_clk_mutex);

	cpts->mult_new = neg_adj ? mult - dअगरf : mult + dअगरf;

	cpts_update_cur_समय(cpts, CPTS_EV_PUSH, शून्य);

	mutex_unlock(&cpts->ptp_clk_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक cpts_ptp_adjसमय(काष्ठा ptp_घड़ी_info *ptp, s64 delta)
अणु
	काष्ठा cpts *cpts = container_of(ptp, काष्ठा cpts, info);

	mutex_lock(&cpts->ptp_clk_mutex);
	समयcounter_adjसमय(&cpts->tc, delta);
	mutex_unlock(&cpts->ptp_clk_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक cpts_ptp_समय_लोex(काष्ठा ptp_घड़ी_info *ptp,
			      काष्ठा बारpec64 *ts,
			      काष्ठा ptp_प्रणाली_बारtamp *sts)
अणु
	काष्ठा cpts *cpts = container_of(ptp, काष्ठा cpts, info);
	u64 ns;

	mutex_lock(&cpts->ptp_clk_mutex);

	cpts_update_cur_समय(cpts, CPTS_EV_PUSH, sts);

	ns = समयcounter_पढ़ो(&cpts->tc);
	mutex_unlock(&cpts->ptp_clk_mutex);

	*ts = ns_to_बारpec64(ns);

	वापस 0;
पूर्ण

अटल पूर्णांक cpts_ptp_समय_रखो(काष्ठा ptp_घड़ी_info *ptp,
			    स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा cpts *cpts = container_of(ptp, काष्ठा cpts, info);
	u64 ns;

	ns = बारpec64_to_ns(ts);

	mutex_lock(&cpts->ptp_clk_mutex);
	समयcounter_init(&cpts->tc, &cpts->cc, ns);
	mutex_unlock(&cpts->ptp_clk_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक cpts_extts_enable(काष्ठा cpts *cpts, u32 index, पूर्णांक on)
अणु
	u32 v;

	अगर (((cpts->hw_ts_enable & BIT(index)) >> index) == on)
		वापस 0;

	mutex_lock(&cpts->ptp_clk_mutex);

	v = cpts_पढ़ो32(cpts, control);
	अगर (on) अणु
		v |= BIT(8 + index);
		cpts->hw_ts_enable |= BIT(index);
	पूर्ण अन्यथा अणु
		v &= ~BIT(8 + index);
		cpts->hw_ts_enable &= ~BIT(index);
	पूर्ण
	cpts_ग_लिखो32(cpts, v, control);

	mutex_unlock(&cpts->ptp_clk_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक cpts_ptp_enable(काष्ठा ptp_घड़ी_info *ptp,
			   काष्ठा ptp_घड़ी_request *rq, पूर्णांक on)
अणु
	काष्ठा cpts *cpts = container_of(ptp, काष्ठा cpts, info);

	चयन (rq->type) अणु
	हाल PTP_CLK_REQ_EXTTS:
		वापस cpts_extts_enable(cpts, rq->extts.index, on);
	शेष:
		अवरोध;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल bool cpts_match_tx_ts(काष्ठा cpts *cpts, काष्ठा cpts_event *event)
अणु
	काष्ठा sk_buff_head txq_list;
	काष्ठा sk_buff *skb, *पंचांगp;
	अचिन्हित दीर्घ flags;
	bool found = false;
	u32 mtype_seqid;

	mtype_seqid = event->high &
		      ((MESSAGE_TYPE_MASK << MESSAGE_TYPE_SHIFT) |
		       (SEQUENCE_ID_MASK << SEQUENCE_ID_SHIFT) |
		       (EVENT_TYPE_MASK << EVENT_TYPE_SHIFT));

	__skb_queue_head_init(&txq_list);

	spin_lock_irqsave(&cpts->txq.lock, flags);
	skb_queue_splice_init(&cpts->txq, &txq_list);
	spin_unlock_irqrestore(&cpts->txq.lock, flags);

	skb_queue_walk_safe(&txq_list, skb, पंचांगp) अणु
		काष्ठा skb_shared_hwtstamps ssh;
		काष्ठा cpts_skb_cb_data *skb_cb =
					(काष्ठा cpts_skb_cb_data *)skb->cb;

		अगर (mtype_seqid == skb_cb->skb_mtype_seqid) अणु
			स_रखो(&ssh, 0, माप(ssh));
			ssh.hwtstamp = ns_to_kसमय(event->बारtamp);
			skb_tstamp_tx(skb, &ssh);
			found = true;
			__skb_unlink(skb, &txq_list);
			dev_consume_skb_any(skb);
			dev_dbg(cpts->dev, "match tx timestamp mtype_seqid %08x\n",
				mtype_seqid);
			अवरोध;
		पूर्ण

		अगर (समय_after(jअगरfies, skb_cb->पंचांगo)) अणु
			/* समयout any expired skbs over 1s */
			dev_dbg(cpts->dev, "expiring tx timestamp from txq\n");
			__skb_unlink(skb, &txq_list);
			dev_consume_skb_any(skb);
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&cpts->txq.lock, flags);
	skb_queue_splice(&txq_list, &cpts->txq);
	spin_unlock_irqrestore(&cpts->txq.lock, flags);

	वापस found;
पूर्ण

अटल व्योम cpts_process_events(काष्ठा cpts *cpts)
अणु
	काष्ठा list_head *this, *next;
	काष्ठा cpts_event *event;
	LIST_HEAD(events_मुक्त);
	अचिन्हित दीर्घ flags;
	LIST_HEAD(events);

	spin_lock_irqsave(&cpts->lock, flags);
	list_splice_init(&cpts->events, &events);
	spin_unlock_irqrestore(&cpts->lock, flags);

	list_क्रम_each_safe(this, next, &events) अणु
		event = list_entry(this, काष्ठा cpts_event, list);
		अगर (cpts_match_tx_ts(cpts, event) ||
		    समय_after(jअगरfies, event->पंचांगo)) अणु
			list_del_init(&event->list);
			list_add(&event->list, &events_मुक्त);
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&cpts->lock, flags);
	list_splice_tail(&events, &cpts->events);
	list_splice_tail(&events_मुक्त, &cpts->pool);
	spin_unlock_irqrestore(&cpts->lock, flags);
पूर्ण

अटल दीर्घ cpts_overflow_check(काष्ठा ptp_घड़ी_info *ptp)
अणु
	काष्ठा cpts *cpts = container_of(ptp, काष्ठा cpts, info);
	अचिन्हित दीर्घ delay = cpts->ov_check_period;
	अचिन्हित दीर्घ flags;
	u64 ns;

	mutex_lock(&cpts->ptp_clk_mutex);

	cpts_update_cur_समय(cpts, -1, शून्य);
	ns = समयcounter_पढ़ो(&cpts->tc);

	cpts_process_events(cpts);

	spin_lock_irqsave(&cpts->txq.lock, flags);
	अगर (!skb_queue_empty(&cpts->txq)) अणु
		cpts_purge_txq(cpts);
		अगर (!skb_queue_empty(&cpts->txq))
			delay = CPTS_SKB_TX_WORK_TIMEOUT;
	पूर्ण
	spin_unlock_irqrestore(&cpts->txq.lock, flags);

	dev_dbg(cpts->dev, "cpts overflow check at %lld\n", ns);
	mutex_unlock(&cpts->ptp_clk_mutex);
	वापस (दीर्घ)delay;
पूर्ण

अटल स्थिर काष्ठा ptp_घड़ी_info cpts_info = अणु
	.owner		= THIS_MODULE,
	.name		= "CTPS timer",
	.max_adj	= 1000000,
	.n_ext_ts	= 0,
	.n_pins		= 0,
	.pps		= 0,
	.adjfreq	= cpts_ptp_adjfreq,
	.adjसमय	= cpts_ptp_adjसमय,
	.समय_लोx64	= cpts_ptp_समय_लोex,
	.समय_रखो64	= cpts_ptp_समय_रखो,
	.enable		= cpts_ptp_enable,
	.करो_aux_work	= cpts_overflow_check,
पूर्ण;

अटल पूर्णांक cpts_skb_get_mtype_seqid(काष्ठा sk_buff *skb, u32 *mtype_seqid)
अणु
	अचिन्हित पूर्णांक ptp_class = ptp_classअगरy_raw(skb);
	काष्ठा ptp_header *hdr;
	u8 msgtype;
	u16 seqid;

	अगर (ptp_class == PTP_CLASS_NONE)
		वापस 0;

	hdr = ptp_parse_header(skb, ptp_class);
	अगर (!hdr)
		वापस 0;

	msgtype = ptp_get_msgtype(hdr, ptp_class);
	seqid	= ntohs(hdr->sequence_id);

	*mtype_seqid  = (msgtype & MESSAGE_TYPE_MASK) << MESSAGE_TYPE_SHIFT;
	*mtype_seqid |= (seqid & SEQUENCE_ID_MASK) << SEQUENCE_ID_SHIFT;

	वापस 1;
पूर्ण

अटल u64 cpts_find_ts(काष्ठा cpts *cpts, काष्ठा sk_buff *skb,
			पूर्णांक ev_type, u32 skb_mtype_seqid)
अणु
	काष्ठा list_head *this, *next;
	काष्ठा cpts_event *event;
	अचिन्हित दीर्घ flags;
	u32 mtype_seqid;
	u64 ns = 0;

	cpts_fअगरo_पढ़ो(cpts, -1);
	spin_lock_irqsave(&cpts->lock, flags);
	list_क्रम_each_safe(this, next, &cpts->events) अणु
		event = list_entry(this, काष्ठा cpts_event, list);
		अगर (event_expired(event)) अणु
			list_del_init(&event->list);
			list_add(&event->list, &cpts->pool);
			जारी;
		पूर्ण

		mtype_seqid = event->high &
			      ((MESSAGE_TYPE_MASK << MESSAGE_TYPE_SHIFT) |
			       (SEQUENCE_ID_MASK << SEQUENCE_ID_SHIFT) |
			       (EVENT_TYPE_MASK << EVENT_TYPE_SHIFT));

		अगर (mtype_seqid == skb_mtype_seqid) अणु
			ns = event->बारtamp;
			list_del_init(&event->list);
			list_add(&event->list, &cpts->pool);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&cpts->lock, flags);

	वापस ns;
पूर्ण

व्योम cpts_rx_बारtamp(काष्ठा cpts *cpts, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpts_skb_cb_data *skb_cb = (काष्ठा cpts_skb_cb_data *)skb->cb;
	काष्ठा skb_shared_hwtstamps *ssh;
	पूर्णांक ret;
	u64 ns;

	/* cpts_rx_बारtamp() is called beक्रमe eth_type_trans(), so
	 * skb MAC Hdr properties are not configured yet. Hence need to
	 * reset skb MAC header here
	 */
	skb_reset_mac_header(skb);
	ret = cpts_skb_get_mtype_seqid(skb, &skb_cb->skb_mtype_seqid);
	अगर (!ret)
		वापस;

	skb_cb->skb_mtype_seqid |= (CPTS_EV_RX << EVENT_TYPE_SHIFT);

	dev_dbg(cpts->dev, "%s mtype seqid %08x\n",
		__func__, skb_cb->skb_mtype_seqid);

	ns = cpts_find_ts(cpts, skb, CPTS_EV_RX, skb_cb->skb_mtype_seqid);
	अगर (!ns)
		वापस;
	ssh = skb_hwtstamps(skb);
	स_रखो(ssh, 0, माप(*ssh));
	ssh->hwtstamp = ns_to_kसमय(ns);
पूर्ण
EXPORT_SYMBOL_GPL(cpts_rx_बारtamp);

व्योम cpts_tx_बारtamp(काष्ठा cpts *cpts, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpts_skb_cb_data *skb_cb = (काष्ठा cpts_skb_cb_data *)skb->cb;
	पूर्णांक ret;

	अगर (!(skb_shinfo(skb)->tx_flags & SKBTX_IN_PROGRESS))
		वापस;

	ret = cpts_skb_get_mtype_seqid(skb, &skb_cb->skb_mtype_seqid);
	अगर (!ret)
		वापस;

	skb_cb->skb_mtype_seqid |= (CPTS_EV_TX << EVENT_TYPE_SHIFT);

	dev_dbg(cpts->dev, "%s mtype seqid %08x\n",
		__func__, skb_cb->skb_mtype_seqid);

	/* Always defer TX TS processing to PTP worker */
	skb_get(skb);
	/* get the बारtamp क्रम समयouts */
	skb_cb->पंचांगo = jअगरfies + msecs_to_jअगरfies(CPTS_SKB_RX_TX_TMO);
	skb_queue_tail(&cpts->txq, skb);
	ptp_schedule_worker(cpts->घड़ी, 0);
पूर्ण
EXPORT_SYMBOL_GPL(cpts_tx_बारtamp);

पूर्णांक cpts_रेजिस्टर(काष्ठा cpts *cpts)
अणु
	पूर्णांक err, i;

	skb_queue_head_init(&cpts->txq);
	INIT_LIST_HEAD(&cpts->events);
	INIT_LIST_HEAD(&cpts->pool);
	क्रम (i = 0; i < CPTS_MAX_EVENTS; i++)
		list_add(&cpts->pool_data[i].list, &cpts->pool);

	clk_enable(cpts->refclk);

	cpts_ग_लिखो32(cpts, CPTS_EN, control);
	cpts_ग_लिखो32(cpts, TS_PEND_EN, पूर्णांक_enable);

	समयcounter_init(&cpts->tc, &cpts->cc, kसमय_get_real_ns());

	cpts->घड़ी = ptp_घड़ी_रेजिस्टर(&cpts->info, cpts->dev);
	अगर (IS_ERR(cpts->घड़ी)) अणु
		err = PTR_ERR(cpts->घड़ी);
		cpts->घड़ी = शून्य;
		जाओ err_ptp;
	पूर्ण
	cpts->phc_index = ptp_घड़ी_index(cpts->घड़ी);

	ptp_schedule_worker(cpts->घड़ी, cpts->ov_check_period);
	वापस 0;

err_ptp:
	clk_disable(cpts->refclk);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(cpts_रेजिस्टर);

व्योम cpts_unरेजिस्टर(काष्ठा cpts *cpts)
अणु
	अगर (WARN_ON(!cpts->घड़ी))
		वापस;

	ptp_घड़ी_unरेजिस्टर(cpts->घड़ी);
	cpts->घड़ी = शून्य;
	cpts->phc_index = -1;

	cpts_ग_लिखो32(cpts, 0, पूर्णांक_enable);
	cpts_ग_लिखो32(cpts, 0, control);

	/* Drop all packet */
	skb_queue_purge(&cpts->txq);

	clk_disable(cpts->refclk);
पूर्ण
EXPORT_SYMBOL_GPL(cpts_unरेजिस्टर);

अटल व्योम cpts_calc_mult_shअगरt(काष्ठा cpts *cpts)
अणु
	u64 frac, maxsec, ns;
	u32 freq;

	freq = clk_get_rate(cpts->refclk);

	/* Calc the maximum number of seconds which we can run beक्रमe
	 * wrapping around.
	 */
	maxsec = cpts->cc.mask;
	करो_भाग(maxsec, freq);
	/* limit conversation rate to 10 sec as higher values will produce
	 * too small mult factors and so reduce the conversion accuracy
	 */
	अगर (maxsec > 10)
		maxsec = 10;

	/* Calc overflow check period (maxsec / 2) */
	cpts->ov_check_period = (HZ * maxsec) / 2;
	dev_info(cpts->dev, "cpts: overflow check period %lu (jiffies)\n",
		 cpts->ov_check_period);

	अगर (cpts->cc.mult || cpts->cc.shअगरt)
		वापस;

	घड़ीs_calc_mult_shअगरt(&cpts->cc.mult, &cpts->cc.shअगरt,
			       freq, NSEC_PER_SEC, maxsec);

	frac = 0;
	ns = cyclecounter_cyc2ns(&cpts->cc, freq, cpts->cc.mask, &frac);

	dev_info(cpts->dev,
		 "CPTS: ref_clk_freq:%u calc_mult:%u calc_shift:%u error:%lld nsec/sec\n",
		 freq, cpts->cc.mult, cpts->cc.shअगरt, (ns - NSEC_PER_SEC));
पूर्ण

अटल पूर्णांक cpts_of_mux_clk_setup(काष्ठा cpts *cpts, काष्ठा device_node *node)
अणु
	काष्ठा device_node *refclk_np;
	स्थिर अक्षर **parent_names;
	अचिन्हित पूर्णांक num_parents;
	काष्ठा clk_hw *clk_hw;
	पूर्णांक ret = -EINVAL;
	u32 *mux_table;

	refclk_np = of_get_child_by_name(node, "cpts-refclk-mux");
	अगर (!refclk_np)
		/* refclk selection supported not क्रम all SoCs */
		वापस 0;

	num_parents = of_clk_get_parent_count(refclk_np);
	अगर (num_parents < 1) अणु
		dev_err(cpts->dev, "mux-clock %s must have parents\n",
			refclk_np->name);
		जाओ mux_fail;
	पूर्ण

	parent_names = devm_kzalloc(cpts->dev, (माप(अक्षर *) * num_parents),
				    GFP_KERNEL);

	mux_table = devm_kzalloc(cpts->dev, माप(*mux_table) * num_parents,
				 GFP_KERNEL);
	अगर (!mux_table || !parent_names) अणु
		ret = -ENOMEM;
		जाओ mux_fail;
	पूर्ण

	of_clk_parent_fill(refclk_np, parent_names, num_parents);

	ret = of_property_पढ़ो_variable_u32_array(refclk_np, "ti,mux-tbl",
						  mux_table,
						  num_parents, num_parents);
	अगर (ret < 0)
		जाओ mux_fail;

	clk_hw = clk_hw_रेजिस्टर_mux_table(cpts->dev, refclk_np->name,
					   parent_names, num_parents,
					   0,
					   &cpts->reg->rftclk_sel, 0, 0x1F,
					   0, mux_table, शून्य);
	अगर (IS_ERR(clk_hw)) अणु
		ret = PTR_ERR(clk_hw);
		जाओ mux_fail;
	पूर्ण

	ret = devm_add_action_or_reset(cpts->dev,
				       (व्योम(*)(व्योम *))clk_hw_unरेजिस्टर_mux,
				       clk_hw);
	अगर (ret) अणु
		dev_err(cpts->dev, "add clkmux unreg action %d", ret);
		जाओ mux_fail;
	पूर्ण

	ret = of_clk_add_hw_provider(refclk_np, of_clk_hw_simple_get, clk_hw);
	अगर (ret)
		जाओ mux_fail;

	ret = devm_add_action_or_reset(cpts->dev,
				       (व्योम(*)(व्योम *))of_clk_del_provider,
				       refclk_np);
	अगर (ret) अणु
		dev_err(cpts->dev, "add clkmux provider unreg action %d", ret);
		जाओ mux_fail;
	पूर्ण

	वापस ret;

mux_fail:
	of_node_put(refclk_np);
	वापस ret;
पूर्ण

अटल पूर्णांक cpts_of_parse(काष्ठा cpts *cpts, काष्ठा device_node *node)
अणु
	पूर्णांक ret = -EINVAL;
	u32 prop;

	अगर (!of_property_पढ़ो_u32(node, "cpts_clock_mult", &prop))
		cpts->cc.mult = prop;

	अगर (!of_property_पढ़ो_u32(node, "cpts_clock_shift", &prop))
		cpts->cc.shअगरt = prop;

	अगर ((cpts->cc.mult && !cpts->cc.shअगरt) ||
	    (!cpts->cc.mult && cpts->cc.shअगरt))
		जाओ of_error;

	वापस cpts_of_mux_clk_setup(cpts, node);

of_error:
	dev_err(cpts->dev, "CPTS: Missing property in the DT.\n");
	वापस ret;
पूर्ण

काष्ठा cpts *cpts_create(काष्ठा device *dev, व्योम __iomem *regs,
			 काष्ठा device_node *node, u32 n_ext_ts)
अणु
	काष्ठा cpts *cpts;
	पूर्णांक ret;

	cpts = devm_kzalloc(dev, माप(*cpts), GFP_KERNEL);
	अगर (!cpts)
		वापस ERR_PTR(-ENOMEM);

	cpts->dev = dev;
	cpts->reg = (काष्ठा cpsw_cpts __iomem *)regs;
	cpts->irq_poll = true;
	spin_lock_init(&cpts->lock);
	mutex_init(&cpts->ptp_clk_mutex);
	init_completion(&cpts->ts_push_complete);

	ret = cpts_of_parse(cpts, node);
	अगर (ret)
		वापस ERR_PTR(ret);

	cpts->refclk = devm_get_clk_from_child(dev, node, "cpts");
	अगर (IS_ERR(cpts->refclk))
		/* try get clk from dev node क्रम compatibility */
		cpts->refclk = devm_clk_get(dev, "cpts");

	अगर (IS_ERR(cpts->refclk)) अणु
		dev_err(dev, "Failed to get cpts refclk %ld\n",
			PTR_ERR(cpts->refclk));
		वापस ERR_CAST(cpts->refclk);
	पूर्ण

	ret = clk_prepare(cpts->refclk);
	अगर (ret)
		वापस ERR_PTR(ret);

	cpts->cc.पढ़ो = cpts_systim_पढ़ो;
	cpts->cc.mask = CLOCKSOURCE_MASK(32);
	cpts->info = cpts_info;
	cpts->phc_index = -1;

	अगर (n_ext_ts)
		cpts->info.n_ext_ts = n_ext_ts;

	cpts_calc_mult_shअगरt(cpts);
	/* save cc.mult original value as it can be modअगरied
	 * by cpts_ptp_adjfreq().
	 */
	cpts->cc_mult = cpts->cc.mult;

	वापस cpts;
पूर्ण
EXPORT_SYMBOL_GPL(cpts_create);

व्योम cpts_release(काष्ठा cpts *cpts)
अणु
	अगर (!cpts)
		वापस;

	अगर (WARN_ON(!cpts->refclk))
		वापस;

	clk_unprepare(cpts->refclk);
पूर्ण
EXPORT_SYMBOL_GPL(cpts_release);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("TI CPTS driver");
MODULE_AUTHOR("Richard Cochran <richardcochran@gmail.com>");
