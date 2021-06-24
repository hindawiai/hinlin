<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2016 Felix Fietkau <nbd@nbd.name>
 */

#समावेश <linux/debugfs.h>
#समावेश "mt76x02.h"

अटल पूर्णांक
mt76x02_ampdu_stat_show(काष्ठा seq_file *file, व्योम *data)
अणु
	काष्ठा mt76x02_dev *dev = file->निजी;
	पूर्णांक i, j;

	क्रम (i = 0; i < 4; i++) अणु
		seq_माला_दो(file, "Length: ");
		क्रम (j = 0; j < 8; j++)
			seq_म_लिखो(file, "%8d | ", i * 8 + j + 1);
		seq_माला_दो(file, "\n");
		seq_माला_दो(file, "Count:  ");
		क्रम (j = 0; j < 8; j++)
			seq_म_लिखो(file, "%8d | ",
				   dev->mt76.aggr_stats[i * 8 + j]);
		seq_माला_दो(file, "\n");
		seq_माला_दो(file, "--------");
		क्रम (j = 0; j < 8; j++)
			seq_माला_दो(file, "-----------");
		seq_माला_दो(file, "\n");
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(mt76x02_ampdu_stat);

अटल पूर्णांक पढ़ो_txघातer(काष्ठा seq_file *file, व्योम *data)
अणु
	काष्ठा mt76x02_dev *dev = dev_get_drvdata(file->निजी);

	seq_म_लिखो(file, "Target power: %d\n", dev->target_घातer);

	mt76_seq_माला_दो_array(file, "Delta", dev->target_घातer_delta,
			    ARRAY_SIZE(dev->target_घातer_delta));
	वापस 0;
पूर्ण

अटल पूर्णांक
mt76x02_dfs_stat_show(काष्ठा seq_file *file, व्योम *data)
अणु
	काष्ठा mt76x02_dev *dev = file->निजी;
	काष्ठा mt76x02_dfs_pattern_detector *dfs_pd = &dev->dfs_pd;
	पूर्णांक i;

	seq_म_लिखो(file, "allocated sequences:\t%d\n",
		   dfs_pd->seq_stats.seq_pool_len);
	seq_म_लिखो(file, "used sequences:\t\t%d\n",
		   dfs_pd->seq_stats.seq_len);
	seq_माला_दो(file, "\n");

	क्रम (i = 0; i < MT_DFS_NUM_ENGINES; i++) अणु
		seq_म_लिखो(file, "engine: %d\n", i);
		seq_म_लिखो(file, "  hw pattern detected:\t%d\n",
			   dfs_pd->stats[i].hw_pattern);
		seq_म_लिखो(file, "  hw pulse discarded:\t%d\n",
			   dfs_pd->stats[i].hw_pulse_discarded);
		seq_म_लिखो(file, "  sw pattern detected:\t%d\n",
			   dfs_pd->stats[i].sw_pattern);
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(mt76x02_dfs_stat);

अटल पूर्णांक पढ़ो_agc(काष्ठा seq_file *file, व्योम *data)
अणु
	काष्ठा mt76x02_dev *dev = dev_get_drvdata(file->निजी);

	seq_म_लिखो(file, "avg_rssi: %d\n", dev->cal.avg_rssi_all);
	seq_म_लिखो(file, "low_gain: %d\n", dev->cal.low_gain);
	seq_म_लिखो(file, "false_cca: %d\n", dev->cal.false_cca);
	seq_म_लिखो(file, "agc_gain_adjust: %d\n", dev->cal.agc_gain_adjust);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt76_edcca_set(व्योम *data, u64 val)
अणु
	काष्ठा mt76x02_dev *dev = data;
	क्रमागत nl80211_dfs_regions region = dev->mt76.region;

	mutex_lock(&dev->mt76.mutex);

	dev->ed_monitor_enabled = !!val;
	dev->ed_monitor = dev->ed_monitor_enabled &&
			  region == NL80211_DFS_ETSI;
	mt76x02_edcca_init(dev);

	mutex_unlock(&dev->mt76.mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt76_edcca_get(व्योम *data, u64 *val)
अणु
	काष्ठा mt76x02_dev *dev = data;

	*val = dev->ed_monitor_enabled;
	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(fops_edcca, mt76_edcca_get, mt76_edcca_set,
			 "%lld\n");

व्योम mt76x02_init_debugfs(काष्ठा mt76x02_dev *dev)
अणु
	काष्ठा dentry *dir;

	dir = mt76_रेजिस्टर_debugfs(&dev->mt76);
	अगर (!dir)
		वापस;

	debugfs_create_devm_seqfile(dev->mt76.dev, "xmit-queues", dir,
				    mt76_queues_पढ़ो);
	debugfs_create_u8("temperature", 0400, dir, &dev->cal.temp);
	debugfs_create_bool("tpc", 0600, dir, &dev->enable_tpc);

	debugfs_create_file("edcca", 0600, dir, dev, &fops_edcca);
	debugfs_create_file("ampdu_stat", 0400, dir, dev, &mt76x02_ampdu_stat_fops);
	debugfs_create_file("dfs_stats", 0400, dir, dev, &mt76x02_dfs_stat_fops);
	debugfs_create_devm_seqfile(dev->mt76.dev, "txpower", dir,
				    पढ़ो_txघातer);

	debugfs_create_devm_seqfile(dev->mt76.dev, "agc", dir, पढ़ो_agc);

	debugfs_create_u32("tx_hang_reset", 0400, dir, &dev->tx_hang_reset);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x02_init_debugfs);
