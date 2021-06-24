<शैली गुरु>
/*
 * Copyright (c) 2004-2011 Atheros Communications Inc.
 * Copyright (c) 2011 Qualcomm Atheros, Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित HTC_H
#घोषणा HTC_H

#समावेश "common.h"

/* frame header flags */

/* send direction */
#घोषणा HTC_FLAGS_NEED_CREDIT_UPDATE (1 << 0)
#घोषणा HTC_FLAGS_SEND_BUNDLE        (1 << 1)
#घोषणा HTC_FLAGS_TX_FIXUP_NETBUF    (1 << 2)

/* receive direction */
#घोषणा HTC_FLG_RX_UNUSED        (1 << 0)
#घोषणा HTC_FLG_RX_TRAILER       (1 << 1)
/* Bundle count maske and shअगरt */
#घोषणा HTC_FLG_RX_BNDL_CNT	 (0xF0)
#घोषणा HTC_FLG_RX_BNDL_CNT_S	 4

#घोषणा HTC_HDR_LENGTH  (माप(काष्ठा htc_frame_hdr))
#घोषणा HTC_MAX_PAYLOAD_LENGTH   (4096 - माप(काष्ठा htc_frame_hdr))

/* HTC control message IDs */

#घोषणा HTC_MSG_READY_ID		1
#घोषणा HTC_MSG_CONN_SVC_ID		2
#घोषणा HTC_MSG_CONN_SVC_RESP_ID	3
#घोषणा HTC_MSG_SETUP_COMPLETE_ID	4
#घोषणा HTC_MSG_SETUP_COMPLETE_EX_ID	5

#घोषणा HTC_MAX_CTRL_MSG_LEN  256

#घोषणा HTC_VERSION_2P0  0x00
#घोषणा HTC_VERSION_2P1  0x01

#घोषणा HTC_SERVICE_META_DATA_MAX_LENGTH 128

#घोषणा HTC_CONN_FLGS_THRESH_LVL_QUAT		0x0
#घोषणा HTC_CONN_FLGS_THRESH_LVL_HALF		0x1
#घोषणा HTC_CONN_FLGS_THRESH_LVL_THREE_QUAT	0x2
#घोषणा HTC_CONN_FLGS_REDUCE_CRED_DRIB		0x4
#घोषणा HTC_CONN_FLGS_THRESH_MASK		0x3
/* disable credit flow control on a specअगरic service */
#घोषणा HTC_CONN_FLGS_DISABLE_CRED_FLOW_CTRL          (1 << 3)
#घोषणा HTC_CONN_FLGS_SET_RECV_ALLOC_SHIFT    8
#घोषणा HTC_CONN_FLGS_SET_RECV_ALLOC_MASK     0xFF00U

/* connect response status codes */
#घोषणा HTC_SERVICE_SUCCESS      0
#घोषणा HTC_SERVICE_NOT_FOUND    1
#घोषणा HTC_SERVICE_FAILED       2

/* no resources (i.e. no more endpoपूर्णांकs) */
#घोषणा HTC_SERVICE_NO_RESOURCES 3

/* specअगरic service is not allowing any more endpoपूर्णांकs */
#घोषणा HTC_SERVICE_NO_MORE_EP   4

/* report record IDs */
#घोषणा HTC_RECORD_शून्य             0
#घोषणा HTC_RECORD_CREDITS          1
#घोषणा HTC_RECORD_LOOKAHEAD        2
#घोषणा HTC_RECORD_LOOKAHEAD_BUNDLE 3

#घोषणा HTC_SETUP_COMP_FLG_RX_BNDL_EN     (1 << 0)
#घोषणा HTC_SETUP_COMP_FLG_DISABLE_TX_CREDIT_FLOW (1 << 1)

#घोषणा MAKE_SERVICE_ID(group, index) \
	(पूर्णांक)(((पूर्णांक)group << 8) | (पूर्णांक)(index))

/* NOTE: service ID of 0x0000 is reserved and should never be used */
#घोषणा HTC_CTRL_RSVD_SVC MAKE_SERVICE_ID(RSVD_SERVICE_GROUP, 1)
#घोषणा WMI_CONTROL_SVC   MAKE_SERVICE_ID(WMI_SERVICE_GROUP, 0)
#घोषणा WMI_DATA_BE_SVC   MAKE_SERVICE_ID(WMI_SERVICE_GROUP, 1)
#घोषणा WMI_DATA_BK_SVC   MAKE_SERVICE_ID(WMI_SERVICE_GROUP, 2)
#घोषणा WMI_DATA_VI_SVC   MAKE_SERVICE_ID(WMI_SERVICE_GROUP, 3)
#घोषणा WMI_DATA_VO_SVC   MAKE_SERVICE_ID(WMI_SERVICE_GROUP, 4)
#घोषणा WMI_MAX_SERVICES  5

#घोषणा WMM_NUM_AC  4

/* reserved and used to flush ALL packets */
#घोषणा HTC_TX_PACKET_TAG_ALL          0
#घोषणा HTC_SERVICE_TX_PACKET_TAG      1
#घोषणा HTC_TX_PACKET_TAG_USER_DEFINED (HTC_SERVICE_TX_PACKET_TAG + 9)

/* more packets on this endpoपूर्णांक are being fetched */
#घोषणा HTC_RX_FLAGS_INDICATE_MORE_PKTS  (1 << 0)

/* TODO.. क्रम BMI */
#घोषणा ENDPOINT1 0
/* TODO -हटाओ me, but we have to fix BMI first */
#घोषणा HTC_MAILBOX_NUM_MAX    4

/* enable send bundle padding क्रम this endpoपूर्णांक */
#घोषणा HTC_FLGS_TX_BNDL_PAD_EN	 (1 << 0)
#घोषणा HTC_EP_ACTIVE                            ((u32) (1u << 31))

/* HTC operational parameters */
#घोषणा HTC_TARGET_RESPONSE_TIMEOUT        2000	/* in ms */
#घोषणा HTC_TARGET_RESPONSE_POLL_WAIT      10
#घोषणा HTC_TARGET_RESPONSE_POLL_COUNT     200
#घोषणा HTC_TARGET_DEBUG_INTR_MASK         0x01
#घोषणा HTC_TARGET_CREDIT_INTR_MASK        0xF0

#घोषणा HTC_HOST_MAX_MSG_PER_BUNDLE        8
#घोषणा HTC_MIN_HTC_MSGS_TO_BUNDLE         2

/* packet flags */

#घोषणा HTC_RX_PKT_IGNORE_LOOKAHEAD      (1 << 0)
#घोषणा HTC_RX_PKT_REFRESH_HDR           (1 << 1)
#घोषणा HTC_RX_PKT_PART_OF_BUNDLE        (1 << 2)
#घोषणा HTC_RX_PKT_NO_RECYCLE            (1 << 3)

#घोषणा NUM_CONTROL_BUFFERS     8
#घोषणा NUM_CONTROL_TX_BUFFERS  2
#घोषणा NUM_CONTROL_RX_BUFFERS  (NUM_CONTROL_BUFFERS - NUM_CONTROL_TX_BUFFERS)

#घोषणा HTC_RECV_WAIT_BUFFERS        (1 << 0)
#घोषणा HTC_OP_STATE_STOPPING        (1 << 0)
#घोषणा HTC_OP_STATE_SETUP_COMPLETE  (1 << 1)

/*
 * The frame header length and message क्रमmats defined herein were selected
 * to accommodate optimal alignment क्रम target processing. This reduces
 * code size and improves perक्रमmance. Any changes to the header length may
 * alter the alignment and cause exceptions on the target. When adding to
 * the messageकाष्ठाures insure that fields are properly aligned.
 */

/* HTC frame header
 *
 * NOTE: करो not हटाओ or re-arrange the fields, these are minimally
 * required to take advantage of 4-byte lookaheads in some hardware
 * implementations.
 */
काष्ठा htc_frame_hdr अणु
	u8 eid;
	u8 flags;

	/* length of data (including trailer) that follows the header */
	__le16 payld_len;

	/* end of 4-byte lookahead */

	u8 ctrl[2];
पूर्ण __packed;

/* HTC पढ़ोy message */
काष्ठा htc_पढ़ोy_msg अणु
	__le16 msg_id;
	__le16 cred_cnt;
	__le16 cred_sz;
	u8 max_ep;
	u8 pad;
पूर्ण __packed;

/* extended HTC पढ़ोy message */
काष्ठा htc_पढ़ोy_ext_msg अणु
	काष्ठा htc_पढ़ोy_msg ver2_0_info;
	u8 htc_ver;
	u8 msg_per_htc_bndl;
पूर्ण __packed;

/* connect service */
काष्ठा htc_conn_service_msg अणु
	__le16 msg_id;
	__le16 svc_id;
	__le16 conn_flags;
	u8 svc_meta_len;
	u8 pad;
पूर्ण __packed;

/* connect response */
काष्ठा htc_conn_service_resp अणु
	__le16 msg_id;
	__le16 svc_id;
	u8 status;
	u8 eid;
	__le16 max_msg_sz;
	u8 svc_meta_len;
	u8 pad;
पूर्ण __packed;

काष्ठा htc_setup_comp_msg अणु
	__le16 msg_id;
पूर्ण __packed;

/* extended setup completion message */
काष्ठा htc_setup_comp_ext_msg अणु
	__le16 msg_id;
	__le32 flags;
	u8 msg_per_rxbndl;
	u8 Rsvd[3];
पूर्ण __packed;

काष्ठा htc_record_hdr अणु
	u8 rec_id;
	u8 len;
पूर्ण __packed;

काष्ठा htc_credit_report अणु
	u8 eid;
	u8 credits;
पूर्ण __packed;

/*
 * NOTE: The lk_ahd array is guarded by a pre_valid
 * and Post Valid guard bytes. The pre_valid bytes must
 * equal the inverse of the post_valid byte.
 */
काष्ठा htc_lookahead_report अणु
	u8 pre_valid;
	u8 lk_ahd[4];
	u8 post_valid;
पूर्ण __packed;

काष्ठा htc_bundle_lkahd_rpt अणु
	u8 lk_ahd[4];
पूर्ण __packed;

/* Current service IDs */

क्रमागत htc_service_grp_ids अणु
	RSVD_SERVICE_GROUP = 0,
	WMI_SERVICE_GROUP = 1,

	HTC_TEST_GROUP = 254,
	HTC_SERVICE_GROUP_LAST = 255
पूर्ण;

/* ------ endpoपूर्णांक IDS ------ */

क्रमागत htc_endpoपूर्णांक_id अणु
	ENDPOINT_UNUSED = -1,
	ENDPOINT_0 = 0,
	ENDPOINT_1 = 1,
	ENDPOINT_2 = 2,
	ENDPOINT_3,
	ENDPOINT_4,
	ENDPOINT_5,
	ENDPOINT_6,
	ENDPOINT_7,
	ENDPOINT_8,
	ENDPOपूर्णांक_उच्च,
पूर्ण;

काष्ठा htc_tx_packet_info अणु
	u16 tag;
	पूर्णांक cred_used;
	u8 flags;
	पूर्णांक seqno;
पूर्ण;

काष्ठा htc_rx_packet_info अणु
	u32 exp_hdr;
	u32 rx_flags;
	u32 indicat_flags;
पूर्ण;

काष्ठा htc_target;

/* wrapper around endpoपूर्णांक-specअगरic packets */
काष्ठा htc_packet अणु
	काष्ठा list_head list;

	/* caller's per packet specअगरic context */
	व्योम *pkt_cntxt;

	/*
	 * the true buffer start , the caller can store the real
	 * buffer start here.  In receive callbacks, the HTC layer
	 * sets buf to the start of the payload past the header.
	 * This field allows the caller to reset buf when it recycles
	 * receive packets back to HTC.
	 */
	u8 *buf_start;

	/*
	 * Poपूर्णांकer to the start of the buffer. In the transmit
	 * direction this poपूर्णांकs to the start of the payload. In the
	 * receive direction, however, the buffer when queued up
	 * poपूर्णांकs to the start of the HTC header but when वापसed
	 * to the caller poपूर्णांकs to the start of the payload
	 */
	u8 *buf;
	u32 buf_len;

	/* actual length of payload */
	u32 act_len;

	/* endpoपूर्णांक that this packet was sent/recv'd from */
	क्रमागत htc_endpoपूर्णांक_id endpoपूर्णांक;

	/* completion status */

	पूर्णांक status;
	जोड़ अणु
		काष्ठा htc_tx_packet_info tx;
		काष्ठा htc_rx_packet_info rx;
	पूर्ण info;

	व्योम (*completion) (काष्ठा htc_target *, काष्ठा htc_packet *);
	काष्ठा htc_target *context;

	/*
	 * optimization क्रम network-oriented data, the HTC packet
	 * can pass the network buffer corresponding to the HTC packet
	 * lower layers may optimized the transfer knowing this is
	 * a network buffer
	 */
	काष्ठा sk_buff *skb;
पूर्ण;

क्रमागत htc_send_full_action अणु
	HTC_SEND_FULL_KEEP = 0,
	HTC_SEND_FULL_DROP = 1,
पूर्ण;

काष्ठा htc_ep_callbacks अणु
	व्योम (*tx_complete) (काष्ठा htc_target *, काष्ठा htc_packet *);
	व्योम (*rx) (काष्ठा htc_target *, काष्ठा htc_packet *);
	व्योम (*rx_refill) (काष्ठा htc_target *, क्रमागत htc_endpoपूर्णांक_id endpoपूर्णांक);
	क्रमागत htc_send_full_action (*tx_full) (काष्ठा htc_target *,
					      काष्ठा htc_packet *);
	काष्ठा htc_packet *(*rx_allocthresh) (काष्ठा htc_target *,
					      क्रमागत htc_endpoपूर्णांक_id, पूर्णांक);
	व्योम (*tx_comp_multi) (काष्ठा htc_target *, काष्ठा list_head *);
	पूर्णांक rx_alloc_thresh;
	पूर्णांक rx_refill_thresh;
पूर्ण;

/* service connection inक्रमmation */
काष्ठा htc_service_connect_req अणु
	u16 svc_id;
	u16 conn_flags;
	काष्ठा htc_ep_callbacks ep_cb;
	पूर्णांक max_txq_depth;
	u32 flags;
	अचिन्हित पूर्णांक max_rxmsg_sz;
पूर्ण;

/* service connection response inक्रमmation */
काष्ठा htc_service_connect_resp अणु
	u8 buf_len;
	u8 act_len;
	क्रमागत htc_endpoपूर्णांक_id endpoपूर्णांक;
	अचिन्हित पूर्णांक len_max;
	u8 resp_code;
पूर्ण;

/* endpoपूर्णांक distributionकाष्ठाure */
काष्ठा htc_endpoपूर्णांक_credit_dist अणु
	काष्ठा list_head list;

	/* Service ID (set by HTC) */
	u16 svc_id;

	/* endpoपूर्णांक क्रम this distributionकाष्ठा (set by HTC) */
	क्रमागत htc_endpoपूर्णांक_id endpoपूर्णांक;

	u32 dist_flags;

	/*
	 * credits क्रम normal operation, anything above this
	 * indicates the endpoपूर्णांक is over-subscribed.
	 */
	पूर्णांक cred_norm;

	/* न्यूनमान क्रम credit distribution */
	पूर्णांक cred_min;

	पूर्णांक cred_assngd;

	/* current credits available */
	पूर्णांक credits;

	/*
	 * pending credits to distribute on this endpoपूर्णांक, this
	 * is set by HTC when credit reports arrive.  The credit
	 * distribution functions sets this to zero when it distributes
	 * the credits.
	 */
	पूर्णांक cred_to_dist;

	/*
	 * the number of credits that the current pending TX packet needs
	 * to transmit. This is set by HTC when endpoपूर्णांक needs credits in
	 * order to transmit.
	 */
	पूर्णांक seek_cred;

	/* size in bytes of each credit */
	पूर्णांक cred_sz;

	/* credits required क्रम a maximum sized messages */
	पूर्णांक cred_per_msg;

	/* reserved क्रम HTC use */
	काष्ठा htc_endpoपूर्णांक *htc_ep;

	/*
	 * current depth of TX queue , i.e. messages रुकोing क्रम credits
	 * This field is valid only when HTC_CREDIT_DIST_ACTIVITY_CHANGE
	 * or HTC_CREDIT_DIST_SEND_COMPLETE is indicated on an endpoपूर्णांक
	 * that has non-zero credits to recover.
	 */
	पूर्णांक txq_depth;
पूर्ण;

/*
 * credit distribution code that is passed पूर्णांकo the distribution function,
 * there are mandatory and optional codes that must be handled
 */
क्रमागत htc_credit_dist_reason अणु
	HTC_CREDIT_DIST_SEND_COMPLETE = 0,
	HTC_CREDIT_DIST_ACTIVITY_CHANGE = 1,
	HTC_CREDIT_DIST_SEEK_CREDITS,
पूर्ण;

काष्ठा ath6kl_htc_credit_info अणु
	पूर्णांक total_avail_credits;
	पूर्णांक cur_मुक्त_credits;

	/* list of lowest priority endpoपूर्णांकs */
	काष्ठा list_head lowestpri_ep_dist;
पूर्ण;

/* endpoपूर्णांक statistics */
काष्ठा htc_endpoपूर्णांक_stats अणु
	/*
	 * number of बार the host set the credit-low flag in a send
	 * message on this endpoपूर्णांक
	 */
	u32 cred_low_indicate;

	u32 tx_issued;
	u32 tx_pkt_bundled;
	u32 tx_bundles;
	u32 tx_dropped;

	/* running count of total credit reports received क्रम this endpoपूर्णांक */
	u32 tx_cred_rpt;

	/* credit reports received from this endpoपूर्णांक's RX packets */
	u32 cred_rpt_from_rx;

	/* credit reports received from RX packets of other endpoपूर्णांकs */
	u32 cred_rpt_from_other;

	/* credit reports received from endpoपूर्णांक 0 RX packets */
	u32 cred_rpt_ep0;

	/* count of credits received via Rx packets on this endpoपूर्णांक */
	u32 cred_from_rx;

	/* count of credits received via another endpoपूर्णांक */
	u32 cred_from_other;

	/* count of credits received via another endpoपूर्णांक */
	u32 cred_from_ep0;

	/* count of consummed credits */
	u32 cred_cosumd;

	/* count of credits वापसed */
	u32 cred_retnd;

	u32 rx_pkts;

	/* count of lookahead records found in Rx msg */
	u32 rx_lkahds;

	/* count of recv packets received in a bundle */
	u32 rx_bundl;

	/* count of number of bundled lookaheads */
	u32 rx_bundle_lkahd;

	/* count of the number of bundle indications from the HTC header */
	u32 rx_bundle_from_hdr;

	/* the number of बार the recv allocation threshold was hit */
	u32 rx_alloc_thresh_hit;

	/* total number of bytes */
	u32 rxalloc_thresh_byte;
पूर्ण;

काष्ठा htc_endpoपूर्णांक अणु
	क्रमागत htc_endpoपूर्णांक_id eid;
	u16 svc_id;
	काष्ठा list_head txq;
	काष्ठा list_head rx_bufq;
	काष्ठा htc_endpoपूर्णांक_credit_dist cred_dist;
	काष्ठा htc_ep_callbacks ep_cb;
	पूर्णांक max_txq_depth;
	पूर्णांक len_max;
	पूर्णांक tx_proc_cnt;
	पूर्णांक rx_proc_cnt;
	काष्ठा htc_target *target;
	u8 seqno;
	u32 conn_flags;
	काष्ठा htc_endpoपूर्णांक_stats ep_st;
	u16 tx_drop_packet_threshold;

	काष्ठा अणु
		u8 pipeid_ul;
		u8 pipeid_dl;
		काष्ठा list_head tx_lookup_queue;
		bool tx_credit_flow_enabled;
	पूर्ण pipe;
पूर्ण;

काष्ठा htc_control_buffer अणु
	काष्ठा htc_packet packet;
	u8 *buf;
पूर्ण;

काष्ठा htc_pipe_txcredit_alloc अणु
	u16 service_id;
	u8 credit_alloc;
पूर्ण;

क्रमागत htc_send_queue_result अणु
	HTC_SEND_QUEUE_OK = 0,	/* packet was queued */
	HTC_SEND_QUEUE_DROP = 1,	/* this packet should be dropped */
पूर्ण;

काष्ठा ath6kl_htc_ops अणु
	व्योम* (*create)(काष्ठा ath6kl *ar);
	पूर्णांक (*रुको_target)(काष्ठा htc_target *target);
	पूर्णांक (*start)(काष्ठा htc_target *target);
	पूर्णांक (*conn_service)(काष्ठा htc_target *target,
			    काष्ठा htc_service_connect_req *req,
			    काष्ठा htc_service_connect_resp *resp);
	पूर्णांक  (*tx)(काष्ठा htc_target *target, काष्ठा htc_packet *packet);
	व्योम (*stop)(काष्ठा htc_target *target);
	व्योम (*cleanup)(काष्ठा htc_target *target);
	व्योम (*flush_txep)(काष्ठा htc_target *target,
			   क्रमागत htc_endpoपूर्णांक_id endpoपूर्णांक, u16 tag);
	व्योम (*flush_rx_buf)(काष्ठा htc_target *target);
	व्योम (*activity_changed)(काष्ठा htc_target *target,
				 क्रमागत htc_endpoपूर्णांक_id endpoपूर्णांक,
				 bool active);
	पूर्णांक (*get_rxbuf_num)(काष्ठा htc_target *target,
			     क्रमागत htc_endpoपूर्णांक_id endpoपूर्णांक);
	पूर्णांक (*add_rxbuf_multiple)(काष्ठा htc_target *target,
				  काष्ठा list_head *pktq);
	पूर्णांक (*credit_setup)(काष्ठा htc_target *target,
			    काष्ठा ath6kl_htc_credit_info *cred_info);
	पूर्णांक (*tx_complete)(काष्ठा ath6kl *ar, काष्ठा sk_buff *skb);
	पूर्णांक (*rx_complete)(काष्ठा ath6kl *ar, काष्ठा sk_buff *skb, u8 pipe);
पूर्ण;

काष्ठा ath6kl_device;

/* our HTC target state */
काष्ठा htc_target अणु
	काष्ठा htc_endpoपूर्णांक endpoपूर्णांक[ENDPOपूर्णांक_उच्च];

	/* contains काष्ठा htc_endpoपूर्णांक_credit_dist */
	काष्ठा list_head cred_dist_list;

	काष्ठा list_head मुक्त_ctrl_txbuf;
	काष्ठा list_head मुक्त_ctrl_rxbuf;
	काष्ठा ath6kl_htc_credit_info *credit_info;
	पूर्णांक tgt_creds;
	अचिन्हित पूर्णांक tgt_cred_sz;

	/* protects मुक्त_ctrl_txbuf and मुक्त_ctrl_rxbuf */
	spinlock_t htc_lock;

	/* FIXME: करोes this protext rx_bufq and endpoपूर्णांक काष्ठाures or what? */
	spinlock_t rx_lock;

	/* protects endpoपूर्णांक->txq */
	spinlock_t tx_lock;

	काष्ठा ath6kl_device *dev;
	u32 htc_flags;
	u32 rx_st_flags;
	क्रमागत htc_endpoपूर्णांक_id ep_रुकोing;
	u8 htc_tgt_ver;

	/* max messages per bundle क्रम HTC */
	पूर्णांक msg_per_bndl_max;

	u32 tx_bndl_mask;
	पूर्णांक rx_bndl_enable;
	पूर्णांक max_rx_bndl_sz;
	पूर्णांक max_tx_bndl_sz;

	u32 block_sz;
	u32 block_mask;

	पूर्णांक max_scat_entries;
	पूर्णांक max_xfer_szper_scatreq;

	पूर्णांक chk_irq_status_cnt;

	/* counts the number of Tx without bundling continously per AC */
	u32 ac_tx_count[WMM_NUM_AC];

	काष्ठा अणु
		काष्ठा htc_packet *htc_packet_pool;
		u8 ctrl_response_buf[HTC_MAX_CTRL_MSG_LEN];
		पूर्णांक ctrl_response_len;
		bool ctrl_response_valid;
		काष्ठा htc_pipe_txcredit_alloc txcredit_alloc[ENDPOपूर्णांक_उच्च];
	पूर्ण pipe;
पूर्ण;

पूर्णांक ath6kl_htc_rxmsg_pending_handler(काष्ठा htc_target *target,
				     u32 msg_look_ahead, पूर्णांक *n_pkts);

अटल अंतरभूत व्योम set_htc_pkt_info(काष्ठा htc_packet *packet, व्योम *context,
				    u8 *buf, अचिन्हित पूर्णांक len,
				    क्रमागत htc_endpoपूर्णांक_id eid, u16 tag)
अणु
	packet->pkt_cntxt = context;
	packet->buf = buf;
	packet->act_len = len;
	packet->endpoपूर्णांक = eid;
	packet->info.tx.tag = tag;
पूर्ण

अटल अंतरभूत व्योम htc_rxpkt_reset(काष्ठा htc_packet *packet)
अणु
	packet->buf = packet->buf_start;
	packet->act_len = 0;
पूर्ण

अटल अंतरभूत व्योम set_htc_rxpkt_info(काष्ठा htc_packet *packet, व्योम *context,
				      u8 *buf, अचिन्हित दीर्घ len,
				      क्रमागत htc_endpoपूर्णांक_id eid)
अणु
	packet->pkt_cntxt = context;
	packet->buf = buf;
	packet->buf_start = buf;
	packet->buf_len = len;
	packet->endpoपूर्णांक = eid;
पूर्ण

अटल अंतरभूत पूर्णांक get_queue_depth(काष्ठा list_head *queue)
अणु
	काष्ठा list_head *पंचांगp_list;
	पूर्णांक depth = 0;

	list_क्रम_each(पंचांगp_list, queue)
	    depth++;

	वापस depth;
पूर्ण

व्योम ath6kl_htc_pipe_attach(काष्ठा ath6kl *ar);
व्योम ath6kl_htc_mbox_attach(काष्ठा ath6kl *ar);

#पूर्ण_अगर
