<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
 *
 * Copyright(c) 2008 - 2014 Intel Corporation. All rights reserved.
 * Copyright(c) 2018        Intel Corporation
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <linuxwअगरi@पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *****************************************************************************/
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/etherdevice.h>
#समावेश <net/mac80211.h>

#समावेश "dev.h"
#समावेश "agn.h"

/* For active scan, listen ACTIVE_DWELL_TIME (msec) on each channel after
 * sending probe req.  This should be set दीर्घ enough to hear probe responses
 * from more than one AP.  */
#घोषणा IWL_ACTIVE_DWELL_TIME_24    (30)       /* all बार in msec */
#घोषणा IWL_ACTIVE_DWELL_TIME_52    (20)

#घोषणा IWL_ACTIVE_DWELL_FACTOR_24GHZ (3)
#घोषणा IWL_ACTIVE_DWELL_FACTOR_52GHZ (2)

/* For passive scan, listen PASSIVE_DWELL_TIME (msec) on each channel.
 * Must be set दीर्घer than active dwell समय.
 * For the most reliable scan, set > AP beacon पूर्णांकerval (typically 100msec). */
#घोषणा IWL_PASSIVE_DWELL_TIME_24   (20)       /* all बार in msec */
#घोषणा IWL_PASSIVE_DWELL_TIME_52   (10)
#घोषणा IWL_PASSIVE_DWELL_BASE      (100)
#घोषणा IWL_CHANNEL_TUNE_TIME       5
#घोषणा MAX_SCAN_CHANNEL	    50

/* For reset radio, need minimal dwell समय only */
#घोषणा IWL_RADIO_RESET_DWELL_TIME	5

अटल पूर्णांक iwl_send_scan_पात(काष्ठा iwl_priv *priv)
अणु
	पूर्णांक ret;
	काष्ठा iwl_host_cmd cmd = अणु
		.id = REPLY_SCAN_ABORT_CMD,
		.flags = CMD_WANT_SKB,
	पूर्ण;
	__le32 *status;

	/* Exit instantly with error when device is not पढ़ोy
	 * to receive scan पात command or it करोes not perक्रमm
	 * hardware scan currently */
	अगर (!test_bit(STATUS_READY, &priv->status) ||
	    !test_bit(STATUS_SCAN_HW, &priv->status) ||
	    test_bit(STATUS_FW_ERROR, &priv->status))
		वापस -EIO;

	ret = iwl_dvm_send_cmd(priv, &cmd);
	अगर (ret)
		वापस ret;

	status = (व्योम *)cmd.resp_pkt->data;
	अगर (*status != CAN_ABORT_STATUS) अणु
		/* The scan पात will वापस 1 क्रम success or
		 * 2 क्रम "failure".  A failure condition can be
		 * due to simply not being in an active scan which
		 * can occur अगर we send the scan पात beक्रमe we
		 * the microcode has notअगरied us that a scan is
		 * completed. */
		IWL_DEBUG_SCAN(priv, "SCAN_ABORT ret %d.\n",
			       le32_to_cpu(*status));
		ret = -EIO;
	पूर्ण

	iwl_मुक्त_resp(&cmd);
	वापस ret;
पूर्ण

अटल व्योम iwl_complete_scan(काष्ठा iwl_priv *priv, bool पातed)
अणु
	काष्ठा cfg80211_scan_info info = अणु
		.पातed = पातed,
	पूर्ण;

	/* check अगर scan was requested from mac80211 */
	अगर (priv->scan_request) अणु
		IWL_DEBUG_SCAN(priv, "Complete scan in mac80211\n");
		ieee80211_scan_completed(priv->hw, &info);
	पूर्ण

	priv->scan_type = IWL_SCAN_NORMAL;
	priv->scan_vअगर = शून्य;
	priv->scan_request = शून्य;
पूर्ण

अटल व्योम iwl_process_scan_complete(काष्ठा iwl_priv *priv)
अणु
	bool पातed;

	lockdep_निश्चित_held(&priv->mutex);

	अगर (!test_and_clear_bit(STATUS_SCAN_COMPLETE, &priv->status))
		वापस;

	IWL_DEBUG_SCAN(priv, "Completed scan.\n");

	cancel_delayed_work(&priv->scan_check);

	पातed = test_and_clear_bit(STATUS_SCAN_ABORTING, &priv->status);
	अगर (पातed)
		IWL_DEBUG_SCAN(priv, "Aborted scan completed.\n");

	अगर (!test_and_clear_bit(STATUS_SCANNING, &priv->status)) अणु
		IWL_DEBUG_SCAN(priv, "Scan already completed.\n");
		जाओ out_settings;
	पूर्ण

	अगर (priv->scan_type != IWL_SCAN_NORMAL && !पातed) अणु
		पूर्णांक err;

		/* Check अगर mac80211 requested scan during our पूर्णांकernal scan */
		अगर (priv->scan_request == शून्य)
			जाओ out_complete;

		/* If so request a new scan */
		err = iwl_scan_initiate(priv, priv->scan_vअगर, IWL_SCAN_NORMAL,
					priv->scan_request->channels[0]->band);
		अगर (err) अणु
			IWL_DEBUG_SCAN(priv,
				"failed to initiate pending scan: %d\n", err);
			पातed = true;
			जाओ out_complete;
		पूर्ण

		वापस;
	पूर्ण

out_complete:
	iwl_complete_scan(priv, पातed);

out_settings:
	/* Can we still talk to firmware ? */
	अगर (!iwl_is_पढ़ोy_rf(priv))
		वापस;

	iwlagn_post_scan(priv);
पूर्ण

व्योम iwl_क्रमce_scan_end(काष्ठा iwl_priv *priv)
अणु
	lockdep_निश्चित_held(&priv->mutex);

	अगर (!test_bit(STATUS_SCANNING, &priv->status)) अणु
		IWL_DEBUG_SCAN(priv, "Forcing scan end while not scanning\n");
		वापस;
	पूर्ण

	IWL_DEBUG_SCAN(priv, "Forcing scan end\n");
	clear_bit(STATUS_SCANNING, &priv->status);
	clear_bit(STATUS_SCAN_HW, &priv->status);
	clear_bit(STATUS_SCAN_ABORTING, &priv->status);
	clear_bit(STATUS_SCAN_COMPLETE, &priv->status);
	iwl_complete_scan(priv, true);
पूर्ण

अटल व्योम iwl_करो_scan_पात(काष्ठा iwl_priv *priv)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&priv->mutex);

	अगर (!test_bit(STATUS_SCANNING, &priv->status)) अणु
		IWL_DEBUG_SCAN(priv, "Not performing scan to abort\n");
		वापस;
	पूर्ण

	अगर (test_and_set_bit(STATUS_SCAN_ABORTING, &priv->status)) अणु
		IWL_DEBUG_SCAN(priv, "Scan abort in progress\n");
		वापस;
	पूर्ण

	ret = iwl_send_scan_पात(priv);
	अगर (ret) अणु
		IWL_DEBUG_SCAN(priv, "Send scan abort failed %d\n", ret);
		iwl_क्रमce_scan_end(priv);
	पूर्ण अन्यथा
		IWL_DEBUG_SCAN(priv, "Successfully send scan abort\n");
पूर्ण

/*
 * iwl_scan_cancel - Cancel any currently executing HW scan
 */
पूर्णांक iwl_scan_cancel(काष्ठा iwl_priv *priv)
अणु
	IWL_DEBUG_SCAN(priv, "Queuing abort scan\n");
	queue_work(priv->workqueue, &priv->पात_scan);
	वापस 0;
पूर्ण

/*
 * iwl_scan_cancel_समयout - Cancel any currently executing HW scan
 * @ms: amount of समय to रुको (in milliseconds) क्रम scan to पात
 */
व्योम iwl_scan_cancel_समयout(काष्ठा iwl_priv *priv, अचिन्हित दीर्घ ms)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(ms);

	lockdep_निश्चित_held(&priv->mutex);

	IWL_DEBUG_SCAN(priv, "Scan cancel timeout\n");

	iwl_करो_scan_पात(priv);

	जबतक (समय_beक्रमe_eq(jअगरfies, समयout)) अणु
		अगर (!test_bit(STATUS_SCAN_HW, &priv->status))
			जाओ finished;
		msleep(20);
	पूर्ण

	वापस;

 finished:
	/*
	 * Now STATUS_SCAN_HW is clear. This means that the
	 * device finished, but the background work is going
	 * to execute at best as soon as we release the mutex.
	 * Since we need to be able to issue a new scan right
	 * after this function वापसs, run the complete here.
	 * The STATUS_SCAN_COMPLETE bit will then be cleared
	 * and prevent the background work from "completing"
	 * a possible new scan.
	 */
	iwl_process_scan_complete(priv);
पूर्ण

/* Service response to REPLY_SCAN_CMD (0x80) */
अटल व्योम iwl_rx_reply_scan(काष्ठा iwl_priv *priv,
			      काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
#अगर_घोषित CONFIG_IWLWIFI_DEBUG
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_scanreq_notअगरication *notअगर = (व्योम *)pkt->data;

	IWL_DEBUG_SCAN(priv, "Scan request status = 0x%x\n", notअगर->status);
#पूर्ण_अगर
पूर्ण

/* Service SCAN_START_NOTIFICATION (0x82) */
अटल व्योम iwl_rx_scan_start_notअगर(काष्ठा iwl_priv *priv,
				    काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_scanstart_notअगरication *notअगर = (व्योम *)pkt->data;

	priv->scan_start_tsf = le32_to_cpu(notअगर->tsf_low);
	IWL_DEBUG_SCAN(priv, "Scan start: "
		       "%d [802.11%s] "
		       "(TSF: 0x%08X:%08X) - %d (beacon timer %u)\n",
		       notअगर->channel,
		       notअगर->band ? "bg" : "a",
		       le32_to_cpu(notअगर->tsf_high),
		       le32_to_cpu(notअगर->tsf_low),
		       notअगर->status, notअगर->beacon_समयr);
पूर्ण

/* Service SCAN_RESULTS_NOTIFICATION (0x83) */
अटल व्योम iwl_rx_scan_results_notअगर(काष्ठा iwl_priv *priv,
				      काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
#अगर_घोषित CONFIG_IWLWIFI_DEBUG
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_scanresults_notअगरication *notअगर = (व्योम *)pkt->data;

	IWL_DEBUG_SCAN(priv, "Scan ch.res: "
		       "%d [802.11%s] "
		       "probe status: %u:%u "
		       "(TSF: 0x%08X:%08X) - %d "
		       "elapsed=%lu usec\n",
		       notअगर->channel,
		       notअगर->band ? "bg" : "a",
		       notअगर->probe_status, notअगर->num_probe_not_sent,
		       le32_to_cpu(notअगर->tsf_high),
		       le32_to_cpu(notअगर->tsf_low),
		       le32_to_cpu(notअगर->statistics[0]),
		       le32_to_cpu(notअगर->tsf_low) - priv->scan_start_tsf);
#पूर्ण_अगर
पूर्ण

/* Service SCAN_COMPLETE_NOTIFICATION (0x84) */
अटल व्योम iwl_rx_scan_complete_notअगर(काष्ठा iwl_priv *priv,
				       काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_scancomplete_notअगरication *scan_notअगर = (व्योम *)pkt->data;

	IWL_DEBUG_SCAN(priv, "Scan complete: %d channels (TSF 0x%08X:%08X) - %d\n",
		       scan_notअगर->scanned_channels,
		       scan_notअगर->tsf_low,
		       scan_notअगर->tsf_high, scan_notअगर->status);

	IWL_DEBUG_SCAN(priv, "Scan on %sGHz took %dms\n",
		       (priv->scan_band == NL80211_BAND_2GHZ) ? "2.4" : "5.2",
		       jअगरfies_to_msecs(jअगरfies - priv->scan_start));

	/*
	 * When पातing, we run the scan completed background work अंतरभूत
	 * and the background work must then करो nothing. The SCAN_COMPLETE
	 * bit helps implement that logic and thus needs to be set beक्रमe
	 * queueing the work. Also, since the scan पात रुकोs क्रम SCAN_HW
	 * to clear, we need to set SCAN_COMPLETE beक्रमe clearing SCAN_HW
	 * to aव्योम a race there.
	 */
	set_bit(STATUS_SCAN_COMPLETE, &priv->status);
	clear_bit(STATUS_SCAN_HW, &priv->status);
	queue_work(priv->workqueue, &priv->scan_completed);

	अगर (priv->iw_mode != NL80211_IFTYPE_ADHOC &&
	    iwl_advanced_bt_coexist(priv) &&
	    priv->bt_status != scan_notअगर->bt_status) अणु
		अगर (scan_notअगर->bt_status) अणु
			/* BT on */
			अगर (!priv->bt_ch_announce)
				priv->bt_traffic_load =
					IWL_BT_COEX_TRAFFIC_LOAD_HIGH;
			/*
			 * otherwise, no traffic load inक्रमmation provided
			 * no changes made
			 */
		पूर्ण अन्यथा अणु
			/* BT off */
			priv->bt_traffic_load =
				IWL_BT_COEX_TRAFFIC_LOAD_NONE;
		पूर्ण
		priv->bt_status = scan_notअगर->bt_status;
		queue_work(priv->workqueue,
			   &priv->bt_traffic_change_work);
	पूर्ण
पूर्ण

व्योम iwl_setup_rx_scan_handlers(काष्ठा iwl_priv *priv)
अणु
	/* scan handlers */
	priv->rx_handlers[REPLY_SCAN_CMD] = iwl_rx_reply_scan;
	priv->rx_handlers[SCAN_START_NOTIFICATION] = iwl_rx_scan_start_notअगर;
	priv->rx_handlers[SCAN_RESULTS_NOTIFICATION] =
					iwl_rx_scan_results_notअगर;
	priv->rx_handlers[SCAN_COMPLETE_NOTIFICATION] =
					iwl_rx_scan_complete_notअगर;
पूर्ण

अटल u16 iwl_get_active_dwell_समय(काष्ठा iwl_priv *priv,
				     क्रमागत nl80211_band band, u8 n_probes)
अणु
	अगर (band == NL80211_BAND_5GHZ)
		वापस IWL_ACTIVE_DWELL_TIME_52 +
			IWL_ACTIVE_DWELL_FACTOR_52GHZ * (n_probes + 1);
	अन्यथा
		वापस IWL_ACTIVE_DWELL_TIME_24 +
			IWL_ACTIVE_DWELL_FACTOR_24GHZ * (n_probes + 1);
पूर्ण

अटल u16 iwl_limit_dwell(काष्ठा iwl_priv *priv, u16 dwell_समय)
अणु
	काष्ठा iwl_rxon_context *ctx;
	पूर्णांक limits[NUM_IWL_RXON_CTX] = अणुपूर्ण;
	पूर्णांक n_active = 0;
	u16 limit;

	BUILD_BUG_ON(NUM_IWL_RXON_CTX != 2);

	/*
	 * If we're associated, we clamp the dwell समय 98%
	 * of the beacon पूर्णांकerval (minus 2 * channel tune समय)
	 * If both contexts are active, we have to restrict to
	 * 1/2 of the minimum of them, because they might be in
	 * lock-step with the समय inbetween only half of what
	 * समय we'd have in each of them.
	 */
	क्रम_each_context(priv, ctx) अणु
		चयन (ctx->staging.dev_type) अणु
		हाल RXON_DEV_TYPE_P2P:
			/* no timing स्थिरraपूर्णांकs */
			जारी;
		हाल RXON_DEV_TYPE_ESS:
		शेष:
			/* timing स्थिरraपूर्णांकs अगर associated */
			अगर (!iwl_is_associated_ctx(ctx))
				जारी;
			अवरोध;
		हाल RXON_DEV_TYPE_CP:
		हाल RXON_DEV_TYPE_2STA:
			/*
			 * These seem to always have समयrs क्रम TBTT
			 * active in uCode even when not associated yet.
			 */
			अवरोध;
		पूर्ण

		limits[n_active++] = ctx->beacon_पूर्णांक ?: IWL_PASSIVE_DWELL_BASE;
	पूर्ण

	चयन (n_active) अणु
	हाल 0:
		वापस dwell_समय;
	हाल 2:
		limit = (limits[1] * 98) / 100 - IWL_CHANNEL_TUNE_TIME * 2;
		limit /= 2;
		dwell_समय = min(limit, dwell_समय);
		fallthrough;
	हाल 1:
		limit = (limits[0] * 98) / 100 - IWL_CHANNEL_TUNE_TIME * 2;
		limit /= n_active;
		वापस min(limit, dwell_समय);
	शेष:
		WARN_ON_ONCE(1);
		वापस dwell_समय;
	पूर्ण
पूर्ण

अटल u16 iwl_get_passive_dwell_समय(काष्ठा iwl_priv *priv,
				      क्रमागत nl80211_band band)
अणु
	u16 passive = (band == NL80211_BAND_2GHZ) ?
	    IWL_PASSIVE_DWELL_BASE + IWL_PASSIVE_DWELL_TIME_24 :
	    IWL_PASSIVE_DWELL_BASE + IWL_PASSIVE_DWELL_TIME_52;

	वापस iwl_limit_dwell(priv, passive);
पूर्ण

/* Return valid, unused, channel क्रम a passive scan to reset the RF */
अटल u8 iwl_get_single_channel_number(काष्ठा iwl_priv *priv,
					क्रमागत nl80211_band band)
अणु
	काष्ठा ieee80211_supported_band *sband = priv->hw->wiphy->bands[band];
	काष्ठा iwl_rxon_context *ctx;
	पूर्णांक i;

	क्रम (i = 0; i < sband->n_channels; i++) अणु
		bool busy = false;

		क्रम_each_context(priv, ctx) अणु
			busy = sband->channels[i].hw_value ==
				le16_to_cpu(ctx->staging.channel);
			अगर (busy)
				अवरोध;
		पूर्ण

		अगर (busy)
			जारी;

		अगर (!(sband->channels[i].flags & IEEE80211_CHAN_DISABLED))
			वापस sband->channels[i].hw_value;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iwl_get_channel_क्रम_reset_scan(काष्ठा iwl_priv *priv,
					  काष्ठा ieee80211_vअगर *vअगर,
					  क्रमागत nl80211_band band,
					  काष्ठा iwl_scan_channel *scan_ch)
अणु
	स्थिर काष्ठा ieee80211_supported_band *sband;
	u16 channel;

	sband = iwl_get_hw_mode(priv, band);
	अगर (!sband) अणु
		IWL_ERR(priv, "invalid band\n");
		वापस 0;
	पूर्ण

	channel = iwl_get_single_channel_number(priv, band);
	अगर (channel) अणु
		scan_ch->channel = cpu_to_le16(channel);
		scan_ch->type = SCAN_CHANNEL_TYPE_PASSIVE;
		scan_ch->active_dwell =
			cpu_to_le16(IWL_RADIO_RESET_DWELL_TIME);
		scan_ch->passive_dwell =
			cpu_to_le16(IWL_RADIO_RESET_DWELL_TIME);
		/* Set txघातer levels to शेषs */
		scan_ch->dsp_atten = 110;
		अगर (band == NL80211_BAND_5GHZ)
			scan_ch->tx_gain = ((1 << 5) | (3 << 3)) | 3;
		अन्यथा
			scan_ch->tx_gain = ((1 << 5) | (5 << 3));
		वापस 1;
	पूर्ण

	IWL_ERR(priv, "no valid channel found\n");
	वापस 0;
पूर्ण

अटल पूर्णांक iwl_get_channels_क्रम_scan(काष्ठा iwl_priv *priv,
				     काष्ठा ieee80211_vअगर *vअगर,
				     क्रमागत nl80211_band band,
				     u8 is_active, u8 n_probes,
				     काष्ठा iwl_scan_channel *scan_ch)
अणु
	काष्ठा ieee80211_channel *chan;
	स्थिर काष्ठा ieee80211_supported_band *sband;
	u16 passive_dwell = 0;
	u16 active_dwell = 0;
	पूर्णांक added, i;
	u16 channel;

	sband = iwl_get_hw_mode(priv, band);
	अगर (!sband)
		वापस 0;

	active_dwell = iwl_get_active_dwell_समय(priv, band, n_probes);
	passive_dwell = iwl_get_passive_dwell_समय(priv, band);

	अगर (passive_dwell <= active_dwell)
		passive_dwell = active_dwell + 1;

	क्रम (i = 0, added = 0; i < priv->scan_request->n_channels; i++) अणु
		chan = priv->scan_request->channels[i];

		अगर (chan->band != band)
			जारी;

		channel = chan->hw_value;
		scan_ch->channel = cpu_to_le16(channel);

		अगर (!is_active || (chan->flags & IEEE80211_CHAN_NO_IR))
			scan_ch->type = SCAN_CHANNEL_TYPE_PASSIVE;
		अन्यथा
			scan_ch->type = SCAN_CHANNEL_TYPE_ACTIVE;

		अगर (n_probes)
			scan_ch->type |= IWL_SCAN_PROBE_MASK(n_probes);

		scan_ch->active_dwell = cpu_to_le16(active_dwell);
		scan_ch->passive_dwell = cpu_to_le16(passive_dwell);

		/* Set txघातer levels to शेषs */
		scan_ch->dsp_atten = 110;

		/* NOTE: अगर we were करोing 6Mb OFDM क्रम scans we'd use
		 * घातer level:
		 * scan_ch->tx_gain = ((1 << 5) | (2 << 3)) | 3;
		 */
		अगर (band == NL80211_BAND_5GHZ)
			scan_ch->tx_gain = ((1 << 5) | (3 << 3)) | 3;
		अन्यथा
			scan_ch->tx_gain = ((1 << 5) | (5 << 3));

		IWL_DEBUG_SCAN(priv, "Scanning ch=%d prob=0x%X [%s %d]\n",
			       channel, le32_to_cpu(scan_ch->type),
			       (scan_ch->type & SCAN_CHANNEL_TYPE_ACTIVE) ?
				"ACTIVE" : "PASSIVE",
			       (scan_ch->type & SCAN_CHANNEL_TYPE_ACTIVE) ?
			       active_dwell : passive_dwell);

		scan_ch++;
		added++;
	पूर्ण

	IWL_DEBUG_SCAN(priv, "total channels to scan %d\n", added);
	वापस added;
पूर्ण

/*
 * iwl_fill_probe_req - fill in all required fields and IE क्रम probe request
 */
अटल u16 iwl_fill_probe_req(काष्ठा ieee80211_mgmt *frame, स्थिर u8 *ta,
			      स्थिर u8 *ies, पूर्णांक ie_len, स्थिर u8 *ssid,
			      u8 ssid_len, पूर्णांक left)
अणु
	पूर्णांक len = 0;
	u8 *pos = शून्य;

	/* Make sure there is enough space क्रम the probe request,
	 * two mandatory IEs and the data */
	left -= 24;
	अगर (left < 0)
		वापस 0;

	frame->frame_control = cpu_to_le16(IEEE80211_STYPE_PROBE_REQ);
	eth_broadcast_addr(frame->da);
	स_नकल(frame->sa, ta, ETH_ALEN);
	eth_broadcast_addr(frame->bssid);
	frame->seq_ctrl = 0;

	len += 24;

	/* ...next IE... */
	pos = &frame->u.probe_req.variable[0];

	/* fill in our SSID IE */
	left -= ssid_len + 2;
	अगर (left < 0)
		वापस 0;
	*pos++ = WLAN_EID_SSID;
	*pos++ = ssid_len;
	अगर (ssid && ssid_len) अणु
		स_नकल(pos, ssid, ssid_len);
		pos += ssid_len;
	पूर्ण

	len += ssid_len + 2;

	अगर (WARN_ON(left < ie_len))
		वापस len;

	अगर (ies && ie_len) अणु
		स_नकल(pos, ies, ie_len);
		len += ie_len;
	पूर्ण

	वापस (u16)len;
पूर्ण

अटल पूर्णांक iwlagn_request_scan(काष्ठा iwl_priv *priv, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_host_cmd cmd = अणु
		.id = REPLY_SCAN_CMD,
		.len = अणु माप(काष्ठा iwl_scan_cmd), पूर्ण,
	पूर्ण;
	काष्ठा iwl_scan_cmd *scan;
	काष्ठा iwl_rxon_context *ctx = &priv->contexts[IWL_RXON_CTX_BSS];
	u32 rate_flags = 0;
	u16 cmd_len = 0;
	u16 rx_chain = 0;
	क्रमागत nl80211_band band;
	u8 n_probes = 0;
	u8 rx_ant = priv->nvm_data->valid_rx_ant;
	u8 rate;
	bool is_active = false;
	पूर्णांक  chan_mod;
	u8 active_chains;
	u8 scan_tx_antennas = priv->nvm_data->valid_tx_ant;
	पूर्णांक ret;
	पूर्णांक scan_cmd_size = माप(काष्ठा iwl_scan_cmd) +
			    MAX_SCAN_CHANNEL * माप(काष्ठा iwl_scan_channel) +
			    priv->fw->ucode_capa.max_probe_length;
	स्थिर u8 *ssid = शून्य;
	u8 ssid_len = 0;

	अगर (WARN_ON(priv->scan_type == IWL_SCAN_NORMAL &&
		    (!priv->scan_request ||
		     priv->scan_request->n_channels > MAX_SCAN_CHANNEL)))
		वापस -EINVAL;

	lockdep_निश्चित_held(&priv->mutex);

	अगर (vअगर)
		ctx = iwl_rxon_ctx_from_vअगर(vअगर);

	अगर (!priv->scan_cmd) अणु
		priv->scan_cmd = kदो_स्मृति(scan_cmd_size, GFP_KERNEL);
		अगर (!priv->scan_cmd) अणु
			IWL_DEBUG_SCAN(priv,
				       "fail to allocate memory for scan\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	scan = priv->scan_cmd;
	स_रखो(scan, 0, scan_cmd_size);

	scan->quiet_plcp_th = IWL_PLCP_QUIET_THRESH;
	scan->quiet_समय = IWL_ACTIVE_QUIET_TIME;

	अगर (iwl_is_any_associated(priv)) अणु
		u16 पूर्णांकerval = 0;
		u32 extra;
		u32 suspend_समय = 100;
		u32 scan_suspend_समय = 100;

		IWL_DEBUG_INFO(priv, "Scanning while associated...\n");
		चयन (priv->scan_type) अणु
		हाल IWL_SCAN_RADIO_RESET:
			पूर्णांकerval = 0;
			अवरोध;
		हाल IWL_SCAN_NORMAL:
			पूर्णांकerval = vअगर->bss_conf.beacon_पूर्णांक;
			अवरोध;
		पूर्ण

		scan->suspend_समय = 0;
		scan->max_out_समय = cpu_to_le32(200 * 1024);
		अगर (!पूर्णांकerval)
			पूर्णांकerval = suspend_समय;

		extra = (suspend_समय / पूर्णांकerval) << 22;
		scan_suspend_समय = (extra |
		    ((suspend_समय % पूर्णांकerval) * 1024));
		scan->suspend_समय = cpu_to_le32(scan_suspend_समय);
		IWL_DEBUG_SCAN(priv, "suspend_time 0x%X beacon interval %d\n",
			       scan_suspend_समय, पूर्णांकerval);
	पूर्ण

	चयन (priv->scan_type) अणु
	हाल IWL_SCAN_RADIO_RESET:
		IWL_DEBUG_SCAN(priv, "Start internal passive scan.\n");
		/*
		 * Override quiet समय as firmware checks that active
		 * dwell is >= quiet; since we use passive scan it'll
		 * not actually be used.
		 */
		scan->quiet_समय = cpu_to_le16(IWL_RADIO_RESET_DWELL_TIME);
		अवरोध;
	हाल IWL_SCAN_NORMAL:
		अगर (priv->scan_request->n_ssids) अणु
			पूर्णांक i, p = 0;
			IWL_DEBUG_SCAN(priv, "Kicking off active scan\n");
			/*
			 * The highest priority SSID is inserted to the
			 * probe request ढाँचा.
			 */
			ssid_len = priv->scan_request->ssids[0].ssid_len;
			ssid = priv->scan_request->ssids[0].ssid;

			/*
			 * Invert the order of ssids, the firmware will invert
			 * it back.
			 */
			क्रम (i = priv->scan_request->n_ssids - 1; i >= 1; i--) अणु
				scan->direct_scan[p].id = WLAN_EID_SSID;
				scan->direct_scan[p].len =
					priv->scan_request->ssids[i].ssid_len;
				स_नकल(scan->direct_scan[p].ssid,
				       priv->scan_request->ssids[i].ssid,
				       priv->scan_request->ssids[i].ssid_len);
				n_probes++;
				p++;
			पूर्ण
			is_active = true;
		पूर्ण अन्यथा
			IWL_DEBUG_SCAN(priv, "Start passive scan.\n");
		अवरोध;
	पूर्ण

	scan->tx_cmd.tx_flags = TX_CMD_FLG_SEQ_CTL_MSK;
	scan->tx_cmd.sta_id = ctx->bcast_sta_id;
	scan->tx_cmd.stop_समय.lअगरe_समय = TX_CMD_LIFE_TIME_INFINITE;

	चयन (priv->scan_band) अणु
	हाल NL80211_BAND_2GHZ:
		scan->flags = RXON_FLG_BAND_24G_MSK | RXON_FLG_AUTO_DETECT_MSK;
		chan_mod = le32_to_cpu(
			priv->contexts[IWL_RXON_CTX_BSS].active.flags &
						RXON_FLG_CHANNEL_MODE_MSK)
				       >> RXON_FLG_CHANNEL_MODE_POS;
		अगर ((priv->scan_request && priv->scan_request->no_cck) ||
		    chan_mod == CHANNEL_MODE_PURE_40) अणु
			rate = IWL_RATE_6M_PLCP;
		पूर्ण अन्यथा अणु
			rate = IWL_RATE_1M_PLCP;
			rate_flags = RATE_MCS_CCK_MSK;
		पूर्ण
		/*
		 * Internal scans are passive, so we can indiscriminately set
		 * the BT ignore flag on 2.4 GHz since it applies to TX only.
		 */
		अगर (priv->lib->bt_params &&
		    priv->lib->bt_params->advanced_bt_coexist)
			scan->tx_cmd.tx_flags |= TX_CMD_FLG_IGNORE_BT;
		अवरोध;
	हाल NL80211_BAND_5GHZ:
		rate = IWL_RATE_6M_PLCP;
		अवरोध;
	शेष:
		IWL_WARN(priv, "Invalid scan band\n");
		वापस -EIO;
	पूर्ण

	/*
	 * If active scanning is requested but a certain channel is
	 * marked passive, we can करो active scanning अगर we detect
	 * transmissions.
	 *
	 * There is an issue with some firmware versions that triggers
	 * a sysनिश्चित on a "good CRC threshold" of zero (== disabled),
	 * on a radar channel even though this means that we should NOT
	 * send probes.
	 *
	 * The "good CRC threshold" is the number of frames that we
	 * need to receive during our dwell समय on a channel beक्रमe
	 * sending out probes -- setting this to a huge value will
	 * mean we never reach it, but at the same समय work around
	 * the aक्रमementioned issue. Thus use IWL_GOOD_CRC_TH_NEVER
	 * here instead of IWL_GOOD_CRC_TH_DISABLED.
	 *
	 * This was fixed in later versions aदीर्घ with some other
	 * scan changes, and the threshold behaves as a flag in those
	 * versions.
	 */
	अगर (priv->new_scan_threshold_behaviour)
		scan->good_CRC_th = is_active ? IWL_GOOD_CRC_TH_DEFAULT :
						IWL_GOOD_CRC_TH_DISABLED;
	अन्यथा
		scan->good_CRC_th = is_active ? IWL_GOOD_CRC_TH_DEFAULT :
						IWL_GOOD_CRC_TH_NEVER;

	band = priv->scan_band;

	अगर (band == NL80211_BAND_2GHZ &&
	    priv->lib->bt_params &&
	    priv->lib->bt_params->advanced_bt_coexist) अणु
		/* transmit 2.4 GHz probes only on first antenna */
		scan_tx_antennas = first_antenna(scan_tx_antennas);
	पूर्ण

	priv->scan_tx_ant[band] = iwl_toggle_tx_ant(priv,
						    priv->scan_tx_ant[band],
						    scan_tx_antennas);
	rate_flags |= iwl_ant_idx_to_flags(priv->scan_tx_ant[band]);
	scan->tx_cmd.rate_n_flags = iwl_hw_set_rate_n_flags(rate, rate_flags);

	/*
	 * In घातer save mode जबतक associated use one chain,
	 * otherwise use all chains
	 */
	अगर (test_bit(STATUS_POWER_PMI, &priv->status) &&
	    !(priv->hw->conf.flags & IEEE80211_CONF_IDLE)) अणु
		/* rx_ant has been set to all valid chains previously */
		active_chains = rx_ant &
				((u8)(priv->chain_noise_data.active_chains));
		अगर (!active_chains)
			active_chains = rx_ant;

		IWL_DEBUG_SCAN(priv, "chain_noise_data.active_chains: %u\n",
				priv->chain_noise_data.active_chains);

		rx_ant = first_antenna(active_chains);
	पूर्ण
	अगर (priv->lib->bt_params &&
	    priv->lib->bt_params->advanced_bt_coexist &&
	    priv->bt_full_concurrent) अणु
		/* operated as 1x1 in full concurrency mode */
		rx_ant = first_antenna(rx_ant);
	पूर्ण

	/* MIMO is not used here, but value is required */
	rx_chain |=
		priv->nvm_data->valid_rx_ant << RXON_RX_CHAIN_VALID_POS;
	rx_chain |= rx_ant << RXON_RX_CHAIN_FORCE_MIMO_SEL_POS;
	rx_chain |= rx_ant << RXON_RX_CHAIN_FORCE_SEL_POS;
	rx_chain |= 0x1 << RXON_RX_CHAIN_DRIVER_FORCE_POS;
	scan->rx_chain = cpu_to_le16(rx_chain);
	चयन (priv->scan_type) अणु
	हाल IWL_SCAN_NORMAL:
		cmd_len = iwl_fill_probe_req(
					(काष्ठा ieee80211_mgmt *)scan->data,
					vअगर->addr,
					priv->scan_request->ie,
					priv->scan_request->ie_len,
					ssid, ssid_len,
					scan_cmd_size - माप(*scan));
		अवरोध;
	हाल IWL_SCAN_RADIO_RESET:
		/* use bcast addr, will not be transmitted but must be valid */
		cmd_len = iwl_fill_probe_req(
					(काष्ठा ieee80211_mgmt *)scan->data,
					iwl_bcast_addr, शून्य, 0,
					शून्य, 0,
					scan_cmd_size - माप(*scan));
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	scan->tx_cmd.len = cpu_to_le16(cmd_len);

	scan->filter_flags |= (RXON_FILTER_ACCEPT_GRP_MSK |
			       RXON_FILTER_BCON_AWARE_MSK);

	चयन (priv->scan_type) अणु
	हाल IWL_SCAN_RADIO_RESET:
		scan->channel_count =
			iwl_get_channel_क्रम_reset_scan(priv, vअगर, band,
				(व्योम *)&scan->data[cmd_len]);
		अवरोध;
	हाल IWL_SCAN_NORMAL:
		scan->channel_count =
			iwl_get_channels_क्रम_scan(priv, vअगर, band,
				is_active, n_probes,
				(व्योम *)&scan->data[cmd_len]);
		अवरोध;
	पूर्ण

	अगर (scan->channel_count == 0) अणु
		IWL_DEBUG_SCAN(priv, "channel count %d\n", scan->channel_count);
		वापस -EIO;
	पूर्ण

	cmd.len[0] += le16_to_cpu(scan->tx_cmd.len) +
	    scan->channel_count * माप(काष्ठा iwl_scan_channel);
	cmd.data[0] = scan;
	cmd.dataflags[0] = IWL_HCMD_DFL_NOCOPY;
	scan->len = cpu_to_le16(cmd.len[0]);

	/* set scan bit here क्रम PAN params */
	set_bit(STATUS_SCAN_HW, &priv->status);

	ret = iwlagn_set_pan_params(priv);
	अगर (ret) अणु
		clear_bit(STATUS_SCAN_HW, &priv->status);
		वापस ret;
	पूर्ण

	ret = iwl_dvm_send_cmd(priv, &cmd);
	अगर (ret) अणु
		clear_bit(STATUS_SCAN_HW, &priv->status);
		iwlagn_set_pan_params(priv);
	पूर्ण

	वापस ret;
पूर्ण

व्योम iwl_init_scan_params(काष्ठा iwl_priv *priv)
अणु
	u8 ant_idx = fls(priv->nvm_data->valid_tx_ant) - 1;
	अगर (!priv->scan_tx_ant[NL80211_BAND_5GHZ])
		priv->scan_tx_ant[NL80211_BAND_5GHZ] = ant_idx;
	अगर (!priv->scan_tx_ant[NL80211_BAND_2GHZ])
		priv->scan_tx_ant[NL80211_BAND_2GHZ] = ant_idx;
पूर्ण

पूर्णांक __must_check iwl_scan_initiate(काष्ठा iwl_priv *priv,
				   काष्ठा ieee80211_vअगर *vअगर,
				   क्रमागत iwl_scan_type scan_type,
				   क्रमागत nl80211_band band)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&priv->mutex);

	cancel_delayed_work(&priv->scan_check);

	अगर (!iwl_is_पढ़ोy_rf(priv)) अणु
		IWL_WARN(priv, "Request scan called when driver not ready.\n");
		वापस -EIO;
	पूर्ण

	अगर (test_bit(STATUS_SCAN_HW, &priv->status)) अणु
		IWL_DEBUG_SCAN(priv,
			"Multiple concurrent scan requests in parallel.\n");
		वापस -EBUSY;
	पूर्ण

	अगर (test_bit(STATUS_SCAN_ABORTING, &priv->status)) अणु
		IWL_DEBUG_SCAN(priv, "Scan request while abort pending.\n");
		वापस -EBUSY;
	पूर्ण

	IWL_DEBUG_SCAN(priv, "Starting %sscan...\n",
			scan_type == IWL_SCAN_NORMAL ? "" :
			"internal short ");

	set_bit(STATUS_SCANNING, &priv->status);
	priv->scan_type = scan_type;
	priv->scan_start = jअगरfies;
	priv->scan_band = band;

	ret = iwlagn_request_scan(priv, vअगर);
	अगर (ret) अणु
		clear_bit(STATUS_SCANNING, &priv->status);
		priv->scan_type = IWL_SCAN_NORMAL;
		वापस ret;
	पूर्ण

	queue_delayed_work(priv->workqueue, &priv->scan_check,
			   IWL_SCAN_CHECK_WATCHDOG);

	वापस 0;
पूर्ण


/*
 * पूर्णांकernal लघु scan, this function should only been called जबतक associated.
 * It will reset and tune the radio to prevent possible RF related problem
 */
व्योम iwl_पूर्णांकernal_लघु_hw_scan(काष्ठा iwl_priv *priv)
अणु
	queue_work(priv->workqueue, &priv->start_पूर्णांकernal_scan);
पूर्ण

अटल व्योम iwl_bg_start_पूर्णांकernal_scan(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा iwl_priv *priv =
		container_of(work, काष्ठा iwl_priv, start_पूर्णांकernal_scan);

	IWL_DEBUG_SCAN(priv, "Start internal scan\n");

	mutex_lock(&priv->mutex);

	अगर (priv->scan_type == IWL_SCAN_RADIO_RESET) अणु
		IWL_DEBUG_SCAN(priv, "Internal scan already in progress\n");
		जाओ unlock;
	पूर्ण

	अगर (test_bit(STATUS_SCANNING, &priv->status)) अणु
		IWL_DEBUG_SCAN(priv, "Scan already in progress.\n");
		जाओ unlock;
	पूर्ण

	अगर (iwl_scan_initiate(priv, शून्य, IWL_SCAN_RADIO_RESET, priv->band))
		IWL_DEBUG_SCAN(priv, "failed to start internal short scan\n");
 unlock:
	mutex_unlock(&priv->mutex);
पूर्ण

अटल व्योम iwl_bg_scan_check(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा iwl_priv *priv =
	    container_of(data, काष्ठा iwl_priv, scan_check.work);

	IWL_DEBUG_SCAN(priv, "Scan check work\n");

	/* Since we are here firmware करोes not finish scan and
	 * most likely is in bad shape, so we करोn't bother to
	 * send पात command, just क्रमce scan complete to mac80211 */
	mutex_lock(&priv->mutex);
	iwl_क्रमce_scan_end(priv);
	mutex_unlock(&priv->mutex);
पूर्ण

अटल व्योम iwl_bg_पात_scan(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा iwl_priv *priv = container_of(work, काष्ठा iwl_priv, पात_scan);

	IWL_DEBUG_SCAN(priv, "Abort scan work\n");

	/* We keep scan_check work queued in हाल when firmware will not
	 * report back scan completed notअगरication */
	mutex_lock(&priv->mutex);
	iwl_scan_cancel_समयout(priv, 200);
	mutex_unlock(&priv->mutex);
पूर्ण

अटल व्योम iwl_bg_scan_completed(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा iwl_priv *priv =
		container_of(work, काष्ठा iwl_priv, scan_completed);

	mutex_lock(&priv->mutex);
	iwl_process_scan_complete(priv);
	mutex_unlock(&priv->mutex);
पूर्ण

व्योम iwl_setup_scan_deferred_work(काष्ठा iwl_priv *priv)
अणु
	INIT_WORK(&priv->scan_completed, iwl_bg_scan_completed);
	INIT_WORK(&priv->पात_scan, iwl_bg_पात_scan);
	INIT_WORK(&priv->start_पूर्णांकernal_scan, iwl_bg_start_पूर्णांकernal_scan);
	INIT_DELAYED_WORK(&priv->scan_check, iwl_bg_scan_check);
पूर्ण

व्योम iwl_cancel_scan_deferred_work(काष्ठा iwl_priv *priv)
अणु
	cancel_work_sync(&priv->start_पूर्णांकernal_scan);
	cancel_work_sync(&priv->पात_scan);
	cancel_work_sync(&priv->scan_completed);

	अगर (cancel_delayed_work_sync(&priv->scan_check)) अणु
		mutex_lock(&priv->mutex);
		iwl_क्रमce_scan_end(priv);
		mutex_unlock(&priv->mutex);
	पूर्ण
पूर्ण
