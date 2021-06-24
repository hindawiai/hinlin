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

#समावेश "common.h"
#समावेश "3945.h"

अटल पूर्णांक
il3945_stats_flag(काष्ठा il_priv *il, अक्षर *buf, पूर्णांक bufsz)
अणु
	पूर्णांक p = 0;

	p += scnम_लिखो(buf + p, bufsz - p, "Statistics Flag(0x%X):\n",
		       le32_to_cpu(il->_3945.stats.flag));
	अगर (le32_to_cpu(il->_3945.stats.flag) & UCODE_STATS_CLEAR_MSK)
		p += scnम_लिखो(buf + p, bufsz - p,
			       "\tStatistics have been cleared\n");
	p += scnम_लिखो(buf + p, bufsz - p, "\tOperational Frequency: %s\n",
		       (le32_to_cpu(il->_3945.stats.flag) &
			UCODE_STATS_FREQUENCY_MSK) ? "2.4 GHz" : "5.2 GHz");
	p += scnम_लिखो(buf + p, bufsz - p, "\tTGj Narrow Band: %s\n",
		       (le32_to_cpu(il->_3945.stats.flag) &
			UCODE_STATS_NARROW_BAND_MSK) ? "enabled" : "disabled");
	वापस p;
पूर्ण

अटल sमाप_प्रकार
il3945_ucode_rx_stats_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
			   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा il_priv *il = file->निजी_data;
	पूर्णांक pos = 0;
	अक्षर *buf;
	पूर्णांक bufsz =
	    माप(काष्ठा iwl39_stats_rx_phy) * 40 +
	    माप(काष्ठा iwl39_stats_rx_non_phy) * 40 + 400;
	sमाप_प्रकार ret;
	काष्ठा iwl39_stats_rx_phy *ofdm, *accum_ofdm, *delta_ofdm, *max_ofdm;
	काष्ठा iwl39_stats_rx_phy *cck, *accum_cck, *delta_cck, *max_cck;
	काष्ठा iwl39_stats_rx_non_phy *general, *accum_general;
	काष्ठा iwl39_stats_rx_non_phy *delta_general, *max_general;

	अगर (!il_is_alive(il))
		वापस -EAGAIN;

	buf = kzalloc(bufsz, GFP_KERNEL);
	अगर (!buf) अणु
		IL_ERR("Can not allocate Buffer\n");
		वापस -ENOMEM;
	पूर्ण

	/*
	 * The statistic inक्रमmation display here is based on
	 * the last stats notअगरication from uCode
	 * might not reflect the current uCode activity
	 */
	ofdm = &il->_3945.stats.rx.ofdm;
	cck = &il->_3945.stats.rx.cck;
	general = &il->_3945.stats.rx.general;
	accum_ofdm = &il->_3945.accum_stats.rx.ofdm;
	accum_cck = &il->_3945.accum_stats.rx.cck;
	accum_general = &il->_3945.accum_stats.rx.general;
	delta_ofdm = &il->_3945.delta_stats.rx.ofdm;
	delta_cck = &il->_3945.delta_stats.rx.cck;
	delta_general = &il->_3945.delta_stats.rx.general;
	max_ofdm = &il->_3945.max_delta.rx.ofdm;
	max_cck = &il->_3945.max_delta.rx.cck;
	max_general = &il->_3945.max_delta.rx.general;

	pos += il3945_stats_flag(il, buf, bufsz);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "%-32s     current"
		      "accumulative      delta         max\n",
		      "Statistics_Rx - OFDM:");
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "ina_cnt:",
		      le32_to_cpu(ofdm->ina_cnt), accum_ofdm->ina_cnt,
		      delta_ofdm->ina_cnt, max_ofdm->ina_cnt);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "fina_cnt:",
		      le32_to_cpu(ofdm->fina_cnt), accum_ofdm->fina_cnt,
		      delta_ofdm->fina_cnt, max_ofdm->fina_cnt);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "plcp_err:",
		      le32_to_cpu(ofdm->plcp_err), accum_ofdm->plcp_err,
		      delta_ofdm->plcp_err, max_ofdm->plcp_err);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "crc32_err:",
		      le32_to_cpu(ofdm->crc32_err), accum_ofdm->crc32_err,
		      delta_ofdm->crc32_err, max_ofdm->crc32_err);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "overrun_err:",
		      le32_to_cpu(ofdm->overrun_err), accum_ofdm->overrun_err,
		      delta_ofdm->overrun_err, max_ofdm->overrun_err);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "early_overrun_err:",
		      le32_to_cpu(ofdm->early_overrun_err),
		      accum_ofdm->early_overrun_err,
		      delta_ofdm->early_overrun_err,
		      max_ofdm->early_overrun_err);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "crc32_good:",
		      le32_to_cpu(ofdm->crc32_good), accum_ofdm->crc32_good,
		      delta_ofdm->crc32_good, max_ofdm->crc32_good);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "false_alarm_cnt:",
		      le32_to_cpu(ofdm->false_alarm_cnt),
		      accum_ofdm->false_alarm_cnt, delta_ofdm->false_alarm_cnt,
		      max_ofdm->false_alarm_cnt);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "fina_sync_err_cnt:",
		      le32_to_cpu(ofdm->fina_sync_err_cnt),
		      accum_ofdm->fina_sync_err_cnt,
		      delta_ofdm->fina_sync_err_cnt,
		      max_ofdm->fina_sync_err_cnt);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "sfd_timeout:",
		      le32_to_cpu(ofdm->sfd_समयout), accum_ofdm->sfd_समयout,
		      delta_ofdm->sfd_समयout, max_ofdm->sfd_समयout);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "fina_timeout:",
		      le32_to_cpu(ofdm->fina_समयout), accum_ofdm->fina_समयout,
		      delta_ofdm->fina_समयout, max_ofdm->fina_समयout);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "unresponded_rts:",
		      le32_to_cpu(ofdm->unresponded_rts),
		      accum_ofdm->unresponded_rts, delta_ofdm->unresponded_rts,
		      max_ofdm->unresponded_rts);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n",
		      "rxe_frame_lmt_ovrun:",
		      le32_to_cpu(ofdm->rxe_frame_limit_overrun),
		      accum_ofdm->rxe_frame_limit_overrun,
		      delta_ofdm->rxe_frame_limit_overrun,
		      max_ofdm->rxe_frame_limit_overrun);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "sent_ack_cnt:",
		      le32_to_cpu(ofdm->sent_ack_cnt), accum_ofdm->sent_ack_cnt,
		      delta_ofdm->sent_ack_cnt, max_ofdm->sent_ack_cnt);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "sent_cts_cnt:",
		      le32_to_cpu(ofdm->sent_cts_cnt), accum_ofdm->sent_cts_cnt,
		      delta_ofdm->sent_cts_cnt, max_ofdm->sent_cts_cnt);

	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "%-32s     current"
		      "accumulative      delta         max\n",
		      "Statistics_Rx - CCK:");
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "ina_cnt:",
		      le32_to_cpu(cck->ina_cnt), accum_cck->ina_cnt,
		      delta_cck->ina_cnt, max_cck->ina_cnt);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "fina_cnt:",
		      le32_to_cpu(cck->fina_cnt), accum_cck->fina_cnt,
		      delta_cck->fina_cnt, max_cck->fina_cnt);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "plcp_err:",
		      le32_to_cpu(cck->plcp_err), accum_cck->plcp_err,
		      delta_cck->plcp_err, max_cck->plcp_err);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "crc32_err:",
		      le32_to_cpu(cck->crc32_err), accum_cck->crc32_err,
		      delta_cck->crc32_err, max_cck->crc32_err);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "overrun_err:",
		      le32_to_cpu(cck->overrun_err), accum_cck->overrun_err,
		      delta_cck->overrun_err, max_cck->overrun_err);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "early_overrun_err:",
		      le32_to_cpu(cck->early_overrun_err),
		      accum_cck->early_overrun_err,
		      delta_cck->early_overrun_err, max_cck->early_overrun_err);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "crc32_good:",
		      le32_to_cpu(cck->crc32_good), accum_cck->crc32_good,
		      delta_cck->crc32_good, max_cck->crc32_good);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "false_alarm_cnt:",
		      le32_to_cpu(cck->false_alarm_cnt),
		      accum_cck->false_alarm_cnt, delta_cck->false_alarm_cnt,
		      max_cck->false_alarm_cnt);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "fina_sync_err_cnt:",
		      le32_to_cpu(cck->fina_sync_err_cnt),
		      accum_cck->fina_sync_err_cnt,
		      delta_cck->fina_sync_err_cnt, max_cck->fina_sync_err_cnt);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "sfd_timeout:",
		      le32_to_cpu(cck->sfd_समयout), accum_cck->sfd_समयout,
		      delta_cck->sfd_समयout, max_cck->sfd_समयout);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "fina_timeout:",
		      le32_to_cpu(cck->fina_समयout), accum_cck->fina_समयout,
		      delta_cck->fina_समयout, max_cck->fina_समयout);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "unresponded_rts:",
		      le32_to_cpu(cck->unresponded_rts),
		      accum_cck->unresponded_rts, delta_cck->unresponded_rts,
		      max_cck->unresponded_rts);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n",
		      "rxe_frame_lmt_ovrun:",
		      le32_to_cpu(cck->rxe_frame_limit_overrun),
		      accum_cck->rxe_frame_limit_overrun,
		      delta_cck->rxe_frame_limit_overrun,
		      max_cck->rxe_frame_limit_overrun);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "sent_ack_cnt:",
		      le32_to_cpu(cck->sent_ack_cnt), accum_cck->sent_ack_cnt,
		      delta_cck->sent_ack_cnt, max_cck->sent_ack_cnt);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "sent_cts_cnt:",
		      le32_to_cpu(cck->sent_cts_cnt), accum_cck->sent_cts_cnt,
		      delta_cck->sent_cts_cnt, max_cck->sent_cts_cnt);

	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "%-32s     current"
		      "accumulative      delta         max\n",
		      "Statistics_Rx - GENERAL:");
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "bogus_cts:",
		      le32_to_cpu(general->bogus_cts), accum_general->bogus_cts,
		      delta_general->bogus_cts, max_general->bogus_cts);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "bogus_ack:",
		      le32_to_cpu(general->bogus_ack), accum_general->bogus_ack,
		      delta_general->bogus_ack, max_general->bogus_ack);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "non_bssid_frames:",
		      le32_to_cpu(general->non_bssid_frames),
		      accum_general->non_bssid_frames,
		      delta_general->non_bssid_frames,
		      max_general->non_bssid_frames);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "filtered_frames:",
		      le32_to_cpu(general->filtered_frames),
		      accum_general->filtered_frames,
		      delta_general->filtered_frames,
		      max_general->filtered_frames);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n",
		      "non_channel_beacons:",
		      le32_to_cpu(general->non_channel_beacons),
		      accum_general->non_channel_beacons,
		      delta_general->non_channel_beacons,
		      max_general->non_channel_beacons);

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार
il3945_ucode_tx_stats_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
			   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा il_priv *il = file->निजी_data;
	पूर्णांक pos = 0;
	अक्षर *buf;
	पूर्णांक bufsz = (माप(काष्ठा iwl39_stats_tx) * 48) + 250;
	sमाप_प्रकार ret;
	काष्ठा iwl39_stats_tx *tx, *accum_tx, *delta_tx, *max_tx;

	अगर (!il_is_alive(il))
		वापस -EAGAIN;

	buf = kzalloc(bufsz, GFP_KERNEL);
	अगर (!buf) अणु
		IL_ERR("Can not allocate Buffer\n");
		वापस -ENOMEM;
	पूर्ण

	/*
	 * The statistic inक्रमmation display here is based on
	 * the last stats notअगरication from uCode
	 * might not reflect the current uCode activity
	 */
	tx = &il->_3945.stats.tx;
	accum_tx = &il->_3945.accum_stats.tx;
	delta_tx = &il->_3945.delta_stats.tx;
	max_tx = &il->_3945.max_delta.tx;
	pos += il3945_stats_flag(il, buf, bufsz);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "%-32s     current"
		      "accumulative      delta         max\n",
		      "Statistics_Tx:");
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "preamble:",
		      le32_to_cpu(tx->preamble_cnt), accum_tx->preamble_cnt,
		      delta_tx->preamble_cnt, max_tx->preamble_cnt);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "rx_detected_cnt:",
		      le32_to_cpu(tx->rx_detected_cnt),
		      accum_tx->rx_detected_cnt, delta_tx->rx_detected_cnt,
		      max_tx->rx_detected_cnt);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "bt_prio_defer_cnt:",
		      le32_to_cpu(tx->bt_prio_defer_cnt),
		      accum_tx->bt_prio_defer_cnt, delta_tx->bt_prio_defer_cnt,
		      max_tx->bt_prio_defer_cnt);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "bt_prio_kill_cnt:",
		      le32_to_cpu(tx->bt_prio_समाप्त_cnt),
		      accum_tx->bt_prio_समाप्त_cnt, delta_tx->bt_prio_समाप्त_cnt,
		      max_tx->bt_prio_समाप्त_cnt);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "few_bytes_cnt:",
		      le32_to_cpu(tx->few_bytes_cnt), accum_tx->few_bytes_cnt,
		      delta_tx->few_bytes_cnt, max_tx->few_bytes_cnt);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "cts_timeout:",
		      le32_to_cpu(tx->cts_समयout), accum_tx->cts_समयout,
		      delta_tx->cts_समयout, max_tx->cts_समयout);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "ack_timeout:",
		      le32_to_cpu(tx->ack_समयout), accum_tx->ack_समयout,
		      delta_tx->ack_समयout, max_tx->ack_समयout);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "expected_ack_cnt:",
		      le32_to_cpu(tx->expected_ack_cnt),
		      accum_tx->expected_ack_cnt, delta_tx->expected_ack_cnt,
		      max_tx->expected_ack_cnt);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "actual_ack_cnt:",
		      le32_to_cpu(tx->actual_ack_cnt), accum_tx->actual_ack_cnt,
		      delta_tx->actual_ack_cnt, max_tx->actual_ack_cnt);

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार
il3945_ucode_general_stats_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा il_priv *il = file->निजी_data;
	पूर्णांक pos = 0;
	अक्षर *buf;
	पूर्णांक bufsz = माप(काष्ठा iwl39_stats_general) * 10 + 300;
	sमाप_प्रकार ret;
	काष्ठा iwl39_stats_general *general, *accum_general;
	काष्ठा iwl39_stats_general *delta_general, *max_general;
	काष्ठा stats_dbg *dbg, *accum_dbg, *delta_dbg, *max_dbg;
	काष्ठा iwl39_stats_भाग *भाग, *accum_भाग, *delta_भाग, *max_भाग;

	अगर (!il_is_alive(il))
		वापस -EAGAIN;

	buf = kzalloc(bufsz, GFP_KERNEL);
	अगर (!buf) अणु
		IL_ERR("Can not allocate Buffer\n");
		वापस -ENOMEM;
	पूर्ण

	/*
	 * The statistic inक्रमmation display here is based on
	 * the last stats notअगरication from uCode
	 * might not reflect the current uCode activity
	 */
	general = &il->_3945.stats.general;
	dbg = &il->_3945.stats.general.dbg;
	भाग = &il->_3945.stats.general.भाग;
	accum_general = &il->_3945.accum_stats.general;
	delta_general = &il->_3945.delta_stats.general;
	max_general = &il->_3945.max_delta.general;
	accum_dbg = &il->_3945.accum_stats.general.dbg;
	delta_dbg = &il->_3945.delta_stats.general.dbg;
	max_dbg = &il->_3945.max_delta.general.dbg;
	accum_भाग = &il->_3945.accum_stats.general.भाग;
	delta_भाग = &il->_3945.delta_stats.general.भाग;
	max_भाग = &il->_3945.max_delta.general.भाग;
	pos += il3945_stats_flag(il, buf, bufsz);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "%-32s     current"
		      "accumulative      delta         max\n",
		      "Statistics_General:");
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "burst_check:",
		      le32_to_cpu(dbg->burst_check), accum_dbg->burst_check,
		      delta_dbg->burst_check, max_dbg->burst_check);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "burst_count:",
		      le32_to_cpu(dbg->burst_count), accum_dbg->burst_count,
		      delta_dbg->burst_count, max_dbg->burst_count);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "sleep_time:",
		      le32_to_cpu(general->sleep_समय),
		      accum_general->sleep_समय, delta_general->sleep_समय,
		      max_general->sleep_समय);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "slots_out:",
		      le32_to_cpu(general->slots_out), accum_general->slots_out,
		      delta_general->slots_out, max_general->slots_out);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "slots_idle:",
		      le32_to_cpu(general->slots_idle),
		      accum_general->slots_idle, delta_general->slots_idle,
		      max_general->slots_idle);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos, "ttl_timestamp:\t\t\t%u\n",
		      le32_to_cpu(general->ttl_बारtamp));
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "tx_on_a:",
		      le32_to_cpu(भाग->tx_on_a), accum_भाग->tx_on_a,
		      delta_भाग->tx_on_a, max_भाग->tx_on_a);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "tx_on_b:",
		      le32_to_cpu(भाग->tx_on_b), accum_भाग->tx_on_b,
		      delta_भाग->tx_on_b, max_भाग->tx_on_b);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "exec_time:",
		      le32_to_cpu(भाग->exec_समय), accum_भाग->exec_समय,
		      delta_भाग->exec_समय, max_भाग->exec_समय);
	pos +=
	    scnम_लिखो(buf + pos, bufsz - pos,
		      "  %-30s %10u  %10u  %10u  %10u\n", "probe_time:",
		      le32_to_cpu(भाग->probe_समय), accum_भाग->probe_समय,
		      delta_भाग->probe_समय, max_भाग->probe_समय);
	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
	kमुक्त(buf);
	वापस ret;
पूर्ण

स्थिर काष्ठा il_debugfs_ops il3945_debugfs_ops = अणु
	.rx_stats_पढ़ो = il3945_ucode_rx_stats_पढ़ो,
	.tx_stats_पढ़ो = il3945_ucode_tx_stats_पढ़ो,
	.general_stats_पढ़ो = il3945_ucode_general_stats_पढ़ो,
पूर्ण;
