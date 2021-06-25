<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2020 MediaTek Inc. */

#समावेश "mt7921.h"
#समावेश "eeprom.h"

अटल पूर्णांक
mt7921_fw_debug_set(व्योम *data, u64 val)
अणु
	काष्ठा mt7921_dev *dev = data;

	mt7921_mutex_acquire(dev);

	dev->fw_debug = (u8)val;
	mt7921_mcu_fw_log_2_host(dev, dev->fw_debug);

	mt7921_mutex_release(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7921_fw_debug_get(व्योम *data, u64 *val)
अणु
	काष्ठा mt7921_dev *dev = data;

	*val = dev->fw_debug;

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(fops_fw_debug, mt7921_fw_debug_get,
			 mt7921_fw_debug_set, "%lld\n");

अटल व्योम
mt7921_ampdu_stat_पढ़ो_phy(काष्ठा mt7921_phy *phy,
			   काष्ठा seq_file *file)
अणु
	काष्ठा mt7921_dev *dev = file->निजी;
	पूर्णांक bound[15], range[4], i;

	अगर (!phy)
		वापस;

	/* Tx ampdu stat */
	क्रम (i = 0; i < ARRAY_SIZE(range); i++)
		range[i] = mt76_rr(dev, MT_MIB_ARNG(0, i));

	क्रम (i = 0; i < ARRAY_SIZE(bound); i++)
		bound[i] = MT_MIB_ARNCR_RANGE(range[i / 4], i % 4) + 1;

	seq_म_लिखो(file, "\nPhy0\n");

	seq_म_लिखो(file, "Length: %8d | ", bound[0]);
	क्रम (i = 0; i < ARRAY_SIZE(bound) - 1; i++)
		seq_म_लिखो(file, "%3d  %3d | ", bound[i] + 1, bound[i + 1]);

	seq_माला_दो(file, "\nCount:  ");
	क्रम (i = 0; i < ARRAY_SIZE(bound); i++)
		seq_म_लिखो(file, "%8d | ", dev->mt76.aggr_stats[i]);
	seq_माला_दो(file, "\n");

	seq_म_लिखो(file, "BA miss count: %d\n", phy->mib.ba_miss_cnt);
पूर्ण

अटल पूर्णांक
mt7921_tx_stats_show(काष्ठा seq_file *file, व्योम *data)
अणु
	काष्ठा mt7921_dev *dev = file->निजी;
	पूर्णांक stat[8], i, n;

	mt7921_ampdu_stat_पढ़ो_phy(&dev->phy, file);

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

DEFINE_SHOW_ATTRIBUTE(mt7921_tx_stats);

अटल पूर्णांक
mt7921_queues_acq(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा mt7921_dev *dev = dev_get_drvdata(s->निजी);
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
mt7921_queues_पढ़ो(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा mt7921_dev *dev = dev_get_drvdata(s->निजी);
	काष्ठा अणु
		काष्ठा mt76_queue *q;
		अक्षर *queue;
	पूर्ण queue_map[] = अणु
		अणु dev->mphy.q_tx[MT_TXQ_BE],	 "WFDMA0" पूर्ण,
		अणु dev->mt76.q_mcu[MT_MCUQ_WM],	 "MCUWM"  पूर्ण,
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
mt7921_seq_माला_दो_array(काष्ठा seq_file *file, स्थिर अक्षर *str,
		      s8 *val, पूर्णांक len)
अणु
	पूर्णांक i;

	seq_म_लिखो(file, "%-16s:", str);
	क्रम (i = 0; i < len; i++)
		अगर (val[i] == 127)
			seq_म_लिखो(file, " %6s", "N.A");
		अन्यथा
			seq_म_लिखो(file, " %6d", val[i]);
	seq_माला_दो(file, "\n");
पूर्ण

#घोषणा mt7921_prपूर्णांक_txpwr_entry(prefix, rate)				\
(अणु									\
	mt7921_seq_माला_दो_array(s, #prefix " (user)",			\
			      txpwr.data[TXPWR_USER].rate,		\
			      ARRAY_SIZE(txpwr.data[TXPWR_USER].rate)); \
	mt7921_seq_माला_दो_array(s, #prefix " (eeprom)",			\
			      txpwr.data[TXPWR_EEPROM].rate,		\
			      ARRAY_SIZE(txpwr.data[TXPWR_EEPROM].rate)); \
	mt7921_seq_माला_दो_array(s, #prefix " (tmac)",			\
			      txpwr.data[TXPWR_MAC].rate,		\
			      ARRAY_SIZE(txpwr.data[TXPWR_MAC].rate));	\
पूर्ण)

अटल पूर्णांक
mt7921_txpwr(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा mt7921_dev *dev = dev_get_drvdata(s->निजी);
	काष्ठा mt7921_txpwr txpwr;
	पूर्णांक ret;

	ret = mt7921_get_txpwr_info(dev, &txpwr);
	अगर (ret)
		वापस ret;

	seq_म_लिखो(s, "Tx power table (channel %d)\n", txpwr.ch);
	seq_म_लिखो(s, "%-16s  %6s %6s %6s %6s\n",
		   " ", "1m", "2m", "5m", "11m");
	mt7921_prपूर्णांक_txpwr_entry(CCK, cck);

	seq_म_लिखो(s, "%-16s  %6s %6s %6s %6s %6s %6s %6s %6s\n",
		   " ", "6m", "9m", "12m", "18m", "24m", "36m",
		   "48m", "54m");
	mt7921_prपूर्णांक_txpwr_entry(OFDM, ofdm);

	seq_म_लिखो(s, "%-16s  %6s %6s %6s %6s %6s %6s %6s %6s\n",
		   " ", "mcs0", "mcs1", "mcs2", "mcs3", "mcs4", "mcs5",
		   "mcs6", "mcs7");
	mt7921_prपूर्णांक_txpwr_entry(HT20, ht20);

	seq_म_लिखो(s, "%-16s  %6s %6s %6s %6s %6s %6s %6s %6s %6s\n",
		   " ", "mcs0", "mcs1", "mcs2", "mcs3", "mcs4", "mcs5",
		   "mcs6", "mcs7", "mcs32");
	mt7921_prपूर्णांक_txpwr_entry(HT40, ht40);

	seq_म_लिखो(s, "%-16s  %6s %6s %6s %6s %6s %6s %6s %6s %6s %6s %6s %6s\n",
		   " ", "mcs0", "mcs1", "mcs2", "mcs3", "mcs4", "mcs5",
		   "mcs6", "mcs7", "mcs8", "mcs9", "mcs10", "mcs11");
	mt7921_prपूर्णांक_txpwr_entry(VHT20, vht20);
	mt7921_prपूर्णांक_txpwr_entry(VHT40, vht40);
	mt7921_prपूर्णांक_txpwr_entry(VHT80, vht80);
	mt7921_prपूर्णांक_txpwr_entry(VHT160, vht160);
	mt7921_prपूर्णांक_txpwr_entry(HE26, he26);
	mt7921_prपूर्णांक_txpwr_entry(HE52, he52);
	mt7921_prपूर्णांक_txpwr_entry(HE106, he106);
	mt7921_prपूर्णांक_txpwr_entry(HE242, he242);
	mt7921_prपूर्णांक_txpwr_entry(HE484, he484);
	mt7921_prपूर्णांक_txpwr_entry(HE996, he996);
	mt7921_prपूर्णांक_txpwr_entry(HE996x2, he996x2);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7921_pm_set(व्योम *data, u64 val)
अणु
	काष्ठा mt7921_dev *dev = data;
	काष्ठा mt76_connac_pm *pm = &dev->pm;
	काष्ठा mt76_phy *mphy = dev->phy.mt76;

	अगर (val == pm->enable)
		वापस 0;

	mt7921_mutex_acquire(dev);

	अगर (!pm->enable) अणु
		pm->stats.last_wake_event = jअगरfies;
		pm->stats.last_करोze_event = jअगरfies;
	पूर्ण
	pm->enable = val;

	ieee80211_iterate_active_पूर्णांकerfaces(mphy->hw,
					    IEEE80211_IFACE_ITER_RESUME_ALL,
					    mt7921_pm_पूर्णांकerface_iter, mphy->priv);
	mt7921_mutex_release(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7921_pm_get(व्योम *data, u64 *val)
अणु
	काष्ठा mt7921_dev *dev = data;

	*val = dev->pm.enable;

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(fops_pm, mt7921_pm_get, mt7921_pm_set, "%lld\n");

अटल पूर्णांक
mt7921_pm_stats(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा mt7921_dev *dev = dev_get_drvdata(s->निजी);
	काष्ठा mt76_connac_pm *pm = &dev->pm;

	अचिन्हित दीर्घ awake_समय = pm->stats.awake_समय;
	अचिन्हित दीर्घ करोze_समय = pm->stats.करोze_समय;

	अगर (!test_bit(MT76_STATE_PM, &dev->mphy.state))
		awake_समय += jअगरfies - pm->stats.last_wake_event;
	अन्यथा
		करोze_समय += jअगरfies - pm->stats.last_करोze_event;

	seq_म_लिखो(s, "awake time: %14u\ndoze time: %15u\n",
		   jअगरfies_to_msecs(awake_समय),
		   jअगरfies_to_msecs(करोze_समय));

	seq_म_लिखो(s, "low power wakes: %9d\n", pm->stats.lp_wake);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7921_pm_idle_समयout_set(व्योम *data, u64 val)
अणु
	काष्ठा mt7921_dev *dev = data;

	dev->pm.idle_समयout = msecs_to_jअगरfies(val);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7921_pm_idle_समयout_get(व्योम *data, u64 *val)
अणु
	काष्ठा mt7921_dev *dev = data;

	*val = jअगरfies_to_msecs(dev->pm.idle_समयout);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(fops_pm_idle_समयout, mt7921_pm_idle_समयout_get,
			 mt7921_pm_idle_समयout_set, "%lld\n");

अटल पूर्णांक mt7921_chip_reset(व्योम *data, u64 val)
अणु
	काष्ठा mt7921_dev *dev = data;
	पूर्णांक ret = 0;

	चयन (val) अणु
	हाल 1:
		/* Reset wअगरisys directly. */
		mt7921_reset(&dev->mt76);
		अवरोध;
	शेष:
		/* Collect the core dump beक्रमe reset wअगरisys. */
		mt7921_mutex_acquire(dev);
		ret = mt76_connac_mcu_chip_config(&dev->mt76);
		mt7921_mutex_release(dev);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(fops_reset, शून्य, mt7921_chip_reset, "%lld\n");

पूर्णांक mt7921_init_debugfs(काष्ठा mt7921_dev *dev)
अणु
	काष्ठा dentry *dir;

	dir = mt76_रेजिस्टर_debugfs(&dev->mt76);
	अगर (!dir)
		वापस -ENOMEM;

	debugfs_create_devm_seqfile(dev->mt76.dev, "queues", dir,
				    mt7921_queues_पढ़ो);
	debugfs_create_devm_seqfile(dev->mt76.dev, "acq", dir,
				    mt7921_queues_acq);
	debugfs_create_devm_seqfile(dev->mt76.dev, "txpower_sku", dir,
				    mt7921_txpwr);
	debugfs_create_file("tx_stats", 0400, dir, dev, &mt7921_tx_stats_fops);
	debugfs_create_file("fw_debug", 0600, dir, dev, &fops_fw_debug);
	debugfs_create_file("runtime-pm", 0600, dir, dev, &fops_pm);
	debugfs_create_file("idle-timeout", 0600, dir, dev,
			    &fops_pm_idle_समयout);
	debugfs_create_file("chip_reset", 0600, dir, dev, &fops_reset);
	debugfs_create_devm_seqfile(dev->mt76.dev, "runtime_pm_stats", dir,
				    mt7921_pm_stats);

	वापस 0;
पूर्ण
