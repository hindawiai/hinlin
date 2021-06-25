<शैली गुरु>
/*
 * Copyright (c) 2009-2010 Chelsio, Inc. All rights reserved.
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
#अगर_अघोषित __T4_H__
#घोषणा __T4_H__

#समावेश "t4_hw.h"
#समावेश "t4_regs.h"
#समावेश "t4_values.h"
#समावेश "t4_msg.h"
#समावेश "t4_tcb.h"
#समावेश "t4fw_ri_api.h"

#घोषणा T4_MAX_NUM_PD 65536
#घोषणा T4_MAX_MR_SIZE (~0ULL)
#घोषणा T4_PAGESIZE_MASK 0xffff000  /* 4KB-128MB */
#घोषणा T4_STAG_UNSET 0xffffffff
#घोषणा T4_FW_MAJ 0
#घोषणा PCIE_MA_SYNC_A 0x30b4

काष्ठा t4_status_page अणु
	__be32 rsvd1;	/* flit 0 - hw owns */
	__be16 rsvd2;
	__be16 qid;
	__be16 cidx;
	__be16 pidx;
	u8 qp_err;	/* flit 1 - sw owns */
	u8 db_off;
	u8 pad[2];
	u16 host_wq_pidx;
	u16 host_cidx;
	u16 host_pidx;
	u16 pad2;
	u32 srqidx;
पूर्ण;

#घोषणा T4_RQT_ENTRY_SHIFT 6
#घोषणा T4_RQT_ENTRY_SIZE  BIT(T4_RQT_ENTRY_SHIFT)
#घोषणा T4_EQ_ENTRY_SIZE 64

#घोषणा T4_SQ_NUM_SLOTS 5
#घोषणा T4_SQ_NUM_BYTES (T4_EQ_ENTRY_SIZE * T4_SQ_NUM_SLOTS)
#घोषणा T4_MAX_SEND_SGE ((T4_SQ_NUM_BYTES - माप(काष्ठा fw_ri_send_wr) - \
			माप(काष्ठा fw_ri_isgl)) / माप(काष्ठा fw_ri_sge))
#घोषणा T4_MAX_SEND_INLINE ((T4_SQ_NUM_BYTES - माप(काष्ठा fw_ri_send_wr) - \
			माप(काष्ठा fw_ri_immd)))
#घोषणा T4_MAX_WRITE_INLINE ((T4_SQ_NUM_BYTES - \
			माप(काष्ठा fw_ri_rdma_ग_लिखो_wr) - \
			माप(काष्ठा fw_ri_immd)))
#घोषणा T4_MAX_WRITE_SGE ((T4_SQ_NUM_BYTES - \
			माप(काष्ठा fw_ri_rdma_ग_लिखो_wr) - \
			माप(काष्ठा fw_ri_isgl)) / माप(काष्ठा fw_ri_sge))
#घोषणा T4_MAX_FR_IMMD ((T4_SQ_NUM_BYTES - माप(काष्ठा fw_ri_fr_nsmr_wr) - \
			माप(काष्ठा fw_ri_immd)) & ~31UL)
#घोषणा T4_MAX_FR_IMMD_DEPTH (T4_MAX_FR_IMMD / माप(u64))
#घोषणा T4_MAX_FR_DSGL 1024
#घोषणा T4_MAX_FR_DSGL_DEPTH (T4_MAX_FR_DSGL / माप(u64))

अटल अंतरभूत पूर्णांक t4_max_fr_depth(पूर्णांक use_dsgl)
अणु
	वापस use_dsgl ? T4_MAX_FR_DSGL_DEPTH : T4_MAX_FR_IMMD_DEPTH;
पूर्ण

#घोषणा T4_RQ_NUM_SLOTS 2
#घोषणा T4_RQ_NUM_BYTES (T4_EQ_ENTRY_SIZE * T4_RQ_NUM_SLOTS)
#घोषणा T4_MAX_RECV_SGE 4

#घोषणा T4_WRITE_CMPL_MAX_SGL 4
#घोषणा T4_WRITE_CMPL_MAX_CQE 16

जोड़ t4_wr अणु
	काष्ठा fw_ri_res_wr res;
	काष्ठा fw_ri_wr ri;
	काष्ठा fw_ri_rdma_ग_लिखो_wr ग_लिखो;
	काष्ठा fw_ri_send_wr send;
	काष्ठा fw_ri_rdma_पढ़ो_wr पढ़ो;
	काष्ठा fw_ri_bind_mw_wr bind;
	काष्ठा fw_ri_fr_nsmr_wr fr;
	काष्ठा fw_ri_fr_nsmr_tpte_wr fr_tpte;
	काष्ठा fw_ri_inv_lstag_wr inv;
	काष्ठा fw_ri_rdma_ग_लिखो_cmpl_wr ग_लिखो_cmpl;
	काष्ठा t4_status_page status;
	__be64 flits[T4_EQ_ENTRY_SIZE / माप(__be64) * T4_SQ_NUM_SLOTS];
पूर्ण;

जोड़ t4_recv_wr अणु
	काष्ठा fw_ri_recv_wr recv;
	काष्ठा t4_status_page status;
	__be64 flits[T4_EQ_ENTRY_SIZE / माप(__be64) * T4_RQ_NUM_SLOTS];
पूर्ण;

अटल अंतरभूत व्योम init_wr_hdr(जोड़ t4_wr *wqe, u16 wrid,
			       क्रमागत fw_wr_opcodes opcode, u8 flags, u8 len16)
अणु
	wqe->send.opcode = (u8)opcode;
	wqe->send.flags = flags;
	wqe->send.wrid = wrid;
	wqe->send.r1[0] = 0;
	wqe->send.r1[1] = 0;
	wqe->send.r1[2] = 0;
	wqe->send.len16 = len16;
पूर्ण

/* CQE/AE status codes */
#घोषणा T4_ERR_SUCCESS                     0x0
#घोषणा T4_ERR_STAG                        0x1	/* STAG invalid: either the */
						/* STAG is offlimt, being 0, */
						/* or STAG_key mismatch */
#घोषणा T4_ERR_PDID                        0x2	/* PDID mismatch */
#घोषणा T4_ERR_QPID                        0x3	/* QPID mismatch */
#घोषणा T4_ERR_ACCESS                      0x4	/* Invalid access right */
#घोषणा T4_ERR_WRAP                        0x5	/* Wrap error */
#घोषणा T4_ERR_BOUND                       0x6	/* base and bounds voilation */
#घोषणा T4_ERR_INVALIDATE_SHARED_MR        0x7	/* attempt to invalidate a  */
						/* shared memory region */
#घोषणा T4_ERR_INVALIDATE_MR_WITH_MW_BOUND 0x8	/* attempt to invalidate a  */
						/* shared memory region */
#घोषणा T4_ERR_ECC                         0x9	/* ECC error detected */
#घोषणा T4_ERR_ECC_PSTAG                   0xA	/* ECC error detected when  */
						/* पढ़ोing PSTAG क्रम a MW  */
						/* Invalidate */
#घोषणा T4_ERR_PBL_ADDR_BOUND              0xB	/* pbl addr out of bounds:  */
						/* software error */
#घोषणा T4_ERR_SWFLUSH			   0xC	/* SW FLUSHED */
#घोषणा T4_ERR_CRC                         0x10 /* CRC error */
#घोषणा T4_ERR_MARKER                      0x11 /* Marker error */
#घोषणा T4_ERR_PDU_LEN_ERR                 0x12 /* invalid PDU length */
#घोषणा T4_ERR_OUT_OF_RQE                  0x13 /* out of RQE */
#घोषणा T4_ERR_DDP_VERSION                 0x14 /* wrong DDP version */
#घोषणा T4_ERR_RDMA_VERSION                0x15 /* wrong RDMA version */
#घोषणा T4_ERR_OPCODE                      0x16 /* invalid rdma opcode */
#घोषणा T4_ERR_DDP_QUEUE_NUM               0x17 /* invalid ddp queue number */
#घोषणा T4_ERR_MSN                         0x18 /* MSN error */
#घोषणा T4_ERR_TBIT                        0x19 /* tag bit not set correctly */
#घोषणा T4_ERR_MO                          0x1A /* MO not 0 क्रम TERMINATE  */
						/* or READ_REQ */
#घोषणा T4_ERR_MSN_GAP                     0x1B
#घोषणा T4_ERR_MSN_RANGE                   0x1C
#घोषणा T4_ERR_IRD_OVERFLOW                0x1D
#घोषणा T4_ERR_RQE_ADDR_BOUND              0x1E /* RQE addr out of bounds:  */
						/* software error */
#घोषणा T4_ERR_INTERNAL_ERR                0x1F /* पूर्णांकernal error (opcode  */
						/* mismatch) */
/*
 * CQE defs
 */
काष्ठा t4_cqe अणु
	__be32 header;
	__be32 len;
	जोड़ अणु
		काष्ठा अणु
			__be32 stag;
			__be32 msn;
		पूर्ण rcqe;
		काष्ठा अणु
			__be32 stag;
			u16 nada2;
			u16 cidx;
		पूर्ण scqe;
		काष्ठा अणु
			__be32 wrid_hi;
			__be32 wrid_low;
		पूर्ण gen;
		काष्ठा अणु
			__be32 stag;
			__be32 msn;
			__be32 reserved;
			__be32 असल_rqe_idx;
		पूर्ण srcqe;
		काष्ठा अणु
			__be32 mo;
			__be32 msn;
			/*
			 * Use जोड़ क्रम immediate data to be consistent with
			 * stack's 32 bit data and iWARP spec's 64 bit data.
			 */
			जोड़ अणु
				काष्ठा अणु
					__be32 imm_data32;
					u32 reserved;
				पूर्ण ib_imm_data;
				__be64 imm_data64;
			पूर्ण iw_imm_data;
		पूर्ण imm_data_rcqe;

		u64 drain_cookie;
		__be64 flits[3];
	पूर्ण u;
	__be64 reserved[3];
	__be64 bits_type_ts;
पूर्ण;

/* macros क्रम flit 0 of the cqe */

#घोषणा CQE_QPID_S        12
#घोषणा CQE_QPID_M        0xFFFFF
#घोषणा CQE_QPID_G(x)     ((((x) >> CQE_QPID_S)) & CQE_QPID_M)
#घोषणा CQE_QPID_V(x)	  ((x)<<CQE_QPID_S)

#घोषणा CQE_SWCQE_S       11
#घोषणा CQE_SWCQE_M       0x1
#घोषणा CQE_SWCQE_G(x)    ((((x) >> CQE_SWCQE_S)) & CQE_SWCQE_M)
#घोषणा CQE_SWCQE_V(x)	  ((x)<<CQE_SWCQE_S)

#घोषणा CQE_DRAIN_S       10
#घोषणा CQE_DRAIN_M       0x1
#घोषणा CQE_DRAIN_G(x)    ((((x) >> CQE_DRAIN_S)) & CQE_DRAIN_M)
#घोषणा CQE_DRAIN_V(x)	  ((x)<<CQE_DRAIN_S)

#घोषणा CQE_STATUS_S      5
#घोषणा CQE_STATUS_M      0x1F
#घोषणा CQE_STATUS_G(x)   ((((x) >> CQE_STATUS_S)) & CQE_STATUS_M)
#घोषणा CQE_STATUS_V(x)   ((x)<<CQE_STATUS_S)

#घोषणा CQE_TYPE_S        4
#घोषणा CQE_TYPE_M        0x1
#घोषणा CQE_TYPE_G(x)     ((((x) >> CQE_TYPE_S)) & CQE_TYPE_M)
#घोषणा CQE_TYPE_V(x)     ((x)<<CQE_TYPE_S)

#घोषणा CQE_OPCODE_S      0
#घोषणा CQE_OPCODE_M      0xF
#घोषणा CQE_OPCODE_G(x)   ((((x) >> CQE_OPCODE_S)) & CQE_OPCODE_M)
#घोषणा CQE_OPCODE_V(x)   ((x)<<CQE_OPCODE_S)

#घोषणा SW_CQE(x)         (CQE_SWCQE_G(be32_to_cpu((x)->header)))
#घोषणा DRAIN_CQE(x)      (CQE_DRAIN_G(be32_to_cpu((x)->header)))
#घोषणा CQE_QPID(x)       (CQE_QPID_G(be32_to_cpu((x)->header)))
#घोषणा CQE_TYPE(x)       (CQE_TYPE_G(be32_to_cpu((x)->header)))
#घोषणा SQ_TYPE(x)	  (CQE_TYPE((x)))
#घोषणा RQ_TYPE(x)	  (!CQE_TYPE((x)))
#घोषणा CQE_STATUS(x)     (CQE_STATUS_G(be32_to_cpu((x)->header)))
#घोषणा CQE_OPCODE(x)     (CQE_OPCODE_G(be32_to_cpu((x)->header)))

#घोषणा CQE_SEND_OPCODE(x)( \
	(CQE_OPCODE_G(be32_to_cpu((x)->header)) == FW_RI_SEND) || \
	(CQE_OPCODE_G(be32_to_cpu((x)->header)) == FW_RI_SEND_WITH_SE) || \
	(CQE_OPCODE_G(be32_to_cpu((x)->header)) == FW_RI_SEND_WITH_INV) || \
	(CQE_OPCODE_G(be32_to_cpu((x)->header)) == FW_RI_SEND_WITH_SE_INV))

#घोषणा CQE_LEN(x)        (be32_to_cpu((x)->len))

/* used क्रम RQ completion processing */
#घोषणा CQE_WRID_STAG(x)  (be32_to_cpu((x)->u.rcqe.stag))
#घोषणा CQE_WRID_MSN(x)   (be32_to_cpu((x)->u.rcqe.msn))
#घोषणा CQE_ABS_RQE_IDX(x) (be32_to_cpu((x)->u.srcqe.असल_rqe_idx))
#घोषणा CQE_IMM_DATA(x)( \
	(x)->u.imm_data_rcqe.iw_imm_data.ib_imm_data.imm_data32)

/* used क्रम SQ completion processing */
#घोषणा CQE_WRID_SQ_IDX(x)	((x)->u.scqe.cidx)
#घोषणा CQE_WRID_FR_STAG(x)     (be32_to_cpu((x)->u.scqe.stag))

/* generic accessor macros */
#घोषणा CQE_WRID_HI(x)		(be32_to_cpu((x)->u.gen.wrid_hi))
#घोषणा CQE_WRID_LOW(x)		(be32_to_cpu((x)->u.gen.wrid_low))
#घोषणा CQE_DRAIN_COOKIE(x)	((x)->u.drain_cookie)

/* macros क्रम flit 3 of the cqe */
#घोषणा CQE_GENBIT_S	63
#घोषणा CQE_GENBIT_M	0x1
#घोषणा CQE_GENBIT_G(x)	(((x) >> CQE_GENBIT_S) & CQE_GENBIT_M)
#घोषणा CQE_GENBIT_V(x) ((x)<<CQE_GENBIT_S)

#घोषणा CQE_OVFBIT_S	62
#घोषणा CQE_OVFBIT_M	0x1
#घोषणा CQE_OVFBIT_G(x)	((((x) >> CQE_OVFBIT_S)) & CQE_OVFBIT_M)

#घोषणा CQE_IQTYPE_S	60
#घोषणा CQE_IQTYPE_M	0x3
#घोषणा CQE_IQTYPE_G(x)	((((x) >> CQE_IQTYPE_S)) & CQE_IQTYPE_M)

#घोषणा CQE_TS_M	0x0fffffffffffffffULL
#घोषणा CQE_TS_G(x)	((x) & CQE_TS_M)

#घोषणा CQE_OVFBIT(x)	((अचिन्हित)CQE_OVFBIT_G(be64_to_cpu((x)->bits_type_ts)))
#घोषणा CQE_GENBIT(x)	((अचिन्हित)CQE_GENBIT_G(be64_to_cpu((x)->bits_type_ts)))
#घोषणा CQE_TS(x)	(CQE_TS_G(be64_to_cpu((x)->bits_type_ts)))

काष्ठा t4_swsqe अणु
	u64			wr_id;
	काष्ठा t4_cqe		cqe;
	पूर्णांक			पढ़ो_len;
	पूर्णांक			opcode;
	पूर्णांक			complete;
	पूर्णांक			संकेतed;
	u16			idx;
	पूर्णांक                     flushed;
	kसमय_प्रकार			host_समय;
	u64                     sge_ts;
पूर्ण;

अटल अंतरभूत pgprot_t t4_pgprot_wc(pgprot_t prot)
अणु
#अगर defined(__i386__) || defined(__x86_64__) || defined(CONFIG_PPC64)
	वापस pgprot_ग_लिखोcombine(prot);
#अन्यथा
	वापस pgprot_noncached(prot);
#पूर्ण_अगर
पूर्ण

क्रमागत अणु
	T4_SQ_ONCHIP = (1<<0),
पूर्ण;

काष्ठा t4_sq अणु
	जोड़ t4_wr *queue;
	dma_addr_t dma_addr;
	DEFINE_DMA_UNMAP_ADDR(mapping);
	अचिन्हित दीर्घ phys_addr;
	काष्ठा t4_swsqe *sw_sq;
	काष्ठा t4_swsqe *oldest_पढ़ो;
	व्योम __iomem *bar2_va;
	u64 bar2_pa;
	माप_प्रकार memsize;
	u32 bar2_qid;
	u32 qid;
	u16 in_use;
	u16 size;
	u16 cidx;
	u16 pidx;
	u16 wq_pidx;
	u16 wq_pidx_inc;
	u16 flags;
	लघु flush_cidx;
पूर्ण;

काष्ठा t4_swrqe अणु
	u64 wr_id;
	kसमय_प्रकार	host_समय;
	u64 sge_ts;
	पूर्णांक valid;
पूर्ण;

काष्ठा t4_rq अणु
	जोड़  t4_recv_wr *queue;
	dma_addr_t dma_addr;
	DEFINE_DMA_UNMAP_ADDR(mapping);
	काष्ठा t4_swrqe *sw_rq;
	व्योम __iomem *bar2_va;
	u64 bar2_pa;
	माप_प्रकार memsize;
	u32 bar2_qid;
	u32 qid;
	u32 msn;
	u32 rqt_hwaddr;
	u16 rqt_size;
	u16 in_use;
	u16 size;
	u16 cidx;
	u16 pidx;
	u16 wq_pidx;
	u16 wq_pidx_inc;
पूर्ण;

काष्ठा t4_wq अणु
	काष्ठा t4_sq sq;
	काष्ठा t4_rq rq;
	व्योम __iomem *db;
	काष्ठा c4iw_rdev *rdev;
	पूर्णांक flushed;
	u8 *qp_errp;
	u32 *srqidxp;
पूर्ण;

काष्ठा t4_srq_pending_wr अणु
	u64 wr_id;
	जोड़ t4_recv_wr wqe;
	u8 len16;
पूर्ण;

काष्ठा t4_srq अणु
	जोड़ t4_recv_wr *queue;
	dma_addr_t dma_addr;
	DEFINE_DMA_UNMAP_ADDR(mapping);
	काष्ठा t4_swrqe *sw_rq;
	व्योम __iomem *bar2_va;
	u64 bar2_pa;
	माप_प्रकार memsize;
	u32 bar2_qid;
	u32 qid;
	u32 msn;
	u32 rqt_hwaddr;
	u32 rqt_असल_idx;
	u16 rqt_size;
	u16 size;
	u16 cidx;
	u16 pidx;
	u16 wq_pidx;
	u16 wq_pidx_inc;
	u16 in_use;
	काष्ठा t4_srq_pending_wr *pending_wrs;
	u16 pending_cidx;
	u16 pending_pidx;
	u16 pending_in_use;
	u16 ooo_count;
पूर्ण;

अटल अंतरभूत u32 t4_srq_avail(काष्ठा t4_srq *srq)
अणु
	वापस srq->size - 1 - srq->in_use;
पूर्ण

अटल अंतरभूत व्योम t4_srq_produce(काष्ठा t4_srq *srq, u8 len16)
अणु
	srq->in_use++;
	अगर (++srq->pidx == srq->size)
		srq->pidx = 0;
	srq->wq_pidx += DIV_ROUND_UP(len16 * 16, T4_EQ_ENTRY_SIZE);
	अगर (srq->wq_pidx >= srq->size * T4_RQ_NUM_SLOTS)
		srq->wq_pidx %= srq->size * T4_RQ_NUM_SLOTS;
	srq->queue[srq->size].status.host_pidx = srq->pidx;
पूर्ण

अटल अंतरभूत व्योम t4_srq_produce_pending_wr(काष्ठा t4_srq *srq)
अणु
	srq->pending_in_use++;
	srq->in_use++;
	अगर (++srq->pending_pidx == srq->size)
		srq->pending_pidx = 0;
पूर्ण

अटल अंतरभूत व्योम t4_srq_consume_pending_wr(काष्ठा t4_srq *srq)
अणु
	srq->pending_in_use--;
	srq->in_use--;
	अगर (++srq->pending_cidx == srq->size)
		srq->pending_cidx = 0;
पूर्ण

अटल अंतरभूत व्योम t4_srq_produce_ooo(काष्ठा t4_srq *srq)
अणु
	srq->in_use--;
	srq->ooo_count++;
पूर्ण

अटल अंतरभूत व्योम t4_srq_consume_ooo(काष्ठा t4_srq *srq)
अणु
	srq->cidx++;
	अगर (srq->cidx == srq->size)
		srq->cidx  = 0;
	srq->queue[srq->size].status.host_cidx = srq->cidx;
	srq->ooo_count--;
पूर्ण

अटल अंतरभूत व्योम t4_srq_consume(काष्ठा t4_srq *srq)
अणु
	srq->in_use--;
	अगर (++srq->cidx == srq->size)
		srq->cidx = 0;
	srq->queue[srq->size].status.host_cidx = srq->cidx;
पूर्ण

अटल अंतरभूत पूर्णांक t4_rqes_posted(काष्ठा t4_wq *wq)
अणु
	वापस wq->rq.in_use;
पूर्ण

अटल अंतरभूत पूर्णांक t4_rq_empty(काष्ठा t4_wq *wq)
अणु
	वापस wq->rq.in_use == 0;
पूर्ण

अटल अंतरभूत u32 t4_rq_avail(काष्ठा t4_wq *wq)
अणु
	वापस wq->rq.size - 1 - wq->rq.in_use;
पूर्ण

अटल अंतरभूत व्योम t4_rq_produce(काष्ठा t4_wq *wq, u8 len16)
अणु
	wq->rq.in_use++;
	अगर (++wq->rq.pidx == wq->rq.size)
		wq->rq.pidx = 0;
	wq->rq.wq_pidx += DIV_ROUND_UP(len16*16, T4_EQ_ENTRY_SIZE);
	अगर (wq->rq.wq_pidx >= wq->rq.size * T4_RQ_NUM_SLOTS)
		wq->rq.wq_pidx %= wq->rq.size * T4_RQ_NUM_SLOTS;
पूर्ण

अटल अंतरभूत व्योम t4_rq_consume(काष्ठा t4_wq *wq)
अणु
	wq->rq.in_use--;
	अगर (++wq->rq.cidx == wq->rq.size)
		wq->rq.cidx = 0;
पूर्ण

अटल अंतरभूत u16 t4_rq_host_wq_pidx(काष्ठा t4_wq *wq)
अणु
	वापस wq->rq.queue[wq->rq.size].status.host_wq_pidx;
पूर्ण

अटल अंतरभूत u16 t4_rq_wq_size(काष्ठा t4_wq *wq)
अणु
		वापस wq->rq.size * T4_RQ_NUM_SLOTS;
पूर्ण

अटल अंतरभूत पूर्णांक t4_sq_onchip(काष्ठा t4_sq *sq)
अणु
	वापस sq->flags & T4_SQ_ONCHIP;
पूर्ण

अटल अंतरभूत पूर्णांक t4_sq_empty(काष्ठा t4_wq *wq)
अणु
	वापस wq->sq.in_use == 0;
पूर्ण

अटल अंतरभूत u32 t4_sq_avail(काष्ठा t4_wq *wq)
अणु
	वापस wq->sq.size - 1 - wq->sq.in_use;
पूर्ण

अटल अंतरभूत व्योम t4_sq_produce(काष्ठा t4_wq *wq, u8 len16)
अणु
	wq->sq.in_use++;
	अगर (++wq->sq.pidx == wq->sq.size)
		wq->sq.pidx = 0;
	wq->sq.wq_pidx += DIV_ROUND_UP(len16*16, T4_EQ_ENTRY_SIZE);
	अगर (wq->sq.wq_pidx >= wq->sq.size * T4_SQ_NUM_SLOTS)
		wq->sq.wq_pidx %= wq->sq.size * T4_SQ_NUM_SLOTS;
पूर्ण

अटल अंतरभूत व्योम t4_sq_consume(काष्ठा t4_wq *wq)
अणु
	अगर (wq->sq.cidx == wq->sq.flush_cidx)
		wq->sq.flush_cidx = -1;
	wq->sq.in_use--;
	अगर (++wq->sq.cidx == wq->sq.size)
		wq->sq.cidx = 0;
पूर्ण

अटल अंतरभूत u16 t4_sq_host_wq_pidx(काष्ठा t4_wq *wq)
अणु
	वापस wq->sq.queue[wq->sq.size].status.host_wq_pidx;
पूर्ण

अटल अंतरभूत u16 t4_sq_wq_size(काष्ठा t4_wq *wq)
अणु
		वापस wq->sq.size * T4_SQ_NUM_SLOTS;
पूर्ण

/* This function copies 64 byte coalesced work request to memory
 * mapped BAR2 space. For coalesced WRs, the SGE fetches data
 * from the FIFO instead of from Host.
 */
अटल अंतरभूत व्योम pio_copy(u64 __iomem *dst, u64 *src)
अणु
	पूर्णांक count = 8;

	जबतक (count) अणु
		ग_लिखोq(*src, dst);
		src++;
		dst++;
		count--;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम t4_ring_srq_db(काष्ठा t4_srq *srq, u16 inc, u8 len16,
				  जोड़ t4_recv_wr *wqe)
अणु
	/* Flush host queue memory ग_लिखोs. */
	wmb();
	अगर (inc == 1 && srq->bar2_qid == 0 && wqe) अणु
		pr_debug("%s : WC srq->pidx = %d; len16=%d\n",
			 __func__, srq->pidx, len16);
		pio_copy(srq->bar2_va + SGE_UDB_WCDOORBELL, (u64 *)wqe);
	पूर्ण अन्यथा अणु
		pr_debug("%s: DB srq->pidx = %d; len16=%d\n",
			 __func__, srq->pidx, len16);
		ग_लिखोl(PIDX_T5_V(inc) | QID_V(srq->bar2_qid),
		       srq->bar2_va + SGE_UDB_KDOORBELL);
	पूर्ण
	/* Flush user करोorbell area ग_लिखोs. */
	wmb();
पूर्ण

अटल अंतरभूत व्योम t4_ring_sq_db(काष्ठा t4_wq *wq, u16 inc, जोड़ t4_wr *wqe)
अणु

	/* Flush host queue memory ग_लिखोs. */
	wmb();
	अगर (wq->sq.bar2_va) अणु
		अगर (inc == 1 && wq->sq.bar2_qid == 0 && wqe) अणु
			pr_debug("WC wq->sq.pidx = %d\n", wq->sq.pidx);
			pio_copy((u64 __iomem *)
				 (wq->sq.bar2_va + SGE_UDB_WCDOORBELL),
				 (u64 *)wqe);
		पूर्ण अन्यथा अणु
			pr_debug("DB wq->sq.pidx = %d\n", wq->sq.pidx);
			ग_लिखोl(PIDX_T5_V(inc) | QID_V(wq->sq.bar2_qid),
			       wq->sq.bar2_va + SGE_UDB_KDOORBELL);
		पूर्ण

		/* Flush user करोorbell area ग_लिखोs. */
		wmb();
		वापस;
	पूर्ण
	ग_लिखोl(QID_V(wq->sq.qid) | PIDX_V(inc), wq->db);
पूर्ण

अटल अंतरभूत व्योम t4_ring_rq_db(काष्ठा t4_wq *wq, u16 inc,
				 जोड़ t4_recv_wr *wqe)
अणु

	/* Flush host queue memory ग_लिखोs. */
	wmb();
	अगर (wq->rq.bar2_va) अणु
		अगर (inc == 1 && wq->rq.bar2_qid == 0 && wqe) अणु
			pr_debug("WC wq->rq.pidx = %d\n", wq->rq.pidx);
			pio_copy((u64 __iomem *)
				 (wq->rq.bar2_va + SGE_UDB_WCDOORBELL),
				 (व्योम *)wqe);
		पूर्ण अन्यथा अणु
			pr_debug("DB wq->rq.pidx = %d\n", wq->rq.pidx);
			ग_लिखोl(PIDX_T5_V(inc) | QID_V(wq->rq.bar2_qid),
			       wq->rq.bar2_va + SGE_UDB_KDOORBELL);
		पूर्ण

		/* Flush user करोorbell area ग_लिखोs. */
		wmb();
		वापस;
	पूर्ण
	ग_लिखोl(QID_V(wq->rq.qid) | PIDX_V(inc), wq->db);
पूर्ण

अटल अंतरभूत पूर्णांक t4_wq_in_error(काष्ठा t4_wq *wq)
अणु
	वापस *wq->qp_errp;
पूर्ण

अटल अंतरभूत व्योम t4_set_wq_in_error(काष्ठा t4_wq *wq, u32 srqidx)
अणु
	अगर (srqidx)
		*wq->srqidxp = srqidx;
	*wq->qp_errp = 1;
पूर्ण

अटल अंतरभूत व्योम t4_disable_wq_db(काष्ठा t4_wq *wq)
अणु
	wq->rq.queue[wq->rq.size].status.db_off = 1;
पूर्ण

अटल अंतरभूत व्योम t4_enable_wq_db(काष्ठा t4_wq *wq)
अणु
	wq->rq.queue[wq->rq.size].status.db_off = 0;
पूर्ण

क्रमागत t4_cq_flags अणु
	CQ_ARMED	= 1,
पूर्ण;

काष्ठा t4_cq अणु
	काष्ठा t4_cqe *queue;
	dma_addr_t dma_addr;
	DEFINE_DMA_UNMAP_ADDR(mapping);
	काष्ठा t4_cqe *sw_queue;
	व्योम __iomem *gts;
	व्योम __iomem *bar2_va;
	u64 bar2_pa;
	u32 bar2_qid;
	काष्ठा c4iw_rdev *rdev;
	माप_प्रकार memsize;
	__be64 bits_type_ts;
	u32 cqid;
	u32 qid_mask;
	पूर्णांक vector;
	u16 size; /* including status page */
	u16 cidx;
	u16 sw_pidx;
	u16 sw_cidx;
	u16 sw_in_use;
	u16 cidx_inc;
	u8 gen;
	u8 error;
	u8 *qp_errp;
	अचिन्हित दीर्घ flags;
पूर्ण;

अटल अंतरभूत व्योम ग_लिखो_gts(काष्ठा t4_cq *cq, u32 val)
अणु
	अगर (cq->bar2_va)
		ग_लिखोl(val | INGRESSQID_V(cq->bar2_qid),
		       cq->bar2_va + SGE_UDB_GTS);
	अन्यथा
		ग_लिखोl(val | INGRESSQID_V(cq->cqid), cq->gts);
पूर्ण

अटल अंतरभूत पूर्णांक t4_clear_cq_armed(काष्ठा t4_cq *cq)
अणु
	वापस test_and_clear_bit(CQ_ARMED, &cq->flags);
पूर्ण

अटल अंतरभूत पूर्णांक t4_arm_cq(काष्ठा t4_cq *cq, पूर्णांक se)
अणु
	u32 val;

	set_bit(CQ_ARMED, &cq->flags);
	जबतक (cq->cidx_inc > CIDXINC_M) अणु
		val = SEINTARM_V(0) | CIDXINC_V(CIDXINC_M) | TIMERREG_V(7);
		ग_लिखो_gts(cq, val);
		cq->cidx_inc -= CIDXINC_M;
	पूर्ण
	val = SEINTARM_V(se) | CIDXINC_V(cq->cidx_inc) | TIMERREG_V(6);
	ग_लिखो_gts(cq, val);
	cq->cidx_inc = 0;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम t4_swcq_produce(काष्ठा t4_cq *cq)
अणु
	cq->sw_in_use++;
	अगर (cq->sw_in_use == cq->size) अणु
		pr_warn("%s cxgb4 sw cq overflow cqid %u\n",
			__func__, cq->cqid);
		cq->error = 1;
		cq->sw_in_use--;
		वापस;
	पूर्ण
	अगर (++cq->sw_pidx == cq->size)
		cq->sw_pidx = 0;
पूर्ण

अटल अंतरभूत व्योम t4_swcq_consume(काष्ठा t4_cq *cq)
अणु
	cq->sw_in_use--;
	अगर (++cq->sw_cidx == cq->size)
		cq->sw_cidx = 0;
पूर्ण

अटल अंतरभूत व्योम t4_hwcq_consume(काष्ठा t4_cq *cq)
अणु
	cq->bits_type_ts = cq->queue[cq->cidx].bits_type_ts;
	अगर (++cq->cidx_inc == (cq->size >> 4) || cq->cidx_inc == CIDXINC_M) अणु
		u32 val;

		val = SEINTARM_V(0) | CIDXINC_V(cq->cidx_inc) | TIMERREG_V(7);
		ग_लिखो_gts(cq, val);
		cq->cidx_inc = 0;
	पूर्ण
	अगर (++cq->cidx == cq->size) अणु
		cq->cidx = 0;
		cq->gen ^= 1;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक t4_valid_cqe(काष्ठा t4_cq *cq, काष्ठा t4_cqe *cqe)
अणु
	वापस (CQE_GENBIT(cqe) == cq->gen);
पूर्ण

अटल अंतरभूत पूर्णांक t4_cq_notempty(काष्ठा t4_cq *cq)
अणु
	वापस cq->sw_in_use || t4_valid_cqe(cq, &cq->queue[cq->cidx]);
पूर्ण

अटल अंतरभूत पूर्णांक t4_next_hw_cqe(काष्ठा t4_cq *cq, काष्ठा t4_cqe **cqe)
अणु
	पूर्णांक ret;
	u16 prev_cidx;

	अगर (cq->cidx == 0)
		prev_cidx = cq->size - 1;
	अन्यथा
		prev_cidx = cq->cidx - 1;

	अगर (cq->queue[prev_cidx].bits_type_ts != cq->bits_type_ts) अणु
		ret = -EOVERFLOW;
		cq->error = 1;
		pr_err("cq overflow cqid %u\n", cq->cqid);
	पूर्ण अन्यथा अगर (t4_valid_cqe(cq, &cq->queue[cq->cidx])) अणु

		/* Ensure CQE is flushed to memory */
		rmb();
		*cqe = &cq->queue[cq->cidx];
		ret = 0;
	पूर्ण अन्यथा
		ret = -ENODATA;
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक t4_next_cqe(काष्ठा t4_cq *cq, काष्ठा t4_cqe **cqe)
अणु
	पूर्णांक ret = 0;

	अगर (cq->error)
		ret = -ENODATA;
	अन्यथा अगर (cq->sw_in_use)
		*cqe = &cq->sw_queue[cq->sw_cidx];
	अन्यथा
		ret = t4_next_hw_cqe(cq, cqe);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम t4_set_cq_in_error(काष्ठा t4_cq *cq)
अणु
	*cq->qp_errp = 1;
पूर्ण
#पूर्ण_अगर

काष्ठा t4_dev_status_page अणु
	u8 db_off;
	u8 ग_लिखो_cmpl_supported;
	u16 pad2;
	u32 pad3;
	u64 qp_start;
	u64 qp_size;
	u64 cq_start;
	u64 cq_size;
पूर्ण;
