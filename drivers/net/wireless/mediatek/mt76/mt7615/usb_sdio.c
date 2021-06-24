<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2020 MediaTek Inc.
 *
 * Author: Lorenzo Bianconi <lorenzo@kernel.org>
 *	   Sean Wang <sean.wang@mediatek.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>

#समावेश "mt7615.h"
#समावेश "mac.h"
#समावेश "mcu.h"
#समावेश "regs.h"

स्थिर u32 mt7663_usb_sdio_reg_map[] = अणु
	[MT_TOP_CFG_BASE]	= 0x80020000,
	[MT_HW_BASE]		= 0x80000000,
	[MT_DMA_SHDL_BASE]	= 0x5000a000,
	[MT_HIF_BASE]		= 0x50000000,
	[MT_CSR_BASE]		= 0x40000000,
	[MT_EFUSE_ADDR_BASE]	= 0x78011000,
	[MT_TOP_MISC_BASE]	= 0x81020000,
	[MT_PLE_BASE]		= 0x82060000,
	[MT_PSE_BASE]		= 0x82068000,
	[MT_PP_BASE]		= 0x8206c000,
	[MT_WTBL_BASE_ADDR]	= 0x820e0000,
	[MT_CFG_BASE]		= 0x820f0000,
	[MT_AGG_BASE]		= 0x820f2000,
	[MT_ARB_BASE]		= 0x820f3000,
	[MT_TMAC_BASE]		= 0x820f4000,
	[MT_RMAC_BASE]		= 0x820f5000,
	[MT_DMA_BASE]		= 0x820f7000,
	[MT_PF_BASE]		= 0x820f8000,
	[MT_WTBL_BASE_ON]	= 0x820f9000,
	[MT_WTBL_BASE_OFF]	= 0x820f9800,
	[MT_LPON_BASE]		= 0x820fb000,
	[MT_MIB_BASE]		= 0x820fd000,
पूर्ण;
EXPORT_SYMBOL_GPL(mt7663_usb_sdio_reg_map);

अटल व्योम
mt7663_usb_sdio_ग_लिखो_txwi(काष्ठा mt7615_dev *dev, काष्ठा mt76_wcid *wcid,
			   क्रमागत mt76_txq_id qid, काष्ठा ieee80211_sta *sta,
			   काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_key_conf *key = info->control.hw_key;
	__le32 *txwi;
	पूर्णांक pid;

	अगर (!wcid)
		wcid = &dev->mt76.global_wcid;

	pid = mt76_tx_status_skb_add(&dev->mt76, wcid, skb);

	txwi = (__le32 *)(skb->data - MT_USB_TXD_SIZE);
	स_रखो(txwi, 0, MT_USB_TXD_SIZE);
	mt7615_mac_ग_लिखो_txwi(dev, txwi, skb, wcid, sta, pid, key, false);
	skb_push(skb, MT_USB_TXD_SIZE);
पूर्ण

अटल पूर्णांक mt7663_usb_sdio_set_rates(काष्ठा mt7615_dev *dev,
				     काष्ठा mt7615_wtbl_rate_desc *wrd)
अणु
	काष्ठा mt7615_rate_desc *rate = &wrd->rate;
	काष्ठा mt7615_sta *sta = wrd->sta;
	u32 w5, w27, addr, val;
	u16 idx;

	lockdep_निश्चित_held(&dev->mt76.mutex);

	अगर (!sta)
		वापस -EINVAL;

	अगर (!mt76_poll(dev, MT_WTBL_UPDATE, MT_WTBL_UPDATE_BUSY, 0, 5000))
		वापस -ETIMEDOUT;

	addr = mt7615_mac_wtbl_addr(dev, sta->wcid.idx);

	w27 = mt76_rr(dev, addr + 27 * 4);
	w27 &= ~MT_WTBL_W27_CC_BW_SEL;
	w27 |= FIELD_PREP(MT_WTBL_W27_CC_BW_SEL, rate->bw);

	w5 = mt76_rr(dev, addr + 5 * 4);
	w5 &= ~(MT_WTBL_W5_BW_CAP | MT_WTBL_W5_CHANGE_BW_RATE |
		MT_WTBL_W5_MPDU_OK_COUNT |
		MT_WTBL_W5_MPDU_FAIL_COUNT |
		MT_WTBL_W5_RATE_IDX);
	w5 |= FIELD_PREP(MT_WTBL_W5_BW_CAP, rate->bw) |
	      FIELD_PREP(MT_WTBL_W5_CHANGE_BW_RATE,
			 rate->bw_idx ? rate->bw_idx - 1 : 7);

	mt76_wr(dev, MT_WTBL_RIUCR0, w5);

	mt76_wr(dev, MT_WTBL_RIUCR1,
		FIELD_PREP(MT_WTBL_RIUCR1_RATE0, rate->probe_val) |
		FIELD_PREP(MT_WTBL_RIUCR1_RATE1, rate->val[0]) |
		FIELD_PREP(MT_WTBL_RIUCR1_RATE2_LO, rate->val[1]));

	mt76_wr(dev, MT_WTBL_RIUCR2,
		FIELD_PREP(MT_WTBL_RIUCR2_RATE2_HI, rate->val[1] >> 8) |
		FIELD_PREP(MT_WTBL_RIUCR2_RATE3, rate->val[1]) |
		FIELD_PREP(MT_WTBL_RIUCR2_RATE4, rate->val[2]) |
		FIELD_PREP(MT_WTBL_RIUCR2_RATE5_LO, rate->val[2]));

	mt76_wr(dev, MT_WTBL_RIUCR3,
		FIELD_PREP(MT_WTBL_RIUCR3_RATE5_HI, rate->val[2] >> 4) |
		FIELD_PREP(MT_WTBL_RIUCR3_RATE6, rate->val[3]) |
		FIELD_PREP(MT_WTBL_RIUCR3_RATE7, rate->val[3]));

	mt76_wr(dev, MT_WTBL_UPDATE,
		FIELD_PREP(MT_WTBL_UPDATE_WLAN_IDX, sta->wcid.idx) |
		MT_WTBL_UPDATE_RATE_UPDATE |
		MT_WTBL_UPDATE_TX_COUNT_CLEAR);

	mt76_wr(dev, addr + 27 * 4, w27);

	sta->rate_probe = sta->rateset[rate->rateset].probe_rate.idx != -1;

	idx = sta->vअगर->mt76.omac_idx;
	idx = idx > HW_BSSID_MAX ? HW_BSSID_0 : idx;
	addr = idx > 1 ? MT_LPON_TCR2(idx): MT_LPON_TCR0(idx);

	mt76_set(dev, addr, MT_LPON_TCR_MODE); /* TSF पढ़ो */
	val = mt76_rr(dev, MT_LPON_UTTR0);
	sta->rate_set_tsf = (val & ~BIT(0)) | rate->rateset;

	अगर (!(sta->wcid.tx_info & MT_WCID_TX_INFO_SET))
		mt76_poll(dev, MT_WTBL_UPDATE, MT_WTBL_UPDATE_BUSY, 0, 5000);

	sta->rate_count = 2 * MT7615_RATE_RETRY * sta->n_rates;
	sta->wcid.tx_info |= MT_WCID_TX_INFO_SET;

	वापस 0;
पूर्ण

अटल व्योम mt7663_usb_sdio_rate_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mt7615_wtbl_rate_desc *wrd, *wrd_next;
	काष्ठा list_head wrd_list;
	काष्ठा mt7615_dev *dev;

	dev = (काष्ठा mt7615_dev *)container_of(work, काष्ठा mt7615_dev,
						rate_work);

	INIT_LIST_HEAD(&wrd_list);
	spin_lock_bh(&dev->mt76.lock);
	list_splice_init(&dev->wrd_head, &wrd_list);
	spin_unlock_bh(&dev->mt76.lock);

	list_क्रम_each_entry_safe(wrd, wrd_next, &wrd_list, node) अणु
		list_del(&wrd->node);

		mt7615_mutex_acquire(dev);
		mt7663_usb_sdio_set_rates(dev, wrd);
		mt7615_mutex_release(dev);

		kमुक्त(wrd);
	पूर्ण
पूर्ण

bool mt7663_usb_sdio_tx_status_data(काष्ठा mt76_dev *mdev, u8 *update)
अणु
	काष्ठा mt7615_dev *dev = container_of(mdev, काष्ठा mt7615_dev, mt76);

	mt7615_mutex_acquire(dev);
	mt7615_mac_sta_poll(dev);
	mt7615_mutex_release(dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt7663_usb_sdio_tx_status_data);

व्योम mt7663_usb_sdio_tx_complete_skb(काष्ठा mt76_dev *mdev,
				     काष्ठा mt76_queue_entry *e)
अणु
	अचिन्हित पूर्णांक headroom = MT_USB_TXD_SIZE;

	अगर (mt76_is_usb(mdev))
		headroom += MT_USB_HDR_SIZE;
	skb_pull(e->skb, headroom);

	mt76_tx_complete_skb(mdev, e->wcid, e->skb);
पूर्ण
EXPORT_SYMBOL_GPL(mt7663_usb_sdio_tx_complete_skb);

पूर्णांक mt7663_usb_sdio_tx_prepare_skb(काष्ठा mt76_dev *mdev, व्योम *txwi_ptr,
				   क्रमागत mt76_txq_id qid, काष्ठा mt76_wcid *wcid,
				   काष्ठा ieee80211_sta *sta,
				   काष्ठा mt76_tx_info *tx_info)
अणु
	काष्ठा mt7615_sta *msta = container_of(wcid, काष्ठा mt7615_sta, wcid);
	काष्ठा mt7615_dev *dev = container_of(mdev, काष्ठा mt7615_dev, mt76);
	काष्ठा sk_buff *skb = tx_info->skb;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	पूर्णांक pad;

	अगर ((info->flags & IEEE80211_TX_CTL_RATE_CTRL_PROBE) &&
	    !msta->rate_probe) अणु
		/* request to configure sampling rate */
		spin_lock_bh(&dev->mt76.lock);
		mt7615_mac_set_rates(&dev->phy, msta, &info->control.rates[0],
				     msta->rates);
		spin_unlock_bh(&dev->mt76.lock);
	पूर्ण

	mt7663_usb_sdio_ग_लिखो_txwi(dev, wcid, qid, sta, skb);
	अगर (mt76_is_usb(mdev)) अणु
		u32 len = skb->len;

		put_unaligned_le32(len, skb_push(skb, माप(len)));
		pad = round_up(skb->len, 4) + 4 - skb->len;
	पूर्ण अन्यथा अणु
		pad = round_up(skb->len, 4) - skb->len;
	पूर्ण

	वापस mt76_skb_adjust_pad(skb, pad);
पूर्ण
EXPORT_SYMBOL_GPL(mt7663_usb_sdio_tx_prepare_skb);

अटल पूर्णांक mt7663u_dma_sched_init(काष्ठा mt7615_dev *dev)
अणु
	पूर्णांक i;

	mt76_rmw(dev, MT_DMA_SHDL(MT_DMASHDL_PKT_MAX_SIZE),
		 MT_DMASHDL_PKT_MAX_SIZE_PLE | MT_DMASHDL_PKT_MAX_SIZE_PSE,
		 FIELD_PREP(MT_DMASHDL_PKT_MAX_SIZE_PLE, 1) |
		 FIELD_PREP(MT_DMASHDL_PKT_MAX_SIZE_PSE, 8));

	/* disable refill group 5 - group 15 and उठाओ group 2
	 * and 3 as high priority.
	 */
	mt76_wr(dev, MT_DMA_SHDL(MT_DMASHDL_REFILL), 0xffe00006);
	mt76_clear(dev, MT_DMA_SHDL(MT_DMASHDL_PAGE), BIT(16));

	क्रम (i = 0; i < 5; i++)
		mt76_wr(dev, MT_DMA_SHDL(MT_DMASHDL_GROUP_QUOTA(i)),
			FIELD_PREP(MT_DMASHDL_GROUP_QUOTA_MIN, 0x3) |
			FIELD_PREP(MT_DMASHDL_GROUP_QUOTA_MAX, 0x1ff));

	mt76_wr(dev, MT_DMA_SHDL(MT_DMASHDL_Q_MAP(0)), 0x42104210);
	mt76_wr(dev, MT_DMA_SHDL(MT_DMASHDL_Q_MAP(1)), 0x42104210);

	mt76_wr(dev, MT_DMA_SHDL(MT_DMASHDL_Q_MAP(2)), 0x4444);

	/* group pririority from high to low:
	 * 15 (cmd groups) > 4 > 3 > 2 > 1 > 0.
	 */
	mt76_wr(dev, MT_DMA_SHDL(MT_DMASHDL_SCHED_SET0), 0x6501234f);
	mt76_wr(dev, MT_DMA_SHDL(MT_DMASHDL_SCHED_SET1), 0xedcba987);
	mt76_wr(dev, MT_DMA_SHDL(MT_DMASHDL_OPTIONAL), 0x7004801c);

	mt76_wr(dev, MT_UDMA_WLCFG_1,
		FIELD_PREP(MT_WL_TX_TMOUT_LMT, 80000) |
		FIELD_PREP(MT_WL_RX_AGG_PKT_LMT, 1));

	/* setup UDMA Rx Flush */
	mt76_clear(dev, MT_UDMA_WLCFG_0, MT_WL_RX_FLUSH);
	/* hअगर reset */
	mt76_set(dev, MT_HIF_RST, MT_HIF_LOGIC_RST_N);

	mt76_set(dev, MT_UDMA_WLCFG_0,
		 MT_WL_RX_AGG_EN | MT_WL_RX_EN | MT_WL_TX_EN |
		 MT_WL_RX_MPSZ_PAD0 | MT_TICK_1US_EN |
		 MT_WL_TX_TMOUT_FUNC_EN);
	mt76_rmw(dev, MT_UDMA_WLCFG_0, MT_WL_RX_AGG_LMT | MT_WL_RX_AGG_TO,
		 FIELD_PREP(MT_WL_RX_AGG_LMT, 32) |
		 FIELD_PREP(MT_WL_RX_AGG_TO, 100));

	वापस 0;
पूर्ण

अटल पूर्णांक mt7663_usb_sdio_init_hardware(काष्ठा mt7615_dev *dev)
अणु
	पूर्णांक ret, idx;

	ret = mt7615_eeprom_init(dev, MT_EFUSE_BASE);
	अगर (ret < 0)
		वापस ret;

	अगर (mt76_is_usb(&dev->mt76)) अणु
		ret = mt7663u_dma_sched_init(dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	set_bit(MT76_STATE_INITIALIZED, &dev->mphy.state);

	/* Beacon and mgmt frames should occupy wcid 0 */
	idx = mt76_wcid_alloc(dev->mt76.wcid_mask, MT7615_WTBL_STA - 1);
	अगर (idx)
		वापस -ENOSPC;

	dev->mt76.global_wcid.idx = idx;
	dev->mt76.global_wcid.hw_key_idx = -1;
	rcu_assign_poपूर्णांकer(dev->mt76.wcid[idx], &dev->mt76.global_wcid);

	वापस 0;
पूर्ण

पूर्णांक mt7663_usb_sdio_रेजिस्टर_device(काष्ठा mt7615_dev *dev)
अणु
	काष्ठा ieee80211_hw *hw = mt76_hw(dev);
	पूर्णांक err;

	INIT_WORK(&dev->rate_work, mt7663_usb_sdio_rate_work);
	INIT_LIST_HEAD(&dev->wrd_head);
	mt7615_init_device(dev);

	err = mt7663_usb_sdio_init_hardware(dev);
	अगर (err)
		वापस err;

	hw->extra_tx_headroom += MT_USB_TXD_SIZE;
	अगर (mt76_is_usb(&dev->mt76)) अणु
		hw->extra_tx_headroom += MT_USB_HDR_SIZE;
		/* check hw sg support in order to enable AMSDU */
		अगर (dev->mt76.usb.sg_en)
			hw->max_tx_fragments = MT_HW_TXP_MAX_BUF_NUM;
		अन्यथा
			hw->max_tx_fragments = 1;
	पूर्ण

	err = mt76_रेजिस्टर_device(&dev->mt76, true, mt7615_rates,
				   ARRAY_SIZE(mt7615_rates));
	अगर (err < 0)
		वापस err;

	अगर (!dev->mt76.usb.sg_en) अणु
		काष्ठा ieee80211_sta_vht_cap *vht_cap;

		/* decrease max A-MSDU size अगर SG is not supported */
		vht_cap = &dev->mphy.sband_5g.sband.vht_cap;
		vht_cap->cap &= ~IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_11454;
	पूर्ण

	ieee80211_queue_work(hw, &dev->mcu_work);
	mt7615_init_txघातer(dev, &dev->mphy.sband_2g.sband);
	mt7615_init_txघातer(dev, &dev->mphy.sband_5g.sband);

	वापस mt7615_init_debugfs(dev);
पूर्ण
EXPORT_SYMBOL_GPL(mt7663_usb_sdio_रेजिस्टर_device);

MODULE_AUTHOR("Lorenzo Bianconi <lorenzo@kernel.org>");
MODULE_AUTHOR("Sean Wang <sean.wang@mediatek.com>");
MODULE_LICENSE("Dual BSD/GPL");
