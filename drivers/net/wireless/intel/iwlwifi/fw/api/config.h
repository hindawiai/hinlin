<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2012-2014, 2018-2019 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#अगर_अघोषित __iwl_fw_api_config_h__
#घोषणा __iwl_fw_api_config_h__

/*
 * काष्ठा iwl_dqa_enable_cmd
 * @cmd_queue: the TXQ number of the command queue
 */
काष्ठा iwl_dqa_enable_cmd अणु
	__le32 cmd_queue;
पूर्ण __packed; /* DQA_CONTROL_CMD_API_S_VER_1 */

/*
 * काष्ठा iwl_tx_ant_cfg_cmd
 * @valid: valid antenna configuration
 */
काष्ठा iwl_tx_ant_cfg_cmd अणु
	__le32 valid;
पूर्ण __packed;

/**
 * काष्ठा iwl_calib_ctrl - Calibration control काष्ठा.
 * Sent as part of the phy configuration command.
 * @flow_trigger: biपंचांगap क्रम which calibrations to perक्रमm according to
 *		flow triggers, using &क्रमागत iwl_calib_cfg
 * @event_trigger: biपंचांगap क्रम which calibrations to perक्रमm according to
 *		event triggers, using &क्रमागत iwl_calib_cfg
 */
काष्ठा iwl_calib_ctrl अणु
	__le32 flow_trigger;
	__le32 event_trigger;
पूर्ण __packed;

/* This क्रमागत defines the biपंचांगap of various calibrations to enable in both
 * init ucode and runसमय ucode through CALIBRATION_CFG_CMD.
 */
क्रमागत iwl_calib_cfg अणु
	IWL_CALIB_CFG_XTAL_IDX			= BIT(0),
	IWL_CALIB_CFG_TEMPERATURE_IDX		= BIT(1),
	IWL_CALIB_CFG_VOLTAGE_READ_IDX		= BIT(2),
	IWL_CALIB_CFG_PAPD_IDX			= BIT(3),
	IWL_CALIB_CFG_TX_PWR_IDX		= BIT(4),
	IWL_CALIB_CFG_DC_IDX			= BIT(5),
	IWL_CALIB_CFG_BB_FILTER_IDX		= BIT(6),
	IWL_CALIB_CFG_LO_LEAKAGE_IDX		= BIT(7),
	IWL_CALIB_CFG_TX_IQ_IDX			= BIT(8),
	IWL_CALIB_CFG_TX_IQ_SKEW_IDX		= BIT(9),
	IWL_CALIB_CFG_RX_IQ_IDX			= BIT(10),
	IWL_CALIB_CFG_RX_IQ_SKEW_IDX		= BIT(11),
	IWL_CALIB_CFG_SENSITIVITY_IDX		= BIT(12),
	IWL_CALIB_CFG_CHAIN_NOISE_IDX		= BIT(13),
	IWL_CALIB_CFG_DISCONNECTED_ANT_IDX	= BIT(14),
	IWL_CALIB_CFG_ANT_COUPLING_IDX		= BIT(15),
	IWL_CALIB_CFG_DAC_IDX			= BIT(16),
	IWL_CALIB_CFG_ABS_IDX			= BIT(17),
	IWL_CALIB_CFG_AGC_IDX			= BIT(18),
पूर्ण;

/**
 * काष्ठा iwl_phy_specअगरic_cfg - specअगरic PHY filter configuration
 *
 * Sent as part of the phy configuration command (v3) to configure specअगरic FW
 * defined PHY filters that can be applied to each antenna.
 *
 * @filter_cfg_chain_a: filter config id क्रम LMAC1 chain A
 * @filter_cfg_chain_b: filter config id क्रम LMAC1 chain B
 * @filter_cfg_chain_c: filter config id क्रम LMAC2 chain A
 * @filter_cfg_chain_d: filter config id क्रम LMAC2 chain B
 * values: 0 - no filter; 0xffffffff - reserved; otherwise - filter id
 */
काष्ठा iwl_phy_specअगरic_cfg अणु
	__le32 filter_cfg_chain_a;
	__le32 filter_cfg_chain_b;
	__le32 filter_cfg_chain_c;
	__le32 filter_cfg_chain_d;
पूर्ण __packed; /* PHY_SPECIFIC_CONFIGURATION_API_VER_1*/

/**
 * काष्ठा iwl_phy_cfg_cmd - Phy configuration command
 *
 * @phy_cfg: PHY configuration value, uses &क्रमागत iwl_fw_phy_cfg
 * @calib_control: calibration control data
 */
काष्ठा iwl_phy_cfg_cmd_v1 अणु
	__le32	phy_cfg;
	काष्ठा iwl_calib_ctrl calib_control;
पूर्ण __packed;

/**
 * काष्ठा iwl_phy_cfg_cmd_v3 - Phy configuration command (v3)
 *
 * @phy_cfg: PHY configuration value, uses &क्रमागत iwl_fw_phy_cfg
 * @calib_control: calibration control data
 * @phy_specअगरic_cfg: configure predefined PHY filters
 */
काष्ठा iwl_phy_cfg_cmd_v3 अणु
	__le32	phy_cfg;
	काष्ठा iwl_calib_ctrl calib_control;
	काष्ठा iwl_phy_specअगरic_cfg phy_specअगरic_cfg;
पूर्ण __packed; /* PHY_CONFIGURATION_CMD_API_S_VER_3 */

/*
 * क्रमागत iwl_dc2dc_config_id - flag ids
 *
 * Ids of dc2dc configuration flags
 */
क्रमागत iwl_dc2dc_config_id अणु
	DCDC_LOW_POWER_MODE_MSK_SET  = 0x1, /* not used */
	DCDC_FREQ_TUNE_SET = 0x2,
पूर्ण; /* MARKER_ID_API_E_VER_1 */

/**
 * काष्ठा iwl_dc2dc_config_cmd - configure dc2dc values
 *
 * (DC2DC_CONFIG_CMD = 0x83)
 *
 * Set/Get & configure dc2dc values.
 * The command always वापसs the current dc2dc values.
 *
 * @flags: set/get dc2dc
 * @enable_low_घातer_mode: not used.
 * @dc2dc_freq_tune0: frequency भागider - digital करोमुख्य
 * @dc2dc_freq_tune1: frequency भागider - analog करोमुख्य
 */
काष्ठा iwl_dc2dc_config_cmd अणु
	__le32 flags;
	__le32 enable_low_घातer_mode; /* not used */
	__le32 dc2dc_freq_tune0;
	__le32 dc2dc_freq_tune1;
पूर्ण __packed; /* DC2DC_CONFIG_CMD_API_S_VER_1 */

/**
 * काष्ठा iwl_dc2dc_config_resp - response क्रम iwl_dc2dc_config_cmd
 *
 * Current dc2dc values वापसed by the FW.
 *
 * @dc2dc_freq_tune0: frequency भागider - digital करोमुख्य
 * @dc2dc_freq_tune1: frequency भागider - analog करोमुख्य
 */
काष्ठा iwl_dc2dc_config_resp अणु
	__le32 dc2dc_freq_tune0;
	__le32 dc2dc_freq_tune1;
पूर्ण __packed; /* DC2DC_CONFIG_RESP_API_S_VER_1 */

#पूर्ण_अगर /* __iwl_fw_api_config_h__ */
