<शैली गुरु>
/*
 * Copyright (c) 2010-2011 Atheros Communications Inc.
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

#अगर_अघोषित HTC_HST_H
#घोषणा HTC_HST_H

काष्ठा ath9k_htc_priv;
काष्ठा htc_target;
काष्ठा ath9k_htc_tx_ctl;

क्रमागत ath9k_hअगर_transports अणु
	ATH9K_HIF_USB,
पूर्ण;

काष्ठा ath9k_htc_hअगर अणु
	काष्ठा list_head list;
	स्थिर क्रमागत ath9k_hअगर_transports transport;
	स्थिर अक्षर *name;

	u8 control_dl_pipe;
	u8 control_ul_pipe;

	व्योम (*start) (व्योम *hअगर_handle);
	व्योम (*stop) (व्योम *hअगर_handle);
	व्योम (*sta_drain) (व्योम *hअगर_handle, u8 idx);
	पूर्णांक (*send) (व्योम *hअगर_handle, u8 pipe, काष्ठा sk_buff *buf);
पूर्ण;

क्रमागत htc_endpoपूर्णांक_id अणु
	ENDPOINT_UNUSED = -1,
	ENDPOINT0 = 0,
	ENDPOINT1 = 1,
	ENDPOINT2 = 2,
	ENDPOINT3 = 3,
	ENDPOINT4 = 4,
	ENDPOINT5 = 5,
	ENDPOINT6 = 6,
	ENDPOINT7 = 7,
	ENDPOINT8 = 8,
	ENDPOपूर्णांक_उच्च = 22
पूर्ण;

/* Htc frame hdr flags */
#घोषणा HTC_FLAGS_RECV_TRAILER (1 << 1)

काष्ठा htc_frame_hdr अणु
	u8 endpoपूर्णांक_id;
	u8 flags;
	__be16 payload_len;
	u8 control[4];
पूर्ण __packed;

काष्ठा htc_पढ़ोy_msg अणु
	__be16 message_id;
	__be16 credits;
	__be16 credit_size;
	u8 max_endpoपूर्णांकs;
	u8 pad;
पूर्ण __packed;

काष्ठा htc_config_pipe_msg अणु
	__be16 message_id;
	u8 pipe_id;
	u8 credits;
पूर्ण __packed;

काष्ठा htc_panic_bad_vaddr अणु
	__be32 pattern;
	__be32 exccause;
	__be32 pc;
	__be32 badvaddr;
पूर्ण __packed;

काष्ठा htc_panic_bad_epid अणु
	__be32 pattern;
	__be32 epid;
पूर्ण __packed;

काष्ठा htc_ep_callbacks अणु
	व्योम *priv;
	व्योम (*tx) (व्योम *, काष्ठा sk_buff *, क्रमागत htc_endpoपूर्णांक_id, bool txok);
	व्योम (*rx) (व्योम *, काष्ठा sk_buff *, क्रमागत htc_endpoपूर्णांक_id);
पूर्ण;

काष्ठा htc_endpoपूर्णांक अणु
	u16 service_id;

	काष्ठा htc_ep_callbacks ep_callbacks;
	u32 max_txqdepth;
	पूर्णांक max_msglen;

	u8 ul_pipeid;
	u8 dl_pipeid;
पूर्ण;

#घोषणा HTC_MAX_CONTROL_MESSAGE_LENGTH 255
#घोषणा HTC_CONTROL_BUFFER_SIZE	\
	(HTC_MAX_CONTROL_MESSAGE_LENGTH + माप(काष्ठा htc_frame_hdr))

#घोषणा HTC_OP_START_WAIT           BIT(0)
#घोषणा HTC_OP_CONFIG_PIPE_CREDITS  BIT(1)

काष्ठा htc_target अणु
	व्योम *hअगर_dev;
	काष्ठा ath9k_htc_priv *drv_priv;
	काष्ठा device *dev;
	काष्ठा ath9k_htc_hअगर *hअगर;
	काष्ठा htc_endpoपूर्णांक endpoपूर्णांक[ENDPOपूर्णांक_उच्च];
	काष्ठा completion target_रुको;
	काष्ठा completion cmd_रुको;
	काष्ठा list_head list;
	क्रमागत htc_endpoपूर्णांक_id conn_rsp_epid;
	u16 credits;
	u16 credit_size;
	u8 htc_flags;
	atomic_t tgt_पढ़ोy;
पूर्ण;

क्रमागत htc_msg_id अणु
	HTC_MSG_READY_ID = 1,
	HTC_MSG_CONNECT_SERVICE_ID,
	HTC_MSG_CONNECT_SERVICE_RESPONSE_ID,
	HTC_MSG_SETUP_COMPLETE_ID,
	HTC_MSG_CONFIG_PIPE_ID,
	HTC_MSG_CONFIG_PIPE_RESPONSE_ID,
पूर्ण;

काष्ठा htc_service_connreq अणु
	u16 service_id;
	u16 con_flags;
	u32 max_send_qdepth;
	काष्ठा htc_ep_callbacks ep_callbacks;
पूर्ण;

/* Current service IDs */

क्रमागत htc_service_group_idsअणु
	RSVD_SERVICE_GROUP = 0,
	WMI_SERVICE_GROUP = 1,

	HTC_SERVICE_GROUP_LAST = 255
पूर्ण;

#घोषणा MAKE_SERVICE_ID(group, index)		\
	(पूर्णांक)(((पूर्णांक)group << 8) | (पूर्णांक)(index))

/* NOTE: service ID of 0x0000 is reserved and should never be used */
#घोषणा HTC_CTRL_RSVD_SVC MAKE_SERVICE_ID(RSVD_SERVICE_GROUP, 1)
#घोषणा HTC_LOOPBACK_RSVD_SVC MAKE_SERVICE_ID(RSVD_SERVICE_GROUP, 2)

#घोषणा WMI_CONTROL_SVC   MAKE_SERVICE_ID(WMI_SERVICE_GROUP, 0)
#घोषणा WMI_BEACON_SVC	  MAKE_SERVICE_ID(WMI_SERVICE_GROUP, 1)
#घोषणा WMI_CAB_SVC	  MAKE_SERVICE_ID(WMI_SERVICE_GROUP, 2)
#घोषणा WMI_UAPSD_SVC	  MAKE_SERVICE_ID(WMI_SERVICE_GROUP, 3)
#घोषणा WMI_MGMT_SVC	  MAKE_SERVICE_ID(WMI_SERVICE_GROUP, 4)
#घोषणा WMI_DATA_VO_SVC   MAKE_SERVICE_ID(WMI_SERVICE_GROUP, 5)
#घोषणा WMI_DATA_VI_SVC   MAKE_SERVICE_ID(WMI_SERVICE_GROUP, 6)
#घोषणा WMI_DATA_BE_SVC   MAKE_SERVICE_ID(WMI_SERVICE_GROUP, 7)
#घोषणा WMI_DATA_BK_SVC   MAKE_SERVICE_ID(WMI_SERVICE_GROUP, 8)

काष्ठा htc_conn_svc_msg अणु
	__be16 msg_id;
	__be16 service_id;
	__be16 con_flags;
	u8 dl_pipeid;
	u8 ul_pipeid;
	u8 svc_meta_len;
	u8 pad;
पूर्ण __packed;

/* connect response status codes */
#घोषणा HTC_SERVICE_SUCCESS      0
#घोषणा HTC_SERVICE_NOT_FOUND    1
#घोषणा HTC_SERVICE_FAILED       2
#घोषणा HTC_SERVICE_NO_RESOURCES 3
#घोषणा HTC_SERVICE_NO_MORE_EP   4

काष्ठा htc_conn_svc_rspmsg अणु
	__be16 msg_id;
	__be16 service_id;
	u8 status;
	u8 endpoपूर्णांक_id;
	__be16 max_msg_len;
	u8 svc_meta_len;
	u8 pad;
पूर्ण __packed;

काष्ठा htc_comp_msg अणु
	__be16 msg_id;
पूर्ण __packed;

पूर्णांक htc_init(काष्ठा htc_target *target);
पूर्णांक htc_connect_service(काष्ठा htc_target *target,
			  काष्ठा htc_service_connreq *service_connreq,
			  क्रमागत htc_endpoपूर्णांक_id *conn_rsp_eid);
पूर्णांक htc_send(काष्ठा htc_target *target, काष्ठा sk_buff *skb);
पूर्णांक htc_send_epid(काष्ठा htc_target *target, काष्ठा sk_buff *skb,
		  क्रमागत htc_endpoपूर्णांक_id epid);
व्योम htc_stop(काष्ठा htc_target *target);
व्योम htc_start(काष्ठा htc_target *target);
व्योम htc_sta_drain(काष्ठा htc_target *target, u8 idx);

व्योम ath9k_htc_rx_msg(काष्ठा htc_target *htc_handle,
		      काष्ठा sk_buff *skb, u32 len, u8 pipe_id);
व्योम ath9k_htc_txcompletion_cb(काष्ठा htc_target *htc_handle,
			       काष्ठा sk_buff *skb, bool txok);

काष्ठा htc_target *ath9k_htc_hw_alloc(व्योम *hअगर_handle,
				      काष्ठा ath9k_htc_hअगर *hअगर,
				      काष्ठा device *dev);
व्योम ath9k_htc_hw_मुक्त(काष्ठा htc_target *htc);
पूर्णांक ath9k_htc_hw_init(काष्ठा htc_target *target,
		      काष्ठा device *dev, u16 devid, अक्षर *product,
		      u32 drv_info);
व्योम ath9k_htc_hw_deinit(काष्ठा htc_target *target, bool hot_unplug);

#पूर्ण_अगर /* HTC_HST_H */
