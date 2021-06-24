<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2018 Felix Fietkau <nbd@nbd.name>
 */
#समावेश "mt76.h"

अटल अचिन्हित दीर्घ mt76_aggr_tid_to_समयo(u8 tidno)
अणु
	/* Currently voice traffic (AC_VO) always runs without aggregation,
	 * no special handling is needed. AC_BE/AC_BK use tids 0-3. Just check
	 * क्रम non AC_BK/AC_BE and set smaller समयout क्रम it. */
	वापस HZ / (tidno >= 4 ? 25 : 10);
पूर्ण

अटल व्योम
mt76_aggr_release(काष्ठा mt76_rx_tid *tid, काष्ठा sk_buff_head *frames, पूर्णांक idx)
अणु
	काष्ठा sk_buff *skb;

	tid->head = ieee80211_sn_inc(tid->head);

	skb = tid->reorder_buf[idx];
	अगर (!skb)
		वापस;

	tid->reorder_buf[idx] = शून्य;
	tid->nframes--;
	__skb_queue_tail(frames, skb);
पूर्ण

अटल व्योम
mt76_rx_aggr_release_frames(काष्ठा mt76_rx_tid *tid,
			    काष्ठा sk_buff_head *frames,
			    u16 head)
अणु
	पूर्णांक idx;

	जबतक (ieee80211_sn_less(tid->head, head)) अणु
		idx = tid->head % tid->size;
		mt76_aggr_release(tid, frames, idx);
	पूर्ण
पूर्ण

अटल व्योम
mt76_rx_aggr_release_head(काष्ठा mt76_rx_tid *tid, काष्ठा sk_buff_head *frames)
अणु
	पूर्णांक idx = tid->head % tid->size;

	जबतक (tid->reorder_buf[idx]) अणु
		mt76_aggr_release(tid, frames, idx);
		idx = tid->head % tid->size;
	पूर्ण
पूर्ण

अटल व्योम
mt76_rx_aggr_check_release(काष्ठा mt76_rx_tid *tid, काष्ठा sk_buff_head *frames)
अणु
	काष्ठा mt76_rx_status *status;
	काष्ठा sk_buff *skb;
	पूर्णांक start, idx, nframes;

	अगर (!tid->nframes)
		वापस;

	mt76_rx_aggr_release_head(tid, frames);

	start = tid->head % tid->size;
	nframes = tid->nframes;

	क्रम (idx = (tid->head + 1) % tid->size;
	     idx != start && nframes;
	     idx = (idx + 1) % tid->size) अणु
		skb = tid->reorder_buf[idx];
		अगर (!skb)
			जारी;

		nframes--;
		status = (काष्ठा mt76_rx_status *)skb->cb;
		अगर (!समय_after32(jअगरfies,
				  status->reorder_समय +
				  mt76_aggr_tid_to_समयo(tid->num)))
			जारी;

		mt76_rx_aggr_release_frames(tid, frames, status->seqno);
	पूर्ण

	mt76_rx_aggr_release_head(tid, frames);
पूर्ण

अटल व्योम
mt76_rx_aggr_reorder_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mt76_rx_tid *tid = container_of(work, काष्ठा mt76_rx_tid,
					       reorder_work.work);
	काष्ठा mt76_dev *dev = tid->dev;
	काष्ठा sk_buff_head frames;
	पूर्णांक nframes;

	__skb_queue_head_init(&frames);

	local_bh_disable();
	rcu_पढ़ो_lock();

	spin_lock(&tid->lock);
	mt76_rx_aggr_check_release(tid, &frames);
	nframes = tid->nframes;
	spin_unlock(&tid->lock);

	अगर (nframes)
		ieee80211_queue_delayed_work(tid->dev->hw, &tid->reorder_work,
					     mt76_aggr_tid_to_समयo(tid->num));
	mt76_rx_complete(dev, &frames, शून्य);

	rcu_पढ़ो_unlock();
	local_bh_enable();
पूर्ण

अटल व्योम
mt76_rx_aggr_check_ctl(काष्ठा sk_buff *skb, काष्ठा sk_buff_head *frames)
अणु
	काष्ठा mt76_rx_status *status = (काष्ठा mt76_rx_status *)skb->cb;
	काष्ठा ieee80211_bar *bar = mt76_skb_get_hdr(skb);
	काष्ठा mt76_wcid *wcid = status->wcid;
	काष्ठा mt76_rx_tid *tid;
	u8 tidno = status->qos_ctl & IEEE80211_QOS_CTL_TID_MASK;
	u16 seqno;

	अगर (!ieee80211_is_ctl(bar->frame_control))
		वापस;

	अगर (!ieee80211_is_back_req(bar->frame_control))
		वापस;

	status->qos_ctl = tidno = le16_to_cpu(bar->control) >> 12;
	seqno = IEEE80211_SEQ_TO_SN(le16_to_cpu(bar->start_seq_num));
	tid = rcu_dereference(wcid->aggr[tidno]);
	अगर (!tid)
		वापस;

	spin_lock_bh(&tid->lock);
	अगर (!tid->stopped) अणु
		mt76_rx_aggr_release_frames(tid, frames, seqno);
		mt76_rx_aggr_release_head(tid, frames);
	पूर्ण
	spin_unlock_bh(&tid->lock);
पूर्ण

व्योम mt76_rx_aggr_reorder(काष्ठा sk_buff *skb, काष्ठा sk_buff_head *frames)
अणु
	काष्ठा mt76_rx_status *status = (काष्ठा mt76_rx_status *)skb->cb;
	काष्ठा mt76_wcid *wcid = status->wcid;
	काष्ठा ieee80211_sta *sta;
	काष्ठा mt76_rx_tid *tid;
	bool sn_less;
	u16 seqno, head, size, idx;
	u8 tidno = status->qos_ctl & IEEE80211_QOS_CTL_TID_MASK;
	u8 ackp;

	__skb_queue_tail(frames, skb);

	sta = wcid_to_sta(wcid);
	अगर (!sta)
		वापस;

	अगर (!status->aggr && !(status->flag & RX_FLAG_8023)) अणु
		mt76_rx_aggr_check_ctl(skb, frames);
		वापस;
	पूर्ण

	/* not part of a BA session */
	ackp = status->qos_ctl & IEEE80211_QOS_CTL_ACK_POLICY_MASK;
	अगर (ackp != IEEE80211_QOS_CTL_ACK_POLICY_BLOCKACK &&
	    ackp != IEEE80211_QOS_CTL_ACK_POLICY_NORMAL)
		वापस;

	tid = rcu_dereference(wcid->aggr[tidno]);
	अगर (!tid)
		वापस;

	status->flag |= RX_FLAG_DUP_VALIDATED;
	spin_lock_bh(&tid->lock);

	अगर (tid->stopped)
		जाओ out;

	head = tid->head;
	seqno = status->seqno;
	size = tid->size;
	sn_less = ieee80211_sn_less(seqno, head);

	अगर (!tid->started) अणु
		अगर (sn_less)
			जाओ out;

		tid->started = true;
	पूर्ण

	अगर (sn_less) अणु
		__skb_unlink(skb, frames);
		dev_kमुक्त_skb(skb);
		जाओ out;
	पूर्ण

	अगर (seqno == head) अणु
		tid->head = ieee80211_sn_inc(head);
		अगर (tid->nframes)
			mt76_rx_aggr_release_head(tid, frames);
		जाओ out;
	पूर्ण

	__skb_unlink(skb, frames);

	/*
	 * Frame sequence number exceeds buffering winकरोw, मुक्त up some space
	 * by releasing previous frames
	 */
	अगर (!ieee80211_sn_less(seqno, head + size)) अणु
		head = ieee80211_sn_inc(ieee80211_sn_sub(seqno, size));
		mt76_rx_aggr_release_frames(tid, frames, head);
	पूर्ण

	idx = seqno % size;

	/* Discard अगर the current slot is alपढ़ोy in use */
	अगर (tid->reorder_buf[idx]) अणु
		dev_kमुक्त_skb(skb);
		जाओ out;
	पूर्ण

	status->reorder_समय = jअगरfies;
	tid->reorder_buf[idx] = skb;
	tid->nframes++;
	mt76_rx_aggr_release_head(tid, frames);

	ieee80211_queue_delayed_work(tid->dev->hw, &tid->reorder_work,
				     mt76_aggr_tid_to_समयo(tid->num));

out:
	spin_unlock_bh(&tid->lock);
पूर्ण

पूर्णांक mt76_rx_aggr_start(काष्ठा mt76_dev *dev, काष्ठा mt76_wcid *wcid, u8 tidno,
		       u16 ssn, u16 size)
अणु
	काष्ठा mt76_rx_tid *tid;

	mt76_rx_aggr_stop(dev, wcid, tidno);

	tid = kzalloc(काष्ठा_size(tid, reorder_buf, size), GFP_KERNEL);
	अगर (!tid)
		वापस -ENOMEM;

	tid->dev = dev;
	tid->head = ssn;
	tid->size = size;
	tid->num = tidno;
	INIT_DELAYED_WORK(&tid->reorder_work, mt76_rx_aggr_reorder_work);
	spin_lock_init(&tid->lock);

	rcu_assign_poपूर्णांकer(wcid->aggr[tidno], tid);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_rx_aggr_start);

अटल व्योम mt76_rx_aggr_shutकरोwn(काष्ठा mt76_dev *dev, काष्ठा mt76_rx_tid *tid)
अणु
	u16 size = tid->size;
	पूर्णांक i;

	spin_lock_bh(&tid->lock);

	tid->stopped = true;
	क्रम (i = 0; tid->nframes && i < size; i++) अणु
		काष्ठा sk_buff *skb = tid->reorder_buf[i];

		अगर (!skb)
			जारी;

		tid->reorder_buf[i] = शून्य;
		tid->nframes--;
		dev_kमुक्त_skb(skb);
	पूर्ण

	spin_unlock_bh(&tid->lock);

	cancel_delayed_work_sync(&tid->reorder_work);
पूर्ण

व्योम mt76_rx_aggr_stop(काष्ठा mt76_dev *dev, काष्ठा mt76_wcid *wcid, u8 tidno)
अणु
	काष्ठा mt76_rx_tid *tid = शून्य;

	tid = rcu_replace_poपूर्णांकer(wcid->aggr[tidno], tid,
				  lockdep_is_held(&dev->mutex));
	अगर (tid) अणु
		mt76_rx_aggr_shutकरोwn(dev, tid);
		kमुक्त_rcu(tid, rcu_head);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mt76_rx_aggr_stop);
