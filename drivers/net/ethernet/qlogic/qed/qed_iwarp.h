<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#अगर_अघोषित _QED_IWARP_H
#घोषणा _QED_IWARP_H

क्रमागत qed_iwarp_qp_state अणु
	QED_IWARP_QP_STATE_IDLE,
	QED_IWARP_QP_STATE_RTS,
	QED_IWARP_QP_STATE_TERMINATE,
	QED_IWARP_QP_STATE_CLOSING,
	QED_IWARP_QP_STATE_ERROR,
पूर्ण;

क्रमागत qed_iwarp_qp_state qed_roce2iwarp_state(क्रमागत qed_roce_qp_state state);

#घोषणा QED_IWARP_PREALLOC_CNT  (256)

#घोषणा QED_IWARP_LL2_SYN_TX_SIZE       (128)
#घोषणा QED_IWARP_LL2_SYN_RX_SIZE       (256)

#घोषणा QED_IWARP_LL2_OOO_DEF_TX_SIZE   (256)
#घोषणा QED_IWARP_MAX_OOO		(16)
#घोषणा QED_IWARP_LL2_OOO_MAX_RX_SIZE   (16384)

#घोषणा QED_IWARP_HANDLE_INVAL		(0xff)

काष्ठा qed_iwarp_ll2_buff अणु
	काष्ठा qed_iwarp_ll2_buff *piggy_buf;
	व्योम *data;
	dma_addr_t data_phys_addr;
	u32 buff_size;
पूर्ण;

काष्ठा qed_iwarp_ll2_mpa_buf अणु
	काष्ठा list_head list_entry;
	काष्ठा qed_iwarp_ll2_buff *ll2_buf;
	काष्ठा unaligned_opaque_data data;
	u16 tcp_payload_len;
	u8 placement_offset;
पूर्ण;

/* In some हालs a fpdu will arrive with only one byte of the header, in this
 * हाल the fpdu_length will be partial (contain only higher byte and
 * incomplete bytes will contain the invalid value
 */
#घोषणा QED_IWARP_INVALID_INCOMPLETE_BYTES 0xffff

काष्ठा qed_iwarp_fpdu अणु
	काष्ठा qed_iwarp_ll2_buff *mpa_buf;
	व्योम *mpa_frag_virt;
	dma_addr_t mpa_frag;
	dma_addr_t pkt_hdr;
	u16 mpa_frag_len;
	u16 fpdu_length;
	u16 incomplete_bytes;
	u8 pkt_hdr_size;
पूर्ण;

काष्ठा qed_iwarp_info अणु
	काष्ठा list_head listen_list;	/* qed_iwarp_listener */
	काष्ठा list_head ep_list;	/* qed_iwarp_ep */
	काष्ठा list_head ep_मुक्त_list;	/* pre-allocated ep's */
	काष्ठा list_head mpa_buf_list;	/* list of mpa_bufs */
	काष्ठा list_head mpa_buf_pending_list;
	spinlock_t iw_lock;	/* क्रम iwarp resources */
	spinlock_t qp_lock;	/* क्रम tearकरोwn races */
	u32 rcv_wnd_scale;
	u16 rcv_wnd_size;
	u16 max_mtu;
	u8 mac_addr[ETH_ALEN];
	u8 crc_needed;
	u8 tcp_flags;
	u8 ll2_syn_handle;
	u8 ll2_ooo_handle;
	u8 ll2_mpa_handle;
	u8 peer2peer;
	क्रमागत mpa_negotiation_mode mpa_rev;
	क्रमागत mpa_rtr_type rtr_type;
	काष्ठा qed_iwarp_fpdu *partial_fpdus;
	काष्ठा qed_iwarp_ll2_mpa_buf *mpa_bufs;
	u8 *mpa_पूर्णांकermediate_buf;
	u16 max_num_partial_fpdus;
पूर्ण;

क्रमागत qed_iwarp_ep_state अणु
	QED_IWARP_EP_INIT,
	QED_IWARP_EP_MPA_REQ_RCVD,
	QED_IWARP_EP_MPA_OFFLOADED,
	QED_IWARP_EP_ESTABLISHED,
	QED_IWARP_EP_CLOSED
पूर्ण;

जोड़ async_output अणु
	काष्ठा iwarp_eqe_data_mpa_async_completion mpa_response;
	काष्ठा iwarp_eqe_data_tcp_async_completion mpa_request;
पूर्ण;

#घोषणा QED_MAX_PRIV_DATA_LEN (512)
काष्ठा qed_iwarp_ep_memory अणु
	u8 in_pdata[QED_MAX_PRIV_DATA_LEN];
	u8 out_pdata[QED_MAX_PRIV_DATA_LEN];
	जोड़ async_output async_output;
पूर्ण;

/* Endpoपूर्णांक काष्ठाure represents a TCP connection. This connection can be
 * associated with a QP or not (in which हाल QP==शून्य)
 */
काष्ठा qed_iwarp_ep अणु
	काष्ठा list_head list_entry;
	काष्ठा qed_rdma_qp *qp;
	काष्ठा qed_iwarp_ep_memory *ep_buffer_virt;
	dma_addr_t ep_buffer_phys;
	क्रमागत qed_iwarp_ep_state state;
	पूर्णांक sig;
	काष्ठा qed_iwarp_cm_info cm_info;
	क्रमागत tcp_connect_mode connect_mode;
	क्रमागत mpa_rtr_type rtr_type;
	क्रमागत mpa_negotiation_mode mpa_rev;
	u32 tcp_cid;
	u32 cid;
	u16 mss;
	u8 remote_mac_addr[6];
	u8 local_mac_addr[6];
	bool mpa_reply_processed;

	/* For Passive side - syn packet related data */
	u16 syn_ip_payload_length;
	काष्ठा qed_iwarp_ll2_buff *syn;
	dma_addr_t syn_phy_addr;

	/* The event_cb function is called क्रम asynchrounous events associated
	 * with the ep. It is initialized at dअगरferent entry poपूर्णांकs depending
	 * on whether the ep is the tcp connection active side or passive side
	 * The cb_context is passed to the event_cb function.
	 */
	iwarp_event_handler event_cb;
	व्योम *cb_context;
पूर्ण;

काष्ठा qed_iwarp_listener अणु
	काष्ठा list_head list_entry;

	/* The event_cb function is called क्रम connection requests.
	 * The cb_context is passed to the event_cb function.
	 */
	iwarp_event_handler event_cb;
	व्योम *cb_context;
	u32 max_backlog;
	u32 ip_addr[4];
	u16 port;
	u16 vlan;
	u8 ip_version;
पूर्ण;

पूर्णांक qed_iwarp_alloc(काष्ठा qed_hwfn *p_hwfn);

पूर्णांक qed_iwarp_setup(काष्ठा qed_hwfn *p_hwfn,
		    काष्ठा qed_rdma_start_in_params *params);

व्योम qed_iwarp_init_fw_ramrod(काष्ठा qed_hwfn *p_hwfn,
			      काष्ठा iwarp_init_func_ramrod_data *p_ramrod);

पूर्णांक qed_iwarp_stop(काष्ठा qed_hwfn *p_hwfn);

व्योम qed_iwarp_resc_मुक्त(काष्ठा qed_hwfn *p_hwfn);

व्योम qed_iwarp_init_devinfo(काष्ठा qed_hwfn *p_hwfn);

व्योम qed_iwarp_init_hw(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt);

पूर्णांक qed_iwarp_create_qp(काष्ठा qed_hwfn *p_hwfn,
			काष्ठा qed_rdma_qp *qp,
			काष्ठा qed_rdma_create_qp_out_params *out_params);

पूर्णांक qed_iwarp_modअगरy_qp(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_rdma_qp *qp,
			क्रमागत qed_iwarp_qp_state new_state, bool पूर्णांकernal);

पूर्णांक qed_iwarp_destroy_qp(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_rdma_qp *qp);

पूर्णांक qed_iwarp_fw_destroy(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_rdma_qp *qp);

व्योम qed_iwarp_query_qp(काष्ठा qed_rdma_qp *qp,
			काष्ठा qed_rdma_query_qp_out_params *out_params);

पूर्णांक
qed_iwarp_connect(व्योम *rdma_cxt,
		  काष्ठा qed_iwarp_connect_in *iparams,
		  काष्ठा qed_iwarp_connect_out *oparams);

पूर्णांक
qed_iwarp_create_listen(व्योम *rdma_cxt,
			काष्ठा qed_iwarp_listen_in *iparams,
			काष्ठा qed_iwarp_listen_out *oparams);

पूर्णांक qed_iwarp_accept(व्योम *rdma_cxt, काष्ठा qed_iwarp_accept_in *iparams);

पूर्णांक qed_iwarp_reject(व्योम *rdma_cxt, काष्ठा qed_iwarp_reject_in *iparams);
पूर्णांक qed_iwarp_destroy_listen(व्योम *rdma_cxt, व्योम *handle);

पूर्णांक qed_iwarp_send_rtr(व्योम *rdma_cxt, काष्ठा qed_iwarp_send_rtr_in *iparams);

#पूर्ण_अगर
