<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2020 MediaTek Inc. */

#समावेश "mt7915.h"
#समावेश "eeprom.h"

/** global debugfs **/

अटल पूर्णांक
mt7915_implicit_txbf_set(व्योम *data, u64 val)
अणु
	काष्ठा mt7915_dev *dev = data;

	अगर (test_bit(MT76_STATE_RUNNING, &dev->mphy.state))
		वापस -EBUSY;

	dev->ibf = !!val;

	वापस mt7915_mcu_set_txbf_type(dev);
पूर्ण

अटल पूर्णांक
mt7915_implicit_txbf_get(व्योम *data, u64 *val)
अणु
	काष्ठा mt7915_dev *dev = data;

	*val = dev->ibf;

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(fops_implicit_txbf, mt7915_implicit_txbf_get,
			 mt7915_implicit_txbf_set, "%lld\n");

/* test knob of प्रणाली layer 1/2 error recovery */
अटल पूर्णांक mt7915_ser_trigger_set(व्योम *data, u64 val)
अणु
	क्रमागत अणु
		SER_SET_RECOVER_L1 = 1,
		SER_SET_RECOVER_L2,
		SER_ENABLE = 2,
		SER_RECOVER
	पूर्ण;
	काष्ठा mt7915_dev *dev = data;
	पूर्णांक ret = 0;

	चयन (val) अणु
	हाल SER_SET_RECOVER_L1:
	हाल SER_SET_RECOVER_L2:
		ret = mt7915_mcu_set_ser(dev, SER_ENABLE, BIT(val), 0);
		अगर (ret)
			वापस ret;

		वापस mt7915_mcu_set_ser(dev, SER_RECOVER, val, 0);
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(fops_ser_trigger, शून्य,
			 mt7915_ser_trigger_set, "%lld\n");

अटल पूर्णांक
mt7915_radar_trigger(व्योम *data, u64 val)
अणु
	काष्ठा mt7915_dev *dev = data;

	वापस mt7915_mcu_rdd_cmd(dev, RDD_RADAR_EMULATE, 1, 0, 0);
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(fops_radar_trigger, शून्य,
			 mt7915_radar_trigger, "%lld\n");

अटल पूर्णांक
mt7915_fw_debug_set(व्योम *data, u64 val)
अणु
	काष्ठा mt7915_dev *dev = data;
	क्रमागत अणु
		DEBUG_TXCMD = 62,
		DEBUG_CMD_RPT_TX,
		DEBUG_CMD_RPT_TRIG,
		DEBUG_SPL,
		DEBUG_RPT_RX,
	पूर्ण debug;

	dev->fw_debug = !!val;

	mt7915_mcu_fw_log_2_host(dev, dev->fw_debug ? 2 : 0);

	क्रम (debug = DEBUG_TXCMD; debug <= DEBUG_RPT_RX; debug++)
		mt7915_mcu_fw_dbg_ctrl(dev, debug, dev->fw_debug);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7915_fw_debug_get(व्योम *data, u64 *val)
अणु
	काष्ठा mt7915_dev *dev = data;

	*val = dev->fw_debug;

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(fops_fw_debug, mt7915_fw_debug_get,
			 mt7915_fw_debug_set, "%lld\n");

अटल व्योम
mt7915_ampdu_stat_पढ़ो_phy(काष्ठा mt7915_phy *phy,
			   काष्ठा seq_file *file)
अणु
	काष्ठा mt7915_dev *dev = file->निजी;
	bool ext_phy = phy != &dev->phy;
	पूर्णांक bound[15], range[4], i, n;

	अगर (!phy)
		वापस;

	/* Tx ampdu stat */
	क्रम (i = 0; i < ARRAY_SIZE(range); i++)
		range[i] = mt76_rr(dev, MT_MIB_ARNG(ext_phy, i));

	क्रम (i = 0; i < ARRAY_SIZE(bound); i++)
		bound[i] = MT_MIB_ARNCR_RANGE(range[i / 4], i % 4) + 1;

	seq_म_लिखो(file, "\nPhy %d\n", ext_phy);

	seq_म_लिखो(file, "Length: %8d | ", bound[0]);
	क्रम (i = 0; i < ARRAY_SIZE(bound) - 1; i++)
		seq_म_लिखो(file, "%3d -%3d | ",
			   bound[i] + 1, bound[i + 1]);

	seq_माला_दो(file, "\nCount:  ");
	n = ext_phy ? ARRAY_SIZE(dev->mt76.aggr_stats) / 2 : 0;
	क्रम (i = 0; i < ARRAY_SIZE(bound); i++)
		seq_म_लिखो(file, "%8d | ", dev->mt76.aggr_stats[i + n]);
	seq_माला_दो(file, "\n");

	seq_म_लिखो(file, "BA miss count: %d\n", phy->mib.ba_miss_cnt);
पूर्ण

अटल व्योम
mt7915_txbf_stat_पढ़ो_phy(काष्ठा mt7915_phy *phy, काष्ठा seq_file *s)
अणु
	काष्ठा mt7915_dev *dev = s->निजी;
	bool ext_phy = phy != &dev->phy;
	पूर्णांक cnt;

	अगर (!phy)
		वापस;

	/* Tx Beamक्रमmer monitor */
	seq_माला_दो(s, "\nTx Beamformer applied PPDU counts: ");

	cnt = mt76_rr(dev, MT_ETBF_TX_APP_CNT(ext_phy));
	seq_म_लिखो(s, "iBF: %ld, eBF: %ld\n",
		   FIELD_GET(MT_ETBF_TX_IBF_CNT, cnt),
		   FIELD_GET(MT_ETBF_TX_EBF_CNT, cnt));

	/* Tx Beamक्रमmer Rx feedback monitor */
	seq_माला_दो(s, "Tx Beamformer Rx feedback statistics: ");

	cnt = mt76_rr(dev, MT_ETBF_RX_FB_CNT(ext_phy));
	seq_म_लिखो(s, "All: %ld, HE: %ld, VHT: %ld, HT: %ld\n",
		   FIELD_GET(MT_ETBF_RX_FB_ALL, cnt),
		   FIELD_GET(MT_ETBF_RX_FB_HE, cnt),
		   FIELD_GET(MT_ETBF_RX_FB_VHT, cnt),
		   FIELD_GET(MT_ETBF_RX_FB_HT, cnt));

	/* Tx Beamक्रमmee Rx NDPA & Tx feedback report */
	cnt = mt76_rr(dev, MT_ETBF_TX_NDP_BFRP(ext_phy));
	seq_म_लिखो(s, "Tx Beamformee successful feedback frames: %ld\n",
		   FIELD_GET(MT_ETBF_TX_FB_CPL, cnt));
	seq_म_लिखो(s, "Tx Beamformee feedback triggered counts: %ld\n",
		   FIELD_GET(MT_ETBF_TX_FB_TRI, cnt));

	/* Tx SU & MU counters */
	cnt = mt76_rr(dev, MT_MIB_SDR34(ext_phy));
	seq_म_लिखो(s, "Tx multi-user Beamforming counts: %ld\n",
		   FIELD_GET(MT_MIB_MU_BF_TX_CNT, cnt));
	cnt = mt76_rr(dev, MT_MIB_DR8(ext_phy));
	seq_म_लिखो(s, "Tx multi-user MPDU counts: %d\n", cnt);
	cnt = mt76_rr(dev, MT_MIB_DR9(ext_phy));
	seq_म_लिखो(s, "Tx multi-user successful MPDU counts: %d\n", cnt);
	cnt = mt76_rr(dev, MT_MIB_DR11(ext_phy));
	seq_म_लिखो(s, "Tx single-user successful MPDU counts: %d\n", cnt);

	seq_माला_दो(s, "\n");
पूर्ण

अटल पूर्णांक
mt7915_tx_stats_show(काष्ठा seq_file *file, व्योम *data)
अणु
	काष्ठा mt7915_dev *dev = file->निजी;
	पूर्णांक stat[8], i, n;

	mt7915_ampdu_stat_पढ़ो_phy(&dev->phy, file);
	mt7915_txbf_stat_पढ़ो_phy(&dev->phy, file);

	mt7915_ampdu_stat_पढ़ो_phy(mt7915_ext_phy(dev), file);
	mt7915_txbf_stat_पढ़ो_phy(mt7915_ext_phy(dev), file);

	/* Tx amsdu info */
	seq_माला_दो(file, "Tx MSDU stat:\n");
	क्रम (i = 0, n = 0; i < ARRAY_SIZE(stat); i++) अणु
		stat[i] = mt76_rr(dev,  MT_PLE_AMSDU_PACK_MSDU_CNT(i));
		n += stat[i];
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(stat); i++) अणु
		seq_म_लिखो(file, "AMSDU pack count of %d MSDU in TXD: 0x%x ",
			   i + 1, stat[i]);
		अगर (n != 0)
			seq_म_लिखो(file, "(%d%%)\n", stat[i] * 100 / n);
		अन्यथा
			seq_माला_दो(file, "\n");
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(mt7915_tx_stats);

अटल पूर्णांक mt7915_पढ़ो_temperature(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा mt7915_dev *dev = dev_get_drvdata(s->निजी);
	पूर्णांक temp;

	/* cpu */
	temp = mt7915_mcu_get_temperature(dev, 0);
	seq_म_लिखो(s, "Temperature: %d\n", temp);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7915_queues_acq(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा mt7915_dev *dev = dev_get_drvdata(s->निजी);
	पूर्णांक i;

	क्रम (i = 0; i < 16; i++) अणु
		पूर्णांक j, acs = i / 4, index = i % 4;
		u32 ctrl, val, qlen = 0;

		val = mt76_rr(dev, MT_PLE_AC_QEMPTY(acs, index));
		ctrl = BIT(31) | BIT(15) | (acs << 8);

		क्रम (j = 0; j < 32; j++) अणु
			अगर (val & BIT(j))
				जारी;

			mt76_wr(dev, MT_PLE_FL_Q0_CTRL,
				ctrl | (j + (index << 5)));
			qlen += mt76_get_field(dev, MT_PLE_FL_Q3_CTRL,
					       GENMASK(11, 0));
		पूर्ण
		seq_म_लिखो(s, "AC%d%d: queued=%d\n", acs, index, qlen);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7915_queues_पढ़ो(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा mt7915_dev *dev = dev_get_drvdata(s->निजी);
	काष्ठा mt76_phy *mphy_ext = dev->mt76.phy2;
	काष्ठा mt76_queue *ext_q = mphy_ext ? mphy_ext->q_tx[MT_TXQ_BE] : शून्य;
	काष्ठा अणु
		काष्ठा mt76_queue *q;
		अक्षर *queue;
	पूर्ण queue_map[] = अणु
		अणु dev->mphy.q_tx[MT_TXQ_BE],	 "WFDMA0" पूर्ण,
		अणु ext_q,			 "WFDMA1" पूर्ण,
		अणु dev->mphy.q_tx[MT_TXQ_BE],	 "WFDMA0" पूर्ण,
		अणु dev->mt76.q_mcu[MT_MCUQ_WM],	 "MCUWM"  पूर्ण,
		अणु dev->mt76.q_mcu[MT_MCUQ_WA],	 "MCUWA"  पूर्ण,
		अणु dev->mt76.q_mcu[MT_MCUQ_FWDL], "MCUFWQ" पूर्ण,
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(queue_map); i++) अणु
		काष्ठा mt76_queue *q = queue_map[i].q;

		अगर (!q)
			जारी;

		seq_म_लिखो(s,
			   "%s:	queued=%d head=%d tail=%d\n",
			   queue_map[i].queue, q->queued, q->head,
			   q->tail);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
mt7915_माला_दो_rate_txघातer(काष्ठा seq_file *s, काष्ठा mt7915_phy *phy)
अणु
	अटल स्थिर अक्षर * स्थिर sku_group_name[] = अणु
		"CCK", "OFDM", "HT20", "HT40",
		"VHT20", "VHT40", "VHT80", "VHT160",
		"RU26", "RU52", "RU106", "RU242/SU20",
		"RU484/SU40", "RU996/SU80", "RU2x996/SU160"
	पूर्ण;
	काष्ठा mt7915_dev *dev = dev_get_drvdata(s->निजी);
	bool ext_phy = phy != &dev->phy;
	u32 reg_base;
	पूर्णांक i, idx = 0;

	अगर (!phy)
		वापस;

	reg_base = MT_TMAC_FP0R0(ext_phy);
	seq_म_लिखो(s, "\nBand %d\n", ext_phy);

	क्रम (i = 0; i < ARRAY_SIZE(mt7915_sku_group_len); i++) अणु
		u8 cnt, mcs_num = mt7915_sku_group_len[i];
		s8 txघातer[12];
		पूर्णांक j;

		अगर (i == SKU_HT_BW20 || i == SKU_HT_BW40) अणु
			mcs_num = 8;
		पूर्ण अन्यथा अगर (i >= SKU_VHT_BW20 && i <= SKU_VHT_BW160) अणु
			mcs_num = 10;
		पूर्ण अन्यथा अगर (i == SKU_HE_RU26) अणु
			reg_base = MT_TMAC_FP0R18(ext_phy);
			idx = 0;
		पूर्ण

		क्रम (j = 0, cnt = 0; j < DIV_ROUND_UP(mcs_num, 4); j++) अणु
			u32 val;

			अगर (i == SKU_VHT_BW160 && idx == 60) अणु
				reg_base = MT_TMAC_FP0R15(ext_phy);
				idx = 0;
			पूर्ण

			val = mt76_rr(dev, reg_base + (idx / 4) * 4);

			अगर (idx && idx % 4)
				val >>= (idx % 4) * 8;

			जबतक (val > 0 && cnt < mcs_num) अणु
				s8 pwr = FIELD_GET(MT_TMAC_FP_MASK, val);

				txघातer[cnt++] = pwr;
				val >>= 8;
				idx++;
			पूर्ण
		पूर्ण

		mt76_seq_माला_दो_array(s, sku_group_name[i], txघातer, mcs_num);
	पूर्ण
पूर्ण

अटल पूर्णांक
mt7915_पढ़ो_rate_txघातer(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा mt7915_dev *dev = dev_get_drvdata(s->निजी);

	mt7915_माला_दो_rate_txघातer(s, &dev->phy);
	mt7915_माला_दो_rate_txघातer(s, mt7915_ext_phy(dev));

	वापस 0;
पूर्ण

पूर्णांक mt7915_init_debugfs(काष्ठा mt7915_dev *dev)
अणु
	काष्ठा dentry *dir;

	dir = mt76_रेजिस्टर_debugfs(&dev->mt76);
	अगर (!dir)
		वापस -ENOMEM;

	debugfs_create_devm_seqfile(dev->mt76.dev, "queues", dir,
				    mt7915_queues_पढ़ो);
	debugfs_create_devm_seqfile(dev->mt76.dev, "acq", dir,
				    mt7915_queues_acq);
	debugfs_create_file("tx_stats", 0400, dir, dev, &mt7915_tx_stats_fops);
	debugfs_create_file("fw_debug", 0600, dir, dev, &fops_fw_debug);
	debugfs_create_file("implicit_txbf", 0600, dir, dev,
			    &fops_implicit_txbf);
	debugfs_create_u32("dfs_hw_pattern", 0400, dir, &dev->hw_pattern);
	/* test knobs */
	debugfs_create_file("radar_trigger", 0200, dir, dev,
			    &fops_radar_trigger);
	debugfs_create_file("ser_trigger", 0200, dir, dev, &fops_ser_trigger);
	debugfs_create_devm_seqfile(dev->mt76.dev, "temperature", dir,
				    mt7915_पढ़ो_temperature);
	debugfs_create_devm_seqfile(dev->mt76.dev, "txpower_sku", dir,
				    mt7915_पढ़ो_rate_txघातer);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_MAC80211_DEBUGFS
/** per-station debugfs **/

/* usage: <tx mode> <ldpc> <stbc> <bw> <gi> <nss> <mcs> */
अटल पूर्णांक mt7915_sta_fixed_rate_set(व्योम *data, u64 rate)
अणु
	काष्ठा ieee80211_sta *sta = data;
	काष्ठा mt7915_sta *msta = (काष्ठा mt7915_sta *)sta->drv_priv;

	वापस mt7915_mcu_set_fixed_rate(msta->vअगर->phy->dev, sta, rate);
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(fops_fixed_rate, शून्य,
			 mt7915_sta_fixed_rate_set, "%llx\n");

अटल पूर्णांक
mt7915_sta_stats_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा ieee80211_sta *sta = s->निजी;
	काष्ठा mt7915_sta *msta = (काष्ठा mt7915_sta *)sta->drv_priv;
	काष्ठा mt7915_sta_stats *stats = &msta->stats;
	काष्ठा rate_info *rate = &stats->prob_rate;
	अटल स्थिर अक्षर * स्थिर bw[] = अणु
		"BW20", "BW5", "BW10", "BW40",
		"BW80", "BW160", "BW_HE_RU"
	पूर्ण;

	अगर (!rate->legacy && !rate->flags)
		वापस 0;

	seq_माला_दो(s, "Probing rate - ");
	अगर (rate->flags & RATE_INFO_FLAGS_MCS)
		seq_माला_दो(s, "HT ");
	अन्यथा अगर (rate->flags & RATE_INFO_FLAGS_VHT_MCS)
		seq_माला_दो(s, "VHT ");
	अन्यथा अगर (rate->flags & RATE_INFO_FLAGS_HE_MCS)
		seq_माला_दो(s, "HE ");
	अन्यथा
		seq_म_लिखो(s, "Bitrate %d\n", rate->legacy);

	अगर (rate->flags) अणु
		seq_म_लिखो(s, "%s NSS%d MCS%d ",
			   bw[rate->bw], rate->nss, rate->mcs);

		अगर (rate->flags & RATE_INFO_FLAGS_SHORT_GI)
			seq_माला_दो(s, "SGI ");
		अन्यथा अगर (rate->he_gi)
			seq_माला_दो(s, "HE GI ");

		अगर (rate->he_dcm)
			seq_माला_दो(s, "DCM ");
	पूर्ण

	seq_म_लिखो(s, "\nPPDU PER: %ld.%1ld%%\n",
		   stats->per / 10, stats->per % 10);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(mt7915_sta_stats);

व्योम mt7915_sta_add_debugfs(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			    काष्ठा ieee80211_sta *sta, काष्ठा dentry *dir)
अणु
	debugfs_create_file("fixed_rate", 0600, dir, sta, &fops_fixed_rate);
	debugfs_create_file("stats", 0400, dir, sta, &mt7915_sta_stats_fops);
पूर्ण
#पूर्ण_अगर
