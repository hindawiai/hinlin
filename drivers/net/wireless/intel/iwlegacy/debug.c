<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
 *
 * Copyright(c) 2008 - 2011 Intel Corporation. All rights reserved.
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <ilw@linux.पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *****************************************************************************/
#समावेश <linux/ieee80211.h>
#समावेश <linux/export.h>
#समावेश <net/mac80211.h>

#समावेश "common.h"

अटल व्योम
il_clear_traffic_stats(काष्ठा il_priv *il)
अणु
	स_रखो(&il->tx_stats, 0, माप(काष्ठा traffic_stats));
	स_रखो(&il->rx_stats, 0, माप(काष्ठा traffic_stats));
पूर्ण

/*
 * il_update_stats function record all the MGMT, CTRL and DATA pkt क्रम
 * both TX and Rx . Use debugfs to display the rx/rx_stats
 */
व्योम
il_update_stats(काष्ठा il_priv *il, bool is_tx, __le16 fc, u16 len)
अणु
	काष्ठा traffic_stats *stats;

	अगर (is_tx)
		stats = &il->tx_stats;
	अन्यथा
		stats = &il->rx_stats;

	अगर (ieee80211_is_mgmt(fc)) अणु
		चयन (fc & cpu_to_le16(IEEE80211_FCTL_STYPE)) अणु
		हाल cpu_to_le16(IEEE80211_STYPE_ASSOC_REQ):
			stats->mgmt[MANAGEMENT_ASSOC_REQ]++;
			अवरोध;
		हाल cpu_to_le16(IEEE80211_STYPE_ASSOC_RESP):
			stats->mgmt[MANAGEMENT_ASSOC_RESP]++;
			अवरोध;
		हाल cpu_to_le16(IEEE80211_STYPE_REASSOC_REQ):
			stats->mgmt[MANAGEMENT_REASSOC_REQ]++;
			अवरोध;
		हाल cpu_to_le16(IEEE80211_STYPE_REASSOC_RESP):
			stats->mgmt[MANAGEMENT_REASSOC_RESP]++;
			अवरोध;
		हाल cpu_to_le16(IEEE80211_STYPE_PROBE_REQ):
			stats->mgmt[MANAGEMENT_PROBE_REQ]++;
			अवरोध;
		हाल cpu_to_le16(IEEE80211_STYPE_PROBE_RESP):
			stats->mgmt[MANAGEMENT_PROBE_RESP]++;
			अवरोध;
		हाल cpu_to_le16(IEEE80211_STYPE_BEACON):
			stats->mgmt[MANAGEMENT_BEACON]++;
			अवरोध;
		हाल cpu_to_le16(IEEE80211_STYPE_ATIM):
			stats->mgmt[MANAGEMENT_ATIM]++;
			अवरोध;
		हाल cpu_to_le16(IEEE80211_STYPE_DISASSOC):
			stats->mgmt[MANAGEMENT_DISASSOC]++;
			अवरोध;
		हाल cpu_to_le16(IEEE80211_STYPE_AUTH):
			stats->mgmt[MANAGEMENT_AUTH]++;
			अवरोध;
		हाल cpu_to_le16(IEEE80211_STYPE_DEAUTH):
			stats->mgmt[MANAGEMENT_DEAUTH]++;
			अवरोध;
		हाल cpu_to_le16(IEEE80211_STYPE_ACTION):
			stats->mgmt[MANAGEMENT_ACTION]++;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (ieee80211_is_ctl(fc)) अणु
		चयन (fc & cpu_to_le16(IEEE80211_FCTL_STYPE)) अणु
		हाल cpu_to_le16(IEEE80211_STYPE_BACK_REQ):
			stats->ctrl[CONTROL_BACK_REQ]++;
			अवरोध;
		हाल cpu_to_le16(IEEE80211_STYPE_BACK):
			stats->ctrl[CONTROL_BACK]++;
			अवरोध;
		हाल cpu_to_le16(IEEE80211_STYPE_PSPOLL):
			stats->ctrl[CONTROL_PSPOLL]++;
			अवरोध;
		हाल cpu_to_le16(IEEE80211_STYPE_RTS):
			stats->ctrl[CONTROL_RTS]++;
			अवरोध;
		हाल cpu_to_le16(IEEE80211_STYPE_CTS):
			stats->ctrl[CONTROL_CTS]++;
			अवरोध;
		हाल cpu_to_le16(IEEE80211_STYPE_ACK):
			stats->ctrl[CONTROL_ACK]++;
			अवरोध;
		हाल cpu_to_le16(IEEE80211_STYPE_CFEND):
			stats->ctrl[CONTROL_CFEND]++;
			अवरोध;
		हाल cpu_to_le16(IEEE80211_STYPE_CFENDACK):
			stats->ctrl[CONTROL_CFENDACK]++;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* data */
		stats->data_cnt++;
		stats->data_bytes += len;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(il_update_stats);

/* create and हटाओ of files */
#घोषणा DEBUGFS_ADD_खाता(name, parent, mode) करो अणु			\
	debugfs_create_file(#name, mode, parent, il,			\
			    &il_dbgfs_##name##_ops);			\
पूर्ण जबतक (0)

#घोषणा DEBUGFS_ADD_BOOL(name, parent, ptr) करो अणु			\
	debugfs_create_bool(#name, 0600, parent, ptr);			\
पूर्ण जबतक (0)

/* file operation */
#घोषणा DEBUGFS_READ_FUNC(name)                                         \
अटल sमाप_प्रकार il_dbgfs_##name##_पढ़ो(काष्ठा file *file,               \
					अक्षर __user *user_buf,          \
					माप_प्रकार count, loff_t *ppos);

#घोषणा DEBUGFS_WRITE_FUNC(name)                                        \
अटल sमाप_प्रकार il_dbgfs_##name##_ग_लिखो(काष्ठा file *file,              \
					स्थिर अक्षर __user *user_buf,    \
					माप_प्रकार count, loff_t *ppos);


#घोषणा DEBUGFS_READ_खाता_OPS(name)				\
	DEBUGFS_READ_FUNC(name);				\
अटल स्थिर काष्ठा file_operations il_dbgfs_##name##_ops = अणु	\
	.पढ़ो = il_dbgfs_##name##_पढ़ो,				\
	.खोलो = simple_खोलो,					\
	.llseek = generic_file_llseek,				\
पूर्ण;

#घोषणा DEBUGFS_WRITE_खाता_OPS(name)				\
	DEBUGFS_WRITE_FUNC(name);				\
अटल स्थिर काष्ठा file_operations il_dbgfs_##name##_ops = अणु	\
	.ग_लिखो = il_dbgfs_##name##_ग_लिखो,			\
	.खोलो = simple_खोलो,					\
	.llseek = generic_file_llseek,				\
पूर्ण;

#घोषणा DEBUGFS_READ_WRITE_खाता_OPS(name)			\
	DEBUGFS_READ_FUNC(name);				\
	DEBUGFS_WRITE_FUNC(name);				\
अटल स्थिर काष्ठा file_operations il_dbgfs_##name##_ops = अणु	\
	.ग_लिखो = il_dbgfs_##name##_ग_लिखो,			\
	.पढ़ो = il_dbgfs_##name##_पढ़ो,				\
	.खोलो = simple_खोलो,					\
	.llseek = generic_file_llseek,				\
पूर्ण;

अटल स्थिर अक्षर *
il_get_mgmt_string(पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	IL_CMD(MANAGEMENT_ASSOC_REQ);
	IL_CMD(MANAGEMENT_ASSOC_RESP);
	IL_CMD(MANAGEMENT_REASSOC_REQ);
	IL_CMD(MANAGEMENT_REASSOC_RESP);
	IL_CMD(MANAGEMENT_PROBE_REQ);
	IL_CMD(MANAGEMENT_PROBE_RESP);
	IL_CMD(MANAGEMENT_BEACON);
	IL_CMD(MANAGEMENT_ATIM);
	IL_CMD(MANAGEMENT_DISASSOC);
	IL_CMD(MANAGEMENT_AUTH);
	IL_CMD(MANAGEMENT_DEAUTH);
	IL_CMD(MANAGEMENT_ACTION);
	शेष:
		वापस "UNKNOWN";

	पूर्ण
पूर्ण

अटल स्थिर अक्षर *
il_get_ctrl_string(पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	IL_CMD(CONTROL_BACK_REQ);
	IL_CMD(CONTROL_BACK);
	IL_CMD(CONTROL_PSPOLL);
	IL_CMD(CONTROL_RTS);
	IL_CMD(CONTROL_CTS);
	IL_CMD(CONTROL_ACK);
	IL_CMD(CONTROL_CFEND);
	IL_CMD(CONTROL_CFENDACK);
	शेष:
		वापस "UNKNOWN";

	पूर्ण
पूर्ण

अटल sमाप_प्रकार
il_dbgfs_tx_stats_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf, माप_प्रकार count,
		       loff_t *ppos)
अणु

	काष्ठा il_priv *il = file->निजी_data;
	अक्षर *buf;
	पूर्णांक pos = 0;

	पूर्णांक cnt;
	sमाप_प्रकार ret;
	स्थिर माप_प्रकार bufsz =
	    100 + माप(अक्षर) * 50 * (MANAGEMENT_MAX + CONTROL_MAX);
	buf = kzalloc(bufsz, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;
	pos += scnम_लिखो(buf + pos, bufsz - pos, "Management:\n");
	क्रम (cnt = 0; cnt < MANAGEMENT_MAX; cnt++) अणु
		pos +=
		    scnम_लिखो(buf + pos, bufsz - pos, "\t%25s\t\t: %u\n",
			      il_get_mgmt_string(cnt), il->tx_stats.mgmt[cnt]);
	पूर्ण
	pos += scnम_लिखो(buf + pos, bufsz - pos, "Control\n");
	क्रम (cnt = 0; cnt < CONTROL_MAX; cnt++) अणु
		pos +=
		    scnम_लिखो(buf + pos, bufsz - pos, "\t%25s\t\t: %u\n",
			      il_get_ctrl_string(cnt), il->tx_stats.ctrl[cnt]);
	पूर्ण
	pos += scnम_लिखो(buf + pos, bufsz - pos, "Data:\n");
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "\tcnt: %u\n",
		      il->tx_stats.data_cnt);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "\tbytes: %llu\n",
		      il->tx_stats.data_bytes);
	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार
il_dbgfs_clear_traffic_stats_ग_लिखो(काष्ठा file *file,
				   स्थिर अक्षर __user *user_buf, माप_प्रकार count,
				   loff_t *ppos)
अणु
	काष्ठा il_priv *il = file->निजी_data;
	u32 clear_flag;
	अक्षर buf[8];
	पूर्णांक buf_size;

	स_रखो(buf, 0, माप(buf));
	buf_size = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, buf_size))
		वापस -EFAULT;
	अगर (माला_पूछो(buf, "%x", &clear_flag) != 1)
		वापस -EFAULT;
	il_clear_traffic_stats(il);

	वापस count;
पूर्ण

अटल sमाप_प्रकार
il_dbgfs_rx_stats_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf, माप_प्रकार count,
		       loff_t *ppos)
अणु

	काष्ठा il_priv *il = file->निजी_data;
	अक्षर *buf;
	पूर्णांक pos = 0;
	पूर्णांक cnt;
	sमाप_प्रकार ret;
	स्थिर माप_प्रकार bufsz =
	    100 + माप(अक्षर) * 50 * (MANAGEMENT_MAX + CONTROL_MAX);
	buf = kzalloc(bufsz, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	pos += scnम_लिखो(buf + pos, bufsz - pos, "Management:\n");
	क्रम (cnt = 0; cnt < MANAGEMENT_MAX; cnt++) अणु
		pos +=
		    scnम_लिखो(buf + pos, bufsz - pos, "\t%25s\t\t: %u\n",
			      il_get_mgmt_string(cnt), il->rx_stats.mgmt[cnt]);
	पूर्ण
	pos += scnम_लिखो(buf + pos, bufsz - pos, "Control:\n");
	क्रम (cnt = 0; cnt < CONTROL_MAX; cnt++) अणु
		pos +=
		    scnम_लिखो(buf + pos, bufsz - pos, "\t%25s\t\t: %u\n",
			      il_get_ctrl_string(cnt), il->rx_stats.ctrl[cnt]);
	पूर्ण
	pos += scnम_लिखो(buf + pos, bufsz - pos, "Data:\n");
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "\tcnt: %u\n",
		      il->rx_stats.data_cnt);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "\tbytes: %llu\n",
		      il->rx_stats.data_bytes);

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
	kमुक्त(buf);
	वापस ret;
पूर्ण

#घोषणा BYTE1_MASK 0x000000ff;
#घोषणा BYTE2_MASK 0x0000ffff;
#घोषणा BYTE3_MASK 0x00ffffff;
अटल sमाप_प्रकार
il_dbgfs_sram_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf, माप_प्रकार count,
		   loff_t *ppos)
अणु
	u32 val;
	अक्षर *buf;
	sमाप_प्रकार ret;
	पूर्णांक i;
	पूर्णांक pos = 0;
	काष्ठा il_priv *il = file->निजी_data;
	माप_प्रकार bufsz;

	/* शेष is to dump the entire data segment */
	अगर (!il->dbgfs_sram_offset && !il->dbgfs_sram_len) अणु
		il->dbgfs_sram_offset = 0x800000;
		अगर (il->ucode_type == UCODE_INIT)
			il->dbgfs_sram_len = il->ucode_init_data.len;
		अन्यथा
			il->dbgfs_sram_len = il->ucode_data.len;
	पूर्ण
	bufsz = 30 + il->dbgfs_sram_len * माप(अक्षर) * 10;
	buf = kदो_स्मृति(bufsz, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "sram_len: 0x%x\n",
		      il->dbgfs_sram_len);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "sram_offset: 0x%x\n",
		      il->dbgfs_sram_offset);
	क्रम (i = il->dbgfs_sram_len; i > 0; i -= 4) अणु
		val =
		    il_पढ़ो_targ_mem(il,
				     il->dbgfs_sram_offset +
				     il->dbgfs_sram_len - i);
		अगर (i < 4) अणु
			चयन (i) अणु
			हाल 1:
				val &= BYTE1_MASK;
				अवरोध;
			हाल 2:
				val &= BYTE2_MASK;
				अवरोध;
			हाल 3:
				val &= BYTE3_MASK;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!(i % 16))
			pos += scnम_लिखो(buf + pos, bufsz - pos, "\n");
		pos += scnम_लिखो(buf + pos, bufsz - pos, "0x%08x ", val);
	पूर्ण
	pos += scnम_लिखो(buf + pos, bufsz - pos, "\n");

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार
il_dbgfs_sram_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
		    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा il_priv *il = file->निजी_data;
	अक्षर buf[64];
	पूर्णांक buf_size;
	u32 offset, len;

	स_रखो(buf, 0, माप(buf));
	buf_size = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, buf_size))
		वापस -EFAULT;

	अगर (माला_पूछो(buf, "%x,%x", &offset, &len) == 2) अणु
		il->dbgfs_sram_offset = offset;
		il->dbgfs_sram_len = len;
	पूर्ण अन्यथा अणु
		il->dbgfs_sram_offset = 0;
		il->dbgfs_sram_len = 0;
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार
il_dbgfs_stations_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf, माप_प्रकार count,
		       loff_t *ppos)
अणु
	काष्ठा il_priv *il = file->निजी_data;
	काष्ठा il_station_entry *station;
	पूर्णांक max_sta = il->hw_params.max_stations;
	अक्षर *buf;
	पूर्णांक i, j, pos = 0;
	sमाप_प्रकार ret;
	/* Add 30 क्रम initial string */
	स्थिर माप_प्रकार bufsz = 30 + माप(अक्षर) * 500 * (il->num_stations);

	buf = kदो_स्मृति(bufsz, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "num of stations: %d\n\n",
		      il->num_stations);

	क्रम (i = 0; i < max_sta; i++) अणु
		station = &il->stations[i];
		अगर (!station->used)
			जारी;
		pos +=
		    scnम_लिखो(buf + pos, bufsz - pos,
			      "station %d - addr: %pM, flags: %#x\n", i,
			      station->sta.sta.addr,
			      station->sta.station_flags_msk);
		pos +=
		    scnम_लिखो(buf + pos, bufsz - pos,
			      "TID\tseq_num\ttxq_id\tframes\ttfds\t");
		pos +=
		    scnम_लिखो(buf + pos, bufsz - pos,
			      "start_idx\tbitmap\t\t\trate_n_flags\n");

		क्रम (j = 0; j < MAX_TID_COUNT; j++) अणु
			pos +=
			    scnम_लिखो(buf + pos, bufsz - pos,
				      "%d:\t%#x\t%#x\t%u\t%u\t%u\t\t%#.16llx\t%#x",
				      j, station->tid[j].seq_number,
				      station->tid[j].agg.txq_id,
				      station->tid[j].agg.frame_count,
				      station->tid[j].tfds_in_queue,
				      station->tid[j].agg.start_idx,
				      station->tid[j].agg.biपंचांगap,
				      station->tid[j].agg.rate_n_flags);

			अगर (station->tid[j].agg.रुको_क्रम_ba)
				pos +=
				    scnम_लिखो(buf + pos, bufsz - pos,
					      " - waitforba");
			pos += scnम_लिखो(buf + pos, bufsz - pos, "\n");
		पूर्ण

		pos += scnम_लिखो(buf + pos, bufsz - pos, "\n");
	पूर्ण

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार
il_dbgfs_nvm_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf, माप_प्रकार count,
		  loff_t *ppos)
अणु
	sमाप_प्रकार ret;
	काष्ठा il_priv *il = file->निजी_data;
	पूर्णांक pos = 0, ofs = 0, buf_size = 0;
	स्थिर u8 *ptr;
	अक्षर *buf;
	u16 eeprom_ver;
	माप_प्रकार eeprom_len = il->cfg->eeprom_size;
	buf_size = 4 * eeprom_len + 256;

	अगर (eeprom_len % 16) अणु
		IL_ERR("NVM size is not multiple of 16.\n");
		वापस -ENODATA;
	पूर्ण

	ptr = il->eeprom;
	अगर (!ptr) अणु
		IL_ERR("Invalid EEPROM memory\n");
		वापस -ENOMEM;
	पूर्ण

	/* 4 अक्षरacters क्रम byte 0xYY */
	buf = kzalloc(buf_size, GFP_KERNEL);
	अगर (!buf) अणु
		IL_ERR("Can not allocate Buffer\n");
		वापस -ENOMEM;
	पूर्ण
	eeprom_ver = il_eeprom_query16(il, EEPROM_VERSION);
	pos +=
	    scnम_लिखो(buf + pos, buf_size - pos, "EEPROM " "version: 0x%x\n",
		      eeprom_ver);
	क्रम (ofs = 0; ofs < eeprom_len; ofs += 16) अणु
		pos += scnम_लिखो(buf + pos, buf_size - pos, "0x%.4x %16ph\n",
				 ofs, ptr + ofs);
	पूर्ण

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार
il_dbgfs_channels_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf, माप_प्रकार count,
		       loff_t *ppos)
अणु
	काष्ठा il_priv *il = file->निजी_data;
	काष्ठा ieee80211_channel *channels = शून्य;
	स्थिर काष्ठा ieee80211_supported_band *supp_band = शून्य;
	पूर्णांक pos = 0, i, bufsz = PAGE_SIZE;
	अक्षर *buf;
	sमाप_प्रकार ret;

	अगर (!test_bit(S_GEO_CONFIGURED, &il->status))
		वापस -EAGAIN;

	buf = kzalloc(bufsz, GFP_KERNEL);
	अगर (!buf) अणु
		IL_ERR("Can not allocate Buffer\n");
		वापस -ENOMEM;
	पूर्ण

	supp_band = il_get_hw_mode(il, NL80211_BAND_2GHZ);
	अगर (supp_band) अणु
		channels = supp_band->channels;

		pos +=
		    scnम_लिखो(buf + pos, bufsz - pos,
			      "Displaying %d channels in 2.4GHz band 802.11bg):\n",
			      supp_band->n_channels);

		क्रम (i = 0; i < supp_band->n_channels; i++)
			pos +=
			    scnम_लिखो(buf + pos, bufsz - pos,
				      "%d: %ddBm: BSS%s%s, %s.\n",
				      channels[i].hw_value,
				      channels[i].max_घातer,
				      channels[i].
				      flags & IEEE80211_CHAN_RADAR ?
				      " (IEEE 802.11h required)" : "",
				      ((channels[i].
					flags & IEEE80211_CHAN_NO_IR) ||
				       (channels[i].
					flags & IEEE80211_CHAN_RADAR)) ? "" :
				      ", IBSS",
				      channels[i].
				      flags & IEEE80211_CHAN_NO_IR ?
				      "passive only" : "active/passive");
	पूर्ण
	supp_band = il_get_hw_mode(il, NL80211_BAND_5GHZ);
	अगर (supp_band) अणु
		channels = supp_band->channels;

		pos +=
		    scnम_लिखो(buf + pos, bufsz - pos,
			      "Displaying %d channels in 5.2GHz band (802.11a)\n",
			      supp_band->n_channels);

		क्रम (i = 0; i < supp_band->n_channels; i++)
			pos +=
			    scnम_लिखो(buf + pos, bufsz - pos,
				      "%d: %ddBm: BSS%s%s, %s.\n",
				      channels[i].hw_value,
				      channels[i].max_घातer,
				      channels[i].
				      flags & IEEE80211_CHAN_RADAR ?
				      " (IEEE 802.11h required)" : "",
				      ((channels[i].
					flags & IEEE80211_CHAN_NO_IR) ||
				       (channels[i].
					flags & IEEE80211_CHAN_RADAR)) ? "" :
				      ", IBSS",
				      channels[i].
				      flags & IEEE80211_CHAN_NO_IR ?
				      "passive only" : "active/passive");
	पूर्ण
	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार
il_dbgfs_status_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf, माप_प्रकार count,
		     loff_t *ppos)
अणु

	काष्ठा il_priv *il = file->निजी_data;
	अक्षर buf[512];
	पूर्णांक pos = 0;
	स्थिर माप_प्रकार bufsz = माप(buf);

	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "S_HCMD_ACTIVE:\t %d\n",
		      test_bit(S_HCMD_ACTIVE, &il->status));
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "S_INT_ENABLED:\t %d\n",
		      test_bit(S_INT_ENABLED, &il->status));
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "S_RFKILL:\t %d\n",
		      test_bit(S_RFKILL, &il->status));
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "S_CT_KILL:\t\t %d\n",
		      test_bit(S_CT_KILL, &il->status));
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "S_INIT:\t\t %d\n",
		      test_bit(S_INIT, &il->status));
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "S_ALIVE:\t\t %d\n",
		      test_bit(S_ALIVE, &il->status));
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "S_READY:\t\t %d\n",
		      test_bit(S_READY, &il->status));
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "S_TEMPERATURE:\t %d\n",
		      test_bit(S_TEMPERATURE, &il->status));
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "S_GEO_CONFIGURED:\t %d\n",
		      test_bit(S_GEO_CONFIGURED, &il->status));
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "S_EXIT_PENDING:\t %d\n",
		      test_bit(S_EXIT_PENDING, &il->status));
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "S_STATS:\t %d\n",
		      test_bit(S_STATS, &il->status));
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "S_SCANNING:\t %d\n",
		      test_bit(S_SCANNING, &il->status));
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "S_SCAN_ABORTING:\t %d\n",
		      test_bit(S_SCAN_ABORTING, &il->status));
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "S_SCAN_HW:\t\t %d\n",
		      test_bit(S_SCAN_HW, &il->status));
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "S_POWER_PMI:\t %d\n",
		      test_bit(S_POWER_PMI, &il->status));
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "S_FW_ERROR:\t %d\n",
		      test_bit(S_FW_ERROR, &il->status));
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

अटल sमाप_प्रकार
il_dbgfs_पूर्णांकerrupt_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf, माप_प्रकार count,
			loff_t *ppos)
अणु

	काष्ठा il_priv *il = file->निजी_data;
	पूर्णांक pos = 0;
	पूर्णांक cnt = 0;
	अक्षर *buf;
	पूर्णांक bufsz = 24 * 64;	/* 24 items * 64 अक्षर per item */
	sमाप_प्रकार ret;

	buf = kzalloc(bufsz, GFP_KERNEL);
	अगर (!buf) अणु
		IL_ERR("Can not allocate Buffer\n");
		वापस -ENOMEM;
	पूर्ण

	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "Interrupt Statistics Report:\n");

	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "HW Error:\t\t\t %u\n",
		      il->isr_stats.hw);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "SW Error:\t\t\t %u\n",
		      il->isr_stats.sw);
	अगर (il->isr_stats.sw || il->isr_stats.hw) अणु
		pos +=
		    scnम_लिखो(buf + pos, bufsz - pos,
			      "\tLast Restarting Code:  0x%X\n",
			      il->isr_stats.err_code);
	पूर्ण
#अगर_घोषित CONFIG_IWLEGACY_DEBUG
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "Frame transmitted:\t\t %u\n",
		      il->isr_stats.sch);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "Alive interrupt:\t\t %u\n",
		      il->isr_stats.alive);
#पूर्ण_अगर
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "HW RF KILL switch toggled:\t %u\n",
		      il->isr_stats.rfसमाप्त);

	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "CT KILL:\t\t\t %u\n",
		      il->isr_stats.ctसमाप्त);

	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "Wakeup Interrupt:\t\t %u\n",
		      il->isr_stats.wakeup);

	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "Rx command responses:\t\t %u\n",
		      il->isr_stats.rx);
	क्रम (cnt = 0; cnt < IL_CN_MAX; cnt++) अणु
		अगर (il->isr_stats.handlers[cnt] > 0)
			pos +=
			    scnम_लिखो(buf + pos, bufsz - pos,
				      "\tRx handler[%36s]:\t\t %u\n",
				      il_get_cmd_string(cnt),
				      il->isr_stats.handlers[cnt]);
	पूर्ण

	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "Tx/FH interrupt:\t\t %u\n",
		      il->isr_stats.tx);

	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "Unexpected INTA:\t\t %u\n",
		      il->isr_stats.unhandled);

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार
il_dbgfs_पूर्णांकerrupt_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
			 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा il_priv *il = file->निजी_data;
	अक्षर buf[8];
	पूर्णांक buf_size;
	u32 reset_flag;

	स_रखो(buf, 0, माप(buf));
	buf_size = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, buf_size))
		वापस -EFAULT;
	अगर (माला_पूछो(buf, "%x", &reset_flag) != 1)
		वापस -EFAULT;
	अगर (reset_flag == 0)
		il_clear_isr_stats(il);

	वापस count;
पूर्ण

अटल sमाप_प्रकार
il_dbgfs_qos_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf, माप_प्रकार count,
		  loff_t *ppos)
अणु
	काष्ठा il_priv *il = file->निजी_data;
	पूर्णांक pos = 0, i;
	अक्षर buf[256];
	स्थिर माप_प्रकार bufsz = माप(buf);

	क्रम (i = 0; i < AC_NUM; i++) अणु
		pos +=
		    scnम_लिखो(buf + pos, bufsz - pos,
			      "\tcw_min\tcw_max\taifsn\ttxop\n");
		pos +=
		    scnम_लिखो(buf + pos, bufsz - pos,
			      "AC[%d]\t%u\t%u\t%u\t%u\n", i,
			      il->qos_data.def_qos_parm.ac[i].cw_min,
			      il->qos_data.def_qos_parm.ac[i].cw_max,
			      il->qos_data.def_qos_parm.ac[i].aअगरsn,
			      il->qos_data.def_qos_parm.ac[i].edca_txop);
	पूर्ण

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

अटल sमाप_प्रकार
il_dbgfs_disable_ht40_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
			    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा il_priv *il = file->निजी_data;
	अक्षर buf[8];
	पूर्णांक buf_size;
	पूर्णांक ht40;

	स_रखो(buf, 0, माप(buf));
	buf_size = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, buf_size))
		वापस -EFAULT;
	अगर (माला_पूछो(buf, "%d", &ht40) != 1)
		वापस -EFAULT;
	अगर (!il_is_any_associated(il))
		il->disable_ht40 = ht40 ? true : false;
	अन्यथा अणु
		IL_ERR("Sta associated with AP - "
		       "Change to 40MHz channel support is not allowed\n");
		वापस -EINVAL;
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार
il_dbgfs_disable_ht40_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
			   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा il_priv *il = file->निजी_data;
	अक्षर buf[100];
	पूर्णांक pos = 0;
	स्थिर माप_प्रकार bufsz = माप(buf);

	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "11n 40MHz Mode: %s\n",
		      il->disable_ht40 ? "Disabled" : "Enabled");
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

DEBUGFS_READ_WRITE_खाता_OPS(sram);
DEBUGFS_READ_खाता_OPS(nvm);
DEBUGFS_READ_खाता_OPS(stations);
DEBUGFS_READ_खाता_OPS(channels);
DEBUGFS_READ_खाता_OPS(status);
DEBUGFS_READ_WRITE_खाता_OPS(पूर्णांकerrupt);
DEBUGFS_READ_खाता_OPS(qos);
DEBUGFS_READ_WRITE_खाता_OPS(disable_ht40);

अटल sमाप_प्रकार
il_dbgfs_tx_queue_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf, माप_प्रकार count,
		       loff_t *ppos)
अणु

	काष्ठा il_priv *il = file->निजी_data;
	काष्ठा il_tx_queue *txq;
	काष्ठा il_queue *q;
	अक्षर *buf;
	पूर्णांक pos = 0;
	पूर्णांक cnt;
	पूर्णांक ret;
	स्थिर माप_प्रकार bufsz =
	    माप(अक्षर) * 64 * il->cfg->num_of_queues;

	अगर (!il->txq) अणु
		IL_ERR("txq not ready\n");
		वापस -EAGAIN;
	पूर्ण
	buf = kzalloc(bufsz, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	क्रम (cnt = 0; cnt < il->hw_params.max_txq_num; cnt++) अणु
		txq = &il->txq[cnt];
		q = &txq->q;
		pos +=
		    scnम_लिखो(buf + pos, bufsz - pos,
			      "hwq %.2d: read=%u write=%u stop=%d"
			      " swq_id=%#.2x (ac %d/hwq %d)\n", cnt,
			      q->पढ़ो_ptr, q->ग_लिखो_ptr,
			      !!test_bit(cnt, il->queue_stopped),
			      txq->swq_id, txq->swq_id & 3,
			      (txq->swq_id >> 2) & 0x1f);
		अगर (cnt >= 4)
			जारी;
		/* क्रम the ACs, display the stop count too */
		pos +=
		    scnम_लिखो(buf + pos, bufsz - pos,
			      "        stop-count: %d\n",
			      atomic_पढ़ो(&il->queue_stop_count[cnt]));
	पूर्ण
	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार
il_dbgfs_rx_queue_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf, माप_प्रकार count,
		       loff_t *ppos)
अणु

	काष्ठा il_priv *il = file->निजी_data;
	काष्ठा il_rx_queue *rxq = &il->rxq;
	अक्षर buf[256];
	पूर्णांक pos = 0;
	स्थिर माप_प्रकार bufsz = माप(buf);

	pos += scnम_लिखो(buf + pos, bufsz - pos, "read: %u\n", rxq->पढ़ो);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "write: %u\n", rxq->ग_लिखो);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "free_count: %u\n",
		      rxq->मुक्त_count);
	अगर (rxq->rb_stts) अणु
		pos +=
		    scnम_लिखो(buf + pos, bufsz - pos, "closed_rb_num: %u\n",
			      le16_to_cpu(rxq->rb_stts->
					  बंदd_rb_num) & 0x0FFF);
	पूर्ण अन्यथा अणु
		pos +=
		    scnम_लिखो(buf + pos, bufsz - pos,
			      "closed_rb_num: Not Allocated\n");
	पूर्ण
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

अटल sमाप_प्रकार
il_dbgfs_ucode_rx_stats_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
			     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा il_priv *il = file->निजी_data;

	वापस il->debugfs_ops->rx_stats_पढ़ो(file, user_buf, count, ppos);
पूर्ण

अटल sमाप_प्रकार
il_dbgfs_ucode_tx_stats_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
			     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा il_priv *il = file->निजी_data;

	वापस il->debugfs_ops->tx_stats_पढ़ो(file, user_buf, count, ppos);
पूर्ण

अटल sमाप_प्रकार
il_dbgfs_ucode_general_stats_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा il_priv *il = file->निजी_data;

	वापस il->debugfs_ops->general_stats_पढ़ो(file, user_buf, count, ppos);
पूर्ण

अटल sमाप_प्रकार
il_dbgfs_sensitivity_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
			  माप_प्रकार count, loff_t *ppos)
अणु

	काष्ठा il_priv *il = file->निजी_data;
	पूर्णांक pos = 0;
	पूर्णांक cnt = 0;
	अक्षर *buf;
	पूर्णांक bufsz = माप(काष्ठा il_sensitivity_data) * 4 + 100;
	sमाप_प्रकार ret;
	काष्ठा il_sensitivity_data *data;

	data = &il->sensitivity_data;
	buf = kzalloc(bufsz, GFP_KERNEL);
	अगर (!buf) अणु
		IL_ERR("Can not allocate Buffer\n");
		वापस -ENOMEM;
	पूर्ण

	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "auto_corr_ofdm:\t\t\t %u\n",
		      data->स्वतः_corr_ofdm);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "auto_corr_ofdm_mrc:\t\t %u\n",
		      data->स्वतः_corr_ofdm_mrc);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "auto_corr_ofdm_x1:\t\t %u\n",
		      data->स्वतः_corr_ofdm_x1);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "auto_corr_ofdm_mrc_x1:\t\t %u\n",
		      data->स्वतः_corr_ofdm_mrc_x1);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "auto_corr_cck:\t\t\t %u\n",
		      data->स्वतः_corr_cck);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "auto_corr_cck_mrc:\t\t %u\n",
		      data->स्वतः_corr_cck_mrc);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "last_bad_plcp_cnt_ofdm:\t\t %u\n",
		      data->last_bad_plcp_cnt_ofdm);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "last_fa_cnt_ofdm:\t\t %u\n",
		      data->last_fa_cnt_ofdm);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "last_bad_plcp_cnt_cck:\t\t %u\n",
		      data->last_bad_plcp_cnt_cck);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "last_fa_cnt_cck:\t\t %u\n",
		      data->last_fa_cnt_cck);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "nrg_curr_state:\t\t\t %u\n",
		      data->nrg_curr_state);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "nrg_prev_state:\t\t\t %u\n",
		      data->nrg_prev_state);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "nrg_value:\t\t\t");
	क्रम (cnt = 0; cnt < 10; cnt++) अणु
		pos +=
		    scnम_लिखो(buf + pos, bufsz - pos, " %u",
			      data->nrg_value[cnt]);
	पूर्ण
	pos += scnम_लिखो(buf + pos, bufsz - pos, "\n");
	pos += scnम_लिखो(buf + pos, bufsz - pos, "nrg_silence_rssi:\t\t");
	क्रम (cnt = 0; cnt < NRG_NUM_PREV_STAT_L; cnt++) अणु
		pos +=
		    scnम_लिखो(buf + pos, bufsz - pos, " %u",
			      data->nrg_silence_rssi[cnt]);
	पूर्ण
	pos += scnम_लिखो(buf + pos, bufsz - pos, "\n");
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "nrg_silence_ref:\t\t %u\n",
		      data->nrg_silence_ref);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "nrg_energy_idx:\t\t\t %u\n",
		      data->nrg_energy_idx);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "nrg_silence_idx:\t\t %u\n",
		      data->nrg_silence_idx);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "nrg_th_cck:\t\t\t %u\n",
		      data->nrg_th_cck);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "nrg_auto_corr_silence_diff:\t %u\n",
		      data->nrg_स्वतः_corr_silence_dअगरf);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "num_in_cck_no_fa:\t\t %u\n",
		      data->num_in_cck_no_fa);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "nrg_th_ofdm:\t\t\t %u\n",
		      data->nrg_th_ofdm);

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार
il_dbgfs_chain_noise_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
			  माप_प्रकार count, loff_t *ppos)
अणु

	काष्ठा il_priv *il = file->निजी_data;
	पूर्णांक pos = 0;
	पूर्णांक cnt = 0;
	अक्षर *buf;
	पूर्णांक bufsz = माप(काष्ठा il_chain_noise_data) * 4 + 100;
	sमाप_प्रकार ret;
	काष्ठा il_chain_noise_data *data;

	data = &il->chain_noise_data;
	buf = kzalloc(bufsz, GFP_KERNEL);
	अगर (!buf) अणु
		IL_ERR("Can not allocate Buffer\n");
		वापस -ENOMEM;
	पूर्ण

	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "active_chains:\t\t\t %u\n",
		      data->active_chains);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "chain_noise_a:\t\t\t %u\n",
		      data->chain_noise_a);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "chain_noise_b:\t\t\t %u\n",
		      data->chain_noise_b);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "chain_noise_c:\t\t\t %u\n",
		      data->chain_noise_c);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "chain_signal_a:\t\t\t %u\n",
		      data->chain_संकेत_a);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "chain_signal_b:\t\t\t %u\n",
		      data->chain_संकेत_b);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "chain_signal_c:\t\t\t %u\n",
		      data->chain_संकेत_c);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "beacon_count:\t\t\t %u\n",
		      data->beacon_count);

	pos += scnम_लिखो(buf + pos, bufsz - pos, "disconn_array:\t\t\t");
	क्रम (cnt = 0; cnt < NUM_RX_CHAINS; cnt++) अणु
		pos +=
		    scnम_लिखो(buf + pos, bufsz - pos, " %u",
			      data->disconn_array[cnt]);
	पूर्ण
	pos += scnम_लिखो(buf + pos, bufsz - pos, "\n");
	pos += scnम_लिखो(buf + pos, bufsz - pos, "delta_gain_code:\t\t");
	क्रम (cnt = 0; cnt < NUM_RX_CHAINS; cnt++) अणु
		pos +=
		    scnम_लिखो(buf + pos, bufsz - pos, " %u",
			      data->delta_gain_code[cnt]);
	पूर्ण
	pos += scnम_लिखो(buf + pos, bufsz - pos, "\n");
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "radio_write:\t\t\t %u\n",
		      data->radio_ग_लिखो);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "state:\t\t\t\t %u\n",
		      data->state);

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार
il_dbgfs_घातer_save_status_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा il_priv *il = file->निजी_data;
	अक्षर buf[60];
	पूर्णांक pos = 0;
	स्थिर माप_प्रकार bufsz = माप(buf);
	u32 pwrsave_status;

	pwrsave_status =
	    _il_rd(il, CSR_GP_CNTRL) & CSR_GP_REG_POWER_SAVE_STATUS_MSK;

	pos += scnम_लिखो(buf + pos, bufsz - pos, "Power Save Status: ");
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "%s\n",
		      (pwrsave_status == CSR_GP_REG_NO_POWER_SAVE) ? "none" :
		      (pwrsave_status == CSR_GP_REG_MAC_POWER_SAVE) ? "MAC" :
		      (pwrsave_status == CSR_GP_REG_PHY_POWER_SAVE) ? "PHY" :
		      "error");

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

अटल sमाप_प्रकार
il_dbgfs_clear_ucode_stats_ग_लिखो(काष्ठा file *file,
				 स्थिर अक्षर __user *user_buf, माप_प्रकार count,
				 loff_t *ppos)
अणु
	काष्ठा il_priv *il = file->निजी_data;
	अक्षर buf[8];
	पूर्णांक buf_size;
	पूर्णांक clear;

	स_रखो(buf, 0, माप(buf));
	buf_size = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, buf_size))
		वापस -EFAULT;
	अगर (माला_पूछो(buf, "%d", &clear) != 1)
		वापस -EFAULT;

	/* make request to uCode to retrieve stats inक्रमmation */
	mutex_lock(&il->mutex);
	il_send_stats_request(il, CMD_SYNC, true);
	mutex_unlock(&il->mutex);

	वापस count;
पूर्ण

अटल sमाप_प्रकार
il_dbgfs_rxon_flags_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
			 माप_प्रकार count, loff_t *ppos)
अणु

	काष्ठा il_priv *il = file->निजी_data;
	पूर्णांक len = 0;
	अक्षर buf[20];

	len = प्र_लिखो(buf, "0x%04X\n", le32_to_cpu(il->active.flags));
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार
il_dbgfs_rxon_filter_flags_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
				माप_प्रकार count, loff_t *ppos)
अणु

	काष्ठा il_priv *il = file->निजी_data;
	पूर्णांक len = 0;
	अक्षर buf[20];

	len =
	    प्र_लिखो(buf, "0x%04X\n", le32_to_cpu(il->active.filter_flags));
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार
il_dbgfs_fh_reg_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf, माप_प्रकार count,
		     loff_t *ppos)
अणु
	काष्ठा il_priv *il = file->निजी_data;
	अक्षर *buf;
	पूर्णांक pos = 0;
	sमाप_प्रकार ret = -EFAULT;

	अगर (il->ops->dump_fh) अणु
		ret = pos = il->ops->dump_fh(il, &buf, true);
		अगर (buf) अणु
			ret =
			    simple_पढ़ो_from_buffer(user_buf, count, ppos, buf,
						    pos);
			kमुक्त(buf);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल sमाप_प्रकार
il_dbgfs_missed_beacon_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
			    माप_प्रकार count, loff_t *ppos)
अणु

	काष्ठा il_priv *il = file->निजी_data;
	पूर्णांक pos = 0;
	अक्षर buf[12];
	स्थिर माप_प्रकार bufsz = माप(buf);

	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "%d\n",
		      il->missed_beacon_threshold);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

अटल sमाप_प्रकार
il_dbgfs_missed_beacon_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
			     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा il_priv *il = file->निजी_data;
	अक्षर buf[8];
	पूर्णांक buf_size;
	पूर्णांक missed;

	स_रखो(buf, 0, माप(buf));
	buf_size = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, buf_size))
		वापस -EFAULT;
	अगर (माला_पूछो(buf, "%d", &missed) != 1)
		वापस -EINVAL;

	अगर (missed < IL_MISSED_BEACON_THRESHOLD_MIN ||
	    missed > IL_MISSED_BEACON_THRESHOLD_MAX)
		il->missed_beacon_threshold = IL_MISSED_BEACON_THRESHOLD_DEF;
	अन्यथा
		il->missed_beacon_threshold = missed;

	वापस count;
पूर्ण

अटल sमाप_प्रकार
il_dbgfs_क्रमce_reset_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
			  माप_प्रकार count, loff_t *ppos)
अणु

	काष्ठा il_priv *il = file->निजी_data;
	पूर्णांक pos = 0;
	अक्षर buf[300];
	स्थिर माप_प्रकार bufsz = माप(buf);
	काष्ठा il_क्रमce_reset *क्रमce_reset;

	क्रमce_reset = &il->क्रमce_reset;

	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "\tnumber of reset request: %d\n",
		      क्रमce_reset->reset_request_count);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "\tnumber of reset request success: %d\n",
		      क्रमce_reset->reset_success_count);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "\tnumber of reset request reject: %d\n",
		      क्रमce_reset->reset_reject_count);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "\treset duration: %lu\n",
		      क्रमce_reset->reset_duration);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

अटल sमाप_प्रकार
il_dbgfs_क्रमce_reset_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
			   माप_प्रकार count, loff_t *ppos)
अणु

	पूर्णांक ret;
	काष्ठा il_priv *il = file->निजी_data;

	ret = il_क्रमce_reset(il, true);

	वापस ret ? ret : count;
पूर्ण

अटल sमाप_प्रकार
il_dbgfs_wd_समयout_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
			  माप_प्रकार count, loff_t *ppos)
अणु

	काष्ठा il_priv *il = file->निजी_data;
	अक्षर buf[8];
	पूर्णांक buf_size;
	पूर्णांक समयout;

	स_रखो(buf, 0, माप(buf));
	buf_size = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, buf_size))
		वापस -EFAULT;
	अगर (माला_पूछो(buf, "%d", &समयout) != 1)
		वापस -EINVAL;
	अगर (समयout < 0 || समयout > IL_MAX_WD_TIMEOUT)
		समयout = IL_DEF_WD_TIMEOUT;

	il->cfg->wd_समयout = समयout;
	il_setup_watchकरोg(il);
	वापस count;
पूर्ण

DEBUGFS_READ_खाता_OPS(rx_stats);
DEBUGFS_READ_खाता_OPS(tx_stats);
DEBUGFS_READ_खाता_OPS(rx_queue);
DEBUGFS_READ_खाता_OPS(tx_queue);
DEBUGFS_READ_खाता_OPS(ucode_rx_stats);
DEBUGFS_READ_खाता_OPS(ucode_tx_stats);
DEBUGFS_READ_खाता_OPS(ucode_general_stats);
DEBUGFS_READ_खाता_OPS(sensitivity);
DEBUGFS_READ_खाता_OPS(chain_noise);
DEBUGFS_READ_खाता_OPS(घातer_save_status);
DEBUGFS_WRITE_खाता_OPS(clear_ucode_stats);
DEBUGFS_WRITE_खाता_OPS(clear_traffic_stats);
DEBUGFS_READ_खाता_OPS(fh_reg);
DEBUGFS_READ_WRITE_खाता_OPS(missed_beacon);
DEBUGFS_READ_WRITE_खाता_OPS(क्रमce_reset);
DEBUGFS_READ_खाता_OPS(rxon_flags);
DEBUGFS_READ_खाता_OPS(rxon_filter_flags);
DEBUGFS_WRITE_खाता_OPS(wd_समयout);

/*
 * Create the debugfs files and directories
 *
 */
व्योम
il_dbgfs_रेजिस्टर(काष्ठा il_priv *il, स्थिर अक्षर *name)
अणु
	काष्ठा dentry *phyd = il->hw->wiphy->debugfsdir;
	काष्ठा dentry *dir_drv, *dir_data, *dir_rf, *dir_debug;

	dir_drv = debugfs_create_dir(name, phyd);
	il->debugfs_dir = dir_drv;

	dir_data = debugfs_create_dir("data", dir_drv);
	dir_rf = debugfs_create_dir("rf", dir_drv);
	dir_debug = debugfs_create_dir("debug", dir_drv);

	DEBUGFS_ADD_खाता(nvm, dir_data, 0400);
	DEBUGFS_ADD_खाता(sram, dir_data, 0600);
	DEBUGFS_ADD_खाता(stations, dir_data, 0400);
	DEBUGFS_ADD_खाता(channels, dir_data, 0400);
	DEBUGFS_ADD_खाता(status, dir_data, 0400);
	DEBUGFS_ADD_खाता(पूर्णांकerrupt, dir_data, 0600);
	DEBUGFS_ADD_खाता(qos, dir_data, 0400);
	DEBUGFS_ADD_खाता(disable_ht40, dir_data, 0600);
	DEBUGFS_ADD_खाता(rx_stats, dir_debug, 0400);
	DEBUGFS_ADD_खाता(tx_stats, dir_debug, 0400);
	DEBUGFS_ADD_खाता(rx_queue, dir_debug, 0400);
	DEBUGFS_ADD_खाता(tx_queue, dir_debug, 0400);
	DEBUGFS_ADD_खाता(घातer_save_status, dir_debug, 0400);
	DEBUGFS_ADD_खाता(clear_ucode_stats, dir_debug, 0200);
	DEBUGFS_ADD_खाता(clear_traffic_stats, dir_debug, 0200);
	DEBUGFS_ADD_खाता(fh_reg, dir_debug, 0400);
	DEBUGFS_ADD_खाता(missed_beacon, dir_debug, 0200);
	DEBUGFS_ADD_खाता(क्रमce_reset, dir_debug, 0600);
	DEBUGFS_ADD_खाता(ucode_rx_stats, dir_debug, 0400);
	DEBUGFS_ADD_खाता(ucode_tx_stats, dir_debug, 0400);
	DEBUGFS_ADD_खाता(ucode_general_stats, dir_debug, 0400);

	अगर (il->cfg->sensitivity_calib_by_driver)
		DEBUGFS_ADD_खाता(sensitivity, dir_debug, 0400);
	अगर (il->cfg->chain_noise_calib_by_driver)
		DEBUGFS_ADD_खाता(chain_noise, dir_debug, 0400);
	DEBUGFS_ADD_खाता(rxon_flags, dir_debug, 0200);
	DEBUGFS_ADD_खाता(rxon_filter_flags, dir_debug, 0200);
	DEBUGFS_ADD_खाता(wd_समयout, dir_debug, 0200);
	अगर (il->cfg->sensitivity_calib_by_driver)
		DEBUGFS_ADD_BOOL(disable_sensitivity, dir_rf,
				 &il->disable_sens_cal);
	अगर (il->cfg->chain_noise_calib_by_driver)
		DEBUGFS_ADD_BOOL(disable_chain_noise, dir_rf,
				 &il->disable_chain_noise_cal);
	DEBUGFS_ADD_BOOL(disable_tx_घातer, dir_rf, &il->disable_tx_घातer_cal);
पूर्ण
EXPORT_SYMBOL(il_dbgfs_रेजिस्टर);

/*
 * Remove the debugfs files and directories
 */
व्योम
il_dbgfs_unरेजिस्टर(काष्ठा il_priv *il)
अणु
	अगर (!il->debugfs_dir)
		वापस;

	debugfs_हटाओ_recursive(il->debugfs_dir);
	il->debugfs_dir = शून्य;
पूर्ण
EXPORT_SYMBOL(il_dbgfs_unरेजिस्टर);
