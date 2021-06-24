<शैली गुरु>
// SPDX-License-Identअगरier: ISC

#समावेश <linux/firmware.h>
#समावेश "mt7603.h"
#समावेश "mcu.h"
#समावेश "eeprom.h"

#घोषणा MCU_SKB_RESERVE	8

काष्ठा mt7603_fw_trailer अणु
	अक्षर fw_ver[10];
	अक्षर build_date[15];
	__le32 dl_len;
पूर्ण __packed;

अटल पूर्णांक
mt7603_mcu_parse_response(काष्ठा mt76_dev *mdev, पूर्णांक cmd,
			  काष्ठा sk_buff *skb, पूर्णांक seq)
अणु
	काष्ठा mt7603_dev *dev = container_of(mdev, काष्ठा mt7603_dev, mt76);
	काष्ठा mt7603_mcu_rxd *rxd;

	अगर (!skb) अणु
		dev_err(mdev->dev, "MCU message %02x (seq %d) timed out\n",
			असल(cmd), seq);
		dev->mcu_hang = MT7603_WATCHDOG_TIMEOUT;
		वापस -ETIMEDOUT;
	पूर्ण

	rxd = (काष्ठा mt7603_mcu_rxd *)skb->data;
	अगर (seq != rxd->seq)
		वापस -EAGAIN;

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7603_mcu_skb_send_msg(काष्ठा mt76_dev *mdev, काष्ठा sk_buff *skb,
			पूर्णांक cmd, पूर्णांक *रुको_seq)
अणु
	काष्ठा mt7603_dev *dev = container_of(mdev, काष्ठा mt7603_dev, mt76);
	पूर्णांक hdrlen = dev->mcu_running ? माप(काष्ठा mt7603_mcu_txd) : 12;
	काष्ठा mt7603_mcu_txd *txd;
	u8 seq;

	mdev->mcu.समयout = 3 * HZ;

	seq = ++mdev->mcu.msg_seq & 0xf;
	अगर (!seq)
		seq = ++mdev->mcu.msg_seq & 0xf;

	txd = (काष्ठा mt7603_mcu_txd *)skb_push(skb, hdrlen);

	txd->len = cpu_to_le16(skb->len);
	अगर (cmd == -MCU_CMD_FW_SCATTER)
		txd->pq_id = cpu_to_le16(MCU_PORT_QUEUE_FW);
	अन्यथा
		txd->pq_id = cpu_to_le16(MCU_PORT_QUEUE);
	txd->pkt_type = MCU_PKT_ID;
	txd->seq = seq;

	अगर (cmd < 0) अणु
		txd->cid = -cmd;
		txd->set_query = MCU_Q_NA;
	पूर्ण अन्यथा अणु
		txd->cid = MCU_CMD_EXT_CID;
		txd->ext_cid = cmd;
		txd->set_query = MCU_Q_SET;
		txd->ext_cid_ack = 1;
	पूर्ण

	अगर (रुको_seq)
		*रुको_seq = seq;

	वापस mt76_tx_queue_skb_raw(dev, mdev->q_mcu[MT_MCUQ_WM], skb, 0);
पूर्ण

अटल पूर्णांक
mt7603_mcu_init_करोwnload(काष्ठा mt7603_dev *dev, u32 addr, u32 len)
अणु
	काष्ठा अणु
		__le32 addr;
		__le32 len;
		__le32 mode;
	पूर्ण req = अणु
		.addr = cpu_to_le32(addr),
		.len = cpu_to_le32(len),
		.mode = cpu_to_le32(BIT(31)),
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, -MCU_CMD_TARGET_ADDRESS_LEN_REQ,
				 &req, माप(req), true);
पूर्ण

अटल पूर्णांक
mt7603_mcu_start_firmware(काष्ठा mt7603_dev *dev, u32 addr)
अणु
	काष्ठा अणु
		__le32 override;
		__le32 addr;
	पूर्ण req = अणु
		.override = cpu_to_le32(addr ? 1 : 0),
		.addr = cpu_to_le32(addr),
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, -MCU_CMD_FW_START_REQ, &req,
				 माप(req), true);
पूर्ण

अटल पूर्णांक
mt7603_mcu_restart(काष्ठा mt76_dev *dev)
अणु
	वापस mt76_mcu_send_msg(dev, -MCU_CMD_RESTART_DL_REQ, शून्य, 0, true);
पूर्ण

अटल पूर्णांक mt7603_load_firmware(काष्ठा mt7603_dev *dev)
अणु
	स्थिर काष्ठा firmware *fw;
	स्थिर काष्ठा mt7603_fw_trailer *hdr;
	स्थिर अक्षर *firmware;
	पूर्णांक dl_len;
	u32 addr, val;
	पूर्णांक ret;

	अगर (is_mt7628(dev)) अणु
		अगर (mt76xx_rev(dev) == MT7628_REV_E1)
			firmware = MT7628_FIRMWARE_E1;
		अन्यथा
			firmware = MT7628_FIRMWARE_E2;
	पूर्ण अन्यथा अणु
		अगर (mt76xx_rev(dev) < MT7603_REV_E2)
			firmware = MT7603_FIRMWARE_E1;
		अन्यथा
			firmware = MT7603_FIRMWARE_E2;
	पूर्ण

	ret = request_firmware(&fw, firmware, dev->mt76.dev);
	अगर (ret)
		वापस ret;

	अगर (!fw || !fw->data || fw->size < माप(*hdr)) अणु
		dev_err(dev->mt76.dev, "Invalid firmware\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	hdr = (स्थिर काष्ठा mt7603_fw_trailer *)(fw->data + fw->size -
						 माप(*hdr));

	dev_info(dev->mt76.dev, "Firmware Version: %.10s\n", hdr->fw_ver);
	dev_info(dev->mt76.dev, "Build Time: %.15s\n", hdr->build_date);

	addr = mt7603_reg_map(dev, 0x50012498);
	mt76_wr(dev, addr, 0x5);
	mt76_wr(dev, addr, 0x5);
	udelay(1);

	/* चयन to bypass mode */
	mt76_rmw(dev, MT_SCH_4, MT_SCH_4_FORCE_QID,
		 MT_SCH_4_BYPASS | FIELD_PREP(MT_SCH_4_FORCE_QID, 5));

	val = mt76_rr(dev, MT_TOP_MISC2);
	अगर (val & BIT(1)) अणु
		dev_info(dev->mt76.dev, "Firmware already running...\n");
		जाओ running;
	पूर्ण

	अगर (!mt76_poll_msec(dev, MT_TOP_MISC2, BIT(0) | BIT(1), BIT(0), 500)) अणु
		dev_err(dev->mt76.dev, "Timeout waiting for ROM code to become ready\n");
		ret = -EIO;
		जाओ out;
	पूर्ण

	dl_len = le32_to_cpu(hdr->dl_len) + 4;
	ret = mt7603_mcu_init_करोwnload(dev, MCU_FIRMWARE_ADDRESS, dl_len);
	अगर (ret) अणु
		dev_err(dev->mt76.dev, "Download request failed\n");
		जाओ out;
	पूर्ण

	ret = mt76_mcu_send_firmware(&dev->mt76, -MCU_CMD_FW_SCATTER,
				     fw->data, dl_len);
	अगर (ret) अणु
		dev_err(dev->mt76.dev, "Failed to send firmware to device\n");
		जाओ out;
	पूर्ण

	ret = mt7603_mcu_start_firmware(dev, MCU_FIRMWARE_ADDRESS);
	अगर (ret) अणु
		dev_err(dev->mt76.dev, "Failed to start firmware\n");
		जाओ out;
	पूर्ण

	अगर (!mt76_poll_msec(dev, MT_TOP_MISC2, BIT(1), BIT(1), 500)) अणु
		dev_err(dev->mt76.dev, "Timeout waiting for firmware to initialize\n");
		ret = -EIO;
		जाओ out;
	पूर्ण

running:
	mt76_clear(dev, MT_SCH_4, MT_SCH_4_FORCE_QID | MT_SCH_4_BYPASS);

	mt76_set(dev, MT_SCH_4, BIT(8));
	mt76_clear(dev, MT_SCH_4, BIT(8));

	dev->mcu_running = true;
	snम_लिखो(dev->mt76.hw->wiphy->fw_version,
		 माप(dev->mt76.hw->wiphy->fw_version),
		 "%.10s-%.15s", hdr->fw_ver, hdr->build_date);
	dev_info(dev->mt76.dev, "firmware init done\n");

out:
	release_firmware(fw);

	वापस ret;
पूर्ण

पूर्णांक mt7603_mcu_init(काष्ठा mt7603_dev *dev)
अणु
	अटल स्थिर काष्ठा mt76_mcu_ops mt7603_mcu_ops = अणु
		.headroom = माप(काष्ठा mt7603_mcu_txd),
		.mcu_skb_send_msg = mt7603_mcu_skb_send_msg,
		.mcu_parse_response = mt7603_mcu_parse_response,
		.mcu_restart = mt7603_mcu_restart,
	पूर्ण;

	dev->mt76.mcu_ops = &mt7603_mcu_ops;
	वापस mt7603_load_firmware(dev);
पूर्ण

व्योम mt7603_mcu_निकास(काष्ठा mt7603_dev *dev)
अणु
	__mt76_mcu_restart(&dev->mt76);
	skb_queue_purge(&dev->mt76.mcu.res_q);
पूर्ण

पूर्णांक mt7603_mcu_set_eeprom(काष्ठा mt7603_dev *dev)
अणु
	अटल स्थिर u16 req_fields[] = अणु
#घोषणा WORD(_start)			\
		_start,			\
		_start + 1
#घोषणा GROUP_2G(_start)		\
		WORD(_start),		\
		WORD(_start + 2),	\
		WORD(_start + 4)

		MT_EE_NIC_CONF_0 + 1,
		WORD(MT_EE_NIC_CONF_1),
		MT_EE_WIFI_RF_SETTING,
		MT_EE_TX_POWER_DELTA_BW40,
		MT_EE_TX_POWER_DELTA_BW80 + 1,
		MT_EE_TX_POWER_EXT_PA_5G,
		MT_EE_TEMP_SENSOR_CAL,
		GROUP_2G(MT_EE_TX_POWER_0_START_2G),
		GROUP_2G(MT_EE_TX_POWER_1_START_2G),
		WORD(MT_EE_TX_POWER_CCK),
		WORD(MT_EE_TX_POWER_OFDM_2G_6M),
		WORD(MT_EE_TX_POWER_OFDM_2G_24M),
		WORD(MT_EE_TX_POWER_OFDM_2G_54M),
		WORD(MT_EE_TX_POWER_HT_BPSK_QPSK),
		WORD(MT_EE_TX_POWER_HT_16_64_QAM),
		WORD(MT_EE_TX_POWER_HT_64_QAM),
		MT_EE_ELAN_RX_MODE_GAIN,
		MT_EE_ELAN_RX_MODE_NF,
		MT_EE_ELAN_RX_MODE_P1DB,
		MT_EE_ELAN_BYPASS_MODE_GAIN,
		MT_EE_ELAN_BYPASS_MODE_NF,
		MT_EE_ELAN_BYPASS_MODE_P1DB,
		WORD(MT_EE_STEP_NUM_NEG_6_7),
		WORD(MT_EE_STEP_NUM_NEG_4_5),
		WORD(MT_EE_STEP_NUM_NEG_2_3),
		WORD(MT_EE_STEP_NUM_NEG_0_1),
		WORD(MT_EE_REF_STEP_24G),
		WORD(MT_EE_STEP_NUM_PLUS_1_2),
		WORD(MT_EE_STEP_NUM_PLUS_3_4),
		WORD(MT_EE_STEP_NUM_PLUS_5_6),
		MT_EE_STEP_NUM_PLUS_7,
		MT_EE_XTAL_FREQ_OFFSET,
		MT_EE_XTAL_TRIM_2_COMP,
		MT_EE_XTAL_TRIM_3_COMP,
		MT_EE_XTAL_WF_RFCAL,

		/* unknown fields below */
		WORD(0x24),
		0x34,
		0x39,
		0x3b,
		WORD(0x42),
		WORD(0x9e),
		0xf2,
		WORD(0xf8),
		0xfa,
		0x12e,
		WORD(0x130), WORD(0x132), WORD(0x134), WORD(0x136),
		WORD(0x138), WORD(0x13a), WORD(0x13c), WORD(0x13e),

#अघोषित GROUP_2G
#अघोषित WORD

	पूर्ण;
	काष्ठा req_data अणु
		__le16 addr;
		u8 val;
		u8 pad;
	पूर्ण __packed;
	काष्ठा अणु
		u8 buffer_mode;
		u8 len;
		u8 pad[2];
	पूर्ण req_hdr = अणु
		.buffer_mode = 1,
		.len = ARRAY_SIZE(req_fields) - 1,
	पूर्ण;
	स्थिर पूर्णांक size = 0xff * माप(काष्ठा req_data);
	u8 *req, *eep = (u8 *)dev->mt76.eeprom.data;
	पूर्णांक i, ret, len = माप(req_hdr) + size;
	काष्ठा req_data *data;

	BUILD_BUG_ON(ARRAY_SIZE(req_fields) * माप(*data) > size);

	req = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;

	स_नकल(req, &req_hdr, माप(req_hdr));
	data = (काष्ठा req_data *)(req + माप(req_hdr));
	स_रखो(data, 0, size);
	क्रम (i = 0; i < ARRAY_SIZE(req_fields); i++) अणु
		data[i].addr = cpu_to_le16(req_fields[i]);
		data[i].val = eep[req_fields[i]];
	पूर्ण

	ret = mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD_EFUSE_BUFFER_MODE,
				req, len, true);
	kमुक्त(req);

	वापस ret;
पूर्ण

अटल पूर्णांक mt7603_mcu_set_tx_घातer(काष्ठा mt7603_dev *dev)
अणु
	काष्ठा अणु
		u8 center_channel;
		u8 tssi;
		u8 temp_comp;
		u8 target_घातer[2];
		u8 rate_घातer_delta[14];
		u8 bw_घातer_delta;
		u8 ch_घातer_delta[6];
		u8 temp_comp_घातer[17];
		u8 reserved;
	पूर्ण req = अणु
		.center_channel = dev->mphy.chandef.chan->hw_value,
#घोषणा EEP_VAL(n) ((u8 *)dev->mt76.eeprom.data)[n]
		.tssi = EEP_VAL(MT_EE_NIC_CONF_1 + 1),
		.temp_comp = EEP_VAL(MT_EE_NIC_CONF_1),
		.target_घातer = अणु
			EEP_VAL(MT_EE_TX_POWER_0_START_2G + 2),
			EEP_VAL(MT_EE_TX_POWER_1_START_2G + 2)
		पूर्ण,
		.bw_घातer_delta = EEP_VAL(MT_EE_TX_POWER_DELTA_BW40),
		.ch_घातer_delta = अणु
			EEP_VAL(MT_EE_TX_POWER_0_START_2G + 3),
			EEP_VAL(MT_EE_TX_POWER_0_START_2G + 4),
			EEP_VAL(MT_EE_TX_POWER_0_START_2G + 5),
			EEP_VAL(MT_EE_TX_POWER_1_START_2G + 3),
			EEP_VAL(MT_EE_TX_POWER_1_START_2G + 4),
			EEP_VAL(MT_EE_TX_POWER_1_START_2G + 5)
		पूर्ण,
#अघोषित EEP_VAL
	पूर्ण;
	u8 *eep = (u8 *)dev->mt76.eeprom.data;

	स_नकल(req.rate_घातer_delta, eep + MT_EE_TX_POWER_CCK,
	       माप(req.rate_घातer_delta));

	स_नकल(req.temp_comp_घातer, eep + MT_EE_STEP_NUM_NEG_6_7,
	       माप(req.temp_comp_घातer));

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD_SET_TX_POWER_CTRL,
				 &req, माप(req), true);
पूर्ण

पूर्णांक mt7603_mcu_set_channel(काष्ठा mt7603_dev *dev)
अणु
	काष्ठा cfg80211_chan_def *chandef = &dev->mphy.chandef;
	काष्ठा ieee80211_hw *hw = mt76_hw(dev);
	पूर्णांक n_chains = hweight8(dev->mphy.antenna_mask);
	काष्ठा अणु
		u8 control_chan;
		u8 center_chan;
		u8 bw;
		u8 tx_streams;
		u8 rx_streams;
		u8 _res0[7];
		u8 txघातer[21];
		u8 _res1[3];
	पूर्ण req = अणु
		.control_chan = chandef->chan->hw_value,
		.center_chan = chandef->chan->hw_value,
		.bw = MT_BW_20,
		.tx_streams = n_chains,
		.rx_streams = n_chains,
	पूर्ण;
	s8 tx_घातer;
	पूर्णांक i, ret;

	अगर (dev->mphy.chandef.width == NL80211_CHAN_WIDTH_40) अणु
		req.bw = MT_BW_40;
		अगर (chandef->center_freq1 > chandef->chan->center_freq)
			req.center_chan += 2;
		अन्यथा
			req.center_chan -= 2;
	पूर्ण

	tx_घातer = hw->conf.घातer_level * 2;
	अगर (dev->mphy.antenna_mask == 3)
		tx_घातer -= 6;
	tx_घातer = min(tx_घातer, dev->tx_घातer_limit);

	dev->mphy.txघातer_cur = tx_घातer;

	क्रम (i = 0; i < ARRAY_SIZE(req.txघातer); i++)
		req.txघातer[i] = tx_घातer;

	ret = mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD_CHANNEL_SWITCH, &req,
				माप(req), true);
	अगर (ret)
		वापस ret;

	वापस mt7603_mcu_set_tx_घातer(dev);
पूर्ण
