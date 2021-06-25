<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2016 Felix Fietkau <nbd@nbd.name>
 * Copyright (C) 2004 - 2009 Ivo van Doorn <IvDoorn@gmail.com>
 */

#अगर_अघोषित __MT76_UTIL_H
#घोषणा __MT76_UTIL_H

#समावेश <linux/skbuff.h>
#समावेश <linux/bitops.h>
#समावेश <linux/bitfield.h>
#समावेश <net/mac80211.h>

काष्ठा mt76_worker
अणु
	काष्ठा task_काष्ठा *task;
	व्योम (*fn)(काष्ठा mt76_worker *);
	अचिन्हित दीर्घ state;
पूर्ण;

क्रमागत अणु
	MT76_WORKER_SCHEDULED,
	MT76_WORKER_RUNNING,
पूर्ण;

#घोषणा MT76_INCR(_var, _size) \
	(_var = (((_var) + 1) % (_size)))

पूर्णांक mt76_wcid_alloc(u32 *mask, पूर्णांक size);

अटल अंतरभूत bool
mt76_wcid_mask_test(u32 *mask, पूर्णांक idx)
अणु
	वापस mask[idx / 32] & BIT(idx % 32);
पूर्ण

अटल अंतरभूत व्योम
mt76_wcid_mask_set(u32 *mask, पूर्णांक idx)
अणु
	mask[idx / 32] |= BIT(idx % 32);
पूर्ण

अटल अंतरभूत व्योम
mt76_wcid_mask_clear(u32 *mask, पूर्णांक idx)
अणु
	mask[idx / 32] &= ~BIT(idx % 32);
पूर्ण

अटल अंतरभूत व्योम
mt76_skb_set_moredata(काष्ठा sk_buff *skb, bool enable)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;

	अगर (enable)
		hdr->frame_control |= cpu_to_le16(IEEE80211_FCTL_MOREDATA);
	अन्यथा
		hdr->frame_control &= ~cpu_to_le16(IEEE80211_FCTL_MOREDATA);
पूर्ण

पूर्णांक __mt76_worker_fn(व्योम *ptr);

अटल अंतरभूत पूर्णांक
mt76_worker_setup(काष्ठा ieee80211_hw *hw, काष्ठा mt76_worker *w,
		  व्योम (*fn)(काष्ठा mt76_worker *),
		  स्थिर अक्षर *name)
अणु
	स्थिर अक्षर *dev_name = wiphy_name(hw->wiphy);
	पूर्णांक ret;

	अगर (fn)
		w->fn = fn;
	w->task = kthपढ़ो_create(__mt76_worker_fn, w, "mt76-%s %s",
				 name, dev_name);

	ret = PTR_ERR_OR_ZERO(w->task);
	अगर (ret) अणु
		w->task = शून्य;
		वापस ret;
	पूर्ण

	wake_up_process(w->task);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mt76_worker_schedule(काष्ठा mt76_worker *w)
अणु
	अगर (!w->task)
		वापस;

	अगर (!test_and_set_bit(MT76_WORKER_SCHEDULED, &w->state) &&
	    !test_bit(MT76_WORKER_RUNNING, &w->state))
		wake_up_process(w->task);
पूर्ण

अटल अंतरभूत व्योम mt76_worker_disable(काष्ठा mt76_worker *w)
अणु
	अगर (!w->task)
		वापस;

	kthपढ़ो_park(w->task);
	WRITE_ONCE(w->state, 0);
पूर्ण

अटल अंतरभूत व्योम mt76_worker_enable(काष्ठा mt76_worker *w)
अणु
	अगर (!w->task)
		वापस;

	kthपढ़ो_unpark(w->task);
	mt76_worker_schedule(w);
पूर्ण

अटल अंतरभूत व्योम mt76_worker_tearकरोwn(काष्ठा mt76_worker *w)
अणु
	अगर (!w->task)
		वापस;

	kthपढ़ो_stop(w->task);
	w->task = शून्य;
पूर्ण

#पूर्ण_अगर
