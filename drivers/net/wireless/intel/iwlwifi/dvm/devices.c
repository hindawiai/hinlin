<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
 *
 * Copyright(c) 2008 - 2014 Intel Corporation. All rights reserved.
 * Copyright (C) 2019 Intel Corporation
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <linuxwअगरi@पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 *****************************************************************************/

#समावेश <linux/units.h>

/*
 * DVM device-specअगरic data & functions
 */
#समावेश "iwl-io.h"
#समावेश "iwl-prph.h"
#समावेश "iwl-eeprom-parse.h"

#समावेश "agn.h"
#समावेश "dev.h"
#समावेश "commands.h"


/*
 * 1000 series
 * ===========
 */

/*
 * For 1000, use advance thermal throttling critical temperature threshold,
 * but legacy thermal management implementation क्रम now.
 * This is क्रम the reason of 1000 uCode using advance thermal throttling API
 * but not implement ct_समाप्त_निकास based on ct_समाप्त निकास temperature
 * so the thermal throttling will still based on legacy thermal throttling
 * management.
 * The code here need to be modअगरied once 1000 uCode has the advanced thermal
 * throttling algorithm in place
 */
अटल व्योम iwl1000_set_ct_threshold(काष्ठा iwl_priv *priv)
अणु
	/* want Celsius */
	priv->hw_params.ct_समाप्त_threshold = CT_KILL_THRESHOLD_LEGACY;
	priv->hw_params.ct_समाप्त_निकास_threshold = CT_KILL_EXIT_THRESHOLD;
पूर्ण

/* NIC configuration क्रम 1000 series */
अटल व्योम iwl1000_nic_config(काष्ठा iwl_priv *priv)
अणु
	/* Setting digital SVR क्रम 1000 card to 1.32V */
	/* locking is acquired in iwl_set_bits_mask_prph() function */
	iwl_set_bits_mask_prph(priv->trans, APMG_DIGITAL_SVR_REG,
				APMG_SVR_DIGITAL_VOLTAGE_1_32,
				~APMG_SVR_VOLTAGE_CONFIG_BIT_MSK);
पूर्ण

/**
 * iwl_beacon_समय_mask_low - mask of lower 32 bit of beacon समय
 * @priv: poपूर्णांकer to iwl_priv data काष्ठाure
 * @tsf_bits: number of bits need to shअगरt क्रम masking)
 */
अटल अंतरभूत u32 iwl_beacon_समय_mask_low(काष्ठा iwl_priv *priv,
					   u16 tsf_bits)
अणु
	वापस (1 << tsf_bits) - 1;
पूर्ण

/**
 * iwl_beacon_समय_mask_high - mask of higher 32 bit of beacon समय
 * @priv: poपूर्णांकer to iwl_priv data काष्ठाure
 * @tsf_bits: number of bits need to shअगरt क्रम masking)
 */
अटल अंतरभूत u32 iwl_beacon_समय_mask_high(काष्ठा iwl_priv *priv,
					    u16 tsf_bits)
अणु
	वापस ((1 << (32 - tsf_bits)) - 1) << tsf_bits;
पूर्ण

/*
 * extended beacon समय क्रमmat
 * समय in usec will be changed पूर्णांकo a 32-bit value in extended:पूर्णांकernal क्रमmat
 * the extended part is the beacon counts
 * the पूर्णांकernal part is the समय in usec within one beacon पूर्णांकerval
 */
अटल u32 iwl_usecs_to_beacons(काष्ठा iwl_priv *priv, u32 usec,
				u32 beacon_पूर्णांकerval)
अणु
	u32 quot;
	u32 rem;
	u32 पूर्णांकerval = beacon_पूर्णांकerval * TIME_UNIT;

	अगर (!पूर्णांकerval || !usec)
		वापस 0;

	quot = (usec / पूर्णांकerval) &
		(iwl_beacon_समय_mask_high(priv, IWLAGN_EXT_BEACON_TIME_POS) >>
		IWLAGN_EXT_BEACON_TIME_POS);
	rem = (usec % पूर्णांकerval) & iwl_beacon_समय_mask_low(priv,
				   IWLAGN_EXT_BEACON_TIME_POS);

	वापस (quot << IWLAGN_EXT_BEACON_TIME_POS) + rem;
पूर्ण

/* base is usually what we get from ucode with each received frame,
 * the same as HW समयr counter counting करोwn
 */
अटल __le32 iwl_add_beacon_समय(काष्ठा iwl_priv *priv, u32 base,
			   u32 adकरोn, u32 beacon_पूर्णांकerval)
अणु
	u32 base_low = base & iwl_beacon_समय_mask_low(priv,
				IWLAGN_EXT_BEACON_TIME_POS);
	u32 adकरोn_low = adकरोn & iwl_beacon_समय_mask_low(priv,
				IWLAGN_EXT_BEACON_TIME_POS);
	u32 पूर्णांकerval = beacon_पूर्णांकerval * TIME_UNIT;
	u32 res = (base & iwl_beacon_समय_mask_high(priv,
				IWLAGN_EXT_BEACON_TIME_POS)) +
				(adकरोn & iwl_beacon_समय_mask_high(priv,
				IWLAGN_EXT_BEACON_TIME_POS));

	अगर (base_low > adकरोn_low)
		res += base_low - adकरोn_low;
	अन्यथा अगर (base_low < adकरोn_low) अणु
		res += पूर्णांकerval + base_low - adकरोn_low;
		res += (1 << IWLAGN_EXT_BEACON_TIME_POS);
	पूर्ण अन्यथा
		res += (1 << IWLAGN_EXT_BEACON_TIME_POS);

	वापस cpu_to_le32(res);
पूर्ण

अटल स्थिर काष्ठा iwl_sensitivity_ranges iwl1000_sensitivity = अणु
	.min_nrg_cck = 95,
	.स्वतः_corr_min_ofdm = 90,
	.स्वतः_corr_min_ofdm_mrc = 170,
	.स्वतः_corr_min_ofdm_x1 = 120,
	.स्वतः_corr_min_ofdm_mrc_x1 = 240,

	.स्वतः_corr_max_ofdm = 120,
	.स्वतः_corr_max_ofdm_mrc = 210,
	.स्वतः_corr_max_ofdm_x1 = 155,
	.स्वतः_corr_max_ofdm_mrc_x1 = 290,

	.स्वतः_corr_min_cck = 125,
	.स्वतः_corr_max_cck = 200,
	.स्वतः_corr_min_cck_mrc = 170,
	.स्वतः_corr_max_cck_mrc = 400,
	.nrg_th_cck = 95,
	.nrg_th_ofdm = 95,

	.barker_corr_th_min = 190,
	.barker_corr_th_min_mrc = 390,
	.nrg_th_cca = 62,
पूर्ण;

अटल व्योम iwl1000_hw_set_hw_params(काष्ठा iwl_priv *priv)
अणु
	iwl1000_set_ct_threshold(priv);

	/* Set initial sensitivity parameters */
	priv->hw_params.sens = &iwl1000_sensitivity;
पूर्ण

स्थिर काष्ठा iwl_dvm_cfg iwl_dvm_1000_cfg = अणु
	.set_hw_params = iwl1000_hw_set_hw_params,
	.nic_config = iwl1000_nic_config,
	.temperature = iwlagn_temperature,
	.support_ct_समाप्त_निकास = true,
	.plcp_delta_threshold = IWL_MAX_PLCP_ERR_EXT_LONG_THRESHOLD_DEF,
	.chain_noise_scale = 1000,
पूर्ण;


/*
 * 2000 series
 * ===========
 */

अटल व्योम iwl2000_set_ct_threshold(काष्ठा iwl_priv *priv)
अणु
	/* want Celsius */
	priv->hw_params.ct_समाप्त_threshold = CT_KILL_THRESHOLD;
	priv->hw_params.ct_समाप्त_निकास_threshold = CT_KILL_EXIT_THRESHOLD;
पूर्ण

/* NIC configuration क्रम 2000 series */
अटल व्योम iwl2000_nic_config(काष्ठा iwl_priv *priv)
अणु
	iwl_set_bit(priv->trans, CSR_GP_DRIVER_REG,
		    CSR_GP_DRIVER_REG_BIT_RADIO_IQ_INVER);
पूर्ण

अटल स्थिर काष्ठा iwl_sensitivity_ranges iwl2000_sensitivity = अणु
	.min_nrg_cck = 97,
	.स्वतः_corr_min_ofdm = 80,
	.स्वतः_corr_min_ofdm_mrc = 128,
	.स्वतः_corr_min_ofdm_x1 = 105,
	.स्वतः_corr_min_ofdm_mrc_x1 = 192,

	.स्वतः_corr_max_ofdm = 145,
	.स्वतः_corr_max_ofdm_mrc = 232,
	.स्वतः_corr_max_ofdm_x1 = 110,
	.स्वतः_corr_max_ofdm_mrc_x1 = 232,

	.स्वतः_corr_min_cck = 125,
	.स्वतः_corr_max_cck = 175,
	.स्वतः_corr_min_cck_mrc = 160,
	.स्वतः_corr_max_cck_mrc = 310,
	.nrg_th_cck = 97,
	.nrg_th_ofdm = 100,

	.barker_corr_th_min = 190,
	.barker_corr_th_min_mrc = 390,
	.nrg_th_cca = 62,
पूर्ण;

अटल व्योम iwl2000_hw_set_hw_params(काष्ठा iwl_priv *priv)
अणु
	iwl2000_set_ct_threshold(priv);

	/* Set initial sensitivity parameters */
	priv->hw_params.sens = &iwl2000_sensitivity;
पूर्ण

स्थिर काष्ठा iwl_dvm_cfg iwl_dvm_2000_cfg = अणु
	.set_hw_params = iwl2000_hw_set_hw_params,
	.nic_config = iwl2000_nic_config,
	.temperature = iwlagn_temperature,
	.adv_thermal_throttle = true,
	.support_ct_समाप्त_निकास = true,
	.plcp_delta_threshold = IWL_MAX_PLCP_ERR_THRESHOLD_DEF,
	.chain_noise_scale = 1000,
	.hd_v2 = true,
	.need_temp_offset_calib = true,
	.temp_offset_v2 = true,
पूर्ण;

स्थिर काष्ठा iwl_dvm_cfg iwl_dvm_105_cfg = अणु
	.set_hw_params = iwl2000_hw_set_hw_params,
	.nic_config = iwl2000_nic_config,
	.temperature = iwlagn_temperature,
	.adv_thermal_throttle = true,
	.support_ct_समाप्त_निकास = true,
	.plcp_delta_threshold = IWL_MAX_PLCP_ERR_THRESHOLD_DEF,
	.chain_noise_scale = 1000,
	.hd_v2 = true,
	.need_temp_offset_calib = true,
	.temp_offset_v2 = true,
	.adv_pm = true,
पूर्ण;

अटल स्थिर काष्ठा iwl_dvm_bt_params iwl2030_bt_params = अणु
	/* Due to bluetooth, we transmit 2.4 GHz probes only on antenna A */
	.advanced_bt_coexist = true,
	.agg_समय_limit = BT_AGG_THRESHOLD_DEF,
	.bt_init_traffic_load = IWL_BT_COEX_TRAFFIC_LOAD_NONE,
	.bt_prio_boost = IWLAGN_BT_PRIO_BOOST_DEFAULT32,
	.bt_sco_disable = true,
	.bt_session_2 = true,
पूर्ण;

स्थिर काष्ठा iwl_dvm_cfg iwl_dvm_2030_cfg = अणु
	.set_hw_params = iwl2000_hw_set_hw_params,
	.nic_config = iwl2000_nic_config,
	.temperature = iwlagn_temperature,
	.adv_thermal_throttle = true,
	.support_ct_समाप्त_निकास = true,
	.plcp_delta_threshold = IWL_MAX_PLCP_ERR_THRESHOLD_DEF,
	.chain_noise_scale = 1000,
	.hd_v2 = true,
	.bt_params = &iwl2030_bt_params,
	.need_temp_offset_calib = true,
	.temp_offset_v2 = true,
	.adv_pm = true,
पूर्ण;

/*
 * 5000 series
 * ===========
 */

/* NIC configuration क्रम 5000 series */
अटल स्थिर काष्ठा iwl_sensitivity_ranges iwl5000_sensitivity = अणु
	.min_nrg_cck = 100,
	.स्वतः_corr_min_ofdm = 90,
	.स्वतः_corr_min_ofdm_mrc = 170,
	.स्वतः_corr_min_ofdm_x1 = 105,
	.स्वतः_corr_min_ofdm_mrc_x1 = 220,

	.स्वतः_corr_max_ofdm = 120,
	.स्वतः_corr_max_ofdm_mrc = 210,
	.स्वतः_corr_max_ofdm_x1 = 120,
	.स्वतः_corr_max_ofdm_mrc_x1 = 240,

	.स्वतः_corr_min_cck = 125,
	.स्वतः_corr_max_cck = 200,
	.स्वतः_corr_min_cck_mrc = 200,
	.स्वतः_corr_max_cck_mrc = 400,
	.nrg_th_cck = 100,
	.nrg_th_ofdm = 100,

	.barker_corr_th_min = 190,
	.barker_corr_th_min_mrc = 390,
	.nrg_th_cca = 62,
पूर्ण;

अटल स्थिर काष्ठा iwl_sensitivity_ranges iwl5150_sensitivity = अणु
	.min_nrg_cck = 95,
	.स्वतः_corr_min_ofdm = 90,
	.स्वतः_corr_min_ofdm_mrc = 170,
	.स्वतः_corr_min_ofdm_x1 = 105,
	.स्वतः_corr_min_ofdm_mrc_x1 = 220,

	.स्वतः_corr_max_ofdm = 120,
	.स्वतः_corr_max_ofdm_mrc = 210,
	/* max = min क्रम perक्रमmance bug in 5150 DSP */
	.स्वतः_corr_max_ofdm_x1 = 105,
	.स्वतः_corr_max_ofdm_mrc_x1 = 220,

	.स्वतः_corr_min_cck = 125,
	.स्वतः_corr_max_cck = 200,
	.स्वतः_corr_min_cck_mrc = 170,
	.स्वतः_corr_max_cck_mrc = 400,
	.nrg_th_cck = 95,
	.nrg_th_ofdm = 95,

	.barker_corr_th_min = 190,
	.barker_corr_th_min_mrc = 390,
	.nrg_th_cca = 62,
पूर्ण;

#घोषणा IWL_5150_VOLTAGE_TO_TEMPERATURE_COEFF	(-5)

अटल s32 iwl_temp_calib_to_offset(काष्ठा iwl_priv *priv)
अणु
	u16 temperature, voltage;

	temperature = le16_to_cpu(priv->nvm_data->kelvin_temperature);
	voltage = le16_to_cpu(priv->nvm_data->kelvin_voltage);

	/* offset = temp - volt / coeff */
	वापस (s32)(temperature -
			voltage / IWL_5150_VOLTAGE_TO_TEMPERATURE_COEFF);
पूर्ण

अटल व्योम iwl5150_set_ct_threshold(काष्ठा iwl_priv *priv)
अणु
	स्थिर s32 volt2temp_coef = IWL_5150_VOLTAGE_TO_TEMPERATURE_COEFF;
	s32 threshold = (s32)celsius_to_kelvin(CT_KILL_THRESHOLD_LEGACY) -
			iwl_temp_calib_to_offset(priv);

	priv->hw_params.ct_समाप्त_threshold = threshold * volt2temp_coef;
पूर्ण

अटल व्योम iwl5000_set_ct_threshold(काष्ठा iwl_priv *priv)
अणु
	/* want Celsius */
	priv->hw_params.ct_समाप्त_threshold = CT_KILL_THRESHOLD_LEGACY;
पूर्ण

अटल व्योम iwl5000_hw_set_hw_params(काष्ठा iwl_priv *priv)
अणु
	iwl5000_set_ct_threshold(priv);

	/* Set initial sensitivity parameters */
	priv->hw_params.sens = &iwl5000_sensitivity;
पूर्ण

अटल व्योम iwl5150_hw_set_hw_params(काष्ठा iwl_priv *priv)
अणु
	iwl5150_set_ct_threshold(priv);

	/* Set initial sensitivity parameters */
	priv->hw_params.sens = &iwl5150_sensitivity;
पूर्ण

अटल व्योम iwl5150_temperature(काष्ठा iwl_priv *priv)
अणु
	u32 vt = 0;
	s32 offset =  iwl_temp_calib_to_offset(priv);

	vt = le32_to_cpu(priv->statistics.common.temperature);
	vt = vt / IWL_5150_VOLTAGE_TO_TEMPERATURE_COEFF + offset;
	/* now vt hold the temperature in Kelvin */
	priv->temperature = kelvin_to_celsius(vt);
	iwl_tt_handler(priv);
पूर्ण

अटल पूर्णांक iwl5000_hw_channel_चयन(काष्ठा iwl_priv *priv,
				     काष्ठा ieee80211_channel_चयन *ch_चयन)
अणु
	/*
	 * MULTI-FIXME
	 * See iwlagn_mac_channel_चयन.
	 */
	काष्ठा iwl_rxon_context *ctx = &priv->contexts[IWL_RXON_CTX_BSS];
	काष्ठा iwl5000_channel_चयन_cmd cmd;
	u32 चयन_समय_in_usec, ucode_चयन_समय;
	u16 ch;
	u32 tsf_low;
	u8 चयन_count;
	u16 beacon_पूर्णांकerval = le16_to_cpu(ctx->timing.beacon_पूर्णांकerval);
	काष्ठा ieee80211_vअगर *vअगर = ctx->vअगर;
	काष्ठा iwl_host_cmd hcmd = अणु
		.id = REPLY_CHANNEL_SWITCH,
		.len = अणु माप(cmd), पूर्ण,
		.data = अणु &cmd, पूर्ण,
	पूर्ण;

	cmd.band = priv->band == NL80211_BAND_2GHZ;
	ch = ch_चयन->chandef.chan->hw_value;
	IWL_DEBUG_11H(priv, "channel switch from %d to %d\n",
		      ctx->active.channel, ch);
	cmd.channel = cpu_to_le16(ch);
	cmd.rxon_flags = ctx->staging.flags;
	cmd.rxon_filter_flags = ctx->staging.filter_flags;
	चयन_count = ch_चयन->count;
	tsf_low = ch_चयन->बारtamp & 0x0ffffffff;
	/*
	 * calculate the ucode channel चयन समय
	 * adding TSF as one of the factor क्रम when to चयन
	 */
	अगर ((priv->ucode_beacon_समय > tsf_low) && beacon_पूर्णांकerval) अणु
		अगर (चयन_count > ((priv->ucode_beacon_समय - tsf_low) /
		    beacon_पूर्णांकerval)) अणु
			चयन_count -= (priv->ucode_beacon_समय -
				tsf_low) / beacon_पूर्णांकerval;
		पूर्ण अन्यथा
			चयन_count = 0;
	पूर्ण
	अगर (चयन_count <= 1)
		cmd.चयन_समय = cpu_to_le32(priv->ucode_beacon_समय);
	अन्यथा अणु
		चयन_समय_in_usec =
			vअगर->bss_conf.beacon_पूर्णांक * चयन_count * TIME_UNIT;
		ucode_चयन_समय = iwl_usecs_to_beacons(priv,
							 चयन_समय_in_usec,
							 beacon_पूर्णांकerval);
		cmd.चयन_समय = iwl_add_beacon_समय(priv,
						      priv->ucode_beacon_समय,
						      ucode_चयन_समय,
						      beacon_पूर्णांकerval);
	पूर्ण
	IWL_DEBUG_11H(priv, "uCode time for the switch is 0x%x\n",
		      cmd.चयन_समय);
	cmd.expect_beacon =
		ch_चयन->chandef.chan->flags & IEEE80211_CHAN_RADAR;

	वापस iwl_dvm_send_cmd(priv, &hcmd);
पूर्ण

स्थिर काष्ठा iwl_dvm_cfg iwl_dvm_5000_cfg = अणु
	.set_hw_params = iwl5000_hw_set_hw_params,
	.set_channel_चयन = iwl5000_hw_channel_चयन,
	.temperature = iwlagn_temperature,
	.plcp_delta_threshold = IWL_MAX_PLCP_ERR_LONG_THRESHOLD_DEF,
	.chain_noise_scale = 1000,
	.no_idle_support = true,
पूर्ण;

स्थिर काष्ठा iwl_dvm_cfg iwl_dvm_5150_cfg = अणु
	.set_hw_params = iwl5150_hw_set_hw_params,
	.set_channel_चयन = iwl5000_hw_channel_चयन,
	.temperature = iwl5150_temperature,
	.plcp_delta_threshold = IWL_MAX_PLCP_ERR_LONG_THRESHOLD_DEF,
	.chain_noise_scale = 1000,
	.no_idle_support = true,
	.no_xtal_calib = true,
पूर्ण;



/*
 * 6000 series
 * ===========
 */

अटल व्योम iwl6000_set_ct_threshold(काष्ठा iwl_priv *priv)
अणु
	/* want Celsius */
	priv->hw_params.ct_समाप्त_threshold = CT_KILL_THRESHOLD;
	priv->hw_params.ct_समाप्त_निकास_threshold = CT_KILL_EXIT_THRESHOLD;
पूर्ण

/* NIC configuration क्रम 6000 series */
अटल व्योम iwl6000_nic_config(काष्ठा iwl_priv *priv)
अणु
	चयन (priv->trans->trans_cfg->device_family) अणु
	हाल IWL_DEVICE_FAMILY_6005:
	हाल IWL_DEVICE_FAMILY_6030:
	हाल IWL_DEVICE_FAMILY_6000:
		अवरोध;
	हाल IWL_DEVICE_FAMILY_6000i:
		/* 2x2 IPA phy type */
		iwl_ग_लिखो32(priv->trans, CSR_GP_DRIVER_REG,
			     CSR_GP_DRIVER_REG_BIT_RADIO_SKU_2x2_IPA);
		अवरोध;
	हाल IWL_DEVICE_FAMILY_6050:
		/* Indicate calibration version to uCode. */
		अगर (priv->nvm_data->calib_version >= 6)
			iwl_set_bit(priv->trans, CSR_GP_DRIVER_REG,
					CSR_GP_DRIVER_REG_BIT_CALIB_VERSION6);
		अवरोध;
	हाल IWL_DEVICE_FAMILY_6150:
		/* Indicate calibration version to uCode. */
		अगर (priv->nvm_data->calib_version >= 6)
			iwl_set_bit(priv->trans, CSR_GP_DRIVER_REG,
					CSR_GP_DRIVER_REG_BIT_CALIB_VERSION6);
		iwl_set_bit(priv->trans, CSR_GP_DRIVER_REG,
			    CSR_GP_DRIVER_REG_BIT_6050_1x2);
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iwl_sensitivity_ranges iwl6000_sensitivity = अणु
	.min_nrg_cck = 110,
	.स्वतः_corr_min_ofdm = 80,
	.स्वतः_corr_min_ofdm_mrc = 128,
	.स्वतः_corr_min_ofdm_x1 = 105,
	.स्वतः_corr_min_ofdm_mrc_x1 = 192,

	.स्वतः_corr_max_ofdm = 145,
	.स्वतः_corr_max_ofdm_mrc = 232,
	.स्वतः_corr_max_ofdm_x1 = 110,
	.स्वतः_corr_max_ofdm_mrc_x1 = 232,

	.स्वतः_corr_min_cck = 125,
	.स्वतः_corr_max_cck = 175,
	.स्वतः_corr_min_cck_mrc = 160,
	.स्वतः_corr_max_cck_mrc = 310,
	.nrg_th_cck = 110,
	.nrg_th_ofdm = 110,

	.barker_corr_th_min = 190,
	.barker_corr_th_min_mrc = 336,
	.nrg_th_cca = 62,
पूर्ण;

अटल व्योम iwl6000_hw_set_hw_params(काष्ठा iwl_priv *priv)
अणु
	iwl6000_set_ct_threshold(priv);

	/* Set initial sensitivity parameters */
	priv->hw_params.sens = &iwl6000_sensitivity;

पूर्ण

अटल पूर्णांक iwl6000_hw_channel_चयन(काष्ठा iwl_priv *priv,
				     काष्ठा ieee80211_channel_चयन *ch_चयन)
अणु
	/*
	 * MULTI-FIXME
	 * See iwlagn_mac_channel_चयन.
	 */
	काष्ठा iwl_rxon_context *ctx = &priv->contexts[IWL_RXON_CTX_BSS];
	काष्ठा iwl6000_channel_चयन_cmd *cmd;
	u32 चयन_समय_in_usec, ucode_चयन_समय;
	u16 ch;
	u32 tsf_low;
	u8 चयन_count;
	u16 beacon_पूर्णांकerval = le16_to_cpu(ctx->timing.beacon_पूर्णांकerval);
	काष्ठा ieee80211_vअगर *vअगर = ctx->vअगर;
	काष्ठा iwl_host_cmd hcmd = अणु
		.id = REPLY_CHANNEL_SWITCH,
		.len = अणु माप(*cmd), पूर्ण,
		.dataflags[0] = IWL_HCMD_DFL_NOCOPY,
	पूर्ण;
	पूर्णांक err;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	hcmd.data[0] = cmd;

	cmd->band = priv->band == NL80211_BAND_2GHZ;
	ch = ch_चयन->chandef.chan->hw_value;
	IWL_DEBUG_11H(priv, "channel switch from %u to %u\n",
		      ctx->active.channel, ch);
	cmd->channel = cpu_to_le16(ch);
	cmd->rxon_flags = ctx->staging.flags;
	cmd->rxon_filter_flags = ctx->staging.filter_flags;
	चयन_count = ch_चयन->count;
	tsf_low = ch_चयन->बारtamp & 0x0ffffffff;
	/*
	 * calculate the ucode channel चयन समय
	 * adding TSF as one of the factor क्रम when to चयन
	 */
	अगर ((priv->ucode_beacon_समय > tsf_low) && beacon_पूर्णांकerval) अणु
		अगर (चयन_count > ((priv->ucode_beacon_समय - tsf_low) /
		    beacon_पूर्णांकerval)) अणु
			चयन_count -= (priv->ucode_beacon_समय -
				tsf_low) / beacon_पूर्णांकerval;
		पूर्ण अन्यथा
			चयन_count = 0;
	पूर्ण
	अगर (चयन_count <= 1)
		cmd->चयन_समय = cpu_to_le32(priv->ucode_beacon_समय);
	अन्यथा अणु
		चयन_समय_in_usec =
			vअगर->bss_conf.beacon_पूर्णांक * चयन_count * TIME_UNIT;
		ucode_चयन_समय = iwl_usecs_to_beacons(priv,
							 चयन_समय_in_usec,
							 beacon_पूर्णांकerval);
		cmd->चयन_समय = iwl_add_beacon_समय(priv,
						       priv->ucode_beacon_समय,
						       ucode_चयन_समय,
						       beacon_पूर्णांकerval);
	पूर्ण
	IWL_DEBUG_11H(priv, "uCode time for the switch is 0x%x\n",
		      cmd->चयन_समय);
	cmd->expect_beacon =
		ch_चयन->chandef.chan->flags & IEEE80211_CHAN_RADAR;

	err = iwl_dvm_send_cmd(priv, &hcmd);
	kमुक्त(cmd);
	वापस err;
पूर्ण

स्थिर काष्ठा iwl_dvm_cfg iwl_dvm_6000_cfg = अणु
	.set_hw_params = iwl6000_hw_set_hw_params,
	.set_channel_चयन = iwl6000_hw_channel_चयन,
	.nic_config = iwl6000_nic_config,
	.temperature = iwlagn_temperature,
	.adv_thermal_throttle = true,
	.support_ct_समाप्त_निकास = true,
	.plcp_delta_threshold = IWL_MAX_PLCP_ERR_THRESHOLD_DEF,
	.chain_noise_scale = 1000,
पूर्ण;

स्थिर काष्ठा iwl_dvm_cfg iwl_dvm_6005_cfg = अणु
	.set_hw_params = iwl6000_hw_set_hw_params,
	.set_channel_चयन = iwl6000_hw_channel_चयन,
	.nic_config = iwl6000_nic_config,
	.temperature = iwlagn_temperature,
	.adv_thermal_throttle = true,
	.support_ct_समाप्त_निकास = true,
	.plcp_delta_threshold = IWL_MAX_PLCP_ERR_THRESHOLD_DEF,
	.chain_noise_scale = 1000,
	.need_temp_offset_calib = true,
पूर्ण;

स्थिर काष्ठा iwl_dvm_cfg iwl_dvm_6050_cfg = अणु
	.set_hw_params = iwl6000_hw_set_hw_params,
	.set_channel_चयन = iwl6000_hw_channel_चयन,
	.nic_config = iwl6000_nic_config,
	.temperature = iwlagn_temperature,
	.adv_thermal_throttle = true,
	.support_ct_समाप्त_निकास = true,
	.plcp_delta_threshold = IWL_MAX_PLCP_ERR_THRESHOLD_DEF,
	.chain_noise_scale = 1500,
पूर्ण;

अटल स्थिर काष्ठा iwl_dvm_bt_params iwl6000_bt_params = अणु
	/* Due to bluetooth, we transmit 2.4 GHz probes only on antenna A */
	.advanced_bt_coexist = true,
	.agg_समय_limit = BT_AGG_THRESHOLD_DEF,
	.bt_init_traffic_load = IWL_BT_COEX_TRAFFIC_LOAD_NONE,
	.bt_prio_boost = IWLAGN_BT_PRIO_BOOST_DEFAULT,
	.bt_sco_disable = true,
पूर्ण;

स्थिर काष्ठा iwl_dvm_cfg iwl_dvm_6030_cfg = अणु
	.set_hw_params = iwl6000_hw_set_hw_params,
	.set_channel_चयन = iwl6000_hw_channel_चयन,
	.nic_config = iwl6000_nic_config,
	.temperature = iwlagn_temperature,
	.adv_thermal_throttle = true,
	.support_ct_समाप्त_निकास = true,
	.plcp_delta_threshold = IWL_MAX_PLCP_ERR_THRESHOLD_DEF,
	.chain_noise_scale = 1000,
	.bt_params = &iwl6000_bt_params,
	.need_temp_offset_calib = true,
	.adv_pm = true,
पूर्ण;
