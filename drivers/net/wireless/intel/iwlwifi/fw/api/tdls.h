<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2012-2014, 2018 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#अगर_अघोषित __iwl_fw_api_tdls_h__
#घोषणा __iwl_fw_api_tdls_h__

#समावेश "fw/api/tx.h"
#समावेश "fw/api/phy-ctxt.h"

#घोषणा IWL_MVM_TDLS_STA_COUNT	4

/* Type of TDLS request */
क्रमागत iwl_tdls_channel_चयन_type अणु
	TDLS_SEND_CHAN_SW_REQ = 0,
	TDLS_SEND_CHAN_SW_RESP_AND_MOVE_CH,
	TDLS_MOVE_CH,
पूर्ण; /* TDLS_STA_CHANNEL_SWITCH_CMD_TYPE_API_E_VER_1 */

/**
 * काष्ठा iwl_tdls_channel_चयन_timing - Switch timing in TDLS channel-चयन
 * @frame_बारtamp: GP2 बारtamp of channel-चयन request/response packet
 *	received from peer
 * @max_offchan_duration: What amount of microseconds out of a DTIM is given
 *	to the TDLS off-channel communication. For instance अगर the DTIM is
 *	200TU and the TDLS peer is to be given 25% of the समय, the value
 *	given will be 50TU, or 50 * 1024 अगर translated पूर्णांकo microseconds.
 * @चयन_समय: चयन समय the peer sent in its channel चयन timing IE
 * @चयन_समयout: चयन समयout the peer sent in its channel चयन timing IE
 */
काष्ठा iwl_tdls_channel_चयन_timing अणु
	__le32 frame_बारtamp; /* GP2 समय of peer packet Rx */
	__le32 max_offchan_duration; /* given in micro-seconds */
	__le32 चयन_समय; /* given in micro-seconds */
	__le32 चयन_समयout; /* given in micro-seconds */
पूर्ण __packed; /* TDLS_STA_CHANNEL_SWITCH_TIMING_DATA_API_S_VER_1 */

#घोषणा IWL_TDLS_CH_SW_FRAME_MAX_SIZE 200

/**
 * काष्ठा iwl_tdls_channel_चयन_frame - TDLS channel चयन frame ढाँचा
 *
 * A ढाँचा representing a TDLS channel-चयन request or response frame
 *
 * @चयन_समय_offset: offset to the channel चयन timing IE in the ढाँचा
 * @tx_cmd: Tx parameters क्रम the frame
 * @data: frame data
 */
काष्ठा iwl_tdls_channel_चयन_frame अणु
	__le32 चयन_समय_offset;
	काष्ठा iwl_tx_cmd tx_cmd;
	u8 data[IWL_TDLS_CH_SW_FRAME_MAX_SIZE];
पूर्ण __packed; /* TDLS_STA_CHANNEL_SWITCH_FRAME_API_S_VER_1 */

/**
 * काष्ठा iwl_tdls_channel_चयन_cmd_tail - tail of iwl_tdls_channel_चयन_cmd
 *
 * @timing: timing related data क्रम command
 * @frame: channel-चयन request/response ढाँचा, depending to चयन_type
 */
काष्ठा iwl_tdls_channel_चयन_cmd_tail अणु
	काष्ठा iwl_tdls_channel_चयन_timing timing;
	काष्ठा iwl_tdls_channel_चयन_frame frame;
पूर्ण __packed;

/**
 * काष्ठा iwl_tdls_channel_चयन_cmd - TDLS channel चयन command
 *
 * The command is sent to initiate a channel चयन and also in response to
 * incoming TDLS channel-चयन request/response packets from remote peers.
 *
 * @चयन_type: see &क्रमागत iwl_tdls_channel_चयन_type
 * @peer_sta_id: station id of TDLS peer
 * @ci: channel we चयन to
 * @tail: command tail
 */
काष्ठा iwl_tdls_channel_चयन_cmd अणु
	u8 चयन_type;
	__le32 peer_sta_id;
	काष्ठा iwl_fw_channel_info ci;
	काष्ठा iwl_tdls_channel_चयन_cmd_tail tail;
पूर्ण __packed; /* TDLS_STA_CHANNEL_SWITCH_CMD_API_S_VER_1 */

/**
 * काष्ठा iwl_tdls_channel_चयन_notअगर - TDLS channel चयन start notअगरication
 *
 * @status: non-zero on success
 * @offchannel_duration: duration given in microseconds
 * @sta_id: peer currently perक्रमming the channel-चयन with
 */
काष्ठा iwl_tdls_channel_चयन_notअगर अणु
	__le32 status;
	__le32 offchannel_duration;
	__le32 sta_id;
पूर्ण __packed; /* TDLS_STA_CHANNEL_SWITCH_NTFY_API_S_VER_1 */

/**
 * काष्ठा iwl_tdls_sta_info - TDLS station info
 *
 * @sta_id: station id of the TDLS peer
 * @tx_to_peer_tid: TID reserved vs. the peer क्रम FW based Tx
 * @tx_to_peer_ssn: initial SSN the FW should use क्रम Tx on its TID vs the peer
 * @is_initiator: 1 अगर the peer is the TDLS link initiator, 0 otherwise
 */
काष्ठा iwl_tdls_sta_info अणु
	u8 sta_id;
	u8 tx_to_peer_tid;
	__le16 tx_to_peer_ssn;
	__le32 is_initiator;
पूर्ण __packed; /* TDLS_STA_INFO_VER_1 */

/**
 * काष्ठा iwl_tdls_config_cmd - TDLS basic config command
 *
 * @id_and_color: MAC id and color being configured
 * @tdls_peer_count: amount of currently connected TDLS peers
 * @tx_to_ap_tid: TID reverved vs. the AP क्रम FW based Tx
 * @tx_to_ap_ssn: initial SSN the FW should use क्रम Tx on its TID vs. the AP
 * @sta_info: per-station info. Only the first tdls_peer_count entries are set
 * @pti_req_data_offset: offset of network-level data क्रम the PTI ढाँचा
 * @pti_req_tx_cmd: Tx parameters क्रम PTI request ढाँचा
 * @pti_req_ढाँचा: PTI request ढाँचा data
 */
काष्ठा iwl_tdls_config_cmd अणु
	__le32 id_and_color; /* mac id and color */
	u8 tdls_peer_count;
	u8 tx_to_ap_tid;
	__le16 tx_to_ap_ssn;
	काष्ठा iwl_tdls_sta_info sta_info[IWL_MVM_TDLS_STA_COUNT];

	__le32 pti_req_data_offset;
	काष्ठा iwl_tx_cmd pti_req_tx_cmd;
	u8 pti_req_ढाँचा[0];
पूर्ण __packed; /* TDLS_CONFIG_CMD_API_S_VER_1 */

/**
 * काष्ठा iwl_tdls_config_sta_info_res - TDLS per-station config inक्रमmation
 *
 * @sta_id: station id of the TDLS peer
 * @tx_to_peer_last_seq: last sequence number used by FW during FW-based Tx to
 *	the peer
 */
काष्ठा iwl_tdls_config_sta_info_res अणु
	__le16 sta_id;
	__le16 tx_to_peer_last_seq;
पूर्ण __packed; /* TDLS_STA_INFO_RSP_VER_1 */

/**
 * काष्ठा iwl_tdls_config_res - TDLS config inक्रमmation from FW
 *
 * @tx_to_ap_last_seq: last sequence number used by FW during FW-based Tx to AP
 * @sta_info: per-station TDLS config inक्रमmation
 */
काष्ठा iwl_tdls_config_res अणु
	__le32 tx_to_ap_last_seq;
	काष्ठा iwl_tdls_config_sta_info_res sta_info[IWL_MVM_TDLS_STA_COUNT];
पूर्ण __packed; /* TDLS_CONFIG_RSP_API_S_VER_1 */

#पूर्ण_अगर /* __iwl_fw_api_tdls_h__ */
