<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2012-2014, 2019-2020 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#अगर_अघोषित __iwl_fw_api_phy_h__
#घोषणा __iwl_fw_api_phy_h__

/**
 * क्रमागत iwl_phy_ops_subcmd_ids - PHY group commands
 */
क्रमागत iwl_phy_ops_subcmd_ids अणु
	/**
	 * @CMD_DTS_MEASUREMENT_TRIGGER_WIDE:
	 * Uses either &काष्ठा iwl_dts_measurement_cmd or
	 * &काष्ठा iwl_ext_dts_measurement_cmd
	 */
	CMD_DTS_MEASUREMENT_TRIGGER_WIDE = 0x0,

	/**
	 * @CTDP_CONFIG_CMD: &काष्ठा iwl_mvm_ctdp_cmd
	 */
	CTDP_CONFIG_CMD = 0x03,

	/**
	 * @TEMP_REPORTING_THRESHOLDS_CMD: &काष्ठा temp_report_ths_cmd
	 */
	TEMP_REPORTING_THRESHOLDS_CMD = 0x04,

	/**
	 * @GEO_TX_POWER_LIMIT: &काष्ठा iwl_geo_tx_घातer_profiles_cmd
	 */
	GEO_TX_POWER_LIMIT = 0x05,

	/**
	 * @PER_PLATFORM_ANT_GAIN_CMD: &काष्ठा iwl_ppag_table_cmd
	 */
	PER_PLATFORM_ANT_GAIN_CMD = 0x07,

	/**
	 * @CT_KILL_NOTIFICATION: &काष्ठा ct_समाप्त_notअगर
	 */
	CT_KILL_NOTIFICATION = 0xFE,

	/**
	 * @DTS_MEASUREMENT_NOTIF_WIDE:
	 * &काष्ठा iwl_dts_measurement_notअगर_v1 or
	 * &काष्ठा iwl_dts_measurement_notअगर_v2
	 */
	DTS_MEASUREMENT_NOTIF_WIDE = 0xFF,
पूर्ण;

/* DTS measurements */

क्रमागत iwl_dts_measurement_flags अणु
	DTS_TRIGGER_CMD_FLAGS_TEMP	= BIT(0),
	DTS_TRIGGER_CMD_FLAGS_VOLT	= BIT(1),
पूर्ण;

/**
 * काष्ठा iwl_dts_measurement_cmd - request DTS temp and/or voltage measurements
 *
 * @flags: indicates which measurements we want as specअगरied in
 *	&क्रमागत iwl_dts_measurement_flags
 */
काष्ठा iwl_dts_measurement_cmd अणु
	__le32 flags;
पूर्ण __packed; /* TEMPERATURE_MEASUREMENT_TRIGGER_CMD_S */

/**
* क्रमागत iwl_dts_control_measurement_mode - DTS measurement type
* @DTS_AUTOMATIC: Automatic mode (full SW control). Provide temperature पढ़ो
*                 back (latest value. Not रुकोing क्रम new value). Use स्वतःmatic
*                 SW DTS configuration.
* @DTS_REQUEST_READ: Request DTS पढ़ो. Configure DTS with manual settings,
*                    trigger DTS पढ़ोing and provide पढ़ो back temperature पढ़ो
*                    when available.
* @DTS_OVER_WRITE: over-ग_लिखो the DTS temperatures in the SW until next पढ़ो
* @DTS_सूचीECT_WITHOUT_MEASURE: DTS वापसs its latest temperature result,
*                              without measurement trigger.
*/
क्रमागत iwl_dts_control_measurement_mode अणु
	DTS_AUTOMATIC			= 0,
	DTS_REQUEST_READ		= 1,
	DTS_OVER_WRITE			= 2,
	DTS_सूचीECT_WITHOUT_MEASURE	= 3,
पूर्ण;

/**
* क्रमागत iwl_dts_used - DTS to use or used क्रम measurement in the DTS request
* @DTS_USE_TOP: Top
* @DTS_USE_CHAIN_A: chain A
* @DTS_USE_CHAIN_B: chain B
* @DTS_USE_CHAIN_C: chain C
* @XTAL_TEMPERATURE: पढ़ो temperature from xtal
*/
क्रमागत iwl_dts_used अणु
	DTS_USE_TOP		= 0,
	DTS_USE_CHAIN_A		= 1,
	DTS_USE_CHAIN_B		= 2,
	DTS_USE_CHAIN_C		= 3,
	XTAL_TEMPERATURE	= 4,
पूर्ण;

/**
* क्रमागत iwl_dts_bit_mode - bit-mode to use in DTS request पढ़ो mode
* @DTS_BIT6_MODE: bit 6 mode
* @DTS_BIT8_MODE: bit 8 mode
*/
क्रमागत iwl_dts_bit_mode अणु
	DTS_BIT6_MODE	= 0,
	DTS_BIT8_MODE	= 1,
पूर्ण;

/**
 * काष्ठा iwl_ext_dts_measurement_cmd - request extended DTS temp measurements
 * @control_mode: see &क्रमागत iwl_dts_control_measurement_mode
 * @temperature: used when over ग_लिखो DTS mode is selected
 * @sensor: set temperature sensor to use. See &क्रमागत iwl_dts_used
 * @avg_factor: average factor to DTS in request DTS पढ़ो mode
 * @bit_mode: value defines the DTS bit mode to use. See &क्रमागत iwl_dts_bit_mode
 * @step_duration: step duration क्रम the DTS
 */
काष्ठा iwl_ext_dts_measurement_cmd अणु
	__le32 control_mode;
	__le32 temperature;
	__le32 sensor;
	__le32 avg_factor;
	__le32 bit_mode;
	__le32 step_duration;
पूर्ण __packed; /* XVT_FW_DTS_CONTROL_MEASUREMENT_REQUEST_API_S */

/**
 * काष्ठा iwl_dts_measurement_notअगर_v1 - measurements notअगरication
 *
 * @temp: the measured temperature
 * @voltage: the measured voltage
 */
काष्ठा iwl_dts_measurement_notअगर_v1 अणु
	__le32 temp;
	__le32 voltage;
पूर्ण __packed; /* TEMPERATURE_MEASUREMENT_TRIGGER_NTFY_S_VER_1*/

/**
 * काष्ठा iwl_dts_measurement_notअगर_v2 - measurements notअगरication
 *
 * @temp: the measured temperature
 * @voltage: the measured voltage
 * @threshold_idx: the trip index that was crossed
 */
काष्ठा iwl_dts_measurement_notअगर_v2 अणु
	__le32 temp;
	__le32 voltage;
	__le32 threshold_idx;
पूर्ण __packed; /* TEMPERATURE_MEASUREMENT_TRIGGER_NTFY_S_VER_2 */

/**
 * काष्ठा iwl_dts_measurement_resp - measurements response
 *
 * @temp: the measured temperature
 */
काष्ठा iwl_dts_measurement_resp अणु
	__le32 temp;
पूर्ण __packed; /* CMD_DTS_MEASUREMENT_RSP_API_S_VER_1 */

/**
 * काष्ठा ct_समाप्त_notअगर - CT-समाप्त entry notअगरication
 *
 * @temperature: the current temperature in celsius
 * @reserved: reserved
 */
काष्ठा ct_समाप्त_notअगर अणु
	__le16 temperature;
	__le16 reserved;
पूर्ण __packed; /* GRP_PHY_CT_KILL_NTF */

/**
* क्रमागत ctdp_cmd_operation - CTDP command operations
* @CTDP_CMD_OPERATION_START: update the current budget
* @CTDP_CMD_OPERATION_STOP: stop ctdp
* @CTDP_CMD_OPERATION_REPORT: get the average budget
*/
क्रमागत iwl_mvm_ctdp_cmd_operation अणु
	CTDP_CMD_OPERATION_START	= 0x1,
	CTDP_CMD_OPERATION_STOP		= 0x2,
	CTDP_CMD_OPERATION_REPORT	= 0x4,
पूर्ण;/* CTDP_CMD_OPERATION_TYPE_E */

/**
 * काष्ठा iwl_mvm_ctdp_cmd - track and manage the FW घातer consumption budget
 *
 * @operation: see &क्रमागत iwl_mvm_ctdp_cmd_operation
 * @budget: the budget in milliwatt
 * @winकरोw_size: defined in API but not used
 */
काष्ठा iwl_mvm_ctdp_cmd अणु
	__le32 operation;
	__le32 budget;
	__le32 winकरोw_size;
पूर्ण __packed;

#घोषणा IWL_MAX_DTS_TRIPS	8

/**
 * काष्ठा temp_report_ths_cmd - set temperature thresholds
 *
 * @num_temps: number of temperature thresholds passed
 * @thresholds: array with the thresholds to be configured
 */
काष्ठा temp_report_ths_cmd अणु
	__le32 num_temps;
	__le16 thresholds[IWL_MAX_DTS_TRIPS];
पूर्ण __packed; /* GRP_PHY_TEMP_REPORTING_THRESHOLDS_CMD */

#पूर्ण_अगर /* __iwl_fw_api_phy_h__ */
