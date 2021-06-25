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

#अगर_अघोषित __CSIO_SCSI_H__
#घोषणा __CSIO_SCSI_H__

#समावेश <linux/spinlock_types.h>
#समावेश <linux/completion.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/fc/fc_fcp.h>

#समावेश "csio_defs.h"
#समावेश "csio_wr.h"

बाह्य काष्ठा scsi_host_ढाँचा csio_fcoe_shost_ढाँचा;
बाह्य काष्ठा scsi_host_ढाँचा csio_fcoe_shost_vport_ढाँचा;

बाह्य पूर्णांक csio_scsi_eqsize;
बाह्य पूर्णांक csio_scsi_iqlen;
बाह्य पूर्णांक csio_scsi_ioreqs;
बाह्य uपूर्णांक32_t csio_max_scan_पंचांगo;
बाह्य uपूर्णांक32_t csio_delta_scan_पंचांगo;
बाह्य पूर्णांक csio_lun_qdepth;

/*
 **************************** NOTE *******************************
 * How करो we calculate MAX FCoE SCSI SGEs? Here is the math:
 * Max Egress WR size = 512 bytes
 * One SCSI egress WR has the following fixed no of bytes:
 *      48 (माप(काष्ठा fw_scsi_ग_लिखो[पढ़ो]_wr)) - FW WR
 *    + 32 (माप(काष्ठा fc_fcp_cmnd)) - Immediate FCP_CMD
 *    ------
 *      80
 *    ------
 * That leaves us with 512 - 96 = 432 bytes क्रम data SGE. Using
 * काष्ठा ulptx_sgl header क्रम the SGE consumes:
 *	- 4 bytes क्रम cmnd_sge.
 *	- 12 bytes क्रम the first SGL.
 * That leaves us with 416 bytes क्रम the reमुख्यing SGE pairs. Which is
 * is 416 / 24 (size(काष्ठा ulptx_sge_pair)) = 17 SGE pairs,
 * or 34 SGEs. Adding the first SGE fetches us 35 SGEs.
 */
#घोषणा CSIO_SCSI_MAX_SGE		35
#घोषणा CSIO_SCSI_ABRT_TMO_MS		60000
#घोषणा CSIO_SCSI_LUNRST_TMO_MS		60000
#घोषणा CSIO_SCSI_TM_POLL_MS		2000	/* should be less than
						 * all TM समयouts.
						 */
#घोषणा CSIO_SCSI_IQ_WRSZ		128
#घोषणा CSIO_SCSI_IQSIZE		(csio_scsi_iqlen * CSIO_SCSI_IQ_WRSZ)

#घोषणा	CSIO_MAX_SNS_LEN		128
#घोषणा	CSIO_SCSI_RSP_LEN	(FCP_RESP_WITH_EXT + 4 + CSIO_MAX_SNS_LEN)

/* Reference to scsi_cmnd */
#घोषणा csio_scsi_cmnd(req)		((req)->scratch1)

काष्ठा csio_scsi_stats अणु
	uपूर्णांक64_t		n_tot_success;	/* Total number of good I/Os */
	uपूर्णांक32_t		n_rn_nr_error;	/* No. of remote-node-not-
						 * पढ़ोy errors
						 */
	uपूर्णांक32_t		n_hw_nr_error;	/* No. of hw-module-not-
						 * पढ़ोy errors
						 */
	uपूर्णांक32_t		n_dmamap_error;	/* No. of DMA map erros */
	uपूर्णांक32_t		n_unsupp_sge_error; /* No. of too-many-SGes
						     * errors.
						     */
	uपूर्णांक32_t		n_no_req_error;	/* No. of Out-of-ioreqs error */
	uपूर्णांक32_t		n_busy_error;	/* No. of -EBUSY errors */
	uपूर्णांक32_t		n_hosterror;	/* No. of FW_HOSTERROR I/O */
	uपूर्णांक32_t		n_rsलिखो_त्रुटि;	/* No. of response errors */
	uपूर्णांक32_t		n_स्वतःsense;	/* No. of स्वतः sense replies */
	uपूर्णांक32_t		n_ovflerror;	/* No. of overflow errors */
	uपूर्णांक32_t		n_unflerror;	/* No. of underflow errors */
	uपूर्णांक32_t		n_rdev_nr_error;/* No. of rdev not
						 * पढ़ोy errors
						 */
	uपूर्णांक32_t		n_rdev_lost_error;/* No. of rdev lost errors */
	uपूर्णांक32_t		n_rdev_logo_error;/* No. of rdev logo errors */
	uपूर्णांक32_t		n_link_करोwn_error;/* No. of link करोwn errors */
	uपूर्णांक32_t		n_no_xchg_error; /* No. no exchange error */
	uपूर्णांक32_t		n_unknown_error;/* No. of unhandled errors */
	uपूर्णांक32_t		n_पातed;	/* No. of पातed I/Os */
	uपूर्णांक32_t		n_abrt_समयकरोut; /* No. of पात समयकरोuts */
	uपूर्णांक32_t		n_abrt_fail;	/* No. of पात failures */
	uपूर्णांक32_t		n_abrt_dups;	/* No. of duplicate पातs */
	uपूर्णांक32_t		n_abrt_race_comp; /* No. of पातs that raced
						   * with completions.
						   */
	uपूर्णांक32_t		n_abrt_busy_error;/* No. of पात failures
						   * due to -EBUSY.
						   */
	uपूर्णांक32_t		n_बंदd;	/* No. of बंदd I/Os */
	uपूर्णांक32_t		n_cls_busy_error; /* No. of बंद failures
						   * due to -EBUSY.
						   */
	uपूर्णांक32_t		n_active;	/* No. of IOs in active_q */
	uपूर्णांक32_t		n_पंचांग_active;	/* No. of TMs in active_q */
	uपूर्णांक32_t		n_wcbfn;	/* No. of I/Os in worker
						 * cbfn q
						 */
	uपूर्णांक32_t		n_मुक्त_ioreq;	/* No. of मुक्तlist entries */
	uपूर्णांक32_t		n_मुक्त_ddp;	/* No. of DDP मुक्तlist */
	uपूर्णांक32_t		n_unaligned;	/* No. of Unaligned SGls */
	uपूर्णांक32_t		n_inval_cplop;	/* No. invalid CPL op's in IQ */
	uपूर्णांक32_t		n_inval_scsiop;	/* No. invalid scsi op's in IQ*/
पूर्ण;

काष्ठा csio_scsim अणु
	काष्ठा csio_hw		*hw;		/* Poपूर्णांकer to HW moduel */
	uपूर्णांक8_t			max_sge;	/* Max SGE */
	uपूर्णांक8_t			proto_cmd_len;	/* Proto specअगरic SCSI
						 * cmd length
						 */
	uपूर्णांक16_t		proto_rsp_len;	/* Proto specअगरic SCSI
						 * response length
						 */
	spinlock_t		मुक्तlist_lock;	/* Lock क्रम ioreq मुक्तlist */
	काष्ठा list_head	active_q;	/* Outstanding SCSI I/Os */
	काष्ठा list_head	ioreq_मुक्तlist;	/* Free list of ioreq's */
	काष्ठा list_head	ddp_मुक्तlist;	/* DDP descriptor मुक्तlist */
	काष्ठा csio_scsi_stats	stats;		/* This module's statistics */
पूर्ण;

/* State machine defines */
क्रमागत csio_scsi_ev अणु
	CSIO_SCSIE_START_IO = 1,		/* Start a regular SCSI IO */
	CSIO_SCSIE_START_TM,			/* Start a TM IO */
	CSIO_SCSIE_COMPLETED,			/* IO Completed */
	CSIO_SCSIE_ABORT,			/* Abort IO */
	CSIO_SCSIE_ABORTED,			/* IO Aborted */
	CSIO_SCSIE_CLOSE,			/* Close exchange */
	CSIO_SCSIE_CLOSED,			/* Exchange बंदd */
	CSIO_SCSIE_DRVCLEANUP,			/* Driver wants to manually
						 * cleanup this I/O.
						 */
पूर्ण;

क्रमागत csio_scsi_lev अणु
	CSIO_LEV_ALL = 1,
	CSIO_LEV_LNODE,
	CSIO_LEV_RNODE,
	CSIO_LEV_LUN,
पूर्ण;

काष्ठा csio_scsi_level_data अणु
	क्रमागत csio_scsi_lev	level;
	काष्ठा csio_rnode	*rnode;
	काष्ठा csio_lnode	*lnode;
	uपूर्णांक64_t		oslun;
पूर्ण;

अटल अंतरभूत काष्ठा csio_ioreq *
csio_get_scsi_ioreq(काष्ठा csio_scsim *scm)
अणु
	काष्ठा csio_sm *req;

	अगर (likely(!list_empty(&scm->ioreq_मुक्तlist))) अणु
		req = list_first_entry(&scm->ioreq_मुक्तlist,
				       काष्ठा csio_sm, sm_list);
		list_del_init(&req->sm_list);
		CSIO_DEC_STATS(scm, n_मुक्त_ioreq);
		वापस (काष्ठा csio_ioreq *)req;
	पूर्ण अन्यथा
		वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम
csio_put_scsi_ioreq(काष्ठा csio_scsim *scm, काष्ठा csio_ioreq *ioreq)
अणु
	list_add_tail(&ioreq->sm.sm_list, &scm->ioreq_मुक्तlist);
	CSIO_INC_STATS(scm, n_मुक्त_ioreq);
पूर्ण

अटल अंतरभूत व्योम
csio_put_scsi_ioreq_list(काष्ठा csio_scsim *scm, काष्ठा list_head *reqlist,
			 पूर्णांक n)
अणु
	list_splice_init(reqlist, &scm->ioreq_मुक्तlist);
	scm->stats.n_मुक्त_ioreq += n;
पूर्ण

अटल अंतरभूत काष्ठा csio_dma_buf *
csio_get_scsi_ddp(काष्ठा csio_scsim *scm)
अणु
	काष्ठा csio_dma_buf *ddp;

	अगर (likely(!list_empty(&scm->ddp_मुक्तlist))) अणु
		ddp = list_first_entry(&scm->ddp_मुक्तlist,
				       काष्ठा csio_dma_buf, list);
		list_del_init(&ddp->list);
		CSIO_DEC_STATS(scm, n_मुक्त_ddp);
		वापस ddp;
	पूर्ण अन्यथा
		वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम
csio_put_scsi_ddp(काष्ठा csio_scsim *scm, काष्ठा csio_dma_buf *ddp)
अणु
	list_add_tail(&ddp->list, &scm->ddp_मुक्तlist);
	CSIO_INC_STATS(scm, n_मुक्त_ddp);
पूर्ण

अटल अंतरभूत व्योम
csio_put_scsi_ddp_list(काष्ठा csio_scsim *scm, काष्ठा list_head *reqlist,
			 पूर्णांक n)
अणु
	list_splice_tail_init(reqlist, &scm->ddp_मुक्तlist);
	scm->stats.n_मुक्त_ddp += n;
पूर्ण

अटल अंतरभूत व्योम
csio_scsi_completed(काष्ठा csio_ioreq *ioreq, काष्ठा list_head *cbfn_q)
अणु
	csio_post_event(&ioreq->sm, CSIO_SCSIE_COMPLETED);
	अगर (csio_list_deleted(&ioreq->sm.sm_list))
		list_add_tail(&ioreq->sm.sm_list, cbfn_q);
पूर्ण

अटल अंतरभूत व्योम
csio_scsi_पातed(काष्ठा csio_ioreq *ioreq, काष्ठा list_head *cbfn_q)
अणु
	csio_post_event(&ioreq->sm, CSIO_SCSIE_ABORTED);
	list_add_tail(&ioreq->sm.sm_list, cbfn_q);
पूर्ण

अटल अंतरभूत व्योम
csio_scsi_बंदd(काष्ठा csio_ioreq *ioreq, काष्ठा list_head *cbfn_q)
अणु
	csio_post_event(&ioreq->sm, CSIO_SCSIE_CLOSED);
	list_add_tail(&ioreq->sm.sm_list, cbfn_q);
पूर्ण

अटल अंतरभूत व्योम
csio_scsi_drvcleanup(काष्ठा csio_ioreq *ioreq)
अणु
	csio_post_event(&ioreq->sm, CSIO_SCSIE_DRVCLEANUP);
पूर्ण

/*
 * csio_scsi_start_io - Kick starts the IO SM.
 * @req: io request SM.
 *
 * needs to be called with lock held.
 */
अटल अंतरभूत पूर्णांक
csio_scsi_start_io(काष्ठा csio_ioreq *ioreq)
अणु
	csio_post_event(&ioreq->sm, CSIO_SCSIE_START_IO);
	वापस ioreq->drv_status;
पूर्ण

/*
 * csio_scsi_start_पंचांग - Kicks off the Task management IO SM.
 * @req: io request SM.
 *
 * needs to be called with lock held.
 */
अटल अंतरभूत पूर्णांक
csio_scsi_start_पंचांग(काष्ठा csio_ioreq *ioreq)
अणु
	csio_post_event(&ioreq->sm, CSIO_SCSIE_START_TM);
	वापस ioreq->drv_status;
पूर्ण

/*
 * csio_scsi_पात - Abort an IO request
 * @req: io request SM.
 *
 * needs to be called with lock held.
 */
अटल अंतरभूत पूर्णांक
csio_scsi_पात(काष्ठा csio_ioreq *ioreq)
अणु
	csio_post_event(&ioreq->sm, CSIO_SCSIE_ABORT);
	वापस ioreq->drv_status;
पूर्ण

/*
 * csio_scsi_बंद - Close an IO request
 * @req: io request SM.
 *
 * needs to be called with lock held.
 */
अटल अंतरभूत पूर्णांक
csio_scsi_बंद(काष्ठा csio_ioreq *ioreq)
अणु
	csio_post_event(&ioreq->sm, CSIO_SCSIE_CLOSE);
	वापस ioreq->drv_status;
पूर्ण

व्योम csio_scsi_cleanup_io_q(काष्ठा csio_scsim *, काष्ठा list_head *);
पूर्णांक csio_scsim_cleanup_io(काष्ठा csio_scsim *, bool पात);
पूर्णांक csio_scsim_cleanup_io_lnode(काष्ठा csio_scsim *,
					  काष्ठा csio_lnode *);
काष्ठा csio_ioreq *csio_scsi_cmpl_handler(काष्ठा csio_hw *, व्योम *, uपूर्णांक32_t,
					  काष्ठा csio_fl_dma_buf *,
					  व्योम *, uपूर्णांक8_t **);
पूर्णांक csio_scsi_qconfig(काष्ठा csio_hw *);
पूर्णांक csio_scsim_init(काष्ठा csio_scsim *, काष्ठा csio_hw *);
व्योम csio_scsim_निकास(काष्ठा csio_scsim *);

#पूर्ण_अगर /* __CSIO_SCSI_H__ */
