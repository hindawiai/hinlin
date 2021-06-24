<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
 *
 * Copyright(c) 2008 - 2014 Intel Corporation. All rights reserved.
 * Copyright (C) 2018 Intel Corporation
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <linuxwअगरi@पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *****************************************************************************/

#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/ieee80211.h>
#समावेश <net/mac80211.h>

#समावेश "iwl-debug.h"
#समावेश "iwl-trans.h"
#समावेश "iwl-io.h"
#समावेश "dev.h"
#समावेश "agn.h"

/* create and हटाओ of files */
#घोषणा DEBUGFS_ADD_खाता(name, parent, mode) करो अणु			\
	debugfs_create_file(#name, mode, parent, priv,			\
			    &iwl_dbgfs_##name##_ops);			\
पूर्ण जबतक (0)

/* file operation */
#घोषणा DEBUGFS_READ_खाता_OPS(name)                                     \
अटल स्थिर काष्ठा file_operations iwl_dbgfs_##name##_ops = अणु          \
	.पढ़ो = iwl_dbgfs_##name##_पढ़ो,				\
	.खोलो = simple_खोलो,						\
	.llseek = generic_file_llseek,					\
पूर्ण;

#घोषणा DEBUGFS_WRITE_खाता_OPS(name)                                    \
अटल स्थिर काष्ठा file_operations iwl_dbgfs_##name##_ops = अणु          \
	.ग_लिखो = iwl_dbgfs_##name##_ग_लिखो,                              \
	.खोलो = simple_खोलो,						\
	.llseek = generic_file_llseek,					\
पूर्ण;


#घोषणा DEBUGFS_READ_WRITE_खाता_OPS(name)                               \
अटल स्थिर काष्ठा file_operations iwl_dbgfs_##name##_ops = अणु          \
	.ग_लिखो = iwl_dbgfs_##name##_ग_लिखो,                              \
	.पढ़ो = iwl_dbgfs_##name##_पढ़ो,                                \
	.खोलो = simple_खोलो,						\
	.llseek = generic_file_llseek,					\
पूर्ण;

अटल sमाप_प्रकार iwl_dbgfs_sram_पढ़ो(काष्ठा file *file,
					अक्षर __user *user_buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	u32 val = 0;
	अक्षर *buf;
	sमाप_प्रकार ret;
	पूर्णांक i = 0;
	bool device_क्रमmat = false;
	पूर्णांक offset = 0;
	पूर्णांक len = 0;
	पूर्णांक pos = 0;
	पूर्णांक sram;
	काष्ठा iwl_priv *priv = file->निजी_data;
	स्थिर काष्ठा fw_img *img;
	माप_प्रकार bufsz;

	अगर (!iwl_is_पढ़ोy_rf(priv))
		वापस -EAGAIN;

	/* शेष is to dump the entire data segment */
	अगर (!priv->dbgfs_sram_offset && !priv->dbgfs_sram_len) अणु
		priv->dbgfs_sram_offset = 0x800000;
		अगर (!priv->ucode_loaded)
			वापस -EINVAL;
		img = &priv->fw->img[priv->cur_ucode];
		priv->dbgfs_sram_len = img->sec[IWL_UCODE_SECTION_DATA].len;
	पूर्ण
	len = priv->dbgfs_sram_len;

	अगर (len == -4) अणु
		device_क्रमmat = true;
		len = 4;
	पूर्ण

	bufsz =  50 + len * 4;
	buf = kदो_स्मृति(bufsz, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	pos += scnम_लिखो(buf + pos, bufsz - pos, "sram_len: 0x%x\n",
			 len);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "sram_offset: 0x%x\n",
			priv->dbgfs_sram_offset);

	/* adjust sram address since पढ़ोs are only on even u32 boundaries */
	offset = priv->dbgfs_sram_offset & 0x3;
	sram = priv->dbgfs_sram_offset & ~0x3;

	/* पढ़ो the first u32 from sram */
	val = iwl_trans_पढ़ो_mem32(priv->trans, sram);

	क्रम (; len; len--) अणु
		/* put the address at the start of every line */
		अगर (i == 0)
			pos += scnम_लिखो(buf + pos, bufsz - pos,
				"%08X: ", sram + offset);

		अगर (device_क्रमmat)
			pos += scnम_लिखो(buf + pos, bufsz - pos,
				"%02x", (val >> (8 * (3 - offset))) & 0xff);
		अन्यथा
			pos += scnम_लिखो(buf + pos, bufsz - pos,
				"%02x ", (val >> (8 * offset)) & 0xff);

		/* अगर all bytes processed, पढ़ो the next u32 from sram */
		अगर (++offset == 4) अणु
			sram += 4;
			offset = 0;
			val = iwl_trans_पढ़ो_mem32(priv->trans, sram);
		पूर्ण

		/* put in extra spaces and split lines क्रम human पढ़ोability */
		अगर (++i == 16) अणु
			i = 0;
			pos += scnम_लिखो(buf + pos, bufsz - pos, "\n");
		पूर्ण अन्यथा अगर (!(i & 7)) अणु
			pos += scnम_लिखो(buf + pos, bufsz - pos, "   ");
		पूर्ण अन्यथा अगर (!(i & 3)) अणु
			pos += scnम_लिखो(buf + pos, bufsz - pos, " ");
		पूर्ण
	पूर्ण
	अगर (i)
		pos += scnम_लिखो(buf + pos, bufsz - pos, "\n");

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_sram_ग_लिखो(काष्ठा file *file,
					स्थिर अक्षर __user *user_buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_priv *priv = file->निजी_data;
	अक्षर buf[64];
	पूर्णांक buf_size;
	u32 offset, len;

	स_रखो(buf, 0, माप(buf));
	buf_size = min(count, माप(buf) -  1);
	अगर (copy_from_user(buf, user_buf, buf_size))
		वापस -EFAULT;

	अगर (माला_पूछो(buf, "%x,%x", &offset, &len) == 2) अणु
		priv->dbgfs_sram_offset = offset;
		priv->dbgfs_sram_len = len;
	पूर्ण अन्यथा अगर (माला_पूछो(buf, "%x", &offset) == 1) अणु
		priv->dbgfs_sram_offset = offset;
		priv->dbgfs_sram_len = -4;
	पूर्ण अन्यथा अणु
		priv->dbgfs_sram_offset = 0;
		priv->dbgfs_sram_len = 0;
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_wowlan_sram_पढ़ो(काष्ठा file *file,
					  अक्षर __user *user_buf,
					  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_priv *priv = file->निजी_data;
	स्थिर काष्ठा fw_img *img = &priv->fw->img[IWL_UCODE_WOWLAN];

	अगर (!priv->wowlan_sram)
		वापस -ENODATA;

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos,
				       priv->wowlan_sram,
				       img->sec[IWL_UCODE_SECTION_DATA].len);
पूर्ण
अटल sमाप_प्रकार iwl_dbgfs_stations_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_priv *priv = file->निजी_data;
	काष्ठा iwl_station_entry *station;
	काष्ठा iwl_tid_data *tid_data;
	अक्षर *buf;
	पूर्णांक i, j, pos = 0;
	sमाप_प्रकार ret;
	/* Add 30 क्रम initial string */
	स्थिर माप_प्रकार bufsz = 30 + माप(अक्षर) * 500 * (priv->num_stations);

	buf = kदो_स्मृति(bufsz, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	pos += scnम_लिखो(buf + pos, bufsz - pos, "num of stations: %d\n\n",
			priv->num_stations);

	क्रम (i = 0; i < IWLAGN_STATION_COUNT; i++) अणु
		station = &priv->stations[i];
		अगर (!station->used)
			जारी;
		pos += scnम_लिखो(buf + pos, bufsz - pos,
				 "station %d - addr: %pM, flags: %#x\n",
				 i, station->sta.sta.addr,
				 station->sta.station_flags_msk);
		pos += scnम_लिखो(buf + pos, bufsz - pos,
				"TID seqno  next_rclmd "
				"rate_n_flags state txq\n");

		क्रम (j = 0; j < IWL_MAX_TID_COUNT; j++) अणु
			tid_data = &priv->tid_data[i][j];
			pos += scnम_लिखो(buf + pos, bufsz - pos,
				"%d:  0x%.4x 0x%.4x     0x%.8x   "
				"%d     %.2d",
				j, tid_data->seq_number,
				tid_data->next_reclaimed,
				tid_data->agg.rate_n_flags,
				tid_data->agg.state,
				tid_data->agg.txq_id);

			अगर (tid_data->agg.रुको_क्रम_ba)
				pos += scnम_लिखो(buf + pos, bufsz - pos,
						 " - waitforba");
			pos += scnम_लिखो(buf + pos, bufsz - pos, "\n");
		पूर्ण

		pos += scnम_लिखो(buf + pos, bufsz - pos, "\n");
	पूर्ण

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_nvm_पढ़ो(काष्ठा file *file,
				       अक्षर __user *user_buf,
				       माप_प्रकार count,
				       loff_t *ppos)
अणु
	sमाप_प्रकार ret;
	काष्ठा iwl_priv *priv = file->निजी_data;
	पूर्णांक pos = 0, ofs = 0, buf_size = 0;
	स्थिर u8 *ptr;
	अक्षर *buf;
	u16 nvm_ver;
	माप_प्रकार eeprom_len = priv->eeprom_blob_size;
	buf_size = 4 * eeprom_len + 256;

	अगर (eeprom_len % 16)
		वापस -ENODATA;

	ptr = priv->eeprom_blob;
	अगर (!ptr)
		वापस -ENOMEM;

	/* 4 अक्षरacters क्रम byte 0xYY */
	buf = kzalloc(buf_size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	nvm_ver = priv->nvm_data->nvm_version;
	pos += scnम_लिखो(buf + pos, buf_size - pos,
			 "NVM version: 0x%x\n", nvm_ver);
	क्रम (ofs = 0 ; ofs < eeprom_len ; ofs += 16) अणु
		pos += scnम_लिखो(buf + pos, buf_size - pos, "0x%.4x %16ph\n",
				 ofs, ptr + ofs);
	पूर्ण

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_channels_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
				       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_priv *priv = file->निजी_data;
	काष्ठा ieee80211_channel *channels = शून्य;
	स्थिर काष्ठा ieee80211_supported_band *supp_band = शून्य;
	पूर्णांक pos = 0, i, bufsz = PAGE_SIZE;
	अक्षर *buf;
	sमाप_प्रकार ret;

	buf = kzalloc(bufsz, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	supp_band = iwl_get_hw_mode(priv, NL80211_BAND_2GHZ);
	अगर (supp_band) अणु
		channels = supp_band->channels;

		pos += scnम_लिखो(buf + pos, bufsz - pos,
				"Displaying %d channels in 2.4GHz band 802.11bg):\n",
				supp_band->n_channels);

		क्रम (i = 0; i < supp_band->n_channels; i++)
			pos += scnम_लिखो(buf + pos, bufsz - pos,
					"%d: %ddBm: BSS%s%s, %s.\n",
					channels[i].hw_value,
					channels[i].max_घातer,
					channels[i].flags & IEEE80211_CHAN_RADAR ?
					" (IEEE 802.11h required)" : "",
					((channels[i].flags & IEEE80211_CHAN_NO_IR)
					|| (channels[i].flags &
					IEEE80211_CHAN_RADAR)) ? "" :
					", IBSS",
					channels[i].flags &
					IEEE80211_CHAN_NO_IR ?
					"passive only" : "active/passive");
	पूर्ण
	supp_band = iwl_get_hw_mode(priv, NL80211_BAND_5GHZ);
	अगर (supp_band) अणु
		channels = supp_band->channels;

		pos += scnम_लिखो(buf + pos, bufsz - pos,
				"Displaying %d channels in 5.2GHz band (802.11a)\n",
				supp_band->n_channels);

		क्रम (i = 0; i < supp_band->n_channels; i++)
			pos += scnम_लिखो(buf + pos, bufsz - pos,
					"%d: %ddBm: BSS%s%s, %s.\n",
					channels[i].hw_value,
					channels[i].max_घातer,
					channels[i].flags & IEEE80211_CHAN_RADAR ?
					" (IEEE 802.11h required)" : "",
					((channels[i].flags & IEEE80211_CHAN_NO_IR)
					|| (channels[i].flags &
					IEEE80211_CHAN_RADAR)) ? "" :
					", IBSS",
					channels[i].flags &
					IEEE80211_CHAN_NO_IR ?
					"passive only" : "active/passive");
	पूर्ण
	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_status_पढ़ो(काष्ठा file *file,
						अक्षर __user *user_buf,
						माप_प्रकार count, loff_t *ppos) अणु

	काष्ठा iwl_priv *priv = file->निजी_data;
	अक्षर buf[512];
	पूर्णांक pos = 0;
	स्थिर माप_प्रकार bufsz = माप(buf);

	pos += scnम_लिखो(buf + pos, bufsz - pos, "STATUS_RF_KILL_HW:\t %d\n",
		test_bit(STATUS_RF_KILL_HW, &priv->status));
	pos += scnम_लिखो(buf + pos, bufsz - pos, "STATUS_CT_KILL:\t\t %d\n",
		test_bit(STATUS_CT_KILL, &priv->status));
	pos += scnम_लिखो(buf + pos, bufsz - pos, "STATUS_ALIVE:\t\t %d\n",
		test_bit(STATUS_ALIVE, &priv->status));
	pos += scnम_लिखो(buf + pos, bufsz - pos, "STATUS_READY:\t\t %d\n",
		test_bit(STATUS_READY, &priv->status));
	pos += scnम_लिखो(buf + pos, bufsz - pos, "STATUS_EXIT_PENDING:\t %d\n",
		test_bit(STATUS_EXIT_PENDING, &priv->status));
	pos += scnम_लिखो(buf + pos, bufsz - pos, "STATUS_STATISTICS:\t %d\n",
		test_bit(STATUS_STATISTICS, &priv->status));
	pos += scnम_लिखो(buf + pos, bufsz - pos, "STATUS_SCANNING:\t %d\n",
		test_bit(STATUS_SCANNING, &priv->status));
	pos += scnम_लिखो(buf + pos, bufsz - pos, "STATUS_SCAN_ABORTING:\t %d\n",
		test_bit(STATUS_SCAN_ABORTING, &priv->status));
	pos += scnम_लिखो(buf + pos, bufsz - pos, "STATUS_SCAN_HW:\t\t %d\n",
		test_bit(STATUS_SCAN_HW, &priv->status));
	pos += scnम_लिखो(buf + pos, bufsz - pos, "STATUS_POWER_PMI:\t %d\n",
		test_bit(STATUS_POWER_PMI, &priv->status));
	pos += scnम_लिखो(buf + pos, bufsz - pos, "STATUS_FW_ERROR:\t %d\n",
		test_bit(STATUS_FW_ERROR, &priv->status));
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_rx_handlers_पढ़ो(काष्ठा file *file,
					अक्षर __user *user_buf,
					माप_प्रकार count, loff_t *ppos) अणु

	काष्ठा iwl_priv *priv = file->निजी_data;

	पूर्णांक pos = 0;
	पूर्णांक cnt = 0;
	अक्षर *buf;
	पूर्णांक bufsz = 24 * 64; /* 24 items * 64 अक्षर per item */
	sमाप_प्रकार ret;

	buf = kzalloc(bufsz, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	क्रम (cnt = 0; cnt < REPLY_MAX; cnt++) अणु
		अगर (priv->rx_handlers_stats[cnt] > 0)
			pos += scnम_लिखो(buf + pos, bufsz - pos,
				"\tRx handler[%36s]:\t\t %u\n",
				iwl_get_cmd_string(priv->trans, (u32)cnt),
				priv->rx_handlers_stats[cnt]);
	पूर्ण

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_rx_handlers_ग_लिखो(काष्ठा file *file,
					 स्थिर अक्षर __user *user_buf,
					 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_priv *priv = file->निजी_data;

	अक्षर buf[8];
	पूर्णांक buf_size;
	u32 reset_flag;

	स_रखो(buf, 0, माप(buf));
	buf_size = min(count, माप(buf) -  1);
	अगर (copy_from_user(buf, user_buf, buf_size))
		वापस -EFAULT;
	अगर (माला_पूछो(buf, "%x", &reset_flag) != 1)
		वापस -EFAULT;
	अगर (reset_flag == 0)
		स_रखो(&priv->rx_handlers_stats[0], 0,
			माप(priv->rx_handlers_stats));

	वापस count;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_qos_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
				       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_priv *priv = file->निजी_data;
	काष्ठा iwl_rxon_context *ctx;
	पूर्णांक pos = 0, i;
	अक्षर buf[256 * NUM_IWL_RXON_CTX];
	स्थिर माप_प्रकार bufsz = माप(buf);

	क्रम_each_context(priv, ctx) अणु
		pos += scnम_लिखो(buf + pos, bufsz - pos, "context %d:\n",
				 ctx->ctxid);
		क्रम (i = 0; i < AC_NUM; i++) अणु
			pos += scnम_लिखो(buf + pos, bufsz - pos,
				"\tcw_min\tcw_max\taifsn\ttxop\n");
			pos += scnम_लिखो(buf + pos, bufsz - pos,
				"AC[%d]\t%u\t%u\t%u\t%u\n", i,
				ctx->qos_data.def_qos_parm.ac[i].cw_min,
				ctx->qos_data.def_qos_parm.ac[i].cw_max,
				ctx->qos_data.def_qos_parm.ac[i].aअगरsn,
				ctx->qos_data.def_qos_parm.ac[i].edca_txop);
		पूर्ण
		pos += scnम_लिखो(buf + pos, bufsz - pos, "\n");
	पूर्ण
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_thermal_throttling_पढ़ो(काष्ठा file *file,
				अक्षर __user *user_buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_priv *priv = file->निजी_data;
	काष्ठा iwl_tt_mgmt *tt = &priv->thermal_throttle;
	काष्ठा iwl_tt_restriction *restriction;
	अक्षर buf[100];
	पूर्णांक pos = 0;
	स्थिर माप_प्रकार bufsz = माप(buf);

	pos += scnम_लिखो(buf + pos, bufsz - pos,
			"Thermal Throttling Mode: %s\n",
			tt->advanced_tt ? "Advance" : "Legacy");
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			"Thermal Throttling State: %d\n",
			tt->state);
	अगर (tt->advanced_tt) अणु
		restriction = tt->restriction + tt->state;
		pos += scnम_लिखो(buf + pos, bufsz - pos,
				"Tx mode: %d\n",
				restriction->tx_stream);
		pos += scnम_लिखो(buf + pos, bufsz - pos,
				"Rx mode: %d\n",
				restriction->rx_stream);
		pos += scnम_लिखो(buf + pos, bufsz - pos,
				"HT mode: %d\n",
				restriction->is_ht);
	पूर्ण
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_disable_ht40_ग_लिखो(काष्ठा file *file,
					 स्थिर अक्षर __user *user_buf,
					 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_priv *priv = file->निजी_data;
	अक्षर buf[8];
	पूर्णांक buf_size;
	पूर्णांक ht40;

	स_रखो(buf, 0, माप(buf));
	buf_size = min(count, माप(buf) -  1);
	अगर (copy_from_user(buf, user_buf, buf_size))
		वापस -EFAULT;
	अगर (माला_पूछो(buf, "%d", &ht40) != 1)
		वापस -EFAULT;
	अगर (!iwl_is_any_associated(priv))
		priv->disable_ht40 = ht40 ? true : false;
	अन्यथा
		वापस -EINVAL;

	वापस count;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_disable_ht40_पढ़ो(काष्ठा file *file,
					 अक्षर __user *user_buf,
					 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_priv *priv = file->निजी_data;
	अक्षर buf[100];
	पूर्णांक pos = 0;
	स्थिर माप_प्रकार bufsz = माप(buf);

	pos += scnम_लिखो(buf + pos, bufsz - pos,
			"11n 40MHz Mode: %s\n",
			priv->disable_ht40 ? "Disabled" : "Enabled");
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_temperature_पढ़ो(काष्ठा file *file,
					 अक्षर __user *user_buf,
					 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_priv *priv = file->निजी_data;
	अक्षर buf[8];
	पूर्णांक pos = 0;
	स्थिर माप_प्रकार bufsz = माप(buf);

	pos += scnम_लिखो(buf + pos, bufsz - pos, "%d\n", priv->temperature);
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण


अटल sमाप_प्रकार iwl_dbgfs_sleep_level_override_ग_लिखो(काष्ठा file *file,
						    स्थिर अक्षर __user *user_buf,
						    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_priv *priv = file->निजी_data;
	अक्षर buf[8];
	पूर्णांक buf_size;
	पूर्णांक value;

	स_रखो(buf, 0, माप(buf));
	buf_size = min(count, माप(buf) -  1);
	अगर (copy_from_user(buf, user_buf, buf_size))
		वापस -EFAULT;

	अगर (माला_पूछो(buf, "%d", &value) != 1)
		वापस -EINVAL;

	/*
	 * Our users expect 0 to be "CAM", but 0 isn't actually
	 * valid here. However, let's not confuse them and present
	 * IWL_POWER_INDEX_1 as "1", not "0".
	 */
	अगर (value == 0)
		वापस -EINVAL;
	अन्यथा अगर (value > 0)
		value -= 1;

	अगर (value != -1 && (value < 0 || value >= IWL_POWER_NUM))
		वापस -EINVAL;

	अगर (!iwl_is_पढ़ोy_rf(priv))
		वापस -EAGAIN;

	priv->घातer_data.debug_sleep_level_override = value;

	mutex_lock(&priv->mutex);
	iwl_घातer_update_mode(priv, true);
	mutex_unlock(&priv->mutex);

	वापस count;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_sleep_level_override_पढ़ो(काष्ठा file *file,
						   अक्षर __user *user_buf,
						   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_priv *priv = file->निजी_data;
	अक्षर buf[10];
	पूर्णांक pos, value;
	स्थिर माप_प्रकार bufsz = माप(buf);

	/* see the ग_लिखो function */
	value = priv->घातer_data.debug_sleep_level_override;
	अगर (value >= 0)
		value += 1;

	pos = scnम_लिखो(buf, bufsz, "%d\n", value);
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_current_sleep_command_पढ़ो(काष्ठा file *file,
						    अक्षर __user *user_buf,
						    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_priv *priv = file->निजी_data;
	अक्षर buf[200];
	पूर्णांक pos = 0, i;
	स्थिर माप_प्रकार bufsz = माप(buf);
	काष्ठा iwl_घातertable_cmd *cmd = &priv->घातer_data.sleep_cmd;

	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 "flags: %#.2x\n", le16_to_cpu(cmd->flags));
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 "RX/TX timeout: %d/%d usec\n",
			 le32_to_cpu(cmd->rx_data_समयout),
			 le32_to_cpu(cmd->tx_data_समयout));
	क्रम (i = 0; i < IWL_POWER_VEC_SIZE; i++)
		pos += scnम_लिखो(buf + pos, bufsz - pos,
				 "sleep_interval[%d]: %d\n", i,
				 le32_to_cpu(cmd->sleep_पूर्णांकerval[i]));

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

DEBUGFS_READ_WRITE_खाता_OPS(sram);
DEBUGFS_READ_खाता_OPS(wowlan_sram);
DEBUGFS_READ_खाता_OPS(nvm);
DEBUGFS_READ_खाता_OPS(stations);
DEBUGFS_READ_खाता_OPS(channels);
DEBUGFS_READ_खाता_OPS(status);
DEBUGFS_READ_WRITE_खाता_OPS(rx_handlers);
DEBUGFS_READ_खाता_OPS(qos);
DEBUGFS_READ_खाता_OPS(thermal_throttling);
DEBUGFS_READ_WRITE_खाता_OPS(disable_ht40);
DEBUGFS_READ_खाता_OPS(temperature);
DEBUGFS_READ_WRITE_खाता_OPS(sleep_level_override);
DEBUGFS_READ_खाता_OPS(current_sleep_command);

#घोषणा fmt_value	"  %-30s %10u\n"
#घोषणा fmt_hex		"  %-30s       0x%02X\n"
#घोषणा fmt_table	"  %-30s %10u  %10u  %10u  %10u\n"
#घोषणा fmt_header	"%-32s    current  cumulative       delta         max\n"

अटल पूर्णांक iwl_statistics_flag(काष्ठा iwl_priv *priv, अक्षर *buf, पूर्णांक bufsz)
अणु
	पूर्णांक p = 0;
	u32 flag;

	lockdep_निश्चित_held(&priv->statistics.lock);

	flag = le32_to_cpu(priv->statistics.flag);

	p += scnम_लिखो(buf + p, bufsz - p, "Statistics Flag(0x%X):\n", flag);
	अगर (flag & UCODE_STATISTICS_CLEAR_MSK)
		p += scnम_लिखो(buf + p, bufsz - p,
		"\tStatistics have been cleared\n");
	p += scnम_लिखो(buf + p, bufsz - p, "\tOperational Frequency: %s\n",
		(flag & UCODE_STATISTICS_FREQUENCY_MSK)
		? "2.4 GHz" : "5.2 GHz");
	p += scnम_लिखो(buf + p, bufsz - p, "\tTGj Narrow Band: %s\n",
		(flag & UCODE_STATISTICS_NARROW_BAND_MSK)
		 ? "enabled" : "disabled");

	वापस p;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_ucode_rx_stats_पढ़ो(काष्ठा file *file,
					अक्षर __user *user_buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_priv *priv = file->निजी_data;
	पूर्णांक pos = 0;
	अक्षर *buf;
	पूर्णांक bufsz = माप(काष्ठा statistics_rx_phy) * 40 +
		    माप(काष्ठा statistics_rx_non_phy) * 40 +
		    माप(काष्ठा statistics_rx_ht_phy) * 40 + 400;
	sमाप_प्रकार ret;
	काष्ठा statistics_rx_phy *ofdm, *accum_ofdm, *delta_ofdm, *max_ofdm;
	काष्ठा statistics_rx_phy *cck, *accum_cck, *delta_cck, *max_cck;
	काष्ठा statistics_rx_non_phy *general, *accum_general;
	काष्ठा statistics_rx_non_phy *delta_general, *max_general;
	काष्ठा statistics_rx_ht_phy *ht, *accum_ht, *delta_ht, *max_ht;

	अगर (!iwl_is_alive(priv))
		वापस -EAGAIN;

	buf = kzalloc(bufsz, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	/*
	 * the statistic inक्रमmation display here is based on
	 * the last statistics notअगरication from uCode
	 * might not reflect the current uCode activity
	 */
	spin_lock_bh(&priv->statistics.lock);
	ofdm = &priv->statistics.rx_ofdm;
	cck = &priv->statistics.rx_cck;
	general = &priv->statistics.rx_non_phy;
	ht = &priv->statistics.rx_ofdm_ht;
	accum_ofdm = &priv->accum_stats.rx_ofdm;
	accum_cck = &priv->accum_stats.rx_cck;
	accum_general = &priv->accum_stats.rx_non_phy;
	accum_ht = &priv->accum_stats.rx_ofdm_ht;
	delta_ofdm = &priv->delta_stats.rx_ofdm;
	delta_cck = &priv->delta_stats.rx_cck;
	delta_general = &priv->delta_stats.rx_non_phy;
	delta_ht = &priv->delta_stats.rx_ofdm_ht;
	max_ofdm = &priv->max_delta_stats.rx_ofdm;
	max_cck = &priv->max_delta_stats.rx_cck;
	max_general = &priv->max_delta_stats.rx_non_phy;
	max_ht = &priv->max_delta_stats.rx_ofdm_ht;

	pos += iwl_statistics_flag(priv, buf, bufsz);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_header, "Statistics_Rx - OFDM:");
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "ina_cnt:",
			 le32_to_cpu(ofdm->ina_cnt),
			 accum_ofdm->ina_cnt,
			 delta_ofdm->ina_cnt, max_ofdm->ina_cnt);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "fina_cnt:",
			 le32_to_cpu(ofdm->fina_cnt), accum_ofdm->fina_cnt,
			 delta_ofdm->fina_cnt, max_ofdm->fina_cnt);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "plcp_err:",
			 le32_to_cpu(ofdm->plcp_err), accum_ofdm->plcp_err,
			 delta_ofdm->plcp_err, max_ofdm->plcp_err);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "crc32_err:",
			 le32_to_cpu(ofdm->crc32_err), accum_ofdm->crc32_err,
			 delta_ofdm->crc32_err, max_ofdm->crc32_err);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "overrun_err:",
			 le32_to_cpu(ofdm->overrun_err),
			 accum_ofdm->overrun_err, delta_ofdm->overrun_err,
			 max_ofdm->overrun_err);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "early_overrun_err:",
			 le32_to_cpu(ofdm->early_overrun_err),
			 accum_ofdm->early_overrun_err,
			 delta_ofdm->early_overrun_err,
			 max_ofdm->early_overrun_err);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "crc32_good:",
			 le32_to_cpu(ofdm->crc32_good),
			 accum_ofdm->crc32_good, delta_ofdm->crc32_good,
			 max_ofdm->crc32_good);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "false_alarm_cnt:",
			 le32_to_cpu(ofdm->false_alarm_cnt),
			 accum_ofdm->false_alarm_cnt,
			 delta_ofdm->false_alarm_cnt,
			 max_ofdm->false_alarm_cnt);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "fina_sync_err_cnt:",
			 le32_to_cpu(ofdm->fina_sync_err_cnt),
			 accum_ofdm->fina_sync_err_cnt,
			 delta_ofdm->fina_sync_err_cnt,
			 max_ofdm->fina_sync_err_cnt);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "sfd_timeout:",
			 le32_to_cpu(ofdm->sfd_समयout),
			 accum_ofdm->sfd_समयout, delta_ofdm->sfd_समयout,
			 max_ofdm->sfd_समयout);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "fina_timeout:",
			 le32_to_cpu(ofdm->fina_समयout),
			 accum_ofdm->fina_समयout, delta_ofdm->fina_समयout,
			 max_ofdm->fina_समयout);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "unresponded_rts:",
			 le32_to_cpu(ofdm->unresponded_rts),
			 accum_ofdm->unresponded_rts,
			 delta_ofdm->unresponded_rts,
			 max_ofdm->unresponded_rts);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "rxe_frame_lmt_ovrun:",
			 le32_to_cpu(ofdm->rxe_frame_limit_overrun),
			 accum_ofdm->rxe_frame_limit_overrun,
			 delta_ofdm->rxe_frame_limit_overrun,
			 max_ofdm->rxe_frame_limit_overrun);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "sent_ack_cnt:",
			 le32_to_cpu(ofdm->sent_ack_cnt),
			 accum_ofdm->sent_ack_cnt, delta_ofdm->sent_ack_cnt,
			 max_ofdm->sent_ack_cnt);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "sent_cts_cnt:",
			 le32_to_cpu(ofdm->sent_cts_cnt),
			 accum_ofdm->sent_cts_cnt, delta_ofdm->sent_cts_cnt,
			 max_ofdm->sent_cts_cnt);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "sent_ba_rsp_cnt:",
			 le32_to_cpu(ofdm->sent_ba_rsp_cnt),
			 accum_ofdm->sent_ba_rsp_cnt,
			 delta_ofdm->sent_ba_rsp_cnt,
			 max_ofdm->sent_ba_rsp_cnt);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "dsp_self_kill:",
			 le32_to_cpu(ofdm->dsp_self_समाप्त),
			 accum_ofdm->dsp_self_समाप्त,
			 delta_ofdm->dsp_self_समाप्त,
			 max_ofdm->dsp_self_समाप्त);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "mh_format_err:",
			 le32_to_cpu(ofdm->mh_क्रमmat_err),
			 accum_ofdm->mh_क्रमmat_err,
			 delta_ofdm->mh_क्रमmat_err,
			 max_ofdm->mh_क्रमmat_err);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "re_acq_main_rssi_sum:",
			 le32_to_cpu(ofdm->re_acq_मुख्य_rssi_sum),
			 accum_ofdm->re_acq_मुख्य_rssi_sum,
			 delta_ofdm->re_acq_मुख्य_rssi_sum,
			 max_ofdm->re_acq_मुख्य_rssi_sum);

	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_header, "Statistics_Rx - CCK:");
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "ina_cnt:",
			 le32_to_cpu(cck->ina_cnt), accum_cck->ina_cnt,
			 delta_cck->ina_cnt, max_cck->ina_cnt);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "fina_cnt:",
			 le32_to_cpu(cck->fina_cnt), accum_cck->fina_cnt,
			 delta_cck->fina_cnt, max_cck->fina_cnt);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "plcp_err:",
			 le32_to_cpu(cck->plcp_err), accum_cck->plcp_err,
			 delta_cck->plcp_err, max_cck->plcp_err);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "crc32_err:",
			 le32_to_cpu(cck->crc32_err), accum_cck->crc32_err,
			 delta_cck->crc32_err, max_cck->crc32_err);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "overrun_err:",
			 le32_to_cpu(cck->overrun_err),
			 accum_cck->overrun_err, delta_cck->overrun_err,
			 max_cck->overrun_err);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "early_overrun_err:",
			 le32_to_cpu(cck->early_overrun_err),
			 accum_cck->early_overrun_err,
			 delta_cck->early_overrun_err,
			 max_cck->early_overrun_err);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "crc32_good:",
			 le32_to_cpu(cck->crc32_good), accum_cck->crc32_good,
			 delta_cck->crc32_good, max_cck->crc32_good);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "false_alarm_cnt:",
			 le32_to_cpu(cck->false_alarm_cnt),
			 accum_cck->false_alarm_cnt,
			 delta_cck->false_alarm_cnt, max_cck->false_alarm_cnt);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "fina_sync_err_cnt:",
			 le32_to_cpu(cck->fina_sync_err_cnt),
			 accum_cck->fina_sync_err_cnt,
			 delta_cck->fina_sync_err_cnt,
			 max_cck->fina_sync_err_cnt);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "sfd_timeout:",
			 le32_to_cpu(cck->sfd_समयout),
			 accum_cck->sfd_समयout, delta_cck->sfd_समयout,
			 max_cck->sfd_समयout);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "fina_timeout:",
			 le32_to_cpu(cck->fina_समयout),
			 accum_cck->fina_समयout, delta_cck->fina_समयout,
			 max_cck->fina_समयout);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "unresponded_rts:",
			 le32_to_cpu(cck->unresponded_rts),
			 accum_cck->unresponded_rts, delta_cck->unresponded_rts,
			 max_cck->unresponded_rts);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "rxe_frame_lmt_ovrun:",
			 le32_to_cpu(cck->rxe_frame_limit_overrun),
			 accum_cck->rxe_frame_limit_overrun,
			 delta_cck->rxe_frame_limit_overrun,
			 max_cck->rxe_frame_limit_overrun);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "sent_ack_cnt:",
			 le32_to_cpu(cck->sent_ack_cnt),
			 accum_cck->sent_ack_cnt, delta_cck->sent_ack_cnt,
			 max_cck->sent_ack_cnt);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "sent_cts_cnt:",
			 le32_to_cpu(cck->sent_cts_cnt),
			 accum_cck->sent_cts_cnt, delta_cck->sent_cts_cnt,
			 max_cck->sent_cts_cnt);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "sent_ba_rsp_cnt:",
			 le32_to_cpu(cck->sent_ba_rsp_cnt),
			 accum_cck->sent_ba_rsp_cnt,
			 delta_cck->sent_ba_rsp_cnt,
			 max_cck->sent_ba_rsp_cnt);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "dsp_self_kill:",
			 le32_to_cpu(cck->dsp_self_समाप्त),
			 accum_cck->dsp_self_समाप्त, delta_cck->dsp_self_समाप्त,
			 max_cck->dsp_self_समाप्त);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "mh_format_err:",
			 le32_to_cpu(cck->mh_क्रमmat_err),
			 accum_cck->mh_क्रमmat_err, delta_cck->mh_क्रमmat_err,
			 max_cck->mh_क्रमmat_err);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "re_acq_main_rssi_sum:",
			 le32_to_cpu(cck->re_acq_मुख्य_rssi_sum),
			 accum_cck->re_acq_मुख्य_rssi_sum,
			 delta_cck->re_acq_मुख्य_rssi_sum,
			 max_cck->re_acq_मुख्य_rssi_sum);

	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_header, "Statistics_Rx - GENERAL:");
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "bogus_cts:",
			 le32_to_cpu(general->bogus_cts),
			 accum_general->bogus_cts, delta_general->bogus_cts,
			 max_general->bogus_cts);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "bogus_ack:",
			 le32_to_cpu(general->bogus_ack),
			 accum_general->bogus_ack, delta_general->bogus_ack,
			 max_general->bogus_ack);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "non_bssid_frames:",
			 le32_to_cpu(general->non_bssid_frames),
			 accum_general->non_bssid_frames,
			 delta_general->non_bssid_frames,
			 max_general->non_bssid_frames);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "filtered_frames:",
			 le32_to_cpu(general->filtered_frames),
			 accum_general->filtered_frames,
			 delta_general->filtered_frames,
			 max_general->filtered_frames);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "non_channel_beacons:",
			 le32_to_cpu(general->non_channel_beacons),
			 accum_general->non_channel_beacons,
			 delta_general->non_channel_beacons,
			 max_general->non_channel_beacons);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "channel_beacons:",
			 le32_to_cpu(general->channel_beacons),
			 accum_general->channel_beacons,
			 delta_general->channel_beacons,
			 max_general->channel_beacons);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "num_missed_bcon:",
			 le32_to_cpu(general->num_missed_bcon),
			 accum_general->num_missed_bcon,
			 delta_general->num_missed_bcon,
			 max_general->num_missed_bcon);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "adc_rx_saturation_time:",
			 le32_to_cpu(general->adc_rx_saturation_समय),
			 accum_general->adc_rx_saturation_समय,
			 delta_general->adc_rx_saturation_समय,
			 max_general->adc_rx_saturation_समय);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "ina_detect_search_tm:",
			 le32_to_cpu(general->ina_detection_search_समय),
			 accum_general->ina_detection_search_समय,
			 delta_general->ina_detection_search_समय,
			 max_general->ina_detection_search_समय);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "beacon_silence_rssi_a:",
			 le32_to_cpu(general->beacon_silence_rssi_a),
			 accum_general->beacon_silence_rssi_a,
			 delta_general->beacon_silence_rssi_a,
			 max_general->beacon_silence_rssi_a);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "beacon_silence_rssi_b:",
			 le32_to_cpu(general->beacon_silence_rssi_b),
			 accum_general->beacon_silence_rssi_b,
			 delta_general->beacon_silence_rssi_b,
			 max_general->beacon_silence_rssi_b);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "beacon_silence_rssi_c:",
			 le32_to_cpu(general->beacon_silence_rssi_c),
			 accum_general->beacon_silence_rssi_c,
			 delta_general->beacon_silence_rssi_c,
			 max_general->beacon_silence_rssi_c);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "interference_data_flag:",
			 le32_to_cpu(general->पूर्णांकerference_data_flag),
			 accum_general->पूर्णांकerference_data_flag,
			 delta_general->पूर्णांकerference_data_flag,
			 max_general->पूर्णांकerference_data_flag);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "channel_load:",
			 le32_to_cpu(general->channel_load),
			 accum_general->channel_load,
			 delta_general->channel_load,
			 max_general->channel_load);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "dsp_false_alarms:",
			 le32_to_cpu(general->dsp_false_alarms),
			 accum_general->dsp_false_alarms,
			 delta_general->dsp_false_alarms,
			 max_general->dsp_false_alarms);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "beacon_rssi_a:",
			 le32_to_cpu(general->beacon_rssi_a),
			 accum_general->beacon_rssi_a,
			 delta_general->beacon_rssi_a,
			 max_general->beacon_rssi_a);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "beacon_rssi_b:",
			 le32_to_cpu(general->beacon_rssi_b),
			 accum_general->beacon_rssi_b,
			 delta_general->beacon_rssi_b,
			 max_general->beacon_rssi_b);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "beacon_rssi_c:",
			 le32_to_cpu(general->beacon_rssi_c),
			 accum_general->beacon_rssi_c,
			 delta_general->beacon_rssi_c,
			 max_general->beacon_rssi_c);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "beacon_energy_a:",
			 le32_to_cpu(general->beacon_energy_a),
			 accum_general->beacon_energy_a,
			 delta_general->beacon_energy_a,
			 max_general->beacon_energy_a);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "beacon_energy_b:",
			 le32_to_cpu(general->beacon_energy_b),
			 accum_general->beacon_energy_b,
			 delta_general->beacon_energy_b,
			 max_general->beacon_energy_b);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "beacon_energy_c:",
			 le32_to_cpu(general->beacon_energy_c),
			 accum_general->beacon_energy_c,
			 delta_general->beacon_energy_c,
			 max_general->beacon_energy_c);

	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_header, "Statistics_Rx - OFDM_HT:");
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "plcp_err:",
			 le32_to_cpu(ht->plcp_err), accum_ht->plcp_err,
			 delta_ht->plcp_err, max_ht->plcp_err);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "overrun_err:",
			 le32_to_cpu(ht->overrun_err), accum_ht->overrun_err,
			 delta_ht->overrun_err, max_ht->overrun_err);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "early_overrun_err:",
			 le32_to_cpu(ht->early_overrun_err),
			 accum_ht->early_overrun_err,
			 delta_ht->early_overrun_err,
			 max_ht->early_overrun_err);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "crc32_good:",
			 le32_to_cpu(ht->crc32_good), accum_ht->crc32_good,
			 delta_ht->crc32_good, max_ht->crc32_good);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "crc32_err:",
			 le32_to_cpu(ht->crc32_err), accum_ht->crc32_err,
			 delta_ht->crc32_err, max_ht->crc32_err);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "mh_format_err:",
			 le32_to_cpu(ht->mh_क्रमmat_err),
			 accum_ht->mh_क्रमmat_err,
			 delta_ht->mh_क्रमmat_err, max_ht->mh_क्रमmat_err);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "agg_crc32_good:",
			 le32_to_cpu(ht->agg_crc32_good),
			 accum_ht->agg_crc32_good,
			 delta_ht->agg_crc32_good, max_ht->agg_crc32_good);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "agg_mpdu_cnt:",
			 le32_to_cpu(ht->agg_mpdu_cnt),
			 accum_ht->agg_mpdu_cnt,
			 delta_ht->agg_mpdu_cnt, max_ht->agg_mpdu_cnt);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "agg_cnt:",
			 le32_to_cpu(ht->agg_cnt), accum_ht->agg_cnt,
			 delta_ht->agg_cnt, max_ht->agg_cnt);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "unsupport_mcs:",
			 le32_to_cpu(ht->unsupport_mcs),
			 accum_ht->unsupport_mcs,
			 delta_ht->unsupport_mcs, max_ht->unsupport_mcs);

	spin_unlock_bh(&priv->statistics.lock);

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_ucode_tx_stats_पढ़ो(काष्ठा file *file,
					अक्षर __user *user_buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_priv *priv = file->निजी_data;
	पूर्णांक pos = 0;
	अक्षर *buf;
	पूर्णांक bufsz = (माप(काष्ठा statistics_tx) * 48) + 250;
	sमाप_प्रकार ret;
	काष्ठा statistics_tx *tx, *accum_tx, *delta_tx, *max_tx;

	अगर (!iwl_is_alive(priv))
		वापस -EAGAIN;

	buf = kzalloc(bufsz, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	/* the statistic inक्रमmation display here is based on
	 * the last statistics notअगरication from uCode
	 * might not reflect the current uCode activity
	 */
	spin_lock_bh(&priv->statistics.lock);

	tx = &priv->statistics.tx;
	accum_tx = &priv->accum_stats.tx;
	delta_tx = &priv->delta_stats.tx;
	max_tx = &priv->max_delta_stats.tx;

	pos += iwl_statistics_flag(priv, buf, bufsz);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_header, "Statistics_Tx:");
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "preamble:",
			 le32_to_cpu(tx->preamble_cnt),
			 accum_tx->preamble_cnt,
			 delta_tx->preamble_cnt, max_tx->preamble_cnt);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "rx_detected_cnt:",
			 le32_to_cpu(tx->rx_detected_cnt),
			 accum_tx->rx_detected_cnt,
			 delta_tx->rx_detected_cnt, max_tx->rx_detected_cnt);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "bt_prio_defer_cnt:",
			 le32_to_cpu(tx->bt_prio_defer_cnt),
			 accum_tx->bt_prio_defer_cnt,
			 delta_tx->bt_prio_defer_cnt,
			 max_tx->bt_prio_defer_cnt);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "bt_prio_kill_cnt:",
			 le32_to_cpu(tx->bt_prio_समाप्त_cnt),
			 accum_tx->bt_prio_समाप्त_cnt,
			 delta_tx->bt_prio_समाप्त_cnt,
			 max_tx->bt_prio_समाप्त_cnt);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "few_bytes_cnt:",
			 le32_to_cpu(tx->few_bytes_cnt),
			 accum_tx->few_bytes_cnt,
			 delta_tx->few_bytes_cnt, max_tx->few_bytes_cnt);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "cts_timeout:",
			 le32_to_cpu(tx->cts_समयout), accum_tx->cts_समयout,
			 delta_tx->cts_समयout, max_tx->cts_समयout);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "ack_timeout:",
			 le32_to_cpu(tx->ack_समयout),
			 accum_tx->ack_समयout,
			 delta_tx->ack_समयout, max_tx->ack_समयout);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "expected_ack_cnt:",
			 le32_to_cpu(tx->expected_ack_cnt),
			 accum_tx->expected_ack_cnt,
			 delta_tx->expected_ack_cnt,
			 max_tx->expected_ack_cnt);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "actual_ack_cnt:",
			 le32_to_cpu(tx->actual_ack_cnt),
			 accum_tx->actual_ack_cnt,
			 delta_tx->actual_ack_cnt,
			 max_tx->actual_ack_cnt);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "dump_msdu_cnt:",
			 le32_to_cpu(tx->dump_msdu_cnt),
			 accum_tx->dump_msdu_cnt,
			 delta_tx->dump_msdu_cnt,
			 max_tx->dump_msdu_cnt);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "abort_nxt_frame_mismatch:",
			 le32_to_cpu(tx->burst_पात_next_frame_mismatch_cnt),
			 accum_tx->burst_पात_next_frame_mismatch_cnt,
			 delta_tx->burst_पात_next_frame_mismatch_cnt,
			 max_tx->burst_पात_next_frame_mismatch_cnt);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "abort_missing_nxt_frame:",
			 le32_to_cpu(tx->burst_पात_missing_next_frame_cnt),
			 accum_tx->burst_पात_missing_next_frame_cnt,
			 delta_tx->burst_पात_missing_next_frame_cnt,
			 max_tx->burst_पात_missing_next_frame_cnt);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "cts_timeout_collision:",
			 le32_to_cpu(tx->cts_समयout_collision),
			 accum_tx->cts_समयout_collision,
			 delta_tx->cts_समयout_collision,
			 max_tx->cts_समयout_collision);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "ack_ba_timeout_collision:",
			 le32_to_cpu(tx->ack_or_ba_समयout_collision),
			 accum_tx->ack_or_ba_समयout_collision,
			 delta_tx->ack_or_ba_समयout_collision,
			 max_tx->ack_or_ba_समयout_collision);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "agg ba_timeout:",
			 le32_to_cpu(tx->agg.ba_समयout),
			 accum_tx->agg.ba_समयout,
			 delta_tx->agg.ba_समयout,
			 max_tx->agg.ba_समयout);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "agg ba_resched_frames:",
			 le32_to_cpu(tx->agg.ba_reschedule_frames),
			 accum_tx->agg.ba_reschedule_frames,
			 delta_tx->agg.ba_reschedule_frames,
			 max_tx->agg.ba_reschedule_frames);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "agg scd_query_agg_frame:",
			 le32_to_cpu(tx->agg.scd_query_agg_frame_cnt),
			 accum_tx->agg.scd_query_agg_frame_cnt,
			 delta_tx->agg.scd_query_agg_frame_cnt,
			 max_tx->agg.scd_query_agg_frame_cnt);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "agg scd_query_no_agg:",
			 le32_to_cpu(tx->agg.scd_query_no_agg),
			 accum_tx->agg.scd_query_no_agg,
			 delta_tx->agg.scd_query_no_agg,
			 max_tx->agg.scd_query_no_agg);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "agg scd_query_agg:",
			 le32_to_cpu(tx->agg.scd_query_agg),
			 accum_tx->agg.scd_query_agg,
			 delta_tx->agg.scd_query_agg,
			 max_tx->agg.scd_query_agg);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "agg scd_query_mismatch:",
			 le32_to_cpu(tx->agg.scd_query_mismatch),
			 accum_tx->agg.scd_query_mismatch,
			 delta_tx->agg.scd_query_mismatch,
			 max_tx->agg.scd_query_mismatch);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "agg frame_not_ready:",
			 le32_to_cpu(tx->agg.frame_not_पढ़ोy),
			 accum_tx->agg.frame_not_पढ़ोy,
			 delta_tx->agg.frame_not_पढ़ोy,
			 max_tx->agg.frame_not_पढ़ोy);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "agg underrun:",
			 le32_to_cpu(tx->agg.underrun),
			 accum_tx->agg.underrun,
			 delta_tx->agg.underrun, max_tx->agg.underrun);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "agg bt_prio_kill:",
			 le32_to_cpu(tx->agg.bt_prio_समाप्त),
			 accum_tx->agg.bt_prio_समाप्त,
			 delta_tx->agg.bt_prio_समाप्त,
			 max_tx->agg.bt_prio_समाप्त);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "agg rx_ba_rsp_cnt:",
			 le32_to_cpu(tx->agg.rx_ba_rsp_cnt),
			 accum_tx->agg.rx_ba_rsp_cnt,
			 delta_tx->agg.rx_ba_rsp_cnt,
			 max_tx->agg.rx_ba_rsp_cnt);

	अगर (tx->tx_घातer.ant_a || tx->tx_घातer.ant_b || tx->tx_घातer.ant_c) अणु
		pos += scnम_लिखो(buf + pos, bufsz - pos,
			"tx power: (1/2 dB step)\n");
		अगर ((priv->nvm_data->valid_tx_ant & ANT_A) &&
		    tx->tx_घातer.ant_a)
			pos += scnम_लिखो(buf + pos, bufsz - pos,
					fmt_hex, "antenna A:",
					tx->tx_घातer.ant_a);
		अगर ((priv->nvm_data->valid_tx_ant & ANT_B) &&
		    tx->tx_घातer.ant_b)
			pos += scnम_लिखो(buf + pos, bufsz - pos,
					fmt_hex, "antenna B:",
					tx->tx_घातer.ant_b);
		अगर ((priv->nvm_data->valid_tx_ant & ANT_C) &&
		    tx->tx_घातer.ant_c)
			pos += scnम_लिखो(buf + pos, bufsz - pos,
					fmt_hex, "antenna C:",
					tx->tx_घातer.ant_c);
	पूर्ण

	spin_unlock_bh(&priv->statistics.lock);

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_ucode_general_stats_पढ़ो(काष्ठा file *file,
					अक्षर __user *user_buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_priv *priv = file->निजी_data;
	पूर्णांक pos = 0;
	अक्षर *buf;
	पूर्णांक bufsz = माप(काष्ठा statistics_general) * 10 + 300;
	sमाप_प्रकार ret;
	काष्ठा statistics_general_common *general, *accum_general;
	काष्ठा statistics_general_common *delta_general, *max_general;
	काष्ठा statistics_dbg *dbg, *accum_dbg, *delta_dbg, *max_dbg;
	काष्ठा statistics_भाग *भाग, *accum_भाग, *delta_भाग, *max_भाग;

	अगर (!iwl_is_alive(priv))
		वापस -EAGAIN;

	buf = kzalloc(bufsz, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	/* the statistic inक्रमmation display here is based on
	 * the last statistics notअगरication from uCode
	 * might not reflect the current uCode activity
	 */

	spin_lock_bh(&priv->statistics.lock);

	general = &priv->statistics.common;
	dbg = &priv->statistics.common.dbg;
	भाग = &priv->statistics.common.भाग;
	accum_general = &priv->accum_stats.common;
	accum_dbg = &priv->accum_stats.common.dbg;
	accum_भाग = &priv->accum_stats.common.भाग;
	delta_general = &priv->delta_stats.common;
	max_general = &priv->max_delta_stats.common;
	delta_dbg = &priv->delta_stats.common.dbg;
	max_dbg = &priv->max_delta_stats.common.dbg;
	delta_भाग = &priv->delta_stats.common.भाग;
	max_भाग = &priv->max_delta_stats.common.भाग;

	pos += iwl_statistics_flag(priv, buf, bufsz);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_header, "Statistics_General:");
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_value, "temperature:",
			 le32_to_cpu(general->temperature));
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_value, "temperature_m:",
			 le32_to_cpu(general->temperature_m));
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_value, "ttl_timestamp:",
			 le32_to_cpu(general->ttl_बारtamp));
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "burst_check:",
			 le32_to_cpu(dbg->burst_check),
			 accum_dbg->burst_check,
			 delta_dbg->burst_check, max_dbg->burst_check);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "burst_count:",
			 le32_to_cpu(dbg->burst_count),
			 accum_dbg->burst_count,
			 delta_dbg->burst_count, max_dbg->burst_count);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "wait_for_silence_timeout_count:",
			 le32_to_cpu(dbg->रुको_क्रम_silence_समयout_cnt),
			 accum_dbg->रुको_क्रम_silence_समयout_cnt,
			 delta_dbg->रुको_क्रम_silence_समयout_cnt,
			 max_dbg->रुको_क्रम_silence_समयout_cnt);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "sleep_time:",
			 le32_to_cpu(general->sleep_समय),
			 accum_general->sleep_समय,
			 delta_general->sleep_समय, max_general->sleep_समय);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "slots_out:",
			 le32_to_cpu(general->slots_out),
			 accum_general->slots_out,
			 delta_general->slots_out, max_general->slots_out);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "slots_idle:",
			 le32_to_cpu(general->slots_idle),
			 accum_general->slots_idle,
			 delta_general->slots_idle, max_general->slots_idle);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "tx_on_a:",
			 le32_to_cpu(भाग->tx_on_a), accum_भाग->tx_on_a,
			 delta_भाग->tx_on_a, max_भाग->tx_on_a);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "tx_on_b:",
			 le32_to_cpu(भाग->tx_on_b), accum_भाग->tx_on_b,
			 delta_भाग->tx_on_b, max_भाग->tx_on_b);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "exec_time:",
			 le32_to_cpu(भाग->exec_समय), accum_भाग->exec_समय,
			 delta_भाग->exec_समय, max_भाग->exec_समय);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "probe_time:",
			 le32_to_cpu(भाग->probe_समय), accum_भाग->probe_समय,
			 delta_भाग->probe_समय, max_भाग->probe_समय);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "rx_enable_counter:",
			 le32_to_cpu(general->rx_enable_counter),
			 accum_general->rx_enable_counter,
			 delta_general->rx_enable_counter,
			 max_general->rx_enable_counter);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 fmt_table, "num_of_sos_states:",
			 le32_to_cpu(general->num_of_sos_states),
			 accum_general->num_of_sos_states,
			 delta_general->num_of_sos_states,
			 max_general->num_of_sos_states);

	spin_unlock_bh(&priv->statistics.lock);

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_ucode_bt_stats_पढ़ो(काष्ठा file *file,
					अक्षर __user *user_buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_priv *priv = (काष्ठा iwl_priv *)file->निजी_data;
	पूर्णांक pos = 0;
	अक्षर *buf;
	पूर्णांक bufsz = (माप(काष्ठा statistics_bt_activity) * 24) + 200;
	sमाप_प्रकार ret;
	काष्ठा statistics_bt_activity *bt, *accum_bt;

	अगर (!iwl_is_alive(priv))
		वापस -EAGAIN;

	अगर (!priv->bt_enable_flag)
		वापस -EINVAL;

	/* make request to uCode to retrieve statistics inक्रमmation */
	mutex_lock(&priv->mutex);
	ret = iwl_send_statistics_request(priv, 0, false);
	mutex_unlock(&priv->mutex);

	अगर (ret)
		वापस -EAGAIN;
	buf = kzalloc(bufsz, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	/*
	 * the statistic inक्रमmation display here is based on
	 * the last statistics notअगरication from uCode
	 * might not reflect the current uCode activity
	 */

	spin_lock_bh(&priv->statistics.lock);

	bt = &priv->statistics.bt_activity;
	accum_bt = &priv->accum_stats.bt_activity;

	pos += iwl_statistics_flag(priv, buf, bufsz);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "Statistics_BT:\n");
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			"\t\t\tcurrent\t\t\taccumulative\n");
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 "hi_priority_tx_req_cnt:\t\t%u\t\t\t%u\n",
			 le32_to_cpu(bt->hi_priority_tx_req_cnt),
			 accum_bt->hi_priority_tx_req_cnt);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 "hi_priority_tx_denied_cnt:\t%u\t\t\t%u\n",
			 le32_to_cpu(bt->hi_priority_tx_denied_cnt),
			 accum_bt->hi_priority_tx_denied_cnt);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 "lo_priority_tx_req_cnt:\t\t%u\t\t\t%u\n",
			 le32_to_cpu(bt->lo_priority_tx_req_cnt),
			 accum_bt->lo_priority_tx_req_cnt);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 "lo_priority_tx_denied_cnt:\t%u\t\t\t%u\n",
			 le32_to_cpu(bt->lo_priority_tx_denied_cnt),
			 accum_bt->lo_priority_tx_denied_cnt);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 "hi_priority_rx_req_cnt:\t\t%u\t\t\t%u\n",
			 le32_to_cpu(bt->hi_priority_rx_req_cnt),
			 accum_bt->hi_priority_rx_req_cnt);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 "hi_priority_rx_denied_cnt:\t%u\t\t\t%u\n",
			 le32_to_cpu(bt->hi_priority_rx_denied_cnt),
			 accum_bt->hi_priority_rx_denied_cnt);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 "lo_priority_rx_req_cnt:\t\t%u\t\t\t%u\n",
			 le32_to_cpu(bt->lo_priority_rx_req_cnt),
			 accum_bt->lo_priority_rx_req_cnt);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 "lo_priority_rx_denied_cnt:\t%u\t\t\t%u\n",
			 le32_to_cpu(bt->lo_priority_rx_denied_cnt),
			 accum_bt->lo_priority_rx_denied_cnt);

	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 "(rx)num_bt_kills:\t\t%u\t\t\t%u\n",
			 le32_to_cpu(priv->statistics.num_bt_समाप्तs),
			 priv->statistics.accum_num_bt_समाप्तs);

	spin_unlock_bh(&priv->statistics.lock);

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_reply_tx_error_पढ़ो(काष्ठा file *file,
					अक्षर __user *user_buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_priv *priv = (काष्ठा iwl_priv *)file->निजी_data;
	पूर्णांक pos = 0;
	अक्षर *buf;
	पूर्णांक bufsz = (माप(काष्ठा reply_tx_error_statistics) * 24) +
		(माप(काष्ठा reply_agg_tx_error_statistics) * 24) + 200;
	sमाप_प्रकार ret;

	अगर (!iwl_is_alive(priv))
		वापस -EAGAIN;

	buf = kzalloc(bufsz, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	pos += scnम_लिखो(buf + pos, bufsz - pos, "Statistics_TX_Error:\n");
	pos += scnम_लिखो(buf + pos, bufsz - pos, "%s:\t\t\t\t%u\n",
			 iwl_get_tx_fail_reason(TX_STATUS_POSTPONE_DELAY),
			 priv->reply_tx_stats.pp_delay);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "%s:\t\t\t%u\n",
			 iwl_get_tx_fail_reason(TX_STATUS_POSTPONE_FEW_BYTES),
			 priv->reply_tx_stats.pp_few_bytes);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "%s:\t\t\t%u\n",
			 iwl_get_tx_fail_reason(TX_STATUS_POSTPONE_BT_PRIO),
			 priv->reply_tx_stats.pp_bt_prio);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "%s:\t\t\t%u\n",
			 iwl_get_tx_fail_reason(TX_STATUS_POSTPONE_QUIET_PERIOD),
			 priv->reply_tx_stats.pp_quiet_period);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "%s:\t\t\t%u\n",
			 iwl_get_tx_fail_reason(TX_STATUS_POSTPONE_CALC_TTAK),
			 priv->reply_tx_stats.pp_calc_ttak);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "%s:\t\t%u\n",
			 iwl_get_tx_fail_reason(
				TX_STATUS_FAIL_INTERNAL_CROSSED_RETRY),
			 priv->reply_tx_stats.पूर्णांक_crossed_retry);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "%s:\t\t\t%u\n",
			 iwl_get_tx_fail_reason(TX_STATUS_FAIL_SHORT_LIMIT),
			 priv->reply_tx_stats.लघु_limit);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "%s:\t\t\t%u\n",
			 iwl_get_tx_fail_reason(TX_STATUS_FAIL_LONG_LIMIT),
			 priv->reply_tx_stats.दीर्घ_limit);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "%s:\t\t\t%u\n",
			 iwl_get_tx_fail_reason(TX_STATUS_FAIL_FIFO_UNDERRUN),
			 priv->reply_tx_stats.fअगरo_underrun);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "%s:\t\t\t%u\n",
			 iwl_get_tx_fail_reason(TX_STATUS_FAIL_DRAIN_FLOW),
			 priv->reply_tx_stats.drain_flow);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "%s:\t\t\t%u\n",
			 iwl_get_tx_fail_reason(TX_STATUS_FAIL_RFKILL_FLUSH),
			 priv->reply_tx_stats.rfसमाप्त_flush);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "%s:\t\t\t%u\n",
			 iwl_get_tx_fail_reason(TX_STATUS_FAIL_LIFE_EXPIRE),
			 priv->reply_tx_stats.lअगरe_expire);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "%s:\t\t\t%u\n",
			 iwl_get_tx_fail_reason(TX_STATUS_FAIL_DEST_PS),
			 priv->reply_tx_stats.dest_ps);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "%s:\t\t\t%u\n",
			 iwl_get_tx_fail_reason(TX_STATUS_FAIL_HOST_ABORTED),
			 priv->reply_tx_stats.host_पात);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "%s:\t\t\t%u\n",
			 iwl_get_tx_fail_reason(TX_STATUS_FAIL_BT_RETRY),
			 priv->reply_tx_stats.pp_delay);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "%s:\t\t\t%u\n",
			 iwl_get_tx_fail_reason(TX_STATUS_FAIL_STA_INVALID),
			 priv->reply_tx_stats.sta_invalid);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "%s:\t\t\t%u\n",
			 iwl_get_tx_fail_reason(TX_STATUS_FAIL_FRAG_DROPPED),
			 priv->reply_tx_stats.frag_drop);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "%s:\t\t\t%u\n",
			 iwl_get_tx_fail_reason(TX_STATUS_FAIL_TID_DISABLE),
			 priv->reply_tx_stats.tid_disable);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "%s:\t\t\t%u\n",
			 iwl_get_tx_fail_reason(TX_STATUS_FAIL_FIFO_FLUSHED),
			 priv->reply_tx_stats.fअगरo_flush);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "%s:\t\t%u\n",
			 iwl_get_tx_fail_reason(
				TX_STATUS_FAIL_INSUFFICIENT_CF_POLL),
			 priv->reply_tx_stats.insuff_cf_poll);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "%s:\t\t\t%u\n",
			 iwl_get_tx_fail_reason(TX_STATUS_FAIL_PASSIVE_NO_RX),
			 priv->reply_tx_stats.fail_hw_drop);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "%s:\t\t%u\n",
			 iwl_get_tx_fail_reason(
				TX_STATUS_FAIL_NO_BEACON_ON_RADAR),
			 priv->reply_tx_stats.sta_color_mismatch);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "UNKNOWN:\t\t\t%u\n",
			 priv->reply_tx_stats.unknown);

	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 "\nStatistics_Agg_TX_Error:\n");

	pos += scnम_लिखो(buf + pos, bufsz - pos, "%s:\t\t\t%u\n",
			 iwl_get_agg_tx_fail_reason(AGG_TX_STATE_UNDERRUN_MSK),
			 priv->reply_agg_tx_stats.underrun);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "%s:\t\t\t%u\n",
			 iwl_get_agg_tx_fail_reason(AGG_TX_STATE_BT_PRIO_MSK),
			 priv->reply_agg_tx_stats.bt_prio);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "%s:\t\t\t%u\n",
			 iwl_get_agg_tx_fail_reason(AGG_TX_STATE_FEW_BYTES_MSK),
			 priv->reply_agg_tx_stats.few_bytes);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "%s:\t\t\t%u\n",
			 iwl_get_agg_tx_fail_reason(AGG_TX_STATE_ABORT_MSK),
			 priv->reply_agg_tx_stats.पात);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "%s:\t\t%u\n",
			 iwl_get_agg_tx_fail_reason(
				AGG_TX_STATE_LAST_SENT_TTL_MSK),
			 priv->reply_agg_tx_stats.last_sent_ttl);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "%s:\t\t%u\n",
			 iwl_get_agg_tx_fail_reason(
				AGG_TX_STATE_LAST_SENT_TRY_CNT_MSK),
			 priv->reply_agg_tx_stats.last_sent_try);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "%s:\t\t%u\n",
			 iwl_get_agg_tx_fail_reason(
				AGG_TX_STATE_LAST_SENT_BT_KILL_MSK),
			 priv->reply_agg_tx_stats.last_sent_bt_समाप्त);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "%s:\t\t\t%u\n",
			 iwl_get_agg_tx_fail_reason(AGG_TX_STATE_SCD_QUERY_MSK),
			 priv->reply_agg_tx_stats.scd_query);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "%s:\t\t%u\n",
			 iwl_get_agg_tx_fail_reason(
				AGG_TX_STATE_TEST_BAD_CRC32_MSK),
			 priv->reply_agg_tx_stats.bad_crc32);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "%s:\t\t\t%u\n",
			 iwl_get_agg_tx_fail_reason(AGG_TX_STATE_RESPONSE_MSK),
			 priv->reply_agg_tx_stats.response);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "%s:\t\t\t%u\n",
			 iwl_get_agg_tx_fail_reason(AGG_TX_STATE_DUMP_TX_MSK),
			 priv->reply_agg_tx_stats.dump_tx);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "%s:\t\t\t%u\n",
			 iwl_get_agg_tx_fail_reason(AGG_TX_STATE_DELAY_TX_MSK),
			 priv->reply_agg_tx_stats.delay_tx);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "UNKNOWN:\t\t\t%u\n",
			 priv->reply_agg_tx_stats.unknown);

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_sensitivity_पढ़ो(काष्ठा file *file,
					अक्षर __user *user_buf,
					माप_प्रकार count, loff_t *ppos) अणु

	काष्ठा iwl_priv *priv = file->निजी_data;
	पूर्णांक pos = 0;
	पूर्णांक cnt = 0;
	अक्षर *buf;
	पूर्णांक bufsz = माप(काष्ठा iwl_sensitivity_data) * 4 + 100;
	sमाप_प्रकार ret;
	काष्ठा iwl_sensitivity_data *data;

	data = &priv->sensitivity_data;
	buf = kzalloc(bufsz, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	pos += scnम_लिखो(buf + pos, bufsz - pos, "auto_corr_ofdm:\t\t\t %u\n",
			data->स्वतः_corr_ofdm);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			"auto_corr_ofdm_mrc:\t\t %u\n",
			data->स्वतः_corr_ofdm_mrc);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "auto_corr_ofdm_x1:\t\t %u\n",
			data->स्वतः_corr_ofdm_x1);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			"auto_corr_ofdm_mrc_x1:\t\t %u\n",
			data->स्वतः_corr_ofdm_mrc_x1);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "auto_corr_cck:\t\t\t %u\n",
			data->स्वतः_corr_cck);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "auto_corr_cck_mrc:\t\t %u\n",
			data->स्वतः_corr_cck_mrc);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			"last_bad_plcp_cnt_ofdm:\t\t %u\n",
			data->last_bad_plcp_cnt_ofdm);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "last_fa_cnt_ofdm:\t\t %u\n",
			data->last_fa_cnt_ofdm);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			"last_bad_plcp_cnt_cck:\t\t %u\n",
			data->last_bad_plcp_cnt_cck);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "last_fa_cnt_cck:\t\t %u\n",
			data->last_fa_cnt_cck);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "nrg_curr_state:\t\t\t %u\n",
			data->nrg_curr_state);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "nrg_prev_state:\t\t\t %u\n",
			data->nrg_prev_state);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "nrg_value:\t\t\t");
	क्रम (cnt = 0; cnt < 10; cnt++) अणु
		pos += scnम_लिखो(buf + pos, bufsz - pos, " %u",
				data->nrg_value[cnt]);
	पूर्ण
	pos += scnम_लिखो(buf + pos, bufsz - pos, "\n");
	pos += scnम_लिखो(buf + pos, bufsz - pos, "nrg_silence_rssi:\t\t");
	क्रम (cnt = 0; cnt < NRG_NUM_PREV_STAT_L; cnt++) अणु
		pos += scnम_लिखो(buf + pos, bufsz - pos, " %u",
				data->nrg_silence_rssi[cnt]);
	पूर्ण
	pos += scnम_लिखो(buf + pos, bufsz - pos, "\n");
	pos += scnम_लिखो(buf + pos, bufsz - pos, "nrg_silence_ref:\t\t %u\n",
			data->nrg_silence_ref);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "nrg_energy_idx:\t\t\t %u\n",
			data->nrg_energy_idx);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "nrg_silence_idx:\t\t %u\n",
			data->nrg_silence_idx);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "nrg_th_cck:\t\t\t %u\n",
			data->nrg_th_cck);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			"nrg_auto_corr_silence_diff:\t %u\n",
			data->nrg_स्वतः_corr_silence_dअगरf);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "num_in_cck_no_fa:\t\t %u\n",
			data->num_in_cck_no_fa);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "nrg_th_ofdm:\t\t\t %u\n",
			data->nrg_th_ofdm);

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
	kमुक्त(buf);
	वापस ret;
पूर्ण


अटल sमाप_प्रकार iwl_dbgfs_chain_noise_पढ़ो(काष्ठा file *file,
					अक्षर __user *user_buf,
					माप_प्रकार count, loff_t *ppos) अणु

	काष्ठा iwl_priv *priv = file->निजी_data;
	पूर्णांक pos = 0;
	पूर्णांक cnt = 0;
	अक्षर *buf;
	पूर्णांक bufsz = माप(काष्ठा iwl_chain_noise_data) * 4 + 100;
	sमाप_प्रकार ret;
	काष्ठा iwl_chain_noise_data *data;

	data = &priv->chain_noise_data;
	buf = kzalloc(bufsz, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	pos += scnम_लिखो(buf + pos, bufsz - pos, "active_chains:\t\t\t %u\n",
			data->active_chains);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "chain_noise_a:\t\t\t %u\n",
			data->chain_noise_a);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "chain_noise_b:\t\t\t %u\n",
			data->chain_noise_b);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "chain_noise_c:\t\t\t %u\n",
			data->chain_noise_c);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "chain_signal_a:\t\t\t %u\n",
			data->chain_संकेत_a);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "chain_signal_b:\t\t\t %u\n",
			data->chain_संकेत_b);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "chain_signal_c:\t\t\t %u\n",
			data->chain_संकेत_c);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "beacon_count:\t\t\t %u\n",
			data->beacon_count);

	pos += scnम_लिखो(buf + pos, bufsz - pos, "disconn_array:\t\t\t");
	क्रम (cnt = 0; cnt < NUM_RX_CHAINS; cnt++) अणु
		pos += scnम_लिखो(buf + pos, bufsz - pos, " %u",
				data->disconn_array[cnt]);
	पूर्ण
	pos += scnम_लिखो(buf + pos, bufsz - pos, "\n");
	pos += scnम_लिखो(buf + pos, bufsz - pos, "delta_gain_code:\t\t");
	क्रम (cnt = 0; cnt < NUM_RX_CHAINS; cnt++) अणु
		pos += scnम_लिखो(buf + pos, bufsz - pos, " %u",
				data->delta_gain_code[cnt]);
	पूर्ण
	pos += scnम_लिखो(buf + pos, bufsz - pos, "\n");
	pos += scnम_लिखो(buf + pos, bufsz - pos, "radio_write:\t\t\t %u\n",
			data->radio_ग_लिखो);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "state:\t\t\t\t %u\n",
			data->state);

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_घातer_save_status_पढ़ो(काष्ठा file *file,
						    अक्षर __user *user_buf,
						    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_priv *priv = file->निजी_data;
	अक्षर buf[60];
	पूर्णांक pos = 0;
	स्थिर माप_प्रकार bufsz = माप(buf);
	u32 pwrsave_status;

	pwrsave_status = iwl_पढ़ो32(priv->trans, CSR_GP_CNTRL) &
			CSR_GP_REG_POWER_SAVE_STATUS_MSK;

	pos += scnम_लिखो(buf + pos, bufsz - pos, "Power Save Status: ");
	pos += scnम_लिखो(buf + pos, bufsz - pos, "%s\n",
		(pwrsave_status == CSR_GP_REG_NO_POWER_SAVE) ? "none" :
		(pwrsave_status == CSR_GP_REG_MAC_POWER_SAVE) ? "MAC" :
		(pwrsave_status == CSR_GP_REG_PHY_POWER_SAVE) ? "PHY" :
		"error");

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_clear_ucode_statistics_ग_लिखो(काष्ठा file *file,
					 स्थिर अक्षर __user *user_buf,
					 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_priv *priv = file->निजी_data;
	अक्षर buf[8];
	पूर्णांक buf_size;
	पूर्णांक clear;

	स_रखो(buf, 0, माप(buf));
	buf_size = min(count, माप(buf) -  1);
	अगर (copy_from_user(buf, user_buf, buf_size))
		वापस -EFAULT;
	अगर (माला_पूछो(buf, "%d", &clear) != 1)
		वापस -EFAULT;

	/* make request to uCode to retrieve statistics inक्रमmation */
	mutex_lock(&priv->mutex);
	iwl_send_statistics_request(priv, 0, true);
	mutex_unlock(&priv->mutex);

	वापस count;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_ucode_tracing_पढ़ो(काष्ठा file *file,
					अक्षर __user *user_buf,
					माप_प्रकार count, loff_t *ppos) अणु

	काष्ठा iwl_priv *priv = file->निजी_data;
	पूर्णांक pos = 0;
	अक्षर buf[128];
	स्थिर माप_प्रकार bufsz = माप(buf);

	pos += scnम_लिखो(buf + pos, bufsz - pos, "ucode trace timer is %s\n",
			priv->event_log.ucode_trace ? "On" : "Off");
	pos += scnम_लिखो(buf + pos, bufsz - pos, "non_wraps_count:\t\t %u\n",
			priv->event_log.non_wraps_count);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "wraps_once_count:\t\t %u\n",
			priv->event_log.wraps_once_count);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "wraps_more_count:\t\t %u\n",
			priv->event_log.wraps_more_count);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_ucode_tracing_ग_लिखो(काष्ठा file *file,
					 स्थिर अक्षर __user *user_buf,
					 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_priv *priv = file->निजी_data;
	अक्षर buf[8];
	पूर्णांक buf_size;
	पूर्णांक trace;

	स_रखो(buf, 0, माप(buf));
	buf_size = min(count, माप(buf) -  1);
	अगर (copy_from_user(buf, user_buf, buf_size))
		वापस -EFAULT;
	अगर (माला_पूछो(buf, "%d", &trace) != 1)
		वापस -EFAULT;

	अगर (trace) अणु
		priv->event_log.ucode_trace = true;
		अगर (iwl_is_alive(priv)) अणु
			/* start collecting data now */
			mod_समयr(&priv->ucode_trace, jअगरfies);
		पूर्ण
	पूर्ण अन्यथा अणु
		priv->event_log.ucode_trace = false;
		del_समयr_sync(&priv->ucode_trace);
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_rxon_flags_पढ़ो(काष्ठा file *file,
					 अक्षर __user *user_buf,
					 माप_प्रकार count, loff_t *ppos) अणु

	काष्ठा iwl_priv *priv = file->निजी_data;
	पूर्णांक len = 0;
	अक्षर buf[20];

	len = प्र_लिखो(buf, "0x%04X\n",
		le32_to_cpu(priv->contexts[IWL_RXON_CTX_BSS].active.flags));
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_rxon_filter_flags_पढ़ो(काष्ठा file *file,
						अक्षर __user *user_buf,
						माप_प्रकार count, loff_t *ppos) अणु

	काष्ठा iwl_priv *priv = file->निजी_data;
	पूर्णांक len = 0;
	अक्षर buf[20];

	len = प्र_लिखो(buf, "0x%04X\n",
		le32_to_cpu(priv->contexts[IWL_RXON_CTX_BSS].active.filter_flags));
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_missed_beacon_पढ़ो(काष्ठा file *file,
					अक्षर __user *user_buf,
					माप_प्रकार count, loff_t *ppos) अणु

	काष्ठा iwl_priv *priv = file->निजी_data;
	पूर्णांक pos = 0;
	अक्षर buf[12];
	स्थिर माप_प्रकार bufsz = माप(buf);

	pos += scnम_लिखो(buf + pos, bufsz - pos, "%d\n",
			priv->missed_beacon_threshold);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_missed_beacon_ग_लिखो(काष्ठा file *file,
					 स्थिर अक्षर __user *user_buf,
					 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_priv *priv = file->निजी_data;
	अक्षर buf[8];
	पूर्णांक buf_size;
	पूर्णांक missed;

	स_रखो(buf, 0, माप(buf));
	buf_size = min(count, माप(buf) -  1);
	अगर (copy_from_user(buf, user_buf, buf_size))
		वापस -EFAULT;
	अगर (माला_पूछो(buf, "%d", &missed) != 1)
		वापस -EINVAL;

	अगर (missed < IWL_MISSED_BEACON_THRESHOLD_MIN ||
	    missed > IWL_MISSED_BEACON_THRESHOLD_MAX)
		priv->missed_beacon_threshold =
			IWL_MISSED_BEACON_THRESHOLD_DEF;
	अन्यथा
		priv->missed_beacon_threshold = missed;

	वापस count;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_plcp_delta_पढ़ो(काष्ठा file *file,
					अक्षर __user *user_buf,
					माप_प्रकार count, loff_t *ppos) अणु

	काष्ठा iwl_priv *priv = file->निजी_data;
	पूर्णांक pos = 0;
	अक्षर buf[12];
	स्थिर माप_प्रकार bufsz = माप(buf);

	pos += scnम_लिखो(buf + pos, bufsz - pos, "%u\n",
			priv->plcp_delta_threshold);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_plcp_delta_ग_लिखो(काष्ठा file *file,
					स्थिर अक्षर __user *user_buf,
					माप_प्रकार count, loff_t *ppos) अणु

	काष्ठा iwl_priv *priv = file->निजी_data;
	अक्षर buf[8];
	पूर्णांक buf_size;
	पूर्णांक plcp;

	स_रखो(buf, 0, माप(buf));
	buf_size = min(count, माप(buf) -  1);
	अगर (copy_from_user(buf, user_buf, buf_size))
		वापस -EFAULT;
	अगर (माला_पूछो(buf, "%d", &plcp) != 1)
		वापस -EINVAL;
	अगर ((plcp < IWL_MAX_PLCP_ERR_THRESHOLD_MIN) ||
		(plcp > IWL_MAX_PLCP_ERR_THRESHOLD_MAX))
		priv->plcp_delta_threshold =
			IWL_MAX_PLCP_ERR_THRESHOLD_DISABLE;
	अन्यथा
		priv->plcp_delta_threshold = plcp;
	वापस count;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_rf_reset_पढ़ो(काष्ठा file *file,
				       अक्षर __user *user_buf,
				       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_priv *priv = file->निजी_data;
	पूर्णांक pos = 0;
	अक्षर buf[300];
	स्थिर माप_प्रकार bufsz = माप(buf);
	काष्ठा iwl_rf_reset *rf_reset = &priv->rf_reset;

	pos += scnम_लिखो(buf + pos, bufsz - pos,
			"RF reset statistics\n");
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			"\tnumber of reset request: %d\n",
			rf_reset->reset_request_count);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			"\tnumber of reset request success: %d\n",
			rf_reset->reset_success_count);
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			"\tnumber of reset request reject: %d\n",
			rf_reset->reset_reject_count);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_rf_reset_ग_लिखो(काष्ठा file *file,
					स्थिर अक्षर __user *user_buf,
					माप_प्रकार count, loff_t *ppos) अणु

	काष्ठा iwl_priv *priv = file->निजी_data;
	पूर्णांक ret;

	ret = iwl_क्रमce_rf_reset(priv, true);
	वापस ret ? ret : count;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_txfअगरo_flush_ग_लिखो(काष्ठा file *file,
					स्थिर अक्षर __user *user_buf,
					माप_प्रकार count, loff_t *ppos) अणु

	काष्ठा iwl_priv *priv = file->निजी_data;
	अक्षर buf[8];
	पूर्णांक buf_size;
	पूर्णांक flush;

	स_रखो(buf, 0, माप(buf));
	buf_size = min(count, माप(buf) -  1);
	अगर (copy_from_user(buf, user_buf, buf_size))
		वापस -EFAULT;
	अगर (माला_पूछो(buf, "%d", &flush) != 1)
		वापस -EINVAL;

	अगर (iwl_is_rfसमाप्त(priv))
		वापस -EFAULT;

	iwlagn_dev_txfअगरo_flush(priv);

	वापस count;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_bt_traffic_पढ़ो(काष्ठा file *file,
					अक्षर __user *user_buf,
					माप_प्रकार count, loff_t *ppos) अणु

	काष्ठा iwl_priv *priv = (काष्ठा iwl_priv *)file->निजी_data;
	पूर्णांक pos = 0;
	अक्षर buf[200];
	स्थिर माप_प्रकार bufsz = माप(buf);

	अगर (!priv->bt_enable_flag) अणु
		pos += scnम_लिखो(buf + pos, bufsz - pos, "BT coex disabled\n");
		वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
	पूर्ण
	pos += scnम_लिखो(buf + pos, bufsz - pos, "BT enable flag: 0x%x\n",
		priv->bt_enable_flag);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "BT in %s mode\n",
		priv->bt_full_concurrent ? "full concurrency" : "3-wire");
	pos += scnम_लिखो(buf + pos, bufsz - pos, "BT status: %s, "
			 "last traffic notif: %d\n",
		priv->bt_status ? "On" : "Off", priv->last_bt_traffic_load);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "ch_announcement: %d, "
			 "kill_ack_mask: %x, kill_cts_mask: %x\n",
		priv->bt_ch_announce, priv->समाप्त_ack_mask,
		priv->समाप्त_cts_mask);

	pos += scnम_लिखो(buf + pos, bufsz - pos, "bluetooth traffic load: ");
	चयन (priv->bt_traffic_load) अणु
	हाल IWL_BT_COEX_TRAFFIC_LOAD_CONTINUOUS:
		pos += scnम_लिखो(buf + pos, bufsz - pos, "Continuous\n");
		अवरोध;
	हाल IWL_BT_COEX_TRAFFIC_LOAD_HIGH:
		pos += scnम_लिखो(buf + pos, bufsz - pos, "High\n");
		अवरोध;
	हाल IWL_BT_COEX_TRAFFIC_LOAD_LOW:
		pos += scnम_लिखो(buf + pos, bufsz - pos, "Low\n");
		अवरोध;
	हाल IWL_BT_COEX_TRAFFIC_LOAD_NONE:
	शेष:
		pos += scnम_लिखो(buf + pos, bufsz - pos, "None\n");
		अवरोध;
	पूर्ण

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_protection_mode_पढ़ो(काष्ठा file *file,
					अक्षर __user *user_buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_priv *priv = (काष्ठा iwl_priv *)file->निजी_data;

	पूर्णांक pos = 0;
	अक्षर buf[40];
	स्थिर माप_प्रकार bufsz = माप(buf);

	अगर (priv->cfg->ht_params)
		pos += scnम_लिखो(buf + pos, bufsz - pos,
			 "use %s for aggregation\n",
			 (priv->hw_params.use_rts_क्रम_aggregation) ?
				"rts/cts" : "cts-to-self");
	अन्यथा
		pos += scnम_लिखो(buf + pos, bufsz - pos, "N/A");

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_protection_mode_ग_लिखो(काष्ठा file *file,
					स्थिर अक्षर __user *user_buf,
					माप_प्रकार count, loff_t *ppos) अणु

	काष्ठा iwl_priv *priv = file->निजी_data;
	अक्षर buf[8];
	पूर्णांक buf_size;
	पूर्णांक rts;

	अगर (!priv->cfg->ht_params)
		वापस -EINVAL;

	स_रखो(buf, 0, माप(buf));
	buf_size = min(count, माप(buf) -  1);
	अगर (copy_from_user(buf, user_buf, buf_size))
		वापस -EFAULT;
	अगर (माला_पूछो(buf, "%d", &rts) != 1)
		वापस -EINVAL;
	अगर (rts)
		priv->hw_params.use_rts_क्रम_aggregation = true;
	अन्यथा
		priv->hw_params.use_rts_क्रम_aggregation = false;
	वापस count;
पूर्ण

अटल पूर्णांक iwl_cmd_echo_test(काष्ठा iwl_priv *priv)
अणु
	पूर्णांक ret;
	काष्ठा iwl_host_cmd cmd = अणु
		.id = REPLY_ECHO,
		.len = अणु 0 पूर्ण,
	पूर्ण;

	ret = iwl_dvm_send_cmd(priv, &cmd);
	अगर (ret)
		IWL_ERR(priv, "echo testing fail: 0X%x\n", ret);
	अन्यथा
		IWL_DEBUG_INFO(priv, "echo testing pass\n");
	वापस ret;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_echo_test_ग_लिखो(काष्ठा file *file,
					स्थिर अक्षर __user *user_buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_priv *priv = file->निजी_data;
	अक्षर buf[8];
	पूर्णांक buf_size;

	स_रखो(buf, 0, माप(buf));
	buf_size = min(count, माप(buf) -  1);
	अगर (copy_from_user(buf, user_buf, buf_size))
		वापस -EFAULT;

	iwl_cmd_echo_test(priv);
	वापस count;
पूर्ण

#अगर_घोषित CONFIG_IWLWIFI_DEBUG
अटल sमाप_प्रकार iwl_dbgfs_log_event_पढ़ो(काष्ठा file *file,
					 अक्षर __user *user_buf,
					 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_priv *priv = file->निजी_data;
	अक्षर *buf = शून्य;
	sमाप_प्रकार ret;

	ret = iwl_dump_nic_event_log(priv, true, &buf);
	अगर (ret > 0)
		ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, ret);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_log_event_ग_लिखो(काष्ठा file *file,
					स्थिर अक्षर __user *user_buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_priv *priv = file->निजी_data;
	u32 event_log_flag;
	अक्षर buf[8];
	पूर्णांक buf_size;

	/* check that the पूर्णांकerface is up */
	अगर (!iwl_is_पढ़ोy(priv))
		वापस -EAGAIN;

	स_रखो(buf, 0, माप(buf));
	buf_size = min(count, माप(buf) -  1);
	अगर (copy_from_user(buf, user_buf, buf_size))
		वापस -EFAULT;
	अगर (माला_पूछो(buf, "%u", &event_log_flag) != 1)
		वापस -EFAULT;
	अगर (event_log_flag == 1)
		iwl_dump_nic_event_log(priv, true, शून्य);

	वापस count;
पूर्ण
#पूर्ण_अगर

अटल sमाप_प्रकार iwl_dbgfs_calib_disabled_पढ़ो(काष्ठा file *file,
					 अक्षर __user *user_buf,
					 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_priv *priv = file->निजी_data;
	अक्षर buf[120];
	पूर्णांक pos = 0;
	स्थिर माप_प्रकार bufsz = माप(buf);

	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 "Sensitivity calibrations %s\n",
			 (priv->calib_disabled &
					IWL_SENSITIVITY_CALIB_DISABLED) ?
			 "DISABLED" : "ENABLED");
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 "Chain noise calibrations %s\n",
			 (priv->calib_disabled &
					IWL_CHAIN_NOISE_CALIB_DISABLED) ?
			 "DISABLED" : "ENABLED");
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 "Tx power calibrations %s\n",
			 (priv->calib_disabled &
					IWL_TX_POWER_CALIB_DISABLED) ?
			 "DISABLED" : "ENABLED");

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_calib_disabled_ग_लिखो(काष्ठा file *file,
					      स्थिर अक्षर __user *user_buf,
					      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_priv *priv = file->निजी_data;
	अक्षर buf[8];
	u32 calib_disabled;
	पूर्णांक buf_size;

	स_रखो(buf, 0, माप(buf));
	buf_size = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, buf_size))
		वापस -EFAULT;
	अगर (माला_पूछो(buf, "%x", &calib_disabled) != 1)
		वापस -EFAULT;

	priv->calib_disabled = calib_disabled;

	वापस count;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_fw_restart_ग_लिखो(काष्ठा file *file,
					  स्थिर अक्षर __user *user_buf,
					  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_priv *priv = file->निजी_data;
	bool fw_restart = iwlwअगरi_mod_params.fw_restart;
	पूर्णांक __maybe_unused ret;

	iwlwअगरi_mod_params.fw_restart = true;

	mutex_lock(&priv->mutex);

	/* take the वापस value to make compiler happy - it will fail anyway */
	ret = iwl_dvm_send_cmd_pdu(priv, REPLY_ERROR, 0, 0, शून्य);

	mutex_unlock(&priv->mutex);

	iwlwअगरi_mod_params.fw_restart = fw_restart;

	वापस count;
पूर्ण

DEBUGFS_READ_खाता_OPS(ucode_rx_stats);
DEBUGFS_READ_खाता_OPS(ucode_tx_stats);
DEBUGFS_READ_खाता_OPS(ucode_general_stats);
DEBUGFS_READ_खाता_OPS(sensitivity);
DEBUGFS_READ_खाता_OPS(chain_noise);
DEBUGFS_READ_खाता_OPS(घातer_save_status);
DEBUGFS_WRITE_खाता_OPS(clear_ucode_statistics);
DEBUGFS_READ_WRITE_खाता_OPS(ucode_tracing);
DEBUGFS_READ_WRITE_खाता_OPS(missed_beacon);
DEBUGFS_READ_WRITE_खाता_OPS(plcp_delta);
DEBUGFS_READ_WRITE_खाता_OPS(rf_reset);
DEBUGFS_READ_खाता_OPS(rxon_flags);
DEBUGFS_READ_खाता_OPS(rxon_filter_flags);
DEBUGFS_WRITE_खाता_OPS(txfअगरo_flush);
DEBUGFS_READ_खाता_OPS(ucode_bt_stats);
DEBUGFS_READ_खाता_OPS(bt_traffic);
DEBUGFS_READ_WRITE_खाता_OPS(protection_mode);
DEBUGFS_READ_खाता_OPS(reply_tx_error);
DEBUGFS_WRITE_खाता_OPS(echo_test);
DEBUGFS_WRITE_खाता_OPS(fw_restart);
#अगर_घोषित CONFIG_IWLWIFI_DEBUG
DEBUGFS_READ_WRITE_खाता_OPS(log_event);
#पूर्ण_अगर
DEBUGFS_READ_WRITE_खाता_OPS(calib_disabled);

/*
 * Create the debugfs files and directories
 *
 */
व्योम iwl_dbgfs_रेजिस्टर(काष्ठा iwl_priv *priv, काष्ठा dentry *dbgfs_dir)
अणु
	काष्ठा dentry *dir_data, *dir_rf, *dir_debug;

	priv->debugfs_dir = dbgfs_dir;

	dir_data = debugfs_create_dir("data", dbgfs_dir);
	dir_rf = debugfs_create_dir("rf", dbgfs_dir);
	dir_debug = debugfs_create_dir("debug", dbgfs_dir);

	DEBUGFS_ADD_खाता(nvm, dir_data, 0400);
	DEBUGFS_ADD_खाता(sram, dir_data, 0600);
	DEBUGFS_ADD_खाता(wowlan_sram, dir_data, 0400);
	DEBUGFS_ADD_खाता(stations, dir_data, 0400);
	DEBUGFS_ADD_खाता(channels, dir_data, 0400);
	DEBUGFS_ADD_खाता(status, dir_data, 0400);
	DEBUGFS_ADD_खाता(rx_handlers, dir_data, 0600);
	DEBUGFS_ADD_खाता(qos, dir_data, 0400);
	DEBUGFS_ADD_खाता(sleep_level_override, dir_data, 0600);
	DEBUGFS_ADD_खाता(current_sleep_command, dir_data, 0400);
	DEBUGFS_ADD_खाता(thermal_throttling, dir_data, 0400);
	DEBUGFS_ADD_खाता(disable_ht40, dir_data, 0600);
	DEBUGFS_ADD_खाता(temperature, dir_data, 0400);

	DEBUGFS_ADD_खाता(घातer_save_status, dir_debug, 0400);
	DEBUGFS_ADD_खाता(clear_ucode_statistics, dir_debug, 0200);
	DEBUGFS_ADD_खाता(missed_beacon, dir_debug, 0200);
	DEBUGFS_ADD_खाता(plcp_delta, dir_debug, 0600);
	DEBUGFS_ADD_खाता(rf_reset, dir_debug, 0600);
	DEBUGFS_ADD_खाता(ucode_rx_stats, dir_debug, 0400);
	DEBUGFS_ADD_खाता(ucode_tx_stats, dir_debug, 0400);
	DEBUGFS_ADD_खाता(ucode_general_stats, dir_debug, 0400);
	DEBUGFS_ADD_खाता(txfअगरo_flush, dir_debug, 0200);
	DEBUGFS_ADD_खाता(protection_mode, dir_debug, 0600);
	DEBUGFS_ADD_खाता(sensitivity, dir_debug, 0400);
	DEBUGFS_ADD_खाता(chain_noise, dir_debug, 0400);
	DEBUGFS_ADD_खाता(ucode_tracing, dir_debug, 0600);
	DEBUGFS_ADD_खाता(ucode_bt_stats, dir_debug, 0400);
	DEBUGFS_ADD_खाता(reply_tx_error, dir_debug, 0400);
	DEBUGFS_ADD_खाता(rxon_flags, dir_debug, 0200);
	DEBUGFS_ADD_खाता(rxon_filter_flags, dir_debug, 0200);
	DEBUGFS_ADD_खाता(echo_test, dir_debug, 0200);
	DEBUGFS_ADD_खाता(fw_restart, dir_debug, 0200);
#अगर_घोषित CONFIG_IWLWIFI_DEBUG
	DEBUGFS_ADD_खाता(log_event, dir_debug, 0600);
#पूर्ण_अगर

	अगर (iwl_advanced_bt_coexist(priv))
		DEBUGFS_ADD_खाता(bt_traffic, dir_debug, 0400);

	/* Calibrations disabled/enabled status*/
	DEBUGFS_ADD_खाता(calib_disabled, dir_rf, 0600);

	/*
	 * Create a symlink with mac80211. This is not very robust, as it करोes
	 * not हटाओ the symlink created. The implicit assumption is that
	 * when the opmode निकासs, mac80211 will also निकास, and will हटाओ
	 * this symlink as part of its cleanup.
	 */
	अगर (priv->mac80211_रेजिस्टरed) अणु
		अक्षर buf[100];
		काष्ठा dentry *mac80211_dir, *dev_dir;

		dev_dir = dbgfs_dir->d_parent;
		mac80211_dir = priv->hw->wiphy->debugfsdir;

		snम_लिखो(buf, 100, "../../%pd2", dev_dir);

		debugfs_create_symlink("iwlwifi", mac80211_dir, buf);
	पूर्ण
पूर्ण
