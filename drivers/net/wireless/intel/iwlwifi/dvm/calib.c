<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2005-2014 Intel Corporation
 */
#समावेश <linux/slab.h>
#समावेश <net/mac80211.h>

#समावेश "iwl-trans.h"

#समावेश "dev.h"
#समावेश "calib.h"
#समावेश "agn.h"

/*****************************************************************************
 * INIT calibrations framework
 *****************************************************************************/

/* Opaque calibration results */
काष्ठा iwl_calib_result अणु
	काष्ठा list_head list;
	माप_प्रकार cmd_len;
	काष्ठा iwl_calib_hdr hdr;
	/* data follows */
पूर्ण;

काष्ठा statistics_general_data अणु
	u32 beacon_silence_rssi_a;
	u32 beacon_silence_rssi_b;
	u32 beacon_silence_rssi_c;
	u32 beacon_energy_a;
	u32 beacon_energy_b;
	u32 beacon_energy_c;
पूर्ण;

पूर्णांक iwl_send_calib_results(काष्ठा iwl_priv *priv)
अणु
	काष्ठा iwl_host_cmd hcmd = अणु
		.id = REPLY_PHY_CALIBRATION_CMD,
	पूर्ण;
	काष्ठा iwl_calib_result *res;

	list_क्रम_each_entry(res, &priv->calib_results, list) अणु
		पूर्णांक ret;

		hcmd.len[0] = res->cmd_len;
		hcmd.data[0] = &res->hdr;
		hcmd.dataflags[0] = IWL_HCMD_DFL_NOCOPY;
		ret = iwl_dvm_send_cmd(priv, &hcmd);
		अगर (ret) अणु
			IWL_ERR(priv, "Error %d on calib cmd %d\n",
				ret, res->hdr.op_code);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक iwl_calib_set(काष्ठा iwl_priv *priv,
		  स्थिर काष्ठा iwl_calib_hdr *cmd, पूर्णांक len)
अणु
	काष्ठा iwl_calib_result *res, *पंचांगp;

	res = kदो_स्मृति(माप(*res) + len - माप(काष्ठा iwl_calib_hdr),
		      GFP_ATOMIC);
	अगर (!res)
		वापस -ENOMEM;
	स_नकल(&res->hdr, cmd, len);
	res->cmd_len = len;

	list_क्रम_each_entry(पंचांगp, &priv->calib_results, list) अणु
		अगर (पंचांगp->hdr.op_code == res->hdr.op_code) अणु
			list_replace(&पंचांगp->list, &res->list);
			kमुक्त(पंचांगp);
			वापस 0;
		पूर्ण
	पूर्ण

	/* wasn't in list alपढ़ोy */
	list_add_tail(&res->list, &priv->calib_results);

	वापस 0;
पूर्ण

व्योम iwl_calib_मुक्त_results(काष्ठा iwl_priv *priv)
अणु
	काष्ठा iwl_calib_result *res, *पंचांगp;

	list_क्रम_each_entry_safe(res, पंचांगp, &priv->calib_results, list) अणु
		list_del(&res->list);
		kमुक्त(res);
	पूर्ण
पूर्ण

/*****************************************************************************
 * RUNTIME calibrations framework
 *****************************************************************************/

/* "false alarms" are संकेतs that our DSP tries to lock onto,
 *   but then determines that they are either noise, or transmissions
 *   from a distant wireless network (also "noise", really) that get
 *   "stepped on" by stronger transmissions within our own network.
 * This algorithm attempts to set a sensitivity level that is high
 *   enough to receive all of our own network traffic, but not so
 *   high that our DSP माला_लो too busy trying to lock onto non-network
 *   activity/noise. */
अटल पूर्णांक iwl_sens_energy_cck(काष्ठा iwl_priv *priv,
				   u32 norm_fa,
				   u32 rx_enable_समय,
				   काष्ठा statistics_general_data *rx_info)
अणु
	u32 max_nrg_cck = 0;
	पूर्णांक i = 0;
	u8 max_silence_rssi = 0;
	u32 silence_ref = 0;
	u8 silence_rssi_a = 0;
	u8 silence_rssi_b = 0;
	u8 silence_rssi_c = 0;
	u32 val;

	/* "false_alarms" values below are cross-multiplications to assess the
	 *   numbers of false alarms within the measured period of actual Rx
	 *   (Rx is off when we're txing), vs the min/max expected false alarms
	 *   (some should be expected अगर rx is sensitive enough) in a
	 *   hypothetical listening period of 200 समय units (TU), 204.8 msec:
	 *
	 * MIN_FA/fixed-समय < false_alarms/actual-rx-समय < MAX_FA/beacon-समय
	 *
	 * */
	u32 false_alarms = norm_fa * 200 * 1024;
	u32 max_false_alarms = MAX_FA_CCK * rx_enable_समय;
	u32 min_false_alarms = MIN_FA_CCK * rx_enable_समय;
	काष्ठा iwl_sensitivity_data *data = शून्य;
	स्थिर काष्ठा iwl_sensitivity_ranges *ranges = priv->hw_params.sens;

	data = &(priv->sensitivity_data);

	data->nrg_स्वतः_corr_silence_dअगरf = 0;

	/* Find max silence rssi among all 3 receivers.
	 * This is background noise, which may include transmissions from other
	 *    networks, measured during silence beक्रमe our network's beacon */
	silence_rssi_a = (u8)((rx_info->beacon_silence_rssi_a &
			    ALL_BAND_FILTER) >> 8);
	silence_rssi_b = (u8)((rx_info->beacon_silence_rssi_b &
			    ALL_BAND_FILTER) >> 8);
	silence_rssi_c = (u8)((rx_info->beacon_silence_rssi_c &
			    ALL_BAND_FILTER) >> 8);

	val = max(silence_rssi_b, silence_rssi_c);
	max_silence_rssi = max(silence_rssi_a, (u8) val);

	/* Store silence rssi in 20-beacon history table */
	data->nrg_silence_rssi[data->nrg_silence_idx] = max_silence_rssi;
	data->nrg_silence_idx++;
	अगर (data->nrg_silence_idx >= NRG_NUM_PREV_STAT_L)
		data->nrg_silence_idx = 0;

	/* Find max silence rssi across 20 beacon history */
	क्रम (i = 0; i < NRG_NUM_PREV_STAT_L; i++) अणु
		val = data->nrg_silence_rssi[i];
		silence_ref = max(silence_ref, val);
	पूर्ण
	IWL_DEBUG_CALIB(priv, "silence a %u, b %u, c %u, 20-bcn max %u\n",
			silence_rssi_a, silence_rssi_b, silence_rssi_c,
			silence_ref);

	/* Find max rx energy (min value!) among all 3 receivers,
	 *   measured during beacon frame.
	 * Save it in 10-beacon history table. */
	i = data->nrg_energy_idx;
	val = min(rx_info->beacon_energy_b, rx_info->beacon_energy_c);
	data->nrg_value[i] = min(rx_info->beacon_energy_a, val);

	data->nrg_energy_idx++;
	अगर (data->nrg_energy_idx >= 10)
		data->nrg_energy_idx = 0;

	/* Find min rx energy (max value) across 10 beacon history.
	 * This is the minimum संकेत level that we want to receive well.
	 * Add backoff (margin so we करोn't miss slightly lower energy frames).
	 * This establishes an upper bound (min value) क्रम energy threshold. */
	max_nrg_cck = data->nrg_value[0];
	क्रम (i = 1; i < 10; i++)
		max_nrg_cck = (u32) max(max_nrg_cck, (data->nrg_value[i]));
	max_nrg_cck += 6;

	IWL_DEBUG_CALIB(priv, "rx energy a %u, b %u, c %u, 10-bcn max/min %u\n",
			rx_info->beacon_energy_a, rx_info->beacon_energy_b,
			rx_info->beacon_energy_c, max_nrg_cck - 6);

	/* Count number of consecutive beacons with fewer-than-desired
	 *   false alarms. */
	अगर (false_alarms < min_false_alarms)
		data->num_in_cck_no_fa++;
	अन्यथा
		data->num_in_cck_no_fa = 0;
	IWL_DEBUG_CALIB(priv, "consecutive bcns with few false alarms = %u\n",
			data->num_in_cck_no_fa);

	/* If we got too many false alarms this समय, reduce sensitivity */
	अगर ((false_alarms > max_false_alarms) &&
		(data->स्वतः_corr_cck > AUTO_CORR_MAX_TH_CCK)) अणु
		IWL_DEBUG_CALIB(priv, "norm FA %u > max FA %u\n",
		     false_alarms, max_false_alarms);
		IWL_DEBUG_CALIB(priv, "... reducing sensitivity\n");
		data->nrg_curr_state = IWL_FA_TOO_MANY;
		/* Store क्रम "fewer than desired" on later beacon */
		data->nrg_silence_ref = silence_ref;

		/* increase energy threshold (reduce nrg value)
		 *   to decrease sensitivity */
		data->nrg_th_cck = data->nrg_th_cck - NRG_STEP_CCK;
	/* Else अगर we got fewer than desired, increase sensitivity */
	पूर्ण अन्यथा अगर (false_alarms < min_false_alarms) अणु
		data->nrg_curr_state = IWL_FA_TOO_FEW;

		/* Compare silence level with silence level क्रम most recent
		 *   healthy number or too many false alarms */
		data->nrg_स्वतः_corr_silence_dअगरf = (s32)data->nrg_silence_ref -
						   (s32)silence_ref;

		IWL_DEBUG_CALIB(priv, "norm FA %u < min FA %u, silence diff %d\n",
			 false_alarms, min_false_alarms,
			 data->nrg_स्वतः_corr_silence_dअगरf);

		/* Increase value to increase sensitivity, but only अगर:
		 * 1a) previous beacon did *not* have *too many* false alarms
		 * 1b) AND there's a signअगरicant dअगरference in Rx levels
		 *      from a previous beacon with too many, or healthy # FAs
		 * OR 2) We've seen a lot of beacons (100) with too few
		 *       false alarms */
		अगर ((data->nrg_prev_state != IWL_FA_TOO_MANY) &&
			((data->nrg_स्वतः_corr_silence_dअगरf > NRG_DIFF) ||
			(data->num_in_cck_no_fa > MAX_NUMBER_CCK_NO_FA))) अणु

			IWL_DEBUG_CALIB(priv, "... increasing sensitivity\n");
			/* Increase nrg value to increase sensitivity */
			val = data->nrg_th_cck + NRG_STEP_CCK;
			data->nrg_th_cck = min((u32)ranges->min_nrg_cck, val);
		पूर्ण अन्यथा अणु
			IWL_DEBUG_CALIB(priv, "... but not changing sensitivity\n");
		पूर्ण

	/* Else we got a healthy number of false alarms, keep status quo */
	पूर्ण अन्यथा अणु
		IWL_DEBUG_CALIB(priv, " FA in safe zone\n");
		data->nrg_curr_state = IWL_FA_GOOD_RANGE;

		/* Store क्रम use in "fewer than desired" with later beacon */
		data->nrg_silence_ref = silence_ref;

		/* If previous beacon had too many false alarms,
		 *   give it some extra margin by reducing sensitivity again
		 *   (but करोn't go below measured energy of desired Rx) */
		अगर (data->nrg_prev_state == IWL_FA_TOO_MANY) अणु
			IWL_DEBUG_CALIB(priv, "... increasing margin\n");
			अगर (data->nrg_th_cck > (max_nrg_cck + NRG_MARGIN))
				data->nrg_th_cck -= NRG_MARGIN;
			अन्यथा
				data->nrg_th_cck = max_nrg_cck;
		पूर्ण
	पूर्ण

	/* Make sure the energy threshold करोes not go above the measured
	 * energy of the desired Rx संकेतs (reduced by backoff margin),
	 * or अन्यथा we might start missing Rx frames.
	 * Lower value is higher energy, so we use max()!
	 */
	data->nrg_th_cck = max(max_nrg_cck, data->nrg_th_cck);
	IWL_DEBUG_CALIB(priv, "new nrg_th_cck %u\n", data->nrg_th_cck);

	data->nrg_prev_state = data->nrg_curr_state;

	/* Auto-correlation CCK algorithm */
	अगर (false_alarms > min_false_alarms) अणु

		/* increase स्वतः_corr values to decrease sensitivity
		 * so the DSP won't be disturbed by the noise
		 */
		अगर (data->स्वतः_corr_cck < AUTO_CORR_MAX_TH_CCK)
			data->स्वतः_corr_cck = AUTO_CORR_MAX_TH_CCK + 1;
		अन्यथा अणु
			val = data->स्वतः_corr_cck + AUTO_CORR_STEP_CCK;
			data->स्वतः_corr_cck =
				min((u32)ranges->स्वतः_corr_max_cck, val);
		पूर्ण
		val = data->स्वतः_corr_cck_mrc + AUTO_CORR_STEP_CCK;
		data->स्वतः_corr_cck_mrc =
			min((u32)ranges->स्वतः_corr_max_cck_mrc, val);
	पूर्ण अन्यथा अगर ((false_alarms < min_false_alarms) &&
	   ((data->nrg_स्वतः_corr_silence_dअगरf > NRG_DIFF) ||
	   (data->num_in_cck_no_fa > MAX_NUMBER_CCK_NO_FA))) अणु

		/* Decrease स्वतः_corr values to increase sensitivity */
		val = data->स्वतः_corr_cck - AUTO_CORR_STEP_CCK;
		data->स्वतः_corr_cck =
			max((u32)ranges->स्वतः_corr_min_cck, val);
		val = data->स्वतः_corr_cck_mrc - AUTO_CORR_STEP_CCK;
		data->स्वतः_corr_cck_mrc =
			max((u32)ranges->स्वतः_corr_min_cck_mrc, val);
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक iwl_sens_स्वतः_corr_ofdm(काष्ठा iwl_priv *priv,
				       u32 norm_fa,
				       u32 rx_enable_समय)
अणु
	u32 val;
	u32 false_alarms = norm_fa * 200 * 1024;
	u32 max_false_alarms = MAX_FA_OFDM * rx_enable_समय;
	u32 min_false_alarms = MIN_FA_OFDM * rx_enable_समय;
	काष्ठा iwl_sensitivity_data *data = शून्य;
	स्थिर काष्ठा iwl_sensitivity_ranges *ranges = priv->hw_params.sens;

	data = &(priv->sensitivity_data);

	/* If we got too many false alarms this समय, reduce sensitivity */
	अगर (false_alarms > max_false_alarms) अणु

		IWL_DEBUG_CALIB(priv, "norm FA %u > max FA %u)\n",
			     false_alarms, max_false_alarms);

		val = data->स्वतः_corr_ofdm + AUTO_CORR_STEP_OFDM;
		data->स्वतः_corr_ofdm =
			min((u32)ranges->स्वतः_corr_max_ofdm, val);

		val = data->स्वतः_corr_ofdm_mrc + AUTO_CORR_STEP_OFDM;
		data->स्वतः_corr_ofdm_mrc =
			min((u32)ranges->स्वतः_corr_max_ofdm_mrc, val);

		val = data->स्वतः_corr_ofdm_x1 + AUTO_CORR_STEP_OFDM;
		data->स्वतः_corr_ofdm_x1 =
			min((u32)ranges->स्वतः_corr_max_ofdm_x1, val);

		val = data->स्वतः_corr_ofdm_mrc_x1 + AUTO_CORR_STEP_OFDM;
		data->स्वतः_corr_ofdm_mrc_x1 =
			min((u32)ranges->स्वतः_corr_max_ofdm_mrc_x1, val);
	पूर्ण

	/* Else अगर we got fewer than desired, increase sensitivity */
	अन्यथा अगर (false_alarms < min_false_alarms) अणु

		IWL_DEBUG_CALIB(priv, "norm FA %u < min FA %u\n",
			     false_alarms, min_false_alarms);

		val = data->स्वतः_corr_ofdm - AUTO_CORR_STEP_OFDM;
		data->स्वतः_corr_ofdm =
			max((u32)ranges->स्वतः_corr_min_ofdm, val);

		val = data->स्वतः_corr_ofdm_mrc - AUTO_CORR_STEP_OFDM;
		data->स्वतः_corr_ofdm_mrc =
			max((u32)ranges->स्वतः_corr_min_ofdm_mrc, val);

		val = data->स्वतः_corr_ofdm_x1 - AUTO_CORR_STEP_OFDM;
		data->स्वतः_corr_ofdm_x1 =
			max((u32)ranges->स्वतः_corr_min_ofdm_x1, val);

		val = data->स्वतः_corr_ofdm_mrc_x1 - AUTO_CORR_STEP_OFDM;
		data->स्वतः_corr_ofdm_mrc_x1 =
			max((u32)ranges->स्वतः_corr_min_ofdm_mrc_x1, val);
	पूर्ण अन्यथा अणु
		IWL_DEBUG_CALIB(priv, "min FA %u < norm FA %u < max FA %u OK\n",
			 min_false_alarms, false_alarms, max_false_alarms);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम iwl_prepare_legacy_sensitivity_tbl(काष्ठा iwl_priv *priv,
				काष्ठा iwl_sensitivity_data *data,
				__le16 *tbl)
अणु
	tbl[HD_AUTO_CORR32_X4_TH_ADD_MIN_INDEX] =
				cpu_to_le16((u16)data->स्वतः_corr_ofdm);
	tbl[HD_AUTO_CORR32_X4_TH_ADD_MIN_MRC_INDEX] =
				cpu_to_le16((u16)data->स्वतः_corr_ofdm_mrc);
	tbl[HD_AUTO_CORR32_X1_TH_ADD_MIN_INDEX] =
				cpu_to_le16((u16)data->स्वतः_corr_ofdm_x1);
	tbl[HD_AUTO_CORR32_X1_TH_ADD_MIN_MRC_INDEX] =
				cpu_to_le16((u16)data->स्वतः_corr_ofdm_mrc_x1);

	tbl[HD_AUTO_CORR40_X4_TH_ADD_MIN_INDEX] =
				cpu_to_le16((u16)data->स्वतः_corr_cck);
	tbl[HD_AUTO_CORR40_X4_TH_ADD_MIN_MRC_INDEX] =
				cpu_to_le16((u16)data->स्वतः_corr_cck_mrc);

	tbl[HD_MIN_ENERGY_CCK_DET_INDEX] =
				cpu_to_le16((u16)data->nrg_th_cck);
	tbl[HD_MIN_ENERGY_OFDM_DET_INDEX] =
				cpu_to_le16((u16)data->nrg_th_ofdm);

	tbl[HD_BARKER_CORR_TH_ADD_MIN_INDEX] =
				cpu_to_le16(data->barker_corr_th_min);
	tbl[HD_BARKER_CORR_TH_ADD_MIN_MRC_INDEX] =
				cpu_to_le16(data->barker_corr_th_min_mrc);
	tbl[HD_OFDM_ENERGY_TH_IN_INDEX] =
				cpu_to_le16(data->nrg_th_cca);

	IWL_DEBUG_CALIB(priv, "ofdm: ac %u mrc %u x1 %u mrc_x1 %u thresh %u\n",
			data->स्वतः_corr_ofdm, data->स्वतः_corr_ofdm_mrc,
			data->स्वतः_corr_ofdm_x1, data->स्वतः_corr_ofdm_mrc_x1,
			data->nrg_th_ofdm);

	IWL_DEBUG_CALIB(priv, "cck: ac %u mrc %u thresh %u\n",
			data->स्वतः_corr_cck, data->स्वतः_corr_cck_mrc,
			data->nrg_th_cck);
पूर्ण

/* Prepare a SENSITIVITY_CMD, send to uCode अगर values have changed */
अटल पूर्णांक iwl_sensitivity_ग_लिखो(काष्ठा iwl_priv *priv)
अणु
	काष्ठा iwl_sensitivity_cmd cmd;
	काष्ठा iwl_sensitivity_data *data = शून्य;
	काष्ठा iwl_host_cmd cmd_out = अणु
		.id = SENSITIVITY_CMD,
		.len = अणु माप(काष्ठा iwl_sensitivity_cmd), पूर्ण,
		.flags = CMD_ASYNC,
		.data = अणु &cmd, पूर्ण,
	पूर्ण;

	data = &(priv->sensitivity_data);

	स_रखो(&cmd, 0, माप(cmd));

	iwl_prepare_legacy_sensitivity_tbl(priv, data, &cmd.table[0]);

	/* Update uCode's "work" table, and copy it to DSP */
	cmd.control = SENSITIVITY_CMD_CONTROL_WORK_TABLE;

	/* Don't send command to uCode अगर nothing has changed */
	अगर (!स_भेद(&cmd.table[0], &(priv->sensitivity_tbl[0]),
		    माप(u16)*HD_TABLE_SIZE)) अणु
		IWL_DEBUG_CALIB(priv, "No change in SENSITIVITY_CMD\n");
		वापस 0;
	पूर्ण

	/* Copy table क्रम comparison next समय */
	स_नकल(&(priv->sensitivity_tbl[0]), &(cmd.table[0]),
	       माप(u16)*HD_TABLE_SIZE);

	वापस iwl_dvm_send_cmd(priv, &cmd_out);
पूर्ण

/* Prepare a SENSITIVITY_CMD, send to uCode अगर values have changed */
अटल पूर्णांक iwl_enhance_sensitivity_ग_लिखो(काष्ठा iwl_priv *priv)
अणु
	काष्ठा iwl_enhance_sensitivity_cmd cmd;
	काष्ठा iwl_sensitivity_data *data = शून्य;
	काष्ठा iwl_host_cmd cmd_out = अणु
		.id = SENSITIVITY_CMD,
		.len = अणु माप(काष्ठा iwl_enhance_sensitivity_cmd), पूर्ण,
		.flags = CMD_ASYNC,
		.data = अणु &cmd, पूर्ण,
	पूर्ण;

	data = &(priv->sensitivity_data);

	स_रखो(&cmd, 0, माप(cmd));

	iwl_prepare_legacy_sensitivity_tbl(priv, data, &cmd.enhance_table[0]);

	अगर (priv->lib->hd_v2) अणु
		cmd.enhance_table[HD_INA_NON_SQUARE_DET_OFDM_INDEX] =
			HD_INA_NON_SQUARE_DET_OFDM_DATA_V2;
		cmd.enhance_table[HD_INA_NON_SQUARE_DET_CCK_INDEX] =
			HD_INA_NON_SQUARE_DET_CCK_DATA_V2;
		cmd.enhance_table[HD_CORR_11_INSTEAD_OF_CORR_9_EN_INDEX] =
			HD_CORR_11_INSTEAD_OF_CORR_9_EN_DATA_V2;
		cmd.enhance_table[HD_OFDM_NON_SQUARE_DET_SLOPE_MRC_INDEX] =
			HD_OFDM_NON_SQUARE_DET_SLOPE_MRC_DATA_V2;
		cmd.enhance_table[HD_OFDM_NON_SQUARE_DET_INTERCEPT_MRC_INDEX] =
			HD_OFDM_NON_SQUARE_DET_INTERCEPT_MRC_DATA_V2;
		cmd.enhance_table[HD_OFDM_NON_SQUARE_DET_SLOPE_INDEX] =
			HD_OFDM_NON_SQUARE_DET_SLOPE_DATA_V2;
		cmd.enhance_table[HD_OFDM_NON_SQUARE_DET_INTERCEPT_INDEX] =
			HD_OFDM_NON_SQUARE_DET_INTERCEPT_DATA_V2;
		cmd.enhance_table[HD_CCK_NON_SQUARE_DET_SLOPE_MRC_INDEX] =
			HD_CCK_NON_SQUARE_DET_SLOPE_MRC_DATA_V2;
		cmd.enhance_table[HD_CCK_NON_SQUARE_DET_INTERCEPT_MRC_INDEX] =
			HD_CCK_NON_SQUARE_DET_INTERCEPT_MRC_DATA_V2;
		cmd.enhance_table[HD_CCK_NON_SQUARE_DET_SLOPE_INDEX] =
			HD_CCK_NON_SQUARE_DET_SLOPE_DATA_V2;
		cmd.enhance_table[HD_CCK_NON_SQUARE_DET_INTERCEPT_INDEX] =
			HD_CCK_NON_SQUARE_DET_INTERCEPT_DATA_V2;
	पूर्ण अन्यथा अणु
		cmd.enhance_table[HD_INA_NON_SQUARE_DET_OFDM_INDEX] =
			HD_INA_NON_SQUARE_DET_OFDM_DATA_V1;
		cmd.enhance_table[HD_INA_NON_SQUARE_DET_CCK_INDEX] =
			HD_INA_NON_SQUARE_DET_CCK_DATA_V1;
		cmd.enhance_table[HD_CORR_11_INSTEAD_OF_CORR_9_EN_INDEX] =
			HD_CORR_11_INSTEAD_OF_CORR_9_EN_DATA_V1;
		cmd.enhance_table[HD_OFDM_NON_SQUARE_DET_SLOPE_MRC_INDEX] =
			HD_OFDM_NON_SQUARE_DET_SLOPE_MRC_DATA_V1;
		cmd.enhance_table[HD_OFDM_NON_SQUARE_DET_INTERCEPT_MRC_INDEX] =
			HD_OFDM_NON_SQUARE_DET_INTERCEPT_MRC_DATA_V1;
		cmd.enhance_table[HD_OFDM_NON_SQUARE_DET_SLOPE_INDEX] =
			HD_OFDM_NON_SQUARE_DET_SLOPE_DATA_V1;
		cmd.enhance_table[HD_OFDM_NON_SQUARE_DET_INTERCEPT_INDEX] =
			HD_OFDM_NON_SQUARE_DET_INTERCEPT_DATA_V1;
		cmd.enhance_table[HD_CCK_NON_SQUARE_DET_SLOPE_MRC_INDEX] =
			HD_CCK_NON_SQUARE_DET_SLOPE_MRC_DATA_V1;
		cmd.enhance_table[HD_CCK_NON_SQUARE_DET_INTERCEPT_MRC_INDEX] =
			HD_CCK_NON_SQUARE_DET_INTERCEPT_MRC_DATA_V1;
		cmd.enhance_table[HD_CCK_NON_SQUARE_DET_SLOPE_INDEX] =
			HD_CCK_NON_SQUARE_DET_SLOPE_DATA_V1;
		cmd.enhance_table[HD_CCK_NON_SQUARE_DET_INTERCEPT_INDEX] =
			HD_CCK_NON_SQUARE_DET_INTERCEPT_DATA_V1;
	पूर्ण

	/* Update uCode's "work" table, and copy it to DSP */
	cmd.control = SENSITIVITY_CMD_CONTROL_WORK_TABLE;

	/* Don't send command to uCode अगर nothing has changed */
	अगर (!स_भेद(&cmd.enhance_table[0], &(priv->sensitivity_tbl[0]),
		    माप(u16)*HD_TABLE_SIZE) &&
	    !स_भेद(&cmd.enhance_table[HD_INA_NON_SQUARE_DET_OFDM_INDEX],
		    &(priv->enhance_sensitivity_tbl[0]),
		    माप(u16)*ENHANCE_HD_TABLE_ENTRIES)) अणु
		IWL_DEBUG_CALIB(priv, "No change in SENSITIVITY_CMD\n");
		वापस 0;
	पूर्ण

	/* Copy table क्रम comparison next समय */
	स_नकल(&(priv->sensitivity_tbl[0]), &(cmd.enhance_table[0]),
	       माप(u16)*HD_TABLE_SIZE);
	स_नकल(&(priv->enhance_sensitivity_tbl[0]),
	       &(cmd.enhance_table[HD_INA_NON_SQUARE_DET_OFDM_INDEX]),
	       माप(u16)*ENHANCE_HD_TABLE_ENTRIES);

	वापस iwl_dvm_send_cmd(priv, &cmd_out);
पूर्ण

व्योम iwl_init_sensitivity(काष्ठा iwl_priv *priv)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i;
	काष्ठा iwl_sensitivity_data *data = शून्य;
	स्थिर काष्ठा iwl_sensitivity_ranges *ranges = priv->hw_params.sens;

	अगर (priv->calib_disabled & IWL_SENSITIVITY_CALIB_DISABLED)
		वापस;

	IWL_DEBUG_CALIB(priv, "Start iwl_init_sensitivity\n");

	/* Clear driver's sensitivity algo data */
	data = &(priv->sensitivity_data);

	अगर (ranges == शून्य)
		वापस;

	स_रखो(data, 0, माप(काष्ठा iwl_sensitivity_data));

	data->num_in_cck_no_fa = 0;
	data->nrg_curr_state = IWL_FA_TOO_MANY;
	data->nrg_prev_state = IWL_FA_TOO_MANY;
	data->nrg_silence_ref = 0;
	data->nrg_silence_idx = 0;
	data->nrg_energy_idx = 0;

	क्रम (i = 0; i < 10; i++)
		data->nrg_value[i] = 0;

	क्रम (i = 0; i < NRG_NUM_PREV_STAT_L; i++)
		data->nrg_silence_rssi[i] = 0;

	data->स्वतः_corr_ofdm =  ranges->स्वतः_corr_min_ofdm;
	data->स्वतः_corr_ofdm_mrc = ranges->स्वतः_corr_min_ofdm_mrc;
	data->स्वतः_corr_ofdm_x1  = ranges->स्वतः_corr_min_ofdm_x1;
	data->स्वतः_corr_ofdm_mrc_x1 = ranges->स्वतः_corr_min_ofdm_mrc_x1;
	data->स्वतः_corr_cck = AUTO_CORR_CCK_MIN_VAL_DEF;
	data->स्वतः_corr_cck_mrc = ranges->स्वतः_corr_min_cck_mrc;
	data->nrg_th_cck = ranges->nrg_th_cck;
	data->nrg_th_ofdm = ranges->nrg_th_ofdm;
	data->barker_corr_th_min = ranges->barker_corr_th_min;
	data->barker_corr_th_min_mrc = ranges->barker_corr_th_min_mrc;
	data->nrg_th_cca = ranges->nrg_th_cca;

	data->last_bad_plcp_cnt_ofdm = 0;
	data->last_fa_cnt_ofdm = 0;
	data->last_bad_plcp_cnt_cck = 0;
	data->last_fa_cnt_cck = 0;

	अगर (priv->fw->enhance_sensitivity_table)
		ret |= iwl_enhance_sensitivity_ग_लिखो(priv);
	अन्यथा
		ret |= iwl_sensitivity_ग_लिखो(priv);
	IWL_DEBUG_CALIB(priv, "<<return 0x%X\n", ret);
पूर्ण

व्योम iwl_sensitivity_calibration(काष्ठा iwl_priv *priv)
अणु
	u32 rx_enable_समय;
	u32 fa_cck;
	u32 fa_ofdm;
	u32 bad_plcp_cck;
	u32 bad_plcp_ofdm;
	u32 norm_fa_ofdm;
	u32 norm_fa_cck;
	काष्ठा iwl_sensitivity_data *data = शून्य;
	काष्ठा statistics_rx_non_phy *rx_info;
	काष्ठा statistics_rx_phy *ofdm, *cck;
	काष्ठा statistics_general_data statis;

	अगर (priv->calib_disabled & IWL_SENSITIVITY_CALIB_DISABLED)
		वापस;

	data = &(priv->sensitivity_data);

	अगर (!iwl_is_any_associated(priv)) अणु
		IWL_DEBUG_CALIB(priv, "<< - not associated\n");
		वापस;
	पूर्ण

	spin_lock_bh(&priv->statistics.lock);
	rx_info = &priv->statistics.rx_non_phy;
	ofdm = &priv->statistics.rx_ofdm;
	cck = &priv->statistics.rx_cck;
	अगर (rx_info->पूर्णांकerference_data_flag != INTERFERENCE_DATA_AVAILABLE) अणु
		IWL_DEBUG_CALIB(priv, "<< invalid data.\n");
		spin_unlock_bh(&priv->statistics.lock);
		वापस;
	पूर्ण

	/* Extract Statistics: */
	rx_enable_समय = le32_to_cpu(rx_info->channel_load);
	fa_cck = le32_to_cpu(cck->false_alarm_cnt);
	fa_ofdm = le32_to_cpu(ofdm->false_alarm_cnt);
	bad_plcp_cck = le32_to_cpu(cck->plcp_err);
	bad_plcp_ofdm = le32_to_cpu(ofdm->plcp_err);

	statis.beacon_silence_rssi_a =
			le32_to_cpu(rx_info->beacon_silence_rssi_a);
	statis.beacon_silence_rssi_b =
			le32_to_cpu(rx_info->beacon_silence_rssi_b);
	statis.beacon_silence_rssi_c =
			le32_to_cpu(rx_info->beacon_silence_rssi_c);
	statis.beacon_energy_a =
			le32_to_cpu(rx_info->beacon_energy_a);
	statis.beacon_energy_b =
			le32_to_cpu(rx_info->beacon_energy_b);
	statis.beacon_energy_c =
			le32_to_cpu(rx_info->beacon_energy_c);

	spin_unlock_bh(&priv->statistics.lock);

	IWL_DEBUG_CALIB(priv, "rx_enable_time = %u usecs\n", rx_enable_समय);

	अगर (!rx_enable_समय) अणु
		IWL_DEBUG_CALIB(priv, "<< RX Enable Time == 0!\n");
		वापस;
	पूर्ण

	/* These statistics increase monotonically, and करो not reset
	 *   at each beacon.  Calculate dअगरference from last value, or just
	 *   use the new statistics value अगर it has reset or wrapped around. */
	अगर (data->last_bad_plcp_cnt_cck > bad_plcp_cck)
		data->last_bad_plcp_cnt_cck = bad_plcp_cck;
	अन्यथा अणु
		bad_plcp_cck -= data->last_bad_plcp_cnt_cck;
		data->last_bad_plcp_cnt_cck += bad_plcp_cck;
	पूर्ण

	अगर (data->last_bad_plcp_cnt_ofdm > bad_plcp_ofdm)
		data->last_bad_plcp_cnt_ofdm = bad_plcp_ofdm;
	अन्यथा अणु
		bad_plcp_ofdm -= data->last_bad_plcp_cnt_ofdm;
		data->last_bad_plcp_cnt_ofdm += bad_plcp_ofdm;
	पूर्ण

	अगर (data->last_fa_cnt_ofdm > fa_ofdm)
		data->last_fa_cnt_ofdm = fa_ofdm;
	अन्यथा अणु
		fa_ofdm -= data->last_fa_cnt_ofdm;
		data->last_fa_cnt_ofdm += fa_ofdm;
	पूर्ण

	अगर (data->last_fa_cnt_cck > fa_cck)
		data->last_fa_cnt_cck = fa_cck;
	अन्यथा अणु
		fa_cck -= data->last_fa_cnt_cck;
		data->last_fa_cnt_cck += fa_cck;
	पूर्ण

	/* Total पातed संकेत locks */
	norm_fa_ofdm = fa_ofdm + bad_plcp_ofdm;
	norm_fa_cck = fa_cck + bad_plcp_cck;

	IWL_DEBUG_CALIB(priv, "cck: fa %u badp %u  ofdm: fa %u badp %u\n", fa_cck,
			bad_plcp_cck, fa_ofdm, bad_plcp_ofdm);

	iwl_sens_स्वतः_corr_ofdm(priv, norm_fa_ofdm, rx_enable_समय);
	iwl_sens_energy_cck(priv, norm_fa_cck, rx_enable_समय, &statis);
	अगर (priv->fw->enhance_sensitivity_table)
		iwl_enhance_sensitivity_ग_लिखो(priv);
	अन्यथा
		iwl_sensitivity_ग_लिखो(priv);
पूर्ण

अटल अंतरभूत u8 find_first_chain(u8 mask)
अणु
	अगर (mask & ANT_A)
		वापस CHAIN_A;
	अगर (mask & ANT_B)
		वापस CHAIN_B;
	वापस CHAIN_C;
पूर्ण

/*
 * Run disconnected antenna algorithm to find out which antennas are
 * disconnected.
 */
अटल व्योम iwl_find_disconn_antenna(काष्ठा iwl_priv *priv, u32* average_sig,
				     काष्ठा iwl_chain_noise_data *data)
अणु
	u32 active_chains = 0;
	u32 max_average_sig;
	u16 max_average_sig_antenna_i;
	u8 num_tx_chains;
	u8 first_chain;
	u16 i = 0;

	average_sig[0] = data->chain_संकेत_a / IWL_CAL_NUM_BEACONS;
	average_sig[1] = data->chain_संकेत_b / IWL_CAL_NUM_BEACONS;
	average_sig[2] = data->chain_संकेत_c / IWL_CAL_NUM_BEACONS;

	अगर (average_sig[0] >= average_sig[1]) अणु
		max_average_sig = average_sig[0];
		max_average_sig_antenna_i = 0;
		active_chains = (1 << max_average_sig_antenna_i);
	पूर्ण अन्यथा अणु
		max_average_sig = average_sig[1];
		max_average_sig_antenna_i = 1;
		active_chains = (1 << max_average_sig_antenna_i);
	पूर्ण

	अगर (average_sig[2] >= max_average_sig) अणु
		max_average_sig = average_sig[2];
		max_average_sig_antenna_i = 2;
		active_chains = (1 << max_average_sig_antenna_i);
	पूर्ण

	IWL_DEBUG_CALIB(priv, "average_sig: a %d b %d c %d\n",
		     average_sig[0], average_sig[1], average_sig[2]);
	IWL_DEBUG_CALIB(priv, "max_average_sig = %d, antenna %d\n",
		     max_average_sig, max_average_sig_antenna_i);

	/* Compare संकेत strengths क्रम all 3 receivers. */
	क्रम (i = 0; i < NUM_RX_CHAINS; i++) अणु
		अगर (i != max_average_sig_antenna_i) अणु
			s32 rssi_delta = (max_average_sig - average_sig[i]);

			/* If संकेत is very weak, compared with
			 * strongest, mark it as disconnected. */
			अगर (rssi_delta > MAXIMUM_ALLOWED_PATHLOSS)
				data->disconn_array[i] = 1;
			अन्यथा
				active_chains |= (1 << i);
			IWL_DEBUG_CALIB(priv, "i = %d  rssiDelta = %d  "
			     "disconn_array[i] = %d\n",
			     i, rssi_delta, data->disconn_array[i]);
		पूर्ण
	पूर्ण

	/*
	 * The above algorithm someबार fails when the ucode
	 * reports 0 क्रम all chains. It's not clear why that
	 * happens to start with, but it is then causing trouble
	 * because this can make us enable more chains than the
	 * hardware really has.
	 *
	 * To be safe, simply mask out any chains that we know
	 * are not on the device.
	 */
	active_chains &= priv->nvm_data->valid_rx_ant;

	num_tx_chains = 0;
	क्रम (i = 0; i < NUM_RX_CHAINS; i++) अणु
		/* loops on all the bits of
		 * priv->hw_setting.valid_tx_ant */
		u8 ant_msk = (1 << i);
		अगर (!(priv->nvm_data->valid_tx_ant & ant_msk))
			जारी;

		num_tx_chains++;
		अगर (data->disconn_array[i] == 0)
			/* there is a Tx antenna connected */
			अवरोध;
		अगर (num_tx_chains == priv->hw_params.tx_chains_num &&
		    data->disconn_array[i]) अणु
			/*
			 * If all chains are disconnected
			 * connect the first valid tx chain
			 */
			first_chain =
				find_first_chain(priv->nvm_data->valid_tx_ant);
			data->disconn_array[first_chain] = 0;
			active_chains |= BIT(first_chain);
			IWL_DEBUG_CALIB(priv,
					"All Tx chains are disconnected W/A - declare %d as connected\n",
					first_chain);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (active_chains != priv->nvm_data->valid_rx_ant &&
	    active_chains != priv->chain_noise_data.active_chains)
		IWL_DEBUG_CALIB(priv,
				"Detected that not all antennas are connected! "
				"Connected: %#x, valid: %#x.\n",
				active_chains,
				priv->nvm_data->valid_rx_ant);

	/* Save क्रम use within RXON, TX, SCAN commands, etc. */
	data->active_chains = active_chains;
	IWL_DEBUG_CALIB(priv, "active_chains (bitwise) = 0x%x\n",
			active_chains);
पूर्ण

अटल व्योम iwlagn_gain_computation(काष्ठा iwl_priv *priv,
				    u32 average_noise[NUM_RX_CHAINS],
				    u8 शेष_chain)
अणु
	पूर्णांक i;
	s32 delta_g;
	काष्ठा iwl_chain_noise_data *data = &priv->chain_noise_data;

	/*
	 * Find Gain Code क्रम the chains based on "default chain"
	 */
	क्रम (i = शेष_chain + 1; i < NUM_RX_CHAINS; i++) अणु
		अगर ((data->disconn_array[i])) अणु
			data->delta_gain_code[i] = 0;
			जारी;
		पूर्ण

		delta_g = (priv->lib->chain_noise_scale *
			((s32)average_noise[शेष_chain] -
			(s32)average_noise[i])) / 1500;

		/* bound gain by 2 bits value max, 3rd bit is sign */
		data->delta_gain_code[i] =
			min(असल(delta_g), CHAIN_NOISE_MAX_DELTA_GAIN_CODE);

		अगर (delta_g < 0)
			/*
			 * set negative sign ...
			 * note to Intel developers:  This is uCode API क्रमmat,
			 *   not the क्रमmat of any पूर्णांकernal device रेजिस्टरs.
			 *   Do not change this क्रमmat क्रम e.g. 6050 or similar
			 *   devices.  Change क्रमmat only अगर more resolution
			 *   (i.e. more than 2 bits magnitude) is needed.
			 */
			data->delta_gain_code[i] |= (1 << 2);
	पूर्ण

	IWL_DEBUG_CALIB(priv, "Delta gains: ANT_B = %d  ANT_C = %d\n",
			data->delta_gain_code[1], data->delta_gain_code[2]);

	अगर (!data->radio_ग_लिखो) अणु
		काष्ठा iwl_calib_chain_noise_gain_cmd cmd;

		स_रखो(&cmd, 0, माप(cmd));

		iwl_set_calib_hdr(&cmd.hdr,
			priv->phy_calib_chain_noise_gain_cmd);
		cmd.delta_gain_1 = data->delta_gain_code[1];
		cmd.delta_gain_2 = data->delta_gain_code[2];
		iwl_dvm_send_cmd_pdu(priv, REPLY_PHY_CALIBRATION_CMD,
			CMD_ASYNC, माप(cmd), &cmd);

		data->radio_ग_लिखो = 1;
		data->state = IWL_CHAIN_NOISE_CALIBRATED;
	पूर्ण
पूर्ण

/*
 * Accumulate 16 beacons of संकेत and noise statistics क्रम each of
 *   3 receivers/antennas/rx-chains, then figure out:
 * 1)  Which antennas are connected.
 * 2)  Dअगरferential rx gain settings to balance the 3 receivers.
 */
व्योम iwl_chain_noise_calibration(काष्ठा iwl_priv *priv)
अणु
	काष्ठा iwl_chain_noise_data *data = शून्य;

	u32 chain_noise_a;
	u32 chain_noise_b;
	u32 chain_noise_c;
	u32 chain_sig_a;
	u32 chain_sig_b;
	u32 chain_sig_c;
	u32 average_sig[NUM_RX_CHAINS] = अणुINITIALIZATION_VALUEपूर्ण;
	u32 average_noise[NUM_RX_CHAINS] = अणुINITIALIZATION_VALUEपूर्ण;
	u32 min_average_noise = MIN_AVERAGE_NOISE_MAX_VALUE;
	u16 min_average_noise_antenna_i = INITIALIZATION_VALUE;
	u16 i = 0;
	u16 rxon_chnum = INITIALIZATION_VALUE;
	u16 stat_chnum = INITIALIZATION_VALUE;
	u8 rxon_band24;
	u8 stat_band24;
	काष्ठा statistics_rx_non_phy *rx_info;

	/*
	 * MULTI-FIXME:
	 * When we support multiple पूर्णांकerfaces on dअगरferent channels,
	 * this must be modअगरied/fixed.
	 */
	काष्ठा iwl_rxon_context *ctx = &priv->contexts[IWL_RXON_CTX_BSS];

	अगर (priv->calib_disabled & IWL_CHAIN_NOISE_CALIB_DISABLED)
		वापस;

	data = &(priv->chain_noise_data);

	/*
	 * Accumulate just the first "chain_noise_num_beacons" after
	 * the first association, then we're करोne क्रमever.
	 */
	अगर (data->state != IWL_CHAIN_NOISE_ACCUMULATE) अणु
		अगर (data->state == IWL_CHAIN_NOISE_ALIVE)
			IWL_DEBUG_CALIB(priv, "Wait for noise calib reset\n");
		वापस;
	पूर्ण

	spin_lock_bh(&priv->statistics.lock);

	rx_info = &priv->statistics.rx_non_phy;

	अगर (rx_info->पूर्णांकerference_data_flag != INTERFERENCE_DATA_AVAILABLE) अणु
		IWL_DEBUG_CALIB(priv, " << Interference data unavailable\n");
		spin_unlock_bh(&priv->statistics.lock);
		वापस;
	पूर्ण

	rxon_band24 = !!(ctx->staging.flags & RXON_FLG_BAND_24G_MSK);
	rxon_chnum = le16_to_cpu(ctx->staging.channel);
	stat_band24 =
		!!(priv->statistics.flag & STATISTICS_REPLY_FLG_BAND_24G_MSK);
	stat_chnum = le32_to_cpu(priv->statistics.flag) >> 16;

	/* Make sure we accumulate data क्रम just the associated channel
	 *   (even अगर scanning). */
	अगर ((rxon_chnum != stat_chnum) || (rxon_band24 != stat_band24)) अणु
		IWL_DEBUG_CALIB(priv, "Stats not from chan=%d, band24=%d\n",
				rxon_chnum, rxon_band24);
		spin_unlock_bh(&priv->statistics.lock);
		वापस;
	पूर्ण

	/*
	 *  Accumulate beacon statistics values across
	 * "chain_noise_num_beacons"
	 */
	chain_noise_a = le32_to_cpu(rx_info->beacon_silence_rssi_a) &
				IN_BAND_FILTER;
	chain_noise_b = le32_to_cpu(rx_info->beacon_silence_rssi_b) &
				IN_BAND_FILTER;
	chain_noise_c = le32_to_cpu(rx_info->beacon_silence_rssi_c) &
				IN_BAND_FILTER;

	chain_sig_a = le32_to_cpu(rx_info->beacon_rssi_a) & IN_BAND_FILTER;
	chain_sig_b = le32_to_cpu(rx_info->beacon_rssi_b) & IN_BAND_FILTER;
	chain_sig_c = le32_to_cpu(rx_info->beacon_rssi_c) & IN_BAND_FILTER;

	spin_unlock_bh(&priv->statistics.lock);

	data->beacon_count++;

	data->chain_noise_a = (chain_noise_a + data->chain_noise_a);
	data->chain_noise_b = (chain_noise_b + data->chain_noise_b);
	data->chain_noise_c = (chain_noise_c + data->chain_noise_c);

	data->chain_संकेत_a = (chain_sig_a + data->chain_संकेत_a);
	data->chain_संकेत_b = (chain_sig_b + data->chain_संकेत_b);
	data->chain_संकेत_c = (chain_sig_c + data->chain_संकेत_c);

	IWL_DEBUG_CALIB(priv, "chan=%d, band24=%d, beacon=%d\n",
			rxon_chnum, rxon_band24, data->beacon_count);
	IWL_DEBUG_CALIB(priv, "chain_sig: a %d b %d c %d\n",
			chain_sig_a, chain_sig_b, chain_sig_c);
	IWL_DEBUG_CALIB(priv, "chain_noise: a %d b %d c %d\n",
			chain_noise_a, chain_noise_b, chain_noise_c);

	/* If this is the "chain_noise_num_beacons", determine:
	 * 1)  Disconnected antennas (using संकेत strengths)
	 * 2)  Dअगरferential gain (using silence noise) to balance receivers */
	अगर (data->beacon_count != IWL_CAL_NUM_BEACONS)
		वापस;

	/* Analyze संकेत क्रम disconnected antenna */
	अगर (priv->lib->bt_params &&
	    priv->lib->bt_params->advanced_bt_coexist) अणु
		/* Disable disconnected antenna algorithm क्रम advanced
		   bt coex, assuming valid antennas are connected */
		data->active_chains = priv->nvm_data->valid_rx_ant;
		क्रम (i = 0; i < NUM_RX_CHAINS; i++)
			अगर (!(data->active_chains & (1<<i)))
				data->disconn_array[i] = 1;
	पूर्ण अन्यथा
		iwl_find_disconn_antenna(priv, average_sig, data);

	/* Analyze noise क्रम rx balance */
	average_noise[0] = data->chain_noise_a / IWL_CAL_NUM_BEACONS;
	average_noise[1] = data->chain_noise_b / IWL_CAL_NUM_BEACONS;
	average_noise[2] = data->chain_noise_c / IWL_CAL_NUM_BEACONS;

	क्रम (i = 0; i < NUM_RX_CHAINS; i++) अणु
		अगर (!(data->disconn_array[i]) &&
		   (average_noise[i] <= min_average_noise)) अणु
			/* This means that chain i is active and has
			 * lower noise values so far: */
			min_average_noise = average_noise[i];
			min_average_noise_antenna_i = i;
		पूर्ण
	पूर्ण

	IWL_DEBUG_CALIB(priv, "average_noise: a %d b %d c %d\n",
			average_noise[0], average_noise[1],
			average_noise[2]);

	IWL_DEBUG_CALIB(priv, "min_average_noise = %d, antenna %d\n",
			min_average_noise, min_average_noise_antenna_i);

	iwlagn_gain_computation(
		priv, average_noise,
		find_first_chain(priv->nvm_data->valid_rx_ant));

	/* Some घातer changes may have been made during the calibration.
	 * Update and commit the RXON
	 */
	iwl_update_chain_flags(priv);

	data->state = IWL_CHAIN_NOISE_DONE;
	iwl_घातer_update_mode(priv, false);
पूर्ण

व्योम iwl_reset_run_समय_calib(काष्ठा iwl_priv *priv)
अणु
	पूर्णांक i;
	स_रखो(&(priv->sensitivity_data), 0,
	       माप(काष्ठा iwl_sensitivity_data));
	स_रखो(&(priv->chain_noise_data), 0,
	       माप(काष्ठा iwl_chain_noise_data));
	क्रम (i = 0; i < NUM_RX_CHAINS; i++)
		priv->chain_noise_data.delta_gain_code[i] =
				CHAIN_NOISE_DELTA_GAIN_INIT_VAL;

	/* Ask क्रम statistics now, the uCode will send notअगरication
	 * periodically after association */
	iwl_send_statistics_request(priv, CMD_ASYNC, true);
पूर्ण
