<शैली गुरु>
/******************************************************************************
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * Copyright(c) 2008 - 2011 Intel Corporation. All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fअगरth Floor, Boston, MA 02110,
 * USA
 *
 * The full GNU General Public License is included in this distribution
 * in the file called LICENSE.GPL.
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <ilw@linux.पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 * BSD LICENSE
 *
 * Copyright(c) 2005 - 2011 Intel Corporation. All rights reserved.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  * Neither the name Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#समावेश <linux/slab.h>
#समावेश <net/mac80211.h>

#समावेश "common.h"
#समावेश "4965.h"

/*****************************************************************************
 * INIT calibrations framework
 *****************************************************************************/

काष्ठा stats_general_data अणु
	u32 beacon_silence_rssi_a;
	u32 beacon_silence_rssi_b;
	u32 beacon_silence_rssi_c;
	u32 beacon_energy_a;
	u32 beacon_energy_b;
	u32 beacon_energy_c;
पूर्ण;

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
अटल पूर्णांक
il4965_sens_energy_cck(काष्ठा il_priv *il, u32 norm_fa, u32 rx_enable_समय,
		       काष्ठा stats_general_data *rx_info)
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
	काष्ठा il_sensitivity_data *data = शून्य;
	स्थिर काष्ठा il_sensitivity_ranges *ranges = il->hw_params.sens;

	data = &(il->sensitivity_data);

	data->nrg_स्वतः_corr_silence_dअगरf = 0;

	/* Find max silence rssi among all 3 receivers.
	 * This is background noise, which may include transmissions from other
	 *    networks, measured during silence beक्रमe our network's beacon */
	silence_rssi_a =
	    (u8) ((rx_info->beacon_silence_rssi_a & ALL_BAND_FILTER) >> 8);
	silence_rssi_b =
	    (u8) ((rx_info->beacon_silence_rssi_b & ALL_BAND_FILTER) >> 8);
	silence_rssi_c =
	    (u8) ((rx_info->beacon_silence_rssi_c & ALL_BAND_FILTER) >> 8);

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
	D_CALIB("silence a %u, b %u, c %u, 20-bcn max %u\n", silence_rssi_a,
		silence_rssi_b, silence_rssi_c, silence_ref);

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

	D_CALIB("rx energy a %u, b %u, c %u, 10-bcn max/min %u\n",
		rx_info->beacon_energy_a, rx_info->beacon_energy_b,
		rx_info->beacon_energy_c, max_nrg_cck - 6);

	/* Count number of consecutive beacons with fewer-than-desired
	 *   false alarms. */
	अगर (false_alarms < min_false_alarms)
		data->num_in_cck_no_fa++;
	अन्यथा
		data->num_in_cck_no_fa = 0;
	D_CALIB("consecutive bcns with few false alarms = %u\n",
		data->num_in_cck_no_fa);

	/* If we got too many false alarms this समय, reduce sensitivity */
	अगर (false_alarms > max_false_alarms &&
	    data->स्वतः_corr_cck > AUTO_CORR_MAX_TH_CCK) अणु
		D_CALIB("norm FA %u > max FA %u\n", false_alarms,
			max_false_alarms);
		D_CALIB("... reducing sensitivity\n");
		data->nrg_curr_state = IL_FA_TOO_MANY;
		/* Store क्रम "fewer than desired" on later beacon */
		data->nrg_silence_ref = silence_ref;

		/* increase energy threshold (reduce nrg value)
		 *   to decrease sensitivity */
		data->nrg_th_cck = data->nrg_th_cck - NRG_STEP_CCK;
		/* Else अगर we got fewer than desired, increase sensitivity */
	पूर्ण अन्यथा अगर (false_alarms < min_false_alarms) अणु
		data->nrg_curr_state = IL_FA_TOO_FEW;

		/* Compare silence level with silence level क्रम most recent
		 *   healthy number or too many false alarms */
		data->nrg_स्वतः_corr_silence_dअगरf =
		    (s32) data->nrg_silence_ref - (s32) silence_ref;

		D_CALIB("norm FA %u < min FA %u, silence diff %d\n",
			false_alarms, min_false_alarms,
			data->nrg_स्वतः_corr_silence_dअगरf);

		/* Increase value to increase sensitivity, but only अगर:
		 * 1a) previous beacon did *not* have *too many* false alarms
		 * 1b) AND there's a signअगरicant dअगरference in Rx levels
		 *      from a previous beacon with too many, or healthy # FAs
		 * OR 2) We've seen a lot of beacons (100) with too few
		 *       false alarms */
		अगर (data->nrg_prev_state != IL_FA_TOO_MANY &&
		    (data->nrg_स्वतः_corr_silence_dअगरf > NRG_DIFF ||
		     data->num_in_cck_no_fa > MAX_NUMBER_CCK_NO_FA)) अणु

			D_CALIB("... increasing sensitivity\n");
			/* Increase nrg value to increase sensitivity */
			val = data->nrg_th_cck + NRG_STEP_CCK;
			data->nrg_th_cck = min((u32) ranges->min_nrg_cck, val);
		पूर्ण अन्यथा अणु
			D_CALIB("... but not changing sensitivity\n");
		पूर्ण

		/* Else we got a healthy number of false alarms, keep status quo */
	पूर्ण अन्यथा अणु
		D_CALIB(" FA in safe zone\n");
		data->nrg_curr_state = IL_FA_GOOD_RANGE;

		/* Store क्रम use in "fewer than desired" with later beacon */
		data->nrg_silence_ref = silence_ref;

		/* If previous beacon had too many false alarms,
		 *   give it some extra margin by reducing sensitivity again
		 *   (but करोn't go below measured energy of desired Rx) */
		अगर (IL_FA_TOO_MANY == data->nrg_prev_state) अणु
			D_CALIB("... increasing margin\n");
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
	D_CALIB("new nrg_th_cck %u\n", data->nrg_th_cck);

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
			    min((u32) ranges->स्वतः_corr_max_cck, val);
		पूर्ण
		val = data->स्वतः_corr_cck_mrc + AUTO_CORR_STEP_CCK;
		data->स्वतः_corr_cck_mrc =
		    min((u32) ranges->स्वतः_corr_max_cck_mrc, val);
	पूर्ण अन्यथा अगर (false_alarms < min_false_alarms &&
		   (data->nrg_स्वतः_corr_silence_dअगरf > NRG_DIFF ||
		    data->num_in_cck_no_fa > MAX_NUMBER_CCK_NO_FA)) अणु

		/* Decrease स्वतः_corr values to increase sensitivity */
		val = data->स्वतः_corr_cck - AUTO_CORR_STEP_CCK;
		data->स्वतः_corr_cck = max((u32) ranges->स्वतः_corr_min_cck, val);
		val = data->स्वतः_corr_cck_mrc - AUTO_CORR_STEP_CCK;
		data->स्वतः_corr_cck_mrc =
		    max((u32) ranges->स्वतः_corr_min_cck_mrc, val);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
il4965_sens_स्वतः_corr_ofdm(काष्ठा il_priv *il, u32 norm_fa, u32 rx_enable_समय)
अणु
	u32 val;
	u32 false_alarms = norm_fa * 200 * 1024;
	u32 max_false_alarms = MAX_FA_OFDM * rx_enable_समय;
	u32 min_false_alarms = MIN_FA_OFDM * rx_enable_समय;
	काष्ठा il_sensitivity_data *data = शून्य;
	स्थिर काष्ठा il_sensitivity_ranges *ranges = il->hw_params.sens;

	data = &(il->sensitivity_data);

	/* If we got too many false alarms this समय, reduce sensitivity */
	अगर (false_alarms > max_false_alarms) अणु

		D_CALIB("norm FA %u > max FA %u)\n", false_alarms,
			max_false_alarms);

		val = data->स्वतः_corr_ofdm + AUTO_CORR_STEP_OFDM;
		data->स्वतः_corr_ofdm =
		    min((u32) ranges->स्वतः_corr_max_ofdm, val);

		val = data->स्वतः_corr_ofdm_mrc + AUTO_CORR_STEP_OFDM;
		data->स्वतः_corr_ofdm_mrc =
		    min((u32) ranges->स्वतः_corr_max_ofdm_mrc, val);

		val = data->स्वतः_corr_ofdm_x1 + AUTO_CORR_STEP_OFDM;
		data->स्वतः_corr_ofdm_x1 =
		    min((u32) ranges->स्वतः_corr_max_ofdm_x1, val);

		val = data->स्वतः_corr_ofdm_mrc_x1 + AUTO_CORR_STEP_OFDM;
		data->स्वतः_corr_ofdm_mrc_x1 =
		    min((u32) ranges->स्वतः_corr_max_ofdm_mrc_x1, val);
	पूर्ण

	/* Else अगर we got fewer than desired, increase sensitivity */
	अन्यथा अगर (false_alarms < min_false_alarms) अणु

		D_CALIB("norm FA %u < min FA %u\n", false_alarms,
			min_false_alarms);

		val = data->स्वतः_corr_ofdm - AUTO_CORR_STEP_OFDM;
		data->स्वतः_corr_ofdm =
		    max((u32) ranges->स्वतः_corr_min_ofdm, val);

		val = data->स्वतः_corr_ofdm_mrc - AUTO_CORR_STEP_OFDM;
		data->स्वतः_corr_ofdm_mrc =
		    max((u32) ranges->स्वतः_corr_min_ofdm_mrc, val);

		val = data->स्वतः_corr_ofdm_x1 - AUTO_CORR_STEP_OFDM;
		data->स्वतः_corr_ofdm_x1 =
		    max((u32) ranges->स्वतः_corr_min_ofdm_x1, val);

		val = data->स्वतः_corr_ofdm_mrc_x1 - AUTO_CORR_STEP_OFDM;
		data->स्वतः_corr_ofdm_mrc_x1 =
		    max((u32) ranges->स्वतः_corr_min_ofdm_mrc_x1, val);
	पूर्ण अन्यथा अणु
		D_CALIB("min FA %u < norm FA %u < max FA %u OK\n",
			min_false_alarms, false_alarms, max_false_alarms);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
il4965_prepare_legacy_sensitivity_tbl(काष्ठा il_priv *il,
				      काष्ठा il_sensitivity_data *data,
				      __le16 *tbl)
अणु
	tbl[HD_AUTO_CORR32_X4_TH_ADD_MIN_IDX] =
	    cpu_to_le16((u16) data->स्वतः_corr_ofdm);
	tbl[HD_AUTO_CORR32_X4_TH_ADD_MIN_MRC_IDX] =
	    cpu_to_le16((u16) data->स्वतः_corr_ofdm_mrc);
	tbl[HD_AUTO_CORR32_X1_TH_ADD_MIN_IDX] =
	    cpu_to_le16((u16) data->स्वतः_corr_ofdm_x1);
	tbl[HD_AUTO_CORR32_X1_TH_ADD_MIN_MRC_IDX] =
	    cpu_to_le16((u16) data->स्वतः_corr_ofdm_mrc_x1);

	tbl[HD_AUTO_CORR40_X4_TH_ADD_MIN_IDX] =
	    cpu_to_le16((u16) data->स्वतः_corr_cck);
	tbl[HD_AUTO_CORR40_X4_TH_ADD_MIN_MRC_IDX] =
	    cpu_to_le16((u16) data->स्वतः_corr_cck_mrc);

	tbl[HD_MIN_ENERGY_CCK_DET_IDX] = cpu_to_le16((u16) data->nrg_th_cck);
	tbl[HD_MIN_ENERGY_OFDM_DET_IDX] = cpu_to_le16((u16) data->nrg_th_ofdm);

	tbl[HD_BARKER_CORR_TH_ADD_MIN_IDX] =
	    cpu_to_le16(data->barker_corr_th_min);
	tbl[HD_BARKER_CORR_TH_ADD_MIN_MRC_IDX] =
	    cpu_to_le16(data->barker_corr_th_min_mrc);
	tbl[HD_OFDM_ENERGY_TH_IN_IDX] = cpu_to_le16(data->nrg_th_cca);

	D_CALIB("ofdm: ac %u mrc %u x1 %u mrc_x1 %u thresh %u\n",
		data->स्वतः_corr_ofdm, data->स्वतः_corr_ofdm_mrc,
		data->स्वतः_corr_ofdm_x1, data->स्वतः_corr_ofdm_mrc_x1,
		data->nrg_th_ofdm);

	D_CALIB("cck: ac %u mrc %u thresh %u\n", data->स्वतः_corr_cck,
		data->स्वतः_corr_cck_mrc, data->nrg_th_cck);
पूर्ण

/* Prepare a C_SENSITIVITY, send to uCode अगर values have changed */
अटल पूर्णांक
il4965_sensitivity_ग_लिखो(काष्ठा il_priv *il)
अणु
	काष्ठा il_sensitivity_cmd cmd;
	काष्ठा il_sensitivity_data *data = शून्य;
	काष्ठा il_host_cmd cmd_out = अणु
		.id = C_SENSITIVITY,
		.len = माप(काष्ठा il_sensitivity_cmd),
		.flags = CMD_ASYNC,
		.data = &cmd,
	पूर्ण;

	data = &(il->sensitivity_data);

	स_रखो(&cmd, 0, माप(cmd));

	il4965_prepare_legacy_sensitivity_tbl(il, data, &cmd.table[0]);

	/* Update uCode's "work" table, and copy it to DSP */
	cmd.control = C_SENSITIVITY_CONTROL_WORK_TBL;

	/* Don't send command to uCode अगर nothing has changed */
	अगर (!स_भेद
	    (&cmd.table[0], &(il->sensitivity_tbl[0]),
	     माप(u16) * HD_TBL_SIZE)) अणु
		D_CALIB("No change in C_SENSITIVITY\n");
		वापस 0;
	पूर्ण

	/* Copy table क्रम comparison next समय */
	स_नकल(&(il->sensitivity_tbl[0]), &(cmd.table[0]),
	       माप(u16) * HD_TBL_SIZE);

	वापस il_send_cmd(il, &cmd_out);
पूर्ण

व्योम
il4965_init_sensitivity(काष्ठा il_priv *il)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i;
	काष्ठा il_sensitivity_data *data = शून्य;
	स्थिर काष्ठा il_sensitivity_ranges *ranges = il->hw_params.sens;

	अगर (il->disable_sens_cal)
		वापस;

	D_CALIB("Start il4965_init_sensitivity\n");

	/* Clear driver's sensitivity algo data */
	data = &(il->sensitivity_data);

	अगर (ranges == शून्य)
		वापस;

	स_रखो(data, 0, माप(काष्ठा il_sensitivity_data));

	data->num_in_cck_no_fa = 0;
	data->nrg_curr_state = IL_FA_TOO_MANY;
	data->nrg_prev_state = IL_FA_TOO_MANY;
	data->nrg_silence_ref = 0;
	data->nrg_silence_idx = 0;
	data->nrg_energy_idx = 0;

	क्रम (i = 0; i < 10; i++)
		data->nrg_value[i] = 0;

	क्रम (i = 0; i < NRG_NUM_PREV_STAT_L; i++)
		data->nrg_silence_rssi[i] = 0;

	data->स्वतः_corr_ofdm = ranges->स्वतः_corr_min_ofdm;
	data->स्वतः_corr_ofdm_mrc = ranges->स्वतः_corr_min_ofdm_mrc;
	data->स्वतः_corr_ofdm_x1 = ranges->स्वतः_corr_min_ofdm_x1;
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

	ret |= il4965_sensitivity_ग_लिखो(il);
	D_CALIB("<<return 0x%X\n", ret);
पूर्ण

व्योम
il4965_sensitivity_calibration(काष्ठा il_priv *il, व्योम *resp)
अणु
	u32 rx_enable_समय;
	u32 fa_cck;
	u32 fa_ofdm;
	u32 bad_plcp_cck;
	u32 bad_plcp_ofdm;
	u32 norm_fa_ofdm;
	u32 norm_fa_cck;
	काष्ठा il_sensitivity_data *data = शून्य;
	काष्ठा stats_rx_non_phy *rx_info;
	काष्ठा stats_rx_phy *ofdm, *cck;
	अचिन्हित दीर्घ flags;
	काष्ठा stats_general_data statis;

	अगर (il->disable_sens_cal)
		वापस;

	data = &(il->sensitivity_data);

	अगर (!il_is_any_associated(il)) अणु
		D_CALIB("<< - not associated\n");
		वापस;
	पूर्ण

	spin_lock_irqsave(&il->lock, flags);

	rx_info = &(((काष्ठा il_notअगर_stats *)resp)->rx.general);
	ofdm = &(((काष्ठा il_notअगर_stats *)resp)->rx.ofdm);
	cck = &(((काष्ठा il_notअगर_stats *)resp)->rx.cck);

	अगर (rx_info->पूर्णांकerference_data_flag != INTERFERENCE_DATA_AVAILABLE) अणु
		D_CALIB("<< invalid data.\n");
		spin_unlock_irqrestore(&il->lock, flags);
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
	statis.beacon_energy_a = le32_to_cpu(rx_info->beacon_energy_a);
	statis.beacon_energy_b = le32_to_cpu(rx_info->beacon_energy_b);
	statis.beacon_energy_c = le32_to_cpu(rx_info->beacon_energy_c);

	spin_unlock_irqrestore(&il->lock, flags);

	D_CALIB("rx_enable_time = %u usecs\n", rx_enable_समय);

	अगर (!rx_enable_समय) अणु
		D_CALIB("<< RX Enable Time == 0!\n");
		वापस;
	पूर्ण

	/* These stats increase monotonically, and करो not reset
	 *   at each beacon.  Calculate dअगरference from last value, or just
	 *   use the new stats value अगर it has reset or wrapped around. */
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

	D_CALIB("cck: fa %u badp %u  ofdm: fa %u badp %u\n", fa_cck,
		bad_plcp_cck, fa_ofdm, bad_plcp_ofdm);

	il4965_sens_स्वतः_corr_ofdm(il, norm_fa_ofdm, rx_enable_समय);
	il4965_sens_energy_cck(il, norm_fa_cck, rx_enable_समय, &statis);

	il4965_sensitivity_ग_लिखो(il);
पूर्ण

अटल अंतरभूत u8
il4965_find_first_chain(u8 mask)
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
अटल व्योम
il4965_find_disconn_antenna(काष्ठा il_priv *il, u32 * average_sig,
			    काष्ठा il_chain_noise_data *data)
अणु
	u32 active_chains = 0;
	u32 max_average_sig;
	u16 max_average_sig_antenna_i;
	u8 num_tx_chains;
	u8 first_chain;
	u16 i = 0;

	average_sig[0] =
	    data->chain_संकेत_a /
	    il->cfg->chain_noise_num_beacons;
	average_sig[1] =
	    data->chain_संकेत_b /
	    il->cfg->chain_noise_num_beacons;
	average_sig[2] =
	    data->chain_संकेत_c /
	    il->cfg->chain_noise_num_beacons;

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

	D_CALIB("average_sig: a %d b %d c %d\n", average_sig[0], average_sig[1],
		average_sig[2]);
	D_CALIB("max_average_sig = %d, antenna %d\n", max_average_sig,
		max_average_sig_antenna_i);

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
			D_CALIB("i = %d  rssiDelta = %d  "
				"disconn_array[i] = %d\n", i, rssi_delta,
				data->disconn_array[i]);
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
	active_chains &= il->hw_params.valid_rx_ant;

	num_tx_chains = 0;
	क्रम (i = 0; i < NUM_RX_CHAINS; i++) अणु
		/* loops on all the bits of
		 * il->hw_setting.valid_tx_ant */
		u8 ant_msk = (1 << i);
		अगर (!(il->hw_params.valid_tx_ant & ant_msk))
			जारी;

		num_tx_chains++;
		अगर (data->disconn_array[i] == 0)
			/* there is a Tx antenna connected */
			अवरोध;
		अगर (num_tx_chains == il->hw_params.tx_chains_num &&
		    data->disconn_array[i]) अणु
			/*
			 * If all chains are disconnected
			 * connect the first valid tx chain
			 */
			first_chain =
			    il4965_find_first_chain(il->cfg->valid_tx_ant);
			data->disconn_array[first_chain] = 0;
			active_chains |= BIT(first_chain);
			D_CALIB("All Tx chains are disconnected"
				"- declare %d as connected\n", first_chain);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (active_chains != il->hw_params.valid_rx_ant &&
	    active_chains != il->chain_noise_data.active_chains)
		D_CALIB("Detected that not all antennas are connected! "
			"Connected: %#x, valid: %#x.\n", active_chains,
			il->hw_params.valid_rx_ant);

	/* Save क्रम use within RXON, TX, SCAN commands, etc. */
	data->active_chains = active_chains;
	D_CALIB("active_chains (bitwise) = 0x%x\n", active_chains);
पूर्ण

अटल व्योम
il4965_gain_computation(काष्ठा il_priv *il, u32 * average_noise,
			u16 min_average_noise_antenna_i, u32 min_average_noise,
			u8 शेष_chain)
अणु
	पूर्णांक i, ret;
	काष्ठा il_chain_noise_data *data = &il->chain_noise_data;

	data->delta_gain_code[min_average_noise_antenna_i] = 0;

	क्रम (i = शेष_chain; i < NUM_RX_CHAINS; i++) अणु
		s32 delta_g = 0;

		अगर (!data->disconn_array[i] &&
		    data->delta_gain_code[i] ==
		    CHAIN_NOISE_DELTA_GAIN_INIT_VAL) अणु
			delta_g = average_noise[i] - min_average_noise;
			data->delta_gain_code[i] = (u8) ((delta_g * 10) / 15);
			data->delta_gain_code[i] =
			    min(data->delta_gain_code[i],
				(u8) CHAIN_NOISE_MAX_DELTA_GAIN_CODE);

			data->delta_gain_code[i] =
			    (data->delta_gain_code[i] | (1 << 2));
		पूर्ण अन्यथा अणु
			data->delta_gain_code[i] = 0;
		पूर्ण
	पूर्ण
	D_CALIB("delta_gain_codes: a %d b %d c %d\n", data->delta_gain_code[0],
		data->delta_gain_code[1], data->delta_gain_code[2]);

	/* Dअगरferential gain माला_लो sent to uCode only once */
	अगर (!data->radio_ग_लिखो) अणु
		काष्ठा il_calib_dअगरf_gain_cmd cmd;
		data->radio_ग_लिखो = 1;

		स_रखो(&cmd, 0, माप(cmd));
		cmd.hdr.op_code = IL_PHY_CALIBRATE_DIFF_GAIN_CMD;
		cmd.dअगरf_gain_a = data->delta_gain_code[0];
		cmd.dअगरf_gain_b = data->delta_gain_code[1];
		cmd.dअगरf_gain_c = data->delta_gain_code[2];
		ret = il_send_cmd_pdu(il, C_PHY_CALIBRATION, माप(cmd), &cmd);
		अगर (ret)
			D_CALIB("fail sending cmd " "C_PHY_CALIBRATION\n");

		/* TODO we might want recalculate
		 * rx_chain in rxon cmd */

		/* Mark so we run this algo only once! */
		data->state = IL_CHAIN_NOISE_CALIBRATED;
	पूर्ण
पूर्ण

/*
 * Accumulate 16 beacons of संकेत and noise stats क्रम each of
 *   3 receivers/antennas/rx-chains, then figure out:
 * 1)  Which antennas are connected.
 * 2)  Dअगरferential rx gain settings to balance the 3 receivers.
 */
व्योम
il4965_chain_noise_calibration(काष्ठा il_priv *il, व्योम *stat_resp)
अणु
	काष्ठा il_chain_noise_data *data = शून्य;

	u32 chain_noise_a;
	u32 chain_noise_b;
	u32 chain_noise_c;
	u32 chain_sig_a;
	u32 chain_sig_b;
	u32 chain_sig_c;
	u32 average_sig[NUM_RX_CHAINS] = अणु INITIALIZATION_VALUE पूर्ण;
	u32 average_noise[NUM_RX_CHAINS] = अणु INITIALIZATION_VALUE पूर्ण;
	u32 min_average_noise = MIN_AVERAGE_NOISE_MAX_VALUE;
	u16 min_average_noise_antenna_i = INITIALIZATION_VALUE;
	u16 i = 0;
	u16 rxon_chnum = INITIALIZATION_VALUE;
	u16 stat_chnum = INITIALIZATION_VALUE;
	u8 rxon_band24;
	u8 stat_band24;
	अचिन्हित दीर्घ flags;
	काष्ठा stats_rx_non_phy *rx_info;

	अगर (il->disable_chain_noise_cal)
		वापस;

	data = &(il->chain_noise_data);

	/*
	 * Accumulate just the first "chain_noise_num_beacons" after
	 * the first association, then we're करोne क्रमever.
	 */
	अगर (data->state != IL_CHAIN_NOISE_ACCUMULATE) अणु
		अगर (data->state == IL_CHAIN_NOISE_ALIVE)
			D_CALIB("Wait for noise calib reset\n");
		वापस;
	पूर्ण

	spin_lock_irqsave(&il->lock, flags);

	rx_info = &(((काष्ठा il_notअगर_stats *)stat_resp)->rx.general);

	अगर (rx_info->पूर्णांकerference_data_flag != INTERFERENCE_DATA_AVAILABLE) अणु
		D_CALIB(" << Interference data unavailable\n");
		spin_unlock_irqrestore(&il->lock, flags);
		वापस;
	पूर्ण

	rxon_band24 = !!(il->staging.flags & RXON_FLG_BAND_24G_MSK);
	rxon_chnum = le16_to_cpu(il->staging.channel);

	stat_band24 =
	    !!(((काष्ठा il_notअगर_stats *)stat_resp)->
	       flag & STATS_REPLY_FLG_BAND_24G_MSK);
	stat_chnum =
	    le32_to_cpu(((काष्ठा il_notअगर_stats *)stat_resp)->flag) >> 16;

	/* Make sure we accumulate data क्रम just the associated channel
	 *   (even अगर scanning). */
	अगर (rxon_chnum != stat_chnum || rxon_band24 != stat_band24) अणु
		D_CALIB("Stats not from chan=%d, band24=%d\n", rxon_chnum,
			rxon_band24);
		spin_unlock_irqrestore(&il->lock, flags);
		वापस;
	पूर्ण

	/*
	 *  Accumulate beacon stats values across
	 * "chain_noise_num_beacons"
	 */
	chain_noise_a =
	    le32_to_cpu(rx_info->beacon_silence_rssi_a) & IN_BAND_FILTER;
	chain_noise_b =
	    le32_to_cpu(rx_info->beacon_silence_rssi_b) & IN_BAND_FILTER;
	chain_noise_c =
	    le32_to_cpu(rx_info->beacon_silence_rssi_c) & IN_BAND_FILTER;

	chain_sig_a = le32_to_cpu(rx_info->beacon_rssi_a) & IN_BAND_FILTER;
	chain_sig_b = le32_to_cpu(rx_info->beacon_rssi_b) & IN_BAND_FILTER;
	chain_sig_c = le32_to_cpu(rx_info->beacon_rssi_c) & IN_BAND_FILTER;

	spin_unlock_irqrestore(&il->lock, flags);

	data->beacon_count++;

	data->chain_noise_a = (chain_noise_a + data->chain_noise_a);
	data->chain_noise_b = (chain_noise_b + data->chain_noise_b);
	data->chain_noise_c = (chain_noise_c + data->chain_noise_c);

	data->chain_संकेत_a = (chain_sig_a + data->chain_संकेत_a);
	data->chain_संकेत_b = (chain_sig_b + data->chain_संकेत_b);
	data->chain_संकेत_c = (chain_sig_c + data->chain_संकेत_c);

	D_CALIB("chan=%d, band24=%d, beacon=%d\n", rxon_chnum, rxon_band24,
		data->beacon_count);
	D_CALIB("chain_sig: a %d b %d c %d\n", chain_sig_a, chain_sig_b,
		chain_sig_c);
	D_CALIB("chain_noise: a %d b %d c %d\n", chain_noise_a, chain_noise_b,
		chain_noise_c);

	/* If this is the "chain_noise_num_beacons", determine:
	 * 1)  Disconnected antennas (using संकेत strengths)
	 * 2)  Dअगरferential gain (using silence noise) to balance receivers */
	अगर (data->beacon_count != il->cfg->chain_noise_num_beacons)
		वापस;

	/* Analyze संकेत क्रम disconnected antenna */
	il4965_find_disconn_antenna(il, average_sig, data);

	/* Analyze noise क्रम rx balance */
	average_noise[0] =
	    data->chain_noise_a / il->cfg->chain_noise_num_beacons;
	average_noise[1] =
	    data->chain_noise_b / il->cfg->chain_noise_num_beacons;
	average_noise[2] =
	    data->chain_noise_c / il->cfg->chain_noise_num_beacons;

	क्रम (i = 0; i < NUM_RX_CHAINS; i++) अणु
		अगर (!data->disconn_array[i] &&
		    average_noise[i] <= min_average_noise) अणु
			/* This means that chain i is active and has
			 * lower noise values so far: */
			min_average_noise = average_noise[i];
			min_average_noise_antenna_i = i;
		पूर्ण
	पूर्ण

	D_CALIB("average_noise: a %d b %d c %d\n", average_noise[0],
		average_noise[1], average_noise[2]);

	D_CALIB("min_average_noise = %d, antenna %d\n", min_average_noise,
		min_average_noise_antenna_i);

	il4965_gain_computation(il, average_noise, min_average_noise_antenna_i,
				min_average_noise,
				il4965_find_first_chain(il->cfg->valid_rx_ant));

	/* Some घातer changes may have been made during the calibration.
	 * Update and commit the RXON
	 */
	अगर (il->ops->update_chain_flags)
		il->ops->update_chain_flags(il);

	data->state = IL_CHAIN_NOISE_DONE;
	il_घातer_update_mode(il, false);
पूर्ण

व्योम
il4965_reset_run_समय_calib(काष्ठा il_priv *il)
अणु
	पूर्णांक i;
	स_रखो(&(il->sensitivity_data), 0, माप(काष्ठा il_sensitivity_data));
	स_रखो(&(il->chain_noise_data), 0, माप(काष्ठा il_chain_noise_data));
	क्रम (i = 0; i < NUM_RX_CHAINS; i++)
		il->chain_noise_data.delta_gain_code[i] =
		    CHAIN_NOISE_DELTA_GAIN_INIT_VAL;

	/* Ask क्रम stats now, the uCode will send notअगरication
	 * periodically after association */
	il_send_stats_request(il, CMD_ASYNC, true);
पूर्ण
