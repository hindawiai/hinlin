<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Aic94xx SAS/SATA Tasks
 *
 * Copyright (C) 2005 Adaptec, Inc.  All rights reserved.
 * Copyright (C) 2005 Luben Tuikov <luben_tuikov@adaptec.com>
 */

#समावेश <linux/spinlock.h>
#समावेश "aic94xx.h"
#समावेश "aic94xx_sas.h"
#समावेश "aic94xx_hwi.h"

अटल व्योम asd_unbuild_ata_ascb(काष्ठा asd_ascb *a);
अटल व्योम asd_unbuild_smp_ascb(काष्ठा asd_ascb *a);
अटल व्योम asd_unbuild_ssp_ascb(काष्ठा asd_ascb *a);

अटल व्योम asd_can_dequeue(काष्ठा asd_ha_काष्ठा *asd_ha, पूर्णांक num)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&asd_ha->seq.pend_q_lock, flags);
	asd_ha->seq.can_queue += num;
	spin_unlock_irqrestore(&asd_ha->seq.pend_q_lock, flags);
पूर्ण

/* DMA_... to our direction translation.
 */
अटल स्थिर u8 data_dir_flags[] = अणु
	[DMA_BIसूचीECTIONAL]	= DATA_सूची_BYRECIPIENT,	/* UNSPECIFIED */
	[DMA_TO_DEVICE]		= DATA_सूची_OUT,		/* OUTBOUND */
	[DMA_FROM_DEVICE]	= DATA_सूची_IN,		/* INBOUND */
	[DMA_NONE]		= DATA_सूची_NONE,	/* NO TRANSFER */
पूर्ण;

अटल पूर्णांक asd_map_scatterlist(काष्ठा sas_task *task,
			       काष्ठा sg_el *sg_arr,
			       gfp_t gfp_flags)
अणु
	काष्ठा asd_ascb *ascb = task->lldd_task;
	काष्ठा asd_ha_काष्ठा *asd_ha = ascb->ha;
	काष्ठा scatterlist *sc;
	पूर्णांक num_sg, res;

	अगर (task->data_dir == DMA_NONE)
		वापस 0;

	अगर (task->num_scatter == 0) अणु
		व्योम *p = task->scatter;
		dma_addr_t dma = dma_map_single(&asd_ha->pcidev->dev, p,
						task->total_xfer_len,
						task->data_dir);
		sg_arr[0].bus_addr = cpu_to_le64((u64)dma);
		sg_arr[0].size = cpu_to_le32(task->total_xfer_len);
		sg_arr[0].flags |= ASD_SG_EL_LIST_EOL;
		वापस 0;
	पूर्ण

	/* STP tasks come from libata which has alपढ़ोy mapped
	 * the SG list */
	अगर (sas_protocol_ata(task->task_proto))
		num_sg = task->num_scatter;
	अन्यथा
		num_sg = dma_map_sg(&asd_ha->pcidev->dev, task->scatter,
				    task->num_scatter, task->data_dir);
	अगर (num_sg == 0)
		वापस -ENOMEM;

	अगर (num_sg > 3) अणु
		पूर्णांक i;

		ascb->sg_arr = asd_alloc_coherent(asd_ha,
						  num_sg*माप(काष्ठा sg_el),
						  gfp_flags);
		अगर (!ascb->sg_arr) अणु
			res = -ENOMEM;
			जाओ err_unmap;
		पूर्ण
		क्रम_each_sg(task->scatter, sc, num_sg, i) अणु
			काष्ठा sg_el *sg =
				&((काष्ठा sg_el *)ascb->sg_arr->vaddr)[i];
			sg->bus_addr = cpu_to_le64((u64)sg_dma_address(sc));
			sg->size = cpu_to_le32((u32)sg_dma_len(sc));
			अगर (i == num_sg-1)
				sg->flags |= ASD_SG_EL_LIST_EOL;
		पूर्ण

		क्रम_each_sg(task->scatter, sc, 2, i) अणु
			sg_arr[i].bus_addr =
				cpu_to_le64((u64)sg_dma_address(sc));
			sg_arr[i].size = cpu_to_le32((u32)sg_dma_len(sc));
		पूर्ण
		sg_arr[1].next_sg_offs = 2 * माप(*sg_arr);
		sg_arr[1].flags |= ASD_SG_EL_LIST_EOS;

		स_रखो(&sg_arr[2], 0, माप(*sg_arr));
		sg_arr[2].bus_addr=cpu_to_le64((u64)ascb->sg_arr->dma_handle);
	पूर्ण अन्यथा अणु
		पूर्णांक i;
		क्रम_each_sg(task->scatter, sc, num_sg, i) अणु
			sg_arr[i].bus_addr =
				cpu_to_le64((u64)sg_dma_address(sc));
			sg_arr[i].size = cpu_to_le32((u32)sg_dma_len(sc));
		पूर्ण
		sg_arr[i-1].flags |= ASD_SG_EL_LIST_EOL;
	पूर्ण

	वापस 0;
err_unmap:
	अगर (sas_protocol_ata(task->task_proto))
		dma_unmap_sg(&asd_ha->pcidev->dev, task->scatter,
			     task->num_scatter, task->data_dir);
	वापस res;
पूर्ण

अटल व्योम asd_unmap_scatterlist(काष्ठा asd_ascb *ascb)
अणु
	काष्ठा asd_ha_काष्ठा *asd_ha = ascb->ha;
	काष्ठा sas_task *task = ascb->uldd_task;

	अगर (task->data_dir == DMA_NONE)
		वापस;

	अगर (task->num_scatter == 0) अणु
		dma_addr_t dma = (dma_addr_t)
		       le64_to_cpu(ascb->scb->ssp_task.sg_element[0].bus_addr);
		dma_unmap_single(&ascb->ha->pcidev->dev, dma,
				 task->total_xfer_len, task->data_dir);
		वापस;
	पूर्ण

	asd_मुक्त_coherent(asd_ha, ascb->sg_arr);
	अगर (task->task_proto != SAS_PROTOCOL_STP)
		dma_unmap_sg(&asd_ha->pcidev->dev, task->scatter,
			     task->num_scatter, task->data_dir);
पूर्ण

/* ---------- Task complete tasklet ---------- */

अटल व्योम asd_get_response_tasklet(काष्ठा asd_ascb *ascb,
				     काष्ठा करोne_list_काष्ठा *dl)
अणु
	काष्ठा asd_ha_काष्ठा *asd_ha = ascb->ha;
	काष्ठा sas_task *task = ascb->uldd_task;
	काष्ठा task_status_काष्ठा *ts = &task->task_status;
	अचिन्हित दीर्घ flags;
	काष्ठा tc_resp_sb_काष्ठा अणु
		__le16 index_escb;
		u8     len_lsb;
		u8     flags;
	पूर्ण __attribute__ ((packed)) *resp_sb = (व्योम *) dl->status_block;

/* 	पूर्णांक  size   = ((resp_sb->flags & 7) << 8) | resp_sb->len_lsb; */
	पूर्णांक  edb_id = ((resp_sb->flags & 0x70) >> 4)-1;
	काष्ठा asd_ascb *escb;
	काष्ठा asd_dma_tok *edb;
	व्योम *r;

	spin_lock_irqsave(&asd_ha->seq.tc_index_lock, flags);
	escb = asd_tc_index_find(&asd_ha->seq,
				 (पूर्णांक)le16_to_cpu(resp_sb->index_escb));
	spin_unlock_irqrestore(&asd_ha->seq.tc_index_lock, flags);

	अगर (!escb) अणु
		ASD_DPRINTK("Uh-oh! No escb for this dl?!\n");
		वापस;
	पूर्ण

	ts->buf_valid_size = 0;
	edb = asd_ha->seq.edb_arr[edb_id + escb->edb_index];
	r = edb->vaddr;
	अगर (task->task_proto == SAS_PROTOCOL_SSP) अणु
		काष्ठा ssp_response_iu *iu =
			r + 16 + माप(काष्ठा ssp_frame_hdr);

		ts->residual = le32_to_cpu(*(__le32 *)r);

		sas_ssp_task_response(&asd_ha->pcidev->dev, task, iu);
	पूर्ण  अन्यथा अणु
		काष्ठा ata_task_resp *resp = (व्योम *) &ts->buf[0];

		ts->residual = le32_to_cpu(*(__le32 *)r);

		अगर (SAS_STATUS_BUF_SIZE >= माप(*resp)) अणु
			resp->frame_len = le16_to_cpu(*(__le16 *)(r+6));
			स_नकल(&resp->ending_fis[0], r+16, ATA_RESP_FIS_SIZE);
			ts->buf_valid_size = माप(*resp);
		पूर्ण
	पूर्ण

	asd_invalidate_edb(escb, edb_id);
पूर्ण

अटल व्योम asd_task_tasklet_complete(काष्ठा asd_ascb *ascb,
				      काष्ठा करोne_list_काष्ठा *dl)
अणु
	काष्ठा sas_task *task = ascb->uldd_task;
	काष्ठा task_status_काष्ठा *ts = &task->task_status;
	अचिन्हित दीर्घ flags;
	u8 opcode = dl->opcode;

	asd_can_dequeue(ascb->ha, 1);

Again:
	चयन (opcode) अणु
	हाल TC_NO_ERROR:
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAM_STAT_GOOD;
		अवरोध;
	हाल TC_UNDERRUN:
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DATA_UNDERRUN;
		ts->residual = le32_to_cpu(*(__le32 *)dl->status_block);
		अवरोध;
	हाल TC_OVERRUN:
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DATA_OVERRUN;
		ts->residual = 0;
		अवरोध;
	हाल TC_SSP_RESP:
	हाल TC_ATA_RESP:
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_PROTO_RESPONSE;
		asd_get_response_tasklet(ascb, dl);
		अवरोध;
	हाल TF_OPEN_REJECT:
		ts->resp = SAS_TASK_UNDELIVERED;
		ts->stat = SAS_OPEN_REJECT;
		अगर (dl->status_block[1] & 2)
			ts->खोलो_rej_reason = 1 + dl->status_block[2];
		अन्यथा अगर (dl->status_block[1] & 1)
			ts->खोलो_rej_reason = (dl->status_block[2] >> 4)+10;
		अन्यथा
			ts->खोलो_rej_reason = SAS_OREJ_UNKNOWN;
		अवरोध;
	हाल TF_OPEN_TO:
		ts->resp = SAS_TASK_UNDELIVERED;
		ts->stat = SAS_OPEN_TO;
		अवरोध;
	हाल TF_PHY_DOWN:
	हाल TU_PHY_DOWN:
		ts->resp = SAS_TASK_UNDELIVERED;
		ts->stat = SAS_PHY_DOWN;
		अवरोध;
	हाल TI_PHY_DOWN:
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_PHY_DOWN;
		अवरोध;
	हाल TI_BREAK:
	हाल TI_PROTO_ERR:
	हाल TI_NAK:
	हाल TI_ACK_NAK_TO:
	हाल TF_SMP_XMIT_RCV_ERR:
	हाल TC_ATA_R_ERR_RECV:
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_INTERRUPTED;
		अवरोध;
	हाल TF_BREAK:
	हाल TU_BREAK:
	हाल TU_ACK_NAK_TO:
	हाल TF_SMPRSP_TO:
		ts->resp = SAS_TASK_UNDELIVERED;
		ts->stat = SAS_DEV_NO_RESPONSE;
		अवरोध;
	हाल TF_NAK_RECV:
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_NAK_R_ERR;
		अवरोध;
	हाल TA_I_T_NEXUS_LOSS:
		opcode = dl->status_block[0];
		जाओ Again;
	हाल TF_INV_CONN_HANDLE:
		ts->resp = SAS_TASK_UNDELIVERED;
		ts->stat = SAS_DEVICE_UNKNOWN;
		अवरोध;
	हाल TF_REQUESTED_N_PENDING:
		ts->resp = SAS_TASK_UNDELIVERED;
		ts->stat = SAS_PENDING;
		अवरोध;
	हाल TC_TASK_CLEARED:
	हाल TA_ON_REQ:
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_ABORTED_TASK;
		अवरोध;

	हाल TF_NO_SMP_CONN:
	हाल TF_TMF_NO_CTX:
	हाल TF_TMF_NO_TAG:
	हाल TF_TMF_TAG_FREE:
	हाल TF_TMF_TASK_DONE:
	हाल TF_TMF_NO_CONN_HANDLE:
	हाल TF_IRTT_TO:
	हाल TF_IU_SHORT:
	हाल TF_DATA_OFFS_ERR:
		ts->resp = SAS_TASK_UNDELIVERED;
		ts->stat = SAS_DEV_NO_RESPONSE;
		अवरोध;

	हाल TC_LINK_ADM_RESP:
	हाल TC_CONTROL_PHY:
	हाल TC_RESUME:
	हाल TC_PARTIAL_SG_LIST:
	शेष:
		ASD_DPRINTK("%s: dl opcode: 0x%x?\n", __func__, opcode);
		अवरोध;
	पूर्ण

	चयन (task->task_proto) अणु
	हाल SAS_PROTOCOL_SATA:
	हाल SAS_PROTOCOL_STP:
		asd_unbuild_ata_ascb(ascb);
		अवरोध;
	हाल SAS_PROTOCOL_SMP:
		asd_unbuild_smp_ascb(ascb);
		अवरोध;
	हाल SAS_PROTOCOL_SSP:
		asd_unbuild_ssp_ascb(ascb);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	spin_lock_irqsave(&task->task_state_lock, flags);
	task->task_state_flags &= ~SAS_TASK_STATE_PENDING;
	task->task_state_flags &= ~SAS_TASK_AT_INITIATOR;
	task->task_state_flags |= SAS_TASK_STATE_DONE;
	अगर (unlikely((task->task_state_flags & SAS_TASK_STATE_ABORTED))) अणु
		काष्ठा completion *completion = ascb->completion;
		spin_unlock_irqrestore(&task->task_state_lock, flags);
		ASD_DPRINTK("task 0x%p done with opcode 0x%x resp 0x%x "
			    "stat 0x%x but aborted by upper layer!\n",
			    task, opcode, ts->resp, ts->stat);
		अगर (completion)
			complete(completion);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&task->task_state_lock, flags);
		task->lldd_task = शून्य;
		asd_ascb_मुक्त(ascb);
		mb();
		task->task_करोne(task);
	पूर्ण
पूर्ण

/* ---------- ATA ---------- */

अटल पूर्णांक asd_build_ata_ascb(काष्ठा asd_ascb *ascb, काष्ठा sas_task *task,
			      gfp_t gfp_flags)
अणु
	काष्ठा करोमुख्य_device *dev = task->dev;
	काष्ठा scb *scb;
	u8     flags;
	पूर्णांक    res = 0;

	scb = ascb->scb;

	अगर (unlikely(task->ata_task.device_control_reg_update))
		scb->header.opcode = CONTROL_ATA_DEV;
	अन्यथा अगर (dev->sata_dev.class == ATA_DEV_ATAPI)
		scb->header.opcode = INITIATE_ATAPI_TASK;
	अन्यथा
		scb->header.opcode = INITIATE_ATA_TASK;

	scb->ata_task.proto_conn_rate = (1 << 5); /* STP */
	अगर (dev->port->oob_mode == SAS_OOB_MODE)
		scb->ata_task.proto_conn_rate |= dev->linkrate;

	scb->ata_task.total_xfer_len = cpu_to_le32(task->total_xfer_len);
	scb->ata_task.fis = task->ata_task.fis;
	अगर (likely(!task->ata_task.device_control_reg_update))
		scb->ata_task.fis.flags |= 0x80; /* C=1: update ATA cmd reg */
	scb->ata_task.fis.flags &= 0xF0; /* PM_PORT field shall be 0 */
	अगर (dev->sata_dev.class == ATA_DEV_ATAPI)
		स_नकल(scb->ata_task.atapi_packet, task->ata_task.atapi_packet,
		       16);
	scb->ata_task.sister_scb = cpu_to_le16(0xFFFF);
	scb->ata_task.conn_handle = cpu_to_le16(
		(u16)(अचिन्हित दीर्घ)dev->lldd_dev);

	अगर (likely(!task->ata_task.device_control_reg_update)) अणु
		flags = 0;
		अगर (task->ata_task.dma_xfer)
			flags |= DATA_XFER_MODE_DMA;
		अगर (task->ata_task.use_ncq &&
		    dev->sata_dev.class != ATA_DEV_ATAPI)
			flags |= ATA_Q_TYPE_NCQ;
		flags |= data_dir_flags[task->data_dir];
		scb->ata_task.ata_flags = flags;

		scb->ata_task.retry_count = task->ata_task.retry_count;

		flags = 0;
		अगर (task->ata_task.set_affil_pol)
			flags |= SET_AFFIL_POLICY;
		अगर (task->ata_task.stp_affil_pol)
			flags |= STP_AFFIL_POLICY;
		scb->ata_task.flags = flags;
	पूर्ण
	ascb->tasklet_complete = asd_task_tasklet_complete;

	अगर (likely(!task->ata_task.device_control_reg_update))
		res = asd_map_scatterlist(task, scb->ata_task.sg_element,
					  gfp_flags);

	वापस res;
पूर्ण

अटल व्योम asd_unbuild_ata_ascb(काष्ठा asd_ascb *a)
अणु
	asd_unmap_scatterlist(a);
पूर्ण

/* ---------- SMP ---------- */

अटल पूर्णांक asd_build_smp_ascb(काष्ठा asd_ascb *ascb, काष्ठा sas_task *task,
			      gfp_t gfp_flags)
अणु
	काष्ठा asd_ha_काष्ठा *asd_ha = ascb->ha;
	काष्ठा करोमुख्य_device *dev = task->dev;
	काष्ठा scb *scb;

	dma_map_sg(&asd_ha->pcidev->dev, &task->smp_task.smp_req, 1,
		   DMA_TO_DEVICE);
	dma_map_sg(&asd_ha->pcidev->dev, &task->smp_task.smp_resp, 1,
		   DMA_FROM_DEVICE);

	scb = ascb->scb;

	scb->header.opcode = INITIATE_SMP_TASK;

	scb->smp_task.proto_conn_rate = dev->linkrate;

	scb->smp_task.smp_req.bus_addr =
		cpu_to_le64((u64)sg_dma_address(&task->smp_task.smp_req));
	scb->smp_task.smp_req.size =
		cpu_to_le32((u32)sg_dma_len(&task->smp_task.smp_req)-4);

	scb->smp_task.smp_resp.bus_addr =
		cpu_to_le64((u64)sg_dma_address(&task->smp_task.smp_resp));
	scb->smp_task.smp_resp.size =
		cpu_to_le32((u32)sg_dma_len(&task->smp_task.smp_resp)-4);

	scb->smp_task.sister_scb = cpu_to_le16(0xFFFF);
	scb->smp_task.conn_handle = cpu_to_le16((u16)
						(अचिन्हित दीर्घ)dev->lldd_dev);

	ascb->tasklet_complete = asd_task_tasklet_complete;

	वापस 0;
पूर्ण

अटल व्योम asd_unbuild_smp_ascb(काष्ठा asd_ascb *a)
अणु
	काष्ठा sas_task *task = a->uldd_task;

	BUG_ON(!task);
	dma_unmap_sg(&a->ha->pcidev->dev, &task->smp_task.smp_req, 1,
		     DMA_TO_DEVICE);
	dma_unmap_sg(&a->ha->pcidev->dev, &task->smp_task.smp_resp, 1,
		     DMA_FROM_DEVICE);
पूर्ण

/* ---------- SSP ---------- */

अटल पूर्णांक asd_build_ssp_ascb(काष्ठा asd_ascb *ascb, काष्ठा sas_task *task,
			      gfp_t gfp_flags)
अणु
	काष्ठा करोमुख्य_device *dev = task->dev;
	काष्ठा scb *scb;
	पूर्णांक    res = 0;

	scb = ascb->scb;

	scb->header.opcode = INITIATE_SSP_TASK;

	scb->ssp_task.proto_conn_rate  = (1 << 4); /* SSP */
	scb->ssp_task.proto_conn_rate |= dev->linkrate;
	scb->ssp_task.total_xfer_len = cpu_to_le32(task->total_xfer_len);
	scb->ssp_task.ssp_frame.frame_type = SSP_DATA;
	स_नकल(scb->ssp_task.ssp_frame.hashed_dest_addr, dev->hashed_sas_addr,
	       HASHED_SAS_ADDR_SIZE);
	स_नकल(scb->ssp_task.ssp_frame.hashed_src_addr,
	       dev->port->ha->hashed_sas_addr, HASHED_SAS_ADDR_SIZE);
	scb->ssp_task.ssp_frame.tptt = cpu_to_be16(0xFFFF);

	स_नकल(scb->ssp_task.ssp_cmd.lun, task->ssp_task.LUN, 8);
	अगर (task->ssp_task.enable_first_burst)
		scb->ssp_task.ssp_cmd.efb_prio_attr |= EFB_MASK;
	scb->ssp_task.ssp_cmd.efb_prio_attr |= (task->ssp_task.task_prio << 3);
	scb->ssp_task.ssp_cmd.efb_prio_attr |= (task->ssp_task.task_attr & 7);
	स_नकल(scb->ssp_task.ssp_cmd.cdb, task->ssp_task.cmd->cmnd,
	       task->ssp_task.cmd->cmd_len);

	scb->ssp_task.sister_scb = cpu_to_le16(0xFFFF);
	scb->ssp_task.conn_handle = cpu_to_le16(
		(u16)(अचिन्हित दीर्घ)dev->lldd_dev);
	scb->ssp_task.data_dir = data_dir_flags[task->data_dir];
	scb->ssp_task.retry_count = scb->ssp_task.retry_count;

	ascb->tasklet_complete = asd_task_tasklet_complete;

	res = asd_map_scatterlist(task, scb->ssp_task.sg_element, gfp_flags);

	वापस res;
पूर्ण

अटल व्योम asd_unbuild_ssp_ascb(काष्ठा asd_ascb *a)
अणु
	asd_unmap_scatterlist(a);
पूर्ण

/* ---------- Execute Task ---------- */

अटल पूर्णांक asd_can_queue(काष्ठा asd_ha_काष्ठा *asd_ha, पूर्णांक num)
अणु
	पूर्णांक res = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&asd_ha->seq.pend_q_lock, flags);
	अगर ((asd_ha->seq.can_queue - num) < 0)
		res = -SAS_QUEUE_FULL;
	अन्यथा
		asd_ha->seq.can_queue -= num;
	spin_unlock_irqrestore(&asd_ha->seq.pend_q_lock, flags);

	वापस res;
पूर्ण

पूर्णांक asd_execute_task(काष्ठा sas_task *task, gfp_t gfp_flags)
अणु
	पूर्णांक res = 0;
	LIST_HEAD(alist);
	काष्ठा sas_task *t = task;
	काष्ठा asd_ascb *ascb = शून्य, *a;
	काष्ठा asd_ha_काष्ठा *asd_ha = task->dev->port->ha->lldd_ha;
	अचिन्हित दीर्घ flags;

	res = asd_can_queue(asd_ha, 1);
	अगर (res)
		वापस res;

	res = 1;
	ascb = asd_ascb_alloc_list(asd_ha, &res, gfp_flags);
	अगर (res) अणु
		res = -ENOMEM;
		जाओ out_err;
	पूर्ण

	__list_add(&alist, ascb->list.prev, &ascb->list);
	list_क्रम_each_entry(a, &alist, list) अणु
		a->uldd_task = t;
		t->lldd_task = a;
		अवरोध;
	पूर्ण
	list_क्रम_each_entry(a, &alist, list) अणु
		t = a->uldd_task;
		a->uldd_समयr = 1;
		अगर (t->task_proto & SAS_PROTOCOL_STP)
			t->task_proto = SAS_PROTOCOL_STP;
		चयन (t->task_proto) अणु
		हाल SAS_PROTOCOL_SATA:
		हाल SAS_PROTOCOL_STP:
			res = asd_build_ata_ascb(a, t, gfp_flags);
			अवरोध;
		हाल SAS_PROTOCOL_SMP:
			res = asd_build_smp_ascb(a, t, gfp_flags);
			अवरोध;
		हाल SAS_PROTOCOL_SSP:
			res = asd_build_ssp_ascb(a, t, gfp_flags);
			अवरोध;
		शेष:
			asd_prपूर्णांकk("unknown sas_task proto: 0x%x\n",
				   t->task_proto);
			res = -ENOMEM;
			अवरोध;
		पूर्ण
		अगर (res)
			जाओ out_err_unmap;

		spin_lock_irqsave(&t->task_state_lock, flags);
		t->task_state_flags |= SAS_TASK_AT_INITIATOR;
		spin_unlock_irqrestore(&t->task_state_lock, flags);
	पूर्ण
	list_del_init(&alist);

	res = asd_post_ascb_list(asd_ha, ascb, 1);
	अगर (unlikely(res)) अणु
		a = शून्य;
		__list_add(&alist, ascb->list.prev, &ascb->list);
		जाओ out_err_unmap;
	पूर्ण

	वापस 0;
out_err_unmap:
	अणु
		काष्ठा asd_ascb *b = a;
		list_क्रम_each_entry(a, &alist, list) अणु
			अगर (a == b)
				अवरोध;
			t = a->uldd_task;
			spin_lock_irqsave(&t->task_state_lock, flags);
			t->task_state_flags &= ~SAS_TASK_AT_INITIATOR;
			spin_unlock_irqrestore(&t->task_state_lock, flags);
			चयन (t->task_proto) अणु
			हाल SAS_PROTOCOL_SATA:
			हाल SAS_PROTOCOL_STP:
				asd_unbuild_ata_ascb(a);
				अवरोध;
			हाल SAS_PROTOCOL_SMP:
				asd_unbuild_smp_ascb(a);
				अवरोध;
			हाल SAS_PROTOCOL_SSP:
				asd_unbuild_ssp_ascb(a);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			t->lldd_task = शून्य;
		पूर्ण
	पूर्ण
	list_del_init(&alist);
out_err:
	अगर (ascb)
		asd_ascb_मुक्त_list(ascb);
	asd_can_dequeue(asd_ha, 1);
	वापस res;
पूर्ण
