<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2019 MediaTek Inc.
 *
 * Author: Roy Luo <royluo@google.com>
 *         Ryder Lee <ryder.lee@mediatek.com>
 */

#समावेश <linux/firmware.h>
#समावेश "mt7615.h"
#समावेश "mcu.h"
#समावेश "mac.h"
#समावेश "eeprom.h"

अटल bool prefer_offload_fw = true;
module_param(prefer_offload_fw, bool, 0644);
MODULE_PARM_DESC(prefer_offload_fw,
		 "Prefer client mode offload firmware (MT7663)");

काष्ठा mt7615_patch_hdr अणु
	अक्षर build_date[16];
	अक्षर platक्रमm[4];
	__be32 hw_sw_ver;
	__be32 patch_ver;
	__be16 checksum;
पूर्ण __packed;

काष्ठा mt7615_fw_trailer अणु
	__le32 addr;
	u8 chip_id;
	u8 feature_set;
	u8 eco_code;
	अक्षर fw_ver[10];
	अक्षर build_date[15];
	__le32 len;
पूर्ण __packed;

#घोषणा FW_V3_COMMON_TAILER_SIZE	36
#घोषणा FW_V3_REGION_TAILER_SIZE	40
#घोषणा FW_START_OVERRIDE		BIT(0)
#घोषणा FW_START_DLYCAL                 BIT(1)
#घोषणा FW_START_WORKING_PDA_CR4	BIT(2)

काष्ठा mt7663_fw_trailer अणु
	u8 chip_id;
	u8 eco_code;
	u8 n_region;
	u8 क्रमmat_ver;
	u8 क्रमmat_flag;
	u8 reserv[2];
	अक्षर fw_ver[10];
	अक्षर build_date[15];
	__le32 crc;
पूर्ण __packed;

काष्ठा mt7663_fw_buf अणु
	__le32 crc;
	__le32 d_img_size;
	__le32 block_size;
	u8 rsv[4];
	__le32 img_dest_addr;
	__le32 img_size;
	u8 feature_set;
पूर्ण;

#घोषणा MT7615_PATCH_ADDRESS		0x80000
#घोषणा MT7622_PATCH_ADDRESS		0x9c000
#घोषणा MT7663_PATCH_ADDRESS		0xdc000

#घोषणा N9_REGION_NUM			2
#घोषणा CR4_REGION_NUM			1

#घोषणा IMG_CRC_LEN			4

#घोषणा FW_FEATURE_SET_ENCRYPT		BIT(0)
#घोषणा FW_FEATURE_SET_KEY_IDX		GENMASK(2, 1)

#घोषणा DL_MODE_ENCRYPT			BIT(0)
#घोषणा DL_MODE_KEY_IDX			GENMASK(2, 1)
#घोषणा DL_MODE_RESET_SEC_IV		BIT(3)
#घोषणा DL_MODE_WORKING_PDA_CR4		BIT(4)
#घोषणा DL_MODE_VALID_RAM_ENTRY         BIT(5)
#घोषणा DL_MODE_NEED_RSP		BIT(31)

#घोषणा FW_START_OVERRIDE		BIT(0)
#घोषणा FW_START_WORKING_PDA_CR4	BIT(2)

व्योम mt7615_mcu_fill_msg(काष्ठा mt7615_dev *dev, काष्ठा sk_buff *skb,
			 पूर्णांक cmd, पूर्णांक *रुको_seq)
अणु
	पूर्णांक txd_len, mcu_cmd = cmd & MCU_CMD_MASK;
	काष्ठा mt7615_uni_txd *uni_txd;
	काष्ठा mt7615_mcu_txd *mcu_txd;
	u8 seq, q_idx, pkt_fmt;
	__le32 *txd;
	u32 val;

	/* TODO: make dynamic based on msg type */
	dev->mt76.mcu.समयout = 20 * HZ;

	seq = ++dev->mt76.mcu.msg_seq & 0xf;
	अगर (!seq)
		seq = ++dev->mt76.mcu.msg_seq & 0xf;
	अगर (रुको_seq)
		*रुको_seq = seq;

	txd_len = cmd & MCU_UNI_PREFIX ? माप(*uni_txd) : माप(*mcu_txd);
	txd = (__le32 *)skb_push(skb, txd_len);

	अगर (cmd != MCU_CMD_FW_SCATTER) अणु
		q_idx = MT_TX_MCU_PORT_RX_Q0;
		pkt_fmt = MT_TX_TYPE_CMD;
	पूर्ण अन्यथा अणु
		q_idx = MT_TX_MCU_PORT_RX_FWDL;
		pkt_fmt = MT_TX_TYPE_FW;
	पूर्ण

	val = FIELD_PREP(MT_TXD0_TX_BYTES, skb->len) |
	      FIELD_PREP(MT_TXD0_P_IDX, MT_TX_PORT_IDX_MCU) |
	      FIELD_PREP(MT_TXD0_Q_IDX, q_idx);
	txd[0] = cpu_to_le32(val);

	val = MT_TXD1_LONG_FORMAT |
	      FIELD_PREP(MT_TXD1_HDR_FORMAT, MT_HDR_FORMAT_CMD) |
	      FIELD_PREP(MT_TXD1_PKT_FMT, pkt_fmt);
	txd[1] = cpu_to_le32(val);

	अगर (cmd & MCU_UNI_PREFIX) अणु
		uni_txd = (काष्ठा mt7615_uni_txd *)txd;
		uni_txd->len = cpu_to_le16(skb->len - माप(uni_txd->txd));
		uni_txd->option = MCU_CMD_UNI_EXT_ACK;
		uni_txd->cid = cpu_to_le16(mcu_cmd);
		uni_txd->s2d_index = MCU_S2D_H2N;
		uni_txd->pkt_type = MCU_PKT_ID;
		uni_txd->seq = seq;

		वापस;
	पूर्ण

	mcu_txd = (काष्ठा mt7615_mcu_txd *)txd;
	mcu_txd->len = cpu_to_le16(skb->len - माप(mcu_txd->txd));
	mcu_txd->pq_id = cpu_to_le16(MCU_PQ_ID(MT_TX_PORT_IDX_MCU, q_idx));
	mcu_txd->s2d_index = MCU_S2D_H2N;
	mcu_txd->pkt_type = MCU_PKT_ID;
	mcu_txd->seq = seq;

	चयन (cmd & ~MCU_CMD_MASK) अणु
	हाल MCU_FW_PREFIX:
		mcu_txd->set_query = MCU_Q_NA;
		mcu_txd->cid = mcu_cmd;
		अवरोध;
	हाल MCU_CE_PREFIX:
		अगर (cmd & MCU_QUERY_MASK)
			mcu_txd->set_query = MCU_Q_QUERY;
		अन्यथा
			mcu_txd->set_query = MCU_Q_SET;
		mcu_txd->cid = mcu_cmd;
		अवरोध;
	शेष:
		mcu_txd->cid = MCU_CMD_EXT_CID;
		अगर (cmd & MCU_QUERY_PREFIX)
			mcu_txd->set_query = MCU_Q_QUERY;
		अन्यथा
			mcu_txd->set_query = MCU_Q_SET;
		mcu_txd->ext_cid = mcu_cmd;
		mcu_txd->ext_cid_ack = 1;
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mt7615_mcu_fill_msg);

पूर्णांक mt7615_mcu_parse_response(काष्ठा mt76_dev *mdev, पूर्णांक cmd,
			      काष्ठा sk_buff *skb, पूर्णांक seq)
अणु
	काष्ठा mt7615_mcu_rxd *rxd;
	पूर्णांक ret = 0;

	अगर (!skb) अणु
		dev_err(mdev->dev, "Message %08x (seq %d) timeout\n",
			cmd, seq);
		वापस -ETIMEDOUT;
	पूर्ण

	rxd = (काष्ठा mt7615_mcu_rxd *)skb->data;
	अगर (seq != rxd->seq)
		वापस -EAGAIN;

	चयन (cmd) अणु
	हाल MCU_CMD_PATCH_SEM_CONTROL:
		skb_pull(skb, माप(*rxd) - 4);
		ret = *skb->data;
		अवरोध;
	हाल MCU_EXT_CMD_GET_TEMP:
		skb_pull(skb, माप(*rxd));
		ret = le32_to_cpu(*(__le32 *)skb->data);
		अवरोध;
	हाल MCU_EXT_CMD_RF_REG_ACCESS | MCU_QUERY_PREFIX:
		skb_pull(skb, माप(*rxd));
		ret = le32_to_cpu(*(__le32 *)&skb->data[8]);
		अवरोध;
	हाल MCU_UNI_CMD_DEV_INFO_UPDATE:
	हाल MCU_UNI_CMD_BSS_INFO_UPDATE:
	हाल MCU_UNI_CMD_STA_REC_UPDATE:
	हाल MCU_UNI_CMD_HIF_CTRL:
	हाल MCU_UNI_CMD_OFFLOAD:
	हाल MCU_UNI_CMD_SUSPEND: अणु
		काष्ठा mt7615_mcu_uni_event *event;

		skb_pull(skb, माप(*rxd));
		event = (काष्ठा mt7615_mcu_uni_event *)skb->data;
		ret = le32_to_cpu(event->status);
		अवरोध;
	पूर्ण
	हाल MCU_CMD_REG_READ: अणु
		काष्ठा mt7615_mcu_reg_event *event;

		skb_pull(skb, माप(*rxd));
		event = (काष्ठा mt7615_mcu_reg_event *)skb->data;
		ret = (पूर्णांक)le32_to_cpu(event->val);
		अवरोध;
	पूर्ण
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mt7615_mcu_parse_response);

अटल पूर्णांक
mt7615_mcu_send_message(काष्ठा mt76_dev *mdev, काष्ठा sk_buff *skb,
			पूर्णांक cmd, पूर्णांक *seq)
अणु
	काष्ठा mt7615_dev *dev = container_of(mdev, काष्ठा mt7615_dev, mt76);
	क्रमागत mt76_mcuq_id qid;

	mt7615_mcu_fill_msg(dev, skb, cmd, seq);
	अगर (test_bit(MT76_STATE_MCU_RUNNING, &dev->mphy.state))
		qid = MT_MCUQ_WM;
	अन्यथा
		qid = MT_MCUQ_FWDL;

	वापस mt76_tx_queue_skb_raw(dev, dev->mt76.q_mcu[qid], skb, 0);
पूर्ण

u32 mt7615_rf_rr(काष्ठा mt7615_dev *dev, u32 wf, u32 reg)
अणु
	काष्ठा अणु
		__le32 wअगरi_stream;
		__le32 address;
		__le32 data;
	पूर्ण req = अणु
		.wअगरi_stream = cpu_to_le32(wf),
		.address = cpu_to_le32(reg),
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76,
				 MCU_EXT_CMD_RF_REG_ACCESS | MCU_QUERY_PREFIX,
				 &req, माप(req), true);
पूर्ण

पूर्णांक mt7615_rf_wr(काष्ठा mt7615_dev *dev, u32 wf, u32 reg, u32 val)
अणु
	काष्ठा अणु
		__le32 wअगरi_stream;
		__le32 address;
		__le32 data;
	पूर्ण req = अणु
		.wअगरi_stream = cpu_to_le32(wf),
		.address = cpu_to_le32(reg),
		.data = cpu_to_le32(val),
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD_RF_REG_ACCESS, &req,
				 माप(req), false);
पूर्ण

व्योम mt7622_trigger_hअगर_पूर्णांक(काष्ठा mt7615_dev *dev, bool en)
अणु
	अगर (!is_mt7622(&dev->mt76))
		वापस;

	regmap_update_bits(dev->infracfg, MT_INFRACFG_MISC,
			   MT_INFRACFG_MISC_AP2CONN_WAKE,
			   !en * MT_INFRACFG_MISC_AP2CONN_WAKE);
पूर्ण
EXPORT_SYMBOL_GPL(mt7622_trigger_hअगर_पूर्णांक);

अटल पूर्णांक mt7615_mcu_drv_pmctrl(काष्ठा mt7615_dev *dev)
अणु
	काष्ठा mt76_phy *mphy = &dev->mt76.phy;
	काष्ठा mt76_connac_pm *pm = &dev->pm;
	काष्ठा mt76_dev *mdev = &dev->mt76;
	u32 addr;
	पूर्णांक err;

	अगर (is_mt7663(mdev)) अणु
		/* Clear firmware own via N9 eपूर्णांक */
		mt76_wr(dev, MT_PCIE_DOORBELL_PUSH, MT_CFG_LPCR_HOST_DRV_OWN);
		mt76_poll(dev, MT_CONN_ON_MISC, MT_CFG_LPCR_HOST_FW_OWN, 0, 3000);

		addr = MT_CONN_HIF_ON_LPCTL;
	पूर्ण अन्यथा अणु
		addr = MT_CFG_LPCR_HOST;
	पूर्ण

	mt76_wr(dev, addr, MT_CFG_LPCR_HOST_DRV_OWN);

	mt7622_trigger_hअगर_पूर्णांक(dev, true);

	err = !mt76_poll_msec(dev, addr, MT_CFG_LPCR_HOST_FW_OWN, 0, 3000);

	mt7622_trigger_hअगर_पूर्णांक(dev, false);

	अगर (err) अणु
		dev_err(mdev->dev, "driver own failed\n");
		वापस -ETIMEDOUT;
	पूर्ण

	clear_bit(MT76_STATE_PM, &mphy->state);

	pm->stats.last_wake_event = jअगरfies;
	pm->stats.करोze_समय += pm->stats.last_wake_event -
			       pm->stats.last_करोze_event;

	वापस 0;
पूर्ण

अटल पूर्णांक mt7615_mcu_lp_drv_pmctrl(काष्ठा mt7615_dev *dev)
अणु
	काष्ठा mt76_phy *mphy = &dev->mt76.phy;
	काष्ठा mt76_connac_pm *pm = &dev->pm;
	पूर्णांक i, err = 0;

	mutex_lock(&pm->mutex);

	अगर (!test_bit(MT76_STATE_PM, &mphy->state))
		जाओ out;

	क्रम (i = 0; i < MT7615_DRV_OWN_RETRY_COUNT; i++) अणु
		mt76_wr(dev, MT_PCIE_DOORBELL_PUSH, MT_CFG_LPCR_HOST_DRV_OWN);
		अगर (mt76_poll_msec(dev, MT_CONN_HIF_ON_LPCTL,
				   MT_CFG_LPCR_HOST_FW_OWN, 0, 50))
			अवरोध;
	पूर्ण

	अगर (i == MT7615_DRV_OWN_RETRY_COUNT) अणु
		dev_err(dev->mt76.dev, "driver own failed\n");
		err = -EIO;
		जाओ out;
	पूर्ण
	clear_bit(MT76_STATE_PM, &mphy->state);

	pm->stats.last_wake_event = jअगरfies;
	pm->stats.करोze_समय += pm->stats.last_wake_event -
			       pm->stats.last_करोze_event;
out:
	mutex_unlock(&pm->mutex);

	वापस err;
पूर्ण

अटल पूर्णांक mt7615_mcu_fw_pmctrl(काष्ठा mt7615_dev *dev)
अणु
	काष्ठा mt76_phy *mphy = &dev->mt76.phy;
	काष्ठा mt76_connac_pm *pm = &dev->pm;
	पूर्णांक err = 0;
	u32 addr;

	mutex_lock(&pm->mutex);

	अगर (mt76_connac_skip_fw_pmctrl(mphy, pm))
		जाओ out;

	mt7622_trigger_hअगर_पूर्णांक(dev, true);

	addr = is_mt7663(&dev->mt76) ? MT_CONN_HIF_ON_LPCTL : MT_CFG_LPCR_HOST;
	mt76_wr(dev, addr, MT_CFG_LPCR_HOST_FW_OWN);

	अगर (is_mt7622(&dev->mt76) &&
	    !mt76_poll_msec(dev, addr, MT_CFG_LPCR_HOST_FW_OWN,
			    MT_CFG_LPCR_HOST_FW_OWN, 3000)) अणु
		dev_err(dev->mt76.dev, "Timeout for firmware own\n");
		clear_bit(MT76_STATE_PM, &mphy->state);
		err = -EIO;
	पूर्ण

	mt7622_trigger_hअगर_पूर्णांक(dev, false);

	pm->stats.last_करोze_event = jअगरfies;
	pm->stats.awake_समय += pm->stats.last_करोze_event -
				pm->stats.last_wake_event;
out:
	mutex_unlock(&pm->mutex);

	वापस err;
पूर्ण

अटल व्योम
mt7615_mcu_csa_finish(व्योम *priv, u8 *mac, काष्ठा ieee80211_vअगर *vअगर)
अणु
	अगर (vअगर->csa_active)
		ieee80211_csa_finish(vअगर);
पूर्ण

अटल व्योम
mt7615_mcu_rx_csa_notअगरy(काष्ठा mt7615_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा mt7615_phy *ext_phy = mt7615_ext_phy(dev);
	काष्ठा mt76_phy *mphy = &dev->mt76.phy;
	काष्ठा mt7615_mcu_csa_notअगरy *c;

	c = (काष्ठा mt7615_mcu_csa_notअगरy *)skb->data;

	अगर (ext_phy && ext_phy->omac_mask & BIT_ULL(c->omac_idx))
		mphy = dev->mt76.phy2;

	ieee80211_iterate_active_पूर्णांकerfaces_atomic(mphy->hw,
			IEEE80211_IFACE_ITER_RESUME_ALL,
			mt7615_mcu_csa_finish, mphy->hw);
पूर्ण

अटल व्योम
mt7615_mcu_rx_radar_detected(काष्ठा mt7615_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा mt76_phy *mphy = &dev->mt76.phy;
	काष्ठा mt7615_mcu_rdd_report *r;

	r = (काष्ठा mt7615_mcu_rdd_report *)skb->data;

	अगर (r->band_idx && dev->mt76.phy2)
		mphy = dev->mt76.phy2;

	ieee80211_radar_detected(mphy->hw);
	dev->hw_pattern++;
पूर्ण

अटल व्योम
mt7615_mcu_rx_log_message(काष्ठा mt7615_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा mt7615_mcu_rxd *rxd = (काष्ठा mt7615_mcu_rxd *)skb->data;
	स्थिर अक्षर *data = (अक्षर *)&rxd[1];
	स्थिर अक्षर *type;

	चयन (rxd->s2d_index) अणु
	हाल 0:
		type = "N9";
		अवरोध;
	हाल 2:
		type = "CR4";
		अवरोध;
	शेष:
		type = "unknown";
		अवरोध;
	पूर्ण

	wiphy_info(mt76_hw(dev)->wiphy, "%s: %.*s", type,
		   (पूर्णांक)(skb->len - माप(*rxd)), data);
पूर्ण

अटल व्योम
mt7615_mcu_rx_ext_event(काष्ठा mt7615_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा mt7615_mcu_rxd *rxd = (काष्ठा mt7615_mcu_rxd *)skb->data;

	चयन (rxd->ext_eid) अणु
	हाल MCU_EXT_EVENT_RDD_REPORT:
		mt7615_mcu_rx_radar_detected(dev, skb);
		अवरोध;
	हाल MCU_EXT_EVENT_CSA_NOTIFY:
		mt7615_mcu_rx_csa_notअगरy(dev, skb);
		अवरोध;
	हाल MCU_EXT_EVENT_FW_LOG_2_HOST:
		mt7615_mcu_rx_log_message(dev, skb);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
mt7615_mcu_scan_event(काष्ठा mt7615_dev *dev, काष्ठा sk_buff *skb)
अणु
	u8 *seq_num = skb->data + माप(काष्ठा mt7615_mcu_rxd);
	काष्ठा mt7615_phy *phy;
	काष्ठा mt76_phy *mphy;

	अगर (*seq_num & BIT(7) && dev->mt76.phy2)
		mphy = dev->mt76.phy2;
	अन्यथा
		mphy = &dev->mt76.phy;

	phy = (काष्ठा mt7615_phy *)mphy->priv;

	spin_lock_bh(&dev->mt76.lock);
	__skb_queue_tail(&phy->scan_event_list, skb);
	spin_unlock_bh(&dev->mt76.lock);

	ieee80211_queue_delayed_work(mphy->hw, &phy->scan_work,
				     MT7615_HW_SCAN_TIMEOUT);
पूर्ण

अटल व्योम
mt7615_mcu_roc_event(काष्ठा mt7615_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा mt7615_roc_tlv *event;
	काष्ठा mt7615_phy *phy;
	काष्ठा mt76_phy *mphy;
	पूर्णांक duration;

	skb_pull(skb, माप(काष्ठा mt7615_mcu_rxd));
	event = (काष्ठा mt7615_roc_tlv *)skb->data;

	अगर (event->dbdc_band && dev->mt76.phy2)
		mphy = dev->mt76.phy2;
	अन्यथा
		mphy = &dev->mt76.phy;

	ieee80211_पढ़ोy_on_channel(mphy->hw);

	phy = (काष्ठा mt7615_phy *)mphy->priv;
	phy->roc_grant = true;
	wake_up(&phy->roc_रुको);

	duration = le32_to_cpu(event->max_पूर्णांकerval);
	mod_समयr(&phy->roc_समयr,
		  round_jअगरfies_up(jअगरfies + msecs_to_jअगरfies(duration)));
पूर्ण

अटल व्योम
mt7615_mcu_beacon_loss_event(काष्ठा mt7615_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा mt76_connac_beacon_loss_event *event;
	काष्ठा mt76_phy *mphy;
	u8 band_idx = 0; /* DBDC support */

	skb_pull(skb, माप(काष्ठा mt7615_mcu_rxd));
	event = (काष्ठा mt76_connac_beacon_loss_event *)skb->data;
	अगर (band_idx && dev->mt76.phy2)
		mphy = dev->mt76.phy2;
	अन्यथा
		mphy = &dev->mt76.phy;

	ieee80211_iterate_active_पूर्णांकerfaces_atomic(mphy->hw,
					IEEE80211_IFACE_ITER_RESUME_ALL,
					mt76_connac_mcu_beacon_loss_iter,
					event);
पूर्ण

अटल व्योम
mt7615_mcu_bss_event(काष्ठा mt7615_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा mt76_connac_mcu_bss_event *event;
	काष्ठा mt76_phy *mphy;
	u8 band_idx = 0; /* DBDC support */

	skb_pull(skb, माप(काष्ठा mt7615_mcu_rxd));
	event = (काष्ठा mt76_connac_mcu_bss_event *)skb->data;

	अगर (band_idx && dev->mt76.phy2)
		mphy = dev->mt76.phy2;
	अन्यथा
		mphy = &dev->mt76.phy;

	अगर (event->is_असलent)
		ieee80211_stop_queues(mphy->hw);
	अन्यथा
		ieee80211_wake_queues(mphy->hw);
पूर्ण

अटल व्योम
mt7615_mcu_rx_unsolicited_event(काष्ठा mt7615_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा mt7615_mcu_rxd *rxd = (काष्ठा mt7615_mcu_rxd *)skb->data;

	चयन (rxd->eid) अणु
	हाल MCU_EVENT_EXT:
		mt7615_mcu_rx_ext_event(dev, skb);
		अवरोध;
	हाल MCU_EVENT_BSS_BEACON_LOSS:
		mt7615_mcu_beacon_loss_event(dev, skb);
		अवरोध;
	हाल MCU_EVENT_ROC:
		mt7615_mcu_roc_event(dev, skb);
		अवरोध;
	हाल MCU_EVENT_SCHED_SCAN_DONE:
	हाल MCU_EVENT_SCAN_DONE:
		mt7615_mcu_scan_event(dev, skb);
		वापस;
	हाल MCU_EVENT_BSS_ABSENCE:
		mt7615_mcu_bss_event(dev, skb);
		अवरोध;
	हाल MCU_EVENT_COREDUMP:
		mt76_connac_mcu_coredump_event(&dev->mt76, skb,
					       &dev->coredump);
		वापस;
	शेष:
		अवरोध;
	पूर्ण
	dev_kमुक्त_skb(skb);
पूर्ण

व्योम mt7615_mcu_rx_event(काष्ठा mt7615_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा mt7615_mcu_rxd *rxd = (काष्ठा mt7615_mcu_rxd *)skb->data;

	अगर (rxd->ext_eid == MCU_EXT_EVENT_THERMAL_PROTECT ||
	    rxd->ext_eid == MCU_EXT_EVENT_FW_LOG_2_HOST ||
	    rxd->ext_eid == MCU_EXT_EVENT_ASSERT_DUMP ||
	    rxd->ext_eid == MCU_EXT_EVENT_PS_SYNC ||
	    rxd->eid == MCU_EVENT_BSS_BEACON_LOSS ||
	    rxd->eid == MCU_EVENT_SCHED_SCAN_DONE ||
	    rxd->eid == MCU_EVENT_BSS_ABSENCE ||
	    rxd->eid == MCU_EVENT_SCAN_DONE ||
	    rxd->eid == MCU_EVENT_COREDUMP ||
	    rxd->eid == MCU_EVENT_ROC ||
	    !rxd->seq)
		mt7615_mcu_rx_unsolicited_event(dev, skb);
	अन्यथा
		mt76_mcu_rx_event(&dev->mt76, skb);
पूर्ण

अटल पूर्णांक
mt7615_mcu_muar_config(काष्ठा mt7615_dev *dev, काष्ठा ieee80211_vअगर *vअगर,
		       bool bssid, bool enable)
अणु
	काष्ठा mt7615_vअगर *mvअगर = (काष्ठा mt7615_vअगर *)vअगर->drv_priv;
	u32 idx = mvअगर->mt76.omac_idx - REPEATER_BSSID_START;
	u32 mask = dev->omac_mask >> 32 & ~BIT(idx);
	स्थिर u8 *addr = vअगर->addr;
	काष्ठा अणु
		u8 mode;
		u8 क्रमce_clear;
		u8 clear_biपंचांगap[8];
		u8 entry_count;
		u8 ग_लिखो;

		u8 index;
		u8 bssid;
		u8 addr[ETH_ALEN];
	पूर्ण __packed req = अणु
		.mode = !!mask || enable,
		.entry_count = 1,
		.ग_लिखो = 1,

		.index = idx * 2 + bssid,
	पूर्ण;

	अगर (bssid)
		addr = vअगर->bss_conf.bssid;

	अगर (enable)
		ether_addr_copy(req.addr, addr);

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD_MUAR_UPDATE, &req,
				 माप(req), true);
पूर्ण

अटल पूर्णांक
mt7615_mcu_add_dev(काष्ठा mt7615_phy *phy, काष्ठा ieee80211_vअगर *vअगर,
		   bool enable)
अणु
	काष्ठा mt7615_vअगर *mvअगर = (काष्ठा mt7615_vअगर *)vअगर->drv_priv;
	काष्ठा mt7615_dev *dev = phy->dev;
	काष्ठा अणु
		काष्ठा req_hdr अणु
			u8 omac_idx;
			u8 band_idx;
			__le16 tlv_num;
			u8 is_tlv_append;
			u8 rsv[3];
		पूर्ण __packed hdr;
		काष्ठा req_tlv अणु
			__le16 tag;
			__le16 len;
			u8 active;
			u8 band_idx;
			u8 omac_addr[ETH_ALEN];
		पूर्ण __packed tlv;
	पूर्ण data = अणु
		.hdr = अणु
			.omac_idx = mvअगर->mt76.omac_idx,
			.band_idx = mvअगर->mt76.band_idx,
			.tlv_num = cpu_to_le16(1),
			.is_tlv_append = 1,
		पूर्ण,
		.tlv = अणु
			.tag = cpu_to_le16(DEV_INFO_ACTIVE),
			.len = cpu_to_le16(माप(काष्ठा req_tlv)),
			.active = enable,
			.band_idx = mvअगर->mt76.band_idx,
		पूर्ण,
	पूर्ण;

	अगर (mvअगर->mt76.omac_idx >= REPEATER_BSSID_START)
		वापस mt7615_mcu_muar_config(dev, vअगर, false, enable);

	स_नकल(data.tlv.omac_addr, vअगर->addr, ETH_ALEN);
	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD_DEV_INFO_UPDATE,
				 &data, माप(data), true);
पूर्ण

अटल पूर्णांक
mt7615_mcu_add_beacon_offload(काष्ठा mt7615_dev *dev,
			      काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर, bool enable)
अणु
	काष्ठा mt7615_vअगर *mvअगर = (काष्ठा mt7615_vअगर *)vअगर->drv_priv;
	काष्ठा mt76_wcid *wcid = &dev->mt76.global_wcid;
	काष्ठा ieee80211_mutable_offsets offs;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा req अणु
		u8 omac_idx;
		u8 enable;
		u8 wlan_idx;
		u8 band_idx;
		u8 pkt_type;
		u8 need_pre_tbtt_पूर्णांक;
		__le16 csa_ie_pos;
		__le16 pkt_len;
		__le16 tim_ie_pos;
		u8 pkt[512];
		u8 csa_cnt;
		/* bss color change */
		u8 bcc_cnt;
		__le16 bcc_ie_pos;
	पूर्ण __packed req = अणु
		.omac_idx = mvअगर->mt76.omac_idx,
		.enable = enable,
		.wlan_idx = wcid->idx,
		.band_idx = mvअगर->mt76.band_idx,
	पूर्ण;
	काष्ठा sk_buff *skb;

	अगर (!enable)
		जाओ out;

	skb = ieee80211_beacon_get_ढाँचा(hw, vअगर, &offs);
	अगर (!skb)
		वापस -EINVAL;

	अगर (skb->len > 512 - MT_TXD_SIZE) अणु
		dev_err(dev->mt76.dev, "Bcn size limit exceed\n");
		dev_kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	अगर (mvअगर->mt76.band_idx) अणु
		info = IEEE80211_SKB_CB(skb);
		info->hw_queue |= MT_TX_HW_QUEUE_EXT_PHY;
	पूर्ण

	mt7615_mac_ग_लिखो_txwi(dev, (__le32 *)(req.pkt), skb, wcid, शून्य,
			      0, शून्य, true);
	स_नकल(req.pkt + MT_TXD_SIZE, skb->data, skb->len);
	req.pkt_len = cpu_to_le16(MT_TXD_SIZE + skb->len);
	req.tim_ie_pos = cpu_to_le16(MT_TXD_SIZE + offs.tim_offset);
	अगर (offs.cntdwn_counter_offs[0]) अणु
		u16 csa_offs;

		csa_offs = MT_TXD_SIZE + offs.cntdwn_counter_offs[0] - 4;
		req.csa_ie_pos = cpu_to_le16(csa_offs);
		req.csa_cnt = skb->data[offs.cntdwn_counter_offs[0]];
	पूर्ण
	dev_kमुक्त_skb(skb);

out:
	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD_BCN_OFFLOAD, &req,
				 माप(req), true);
पूर्ण

अटल पूर्णांक
mt7615_mcu_ctrl_pm_state(काष्ठा mt7615_dev *dev, पूर्णांक band, पूर्णांक state)
अणु
#घोषणा ENTER_PM_STATE	1
#घोषणा EXIT_PM_STATE	2
	काष्ठा अणु
		u8 pm_number;
		u8 pm_state;
		u8 bssid[ETH_ALEN];
		u8 dtim_period;
		u8 wlan_idx;
		__le16 bcn_पूर्णांकerval;
		__le32 aid;
		__le32 rx_filter;
		u8 band_idx;
		u8 rsv[3];
		__le32 feature;
		u8 omac_idx;
		u8 wmm_idx;
		u8 bcn_loss_cnt;
		u8 bcn_sp_duration;
	पूर्ण __packed req = अणु
		.pm_number = 5,
		.pm_state = state ? ENTER_PM_STATE : EXIT_PM_STATE,
		.band_idx = band,
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD_PM_STATE_CTRL, &req,
				 माप(req), true);
पूर्ण

अटल पूर्णांक
mt7615_mcu_bss_basic_tlv(काष्ठा sk_buff *skb, काष्ठा ieee80211_vअगर *vअगर,
			 काष्ठा ieee80211_sta *sta, bool enable)
अणु
	काष्ठा mt7615_vअगर *mvअगर = (काष्ठा mt7615_vअगर *)vअगर->drv_priv;
	u32 type = vअगर->p2p ? NETWORK_P2P : NETWORK_INFRA;
	काष्ठा bss_info_basic *bss;
	u8 wlan_idx = mvअगर->sta.wcid.idx;
	काष्ठा tlv *tlv;

	tlv = mt76_connac_mcu_add_tlv(skb, BSS_INFO_BASIC, माप(*bss));

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_MESH_POINT:
	हाल NL80211_IFTYPE_AP:
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		/* TODO: enable BSS_INFO_UAPSD & BSS_INFO_PM */
		अगर (enable && sta) अणु
			काष्ठा mt7615_sta *msta;

			msta = (काष्ठा mt7615_sta *)sta->drv_priv;
			wlan_idx = msta->wcid.idx;
		पूर्ण
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		type = NETWORK_IBSS;
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण

	bss = (काष्ठा bss_info_basic *)tlv;
	स_नकल(bss->bssid, vअगर->bss_conf.bssid, ETH_ALEN);
	bss->bcn_पूर्णांकerval = cpu_to_le16(vअगर->bss_conf.beacon_पूर्णांक);
	bss->network_type = cpu_to_le32(type);
	bss->dtim_period = vअगर->bss_conf.dtim_period;
	bss->bmc_tx_wlan_idx = wlan_idx;
	bss->wmm_idx = mvअगर->mt76.wmm_idx;
	bss->active = enable;

	वापस 0;
पूर्ण

अटल व्योम
mt7615_mcu_bss_omac_tlv(काष्ठा sk_buff *skb, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt7615_vअगर *mvअगर = (काष्ठा mt7615_vअगर *)vअगर->drv_priv;
	u8 omac_idx = mvअगर->mt76.omac_idx;
	काष्ठा bss_info_omac *omac;
	काष्ठा tlv *tlv;
	u32 type = 0;

	tlv = mt76_connac_mcu_add_tlv(skb, BSS_INFO_OMAC, माप(*omac));

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_MESH_POINT:
	हाल NL80211_IFTYPE_AP:
		अगर (vअगर->p2p)
			type = CONNECTION_P2P_GO;
		अन्यथा
			type = CONNECTION_INFRA_AP;
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		अगर (vअगर->p2p)
			type = CONNECTION_P2P_GC;
		अन्यथा
			type = CONNECTION_INFRA_STA;
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		type = CONNECTION_IBSS_ADHOC;
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण

	omac = (काष्ठा bss_info_omac *)tlv;
	omac->conn_type = cpu_to_le32(type);
	omac->omac_idx = mvअगर->mt76.omac_idx;
	omac->band_idx = mvअगर->mt76.band_idx;
	omac->hw_bss_idx = omac_idx > EXT_BSSID_START ? HW_BSSID_0 : omac_idx;
पूर्ण

/* SIFS 20us + 512 byte beacon tranmitted by 1Mbps (3906us) */
#घोषणा BCN_TX_ESTIMATE_TIME (4096 + 20)
अटल व्योम
mt7615_mcu_bss_ext_tlv(काष्ठा sk_buff *skb, काष्ठा mt7615_vअगर *mvअगर)
अणु
	काष्ठा bss_info_ext_bss *ext;
	पूर्णांक ext_bss_idx, tsf_offset;
	काष्ठा tlv *tlv;

	ext_bss_idx = mvअगर->mt76.omac_idx - EXT_BSSID_START;
	अगर (ext_bss_idx < 0)
		वापस;

	tlv = mt76_connac_mcu_add_tlv(skb, BSS_INFO_EXT_BSS, माप(*ext));

	ext = (काष्ठा bss_info_ext_bss *)tlv;
	tsf_offset = ext_bss_idx * BCN_TX_ESTIMATE_TIME;
	ext->mbss_tsf_offset = cpu_to_le32(tsf_offset);
पूर्ण

अटल पूर्णांक
mt7615_mcu_add_bss(काष्ठा mt7615_phy *phy, काष्ठा ieee80211_vअगर *vअगर,
		   काष्ठा ieee80211_sta *sta, bool enable)
अणु
	काष्ठा mt7615_vअगर *mvअगर = (काष्ठा mt7615_vअगर *)vअगर->drv_priv;
	काष्ठा mt7615_dev *dev = phy->dev;
	काष्ठा sk_buff *skb;

	अगर (mvअगर->mt76.omac_idx >= REPEATER_BSSID_START)
		mt7615_mcu_muar_config(dev, vअगर, true, enable);

	skb = mt76_connac_mcu_alloc_sta_req(&dev->mt76, &mvअगर->mt76, शून्य);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	अगर (enable)
		mt7615_mcu_bss_omac_tlv(skb, vअगर);

	mt7615_mcu_bss_basic_tlv(skb, vअगर, sta, enable);

	अगर (enable && mvअगर->mt76.omac_idx >= EXT_BSSID_START &&
	    mvअगर->mt76.omac_idx < REPEATER_BSSID_START)
		mt7615_mcu_bss_ext_tlv(skb, mvअगर);

	वापस mt76_mcu_skb_send_msg(&dev->mt76, skb,
				     MCU_EXT_CMD_BSS_INFO_UPDATE, true);
पूर्ण

अटल पूर्णांक
mt7615_mcu_wtbl_tx_ba(काष्ठा mt7615_dev *dev,
		      काष्ठा ieee80211_ampdu_params *params,
		      bool enable)
अणु
	काष्ठा mt7615_sta *msta = (काष्ठा mt7615_sta *)params->sta->drv_priv;
	काष्ठा mt7615_vअगर *mvअगर = msta->vअगर;
	काष्ठा wtbl_req_hdr *wtbl_hdr;
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक err;

	wtbl_hdr = mt76_connac_mcu_alloc_wtbl_req(&dev->mt76, &msta->wcid,
						  WTBL_SET, शून्य, &skb);
	अगर (IS_ERR(wtbl_hdr))
		वापस PTR_ERR(wtbl_hdr);

	mt76_connac_mcu_wtbl_ba_tlv(&dev->mt76, skb, params, enable, true,
				    शून्य, wtbl_hdr);

	err = mt76_mcu_skb_send_msg(&dev->mt76, skb, MCU_EXT_CMD_WTBL_UPDATE,
				    true);
	अगर (err < 0)
		वापस err;

	skb = mt76_connac_mcu_alloc_sta_req(&dev->mt76, &mvअगर->mt76,
					    &msta->wcid);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	mt76_connac_mcu_sta_ba_tlv(skb, params, enable, true);

	वापस mt76_mcu_skb_send_msg(&dev->mt76, skb,
				     MCU_EXT_CMD_STA_REC_UPDATE, true);
पूर्ण

अटल पूर्णांक
mt7615_mcu_wtbl_rx_ba(काष्ठा mt7615_dev *dev,
		      काष्ठा ieee80211_ampdu_params *params,
		      bool enable)
अणु
	काष्ठा mt7615_sta *msta = (काष्ठा mt7615_sta *)params->sta->drv_priv;
	काष्ठा mt7615_vअगर *mvअगर = msta->vअगर;
	काष्ठा wtbl_req_hdr *wtbl_hdr;
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	skb = mt76_connac_mcu_alloc_sta_req(&dev->mt76, &mvअगर->mt76,
					    &msta->wcid);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	mt76_connac_mcu_sta_ba_tlv(skb, params, enable, false);

	err = mt76_mcu_skb_send_msg(&dev->mt76, skb,
				    MCU_EXT_CMD_STA_REC_UPDATE, true);
	अगर (err < 0 || !enable)
		वापस err;

	skb = शून्य;
	wtbl_hdr = mt76_connac_mcu_alloc_wtbl_req(&dev->mt76, &msta->wcid,
						  WTBL_SET, शून्य, &skb);
	अगर (IS_ERR(wtbl_hdr))
		वापस PTR_ERR(wtbl_hdr);

	mt76_connac_mcu_wtbl_ba_tlv(&dev->mt76, skb, params, enable, false,
				    शून्य, wtbl_hdr);

	वापस mt76_mcu_skb_send_msg(&dev->mt76, skb, MCU_EXT_CMD_WTBL_UPDATE,
				     true);
पूर्ण

अटल पूर्णांक
mt7615_mcu_wtbl_sta_add(काष्ठा mt7615_phy *phy, काष्ठा ieee80211_vअगर *vअगर,
			काष्ठा ieee80211_sta *sta, bool enable)
अणु
	काष्ठा mt7615_vअगर *mvअगर = (काष्ठा mt7615_vअगर *)vअगर->drv_priv;
	काष्ठा sk_buff *skb, *sskb, *wskb = शून्य;
	काष्ठा mt7615_dev *dev = phy->dev;
	काष्ठा wtbl_req_hdr *wtbl_hdr;
	काष्ठा mt7615_sta *msta;
	पूर्णांक cmd, err;

	msta = sta ? (काष्ठा mt7615_sta *)sta->drv_priv : &mvअगर->sta;

	sskb = mt76_connac_mcu_alloc_sta_req(&dev->mt76, &mvअगर->mt76,
					     &msta->wcid);
	अगर (IS_ERR(sskb))
		वापस PTR_ERR(sskb);

	mt76_connac_mcu_sta_basic_tlv(sskb, vअगर, sta, enable);
	अगर (enable && sta)
		mt76_connac_mcu_sta_tlv(phy->mt76, sskb, sta, vअगर, 0);

	wtbl_hdr = mt76_connac_mcu_alloc_wtbl_req(&dev->mt76, &msta->wcid,
						  WTBL_RESET_AND_SET, शून्य,
						  &wskb);
	अगर (IS_ERR(wtbl_hdr))
		वापस PTR_ERR(wtbl_hdr);

	अगर (enable) अणु
		mt76_connac_mcu_wtbl_generic_tlv(&dev->mt76, wskb, vअगर, sta,
						 शून्य, wtbl_hdr);
		अगर (sta)
			mt76_connac_mcu_wtbl_ht_tlv(&dev->mt76, wskb, sta,
						    शून्य, wtbl_hdr);
		mt76_connac_mcu_wtbl_hdr_trans_tlv(wskb, &msta->wcid, शून्य,
						   wtbl_hdr);
	पूर्ण

	cmd = enable ? MCU_EXT_CMD_WTBL_UPDATE : MCU_EXT_CMD_STA_REC_UPDATE;
	skb = enable ? wskb : sskb;

	err = mt76_mcu_skb_send_msg(&dev->mt76, skb, cmd, true);
	अगर (err < 0) अणु
		skb = enable ? sskb : wskb;
		dev_kमुक्त_skb(skb);

		वापस err;
	पूर्ण

	cmd = enable ? MCU_EXT_CMD_STA_REC_UPDATE : MCU_EXT_CMD_WTBL_UPDATE;
	skb = enable ? sskb : wskb;

	वापस mt76_mcu_skb_send_msg(&dev->mt76, skb, cmd, true);
पूर्ण

अटल स्थिर काष्ठा mt7615_mcu_ops wtbl_update_ops = अणु
	.add_beacon_offload = mt7615_mcu_add_beacon_offload,
	.set_pm_state = mt7615_mcu_ctrl_pm_state,
	.add_dev_info = mt7615_mcu_add_dev,
	.add_bss_info = mt7615_mcu_add_bss,
	.add_tx_ba = mt7615_mcu_wtbl_tx_ba,
	.add_rx_ba = mt7615_mcu_wtbl_rx_ba,
	.sta_add = mt7615_mcu_wtbl_sta_add,
	.set_drv_ctrl = mt7615_mcu_drv_pmctrl,
	.set_fw_ctrl = mt7615_mcu_fw_pmctrl,
पूर्ण;

अटल पूर्णांक
mt7615_mcu_sta_ba(काष्ठा mt7615_dev *dev,
		  काष्ठा ieee80211_ampdu_params *params,
		  bool enable, bool tx)
अणु
	काष्ठा mt7615_sta *msta = (काष्ठा mt7615_sta *)params->sta->drv_priv;
	काष्ठा mt7615_vअगर *mvअगर = msta->vअगर;
	काष्ठा wtbl_req_hdr *wtbl_hdr;
	काष्ठा tlv *sta_wtbl;
	काष्ठा sk_buff *skb;

	skb = mt76_connac_mcu_alloc_sta_req(&dev->mt76, &mvअगर->mt76,
					    &msta->wcid);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	mt76_connac_mcu_sta_ba_tlv(skb, params, enable, tx);

	sta_wtbl = mt76_connac_mcu_add_tlv(skb, STA_REC_WTBL, माप(काष्ठा tlv));

	wtbl_hdr = mt76_connac_mcu_alloc_wtbl_req(&dev->mt76, &msta->wcid,
						  WTBL_SET, sta_wtbl, &skb);
	अगर (IS_ERR(wtbl_hdr))
		वापस PTR_ERR(wtbl_hdr);

	mt76_connac_mcu_wtbl_ba_tlv(&dev->mt76, skb, params, enable, tx,
				    sta_wtbl, wtbl_hdr);

	वापस mt76_mcu_skb_send_msg(&dev->mt76, skb,
				     MCU_EXT_CMD_STA_REC_UPDATE, true);
पूर्ण

अटल पूर्णांक
mt7615_mcu_sta_tx_ba(काष्ठा mt7615_dev *dev,
		     काष्ठा ieee80211_ampdu_params *params,
		     bool enable)
अणु
	वापस mt7615_mcu_sta_ba(dev, params, enable, true);
पूर्ण

अटल पूर्णांक
mt7615_mcu_sta_rx_ba(काष्ठा mt7615_dev *dev,
		     काष्ठा ieee80211_ampdu_params *params,
		     bool enable)
अणु
	वापस mt7615_mcu_sta_ba(dev, params, enable, false);
पूर्ण

अटल पूर्णांक
__mt7615_mcu_add_sta(काष्ठा mt76_phy *phy, काष्ठा ieee80211_vअगर *vअगर,
		     काष्ठा ieee80211_sta *sta, bool enable, पूर्णांक cmd)
अणु
	काष्ठा mt7615_vअगर *mvअगर = (काष्ठा mt7615_vअगर *)vअगर->drv_priv;
	काष्ठा mt76_sta_cmd_info info = अणु
		.sta = sta,
		.vअगर = vअगर,
		.enable = enable,
		.cmd = cmd,
	पूर्ण;

	info.wcid = sta ? (काष्ठा mt76_wcid *)sta->drv_priv : &mvअगर->sta.wcid;
	वापस mt76_connac_mcu_add_sta_cmd(phy, &info);
पूर्ण

अटल पूर्णांक
mt7615_mcu_add_sta(काष्ठा mt7615_phy *phy, काष्ठा ieee80211_vअगर *vअगर,
		   काष्ठा ieee80211_sta *sta, bool enable)
अणु
	वापस __mt7615_mcu_add_sta(phy->mt76, vअगर, sta, enable,
				    MCU_EXT_CMD_STA_REC_UPDATE);
पूर्ण

अटल स्थिर काष्ठा mt7615_mcu_ops sta_update_ops = अणु
	.add_beacon_offload = mt7615_mcu_add_beacon_offload,
	.set_pm_state = mt7615_mcu_ctrl_pm_state,
	.add_dev_info = mt7615_mcu_add_dev,
	.add_bss_info = mt7615_mcu_add_bss,
	.add_tx_ba = mt7615_mcu_sta_tx_ba,
	.add_rx_ba = mt7615_mcu_sta_rx_ba,
	.sta_add = mt7615_mcu_add_sta,
	.set_drv_ctrl = mt7615_mcu_drv_pmctrl,
	.set_fw_ctrl = mt7615_mcu_fw_pmctrl,
पूर्ण;

पूर्णांक mt7615_mcu_sta_update_hdr_trans(काष्ठा mt7615_dev *dev,
				    काष्ठा ieee80211_vअगर *vअगर,
				    काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा mt7615_sta *msta = (काष्ठा mt7615_sta *)sta->drv_priv;
	काष्ठा wtbl_req_hdr *wtbl_hdr;
	काष्ठा sk_buff *skb = शून्य;

	wtbl_hdr = mt76_connac_mcu_alloc_wtbl_req(&dev->mt76, &msta->wcid,
						  WTBL_SET, शून्य, &skb);
	अगर (IS_ERR(wtbl_hdr))
		वापस PTR_ERR(wtbl_hdr);

	mt76_connac_mcu_wtbl_hdr_trans_tlv(skb, &msta->wcid, शून्य, wtbl_hdr);

	वापस mt76_mcu_skb_send_msg(&dev->mt76, skb, MCU_EXT_CMD_WTBL_UPDATE,
				     true);
पूर्ण

अटल पूर्णांक
mt7615_mcu_uni_ctrl_pm_state(काष्ठा mt7615_dev *dev, पूर्णांक band, पूर्णांक state)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक
mt7615_mcu_uni_add_beacon_offload(काष्ठा mt7615_dev *dev,
				  काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_vअगर *vअगर,
				  bool enable)
अणु
	काष्ठा mt7615_vअगर *mvअगर = (काष्ठा mt7615_vअगर *)vअगर->drv_priv;
	काष्ठा mt76_wcid *wcid = &dev->mt76.global_wcid;
	काष्ठा ieee80211_mutable_offsets offs;
	काष्ठा अणु
		काष्ठा req_hdr अणु
			u8 bss_idx;
			u8 pad[3];
		पूर्ण __packed hdr;
		काष्ठा bcn_content_tlv अणु
			__le16 tag;
			__le16 len;
			__le16 tim_ie_pos;
			__le16 csa_ie_pos;
			__le16 bcc_ie_pos;
			/* 0: disable beacon offload
			 * 1: enable beacon offload
			 * 2: update probe respond offload
			 */
			u8 enable;
			/* 0: legacy क्रमmat (TXD + payload)
			 * 1: only cap field IE
			 */
			u8 type;
			__le16 pkt_len;
			u8 pkt[512];
		पूर्ण __packed beacon_tlv;
	पूर्ण req = अणु
		.hdr = अणु
			.bss_idx = mvअगर->mt76.idx,
		पूर्ण,
		.beacon_tlv = अणु
			.tag = cpu_to_le16(UNI_BSS_INFO_BCN_CONTENT),
			.len = cpu_to_le16(माप(काष्ठा bcn_content_tlv)),
			.enable = enable,
		पूर्ण,
	पूर्ण;
	काष्ठा sk_buff *skb;

	अगर (!enable)
		जाओ out;

	skb = ieee80211_beacon_get_ढाँचा(mt76_hw(dev), vअगर, &offs);
	अगर (!skb)
		वापस -EINVAL;

	अगर (skb->len > 512 - MT_TXD_SIZE) अणु
		dev_err(dev->mt76.dev, "beacon size limit exceed\n");
		dev_kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	mt7615_mac_ग_लिखो_txwi(dev, (__le32 *)(req.beacon_tlv.pkt), skb,
			      wcid, शून्य, 0, शून्य, true);
	स_नकल(req.beacon_tlv.pkt + MT_TXD_SIZE, skb->data, skb->len);
	req.beacon_tlv.pkt_len = cpu_to_le16(MT_TXD_SIZE + skb->len);
	req.beacon_tlv.tim_ie_pos = cpu_to_le16(MT_TXD_SIZE + offs.tim_offset);

	अगर (offs.cntdwn_counter_offs[0]) अणु
		u16 csa_offs;

		csa_offs = MT_TXD_SIZE + offs.cntdwn_counter_offs[0] - 4;
		req.beacon_tlv.csa_ie_pos = cpu_to_le16(csa_offs);
	पूर्ण
	dev_kमुक्त_skb(skb);

out:
	वापस mt76_mcu_send_msg(&dev->mt76, MCU_UNI_CMD_BSS_INFO_UPDATE,
				 &req, माप(req), true);
पूर्ण

अटल पूर्णांक
mt7615_mcu_uni_add_dev(काष्ठा mt7615_phy *phy, काष्ठा ieee80211_vअगर *vअगर,
		       bool enable)
अणु
	काष्ठा mt7615_vअगर *mvअगर = (काष्ठा mt7615_vअगर *)vअगर->drv_priv;

	वापस mt76_connac_mcu_uni_add_dev(phy->mt76, vअगर, &mvअगर->sta.wcid,
					   enable);
पूर्ण

अटल पूर्णांक
mt7615_mcu_uni_add_bss(काष्ठा mt7615_phy *phy, काष्ठा ieee80211_vअगर *vअगर,
		       काष्ठा ieee80211_sta *sta, bool enable)
अणु
	काष्ठा mt7615_vअगर *mvअगर = (काष्ठा mt7615_vअगर *)vअगर->drv_priv;

	वापस mt76_connac_mcu_uni_add_bss(phy->mt76, vअगर, &mvअगर->sta.wcid,
					   enable);
पूर्ण

अटल अंतरभूत पूर्णांक
mt7615_mcu_uni_add_sta(काष्ठा mt7615_phy *phy, काष्ठा ieee80211_vअगर *vअगर,
		       काष्ठा ieee80211_sta *sta, bool enable)
अणु
	वापस __mt7615_mcu_add_sta(phy->mt76, vअगर, sta, enable,
				    MCU_UNI_CMD_STA_REC_UPDATE);
पूर्ण

अटल पूर्णांक
mt7615_mcu_uni_tx_ba(काष्ठा mt7615_dev *dev,
		     काष्ठा ieee80211_ampdu_params *params,
		     bool enable)
अणु
	काष्ठा mt7615_sta *sta = (काष्ठा mt7615_sta *)params->sta->drv_priv;

	वापस mt76_connac_mcu_sta_ba(&dev->mt76, &sta->vअगर->mt76, params,
				      enable, true);
पूर्ण

अटल पूर्णांक
mt7615_mcu_uni_rx_ba(काष्ठा mt7615_dev *dev,
		     काष्ठा ieee80211_ampdu_params *params,
		     bool enable)
अणु
	काष्ठा mt7615_sta *msta = (काष्ठा mt7615_sta *)params->sta->drv_priv;
	काष्ठा mt7615_vअगर *mvअगर = msta->vअगर;
	काष्ठा wtbl_req_hdr *wtbl_hdr;
	काष्ठा tlv *sta_wtbl;
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	skb = mt76_connac_mcu_alloc_sta_req(&dev->mt76, &mvअगर->mt76,
					    &msta->wcid);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	mt76_connac_mcu_sta_ba_tlv(skb, params, enable, false);

	err = mt76_mcu_skb_send_msg(&dev->mt76, skb,
				    MCU_UNI_CMD_STA_REC_UPDATE, true);
	अगर (err < 0 || !enable)
		वापस err;

	skb = mt76_connac_mcu_alloc_sta_req(&dev->mt76, &mvअगर->mt76,
					    &msta->wcid);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	sta_wtbl = mt76_connac_mcu_add_tlv(skb, STA_REC_WTBL,
					   माप(काष्ठा tlv));

	wtbl_hdr = mt76_connac_mcu_alloc_wtbl_req(&dev->mt76, &msta->wcid,
						  WTBL_SET, sta_wtbl, &skb);
	अगर (IS_ERR(wtbl_hdr))
		वापस PTR_ERR(wtbl_hdr);

	mt76_connac_mcu_wtbl_ba_tlv(&dev->mt76, skb, params, enable, false,
				    sta_wtbl, wtbl_hdr);

	वापस mt76_mcu_skb_send_msg(&dev->mt76, skb,
				     MCU_UNI_CMD_STA_REC_UPDATE, true);
पूर्ण

अटल स्थिर काष्ठा mt7615_mcu_ops uni_update_ops = अणु
	.add_beacon_offload = mt7615_mcu_uni_add_beacon_offload,
	.set_pm_state = mt7615_mcu_uni_ctrl_pm_state,
	.add_dev_info = mt7615_mcu_uni_add_dev,
	.add_bss_info = mt7615_mcu_uni_add_bss,
	.add_tx_ba = mt7615_mcu_uni_tx_ba,
	.add_rx_ba = mt7615_mcu_uni_rx_ba,
	.sta_add = mt7615_mcu_uni_add_sta,
	.set_drv_ctrl = mt7615_mcu_lp_drv_pmctrl,
	.set_fw_ctrl = mt7615_mcu_fw_pmctrl,
पूर्ण;

पूर्णांक mt7615_mcu_restart(काष्ठा mt76_dev *dev)
अणु
	वापस mt76_mcu_send_msg(dev, MCU_CMD_RESTART_DL_REQ, शून्य, 0, true);
पूर्ण
EXPORT_SYMBOL_GPL(mt7615_mcu_restart);

अटल पूर्णांक mt7615_load_patch(काष्ठा mt7615_dev *dev, u32 addr, स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा mt7615_patch_hdr *hdr;
	स्थिर काष्ठा firmware *fw = शून्य;
	पूर्णांक len, ret, sem;

	ret = firmware_request_nowarn(&fw, name, dev->mt76.dev);
	अगर (ret)
		वापस ret;

	अगर (!fw || !fw->data || fw->size < माप(*hdr)) अणु
		dev_err(dev->mt76.dev, "Invalid firmware\n");
		ret = -EINVAL;
		जाओ release_fw;
	पूर्ण

	sem = mt76_connac_mcu_patch_sem_ctrl(&dev->mt76, true);
	चयन (sem) अणु
	हाल PATCH_IS_DL:
		जाओ release_fw;
	हाल PATCH_NOT_DL_SEM_SUCCESS:
		अवरोध;
	शेष:
		dev_err(dev->mt76.dev, "Failed to get patch semaphore\n");
		ret = -EAGAIN;
		जाओ release_fw;
	पूर्ण

	hdr = (स्थिर काष्ठा mt7615_patch_hdr *)(fw->data);

	dev_info(dev->mt76.dev, "HW/SW Version: 0x%x, Build Time: %.16s\n",
		 be32_to_cpu(hdr->hw_sw_ver), hdr->build_date);

	len = fw->size - माप(*hdr);

	ret = mt76_connac_mcu_init_करोwnload(&dev->mt76, addr, len,
					    DL_MODE_NEED_RSP);
	अगर (ret) अणु
		dev_err(dev->mt76.dev, "Download request failed\n");
		जाओ out;
	पूर्ण

	ret = mt76_mcu_send_firmware(&dev->mt76, MCU_CMD_FW_SCATTER,
				     fw->data + माप(*hdr), len);
	अगर (ret) अणु
		dev_err(dev->mt76.dev, "Failed to send firmware to device\n");
		जाओ out;
	पूर्ण

	ret = mt76_connac_mcu_start_patch(&dev->mt76);
	अगर (ret)
		dev_err(dev->mt76.dev, "Failed to start patch\n");

out:
	sem = mt76_connac_mcu_patch_sem_ctrl(&dev->mt76, false);
	चयन (sem) अणु
	हाल PATCH_REL_SEM_SUCCESS:
		अवरोध;
	शेष:
		ret = -EAGAIN;
		dev_err(dev->mt76.dev, "Failed to release patch semaphore\n");
		अवरोध;
	पूर्ण

release_fw:
	release_firmware(fw);

	वापस ret;
पूर्ण

अटल u32 mt7615_mcu_gen_dl_mode(u8 feature_set, bool is_cr4)
अणु
	u32 ret = 0;

	ret |= (feature_set & FW_FEATURE_SET_ENCRYPT) ?
	       (DL_MODE_ENCRYPT | DL_MODE_RESET_SEC_IV) : 0;
	ret |= FIELD_PREP(DL_MODE_KEY_IDX,
			  FIELD_GET(FW_FEATURE_SET_KEY_IDX, feature_set));
	ret |= DL_MODE_NEED_RSP;
	ret |= is_cr4 ? DL_MODE_WORKING_PDA_CR4 : 0;

	वापस ret;
पूर्ण

अटल पूर्णांक
mt7615_mcu_send_ram_firmware(काष्ठा mt7615_dev *dev,
			     स्थिर काष्ठा mt7615_fw_trailer *hdr,
			     स्थिर u8 *data, bool is_cr4)
अणु
	पूर्णांक n_region = is_cr4 ? CR4_REGION_NUM : N9_REGION_NUM;
	पूर्णांक err, i, offset = 0;
	u32 len, addr, mode;

	क्रम (i = 0; i < n_region; i++) अणु
		mode = mt7615_mcu_gen_dl_mode(hdr[i].feature_set, is_cr4);
		len = le32_to_cpu(hdr[i].len) + IMG_CRC_LEN;
		addr = le32_to_cpu(hdr[i].addr);

		err = mt76_connac_mcu_init_करोwnload(&dev->mt76, addr, len,
						    mode);
		अगर (err) अणु
			dev_err(dev->mt76.dev, "Download request failed\n");
			वापस err;
		पूर्ण

		err = mt76_mcu_send_firmware(&dev->mt76, MCU_CMD_FW_SCATTER,
					     data + offset, len);
		अगर (err) अणु
			dev_err(dev->mt76.dev, "Failed to send firmware to device\n");
			वापस err;
		पूर्ण

		offset += len;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt7615_load_n9(काष्ठा mt7615_dev *dev, स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा mt7615_fw_trailer *hdr;
	स्थिर काष्ठा firmware *fw;
	पूर्णांक ret;

	ret = request_firmware(&fw, name, dev->mt76.dev);
	अगर (ret)
		वापस ret;

	अगर (!fw || !fw->data || fw->size < N9_REGION_NUM * माप(*hdr)) अणु
		dev_err(dev->mt76.dev, "Invalid firmware\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	hdr = (स्थिर काष्ठा mt7615_fw_trailer *)(fw->data + fw->size -
					N9_REGION_NUM * माप(*hdr));

	dev_info(dev->mt76.dev, "N9 Firmware Version: %.10s, Build Time: %.15s\n",
		 hdr->fw_ver, hdr->build_date);

	ret = mt7615_mcu_send_ram_firmware(dev, hdr, fw->data, false);
	अगर (ret)
		जाओ out;

	ret = mt76_connac_mcu_start_firmware(&dev->mt76,
					     le32_to_cpu(hdr->addr),
					     FW_START_OVERRIDE);
	अगर (ret) अणु
		dev_err(dev->mt76.dev, "Failed to start N9 firmware\n");
		जाओ out;
	पूर्ण

	snम_लिखो(dev->mt76.hw->wiphy->fw_version,
		 माप(dev->mt76.hw->wiphy->fw_version),
		 "%.10s-%.15s", hdr->fw_ver, hdr->build_date);

	अगर (!is_mt7615(&dev->mt76)) अणु
		dev->fw_ver = MT7615_FIRMWARE_V2;
		dev->mcu_ops = &sta_update_ops;
	पूर्ण अन्यथा अणु
		dev->fw_ver = MT7615_FIRMWARE_V1;
		dev->mcu_ops = &wtbl_update_ops;
	पूर्ण

out:
	release_firmware(fw);
	वापस ret;
पूर्ण

अटल पूर्णांक mt7615_load_cr4(काष्ठा mt7615_dev *dev, स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा mt7615_fw_trailer *hdr;
	स्थिर काष्ठा firmware *fw;
	पूर्णांक ret;

	ret = request_firmware(&fw, name, dev->mt76.dev);
	अगर (ret)
		वापस ret;

	अगर (!fw || !fw->data || fw->size < CR4_REGION_NUM * माप(*hdr)) अणु
		dev_err(dev->mt76.dev, "Invalid firmware\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	hdr = (स्थिर काष्ठा mt7615_fw_trailer *)(fw->data + fw->size -
					CR4_REGION_NUM * माप(*hdr));

	dev_info(dev->mt76.dev, "CR4 Firmware Version: %.10s, Build Time: %.15s\n",
		 hdr->fw_ver, hdr->build_date);

	ret = mt7615_mcu_send_ram_firmware(dev, hdr, fw->data, true);
	अगर (ret)
		जाओ out;

	ret = mt76_connac_mcu_start_firmware(&dev->mt76, 0,
					     FW_START_WORKING_PDA_CR4);
	अगर (ret) अणु
		dev_err(dev->mt76.dev, "Failed to start CR4 firmware\n");
		जाओ out;
	पूर्ण

out:
	release_firmware(fw);

	वापस ret;
पूर्ण

अटल पूर्णांक mt7615_load_ram(काष्ठा mt7615_dev *dev)
अणु
	पूर्णांक ret;

	ret = mt7615_load_n9(dev, MT7615_FIRMWARE_N9);
	अगर (ret)
		वापस ret;

	वापस mt7615_load_cr4(dev, MT7615_FIRMWARE_CR4);
पूर्ण

अटल पूर्णांक mt7615_load_firmware(काष्ठा mt7615_dev *dev)
अणु
	पूर्णांक ret;
	u32 val;

	val = mt76_get_field(dev, MT_TOP_MISC2, MT_TOP_MISC2_FW_STATE);

	अगर (val != FW_STATE_FW_DOWNLOAD) अणु
		dev_err(dev->mt76.dev, "Firmware is not ready for download\n");
		वापस -EIO;
	पूर्ण

	ret = mt7615_load_patch(dev, MT7615_PATCH_ADDRESS, MT7615_ROM_PATCH);
	अगर (ret)
		वापस ret;

	ret = mt7615_load_ram(dev);
	अगर (ret)
		वापस ret;

	अगर (!mt76_poll_msec(dev, MT_TOP_MISC2, MT_TOP_MISC2_FW_STATE,
			    FIELD_PREP(MT_TOP_MISC2_FW_STATE,
				       FW_STATE_CR4_RDY), 500)) अणु
		dev_err(dev->mt76.dev, "Timeout for initializing firmware\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt7622_load_firmware(काष्ठा mt7615_dev *dev)
अणु
	पूर्णांक ret;
	u32 val;

	mt76_set(dev, MT_WPDMA_GLO_CFG, MT_WPDMA_GLO_CFG_BYPASS_TX_SCH);

	val = mt76_get_field(dev, MT_TOP_OFF_RSV, MT_TOP_OFF_RSV_FW_STATE);
	अगर (val != FW_STATE_FW_DOWNLOAD) अणु
		dev_err(dev->mt76.dev, "Firmware is not ready for download\n");
		वापस -EIO;
	पूर्ण

	ret = mt7615_load_patch(dev, MT7622_PATCH_ADDRESS, MT7622_ROM_PATCH);
	अगर (ret)
		वापस ret;

	ret = mt7615_load_n9(dev, MT7622_FIRMWARE_N9);
	अगर (ret)
		वापस ret;

	अगर (!mt76_poll_msec(dev, MT_TOP_OFF_RSV, MT_TOP_OFF_RSV_FW_STATE,
			    FIELD_PREP(MT_TOP_OFF_RSV_FW_STATE,
				       FW_STATE_NORMAL_TRX), 1500)) अणु
		dev_err(dev->mt76.dev, "Timeout for initializing firmware\n");
		वापस -EIO;
	पूर्ण

	mt76_clear(dev, MT_WPDMA_GLO_CFG, MT_WPDMA_GLO_CFG_BYPASS_TX_SCH);

	वापस 0;
पूर्ण

पूर्णांक mt7615_mcu_fw_log_2_host(काष्ठा mt7615_dev *dev, u8 ctrl)
अणु
	काष्ठा अणु
		u8 ctrl_val;
		u8 pad[3];
	पूर्ण data = अणु
		.ctrl_val = ctrl
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD_FW_LOG_2_HOST, &data,
				 माप(data), true);
पूर्ण

अटल पूर्णांक mt7663_load_n9(काष्ठा mt7615_dev *dev, स्थिर अक्षर *name)
अणु
	u32 offset = 0, override_addr = 0, flag = FW_START_DLYCAL;
	स्थिर काष्ठा mt7663_fw_trailer *hdr;
	स्थिर काष्ठा mt7663_fw_buf *buf;
	स्थिर काष्ठा firmware *fw;
	स्थिर u8 *base_addr;
	पूर्णांक i, ret;

	ret = request_firmware(&fw, name, dev->mt76.dev);
	अगर (ret)
		वापस ret;

	अगर (!fw || !fw->data || fw->size < FW_V3_COMMON_TAILER_SIZE) अणु
		dev_err(dev->mt76.dev, "Invalid firmware\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	hdr = (स्थिर काष्ठा mt7663_fw_trailer *)(fw->data + fw->size -
						 FW_V3_COMMON_TAILER_SIZE);

	dev_info(dev->mt76.dev, "N9 Firmware Version: %.10s, Build Time: %.15s\n",
		 hdr->fw_ver, hdr->build_date);
	dev_info(dev->mt76.dev, "Region number: 0x%x\n", hdr->n_region);

	base_addr = fw->data + fw->size - FW_V3_COMMON_TAILER_SIZE;
	क्रम (i = 0; i < hdr->n_region; i++) अणु
		u32 shअगरt = (hdr->n_region - i) * FW_V3_REGION_TAILER_SIZE;
		u32 len, addr, mode;

		dev_info(dev->mt76.dev, "Parsing tailer Region: %d\n", i);

		buf = (स्थिर काष्ठा mt7663_fw_buf *)(base_addr - shअगरt);
		mode = mt7615_mcu_gen_dl_mode(buf->feature_set, false);
		addr = le32_to_cpu(buf->img_dest_addr);
		len = le32_to_cpu(buf->img_size);

		ret = mt76_connac_mcu_init_करोwnload(&dev->mt76, addr, len,
						    mode);
		अगर (ret) अणु
			dev_err(dev->mt76.dev, "Download request failed\n");
			जाओ out;
		पूर्ण

		ret = mt76_mcu_send_firmware(&dev->mt76, MCU_CMD_FW_SCATTER,
					     fw->data + offset, len);
		अगर (ret) अणु
			dev_err(dev->mt76.dev, "Failed to send firmware\n");
			जाओ out;
		पूर्ण

		offset += le32_to_cpu(buf->img_size);
		अगर (buf->feature_set & DL_MODE_VALID_RAM_ENTRY) अणु
			override_addr = le32_to_cpu(buf->img_dest_addr);
			dev_info(dev->mt76.dev, "Region %d, override_addr = 0x%08x\n",
				 i, override_addr);
		पूर्ण
	पूर्ण

	अगर (override_addr)
		flag |= FW_START_OVERRIDE;

	dev_info(dev->mt76.dev, "override_addr = 0x%08x, option = %d\n",
		 override_addr, flag);

	ret = mt76_connac_mcu_start_firmware(&dev->mt76, override_addr, flag);
	अगर (ret) अणु
		dev_err(dev->mt76.dev, "Failed to start N9 firmware\n");
		जाओ out;
	पूर्ण

	snम_लिखो(dev->mt76.hw->wiphy->fw_version,
		 माप(dev->mt76.hw->wiphy->fw_version),
		 "%.10s-%.15s", hdr->fw_ver, hdr->build_date);

out:
	release_firmware(fw);

	वापस ret;
पूर्ण

अटल पूर्णांक
mt7663_load_rom_patch(काष्ठा mt7615_dev *dev, स्थिर अक्षर **n9_firmware)
अणु
	स्थिर अक्षर *selected_rom, *secondary_rom = MT7663_ROM_PATCH;
	स्थिर अक्षर *primary_rom = MT7663_OFFLOAD_ROM_PATCH;
	पूर्णांक ret;

	अगर (!prefer_offload_fw) अणु
		secondary_rom = MT7663_OFFLOAD_ROM_PATCH;
		primary_rom = MT7663_ROM_PATCH;
	पूर्ण
	selected_rom = primary_rom;

	ret = mt7615_load_patch(dev, MT7663_PATCH_ADDRESS, primary_rom);
	अगर (ret) अणु
		dev_info(dev->mt76.dev, "%s not found, switching to %s",
			 primary_rom, secondary_rom);
		ret = mt7615_load_patch(dev, MT7663_PATCH_ADDRESS,
					secondary_rom);
		अगर (ret) अणु
			dev_err(dev->mt76.dev, "failed to load %s",
				secondary_rom);
			वापस ret;
		पूर्ण
		selected_rom = secondary_rom;
	पूर्ण

	अगर (!म_भेद(selected_rom, MT7663_OFFLOAD_ROM_PATCH)) अणु
		*n9_firmware = MT7663_OFFLOAD_FIRMWARE_N9;
		dev->fw_ver = MT7615_FIRMWARE_V3;
		dev->mcu_ops = &uni_update_ops;
	पूर्ण अन्यथा अणु
		*n9_firmware = MT7663_FIRMWARE_N9;
		dev->fw_ver = MT7615_FIRMWARE_V2;
		dev->mcu_ops = &sta_update_ops;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक __mt7663_load_firmware(काष्ठा mt7615_dev *dev)
अणु
	स्थिर अक्षर *n9_firmware;
	पूर्णांक ret;

	ret = mt76_get_field(dev, MT_CONN_ON_MISC, MT_TOP_MISC2_FW_N9_RDY);
	अगर (ret) अणु
		dev_dbg(dev->mt76.dev, "Firmware is already download\n");
		वापस -EIO;
	पूर्ण

	ret = mt7663_load_rom_patch(dev, &n9_firmware);
	अगर (ret)
		वापस ret;

	ret = mt7663_load_n9(dev, n9_firmware);
	अगर (ret)
		वापस ret;

	अगर (!mt76_poll_msec(dev, MT_CONN_ON_MISC, MT_TOP_MISC2_FW_N9_RDY,
			    MT_TOP_MISC2_FW_N9_RDY, 1500)) अणु
		ret = mt76_get_field(dev, MT_CONN_ON_MISC,
				     MT7663_TOP_MISC2_FW_STATE);
		dev_err(dev->mt76.dev, "Timeout for initializing firmware\n");
		वापस -EIO;
	पूर्ण

#अगर_घोषित CONFIG_PM
	अगर (mt7615_firmware_offload(dev))
		dev->mt76.hw->wiphy->wowlan = &mt76_connac_wowlan_support;
#पूर्ण_अगर /* CONFIG_PM */

	dev_dbg(dev->mt76.dev, "Firmware init done\n");

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__mt7663_load_firmware);

अटल पूर्णांक mt7663_load_firmware(काष्ठा mt7615_dev *dev)
अणु
	पूर्णांक ret;

	mt76_set(dev, MT_WPDMA_GLO_CFG, MT_WPDMA_GLO_CFG_BYPASS_TX_SCH);

	ret = __mt7663_load_firmware(dev);
	अगर (ret)
		वापस ret;

	mt76_clear(dev, MT_WPDMA_GLO_CFG, MT_WPDMA_GLO_CFG_BYPASS_TX_SCH);

	वापस 0;
पूर्ण

पूर्णांक mt7615_mcu_init(काष्ठा mt7615_dev *dev)
अणु
	अटल स्थिर काष्ठा mt76_mcu_ops mt7615_mcu_ops = अणु
		.headroom = माप(काष्ठा mt7615_mcu_txd),
		.mcu_skb_send_msg = mt7615_mcu_send_message,
		.mcu_parse_response = mt7615_mcu_parse_response,
		.mcu_restart = mt7615_mcu_restart,
	पूर्ण;
	पूर्णांक ret;

	dev->mt76.mcu_ops = &mt7615_mcu_ops,

	ret = mt7615_mcu_drv_pmctrl(dev);
	अगर (ret)
		वापस ret;

	चयन (mt76_chip(&dev->mt76)) अणु
	हाल 0x7622:
		ret = mt7622_load_firmware(dev);
		अवरोध;
	हाल 0x7663:
		ret = mt7663_load_firmware(dev);
		अवरोध;
	शेष:
		ret = mt7615_load_firmware(dev);
		अवरोध;
	पूर्ण
	अगर (ret)
		वापस ret;

	mt76_queue_tx_cleanup(dev, dev->mt76.q_mcu[MT_MCUQ_FWDL], false);
	dev_dbg(dev->mt76.dev, "Firmware init done\n");
	set_bit(MT76_STATE_MCU_RUNNING, &dev->mphy.state);
	mt7615_mcu_fw_log_2_host(dev, 0);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt7615_mcu_init);

व्योम mt7615_mcu_निकास(काष्ठा mt7615_dev *dev)
अणु
	__mt76_mcu_restart(&dev->mt76);
	mt7615_mcu_set_fw_ctrl(dev);
	skb_queue_purge(&dev->mt76.mcu.res_q);
पूर्ण
EXPORT_SYMBOL_GPL(mt7615_mcu_निकास);

पूर्णांक mt7615_mcu_set_eeprom(काष्ठा mt7615_dev *dev)
अणु
	काष्ठा अणु
		u8 buffer_mode;
		u8 content_क्रमmat;
		__le16 len;
	पूर्ण __packed req_hdr = अणु
		.buffer_mode = 1,
	पूर्ण;
	u8 *eep = (u8 *)dev->mt76.eeprom.data;
	काष्ठा sk_buff *skb;
	पूर्णांक eep_len, offset;

	चयन (mt76_chip(&dev->mt76)) अणु
	हाल 0x7622:
		eep_len = MT7622_EE_MAX - MT_EE_NIC_CONF_0;
		offset = MT_EE_NIC_CONF_0;
		अवरोध;
	हाल 0x7663:
		eep_len = MT7663_EE_MAX - MT_EE_CHIP_ID;
		req_hdr.content_क्रमmat = 1;
		offset = MT_EE_CHIP_ID;
		अवरोध;
	शेष:
		eep_len = MT7615_EE_MAX - MT_EE_NIC_CONF_0;
		offset = MT_EE_NIC_CONF_0;
		अवरोध;
	पूर्ण

	req_hdr.len = cpu_to_le16(eep_len);

	skb = mt76_mcu_msg_alloc(&dev->mt76, शून्य, माप(req_hdr) + eep_len);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put_data(skb, &req_hdr, माप(req_hdr));
	skb_put_data(skb, eep + offset, eep_len);

	वापस mt76_mcu_skb_send_msg(&dev->mt76, skb,
				     MCU_EXT_CMD_EFUSE_BUFFER_MODE, true);
पूर्ण

पूर्णांक mt7615_mcu_set_wmm(काष्ठा mt7615_dev *dev, u8 queue,
		       स्थिर काष्ठा ieee80211_tx_queue_params *params)
अणु
#घोषणा WMM_AIFS_SET	BIT(0)
#घोषणा WMM_CW_MIN_SET	BIT(1)
#घोषणा WMM_CW_MAX_SET	BIT(2)
#घोषणा WMM_TXOP_SET	BIT(3)
#घोषणा WMM_PARAM_SET	(WMM_AIFS_SET | WMM_CW_MIN_SET | \
			 WMM_CW_MAX_SET | WMM_TXOP_SET)
	काष्ठा req_data अणु
		u8 number;
		u8 rsv[3];
		u8 queue;
		u8 valid;
		u8 aअगरs;
		u8 cw_min;
		__le16 cw_max;
		__le16 txop;
	पूर्ण __packed req = अणु
		.number = 1,
		.queue = queue,
		.valid = WMM_PARAM_SET,
		.aअगरs = params->aअगरs,
		.cw_min = 5,
		.cw_max = cpu_to_le16(10),
		.txop = cpu_to_le16(params->txop),
	पूर्ण;

	अगर (params->cw_min)
		req.cw_min = fls(params->cw_min);
	अगर (params->cw_max)
		req.cw_max = cpu_to_le16(fls(params->cw_max));

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD_EDCA_UPDATE, &req,
				 माप(req), true);
पूर्ण

पूर्णांक mt7615_mcu_set_dbdc(काष्ठा mt7615_dev *dev)
अणु
	काष्ठा mt7615_phy *ext_phy = mt7615_ext_phy(dev);
	काष्ठा dbdc_entry अणु
		u8 type;
		u8 index;
		u8 band;
		u8 _rsv;
	पूर्ण;
	काष्ठा अणु
		u8 enable;
		u8 num;
		u8 _rsv[2];
		काष्ठा dbdc_entry entry[64];
	पूर्ण req = अणु
		.enable = !!ext_phy,
	पूर्ण;
	पूर्णांक i;

	अगर (!ext_phy)
		जाओ out;

#घोषणा ADD_DBDC_ENTRY(_type, _idx, _band)		\
	करो अणु \
		req.entry[req.num].type = _type;		\
		req.entry[req.num].index = _idx;		\
		req.entry[req.num++].band = _band;		\
	पूर्ण जबतक (0)

	क्रम (i = 0; i < 4; i++) अणु
		bool band = !!(ext_phy->omac_mask & BIT_ULL(i));

		ADD_DBDC_ENTRY(DBDC_TYPE_BSS, i, band);
	पूर्ण

	क्रम (i = 0; i < 14; i++) अणु
		bool band = !!(ext_phy->omac_mask & BIT_ULL(0x11 + i));

		ADD_DBDC_ENTRY(DBDC_TYPE_MBSS, i, band);
	पूर्ण

	ADD_DBDC_ENTRY(DBDC_TYPE_MU, 0, 1);

	क्रम (i = 0; i < 3; i++)
		ADD_DBDC_ENTRY(DBDC_TYPE_BF, i, 1);

	ADD_DBDC_ENTRY(DBDC_TYPE_WMM, 0, 0);
	ADD_DBDC_ENTRY(DBDC_TYPE_WMM, 1, 0);
	ADD_DBDC_ENTRY(DBDC_TYPE_WMM, 2, 1);
	ADD_DBDC_ENTRY(DBDC_TYPE_WMM, 3, 1);

	ADD_DBDC_ENTRY(DBDC_TYPE_MGMT, 0, 0);
	ADD_DBDC_ENTRY(DBDC_TYPE_MGMT, 1, 1);

out:
	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD_DBDC_CTRL, &req,
				 माप(req), true);
पूर्ण

पूर्णांक mt7615_mcu_del_wtbl_all(काष्ठा mt7615_dev *dev)
अणु
	काष्ठा wtbl_req_hdr req = अणु
		.operation = WTBL_RESET_ALL,
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD_WTBL_UPDATE, &req,
				 माप(req), true);
पूर्ण

पूर्णांक mt7615_mcu_rdd_cmd(काष्ठा mt7615_dev *dev,
		       क्रमागत mt7615_rdd_cmd cmd, u8 index,
		       u8 rx_sel, u8 val)
अणु
	काष्ठा अणु
		u8 ctrl;
		u8 rdd_idx;
		u8 rdd_rx_sel;
		u8 val;
		u8 rsv[4];
	पूर्ण req = अणु
		.ctrl = cmd,
		.rdd_idx = index,
		.rdd_rx_sel = rx_sel,
		.val = val,
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD_SET_RDD_CTRL, &req,
				 माप(req), true);
पूर्ण

पूर्णांक mt7615_mcu_set_fcc5_lpn(काष्ठा mt7615_dev *dev, पूर्णांक val)
अणु
	काष्ठा अणु
		__le16 tag;
		__le16 min_lpn;
	पूर्ण req = अणु
		.tag = cpu_to_le16(0x1),
		.min_lpn = cpu_to_le16(val),
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD_SET_RDD_TH, &req,
				 माप(req), true);
पूर्ण

पूर्णांक mt7615_mcu_set_pulse_th(काष्ठा mt7615_dev *dev,
			    स्थिर काष्ठा mt7615_dfs_pulse *pulse)
अणु
	काष्ठा अणु
		__le16 tag;
		__le32 max_width;	/* us */
		__le32 max_pwr;		/* dbm */
		__le32 min_pwr;		/* dbm */
		__le32 min_stgr_pri;	/* us */
		__le32 max_stgr_pri;	/* us */
		__le32 min_cr_pri;	/* us */
		__le32 max_cr_pri;	/* us */
	पूर्ण req = अणु
		.tag = cpu_to_le16(0x3),
#घोषणा __req_field(field) .field = cpu_to_le32(pulse->field)
		__req_field(max_width),
		__req_field(max_pwr),
		__req_field(min_pwr),
		__req_field(min_stgr_pri),
		__req_field(max_stgr_pri),
		__req_field(min_cr_pri),
		__req_field(max_cr_pri),
#अघोषित  __req_field
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD_SET_RDD_TH, &req,
				 माप(req), true);
पूर्ण

पूर्णांक mt7615_mcu_set_radar_th(काष्ठा mt7615_dev *dev, पूर्णांक index,
			    स्थिर काष्ठा mt7615_dfs_pattern *pattern)
अणु
	काष्ठा अणु
		__le16 tag;
		__le16 radar_type;
		u8 enb;
		u8 stgr;
		u8 min_crpn;
		u8 max_crpn;
		u8 min_crpr;
		u8 min_pw;
		u8 max_pw;
		__le32 min_pri;
		__le32 max_pri;
		u8 min_crbn;
		u8 max_crbn;
		u8 min_stgpn;
		u8 max_stgpn;
		u8 min_stgpr;
	पूर्ण req = अणु
		.tag = cpu_to_le16(0x2),
		.radar_type = cpu_to_le16(index),
#घोषणा __req_field_u8(field) .field = pattern->field
#घोषणा __req_field_u32(field) .field = cpu_to_le32(pattern->field)
		__req_field_u8(enb),
		__req_field_u8(stgr),
		__req_field_u8(min_crpn),
		__req_field_u8(max_crpn),
		__req_field_u8(min_crpr),
		__req_field_u8(min_pw),
		__req_field_u8(max_pw),
		__req_field_u32(min_pri),
		__req_field_u32(max_pri),
		__req_field_u8(min_crbn),
		__req_field_u8(max_crbn),
		__req_field_u8(min_stgpn),
		__req_field_u8(max_stgpn),
		__req_field_u8(min_stgpr),
#अघोषित __req_field_u8
#अघोषित __req_field_u32
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD_SET_RDD_TH, &req,
				 माप(req), true);
पूर्ण

पूर्णांक mt7615_mcu_rdd_send_pattern(काष्ठा mt7615_dev *dev)
अणु
	काष्ठा अणु
		u8 pulse_num;
		u8 rsv[3];
		काष्ठा अणु
			__le32 start_समय;
			__le16 width;
			__le16 घातer;
		पूर्ण pattern[32];
	पूर्ण req = अणु
		.pulse_num = dev->radar_pattern.n_pulses,
	पूर्ण;
	u32 start_समय = kसमय_प्रकारo_ms(kसमय_get_bootसमय());
	पूर्णांक i;

	अगर (dev->radar_pattern.n_pulses > ARRAY_SIZE(req.pattern))
		वापस -EINVAL;

	/* TODO: add some noise here */
	क्रम (i = 0; i < dev->radar_pattern.n_pulses; i++) अणु
		u32 ts = start_समय + i * dev->radar_pattern.period;

		req.pattern[i].width = cpu_to_le16(dev->radar_pattern.width);
		req.pattern[i].घातer = cpu_to_le16(dev->radar_pattern.घातer);
		req.pattern[i].start_समय = cpu_to_le32(ts);
	पूर्ण

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD_SET_RDD_PATTERN,
				 &req, माप(req), false);
पूर्ण

अटल व्योम mt7615_mcu_set_txघातer_sku(काष्ठा mt7615_phy *phy, u8 *sku)
अणु
	काष्ठा mt76_phy *mphy = phy->mt76;
	काष्ठा ieee80211_hw *hw = mphy->hw;
	काष्ठा mt76_घातer_limits limits;
	s8 *limits_array = (s8 *)&limits;
	पूर्णांक n_chains = hweight8(mphy->antenna_mask);
	पूर्णांक tx_घातer;
	पूर्णांक i;
	अटल स्थिर u8 sku_mapping[] = अणु
#घोषणा SKU_FIELD(_type, _field) \
		[MT_SKU_##_type] = दुरत्व(काष्ठा mt76_घातer_limits, _field)
		SKU_FIELD(CCK_1_2, cck[0]),
		SKU_FIELD(CCK_55_11, cck[2]),
		SKU_FIELD(OFDM_6_9, ofdm[0]),
		SKU_FIELD(OFDM_12_18, ofdm[2]),
		SKU_FIELD(OFDM_24_36, ofdm[4]),
		SKU_FIELD(OFDM_48, ofdm[6]),
		SKU_FIELD(OFDM_54, ofdm[7]),
		SKU_FIELD(HT20_0_8, mcs[0][0]),
		SKU_FIELD(HT20_32, ofdm[0]),
		SKU_FIELD(HT20_1_2_9_10, mcs[0][1]),
		SKU_FIELD(HT20_3_4_11_12, mcs[0][3]),
		SKU_FIELD(HT20_5_13, mcs[0][5]),
		SKU_FIELD(HT20_6_14, mcs[0][6]),
		SKU_FIELD(HT20_7_15, mcs[0][7]),
		SKU_FIELD(HT40_0_8, mcs[1][0]),
		SKU_FIELD(HT40_32, ofdm[0]),
		SKU_FIELD(HT40_1_2_9_10, mcs[1][1]),
		SKU_FIELD(HT40_3_4_11_12, mcs[1][3]),
		SKU_FIELD(HT40_5_13, mcs[1][5]),
		SKU_FIELD(HT40_6_14, mcs[1][6]),
		SKU_FIELD(HT40_7_15, mcs[1][7]),
		SKU_FIELD(VHT20_0, mcs[0][0]),
		SKU_FIELD(VHT20_1_2, mcs[0][1]),
		SKU_FIELD(VHT20_3_4, mcs[0][3]),
		SKU_FIELD(VHT20_5_6, mcs[0][5]),
		SKU_FIELD(VHT20_7, mcs[0][7]),
		SKU_FIELD(VHT20_8, mcs[0][8]),
		SKU_FIELD(VHT20_9, mcs[0][9]),
		SKU_FIELD(VHT40_0, mcs[1][0]),
		SKU_FIELD(VHT40_1_2, mcs[1][1]),
		SKU_FIELD(VHT40_3_4, mcs[1][3]),
		SKU_FIELD(VHT40_5_6, mcs[1][5]),
		SKU_FIELD(VHT40_7, mcs[1][7]),
		SKU_FIELD(VHT40_8, mcs[1][8]),
		SKU_FIELD(VHT40_9, mcs[1][9]),
		SKU_FIELD(VHT80_0, mcs[2][0]),
		SKU_FIELD(VHT80_1_2, mcs[2][1]),
		SKU_FIELD(VHT80_3_4, mcs[2][3]),
		SKU_FIELD(VHT80_5_6, mcs[2][5]),
		SKU_FIELD(VHT80_7, mcs[2][7]),
		SKU_FIELD(VHT80_8, mcs[2][8]),
		SKU_FIELD(VHT80_9, mcs[2][9]),
		SKU_FIELD(VHT160_0, mcs[3][0]),
		SKU_FIELD(VHT160_1_2, mcs[3][1]),
		SKU_FIELD(VHT160_3_4, mcs[3][3]),
		SKU_FIELD(VHT160_5_6, mcs[3][5]),
		SKU_FIELD(VHT160_7, mcs[3][7]),
		SKU_FIELD(VHT160_8, mcs[3][8]),
		SKU_FIELD(VHT160_9, mcs[3][9]),
#अघोषित SKU_FIELD
	पूर्ण;

	tx_घातer = hw->conf.घातer_level * 2 -
		   mt76_tx_घातer_nss_delta(n_chains);

	tx_घातer = mt76_get_rate_घातer_limits(mphy, mphy->chandef.chan,
					      &limits, tx_घातer);
	mphy->txघातer_cur = tx_घातer;

	अगर (is_mt7663(mphy->dev)) अणु
		स_रखो(sku, tx_घातer, MT_SKU_4SS_DELTA + 1);
		वापस;
	पूर्ण

	क्रम (i = 0; i < MT_SKU_1SS_DELTA; i++)
		sku[i] = limits_array[sku_mapping[i]];

	क्रम (i = 0; i < 4; i++) अणु
		पूर्णांक delta = 0;

		अगर (i < n_chains - 1)
			delta = mt76_tx_घातer_nss_delta(n_chains) -
				mt76_tx_घातer_nss_delta(i + 1);
		sku[MT_SKU_1SS_DELTA + i] = delta;
	पूर्ण
पूर्ण

अटल u8 mt7615_mcu_chan_bw(काष्ठा cfg80211_chan_def *chandef)
अणु
	अटल स्थिर u8 width_to_bw[] = अणु
		[NL80211_CHAN_WIDTH_40] = CMD_CBW_40MHZ,
		[NL80211_CHAN_WIDTH_80] = CMD_CBW_80MHZ,
		[NL80211_CHAN_WIDTH_80P80] = CMD_CBW_8080MHZ,
		[NL80211_CHAN_WIDTH_160] = CMD_CBW_160MHZ,
		[NL80211_CHAN_WIDTH_5] = CMD_CBW_5MHZ,
		[NL80211_CHAN_WIDTH_10] = CMD_CBW_10MHZ,
		[NL80211_CHAN_WIDTH_20] = CMD_CBW_20MHZ,
		[NL80211_CHAN_WIDTH_20_NOHT] = CMD_CBW_20MHZ,
	पूर्ण;

	अगर (chandef->width >= ARRAY_SIZE(width_to_bw))
		वापस 0;

	वापस width_to_bw[chandef->width];
पूर्ण

पूर्णांक mt7615_mcu_set_chan_info(काष्ठा mt7615_phy *phy, पूर्णांक cmd)
अणु
	काष्ठा mt7615_dev *dev = phy->dev;
	काष्ठा cfg80211_chan_def *chandef = &phy->mt76->chandef;
	पूर्णांक freq1 = chandef->center_freq1, freq2 = chandef->center_freq2;
	काष्ठा अणु
		u8 control_chan;
		u8 center_chan;
		u8 bw;
		u8 tx_streams;
		u8 rx_streams_mask;
		u8 चयन_reason;
		u8 band_idx;
		/* क्रम 80+80 only */
		u8 center_chan2;
		__le16 cac_हाल;
		u8 channel_band;
		u8 rsv0;
		__le32 outband_freq;
		u8 txघातer_drop;
		u8 rsv1[3];
		u8 txघातer_sku[53];
		u8 rsv2[3];
	पूर्ण req = अणु
		.control_chan = chandef->chan->hw_value,
		.center_chan = ieee80211_frequency_to_channel(freq1),
		.tx_streams = hweight8(phy->mt76->antenna_mask),
		.rx_streams_mask = phy->mt76->chainmask,
		.center_chan2 = ieee80211_frequency_to_channel(freq2),
	पूर्ण;

	अगर (phy->mt76->hw->conf.flags & IEEE80211_CONF_OFFCHANNEL)
		req.चयन_reason = CH_SWITCH_SCAN_BYPASS_DPD;
	अन्यथा अगर ((chandef->chan->flags & IEEE80211_CHAN_RADAR) &&
		 chandef->chan->dfs_state != NL80211_DFS_AVAILABLE)
		req.चयन_reason = CH_SWITCH_DFS;
	अन्यथा
		req.चयन_reason = CH_SWITCH_NORMAL;

	req.band_idx = phy != &dev->phy;
	req.bw = mt7615_mcu_chan_bw(chandef);

	अगर (mt76_tesपंचांगode_enabled(phy->mt76))
		स_रखो(req.txघातer_sku, 0x3f, 49);
	अन्यथा
		mt7615_mcu_set_txघातer_sku(phy, req.txघातer_sku);

	वापस mt76_mcu_send_msg(&dev->mt76, cmd, &req, माप(req), true);
पूर्ण

पूर्णांक mt7615_mcu_get_temperature(काष्ठा mt7615_dev *dev, पूर्णांक index)
अणु
	काष्ठा अणु
		u8 action;
		u8 rsv[3];
	पूर्ण req = अणु
		.action = index,
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD_GET_TEMP, &req,
				 माप(req), true);
पूर्ण

पूर्णांक mt7615_mcu_set_test_param(काष्ठा mt7615_dev *dev, u8 param, bool test_mode,
			      u32 val)
अणु
	काष्ठा अणु
		u8 test_mode_en;
		u8 param_idx;
		u8 _rsv[2];

		__le32 value;

		u8 pad[8];
	पूर्ण req = अणु
		.test_mode_en = test_mode,
		.param_idx = param,
		.value = cpu_to_le32(val),
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD_ATE_CTRL, &req,
				 माप(req), false);
पूर्ण

पूर्णांक mt7615_mcu_set_sku_en(काष्ठा mt7615_phy *phy, bool enable)
अणु
	काष्ठा mt7615_dev *dev = phy->dev;
	काष्ठा अणु
		u8 क्रमmat_id;
		u8 sku_enable;
		u8 band_idx;
		u8 rsv;
	पूर्ण req = अणु
		.क्रमmat_id = 0,
		.band_idx = phy != &dev->phy,
		.sku_enable = enable,
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76,
				 MCU_EXT_CMD_TX_POWER_FEATURE_CTRL, &req,
				 माप(req), true);
पूर्ण

अटल पूर्णांक mt7615_find_freq_idx(स्थिर u16 *freqs, पूर्णांक n_freqs, u16 cur)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < n_freqs; i++)
		अगर (cur == freqs[i])
			वापस i;

	वापस -1;
पूर्ण

अटल पूर्णांक mt7615_dcoc_freq_idx(u16 freq, u8 bw)
अणु
	अटल स्थिर u16 freq_list[] = अणु
		4980, 5805, 5905, 5190,
		5230, 5270, 5310, 5350,
		5390, 5430, 5470, 5510,
		5550, 5590, 5630, 5670,
		5710, 5755, 5795, 5835,
		5875, 5210, 5290, 5370,
		5450, 5530, 5610, 5690,
		5775, 5855
	पूर्ण;
	अटल स्थिर u16 freq_bw40[] = अणु
		5190, 5230, 5270, 5310,
		5350, 5390, 5430, 5470,
		5510, 5550, 5590, 5630,
		5670, 5710, 5755, 5795,
		5835, 5875
	पूर्ण;
	पूर्णांक offset_2g = ARRAY_SIZE(freq_list);
	पूर्णांक idx;

	अगर (freq < 4000) अणु
		अगर (freq < 2427)
			वापस offset_2g;
		अगर (freq < 2442)
			वापस offset_2g + 1;
		अगर (freq < 2457)
			वापस offset_2g + 2;

		वापस offset_2g + 3;
	पूर्ण

	चयन (bw) अणु
	हाल NL80211_CHAN_WIDTH_80:
	हाल NL80211_CHAN_WIDTH_80P80:
	हाल NL80211_CHAN_WIDTH_160:
		अवरोध;
	शेष:
		idx = mt7615_find_freq_idx(freq_bw40, ARRAY_SIZE(freq_bw40),
					   freq + 10);
		अगर (idx >= 0) अणु
			freq = freq_bw40[idx];
			अवरोध;
		पूर्ण

		idx = mt7615_find_freq_idx(freq_bw40, ARRAY_SIZE(freq_bw40),
					   freq - 10);
		अगर (idx >= 0) अणु
			freq = freq_bw40[idx];
			अवरोध;
		पूर्ण
		fallthrough;
	हाल NL80211_CHAN_WIDTH_40:
		idx = mt7615_find_freq_idx(freq_bw40, ARRAY_SIZE(freq_bw40),
					   freq);
		अगर (idx >= 0)
			अवरोध;

		वापस -1;

	पूर्ण

	वापस mt7615_find_freq_idx(freq_list, ARRAY_SIZE(freq_list), freq);
पूर्ण

पूर्णांक mt7615_mcu_apply_rx_dcoc(काष्ठा mt7615_phy *phy)
अणु
	काष्ठा mt7615_dev *dev = phy->dev;
	काष्ठा cfg80211_chan_def *chandef = &phy->mt76->chandef;
	पूर्णांक freq2 = chandef->center_freq2;
	पूर्णांक ret;
	काष्ठा अणु
		u8 direction;
		u8 runसमय_calibration;
		u8 _rsv[2];

		__le16 center_freq;
		u8 bw;
		u8 band;
		u8 is_freq2;
		u8 success;
		u8 dbdc_en;

		u8 _rsv2;

		काष्ठा अणु
			__le32 sx0_i_lna[4];
			__le32 sx0_q_lna[4];

			__le32 sx2_i_lna[4];
			__le32 sx2_q_lna[4];
		पूर्ण dcoc_data[4];
	पूर्ण req = अणु
		.direction = 1,

		.bw = mt7615_mcu_chan_bw(chandef),
		.band = chandef->center_freq1 > 4000,
		.dbdc_en = !!dev->mt76.phy2,
	पूर्ण;
	u16 center_freq = chandef->center_freq1;
	पूर्णांक freq_idx;
	u8 *eep = dev->mt76.eeprom.data;

	अगर (!(eep[MT_EE_CALDATA_FLASH] & MT_EE_CALDATA_FLASH_RX_CAL))
		वापस 0;

	अगर (chandef->width == NL80211_CHAN_WIDTH_160) अणु
		freq2 = center_freq + 40;
		center_freq -= 40;
	पूर्ण

again:
	req.runसमय_calibration = 1;
	freq_idx = mt7615_dcoc_freq_idx(center_freq, chandef->width);
	अगर (freq_idx < 0)
		जाओ out;

	स_नकल(req.dcoc_data, eep + MT7615_EEPROM_DCOC_OFFSET +
			      freq_idx * MT7615_EEPROM_DCOC_SIZE,
	       माप(req.dcoc_data));
	req.runसमय_calibration = 0;

out:
	req.center_freq = cpu_to_le16(center_freq);
	ret = mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD_RXDCOC_CAL, &req,
				माप(req), true);

	अगर ((chandef->width == NL80211_CHAN_WIDTH_80P80 ||
	     chandef->width == NL80211_CHAN_WIDTH_160) && !req.is_freq2) अणु
		req.is_freq2 = true;
		center_freq = freq2;
		जाओ again;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mt7615_dpd_freq_idx(u16 freq, u8 bw)
अणु
	अटल स्थिर u16 freq_list[] = अणु
		4920, 4940, 4960, 4980,
		5040, 5060, 5080, 5180,
		5200, 5220, 5240, 5260,
		5280, 5300, 5320, 5340,
		5360, 5380, 5400, 5420,
		5440, 5460, 5480, 5500,
		5520, 5540, 5560, 5580,
		5600, 5620, 5640, 5660,
		5680, 5700, 5720, 5745,
		5765, 5785, 5805, 5825,
		5845, 5865, 5885, 5905
	पूर्ण;
	पूर्णांक offset_2g = ARRAY_SIZE(freq_list);
	पूर्णांक idx;

	अगर (freq < 4000) अणु
		अगर (freq < 2432)
			वापस offset_2g;
		अगर (freq < 2457)
			वापस offset_2g + 1;

		वापस offset_2g + 2;
	पूर्ण

	अगर (bw != NL80211_CHAN_WIDTH_20) अणु
		idx = mt7615_find_freq_idx(freq_list, ARRAY_SIZE(freq_list),
					   freq + 10);
		अगर (idx >= 0)
			वापस idx;

		idx = mt7615_find_freq_idx(freq_list, ARRAY_SIZE(freq_list),
					   freq - 10);
		अगर (idx >= 0)
			वापस idx;
	पूर्ण

	वापस mt7615_find_freq_idx(freq_list, ARRAY_SIZE(freq_list), freq);
पूर्ण


पूर्णांक mt7615_mcu_apply_tx_dpd(काष्ठा mt7615_phy *phy)
अणु
	काष्ठा mt7615_dev *dev = phy->dev;
	काष्ठा cfg80211_chan_def *chandef = &phy->mt76->chandef;
	पूर्णांक freq2 = chandef->center_freq2;
	पूर्णांक ret;
	काष्ठा अणु
		u8 direction;
		u8 runसमय_calibration;
		u8 _rsv[2];

		__le16 center_freq;
		u8 bw;
		u8 band;
		u8 is_freq2;
		u8 success;
		u8 dbdc_en;

		u8 _rsv2;

		काष्ठा अणु
			काष्ठा अणु
				u32 dpd_g0;
				u8 data[32];
			पूर्ण wf0, wf1;

			काष्ठा अणु
				u32 dpd_g0_prim;
				u32 dpd_g0_sec;
				u8 data_prim[32];
				u8 data_sec[32];
			पूर्ण wf2, wf3;
		पूर्ण dpd_data;
	पूर्ण req = अणु
		.direction = 1,

		.bw = mt7615_mcu_chan_bw(chandef),
		.band = chandef->center_freq1 > 4000,
		.dbdc_en = !!dev->mt76.phy2,
	पूर्ण;
	u16 center_freq = chandef->center_freq1;
	पूर्णांक freq_idx;
	u8 *eep = dev->mt76.eeprom.data;

	अगर (!(eep[MT_EE_CALDATA_FLASH] & MT_EE_CALDATA_FLASH_TX_DPD))
		वापस 0;

	अगर (chandef->width == NL80211_CHAN_WIDTH_160) अणु
		freq2 = center_freq + 40;
		center_freq -= 40;
	पूर्ण

again:
	req.runसमय_calibration = 1;
	freq_idx = mt7615_dpd_freq_idx(center_freq, chandef->width);
	अगर (freq_idx < 0)
		जाओ out;

	स_नकल(&req.dpd_data, eep + MT7615_EEPROM_TXDPD_OFFSET +
			      freq_idx * MT7615_EEPROM_TXDPD_SIZE,
	       माप(req.dpd_data));
	req.runसमय_calibration = 0;

out:
	req.center_freq = cpu_to_le16(center_freq);
	ret = mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD_TXDPD_CAL, &req,
				माप(req), true);

	अगर ((chandef->width == NL80211_CHAN_WIDTH_80P80 ||
	     chandef->width == NL80211_CHAN_WIDTH_160) && !req.is_freq2) अणु
		req.is_freq2 = true;
		center_freq = freq2;
		जाओ again;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक mt7615_mcu_set_rx_hdr_trans_blacklist(काष्ठा mt7615_dev *dev)
अणु
	काष्ठा अणु
		u8 operation;
		u8 count;
		u8 _rsv[2];
		u8 index;
		u8 enable;
		__le16 etype;
	पूर्ण req = अणु
		.operation = 1,
		.count = 1,
		.enable = 1,
		.etype = cpu_to_le16(ETH_P_PAE),
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD_RX_HDR_TRANS,
				 &req, माप(req), false);
पूर्ण

पूर्णांक mt7615_mcu_set_bss_pm(काष्ठा mt7615_dev *dev, काष्ठा ieee80211_vअगर *vअगर,
			  bool enable)
अणु
	काष्ठा mt7615_vअगर *mvअगर = (काष्ठा mt7615_vअगर *)vअगर->drv_priv;
	काष्ठा अणु
		u8 bss_idx;
		u8 dtim_period;
		__le16 aid;
		__le16 bcn_पूर्णांकerval;
		__le16 atim_winकरोw;
		u8 uapsd;
		u8 bmc_delivered_ac;
		u8 bmc_triggered_ac;
		u8 pad;
	पूर्ण req = अणु
		.bss_idx = mvअगर->mt76.idx,
		.aid = cpu_to_le16(vअगर->bss_conf.aid),
		.dtim_period = vअगर->bss_conf.dtim_period,
		.bcn_पूर्णांकerval = cpu_to_le16(vअगर->bss_conf.beacon_पूर्णांक),
	पूर्ण;
	काष्ठा अणु
		u8 bss_idx;
		u8 pad[3];
	पूर्ण req_hdr = अणु
		.bss_idx = mvअगर->mt76.idx,
	पूर्ण;
	पूर्णांक err;

	अगर (vअगर->type != NL80211_IFTYPE_STATION)
		वापस 0;

	err = mt76_mcu_send_msg(&dev->mt76, MCU_CMD_SET_BSS_ABORT, &req_hdr,
				माप(req_hdr), false);
	अगर (err < 0 || !enable)
		वापस err;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_CMD_SET_BSS_CONNECTED, &req,
				 माप(req), false);
पूर्ण

पूर्णांक mt7615_mcu_set_roc(काष्ठा mt7615_phy *phy, काष्ठा ieee80211_vअगर *vअगर,
		       काष्ठा ieee80211_channel *chan, पूर्णांक duration)
अणु
	काष्ठा mt7615_vअगर *mvअगर = (काष्ठा mt7615_vअगर *)vअगर->drv_priv;
	काष्ठा mt7615_dev *dev = phy->dev;
	काष्ठा mt7615_roc_tlv req = अणु
		.bss_idx = mvअगर->mt76.idx,
		.active = !chan,
		.max_पूर्णांकerval = cpu_to_le32(duration),
		.primary_chan = chan ? chan->hw_value : 0,
		.band = chan ? chan->band : 0,
		.req_type = 2,
	पूर्ण;

	phy->roc_grant = false;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_CMD_SET_ROC, &req,
				 माप(req), false);
पूर्ण

पूर्णांक mt7615_mcu_set_p2p_oppps(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा mt7615_vअगर *mvअगर = (काष्ठा mt7615_vअगर *)vअगर->drv_priv;
	पूर्णांक ct_winकरोw = vअगर->bss_conf.p2p_noa_attr.oppps_ctwinकरोw;
	काष्ठा mt7615_dev *dev = mt7615_hw_dev(hw);
	काष्ठा अणु
		__le32 ct_win;
		u8 bss_idx;
		u8 rsv[3];
	पूर्ण __packed req = अणु
		.ct_win = cpu_to_le32(ct_winकरोw),
		.bss_idx = mvअगर->mt76.idx,
	पूर्ण;

	अगर (!mt7615_firmware_offload(dev))
		वापस -ENOTSUPP;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_CMD_SET_P2P_OPPPS, &req,
				 माप(req), false);
पूर्ण

u32 mt7615_mcu_reg_rr(काष्ठा mt76_dev *dev, u32 offset)
अणु
	काष्ठा अणु
		__le32 addr;
		__le32 val;
	पूर्ण __packed req = अणु
		.addr = cpu_to_le32(offset),
	पूर्ण;

	वापस mt76_mcu_send_msg(dev, MCU_CMD_REG_READ, &req, माप(req),
				 true);
पूर्ण
EXPORT_SYMBOL_GPL(mt7615_mcu_reg_rr);

व्योम mt7615_mcu_reg_wr(काष्ठा mt76_dev *dev, u32 offset, u32 val)
अणु
	काष्ठा अणु
		__le32 addr;
		__le32 val;
	पूर्ण __packed req = अणु
		.addr = cpu_to_le32(offset),
		.val = cpu_to_le32(val),
	पूर्ण;

	mt76_mcu_send_msg(dev, MCU_CMD_REG_WRITE, &req, माप(req), false);
पूर्ण
EXPORT_SYMBOL_GPL(mt7615_mcu_reg_wr);
