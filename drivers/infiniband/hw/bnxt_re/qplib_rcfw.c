<शैली गुरु>
/*
 * Broadcom NetXtreme-E RoCE driver.
 *
 * Copyright (c) 2016 - 2017, Broadcom. All rights reserved.  The term
 * Broadcom refers to Broadcom Limited and/or its subsidiaries.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * BSD license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS
 * BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Description: RDMA Controller HW पूर्णांकerface
 */

#घोषणा dev_fmt(fmt) "QPLIB: " fmt

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/pci.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/delay.h>

#समावेश "roce_hsi.h"
#समावेश "qplib_res.h"
#समावेश "qplib_rcfw.h"
#समावेश "qplib_sp.h"
#समावेश "qplib_fp.h"

अटल व्योम bnxt_qplib_service_creq(काष्ठा tasklet_काष्ठा *t);

/* Hardware communication channel */
अटल पूर्णांक __रुको_क्रम_resp(काष्ठा bnxt_qplib_rcfw *rcfw, u16 cookie)
अणु
	काष्ठा bnxt_qplib_cmdq_ctx *cmdq;
	u16 cbit;
	पूर्णांक rc;

	cmdq = &rcfw->cmdq;
	cbit = cookie % rcfw->cmdq_depth;
	rc = रुको_event_समयout(cmdq->रुकोq,
				!test_bit(cbit, cmdq->cmdq_biपंचांगap),
				msecs_to_jअगरfies(RCFW_CMD_WAIT_TIME_MS));
	वापस rc ? 0 : -ETIMEDOUT;
पूर्ण;

अटल पूर्णांक __block_क्रम_resp(काष्ठा bnxt_qplib_rcfw *rcfw, u16 cookie)
अणु
	u32 count = RCFW_BLOCKED_CMD_WAIT_COUNT;
	काष्ठा bnxt_qplib_cmdq_ctx *cmdq;
	u16 cbit;

	cmdq = &rcfw->cmdq;
	cbit = cookie % rcfw->cmdq_depth;
	अगर (!test_bit(cbit, cmdq->cmdq_biपंचांगap))
		जाओ करोne;
	करो अणु
		mdelay(1); /* 1m sec */
		bnxt_qplib_service_creq(&rcfw->creq.creq_tasklet);
	पूर्ण जबतक (test_bit(cbit, cmdq->cmdq_biपंचांगap) && --count);
करोne:
	वापस count ? 0 : -ETIMEDOUT;
पूर्ण;

अटल पूर्णांक __send_message(काष्ठा bnxt_qplib_rcfw *rcfw, काष्ठा cmdq_base *req,
			  काष्ठा creq_base *resp, व्योम *sb, u8 is_block)
अणु
	काष्ठा bnxt_qplib_cmdq_ctx *cmdq = &rcfw->cmdq;
	काष्ठा bnxt_qplib_hwq *hwq = &cmdq->hwq;
	काष्ठा bnxt_qplib_crsqe *crsqe;
	काष्ठा bnxt_qplib_cmdqe *cmdqe;
	u32 sw_prod, cmdq_prod;
	काष्ठा pci_dev *pdev;
	अचिन्हित दीर्घ flags;
	u32 size, opcode;
	u16 cookie, cbit;
	u8 *preq;

	pdev = rcfw->pdev;

	opcode = req->opcode;
	अगर (!test_bit(FIRMWARE_INITIALIZED_FLAG, &cmdq->flags) &&
	    (opcode != CMDQ_BASE_OPCODE_QUERY_FUNC &&
	     opcode != CMDQ_BASE_OPCODE_INITIALIZE_FW &&
	     opcode != CMDQ_BASE_OPCODE_QUERY_VERSION)) अणु
		dev_err(&pdev->dev,
			"RCFW not initialized, reject opcode 0x%x\n", opcode);
		वापस -EINVAL;
	पूर्ण

	अगर (test_bit(FIRMWARE_INITIALIZED_FLAG, &cmdq->flags) &&
	    opcode == CMDQ_BASE_OPCODE_INITIALIZE_FW) अणु
		dev_err(&pdev->dev, "RCFW already initialized!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (test_bit(FIRMWARE_TIMED_OUT, &cmdq->flags))
		वापस -ETIMEDOUT;

	/* Cmdq are in 16-byte units, each request can consume 1 or more
	 * cmdqe
	 */
	spin_lock_irqsave(&hwq->lock, flags);
	अगर (req->cmd_size >= HWQ_FREE_SLOTS(hwq)) अणु
		dev_err(&pdev->dev, "RCFW: CMDQ is full!\n");
		spin_unlock_irqrestore(&hwq->lock, flags);
		वापस -EAGAIN;
	पूर्ण


	cookie = cmdq->seq_num & RCFW_MAX_COOKIE_VALUE;
	cbit = cookie % rcfw->cmdq_depth;
	अगर (is_block)
		cookie |= RCFW_CMD_IS_BLOCKING;

	set_bit(cbit, cmdq->cmdq_biपंचांगap);
	req->cookie = cpu_to_le16(cookie);
	crsqe = &rcfw->crsqe_tbl[cbit];
	अगर (crsqe->resp) अणु
		spin_unlock_irqrestore(&hwq->lock, flags);
		वापस -EBUSY;
	पूर्ण

	size = req->cmd_size;
	/* change the cmd_size to the number of 16byte cmdq unit.
	 * req->cmd_size is modअगरied here
	 */
	bnxt_qplib_set_cmd_slots(req);

	स_रखो(resp, 0, माप(*resp));
	crsqe->resp = (काष्ठा creq_qp_event *)resp;
	crsqe->resp->cookie = req->cookie;
	crsqe->req_size = req->cmd_size;
	अगर (req->resp_size && sb) अणु
		काष्ठा bnxt_qplib_rcfw_sbuf *sbuf = sb;

		req->resp_addr = cpu_to_le64(sbuf->dma_addr);
		req->resp_size = (sbuf->size + BNXT_QPLIB_CMDQE_UNITS - 1) /
				  BNXT_QPLIB_CMDQE_UNITS;
	पूर्ण

	preq = (u8 *)req;
	करो अणु
		/* Locate the next cmdq slot */
		sw_prod = HWQ_CMP(hwq->prod, hwq);
		cmdqe = bnxt_qplib_get_qe(hwq, sw_prod, शून्य);
		अगर (!cmdqe) अणु
			dev_err(&pdev->dev,
				"RCFW request failed with no cmdqe!\n");
			जाओ करोne;
		पूर्ण
		/* Copy a segment of the req cmd to the cmdq */
		स_रखो(cmdqe, 0, माप(*cmdqe));
		स_नकल(cmdqe, preq, min_t(u32, size, माप(*cmdqe)));
		preq += min_t(u32, size, माप(*cmdqe));
		size -= min_t(u32, size, माप(*cmdqe));
		hwq->prod++;
	पूर्ण जबतक (size > 0);
	cmdq->seq_num++;

	cmdq_prod = hwq->prod;
	अगर (test_bit(FIRMWARE_FIRST_FLAG, &cmdq->flags)) अणु
		/* The very first करोorbell ग_लिखो
		 * is required to set this flag
		 * which prompts the FW to reset
		 * its पूर्णांकernal poपूर्णांकers
		 */
		cmdq_prod |= BIT(FIRMWARE_FIRST_FLAG);
		clear_bit(FIRMWARE_FIRST_FLAG, &cmdq->flags);
	पूर्ण

	/* ring CMDQ DB */
	wmb();
	ग_लिखोl(cmdq_prod, cmdq->cmdq_mbox.prod);
	ग_लिखोl(RCFW_CMDQ_TRIG_VAL, cmdq->cmdq_mbox.db);
करोne:
	spin_unlock_irqrestore(&hwq->lock, flags);
	/* Return the CREQ response poपूर्णांकer */
	वापस 0;
पूर्ण

पूर्णांक bnxt_qplib_rcfw_send_message(काष्ठा bnxt_qplib_rcfw *rcfw,
				 काष्ठा cmdq_base *req,
				 काष्ठा creq_base *resp,
				 व्योम *sb, u8 is_block)
अणु
	काष्ठा creq_qp_event *evnt = (काष्ठा creq_qp_event *)resp;
	u16 cookie;
	u8 opcode, retry_cnt = 0xFF;
	पूर्णांक rc = 0;

	/* Prevent posting अगर f/w is not in a state to process */
	अगर (test_bit(ERR_DEVICE_DETACHED, &rcfw->cmdq.flags))
		वापस 0;

	करो अणु
		opcode = req->opcode;
		rc = __send_message(rcfw, req, resp, sb, is_block);
		cookie = le16_to_cpu(req->cookie) & RCFW_MAX_COOKIE_VALUE;
		अगर (!rc)
			अवरोध;

		अगर (!retry_cnt || (rc != -EAGAIN && rc != -EBUSY)) अणु
			/* send failed */
			dev_err(&rcfw->pdev->dev, "cmdq[%#x]=%#x send failed\n",
				cookie, opcode);
			वापस rc;
		पूर्ण
		is_block ? mdelay(1) : usleep_range(500, 1000);

	पूर्ण जबतक (retry_cnt--);

	अगर (is_block)
		rc = __block_क्रम_resp(rcfw, cookie);
	अन्यथा
		rc = __रुको_क्रम_resp(rcfw, cookie);
	अगर (rc) अणु
		/* समयd out */
		dev_err(&rcfw->pdev->dev, "cmdq[%#x]=%#x timedout (%d)msec\n",
			cookie, opcode, RCFW_CMD_WAIT_TIME_MS);
		set_bit(FIRMWARE_TIMED_OUT, &rcfw->cmdq.flags);
		वापस rc;
	पूर्ण

	अगर (evnt->status) अणु
		/* failed with status */
		dev_err(&rcfw->pdev->dev, "cmdq[%#x]=%#x status %#x\n",
			cookie, opcode, evnt->status);
		rc = -EFAULT;
	पूर्ण

	वापस rc;
पूर्ण
/* Completions */
अटल पूर्णांक bnxt_qplib_process_func_event(काष्ठा bnxt_qplib_rcfw *rcfw,
					 काष्ठा creq_func_event *func_event)
अणु
	पूर्णांक rc;

	चयन (func_event->event) अणु
	हाल CREQ_FUNC_EVENT_EVENT_TX_WQE_ERROR:
		अवरोध;
	हाल CREQ_FUNC_EVENT_EVENT_TX_DATA_ERROR:
		अवरोध;
	हाल CREQ_FUNC_EVENT_EVENT_RX_WQE_ERROR:
		अवरोध;
	हाल CREQ_FUNC_EVENT_EVENT_RX_DATA_ERROR:
		अवरोध;
	हाल CREQ_FUNC_EVENT_EVENT_CQ_ERROR:
		अवरोध;
	हाल CREQ_FUNC_EVENT_EVENT_TQM_ERROR:
		अवरोध;
	हाल CREQ_FUNC_EVENT_EVENT_CFCQ_ERROR:
		अवरोध;
	हाल CREQ_FUNC_EVENT_EVENT_CFCS_ERROR:
		/* SRQ ctx error, call srq_handler??
		 * But there's no SRQ handle!
		 */
		अवरोध;
	हाल CREQ_FUNC_EVENT_EVENT_CFCC_ERROR:
		अवरोध;
	हाल CREQ_FUNC_EVENT_EVENT_CFCM_ERROR:
		अवरोध;
	हाल CREQ_FUNC_EVENT_EVENT_TIM_ERROR:
		अवरोध;
	हाल CREQ_FUNC_EVENT_EVENT_VF_COMM_REQUEST:
		अवरोध;
	हाल CREQ_FUNC_EVENT_EVENT_RESOURCE_EXHAUSTED:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	rc = rcfw->creq.aeq_handler(rcfw, (व्योम *)func_event, शून्य);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_qplib_process_qp_event(काष्ठा bnxt_qplib_rcfw *rcfw,
				       काष्ठा creq_qp_event *qp_event)
अणु
	काष्ठा creq_qp_error_notअगरication *err_event;
	काष्ठा bnxt_qplib_hwq *hwq = &rcfw->cmdq.hwq;
	काष्ठा bnxt_qplib_crsqe *crsqe;
	काष्ठा bnxt_qplib_qp *qp;
	u16 cbit, blocked = 0;
	काष्ठा pci_dev *pdev;
	अचिन्हित दीर्घ flags;
	__le16  mcookie;
	u16 cookie;
	पूर्णांक rc = 0;
	u32 qp_id, tbl_indx;

	pdev = rcfw->pdev;
	चयन (qp_event->event) अणु
	हाल CREQ_QP_EVENT_EVENT_QP_ERROR_NOTIFICATION:
		err_event = (काष्ठा creq_qp_error_notअगरication *)qp_event;
		qp_id = le32_to_cpu(err_event->xid);
		tbl_indx = map_qp_id_to_tbl_indx(qp_id, rcfw);
		qp = rcfw->qp_tbl[tbl_indx].qp_handle;
		dev_dbg(&pdev->dev, "Received QP error notification\n");
		dev_dbg(&pdev->dev,
			"qpid 0x%x, req_err=0x%x, resp_err=0x%x\n",
			qp_id, err_event->req_err_state_reason,
			err_event->res_err_state_reason);
		अगर (!qp)
			अवरोध;
		bnxt_qplib_mark_qp_error(qp);
		rc = rcfw->creq.aeq_handler(rcfw, qp_event, qp);
		अवरोध;
	शेष:
		/*
		 * Command Response
		 * cmdq->lock needs to be acquired to synchronie
		 * the command send and completion reaping. This function
		 * is always called with creq->lock held. Using
		 * the nested variant of spin_lock.
		 *
		 */

		spin_lock_irqsave_nested(&hwq->lock, flags,
					 SINGLE_DEPTH_NESTING);
		cookie = le16_to_cpu(qp_event->cookie);
		mcookie = qp_event->cookie;
		blocked = cookie & RCFW_CMD_IS_BLOCKING;
		cookie &= RCFW_MAX_COOKIE_VALUE;
		cbit = cookie % rcfw->cmdq_depth;
		crsqe = &rcfw->crsqe_tbl[cbit];
		अगर (crsqe->resp &&
		    crsqe->resp->cookie  == mcookie) अणु
			स_नकल(crsqe->resp, qp_event, माप(*qp_event));
			crsqe->resp = शून्य;
		पूर्ण अन्यथा अणु
			अगर (crsqe->resp && crsqe->resp->cookie)
				dev_err(&pdev->dev,
					"CMD %s cookie sent=%#x, recd=%#x\n",
					crsqe->resp ? "mismatch" : "collision",
					crsqe->resp ? crsqe->resp->cookie : 0,
					mcookie);
		पूर्ण
		अगर (!test_and_clear_bit(cbit, rcfw->cmdq.cmdq_biपंचांगap))
			dev_warn(&pdev->dev,
				 "CMD bit %d was not requested\n", cbit);
		hwq->cons += crsqe->req_size;
		crsqe->req_size = 0;

		अगर (!blocked)
			wake_up(&rcfw->cmdq.रुकोq);
		spin_unlock_irqrestore(&hwq->lock, flags);
	पूर्ण
	वापस rc;
पूर्ण

/* SP - CREQ Completion handlers */
अटल व्योम bnxt_qplib_service_creq(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा bnxt_qplib_rcfw *rcfw = from_tasklet(rcfw, t, creq.creq_tasklet);
	काष्ठा bnxt_qplib_creq_ctx *creq = &rcfw->creq;
	u32 type, budget = CREQ_ENTRY_POLL_BUDGET;
	काष्ठा bnxt_qplib_hwq *hwq = &creq->hwq;
	काष्ठा creq_base *creqe;
	u32 sw_cons, raw_cons;
	अचिन्हित दीर्घ flags;

	/* Service the CREQ until budget is over */
	spin_lock_irqsave(&hwq->lock, flags);
	raw_cons = hwq->cons;
	जबतक (budget > 0) अणु
		sw_cons = HWQ_CMP(raw_cons, hwq);
		creqe = bnxt_qplib_get_qe(hwq, sw_cons, शून्य);
		अगर (!CREQ_CMP_VALID(creqe, raw_cons, hwq->max_elements))
			अवरोध;
		/* The valid test of the entry must be करोne first beक्रमe
		 * पढ़ोing any further.
		 */
		dma_rmb();

		type = creqe->type & CREQ_BASE_TYPE_MASK;
		चयन (type) अणु
		हाल CREQ_BASE_TYPE_QP_EVENT:
			bnxt_qplib_process_qp_event
				(rcfw, (काष्ठा creq_qp_event *)creqe);
			creq->stats.creq_qp_event_processed++;
			अवरोध;
		हाल CREQ_BASE_TYPE_FUNC_EVENT:
			अगर (!bnxt_qplib_process_func_event
			    (rcfw, (काष्ठा creq_func_event *)creqe))
				creq->stats.creq_func_event_processed++;
			अन्यथा
				dev_warn(&rcfw->pdev->dev,
					 "aeqe:%#x Not handled\n", type);
			अवरोध;
		शेष:
			अगर (type != ASYNC_EVENT_CMPL_TYPE_HWRM_ASYNC_EVENT)
				dev_warn(&rcfw->pdev->dev,
					 "creqe with event 0x%x not handled\n",
					 type);
			अवरोध;
		पूर्ण
		raw_cons++;
		budget--;
	पूर्ण

	अगर (hwq->cons != raw_cons) अणु
		hwq->cons = raw_cons;
		bnxt_qplib_ring_nq_db(&creq->creq_db.dbinfo,
				      rcfw->res->cctx, true);
	पूर्ण
	spin_unlock_irqrestore(&hwq->lock, flags);
पूर्ण

अटल irqवापस_t bnxt_qplib_creq_irq(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा bnxt_qplib_rcfw *rcfw = dev_instance;
	काष्ठा bnxt_qplib_creq_ctx *creq;
	काष्ठा bnxt_qplib_hwq *hwq;
	u32 sw_cons;

	creq = &rcfw->creq;
	hwq = &creq->hwq;
	/* Prefetch the CREQ element */
	sw_cons = HWQ_CMP(hwq->cons, hwq);
	prefetch(bnxt_qplib_get_qe(hwq, sw_cons, शून्य));

	tasklet_schedule(&creq->creq_tasklet);

	वापस IRQ_HANDLED;
पूर्ण

/* RCFW */
पूर्णांक bnxt_qplib_deinit_rcfw(काष्ठा bnxt_qplib_rcfw *rcfw)
अणु
	काष्ठा cmdq_deinitialize_fw req;
	काष्ठा creq_deinitialize_fw_resp resp;
	u16 cmd_flags = 0;
	पूर्णांक rc;

	RCFW_CMD_PREP(req, DEINITIALIZE_FW, cmd_flags);
	rc = bnxt_qplib_rcfw_send_message(rcfw, (व्योम *)&req, (व्योम *)&resp,
					  शून्य, 0);
	अगर (rc)
		वापस rc;

	clear_bit(FIRMWARE_INITIALIZED_FLAG, &rcfw->cmdq.flags);
	वापस 0;
पूर्ण

पूर्णांक bnxt_qplib_init_rcfw(काष्ठा bnxt_qplib_rcfw *rcfw,
			 काष्ठा bnxt_qplib_ctx *ctx, पूर्णांक is_virtfn)
अणु
	काष्ठा creq_initialize_fw_resp resp;
	काष्ठा cmdq_initialize_fw req;
	u16 cmd_flags = 0;
	u8 pgsz, lvl;
	पूर्णांक rc;

	RCFW_CMD_PREP(req, INITIALIZE_FW, cmd_flags);
	/* Supply (log-base-2-of-host-page-size - base-page-shअगरt)
	 * to bono to adjust the करोorbell page sizes.
	 */
	req.log2_dbr_pg_size = cpu_to_le16(PAGE_SHIFT -
					   RCFW_DBR_BASE_PAGE_SHIFT);
	/*
	 * Gen P5 devices करोesn't require this allocation
	 * as the L2 driver करोes the same क्रम RoCE also.
	 * Also, VFs need not setup the HW context area, PF
	 * shall setup this area क्रम VF. Skipping the
	 * HW programming
	 */
	अगर (is_virtfn)
		जाओ skip_ctx_setup;
	अगर (bnxt_qplib_is_chip_gen_p5(rcfw->res->cctx))
		जाओ config_vf_res;

	lvl = ctx->qpc_tbl.level;
	pgsz = bnxt_qplib_base_pg_size(&ctx->qpc_tbl);
	req.qpc_pg_size_qpc_lvl = (pgsz << CMDQ_INITIALIZE_FW_QPC_PG_SIZE_SFT) |
				   lvl;
	lvl = ctx->mrw_tbl.level;
	pgsz = bnxt_qplib_base_pg_size(&ctx->mrw_tbl);
	req.mrw_pg_size_mrw_lvl = (pgsz << CMDQ_INITIALIZE_FW_QPC_PG_SIZE_SFT) |
				   lvl;
	lvl = ctx->srqc_tbl.level;
	pgsz = bnxt_qplib_base_pg_size(&ctx->srqc_tbl);
	req.srq_pg_size_srq_lvl = (pgsz << CMDQ_INITIALIZE_FW_QPC_PG_SIZE_SFT) |
				   lvl;
	lvl = ctx->cq_tbl.level;
	pgsz = bnxt_qplib_base_pg_size(&ctx->cq_tbl);
	req.cq_pg_size_cq_lvl = (pgsz << CMDQ_INITIALIZE_FW_QPC_PG_SIZE_SFT) |
				 lvl;
	lvl = ctx->tim_tbl.level;
	pgsz = bnxt_qplib_base_pg_size(&ctx->tim_tbl);
	req.tim_pg_माप_प्रकारim_lvl = (pgsz << CMDQ_INITIALIZE_FW_QPC_PG_SIZE_SFT) |
				   lvl;
	lvl = ctx->tqm_ctx.pde.level;
	pgsz = bnxt_qplib_base_pg_size(&ctx->tqm_ctx.pde);
	req.tqm_pg_माप_प्रकारqm_lvl = (pgsz << CMDQ_INITIALIZE_FW_QPC_PG_SIZE_SFT) |
				   lvl;
	req.qpc_page_dir =
		cpu_to_le64(ctx->qpc_tbl.pbl[PBL_LVL_0].pg_map_arr[0]);
	req.mrw_page_dir =
		cpu_to_le64(ctx->mrw_tbl.pbl[PBL_LVL_0].pg_map_arr[0]);
	req.srq_page_dir =
		cpu_to_le64(ctx->srqc_tbl.pbl[PBL_LVL_0].pg_map_arr[0]);
	req.cq_page_dir =
		cpu_to_le64(ctx->cq_tbl.pbl[PBL_LVL_0].pg_map_arr[0]);
	req.tim_page_dir =
		cpu_to_le64(ctx->tim_tbl.pbl[PBL_LVL_0].pg_map_arr[0]);
	req.tqm_page_dir =
		cpu_to_le64(ctx->tqm_ctx.pde.pbl[PBL_LVL_0].pg_map_arr[0]);

	req.number_of_qp = cpu_to_le32(ctx->qpc_tbl.max_elements);
	req.number_of_mrw = cpu_to_le32(ctx->mrw_tbl.max_elements);
	req.number_of_srq = cpu_to_le32(ctx->srqc_tbl.max_elements);
	req.number_of_cq = cpu_to_le32(ctx->cq_tbl.max_elements);

config_vf_res:
	req.max_qp_per_vf = cpu_to_le32(ctx->vf_res.max_qp_per_vf);
	req.max_mrw_per_vf = cpu_to_le32(ctx->vf_res.max_mrw_per_vf);
	req.max_srq_per_vf = cpu_to_le32(ctx->vf_res.max_srq_per_vf);
	req.max_cq_per_vf = cpu_to_le32(ctx->vf_res.max_cq_per_vf);
	req.max_gid_per_vf = cpu_to_le32(ctx->vf_res.max_gid_per_vf);

skip_ctx_setup:
	req.stat_ctx_id = cpu_to_le32(ctx->stats.fw_id);
	rc = bnxt_qplib_rcfw_send_message(rcfw, (व्योम *)&req, (व्योम *)&resp,
					  शून्य, 0);
	अगर (rc)
		वापस rc;
	set_bit(FIRMWARE_INITIALIZED_FLAG, &rcfw->cmdq.flags);
	वापस 0;
पूर्ण

व्योम bnxt_qplib_मुक्त_rcfw_channel(काष्ठा bnxt_qplib_rcfw *rcfw)
अणु
	kमुक्त(rcfw->cmdq.cmdq_biपंचांगap);
	kमुक्त(rcfw->qp_tbl);
	kमुक्त(rcfw->crsqe_tbl);
	bnxt_qplib_मुक्त_hwq(rcfw->res, &rcfw->cmdq.hwq);
	bnxt_qplib_मुक्त_hwq(rcfw->res, &rcfw->creq.hwq);
	rcfw->pdev = शून्य;
पूर्ण

पूर्णांक bnxt_qplib_alloc_rcfw_channel(काष्ठा bnxt_qplib_res *res,
				  काष्ठा bnxt_qplib_rcfw *rcfw,
				  काष्ठा bnxt_qplib_ctx *ctx,
				  पूर्णांक qp_tbl_sz)
अणु
	काष्ठा bnxt_qplib_hwq_attr hwq_attr = अणुपूर्ण;
	काष्ठा bnxt_qplib_sg_info sginfo = अणुपूर्ण;
	काष्ठा bnxt_qplib_cmdq_ctx *cmdq;
	काष्ठा bnxt_qplib_creq_ctx *creq;
	u32 bmap_size = 0;

	rcfw->pdev = res->pdev;
	cmdq = &rcfw->cmdq;
	creq = &rcfw->creq;
	rcfw->res = res;

	sginfo.pgsize = PAGE_SIZE;
	sginfo.pgshft = PAGE_SHIFT;

	hwq_attr.sginfo = &sginfo;
	hwq_attr.res = rcfw->res;
	hwq_attr.depth = BNXT_QPLIB_CREQE_MAX_CNT;
	hwq_attr.stride = BNXT_QPLIB_CREQE_UNITS;
	hwq_attr.type = bnxt_qplib_get_hwq_type(res);

	अगर (bnxt_qplib_alloc_init_hwq(&creq->hwq, &hwq_attr)) अणु
		dev_err(&rcfw->pdev->dev,
			"HW channel CREQ allocation failed\n");
		जाओ fail;
	पूर्ण
	अगर (ctx->hwrm_पूर्णांकf_ver < HWRM_VERSION_RCFW_CMDQ_DEPTH_CHECK)
		rcfw->cmdq_depth = BNXT_QPLIB_CMDQE_MAX_CNT_256;
	अन्यथा
		rcfw->cmdq_depth = BNXT_QPLIB_CMDQE_MAX_CNT_8192;

	sginfo.pgsize = bnxt_qplib_cmdqe_page_size(rcfw->cmdq_depth);
	hwq_attr.depth = rcfw->cmdq_depth;
	hwq_attr.stride = BNXT_QPLIB_CMDQE_UNITS;
	hwq_attr.type = HWQ_TYPE_CTX;
	अगर (bnxt_qplib_alloc_init_hwq(&cmdq->hwq, &hwq_attr)) अणु
		dev_err(&rcfw->pdev->dev,
			"HW channel CMDQ allocation failed\n");
		जाओ fail;
	पूर्ण

	rcfw->crsqe_tbl = kसुस्मृति(cmdq->hwq.max_elements,
				  माप(*rcfw->crsqe_tbl), GFP_KERNEL);
	अगर (!rcfw->crsqe_tbl)
		जाओ fail;

	bmap_size = BITS_TO_LONGS(rcfw->cmdq_depth) * माप(अचिन्हित दीर्घ);
	cmdq->cmdq_biपंचांगap = kzalloc(bmap_size, GFP_KERNEL);
	अगर (!cmdq->cmdq_biपंचांगap)
		जाओ fail;

	cmdq->bmap_size = bmap_size;

	/* Allocate one extra to hold the QP1 entries */
	rcfw->qp_tbl_size = qp_tbl_sz + 1;
	rcfw->qp_tbl = kसुस्मृति(rcfw->qp_tbl_size, माप(काष्ठा bnxt_qplib_qp_node),
			       GFP_KERNEL);
	अगर (!rcfw->qp_tbl)
		जाओ fail;

	वापस 0;

fail:
	bnxt_qplib_मुक्त_rcfw_channel(rcfw);
	वापस -ENOMEM;
पूर्ण

व्योम bnxt_qplib_rcfw_stop_irq(काष्ठा bnxt_qplib_rcfw *rcfw, bool समाप्त)
अणु
	काष्ठा bnxt_qplib_creq_ctx *creq;

	creq = &rcfw->creq;
	tasklet_disable(&creq->creq_tasklet);
	/* Mask h/w पूर्णांकerrupts */
	bnxt_qplib_ring_nq_db(&creq->creq_db.dbinfo, rcfw->res->cctx, false);
	/* Sync with last running IRQ-handler */
	synchronize_irq(creq->msix_vec);
	अगर (समाप्त)
		tasklet_समाप्त(&creq->creq_tasklet);

	अगर (creq->requested) अणु
		मुक्त_irq(creq->msix_vec, rcfw);
		creq->requested = false;
	पूर्ण
पूर्ण

व्योम bnxt_qplib_disable_rcfw_channel(काष्ठा bnxt_qplib_rcfw *rcfw)
अणु
	काष्ठा bnxt_qplib_creq_ctx *creq;
	काष्ठा bnxt_qplib_cmdq_ctx *cmdq;
	अचिन्हित दीर्घ indx;

	creq = &rcfw->creq;
	cmdq = &rcfw->cmdq;
	/* Make sure the HW channel is stopped! */
	bnxt_qplib_rcfw_stop_irq(rcfw, true);

	iounmap(cmdq->cmdq_mbox.reg.bar_reg);
	iounmap(creq->creq_db.reg.bar_reg);

	indx = find_first_bit(cmdq->cmdq_biपंचांगap, cmdq->bmap_size);
	अगर (indx != cmdq->bmap_size)
		dev_err(&rcfw->pdev->dev,
			"disabling RCFW with pending cmd-bit %lx\n", indx);

	cmdq->cmdq_mbox.reg.bar_reg = शून्य;
	creq->creq_db.reg.bar_reg = शून्य;
	creq->aeq_handler = शून्य;
	creq->msix_vec = 0;
पूर्ण

पूर्णांक bnxt_qplib_rcfw_start_irq(काष्ठा bnxt_qplib_rcfw *rcfw, पूर्णांक msix_vector,
			      bool need_init)
अणु
	काष्ठा bnxt_qplib_creq_ctx *creq;
	पूर्णांक rc;

	creq = &rcfw->creq;

	अगर (creq->requested)
		वापस -EFAULT;

	creq->msix_vec = msix_vector;
	अगर (need_init)
		tasklet_setup(&creq->creq_tasklet, bnxt_qplib_service_creq);
	अन्यथा
		tasklet_enable(&creq->creq_tasklet);
	rc = request_irq(creq->msix_vec, bnxt_qplib_creq_irq, 0,
			 "bnxt_qplib_creq", rcfw);
	अगर (rc)
		वापस rc;
	creq->requested = true;

	bnxt_qplib_ring_nq_db(&creq->creq_db.dbinfo, rcfw->res->cctx, true);

	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_qplib_map_cmdq_mbox(काष्ठा bnxt_qplib_rcfw *rcfw, bool is_vf)
अणु
	काष्ठा bnxt_qplib_cmdq_mbox *mbox;
	resource_माप_प्रकार bar_reg;
	काष्ठा pci_dev *pdev;
	u16 prod_offt;
	पूर्णांक rc = 0;

	pdev = rcfw->pdev;
	mbox = &rcfw->cmdq.cmdq_mbox;

	mbox->reg.bar_id = RCFW_COMM_PCI_BAR_REGION;
	mbox->reg.len = RCFW_COMM_SIZE;
	mbox->reg.bar_base = pci_resource_start(pdev, mbox->reg.bar_id);
	अगर (!mbox->reg.bar_base) अणु
		dev_err(&pdev->dev,
			"QPLIB: CMDQ BAR region %d resc start is 0!\n",
			mbox->reg.bar_id);
		वापस -ENOMEM;
	पूर्ण

	bar_reg = mbox->reg.bar_base + RCFW_COMM_BASE_OFFSET;
	mbox->reg.len = RCFW_COMM_SIZE;
	mbox->reg.bar_reg = ioremap(bar_reg, mbox->reg.len);
	अगर (!mbox->reg.bar_reg) अणु
		dev_err(&pdev->dev,
			"QPLIB: CMDQ BAR region %d mapping failed\n",
			mbox->reg.bar_id);
		वापस -ENOMEM;
	पूर्ण

	prod_offt = is_vf ? RCFW_VF_COMM_PROD_OFFSET :
			    RCFW_PF_COMM_PROD_OFFSET;
	mbox->prod = (व्योम  __iomem *)(mbox->reg.bar_reg + prod_offt);
	mbox->db = (व्योम __iomem *)(mbox->reg.bar_reg + RCFW_COMM_TRIG_OFFSET);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_qplib_map_creq_db(काष्ठा bnxt_qplib_rcfw *rcfw, u32 reg_offt)
अणु
	काष्ठा bnxt_qplib_creq_db *creq_db;
	resource_माप_प्रकार bar_reg;
	काष्ठा pci_dev *pdev;

	pdev = rcfw->pdev;
	creq_db = &rcfw->creq.creq_db;

	creq_db->reg.bar_id = RCFW_COMM_CONS_PCI_BAR_REGION;
	creq_db->reg.bar_base = pci_resource_start(pdev, creq_db->reg.bar_id);
	अगर (!creq_db->reg.bar_id)
		dev_err(&pdev->dev,
			"QPLIB: CREQ BAR region %d resc start is 0!",
			creq_db->reg.bar_id);

	bar_reg = creq_db->reg.bar_base + reg_offt;
	/* Unconditionally map 8 bytes to support 57500 series */
	creq_db->reg.len = 8;
	creq_db->reg.bar_reg = ioremap(bar_reg, creq_db->reg.len);
	अगर (!creq_db->reg.bar_reg) अणु
		dev_err(&pdev->dev,
			"QPLIB: CREQ BAR region %d mapping failed",
			creq_db->reg.bar_id);
		वापस -ENOMEM;
	पूर्ण
	creq_db->dbinfo.db = creq_db->reg.bar_reg;
	creq_db->dbinfo.hwq = &rcfw->creq.hwq;
	creq_db->dbinfo.xid = rcfw->creq.ring_id;
	वापस 0;
पूर्ण

अटल व्योम bnxt_qplib_start_rcfw(काष्ठा bnxt_qplib_rcfw *rcfw)
अणु
	काष्ठा bnxt_qplib_cmdq_ctx *cmdq;
	काष्ठा bnxt_qplib_creq_ctx *creq;
	काष्ठा bnxt_qplib_cmdq_mbox *mbox;
	काष्ठा cmdq_init init = अणु0पूर्ण;

	cmdq = &rcfw->cmdq;
	creq = &rcfw->creq;
	mbox = &cmdq->cmdq_mbox;

	init.cmdq_pbl = cpu_to_le64(cmdq->hwq.pbl[PBL_LVL_0].pg_map_arr[0]);
	init.cmdq_size_cmdq_lvl =
			cpu_to_le16(((rcfw->cmdq_depth <<
				      CMDQ_INIT_CMDQ_SIZE_SFT) &
				    CMDQ_INIT_CMDQ_SIZE_MASK) |
				    ((cmdq->hwq.level <<
				      CMDQ_INIT_CMDQ_LVL_SFT) &
				    CMDQ_INIT_CMDQ_LVL_MASK));
	init.creq_ring_id = cpu_to_le16(creq->ring_id);
	/* Write to the Bono mailbox रेजिस्टर */
	__ioग_लिखो32_copy(mbox->reg.bar_reg, &init, माप(init) / 4);
पूर्ण

पूर्णांक bnxt_qplib_enable_rcfw_channel(काष्ठा bnxt_qplib_rcfw *rcfw,
				   पूर्णांक msix_vector,
				   पूर्णांक cp_bar_reg_off, पूर्णांक virt_fn,
				   aeq_handler_t aeq_handler)
अणु
	काष्ठा bnxt_qplib_cmdq_ctx *cmdq;
	काष्ठा bnxt_qplib_creq_ctx *creq;
	पूर्णांक rc;

	cmdq = &rcfw->cmdq;
	creq = &rcfw->creq;

	/* Clear to शेषs */

	cmdq->seq_num = 0;
	set_bit(FIRMWARE_FIRST_FLAG, &cmdq->flags);
	init_रुकोqueue_head(&cmdq->रुकोq);

	creq->stats.creq_qp_event_processed = 0;
	creq->stats.creq_func_event_processed = 0;
	creq->aeq_handler = aeq_handler;

	rc = bnxt_qplib_map_cmdq_mbox(rcfw, virt_fn);
	अगर (rc)
		वापस rc;

	rc = bnxt_qplib_map_creq_db(rcfw, cp_bar_reg_off);
	अगर (rc)
		वापस rc;

	rc = bnxt_qplib_rcfw_start_irq(rcfw, msix_vector, true);
	अगर (rc) अणु
		dev_err(&rcfw->pdev->dev,
			"Failed to request IRQ for CREQ rc = 0x%x\n", rc);
		bnxt_qplib_disable_rcfw_channel(rcfw);
		वापस rc;
	पूर्ण

	bnxt_qplib_start_rcfw(rcfw);

	वापस 0;
पूर्ण

काष्ठा bnxt_qplib_rcfw_sbuf *bnxt_qplib_rcfw_alloc_sbuf(
		काष्ठा bnxt_qplib_rcfw *rcfw,
		u32 size)
अणु
	काष्ठा bnxt_qplib_rcfw_sbuf *sbuf;

	sbuf = kzalloc(माप(*sbuf), GFP_ATOMIC);
	अगर (!sbuf)
		वापस शून्य;

	sbuf->size = size;
	sbuf->sb = dma_alloc_coherent(&rcfw->pdev->dev, sbuf->size,
				      &sbuf->dma_addr, GFP_ATOMIC);
	अगर (!sbuf->sb)
		जाओ bail;

	वापस sbuf;
bail:
	kमुक्त(sbuf);
	वापस शून्य;
पूर्ण

व्योम bnxt_qplib_rcfw_मुक्त_sbuf(काष्ठा bnxt_qplib_rcfw *rcfw,
			       काष्ठा bnxt_qplib_rcfw_sbuf *sbuf)
अणु
	अगर (sbuf->sb)
		dma_मुक्त_coherent(&rcfw->pdev->dev, sbuf->size,
				  sbuf->sb, sbuf->dma_addr);
	kमुक्त(sbuf);
पूर्ण
