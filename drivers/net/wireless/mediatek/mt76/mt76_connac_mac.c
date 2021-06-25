<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2020 MediaTek Inc. */

#समावेश "mt76_connac.h"

पूर्णांक mt76_connac_pm_wake(काष्ठा mt76_phy *phy, काष्ठा mt76_connac_pm *pm)
अणु
	काष्ठा mt76_dev *dev = phy->dev;

	अगर (!pm->enable)
		वापस 0;

	अगर (!mt76_is_mmio(dev))
		वापस 0;

	cancel_delayed_work_sync(&pm->ps_work);
	अगर (!test_bit(MT76_STATE_PM, &phy->state))
		वापस 0;

	queue_work(dev->wq, &pm->wake_work);
	अगर (!रुको_event_समयout(pm->रुको,
				!test_bit(MT76_STATE_PM, &phy->state),
				3 * HZ)) अणु
		ieee80211_wake_queues(phy->hw);
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_pm_wake);

व्योम mt76_connac_घातer_save_sched(काष्ठा mt76_phy *phy,
				  काष्ठा mt76_connac_pm *pm)
अणु
	काष्ठा mt76_dev *dev = phy->dev;

	अगर (!mt76_is_mmio(dev))
		वापस;

	अगर (!pm->enable)
		वापस;

	pm->last_activity = jअगरfies;

	अगर (!test_bit(MT76_STATE_PM, &phy->state)) अणु
		cancel_delayed_work(&phy->mac_work);
		queue_delayed_work(dev->wq, &pm->ps_work, pm->idle_समयout);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_घातer_save_sched);

व्योम mt76_connac_मुक्त_pending_tx_skbs(काष्ठा mt76_connac_pm *pm,
				      काष्ठा mt76_wcid *wcid)
अणु
	पूर्णांक i;

	spin_lock_bh(&pm->txq_lock);
	क्रम (i = 0; i < IEEE80211_NUM_ACS; i++) अणु
		अगर (wcid && pm->tx_q[i].wcid != wcid)
			जारी;

		dev_kमुक्त_skb(pm->tx_q[i].skb);
		pm->tx_q[i].skb = शून्य;
	पूर्ण
	spin_unlock_bh(&pm->txq_lock);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_मुक्त_pending_tx_skbs);

व्योम mt76_connac_pm_queue_skb(काष्ठा ieee80211_hw *hw,
			      काष्ठा mt76_connac_pm *pm,
			      काष्ठा mt76_wcid *wcid,
			      काष्ठा sk_buff *skb)
अणु
	पूर्णांक qid = skb_get_queue_mapping(skb);
	काष्ठा mt76_phy *phy = hw->priv;

	spin_lock_bh(&pm->txq_lock);
	अगर (!pm->tx_q[qid].skb) अणु
		ieee80211_stop_queues(hw);
		pm->tx_q[qid].wcid = wcid;
		pm->tx_q[qid].skb = skb;
		queue_work(phy->dev->wq, &pm->wake_work);
	पूर्ण अन्यथा अणु
		dev_kमुक्त_skb(skb);
	पूर्ण
	spin_unlock_bh(&pm->txq_lock);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_pm_queue_skb);

व्योम mt76_connac_pm_dequeue_skbs(काष्ठा mt76_phy *phy,
				 काष्ठा mt76_connac_pm *pm)
अणु
	पूर्णांक i;

	spin_lock_bh(&pm->txq_lock);
	क्रम (i = 0; i < IEEE80211_NUM_ACS; i++) अणु
		काष्ठा mt76_wcid *wcid = pm->tx_q[i].wcid;
		काष्ठा ieee80211_sta *sta = शून्य;

		अगर (!pm->tx_q[i].skb)
			जारी;

		अगर (wcid && wcid->sta)
			sta = container_of((व्योम *)wcid, काष्ठा ieee80211_sta,
					   drv_priv);

		mt76_tx(phy, sta, wcid, pm->tx_q[i].skb);
		pm->tx_q[i].skb = शून्य;
	पूर्ण
	spin_unlock_bh(&pm->txq_lock);

	mt76_worker_schedule(&phy->dev->tx_worker);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_connac_pm_dequeue_skbs);
