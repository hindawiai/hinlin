<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
 *
 * Copyright(c) 2008 - 2014 Intel Corporation. All rights reserved.
 * Copyright(c) 2015 Intel Deutschland GmbH
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <linuxwअगरi@पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 *****************************************************************************/

#समावेश <linux/kernel.h>

#समावेश "iwl-io.h"
#समावेश "iwl-agn-hw.h"
#समावेश "iwl-trans.h"
#समावेश "iwl-fh.h"
#समावेश "iwl-op-mode.h"

#समावेश "dev.h"
#समावेश "agn.h"
#समावेश "calib.h"

/******************************************************************************
 *
 * uCode करोwnload functions
 *
 ******************************************************************************/

/*
 *  Calibration
 */
अटल पूर्णांक iwl_set_Xtal_calib(काष्ठा iwl_priv *priv)
अणु
	काष्ठा iwl_calib_xtal_freq_cmd cmd;
	__le16 *xtal_calib = priv->nvm_data->xtal_calib;

	iwl_set_calib_hdr(&cmd.hdr, IWL_PHY_CALIBRATE_CRYSTAL_FRQ_CMD);
	cmd.cap_pin1 = le16_to_cpu(xtal_calib[0]);
	cmd.cap_pin2 = le16_to_cpu(xtal_calib[1]);
	वापस iwl_calib_set(priv, (व्योम *)&cmd, माप(cmd));
पूर्ण

अटल पूर्णांक iwl_set_temperature_offset_calib(काष्ठा iwl_priv *priv)
अणु
	काष्ठा iwl_calib_temperature_offset_cmd cmd;

	स_रखो(&cmd, 0, माप(cmd));
	iwl_set_calib_hdr(&cmd.hdr, IWL_PHY_CALIBRATE_TEMP_OFFSET_CMD);
	cmd.radio_sensor_offset = priv->nvm_data->raw_temperature;
	अगर (!(cmd.radio_sensor_offset))
		cmd.radio_sensor_offset = DEFAULT_RADIO_SENSOR_OFFSET;

	IWL_DEBUG_CALIB(priv, "Radio sensor offset: %d\n",
			le16_to_cpu(cmd.radio_sensor_offset));
	वापस iwl_calib_set(priv, (व्योम *)&cmd, माप(cmd));
पूर्ण

अटल पूर्णांक iwl_set_temperature_offset_calib_v2(काष्ठा iwl_priv *priv)
अणु
	काष्ठा iwl_calib_temperature_offset_v2_cmd cmd;

	स_रखो(&cmd, 0, माप(cmd));
	iwl_set_calib_hdr(&cmd.hdr, IWL_PHY_CALIBRATE_TEMP_OFFSET_CMD);
	cmd.radio_sensor_offset_high = priv->nvm_data->kelvin_temperature;
	cmd.radio_sensor_offset_low = priv->nvm_data->raw_temperature;
	अगर (!cmd.radio_sensor_offset_low) अणु
		IWL_DEBUG_CALIB(priv, "no info in EEPROM, use default\n");
		cmd.radio_sensor_offset_low = DEFAULT_RADIO_SENSOR_OFFSET;
		cmd.radio_sensor_offset_high = DEFAULT_RADIO_SENSOR_OFFSET;
	पूर्ण
	cmd.burntVoltageRef = priv->nvm_data->calib_voltage;

	IWL_DEBUG_CALIB(priv, "Radio sensor offset high: %d\n",
			le16_to_cpu(cmd.radio_sensor_offset_high));
	IWL_DEBUG_CALIB(priv, "Radio sensor offset low: %d\n",
			le16_to_cpu(cmd.radio_sensor_offset_low));
	IWL_DEBUG_CALIB(priv, "Voltage Ref: %d\n",
			le16_to_cpu(cmd.burntVoltageRef));

	वापस iwl_calib_set(priv, (व्योम *)&cmd, माप(cmd));
पूर्ण

अटल पूर्णांक iwl_send_calib_cfg(काष्ठा iwl_priv *priv)
अणु
	काष्ठा iwl_calib_cfg_cmd calib_cfg_cmd;
	काष्ठा iwl_host_cmd cmd = अणु
		.id = CALIBRATION_CFG_CMD,
		.len = अणु माप(काष्ठा iwl_calib_cfg_cmd), पूर्ण,
		.data = अणु &calib_cfg_cmd, पूर्ण,
	पूर्ण;

	स_रखो(&calib_cfg_cmd, 0, माप(calib_cfg_cmd));
	calib_cfg_cmd.ucd_calib_cfg.once.is_enable = IWL_CALIB_INIT_CFG_ALL;
	calib_cfg_cmd.ucd_calib_cfg.once.start = IWL_CALIB_INIT_CFG_ALL;
	calib_cfg_cmd.ucd_calib_cfg.once.send_res = IWL_CALIB_INIT_CFG_ALL;
	calib_cfg_cmd.ucd_calib_cfg.flags =
		IWL_CALIB_CFG_FLAG_SEND_COMPLETE_NTFY_MSK;

	वापस iwl_dvm_send_cmd(priv, &cmd);
पूर्ण

पूर्णांक iwl_init_alive_start(काष्ठा iwl_priv *priv)
अणु
	पूर्णांक ret;

	अगर (priv->lib->bt_params &&
	    priv->lib->bt_params->advanced_bt_coexist) अणु
		/*
		 * Tell uCode we are पढ़ोy to perक्रमm calibration
		 * need to perक्रमm this beक्रमe any calibration
		 * no need to बंद the envlope since we are going
		 * to load the runसमय uCode later.
		 */
		ret = iwl_send_bt_env(priv, IWL_BT_COEX_ENV_OPEN,
			BT_COEX_PRIO_TBL_EVT_INIT_CALIB2);
		अगर (ret)
			वापस ret;

	पूर्ण

	ret = iwl_send_calib_cfg(priv);
	अगर (ret)
		वापस ret;

	/**
	 * temperature offset calibration is only needed क्रम runसमय ucode,
	 * so prepare the value now.
	 */
	अगर (priv->lib->need_temp_offset_calib) अणु
		अगर (priv->lib->temp_offset_v2)
			वापस iwl_set_temperature_offset_calib_v2(priv);
		अन्यथा
			वापस iwl_set_temperature_offset_calib(priv);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iwl_send_wimax_coex(काष्ठा iwl_priv *priv)
अणु
	काष्ठा iwl_wimax_coex_cmd coex_cmd;

	/* coexistence is disabled */
	स_रखो(&coex_cmd, 0, माप(coex_cmd));

	वापस iwl_dvm_send_cmd_pdu(priv,
				COEX_PRIORITY_TABLE_CMD, 0,
				माप(coex_cmd), &coex_cmd);
पूर्ण

अटल स्थिर u8 iwl_bt_prio_tbl[BT_COEX_PRIO_TBL_EVT_MAX] = अणु
	((BT_COEX_PRIO_TBL_PRIO_BYPASS << IWL_BT_COEX_PRIO_TBL_PRIO_POS) |
		(0 << IWL_BT_COEX_PRIO_TBL_SHARED_ANTENNA_POS)),
	((BT_COEX_PRIO_TBL_PRIO_BYPASS << IWL_BT_COEX_PRIO_TBL_PRIO_POS) |
		(1 << IWL_BT_COEX_PRIO_TBL_SHARED_ANTENNA_POS)),
	((BT_COEX_PRIO_TBL_PRIO_LOW << IWL_BT_COEX_PRIO_TBL_PRIO_POS) |
		(0 << IWL_BT_COEX_PRIO_TBL_SHARED_ANTENNA_POS)),
	((BT_COEX_PRIO_TBL_PRIO_LOW << IWL_BT_COEX_PRIO_TBL_PRIO_POS) |
		(1 << IWL_BT_COEX_PRIO_TBL_SHARED_ANTENNA_POS)),
	((BT_COEX_PRIO_TBL_PRIO_HIGH << IWL_BT_COEX_PRIO_TBL_PRIO_POS) |
		(0 << IWL_BT_COEX_PRIO_TBL_SHARED_ANTENNA_POS)),
	((BT_COEX_PRIO_TBL_PRIO_HIGH << IWL_BT_COEX_PRIO_TBL_PRIO_POS) |
		(1 << IWL_BT_COEX_PRIO_TBL_SHARED_ANTENNA_POS)),
	((BT_COEX_PRIO_TBL_PRIO_BYPASS << IWL_BT_COEX_PRIO_TBL_PRIO_POS) |
		(0 << IWL_BT_COEX_PRIO_TBL_SHARED_ANTENNA_POS)),
	((BT_COEX_PRIO_TBL_PRIO_COEX_OFF << IWL_BT_COEX_PRIO_TBL_PRIO_POS) |
		(0 << IWL_BT_COEX_PRIO_TBL_SHARED_ANTENNA_POS)),
	((BT_COEX_PRIO_TBL_PRIO_COEX_ON << IWL_BT_COEX_PRIO_TBL_PRIO_POS) |
		(0 << IWL_BT_COEX_PRIO_TBL_SHARED_ANTENNA_POS)),
	0, 0, 0, 0, 0, 0, 0
पूर्ण;

व्योम iwl_send_prio_tbl(काष्ठा iwl_priv *priv)
अणु
	काष्ठा iwl_bt_coex_prio_table_cmd prio_tbl_cmd;

	स_नकल(prio_tbl_cmd.prio_tbl, iwl_bt_prio_tbl,
		माप(iwl_bt_prio_tbl));
	अगर (iwl_dvm_send_cmd_pdu(priv,
				REPLY_BT_COEX_PRIO_TABLE, 0,
				माप(prio_tbl_cmd), &prio_tbl_cmd))
		IWL_ERR(priv, "failed to send BT prio tbl command\n");
पूर्ण

पूर्णांक iwl_send_bt_env(काष्ठा iwl_priv *priv, u8 action, u8 type)
अणु
	काष्ठा iwl_bt_coex_prot_env_cmd env_cmd;
	पूर्णांक ret;

	env_cmd.action = action;
	env_cmd.type = type;
	ret = iwl_dvm_send_cmd_pdu(priv,
			       REPLY_BT_COEX_PROT_ENV, 0,
			       माप(env_cmd), &env_cmd);
	अगर (ret)
		IWL_ERR(priv, "failed to send BT env command\n");
	वापस ret;
पूर्ण

अटल स्थिर u8 iwlagn_शेष_queue_to_tx_fअगरo[] = अणु
	IWL_TX_FIFO_VO,
	IWL_TX_FIFO_VI,
	IWL_TX_FIFO_BE,
	IWL_TX_FIFO_BK,
पूर्ण;

अटल स्थिर u8 iwlagn_ipan_queue_to_tx_fअगरo[] = अणु
	IWL_TX_FIFO_VO,
	IWL_TX_FIFO_VI,
	IWL_TX_FIFO_BE,
	IWL_TX_FIFO_BK,
	IWL_TX_FIFO_BK_IPAN,
	IWL_TX_FIFO_BE_IPAN,
	IWL_TX_FIFO_VI_IPAN,
	IWL_TX_FIFO_VO_IPAN,
	IWL_TX_FIFO_BE_IPAN,
	IWL_TX_FIFO_UNUSED,
	IWL_TX_FIFO_AUX,
पूर्ण;

अटल पूर्णांक iwl_alive_notअगरy(काष्ठा iwl_priv *priv)
अणु
	स्थिर u8 *queue_to_txf;
	u8 n_queues;
	पूर्णांक ret;
	पूर्णांक i;

	iwl_trans_fw_alive(priv->trans, 0);

	अगर (priv->fw->ucode_capa.flags & IWL_UCODE_TLV_FLAGS_PAN &&
	    priv->nvm_data->sku_cap_ipan_enable) अणु
		n_queues = ARRAY_SIZE(iwlagn_ipan_queue_to_tx_fअगरo);
		queue_to_txf = iwlagn_ipan_queue_to_tx_fअगरo;
	पूर्ण अन्यथा अणु
		n_queues = ARRAY_SIZE(iwlagn_शेष_queue_to_tx_fअगरo);
		queue_to_txf = iwlagn_शेष_queue_to_tx_fअगरo;
	पूर्ण

	क्रम (i = 0; i < n_queues; i++)
		अगर (queue_to_txf[i] != IWL_TX_FIFO_UNUSED)
			iwl_trans_ac_txq_enable(priv->trans, i,
						queue_to_txf[i], 0);

	priv->passive_no_rx = false;
	priv->transport_queue_stop = 0;

	ret = iwl_send_wimax_coex(priv);
	अगर (ret)
		वापस ret;

	अगर (!priv->lib->no_xtal_calib) अणु
		ret = iwl_set_Xtal_calib(priv);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस iwl_send_calib_results(priv);
पूर्ण

काष्ठा iwl_alive_data अणु
	bool valid;
	u8 subtype;
पूर्ण;

अटल bool iwl_alive_fn(काष्ठा iwl_notअगर_रुको_data *notअगर_रुको,
			 काष्ठा iwl_rx_packet *pkt, व्योम *data)
अणु
	काष्ठा iwl_priv *priv =
		container_of(notअगर_रुको, काष्ठा iwl_priv, notअगर_रुको);
	काष्ठा iwl_alive_data *alive_data = data;
	काष्ठा iwl_alive_resp *palive;

	palive = (व्योम *)pkt->data;

	IWL_DEBUG_FW(priv, "Alive ucode status 0x%08X revision "
		       "0x%01X 0x%01X\n",
		       palive->is_valid, palive->ver_type,
		       palive->ver_subtype);

	priv->device_poपूर्णांकers.error_event_table =
		le32_to_cpu(palive->error_event_table_ptr);
	priv->device_poपूर्णांकers.log_event_table =
		le32_to_cpu(palive->log_event_table_ptr);

	alive_data->subtype = palive->ver_subtype;
	alive_data->valid = palive->is_valid == UCODE_VALID_OK;

	वापस true;
पूर्ण

#घोषणा UCODE_ALIVE_TIMEOUT	HZ
#घोषणा UCODE_CALIB_TIMEOUT	(2*HZ)

पूर्णांक iwl_load_ucode_रुको_alive(काष्ठा iwl_priv *priv,
				 क्रमागत iwl_ucode_type ucode_type)
अणु
	काष्ठा iwl_notअगरication_रुको alive_रुको;
	काष्ठा iwl_alive_data alive_data;
	स्थिर काष्ठा fw_img *fw;
	पूर्णांक ret;
	क्रमागत iwl_ucode_type old_type;
	अटल स्थिर u16 alive_cmd[] = अणु REPLY_ALIVE पूर्ण;

	fw = iwl_get_ucode_image(priv->fw, ucode_type);
	अगर (WARN_ON(!fw))
		वापस -EINVAL;

	old_type = priv->cur_ucode;
	priv->cur_ucode = ucode_type;
	priv->ucode_loaded = false;

	iwl_init_notअगरication_रुको(&priv->notअगर_रुको, &alive_रुको,
				   alive_cmd, ARRAY_SIZE(alive_cmd),
				   iwl_alive_fn, &alive_data);

	ret = iwl_trans_start_fw(priv->trans, fw, false);
	अगर (ret) अणु
		priv->cur_ucode = old_type;
		iwl_हटाओ_notअगरication(&priv->notअगर_रुको, &alive_रुको);
		वापस ret;
	पूर्ण

	/*
	 * Some things may run in the background now, but we
	 * just रुको क्रम the ALIVE notअगरication here.
	 */
	ret = iwl_रुको_notअगरication(&priv->notअगर_रुको, &alive_रुको,
					UCODE_ALIVE_TIMEOUT);
	अगर (ret) अणु
		priv->cur_ucode = old_type;
		वापस ret;
	पूर्ण

	अगर (!alive_data.valid) अणु
		IWL_ERR(priv, "Loaded ucode is not valid!\n");
		priv->cur_ucode = old_type;
		वापस -EIO;
	पूर्ण

	priv->ucode_loaded = true;

	अगर (ucode_type != IWL_UCODE_WOWLAN) अणु
		/* delay a bit to give rfसमाप्त समय to run */
		msleep(5);
	पूर्ण

	ret = iwl_alive_notअगरy(priv);
	अगर (ret) अणु
		IWL_WARN(priv,
			"Could not complete ALIVE transition: %d\n", ret);
		priv->cur_ucode = old_type;
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool iwlagn_रुको_calib(काष्ठा iwl_notअगर_रुको_data *notअगर_रुको,
			      काष्ठा iwl_rx_packet *pkt, व्योम *data)
अणु
	काष्ठा iwl_priv *priv = data;
	काष्ठा iwl_calib_hdr *hdr;

	अगर (pkt->hdr.cmd != CALIBRATION_RES_NOTIFICATION) अणु
		WARN_ON(pkt->hdr.cmd != CALIBRATION_COMPLETE_NOTIFICATION);
		वापस true;
	पूर्ण

	hdr = (काष्ठा iwl_calib_hdr *)pkt->data;

	अगर (iwl_calib_set(priv, hdr, iwl_rx_packet_payload_len(pkt)))
		IWL_ERR(priv, "Failed to record calibration data %d\n",
			hdr->op_code);

	वापस false;
पूर्ण

पूर्णांक iwl_run_init_ucode(काष्ठा iwl_priv *priv)
अणु
	काष्ठा iwl_notअगरication_रुको calib_रुको;
	अटल स्थिर u16 calib_complete[] = अणु
		CALIBRATION_RES_NOTIFICATION,
		CALIBRATION_COMPLETE_NOTIFICATION
	पूर्ण;
	पूर्णांक ret;

	lockdep_निश्चित_held(&priv->mutex);

	/* No init ucode required? Curious, but maybe ok */
	अगर (!priv->fw->img[IWL_UCODE_INIT].num_sec)
		वापस 0;

	iwl_init_notअगरication_रुको(&priv->notअगर_रुको, &calib_रुको,
				   calib_complete, ARRAY_SIZE(calib_complete),
				   iwlagn_रुको_calib, priv);

	/* Will also start the device */
	ret = iwl_load_ucode_रुको_alive(priv, IWL_UCODE_INIT);
	अगर (ret)
		जाओ error;

	ret = iwl_init_alive_start(priv);
	अगर (ret)
		जाओ error;

	/*
	 * Some things may run in the background now, but we
	 * just रुको क्रम the calibration complete notअगरication.
	 */
	ret = iwl_रुको_notअगरication(&priv->notअगर_रुको, &calib_रुको,
					UCODE_CALIB_TIMEOUT);

	जाओ out;

 error:
	iwl_हटाओ_notअगरication(&priv->notअगर_रुको, &calib_रुको);
 out:
	/* Whatever happened, stop the device */
	iwl_trans_stop_device(priv->trans);
	priv->ucode_loaded = false;

	वापस ret;
पूर्ण
