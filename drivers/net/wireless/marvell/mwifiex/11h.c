<शैली गुरु>
/*
 * NXP Wireless LAN device driver: 802.11h
 *
 * Copyright 2011-2020 NXP
 *
 * This software file (the "File") is distributed by NXP
 * under the terms of the GNU General Public License Version 2, June 1991
 * (the "License").  You may use, redistribute and/or modअगरy this File in
 * accordance with the terms and conditions of the License, a copy of which
 * is available by writing to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fअगरth Floor, Boston, MA 02110-1301 USA or on the
 * worldwide web at http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 *
 * THE खाता IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE
 * ARE EXPRESSLY DISCLAIMED.  The License provides additional details about
 * this warranty disclaimer.
 */

#समावेश "main.h"
#समावेश "fw.h"


व्योम mwअगरiex_init_11h_params(काष्ठा mwअगरiex_निजी *priv)
अणु
	priv->state_11h.is_11h_enabled = true;
	priv->state_11h.is_11h_active = false;
पूर्ण

अंतरभूत पूर्णांक mwअगरiex_is_11h_active(काष्ठा mwअगरiex_निजी *priv)
अणु
	वापस priv->state_11h.is_11h_active;
पूर्ण
/* This function appends 11h info to a buffer जबतक joining an
 * infraकाष्ठाure BSS
 */
अटल व्योम
mwअगरiex_11h_process_infra_join(काष्ठा mwअगरiex_निजी *priv, u8 **buffer,
			       काष्ठा mwअगरiex_bssdescriptor *bss_desc)
अणु
	काष्ठा mwअगरiex_ie_types_header *ie_header;
	काष्ठा mwअगरiex_ie_types_pwr_capability *cap;
	काष्ठा mwअगरiex_ie_types_local_pwr_स्थिरraपूर्णांक *स्थिरraपूर्णांक;
	काष्ठा ieee80211_supported_band *sband;
	u8 radio_type;
	पूर्णांक i;

	अगर (!buffer || !(*buffer))
		वापस;

	radio_type = mwअगरiex_band_to_radio_type((u8) bss_desc->bss_band);
	sband = priv->wdev.wiphy->bands[radio_type];

	cap = (काष्ठा mwअगरiex_ie_types_pwr_capability *)*buffer;
	cap->header.type = cpu_to_le16(WLAN_EID_PWR_CAPABILITY);
	cap->header.len = cpu_to_le16(2);
	cap->min_pwr = 0;
	cap->max_pwr = 0;
	*buffer += माप(*cap);

	स्थिरraपूर्णांक = (काष्ठा mwअगरiex_ie_types_local_pwr_स्थिरraपूर्णांक *)*buffer;
	स्थिरraपूर्णांक->header.type = cpu_to_le16(WLAN_EID_PWR_CONSTRAINT);
	स्थिरraपूर्णांक->header.len = cpu_to_le16(2);
	स्थिरraपूर्णांक->chan = bss_desc->channel;
	स्थिरraपूर्णांक->स्थिरraपूर्णांक = bss_desc->local_स्थिरraपूर्णांक;
	*buffer += माप(*स्थिरraपूर्णांक);

	ie_header = (काष्ठा mwअगरiex_ie_types_header *)*buffer;
	ie_header->type = cpu_to_le16(TLV_TYPE_PASSTHROUGH);
	ie_header->len  = cpu_to_le16(2 * sband->n_channels + 2);
	*buffer += माप(*ie_header);
	*(*buffer)++ = WLAN_EID_SUPPORTED_CHANNELS;
	*(*buffer)++ = 2 * sband->n_channels;
	क्रम (i = 0; i < sband->n_channels; i++) अणु
		*(*buffer)++ = ieee80211_frequency_to_channel(
					sband->channels[i].center_freq);
		*(*buffer)++ = 1; /* one channel in the subband */
	पूर्ण
पूर्ण

/* Enable or disable the 11h extensions in the firmware */
पूर्णांक mwअगरiex_11h_activate(काष्ठा mwअगरiex_निजी *priv, bool flag)
अणु
	u32 enable = flag;

	/* enable master mode radar detection on AP पूर्णांकerface */
	अगर ((GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_UAP) && enable)
		enable |= MWIFIEX_MASTER_RADAR_DET_MASK;

	वापस mwअगरiex_send_cmd(priv, HostCmd_CMD_802_11_SNMP_MIB,
				HostCmd_ACT_GEN_SET, DOT11H_I, &enable, true);
पूर्ण

/* This functions processes TLV buffer क्रम a pending BSS Join command.
 *
 * Activate 11h functionality in the firmware अगर the spectrum management
 * capability bit is found in the network we are joining. Also, necessary
 * TLVs are set based on requested network's 11h capability.
 */
व्योम mwअगरiex_11h_process_join(काष्ठा mwअगरiex_निजी *priv, u8 **buffer,
			      काष्ठा mwअगरiex_bssdescriptor *bss_desc)
अणु
	अगर (bss_desc->sensed_11h) अणु
		/* Activate 11h functions in firmware, turns on capability
		 * bit
		 */
		mwअगरiex_11h_activate(priv, true);
		priv->state_11h.is_11h_active = true;
		bss_desc->cap_info_biपंचांगap |= WLAN_CAPABILITY_SPECTRUM_MGMT;
		mwअगरiex_11h_process_infra_join(priv, buffer, bss_desc);
	पूर्ण अन्यथा अणु
		/* Deactivate 11h functions in the firmware */
		mwअगरiex_11h_activate(priv, false);
		priv->state_11h.is_11h_active = false;
		bss_desc->cap_info_biपंचांगap &= ~WLAN_CAPABILITY_SPECTRUM_MGMT;
	पूर्ण
पूर्ण

/* This is DFS CAC work queue function.
 * This delayed work emits CAC finished event क्रम cfg80211 अगर
 * CAC was started earlier.
 */
व्योम mwअगरiex_dfs_cac_work_queue(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cfg80211_chan_def chandef;
	काष्ठा delayed_work *delayed_work = to_delayed_work(work);
	काष्ठा mwअगरiex_निजी *priv =
			container_of(delayed_work, काष्ठा mwअगरiex_निजी,
				     dfs_cac_work);

	chandef = priv->dfs_chandef;
	अगर (priv->wdev.cac_started) अणु
		mwअगरiex_dbg(priv->adapter, MSG,
			    "CAC timer finished; No radar detected\n");
		cfg80211_cac_event(priv->netdev, &chandef,
				   NL80211_RADAR_CAC_FINISHED,
				   GFP_KERNEL);
	पूर्ण
पूर्ण

/* This function prepares channel report request command to FW क्रम
 * starting radar detection.
 */
पूर्णांक mwअगरiex_cmd_issue_chan_report_request(काष्ठा mwअगरiex_निजी *priv,
					  काष्ठा host_cmd_ds_command *cmd,
					  व्योम *data_buf)
अणु
	काष्ठा host_cmd_ds_chan_rpt_req *cr_req = &cmd->params.chan_rpt_req;
	काष्ठा mwअगरiex_radar_params *radar_params = (व्योम *)data_buf;

	cmd->command = cpu_to_le16(HostCmd_CMD_CHAN_REPORT_REQUEST);
	cmd->size = cpu_to_le16(S_DS_GEN);
	le16_unaligned_add_cpu(&cmd->size,
			       माप(काष्ठा host_cmd_ds_chan_rpt_req));

	cr_req->chan_desc.start_freq = cpu_to_le16(MWIFIEX_A_BAND_START_FREQ);
	cr_req->chan_desc.chan_num = radar_params->chandef->chan->hw_value;
	cr_req->chan_desc.chan_width = radar_params->chandef->width;
	cr_req->msec_dwell_समय = cpu_to_le32(radar_params->cac_समय_ms);

	अगर (radar_params->cac_समय_ms)
		mwअगरiex_dbg(priv->adapter, MSG,
			    "11h: issuing DFS Radar check for channel=%d\n",
			    radar_params->chandef->chan->hw_value);
	अन्यथा
		mwअगरiex_dbg(priv->adapter, MSG, "cancelling CAC\n");

	वापस 0;
पूर्ण

पूर्णांक mwअगरiex_stop_radar_detection(काष्ठा mwअगरiex_निजी *priv,
				 काष्ठा cfg80211_chan_def *chandef)
अणु
	काष्ठा mwअगरiex_radar_params radar_params;

	स_रखो(&radar_params, 0, माप(काष्ठा mwअगरiex_radar_params));
	radar_params.chandef = chandef;
	radar_params.cac_समय_ms = 0;

	वापस mwअगरiex_send_cmd(priv, HostCmd_CMD_CHAN_REPORT_REQUEST,
				HostCmd_ACT_GEN_SET, 0, &radar_params, true);
पूर्ण

/* This function is to पात ongoing CAC upon stopping AP operations
 * or during unload.
 */
व्योम mwअगरiex_पात_cac(काष्ठा mwअगरiex_निजी *priv)
अणु
	अगर (priv->wdev.cac_started) अणु
		अगर (mwअगरiex_stop_radar_detection(priv, &priv->dfs_chandef))
			mwअगरiex_dbg(priv->adapter, ERROR,
				    "failed to stop CAC in FW\n");
		mwअगरiex_dbg(priv->adapter, MSG,
			    "Aborting delayed work for CAC.\n");
		cancel_delayed_work_sync(&priv->dfs_cac_work);
		cfg80211_cac_event(priv->netdev, &priv->dfs_chandef,
				   NL80211_RADAR_CAC_ABORTED, GFP_KERNEL);
	पूर्ण
पूर्ण

/* This function handles channel report event from FW during CAC period.
 * If radar is detected during CAC, driver indicates the same to cfg80211
 * and also cancels ongoing delayed work.
 */
पूर्णांक mwअगरiex_11h_handle_chanrpt_पढ़ोy(काष्ठा mwअगरiex_निजी *priv,
				     काष्ठा sk_buff *skb)
अणु
	काष्ठा host_cmd_ds_chan_rpt_event *rpt_event;
	काष्ठा mwअगरiex_ie_types_chan_rpt_data *rpt;
	u8 *evt_buf;
	u16 event_len, tlv_len;

	rpt_event = (व्योम *)(skb->data + माप(u32));
	event_len = skb->len - (माप(काष्ठा host_cmd_ds_chan_rpt_event)+
				माप(u32));

	अगर (le32_to_cpu(rpt_event->result) != HostCmd_RESULT_OK) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "Error in channel report event\n");
		वापस -1;
	पूर्ण

	evt_buf = (व्योम *)&rpt_event->tlvbuf;

	जबतक (event_len >= माप(काष्ठा mwअगरiex_ie_types_header)) अणु
		rpt = (व्योम *)&rpt_event->tlvbuf;
		tlv_len = le16_to_cpu(rpt->header.len);

		चयन (le16_to_cpu(rpt->header.type)) अणु
		हाल TLV_TYPE_CHANRPT_11H_BASIC:
			अगर (rpt->map.radar) अणु
				mwअगरiex_dbg(priv->adapter, MSG,
					    "RADAR Detected on channel %d!\n",
					    priv->dfs_chandef.chan->hw_value);
				cancel_delayed_work_sync(&priv->dfs_cac_work);
				cfg80211_cac_event(priv->netdev,
						   &priv->dfs_chandef,
						   NL80211_RADAR_DETECTED,
						   GFP_KERNEL);
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		evt_buf += (tlv_len + माप(rpt->header));
		event_len -= (tlv_len + माप(rpt->header));
	पूर्ण

	वापस 0;
पूर्ण

/* Handler क्रम radar detected event from FW.*/
पूर्णांक mwअगरiex_11h_handle_radar_detected(काष्ठा mwअगरiex_निजी *priv,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा mwअगरiex_radar_det_event *rdr_event;

	rdr_event = (व्योम *)(skb->data + माप(u32));

	mwअगरiex_dbg(priv->adapter, MSG,
		    "radar detected; indicating kernel\n");
	अगर (mwअगरiex_stop_radar_detection(priv, &priv->dfs_chandef))
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "Failed to stop CAC in FW\n");
	cfg80211_radar_event(priv->adapter->wiphy, &priv->dfs_chandef,
			     GFP_KERNEL);
	mwअगरiex_dbg(priv->adapter, MSG, "regdomain: %d\n",
		    rdr_event->reg_करोमुख्य);
	mwअगरiex_dbg(priv->adapter, MSG, "radar detection type: %d\n",
		    rdr_event->det_type);

	वापस 0;
पूर्ण

/* This is work queue function क्रम channel चयन handling.
 * This function takes care of updating new channel definitin to
 * bss config काष्ठाure, restart AP and indicate channel चयन success
 * to cfg80211.
 */
व्योम mwअगरiex_dfs_chan_sw_work_queue(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mwअगरiex_uap_bss_param *bss_cfg;
	काष्ठा delayed_work *delayed_work = to_delayed_work(work);
	काष्ठा mwअगरiex_निजी *priv =
			container_of(delayed_work, काष्ठा mwअगरiex_निजी,
				     dfs_chan_sw_work);

	bss_cfg = &priv->bss_cfg;
	अगर (!bss_cfg->beacon_period) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "channel switch: AP already stopped\n");
		वापस;
	पूर्ण

	mwअगरiex_uap_set_channel(priv, bss_cfg, priv->dfs_chandef);

	अगर (mwअगरiex_config_start_uap(priv, bss_cfg)) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "Failed to start AP after channel switch\n");
		वापस;
	पूर्ण

	mwअगरiex_dbg(priv->adapter, MSG,
		    "indicating channel switch completion to kernel\n");
	cfg80211_ch_चयन_notअगरy(priv->netdev, &priv->dfs_chandef);
पूर्ण
