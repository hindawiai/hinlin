<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Linux Driver क्रम Mylex DAC960/AcceleRAID/eXtremeRAID PCI RAID Controllers
 *
 * Copyright 2017 Hannes Reinecke, SUSE Linux GmbH <hare@suse.com>
 *
 * Based on the original DAC960 driver,
 * Copyright 1998-2001 by Leonard N. Zubkoff <lnz@dandelion.com>
 * Portions Copyright 2002 by Mylex (An IBM Business Unit)
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/raid_class.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश "myrb.h"

अटल काष्ठा raid_ढाँचा *myrb_raid_ढाँचा;

अटल व्योम myrb_monitor(काष्ठा work_काष्ठा *work);
अटल अंतरभूत व्योम myrb_translate_devstate(व्योम *DeviceState);

अटल अंतरभूत पूर्णांक myrb_logical_channel(काष्ठा Scsi_Host *shost)
अणु
	वापस shost->max_channel - 1;
पूर्ण

अटल काष्ठा myrb_devstate_name_entry अणु
	क्रमागत myrb_devstate state;
	स्थिर अक्षर *name;
पूर्ण myrb_devstate_name_list[] = अणु
	अणु MYRB_DEVICE_DEAD, "Dead" पूर्ण,
	अणु MYRB_DEVICE_WO, "WriteOnly" पूर्ण,
	अणु MYRB_DEVICE_ONLINE, "Online" पूर्ण,
	अणु MYRB_DEVICE_CRITICAL, "Critical" पूर्ण,
	अणु MYRB_DEVICE_STANDBY, "Standby" पूर्ण,
	अणु MYRB_DEVICE_OFFLINE, "Offline" पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *myrb_devstate_name(क्रमागत myrb_devstate state)
अणु
	काष्ठा myrb_devstate_name_entry *entry = myrb_devstate_name_list;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(myrb_devstate_name_list); i++) अणु
		अगर (entry[i].state == state)
			वापस entry[i].name;
	पूर्ण
	वापस "Unknown";
पूर्ण

अटल काष्ठा myrb_raidlevel_name_entry अणु
	क्रमागत myrb_raidlevel level;
	स्थिर अक्षर *name;
पूर्ण myrb_raidlevel_name_list[] = अणु
	अणु MYRB_RAID_LEVEL0, "RAID0" पूर्ण,
	अणु MYRB_RAID_LEVEL1, "RAID1" पूर्ण,
	अणु MYRB_RAID_LEVEL3, "RAID3" पूर्ण,
	अणु MYRB_RAID_LEVEL5, "RAID5" पूर्ण,
	अणु MYRB_RAID_LEVEL6, "RAID6" पूर्ण,
	अणु MYRB_RAID_JBOD, "JBOD" पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *myrb_raidlevel_name(क्रमागत myrb_raidlevel level)
अणु
	काष्ठा myrb_raidlevel_name_entry *entry = myrb_raidlevel_name_list;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(myrb_raidlevel_name_list); i++) अणु
		अगर (entry[i].level == level)
			वापस entry[i].name;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * myrb_create_mempools - allocates auxiliary data काष्ठाures
 *
 * Return: true on success, false otherwise.
 */
अटल bool myrb_create_mempools(काष्ठा pci_dev *pdev, काष्ठा myrb_hba *cb)
अणु
	माप_प्रकार elem_size, elem_align;

	elem_align = माप(काष्ठा myrb_sge);
	elem_size = cb->host->sg_tablesize * elem_align;
	cb->sg_pool = dma_pool_create("myrb_sg", &pdev->dev,
				      elem_size, elem_align, 0);
	अगर (cb->sg_pool == शून्य) अणु
		shost_prपूर्णांकk(KERN_ERR, cb->host,
			     "Failed to allocate SG pool\n");
		वापस false;
	पूर्ण

	cb->dcdb_pool = dma_pool_create("myrb_dcdb", &pdev->dev,
				       माप(काष्ठा myrb_dcdb),
				       माप(अचिन्हित पूर्णांक), 0);
	अगर (!cb->dcdb_pool) अणु
		dma_pool_destroy(cb->sg_pool);
		cb->sg_pool = शून्य;
		shost_prपूर्णांकk(KERN_ERR, cb->host,
			     "Failed to allocate DCDB pool\n");
		वापस false;
	पूर्ण

	snम_लिखो(cb->work_q_name, माप(cb->work_q_name),
		 "myrb_wq_%d", cb->host->host_no);
	cb->work_q = create_singlethपढ़ो_workqueue(cb->work_q_name);
	अगर (!cb->work_q) अणु
		dma_pool_destroy(cb->dcdb_pool);
		cb->dcdb_pool = शून्य;
		dma_pool_destroy(cb->sg_pool);
		cb->sg_pool = शून्य;
		shost_prपूर्णांकk(KERN_ERR, cb->host,
			     "Failed to create workqueue\n");
		वापस false;
	पूर्ण

	/*
	 * Initialize the Monitoring Timer.
	 */
	INIT_DELAYED_WORK(&cb->monitor_work, myrb_monitor);
	queue_delayed_work(cb->work_q, &cb->monitor_work, 1);

	वापस true;
पूर्ण

/*
 * myrb_destroy_mempools - tears करोwn the memory pools क्रम the controller
 */
अटल व्योम myrb_destroy_mempools(काष्ठा myrb_hba *cb)
अणु
	cancel_delayed_work_sync(&cb->monitor_work);
	destroy_workqueue(cb->work_q);

	dma_pool_destroy(cb->sg_pool);
	dma_pool_destroy(cb->dcdb_pool);
पूर्ण

/*
 * myrb_reset_cmd - reset command block
 */
अटल अंतरभूत व्योम myrb_reset_cmd(काष्ठा myrb_cmdblk *cmd_blk)
अणु
	जोड़ myrb_cmd_mbox *mbox = &cmd_blk->mbox;

	स_रखो(mbox, 0, माप(जोड़ myrb_cmd_mbox));
	cmd_blk->status = 0;
पूर्ण

/*
 * myrb_qcmd - queues command block क्रम execution
 */
अटल व्योम myrb_qcmd(काष्ठा myrb_hba *cb, काष्ठा myrb_cmdblk *cmd_blk)
अणु
	व्योम __iomem *base = cb->io_base;
	जोड़ myrb_cmd_mbox *mbox = &cmd_blk->mbox;
	जोड़ myrb_cmd_mbox *next_mbox = cb->next_cmd_mbox;

	cb->ग_लिखो_cmd_mbox(next_mbox, mbox);
	अगर (cb->prev_cmd_mbox1->words[0] == 0 ||
	    cb->prev_cmd_mbox2->words[0] == 0)
		cb->get_cmd_mbox(base);
	cb->prev_cmd_mbox2 = cb->prev_cmd_mbox1;
	cb->prev_cmd_mbox1 = next_mbox;
	अगर (++next_mbox > cb->last_cmd_mbox)
		next_mbox = cb->first_cmd_mbox;
	cb->next_cmd_mbox = next_mbox;
पूर्ण

/*
 * myrb_exec_cmd - executes command block and रुकोs क्रम completion.
 *
 * Return: command status
 */
अटल अचिन्हित लघु myrb_exec_cmd(काष्ठा myrb_hba *cb,
		काष्ठा myrb_cmdblk *cmd_blk)
अणु
	DECLARE_COMPLETION_ONSTACK(cmpl);
	अचिन्हित दीर्घ flags;

	cmd_blk->completion = &cmpl;

	spin_lock_irqsave(&cb->queue_lock, flags);
	cb->qcmd(cb, cmd_blk);
	spin_unlock_irqrestore(&cb->queue_lock, flags);

	रुको_क्रम_completion(&cmpl);
	वापस cmd_blk->status;
पूर्ण

/*
 * myrb_exec_type3 - executes a type 3 command and रुकोs क्रम completion.
 *
 * Return: command status
 */
अटल अचिन्हित लघु myrb_exec_type3(काष्ठा myrb_hba *cb,
		क्रमागत myrb_cmd_opcode op, dma_addr_t addr)
अणु
	काष्ठा myrb_cmdblk *cmd_blk = &cb->dcmd_blk;
	जोड़ myrb_cmd_mbox *mbox = &cmd_blk->mbox;
	अचिन्हित लघु status;

	mutex_lock(&cb->dcmd_mutex);
	myrb_reset_cmd(cmd_blk);
	mbox->type3.id = MYRB_DCMD_TAG;
	mbox->type3.opcode = op;
	mbox->type3.addr = addr;
	status = myrb_exec_cmd(cb, cmd_blk);
	mutex_unlock(&cb->dcmd_mutex);
	वापस status;
पूर्ण

/*
 * myrb_exec_type3D - executes a type 3D command and रुकोs क्रम completion.
 *
 * Return: command status
 */
अटल अचिन्हित लघु myrb_exec_type3D(काष्ठा myrb_hba *cb,
		क्रमागत myrb_cmd_opcode op, काष्ठा scsi_device *sdev,
		काष्ठा myrb_pdev_state *pdev_info)
अणु
	काष्ठा myrb_cmdblk *cmd_blk = &cb->dcmd_blk;
	जोड़ myrb_cmd_mbox *mbox = &cmd_blk->mbox;
	अचिन्हित लघु status;
	dma_addr_t pdev_info_addr;

	pdev_info_addr = dma_map_single(&cb->pdev->dev, pdev_info,
					माप(काष्ठा myrb_pdev_state),
					DMA_FROM_DEVICE);
	अगर (dma_mapping_error(&cb->pdev->dev, pdev_info_addr))
		वापस MYRB_STATUS_SUBSYS_FAILED;

	mutex_lock(&cb->dcmd_mutex);
	myrb_reset_cmd(cmd_blk);
	mbox->type3D.id = MYRB_DCMD_TAG;
	mbox->type3D.opcode = op;
	mbox->type3D.channel = sdev->channel;
	mbox->type3D.target = sdev->id;
	mbox->type3D.addr = pdev_info_addr;
	status = myrb_exec_cmd(cb, cmd_blk);
	mutex_unlock(&cb->dcmd_mutex);
	dma_unmap_single(&cb->pdev->dev, pdev_info_addr,
			 माप(काष्ठा myrb_pdev_state), DMA_FROM_DEVICE);
	अगर (status == MYRB_STATUS_SUCCESS &&
	    mbox->type3D.opcode == MYRB_CMD_GET_DEVICE_STATE_OLD)
		myrb_translate_devstate(pdev_info);

	वापस status;
पूर्ण

अटल अक्षर *myrb_event_msg[] = अणु
	"killed because write recovery failed",
	"killed because of SCSI bus reset failure",
	"killed because of double check condition",
	"killed because it was removed",
	"killed because of gross error on SCSI chip",
	"killed because of bad tag returned from drive",
	"killed because of timeout on SCSI command",
	"killed because of reset SCSI command issued from system",
	"killed because busy or parity error count exceeded limit",
	"killed because of 'kill drive' command from system",
	"killed because of selection timeout",
	"killed due to SCSI phase sequence error",
	"killed due to unknown status",
पूर्ण;

/**
 * myrb_get_event - get event log from HBA
 * @cb: poपूर्णांकer to the hba काष्ठाure
 * @event: number of the event
 *
 * Execute a type 3E command and logs the event message
 */
अटल व्योम myrb_get_event(काष्ठा myrb_hba *cb, अचिन्हित पूर्णांक event)
अणु
	काष्ठा myrb_cmdblk *cmd_blk = &cb->mcmd_blk;
	जोड़ myrb_cmd_mbox *mbox = &cmd_blk->mbox;
	काष्ठा myrb_log_entry *ev_buf;
	dma_addr_t ev_addr;
	अचिन्हित लघु status;

	ev_buf = dma_alloc_coherent(&cb->pdev->dev,
				    माप(काष्ठा myrb_log_entry),
				    &ev_addr, GFP_KERNEL);
	अगर (!ev_buf)
		वापस;

	myrb_reset_cmd(cmd_blk);
	mbox->type3E.id = MYRB_MCMD_TAG;
	mbox->type3E.opcode = MYRB_CMD_EVENT_LOG_OPERATION;
	mbox->type3E.optype = DAC960_V1_GetEventLogEntry;
	mbox->type3E.opqual = 1;
	mbox->type3E.ev_seq = event;
	mbox->type3E.addr = ev_addr;
	status = myrb_exec_cmd(cb, cmd_blk);
	अगर (status != MYRB_STATUS_SUCCESS)
		shost_prपूर्णांकk(KERN_INFO, cb->host,
			     "Failed to get event log %d, status %04x\n",
			     event, status);

	अन्यथा अगर (ev_buf->seq_num == event) अणु
		काष्ठा scsi_sense_hdr sshdr;

		स_रखो(&sshdr, 0, माप(sshdr));
		scsi_normalize_sense(ev_buf->sense, 32, &sshdr);

		अगर (sshdr.sense_key == VENDOR_SPECIFIC &&
		    sshdr.asc == 0x80 &&
		    sshdr.ascq < ARRAY_SIZE(myrb_event_msg))
			shost_prपूर्णांकk(KERN_CRIT, cb->host,
				     "Physical drive %d:%d: %s\n",
				     ev_buf->channel, ev_buf->target,
				     myrb_event_msg[sshdr.ascq]);
		अन्यथा
			shost_prपूर्णांकk(KERN_CRIT, cb->host,
				     "Physical drive %d:%d: Sense: %X/%02X/%02X\n",
				     ev_buf->channel, ev_buf->target,
				     sshdr.sense_key, sshdr.asc, sshdr.ascq);
	पूर्ण

	dma_मुक्त_coherent(&cb->pdev->dev, माप(काष्ठा myrb_log_entry),
			  ev_buf, ev_addr);
पूर्ण

/*
 * myrb_get_errtable - retrieves the error table from the controller
 *
 * Executes a type 3 command and logs the error table from the controller.
 */
अटल व्योम myrb_get_errtable(काष्ठा myrb_hba *cb)
अणु
	काष्ठा myrb_cmdblk *cmd_blk = &cb->mcmd_blk;
	जोड़ myrb_cmd_mbox *mbox = &cmd_blk->mbox;
	अचिन्हित लघु status;
	काष्ठा myrb_error_entry old_table[MYRB_MAX_CHANNELS * MYRB_MAX_TARGETS];

	स_नकल(&old_table, cb->err_table, माप(old_table));

	myrb_reset_cmd(cmd_blk);
	mbox->type3.id = MYRB_MCMD_TAG;
	mbox->type3.opcode = MYRB_CMD_GET_ERROR_TABLE;
	mbox->type3.addr = cb->err_table_addr;
	status = myrb_exec_cmd(cb, cmd_blk);
	अगर (status == MYRB_STATUS_SUCCESS) अणु
		काष्ठा myrb_error_entry *table = cb->err_table;
		काष्ठा myrb_error_entry *new, *old;
		माप_प्रकार err_table_offset;
		काष्ठा scsi_device *sdev;

		shost_क्रम_each_device(sdev, cb->host) अणु
			अगर (sdev->channel >= myrb_logical_channel(cb->host))
				जारी;
			err_table_offset = sdev->channel * MYRB_MAX_TARGETS
				+ sdev->id;
			new = table + err_table_offset;
			old = &old_table[err_table_offset];
			अगर (new->parity_err == old->parity_err &&
			    new->soft_err == old->soft_err &&
			    new->hard_err == old->hard_err &&
			    new->misc_err == old->misc_err)
				जारी;
			sdev_prपूर्णांकk(KERN_CRIT, sdev,
				    "Errors: Parity = %d, Soft = %d, Hard = %d, Misc = %d\n",
				    new->parity_err, new->soft_err,
				    new->hard_err, new->misc_err);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * myrb_get_ldev_info - retrieves the logical device table from the controller
 *
 * Executes a type 3 command and updates the logical device table.
 *
 * Return: command status
 */
अटल अचिन्हित लघु myrb_get_ldev_info(काष्ठा myrb_hba *cb)
अणु
	अचिन्हित लघु status;
	पूर्णांक ldev_num, ldev_cnt = cb->enquiry->ldev_count;
	काष्ठा Scsi_Host *shost = cb->host;

	status = myrb_exec_type3(cb, MYRB_CMD_GET_LDEV_INFO,
				 cb->ldev_info_addr);
	अगर (status != MYRB_STATUS_SUCCESS)
		वापस status;

	क्रम (ldev_num = 0; ldev_num < ldev_cnt; ldev_num++) अणु
		काष्ठा myrb_ldev_info *old = शून्य;
		काष्ठा myrb_ldev_info *new = cb->ldev_info_buf + ldev_num;
		काष्ठा scsi_device *sdev;

		sdev = scsi_device_lookup(shost, myrb_logical_channel(shost),
					  ldev_num, 0);
		अगर (!sdev) अणु
			अगर (new->state == MYRB_DEVICE_OFFLINE)
				जारी;
			shost_prपूर्णांकk(KERN_INFO, shost,
				     "Adding Logical Drive %d in state %s\n",
				     ldev_num, myrb_devstate_name(new->state));
			scsi_add_device(shost, myrb_logical_channel(shost),
					ldev_num, 0);
			जारी;
		पूर्ण
		old = sdev->hostdata;
		अगर (new->state != old->state)
			shost_prपूर्णांकk(KERN_INFO, shost,
				     "Logical Drive %d is now %s\n",
				     ldev_num, myrb_devstate_name(new->state));
		अगर (new->wb_enabled != old->wb_enabled)
			sdev_prपूर्णांकk(KERN_INFO, sdev,
				    "Logical Drive is now WRITE %s\n",
				    (new->wb_enabled ? "BACK" : "THRU"));
		स_नकल(old, new, माप(*new));
		scsi_device_put(sdev);
	पूर्ण
	वापस status;
पूर्ण

/*
 * myrb_get_rbld_progress - get rebuild progress inक्रमmation
 *
 * Executes a type 3 command and वापसs the rebuild progress
 * inक्रमmation.
 *
 * Return: command status
 */
अटल अचिन्हित लघु myrb_get_rbld_progress(काष्ठा myrb_hba *cb,
		काष्ठा myrb_rbld_progress *rbld)
अणु
	काष्ठा myrb_cmdblk *cmd_blk = &cb->mcmd_blk;
	जोड़ myrb_cmd_mbox *mbox = &cmd_blk->mbox;
	काष्ठा myrb_rbld_progress *rbld_buf;
	dma_addr_t rbld_addr;
	अचिन्हित लघु status;

	rbld_buf = dma_alloc_coherent(&cb->pdev->dev,
				      माप(काष्ठा myrb_rbld_progress),
				      &rbld_addr, GFP_KERNEL);
	अगर (!rbld_buf)
		वापस MYRB_STATUS_RBLD_NOT_CHECKED;

	myrb_reset_cmd(cmd_blk);
	mbox->type3.id = MYRB_MCMD_TAG;
	mbox->type3.opcode = MYRB_CMD_GET_REBUILD_PROGRESS;
	mbox->type3.addr = rbld_addr;
	status = myrb_exec_cmd(cb, cmd_blk);
	अगर (rbld)
		स_नकल(rbld, rbld_buf, माप(काष्ठा myrb_rbld_progress));
	dma_मुक्त_coherent(&cb->pdev->dev, माप(काष्ठा myrb_rbld_progress),
			  rbld_buf, rbld_addr);
	वापस status;
पूर्ण

/*
 * myrb_update_rbld_progress - updates the rebuild status
 *
 * Updates the rebuild status क्रम the attached logical devices.
 */
अटल व्योम myrb_update_rbld_progress(काष्ठा myrb_hba *cb)
अणु
	काष्ठा myrb_rbld_progress rbld_buf;
	अचिन्हित लघु status;

	status = myrb_get_rbld_progress(cb, &rbld_buf);
	अगर (status == MYRB_NO_STDBY_RBLD_OR_CHECK_IN_PROGRESS &&
	    cb->last_rbld_status == MYRB_STATUS_SUCCESS)
		status = MYRB_STATUS_RBLD_SUCCESS;
	अगर (status != MYRB_NO_STDBY_RBLD_OR_CHECK_IN_PROGRESS) अणु
		अचिन्हित पूर्णांक blocks_करोne =
			rbld_buf.ldev_size - rbld_buf.blocks_left;
		काष्ठा scsi_device *sdev;

		sdev = scsi_device_lookup(cb->host,
					  myrb_logical_channel(cb->host),
					  rbld_buf.ldev_num, 0);
		अगर (!sdev)
			वापस;

		चयन (status) अणु
		हाल MYRB_STATUS_SUCCESS:
			sdev_prपूर्णांकk(KERN_INFO, sdev,
				    "Rebuild in Progress, %d%% completed\n",
				    (100 * (blocks_करोne >> 7))
				    / (rbld_buf.ldev_size >> 7));
			अवरोध;
		हाल MYRB_STATUS_RBLD_FAILED_LDEV_FAILURE:
			sdev_prपूर्णांकk(KERN_INFO, sdev,
				    "Rebuild Failed due to Logical Drive Failure\n");
			अवरोध;
		हाल MYRB_STATUS_RBLD_FAILED_BADBLOCKS:
			sdev_prपूर्णांकk(KERN_INFO, sdev,
				    "Rebuild Failed due to Bad Blocks on Other Drives\n");
			अवरोध;
		हाल MYRB_STATUS_RBLD_FAILED_NEW_DRIVE_FAILED:
			sdev_prपूर्णांकk(KERN_INFO, sdev,
				    "Rebuild Failed due to Failure of Drive Being Rebuilt\n");
			अवरोध;
		हाल MYRB_STATUS_RBLD_SUCCESS:
			sdev_prपूर्णांकk(KERN_INFO, sdev,
				    "Rebuild Completed Successfully\n");
			अवरोध;
		हाल MYRB_STATUS_RBLD_SUCCESS_TERMINATED:
			sdev_prपूर्णांकk(KERN_INFO, sdev,
				     "Rebuild Successfully Terminated\n");
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		scsi_device_put(sdev);
	पूर्ण
	cb->last_rbld_status = status;
पूर्ण

/*
 * myrb_get_cc_progress - retrieve the rebuild status
 *
 * Execute a type 3 Command and fetch the rebuild / consistency check
 * status.
 */
अटल व्योम myrb_get_cc_progress(काष्ठा myrb_hba *cb)
अणु
	काष्ठा myrb_cmdblk *cmd_blk = &cb->mcmd_blk;
	जोड़ myrb_cmd_mbox *mbox = &cmd_blk->mbox;
	काष्ठा myrb_rbld_progress *rbld_buf;
	dma_addr_t rbld_addr;
	अचिन्हित लघु status;

	rbld_buf = dma_alloc_coherent(&cb->pdev->dev,
				      माप(काष्ठा myrb_rbld_progress),
				      &rbld_addr, GFP_KERNEL);
	अगर (!rbld_buf) अणु
		cb->need_cc_status = true;
		वापस;
	पूर्ण
	myrb_reset_cmd(cmd_blk);
	mbox->type3.id = MYRB_MCMD_TAG;
	mbox->type3.opcode = MYRB_CMD_REBUILD_STAT;
	mbox->type3.addr = rbld_addr;
	status = myrb_exec_cmd(cb, cmd_blk);
	अगर (status == MYRB_STATUS_SUCCESS) अणु
		अचिन्हित पूर्णांक ldev_num = rbld_buf->ldev_num;
		अचिन्हित पूर्णांक ldev_size = rbld_buf->ldev_size;
		अचिन्हित पूर्णांक blocks_करोne =
			ldev_size - rbld_buf->blocks_left;
		काष्ठा scsi_device *sdev;

		sdev = scsi_device_lookup(cb->host,
					  myrb_logical_channel(cb->host),
					  ldev_num, 0);
		अगर (sdev) अणु
			sdev_prपूर्णांकk(KERN_INFO, sdev,
				    "Consistency Check in Progress: %d%% completed\n",
				    (100 * (blocks_करोne >> 7))
				    / (ldev_size >> 7));
			scsi_device_put(sdev);
		पूर्ण
	पूर्ण
	dma_मुक्त_coherent(&cb->pdev->dev, माप(काष्ठा myrb_rbld_progress),
			  rbld_buf, rbld_addr);
पूर्ण

/*
 * myrb_bgi_control - updates background initialisation status
 *
 * Executes a type 3B command and updates the background initialisation status
 */
अटल व्योम myrb_bgi_control(काष्ठा myrb_hba *cb)
अणु
	काष्ठा myrb_cmdblk *cmd_blk = &cb->mcmd_blk;
	जोड़ myrb_cmd_mbox *mbox = &cmd_blk->mbox;
	काष्ठा myrb_bgi_status *bgi, *last_bgi;
	dma_addr_t bgi_addr;
	काष्ठा scsi_device *sdev = शून्य;
	अचिन्हित लघु status;

	bgi = dma_alloc_coherent(&cb->pdev->dev, माप(काष्ठा myrb_bgi_status),
				 &bgi_addr, GFP_KERNEL);
	अगर (!bgi) अणु
		shost_prपूर्णांकk(KERN_ERR, cb->host,
			     "Failed to allocate bgi memory\n");
		वापस;
	पूर्ण
	myrb_reset_cmd(cmd_blk);
	mbox->type3B.id = MYRB_DCMD_TAG;
	mbox->type3B.opcode = MYRB_CMD_BGI_CONTROL;
	mbox->type3B.optype = 0x20;
	mbox->type3B.addr = bgi_addr;
	status = myrb_exec_cmd(cb, cmd_blk);
	last_bgi = &cb->bgi_status;
	sdev = scsi_device_lookup(cb->host,
				  myrb_logical_channel(cb->host),
				  bgi->ldev_num, 0);
	चयन (status) अणु
	हाल MYRB_STATUS_SUCCESS:
		चयन (bgi->status) अणु
		हाल MYRB_BGI_INVALID:
			अवरोध;
		हाल MYRB_BGI_STARTED:
			अगर (!sdev)
				अवरोध;
			sdev_prपूर्णांकk(KERN_INFO, sdev,
				    "Background Initialization Started\n");
			अवरोध;
		हाल MYRB_BGI_INPROGRESS:
			अगर (!sdev)
				अवरोध;
			अगर (bgi->blocks_करोne == last_bgi->blocks_करोne &&
			    bgi->ldev_num == last_bgi->ldev_num)
				अवरोध;
			sdev_prपूर्णांकk(KERN_INFO, sdev,
				 "Background Initialization in Progress: %d%% completed\n",
				 (100 * (bgi->blocks_करोne >> 7))
				 / (bgi->ldev_size >> 7));
			अवरोध;
		हाल MYRB_BGI_SUSPENDED:
			अगर (!sdev)
				अवरोध;
			sdev_prपूर्णांकk(KERN_INFO, sdev,
				    "Background Initialization Suspended\n");
			अवरोध;
		हाल MYRB_BGI_CANCELLED:
			अगर (!sdev)
				अवरोध;
			sdev_prपूर्णांकk(KERN_INFO, sdev,
				    "Background Initialization Cancelled\n");
			अवरोध;
		पूर्ण
		स_नकल(&cb->bgi_status, bgi, माप(काष्ठा myrb_bgi_status));
		अवरोध;
	हाल MYRB_STATUS_BGI_SUCCESS:
		अगर (sdev && cb->bgi_status.status == MYRB_BGI_INPROGRESS)
			sdev_prपूर्णांकk(KERN_INFO, sdev,
				    "Background Initialization Completed Successfully\n");
		cb->bgi_status.status = MYRB_BGI_INVALID;
		अवरोध;
	हाल MYRB_STATUS_BGI_ABORTED:
		अगर (sdev && cb->bgi_status.status == MYRB_BGI_INPROGRESS)
			sdev_prपूर्णांकk(KERN_INFO, sdev,
				    "Background Initialization Aborted\n");
		fallthrough;
	हाल MYRB_STATUS_NO_BGI_INPROGRESS:
		cb->bgi_status.status = MYRB_BGI_INVALID;
		अवरोध;
	पूर्ण
	अगर (sdev)
		scsi_device_put(sdev);
	dma_मुक्त_coherent(&cb->pdev->dev, माप(काष्ठा myrb_bgi_status),
			  bgi, bgi_addr);
पूर्ण

/*
 * myrb_hba_enquiry - updates the controller status
 *
 * Executes a DAC_V1_Enquiry command and updates the controller status.
 *
 * Return: command status
 */
अटल अचिन्हित लघु myrb_hba_enquiry(काष्ठा myrb_hba *cb)
अणु
	काष्ठा myrb_enquiry old, *new;
	अचिन्हित लघु status;

	स_नकल(&old, cb->enquiry, माप(काष्ठा myrb_enquiry));

	status = myrb_exec_type3(cb, MYRB_CMD_ENQUIRY, cb->enquiry_addr);
	अगर (status != MYRB_STATUS_SUCCESS)
		वापस status;

	new = cb->enquiry;
	अगर (new->ldev_count > old.ldev_count) अणु
		पूर्णांक ldev_num = old.ldev_count - 1;

		जबतक (++ldev_num < new->ldev_count)
			shost_prपूर्णांकk(KERN_CRIT, cb->host,
				     "Logical Drive %d Now Exists\n",
				     ldev_num);
	पूर्ण
	अगर (new->ldev_count < old.ldev_count) अणु
		पूर्णांक ldev_num = new->ldev_count - 1;

		जबतक (++ldev_num < old.ldev_count)
			shost_prपूर्णांकk(KERN_CRIT, cb->host,
				     "Logical Drive %d No Longer Exists\n",
				     ldev_num);
	पूर्ण
	अगर (new->status.deferred != old.status.deferred)
		shost_prपूर्णांकk(KERN_CRIT, cb->host,
			     "Deferred Write Error Flag is now %s\n",
			     (new->status.deferred ? "TRUE" : "FALSE"));
	अगर (new->ev_seq != old.ev_seq) अणु
		cb->new_ev_seq = new->ev_seq;
		cb->need_err_info = true;
		shost_prपूर्णांकk(KERN_INFO, cb->host,
			     "Event log %d/%d (%d/%d) available\n",
			     cb->old_ev_seq, cb->new_ev_seq,
			     old.ev_seq, new->ev_seq);
	पूर्ण
	अगर ((new->ldev_critical > 0 &&
	     new->ldev_critical != old.ldev_critical) ||
	    (new->ldev_offline > 0 &&
	     new->ldev_offline != old.ldev_offline) ||
	    (new->ldev_count != old.ldev_count)) अणु
		shost_prपूर्णांकk(KERN_INFO, cb->host,
			     "Logical drive count changed (%d/%d/%d)\n",
			     new->ldev_critical,
			     new->ldev_offline,
			     new->ldev_count);
		cb->need_ldev_info = true;
	पूर्ण
	अगर (new->pdev_dead > 0 ||
	    new->pdev_dead != old.pdev_dead ||
	    समय_after_eq(jअगरfies, cb->secondary_monitor_समय
			  + MYRB_SECONDARY_MONITOR_INTERVAL)) अणु
		cb->need_bgi_status = cb->bgi_status_supported;
		cb->secondary_monitor_समय = jअगरfies;
	पूर्ण
	अगर (new->rbld == MYRB_STDBY_RBLD_IN_PROGRESS ||
	    new->rbld == MYRB_BG_RBLD_IN_PROGRESS ||
	    old.rbld == MYRB_STDBY_RBLD_IN_PROGRESS ||
	    old.rbld == MYRB_BG_RBLD_IN_PROGRESS) अणु
		cb->need_rbld = true;
		cb->rbld_first = (new->ldev_critical < old.ldev_critical);
	पूर्ण
	अगर (old.rbld == MYRB_BG_CHECK_IN_PROGRESS)
		चयन (new->rbld) अणु
		हाल MYRB_NO_STDBY_RBLD_OR_CHECK_IN_PROGRESS:
			shost_prपूर्णांकk(KERN_INFO, cb->host,
				     "Consistency Check Completed Successfully\n");
			अवरोध;
		हाल MYRB_STDBY_RBLD_IN_PROGRESS:
		हाल MYRB_BG_RBLD_IN_PROGRESS:
			अवरोध;
		हाल MYRB_BG_CHECK_IN_PROGRESS:
			cb->need_cc_status = true;
			अवरोध;
		हाल MYRB_STDBY_RBLD_COMPLETED_WITH_ERROR:
			shost_prपूर्णांकk(KERN_INFO, cb->host,
				     "Consistency Check Completed with Error\n");
			अवरोध;
		हाल MYRB_BG_RBLD_OR_CHECK_FAILED_DRIVE_FAILED:
			shost_prपूर्णांकk(KERN_INFO, cb->host,
				     "Consistency Check Failed - Physical Device Failed\n");
			अवरोध;
		हाल MYRB_BG_RBLD_OR_CHECK_FAILED_LDEV_FAILED:
			shost_prपूर्णांकk(KERN_INFO, cb->host,
				     "Consistency Check Failed - Logical Drive Failed\n");
			अवरोध;
		हाल MYRB_BG_RBLD_OR_CHECK_FAILED_OTHER:
			shost_prपूर्णांकk(KERN_INFO, cb->host,
				     "Consistency Check Failed - Other Causes\n");
			अवरोध;
		हाल MYRB_BG_RBLD_OR_CHECK_SUCCESS_TERMINATED:
			shost_prपूर्णांकk(KERN_INFO, cb->host,
				     "Consistency Check Successfully Terminated\n");
			अवरोध;
		पूर्ण
	अन्यथा अगर (new->rbld == MYRB_BG_CHECK_IN_PROGRESS)
		cb->need_cc_status = true;

	वापस MYRB_STATUS_SUCCESS;
पूर्ण

/*
 * myrb_set_pdev_state - sets the device state क्रम a physical device
 *
 * Return: command status
 */
अटल अचिन्हित लघु myrb_set_pdev_state(काष्ठा myrb_hba *cb,
		काष्ठा scsi_device *sdev, क्रमागत myrb_devstate state)
अणु
	काष्ठा myrb_cmdblk *cmd_blk = &cb->dcmd_blk;
	जोड़ myrb_cmd_mbox *mbox = &cmd_blk->mbox;
	अचिन्हित लघु status;

	mutex_lock(&cb->dcmd_mutex);
	mbox->type3D.opcode = MYRB_CMD_START_DEVICE;
	mbox->type3D.id = MYRB_DCMD_TAG;
	mbox->type3D.channel = sdev->channel;
	mbox->type3D.target = sdev->id;
	mbox->type3D.state = state & 0x1F;
	status = myrb_exec_cmd(cb, cmd_blk);
	mutex_unlock(&cb->dcmd_mutex);

	वापस status;
पूर्ण

/*
 * myrb_enable_mmio - enables the Memory Mailbox Interface
 *
 * PD and P controller types have no memory mailbox, but still need the
 * other dma mapped memory.
 *
 * Return: true on success, false otherwise.
 */
अटल bool myrb_enable_mmio(काष्ठा myrb_hba *cb, mbox_mmio_init_t mmio_init_fn)
अणु
	व्योम __iomem *base = cb->io_base;
	काष्ठा pci_dev *pdev = cb->pdev;
	माप_प्रकार err_table_size;
	माप_प्रकार ldev_info_size;
	जोड़ myrb_cmd_mbox *cmd_mbox_mem;
	काष्ठा myrb_stat_mbox *stat_mbox_mem;
	जोड़ myrb_cmd_mbox mbox;
	अचिन्हित लघु status;

	स_रखो(&mbox, 0, माप(जोड़ myrb_cmd_mbox));

	अगर (dma_set_mask(&pdev->dev, DMA_BIT_MASK(32))) अणु
		dev_err(&pdev->dev, "DMA mask out of range\n");
		वापस false;
	पूर्ण

	cb->enquiry = dma_alloc_coherent(&pdev->dev,
					 माप(काष्ठा myrb_enquiry),
					 &cb->enquiry_addr, GFP_KERNEL);
	अगर (!cb->enquiry)
		वापस false;

	err_table_size = माप(काष्ठा myrb_error_entry) *
		MYRB_MAX_CHANNELS * MYRB_MAX_TARGETS;
	cb->err_table = dma_alloc_coherent(&pdev->dev, err_table_size,
					   &cb->err_table_addr, GFP_KERNEL);
	अगर (!cb->err_table)
		वापस false;

	ldev_info_size = माप(काष्ठा myrb_ldev_info) * MYRB_MAX_LDEVS;
	cb->ldev_info_buf = dma_alloc_coherent(&pdev->dev, ldev_info_size,
					       &cb->ldev_info_addr, GFP_KERNEL);
	अगर (!cb->ldev_info_buf)
		वापस false;

	/*
	 * Skip mailbox initialisation क्रम PD and P Controllers
	 */
	अगर (!mmio_init_fn)
		वापस true;

	/* These are the base addresses क्रम the command memory mailbox array */
	cb->cmd_mbox_size =  MYRB_CMD_MBOX_COUNT * माप(जोड़ myrb_cmd_mbox);
	cb->first_cmd_mbox = dma_alloc_coherent(&pdev->dev,
						cb->cmd_mbox_size,
						&cb->cmd_mbox_addr,
						GFP_KERNEL);
	अगर (!cb->first_cmd_mbox)
		वापस false;

	cmd_mbox_mem = cb->first_cmd_mbox;
	cmd_mbox_mem += MYRB_CMD_MBOX_COUNT - 1;
	cb->last_cmd_mbox = cmd_mbox_mem;
	cb->next_cmd_mbox = cb->first_cmd_mbox;
	cb->prev_cmd_mbox1 = cb->last_cmd_mbox;
	cb->prev_cmd_mbox2 = cb->last_cmd_mbox - 1;

	/* These are the base addresses क्रम the status memory mailbox array */
	cb->stat_mbox_size = MYRB_STAT_MBOX_COUNT *
	    माप(काष्ठा myrb_stat_mbox);
	cb->first_stat_mbox = dma_alloc_coherent(&pdev->dev,
						 cb->stat_mbox_size,
						 &cb->stat_mbox_addr,
						 GFP_KERNEL);
	अगर (!cb->first_stat_mbox)
		वापस false;

	stat_mbox_mem = cb->first_stat_mbox;
	stat_mbox_mem += MYRB_STAT_MBOX_COUNT - 1;
	cb->last_stat_mbox = stat_mbox_mem;
	cb->next_stat_mbox = cb->first_stat_mbox;

	/* Enable the Memory Mailbox Interface. */
	cb->dual_mode_पूर्णांकerface = true;
	mbox.typeX.opcode = 0x2B;
	mbox.typeX.id = 0;
	mbox.typeX.opcode2 = 0x14;
	mbox.typeX.cmd_mbox_addr = cb->cmd_mbox_addr;
	mbox.typeX.stat_mbox_addr = cb->stat_mbox_addr;

	status = mmio_init_fn(pdev, base, &mbox);
	अगर (status != MYRB_STATUS_SUCCESS) अणु
		cb->dual_mode_पूर्णांकerface = false;
		mbox.typeX.opcode2 = 0x10;
		status = mmio_init_fn(pdev, base, &mbox);
		अगर (status != MYRB_STATUS_SUCCESS) अणु
			dev_err(&pdev->dev,
				"Failed to enable mailbox, statux %02X\n",
				status);
			वापस false;
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

/*
 * myrb_get_hba_config - पढ़ोs the configuration inक्रमmation
 *
 * Reads the configuration inक्रमmation from the controller and
 * initializes the controller काष्ठाure.
 *
 * Return: 0 on success, त्रुटि_सं otherwise
 */
अटल पूर्णांक myrb_get_hba_config(काष्ठा myrb_hba *cb)
अणु
	काष्ठा myrb_enquiry2 *enquiry2;
	dma_addr_t enquiry2_addr;
	काष्ठा myrb_config2 *config2;
	dma_addr_t config2_addr;
	काष्ठा Scsi_Host *shost = cb->host;
	काष्ठा pci_dev *pdev = cb->pdev;
	पूर्णांक pchan_max = 0, pchan_cur = 0;
	अचिन्हित लघु status;
	पूर्णांक ret = -ENODEV, memsize = 0;

	enquiry2 = dma_alloc_coherent(&pdev->dev, माप(काष्ठा myrb_enquiry2),
				      &enquiry2_addr, GFP_KERNEL);
	अगर (!enquiry2) अणु
		shost_prपूर्णांकk(KERN_ERR, cb->host,
			     "Failed to allocate V1 enquiry2 memory\n");
		वापस -ENOMEM;
	पूर्ण
	config2 = dma_alloc_coherent(&pdev->dev, माप(काष्ठा myrb_config2),
				     &config2_addr, GFP_KERNEL);
	अगर (!config2) अणु
		shost_prपूर्णांकk(KERN_ERR, cb->host,
			     "Failed to allocate V1 config2 memory\n");
		dma_मुक्त_coherent(&pdev->dev, माप(काष्ठा myrb_enquiry2),
				  enquiry2, enquiry2_addr);
		वापस -ENOMEM;
	पूर्ण
	mutex_lock(&cb->dma_mutex);
	status = myrb_hba_enquiry(cb);
	mutex_unlock(&cb->dma_mutex);
	अगर (status != MYRB_STATUS_SUCCESS) अणु
		shost_prपूर्णांकk(KERN_WARNING, cb->host,
			     "Failed it issue V1 Enquiry\n");
		जाओ out_मुक्त;
	पूर्ण

	status = myrb_exec_type3(cb, MYRB_CMD_ENQUIRY2, enquiry2_addr);
	अगर (status != MYRB_STATUS_SUCCESS) अणु
		shost_prपूर्णांकk(KERN_WARNING, cb->host,
			     "Failed to issue V1 Enquiry2\n");
		जाओ out_मुक्त;
	पूर्ण

	status = myrb_exec_type3(cb, MYRB_CMD_READ_CONFIG2, config2_addr);
	अगर (status != MYRB_STATUS_SUCCESS) अणु
		shost_prपूर्णांकk(KERN_WARNING, cb->host,
			     "Failed to issue ReadConfig2\n");
		जाओ out_मुक्त;
	पूर्ण

	status = myrb_get_ldev_info(cb);
	अगर (status != MYRB_STATUS_SUCCESS) अणु
		shost_prपूर्णांकk(KERN_WARNING, cb->host,
			     "Failed to get logical drive information\n");
		जाओ out_मुक्त;
	पूर्ण

	/*
	 * Initialize the Controller Model Name and Full Model Name fields.
	 */
	चयन (enquiry2->hw.sub_model) अणु
	हाल DAC960_V1_P_PD_PU:
		अगर (enquiry2->scsi_cap.bus_speed == MYRB_SCSI_SPEED_ULTRA)
			म_नकल(cb->model_name, "DAC960PU");
		अन्यथा
			म_नकल(cb->model_name, "DAC960PD");
		अवरोध;
	हाल DAC960_V1_PL:
		म_नकल(cb->model_name, "DAC960PL");
		अवरोध;
	हाल DAC960_V1_PG:
		म_नकल(cb->model_name, "DAC960PG");
		अवरोध;
	हाल DAC960_V1_PJ:
		म_नकल(cb->model_name, "DAC960PJ");
		अवरोध;
	हाल DAC960_V1_PR:
		म_नकल(cb->model_name, "DAC960PR");
		अवरोध;
	हाल DAC960_V1_PT:
		म_नकल(cb->model_name, "DAC960PT");
		अवरोध;
	हाल DAC960_V1_PTL0:
		म_नकल(cb->model_name, "DAC960PTL0");
		अवरोध;
	हाल DAC960_V1_PRL:
		म_नकल(cb->model_name, "DAC960PRL");
		अवरोध;
	हाल DAC960_V1_PTL1:
		म_नकल(cb->model_name, "DAC960PTL1");
		अवरोध;
	हाल DAC960_V1_1164P:
		म_नकल(cb->model_name, "eXtremeRAID 1100");
		अवरोध;
	शेष:
		shost_prपूर्णांकk(KERN_WARNING, cb->host,
			     "Unknown Model %X\n",
			     enquiry2->hw.sub_model);
		जाओ out;
	पूर्ण
	/*
	 * Initialize the Controller Firmware Version field and verअगरy that it
	 * is a supported firmware version.
	 * The supported firmware versions are:
	 *
	 * DAC1164P		    5.06 and above
	 * DAC960PTL/PRL/PJ/PG	    4.06 and above
	 * DAC960PU/PD/PL	    3.51 and above
	 * DAC960PU/PD/PL/P	    2.73 and above
	 */
#अगर defined(CONFIG_ALPHA)
	/*
	 * DEC Alpha machines were often equipped with DAC960 cards that were
	 * OEMed from Mylex, and had their own custom firmware. Version 2.70,
	 * the last custom FW revision to be released by DEC क्रम these older
	 * controllers, appears to work quite well with this driver.
	 *
	 * Cards tested successfully were several versions each of the PD and
	 * PU, called by DEC the KZPSC and KZPAC, respectively, and having
	 * the Manufacturer Numbers (from Mylex), usually on a sticker on the
	 * back of the board, of:
	 *
	 * KZPSC:  D040347 (1-channel) or D040348 (2-channel)
	 *         or D040349 (3-channel)
	 * KZPAC:  D040395 (1-channel) or D040396 (2-channel)
	 *         or D040397 (3-channel)
	 */
# define FIRMWARE_27X	"2.70"
#अन्यथा
# define FIRMWARE_27X	"2.73"
#पूर्ण_अगर

	अगर (enquiry2->fw.major_version == 0) अणु
		enquiry2->fw.major_version = cb->enquiry->fw_major_version;
		enquiry2->fw.minor_version = cb->enquiry->fw_minor_version;
		enquiry2->fw.firmware_type = '0';
		enquiry2->fw.turn_id = 0;
	पूर्ण
	snम_लिखो(cb->fw_version, माप(cb->fw_version),
		"%u.%02u-%c-%02u",
		enquiry2->fw.major_version,
		enquiry2->fw.minor_version,
		enquiry2->fw.firmware_type,
		enquiry2->fw.turn_id);
	अगर (!((enquiry2->fw.major_version == 5 &&
	       enquiry2->fw.minor_version >= 6) ||
	      (enquiry2->fw.major_version == 4 &&
	       enquiry2->fw.minor_version >= 6) ||
	      (enquiry2->fw.major_version == 3 &&
	       enquiry2->fw.minor_version >= 51) ||
	      (enquiry2->fw.major_version == 2 &&
	       म_भेद(cb->fw_version, FIRMWARE_27X) >= 0))) अणु
		shost_prपूर्णांकk(KERN_WARNING, cb->host,
			"Firmware Version '%s' unsupported\n",
			cb->fw_version);
		जाओ out;
	पूर्ण
	/*
	 * Initialize the Channels, Tarमाला_लो, Memory Size, and SAF-TE
	 * Enclosure Management Enabled fields.
	 */
	चयन (enquiry2->hw.model) अणु
	हाल MYRB_5_CHANNEL_BOARD:
		pchan_max = 5;
		अवरोध;
	हाल MYRB_3_CHANNEL_BOARD:
	हाल MYRB_3_CHANNEL_ASIC_DAC:
		pchan_max = 3;
		अवरोध;
	हाल MYRB_2_CHANNEL_BOARD:
		pchan_max = 2;
		अवरोध;
	शेष:
		pchan_max = enquiry2->cfg_chan;
		अवरोध;
	पूर्ण
	pchan_cur = enquiry2->cur_chan;
	अगर (enquiry2->scsi_cap.bus_width == MYRB_WIDTH_WIDE_32BIT)
		cb->bus_width = 32;
	अन्यथा अगर (enquiry2->scsi_cap.bus_width == MYRB_WIDTH_WIDE_16BIT)
		cb->bus_width = 16;
	अन्यथा
		cb->bus_width = 8;
	cb->ldev_block_size = enquiry2->ldev_block_size;
	shost->max_channel = pchan_cur;
	shost->max_id = enquiry2->max_tarमाला_लो;
	memsize = enquiry2->mem_size >> 20;
	cb->safte_enabled = (enquiry2->fault_mgmt == MYRB_FAULT_SAFTE);
	/*
	 * Initialize the Controller Queue Depth, Driver Queue Depth,
	 * Logical Drive Count, Maximum Blocks per Command, Controller
	 * Scatter/Gather Limit, and Driver Scatter/Gather Limit.
	 * The Driver Queue Depth must be at most one less than the
	 * Controller Queue Depth to allow क्रम an स्वतःmatic drive
	 * rebuild operation.
	 */
	shost->can_queue = cb->enquiry->max_tcq;
	अगर (shost->can_queue < 3)
		shost->can_queue = enquiry2->max_cmds;
	अगर (shost->can_queue < 3)
		/* Play safe and disable TCQ */
		shost->can_queue = 1;

	अगर (shost->can_queue > MYRB_CMD_MBOX_COUNT - 2)
		shost->can_queue = MYRB_CMD_MBOX_COUNT - 2;
	shost->max_sectors = enquiry2->max_sectors;
	shost->sg_tablesize = enquiry2->max_sge;
	अगर (shost->sg_tablesize > MYRB_SCATTER_GATHER_LIMIT)
		shost->sg_tablesize = MYRB_SCATTER_GATHER_LIMIT;
	/*
	 * Initialize the Stripe Size, Segment Size, and Geometry Translation.
	 */
	cb->stripe_size = config2->blocks_per_stripe * config2->block_factor
		>> (10 - MYRB_BLKSIZE_BITS);
	cb->segment_size = config2->blocks_per_cacheline * config2->block_factor
		>> (10 - MYRB_BLKSIZE_BITS);
	/* Assume 255/63 translation */
	cb->ldev_geom_heads = 255;
	cb->ldev_geom_sectors = 63;
	अगर (config2->drive_geometry) अणु
		cb->ldev_geom_heads = 128;
		cb->ldev_geom_sectors = 32;
	पूर्ण

	/*
	 * Initialize the Background Initialization Status.
	 */
	अगर ((cb->fw_version[0] == '4' &&
	     म_भेद(cb->fw_version, "4.08") >= 0) ||
	    (cb->fw_version[0] == '5' &&
	     म_भेद(cb->fw_version, "5.08") >= 0)) अणु
		cb->bgi_status_supported = true;
		myrb_bgi_control(cb);
	पूर्ण
	cb->last_rbld_status = MYRB_NO_STDBY_RBLD_OR_CHECK_IN_PROGRESS;
	ret = 0;

out:
	shost_prपूर्णांकk(KERN_INFO, cb->host,
		"Configuring %s PCI RAID Controller\n", cb->model_name);
	shost_prपूर्णांकk(KERN_INFO, cb->host,
		"  Firmware Version: %s, Memory Size: %dMB\n",
		cb->fw_version, memsize);
	अगर (cb->io_addr == 0)
		shost_prपूर्णांकk(KERN_INFO, cb->host,
			"  I/O Address: n/a, PCI Address: 0x%lX, IRQ Channel: %d\n",
			(अचिन्हित दीर्घ)cb->pci_addr, cb->irq);
	अन्यथा
		shost_prपूर्णांकk(KERN_INFO, cb->host,
			"  I/O Address: 0x%lX, PCI Address: 0x%lX, IRQ Channel: %d\n",
			(अचिन्हित दीर्घ)cb->io_addr, (अचिन्हित दीर्घ)cb->pci_addr,
			cb->irq);
	shost_prपूर्णांकk(KERN_INFO, cb->host,
		"  Controller Queue Depth: %d, Maximum Blocks per Command: %d\n",
		cb->host->can_queue, cb->host->max_sectors);
	shost_prपूर्णांकk(KERN_INFO, cb->host,
		     "  Driver Queue Depth: %d, Scatter/Gather Limit: %d of %d Segments\n",
		     cb->host->can_queue, cb->host->sg_tablesize,
		     MYRB_SCATTER_GATHER_LIMIT);
	shost_prपूर्णांकk(KERN_INFO, cb->host,
		     "  Stripe Size: %dKB, Segment Size: %dKB, BIOS Geometry: %d/%d%s\n",
		     cb->stripe_size, cb->segment_size,
		     cb->ldev_geom_heads, cb->ldev_geom_sectors,
		     cb->safte_enabled ?
		     "  SAF-TE Enclosure Management Enabled" : "");
	shost_prपूर्णांकk(KERN_INFO, cb->host,
		     "  Physical: %d/%d channels %d/%d/%d devices\n",
		     pchan_cur, pchan_max, 0, cb->enquiry->pdev_dead,
		     cb->host->max_id);

	shost_prपूर्णांकk(KERN_INFO, cb->host,
		     "  Logical: 1/1 channels, %d/%d disks\n",
		     cb->enquiry->ldev_count, MYRB_MAX_LDEVS);

out_मुक्त:
	dma_मुक्त_coherent(&pdev->dev, माप(काष्ठा myrb_enquiry2),
			  enquiry2, enquiry2_addr);
	dma_मुक्त_coherent(&pdev->dev, माप(काष्ठा myrb_config2),
			  config2, config2_addr);

	वापस ret;
पूर्ण

/*
 * myrb_unmap - unmaps controller काष्ठाures
 */
अटल व्योम myrb_unmap(काष्ठा myrb_hba *cb)
अणु
	अगर (cb->ldev_info_buf) अणु
		माप_प्रकार ldev_info_size = माप(काष्ठा myrb_ldev_info) *
			MYRB_MAX_LDEVS;
		dma_मुक्त_coherent(&cb->pdev->dev, ldev_info_size,
				  cb->ldev_info_buf, cb->ldev_info_addr);
		cb->ldev_info_buf = शून्य;
	पूर्ण
	अगर (cb->err_table) अणु
		माप_प्रकार err_table_size = माप(काष्ठा myrb_error_entry) *
			MYRB_MAX_CHANNELS * MYRB_MAX_TARGETS;
		dma_मुक्त_coherent(&cb->pdev->dev, err_table_size,
				  cb->err_table, cb->err_table_addr);
		cb->err_table = शून्य;
	पूर्ण
	अगर (cb->enquiry) अणु
		dma_मुक्त_coherent(&cb->pdev->dev, माप(काष्ठा myrb_enquiry),
				  cb->enquiry, cb->enquiry_addr);
		cb->enquiry = शून्य;
	पूर्ण
	अगर (cb->first_stat_mbox) अणु
		dma_मुक्त_coherent(&cb->pdev->dev, cb->stat_mbox_size,
				  cb->first_stat_mbox, cb->stat_mbox_addr);
		cb->first_stat_mbox = शून्य;
	पूर्ण
	अगर (cb->first_cmd_mbox) अणु
		dma_मुक्त_coherent(&cb->pdev->dev, cb->cmd_mbox_size,
				  cb->first_cmd_mbox, cb->cmd_mbox_addr);
		cb->first_cmd_mbox = शून्य;
	पूर्ण
पूर्ण

/*
 * myrb_cleanup - cleanup controller काष्ठाures
 */
अटल व्योम myrb_cleanup(काष्ठा myrb_hba *cb)
अणु
	काष्ठा pci_dev *pdev = cb->pdev;

	/* Free the memory mailbox, status, and related काष्ठाures */
	myrb_unmap(cb);

	अगर (cb->mmio_base) अणु
		cb->disable_पूर्णांकr(cb->io_base);
		iounmap(cb->mmio_base);
	पूर्ण
	अगर (cb->irq)
		मुक्त_irq(cb->irq, cb);
	अगर (cb->io_addr)
		release_region(cb->io_addr, 0x80);
	pci_set_drvdata(pdev, शून्य);
	pci_disable_device(pdev);
	scsi_host_put(cb->host);
पूर्ण

अटल पूर्णांक myrb_host_reset(काष्ठा scsi_cmnd *scmd)
अणु
	काष्ठा Scsi_Host *shost = scmd->device->host;
	काष्ठा myrb_hba *cb = shost_priv(shost);

	cb->reset(cb->io_base);
	वापस SUCCESS;
पूर्ण

अटल पूर्णांक myrb_pthru_queuecommand(काष्ठा Scsi_Host *shost,
		काष्ठा scsi_cmnd *scmd)
अणु
	काष्ठा myrb_hba *cb = shost_priv(shost);
	काष्ठा myrb_cmdblk *cmd_blk = scsi_cmd_priv(scmd);
	जोड़ myrb_cmd_mbox *mbox = &cmd_blk->mbox;
	काष्ठा myrb_dcdb *dcdb;
	dma_addr_t dcdb_addr;
	काष्ठा scsi_device *sdev = scmd->device;
	काष्ठा scatterlist *sgl;
	अचिन्हित दीर्घ flags;
	पूर्णांक nsge;

	myrb_reset_cmd(cmd_blk);
	dcdb = dma_pool_alloc(cb->dcdb_pool, GFP_ATOMIC, &dcdb_addr);
	अगर (!dcdb)
		वापस SCSI_MLQUEUE_HOST_BUSY;
	nsge = scsi_dma_map(scmd);
	अगर (nsge > 1) अणु
		dma_pool_मुक्त(cb->dcdb_pool, dcdb, dcdb_addr);
		scmd->result = (DID_ERROR << 16);
		scmd->scsi_करोne(scmd);
		वापस 0;
	पूर्ण

	mbox->type3.opcode = MYRB_CMD_DCDB;
	mbox->type3.id = scmd->request->tag + 3;
	mbox->type3.addr = dcdb_addr;
	dcdb->channel = sdev->channel;
	dcdb->target = sdev->id;
	चयन (scmd->sc_data_direction) अणु
	हाल DMA_NONE:
		dcdb->data_xfer = MYRB_DCDB_XFER_NONE;
		अवरोध;
	हाल DMA_TO_DEVICE:
		dcdb->data_xfer = MYRB_DCDB_XFER_SYSTEM_TO_DEVICE;
		अवरोध;
	हाल DMA_FROM_DEVICE:
		dcdb->data_xfer = MYRB_DCDB_XFER_DEVICE_TO_SYSTEM;
		अवरोध;
	शेष:
		dcdb->data_xfer = MYRB_DCDB_XFER_ILLEGAL;
		अवरोध;
	पूर्ण
	dcdb->early_status = false;
	अगर (scmd->request->समयout <= 10)
		dcdb->समयout = MYRB_DCDB_TMO_10_SECS;
	अन्यथा अगर (scmd->request->समयout <= 60)
		dcdb->समयout = MYRB_DCDB_TMO_60_SECS;
	अन्यथा अगर (scmd->request->समयout <= 600)
		dcdb->समयout = MYRB_DCDB_TMO_10_MINS;
	अन्यथा
		dcdb->समयout = MYRB_DCDB_TMO_24_HRS;
	dcdb->no_स्वतःsense = false;
	dcdb->allow_disconnect = true;
	sgl = scsi_sglist(scmd);
	dcdb->dma_addr = sg_dma_address(sgl);
	अगर (sg_dma_len(sgl) > अच_लघु_उच्च) अणु
		dcdb->xfer_len_lo = sg_dma_len(sgl) & 0xffff;
		dcdb->xfer_len_hi4 = sg_dma_len(sgl) >> 16;
	पूर्ण अन्यथा अणु
		dcdb->xfer_len_lo = sg_dma_len(sgl);
		dcdb->xfer_len_hi4 = 0;
	पूर्ण
	dcdb->cdb_len = scmd->cmd_len;
	dcdb->sense_len = माप(dcdb->sense);
	स_नकल(&dcdb->cdb, scmd->cmnd, scmd->cmd_len);

	spin_lock_irqsave(&cb->queue_lock, flags);
	cb->qcmd(cb, cmd_blk);
	spin_unlock_irqrestore(&cb->queue_lock, flags);
	वापस 0;
पूर्ण

अटल व्योम myrb_inquiry(काष्ठा myrb_hba *cb,
		काष्ठा scsi_cmnd *scmd)
अणु
	अचिन्हित अक्षर inq[36] = अणु
		0x00, 0x00, 0x03, 0x02, 0x20, 0x00, 0x01, 0x00,
		0x4d, 0x59, 0x4c, 0x45, 0x58, 0x20, 0x20, 0x20,
		0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
		0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
		0x20, 0x20, 0x20, 0x20,
	पूर्ण;

	अगर (cb->bus_width > 16)
		inq[7] |= 1 << 6;
	अगर (cb->bus_width > 8)
		inq[7] |= 1 << 5;
	स_नकल(&inq[16], cb->model_name, 16);
	स_नकल(&inq[32], cb->fw_version, 1);
	स_नकल(&inq[33], &cb->fw_version[2], 2);
	स_नकल(&inq[35], &cb->fw_version[7], 1);

	scsi_sg_copy_from_buffer(scmd, (व्योम *)inq, 36);
पूर्ण

अटल व्योम
myrb_mode_sense(काष्ठा myrb_hba *cb, काष्ठा scsi_cmnd *scmd,
		काष्ठा myrb_ldev_info *ldev_info)
अणु
	अचिन्हित अक्षर modes[32], *mode_pg;
	bool dbd;
	माप_प्रकार mode_len;

	dbd = (scmd->cmnd[1] & 0x08) == 0x08;
	अगर (dbd) अणु
		mode_len = 24;
		mode_pg = &modes[4];
	पूर्ण अन्यथा अणु
		mode_len = 32;
		mode_pg = &modes[12];
	पूर्ण
	स_रखो(modes, 0, माप(modes));
	modes[0] = mode_len - 1;
	अगर (!dbd) अणु
		अचिन्हित अक्षर *block_desc = &modes[4];

		modes[3] = 8;
		put_unaligned_be32(ldev_info->size, &block_desc[0]);
		put_unaligned_be32(cb->ldev_block_size, &block_desc[5]);
	पूर्ण
	mode_pg[0] = 0x08;
	mode_pg[1] = 0x12;
	अगर (ldev_info->wb_enabled)
		mode_pg[2] |= 0x04;
	अगर (cb->segment_size) अणु
		mode_pg[2] |= 0x08;
		put_unaligned_be16(cb->segment_size, &mode_pg[14]);
	पूर्ण

	scsi_sg_copy_from_buffer(scmd, modes, mode_len);
पूर्ण

अटल व्योम myrb_request_sense(काष्ठा myrb_hba *cb,
		काष्ठा scsi_cmnd *scmd)
अणु
	scsi_build_sense_buffer(0, scmd->sense_buffer,
				NO_SENSE, 0, 0);
	scsi_sg_copy_from_buffer(scmd, scmd->sense_buffer,
				 SCSI_SENSE_BUFFERSIZE);
पूर्ण

अटल व्योम myrb_पढ़ो_capacity(काष्ठा myrb_hba *cb, काष्ठा scsi_cmnd *scmd,
		काष्ठा myrb_ldev_info *ldev_info)
अणु
	अचिन्हित अक्षर data[8];

	dev_dbg(&scmd->device->sdev_gendev,
		"Capacity %u, blocksize %u\n",
		ldev_info->size, cb->ldev_block_size);
	put_unaligned_be32(ldev_info->size - 1, &data[0]);
	put_unaligned_be32(cb->ldev_block_size, &data[4]);
	scsi_sg_copy_from_buffer(scmd, data, 8);
पूर्ण

अटल पूर्णांक myrb_ldev_queuecommand(काष्ठा Scsi_Host *shost,
		काष्ठा scsi_cmnd *scmd)
अणु
	काष्ठा myrb_hba *cb = shost_priv(shost);
	काष्ठा myrb_cmdblk *cmd_blk = scsi_cmd_priv(scmd);
	जोड़ myrb_cmd_mbox *mbox = &cmd_blk->mbox;
	काष्ठा myrb_ldev_info *ldev_info;
	काष्ठा scsi_device *sdev = scmd->device;
	काष्ठा scatterlist *sgl;
	अचिन्हित दीर्घ flags;
	u64 lba;
	u32 block_cnt;
	पूर्णांक nsge;

	ldev_info = sdev->hostdata;
	अगर (ldev_info->state != MYRB_DEVICE_ONLINE &&
	    ldev_info->state != MYRB_DEVICE_WO) अणु
		dev_dbg(&shost->shost_gendev, "ldev %u in state %x, skip\n",
			sdev->id, ldev_info ? ldev_info->state : 0xff);
		scmd->result = (DID_BAD_TARGET << 16);
		scmd->scsi_करोne(scmd);
		वापस 0;
	पूर्ण
	चयन (scmd->cmnd[0]) अणु
	हाल TEST_UNIT_READY:
		scmd->result = (DID_OK << 16);
		scmd->scsi_करोne(scmd);
		वापस 0;
	हाल INQUIRY:
		अगर (scmd->cmnd[1] & 1) अणु
			/* Illegal request, invalid field in CDB */
			scsi_build_sense_buffer(0, scmd->sense_buffer,
						ILLEGAL_REQUEST, 0x24, 0);
			scmd->result = (DRIVER_SENSE << 24) |
				SAM_STAT_CHECK_CONDITION;
		पूर्ण अन्यथा अणु
			myrb_inquiry(cb, scmd);
			scmd->result = (DID_OK << 16);
		पूर्ण
		scmd->scsi_करोne(scmd);
		वापस 0;
	हाल SYNCHRONIZE_CACHE:
		scmd->result = (DID_OK << 16);
		scmd->scsi_करोne(scmd);
		वापस 0;
	हाल MODE_SENSE:
		अगर ((scmd->cmnd[2] & 0x3F) != 0x3F &&
		    (scmd->cmnd[2] & 0x3F) != 0x08) अणु
			/* Illegal request, invalid field in CDB */
			scsi_build_sense_buffer(0, scmd->sense_buffer,
						ILLEGAL_REQUEST, 0x24, 0);
			scmd->result = (DRIVER_SENSE << 24) |
				SAM_STAT_CHECK_CONDITION;
		पूर्ण अन्यथा अणु
			myrb_mode_sense(cb, scmd, ldev_info);
			scmd->result = (DID_OK << 16);
		पूर्ण
		scmd->scsi_करोne(scmd);
		वापस 0;
	हाल READ_CAPACITY:
		अगर ((scmd->cmnd[1] & 1) ||
		    (scmd->cmnd[8] & 1)) अणु
			/* Illegal request, invalid field in CDB */
			scsi_build_sense_buffer(0, scmd->sense_buffer,
						ILLEGAL_REQUEST, 0x24, 0);
			scmd->result = (DRIVER_SENSE << 24) |
				SAM_STAT_CHECK_CONDITION;
			scmd->scsi_करोne(scmd);
			वापस 0;
		पूर्ण
		lba = get_unaligned_be32(&scmd->cmnd[2]);
		अगर (lba) अणु
			/* Illegal request, invalid field in CDB */
			scsi_build_sense_buffer(0, scmd->sense_buffer,
						ILLEGAL_REQUEST, 0x24, 0);
			scmd->result = (DRIVER_SENSE << 24) |
				SAM_STAT_CHECK_CONDITION;
			scmd->scsi_करोne(scmd);
			वापस 0;
		पूर्ण
		myrb_पढ़ो_capacity(cb, scmd, ldev_info);
		scmd->scsi_करोne(scmd);
		वापस 0;
	हाल REQUEST_SENSE:
		myrb_request_sense(cb, scmd);
		scmd->result = (DID_OK << 16);
		वापस 0;
	हाल SEND_DIAGNOSTIC:
		अगर (scmd->cmnd[1] != 0x04) अणु
			/* Illegal request, invalid field in CDB */
			scsi_build_sense_buffer(0, scmd->sense_buffer,
						ILLEGAL_REQUEST, 0x24, 0);
			scmd->result = (DRIVER_SENSE << 24) |
				SAM_STAT_CHECK_CONDITION;
		पूर्ण अन्यथा अणु
			/* Assume good status */
			scmd->result = (DID_OK << 16);
		पूर्ण
		scmd->scsi_करोne(scmd);
		वापस 0;
	हाल READ_6:
		अगर (ldev_info->state == MYRB_DEVICE_WO) अणु
			/* Data protect, attempt to पढ़ो invalid data */
			scsi_build_sense_buffer(0, scmd->sense_buffer,
						DATA_PROTECT, 0x21, 0x06);
			scmd->result = (DRIVER_SENSE << 24) |
				SAM_STAT_CHECK_CONDITION;
			scmd->scsi_करोne(scmd);
			वापस 0;
		पूर्ण
		fallthrough;
	हाल WRITE_6:
		lba = (((scmd->cmnd[1] & 0x1F) << 16) |
		       (scmd->cmnd[2] << 8) |
		       scmd->cmnd[3]);
		block_cnt = scmd->cmnd[4];
		अवरोध;
	हाल READ_10:
		अगर (ldev_info->state == MYRB_DEVICE_WO) अणु
			/* Data protect, attempt to पढ़ो invalid data */
			scsi_build_sense_buffer(0, scmd->sense_buffer,
						DATA_PROTECT, 0x21, 0x06);
			scmd->result = (DRIVER_SENSE << 24) |
				SAM_STAT_CHECK_CONDITION;
			scmd->scsi_करोne(scmd);
			वापस 0;
		पूर्ण
		fallthrough;
	हाल WRITE_10:
	हाल VERIFY:		/* 0x2F */
	हाल WRITE_VERIFY:	/* 0x2E */
		lba = get_unaligned_be32(&scmd->cmnd[2]);
		block_cnt = get_unaligned_be16(&scmd->cmnd[7]);
		अवरोध;
	हाल READ_12:
		अगर (ldev_info->state == MYRB_DEVICE_WO) अणु
			/* Data protect, attempt to पढ़ो invalid data */
			scsi_build_sense_buffer(0, scmd->sense_buffer,
						DATA_PROTECT, 0x21, 0x06);
			scmd->result = (DRIVER_SENSE << 24) |
				SAM_STAT_CHECK_CONDITION;
			scmd->scsi_करोne(scmd);
			वापस 0;
		पूर्ण
		fallthrough;
	हाल WRITE_12:
	हाल VERIFY_12: /* 0xAF */
	हाल WRITE_VERIFY_12:	/* 0xAE */
		lba = get_unaligned_be32(&scmd->cmnd[2]);
		block_cnt = get_unaligned_be32(&scmd->cmnd[6]);
		अवरोध;
	शेष:
		/* Illegal request, invalid opcode */
		scsi_build_sense_buffer(0, scmd->sense_buffer,
					ILLEGAL_REQUEST, 0x20, 0);
		scmd->result = (DRIVER_SENSE << 24) | SAM_STAT_CHECK_CONDITION;
		scmd->scsi_करोne(scmd);
		वापस 0;
	पूर्ण

	myrb_reset_cmd(cmd_blk);
	mbox->type5.id = scmd->request->tag + 3;
	अगर (scmd->sc_data_direction == DMA_NONE)
		जाओ submit;
	nsge = scsi_dma_map(scmd);
	अगर (nsge == 1) अणु
		sgl = scsi_sglist(scmd);
		अगर (scmd->sc_data_direction == DMA_FROM_DEVICE)
			mbox->type5.opcode = MYRB_CMD_READ;
		अन्यथा
			mbox->type5.opcode = MYRB_CMD_WRITE;

		mbox->type5.ld.xfer_len = block_cnt;
		mbox->type5.ld.ldev_num = sdev->id;
		mbox->type5.lba = lba;
		mbox->type5.addr = (u32)sg_dma_address(sgl);
	पूर्ण अन्यथा अणु
		काष्ठा myrb_sge *hw_sgl;
		dma_addr_t hw_sgl_addr;
		पूर्णांक i;

		hw_sgl = dma_pool_alloc(cb->sg_pool, GFP_ATOMIC, &hw_sgl_addr);
		अगर (!hw_sgl)
			वापस SCSI_MLQUEUE_HOST_BUSY;

		cmd_blk->sgl = hw_sgl;
		cmd_blk->sgl_addr = hw_sgl_addr;

		अगर (scmd->sc_data_direction == DMA_FROM_DEVICE)
			mbox->type5.opcode = MYRB_CMD_READ_SG;
		अन्यथा
			mbox->type5.opcode = MYRB_CMD_WRITE_SG;

		mbox->type5.ld.xfer_len = block_cnt;
		mbox->type5.ld.ldev_num = sdev->id;
		mbox->type5.lba = lba;
		mbox->type5.addr = hw_sgl_addr;
		mbox->type5.sg_count = nsge;

		scsi_क्रम_each_sg(scmd, sgl, nsge, i) अणु
			hw_sgl->sge_addr = (u32)sg_dma_address(sgl);
			hw_sgl->sge_count = (u32)sg_dma_len(sgl);
			hw_sgl++;
		पूर्ण
	पूर्ण
submit:
	spin_lock_irqsave(&cb->queue_lock, flags);
	cb->qcmd(cb, cmd_blk);
	spin_unlock_irqrestore(&cb->queue_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक myrb_queuecommand(काष्ठा Scsi_Host *shost,
		काष्ठा scsi_cmnd *scmd)
अणु
	काष्ठा scsi_device *sdev = scmd->device;

	अगर (sdev->channel > myrb_logical_channel(shost)) अणु
		scmd->result = (DID_BAD_TARGET << 16);
		scmd->scsi_करोne(scmd);
		वापस 0;
	पूर्ण
	अगर (sdev->channel == myrb_logical_channel(shost))
		वापस myrb_ldev_queuecommand(shost, scmd);

	वापस myrb_pthru_queuecommand(shost, scmd);
पूर्ण

अटल पूर्णांक myrb_ldev_slave_alloc(काष्ठा scsi_device *sdev)
अणु
	काष्ठा myrb_hba *cb = shost_priv(sdev->host);
	काष्ठा myrb_ldev_info *ldev_info;
	अचिन्हित लघु ldev_num = sdev->id;
	क्रमागत raid_level level;

	ldev_info = cb->ldev_info_buf + ldev_num;
	अगर (!ldev_info)
		वापस -ENXIO;

	sdev->hostdata = kzalloc(माप(*ldev_info), GFP_KERNEL);
	अगर (!sdev->hostdata)
		वापस -ENOMEM;
	dev_dbg(&sdev->sdev_gendev,
		"slave alloc ldev %d state %x\n",
		ldev_num, ldev_info->state);
	स_नकल(sdev->hostdata, ldev_info,
	       माप(*ldev_info));
	चयन (ldev_info->raid_level) अणु
	हाल MYRB_RAID_LEVEL0:
		level = RAID_LEVEL_LINEAR;
		अवरोध;
	हाल MYRB_RAID_LEVEL1:
		level = RAID_LEVEL_1;
		अवरोध;
	हाल MYRB_RAID_LEVEL3:
		level = RAID_LEVEL_3;
		अवरोध;
	हाल MYRB_RAID_LEVEL5:
		level = RAID_LEVEL_5;
		अवरोध;
	हाल MYRB_RAID_LEVEL6:
		level = RAID_LEVEL_6;
		अवरोध;
	हाल MYRB_RAID_JBOD:
		level = RAID_LEVEL_JBOD;
		अवरोध;
	शेष:
		level = RAID_LEVEL_UNKNOWN;
		अवरोध;
	पूर्ण
	raid_set_level(myrb_raid_ढाँचा, &sdev->sdev_gendev, level);
	वापस 0;
पूर्ण

अटल पूर्णांक myrb_pdev_slave_alloc(काष्ठा scsi_device *sdev)
अणु
	काष्ठा myrb_hba *cb = shost_priv(sdev->host);
	काष्ठा myrb_pdev_state *pdev_info;
	अचिन्हित लघु status;

	अगर (sdev->id > MYRB_MAX_TARGETS)
		वापस -ENXIO;

	pdev_info = kzalloc(माप(*pdev_info), GFP_KERNEL|GFP_DMA);
	अगर (!pdev_info)
		वापस -ENOMEM;

	status = myrb_exec_type3D(cb, MYRB_CMD_GET_DEVICE_STATE,
				  sdev, pdev_info);
	अगर (status != MYRB_STATUS_SUCCESS) अणु
		dev_dbg(&sdev->sdev_gendev,
			"Failed to get device state, status %x\n",
			status);
		kमुक्त(pdev_info);
		वापस -ENXIO;
	पूर्ण
	अगर (!pdev_info->present) अणु
		dev_dbg(&sdev->sdev_gendev,
			"device not present, skip\n");
		kमुक्त(pdev_info);
		वापस -ENXIO;
	पूर्ण
	dev_dbg(&sdev->sdev_gendev,
		"slave alloc pdev %d:%d state %x\n",
		sdev->channel, sdev->id, pdev_info->state);
	sdev->hostdata = pdev_info;

	वापस 0;
पूर्ण

अटल पूर्णांक myrb_slave_alloc(काष्ठा scsi_device *sdev)
अणु
	अगर (sdev->channel > myrb_logical_channel(sdev->host))
		वापस -ENXIO;

	अगर (sdev->lun > 0)
		वापस -ENXIO;

	अगर (sdev->channel == myrb_logical_channel(sdev->host))
		वापस myrb_ldev_slave_alloc(sdev);

	वापस myrb_pdev_slave_alloc(sdev);
पूर्ण

अटल पूर्णांक myrb_slave_configure(काष्ठा scsi_device *sdev)
अणु
	काष्ठा myrb_ldev_info *ldev_info;

	अगर (sdev->channel > myrb_logical_channel(sdev->host))
		वापस -ENXIO;

	अगर (sdev->channel < myrb_logical_channel(sdev->host)) अणु
		sdev->no_uld_attach = 1;
		वापस 0;
	पूर्ण
	अगर (sdev->lun != 0)
		वापस -ENXIO;

	ldev_info = sdev->hostdata;
	अगर (!ldev_info)
		वापस -ENXIO;
	अगर (ldev_info->state != MYRB_DEVICE_ONLINE)
		sdev_prपूर्णांकk(KERN_INFO, sdev,
			    "Logical drive is %s\n",
			    myrb_devstate_name(ldev_info->state));

	sdev->tagged_supported = 1;
	वापस 0;
पूर्ण

अटल व्योम myrb_slave_destroy(काष्ठा scsi_device *sdev)
अणु
	kमुक्त(sdev->hostdata);
पूर्ण

अटल पूर्णांक myrb_biosparam(काष्ठा scsi_device *sdev, काष्ठा block_device *bdev,
		sector_t capacity, पूर्णांक geom[])
अणु
	काष्ठा myrb_hba *cb = shost_priv(sdev->host);

	geom[0] = cb->ldev_geom_heads;
	geom[1] = cb->ldev_geom_sectors;
	geom[2] = sector_भाग(capacity, geom[0] * geom[1]);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार raid_state_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा myrb_hba *cb = shost_priv(sdev->host);
	पूर्णांक ret;

	अगर (!sdev->hostdata)
		वापस snम_लिखो(buf, 16, "Unknown\n");

	अगर (sdev->channel == myrb_logical_channel(sdev->host)) अणु
		काष्ठा myrb_ldev_info *ldev_info = sdev->hostdata;
		स्थिर अक्षर *name;

		name = myrb_devstate_name(ldev_info->state);
		अगर (name)
			ret = snम_लिखो(buf, 32, "%s\n", name);
		अन्यथा
			ret = snम_लिखो(buf, 32, "Invalid (%02X)\n",
				       ldev_info->state);
	पूर्ण अन्यथा अणु
		काष्ठा myrb_pdev_state *pdev_info = sdev->hostdata;
		अचिन्हित लघु status;
		स्थिर अक्षर *name;

		status = myrb_exec_type3D(cb, MYRB_CMD_GET_DEVICE_STATE,
					  sdev, pdev_info);
		अगर (status != MYRB_STATUS_SUCCESS)
			sdev_prपूर्णांकk(KERN_INFO, sdev,
				    "Failed to get device state, status %x\n",
				    status);

		अगर (!pdev_info->present)
			name = "Removed";
		अन्यथा
			name = myrb_devstate_name(pdev_info->state);
		अगर (name)
			ret = snम_लिखो(buf, 32, "%s\n", name);
		अन्यथा
			ret = snम_लिखो(buf, 32, "Invalid (%02X)\n",
				       pdev_info->state);
	पूर्ण
	वापस ret;
पूर्ण

अटल sमाप_प्रकार raid_state_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा myrb_hba *cb = shost_priv(sdev->host);
	काष्ठा myrb_pdev_state *pdev_info;
	क्रमागत myrb_devstate new_state;
	अचिन्हित लघु status;

	अगर (!म_भेदन(buf, "kill", 4) ||
	    !म_भेदन(buf, "offline", 7))
		new_state = MYRB_DEVICE_DEAD;
	अन्यथा अगर (!म_भेदन(buf, "online", 6))
		new_state = MYRB_DEVICE_ONLINE;
	अन्यथा अगर (!म_भेदन(buf, "standby", 7))
		new_state = MYRB_DEVICE_STANDBY;
	अन्यथा
		वापस -EINVAL;

	pdev_info = sdev->hostdata;
	अगर (!pdev_info) अणु
		sdev_prपूर्णांकk(KERN_INFO, sdev,
			    "Failed - no physical device information\n");
		वापस -ENXIO;
	पूर्ण
	अगर (!pdev_info->present) अणु
		sdev_prपूर्णांकk(KERN_INFO, sdev,
			    "Failed - device not present\n");
		वापस -ENXIO;
	पूर्ण

	अगर (pdev_info->state == new_state)
		वापस count;

	status = myrb_set_pdev_state(cb, sdev, new_state);
	चयन (status) अणु
	हाल MYRB_STATUS_SUCCESS:
		अवरोध;
	हाल MYRB_STATUS_START_DEVICE_FAILED:
		sdev_prपूर्णांकk(KERN_INFO, sdev,
			     "Failed - Unable to Start Device\n");
		count = -EAGAIN;
		अवरोध;
	हाल MYRB_STATUS_NO_DEVICE:
		sdev_prपूर्णांकk(KERN_INFO, sdev,
			    "Failed - No Device at Address\n");
		count = -ENODEV;
		अवरोध;
	हाल MYRB_STATUS_INVALID_CHANNEL_OR_TARGET:
		sdev_prपूर्णांकk(KERN_INFO, sdev,
			 "Failed - Invalid Channel or Target or Modifier\n");
		count = -EINVAL;
		अवरोध;
	हाल MYRB_STATUS_CHANNEL_BUSY:
		sdev_prपूर्णांकk(KERN_INFO, sdev,
			 "Failed - Channel Busy\n");
		count = -EBUSY;
		अवरोध;
	शेष:
		sdev_prपूर्णांकk(KERN_INFO, sdev,
			 "Failed - Unexpected Status %04X\n", status);
		count = -EIO;
		अवरोध;
	पूर्ण
	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(raid_state);

अटल sमाप_प्रकार raid_level_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);

	अगर (sdev->channel == myrb_logical_channel(sdev->host)) अणु
		काष्ठा myrb_ldev_info *ldev_info = sdev->hostdata;
		स्थिर अक्षर *name;

		अगर (!ldev_info)
			वापस -ENXIO;

		name = myrb_raidlevel_name(ldev_info->raid_level);
		अगर (!name)
			वापस snम_लिखो(buf, 32, "Invalid (%02X)\n",
					ldev_info->state);
		वापस snम_लिखो(buf, 32, "%s\n", name);
	पूर्ण
	वापस snम_लिखो(buf, 32, "Physical Drive\n");
पूर्ण
अटल DEVICE_ATTR_RO(raid_level);

अटल sमाप_प्रकार rebuild_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा myrb_hba *cb = shost_priv(sdev->host);
	काष्ठा myrb_rbld_progress rbld_buf;
	अचिन्हित अक्षर status;

	अगर (sdev->channel < myrb_logical_channel(sdev->host))
		वापस snम_लिखो(buf, 32, "physical device - not rebuilding\n");

	status = myrb_get_rbld_progress(cb, &rbld_buf);

	अगर (rbld_buf.ldev_num != sdev->id ||
	    status != MYRB_STATUS_SUCCESS)
		वापस snम_लिखो(buf, 32, "not rebuilding\n");

	वापस snम_लिखो(buf, 32, "rebuilding block %u of %u\n",
			rbld_buf.ldev_size - rbld_buf.blocks_left,
			rbld_buf.ldev_size);
पूर्ण

अटल sमाप_प्रकार rebuild_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा myrb_hba *cb = shost_priv(sdev->host);
	काष्ठा myrb_cmdblk *cmd_blk;
	जोड़ myrb_cmd_mbox *mbox;
	अचिन्हित लघु status;
	पूर्णांक rc, start;
	स्थिर अक्षर *msg;

	rc = kstrtoपूर्णांक(buf, 0, &start);
	अगर (rc)
		वापस rc;

	अगर (sdev->channel >= myrb_logical_channel(sdev->host))
		वापस -ENXIO;

	status = myrb_get_rbld_progress(cb, शून्य);
	अगर (start) अणु
		अगर (status == MYRB_STATUS_SUCCESS) अणु
			sdev_prपूर्णांकk(KERN_INFO, sdev,
				    "Rebuild Not Initiated; already in progress\n");
			वापस -EALREADY;
		पूर्ण
		mutex_lock(&cb->dcmd_mutex);
		cmd_blk = &cb->dcmd_blk;
		myrb_reset_cmd(cmd_blk);
		mbox = &cmd_blk->mbox;
		mbox->type3D.opcode = MYRB_CMD_REBUILD_ASYNC;
		mbox->type3D.id = MYRB_DCMD_TAG;
		mbox->type3D.channel = sdev->channel;
		mbox->type3D.target = sdev->id;
		status = myrb_exec_cmd(cb, cmd_blk);
		mutex_unlock(&cb->dcmd_mutex);
	पूर्ण अन्यथा अणु
		काष्ठा pci_dev *pdev = cb->pdev;
		अचिन्हित अक्षर *rate;
		dma_addr_t rate_addr;

		अगर (status != MYRB_STATUS_SUCCESS) अणु
			sdev_prपूर्णांकk(KERN_INFO, sdev,
				    "Rebuild Not Cancelled; not in progress\n");
			वापस 0;
		पूर्ण

		rate = dma_alloc_coherent(&pdev->dev, माप(अक्षर),
					  &rate_addr, GFP_KERNEL);
		अगर (rate == शून्य) अणु
			sdev_prपूर्णांकk(KERN_INFO, sdev,
				    "Cancellation of Rebuild Failed - Out of Memory\n");
			वापस -ENOMEM;
		पूर्ण
		mutex_lock(&cb->dcmd_mutex);
		cmd_blk = &cb->dcmd_blk;
		myrb_reset_cmd(cmd_blk);
		mbox = &cmd_blk->mbox;
		mbox->type3R.opcode = MYRB_CMD_REBUILD_CONTROL;
		mbox->type3R.id = MYRB_DCMD_TAG;
		mbox->type3R.rbld_rate = 0xFF;
		mbox->type3R.addr = rate_addr;
		status = myrb_exec_cmd(cb, cmd_blk);
		dma_मुक्त_coherent(&pdev->dev, माप(अक्षर), rate, rate_addr);
		mutex_unlock(&cb->dcmd_mutex);
	पूर्ण
	अगर (status == MYRB_STATUS_SUCCESS) अणु
		sdev_prपूर्णांकk(KERN_INFO, sdev, "Rebuild %s\n",
			    start ? "Initiated" : "Cancelled");
		वापस count;
	पूर्ण
	अगर (!start) अणु
		sdev_prपूर्णांकk(KERN_INFO, sdev,
			    "Rebuild Not Cancelled, status 0x%x\n",
			    status);
		वापस -EIO;
	पूर्ण

	चयन (status) अणु
	हाल MYRB_STATUS_ATTEMPT_TO_RBLD_ONLINE_DRIVE:
		msg = "Attempt to Rebuild Online or Unresponsive Drive";
		अवरोध;
	हाल MYRB_STATUS_RBLD_NEW_DISK_FAILED:
		msg = "New Disk Failed During Rebuild";
		अवरोध;
	हाल MYRB_STATUS_INVALID_ADDRESS:
		msg = "Invalid Device Address";
		अवरोध;
	हाल MYRB_STATUS_RBLD_OR_CHECK_INPROGRESS:
		msg = "Already in Progress";
		अवरोध;
	शेष:
		msg = शून्य;
		अवरोध;
	पूर्ण
	अगर (msg)
		sdev_prपूर्णांकk(KERN_INFO, sdev,
			    "Rebuild Failed - %s\n", msg);
	अन्यथा
		sdev_prपूर्णांकk(KERN_INFO, sdev,
			    "Rebuild Failed, status 0x%x\n", status);

	वापस -EIO;
पूर्ण
अटल DEVICE_ATTR_RW(rebuild);

अटल sमाप_प्रकार consistency_check_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा myrb_hba *cb = shost_priv(sdev->host);
	काष्ठा myrb_rbld_progress rbld_buf;
	काष्ठा myrb_cmdblk *cmd_blk;
	जोड़ myrb_cmd_mbox *mbox;
	अचिन्हित लघु ldev_num = 0xFFFF;
	अचिन्हित लघु status;
	पूर्णांक rc, start;
	स्थिर अक्षर *msg;

	rc = kstrtoपूर्णांक(buf, 0, &start);
	अगर (rc)
		वापस rc;

	अगर (sdev->channel < myrb_logical_channel(sdev->host))
		वापस -ENXIO;

	status = myrb_get_rbld_progress(cb, &rbld_buf);
	अगर (start) अणु
		अगर (status == MYRB_STATUS_SUCCESS) अणु
			sdev_prपूर्णांकk(KERN_INFO, sdev,
				    "Check Consistency Not Initiated; already in progress\n");
			वापस -EALREADY;
		पूर्ण
		mutex_lock(&cb->dcmd_mutex);
		cmd_blk = &cb->dcmd_blk;
		myrb_reset_cmd(cmd_blk);
		mbox = &cmd_blk->mbox;
		mbox->type3C.opcode = MYRB_CMD_CHECK_CONSISTENCY_ASYNC;
		mbox->type3C.id = MYRB_DCMD_TAG;
		mbox->type3C.ldev_num = sdev->id;
		mbox->type3C.स्वतः_restore = true;

		status = myrb_exec_cmd(cb, cmd_blk);
		mutex_unlock(&cb->dcmd_mutex);
	पूर्ण अन्यथा अणु
		काष्ठा pci_dev *pdev = cb->pdev;
		अचिन्हित अक्षर *rate;
		dma_addr_t rate_addr;

		अगर (ldev_num != sdev->id) अणु
			sdev_prपूर्णांकk(KERN_INFO, sdev,
				    "Check Consistency Not Cancelled; not in progress\n");
			वापस 0;
		पूर्ण
		rate = dma_alloc_coherent(&pdev->dev, माप(अक्षर),
					  &rate_addr, GFP_KERNEL);
		अगर (rate == शून्य) अणु
			sdev_prपूर्णांकk(KERN_INFO, sdev,
				    "Cancellation of Check Consistency Failed - Out of Memory\n");
			वापस -ENOMEM;
		पूर्ण
		mutex_lock(&cb->dcmd_mutex);
		cmd_blk = &cb->dcmd_blk;
		myrb_reset_cmd(cmd_blk);
		mbox = &cmd_blk->mbox;
		mbox->type3R.opcode = MYRB_CMD_REBUILD_CONTROL;
		mbox->type3R.id = MYRB_DCMD_TAG;
		mbox->type3R.rbld_rate = 0xFF;
		mbox->type3R.addr = rate_addr;
		status = myrb_exec_cmd(cb, cmd_blk);
		dma_मुक्त_coherent(&pdev->dev, माप(अक्षर), rate, rate_addr);
		mutex_unlock(&cb->dcmd_mutex);
	पूर्ण
	अगर (status == MYRB_STATUS_SUCCESS) अणु
		sdev_prपूर्णांकk(KERN_INFO, sdev, "Check Consistency %s\n",
			    start ? "Initiated" : "Cancelled");
		वापस count;
	पूर्ण
	अगर (!start) अणु
		sdev_prपूर्णांकk(KERN_INFO, sdev,
			    "Check Consistency Not Cancelled, status 0x%x\n",
			    status);
		वापस -EIO;
	पूर्ण

	चयन (status) अणु
	हाल MYRB_STATUS_ATTEMPT_TO_RBLD_ONLINE_DRIVE:
		msg = "Dependent Physical Device is DEAD";
		अवरोध;
	हाल MYRB_STATUS_RBLD_NEW_DISK_FAILED:
		msg = "New Disk Failed During Rebuild";
		अवरोध;
	हाल MYRB_STATUS_INVALID_ADDRESS:
		msg = "Invalid or Nonredundant Logical Drive";
		अवरोध;
	हाल MYRB_STATUS_RBLD_OR_CHECK_INPROGRESS:
		msg = "Already in Progress";
		अवरोध;
	शेष:
		msg = शून्य;
		अवरोध;
	पूर्ण
	अगर (msg)
		sdev_prपूर्णांकk(KERN_INFO, sdev,
			    "Check Consistency Failed - %s\n", msg);
	अन्यथा
		sdev_prपूर्णांकk(KERN_INFO, sdev,
			    "Check Consistency Failed, status 0x%x\n", status);

	वापस -EIO;
पूर्ण

अटल sमाप_प्रकार consistency_check_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस rebuild_show(dev, attr, buf);
पूर्ण
अटल DEVICE_ATTR_RW(consistency_check);

अटल sमाप_प्रकार ctlr_num_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा myrb_hba *cb = shost_priv(shost);

	वापस snम_लिखो(buf, 20, "%u\n", cb->ctlr_num);
पूर्ण
अटल DEVICE_ATTR_RO(ctlr_num);

अटल sमाप_प्रकार firmware_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा myrb_hba *cb = shost_priv(shost);

	वापस snम_लिखो(buf, 16, "%s\n", cb->fw_version);
पूर्ण
अटल DEVICE_ATTR_RO(firmware);

अटल sमाप_प्रकार model_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा myrb_hba *cb = shost_priv(shost);

	वापस snम_लिखो(buf, 16, "%s\n", cb->model_name);
पूर्ण
अटल DEVICE_ATTR_RO(model);

अटल sमाप_प्रकार flush_cache_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा myrb_hba *cb = shost_priv(shost);
	अचिन्हित लघु status;

	status = myrb_exec_type3(cb, MYRB_CMD_FLUSH, 0);
	अगर (status == MYRB_STATUS_SUCCESS) अणु
		shost_prपूर्णांकk(KERN_INFO, shost,
			     "Cache Flush Completed\n");
		वापस count;
	पूर्ण
	shost_prपूर्णांकk(KERN_INFO, shost,
		     "Cache Flush Failed, status %x\n", status);
	वापस -EIO;
पूर्ण
अटल DEVICE_ATTR_WO(flush_cache);

अटल काष्ठा device_attribute *myrb_sdev_attrs[] = अणु
	&dev_attr_rebuild,
	&dev_attr_consistency_check,
	&dev_attr_raid_state,
	&dev_attr_raid_level,
	शून्य,
पूर्ण;

अटल काष्ठा device_attribute *myrb_shost_attrs[] = अणु
	&dev_attr_ctlr_num,
	&dev_attr_model,
	&dev_attr_firmware,
	&dev_attr_flush_cache,
	शून्य,
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा myrb_ढाँचा = अणु
	.module			= THIS_MODULE,
	.name			= "DAC960",
	.proc_name		= "myrb",
	.queuecommand		= myrb_queuecommand,
	.eh_host_reset_handler	= myrb_host_reset,
	.slave_alloc		= myrb_slave_alloc,
	.slave_configure	= myrb_slave_configure,
	.slave_destroy		= myrb_slave_destroy,
	.bios_param		= myrb_biosparam,
	.cmd_size		= माप(काष्ठा myrb_cmdblk),
	.shost_attrs		= myrb_shost_attrs,
	.sdev_attrs		= myrb_sdev_attrs,
	.this_id		= -1,
पूर्ण;

/**
 * myrb_is_raid - वापस boolean indicating device is raid volume
 * @dev: the device काष्ठा object
 */
अटल पूर्णांक myrb_is_raid(काष्ठा device *dev)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);

	वापस sdev->channel == myrb_logical_channel(sdev->host);
पूर्ण

/**
 * myrb_get_resync - get raid volume resync percent complete
 * @dev: the device काष्ठा object
 */
अटल व्योम myrb_get_resync(काष्ठा device *dev)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा myrb_hba *cb = shost_priv(sdev->host);
	काष्ठा myrb_rbld_progress rbld_buf;
	अचिन्हित पूर्णांक percent_complete = 0;
	अचिन्हित लघु status;
	अचिन्हित पूर्णांक ldev_size = 0, reमुख्यing = 0;

	अगर (sdev->channel < myrb_logical_channel(sdev->host))
		वापस;
	status = myrb_get_rbld_progress(cb, &rbld_buf);
	अगर (status == MYRB_STATUS_SUCCESS) अणु
		अगर (rbld_buf.ldev_num == sdev->id) अणु
			ldev_size = rbld_buf.ldev_size;
			reमुख्यing = rbld_buf.blocks_left;
		पूर्ण
	पूर्ण
	अगर (reमुख्यing && ldev_size)
		percent_complete = (ldev_size - reमुख्यing) * 100 / ldev_size;
	raid_set_resync(myrb_raid_ढाँचा, dev, percent_complete);
पूर्ण

/**
 * myrb_get_state - get raid volume status
 * @dev: the device काष्ठा object
 */
अटल व्योम myrb_get_state(काष्ठा device *dev)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा myrb_hba *cb = shost_priv(sdev->host);
	काष्ठा myrb_ldev_info *ldev_info = sdev->hostdata;
	क्रमागत raid_state state = RAID_STATE_UNKNOWN;
	अचिन्हित लघु status;

	अगर (sdev->channel < myrb_logical_channel(sdev->host) || !ldev_info)
		state = RAID_STATE_UNKNOWN;
	अन्यथा अणु
		status = myrb_get_rbld_progress(cb, शून्य);
		अगर (status == MYRB_STATUS_SUCCESS)
			state = RAID_STATE_RESYNCING;
		अन्यथा अणु
			चयन (ldev_info->state) अणु
			हाल MYRB_DEVICE_ONLINE:
				state = RAID_STATE_ACTIVE;
				अवरोध;
			हाल MYRB_DEVICE_WO:
			हाल MYRB_DEVICE_CRITICAL:
				state = RAID_STATE_DEGRADED;
				अवरोध;
			शेष:
				state = RAID_STATE_OFFLINE;
			पूर्ण
		पूर्ण
	पूर्ण
	raid_set_state(myrb_raid_ढाँचा, dev, state);
पूर्ण

अटल काष्ठा raid_function_ढाँचा myrb_raid_functions = अणु
	.cookie		= &myrb_ढाँचा,
	.is_raid	= myrb_is_raid,
	.get_resync	= myrb_get_resync,
	.get_state	= myrb_get_state,
पूर्ण;

अटल व्योम myrb_handle_scsi(काष्ठा myrb_hba *cb, काष्ठा myrb_cmdblk *cmd_blk,
		काष्ठा scsi_cmnd *scmd)
अणु
	अचिन्हित लघु status;

	अगर (!cmd_blk)
		वापस;

	scsi_dma_unmap(scmd);

	अगर (cmd_blk->dcdb) अणु
		स_नकल(scmd->sense_buffer, &cmd_blk->dcdb->sense, 64);
		dma_pool_मुक्त(cb->dcdb_pool, cmd_blk->dcdb,
			      cmd_blk->dcdb_addr);
		cmd_blk->dcdb = शून्य;
	पूर्ण
	अगर (cmd_blk->sgl) अणु
		dma_pool_मुक्त(cb->sg_pool, cmd_blk->sgl, cmd_blk->sgl_addr);
		cmd_blk->sgl = शून्य;
		cmd_blk->sgl_addr = 0;
	पूर्ण
	status = cmd_blk->status;
	चयन (status) अणु
	हाल MYRB_STATUS_SUCCESS:
	हाल MYRB_STATUS_DEVICE_BUSY:
		scmd->result = (DID_OK << 16) | status;
		अवरोध;
	हाल MYRB_STATUS_BAD_DATA:
		dev_dbg(&scmd->device->sdev_gendev,
			"Bad Data Encountered\n");
		अगर (scmd->sc_data_direction == DMA_FROM_DEVICE)
			/* Unrecovered पढ़ो error */
			scsi_build_sense_buffer(0, scmd->sense_buffer,
						MEDIUM_ERROR, 0x11, 0);
		अन्यथा
			/* Write error */
			scsi_build_sense_buffer(0, scmd->sense_buffer,
						MEDIUM_ERROR, 0x0C, 0);
		scmd->result = (DID_OK << 16) | SAM_STAT_CHECK_CONDITION;
		अवरोध;
	हाल MYRB_STATUS_IRRECOVERABLE_DATA_ERROR:
		scmd_prपूर्णांकk(KERN_ERR, scmd, "Irrecoverable Data Error\n");
		अगर (scmd->sc_data_direction == DMA_FROM_DEVICE)
			/* Unrecovered पढ़ो error, स्वतः-पुनः_स्मृतिation failed */
			scsi_build_sense_buffer(0, scmd->sense_buffer,
						MEDIUM_ERROR, 0x11, 0x04);
		अन्यथा
			/* Write error, स्वतः-पुनः_स्मृतिation failed */
			scsi_build_sense_buffer(0, scmd->sense_buffer,
						MEDIUM_ERROR, 0x0C, 0x02);
		scmd->result = (DID_OK << 16) | SAM_STAT_CHECK_CONDITION;
		अवरोध;
	हाल MYRB_STATUS_LDRV_NONEXISTENT_OR_OFFLINE:
		dev_dbg(&scmd->device->sdev_gendev,
			    "Logical Drive Nonexistent or Offline");
		scmd->result = (DID_BAD_TARGET << 16);
		अवरोध;
	हाल MYRB_STATUS_ACCESS_BEYOND_END_OF_LDRV:
		dev_dbg(&scmd->device->sdev_gendev,
			    "Attempt to Access Beyond End of Logical Drive");
		/* Logical block address out of range */
		scsi_build_sense_buffer(0, scmd->sense_buffer,
					NOT_READY, 0x21, 0);
		अवरोध;
	हाल MYRB_STATUS_DEVICE_NONRESPONSIVE:
		dev_dbg(&scmd->device->sdev_gendev, "Device nonresponsive\n");
		scmd->result = (DID_BAD_TARGET << 16);
		अवरोध;
	शेष:
		scmd_prपूर्णांकk(KERN_ERR, scmd,
			    "Unexpected Error Status %04X", status);
		scmd->result = (DID_ERROR << 16);
		अवरोध;
	पूर्ण
	scmd->scsi_करोne(scmd);
पूर्ण

अटल व्योम myrb_handle_cmdblk(काष्ठा myrb_hba *cb, काष्ठा myrb_cmdblk *cmd_blk)
अणु
	अगर (!cmd_blk)
		वापस;

	अगर (cmd_blk->completion) अणु
		complete(cmd_blk->completion);
		cmd_blk->completion = शून्य;
	पूर्ण
पूर्ण

अटल व्योम myrb_monitor(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा myrb_hba *cb = container_of(work,
			काष्ठा myrb_hba, monitor_work.work);
	काष्ठा Scsi_Host *shost = cb->host;
	अचिन्हित दीर्घ पूर्णांकerval = MYRB_PRIMARY_MONITOR_INTERVAL;

	dev_dbg(&shost->shost_gendev, "monitor tick\n");

	अगर (cb->new_ev_seq > cb->old_ev_seq) अणु
		पूर्णांक event = cb->old_ev_seq;

		dev_dbg(&shost->shost_gendev,
			"get event log no %d/%d\n",
			cb->new_ev_seq, event);
		myrb_get_event(cb, event);
		cb->old_ev_seq = event + 1;
		पूर्णांकerval = 10;
	पूर्ण अन्यथा अगर (cb->need_err_info) अणु
		cb->need_err_info = false;
		dev_dbg(&shost->shost_gendev, "get error table\n");
		myrb_get_errtable(cb);
		पूर्णांकerval = 10;
	पूर्ण अन्यथा अगर (cb->need_rbld && cb->rbld_first) अणु
		cb->need_rbld = false;
		dev_dbg(&shost->shost_gendev,
			"get rebuild progress\n");
		myrb_update_rbld_progress(cb);
		पूर्णांकerval = 10;
	पूर्ण अन्यथा अगर (cb->need_ldev_info) अणु
		cb->need_ldev_info = false;
		dev_dbg(&shost->shost_gendev,
			"get logical drive info\n");
		myrb_get_ldev_info(cb);
		पूर्णांकerval = 10;
	पूर्ण अन्यथा अगर (cb->need_rbld) अणु
		cb->need_rbld = false;
		dev_dbg(&shost->shost_gendev,
			"get rebuild progress\n");
		myrb_update_rbld_progress(cb);
		पूर्णांकerval = 10;
	पूर्ण अन्यथा अगर (cb->need_cc_status) अणु
		cb->need_cc_status = false;
		dev_dbg(&shost->shost_gendev,
			"get consistency check progress\n");
		myrb_get_cc_progress(cb);
		पूर्णांकerval = 10;
	पूर्ण अन्यथा अगर (cb->need_bgi_status) अणु
		cb->need_bgi_status = false;
		dev_dbg(&shost->shost_gendev, "get background init status\n");
		myrb_bgi_control(cb);
		पूर्णांकerval = 10;
	पूर्ण अन्यथा अणु
		dev_dbg(&shost->shost_gendev, "new enquiry\n");
		mutex_lock(&cb->dma_mutex);
		myrb_hba_enquiry(cb);
		mutex_unlock(&cb->dma_mutex);
		अगर ((cb->new_ev_seq - cb->old_ev_seq > 0) ||
		    cb->need_err_info || cb->need_rbld ||
		    cb->need_ldev_info || cb->need_cc_status ||
		    cb->need_bgi_status) अणु
			dev_dbg(&shost->shost_gendev,
				"reschedule monitor\n");
			पूर्णांकerval = 0;
		पूर्ण
	पूर्ण
	अगर (पूर्णांकerval > 1)
		cb->primary_monitor_समय = jअगरfies;
	queue_delayed_work(cb->work_q, &cb->monitor_work, पूर्णांकerval);
पूर्ण

/*
 * myrb_err_status - reports controller BIOS messages
 *
 * Controller BIOS messages are passed through the Error Status Register
 * when the driver perक्रमms the BIOS handshaking.
 *
 * Return: true क्रम fatal errors and false otherwise.
 */
अटल bool myrb_err_status(काष्ठा myrb_hba *cb, अचिन्हित अक्षर error,
		अचिन्हित अक्षर parm0, अचिन्हित अक्षर parm1)
अणु
	काष्ठा pci_dev *pdev = cb->pdev;

	चयन (error) अणु
	हाल 0x00:
		dev_info(&pdev->dev,
			 "Physical Device %d:%d Not Responding\n",
			 parm1, parm0);
		अवरोध;
	हाल 0x08:
		dev_notice(&pdev->dev, "Spinning Up Drives\n");
		अवरोध;
	हाल 0x30:
		dev_notice(&pdev->dev, "Configuration Checksum Error\n");
		अवरोध;
	हाल 0x60:
		dev_notice(&pdev->dev, "Mirror Race Recovery Failed\n");
		अवरोध;
	हाल 0x70:
		dev_notice(&pdev->dev, "Mirror Race Recovery In Progress\n");
		अवरोध;
	हाल 0x90:
		dev_notice(&pdev->dev, "Physical Device %d:%d COD Mismatch\n",
			   parm1, parm0);
		अवरोध;
	हाल 0xA0:
		dev_notice(&pdev->dev, "Logical Drive Installation Aborted\n");
		अवरोध;
	हाल 0xB0:
		dev_notice(&pdev->dev, "Mirror Race On A Critical Logical Drive\n");
		अवरोध;
	हाल 0xD0:
		dev_notice(&pdev->dev, "New Controller Configuration Found\n");
		अवरोध;
	हाल 0xF0:
		dev_err(&pdev->dev, "Fatal Memory Parity Error\n");
		वापस true;
	शेष:
		dev_err(&pdev->dev, "Unknown Initialization Error %02X\n",
			error);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/*
 * Hardware-specअगरic functions
 */

/*
 * DAC960 LA Series Controllers
 */

अटल अंतरभूत व्योम DAC960_LA_hw_mbox_new_cmd(व्योम __iomem *base)
अणु
	ग_लिखोb(DAC960_LA_IDB_HWMBOX_NEW_CMD, base + DAC960_LA_IDB_OFFSET);
पूर्ण

अटल अंतरभूत व्योम DAC960_LA_ack_hw_mbox_status(व्योम __iomem *base)
अणु
	ग_लिखोb(DAC960_LA_IDB_HWMBOX_ACK_STS, base + DAC960_LA_IDB_OFFSET);
पूर्ण

अटल अंतरभूत व्योम DAC960_LA_reset_ctrl(व्योम __iomem *base)
अणु
	ग_लिखोb(DAC960_LA_IDB_CTRL_RESET, base + DAC960_LA_IDB_OFFSET);
पूर्ण

अटल अंतरभूत व्योम DAC960_LA_mem_mbox_new_cmd(व्योम __iomem *base)
अणु
	ग_लिखोb(DAC960_LA_IDB_MMBOX_NEW_CMD, base + DAC960_LA_IDB_OFFSET);
पूर्ण

अटल अंतरभूत bool DAC960_LA_hw_mbox_is_full(व्योम __iomem *base)
अणु
	अचिन्हित अक्षर idb = पढ़ोb(base + DAC960_LA_IDB_OFFSET);

	वापस !(idb & DAC960_LA_IDB_HWMBOX_EMPTY);
पूर्ण

अटल अंतरभूत bool DAC960_LA_init_in_progress(व्योम __iomem *base)
अणु
	अचिन्हित अक्षर idb = पढ़ोb(base + DAC960_LA_IDB_OFFSET);

	वापस !(idb & DAC960_LA_IDB_INIT_DONE);
पूर्ण

अटल अंतरभूत व्योम DAC960_LA_ack_hw_mbox_पूर्णांकr(व्योम __iomem *base)
अणु
	ग_लिखोb(DAC960_LA_ODB_HWMBOX_ACK_IRQ, base + DAC960_LA_ODB_OFFSET);
पूर्ण

अटल अंतरभूत व्योम DAC960_LA_ack_पूर्णांकr(व्योम __iomem *base)
अणु
	ग_लिखोb(DAC960_LA_ODB_HWMBOX_ACK_IRQ | DAC960_LA_ODB_MMBOX_ACK_IRQ,
	       base + DAC960_LA_ODB_OFFSET);
पूर्ण

अटल अंतरभूत bool DAC960_LA_hw_mbox_status_available(व्योम __iomem *base)
अणु
	अचिन्हित अक्षर odb = पढ़ोb(base + DAC960_LA_ODB_OFFSET);

	वापस odb & DAC960_LA_ODB_HWMBOX_STS_AVAIL;
पूर्ण

अटल अंतरभूत व्योम DAC960_LA_enable_पूर्णांकr(व्योम __iomem *base)
अणु
	अचिन्हित अक्षर odb = 0xFF;

	odb &= ~DAC960_LA_IRQMASK_DISABLE_IRQ;
	ग_लिखोb(odb, base + DAC960_LA_IRQMASK_OFFSET);
पूर्ण

अटल अंतरभूत व्योम DAC960_LA_disable_पूर्णांकr(व्योम __iomem *base)
अणु
	अचिन्हित अक्षर odb = 0xFF;

	odb |= DAC960_LA_IRQMASK_DISABLE_IRQ;
	ग_लिखोb(odb, base + DAC960_LA_IRQMASK_OFFSET);
पूर्ण

अटल अंतरभूत व्योम DAC960_LA_ग_लिखो_cmd_mbox(जोड़ myrb_cmd_mbox *mem_mbox,
		जोड़ myrb_cmd_mbox *mbox)
अणु
	mem_mbox->words[1] = mbox->words[1];
	mem_mbox->words[2] = mbox->words[2];
	mem_mbox->words[3] = mbox->words[3];
	/* Memory barrier to prevent reordering */
	wmb();
	mem_mbox->words[0] = mbox->words[0];
	/* Memory barrier to क्रमce PCI access */
	mb();
पूर्ण

अटल अंतरभूत व्योम DAC960_LA_ग_लिखो_hw_mbox(व्योम __iomem *base,
		जोड़ myrb_cmd_mbox *mbox)
अणु
	ग_लिखोl(mbox->words[0], base + DAC960_LA_CMDOP_OFFSET);
	ग_लिखोl(mbox->words[1], base + DAC960_LA_MBOX4_OFFSET);
	ग_लिखोl(mbox->words[2], base + DAC960_LA_MBOX8_OFFSET);
	ग_लिखोb(mbox->bytes[12], base + DAC960_LA_MBOX12_OFFSET);
पूर्ण

अटल अंतरभूत अचिन्हित लघु DAC960_LA_पढ़ो_status(व्योम __iomem *base)
अणु
	वापस पढ़ोw(base + DAC960_LA_STS_OFFSET);
पूर्ण

अटल अंतरभूत bool
DAC960_LA_पढ़ो_error_status(व्योम __iomem *base, अचिन्हित अक्षर *error,
		अचिन्हित अक्षर *param0, अचिन्हित अक्षर *param1)
अणु
	अचिन्हित अक्षर errsts = पढ़ोb(base + DAC960_LA_ERRSTS_OFFSET);

	अगर (!(errsts & DAC960_LA_ERRSTS_PENDING))
		वापस false;
	errsts &= ~DAC960_LA_ERRSTS_PENDING;

	*error = errsts;
	*param0 = पढ़ोb(base + DAC960_LA_CMDOP_OFFSET);
	*param1 = पढ़ोb(base + DAC960_LA_CMDID_OFFSET);
	ग_लिखोb(0xFF, base + DAC960_LA_ERRSTS_OFFSET);
	वापस true;
पूर्ण

अटल अंतरभूत अचिन्हित लघु
DAC960_LA_mbox_init(काष्ठा pci_dev *pdev, व्योम __iomem *base,
		जोड़ myrb_cmd_mbox *mbox)
अणु
	अचिन्हित लघु status;
	पूर्णांक समयout = 0;

	जबतक (समयout < MYRB_MAILBOX_TIMEOUT) अणु
		अगर (!DAC960_LA_hw_mbox_is_full(base))
			अवरोध;
		udelay(10);
		समयout++;
	पूर्ण
	अगर (DAC960_LA_hw_mbox_is_full(base)) अणु
		dev_err(&pdev->dev,
			"Timeout waiting for empty mailbox\n");
		वापस MYRB_STATUS_SUBSYS_TIMEOUT;
	पूर्ण
	DAC960_LA_ग_लिखो_hw_mbox(base, mbox);
	DAC960_LA_hw_mbox_new_cmd(base);
	समयout = 0;
	जबतक (समयout < MYRB_MAILBOX_TIMEOUT) अणु
		अगर (DAC960_LA_hw_mbox_status_available(base))
			अवरोध;
		udelay(10);
		समयout++;
	पूर्ण
	अगर (!DAC960_LA_hw_mbox_status_available(base)) अणु
		dev_err(&pdev->dev, "Timeout waiting for mailbox status\n");
		वापस MYRB_STATUS_SUBSYS_TIMEOUT;
	पूर्ण
	status = DAC960_LA_पढ़ो_status(base);
	DAC960_LA_ack_hw_mbox_पूर्णांकr(base);
	DAC960_LA_ack_hw_mbox_status(base);

	वापस status;
पूर्ण

अटल पूर्णांक DAC960_LA_hw_init(काष्ठा pci_dev *pdev,
		काष्ठा myrb_hba *cb, व्योम __iomem *base)
अणु
	पूर्णांक समयout = 0;
	अचिन्हित अक्षर error, parm0, parm1;

	DAC960_LA_disable_पूर्णांकr(base);
	DAC960_LA_ack_hw_mbox_status(base);
	udelay(1000);
	जबतक (DAC960_LA_init_in_progress(base) &&
	       समयout < MYRB_MAILBOX_TIMEOUT) अणु
		अगर (DAC960_LA_पढ़ो_error_status(base, &error,
					      &parm0, &parm1) &&
		    myrb_err_status(cb, error, parm0, parm1))
			वापस -ENODEV;
		udelay(10);
		समयout++;
	पूर्ण
	अगर (समयout == MYRB_MAILBOX_TIMEOUT) अणु
		dev_err(&pdev->dev,
			"Timeout waiting for Controller Initialisation\n");
		वापस -ETIMEDOUT;
	पूर्ण
	अगर (!myrb_enable_mmio(cb, DAC960_LA_mbox_init)) अणु
		dev_err(&pdev->dev,
			"Unable to Enable Memory Mailbox Interface\n");
		DAC960_LA_reset_ctrl(base);
		वापस -ENODEV;
	पूर्ण
	DAC960_LA_enable_पूर्णांकr(base);
	cb->qcmd = myrb_qcmd;
	cb->ग_लिखो_cmd_mbox = DAC960_LA_ग_लिखो_cmd_mbox;
	अगर (cb->dual_mode_पूर्णांकerface)
		cb->get_cmd_mbox = DAC960_LA_mem_mbox_new_cmd;
	अन्यथा
		cb->get_cmd_mbox = DAC960_LA_hw_mbox_new_cmd;
	cb->disable_पूर्णांकr = DAC960_LA_disable_पूर्णांकr;
	cb->reset = DAC960_LA_reset_ctrl;

	वापस 0;
पूर्ण

अटल irqवापस_t DAC960_LA_पूर्णांकr_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा myrb_hba *cb = arg;
	व्योम __iomem *base = cb->io_base;
	काष्ठा myrb_stat_mbox *next_stat_mbox;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cb->queue_lock, flags);
	DAC960_LA_ack_पूर्णांकr(base);
	next_stat_mbox = cb->next_stat_mbox;
	जबतक (next_stat_mbox->valid) अणु
		अचिन्हित अक्षर id = next_stat_mbox->id;
		काष्ठा scsi_cmnd *scmd = शून्य;
		काष्ठा myrb_cmdblk *cmd_blk = शून्य;

		अगर (id == MYRB_DCMD_TAG)
			cmd_blk = &cb->dcmd_blk;
		अन्यथा अगर (id == MYRB_MCMD_TAG)
			cmd_blk = &cb->mcmd_blk;
		अन्यथा अणु
			scmd = scsi_host_find_tag(cb->host, id - 3);
			अगर (scmd)
				cmd_blk = scsi_cmd_priv(scmd);
		पूर्ण
		अगर (cmd_blk)
			cmd_blk->status = next_stat_mbox->status;
		अन्यथा
			dev_err(&cb->pdev->dev,
				"Unhandled command completion %d\n", id);

		स_रखो(next_stat_mbox, 0, माप(काष्ठा myrb_stat_mbox));
		अगर (++next_stat_mbox > cb->last_stat_mbox)
			next_stat_mbox = cb->first_stat_mbox;

		अगर (cmd_blk) अणु
			अगर (id < 3)
				myrb_handle_cmdblk(cb, cmd_blk);
			अन्यथा
				myrb_handle_scsi(cb, cmd_blk, scmd);
		पूर्ण
	पूर्ण
	cb->next_stat_mbox = next_stat_mbox;
	spin_unlock_irqrestore(&cb->queue_lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा myrb_privdata DAC960_LA_privdata = अणु
	.hw_init =	DAC960_LA_hw_init,
	.irq_handler =	DAC960_LA_पूर्णांकr_handler,
	.mmio_size =	DAC960_LA_mmio_size,
पूर्ण;

/*
 * DAC960 PG Series Controllers
 */
अटल अंतरभूत व्योम DAC960_PG_hw_mbox_new_cmd(व्योम __iomem *base)
अणु
	ग_लिखोl(DAC960_PG_IDB_HWMBOX_NEW_CMD, base + DAC960_PG_IDB_OFFSET);
पूर्ण

अटल अंतरभूत व्योम DAC960_PG_ack_hw_mbox_status(व्योम __iomem *base)
अणु
	ग_लिखोl(DAC960_PG_IDB_HWMBOX_ACK_STS, base + DAC960_PG_IDB_OFFSET);
पूर्ण

अटल अंतरभूत व्योम DAC960_PG_reset_ctrl(व्योम __iomem *base)
अणु
	ग_लिखोl(DAC960_PG_IDB_CTRL_RESET, base + DAC960_PG_IDB_OFFSET);
पूर्ण

अटल अंतरभूत व्योम DAC960_PG_mem_mbox_new_cmd(व्योम __iomem *base)
अणु
	ग_लिखोl(DAC960_PG_IDB_MMBOX_NEW_CMD, base + DAC960_PG_IDB_OFFSET);
पूर्ण

अटल अंतरभूत bool DAC960_PG_hw_mbox_is_full(व्योम __iomem *base)
अणु
	अचिन्हित अक्षर idb = पढ़ोl(base + DAC960_PG_IDB_OFFSET);

	वापस idb & DAC960_PG_IDB_HWMBOX_FULL;
पूर्ण

अटल अंतरभूत bool DAC960_PG_init_in_progress(व्योम __iomem *base)
अणु
	अचिन्हित अक्षर idb = पढ़ोl(base + DAC960_PG_IDB_OFFSET);

	वापस idb & DAC960_PG_IDB_INIT_IN_PROGRESS;
पूर्ण

अटल अंतरभूत व्योम DAC960_PG_ack_hw_mbox_पूर्णांकr(व्योम __iomem *base)
अणु
	ग_लिखोl(DAC960_PG_ODB_HWMBOX_ACK_IRQ, base + DAC960_PG_ODB_OFFSET);
पूर्ण

अटल अंतरभूत व्योम DAC960_PG_ack_पूर्णांकr(व्योम __iomem *base)
अणु
	ग_लिखोl(DAC960_PG_ODB_HWMBOX_ACK_IRQ | DAC960_PG_ODB_MMBOX_ACK_IRQ,
	       base + DAC960_PG_ODB_OFFSET);
पूर्ण

अटल अंतरभूत bool DAC960_PG_hw_mbox_status_available(व्योम __iomem *base)
अणु
	अचिन्हित अक्षर odb = पढ़ोl(base + DAC960_PG_ODB_OFFSET);

	वापस odb & DAC960_PG_ODB_HWMBOX_STS_AVAIL;
पूर्ण

अटल अंतरभूत व्योम DAC960_PG_enable_पूर्णांकr(व्योम __iomem *base)
अणु
	अचिन्हित पूर्णांक imask = (अचिन्हित पूर्णांक)-1;

	imask &= ~DAC960_PG_IRQMASK_DISABLE_IRQ;
	ग_लिखोl(imask, base + DAC960_PG_IRQMASK_OFFSET);
पूर्ण

अटल अंतरभूत व्योम DAC960_PG_disable_पूर्णांकr(व्योम __iomem *base)
अणु
	अचिन्हित पूर्णांक imask = (अचिन्हित पूर्णांक)-1;

	ग_लिखोl(imask, base + DAC960_PG_IRQMASK_OFFSET);
पूर्ण

अटल अंतरभूत व्योम DAC960_PG_ग_लिखो_cmd_mbox(जोड़ myrb_cmd_mbox *mem_mbox,
		जोड़ myrb_cmd_mbox *mbox)
अणु
	mem_mbox->words[1] = mbox->words[1];
	mem_mbox->words[2] = mbox->words[2];
	mem_mbox->words[3] = mbox->words[3];
	/* Memory barrier to prevent reordering */
	wmb();
	mem_mbox->words[0] = mbox->words[0];
	/* Memory barrier to क्रमce PCI access */
	mb();
पूर्ण

अटल अंतरभूत व्योम DAC960_PG_ग_लिखो_hw_mbox(व्योम __iomem *base,
		जोड़ myrb_cmd_mbox *mbox)
अणु
	ग_लिखोl(mbox->words[0], base + DAC960_PG_CMDOP_OFFSET);
	ग_लिखोl(mbox->words[1], base + DAC960_PG_MBOX4_OFFSET);
	ग_लिखोl(mbox->words[2], base + DAC960_PG_MBOX8_OFFSET);
	ग_लिखोb(mbox->bytes[12], base + DAC960_PG_MBOX12_OFFSET);
पूर्ण

अटल अंतरभूत अचिन्हित लघु
DAC960_PG_पढ़ो_status(व्योम __iomem *base)
अणु
	वापस पढ़ोw(base + DAC960_PG_STS_OFFSET);
पूर्ण

अटल अंतरभूत bool
DAC960_PG_पढ़ो_error_status(व्योम __iomem *base, अचिन्हित अक्षर *error,
		अचिन्हित अक्षर *param0, अचिन्हित अक्षर *param1)
अणु
	अचिन्हित अक्षर errsts = पढ़ोb(base + DAC960_PG_ERRSTS_OFFSET);

	अगर (!(errsts & DAC960_PG_ERRSTS_PENDING))
		वापस false;
	errsts &= ~DAC960_PG_ERRSTS_PENDING;
	*error = errsts;
	*param0 = पढ़ोb(base + DAC960_PG_CMDOP_OFFSET);
	*param1 = पढ़ोb(base + DAC960_PG_CMDID_OFFSET);
	ग_लिखोb(0, base + DAC960_PG_ERRSTS_OFFSET);
	वापस true;
पूर्ण

अटल अंतरभूत अचिन्हित लघु
DAC960_PG_mbox_init(काष्ठा pci_dev *pdev, व्योम __iomem *base,
		जोड़ myrb_cmd_mbox *mbox)
अणु
	अचिन्हित लघु status;
	पूर्णांक समयout = 0;

	जबतक (समयout < MYRB_MAILBOX_TIMEOUT) अणु
		अगर (!DAC960_PG_hw_mbox_is_full(base))
			अवरोध;
		udelay(10);
		समयout++;
	पूर्ण
	अगर (DAC960_PG_hw_mbox_is_full(base)) अणु
		dev_err(&pdev->dev,
			"Timeout waiting for empty mailbox\n");
		वापस MYRB_STATUS_SUBSYS_TIMEOUT;
	पूर्ण
	DAC960_PG_ग_लिखो_hw_mbox(base, mbox);
	DAC960_PG_hw_mbox_new_cmd(base);

	समयout = 0;
	जबतक (समयout < MYRB_MAILBOX_TIMEOUT) अणु
		अगर (DAC960_PG_hw_mbox_status_available(base))
			अवरोध;
		udelay(10);
		समयout++;
	पूर्ण
	अगर (!DAC960_PG_hw_mbox_status_available(base)) अणु
		dev_err(&pdev->dev,
			"Timeout waiting for mailbox status\n");
		वापस MYRB_STATUS_SUBSYS_TIMEOUT;
	पूर्ण
	status = DAC960_PG_पढ़ो_status(base);
	DAC960_PG_ack_hw_mbox_पूर्णांकr(base);
	DAC960_PG_ack_hw_mbox_status(base);

	वापस status;
पूर्ण

अटल पूर्णांक DAC960_PG_hw_init(काष्ठा pci_dev *pdev,
		काष्ठा myrb_hba *cb, व्योम __iomem *base)
अणु
	पूर्णांक समयout = 0;
	अचिन्हित अक्षर error, parm0, parm1;

	DAC960_PG_disable_पूर्णांकr(base);
	DAC960_PG_ack_hw_mbox_status(base);
	udelay(1000);
	जबतक (DAC960_PG_init_in_progress(base) &&
	       समयout < MYRB_MAILBOX_TIMEOUT) अणु
		अगर (DAC960_PG_पढ़ो_error_status(base, &error,
						&parm0, &parm1) &&
		    myrb_err_status(cb, error, parm0, parm1))
			वापस -EIO;
		udelay(10);
		समयout++;
	पूर्ण
	अगर (समयout == MYRB_MAILBOX_TIMEOUT) अणु
		dev_err(&pdev->dev,
			"Timeout waiting for Controller Initialisation\n");
		वापस -ETIMEDOUT;
	पूर्ण
	अगर (!myrb_enable_mmio(cb, DAC960_PG_mbox_init)) अणु
		dev_err(&pdev->dev,
			"Unable to Enable Memory Mailbox Interface\n");
		DAC960_PG_reset_ctrl(base);
		वापस -ENODEV;
	पूर्ण
	DAC960_PG_enable_पूर्णांकr(base);
	cb->qcmd = myrb_qcmd;
	cb->ग_लिखो_cmd_mbox = DAC960_PG_ग_लिखो_cmd_mbox;
	अगर (cb->dual_mode_पूर्णांकerface)
		cb->get_cmd_mbox = DAC960_PG_mem_mbox_new_cmd;
	अन्यथा
		cb->get_cmd_mbox = DAC960_PG_hw_mbox_new_cmd;
	cb->disable_पूर्णांकr = DAC960_PG_disable_पूर्णांकr;
	cb->reset = DAC960_PG_reset_ctrl;

	वापस 0;
पूर्ण

अटल irqवापस_t DAC960_PG_पूर्णांकr_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा myrb_hba *cb = arg;
	व्योम __iomem *base = cb->io_base;
	काष्ठा myrb_stat_mbox *next_stat_mbox;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cb->queue_lock, flags);
	DAC960_PG_ack_पूर्णांकr(base);
	next_stat_mbox = cb->next_stat_mbox;
	जबतक (next_stat_mbox->valid) अणु
		अचिन्हित अक्षर id = next_stat_mbox->id;
		काष्ठा scsi_cmnd *scmd = शून्य;
		काष्ठा myrb_cmdblk *cmd_blk = शून्य;

		अगर (id == MYRB_DCMD_TAG)
			cmd_blk = &cb->dcmd_blk;
		अन्यथा अगर (id == MYRB_MCMD_TAG)
			cmd_blk = &cb->mcmd_blk;
		अन्यथा अणु
			scmd = scsi_host_find_tag(cb->host, id - 3);
			अगर (scmd)
				cmd_blk = scsi_cmd_priv(scmd);
		पूर्ण
		अगर (cmd_blk)
			cmd_blk->status = next_stat_mbox->status;
		अन्यथा
			dev_err(&cb->pdev->dev,
				"Unhandled command completion %d\n", id);

		स_रखो(next_stat_mbox, 0, माप(काष्ठा myrb_stat_mbox));
		अगर (++next_stat_mbox > cb->last_stat_mbox)
			next_stat_mbox = cb->first_stat_mbox;

		अगर (id < 3)
			myrb_handle_cmdblk(cb, cmd_blk);
		अन्यथा
			myrb_handle_scsi(cb, cmd_blk, scmd);
	पूर्ण
	cb->next_stat_mbox = next_stat_mbox;
	spin_unlock_irqrestore(&cb->queue_lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा myrb_privdata DAC960_PG_privdata = अणु
	.hw_init =	DAC960_PG_hw_init,
	.irq_handler =	DAC960_PG_पूर्णांकr_handler,
	.mmio_size =	DAC960_PG_mmio_size,
पूर्ण;


/*
 * DAC960 PD Series Controllers
 */

अटल अंतरभूत व्योम DAC960_PD_hw_mbox_new_cmd(व्योम __iomem *base)
अणु
	ग_लिखोb(DAC960_PD_IDB_HWMBOX_NEW_CMD, base + DAC960_PD_IDB_OFFSET);
पूर्ण

अटल अंतरभूत व्योम DAC960_PD_ack_hw_mbox_status(व्योम __iomem *base)
अणु
	ग_लिखोb(DAC960_PD_IDB_HWMBOX_ACK_STS, base + DAC960_PD_IDB_OFFSET);
पूर्ण

अटल अंतरभूत व्योम DAC960_PD_reset_ctrl(व्योम __iomem *base)
अणु
	ग_लिखोb(DAC960_PD_IDB_CTRL_RESET, base + DAC960_PD_IDB_OFFSET);
पूर्ण

अटल अंतरभूत bool DAC960_PD_hw_mbox_is_full(व्योम __iomem *base)
अणु
	अचिन्हित अक्षर idb = पढ़ोb(base + DAC960_PD_IDB_OFFSET);

	वापस idb & DAC960_PD_IDB_HWMBOX_FULL;
पूर्ण

अटल अंतरभूत bool DAC960_PD_init_in_progress(व्योम __iomem *base)
अणु
	अचिन्हित अक्षर idb = पढ़ोb(base + DAC960_PD_IDB_OFFSET);

	वापस idb & DAC960_PD_IDB_INIT_IN_PROGRESS;
पूर्ण

अटल अंतरभूत व्योम DAC960_PD_ack_पूर्णांकr(व्योम __iomem *base)
अणु
	ग_लिखोb(DAC960_PD_ODB_HWMBOX_ACK_IRQ, base + DAC960_PD_ODB_OFFSET);
पूर्ण

अटल अंतरभूत bool DAC960_PD_hw_mbox_status_available(व्योम __iomem *base)
अणु
	अचिन्हित अक्षर odb = पढ़ोb(base + DAC960_PD_ODB_OFFSET);

	वापस odb & DAC960_PD_ODB_HWMBOX_STS_AVAIL;
पूर्ण

अटल अंतरभूत व्योम DAC960_PD_enable_पूर्णांकr(व्योम __iomem *base)
अणु
	ग_लिखोb(DAC960_PD_IRQMASK_ENABLE_IRQ, base + DAC960_PD_IRQEN_OFFSET);
पूर्ण

अटल अंतरभूत व्योम DAC960_PD_disable_पूर्णांकr(व्योम __iomem *base)
अणु
	ग_लिखोb(0, base + DAC960_PD_IRQEN_OFFSET);
पूर्ण

अटल अंतरभूत व्योम DAC960_PD_ग_लिखो_cmd_mbox(व्योम __iomem *base,
		जोड़ myrb_cmd_mbox *mbox)
अणु
	ग_लिखोl(mbox->words[0], base + DAC960_PD_CMDOP_OFFSET);
	ग_लिखोl(mbox->words[1], base + DAC960_PD_MBOX4_OFFSET);
	ग_लिखोl(mbox->words[2], base + DAC960_PD_MBOX8_OFFSET);
	ग_लिखोb(mbox->bytes[12], base + DAC960_PD_MBOX12_OFFSET);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर
DAC960_PD_पढ़ो_status_cmd_ident(व्योम __iomem *base)
अणु
	वापस पढ़ोb(base + DAC960_PD_STSID_OFFSET);
पूर्ण

अटल अंतरभूत अचिन्हित लघु
DAC960_PD_पढ़ो_status(व्योम __iomem *base)
अणु
	वापस पढ़ोw(base + DAC960_PD_STS_OFFSET);
पूर्ण

अटल अंतरभूत bool
DAC960_PD_पढ़ो_error_status(व्योम __iomem *base, अचिन्हित अक्षर *error,
		अचिन्हित अक्षर *param0, अचिन्हित अक्षर *param1)
अणु
	अचिन्हित अक्षर errsts = पढ़ोb(base + DAC960_PD_ERRSTS_OFFSET);

	अगर (!(errsts & DAC960_PD_ERRSTS_PENDING))
		वापस false;
	errsts &= ~DAC960_PD_ERRSTS_PENDING;
	*error = errsts;
	*param0 = पढ़ोb(base + DAC960_PD_CMDOP_OFFSET);
	*param1 = पढ़ोb(base + DAC960_PD_CMDID_OFFSET);
	ग_लिखोb(0, base + DAC960_PD_ERRSTS_OFFSET);
	वापस true;
पूर्ण

अटल व्योम DAC960_PD_qcmd(काष्ठा myrb_hba *cb, काष्ठा myrb_cmdblk *cmd_blk)
अणु
	व्योम __iomem *base = cb->io_base;
	जोड़ myrb_cmd_mbox *mbox = &cmd_blk->mbox;

	जबतक (DAC960_PD_hw_mbox_is_full(base))
		udelay(1);
	DAC960_PD_ग_लिखो_cmd_mbox(base, mbox);
	DAC960_PD_hw_mbox_new_cmd(base);
पूर्ण

अटल पूर्णांक DAC960_PD_hw_init(काष्ठा pci_dev *pdev,
		काष्ठा myrb_hba *cb, व्योम __iomem *base)
अणु
	पूर्णांक समयout = 0;
	अचिन्हित अक्षर error, parm0, parm1;

	अगर (!request_region(cb->io_addr, 0x80, "myrb")) अणु
		dev_err(&pdev->dev, "IO port 0x%lx busy\n",
			(अचिन्हित दीर्घ)cb->io_addr);
		वापस -EBUSY;
	पूर्ण
	DAC960_PD_disable_पूर्णांकr(base);
	DAC960_PD_ack_hw_mbox_status(base);
	udelay(1000);
	जबतक (DAC960_PD_init_in_progress(base) &&
	       समयout < MYRB_MAILBOX_TIMEOUT) अणु
		अगर (DAC960_PD_पढ़ो_error_status(base, &error,
					      &parm0, &parm1) &&
		    myrb_err_status(cb, error, parm0, parm1))
			वापस -EIO;
		udelay(10);
		समयout++;
	पूर्ण
	अगर (समयout == MYRB_MAILBOX_TIMEOUT) अणु
		dev_err(&pdev->dev,
			"Timeout waiting for Controller Initialisation\n");
		वापस -ETIMEDOUT;
	पूर्ण
	अगर (!myrb_enable_mmio(cb, शून्य)) अणु
		dev_err(&pdev->dev,
			"Unable to Enable Memory Mailbox Interface\n");
		DAC960_PD_reset_ctrl(base);
		वापस -ENODEV;
	पूर्ण
	DAC960_PD_enable_पूर्णांकr(base);
	cb->qcmd = DAC960_PD_qcmd;
	cb->disable_पूर्णांकr = DAC960_PD_disable_पूर्णांकr;
	cb->reset = DAC960_PD_reset_ctrl;

	वापस 0;
पूर्ण

अटल irqवापस_t DAC960_PD_पूर्णांकr_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा myrb_hba *cb = arg;
	व्योम __iomem *base = cb->io_base;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cb->queue_lock, flags);
	जबतक (DAC960_PD_hw_mbox_status_available(base)) अणु
		अचिन्हित अक्षर id = DAC960_PD_पढ़ो_status_cmd_ident(base);
		काष्ठा scsi_cmnd *scmd = शून्य;
		काष्ठा myrb_cmdblk *cmd_blk = शून्य;

		अगर (id == MYRB_DCMD_TAG)
			cmd_blk = &cb->dcmd_blk;
		अन्यथा अगर (id == MYRB_MCMD_TAG)
			cmd_blk = &cb->mcmd_blk;
		अन्यथा अणु
			scmd = scsi_host_find_tag(cb->host, id - 3);
			अगर (scmd)
				cmd_blk = scsi_cmd_priv(scmd);
		पूर्ण
		अगर (cmd_blk)
			cmd_blk->status = DAC960_PD_पढ़ो_status(base);
		अन्यथा
			dev_err(&cb->pdev->dev,
				"Unhandled command completion %d\n", id);

		DAC960_PD_ack_पूर्णांकr(base);
		DAC960_PD_ack_hw_mbox_status(base);

		अगर (id < 3)
			myrb_handle_cmdblk(cb, cmd_blk);
		अन्यथा
			myrb_handle_scsi(cb, cmd_blk, scmd);
	पूर्ण
	spin_unlock_irqrestore(&cb->queue_lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा myrb_privdata DAC960_PD_privdata = अणु
	.hw_init =	DAC960_PD_hw_init,
	.irq_handler =	DAC960_PD_पूर्णांकr_handler,
	.mmio_size =	DAC960_PD_mmio_size,
पूर्ण;


/*
 * DAC960 P Series Controllers
 *
 * Similar to the DAC960 PD Series Controllers, but some commands have
 * to be translated.
 */

अटल अंतरभूत व्योम myrb_translate_enquiry(व्योम *enq)
अणु
	स_नकल(enq + 132, enq + 36, 64);
	स_रखो(enq + 36, 0, 96);
पूर्ण

अटल अंतरभूत व्योम myrb_translate_devstate(व्योम *state)
अणु
	स_नकल(state + 2, state + 3, 1);
	स_हटाओ(state + 4, state + 5, 2);
	स_हटाओ(state + 6, state + 8, 4);
पूर्ण

अटल अंतरभूत व्योम myrb_translate_to_rw_command(काष्ठा myrb_cmdblk *cmd_blk)
अणु
	जोड़ myrb_cmd_mbox *mbox = &cmd_blk->mbox;
	पूर्णांक ldev_num = mbox->type5.ld.ldev_num;

	mbox->bytes[3] &= 0x7;
	mbox->bytes[3] |= mbox->bytes[7] << 6;
	mbox->bytes[7] = ldev_num;
पूर्ण

अटल अंतरभूत व्योम myrb_translate_from_rw_command(काष्ठा myrb_cmdblk *cmd_blk)
अणु
	जोड़ myrb_cmd_mbox *mbox = &cmd_blk->mbox;
	पूर्णांक ldev_num = mbox->bytes[7];

	mbox->bytes[7] = mbox->bytes[3] >> 6;
	mbox->bytes[3] &= 0x7;
	mbox->bytes[3] |= ldev_num << 3;
पूर्ण

अटल व्योम DAC960_P_qcmd(काष्ठा myrb_hba *cb, काष्ठा myrb_cmdblk *cmd_blk)
अणु
	व्योम __iomem *base = cb->io_base;
	जोड़ myrb_cmd_mbox *mbox = &cmd_blk->mbox;

	चयन (mbox->common.opcode) अणु
	हाल MYRB_CMD_ENQUIRY:
		mbox->common.opcode = MYRB_CMD_ENQUIRY_OLD;
		अवरोध;
	हाल MYRB_CMD_GET_DEVICE_STATE:
		mbox->common.opcode = MYRB_CMD_GET_DEVICE_STATE_OLD;
		अवरोध;
	हाल MYRB_CMD_READ:
		mbox->common.opcode = MYRB_CMD_READ_OLD;
		myrb_translate_to_rw_command(cmd_blk);
		अवरोध;
	हाल MYRB_CMD_WRITE:
		mbox->common.opcode = MYRB_CMD_WRITE_OLD;
		myrb_translate_to_rw_command(cmd_blk);
		अवरोध;
	हाल MYRB_CMD_READ_SG:
		mbox->common.opcode = MYRB_CMD_READ_SG_OLD;
		myrb_translate_to_rw_command(cmd_blk);
		अवरोध;
	हाल MYRB_CMD_WRITE_SG:
		mbox->common.opcode = MYRB_CMD_WRITE_SG_OLD;
		myrb_translate_to_rw_command(cmd_blk);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	जबतक (DAC960_PD_hw_mbox_is_full(base))
		udelay(1);
	DAC960_PD_ग_लिखो_cmd_mbox(base, mbox);
	DAC960_PD_hw_mbox_new_cmd(base);
पूर्ण


अटल पूर्णांक DAC960_P_hw_init(काष्ठा pci_dev *pdev,
		काष्ठा myrb_hba *cb, व्योम __iomem *base)
अणु
	पूर्णांक समयout = 0;
	अचिन्हित अक्षर error, parm0, parm1;

	अगर (!request_region(cb->io_addr, 0x80, "myrb")) अणु
		dev_err(&pdev->dev, "IO port 0x%lx busy\n",
			(अचिन्हित दीर्घ)cb->io_addr);
		वापस -EBUSY;
	पूर्ण
	DAC960_PD_disable_पूर्णांकr(base);
	DAC960_PD_ack_hw_mbox_status(base);
	udelay(1000);
	जबतक (DAC960_PD_init_in_progress(base) &&
	       समयout < MYRB_MAILBOX_TIMEOUT) अणु
		अगर (DAC960_PD_पढ़ो_error_status(base, &error,
						&parm0, &parm1) &&
		    myrb_err_status(cb, error, parm0, parm1))
			वापस -EAGAIN;
		udelay(10);
		समयout++;
	पूर्ण
	अगर (समयout == MYRB_MAILBOX_TIMEOUT) अणु
		dev_err(&pdev->dev,
			"Timeout waiting for Controller Initialisation\n");
		वापस -ETIMEDOUT;
	पूर्ण
	अगर (!myrb_enable_mmio(cb, शून्य)) अणु
		dev_err(&pdev->dev,
			"Unable to allocate DMA mapped memory\n");
		DAC960_PD_reset_ctrl(base);
		वापस -ETIMEDOUT;
	पूर्ण
	DAC960_PD_enable_पूर्णांकr(base);
	cb->qcmd = DAC960_P_qcmd;
	cb->disable_पूर्णांकr = DAC960_PD_disable_पूर्णांकr;
	cb->reset = DAC960_PD_reset_ctrl;

	वापस 0;
पूर्ण

अटल irqवापस_t DAC960_P_पूर्णांकr_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा myrb_hba *cb = arg;
	व्योम __iomem *base = cb->io_base;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cb->queue_lock, flags);
	जबतक (DAC960_PD_hw_mbox_status_available(base)) अणु
		अचिन्हित अक्षर id = DAC960_PD_पढ़ो_status_cmd_ident(base);
		काष्ठा scsi_cmnd *scmd = शून्य;
		काष्ठा myrb_cmdblk *cmd_blk = शून्य;
		जोड़ myrb_cmd_mbox *mbox;
		क्रमागत myrb_cmd_opcode op;


		अगर (id == MYRB_DCMD_TAG)
			cmd_blk = &cb->dcmd_blk;
		अन्यथा अगर (id == MYRB_MCMD_TAG)
			cmd_blk = &cb->mcmd_blk;
		अन्यथा अणु
			scmd = scsi_host_find_tag(cb->host, id - 3);
			अगर (scmd)
				cmd_blk = scsi_cmd_priv(scmd);
		पूर्ण
		अगर (cmd_blk)
			cmd_blk->status = DAC960_PD_पढ़ो_status(base);
		अन्यथा
			dev_err(&cb->pdev->dev,
				"Unhandled command completion %d\n", id);

		DAC960_PD_ack_पूर्णांकr(base);
		DAC960_PD_ack_hw_mbox_status(base);

		अगर (!cmd_blk)
			जारी;

		mbox = &cmd_blk->mbox;
		op = mbox->common.opcode;
		चयन (op) अणु
		हाल MYRB_CMD_ENQUIRY_OLD:
			mbox->common.opcode = MYRB_CMD_ENQUIRY;
			myrb_translate_enquiry(cb->enquiry);
			अवरोध;
		हाल MYRB_CMD_READ_OLD:
			mbox->common.opcode = MYRB_CMD_READ;
			myrb_translate_from_rw_command(cmd_blk);
			अवरोध;
		हाल MYRB_CMD_WRITE_OLD:
			mbox->common.opcode = MYRB_CMD_WRITE;
			myrb_translate_from_rw_command(cmd_blk);
			अवरोध;
		हाल MYRB_CMD_READ_SG_OLD:
			mbox->common.opcode = MYRB_CMD_READ_SG;
			myrb_translate_from_rw_command(cmd_blk);
			अवरोध;
		हाल MYRB_CMD_WRITE_SG_OLD:
			mbox->common.opcode = MYRB_CMD_WRITE_SG;
			myrb_translate_from_rw_command(cmd_blk);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अगर (id < 3)
			myrb_handle_cmdblk(cb, cmd_blk);
		अन्यथा
			myrb_handle_scsi(cb, cmd_blk, scmd);
	पूर्ण
	spin_unlock_irqrestore(&cb->queue_lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा myrb_privdata DAC960_P_privdata = अणु
	.hw_init =	DAC960_P_hw_init,
	.irq_handler =	DAC960_P_पूर्णांकr_handler,
	.mmio_size =	DAC960_PD_mmio_size,
पूर्ण;

अटल काष्ठा myrb_hba *myrb_detect(काष्ठा pci_dev *pdev,
		स्थिर काष्ठा pci_device_id *entry)
अणु
	काष्ठा myrb_privdata *privdata =
		(काष्ठा myrb_privdata *)entry->driver_data;
	irq_handler_t irq_handler = privdata->irq_handler;
	अचिन्हित पूर्णांक mmio_size = privdata->mmio_size;
	काष्ठा Scsi_Host *shost;
	काष्ठा myrb_hba *cb = शून्य;

	shost = scsi_host_alloc(&myrb_ढाँचा, माप(काष्ठा myrb_hba));
	अगर (!shost) अणु
		dev_err(&pdev->dev, "Unable to allocate Controller\n");
		वापस शून्य;
	पूर्ण
	shost->max_cmd_len = 12;
	shost->max_lun = 256;
	cb = shost_priv(shost);
	mutex_init(&cb->dcmd_mutex);
	mutex_init(&cb->dma_mutex);
	cb->pdev = pdev;

	अगर (pci_enable_device(pdev))
		जाओ failure;

	अगर (privdata->hw_init == DAC960_PD_hw_init ||
	    privdata->hw_init == DAC960_P_hw_init) अणु
		cb->io_addr = pci_resource_start(pdev, 0);
		cb->pci_addr = pci_resource_start(pdev, 1);
	पूर्ण अन्यथा
		cb->pci_addr = pci_resource_start(pdev, 0);

	pci_set_drvdata(pdev, cb);
	spin_lock_init(&cb->queue_lock);
	अगर (mmio_size < PAGE_SIZE)
		mmio_size = PAGE_SIZE;
	cb->mmio_base = ioremap(cb->pci_addr & PAGE_MASK, mmio_size);
	अगर (cb->mmio_base == शून्य) अणु
		dev_err(&pdev->dev,
			"Unable to map Controller Register Window\n");
		जाओ failure;
	पूर्ण

	cb->io_base = cb->mmio_base + (cb->pci_addr & ~PAGE_MASK);
	अगर (privdata->hw_init(pdev, cb, cb->io_base))
		जाओ failure;

	अगर (request_irq(pdev->irq, irq_handler, IRQF_SHARED, "myrb", cb) < 0) अणु
		dev_err(&pdev->dev,
			"Unable to acquire IRQ Channel %d\n", pdev->irq);
		जाओ failure;
	पूर्ण
	cb->irq = pdev->irq;
	वापस cb;

failure:
	dev_err(&pdev->dev,
		"Failed to initialize Controller\n");
	myrb_cleanup(cb);
	वापस शून्य;
पूर्ण

अटल पूर्णांक myrb_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *entry)
अणु
	काष्ठा myrb_hba *cb;
	पूर्णांक ret;

	cb = myrb_detect(dev, entry);
	अगर (!cb)
		वापस -ENODEV;

	ret = myrb_get_hba_config(cb);
	अगर (ret < 0) अणु
		myrb_cleanup(cb);
		वापस ret;
	पूर्ण

	अगर (!myrb_create_mempools(dev, cb)) अणु
		ret = -ENOMEM;
		जाओ failed;
	पूर्ण

	ret = scsi_add_host(cb->host, &dev->dev);
	अगर (ret) अणु
		dev_err(&dev->dev, "scsi_add_host failed with %d\n", ret);
		myrb_destroy_mempools(cb);
		जाओ failed;
	पूर्ण
	scsi_scan_host(cb->host);
	वापस 0;
failed:
	myrb_cleanup(cb);
	वापस ret;
पूर्ण


अटल व्योम myrb_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा myrb_hba *cb = pci_get_drvdata(pdev);

	shost_prपूर्णांकk(KERN_NOTICE, cb->host, "Flushing Cache...");
	myrb_exec_type3(cb, MYRB_CMD_FLUSH, 0);
	myrb_cleanup(cb);
	myrb_destroy_mempools(cb);
पूर्ण


अटल स्थिर काष्ठा pci_device_id myrb_id_table[] = अणु
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_DEC,
			       PCI_DEVICE_ID_DEC_21285,
			       PCI_VENDOR_ID_MYLEX,
			       PCI_DEVICE_ID_MYLEX_DAC960_LA),
		.driver_data	= (अचिन्हित दीर्घ) &DAC960_LA_privdata,
	पूर्ण,
	अणु
		PCI_DEVICE_DATA(MYLEX, DAC960_PG, &DAC960_PG_privdata),
	पूर्ण,
	अणु
		PCI_DEVICE_DATA(MYLEX, DAC960_PD, &DAC960_PD_privdata),
	पूर्ण,
	अणु
		PCI_DEVICE_DATA(MYLEX, DAC960_P, &DAC960_P_privdata),
	पूर्ण,
	अणु0, पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, myrb_id_table);

अटल काष्ठा pci_driver myrb_pci_driver = अणु
	.name		= "myrb",
	.id_table	= myrb_id_table,
	.probe		= myrb_probe,
	.हटाओ		= myrb_हटाओ,
पूर्ण;

अटल पूर्णांक __init myrb_init_module(व्योम)
अणु
	पूर्णांक ret;

	myrb_raid_ढाँचा = raid_class_attach(&myrb_raid_functions);
	अगर (!myrb_raid_ढाँचा)
		वापस -ENODEV;

	ret = pci_रेजिस्टर_driver(&myrb_pci_driver);
	अगर (ret)
		raid_class_release(myrb_raid_ढाँचा);

	वापस ret;
पूर्ण

अटल व्योम __निकास myrb_cleanup_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&myrb_pci_driver);
	raid_class_release(myrb_raid_ढाँचा);
पूर्ण

module_init(myrb_init_module);
module_निकास(myrb_cleanup_module);

MODULE_DESCRIPTION("Mylex DAC960/AcceleRAID/eXtremeRAID driver (Block interface)");
MODULE_AUTHOR("Hannes Reinecke <hare@suse.com>");
MODULE_LICENSE("GPL");
