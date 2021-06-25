<शैली गुरु>
/*
 * Copyright(c) 2015 - 2018 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#अगर_अघोषित HFI1_VERBS_H
#घोषणा HFI1_VERBS_H

#समावेश <linux/types.h>
#समावेश <linux/seqlock.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kref.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/completion.h>
#समावेश <linux/slab.h>
#समावेश <rdma/ib_pack.h>
#समावेश <rdma/ib_user_verbs.h>
#समावेश <rdma/ib_mad.h>
#समावेश <rdma/ib_hdrs.h>
#समावेश <rdma/rdma_vt.h>
#समावेश <rdma/rdmavt_qp.h>
#समावेश <rdma/rdmavt_cq.h>

काष्ठा hfi1_ctxtdata;
काष्ठा hfi1_pportdata;
काष्ठा hfi1_devdata;
काष्ठा hfi1_packet;

#समावेश "iowait.h"
#समावेश "tid_rdma.h"
#समावेश "opfn.h"

#घोषणा HFI1_MAX_RDMA_ATOMIC     16

/*
 * Increment this value अगर any changes that अवरोध userspace ABI
 * compatibility are made.
 */
#घोषणा HFI1_UVERBS_ABI_VERSION       2

/* IB Perक्रमmance Manager status values */
#घोषणा IB_PMA_SAMPLE_STATUS_DONE       0x00
#घोषणा IB_PMA_SAMPLE_STATUS_STARTED    0x01
#घोषणा IB_PMA_SAMPLE_STATUS_RUNNING    0x02

/* Mandatory IB perक्रमmance counter select values. */
#घोषणा IB_PMA_PORT_XMIT_DATA   cpu_to_be16(0x0001)
#घोषणा IB_PMA_PORT_RCV_DATA    cpu_to_be16(0x0002)
#घोषणा IB_PMA_PORT_XMIT_PKTS   cpu_to_be16(0x0003)
#घोषणा IB_PMA_PORT_RCV_PKTS    cpu_to_be16(0x0004)
#घोषणा IB_PMA_PORT_XMIT_WAIT   cpu_to_be16(0x0005)

#घोषणा HFI1_VENDOR_IPG		cpu_to_be16(0xFFA0)

#घोषणा IB_DEFAULT_GID_PREFIX	cpu_to_be64(0xfe80000000000000ULL)
#घोषणा OPA_BTH_MIG_REQ		BIT(31)

#घोषणा RC_OP(x) IB_OPCODE_RC_##x
#घोषणा UC_OP(x) IB_OPCODE_UC_##x

/* flags passed by hfi1_ib_rcv() */
क्रमागत अणु
	HFI1_HAS_GRH = (1 << 0),
पूर्ण;

#घोषणा LRH_16B_BYTES (माप_field(काष्ठा hfi1_16b_header, lrh))
#घोषणा LRH_16B_DWORDS (LRH_16B_BYTES / माप(u32))
#घोषणा LRH_9B_BYTES (माप_field(काष्ठा ib_header, lrh))
#घोषणा LRH_9B_DWORDS (LRH_9B_BYTES / माप(u32))

/* 24Bits क्रम qpn, upper 8Bits reserved */
काष्ठा opa_16b_mgmt अणु
	__be32 dest_qpn;
	__be32 src_qpn;
पूर्ण;

काष्ठा hfi1_16b_header अणु
	u32 lrh[4];
	जोड़ अणु
		काष्ठा अणु
			काष्ठा ib_grh grh;
			काष्ठा ib_other_headers oth;
		पूर्ण l;
		काष्ठा ib_other_headers oth;
		काष्ठा opa_16b_mgmt mgmt;
	पूर्ण u;
पूर्ण __packed;

काष्ठा hfi1_opa_header अणु
	जोड़ अणु
		काष्ठा ib_header ibh; /* 9B header */
		काष्ठा hfi1_16b_header opah; /* 16B header */
	पूर्ण;
	u8 hdr_type; /* 9B or 16B */
पूर्ण __packed;

काष्ठा hfi1_ahg_info अणु
	u32 ahgdesc[2];
	u16 tx_flags;
	u8 ahgcount;
	u8 ahgidx;
पूर्ण;

काष्ठा hfi1_sdma_header अणु
	__le64 pbc;
	काष्ठा hfi1_opa_header hdr;
पूर्ण __packed;

/*
 * hfi1 specअगरic data काष्ठाures that will be hidden from rvt after the queue
 * pair is made common
 */
काष्ठा hfi1_qp_priv अणु
	काष्ठा hfi1_ahg_info *s_ahg;              /* ahg info क्रम next header */
	काष्ठा sdma_engine *s_sde;                /* current sde */
	काष्ठा send_context *s_sendcontext;       /* current sendcontext */
	काष्ठा hfi1_ctxtdata *rcd;                /* QP's receive context */
	काष्ठा page **pages;                      /* क्रम TID page scan */
	u32 tid_enqueue;                          /* saved when tid रुकोed */
	u8 s_sc;		                  /* SC[0..4] क्रम next packet */
	काष्ठा ioरुको s_ioरुको;
	काष्ठा समयr_list s_tid_समयr;            /* क्रम timing tid रुको */
	काष्ठा समयr_list s_tid_retry_समयr;      /* क्रम timing tid ack */
	काष्ठा list_head tid_रुको;                /* क्रम queueing tid space */
	काष्ठा hfi1_opfn_data opfn;
	काष्ठा tid_flow_state flow_state;
	काष्ठा tid_rdma_qp_params tid_rdma;
	काष्ठा rvt_qp *owner;
	u16 s_running_pkt_size;
	u8 hdr_type; /* 9B or 16B */
	काष्ठा rvt_sge_state tid_ss;       /* SGE state poपूर्णांकer क्रम 2nd leg */
	atomic_t n_requests;               /* # of TID RDMA requests in the */
					   /* queue */
	atomic_t n_tid_requests;            /* # of sent TID RDMA requests */
	अचिन्हित दीर्घ tid_समयr_समयout_jअगरfies;
	अचिन्हित दीर्घ tid_retry_समयout_jअगरfies;

	/* variables क्रम the TID RDMA SE state machine */
	u8 s_state;
	u8 s_retry;
	u8 rnr_nak_state;       /* RNR NAK state */
	u8 s_nak_state;
	u32 s_nak_psn;
	u32 s_flags;
	u32 s_tid_cur;
	u32 s_tid_head;
	u32 s_tid_tail;
	u32 r_tid_head;     /* Most recently added TID RDMA request */
	u32 r_tid_tail;     /* the last completed TID RDMA request */
	u32 r_tid_ack;      /* the TID RDMA request to be ACK'ed */
	u32 r_tid_alloc;    /* Request क्रम which we are allocating resources */
	u32 pending_tid_w_segs; /* Num of pending tid ग_लिखो segments */
	u32 pending_tid_w_resp; /* Num of pending tid ग_लिखो responses */
	u32 alloc_w_segs;       /* Number of segments क्रम which ग_लिखो */
			       /* resources have been allocated क्रम this QP */

	/* For TID RDMA READ */
	u32 tid_r_reqs;         /* Num of tid पढ़ोs requested */
	u32 tid_r_comp;         /* Num of tid पढ़ोs completed */
	u32 pending_tid_r_segs; /* Num of pending tid पढ़ो segments */
	u16 pkts_ps;            /* packets per segment */
	u8 समयout_shअगरt;       /* account क्रम number of packets per segment */

	u32 r_next_psn_kdeth;
	u32 r_next_psn_kdeth_save;
	u32 s_resync_psn;
	u8 sync_pt;           /* Set when QP reaches sync poपूर्णांक */
	u8 resync;
पूर्ण;

#घोषणा HFI1_QP_WQE_INVALID   ((u32)-1)

काष्ठा hfi1_swqe_priv अणु
	काष्ठा tid_rdma_request tid_req;
	काष्ठा rvt_sge_state ss;  /* Used क्रम TID RDMA READ Request */
पूर्ण;

काष्ठा hfi1_ack_priv अणु
	काष्ठा rvt_sge_state ss;               /* used क्रम TID WRITE RESP */
	काष्ठा tid_rdma_request tid_req;
पूर्ण;

/*
 * This काष्ठाure is used to hold commonly lookedup and computed values during
 * the send engine progress.
 */
काष्ठा ioरुको_work;
काष्ठा hfi1_pkt_state अणु
	काष्ठा hfi1_ibdev *dev;
	काष्ठा hfi1_ibport *ibp;
	काष्ठा hfi1_pportdata *ppd;
	काष्ठा verbs_txreq *s_txreq;
	काष्ठा ioरुको_work *रुको;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ समयout;
	अचिन्हित दीर्घ समयout_पूर्णांक;
	पूर्णांक cpu;
	u8 opcode;
	bool in_thपढ़ो;
	bool pkts_sent;
पूर्ण;

#घोषणा HFI1_PSN_CREDIT  16

काष्ठा hfi1_opcode_stats अणु
	u64 n_packets;          /* number of packets */
	u64 n_bytes;            /* total number of bytes */
पूर्ण;

काष्ठा hfi1_opcode_stats_perctx अणु
	काष्ठा hfi1_opcode_stats stats[256];
पूर्ण;

अटल अंतरभूत व्योम inc_opstats(
	u32 tlen,
	काष्ठा hfi1_opcode_stats *stats)
अणु
#अगर_घोषित CONFIG_DEBUG_FS
	stats->n_bytes += tlen;
	stats->n_packets++;
#पूर्ण_अगर
पूर्ण

काष्ठा hfi1_ibport अणु
	काष्ठा rvt_qp __rcu *qp[2];
	काष्ठा rvt_ibport rvp;

	/* the first 16 entries are sl_to_vl क्रम !OPA */
	u8 sl_to_sc[32];
	u8 sc_to_sl[32];
पूर्ण;

काष्ठा hfi1_ibdev अणु
	काष्ठा rvt_dev_info rdi; /* Must be first */

	/* QP numbers are shared by all IB ports */
	/* protect txरुको list */
	seqlock_t txरुको_lock ____cacheline_aligned_in_smp;
	काष्ठा list_head txरुको;        /* list क्रम रुको verbs_txreq */
	काष्ठा list_head memरुको;       /* list क्रम रुको kernel memory */
	काष्ठा kmem_cache *verbs_txreq_cache;
	u64 n_txरुको;
	u64 n_kmem_रुको;
	u64 n_tidरुको;

	/* protect ioरुको lists */
	seqlock_t ioरुको_lock ____cacheline_aligned_in_smp;
	u64 n_pioरुको;
	u64 n_piodrain;
	काष्ठा समयr_list mem_समयr;

#अगर_घोषित CONFIG_DEBUG_FS
	/* per HFI debugfs */
	काष्ठा dentry *hfi1_ibdev_dbg;
	/* per HFI symlinks to above */
	काष्ठा dentry *hfi1_ibdev_link;
#अगर_घोषित CONFIG_FAULT_INJECTION
	काष्ठा fault *fault;
#पूर्ण_अगर
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत काष्ठा hfi1_ibdev *to_idev(काष्ठा ib_device *ibdev)
अणु
	काष्ठा rvt_dev_info *rdi;

	rdi = container_of(ibdev, काष्ठा rvt_dev_info, ibdev);
	वापस container_of(rdi, काष्ठा hfi1_ibdev, rdi);
पूर्ण

अटल अंतरभूत काष्ठा rvt_qp *ioरुको_to_qp(काष्ठा ioरुको *s_ioरुको)
अणु
	काष्ठा hfi1_qp_priv *priv;

	priv = container_of(s_ioरुको, काष्ठा hfi1_qp_priv, s_ioरुको);
	वापस priv->owner;
पूर्ण

/*
 * This must be called with s_lock held.
 */
व्योम hfi1_bad_pkey(काष्ठा hfi1_ibport *ibp, u32 key, u32 sl,
		   u32 qp1, u32 qp2, u32 lid1, u32 lid2);
व्योम hfi1_cap_mask_chg(काष्ठा rvt_dev_info *rdi, u32 port_num);
व्योम hfi1_sys_guid_chg(काष्ठा hfi1_ibport *ibp);
व्योम hfi1_node_desc_chg(काष्ठा hfi1_ibport *ibp);
पूर्णांक hfi1_process_mad(काष्ठा ib_device *ibdev, पूर्णांक mad_flags, u32 port,
		     स्थिर काष्ठा ib_wc *in_wc, स्थिर काष्ठा ib_grh *in_grh,
		     स्थिर काष्ठा ib_mad *in_mad, काष्ठा ib_mad *out_mad,
		     माप_प्रकार *out_mad_size, u16 *out_mad_pkey_index);

/*
 * The PSN_MASK and PSN_SHIFT allow क्रम
 * 1) comparing two PSNs
 * 2) वापसing the PSN with any upper bits masked
 * 3) वापसing the dअगरference between to PSNs
 *
 * The number of signअगरicant bits in the PSN must
 * necessarily be at least one bit less than
 * the container holding the PSN.
 */
#घोषणा PSN_MASK 0x7FFFFFFF
#घोषणा PSN_SHIFT 1
#घोषणा PSN_MODIFY_MASK 0xFFFFFF

/*
 * Compare two PSNs
 * Returns an पूर्णांकeger <, ==, or > than zero.
 */
अटल अंतरभूत पूर्णांक cmp_psn(u32 a, u32 b)
अणु
	वापस (((पूर्णांक)a) - ((पूर्णांक)b)) << PSN_SHIFT;
पूर्ण

/*
 * Return masked PSN
 */
अटल अंतरभूत u32 mask_psn(u32 a)
अणु
	वापस a & PSN_MASK;
पूर्ण

/*
 * Return delta between two PSNs
 */
अटल अंतरभूत u32 delta_psn(u32 a, u32 b)
अणु
	वापस (((पूर्णांक)a - (पूर्णांक)b) << PSN_SHIFT) >> PSN_SHIFT;
पूर्ण

अटल अंतरभूत काष्ठा tid_rdma_request *wqe_to_tid_req(काष्ठा rvt_swqe *wqe)
अणु
	वापस &((काष्ठा hfi1_swqe_priv *)wqe->priv)->tid_req;
पूर्ण

अटल अंतरभूत काष्ठा tid_rdma_request *ack_to_tid_req(काष्ठा rvt_ack_entry *e)
अणु
	वापस &((काष्ठा hfi1_ack_priv *)e->priv)->tid_req;
पूर्ण

/*
 * Look through all the active flows क्रम a TID RDMA request and find
 * the one (अगर it exists) that contains the specअगरied PSN.
 */
अटल अंतरभूत u32 __full_flow_psn(काष्ठा flow_state *state, u32 psn)
अणु
	वापस mask_psn((state->generation << HFI1_KDETH_BTH_SEQ_SHIFT) |
			(psn & HFI1_KDETH_BTH_SEQ_MASK));
पूर्ण

अटल अंतरभूत u32 full_flow_psn(काष्ठा tid_rdma_flow *flow, u32 psn)
अणु
	वापस __full_flow_psn(&flow->flow_state, psn);
पूर्ण

काष्ठा verbs_txreq;
व्योम hfi1_put_txreq(काष्ठा verbs_txreq *tx);

पूर्णांक hfi1_verbs_send(काष्ठा rvt_qp *qp, काष्ठा hfi1_pkt_state *ps);

व्योम hfi1_cnp_rcv(काष्ठा hfi1_packet *packet);

व्योम hfi1_uc_rcv(काष्ठा hfi1_packet *packet);

व्योम hfi1_rc_rcv(काष्ठा hfi1_packet *packet);

व्योम hfi1_rc_hdrerr(
	काष्ठा hfi1_ctxtdata *rcd,
	काष्ठा hfi1_packet *packet,
	काष्ठा rvt_qp *qp);

u8 ah_to_sc(काष्ठा ib_device *ibdev, काष्ठा rdma_ah_attr *ah_attr);

व्योम hfi1_rc_verbs_पातed(काष्ठा rvt_qp *qp, काष्ठा hfi1_opa_header *opah);
व्योम hfi1_rc_send_complete(काष्ठा rvt_qp *qp, काष्ठा hfi1_opa_header *opah);

व्योम hfi1_ud_rcv(काष्ठा hfi1_packet *packet);

पूर्णांक hfi1_lookup_pkey_idx(काष्ठा hfi1_ibport *ibp, u16 pkey);

व्योम hfi1_migrate_qp(काष्ठा rvt_qp *qp);

पूर्णांक hfi1_check_modअगरy_qp(काष्ठा rvt_qp *qp, काष्ठा ib_qp_attr *attr,
			 पूर्णांक attr_mask, काष्ठा ib_udata *udata);

व्योम hfi1_modअगरy_qp(काष्ठा rvt_qp *qp, काष्ठा ib_qp_attr *attr,
		    पूर्णांक attr_mask, काष्ठा ib_udata *udata);
व्योम hfi1_restart_rc(काष्ठा rvt_qp *qp, u32 psn, पूर्णांक रुको);
पूर्णांक hfi1_setup_wqe(काष्ठा rvt_qp *qp, काष्ठा rvt_swqe *wqe,
		   bool *call_send);

बाह्य स्थिर u32 rc_only_opcode;
बाह्य स्थिर u32 uc_only_opcode;

पूर्णांक hfi1_ruc_check_hdr(काष्ठा hfi1_ibport *ibp, काष्ठा hfi1_packet *packet);

u32 hfi1_make_grh(काष्ठा hfi1_ibport *ibp, काष्ठा ib_grh *hdr,
		  स्थिर काष्ठा ib_global_route *grh, u32 hwords, u32 nwords);

व्योम hfi1_make_ruc_header(काष्ठा rvt_qp *qp, काष्ठा ib_other_headers *ohdr,
			  u32 bth0, u32 bth1, u32 bth2, पूर्णांक middle,
			  काष्ठा hfi1_pkt_state *ps);

bool hfi1_schedule_send_yield(काष्ठा rvt_qp *qp, काष्ठा hfi1_pkt_state *ps,
			      bool tid);

व्योम _hfi1_करो_send(काष्ठा work_काष्ठा *work);

व्योम hfi1_करो_send_from_rvt(काष्ठा rvt_qp *qp);

व्योम hfi1_करो_send(काष्ठा rvt_qp *qp, bool in_thपढ़ो);

व्योम hfi1_send_rc_ack(काष्ठा hfi1_packet *packet, bool is_fecn);

पूर्णांक hfi1_make_rc_req(काष्ठा rvt_qp *qp, काष्ठा hfi1_pkt_state *ps);

पूर्णांक hfi1_make_uc_req(काष्ठा rvt_qp *qp, काष्ठा hfi1_pkt_state *ps);

पूर्णांक hfi1_make_ud_req(काष्ठा rvt_qp *qp, काष्ठा hfi1_pkt_state *ps);

पूर्णांक hfi1_रेजिस्टर_ib_device(काष्ठा hfi1_devdata *);

व्योम hfi1_unरेजिस्टर_ib_device(काष्ठा hfi1_devdata *);

व्योम hfi1_kdeth_eager_rcv(काष्ठा hfi1_packet *packet);

व्योम hfi1_kdeth_expected_rcv(काष्ठा hfi1_packet *packet);

व्योम hfi1_ib_rcv(काष्ठा hfi1_packet *packet);

व्योम hfi1_16B_rcv(काष्ठा hfi1_packet *packet);

अचिन्हित hfi1_get_npkeys(काष्ठा hfi1_devdata *);

पूर्णांक hfi1_verbs_send_dma(काष्ठा rvt_qp *qp, काष्ठा hfi1_pkt_state *ps,
			u64 pbc);

पूर्णांक hfi1_verbs_send_pio(काष्ठा rvt_qp *qp, काष्ठा hfi1_pkt_state *ps,
			u64 pbc);

अटल अंतरभूत bool opa_bth_is_migration(काष्ठा ib_other_headers *ohdr)
अणु
	वापस ohdr->bth[1] & cpu_to_be32(OPA_BTH_MIG_REQ);
पूर्ण

व्योम hfi1_रुको_kmem(काष्ठा rvt_qp *qp);

अटल अंतरभूत व्योम hfi1_trdma_send_complete(काष्ठा rvt_qp *qp,
					    काष्ठा rvt_swqe *wqe,
					    क्रमागत ib_wc_status status)
अणु
	trdma_clean_swqe(qp, wqe);
	rvt_send_complete(qp, wqe, status);
पूर्ण

बाह्य स्थिर क्रमागत ib_wc_opcode ib_hfi1_wc_opcode[];

बाह्य स्थिर u8 hdr_len_by_opcode[];

बाह्य स्थिर पूर्णांक ib_rvt_state_ops[];

बाह्य __be64 ib_hfi1_sys_image_guid;    /* in network order */

बाह्य अचिन्हित पूर्णांक hfi1_max_cqes;

बाह्य अचिन्हित पूर्णांक hfi1_max_cqs;

बाह्य अचिन्हित पूर्णांक hfi1_max_qp_wrs;

बाह्य अचिन्हित पूर्णांक hfi1_max_qps;

बाह्य अचिन्हित पूर्णांक hfi1_max_sges;

बाह्य अचिन्हित पूर्णांक hfi1_max_mcast_grps;

बाह्य अचिन्हित पूर्णांक hfi1_max_mcast_qp_attached;

बाह्य अचिन्हित पूर्णांक hfi1_max_srqs;

बाह्य अचिन्हित पूर्णांक hfi1_max_srq_sges;

बाह्य अचिन्हित पूर्णांक hfi1_max_srq_wrs;

बाह्य अचिन्हित लघु piothreshold;

बाह्य स्थिर u32 ib_hfi1_rnr_table[];

#पूर्ण_अगर                          /* HFI1_VERBS_H */
