<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/* Copyright (C) 2020 MediaTek Inc. */

#अगर_अघोषित __MT76_CONNAC_H
#घोषणा __MT76_CONNAC_H

#समावेश "mt76.h"

#घोषणा MT76_CONNAC_SCAN_IE_LEN			600
#घोषणा MT76_CONNAC_MAX_SCHED_SCAN_INTERVAL	10
#घोषणा MT76_CONNAC_MAX_SCHED_SCAN_SSID		10
#घोषणा MT76_CONNAC_MAX_SCAN_MATCH		16

#घोषणा MT76_CONNAC_COREDUMP_TIMEOUT		(HZ / 20)
#घोषणा MT76_CONNAC_COREDUMP_SZ			(128 * 1024)

क्रमागत अणु
	CMD_CBW_20MHZ = IEEE80211_STA_RX_BW_20,
	CMD_CBW_40MHZ = IEEE80211_STA_RX_BW_40,
	CMD_CBW_80MHZ = IEEE80211_STA_RX_BW_80,
	CMD_CBW_160MHZ = IEEE80211_STA_RX_BW_160,
	CMD_CBW_10MHZ,
	CMD_CBW_5MHZ,
	CMD_CBW_8080MHZ,

	CMD_HE_MCS_BW80 = 0,
	CMD_HE_MCS_BW160,
	CMD_HE_MCS_BW8080,
	CMD_HE_MCS_BW_NUM
पूर्ण;

क्रमागत अणु
	HW_BSSID_0 = 0x0,
	HW_BSSID_1,
	HW_BSSID_2,
	HW_BSSID_3,
	HW_BSSID_MAX = HW_BSSID_3,
	EXT_BSSID_START = 0x10,
	EXT_BSSID_1,
	EXT_BSSID_15 = 0x1f,
	EXT_BSSID_MAX = EXT_BSSID_15,
	REPEATER_BSSID_START = 0x20,
	REPEATER_BSSID_MAX = 0x3f,
पूर्ण;

काष्ठा mt76_connac_pm अणु
	bool enable;

	spinlock_t txq_lock;
	काष्ठा अणु
		काष्ठा mt76_wcid *wcid;
		काष्ठा sk_buff *skb;
	पूर्ण tx_q[IEEE80211_NUM_ACS];

	काष्ठा work_काष्ठा wake_work;
	रुको_queue_head_t रुको;

	काष्ठा अणु
		spinlock_t lock;
		u32 count;
	पूर्ण wake;
	काष्ठा mutex mutex;

	काष्ठा delayed_work ps_work;
	अचिन्हित दीर्घ last_activity;
	अचिन्हित दीर्घ idle_समयout;

	काष्ठा अणु
		अचिन्हित दीर्घ last_wake_event;
		अचिन्हित दीर्घ awake_समय;
		अचिन्हित दीर्घ last_करोze_event;
		अचिन्हित दीर्घ करोze_समय;
		अचिन्हित पूर्णांक lp_wake;
	पूर्ण stats;
पूर्ण;

काष्ठा mt76_connac_coredump अणु
	काष्ठा sk_buff_head msg_list;
	काष्ठा delayed_work work;
	अचिन्हित दीर्घ last_activity;
पूर्ण;

बाह्य स्थिर काष्ठा wiphy_wowlan_support mt76_connac_wowlan_support;

अटल अंतरभूत bool is_mt7921(काष्ठा mt76_dev *dev)
अणु
	वापस mt76_chip(dev) == 0x7961;
पूर्ण

अटल अंतरभूत bool is_mt7663(काष्ठा mt76_dev *dev)
अणु
	वापस mt76_chip(dev) == 0x7663;
पूर्ण

पूर्णांक mt76_connac_pm_wake(काष्ठा mt76_phy *phy, काष्ठा mt76_connac_pm *pm);
व्योम mt76_connac_घातer_save_sched(काष्ठा mt76_phy *phy,
				  काष्ठा mt76_connac_pm *pm);
व्योम mt76_connac_मुक्त_pending_tx_skbs(काष्ठा mt76_connac_pm *pm,
				      काष्ठा mt76_wcid *wcid);

अटल अंतरभूत bool
mt76_connac_pm_ref(काष्ठा mt76_phy *phy, काष्ठा mt76_connac_pm *pm)
अणु
	bool ret = false;

	spin_lock_bh(&pm->wake.lock);
	अगर (test_bit(MT76_STATE_PM, &phy->state))
		जाओ out;

	pm->wake.count++;
	ret = true;
out:
	spin_unlock_bh(&pm->wake.lock);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम
mt76_connac_pm_unref(काष्ठा mt76_connac_pm *pm)
अणु
	spin_lock_bh(&pm->wake.lock);
	pm->wake.count--;
	pm->last_activity = jअगरfies;
	spin_unlock_bh(&pm->wake.lock);
पूर्ण

अटल अंतरभूत bool
mt76_connac_skip_fw_pmctrl(काष्ठा mt76_phy *phy, काष्ठा mt76_connac_pm *pm)
अणु
	bool ret;

	spin_lock_bh(&pm->wake.lock);
	ret = pm->wake.count || test_and_set_bit(MT76_STATE_PM, &phy->state);
	spin_unlock_bh(&pm->wake.lock);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम
mt76_connac_mutex_acquire(काष्ठा mt76_dev *dev, काष्ठा mt76_connac_pm *pm)
	__acquires(&dev->mutex)
अणु
	mutex_lock(&dev->mutex);
	mt76_connac_pm_wake(&dev->phy, pm);
पूर्ण

अटल अंतरभूत व्योम
mt76_connac_mutex_release(काष्ठा mt76_dev *dev, काष्ठा mt76_connac_pm *pm)
	__releases(&dev->mutex)
अणु
	mt76_connac_घातer_save_sched(&dev->phy, pm);
	mutex_unlock(&dev->mutex);
पूर्ण

व्योम mt76_connac_pm_queue_skb(काष्ठा ieee80211_hw *hw,
			      काष्ठा mt76_connac_pm *pm,
			      काष्ठा mt76_wcid *wcid,
			      काष्ठा sk_buff *skb);
व्योम mt76_connac_pm_dequeue_skbs(काष्ठा mt76_phy *phy,
				 काष्ठा mt76_connac_pm *pm);

#पूर्ण_अगर /* __MT76_CONNAC_H */
