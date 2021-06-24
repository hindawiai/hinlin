<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Authors:
 * Alexander Aring <aar@pengutronix.de>
 *
 * Based on: net/mac80211/util.c
 */

#समावेश "ieee802154_i.h"
#समावेश "driver-ops.h"

/* privid क्रम wpan_phys to determine whether they beदीर्घ to us or not */
स्थिर व्योम *स्थिर mac802154_wpan_phy_privid = &mac802154_wpan_phy_privid;

व्योम ieee802154_wake_queue(काष्ठा ieee802154_hw *hw)
अणु
	काष्ठा ieee802154_local *local = hw_to_local(hw);
	काष्ठा ieee802154_sub_अगर_data *sdata;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(sdata, &local->पूर्णांकerfaces, list) अणु
		अगर (!sdata->dev)
			जारी;

		netअगर_wake_queue(sdata->dev);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL(ieee802154_wake_queue);

व्योम ieee802154_stop_queue(काष्ठा ieee802154_hw *hw)
अणु
	काष्ठा ieee802154_local *local = hw_to_local(hw);
	काष्ठा ieee802154_sub_अगर_data *sdata;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(sdata, &local->पूर्णांकerfaces, list) अणु
		अगर (!sdata->dev)
			जारी;

		netअगर_stop_queue(sdata->dev);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL(ieee802154_stop_queue);

क्रमागत hrसमयr_restart ieee802154_xmit_अगरs_समयr(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा ieee802154_local *local =
		container_of(समयr, काष्ठा ieee802154_local, अगरs_समयr);

	ieee802154_wake_queue(&local->hw);

	वापस HRTIMER_NORESTART;
पूर्ण

व्योम ieee802154_xmit_complete(काष्ठा ieee802154_hw *hw, काष्ठा sk_buff *skb,
			      bool अगरs_handling)
अणु
	अगर (अगरs_handling) अणु
		काष्ठा ieee802154_local *local = hw_to_local(hw);
		u8 max_sअगरs_size;

		/* If transceiver sets CRC on his own we need to use lअगरs
		 * threshold len above 16 otherwise 18, because it's not
		 * part of skb->len.
		 */
		अगर (hw->flags & IEEE802154_HW_TX_OMIT_CKSUM)
			max_sअगरs_size = IEEE802154_MAX_SIFS_FRAME_SIZE -
					IEEE802154_FCS_LEN;
		अन्यथा
			max_sअगरs_size = IEEE802154_MAX_SIFS_FRAME_SIZE;

		अगर (skb->len > max_sअगरs_size)
			hrसमयr_start(&local->अगरs_समयr,
				      hw->phy->lअगरs_period * NSEC_PER_USEC,
				      HRTIMER_MODE_REL);
		अन्यथा
			hrसमयr_start(&local->अगरs_समयr,
				      hw->phy->sअगरs_period * NSEC_PER_USEC,
				      HRTIMER_MODE_REL);
	पूर्ण अन्यथा अणु
		ieee802154_wake_queue(hw);
	पूर्ण

	dev_consume_skb_any(skb);
पूर्ण
EXPORT_SYMBOL(ieee802154_xmit_complete);

व्योम ieee802154_stop_device(काष्ठा ieee802154_local *local)
अणु
	flush_workqueue(local->workqueue);
	hrसमयr_cancel(&local->अगरs_समयr);
	drv_stop(local);
पूर्ण
