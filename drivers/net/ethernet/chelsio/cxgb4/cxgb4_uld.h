<शैली गुरु>
/*
 * This file is part of the Chelsio T4 Ethernet driver क्रम Linux.
 *
 * Copyright (c) 2003-2016 Chelsio Communications, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_अघोषित __CXGB4_ULD_H
#घोषणा __CXGB4_ULD_H

#समावेश <linux/cache.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/atomic.h>
#समावेश <net/tls.h>
#समावेश "cxgb4.h"

#घोषणा MAX_ULD_QSETS 16
#घोषणा MAX_ULD_NPORTS 4

/* ulp_mem_io + ulptx_idata + payload + padding */
#घोषणा MAX_IMM_ULPTX_WR_LEN (32 + 8 + 256 + 8)

/* CPL message priority levels */
क्रमागत अणु
	CPL_PRIORITY_DATA     = 0,  /* data messages */
	CPL_PRIORITY_SETUP    = 1,  /* connection setup messages */
	CPL_PRIORITY_TEARDOWN = 0,  /* connection tearकरोwn messages */
	CPL_PRIORITY_LISTEN   = 1,  /* listen start/stop messages */
	CPL_PRIORITY_ACK      = 1,  /* RX ACK messages */
	CPL_PRIORITY_CONTROL  = 1   /* control messages */
पूर्ण;

#घोषणा INIT_TP_WR(w, tid) करो अणु \
	(w)->wr.wr_hi = htonl(FW_WR_OP_V(FW_TP_WR) | \
			      FW_WR_IMMDLEN_V(माप(*w) - माप(w->wr))); \
	(w)->wr.wr_mid = htonl(FW_WR_LEN16_V(DIV_ROUND_UP(माप(*w), 16)) | \
			       FW_WR_FLOWID_V(tid)); \
	(w)->wr.wr_lo = cpu_to_be64(0); \
पूर्ण जबतक (0)

#घोषणा INIT_TP_WR_CPL(w, cpl, tid) करो अणु \
	INIT_TP_WR(w, tid); \
	OPCODE_TID(w) = htonl(MK_OPCODE_TID(cpl, tid)); \
पूर्ण जबतक (0)

#घोषणा INIT_ULPTX_WR(w, wrlen, atomic, tid) करो अणु \
	(w)->wr.wr_hi = htonl(FW_WR_OP_V(FW_ULPTX_WR) | \
			      FW_WR_ATOMIC_V(atomic)); \
	(w)->wr.wr_mid = htonl(FW_WR_LEN16_V(DIV_ROUND_UP(wrlen, 16)) | \
			       FW_WR_FLOWID_V(tid)); \
	(w)->wr.wr_lo = cpu_to_be64(0); \
पूर्ण जबतक (0)

/* Special asynchronous notअगरication message */
#घोषणा CXGB4_MSG_AN ((व्योम *)1)
#घोषणा TX_ULD(uld)(((uld) != CXGB4_ULD_CRYPTO) ? CXGB4_TX_OFLD :\
		      CXGB4_TX_CRYPTO)

काष्ठा serv_entry अणु
	व्योम *data;
पूर्ण;

जोड़ aखोलो_entry अणु
	व्योम *data;
	जोड़ aखोलो_entry *next;
पूर्ण;

काष्ठा eotid_entry अणु
	व्योम *data;
पूर्ण;

/*
 * Holds the size, base address, मुक्त list start, etc of the TID, server TID,
 * and active-खोलो TID tables.  The tables themselves are allocated dynamically.
 */
काष्ठा tid_info अणु
	व्योम **tid_tab;
	अचिन्हित पूर्णांक tid_base;
	अचिन्हित पूर्णांक ntids;

	काष्ठा serv_entry *stid_tab;
	अचिन्हित दीर्घ *stid_bmap;
	अचिन्हित पूर्णांक nstids;
	अचिन्हित पूर्णांक stid_base;

	अचिन्हित पूर्णांक nhash;
	अचिन्हित पूर्णांक hash_base;

	जोड़ aखोलो_entry *atid_tab;
	अचिन्हित पूर्णांक natids;
	अचिन्हित पूर्णांक atid_base;

	काष्ठा filter_entry *hpftid_tab;
	अचिन्हित दीर्घ *hpftid_bmap;
	अचिन्हित पूर्णांक nhpftids;
	अचिन्हित पूर्णांक hpftid_base;

	काष्ठा filter_entry *ftid_tab;
	अचिन्हित दीर्घ *ftid_bmap;
	अचिन्हित पूर्णांक nftids;
	अचिन्हित पूर्णांक ftid_base;
	अचिन्हित पूर्णांक aftid_base;
	अचिन्हित पूर्णांक aftid_end;
	/* Server filter region */
	अचिन्हित पूर्णांक sftid_base;
	अचिन्हित पूर्णांक nsftids;

	spinlock_t atid_lock ____cacheline_aligned_in_smp;
	जोड़ aखोलो_entry *aमुक्त;
	अचिन्हित पूर्णांक atids_in_use;

	spinlock_t stid_lock;
	अचिन्हित पूर्णांक stids_in_use;
	अचिन्हित पूर्णांक v6_stids_in_use;
	अचिन्हित पूर्णांक sftids_in_use;

	/* ETHOFLD range */
	काष्ठा eotid_entry *eotid_tab;
	अचिन्हित दीर्घ *eotid_bmap;
	अचिन्हित पूर्णांक eotid_base;
	अचिन्हित पूर्णांक neotids;

	/* TIDs in the TCAM */
	atomic_t tids_in_use;
	/* TIDs in the HASH */
	atomic_t hash_tids_in_use;
	atomic_t conns_in_use;
	/* ETHOFLD TIDs used क्रम rate limiting */
	atomic_t eotids_in_use;

	/* lock क्रम setting/clearing filter biपंचांगap */
	spinlock_t ftid_lock;

	अचिन्हित पूर्णांक tc_hash_tids_max_prio;
पूर्ण;

अटल अंतरभूत व्योम *lookup_tid(स्थिर काष्ठा tid_info *t, अचिन्हित पूर्णांक tid)
अणु
	tid -= t->tid_base;
	वापस tid < t->ntids ? t->tid_tab[tid] : शून्य;
पूर्ण

अटल अंतरभूत bool tid_out_of_range(स्थिर काष्ठा tid_info *t, अचिन्हित पूर्णांक tid)
अणु
	वापस ((tid - t->tid_base) >= t->ntids);
पूर्ण

अटल अंतरभूत व्योम *lookup_atid(स्थिर काष्ठा tid_info *t, अचिन्हित पूर्णांक atid)
अणु
	वापस atid < t->natids ? t->atid_tab[atid].data : शून्य;
पूर्ण

अटल अंतरभूत व्योम *lookup_stid(स्थिर काष्ठा tid_info *t, अचिन्हित पूर्णांक stid)
अणु
	/* Is it a server filter TID? */
	अगर (t->nsftids && (stid >= t->sftid_base)) अणु
		stid -= t->sftid_base;
		stid += t->nstids;
	पूर्ण अन्यथा अणु
		stid -= t->stid_base;
	पूर्ण

	वापस stid < (t->nstids + t->nsftids) ? t->stid_tab[stid].data : शून्य;
पूर्ण

अटल अंतरभूत व्योम cxgb4_insert_tid(काष्ठा tid_info *t, व्योम *data,
				    अचिन्हित पूर्णांक tid, अचिन्हित लघु family)
अणु
	t->tid_tab[tid - t->tid_base] = data;
	अगर (t->hash_base && (tid >= t->hash_base)) अणु
		अगर (family == AF_INET6)
			atomic_add(2, &t->hash_tids_in_use);
		अन्यथा
			atomic_inc(&t->hash_tids_in_use);
	पूर्ण अन्यथा अणु
		अगर (family == AF_INET6)
			atomic_add(2, &t->tids_in_use);
		अन्यथा
			atomic_inc(&t->tids_in_use);
	पूर्ण
	atomic_inc(&t->conns_in_use);
पूर्ण

अटल अंतरभूत काष्ठा eotid_entry *cxgb4_lookup_eotid(काष्ठा tid_info *t,
						     u32 eotid)
अणु
	वापस eotid < t->neotids ? &t->eotid_tab[eotid] : शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक cxgb4_get_मुक्त_eotid(काष्ठा tid_info *t)
अणु
	पूर्णांक eotid;

	eotid = find_first_zero_bit(t->eotid_bmap, t->neotids);
	अगर (eotid >= t->neotids)
		eotid = -1;

	वापस eotid;
पूर्ण

अटल अंतरभूत व्योम cxgb4_alloc_eotid(काष्ठा tid_info *t, u32 eotid, व्योम *data)
अणु
	set_bit(eotid, t->eotid_bmap);
	t->eotid_tab[eotid].data = data;
	atomic_inc(&t->eotids_in_use);
पूर्ण

अटल अंतरभूत व्योम cxgb4_मुक्त_eotid(काष्ठा tid_info *t, u32 eotid)
अणु
	clear_bit(eotid, t->eotid_bmap);
	t->eotid_tab[eotid].data = शून्य;
	atomic_dec(&t->eotids_in_use);
पूर्ण

पूर्णांक cxgb4_alloc_atid(काष्ठा tid_info *t, व्योम *data);
पूर्णांक cxgb4_alloc_stid(काष्ठा tid_info *t, पूर्णांक family, व्योम *data);
पूर्णांक cxgb4_alloc_sftid(काष्ठा tid_info *t, पूर्णांक family, व्योम *data);
व्योम cxgb4_मुक्त_atid(काष्ठा tid_info *t, अचिन्हित पूर्णांक atid);
व्योम cxgb4_मुक्त_stid(काष्ठा tid_info *t, अचिन्हित पूर्णांक stid, पूर्णांक family);
व्योम cxgb4_हटाओ_tid(काष्ठा tid_info *t, अचिन्हित पूर्णांक qid, अचिन्हित पूर्णांक tid,
		      अचिन्हित लघु family);
काष्ठा in6_addr;

पूर्णांक cxgb4_create_server(स्थिर काष्ठा net_device *dev, अचिन्हित पूर्णांक stid,
			__be32 sip, __be16 sport, __be16 vlan,
			अचिन्हित पूर्णांक queue);
पूर्णांक cxgb4_create_server6(स्थिर काष्ठा net_device *dev, अचिन्हित पूर्णांक stid,
			 स्थिर काष्ठा in6_addr *sip, __be16 sport,
			 अचिन्हित पूर्णांक queue);
पूर्णांक cxgb4_हटाओ_server(स्थिर काष्ठा net_device *dev, अचिन्हित पूर्णांक stid,
			अचिन्हित पूर्णांक queue, bool ipv6);
पूर्णांक cxgb4_create_server_filter(स्थिर काष्ठा net_device *dev, अचिन्हित पूर्णांक stid,
			       __be32 sip, __be16 sport, __be16 vlan,
			       अचिन्हित पूर्णांक queue,
			       अचिन्हित अक्षर port, अचिन्हित अक्षर mask);
पूर्णांक cxgb4_हटाओ_server_filter(स्थिर काष्ठा net_device *dev, अचिन्हित पूर्णांक stid,
			       अचिन्हित पूर्णांक queue, bool ipv6);

/* Filter operation context to allow callers of cxgb4_set_filter() and
 * cxgb4_del_filter() to रुको क्रम an asynchronous completion.
 */
काष्ठा filter_ctx अणु
	काष्ठा completion completion;	/* completion rendezvous */
	व्योम *closure;			/* caller's opaque inक्रमmation */
	पूर्णांक result;			/* result of operation */
	u32 tid;			/* to store tid */
पूर्ण;

काष्ठा chcr_ktls अणु
	refcount_t ktls_refcount;
पूर्ण;

काष्ठा ch_filter_specअगरication;

पूर्णांक cxgb4_get_मुक्त_ftid(काष्ठा net_device *dev, u8 family, bool hash_en,
			u32 tc_prio);
पूर्णांक __cxgb4_set_filter(काष्ठा net_device *dev, पूर्णांक filter_id,
		       काष्ठा ch_filter_specअगरication *fs,
		       काष्ठा filter_ctx *ctx);
पूर्णांक __cxgb4_del_filter(काष्ठा net_device *dev, पूर्णांक filter_id,
		       काष्ठा ch_filter_specअगरication *fs,
		       काष्ठा filter_ctx *ctx);
पूर्णांक cxgb4_set_filter(काष्ठा net_device *dev, पूर्णांक filter_id,
		     काष्ठा ch_filter_specअगरication *fs);
पूर्णांक cxgb4_del_filter(काष्ठा net_device *dev, पूर्णांक filter_id,
		     काष्ठा ch_filter_specअगरication *fs);
पूर्णांक cxgb4_get_filter_counters(काष्ठा net_device *dev, अचिन्हित पूर्णांक fidx,
			      u64 *hitcnt, u64 *bytecnt, bool hash);

अटल अंतरभूत व्योम set_wr_txq(काष्ठा sk_buff *skb, पूर्णांक prio, पूर्णांक queue)
अणु
	skb_set_queue_mapping(skb, (queue << 1) | prio);
पूर्ण

क्रमागत cxgb4_uld अणु
	CXGB4_ULD_INIT,
	CXGB4_ULD_RDMA,
	CXGB4_ULD_ISCSI,
	CXGB4_ULD_ISCSIT,
	CXGB4_ULD_CRYPTO,
	CXGB4_ULD_IPSEC,
	CXGB4_ULD_TLS,
	CXGB4_ULD_KTLS,
	CXGB4_ULD_MAX
पूर्ण;

क्रमागत cxgb4_tx_uld अणु
	CXGB4_TX_OFLD,
	CXGB4_TX_CRYPTO,
	CXGB4_TX_MAX
पूर्ण;

क्रमागत cxgb4_txq_type अणु
	CXGB4_TXQ_ETH,
	CXGB4_TXQ_ULD,
	CXGB4_TXQ_CTRL,
	CXGB4_TXQ_MAX
पूर्ण;

क्रमागत cxgb4_state अणु
	CXGB4_STATE_UP,
	CXGB4_STATE_START_RECOVERY,
	CXGB4_STATE_DOWN,
	CXGB4_STATE_DETACH,
	CXGB4_STATE_FATAL_ERROR
पूर्ण;

क्रमागत cxgb4_control अणु
	CXGB4_CONTROL_DB_FULL,
	CXGB4_CONTROL_DB_EMPTY,
	CXGB4_CONTROL_DB_DROP,
पूर्ण;

काष्ठा adapter;
काष्ठा pci_dev;
काष्ठा l2t_data;
काष्ठा net_device;
काष्ठा pkt_gl;
काष्ठा tp_tcp_stats;
काष्ठा t4_lro_mgr;

काष्ठा cxgb4_range अणु
	अचिन्हित पूर्णांक start;
	अचिन्हित पूर्णांक size;
पूर्ण;

काष्ठा cxgb4_virt_res अणु                      /* भवized HW resources */
	काष्ठा cxgb4_range ddp;
	काष्ठा cxgb4_range iscsi;
	काष्ठा cxgb4_range stag;
	काष्ठा cxgb4_range rq;
	काष्ठा cxgb4_range srq;
	काष्ठा cxgb4_range pbl;
	काष्ठा cxgb4_range qp;
	काष्ठा cxgb4_range cq;
	काष्ठा cxgb4_range ocq;
	काष्ठा cxgb4_range key;
	अचिन्हित पूर्णांक ncrypto_fc;
	काष्ठा cxgb4_range ppod_edram;
पूर्ण;

#अगर IS_ENABLED(CONFIG_CHELSIO_TLS_DEVICE)
काष्ठा ch_ktls_port_stats_debug अणु
	atomic64_t ktls_tx_connection_खोलो;
	atomic64_t ktls_tx_connection_fail;
	atomic64_t ktls_tx_connection_बंद;
	atomic64_t ktls_tx_encrypted_packets;
	atomic64_t ktls_tx_encrypted_bytes;
	atomic64_t ktls_tx_ctx;
	atomic64_t ktls_tx_ooo;
	atomic64_t ktls_tx_skip_no_sync_data;
	atomic64_t ktls_tx_drop_no_sync_data;
	atomic64_t ktls_tx_drop_bypass_req;
पूर्ण;

काष्ठा ch_ktls_stats_debug अणु
	काष्ठा ch_ktls_port_stats_debug ktls_port[MAX_ULD_NPORTS];
	atomic64_t ktls_tx_send_records;
	atomic64_t ktls_tx_end_pkts;
	atomic64_t ktls_tx_start_pkts;
	atomic64_t ktls_tx_middle_pkts;
	atomic64_t ktls_tx_retransmit_pkts;
	atomic64_t ktls_tx_complete_pkts;
	atomic64_t ktls_tx_trimmed_pkts;
	atomic64_t ktls_tx_fallback;
पूर्ण;
#पूर्ण_अगर

काष्ठा chcr_stats_debug अणु
	atomic_t cipher_rqst;
	atomic_t digest_rqst;
	atomic_t aead_rqst;
	atomic_t complete;
	atomic_t error;
	atomic_t fallback;
	atomic_t tls_pdu_tx;
	atomic_t tls_pdu_rx;
	atomic_t tls_key;
पूर्ण;

#अगर IS_ENABLED(CONFIG_CHELSIO_IPSEC_INLINE)
काष्ठा ch_ipsec_stats_debug अणु
	atomic_t ipsec_cnt;
पूर्ण;
#पूर्ण_अगर

#घोषणा OCQ_WIN_OFFSET(pdev, vres) \
	(pci_resource_len((pdev), 2) - roundup_घात_of_two((vres)->ocq.size))

/*
 * Block of inक्रमmation the LLD provides to ULDs attaching to a device.
 */
काष्ठा cxgb4_lld_info अणु
	काष्ठा pci_dev *pdev;                /* associated PCI device */
	काष्ठा l2t_data *l2t;                /* L2 table */
	काष्ठा tid_info *tids;               /* TID table */
	काष्ठा net_device **ports;           /* device ports */
	स्थिर काष्ठा cxgb4_virt_res *vr;     /* assorted HW resources */
	स्थिर अचिन्हित लघु *mtus;          /* MTU table */
	स्थिर अचिन्हित लघु *rxq_ids;       /* the ULD's Rx queue ids */
	स्थिर अचिन्हित लघु *ciq_ids;       /* the ULD's concentrator IQ ids */
	अचिन्हित लघु nrxq;                 /* # of Rx queues */
	अचिन्हित लघु ntxq;                 /* # of Tx queues */
	अचिन्हित लघु nciq;		     /* # of concentrator IQ */
	अचिन्हित अक्षर nchan:4;               /* # of channels */
	अचिन्हित अक्षर nports:4;              /* # of ports */
	अचिन्हित अक्षर wr_cred;               /* WR 16-byte credits */
	अचिन्हित अक्षर adapter_type;          /* type of adapter */
	अचिन्हित अक्षर fw_api_ver;            /* FW API version */
	अचिन्हित अक्षर crypto;                /* crypto support */
	अचिन्हित पूर्णांक fw_vers;                /* FW version */
	अचिन्हित पूर्णांक iscsi_iolen;            /* iSCSI max I/O length */
	अचिन्हित पूर्णांक cclk_ps;                /* Core घड़ी period in psec */
	अचिन्हित लघु udb_density;          /* # of user DB/page */
	अचिन्हित लघु ucq_density;          /* # of user CQs/page */
	अचिन्हित पूर्णांक sge_host_page_size;     /* SGE host page size */
	अचिन्हित लघु filt_mode;            /* filter optional components */
	अचिन्हित लघु tx_modq[NCHAN];       /* maps each tx channel to a */
					     /* scheduler queue */
	व्योम __iomem *gts_reg;               /* address of GTS रेजिस्टर */
	व्योम __iomem *db_reg;                /* address of kernel करोorbell */
	पूर्णांक dbfअगरo_पूर्णांक_thresh;		     /* करोorbell fअगरo पूर्णांक threshold */
	अचिन्हित पूर्णांक sge_ingpadboundary;     /* SGE ingress padding boundary */
	अचिन्हित पूर्णांक sge_egrstatuspagesize;  /* SGE egress status page size */
	अचिन्हित पूर्णांक sge_pktshअगरt;           /* Padding between CPL and */
					     /*	packet data */
	अचिन्हित पूर्णांक pf;		     /* Physical Function we're using */
	bool enable_fw_ofld_conn;            /* Enable connection through fw */
					     /* WR */
	अचिन्हित पूर्णांक max_ordird_qp;          /* Max ORD/IRD depth per RDMA QP */
	अचिन्हित पूर्णांक max_ird_adapter;        /* Max IRD memory per adapter */
	bool ulptx_memग_लिखो_dsgl;            /* use of T5 DSGL allowed */
	अचिन्हित पूर्णांक iscsi_tagmask;	     /* iscsi ddp tag mask */
	अचिन्हित पूर्णांक iscsi_pgsz_order;	     /* iscsi ddp page size orders */
	अचिन्हित पूर्णांक iscsi_llimit;	     /* chip's iscsi region llimit */
	अचिन्हित पूर्णांक ulp_crypto;             /* crypto lookaside support */
	व्योम **iscsi_ppm;		     /* iscsi page pod manager */
	पूर्णांक nodeid;			     /* device numa node id */
	bool fr_nsmr_tpte_wr_support;	     /* FW supports FR_NSMR_TPTE_WR */
	bool ग_लिखो_w_imm_support;         /* FW supports WRITE_WITH_IMMEDIATE */
	bool ग_लिखो_cmpl_support;             /* FW supports WRITE_CMPL WR */
पूर्ण;

काष्ठा cxgb4_uld_info अणु
	अक्षर name[IFNAMSIZ];
	व्योम *handle;
	अचिन्हित पूर्णांक nrxq;
	अचिन्हित पूर्णांक rxq_size;
	अचिन्हित पूर्णांक ntxq;
	bool ciq;
	bool lro;
	व्योम *(*add)(स्थिर काष्ठा cxgb4_lld_info *p);
	पूर्णांक (*rx_handler)(व्योम *handle, स्थिर __be64 *rsp,
			  स्थिर काष्ठा pkt_gl *gl);
	पूर्णांक (*state_change)(व्योम *handle, क्रमागत cxgb4_state new_state);
	पूर्णांक (*control)(व्योम *handle, क्रमागत cxgb4_control control, ...);
	पूर्णांक (*lro_rx_handler)(व्योम *handle, स्थिर __be64 *rsp,
			      स्थिर काष्ठा pkt_gl *gl,
			      काष्ठा t4_lro_mgr *lro_mgr,
			      काष्ठा napi_काष्ठा *napi);
	व्योम (*lro_flush)(काष्ठा t4_lro_mgr *);
	पूर्णांक (*tx_handler)(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
#अगर IS_ENABLED(CONFIG_CHELSIO_TLS_DEVICE)
	स्थिर काष्ठा tlsdev_ops *tlsdev_ops;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_XFRM_OFFLOAD)
	स्थिर काष्ठा xfrmdev_ops *xfrmdev_ops;
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत bool cxgb4_is_ktls_skb(काष्ठा sk_buff *skb)
अणु
	वापस skb->sk && tls_is_sk_tx_device_offloaded(skb->sk);
पूर्ण

व्योम cxgb4_uld_enable(काष्ठा adapter *adap);
व्योम cxgb4_रेजिस्टर_uld(क्रमागत cxgb4_uld type, स्थिर काष्ठा cxgb4_uld_info *p);
पूर्णांक cxgb4_unरेजिस्टर_uld(क्रमागत cxgb4_uld type);
पूर्णांक cxgb4_ofld_send(काष्ठा net_device *dev, काष्ठा sk_buff *skb);
पूर्णांक cxgb4_immdata_send(काष्ठा net_device *dev, अचिन्हित पूर्णांक idx,
		       स्थिर व्योम *src, अचिन्हित पूर्णांक len);
पूर्णांक cxgb4_crypto_send(काष्ठा net_device *dev, काष्ठा sk_buff *skb);
अचिन्हित पूर्णांक cxgb4_dbfअगरo_count(स्थिर काष्ठा net_device *dev, पूर्णांक lpfअगरo);
अचिन्हित पूर्णांक cxgb4_port_chan(स्थिर काष्ठा net_device *dev);
अचिन्हित पूर्णांक cxgb4_port_e2cchan(स्थिर काष्ठा net_device *dev);
अचिन्हित पूर्णांक cxgb4_port_viid(स्थिर काष्ठा net_device *dev);
अचिन्हित पूर्णांक cxgb4_tp_smt_idx(क्रमागत chip_type chip, अचिन्हित पूर्णांक viid);
अचिन्हित पूर्णांक cxgb4_port_idx(स्थिर काष्ठा net_device *dev);
अचिन्हित पूर्णांक cxgb4_best_mtu(स्थिर अचिन्हित लघु *mtus, अचिन्हित लघु mtu,
			    अचिन्हित पूर्णांक *idx);
अचिन्हित पूर्णांक cxgb4_best_aligned_mtu(स्थिर अचिन्हित लघु *mtus,
				    अचिन्हित लघु header_size,
				    अचिन्हित लघु data_size_max,
				    अचिन्हित लघु data_size_align,
				    अचिन्हित पूर्णांक *mtu_idxp);
व्योम cxgb4_get_tcp_stats(काष्ठा pci_dev *pdev, काष्ठा tp_tcp_stats *v4,
			 काष्ठा tp_tcp_stats *v6);
व्योम cxgb4_iscsi_init(काष्ठा net_device *dev, अचिन्हित पूर्णांक tag_mask,
		      स्थिर अचिन्हित पूर्णांक *pgsz_order);
काष्ठा sk_buff *cxgb4_pktgl_to_skb(स्थिर काष्ठा pkt_gl *gl,
				   अचिन्हित पूर्णांक skb_len, अचिन्हित पूर्णांक pull_len);
पूर्णांक cxgb4_sync_txq_pidx(काष्ठा net_device *dev, u16 qid, u16 pidx, u16 size);
पूर्णांक cxgb4_flush_eq_cache(काष्ठा net_device *dev);
पूर्णांक cxgb4_पढ़ो_tpte(काष्ठा net_device *dev, u32 stag, __be32 *tpte);
u64 cxgb4_पढ़ो_sge_बारtamp(काष्ठा net_device *dev);

क्रमागत cxgb4_bar2_qtype अणु CXGB4_BAR2_QTYPE_EGRESS, CXGB4_BAR2_QTYPE_INGRESS पूर्ण;
पूर्णांक cxgb4_bar2_sge_qregs(काष्ठा net_device *dev,
			 अचिन्हित पूर्णांक qid,
			 क्रमागत cxgb4_bar2_qtype qtype,
			 पूर्णांक user,
			 u64 *pbar2_qoffset,
			 अचिन्हित पूर्णांक *pbar2_qid);

#पूर्ण_अगर  /* !__CXGB4_ULD_H */
