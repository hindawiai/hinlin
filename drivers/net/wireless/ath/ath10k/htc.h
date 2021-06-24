<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (c) 2005-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2016 Qualcomm Atheros, Inc.
 */

#अगर_अघोषित _HTC_H_
#घोषणा _HTC_H_

#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/bug.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/समयr.h>
#समावेश <linux/bitfield.h>

काष्ठा ath10k;

/****************/
/* HTC protocol */
/****************/

/*
 * HTC - host-target control protocol
 *
 * tx packets are generally <htc_hdr><payload>
 * rx packets are more complex: <htc_hdr><payload><trailer>
 *
 * The payload + trailer length is stored in len.
 * To get payload-only length one needs to payload - trailer_len.
 *
 * Trailer contains (possibly) multiple <htc_record>.
 * Each record is a id-len-value.
 *
 * HTC header flags, control_byte0, control_byte1
 * have dअगरferent meaning depending whether its tx
 * or rx.
 *
 * Alignment: htc_hdr, payload and trailer are
 * 4-byte aligned.
 */

#घोषणा HTC_HOST_MAX_MSG_PER_RX_BUNDLE        32

क्रमागत ath10k_htc_tx_flags अणु
	ATH10K_HTC_FLAG_NEED_CREDIT_UPDATE = 0x01,
	ATH10K_HTC_FLAG_SEND_BUNDLE        = 0x02
पूर्ण;

क्रमागत ath10k_htc_rx_flags अणु
	ATH10K_HTC_FLAGS_RECV_1MORE_BLOCK = 0x01,
	ATH10K_HTC_FLAG_TRAILER_PRESENT = 0x02,
पूर्ण;

#घोषणा ATH10K_HTC_FLAG_BUNDLE_MASK GENMASK(7, 4)

/* bits 2-3 are क्रम extra bundle count bits 4-5 */
#घोषणा ATH10K_HTC_BUNDLE_EXTRA_MASK GENMASK(3, 2)
#घोषणा ATH10K_HTC_BUNDLE_EXTRA_SHIFT 4

अटल अंतरभूत अचिन्हित पूर्णांक ath10k_htc_get_bundle_count(u8 max_msgs, u8 flags)
अणु
	अचिन्हित पूर्णांक count, extra_count = 0;

	count = FIELD_GET(ATH10K_HTC_FLAG_BUNDLE_MASK, flags);

	अगर (max_msgs > 16)
		extra_count = FIELD_GET(ATH10K_HTC_BUNDLE_EXTRA_MASK, flags) <<
			ATH10K_HTC_BUNDLE_EXTRA_SHIFT;

	वापस count + extra_count;
पूर्ण

काष्ठा ath10k_htc_hdr अणु
	u8 eid; /* @क्रमागत ath10k_htc_ep_id */
	u8 flags; /* @क्रमागत ath10k_htc_tx_flags, ath10k_htc_rx_flags */
	__le16 len;
	जोड़ अणु
		u8 trailer_len; /* क्रम rx */
		u8 control_byte0;
	पूर्ण __packed;
	जोड़ अणु
		u8 seq_no; /* क्रम tx */
		u8 control_byte1;
	पूर्ण __packed;
	जोड़ अणु
		__le16 pad_len;
		काष्ठा अणु
			u8 pad0;
			u8 pad1;
		पूर्ण __packed;
	पूर्ण __packed;

पूर्ण __packed __aligned(4);

क्रमागत ath10k_ath10k_htc_msg_id अणु
	ATH10K_HTC_MSG_READY_ID                = 1,
	ATH10K_HTC_MSG_CONNECT_SERVICE_ID      = 2,
	ATH10K_HTC_MSG_CONNECT_SERVICE_RESP_ID = 3,
	ATH10K_HTC_MSG_SETUP_COMPLETE_ID       = 4,
	ATH10K_HTC_MSG_SETUP_COMPLETE_EX_ID    = 5,
	ATH10K_HTC_MSG_SEND_SUSPEND_COMPLETE   = 6
पूर्ण;

क्रमागत ath10k_htc_version अणु
	ATH10K_HTC_VERSION_2P0 = 0x00, /* 2.0 */
	ATH10K_HTC_VERSION_2P1 = 0x01, /* 2.1 */
पूर्ण;

क्रमागत ath10k_htc_conn_flags अणु
	ATH10K_HTC_CONN_FLAGS_THRESHOLD_LEVEL_ONE_FOURTH    = 0x0,
	ATH10K_HTC_CONN_FLAGS_THRESHOLD_LEVEL_ONE_HALF      = 0x1,
	ATH10K_HTC_CONN_FLAGS_THRESHOLD_LEVEL_THREE_FOURTHS = 0x2,
	ATH10K_HTC_CONN_FLAGS_THRESHOLD_LEVEL_UNITY         = 0x3,
#घोषणा ATH10K_HTC_CONN_FLAGS_THRESHOLD_LEVEL_MASK 0x3
	ATH10K_HTC_CONN_FLAGS_REDUCE_CREDIT_DRIBBLE    = 1 << 2,
	ATH10K_HTC_CONN_FLAGS_DISABLE_CREDIT_FLOW_CTRL = 1 << 3
#घोषणा ATH10K_HTC_CONN_FLAGS_RECV_ALLOC_MASK 0xFF00
#घोषणा ATH10K_HTC_CONN_FLAGS_RECV_ALLOC_LSB  8
पूर्ण;

#घोषणा ATH10K_HTC_MSG_READY_EXT_ALT_DATA_MASK 0xFFF

क्रमागत ath10k_htc_conn_svc_status अणु
	ATH10K_HTC_CONN_SVC_STATUS_SUCCESS      = 0,
	ATH10K_HTC_CONN_SVC_STATUS_NOT_FOUND    = 1,
	ATH10K_HTC_CONN_SVC_STATUS_FAILED       = 2,
	ATH10K_HTC_CONN_SVC_STATUS_NO_RESOURCES = 3,
	ATH10K_HTC_CONN_SVC_STATUS_NO_MORE_EP   = 4
पूर्ण;

#घोषणा ATH10K_MAX_MSG_PER_HTC_TX_BUNDLE        32
#घोषणा ATH10K_MIN_MSG_PER_HTC_TX_BUNDLE        2
#घोषणा ATH10K_MIN_CREDIT_PER_HTC_TX_BUNDLE     2

क्रमागत ath10k_htc_setup_complete_flags अणु
	ATH10K_HTC_SETUP_COMPLETE_FLAGS_RX_BNDL_EN = 1
पूर्ण;

काष्ठा ath10k_ath10k_htc_msg_hdr अणु
	__le16 message_id; /* @क्रमागत htc_message_id */
पूर्ण __packed;

काष्ठा ath10k_htc_unknown अणु
	u8 pad0;
	u8 pad1;
पूर्ण __packed;

काष्ठा ath10k_htc_पढ़ोy अणु
	__le16 credit_count;
	__le16 credit_size;
	u8 max_endpoपूर्णांकs;
	u8 pad0;
पूर्ण __packed;

काष्ठा ath10k_htc_पढ़ोy_extended अणु
	काष्ठा ath10k_htc_पढ़ोy base;
	u8 htc_version; /* @क्रमागत ath10k_htc_version */
	u8 max_msgs_per_htc_bundle;
	जोड़ अणु
		__le16 reserved;
		काष्ठा अणु
			u8 pad0;
			u8 pad1;
		पूर्ण __packed;
	पूर्ण __packed;

पूर्ण __packed;

काष्ठा ath10k_htc_conn_svc अणु
	__le16 service_id;
	__le16 flags; /* @क्रमागत ath10k_htc_conn_flags */
	u8 pad0;
	u8 pad1;
पूर्ण __packed;

काष्ठा ath10k_htc_conn_svc_response अणु
	__le16 service_id;
	u8 status; /* @क्रमागत ath10k_htc_conn_svc_status */
	u8 eid;
	__le16 max_msg_size;
पूर्ण __packed;

काष्ठा ath10k_htc_setup_complete_extended अणु
	u8 pad0;
	u8 pad1;
	__le32 flags; /* @क्रमागत htc_setup_complete_flags */
	u8 max_msgs_per_bundled_recv;
	u8 pad2;
	u8 pad3;
	u8 pad4;
पूर्ण __packed;

काष्ठा ath10k_htc_msg अणु
	काष्ठा ath10k_ath10k_htc_msg_hdr hdr;
	जोड़ अणु
		/* host-to-target */
		काष्ठा ath10k_htc_conn_svc connect_service;
		काष्ठा ath10k_htc_पढ़ोy पढ़ोy;
		काष्ठा ath10k_htc_पढ़ोy_extended पढ़ोy_ext;
		काष्ठा ath10k_htc_unknown unknown;
		काष्ठा ath10k_htc_setup_complete_extended setup_complete_ext;

		/* target-to-host */
		काष्ठा ath10k_htc_conn_svc_response connect_service_response;
	पूर्ण;
पूर्ण __packed __aligned(4);

क्रमागत ath10k_ath10k_htc_record_id अणु
	ATH10K_HTC_RECORD_शून्य             = 0,
	ATH10K_HTC_RECORD_CREDITS          = 1,
	ATH10K_HTC_RECORD_LOOKAHEAD        = 2,
	ATH10K_HTC_RECORD_LOOKAHEAD_BUNDLE = 3,
पूर्ण;

काष्ठा ath10k_ath10k_htc_record_hdr अणु
	u8 id; /* @क्रमागत ath10k_ath10k_htc_record_id */
	u8 len;
	u8 pad0;
	u8 pad1;
पूर्ण __packed;

काष्ठा ath10k_htc_credit_report अणु
	u8 eid; /* @क्रमागत ath10k_htc_ep_id */
	u8 credits;
	u8 pad0;
	u8 pad1;
पूर्ण __packed;

काष्ठा ath10k_htc_lookahead_report अणु
	u8 pre_valid;
	u8 pad0;
	u8 pad1;
	u8 pad2;
	u8 lookahead[4];
	u8 post_valid;
	u8 pad3;
	u8 pad4;
	u8 pad5;
पूर्ण __packed;

काष्ठा ath10k_htc_lookahead_bundle अणु
	u8 lookahead[4];
पूर्ण __packed;

काष्ठा ath10k_htc_record अणु
	काष्ठा ath10k_ath10k_htc_record_hdr hdr;
	जोड़ अणु
		काष्ठा ath10k_htc_credit_report credit_report[0];
		काष्ठा ath10k_htc_lookahead_report lookahead_report[0];
		काष्ठा ath10k_htc_lookahead_bundle lookahead_bundle[0];
		u8 pauload[0];
	पूर्ण;
पूर्ण __packed __aligned(4);

/*
 * note: the trailer offset is dynamic depending
 * on payload length. this is only a काष्ठा layout draft
 */
काष्ठा ath10k_htc_frame अणु
	काष्ठा ath10k_htc_hdr hdr;
	जोड़ अणु
		काष्ठा ath10k_htc_msg msg;
		u8 payload[0];
	पूर्ण;
	काष्ठा ath10k_htc_record trailer[0];
पूर्ण __packed __aligned(4);

/*******************/
/* Host-side stuff */
/*******************/

क्रमागत ath10k_htc_svc_gid अणु
	ATH10K_HTC_SVC_GRP_RSVD = 0,
	ATH10K_HTC_SVC_GRP_WMI = 1,
	ATH10K_HTC_SVC_GRP_NMI = 2,
	ATH10K_HTC_SVC_GRP_HTT = 3,
	ATH10K_LOG_SERVICE_GROUP = 6,

	ATH10K_HTC_SVC_GRP_TEST = 254,
	ATH10K_HTC_SVC_GRP_LAST = 255,
पूर्ण;

#घोषणा SVC(group, idx) \
	(पूर्णांक)(((पूर्णांक)(group) << 8) | (पूर्णांक)(idx))

क्रमागत ath10k_htc_svc_id अणु
	/* NOTE: service ID of 0x0000 is reserved and should never be used */
	ATH10K_HTC_SVC_ID_RESERVED	= 0x0000,
	ATH10K_HTC_SVC_ID_UNUSED	= ATH10K_HTC_SVC_ID_RESERVED,

	ATH10K_HTC_SVC_ID_RSVD_CTRL	= SVC(ATH10K_HTC_SVC_GRP_RSVD, 1),
	ATH10K_HTC_SVC_ID_WMI_CONTROL	= SVC(ATH10K_HTC_SVC_GRP_WMI, 0),
	ATH10K_HTC_SVC_ID_WMI_DATA_BE	= SVC(ATH10K_HTC_SVC_GRP_WMI, 1),
	ATH10K_HTC_SVC_ID_WMI_DATA_BK	= SVC(ATH10K_HTC_SVC_GRP_WMI, 2),
	ATH10K_HTC_SVC_ID_WMI_DATA_VI	= SVC(ATH10K_HTC_SVC_GRP_WMI, 3),
	ATH10K_HTC_SVC_ID_WMI_DATA_VO	= SVC(ATH10K_HTC_SVC_GRP_WMI, 4),

	ATH10K_HTC_SVC_ID_NMI_CONTROL	= SVC(ATH10K_HTC_SVC_GRP_NMI, 0),
	ATH10K_HTC_SVC_ID_NMI_DATA	= SVC(ATH10K_HTC_SVC_GRP_NMI, 1),

	ATH10K_HTC_SVC_ID_HTT_DATA_MSG	= SVC(ATH10K_HTC_SVC_GRP_HTT, 0),

	ATH10K_HTC_SVC_ID_HTT_DATA2_MSG = SVC(ATH10K_HTC_SVC_GRP_HTT, 1),
	ATH10K_HTC_SVC_ID_HTT_DATA3_MSG = SVC(ATH10K_HTC_SVC_GRP_HTT, 2),
	ATH10K_HTC_SVC_ID_HTT_LOG_MSG = SVC(ATH10K_LOG_SERVICE_GROUP, 0),
	/* raw stream service (i.e. flash, tcmd, calibration apps) */
	ATH10K_HTC_SVC_ID_TEST_RAW_STREAMS = SVC(ATH10K_HTC_SVC_GRP_TEST, 0),
पूर्ण;

#अघोषित SVC

क्रमागत ath10k_htc_ep_id अणु
	ATH10K_HTC_EP_UNUSED = -1,
	ATH10K_HTC_EP_0 = 0,
	ATH10K_HTC_EP_1 = 1,
	ATH10K_HTC_EP_2,
	ATH10K_HTC_EP_3,
	ATH10K_HTC_EP_4,
	ATH10K_HTC_EP_5,
	ATH10K_HTC_EP_6,
	ATH10K_HTC_EP_7,
	ATH10K_HTC_EP_8,
	ATH10K_HTC_EP_COUNT,
पूर्ण;

काष्ठा ath10k_htc_ops अणु
	व्योम (*target_send_suspend_complete)(काष्ठा ath10k *ar);
पूर्ण;

काष्ठा ath10k_htc_ep_ops अणु
	व्योम (*ep_tx_complete)(काष्ठा ath10k *, काष्ठा sk_buff *);
	व्योम (*ep_rx_complete)(काष्ठा ath10k *, काष्ठा sk_buff *);
	व्योम (*ep_tx_credits)(काष्ठा ath10k *);
पूर्ण;

/* service connection inक्रमmation */
काष्ठा ath10k_htc_svc_conn_req अणु
	u16 service_id;
	काष्ठा ath10k_htc_ep_ops ep_ops;
	पूर्णांक max_send_queue_depth;
पूर्ण;

/* service connection response inक्रमmation */
काष्ठा ath10k_htc_svc_conn_resp अणु
	u8 buffer_len;
	u8 actual_len;
	क्रमागत ath10k_htc_ep_id eid;
	अचिन्हित पूर्णांक max_msg_len;
	u8 connect_resp_code;
पूर्ण;

#घोषणा ATH10K_NUM_CONTROL_TX_BUFFERS 2
#घोषणा ATH10K_HTC_MAX_LEN 4096
#घोषणा ATH10K_HTC_MAX_CTRL_MSG_LEN 256
#घोषणा ATH10K_HTC_WAIT_TIMEOUT_HZ (1 * HZ)
#घोषणा ATH10K_HTC_CONTROL_BUFFER_SIZE (ATH10K_HTC_MAX_CTRL_MSG_LEN + \
					माप(काष्ठा ath10k_htc_hdr))
#घोषणा ATH10K_HTC_CONN_SVC_TIMEOUT_HZ (1 * HZ)

काष्ठा ath10k_htc_ep अणु
	काष्ठा ath10k_htc *htc;
	क्रमागत ath10k_htc_ep_id eid;
	क्रमागत ath10k_htc_svc_id service_id;
	काष्ठा ath10k_htc_ep_ops ep_ops;

	पूर्णांक max_tx_queue_depth;
	पूर्णांक max_ep_message_len;
	u8 ul_pipe_id;
	u8 dl_pipe_id;

	u8 seq_no; /* क्रम debugging */
	पूर्णांक tx_credits;
	पूर्णांक tx_credit_size;
	bool tx_credit_flow_enabled;
	bool bundle_tx;
	काष्ठा sk_buff_head tx_req_head;
	काष्ठा sk_buff_head tx_complete_head;

पूर्ण;

काष्ठा ath10k_htc_svc_tx_credits अणु
	u16 service_id;
	u8  credit_allocation;
पूर्ण;

काष्ठा ath10k_htc अणु
	काष्ठा ath10k *ar;
	काष्ठा ath10k_htc_ep endpoपूर्णांक[ATH10K_HTC_EP_COUNT];

	/* protects endpoपूर्णांकs */
	spinlock_t tx_lock;

	काष्ठा ath10k_htc_ops htc_ops;

	u8 control_resp_buffer[ATH10K_HTC_MAX_CTRL_MSG_LEN];
	पूर्णांक control_resp_len;

	काष्ठा completion ctl_resp;

	पूर्णांक total_transmit_credits;
	पूर्णांक target_credit_size;
	u8 max_msgs_per_htc_bundle;
	पूर्णांक alt_data_credit_size;
पूर्ण;

पूर्णांक ath10k_htc_init(काष्ठा ath10k *ar);
पूर्णांक ath10k_htc_रुको_target(काष्ठा ath10k_htc *htc);
व्योम ath10k_htc_setup_tx_req(काष्ठा ath10k_htc_ep *ep);
पूर्णांक ath10k_htc_start(काष्ठा ath10k_htc *htc);
पूर्णांक ath10k_htc_connect_service(काष्ठा ath10k_htc *htc,
			       काष्ठा ath10k_htc_svc_conn_req  *conn_req,
			       काष्ठा ath10k_htc_svc_conn_resp *conn_resp);
व्योम ath10k_htc_change_tx_credit_flow(काष्ठा ath10k_htc *htc,
				      क्रमागत ath10k_htc_ep_id eid,
				      bool enable);
पूर्णांक ath10k_htc_send(काष्ठा ath10k_htc *htc, क्रमागत ath10k_htc_ep_id eid,
		    काष्ठा sk_buff *packet);
व्योम ath10k_htc_stop_hl(काष्ठा ath10k *ar);

पूर्णांक ath10k_htc_send_hl(काष्ठा ath10k_htc *htc, क्रमागत ath10k_htc_ep_id eid,
		       काष्ठा sk_buff *packet);
काष्ठा sk_buff *ath10k_htc_alloc_skb(काष्ठा ath10k *ar, पूर्णांक size);
व्योम ath10k_htc_tx_completion_handler(काष्ठा ath10k *ar, काष्ठा sk_buff *skb);
व्योम ath10k_htc_rx_completion_handler(काष्ठा ath10k *ar, काष्ठा sk_buff *skb);
व्योम ath10k_htc_notअगरy_tx_completion(काष्ठा ath10k_htc_ep *ep,
				     काष्ठा sk_buff *skb);
पूर्णांक ath10k_htc_process_trailer(काष्ठा ath10k_htc *htc,
			       u8 *buffer,
			       पूर्णांक length,
			       क्रमागत ath10k_htc_ep_id src_eid,
			       व्योम *next_lookaheads,
			       पूर्णांक *next_lookaheads_len);

#पूर्ण_अगर
