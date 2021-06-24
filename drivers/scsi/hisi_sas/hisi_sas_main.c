<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2015 Linaro Ltd.
 * Copyright (c) 2015 Hisilicon Limited.
 */

#समावेश "hisi_sas.h"
#घोषणा DRV_NAME "hisi_sas"

#घोषणा DEV_IS_GONE(dev) \
	((!dev) || (dev->dev_type == SAS_PHY_UNUSED))

अटल पूर्णांक hisi_sas_debug_issue_ssp_पंचांगf(काष्ठा करोमुख्य_device *device,
				u8 *lun, काष्ठा hisi_sas_पंचांगf_task *पंचांगf);
अटल पूर्णांक
hisi_sas_पूर्णांकernal_task_पात(काष्ठा hisi_hba *hisi_hba,
			     काष्ठा करोमुख्य_device *device,
			     पूर्णांक पात_flag, पूर्णांक tag);
अटल पूर्णांक hisi_sas_softreset_ata_disk(काष्ठा करोमुख्य_device *device);
अटल पूर्णांक hisi_sas_control_phy(काष्ठा asd_sas_phy *sas_phy, क्रमागत phy_func func,
				व्योम *funcdata);
अटल व्योम hisi_sas_release_task(काष्ठा hisi_hba *hisi_hba,
				  काष्ठा करोमुख्य_device *device);
अटल व्योम hisi_sas_dev_gone(काष्ठा करोमुख्य_device *device);

u8 hisi_sas_get_ata_protocol(काष्ठा host_to_dev_fis *fis, पूर्णांक direction)
अणु
	चयन (fis->command) अणु
	हाल ATA_CMD_FPDMA_WRITE:
	हाल ATA_CMD_FPDMA_READ:
	हाल ATA_CMD_FPDMA_RECV:
	हाल ATA_CMD_FPDMA_SEND:
	हाल ATA_CMD_NCQ_NON_DATA:
		वापस HISI_SAS_SATA_PROTOCOL_FPDMA;

	हाल ATA_CMD_DOWNLOAD_MICRO:
	हाल ATA_CMD_ID_ATA:
	हाल ATA_CMD_PMP_READ:
	हाल ATA_CMD_READ_LOG_EXT:
	हाल ATA_CMD_PIO_READ:
	हाल ATA_CMD_PIO_READ_EXT:
	हाल ATA_CMD_PMP_WRITE:
	हाल ATA_CMD_WRITE_LOG_EXT:
	हाल ATA_CMD_PIO_WRITE:
	हाल ATA_CMD_PIO_WRITE_EXT:
		वापस HISI_SAS_SATA_PROTOCOL_PIO;

	हाल ATA_CMD_DSM:
	हाल ATA_CMD_DOWNLOAD_MICRO_DMA:
	हाल ATA_CMD_PMP_READ_DMA:
	हाल ATA_CMD_PMP_WRITE_DMA:
	हाल ATA_CMD_READ:
	हाल ATA_CMD_READ_EXT:
	हाल ATA_CMD_READ_LOG_DMA_EXT:
	हाल ATA_CMD_READ_STREAM_DMA_EXT:
	हाल ATA_CMD_TRUSTED_RCV_DMA:
	हाल ATA_CMD_TRUSTED_SND_DMA:
	हाल ATA_CMD_WRITE:
	हाल ATA_CMD_WRITE_EXT:
	हाल ATA_CMD_WRITE_FUA_EXT:
	हाल ATA_CMD_WRITE_QUEUED:
	हाल ATA_CMD_WRITE_LOG_DMA_EXT:
	हाल ATA_CMD_WRITE_STREAM_DMA_EXT:
	हाल ATA_CMD_ZAC_MGMT_IN:
		वापस HISI_SAS_SATA_PROTOCOL_DMA;

	हाल ATA_CMD_CHK_POWER:
	हाल ATA_CMD_DEV_RESET:
	हाल ATA_CMD_EDD:
	हाल ATA_CMD_FLUSH:
	हाल ATA_CMD_FLUSH_EXT:
	हाल ATA_CMD_VERIFY:
	हाल ATA_CMD_VERIFY_EXT:
	हाल ATA_CMD_SET_FEATURES:
	हाल ATA_CMD_STANDBY:
	हाल ATA_CMD_STANDBYNOW1:
	हाल ATA_CMD_ZAC_MGMT_OUT:
		वापस HISI_SAS_SATA_PROTOCOL_NONDATA;

	हाल ATA_CMD_SET_MAX:
		चयन (fis->features) अणु
		हाल ATA_SET_MAX_PASSWD:
		हाल ATA_SET_MAX_LOCK:
			वापस HISI_SAS_SATA_PROTOCOL_PIO;

		हाल ATA_SET_MAX_PASSWD_DMA:
		हाल ATA_SET_MAX_UNLOCK_DMA:
			वापस HISI_SAS_SATA_PROTOCOL_DMA;

		शेष:
			वापस HISI_SAS_SATA_PROTOCOL_NONDATA;
		पूर्ण

	शेष:
	अणु
		अगर (direction == DMA_NONE)
			वापस HISI_SAS_SATA_PROTOCOL_NONDATA;
		वापस HISI_SAS_SATA_PROTOCOL_PIO;
	पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(hisi_sas_get_ata_protocol);

व्योम hisi_sas_sata_करोne(काष्ठा sas_task *task,
			    काष्ठा hisi_sas_slot *slot)
अणु
	काष्ठा task_status_काष्ठा *ts = &task->task_status;
	काष्ठा ata_task_resp *resp = (काष्ठा ata_task_resp *)ts->buf;
	काष्ठा hisi_sas_status_buffer *status_buf =
			hisi_sas_status_buf_addr_mem(slot);
	u8 *iu = &status_buf->iu[0];
	काष्ठा dev_to_host_fis *d2h =  (काष्ठा dev_to_host_fis *)iu;

	resp->frame_len = माप(काष्ठा dev_to_host_fis);
	स_नकल(&resp->ending_fis[0], d2h, माप(काष्ठा dev_to_host_fis));

	ts->buf_valid_size = माप(*resp);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_sas_sata_करोne);

/*
 * This function assumes linkrate mask fits in 8 bits, which it
 * करोes क्रम all HW versions supported.
 */
u8 hisi_sas_get_prog_phy_linkrate_mask(क्रमागत sas_linkrate max)
अणु
	u8 rate = 0;
	पूर्णांक i;

	max -= SAS_LINK_RATE_1_5_GBPS;
	क्रम (i = 0; i <= max; i++)
		rate |= 1 << (i * 2);
	वापस rate;
पूर्ण
EXPORT_SYMBOL_GPL(hisi_sas_get_prog_phy_linkrate_mask);

अटल काष्ठा hisi_hba *dev_to_hisi_hba(काष्ठा करोमुख्य_device *device)
अणु
	वापस device->port->ha->lldd_ha;
पूर्ण

काष्ठा hisi_sas_port *to_hisi_sas_port(काष्ठा asd_sas_port *sas_port)
अणु
	वापस container_of(sas_port, काष्ठा hisi_sas_port, sas_port);
पूर्ण
EXPORT_SYMBOL_GPL(to_hisi_sas_port);

व्योम hisi_sas_stop_phys(काष्ठा hisi_hba *hisi_hba)
अणु
	पूर्णांक phy_no;

	क्रम (phy_no = 0; phy_no < hisi_hba->n_phy; phy_no++)
		hisi_sas_phy_enable(hisi_hba, phy_no, 0);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_sas_stop_phys);

अटल व्योम hisi_sas_slot_index_clear(काष्ठा hisi_hba *hisi_hba, पूर्णांक slot_idx)
अणु
	व्योम *biपंचांगap = hisi_hba->slot_index_tags;

	clear_bit(slot_idx, biपंचांगap);
पूर्ण

अटल व्योम hisi_sas_slot_index_मुक्त(काष्ठा hisi_hba *hisi_hba, पूर्णांक slot_idx)
अणु
	अगर (hisi_hba->hw->slot_index_alloc ||
	    slot_idx >= HISI_SAS_UNRESERVED_IPTT) अणु
		spin_lock(&hisi_hba->lock);
		hisi_sas_slot_index_clear(hisi_hba, slot_idx);
		spin_unlock(&hisi_hba->lock);
	पूर्ण
पूर्ण

अटल व्योम hisi_sas_slot_index_set(काष्ठा hisi_hba *hisi_hba, पूर्णांक slot_idx)
अणु
	व्योम *biपंचांगap = hisi_hba->slot_index_tags;

	set_bit(slot_idx, biपंचांगap);
पूर्ण

अटल पूर्णांक hisi_sas_slot_index_alloc(काष्ठा hisi_hba *hisi_hba,
				     काष्ठा scsi_cmnd *scsi_cmnd)
अणु
	पूर्णांक index;
	व्योम *biपंचांगap = hisi_hba->slot_index_tags;

	अगर (scsi_cmnd)
		वापस scsi_cmnd->request->tag;

	spin_lock(&hisi_hba->lock);
	index = find_next_zero_bit(biपंचांगap, hisi_hba->slot_index_count,
				   hisi_hba->last_slot_index + 1);
	अगर (index >= hisi_hba->slot_index_count) अणु
		index = find_next_zero_bit(biपंचांगap,
				hisi_hba->slot_index_count,
				HISI_SAS_UNRESERVED_IPTT);
		अगर (index >= hisi_hba->slot_index_count) अणु
			spin_unlock(&hisi_hba->lock);
			वापस -SAS_QUEUE_FULL;
		पूर्ण
	पूर्ण
	hisi_sas_slot_index_set(hisi_hba, index);
	hisi_hba->last_slot_index = index;
	spin_unlock(&hisi_hba->lock);

	वापस index;
पूर्ण

अटल व्योम hisi_sas_slot_index_init(काष्ठा hisi_hba *hisi_hba)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < hisi_hba->slot_index_count; ++i)
		hisi_sas_slot_index_clear(hisi_hba, i);
पूर्ण

व्योम hisi_sas_slot_task_मुक्त(काष्ठा hisi_hba *hisi_hba, काष्ठा sas_task *task,
			     काष्ठा hisi_sas_slot *slot)
अणु
	पूर्णांक device_id = slot->device_id;
	काष्ठा hisi_sas_device *sas_dev = &hisi_hba->devices[device_id];

	अगर (task) अणु
		काष्ठा device *dev = hisi_hba->dev;

		अगर (!task->lldd_task)
			वापस;

		task->lldd_task = शून्य;

		अगर (!sas_protocol_ata(task->task_proto)) अणु
			अगर (slot->n_elem)
				dma_unmap_sg(dev, task->scatter,
					     task->num_scatter,
					     task->data_dir);
			अगर (slot->n_elem_dअगर) अणु
				काष्ठा sas_ssp_task *ssp_task = &task->ssp_task;
				काष्ठा scsi_cmnd *scsi_cmnd = ssp_task->cmd;

				dma_unmap_sg(dev, scsi_prot_sglist(scsi_cmnd),
					     scsi_prot_sg_count(scsi_cmnd),
					     task->data_dir);
			पूर्ण
		पूर्ण
	पूर्ण

	spin_lock(&sas_dev->lock);
	list_del_init(&slot->entry);
	spin_unlock(&sas_dev->lock);

	स_रखो(slot, 0, दुरत्व(काष्ठा hisi_sas_slot, buf));

	hisi_sas_slot_index_मुक्त(hisi_hba, slot->idx);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_sas_slot_task_मुक्त);

अटल व्योम hisi_sas_task_prep_smp(काष्ठा hisi_hba *hisi_hba,
				  काष्ठा hisi_sas_slot *slot)
अणु
	hisi_hba->hw->prep_smp(hisi_hba, slot);
पूर्ण

अटल व्योम hisi_sas_task_prep_ssp(काष्ठा hisi_hba *hisi_hba,
				  काष्ठा hisi_sas_slot *slot)
अणु
	hisi_hba->hw->prep_ssp(hisi_hba, slot);
पूर्ण

अटल व्योम hisi_sas_task_prep_ata(काष्ठा hisi_hba *hisi_hba,
				  काष्ठा hisi_sas_slot *slot)
अणु
	hisi_hba->hw->prep_stp(hisi_hba, slot);
पूर्ण

अटल व्योम hisi_sas_task_prep_पात(काष्ठा hisi_hba *hisi_hba,
		काष्ठा hisi_sas_slot *slot,
		पूर्णांक device_id, पूर्णांक पात_flag, पूर्णांक tag_to_पात)
अणु
	hisi_hba->hw->prep_पात(hisi_hba, slot,
			device_id, पात_flag, tag_to_पात);
पूर्ण

अटल व्योम hisi_sas_dma_unmap(काष्ठा hisi_hba *hisi_hba,
			       काष्ठा sas_task *task, पूर्णांक n_elem,
			       पूर्णांक n_elem_req)
अणु
	काष्ठा device *dev = hisi_hba->dev;

	अगर (!sas_protocol_ata(task->task_proto)) अणु
		अगर (task->num_scatter) अणु
			अगर (n_elem)
				dma_unmap_sg(dev, task->scatter,
					     task->num_scatter,
					     task->data_dir);
		पूर्ण अन्यथा अगर (task->task_proto & SAS_PROTOCOL_SMP) अणु
			अगर (n_elem_req)
				dma_unmap_sg(dev, &task->smp_task.smp_req,
					     1, DMA_TO_DEVICE);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक hisi_sas_dma_map(काष्ठा hisi_hba *hisi_hba,
			    काष्ठा sas_task *task, पूर्णांक *n_elem,
			    पूर्णांक *n_elem_req)
अणु
	काष्ठा device *dev = hisi_hba->dev;
	पूर्णांक rc;

	अगर (sas_protocol_ata(task->task_proto)) अणु
		*n_elem = task->num_scatter;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक req_len;

		अगर (task->num_scatter) अणु
			*n_elem = dma_map_sg(dev, task->scatter,
					     task->num_scatter, task->data_dir);
			अगर (!*n_elem) अणु
				rc = -ENOMEM;
				जाओ prep_out;
			पूर्ण
		पूर्ण अन्यथा अगर (task->task_proto & SAS_PROTOCOL_SMP) अणु
			*n_elem_req = dma_map_sg(dev, &task->smp_task.smp_req,
						 1, DMA_TO_DEVICE);
			अगर (!*n_elem_req) अणु
				rc = -ENOMEM;
				जाओ prep_out;
			पूर्ण
			req_len = sg_dma_len(&task->smp_task.smp_req);
			अगर (req_len & 0x3) अणु
				rc = -EINVAL;
				जाओ err_out_dma_unmap;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (*n_elem > HISI_SAS_SGE_PAGE_CNT) अणु
		dev_err(dev, "task prep: n_elem(%d) > HISI_SAS_SGE_PAGE_CNT\n",
			*n_elem);
		rc = -EINVAL;
		जाओ err_out_dma_unmap;
	पूर्ण
	वापस 0;

err_out_dma_unmap:
	/* It would be better to call dma_unmap_sg() here, but it's messy */
	hisi_sas_dma_unmap(hisi_hba, task, *n_elem,
			   *n_elem_req);
prep_out:
	वापस rc;
पूर्ण

अटल व्योम hisi_sas_dअगर_dma_unmap(काष्ठा hisi_hba *hisi_hba,
				   काष्ठा sas_task *task, पूर्णांक n_elem_dअगर)
अणु
	काष्ठा device *dev = hisi_hba->dev;

	अगर (n_elem_dअगर) अणु
		काष्ठा sas_ssp_task *ssp_task = &task->ssp_task;
		काष्ठा scsi_cmnd *scsi_cmnd = ssp_task->cmd;

		dma_unmap_sg(dev, scsi_prot_sglist(scsi_cmnd),
			     scsi_prot_sg_count(scsi_cmnd),
			     task->data_dir);
	पूर्ण
पूर्ण

अटल पूर्णांक hisi_sas_dअगर_dma_map(काष्ठा hisi_hba *hisi_hba,
				पूर्णांक *n_elem_dअगर, काष्ठा sas_task *task)
अणु
	काष्ठा device *dev = hisi_hba->dev;
	काष्ठा sas_ssp_task *ssp_task;
	काष्ठा scsi_cmnd *scsi_cmnd;
	पूर्णांक rc;

	अगर (task->num_scatter) अणु
		ssp_task = &task->ssp_task;
		scsi_cmnd = ssp_task->cmd;

		अगर (scsi_prot_sg_count(scsi_cmnd)) अणु
			*n_elem_dअगर = dma_map_sg(dev,
						 scsi_prot_sglist(scsi_cmnd),
						 scsi_prot_sg_count(scsi_cmnd),
						 task->data_dir);

			अगर (!*n_elem_dअगर)
				वापस -ENOMEM;

			अगर (*n_elem_dअगर > HISI_SAS_SGE_DIF_PAGE_CNT) अणु
				dev_err(dev, "task prep: n_elem_dif(%d) too large\n",
					*n_elem_dअगर);
				rc = -EINVAL;
				जाओ err_out_dअगर_dma_unmap;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;

err_out_dअगर_dma_unmap:
	dma_unmap_sg(dev, scsi_prot_sglist(scsi_cmnd),
		     scsi_prot_sg_count(scsi_cmnd), task->data_dir);
	वापस rc;
पूर्ण

अटल पूर्णांक hisi_sas_task_prep(काष्ठा sas_task *task,
			      काष्ठा hisi_sas_dq **dq_poपूर्णांकer,
			      bool is_पंचांगf, काष्ठा hisi_sas_पंचांगf_task *पंचांगf,
			      पूर्णांक *pass)
अणु
	काष्ठा करोमुख्य_device *device = task->dev;
	काष्ठा hisi_hba *hisi_hba = dev_to_hisi_hba(device);
	काष्ठा hisi_sas_device *sas_dev = device->lldd_dev;
	काष्ठा hisi_sas_port *port;
	काष्ठा hisi_sas_slot *slot;
	काष्ठा hisi_sas_cmd_hdr	*cmd_hdr_base;
	काष्ठा asd_sas_port *sas_port = device->port;
	काष्ठा device *dev = hisi_hba->dev;
	पूर्णांक dlvry_queue_slot, dlvry_queue, rc, slot_idx;
	पूर्णांक n_elem = 0, n_elem_dअगर = 0, n_elem_req = 0;
	काष्ठा scsi_cmnd *scmd = शून्य;
	काष्ठा hisi_sas_dq *dq;
	अचिन्हित दीर्घ flags;
	पूर्णांक wr_q_index;

	अगर (DEV_IS_GONE(sas_dev)) अणु
		अगर (sas_dev)
			dev_info(dev, "task prep: device %d not ready\n",
				 sas_dev->device_id);
		अन्यथा
			dev_info(dev, "task prep: device %016llx not ready\n",
				 SAS_ADDR(device->sas_addr));

		वापस -ECOMM;
	पूर्ण

	अगर (task->uldd_task) अणु
		काष्ठा ata_queued_cmd *qc;

		अगर (dev_is_sata(device)) अणु
			qc = task->uldd_task;
			scmd = qc->scsicmd;
		पूर्ण अन्यथा अणु
			scmd = task->uldd_task;
		पूर्ण
	पूर्ण

	अगर (scmd) अणु
		अचिन्हित पूर्णांक dq_index;
		u32 blk_tag;

		blk_tag = blk_mq_unique_tag(scmd->request);
		dq_index = blk_mq_unique_tag_to_hwq(blk_tag);
		*dq_poपूर्णांकer = dq = &hisi_hba->dq[dq_index];
	पूर्ण अन्यथा अणु
		काष्ठा Scsi_Host *shost = hisi_hba->shost;
		काष्ठा blk_mq_queue_map *qmap = &shost->tag_set.map[HCTX_TYPE_DEFAULT];
		पूर्णांक queue = qmap->mq_map[raw_smp_processor_id()];

		*dq_poपूर्णांकer = dq = &hisi_hba->dq[queue];
	पूर्ण

	port = to_hisi_sas_port(sas_port);
	अगर (port && !port->port_attached) अणु
		dev_info(dev, "task prep: %s port%d not attach device\n",
			 (dev_is_sata(device)) ?
			 "SATA/STP" : "SAS",
			 device->port->id);

		वापस -ECOMM;
	पूर्ण

	rc = hisi_sas_dma_map(hisi_hba, task, &n_elem,
			      &n_elem_req);
	अगर (rc < 0)
		जाओ prep_out;

	अगर (!sas_protocol_ata(task->task_proto)) अणु
		rc = hisi_sas_dअगर_dma_map(hisi_hba, &n_elem_dअगर, task);
		अगर (rc < 0)
			जाओ err_out_dma_unmap;
	पूर्ण

	अगर (hisi_hba->hw->slot_index_alloc)
		rc = hisi_hba->hw->slot_index_alloc(hisi_hba, device);
	अन्यथा
		rc = hisi_sas_slot_index_alloc(hisi_hba, scmd);

	अगर (rc < 0)
		जाओ err_out_dअगर_dma_unmap;

	slot_idx = rc;
	slot = &hisi_hba->slot_info[slot_idx];

	spin_lock(&dq->lock);
	wr_q_index = dq->wr_poपूर्णांक;
	dq->wr_poपूर्णांक = (dq->wr_poपूर्णांक + 1) % HISI_SAS_QUEUE_SLOTS;
	list_add_tail(&slot->delivery, &dq->list);
	spin_unlock(&dq->lock);
	spin_lock(&sas_dev->lock);
	list_add_tail(&slot->entry, &sas_dev->list);
	spin_unlock(&sas_dev->lock);

	dlvry_queue = dq->id;
	dlvry_queue_slot = wr_q_index;

	slot->device_id = sas_dev->device_id;
	slot->n_elem = n_elem;
	slot->n_elem_dअगर = n_elem_dअगर;
	slot->dlvry_queue = dlvry_queue;
	slot->dlvry_queue_slot = dlvry_queue_slot;
	cmd_hdr_base = hisi_hba->cmd_hdr[dlvry_queue];
	slot->cmd_hdr = &cmd_hdr_base[dlvry_queue_slot];
	slot->task = task;
	slot->port = port;
	slot->पंचांगf = पंचांगf;
	slot->is_पूर्णांकernal = is_पंचांगf;
	task->lldd_task = slot;

	स_रखो(slot->cmd_hdr, 0, माप(काष्ठा hisi_sas_cmd_hdr));
	स_रखो(hisi_sas_cmd_hdr_addr_mem(slot), 0, HISI_SAS_COMMAND_TABLE_SZ);
	स_रखो(hisi_sas_status_buf_addr_mem(slot), 0,
	       माप(काष्ठा hisi_sas_err_record));

	चयन (task->task_proto) अणु
	हाल SAS_PROTOCOL_SMP:
		hisi_sas_task_prep_smp(hisi_hba, slot);
		अवरोध;
	हाल SAS_PROTOCOL_SSP:
		hisi_sas_task_prep_ssp(hisi_hba, slot);
		अवरोध;
	हाल SAS_PROTOCOL_SATA:
	हाल SAS_PROTOCOL_STP:
	हाल SAS_PROTOCOL_SATA | SAS_PROTOCOL_STP:
		hisi_sas_task_prep_ata(hisi_hba, slot);
		अवरोध;
	शेष:
		dev_err(dev, "task prep: unknown/unsupported proto (0x%x)\n",
			task->task_proto);
		अवरोध;
	पूर्ण

	spin_lock_irqsave(&task->task_state_lock, flags);
	task->task_state_flags |= SAS_TASK_AT_INITIATOR;
	spin_unlock_irqrestore(&task->task_state_lock, flags);

	++(*pass);
	WRITE_ONCE(slot->पढ़ोy, 1);

	वापस 0;

err_out_dअगर_dma_unmap:
	अगर (!sas_protocol_ata(task->task_proto))
		hisi_sas_dअगर_dma_unmap(hisi_hba, task, n_elem_dअगर);
err_out_dma_unmap:
	hisi_sas_dma_unmap(hisi_hba, task, n_elem,
			   n_elem_req);
prep_out:
	dev_err(dev, "task prep: failed[%d]!\n", rc);
	वापस rc;
पूर्ण

अटल पूर्णांक hisi_sas_task_exec(काष्ठा sas_task *task, gfp_t gfp_flags,
			      bool is_पंचांगf, काष्ठा hisi_sas_पंचांगf_task *पंचांगf)
अणु
	u32 rc;
	u32 pass = 0;
	काष्ठा hisi_hba *hisi_hba;
	काष्ठा device *dev;
	काष्ठा करोमुख्य_device *device = task->dev;
	काष्ठा asd_sas_port *sas_port = device->port;
	काष्ठा hisi_sas_dq *dq = शून्य;

	अगर (!sas_port) अणु
		काष्ठा task_status_काष्ठा *ts = &task->task_status;

		ts->resp = SAS_TASK_UNDELIVERED;
		ts->stat = SAS_PHY_DOWN;
		/*
		 * libsas will use dev->port, should
		 * not call task_करोne क्रम sata
		 */
		अगर (device->dev_type != SAS_SATA_DEV)
			task->task_करोne(task);
		वापस -ECOMM;
	पूर्ण

	hisi_hba = dev_to_hisi_hba(device);
	dev = hisi_hba->dev;

	अगर (unlikely(test_bit(HISI_SAS_REJECT_CMD_BIT, &hisi_hba->flags))) अणु
		अगर (!gfpflags_allow_blocking(gfp_flags))
			वापस -EINVAL;

		करोwn(&hisi_hba->sem);
		up(&hisi_hba->sem);
	पूर्ण

	/* protect task_prep and start_delivery sequence */
	rc = hisi_sas_task_prep(task, &dq, is_पंचांगf, पंचांगf, &pass);
	अगर (rc)
		dev_err(dev, "task exec: failed[%d]!\n", rc);

	अगर (likely(pass)) अणु
		spin_lock(&dq->lock);
		hisi_hba->hw->start_delivery(dq);
		spin_unlock(&dq->lock);
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम hisi_sas_bytes_dmaed(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no,
				 gfp_t gfp_flags)
अणु
	काष्ठा hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
	काष्ठा asd_sas_phy *sas_phy = &phy->sas_phy;

	अगर (!phy->phy_attached)
		वापस;

	अगर (test_bit(HISI_SAS_PM_BIT, &hisi_hba->flags) &&
	    !sas_phy->suspended) अणु
		dev_warn(hisi_hba->dev, "phy%d during suspend filtered out\n", phy_no);
		वापस;
	पूर्ण

	sas_notअगरy_phy_event(sas_phy, PHYE_OOB_DONE, gfp_flags);

	अगर (sas_phy->phy) अणु
		काष्ठा sas_phy *sphy = sas_phy->phy;

		sphy->negotiated_linkrate = sas_phy->linkrate;
		sphy->minimum_linkrate_hw = SAS_LINK_RATE_1_5_GBPS;
		sphy->maximum_linkrate_hw =
			hisi_hba->hw->phy_get_max_linkrate();
		अगर (sphy->minimum_linkrate == SAS_LINK_RATE_UNKNOWN)
			sphy->minimum_linkrate = phy->minimum_linkrate;

		अगर (sphy->maximum_linkrate == SAS_LINK_RATE_UNKNOWN)
			sphy->maximum_linkrate = phy->maximum_linkrate;
	पूर्ण

	अगर (phy->phy_type & PORT_TYPE_SAS) अणु
		काष्ठा sas_identअगरy_frame *id;

		id = (काष्ठा sas_identअगरy_frame *)phy->frame_rcvd;
		id->dev_type = phy->identअगरy.device_type;
		id->initiator_bits = SAS_PROTOCOL_ALL;
		id->target_bits = phy->identअगरy.target_port_protocols;
	पूर्ण अन्यथा अगर (phy->phy_type & PORT_TYPE_SATA) अणु
		/* Nothing */
	पूर्ण

	sas_phy->frame_rcvd_size = phy->frame_rcvd_size;
	sas_notअगरy_port_event(sas_phy, PORTE_BYTES_DMAED, gfp_flags);
पूर्ण

अटल काष्ठा hisi_sas_device *hisi_sas_alloc_dev(काष्ठा करोमुख्य_device *device)
अणु
	काष्ठा hisi_hba *hisi_hba = dev_to_hisi_hba(device);
	काष्ठा hisi_sas_device *sas_dev = शून्य;
	पूर्णांक last = hisi_hba->last_dev_id;
	पूर्णांक first = (hisi_hba->last_dev_id + 1) % HISI_SAS_MAX_DEVICES;
	पूर्णांक i;

	spin_lock(&hisi_hba->lock);
	क्रम (i = first; i != last; i %= HISI_SAS_MAX_DEVICES) अणु
		अगर (hisi_hba->devices[i].dev_type == SAS_PHY_UNUSED) अणु
			पूर्णांक queue = i % hisi_hba->queue_count;
			काष्ठा hisi_sas_dq *dq = &hisi_hba->dq[queue];

			hisi_hba->devices[i].device_id = i;
			sas_dev = &hisi_hba->devices[i];
			sas_dev->dev_status = HISI_SAS_DEV_INIT;
			sas_dev->dev_type = device->dev_type;
			sas_dev->hisi_hba = hisi_hba;
			sas_dev->sas_device = device;
			sas_dev->dq = dq;
			spin_lock_init(&sas_dev->lock);
			INIT_LIST_HEAD(&hisi_hba->devices[i].list);
			अवरोध;
		पूर्ण
		i++;
	पूर्ण
	hisi_hba->last_dev_id = i;
	spin_unlock(&hisi_hba->lock);

	वापस sas_dev;
पूर्ण

#घोषणा HISI_SAS_DISK_RECOVER_CNT 3
अटल पूर्णांक hisi_sas_init_device(काष्ठा करोमुख्य_device *device)
अणु
	पूर्णांक rc = TMF_RESP_FUNC_COMPLETE;
	काष्ठा scsi_lun lun;
	काष्ठा hisi_sas_पंचांगf_task पंचांगf_task;
	पूर्णांक retry = HISI_SAS_DISK_RECOVER_CNT;
	काष्ठा hisi_hba *hisi_hba = dev_to_hisi_hba(device);
	काष्ठा device *dev = hisi_hba->dev;
	काष्ठा sas_phy *local_phy;

	चयन (device->dev_type) अणु
	हाल SAS_END_DEVICE:
		पूर्णांक_to_scsilun(0, &lun);

		पंचांगf_task.पंचांगf = TMF_CLEAR_TASK_SET;
		जबतक (retry-- > 0) अणु
			rc = hisi_sas_debug_issue_ssp_पंचांगf(device, lun.scsi_lun,
							  &पंचांगf_task);
			अगर (rc == TMF_RESP_FUNC_COMPLETE) अणु
				hisi_sas_release_task(hisi_hba, device);
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल SAS_SATA_DEV:
	हाल SAS_SATA_PM:
	हाल SAS_SATA_PM_PORT:
	हाल SAS_SATA_PENDING:
		/*
		 * send HARD RESET to clear previous affiliation of
		 * STP target port
		 */
		local_phy = sas_get_local_phy(device);
		अगर (!scsi_is_sas_phy_local(local_phy) &&
		    !test_bit(HISI_SAS_RESET_BIT, &hisi_hba->flags)) अणु
			अचिन्हित दीर्घ deadline = ata_deadline(jअगरfies, 20000);
			काष्ठा sata_device *sata_dev = &device->sata_dev;
			काष्ठा ata_host *ata_host = sata_dev->ata_host;
			काष्ठा ata_port_operations *ops = ata_host->ops;
			काष्ठा ata_port *ap = sata_dev->ap;
			काष्ठा ata_link *link;
			अचिन्हित पूर्णांक classes;

			ata_क्रम_each_link(link, ap, EDGE)
				rc = ops->hardreset(link, &classes,
						    deadline);
		पूर्ण
		sas_put_local_phy(local_phy);
		अगर (rc) अणु
			dev_warn(dev, "SATA disk hardreset fail: %d\n", rc);
			वापस rc;
		पूर्ण

		जबतक (retry-- > 0) अणु
			rc = hisi_sas_softreset_ata_disk(device);
			अगर (!rc)
				अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक hisi_sas_dev_found(काष्ठा करोमुख्य_device *device)
अणु
	काष्ठा hisi_hba *hisi_hba = dev_to_hisi_hba(device);
	काष्ठा करोमुख्य_device *parent_dev = device->parent;
	काष्ठा hisi_sas_device *sas_dev;
	काष्ठा device *dev = hisi_hba->dev;
	पूर्णांक rc;

	अगर (hisi_hba->hw->alloc_dev)
		sas_dev = hisi_hba->hw->alloc_dev(device);
	अन्यथा
		sas_dev = hisi_sas_alloc_dev(device);
	अगर (!sas_dev) अणु
		dev_err(dev, "fail alloc dev: max support %d devices\n",
			HISI_SAS_MAX_DEVICES);
		वापस -EINVAL;
	पूर्ण

	device->lldd_dev = sas_dev;
	hisi_hba->hw->setup_itct(hisi_hba, sas_dev);

	अगर (parent_dev && dev_is_expander(parent_dev->dev_type)) अणु
		पूर्णांक phy_no;
		u8 phy_num = parent_dev->ex_dev.num_phys;
		काष्ठा ex_phy *phy;

		क्रम (phy_no = 0; phy_no < phy_num; phy_no++) अणु
			phy = &parent_dev->ex_dev.ex_phy[phy_no];
			अगर (SAS_ADDR(phy->attached_sas_addr) ==
				SAS_ADDR(device->sas_addr))
				अवरोध;
		पूर्ण

		अगर (phy_no == phy_num) अणु
			dev_info(dev, "dev found: no attached "
				 "dev:%016llx at ex:%016llx\n",
				 SAS_ADDR(device->sas_addr),
				 SAS_ADDR(parent_dev->sas_addr));
			rc = -EINVAL;
			जाओ err_out;
		पूर्ण
	पूर्ण

	dev_info(dev, "dev[%d:%x] found\n",
		sas_dev->device_id, sas_dev->dev_type);

	rc = hisi_sas_init_device(device);
	अगर (rc)
		जाओ err_out;
	sas_dev->dev_status = HISI_SAS_DEV_NORMAL;
	वापस 0;

err_out:
	hisi_sas_dev_gone(device);
	वापस rc;
पूर्ण

पूर्णांक hisi_sas_slave_configure(काष्ठा scsi_device *sdev)
अणु
	काष्ठा करोमुख्य_device *dev = sdev_to_करोमुख्य_dev(sdev);
	पूर्णांक ret = sas_slave_configure(sdev);

	अगर (ret)
		वापस ret;
	अगर (!dev_is_sata(dev))
		sas_change_queue_depth(sdev, 64);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hisi_sas_slave_configure);

व्योम hisi_sas_scan_start(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा hisi_hba *hisi_hba = shost_priv(shost);

	hisi_hba->hw->phys_init(hisi_hba);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_sas_scan_start);

पूर्णांक hisi_sas_scan_finished(काष्ठा Scsi_Host *shost, अचिन्हित दीर्घ समय)
अणु
	काष्ठा hisi_hba *hisi_hba = shost_priv(shost);
	काष्ठा sas_ha_काष्ठा *sha = &hisi_hba->sha;

	/* Wait क्रम PHY up पूर्णांकerrupt to occur */
	अगर (समय < HZ)
		वापस 0;

	sas_drain_work(sha);
	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(hisi_sas_scan_finished);

अटल व्योम hisi_sas_phyup_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hisi_sas_phy *phy =
		container_of(work, typeof(*phy), works[HISI_PHYE_PHY_UP]);
	काष्ठा hisi_hba *hisi_hba = phy->hisi_hba;
	काष्ठा asd_sas_phy *sas_phy = &phy->sas_phy;
	पूर्णांक phy_no = sas_phy->id;

	अगर (phy->identअगरy.target_port_protocols == SAS_PROTOCOL_SSP)
		hisi_hba->hw->sl_notअगरy_ssp(hisi_hba, phy_no);
	hisi_sas_bytes_dmaed(hisi_hba, phy_no, GFP_KERNEL);
पूर्ण

अटल व्योम hisi_sas_linkreset_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hisi_sas_phy *phy =
		container_of(work, typeof(*phy), works[HISI_PHYE_LINK_RESET]);
	काष्ठा asd_sas_phy *sas_phy = &phy->sas_phy;

	hisi_sas_control_phy(sas_phy, PHY_FUNC_LINK_RESET, शून्य);
पूर्ण

अटल स्थिर work_func_t hisi_sas_phye_fns[HISI_PHYES_NUM] = अणु
	[HISI_PHYE_PHY_UP] = hisi_sas_phyup_work,
	[HISI_PHYE_LINK_RESET] = hisi_sas_linkreset_work,
पूर्ण;

bool hisi_sas_notअगरy_phy_event(काष्ठा hisi_sas_phy *phy,
				क्रमागत hisi_sas_phy_event event)
अणु
	काष्ठा hisi_hba *hisi_hba = phy->hisi_hba;

	अगर (WARN_ON(event >= HISI_PHYES_NUM))
		वापस false;

	वापस queue_work(hisi_hba->wq, &phy->works[event]);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_sas_notअगरy_phy_event);

अटल व्योम hisi_sas_रुको_phyup_समयकरोut(काष्ठा समयr_list *t)
अणु
	काष्ठा hisi_sas_phy *phy = from_समयr(phy, t, समयr);
	काष्ठा hisi_hba *hisi_hba = phy->hisi_hba;
	काष्ठा device *dev = hisi_hba->dev;
	पूर्णांक phy_no = phy->sas_phy.id;

	dev_warn(dev, "phy%d wait phyup timeout, issuing link reset\n", phy_no);
	hisi_sas_notअगरy_phy_event(phy, HISI_PHYE_LINK_RESET);
पूर्ण

व्योम hisi_sas_phy_oob_पढ़ोy(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no)
अणु
	काष्ठा hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
	काष्ठा device *dev = hisi_hba->dev;

	dev_dbg(dev, "phy%d OOB ready\n", phy_no);
	अगर (phy->phy_attached)
		वापस;

	अगर (!समयr_pending(&phy->समयr)) अणु
		phy->समयr.expires = jअगरfies + HISI_SAS_WAIT_PHYUP_TIMEOUT * HZ;
		add_समयr(&phy->समयr);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(hisi_sas_phy_oob_पढ़ोy);

अटल व्योम hisi_sas_phy_init(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no)
अणु
	काष्ठा hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
	काष्ठा asd_sas_phy *sas_phy = &phy->sas_phy;
	पूर्णांक i;

	phy->hisi_hba = hisi_hba;
	phy->port = शून्य;
	phy->minimum_linkrate = SAS_LINK_RATE_1_5_GBPS;
	phy->maximum_linkrate = hisi_hba->hw->phy_get_max_linkrate();
	sas_phy->enabled = (phy_no < hisi_hba->n_phy) ? 1 : 0;
	sas_phy->class = SAS;
	sas_phy->iproto = SAS_PROTOCOL_ALL;
	sas_phy->tproto = 0;
	sas_phy->type = PHY_TYPE_PHYSICAL;
	sas_phy->role = PHY_ROLE_INITIATOR;
	sas_phy->oob_mode = OOB_NOT_CONNECTED;
	sas_phy->linkrate = SAS_LINK_RATE_UNKNOWN;
	sas_phy->id = phy_no;
	sas_phy->sas_addr = &hisi_hba->sas_addr[0];
	sas_phy->frame_rcvd = &phy->frame_rcvd[0];
	sas_phy->ha = (काष्ठा sas_ha_काष्ठा *)hisi_hba->shost->hostdata;
	sas_phy->lldd_phy = phy;

	क्रम (i = 0; i < HISI_PHYES_NUM; i++)
		INIT_WORK(&phy->works[i], hisi_sas_phye_fns[i]);

	spin_lock_init(&phy->lock);

	समयr_setup(&phy->समयr, hisi_sas_रुको_phyup_समयकरोut, 0);
पूर्ण

/* Wrapper to ensure we track hisi_sas_phy.enable properly */
व्योम hisi_sas_phy_enable(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no, पूर्णांक enable)
अणु
	काष्ठा hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
	काष्ठा asd_sas_phy *aphy = &phy->sas_phy;
	काष्ठा sas_phy *sphy = aphy->phy;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&phy->lock, flags);

	अगर (enable) अणु
		/* We may have been enabled alपढ़ोy; अगर so, करोn't touch */
		अगर (!phy->enable)
			sphy->negotiated_linkrate = SAS_LINK_RATE_UNKNOWN;
		hisi_hba->hw->phy_start(hisi_hba, phy_no);
	पूर्ण अन्यथा अणु
		sphy->negotiated_linkrate = SAS_PHY_DISABLED;
		hisi_hba->hw->phy_disable(hisi_hba, phy_no);
	पूर्ण
	phy->enable = enable;
	spin_unlock_irqrestore(&phy->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_sas_phy_enable);

अटल व्योम hisi_sas_port_notअगरy_क्रमmed(काष्ठा asd_sas_phy *sas_phy)
अणु
	काष्ठा sas_ha_काष्ठा *sas_ha = sas_phy->ha;
	काष्ठा hisi_hba *hisi_hba = sas_ha->lldd_ha;
	काष्ठा hisi_sas_phy *phy = sas_phy->lldd_phy;
	काष्ठा asd_sas_port *sas_port = sas_phy->port;
	काष्ठा hisi_sas_port *port;
	अचिन्हित दीर्घ flags;

	अगर (!sas_port)
		वापस;

	port = to_hisi_sas_port(sas_port);
	spin_lock_irqsave(&hisi_hba->lock, flags);
	port->port_attached = 1;
	port->id = phy->port_id;
	phy->port = port;
	sas_port->lldd_port = port;
	spin_unlock_irqrestore(&hisi_hba->lock, flags);
पूर्ण

अटल व्योम hisi_sas_करो_release_task(काष्ठा hisi_hba *hisi_hba, काष्ठा sas_task *task,
				     काष्ठा hisi_sas_slot *slot)
अणु
	अगर (task) अणु
		अचिन्हित दीर्घ flags;
		काष्ठा task_status_काष्ठा *ts;

		ts = &task->task_status;

		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_ABORTED_TASK;
		spin_lock_irqsave(&task->task_state_lock, flags);
		task->task_state_flags &=
			~(SAS_TASK_STATE_PENDING | SAS_TASK_AT_INITIATOR);
		अगर (!slot->is_पूर्णांकernal && task->task_proto != SAS_PROTOCOL_SMP)
			task->task_state_flags |= SAS_TASK_STATE_DONE;
		spin_unlock_irqrestore(&task->task_state_lock, flags);
	पूर्ण

	hisi_sas_slot_task_मुक्त(hisi_hba, task, slot);
पूर्ण

अटल व्योम hisi_sas_release_task(काष्ठा hisi_hba *hisi_hba,
			काष्ठा करोमुख्य_device *device)
अणु
	काष्ठा hisi_sas_slot *slot, *slot2;
	काष्ठा hisi_sas_device *sas_dev = device->lldd_dev;

	list_क्रम_each_entry_safe(slot, slot2, &sas_dev->list, entry)
		hisi_sas_करो_release_task(hisi_hba, slot->task, slot);
पूर्ण

व्योम hisi_sas_release_tasks(काष्ठा hisi_hba *hisi_hba)
अणु
	काष्ठा hisi_sas_device *sas_dev;
	काष्ठा करोमुख्य_device *device;
	पूर्णांक i;

	क्रम (i = 0; i < HISI_SAS_MAX_DEVICES; i++) अणु
		sas_dev = &hisi_hba->devices[i];
		device = sas_dev->sas_device;

		अगर ((sas_dev->dev_type == SAS_PHY_UNUSED) ||
		    !device)
			जारी;

		hisi_sas_release_task(hisi_hba, device);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(hisi_sas_release_tasks);

अटल व्योम hisi_sas_dereg_device(काष्ठा hisi_hba *hisi_hba,
				काष्ठा करोमुख्य_device *device)
अणु
	अगर (hisi_hba->hw->dereg_device)
		hisi_hba->hw->dereg_device(hisi_hba, device);
पूर्ण

अटल व्योम hisi_sas_dev_gone(काष्ठा करोमुख्य_device *device)
अणु
	काष्ठा hisi_sas_device *sas_dev = device->lldd_dev;
	काष्ठा hisi_hba *hisi_hba = dev_to_hisi_hba(device);
	काष्ठा device *dev = hisi_hba->dev;
	पूर्णांक ret = 0;

	dev_info(dev, "dev[%d:%x] is gone\n",
		 sas_dev->device_id, sas_dev->dev_type);

	करोwn(&hisi_hba->sem);
	अगर (!test_bit(HISI_SAS_RESET_BIT, &hisi_hba->flags)) अणु
		hisi_sas_पूर्णांकernal_task_पात(hisi_hba, device,
					     HISI_SAS_INT_ABT_DEV, 0);

		hisi_sas_dereg_device(hisi_hba, device);

		ret = hisi_hba->hw->clear_itct(hisi_hba, sas_dev);
		device->lldd_dev = शून्य;
	पूर्ण

	अगर (hisi_hba->hw->मुक्त_device)
		hisi_hba->hw->मुक्त_device(sas_dev);

	/* Don't mark it as SAS_PHY_UNUSED अगर failed to clear ITCT */
	अगर (!ret)
		sas_dev->dev_type = SAS_PHY_UNUSED;
	sas_dev->sas_device = शून्य;
	up(&hisi_hba->sem);
पूर्ण

अटल पूर्णांक hisi_sas_queue_command(काष्ठा sas_task *task, gfp_t gfp_flags)
अणु
	वापस hisi_sas_task_exec(task, gfp_flags, 0, शून्य);
पूर्ण

अटल पूर्णांक hisi_sas_phy_set_linkrate(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no,
			काष्ठा sas_phy_linkrates *r)
अणु
	काष्ठा sas_phy_linkrates _r;

	काष्ठा hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
	काष्ठा asd_sas_phy *sas_phy = &phy->sas_phy;
	क्रमागत sas_linkrate min, max;

	अगर (r->minimum_linkrate > SAS_LINK_RATE_1_5_GBPS)
		वापस -EINVAL;

	अगर (r->maximum_linkrate == SAS_LINK_RATE_UNKNOWN) अणु
		max = sas_phy->phy->maximum_linkrate;
		min = r->minimum_linkrate;
	पूर्ण अन्यथा अगर (r->minimum_linkrate == SAS_LINK_RATE_UNKNOWN) अणु
		max = r->maximum_linkrate;
		min = sas_phy->phy->minimum_linkrate;
	पूर्ण अन्यथा
		वापस -EINVAL;

	_r.maximum_linkrate = max;
	_r.minimum_linkrate = min;

	sas_phy->phy->maximum_linkrate = max;
	sas_phy->phy->minimum_linkrate = min;

	hisi_sas_phy_enable(hisi_hba, phy_no, 0);
	msleep(100);
	hisi_hba->hw->phy_set_linkrate(hisi_hba, phy_no, &_r);
	hisi_sas_phy_enable(hisi_hba, phy_no, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक hisi_sas_control_phy(काष्ठा asd_sas_phy *sas_phy, क्रमागत phy_func func,
				व्योम *funcdata)
अणु
	काष्ठा sas_ha_काष्ठा *sas_ha = sas_phy->ha;
	काष्ठा hisi_hba *hisi_hba = sas_ha->lldd_ha;
	पूर्णांक phy_no = sas_phy->id;

	चयन (func) अणु
	हाल PHY_FUNC_HARD_RESET:
		hisi_hba->hw->phy_hard_reset(hisi_hba, phy_no);
		अवरोध;

	हाल PHY_FUNC_LINK_RESET:
		hisi_sas_phy_enable(hisi_hba, phy_no, 0);
		msleep(100);
		hisi_sas_phy_enable(hisi_hba, phy_no, 1);
		अवरोध;

	हाल PHY_FUNC_DISABLE:
		hisi_sas_phy_enable(hisi_hba, phy_no, 0);
		अवरोध;

	हाल PHY_FUNC_SET_LINK_RATE:
		वापस hisi_sas_phy_set_linkrate(hisi_hba, phy_no, funcdata);
	हाल PHY_FUNC_GET_EVENTS:
		अगर (hisi_hba->hw->get_events) अणु
			hisi_hba->hw->get_events(hisi_hba, phy_no);
			अवरोध;
		पूर्ण
		fallthrough;
	हाल PHY_FUNC_RELEASE_SPINUP_HOLD:
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम hisi_sas_task_करोne(काष्ठा sas_task *task)
अणु
	del_समयr(&task->slow_task->समयr);
	complete(&task->slow_task->completion);
पूर्ण

अटल व्योम hisi_sas_पंचांगf_समयकरोut(काष्ठा समयr_list *t)
अणु
	काष्ठा sas_task_slow *slow = from_समयr(slow, t, समयr);
	काष्ठा sas_task *task = slow->task;
	अचिन्हित दीर्घ flags;
	bool is_completed = true;

	spin_lock_irqsave(&task->task_state_lock, flags);
	अगर (!(task->task_state_flags & SAS_TASK_STATE_DONE)) अणु
		task->task_state_flags |= SAS_TASK_STATE_ABORTED;
		is_completed = false;
	पूर्ण
	spin_unlock_irqrestore(&task->task_state_lock, flags);

	अगर (!is_completed)
		complete(&task->slow_task->completion);
पूर्ण

#घोषणा TASK_TIMEOUT 20
#घोषणा TASK_RETRY 3
#घोषणा INTERNAL_ABORT_TIMEOUT 6
अटल पूर्णांक hisi_sas_exec_पूर्णांकernal_पंचांगf_task(काष्ठा करोमुख्य_device *device,
					   व्योम *parameter, u32 para_len,
					   काष्ठा hisi_sas_पंचांगf_task *पंचांगf)
अणु
	काष्ठा hisi_sas_device *sas_dev = device->lldd_dev;
	काष्ठा hisi_hba *hisi_hba = sas_dev->hisi_hba;
	काष्ठा device *dev = hisi_hba->dev;
	काष्ठा sas_task *task;
	पूर्णांक res, retry;

	क्रम (retry = 0; retry < TASK_RETRY; retry++) अणु
		task = sas_alloc_slow_task(GFP_KERNEL);
		अगर (!task)
			वापस -ENOMEM;

		task->dev = device;
		task->task_proto = device->tproto;

		अगर (dev_is_sata(device)) अणु
			task->ata_task.device_control_reg_update = 1;
			स_नकल(&task->ata_task.fis, parameter, para_len);
		पूर्ण अन्यथा अणु
			स_नकल(&task->ssp_task, parameter, para_len);
		पूर्ण
		task->task_करोne = hisi_sas_task_करोne;

		task->slow_task->समयr.function = hisi_sas_पंचांगf_समयकरोut;
		task->slow_task->समयr.expires = jअगरfies + TASK_TIMEOUT * HZ;
		add_समयr(&task->slow_task->समयr);

		res = hisi_sas_task_exec(task, GFP_KERNEL, 1, पंचांगf);

		अगर (res) अणु
			del_समयr(&task->slow_task->समयr);
			dev_err(dev, "abort tmf: executing internal task failed: %d\n",
				res);
			जाओ ex_err;
		पूर्ण

		रुको_क्रम_completion(&task->slow_task->completion);
		res = TMF_RESP_FUNC_FAILED;
		/* Even TMF समयd out, वापस direct. */
		अगर ((task->task_state_flags & SAS_TASK_STATE_ABORTED)) अणु
			अगर (!(task->task_state_flags & SAS_TASK_STATE_DONE)) अणु
				काष्ठा hisi_sas_slot *slot = task->lldd_task;

				dev_err(dev, "abort tmf: TMF task timeout and not done\n");
				अगर (slot) अणु
					काष्ठा hisi_sas_cq *cq =
					       &hisi_hba->cq[slot->dlvry_queue];
					/*
					 * sync irq to aव्योम मुक्त'ing task
					 * beक्रमe using task in IO completion
					 */
					synchronize_irq(cq->irq_no);
					slot->task = शून्य;
				पूर्ण

				जाओ ex_err;
			पूर्ण अन्यथा
				dev_err(dev, "abort tmf: TMF task timeout\n");
		पूर्ण

		अगर (task->task_status.resp == SAS_TASK_COMPLETE &&
		     task->task_status.stat == TMF_RESP_FUNC_COMPLETE) अणु
			res = TMF_RESP_FUNC_COMPLETE;
			अवरोध;
		पूर्ण

		अगर (task->task_status.resp == SAS_TASK_COMPLETE &&
			task->task_status.stat == TMF_RESP_FUNC_SUCC) अणु
			res = TMF_RESP_FUNC_SUCC;
			अवरोध;
		पूर्ण

		अगर (task->task_status.resp == SAS_TASK_COMPLETE &&
		      task->task_status.stat == SAS_DATA_UNDERRUN) अणु
			/* no error, but वापस the number of bytes of
			 * underrun
			 */
			dev_warn(dev, "abort tmf: task to dev %016llx resp: 0x%x sts 0x%x underrun\n",
				 SAS_ADDR(device->sas_addr),
				 task->task_status.resp,
				 task->task_status.stat);
			res = task->task_status.residual;
			अवरोध;
		पूर्ण

		अगर (task->task_status.resp == SAS_TASK_COMPLETE &&
			task->task_status.stat == SAS_DATA_OVERRUN) अणु
			dev_warn(dev, "abort tmf: blocked task error\n");
			res = -EMSGSIZE;
			अवरोध;
		पूर्ण

		अगर (task->task_status.resp == SAS_TASK_COMPLETE &&
		    task->task_status.stat == SAS_OPEN_REJECT) अणु
			dev_warn(dev, "abort tmf: open reject failed\n");
			res = -EIO;
		पूर्ण अन्यथा अणु
			dev_warn(dev, "abort tmf: task to dev %016llx resp: 0x%x status 0x%x\n",
				 SAS_ADDR(device->sas_addr),
				 task->task_status.resp,
				 task->task_status.stat);
		पूर्ण
		sas_मुक्त_task(task);
		task = शून्य;
	पूर्ण
ex_err:
	अगर (retry == TASK_RETRY)
		dev_warn(dev, "abort tmf: executing internal task failed!\n");
	sas_मुक्त_task(task);
	वापस res;
पूर्ण

अटल व्योम hisi_sas_fill_ata_reset_cmd(काष्ठा ata_device *dev,
		bool reset, पूर्णांक pmp, u8 *fis)
अणु
	काष्ठा ata_taskfile tf;

	ata_tf_init(dev, &tf);
	अगर (reset)
		tf.ctl |= ATA_SRST;
	अन्यथा
		tf.ctl &= ~ATA_SRST;
	tf.command = ATA_CMD_DEV_RESET;
	ata_tf_to_fis(&tf, pmp, 0, fis);
पूर्ण

अटल पूर्णांक hisi_sas_softreset_ata_disk(काष्ठा करोमुख्य_device *device)
अणु
	u8 fis[20] = अणु0पूर्ण;
	काष्ठा ata_port *ap = device->sata_dev.ap;
	काष्ठा ata_link *link;
	पूर्णांक rc = TMF_RESP_FUNC_FAILED;
	काष्ठा hisi_hba *hisi_hba = dev_to_hisi_hba(device);
	काष्ठा device *dev = hisi_hba->dev;
	पूर्णांक s = माप(काष्ठा host_to_dev_fis);

	ata_क्रम_each_link(link, ap, EDGE) अणु
		पूर्णांक pmp = sata_srst_pmp(link);

		hisi_sas_fill_ata_reset_cmd(link->device, 1, pmp, fis);
		rc = hisi_sas_exec_पूर्णांकernal_पंचांगf_task(device, fis, s, शून्य);
		अगर (rc != TMF_RESP_FUNC_COMPLETE)
			अवरोध;
	पूर्ण

	अगर (rc == TMF_RESP_FUNC_COMPLETE) अणु
		ata_क्रम_each_link(link, ap, EDGE) अणु
			पूर्णांक pmp = sata_srst_pmp(link);

			hisi_sas_fill_ata_reset_cmd(link->device, 0, pmp, fis);
			rc = hisi_sas_exec_पूर्णांकernal_पंचांगf_task(device, fis,
							     s, शून्य);
			अगर (rc != TMF_RESP_FUNC_COMPLETE)
				dev_err(dev, "ata disk %016llx de-reset failed\n",
					SAS_ADDR(device->sas_addr));
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(dev, "ata disk %016llx reset failed\n",
			SAS_ADDR(device->sas_addr));
	पूर्ण

	अगर (rc == TMF_RESP_FUNC_COMPLETE)
		hisi_sas_release_task(hisi_hba, device);

	वापस rc;
पूर्ण

अटल पूर्णांक hisi_sas_debug_issue_ssp_पंचांगf(काष्ठा करोमुख्य_device *device,
				u8 *lun, काष्ठा hisi_sas_पंचांगf_task *पंचांगf)
अणु
	काष्ठा sas_ssp_task ssp_task;

	अगर (!(device->tproto & SAS_PROTOCOL_SSP))
		वापस TMF_RESP_FUNC_ESUPP;

	स_नकल(ssp_task.LUN, lun, 8);

	वापस hisi_sas_exec_पूर्णांकernal_पंचांगf_task(device, &ssp_task,
				माप(ssp_task), पंचांगf);
पूर्ण

अटल व्योम hisi_sas_refresh_port_id(काष्ठा hisi_hba *hisi_hba)
अणु
	u32 state = hisi_hba->hw->get_phys_state(hisi_hba);
	पूर्णांक i;

	क्रम (i = 0; i < HISI_SAS_MAX_DEVICES; i++) अणु
		काष्ठा hisi_sas_device *sas_dev = &hisi_hba->devices[i];
		काष्ठा करोमुख्य_device *device = sas_dev->sas_device;
		काष्ठा asd_sas_port *sas_port;
		काष्ठा hisi_sas_port *port;
		काष्ठा hisi_sas_phy *phy = शून्य;
		काष्ठा asd_sas_phy *sas_phy;

		अगर ((sas_dev->dev_type == SAS_PHY_UNUSED)
				|| !device || !device->port)
			जारी;

		sas_port = device->port;
		port = to_hisi_sas_port(sas_port);

		list_क्रम_each_entry(sas_phy, &sas_port->phy_list, port_phy_el)
			अगर (state & BIT(sas_phy->id)) अणु
				phy = sas_phy->lldd_phy;
				अवरोध;
			पूर्ण

		अगर (phy) अणु
			port->id = phy->port_id;

			/* Update linkrate of directly attached device. */
			अगर (!device->parent)
				device->linkrate = phy->sas_phy.linkrate;

			hisi_hba->hw->setup_itct(hisi_hba, sas_dev);
		पूर्ण अन्यथा
			port->id = 0xff;
	पूर्ण
पूर्ण

अटल व्योम hisi_sas_rescan_topology(काष्ठा hisi_hba *hisi_hba, u32 state)
अणु
	काष्ठा asd_sas_port *_sas_port = शून्य;
	पूर्णांक phy_no;

	क्रम (phy_no = 0; phy_no < hisi_hba->n_phy; phy_no++) अणु
		काष्ठा hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
		काष्ठा asd_sas_phy *sas_phy = &phy->sas_phy;
		काष्ठा asd_sas_port *sas_port = sas_phy->port;
		bool करो_port_check = _sas_port != sas_port;

		अगर (!sas_phy->phy->enabled)
			जारी;

		/* Report PHY state change to libsas */
		अगर (state & BIT(phy_no)) अणु
			अगर (करो_port_check && sas_port && sas_port->port_dev) अणु
				काष्ठा करोमुख्य_device *dev = sas_port->port_dev;

				_sas_port = sas_port;

				अगर (dev_is_expander(dev->dev_type))
					sas_notअगरy_port_event(sas_phy,
							PORTE_BROADCAST_RCVD,
							GFP_KERNEL);
			पूर्ण
		पूर्ण अन्यथा अणु
			hisi_sas_phy_करोwn(hisi_hba, phy_no, 0, GFP_KERNEL);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम hisi_sas_reset_init_all_devices(काष्ठा hisi_hba *hisi_hba)
अणु
	काष्ठा hisi_sas_device *sas_dev;
	काष्ठा करोमुख्य_device *device;
	पूर्णांक i;

	क्रम (i = 0; i < HISI_SAS_MAX_DEVICES; i++) अणु
		sas_dev = &hisi_hba->devices[i];
		device = sas_dev->sas_device;

		अगर ((sas_dev->dev_type == SAS_PHY_UNUSED) || !device)
			जारी;

		hisi_sas_init_device(device);
	पूर्ण
पूर्ण

अटल व्योम hisi_sas_send_ata_reset_each_phy(काष्ठा hisi_hba *hisi_hba,
					     काष्ठा asd_sas_port *sas_port,
					     काष्ठा करोमुख्य_device *device)
अणु
	काष्ठा hisi_sas_पंचांगf_task पंचांगf_task = अणु .क्रमce_phy = 1 पूर्ण;
	काष्ठा ata_port *ap = device->sata_dev.ap;
	काष्ठा device *dev = hisi_hba->dev;
	पूर्णांक s = माप(काष्ठा host_to_dev_fis);
	पूर्णांक rc = TMF_RESP_FUNC_FAILED;
	काष्ठा asd_sas_phy *sas_phy;
	काष्ठा ata_link *link;
	u8 fis[20] = अणु0पूर्ण;
	u32 state;

	state = hisi_hba->hw->get_phys_state(hisi_hba);
	list_क्रम_each_entry(sas_phy, &sas_port->phy_list, port_phy_el) अणु
		अगर (!(state & BIT(sas_phy->id)))
			जारी;

		ata_क्रम_each_link(link, ap, EDGE) अणु
			पूर्णांक pmp = sata_srst_pmp(link);

			पंचांगf_task.phy_id = sas_phy->id;
			hisi_sas_fill_ata_reset_cmd(link->device, 1, pmp, fis);
			rc = hisi_sas_exec_पूर्णांकernal_पंचांगf_task(device, fis, s,
							     &पंचांगf_task);
			अगर (rc != TMF_RESP_FUNC_COMPLETE) अणु
				dev_err(dev, "phy%d ata reset failed rc=%d\n",
					sas_phy->id, rc);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम hisi_sas_terminate_stp_reject(काष्ठा hisi_hba *hisi_hba)
अणु
	काष्ठा device *dev = hisi_hba->dev;
	पूर्णांक port_no, rc, i;

	क्रम (i = 0; i < HISI_SAS_MAX_DEVICES; i++) अणु
		काष्ठा hisi_sas_device *sas_dev = &hisi_hba->devices[i];
		काष्ठा करोमुख्य_device *device = sas_dev->sas_device;

		अगर ((sas_dev->dev_type == SAS_PHY_UNUSED) || !device)
			जारी;

		rc = hisi_sas_पूर्णांकernal_task_पात(hisi_hba, device,
						  HISI_SAS_INT_ABT_DEV, 0);
		अगर (rc < 0)
			dev_err(dev, "STP reject: abort dev failed %d\n", rc);
	पूर्ण

	क्रम (port_no = 0; port_no < hisi_hba->n_phy; port_no++) अणु
		काष्ठा hisi_sas_port *port = &hisi_hba->port[port_no];
		काष्ठा asd_sas_port *sas_port = &port->sas_port;
		काष्ठा करोमुख्य_device *port_dev = sas_port->port_dev;
		काष्ठा करोमुख्य_device *device;

		अगर (!port_dev || !dev_is_expander(port_dev->dev_type))
			जारी;

		/* Try to find a SATA device */
		list_क्रम_each_entry(device, &sas_port->dev_list,
				    dev_list_node) अणु
			अगर (dev_is_sata(device)) अणु
				hisi_sas_send_ata_reset_each_phy(hisi_hba,
								 sas_port,
								 device);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम hisi_sas_controller_reset_prepare(काष्ठा hisi_hba *hisi_hba)
अणु
	काष्ठा Scsi_Host *shost = hisi_hba->shost;

	करोwn(&hisi_hba->sem);
	hisi_hba->phy_state = hisi_hba->hw->get_phys_state(hisi_hba);

	scsi_block_requests(shost);
	hisi_hba->hw->रुको_cmds_complete_समयout(hisi_hba, 100, 5000);

	अगर (समयr_pending(&hisi_hba->समयr))
		del_समयr_sync(&hisi_hba->समयr);

	set_bit(HISI_SAS_REJECT_CMD_BIT, &hisi_hba->flags);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_sas_controller_reset_prepare);

व्योम hisi_sas_controller_reset_करोne(काष्ठा hisi_hba *hisi_hba)
अणु
	काष्ठा Scsi_Host *shost = hisi_hba->shost;

	/* Init and रुको क्रम PHYs to come up and all libsas event finished. */
	hisi_hba->hw->phys_init(hisi_hba);
	msleep(1000);
	hisi_sas_refresh_port_id(hisi_hba);
	clear_bit(HISI_SAS_REJECT_CMD_BIT, &hisi_hba->flags);

	अगर (hisi_hba->reject_stp_links_msk)
		hisi_sas_terminate_stp_reject(hisi_hba);
	hisi_sas_reset_init_all_devices(hisi_hba);
	up(&hisi_hba->sem);
	scsi_unblock_requests(shost);
	clear_bit(HISI_SAS_RESET_BIT, &hisi_hba->flags);

	hisi_sas_rescan_topology(hisi_hba, hisi_hba->phy_state);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_sas_controller_reset_करोne);

अटल पूर्णांक hisi_sas_controller_prereset(काष्ठा hisi_hba *hisi_hba)
अणु
	अगर (!hisi_hba->hw->soft_reset)
		वापस -1;

	अगर (test_and_set_bit(HISI_SAS_RESET_BIT, &hisi_hba->flags))
		वापस -1;

	अगर (hisi_sas_debugfs_enable && hisi_hba->debugfs_itct[0].itct)
		hisi_hba->hw->debugfs_snapshot_regs(hisi_hba);

	वापस 0;
पूर्ण

अटल पूर्णांक hisi_sas_controller_reset(काष्ठा hisi_hba *hisi_hba)
अणु
	काष्ठा device *dev = hisi_hba->dev;
	काष्ठा Scsi_Host *shost = hisi_hba->shost;
	पूर्णांक rc;

	dev_info(dev, "controller resetting...\n");
	hisi_sas_controller_reset_prepare(hisi_hba);

	rc = hisi_hba->hw->soft_reset(hisi_hba);
	अगर (rc) अणु
		dev_warn(dev, "controller reset failed (%d)\n", rc);
		clear_bit(HISI_SAS_REJECT_CMD_BIT, &hisi_hba->flags);
		up(&hisi_hba->sem);
		scsi_unblock_requests(shost);
		clear_bit(HISI_SAS_RESET_BIT, &hisi_hba->flags);
		वापस rc;
	पूर्ण

	hisi_sas_controller_reset_करोne(hisi_hba);
	dev_info(dev, "controller reset complete\n");

	वापस 0;
पूर्ण

अटल पूर्णांक hisi_sas_पात_task(काष्ठा sas_task *task)
अणु
	काष्ठा scsi_lun lun;
	काष्ठा hisi_sas_पंचांगf_task पंचांगf_task;
	काष्ठा करोमुख्य_device *device = task->dev;
	काष्ठा hisi_sas_device *sas_dev = device->lldd_dev;
	काष्ठा hisi_hba *hisi_hba;
	काष्ठा device *dev;
	पूर्णांक rc = TMF_RESP_FUNC_FAILED;
	अचिन्हित दीर्घ flags;

	अगर (!sas_dev)
		वापस TMF_RESP_FUNC_FAILED;

	hisi_hba = dev_to_hisi_hba(task->dev);
	dev = hisi_hba->dev;

	spin_lock_irqsave(&task->task_state_lock, flags);
	अगर (task->task_state_flags & SAS_TASK_STATE_DONE) अणु
		काष्ठा hisi_sas_slot *slot = task->lldd_task;
		काष्ठा hisi_sas_cq *cq;

		अगर (slot) अणु
			/*
			 * sync irq to aव्योम मुक्त'ing task
			 * beक्रमe using task in IO completion
			 */
			cq = &hisi_hba->cq[slot->dlvry_queue];
			synchronize_irq(cq->irq_no);
		पूर्ण
		spin_unlock_irqrestore(&task->task_state_lock, flags);
		rc = TMF_RESP_FUNC_COMPLETE;
		जाओ out;
	पूर्ण
	task->task_state_flags |= SAS_TASK_STATE_ABORTED;
	spin_unlock_irqrestore(&task->task_state_lock, flags);

	अगर (task->lldd_task && task->task_proto & SAS_PROTOCOL_SSP) अणु
		काष्ठा scsi_cmnd *cmnd = task->uldd_task;
		काष्ठा hisi_sas_slot *slot = task->lldd_task;
		u16 tag = slot->idx;
		पूर्णांक rc2;

		पूर्णांक_to_scsilun(cmnd->device->lun, &lun);
		पंचांगf_task.पंचांगf = TMF_ABORT_TASK;
		पंचांगf_task.tag_of_task_to_be_managed = tag;

		rc = hisi_sas_debug_issue_ssp_पंचांगf(task->dev, lun.scsi_lun,
						  &पंचांगf_task);

		rc2 = hisi_sas_पूर्णांकernal_task_पात(hisi_hba, device,
						   HISI_SAS_INT_ABT_CMD, tag);
		अगर (rc2 < 0) अणु
			dev_err(dev, "abort task: internal abort (%d)\n", rc2);
			वापस TMF_RESP_FUNC_FAILED;
		पूर्ण

		/*
		 * If the TMF finds that the IO is not in the device and also
		 * the पूर्णांकernal पात करोes not succeed, then it is safe to
		 * मुक्त the slot.
		 * Note: अगर the पूर्णांकernal पात succeeds then the slot
		 * will have alपढ़ोy been completed
		 */
		अगर (rc == TMF_RESP_FUNC_COMPLETE && rc2 != TMF_RESP_FUNC_SUCC) अणु
			अगर (task->lldd_task)
				hisi_sas_करो_release_task(hisi_hba, task, slot);
		पूर्ण
	पूर्ण अन्यथा अगर (task->task_proto & SAS_PROTOCOL_SATA ||
		task->task_proto & SAS_PROTOCOL_STP) अणु
		अगर (task->dev->dev_type == SAS_SATA_DEV) अणु
			rc = hisi_sas_पूर्णांकernal_task_पात(hisi_hba, device,
							  HISI_SAS_INT_ABT_DEV,
							  0);
			अगर (rc < 0) अणु
				dev_err(dev, "abort task: internal abort failed\n");
				जाओ out;
			पूर्ण
			hisi_sas_dereg_device(hisi_hba, device);
			rc = hisi_sas_softreset_ata_disk(device);
		पूर्ण
	पूर्ण अन्यथा अगर (task->lldd_task && task->task_proto & SAS_PROTOCOL_SMP) अणु
		/* SMP */
		काष्ठा hisi_sas_slot *slot = task->lldd_task;
		u32 tag = slot->idx;
		काष्ठा hisi_sas_cq *cq = &hisi_hba->cq[slot->dlvry_queue];

		rc = hisi_sas_पूर्णांकernal_task_पात(hisi_hba, device,
						  HISI_SAS_INT_ABT_CMD, tag);
		अगर (((rc < 0) || (rc == TMF_RESP_FUNC_FAILED)) &&
					task->lldd_task) अणु
			/*
			 * sync irq to aव्योम मुक्त'ing task
			 * beक्रमe using task in IO completion
			 */
			synchronize_irq(cq->irq_no);
			slot->task = शून्य;
		पूर्ण
	पूर्ण

out:
	अगर (rc != TMF_RESP_FUNC_COMPLETE)
		dev_notice(dev, "abort task: rc=%d\n", rc);
	वापस rc;
पूर्ण

अटल पूर्णांक hisi_sas_पात_task_set(काष्ठा करोमुख्य_device *device, u8 *lun)
अणु
	काष्ठा hisi_hba *hisi_hba = dev_to_hisi_hba(device);
	काष्ठा device *dev = hisi_hba->dev;
	काष्ठा hisi_sas_पंचांगf_task पंचांगf_task;
	पूर्णांक rc;

	rc = hisi_sas_पूर्णांकernal_task_पात(hisi_hba, device,
					  HISI_SAS_INT_ABT_DEV, 0);
	अगर (rc < 0) अणु
		dev_err(dev, "abort task set: internal abort rc=%d\n", rc);
		वापस TMF_RESP_FUNC_FAILED;
	पूर्ण
	hisi_sas_dereg_device(hisi_hba, device);

	पंचांगf_task.पंचांगf = TMF_ABORT_TASK_SET;
	rc = hisi_sas_debug_issue_ssp_पंचांगf(device, lun, &पंचांगf_task);

	अगर (rc == TMF_RESP_FUNC_COMPLETE)
		hisi_sas_release_task(hisi_hba, device);

	वापस rc;
पूर्ण

अटल पूर्णांक hisi_sas_clear_aca(काष्ठा करोमुख्य_device *device, u8 *lun)
अणु
	काष्ठा hisi_sas_पंचांगf_task पंचांगf_task;
	पूर्णांक rc;

	पंचांगf_task.पंचांगf = TMF_CLEAR_ACA;
	rc = hisi_sas_debug_issue_ssp_पंचांगf(device, lun, &पंचांगf_task);

	वापस rc;
पूर्ण

अटल पूर्णांक hisi_sas_debug_I_T_nexus_reset(काष्ठा करोमुख्य_device *device)
अणु
	काष्ठा sas_phy *local_phy = sas_get_local_phy(device);
	काष्ठा hisi_sas_device *sas_dev = device->lldd_dev;
	काष्ठा hisi_hba *hisi_hba = dev_to_hisi_hba(device);
	काष्ठा sas_ha_काष्ठा *sas_ha = &hisi_hba->sha;
	DECLARE_COMPLETION_ONSTACK(phyreset);
	पूर्णांक rc, reset_type;

	अगर (!local_phy->enabled) अणु
		sas_put_local_phy(local_phy);
		वापस -ENODEV;
	पूर्ण

	अगर (scsi_is_sas_phy_local(local_phy)) अणु
		काष्ठा asd_sas_phy *sas_phy =
			sas_ha->sas_phy[local_phy->number];
		काष्ठा hisi_sas_phy *phy =
			container_of(sas_phy, काष्ठा hisi_sas_phy, sas_phy);
		phy->in_reset = 1;
		phy->reset_completion = &phyreset;
	पूर्ण

	reset_type = (sas_dev->dev_status == HISI_SAS_DEV_INIT ||
		      !dev_is_sata(device)) ? true : false;

	rc = sas_phy_reset(local_phy, reset_type);
	sas_put_local_phy(local_phy);

	अगर (scsi_is_sas_phy_local(local_phy)) अणु
		काष्ठा asd_sas_phy *sas_phy =
			sas_ha->sas_phy[local_phy->number];
		काष्ठा hisi_sas_phy *phy =
			container_of(sas_phy, काष्ठा hisi_sas_phy, sas_phy);
		पूर्णांक ret = रुको_क्रम_completion_समयout(&phyreset, 2 * HZ);
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&phy->lock, flags);
		phy->reset_completion = शून्य;
		phy->in_reset = 0;
		spin_unlock_irqrestore(&phy->lock, flags);

		/* report PHY करोwn अगर समयd out */
		अगर (!ret)
			hisi_sas_phy_करोwn(hisi_hba, sas_phy->id, 0, GFP_KERNEL);
	पूर्ण अन्यथा अगर (sas_dev->dev_status != HISI_SAS_DEV_INIT) अणु
		/*
		 * If in init state, we rely on caller to रुको क्रम link to be
		 * पढ़ोy; otherwise, except phy reset is fail, delay.
		 */
		अगर (!rc)
			msleep(2000);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक hisi_sas_I_T_nexus_reset(काष्ठा करोमुख्य_device *device)
अणु
	काष्ठा hisi_hba *hisi_hba = dev_to_hisi_hba(device);
	काष्ठा device *dev = hisi_hba->dev;
	पूर्णांक rc;

	rc = hisi_sas_पूर्णांकernal_task_पात(hisi_hba, device,
					  HISI_SAS_INT_ABT_DEV, 0);
	अगर (rc < 0) अणु
		dev_err(dev, "I_T nexus reset: internal abort (%d)\n", rc);
		वापस TMF_RESP_FUNC_FAILED;
	पूर्ण
	hisi_sas_dereg_device(hisi_hba, device);

	अगर (dev_is_sata(device)) अणु
		rc = hisi_sas_softreset_ata_disk(device);
		अगर (rc == TMF_RESP_FUNC_FAILED)
			वापस TMF_RESP_FUNC_FAILED;
	पूर्ण

	rc = hisi_sas_debug_I_T_nexus_reset(device);

	अगर ((rc == TMF_RESP_FUNC_COMPLETE) || (rc == -ENODEV))
		hisi_sas_release_task(hisi_hba, device);

	वापस rc;
पूर्ण

अटल पूर्णांक hisi_sas_lu_reset(काष्ठा करोमुख्य_device *device, u8 *lun)
अणु
	काष्ठा hisi_sas_device *sas_dev = device->lldd_dev;
	काष्ठा hisi_hba *hisi_hba = dev_to_hisi_hba(device);
	काष्ठा device *dev = hisi_hba->dev;
	पूर्णांक rc = TMF_RESP_FUNC_FAILED;

	/* Clear पूर्णांकernal IO and then lu reset */
	rc = hisi_sas_पूर्णांकernal_task_पात(hisi_hba, device,
					  HISI_SAS_INT_ABT_DEV, 0);
	अगर (rc < 0) अणु
		dev_err(dev, "lu_reset: internal abort failed\n");
		जाओ out;
	पूर्ण
	hisi_sas_dereg_device(hisi_hba, device);

	अगर (dev_is_sata(device)) अणु
		काष्ठा sas_phy *phy;

		phy = sas_get_local_phy(device);

		rc = sas_phy_reset(phy, true);

		अगर (rc == 0)
			hisi_sas_release_task(hisi_hba, device);
		sas_put_local_phy(phy);
	पूर्ण अन्यथा अणु
		काष्ठा hisi_sas_पंचांगf_task पंचांगf_task = अणु .पंचांगf =  TMF_LU_RESET पूर्ण;

		rc = hisi_sas_debug_issue_ssp_पंचांगf(device, lun, &पंचांगf_task);
		अगर (rc == TMF_RESP_FUNC_COMPLETE)
			hisi_sas_release_task(hisi_hba, device);
	पूर्ण
out:
	अगर (rc != TMF_RESP_FUNC_COMPLETE)
		dev_err(dev, "lu_reset: for device[%d]:rc= %d\n",
			     sas_dev->device_id, rc);
	वापस rc;
पूर्ण

अटल पूर्णांक hisi_sas_clear_nexus_ha(काष्ठा sas_ha_काष्ठा *sas_ha)
अणु
	काष्ठा hisi_hba *hisi_hba = sas_ha->lldd_ha;
	काष्ठा device *dev = hisi_hba->dev;
	HISI_SAS_DECLARE_RST_WORK_ON_STACK(r);
	पूर्णांक rc, i;

	queue_work(hisi_hba->wq, &r.work);
	रुको_क्रम_completion(r.completion);
	अगर (!r.करोne)
		वापस TMF_RESP_FUNC_FAILED;

	क्रम (i = 0; i < HISI_SAS_MAX_DEVICES; i++) अणु
		काष्ठा hisi_sas_device *sas_dev = &hisi_hba->devices[i];
		काष्ठा करोमुख्य_device *device = sas_dev->sas_device;

		अगर ((sas_dev->dev_type == SAS_PHY_UNUSED) || !device ||
		    dev_is_expander(device->dev_type))
			जारी;

		rc = hisi_sas_debug_I_T_nexus_reset(device);
		अगर (rc != TMF_RESP_FUNC_COMPLETE)
			dev_info(dev, "clear nexus ha: for device[%d] rc=%d\n",
				 sas_dev->device_id, rc);
	पूर्ण

	hisi_sas_release_tasks(hisi_hba);

	वापस TMF_RESP_FUNC_COMPLETE;
पूर्ण

अटल पूर्णांक hisi_sas_query_task(काष्ठा sas_task *task)
अणु
	काष्ठा scsi_lun lun;
	काष्ठा hisi_sas_पंचांगf_task पंचांगf_task;
	पूर्णांक rc = TMF_RESP_FUNC_FAILED;

	अगर (task->lldd_task && task->task_proto & SAS_PROTOCOL_SSP) अणु
		काष्ठा scsi_cmnd *cmnd = task->uldd_task;
		काष्ठा करोमुख्य_device *device = task->dev;
		काष्ठा hisi_sas_slot *slot = task->lldd_task;
		u32 tag = slot->idx;

		पूर्णांक_to_scsilun(cmnd->device->lun, &lun);
		पंचांगf_task.पंचांगf = TMF_QUERY_TASK;
		पंचांगf_task.tag_of_task_to_be_managed = tag;

		rc = hisi_sas_debug_issue_ssp_पंचांगf(device,
						  lun.scsi_lun,
						  &पंचांगf_task);
		चयन (rc) अणु
		/* The task is still in Lun, release it then */
		हाल TMF_RESP_FUNC_SUCC:
		/* The task is not in Lun or failed, reset the phy */
		हाल TMF_RESP_FUNC_FAILED:
		हाल TMF_RESP_FUNC_COMPLETE:
			अवरोध;
		शेष:
			rc = TMF_RESP_FUNC_FAILED;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक
hisi_sas_पूर्णांकernal_पात_task_exec(काष्ठा hisi_hba *hisi_hba, पूर्णांक device_id,
				  काष्ठा sas_task *task, पूर्णांक पात_flag,
				  पूर्णांक task_tag, काष्ठा hisi_sas_dq *dq)
अणु
	काष्ठा करोमुख्य_device *device = task->dev;
	काष्ठा hisi_sas_device *sas_dev = device->lldd_dev;
	काष्ठा device *dev = hisi_hba->dev;
	काष्ठा hisi_sas_port *port;
	काष्ठा hisi_sas_slot *slot;
	काष्ठा asd_sas_port *sas_port = device->port;
	काष्ठा hisi_sas_cmd_hdr *cmd_hdr_base;
	पूर्णांक dlvry_queue_slot, dlvry_queue, n_elem = 0, rc, slot_idx;
	अचिन्हित दीर्घ flags;
	पूर्णांक wr_q_index;

	अगर (unlikely(test_bit(HISI_SAS_REJECT_CMD_BIT, &hisi_hba->flags)))
		वापस -EINVAL;

	अगर (!device->port)
		वापस -1;

	port = to_hisi_sas_port(sas_port);

	/* simply get a slot and send पात command */
	rc = hisi_sas_slot_index_alloc(hisi_hba, शून्य);
	अगर (rc < 0)
		जाओ err_out;

	slot_idx = rc;
	slot = &hisi_hba->slot_info[slot_idx];

	spin_lock(&dq->lock);
	wr_q_index = dq->wr_poपूर्णांक;
	dq->wr_poपूर्णांक = (dq->wr_poपूर्णांक + 1) % HISI_SAS_QUEUE_SLOTS;
	list_add_tail(&slot->delivery, &dq->list);
	spin_unlock(&dq->lock);
	spin_lock(&sas_dev->lock);
	list_add_tail(&slot->entry, &sas_dev->list);
	spin_unlock(&sas_dev->lock);

	dlvry_queue = dq->id;
	dlvry_queue_slot = wr_q_index;

	slot->device_id = sas_dev->device_id;
	slot->n_elem = n_elem;
	slot->dlvry_queue = dlvry_queue;
	slot->dlvry_queue_slot = dlvry_queue_slot;
	cmd_hdr_base = hisi_hba->cmd_hdr[dlvry_queue];
	slot->cmd_hdr = &cmd_hdr_base[dlvry_queue_slot];
	slot->task = task;
	slot->port = port;
	slot->is_पूर्णांकernal = true;
	task->lldd_task = slot;

	स_रखो(slot->cmd_hdr, 0, माप(काष्ठा hisi_sas_cmd_hdr));
	स_रखो(hisi_sas_cmd_hdr_addr_mem(slot), 0, HISI_SAS_COMMAND_TABLE_SZ);
	स_रखो(hisi_sas_status_buf_addr_mem(slot), 0,
	       माप(काष्ठा hisi_sas_err_record));

	hisi_sas_task_prep_पात(hisi_hba, slot, device_id,
				      पात_flag, task_tag);

	spin_lock_irqsave(&task->task_state_lock, flags);
	task->task_state_flags |= SAS_TASK_AT_INITIATOR;
	spin_unlock_irqrestore(&task->task_state_lock, flags);
	WRITE_ONCE(slot->पढ़ोy, 1);
	/* send पात command to the chip */
	spin_lock(&dq->lock);
	hisi_hba->hw->start_delivery(dq);
	spin_unlock(&dq->lock);

	वापस 0;

err_out:
	dev_err(dev, "internal abort task prep: failed[%d]!\n", rc);

	वापस rc;
पूर्ण

/**
 * _hisi_sas_पूर्णांकernal_task_पात -- execute an पूर्णांकernal
 * पात command क्रम single IO command or a device
 * @hisi_hba: host controller काष्ठा
 * @device: करोमुख्य device
 * @पात_flag: mode of operation, device or single IO
 * @tag: tag of IO to be पातed (only relevant to single
 *       IO mode)
 * @dq: delivery queue क्रम this पूर्णांकernal पात command
 */
अटल पूर्णांक
_hisi_sas_पूर्णांकernal_task_पात(काष्ठा hisi_hba *hisi_hba,
			      काष्ठा करोमुख्य_device *device, पूर्णांक पात_flag,
			      पूर्णांक tag, काष्ठा hisi_sas_dq *dq)
अणु
	काष्ठा sas_task *task;
	काष्ठा hisi_sas_device *sas_dev = device->lldd_dev;
	काष्ठा device *dev = hisi_hba->dev;
	पूर्णांक res;

	/*
	 * The पूर्णांकerface is not realized means this HW करोn't support पूर्णांकernal
	 * पात, or करोn't need to करो पूर्णांकernal पात. Then here, we वापस
	 * TMF_RESP_FUNC_FAILED and let other steps go on, which depends that
	 * the पूर्णांकernal पात has been executed and वापसed CQ.
	 */
	अगर (!hisi_hba->hw->prep_पात)
		वापस TMF_RESP_FUNC_FAILED;

	task = sas_alloc_slow_task(GFP_KERNEL);
	अगर (!task)
		वापस -ENOMEM;

	task->dev = device;
	task->task_proto = device->tproto;
	task->task_करोne = hisi_sas_task_करोne;
	task->slow_task->समयr.function = hisi_sas_पंचांगf_समयकरोut;
	task->slow_task->समयr.expires = jअगरfies + INTERNAL_ABORT_TIMEOUT * HZ;
	add_समयr(&task->slow_task->समयr);

	res = hisi_sas_पूर्णांकernal_पात_task_exec(hisi_hba, sas_dev->device_id,
						task, पात_flag, tag, dq);
	अगर (res) अणु
		del_समयr(&task->slow_task->समयr);
		dev_err(dev, "internal task abort: executing internal task failed: %d\n",
			res);
		जाओ निकास;
	पूर्ण
	रुको_क्रम_completion(&task->slow_task->completion);
	res = TMF_RESP_FUNC_FAILED;

	/* Internal पात समयd out */
	अगर ((task->task_state_flags & SAS_TASK_STATE_ABORTED)) अणु
		अगर (hisi_sas_debugfs_enable && hisi_hba->debugfs_itct[0].itct)
			queue_work(hisi_hba->wq, &hisi_hba->debugfs_work);

		अगर (!(task->task_state_flags & SAS_TASK_STATE_DONE)) अणु
			काष्ठा hisi_sas_slot *slot = task->lldd_task;

			अगर (slot) अणु
				काष्ठा hisi_sas_cq *cq =
					&hisi_hba->cq[slot->dlvry_queue];
				/*
				 * sync irq to aव्योम मुक्त'ing task
				 * beक्रमe using task in IO completion
				 */
				synchronize_irq(cq->irq_no);
				slot->task = शून्य;
			पूर्ण
			dev_err(dev, "internal task abort: timeout and not done.\n");

			res = -EIO;
			जाओ निकास;
		पूर्ण अन्यथा
			dev_err(dev, "internal task abort: timeout.\n");
	पूर्ण

	अगर (task->task_status.resp == SAS_TASK_COMPLETE &&
		task->task_status.stat == TMF_RESP_FUNC_COMPLETE) अणु
		res = TMF_RESP_FUNC_COMPLETE;
		जाओ निकास;
	पूर्ण

	अगर (task->task_status.resp == SAS_TASK_COMPLETE &&
		task->task_status.stat == TMF_RESP_FUNC_SUCC) अणु
		res = TMF_RESP_FUNC_SUCC;
		जाओ निकास;
	पूर्ण

निकास:
	dev_dbg(dev, "internal task abort: task to dev %016llx task=%pK resp: 0x%x sts 0x%x\n",
		SAS_ADDR(device->sas_addr), task,
		task->task_status.resp, /* 0 is complete, -1 is undelivered */
		task->task_status.stat);
	sas_मुक्त_task(task);

	वापस res;
पूर्ण

अटल पूर्णांक
hisi_sas_पूर्णांकernal_task_पात(काष्ठा hisi_hba *hisi_hba,
			     काष्ठा करोमुख्य_device *device,
			     पूर्णांक पात_flag, पूर्णांक tag)
अणु
	काष्ठा hisi_sas_slot *slot;
	काष्ठा device *dev = hisi_hba->dev;
	काष्ठा hisi_sas_dq *dq;
	पूर्णांक i, rc;

	चयन (पात_flag) अणु
	हाल HISI_SAS_INT_ABT_CMD:
		slot = &hisi_hba->slot_info[tag];
		dq = &hisi_hba->dq[slot->dlvry_queue];
		वापस _hisi_sas_पूर्णांकernal_task_पात(hisi_hba, device,
						     पात_flag, tag, dq);
	हाल HISI_SAS_INT_ABT_DEV:
		क्रम (i = 0; i < hisi_hba->cq_nvecs; i++) अणु
			काष्ठा hisi_sas_cq *cq = &hisi_hba->cq[i];
			स्थिर काष्ठा cpumask *mask = cq->irq_mask;

			अगर (mask && !cpumask_पूर्णांकersects(cpu_online_mask, mask))
				जारी;
			dq = &hisi_hba->dq[i];
			rc = _hisi_sas_पूर्णांकernal_task_पात(hisi_hba, device,
							   पात_flag, tag,
							   dq);
			अगर (rc)
				वापस rc;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(dev, "Unrecognised internal abort flag (%d)\n",
			पात_flag);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hisi_sas_port_क्रमmed(काष्ठा asd_sas_phy *sas_phy)
अणु
	hisi_sas_port_notअगरy_क्रमmed(sas_phy);
पूर्ण

अटल पूर्णांक hisi_sas_ग_लिखो_gpio(काष्ठा sas_ha_काष्ठा *sha, u8 reg_type,
			u8 reg_index, u8 reg_count, u8 *ग_लिखो_data)
अणु
	काष्ठा hisi_hba *hisi_hba = sha->lldd_ha;

	अगर (!hisi_hba->hw->ग_लिखो_gpio)
		वापस -EOPNOTSUPP;

	वापस hisi_hba->hw->ग_लिखो_gpio(hisi_hba, reg_type,
				reg_index, reg_count, ग_लिखो_data);
पूर्ण

अटल व्योम hisi_sas_phy_disconnected(काष्ठा hisi_sas_phy *phy)
अणु
	काष्ठा asd_sas_phy *sas_phy = &phy->sas_phy;
	काष्ठा sas_phy *sphy = sas_phy->phy;
	अचिन्हित दीर्घ flags;

	phy->phy_attached = 0;
	phy->phy_type = 0;
	phy->port = शून्य;

	spin_lock_irqsave(&phy->lock, flags);
	अगर (phy->enable)
		sphy->negotiated_linkrate = SAS_LINK_RATE_UNKNOWN;
	अन्यथा
		sphy->negotiated_linkrate = SAS_PHY_DISABLED;
	spin_unlock_irqrestore(&phy->lock, flags);
पूर्ण

व्योम hisi_sas_phy_करोwn(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no, पूर्णांक rdy,
		       gfp_t gfp_flags)
अणु
	काष्ठा hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
	काष्ठा asd_sas_phy *sas_phy = &phy->sas_phy;
	काष्ठा device *dev = hisi_hba->dev;

	अगर (rdy) अणु
		/* Phy करोwn but पढ़ोy */
		hisi_sas_bytes_dmaed(hisi_hba, phy_no, gfp_flags);
		hisi_sas_port_notअगरy_क्रमmed(sas_phy);
	पूर्ण अन्यथा अणु
		काष्ठा hisi_sas_port *port  = phy->port;

		अगर (test_bit(HISI_SAS_RESET_BIT, &hisi_hba->flags) ||
		    phy->in_reset) अणु
			dev_info(dev, "ignore flutter phy%d down\n", phy_no);
			वापस;
		पूर्ण
		/* Phy करोwn and not पढ़ोy */
		sas_notअगरy_phy_event(sas_phy, PHYE_LOSS_OF_SIGNAL, gfp_flags);
		sas_phy_disconnected(sas_phy);

		अगर (port) अणु
			अगर (phy->phy_type & PORT_TYPE_SAS) अणु
				पूर्णांक port_id = port->id;

				अगर (!hisi_hba->hw->get_wideport_biपंचांगap(hisi_hba,
								       port_id))
					port->port_attached = 0;
			पूर्ण अन्यथा अगर (phy->phy_type & PORT_TYPE_SATA)
				port->port_attached = 0;
		पूर्ण
		hisi_sas_phy_disconnected(phy);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(hisi_sas_phy_करोwn);

व्योम hisi_sas_sync_irqs(काष्ठा hisi_hba *hisi_hba)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < hisi_hba->cq_nvecs; i++) अणु
		काष्ठा hisi_sas_cq *cq = &hisi_hba->cq[i];

		synchronize_irq(cq->irq_no);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(hisi_sas_sync_irqs);

पूर्णांक hisi_sas_host_reset(काष्ठा Scsi_Host *shost, पूर्णांक reset_type)
अणु
	काष्ठा hisi_hba *hisi_hba = shost_priv(shost);

	अगर (reset_type != SCSI_ADAPTER_RESET)
		वापस -EOPNOTSUPP;

	queue_work(hisi_hba->wq, &hisi_hba->rst_work);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hisi_sas_host_reset);

काष्ठा scsi_transport_ढाँचा *hisi_sas_stt;
EXPORT_SYMBOL_GPL(hisi_sas_stt);

अटल काष्ठा sas_करोमुख्य_function_ढाँचा hisi_sas_transport_ops = अणु
	.lldd_dev_found		= hisi_sas_dev_found,
	.lldd_dev_gone		= hisi_sas_dev_gone,
	.lldd_execute_task	= hisi_sas_queue_command,
	.lldd_control_phy	= hisi_sas_control_phy,
	.lldd_पात_task	= hisi_sas_पात_task,
	.lldd_पात_task_set	= hisi_sas_पात_task_set,
	.lldd_clear_aca		= hisi_sas_clear_aca,
	.lldd_I_T_nexus_reset	= hisi_sas_I_T_nexus_reset,
	.lldd_lu_reset		= hisi_sas_lu_reset,
	.lldd_query_task	= hisi_sas_query_task,
	.lldd_clear_nexus_ha	= hisi_sas_clear_nexus_ha,
	.lldd_port_क्रमmed	= hisi_sas_port_क्रमmed,
	.lldd_ग_लिखो_gpio	= hisi_sas_ग_लिखो_gpio,
पूर्ण;

व्योम hisi_sas_init_mem(काष्ठा hisi_hba *hisi_hba)
अणु
	पूर्णांक i, s, j, max_command_entries = HISI_SAS_MAX_COMMANDS;
	काष्ठा hisi_sas_अवरोधpoपूर्णांक *sata_अवरोधpoपूर्णांक = hisi_hba->sata_अवरोधpoपूर्णांक;

	क्रम (i = 0; i < hisi_hba->queue_count; i++) अणु
		काष्ठा hisi_sas_cq *cq = &hisi_hba->cq[i];
		काष्ठा hisi_sas_dq *dq = &hisi_hba->dq[i];
		काष्ठा hisi_sas_cmd_hdr *cmd_hdr = hisi_hba->cmd_hdr[i];

		s = माप(काष्ठा hisi_sas_cmd_hdr);
		क्रम (j = 0; j < HISI_SAS_QUEUE_SLOTS; j++)
			स_रखो(&cmd_hdr[j], 0, s);

		dq->wr_poपूर्णांक = 0;

		s = hisi_hba->hw->complete_hdr_size * HISI_SAS_QUEUE_SLOTS;
		स_रखो(hisi_hba->complete_hdr[i], 0, s);
		cq->rd_poपूर्णांक = 0;
	पूर्ण

	s = माप(काष्ठा hisi_sas_initial_fis) * hisi_hba->n_phy;
	स_रखो(hisi_hba->initial_fis, 0, s);

	s = max_command_entries * माप(काष्ठा hisi_sas_iost);
	स_रखो(hisi_hba->iost, 0, s);

	s = max_command_entries * माप(काष्ठा hisi_sas_अवरोधpoपूर्णांक);
	स_रखो(hisi_hba->अवरोधpoपूर्णांक, 0, s);

	s = माप(काष्ठा hisi_sas_sata_अवरोधpoपूर्णांक);
	क्रम (j = 0; j < HISI_SAS_MAX_ITCT_ENTRIES; j++)
		स_रखो(&sata_अवरोधpoपूर्णांक[j], 0, s);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_sas_init_mem);

पूर्णांक hisi_sas_alloc(काष्ठा hisi_hba *hisi_hba)
अणु
	काष्ठा device *dev = hisi_hba->dev;
	पूर्णांक i, j, s, max_command_entries = HISI_SAS_MAX_COMMANDS;
	पूर्णांक max_command_entries_ru, sz_slot_buf_ru;
	पूर्णांक blk_cnt, slots_per_blk;

	sema_init(&hisi_hba->sem, 1);
	spin_lock_init(&hisi_hba->lock);
	क्रम (i = 0; i < hisi_hba->n_phy; i++) अणु
		hisi_sas_phy_init(hisi_hba, i);
		hisi_hba->port[i].port_attached = 0;
		hisi_hba->port[i].id = -1;
	पूर्ण

	क्रम (i = 0; i < HISI_SAS_MAX_DEVICES; i++) अणु
		hisi_hba->devices[i].dev_type = SAS_PHY_UNUSED;
		hisi_hba->devices[i].device_id = i;
		hisi_hba->devices[i].dev_status = HISI_SAS_DEV_INIT;
	पूर्ण

	क्रम (i = 0; i < hisi_hba->queue_count; i++) अणु
		काष्ठा hisi_sas_cq *cq = &hisi_hba->cq[i];
		काष्ठा hisi_sas_dq *dq = &hisi_hba->dq[i];

		/* Completion queue काष्ठाure */
		cq->id = i;
		cq->hisi_hba = hisi_hba;

		/* Delivery queue काष्ठाure */
		spin_lock_init(&dq->lock);
		INIT_LIST_HEAD(&dq->list);
		dq->id = i;
		dq->hisi_hba = hisi_hba;

		/* Delivery queue */
		s = माप(काष्ठा hisi_sas_cmd_hdr) * HISI_SAS_QUEUE_SLOTS;
		hisi_hba->cmd_hdr[i] = dmam_alloc_coherent(dev, s,
						&hisi_hba->cmd_hdr_dma[i],
						GFP_KERNEL);
		अगर (!hisi_hba->cmd_hdr[i])
			जाओ err_out;

		/* Completion queue */
		s = hisi_hba->hw->complete_hdr_size * HISI_SAS_QUEUE_SLOTS;
		hisi_hba->complete_hdr[i] = dmam_alloc_coherent(dev, s,
						&hisi_hba->complete_hdr_dma[i],
						GFP_KERNEL);
		अगर (!hisi_hba->complete_hdr[i])
			जाओ err_out;
	पूर्ण

	s = HISI_SAS_MAX_ITCT_ENTRIES * माप(काष्ठा hisi_sas_itct);
	hisi_hba->itct = dmam_alloc_coherent(dev, s, &hisi_hba->itct_dma,
					     GFP_KERNEL);
	अगर (!hisi_hba->itct)
		जाओ err_out;

	hisi_hba->slot_info = devm_kसुस्मृति(dev, max_command_entries,
					   माप(काष्ठा hisi_sas_slot),
					   GFP_KERNEL);
	अगर (!hisi_hba->slot_info)
		जाओ err_out;

	/* roundup to aव्योम overly large block size */
	max_command_entries_ru = roundup(max_command_entries, 64);
	अगर (hisi_hba->prot_mask & HISI_SAS_DIX_PROT_MASK)
		sz_slot_buf_ru = माप(काष्ठा hisi_sas_slot_dअगर_buf_table);
	अन्यथा
		sz_slot_buf_ru = माप(काष्ठा hisi_sas_slot_buf_table);
	sz_slot_buf_ru = roundup(sz_slot_buf_ru, 64);
	s = max(lcm(max_command_entries_ru, sz_slot_buf_ru), PAGE_SIZE);
	blk_cnt = (max_command_entries_ru * sz_slot_buf_ru) / s;
	slots_per_blk = s / sz_slot_buf_ru;

	क्रम (i = 0; i < blk_cnt; i++) अणु
		पूर्णांक slot_index = i * slots_per_blk;
		dma_addr_t buf_dma;
		व्योम *buf;

		buf = dmam_alloc_coherent(dev, s, &buf_dma,
					  GFP_KERNEL);
		अगर (!buf)
			जाओ err_out;

		क्रम (j = 0; j < slots_per_blk; j++, slot_index++) अणु
			काष्ठा hisi_sas_slot *slot;

			slot = &hisi_hba->slot_info[slot_index];
			slot->buf = buf;
			slot->buf_dma = buf_dma;
			slot->idx = slot_index;

			buf += sz_slot_buf_ru;
			buf_dma += sz_slot_buf_ru;
		पूर्ण
	पूर्ण

	s = max_command_entries * माप(काष्ठा hisi_sas_iost);
	hisi_hba->iost = dmam_alloc_coherent(dev, s, &hisi_hba->iost_dma,
					     GFP_KERNEL);
	अगर (!hisi_hba->iost)
		जाओ err_out;

	s = max_command_entries * माप(काष्ठा hisi_sas_अवरोधpoपूर्णांक);
	hisi_hba->अवरोधpoपूर्णांक = dmam_alloc_coherent(dev, s,
						   &hisi_hba->अवरोधpoपूर्णांक_dma,
						   GFP_KERNEL);
	अगर (!hisi_hba->अवरोधpoपूर्णांक)
		जाओ err_out;

	hisi_hba->slot_index_count = max_command_entries;
	s = hisi_hba->slot_index_count / BITS_PER_BYTE;
	hisi_hba->slot_index_tags = devm_kzalloc(dev, s, GFP_KERNEL);
	अगर (!hisi_hba->slot_index_tags)
		जाओ err_out;

	s = माप(काष्ठा hisi_sas_initial_fis) * HISI_SAS_MAX_PHYS;
	hisi_hba->initial_fis = dmam_alloc_coherent(dev, s,
						    &hisi_hba->initial_fis_dma,
						    GFP_KERNEL);
	अगर (!hisi_hba->initial_fis)
		जाओ err_out;

	s = HISI_SAS_MAX_ITCT_ENTRIES * माप(काष्ठा hisi_sas_sata_अवरोधpoपूर्णांक);
	hisi_hba->sata_अवरोधpoपूर्णांक = dmam_alloc_coherent(dev, s,
					&hisi_hba->sata_अवरोधpoपूर्णांक_dma,
					GFP_KERNEL);
	अगर (!hisi_hba->sata_अवरोधpoपूर्णांक)
		जाओ err_out;

	hisi_sas_slot_index_init(hisi_hba);
	hisi_hba->last_slot_index = HISI_SAS_UNRESERVED_IPTT;

	hisi_hba->wq = create_singlethपढ़ो_workqueue(dev_name(dev));
	अगर (!hisi_hba->wq) अणु
		dev_err(dev, "sas_alloc: failed to create workqueue\n");
		जाओ err_out;
	पूर्ण

	वापस 0;
err_out:
	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL_GPL(hisi_sas_alloc);

व्योम hisi_sas_मुक्त(काष्ठा hisi_hba *hisi_hba)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < hisi_hba->n_phy; i++) अणु
		काष्ठा hisi_sas_phy *phy = &hisi_hba->phy[i];

		del_समयr_sync(&phy->समयr);
	पूर्ण

	अगर (hisi_hba->wq)
		destroy_workqueue(hisi_hba->wq);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_sas_मुक्त);

व्योम hisi_sas_rst_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hisi_hba *hisi_hba =
		container_of(work, काष्ठा hisi_hba, rst_work);

	अगर (hisi_sas_controller_prereset(hisi_hba))
		वापस;

	hisi_sas_controller_reset(hisi_hba);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_sas_rst_work_handler);

व्योम hisi_sas_sync_rst_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hisi_sas_rst *rst =
		container_of(work, काष्ठा hisi_sas_rst, work);

	अगर (hisi_sas_controller_prereset(rst->hisi_hba))
		जाओ rst_complete;

	अगर (!hisi_sas_controller_reset(rst->hisi_hba))
		rst->करोne = true;
rst_complete:
	complete(rst->completion);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_sas_sync_rst_work_handler);

पूर्णांक hisi_sas_get_fw_info(काष्ठा hisi_hba *hisi_hba)
अणु
	काष्ठा device *dev = hisi_hba->dev;
	काष्ठा platक्रमm_device *pdev = hisi_hba->platक्रमm_dev;
	काष्ठा device_node *np = pdev ? pdev->dev.of_node : शून्य;
	काष्ठा clk *refclk;

	अगर (device_property_पढ़ो_u8_array(dev, "sas-addr", hisi_hba->sas_addr,
					  SAS_ADDR_SIZE)) अणु
		dev_err(dev, "could not get property sas-addr\n");
		वापस -ENOENT;
	पूर्ण

	अगर (np) अणु
		/*
		 * These properties are only required क्रम platक्रमm device-based
		 * controller with DT firmware.
		 */
		hisi_hba->ctrl = syscon_regmap_lookup_by_phandle(np,
					"hisilicon,sas-syscon");
		अगर (IS_ERR(hisi_hba->ctrl)) अणु
			dev_err(dev, "could not get syscon\n");
			वापस -ENOENT;
		पूर्ण

		अगर (device_property_पढ़ो_u32(dev, "ctrl-reset-reg",
					     &hisi_hba->ctrl_reset_reg)) अणु
			dev_err(dev, "could not get property ctrl-reset-reg\n");
			वापस -ENOENT;
		पूर्ण

		अगर (device_property_पढ़ो_u32(dev, "ctrl-reset-sts-reg",
					     &hisi_hba->ctrl_reset_sts_reg)) अणु
			dev_err(dev, "could not get property ctrl-reset-sts-reg\n");
			वापस -ENOENT;
		पूर्ण

		अगर (device_property_पढ़ो_u32(dev, "ctrl-clock-ena-reg",
					     &hisi_hba->ctrl_घड़ी_ena_reg)) अणु
			dev_err(dev, "could not get property ctrl-clock-ena-reg\n");
			वापस -ENOENT;
		पूर्ण
	पूर्ण

	refclk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(refclk))
		dev_dbg(dev, "no ref clk property\n");
	अन्यथा
		hisi_hba->refclk_frequency_mhz = clk_get_rate(refclk) / 1000000;

	अगर (device_property_पढ़ो_u32(dev, "phy-count", &hisi_hba->n_phy)) अणु
		dev_err(dev, "could not get property phy-count\n");
		वापस -ENOENT;
	पूर्ण

	अगर (device_property_पढ़ो_u32(dev, "queue-count",
				     &hisi_hba->queue_count)) अणु
		dev_err(dev, "could not get property queue-count\n");
		वापस -ENOENT;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hisi_sas_get_fw_info);

अटल काष्ठा Scsi_Host *hisi_sas_shost_alloc(काष्ठा platक्रमm_device *pdev,
					      स्थिर काष्ठा hisi_sas_hw *hw)
अणु
	काष्ठा resource *res;
	काष्ठा Scsi_Host *shost;
	काष्ठा hisi_hba *hisi_hba;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक error;

	shost = scsi_host_alloc(hw->sht, माप(*hisi_hba));
	अगर (!shost) अणु
		dev_err(dev, "scsi host alloc failed\n");
		वापस शून्य;
	पूर्ण
	hisi_hba = shost_priv(shost);

	INIT_WORK(&hisi_hba->rst_work, hisi_sas_rst_work_handler);
	hisi_hba->hw = hw;
	hisi_hba->dev = dev;
	hisi_hba->platक्रमm_dev = pdev;
	hisi_hba->shost = shost;
	SHOST_TO_SAS_HA(shost) = &hisi_hba->sha;

	समयr_setup(&hisi_hba->समयr, शून्य, 0);

	अगर (hisi_sas_get_fw_info(hisi_hba) < 0)
		जाओ err_out;

	error = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(64));
	अगर (error)
		error = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32));

	अगर (error) अणु
		dev_err(dev, "No usable DMA addressing method\n");
		जाओ err_out;
	पूर्ण

	hisi_hba->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(hisi_hba->regs))
		जाओ err_out;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (res) अणु
		hisi_hba->sgpio_regs = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(hisi_hba->sgpio_regs))
			जाओ err_out;
	पूर्ण

	अगर (hisi_sas_alloc(hisi_hba)) अणु
		hisi_sas_मुक्त(hisi_hba);
		जाओ err_out;
	पूर्ण

	वापस shost;
err_out:
	scsi_host_put(shost);
	dev_err(dev, "shost alloc failed\n");
	वापस शून्य;
पूर्ण

अटल पूर्णांक hisi_sas_पूर्णांकerrupt_preinit(काष्ठा hisi_hba *hisi_hba)
अणु
	अगर (hisi_hba->hw->पूर्णांकerrupt_preinit)
		वापस hisi_hba->hw->पूर्णांकerrupt_preinit(hisi_hba);
	वापस 0;
पूर्ण

पूर्णांक hisi_sas_probe(काष्ठा platक्रमm_device *pdev,
		   स्थिर काष्ठा hisi_sas_hw *hw)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा hisi_hba *hisi_hba;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा asd_sas_phy **arr_phy;
	काष्ठा asd_sas_port **arr_port;
	काष्ठा sas_ha_काष्ठा *sha;
	पूर्णांक rc, phy_nr, port_nr, i;

	shost = hisi_sas_shost_alloc(pdev, hw);
	अगर (!shost)
		वापस -ENOMEM;

	sha = SHOST_TO_SAS_HA(shost);
	hisi_hba = shost_priv(shost);
	platक्रमm_set_drvdata(pdev, sha);

	phy_nr = port_nr = hisi_hba->n_phy;

	arr_phy = devm_kसुस्मृति(dev, phy_nr, माप(व्योम *), GFP_KERNEL);
	arr_port = devm_kसुस्मृति(dev, port_nr, माप(व्योम *), GFP_KERNEL);
	अगर (!arr_phy || !arr_port) अणु
		rc = -ENOMEM;
		जाओ err_out_ha;
	पूर्ण

	sha->sas_phy = arr_phy;
	sha->sas_port = arr_port;
	sha->lldd_ha = hisi_hba;

	shost->transportt = hisi_sas_stt;
	shost->max_id = HISI_SAS_MAX_DEVICES;
	shost->max_lun = ~0;
	shost->max_channel = 1;
	shost->max_cmd_len = 16;
	अगर (hisi_hba->hw->slot_index_alloc) अणु
		shost->can_queue = HISI_SAS_MAX_COMMANDS;
		shost->cmd_per_lun = HISI_SAS_MAX_COMMANDS;
	पूर्ण अन्यथा अणु
		shost->can_queue = HISI_SAS_UNRESERVED_IPTT;
		shost->cmd_per_lun = HISI_SAS_UNRESERVED_IPTT;
	पूर्ण

	sha->sas_ha_name = DRV_NAME;
	sha->dev = hisi_hba->dev;
	sha->lldd_module = THIS_MODULE;
	sha->sas_addr = &hisi_hba->sas_addr[0];
	sha->num_phys = hisi_hba->n_phy;
	sha->core.shost = hisi_hba->shost;

	क्रम (i = 0; i < hisi_hba->n_phy; i++) अणु
		sha->sas_phy[i] = &hisi_hba->phy[i].sas_phy;
		sha->sas_port[i] = &hisi_hba->port[i].sas_port;
	पूर्ण

	rc = hisi_sas_पूर्णांकerrupt_preinit(hisi_hba);
	अगर (rc)
		जाओ err_out_ha;

	rc = scsi_add_host(shost, &pdev->dev);
	अगर (rc)
		जाओ err_out_ha;

	rc = sas_रेजिस्टर_ha(sha);
	अगर (rc)
		जाओ err_out_रेजिस्टर_ha;

	rc = hisi_hba->hw->hw_init(hisi_hba);
	अगर (rc)
		जाओ err_out_hw_init;

	scsi_scan_host(shost);

	वापस 0;

err_out_hw_init:
	sas_unरेजिस्टर_ha(sha);
err_out_रेजिस्टर_ha:
	scsi_हटाओ_host(shost);
err_out_ha:
	hisi_sas_मुक्त(hisi_hba);
	scsi_host_put(shost);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(hisi_sas_probe);

पूर्णांक hisi_sas_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sas_ha_काष्ठा *sha = platक्रमm_get_drvdata(pdev);
	काष्ठा hisi_hba *hisi_hba = sha->lldd_ha;
	काष्ठा Scsi_Host *shost = sha->core.shost;

	अगर (समयr_pending(&hisi_hba->समयr))
		del_समयr(&hisi_hba->समयr);

	sas_unरेजिस्टर_ha(sha);
	sas_हटाओ_host(sha->core.shost);

	hisi_sas_मुक्त(hisi_hba);
	scsi_host_put(shost);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hisi_sas_हटाओ);

#अगर IS_ENABLED(CONFIG_SCSI_HISI_SAS_DEBUGFS_DEFAULT_ENABLE)
#घोषणा DEBUGFS_ENABLE_DEFAULT  "enabled"
bool hisi_sas_debugfs_enable = true;
u32 hisi_sas_debugfs_dump_count = 50;
#अन्यथा
#घोषणा DEBUGFS_ENABLE_DEFAULT "disabled"
bool hisi_sas_debugfs_enable;
u32 hisi_sas_debugfs_dump_count = 1;
#पूर्ण_अगर

EXPORT_SYMBOL_GPL(hisi_sas_debugfs_enable);
module_param_named(debugfs_enable, hisi_sas_debugfs_enable, bool, 0444);
MODULE_PARM_DESC(hisi_sas_debugfs_enable,
		 "Enable driver debugfs (default "DEBUGFS_ENABLE_DEFAULT")");

EXPORT_SYMBOL_GPL(hisi_sas_debugfs_dump_count);
module_param_named(debugfs_dump_count, hisi_sas_debugfs_dump_count, uपूर्णांक, 0444);
MODULE_PARM_DESC(hisi_sas_debugfs_dump_count, "Number of debugfs dumps to allow");

काष्ठा dentry *hisi_sas_debugfs_dir;
EXPORT_SYMBOL_GPL(hisi_sas_debugfs_dir);

अटल __init पूर्णांक hisi_sas_init(व्योम)
अणु
	hisi_sas_stt = sas_करोमुख्य_attach_transport(&hisi_sas_transport_ops);
	अगर (!hisi_sas_stt)
		वापस -ENOMEM;

	अगर (hisi_sas_debugfs_enable) अणु
		hisi_sas_debugfs_dir = debugfs_create_dir("hisi_sas", शून्य);
		अगर (hisi_sas_debugfs_dump_count > HISI_SAS_MAX_DEBUGFS_DUMP) अणु
			pr_info("hisi_sas: Limiting debugfs dump count\n");
			hisi_sas_debugfs_dump_count = HISI_SAS_MAX_DEBUGFS_DUMP;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल __निकास व्योम hisi_sas_निकास(व्योम)
अणु
	sas_release_transport(hisi_sas_stt);

	debugfs_हटाओ(hisi_sas_debugfs_dir);
पूर्ण

module_init(hisi_sas_init);
module_निकास(hisi_sas_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("John Garry <john.garry@huawei.com>");
MODULE_DESCRIPTION("HISILICON SAS controller driver");
MODULE_ALIAS("platform:" DRV_NAME);
