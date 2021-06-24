<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2020 - 2021 Intel Corporation
 */

#समावेश "mvm.h"
#समावेश "fw/api/commands.h"
#समावेश "fw/api/phy-ctxt.h"

/**
 * DDR needs frequency in units of 16.666MHz, so provide FW with the
 * frequency values in the adjusted क्रमmat.
 */
स्थिर अटल काष्ठा iwl_rfi_lut_entry iwl_rfi_table[IWL_RFI_LUT_SIZE] = अणु
	/* LPDDR4 */

	/* frequency 3733MHz */
	अणुcpu_to_le16(223), अणु114, 116, 118, 120, 122,पूर्ण,
	      अणुPHY_BAND_5, PHY_BAND_5, PHY_BAND_5, PHY_BAND_5, PHY_BAND_5,पूर्णपूर्ण,

	/* frequency 4267MHz */
	अणुcpu_to_le16(256), अणु79, 83, 85, 87, 89, 91, 93,पूर्ण,
	       अणुPHY_BAND_6, PHY_BAND_6, PHY_BAND_6, PHY_BAND_6, PHY_BAND_6,
		PHY_BAND_6, PHY_BAND_6,पूर्णपूर्ण,

	/* DDR5ePOR */

	/* frequency 4000MHz */
	अणुcpu_to_le16(240), अणु3, 5, 7, 9, 11, 13, 15,पूर्ण,
	      अणुPHY_BAND_6, PHY_BAND_6, PHY_BAND_6, PHY_BAND_6, PHY_BAND_6,
	       PHY_BAND_6, PHY_BAND_6,पूर्णपूर्ण,

	/* frequency 4400MHz */
	अणुcpu_to_le16(264), अणु111, 119, 123, 125, 129, 131, 133, 135, 143,पूर्ण,
	      अणुPHY_BAND_6, PHY_BAND_6, PHY_BAND_6, PHY_BAND_6, PHY_BAND_6,
	       PHY_BAND_6, PHY_BAND_6, PHY_BAND_6, PHY_BAND_6,पूर्णपूर्ण,

	/* LPDDR5iPOR */

	/* frequency 5200MHz */
	अणुcpu_to_le16(312), अणु36, 38, 40, 42, 50,पूर्ण,
	       अणुPHY_BAND_5, PHY_BAND_5, PHY_BAND_5, PHY_BAND_5, PHY_BAND_5,पूर्णपूर्ण,

	/* frequency 6000MHz */
	अणुcpu_to_le16(360), अणु3, 5, 7, 9, 11, 13, 15,पूर्ण,
	       अणुPHY_BAND_6, PHY_BAND_6, PHY_BAND_6, PHY_BAND_6, PHY_BAND_6,
		PHY_BAND_6, PHY_BAND_6,पूर्णपूर्ण,

	/* frequency 6400MHz */
	अणुcpu_to_le16(384), अणु79, 83, 85, 87, 89, 91, 93,पूर्ण,
	       अणुPHY_BAND_6, PHY_BAND_6, PHY_BAND_6, PHY_BAND_6, PHY_BAND_6,
		PHY_BAND_6, PHY_BAND_6,पूर्णपूर्ण,
पूर्ण;

पूर्णांक iwl_rfi_send_config_cmd(काष्ठा iwl_mvm *mvm, काष्ठा iwl_rfi_lut_entry *rfi_table)
अणु
	पूर्णांक ret;
	काष्ठा iwl_rfi_config_cmd cmd;
	काष्ठा iwl_host_cmd hcmd = अणु
		.id = WIDE_ID(SYSTEM_GROUP, RFI_CONFIG_CMD),
		.dataflags[0] = IWL_HCMD_DFL_DUP,
		.data[0] = &cmd,
		.len[0] = माप(cmd),
	पूर्ण;

	अगर (!fw_has_capa(&mvm->fw->ucode_capa, IWL_UCODE_TLV_CAPA_RFIM_SUPPORT))
		वापस -EOPNOTSUPP;

	lockdep_निश्चित_held(&mvm->mutex);

	/* in हाल no table is passed, use the शेष one */
	अगर (!rfi_table) अणु
		स_नकल(cmd.table, iwl_rfi_table, माप(cmd.table));
	पूर्ण अन्यथा अणु
		स_नकल(cmd.table, rfi_table, माप(cmd.table));
		/* notअगरy FW the table is not the शेष one */
		cmd.oem = 1;
	पूर्ण

	ret = iwl_mvm_send_cmd(mvm, &hcmd);

	अगर (ret)
		IWL_ERR(mvm, "Failed to send RFI config cmd %d\n", ret);

	वापस ret;
पूर्ण

काष्ठा iwl_rfi_freq_table_resp_cmd *iwl_rfi_get_freq_table(काष्ठा iwl_mvm *mvm)
अणु
	काष्ठा iwl_rfi_freq_table_resp_cmd *resp;
	पूर्णांक resp_size = माप(*resp);
	पूर्णांक ret;
	काष्ठा iwl_host_cmd cmd = अणु
		.id = WIDE_ID(SYSTEM_GROUP, RFI_GET_FREQ_TABLE_CMD),
		.flags = CMD_WANT_SKB,
	पूर्ण;

	अगर (!fw_has_capa(&mvm->fw->ucode_capa, IWL_UCODE_TLV_CAPA_RFIM_SUPPORT))
		वापस ERR_PTR(-EOPNOTSUPP);

	mutex_lock(&mvm->mutex);
	ret = iwl_mvm_send_cmd(mvm, &cmd);
	mutex_unlock(&mvm->mutex);
	अगर (ret)
		वापस ERR_PTR(ret);

	अगर (WARN_ON_ONCE(iwl_rx_packet_payload_len(cmd.resp_pkt) != resp_size))
		वापस ERR_PTR(-EIO);

	resp = kzalloc(resp_size, GFP_KERNEL);
	अगर (!resp)
		वापस ERR_PTR(-ENOMEM);

	स_नकल(resp, cmd.resp_pkt->data, resp_size);

	iwl_मुक्त_resp(&cmd);
	वापस resp;
पूर्ण
