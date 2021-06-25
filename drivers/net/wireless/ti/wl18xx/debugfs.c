<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl18xx
 *
 * Copyright (C) 2009 Nokia Corporation
 * Copyright (C) 2011-2012 Texas Instruments
 */

#समावेश <linux/pm_runसमय.स>

#समावेश "../wlcore/debugfs.h"
#समावेश "../wlcore/wlcore.h"
#समावेश "../wlcore/debug.h"
#समावेश "../wlcore/ps.h"

#समावेश "wl18xx.h"
#समावेश "acx.h"
#समावेश "cmd.h"
#समावेश "debugfs.h"

#घोषणा WL18XX_DEBUGFS_FWSTATS_खाता(a, b, c) \
	DEBUGFS_FWSTATS_खाता(a, b, c, wl18xx_acx_statistics)
#घोषणा WL18XX_DEBUGFS_FWSTATS_खाता_ARRAY(a, b, c) \
	DEBUGFS_FWSTATS_खाता_ARRAY(a, b, c, wl18xx_acx_statistics)


WL18XX_DEBUGFS_FWSTATS_खाता(error, error_frame_non_ctrl, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(error, error_frame_ctrl, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(error, error_frame_during_protection, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(error, null_frame_tx_start, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(error, null_frame_cts_start, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(error, bar_retry, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(error, num_frame_cts_nul_flid, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(error, tx_पात_failure, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(error, tx_resume_failure, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(error, rx_cmplt_db_overflow_cnt, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(error, elp_जबतक_rx_exch, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(error, elp_जबतक_tx_exch, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(error, elp_जबतक_tx, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(error, elp_जबतक_nvic_pending, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(error, rx_excessive_frame_len, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(error, burst_mismatch, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(error, tbc_exch_mismatch, "%u");

WL18XX_DEBUGFS_FWSTATS_खाता(tx, tx_prepared_descs, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(tx, tx_cmplt, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(tx, tx_ढाँचा_prepared, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(tx, tx_data_prepared, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(tx, tx_ढाँचा_programmed, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(tx, tx_data_programmed, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(tx, tx_burst_programmed, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(tx, tx_starts, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(tx, tx_stop, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(tx, tx_start_ढाँचाs, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(tx, tx_start_पूर्णांक_ढाँचाs, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(tx, tx_start_fw_gen, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(tx, tx_start_data, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(tx, tx_start_null_frame, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(tx, tx_exch, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(tx, tx_retry_ढाँचा, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(tx, tx_retry_data, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता_ARRAY(tx, tx_retry_per_rate,
				  NUM_OF_RATES_INDEXES);
WL18XX_DEBUGFS_FWSTATS_खाता(tx, tx_exch_pending, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(tx, tx_exch_expiry, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(tx, tx_करोne_ढाँचा, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(tx, tx_करोne_data, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(tx, tx_करोne_पूर्णांक_ढाँचा, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(tx, tx_cfe1, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(tx, tx_cfe2, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(tx, frag_called, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(tx, frag_mpdu_alloc_failed, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(tx, frag_init_called, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(tx, frag_in_process_called, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(tx, frag_tkip_called, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(tx, frag_key_not_found, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(tx, frag_need_fragmentation, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(tx, frag_bad_mblk_num, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(tx, frag_failed, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(tx, frag_cache_hit, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(tx, frag_cache_miss, "%u");

WL18XX_DEBUGFS_FWSTATS_खाता(rx, rx_beacon_early_term, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(rx, rx_out_of_mpdu_nodes, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(rx, rx_hdr_overflow, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(rx, rx_dropped_frame, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(rx, rx_करोne, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(rx, rx_defrag, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(rx, rx_defrag_end, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(rx, rx_cmplt, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(rx, rx_pre_complt, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(rx, rx_cmplt_task, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(rx, rx_phy_hdr, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(rx, rx_समयout, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(rx, rx_rts_समयout, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(rx, rx_समयout_wa, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(rx, defrag_called, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(rx, defrag_init_called, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(rx, defrag_in_process_called, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(rx, defrag_tkip_called, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(rx, defrag_need_defrag, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(rx, defrag_decrypt_failed, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(rx, decrypt_key_not_found, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(rx, defrag_need_decrypt, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(rx, rx_tkip_replays, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(rx, rx_xfr, "%u");

WL18XX_DEBUGFS_FWSTATS_खाता(isr, irqs, "%u");

WL18XX_DEBUGFS_FWSTATS_खाता(pwr, missing_bcns_cnt, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(pwr, rcvd_bcns_cnt, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(pwr, connection_out_of_sync, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता_ARRAY(pwr, cont_miss_bcns_spपढ़ो,
				  PWR_STAT_MAX_CONT_MISSED_BCNS_SPREAD);
WL18XX_DEBUGFS_FWSTATS_खाता(pwr, rcvd_awake_bcns_cnt, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(pwr, sleep_समय_count, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(pwr, sleep_समय_avg, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(pwr, sleep_cycle_avg, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(pwr, sleep_percent, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(pwr, ap_sleep_active_conf, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(pwr, ap_sleep_user_conf, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(pwr, ap_sleep_counter, "%u");

WL18XX_DEBUGFS_FWSTATS_खाता(rx_filter, beacon_filter, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(rx_filter, arp_filter, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(rx_filter, mc_filter, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(rx_filter, dup_filter, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(rx_filter, data_filter, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(rx_filter, ibss_filter, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(rx_filter, protection_filter, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(rx_filter, accum_arp_pend_requests, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(rx_filter, max_arp_queue_dep, "%u");

WL18XX_DEBUGFS_FWSTATS_खाता_ARRAY(rx_rate, rx_frames_per_rates, 50);

WL18XX_DEBUGFS_FWSTATS_खाता_ARRAY(aggr_size, tx_agg_rate,
				  AGGR_STATS_TX_AGG);
WL18XX_DEBUGFS_FWSTATS_खाता_ARRAY(aggr_size, tx_agg_len,
				  AGGR_STATS_TX_AGG);
WL18XX_DEBUGFS_FWSTATS_खाता_ARRAY(aggr_size, rx_size,
				  AGGR_STATS_RX_SIZE_LEN);

WL18XX_DEBUGFS_FWSTATS_खाता(pipeline, hs_tx_stat_fअगरo_पूर्णांक, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(pipeline, enc_tx_stat_fअगरo_पूर्णांक, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(pipeline, enc_rx_stat_fअगरo_पूर्णांक, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(pipeline, rx_complete_stat_fअगरo_पूर्णांक, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(pipeline, pre_proc_swi, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(pipeline, post_proc_swi, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(pipeline, sec_frag_swi, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(pipeline, pre_to_defrag_swi, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(pipeline, defrag_to_rx_xfer_swi, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(pipeline, dec_packet_in, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(pipeline, dec_packet_in_fअगरo_full, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(pipeline, dec_packet_out, "%u");

WL18XX_DEBUGFS_FWSTATS_खाता_ARRAY(pipeline, pipeline_fअगरo_full,
				  PIPE_STATS_HW_FIFO);

WL18XX_DEBUGFS_FWSTATS_खाता_ARRAY(भागersity, num_of_packets_per_ant,
				  DIVERSITY_STATS_NUM_OF_ANT);
WL18XX_DEBUGFS_FWSTATS_खाता(भागersity, total_num_of_toggles, "%u");

WL18XX_DEBUGFS_FWSTATS_खाता(thermal, irq_thr_low, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(thermal, irq_thr_high, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(thermal, tx_stop, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(thermal, tx_resume, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(thermal, false_irq, "%u");
WL18XX_DEBUGFS_FWSTATS_खाता(thermal, adc_source_unexpected, "%u");

WL18XX_DEBUGFS_FWSTATS_खाता_ARRAY(calib, fail_count,
				  WL18XX_NUM_OF_CALIBRATIONS_ERRORS);
WL18XX_DEBUGFS_FWSTATS_खाता(calib, calib_count, "%u");

WL18XX_DEBUGFS_FWSTATS_खाता(roaming, rssi_level, "%d");

WL18XX_DEBUGFS_FWSTATS_खाता(dfs, num_of_radar_detections, "%d");

अटल sमाप_प्रकार conf_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
			 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1271 *wl = file->निजी_data;
	काष्ठा wl18xx_priv *priv = wl->priv;
	काष्ठा wlcore_conf_header header;
	अक्षर *buf, *pos;
	माप_प्रकार len;
	पूर्णांक ret;

	len = WL18XX_CONF_SIZE;
	buf = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	header.magic	= cpu_to_le32(WL18XX_CONF_MAGIC);
	header.version	= cpu_to_le32(WL18XX_CONF_VERSION);
	header.checksum	= 0;

	mutex_lock(&wl->mutex);

	pos = buf;
	स_नकल(pos, &header, माप(header));
	pos += माप(header);
	स_नकल(pos, &wl->conf, माप(wl->conf));
	pos += माप(wl->conf);
	स_नकल(pos, &priv->conf, माप(priv->conf));

	mutex_unlock(&wl->mutex);

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);

	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations conf_ops = अणु
	.पढ़ो = conf_पढ़ो,
	.खोलो = simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार clear_fw_stats_ग_लिखो(काष्ठा file *file,
			      स्थिर अक्षर __user *user_buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1271 *wl = file->निजी_data;
	पूर्णांक ret;

	mutex_lock(&wl->mutex);

	अगर (unlikely(wl->state != WLCORE_STATE_ON))
		जाओ out;

	ret = wl18xx_acx_clear_statistics(wl);
	अगर (ret < 0) अणु
		count = ret;
		जाओ out;
	पूर्ण
out:
	mutex_unlock(&wl->mutex);
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations clear_fw_stats_ops = अणु
	.ग_लिखो = clear_fw_stats_ग_लिखो,
	.खोलो = simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार radar_detection_ग_लिखो(काष्ठा file *file,
				     स्थिर अक्षर __user *user_buf,
				     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1271 *wl = file->निजी_data;
	पूर्णांक ret;
	u8 channel;

	ret = kstrtou8_from_user(user_buf, count, 10, &channel);
	अगर (ret < 0) अणु
		wl1271_warning("illegal channel");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&wl->mutex);

	अगर (unlikely(wl->state != WLCORE_STATE_ON))
		जाओ out;

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	ret = wl18xx_cmd_radar_detection_debug(wl, channel);
	अगर (ret < 0)
		count = ret;

	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);
out:
	mutex_unlock(&wl->mutex);
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations radar_detection_ops = अणु
	.ग_लिखो = radar_detection_ग_लिखो,
	.खोलो = simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार dynamic_fw_traces_ग_लिखो(काष्ठा file *file,
					स्थिर अक्षर __user *user_buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1271 *wl = file->निजी_data;
	अचिन्हित दीर्घ value;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ_from_user(user_buf, count, 0, &value);
	अगर (ret < 0)
		वापस ret;

	mutex_lock(&wl->mutex);

	wl->dynamic_fw_traces = value;

	अगर (unlikely(wl->state != WLCORE_STATE_ON))
		जाओ out;

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	ret = wl18xx_acx_dynamic_fw_traces(wl);
	अगर (ret < 0)
		count = ret;

	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);
out:
	mutex_unlock(&wl->mutex);
	वापस count;
पूर्ण

अटल sमाप_प्रकार dynamic_fw_traces_पढ़ो(काष्ठा file *file,
					अक्षर __user *userbuf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1271 *wl = file->निजी_data;
	वापस wl1271_क्रमmat_buffer(userbuf, count, ppos,
				    "%d\n", wl->dynamic_fw_traces);
पूर्ण

अटल स्थिर काष्ठा file_operations dynamic_fw_traces_ops = अणु
	.पढ़ो = dynamic_fw_traces_पढ़ो,
	.ग_लिखो = dynamic_fw_traces_ग_लिखो,
	.खोलो = simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;

#अगर_घोषित CONFIG_CFG80211_CERTIFICATION_ONUS
अटल sमाप_प्रकार radar_debug_mode_ग_लिखो(काष्ठा file *file,
				      स्थिर अक्षर __user *user_buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1271 *wl = file->निजी_data;
	काष्ठा wl12xx_vअगर *wlvअगर;
	अचिन्हित दीर्घ value;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ_from_user(user_buf, count, 10, &value);
	अगर (ret < 0) अणु
		wl1271_warning("illegal radar_debug_mode value!");
		वापस -EINVAL;
	पूर्ण

	/* valid values: 0/1 */
	अगर (!(value == 0 || value == 1)) अणु
		wl1271_warning("value is not in valid!");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&wl->mutex);

	wl->radar_debug_mode = value;

	अगर (unlikely(wl->state != WLCORE_STATE_ON))
		जाओ out;

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	wl12xx_क्रम_each_wlvअगर_ap(wl, wlvअगर) अणु
		wlcore_cmd_generic_cfg(wl, wlvअगर,
				       WLCORE_CFG_FEATURE_RADAR_DEBUG,
				       wl->radar_debug_mode, 0);
	पूर्ण

	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);
out:
	mutex_unlock(&wl->mutex);
	वापस count;
पूर्ण

अटल sमाप_प्रकार radar_debug_mode_पढ़ो(काष्ठा file *file,
				     अक्षर __user *userbuf,
				     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1271 *wl = file->निजी_data;

	वापस wl1271_क्रमmat_buffer(userbuf, count, ppos,
				    "%d\n", wl->radar_debug_mode);
पूर्ण

अटल स्थिर काष्ठा file_operations radar_debug_mode_ops = अणु
	.ग_लिखो = radar_debug_mode_ग_लिखो,
	.पढ़ो = radar_debug_mode_पढ़ो,
	.खोलो = simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;
#पूर्ण_अगर /* CFG80211_CERTIFICATION_ONUS */

पूर्णांक wl18xx_debugfs_add_files(काष्ठा wl1271 *wl,
			     काष्ठा dentry *rootdir)
अणु
	काष्ठा dentry *stats, *moddir;

	moddir = debugfs_create_dir(KBUILD_MODNAME, rootdir);
	stats = debugfs_create_dir("fw_stats", moddir);

	DEBUGFS_ADD(clear_fw_stats, stats);

	DEBUGFS_FWSTATS_ADD(error, error_frame_non_ctrl);
	DEBUGFS_FWSTATS_ADD(error, error_frame_ctrl);
	DEBUGFS_FWSTATS_ADD(error, error_frame_during_protection);
	DEBUGFS_FWSTATS_ADD(error, null_frame_tx_start);
	DEBUGFS_FWSTATS_ADD(error, null_frame_cts_start);
	DEBUGFS_FWSTATS_ADD(error, bar_retry);
	DEBUGFS_FWSTATS_ADD(error, num_frame_cts_nul_flid);
	DEBUGFS_FWSTATS_ADD(error, tx_पात_failure);
	DEBUGFS_FWSTATS_ADD(error, tx_resume_failure);
	DEBUGFS_FWSTATS_ADD(error, rx_cmplt_db_overflow_cnt);
	DEBUGFS_FWSTATS_ADD(error, elp_जबतक_rx_exch);
	DEBUGFS_FWSTATS_ADD(error, elp_जबतक_tx_exch);
	DEBUGFS_FWSTATS_ADD(error, elp_जबतक_tx);
	DEBUGFS_FWSTATS_ADD(error, elp_जबतक_nvic_pending);
	DEBUGFS_FWSTATS_ADD(error, rx_excessive_frame_len);
	DEBUGFS_FWSTATS_ADD(error, burst_mismatch);
	DEBUGFS_FWSTATS_ADD(error, tbc_exch_mismatch);

	DEBUGFS_FWSTATS_ADD(tx, tx_prepared_descs);
	DEBUGFS_FWSTATS_ADD(tx, tx_cmplt);
	DEBUGFS_FWSTATS_ADD(tx, tx_ढाँचा_prepared);
	DEBUGFS_FWSTATS_ADD(tx, tx_data_prepared);
	DEBUGFS_FWSTATS_ADD(tx, tx_ढाँचा_programmed);
	DEBUGFS_FWSTATS_ADD(tx, tx_data_programmed);
	DEBUGFS_FWSTATS_ADD(tx, tx_burst_programmed);
	DEBUGFS_FWSTATS_ADD(tx, tx_starts);
	DEBUGFS_FWSTATS_ADD(tx, tx_stop);
	DEBUGFS_FWSTATS_ADD(tx, tx_start_ढाँचाs);
	DEBUGFS_FWSTATS_ADD(tx, tx_start_पूर्णांक_ढाँचाs);
	DEBUGFS_FWSTATS_ADD(tx, tx_start_fw_gen);
	DEBUGFS_FWSTATS_ADD(tx, tx_start_data);
	DEBUGFS_FWSTATS_ADD(tx, tx_start_null_frame);
	DEBUGFS_FWSTATS_ADD(tx, tx_exch);
	DEBUGFS_FWSTATS_ADD(tx, tx_retry_ढाँचा);
	DEBUGFS_FWSTATS_ADD(tx, tx_retry_data);
	DEBUGFS_FWSTATS_ADD(tx, tx_retry_per_rate);
	DEBUGFS_FWSTATS_ADD(tx, tx_exch_pending);
	DEBUGFS_FWSTATS_ADD(tx, tx_exch_expiry);
	DEBUGFS_FWSTATS_ADD(tx, tx_करोne_ढाँचा);
	DEBUGFS_FWSTATS_ADD(tx, tx_करोne_data);
	DEBUGFS_FWSTATS_ADD(tx, tx_करोne_पूर्णांक_ढाँचा);
	DEBUGFS_FWSTATS_ADD(tx, tx_cfe1);
	DEBUGFS_FWSTATS_ADD(tx, tx_cfe2);
	DEBUGFS_FWSTATS_ADD(tx, frag_called);
	DEBUGFS_FWSTATS_ADD(tx, frag_mpdu_alloc_failed);
	DEBUGFS_FWSTATS_ADD(tx, frag_init_called);
	DEBUGFS_FWSTATS_ADD(tx, frag_in_process_called);
	DEBUGFS_FWSTATS_ADD(tx, frag_tkip_called);
	DEBUGFS_FWSTATS_ADD(tx, frag_key_not_found);
	DEBUGFS_FWSTATS_ADD(tx, frag_need_fragmentation);
	DEBUGFS_FWSTATS_ADD(tx, frag_bad_mblk_num);
	DEBUGFS_FWSTATS_ADD(tx, frag_failed);
	DEBUGFS_FWSTATS_ADD(tx, frag_cache_hit);
	DEBUGFS_FWSTATS_ADD(tx, frag_cache_miss);

	DEBUGFS_FWSTATS_ADD(rx, rx_beacon_early_term);
	DEBUGFS_FWSTATS_ADD(rx, rx_out_of_mpdu_nodes);
	DEBUGFS_FWSTATS_ADD(rx, rx_hdr_overflow);
	DEBUGFS_FWSTATS_ADD(rx, rx_dropped_frame);
	DEBUGFS_FWSTATS_ADD(rx, rx_करोne);
	DEBUGFS_FWSTATS_ADD(rx, rx_defrag);
	DEBUGFS_FWSTATS_ADD(rx, rx_defrag_end);
	DEBUGFS_FWSTATS_ADD(rx, rx_cmplt);
	DEBUGFS_FWSTATS_ADD(rx, rx_pre_complt);
	DEBUGFS_FWSTATS_ADD(rx, rx_cmplt_task);
	DEBUGFS_FWSTATS_ADD(rx, rx_phy_hdr);
	DEBUGFS_FWSTATS_ADD(rx, rx_समयout);
	DEBUGFS_FWSTATS_ADD(rx, rx_rts_समयout);
	DEBUGFS_FWSTATS_ADD(rx, rx_समयout_wa);
	DEBUGFS_FWSTATS_ADD(rx, defrag_called);
	DEBUGFS_FWSTATS_ADD(rx, defrag_init_called);
	DEBUGFS_FWSTATS_ADD(rx, defrag_in_process_called);
	DEBUGFS_FWSTATS_ADD(rx, defrag_tkip_called);
	DEBUGFS_FWSTATS_ADD(rx, defrag_need_defrag);
	DEBUGFS_FWSTATS_ADD(rx, defrag_decrypt_failed);
	DEBUGFS_FWSTATS_ADD(rx, decrypt_key_not_found);
	DEBUGFS_FWSTATS_ADD(rx, defrag_need_decrypt);
	DEBUGFS_FWSTATS_ADD(rx, rx_tkip_replays);
	DEBUGFS_FWSTATS_ADD(rx, rx_xfr);

	DEBUGFS_FWSTATS_ADD(isr, irqs);

	DEBUGFS_FWSTATS_ADD(pwr, missing_bcns_cnt);
	DEBUGFS_FWSTATS_ADD(pwr, rcvd_bcns_cnt);
	DEBUGFS_FWSTATS_ADD(pwr, connection_out_of_sync);
	DEBUGFS_FWSTATS_ADD(pwr, cont_miss_bcns_spपढ़ो);
	DEBUGFS_FWSTATS_ADD(pwr, rcvd_awake_bcns_cnt);
	DEBUGFS_FWSTATS_ADD(pwr, sleep_समय_count);
	DEBUGFS_FWSTATS_ADD(pwr, sleep_समय_avg);
	DEBUGFS_FWSTATS_ADD(pwr, sleep_cycle_avg);
	DEBUGFS_FWSTATS_ADD(pwr, sleep_percent);
	DEBUGFS_FWSTATS_ADD(pwr, ap_sleep_active_conf);
	DEBUGFS_FWSTATS_ADD(pwr, ap_sleep_user_conf);
	DEBUGFS_FWSTATS_ADD(pwr, ap_sleep_counter);

	DEBUGFS_FWSTATS_ADD(rx_filter, beacon_filter);
	DEBUGFS_FWSTATS_ADD(rx_filter, arp_filter);
	DEBUGFS_FWSTATS_ADD(rx_filter, mc_filter);
	DEBUGFS_FWSTATS_ADD(rx_filter, dup_filter);
	DEBUGFS_FWSTATS_ADD(rx_filter, data_filter);
	DEBUGFS_FWSTATS_ADD(rx_filter, ibss_filter);
	DEBUGFS_FWSTATS_ADD(rx_filter, protection_filter);
	DEBUGFS_FWSTATS_ADD(rx_filter, accum_arp_pend_requests);
	DEBUGFS_FWSTATS_ADD(rx_filter, max_arp_queue_dep);

	DEBUGFS_FWSTATS_ADD(rx_rate, rx_frames_per_rates);

	DEBUGFS_FWSTATS_ADD(aggr_size, tx_agg_rate);
	DEBUGFS_FWSTATS_ADD(aggr_size, tx_agg_len);
	DEBUGFS_FWSTATS_ADD(aggr_size, rx_size);

	DEBUGFS_FWSTATS_ADD(pipeline, hs_tx_stat_fअगरo_पूर्णांक);
	DEBUGFS_FWSTATS_ADD(pipeline, enc_tx_stat_fअगरo_पूर्णांक);
	DEBUGFS_FWSTATS_ADD(pipeline, enc_rx_stat_fअगरo_पूर्णांक);
	DEBUGFS_FWSTATS_ADD(pipeline, rx_complete_stat_fअगरo_पूर्णांक);
	DEBUGFS_FWSTATS_ADD(pipeline, pre_proc_swi);
	DEBUGFS_FWSTATS_ADD(pipeline, post_proc_swi);
	DEBUGFS_FWSTATS_ADD(pipeline, sec_frag_swi);
	DEBUGFS_FWSTATS_ADD(pipeline, pre_to_defrag_swi);
	DEBUGFS_FWSTATS_ADD(pipeline, defrag_to_rx_xfer_swi);
	DEBUGFS_FWSTATS_ADD(pipeline, dec_packet_in);
	DEBUGFS_FWSTATS_ADD(pipeline, dec_packet_in_fअगरo_full);
	DEBUGFS_FWSTATS_ADD(pipeline, dec_packet_out);
	DEBUGFS_FWSTATS_ADD(pipeline, pipeline_fअगरo_full);

	DEBUGFS_FWSTATS_ADD(भागersity, num_of_packets_per_ant);
	DEBUGFS_FWSTATS_ADD(भागersity, total_num_of_toggles);

	DEBUGFS_FWSTATS_ADD(thermal, irq_thr_low);
	DEBUGFS_FWSTATS_ADD(thermal, irq_thr_high);
	DEBUGFS_FWSTATS_ADD(thermal, tx_stop);
	DEBUGFS_FWSTATS_ADD(thermal, tx_resume);
	DEBUGFS_FWSTATS_ADD(thermal, false_irq);
	DEBUGFS_FWSTATS_ADD(thermal, adc_source_unexpected);

	DEBUGFS_FWSTATS_ADD(calib, fail_count);

	DEBUGFS_FWSTATS_ADD(calib, calib_count);

	DEBUGFS_FWSTATS_ADD(roaming, rssi_level);

	DEBUGFS_FWSTATS_ADD(dfs, num_of_radar_detections);

	DEBUGFS_ADD(conf, moddir);
	DEBUGFS_ADD(radar_detection, moddir);
#अगर_घोषित CONFIG_CFG80211_CERTIFICATION_ONUS
	DEBUGFS_ADD(radar_debug_mode, moddir);
#पूर्ण_अगर
	DEBUGFS_ADD(dynamic_fw_traces, moddir);

	वापस 0;
पूर्ण
