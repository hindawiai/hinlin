<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0+) */
/*
 * Copyright तऊ 2017-2019 Intel Corporation
 *
 * Authors:
 * Ramalingam C <ramalingam.c@पूर्णांकel.com>
 */

#अगर_अघोषित _I915_MEI_HDCP_INTERFACE_H_
#घोषणा _I915_MEI_HDCP_INTERFACE_H_

#समावेश <linux/mutex.h>
#समावेश <linux/device.h>
#समावेश <drm/drm_hdcp.h>

/**
 * क्रमागत hdcp_port_type - HDCP port implementation type defined by ME FW
 * @HDCP_PORT_TYPE_INVALID: Invalid hdcp port type
 * @HDCP_PORT_TYPE_INTEGRATED: In-Host HDCP2.x port
 * @HDCP_PORT_TYPE_LSPCON: HDCP2.2 discrete wired Tx port with LSPCON
 *			   (HDMI 2.0) solution
 * @HDCP_PORT_TYPE_CPDP: HDCP2.2 discrete wired Tx port using the CPDP (DP 1.3)
 *			 solution
 */
क्रमागत hdcp_port_type अणु
	HDCP_PORT_TYPE_INVALID,
	HDCP_PORT_TYPE_INTEGRATED,
	HDCP_PORT_TYPE_LSPCON,
	HDCP_PORT_TYPE_CPDP
पूर्ण;

/**
 * क्रमागत hdcp_wired_protocol - HDCP adaptation used on the port
 * @HDCP_PROTOCOL_INVALID: Invalid HDCP adaptation protocol
 * @HDCP_PROTOCOL_HDMI: HDMI adaptation of HDCP used on the port
 * @HDCP_PROTOCOL_DP: DP adaptation of HDCP used on the port
 */
क्रमागत hdcp_wired_protocol अणु
	HDCP_PROTOCOL_INVALID,
	HDCP_PROTOCOL_HDMI,
	HDCP_PROTOCOL_DP
पूर्ण;

क्रमागत mei_fw_ddi अणु
	MEI_DDI_INVALID_PORT = 0x0,

	MEI_DDI_B = 1,
	MEI_DDI_C,
	MEI_DDI_D,
	MEI_DDI_E,
	MEI_DDI_F,
	MEI_DDI_A = 7,
	MEI_DDI_RANGE_END = MEI_DDI_A,
पूर्ण;

/**
 * क्रमागत mei_fw_tc - ME Firmware defined index क्रम transcoders
 * @MEI_INVALID_TRANSCODER: Index क्रम Invalid transcoder
 * @MEI_TRANSCODER_EDP: Index क्रम EDP Transcoder
 * @MEI_TRANSCODER_DSI0: Index क्रम DSI0 Transcoder
 * @MEI_TRANSCODER_DSI1: Index क्रम DSI1 Transcoder
 * @MEI_TRANSCODER_A: Index क्रम Transcoder A
 * @MEI_TRANSCODER_B: Index क्रम Transcoder B
 * @MEI_TRANSCODER_C: Index क्रम Transcoder C
 * @MEI_TRANSCODER_D: Index क्रम Transcoder D
 */
क्रमागत mei_fw_tc अणु
	MEI_INVALID_TRANSCODER = 0x00,
	MEI_TRANSCODER_EDP,
	MEI_TRANSCODER_DSI0,
	MEI_TRANSCODER_DSI1,
	MEI_TRANSCODER_A = 0x10,
	MEI_TRANSCODER_B,
	MEI_TRANSCODER_C,
	MEI_TRANSCODER_D
पूर्ण;

/**
 * काष्ठा hdcp_port_data - पूर्णांकel specअगरic HDCP port data
 * @fw_ddi: ddi index as per ME FW
 * @fw_tc: transcoder index as per ME FW
 * @port_type: HDCP port type as per ME FW classअगरication
 * @protocol: HDCP adaptation as per ME FW
 * @k: No of streams transmitted on a port. Only on DP MST this is != 1
 * @seq_num_m: Count of RepeaterAuth_Stream_Manage msg propagated.
 *	       Initialized to 0 on AKE_INIT. Incremented after every successful
 *	       transmission of RepeaterAuth_Stream_Manage message. When it rolls
 *	       over re-Auth has to be triggered.
 * @streams: काष्ठा hdcp2_streamid_type[k]. Defines the type and id क्रम the
 *	     streams
 */
काष्ठा hdcp_port_data अणु
	क्रमागत mei_fw_ddi fw_ddi;
	क्रमागत mei_fw_tc fw_tc;
	u8 port_type;
	u8 protocol;
	u16 k;
	u32 seq_num_m;
	काष्ठा hdcp2_streamid_type *streams;
पूर्ण;

/**
 * काष्ठा i915_hdcp_component_ops- ops क्रम HDCP2.2 services.
 * @owner: Module providing the ops
 * @initiate_hdcp2_session: Initiate a Wired HDCP2.2 Tx Session.
 *			    And Prepare AKE_Init.
 * @verअगरy_receiver_cert_prepare_km: Verअगरy the Receiver Certअगरicate
 *				     AKE_Send_Cert and prepare
				     AKE_Stored_Km/AKE_No_Stored_Km
 * @verअगरy_hprime: Verअगरy AKE_Send_H_prime
 * @store_pairing_info: Store pairing info received
 * @initiate_locality_check: Prepare LC_Init
 * @verअगरy_lprime: Verअगरy lprime
 * @get_session_key: Prepare SKE_Send_Eks
 * @repeater_check_flow_prepare_ack: Validate the Downstream topology
 *				     and prepare rep_ack
 * @verअगरy_mprime: Verअगरy mprime
 * @enable_hdcp_authentication:  Mark a port as authenticated.
 * @बंद_hdcp_session: Close the Wired HDCP Tx session per port.
 *			This also disables the authenticated state of the port.
 */
काष्ठा i915_hdcp_component_ops अणु
	/**
	 * @owner: mei_hdcp module
	 */
	काष्ठा module *owner;

	पूर्णांक (*initiate_hdcp2_session)(काष्ठा device *dev,
				      काष्ठा hdcp_port_data *data,
				      काष्ठा hdcp2_ake_init *ake_data);
	पूर्णांक (*verअगरy_receiver_cert_prepare_km)(काष्ठा device *dev,
					       काष्ठा hdcp_port_data *data,
					       काष्ठा hdcp2_ake_send_cert
								*rx_cert,
					       bool *km_stored,
					       काष्ठा hdcp2_ake_no_stored_km
								*ek_pub_km,
					       माप_प्रकार *msg_sz);
	पूर्णांक (*verअगरy_hprime)(काष्ठा device *dev,
			     काष्ठा hdcp_port_data *data,
			     काष्ठा hdcp2_ake_send_hprime *rx_hprime);
	पूर्णांक (*store_pairing_info)(काष्ठा device *dev,
				  काष्ठा hdcp_port_data *data,
				  काष्ठा hdcp2_ake_send_pairing_info
								*pairing_info);
	पूर्णांक (*initiate_locality_check)(काष्ठा device *dev,
				       काष्ठा hdcp_port_data *data,
				       काष्ठा hdcp2_lc_init *lc_init_data);
	पूर्णांक (*verअगरy_lprime)(काष्ठा device *dev,
			     काष्ठा hdcp_port_data *data,
			     काष्ठा hdcp2_lc_send_lprime *rx_lprime);
	पूर्णांक (*get_session_key)(काष्ठा device *dev,
			       काष्ठा hdcp_port_data *data,
			       काष्ठा hdcp2_ske_send_eks *ske_data);
	पूर्णांक (*repeater_check_flow_prepare_ack)(काष्ठा device *dev,
					       काष्ठा hdcp_port_data *data,
					       काष्ठा hdcp2_rep_send_receiverid_list
								*rep_topology,
					       काष्ठा hdcp2_rep_send_ack
								*rep_send_ack);
	पूर्णांक (*verअगरy_mprime)(काष्ठा device *dev,
			     काष्ठा hdcp_port_data *data,
			     काष्ठा hdcp2_rep_stream_पढ़ोy *stream_पढ़ोy);
	पूर्णांक (*enable_hdcp_authentication)(काष्ठा device *dev,
					  काष्ठा hdcp_port_data *data);
	पूर्णांक (*बंद_hdcp_session)(काष्ठा device *dev,
				  काष्ठा hdcp_port_data *data);
पूर्ण;

/**
 * काष्ठा i915_hdcp_component_master - Used क्रम communication between i915
 * and mei_hdcp drivers क्रम the HDCP2.2 services
 * @mei_dev: device that provide the HDCP2.2 service from MEI Bus.
 * @hdcp_ops: Ops implemented by mei_hdcp driver, used by i915 driver.
 */
काष्ठा i915_hdcp_comp_master अणु
	काष्ठा device *mei_dev;
	स्थिर काष्ठा i915_hdcp_component_ops *ops;

	/* To protect the above members. */
	काष्ठा mutex mutex;
पूर्ण;

#पूर्ण_अगर /* _I915_MEI_HDCP_INTERFACE_H_ */
