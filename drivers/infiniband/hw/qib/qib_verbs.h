<शैली गुरु>
/*
 * Copyright (c) 2012 - 2018 Intel Corporation.  All rights reserved.
 * Copyright (c) 2006 - 2012 QLogic Corporation. All rights reserved.
 * Copyright (c) 2005, 2006 PathScale, Inc. All rights reserved.
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

#अगर_अघोषित QIB_VERBS_H
#घोषणा QIB_VERBS_H

#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kref.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/completion.h>
#समावेश <rdma/ib_pack.h>
#समावेश <rdma/ib_user_verbs.h>
#समावेश <rdma/ib_hdrs.h>
#समावेश <rdma/rdmavt_qp.h>
#समावेश <rdma/rdmavt_cq.h>

काष्ठा qib_ctxtdata;
काष्ठा qib_pportdata;
काष्ठा qib_devdata;
काष्ठा qib_verbs_txreq;

#घोषणा QIB_MAX_RDMA_ATOMIC     16
#घोषणा QIB_GUIDS_PER_PORT	5
#घोषणा QIB_PSN_SHIFT		8

/*
 * Increment this value अगर any changes that अवरोध userspace ABI
 * compatibility are made.
 */
#घोषणा QIB_UVERBS_ABI_VERSION       2

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

#घोषणा QIB_VENDOR_IPG		cpu_to_be16(0xFFA0)

#घोषणा IB_DEFAULT_GID_PREFIX	cpu_to_be64(0xfe80000000000000ULL)

/* Values क्रम set/get portinfo VLCap OperationalVLs */
#घोषणा IB_VL_VL0       1
#घोषणा IB_VL_VL0_1     2
#घोषणा IB_VL_VL0_3     3
#घोषणा IB_VL_VL0_7     4
#घोषणा IB_VL_VL0_14    5

अटल अंतरभूत पूर्णांक qib_num_vls(पूर्णांक vls)
अणु
	चयन (vls) अणु
	शेष:
	हाल IB_VL_VL0:
		वापस 1;
	हाल IB_VL_VL0_1:
		वापस 2;
	हाल IB_VL_VL0_3:
		वापस 4;
	हाल IB_VL_VL0_7:
		वापस 8;
	हाल IB_VL_VL0_14:
		वापस 15;
	पूर्ण
पूर्ण

काष्ठा qib_pio_header अणु
	__le32 pbc[2];
	काष्ठा ib_header hdr;
पूर्ण __packed;

/*
 * qib specअगरic data काष्ठाure that will be hidden from rvt after the queue pair
 * is made common.
 */
काष्ठा qib_qp_priv अणु
	काष्ठा ib_header *s_hdr;        /* next packet header to send */
	काष्ठा list_head ioरुको;        /* link क्रम रुको PIO buf */
	atomic_t s_dma_busy;
	काष्ठा qib_verbs_txreq *s_tx;
	काष्ठा work_काष्ठा s_work;
	रुको_queue_head_t रुको_dma;
	काष्ठा rvt_qp *owner;
पूर्ण;

#घोषणा QIB_PSN_CREDIT  16

काष्ठा qib_opcode_stats अणु
	u64 n_packets;          /* number of packets */
	u64 n_bytes;            /* total number of bytes */
पूर्ण;

काष्ठा qib_opcode_stats_perctx अणु
	काष्ठा qib_opcode_stats stats[128];
पूर्ण;

काष्ठा qib_pma_counters अणु
	u64 n_unicast_xmit;     /* total unicast packets sent */
	u64 n_unicast_rcv;      /* total unicast packets received */
	u64 n_multicast_xmit;   /* total multicast packets sent */
	u64 n_multicast_rcv;    /* total multicast packets received */
पूर्ण;

काष्ठा qib_ibport अणु
	काष्ठा rvt_ibport rvp;
	काष्ठा rvt_ah *smi_ah;
	__be64 guids[QIB_GUIDS_PER_PORT	- 1];	/* writable GUIDs */
	काष्ठा qib_pma_counters __percpu *pmastats;
	u64 z_unicast_xmit;     /* starting count क्रम PMA */
	u64 z_unicast_rcv;      /* starting count क्रम PMA */
	u64 z_multicast_xmit;   /* starting count क्रम PMA */
	u64 z_multicast_rcv;    /* starting count क्रम PMA */
	u64 z_symbol_error_counter;             /* starting count क्रम PMA */
	u64 z_link_error_recovery_counter;      /* starting count क्रम PMA */
	u64 z_link_करोwned_counter;              /* starting count क्रम PMA */
	u64 z_port_rcv_errors;                  /* starting count क्रम PMA */
	u64 z_port_rcv_remphys_errors;          /* starting count क्रम PMA */
	u64 z_port_xmit_discards;               /* starting count क्रम PMA */
	u64 z_port_xmit_data;                   /* starting count क्रम PMA */
	u64 z_port_rcv_data;                    /* starting count क्रम PMA */
	u64 z_port_xmit_packets;                /* starting count क्रम PMA */
	u64 z_port_rcv_packets;                 /* starting count क्रम PMA */
	u32 z_local_link_पूर्णांकegrity_errors;      /* starting count क्रम PMA */
	u32 z_excessive_buffer_overrun_errors;  /* starting count क्रम PMA */
	u32 z_vl15_dropped;                     /* starting count क्रम PMA */
	u8 sl_to_vl[16];
पूर्ण;

काष्ठा qib_ibdev अणु
	काष्ठा rvt_dev_info rdi;

	काष्ठा list_head pioरुको;       /* list क्रम रुको PIO buf */
	काष्ठा list_head dmaरुको;	/* list क्रम रुको DMA */
	काष्ठा list_head txरुको;        /* list क्रम रुको qib_verbs_txreq */
	काष्ठा list_head memरुको;       /* list क्रम रुको kernel memory */
	काष्ठा list_head txreq_मुक्त;
	काष्ठा समयr_list mem_समयr;
	काष्ठा qib_pio_header *pio_hdrs;
	dma_addr_t pio_hdrs_phys;

	u32 n_pioरुको;
	u32 n_txरुको;

#अगर_घोषित CONFIG_DEBUG_FS
	/* per HCA debugfs */
	काष्ठा dentry *qib_ibdev_dbg;
#पूर्ण_अगर
पूर्ण;

काष्ठा qib_verbs_counters अणु
	u64 symbol_error_counter;
	u64 link_error_recovery_counter;
	u64 link_करोwned_counter;
	u64 port_rcv_errors;
	u64 port_rcv_remphys_errors;
	u64 port_xmit_discards;
	u64 port_xmit_data;
	u64 port_rcv_data;
	u64 port_xmit_packets;
	u64 port_rcv_packets;
	u32 local_link_पूर्णांकegrity_errors;
	u32 excessive_buffer_overrun_errors;
	u32 vl15_dropped;
पूर्ण;

अटल अंतरभूत काष्ठा qib_ibdev *to_idev(काष्ठा ib_device *ibdev)
अणु
	काष्ठा rvt_dev_info *rdi;

	rdi = container_of(ibdev, काष्ठा rvt_dev_info, ibdev);
	वापस container_of(rdi, काष्ठा qib_ibdev, rdi);
पूर्ण

/*
 * Send अगर not busy or रुकोing क्रम I/O and either
 * a RC response is pending or we can process send work requests.
 */
अटल अंतरभूत पूर्णांक qib_send_ok(काष्ठा rvt_qp *qp)
अणु
	वापस !(qp->s_flags & (RVT_S_BUSY | RVT_S_ANY_WAIT_IO)) &&
		(qp->s_hdrwords || (qp->s_flags & RVT_S_RESP_PENDING) ||
		 !(qp->s_flags & RVT_S_ANY_WAIT_SEND));
पूर्ण

bool _qib_schedule_send(काष्ठा rvt_qp *qp);
bool qib_schedule_send(काष्ठा rvt_qp *qp);

अटल अंतरभूत पूर्णांक qib_pkey_ok(u16 pkey1, u16 pkey2)
अणु
	u16 p1 = pkey1 & 0x7FFF;
	u16 p2 = pkey2 & 0x7FFF;

	/*
	 * Low 15 bits must be non-zero and match, and
	 * one of the two must be a full member.
	 */
	वापस p1 && p1 == p2 && ((__s16)pkey1 < 0 || (__s16)pkey2 < 0);
पूर्ण

व्योम qib_bad_pkey(काष्ठा qib_ibport *ibp, u32 key, u32 sl,
		  u32 qp1, u32 qp2, __be16 lid1, __be16 lid2);
व्योम qib_cap_mask_chg(काष्ठा rvt_dev_info *rdi, u32 port_num);
व्योम qib_sys_guid_chg(काष्ठा qib_ibport *ibp);
व्योम qib_node_desc_chg(काष्ठा qib_ibport *ibp);
पूर्णांक qib_process_mad(काष्ठा ib_device *ibdev, पूर्णांक mad_flags, u32 port_num,
		    स्थिर काष्ठा ib_wc *in_wc, स्थिर काष्ठा ib_grh *in_grh,
		    स्थिर काष्ठा ib_mad *in, काष्ठा ib_mad *out,
		    माप_प्रकार *out_mad_size, u16 *out_mad_pkey_index);
व्योम qib_notअगरy_create_mad_agent(काष्ठा rvt_dev_info *rdi, पूर्णांक port_idx);
व्योम qib_notअगरy_मुक्त_mad_agent(काष्ठा rvt_dev_info *rdi, पूर्णांक port_idx);

/*
 * Compare the lower 24 bits of the two values.
 * Returns an पूर्णांकeger <, ==, or > than zero.
 */
अटल अंतरभूत पूर्णांक qib_cmp24(u32 a, u32 b)
अणु
	वापस (((पूर्णांक) a) - ((पूर्णांक) b)) << 8;
पूर्ण

पूर्णांक qib_snapshot_counters(काष्ठा qib_pportdata *ppd, u64 *swords,
			  u64 *rwords, u64 *spkts, u64 *rpkts,
			  u64 *xmit_रुको);

पूर्णांक qib_get_counters(काष्ठा qib_pportdata *ppd,
		     काष्ठा qib_verbs_counters *cntrs);

/*
 * Functions provided by qib driver क्रम rdmavt to use
 */
अचिन्हित qib_मुक्त_all_qps(काष्ठा rvt_dev_info *rdi);
व्योम *qib_qp_priv_alloc(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_qp *qp);
व्योम qib_qp_priv_मुक्त(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_qp *qp);
व्योम qib_notअगरy_qp_reset(काष्ठा rvt_qp *qp);
पूर्णांक qib_alloc_qpn(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_qpn_table *qpt,
		  क्रमागत ib_qp_type type, u32 port);
व्योम qib_restart_rc(काष्ठा rvt_qp *qp, u32 psn, पूर्णांक रुको);
#अगर_घोषित CONFIG_DEBUG_FS

व्योम qib_qp_iter_prपूर्णांक(काष्ठा seq_file *s, काष्ठा rvt_qp_iter *iter);

#पूर्ण_अगर

अचिन्हित qib_pkt_delay(u32 plen, u8 snd_mult, u8 rcv_mult);

व्योम qib_verbs_sdma_desc_avail(काष्ठा qib_pportdata *ppd, अचिन्हित avail);

व्योम qib_put_txreq(काष्ठा qib_verbs_txreq *tx);

पूर्णांक qib_verbs_send(काष्ठा rvt_qp *qp, काष्ठा ib_header *hdr,
		   u32 hdrwords, काष्ठा rvt_sge_state *ss, u32 len);

व्योम qib_uc_rcv(काष्ठा qib_ibport *ibp, काष्ठा ib_header *hdr,
		पूर्णांक has_grh, व्योम *data, u32 tlen, काष्ठा rvt_qp *qp);

व्योम qib_rc_rcv(काष्ठा qib_ctxtdata *rcd, काष्ठा ib_header *hdr,
		पूर्णांक has_grh, व्योम *data, u32 tlen, काष्ठा rvt_qp *qp);

पूर्णांक qib_check_ah(काष्ठा ib_device *ibdev, काष्ठा rdma_ah_attr *ah_attr);

पूर्णांक qib_check_send_wqe(काष्ठा rvt_qp *qp, काष्ठा rvt_swqe *wqe,
		       bool *call_send);

काष्ठा ib_ah *qib_create_qp0_ah(काष्ठा qib_ibport *ibp, u16 dlid);

व्योम qib_rc_rnr_retry(अचिन्हित दीर्घ arg);

व्योम qib_rc_send_complete(काष्ठा rvt_qp *qp, काष्ठा ib_header *hdr);

पूर्णांक qib_post_ud_send(काष्ठा rvt_qp *qp, स्थिर काष्ठा ib_send_wr *wr);

व्योम qib_ud_rcv(काष्ठा qib_ibport *ibp, काष्ठा ib_header *hdr,
		पूर्णांक has_grh, व्योम *data, u32 tlen, काष्ठा rvt_qp *qp);

व्योम mr_rcu_callback(काष्ठा rcu_head *list);

व्योम qib_migrate_qp(काष्ठा rvt_qp *qp);

पूर्णांक qib_ruc_check_hdr(काष्ठा qib_ibport *ibp, काष्ठा ib_header *hdr,
		      पूर्णांक has_grh, काष्ठा rvt_qp *qp, u32 bth0);

u32 qib_make_grh(काष्ठा qib_ibport *ibp, काष्ठा ib_grh *hdr,
		 स्थिर काष्ठा ib_global_route *grh, u32 hwords, u32 nwords);

व्योम qib_make_ruc_header(काष्ठा rvt_qp *qp, काष्ठा ib_other_headers *ohdr,
			 u32 bth0, u32 bth2);

व्योम _qib_करो_send(काष्ठा work_काष्ठा *work);

व्योम qib_करो_send(काष्ठा rvt_qp *qp);

व्योम qib_send_rc_ack(काष्ठा rvt_qp *qp);

पूर्णांक qib_make_rc_req(काष्ठा rvt_qp *qp, अचिन्हित दीर्घ *flags);

पूर्णांक qib_make_uc_req(काष्ठा rvt_qp *qp, अचिन्हित दीर्घ *flags);

पूर्णांक qib_make_ud_req(काष्ठा rvt_qp *qp, अचिन्हित दीर्घ *flags);

पूर्णांक qib_रेजिस्टर_ib_device(काष्ठा qib_devdata *);

व्योम qib_unरेजिस्टर_ib_device(काष्ठा qib_devdata *);

व्योम qib_ib_rcv(काष्ठा qib_ctxtdata *, व्योम *, व्योम *, u32);

व्योम qib_ib_piobufavail(काष्ठा qib_devdata *);

अचिन्हित qib_get_npkeys(काष्ठा qib_devdata *);

अचिन्हित qib_get_pkey(काष्ठा qib_ibport *, अचिन्हित);

बाह्य स्थिर क्रमागत ib_wc_opcode ib_qib_wc_opcode[];

/*
 * Below  HCA-independent IB PhysPortState values, वापसed
 * by the f_ibphys_portstate() routine.
 */
#घोषणा IB_PHYSPORTSTATE_SLEEP 1
#घोषणा IB_PHYSPORTSTATE_POLL 2
#घोषणा IB_PHYSPORTSTATE_DISABLED 3
#घोषणा IB_PHYSPORTSTATE_CFG_TRAIN 4
#घोषणा IB_PHYSPORTSTATE_LINKUP 5
#घोषणा IB_PHYSPORTSTATE_LINK_ERR_RECOVER 6
#घोषणा IB_PHYSPORTSTATE_CFG_DEBOUNCE 8
#घोषणा IB_PHYSPORTSTATE_CFG_IDLE 0xB
#घोषणा IB_PHYSPORTSTATE_RECOVERY_RETRAIN 0xC
#घोषणा IB_PHYSPORTSTATE_RECOVERY_WAITRMT 0xE
#घोषणा IB_PHYSPORTSTATE_RECOVERY_IDLE 0xF
#घोषणा IB_PHYSPORTSTATE_CFG_ENH 0x10
#घोषणा IB_PHYSPORTSTATE_CFG_WAIT_ENH 0x13

बाह्य स्थिर पूर्णांक ib_rvt_state_ops[];

बाह्य __be64 ib_qib_sys_image_guid;    /* in network order */

बाह्य अचिन्हित पूर्णांक ib_rvt_lkey_table_size;

बाह्य अचिन्हित पूर्णांक ib_qib_max_cqes;

बाह्य अचिन्हित पूर्णांक ib_qib_max_cqs;

बाह्य अचिन्हित पूर्णांक ib_qib_max_qp_wrs;

बाह्य अचिन्हित पूर्णांक ib_qib_max_qps;

बाह्य अचिन्हित पूर्णांक ib_qib_max_sges;

बाह्य अचिन्हित पूर्णांक ib_qib_max_mcast_grps;

बाह्य अचिन्हित पूर्णांक ib_qib_max_mcast_qp_attached;

बाह्य अचिन्हित पूर्णांक ib_qib_max_srqs;

बाह्य अचिन्हित पूर्णांक ib_qib_max_srq_sges;

बाह्य अचिन्हित पूर्णांक ib_qib_max_srq_wrs;

बाह्य स्थिर u32 ib_qib_rnr_table[];

बाह्य स्थिर काष्ठा rvt_operation_params qib_post_parms[];

#पूर्ण_अगर                          /* QIB_VERBS_H */
