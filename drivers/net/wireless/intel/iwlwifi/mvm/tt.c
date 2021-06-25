<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2012-2014, 2019-2020 Intel Corporation
 * Copyright (C) 2013-2014 Intel Mobile Communications GmbH
 * Copyright (C) 2015-2016 Intel Deutschland GmbH
 */
#समावेश <linux/sort.h>

#समावेश "mvm.h"

#घोषणा IWL_MVM_TEMP_NOTIF_WAIT_TIMEOUT	HZ

व्योम iwl_mvm_enter_ctसमाप्त(काष्ठा iwl_mvm *mvm)
अणु
	काष्ठा iwl_mvm_tt_mgmt *tt = &mvm->thermal_throttle;
	u32 duration = tt->params.ct_समाप्त_duration;

	अगर (test_bit(IWL_MVM_STATUS_HW_CTKILL, &mvm->status))
		वापस;

	IWL_ERR(mvm, "Enter CT Kill\n");
	iwl_mvm_set_hw_ctसमाप्त_state(mvm, true);

	अगर (!iwl_mvm_is_tt_in_fw(mvm)) अणु
		tt->throttle = false;
		tt->dynamic_smps = false;
	पूर्ण

	/* Don't schedule an exit work if we're in test mode, since
	 * the temperature will not change unless we manually set it
	 * again (or disable testing).
	 */
	अगर (!mvm->temperature_test)
		schedule_delayed_work(&tt->ct_समाप्त_निकास,
				      round_jअगरfies_relative(duration * HZ));
पूर्ण

अटल व्योम iwl_mvm_निकास_ctसमाप्त(काष्ठा iwl_mvm *mvm)
अणु
	अगर (!test_bit(IWL_MVM_STATUS_HW_CTKILL, &mvm->status))
		वापस;

	IWL_ERR(mvm, "Exit CT Kill\n");
	iwl_mvm_set_hw_ctसमाप्त_state(mvm, false);
पूर्ण

अटल व्योम iwl_mvm_tt_temp_changed(काष्ठा iwl_mvm *mvm, u32 temp)
अणु
	/* ignore the notअगरication अगर we are in test mode */
	अगर (mvm->temperature_test)
		वापस;

	अगर (mvm->temperature == temp)
		वापस;

	mvm->temperature = temp;
	iwl_mvm_tt_handler(mvm);
पूर्ण

अटल पूर्णांक iwl_mvm_temp_notअगर_parse(काष्ठा iwl_mvm *mvm,
				    काष्ठा iwl_rx_packet *pkt)
अणु
	काष्ठा iwl_dts_measurement_notअगर_v1 *notअगर_v1;
	पूर्णांक len = iwl_rx_packet_payload_len(pkt);
	पूर्णांक temp;

	/* we can use notअगर_v1 only, because v2 only adds an additional
	 * parameter, which is not used in this function.
	*/
	अगर (WARN_ON_ONCE(len < माप(*notअगर_v1))) अणु
		IWL_ERR(mvm, "Invalid DTS_MEASUREMENT_NOTIFICATION\n");
		वापस -EINVAL;
	पूर्ण

	notअगर_v1 = (व्योम *)pkt->data;

	temp = le32_to_cpu(notअगर_v1->temp);

	/* shouldn't be negative, but since it's s32, make sure it isn't */
	अगर (WARN_ON_ONCE(temp < 0))
		temp = 0;

	IWL_DEBUG_TEMP(mvm, "DTS_MEASUREMENT_NOTIFICATION - %d\n", temp);

	वापस temp;
पूर्ण

अटल bool iwl_mvm_temp_notअगर_रुको(काष्ठा iwl_notअगर_रुको_data *notअगर_रुको,
				    काष्ठा iwl_rx_packet *pkt, व्योम *data)
अणु
	काष्ठा iwl_mvm *mvm =
		container_of(notअगर_रुको, काष्ठा iwl_mvm, notअगर_रुको);
	पूर्णांक *temp = data;
	पूर्णांक ret;

	ret = iwl_mvm_temp_notअगर_parse(mvm, pkt);
	अगर (ret < 0)
		वापस true;

	*temp = ret;

	वापस true;
पूर्ण

व्योम iwl_mvm_temp_notअगर(काष्ठा iwl_mvm *mvm, काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_dts_measurement_notअगर_v2 *notअगर_v2;
	पूर्णांक len = iwl_rx_packet_payload_len(pkt);
	पूर्णांक temp;
	u32 ths_crossed;

	/* the notअगरication is handled synchronously in ctसमाप्त, so skip here */
	अगर (test_bit(IWL_MVM_STATUS_HW_CTKILL, &mvm->status))
		वापस;

	temp = iwl_mvm_temp_notअगर_parse(mvm, pkt);

	अगर (!iwl_mvm_is_tt_in_fw(mvm)) अणु
		अगर (temp >= 0)
			iwl_mvm_tt_temp_changed(mvm, temp);
		वापस;
	पूर्ण

	अगर (WARN_ON_ONCE(len < माप(*notअगर_v2))) अणु
		IWL_ERR(mvm, "Invalid DTS_MEASUREMENT_NOTIFICATION\n");
		वापस;
	पूर्ण

	notअगर_v2 = (व्योम *)pkt->data;
	ths_crossed = le32_to_cpu(notअगर_v2->threshold_idx);

	/* 0xFF in ths_crossed means the notअगरication is not related
	 * to a trip, so we can ignore it here.
	 */
	अगर (ths_crossed == 0xFF)
		वापस;

	IWL_DEBUG_TEMP(mvm, "Temp = %d Threshold crossed = %d\n",
		       temp, ths_crossed);

#अगर_घोषित CONFIG_THERMAL
	अगर (WARN_ON(ths_crossed >= IWL_MAX_DTS_TRIPS))
		वापस;

	अगर (mvm->tz_device.tzone) अणु
		काष्ठा iwl_mvm_thermal_device *tz_dev = &mvm->tz_device;

		thermal_zone_device_update(tz_dev->tzone,
					   THERMAL_TRIP_VIOLATED);
	पूर्ण
#पूर्ण_अगर /* CONFIG_THERMAL */
पूर्ण

व्योम iwl_mvm_ct_समाप्त_notअगर(काष्ठा iwl_mvm *mvm, काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा ct_समाप्त_notअगर *notअगर;

	notअगर = (काष्ठा ct_समाप्त_notअगर *)pkt->data;
	IWL_DEBUG_TEMP(mvm, "CT Kill notification temperature = %d\n",
		       notअगर->temperature);

	iwl_mvm_enter_ctसमाप्त(mvm);
पूर्ण

/*
 * send the DTS_MEASUREMENT_TRIGGER command with or without रुकोing क्रम a
 * response. If we get a response then the measurement is stored in 'temp'
 */
अटल पूर्णांक iwl_mvm_send_temp_cmd(काष्ठा iwl_mvm *mvm, bool response, s32 *temp)
अणु
	काष्ठा iwl_host_cmd cmd = अणुपूर्ण;
	काष्ठा iwl_dts_measurement_cmd dts_cmd = अणु
		.flags = cpu_to_le32(DTS_TRIGGER_CMD_FLAGS_TEMP),
	पूर्ण;
	काष्ठा iwl_ext_dts_measurement_cmd ext_cmd = अणु
		.control_mode = cpu_to_le32(DTS_सूचीECT_WITHOUT_MEASURE),
	पूर्ण;
	काष्ठा iwl_dts_measurement_resp *resp;
	व्योम *cmd_ptr;
	पूर्णांक ret;
	u32 cmd_flags = 0;
	u16 len;

	/* Check which command क्रमmat is used (regular/extended) */
	अगर (fw_has_capa(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_EXTENDED_DTS_MEASURE)) अणु
		len = माप(ext_cmd);
		cmd_ptr = &ext_cmd;
	पूर्ण अन्यथा अणु
		len = माप(dts_cmd);
		cmd_ptr = &dts_cmd;
	पूर्ण
	/* The command version where we get a response is zero length */
	अगर (response) अणु
		cmd_flags = CMD_WANT_SKB;
		len = 0;
	पूर्ण

	cmd.id =  WIDE_ID(PHY_OPS_GROUP, CMD_DTS_MEASUREMENT_TRIGGER_WIDE);
	cmd.len[0] = len;
	cmd.flags = cmd_flags;
	cmd.data[0] = cmd_ptr;

	IWL_DEBUG_TEMP(mvm,
		       "Sending temperature measurement command - %s response\n",
		       response ? "with" : "without");
	ret = iwl_mvm_send_cmd(mvm, &cmd);

	अगर (ret) अणु
		IWL_ERR(mvm,
			"Failed to send the temperature measurement command (err=%d)\n",
			ret);
		वापस ret;
	पूर्ण

	अगर (response) अणु
		resp = (व्योम *)cmd.resp_pkt->data;
		*temp = le32_to_cpu(resp->temp);
		IWL_DEBUG_TEMP(mvm,
			       "Got temperature measurement response: temp=%d\n",
			       *temp);
		iwl_मुक्त_resp(&cmd);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक iwl_mvm_get_temp(काष्ठा iwl_mvm *mvm, s32 *temp)
अणु
	काष्ठा iwl_notअगरication_रुको रुको_temp_notअगर;
	अटल u16 temp_notअगर[] = अणु WIDE_ID(PHY_OPS_GROUP,
					    DTS_MEASUREMENT_NOTIF_WIDE) पूर्ण;
	पूर्णांक ret;
	u8 cmd_ver;

	/*
	 * If command version is 1 we send the command and immediately get
	 * a response. For older versions we send the command and रुको क्रम a
	 * notअगरication (no command TLV क्रम previous versions).
	 */
	cmd_ver = iwl_fw_lookup_cmd_ver(mvm->fw, PHY_OPS_GROUP,
					CMD_DTS_MEASUREMENT_TRIGGER_WIDE,
					IWL_FW_CMD_VER_UNKNOWN);
	अगर (cmd_ver == 1)
		वापस iwl_mvm_send_temp_cmd(mvm, true, temp);

	lockdep_निश्चित_held(&mvm->mutex);

	iwl_init_notअगरication_रुको(&mvm->notअगर_रुको, &रुको_temp_notअगर,
				   temp_notअगर, ARRAY_SIZE(temp_notअगर),
				   iwl_mvm_temp_notअगर_रुको, temp);

	ret = iwl_mvm_send_temp_cmd(mvm, false, temp);
	अगर (ret) अणु
		iwl_हटाओ_notअगरication(&mvm->notअगर_रुको, &रुको_temp_notअगर);
		वापस ret;
	पूर्ण

	ret = iwl_रुको_notअगरication(&mvm->notअगर_रुको, &रुको_temp_notअगर,
				    IWL_MVM_TEMP_NOTIF_WAIT_TIMEOUT);
	अगर (ret)
		IWL_WARN(mvm, "Getting the temperature timed out\n");

	वापस ret;
पूर्ण

अटल व्योम check_निकास_ctसमाप्त(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा iwl_mvm_tt_mgmt *tt;
	काष्ठा iwl_mvm *mvm;
	u32 duration;
	s32 temp;
	पूर्णांक ret;

	tt = container_of(work, काष्ठा iwl_mvm_tt_mgmt, ct_समाप्त_निकास.work);
	mvm = container_of(tt, काष्ठा iwl_mvm, thermal_throttle);

	अगर (iwl_mvm_is_tt_in_fw(mvm)) अणु
		iwl_mvm_निकास_ctसमाप्त(mvm);

		वापस;
	पूर्ण

	duration = tt->params.ct_समाप्त_duration;

	flush_work(&mvm->roc_करोne_wk);

	mutex_lock(&mvm->mutex);

	अगर (__iwl_mvm_mac_start(mvm))
		जाओ reschedule;

	ret = iwl_mvm_get_temp(mvm, &temp);

	__iwl_mvm_mac_stop(mvm);

	अगर (ret)
		जाओ reschedule;

	IWL_DEBUG_TEMP(mvm, "NIC temperature: %d\n", temp);

	अगर (temp <= tt->params.ct_समाप्त_निकास) अणु
		mutex_unlock(&mvm->mutex);
		iwl_mvm_निकास_ctसमाप्त(mvm);
		वापस;
	पूर्ण

reschedule:
	mutex_unlock(&mvm->mutex);
	schedule_delayed_work(&mvm->thermal_throttle.ct_समाप्त_निकास,
			      round_jअगरfies(duration * HZ));
पूर्ण

अटल व्योम iwl_mvm_tt_smps_iterator(व्योम *_data, u8 *mac,
				     काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm *mvm = _data;
	क्रमागत ieee80211_smps_mode smps_mode;

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (mvm->thermal_throttle.dynamic_smps)
		smps_mode = IEEE80211_SMPS_DYNAMIC;
	अन्यथा
		smps_mode = IEEE80211_SMPS_AUTOMATIC;

	अगर (vअगर->type != NL80211_IFTYPE_STATION)
		वापस;

	iwl_mvm_update_smps(mvm, vअगर, IWL_MVM_SMPS_REQ_TT, smps_mode);
पूर्ण

अटल व्योम iwl_mvm_tt_tx_protection(काष्ठा iwl_mvm *mvm, bool enable)
अणु
	काष्ठा iwl_mvm_sta *mvmsta;
	पूर्णांक i, err;

	क्रम (i = 0; i < mvm->fw->ucode_capa.num_stations; i++) अणु
		mvmsta = iwl_mvm_sta_from_staid_रक्षित(mvm, i);
		अगर (!mvmsta)
			जारी;

		अगर (enable == mvmsta->tt_tx_protection)
			जारी;
		err = iwl_mvm_tx_protection(mvm, mvmsta, enable);
		अगर (err) अणु
			IWL_ERR(mvm, "Failed to %s Tx protection\n",
				enable ? "enable" : "disable");
		पूर्ण अन्यथा अणु
			IWL_DEBUG_TEMP(mvm, "%s Tx protection\n",
				       enable ? "Enable" : "Disable");
			mvmsta->tt_tx_protection = enable;
		पूर्ण
	पूर्ण
पूर्ण

व्योम iwl_mvm_tt_tx_backoff(काष्ठा iwl_mvm *mvm, u32 backoff)
अणु
	काष्ठा iwl_host_cmd cmd = अणु
		.id = REPLY_THERMAL_MNG_BACKOFF,
		.len = अणु माप(u32), पूर्ण,
		.data = अणु &backoff, पूर्ण,
	पूर्ण;

	backoff = max(backoff, mvm->thermal_throttle.min_backoff);

	अगर (iwl_mvm_send_cmd(mvm, &cmd) == 0) अणु
		IWL_DEBUG_TEMP(mvm, "Set Thermal Tx backoff to: %u\n",
			       backoff);
		mvm->thermal_throttle.tx_backoff = backoff;
	पूर्ण अन्यथा अणु
		IWL_ERR(mvm, "Failed to change Thermal Tx backoff\n");
	पूर्ण
पूर्ण

व्योम iwl_mvm_tt_handler(काष्ठा iwl_mvm *mvm)
अणु
	काष्ठा iwl_tt_params *params = &mvm->thermal_throttle.params;
	काष्ठा iwl_mvm_tt_mgmt *tt = &mvm->thermal_throttle;
	s32 temperature = mvm->temperature;
	bool throttle_enable = false;
	पूर्णांक i;
	u32 tx_backoff;

	IWL_DEBUG_TEMP(mvm, "NIC temperature: %d\n", mvm->temperature);

	अगर (params->support_ct_समाप्त && temperature >= params->ct_समाप्त_entry) अणु
		iwl_mvm_enter_ctसमाप्त(mvm);
		वापस;
	पूर्ण

	अगर (params->support_ct_समाप्त &&
	    temperature <= params->ct_समाप्त_निकास) अणु
		iwl_mvm_निकास_ctसमाप्त(mvm);
		वापस;
	पूर्ण

	अगर (params->support_dynamic_smps) अणु
		अगर (!tt->dynamic_smps &&
		    temperature >= params->dynamic_smps_entry) अणु
			IWL_DEBUG_TEMP(mvm, "Enable dynamic SMPS\n");
			tt->dynamic_smps = true;
			ieee80211_iterate_active_पूर्णांकerfaces_atomic(
					mvm->hw, IEEE80211_IFACE_ITER_NORMAL,
					iwl_mvm_tt_smps_iterator, mvm);
			throttle_enable = true;
		पूर्ण अन्यथा अगर (tt->dynamic_smps &&
			   temperature <= params->dynamic_smps_निकास) अणु
			IWL_DEBUG_TEMP(mvm, "Disable dynamic SMPS\n");
			tt->dynamic_smps = false;
			ieee80211_iterate_active_पूर्णांकerfaces_atomic(
					mvm->hw, IEEE80211_IFACE_ITER_NORMAL,
					iwl_mvm_tt_smps_iterator, mvm);
		पूर्ण
	पूर्ण

	अगर (params->support_tx_protection) अणु
		अगर (temperature >= params->tx_protection_entry) अणु
			iwl_mvm_tt_tx_protection(mvm, true);
			throttle_enable = true;
		पूर्ण अन्यथा अगर (temperature <= params->tx_protection_निकास) अणु
			iwl_mvm_tt_tx_protection(mvm, false);
		पूर्ण
	पूर्ण

	अगर (params->support_tx_backoff) अणु
		tx_backoff = tt->min_backoff;
		क्रम (i = 0; i < TT_TX_BACKOFF_SIZE; i++) अणु
			अगर (temperature < params->tx_backoff[i].temperature)
				अवरोध;
			tx_backoff = max(tt->min_backoff,
					 params->tx_backoff[i].backoff);
		पूर्ण
		अगर (tx_backoff != tt->min_backoff)
			throttle_enable = true;
		अगर (tt->tx_backoff != tx_backoff)
			iwl_mvm_tt_tx_backoff(mvm, tx_backoff);
	पूर्ण

	अगर (!tt->throttle && throttle_enable) अणु
		IWL_WARN(mvm,
			 "Due to high temperature thermal throttling initiated\n");
		tt->throttle = true;
	पूर्ण अन्यथा अगर (tt->throttle && !tt->dynamic_smps &&
		   tt->tx_backoff == tt->min_backoff &&
		   temperature <= params->tx_protection_निकास) अणु
		IWL_WARN(mvm,
			 "Temperature is back to normal thermal throttling stopped\n");
		tt->throttle = false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iwl_tt_params iwl_mvm_शेष_tt_params = अणु
	.ct_समाप्त_entry = 118,
	.ct_समाप्त_निकास = 96,
	.ct_समाप्त_duration = 5,
	.dynamic_smps_entry = 114,
	.dynamic_smps_निकास = 110,
	.tx_protection_entry = 114,
	.tx_protection_निकास = 108,
	.tx_backoff = अणु
		अणु.temperature = 112, .backoff = 200पूर्ण,
		अणु.temperature = 113, .backoff = 600पूर्ण,
		अणु.temperature = 114, .backoff = 1200पूर्ण,
		अणु.temperature = 115, .backoff = 2000पूर्ण,
		अणु.temperature = 116, .backoff = 4000पूर्ण,
		अणु.temperature = 117, .backoff = 10000पूर्ण,
	पूर्ण,
	.support_ct_समाप्त = true,
	.support_dynamic_smps = true,
	.support_tx_protection = true,
	.support_tx_backoff = true,
पूर्ण;

/* budget in mWatt */
अटल स्थिर u32 iwl_mvm_cdev_budमाला_लो[] = अणु
	2400,	/* cooling state 0 */
	2000,	/* cooling state 1 */
	1800,	/* cooling state 2 */
	1600,	/* cooling state 3 */
	1400,	/* cooling state 4 */
	1200,	/* cooling state 5 */
	1000,	/* cooling state 6 */
	900,	/* cooling state 7 */
	800,	/* cooling state 8 */
	700,	/* cooling state 9 */
	650,	/* cooling state 10 */
	600,	/* cooling state 11 */
	550,	/* cooling state 12 */
	500,	/* cooling state 13 */
	450,	/* cooling state 14 */
	400,	/* cooling state 15 */
	350,	/* cooling state 16 */
	300,	/* cooling state 17 */
	250,	/* cooling state 18 */
	200,	/* cooling state 19 */
	150,	/* cooling state 20 */
पूर्ण;

पूर्णांक iwl_mvm_ctdp_command(काष्ठा iwl_mvm *mvm, u32 op, u32 state)
अणु
	काष्ठा iwl_mvm_ctdp_cmd cmd = अणु
		.operation = cpu_to_le32(op),
		.budget = cpu_to_le32(iwl_mvm_cdev_budमाला_लो[state]),
		.winकरोw_size = 0,
	पूर्ण;
	पूर्णांक ret;
	u32 status;

	lockdep_निश्चित_held(&mvm->mutex);

	status = 0;
	ret = iwl_mvm_send_cmd_pdu_status(mvm, WIDE_ID(PHY_OPS_GROUP,
						       CTDP_CONFIG_CMD),
					  माप(cmd), &cmd, &status);

	अगर (ret) अणु
		IWL_ERR(mvm, "cTDP command failed (err=%d)\n", ret);
		वापस ret;
	पूर्ण

	चयन (op) अणु
	हाल CTDP_CMD_OPERATION_START:
#अगर_घोषित CONFIG_THERMAL
		mvm->cooling_dev.cur_state = state;
#पूर्ण_अगर /* CONFIG_THERMAL */
		अवरोध;
	हाल CTDP_CMD_OPERATION_REPORT:
		IWL_DEBUG_TEMP(mvm, "cTDP avg energy in mWatt = %d\n", status);
		/* when the function is called with CTDP_CMD_OPERATION_REPORT
		 * option the function should वापस the average budget value
		 * that is received from the FW.
		 * The budget can't be less or equal to 0, so it's possible
		 * to distinguish between error values and budमाला_लो.
		 */
		वापस status;
	हाल CTDP_CMD_OPERATION_STOP:
		IWL_DEBUG_TEMP(mvm, "cTDP stopped successfully\n");
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_THERMAL
अटल पूर्णांक compare_temps(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	वापस ((s16)le16_to_cpu(*(__le16 *)a) -
		(s16)le16_to_cpu(*(__le16 *)b));
पूर्ण
#पूर्ण_अगर

पूर्णांक iwl_mvm_send_temp_report_ths_cmd(काष्ठा iwl_mvm *mvm)
अणु
	काष्ठा temp_report_ths_cmd cmd = अणु0पूर्ण;
	पूर्णांक ret;
#अगर_घोषित CONFIG_THERMAL
	पूर्णांक i, j, idx = 0;

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (!mvm->tz_device.tzone)
		जाओ send;

	/* The driver holds array of temperature trips that are unsorted
	 * and uncompressed, the FW should get it compressed and sorted
	 */

	/* compress temp_trips to cmd array, हटाओ uninitialized values*/
	क्रम (i = 0; i < IWL_MAX_DTS_TRIPS; i++) अणु
		अगर (mvm->tz_device.temp_trips[i] != S16_MIN) अणु
			cmd.thresholds[idx++] =
				cpu_to_le16(mvm->tz_device.temp_trips[i]);
		पूर्ण
	पूर्ण
	cmd.num_temps = cpu_to_le32(idx);

	अगर (!idx)
		जाओ send;

	/*sort cmd array*/
	sort(cmd.thresholds, idx, माप(s16), compare_temps, शून्य);

	/* we should save the indexes of trips because we sort
	 * and compress the orginal array
	 */
	क्रम (i = 0; i < idx; i++) अणु
		क्रम (j = 0; j < IWL_MAX_DTS_TRIPS; j++) अणु
			अगर (le16_to_cpu(cmd.thresholds[i]) ==
				mvm->tz_device.temp_trips[j])
				mvm->tz_device.fw_trips_index[i] = j;
		पूर्ण
	पूर्ण

send:
#पूर्ण_अगर
	ret = iwl_mvm_send_cmd_pdu(mvm, WIDE_ID(PHY_OPS_GROUP,
						TEMP_REPORTING_THRESHOLDS_CMD),
				   0, माप(cmd), &cmd);
	अगर (ret)
		IWL_ERR(mvm, "TEMP_REPORT_THS_CMD command failed (err=%d)\n",
			ret);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_THERMAL
अटल पूर्णांक iwl_mvm_tzone_get_temp(काष्ठा thermal_zone_device *device,
				  पूर्णांक *temperature)
अणु
	काष्ठा iwl_mvm *mvm = (काष्ठा iwl_mvm *)device->devdata;
	पूर्णांक ret;
	पूर्णांक temp;

	mutex_lock(&mvm->mutex);

	अगर (!iwl_mvm_firmware_running(mvm) ||
	    mvm->fwrt.cur_fw_img != IWL_UCODE_REGULAR) अणु
		ret = -ENODATA;
		जाओ out;
	पूर्ण

	ret = iwl_mvm_get_temp(mvm, &temp);
	अगर (ret)
		जाओ out;

	*temperature = temp * 1000;

out:
	mutex_unlock(&mvm->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक iwl_mvm_tzone_get_trip_temp(काष्ठा thermal_zone_device *device,
				       पूर्णांक trip, पूर्णांक *temp)
अणु
	काष्ठा iwl_mvm *mvm = (काष्ठा iwl_mvm *)device->devdata;

	अगर (trip < 0 || trip >= IWL_MAX_DTS_TRIPS)
		वापस -EINVAL;

	*temp = mvm->tz_device.temp_trips[trip] * 1000;

	वापस 0;
पूर्ण

अटल पूर्णांक iwl_mvm_tzone_get_trip_type(काष्ठा thermal_zone_device *device,
				       पूर्णांक trip, क्रमागत thermal_trip_type *type)
अणु
	अगर (trip < 0 || trip >= IWL_MAX_DTS_TRIPS)
		वापस -EINVAL;

	*type = THERMAL_TRIP_PASSIVE;

	वापस 0;
पूर्ण

अटल पूर्णांक iwl_mvm_tzone_set_trip_temp(काष्ठा thermal_zone_device *device,
				       पूर्णांक trip, पूर्णांक temp)
अणु
	काष्ठा iwl_mvm *mvm = (काष्ठा iwl_mvm *)device->devdata;
	काष्ठा iwl_mvm_thermal_device *tzone;
	पूर्णांक i, ret;
	s16 temperature;

	mutex_lock(&mvm->mutex);

	अगर (!iwl_mvm_firmware_running(mvm) ||
	    mvm->fwrt.cur_fw_img != IWL_UCODE_REGULAR) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	अगर (trip < 0 || trip >= IWL_MAX_DTS_TRIPS) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर ((temp / 1000) > S16_MAX) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	temperature = (s16)(temp / 1000);
	tzone = &mvm->tz_device;

	अगर (!tzone) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	/* no updates*/
	अगर (tzone->temp_trips[trip] == temperature) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	/* alपढ़ोy existing temperature */
	क्रम (i = 0; i < IWL_MAX_DTS_TRIPS; i++) अणु
		अगर (tzone->temp_trips[i] == temperature) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	tzone->temp_trips[trip] = temperature;

	ret = iwl_mvm_send_temp_report_ths_cmd(mvm);
out:
	mutex_unlock(&mvm->mutex);
	वापस ret;
पूर्ण

अटल  काष्ठा thermal_zone_device_ops tzone_ops = अणु
	.get_temp = iwl_mvm_tzone_get_temp,
	.get_trip_temp = iwl_mvm_tzone_get_trip_temp,
	.get_trip_type = iwl_mvm_tzone_get_trip_type,
	.set_trip_temp = iwl_mvm_tzone_set_trip_temp,
पूर्ण;

/* make all trips writable */
#घोषणा IWL_WRITABLE_TRIPS_MSK (BIT(IWL_MAX_DTS_TRIPS) - 1)

अटल व्योम iwl_mvm_thermal_zone_रेजिस्टर(काष्ठा iwl_mvm *mvm)
अणु
	पूर्णांक i, ret;
	अक्षर name[16];
	अटल atomic_t counter = ATOMIC_INIT(0);

	अगर (!iwl_mvm_is_tt_in_fw(mvm)) अणु
		mvm->tz_device.tzone = शून्य;

		वापस;
	पूर्ण

	BUILD_BUG_ON(ARRAY_SIZE(name) >= THERMAL_NAME_LENGTH);

	प्र_लिखो(name, "iwlwifi_%u", atomic_inc_वापस(&counter) & 0xFF);
	mvm->tz_device.tzone = thermal_zone_device_रेजिस्टर(name,
							IWL_MAX_DTS_TRIPS,
							IWL_WRITABLE_TRIPS_MSK,
							mvm, &tzone_ops,
							शून्य, 0, 0);
	अगर (IS_ERR(mvm->tz_device.tzone)) अणु
		IWL_DEBUG_TEMP(mvm,
			       "Failed to register to thermal zone (err = %ld)\n",
			       PTR_ERR(mvm->tz_device.tzone));
		mvm->tz_device.tzone = शून्य;
		वापस;
	पूर्ण

	ret = thermal_zone_device_enable(mvm->tz_device.tzone);
	अगर (ret) अणु
		IWL_DEBUG_TEMP(mvm, "Failed to enable thermal zone\n");
		thermal_zone_device_unरेजिस्टर(mvm->tz_device.tzone);
		वापस;
	पूर्ण

	/* 0 is a valid temperature,
	 * so initialize the array with S16_MIN which invalid temperature
	 */
	क्रम (i = 0 ; i < IWL_MAX_DTS_TRIPS; i++)
		mvm->tz_device.temp_trips[i] = S16_MIN;
पूर्ण

अटल पूर्णांक iwl_mvm_tcool_get_max_state(काष्ठा thermal_cooling_device *cdev,
				       अचिन्हित दीर्घ *state)
अणु
	*state = ARRAY_SIZE(iwl_mvm_cdev_budमाला_लो) - 1;

	वापस 0;
पूर्ण

अटल पूर्णांक iwl_mvm_tcool_get_cur_state(काष्ठा thermal_cooling_device *cdev,
				       अचिन्हित दीर्घ *state)
अणु
	काष्ठा iwl_mvm *mvm = (काष्ठा iwl_mvm *)(cdev->devdata);

	*state = mvm->cooling_dev.cur_state;

	वापस 0;
पूर्ण

अटल पूर्णांक iwl_mvm_tcool_set_cur_state(काष्ठा thermal_cooling_device *cdev,
				       अचिन्हित दीर्घ new_state)
अणु
	काष्ठा iwl_mvm *mvm = (काष्ठा iwl_mvm *)(cdev->devdata);
	पूर्णांक ret;

	mutex_lock(&mvm->mutex);

	अगर (!iwl_mvm_firmware_running(mvm) ||
	    mvm->fwrt.cur_fw_img != IWL_UCODE_REGULAR) अणु
		ret = -EIO;
		जाओ unlock;
	पूर्ण

	अगर (new_state >= ARRAY_SIZE(iwl_mvm_cdev_budमाला_लो)) अणु
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण

	ret = iwl_mvm_ctdp_command(mvm, CTDP_CMD_OPERATION_START,
				   new_state);

unlock:
	mutex_unlock(&mvm->mutex);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा thermal_cooling_device_ops tcooling_ops = अणु
	.get_max_state = iwl_mvm_tcool_get_max_state,
	.get_cur_state = iwl_mvm_tcool_get_cur_state,
	.set_cur_state = iwl_mvm_tcool_set_cur_state,
पूर्ण;

अटल व्योम iwl_mvm_cooling_device_रेजिस्टर(काष्ठा iwl_mvm *mvm)
अणु
	अक्षर name[] = "iwlwifi";

	अगर (!iwl_mvm_is_ctdp_supported(mvm))
		वापस;

	BUILD_BUG_ON(ARRAY_SIZE(name) >= THERMAL_NAME_LENGTH);

	mvm->cooling_dev.cdev =
		thermal_cooling_device_रेजिस्टर(name,
						mvm,
						&tcooling_ops);

	अगर (IS_ERR(mvm->cooling_dev.cdev)) अणु
		IWL_DEBUG_TEMP(mvm,
			       "Failed to register to cooling device (err = %ld)\n",
			       PTR_ERR(mvm->cooling_dev.cdev));
		mvm->cooling_dev.cdev = शून्य;
		वापस;
	पूर्ण
पूर्ण

अटल व्योम iwl_mvm_thermal_zone_unरेजिस्टर(काष्ठा iwl_mvm *mvm)
अणु
	अगर (!iwl_mvm_is_tt_in_fw(mvm) || !mvm->tz_device.tzone)
		वापस;

	IWL_DEBUG_TEMP(mvm, "Thermal zone device unregister\n");
	अगर (mvm->tz_device.tzone) अणु
		thermal_zone_device_unरेजिस्टर(mvm->tz_device.tzone);
		mvm->tz_device.tzone = शून्य;
	पूर्ण
पूर्ण

अटल व्योम iwl_mvm_cooling_device_unरेजिस्टर(काष्ठा iwl_mvm *mvm)
अणु
	अगर (!iwl_mvm_is_ctdp_supported(mvm) || !mvm->cooling_dev.cdev)
		वापस;

	IWL_DEBUG_TEMP(mvm, "Cooling device unregister\n");
	अगर (mvm->cooling_dev.cdev) अणु
		thermal_cooling_device_unरेजिस्टर(mvm->cooling_dev.cdev);
		mvm->cooling_dev.cdev = शून्य;
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_THERMAL */

व्योम iwl_mvm_thermal_initialize(काष्ठा iwl_mvm *mvm, u32 min_backoff)
अणु
	काष्ठा iwl_mvm_tt_mgmt *tt = &mvm->thermal_throttle;

	IWL_DEBUG_TEMP(mvm, "Initialize Thermal Throttling\n");

	अगर (mvm->cfg->thermal_params)
		tt->params = *mvm->cfg->thermal_params;
	अन्यथा
		tt->params = iwl_mvm_शेष_tt_params;

	tt->throttle = false;
	tt->dynamic_smps = false;
	tt->min_backoff = min_backoff;
	INIT_DELAYED_WORK(&tt->ct_समाप्त_निकास, check_निकास_ctसमाप्त);

#अगर_घोषित CONFIG_THERMAL
	iwl_mvm_cooling_device_रेजिस्टर(mvm);
	iwl_mvm_thermal_zone_रेजिस्टर(mvm);
#पूर्ण_अगर
	mvm->init_status |= IWL_MVM_INIT_STATUS_THERMAL_INIT_COMPLETE;
पूर्ण

व्योम iwl_mvm_thermal_निकास(काष्ठा iwl_mvm *mvm)
अणु
	अगर (!(mvm->init_status & IWL_MVM_INIT_STATUS_THERMAL_INIT_COMPLETE))
		वापस;

	cancel_delayed_work_sync(&mvm->thermal_throttle.ct_समाप्त_निकास);
	IWL_DEBUG_TEMP(mvm, "Exit Thermal Throttling\n");

#अगर_घोषित CONFIG_THERMAL
	iwl_mvm_cooling_device_unरेजिस्टर(mvm);
	iwl_mvm_thermal_zone_unरेजिस्टर(mvm);
#पूर्ण_अगर
	mvm->init_status &= ~IWL_MVM_INIT_STATUS_THERMAL_INIT_COMPLETE;
पूर्ण
