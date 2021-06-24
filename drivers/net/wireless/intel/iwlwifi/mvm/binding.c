<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2012-2014, 2020 Intel Corporation
 * Copyright (C) 2016 Intel Deutschland GmbH
 */
#समावेश <net/mac80211.h>
#समावेश "fw-api.h"
#समावेश "mvm.h"

काष्ठा iwl_mvm_अगरace_iterator_data अणु
	काष्ठा ieee80211_vअगर *ignore_vअगर;
	पूर्णांक idx;

	काष्ठा iwl_mvm_phy_ctxt *phyctxt;

	u16 ids[MAX_MACS_IN_BINDING];
	u16 colors[MAX_MACS_IN_BINDING];
पूर्ण;

अटल पूर्णांक iwl_mvm_binding_cmd(काष्ठा iwl_mvm *mvm, u32 action,
			       काष्ठा iwl_mvm_अगरace_iterator_data *data)
अणु
	काष्ठा iwl_binding_cmd cmd;
	काष्ठा iwl_mvm_phy_ctxt *phyctxt = data->phyctxt;
	पूर्णांक i, ret;
	u32 status;
	पूर्णांक size;

	स_रखो(&cmd, 0, माप(cmd));

	अगर (fw_has_capa(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_BINDING_CDB_SUPPORT)) अणु
		size = माप(cmd);
		cmd.lmac_id = cpu_to_le32(iwl_mvm_get_lmac_id(mvm->fw,
							      phyctxt->channel->band));
	पूर्ण अन्यथा अणु
		size = IWL_BINDING_CMD_SIZE_V1;
	पूर्ण

	cmd.id_and_color = cpu_to_le32(FW_CMD_ID_AND_COLOR(phyctxt->id,
							   phyctxt->color));
	cmd.action = cpu_to_le32(action);
	cmd.phy = cpu_to_le32(FW_CMD_ID_AND_COLOR(phyctxt->id,
						  phyctxt->color));

	क्रम (i = 0; i < MAX_MACS_IN_BINDING; i++)
		cmd.macs[i] = cpu_to_le32(FW_CTXT_INVALID);
	क्रम (i = 0; i < data->idx; i++)
		cmd.macs[i] = cpu_to_le32(FW_CMD_ID_AND_COLOR(data->ids[i],
							      data->colors[i]));

	status = 0;
	ret = iwl_mvm_send_cmd_pdu_status(mvm, BINDING_CONTEXT_CMD,
					  size, &cmd, &status);
	अगर (ret) अणु
		IWL_ERR(mvm, "Failed to send binding (action:%d): %d\n",
			action, ret);
		वापस ret;
	पूर्ण

	अगर (status) अणु
		IWL_ERR(mvm, "Binding command failed: %u\n", status);
		ret = -EIO;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम iwl_mvm_अगरace_iterator(व्योम *_data, u8 *mac,
				   काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_अगरace_iterator_data *data = _data;
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	अगर (vअगर == data->ignore_vअगर)
		वापस;

	अगर (mvmvअगर->phy_ctxt != data->phyctxt)
		वापस;

	अगर (WARN_ON_ONCE(data->idx >= MAX_MACS_IN_BINDING))
		वापस;

	data->ids[data->idx] = mvmvअगर->id;
	data->colors[data->idx] = mvmvअगर->color;
	data->idx++;
पूर्ण

अटल पूर्णांक iwl_mvm_binding_update(काष्ठा iwl_mvm *mvm,
				  काष्ठा ieee80211_vअगर *vअगर,
				  काष्ठा iwl_mvm_phy_ctxt *phyctxt,
				  bool add)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mvm_अगरace_iterator_data data = अणु
		.ignore_vअगर = vअगर,
		.phyctxt = phyctxt,
	पूर्ण;
	u32 action = FW_CTXT_ACTION_MODIFY;

	lockdep_निश्चित_held(&mvm->mutex);

	ieee80211_iterate_active_पूर्णांकerfaces_atomic(mvm->hw,
						   IEEE80211_IFACE_ITER_NORMAL,
						   iwl_mvm_अगरace_iterator,
						   &data);

	/*
	 * If there are no other पूर्णांकerfaces yet we
	 * need to create a new binding.
	 */
	अगर (data.idx == 0) अणु
		अगर (add)
			action = FW_CTXT_ACTION_ADD;
		अन्यथा
			action = FW_CTXT_ACTION_REMOVE;
	पूर्ण

	अगर (add) अणु
		अगर (WARN_ON_ONCE(data.idx >= MAX_MACS_IN_BINDING))
			वापस -EINVAL;

		data.ids[data.idx] = mvmvअगर->id;
		data.colors[data.idx] = mvmvअगर->color;
		data.idx++;
	पूर्ण

	वापस iwl_mvm_binding_cmd(mvm, action, &data);
पूर्ण

पूर्णांक iwl_mvm_binding_add_vअगर(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	अगर (WARN_ON_ONCE(!mvmvअगर->phy_ctxt))
		वापस -EINVAL;

	/*
	 * Update SF - Disable अगर needed. अगर this fails, SF might still be on
	 * जबतक many macs are bound, which is क्रमbidden - so fail the binding.
	 */
	अगर (iwl_mvm_sf_update(mvm, vअगर, false))
		वापस -EINVAL;

	वापस iwl_mvm_binding_update(mvm, vअगर, mvmvअगर->phy_ctxt, true);
पूर्ण

पूर्णांक iwl_mvm_binding_हटाओ_vअगर(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	पूर्णांक ret;

	अगर (WARN_ON_ONCE(!mvmvअगर->phy_ctxt))
		वापस -EINVAL;

	ret = iwl_mvm_binding_update(mvm, vअगर, mvmvअगर->phy_ctxt, false);

	अगर (!ret)
		अगर (iwl_mvm_sf_update(mvm, vअगर, true))
			IWL_ERR(mvm, "Failed to update SF state\n");

	वापस ret;
पूर्ण
