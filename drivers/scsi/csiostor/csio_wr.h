<शैली गुरु>
/*
 * This file is part of the Chelsio FCoE driver क्रम Linux.
 *
 * Copyright (c) 2008-2012 Chelsio Communications, Inc. All rights reserved.
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

#अगर_अघोषित __CSIO_WR_H__
#घोषणा __CSIO_WR_H__

#समावेश <linux/cache.h>

#समावेश "csio_defs.h"
#समावेश "t4fw_api.h"
#समावेश "t4fw_api_stor.h"

/*
 * SGE रेजिस्टर field values.
 */
#घोषणा X_INGPCIEBOUNDARY_32B		0
#घोषणा X_INGPCIEBOUNDARY_64B		1
#घोषणा X_INGPCIEBOUNDARY_128B		2
#घोषणा X_INGPCIEBOUNDARY_256B		3
#घोषणा X_INGPCIEBOUNDARY_512B		4
#घोषणा X_INGPCIEBOUNDARY_1024B		5
#घोषणा X_INGPCIEBOUNDARY_2048B		6
#घोषणा X_INGPCIEBOUNDARY_4096B		7

/* GTS रेजिस्टर */
#घोषणा X_TIMERREG_COUNTER0		0
#घोषणा X_TIMERREG_COUNTER1		1
#घोषणा X_TIMERREG_COUNTER2		2
#घोषणा X_TIMERREG_COUNTER3		3
#घोषणा X_TIMERREG_COUNTER4		4
#घोषणा X_TIMERREG_COUNTER5		5
#घोषणा X_TIMERREG_RESTART_COUNTER	6
#घोषणा X_TIMERREG_UPDATE_CIDX		7

/*
 * Egress Context field values
 */
#घोषणा X_FETCHBURSTMIN_16B		0
#घोषणा X_FETCHBURSTMIN_32B		1
#घोषणा X_FETCHBURSTMIN_64B		2
#घोषणा X_FETCHBURSTMIN_128B		3

#घोषणा X_FETCHBURSTMAX_64B		0
#घोषणा X_FETCHBURSTMAX_128B		1
#घोषणा X_FETCHBURSTMAX_256B		2
#घोषणा X_FETCHBURSTMAX_512B		3

#घोषणा X_HOSTFCMODE_NONE		0
#घोषणा X_HOSTFCMODE_INGRESS_QUEUE	1
#घोषणा X_HOSTFCMODE_STATUS_PAGE	2
#घोषणा X_HOSTFCMODE_BOTH		3

/*
 * Ingress Context field values
 */
#घोषणा X_UPDATESCHEDULING_TIMER	0
#घोषणा X_UPDATESCHEDULING_COUNTER_OPTTIMER	1

#घोषणा X_UPDATEDELIVERY_NONE		0
#घोषणा X_UPDATEDELIVERY_INTERRUPT	1
#घोषणा X_UPDATEDELIVERY_STATUS_PAGE	2
#घोषणा X_UPDATEDELIVERY_BOTH		3

#घोषणा X_INTERRUPTDESTINATION_PCIE	0
#घोषणा X_INTERRUPTDESTINATION_IQ	1

#घोषणा X_RSPD_TYPE_FLBUF		0
#घोषणा X_RSPD_TYPE_CPL			1
#घोषणा X_RSPD_TYPE_INTR		2

/* WR status is at the same position as retval in a CMD header */
#घोषणा csio_wr_status(_wr)		\
		(FW_CMD_RETVAL_G(ntohl(((काष्ठा fw_cmd_hdr *)(_wr))->lo)))

काष्ठा csio_hw;

बाह्य पूर्णांक csio_पूर्णांकr_coalesce_cnt;
बाह्य पूर्णांक csio_पूर्णांकr_coalesce_समय;

/* Ingress queue params */
काष्ठा csio_iq_params अणु

	uपूर्णांक8_t		iq_start:1;
	uपूर्णांक8_t		iq_stop:1;
	uपूर्णांक8_t		pfn:3;

	uपूर्णांक8_t		vfn;

	uपूर्णांक16_t	physiqid;
	uपूर्णांक16_t	iqid;

	uपूर्णांक16_t	fl0id;
	uपूर्णांक16_t	fl1id;

	uपूर्णांक8_t		viid;

	uपूर्णांक8_t		type;
	uपूर्णांक8_t		iqasynch;
	uपूर्णांक8_t		reserved4;

	uपूर्णांक8_t		iqandst;
	uपूर्णांक8_t		iqanus;
	uपूर्णांक8_t		iqanud;

	uपूर्णांक16_t	iqandstindex;

	uपूर्णांक8_t		iqdroprss;
	uपूर्णांक8_t		iqpciech;
	uपूर्णांक8_t		iqdcaen;

	uपूर्णांक8_t		iqdcacpu;
	uपूर्णांक8_t		iqपूर्णांकcntthresh;
	uपूर्णांक8_t		iqo;

	uपूर्णांक8_t		iqcprio;
	uपूर्णांक8_t		iqesize;

	uपूर्णांक16_t	iqsize;

	uपूर्णांक64_t	iqaddr;

	uपूर्णांक8_t		iqflपूर्णांकiqhsen;
	uपूर्णांक8_t		reserved5;
	uपूर्णांक8_t		iqflपूर्णांकcongen;
	uपूर्णांक8_t		iqflपूर्णांकcngchmap;

	uपूर्णांक32_t	reserved6;

	uपूर्णांक8_t		fl0hostfcmode;
	uपूर्णांक8_t		fl0cprio;
	uपूर्णांक8_t		fl0paden;
	uपूर्णांक8_t		fl0packen;
	uपूर्णांक8_t		fl0congen;
	uपूर्णांक8_t		fl0dcaen;

	uपूर्णांक8_t		fl0dcacpu;
	uपूर्णांक8_t		fl0fbmin;

	uपूर्णांक8_t		fl0fbmax;
	uपूर्णांक8_t		fl0cidxfthresho;
	uपूर्णांक8_t		fl0cidxfthresh;

	uपूर्णांक16_t	fl0size;

	uपूर्णांक64_t	fl0addr;

	uपूर्णांक64_t	reserved7;

	uपूर्णांक8_t		fl1hostfcmode;
	uपूर्णांक8_t		fl1cprio;
	uपूर्णांक8_t		fl1paden;
	uपूर्णांक8_t		fl1packen;
	uपूर्णांक8_t		fl1congen;
	uपूर्णांक8_t		fl1dcaen;

	uपूर्णांक8_t		fl1dcacpu;
	uपूर्णांक8_t		fl1fbmin;

	uपूर्णांक8_t		fl1fbmax;
	uपूर्णांक8_t		fl1cidxfthresho;
	uपूर्णांक8_t		fl1cidxfthresh;

	uपूर्णांक16_t	fl1size;

	uपूर्णांक64_t	fl1addr;
पूर्ण;

/* Egress queue params */
काष्ठा csio_eq_params अणु

	uपूर्णांक8_t		pfn;
	uपूर्णांक8_t		vfn;

	uपूर्णांक8_t		eqstart:1;
	uपूर्णांक8_t		eqstop:1;

	uपूर्णांक16_t        physeqid;
	uपूर्णांक32_t	eqid;

	uपूर्णांक8_t		hostfcmode:2;
	uपूर्णांक8_t		cprio:1;
	uपूर्णांक8_t		pciechn:3;

	uपूर्णांक16_t	iqid;

	uपूर्णांक8_t		dcaen:1;
	uपूर्णांक8_t		dcacpu:5;

	uपूर्णांक8_t		fbmin:3;
	uपूर्णांक8_t		fbmax:3;

	uपूर्णांक8_t		cidxfthresho:1;
	uपूर्णांक8_t		cidxfthresh:3;

	uपूर्णांक16_t	eqsize;

	uपूर्णांक64_t	eqaddr;
पूर्ण;

काष्ठा csio_dma_buf अणु
	काष्ठा list_head	list;
	व्योम			*vaddr;		/* Virtual address */
	dma_addr_t		paddr;		/* Physical address */
	uपूर्णांक32_t		len;		/* Buffer size */
पूर्ण;

/* Generic I/O request काष्ठाure */
काष्ठा csio_ioreq अणु
	काष्ठा csio_sm		sm;		/* SM, List
						 * should be the first member
						 */
	पूर्णांक			iq_idx;		/* Ingress queue index */
	पूर्णांक			eq_idx;		/* Egress queue index */
	uपूर्णांक32_t		nsge;		/* Number of SG elements */
	uपूर्णांक32_t		पंचांगo;		/* Driver समयout */
	uपूर्णांक32_t		datadir;	/* Data direction */
	काष्ठा csio_dma_buf	dma_buf;	/* Req/resp DMA buffers */
	uपूर्णांक16_t		wr_status;	/* WR completion status */
	पूर्णांक16_t			drv_status;	/* Driver पूर्णांकernal status */
	काष्ठा csio_lnode	*lnode;		/* Owner lnode */
	काष्ठा csio_rnode	*rnode;		/* Src/destination rnode */
	व्योम (*io_cbfn) (काष्ठा csio_hw *, काष्ठा csio_ioreq *);
						/* completion callback */
	व्योम			*scratch1;	/* Scratch area 1.
						 */
	व्योम			*scratch2;	/* Scratch area 2. */
	काष्ठा list_head	gen_list;	/* Any list associated with
						 * this ioreq.
						 */
	uपूर्णांक64_t		fw_handle;	/* Unique handle passed
						 * to FW
						 */
	uपूर्णांक8_t			dcopy;		/* Data copy required */
	uपूर्णांक8_t			reserved1;
	uपूर्णांक16_t		reserved2;
	काष्ठा completion	cmplobj;	/* ioreq completion object */
पूर्ण ____cacheline_aligned_in_smp;

/*
 * Egress status page क्रम egress cidx updates
 */
काष्ठा csio_qstatus_page अणु
	__be32 qid;
	__be16 cidx;
	__be16 pidx;
पूर्ण;


क्रमागत अणु
	CSIO_MAX_FLBUF_PER_IQWR = 4,
	CSIO_QCREDIT_SZ  = 64,			/* pidx/cidx increments
						 * in bytes
						 */
	CSIO_MAX_QID = 0xFFFF,
	CSIO_MAX_IQ = 128,

	CSIO_SGE_NTIMERS = 6,
	CSIO_SGE_NCOUNTERS = 4,
	CSIO_SGE_FL_SIZE_REGS = 16,
पूर्ण;

/* Defines क्रम type */
क्रमागत अणु
	CSIO_EGRESS	= 1,
	CSIO_INGRESS	= 2,
	CSIO_FREELIST	= 3,
पूर्ण;

/*
 * Structure क्रम footer (last 2 flits) of Ingress Queue Entry.
 */
काष्ठा csio_iqwr_footer अणु
	__be32			hdrbuflen_pidx;
	__be32			pldbuflen_qid;
	जोड़ अणु
		u8		type_gen;
		__be64		last_flit;
	पूर्ण u;
पूर्ण;

#घोषणा IQWRF_NEWBUF		(1 << 31)
#घोषणा IQWRF_LEN_GET(x)	(((x) >> 0) & 0x7fffffffU)
#घोषणा IQWRF_GEN_SHIFT		7
#घोषणा IQWRF_TYPE_GET(x)	(((x) >> 4) & 0x3U)


/*
 * WR pair:
 * ========
 * A WR can start towards the end of a queue, and then जारी at the
 * beginning, since the queue is considered to be circular. This will
 * require a pair of address/len to be passed back to the caller -
 * hence the Work request pair काष्ठाure.
 */
काष्ठा csio_wr_pair अणु
	व्योम			*addr1;
	uपूर्णांक32_t		size1;
	व्योम			*addr2;
	uपूर्णांक32_t		size2;
पूर्ण;

/*
 * The following काष्ठाure is used by ingress processing to वापस the
 * मुक्त list buffers to consumers.
 */
काष्ठा csio_fl_dma_buf अणु
	काष्ठा csio_dma_buf	flbufs[CSIO_MAX_FLBUF_PER_IQWR];
						/* Freelist DMA buffers */
	पूर्णांक			offset;		/* Offset within the
						 * first FL buf.
						 */
	uपूर्णांक32_t		totlen;		/* Total length */
	uपूर्णांक8_t			defer_मुक्त;	/* Free of buffer can
						 * deferred
						 */
पूर्ण;

/* Data-types */
प्रकार व्योम (*iq_handler_t)(काष्ठा csio_hw *, व्योम *, uपूर्णांक32_t,
			     काष्ठा csio_fl_dma_buf *, व्योम *);

काष्ठा csio_iq अणु
	uपूर्णांक16_t		iqid;		/* Queue ID */
	uपूर्णांक16_t		physiqid;	/* Physical Queue ID */
	uपूर्णांक16_t		genbit;		/* Generation bit,
						 * initially set to 1
						 */
	पूर्णांक			flq_idx;	/* Freelist queue index */
	iq_handler_t		iq_पूर्णांकx_handler; /* IQ INTx handler routine */
पूर्ण;

काष्ठा csio_eq अणु
	uपूर्णांक16_t		eqid;		/* Qid */
	uपूर्णांक16_t		physeqid;	/* Physical Queue ID */
	uपूर्णांक8_t			wrap[512];	/* Temp area क्रम q-wrap around*/
पूर्ण;

काष्ठा csio_fl अणु
	uपूर्णांक16_t		flid;		/* Qid */
	uपूर्णांक16_t		packen;		/* Packing enabled? */
	पूर्णांक			offset;		/* Offset within FL buf */
	पूर्णांक			sreg;		/* Size रेजिस्टर */
	काष्ठा csio_dma_buf	*bufs;		/* Free list buffer ptr array
						 * indexed using flq->cidx/pidx
						 */
पूर्ण;

काष्ठा csio_qstats अणु
	uपूर्णांक32_t	n_tot_reqs;		/* Total no. of Requests */
	uपूर्णांक32_t	n_tot_rsps;		/* Total no. of responses */
	uपूर्णांक32_t	n_qwrap;		/* Queue wraps */
	uपूर्णांक32_t	n_eq_wr_split;		/* Number of split EQ WRs */
	uपूर्णांक32_t	n_qentry;		/* Queue entry */
	uपूर्णांक32_t	n_qempty;		/* Queue empty */
	uपूर्णांक32_t	n_qfull;		/* Queue fulls */
	uपूर्णांक32_t	n_rsp_unknown;		/* Unknown response type */
	uपूर्णांक32_t	n_stray_comp;		/* Stray completion पूर्णांकr */
	uपूर्णांक32_t	n_flq_refill;		/* Number of FL refills */
पूर्ण;

/* Queue metadata */
काष्ठा csio_q अणु
	uपूर्णांक16_t		type;		/* Type: Ingress/Egress/FL */
	uपूर्णांक16_t		pidx;		/* producer index */
	uपूर्णांक16_t		cidx;		/* consumer index */
	uपूर्णांक16_t		inc_idx;	/* Incremental index */
	uपूर्णांक32_t		wr_sz;		/* Size of all WRs in this q
						 * अगर fixed
						 */
	व्योम			*vstart;	/* Base भव address
						 * of queue
						 */
	व्योम			*vwrap;		/* Virtual end address to
						 * wrap around at
						 */
	uपूर्णांक32_t		credits;	/* Size of queue in credits */
	व्योम			*owner;		/* Owner */
	जोड़ अणु					/* Queue contexts */
		काष्ठा csio_iq	iq;
		काष्ठा csio_eq	eq;
		काष्ठा csio_fl	fl;
	पूर्ण un;

	dma_addr_t		pstart;		/* Base physical address of
						 * queue
						 */
	uपूर्णांक32_t		portid;		/* PCIE Channel */
	uपूर्णांक32_t		size;		/* Size of queue in bytes */
	काष्ठा csio_qstats	stats;		/* Statistics */
पूर्ण ____cacheline_aligned_in_smp;

काष्ठा csio_sge अणु
	uपूर्णांक32_t	csio_fl_align;		/* Calculated and cached
						 * क्रम fast path
						 */
	uपूर्णांक32_t	sge_control;		/* padding, boundaries,
						 * lengths, etc.
						 */
	uपूर्णांक32_t	sge_host_page_size;	/* Host page size */
	uपूर्णांक32_t	sge_fl_buf_size[CSIO_SGE_FL_SIZE_REGS];
						/* मुक्त list buffer sizes */
	uपूर्णांक16_t	समयr_val[CSIO_SGE_NTIMERS];
	uपूर्णांक8_t		counter_val[CSIO_SGE_NCOUNTERS];
पूर्ण;

/* Work request module */
काष्ठा csio_wrm अणु
	पूर्णांक			num_q;		/* Number of queues */
	काष्ठा csio_q		**q_arr;	/* Array of queue poपूर्णांकers
						 * allocated dynamically
						 * based on configured values
						 */
	uपूर्णांक32_t		fw_iq_start;	/* Start ID of IQ क्रम this fn*/
	uपूर्णांक32_t		fw_eq_start;	/* Start ID of EQ क्रम this fn*/
	काष्ठा csio_q		*पूर्णांकr_map[CSIO_MAX_IQ];
						/* IQ-id to IQ map table. */
	पूर्णांक			मुक्त_qidx;	/* queue idx of मुक्त queue */
	काष्ठा csio_sge		sge;		/* SGE params */
पूर्ण;

#घोषणा csio_get_q(__hw, __idx)		((__hw)->wrm.q_arr[__idx])
#घोषणा	csio_q_type(__hw, __idx)	((__hw)->wrm.q_arr[(__idx)]->type)
#घोषणा	csio_q_pidx(__hw, __idx)	((__hw)->wrm.q_arr[(__idx)]->pidx)
#घोषणा	csio_q_cidx(__hw, __idx)	((__hw)->wrm.q_arr[(__idx)]->cidx)
#घोषणा	csio_q_inc_idx(__hw, __idx)	((__hw)->wrm.q_arr[(__idx)]->inc_idx)
#घोषणा	csio_q_vstart(__hw, __idx)	((__hw)->wrm.q_arr[(__idx)]->vstart)
#घोषणा	csio_q_pstart(__hw, __idx)	((__hw)->wrm.q_arr[(__idx)]->pstart)
#घोषणा	csio_q_size(__hw, __idx)	((__hw)->wrm.q_arr[(__idx)]->size)
#घोषणा	csio_q_credits(__hw, __idx)	((__hw)->wrm.q_arr[(__idx)]->credits)
#घोषणा	csio_q_portid(__hw, __idx)	((__hw)->wrm.q_arr[(__idx)]->portid)
#घोषणा	csio_q_wr_sz(__hw, __idx)	((__hw)->wrm.q_arr[(__idx)]->wr_sz)
#घोषणा	csio_q_iqid(__hw, __idx)	((__hw)->wrm.q_arr[(__idx)]->un.iq.iqid)
#घोषणा csio_q_physiqid(__hw, __idx)					\
				((__hw)->wrm.q_arr[(__idx)]->un.iq.physiqid)
#घोषणा csio_q_iq_flq_idx(__hw, __idx)					\
				((__hw)->wrm.q_arr[(__idx)]->un.iq.flq_idx)
#घोषणा	csio_q_eqid(__hw, __idx)	((__hw)->wrm.q_arr[(__idx)]->un.eq.eqid)
#घोषणा	csio_q_flid(__hw, __idx)	((__hw)->wrm.q_arr[(__idx)]->un.fl.flid)

#घोषणा csio_q_physeqid(__hw, __idx)					\
				((__hw)->wrm.q_arr[(__idx)]->un.eq.physeqid)
#घोषणा csio_iq_has_fl(__iq)		((__iq)->un.iq.flq_idx != -1)

#घोषणा csio_q_iq_to_flid(__hw, __iq_idx)				\
	csio_q_flid((__hw), (__hw)->wrm.q_arr[(__iq_qidx)]->un.iq.flq_idx)
#घोषणा csio_q_set_पूर्णांकr_map(__hw, __iq_idx, __rel_iq_id)		\
		(__hw)->wrm.पूर्णांकr_map[__rel_iq_id] = csio_get_q(__hw, __iq_idx)
#घोषणा	csio_q_eq_wrap(__hw, __idx)	((__hw)->wrm.q_arr[(__idx)]->un.eq.wrap)

काष्ठा csio_mb;

पूर्णांक csio_wr_alloc_q(काष्ठा csio_hw *, uपूर्णांक32_t, uपूर्णांक32_t,
		    uपूर्णांक16_t, व्योम *, uपूर्णांक32_t, पूर्णांक, iq_handler_t);
पूर्णांक csio_wr_iq_create(काष्ठा csio_hw *, व्योम *, पूर्णांक,
				uपूर्णांक32_t, uपूर्णांक8_t, bool,
				व्योम (*)(काष्ठा csio_hw *, काष्ठा csio_mb *));
पूर्णांक csio_wr_eq_create(काष्ठा csio_hw *, व्योम *, पूर्णांक, पूर्णांक, uपूर्णांक8_t,
				व्योम (*)(काष्ठा csio_hw *, काष्ठा csio_mb *));
पूर्णांक csio_wr_destroy_queues(काष्ठा csio_hw *, bool cmd);


पूर्णांक csio_wr_get(काष्ठा csio_hw *, पूर्णांक, uपूर्णांक32_t,
			  काष्ठा csio_wr_pair *);
व्योम csio_wr_copy_to_wrp(व्योम *, काष्ठा csio_wr_pair *, uपूर्णांक32_t, uपूर्णांक32_t);
पूर्णांक csio_wr_issue(काष्ठा csio_hw *, पूर्णांक, bool);
पूर्णांक csio_wr_process_iq(काष्ठा csio_hw *, काष्ठा csio_q *,
				 व्योम (*)(काष्ठा csio_hw *, व्योम *,
					  uपूर्णांक32_t, काष्ठा csio_fl_dma_buf *,
					  व्योम *),
				 व्योम *);
पूर्णांक csio_wr_process_iq_idx(काष्ठा csio_hw *, पूर्णांक,
				 व्योम (*)(काष्ठा csio_hw *, व्योम *,
					  uपूर्णांक32_t, काष्ठा csio_fl_dma_buf *,
					  व्योम *),
				 व्योम *);

व्योम csio_wr_sge_init(काष्ठा csio_hw *);
पूर्णांक csio_wrm_init(काष्ठा csio_wrm *, काष्ठा csio_hw *);
व्योम csio_wrm_निकास(काष्ठा csio_wrm *, काष्ठा csio_hw *);

#पूर्ण_अगर /* अगरndef __CSIO_WR_H__ */
