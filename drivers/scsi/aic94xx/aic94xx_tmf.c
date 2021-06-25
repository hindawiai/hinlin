<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Aic94xx Task Management Functions
 *
 * Copyright (C) 2005 Adaptec, Inc.  All rights reserved.
 * Copyright (C) 2005 Luben Tuikov <luben_tuikov@adaptec.com>
 */

#समावेश <linux/spinlock.h>
#समावेश <linux/gfp.h>
#समावेश "aic94xx.h"
#समावेश "aic94xx_sas.h"
#समावेश "aic94xx_hwi.h"

/* ---------- Internal enqueue ---------- */

अटल पूर्णांक asd_enqueue_पूर्णांकernal(काष्ठा asd_ascb *ascb,
		व्योम (*tasklet_complete)(काष्ठा asd_ascb *,
					 काष्ठा करोne_list_काष्ठा *),
				व्योम (*समयd_out)(काष्ठा समयr_list *t))
अणु
	पूर्णांक res;

	ascb->tasklet_complete = tasklet_complete;
	ascb->uldd_समयr = 1;

	ascb->समयr.function = समयd_out;
	ascb->समयr.expires = jअगरfies + AIC94XX_SCB_TIMEOUT;

	add_समयr(&ascb->समयr);

	res = asd_post_ascb_list(ascb->ha, ascb, 1);
	अगर (unlikely(res))
		del_समयr(&ascb->समयr);
	वापस res;
पूर्ण

/* ---------- CLEAR NEXUS ---------- */

काष्ठा tasklet_completion_status अणु
	पूर्णांक	dl_opcode;
	पूर्णांक	पंचांगf_state;
	u8	tag_valid:1;
	__be16	tag;
पूर्ण;

#घोषणा DECLARE_TCS(tcs) \
	काष्ठा tasklet_completion_status tcs = अणु \
		.dl_opcode = 0, \
		.पंचांगf_state = 0, \
		.tag_valid = 0, \
		.tag = 0, \
	पूर्ण


अटल व्योम asd_clear_nexus_tasklet_complete(काष्ठा asd_ascb *ascb,
					     काष्ठा करोne_list_काष्ठा *dl)
अणु
	काष्ठा tasklet_completion_status *tcs = ascb->uldd_task;
	ASD_DPRINTK("%s: here\n", __func__);
	अगर (!del_समयr(&ascb->समयr)) अणु
		ASD_DPRINTK("%s: couldn't delete timer\n", __func__);
		वापस;
	पूर्ण
	ASD_DPRINTK("%s: opcode: 0x%x\n", __func__, dl->opcode);
	tcs->dl_opcode = dl->opcode;
	complete(ascb->completion);
	asd_ascb_मुक्त(ascb);
पूर्ण

अटल व्योम asd_clear_nexus_समयकरोut(काष्ठा समयr_list *t)
अणु
	काष्ठा asd_ascb *ascb = from_समयr(ascb, t, समयr);
	काष्ठा tasklet_completion_status *tcs = ascb->uldd_task;

	ASD_DPRINTK("%s: here\n", __func__);
	tcs->dl_opcode = TMF_RESP_FUNC_FAILED;
	complete(ascb->completion);
पूर्ण

#घोषणा CLEAR_NEXUS_PRE         \
	काष्ठा asd_ascb *ascb; \
	काष्ठा scb *scb; \
	पूर्णांक res; \
	DECLARE_COMPLETION_ONSTACK(completion); \
	DECLARE_TCS(tcs); \
		\
	ASD_DPRINTK("%s: PRE\n", __func__); \
        res = 1;                \
	ascb = asd_ascb_alloc_list(asd_ha, &res, GFP_KERNEL); \
	अगर (!ascb)              \
		वापस -ENOMEM; \
                                \
	ascb->completion = &completion; \
	ascb->uldd_task = &tcs; \
	scb = ascb->scb;        \
	scb->header.opcode = CLEAR_NEXUS

#घोषणा CLEAR_NEXUS_POST        \
	ASD_DPRINTK("%s: POST\n", __func__); \
	res = asd_enqueue_पूर्णांकernal(ascb, asd_clear_nexus_tasklet_complete, \
				   asd_clear_nexus_समयकरोut);              \
	अगर (res)                \
		जाओ out_err;   \
	ASD_DPRINTK("%s: clear nexus posted, waiting...\n", __func__); \
	रुको_क्रम_completion(&completion); \
	res = tcs.dl_opcode; \
	अगर (res == TC_NO_ERROR) \
		res = TMF_RESP_FUNC_COMPLETE;   \
	वापस res; \
out_err:                        \
	asd_ascb_मुक्त(ascb);    \
	वापस res

पूर्णांक asd_clear_nexus_ha(काष्ठा sas_ha_काष्ठा *sas_ha)
अणु
	काष्ठा asd_ha_काष्ठा *asd_ha = sas_ha->lldd_ha;

	CLEAR_NEXUS_PRE;
	scb->clear_nexus.nexus = NEXUS_ADAPTER;
	CLEAR_NEXUS_POST;
पूर्ण

पूर्णांक asd_clear_nexus_port(काष्ठा asd_sas_port *port)
अणु
	काष्ठा asd_ha_काष्ठा *asd_ha = port->ha->lldd_ha;

	CLEAR_NEXUS_PRE;
	scb->clear_nexus.nexus = NEXUS_PORT;
	scb->clear_nexus.conn_mask = port->phy_mask;
	CLEAR_NEXUS_POST;
पूर्ण

क्रमागत clear_nexus_phase अणु
	NEXUS_PHASE_PRE,
	NEXUS_PHASE_POST,
	NEXUS_PHASE_RESUME,
पूर्ण;

अटल पूर्णांक asd_clear_nexus_I_T(काष्ठा करोमुख्य_device *dev,
			       क्रमागत clear_nexus_phase phase)
अणु
	काष्ठा asd_ha_काष्ठा *asd_ha = dev->port->ha->lldd_ha;

	CLEAR_NEXUS_PRE;
	scb->clear_nexus.nexus = NEXUS_I_T;
	चयन (phase) अणु
	हाल NEXUS_PHASE_PRE:
		scb->clear_nexus.flags = EXEC_Q | SUSPEND_TX;
		अवरोध;
	हाल NEXUS_PHASE_POST:
		scb->clear_nexus.flags = SEND_Q | NOTINQ;
		अवरोध;
	हाल NEXUS_PHASE_RESUME:
		scb->clear_nexus.flags = RESUME_TX;
	पूर्ण
	scb->clear_nexus.conn_handle = cpu_to_le16((u16)(अचिन्हित दीर्घ)
						   dev->lldd_dev);
	CLEAR_NEXUS_POST;
पूर्ण

पूर्णांक asd_I_T_nexus_reset(काष्ठा करोमुख्य_device *dev)
अणु
	पूर्णांक res, पंचांगp_res, i;
	काष्ठा sas_phy *phy = sas_get_local_phy(dev);
	/* Standard mandates link reset क्रम ATA  (type 0) and
	 * hard reset क्रम SSP (type 1) */
	पूर्णांक reset_type = (dev->dev_type == SAS_SATA_DEV ||
			  (dev->tproto & SAS_PROTOCOL_STP)) ? 0 : 1;

	asd_clear_nexus_I_T(dev, NEXUS_PHASE_PRE);
	/* send a hard reset */
	ASD_DPRINTK("sending %s reset to %s\n",
		    reset_type ? "hard" : "soft", dev_name(&phy->dev));
	res = sas_phy_reset(phy, reset_type);
	अगर (res == TMF_RESP_FUNC_COMPLETE || res == -ENODEV) अणु
		/* रुको क्रम the maximum settle समय */
		msleep(500);
		/* clear all outstanding commands (keep nexus suspended) */
		asd_clear_nexus_I_T(dev, NEXUS_PHASE_POST);
	पूर्ण
	क्रम (i = 0 ; i < 3; i++) अणु
		पंचांगp_res = asd_clear_nexus_I_T(dev, NEXUS_PHASE_RESUME);
		अगर (पंचांगp_res == TC_RESUME)
			जाओ out;
		msleep(500);
	पूर्ण

	/* This is a bit of a problem:  the sequencer is still suspended
	 * and is refusing to resume.  Hope it will resume on a bigger hammer
	 * or the disk is lost */
	dev_prपूर्णांकk(KERN_ERR, &phy->dev,
		   "Failed to resume nexus after reset 0x%x\n", पंचांगp_res);

	res = TMF_RESP_FUNC_FAILED;
 out:
	sas_put_local_phy(phy);
	वापस res;
पूर्ण

अटल पूर्णांक asd_clear_nexus_I_T_L(काष्ठा करोमुख्य_device *dev, u8 *lun)
अणु
	काष्ठा asd_ha_काष्ठा *asd_ha = dev->port->ha->lldd_ha;

	CLEAR_NEXUS_PRE;
	scb->clear_nexus.nexus = NEXUS_I_T_L;
	scb->clear_nexus.flags = SEND_Q | EXEC_Q | NOTINQ;
	स_नकल(scb->clear_nexus.ssp_task.lun, lun, 8);
	scb->clear_nexus.conn_handle = cpu_to_le16((u16)(अचिन्हित दीर्घ)
						   dev->lldd_dev);
	CLEAR_NEXUS_POST;
पूर्ण

अटल पूर्णांक asd_clear_nexus_tag(काष्ठा sas_task *task)
अणु
	काष्ठा asd_ha_काष्ठा *asd_ha = task->dev->port->ha->lldd_ha;
	काष्ठा asd_ascb *tascb = task->lldd_task;

	CLEAR_NEXUS_PRE;
	scb->clear_nexus.nexus = NEXUS_TAG;
	स_नकल(scb->clear_nexus.ssp_task.lun, task->ssp_task.LUN, 8);
	scb->clear_nexus.ssp_task.tag = tascb->tag;
	अगर (task->dev->tproto)
		scb->clear_nexus.conn_handle = cpu_to_le16((u16)(अचिन्हित दीर्घ)
							  task->dev->lldd_dev);
	CLEAR_NEXUS_POST;
पूर्ण

अटल पूर्णांक asd_clear_nexus_index(काष्ठा sas_task *task)
अणु
	काष्ठा asd_ha_काष्ठा *asd_ha = task->dev->port->ha->lldd_ha;
	काष्ठा asd_ascb *tascb = task->lldd_task;

	CLEAR_NEXUS_PRE;
	scb->clear_nexus.nexus = NEXUS_TRANS_CX;
	अगर (task->dev->tproto)
		scb->clear_nexus.conn_handle = cpu_to_le16((u16)(अचिन्हित दीर्घ)
							  task->dev->lldd_dev);
	scb->clear_nexus.index = cpu_to_le16(tascb->tc_index);
	CLEAR_NEXUS_POST;
पूर्ण

/* ---------- TMFs ---------- */

अटल व्योम asd_पंचांगf_समयकरोut(काष्ठा समयr_list *t)
अणु
	काष्ठा asd_ascb *ascb = from_समयr(ascb, t, समयr);
	काष्ठा tasklet_completion_status *tcs = ascb->uldd_task;

	ASD_DPRINTK("tmf timed out\n");
	tcs->पंचांगf_state = TMF_RESP_FUNC_FAILED;
	complete(ascb->completion);
पूर्ण

अटल पूर्णांक asd_get_पंचांगf_resp_tasklet(काष्ठा asd_ascb *ascb,
				    काष्ठा करोne_list_काष्ठा *dl)
अणु
	काष्ठा asd_ha_काष्ठा *asd_ha = ascb->ha;
	अचिन्हित दीर्घ flags;
	काष्ठा tc_resp_sb_काष्ठा अणु
		__le16 index_escb;
		u8     len_lsb;
		u8     flags;
	पूर्ण __attribute__ ((packed)) *resp_sb = (व्योम *) dl->status_block;

	पूर्णांक  edb_id = ((resp_sb->flags & 0x70) >> 4)-1;
	काष्ठा asd_ascb *escb;
	काष्ठा asd_dma_tok *edb;
	काष्ठा ssp_frame_hdr *fh;
	काष्ठा ssp_response_iu   *ru;
	पूर्णांक res = TMF_RESP_FUNC_FAILED;

	ASD_DPRINTK("tmf resp tasklet\n");

	spin_lock_irqsave(&asd_ha->seq.tc_index_lock, flags);
	escb = asd_tc_index_find(&asd_ha->seq,
				 (पूर्णांक)le16_to_cpu(resp_sb->index_escb));
	spin_unlock_irqrestore(&asd_ha->seq.tc_index_lock, flags);

	अगर (!escb) अणु
		ASD_DPRINTK("Uh-oh! No escb for this dl?!\n");
		वापस res;
	पूर्ण

	edb = asd_ha->seq.edb_arr[edb_id + escb->edb_index];
	ascb->tag = *(__be16 *)(edb->vaddr+4);
	fh = edb->vaddr + 16;
	ru = edb->vaddr + 16 + माप(*fh);
	res = ru->status;
	अगर (ru->datapres == 1)	  /* Response data present */
		res = ru->resp_data[3];
#अगर 0
	ascb->tag = fh->tag;
#पूर्ण_अगर
	ascb->tag_valid = 1;

	asd_invalidate_edb(escb, edb_id);
	वापस res;
पूर्ण

अटल व्योम asd_पंचांगf_tasklet_complete(काष्ठा asd_ascb *ascb,
				     काष्ठा करोne_list_काष्ठा *dl)
अणु
	काष्ठा tasklet_completion_status *tcs;

	अगर (!del_समयr(&ascb->समयr))
		वापस;

	tcs = ascb->uldd_task;
	ASD_DPRINTK("tmf tasklet complete\n");

	tcs->dl_opcode = dl->opcode;

	अगर (dl->opcode == TC_SSP_RESP) अणु
		tcs->पंचांगf_state = asd_get_पंचांगf_resp_tasklet(ascb, dl);
		tcs->tag_valid = ascb->tag_valid;
		tcs->tag = ascb->tag;
	पूर्ण

	complete(ascb->completion);
	asd_ascb_मुक्त(ascb);
पूर्ण

अटल पूर्णांक asd_clear_nexus(काष्ठा sas_task *task)
अणु
	पूर्णांक res = TMF_RESP_FUNC_FAILED;
	पूर्णांक leftover;
	काष्ठा asd_ascb *tascb = task->lldd_task;
	DECLARE_COMPLETION_ONSTACK(completion);
	अचिन्हित दीर्घ flags;

	tascb->completion = &completion;

	ASD_DPRINTK("task not done, clearing nexus\n");
	अगर (tascb->tag_valid)
		res = asd_clear_nexus_tag(task);
	अन्यथा
		res = asd_clear_nexus_index(task);
	leftover = रुको_क्रम_completion_समयout(&completion,
					       AIC94XX_SCB_TIMEOUT);
	tascb->completion = शून्य;
	ASD_DPRINTK("came back from clear nexus\n");
	spin_lock_irqsave(&task->task_state_lock, flags);
	अगर (leftover < 1)
		res = TMF_RESP_FUNC_FAILED;
	अगर (task->task_state_flags & SAS_TASK_STATE_DONE)
		res = TMF_RESP_FUNC_COMPLETE;
	spin_unlock_irqrestore(&task->task_state_lock, flags);

	वापस res;
पूर्ण

/**
 * asd_पात_task -- ABORT TASK TMF
 * @task: the task to be पातed
 *
 * Beक्रमe calling ABORT TASK the task state flags should be ORed with
 * SAS_TASK_STATE_ABORTED (unless SAS_TASK_STATE_DONE is set) under
 * the task_state_lock IRQ spinlock, then ABORT TASK *must* be called.
 *
 * Implements the ABORT TASK TMF, I_T_L_Q nexus.
 * Returns: SAS TMF responses (see sas_task.h),
 *          -ENOMEM,
 *          -SAS_QUEUE_FULL.
 *
 * When ABORT TASK वापसs, the caller of ABORT TASK checks first the
 * task->task_state_flags, and then the वापस value of ABORT TASK.
 *
 * If the task has task state bit SAS_TASK_STATE_DONE set, then the
 * task was completed successfully prior to it being पातed.  The
 * caller of ABORT TASK has responsibility to call task->task_करोne()
 * xor मुक्त the task, depending on their framework.  The वापस code
 * is TMF_RESP_FUNC_FAILED in this हाल.
 *
 * Else the SAS_TASK_STATE_DONE bit is not set,
 * 	If the वापस code is TMF_RESP_FUNC_COMPLETE, then
 * 		the task was पातed successfully.  The caller of
 * 		ABORT TASK has responsibility to call task->task_करोne()
 *              to finish the task, xor मुक्त the task depending on their
 *		framework.
 *	अन्यथा
 * 		the ABORT TASK वापसed some kind of error. The task
 *              was _not_ cancelled.  Nothing can be assumed.
 *		The caller of ABORT TASK may wish to retry.
 */
पूर्णांक asd_पात_task(काष्ठा sas_task *task)
अणु
	काष्ठा asd_ascb *tascb = task->lldd_task;
	काष्ठा asd_ha_काष्ठा *asd_ha = tascb->ha;
	पूर्णांक res = 1;
	अचिन्हित दीर्घ flags;
	काष्ठा asd_ascb *ascb = शून्य;
	काष्ठा scb *scb;
	पूर्णांक leftover;
	DECLARE_TCS(tcs);
	DECLARE_COMPLETION_ONSTACK(completion);
	DECLARE_COMPLETION_ONSTACK(tascb_completion);

	tascb->completion = &tascb_completion;

	spin_lock_irqsave(&task->task_state_lock, flags);
	अगर (task->task_state_flags & SAS_TASK_STATE_DONE) अणु
		spin_unlock_irqrestore(&task->task_state_lock, flags);
		res = TMF_RESP_FUNC_COMPLETE;
		ASD_DPRINTK("%s: task 0x%p done\n", __func__, task);
		जाओ out_करोne;
	पूर्ण
	spin_unlock_irqrestore(&task->task_state_lock, flags);

	ascb = asd_ascb_alloc_list(asd_ha, &res, GFP_KERNEL);
	अगर (!ascb)
		वापस -ENOMEM;

	ascb->uldd_task = &tcs;
	ascb->completion = &completion;
	scb = ascb->scb;
	scb->header.opcode = SCB_ABORT_TASK;

	चयन (task->task_proto) अणु
	हाल SAS_PROTOCOL_SATA:
	हाल SAS_PROTOCOL_STP:
		scb->पात_task.proto_conn_rate = (1 << 5); /* STP */
		अवरोध;
	हाल SAS_PROTOCOL_SSP:
		scb->पात_task.proto_conn_rate  = (1 << 4); /* SSP */
		scb->पात_task.proto_conn_rate |= task->dev->linkrate;
		अवरोध;
	हाल SAS_PROTOCOL_SMP:
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (task->task_proto == SAS_PROTOCOL_SSP) अणु
		scb->पात_task.ssp_frame.frame_type = SSP_TASK;
		स_नकल(scb->पात_task.ssp_frame.hashed_dest_addr,
		       task->dev->hashed_sas_addr, HASHED_SAS_ADDR_SIZE);
		स_नकल(scb->पात_task.ssp_frame.hashed_src_addr,
		       task->dev->port->ha->hashed_sas_addr,
		       HASHED_SAS_ADDR_SIZE);
		scb->पात_task.ssp_frame.tptt = cpu_to_be16(0xFFFF);

		स_नकल(scb->पात_task.ssp_task.lun, task->ssp_task.LUN, 8);
		scb->पात_task.ssp_task.पंचांगf = TMF_ABORT_TASK;
		scb->पात_task.ssp_task.tag = cpu_to_be16(0xFFFF);
	पूर्ण

	scb->पात_task.sister_scb = cpu_to_le16(0xFFFF);
	scb->पात_task.conn_handle = cpu_to_le16(
		(u16)(अचिन्हित दीर्घ)task->dev->lldd_dev);
	scb->पात_task.retry_count = 1;
	scb->पात_task.index = cpu_to_le16((u16)tascb->tc_index);
	scb->पात_task.itnl_to = cpu_to_le16(ITNL_TIMEOUT_CONST);

	res = asd_enqueue_पूर्णांकernal(ascb, asd_पंचांगf_tasklet_complete,
				   asd_पंचांगf_समयकरोut);
	अगर (res)
		जाओ out_मुक्त;
	रुको_क्रम_completion(&completion);
	ASD_DPRINTK("tmf came back\n");

	tascb->tag = tcs.tag;
	tascb->tag_valid = tcs.tag_valid;

	spin_lock_irqsave(&task->task_state_lock, flags);
	अगर (task->task_state_flags & SAS_TASK_STATE_DONE) अणु
		spin_unlock_irqrestore(&task->task_state_lock, flags);
		res = TMF_RESP_FUNC_COMPLETE;
		ASD_DPRINTK("%s: task 0x%p done\n", __func__, task);
		जाओ out_करोne;
	पूर्ण
	spin_unlock_irqrestore(&task->task_state_lock, flags);

	अगर (tcs.dl_opcode == TC_SSP_RESP) अणु
		/* The task to be पातed has been sent to the device.
		 * We got a Response IU क्रम the ABORT TASK TMF. */
		अगर (tcs.पंचांगf_state == TMF_RESP_FUNC_COMPLETE)
			res = asd_clear_nexus(task);
		अन्यथा
			res = tcs.पंचांगf_state;
	पूर्ण अन्यथा अगर (tcs.dl_opcode == TC_NO_ERROR &&
		   tcs.पंचांगf_state == TMF_RESP_FUNC_FAILED) अणु
		/* समयout */
		res = TMF_RESP_FUNC_FAILED;
	पूर्ण अन्यथा अणु
		/* In the following we assume that the managing layer
		 * will _never_ make a mistake, when issuing ABORT
		 * TASK.
		 */
		चयन (tcs.dl_opcode) अणु
		शेष:
			res = asd_clear_nexus(task);
			fallthrough;
		हाल TC_NO_ERROR:
			अवरोध;
			/* The task hasn't been sent to the device xor
			 * we never got a (sane) Response IU क्रम the
			 * ABORT TASK TMF.
			 */
		हाल TF_NAK_RECV:
			res = TMF_RESP_INVALID_FRAME;
			अवरोध;
		हाल TF_TMF_TASK_DONE:	/* करोne but not reported yet */
			res = TMF_RESP_FUNC_FAILED;
			leftover =
				रुको_क्रम_completion_समयout(&tascb_completion,
							  AIC94XX_SCB_TIMEOUT);
			spin_lock_irqsave(&task->task_state_lock, flags);
			अगर (leftover < 1)
				res = TMF_RESP_FUNC_FAILED;
			अगर (task->task_state_flags & SAS_TASK_STATE_DONE)
				res = TMF_RESP_FUNC_COMPLETE;
			spin_unlock_irqrestore(&task->task_state_lock, flags);
			अवरोध;
		हाल TF_TMF_NO_TAG:
		हाल TF_TMF_TAG_FREE: /* the tag is in the मुक्त list */
		हाल TF_TMF_NO_CONN_HANDLE: /* no such device */
			res = TMF_RESP_FUNC_COMPLETE;
			अवरोध;
		हाल TF_TMF_NO_CTX: /* not in seq, or proto != SSP */
			res = TMF_RESP_FUNC_ESUPP;
			अवरोध;
		पूर्ण
	पूर्ण
 out_करोne:
	tascb->completion = शून्य;
	अगर (res == TMF_RESP_FUNC_COMPLETE) अणु
		task->lldd_task = शून्य;
		mb();
		asd_ascb_मुक्त(tascb);
	पूर्ण
	ASD_DPRINTK("task 0x%p aborted, res: 0x%x\n", task, res);
	वापस res;

 out_मुक्त:
	asd_ascb_मुक्त(ascb);
	ASD_DPRINTK("task 0x%p aborted, res: 0x%x\n", task, res);
	वापस res;
पूर्ण

/**
 * asd_initiate_ssp_पंचांगf -- send a TMF to an I_T_L or I_T_L_Q nexus
 * @dev: poपूर्णांकer to काष्ठा करोमुख्य_device of पूर्णांकerest
 * @lun: poपूर्णांकer to u8[8] which is the LUN
 * @पंचांगf: the TMF to be perक्रमmed (see sas_task.h or the SAS spec)
 * @index: the transaction context of the task to be queried अगर QT TMF
 *
 * This function is used to send ABORT TASK SET, CLEAR ACA,
 * CLEAR TASK SET, LU RESET and QUERY TASK TMFs.
 *
 * No SCBs should be queued to the I_T_L nexus when this SCB is
 * pending.
 *
 * Returns: TMF response code (see sas_task.h or the SAS spec)
 */
अटल पूर्णांक asd_initiate_ssp_पंचांगf(काष्ठा करोमुख्य_device *dev, u8 *lun,
				पूर्णांक पंचांगf, पूर्णांक index)
अणु
	काष्ठा asd_ha_काष्ठा *asd_ha = dev->port->ha->lldd_ha;
	काष्ठा asd_ascb *ascb;
	पूर्णांक res = 1;
	काष्ठा scb *scb;
	DECLARE_COMPLETION_ONSTACK(completion);
	DECLARE_TCS(tcs);

	अगर (!(dev->tproto & SAS_PROTOCOL_SSP))
		वापस TMF_RESP_FUNC_ESUPP;

	ascb = asd_ascb_alloc_list(asd_ha, &res, GFP_KERNEL);
	अगर (!ascb)
		वापस -ENOMEM;

	ascb->completion = &completion;
	ascb->uldd_task = &tcs;
	scb = ascb->scb;

	अगर (पंचांगf == TMF_QUERY_TASK)
		scb->header.opcode = QUERY_SSP_TASK;
	अन्यथा
		scb->header.opcode = INITIATE_SSP_TMF;

	scb->ssp_पंचांगf.proto_conn_rate  = (1 << 4); /* SSP */
	scb->ssp_पंचांगf.proto_conn_rate |= dev->linkrate;
	/* SSP frame header */
	scb->ssp_पंचांगf.ssp_frame.frame_type = SSP_TASK;
	स_नकल(scb->ssp_पंचांगf.ssp_frame.hashed_dest_addr,
	       dev->hashed_sas_addr, HASHED_SAS_ADDR_SIZE);
	स_नकल(scb->ssp_पंचांगf.ssp_frame.hashed_src_addr,
	       dev->port->ha->hashed_sas_addr, HASHED_SAS_ADDR_SIZE);
	scb->ssp_पंचांगf.ssp_frame.tptt = cpu_to_be16(0xFFFF);
	/* SSP Task IU */
	स_नकल(scb->ssp_पंचांगf.ssp_task.lun, lun, 8);
	scb->ssp_पंचांगf.ssp_task.पंचांगf = पंचांगf;

	scb->ssp_पंचांगf.sister_scb = cpu_to_le16(0xFFFF);
	scb->ssp_पंचांगf.conn_handle= cpu_to_le16((u16)(अचिन्हित दीर्घ)
					      dev->lldd_dev);
	scb->ssp_पंचांगf.retry_count = 1;
	scb->ssp_पंचांगf.itnl_to = cpu_to_le16(ITNL_TIMEOUT_CONST);
	अगर (पंचांगf == TMF_QUERY_TASK)
		scb->ssp_पंचांगf.index = cpu_to_le16(index);

	res = asd_enqueue_पूर्णांकernal(ascb, asd_पंचांगf_tasklet_complete,
				   asd_पंचांगf_समयकरोut);
	अगर (res)
		जाओ out_err;
	रुको_क्रम_completion(&completion);

	चयन (tcs.dl_opcode) अणु
	हाल TC_NO_ERROR:
		res = TMF_RESP_FUNC_COMPLETE;
		अवरोध;
	हाल TF_NAK_RECV:
		res = TMF_RESP_INVALID_FRAME;
		अवरोध;
	हाल TF_TMF_TASK_DONE:
		res = TMF_RESP_FUNC_FAILED;
		अवरोध;
	हाल TF_TMF_NO_TAG:
	हाल TF_TMF_TAG_FREE: /* the tag is in the मुक्त list */
	हाल TF_TMF_NO_CONN_HANDLE: /* no such device */
		res = TMF_RESP_FUNC_COMPLETE;
		अवरोध;
	हाल TF_TMF_NO_CTX: /* not in seq, or proto != SSP */
		res = TMF_RESP_FUNC_ESUPP;
		अवरोध;
	शेष:
		/* Allow TMF response codes to propagate upwards */
		res = tcs.dl_opcode;
		अवरोध;
	पूर्ण
	वापस res;
out_err:
	asd_ascb_मुक्त(ascb);
	वापस res;
पूर्ण

पूर्णांक asd_पात_task_set(काष्ठा करोमुख्य_device *dev, u8 *lun)
अणु
	पूर्णांक res = asd_initiate_ssp_पंचांगf(dev, lun, TMF_ABORT_TASK_SET, 0);

	अगर (res == TMF_RESP_FUNC_COMPLETE)
		asd_clear_nexus_I_T_L(dev, lun);
	वापस res;
पूर्ण

पूर्णांक asd_clear_aca(काष्ठा करोमुख्य_device *dev, u8 *lun)
अणु
	पूर्णांक res = asd_initiate_ssp_पंचांगf(dev, lun, TMF_CLEAR_ACA, 0);

	अगर (res == TMF_RESP_FUNC_COMPLETE)
		asd_clear_nexus_I_T_L(dev, lun);
	वापस res;
पूर्ण

पूर्णांक asd_clear_task_set(काष्ठा करोमुख्य_device *dev, u8 *lun)
अणु
	पूर्णांक res = asd_initiate_ssp_पंचांगf(dev, lun, TMF_CLEAR_TASK_SET, 0);

	अगर (res == TMF_RESP_FUNC_COMPLETE)
		asd_clear_nexus_I_T_L(dev, lun);
	वापस res;
पूर्ण

पूर्णांक asd_lu_reset(काष्ठा करोमुख्य_device *dev, u8 *lun)
अणु
	पूर्णांक res = asd_initiate_ssp_पंचांगf(dev, lun, TMF_LU_RESET, 0);

	अगर (res == TMF_RESP_FUNC_COMPLETE)
		asd_clear_nexus_I_T_L(dev, lun);
	वापस res;
पूर्ण

/**
 * asd_query_task -- send a QUERY TASK TMF to an I_T_L_Q nexus
 * @task: poपूर्णांकer to sas_task काष्ठा of पूर्णांकerest
 *
 * Returns: TMF_RESP_FUNC_COMPLETE अगर the task is not in the task set,
 * or TMF_RESP_FUNC_SUCC अगर the task is in the task set.
 *
 * Normally the management layer sets the task to पातed state,
 * and then calls query task and then पात task.
 */
पूर्णांक asd_query_task(काष्ठा sas_task *task)
अणु
	काष्ठा asd_ascb *ascb = task->lldd_task;
	पूर्णांक index;

	अगर (ascb) अणु
		index = ascb->tc_index;
		वापस asd_initiate_ssp_पंचांगf(task->dev, task->ssp_task.LUN,
					    TMF_QUERY_TASK, index);
	पूर्ण
	वापस TMF_RESP_FUNC_COMPLETE;
पूर्ण
