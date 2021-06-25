<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Felix Fietkau <nbd@खोलोwrt.org>
 * Copyright (C) 2015 Jakub Kicinski <kubakici@wp.pl>
 */

#समावेश <linux/debugfs.h>

#समावेश "mt7601u.h"
#समावेश "eeprom.h"

अटल पूर्णांक
mt76_reg_set(व्योम *data, u64 val)
अणु
	काष्ठा mt7601u_dev *dev = data;

	mt76_wr(dev, dev->debugfs_reg, val);
	वापस 0;
पूर्ण

अटल पूर्णांक
mt76_reg_get(व्योम *data, u64 *val)
अणु
	काष्ठा mt7601u_dev *dev = data;

	*val = mt76_rr(dev, dev->debugfs_reg);
	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(fops_regval, mt76_reg_get, mt76_reg_set, "0x%08llx\n");

अटल पूर्णांक
mt7601u_ampdu_stat_show(काष्ठा seq_file *file, व्योम *data)
अणु
	काष्ठा mt7601u_dev *dev = file->निजी;
	पूर्णांक i, j;

#घोषणा stat_म_लिखो(grp, off, name)					\
	seq_म_लिखो(file, #name ":\t%llu\n", dev->stats.grp[off])

	stat_म_लिखो(rx_stat, 0, rx_crc_err);
	stat_म_लिखो(rx_stat, 1, rx_phy_err);
	stat_म_लिखो(rx_stat, 2, rx_false_cca);
	stat_म_लिखो(rx_stat, 3, rx_plcp_err);
	stat_म_लिखो(rx_stat, 4, rx_fअगरo_overflow);
	stat_म_लिखो(rx_stat, 5, rx_duplicate);

	stat_म_लिखो(tx_stat, 0, tx_fail_cnt);
	stat_म_लिखो(tx_stat, 1, tx_bcn_cnt);
	stat_म_लिखो(tx_stat, 2, tx_success);
	stat_म_लिखो(tx_stat, 3, tx_retransmit);
	stat_म_लिखो(tx_stat, 4, tx_zero_len);
	stat_म_लिखो(tx_stat, 5, tx_underflow);

	stat_म_लिखो(aggr_stat, 0, non_aggr_tx);
	stat_म_लिखो(aggr_stat, 1, aggr_tx);

	stat_म_लिखो(zero_len_del, 0, tx_zero_len_del);
	stat_म_लिखो(zero_len_del, 1, rx_zero_len_del);
#अघोषित stat_म_लिखो

	seq_माला_दो(file, "Aggregations stats:\n");
	क्रम (i = 0; i < 4; i++) अणु
		क्रम (j = 0; j < 8; j++)
			seq_म_लिखो(file, "%08llx ",
				   dev->stats.aggr_n[i * 8 + j]);
		seq_अ_दो(file, '\n');
	पूर्ण

	seq_म_लिखो(file, "recent average AMPDU len: %d\n",
		   atomic_पढ़ो(&dev->avg_ampdu_len));

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(mt7601u_ampdu_stat);

अटल पूर्णांक
mt7601u_eeprom_param_show(काष्ठा seq_file *file, व्योम *data)
अणु
	काष्ठा mt7601u_dev *dev = file->निजी;
	काष्ठा mt7601u_rate_घातer *rp = &dev->ee->घातer_rate_table;
	काष्ठा tssi_data *td = &dev->ee->tssi_data;
	पूर्णांक i;

	seq_म_लिखो(file, "RF freq offset: %hhx\n", dev->ee->rf_freq_off);
	seq_म_लिखो(file, "RSSI offset: %hhx %hhx\n",
		   dev->ee->rssi_offset[0], dev->ee->rssi_offset[1]);
	seq_म_लिखो(file, "Reference temp: %hhx\n", dev->ee->ref_temp);
	seq_म_लिखो(file, "LNA gain: %hhx\n", dev->ee->lna_gain);
	seq_म_लिखो(file, "Reg channels: %hhu-%hhu\n", dev->ee->reg.start,
		   dev->ee->reg.start + dev->ee->reg.num - 1);

	seq_माला_दो(file, "Per rate power:\n");
	क्रम (i = 0; i < 2; i++)
		seq_म_लिखो(file, "\t raw:%02hhx bw20:%02hhx bw40:%02hhx\n",
			   rp->cck[i].raw, rp->cck[i].bw20, rp->cck[i].bw40);
	क्रम (i = 0; i < 4; i++)
		seq_म_लिखो(file, "\t raw:%02hhx bw20:%02hhx bw40:%02hhx\n",
			   rp->ofdm[i].raw, rp->ofdm[i].bw20, rp->ofdm[i].bw40);
	क्रम (i = 0; i < 4; i++)
		seq_म_लिखो(file, "\t raw:%02hhx bw20:%02hhx bw40:%02hhx\n",
			   rp->ht[i].raw, rp->ht[i].bw20, rp->ht[i].bw40);

	seq_माला_दो(file, "Per channel power:\n");
	क्रम (i = 0; i < 7; i++)
		seq_म_लिखो(file, "\t tx_power  ch%u:%02hhx ch%u:%02hhx\n",
			   i * 2 + 1, dev->ee->chan_pwr[i * 2],
			   i * 2 + 2, dev->ee->chan_pwr[i * 2 + 1]);

	अगर (!dev->ee->tssi_enabled)
		वापस 0;

	seq_माला_दो(file, "TSSI:\n");
	seq_म_लिखो(file, "\t slope:%02hhx\n", td->slope);
	seq_म_लिखो(file, "\t offset=%02hhx %02hhx %02hhx\n",
		   td->offset[0], td->offset[1], td->offset[2]);
	seq_म_लिखो(file, "\t delta_off:%08x\n", td->tx0_delta_offset);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(mt7601u_eeprom_param);

व्योम mt7601u_init_debugfs(काष्ठा mt7601u_dev *dev)
अणु
	काष्ठा dentry *dir;

	dir = debugfs_create_dir("mt7601u", dev->hw->wiphy->debugfsdir);
	अगर (!dir)
		वापस;

	debugfs_create_u8("temperature", 0400, dir, &dev->raw_temp);
	debugfs_create_u32("temp_mode", 0400, dir, &dev->temp_mode);

	debugfs_create_u32("regidx", 0600, dir, &dev->debugfs_reg);
	debugfs_create_file("regval", 0600, dir, dev, &fops_regval);
	debugfs_create_file("ampdu_stat", 0400, dir, dev, &mt7601u_ampdu_stat_fops);
	debugfs_create_file("eeprom_param", 0400, dir, dev, &mt7601u_eeprom_param_fops);
पूर्ण
