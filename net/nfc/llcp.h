<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2011  Intel Corporation. All rights reserved.
 */

क्रमागत llcp_state अणु
	LLCP_CONNECTED = 1, /* रुको_क्रम_packet() wants that */
	LLCP_CONNECTING,
	LLCP_DISCONNECTING,
	LLCP_CLOSED,
	LLCP_BOUND,
	LLCP_LISTEN,
पूर्ण;

#घोषणा LLCP_DEFAULT_LTO 100
#घोषणा LLCP_DEFAULT_RW  1
#घोषणा LLCP_DEFAULT_MIU 128

#घोषणा LLCP_MAX_LTO  0xff
#घोषणा LLCP_MAX_RW   15
#घोषणा LLCP_MAX_MIUX 0x7ff
#घोषणा LLCP_MAX_MIU (LLCP_MAX_MIUX + 128)

#घोषणा LLCP_WKS_NUM_SAP   16
#घोषणा LLCP_SDP_NUM_SAP   16
#घोषणा LLCP_LOCAL_NUM_SAP 32
#घोषणा LLCP_LOCAL_SAP_OFFSET (LLCP_WKS_NUM_SAP + LLCP_SDP_NUM_SAP)
#घोषणा LLCP_MAX_SAP (LLCP_WKS_NUM_SAP + LLCP_SDP_NUM_SAP + LLCP_LOCAL_NUM_SAP)
#घोषणा LLCP_SDP_UNBOUND   (LLCP_MAX_SAP + 1)

काष्ठा nfc_llcp_sock;

काष्ठा llcp_sock_list अणु
	काष्ठा hlist_head head;
	rwlock_t          lock;
पूर्ण;

काष्ठा nfc_llcp_sdp_tlv अणु
	u8 *tlv;
	u8 tlv_len;

	अक्षर *uri;
	u8 tid;
	u8 sap;

	अचिन्हित दीर्घ समय;

	काष्ठा hlist_node node;
पूर्ण;

काष्ठा nfc_llcp_local अणु
	काष्ठा list_head list;
	काष्ठा nfc_dev *dev;

	काष्ठा kref ref;

	काष्ठा mutex sdp_lock;

	काष्ठा समयr_list link_समयr;
	काष्ठा sk_buff_head tx_queue;
	काष्ठा work_काष्ठा	 tx_work;
	काष्ठा work_काष्ठा	 rx_work;
	काष्ठा sk_buff *rx_pending;
	काष्ठा work_काष्ठा	 समयout_work;

	u32 target_idx;
	u8 rf_mode;
	u8 comm_mode;
	u8 lto;
	u8 rw;
	__be16 miux;
	अचिन्हित दीर्घ local_wks;      /* Well known services */
	अचिन्हित दीर्घ local_sdp;      /* Local services  */
	अचिन्हित दीर्घ local_sap; /* Local SAPs, not available क्रम discovery */
	atomic_t local_sdp_cnt[LLCP_SDP_NUM_SAP];

	/* local */
	u8 gb[NFC_MAX_GT_LEN];
	u8 gb_len;

	/* remote */
	u8 remote_gb[NFC_MAX_GT_LEN];
	u8 remote_gb_len;

	u8  remote_version;
	u16 remote_miu;
	u16 remote_lto;
	u8  remote_opt;
	u16 remote_wks;

	काष्ठा mutex sdreq_lock;
	काष्ठा hlist_head pending_sdreqs;
	काष्ठा समयr_list sdreq_समयr;
	काष्ठा work_काष्ठा sdreq_समयout_work;
	u8 sdreq_next_tid;

	/* sockets array */
	काष्ठा llcp_sock_list sockets;
	काष्ठा llcp_sock_list connecting_sockets;
	काष्ठा llcp_sock_list raw_sockets;
पूर्ण;

काष्ठा nfc_llcp_sock अणु
	काष्ठा sock sk;
	काष्ठा nfc_dev *dev;
	काष्ठा nfc_llcp_local *local;
	u32 target_idx;
	u32 nfc_protocol;

	/* Link parameters */
	u8 ssap;
	u8 dsap;
	अक्षर *service_name;
	माप_प्रकार service_name_len;
	u8 rw;
	__be16 miux;


	/* Remote link parameters */
	u8 remote_rw;
	u16 remote_miu;

	/* Link variables */
	u8 send_n;
	u8 send_ack_n;
	u8 recv_n;
	u8 recv_ack_n;

	/* Is the remote peer पढ़ोy to receive */
	u8 remote_पढ़ोy;

	/* Reserved source SAP */
	u8 reserved_ssap;

	काष्ठा sk_buff_head tx_queue;
	काष्ठा sk_buff_head tx_pending_queue;

	काष्ठा list_head accept_queue;
	काष्ठा sock *parent;
पूर्ण;

काष्ठा nfc_llcp_ui_cb अणु
	__u8 dsap;
	__u8 ssap;
पूर्ण;

#घोषणा nfc_llcp_ui_skb_cb(__skb) ((काष्ठा nfc_llcp_ui_cb *)&((__skb)->cb[0]))

#घोषणा nfc_llcp_sock(sk) ((काष्ठा nfc_llcp_sock *) (sk))
#घोषणा nfc_llcp_dev(sk)  (nfc_llcp_sock((sk))->dev)

#घोषणा LLCP_HEADER_SIZE   2
#घोषणा LLCP_SEQUENCE_SIZE 1
#घोषणा LLCP_AGF_PDU_HEADER_SIZE 2

/* LLCP versions: 1.1 is 1.0 plus SDP */
#घोषणा LLCP_VERSION_10 0x10
#घोषणा LLCP_VERSION_11 0x11

/* LLCP PDU types */
#घोषणा LLCP_PDU_SYMM     0x0
#घोषणा LLCP_PDU_PAX      0x1
#घोषणा LLCP_PDU_AGF      0x2
#घोषणा LLCP_PDU_UI       0x3
#घोषणा LLCP_PDU_CONNECT  0x4
#घोषणा LLCP_PDU_DISC     0x5
#घोषणा LLCP_PDU_CC       0x6
#घोषणा LLCP_PDU_DM       0x7
#घोषणा LLCP_PDU_FRMR     0x8
#घोषणा LLCP_PDU_SNL      0x9
#घोषणा LLCP_PDU_I        0xc
#घोषणा LLCP_PDU_RR       0xd
#घोषणा LLCP_PDU_RNR      0xe

/* Parameters TLV types */
#घोषणा LLCP_TLV_VERSION 0x1
#घोषणा LLCP_TLV_MIUX    0x2
#घोषणा LLCP_TLV_WKS     0x3
#घोषणा LLCP_TLV_LTO     0x4
#घोषणा LLCP_TLV_RW      0x5
#घोषणा LLCP_TLV_SN      0x6
#घोषणा LLCP_TLV_OPT     0x7
#घोषणा LLCP_TLV_SDREQ   0x8
#घोषणा LLCP_TLV_SDRES   0x9
#घोषणा LLCP_TLV_MAX     0xa

/* Well known LLCP SAP */
#घोषणा LLCP_SAP_SDP   0x1
#घोषणा LLCP_SAP_IP    0x2
#घोषणा LLCP_SAP_OBEX  0x3
#घोषणा LLCP_SAP_SNEP  0x4
#घोषणा LLCP_SAP_MAX   0xff

/* Disconnection reason code */
#घोषणा LLCP_DM_DISC    0x00
#घोषणा LLCP_DM_NOCONN  0x01
#घोषणा LLCP_DM_NOBOUND 0x02
#घोषणा LLCP_DM_REJ     0x03


व्योम nfc_llcp_sock_link(काष्ठा llcp_sock_list *l, काष्ठा sock *s);
व्योम nfc_llcp_sock_unlink(काष्ठा llcp_sock_list *l, काष्ठा sock *s);
व्योम nfc_llcp_socket_remote_param_init(काष्ठा nfc_llcp_sock *sock);
काष्ठा nfc_llcp_local *nfc_llcp_find_local(काष्ठा nfc_dev *dev);
काष्ठा nfc_llcp_local *nfc_llcp_local_get(काष्ठा nfc_llcp_local *local);
पूर्णांक nfc_llcp_local_put(काष्ठा nfc_llcp_local *local);
u8 nfc_llcp_get_sdp_ssap(काष्ठा nfc_llcp_local *local,
			 काष्ठा nfc_llcp_sock *sock);
u8 nfc_llcp_get_local_ssap(काष्ठा nfc_llcp_local *local);
व्योम nfc_llcp_put_ssap(काष्ठा nfc_llcp_local *local, u8 ssap);
पूर्णांक nfc_llcp_queue_i_frames(काष्ठा nfc_llcp_sock *sock);
व्योम nfc_llcp_send_to_raw_sock(काष्ठा nfc_llcp_local *local,
			       काष्ठा sk_buff *skb, u8 direction);

/* Sock API */
काष्ठा sock *nfc_llcp_sock_alloc(काष्ठा socket *sock, पूर्णांक type, gfp_t gfp, पूर्णांक kern);
व्योम nfc_llcp_sock_मुक्त(काष्ठा nfc_llcp_sock *sock);
व्योम nfc_llcp_accept_unlink(काष्ठा sock *sk);
व्योम nfc_llcp_accept_enqueue(काष्ठा sock *parent, काष्ठा sock *sk);
काष्ठा sock *nfc_llcp_accept_dequeue(काष्ठा sock *sk, काष्ठा socket *newsock);

/* TLV API */
पूर्णांक nfc_llcp_parse_gb_tlv(काष्ठा nfc_llcp_local *local,
			  u8 *tlv_array, u16 tlv_array_len);
पूर्णांक nfc_llcp_parse_connection_tlv(काष्ठा nfc_llcp_sock *sock,
				  u8 *tlv_array, u16 tlv_array_len);

/* Commands API */
व्योम nfc_llcp_recv(व्योम *data, काष्ठा sk_buff *skb, पूर्णांक err);
u8 *nfc_llcp_build_tlv(u8 type, u8 *value, u8 value_length, u8 *tlv_length);
काष्ठा nfc_llcp_sdp_tlv *nfc_llcp_build_sdres_tlv(u8 tid, u8 sap);
काष्ठा nfc_llcp_sdp_tlv *nfc_llcp_build_sdreq_tlv(u8 tid, अक्षर *uri,
						  माप_प्रकार uri_len);
व्योम nfc_llcp_मुक्त_sdp_tlv(काष्ठा nfc_llcp_sdp_tlv *sdp);
व्योम nfc_llcp_मुक्त_sdp_tlv_list(काष्ठा hlist_head *sdp_head);
व्योम nfc_llcp_recv(व्योम *data, काष्ठा sk_buff *skb, पूर्णांक err);
पूर्णांक nfc_llcp_send_symm(काष्ठा nfc_dev *dev);
पूर्णांक nfc_llcp_send_connect(काष्ठा nfc_llcp_sock *sock);
पूर्णांक nfc_llcp_send_cc(काष्ठा nfc_llcp_sock *sock);
पूर्णांक nfc_llcp_send_snl_sdres(काष्ठा nfc_llcp_local *local,
			    काष्ठा hlist_head *tlv_list, माप_प्रकार tlvs_len);
पूर्णांक nfc_llcp_send_snl_sdreq(काष्ठा nfc_llcp_local *local,
			    काष्ठा hlist_head *tlv_list, माप_प्रकार tlvs_len);
पूर्णांक nfc_llcp_send_dm(काष्ठा nfc_llcp_local *local, u8 ssap, u8 dsap, u8 reason);
पूर्णांक nfc_llcp_send_disconnect(काष्ठा nfc_llcp_sock *sock);
पूर्णांक nfc_llcp_send_i_frame(काष्ठा nfc_llcp_sock *sock,
			  काष्ठा msghdr *msg, माप_प्रकार len);
पूर्णांक nfc_llcp_send_ui_frame(काष्ठा nfc_llcp_sock *sock, u8 ssap, u8 dsap,
			   काष्ठा msghdr *msg, माप_प्रकार len);
पूर्णांक nfc_llcp_send_rr(काष्ठा nfc_llcp_sock *sock);

/* Socket API */
पूर्णांक __init nfc_llcp_sock_init(व्योम);
व्योम nfc_llcp_sock_निकास(व्योम);
