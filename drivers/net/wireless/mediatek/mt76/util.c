<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2016 Felix Fietkau <nbd@nbd.name>
 */

#समावेश <linux/module.h>
#समावेश "mt76.h"

bool __mt76_poll(काष्ठा mt76_dev *dev, u32 offset, u32 mask, u32 val,
		 पूर्णांक समयout)
अणु
	u32 cur;

	समयout /= 10;
	करो अणु
		cur = __mt76_rr(dev, offset) & mask;
		अगर (cur == val)
			वापस true;

		udelay(10);
	पूर्ण जबतक (समयout-- > 0);

	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(__mt76_poll);

bool __mt76_poll_msec(काष्ठा mt76_dev *dev, u32 offset, u32 mask, u32 val,
		      पूर्णांक समयout)
अणु
	u32 cur;

	समयout /= 10;
	करो अणु
		cur = __mt76_rr(dev, offset) & mask;
		अगर (cur == val)
			वापस true;

		usleep_range(10000, 20000);
	पूर्ण जबतक (समयout-- > 0);

	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(__mt76_poll_msec);

पूर्णांक mt76_wcid_alloc(u32 *mask, पूर्णांक size)
अणु
	पूर्णांक i, idx = 0, cur;

	क्रम (i = 0; i < DIV_ROUND_UP(size, 32); i++) अणु
		idx = ffs(~mask[i]);
		अगर (!idx)
			जारी;

		idx--;
		cur = i * 32 + idx;
		अगर (cur >= size)
			अवरोध;

		mask[i] |= BIT(idx);
		वापस cur;
	पूर्ण

	वापस -1;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_wcid_alloc);

पूर्णांक mt76_get_min_avg_rssi(काष्ठा mt76_dev *dev, bool ext_phy)
अणु
	काष्ठा mt76_wcid *wcid;
	पूर्णांक i, j, min_rssi = 0;
	s8 cur_rssi;

	local_bh_disable();
	rcu_पढ़ो_lock();

	क्रम (i = 0; i < ARRAY_SIZE(dev->wcid_mask); i++) अणु
		u32 mask = dev->wcid_mask[i];
		u32 phy_mask = dev->wcid_phy_mask[i];

		अगर (!mask)
			जारी;

		क्रम (j = i * 32; mask; j++, mask >>= 1, phy_mask >>= 1) अणु
			अगर (!(mask & 1))
				जारी;

			अगर (!!(phy_mask & 1) != ext_phy)
				जारी;

			wcid = rcu_dereference(dev->wcid[j]);
			अगर (!wcid)
				जारी;

			spin_lock(&dev->rx_lock);
			अगर (wcid->inactive_count++ < 5)
				cur_rssi = -ewma_संकेत_पढ़ो(&wcid->rssi);
			अन्यथा
				cur_rssi = 0;
			spin_unlock(&dev->rx_lock);

			अगर (cur_rssi < min_rssi)
				min_rssi = cur_rssi;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();
	local_bh_enable();

	वापस min_rssi;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_get_min_avg_rssi);

पूर्णांक __mt76_worker_fn(व्योम *ptr)
अणु
	काष्ठा mt76_worker *w = ptr;

	जबतक (!kthपढ़ो_should_stop()) अणु
		set_current_state(TASK_INTERRUPTIBLE);

		अगर (kthपढ़ो_should_park()) अणु
			kthपढ़ो_parkme();
			जारी;
		पूर्ण

		अगर (!test_and_clear_bit(MT76_WORKER_SCHEDULED, &w->state)) अणु
			schedule();
			जारी;
		पूर्ण

		set_bit(MT76_WORKER_RUNNING, &w->state);
		set_current_state(TASK_RUNNING);
		w->fn(w);
		cond_resched();
		clear_bit(MT76_WORKER_RUNNING, &w->state);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__mt76_worker_fn);

MODULE_LICENSE("Dual BSD/GPL");
