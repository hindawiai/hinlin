<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2020 MediaTek Inc.
 *
 * Author: Ryder Lee <ryder.lee@mediatek.com>
 *         Roy Luo <royluo@google.com>
 *         Felix Fietkau <nbd@nbd.name>
 *         Lorenzo Bianconi <lorenzo@kernel.org>
 */

#समावेश <linux/etherdevice.h>
#समावेश <linux/समयkeeping.h>

#समावेश "mt7615.h"
#समावेश "../dma.h"
#समावेश "mac.h"

व्योम mt7615_tx_complete_skb(काष्ठा mt76_dev *mdev, काष्ठा mt76_queue_entry *e)
अणु
	अगर (!e->txwi) अणु
		dev_kमुक्त_skb_any(e->skb);
		वापस;
	पूर्ण

	/* error path */
	अगर (e->skb == DMA_DUMMY_DATA) अणु
		काष्ठा mt76_txwi_cache *t;
		काष्ठा mt7615_dev *dev;
		काष्ठा mt7615_txp_common *txp;
		u16 token;

		dev = container_of(mdev, काष्ठा mt7615_dev, mt76);
		txp = mt7615_txwi_to_txp(mdev, e->txwi);

		अगर (is_mt7615(&dev->mt76))
			token = le16_to_cpu(txp->fw.token);
		अन्यथा
			token = le16_to_cpu(txp->hw.msdu_id[0]) &
				~MT_MSDU_ID_VALID;

		t = mt76_token_put(mdev, token);
		e->skb = t ? t->skb : शून्य;
	पूर्ण

	अगर (e->skb)
		mt76_tx_complete_skb(mdev, e->wcid, e->skb);
पूर्ण

अटल व्योम
mt7615_ग_लिखो_hw_txp(काष्ठा mt7615_dev *dev, काष्ठा mt76_tx_info *tx_info,
		    व्योम *txp_ptr, u32 id)
अणु
	काष्ठा mt7615_hw_txp *txp = txp_ptr;
	काष्ठा mt7615_txp_ptr *ptr = &txp->ptr[0];
	पूर्णांक i, nbuf = tx_info->nbuf - 1;
	u32 last_mask;

	tx_info->buf[0].len = MT_TXD_SIZE + माप(*txp);
	tx_info->nbuf = 1;

	txp->msdu_id[0] = cpu_to_le16(id | MT_MSDU_ID_VALID);

	अगर (is_mt7663(&dev->mt76))
		last_mask = MT_TXD_LEN_LAST;
	अन्यथा
		last_mask = MT_TXD_LEN_AMSDU_LAST |
			    MT_TXD_LEN_MSDU_LAST;

	क्रम (i = 0; i < nbuf; i++) अणु
		u16 len = tx_info->buf[i + 1].len & MT_TXD_LEN_MASK;
		u32 addr = tx_info->buf[i + 1].addr;

		अगर (i == nbuf - 1)
			len |= last_mask;

		अगर (i & 1) अणु
			ptr->buf1 = cpu_to_le32(addr);
			ptr->len1 = cpu_to_le16(len);
			ptr++;
		पूर्ण अन्यथा अणु
			ptr->buf0 = cpu_to_le32(addr);
			ptr->len0 = cpu_to_le16(len);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
mt7615_ग_लिखो_fw_txp(काष्ठा mt7615_dev *dev, काष्ठा mt76_tx_info *tx_info,
		    व्योम *txp_ptr, u32 id)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)tx_info->skb->data;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(tx_info->skb);
	काष्ठा ieee80211_key_conf *key = info->control.hw_key;
	काष्ठा ieee80211_vअगर *vअगर = info->control.vअगर;
	काष्ठा mt7615_fw_txp *txp = txp_ptr;
	पूर्णांक nbuf = tx_info->nbuf - 1;
	पूर्णांक i;

	क्रम (i = 0; i < nbuf; i++) अणु
		txp->buf[i] = cpu_to_le32(tx_info->buf[i + 1].addr);
		txp->len[i] = cpu_to_le16(tx_info->buf[i + 1].len);
	पूर्ण
	txp->nbuf = nbuf;

	/* pass partial skb header to fw */
	tx_info->buf[0].len = MT_TXD_SIZE + माप(*txp);
	tx_info->buf[1].len = MT_CT_PARSE_LEN;
	tx_info->buf[1].skip_unmap = true;
	tx_info->nbuf = MT_CT_DMA_BUF_NUM;

	txp->flags = cpu_to_le16(MT_CT_INFO_APPLY_TXD);

	अगर (!key)
		txp->flags |= cpu_to_le16(MT_CT_INFO_NONE_CIPHER_FRAME);

	अगर (ieee80211_is_mgmt(hdr->frame_control))
		txp->flags |= cpu_to_le16(MT_CT_INFO_MGMT_FRAME);

	अगर (vअगर) अणु
		काष्ठा mt76_vअगर *mvअगर = (काष्ठा mt76_vअगर *)vअगर->drv_priv;

		txp->bss_idx = mvअगर->idx;
	पूर्ण

	txp->token = cpu_to_le16(id);
	txp->rept_wds_wcid = 0xff;
पूर्ण

पूर्णांक mt7615_tx_prepare_skb(काष्ठा mt76_dev *mdev, व्योम *txwi_ptr,
			  क्रमागत mt76_txq_id qid, काष्ठा mt76_wcid *wcid,
			  काष्ठा ieee80211_sta *sta,
			  काष्ठा mt76_tx_info *tx_info)
अणु
	काष्ठा mt7615_dev *dev = container_of(mdev, काष्ठा mt7615_dev, mt76);
	काष्ठा mt7615_sta *msta = container_of(wcid, काष्ठा mt7615_sta, wcid);
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(tx_info->skb);
	काष्ठा ieee80211_key_conf *key = info->control.hw_key;
	पूर्णांक pid, id;
	u8 *txwi = (u8 *)txwi_ptr;
	काष्ठा mt76_txwi_cache *t;
	व्योम *txp;

	अगर (!wcid)
		wcid = &dev->mt76.global_wcid;

	pid = mt76_tx_status_skb_add(mdev, wcid, tx_info->skb);

	अगर (info->flags & IEEE80211_TX_CTL_RATE_CTRL_PROBE) अणु
		काष्ठा mt7615_phy *phy = &dev->phy;

		अगर ((info->hw_queue & MT_TX_HW_QUEUE_EXT_PHY) && mdev->phy2)
			phy = mdev->phy2->priv;

		spin_lock_bh(&dev->mt76.lock);
		mt7615_mac_set_rates(phy, msta, &info->control.rates[0],
				     msta->rates);
		spin_unlock_bh(&dev->mt76.lock);
	पूर्ण

	t = (काष्ठा mt76_txwi_cache *)(txwi + mdev->drv->txwi_size);
	t->skb = tx_info->skb;

	id = mt76_token_get(mdev, &t);
	अगर (id < 0)
		वापस id;

	mt7615_mac_ग_लिखो_txwi(dev, txwi_ptr, tx_info->skb, wcid, sta,
			      pid, key, false);

	txp = txwi + MT_TXD_SIZE;
	स_रखो(txp, 0, माप(काष्ठा mt7615_txp_common));
	अगर (is_mt7615(&dev->mt76))
		mt7615_ग_लिखो_fw_txp(dev, tx_info, txp, id);
	अन्यथा
		mt7615_ग_लिखो_hw_txp(dev, tx_info, txp, id);

	tx_info->skb = DMA_DUMMY_DATA;

	वापस 0;
पूर्ण

व्योम mt7615_dma_reset(काष्ठा mt7615_dev *dev)
अणु
	पूर्णांक i;

	mt76_clear(dev, MT_WPDMA_GLO_CFG,
		   MT_WPDMA_GLO_CFG_RX_DMA_EN | MT_WPDMA_GLO_CFG_TX_DMA_EN |
		   MT_WPDMA_GLO_CFG_TX_WRITEBACK_DONE);

	usleep_range(1000, 2000);

	क्रम (i = 0; i < __MT_TXQ_MAX; i++)
		mt76_queue_tx_cleanup(dev, dev->mphy.q_tx[i], true);

	क्रम (i = 0; i < __MT_MCUQ_MAX; i++)
		mt76_queue_tx_cleanup(dev, dev->mt76.q_mcu[i], true);

	mt76_क्रम_each_q_rx(&dev->mt76, i)
		mt76_queue_rx_reset(dev, i);

	mt76_tx_status_check(&dev->mt76, शून्य, true);

	mt7615_dma_start(dev);
पूर्ण
EXPORT_SYMBOL_GPL(mt7615_dma_reset);

अटल व्योम
mt7615_hअगर_पूर्णांक_event_trigger(काष्ठा mt7615_dev *dev, u8 event)
अणु
	u32 reg = MT_MCU_INT_EVENT;

	अगर (is_mt7663(&dev->mt76))
		reg = MT7663_MCU_INT_EVENT;

	mt76_wr(dev, reg, event);

	mt7622_trigger_hअगर_पूर्णांक(dev, true);
	mt7622_trigger_hअगर_पूर्णांक(dev, false);
पूर्ण

अटल bool
mt7615_रुको_reset_state(काष्ठा mt7615_dev *dev, u32 state)
अणु
	bool ret;

	ret = रुको_event_समयout(dev->reset_रुको,
				 (READ_ONCE(dev->reset_state) & state),
				 MT7615_RESET_TIMEOUT);
	WARN(!ret, "Timeout waiting for MCU reset state %x\n", state);
	वापस ret;
पूर्ण

अटल व्योम
mt7615_update_vअगर_beacon(व्योम *priv, u8 *mac, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ieee80211_hw *hw = priv;
	काष्ठा mt7615_dev *dev = mt7615_hw_dev(hw);

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_MESH_POINT:
	हाल NL80211_IFTYPE_ADHOC:
	हाल NL80211_IFTYPE_AP:
		mt7615_mcu_add_beacon(dev, hw, vअगर,
				      vअगर->bss_conf.enable_beacon);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
mt7615_update_beacons(काष्ठा mt7615_dev *dev)
अणु
	ieee80211_iterate_active_पूर्णांकerfaces(dev->mt76.hw,
		IEEE80211_IFACE_ITER_RESUME_ALL,
		mt7615_update_vअगर_beacon, dev->mt76.hw);

	अगर (!dev->mt76.phy2)
		वापस;

	ieee80211_iterate_active_पूर्णांकerfaces(dev->mt76.phy2->hw,
		IEEE80211_IFACE_ITER_RESUME_ALL,
		mt7615_update_vअगर_beacon, dev->mt76.phy2->hw);
पूर्ण

व्योम mt7615_mac_reset_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mt7615_phy *phy2;
	काष्ठा mt76_phy *ext_phy;
	काष्ठा mt7615_dev *dev;

	dev = container_of(work, काष्ठा mt7615_dev, reset_work);
	ext_phy = dev->mt76.phy2;
	phy2 = ext_phy ? ext_phy->priv : शून्य;

	अगर (!(READ_ONCE(dev->reset_state) & MT_MCU_CMD_STOP_PDMA))
		वापस;

	ieee80211_stop_queues(mt76_hw(dev));
	अगर (ext_phy)
		ieee80211_stop_queues(ext_phy->hw);

	set_bit(MT76_RESET, &dev->mphy.state);
	set_bit(MT76_MCU_RESET, &dev->mphy.state);
	wake_up(&dev->mt76.mcu.रुको);
	cancel_delayed_work_sync(&dev->mphy.mac_work);
	del_समयr_sync(&dev->phy.roc_समयr);
	cancel_work_sync(&dev->phy.roc_work);
	अगर (phy2) अणु
		set_bit(MT76_RESET, &phy2->mt76->state);
		cancel_delayed_work_sync(&phy2->mt76->mac_work);
		del_समयr_sync(&phy2->roc_समयr);
		cancel_work_sync(&phy2->roc_work);
	पूर्ण

	/* lock/unlock all queues to ensure that no tx is pending */
	mt76_txq_schedule_all(&dev->mphy);
	अगर (ext_phy)
		mt76_txq_schedule_all(ext_phy);

	mt76_worker_disable(&dev->mt76.tx_worker);
	napi_disable(&dev->mt76.napi[0]);
	napi_disable(&dev->mt76.napi[1]);
	napi_disable(&dev->mt76.tx_napi);

	mt7615_mutex_acquire(dev);

	mt7615_hअगर_पूर्णांक_event_trigger(dev, MT_MCU_INT_EVENT_PDMA_STOPPED);

	अगर (mt7615_रुको_reset_state(dev, MT_MCU_CMD_RESET_DONE)) अणु
		mt7615_dma_reset(dev);

		mt7615_tx_token_put(dev);
		idr_init(&dev->mt76.token);

		mt76_wr(dev, MT_WPDMA_MEM_RNG_ERR, 0);

		mt7615_hअगर_पूर्णांक_event_trigger(dev, MT_MCU_INT_EVENT_PDMA_INIT);
		mt7615_रुको_reset_state(dev, MT_MCU_CMD_RECOVERY_DONE);
	पूर्ण

	clear_bit(MT76_MCU_RESET, &dev->mphy.state);
	clear_bit(MT76_RESET, &dev->mphy.state);
	अगर (phy2)
		clear_bit(MT76_RESET, &phy2->mt76->state);

	mt76_worker_enable(&dev->mt76.tx_worker);
	napi_enable(&dev->mt76.tx_napi);
	napi_schedule(&dev->mt76.tx_napi);

	napi_enable(&dev->mt76.napi[0]);
	napi_schedule(&dev->mt76.napi[0]);

	napi_enable(&dev->mt76.napi[1]);
	napi_schedule(&dev->mt76.napi[1]);

	ieee80211_wake_queues(mt76_hw(dev));
	अगर (ext_phy)
		ieee80211_wake_queues(ext_phy->hw);

	mt7615_hअगर_पूर्णांक_event_trigger(dev, MT_MCU_INT_EVENT_RESET_DONE);
	mt7615_रुको_reset_state(dev, MT_MCU_CMD_NORMAL_STATE);

	mt7615_update_beacons(dev);

	mt7615_mutex_release(dev);

	ieee80211_queue_delayed_work(mt76_hw(dev), &dev->mphy.mac_work,
				     MT7615_WATCHDOG_TIME);
	अगर (phy2)
		ieee80211_queue_delayed_work(ext_phy->hw,
					     &phy2->mt76->mac_work,
					     MT7615_WATCHDOG_TIME);

पूर्ण
