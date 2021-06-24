<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2012-2014, 2018-2021 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/ieee80211.h>
#समावेश <linux/netdevice.h>

#समावेश "mvm.h"
#समावेश "sta.h"
#समावेश "iwl-io.h"
#समावेश "debugfs.h"
#समावेश "iwl-modparams.h"
#समावेश "fw/error-dump.h"

अटल sमाप_प्रकार iwl_dbgfs_ctdp_budget_पढ़ो(काष्ठा file *file,
					  अक्षर __user *user_buf,
					  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_mvm *mvm = file->निजी_data;
	अक्षर buf[16];
	पूर्णांक pos, budget;

	अगर (!iwl_mvm_is_ctdp_supported(mvm))
		वापस -EOPNOTSUPP;

	अगर (!iwl_mvm_firmware_running(mvm) ||
	    mvm->fwrt.cur_fw_img != IWL_UCODE_REGULAR)
		वापस -EIO;

	mutex_lock(&mvm->mutex);
	budget = iwl_mvm_ctdp_command(mvm, CTDP_CMD_OPERATION_REPORT, 0);
	mutex_unlock(&mvm->mutex);

	अगर (budget < 0)
		वापस budget;

	pos = scnम_लिखो(buf, माप(buf), "%d\n", budget);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_stop_ctdp_ग_लिखो(काष्ठा iwl_mvm *mvm, अक्षर *buf,
					 माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक ret;

	अगर (!iwl_mvm_is_ctdp_supported(mvm))
		वापस -EOPNOTSUPP;

	अगर (!iwl_mvm_firmware_running(mvm) ||
	    mvm->fwrt.cur_fw_img != IWL_UCODE_REGULAR)
		वापस -EIO;

	mutex_lock(&mvm->mutex);
	ret = iwl_mvm_ctdp_command(mvm, CTDP_CMD_OPERATION_STOP, 0);
	mutex_unlock(&mvm->mutex);

	वापस ret ?: count;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_क्रमce_ctसमाप्त_ग_लिखो(काष्ठा iwl_mvm *mvm, अक्षर *buf,
					    माप_प्रकार count, loff_t *ppos)
अणु
	अगर (!iwl_mvm_firmware_running(mvm) ||
	    mvm->fwrt.cur_fw_img != IWL_UCODE_REGULAR)
		वापस -EIO;

	iwl_mvm_enter_ctसमाप्त(mvm);

	वापस count;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_tx_flush_ग_लिखो(काष्ठा iwl_mvm *mvm, अक्षर *buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक ret;
	u32 flush_arg;

	अगर (!iwl_mvm_firmware_running(mvm) ||
	    mvm->fwrt.cur_fw_img != IWL_UCODE_REGULAR)
		वापस -EIO;

	अगर (kstrtou32(buf, 0, &flush_arg))
		वापस -EINVAL;

	अगर (iwl_mvm_has_new_tx_api(mvm)) अणु
		IWL_DEBUG_TX_QUEUES(mvm,
				    "FLUSHING all tids queues on sta_id = %d\n",
				    flush_arg);
		mutex_lock(&mvm->mutex);
		ret = iwl_mvm_flush_sta_tids(mvm, flush_arg, 0xFFFF)
			? : count;
		mutex_unlock(&mvm->mutex);
		वापस ret;
	पूर्ण

	IWL_DEBUG_TX_QUEUES(mvm, "FLUSHING queues mask to flush = 0x%x\n",
			    flush_arg);

	mutex_lock(&mvm->mutex);
	ret =  iwl_mvm_flush_tx_path(mvm, flush_arg) ? : count;
	mutex_unlock(&mvm->mutex);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_sta_drain_ग_लिखो(काष्ठा iwl_mvm *mvm, अक्षर *buf,
					 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_mvm_sta *mvmsta;
	पूर्णांक sta_id, drain, ret;

	अगर (!iwl_mvm_firmware_running(mvm) ||
	    mvm->fwrt.cur_fw_img != IWL_UCODE_REGULAR)
		वापस -EIO;

	अगर (माला_पूछो(buf, "%d %d", &sta_id, &drain) != 2)
		वापस -EINVAL;
	अगर (sta_id < 0 || sta_id >= mvm->fw->ucode_capa.num_stations)
		वापस -EINVAL;
	अगर (drain < 0 || drain > 1)
		वापस -EINVAL;

	mutex_lock(&mvm->mutex);

	mvmsta = iwl_mvm_sta_from_staid_रक्षित(mvm, sta_id);

	अगर (!mvmsta)
		ret = -ENOENT;
	अन्यथा
		ret = iwl_mvm_drain_sta(mvm, mvmsta, drain) ? : count;

	mutex_unlock(&mvm->mutex);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_sram_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_mvm *mvm = file->निजी_data;
	स्थिर काष्ठा fw_img *img;
	अचिन्हित पूर्णांक ofs, len;
	माप_प्रकार ret;
	u8 *ptr;

	अगर (!iwl_mvm_firmware_running(mvm))
		वापस -EINVAL;

	/* शेष is to dump the entire data segment */
	img = &mvm->fw->img[mvm->fwrt.cur_fw_img];
	ofs = img->sec[IWL_UCODE_SECTION_DATA].offset;
	len = img->sec[IWL_UCODE_SECTION_DATA].len;

	अगर (mvm->dbgfs_sram_len) अणु
		ofs = mvm->dbgfs_sram_offset;
		len = mvm->dbgfs_sram_len;
	पूर्ण

	ptr = kzalloc(len, GFP_KERNEL);
	अगर (!ptr)
		वापस -ENOMEM;

	iwl_trans_पढ़ो_mem_bytes(mvm->trans, ofs, ptr, len);

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, ptr, len);

	kमुक्त(ptr);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_sram_ग_लिखो(काष्ठा iwl_mvm *mvm, अक्षर *buf,
				    माप_प्रकार count, loff_t *ppos)
अणु
	स्थिर काष्ठा fw_img *img;
	u32 offset, len;
	u32 img_offset, img_len;

	अगर (!iwl_mvm_firmware_running(mvm))
		वापस -EINVAL;

	img = &mvm->fw->img[mvm->fwrt.cur_fw_img];
	img_offset = img->sec[IWL_UCODE_SECTION_DATA].offset;
	img_len = img->sec[IWL_UCODE_SECTION_DATA].len;

	अगर (माला_पूछो(buf, "%x,%x", &offset, &len) == 2) अणु
		अगर ((offset & 0x3) || (len & 0x3))
			वापस -EINVAL;

		अगर (offset + len > img_offset + img_len)
			वापस -EINVAL;

		mvm->dbgfs_sram_offset = offset;
		mvm->dbgfs_sram_len = len;
	पूर्ण अन्यथा अणु
		mvm->dbgfs_sram_offset = 0;
		mvm->dbgfs_sram_len = 0;
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_set_nic_temperature_पढ़ो(काष्ठा file *file,
						  अक्षर __user *user_buf,
						  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_mvm *mvm = file->निजी_data;
	अक्षर buf[16];
	पूर्णांक pos;

	अगर (!mvm->temperature_test)
		pos = scnम_लिखो(buf , माप(buf), "disabled\n");
	अन्यथा
		pos = scnम_लिखो(buf , माप(buf), "%d\n", mvm->temperature);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

/*
 * Set NIC Temperature
 * Cause the driver to ignore the actual NIC temperature reported by the FW
 * Enable: any value between IWL_MVM_DEBUG_SET_TEMPERATURE_MIN -
 * IWL_MVM_DEBUG_SET_TEMPERATURE_MAX
 * Disable: IWL_MVM_DEBUG_SET_TEMPERATURE_DISABLE
 */
अटल sमाप_प्रकार iwl_dbgfs_set_nic_temperature_ग_लिखो(काष्ठा iwl_mvm *mvm,
						   अक्षर *buf, माप_प्रकार count,
						   loff_t *ppos)
अणु
	पूर्णांक temperature;

	अगर (!iwl_mvm_firmware_running(mvm) && !mvm->temperature_test)
		वापस -EIO;

	अगर (kstrtoपूर्णांक(buf, 10, &temperature))
		वापस -EINVAL;
	/* not a legal temperature */
	अगर ((temperature > IWL_MVM_DEBUG_SET_TEMPERATURE_MAX &&
	     temperature != IWL_MVM_DEBUG_SET_TEMPERATURE_DISABLE) ||
	    temperature < IWL_MVM_DEBUG_SET_TEMPERATURE_MIN)
		वापस -EINVAL;

	mutex_lock(&mvm->mutex);
	अगर (temperature == IWL_MVM_DEBUG_SET_TEMPERATURE_DISABLE) अणु
		अगर (!mvm->temperature_test)
			जाओ out;

		mvm->temperature_test = false;
		/* Since we can't पढ़ो the temp जबतक awake, just set
		 * it to zero until we get the next RX stats from the
		 * firmware.
		 */
		mvm->temperature = 0;
	पूर्ण अन्यथा अणु
		mvm->temperature_test = true;
		mvm->temperature = temperature;
	पूर्ण
	IWL_DEBUG_TEMP(mvm, "%sabling debug set temperature (temp = %d)\n",
		       mvm->temperature_test ? "En" : "Dis" ,
		       mvm->temperature);
	/* handle the temperature change */
	iwl_mvm_tt_handler(mvm);

out:
	mutex_unlock(&mvm->mutex);

	वापस count;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_nic_temp_पढ़ो(काष्ठा file *file,
				       अक्षर __user *user_buf,
				       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_mvm *mvm = file->निजी_data;
	अक्षर buf[16];
	पूर्णांक pos, ret;
	s32 temp;

	अगर (!iwl_mvm_firmware_running(mvm))
		वापस -EIO;

	mutex_lock(&mvm->mutex);
	ret = iwl_mvm_get_temp(mvm, &temp);
	mutex_unlock(&mvm->mutex);

	अगर (ret)
		वापस -EIO;

	pos = scnम_लिखो(buf , माप(buf), "%d\n", temp);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल sमाप_प्रकार iwl_dbgfs_sar_geo_profile_पढ़ो(काष्ठा file *file,
					      अक्षर __user *user_buf,
					      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_mvm *mvm = file->निजी_data;
	अक्षर buf[256];
	पूर्णांक pos = 0;
	पूर्णांक bufsz = माप(buf);
	पूर्णांक tbl_idx;
	u8 *value;

	अगर (!iwl_mvm_firmware_running(mvm))
		वापस -EIO;

	mutex_lock(&mvm->mutex);
	tbl_idx = iwl_mvm_get_sar_geo_profile(mvm);
	अगर (tbl_idx < 0) अणु
		mutex_unlock(&mvm->mutex);
		वापस tbl_idx;
	पूर्ण

	अगर (!tbl_idx) अणु
		pos = scnम_लिखो(buf, bufsz,
				"SAR geographic profile disabled\n");
	पूर्ण अन्यथा अणु
		value = &mvm->fwrt.geo_profiles[tbl_idx - 1].values[0];

		pos += scnम_लिखो(buf + pos, bufsz - pos,
				 "Use geographic profile %d\n", tbl_idx);
		pos += scnम_लिखो(buf + pos, bufsz - pos,
				 "2.4GHz:\n\tChain A offset: %hhu dBm\n\tChain B offset: %hhu dBm\n\tmax tx power: %hhu dBm\n",
				 value[1], value[2], value[0]);
		pos += scnम_लिखो(buf + pos, bufsz - pos,
				 "5.2GHz:\n\tChain A offset: %hhu dBm\n\tChain B offset: %hhu dBm\n\tmax tx power: %hhu dBm\n",
				 value[4], value[5], value[3]);
	पूर्ण
	mutex_unlock(&mvm->mutex);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण
#पूर्ण_अगर

अटल sमाप_प्रकार iwl_dbgfs_stations_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
				       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_mvm *mvm = file->निजी_data;
	काष्ठा ieee80211_sta *sta;
	अक्षर buf[400];
	पूर्णांक i, pos = 0, bufsz = माप(buf);

	mutex_lock(&mvm->mutex);

	क्रम (i = 0; i < mvm->fw->ucode_capa.num_stations; i++) अणु
		pos += scnम_लिखो(buf + pos, bufsz - pos, "%.2d: ", i);
		sta = rcu_dereference_रक्षित(mvm->fw_id_to_mac_id[i],
						lockdep_is_held(&mvm->mutex));
		अगर (!sta)
			pos += scnम_लिखो(buf + pos, bufsz - pos, "N/A\n");
		अन्यथा अगर (IS_ERR(sta))
			pos += scnम_लिखो(buf + pos, bufsz - pos, "%ld\n",
					 PTR_ERR(sta));
		अन्यथा
			pos += scnम_लिखो(buf + pos, bufsz - pos, "%pM\n",
					 sta->addr);
	पूर्ण

	mutex_unlock(&mvm->mutex);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_rs_data_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_sta *sta = file->निजी_data;
	काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	काष्ठा iwl_lq_sta_rs_fw *lq_sta = &mvmsta->lq_sta.rs_fw;
	काष्ठा iwl_mvm *mvm = lq_sta->pers.drv;
	अटल स्थिर माप_प्रकार bufsz = 2048;
	अक्षर *buff;
	पूर्णांक desc = 0;
	sमाप_प्रकार ret;

	buff = kदो_स्मृति(bufsz, GFP_KERNEL);
	अगर (!buff)
		वापस -ENOMEM;

	mutex_lock(&mvm->mutex);

	desc += scnम_लिखो(buff + desc, bufsz - desc, "sta_id %d\n",
			  lq_sta->pers.sta_id);
	desc += scnम_लिखो(buff + desc, bufsz - desc,
			  "fixed rate 0x%X\n",
			  lq_sta->pers.dbg_fixed_rate);
	desc += scnम_लिखो(buff + desc, bufsz - desc,
			  "A-MPDU size limit %d\n",
			  lq_sta->pers.dbg_agg_frame_count_lim);
	desc += scnम_लिखो(buff + desc, bufsz - desc,
			  "valid_tx_ant %s%s%s\n",
		(iwl_mvm_get_valid_tx_ant(mvm) & ANT_A) ? "ANT_A," : "",
		(iwl_mvm_get_valid_tx_ant(mvm) & ANT_B) ? "ANT_B," : "",
		(iwl_mvm_get_valid_tx_ant(mvm) & ANT_C) ? "ANT_C" : "");
	desc += scnम_लिखो(buff + desc, bufsz - desc,
			  "last tx rate=0x%X ",
			  lq_sta->last_rate_n_flags);

	desc += rs_pretty_prपूर्णांक_rate(buff + desc, bufsz - desc,
				     lq_sta->last_rate_n_flags);
	अगर (desc < bufsz - 1)
		buff[desc++] = '\n';
	mutex_unlock(&mvm->mutex);

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buff, desc);
	kमुक्त(buff);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_amsdu_len_ग_लिखो(काष्ठा ieee80211_sta *sta,
					 अक्षर *buf, माप_प्रकार count,
					 loff_t *ppos)
अणु
	काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	पूर्णांक i;
	u16 amsdu_len;

	अगर (kstrtou16(buf, 0, &amsdu_len))
		वापस -EINVAL;

	/* only change from debug set <-> debug unset */
	अगर ((amsdu_len && mvmsta->orig_amsdu_len) ||
	    (!!amsdu_len && mvmsta->orig_amsdu_len))
		वापस -EBUSY;

	अगर (amsdu_len) अणु
		mvmsta->orig_amsdu_len = sta->max_amsdu_len;
		sta->max_amsdu_len = amsdu_len;
		क्रम (i = 0; i < ARRAY_SIZE(sta->max_tid_amsdu_len); i++)
			sta->max_tid_amsdu_len[i] = amsdu_len;
	पूर्ण अन्यथा अणु
		sta->max_amsdu_len = mvmsta->orig_amsdu_len;
		mvmsta->orig_amsdu_len = 0;
	पूर्ण
	वापस count;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_amsdu_len_पढ़ो(काष्ठा file *file,
					अक्षर __user *user_buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_sta *sta = file->निजी_data;
	काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);

	अक्षर buf[32];
	पूर्णांक pos;

	pos = scnम_लिखो(buf, माप(buf), "current %d ", sta->max_amsdu_len);
	pos += scnम_लिखो(buf + pos, माप(buf) - pos, "stored %d\n",
			 mvmsta->orig_amsdu_len);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_disable_घातer_off_पढ़ो(काष्ठा file *file,
						अक्षर __user *user_buf,
						माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_mvm *mvm = file->निजी_data;
	अक्षर buf[64];
	पूर्णांक bufsz = माप(buf);
	पूर्णांक pos = 0;

	pos += scnम_लिखो(buf+pos, bufsz-pos, "disable_power_off_d0=%d\n",
			 mvm->disable_घातer_off);
	pos += scnम_लिखो(buf+pos, bufsz-pos, "disable_power_off_d3=%d\n",
			 mvm->disable_घातer_off_d3);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_disable_घातer_off_ग_लिखो(काष्ठा iwl_mvm *mvm, अक्षर *buf,
						 माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक ret, val;

	अगर (!iwl_mvm_firmware_running(mvm))
		वापस -EIO;

	अगर (!म_भेदन("disable_power_off_d0=", buf, 21)) अणु
		अगर (माला_पूछो(buf + 21, "%d", &val) != 1)
			वापस -EINVAL;
		mvm->disable_घातer_off = val;
	पूर्ण अन्यथा अगर (!म_भेदन("disable_power_off_d3=", buf, 21)) अणु
		अगर (माला_पूछो(buf + 21, "%d", &val) != 1)
			वापस -EINVAL;
		mvm->disable_घातer_off_d3 = val;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&mvm->mutex);
	ret = iwl_mvm_घातer_update_device(mvm);
	mutex_unlock(&mvm->mutex);

	वापस ret ?: count;
पूर्ण

अटल
पूर्णांक iwl_mvm_coex_dump_mbox(काष्ठा iwl_bt_coex_profile_notअगर *notअगर, अक्षर *buf,
			   पूर्णांक pos, पूर्णांक bufsz)
अणु
	pos += scnम_लिखो(buf+pos, bufsz-pos, "MBOX dw0:\n");

	BT_MBOX_PRINT(0, LE_SLAVE_LAT, false);
	BT_MBOX_PRINT(0, LE_PROF1, false);
	BT_MBOX_PRINT(0, LE_PROF2, false);
	BT_MBOX_PRINT(0, LE_PROF_OTHER, false);
	BT_MBOX_PRINT(0, CHL_SEQ_N, false);
	BT_MBOX_PRINT(0, INBAND_S, false);
	BT_MBOX_PRINT(0, LE_MIN_RSSI, false);
	BT_MBOX_PRINT(0, LE_SCAN, false);
	BT_MBOX_PRINT(0, LE_ADV, false);
	BT_MBOX_PRINT(0, LE_MAX_TX_POWER, false);
	BT_MBOX_PRINT(0, OPEN_CON_1, true);

	pos += scnम_लिखो(buf+pos, bufsz-pos, "MBOX dw1:\n");

	BT_MBOX_PRINT(1, BR_MAX_TX_POWER, false);
	BT_MBOX_PRINT(1, IP_SR, false);
	BT_MBOX_PRINT(1, LE_MSTR, false);
	BT_MBOX_PRINT(1, AGGR_TRFC_LD, false);
	BT_MBOX_PRINT(1, MSG_TYPE, false);
	BT_MBOX_PRINT(1, SSN, true);

	pos += scnम_लिखो(buf+pos, bufsz-pos, "MBOX dw2:\n");

	BT_MBOX_PRINT(2, SNIFF_ACT, false);
	BT_MBOX_PRINT(2, PAG, false);
	BT_MBOX_PRINT(2, INQUIRY, false);
	BT_MBOX_PRINT(2, CONN, false);
	BT_MBOX_PRINT(2, SNIFF_INTERVAL, false);
	BT_MBOX_PRINT(2, DISC, false);
	BT_MBOX_PRINT(2, SCO_TX_ACT, false);
	BT_MBOX_PRINT(2, SCO_RX_ACT, false);
	BT_MBOX_PRINT(2, ESCO_RE_TX, false);
	BT_MBOX_PRINT(2, SCO_DURATION, true);

	pos += scnम_लिखो(buf+pos, bufsz-pos, "MBOX dw3:\n");

	BT_MBOX_PRINT(3, SCO_STATE, false);
	BT_MBOX_PRINT(3, SNIFF_STATE, false);
	BT_MBOX_PRINT(3, A2DP_STATE, false);
	BT_MBOX_PRINT(3, A2DP_SRC, false);
	BT_MBOX_PRINT(3, ACL_STATE, false);
	BT_MBOX_PRINT(3, MSTR_STATE, false);
	BT_MBOX_PRINT(3, OBX_STATE, false);
	BT_MBOX_PRINT(3, OPEN_CON_2, false);
	BT_MBOX_PRINT(3, TRAFFIC_LOAD, false);
	BT_MBOX_PRINT(3, CHL_SEQN_LSB, false);
	BT_MBOX_PRINT(3, INBAND_P, false);
	BT_MBOX_PRINT(3, MSG_TYPE_2, false);
	BT_MBOX_PRINT(3, SSN_2, false);
	BT_MBOX_PRINT(3, UPDATE_REQUEST, true);

	वापस pos;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_bt_notअगर_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
				       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_mvm *mvm = file->निजी_data;
	काष्ठा iwl_bt_coex_profile_notअगर *notअगर = &mvm->last_bt_notअगर;
	अक्षर *buf;
	पूर्णांक ret, pos = 0, bufsz = माप(अक्षर) * 1024;

	buf = kदो_स्मृति(bufsz, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	mutex_lock(&mvm->mutex);

	pos += iwl_mvm_coex_dump_mbox(notअगर, buf, pos, bufsz);

	pos += scnम_लिखो(buf + pos, bufsz - pos, "bt_ci_compliance = %d\n",
			 notअगर->bt_ci_compliance);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "primary_ch_lut = %d\n",
			 le32_to_cpu(notअगर->primary_ch_lut));
	pos += scnम_लिखो(buf + pos, bufsz - pos, "secondary_ch_lut = %d\n",
			 le32_to_cpu(notअगर->secondary_ch_lut));
	pos += scnम_लिखो(buf + pos,
			 bufsz - pos, "bt_activity_grading = %d\n",
			 le32_to_cpu(notअगर->bt_activity_grading));
	pos += scnम_लिखो(buf + pos, bufsz - pos, "bt_rrc = %d\n",
			 notअगर->rrc_status & 0xF);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "bt_ttc = %d\n",
			 notअगर->ttc_status & 0xF);

	pos += scnम_लिखो(buf + pos, bufsz - pos, "sync_sco = %d\n",
			 IWL_MVM_BT_COEX_SYNC2SCO);
	pos += scnम_लिखो(buf + pos, bufsz - pos, "mplut = %d\n",
			 IWL_MVM_BT_COEX_MPLUT);

	mutex_unlock(&mvm->mutex);

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
	kमुक्त(buf);

	वापस ret;
पूर्ण
#अघोषित BT_MBOX_PRINT

अटल sमाप_प्रकार iwl_dbgfs_bt_cmd_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
				     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_mvm *mvm = file->निजी_data;
	काष्ठा iwl_bt_coex_ci_cmd *cmd = &mvm->last_bt_ci_cmd;
	अक्षर buf[256];
	पूर्णांक bufsz = माप(buf);
	पूर्णांक pos = 0;

	mutex_lock(&mvm->mutex);

	pos += scnम_लिखो(buf + pos, bufsz - pos, "Channel inhibition CMD\n");
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 "\tPrimary Channel Bitmap 0x%016llx\n",
			 le64_to_cpu(cmd->bt_primary_ci));
	pos += scnम_लिखो(buf + pos, bufsz - pos,
			 "\tSecondary Channel Bitmap 0x%016llx\n",
			 le64_to_cpu(cmd->bt_secondary_ci));

	mutex_unlock(&mvm->mutex);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

अटल sमाप_प्रकार
iwl_dbgfs_bt_tx_prio_ग_लिखो(काष्ठा iwl_mvm *mvm, अक्षर *buf,
			   माप_प्रकार count, loff_t *ppos)
अणु
	u32 bt_tx_prio;

	अगर (माला_पूछो(buf, "%u", &bt_tx_prio) != 1)
		वापस -EINVAL;
	अगर (bt_tx_prio > 4)
		वापस -EINVAL;

	mvm->bt_tx_prio = bt_tx_prio;

	वापस count;
पूर्ण

अटल sमाप_प्रकार
iwl_dbgfs_bt_क्रमce_ant_ग_लिखो(काष्ठा iwl_mvm *mvm, अक्षर *buf,
			     माप_प्रकार count, loff_t *ppos)
अणु
	अटल स्थिर अक्षर * स्थिर modes_str[BT_FORCE_ANT_MAX] = अणु
		[BT_FORCE_ANT_DIS] = "dis",
		[BT_FORCE_ANT_AUTO] = "auto",
		[BT_FORCE_ANT_BT] = "bt",
		[BT_FORCE_ANT_WIFI] = "wifi",
	पूर्ण;
	पूर्णांक ret, bt_क्रमce_ant_mode;

	ret = match_string(modes_str, ARRAY_SIZE(modes_str), buf);
	अगर (ret < 0)
		वापस ret;

	bt_क्रमce_ant_mode = ret;
	ret = 0;
	mutex_lock(&mvm->mutex);
	अगर (mvm->bt_क्रमce_ant_mode == bt_क्रमce_ant_mode)
		जाओ out;

	mvm->bt_क्रमce_ant_mode = bt_क्रमce_ant_mode;
	IWL_DEBUG_COEX(mvm, "Force mode: %s\n",
		       modes_str[mvm->bt_क्रमce_ant_mode]);

	अगर (iwl_mvm_firmware_running(mvm))
		ret = iwl_mvm_send_bt_init_conf(mvm);
	अन्यथा
		ret = 0;

out:
	mutex_unlock(&mvm->mutex);
	वापस ret ?: count;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_fw_ver_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
				     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_mvm *mvm = file->निजी_data;
	अक्षर *buff, *pos, *endpos;
	अटल स्थिर माप_प्रकार bufsz = 1024;
	पूर्णांक ret;

	buff = kदो_स्मृति(bufsz, GFP_KERNEL);
	अगर (!buff)
		वापस -ENOMEM;

	pos = buff;
	endpos = pos + bufsz;

	pos += scnम_लिखो(pos, endpos - pos, "FW prefix: %s\n",
			 mvm->trans->cfg->fw_name_pre);
	pos += scnम_लिखो(pos, endpos - pos, "FW: %s\n",
			 mvm->fwrt.fw->human_पढ़ोable);
	pos += scnम_लिखो(pos, endpos - pos, "Device: %s\n",
			 mvm->fwrt.trans->name);
	pos += scnम_लिखो(pos, endpos - pos, "Bus: %s\n",
			 mvm->fwrt.dev->bus->name);

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buff, pos - buff);
	kमुक्त(buff);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_phy_पूर्णांकegration_ver_पढ़ो(काष्ठा file *file,
						  अक्षर __user *user_buf,
						  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_mvm *mvm = file->निजी_data;
	अक्षर *buf;
	माप_प्रकार bufsz;
	पूर्णांक pos;
	sमाप_प्रकार ret;

	bufsz = mvm->fw->phy_पूर्णांकegration_ver_len + 2;
	buf = kदो_स्मृति(bufsz, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	pos = scnम_लिखो(buf, bufsz, "%.*s\n", mvm->fw->phy_पूर्णांकegration_ver_len,
			mvm->fw->phy_पूर्णांकegration_ver);

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);

	kमुक्त(buf);
	वापस ret;
पूर्ण

#घोषणा PRINT_STATS_LE32(_काष्ठा, _memb)				\
			 pos += scnम_लिखो(buf + pos, bufsz - pos,	\
					  fmt_table, #_memb,		\
					  le32_to_cpu(_काष्ठा->_memb))

अटल sमाप_प्रकार iwl_dbgfs_fw_rx_stats_पढ़ो(काष्ठा file *file,
					  अक्षर __user *user_buf, माप_प्रकार count,
					  loff_t *ppos)
अणु
	काष्ठा iwl_mvm *mvm = file->निजी_data;
	अटल स्थिर अक्षर *fmt_table = "\t%-30s %10u\n";
	अटल स्थिर अक्षर *fmt_header = "%-32s\n";
	पूर्णांक pos = 0;
	अक्षर *buf;
	पूर्णांक ret;
	माप_प्रकार bufsz;

	अगर (iwl_mvm_has_new_rx_stats_api(mvm))
		bufsz = ((माप(काष्ठा mvm_statistics_rx) /
			  माप(__le32)) * 43) + (4 * 33) + 1;
	अन्यथा
		/* 43 = size of each data line; 33 = size of each header */
		bufsz = ((माप(काष्ठा mvm_statistics_rx_v3) /
			  माप(__le32)) * 43) + (4 * 33) + 1;

	buf = kzalloc(bufsz, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	mutex_lock(&mvm->mutex);

	अगर (iwl_mvm_firmware_running(mvm))
		iwl_mvm_request_statistics(mvm, false);

	pos += scnम_लिखो(buf + pos, bufsz - pos, fmt_header,
			 "Statistics_Rx - OFDM");
	अगर (!iwl_mvm_has_new_rx_stats_api(mvm)) अणु
		काष्ठा mvm_statistics_rx_phy_v2 *ofdm = &mvm->rx_stats_v3.ofdm;

		PRINT_STATS_LE32(ofdm, ina_cnt);
		PRINT_STATS_LE32(ofdm, fina_cnt);
		PRINT_STATS_LE32(ofdm, plcp_err);
		PRINT_STATS_LE32(ofdm, crc32_err);
		PRINT_STATS_LE32(ofdm, overrun_err);
		PRINT_STATS_LE32(ofdm, early_overrun_err);
		PRINT_STATS_LE32(ofdm, crc32_good);
		PRINT_STATS_LE32(ofdm, false_alarm_cnt);
		PRINT_STATS_LE32(ofdm, fina_sync_err_cnt);
		PRINT_STATS_LE32(ofdm, sfd_समयout);
		PRINT_STATS_LE32(ofdm, fina_समयout);
		PRINT_STATS_LE32(ofdm, unresponded_rts);
		PRINT_STATS_LE32(ofdm, rxe_frame_lmt_overrun);
		PRINT_STATS_LE32(ofdm, sent_ack_cnt);
		PRINT_STATS_LE32(ofdm, sent_cts_cnt);
		PRINT_STATS_LE32(ofdm, sent_ba_rsp_cnt);
		PRINT_STATS_LE32(ofdm, dsp_self_समाप्त);
		PRINT_STATS_LE32(ofdm, mh_क्रमmat_err);
		PRINT_STATS_LE32(ofdm, re_acq_मुख्य_rssi_sum);
		PRINT_STATS_LE32(ofdm, reserved);
	पूर्ण अन्यथा अणु
		काष्ठा mvm_statistics_rx_phy *ofdm = &mvm->rx_stats.ofdm;

		PRINT_STATS_LE32(ofdm, unresponded_rts);
		PRINT_STATS_LE32(ofdm, rxe_frame_lmt_overrun);
		PRINT_STATS_LE32(ofdm, sent_ba_rsp_cnt);
		PRINT_STATS_LE32(ofdm, dsp_self_समाप्त);
		PRINT_STATS_LE32(ofdm, reserved);
	पूर्ण

	pos += scnम_लिखो(buf + pos, bufsz - pos, fmt_header,
			 "Statistics_Rx - CCK");
	अगर (!iwl_mvm_has_new_rx_stats_api(mvm)) अणु
		काष्ठा mvm_statistics_rx_phy_v2 *cck = &mvm->rx_stats_v3.cck;

		PRINT_STATS_LE32(cck, ina_cnt);
		PRINT_STATS_LE32(cck, fina_cnt);
		PRINT_STATS_LE32(cck, plcp_err);
		PRINT_STATS_LE32(cck, crc32_err);
		PRINT_STATS_LE32(cck, overrun_err);
		PRINT_STATS_LE32(cck, early_overrun_err);
		PRINT_STATS_LE32(cck, crc32_good);
		PRINT_STATS_LE32(cck, false_alarm_cnt);
		PRINT_STATS_LE32(cck, fina_sync_err_cnt);
		PRINT_STATS_LE32(cck, sfd_समयout);
		PRINT_STATS_LE32(cck, fina_समयout);
		PRINT_STATS_LE32(cck, unresponded_rts);
		PRINT_STATS_LE32(cck, rxe_frame_lmt_overrun);
		PRINT_STATS_LE32(cck, sent_ack_cnt);
		PRINT_STATS_LE32(cck, sent_cts_cnt);
		PRINT_STATS_LE32(cck, sent_ba_rsp_cnt);
		PRINT_STATS_LE32(cck, dsp_self_समाप्त);
		PRINT_STATS_LE32(cck, mh_क्रमmat_err);
		PRINT_STATS_LE32(cck, re_acq_मुख्य_rssi_sum);
		PRINT_STATS_LE32(cck, reserved);
	पूर्ण अन्यथा अणु
		काष्ठा mvm_statistics_rx_phy *cck = &mvm->rx_stats.cck;

		PRINT_STATS_LE32(cck, unresponded_rts);
		PRINT_STATS_LE32(cck, rxe_frame_lmt_overrun);
		PRINT_STATS_LE32(cck, sent_ba_rsp_cnt);
		PRINT_STATS_LE32(cck, dsp_self_समाप्त);
		PRINT_STATS_LE32(cck, reserved);
	पूर्ण

	pos += scnम_लिखो(buf + pos, bufsz - pos, fmt_header,
			 "Statistics_Rx - GENERAL");
	अगर (!iwl_mvm_has_new_rx_stats_api(mvm)) अणु
		काष्ठा mvm_statistics_rx_non_phy_v3 *general =
			&mvm->rx_stats_v3.general;

		PRINT_STATS_LE32(general, bogus_cts);
		PRINT_STATS_LE32(general, bogus_ack);
		PRINT_STATS_LE32(general, non_bssid_frames);
		PRINT_STATS_LE32(general, filtered_frames);
		PRINT_STATS_LE32(general, non_channel_beacons);
		PRINT_STATS_LE32(general, channel_beacons);
		PRINT_STATS_LE32(general, num_missed_bcon);
		PRINT_STATS_LE32(general, adc_rx_saturation_समय);
		PRINT_STATS_LE32(general, ina_detection_search_समय);
		PRINT_STATS_LE32(general, beacon_silence_rssi_a);
		PRINT_STATS_LE32(general, beacon_silence_rssi_b);
		PRINT_STATS_LE32(general, beacon_silence_rssi_c);
		PRINT_STATS_LE32(general, पूर्णांकerference_data_flag);
		PRINT_STATS_LE32(general, channel_load);
		PRINT_STATS_LE32(general, dsp_false_alarms);
		PRINT_STATS_LE32(general, beacon_rssi_a);
		PRINT_STATS_LE32(general, beacon_rssi_b);
		PRINT_STATS_LE32(general, beacon_rssi_c);
		PRINT_STATS_LE32(general, beacon_energy_a);
		PRINT_STATS_LE32(general, beacon_energy_b);
		PRINT_STATS_LE32(general, beacon_energy_c);
		PRINT_STATS_LE32(general, num_bt_समाप्तs);
		PRINT_STATS_LE32(general, mac_id);
		PRINT_STATS_LE32(general, directed_data_mpdu);
	पूर्ण अन्यथा अणु
		काष्ठा mvm_statistics_rx_non_phy *general =
			&mvm->rx_stats.general;

		PRINT_STATS_LE32(general, bogus_cts);
		PRINT_STATS_LE32(general, bogus_ack);
		PRINT_STATS_LE32(general, non_channel_beacons);
		PRINT_STATS_LE32(general, channel_beacons);
		PRINT_STATS_LE32(general, num_missed_bcon);
		PRINT_STATS_LE32(general, adc_rx_saturation_समय);
		PRINT_STATS_LE32(general, ina_detection_search_समय);
		PRINT_STATS_LE32(general, beacon_silence_rssi_a);
		PRINT_STATS_LE32(general, beacon_silence_rssi_b);
		PRINT_STATS_LE32(general, beacon_silence_rssi_c);
		PRINT_STATS_LE32(general, पूर्णांकerference_data_flag);
		PRINT_STATS_LE32(general, channel_load);
		PRINT_STATS_LE32(general, beacon_rssi_a);
		PRINT_STATS_LE32(general, beacon_rssi_b);
		PRINT_STATS_LE32(general, beacon_rssi_c);
		PRINT_STATS_LE32(general, beacon_energy_a);
		PRINT_STATS_LE32(general, beacon_energy_b);
		PRINT_STATS_LE32(general, beacon_energy_c);
		PRINT_STATS_LE32(general, num_bt_समाप्तs);
		PRINT_STATS_LE32(general, mac_id);
	पूर्ण

	pos += scnम_लिखो(buf + pos, bufsz - pos, fmt_header,
			 "Statistics_Rx - HT");
	अगर (!iwl_mvm_has_new_rx_stats_api(mvm)) अणु
		काष्ठा mvm_statistics_rx_ht_phy_v1 *ht =
			&mvm->rx_stats_v3.ofdm_ht;

		PRINT_STATS_LE32(ht, plcp_err);
		PRINT_STATS_LE32(ht, overrun_err);
		PRINT_STATS_LE32(ht, early_overrun_err);
		PRINT_STATS_LE32(ht, crc32_good);
		PRINT_STATS_LE32(ht, crc32_err);
		PRINT_STATS_LE32(ht, mh_क्रमmat_err);
		PRINT_STATS_LE32(ht, agg_crc32_good);
		PRINT_STATS_LE32(ht, agg_mpdu_cnt);
		PRINT_STATS_LE32(ht, agg_cnt);
		PRINT_STATS_LE32(ht, unsupport_mcs);
	पूर्ण अन्यथा अणु
		काष्ठा mvm_statistics_rx_ht_phy *ht =
			&mvm->rx_stats.ofdm_ht;

		PRINT_STATS_LE32(ht, mh_क्रमmat_err);
		PRINT_STATS_LE32(ht, agg_mpdu_cnt);
		PRINT_STATS_LE32(ht, agg_cnt);
		PRINT_STATS_LE32(ht, unsupport_mcs);
	पूर्ण

	mutex_unlock(&mvm->mutex);

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
	kमुक्त(buf);

	वापस ret;
पूर्ण
#अघोषित PRINT_STAT_LE32

अटल sमाप_प्रकार iwl_dbgfs_frame_stats_पढ़ो(काष्ठा iwl_mvm *mvm,
					  अक्षर __user *user_buf, माप_प्रकार count,
					  loff_t *ppos,
					  काष्ठा iwl_mvm_frame_stats *stats)
अणु
	अक्षर *buff, *pos, *endpos;
	पूर्णांक idx, i;
	पूर्णांक ret;
	अटल स्थिर माप_प्रकार bufsz = 1024;

	buff = kदो_स्मृति(bufsz, GFP_KERNEL);
	अगर (!buff)
		वापस -ENOMEM;

	spin_lock_bh(&mvm->drv_stats_lock);

	pos = buff;
	endpos = pos + bufsz;

	pos += scnम_लिखो(pos, endpos - pos,
			 "Legacy/HT/VHT\t:\t%d/%d/%d\n",
			 stats->legacy_frames,
			 stats->ht_frames,
			 stats->vht_frames);
	pos += scnम_लिखो(pos, endpos - pos, "20/40/80\t:\t%d/%d/%d\n",
			 stats->bw_20_frames,
			 stats->bw_40_frames,
			 stats->bw_80_frames);
	pos += scnम_लिखो(pos, endpos - pos, "NGI/SGI\t\t:\t%d/%d\n",
			 stats->ngi_frames,
			 stats->sgi_frames);
	pos += scnम_लिखो(pos, endpos - pos, "SISO/MIMO2\t:\t%d/%d\n",
			 stats->siso_frames,
			 stats->mimo2_frames);
	pos += scnम_लिखो(pos, endpos - pos, "FAIL/SCSS\t:\t%d/%d\n",
			 stats->fail_frames,
			 stats->success_frames);
	pos += scnम_लिखो(pos, endpos - pos, "MPDUs agg\t:\t%d\n",
			 stats->agg_frames);
	pos += scnम_लिखो(pos, endpos - pos, "A-MPDUs\t\t:\t%d\n",
			 stats->ampdu_count);
	pos += scnम_लिखो(pos, endpos - pos, "Avg MPDUs/A-MPDU:\t%d\n",
			 stats->ampdu_count > 0 ?
			 (stats->agg_frames / stats->ampdu_count) : 0);

	pos += scnम_लिखो(pos, endpos - pos, "Last Rates\n");

	idx = stats->last_frame_idx - 1;
	क्रम (i = 0; i < ARRAY_SIZE(stats->last_rates); i++) अणु
		idx = (idx + 1) % ARRAY_SIZE(stats->last_rates);
		अगर (stats->last_rates[idx] == 0)
			जारी;
		pos += scnम_लिखो(pos, endpos - pos, "Rate[%d]: ",
				 (पूर्णांक)(ARRAY_SIZE(stats->last_rates) - i));
		pos += rs_pretty_prपूर्णांक_rate(pos, endpos - pos,
					    stats->last_rates[idx]);
		अगर (pos < endpos - 1)
			*pos++ = '\n';
	पूर्ण
	spin_unlock_bh(&mvm->drv_stats_lock);

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buff, pos - buff);
	kमुक्त(buff);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_drv_rx_stats_पढ़ो(काष्ठा file *file,
					   अक्षर __user *user_buf, माप_प्रकार count,
					   loff_t *ppos)
अणु
	काष्ठा iwl_mvm *mvm = file->निजी_data;

	वापस iwl_dbgfs_frame_stats_पढ़ो(mvm, user_buf, count, ppos,
					  &mvm->drv_rx_stats);
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_fw_restart_ग_लिखो(काष्ठा iwl_mvm *mvm, अक्षर *buf,
					  माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक __maybe_unused ret;

	अगर (!iwl_mvm_firmware_running(mvm))
		वापस -EIO;

	mutex_lock(&mvm->mutex);

	/* allow one more restart that we're provoking here */
	अगर (mvm->fw_restart >= 0)
		mvm->fw_restart++;

	/* take the वापस value to make compiler happy - it will fail anyway */
	ret = iwl_mvm_send_cmd_pdu(mvm, REPLY_ERROR, 0, 0, शून्य);

	mutex_unlock(&mvm->mutex);

	वापस count;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_fw_nmi_ग_लिखो(काष्ठा iwl_mvm *mvm, अक्षर *buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	अगर (!iwl_mvm_firmware_running(mvm))
		वापस -EIO;

	iwl_क्रमce_nmi(mvm->trans);

	वापस count;
पूर्ण

अटल sमाप_प्रकार
iwl_dbgfs_scan_ant_rxchain_पढ़ो(काष्ठा file *file,
				अक्षर __user *user_buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_mvm *mvm = file->निजी_data;
	पूर्णांक pos = 0;
	अक्षर buf[32];
	स्थिर माप_प्रकार bufsz = माप(buf);

	/* prपूर्णांक which antennas were set क्रम the scan command by the user */
	pos += scnम_लिखो(buf + pos, bufsz - pos, "Antennas for scan: ");
	अगर (mvm->scan_rx_ant & ANT_A)
		pos += scnम_लिखो(buf + pos, bufsz - pos, "A");
	अगर (mvm->scan_rx_ant & ANT_B)
		pos += scnम_लिखो(buf + pos, bufsz - pos, "B");
	अगर (mvm->scan_rx_ant & ANT_C)
		pos += scnम_लिखो(buf + pos, bufsz - pos, "C");
	pos += scnम_लिखो(buf + pos, bufsz - pos, " (%hhx)\n", mvm->scan_rx_ant);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

अटल sमाप_प्रकार
iwl_dbgfs_scan_ant_rxchain_ग_लिखो(काष्ठा iwl_mvm *mvm, अक्षर *buf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	u8 scan_rx_ant;

	अगर (!iwl_mvm_firmware_running(mvm))
		वापस -EIO;

	अगर (माला_पूछो(buf, "%hhx", &scan_rx_ant) != 1)
		वापस -EINVAL;
	अगर (scan_rx_ant > ANT_ABC)
		वापस -EINVAL;
	अगर (scan_rx_ant & ~(iwl_mvm_get_valid_rx_ant(mvm)))
		वापस -EINVAL;

	अगर (mvm->scan_rx_ant != scan_rx_ant) अणु
		mvm->scan_rx_ant = scan_rx_ant;
		अगर (fw_has_capa(&mvm->fw->ucode_capa,
				IWL_UCODE_TLV_CAPA_UMAC_SCAN))
			iwl_mvm_config_scan(mvm);
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_indirection_tbl_ग_लिखो(काष्ठा iwl_mvm *mvm,
					       अक्षर *buf, माप_प्रकार count,
					       loff_t *ppos)
अणु
	काष्ठा iwl_rss_config_cmd cmd = अणु
		.flags = cpu_to_le32(IWL_RSS_ENABLE),
		.hash_mask = IWL_RSS_HASH_TYPE_IPV4_TCP |
			     IWL_RSS_HASH_TYPE_IPV4_UDP |
			     IWL_RSS_HASH_TYPE_IPV4_PAYLOAD |
			     IWL_RSS_HASH_TYPE_IPV6_TCP |
			     IWL_RSS_HASH_TYPE_IPV6_UDP |
			     IWL_RSS_HASH_TYPE_IPV6_PAYLOAD,
	पूर्ण;
	पूर्णांक ret, i, num_repeats, nbytes = count / 2;

	ret = hex2bin(cmd.indirection_table, buf, nbytes);
	अगर (ret)
		वापस ret;

	/*
	 * The input is the redirection table, partial or full.
	 * Repeat the pattern अगर needed.
	 * For example, input of 01020F will be repeated 42 बार,
	 * indirecting RSS hash results to queues 1, 2, 15 (skipping
	 * queues 3 - 14).
	 */
	num_repeats = ARRAY_SIZE(cmd.indirection_table) / nbytes;
	क्रम (i = 1; i < num_repeats; i++)
		स_नकल(&cmd.indirection_table[i * nbytes],
		       cmd.indirection_table, nbytes);
	/* handle cut in the middle pattern क्रम the last places */
	स_नकल(&cmd.indirection_table[i * nbytes], cmd.indirection_table,
	       ARRAY_SIZE(cmd.indirection_table) % nbytes);

	netdev_rss_key_fill(cmd.secret_key, माप(cmd.secret_key));

	mutex_lock(&mvm->mutex);
	अगर (iwl_mvm_firmware_running(mvm))
		ret = iwl_mvm_send_cmd_pdu(mvm, RSS_CONFIG_CMD, 0,
					   माप(cmd), &cmd);
	अन्यथा
		ret = 0;
	mutex_unlock(&mvm->mutex);

	वापस ret ?: count;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_inject_packet_ग_लिखो(काष्ठा iwl_mvm *mvm,
					     अक्षर *buf, माप_प्रकार count,
					     loff_t *ppos)
अणु
	काष्ठा iwl_op_mode *opmode = container_of((व्योम *)mvm,
						  काष्ठा iwl_op_mode,
						  op_mode_specअगरic);
	काष्ठा iwl_rx_cmd_buffer rxb = अणु
		._rx_page_order = 0,
		.truesize = 0, /* not used */
		._offset = 0,
	पूर्ण;
	काष्ठा iwl_rx_packet *pkt;
	पूर्णांक bin_len = count / 2;
	पूर्णांक ret = -EINVAL;

	अगर (!iwl_mvm_firmware_running(mvm))
		वापस -EIO;

	/* supporting only MQ RX */
	अगर (!mvm->trans->trans_cfg->mq_rx_supported)
		वापस -ENOTSUPP;

	rxb._page = alloc_pages(GFP_ATOMIC, 0);
	अगर (!rxb._page)
		वापस -ENOMEM;
	pkt = rxb_addr(&rxb);

	ret = hex2bin(page_address(rxb._page), buf, bin_len);
	अगर (ret)
		जाओ out;

	/* aव्योम invalid memory access and malक्रमmed packet */
	अगर (bin_len < माप(*pkt) ||
	    bin_len != माप(*pkt) + iwl_rx_packet_payload_len(pkt))
		जाओ out;

	local_bh_disable();
	iwl_mvm_rx_mq(opmode, शून्य, &rxb);
	local_bh_enable();
	ret = 0;

out:
	iwl_मुक्त_rxb(&rxb);

	वापस ret ?: count;
पूर्ण

अटल पूर्णांक _iwl_dbgfs_inject_beacon_ie(काष्ठा iwl_mvm *mvm, अक्षर *bin, पूर्णांक len)
अणु
	काष्ठा ieee80211_vअगर *vअगर;
	काष्ठा iwl_mvm_vअगर *mvmvअगर;
	काष्ठा sk_buff *beacon;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा iwl_mac_beacon_cmd beacon_cmd = अणुपूर्ण;
	u8 rate;
	u16 flags;
	पूर्णांक i;

	len /= 2;

	/* Element len should be represented by u8 */
	अगर (len >= U8_MAX)
		वापस -EINVAL;

	अगर (!iwl_mvm_firmware_running(mvm))
		वापस -EIO;

	अगर (!iwl_mvm_has_new_tx_api(mvm) &&
	    !fw_has_api(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_API_NEW_BEACON_TEMPLATE))
		वापस -EINVAL;

	mutex_lock(&mvm->mutex);

	क्रम (i = 0; i < NUM_MAC_INDEX_DRIVER; i++) अणु
		vअगर = iwl_mvm_rcu_dereference_vअगर_id(mvm, i, false);
		अगर (!vअगर)
			जारी;

		अगर (vअगर->type == NL80211_IFTYPE_AP)
			अवरोध;
	पूर्ण

	अगर (i == NUM_MAC_INDEX_DRIVER || !vअगर)
		जाओ out_err;

	mvm->hw->extra_beacon_tailroom = len;

	beacon = ieee80211_beacon_get_ढाँचा(mvm->hw, vअगर, शून्य);
	अगर (!beacon)
		जाओ out_err;

	अगर (len && hex2bin(skb_put_zero(beacon, len), bin, len)) अणु
		dev_kमुक्त_skb(beacon);
		जाओ out_err;
	पूर्ण

	mvm->beacon_inject_active = true;

	mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	info = IEEE80211_SKB_CB(beacon);
	rate = iwl_mvm_mac_ctxt_get_lowest_rate(info, vअगर);
	flags = iwl_mvm_mac80211_idx_to_hwrate(rate);

	अगर (rate == IWL_FIRST_CCK_RATE)
		flags |= IWL_MAC_BEACON_CCK;

	beacon_cmd.flags = cpu_to_le16(flags);
	beacon_cmd.byte_cnt = cpu_to_le16((u16)beacon->len);
	beacon_cmd.ढाँचा_id = cpu_to_le32((u32)mvmvअगर->id);

	iwl_mvm_mac_ctxt_set_tim(mvm, &beacon_cmd.tim_idx,
				 &beacon_cmd.tim_size,
				 beacon->data, beacon->len);

	iwl_mvm_mac_ctxt_send_beacon_cmd(mvm, beacon, &beacon_cmd,
					 माप(beacon_cmd));
	mutex_unlock(&mvm->mutex);

	dev_kमुक्त_skb(beacon);

	वापस 0;

out_err:
	mutex_unlock(&mvm->mutex);
	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_inject_beacon_ie_ग_लिखो(काष्ठा iwl_mvm *mvm,
						अक्षर *buf, माप_प्रकार count,
						loff_t *ppos)
अणु
	पूर्णांक ret = _iwl_dbgfs_inject_beacon_ie(mvm, buf, count);

	mvm->hw->extra_beacon_tailroom = 0;
	वापस ret ?: count;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_inject_beacon_ie_restore_ग_लिखो(काष्ठा iwl_mvm *mvm,
							अक्षर *buf,
							माप_प्रकार count,
							loff_t *ppos)
अणु
	पूर्णांक ret = _iwl_dbgfs_inject_beacon_ie(mvm, शून्य, 0);

	mvm->hw->extra_beacon_tailroom = 0;
	mvm->beacon_inject_active = false;
	वापस ret ?: count;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_fw_dbg_conf_पढ़ो(काष्ठा file *file,
					  अक्षर __user *user_buf,
					  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_mvm *mvm = file->निजी_data;
	पूर्णांक conf;
	अक्षर buf[8];
	स्थिर माप_प्रकार bufsz = माप(buf);
	पूर्णांक pos = 0;

	mutex_lock(&mvm->mutex);
	conf = mvm->fwrt.dump.conf;
	mutex_unlock(&mvm->mutex);

	pos += scnम_लिखो(buf + pos, bufsz - pos, "%d\n", conf);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_fw_dbg_conf_ग_लिखो(काष्ठा iwl_mvm *mvm,
					   अक्षर *buf, माप_प्रकार count,
					   loff_t *ppos)
अणु
	अचिन्हित पूर्णांक conf_id;
	पूर्णांक ret;

	अगर (!iwl_mvm_firmware_running(mvm))
		वापस -EIO;

	ret = kstrtouपूर्णांक(buf, 0, &conf_id);
	अगर (ret)
		वापस ret;

	अगर (WARN_ON(conf_id >= FW_DBG_CONF_MAX))
		वापस -EINVAL;

	mutex_lock(&mvm->mutex);
	ret = iwl_fw_start_dbg_conf(&mvm->fwrt, conf_id);
	mutex_unlock(&mvm->mutex);

	वापस ret ?: count;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_fw_dbg_collect_ग_लिखो(काष्ठा iwl_mvm *mvm,
					      अक्षर *buf, माप_प्रकार count,
					      loff_t *ppos)
अणु
	अगर (count == 0)
		वापस 0;

	iwl_dbg_tlv_समय_poपूर्णांक(&mvm->fwrt, IWL_FW_INI_TIME_POINT_USER_TRIGGER,
			       शून्य);

	iwl_fw_dbg_collect(&mvm->fwrt, FW_DBG_TRIGGER_USER, buf,
			   (count - 1), शून्य);

	वापस count;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_dbg_समय_poपूर्णांक_ग_लिखो(काष्ठा iwl_mvm *mvm,
					      अक्षर *buf, माप_प्रकार count,
					      loff_t *ppos)
अणु
	u32 समयpoपूर्णांक;

	अगर (kstrtou32(buf, 0, &समयpoपूर्णांक))
		वापस -EINVAL;

	अगर (समयpoपूर्णांक == IWL_FW_INI_TIME_POINT_INVALID ||
	    समयpoपूर्णांक >= IWL_FW_INI_TIME_POINT_NUM)
		वापस -EINVAL;

	iwl_dbg_tlv_समय_poपूर्णांक(&mvm->fwrt, समयpoपूर्णांक, शून्य);

	वापस count;
पूर्ण

#घोषणा ADD_TEXT(...) pos += scnम_लिखो(buf + pos, bufsz - pos, __VA_ARGS__)
#अगर_घोषित CONFIG_IWLWIFI_BCAST_FILTERING
अटल sमाप_प्रकार iwl_dbgfs_bcast_filters_पढ़ो(काष्ठा file *file,
					    अक्षर __user *user_buf,
					    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_mvm *mvm = file->निजी_data;
	काष्ठा iwl_bcast_filter_cmd cmd;
	स्थिर काष्ठा iwl_fw_bcast_filter *filter;
	अक्षर *buf;
	पूर्णांक bufsz = 1024;
	पूर्णांक i, j, pos = 0;
	sमाप_प्रकार ret;

	buf = kzalloc(bufsz, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	mutex_lock(&mvm->mutex);
	अगर (!iwl_mvm_bcast_filter_build_cmd(mvm, &cmd)) अणु
		ADD_TEXT("None\n");
		mutex_unlock(&mvm->mutex);
		जाओ out;
	पूर्ण
	mutex_unlock(&mvm->mutex);

	क्रम (i = 0; cmd.filters[i].attrs[0].mask; i++) अणु
		filter = &cmd.filters[i];

		ADD_TEXT("Filter [%d]:\n", i);
		ADD_TEXT("\tDiscard=%d\n", filter->discard);
		ADD_TEXT("\tFrame Type: %s\n",
			 filter->frame_type ? "IPv4" : "Generic");

		क्रम (j = 0; j < ARRAY_SIZE(filter->attrs); j++) अणु
			स्थिर काष्ठा iwl_fw_bcast_filter_attr *attr;

			attr = &filter->attrs[j];
			अगर (!attr->mask)
				अवरोध;

			ADD_TEXT("\tAttr [%d]: offset=%d (from %s), mask=0x%x, value=0x%x reserved=0x%x\n",
				 j, attr->offset,
				 attr->offset_type ? "IP End" :
						     "Payload Start",
				 be32_to_cpu(attr->mask),
				 be32_to_cpu(attr->val),
				 le16_to_cpu(attr->reserved1));
		पूर्ण
	पूर्ण
out:
	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_bcast_filters_ग_लिखो(काष्ठा iwl_mvm *mvm, अक्षर *buf,
					     माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक pos, next_pos;
	काष्ठा iwl_fw_bcast_filter filter = अणुपूर्ण;
	काष्ठा iwl_bcast_filter_cmd cmd;
	u32 filter_id, attr_id, mask, value;
	पूर्णांक err = 0;

	अगर (माला_पूछो(buf, "%d %hhi %hhi %n", &filter_id, &filter.discard,
		   &filter.frame_type, &pos) != 3)
		वापस -EINVAL;

	अगर (filter_id >= ARRAY_SIZE(mvm->dbgfs_bcast_filtering.cmd.filters) ||
	    filter.frame_type > BCAST_FILTER_FRAME_TYPE_IPV4)
		वापस -EINVAL;

	क्रम (attr_id = 0; attr_id < ARRAY_SIZE(filter.attrs);
	     attr_id++) अणु
		काष्ठा iwl_fw_bcast_filter_attr *attr =
				&filter.attrs[attr_id];

		अगर (pos >= count)
			अवरोध;

		अगर (माला_पूछो(&buf[pos], "%hhi %hhi %i %i %n",
			   &attr->offset, &attr->offset_type,
			   &mask, &value, &next_pos) != 4)
			वापस -EINVAL;

		attr->mask = cpu_to_be32(mask);
		attr->val = cpu_to_be32(value);
		अगर (mask)
			filter.num_attrs++;

		pos += next_pos;
	पूर्ण

	mutex_lock(&mvm->mutex);
	स_नकल(&mvm->dbgfs_bcast_filtering.cmd.filters[filter_id],
	       &filter, माप(filter));

	/* send updated bcast filtering configuration */
	अगर (iwl_mvm_firmware_running(mvm) &&
	    mvm->dbgfs_bcast_filtering.override &&
	    iwl_mvm_bcast_filter_build_cmd(mvm, &cmd))
		err = iwl_mvm_send_cmd_pdu(mvm, BCAST_FILTER_CMD, 0,
					   माप(cmd), &cmd);
	mutex_unlock(&mvm->mutex);

	वापस err ?: count;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_bcast_filters_macs_पढ़ो(काष्ठा file *file,
						 अक्षर __user *user_buf,
						 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_mvm *mvm = file->निजी_data;
	काष्ठा iwl_bcast_filter_cmd cmd;
	अक्षर *buf;
	पूर्णांक bufsz = 1024;
	पूर्णांक i, pos = 0;
	sमाप_प्रकार ret;

	buf = kzalloc(bufsz, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	mutex_lock(&mvm->mutex);
	अगर (!iwl_mvm_bcast_filter_build_cmd(mvm, &cmd)) अणु
		ADD_TEXT("None\n");
		mutex_unlock(&mvm->mutex);
		जाओ out;
	पूर्ण
	mutex_unlock(&mvm->mutex);

	क्रम (i = 0; i < ARRAY_SIZE(cmd.macs); i++) अणु
		स्थिर काष्ठा iwl_fw_bcast_mac *mac = &cmd.macs[i];

		ADD_TEXT("Mac [%d]: discard=%d attached_filters=0x%x\n",
			 i, mac->शेष_discard, mac->attached_filters);
	पूर्ण
out:
	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_bcast_filters_macs_ग_लिखो(काष्ठा iwl_mvm *mvm,
						  अक्षर *buf, माप_प्रकार count,
						  loff_t *ppos)
अणु
	काष्ठा iwl_bcast_filter_cmd cmd;
	काष्ठा iwl_fw_bcast_mac mac = अणुपूर्ण;
	u32 mac_id, attached_filters;
	पूर्णांक err = 0;

	अगर (!mvm->bcast_filters)
		वापस -ENOENT;

	अगर (माला_पूछो(buf, "%d %hhi %i", &mac_id, &mac.शेष_discard,
		   &attached_filters) != 3)
		वापस -EINVAL;

	अगर (mac_id >= ARRAY_SIZE(cmd.macs) ||
	    mac.शेष_discard > 1 ||
	    attached_filters >= BIT(ARRAY_SIZE(cmd.filters)))
		वापस -EINVAL;

	mac.attached_filters = cpu_to_le16(attached_filters);

	mutex_lock(&mvm->mutex);
	स_नकल(&mvm->dbgfs_bcast_filtering.cmd.macs[mac_id],
	       &mac, माप(mac));

	/* send updated bcast filtering configuration */
	अगर (iwl_mvm_firmware_running(mvm) &&
	    mvm->dbgfs_bcast_filtering.override &&
	    iwl_mvm_bcast_filter_build_cmd(mvm, &cmd))
		err = iwl_mvm_send_cmd_pdu(mvm, BCAST_FILTER_CMD, 0,
					   माप(cmd), &cmd);
	mutex_unlock(&mvm->mutex);

	वापस err ?: count;
पूर्ण
#पूर्ण_अगर

#घोषणा MVM_DEBUGFS_WRITE_खाता_OPS(name, bufsz) \
	_MVM_DEBUGFS_WRITE_खाता_OPS(name, bufsz, काष्ठा iwl_mvm)
#घोषणा MVM_DEBUGFS_READ_WRITE_खाता_OPS(name, bufsz) \
	_MVM_DEBUGFS_READ_WRITE_खाता_OPS(name, bufsz, काष्ठा iwl_mvm)
#घोषणा MVM_DEBUGFS_ADD_खाता_ALIAS(alias, name, parent, mode) करो अणु	\
		debugfs_create_file(alias, mode, parent, mvm,		\
				    &iwl_dbgfs_##name##_ops);		\
	पूर्ण जबतक (0)
#घोषणा MVM_DEBUGFS_ADD_खाता(name, parent, mode) \
	MVM_DEBUGFS_ADD_खाता_ALIAS(#name, name, parent, mode)

#घोषणा MVM_DEBUGFS_WRITE_STA_खाता_OPS(name, bufsz) \
	_MVM_DEBUGFS_WRITE_खाता_OPS(name, bufsz, काष्ठा ieee80211_sta)
#घोषणा MVM_DEBUGFS_READ_WRITE_STA_खाता_OPS(name, bufsz) \
	_MVM_DEBUGFS_READ_WRITE_खाता_OPS(name, bufsz, काष्ठा ieee80211_sta)

#घोषणा MVM_DEBUGFS_ADD_STA_खाता_ALIAS(alias, name, parent, mode) करो अणु	\
		debugfs_create_file(alias, mode, parent, sta,		\
				    &iwl_dbgfs_##name##_ops);		\
	पूर्ण जबतक (0)
#घोषणा MVM_DEBUGFS_ADD_STA_खाता(name, parent, mode) \
	MVM_DEBUGFS_ADD_STA_खाता_ALIAS(#name, name, parent, mode)

अटल sमाप_प्रकार
iwl_dbgfs_prph_reg_पढ़ो(काष्ठा file *file,
			अक्षर __user *user_buf,
			माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_mvm *mvm = file->निजी_data;
	पूर्णांक pos = 0;
	अक्षर buf[32];
	स्थिर माप_प्रकार bufsz = माप(buf);

	अगर (!mvm->dbgfs_prph_reg_addr)
		वापस -EINVAL;

	pos += scnम_लिखो(buf + pos, bufsz - pos, "Reg 0x%x: (0x%x)\n",
		mvm->dbgfs_prph_reg_addr,
		iwl_पढ़ो_prph(mvm->trans, mvm->dbgfs_prph_reg_addr));

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

अटल sमाप_प्रकार
iwl_dbgfs_prph_reg_ग_लिखो(काष्ठा iwl_mvm *mvm, अक्षर *buf,
			 माप_प्रकार count, loff_t *ppos)
अणु
	u8 args;
	u32 value;

	args = माला_पूछो(buf, "%i %i", &mvm->dbgfs_prph_reg_addr, &value);
	/* अगर we only want to set the reg address - nothing more to करो */
	अगर (args == 1)
		जाओ out;

	/* otherwise, make sure we have both address and value */
	अगर (args != 2)
		वापस -EINVAL;

	iwl_ग_लिखो_prph(mvm->trans, mvm->dbgfs_prph_reg_addr, value);

out:
	वापस count;
पूर्ण

अटल sमाप_प्रकार
iwl_dbgfs_send_echo_cmd_ग_लिखो(काष्ठा iwl_mvm *mvm, अक्षर *buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक ret;

	अगर (!iwl_mvm_firmware_running(mvm))
		वापस -EIO;

	mutex_lock(&mvm->mutex);
	ret = iwl_mvm_send_cmd_pdu(mvm, ECHO_CMD, 0, 0, शून्य);
	mutex_unlock(&mvm->mutex);

	वापस ret ?: count;
पूर्ण

काष्ठा iwl_mvm_snअगरfer_apply अणु
	काष्ठा iwl_mvm *mvm;
	u8 *bssid;
	u16 aid;
पूर्ण;

अटल bool iwl_mvm_snअगरfer_apply(काष्ठा iwl_notअगर_रुको_data *notअगर_data,
				  काष्ठा iwl_rx_packet *pkt, व्योम *data)
अणु
	काष्ठा iwl_mvm_snअगरfer_apply *apply = data;

	apply->mvm->cur_aid = cpu_to_le16(apply->aid);
	स_नकल(apply->mvm->cur_bssid, apply->bssid,
	       माप(apply->mvm->cur_bssid));

	वापस true;
पूर्ण

अटल sमाप_प्रकार
iwl_dbgfs_he_snअगरfer_params_ग_लिखो(काष्ठा iwl_mvm *mvm, अक्षर *buf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_notअगरication_रुको रुको;
	काष्ठा iwl_he_monitor_cmd he_mon_cmd = अणुपूर्ण;
	काष्ठा iwl_mvm_snअगरfer_apply apply = अणु
		.mvm = mvm,
	पूर्ण;
	u16 रुको_cmds[] = अणु
		iwl_cmd_id(HE_AIR_SNIFFER_CONFIG_CMD, DATA_PATH_GROUP, 0),
	पूर्ण;
	u32 aid;
	पूर्णांक ret;

	अगर (!iwl_mvm_firmware_running(mvm))
		वापस -EIO;

	ret = माला_पूछो(buf, "%x %2hhx:%2hhx:%2hhx:%2hhx:%2hhx:%2hhx", &aid,
		     &he_mon_cmd.bssid[0], &he_mon_cmd.bssid[1],
		     &he_mon_cmd.bssid[2], &he_mon_cmd.bssid[3],
		     &he_mon_cmd.bssid[4], &he_mon_cmd.bssid[5]);
	अगर (ret != 7)
		वापस -EINVAL;

	he_mon_cmd.aid = cpu_to_le16(aid);

	apply.aid = aid;
	apply.bssid = (व्योम *)he_mon_cmd.bssid;

	mutex_lock(&mvm->mutex);

	/*
	 * Use the notअगरication रुकोer to get our function triggered
	 * in sequence with other RX. This ensures that frames we get
	 * on the RX queue _beक्रमe_ the new configuration is applied
	 * still have mvm->cur_aid poपूर्णांकing to the old AID, and that
	 * frames on the RX queue _after_ the firmware processed the
	 * new configuration (and sent the response, synchronously)
	 * get mvm->cur_aid correctly set to the new AID.
	 */
	iwl_init_notअगरication_रुको(&mvm->notअगर_रुको, &रुको,
				   रुको_cmds, ARRAY_SIZE(रुको_cmds),
				   iwl_mvm_snअगरfer_apply, &apply);

	ret = iwl_mvm_send_cmd_pdu(mvm, iwl_cmd_id(HE_AIR_SNIFFER_CONFIG_CMD,
						   DATA_PATH_GROUP, 0), 0,
				   माप(he_mon_cmd), &he_mon_cmd);

	/* no need to really रुको, we alपढ़ोy did anyway */
	iwl_हटाओ_notअगरication(&mvm->notअगर_रुको, &रुको);

	mutex_unlock(&mvm->mutex);

	वापस ret ?: count;
पूर्ण

अटल sमाप_प्रकार
iwl_dbgfs_he_snअगरfer_params_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_mvm *mvm = file->निजी_data;
	u8 buf[32];
	पूर्णांक len;

	len = scnम_लिखो(buf, माप(buf),
			"%d %02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx\n",
			le16_to_cpu(mvm->cur_aid), mvm->cur_bssid[0],
			mvm->cur_bssid[1], mvm->cur_bssid[2], mvm->cur_bssid[3],
			mvm->cur_bssid[4], mvm->cur_bssid[5]);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार
iwl_dbgfs_uapsd_noagg_bssids_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_mvm *mvm = file->निजी_data;
	u8 buf[IWL_MVM_UAPSD_NOAGG_BSSIDS_NUM * ETH_ALEN * 3 + 1];
	अचिन्हित पूर्णांक pos = 0;
	माप_प्रकार bufsz = माप(buf);
	पूर्णांक i;

	mutex_lock(&mvm->mutex);

	क्रम (i = 0; i < IWL_MVM_UAPSD_NOAGG_LIST_LEN; i++)
		pos += scnम_लिखो(buf + pos, bufsz - pos, "%pM\n",
				 mvm->uapsd_noagg_bssids[i].addr);

	mutex_unlock(&mvm->mutex);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

अटल sमाप_प्रकार
iwl_dbgfs_ltr_config_ग_लिखो(काष्ठा iwl_mvm *mvm,
			   अक्षर *buf, माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक ret;
	काष्ठा iwl_ltr_config_cmd ltr_config = अणु0पूर्ण;

	अगर (!iwl_mvm_firmware_running(mvm))
		वापस -EIO;

	अगर (माला_पूछो(buf, "%x,%x,%x,%x,%x,%x,%x",
		   &ltr_config.flags,
		   &ltr_config.अटल_दीर्घ,
		   &ltr_config.अटल_लघु,
		   &ltr_config.ltr_cfg_values[0],
		   &ltr_config.ltr_cfg_values[1],
		   &ltr_config.ltr_cfg_values[2],
		   &ltr_config.ltr_cfg_values[3]) != 7) अणु
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&mvm->mutex);
	ret = iwl_mvm_send_cmd_pdu(mvm, LTR_CONFIG, 0, माप(ltr_config),
				   &ltr_config);
	mutex_unlock(&mvm->mutex);

	अगर (ret)
		IWL_ERR(mvm, "failed to send ltr configuration cmd\n");

	वापस ret ?: count;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_rfi_freq_table_ग_लिखो(काष्ठा iwl_mvm *mvm, अक्षर *buf,
					      माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक ret = 0;
	u16 op_id;

	अगर (kstrtou16(buf, 10, &op_id))
		वापस -EINVAL;

	/* value zero triggers re-sending the शेष table to the device */
	अगर (!op_id) अणु
		mutex_lock(&mvm->mutex);
		ret = iwl_rfi_send_config_cmd(mvm, शून्य);
		mutex_unlock(&mvm->mutex);
	पूर्ण अन्यथा अणु
		ret = -EOPNOTSUPP; /* in the future a new table will be added */
	पूर्ण

	वापस ret ?: count;
पूर्ण

/* The size computation is as follows:
 * each number needs at most 3 अक्षरacters, number of rows is the size of
 * the table; So, need 5 अक्षरs क्रम the "freq: " part and each tuple afterwards
 * needs 6 अक्षरacters क्रम numbers and 5 क्रम the punctuation around.
 */
#घोषणा IWL_RFI_BUF_SIZE (IWL_RFI_LUT_INSTALLED_SIZE *\
				(5 + IWL_RFI_LUT_ENTRY_CHANNELS_NUM * (6 + 5)))

अटल sमाप_प्रकार iwl_dbgfs_rfi_freq_table_पढ़ो(काष्ठा file *file,
					     अक्षर __user *user_buf,
					     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_mvm *mvm = file->निजी_data;
	काष्ठा iwl_rfi_freq_table_resp_cmd *resp;
	u32 status;
	अक्षर buf[IWL_RFI_BUF_SIZE];
	पूर्णांक i, j, pos = 0;

	resp = iwl_rfi_get_freq_table(mvm);
	अगर (IS_ERR(resp))
		वापस PTR_ERR(resp);

	status = le32_to_cpu(resp->status);
	अगर (status != RFI_FREQ_TABLE_OK) अणु
		scnम_लिखो(buf, IWL_RFI_BUF_SIZE, "status = %d\n", status);
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(resp->table); i++) अणु
		pos += scnम_लिखो(buf + pos, IWL_RFI_BUF_SIZE - pos, "%d: ",
				 resp->table[i].freq);

		क्रम (j = 0; j < ARRAY_SIZE(resp->table[i].channels); j++)
			pos += scnम_लिखो(buf + pos, IWL_RFI_BUF_SIZE - pos,
					 "(%d, %d) ",
					 resp->table[i].channels[j],
					 resp->table[i].bands[j]);
		pos += scnम_लिखो(buf + pos, IWL_RFI_BUF_SIZE - pos, "\n");
	पूर्ण

out:
	kमुक्त(resp);
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

MVM_DEBUGFS_READ_WRITE_खाता_OPS(prph_reg, 64);

/* Device wide debugfs entries */
MVM_DEBUGFS_READ_खाता_OPS(ctdp_budget);
MVM_DEBUGFS_WRITE_खाता_OPS(stop_ctdp, 8);
MVM_DEBUGFS_WRITE_खाता_OPS(क्रमce_ctसमाप्त, 8);
MVM_DEBUGFS_WRITE_खाता_OPS(tx_flush, 16);
MVM_DEBUGFS_WRITE_खाता_OPS(sta_drain, 8);
MVM_DEBUGFS_WRITE_खाता_OPS(send_echo_cmd, 8);
MVM_DEBUGFS_READ_WRITE_खाता_OPS(sram, 64);
MVM_DEBUGFS_READ_WRITE_खाता_OPS(set_nic_temperature, 64);
MVM_DEBUGFS_READ_खाता_OPS(nic_temp);
MVM_DEBUGFS_READ_खाता_OPS(stations);
MVM_DEBUGFS_READ_खाता_OPS(rs_data);
MVM_DEBUGFS_READ_खाता_OPS(bt_notअगर);
MVM_DEBUGFS_READ_खाता_OPS(bt_cmd);
MVM_DEBUGFS_READ_WRITE_खाता_OPS(disable_घातer_off, 64);
MVM_DEBUGFS_READ_खाता_OPS(fw_rx_stats);
MVM_DEBUGFS_READ_खाता_OPS(drv_rx_stats);
MVM_DEBUGFS_READ_खाता_OPS(fw_ver);
MVM_DEBUGFS_READ_खाता_OPS(phy_पूर्णांकegration_ver);
MVM_DEBUGFS_WRITE_खाता_OPS(fw_restart, 10);
MVM_DEBUGFS_WRITE_खाता_OPS(fw_nmi, 10);
MVM_DEBUGFS_WRITE_खाता_OPS(bt_tx_prio, 10);
MVM_DEBUGFS_WRITE_खाता_OPS(bt_क्रमce_ant, 10);
MVM_DEBUGFS_READ_WRITE_खाता_OPS(scan_ant_rxchain, 8);
MVM_DEBUGFS_READ_WRITE_खाता_OPS(fw_dbg_conf, 8);
MVM_DEBUGFS_WRITE_खाता_OPS(fw_dbg_collect, 64);
MVM_DEBUGFS_WRITE_खाता_OPS(dbg_समय_poपूर्णांक, 64);
MVM_DEBUGFS_WRITE_खाता_OPS(indirection_tbl,
			   (IWL_RSS_INसूचीECTION_TABLE_SIZE * 2));
MVM_DEBUGFS_WRITE_खाता_OPS(inject_packet, 512);
MVM_DEBUGFS_WRITE_खाता_OPS(inject_beacon_ie, 512);
MVM_DEBUGFS_WRITE_खाता_OPS(inject_beacon_ie_restore, 512);

MVM_DEBUGFS_READ_खाता_OPS(uapsd_noagg_bssids);

#अगर_घोषित CONFIG_IWLWIFI_BCAST_FILTERING
MVM_DEBUGFS_READ_WRITE_खाता_OPS(bcast_filters, 256);
MVM_DEBUGFS_READ_WRITE_खाता_OPS(bcast_filters_macs, 256);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
MVM_DEBUGFS_READ_खाता_OPS(sar_geo_profile);
#पूर्ण_अगर

MVM_DEBUGFS_READ_WRITE_STA_खाता_OPS(amsdu_len, 16);

MVM_DEBUGFS_READ_WRITE_खाता_OPS(he_snअगरfer_params, 32);

MVM_DEBUGFS_WRITE_खाता_OPS(ltr_config, 512);
MVM_DEBUGFS_READ_WRITE_खाता_OPS(rfi_freq_table, 16);

अटल sमाप_प्रकार iwl_dbgfs_mem_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_mvm *mvm = file->निजी_data;
	काष्ठा iwl_dbg_mem_access_cmd cmd = अणुपूर्ण;
	काष्ठा iwl_dbg_mem_access_rsp *rsp;
	काष्ठा iwl_host_cmd hcmd = अणु
		.flags = CMD_WANT_SKB | CMD_SEND_IN_RFKILL,
		.data = अणु &cmd, पूर्ण,
		.len = अणु माप(cmd) पूर्ण,
	पूर्ण;
	माप_प्रकार delta;
	sमाप_प्रकार ret, len;

	अगर (!iwl_mvm_firmware_running(mvm))
		वापस -EIO;

	hcmd.id = iwl_cmd_id(*ppos >> 24 ? UMAC_RD_WR : LMAC_RD_WR,
			     DEBUG_GROUP, 0);
	cmd.op = cpu_to_le32(DEBUG_MEM_OP_READ);

	/* Take care of alignment of both the position and the length */
	delta = *ppos & 0x3;
	cmd.addr = cpu_to_le32(*ppos - delta);
	cmd.len = cpu_to_le32(min(ALIGN(count + delta, 4) / 4,
				  (माप_प्रकार)DEBUG_MEM_MAX_SIZE_DWORDS));

	mutex_lock(&mvm->mutex);
	ret = iwl_mvm_send_cmd(mvm, &hcmd);
	mutex_unlock(&mvm->mutex);

	अगर (ret < 0)
		वापस ret;

	rsp = (व्योम *)hcmd.resp_pkt->data;
	अगर (le32_to_cpu(rsp->status) != DEBUG_MEM_STATUS_SUCCESS) अणु
		ret = -ENXIO;
		जाओ out;
	पूर्ण

	len = min((माप_प्रकार)le32_to_cpu(rsp->len) << 2,
		  iwl_rx_packet_payload_len(hcmd.resp_pkt) - माप(*rsp));
	len = min(len - delta, count);
	अगर (len < 0) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	ret = len - copy_to_user(user_buf, (व्योम *)rsp->data + delta, len);
	*ppos += ret;

out:
	iwl_मुक्त_resp(&hcmd);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_mem_ग_लिखो(काष्ठा file *file,
				   स्थिर अक्षर __user *user_buf, माप_प्रकार count,
				   loff_t *ppos)
अणु
	काष्ठा iwl_mvm *mvm = file->निजी_data;
	काष्ठा iwl_dbg_mem_access_cmd *cmd;
	काष्ठा iwl_dbg_mem_access_rsp *rsp;
	काष्ठा iwl_host_cmd hcmd = अणुपूर्ण;
	माप_प्रकार cmd_size;
	माप_प्रकार data_size;
	u32 op, len;
	sमाप_प्रकार ret;

	अगर (!iwl_mvm_firmware_running(mvm))
		वापस -EIO;

	hcmd.id = iwl_cmd_id(*ppos >> 24 ? UMAC_RD_WR : LMAC_RD_WR,
			     DEBUG_GROUP, 0);

	अगर (*ppos & 0x3 || count < 4) अणु
		op = DEBUG_MEM_OP_WRITE_BYTES;
		len = min(count, (माप_प्रकार)(4 - (*ppos & 0x3)));
		data_size = len;
	पूर्ण अन्यथा अणु
		op = DEBUG_MEM_OP_WRITE;
		len = min(count >> 2, (माप_प्रकार)DEBUG_MEM_MAX_SIZE_DWORDS);
		data_size = len << 2;
	पूर्ण

	cmd_size = माप(*cmd) + ALIGN(data_size, 4);
	cmd = kzalloc(cmd_size, GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->op = cpu_to_le32(op);
	cmd->len = cpu_to_le32(len);
	cmd->addr = cpu_to_le32(*ppos);
	अगर (copy_from_user((व्योम *)cmd->data, user_buf, data_size)) अणु
		kमुक्त(cmd);
		वापस -EFAULT;
	पूर्ण

	hcmd.flags = CMD_WANT_SKB | CMD_SEND_IN_RFKILL,
	hcmd.data[0] = (व्योम *)cmd;
	hcmd.len[0] = cmd_size;

	mutex_lock(&mvm->mutex);
	ret = iwl_mvm_send_cmd(mvm, &hcmd);
	mutex_unlock(&mvm->mutex);

	kमुक्त(cmd);

	अगर (ret < 0)
		वापस ret;

	rsp = (व्योम *)hcmd.resp_pkt->data;
	अगर (rsp->status != DEBUG_MEM_STATUS_SUCCESS) अणु
		ret = -ENXIO;
		जाओ out;
	पूर्ण

	ret = data_size;
	*ppos += ret;

out:
	iwl_मुक्त_resp(&hcmd);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations iwl_dbgfs_mem_ops = अणु
	.पढ़ो = iwl_dbgfs_mem_पढ़ो,
	.ग_लिखो = iwl_dbgfs_mem_ग_लिखो,
	.खोलो = simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;

व्योम iwl_mvm_sta_add_debugfs(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_vअगर *vअगर,
			     काष्ठा ieee80211_sta *sta,
			     काष्ठा dentry *dir)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);

	अगर (iwl_mvm_has_tlc_offload(mvm)) अणु
		MVM_DEBUGFS_ADD_STA_खाता(rs_data, dir, 0400);
	पूर्ण
	MVM_DEBUGFS_ADD_STA_खाता(amsdu_len, dir, 0600);
पूर्ण

व्योम iwl_mvm_dbgfs_रेजिस्टर(काष्ठा iwl_mvm *mvm)
अणु
	काष्ठा dentry *bcast_dir __maybe_unused;
	अक्षर buf[100];

	spin_lock_init(&mvm->drv_stats_lock);

	MVM_DEBUGFS_ADD_खाता(tx_flush, mvm->debugfs_dir, 0200);
	MVM_DEBUGFS_ADD_खाता(sta_drain, mvm->debugfs_dir, 0200);
	MVM_DEBUGFS_ADD_खाता(sram, mvm->debugfs_dir, 0600);
	MVM_DEBUGFS_ADD_खाता(set_nic_temperature, mvm->debugfs_dir, 0600);
	MVM_DEBUGFS_ADD_खाता(nic_temp, mvm->debugfs_dir, 0400);
	MVM_DEBUGFS_ADD_खाता(ctdp_budget, mvm->debugfs_dir, 0400);
	MVM_DEBUGFS_ADD_खाता(stop_ctdp, mvm->debugfs_dir, 0200);
	MVM_DEBUGFS_ADD_खाता(क्रमce_ctसमाप्त, mvm->debugfs_dir, 0200);
	MVM_DEBUGFS_ADD_खाता(stations, mvm->debugfs_dir, 0400);
	MVM_DEBUGFS_ADD_खाता(bt_notअगर, mvm->debugfs_dir, 0400);
	MVM_DEBUGFS_ADD_खाता(bt_cmd, mvm->debugfs_dir, 0400);
	MVM_DEBUGFS_ADD_खाता(disable_घातer_off, mvm->debugfs_dir, 0600);
	MVM_DEBUGFS_ADD_खाता(fw_ver, mvm->debugfs_dir, 0400);
	MVM_DEBUGFS_ADD_खाता(fw_rx_stats, mvm->debugfs_dir, 0400);
	MVM_DEBUGFS_ADD_खाता(drv_rx_stats, mvm->debugfs_dir, 0400);
	MVM_DEBUGFS_ADD_खाता(fw_restart, mvm->debugfs_dir, 0200);
	MVM_DEBUGFS_ADD_खाता(fw_nmi, mvm->debugfs_dir, 0200);
	MVM_DEBUGFS_ADD_खाता(bt_tx_prio, mvm->debugfs_dir, 0200);
	MVM_DEBUGFS_ADD_खाता(bt_क्रमce_ant, mvm->debugfs_dir, 0200);
	MVM_DEBUGFS_ADD_खाता(scan_ant_rxchain, mvm->debugfs_dir, 0600);
	MVM_DEBUGFS_ADD_खाता(prph_reg, mvm->debugfs_dir, 0600);
	MVM_DEBUGFS_ADD_खाता(fw_dbg_conf, mvm->debugfs_dir, 0600);
	MVM_DEBUGFS_ADD_खाता(fw_dbg_collect, mvm->debugfs_dir, 0200);
	MVM_DEBUGFS_ADD_खाता(send_echo_cmd, mvm->debugfs_dir, 0200);
	MVM_DEBUGFS_ADD_खाता(indirection_tbl, mvm->debugfs_dir, 0200);
	MVM_DEBUGFS_ADD_खाता(inject_packet, mvm->debugfs_dir, 0200);
	MVM_DEBUGFS_ADD_खाता(inject_beacon_ie, mvm->debugfs_dir, 0200);
	MVM_DEBUGFS_ADD_खाता(inject_beacon_ie_restore, mvm->debugfs_dir, 0200);
	MVM_DEBUGFS_ADD_खाता(rfi_freq_table, mvm->debugfs_dir, 0600);

	अगर (mvm->fw->phy_पूर्णांकegration_ver)
		MVM_DEBUGFS_ADD_खाता(phy_पूर्णांकegration_ver, mvm->debugfs_dir, 0400);
#अगर_घोषित CONFIG_ACPI
	MVM_DEBUGFS_ADD_खाता(sar_geo_profile, mvm->debugfs_dir, 0400);
#पूर्ण_अगर
	MVM_DEBUGFS_ADD_खाता(he_snअगरfer_params, mvm->debugfs_dir, 0600);

	अगर (fw_has_capa(&mvm->fw->ucode_capa, IWL_UCODE_TLV_CAPA_SET_LTR_GEN2))
		MVM_DEBUGFS_ADD_खाता(ltr_config, mvm->debugfs_dir, 0200);

	debugfs_create_bool("enable_scan_iteration_notif", 0600,
			    mvm->debugfs_dir, &mvm->scan_iter_notअगर_enabled);
	debugfs_create_bool("drop_bcn_ap_mode", 0600, mvm->debugfs_dir,
			    &mvm->drop_bcn_ap_mode);

	MVM_DEBUGFS_ADD_खाता(uapsd_noagg_bssids, mvm->debugfs_dir, S_IRUSR);

#अगर_घोषित CONFIG_IWLWIFI_BCAST_FILTERING
	अगर (mvm->fw->ucode_capa.flags & IWL_UCODE_TLV_FLAGS_BCAST_FILTERING) अणु
		bcast_dir = debugfs_create_dir("bcast_filtering",
					       mvm->debugfs_dir);

		debugfs_create_bool("override", 0600, bcast_dir,
				    &mvm->dbgfs_bcast_filtering.override);

		MVM_DEBUGFS_ADD_खाता_ALIAS("filters", bcast_filters,
					   bcast_dir, 0600);
		MVM_DEBUGFS_ADD_खाता_ALIAS("macs", bcast_filters_macs,
					   bcast_dir, 0600);
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_SLEEP
	MVM_DEBUGFS_ADD_खाता(d3_test, mvm->debugfs_dir, 0400);
	debugfs_create_bool("d3_wake_sysassert", 0600, mvm->debugfs_dir,
			    &mvm->d3_wake_sysनिश्चित);
	debugfs_create_u32("last_netdetect_scans", 0400, mvm->debugfs_dir,
			   &mvm->last_netdetect_scans);
#पूर्ण_अगर

	debugfs_create_u8("ps_disabled", 0400, mvm->debugfs_dir,
			  &mvm->ps_disabled);
	debugfs_create_blob("nvm_hw", 0400, mvm->debugfs_dir,
			    &mvm->nvm_hw_blob);
	debugfs_create_blob("nvm_sw", 0400, mvm->debugfs_dir,
			    &mvm->nvm_sw_blob);
	debugfs_create_blob("nvm_calib", 0400, mvm->debugfs_dir,
			    &mvm->nvm_calib_blob);
	debugfs_create_blob("nvm_prod", 0400, mvm->debugfs_dir,
			    &mvm->nvm_prod_blob);
	debugfs_create_blob("nvm_phy_sku", 0400, mvm->debugfs_dir,
			    &mvm->nvm_phy_sku_blob);
	debugfs_create_blob("nvm_reg", S_IRUSR,
			    mvm->debugfs_dir, &mvm->nvm_reg_blob);

	debugfs_create_file("mem", 0600, mvm->debugfs_dir, mvm,
			    &iwl_dbgfs_mem_ops);

	/*
	 * Create a symlink with mac80211. It will be हटाओd when mac80211
	 * exists (beक्रमe the opmode exists which हटाओs the target.)
	 */
	snम_लिखो(buf, 100, "../../%pd2", mvm->debugfs_dir->d_parent);
	debugfs_create_symlink("iwlwifi", mvm->hw->wiphy->debugfsdir, buf);
पूर्ण
