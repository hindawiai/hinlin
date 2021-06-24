<शैली गुरु>
// SPDX-License-Identअगरier: ISC

#समावेश "mt7603.h"

अटल पूर्णांक
mt7603_reset_पढ़ो(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा mt7603_dev *dev = dev_get_drvdata(s->निजी);
	अटल स्थिर अक्षर * स्थिर reset_cause_str[] = अणु
		[RESET_CAUSE_TX_HANG] = "TX hang",
		[RESET_CAUSE_TX_BUSY] = "TX DMA busy stuck",
		[RESET_CAUSE_RX_BUSY] = "RX DMA busy stuck",
		[RESET_CAUSE_RX_PSE_BUSY] = "RX PSE busy stuck",
		[RESET_CAUSE_BEACON_STUCK] = "Beacon stuck",
		[RESET_CAUSE_MCU_HANG] = "MCU hang",
		[RESET_CAUSE_RESET_FAILED] = "PSE reset failed",
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(reset_cause_str); i++) अणु
		अगर (!reset_cause_str[i])
			जारी;

		seq_म_लिखो(s, "%20s: %u\n", reset_cause_str[i],
			   dev->reset_cause[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7603_radio_पढ़ो(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा mt7603_dev *dev = dev_get_drvdata(s->निजी);

	seq_म_लिखो(s, "Sensitivity: %d\n", dev->sensitivity);
	seq_म_लिखो(s, "False CCA: ofdm=%d cck=%d\n",
		   dev->false_cca_ofdm, dev->false_cca_cck);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7603_edcca_set(व्योम *data, u64 val)
अणु
	काष्ठा mt7603_dev *dev = data;

	mutex_lock(&dev->mt76.mutex);

	dev->ed_monitor_enabled = !!val;
	dev->ed_monitor = dev->ed_monitor_enabled &&
			  dev->mt76.region == NL80211_DFS_ETSI;
	mt7603_init_edcca(dev);

	mutex_unlock(&dev->mt76.mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7603_edcca_get(व्योम *data, u64 *val)
अणु
	काष्ठा mt7603_dev *dev = data;

	*val = dev->ed_monitor_enabled;
	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(fops_edcca, mt7603_edcca_get,
			 mt7603_edcca_set, "%lld\n");

अटल पूर्णांक
mt7603_ampdu_stat_show(काष्ठा seq_file *file, व्योम *data)
अणु
	काष्ठा mt7603_dev *dev = file->निजी;
	पूर्णांक bound[3], i, range;

	range = mt76_rr(dev, MT_AGG_ASRCR);
	क्रम (i = 0; i < ARRAY_SIZE(bound); i++)
		bound[i] = MT_AGG_ASRCR_RANGE(range, i) + 1;

	seq_म_लिखो(file, "Length: %8d | ", bound[0]);
	क्रम (i = 0; i < ARRAY_SIZE(bound) - 1; i++)
		seq_म_लिखो(file, "%3d -%3d | ",
			   bound[i], bound[i + 1]);
	seq_माला_दो(file, "\nCount:  ");
	क्रम (i = 0; i < ARRAY_SIZE(bound); i++)
		seq_म_लिखो(file, "%8d | ", dev->mt76.aggr_stats[i]);
	seq_माला_दो(file, "\n");

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(mt7603_ampdu_stat);

व्योम mt7603_init_debugfs(काष्ठा mt7603_dev *dev)
अणु
	काष्ठा dentry *dir;

	dir = mt76_रेजिस्टर_debugfs(&dev->mt76);
	अगर (!dir)
		वापस;

	debugfs_create_file("ampdu_stat", 0400, dir, dev,
			     &mt7603_ampdu_stat_fops);
	debugfs_create_devm_seqfile(dev->mt76.dev, "xmit-queues", dir,
				    mt76_queues_पढ़ो);
	debugfs_create_file("edcca", 0600, dir, dev, &fops_edcca);
	debugfs_create_u32("reset_test", 0600, dir, &dev->reset_test);
	debugfs_create_devm_seqfile(dev->mt76.dev, "reset", dir,
				    mt7603_reset_पढ़ो);
	debugfs_create_devm_seqfile(dev->mt76.dev, "radio", dir,
				    mt7603_radio_पढ़ो);
	debugfs_create_u8("sensitivity_limit", 0600, dir,
			    &dev->sensitivity_limit);
	debugfs_create_bool("dynamic_sensitivity", 0600, dir,
			    &dev->dynamic_sensitivity);
पूर्ण
