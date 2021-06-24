<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright तऊ 2019 Intel Corporation
 *
 * mei_hdcp.c: HDCP client driver क्रम mei bus
 *
 * Author:
 * Ramalingam C <ramalingam.c@पूर्णांकel.com>
 */

/**
 * DOC: MEI_HDCP Client Driver
 *
 * The mei_hdcp driver acts as a translation layer between HDCP 2.2
 * protocol  implementer (I915) and ME FW by translating HDCP2.2
 * negotiation messages to ME FW command payloads and vice versa.
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/uuid.h>
#समावेश <linux/mei_cl_bus.h>
#समावेश <linux/component.h>
#समावेश <drm/drm_connector.h>
#समावेश <drm/i915_component.h>
#समावेश <drm/i915_mei_hdcp_पूर्णांकerface.h>

#समावेश "mei_hdcp.h"

/**
 * mei_hdcp_initiate_session() - Initiate a Wired HDCP2.2 Tx Session in ME FW
 * @dev: device corresponding to the mei_cl_device
 * @data: Intel HW specअगरic hdcp data
 * @ake_data: AKE_Init msg output.
 *
 * Return:  0 on Success, <0 on Failure.
 */
अटल पूर्णांक
mei_hdcp_initiate_session(काष्ठा device *dev, काष्ठा hdcp_port_data *data,
			  काष्ठा hdcp2_ake_init *ake_data)
अणु
	काष्ठा wired_cmd_initiate_hdcp2_session_in session_init_in = अणु अणु 0 पूर्ण पूर्ण;
	काष्ठा wired_cmd_initiate_hdcp2_session_out
						session_init_out = अणु अणु 0 पूर्ण पूर्ण;
	काष्ठा mei_cl_device *cldev;
	sमाप_प्रकार byte;

	अगर (!dev || !data || !ake_data)
		वापस -EINVAL;

	cldev = to_mei_cl_device(dev);

	session_init_in.header.api_version = HDCP_API_VERSION;
	session_init_in.header.command_id = WIRED_INITIATE_HDCP2_SESSION;
	session_init_in.header.status = ME_HDCP_STATUS_SUCCESS;
	session_init_in.header.buffer_len =
				WIRED_CMD_BUF_LEN_INITIATE_HDCP2_SESSION_IN;

	session_init_in.port.पूर्णांकegrated_port_type = data->port_type;
	session_init_in.port.physical_port = (u8)data->fw_ddi;
	session_init_in.port.attached_transcoder = (u8)data->fw_tc;
	session_init_in.protocol = data->protocol;

	byte = mei_cldev_send(cldev, (u8 *)&session_init_in,
			      माप(session_init_in));
	अगर (byte < 0) अणु
		dev_dbg(dev, "mei_cldev_send failed. %zd\n", byte);
		वापस byte;
	पूर्ण

	byte = mei_cldev_recv(cldev, (u8 *)&session_init_out,
			      माप(session_init_out));
	अगर (byte < 0) अणु
		dev_dbg(dev, "mei_cldev_recv failed. %zd\n", byte);
		वापस byte;
	पूर्ण

	अगर (session_init_out.header.status != ME_HDCP_STATUS_SUCCESS) अणु
		dev_dbg(dev, "ME cmd 0x%08X Failed. Status: 0x%X\n",
			WIRED_INITIATE_HDCP2_SESSION,
			session_init_out.header.status);
		वापस -EIO;
	पूर्ण

	ake_data->msg_id = HDCP_2_2_AKE_INIT;
	ake_data->tx_caps = session_init_out.tx_caps;
	स_नकल(ake_data->r_tx, session_init_out.r_tx, HDCP_2_2_RTX_LEN);

	वापस 0;
पूर्ण

/**
 * mei_hdcp_verअगरy_receiver_cert_prepare_km() - Verअगरy the Receiver Certअगरicate
 * AKE_Send_Cert and prepare AKE_Stored_Km/AKE_No_Stored_Km
 * @dev: device corresponding to the mei_cl_device
 * @data: Intel HW specअगरic hdcp data
 * @rx_cert: AKE_Send_Cert क्रम verअगरication
 * @km_stored: Pairing status flag output
 * @ek_pub_km: AKE_Stored_Km/AKE_No_Stored_Km output msg
 * @msg_sz : size of AKE_XXXXX_Km output msg
 *
 * Return: 0 on Success, <0 on Failure
 */
अटल पूर्णांक
mei_hdcp_verअगरy_receiver_cert_prepare_km(काष्ठा device *dev,
					 काष्ठा hdcp_port_data *data,
					 काष्ठा hdcp2_ake_send_cert *rx_cert,
					 bool *km_stored,
					 काष्ठा hdcp2_ake_no_stored_km
								*ek_pub_km,
					 माप_प्रकार *msg_sz)
अणु
	काष्ठा wired_cmd_verअगरy_receiver_cert_in verअगरy_rxcert_in = अणु अणु 0 पूर्ण पूर्ण;
	काष्ठा wired_cmd_verअगरy_receiver_cert_out verअगरy_rxcert_out = अणु अणु 0 पूर्ण पूर्ण;
	काष्ठा mei_cl_device *cldev;
	sमाप_प्रकार byte;

	अगर (!dev || !data || !rx_cert || !km_stored || !ek_pub_km || !msg_sz)
		वापस -EINVAL;

	cldev = to_mei_cl_device(dev);

	verअगरy_rxcert_in.header.api_version = HDCP_API_VERSION;
	verअगरy_rxcert_in.header.command_id = WIRED_VERIFY_RECEIVER_CERT;
	verअगरy_rxcert_in.header.status = ME_HDCP_STATUS_SUCCESS;
	verअगरy_rxcert_in.header.buffer_len =
				WIRED_CMD_BUF_LEN_VERIFY_RECEIVER_CERT_IN;

	verअगरy_rxcert_in.port.पूर्णांकegrated_port_type = data->port_type;
	verअगरy_rxcert_in.port.physical_port = (u8)data->fw_ddi;
	verअगरy_rxcert_in.port.attached_transcoder = (u8)data->fw_tc;

	verअगरy_rxcert_in.cert_rx = rx_cert->cert_rx;
	स_नकल(verअगरy_rxcert_in.r_rx, &rx_cert->r_rx, HDCP_2_2_RRX_LEN);
	स_नकल(verअगरy_rxcert_in.rx_caps, rx_cert->rx_caps, HDCP_2_2_RXCAPS_LEN);

	byte = mei_cldev_send(cldev, (u8 *)&verअगरy_rxcert_in,
			      माप(verअगरy_rxcert_in));
	अगर (byte < 0) अणु
		dev_dbg(dev, "mei_cldev_send failed: %zd\n", byte);
		वापस byte;
	पूर्ण

	byte = mei_cldev_recv(cldev, (u8 *)&verअगरy_rxcert_out,
			      माप(verअगरy_rxcert_out));
	अगर (byte < 0) अणु
		dev_dbg(dev, "mei_cldev_recv failed: %zd\n", byte);
		वापस byte;
	पूर्ण

	अगर (verअगरy_rxcert_out.header.status != ME_HDCP_STATUS_SUCCESS) अणु
		dev_dbg(dev, "ME cmd 0x%08X Failed. Status: 0x%X\n",
			WIRED_VERIFY_RECEIVER_CERT,
			verअगरy_rxcert_out.header.status);
		वापस -EIO;
	पूर्ण

	*km_stored = !!verअगरy_rxcert_out.km_stored;
	अगर (verअगरy_rxcert_out.km_stored) अणु
		ek_pub_km->msg_id = HDCP_2_2_AKE_STORED_KM;
		*msg_sz = माप(काष्ठा hdcp2_ake_stored_km);
	पूर्ण अन्यथा अणु
		ek_pub_km->msg_id = HDCP_2_2_AKE_NO_STORED_KM;
		*msg_sz = माप(काष्ठा hdcp2_ake_no_stored_km);
	पूर्ण

	स_नकल(ek_pub_km->e_kpub_km, &verअगरy_rxcert_out.ekm_buff,
	       माप(verअगरy_rxcert_out.ekm_buff));

	वापस 0;
पूर्ण

/**
 * mei_hdcp_verअगरy_hprime() - Verअगरy AKE_Send_H_prime at ME FW.
 * @dev: device corresponding to the mei_cl_device
 * @data: Intel HW specअगरic hdcp data
 * @rx_hprime: AKE_Send_H_prime msg क्रम ME FW verअगरication
 *
 * Return: 0 on Success, <0 on Failure
 */
अटल पूर्णांक
mei_hdcp_verअगरy_hprime(काष्ठा device *dev, काष्ठा hdcp_port_data *data,
		       काष्ठा hdcp2_ake_send_hprime *rx_hprime)
अणु
	काष्ठा wired_cmd_ake_send_hprime_in send_hprime_in = अणु अणु 0 पूर्ण पूर्ण;
	काष्ठा wired_cmd_ake_send_hprime_out send_hprime_out = अणु अणु 0 पूर्ण पूर्ण;
	काष्ठा mei_cl_device *cldev;
	sमाप_प्रकार byte;

	अगर (!dev || !data || !rx_hprime)
		वापस -EINVAL;

	cldev = to_mei_cl_device(dev);

	send_hprime_in.header.api_version = HDCP_API_VERSION;
	send_hprime_in.header.command_id = WIRED_AKE_SEND_HPRIME;
	send_hprime_in.header.status = ME_HDCP_STATUS_SUCCESS;
	send_hprime_in.header.buffer_len = WIRED_CMD_BUF_LEN_AKE_SEND_HPRIME_IN;

	send_hprime_in.port.पूर्णांकegrated_port_type = data->port_type;
	send_hprime_in.port.physical_port = (u8)data->fw_ddi;
	send_hprime_in.port.attached_transcoder = (u8)data->fw_tc;

	स_नकल(send_hprime_in.h_prime, rx_hprime->h_prime,
	       HDCP_2_2_H_PRIME_LEN);

	byte = mei_cldev_send(cldev, (u8 *)&send_hprime_in,
			      माप(send_hprime_in));
	अगर (byte < 0) अणु
		dev_dbg(dev, "mei_cldev_send failed. %zd\n", byte);
		वापस byte;
	पूर्ण

	byte = mei_cldev_recv(cldev, (u8 *)&send_hprime_out,
			      माप(send_hprime_out));
	अगर (byte < 0) अणु
		dev_dbg(dev, "mei_cldev_recv failed. %zd\n", byte);
		वापस byte;
	पूर्ण

	अगर (send_hprime_out.header.status != ME_HDCP_STATUS_SUCCESS) अणु
		dev_dbg(dev, "ME cmd 0x%08X Failed. Status: 0x%X\n",
			WIRED_AKE_SEND_HPRIME, send_hprime_out.header.status);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * mei_hdcp_store_pairing_info() - Store pairing info received at ME FW
 * @dev: device corresponding to the mei_cl_device
 * @data: Intel HW specअगरic hdcp data
 * @pairing_info: AKE_Send_Pairing_Info msg input to ME FW
 *
 * Return: 0 on Success, <0 on Failure
 */
अटल पूर्णांक
mei_hdcp_store_pairing_info(काष्ठा device *dev, काष्ठा hdcp_port_data *data,
			    काष्ठा hdcp2_ake_send_pairing_info *pairing_info)
अणु
	काष्ठा wired_cmd_ake_send_pairing_info_in pairing_info_in = अणु अणु 0 पूर्ण पूर्ण;
	काष्ठा wired_cmd_ake_send_pairing_info_out pairing_info_out = अणु अणु 0 पूर्ण पूर्ण;
	काष्ठा mei_cl_device *cldev;
	sमाप_प्रकार byte;

	अगर (!dev || !data || !pairing_info)
		वापस -EINVAL;

	cldev = to_mei_cl_device(dev);

	pairing_info_in.header.api_version = HDCP_API_VERSION;
	pairing_info_in.header.command_id = WIRED_AKE_SEND_PAIRING_INFO;
	pairing_info_in.header.status = ME_HDCP_STATUS_SUCCESS;
	pairing_info_in.header.buffer_len =
					WIRED_CMD_BUF_LEN_SEND_PAIRING_INFO_IN;

	pairing_info_in.port.पूर्णांकegrated_port_type = data->port_type;
	pairing_info_in.port.physical_port = (u8)data->fw_ddi;
	pairing_info_in.port.attached_transcoder = (u8)data->fw_tc;

	स_नकल(pairing_info_in.e_kh_km, pairing_info->e_kh_km,
	       HDCP_2_2_E_KH_KM_LEN);

	byte = mei_cldev_send(cldev, (u8 *)&pairing_info_in,
			      माप(pairing_info_in));
	अगर (byte < 0) अणु
		dev_dbg(dev, "mei_cldev_send failed. %zd\n", byte);
		वापस byte;
	पूर्ण

	byte = mei_cldev_recv(cldev, (u8 *)&pairing_info_out,
			      माप(pairing_info_out));
	अगर (byte < 0) अणु
		dev_dbg(dev, "mei_cldev_recv failed. %zd\n", byte);
		वापस byte;
	पूर्ण

	अगर (pairing_info_out.header.status != ME_HDCP_STATUS_SUCCESS) अणु
		dev_dbg(dev, "ME cmd 0x%08X failed. Status: 0x%X\n",
			WIRED_AKE_SEND_PAIRING_INFO,
			pairing_info_out.header.status);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * mei_hdcp_initiate_locality_check() - Prepare LC_Init
 * @dev: device corresponding to the mei_cl_device
 * @data: Intel HW specअगरic hdcp data
 * @lc_init_data: LC_Init msg output
 *
 * Return: 0 on Success, <0 on Failure
 */
अटल पूर्णांक
mei_hdcp_initiate_locality_check(काष्ठा device *dev,
				 काष्ठा hdcp_port_data *data,
				 काष्ठा hdcp2_lc_init *lc_init_data)
अणु
	काष्ठा wired_cmd_init_locality_check_in lc_init_in = अणु अणु 0 पूर्ण पूर्ण;
	काष्ठा wired_cmd_init_locality_check_out lc_init_out = अणु अणु 0 पूर्ण पूर्ण;
	काष्ठा mei_cl_device *cldev;
	sमाप_प्रकार byte;

	अगर (!dev || !data || !lc_init_data)
		वापस -EINVAL;

	cldev = to_mei_cl_device(dev);

	lc_init_in.header.api_version = HDCP_API_VERSION;
	lc_init_in.header.command_id = WIRED_INIT_LOCALITY_CHECK;
	lc_init_in.header.status = ME_HDCP_STATUS_SUCCESS;
	lc_init_in.header.buffer_len = WIRED_CMD_BUF_LEN_INIT_LOCALITY_CHECK_IN;

	lc_init_in.port.पूर्णांकegrated_port_type = data->port_type;
	lc_init_in.port.physical_port = (u8)data->fw_ddi;
	lc_init_in.port.attached_transcoder = (u8)data->fw_tc;

	byte = mei_cldev_send(cldev, (u8 *)&lc_init_in, माप(lc_init_in));
	अगर (byte < 0) अणु
		dev_dbg(dev, "mei_cldev_send failed. %zd\n", byte);
		वापस byte;
	पूर्ण

	byte = mei_cldev_recv(cldev, (u8 *)&lc_init_out, माप(lc_init_out));
	अगर (byte < 0) अणु
		dev_dbg(dev, "mei_cldev_recv failed. %zd\n", byte);
		वापस byte;
	पूर्ण

	अगर (lc_init_out.header.status != ME_HDCP_STATUS_SUCCESS) अणु
		dev_dbg(dev, "ME cmd 0x%08X Failed. status: 0x%X\n",
			WIRED_INIT_LOCALITY_CHECK, lc_init_out.header.status);
		वापस -EIO;
	पूर्ण

	lc_init_data->msg_id = HDCP_2_2_LC_INIT;
	स_नकल(lc_init_data->r_n, lc_init_out.r_n, HDCP_2_2_RN_LEN);

	वापस 0;
पूर्ण

/**
 * mei_hdcp_verअगरy_lprime() - Verअगरy lprime.
 * @dev: device corresponding to the mei_cl_device
 * @data: Intel HW specअगरic hdcp data
 * @rx_lprime: LC_Send_L_prime msg क्रम ME FW verअगरication
 *
 * Return: 0 on Success, <0 on Failure
 */
अटल पूर्णांक
mei_hdcp_verअगरy_lprime(काष्ठा device *dev, काष्ठा hdcp_port_data *data,
		       काष्ठा hdcp2_lc_send_lprime *rx_lprime)
अणु
	काष्ठा wired_cmd_validate_locality_in verअगरy_lprime_in = अणु अणु 0 पूर्ण पूर्ण;
	काष्ठा wired_cmd_validate_locality_out verअगरy_lprime_out = अणु अणु 0 पूर्ण पूर्ण;
	काष्ठा mei_cl_device *cldev;
	sमाप_प्रकार byte;

	अगर (!dev || !data || !rx_lprime)
		वापस -EINVAL;

	cldev = to_mei_cl_device(dev);

	verअगरy_lprime_in.header.api_version = HDCP_API_VERSION;
	verअगरy_lprime_in.header.command_id = WIRED_VALIDATE_LOCALITY;
	verअगरy_lprime_in.header.status = ME_HDCP_STATUS_SUCCESS;
	verअगरy_lprime_in.header.buffer_len =
					WIRED_CMD_BUF_LEN_VALIDATE_LOCALITY_IN;

	verअगरy_lprime_in.port.पूर्णांकegrated_port_type = data->port_type;
	verअगरy_lprime_in.port.physical_port = (u8)data->fw_ddi;
	verअगरy_lprime_in.port.attached_transcoder = (u8)data->fw_tc;

	स_नकल(verअगरy_lprime_in.l_prime, rx_lprime->l_prime,
	       HDCP_2_2_L_PRIME_LEN);

	byte = mei_cldev_send(cldev, (u8 *)&verअगरy_lprime_in,
			      माप(verअगरy_lprime_in));
	अगर (byte < 0) अणु
		dev_dbg(dev, "mei_cldev_send failed. %zd\n", byte);
		वापस byte;
	पूर्ण

	byte = mei_cldev_recv(cldev, (u8 *)&verअगरy_lprime_out,
			      माप(verअगरy_lprime_out));
	अगर (byte < 0) अणु
		dev_dbg(dev, "mei_cldev_recv failed. %zd\n", byte);
		वापस byte;
	पूर्ण

	अगर (verअगरy_lprime_out.header.status != ME_HDCP_STATUS_SUCCESS) अणु
		dev_dbg(dev, "ME cmd 0x%08X failed. status: 0x%X\n",
			WIRED_VALIDATE_LOCALITY,
			verअगरy_lprime_out.header.status);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * mei_hdcp_get_session_key() - Prepare SKE_Send_Eks.
 * @dev: device corresponding to the mei_cl_device
 * @data: Intel HW specअगरic hdcp data
 * @ske_data: SKE_Send_Eks msg output from ME FW.
 *
 * Return: 0 on Success, <0 on Failure
 */
अटल पूर्णांक mei_hdcp_get_session_key(काष्ठा device *dev,
				    काष्ठा hdcp_port_data *data,
				    काष्ठा hdcp2_ske_send_eks *ske_data)
अणु
	काष्ठा wired_cmd_get_session_key_in get_skey_in = अणु अणु 0 पूर्ण पूर्ण;
	काष्ठा wired_cmd_get_session_key_out get_skey_out = अणु अणु 0 पूर्ण पूर्ण;
	काष्ठा mei_cl_device *cldev;
	sमाप_प्रकार byte;

	अगर (!dev || !data || !ske_data)
		वापस -EINVAL;

	cldev = to_mei_cl_device(dev);

	get_skey_in.header.api_version = HDCP_API_VERSION;
	get_skey_in.header.command_id = WIRED_GET_SESSION_KEY;
	get_skey_in.header.status = ME_HDCP_STATUS_SUCCESS;
	get_skey_in.header.buffer_len = WIRED_CMD_BUF_LEN_GET_SESSION_KEY_IN;

	get_skey_in.port.पूर्णांकegrated_port_type = data->port_type;
	get_skey_in.port.physical_port = (u8)data->fw_ddi;
	get_skey_in.port.attached_transcoder = (u8)data->fw_tc;

	byte = mei_cldev_send(cldev, (u8 *)&get_skey_in, माप(get_skey_in));
	अगर (byte < 0) अणु
		dev_dbg(dev, "mei_cldev_send failed. %zd\n", byte);
		वापस byte;
	पूर्ण

	byte = mei_cldev_recv(cldev, (u8 *)&get_skey_out, माप(get_skey_out));

	अगर (byte < 0) अणु
		dev_dbg(dev, "mei_cldev_recv failed. %zd\n", byte);
		वापस byte;
	पूर्ण

	अगर (get_skey_out.header.status != ME_HDCP_STATUS_SUCCESS) अणु
		dev_dbg(dev, "ME cmd 0x%08X failed. status: 0x%X\n",
			WIRED_GET_SESSION_KEY, get_skey_out.header.status);
		वापस -EIO;
	पूर्ण

	ske_data->msg_id = HDCP_2_2_SKE_SEND_EKS;
	स_नकल(ske_data->e_dkey_ks, get_skey_out.e_dkey_ks,
	       HDCP_2_2_E_DKEY_KS_LEN);
	स_नकल(ske_data->riv, get_skey_out.r_iv, HDCP_2_2_RIV_LEN);

	वापस 0;
पूर्ण

/**
 * mei_hdcp_repeater_check_flow_prepare_ack() - Validate the Downstream topology
 * and prepare rep_ack.
 * @dev: device corresponding to the mei_cl_device
 * @data: Intel HW specअगरic hdcp data
 * @rep_topology: Receiver ID List to be validated
 * @rep_send_ack : repeater ack from ME FW.
 *
 * Return: 0 on Success, <0 on Failure
 */
अटल पूर्णांक
mei_hdcp_repeater_check_flow_prepare_ack(काष्ठा device *dev,
					 काष्ठा hdcp_port_data *data,
					 काष्ठा hdcp2_rep_send_receiverid_list
							*rep_topology,
					 काष्ठा hdcp2_rep_send_ack
							*rep_send_ack)
अणु
	काष्ठा wired_cmd_verअगरy_repeater_in verअगरy_repeater_in = अणु अणु 0 पूर्ण पूर्ण;
	काष्ठा wired_cmd_verअगरy_repeater_out verअगरy_repeater_out = अणु अणु 0 पूर्ण पूर्ण;
	काष्ठा mei_cl_device *cldev;
	sमाप_प्रकार byte;

	अगर (!dev || !rep_topology || !rep_send_ack || !data)
		वापस -EINVAL;

	cldev = to_mei_cl_device(dev);

	verअगरy_repeater_in.header.api_version = HDCP_API_VERSION;
	verअगरy_repeater_in.header.command_id = WIRED_VERIFY_REPEATER;
	verअगरy_repeater_in.header.status = ME_HDCP_STATUS_SUCCESS;
	verअगरy_repeater_in.header.buffer_len =
					WIRED_CMD_BUF_LEN_VERIFY_REPEATER_IN;

	verअगरy_repeater_in.port.पूर्णांकegrated_port_type = data->port_type;
	verअगरy_repeater_in.port.physical_port = (u8)data->fw_ddi;
	verअगरy_repeater_in.port.attached_transcoder = (u8)data->fw_tc;

	स_नकल(verअगरy_repeater_in.rx_info, rep_topology->rx_info,
	       HDCP_2_2_RXINFO_LEN);
	स_नकल(verअगरy_repeater_in.seq_num_v, rep_topology->seq_num_v,
	       HDCP_2_2_SEQ_NUM_LEN);
	स_नकल(verअगरy_repeater_in.v_prime, rep_topology->v_prime,
	       HDCP_2_2_V_PRIME_HALF_LEN);
	स_नकल(verअगरy_repeater_in.receiver_ids, rep_topology->receiver_ids,
	       HDCP_2_2_RECEIVER_IDS_MAX_LEN);

	byte = mei_cldev_send(cldev, (u8 *)&verअगरy_repeater_in,
			      माप(verअगरy_repeater_in));
	अगर (byte < 0) अणु
		dev_dbg(dev, "mei_cldev_send failed. %zd\n", byte);
		वापस byte;
	पूर्ण

	byte = mei_cldev_recv(cldev, (u8 *)&verअगरy_repeater_out,
			      माप(verअगरy_repeater_out));
	अगर (byte < 0) अणु
		dev_dbg(dev, "mei_cldev_recv failed. %zd\n", byte);
		वापस byte;
	पूर्ण

	अगर (verअगरy_repeater_out.header.status != ME_HDCP_STATUS_SUCCESS) अणु
		dev_dbg(dev, "ME cmd 0x%08X failed. status: 0x%X\n",
			WIRED_VERIFY_REPEATER,
			verअगरy_repeater_out.header.status);
		वापस -EIO;
	पूर्ण

	स_नकल(rep_send_ack->v, verअगरy_repeater_out.v,
	       HDCP_2_2_V_PRIME_HALF_LEN);
	rep_send_ack->msg_id = HDCP_2_2_REP_SEND_ACK;

	वापस 0;
पूर्ण

/**
 * mei_hdcp_verअगरy_mprime() - Verअगरy mprime.
 * @dev: device corresponding to the mei_cl_device
 * @data: Intel HW specअगरic hdcp data
 * @stream_पढ़ोy: RepeaterAuth_Stream_Ready msg क्रम ME FW verअगरication.
 *
 * Return: 0 on Success, <0 on Failure
 */
अटल पूर्णांक mei_hdcp_verअगरy_mprime(काष्ठा device *dev,
				  काष्ठा hdcp_port_data *data,
				  काष्ठा hdcp2_rep_stream_पढ़ोy *stream_पढ़ोy)
अणु
	काष्ठा wired_cmd_repeater_auth_stream_req_in *verअगरy_mprime_in;
	काष्ठा wired_cmd_repeater_auth_stream_req_out
					verअगरy_mprime_out = अणु अणु 0 पूर्ण पूर्ण;
	काष्ठा mei_cl_device *cldev;
	sमाप_प्रकार byte;
	माप_प्रकार cmd_size;

	अगर (!dev || !stream_पढ़ोy || !data)
		वापस -EINVAL;

	cldev = to_mei_cl_device(dev);

	cmd_size = काष्ठा_size(verअगरy_mprime_in, streams, data->k);
	अगर (cmd_size == SIZE_MAX)
		वापस -EINVAL;

	verअगरy_mprime_in = kzalloc(cmd_size, GFP_KERNEL);
	अगर (!verअगरy_mprime_in)
		वापस -ENOMEM;

	verअगरy_mprime_in->header.api_version = HDCP_API_VERSION;
	verअगरy_mprime_in->header.command_id = WIRED_REPEATER_AUTH_STREAM_REQ;
	verअगरy_mprime_in->header.status = ME_HDCP_STATUS_SUCCESS;
	verअगरy_mprime_in->header.buffer_len = cmd_size  - माप(verअगरy_mprime_in->header);

	verअगरy_mprime_in->port.पूर्णांकegrated_port_type = data->port_type;
	verअगरy_mprime_in->port.physical_port = (u8)data->fw_ddi;
	verअगरy_mprime_in->port.attached_transcoder = (u8)data->fw_tc;

	स_नकल(verअगरy_mprime_in->m_prime, stream_पढ़ोy->m_prime, HDCP_2_2_MPRIME_LEN);
	drm_hdcp_cpu_to_be24(verअगरy_mprime_in->seq_num_m, data->seq_num_m);

	स_नकल(verअगरy_mprime_in->streams, data->streams,
	       array_size(data->k, माप(*data->streams)));

	verअगरy_mprime_in->k = cpu_to_be16(data->k);

	byte = mei_cldev_send(cldev, (u8 *)verअगरy_mprime_in, cmd_size);
	kमुक्त(verअगरy_mprime_in);
	अगर (byte < 0) अणु
		dev_dbg(dev, "mei_cldev_send failed. %zd\n", byte);
		वापस byte;
	पूर्ण

	byte = mei_cldev_recv(cldev, (u8 *)&verअगरy_mprime_out,
			      माप(verअगरy_mprime_out));
	अगर (byte < 0) अणु
		dev_dbg(dev, "mei_cldev_recv failed. %zd\n", byte);
		वापस byte;
	पूर्ण

	अगर (verअगरy_mprime_out.header.status != ME_HDCP_STATUS_SUCCESS) अणु
		dev_dbg(dev, "ME cmd 0x%08X failed. status: 0x%X\n",
			WIRED_REPEATER_AUTH_STREAM_REQ,
			verअगरy_mprime_out.header.status);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * mei_hdcp_enable_authentication() - Mark a port as authenticated
 * through ME FW
 * @dev: device corresponding to the mei_cl_device
 * @data: Intel HW specअगरic hdcp data
 *
 * Return: 0 on Success, <0 on Failure
 */
अटल पूर्णांक mei_hdcp_enable_authentication(काष्ठा device *dev,
					  काष्ठा hdcp_port_data *data)
अणु
	काष्ठा wired_cmd_enable_auth_in enable_auth_in = अणु अणु 0 पूर्ण पूर्ण;
	काष्ठा wired_cmd_enable_auth_out enable_auth_out = अणु अणु 0 पूर्ण पूर्ण;
	काष्ठा mei_cl_device *cldev;
	sमाप_प्रकार byte;

	अगर (!dev || !data)
		वापस -EINVAL;

	cldev = to_mei_cl_device(dev);

	enable_auth_in.header.api_version = HDCP_API_VERSION;
	enable_auth_in.header.command_id = WIRED_ENABLE_AUTH;
	enable_auth_in.header.status = ME_HDCP_STATUS_SUCCESS;
	enable_auth_in.header.buffer_len = WIRED_CMD_BUF_LEN_ENABLE_AUTH_IN;

	enable_auth_in.port.पूर्णांकegrated_port_type = data->port_type;
	enable_auth_in.port.physical_port = (u8)data->fw_ddi;
	enable_auth_in.port.attached_transcoder = (u8)data->fw_tc;
	enable_auth_in.stream_type = data->streams[0].stream_type;

	byte = mei_cldev_send(cldev, (u8 *)&enable_auth_in,
			      माप(enable_auth_in));
	अगर (byte < 0) अणु
		dev_dbg(dev, "mei_cldev_send failed. %zd\n", byte);
		वापस byte;
	पूर्ण

	byte = mei_cldev_recv(cldev, (u8 *)&enable_auth_out,
			      माप(enable_auth_out));
	अगर (byte < 0) अणु
		dev_dbg(dev, "mei_cldev_recv failed. %zd\n", byte);
		वापस byte;
	पूर्ण

	अगर (enable_auth_out.header.status != ME_HDCP_STATUS_SUCCESS) अणु
		dev_dbg(dev, "ME cmd 0x%08X failed. status: 0x%X\n",
			WIRED_ENABLE_AUTH, enable_auth_out.header.status);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * mei_hdcp_बंद_session() - Close the Wired HDCP Tx session of ME FW per port.
 * This also disables the authenticated state of the port.
 * @dev: device corresponding to the mei_cl_device
 * @data: Intel HW specअगरic hdcp data
 *
 * Return: 0 on Success, <0 on Failure
 */
अटल पूर्णांक
mei_hdcp_बंद_session(काष्ठा device *dev, काष्ठा hdcp_port_data *data)
अणु
	काष्ठा wired_cmd_बंद_session_in session_बंद_in = अणु अणु 0 पूर्ण पूर्ण;
	काष्ठा wired_cmd_बंद_session_out session_बंद_out = अणु अणु 0 पूर्ण पूर्ण;
	काष्ठा mei_cl_device *cldev;
	sमाप_प्रकार byte;

	अगर (!dev || !data)
		वापस -EINVAL;

	cldev = to_mei_cl_device(dev);

	session_बंद_in.header.api_version = HDCP_API_VERSION;
	session_बंद_in.header.command_id = WIRED_CLOSE_SESSION;
	session_बंद_in.header.status = ME_HDCP_STATUS_SUCCESS;
	session_बंद_in.header.buffer_len =
				WIRED_CMD_BUF_LEN_CLOSE_SESSION_IN;

	session_बंद_in.port.पूर्णांकegrated_port_type = data->port_type;
	session_बंद_in.port.physical_port = (u8)data->fw_ddi;
	session_बंद_in.port.attached_transcoder = (u8)data->fw_tc;

	byte = mei_cldev_send(cldev, (u8 *)&session_बंद_in,
			      माप(session_बंद_in));
	अगर (byte < 0) अणु
		dev_dbg(dev, "mei_cldev_send failed. %zd\n", byte);
		वापस byte;
	पूर्ण

	byte = mei_cldev_recv(cldev, (u8 *)&session_बंद_out,
			      माप(session_बंद_out));
	अगर (byte < 0) अणु
		dev_dbg(dev, "mei_cldev_recv failed. %zd\n", byte);
		वापस byte;
	पूर्ण

	अगर (session_बंद_out.header.status != ME_HDCP_STATUS_SUCCESS) अणु
		dev_dbg(dev, "Session Close Failed. status: 0x%X\n",
			session_बंद_out.header.status);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i915_hdcp_component_ops mei_hdcp_ops = अणु
	.owner = THIS_MODULE,
	.initiate_hdcp2_session = mei_hdcp_initiate_session,
	.verअगरy_receiver_cert_prepare_km =
				mei_hdcp_verअगरy_receiver_cert_prepare_km,
	.verअगरy_hprime = mei_hdcp_verअगरy_hprime,
	.store_pairing_info = mei_hdcp_store_pairing_info,
	.initiate_locality_check = mei_hdcp_initiate_locality_check,
	.verअगरy_lprime = mei_hdcp_verअगरy_lprime,
	.get_session_key = mei_hdcp_get_session_key,
	.repeater_check_flow_prepare_ack =
				mei_hdcp_repeater_check_flow_prepare_ack,
	.verअगरy_mprime = mei_hdcp_verअगरy_mprime,
	.enable_hdcp_authentication = mei_hdcp_enable_authentication,
	.बंद_hdcp_session = mei_hdcp_बंद_session,
पूर्ण;

अटल पूर्णांक mei_component_master_bind(काष्ठा device *dev)
अणु
	काष्ठा mei_cl_device *cldev = to_mei_cl_device(dev);
	काष्ठा i915_hdcp_comp_master *comp_master =
						mei_cldev_get_drvdata(cldev);
	पूर्णांक ret;

	dev_dbg(dev, "%s\n", __func__);
	comp_master->ops = &mei_hdcp_ops;
	comp_master->mei_dev = dev;
	ret = component_bind_all(dev, comp_master);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम mei_component_master_unbind(काष्ठा device *dev)
अणु
	काष्ठा mei_cl_device *cldev = to_mei_cl_device(dev);
	काष्ठा i915_hdcp_comp_master *comp_master =
						mei_cldev_get_drvdata(cldev);

	dev_dbg(dev, "%s\n", __func__);
	component_unbind_all(dev, comp_master);
पूर्ण

अटल स्थिर काष्ठा component_master_ops mei_component_master_ops = अणु
	.bind = mei_component_master_bind,
	.unbind = mei_component_master_unbind,
पूर्ण;

/**
 * mei_hdcp_component_match - compare function क्रम matching mei hdcp.
 *
 *    The function checks अगर the driver is i915, the subcomponent is HDCP
 *    and the gअक्रम parent of hdcp and the parent of i915 are the same
 *    PCH device.
 *
 * @dev: master device
 * @subcomponent: subcomponent to match (I915_COMPONENT_HDCP)
 * @data: compare data (mei hdcp device)
 *
 * Return:
 * * 1 - अगर components match
 * * 0 - otherwise
 */
अटल पूर्णांक mei_hdcp_component_match(काष्ठा device *dev, पूर्णांक subcomponent,
				    व्योम *data)
अणु
	काष्ठा device *base = data;

	अगर (म_भेद(dev->driver->name, "i915") ||
	    subcomponent != I915_COMPONENT_HDCP)
		वापस 0;

	base = base->parent;
	अगर (!base)
		वापस 0;

	base = base->parent;
	dev = dev->parent;

	वापस (base && dev && dev == base);
पूर्ण

अटल पूर्णांक mei_hdcp_probe(काष्ठा mei_cl_device *cldev,
			  स्थिर काष्ठा mei_cl_device_id *id)
अणु
	काष्ठा i915_hdcp_comp_master *comp_master;
	काष्ठा component_match *master_match;
	पूर्णांक ret;

	ret = mei_cldev_enable(cldev);
	अगर (ret < 0) अणु
		dev_err(&cldev->dev, "mei_cldev_enable Failed. %d\n", ret);
		जाओ enable_err_निकास;
	पूर्ण

	comp_master = kzalloc(माप(*comp_master), GFP_KERNEL);
	अगर (!comp_master) अणु
		ret = -ENOMEM;
		जाओ err_निकास;
	पूर्ण

	master_match = शून्य;
	component_match_add_typed(&cldev->dev, &master_match,
				  mei_hdcp_component_match, &cldev->dev);
	अगर (IS_ERR_OR_शून्य(master_match)) अणु
		ret = -ENOMEM;
		जाओ err_निकास;
	पूर्ण

	mei_cldev_set_drvdata(cldev, comp_master);
	ret = component_master_add_with_match(&cldev->dev,
					      &mei_component_master_ops,
					      master_match);
	अगर (ret < 0) अणु
		dev_err(&cldev->dev, "Master comp add failed %d\n", ret);
		जाओ err_निकास;
	पूर्ण

	वापस 0;

err_निकास:
	mei_cldev_set_drvdata(cldev, शून्य);
	kमुक्त(comp_master);
	mei_cldev_disable(cldev);
enable_err_निकास:
	वापस ret;
पूर्ण

अटल व्योम mei_hdcp_हटाओ(काष्ठा mei_cl_device *cldev)
अणु
	काष्ठा i915_hdcp_comp_master *comp_master =
						mei_cldev_get_drvdata(cldev);
	पूर्णांक ret;

	component_master_del(&cldev->dev, &mei_component_master_ops);
	kमुक्त(comp_master);
	mei_cldev_set_drvdata(cldev, शून्य);

	ret = mei_cldev_disable(cldev);
	अगर (ret)
		dev_warn(&cldev->dev, "mei_cldev_disable() failed\n");
पूर्ण

#घोषणा MEI_UUID_HDCP GUID_INIT(0xB638AB7E, 0x94E2, 0x4EA2, 0xA5, \
				0x52, 0xD1, 0xC5, 0x4B, 0x62, 0x7F, 0x04)

अटल स्थिर काष्ठा mei_cl_device_id mei_hdcp_tbl[] = अणु
	अणु .uuid = MEI_UUID_HDCP, .version = MEI_CL_VERSION_ANY पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(mei, mei_hdcp_tbl);

अटल काष्ठा mei_cl_driver mei_hdcp_driver = अणु
	.id_table = mei_hdcp_tbl,
	.name = KBUILD_MODNAME,
	.probe = mei_hdcp_probe,
	.हटाओ	= mei_hdcp_हटाओ,
पूर्ण;

module_mei_cl_driver(mei_hdcp_driver);

MODULE_AUTHOR("Intel Corporation");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("MEI HDCP");
