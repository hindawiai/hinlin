<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2012-2014, 2018 Intel Corporation
 * Copyright (C) 2013-2014 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#समावेश <net/mac80211.h>
#समावेश "fw-api.h"
#समावेश "mvm.h"

#घोषणा QUOTA_100	IWL_MVM_MAX_QUOTA
#घोषणा QUOTA_LOWLAT_MIN ((QUOTA_100 * IWL_MVM_LOWLAT_QUOTA_MIN_PERCENT) / 100)

काष्ठा iwl_mvm_quota_iterator_data अणु
	पूर्णांक n_पूर्णांकerfaces[MAX_BINDINGS];
	पूर्णांक colors[MAX_BINDINGS];
	पूर्णांक low_latency[MAX_BINDINGS];
#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	पूर्णांक dbgfs_min[MAX_BINDINGS];
#पूर्ण_अगर
	पूर्णांक n_low_latency_bindings;
	काष्ठा ieee80211_vअगर *disabled_vअगर;
पूर्ण;

अटल व्योम iwl_mvm_quota_iterator(व्योम *_data, u8 *mac,
				   काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_quota_iterator_data *data = _data;
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	u16 id;

	/* skip disabled पूर्णांकerfaces here immediately */
	अगर (vअगर == data->disabled_vअगर)
		वापस;

	अगर (!mvmvअगर->phy_ctxt)
		वापस;

	/* currently, PHY ID == binding ID */
	id = mvmvअगर->phy_ctxt->id;

	/* need at least one binding per PHY */
	BUILD_BUG_ON(NUM_PHY_CTX > MAX_BINDINGS);

	अगर (WARN_ON_ONCE(id >= MAX_BINDINGS))
		वापस;

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_STATION:
		अगर (vअगर->bss_conf.assoc)
			अवरोध;
		वापस;
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_ADHOC:
		अगर (mvmvअगर->ap_ibss_active)
			अवरोध;
		वापस;
	हाल NL80211_IFTYPE_MONITOR:
		अगर (mvmvअगर->monitor_active)
			अवरोध;
		वापस;
	हाल NL80211_IFTYPE_P2P_DEVICE:
		वापस;
	शेष:
		WARN_ON_ONCE(1);
		वापस;
	पूर्ण

	अगर (data->colors[id] < 0)
		data->colors[id] = mvmvअगर->phy_ctxt->color;
	अन्यथा
		WARN_ON_ONCE(data->colors[id] != mvmvअगर->phy_ctxt->color);

	data->n_पूर्णांकerfaces[id]++;

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	अगर (mvmvअगर->dbgfs_quota_min)
		data->dbgfs_min[id] = max(data->dbgfs_min[id],
					  mvmvअगर->dbgfs_quota_min);
#पूर्ण_अगर

	अगर (iwl_mvm_vअगर_low_latency(mvmvअगर) && !data->low_latency[id]) अणु
		data->n_low_latency_bindings++;
		data->low_latency[id] = true;
	पूर्ण
पूर्ण

अटल व्योम iwl_mvm_adjust_quota_क्रम_noa(काष्ठा iwl_mvm *mvm,
					 काष्ठा iwl_समय_quota_cmd *cmd)
अणु
#अगर_घोषित CONFIG_NL80211_TESTMODE
	काष्ठा iwl_mvm_vअगर *mvmvअगर;
	पूर्णांक i, phy_id = -1, beacon_पूर्णांक = 0;

	अगर (!mvm->noa_duration || !mvm->noa_vअगर)
		वापस;

	mvmvअगर = iwl_mvm_vअगर_from_mac80211(mvm->noa_vअगर);
	अगर (!mvmvअगर->ap_ibss_active)
		वापस;

	phy_id = mvmvअगर->phy_ctxt->id;
	beacon_पूर्णांक = mvm->noa_vअगर->bss_conf.beacon_पूर्णांक;

	क्रम (i = 0; i < MAX_BINDINGS; i++) अणु
		काष्ठा iwl_समय_quota_data *data =
					iwl_mvm_quota_cmd_get_quota(mvm, cmd,
								    i);
		u32 id_n_c = le32_to_cpu(data->id_and_color);
		u32 id = (id_n_c & FW_CTXT_ID_MSK) >> FW_CTXT_ID_POS;
		u32 quota = le32_to_cpu(data->quota);

		अगर (id != phy_id)
			जारी;

		quota *= (beacon_पूर्णांक - mvm->noa_duration);
		quota /= beacon_पूर्णांक;

		IWL_DEBUG_QUOTA(mvm, "quota: adjust for NoA from %d to %d\n",
				le32_to_cpu(data->quota), quota);

		data->quota = cpu_to_le32(quota);
	पूर्ण
#पूर्ण_अगर
पूर्ण

पूर्णांक iwl_mvm_update_quotas(काष्ठा iwl_mvm *mvm,
			  bool क्रमce_update,
			  काष्ठा ieee80211_vअगर *disabled_vअगर)
अणु
	काष्ठा iwl_समय_quota_cmd cmd = अणुपूर्ण;
	पूर्णांक i, idx, err, num_active_macs, quota, quota_rem, n_non_lowlat;
	काष्ठा iwl_mvm_quota_iterator_data data = अणु
		.n_पूर्णांकerfaces = अणुपूर्ण,
		.colors = अणु -1, -1, -1, -1 पूर्ण,
		.disabled_vअगर = disabled_vअगर,
	पूर्ण;
	काष्ठा iwl_समय_quota_cmd *last = &mvm->last_quota_cmd;
	काष्ठा iwl_समय_quota_data *qdata, *last_data;
	bool send = false;

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (fw_has_capa(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_DYNAMIC_QUOTA))
		वापस 0;

	/* update all upon completion */
	अगर (test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status))
		वापस 0;

	/* iterator data above must match */
	BUILD_BUG_ON(MAX_BINDINGS != 4);

	ieee80211_iterate_active_पूर्णांकerfaces_atomic(
		mvm->hw, IEEE80211_IFACE_ITER_NORMAL,
		iwl_mvm_quota_iterator, &data);

	/*
	 * The FW's scheduling session consists of
	 * IWL_MVM_MAX_QUOTA fragments. Divide these fragments
	 * equally between all the bindings that require quota
	 */
	num_active_macs = 0;
	क्रम (i = 0; i < MAX_BINDINGS; i++) अणु
		qdata = iwl_mvm_quota_cmd_get_quota(mvm, &cmd, i);
		qdata->id_and_color = cpu_to_le32(FW_CTXT_INVALID);
		num_active_macs += data.n_पूर्णांकerfaces[i];
	पूर्ण

	n_non_lowlat = num_active_macs;

	अगर (data.n_low_latency_bindings == 1) अणु
		क्रम (i = 0; i < MAX_BINDINGS; i++) अणु
			अगर (data.low_latency[i]) अणु
				n_non_lowlat -= data.n_पूर्णांकerfaces[i];
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (data.n_low_latency_bindings == 1 && n_non_lowlat) अणु
		/*
		 * Reserve quota क्रम the low latency binding in हाल that
		 * there are several data bindings but only a single
		 * low latency one. Split the rest of the quota equally
		 * between the other data पूर्णांकerfaces.
		 */
		quota = (QUOTA_100 - QUOTA_LOWLAT_MIN) / n_non_lowlat;
		quota_rem = QUOTA_100 - n_non_lowlat * quota -
			    QUOTA_LOWLAT_MIN;
		IWL_DEBUG_QUOTA(mvm,
				"quota: low-latency binding active, remaining quota per other binding: %d\n",
				quota);
	पूर्ण अन्यथा अगर (num_active_macs) अणु
		/*
		 * There are 0 or more than 1 low latency bindings, or all the
		 * data पूर्णांकerfaces beदीर्घ to the single low latency binding.
		 * Split the quota equally between the data पूर्णांकerfaces.
		 */
		quota = QUOTA_100 / num_active_macs;
		quota_rem = QUOTA_100 % num_active_macs;
		IWL_DEBUG_QUOTA(mvm,
				"quota: splitting evenly per binding: %d\n",
				quota);
	पूर्ण अन्यथा अणु
		/* values करोn't really matter - won't be used */
		quota = 0;
		quota_rem = 0;
	पूर्ण

	क्रम (idx = 0, i = 0; i < MAX_BINDINGS; i++) अणु
		अगर (data.colors[i] < 0)
			जारी;

		qdata = iwl_mvm_quota_cmd_get_quota(mvm, &cmd, idx);

		qdata->id_and_color =
			cpu_to_le32(FW_CMD_ID_AND_COLOR(i, data.colors[i]));

		अगर (data.n_पूर्णांकerfaces[i] <= 0)
			qdata->quota = cpu_to_le32(0);
#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
		अन्यथा अगर (data.dbgfs_min[i])
			qdata->quota =
				cpu_to_le32(data.dbgfs_min[i] * QUOTA_100 / 100);
#पूर्ण_अगर
		अन्यथा अगर (data.n_low_latency_bindings == 1 && n_non_lowlat &&
			 data.low_latency[i])
			/*
			 * There is more than one binding, but only one of the
			 * bindings is in low latency. For this हाल, allocate
			 * the minimal required quota क्रम the low latency
			 * binding.
			 */
			qdata->quota = cpu_to_le32(QUOTA_LOWLAT_MIN);
		अन्यथा
			qdata->quota =
				cpu_to_le32(quota * data.n_पूर्णांकerfaces[i]);

		WARN_ONCE(le32_to_cpu(qdata->quota) > QUOTA_100,
			  "Binding=%d, quota=%u > max=%u\n",
			  idx, le32_to_cpu(qdata->quota), QUOTA_100);

		qdata->max_duration = cpu_to_le32(0);

		idx++;
	पूर्ण

	/* Give the reमुख्यder of the session to the first data binding */
	क्रम (i = 0; i < MAX_BINDINGS; i++) अणु
		qdata = iwl_mvm_quota_cmd_get_quota(mvm, &cmd, i);
		अगर (le32_to_cpu(qdata->quota) != 0) अणु
			le32_add_cpu(&qdata->quota, quota_rem);
			IWL_DEBUG_QUOTA(mvm,
					"quota: giving remainder of %d to binding %d\n",
					quota_rem, i);
			अवरोध;
		पूर्ण
	पूर्ण

	iwl_mvm_adjust_quota_क्रम_noa(mvm, &cmd);

	/* check that we have non-zero quota क्रम all valid bindings */
	क्रम (i = 0; i < MAX_BINDINGS; i++) अणु
		qdata = iwl_mvm_quota_cmd_get_quota(mvm, &cmd, i);
		last_data = iwl_mvm_quota_cmd_get_quota(mvm, last, i);
		अगर (qdata->id_and_color != last_data->id_and_color)
			send = true;
		अगर (qdata->max_duration != last_data->max_duration)
			send = true;
		अगर (असल((पूर्णांक)le32_to_cpu(qdata->quota) -
			(पूर्णांक)le32_to_cpu(last_data->quota))
						> IWL_MVM_QUOTA_THRESHOLD)
			send = true;
		अगर (qdata->id_and_color == cpu_to_le32(FW_CTXT_INVALID))
			जारी;
		WARN_ONCE(qdata->quota == 0,
			  "zero quota on binding %d\n", i);
	पूर्ण

	अगर (!send && !क्रमce_update) अणु
		/* करोn't send a practically unchanged command, the firmware has
		 * to re-initialize a lot of state and that can have an adverse
		 * impact on it
		 */
		वापस 0;
	पूर्ण

	err = iwl_mvm_send_cmd_pdu(mvm, TIME_QUOTA_CMD, 0,
				   iwl_mvm_quota_cmd_size(mvm), &cmd);

	अगर (err)
		IWL_ERR(mvm, "Failed to send quota: %d\n", err);
	अन्यथा
		mvm->last_quota_cmd = cmd;
	वापस err;
पूर्ण
