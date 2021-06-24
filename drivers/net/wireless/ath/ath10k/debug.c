<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2005-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2017 Qualcomm Atheros, Inc.
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/crc32.h>
#समावेश <linux/firmware.h>

#समावेश "core.h"
#समावेश "debug.h"
#समावेश "hif.h"
#समावेश "wmi-ops.h"

/* ms */
#घोषणा ATH10K_DEBUG_HTT_STATS_INTERVAL 1000

#घोषणा ATH10K_DEBUG_CAL_DATA_LEN 12064

व्योम ath10k_info(काष्ठा ath10k *ar, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf = अणु
		.fmt = fmt,
	पूर्ण;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.va = &args;
	dev_info(ar->dev, "%pV", &vaf);
	trace_ath10k_log_info(ar, &vaf);
	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(ath10k_info);

व्योम ath10k_debug_prपूर्णांक_hwfw_info(काष्ठा ath10k *ar)
अणु
	स्थिर काष्ठा firmware *firmware;
	अक्षर fw_features[128] = अणुपूर्ण;
	u32 crc = 0;

	ath10k_core_get_fw_features_str(ar, fw_features, माप(fw_features));

	ath10k_info(ar, "%s target 0x%08x chip_id 0x%08x sub %04x:%04x",
		    ar->hw_params.name,
		    ar->target_version,
		    ar->bus_param.chip_id,
		    ar->id.subप्रणाली_venकरोr, ar->id.subप्रणाली_device);

	ath10k_info(ar, "kconfig debug %d debugfs %d tracing %d dfs %d testmode %d\n",
		    IS_ENABLED(CONFIG_ATH10K_DEBUG),
		    IS_ENABLED(CONFIG_ATH10K_DEBUGFS),
		    IS_ENABLED(CONFIG_ATH10K_TRACING),
		    IS_ENABLED(CONFIG_ATH10K_DFS_CERTIFIED),
		    IS_ENABLED(CONFIG_NL80211_TESTMODE));

	firmware = ar->normal_mode_fw.fw_file.firmware;
	अगर (firmware)
		crc = crc32_le(0, firmware->data, firmware->size);

	ath10k_info(ar, "firmware ver %s api %d features %s crc32 %08x\n",
		    ar->hw->wiphy->fw_version,
		    ar->fw_api,
		    fw_features,
		    crc);
पूर्ण

व्योम ath10k_debug_prपूर्णांक_board_info(काष्ठा ath10k *ar)
अणु
	अक्षर boardinfo[100];
	स्थिर काष्ठा firmware *board;
	u32 crc;

	अगर (ar->id.bmi_ids_valid)
		scnम_लिखो(boardinfo, माप(boardinfo), "%d:%d",
			  ar->id.bmi_chip_id, ar->id.bmi_board_id);
	अन्यथा
		scnम_लिखो(boardinfo, माप(boardinfo), "N/A");

	board = ar->normal_mode_fw.board;
	अगर (!IS_ERR_OR_शून्य(board))
		crc = crc32_le(0, board->data, board->size);
	अन्यथा
		crc = 0;

	ath10k_info(ar, "board_file api %d bmi_id %s crc32 %08x",
		    ar->bd_api,
		    boardinfo,
		    crc);
पूर्ण

व्योम ath10k_debug_prपूर्णांक_boot_info(काष्ठा ath10k *ar)
अणु
	ath10k_info(ar, "htt-ver %d.%d wmi-op %d htt-op %d cal %s max-sta %d raw %d hwcrypto %d\n",
		    ar->htt.target_version_major,
		    ar->htt.target_version_minor,
		    ar->normal_mode_fw.fw_file.wmi_op_version,
		    ar->normal_mode_fw.fw_file.htt_op_version,
		    ath10k_cal_mode_str(ar->cal_mode),
		    ar->max_num_stations,
		    test_bit(ATH10K_FLAG_RAW_MODE, &ar->dev_flags),
		    !test_bit(ATH10K_FLAG_HW_CRYPTO_DISABLED, &ar->dev_flags));
पूर्ण

व्योम ath10k_prपूर्णांक_driver_info(काष्ठा ath10k *ar)
अणु
	ath10k_debug_prपूर्णांक_hwfw_info(ar);
	ath10k_debug_prपूर्णांक_board_info(ar);
	ath10k_debug_prपूर्णांक_boot_info(ar);
पूर्ण
EXPORT_SYMBOL(ath10k_prपूर्णांक_driver_info);

व्योम ath10k_err(काष्ठा ath10k *ar, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf = अणु
		.fmt = fmt,
	पूर्ण;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.va = &args;
	dev_err(ar->dev, "%pV", &vaf);
	trace_ath10k_log_err(ar, &vaf);
	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(ath10k_err);

व्योम ath10k_warn(काष्ठा ath10k *ar, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf = अणु
		.fmt = fmt,
	पूर्ण;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.va = &args;
	dev_warn_ratelimited(ar->dev, "%pV", &vaf);
	trace_ath10k_log_warn(ar, &vaf);

	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(ath10k_warn);

#अगर_घोषित CONFIG_ATH10K_DEBUGFS

अटल sमाप_प्रकार ath10k_पढ़ो_wmi_services(काष्ठा file *file,
					अक्षर __user *user_buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	अक्षर *buf;
	माप_प्रकार len = 0, buf_len = 8192;
	स्थिर अक्षर *name;
	sमाप_प्रकार ret_cnt;
	bool enabled;
	पूर्णांक i;

	buf = kzalloc(buf_len, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	mutex_lock(&ar->conf_mutex);

	spin_lock_bh(&ar->data_lock);
	क्रम (i = 0; i < WMI_SERVICE_MAX; i++) अणु
		enabled = test_bit(i, ar->wmi.svc_map);
		name = wmi_service_name(i);

		अगर (!name) अणु
			अगर (enabled)
				len += scnम_लिखो(buf + len, buf_len - len,
						 "%-40s %s (bit %d)\n",
						 "unknown", "enabled", i);

			जारी;
		पूर्ण

		len += scnम_लिखो(buf + len, buf_len - len,
				 "%-40s %s\n",
				 name, enabled ? "enabled" : "-");
	पूर्ण
	spin_unlock_bh(&ar->data_lock);

	ret_cnt = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);

	mutex_unlock(&ar->conf_mutex);

	kमुक्त(buf);
	वापस ret_cnt;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_wmi_services = अणु
	.पढ़ो = ath10k_पढ़ो_wmi_services,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल व्योम ath10k_fw_stats_pdevs_मुक्त(काष्ठा list_head *head)
अणु
	काष्ठा ath10k_fw_stats_pdev *i, *पंचांगp;

	list_क्रम_each_entry_safe(i, पंचांगp, head, list) अणु
		list_del(&i->list);
		kमुक्त(i);
	पूर्ण
पूर्ण

अटल व्योम ath10k_fw_stats_vdevs_मुक्त(काष्ठा list_head *head)
अणु
	काष्ठा ath10k_fw_stats_vdev *i, *पंचांगp;

	list_क्रम_each_entry_safe(i, पंचांगp, head, list) अणु
		list_del(&i->list);
		kमुक्त(i);
	पूर्ण
पूर्ण

अटल व्योम ath10k_fw_stats_peers_मुक्त(काष्ठा list_head *head)
अणु
	काष्ठा ath10k_fw_stats_peer *i, *पंचांगp;

	list_क्रम_each_entry_safe(i, पंचांगp, head, list) अणु
		list_del(&i->list);
		kमुक्त(i);
	पूर्ण
पूर्ण

अटल व्योम ath10k_fw_extd_stats_peers_मुक्त(काष्ठा list_head *head)
अणु
	काष्ठा ath10k_fw_extd_stats_peer *i, *पंचांगp;

	list_क्रम_each_entry_safe(i, पंचांगp, head, list) अणु
		list_del(&i->list);
		kमुक्त(i);
	पूर्ण
पूर्ण

अटल व्योम ath10k_debug_fw_stats_reset(काष्ठा ath10k *ar)
अणु
	spin_lock_bh(&ar->data_lock);
	ar->debug.fw_stats_करोne = false;
	ar->debug.fw_stats.extended = false;
	ath10k_fw_stats_pdevs_मुक्त(&ar->debug.fw_stats.pdevs);
	ath10k_fw_stats_vdevs_मुक्त(&ar->debug.fw_stats.vdevs);
	ath10k_fw_stats_peers_मुक्त(&ar->debug.fw_stats.peers);
	ath10k_fw_extd_stats_peers_मुक्त(&ar->debug.fw_stats.peers_extd);
	spin_unlock_bh(&ar->data_lock);
पूर्ण

व्योम ath10k_debug_fw_stats_process(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा ath10k_fw_stats stats = अणुपूर्ण;
	bool is_start, is_started, is_end;
	माप_प्रकार num_peers;
	माप_प्रकार num_vdevs;
	पूर्णांक ret;

	INIT_LIST_HEAD(&stats.pdevs);
	INIT_LIST_HEAD(&stats.vdevs);
	INIT_LIST_HEAD(&stats.peers);
	INIT_LIST_HEAD(&stats.peers_extd);

	spin_lock_bh(&ar->data_lock);
	ret = ath10k_wmi_pull_fw_stats(ar, skb, &stats);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to pull fw stats: %d\n", ret);
		जाओ मुक्त;
	पूर्ण

	/* Stat data may exceed htc-wmi buffer limit. In such हाल firmware
	 * splits the stats data and delivers it in a ping-pong fashion of
	 * request cmd-update event.
	 *
	 * However there is no explicit end-of-data. Instead start-of-data is
	 * used as an implicit one. This works as follows:
	 *  a) discard stat update events until one with pdev stats is
	 *     delivered - this skips session started at end of (b)
	 *  b) consume stat update events until another one with pdev stats is
	 *     delivered which is treated as end-of-data and is itself discarded
	 */
	अगर (ath10k_peer_stats_enabled(ar))
		ath10k_sta_update_rx_duration(ar, &stats);

	अगर (ar->debug.fw_stats_करोne) अणु
		अगर (!ath10k_peer_stats_enabled(ar))
			ath10k_warn(ar, "received unsolicited stats update event\n");

		जाओ मुक्त;
	पूर्ण

	num_peers = ath10k_wmi_fw_stats_num_peers(&ar->debug.fw_stats.peers);
	num_vdevs = ath10k_wmi_fw_stats_num_vdevs(&ar->debug.fw_stats.vdevs);
	is_start = (list_empty(&ar->debug.fw_stats.pdevs) &&
		    !list_empty(&stats.pdevs));
	is_end = (!list_empty(&ar->debug.fw_stats.pdevs) &&
		  !list_empty(&stats.pdevs));

	अगर (is_start)
		list_splice_tail_init(&stats.pdevs, &ar->debug.fw_stats.pdevs);

	अगर (is_end)
		ar->debug.fw_stats_करोne = true;

	अगर (stats.extended)
		ar->debug.fw_stats.extended = true;

	is_started = !list_empty(&ar->debug.fw_stats.pdevs);

	अगर (is_started && !is_end) अणु
		अगर (num_peers >= ATH10K_MAX_NUM_PEER_IDS) अणु
			/* Although this is unlikely impose a sane limit to
			 * prevent firmware from DoS-ing the host.
			 */
			ath10k_fw_stats_peers_मुक्त(&ar->debug.fw_stats.peers);
			ath10k_fw_extd_stats_peers_मुक्त(&ar->debug.fw_stats.peers_extd);
			ath10k_warn(ar, "dropping fw peer stats\n");
			जाओ मुक्त;
		पूर्ण

		अगर (num_vdevs >= BITS_PER_LONG) अणु
			ath10k_fw_stats_vdevs_मुक्त(&ar->debug.fw_stats.vdevs);
			ath10k_warn(ar, "dropping fw vdev stats\n");
			जाओ मुक्त;
		पूर्ण

		अगर (!list_empty(&stats.peers))
			list_splice_tail_init(&stats.peers_extd,
					      &ar->debug.fw_stats.peers_extd);

		list_splice_tail_init(&stats.peers, &ar->debug.fw_stats.peers);
		list_splice_tail_init(&stats.vdevs, &ar->debug.fw_stats.vdevs);
	पूर्ण

	complete(&ar->debug.fw_stats_complete);

मुक्त:
	/* In some हालs lists have been spliced and cleared. Free up
	 * resources अगर that is not the हाल.
	 */
	ath10k_fw_stats_pdevs_मुक्त(&stats.pdevs);
	ath10k_fw_stats_vdevs_मुक्त(&stats.vdevs);
	ath10k_fw_stats_peers_मुक्त(&stats.peers);
	ath10k_fw_extd_stats_peers_मुक्त(&stats.peers_extd);

	spin_unlock_bh(&ar->data_lock);
पूर्ण

पूर्णांक ath10k_debug_fw_stats_request(काष्ठा ath10k *ar)
अणु
	अचिन्हित दीर्घ समयout, समय_left;
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	समयout = jअगरfies + msecs_to_jअगरfies(1 * HZ);

	ath10k_debug_fw_stats_reset(ar);

	क्रम (;;) अणु
		अगर (समय_after(jअगरfies, समयout))
			वापस -ETIMEDOUT;

		reinit_completion(&ar->debug.fw_stats_complete);

		ret = ath10k_wmi_request_stats(ar, ar->fw_stats_req_mask);
		अगर (ret) अणु
			ath10k_warn(ar, "could not request stats (%d)\n", ret);
			वापस ret;
		पूर्ण

		समय_left =
		रुको_क्रम_completion_समयout(&ar->debug.fw_stats_complete,
					    1 * HZ);
		अगर (!समय_left)
			वापस -ETIMEDOUT;

		spin_lock_bh(&ar->data_lock);
		अगर (ar->debug.fw_stats_करोne) अणु
			spin_unlock_bh(&ar->data_lock);
			अवरोध;
		पूर्ण
		spin_unlock_bh(&ar->data_lock);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_fw_stats_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ath10k *ar = inode->i_निजी;
	व्योम *buf = शून्य;
	पूर्णांक ret;

	mutex_lock(&ar->conf_mutex);

	अगर (ar->state != ATH10K_STATE_ON) अणु
		ret = -ENETDOWN;
		जाओ err_unlock;
	पूर्ण

	buf = vदो_स्मृति(ATH10K_FW_STATS_BUF_SIZE);
	अगर (!buf) अणु
		ret = -ENOMEM;
		जाओ err_unlock;
	पूर्ण

	ret = ath10k_debug_fw_stats_request(ar);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to request fw stats: %d\n", ret);
		जाओ err_मुक्त;
	पूर्ण

	ret = ath10k_wmi_fw_stats_fill(ar, &ar->debug.fw_stats, buf);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to fill fw stats: %d\n", ret);
		जाओ err_मुक्त;
	पूर्ण

	file->निजी_data = buf;

	mutex_unlock(&ar->conf_mutex);
	वापस 0;

err_मुक्त:
	vमुक्त(buf);

err_unlock:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_fw_stats_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	vमुक्त(file->निजी_data);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार ath10k_fw_stats_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
				    माप_प्रकार count, loff_t *ppos)
अणु
	स्थिर अक्षर *buf = file->निजी_data;
	माप_प्रकार len = म_माप(buf);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations fops_fw_stats = अणु
	.खोलो = ath10k_fw_stats_खोलो,
	.release = ath10k_fw_stats_release,
	.पढ़ो = ath10k_fw_stats_पढ़ो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath10k_debug_fw_reset_stats_पढ़ो(काष्ठा file *file,
						अक्षर __user *user_buf,
						माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	पूर्णांक ret;
	माप_प्रकार len = 0, buf_len = 500;
	अक्षर *buf;

	buf = kदो_स्मृति(buf_len, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	spin_lock_bh(&ar->data_lock);

	len += scnम_लिखो(buf + len, buf_len - len,
			 "fw_crash_counter\t\t%d\n", ar->stats.fw_crash_counter);
	len += scnम_लिखो(buf + len, buf_len - len,
			 "fw_warm_reset_counter\t\t%d\n",
			 ar->stats.fw_warm_reset_counter);
	len += scnम_लिखो(buf + len, buf_len - len,
			 "fw_cold_reset_counter\t\t%d\n",
			 ar->stats.fw_cold_reset_counter);

	spin_unlock_bh(&ar->data_lock);

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);

	kमुक्त(buf);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_fw_reset_stats = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = ath10k_debug_fw_reset_stats_पढ़ो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

/* This is a clean निश्चित crash in firmware. */
अटल पूर्णांक ath10k_debug_fw_निश्चित(काष्ठा ath10k *ar)
अणु
	काष्ठा wmi_vdev_install_key_cmd *cmd;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*cmd) + 16);
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_vdev_install_key_cmd *)skb->data;
	स_रखो(cmd, 0, माप(*cmd));

	/* big enough number so that firmware निश्चितs */
	cmd->vdev_id = __cpu_to_le32(0x7ffe);

	वापस ath10k_wmi_cmd_send(ar, skb,
				   ar->wmi.cmd->vdev_install_key_cmdid);
पूर्ण

अटल sमाप_प्रकार ath10k_पढ़ो_simulate_fw_crash(काष्ठा file *file,
					     अक्षर __user *user_buf,
					     माप_प्रकार count, loff_t *ppos)
अणु
	स्थिर अक्षर buf[] =
		"To simulate firmware crash write one of the keywords to this file:\n"
		"`soft` - this will send WMI_FORCE_FW_HANG_ASSERT to firmware if FW supports that command.\n"
		"`hard` - this will send to firmware command with illegal parameters causing firmware crash.\n"
		"`assert` - this will send special illegal parameter to firmware to cause assert failure and crash.\n"
		"`hw-restart` - this will simply queue hw restart without fw/hw actually crashing.\n";

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, म_माप(buf));
पूर्ण

/* Simulate firmware crash:
 * 'soft': Call wmi command causing firmware hang. This firmware hang is
 * recoverable by warm firmware reset.
 * 'hard': Force firmware crash by setting any vdev parameter क्रम not allowed
 * vdev id. This is hard firmware crash because it is recoverable only by cold
 * firmware reset.
 */
अटल sमाप_प्रकार ath10k_ग_लिखो_simulate_fw_crash(काष्ठा file *file,
					      स्थिर अक्षर __user *user_buf,
					      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	अक्षर buf[32] = अणु0पूर्ण;
	sमाप_प्रकार rc;
	पूर्णांक ret;

	/* filter partial ग_लिखोs and invalid commands */
	अगर (*ppos != 0 || count >= माप(buf) || count == 0)
		वापस -EINVAL;

	rc = simple_ग_लिखो_to_buffer(buf, माप(buf) - 1, ppos, user_buf, count);
	अगर (rc < 0)
		वापस rc;

	/* drop the possible '\n' from the end */
	अगर (buf[*ppos - 1] == '\n')
		buf[*ppos - 1] = '\0';

	mutex_lock(&ar->conf_mutex);

	अगर (ar->state != ATH10K_STATE_ON &&
	    ar->state != ATH10K_STATE_RESTARTED) अणु
		ret = -ENETDOWN;
		जाओ निकास;
	पूर्ण

	अगर (!म_भेद(buf, "soft")) अणु
		ath10k_info(ar, "simulating soft firmware crash\n");
		ret = ath10k_wmi_क्रमce_fw_hang(ar, WMI_FORCE_FW_HANG_ASSERT, 0);
	पूर्ण अन्यथा अगर (!म_भेद(buf, "hard")) अणु
		ath10k_info(ar, "simulating hard firmware crash\n");
		/* 0x7fff is vdev id, and it is always out of range क्रम all
		 * firmware variants in order to क्रमce a firmware crash.
		 */
		ret = ath10k_wmi_vdev_set_param(ar, 0x7fff,
						ar->wmi.vdev_param->rts_threshold,
						0);
	पूर्ण अन्यथा अगर (!म_भेद(buf, "assert")) अणु
		ath10k_info(ar, "simulating firmware assert crash\n");
		ret = ath10k_debug_fw_निश्चित(ar);
	पूर्ण अन्यथा अगर (!म_भेद(buf, "hw-restart")) अणु
		ath10k_info(ar, "user requested hw restart\n");
		ath10k_core_start_recovery(ar);
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	अगर (ret) अणु
		ath10k_warn(ar, "failed to simulate firmware crash: %d\n", ret);
		जाओ निकास;
	पूर्ण

	ret = count;

निकास:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_simulate_fw_crash = अणु
	.पढ़ो = ath10k_पढ़ो_simulate_fw_crash,
	.ग_लिखो = ath10k_ग_लिखो_simulate_fw_crash,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath10k_पढ़ो_chip_id(काष्ठा file *file, अक्षर __user *user_buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	माप_प्रकार len;
	अक्षर buf[50];

	len = scnम_लिखो(buf, माप(buf), "0x%08x\n", ar->bus_param.chip_id);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations fops_chip_id = अणु
	.पढ़ो = ath10k_पढ़ो_chip_id,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath10k_reg_addr_पढ़ो(काष्ठा file *file,
				    अक्षर __user *user_buf,
				    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	u8 buf[32];
	माप_प्रकार len = 0;
	u32 reg_addr;

	mutex_lock(&ar->conf_mutex);
	reg_addr = ar->debug.reg_addr;
	mutex_unlock(&ar->conf_mutex);

	len += scnम_लिखो(buf + len, माप(buf) - len, "0x%x\n", reg_addr);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार ath10k_reg_addr_ग_लिखो(काष्ठा file *file,
				     स्थिर अक्षर __user *user_buf,
				     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	u32 reg_addr;
	पूर्णांक ret;

	ret = kstrtou32_from_user(user_buf, count, 0, &reg_addr);
	अगर (ret)
		वापस ret;

	अगर (!IS_ALIGNED(reg_addr, 4))
		वापस -EFAULT;

	mutex_lock(&ar->conf_mutex);
	ar->debug.reg_addr = reg_addr;
	mutex_unlock(&ar->conf_mutex);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_reg_addr = अणु
	.पढ़ो = ath10k_reg_addr_पढ़ो,
	.ग_लिखो = ath10k_reg_addr_ग_लिखो,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath10k_reg_value_पढ़ो(काष्ठा file *file,
				     अक्षर __user *user_buf,
				     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	u8 buf[48];
	माप_प्रकार len;
	u32 reg_addr, reg_val;
	पूर्णांक ret;

	mutex_lock(&ar->conf_mutex);

	अगर (ar->state != ATH10K_STATE_ON &&
	    ar->state != ATH10K_STATE_UTF) अणु
		ret = -ENETDOWN;
		जाओ निकास;
	पूर्ण

	reg_addr = ar->debug.reg_addr;

	reg_val = ath10k_hअगर_पढ़ो32(ar, reg_addr);
	len = scnम_लिखो(buf, माप(buf), "0x%08x:0x%08x\n", reg_addr, reg_val);

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);

निकास:
	mutex_unlock(&ar->conf_mutex);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार ath10k_reg_value_ग_लिखो(काष्ठा file *file,
				      स्थिर अक्षर __user *user_buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	u32 reg_addr, reg_val;
	पूर्णांक ret;

	mutex_lock(&ar->conf_mutex);

	अगर (ar->state != ATH10K_STATE_ON &&
	    ar->state != ATH10K_STATE_UTF) अणु
		ret = -ENETDOWN;
		जाओ निकास;
	पूर्ण

	reg_addr = ar->debug.reg_addr;

	ret = kstrtou32_from_user(user_buf, count, 0, &reg_val);
	अगर (ret)
		जाओ निकास;

	ath10k_hअगर_ग_लिखो32(ar, reg_addr, reg_val);

	ret = count;

निकास:
	mutex_unlock(&ar->conf_mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_reg_value = अणु
	.पढ़ो = ath10k_reg_value_पढ़ो,
	.ग_लिखो = ath10k_reg_value_ग_लिखो,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath10k_mem_value_पढ़ो(काष्ठा file *file,
				     अक्षर __user *user_buf,
				     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	u8 *buf;
	पूर्णांक ret;

	अगर (*ppos < 0)
		वापस -EINVAL;

	अगर (!count)
		वापस 0;

	mutex_lock(&ar->conf_mutex);

	buf = vदो_स्मृति(count);
	अगर (!buf) अणु
		ret = -ENOMEM;
		जाओ निकास;
	पूर्ण

	अगर (ar->state != ATH10K_STATE_ON &&
	    ar->state != ATH10K_STATE_UTF) अणु
		ret = -ENETDOWN;
		जाओ निकास;
	पूर्ण

	ret = ath10k_hअगर_diag_पढ़ो(ar, *ppos, buf, count);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to read address 0x%08x via diagnose window from debugfs: %d\n",
			    (u32)(*ppos), ret);
		जाओ निकास;
	पूर्ण

	ret = copy_to_user(user_buf, buf, count);
	अगर (ret) अणु
		ret = -EFAULT;
		जाओ निकास;
	पूर्ण

	count -= ret;
	*ppos += count;
	ret = count;

निकास:
	vमुक्त(buf);
	mutex_unlock(&ar->conf_mutex);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार ath10k_mem_value_ग_लिखो(काष्ठा file *file,
				      स्थिर अक्षर __user *user_buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	u8 *buf;
	पूर्णांक ret;

	अगर (*ppos < 0)
		वापस -EINVAL;

	अगर (!count)
		वापस 0;

	mutex_lock(&ar->conf_mutex);

	buf = vदो_स्मृति(count);
	अगर (!buf) अणु
		ret = -ENOMEM;
		जाओ निकास;
	पूर्ण

	अगर (ar->state != ATH10K_STATE_ON &&
	    ar->state != ATH10K_STATE_UTF) अणु
		ret = -ENETDOWN;
		जाओ निकास;
	पूर्ण

	ret = copy_from_user(buf, user_buf, count);
	अगर (ret) अणु
		ret = -EFAULT;
		जाओ निकास;
	पूर्ण

	ret = ath10k_hअगर_diag_ग_लिखो(ar, *ppos, buf, count);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to write address 0x%08x via diagnose window from debugfs: %d\n",
			    (u32)(*ppos), ret);
		जाओ निकास;
	पूर्ण

	*ppos += count;
	ret = count;

निकास:
	vमुक्त(buf);
	mutex_unlock(&ar->conf_mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_mem_value = अणु
	.पढ़ो = ath10k_mem_value_पढ़ो,
	.ग_लिखो = ath10k_mem_value_ग_लिखो,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल पूर्णांक ath10k_debug_htt_stats_req(काष्ठा ath10k *ar)
अणु
	u64 cookie;
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	अगर (ar->debug.htt_stats_mask == 0)
		/* htt stats are disabled */
		वापस 0;

	अगर (ar->state != ATH10K_STATE_ON)
		वापस 0;

	cookie = get_jअगरfies_64();

	ret = ath10k_htt_h2t_stats_req(&ar->htt, ar->debug.htt_stats_mask,
				       ar->debug.reset_htt_stats, cookie);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to send htt stats request: %d\n", ret);
		वापस ret;
	पूर्ण

	queue_delayed_work(ar->workqueue, &ar->debug.htt_stats_dwork,
			   msecs_to_jअगरfies(ATH10K_DEBUG_HTT_STATS_INTERVAL));

	वापस 0;
पूर्ण

अटल व्योम ath10k_debug_htt_stats_dwork(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath10k *ar = container_of(work, काष्ठा ath10k,
					 debug.htt_stats_dwork.work);

	mutex_lock(&ar->conf_mutex);

	ath10k_debug_htt_stats_req(ar);

	mutex_unlock(&ar->conf_mutex);
पूर्ण

अटल sमाप_प्रकार ath10k_पढ़ो_htt_stats_mask(काष्ठा file *file,
					  अक्षर __user *user_buf,
					  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	अक्षर buf[32];
	माप_प्रकार len;

	len = scnम_लिखो(buf, माप(buf), "%lu\n", ar->debug.htt_stats_mask);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार ath10k_ग_लिखो_htt_stats_mask(काष्ठा file *file,
					   स्थिर अक्षर __user *user_buf,
					   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	अचिन्हित दीर्घ mask;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ_from_user(user_buf, count, 0, &mask);
	अगर (ret)
		वापस ret;

	/* max 17 bit masks (क्रम now) */
	अगर (mask > HTT_STATS_BIT_MASK)
		वापस -E2BIG;

	mutex_lock(&ar->conf_mutex);

	ar->debug.htt_stats_mask = mask;

	ret = ath10k_debug_htt_stats_req(ar);
	अगर (ret)
		जाओ out;

	ret = count;

out:
	mutex_unlock(&ar->conf_mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_htt_stats_mask = अणु
	.पढ़ो = ath10k_पढ़ो_htt_stats_mask,
	.ग_लिखो = ath10k_ग_लिखो_htt_stats_mask,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath10k_पढ़ो_htt_max_amsdu_ampdu(काष्ठा file *file,
					       अक्षर __user *user_buf,
					       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	अक्षर buf[64];
	u8 amsdu, ampdu;
	माप_प्रकार len;

	mutex_lock(&ar->conf_mutex);

	amsdu = ar->htt.max_num_amsdu;
	ampdu = ar->htt.max_num_ampdu;
	mutex_unlock(&ar->conf_mutex);

	len = scnम_लिखो(buf, माप(buf), "%u %u\n", amsdu, ampdu);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार ath10k_ग_लिखो_htt_max_amsdu_ampdu(काष्ठा file *file,
						स्थिर अक्षर __user *user_buf,
						माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	पूर्णांक res;
	अक्षर buf[64] = अणु0पूर्ण;
	अचिन्हित पूर्णांक amsdu, ampdu;

	res = simple_ग_लिखो_to_buffer(buf, माप(buf) - 1, ppos,
				     user_buf, count);
	अगर (res <= 0)
		वापस res;

	res = माला_पूछो(buf, "%u %u", &amsdu, &ampdu);

	अगर (res != 2)
		वापस -EINVAL;

	mutex_lock(&ar->conf_mutex);

	res = ath10k_htt_h2t_aggr_cfg_msg(&ar->htt, ampdu, amsdu);
	अगर (res)
		जाओ out;

	res = count;
	ar->htt.max_num_amsdu = amsdu;
	ar->htt.max_num_ampdu = ampdu;

out:
	mutex_unlock(&ar->conf_mutex);
	वापस res;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_htt_max_amsdu_ampdu = अणु
	.पढ़ो = ath10k_पढ़ो_htt_max_amsdu_ampdu,
	.ग_लिखो = ath10k_ग_लिखो_htt_max_amsdu_ampdu,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath10k_पढ़ो_fw_dbglog(काष्ठा file *file,
				     अक्षर __user *user_buf,
				     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	माप_प्रकार len;
	अक्षर buf[96];

	len = scnम_लिखो(buf, माप(buf), "0x%16llx %u\n",
			ar->debug.fw_dbglog_mask, ar->debug.fw_dbglog_level);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार ath10k_ग_लिखो_fw_dbglog(काष्ठा file *file,
				      स्थिर अक्षर __user *user_buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	पूर्णांक ret;
	अक्षर buf[96] = अणु0पूर्ण;
	अचिन्हित पूर्णांक log_level;
	u64 mask;

	ret = simple_ग_लिखो_to_buffer(buf, माप(buf) - 1, ppos,
				     user_buf, count);
	अगर (ret <= 0)
		वापस ret;

	ret = माला_पूछो(buf, "%llx %u", &mask, &log_level);

	अगर (!ret)
		वापस -EINVAL;

	अगर (ret == 1)
		/* शेष अगर user did not specअगरy */
		log_level = ATH10K_DBGLOG_LEVEL_WARN;

	mutex_lock(&ar->conf_mutex);

	ar->debug.fw_dbglog_mask = mask;
	ar->debug.fw_dbglog_level = log_level;

	अगर (ar->state == ATH10K_STATE_ON) अणु
		ret = ath10k_wmi_dbglog_cfg(ar, ar->debug.fw_dbglog_mask,
					    ar->debug.fw_dbglog_level);
		अगर (ret) अणु
			ath10k_warn(ar, "dbglog cfg failed from debugfs: %d\n",
				    ret);
			जाओ निकास;
		पूर्ण
	पूर्ण

	ret = count;

निकास:
	mutex_unlock(&ar->conf_mutex);

	वापस ret;
पूर्ण

/* TODO:  Would be nice to always support ethtool stats, would need to
 * move the stats storage out of ath10k_debug, or always have ath10k_debug
 * काष्ठा available..
 */

/* This generally cooresponds to the debugfs fw_stats file */
अटल स्थिर अक्षर ath10k_gstrings_stats[][ETH_GSTRING_LEN] = अणु
	"tx_pkts_nic",
	"tx_bytes_nic",
	"rx_pkts_nic",
	"rx_bytes_nic",
	"d_noise_floor",
	"d_cycle_count",
	"d_phy_error",
	"d_rts_bad",
	"d_rts_good",
	"d_tx_power", /* in .5 dbM I think */
	"d_rx_crc_err", /* fcs_bad */
	"d_rx_crc_err_drop", /* frame with FCS error, dropped late in kernel */
	"d_no_beacon",
	"d_tx_mpdus_queued",
	"d_tx_msdu_queued",
	"d_tx_msdu_dropped",
	"d_local_enqued",
	"d_local_freed",
	"d_tx_ppdu_hw_queued",
	"d_tx_ppdu_reaped",
	"d_tx_fifo_underrun",
	"d_tx_ppdu_abort",
	"d_tx_mpdu_requed",
	"d_tx_excessive_retries",
	"d_tx_hw_rate",
	"d_tx_dropped_sw_retries",
	"d_tx_illegal_rate",
	"d_tx_continuous_xretries",
	"d_tx_timeout",
	"d_tx_mpdu_txop_limit",
	"d_pdev_resets",
	"d_rx_mid_ppdu_route_change",
	"d_rx_status",
	"d_rx_extra_frags_ring0",
	"d_rx_extra_frags_ring1",
	"d_rx_extra_frags_ring2",
	"d_rx_extra_frags_ring3",
	"d_rx_msdu_htt",
	"d_rx_mpdu_htt",
	"d_rx_msdu_stack",
	"d_rx_mpdu_stack",
	"d_rx_phy_err",
	"d_rx_phy_err_drops",
	"d_rx_mpdu_errors", /* FCS, MIC, ENC */
	"d_fw_crash_count",
	"d_fw_warm_reset_count",
	"d_fw_cold_reset_count",
पूर्ण;

#घोषणा ATH10K_SSTATS_LEN ARRAY_SIZE(ath10k_gstrings_stats)

व्योम ath10k_debug_get_et_strings(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर *vअगर,
				 u32 sset, u8 *data)
अणु
	अगर (sset == ETH_SS_STATS)
		स_नकल(data, *ath10k_gstrings_stats,
		       माप(ath10k_gstrings_stats));
पूर्ण

पूर्णांक ath10k_debug_get_et_sset_count(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_vअगर *vअगर, पूर्णांक sset)
अणु
	अगर (sset == ETH_SS_STATS)
		वापस ATH10K_SSTATS_LEN;

	वापस 0;
पूर्ण

व्योम ath10k_debug_get_et_stats(काष्ठा ieee80211_hw *hw,
			       काष्ठा ieee80211_vअगर *vअगर,
			       काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा ath10k *ar = hw->priv;
	अटल स्थिर काष्ठा ath10k_fw_stats_pdev zero_stats = अणुपूर्ण;
	स्थिर काष्ठा ath10k_fw_stats_pdev *pdev_stats;
	पूर्णांक i = 0, ret;

	mutex_lock(&ar->conf_mutex);

	अगर (ar->state == ATH10K_STATE_ON) अणु
		ret = ath10k_debug_fw_stats_request(ar);
		अगर (ret) अणु
			/* just prपूर्णांक a warning and try to use older results */
			ath10k_warn(ar,
				    "failed to get fw stats for ethtool: %d\n",
				    ret);
		पूर्ण
	पूर्ण

	pdev_stats = list_first_entry_or_null(&ar->debug.fw_stats.pdevs,
					      काष्ठा ath10k_fw_stats_pdev,
					      list);
	अगर (!pdev_stats) अणु
		/* no results available so just वापस zeroes */
		pdev_stats = &zero_stats;
	पूर्ण

	spin_lock_bh(&ar->data_lock);

	data[i++] = pdev_stats->hw_reaped; /* ppdu reaped */
	data[i++] = 0; /* tx bytes */
	data[i++] = pdev_stats->htt_mpdus;
	data[i++] = 0; /* rx bytes */
	data[i++] = pdev_stats->ch_noise_न्यूनमान;
	data[i++] = pdev_stats->cycle_count;
	data[i++] = pdev_stats->phy_err_count;
	data[i++] = pdev_stats->rts_bad;
	data[i++] = pdev_stats->rts_good;
	data[i++] = pdev_stats->chan_tx_घातer;
	data[i++] = pdev_stats->fcs_bad;
	data[i++] = ar->stats.rx_crc_err_drop;
	data[i++] = pdev_stats->no_beacons;
	data[i++] = pdev_stats->mpdu_enqued;
	data[i++] = pdev_stats->msdu_enqued;
	data[i++] = pdev_stats->wmm_drop;
	data[i++] = pdev_stats->local_enqued;
	data[i++] = pdev_stats->local_मुक्तd;
	data[i++] = pdev_stats->hw_queued;
	data[i++] = pdev_stats->hw_reaped;
	data[i++] = pdev_stats->underrun;
	data[i++] = pdev_stats->tx_पात;
	data[i++] = pdev_stats->mpdus_requed;
	data[i++] = pdev_stats->tx_ko;
	data[i++] = pdev_stats->data_rc;
	data[i++] = pdev_stats->sw_retry_failure;
	data[i++] = pdev_stats->illgl_rate_phy_err;
	data[i++] = pdev_stats->pdev_cont_xretry;
	data[i++] = pdev_stats->pdev_tx_समयout;
	data[i++] = pdev_stats->txop_ovf;
	data[i++] = pdev_stats->pdev_resets;
	data[i++] = pdev_stats->mid_ppdu_route_change;
	data[i++] = pdev_stats->status_rcvd;
	data[i++] = pdev_stats->r0_frags;
	data[i++] = pdev_stats->r1_frags;
	data[i++] = pdev_stats->r2_frags;
	data[i++] = pdev_stats->r3_frags;
	data[i++] = pdev_stats->htt_msdus;
	data[i++] = pdev_stats->htt_mpdus;
	data[i++] = pdev_stats->loc_msdus;
	data[i++] = pdev_stats->loc_mpdus;
	data[i++] = pdev_stats->phy_errs;
	data[i++] = pdev_stats->phy_err_drop;
	data[i++] = pdev_stats->mpdu_errs;
	data[i++] = ar->stats.fw_crash_counter;
	data[i++] = ar->stats.fw_warm_reset_counter;
	data[i++] = ar->stats.fw_cold_reset_counter;

	spin_unlock_bh(&ar->data_lock);

	mutex_unlock(&ar->conf_mutex);

	WARN_ON(i != ATH10K_SSTATS_LEN);
पूर्ण

अटल स्थिर काष्ठा file_operations fops_fw_dbglog = अणु
	.पढ़ो = ath10k_पढ़ो_fw_dbglog,
	.ग_लिखो = ath10k_ग_लिखो_fw_dbglog,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल पूर्णांक ath10k_debug_cal_data_fetch(काष्ठा ath10k *ar)
अणु
	u32 hi_addr;
	__le32 addr;
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	अगर (WARN_ON(ar->hw_params.cal_data_len > ATH10K_DEBUG_CAL_DATA_LEN))
		वापस -EINVAL;

	अगर (ar->hw_params.cal_data_len == 0)
		वापस -EOPNOTSUPP;

	hi_addr = host_पूर्णांकerest_item_address(HI_ITEM(hi_board_data));

	ret = ath10k_hअगर_diag_पढ़ो(ar, hi_addr, &addr, माप(addr));
	अगर (ret) अणु
		ath10k_warn(ar, "failed to read hi_board_data address: %d\n",
			    ret);
		वापस ret;
	पूर्ण

	ret = ath10k_hअगर_diag_पढ़ो(ar, le32_to_cpu(addr), ar->debug.cal_data,
				   ar->hw_params.cal_data_len);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to read calibration data: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_debug_cal_data_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ath10k *ar = inode->i_निजी;

	mutex_lock(&ar->conf_mutex);

	अगर (ar->state == ATH10K_STATE_ON ||
	    ar->state == ATH10K_STATE_UTF) अणु
		ath10k_debug_cal_data_fetch(ar);
	पूर्ण

	file->निजी_data = ar;
	mutex_unlock(&ar->conf_mutex);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार ath10k_debug_cal_data_पढ़ो(काष्ठा file *file,
					  अक्षर __user *user_buf,
					  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;

	mutex_lock(&ar->conf_mutex);

	count = simple_पढ़ो_from_buffer(user_buf, count, ppos,
					ar->debug.cal_data,
					ar->hw_params.cal_data_len);

	mutex_unlock(&ar->conf_mutex);

	वापस count;
पूर्ण

अटल sमाप_प्रकार ath10k_ग_लिखो_ani_enable(काष्ठा file *file,
				       स्थिर अक्षर __user *user_buf,
				       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	पूर्णांक ret;
	u8 enable;

	अगर (kstrtou8_from_user(user_buf, count, 0, &enable))
		वापस -EINVAL;

	mutex_lock(&ar->conf_mutex);

	अगर (ar->ani_enabled == enable) अणु
		ret = count;
		जाओ निकास;
	पूर्ण

	ret = ath10k_wmi_pdev_set_param(ar, ar->wmi.pdev_param->ani_enable,
					enable);
	अगर (ret) अणु
		ath10k_warn(ar, "ani_enable failed from debugfs: %d\n", ret);
		जाओ निकास;
	पूर्ण
	ar->ani_enabled = enable;

	ret = count;

निकास:
	mutex_unlock(&ar->conf_mutex);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार ath10k_पढ़ो_ani_enable(काष्ठा file *file, अक्षर __user *user_buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	माप_प्रकार len;
	अक्षर buf[32];

	len = scnम_लिखो(buf, माप(buf), "%d\n", ar->ani_enabled);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations fops_ani_enable = अणु
	.पढ़ो = ath10k_पढ़ो_ani_enable,
	.ग_लिखो = ath10k_ग_लिखो_ani_enable,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल स्थिर काष्ठा file_operations fops_cal_data = अणु
	.खोलो = ath10k_debug_cal_data_खोलो,
	.पढ़ो = ath10k_debug_cal_data_पढ़ो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath10k_पढ़ो_nf_cal_period(काष्ठा file *file,
					 अक्षर __user *user_buf,
					 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	माप_प्रकार len;
	अक्षर buf[32];

	len = scnम_लिखो(buf, माप(buf), "%d\n", ar->debug.nf_cal_period);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार ath10k_ग_लिखो_nf_cal_period(काष्ठा file *file,
					  स्थिर अक्षर __user *user_buf,
					  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	अचिन्हित दीर्घ period;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ_from_user(user_buf, count, 0, &period);
	अगर (ret)
		वापस ret;

	अगर (period > WMI_PDEV_PARAM_CAL_PERIOD_MAX)
		वापस -EINVAL;

	/* there's no way to चयन back to the firmware शेष */
	अगर (period == 0)
		वापस -EINVAL;

	mutex_lock(&ar->conf_mutex);

	ar->debug.nf_cal_period = period;

	अगर (ar->state != ATH10K_STATE_ON) अणु
		/* firmware is not running, nothing अन्यथा to करो */
		ret = count;
		जाओ निकास;
	पूर्ण

	ret = ath10k_wmi_pdev_set_param(ar, ar->wmi.pdev_param->cal_period,
					ar->debug.nf_cal_period);
	अगर (ret) अणु
		ath10k_warn(ar, "cal period cfg failed from debugfs: %d\n",
			    ret);
		जाओ निकास;
	पूर्ण

	ret = count;

निकास:
	mutex_unlock(&ar->conf_mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_nf_cal_period = अणु
	.पढ़ो = ath10k_पढ़ो_nf_cal_period,
	.ग_लिखो = ath10k_ग_लिखो_nf_cal_period,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

#घोषणा ATH10K_TPC_CONFIG_BUF_SIZE	(1024 * 1024)

अटल पूर्णांक ath10k_debug_tpc_stats_request(काष्ठा ath10k *ar)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ समय_left;

	lockdep_निश्चित_held(&ar->conf_mutex);

	reinit_completion(&ar->debug.tpc_complete);

	ret = ath10k_wmi_pdev_get_tpc_config(ar, WMI_TPC_CONFIG_PARAM);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to request tpc config: %d\n", ret);
		वापस ret;
	पूर्ण

	समय_left = रुको_क्रम_completion_समयout(&ar->debug.tpc_complete,
						1 * HZ);
	अगर (समय_left == 0)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

व्योम ath10k_debug_tpc_stats_process(काष्ठा ath10k *ar,
				    काष्ठा ath10k_tpc_stats *tpc_stats)
अणु
	spin_lock_bh(&ar->data_lock);

	kमुक्त(ar->debug.tpc_stats);
	ar->debug.tpc_stats = tpc_stats;
	complete(&ar->debug.tpc_complete);

	spin_unlock_bh(&ar->data_lock);
पूर्ण

व्योम
ath10k_debug_tpc_stats_final_process(काष्ठा ath10k *ar,
				     काष्ठा ath10k_tpc_stats_final *tpc_stats)
अणु
	spin_lock_bh(&ar->data_lock);

	kमुक्त(ar->debug.tpc_stats_final);
	ar->debug.tpc_stats_final = tpc_stats;
	complete(&ar->debug.tpc_complete);

	spin_unlock_bh(&ar->data_lock);
पूर्ण

अटल व्योम ath10k_tpc_stats_prपूर्णांक(काष्ठा ath10k_tpc_stats *tpc_stats,
				   अचिन्हित पूर्णांक j, अक्षर *buf, माप_प्रकार *len)
अणु
	पूर्णांक i;
	माप_प्रकार buf_len;
	अटल स्थिर अक्षर table_str[][5] = अणु "CDD",
					     "STBC",
					     "TXBF" पूर्ण;
	अटल स्थिर अक्षर pream_str[][6] = अणु "CCK",
					     "OFDM",
					     "HT20",
					     "HT40",
					     "VHT20",
					     "VHT40",
					     "VHT80",
					     "HTCUP" पूर्ण;

	buf_len = ATH10K_TPC_CONFIG_BUF_SIZE;
	*len += scnम_लिखो(buf + *len, buf_len - *len,
			  "********************************\n");
	*len += scnम_लिखो(buf + *len, buf_len - *len,
			  "******************* %s POWER TABLE ****************\n",
			  table_str[j]);
	*len += scnम_लिखो(buf + *len, buf_len - *len,
			  "********************************\n");
	*len += scnम_लिखो(buf + *len, buf_len - *len,
			  "No.  Preamble Rate_code ");

	क्रम (i = 0; i < tpc_stats->num_tx_chain; i++)
		*len += scnम_लिखो(buf + *len, buf_len - *len,
				  "tpc_value%d ", i);

	*len += scnम_लिखो(buf + *len, buf_len - *len, "\n");

	क्रम (i = 0; i < tpc_stats->rate_max; i++) अणु
		*len += scnम_लिखो(buf + *len, buf_len - *len,
				  "%8d %s 0x%2x %s\n", i,
				  pream_str[tpc_stats->tpc_table[j].pream_idx[i]],
				  tpc_stats->tpc_table[j].rate_code[i],
				  tpc_stats->tpc_table[j].tpc_value[i]);
	पूर्ण

	*len += scnम_लिखो(buf + *len, buf_len - *len,
			  "***********************************\n");
पूर्ण

अटल व्योम ath10k_tpc_stats_fill(काष्ठा ath10k *ar,
				  काष्ठा ath10k_tpc_stats *tpc_stats,
				  अक्षर *buf)
अणु
	पूर्णांक j;
	माप_प्रकार len, buf_len;

	len = 0;
	buf_len = ATH10K_TPC_CONFIG_BUF_SIZE;

	spin_lock_bh(&ar->data_lock);

	अगर (!tpc_stats) अणु
		ath10k_warn(ar, "failed to get tpc stats\n");
		जाओ unlock;
	पूर्ण

	len += scnम_लिखो(buf + len, buf_len - len, "\n");
	len += scnम_लिखो(buf + len, buf_len - len,
			 "*************************************\n");
	len += scnम_लिखो(buf + len, buf_len - len,
			 "TPC config for channel %4d mode %d\n",
			 tpc_stats->chan_freq,
			 tpc_stats->phy_mode);
	len += scnम_लिखो(buf + len, buf_len - len,
			 "*************************************\n");
	len += scnम_लिखो(buf + len, buf_len - len,
			 "CTL		=  0x%2x Reg. Domain		= %2d\n",
			 tpc_stats->ctl,
			 tpc_stats->reg_करोमुख्य);
	len += scnम_लिखो(buf + len, buf_len - len,
			 "Antenna Gain	= %2d Reg. Max Antenna Gain	=  %2d\n",
			 tpc_stats->twice_antenna_gain,
			 tpc_stats->twice_antenna_reduction);
	len += scnम_लिखो(buf + len, buf_len - len,
			 "Power Limit	= %2d Reg. Max Power		= %2d\n",
			 tpc_stats->घातer_limit,
			 tpc_stats->twice_max_rd_घातer / 2);
	len += scnम_लिखो(buf + len, buf_len - len,
			 "Num tx chains	= %2d Num supported rates	= %2d\n",
			 tpc_stats->num_tx_chain,
			 tpc_stats->rate_max);

	क्रम (j = 0; j < WMI_TPC_FLAG; j++) अणु
		चयन (j) अणु
		हाल WMI_TPC_TABLE_TYPE_CDD:
			अगर (tpc_stats->flag[j] == ATH10K_TPC_TABLE_TYPE_FLAG) अणु
				len += scnम_लिखो(buf + len, buf_len - len,
						 "CDD not supported\n");
				अवरोध;
			पूर्ण

			ath10k_tpc_stats_prपूर्णांक(tpc_stats, j, buf, &len);
			अवरोध;
		हाल WMI_TPC_TABLE_TYPE_STBC:
			अगर (tpc_stats->flag[j] == ATH10K_TPC_TABLE_TYPE_FLAG) अणु
				len += scnम_लिखो(buf + len, buf_len - len,
						 "STBC not supported\n");
				अवरोध;
			पूर्ण

			ath10k_tpc_stats_prपूर्णांक(tpc_stats, j, buf, &len);
			अवरोध;
		हाल WMI_TPC_TABLE_TYPE_TXBF:
			अगर (tpc_stats->flag[j] == ATH10K_TPC_TABLE_TYPE_FLAG) अणु
				len += scnम_लिखो(buf + len, buf_len - len,
						 "TXBF not supported\n***************************\n");
				अवरोध;
			पूर्ण

			ath10k_tpc_stats_prपूर्णांक(tpc_stats, j, buf, &len);
			अवरोध;
		शेष:
			len += scnम_लिखो(buf + len, buf_len - len,
					 "Invalid Type\n");
			अवरोध;
		पूर्ण
	पूर्ण

unlock:
	spin_unlock_bh(&ar->data_lock);

	अगर (len >= buf_len)
		buf[len - 1] = 0;
	अन्यथा
		buf[len] = 0;
पूर्ण

अटल पूर्णांक ath10k_tpc_stats_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ath10k *ar = inode->i_निजी;
	व्योम *buf = शून्य;
	पूर्णांक ret;

	mutex_lock(&ar->conf_mutex);

	अगर (ar->state != ATH10K_STATE_ON) अणु
		ret = -ENETDOWN;
		जाओ err_unlock;
	पूर्ण

	buf = vदो_स्मृति(ATH10K_TPC_CONFIG_BUF_SIZE);
	अगर (!buf) अणु
		ret = -ENOMEM;
		जाओ err_unlock;
	पूर्ण

	ret = ath10k_debug_tpc_stats_request(ar);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to request tpc config stats: %d\n",
			    ret);
		जाओ err_मुक्त;
	पूर्ण

	ath10k_tpc_stats_fill(ar, ar->debug.tpc_stats, buf);
	file->निजी_data = buf;

	mutex_unlock(&ar->conf_mutex);
	वापस 0;

err_मुक्त:
	vमुक्त(buf);

err_unlock:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_tpc_stats_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	vमुक्त(file->निजी_data);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार ath10k_tpc_stats_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
				     माप_प्रकार count, loff_t *ppos)
अणु
	स्थिर अक्षर *buf = file->निजी_data;
	माप_प्रकार len = म_माप(buf);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations fops_tpc_stats = अणु
	.खोलो = ath10k_tpc_stats_खोलो,
	.release = ath10k_tpc_stats_release,
	.पढ़ो = ath10k_tpc_stats_पढ़ो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

पूर्णांक ath10k_debug_start(काष्ठा ath10k *ar)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	ret = ath10k_debug_htt_stats_req(ar);
	अगर (ret)
		/* जारी normally anyway, this isn't serious */
		ath10k_warn(ar, "failed to start htt stats workqueue: %d\n",
			    ret);

	अगर (ar->debug.fw_dbglog_mask) अणु
		ret = ath10k_wmi_dbglog_cfg(ar, ar->debug.fw_dbglog_mask,
					    ATH10K_DBGLOG_LEVEL_WARN);
		अगर (ret)
			/* not serious */
			ath10k_warn(ar, "failed to enable dbglog during start: %d",
				    ret);
	पूर्ण

	अगर (ar->pktlog_filter) अणु
		ret = ath10k_wmi_pdev_pktlog_enable(ar,
						    ar->pktlog_filter);
		अगर (ret)
			/* not serious */
			ath10k_warn(ar,
				    "failed to enable pktlog filter %x: %d\n",
				    ar->pktlog_filter, ret);
	पूर्ण अन्यथा अणु
		ret = ath10k_wmi_pdev_pktlog_disable(ar);
		अगर (ret)
			/* not serious */
			ath10k_warn(ar, "failed to disable pktlog: %d\n", ret);
	पूर्ण

	अगर (ar->debug.nf_cal_period &&
	    !test_bit(ATH10K_FW_FEATURE_NON_BMI,
		      ar->normal_mode_fw.fw_file.fw_features)) अणु
		ret = ath10k_wmi_pdev_set_param(ar,
						ar->wmi.pdev_param->cal_period,
						ar->debug.nf_cal_period);
		अगर (ret)
			/* not serious */
			ath10k_warn(ar, "cal period cfg failed from debug start: %d\n",
				    ret);
	पूर्ण

	वापस ret;
पूर्ण

व्योम ath10k_debug_stop(काष्ठा ath10k *ar)
अणु
	lockdep_निश्चित_held(&ar->conf_mutex);

	अगर (!test_bit(ATH10K_FW_FEATURE_NON_BMI,
		      ar->normal_mode_fw.fw_file.fw_features))
		ath10k_debug_cal_data_fetch(ar);

	/* Must not use _sync to aव्योम deadlock, we करो that in
	 * ath10k_debug_destroy(). The check क्रम htt_stats_mask is to aव्योम
	 * warning from del_समयr().
	 */
	अगर (ar->debug.htt_stats_mask != 0)
		cancel_delayed_work(&ar->debug.htt_stats_dwork);

	ath10k_wmi_pdev_pktlog_disable(ar);
पूर्ण

अटल sमाप_प्रकार ath10k_ग_लिखो_simulate_radar(काष्ठा file *file,
					   स्थिर अक्षर __user *user_buf,
					   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	काष्ठा ath10k_vअगर *arvअगर;

	/* Just check क्रम the first vअगर alone, as all the vअगरs will be
	 * sharing the same channel and अगर the channel is disabled, all the
	 * vअगरs will share the same 'is_started' state.
	 */
	arvअगर = list_first_entry(&ar->arvअगरs, typeof(*arvअगर), list);
	अगर (!arvअगर->is_started)
		वापस -EINVAL;

	ieee80211_radar_detected(ar->hw);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_simulate_radar = अणु
	.ग_लिखो = ath10k_ग_लिखो_simulate_radar,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

#घोषणा ATH10K_DFS_STAT(s, p) (\
	len += scnम_लिखो(buf + len, size - len, "%-28s : %10u\n", s, \
			 ar->debug.dfs_stats.p))

#घोषणा ATH10K_DFS_POOL_STAT(s, p) (\
	len += scnम_लिखो(buf + len, size - len, "%-28s : %10u\n", s, \
			 ar->debug.dfs_pool_stats.p))

अटल sमाप_प्रकार ath10k_पढ़ो_dfs_stats(काष्ठा file *file, अक्षर __user *user_buf,
				     माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक retval = 0, len = 0;
	स्थिर पूर्णांक size = 8000;
	काष्ठा ath10k *ar = file->निजी_data;
	अक्षर *buf;

	buf = kzalloc(size, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	अगर (!ar->dfs_detector) अणु
		len += scnम_लिखो(buf + len, size - len, "DFS not enabled\n");
		जाओ निकास;
	पूर्ण

	ar->debug.dfs_pool_stats =
			ar->dfs_detector->get_stats(ar->dfs_detector);

	len += scnम_लिखो(buf + len, size - len, "Pulse detector statistics:\n");

	ATH10K_DFS_STAT("reported phy errors", phy_errors);
	ATH10K_DFS_STAT("pulse events reported", pulses_total);
	ATH10K_DFS_STAT("DFS pulses detected", pulses_detected);
	ATH10K_DFS_STAT("DFS pulses discarded", pulses_discarded);
	ATH10K_DFS_STAT("Radars detected", radar_detected);

	len += scnम_लिखो(buf + len, size - len, "Global Pool statistics:\n");
	ATH10K_DFS_POOL_STAT("Pool references", pool_reference);
	ATH10K_DFS_POOL_STAT("Pulses allocated", pulse_allocated);
	ATH10K_DFS_POOL_STAT("Pulses alloc error", pulse_alloc_error);
	ATH10K_DFS_POOL_STAT("Pulses in use", pulse_used);
	ATH10K_DFS_POOL_STAT("Seqs. allocated", pseq_allocated);
	ATH10K_DFS_POOL_STAT("Seqs. alloc error", pseq_alloc_error);
	ATH10K_DFS_POOL_STAT("Seqs. in use", pseq_used);

निकास:
	अगर (len > size)
		len = size;

	retval = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
	kमुक्त(buf);

	वापस retval;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_dfs_stats = अणु
	.पढ़ो = ath10k_पढ़ो_dfs_stats,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath10k_ग_लिखो_pktlog_filter(काष्ठा file *file,
					  स्थिर अक्षर __user *ubuf,
					  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	u32 filter;
	पूर्णांक ret;

	अगर (kstrtouपूर्णांक_from_user(ubuf, count, 0, &filter))
		वापस -EINVAL;

	mutex_lock(&ar->conf_mutex);

	अगर (ar->state != ATH10K_STATE_ON) अणु
		ar->pktlog_filter = filter;
		ret = count;
		जाओ out;
	पूर्ण

	अगर (filter == ar->pktlog_filter) अणु
		ret = count;
		जाओ out;
	पूर्ण

	अगर (filter) अणु
		ret = ath10k_wmi_pdev_pktlog_enable(ar, filter);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to enable pktlog filter %x: %d\n",
				    ar->pktlog_filter, ret);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = ath10k_wmi_pdev_pktlog_disable(ar);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to disable pktlog: %d\n", ret);
			जाओ out;
		पूर्ण
	पूर्ण

	ar->pktlog_filter = filter;
	ret = count;

out:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ath10k_पढ़ो_pktlog_filter(काष्ठा file *file, अक्षर __user *ubuf,
					 माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर buf[32];
	काष्ठा ath10k *ar = file->निजी_data;
	पूर्णांक len = 0;

	mutex_lock(&ar->conf_mutex);
	len = scnम_लिखो(buf, माप(buf) - len, "%08x\n",
			ar->pktlog_filter);
	mutex_unlock(&ar->conf_mutex);

	वापस simple_पढ़ो_from_buffer(ubuf, count, ppos, buf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations fops_pktlog_filter = अणु
	.पढ़ो = ath10k_पढ़ो_pktlog_filter,
	.ग_लिखो = ath10k_ग_लिखो_pktlog_filter,
	.खोलो = simple_खोलो
पूर्ण;

अटल sमाप_प्रकार ath10k_ग_लिखो_quiet_period(काष्ठा file *file,
					 स्थिर अक्षर __user *ubuf,
					 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	u32 period;

	अगर (kstrtouपूर्णांक_from_user(ubuf, count, 0, &period))
		वापस -EINVAL;

	अगर (period < ATH10K_QUIET_PERIOD_MIN) अणु
		ath10k_warn(ar, "Quiet period %u can not be lesser than 25ms\n",
			    period);
		वापस -EINVAL;
	पूर्ण
	mutex_lock(&ar->conf_mutex);
	ar->thermal.quiet_period = period;
	ath10k_thermal_set_throttling(ar);
	mutex_unlock(&ar->conf_mutex);

	वापस count;
पूर्ण

अटल sमाप_प्रकार ath10k_पढ़ो_quiet_period(काष्ठा file *file, अक्षर __user *ubuf,
					माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर buf[32];
	काष्ठा ath10k *ar = file->निजी_data;
	पूर्णांक len = 0;

	mutex_lock(&ar->conf_mutex);
	len = scnम_लिखो(buf, माप(buf) - len, "%d\n",
			ar->thermal.quiet_period);
	mutex_unlock(&ar->conf_mutex);

	वापस simple_पढ़ो_from_buffer(ubuf, count, ppos, buf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations fops_quiet_period = अणु
	.पढ़ो = ath10k_पढ़ो_quiet_period,
	.ग_लिखो = ath10k_ग_लिखो_quiet_period,
	.खोलो = simple_खोलो
पूर्ण;

अटल sमाप_प्रकार ath10k_ग_लिखो_btcoex(काष्ठा file *file,
				   स्थिर अक्षर __user *ubuf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	अक्षर buf[32];
	माप_प्रकार buf_size;
	पूर्णांक ret;
	bool val;
	u32 pdev_param;

	buf_size = min(count, (माप(buf) - 1));
	अगर (copy_from_user(buf, ubuf, buf_size))
		वापस -EFAULT;

	buf[buf_size] = '\0';

	अगर (strtobool(buf, &val) != 0)
		वापस -EINVAL;

	अगर (!ar->coex_support)
		वापस -EOPNOTSUPP;

	mutex_lock(&ar->conf_mutex);

	अगर (ar->state != ATH10K_STATE_ON &&
	    ar->state != ATH10K_STATE_RESTARTED) अणु
		ret = -ENETDOWN;
		जाओ निकास;
	पूर्ण

	अगर (!(test_bit(ATH10K_FLAG_BTCOEX, &ar->dev_flags) ^ val)) अणु
		ret = count;
		जाओ निकास;
	पूर्ण

	pdev_param = ar->wmi.pdev_param->enable_btcoex;
	अगर (test_bit(ATH10K_FW_FEATURE_BTCOEX_PARAM,
		     ar->running_fw->fw_file.fw_features)) अणु
		ret = ath10k_wmi_pdev_set_param(ar, pdev_param, val);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to enable btcoex: %d\n", ret);
			ret = count;
			जाओ निकास;
		पूर्ण
	पूर्ण अन्यथा अणु
		ath10k_info(ar, "restarting firmware due to btcoex change");
		ath10k_core_start_recovery(ar);
	पूर्ण

	अगर (val)
		set_bit(ATH10K_FLAG_BTCOEX, &ar->dev_flags);
	अन्यथा
		clear_bit(ATH10K_FLAG_BTCOEX, &ar->dev_flags);

	ret = count;

निकास:
	mutex_unlock(&ar->conf_mutex);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार ath10k_पढ़ो_btcoex(काष्ठा file *file, अक्षर __user *ubuf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर buf[32];
	काष्ठा ath10k *ar = file->निजी_data;
	पूर्णांक len = 0;

	mutex_lock(&ar->conf_mutex);
	len = scnम_लिखो(buf, माप(buf) - len, "%d\n",
			test_bit(ATH10K_FLAG_BTCOEX, &ar->dev_flags));
	mutex_unlock(&ar->conf_mutex);

	वापस simple_पढ़ो_from_buffer(ubuf, count, ppos, buf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations fops_btcoex = अणु
	.पढ़ो = ath10k_पढ़ो_btcoex,
	.ग_लिखो = ath10k_ग_लिखो_btcoex,
	.खोलो = simple_खोलो
पूर्ण;

अटल sमाप_प्रकार ath10k_ग_लिखो_enable_extd_tx_stats(काष्ठा file *file,
						 स्थिर अक्षर __user *ubuf,
						 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	u32 filter;
	पूर्णांक ret;

	अगर (kstrtouपूर्णांक_from_user(ubuf, count, 0, &filter))
		वापस -EINVAL;

	mutex_lock(&ar->conf_mutex);

	अगर (ar->state != ATH10K_STATE_ON) अणु
		ar->debug.enable_extd_tx_stats = filter;
		ret = count;
		जाओ out;
	पूर्ण

	अगर (filter == ar->debug.enable_extd_tx_stats) अणु
		ret = count;
		जाओ out;
	पूर्ण

	ar->debug.enable_extd_tx_stats = filter;
	ret = count;

out:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ath10k_पढ़ो_enable_extd_tx_stats(काष्ठा file *file,
						अक्षर __user *ubuf,
						माप_प्रकार count, loff_t *ppos)

अणु
	अक्षर buf[32];
	काष्ठा ath10k *ar = file->निजी_data;
	पूर्णांक len = 0;

	mutex_lock(&ar->conf_mutex);
	len = scnम_लिखो(buf, माप(buf) - len, "%08x\n",
			ar->debug.enable_extd_tx_stats);
	mutex_unlock(&ar->conf_mutex);

	वापस simple_पढ़ो_from_buffer(ubuf, count, ppos, buf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations fops_enable_extd_tx_stats = अणु
	.पढ़ो = ath10k_पढ़ो_enable_extd_tx_stats,
	.ग_लिखो = ath10k_ग_लिखो_enable_extd_tx_stats,
	.खोलो = simple_खोलो
पूर्ण;

अटल sमाप_प्रकार ath10k_ग_लिखो_peer_stats(काष्ठा file *file,
				       स्थिर अक्षर __user *ubuf,
				       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	अक्षर buf[32];
	माप_प्रकार buf_size;
	पूर्णांक ret;
	bool val;

	buf_size = min(count, (माप(buf) - 1));
	अगर (copy_from_user(buf, ubuf, buf_size))
		वापस -EFAULT;

	buf[buf_size] = '\0';

	अगर (strtobool(buf, &val) != 0)
		वापस -EINVAL;

	mutex_lock(&ar->conf_mutex);

	अगर (ar->state != ATH10K_STATE_ON &&
	    ar->state != ATH10K_STATE_RESTARTED) अणु
		ret = -ENETDOWN;
		जाओ निकास;
	पूर्ण

	अगर (!(test_bit(ATH10K_FLAG_PEER_STATS, &ar->dev_flags) ^ val)) अणु
		ret = count;
		जाओ निकास;
	पूर्ण

	अगर (val)
		set_bit(ATH10K_FLAG_PEER_STATS, &ar->dev_flags);
	अन्यथा
		clear_bit(ATH10K_FLAG_PEER_STATS, &ar->dev_flags);

	ath10k_info(ar, "restarting firmware due to Peer stats change");

	ath10k_core_start_recovery(ar);
	ret = count;

निकास:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ath10k_पढ़ो_peer_stats(काष्ठा file *file, अक्षर __user *ubuf,
				      माप_प्रकार count, loff_t *ppos)

अणु
	अक्षर buf[32];
	काष्ठा ath10k *ar = file->निजी_data;
	पूर्णांक len = 0;

	mutex_lock(&ar->conf_mutex);
	len = scnम_लिखो(buf, माप(buf) - len, "%d\n",
			test_bit(ATH10K_FLAG_PEER_STATS, &ar->dev_flags));
	mutex_unlock(&ar->conf_mutex);

	वापस simple_पढ़ो_from_buffer(ubuf, count, ppos, buf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations fops_peer_stats = अणु
	.पढ़ो = ath10k_पढ़ो_peer_stats,
	.ग_लिखो = ath10k_ग_लिखो_peer_stats,
	.खोलो = simple_खोलो
पूर्ण;

अटल sमाप_प्रकार ath10k_debug_fw_checksums_पढ़ो(काष्ठा file *file,
					      अक्षर __user *user_buf,
					      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	माप_प्रकार len = 0, buf_len = 4096;
	sमाप_प्रकार ret_cnt;
	अक्षर *buf;

	buf = kzalloc(buf_len, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	mutex_lock(&ar->conf_mutex);

	len += scnम_लिखो(buf + len, buf_len - len,
			 "firmware-N.bin\t\t%08x\n",
			 crc32_le(0, ar->normal_mode_fw.fw_file.firmware->data,
				  ar->normal_mode_fw.fw_file.firmware->size));
	len += scnम_लिखो(buf + len, buf_len - len,
			 "athwlan\t\t\t%08x\n",
			 crc32_le(0, ar->normal_mode_fw.fw_file.firmware_data,
				  ar->normal_mode_fw.fw_file.firmware_len));
	len += scnम_लिखो(buf + len, buf_len - len,
			 "otp\t\t\t%08x\n",
			 crc32_le(0, ar->normal_mode_fw.fw_file.otp_data,
				  ar->normal_mode_fw.fw_file.otp_len));
	len += scnम_लिखो(buf + len, buf_len - len,
			 "codeswap\t\t%08x\n",
			 crc32_le(0, ar->normal_mode_fw.fw_file.codeswap_data,
				  ar->normal_mode_fw.fw_file.codeswap_len));
	len += scnम_लिखो(buf + len, buf_len - len,
			 "board-N.bin\t\t%08x\n",
			 crc32_le(0, ar->normal_mode_fw.board->data,
				  ar->normal_mode_fw.board->size));
	len += scnम_लिखो(buf + len, buf_len - len,
			 "board\t\t\t%08x\n",
			 crc32_le(0, ar->normal_mode_fw.board_data,
				  ar->normal_mode_fw.board_len));

	ret_cnt = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);

	mutex_unlock(&ar->conf_mutex);

	kमुक्त(buf);
	वापस ret_cnt;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_fw_checksums = अणु
	.पढ़ो = ath10k_debug_fw_checksums_पढ़ो,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath10k_sta_tid_stats_mask_पढ़ो(काष्ठा file *file,
					      अक्षर __user *user_buf,
					      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	अक्षर buf[32];
	माप_प्रकार len;

	len = scnम_लिखो(buf, माप(buf), "0x%08x\n", ar->sta_tid_stats_mask);
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार ath10k_sta_tid_stats_mask_ग_लिखो(काष्ठा file *file,
					       स्थिर अक्षर __user *user_buf,
					       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	अक्षर buf[32];
	sमाप_प्रकार len;
	u32 mask;

	len = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, len))
		वापस -EFAULT;

	buf[len] = '\0';
	अगर (kstrtoपूर्णांक(buf, 0, &mask))
		वापस -EINVAL;

	ar->sta_tid_stats_mask = mask;

	वापस len;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_sta_tid_stats_mask = अणु
	.पढ़ो = ath10k_sta_tid_stats_mask_पढ़ो,
	.ग_लिखो = ath10k_sta_tid_stats_mask_ग_लिखो,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल पूर्णांक ath10k_debug_tpc_stats_final_request(काष्ठा ath10k *ar)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ समय_left;

	lockdep_निश्चित_held(&ar->conf_mutex);

	reinit_completion(&ar->debug.tpc_complete);

	ret = ath10k_wmi_pdev_get_tpc_table_cmdid(ar, WMI_TPC_CONFIG_PARAM);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to request tpc table cmdid: %d\n", ret);
		वापस ret;
	पूर्ण

	समय_left = रुको_क्रम_completion_समयout(&ar->debug.tpc_complete,
						1 * HZ);
	अगर (समय_left == 0)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_tpc_stats_final_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ath10k *ar = inode->i_निजी;
	व्योम *buf;
	पूर्णांक ret;

	mutex_lock(&ar->conf_mutex);

	अगर (ar->state != ATH10K_STATE_ON) अणु
		ret = -ENETDOWN;
		जाओ err_unlock;
	पूर्ण

	buf = vदो_स्मृति(ATH10K_TPC_CONFIG_BUF_SIZE);
	अगर (!buf) अणु
		ret = -ENOMEM;
		जाओ err_unlock;
	पूर्ण

	ret = ath10k_debug_tpc_stats_final_request(ar);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to request tpc stats final: %d\n",
			    ret);
		जाओ err_मुक्त;
	पूर्ण

	ath10k_tpc_stats_fill(ar, ar->debug.tpc_stats, buf);
	file->निजी_data = buf;

	mutex_unlock(&ar->conf_mutex);
	वापस 0;

err_मुक्त:
	vमुक्त(buf);

err_unlock:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_tpc_stats_final_release(काष्ठा inode *inode,
					  काष्ठा file *file)
अणु
	vमुक्त(file->निजी_data);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार ath10k_tpc_stats_final_पढ़ो(काष्ठा file *file,
					   अक्षर __user *user_buf,
					   माप_प्रकार count, loff_t *ppos)
अणु
	स्थिर अक्षर *buf = file->निजी_data;
	अचिन्हित पूर्णांक len = म_माप(buf);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations fops_tpc_stats_final = अणु
	.खोलो = ath10k_tpc_stats_final_खोलो,
	.release = ath10k_tpc_stats_final_release,
	.पढ़ो = ath10k_tpc_stats_final_पढ़ो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath10k_ग_लिखो_warm_hw_reset(काष्ठा file *file,
					  स्थिर अक्षर __user *user_buf,
					  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	पूर्णांक ret;
	bool val;

	अगर (kstrtobool_from_user(user_buf, count, &val))
		वापस -EFAULT;

	अगर (!val)
		वापस -EINVAL;

	mutex_lock(&ar->conf_mutex);

	अगर (ar->state != ATH10K_STATE_ON) अणु
		ret = -ENETDOWN;
		जाओ निकास;
	पूर्ण

	ret = ath10k_wmi_pdev_set_param(ar, ar->wmi.pdev_param->pdev_reset,
					WMI_RST_MODE_WARM_RESET);

	अगर (ret) अणु
		ath10k_warn(ar, "failed to enable warm hw reset: %d\n", ret);
		जाओ निकास;
	पूर्ण

	ret = count;

निकास:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_warm_hw_reset = अणु
	.ग_लिखो = ath10k_ग_लिखो_warm_hw_reset,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल व्योम ath10k_peer_ps_state_disable(व्योम *data,
					 काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ath10k *ar = data;
	काष्ठा ath10k_sta *arsta = (काष्ठा ath10k_sta *)sta->drv_priv;

	spin_lock_bh(&ar->data_lock);
	arsta->peer_ps_state = WMI_PEER_PS_STATE_DISABLED;
	spin_unlock_bh(&ar->data_lock);
पूर्ण

अटल sमाप_प्रकार ath10k_ग_लिखो_ps_state_enable(काष्ठा file *file,
					    स्थिर अक्षर __user *user_buf,
					    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	पूर्णांक ret;
	u32 param;
	u8 ps_state_enable;

	अगर (kstrtou8_from_user(user_buf, count, 0, &ps_state_enable))
		वापस -EINVAL;

	अगर (ps_state_enable > 1)
		वापस -EINVAL;

	mutex_lock(&ar->conf_mutex);

	अगर (ar->ps_state_enable == ps_state_enable) अणु
		ret = count;
		जाओ निकास;
	पूर्ण

	param = ar->wmi.pdev_param->peer_sta_ps_statechg_enable;
	ret = ath10k_wmi_pdev_set_param(ar, param, ps_state_enable);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to enable ps_state_enable: %d\n",
			    ret);
		जाओ निकास;
	पूर्ण
	ar->ps_state_enable = ps_state_enable;

	अगर (!ar->ps_state_enable)
		ieee80211_iterate_stations_atomic(ar->hw,
						  ath10k_peer_ps_state_disable,
						  ar);

	ret = count;

निकास:
	mutex_unlock(&ar->conf_mutex);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार ath10k_पढ़ो_ps_state_enable(काष्ठा file *file,
					   अक्षर __user *user_buf,
					   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	पूर्णांक len = 0;
	अक्षर buf[32];

	mutex_lock(&ar->conf_mutex);
	len = scnम_लिखो(buf, माप(buf) - len, "%d\n",
			ar->ps_state_enable);
	mutex_unlock(&ar->conf_mutex);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations fops_ps_state_enable = अणु
	.पढ़ो = ath10k_पढ़ो_ps_state_enable,
	.ग_लिखो = ath10k_ग_लिखो_ps_state_enable,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार ath10k_ग_लिखो_reset_htt_stats(काष्ठा file *file,
					    स्थिर अक्षर __user *user_buf,
					    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath10k *ar = file->निजी_data;
	अचिन्हित दीर्घ reset;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ_from_user(user_buf, count, 0, &reset);
	अगर (ret)
		वापस ret;

	अगर (reset == 0 || reset > 0x1ffff)
		वापस -EINVAL;

	mutex_lock(&ar->conf_mutex);

	ar->debug.reset_htt_stats = reset;

	ret = ath10k_debug_htt_stats_req(ar);
	अगर (ret)
		जाओ out;

	ar->debug.reset_htt_stats = 0;
	ret = count;

out:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_reset_htt_stats = अणु
	.ग_लिखो = ath10k_ग_लिखो_reset_htt_stats,
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;

पूर्णांक ath10k_debug_create(काष्ठा ath10k *ar)
अणु
	ar->debug.cal_data = vzalloc(ATH10K_DEBUG_CAL_DATA_LEN);
	अगर (!ar->debug.cal_data)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&ar->debug.fw_stats.pdevs);
	INIT_LIST_HEAD(&ar->debug.fw_stats.vdevs);
	INIT_LIST_HEAD(&ar->debug.fw_stats.peers);
	INIT_LIST_HEAD(&ar->debug.fw_stats.peers_extd);

	वापस 0;
पूर्ण

व्योम ath10k_debug_destroy(काष्ठा ath10k *ar)
अणु
	vमुक्त(ar->debug.cal_data);
	ar->debug.cal_data = शून्य;

	ath10k_debug_fw_stats_reset(ar);

	kमुक्त(ar->debug.tpc_stats);
	kमुक्त(ar->debug.tpc_stats_final);
पूर्ण

पूर्णांक ath10k_debug_रेजिस्टर(काष्ठा ath10k *ar)
अणु
	ar->debug.debugfs_phy = debugfs_create_dir("ath10k",
						   ar->hw->wiphy->debugfsdir);
	अगर (IS_ERR_OR_शून्य(ar->debug.debugfs_phy)) अणु
		अगर (IS_ERR(ar->debug.debugfs_phy))
			वापस PTR_ERR(ar->debug.debugfs_phy);

		वापस -ENOMEM;
	पूर्ण

	INIT_DELAYED_WORK(&ar->debug.htt_stats_dwork,
			  ath10k_debug_htt_stats_dwork);

	init_completion(&ar->debug.tpc_complete);
	init_completion(&ar->debug.fw_stats_complete);

	debugfs_create_file("fw_stats", 0400, ar->debug.debugfs_phy, ar,
			    &fops_fw_stats);

	debugfs_create_file("fw_reset_stats", 0400, ar->debug.debugfs_phy, ar,
			    &fops_fw_reset_stats);

	debugfs_create_file("wmi_services", 0400, ar->debug.debugfs_phy, ar,
			    &fops_wmi_services);

	debugfs_create_file("simulate_fw_crash", 0600, ar->debug.debugfs_phy, ar,
			    &fops_simulate_fw_crash);

	debugfs_create_file("reg_addr", 0600, ar->debug.debugfs_phy, ar,
			    &fops_reg_addr);

	debugfs_create_file("reg_value", 0600, ar->debug.debugfs_phy, ar,
			    &fops_reg_value);

	debugfs_create_file("mem_value", 0600, ar->debug.debugfs_phy, ar,
			    &fops_mem_value);

	debugfs_create_file("chip_id", 0400, ar->debug.debugfs_phy, ar,
			    &fops_chip_id);

	debugfs_create_file("htt_stats_mask", 0600, ar->debug.debugfs_phy, ar,
			    &fops_htt_stats_mask);

	debugfs_create_file("htt_max_amsdu_ampdu", 0600, ar->debug.debugfs_phy, ar,
			    &fops_htt_max_amsdu_ampdu);

	debugfs_create_file("fw_dbglog", 0600, ar->debug.debugfs_phy, ar,
			    &fops_fw_dbglog);

	अगर (!test_bit(ATH10K_FW_FEATURE_NON_BMI,
		      ar->normal_mode_fw.fw_file.fw_features)) अणु
		debugfs_create_file("cal_data", 0400, ar->debug.debugfs_phy, ar,
				    &fops_cal_data);

		debugfs_create_file("nf_cal_period", 0600, ar->debug.debugfs_phy, ar,
				    &fops_nf_cal_period);
	पूर्ण

	debugfs_create_file("ani_enable", 0600, ar->debug.debugfs_phy, ar,
			    &fops_ani_enable);

	अगर (IS_ENABLED(CONFIG_ATH10K_DFS_CERTIFIED)) अणु
		debugfs_create_file("dfs_simulate_radar", 0200, ar->debug.debugfs_phy,
				    ar, &fops_simulate_radar);

		debugfs_create_bool("dfs_block_radar_events", 0200,
				    ar->debug.debugfs_phy,
				    &ar->dfs_block_radar_events);

		debugfs_create_file("dfs_stats", 0400, ar->debug.debugfs_phy, ar,
				    &fops_dfs_stats);
	पूर्ण

	debugfs_create_file("pktlog_filter", 0644, ar->debug.debugfs_phy, ar,
			    &fops_pktlog_filter);

	अगर (test_bit(WMI_SERVICE_THERM_THROT, ar->wmi.svc_map))
		debugfs_create_file("quiet_period", 0644, ar->debug.debugfs_phy, ar,
				    &fops_quiet_period);

	debugfs_create_file("tpc_stats", 0400, ar->debug.debugfs_phy, ar,
			    &fops_tpc_stats);

	अगर (test_bit(WMI_SERVICE_COEX_GPIO, ar->wmi.svc_map))
		debugfs_create_file("btcoex", 0644, ar->debug.debugfs_phy, ar,
				    &fops_btcoex);

	अगर (test_bit(WMI_SERVICE_PEER_STATS, ar->wmi.svc_map)) अणु
		debugfs_create_file("peer_stats", 0644, ar->debug.debugfs_phy, ar,
				    &fops_peer_stats);

		debugfs_create_file("enable_extd_tx_stats", 0644,
				    ar->debug.debugfs_phy, ar,
				    &fops_enable_extd_tx_stats);
	पूर्ण

	debugfs_create_file("fw_checksums", 0400, ar->debug.debugfs_phy, ar,
			    &fops_fw_checksums);

	अगर (IS_ENABLED(CONFIG_MAC80211_DEBUGFS))
		debugfs_create_file("sta_tid_stats_mask", 0600,
				    ar->debug.debugfs_phy,
				    ar, &fops_sta_tid_stats_mask);

	अगर (test_bit(WMI_SERVICE_TPC_STATS_FINAL, ar->wmi.svc_map))
		debugfs_create_file("tpc_stats_final", 0400,
				    ar->debug.debugfs_phy, ar,
				    &fops_tpc_stats_final);

	अगर (test_bit(WMI_SERVICE_RESET_CHIP, ar->wmi.svc_map))
		debugfs_create_file("warm_hw_reset", 0600,
				    ar->debug.debugfs_phy, ar,
				    &fops_warm_hw_reset);

	debugfs_create_file("ps_state_enable", 0600, ar->debug.debugfs_phy, ar,
			    &fops_ps_state_enable);

	debugfs_create_file("reset_htt_stats", 0200, ar->debug.debugfs_phy, ar,
			    &fops_reset_htt_stats);

	वापस 0;
पूर्ण

व्योम ath10k_debug_unरेजिस्टर(काष्ठा ath10k *ar)
अणु
	cancel_delayed_work_sync(&ar->debug.htt_stats_dwork);
पूर्ण

#पूर्ण_अगर /* CONFIG_ATH10K_DEBUGFS */

#अगर_घोषित CONFIG_ATH10K_DEBUG
व्योम __ath10k_dbg(काष्ठा ath10k *ar, क्रमागत ath10k_debug_mask mask,
		  स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	अगर (ath10k_debug_mask & mask)
		dev_prपूर्णांकk(KERN_DEBUG, ar->dev, "%pV", &vaf);

	trace_ath10k_log_dbg(ar, mask, &vaf);

	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(__ath10k_dbg);

व्योम ath10k_dbg_dump(काष्ठा ath10k *ar,
		     क्रमागत ath10k_debug_mask mask,
		     स्थिर अक्षर *msg, स्थिर अक्षर *prefix,
		     स्थिर व्योम *buf, माप_प्रकार len)
अणु
	अक्षर linebuf[256];
	माप_प्रकार linebuflen;
	स्थिर व्योम *ptr;

	अगर (ath10k_debug_mask & mask) अणु
		अगर (msg)
			__ath10k_dbg(ar, mask, "%s\n", msg);

		क्रम (ptr = buf; (ptr - buf) < len; ptr += 16) अणु
			linebuflen = 0;
			linebuflen += scnम_लिखो(linebuf + linebuflen,
						माप(linebuf) - linebuflen,
						"%s%08x: ",
						(prefix ? prefix : ""),
						(अचिन्हित पूर्णांक)(ptr - buf));
			hex_dump_to_buffer(ptr, len - (ptr - buf), 16, 1,
					   linebuf + linebuflen,
					   माप(linebuf) - linebuflen, true);
			dev_prपूर्णांकk(KERN_DEBUG, ar->dev, "%s\n", linebuf);
		पूर्ण
	पूर्ण

	/* tracing code करोesn't like null strings :/ */
	trace_ath10k_log_dbg_dump(ar, msg ? msg : "", prefix ? prefix : "",
				  buf, len);
पूर्ण
EXPORT_SYMBOL(ath10k_dbg_dump);

#पूर्ण_अगर /* CONFIG_ATH10K_DEBUG */
