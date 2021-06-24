<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (C) 2020 Chelsio Communications.  All rights reserved. */

#अगर_अघोषित __CHCR_KTLS_H__
#घोषणा __CHCR_KTLS_H__

#समावेश "cxgb4.h"
#समावेश "t4_msg.h"
#समावेश "t4_tcb.h"
#समावेश "l2t.h"
#समावेश "chcr_common.h"
#समावेश "cxgb4_uld.h"
#समावेश "clip_tbl.h"

#घोषणा CHCR_KTLS_DRV_MODULE_NAME "ch_ktls"
#घोषणा CHCR_KTLS_DRV_VERSION "1.0.0.0-ko"
#घोषणा CHCR_KTLS_DRV_DESC "Chelsio NIC TLS ULD Driver"

#घोषणा CHCR_TCB_STATE_CLOSED	0
#घोषणा CHCR_KTLS_KEY_CTX_LEN	16
#घोषणा CHCR_SET_TCB_FIELD_LEN	माप(काष्ठा cpl_set_tcb_field)
#घोषणा CHCR_PLAIN_TX_DATA_LEN	(माप(काष्ठा fw_ulptx_wr) +\
				 माप(काष्ठा ulp_txpkt) +\
				 माप(काष्ठा ulptx_idata) +\
				 माप(काष्ठा cpl_tx_data))

#घोषणा CHCR_KTLS_WR_SIZE	(CHCR_PLAIN_TX_DATA_LEN +\
				 माप(काष्ठा cpl_tx_sec_pdu))
#घोषणा FALLBACK		35

क्रमागत ch_ktls_खोलो_state अणु
	CH_KTLS_OPEN_SUCCESS = 0,
	CH_KTLS_OPEN_PENDING = 1,
	CH_KTLS_OPEN_FAILURE = 2,
पूर्ण;

काष्ठा chcr_ktls_info अणु
	काष्ठा sock *sk;
	spinlock_t lock; /* lock क्रम pending_बंद */
	काष्ठा ktls_key_ctx key_ctx;
	काष्ठा adapter *adap;
	काष्ठा l2t_entry *l2te;
	काष्ठा net_device *netdev;
	काष्ठा completion completion;
	u64 iv;
	u64 record_no;
	पूर्णांक tid;
	पूर्णांक atid;
	पूर्णांक rx_qid;
	u32 iv_size;
	u32 prev_seq;
	u32 prev_ack;
	u32 salt_size;
	u32 key_ctx_len;
	u32 scmd0_seqno_numivs;
	u32 scmd0_ivgen_hdrlen;
	u32 tcp_start_seq_number;
	u32 scmd0_लघु_seqno_numivs;
	u32 scmd0_लघु_ivgen_hdrlen;
	u16 prev_win;
	u8 tx_chan;
	u8 smt_idx;
	u8 port_id;
	u8 ip_family;
	u8 first_qset;
	क्रमागत ch_ktls_खोलो_state खोलो_state;
	bool pending_बंद;
पूर्ण;

काष्ठा chcr_ktls_ofld_ctx_tx अणु
	काष्ठा tls_offload_context_tx base;
	काष्ठा chcr_ktls_info *chcr_info;
पूर्ण;

काष्ठा chcr_ktls_uld_ctx अणु
	काष्ठा list_head entry;
	काष्ठा cxgb4_lld_info lldi;
	काष्ठा xarray tid_list;
	bool detach;
पूर्ण;

अटल अंतरभूत काष्ठा chcr_ktls_ofld_ctx_tx *
chcr_get_ktls_tx_context(काष्ठा tls_context *tls_ctx)
अणु
	BUILD_BUG_ON(माप(काष्ठा chcr_ktls_ofld_ctx_tx) >
		     TLS_OFFLOAD_CONTEXT_SIZE_TX);
	वापस container_of(tls_offload_ctx_tx(tls_ctx),
			    काष्ठा chcr_ktls_ofld_ctx_tx,
			    base);
पूर्ण

अटल अंतरभूत पूर्णांक chcr_get_first_rx_qid(काष्ठा adapter *adap)
अणु
	/* u_ctx is saved in adap, fetch it */
	काष्ठा chcr_ktls_uld_ctx *u_ctx = adap->uld[CXGB4_ULD_KTLS].handle;

	अगर (!u_ctx)
		वापस -1;
	वापस u_ctx->lldi.rxq_ids[0];
पूर्ण

प्रकार पूर्णांक (*chcr_handler_func)(काष्ठा adapter *adap, अचिन्हित अक्षर *input);
#पूर्ण_अगर /* __CHCR_KTLS_H__ */
