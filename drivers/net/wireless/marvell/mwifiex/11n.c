<शैली गुरु>
/*
 * NXP Wireless LAN device driver: 802.11n
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

#समावेश "decl.h"
#समावेश "ioctl.h"
#समावेश "util.h"
#समावेश "fw.h"
#समावेश "main.h"
#समावेश "wmm.h"
#समावेश "11n.h"

/*
 * Fills HT capability inक्रमmation field, AMPDU Parameters field, HT extended
 * capability field, and supported MCS set fields.
 *
 * HT capability inक्रमmation field, AMPDU Parameters field, supported MCS set
 * fields are retrieved from cfg80211 stack
 *
 * RD responder bit to set to clear in the extended capability header.
 */
पूर्णांक mwअगरiex_fill_cap_info(काष्ठा mwअगरiex_निजी *priv, u8 radio_type,
			  काष्ठा ieee80211_ht_cap *ht_cap)
अणु
	uपूर्णांक16_t ht_ext_cap = le16_to_cpu(ht_cap->extended_ht_cap_info);
	काष्ठा ieee80211_supported_band *sband =
					priv->wdev.wiphy->bands[radio_type];

	अगर (WARN_ON_ONCE(!sband)) अणु
		mwअगरiex_dbg(priv->adapter, ERROR, "Invalid radio type!\n");
		वापस -EINVAL;
	पूर्ण

	ht_cap->ampdu_params_info =
		(sband->ht_cap.ampdu_factor &
		 IEEE80211_HT_AMPDU_PARM_FACTOR) |
		((sband->ht_cap.ampdu_density <<
		 IEEE80211_HT_AMPDU_PARM_DENSITY_SHIFT) &
		 IEEE80211_HT_AMPDU_PARM_DENSITY);

	स_नकल((u8 *)&ht_cap->mcs, &sband->ht_cap.mcs,
	       माप(sband->ht_cap.mcs));

	अगर (priv->bss_mode == NL80211_IFTYPE_STATION ||
	    (sband->ht_cap.cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40 &&
	     (priv->adapter->sec_chan_offset !=
					IEEE80211_HT_PARAM_CHA_SEC_NONE)))
		/* Set MCS32 क्रम infra mode or ad-hoc mode with 40MHz support */
		SETHT_MCS32(ht_cap->mcs.rx_mask);

	/* Clear RD responder bit */
	ht_ext_cap &= ~IEEE80211_HT_EXT_CAP_RD_RESPONDER;

	ht_cap->cap_info = cpu_to_le16(sband->ht_cap.cap);
	ht_cap->extended_ht_cap_info = cpu_to_le16(ht_ext_cap);

	अगर (ISSUPP_BEAMFORMING(priv->adapter->hw_करोt_11n_dev_cap))
		ht_cap->tx_BF_cap_info = cpu_to_le32(MWIFIEX_DEF_11N_TX_BF_CAP);

	वापस 0;
पूर्ण

/*
 * This function वापसs the poपूर्णांकer to an entry in BA Stream
 * table which matches the requested BA status.
 */
अटल काष्ठा mwअगरiex_tx_ba_stream_tbl *
mwअगरiex_get_ba_status(काष्ठा mwअगरiex_निजी *priv,
		      क्रमागत mwअगरiex_ba_status ba_status)
अणु
	काष्ठा mwअगरiex_tx_ba_stream_tbl *tx_ba_tsr_tbl;

	spin_lock_bh(&priv->tx_ba_stream_tbl_lock);
	list_क्रम_each_entry(tx_ba_tsr_tbl, &priv->tx_ba_stream_tbl_ptr, list) अणु
		अगर (tx_ba_tsr_tbl->ba_status == ba_status) अणु
			spin_unlock_bh(&priv->tx_ba_stream_tbl_lock);
			वापस tx_ba_tsr_tbl;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&priv->tx_ba_stream_tbl_lock);
	वापस शून्य;
पूर्ण

/*
 * This function handles the command response of delete a block
 * ack request.
 *
 * The function checks the response success status and takes action
 * accordingly (send an add BA request in हाल of success, or recreate
 * the deleted stream in हाल of failure, अगर the add BA was also
 * initiated by us).
 */
पूर्णांक mwअगरiex_ret_11n_delba(काष्ठा mwअगरiex_निजी *priv,
			  काष्ठा host_cmd_ds_command *resp)
अणु
	पूर्णांक tid;
	काष्ठा mwअगरiex_tx_ba_stream_tbl *tx_ba_tbl;
	काष्ठा host_cmd_ds_11n_delba *del_ba = &resp->params.del_ba;
	uपूर्णांक16_t del_ba_param_set = le16_to_cpu(del_ba->del_ba_param_set);

	tid = del_ba_param_set >> DELBA_TID_POS;
	अगर (del_ba->del_result == BA_RESULT_SUCCESS) अणु
		mwअगरiex_del_ba_tbl(priv, tid, del_ba->peer_mac_addr,
				   TYPE_DELBA_SENT,
				   INITIATOR_BIT(del_ba_param_set));

		tx_ba_tbl = mwअगरiex_get_ba_status(priv, BA_SETUP_INPROGRESS);
		अगर (tx_ba_tbl)
			mwअगरiex_send_addba(priv, tx_ba_tbl->tid,
					   tx_ba_tbl->ra);
	पूर्ण अन्यथा अणु /*
		  * In हाल of failure, recreate the deleted stream in हाल
		  * we initiated the ADDBA
		  */
		अगर (!INITIATOR_BIT(del_ba_param_set))
			वापस 0;

		mwअगरiex_create_ba_tbl(priv, del_ba->peer_mac_addr, tid,
				      BA_SETUP_INPROGRESS);

		tx_ba_tbl = mwअगरiex_get_ba_status(priv, BA_SETUP_INPROGRESS);

		अगर (tx_ba_tbl)
			mwअगरiex_del_ba_tbl(priv, tx_ba_tbl->tid, tx_ba_tbl->ra,
					   TYPE_DELBA_SENT, true);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function handles the command response of add a block
 * ack request.
 *
 * Handling includes changing the header fields to CPU क्रमmats, checking
 * the response success status and taking actions accordingly (delete the
 * BA stream table in हाल of failure).
 */
पूर्णांक mwअगरiex_ret_11n_addba_req(काष्ठा mwअगरiex_निजी *priv,
			      काष्ठा host_cmd_ds_command *resp)
अणु
	पूर्णांक tid, tid_करोwn;
	काष्ठा host_cmd_ds_11n_addba_rsp *add_ba_rsp = &resp->params.add_ba_rsp;
	काष्ठा mwअगरiex_tx_ba_stream_tbl *tx_ba_tbl;
	काष्ठा mwअगरiex_ra_list_tbl *ra_list;
	u16 block_ack_param_set = le16_to_cpu(add_ba_rsp->block_ack_param_set);

	add_ba_rsp->ssn = cpu_to_le16((le16_to_cpu(add_ba_rsp->ssn))
			& SSN_MASK);

	tid = (block_ack_param_set & IEEE80211_ADDBA_PARAM_TID_MASK)
	       >> BLOCKACKPARAM_TID_POS;

	tid_करोwn = mwअगरiex_wmm_करोwngrade_tid(priv, tid);
	ra_list = mwअगरiex_wmm_get_ralist_node(priv, tid_करोwn, add_ba_rsp->
		peer_mac_addr);
	अगर (le16_to_cpu(add_ba_rsp->status_code) != BA_RESULT_SUCCESS) अणु
		अगर (ra_list) अणु
			ra_list->ba_status = BA_SETUP_NONE;
			ra_list->amsdu_in_ampdu = false;
		पूर्ण
		mwअगरiex_del_ba_tbl(priv, tid, add_ba_rsp->peer_mac_addr,
				   TYPE_DELBA_SENT, true);
		अगर (add_ba_rsp->add_rsp_result != BA_RESULT_TIMEOUT)
			priv->aggr_prio_tbl[tid].ampdu_ap =
				BA_STREAM_NOT_ALLOWED;
		वापस 0;
	पूर्ण

	tx_ba_tbl = mwअगरiex_get_ba_tbl(priv, tid, add_ba_rsp->peer_mac_addr);
	अगर (tx_ba_tbl) अणु
		mwअगरiex_dbg(priv->adapter, EVENT, "info: BA stream complete\n");
		tx_ba_tbl->ba_status = BA_SETUP_COMPLETE;
		अगर ((block_ack_param_set & BLOCKACKPARAM_AMSDU_SUPP_MASK) &&
		    priv->add_ba_param.tx_amsdu &&
		    (priv->aggr_prio_tbl[tid].amsdu != BA_STREAM_NOT_ALLOWED))
			tx_ba_tbl->amsdu = true;
		अन्यथा
			tx_ba_tbl->amsdu = false;
		अगर (ra_list) अणु
			ra_list->amsdu_in_ampdu = tx_ba_tbl->amsdu;
			ra_list->ba_status = BA_SETUP_COMPLETE;
		पूर्ण
	पूर्ण अन्यथा अणु
		mwअगरiex_dbg(priv->adapter, ERROR, "BA stream not created\n");
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function prepares command of reconfigure Tx buffer.
 *
 * Preparation includes -
 *      - Setting command ID, action and proper size
 *      - Setting Tx buffer size (क्रम SET only)
 *      - Ensuring correct endian-ness
 */
पूर्णांक mwअगरiex_cmd_recfg_tx_buf(काष्ठा mwअगरiex_निजी *priv,
			     काष्ठा host_cmd_ds_command *cmd, पूर्णांक cmd_action,
			     u16 *buf_size)
अणु
	काष्ठा host_cmd_ds_txbuf_cfg *tx_buf = &cmd->params.tx_buf;
	u16 action = (u16) cmd_action;

	cmd->command = cpu_to_le16(HostCmd_CMD_RECONFIGURE_TX_BUFF);
	cmd->size =
		cpu_to_le16(माप(काष्ठा host_cmd_ds_txbuf_cfg) + S_DS_GEN);
	tx_buf->action = cpu_to_le16(action);
	चयन (action) अणु
	हाल HostCmd_ACT_GEN_SET:
		mwअगरiex_dbg(priv->adapter, CMD,
			    "cmd: set tx_buf=%d\n", *buf_size);
		tx_buf->buff_size = cpu_to_le16(*buf_size);
		अवरोध;
	हाल HostCmd_ACT_GEN_GET:
	शेष:
		tx_buf->buff_size = 0;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * This function prepares command of AMSDU aggregation control.
 *
 * Preparation includes -
 *      - Setting command ID, action and proper size
 *      - Setting AMSDU control parameters (क्रम SET only)
 *      - Ensuring correct endian-ness
 */
पूर्णांक mwअगरiex_cmd_amsdu_aggr_ctrl(काष्ठा host_cmd_ds_command *cmd,
				पूर्णांक cmd_action,
				काष्ठा mwअगरiex_ds_11n_amsdu_aggr_ctrl *aa_ctrl)
अणु
	काष्ठा host_cmd_ds_amsdu_aggr_ctrl *amsdu_ctrl =
		&cmd->params.amsdu_aggr_ctrl;
	u16 action = (u16) cmd_action;

	cmd->command = cpu_to_le16(HostCmd_CMD_AMSDU_AGGR_CTRL);
	cmd->size = cpu_to_le16(माप(काष्ठा host_cmd_ds_amsdu_aggr_ctrl)
				+ S_DS_GEN);
	amsdu_ctrl->action = cpu_to_le16(action);
	चयन (action) अणु
	हाल HostCmd_ACT_GEN_SET:
		amsdu_ctrl->enable = cpu_to_le16(aa_ctrl->enable);
		amsdu_ctrl->curr_buf_size = 0;
		अवरोध;
	हाल HostCmd_ACT_GEN_GET:
	शेष:
		amsdu_ctrl->curr_buf_size = 0;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * This function prepares 11n configuration command.
 *
 * Preparation includes -
 *      - Setting command ID, action and proper size
 *      - Setting HT Tx capability and HT Tx inक्रमmation fields
 *      - Ensuring correct endian-ness
 */
पूर्णांक mwअगरiex_cmd_11n_cfg(काष्ठा mwअगरiex_निजी *priv,
			काष्ठा host_cmd_ds_command *cmd, u16 cmd_action,
			काष्ठा mwअगरiex_ds_11n_tx_cfg *txcfg)
अणु
	काष्ठा host_cmd_ds_11n_cfg *htcfg = &cmd->params.htcfg;

	cmd->command = cpu_to_le16(HostCmd_CMD_11N_CFG);
	cmd->size = cpu_to_le16(माप(काष्ठा host_cmd_ds_11n_cfg) + S_DS_GEN);
	htcfg->action = cpu_to_le16(cmd_action);
	htcfg->ht_tx_cap = cpu_to_le16(txcfg->tx_htcap);
	htcfg->ht_tx_info = cpu_to_le16(txcfg->tx_htinfo);

	अगर (priv->adapter->is_hw_11ac_capable)
		htcfg->misc_config = cpu_to_le16(txcfg->misc_config);

	वापस 0;
पूर्ण

/*
 * This function appends an 11n TLV to a buffer.
 *
 * Buffer allocation is responsibility of the calling
 * function. No size validation is made here.
 *
 * The function fills up the following sections, अगर applicable -
 *      - HT capability IE
 *      - HT inक्रमmation IE (with channel list)
 *      - 20/40 BSS Coexistence IE
 *      - HT Extended Capabilities IE
 */
पूर्णांक
mwअगरiex_cmd_append_11n_tlv(काष्ठा mwअगरiex_निजी *priv,
			   काष्ठा mwअगरiex_bssdescriptor *bss_desc,
			   u8 **buffer)
अणु
	काष्ठा mwअगरiex_ie_types_htcap *ht_cap;
	काष्ठा mwअगरiex_ie_types_htinfo *ht_info;
	काष्ठा mwअगरiex_ie_types_chan_list_param_set *chan_list;
	काष्ठा mwअगरiex_ie_types_2040bssco *bss_co_2040;
	काष्ठा mwअगरiex_ie_types_extcap *ext_cap;
	पूर्णांक ret_len = 0;
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee_types_header *hdr;
	u8 radio_type;

	अगर (!buffer || !*buffer)
		वापस ret_len;

	radio_type = mwअगरiex_band_to_radio_type((u8) bss_desc->bss_band);
	sband = priv->wdev.wiphy->bands[radio_type];

	अगर (bss_desc->bcn_ht_cap) अणु
		ht_cap = (काष्ठा mwअगरiex_ie_types_htcap *) *buffer;
		स_रखो(ht_cap, 0, माप(काष्ठा mwअगरiex_ie_types_htcap));
		ht_cap->header.type = cpu_to_le16(WLAN_EID_HT_CAPABILITY);
		ht_cap->header.len =
				cpu_to_le16(माप(काष्ठा ieee80211_ht_cap));
		स_नकल((u8 *) ht_cap + माप(काष्ठा mwअगरiex_ie_types_header),
		       (u8 *)bss_desc->bcn_ht_cap,
		       le16_to_cpu(ht_cap->header.len));

		mwअगरiex_fill_cap_info(priv, radio_type, &ht_cap->ht_cap);
		/* Update HT40 capability from current channel inक्रमmation */
		अगर (bss_desc->bcn_ht_oper) अणु
			u8 ht_param = bss_desc->bcn_ht_oper->ht_param;
			u8 radio =
			mwअगरiex_band_to_radio_type(bss_desc->bss_band);
			पूर्णांक freq =
			ieee80211_channel_to_frequency(bss_desc->channel,
						       radio);
			काष्ठा ieee80211_channel *chan =
			ieee80211_get_channel(priv->adapter->wiphy, freq);

			चयन (ht_param & IEEE80211_HT_PARAM_CHA_SEC_OFFSET) अणु
			हाल IEEE80211_HT_PARAM_CHA_SEC_ABOVE:
				अगर (chan->flags & IEEE80211_CHAN_NO_HT40PLUS) अणु
					ht_cap->ht_cap.cap_info &=
					cpu_to_le16
					(~IEEE80211_HT_CAP_SUP_WIDTH_20_40);
					ht_cap->ht_cap.cap_info &=
					cpu_to_le16(~IEEE80211_HT_CAP_SGI_40);
				पूर्ण
				अवरोध;
			हाल IEEE80211_HT_PARAM_CHA_SEC_BELOW:
				अगर (chan->flags & IEEE80211_CHAN_NO_HT40MINUS) अणु
					ht_cap->ht_cap.cap_info &=
					cpu_to_le16
					(~IEEE80211_HT_CAP_SUP_WIDTH_20_40);
					ht_cap->ht_cap.cap_info &=
					cpu_to_le16(~IEEE80211_HT_CAP_SGI_40);
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण

		*buffer += माप(काष्ठा mwअगरiex_ie_types_htcap);
		ret_len += माप(काष्ठा mwअगरiex_ie_types_htcap);
	पूर्ण

	अगर (bss_desc->bcn_ht_oper) अणु
		अगर (priv->bss_mode == NL80211_IFTYPE_ADHOC) अणु
			ht_info = (काष्ठा mwअगरiex_ie_types_htinfo *) *buffer;
			स_रखो(ht_info, 0,
			       माप(काष्ठा mwअगरiex_ie_types_htinfo));
			ht_info->header.type =
					cpu_to_le16(WLAN_EID_HT_OPERATION);
			ht_info->header.len =
				cpu_to_le16(
					माप(काष्ठा ieee80211_ht_operation));

			स_नकल((u8 *) ht_info +
			       माप(काष्ठा mwअगरiex_ie_types_header),
			       (u8 *)bss_desc->bcn_ht_oper,
			       le16_to_cpu(ht_info->header.len));

			अगर (!(sband->ht_cap.cap &
					IEEE80211_HT_CAP_SUP_WIDTH_20_40))
				ht_info->ht_oper.ht_param &=
					~(IEEE80211_HT_PARAM_CHAN_WIDTH_ANY |
					IEEE80211_HT_PARAM_CHA_SEC_OFFSET);

			*buffer += माप(काष्ठा mwअगरiex_ie_types_htinfo);
			ret_len += माप(काष्ठा mwअगरiex_ie_types_htinfo);
		पूर्ण

		chan_list =
			(काष्ठा mwअगरiex_ie_types_chan_list_param_set *) *buffer;
		स_रखो(chan_list, 0,
		       माप(काष्ठा mwअगरiex_ie_types_chan_list_param_set));
		chan_list->header.type = cpu_to_le16(TLV_TYPE_CHANLIST);
		chan_list->header.len = cpu_to_le16(
			माप(काष्ठा mwअगरiex_ie_types_chan_list_param_set) -
			माप(काष्ठा mwअगरiex_ie_types_header));
		chan_list->chan_scan_param[0].chan_number =
			bss_desc->bcn_ht_oper->primary_chan;
		chan_list->chan_scan_param[0].radio_type =
			mwअगरiex_band_to_radio_type((u8) bss_desc->bss_band);

		अगर (sband->ht_cap.cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40 &&
		    bss_desc->bcn_ht_oper->ht_param &
		    IEEE80211_HT_PARAM_CHAN_WIDTH_ANY)
			SET_SECONDARYCHAN(chan_list->chan_scan_param[0].
					  radio_type,
					  (bss_desc->bcn_ht_oper->ht_param &
					  IEEE80211_HT_PARAM_CHA_SEC_OFFSET));

		*buffer += माप(काष्ठा mwअगरiex_ie_types_chan_list_param_set);
		ret_len += माप(काष्ठा mwअगरiex_ie_types_chan_list_param_set);
	पूर्ण

	अगर (bss_desc->bcn_bss_co_2040) अणु
		bss_co_2040 = (काष्ठा mwअगरiex_ie_types_2040bssco *) *buffer;
		स_रखो(bss_co_2040, 0,
		       माप(काष्ठा mwअगरiex_ie_types_2040bssco));
		bss_co_2040->header.type = cpu_to_le16(WLAN_EID_BSS_COEX_2040);
		bss_co_2040->header.len =
		       cpu_to_le16(माप(bss_co_2040->bss_co_2040));

		स_नकल((u8 *) bss_co_2040 +
		       माप(काष्ठा mwअगरiex_ie_types_header),
		       bss_desc->bcn_bss_co_2040 +
		       माप(काष्ठा ieee_types_header),
		       le16_to_cpu(bss_co_2040->header.len));

		*buffer += माप(काष्ठा mwअगरiex_ie_types_2040bssco);
		ret_len += माप(काष्ठा mwअगरiex_ie_types_2040bssco);
	पूर्ण

	अगर (bss_desc->bcn_ext_cap) अणु
		hdr = (व्योम *)bss_desc->bcn_ext_cap;
		ext_cap = (काष्ठा mwअगरiex_ie_types_extcap *) *buffer;
		स_रखो(ext_cap, 0, माप(काष्ठा mwअगरiex_ie_types_extcap));
		ext_cap->header.type = cpu_to_le16(WLAN_EID_EXT_CAPABILITY);
		ext_cap->header.len = cpu_to_le16(hdr->len);

		स_नकल((u8 *)ext_cap->ext_capab,
		       bss_desc->bcn_ext_cap + माप(काष्ठा ieee_types_header),
		       le16_to_cpu(ext_cap->header.len));

		अगर (hdr->len > 3 &&
		    ext_cap->ext_capab[3] & WLAN_EXT_CAPA4_INTERWORKING_ENABLED)
			priv->hs2_enabled = true;
		अन्यथा
			priv->hs2_enabled = false;

		*buffer += माप(काष्ठा mwअगरiex_ie_types_extcap) + hdr->len;
		ret_len += माप(काष्ठा mwअगरiex_ie_types_extcap) + hdr->len;
	पूर्ण

	वापस ret_len;
पूर्ण

/*
 * This function checks अगर the given poपूर्णांकer is valid entry of
 * Tx BA Stream table.
 */
अटल पूर्णांक mwअगरiex_is_tx_ba_stream_ptr_valid(काष्ठा mwअगरiex_निजी *priv,
				काष्ठा mwअगरiex_tx_ba_stream_tbl *tx_tbl_ptr)
अणु
	काष्ठा mwअगरiex_tx_ba_stream_tbl *tx_ba_tsr_tbl;

	list_क्रम_each_entry(tx_ba_tsr_tbl, &priv->tx_ba_stream_tbl_ptr, list) अणु
		अगर (tx_ba_tsr_tbl == tx_tbl_ptr)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * This function deletes the given entry in Tx BA Stream table.
 *
 * The function also perक्रमms a validity check on the supplied
 * poपूर्णांकer beक्रमe trying to delete.
 */
व्योम mwअगरiex_11n_delete_tx_ba_stream_tbl_entry(काष्ठा mwअगरiex_निजी *priv,
				काष्ठा mwअगरiex_tx_ba_stream_tbl *tx_ba_tsr_tbl)
अणु
	अगर (!tx_ba_tsr_tbl &&
	    mwअगरiex_is_tx_ba_stream_ptr_valid(priv, tx_ba_tsr_tbl))
		वापस;

	mwअगरiex_dbg(priv->adapter, INFO,
		    "info: tx_ba_tsr_tbl %p\n", tx_ba_tsr_tbl);

	list_del(&tx_ba_tsr_tbl->list);

	kमुक्त(tx_ba_tsr_tbl);
पूर्ण

/*
 * This function deletes all the entries in Tx BA Stream table.
 */
व्योम mwअगरiex_11n_delete_all_tx_ba_stream_tbl(काष्ठा mwअगरiex_निजी *priv)
अणु
	पूर्णांक i;
	काष्ठा mwअगरiex_tx_ba_stream_tbl *del_tbl_ptr, *पंचांगp_node;

	spin_lock_bh(&priv->tx_ba_stream_tbl_lock);
	list_क्रम_each_entry_safe(del_tbl_ptr, पंचांगp_node,
				 &priv->tx_ba_stream_tbl_ptr, list)
		mwअगरiex_11n_delete_tx_ba_stream_tbl_entry(priv, del_tbl_ptr);
	spin_unlock_bh(&priv->tx_ba_stream_tbl_lock);

	INIT_LIST_HEAD(&priv->tx_ba_stream_tbl_ptr);

	क्रम (i = 0; i < MAX_NUM_TID; ++i)
		priv->aggr_prio_tbl[i].ampdu_ap =
			priv->aggr_prio_tbl[i].ampdu_user;
पूर्ण

/*
 * This function वापसs the poपूर्णांकer to an entry in BA Stream
 * table which matches the given RA/TID pair.
 */
काष्ठा mwअगरiex_tx_ba_stream_tbl *
mwअगरiex_get_ba_tbl(काष्ठा mwअगरiex_निजी *priv, पूर्णांक tid, u8 *ra)
अणु
	काष्ठा mwअगरiex_tx_ba_stream_tbl *tx_ba_tsr_tbl;

	spin_lock_bh(&priv->tx_ba_stream_tbl_lock);
	list_क्रम_each_entry(tx_ba_tsr_tbl, &priv->tx_ba_stream_tbl_ptr, list) अणु
		अगर (ether_addr_equal_unaligned(tx_ba_tsr_tbl->ra, ra) &&
		    tx_ba_tsr_tbl->tid == tid) अणु
			spin_unlock_bh(&priv->tx_ba_stream_tbl_lock);
			वापस tx_ba_tsr_tbl;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&priv->tx_ba_stream_tbl_lock);
	वापस शून्य;
पूर्ण

/*
 * This function creates an entry in Tx BA stream table क्रम the
 * given RA/TID pair.
 */
व्योम mwअगरiex_create_ba_tbl(काष्ठा mwअगरiex_निजी *priv, u8 *ra, पूर्णांक tid,
			   क्रमागत mwअगरiex_ba_status ba_status)
अणु
	काष्ठा mwअगरiex_tx_ba_stream_tbl *new_node;
	काष्ठा mwअगरiex_ra_list_tbl *ra_list;
	पूर्णांक tid_करोwn;

	अगर (!mwअगरiex_get_ba_tbl(priv, tid, ra)) अणु
		new_node = kzalloc(माप(काष्ठा mwअगरiex_tx_ba_stream_tbl),
				   GFP_ATOMIC);
		अगर (!new_node)
			वापस;

		tid_करोwn = mwअगरiex_wmm_करोwngrade_tid(priv, tid);
		ra_list = mwअगरiex_wmm_get_ralist_node(priv, tid_करोwn, ra);
		अगर (ra_list) अणु
			ra_list->ba_status = ba_status;
			ra_list->amsdu_in_ampdu = false;
		पूर्ण
		INIT_LIST_HEAD(&new_node->list);

		new_node->tid = tid;
		new_node->ba_status = ba_status;
		स_नकल(new_node->ra, ra, ETH_ALEN);

		spin_lock_bh(&priv->tx_ba_stream_tbl_lock);
		list_add_tail(&new_node->list, &priv->tx_ba_stream_tbl_ptr);
		spin_unlock_bh(&priv->tx_ba_stream_tbl_lock);
	पूर्ण
पूर्ण

/*
 * This function sends an add BA request to the given TID/RA pair.
 */
पूर्णांक mwअगरiex_send_addba(काष्ठा mwअगरiex_निजी *priv, पूर्णांक tid, u8 *peer_mac)
अणु
	काष्ठा host_cmd_ds_11n_addba_req add_ba_req;
	u32 tx_win_size = priv->add_ba_param.tx_win_size;
	अटल u8 dialog_tok;
	पूर्णांक ret;
	u16 block_ack_param_set;

	mwअगरiex_dbg(priv->adapter, CMD, "cmd: %s: tid %d\n", __func__, tid);

	स_रखो(&add_ba_req, 0, माप(add_ba_req));

	अगर ((GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_STA) &&
	    ISSUPP_TDLS_ENABLED(priv->adapter->fw_cap_info) &&
	    priv->adapter->is_hw_11ac_capable &&
	    स_भेद(priv->cfg_bssid, peer_mac, ETH_ALEN)) अणु
		काष्ठा mwअगरiex_sta_node *sta_ptr;

		spin_lock_bh(&priv->sta_list_spinlock);
		sta_ptr = mwअगरiex_get_sta_entry(priv, peer_mac);
		अगर (!sta_ptr) अणु
			spin_unlock_bh(&priv->sta_list_spinlock);
			mwअगरiex_dbg(priv->adapter, ERROR,
				    "BA setup with unknown TDLS peer %pM!\n",
				    peer_mac);
			वापस -1;
		पूर्ण
		अगर (sta_ptr->is_11ac_enabled)
			tx_win_size = MWIFIEX_11AC_STA_AMPDU_DEF_TXWINSIZE;
		spin_unlock_bh(&priv->sta_list_spinlock);
	पूर्ण

	block_ack_param_set = (u16)((tid << BLOCKACKPARAM_TID_POS) |
				    tx_win_size << BLOCKACKPARAM_WINSIZE_POS |
				    IMMEDIATE_BLOCK_ACK);

	/* enable AMSDU inside AMPDU */
	अगर (priv->add_ba_param.tx_amsdu &&
	    (priv->aggr_prio_tbl[tid].amsdu != BA_STREAM_NOT_ALLOWED))
		block_ack_param_set |= BLOCKACKPARAM_AMSDU_SUPP_MASK;

	add_ba_req.block_ack_param_set = cpu_to_le16(block_ack_param_set);
	add_ba_req.block_ack_पंचांगo = cpu_to_le16((u16)priv->add_ba_param.समयout);

	++dialog_tok;

	अगर (dialog_tok == 0)
		dialog_tok = 1;

	add_ba_req.dialog_token = dialog_tok;
	स_नकल(&add_ba_req.peer_mac_addr, peer_mac, ETH_ALEN);

	/* We करोn't रुको क्रम the response of this command */
	ret = mwअगरiex_send_cmd(priv, HostCmd_CMD_11N_ADDBA_REQ,
			       0, 0, &add_ba_req, false);

	वापस ret;
पूर्ण

/*
 * This function sends a delete BA request to the given TID/RA pair.
 */
पूर्णांक mwअगरiex_send_delba(काष्ठा mwअगरiex_निजी *priv, पूर्णांक tid, u8 *peer_mac,
		       पूर्णांक initiator)
अणु
	काष्ठा host_cmd_ds_11n_delba delba;
	पूर्णांक ret;
	uपूर्णांक16_t del_ba_param_set;

	स_रखो(&delba, 0, माप(delba));
	delba.del_ba_param_set = cpu_to_le16(tid << DELBA_TID_POS);

	del_ba_param_set = le16_to_cpu(delba.del_ba_param_set);
	अगर (initiator)
		del_ba_param_set |= IEEE80211_DELBA_PARAM_INITIATOR_MASK;
	अन्यथा
		del_ba_param_set &= ~IEEE80211_DELBA_PARAM_INITIATOR_MASK;

	स_नकल(&delba.peer_mac_addr, peer_mac, ETH_ALEN);

	/* We करोn't रुको क्रम the response of this command */
	ret = mwअगरiex_send_cmd(priv, HostCmd_CMD_11N_DELBA,
			       HostCmd_ACT_GEN_SET, 0, &delba, false);

	वापस ret;
पूर्ण

/*
 * This function sends delba to specअगरic tid
 */
व्योम mwअगरiex_11n_delba(काष्ठा mwअगरiex_निजी *priv, पूर्णांक tid)
अणु
	काष्ठा mwअगरiex_rx_reorder_tbl *rx_reor_tbl_ptr;

	spin_lock_bh(&priv->rx_reorder_tbl_lock);
	list_क्रम_each_entry(rx_reor_tbl_ptr, &priv->rx_reorder_tbl_ptr, list) अणु
		अगर (rx_reor_tbl_ptr->tid == tid) अणु
			dev_dbg(priv->adapter->dev,
				"Send delba to tid=%d, %pM\n",
				tid, rx_reor_tbl_ptr->ta);
			mwअगरiex_send_delba(priv, tid, rx_reor_tbl_ptr->ta, 0);
			जाओ निकास;
		पूर्ण
	पूर्ण
निकास:
	spin_unlock_bh(&priv->rx_reorder_tbl_lock);
पूर्ण

/*
 * This function handles the command response of a delete BA request.
 */
व्योम mwअगरiex_11n_delete_ba_stream(काष्ठा mwअगरiex_निजी *priv, u8 *del_ba)
अणु
	काष्ठा host_cmd_ds_11n_delba *cmd_del_ba =
		(काष्ठा host_cmd_ds_11n_delba *) del_ba;
	uपूर्णांक16_t del_ba_param_set = le16_to_cpu(cmd_del_ba->del_ba_param_set);
	पूर्णांक tid;

	tid = del_ba_param_set >> DELBA_TID_POS;

	mwअगरiex_del_ba_tbl(priv, tid, cmd_del_ba->peer_mac_addr,
			   TYPE_DELBA_RECEIVE, INITIATOR_BIT(del_ba_param_set));
पूर्ण

/*
 * This function retrieves the Rx reordering table.
 */
पूर्णांक mwअगरiex_get_rx_reorder_tbl(काष्ठा mwअगरiex_निजी *priv,
			       काष्ठा mwअगरiex_ds_rx_reorder_tbl *buf)
अणु
	पूर्णांक i;
	काष्ठा mwअगरiex_ds_rx_reorder_tbl *rx_reo_tbl = buf;
	काष्ठा mwअगरiex_rx_reorder_tbl *rx_reorder_tbl_ptr;
	पूर्णांक count = 0;

	spin_lock_bh(&priv->rx_reorder_tbl_lock);
	list_क्रम_each_entry(rx_reorder_tbl_ptr, &priv->rx_reorder_tbl_ptr,
			    list) अणु
		rx_reo_tbl->tid = (u16) rx_reorder_tbl_ptr->tid;
		स_नकल(rx_reo_tbl->ta, rx_reorder_tbl_ptr->ta, ETH_ALEN);
		rx_reo_tbl->start_win = rx_reorder_tbl_ptr->start_win;
		rx_reo_tbl->win_size = rx_reorder_tbl_ptr->win_size;
		क्रम (i = 0; i < rx_reorder_tbl_ptr->win_size; ++i) अणु
			अगर (rx_reorder_tbl_ptr->rx_reorder_ptr[i])
				rx_reo_tbl->buffer[i] = true;
			अन्यथा
				rx_reo_tbl->buffer[i] = false;
		पूर्ण
		rx_reo_tbl++;
		count++;

		अगर (count >= MWIFIEX_MAX_RX_BASTREAM_SUPPORTED)
			अवरोध;
	पूर्ण
	spin_unlock_bh(&priv->rx_reorder_tbl_lock);

	वापस count;
पूर्ण

/*
 * This function retrieves the Tx BA stream table.
 */
पूर्णांक mwअगरiex_get_tx_ba_stream_tbl(काष्ठा mwअगरiex_निजी *priv,
				 काष्ठा mwअगरiex_ds_tx_ba_stream_tbl *buf)
अणु
	काष्ठा mwअगरiex_tx_ba_stream_tbl *tx_ba_tsr_tbl;
	काष्ठा mwअगरiex_ds_tx_ba_stream_tbl *rx_reo_tbl = buf;
	पूर्णांक count = 0;

	spin_lock_bh(&priv->tx_ba_stream_tbl_lock);
	list_क्रम_each_entry(tx_ba_tsr_tbl, &priv->tx_ba_stream_tbl_ptr, list) अणु
		rx_reo_tbl->tid = (u16) tx_ba_tsr_tbl->tid;
		mwअगरiex_dbg(priv->adapter, DATA, "data: %s tid=%d\n",
			    __func__, rx_reo_tbl->tid);
		स_नकल(rx_reo_tbl->ra, tx_ba_tsr_tbl->ra, ETH_ALEN);
		rx_reo_tbl->amsdu = tx_ba_tsr_tbl->amsdu;
		rx_reo_tbl++;
		count++;
		अगर (count >= MWIFIEX_MAX_TX_BASTREAM_SUPPORTED)
			अवरोध;
	पूर्ण
	spin_unlock_bh(&priv->tx_ba_stream_tbl_lock);

	वापस count;
पूर्ण

/*
 * This function retrieves the entry क्रम specअगरic tx BA stream table by RA and
 * deletes it.
 */
व्योम mwअगरiex_del_tx_ba_stream_tbl_by_ra(काष्ठा mwअगरiex_निजी *priv, u8 *ra)
अणु
	काष्ठा mwअगरiex_tx_ba_stream_tbl *tbl, *पंचांगp;

	अगर (!ra)
		वापस;

	spin_lock_bh(&priv->tx_ba_stream_tbl_lock);
	list_क्रम_each_entry_safe(tbl, पंचांगp, &priv->tx_ba_stream_tbl_ptr, list)
		अगर (!स_भेद(tbl->ra, ra, ETH_ALEN))
			mwअगरiex_11n_delete_tx_ba_stream_tbl_entry(priv, tbl);
	spin_unlock_bh(&priv->tx_ba_stream_tbl_lock);

	वापस;
पूर्ण

/* This function initializes the BlockACK setup inक्रमmation क्रम given
 * mwअगरiex_निजी काष्ठाure.
 */
व्योम mwअगरiex_set_ba_params(काष्ठा mwअगरiex_निजी *priv)
अणु
	priv->add_ba_param.समयout = MWIFIEX_DEFAULT_BLOCK_ACK_TIMEOUT;

	अगर (GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_UAP) अणु
		priv->add_ba_param.tx_win_size =
						MWIFIEX_UAP_AMPDU_DEF_TXWINSIZE;
		priv->add_ba_param.rx_win_size =
						MWIFIEX_UAP_AMPDU_DEF_RXWINSIZE;
	पूर्ण अन्यथा अणु
		priv->add_ba_param.tx_win_size =
						MWIFIEX_STA_AMPDU_DEF_TXWINSIZE;
		priv->add_ba_param.rx_win_size =
						MWIFIEX_STA_AMPDU_DEF_RXWINSIZE;
	पूर्ण

	priv->add_ba_param.tx_amsdu = true;
	priv->add_ba_param.rx_amsdu = true;

	वापस;
पूर्ण

u8 mwअगरiex_get_sec_chan_offset(पूर्णांक chan)
अणु
	u8 sec_offset;

	चयन (chan) अणु
	हाल 36:
	हाल 44:
	हाल 52:
	हाल 60:
	हाल 100:
	हाल 108:
	हाल 116:
	हाल 124:
	हाल 132:
	हाल 140:
	हाल 149:
	हाल 157:
		sec_offset = IEEE80211_HT_PARAM_CHA_SEC_ABOVE;
		अवरोध;
	हाल 40:
	हाल 48:
	हाल 56:
	हाल 64:
	हाल 104:
	हाल 112:
	हाल 120:
	हाल 128:
	हाल 136:
	हाल 144:
	हाल 153:
	हाल 161:
		sec_offset = IEEE80211_HT_PARAM_CHA_SEC_BELOW;
		अवरोध;
	हाल 165:
	शेष:
		sec_offset = IEEE80211_HT_PARAM_CHA_SEC_NONE;
		अवरोध;
	पूर्ण

	वापस sec_offset;
पूर्ण

/* This function will send DELBA to entries in the priv's
 * Tx BA stream table
 */
अटल व्योम
mwअगरiex_send_delba_txbastream_tbl(काष्ठा mwअगरiex_निजी *priv, u8 tid)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा mwअगरiex_tx_ba_stream_tbl *tx_ba_stream_tbl_ptr;

	list_क्रम_each_entry(tx_ba_stream_tbl_ptr,
			    &priv->tx_ba_stream_tbl_ptr, list) अणु
		अगर (tx_ba_stream_tbl_ptr->ba_status == BA_SETUP_COMPLETE) अणु
			अगर (tid == tx_ba_stream_tbl_ptr->tid) अणु
				dev_dbg(adapter->dev,
					"Tx:Send delba to tid=%d, %pM\n", tid,
					tx_ba_stream_tbl_ptr->ra);
				mwअगरiex_send_delba(priv,
						   tx_ba_stream_tbl_ptr->tid,
						   tx_ba_stream_tbl_ptr->ra, 1);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/* This function updates all the tx_win_size
 */
व्योम mwअगरiex_update_ampdu_txwinsize(काष्ठा mwअगरiex_adapter *adapter)
अणु
	u8 i;
	u32 tx_win_size;
	काष्ठा mwअगरiex_निजी *priv;

	क्रम (i = 0; i < adapter->priv_num; i++) अणु
		अगर (!adapter->priv[i])
			जारी;
		priv = adapter->priv[i];
		tx_win_size = priv->add_ba_param.tx_win_size;

		अगर (priv->bss_type == MWIFIEX_BSS_TYPE_STA)
			priv->add_ba_param.tx_win_size =
				MWIFIEX_STA_AMPDU_DEF_TXWINSIZE;

		अगर (priv->bss_type == MWIFIEX_BSS_TYPE_P2P)
			priv->add_ba_param.tx_win_size =
				MWIFIEX_STA_AMPDU_DEF_TXWINSIZE;

		अगर (priv->bss_type == MWIFIEX_BSS_TYPE_UAP)
			priv->add_ba_param.tx_win_size =
				MWIFIEX_UAP_AMPDU_DEF_TXWINSIZE;

		अगर (adapter->coex_win_size) अणु
			अगर (adapter->coex_tx_win_size)
				priv->add_ba_param.tx_win_size =
					adapter->coex_tx_win_size;
		पूर्ण

		अगर (tx_win_size != priv->add_ba_param.tx_win_size) अणु
			अगर (!priv->media_connected)
				जारी;
			क्रम (i = 0; i < MAX_NUM_TID; i++)
				mwअगरiex_send_delba_txbastream_tbl(priv, i);
		पूर्ण
	पूर्ण
पूर्ण
