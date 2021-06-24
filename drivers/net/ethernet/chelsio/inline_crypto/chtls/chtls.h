<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2018 Chelsio Communications, Inc.
 */

#अगर_अघोषित __CHTLS_H__
#घोषणा __CHTLS_H__

#समावेश <crypto/aes.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/hash.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha2.h>
#समावेश <crypto/authenc.h>
#समावेश <crypto/ctr.h>
#समावेश <crypto/gf128mul.h>
#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/null.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/aead.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <linux/tls.h>
#समावेश <net/tls.h>
#समावेश <net/tls_toe.h>

#समावेश "t4fw_api.h"
#समावेश "t4_msg.h"
#समावेश "cxgb4.h"
#समावेश "cxgb4_uld.h"
#समावेश "l2t.h"
#समावेश "chcr_algo.h"
#समावेश "chcr_core.h"
#समावेश "chcr_crypto.h"

#घोषणा CHTLS_DRV_VERSION "1.0.0.0-ko"

#घोषणा TLS_KEYCTX_RXFLIT_CNT_S 24
#घोषणा TLS_KEYCTX_RXFLIT_CNT_V(x) ((x) << TLS_KEYCTX_RXFLIT_CNT_S)

#घोषणा TLS_KEYCTX_RXPROT_VER_S 20
#घोषणा TLS_KEYCTX_RXPROT_VER_M 0xf
#घोषणा TLS_KEYCTX_RXPROT_VER_V(x) ((x) << TLS_KEYCTX_RXPROT_VER_S)

#घोषणा TLS_KEYCTX_RXCIPH_MODE_S 16
#घोषणा TLS_KEYCTX_RXCIPH_MODE_M 0xf
#घोषणा TLS_KEYCTX_RXCIPH_MODE_V(x) ((x) << TLS_KEYCTX_RXCIPH_MODE_S)

#घोषणा TLS_KEYCTX_RXAUTH_MODE_S 12
#घोषणा TLS_KEYCTX_RXAUTH_MODE_M 0xf
#घोषणा TLS_KEYCTX_RXAUTH_MODE_V(x) ((x) << TLS_KEYCTX_RXAUTH_MODE_S)

#घोषणा TLS_KEYCTX_RXCIAU_CTRL_S 11
#घोषणा TLS_KEYCTX_RXCIAU_CTRL_V(x) ((x) << TLS_KEYCTX_RXCIAU_CTRL_S)

#घोषणा TLS_KEYCTX_RX_SEQCTR_S 9
#घोषणा TLS_KEYCTX_RX_SEQCTR_M 0x3
#घोषणा TLS_KEYCTX_RX_SEQCTR_V(x) ((x) << TLS_KEYCTX_RX_SEQCTR_S)

#घोषणा TLS_KEYCTX_RX_VALID_S 8
#घोषणा TLS_KEYCTX_RX_VALID_V(x) ((x) << TLS_KEYCTX_RX_VALID_S)

#घोषणा TLS_KEYCTX_RXCK_SIZE_S 3
#घोषणा TLS_KEYCTX_RXCK_SIZE_M 0x7
#घोषणा TLS_KEYCTX_RXCK_SIZE_V(x) ((x) << TLS_KEYCTX_RXCK_SIZE_S)

#घोषणा TLS_KEYCTX_RXMK_SIZE_S 0
#घोषणा TLS_KEYCTX_RXMK_SIZE_M 0x7
#घोषणा TLS_KEYCTX_RXMK_SIZE_V(x) ((x) << TLS_KEYCTX_RXMK_SIZE_S)

#घोषणा KEYCTX_TX_WR_IV_S  55
#घोषणा KEYCTX_TX_WR_IV_M  0x1ffULL
#घोषणा KEYCTX_TX_WR_IV_V(x) ((x) << KEYCTX_TX_WR_IV_S)
#घोषणा KEYCTX_TX_WR_IV_G(x) \
	(((x) >> KEYCTX_TX_WR_IV_S) & KEYCTX_TX_WR_IV_M)

#घोषणा KEYCTX_TX_WR_AAD_S 47
#घोषणा KEYCTX_TX_WR_AAD_M 0xffULL
#घोषणा KEYCTX_TX_WR_AAD_V(x) ((x) << KEYCTX_TX_WR_AAD_S)
#घोषणा KEYCTX_TX_WR_AAD_G(x) (((x) >> KEYCTX_TX_WR_AAD_S) & \
				KEYCTX_TX_WR_AAD_M)

#घोषणा KEYCTX_TX_WR_AADST_S 39
#घोषणा KEYCTX_TX_WR_AADST_M 0xffULL
#घोषणा KEYCTX_TX_WR_AADST_V(x) ((x) << KEYCTX_TX_WR_AADST_S)
#घोषणा KEYCTX_TX_WR_AADST_G(x) \
	(((x) >> KEYCTX_TX_WR_AADST_S) & KEYCTX_TX_WR_AADST_M)

#घोषणा KEYCTX_TX_WR_CIPHER_S 30
#घोषणा KEYCTX_TX_WR_CIPHER_M 0x1ffULL
#घोषणा KEYCTX_TX_WR_CIPHER_V(x) ((x) << KEYCTX_TX_WR_CIPHER_S)
#घोषणा KEYCTX_TX_WR_CIPHER_G(x) \
	(((x) >> KEYCTX_TX_WR_CIPHER_S) & KEYCTX_TX_WR_CIPHER_M)

#घोषणा KEYCTX_TX_WR_CIPHERST_S 23
#घोषणा KEYCTX_TX_WR_CIPHERST_M 0x7f
#घोषणा KEYCTX_TX_WR_CIPHERST_V(x) ((x) << KEYCTX_TX_WR_CIPHERST_S)
#घोषणा KEYCTX_TX_WR_CIPHERST_G(x) \
	(((x) >> KEYCTX_TX_WR_CIPHERST_S) & KEYCTX_TX_WR_CIPHERST_M)

#घोषणा KEYCTX_TX_WR_AUTH_S 14
#घोषणा KEYCTX_TX_WR_AUTH_M 0x1ff
#घोषणा KEYCTX_TX_WR_AUTH_V(x) ((x) << KEYCTX_TX_WR_AUTH_S)
#घोषणा KEYCTX_TX_WR_AUTH_G(x) \
	(((x) >> KEYCTX_TX_WR_AUTH_S) & KEYCTX_TX_WR_AUTH_M)

#घोषणा KEYCTX_TX_WR_AUTHST_S 7
#घोषणा KEYCTX_TX_WR_AUTHST_M 0x7f
#घोषणा KEYCTX_TX_WR_AUTHST_V(x) ((x) << KEYCTX_TX_WR_AUTHST_S)
#घोषणा KEYCTX_TX_WR_AUTHST_G(x) \
	(((x) >> KEYCTX_TX_WR_AUTHST_S) & KEYCTX_TX_WR_AUTHST_M)

#घोषणा KEYCTX_TX_WR_AUTHIN_S 0
#घोषणा KEYCTX_TX_WR_AUTHIN_M 0x7f
#घोषणा KEYCTX_TX_WR_AUTHIN_V(x) ((x) << KEYCTX_TX_WR_AUTHIN_S)
#घोषणा KEYCTX_TX_WR_AUTHIN_G(x) \
	(((x) >> KEYCTX_TX_WR_AUTHIN_S) & KEYCTX_TX_WR_AUTHIN_M)

काष्ठा sge_opaque_hdr अणु
	व्योम *dev;
	dma_addr_t addr[MAX_SKB_FRAGS + 1];
पूर्ण;

#घोषणा MAX_IVS_PAGE			256
#घोषणा TLS_KEY_CONTEXT_SZ		64
#घोषणा CIPHER_BLOCK_SIZE		16
#घोषणा GCM_TAG_SIZE			16
#घोषणा KEY_ON_MEM_SZ			16
#घोषणा AEAD_EXPLICIT_DATA_SIZE		8
#घोषणा TLS_HEADER_LENGTH		5
#घोषणा SCMD_CIPH_MODE_AES_GCM		2
/* Any MFS size should work and come from खोलोssl */
#घोषणा TLS_MFS				16384

#घोषणा RSS_HDR माप(काष्ठा rss_header)
#घोषणा TLS_WR_CPL_LEN \
	(माप(काष्ठा fw_tlstx_data_wr) + माप(काष्ठा cpl_tx_tls_sfo))

क्रमागत अणु
	CHTLS_KEY_CONTEXT_DSGL,
	CHTLS_KEY_CONTEXT_IMM,
	CHTLS_KEY_CONTEXT_DDR,
पूर्ण;

क्रमागत अणु
	CHTLS_LISTEN_START,
	CHTLS_LISTEN_STOP,
पूर्ण;

/* Flags क्रम वापस value of CPL message handlers */
क्रमागत अणु
	CPL_RET_BUF_DONE =    1,   /* buffer processing करोne */
	CPL_RET_BAD_MSG =     2,   /* bad CPL message */
	CPL_RET_UNKNOWN_TID = 4    /* unexpected unknown TID */
पूर्ण;

#घोषणा LISTEN_INFO_HASH_SIZE 32
#घोषणा RSPQ_HASH_BITS 5
काष्ठा listen_info अणु
	काष्ठा listen_info *next;  /* Link to next entry */
	काष्ठा sock *sk;           /* The listening socket */
	अचिन्हित पूर्णांक stid;         /* The server TID */
पूर्ण;

क्रमागत अणु
	T4_LISTEN_START_PENDING,
	T4_LISTEN_STARTED
पूर्ण;

क्रमागत csk_flags अणु
	CSK_CALLBACKS_CHKD,	/* socket callbacks have been sanitized */
	CSK_ABORT_REQ_RCVD,	/* received one ABORT_REQ_RSS message */
	CSK_TX_MORE_DATA,	/* sending ULP data; करोn't set SHOVE bit */
	CSK_TX_WAIT_IDLE,	/* suspend Tx until in-flight data is ACKed */
	CSK_ABORT_SHUTDOWN,	/* shouldn't send more पात requests */
	CSK_ABORT_RPL_PENDING,	/* expecting an पात reply */
	CSK_CLOSE_CON_REQUESTED,/* we've sent a बंद_conn_req */
	CSK_TX_DATA_SENT,	/* sent a TX_DATA WR on this connection */
	CSK_TX_FAILOVER,	/* Tx traffic failing over */
	CSK_UPDATE_RCV_WND,	/* Need to update rcv winकरोw */
	CSK_RST_ABORTED,	/* outgoing RST was पातed */
	CSK_TLS_HANDSHK,	/* TLS Handshake */
	CSK_CONN_INLINE,	/* Connection on HW */
पूर्ण;

क्रमागत chtls_cdev_state अणु
	CHTLS_CDEV_STATE_UP = 1
पूर्ण;

काष्ठा listen_ctx अणु
	काष्ठा sock *lsk;
	काष्ठा chtls_dev *cdev;
	काष्ठा sk_buff_head synq;
	u32 state;
पूर्ण;

काष्ठा key_map अणु
	अचिन्हित दीर्घ *addr;
	अचिन्हित पूर्णांक start;
	अचिन्हित पूर्णांक available;
	अचिन्हित पूर्णांक size;
	spinlock_t lock; /* lock क्रम key id request from map */
पूर्ण __packed;

काष्ठा tls_scmd अणु
	u32 seqno_numivs;
	u32 ivgen_hdrlen;
पूर्ण;

काष्ठा chtls_dev अणु
	काष्ठा tls_toe_device tlsdev;
	काष्ठा list_head list;
	काष्ठा cxgb4_lld_info *lldi;
	काष्ठा pci_dev *pdev;
	काष्ठा listen_info *listen_hash_tab[LISTEN_INFO_HASH_SIZE];
	spinlock_t listen_lock; /* lock क्रम listen list */
	काष्ठा net_device **ports;
	काष्ठा tid_info *tids;
	अचिन्हित पूर्णांक pfvf;
	स्थिर अचिन्हित लघु *mtus;

	काष्ठा idr hwtid_idr;
	काष्ठा idr stid_idr;

	spinlock_t idr_lock ____cacheline_aligned_in_smp;

	काष्ठा net_device *egr_dev[NCHAN * 2];
	काष्ठा sk_buff *rspq_skb_cache[1 << RSPQ_HASH_BITS];
	काष्ठा sk_buff *askb;

	काष्ठा sk_buff_head deferq;
	काष्ठा work_काष्ठा deferq_task;

	काष्ठा list_head list_node;
	काष्ठा list_head rcu_node;
	काष्ठा list_head na_node;
	अचिन्हित पूर्णांक send_page_order;
	पूर्णांक max_host_sndbuf;
	u32 round_robin_cnt;
	काष्ठा key_map kmap;
	अचिन्हित पूर्णांक cdev_state;
पूर्ण;

काष्ठा chtls_listen अणु
	काष्ठा chtls_dev *cdev;
	काष्ठा sock *sk;
पूर्ण;

काष्ठा chtls_hws अणु
	काष्ठा sk_buff_head sk_recv_queue;
	u8 txqid;
	u8 ofld;
	u16 type;
	u16 rstate;
	u16 keyrpl;
	u16 pldlen;
	u16 rcvpld;
	u16 compute;
	u16 expansion;
	u16 keylen;
	u16 pdus;
	u16 adjustlen;
	u16 ivsize;
	u16 txleft;
	u32 mfs;
	s32 txkey;
	s32 rxkey;
	u32 fcplenmax;
	u32 copied_seq;
	u64 tx_seq_no;
	काष्ठा tls_scmd scmd;
	जोड़ अणु
		काष्ठा tls12_crypto_info_aes_gcm_128 aes_gcm_128;
		काष्ठा tls12_crypto_info_aes_gcm_256 aes_gcm_256;
	पूर्ण crypto_info;
पूर्ण;

काष्ठा chtls_sock अणु
	काष्ठा sock *sk;
	काष्ठा chtls_dev *cdev;
	काष्ठा l2t_entry *l2t_entry;    /* poपूर्णांकer to the L2T entry */
	काष्ठा net_device *egress_dev;  /* TX_CHAN क्रम act खोलो retry */

	काष्ठा sk_buff_head txq;
	काष्ठा sk_buff *wr_skb_head;
	काष्ठा sk_buff *wr_skb_tail;
	काष्ठा sk_buff *ctrl_skb_cache;
	काष्ठा sk_buff *txdata_skb_cache; /* पात path messages */
	काष्ठा kref kref;
	अचिन्हित दीर्घ flags;
	u32 opt2;
	u32 wr_credits;
	u32 wr_unacked;
	u32 wr_max_credits;
	u32 wr_nondata;
	u32 hwtid;               /* TCP Control Block ID */
	u32 txq_idx;
	u32 rss_qid;
	u32 tid;
	u32 idr;
	u32 mss;
	u32 ulp_mode;
	u32 tx_chan;
	u32 rx_chan;
	u32 sndbuf;
	u32 txplen_max;
	u32 mtu_idx;           /* MTU table index */
	u32 smac_idx;
	u8 port_id;
	u8 tos;
	u16 resv2;
	u32 delack_mode;
	u32 delack_seq;
	u32 snd_win;
	u32 rcv_win;

	व्योम *passive_reap_next;        /* placeholder क्रम passive */
	काष्ठा chtls_hws tlshws;
	काष्ठा synq अणु
		काष्ठा sk_buff *next;
		काष्ठा sk_buff *prev;
	पूर्ण synq;
	काष्ठा listen_ctx *listen_ctx;
पूर्ण;

काष्ठा tls_hdr अणु
	u8  type;
	u16 version;
	u16 length;
पूर्ण __packed;

काष्ठा tlsrx_cmp_hdr अणु
	u8  type;
	u16 version;
	u16 length;

	u64 tls_seq;
	u16 reserved1;
	u8  res_to_mac_error;
पूर्ण __packed;

/* res_to_mac_error fields */
#घोषणा TLSRX_HDR_PKT_INT_ERROR_S   4
#घोषणा TLSRX_HDR_PKT_INT_ERROR_M   0x1
#घोषणा TLSRX_HDR_PKT_INT_ERROR_V(x) \
	((x) << TLSRX_HDR_PKT_INT_ERROR_S)
#घोषणा TLSRX_HDR_PKT_INT_ERROR_G(x) \
	(((x) >> TLSRX_HDR_PKT_INT_ERROR_S) & TLSRX_HDR_PKT_INT_ERROR_M)
#घोषणा TLSRX_HDR_PKT_INT_ERROR_F   TLSRX_HDR_PKT_INT_ERROR_V(1U)

#घोषणा TLSRX_HDR_PKT_SPP_ERROR_S        3
#घोषणा TLSRX_HDR_PKT_SPP_ERROR_M        0x1
#घोषणा TLSRX_HDR_PKT_SPP_ERROR_V(x)     ((x) << TLSRX_HDR_PKT_SPP_ERROR)
#घोषणा TLSRX_HDR_PKT_SPP_ERROR_G(x)     \
	(((x) >> TLSRX_HDR_PKT_SPP_ERROR_S) & TLSRX_HDR_PKT_SPP_ERROR_M)
#घोषणा TLSRX_HDR_PKT_SPP_ERROR_F        TLSRX_HDR_PKT_SPP_ERROR_V(1U)

#घोषणा TLSRX_HDR_PKT_CCDX_ERROR_S       2
#घोषणा TLSRX_HDR_PKT_CCDX_ERROR_M       0x1
#घोषणा TLSRX_HDR_PKT_CCDX_ERROR_V(x)    ((x) << TLSRX_HDR_PKT_CCDX_ERROR_S)
#घोषणा TLSRX_HDR_PKT_CCDX_ERROR_G(x)    \
	(((x) >> TLSRX_HDR_PKT_CCDX_ERROR_S) & TLSRX_HDR_PKT_CCDX_ERROR_M)
#घोषणा TLSRX_HDR_PKT_CCDX_ERROR_F       TLSRX_HDR_PKT_CCDX_ERROR_V(1U)

#घोषणा TLSRX_HDR_PKT_PAD_ERROR_S        1
#घोषणा TLSRX_HDR_PKT_PAD_ERROR_M        0x1
#घोषणा TLSRX_HDR_PKT_PAD_ERROR_V(x)     ((x) << TLSRX_HDR_PKT_PAD_ERROR_S)
#घोषणा TLSRX_HDR_PKT_PAD_ERROR_G(x)     \
	(((x) >> TLSRX_HDR_PKT_PAD_ERROR_S) & TLSRX_HDR_PKT_PAD_ERROR_M)
#घोषणा TLSRX_HDR_PKT_PAD_ERROR_F        TLSRX_HDR_PKT_PAD_ERROR_V(1U)

#घोषणा TLSRX_HDR_PKT_MAC_ERROR_S        0
#घोषणा TLSRX_HDR_PKT_MAC_ERROR_M        0x1
#घोषणा TLSRX_HDR_PKT_MAC_ERROR_V(x)     ((x) << TLSRX_HDR_PKT_MAC_ERROR)
#घोषणा TLSRX_HDR_PKT_MAC_ERROR_G(x)     \
	(((x) >> S_TLSRX_HDR_PKT_MAC_ERROR_S) & TLSRX_HDR_PKT_MAC_ERROR_M)
#घोषणा TLSRX_HDR_PKT_MAC_ERROR_F        TLSRX_HDR_PKT_MAC_ERROR_V(1U)

#घोषणा TLSRX_HDR_PKT_ERROR_M           0x1F
#घोषणा CONTENT_TYPE_ERROR		0x7F

काष्ठा ulp_mem_rw अणु
	__be32 cmd;
	__be32 len16;             /* command length */
	__be32 dlen;              /* data length in 32-byte units */
	__be32 lock_addr;
पूर्ण;

काष्ठा tls_key_wr अणु
	__be32 op_to_compl;
	__be32 flowid_len16;
	__be32 ftid;
	u8   reneg_to_ग_लिखो_rx;
	u8   protocol;
	__be16 mfs;
पूर्ण;

काष्ठा tls_key_req अणु
	काष्ठा tls_key_wr wr;
	काष्ठा ulp_mem_rw req;
	काष्ठा ulptx_idata sc_imm;
पूर्ण;

/*
 * This lives in skb->cb and is used to chain WRs in a linked list.
 */
काष्ठा wr_skb_cb अणु
	काष्ठा l2t_skb_cb l2t;          /* reserve space क्रम l2t CB */
	काष्ठा sk_buff *next_wr;        /* next ग_लिखो request */
पूर्ण;

/* Per-skb backlog handler.  Run when a socket's backlog is processed. */
काष्ठा blog_skb_cb अणु
	व्योम (*backlog_rcv)(काष्ठा sock *sk, काष्ठा sk_buff *skb);
	काष्ठा chtls_dev *cdev;
पूर्ण;

/*
 * Similar to tcp_skb_cb but with ULP elements added to support TLS,
 * etc.
 */
काष्ठा ulp_skb_cb अणु
	काष्ठा wr_skb_cb wr;		/* reserve space क्रम ग_लिखो request */
	u16 flags;			/* TCP-like flags */
	u8 psh;
	u8 ulp_mode;			/* ULP mode/submode of sk_buff */
	u32 seq;			/* TCP sequence number */
	जोड़ अणु /* ULP-specअगरic fields */
		काष्ठा अणु
			u8  type;
			u8  ofld;
			u8  iv;
		पूर्ण tls;
	पूर्ण ulp;
पूर्ण;

#घोषणा ULP_SKB_CB(skb) ((काष्ठा ulp_skb_cb *)&((skb)->cb[0]))
#घोषणा BLOG_SKB_CB(skb) ((काष्ठा blog_skb_cb *)(skb)->cb)

/*
 * Flags क्रम ulp_skb_cb.flags.
 */
क्रमागत अणु
	ULPCB_FLAG_NEED_HDR  = 1 << 0,	/* packet needs a TX_DATA_WR header */
	ULPCB_FLAG_NO_APPEND = 1 << 1,	/* करोn't grow this skb */
	ULPCB_FLAG_BARRIER   = 1 << 2,	/* set TX_WAIT_IDLE after sending */
	ULPCB_FLAG_HOLD      = 1 << 3,	/* skb not पढ़ोy क्रम Tx yet */
	ULPCB_FLAG_COMPL     = 1 << 4,	/* request WR completion */
	ULPCB_FLAG_URG       = 1 << 5,	/* urgent data */
	ULPCB_FLAG_TLS_HDR   = 1 << 6,  /* payload with tls hdr */
	ULPCB_FLAG_NO_HDR    = 1 << 7,  /* not a ofld wr */
पूर्ण;

/* The ULP mode/submode of an skbuff */
#घोषणा skb_ulp_mode(skb)  (ULP_SKB_CB(skb)->ulp_mode)
#घोषणा TCP_PAGE(sk)   (sk->sk_frag.page)
#घोषणा TCP_OFF(sk)    (sk->sk_frag.offset)

अटल अंतरभूत काष्ठा chtls_dev *to_chtls_dev(काष्ठा tls_toe_device *tlsdev)
अणु
	वापस container_of(tlsdev, काष्ठा chtls_dev, tlsdev);
पूर्ण

अटल अंतरभूत व्योम csk_set_flag(काष्ठा chtls_sock *csk,
				क्रमागत csk_flags flag)
अणु
	__set_bit(flag, &csk->flags);
पूर्ण

अटल अंतरभूत व्योम csk_reset_flag(काष्ठा chtls_sock *csk,
				  क्रमागत csk_flags flag)
अणु
	__clear_bit(flag, &csk->flags);
पूर्ण

अटल अंतरभूत bool csk_conn_अंतरभूत(स्थिर काष्ठा chtls_sock *csk)
अणु
	वापस test_bit(CSK_CONN_INLINE, &csk->flags);
पूर्ण

अटल अंतरभूत पूर्णांक csk_flag(स्थिर काष्ठा sock *sk, क्रमागत csk_flags flag)
अणु
	काष्ठा chtls_sock *csk = rcu_dereference_sk_user_data(sk);

	अगर (!csk_conn_अंतरभूत(csk))
		वापस 0;
	वापस test_bit(flag, &csk->flags);
पूर्ण

अटल अंतरभूत पूर्णांक csk_flag_nochk(स्थिर काष्ठा chtls_sock *csk,
				 क्रमागत csk_flags flag)
अणु
	वापस test_bit(flag, &csk->flags);
पूर्ण

अटल अंतरभूत व्योम *cplhdr(काष्ठा sk_buff *skb)
अणु
	वापस skb->data;
पूर्ण

अटल अंतरभूत पूर्णांक is_neg_adv(अचिन्हित पूर्णांक status)
अणु
	वापस status == CPL_ERR_RTX_NEG_ADVICE ||
	       status == CPL_ERR_KEEPALV_NEG_ADVICE ||
	       status == CPL_ERR_PERSIST_NEG_ADVICE;
पूर्ण

अटल अंतरभूत व्योम process_cpl_msg(व्योम (*fn)(काष्ठा sock *, काष्ठा sk_buff *),
				   काष्ठा sock *sk,
				   काष्ठा sk_buff *skb)
अणु
	skb_reset_mac_header(skb);
	skb_reset_network_header(skb);
	skb_reset_transport_header(skb);

	bh_lock_sock(sk);
	अगर (unlikely(sock_owned_by_user(sk))) अणु
		BLOG_SKB_CB(skb)->backlog_rcv = fn;
		__sk_add_backlog(sk, skb);
	पूर्ण अन्यथा अणु
		fn(sk, skb);
	पूर्ण
	bh_unlock_sock(sk);
पूर्ण

अटल अंतरभूत व्योम chtls_sock_मुक्त(काष्ठा kref *ref)
अणु
	काष्ठा chtls_sock *csk = container_of(ref, काष्ठा chtls_sock,
					      kref);
	kमुक्त(csk);
पूर्ण

अटल अंतरभूत व्योम __chtls_sock_put(स्थिर अक्षर *fn, काष्ठा chtls_sock *csk)
अणु
	kref_put(&csk->kref, chtls_sock_मुक्त);
पूर्ण

अटल अंतरभूत व्योम __chtls_sock_get(स्थिर अक्षर *fn,
				    काष्ठा chtls_sock *csk)
अणु
	kref_get(&csk->kref);
पूर्ण

अटल अंतरभूत व्योम send_or_defer(काष्ठा sock *sk, काष्ठा tcp_sock *tp,
				 काष्ठा sk_buff *skb, पूर्णांक through_l2t)
अणु
	काष्ठा chtls_sock *csk = rcu_dereference_sk_user_data(sk);

	अगर (through_l2t) अणु
		/* send through L2T */
		cxgb4_l2t_send(csk->egress_dev, skb, csk->l2t_entry);
	पूर्ण अन्यथा अणु
		/* send directly */
		cxgb4_ofld_send(csk->egress_dev, skb);
	पूर्ण
पूर्ण

प्रकार पूर्णांक (*chtls_handler_func)(काष्ठा chtls_dev *, काष्ठा sk_buff *);
बाह्य chtls_handler_func chtls_handlers[NUM_CPL_CMDS];
व्योम chtls_install_cpl_ops(काष्ठा sock *sk);
पूर्णांक chtls_init_kmap(काष्ठा chtls_dev *cdev, काष्ठा cxgb4_lld_info *lldi);
व्योम chtls_listen_stop(काष्ठा chtls_dev *cdev, काष्ठा sock *sk);
पूर्णांक chtls_listen_start(काष्ठा chtls_dev *cdev, काष्ठा sock *sk);
व्योम chtls_बंद(काष्ठा sock *sk, दीर्घ समयout);
पूर्णांक chtls_disconnect(काष्ठा sock *sk, पूर्णांक flags);
व्योम chtls_shutकरोwn(काष्ठा sock *sk, पूर्णांक how);
व्योम chtls_destroy_sock(काष्ठा sock *sk);
पूर्णांक chtls_sendmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार size);
पूर्णांक chtls_recvmsg(काष्ठा sock *sk, काष्ठा msghdr *msg,
		  माप_प्रकार len, पूर्णांक nonblock, पूर्णांक flags, पूर्णांक *addr_len);
पूर्णांक chtls_sendpage(काष्ठा sock *sk, काष्ठा page *page,
		   पूर्णांक offset, माप_प्रकार size, पूर्णांक flags);
पूर्णांक send_tx_flowc_wr(काष्ठा sock *sk, पूर्णांक compl,
		     u32 snd_nxt, u32 rcv_nxt);
व्योम chtls_tcp_push(काष्ठा sock *sk, पूर्णांक flags);
पूर्णांक chtls_push_frames(काष्ठा chtls_sock *csk, पूर्णांक comp);
पूर्णांक chtls_set_tcb_tflag(काष्ठा sock *sk, अचिन्हित पूर्णांक bit_pos, पूर्णांक val);
व्योम chtls_set_tcb_field_rpl_skb(काष्ठा sock *sk, u16 word,
				 u64 mask, u64 val, u8 cookie,
				 पूर्णांक through_l2t);
पूर्णांक chtls_setkey(काष्ठा chtls_sock *csk, u32 keylen, u32 mode, पूर्णांक cipher_type);
व्योम chtls_set_quiesce_ctrl(काष्ठा sock *sk, पूर्णांक val);
व्योम skb_entail(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक flags);
अचिन्हित पूर्णांक keyid_to_addr(पूर्णांक start_addr, पूर्णांक keyid);
व्योम मुक्त_tls_keyid(काष्ठा sock *sk);
#पूर्ण_अगर
