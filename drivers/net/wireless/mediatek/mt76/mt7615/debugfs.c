<शैली गुरु>
// SPDX-License-Identअगरier: ISC

#समावेश "mt7615.h"

अटल पूर्णांक
mt7615_radar_pattern_set(व्योम *data, u64 val)
अणु
	काष्ठा mt7615_dev *dev = data;
	पूर्णांक err;

	अगर (!mt7615_रुको_क्रम_mcu_init(dev))
		वापस 0;

	mt7615_mutex_acquire(dev);
	err = mt7615_mcu_rdd_send_pattern(dev);
	mt7615_mutex_release(dev);

	वापस err;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(fops_radar_pattern, शून्य,
			 mt7615_radar_pattern_set, "%lld\n");

अटल पूर्णांक mt7615_config(व्योम *data, u64 val)
अणु
	काष्ठा mt7615_dev *dev = data;
	पूर्णांक ret;

	mt7615_mutex_acquire(dev);
	ret = mt76_connac_mcu_chip_config(&dev->mt76);
	mt7615_mutex_release(dev);

	वापस ret;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(fops_config, शून्य, mt7615_config, "%lld\n");

अटल पूर्णांक
mt7615_scs_set(व्योम *data, u64 val)
अणु
	काष्ठा mt7615_dev *dev = data;
	काष्ठा mt7615_phy *ext_phy;

	अगर (!mt7615_रुको_क्रम_mcu_init(dev))
		वापस 0;

	mt7615_mac_set_scs(&dev->phy, val);
	ext_phy = mt7615_ext_phy(dev);
	अगर (ext_phy)
		mt7615_mac_set_scs(ext_phy, val);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7615_scs_get(व्योम *data, u64 *val)
अणु
	काष्ठा mt7615_dev *dev = data;

	*val = dev->phy.scs_en;

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(fops_scs, mt7615_scs_get,
			 mt7615_scs_set, "%lld\n");

अटल पूर्णांक
mt7615_pm_set(व्योम *data, u64 val)
अणु
	काष्ठा mt7615_dev *dev = data;
	काष्ठा mt76_connac_pm *pm = &dev->pm;
	पूर्णांक ret = 0;

	अगर (!mt7615_रुको_क्रम_mcu_init(dev))
		वापस 0;

	अगर (!mt7615_firmware_offload(dev) || !mt76_is_mmio(&dev->mt76))
		वापस -EOPNOTSUPP;

	अगर (val == pm->enable)
		वापस 0;

	mt7615_mutex_acquire(dev);

	अगर (dev->phy.n_beacon_vअगर) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	अगर (!pm->enable) अणु
		pm->stats.last_wake_event = jअगरfies;
		pm->stats.last_करोze_event = jअगरfies;
	पूर्ण
	pm->enable = val;
out:
	mt7615_mutex_release(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक
mt7615_pm_get(व्योम *data, u64 *val)
अणु
	काष्ठा mt7615_dev *dev = data;

	*val = dev->pm.enable;

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(fops_pm, mt7615_pm_get, mt7615_pm_set, "%lld\n");

अटल पूर्णांक
mt7615_pm_stats(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा mt7615_dev *dev = dev_get_drvdata(s->निजी);
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

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7615_pm_idle_समयout_set(व्योम *data, u64 val)
अणु
	काष्ठा mt7615_dev *dev = data;

	dev->pm.idle_समयout = msecs_to_jअगरfies(val);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7615_pm_idle_समयout_get(व्योम *data, u64 *val)
अणु
	काष्ठा mt7615_dev *dev = data;

	*val = jअगरfies_to_msecs(dev->pm.idle_समयout);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(fops_pm_idle_समयout, mt7615_pm_idle_समयout_get,
			 mt7615_pm_idle_समयout_set, "%lld\n");

अटल पूर्णांक
mt7615_dbdc_set(व्योम *data, u64 val)
अणु
	काष्ठा mt7615_dev *dev = data;

	अगर (!mt7615_रुको_क्रम_mcu_init(dev))
		वापस 0;

	अगर (val)
		mt7615_रेजिस्टर_ext_phy(dev);
	अन्यथा
		mt7615_unरेजिस्टर_ext_phy(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7615_dbdc_get(व्योम *data, u64 *val)
अणु
	काष्ठा mt7615_dev *dev = data;

	*val = !!mt7615_ext_phy(dev);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(fops_dbdc, mt7615_dbdc_get,
			 mt7615_dbdc_set, "%lld\n");

अटल पूर्णांक
mt7615_fw_debug_set(व्योम *data, u64 val)
अणु
	काष्ठा mt7615_dev *dev = data;

	अगर (!mt7615_रुको_क्रम_mcu_init(dev))
		वापस 0;

	dev->fw_debug = val;

	mt7615_mutex_acquire(dev);
	mt7615_mcu_fw_log_2_host(dev, dev->fw_debug ? 2 : 0);
	mt7615_mutex_release(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7615_fw_debug_get(व्योम *data, u64 *val)
अणु
	काष्ठा mt7615_dev *dev = data;

	*val = dev->fw_debug;

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(fops_fw_debug, mt7615_fw_debug_get,
			 mt7615_fw_debug_set, "%lld\n");

अटल पूर्णांक
mt7615_reset_test_set(व्योम *data, u64 val)
अणु
	काष्ठा mt7615_dev *dev = data;
	काष्ठा sk_buff *skb;

	अगर (!mt7615_रुको_क्रम_mcu_init(dev))
		वापस 0;

	skb = alloc_skb(1, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put(skb, 1);

	mt7615_mutex_acquire(dev);
	mt76_tx_queue_skb_raw(dev, dev->mphy.q_tx[0], skb, 0);
	mt7615_mutex_release(dev);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(fops_reset_test, शून्य,
			 mt7615_reset_test_set, "%lld\n");

अटल व्योम
mt7615_ampdu_stat_पढ़ो_phy(काष्ठा mt7615_phy *phy,
			   काष्ठा seq_file *file)
अणु
	काष्ठा mt7615_dev *dev = file->निजी;
	u32 reg = is_mt7663(&dev->mt76) ? MT_MIB_ARNG(0) : MT_AGG_ASRCR0;
	bool ext_phy = phy != &dev->phy;
	पूर्णांक bound[7], i, range;

	अगर (!phy)
		वापस;

	range = mt76_rr(dev, reg);
	क्रम (i = 0; i < 4; i++)
		bound[i] = MT_AGG_ASRCR_RANGE(range, i) + 1;

	range = mt76_rr(dev, reg + 4);
	क्रम (i = 0; i < 3; i++)
		bound[i + 4] = MT_AGG_ASRCR_RANGE(range, i) + 1;

	seq_म_लिखो(file, "\nPhy %d\n", ext_phy);

	seq_म_लिखो(file, "Length: %8d | ", bound[0]);
	क्रम (i = 0; i < ARRAY_SIZE(bound) - 1; i++)
		seq_म_लिखो(file, "%3d -%3d | ",
			   bound[i], bound[i + 1]);
	seq_माला_दो(file, "\nCount:  ");

	range = ext_phy ? ARRAY_SIZE(dev->mt76.aggr_stats) / 2 : 0;
	क्रम (i = 0; i < ARRAY_SIZE(bound); i++)
		seq_म_लिखो(file, "%8d | ", dev->mt76.aggr_stats[i + range]);
	seq_माला_दो(file, "\n");

	seq_म_लिखो(file, "BA miss count: %d\n", phy->mib.ba_miss_cnt);
	seq_म_लिखो(file, "PER: %ld.%1ld%%\n",
		   phy->mib.aggr_per / 10, phy->mib.aggr_per % 10);
पूर्ण

अटल पूर्णांक
mt7615_ampdu_stat_show(काष्ठा seq_file *file, व्योम *data)
अणु
	काष्ठा mt7615_dev *dev = file->निजी;

	mt7615_mutex_acquire(dev);

	mt7615_ampdu_stat_पढ़ो_phy(&dev->phy, file);
	mt7615_ampdu_stat_पढ़ो_phy(mt7615_ext_phy(dev), file);

	mt7615_mutex_release(dev);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(mt7615_ampdu_stat);

अटल व्योम
mt7615_radio_पढ़ो_phy(काष्ठा mt7615_phy *phy, काष्ठा seq_file *s)
अणु
	काष्ठा mt7615_dev *dev = dev_get_drvdata(s->निजी);
	bool ext_phy = phy != &dev->phy;

	अगर (!phy)
		वापस;

	seq_म_लिखो(s, "Radio %d sensitivity: ofdm=%d cck=%d\n", ext_phy,
		   phy->ofdm_sensitivity, phy->cck_sensitivity);
	seq_म_लिखो(s, "Radio %d false CCA: ofdm=%d cck=%d\n", ext_phy,
		   phy->false_cca_ofdm, phy->false_cca_cck);
पूर्ण

अटल पूर्णांक
mt7615_radio_पढ़ो(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा mt7615_dev *dev = dev_get_drvdata(s->निजी);

	mt7615_radio_पढ़ो_phy(&dev->phy, s);
	mt7615_radio_पढ़ो_phy(mt7615_ext_phy(dev), s);

	वापस 0;
पूर्ण

अटल पूर्णांक mt7615_पढ़ो_temperature(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा mt7615_dev *dev = dev_get_drvdata(s->निजी);
	पूर्णांक temp;

	अगर (!mt7615_रुको_क्रम_mcu_init(dev))
		वापस 0;

	/* cpu */
	mt7615_mutex_acquire(dev);
	temp = mt7615_mcu_get_temperature(dev, 0);
	mt7615_mutex_release(dev);

	seq_म_लिखो(s, "Temperature: %d\n", temp);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7615_queues_acq(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा mt7615_dev *dev = dev_get_drvdata(s->निजी);
	पूर्णांक i;

	mt7615_mutex_acquire(dev);

	क्रम (i = 0; i < 16; i++) अणु
		पूर्णांक j, wmm_idx = i % MT7615_MAX_WMM_SETS;
		पूर्णांक acs = i / MT7615_MAX_WMM_SETS;
		u32 ctrl, val, qlen = 0;

		val = mt76_rr(dev, MT_PLE_AC_QEMPTY(acs, wmm_idx));
		ctrl = BIT(31) | BIT(15) | (acs << 8);

		क्रम (j = 0; j < 32; j++) अणु
			अगर (val & BIT(j))
				जारी;

			mt76_wr(dev, MT_PLE_FL_Q0_CTRL,
				ctrl | (j + (wmm_idx << 5)));
			qlen += mt76_get_field(dev, MT_PLE_FL_Q3_CTRL,
					       GENMASK(11, 0));
		पूर्ण
		seq_म_लिखो(s, "AC%d%d: queued=%d\n", wmm_idx, acs, qlen);
	पूर्ण

	mt7615_mutex_release(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7615_queues_पढ़ो(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा mt7615_dev *dev = dev_get_drvdata(s->निजी);
	काष्ठा अणु
		काष्ठा mt76_queue *q;
		अक्षर *queue;
	पूर्ण queue_map[] = अणु
		अणु dev->mphy.q_tx[MT_TXQ_BE], "PDMA0" पूर्ण,
		अणु dev->mt76.q_mcu[MT_MCUQ_WM], "MCUQ" पूर्ण,
		अणु dev->mt76.q_mcu[MT_MCUQ_FWDL], "MCUFWQ" पूर्ण,
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(queue_map); i++) अणु
		काष्ठा mt76_queue *q = queue_map[i].q;

		seq_म_लिखो(s,
			   "%s:	queued=%d head=%d tail=%d\n",
			   queue_map[i].queue, q->queued, q->head,
			   q->tail);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7615_rf_reg_set(व्योम *data, u64 val)
अणु
	काष्ठा mt7615_dev *dev = data;

	mt7615_rf_wr(dev, dev->debugfs_rf_wf, dev->debugfs_rf_reg, val);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7615_rf_reg_get(व्योम *data, u64 *val)
अणु
	काष्ठा mt7615_dev *dev = data;

	*val = mt7615_rf_rr(dev, dev->debugfs_rf_wf, dev->debugfs_rf_reg);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(fops_rf_reg, mt7615_rf_reg_get, mt7615_rf_reg_set,
			 "0x%08llx\n");

अटल sमाप_प्रकार
mt7615_ext_mac_addr_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
			 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा mt7615_dev *dev = file->निजी_data;
	अक्षर buf[32 * ((ETH_ALEN * 3) + 4) + 1];
	u8 addr[ETH_ALEN];
	पूर्णांक ofs = 0;
	पूर्णांक i;

	क्रम (i = 0; i < 32; i++) अणु
		अगर (!(dev->muar_mask & BIT(i)))
			जारी;

		mt76_wr(dev, MT_WF_RMAC_MAR1,
			FIELD_PREP(MT_WF_RMAC_MAR1_IDX, i * 2) |
			MT_WF_RMAC_MAR1_START);
		put_unaligned_le32(mt76_rr(dev, MT_WF_RMAC_MAR0), addr);
		put_unaligned_le16((mt76_rr(dev, MT_WF_RMAC_MAR1) &
				    MT_WF_RMAC_MAR1_ADDR), addr + 4);
		ofs += snम_लिखो(buf + ofs, माप(buf) - ofs, "%d=%pM\n", i, addr);
	पूर्ण

	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, ofs);
पूर्ण

अटल sमाप_प्रकार
mt7615_ext_mac_addr_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *userbuf,
			  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा mt7615_dev *dev = file->निजी_data;
	अचिन्हित दीर्घ idx = 0;
	u8 addr[ETH_ALEN];
	अक्षर buf[32];
	अक्षर *p;

	अगर (count > माप(buf))
		वापस -EINVAL;

	अगर (copy_from_user(buf, userbuf, count))
		वापस -EFAULT;

	buf[माप(buf) - 1] = '\0';

	p = म_अक्षर(buf, '=');
	अगर (p) अणु
		*p = 0;
		p++;

		अगर (kम_से_अदीर्घ(buf, 0, &idx) || idx > 31)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		idx = 0;
		p = buf;
	पूर्ण

	अगर (!mac_pton(p, addr))
		वापस -EINVAL;

	अगर (is_valid_ether_addr(addr)) अणु
		dev->muar_mask |= BIT(idx);
	पूर्ण अन्यथा अणु
		स_रखो(addr, 0, माप(addr));
		dev->muar_mask &= ~BIT(idx);
	पूर्ण

	mt76_rmw_field(dev, MT_WF_RMAC_MORE(0), MT_WF_RMAC_MORE_MUAR_MODE, 1);
	mt76_wr(dev, MT_WF_RMAC_MAR0, get_unaligned_le32(addr));
	mt76_wr(dev, MT_WF_RMAC_MAR1,
		get_unaligned_le16(addr + 4) |
		FIELD_PREP(MT_WF_RMAC_MAR1_IDX, idx * 2) |
		MT_WF_RMAC_MAR1_START |
		MT_WF_RMAC_MAR1_WRITE);

	mt76_rmw_field(dev, MT_WF_RMAC_MORE(0), MT_WF_RMAC_MORE_MUAR_MODE, !!dev->muar_mask);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_ext_mac_addr = अणु
	.खोलो = simple_खोलो,
	.llseek = generic_file_llseek,
	.पढ़ो = mt7615_ext_mac_addr_पढ़ो,
	.ग_लिखो = mt7615_ext_mac_addr_ग_लिखो,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक
mt7663s_sched_quota_पढ़ो(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा mt7615_dev *dev = dev_get_drvdata(s->निजी);
	काष्ठा mt76_sdio *sdio = &dev->mt76.sdio;

	seq_म_लिखो(s, "pse_data_quota\t%d\n", sdio->sched.pse_data_quota);
	seq_म_लिखो(s, "ple_data_quota\t%d\n", sdio->sched.ple_data_quota);
	seq_म_लिखो(s, "pse_mcu_quota\t%d\n", sdio->sched.pse_mcu_quota);
	seq_म_लिखो(s, "sched_deficit\t%d\n", sdio->sched.deficit);

	वापस 0;
पूर्ण

पूर्णांक mt7615_init_debugfs(काष्ठा mt7615_dev *dev)
अणु
	काष्ठा dentry *dir;

	dir = mt76_रेजिस्टर_debugfs(&dev->mt76);
	अगर (!dir)
		वापस -ENOMEM;

	अगर (is_mt7615(&dev->mt76))
		debugfs_create_devm_seqfile(dev->mt76.dev, "xmit-queues", dir,
					    mt7615_queues_पढ़ो);
	अन्यथा
		debugfs_create_devm_seqfile(dev->mt76.dev, "xmit-queues", dir,
					    mt76_queues_पढ़ो);
	debugfs_create_devm_seqfile(dev->mt76.dev, "acq", dir,
				    mt7615_queues_acq);
	debugfs_create_file("ampdu_stat", 0400, dir, dev, &mt7615_ampdu_stat_fops);
	debugfs_create_file("scs", 0600, dir, dev, &fops_scs);
	debugfs_create_file("dbdc", 0600, dir, dev, &fops_dbdc);
	debugfs_create_file("fw_debug", 0600, dir, dev, &fops_fw_debug);
	debugfs_create_file("runtime-pm", 0600, dir, dev, &fops_pm);
	debugfs_create_file("idle-timeout", 0600, dir, dev,
			    &fops_pm_idle_समयout);
	debugfs_create_devm_seqfile(dev->mt76.dev, "runtime_pm_stats", dir,
				    mt7615_pm_stats);
	debugfs_create_devm_seqfile(dev->mt76.dev, "radio", dir,
				    mt7615_radio_पढ़ो);

	अगर (is_mt7615(&dev->mt76)) अणु
		debugfs_create_u32("dfs_hw_pattern", 0400, dir,
				   &dev->hw_pattern);
		/* test pattern knobs */
		debugfs_create_u8("pattern_len", 0600, dir,
				  &dev->radar_pattern.n_pulses);
		debugfs_create_u32("pulse_period", 0600, dir,
				   &dev->radar_pattern.period);
		debugfs_create_u16("pulse_width", 0600, dir,
				   &dev->radar_pattern.width);
		debugfs_create_u16("pulse_power", 0600, dir,
				   &dev->radar_pattern.घातer);
		debugfs_create_file("radar_trigger", 0200, dir, dev,
				    &fops_radar_pattern);
	पूर्ण

	debugfs_create_file("reset_test", 0200, dir, dev,
			    &fops_reset_test);
	debugfs_create_devm_seqfile(dev->mt76.dev, "temperature", dir,
				    mt7615_पढ़ो_temperature);
	debugfs_create_file("ext_mac_addr", 0600, dir, dev, &fops_ext_mac_addr);

	debugfs_create_u32("rf_wfidx", 0600, dir, &dev->debugfs_rf_wf);
	debugfs_create_u32("rf_regidx", 0600, dir, &dev->debugfs_rf_reg);
	debugfs_create_file_unsafe("rf_regval", 0600, dir, dev,
				   &fops_rf_reg);
	अगर (is_mt7663(&dev->mt76))
		debugfs_create_file("chip_config", 0600, dir, dev,
				    &fops_config);
	अगर (mt76_is_sdio(&dev->mt76))
		debugfs_create_devm_seqfile(dev->mt76.dev, "sched-quota", dir,
					    mt7663s_sched_quota_पढ़ो);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt7615_init_debugfs);
