<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * File: pep.h
 *
 * Phonet Pipe End Poपूर्णांक sockets definitions
 *
 * Copyright (C) 2008 Nokia Corporation.
 */

#अगर_अघोषित NET_PHONET_PEP_H
#घोषणा NET_PHONET_PEP_H

काष्ठा pep_sock अणु
	काष्ठा pn_sock		pn_sk;

	/* XXX: जोड़-अगरy listening vs connected stuff ? */
	/* Listening socket stuff: */
	काष्ठा hlist_head	hlist;

	/* Connected socket stuff: */
	काष्ठा sock		*listener;
	काष्ठा sk_buff_head	ctrlreq_queue;
#घोषणा PNPIPE_CTRLREQ_MAX	10
	atomic_t		tx_credits;
	पूर्णांक			अगरindex;
	u16			peer_type;	/* peer type/subtype */
	u8			pipe_handle;

	u8			rx_credits;
	u8			rx_fc;	/* RX flow control */
	u8			tx_fc;	/* TX flow control */
	u8			init_enable;	/* स्वतः-enable at creation */
	u8			aligned;
पूर्ण;

अटल अंतरभूत काष्ठा pep_sock *pep_sk(काष्ठा sock *sk)
अणु
	वापस (काष्ठा pep_sock *)sk;
पूर्ण

बाह्य स्थिर काष्ठा proto_ops phonet_stream_ops;

/* Pipe protocol definitions */
काष्ठा pnpipehdr अणु
	u8			utid; /* transaction ID */
	u8			message_id;
	u8			pipe_handle;
	जोड़ अणु
		u8		state_after_connect;	/* connect request */
		u8		state_after_reset;	/* reset request */
		u8		error_code;		/* any response */
		u8		pep_type;		/* status indication */
		u8		data0;			/* anything अन्यथा */
	पूर्ण;
	u8			data[];
पूर्ण;
#घोषणा other_pep_type		data[0]

अटल अंतरभूत काष्ठा pnpipehdr *pnp_hdr(काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा pnpipehdr *)skb_transport_header(skb);
पूर्ण

#घोषणा MAX_PNPIPE_HEADER (MAX_PHONET_HEADER + 4)

क्रमागत अणु
	PNS_PIPE_CREATE_REQ = 0x00,
	PNS_PIPE_CREATE_RESP,
	PNS_PIPE_REMOVE_REQ,
	PNS_PIPE_REMOVE_RESP,

	PNS_PIPE_DATA = 0x20,
	PNS_PIPE_ALIGNED_DATA,

	PNS_PEP_CONNECT_REQ = 0x40,
	PNS_PEP_CONNECT_RESP,
	PNS_PEP_DISCONNECT_REQ,
	PNS_PEP_DISCONNECT_RESP,
	PNS_PEP_RESET_REQ,
	PNS_PEP_RESET_RESP,
	PNS_PEP_ENABLE_REQ,
	PNS_PEP_ENABLE_RESP,
	PNS_PEP_CTRL_REQ,
	PNS_PEP_CTRL_RESP,
	PNS_PEP_DISABLE_REQ = 0x4C,
	PNS_PEP_DISABLE_RESP,

	PNS_PEP_STATUS_IND = 0x60,
	PNS_PIPE_CREATED_IND,
	PNS_PIPE_RESET_IND = 0x63,
	PNS_PIPE_ENABLED_IND,
	PNS_PIPE_REसूचीECTED_IND,
	PNS_PIPE_DISABLED_IND = 0x66,
पूर्ण;

#घोषणा PN_PIPE_INVALID_HANDLE	0xff
#घोषणा PN_PEP_TYPE_COMMON	0x00

/* Phonet pipe status indication */
क्रमागत अणु
	PN_PEP_IND_FLOW_CONTROL,
	PN_PEP_IND_ID_MCFC_GRANT_CREDITS,
पूर्ण;

/* Phonet pipe error codes */
क्रमागत अणु
	PN_PIPE_NO_ERROR,
	PN_PIPE_ERR_INVALID_PARAM,
	PN_PIPE_ERR_INVALID_HANDLE,
	PN_PIPE_ERR_INVALID_CTRL_ID,
	PN_PIPE_ERR_NOT_ALLOWED,
	PN_PIPE_ERR_PEP_IN_USE,
	PN_PIPE_ERR_OVERLOAD,
	PN_PIPE_ERR_DEV_DISCONNECTED,
	PN_PIPE_ERR_TIMEOUT,
	PN_PIPE_ERR_ALL_PIPES_IN_USE,
	PN_PIPE_ERR_GENERAL,
	PN_PIPE_ERR_NOT_SUPPORTED,
पूर्ण;

/* Phonet pipe states */
क्रमागत अणु
	PN_PIPE_DISABLE,
	PN_PIPE_ENABLE,
पूर्ण;

/* Phonet pipe sub-block types */
क्रमागत अणु
	PN_PIPE_SB_CREATE_REQ_PEP_SUB_TYPE,
	PN_PIPE_SB_CONNECT_REQ_PEP_SUB_TYPE,
	PN_PIPE_SB_REसूचीECT_REQ_PEP_SUB_TYPE,
	PN_PIPE_SB_NEGOTIATED_FC,
	PN_PIPE_SB_REQUIRED_FC_TX,
	PN_PIPE_SB_PREFERRED_FC_RX,
	PN_PIPE_SB_ALIGNED_DATA,
पूर्ण;

/* Phonet pipe flow control models */
क्रमागत अणु
	PN_NO_FLOW_CONTROL,
	PN_LEGACY_FLOW_CONTROL,
	PN_ONE_CREDIT_FLOW_CONTROL,
	PN_MULTI_CREDIT_FLOW_CONTROL,
	PN_MAX_FLOW_CONTROL,
पूर्ण;

#घोषणा pn_flow_safe(fc) ((fc) >> 1)

/* Phonet pipe flow control states */
क्रमागत अणु
	PEP_IND_EMPTY,
	PEP_IND_BUSY,
	PEP_IND_READY,
पूर्ण;

#पूर्ण_अगर
