<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2012-2014, 2018-2020 Intel Corporation
 * Copyright (C) 2013-2014 Intel Mobile Communications GmbH
 * Copyright (C) 2017 Intel Deutschland GmbH
 */
#समावेश <net/mac80211.h>
#समावेश "fw-api.h"
#समावेश "mvm.h"

/* Maps the driver specअगरic channel width definition to the fw values */
u8 iwl_mvm_get_channel_width(काष्ठा cfg80211_chan_def *chandef)
अणु
	चयन (chandef->width) अणु
	हाल NL80211_CHAN_WIDTH_20_NOHT:
	हाल NL80211_CHAN_WIDTH_20:
		वापस PHY_VHT_CHANNEL_MODE20;
	हाल NL80211_CHAN_WIDTH_40:
		वापस PHY_VHT_CHANNEL_MODE40;
	हाल NL80211_CHAN_WIDTH_80:
		वापस PHY_VHT_CHANNEL_MODE80;
	हाल NL80211_CHAN_WIDTH_160:
		वापस PHY_VHT_CHANNEL_MODE160;
	शेष:
		WARN(1, "Invalid channel width=%u", chandef->width);
		वापस PHY_VHT_CHANNEL_MODE20;
	पूर्ण
पूर्ण

/*
 * Maps the driver specअगरic control channel position (relative to the center
 * freq) definitions to the the fw values
 */
u8 iwl_mvm_get_ctrl_pos(काष्ठा cfg80211_chan_def *chandef)
अणु
	चयन (chandef->chan->center_freq - chandef->center_freq1) अणु
	हाल -70:
		वापस PHY_VHT_CTRL_POS_4_BELOW;
	हाल -50:
		वापस PHY_VHT_CTRL_POS_3_BELOW;
	हाल -30:
		वापस PHY_VHT_CTRL_POS_2_BELOW;
	हाल -10:
		वापस PHY_VHT_CTRL_POS_1_BELOW;
	हाल  10:
		वापस PHY_VHT_CTRL_POS_1_ABOVE;
	हाल  30:
		वापस PHY_VHT_CTRL_POS_2_ABOVE;
	हाल  50:
		वापस PHY_VHT_CTRL_POS_3_ABOVE;
	हाल  70:
		वापस PHY_VHT_CTRL_POS_4_ABOVE;
	शेष:
		WARN(1, "Invalid channel definition");
		fallthrough;
	हाल 0:
		/*
		 * The FW is expected to check the control channel position only
		 * when in HT/VHT and the channel width is not 20MHz. Return
		 * this value as the शेष one.
		 */
		वापस PHY_VHT_CTRL_POS_1_BELOW;
	पूर्ण
पूर्ण

/*
 * Conकाष्ठा the generic fields of the PHY context command
 */
अटल व्योम iwl_mvm_phy_ctxt_cmd_hdr(काष्ठा iwl_mvm_phy_ctxt *ctxt,
				     काष्ठा iwl_phy_context_cmd *cmd,
				     u32 action)
अणु
	cmd->id_and_color = cpu_to_le32(FW_CMD_ID_AND_COLOR(ctxt->id,
							    ctxt->color));
	cmd->action = cpu_to_le32(action);
पूर्ण

अटल व्योम iwl_mvm_phy_ctxt_set_rxchain(काष्ठा iwl_mvm *mvm,
					 __le32 *rxchain_info,
					 u8 chains_अटल,
					 u8 chains_dynamic)
अणु
	u8 active_cnt, idle_cnt;

	/* Set rx the chains */
	idle_cnt = chains_अटल;
	active_cnt = chains_dynamic;

	/* In scenarios where we only ever use a single-stream rates,
	 * i.e. legacy 11b/g/a associations, single-stream APs or even
	 * अटल SMPS, enable both chains to get भागersity, improving
	 * the हाल where we're far enough from the AP that attenuation
	 * between the two antennas is sufficiently dअगरferent to impact
	 * perक्रमmance.
	 */
	अगर (active_cnt == 1 && iwl_mvm_rx_भागersity_allowed(mvm)) अणु
		idle_cnt = 2;
		active_cnt = 2;
	पूर्ण

	*rxchain_info = cpu_to_le32(iwl_mvm_get_valid_rx_ant(mvm) <<
					PHY_RX_CHAIN_VALID_POS);
	*rxchain_info |= cpu_to_le32(idle_cnt << PHY_RX_CHAIN_CNT_POS);
	*rxchain_info |= cpu_to_le32(active_cnt <<
					 PHY_RX_CHAIN_MIMO_CNT_POS);
#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	अगर (unlikely(mvm->dbgfs_rx_phyinfo))
		*rxchain_info = cpu_to_le32(mvm->dbgfs_rx_phyinfo);
#पूर्ण_अगर
पूर्ण

/*
 * Add the phy configuration to the PHY context command
 */
अटल व्योम iwl_mvm_phy_ctxt_cmd_data_v1(काष्ठा iwl_mvm *mvm,
					 काष्ठा iwl_phy_context_cmd_v1 *cmd,
					 काष्ठा cfg80211_chan_def *chandef,
					 u8 chains_अटल, u8 chains_dynamic)
अणु
	काष्ठा iwl_phy_context_cmd_tail *tail =
		iwl_mvm_chan_info_cmd_tail(mvm, &cmd->ci);

	/* Set the channel info data */
	iwl_mvm_set_chan_info_chandef(mvm, &cmd->ci, chandef);

	iwl_mvm_phy_ctxt_set_rxchain(mvm, &tail->rxchain_info,
				     chains_अटल, chains_dynamic);

	tail->txchain_info = cpu_to_le32(iwl_mvm_get_valid_tx_ant(mvm));
पूर्ण

/*
 * Add the phy configuration to the PHY context command
 */
अटल व्योम iwl_mvm_phy_ctxt_cmd_data(काष्ठा iwl_mvm *mvm,
				      काष्ठा iwl_phy_context_cmd *cmd,
				      काष्ठा cfg80211_chan_def *chandef,
				      u8 chains_अटल, u8 chains_dynamic)
अणु
	cmd->lmac_id = cpu_to_le32(iwl_mvm_get_lmac_id(mvm->fw,
						       chandef->chan->band));

	/* Set the channel info data */
	iwl_mvm_set_chan_info_chandef(mvm, &cmd->ci, chandef);

	iwl_mvm_phy_ctxt_set_rxchain(mvm, &cmd->rxchain_info,
				     chains_अटल, chains_dynamic);
पूर्ण

/*
 * Send a command to apply the current phy configuration. The command is send
 * only अगर something in the configuration changed: in हाल that this is the
 * first समय that the phy configuration is applied or in हाल that the phy
 * configuration changed from the previous apply.
 */
अटल पूर्णांक iwl_mvm_phy_ctxt_apply(काष्ठा iwl_mvm *mvm,
				  काष्ठा iwl_mvm_phy_ctxt *ctxt,
				  काष्ठा cfg80211_chan_def *chandef,
				  u8 chains_अटल, u8 chains_dynamic,
				  u32 action)
अणु
	पूर्णांक ret;
	पूर्णांक ver = iwl_fw_lookup_cmd_ver(mvm->fw, IWL_ALWAYS_LONG_GROUP,
					PHY_CONTEXT_CMD, 1);

	अगर (ver == 3) अणु
		काष्ठा iwl_phy_context_cmd cmd = अणुपूर्ण;

		/* Set the command header fields */
		iwl_mvm_phy_ctxt_cmd_hdr(ctxt, &cmd, action);

		/* Set the command data */
		iwl_mvm_phy_ctxt_cmd_data(mvm, &cmd, chandef,
					  chains_अटल,
					  chains_dynamic);

		ret = iwl_mvm_send_cmd_pdu(mvm, PHY_CONTEXT_CMD,
					   0, माप(cmd), &cmd);
	पूर्ण अन्यथा अगर (ver < 3) अणु
		काष्ठा iwl_phy_context_cmd_v1 cmd = अणुपूर्ण;
		u16 len = माप(cmd) - iwl_mvm_chan_info_padding(mvm);

		/* Set the command header fields */
		iwl_mvm_phy_ctxt_cmd_hdr(ctxt,
					 (काष्ठा iwl_phy_context_cmd *)&cmd,
					 action);

		/* Set the command data */
		iwl_mvm_phy_ctxt_cmd_data_v1(mvm, &cmd, chandef,
					     chains_अटल,
					     chains_dynamic);
		ret = iwl_mvm_send_cmd_pdu(mvm, PHY_CONTEXT_CMD,
					   0, len, &cmd);
	पूर्ण अन्यथा अणु
		IWL_ERR(mvm, "PHY ctxt cmd error ver %d not supported\n", ver);
		वापस -EOPNOTSUPP;
	पूर्ण


	अगर (ret)
		IWL_ERR(mvm, "PHY ctxt cmd error. ret=%d\n", ret);
	वापस ret;
पूर्ण

/*
 * Send a command to add a PHY context based on the current HW configuration.
 */
पूर्णांक iwl_mvm_phy_ctxt_add(काष्ठा iwl_mvm *mvm, काष्ठा iwl_mvm_phy_ctxt *ctxt,
			 काष्ठा cfg80211_chan_def *chandef,
			 u8 chains_अटल, u8 chains_dynamic)
अणु
	WARN_ON(!test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status) &&
		ctxt->ref);
	lockdep_निश्चित_held(&mvm->mutex);

	ctxt->channel = chandef->chan;

	वापस iwl_mvm_phy_ctxt_apply(mvm, ctxt, chandef,
				      chains_अटल, chains_dynamic,
				      FW_CTXT_ACTION_ADD);
पूर्ण

/*
 * Update the number of references to the given PHY context. This is valid only
 * in हाल the PHY context was alपढ़ोy created, i.e., its reference count > 0.
 */
व्योम iwl_mvm_phy_ctxt_ref(काष्ठा iwl_mvm *mvm, काष्ठा iwl_mvm_phy_ctxt *ctxt)
अणु
	lockdep_निश्चित_held(&mvm->mutex);
	ctxt->ref++;
पूर्ण

/*
 * Send a command to modअगरy the PHY context based on the current HW
 * configuration. Note that the function करोes not check that the configuration
 * changed.
 */
पूर्णांक iwl_mvm_phy_ctxt_changed(काष्ठा iwl_mvm *mvm, काष्ठा iwl_mvm_phy_ctxt *ctxt,
			     काष्ठा cfg80211_chan_def *chandef,
			     u8 chains_अटल, u8 chains_dynamic)
अणु
	क्रमागत iwl_ctxt_action action = FW_CTXT_ACTION_MODIFY;

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (fw_has_capa(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_BINDING_CDB_SUPPORT) &&
	    ctxt->channel->band != chandef->chan->band) अणु
		पूर्णांक ret;

		/* ... हटाओ it here ...*/
		ret = iwl_mvm_phy_ctxt_apply(mvm, ctxt, chandef,
					     chains_अटल, chains_dynamic,
					     FW_CTXT_ACTION_REMOVE);
		अगर (ret)
			वापस ret;

		/* ... and proceed to add it again */
		action = FW_CTXT_ACTION_ADD;
	पूर्ण

	ctxt->channel = chandef->chan;
	ctxt->width = chandef->width;
	वापस iwl_mvm_phy_ctxt_apply(mvm, ctxt, chandef,
				      chains_अटल, chains_dynamic,
				      action);
पूर्ण

व्योम iwl_mvm_phy_ctxt_unref(काष्ठा iwl_mvm *mvm, काष्ठा iwl_mvm_phy_ctxt *ctxt)
अणु
	lockdep_निश्चित_held(&mvm->mutex);

	अगर (WARN_ON_ONCE(!ctxt))
		वापस;

	ctxt->ref--;

	/*
	 * Move unused phy's to a शेष channel. When the phy is moved the,
	 * fw will cleanup immediate quiet bit अगर it was previously set,
	 * otherwise we might not be able to reuse this phy.
	 */
	अगर (ctxt->ref == 0) अणु
		काष्ठा ieee80211_channel *chan;
		काष्ठा cfg80211_chan_def chandef;
		काष्ठा ieee80211_supported_band *sband = शून्य;
		क्रमागत nl80211_band band = NL80211_BAND_2GHZ;

		जबतक (!sband && band < NUM_NL80211_BANDS)
			sband = mvm->hw->wiphy->bands[band++];

		अगर (WARN_ON(!sband))
			वापस;

		chan = &sband->channels[0];

		cfg80211_chandef_create(&chandef, chan, NL80211_CHAN_NO_HT);
		iwl_mvm_phy_ctxt_changed(mvm, ctxt, &chandef, 1, 1);
	पूर्ण
पूर्ण

अटल व्योम iwl_mvm_binding_iterator(व्योम *_data, u8 *mac,
				     काष्ठा ieee80211_vअगर *vअगर)
अणु
	अचिन्हित दीर्घ *data = _data;
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	अगर (!mvmvअगर->phy_ctxt)
		वापस;

	अगर (vअगर->type == NL80211_IFTYPE_STATION ||
	    vअगर->type == NL80211_IFTYPE_AP)
		__set_bit(mvmvअगर->phy_ctxt->id, data);
पूर्ण

पूर्णांक iwl_mvm_phy_ctx_count(काष्ठा iwl_mvm *mvm)
अणु
	अचिन्हित दीर्घ phy_ctxt_counter = 0;

	ieee80211_iterate_active_पूर्णांकerfaces_atomic(mvm->hw,
						   IEEE80211_IFACE_ITER_NORMAL,
						   iwl_mvm_binding_iterator,
						   &phy_ctxt_counter);

	वापस hweight8(phy_ctxt_counter);
पूर्ण
