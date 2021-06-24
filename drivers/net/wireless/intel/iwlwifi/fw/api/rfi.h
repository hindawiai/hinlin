<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2020 Intel Corporation
 */
#अगर_अघोषित __iwl_fw_api_rfi_h__
#घोषणा __iwl_fw_api_rfi_h__

#घोषणा IWL_RFI_LUT_ENTRY_CHANNELS_NUM 15
#घोषणा IWL_RFI_LUT_SIZE 24
#घोषणा IWL_RFI_LUT_INSTALLED_SIZE 4

/**
 * काष्ठा iwl_rfi_lut_entry - an entry in the RFI frequency LUT.
 *
 * @freq: frequency
 * @channels: channels that can be पूर्णांकerfered at frequency freq (at most 15)
 * @bands: the corresponding bands
 */
काष्ठा iwl_rfi_lut_entry अणु
	__le16 freq;
	u8 channels[IWL_RFI_LUT_ENTRY_CHANNELS_NUM];
	u8 bands[IWL_RFI_LUT_ENTRY_CHANNELS_NUM];
पूर्ण __packed;

/**
 * काष्ठा iwl_rfi_config_cmd - RFI configuration table
 *
 * @entry: a table can have 24 frequency/channel mappings
 * @oem: specअगरies अगर this is the शेष table or set by OEM
 */
काष्ठा iwl_rfi_config_cmd अणु
	काष्ठा iwl_rfi_lut_entry table[IWL_RFI_LUT_SIZE];
	u8 oem;
	u8 reserved[3];
पूर्ण __packed; /* RFI_CONFIG_CMD_API_S_VER_1 */

/**
 * iwl_rfi_freq_table_status - status of the frequency table query
 * @RFI_FREQ_TABLE_OK: can be used
 * @RFI_FREQ_TABLE_DVFS_NOT_READY: DVFS is not पढ़ोy yet, should try later
 * @RFI_FREQ_TABLE_DISABLED: the feature is disabled in FW
 */
क्रमागत iwl_rfi_freq_table_status अणु
	RFI_FREQ_TABLE_OK,
	RFI_FREQ_TABLE_DVFS_NOT_READY,
	RFI_FREQ_TABLE_DISABLED,
पूर्ण;

/**
 * काष्ठा iwl_rfi_freq_table_resp_cmd - get the rfi freq table used by FW
 *
 * @table: table used by FW
 * @status: see &iwl_rfi_freq_table_status
 */
काष्ठा iwl_rfi_freq_table_resp_cmd अणु
	काष्ठा iwl_rfi_lut_entry table[IWL_RFI_LUT_INSTALLED_SIZE];
	__le32 status;
पूर्ण __packed; /* RFI_CONFIG_CMD_API_S_VER_1 */

#पूर्ण_अगर /* __iwl_fw_api_rfi_h__ */
