<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Linux Driver क्रम Mylex DAC960/AcceleRAID/eXtremeRAID PCI RAID Controllers
 *
 * This driver supports the newer, SCSI-based firmware पूर्णांकerface only.
 *
 * Copyright 2017 Hannes Reinecke, SUSE Linux GmbH <hare@suse.com>
 *
 * Based on the original DAC960 driver, which has
 * Copyright 1998-2001 by Leonard N. Zubkoff <lnz@dandelion.com>
 * Portions Copyright 2002 by Mylex (An IBM Business Unit)
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
#समावेश "myrs.h"

अटल काष्ठा raid_ढाँचा *myrs_raid_ढाँचा;

अटल काष्ठा myrs_devstate_name_entry अणु
	क्रमागत myrs_devstate state;
	अक्षर *name;
पूर्ण myrs_devstate_name_list[] = अणु
	अणु MYRS_DEVICE_UNCONFIGURED, "Unconfigured" पूर्ण,
	अणु MYRS_DEVICE_ONLINE, "Online" पूर्ण,
	अणु MYRS_DEVICE_REBUILD, "Rebuild" पूर्ण,
	अणु MYRS_DEVICE_MISSING, "Missing" पूर्ण,
	अणु MYRS_DEVICE_SUSPECTED_CRITICAL, "SuspectedCritical" पूर्ण,
	अणु MYRS_DEVICE_OFFLINE, "Offline" पूर्ण,
	अणु MYRS_DEVICE_CRITICAL, "Critical" पूर्ण,
	अणु MYRS_DEVICE_SUSPECTED_DEAD, "SuspectedDead" पूर्ण,
	अणु MYRS_DEVICE_COMMANDED_OFFLINE, "CommandedOffline" पूर्ण,
	अणु MYRS_DEVICE_STANDBY, "Standby" पूर्ण,
	अणु MYRS_DEVICE_INVALID_STATE, "Invalid" पूर्ण,
पूर्ण;

अटल अक्षर *myrs_devstate_name(क्रमागत myrs_devstate state)
अणु
	काष्ठा myrs_devstate_name_entry *entry = myrs_devstate_name_list;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(myrs_devstate_name_list); i++) अणु
		अगर (entry[i].state == state)
			वापस entry[i].name;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा myrs_raid_level_name_entry अणु
	क्रमागत myrs_raid_level level;
	अक्षर *name;
पूर्ण myrs_raid_level_name_list[] = अणु
	अणु MYRS_RAID_LEVEL0, "RAID0" पूर्ण,
	अणु MYRS_RAID_LEVEL1, "RAID1" पूर्ण,
	अणु MYRS_RAID_LEVEL3, "RAID3 right asymmetric parity" पूर्ण,
	अणु MYRS_RAID_LEVEL5, "RAID5 right asymmetric parity" पूर्ण,
	अणु MYRS_RAID_LEVEL6, "RAID6" पूर्ण,
	अणु MYRS_RAID_JBOD, "JBOD" पूर्ण,
	अणु MYRS_RAID_NEWSPAN, "New Mylex SPAN" पूर्ण,
	अणु MYRS_RAID_LEVEL3F, "RAID3 fixed parity" पूर्ण,
	अणु MYRS_RAID_LEVEL3L, "RAID3 left symmetric parity" पूर्ण,
	अणु MYRS_RAID_SPAN, "Mylex SPAN" पूर्ण,
	अणु MYRS_RAID_LEVEL5L, "RAID5 left symmetric parity" पूर्ण,
	अणु MYRS_RAID_LEVELE, "RAIDE (concatenation)" पूर्ण,
	अणु MYRS_RAID_PHYSICAL, "Physical device" पूर्ण,
पूर्ण;

अटल अक्षर *myrs_raid_level_name(क्रमागत myrs_raid_level level)
अणु
	काष्ठा myrs_raid_level_name_entry *entry = myrs_raid_level_name_list;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(myrs_raid_level_name_list); i++) अणु
		अगर (entry[i].level == level)
			वापस entry[i].name;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * myrs_reset_cmd - clears critical fields in काष्ठा myrs_cmdblk
 */
अटल अंतरभूत व्योम myrs_reset_cmd(काष्ठा myrs_cmdblk *cmd_blk)
अणु
	जोड़ myrs_cmd_mbox *mbox = &cmd_blk->mbox;

	स_रखो(mbox, 0, माप(जोड़ myrs_cmd_mbox));
	cmd_blk->status = 0;
पूर्ण

/*
 * myrs_qcmd - queues Command क्रम DAC960 V2 Series Controllers.
 */
अटल व्योम myrs_qcmd(काष्ठा myrs_hba *cs, काष्ठा myrs_cmdblk *cmd_blk)
अणु
	व्योम __iomem *base = cs->io_base;
	जोड़ myrs_cmd_mbox *mbox = &cmd_blk->mbox;
	जोड़ myrs_cmd_mbox *next_mbox = cs->next_cmd_mbox;

	cs->ग_लिखो_cmd_mbox(next_mbox, mbox);

	अगर (cs->prev_cmd_mbox1->words[0] == 0 ||
	    cs->prev_cmd_mbox2->words[0] == 0)
		cs->get_cmd_mbox(base);

	cs->prev_cmd_mbox2 = cs->prev_cmd_mbox1;
	cs->prev_cmd_mbox1 = next_mbox;

	अगर (++next_mbox > cs->last_cmd_mbox)
		next_mbox = cs->first_cmd_mbox;

	cs->next_cmd_mbox = next_mbox;
पूर्ण

/*
 * myrs_exec_cmd - executes V2 Command and रुकोs क्रम completion.
 */
अटल व्योम myrs_exec_cmd(काष्ठा myrs_hba *cs,
		काष्ठा myrs_cmdblk *cmd_blk)
अणु
	DECLARE_COMPLETION_ONSTACK(complete);
	अचिन्हित दीर्घ flags;

	cmd_blk->complete = &complete;
	spin_lock_irqsave(&cs->queue_lock, flags);
	myrs_qcmd(cs, cmd_blk);
	spin_unlock_irqrestore(&cs->queue_lock, flags);

	रुको_क्रम_completion(&complete);
पूर्ण

/*
 * myrs_report_progress - prपूर्णांकs progress message
 */
अटल व्योम myrs_report_progress(काष्ठा myrs_hba *cs, अचिन्हित लघु ldev_num,
		अचिन्हित अक्षर *msg, अचिन्हित दीर्घ blocks,
		अचिन्हित दीर्घ size)
अणु
	shost_prपूर्णांकk(KERN_INFO, cs->host,
		     "Logical Drive %d: %s in Progress: %d%% completed\n",
		     ldev_num, msg,
		     (100 * (पूर्णांक)(blocks >> 7)) / (पूर्णांक)(size >> 7));
पूर्ण

/*
 * myrs_get_ctlr_info - executes a Controller Inक्रमmation IOCTL Command
 */
अटल अचिन्हित अक्षर myrs_get_ctlr_info(काष्ठा myrs_hba *cs)
अणु
	काष्ठा myrs_cmdblk *cmd_blk = &cs->dcmd_blk;
	जोड़ myrs_cmd_mbox *mbox = &cmd_blk->mbox;
	dma_addr_t ctlr_info_addr;
	जोड़ myrs_sgl *sgl;
	अचिन्हित अक्षर status;
	अचिन्हित लघु ldev_present, ldev_critical, ldev_offline;

	ldev_present = cs->ctlr_info->ldev_present;
	ldev_critical = cs->ctlr_info->ldev_critical;
	ldev_offline = cs->ctlr_info->ldev_offline;

	ctlr_info_addr = dma_map_single(&cs->pdev->dev, cs->ctlr_info,
					माप(काष्ठा myrs_ctlr_info),
					DMA_FROM_DEVICE);
	अगर (dma_mapping_error(&cs->pdev->dev, ctlr_info_addr))
		वापस MYRS_STATUS_FAILED;

	mutex_lock(&cs->dcmd_mutex);
	myrs_reset_cmd(cmd_blk);
	mbox->ctlr_info.id = MYRS_DCMD_TAG;
	mbox->ctlr_info.opcode = MYRS_CMD_OP_IOCTL;
	mbox->ctlr_info.control.dma_ctrl_to_host = true;
	mbox->ctlr_info.control.no_स्वतःsense = true;
	mbox->ctlr_info.dma_size = माप(काष्ठा myrs_ctlr_info);
	mbox->ctlr_info.ctlr_num = 0;
	mbox->ctlr_info.ioctl_opcode = MYRS_IOCTL_GET_CTLR_INFO;
	sgl = &mbox->ctlr_info.dma_addr;
	sgl->sge[0].sge_addr = ctlr_info_addr;
	sgl->sge[0].sge_count = mbox->ctlr_info.dma_size;
	dev_dbg(&cs->host->shost_gendev, "Sending GetControllerInfo\n");
	myrs_exec_cmd(cs, cmd_blk);
	status = cmd_blk->status;
	mutex_unlock(&cs->dcmd_mutex);
	dma_unmap_single(&cs->pdev->dev, ctlr_info_addr,
			 माप(काष्ठा myrs_ctlr_info), DMA_FROM_DEVICE);
	अगर (status == MYRS_STATUS_SUCCESS) अणु
		अगर (cs->ctlr_info->bg_init_active +
		    cs->ctlr_info->ldev_init_active +
		    cs->ctlr_info->pdev_init_active +
		    cs->ctlr_info->cc_active +
		    cs->ctlr_info->rbld_active +
		    cs->ctlr_info->exp_active != 0)
			cs->needs_update = true;
		अगर (cs->ctlr_info->ldev_present != ldev_present ||
		    cs->ctlr_info->ldev_critical != ldev_critical ||
		    cs->ctlr_info->ldev_offline != ldev_offline)
			shost_prपूर्णांकk(KERN_INFO, cs->host,
				     "Logical drive count changes (%d/%d/%d)\n",
				     cs->ctlr_info->ldev_critical,
				     cs->ctlr_info->ldev_offline,
				     cs->ctlr_info->ldev_present);
	पूर्ण

	वापस status;
पूर्ण

/*
 * myrs_get_ldev_info - executes a Logical Device Inक्रमmation IOCTL Command
 */
अटल अचिन्हित अक्षर myrs_get_ldev_info(काष्ठा myrs_hba *cs,
		अचिन्हित लघु ldev_num, काष्ठा myrs_ldev_info *ldev_info)
अणु
	काष्ठा myrs_cmdblk *cmd_blk = &cs->dcmd_blk;
	जोड़ myrs_cmd_mbox *mbox = &cmd_blk->mbox;
	dma_addr_t ldev_info_addr;
	काष्ठा myrs_ldev_info ldev_info_orig;
	जोड़ myrs_sgl *sgl;
	अचिन्हित अक्षर status;

	स_नकल(&ldev_info_orig, ldev_info, माप(काष्ठा myrs_ldev_info));
	ldev_info_addr = dma_map_single(&cs->pdev->dev, ldev_info,
					माप(काष्ठा myrs_ldev_info),
					DMA_FROM_DEVICE);
	अगर (dma_mapping_error(&cs->pdev->dev, ldev_info_addr))
		वापस MYRS_STATUS_FAILED;

	mutex_lock(&cs->dcmd_mutex);
	myrs_reset_cmd(cmd_blk);
	mbox->ldev_info.id = MYRS_DCMD_TAG;
	mbox->ldev_info.opcode = MYRS_CMD_OP_IOCTL;
	mbox->ldev_info.control.dma_ctrl_to_host = true;
	mbox->ldev_info.control.no_स्वतःsense = true;
	mbox->ldev_info.dma_size = माप(काष्ठा myrs_ldev_info);
	mbox->ldev_info.ldev.ldev_num = ldev_num;
	mbox->ldev_info.ioctl_opcode = MYRS_IOCTL_GET_LDEV_INFO_VALID;
	sgl = &mbox->ldev_info.dma_addr;
	sgl->sge[0].sge_addr = ldev_info_addr;
	sgl->sge[0].sge_count = mbox->ldev_info.dma_size;
	dev_dbg(&cs->host->shost_gendev,
		"Sending GetLogicalDeviceInfoValid for ldev %d\n", ldev_num);
	myrs_exec_cmd(cs, cmd_blk);
	status = cmd_blk->status;
	mutex_unlock(&cs->dcmd_mutex);
	dma_unmap_single(&cs->pdev->dev, ldev_info_addr,
			 माप(काष्ठा myrs_ldev_info), DMA_FROM_DEVICE);
	अगर (status == MYRS_STATUS_SUCCESS) अणु
		अचिन्हित लघु ldev_num = ldev_info->ldev_num;
		काष्ठा myrs_ldev_info *new = ldev_info;
		काष्ठा myrs_ldev_info *old = &ldev_info_orig;
		अचिन्हित दीर्घ ldev_size = new->cfg_devsize;

		अगर (new->dev_state != old->dev_state) अणु
			स्थिर अक्षर *name;

			name = myrs_devstate_name(new->dev_state);
			shost_prपूर्णांकk(KERN_INFO, cs->host,
				     "Logical Drive %d is now %s\n",
				     ldev_num, name ? name : "Invalid");
		पूर्ण
		अगर ((new->soft_errs != old->soft_errs) ||
		    (new->cmds_failed != old->cmds_failed) ||
		    (new->deferred_ग_लिखो_errs != old->deferred_ग_लिखो_errs))
			shost_prपूर्णांकk(KERN_INFO, cs->host,
				     "Logical Drive %d Errors: Soft = %d, Failed = %d, Deferred Write = %d\n",
				     ldev_num, new->soft_errs,
				     new->cmds_failed,
				     new->deferred_ग_लिखो_errs);
		अगर (new->bg_init_active)
			myrs_report_progress(cs, ldev_num,
					     "Background Initialization",
					     new->bg_init_lba, ldev_size);
		अन्यथा अगर (new->fg_init_active)
			myrs_report_progress(cs, ldev_num,
					     "Foreground Initialization",
					     new->fg_init_lba, ldev_size);
		अन्यथा अगर (new->migration_active)
			myrs_report_progress(cs, ldev_num,
					     "Data Migration",
					     new->migration_lba, ldev_size);
		अन्यथा अगर (new->patrol_active)
			myrs_report_progress(cs, ldev_num,
					     "Patrol Operation",
					     new->patrol_lba, ldev_size);
		अगर (old->bg_init_active && !new->bg_init_active)
			shost_prपूर्णांकk(KERN_INFO, cs->host,
				     "Logical Drive %d: Background Initialization %s\n",
				     ldev_num,
				     (new->ldev_control.ldev_init_करोne ?
				      "Completed" : "Failed"));
	पूर्ण
	वापस status;
पूर्ण

/*
 * myrs_get_pdev_info - executes a "Read Physical Device Information" Command
 */
अटल अचिन्हित अक्षर myrs_get_pdev_info(काष्ठा myrs_hba *cs,
		अचिन्हित अक्षर channel, अचिन्हित अक्षर target, अचिन्हित अक्षर lun,
		काष्ठा myrs_pdev_info *pdev_info)
अणु
	काष्ठा myrs_cmdblk *cmd_blk = &cs->dcmd_blk;
	जोड़ myrs_cmd_mbox *mbox = &cmd_blk->mbox;
	dma_addr_t pdev_info_addr;
	जोड़ myrs_sgl *sgl;
	अचिन्हित अक्षर status;

	pdev_info_addr = dma_map_single(&cs->pdev->dev, pdev_info,
					माप(काष्ठा myrs_pdev_info),
					DMA_FROM_DEVICE);
	अगर (dma_mapping_error(&cs->pdev->dev, pdev_info_addr))
		वापस MYRS_STATUS_FAILED;

	mutex_lock(&cs->dcmd_mutex);
	myrs_reset_cmd(cmd_blk);
	mbox->pdev_info.opcode = MYRS_CMD_OP_IOCTL;
	mbox->pdev_info.id = MYRS_DCMD_TAG;
	mbox->pdev_info.control.dma_ctrl_to_host = true;
	mbox->pdev_info.control.no_स्वतःsense = true;
	mbox->pdev_info.dma_size = माप(काष्ठा myrs_pdev_info);
	mbox->pdev_info.pdev.lun = lun;
	mbox->pdev_info.pdev.target = target;
	mbox->pdev_info.pdev.channel = channel;
	mbox->pdev_info.ioctl_opcode = MYRS_IOCTL_GET_PDEV_INFO_VALID;
	sgl = &mbox->pdev_info.dma_addr;
	sgl->sge[0].sge_addr = pdev_info_addr;
	sgl->sge[0].sge_count = mbox->pdev_info.dma_size;
	dev_dbg(&cs->host->shost_gendev,
		"Sending GetPhysicalDeviceInfoValid for pdev %d:%d:%d\n",
		channel, target, lun);
	myrs_exec_cmd(cs, cmd_blk);
	status = cmd_blk->status;
	mutex_unlock(&cs->dcmd_mutex);
	dma_unmap_single(&cs->pdev->dev, pdev_info_addr,
			 माप(काष्ठा myrs_pdev_info), DMA_FROM_DEVICE);
	वापस status;
पूर्ण

/*
 * myrs_dev_op - executes a "Device Operation" Command
 */
अटल अचिन्हित अक्षर myrs_dev_op(काष्ठा myrs_hba *cs,
		क्रमागत myrs_ioctl_opcode opcode, क्रमागत myrs_opdev opdev)
अणु
	काष्ठा myrs_cmdblk *cmd_blk = &cs->dcmd_blk;
	जोड़ myrs_cmd_mbox *mbox = &cmd_blk->mbox;
	अचिन्हित अक्षर status;

	mutex_lock(&cs->dcmd_mutex);
	myrs_reset_cmd(cmd_blk);
	mbox->dev_op.opcode = MYRS_CMD_OP_IOCTL;
	mbox->dev_op.id = MYRS_DCMD_TAG;
	mbox->dev_op.control.dma_ctrl_to_host = true;
	mbox->dev_op.control.no_स्वतःsense = true;
	mbox->dev_op.ioctl_opcode = opcode;
	mbox->dev_op.opdev = opdev;
	myrs_exec_cmd(cs, cmd_blk);
	status = cmd_blk->status;
	mutex_unlock(&cs->dcmd_mutex);
	वापस status;
पूर्ण

/*
 * myrs_translate_pdev - translates a Physical Device Channel and
 * TargetID पूर्णांकo a Logical Device.
 */
अटल अचिन्हित अक्षर myrs_translate_pdev(काष्ठा myrs_hba *cs,
		अचिन्हित अक्षर channel, अचिन्हित अक्षर target, अचिन्हित अक्षर lun,
		काष्ठा myrs_devmap *devmap)
अणु
	काष्ठा pci_dev *pdev = cs->pdev;
	dma_addr_t devmap_addr;
	काष्ठा myrs_cmdblk *cmd_blk;
	जोड़ myrs_cmd_mbox *mbox;
	जोड़ myrs_sgl *sgl;
	अचिन्हित अक्षर status;

	स_रखो(devmap, 0x0, माप(काष्ठा myrs_devmap));
	devmap_addr = dma_map_single(&pdev->dev, devmap,
				     माप(काष्ठा myrs_devmap),
				     DMA_FROM_DEVICE);
	अगर (dma_mapping_error(&pdev->dev, devmap_addr))
		वापस MYRS_STATUS_FAILED;

	mutex_lock(&cs->dcmd_mutex);
	cmd_blk = &cs->dcmd_blk;
	mbox = &cmd_blk->mbox;
	mbox->pdev_info.opcode = MYRS_CMD_OP_IOCTL;
	mbox->pdev_info.control.dma_ctrl_to_host = true;
	mbox->pdev_info.control.no_स्वतःsense = true;
	mbox->pdev_info.dma_size = माप(काष्ठा myrs_devmap);
	mbox->pdev_info.pdev.target = target;
	mbox->pdev_info.pdev.channel = channel;
	mbox->pdev_info.pdev.lun = lun;
	mbox->pdev_info.ioctl_opcode = MYRS_IOCTL_XLATE_PDEV_TO_LDEV;
	sgl = &mbox->pdev_info.dma_addr;
	sgl->sge[0].sge_addr = devmap_addr;
	sgl->sge[0].sge_count = mbox->pdev_info.dma_size;

	myrs_exec_cmd(cs, cmd_blk);
	status = cmd_blk->status;
	mutex_unlock(&cs->dcmd_mutex);
	dma_unmap_single(&pdev->dev, devmap_addr,
			 माप(काष्ठा myrs_devmap), DMA_FROM_DEVICE);
	वापस status;
पूर्ण

/*
 * myrs_get_event - executes a Get Event Command
 */
अटल अचिन्हित अक्षर myrs_get_event(काष्ठा myrs_hba *cs,
		अचिन्हित पूर्णांक event_num, काष्ठा myrs_event *event_buf)
अणु
	काष्ठा pci_dev *pdev = cs->pdev;
	dma_addr_t event_addr;
	काष्ठा myrs_cmdblk *cmd_blk = &cs->mcmd_blk;
	जोड़ myrs_cmd_mbox *mbox = &cmd_blk->mbox;
	जोड़ myrs_sgl *sgl;
	अचिन्हित अक्षर status;

	event_addr = dma_map_single(&pdev->dev, event_buf,
				    माप(काष्ठा myrs_event), DMA_FROM_DEVICE);
	अगर (dma_mapping_error(&pdev->dev, event_addr))
		वापस MYRS_STATUS_FAILED;

	mbox->get_event.opcode = MYRS_CMD_OP_IOCTL;
	mbox->get_event.dma_size = माप(काष्ठा myrs_event);
	mbox->get_event.evnum_upper = event_num >> 16;
	mbox->get_event.ctlr_num = 0;
	mbox->get_event.ioctl_opcode = MYRS_IOCTL_GET_EVENT;
	mbox->get_event.evnum_lower = event_num & 0xFFFF;
	sgl = &mbox->get_event.dma_addr;
	sgl->sge[0].sge_addr = event_addr;
	sgl->sge[0].sge_count = mbox->get_event.dma_size;
	myrs_exec_cmd(cs, cmd_blk);
	status = cmd_blk->status;
	dma_unmap_single(&pdev->dev, event_addr,
			 माप(काष्ठा myrs_event), DMA_FROM_DEVICE);

	वापस status;
पूर्ण

/*
 * myrs_get_fwstatus - executes a Get Health Status Command
 */
अटल अचिन्हित अक्षर myrs_get_fwstatus(काष्ठा myrs_hba *cs)
अणु
	काष्ठा myrs_cmdblk *cmd_blk = &cs->mcmd_blk;
	जोड़ myrs_cmd_mbox *mbox = &cmd_blk->mbox;
	जोड़ myrs_sgl *sgl;
	अचिन्हित अक्षर status = cmd_blk->status;

	myrs_reset_cmd(cmd_blk);
	mbox->common.opcode = MYRS_CMD_OP_IOCTL;
	mbox->common.id = MYRS_MCMD_TAG;
	mbox->common.control.dma_ctrl_to_host = true;
	mbox->common.control.no_स्वतःsense = true;
	mbox->common.dma_size = माप(काष्ठा myrs_fwstat);
	mbox->common.ioctl_opcode = MYRS_IOCTL_GET_HEALTH_STATUS;
	sgl = &mbox->common.dma_addr;
	sgl->sge[0].sge_addr = cs->fwstat_addr;
	sgl->sge[0].sge_count = mbox->ctlr_info.dma_size;
	dev_dbg(&cs->host->shost_gendev, "Sending GetHealthStatus\n");
	myrs_exec_cmd(cs, cmd_blk);
	status = cmd_blk->status;

	वापस status;
पूर्ण

/*
 * myrs_enable_mmio_mbox - enables the Memory Mailbox Interface
 */
अटल bool myrs_enable_mmio_mbox(काष्ठा myrs_hba *cs,
		enable_mbox_t enable_mbox_fn)
अणु
	व्योम __iomem *base = cs->io_base;
	काष्ठा pci_dev *pdev = cs->pdev;
	जोड़ myrs_cmd_mbox *cmd_mbox;
	काष्ठा myrs_stat_mbox *stat_mbox;
	जोड़ myrs_cmd_mbox *mbox;
	dma_addr_t mbox_addr;
	अचिन्हित अक्षर status = MYRS_STATUS_FAILED;

	अगर (dma_set_mask(&pdev->dev, DMA_BIT_MASK(64)))
		अगर (dma_set_mask(&pdev->dev, DMA_BIT_MASK(32))) अणु
			dev_err(&pdev->dev, "DMA mask out of range\n");
			वापस false;
		पूर्ण

	/* Temporary dma mapping, used only in the scope of this function */
	mbox = dma_alloc_coherent(&pdev->dev, माप(जोड़ myrs_cmd_mbox),
				  &mbox_addr, GFP_KERNEL);
	अगर (dma_mapping_error(&pdev->dev, mbox_addr))
		वापस false;

	/* These are the base addresses क्रम the command memory mailbox array */
	cs->cmd_mbox_size = MYRS_MAX_CMD_MBOX * माप(जोड़ myrs_cmd_mbox);
	cmd_mbox = dma_alloc_coherent(&pdev->dev, cs->cmd_mbox_size,
				      &cs->cmd_mbox_addr, GFP_KERNEL);
	अगर (dma_mapping_error(&pdev->dev, cs->cmd_mbox_addr)) अणु
		dev_err(&pdev->dev, "Failed to map command mailbox\n");
		जाओ out_मुक्त;
	पूर्ण
	cs->first_cmd_mbox = cmd_mbox;
	cmd_mbox += MYRS_MAX_CMD_MBOX - 1;
	cs->last_cmd_mbox = cmd_mbox;
	cs->next_cmd_mbox = cs->first_cmd_mbox;
	cs->prev_cmd_mbox1 = cs->last_cmd_mbox;
	cs->prev_cmd_mbox2 = cs->last_cmd_mbox - 1;

	/* These are the base addresses क्रम the status memory mailbox array */
	cs->stat_mbox_size = MYRS_MAX_STAT_MBOX * माप(काष्ठा myrs_stat_mbox);
	stat_mbox = dma_alloc_coherent(&pdev->dev, cs->stat_mbox_size,
				       &cs->stat_mbox_addr, GFP_KERNEL);
	अगर (dma_mapping_error(&pdev->dev, cs->stat_mbox_addr)) अणु
		dev_err(&pdev->dev, "Failed to map status mailbox\n");
		जाओ out_मुक्त;
	पूर्ण

	cs->first_stat_mbox = stat_mbox;
	stat_mbox += MYRS_MAX_STAT_MBOX - 1;
	cs->last_stat_mbox = stat_mbox;
	cs->next_stat_mbox = cs->first_stat_mbox;

	cs->fwstat_buf = dma_alloc_coherent(&pdev->dev,
					    माप(काष्ठा myrs_fwstat),
					    &cs->fwstat_addr, GFP_KERNEL);
	अगर (dma_mapping_error(&pdev->dev, cs->fwstat_addr)) अणु
		dev_err(&pdev->dev, "Failed to map firmware health buffer\n");
		cs->fwstat_buf = शून्य;
		जाओ out_मुक्त;
	पूर्ण
	cs->ctlr_info = kzalloc(माप(काष्ठा myrs_ctlr_info),
				GFP_KERNEL | GFP_DMA);
	अगर (!cs->ctlr_info)
		जाओ out_मुक्त;

	cs->event_buf = kzalloc(माप(काष्ठा myrs_event),
				GFP_KERNEL | GFP_DMA);
	अगर (!cs->event_buf)
		जाओ out_मुक्त;

	/* Enable the Memory Mailbox Interface. */
	स_रखो(mbox, 0, माप(जोड़ myrs_cmd_mbox));
	mbox->set_mbox.id = 1;
	mbox->set_mbox.opcode = MYRS_CMD_OP_IOCTL;
	mbox->set_mbox.control.no_स्वतःsense = true;
	mbox->set_mbox.first_cmd_mbox_size_kb =
		(MYRS_MAX_CMD_MBOX * माप(जोड़ myrs_cmd_mbox)) >> 10;
	mbox->set_mbox.first_stat_mbox_size_kb =
		(MYRS_MAX_STAT_MBOX * माप(काष्ठा myrs_stat_mbox)) >> 10;
	mbox->set_mbox.second_cmd_mbox_size_kb = 0;
	mbox->set_mbox.second_stat_mbox_size_kb = 0;
	mbox->set_mbox.sense_len = 0;
	mbox->set_mbox.ioctl_opcode = MYRS_IOCTL_SET_MEM_MBOX;
	mbox->set_mbox.fwstat_buf_size_kb = 1;
	mbox->set_mbox.fwstat_buf_addr = cs->fwstat_addr;
	mbox->set_mbox.first_cmd_mbox_addr = cs->cmd_mbox_addr;
	mbox->set_mbox.first_stat_mbox_addr = cs->stat_mbox_addr;
	status = enable_mbox_fn(base, mbox_addr);

out_मुक्त:
	dma_मुक्त_coherent(&pdev->dev, माप(जोड़ myrs_cmd_mbox),
			  mbox, mbox_addr);
	अगर (status != MYRS_STATUS_SUCCESS)
		dev_err(&pdev->dev, "Failed to enable mailbox, status %X\n",
			status);
	वापस (status == MYRS_STATUS_SUCCESS);
पूर्ण

/*
 * myrs_get_config - पढ़ोs the Configuration Inक्रमmation
 */
अटल पूर्णांक myrs_get_config(काष्ठा myrs_hba *cs)
अणु
	काष्ठा myrs_ctlr_info *info = cs->ctlr_info;
	काष्ठा Scsi_Host *shost = cs->host;
	अचिन्हित अक्षर status;
	अचिन्हित अक्षर model[20];
	अचिन्हित अक्षर fw_version[12];
	पूर्णांक i, model_len;

	/* Get data पूर्णांकo dma-able area, then copy पूर्णांकo permanent location */
	mutex_lock(&cs->cinfo_mutex);
	status = myrs_get_ctlr_info(cs);
	mutex_unlock(&cs->cinfo_mutex);
	अगर (status != MYRS_STATUS_SUCCESS) अणु
		shost_prपूर्णांकk(KERN_ERR, shost,
			     "Failed to get controller information\n");
		वापस -ENODEV;
	पूर्ण

	/* Initialize the Controller Model Name and Full Model Name fields. */
	model_len = माप(info->ctlr_name);
	अगर (model_len > माप(model)-1)
		model_len = माप(model)-1;
	स_नकल(model, info->ctlr_name, model_len);
	model_len--;
	जबतक (model[model_len] == ' ' || model[model_len] == '\0')
		model_len--;
	model[++model_len] = '\0';
	म_नकल(cs->model_name, "DAC960 ");
	म_जोड़ो(cs->model_name, model);
	/* Initialize the Controller Firmware Version field. */
	प्र_लिखो(fw_version, "%d.%02d-%02d",
		info->fw_major_version, info->fw_minor_version,
		info->fw_turn_number);
	अगर (info->fw_major_version == 6 &&
	    info->fw_minor_version == 0 &&
	    info->fw_turn_number < 1) अणु
		shost_prपूर्णांकk(KERN_WARNING, shost,
			"FIRMWARE VERSION %s DOES NOT PROVIDE THE CONTROLLER\n"
			"STATUS MONITORING FUNCTIONALITY NEEDED BY THIS DRIVER.\n"
			"PLEASE UPGRADE TO VERSION 6.00-01 OR ABOVE.\n",
			fw_version);
		वापस -ENODEV;
	पूर्ण
	/* Initialize the Controller Channels and Tarमाला_लो. */
	shost->max_channel = info->physchan_present + info->virtchan_present;
	shost->max_id = info->max_tarमाला_लो[0];
	क्रम (i = 1; i < 16; i++) अणु
		अगर (!info->max_tarमाला_लो[i])
			जारी;
		अगर (shost->max_id < info->max_tarमाला_लो[i])
			shost->max_id = info->max_tarमाला_लो[i];
	पूर्ण

	/*
	 * Initialize the Controller Queue Depth, Driver Queue Depth,
	 * Logical Drive Count, Maximum Blocks per Command, Controller
	 * Scatter/Gather Limit, and Driver Scatter/Gather Limit.
	 * The Driver Queue Depth must be at most three less than
	 * the Controller Queue Depth; tag '1' is reserved क्रम
	 * direct commands, and tag '2' क्रम monitoring commands.
	 */
	shost->can_queue = info->max_tcq - 3;
	अगर (shost->can_queue > MYRS_MAX_CMD_MBOX - 3)
		shost->can_queue = MYRS_MAX_CMD_MBOX - 3;
	shost->max_sectors = info->max_transfer_size;
	shost->sg_tablesize = info->max_sge;
	अगर (shost->sg_tablesize > MYRS_SG_LIMIT)
		shost->sg_tablesize = MYRS_SG_LIMIT;

	shost_prपूर्णांकk(KERN_INFO, shost,
		"Configuring %s PCI RAID Controller\n", model);
	shost_prपूर्णांकk(KERN_INFO, shost,
		"  Firmware Version: %s, Channels: %d, Memory Size: %dMB\n",
		fw_version, info->physchan_present, info->mem_size_mb);

	shost_prपूर्णांकk(KERN_INFO, shost,
		     "  Controller Queue Depth: %d, Maximum Blocks per Command: %d\n",
		     shost->can_queue, shost->max_sectors);

	shost_prपूर्णांकk(KERN_INFO, shost,
		     "  Driver Queue Depth: %d, Scatter/Gather Limit: %d of %d Segments\n",
		     shost->can_queue, shost->sg_tablesize, MYRS_SG_LIMIT);
	क्रम (i = 0; i < info->physchan_max; i++) अणु
		अगर (!info->max_tarमाला_लो[i])
			जारी;
		shost_prपूर्णांकk(KERN_INFO, shost,
			     "  Device Channel %d: max %d devices\n",
			     i, info->max_tarमाला_लो[i]);
	पूर्ण
	shost_prपूर्णांकk(KERN_INFO, shost,
		     "  Physical: %d/%d channels, %d disks, %d devices\n",
		     info->physchan_present, info->physchan_max,
		     info->pdisk_present, info->pdev_present);

	shost_prपूर्णांकk(KERN_INFO, shost,
		     "  Logical: %d/%d channels, %d disks\n",
		     info->virtchan_present, info->virtchan_max,
		     info->ldev_present);
	वापस 0;
पूर्ण

/*
 * myrs_log_event - prपूर्णांकs a Controller Event message
 */
अटल काष्ठा अणु
	पूर्णांक ev_code;
	अचिन्हित अक्षर *ev_msg;
पूर्ण myrs_ev_list[] = अणु
	/* Physical Device Events (0x0000 - 0x007F) */
	अणु 0x0001, "P Online" पूर्ण,
	अणु 0x0002, "P Standby" पूर्ण,
	अणु 0x0005, "P Automatic Rebuild Started" पूर्ण,
	अणु 0x0006, "P Manual Rebuild Started" पूर्ण,
	अणु 0x0007, "P Rebuild Completed" पूर्ण,
	अणु 0x0008, "P Rebuild Cancelled" पूर्ण,
	अणु 0x0009, "P Rebuild Failed for Unknown Reasons" पूर्ण,
	अणु 0x000A, "P Rebuild Failed due to New Physical Device" पूर्ण,
	अणु 0x000B, "P Rebuild Failed due to Logical Drive Failure" पूर्ण,
	अणु 0x000C, "S Offline" पूर्ण,
	अणु 0x000D, "P Found" पूर्ण,
	अणु 0x000E, "P Removed" पूर्ण,
	अणु 0x000F, "P Unconfigured" पूर्ण,
	अणु 0x0010, "P Expand Capacity Started" पूर्ण,
	अणु 0x0011, "P Expand Capacity Completed" पूर्ण,
	अणु 0x0012, "P Expand Capacity Failed" पूर्ण,
	अणु 0x0013, "P Command Timed Out" पूर्ण,
	अणु 0x0014, "P Command Aborted" पूर्ण,
	अणु 0x0015, "P Command Retried" पूर्ण,
	अणु 0x0016, "P Parity Error" पूर्ण,
	अणु 0x0017, "P Soft Error" पूर्ण,
	अणु 0x0018, "P Miscellaneous Error" पूर्ण,
	अणु 0x0019, "P Reset" पूर्ण,
	अणु 0x001A, "P Active Spare Found" पूर्ण,
	अणु 0x001B, "P Warm Spare Found" पूर्ण,
	अणु 0x001C, "S Sense Data Received" पूर्ण,
	अणु 0x001D, "P Initialization Started" पूर्ण,
	अणु 0x001E, "P Initialization Completed" पूर्ण,
	अणु 0x001F, "P Initialization Failed" पूर्ण,
	अणु 0x0020, "P Initialization Cancelled" पूर्ण,
	अणु 0x0021, "P Failed because Write Recovery Failed" पूर्ण,
	अणु 0x0022, "P Failed because SCSI Bus Reset Failed" पूर्ण,
	अणु 0x0023, "P Failed because of Double Check Condition" पूर्ण,
	अणु 0x0024, "P Failed because Device Cannot Be Accessed" पूर्ण,
	अणु 0x0025, "P Failed because of Gross Error on SCSI Processor" पूर्ण,
	अणु 0x0026, "P Failed because of Bad Tag from Device" पूर्ण,
	अणु 0x0027, "P Failed because of Command Timeout" पूर्ण,
	अणु 0x0028, "P Failed because of System Reset" पूर्ण,
	अणु 0x0029, "P Failed because of Busy Status or Parity Error" पूर्ण,
	अणु 0x002A, "P Failed because Host Set Device to Failed State" पूर्ण,
	अणु 0x002B, "P Failed because of Selection Timeout" पूर्ण,
	अणु 0x002C, "P Failed because of SCSI Bus Phase Error" पूर्ण,
	अणु 0x002D, "P Failed because Device Returned Unknown Status" पूर्ण,
	अणु 0x002E, "P Failed because Device Not Ready" पूर्ण,
	अणु 0x002F, "P Failed because Device Not Found at Startup" पूर्ण,
	अणु 0x0030, "P Failed because COD Write Operation Failed" पूर्ण,
	अणु 0x0031, "P Failed because BDT Write Operation Failed" पूर्ण,
	अणु 0x0039, "P Missing at Startup" पूर्ण,
	अणु 0x003A, "P Start Rebuild Failed due to Physical Drive Too Small" पूर्ण,
	अणु 0x003C, "P Temporarily Offline Device Automatically Made Online" पूर्ण,
	अणु 0x003D, "P Standby Rebuild Started" पूर्ण,
	/* Logical Device Events (0x0080 - 0x00FF) */
	अणु 0x0080, "M Consistency Check Started" पूर्ण,
	अणु 0x0081, "M Consistency Check Completed" पूर्ण,
	अणु 0x0082, "M Consistency Check Cancelled" पूर्ण,
	अणु 0x0083, "M Consistency Check Completed With Errors" पूर्ण,
	अणु 0x0084, "M Consistency Check Failed due to Logical Drive Failure" पूर्ण,
	अणु 0x0085, "M Consistency Check Failed due to Physical Device Failure" पूर्ण,
	अणु 0x0086, "L Offline" पूर्ण,
	अणु 0x0087, "L Critical" पूर्ण,
	अणु 0x0088, "L Online" पूर्ण,
	अणु 0x0089, "M Automatic Rebuild Started" पूर्ण,
	अणु 0x008A, "M Manual Rebuild Started" पूर्ण,
	अणु 0x008B, "M Rebuild Completed" पूर्ण,
	अणु 0x008C, "M Rebuild Cancelled" पूर्ण,
	अणु 0x008D, "M Rebuild Failed for Unknown Reasons" पूर्ण,
	अणु 0x008E, "M Rebuild Failed due to New Physical Device" पूर्ण,
	अणु 0x008F, "M Rebuild Failed due to Logical Drive Failure" पूर्ण,
	अणु 0x0090, "M Initialization Started" पूर्ण,
	अणु 0x0091, "M Initialization Completed" पूर्ण,
	अणु 0x0092, "M Initialization Cancelled" पूर्ण,
	अणु 0x0093, "M Initialization Failed" पूर्ण,
	अणु 0x0094, "L Found" पूर्ण,
	अणु 0x0095, "L Deleted" पूर्ण,
	अणु 0x0096, "M Expand Capacity Started" पूर्ण,
	अणु 0x0097, "M Expand Capacity Completed" पूर्ण,
	अणु 0x0098, "M Expand Capacity Failed" पूर्ण,
	अणु 0x0099, "L Bad Block Found" पूर्ण,
	अणु 0x009A, "L Size Changed" पूर्ण,
	अणु 0x009B, "L Type Changed" पूर्ण,
	अणु 0x009C, "L Bad Data Block Found" पूर्ण,
	अणु 0x009E, "L Read of Data Block in BDT" पूर्ण,
	अणु 0x009F, "L Write Back Data for Disk Block Lost" पूर्ण,
	अणु 0x00A0, "L Temporarily Offline RAID-5/3 Drive Made Online" पूर्ण,
	अणु 0x00A1, "L Temporarily Offline RAID-6/1/0/7 Drive Made Online" पूर्ण,
	अणु 0x00A2, "L Standby Rebuild Started" पूर्ण,
	/* Fault Management Events (0x0100 - 0x017F) */
	अणु 0x0140, "E Fan %d Failed" पूर्ण,
	अणु 0x0141, "E Fan %d OK" पूर्ण,
	अणु 0x0142, "E Fan %d Not Present" पूर्ण,
	अणु 0x0143, "E Power Supply %d Failed" पूर्ण,
	अणु 0x0144, "E Power Supply %d OK" पूर्ण,
	अणु 0x0145, "E Power Supply %d Not Present" पूर्ण,
	अणु 0x0146, "E Temperature Sensor %d Temperature Exceeds Safe Limit" पूर्ण,
	अणु 0x0147, "E Temperature Sensor %d Temperature Exceeds Working Limit" पूर्ण,
	अणु 0x0148, "E Temperature Sensor %d Temperature Normal" पूर्ण,
	अणु 0x0149, "E Temperature Sensor %d Not Present" पूर्ण,
	अणु 0x014A, "E Enclosure Management Unit %d Access Critical" पूर्ण,
	अणु 0x014B, "E Enclosure Management Unit %d Access OK" पूर्ण,
	अणु 0x014C, "E Enclosure Management Unit %d Access Offline" पूर्ण,
	/* Controller Events (0x0180 - 0x01FF) */
	अणु 0x0181, "C Cache Write Back Error" पूर्ण,
	अणु 0x0188, "C Battery Backup Unit Found" पूर्ण,
	अणु 0x0189, "C Battery Backup Unit Charge Level Low" पूर्ण,
	अणु 0x018A, "C Battery Backup Unit Charge Level OK" पूर्ण,
	अणु 0x0193, "C Installation Aborted" पूर्ण,
	अणु 0x0195, "C Battery Backup Unit Physically Removed" पूर्ण,
	अणु 0x0196, "C Memory Error During Warm Boot" पूर्ण,
	अणु 0x019E, "C Memory Soft ECC Error Corrected" पूर्ण,
	अणु 0x019F, "C Memory Hard ECC Error Corrected" पूर्ण,
	अणु 0x01A2, "C Battery Backup Unit Failed" पूर्ण,
	अणु 0x01AB, "C Mirror Race Recovery Failed" पूर्ण,
	अणु 0x01AC, "C Mirror Race on Critical Drive" पूर्ण,
	/* Controller Internal Processor Events */
	अणु 0x0380, "C Internal Controller Hung" पूर्ण,
	अणु 0x0381, "C Internal Controller Firmware Breakpoint" पूर्ण,
	अणु 0x0390, "C Internal Controller i960 Processor Specific Error" पूर्ण,
	अणु 0x03A0, "C Internal Controller StrongARM Processor Specific Error" पूर्ण,
	अणु 0, "" पूर्ण
पूर्ण;

अटल व्योम myrs_log_event(काष्ठा myrs_hba *cs, काष्ठा myrs_event *ev)
अणु
	अचिन्हित अक्षर msg_buf[MYRS_LINE_BUFFER_SIZE];
	पूर्णांक ev_idx = 0, ev_code;
	अचिन्हित अक्षर ev_type, *ev_msg;
	काष्ठा Scsi_Host *shost = cs->host;
	काष्ठा scsi_device *sdev;
	काष्ठा scsi_sense_hdr sshdr = अणु0पूर्ण;
	अचिन्हित अक्षर sense_info[4];
	अचिन्हित अक्षर cmd_specअगरic[4];

	अगर (ev->ev_code == 0x1C) अणु
		अगर (!scsi_normalize_sense(ev->sense_data, 40, &sshdr)) अणु
			स_रखो(&sshdr, 0x0, माप(sshdr));
			स_रखो(sense_info, 0x0, माप(sense_info));
			स_रखो(cmd_specअगरic, 0x0, माप(cmd_specअगरic));
		पूर्ण अन्यथा अणु
			स_नकल(sense_info, &ev->sense_data[3], 4);
			स_नकल(cmd_specअगरic, &ev->sense_data[7], 4);
		पूर्ण
	पूर्ण
	अगर (sshdr.sense_key == VENDOR_SPECIFIC &&
	    (sshdr.asc == 0x80 || sshdr.asc == 0x81))
		ev->ev_code = ((sshdr.asc - 0x80) << 8 | sshdr.ascq);
	जबतक (true) अणु
		ev_code = myrs_ev_list[ev_idx].ev_code;
		अगर (ev_code == ev->ev_code || ev_code == 0)
			अवरोध;
		ev_idx++;
	पूर्ण
	ev_type = myrs_ev_list[ev_idx].ev_msg[0];
	ev_msg = &myrs_ev_list[ev_idx].ev_msg[2];
	अगर (ev_code == 0) अणु
		shost_prपूर्णांकk(KERN_WARNING, shost,
			     "Unknown Controller Event Code %04X\n",
			     ev->ev_code);
		वापस;
	पूर्ण
	चयन (ev_type) अणु
	हाल 'P':
		sdev = scsi_device_lookup(shost, ev->channel,
					  ev->target, 0);
		sdev_prपूर्णांकk(KERN_INFO, sdev, "event %d: Physical Device %s\n",
			    ev->ev_seq, ev_msg);
		अगर (sdev && sdev->hostdata &&
		    sdev->channel < cs->ctlr_info->physchan_present) अणु
			काष्ठा myrs_pdev_info *pdev_info = sdev->hostdata;

			चयन (ev->ev_code) अणु
			हाल 0x0001:
			हाल 0x0007:
				pdev_info->dev_state = MYRS_DEVICE_ONLINE;
				अवरोध;
			हाल 0x0002:
				pdev_info->dev_state = MYRS_DEVICE_STANDBY;
				अवरोध;
			हाल 0x000C:
				pdev_info->dev_state = MYRS_DEVICE_OFFLINE;
				अवरोध;
			हाल 0x000E:
				pdev_info->dev_state = MYRS_DEVICE_MISSING;
				अवरोध;
			हाल 0x000F:
				pdev_info->dev_state = MYRS_DEVICE_UNCONFIGURED;
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल 'L':
		shost_prपूर्णांकk(KERN_INFO, shost,
			     "event %d: Logical Drive %d %s\n",
			     ev->ev_seq, ev->lun, ev_msg);
		cs->needs_update = true;
		अवरोध;
	हाल 'M':
		shost_prपूर्णांकk(KERN_INFO, shost,
			     "event %d: Logical Drive %d %s\n",
			     ev->ev_seq, ev->lun, ev_msg);
		cs->needs_update = true;
		अवरोध;
	हाल 'S':
		अगर (sshdr.sense_key == NO_SENSE ||
		    (sshdr.sense_key == NOT_READY &&
		     sshdr.asc == 0x04 && (sshdr.ascq == 0x01 ||
					    sshdr.ascq == 0x02)))
			अवरोध;
		shost_prपूर्णांकk(KERN_INFO, shost,
			     "event %d: Physical Device %d:%d %s\n",
			     ev->ev_seq, ev->channel, ev->target, ev_msg);
		shost_prपूर्णांकk(KERN_INFO, shost,
			     "Physical Device %d:%d Sense Key = %X, ASC = %02X, ASCQ = %02X\n",
			     ev->channel, ev->target,
			     sshdr.sense_key, sshdr.asc, sshdr.ascq);
		shost_prपूर्णांकk(KERN_INFO, shost,
			     "Physical Device %d:%d Sense Information = %02X%02X%02X%02X %02X%02X%02X%02X\n",
			     ev->channel, ev->target,
			     sense_info[0], sense_info[1],
			     sense_info[2], sense_info[3],
			     cmd_specअगरic[0], cmd_specअगरic[1],
			     cmd_specअगरic[2], cmd_specअगरic[3]);
		अवरोध;
	हाल 'E':
		अगर (cs->disable_enc_msg)
			अवरोध;
		प्र_लिखो(msg_buf, ev_msg, ev->lun);
		shost_prपूर्णांकk(KERN_INFO, shost, "event %d: Enclosure %d %s\n",
			     ev->ev_seq, ev->target, msg_buf);
		अवरोध;
	हाल 'C':
		shost_prपूर्णांकk(KERN_INFO, shost, "event %d: Controller %s\n",
			     ev->ev_seq, ev_msg);
		अवरोध;
	शेष:
		shost_prपूर्णांकk(KERN_INFO, shost,
			     "event %d: Unknown Event Code %04X\n",
			     ev->ev_seq, ev->ev_code);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * SCSI sysfs पूर्णांकerface functions
 */
अटल sमाप_प्रकार raid_state_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा myrs_hba *cs = shost_priv(sdev->host);
	पूर्णांक ret;

	अगर (!sdev->hostdata)
		वापस snम_लिखो(buf, 16, "Unknown\n");

	अगर (sdev->channel >= cs->ctlr_info->physchan_present) अणु
		काष्ठा myrs_ldev_info *ldev_info = sdev->hostdata;
		स्थिर अक्षर *name;

		name = myrs_devstate_name(ldev_info->dev_state);
		अगर (name)
			ret = snम_लिखो(buf, 32, "%s\n", name);
		अन्यथा
			ret = snम_लिखो(buf, 32, "Invalid (%02X)\n",
				       ldev_info->dev_state);
	पूर्ण अन्यथा अणु
		काष्ठा myrs_pdev_info *pdev_info;
		स्थिर अक्षर *name;

		pdev_info = sdev->hostdata;
		name = myrs_devstate_name(pdev_info->dev_state);
		अगर (name)
			ret = snम_लिखो(buf, 32, "%s\n", name);
		अन्यथा
			ret = snम_लिखो(buf, 32, "Invalid (%02X)\n",
				       pdev_info->dev_state);
	पूर्ण
	वापस ret;
पूर्ण

अटल sमाप_प्रकार raid_state_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा myrs_hba *cs = shost_priv(sdev->host);
	काष्ठा myrs_cmdblk *cmd_blk;
	जोड़ myrs_cmd_mbox *mbox;
	क्रमागत myrs_devstate new_state;
	अचिन्हित लघु ldev_num;
	अचिन्हित अक्षर status;

	अगर (!म_भेदन(buf, "offline", 7) ||
	    !म_भेदन(buf, "kill", 4))
		new_state = MYRS_DEVICE_OFFLINE;
	अन्यथा अगर (!म_भेदन(buf, "online", 6))
		new_state = MYRS_DEVICE_ONLINE;
	अन्यथा अगर (!म_भेदन(buf, "standby", 7))
		new_state = MYRS_DEVICE_STANDBY;
	अन्यथा
		वापस -EINVAL;

	अगर (sdev->channel < cs->ctlr_info->physchan_present) अणु
		काष्ठा myrs_pdev_info *pdev_info = sdev->hostdata;
		काष्ठा myrs_devmap *pdev_devmap =
			(काष्ठा myrs_devmap *)&pdev_info->rsvd13;

		अगर (pdev_info->dev_state == new_state) अणु
			sdev_prपूर्णांकk(KERN_INFO, sdev,
				    "Device already in %s\n",
				    myrs_devstate_name(new_state));
			वापस count;
		पूर्ण
		status = myrs_translate_pdev(cs, sdev->channel, sdev->id,
					     sdev->lun, pdev_devmap);
		अगर (status != MYRS_STATUS_SUCCESS)
			वापस -ENXIO;
		ldev_num = pdev_devmap->ldev_num;
	पूर्ण अन्यथा अणु
		काष्ठा myrs_ldev_info *ldev_info = sdev->hostdata;

		अगर (ldev_info->dev_state == new_state) अणु
			sdev_prपूर्णांकk(KERN_INFO, sdev,
				    "Device already in %s\n",
				    myrs_devstate_name(new_state));
			वापस count;
		पूर्ण
		ldev_num = ldev_info->ldev_num;
	पूर्ण
	mutex_lock(&cs->dcmd_mutex);
	cmd_blk = &cs->dcmd_blk;
	myrs_reset_cmd(cmd_blk);
	mbox = &cmd_blk->mbox;
	mbox->common.opcode = MYRS_CMD_OP_IOCTL;
	mbox->common.id = MYRS_DCMD_TAG;
	mbox->common.control.dma_ctrl_to_host = true;
	mbox->common.control.no_स्वतःsense = true;
	mbox->set_devstate.ioctl_opcode = MYRS_IOCTL_SET_DEVICE_STATE;
	mbox->set_devstate.state = new_state;
	mbox->set_devstate.ldev.ldev_num = ldev_num;
	myrs_exec_cmd(cs, cmd_blk);
	status = cmd_blk->status;
	mutex_unlock(&cs->dcmd_mutex);
	अगर (status == MYRS_STATUS_SUCCESS) अणु
		अगर (sdev->channel < cs->ctlr_info->physchan_present) अणु
			काष्ठा myrs_pdev_info *pdev_info = sdev->hostdata;

			pdev_info->dev_state = new_state;
		पूर्ण अन्यथा अणु
			काष्ठा myrs_ldev_info *ldev_info = sdev->hostdata;

			ldev_info->dev_state = new_state;
		पूर्ण
		sdev_prपूर्णांकk(KERN_INFO, sdev,
			    "Set device state to %s\n",
			    myrs_devstate_name(new_state));
		वापस count;
	पूर्ण
	sdev_prपूर्णांकk(KERN_INFO, sdev,
		    "Failed to set device state to %s, status 0x%02x\n",
		    myrs_devstate_name(new_state), status);
	वापस -EINVAL;
पूर्ण
अटल DEVICE_ATTR_RW(raid_state);

अटल sमाप_प्रकार raid_level_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा myrs_hba *cs = shost_priv(sdev->host);
	स्थिर अक्षर *name = शून्य;

	अगर (!sdev->hostdata)
		वापस snम_लिखो(buf, 16, "Unknown\n");

	अगर (sdev->channel >= cs->ctlr_info->physchan_present) अणु
		काष्ठा myrs_ldev_info *ldev_info;

		ldev_info = sdev->hostdata;
		name = myrs_raid_level_name(ldev_info->raid_level);
		अगर (!name)
			वापस snम_लिखो(buf, 32, "Invalid (%02X)\n",
					ldev_info->dev_state);

	पूर्ण अन्यथा
		name = myrs_raid_level_name(MYRS_RAID_PHYSICAL);

	वापस snम_लिखो(buf, 32, "%s\n", name);
पूर्ण
अटल DEVICE_ATTR_RO(raid_level);

अटल sमाप_प्रकार rebuild_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा myrs_hba *cs = shost_priv(sdev->host);
	काष्ठा myrs_ldev_info *ldev_info;
	अचिन्हित लघु ldev_num;
	अचिन्हित अक्षर status;

	अगर (sdev->channel < cs->ctlr_info->physchan_present)
		वापस snम_लिखो(buf, 32, "physical device - not rebuilding\n");

	ldev_info = sdev->hostdata;
	ldev_num = ldev_info->ldev_num;
	status = myrs_get_ldev_info(cs, ldev_num, ldev_info);
	अगर (status != MYRS_STATUS_SUCCESS) अणु
		sdev_prपूर्णांकk(KERN_INFO, sdev,
			    "Failed to get device information, status 0x%02x\n",
			    status);
		वापस -EIO;
	पूर्ण
	अगर (ldev_info->rbld_active) अणु
		वापस snम_लिखो(buf, 32, "rebuilding block %zu of %zu\n",
				(माप_प्रकार)ldev_info->rbld_lba,
				(माप_प्रकार)ldev_info->cfg_devsize);
	पूर्ण अन्यथा
		वापस snम_लिखो(buf, 32, "not rebuilding\n");
पूर्ण

अटल sमाप_प्रकार rebuild_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा myrs_hba *cs = shost_priv(sdev->host);
	काष्ठा myrs_ldev_info *ldev_info;
	काष्ठा myrs_cmdblk *cmd_blk;
	जोड़ myrs_cmd_mbox *mbox;
	अचिन्हित लघु ldev_num;
	अचिन्हित अक्षर status;
	पूर्णांक rebuild, ret;

	अगर (sdev->channel < cs->ctlr_info->physchan_present)
		वापस -EINVAL;

	ldev_info = sdev->hostdata;
	अगर (!ldev_info)
		वापस -ENXIO;
	ldev_num = ldev_info->ldev_num;

	ret = kstrtoपूर्णांक(buf, 0, &rebuild);
	अगर (ret)
		वापस ret;

	status = myrs_get_ldev_info(cs, ldev_num, ldev_info);
	अगर (status != MYRS_STATUS_SUCCESS) अणु
		sdev_prपूर्णांकk(KERN_INFO, sdev,
			    "Failed to get device information, status 0x%02x\n",
			    status);
		वापस -EIO;
	पूर्ण

	अगर (rebuild && ldev_info->rbld_active) अणु
		sdev_prपूर्णांकk(KERN_INFO, sdev,
			    "Rebuild Not Initiated; already in progress\n");
		वापस -EALREADY;
	पूर्ण
	अगर (!rebuild && !ldev_info->rbld_active) अणु
		sdev_prपूर्णांकk(KERN_INFO, sdev,
			    "Rebuild Not Cancelled; no rebuild in progress\n");
		वापस count;
	पूर्ण

	mutex_lock(&cs->dcmd_mutex);
	cmd_blk = &cs->dcmd_blk;
	myrs_reset_cmd(cmd_blk);
	mbox = &cmd_blk->mbox;
	mbox->common.opcode = MYRS_CMD_OP_IOCTL;
	mbox->common.id = MYRS_DCMD_TAG;
	mbox->common.control.dma_ctrl_to_host = true;
	mbox->common.control.no_स्वतःsense = true;
	अगर (rebuild) अणु
		mbox->ldev_info.ldev.ldev_num = ldev_num;
		mbox->ldev_info.ioctl_opcode = MYRS_IOCTL_RBLD_DEVICE_START;
	पूर्ण अन्यथा अणु
		mbox->ldev_info.ldev.ldev_num = ldev_num;
		mbox->ldev_info.ioctl_opcode = MYRS_IOCTL_RBLD_DEVICE_STOP;
	पूर्ण
	myrs_exec_cmd(cs, cmd_blk);
	status = cmd_blk->status;
	mutex_unlock(&cs->dcmd_mutex);
	अगर (status) अणु
		sdev_prपूर्णांकk(KERN_INFO, sdev,
			    "Rebuild Not %s, status 0x%02x\n",
			    rebuild ? "Initiated" : "Cancelled", status);
		ret = -EIO;
	पूर्ण अन्यथा अणु
		sdev_prपूर्णांकk(KERN_INFO, sdev, "Rebuild %s\n",
			    rebuild ? "Initiated" : "Cancelled");
		ret = count;
	पूर्ण

	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RW(rebuild);

अटल sमाप_प्रकार consistency_check_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा myrs_hba *cs = shost_priv(sdev->host);
	काष्ठा myrs_ldev_info *ldev_info;
	अचिन्हित लघु ldev_num;

	अगर (sdev->channel < cs->ctlr_info->physchan_present)
		वापस snम_लिखो(buf, 32, "physical device - not checking\n");

	ldev_info = sdev->hostdata;
	अगर (!ldev_info)
		वापस -ENXIO;
	ldev_num = ldev_info->ldev_num;
	myrs_get_ldev_info(cs, ldev_num, ldev_info);
	अगर (ldev_info->cc_active)
		वापस snम_लिखो(buf, 32, "checking block %zu of %zu\n",
				(माप_प्रकार)ldev_info->cc_lba,
				(माप_प्रकार)ldev_info->cfg_devsize);
	अन्यथा
		वापस snम_लिखो(buf, 32, "not checking\n");
पूर्ण

अटल sमाप_प्रकार consistency_check_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा myrs_hba *cs = shost_priv(sdev->host);
	काष्ठा myrs_ldev_info *ldev_info;
	काष्ठा myrs_cmdblk *cmd_blk;
	जोड़ myrs_cmd_mbox *mbox;
	अचिन्हित लघु ldev_num;
	अचिन्हित अक्षर status;
	पूर्णांक check, ret;

	अगर (sdev->channel < cs->ctlr_info->physchan_present)
		वापस -EINVAL;

	ldev_info = sdev->hostdata;
	अगर (!ldev_info)
		वापस -ENXIO;
	ldev_num = ldev_info->ldev_num;

	ret = kstrtoपूर्णांक(buf, 0, &check);
	अगर (ret)
		वापस ret;

	status = myrs_get_ldev_info(cs, ldev_num, ldev_info);
	अगर (status != MYRS_STATUS_SUCCESS) अणु
		sdev_prपूर्णांकk(KERN_INFO, sdev,
			    "Failed to get device information, status 0x%02x\n",
			    status);
		वापस -EIO;
	पूर्ण
	अगर (check && ldev_info->cc_active) अणु
		sdev_prपूर्णांकk(KERN_INFO, sdev,
			    "Consistency Check Not Initiated; "
			    "already in progress\n");
		वापस -EALREADY;
	पूर्ण
	अगर (!check && !ldev_info->cc_active) अणु
		sdev_prपूर्णांकk(KERN_INFO, sdev,
			    "Consistency Check Not Cancelled; "
			    "check not in progress\n");
		वापस count;
	पूर्ण

	mutex_lock(&cs->dcmd_mutex);
	cmd_blk = &cs->dcmd_blk;
	myrs_reset_cmd(cmd_blk);
	mbox = &cmd_blk->mbox;
	mbox->common.opcode = MYRS_CMD_OP_IOCTL;
	mbox->common.id = MYRS_DCMD_TAG;
	mbox->common.control.dma_ctrl_to_host = true;
	mbox->common.control.no_स्वतःsense = true;
	अगर (check) अणु
		mbox->cc.ldev.ldev_num = ldev_num;
		mbox->cc.ioctl_opcode = MYRS_IOCTL_CC_START;
		mbox->cc.restore_consistency = true;
		mbox->cc.initialized_area_only = false;
	पूर्ण अन्यथा अणु
		mbox->cc.ldev.ldev_num = ldev_num;
		mbox->cc.ioctl_opcode = MYRS_IOCTL_CC_STOP;
	पूर्ण
	myrs_exec_cmd(cs, cmd_blk);
	status = cmd_blk->status;
	mutex_unlock(&cs->dcmd_mutex);
	अगर (status != MYRS_STATUS_SUCCESS) अणु
		sdev_prपूर्णांकk(KERN_INFO, sdev,
			    "Consistency Check Not %s, status 0x%02x\n",
			    check ? "Initiated" : "Cancelled", status);
		ret = -EIO;
	पूर्ण अन्यथा अणु
		sdev_prपूर्णांकk(KERN_INFO, sdev, "Consistency Check %s\n",
			    check ? "Initiated" : "Cancelled");
		ret = count;
	पूर्ण

	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RW(consistency_check);

अटल काष्ठा device_attribute *myrs_sdev_attrs[] = अणु
	&dev_attr_consistency_check,
	&dev_attr_rebuild,
	&dev_attr_raid_state,
	&dev_attr_raid_level,
	शून्य,
पूर्ण;

अटल sमाप_प्रकार serial_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा myrs_hba *cs = shost_priv(shost);
	अक्षर serial[17];

	स_नकल(serial, cs->ctlr_info->serial_number, 16);
	serial[16] = '\0';
	वापस snम_लिखो(buf, 16, "%s\n", serial);
पूर्ण
अटल DEVICE_ATTR_RO(serial);

अटल sमाप_प्रकार ctlr_num_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा myrs_hba *cs = shost_priv(shost);

	वापस snम_लिखो(buf, 20, "%d\n", cs->host->host_no);
पूर्ण
अटल DEVICE_ATTR_RO(ctlr_num);

अटल काष्ठा myrs_cpu_type_tbl अणु
	क्रमागत myrs_cpu_type type;
	अक्षर *name;
पूर्ण myrs_cpu_type_names[] = अणु
	अणु MYRS_CPUTYPE_i960CA, "i960CA" पूर्ण,
	अणु MYRS_CPUTYPE_i960RD, "i960RD" पूर्ण,
	अणु MYRS_CPUTYPE_i960RN, "i960RN" पूर्ण,
	अणु MYRS_CPUTYPE_i960RP, "i960RP" पूर्ण,
	अणु MYRS_CPUTYPE_NorthBay, "NorthBay" पूर्ण,
	अणु MYRS_CPUTYPE_StrongArm, "StrongARM" पूर्ण,
	अणु MYRS_CPUTYPE_i960RM, "i960RM" पूर्ण,
पूर्ण;

अटल sमाप_प्रकार processor_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा myrs_hba *cs = shost_priv(shost);
	काष्ठा myrs_cpu_type_tbl *tbl;
	स्थिर अक्षर *first_processor = शून्य;
	स्थिर अक्षर *second_processor = शून्य;
	काष्ठा myrs_ctlr_info *info = cs->ctlr_info;
	sमाप_प्रकार ret;
	पूर्णांक i;

	अगर (info->cpu[0].cpu_count) अणु
		tbl = myrs_cpu_type_names;
		क्रम (i = 0; i < ARRAY_SIZE(myrs_cpu_type_names); i++) अणु
			अगर (tbl[i].type == info->cpu[0].cpu_type) अणु
				first_processor = tbl[i].name;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (info->cpu[1].cpu_count) अणु
		tbl = myrs_cpu_type_names;
		क्रम (i = 0; i < ARRAY_SIZE(myrs_cpu_type_names); i++) अणु
			अगर (tbl[i].type == info->cpu[1].cpu_type) अणु
				second_processor = tbl[i].name;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (first_processor && second_processor)
		ret = snम_लिखो(buf, 64, "1: %s (%s, %d cpus)\n"
			       "2: %s (%s, %d cpus)\n",
			       info->cpu[0].cpu_name,
			       first_processor, info->cpu[0].cpu_count,
			       info->cpu[1].cpu_name,
			       second_processor, info->cpu[1].cpu_count);
	अन्यथा अगर (first_processor && !second_processor)
		ret = snम_लिखो(buf, 64, "1: %s (%s, %d cpus)\n2: absent\n",
			       info->cpu[0].cpu_name,
			       first_processor, info->cpu[0].cpu_count);
	अन्यथा अगर (!first_processor && second_processor)
		ret = snम_लिखो(buf, 64, "1: absent\n2: %s (%s, %d cpus)\n",
			       info->cpu[1].cpu_name,
			       second_processor, info->cpu[1].cpu_count);
	अन्यथा
		ret = snम_लिखो(buf, 64, "1: absent\n2: absent\n");

	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RO(processor);

अटल sमाप_प्रकार model_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा myrs_hba *cs = shost_priv(shost);

	वापस snम_लिखो(buf, 28, "%s\n", cs->model_name);
पूर्ण
अटल DEVICE_ATTR_RO(model);

अटल sमाप_प्रकार ctlr_type_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा myrs_hba *cs = shost_priv(shost);

	वापस snम_लिखो(buf, 4, "%d\n", cs->ctlr_info->ctlr_type);
पूर्ण
अटल DEVICE_ATTR_RO(ctlr_type);

अटल sमाप_प्रकार cache_size_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा myrs_hba *cs = shost_priv(shost);

	वापस snम_लिखो(buf, 8, "%d MB\n", cs->ctlr_info->cache_size_mb);
पूर्ण
अटल DEVICE_ATTR_RO(cache_size);

अटल sमाप_प्रकार firmware_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा myrs_hba *cs = shost_priv(shost);

	वापस snम_लिखो(buf, 16, "%d.%02d-%02d\n",
			cs->ctlr_info->fw_major_version,
			cs->ctlr_info->fw_minor_version,
			cs->ctlr_info->fw_turn_number);
पूर्ण
अटल DEVICE_ATTR_RO(firmware);

अटल sमाप_प्रकार discovery_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा myrs_hba *cs = shost_priv(shost);
	काष्ठा myrs_cmdblk *cmd_blk;
	जोड़ myrs_cmd_mbox *mbox;
	अचिन्हित अक्षर status;

	mutex_lock(&cs->dcmd_mutex);
	cmd_blk = &cs->dcmd_blk;
	myrs_reset_cmd(cmd_blk);
	mbox = &cmd_blk->mbox;
	mbox->common.opcode = MYRS_CMD_OP_IOCTL;
	mbox->common.id = MYRS_DCMD_TAG;
	mbox->common.control.dma_ctrl_to_host = true;
	mbox->common.control.no_स्वतःsense = true;
	mbox->common.ioctl_opcode = MYRS_IOCTL_START_DISCOVERY;
	myrs_exec_cmd(cs, cmd_blk);
	status = cmd_blk->status;
	mutex_unlock(&cs->dcmd_mutex);
	अगर (status != MYRS_STATUS_SUCCESS) अणु
		shost_prपूर्णांकk(KERN_INFO, shost,
			     "Discovery Not Initiated, status %02X\n",
			     status);
		वापस -EINVAL;
	पूर्ण
	shost_prपूर्णांकk(KERN_INFO, shost, "Discovery Initiated\n");
	cs->next_evseq = 0;
	cs->needs_update = true;
	queue_delayed_work(cs->work_q, &cs->monitor_work, 1);
	flush_delayed_work(&cs->monitor_work);
	shost_prपूर्णांकk(KERN_INFO, shost, "Discovery Completed\n");

	वापस count;
पूर्ण
अटल DEVICE_ATTR_WO(discovery);

अटल sमाप_प्रकार flush_cache_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा myrs_hba *cs = shost_priv(shost);
	अचिन्हित अक्षर status;

	status = myrs_dev_op(cs, MYRS_IOCTL_FLUSH_DEVICE_DATA,
			     MYRS_RAID_CONTROLLER);
	अगर (status == MYRS_STATUS_SUCCESS) अणु
		shost_prपूर्णांकk(KERN_INFO, shost, "Cache Flush Completed\n");
		वापस count;
	पूर्ण
	shost_prपूर्णांकk(KERN_INFO, shost,
		     "Cache Flush failed, status 0x%02x\n", status);
	वापस -EIO;
पूर्ण
अटल DEVICE_ATTR_WO(flush_cache);

अटल sमाप_प्रकार disable_enclosure_messages_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा myrs_hba *cs = shost_priv(shost);

	वापस snम_लिखो(buf, 3, "%d\n", cs->disable_enc_msg);
पूर्ण

अटल sमाप_प्रकार disable_enclosure_messages_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा myrs_hba *cs = shost_priv(sdev->host);
	पूर्णांक value, ret;

	ret = kstrtoपूर्णांक(buf, 0, &value);
	अगर (ret)
		वापस ret;

	अगर (value > 2)
		वापस -EINVAL;

	cs->disable_enc_msg = value;
	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(disable_enclosure_messages);

अटल काष्ठा device_attribute *myrs_shost_attrs[] = अणु
	&dev_attr_serial,
	&dev_attr_ctlr_num,
	&dev_attr_processor,
	&dev_attr_model,
	&dev_attr_ctlr_type,
	&dev_attr_cache_size,
	&dev_attr_firmware,
	&dev_attr_discovery,
	&dev_attr_flush_cache,
	&dev_attr_disable_enclosure_messages,
	शून्य,
पूर्ण;

/*
 * SCSI midlayer पूर्णांकerface
 */
अटल पूर्णांक myrs_host_reset(काष्ठा scsi_cmnd *scmd)
अणु
	काष्ठा Scsi_Host *shost = scmd->device->host;
	काष्ठा myrs_hba *cs = shost_priv(shost);

	cs->reset(cs->io_base);
	वापस SUCCESS;
पूर्ण

अटल व्योम myrs_mode_sense(काष्ठा myrs_hba *cs, काष्ठा scsi_cmnd *scmd,
		काष्ठा myrs_ldev_info *ldev_info)
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
	modes[2] = 0x10; /* Enable FUA */
	अगर (ldev_info->ldev_control.wce == MYRS_LOGICALDEVICE_RO)
		modes[2] |= 0x80;
	अगर (!dbd) अणु
		अचिन्हित अक्षर *block_desc = &modes[4];

		modes[3] = 8;
		put_unaligned_be32(ldev_info->cfg_devsize, &block_desc[0]);
		put_unaligned_be32(ldev_info->devsize_bytes, &block_desc[5]);
	पूर्ण
	mode_pg[0] = 0x08;
	mode_pg[1] = 0x12;
	अगर (ldev_info->ldev_control.rce == MYRS_READCACHE_DISABLED)
		mode_pg[2] |= 0x01;
	अगर (ldev_info->ldev_control.wce == MYRS_WRITECACHE_ENABLED ||
	    ldev_info->ldev_control.wce == MYRS_INTELLIGENT_WRITECACHE_ENABLED)
		mode_pg[2] |= 0x04;
	अगर (ldev_info->cacheline_size) अणु
		mode_pg[2] |= 0x08;
		put_unaligned_be16(1 << ldev_info->cacheline_size,
				   &mode_pg[14]);
	पूर्ण

	scsi_sg_copy_from_buffer(scmd, modes, mode_len);
पूर्ण

अटल पूर्णांक myrs_queuecommand(काष्ठा Scsi_Host *shost,
		काष्ठा scsi_cmnd *scmd)
अणु
	काष्ठा myrs_hba *cs = shost_priv(shost);
	काष्ठा myrs_cmdblk *cmd_blk = scsi_cmd_priv(scmd);
	जोड़ myrs_cmd_mbox *mbox = &cmd_blk->mbox;
	काष्ठा scsi_device *sdev = scmd->device;
	जोड़ myrs_sgl *hw_sge;
	dma_addr_t sense_addr;
	काष्ठा scatterlist *sgl;
	अचिन्हित दीर्घ flags, समयout;
	पूर्णांक nsge;

	अगर (!scmd->device->hostdata) अणु
		scmd->result = (DID_NO_CONNECT << 16);
		scmd->scsi_करोne(scmd);
		वापस 0;
	पूर्ण

	चयन (scmd->cmnd[0]) अणु
	हाल REPORT_LUNS:
		scsi_build_sense_buffer(0, scmd->sense_buffer, ILLEGAL_REQUEST,
					0x20, 0x0);
		scmd->result = (DRIVER_SENSE << 24) | SAM_STAT_CHECK_CONDITION;
		scmd->scsi_करोne(scmd);
		वापस 0;
	हाल MODE_SENSE:
		अगर (scmd->device->channel >= cs->ctlr_info->physchan_present) अणु
			काष्ठा myrs_ldev_info *ldev_info = sdev->hostdata;

			अगर ((scmd->cmnd[2] & 0x3F) != 0x3F &&
			    (scmd->cmnd[2] & 0x3F) != 0x08) अणु
				/* Illegal request, invalid field in CDB */
				scsi_build_sense_buffer(0, scmd->sense_buffer,
					ILLEGAL_REQUEST, 0x24, 0);
				scmd->result = (DRIVER_SENSE << 24) |
					SAM_STAT_CHECK_CONDITION;
			पूर्ण अन्यथा अणु
				myrs_mode_sense(cs, scmd, ldev_info);
				scmd->result = (DID_OK << 16);
			पूर्ण
			scmd->scsi_करोne(scmd);
			वापस 0;
		पूर्ण
		अवरोध;
	पूर्ण

	myrs_reset_cmd(cmd_blk);
	cmd_blk->sense = dma_pool_alloc(cs->sense_pool, GFP_ATOMIC,
					&sense_addr);
	अगर (!cmd_blk->sense)
		वापस SCSI_MLQUEUE_HOST_BUSY;
	cmd_blk->sense_addr = sense_addr;

	समयout = scmd->request->समयout;
	अगर (scmd->cmd_len <= 10) अणु
		अगर (scmd->device->channel >= cs->ctlr_info->physchan_present) अणु
			काष्ठा myrs_ldev_info *ldev_info = sdev->hostdata;

			mbox->SCSI_10.opcode = MYRS_CMD_OP_SCSI_10;
			mbox->SCSI_10.pdev.lun = ldev_info->lun;
			mbox->SCSI_10.pdev.target = ldev_info->target;
			mbox->SCSI_10.pdev.channel = ldev_info->channel;
			mbox->SCSI_10.pdev.ctlr = 0;
		पूर्ण अन्यथा अणु
			mbox->SCSI_10.opcode = MYRS_CMD_OP_SCSI_10_PASSTHRU;
			mbox->SCSI_10.pdev.lun = sdev->lun;
			mbox->SCSI_10.pdev.target = sdev->id;
			mbox->SCSI_10.pdev.channel = sdev->channel;
		पूर्ण
		mbox->SCSI_10.id = scmd->request->tag + 3;
		mbox->SCSI_10.control.dma_ctrl_to_host =
			(scmd->sc_data_direction == DMA_FROM_DEVICE);
		अगर (scmd->request->cmd_flags & REQ_FUA)
			mbox->SCSI_10.control.fua = true;
		mbox->SCSI_10.dma_size = scsi_bufflen(scmd);
		mbox->SCSI_10.sense_addr = cmd_blk->sense_addr;
		mbox->SCSI_10.sense_len = MYRS_SENSE_SIZE;
		mbox->SCSI_10.cdb_len = scmd->cmd_len;
		अगर (समयout > 60) अणु
			mbox->SCSI_10.पंचांगo.पंचांगo_scale = MYRS_TMO_SCALE_MINUTES;
			mbox->SCSI_10.पंचांगo.पंचांगo_val = समयout / 60;
		पूर्ण अन्यथा अणु
			mbox->SCSI_10.पंचांगo.पंचांगo_scale = MYRS_TMO_SCALE_SECONDS;
			mbox->SCSI_10.पंचांगo.पंचांगo_val = समयout;
		पूर्ण
		स_नकल(&mbox->SCSI_10.cdb, scmd->cmnd, scmd->cmd_len);
		hw_sge = &mbox->SCSI_10.dma_addr;
		cmd_blk->dcdb = शून्य;
	पूर्ण अन्यथा अणु
		dma_addr_t dcdb_dma;

		cmd_blk->dcdb = dma_pool_alloc(cs->dcdb_pool, GFP_ATOMIC,
					       &dcdb_dma);
		अगर (!cmd_blk->dcdb) अणु
			dma_pool_मुक्त(cs->sense_pool, cmd_blk->sense,
				      cmd_blk->sense_addr);
			cmd_blk->sense = शून्य;
			cmd_blk->sense_addr = 0;
			वापस SCSI_MLQUEUE_HOST_BUSY;
		पूर्ण
		cmd_blk->dcdb_dma = dcdb_dma;
		अगर (scmd->device->channel >= cs->ctlr_info->physchan_present) अणु
			काष्ठा myrs_ldev_info *ldev_info = sdev->hostdata;

			mbox->SCSI_255.opcode = MYRS_CMD_OP_SCSI_256;
			mbox->SCSI_255.pdev.lun = ldev_info->lun;
			mbox->SCSI_255.pdev.target = ldev_info->target;
			mbox->SCSI_255.pdev.channel = ldev_info->channel;
			mbox->SCSI_255.pdev.ctlr = 0;
		पूर्ण अन्यथा अणु
			mbox->SCSI_255.opcode = MYRS_CMD_OP_SCSI_255_PASSTHRU;
			mbox->SCSI_255.pdev.lun = sdev->lun;
			mbox->SCSI_255.pdev.target = sdev->id;
			mbox->SCSI_255.pdev.channel = sdev->channel;
		पूर्ण
		mbox->SCSI_255.id = scmd->request->tag + 3;
		mbox->SCSI_255.control.dma_ctrl_to_host =
			(scmd->sc_data_direction == DMA_FROM_DEVICE);
		अगर (scmd->request->cmd_flags & REQ_FUA)
			mbox->SCSI_255.control.fua = true;
		mbox->SCSI_255.dma_size = scsi_bufflen(scmd);
		mbox->SCSI_255.sense_addr = cmd_blk->sense_addr;
		mbox->SCSI_255.sense_len = MYRS_SENSE_SIZE;
		mbox->SCSI_255.cdb_len = scmd->cmd_len;
		mbox->SCSI_255.cdb_addr = cmd_blk->dcdb_dma;
		अगर (समयout > 60) अणु
			mbox->SCSI_255.पंचांगo.पंचांगo_scale = MYRS_TMO_SCALE_MINUTES;
			mbox->SCSI_255.पंचांगo.पंचांगo_val = समयout / 60;
		पूर्ण अन्यथा अणु
			mbox->SCSI_255.पंचांगo.पंचांगo_scale = MYRS_TMO_SCALE_SECONDS;
			mbox->SCSI_255.पंचांगo.पंचांगo_val = समयout;
		पूर्ण
		स_नकल(cmd_blk->dcdb, scmd->cmnd, scmd->cmd_len);
		hw_sge = &mbox->SCSI_255.dma_addr;
	पूर्ण
	अगर (scmd->sc_data_direction == DMA_NONE)
		जाओ submit;
	nsge = scsi_dma_map(scmd);
	अगर (nsge == 1) अणु
		sgl = scsi_sglist(scmd);
		hw_sge->sge[0].sge_addr = (u64)sg_dma_address(sgl);
		hw_sge->sge[0].sge_count = (u64)sg_dma_len(sgl);
	पूर्ण अन्यथा अणु
		काष्ठा myrs_sge *hw_sgl;
		dma_addr_t hw_sgl_addr;
		पूर्णांक i;

		अगर (nsge > 2) अणु
			hw_sgl = dma_pool_alloc(cs->sg_pool, GFP_ATOMIC,
						&hw_sgl_addr);
			अगर (WARN_ON(!hw_sgl)) अणु
				अगर (cmd_blk->dcdb) अणु
					dma_pool_मुक्त(cs->dcdb_pool,
						      cmd_blk->dcdb,
						      cmd_blk->dcdb_dma);
					cmd_blk->dcdb = शून्य;
					cmd_blk->dcdb_dma = 0;
				पूर्ण
				dma_pool_मुक्त(cs->sense_pool,
					      cmd_blk->sense,
					      cmd_blk->sense_addr);
				cmd_blk->sense = शून्य;
				cmd_blk->sense_addr = 0;
				वापस SCSI_MLQUEUE_HOST_BUSY;
			पूर्ण
			cmd_blk->sgl = hw_sgl;
			cmd_blk->sgl_addr = hw_sgl_addr;
			अगर (scmd->cmd_len <= 10)
				mbox->SCSI_10.control.add_sge_mem = true;
			अन्यथा
				mbox->SCSI_255.control.add_sge_mem = true;
			hw_sge->ext.sge0_len = nsge;
			hw_sge->ext.sge0_addr = cmd_blk->sgl_addr;
		पूर्ण अन्यथा
			hw_sgl = hw_sge->sge;

		scsi_क्रम_each_sg(scmd, sgl, nsge, i) अणु
			अगर (WARN_ON(!hw_sgl)) अणु
				scsi_dma_unmap(scmd);
				scmd->result = (DID_ERROR << 16);
				scmd->scsi_करोne(scmd);
				वापस 0;
			पूर्ण
			hw_sgl->sge_addr = (u64)sg_dma_address(sgl);
			hw_sgl->sge_count = (u64)sg_dma_len(sgl);
			hw_sgl++;
		पूर्ण
	पूर्ण
submit:
	spin_lock_irqsave(&cs->queue_lock, flags);
	myrs_qcmd(cs, cmd_blk);
	spin_unlock_irqrestore(&cs->queue_lock, flags);

	वापस 0;
पूर्ण

अटल अचिन्हित लघु myrs_translate_ldev(काष्ठा myrs_hba *cs,
		काष्ठा scsi_device *sdev)
अणु
	अचिन्हित लघु ldev_num;
	अचिन्हित पूर्णांक chan_offset =
		sdev->channel - cs->ctlr_info->physchan_present;

	ldev_num = sdev->id + chan_offset * sdev->host->max_id;

	वापस ldev_num;
पूर्ण

अटल पूर्णांक myrs_slave_alloc(काष्ठा scsi_device *sdev)
अणु
	काष्ठा myrs_hba *cs = shost_priv(sdev->host);
	अचिन्हित अक्षर status;

	अगर (sdev->channel > sdev->host->max_channel)
		वापस 0;

	अगर (sdev->channel >= cs->ctlr_info->physchan_present) अणु
		काष्ठा myrs_ldev_info *ldev_info;
		अचिन्हित लघु ldev_num;

		अगर (sdev->lun > 0)
			वापस -ENXIO;

		ldev_num = myrs_translate_ldev(cs, sdev);

		ldev_info = kzalloc(माप(*ldev_info), GFP_KERNEL|GFP_DMA);
		अगर (!ldev_info)
			वापस -ENOMEM;

		status = myrs_get_ldev_info(cs, ldev_num, ldev_info);
		अगर (status != MYRS_STATUS_SUCCESS) अणु
			sdev->hostdata = शून्य;
			kमुक्त(ldev_info);
		पूर्ण अन्यथा अणु
			क्रमागत raid_level level;

			dev_dbg(&sdev->sdev_gendev,
				"Logical device mapping %d:%d:%d -> %d\n",
				ldev_info->channel, ldev_info->target,
				ldev_info->lun, ldev_info->ldev_num);

			sdev->hostdata = ldev_info;
			चयन (ldev_info->raid_level) अणु
			हाल MYRS_RAID_LEVEL0:
				level = RAID_LEVEL_LINEAR;
				अवरोध;
			हाल MYRS_RAID_LEVEL1:
				level = RAID_LEVEL_1;
				अवरोध;
			हाल MYRS_RAID_LEVEL3:
			हाल MYRS_RAID_LEVEL3F:
			हाल MYRS_RAID_LEVEL3L:
				level = RAID_LEVEL_3;
				अवरोध;
			हाल MYRS_RAID_LEVEL5:
			हाल MYRS_RAID_LEVEL5L:
				level = RAID_LEVEL_5;
				अवरोध;
			हाल MYRS_RAID_LEVEL6:
				level = RAID_LEVEL_6;
				अवरोध;
			हाल MYRS_RAID_LEVELE:
			हाल MYRS_RAID_NEWSPAN:
			हाल MYRS_RAID_SPAN:
				level = RAID_LEVEL_LINEAR;
				अवरोध;
			हाल MYRS_RAID_JBOD:
				level = RAID_LEVEL_JBOD;
				अवरोध;
			शेष:
				level = RAID_LEVEL_UNKNOWN;
				अवरोध;
			पूर्ण
			raid_set_level(myrs_raid_ढाँचा,
				       &sdev->sdev_gendev, level);
			अगर (ldev_info->dev_state != MYRS_DEVICE_ONLINE) अणु
				स्थिर अक्षर *name;

				name = myrs_devstate_name(ldev_info->dev_state);
				sdev_prपूर्णांकk(KERN_DEBUG, sdev,
					    "logical device in state %s\n",
					    name ? name : "Invalid");
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा myrs_pdev_info *pdev_info;

		pdev_info = kzalloc(माप(*pdev_info), GFP_KERNEL|GFP_DMA);
		अगर (!pdev_info)
			वापस -ENOMEM;

		status = myrs_get_pdev_info(cs, sdev->channel,
					    sdev->id, sdev->lun,
					    pdev_info);
		अगर (status != MYRS_STATUS_SUCCESS) अणु
			sdev->hostdata = शून्य;
			kमुक्त(pdev_info);
			वापस -ENXIO;
		पूर्ण
		sdev->hostdata = pdev_info;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक myrs_slave_configure(काष्ठा scsi_device *sdev)
अणु
	काष्ठा myrs_hba *cs = shost_priv(sdev->host);
	काष्ठा myrs_ldev_info *ldev_info;

	अगर (sdev->channel > sdev->host->max_channel)
		वापस -ENXIO;

	अगर (sdev->channel < cs->ctlr_info->physchan_present) अणु
		/* Skip HBA device */
		अगर (sdev->type == TYPE_RAID)
			वापस -ENXIO;
		sdev->no_uld_attach = 1;
		वापस 0;
	पूर्ण
	अगर (sdev->lun != 0)
		वापस -ENXIO;

	ldev_info = sdev->hostdata;
	अगर (!ldev_info)
		वापस -ENXIO;
	अगर (ldev_info->ldev_control.wce == MYRS_WRITECACHE_ENABLED ||
	    ldev_info->ldev_control.wce == MYRS_INTELLIGENT_WRITECACHE_ENABLED)
		sdev->wce_शेष_on = 1;
	sdev->tagged_supported = 1;
	वापस 0;
पूर्ण

अटल व्योम myrs_slave_destroy(काष्ठा scsi_device *sdev)
अणु
	kमुक्त(sdev->hostdata);
पूर्ण

अटल काष्ठा scsi_host_ढाँचा myrs_ढाँचा = अणु
	.module			= THIS_MODULE,
	.name			= "DAC960",
	.proc_name		= "myrs",
	.queuecommand		= myrs_queuecommand,
	.eh_host_reset_handler	= myrs_host_reset,
	.slave_alloc		= myrs_slave_alloc,
	.slave_configure	= myrs_slave_configure,
	.slave_destroy		= myrs_slave_destroy,
	.cmd_size		= माप(काष्ठा myrs_cmdblk),
	.shost_attrs		= myrs_shost_attrs,
	.sdev_attrs		= myrs_sdev_attrs,
	.this_id		= -1,
पूर्ण;

अटल काष्ठा myrs_hba *myrs_alloc_host(काष्ठा pci_dev *pdev,
		स्थिर काष्ठा pci_device_id *entry)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा myrs_hba *cs;

	shost = scsi_host_alloc(&myrs_ढाँचा, माप(काष्ठा myrs_hba));
	अगर (!shost)
		वापस शून्य;

	shost->max_cmd_len = 16;
	shost->max_lun = 256;
	cs = shost_priv(shost);
	mutex_init(&cs->dcmd_mutex);
	mutex_init(&cs->cinfo_mutex);
	cs->host = shost;

	वापस cs;
पूर्ण

/*
 * RAID ढाँचा functions
 */

/**
 * myrs_is_raid - वापस boolean indicating device is raid volume
 * @dev: the device काष्ठा object
 */
अटल पूर्णांक
myrs_is_raid(काष्ठा device *dev)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा myrs_hba *cs = shost_priv(sdev->host);

	वापस (sdev->channel >= cs->ctlr_info->physchan_present) ? 1 : 0;
पूर्ण

/**
 * myrs_get_resync - get raid volume resync percent complete
 * @dev: the device काष्ठा object
 */
अटल व्योम
myrs_get_resync(काष्ठा device *dev)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा myrs_hba *cs = shost_priv(sdev->host);
	काष्ठा myrs_ldev_info *ldev_info = sdev->hostdata;
	u64 percent_complete = 0;

	अगर (sdev->channel < cs->ctlr_info->physchan_present || !ldev_info)
		वापस;
	अगर (ldev_info->rbld_active) अणु
		अचिन्हित लघु ldev_num = ldev_info->ldev_num;

		myrs_get_ldev_info(cs, ldev_num, ldev_info);
		percent_complete = ldev_info->rbld_lba * 100;
		करो_भाग(percent_complete, ldev_info->cfg_devsize);
	पूर्ण
	raid_set_resync(myrs_raid_ढाँचा, dev, percent_complete);
पूर्ण

/**
 * myrs_get_state - get raid volume status
 * @dev: the device काष्ठा object
 */
अटल व्योम
myrs_get_state(काष्ठा device *dev)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा myrs_hba *cs = shost_priv(sdev->host);
	काष्ठा myrs_ldev_info *ldev_info = sdev->hostdata;
	क्रमागत raid_state state = RAID_STATE_UNKNOWN;

	अगर (sdev->channel < cs->ctlr_info->physchan_present || !ldev_info)
		state = RAID_STATE_UNKNOWN;
	अन्यथा अणु
		चयन (ldev_info->dev_state) अणु
		हाल MYRS_DEVICE_ONLINE:
			state = RAID_STATE_ACTIVE;
			अवरोध;
		हाल MYRS_DEVICE_SUSPECTED_CRITICAL:
		हाल MYRS_DEVICE_CRITICAL:
			state = RAID_STATE_DEGRADED;
			अवरोध;
		हाल MYRS_DEVICE_REBUILD:
			state = RAID_STATE_RESYNCING;
			अवरोध;
		हाल MYRS_DEVICE_UNCONFIGURED:
		हाल MYRS_DEVICE_INVALID_STATE:
			state = RAID_STATE_UNKNOWN;
			अवरोध;
		शेष:
			state = RAID_STATE_OFFLINE;
		पूर्ण
	पूर्ण
	raid_set_state(myrs_raid_ढाँचा, dev, state);
पूर्ण

अटल काष्ठा raid_function_ढाँचा myrs_raid_functions = अणु
	.cookie		= &myrs_ढाँचा,
	.is_raid	= myrs_is_raid,
	.get_resync	= myrs_get_resync,
	.get_state	= myrs_get_state,
पूर्ण;

/*
 * PCI पूर्णांकerface functions
 */
अटल व्योम myrs_flush_cache(काष्ठा myrs_hba *cs)
अणु
	myrs_dev_op(cs, MYRS_IOCTL_FLUSH_DEVICE_DATA, MYRS_RAID_CONTROLLER);
पूर्ण

अटल व्योम myrs_handle_scsi(काष्ठा myrs_hba *cs, काष्ठा myrs_cmdblk *cmd_blk,
		काष्ठा scsi_cmnd *scmd)
अणु
	अचिन्हित अक्षर status;

	अगर (!cmd_blk)
		वापस;

	scsi_dma_unmap(scmd);
	status = cmd_blk->status;
	अगर (cmd_blk->sense) अणु
		अगर (status == MYRS_STATUS_FAILED && cmd_blk->sense_len) अणु
			अचिन्हित पूर्णांक sense_len = SCSI_SENSE_BUFFERSIZE;

			अगर (sense_len > cmd_blk->sense_len)
				sense_len = cmd_blk->sense_len;
			स_नकल(scmd->sense_buffer, cmd_blk->sense, sense_len);
		पूर्ण
		dma_pool_मुक्त(cs->sense_pool, cmd_blk->sense,
			      cmd_blk->sense_addr);
		cmd_blk->sense = शून्य;
		cmd_blk->sense_addr = 0;
	पूर्ण
	अगर (cmd_blk->dcdb) अणु
		dma_pool_मुक्त(cs->dcdb_pool, cmd_blk->dcdb,
			      cmd_blk->dcdb_dma);
		cmd_blk->dcdb = शून्य;
		cmd_blk->dcdb_dma = 0;
	पूर्ण
	अगर (cmd_blk->sgl) अणु
		dma_pool_मुक्त(cs->sg_pool, cmd_blk->sgl,
			      cmd_blk->sgl_addr);
		cmd_blk->sgl = शून्य;
		cmd_blk->sgl_addr = 0;
	पूर्ण
	अगर (cmd_blk->residual)
		scsi_set_resid(scmd, cmd_blk->residual);
	अगर (status == MYRS_STATUS_DEVICE_NON_RESPONSIVE ||
	    status == MYRS_STATUS_DEVICE_NON_RESPONSIVE2)
		scmd->result = (DID_BAD_TARGET << 16);
	अन्यथा
		scmd->result = (DID_OK << 16) | status;
	scmd->scsi_करोne(scmd);
पूर्ण

अटल व्योम myrs_handle_cmdblk(काष्ठा myrs_hba *cs, काष्ठा myrs_cmdblk *cmd_blk)
अणु
	अगर (!cmd_blk)
		वापस;

	अगर (cmd_blk->complete) अणु
		complete(cmd_blk->complete);
		cmd_blk->complete = शून्य;
	पूर्ण
पूर्ण

अटल व्योम myrs_monitor(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा myrs_hba *cs = container_of(work, काष्ठा myrs_hba,
					   monitor_work.work);
	काष्ठा Scsi_Host *shost = cs->host;
	काष्ठा myrs_ctlr_info *info = cs->ctlr_info;
	अचिन्हित पूर्णांक epoch = cs->fwstat_buf->epoch;
	अचिन्हित दीर्घ पूर्णांकerval = MYRS_PRIMARY_MONITOR_INTERVAL;
	अचिन्हित अक्षर status;

	dev_dbg(&shost->shost_gendev, "monitor tick\n");

	status = myrs_get_fwstatus(cs);

	अगर (cs->needs_update) अणु
		cs->needs_update = false;
		mutex_lock(&cs->cinfo_mutex);
		status = myrs_get_ctlr_info(cs);
		mutex_unlock(&cs->cinfo_mutex);
	पूर्ण
	अगर (cs->fwstat_buf->next_evseq - cs->next_evseq > 0) अणु
		status = myrs_get_event(cs, cs->next_evseq,
					cs->event_buf);
		अगर (status == MYRS_STATUS_SUCCESS) अणु
			myrs_log_event(cs, cs->event_buf);
			cs->next_evseq++;
			पूर्णांकerval = 1;
		पूर्ण
	पूर्ण

	अगर (समय_after(jअगरfies, cs->secondary_monitor_समय
		       + MYRS_SECONDARY_MONITOR_INTERVAL))
		cs->secondary_monitor_समय = jअगरfies;

	अगर (info->bg_init_active +
	    info->ldev_init_active +
	    info->pdev_init_active +
	    info->cc_active +
	    info->rbld_active +
	    info->exp_active != 0) अणु
		काष्ठा scsi_device *sdev;

		shost_क्रम_each_device(sdev, shost) अणु
			काष्ठा myrs_ldev_info *ldev_info;
			पूर्णांक ldev_num;

			अगर (sdev->channel < info->physchan_present)
				जारी;
			ldev_info = sdev->hostdata;
			अगर (!ldev_info)
				जारी;
			ldev_num = ldev_info->ldev_num;
			myrs_get_ldev_info(cs, ldev_num, ldev_info);
		पूर्ण
		cs->needs_update = true;
	पूर्ण
	अगर (epoch == cs->epoch &&
	    cs->fwstat_buf->next_evseq == cs->next_evseq &&
	    (cs->needs_update == false ||
	     समय_beक्रमe(jअगरfies, cs->primary_monitor_समय
			 + MYRS_PRIMARY_MONITOR_INTERVAL))) अणु
		पूर्णांकerval = MYRS_SECONDARY_MONITOR_INTERVAL;
	पूर्ण

	अगर (पूर्णांकerval > 1)
		cs->primary_monitor_समय = jअगरfies;
	queue_delayed_work(cs->work_q, &cs->monitor_work, पूर्णांकerval);
पूर्ण

अटल bool myrs_create_mempools(काष्ठा pci_dev *pdev, काष्ठा myrs_hba *cs)
अणु
	काष्ठा Scsi_Host *shost = cs->host;
	माप_प्रकार elem_size, elem_align;

	elem_align = माप(काष्ठा myrs_sge);
	elem_size = shost->sg_tablesize * elem_align;
	cs->sg_pool = dma_pool_create("myrs_sg", &pdev->dev,
				      elem_size, elem_align, 0);
	अगर (cs->sg_pool == शून्य) अणु
		shost_prपूर्णांकk(KERN_ERR, shost,
			     "Failed to allocate SG pool\n");
		वापस false;
	पूर्ण

	cs->sense_pool = dma_pool_create("myrs_sense", &pdev->dev,
					 MYRS_SENSE_SIZE, माप(पूर्णांक), 0);
	अगर (cs->sense_pool == शून्य) अणु
		dma_pool_destroy(cs->sg_pool);
		cs->sg_pool = शून्य;
		shost_prपूर्णांकk(KERN_ERR, shost,
			     "Failed to allocate sense data pool\n");
		वापस false;
	पूर्ण

	cs->dcdb_pool = dma_pool_create("myrs_dcdb", &pdev->dev,
					MYRS_DCDB_SIZE,
					माप(अचिन्हित अक्षर), 0);
	अगर (!cs->dcdb_pool) अणु
		dma_pool_destroy(cs->sg_pool);
		cs->sg_pool = शून्य;
		dma_pool_destroy(cs->sense_pool);
		cs->sense_pool = शून्य;
		shost_prपूर्णांकk(KERN_ERR, shost,
			     "Failed to allocate DCDB pool\n");
		वापस false;
	पूर्ण

	snम_लिखो(cs->work_q_name, माप(cs->work_q_name),
		 "myrs_wq_%d", shost->host_no);
	cs->work_q = create_singlethपढ़ो_workqueue(cs->work_q_name);
	अगर (!cs->work_q) अणु
		dma_pool_destroy(cs->dcdb_pool);
		cs->dcdb_pool = शून्य;
		dma_pool_destroy(cs->sg_pool);
		cs->sg_pool = शून्य;
		dma_pool_destroy(cs->sense_pool);
		cs->sense_pool = शून्य;
		shost_prपूर्णांकk(KERN_ERR, shost,
			     "Failed to create workqueue\n");
		वापस false;
	पूर्ण

	/* Initialize the Monitoring Timer. */
	INIT_DELAYED_WORK(&cs->monitor_work, myrs_monitor);
	queue_delayed_work(cs->work_q, &cs->monitor_work, 1);

	वापस true;
पूर्ण

अटल व्योम myrs_destroy_mempools(काष्ठा myrs_hba *cs)
अणु
	cancel_delayed_work_sync(&cs->monitor_work);
	destroy_workqueue(cs->work_q);

	dma_pool_destroy(cs->sg_pool);
	dma_pool_destroy(cs->dcdb_pool);
	dma_pool_destroy(cs->sense_pool);
पूर्ण

अटल व्योम myrs_unmap(काष्ठा myrs_hba *cs)
अणु
	kमुक्त(cs->event_buf);
	kमुक्त(cs->ctlr_info);
	अगर (cs->fwstat_buf) अणु
		dma_मुक्त_coherent(&cs->pdev->dev, माप(काष्ठा myrs_fwstat),
				  cs->fwstat_buf, cs->fwstat_addr);
		cs->fwstat_buf = शून्य;
	पूर्ण
	अगर (cs->first_stat_mbox) अणु
		dma_मुक्त_coherent(&cs->pdev->dev, cs->stat_mbox_size,
				  cs->first_stat_mbox, cs->stat_mbox_addr);
		cs->first_stat_mbox = शून्य;
	पूर्ण
	अगर (cs->first_cmd_mbox) अणु
		dma_मुक्त_coherent(&cs->pdev->dev, cs->cmd_mbox_size,
				  cs->first_cmd_mbox, cs->cmd_mbox_addr);
		cs->first_cmd_mbox = शून्य;
	पूर्ण
पूर्ण

अटल व्योम myrs_cleanup(काष्ठा myrs_hba *cs)
अणु
	काष्ठा pci_dev *pdev = cs->pdev;

	/* Free the memory mailbox, status, and related काष्ठाures */
	myrs_unmap(cs);

	अगर (cs->mmio_base) अणु
		cs->disable_पूर्णांकr(cs);
		iounmap(cs->mmio_base);
		cs->mmio_base = शून्य;
	पूर्ण
	अगर (cs->irq)
		मुक्त_irq(cs->irq, cs);
	अगर (cs->io_addr)
		release_region(cs->io_addr, 0x80);
	pci_set_drvdata(pdev, शून्य);
	pci_disable_device(pdev);
	scsi_host_put(cs->host);
पूर्ण

अटल काष्ठा myrs_hba *myrs_detect(काष्ठा pci_dev *pdev,
		स्थिर काष्ठा pci_device_id *entry)
अणु
	काष्ठा myrs_privdata *privdata =
		(काष्ठा myrs_privdata *)entry->driver_data;
	irq_handler_t irq_handler = privdata->irq_handler;
	अचिन्हित पूर्णांक mmio_size = privdata->mmio_size;
	काष्ठा myrs_hba *cs = शून्य;

	cs = myrs_alloc_host(pdev, entry);
	अगर (!cs) अणु
		dev_err(&pdev->dev, "Unable to allocate Controller\n");
		वापस शून्य;
	पूर्ण
	cs->pdev = pdev;

	अगर (pci_enable_device(pdev))
		जाओ Failure;

	cs->pci_addr = pci_resource_start(pdev, 0);

	pci_set_drvdata(pdev, cs);
	spin_lock_init(&cs->queue_lock);
	/* Map the Controller Register Winकरोw. */
	अगर (mmio_size < PAGE_SIZE)
		mmio_size = PAGE_SIZE;
	cs->mmio_base = ioremap(cs->pci_addr & PAGE_MASK, mmio_size);
	अगर (cs->mmio_base == शून्य) अणु
		dev_err(&pdev->dev,
			"Unable to map Controller Register Window\n");
		जाओ Failure;
	पूर्ण

	cs->io_base = cs->mmio_base + (cs->pci_addr & ~PAGE_MASK);
	अगर (privdata->hw_init(pdev, cs, cs->io_base))
		जाओ Failure;

	/* Acquire shared access to the IRQ Channel. */
	अगर (request_irq(pdev->irq, irq_handler, IRQF_SHARED, "myrs", cs) < 0) अणु
		dev_err(&pdev->dev,
			"Unable to acquire IRQ Channel %d\n", pdev->irq);
		जाओ Failure;
	पूर्ण
	cs->irq = pdev->irq;
	वापस cs;

Failure:
	dev_err(&pdev->dev,
		"Failed to initialize Controller\n");
	myrs_cleanup(cs);
	वापस शून्य;
पूर्ण

/*
 * myrs_err_status reports Controller BIOS Messages passed through
 * the Error Status Register when the driver perक्रमms the BIOS handshaking.
 * It वापसs true क्रम fatal errors and false otherwise.
 */

अटल bool myrs_err_status(काष्ठा myrs_hba *cs, अचिन्हित अक्षर status,
		अचिन्हित अक्षर parm0, अचिन्हित अक्षर parm1)
अणु
	काष्ठा pci_dev *pdev = cs->pdev;

	चयन (status) अणु
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
			status);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/*
 * Hardware-specअगरic functions
 */

/*
 * DAC960 GEM Series Controllers.
 */

अटल अंतरभूत व्योम DAC960_GEM_hw_mbox_new_cmd(व्योम __iomem *base)
अणु
	__le32 val = cpu_to_le32(DAC960_GEM_IDB_HWMBOX_NEW_CMD << 24);

	ग_लिखोl(val, base + DAC960_GEM_IDB_READ_OFFSET);
पूर्ण

अटल अंतरभूत व्योम DAC960_GEM_ack_hw_mbox_status(व्योम __iomem *base)
अणु
	__le32 val = cpu_to_le32(DAC960_GEM_IDB_HWMBOX_ACK_STS << 24);

	ग_लिखोl(val, base + DAC960_GEM_IDB_CLEAR_OFFSET);
पूर्ण

अटल अंतरभूत व्योम DAC960_GEM_reset_ctrl(व्योम __iomem *base)
अणु
	__le32 val = cpu_to_le32(DAC960_GEM_IDB_CTRL_RESET << 24);

	ग_लिखोl(val, base + DAC960_GEM_IDB_READ_OFFSET);
पूर्ण

अटल अंतरभूत व्योम DAC960_GEM_mem_mbox_new_cmd(व्योम __iomem *base)
अणु
	__le32 val = cpu_to_le32(DAC960_GEM_IDB_HWMBOX_NEW_CMD << 24);

	ग_लिखोl(val, base + DAC960_GEM_IDB_READ_OFFSET);
पूर्ण

अटल अंतरभूत bool DAC960_GEM_hw_mbox_is_full(व्योम __iomem *base)
अणु
	__le32 val;

	val = पढ़ोl(base + DAC960_GEM_IDB_READ_OFFSET);
	वापस (le32_to_cpu(val) >> 24) & DAC960_GEM_IDB_HWMBOX_FULL;
पूर्ण

अटल अंतरभूत bool DAC960_GEM_init_in_progress(व्योम __iomem *base)
अणु
	__le32 val;

	val = पढ़ोl(base + DAC960_GEM_IDB_READ_OFFSET);
	वापस (le32_to_cpu(val) >> 24) & DAC960_GEM_IDB_INIT_IN_PROGRESS;
पूर्ण

अटल अंतरभूत व्योम DAC960_GEM_ack_hw_mbox_पूर्णांकr(व्योम __iomem *base)
अणु
	__le32 val = cpu_to_le32(DAC960_GEM_ODB_HWMBOX_ACK_IRQ << 24);

	ग_लिखोl(val, base + DAC960_GEM_ODB_CLEAR_OFFSET);
पूर्ण

अटल अंतरभूत व्योम DAC960_GEM_ack_पूर्णांकr(व्योम __iomem *base)
अणु
	__le32 val = cpu_to_le32((DAC960_GEM_ODB_HWMBOX_ACK_IRQ |
				  DAC960_GEM_ODB_MMBOX_ACK_IRQ) << 24);

	ग_लिखोl(val, base + DAC960_GEM_ODB_CLEAR_OFFSET);
पूर्ण

अटल अंतरभूत bool DAC960_GEM_hw_mbox_status_available(व्योम __iomem *base)
अणु
	__le32 val;

	val = पढ़ोl(base + DAC960_GEM_ODB_READ_OFFSET);
	वापस (le32_to_cpu(val) >> 24) & DAC960_GEM_ODB_HWMBOX_STS_AVAIL;
पूर्ण

अटल अंतरभूत व्योम DAC960_GEM_enable_पूर्णांकr(व्योम __iomem *base)
अणु
	__le32 val = cpu_to_le32((DAC960_GEM_IRQMASK_HWMBOX_IRQ |
				  DAC960_GEM_IRQMASK_MMBOX_IRQ) << 24);
	ग_लिखोl(val, base + DAC960_GEM_IRQMASK_CLEAR_OFFSET);
पूर्ण

अटल अंतरभूत व्योम DAC960_GEM_disable_पूर्णांकr(व्योम __iomem *base)
अणु
	__le32 val = 0;

	ग_लिखोl(val, base + DAC960_GEM_IRQMASK_READ_OFFSET);
पूर्ण

अटल अंतरभूत व्योम DAC960_GEM_ग_लिखो_cmd_mbox(जोड़ myrs_cmd_mbox *mem_mbox,
		जोड़ myrs_cmd_mbox *mbox)
अणु
	स_नकल(&mem_mbox->words[1], &mbox->words[1],
	       माप(जोड़ myrs_cmd_mbox) - माप(अचिन्हित पूर्णांक));
	/* Barrier to aव्योम reordering */
	wmb();
	mem_mbox->words[0] = mbox->words[0];
	/* Barrier to क्रमce PCI access */
	mb();
पूर्ण

अटल अंतरभूत व्योम DAC960_GEM_ग_लिखो_hw_mbox(व्योम __iomem *base,
		dma_addr_t cmd_mbox_addr)
अणु
	dma_addr_ग_लिखोql(cmd_mbox_addr, base + DAC960_GEM_CMDMBX_OFFSET);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर DAC960_GEM_पढ़ो_cmd_status(व्योम __iomem *base)
अणु
	वापस पढ़ोw(base + DAC960_GEM_CMDSTS_OFFSET + 2);
पूर्ण

अटल अंतरभूत bool
DAC960_GEM_पढ़ो_error_status(व्योम __iomem *base, अचिन्हित अक्षर *error,
		अचिन्हित अक्षर *param0, अचिन्हित अक्षर *param1)
अणु
	__le32 val;

	val = पढ़ोl(base + DAC960_GEM_ERRSTS_READ_OFFSET);
	अगर (!((le32_to_cpu(val) >> 24) & DAC960_GEM_ERRSTS_PENDING))
		वापस false;
	*error = val & ~(DAC960_GEM_ERRSTS_PENDING << 24);
	*param0 = पढ़ोb(base + DAC960_GEM_CMDMBX_OFFSET + 0);
	*param1 = पढ़ोb(base + DAC960_GEM_CMDMBX_OFFSET + 1);
	ग_लिखोl(0x03000000, base + DAC960_GEM_ERRSTS_CLEAR_OFFSET);
	वापस true;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर
DAC960_GEM_mbox_init(व्योम __iomem *base, dma_addr_t mbox_addr)
अणु
	अचिन्हित अक्षर status;

	जबतक (DAC960_GEM_hw_mbox_is_full(base))
		udelay(1);
	DAC960_GEM_ग_लिखो_hw_mbox(base, mbox_addr);
	DAC960_GEM_hw_mbox_new_cmd(base);
	जबतक (!DAC960_GEM_hw_mbox_status_available(base))
		udelay(1);
	status = DAC960_GEM_पढ़ो_cmd_status(base);
	DAC960_GEM_ack_hw_mbox_पूर्णांकr(base);
	DAC960_GEM_ack_hw_mbox_status(base);

	वापस status;
पूर्ण

अटल पूर्णांक DAC960_GEM_hw_init(काष्ठा pci_dev *pdev,
		काष्ठा myrs_hba *cs, व्योम __iomem *base)
अणु
	पूर्णांक समयout = 0;
	अचिन्हित अक्षर status, parm0, parm1;

	DAC960_GEM_disable_पूर्णांकr(base);
	DAC960_GEM_ack_hw_mbox_status(base);
	udelay(1000);
	जबतक (DAC960_GEM_init_in_progress(base) &&
	       समयout < MYRS_MAILBOX_TIMEOUT) अणु
		अगर (DAC960_GEM_पढ़ो_error_status(base, &status,
						 &parm0, &parm1) &&
		    myrs_err_status(cs, status, parm0, parm1))
			वापस -EIO;
		udelay(10);
		समयout++;
	पूर्ण
	अगर (समयout == MYRS_MAILBOX_TIMEOUT) अणु
		dev_err(&pdev->dev,
			"Timeout waiting for Controller Initialisation\n");
		वापस -ETIMEDOUT;
	पूर्ण
	अगर (!myrs_enable_mmio_mbox(cs, DAC960_GEM_mbox_init)) अणु
		dev_err(&pdev->dev,
			"Unable to Enable Memory Mailbox Interface\n");
		DAC960_GEM_reset_ctrl(base);
		वापस -EAGAIN;
	पूर्ण
	DAC960_GEM_enable_पूर्णांकr(base);
	cs->ग_लिखो_cmd_mbox = DAC960_GEM_ग_लिखो_cmd_mbox;
	cs->get_cmd_mbox = DAC960_GEM_mem_mbox_new_cmd;
	cs->disable_पूर्णांकr = DAC960_GEM_disable_पूर्णांकr;
	cs->reset = DAC960_GEM_reset_ctrl;
	वापस 0;
पूर्ण

अटल irqवापस_t DAC960_GEM_पूर्णांकr_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा myrs_hba *cs = arg;
	व्योम __iomem *base = cs->io_base;
	काष्ठा myrs_stat_mbox *next_stat_mbox;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cs->queue_lock, flags);
	DAC960_GEM_ack_पूर्णांकr(base);
	next_stat_mbox = cs->next_stat_mbox;
	जबतक (next_stat_mbox->id > 0) अणु
		अचिन्हित लघु id = next_stat_mbox->id;
		काष्ठा scsi_cmnd *scmd = शून्य;
		काष्ठा myrs_cmdblk *cmd_blk = शून्य;

		अगर (id == MYRS_DCMD_TAG)
			cmd_blk = &cs->dcmd_blk;
		अन्यथा अगर (id == MYRS_MCMD_TAG)
			cmd_blk = &cs->mcmd_blk;
		अन्यथा अणु
			scmd = scsi_host_find_tag(cs->host, id - 3);
			अगर (scmd)
				cmd_blk = scsi_cmd_priv(scmd);
		पूर्ण
		अगर (cmd_blk) अणु
			cmd_blk->status = next_stat_mbox->status;
			cmd_blk->sense_len = next_stat_mbox->sense_len;
			cmd_blk->residual = next_stat_mbox->residual;
		पूर्ण अन्यथा
			dev_err(&cs->pdev->dev,
				"Unhandled command completion %d\n", id);

		स_रखो(next_stat_mbox, 0, माप(काष्ठा myrs_stat_mbox));
		अगर (++next_stat_mbox > cs->last_stat_mbox)
			next_stat_mbox = cs->first_stat_mbox;

		अगर (cmd_blk) अणु
			अगर (id < 3)
				myrs_handle_cmdblk(cs, cmd_blk);
			अन्यथा
				myrs_handle_scsi(cs, cmd_blk, scmd);
		पूर्ण
	पूर्ण
	cs->next_stat_mbox = next_stat_mbox;
	spin_unlock_irqrestore(&cs->queue_lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा myrs_privdata DAC960_GEM_privdata = अणु
	.hw_init =		DAC960_GEM_hw_init,
	.irq_handler =		DAC960_GEM_पूर्णांकr_handler,
	.mmio_size =		DAC960_GEM_mmio_size,
पूर्ण;

/*
 * DAC960 BA Series Controllers.
 */

अटल अंतरभूत व्योम DAC960_BA_hw_mbox_new_cmd(व्योम __iomem *base)
अणु
	ग_लिखोb(DAC960_BA_IDB_HWMBOX_NEW_CMD, base + DAC960_BA_IDB_OFFSET);
पूर्ण

अटल अंतरभूत व्योम DAC960_BA_ack_hw_mbox_status(व्योम __iomem *base)
अणु
	ग_लिखोb(DAC960_BA_IDB_HWMBOX_ACK_STS, base + DAC960_BA_IDB_OFFSET);
पूर्ण

अटल अंतरभूत व्योम DAC960_BA_reset_ctrl(व्योम __iomem *base)
अणु
	ग_लिखोb(DAC960_BA_IDB_CTRL_RESET, base + DAC960_BA_IDB_OFFSET);
पूर्ण

अटल अंतरभूत व्योम DAC960_BA_mem_mbox_new_cmd(व्योम __iomem *base)
अणु
	ग_लिखोb(DAC960_BA_IDB_MMBOX_NEW_CMD, base + DAC960_BA_IDB_OFFSET);
पूर्ण

अटल अंतरभूत bool DAC960_BA_hw_mbox_is_full(व्योम __iomem *base)
अणु
	u8 val;

	val = पढ़ोb(base + DAC960_BA_IDB_OFFSET);
	वापस !(val & DAC960_BA_IDB_HWMBOX_EMPTY);
पूर्ण

अटल अंतरभूत bool DAC960_BA_init_in_progress(व्योम __iomem *base)
अणु
	u8 val;

	val = पढ़ोb(base + DAC960_BA_IDB_OFFSET);
	वापस !(val & DAC960_BA_IDB_INIT_DONE);
पूर्ण

अटल अंतरभूत व्योम DAC960_BA_ack_hw_mbox_पूर्णांकr(व्योम __iomem *base)
अणु
	ग_लिखोb(DAC960_BA_ODB_HWMBOX_ACK_IRQ, base + DAC960_BA_ODB_OFFSET);
पूर्ण

अटल अंतरभूत व्योम DAC960_BA_ack_पूर्णांकr(व्योम __iomem *base)
अणु
	ग_लिखोb(DAC960_BA_ODB_HWMBOX_ACK_IRQ | DAC960_BA_ODB_MMBOX_ACK_IRQ,
	       base + DAC960_BA_ODB_OFFSET);
पूर्ण

अटल अंतरभूत bool DAC960_BA_hw_mbox_status_available(व्योम __iomem *base)
अणु
	u8 val;

	val = पढ़ोb(base + DAC960_BA_ODB_OFFSET);
	वापस val & DAC960_BA_ODB_HWMBOX_STS_AVAIL;
पूर्ण

अटल अंतरभूत व्योम DAC960_BA_enable_पूर्णांकr(व्योम __iomem *base)
अणु
	ग_लिखोb(~DAC960_BA_IRQMASK_DISABLE_IRQ, base + DAC960_BA_IRQMASK_OFFSET);
पूर्ण

अटल अंतरभूत व्योम DAC960_BA_disable_पूर्णांकr(व्योम __iomem *base)
अणु
	ग_लिखोb(0xFF, base + DAC960_BA_IRQMASK_OFFSET);
पूर्ण

अटल अंतरभूत व्योम DAC960_BA_ग_लिखो_cmd_mbox(जोड़ myrs_cmd_mbox *mem_mbox,
		जोड़ myrs_cmd_mbox *mbox)
अणु
	स_नकल(&mem_mbox->words[1], &mbox->words[1],
	       माप(जोड़ myrs_cmd_mbox) - माप(अचिन्हित पूर्णांक));
	/* Barrier to aव्योम reordering */
	wmb();
	mem_mbox->words[0] = mbox->words[0];
	/* Barrier to क्रमce PCI access */
	mb();
पूर्ण


अटल अंतरभूत व्योम DAC960_BA_ग_लिखो_hw_mbox(व्योम __iomem *base,
		dma_addr_t cmd_mbox_addr)
अणु
	dma_addr_ग_लिखोql(cmd_mbox_addr, base + DAC960_BA_CMDMBX_OFFSET);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर DAC960_BA_पढ़ो_cmd_status(व्योम __iomem *base)
अणु
	वापस पढ़ोw(base + DAC960_BA_CMDSTS_OFFSET + 2);
पूर्ण

अटल अंतरभूत bool
DAC960_BA_पढ़ो_error_status(व्योम __iomem *base, अचिन्हित अक्षर *error,
		अचिन्हित अक्षर *param0, अचिन्हित अक्षर *param1)
अणु
	u8 val;

	val = पढ़ोb(base + DAC960_BA_ERRSTS_OFFSET);
	अगर (!(val & DAC960_BA_ERRSTS_PENDING))
		वापस false;
	val &= ~DAC960_BA_ERRSTS_PENDING;
	*error = val;
	*param0 = पढ़ोb(base + DAC960_BA_CMDMBX_OFFSET + 0);
	*param1 = पढ़ोb(base + DAC960_BA_CMDMBX_OFFSET + 1);
	ग_लिखोb(0xFF, base + DAC960_BA_ERRSTS_OFFSET);
	वापस true;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर
DAC960_BA_mbox_init(व्योम __iomem *base, dma_addr_t mbox_addr)
अणु
	अचिन्हित अक्षर status;

	जबतक (DAC960_BA_hw_mbox_is_full(base))
		udelay(1);
	DAC960_BA_ग_लिखो_hw_mbox(base, mbox_addr);
	DAC960_BA_hw_mbox_new_cmd(base);
	जबतक (!DAC960_BA_hw_mbox_status_available(base))
		udelay(1);
	status = DAC960_BA_पढ़ो_cmd_status(base);
	DAC960_BA_ack_hw_mbox_पूर्णांकr(base);
	DAC960_BA_ack_hw_mbox_status(base);

	वापस status;
पूर्ण

अटल पूर्णांक DAC960_BA_hw_init(काष्ठा pci_dev *pdev,
		काष्ठा myrs_hba *cs, व्योम __iomem *base)
अणु
	पूर्णांक समयout = 0;
	अचिन्हित अक्षर status, parm0, parm1;

	DAC960_BA_disable_पूर्णांकr(base);
	DAC960_BA_ack_hw_mbox_status(base);
	udelay(1000);
	जबतक (DAC960_BA_init_in_progress(base) &&
	       समयout < MYRS_MAILBOX_TIMEOUT) अणु
		अगर (DAC960_BA_पढ़ो_error_status(base, &status,
					      &parm0, &parm1) &&
		    myrs_err_status(cs, status, parm0, parm1))
			वापस -EIO;
		udelay(10);
		समयout++;
	पूर्ण
	अगर (समयout == MYRS_MAILBOX_TIMEOUT) अणु
		dev_err(&pdev->dev,
			"Timeout waiting for Controller Initialisation\n");
		वापस -ETIMEDOUT;
	पूर्ण
	अगर (!myrs_enable_mmio_mbox(cs, DAC960_BA_mbox_init)) अणु
		dev_err(&pdev->dev,
			"Unable to Enable Memory Mailbox Interface\n");
		DAC960_BA_reset_ctrl(base);
		वापस -EAGAIN;
	पूर्ण
	DAC960_BA_enable_पूर्णांकr(base);
	cs->ग_लिखो_cmd_mbox = DAC960_BA_ग_लिखो_cmd_mbox;
	cs->get_cmd_mbox = DAC960_BA_mem_mbox_new_cmd;
	cs->disable_पूर्णांकr = DAC960_BA_disable_पूर्णांकr;
	cs->reset = DAC960_BA_reset_ctrl;
	वापस 0;
पूर्ण

अटल irqवापस_t DAC960_BA_पूर्णांकr_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा myrs_hba *cs = arg;
	व्योम __iomem *base = cs->io_base;
	काष्ठा myrs_stat_mbox *next_stat_mbox;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cs->queue_lock, flags);
	DAC960_BA_ack_पूर्णांकr(base);
	next_stat_mbox = cs->next_stat_mbox;
	जबतक (next_stat_mbox->id > 0) अणु
		अचिन्हित लघु id = next_stat_mbox->id;
		काष्ठा scsi_cmnd *scmd = शून्य;
		काष्ठा myrs_cmdblk *cmd_blk = शून्य;

		अगर (id == MYRS_DCMD_TAG)
			cmd_blk = &cs->dcmd_blk;
		अन्यथा अगर (id == MYRS_MCMD_TAG)
			cmd_blk = &cs->mcmd_blk;
		अन्यथा अणु
			scmd = scsi_host_find_tag(cs->host, id - 3);
			अगर (scmd)
				cmd_blk = scsi_cmd_priv(scmd);
		पूर्ण
		अगर (cmd_blk) अणु
			cmd_blk->status = next_stat_mbox->status;
			cmd_blk->sense_len = next_stat_mbox->sense_len;
			cmd_blk->residual = next_stat_mbox->residual;
		पूर्ण अन्यथा
			dev_err(&cs->pdev->dev,
				"Unhandled command completion %d\n", id);

		स_रखो(next_stat_mbox, 0, माप(काष्ठा myrs_stat_mbox));
		अगर (++next_stat_mbox > cs->last_stat_mbox)
			next_stat_mbox = cs->first_stat_mbox;

		अगर (cmd_blk) अणु
			अगर (id < 3)
				myrs_handle_cmdblk(cs, cmd_blk);
			अन्यथा
				myrs_handle_scsi(cs, cmd_blk, scmd);
		पूर्ण
	पूर्ण
	cs->next_stat_mbox = next_stat_mbox;
	spin_unlock_irqrestore(&cs->queue_lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा myrs_privdata DAC960_BA_privdata = अणु
	.hw_init =		DAC960_BA_hw_init,
	.irq_handler =		DAC960_BA_पूर्णांकr_handler,
	.mmio_size =		DAC960_BA_mmio_size,
पूर्ण;

/*
 * DAC960 LP Series Controllers.
 */

अटल अंतरभूत व्योम DAC960_LP_hw_mbox_new_cmd(व्योम __iomem *base)
अणु
	ग_लिखोb(DAC960_LP_IDB_HWMBOX_NEW_CMD, base + DAC960_LP_IDB_OFFSET);
पूर्ण

अटल अंतरभूत व्योम DAC960_LP_ack_hw_mbox_status(व्योम __iomem *base)
अणु
	ग_लिखोb(DAC960_LP_IDB_HWMBOX_ACK_STS, base + DAC960_LP_IDB_OFFSET);
पूर्ण

अटल अंतरभूत व्योम DAC960_LP_reset_ctrl(व्योम __iomem *base)
अणु
	ग_लिखोb(DAC960_LP_IDB_CTRL_RESET, base + DAC960_LP_IDB_OFFSET);
पूर्ण

अटल अंतरभूत व्योम DAC960_LP_mem_mbox_new_cmd(व्योम __iomem *base)
अणु
	ग_लिखोb(DAC960_LP_IDB_MMBOX_NEW_CMD, base + DAC960_LP_IDB_OFFSET);
पूर्ण

अटल अंतरभूत bool DAC960_LP_hw_mbox_is_full(व्योम __iomem *base)
अणु
	u8 val;

	val = पढ़ोb(base + DAC960_LP_IDB_OFFSET);
	वापस val & DAC960_LP_IDB_HWMBOX_FULL;
पूर्ण

अटल अंतरभूत bool DAC960_LP_init_in_progress(व्योम __iomem *base)
अणु
	u8 val;

	val = पढ़ोb(base + DAC960_LP_IDB_OFFSET);
	वापस val & DAC960_LP_IDB_INIT_IN_PROGRESS;
पूर्ण

अटल अंतरभूत व्योम DAC960_LP_ack_hw_mbox_पूर्णांकr(व्योम __iomem *base)
अणु
	ग_लिखोb(DAC960_LP_ODB_HWMBOX_ACK_IRQ, base + DAC960_LP_ODB_OFFSET);
पूर्ण

अटल अंतरभूत व्योम DAC960_LP_ack_पूर्णांकr(व्योम __iomem *base)
अणु
	ग_लिखोb(DAC960_LP_ODB_HWMBOX_ACK_IRQ | DAC960_LP_ODB_MMBOX_ACK_IRQ,
	       base + DAC960_LP_ODB_OFFSET);
पूर्ण

अटल अंतरभूत bool DAC960_LP_hw_mbox_status_available(व्योम __iomem *base)
अणु
	u8 val;

	val = पढ़ोb(base + DAC960_LP_ODB_OFFSET);
	वापस val & DAC960_LP_ODB_HWMBOX_STS_AVAIL;
पूर्ण

अटल अंतरभूत व्योम DAC960_LP_enable_पूर्णांकr(व्योम __iomem *base)
अणु
	ग_लिखोb(~DAC960_LP_IRQMASK_DISABLE_IRQ, base + DAC960_LP_IRQMASK_OFFSET);
पूर्ण

अटल अंतरभूत व्योम DAC960_LP_disable_पूर्णांकr(व्योम __iomem *base)
अणु
	ग_लिखोb(0xFF, base + DAC960_LP_IRQMASK_OFFSET);
पूर्ण

अटल अंतरभूत व्योम DAC960_LP_ग_लिखो_cmd_mbox(जोड़ myrs_cmd_mbox *mem_mbox,
		जोड़ myrs_cmd_mbox *mbox)
अणु
	स_नकल(&mem_mbox->words[1], &mbox->words[1],
	       माप(जोड़ myrs_cmd_mbox) - माप(अचिन्हित पूर्णांक));
	/* Barrier to aव्योम reordering */
	wmb();
	mem_mbox->words[0] = mbox->words[0];
	/* Barrier to क्रमce PCI access */
	mb();
पूर्ण

अटल अंतरभूत व्योम DAC960_LP_ग_लिखो_hw_mbox(व्योम __iomem *base,
		dma_addr_t cmd_mbox_addr)
अणु
	dma_addr_ग_लिखोql(cmd_mbox_addr, base + DAC960_LP_CMDMBX_OFFSET);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर DAC960_LP_पढ़ो_cmd_status(व्योम __iomem *base)
अणु
	वापस पढ़ोw(base + DAC960_LP_CMDSTS_OFFSET + 2);
पूर्ण

अटल अंतरभूत bool
DAC960_LP_पढ़ो_error_status(व्योम __iomem *base, अचिन्हित अक्षर *error,
		अचिन्हित अक्षर *param0, अचिन्हित अक्षर *param1)
अणु
	u8 val;

	val = पढ़ोb(base + DAC960_LP_ERRSTS_OFFSET);
	अगर (!(val & DAC960_LP_ERRSTS_PENDING))
		वापस false;
	val &= ~DAC960_LP_ERRSTS_PENDING;
	*error = val;
	*param0 = पढ़ोb(base + DAC960_LP_CMDMBX_OFFSET + 0);
	*param1 = पढ़ोb(base + DAC960_LP_CMDMBX_OFFSET + 1);
	ग_लिखोb(0xFF, base + DAC960_LP_ERRSTS_OFFSET);
	वापस true;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर
DAC960_LP_mbox_init(व्योम __iomem *base, dma_addr_t mbox_addr)
अणु
	अचिन्हित अक्षर status;

	जबतक (DAC960_LP_hw_mbox_is_full(base))
		udelay(1);
	DAC960_LP_ग_लिखो_hw_mbox(base, mbox_addr);
	DAC960_LP_hw_mbox_new_cmd(base);
	जबतक (!DAC960_LP_hw_mbox_status_available(base))
		udelay(1);
	status = DAC960_LP_पढ़ो_cmd_status(base);
	DAC960_LP_ack_hw_mbox_पूर्णांकr(base);
	DAC960_LP_ack_hw_mbox_status(base);

	वापस status;
पूर्ण

अटल पूर्णांक DAC960_LP_hw_init(काष्ठा pci_dev *pdev,
		काष्ठा myrs_hba *cs, व्योम __iomem *base)
अणु
	पूर्णांक समयout = 0;
	अचिन्हित अक्षर status, parm0, parm1;

	DAC960_LP_disable_पूर्णांकr(base);
	DAC960_LP_ack_hw_mbox_status(base);
	udelay(1000);
	जबतक (DAC960_LP_init_in_progress(base) &&
	       समयout < MYRS_MAILBOX_TIMEOUT) अणु
		अगर (DAC960_LP_पढ़ो_error_status(base, &status,
					      &parm0, &parm1) &&
		    myrs_err_status(cs, status, parm0, parm1))
			वापस -EIO;
		udelay(10);
		समयout++;
	पूर्ण
	अगर (समयout == MYRS_MAILBOX_TIMEOUT) अणु
		dev_err(&pdev->dev,
			"Timeout waiting for Controller Initialisation\n");
		वापस -ETIMEDOUT;
	पूर्ण
	अगर (!myrs_enable_mmio_mbox(cs, DAC960_LP_mbox_init)) अणु
		dev_err(&pdev->dev,
			"Unable to Enable Memory Mailbox Interface\n");
		DAC960_LP_reset_ctrl(base);
		वापस -ENODEV;
	पूर्ण
	DAC960_LP_enable_पूर्णांकr(base);
	cs->ग_लिखो_cmd_mbox = DAC960_LP_ग_लिखो_cmd_mbox;
	cs->get_cmd_mbox = DAC960_LP_mem_mbox_new_cmd;
	cs->disable_पूर्णांकr = DAC960_LP_disable_पूर्णांकr;
	cs->reset = DAC960_LP_reset_ctrl;

	वापस 0;
पूर्ण

अटल irqवापस_t DAC960_LP_पूर्णांकr_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा myrs_hba *cs = arg;
	व्योम __iomem *base = cs->io_base;
	काष्ठा myrs_stat_mbox *next_stat_mbox;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cs->queue_lock, flags);
	DAC960_LP_ack_पूर्णांकr(base);
	next_stat_mbox = cs->next_stat_mbox;
	जबतक (next_stat_mbox->id > 0) अणु
		अचिन्हित लघु id = next_stat_mbox->id;
		काष्ठा scsi_cmnd *scmd = शून्य;
		काष्ठा myrs_cmdblk *cmd_blk = शून्य;

		अगर (id == MYRS_DCMD_TAG)
			cmd_blk = &cs->dcmd_blk;
		अन्यथा अगर (id == MYRS_MCMD_TAG)
			cmd_blk = &cs->mcmd_blk;
		अन्यथा अणु
			scmd = scsi_host_find_tag(cs->host, id - 3);
			अगर (scmd)
				cmd_blk = scsi_cmd_priv(scmd);
		पूर्ण
		अगर (cmd_blk) अणु
			cmd_blk->status = next_stat_mbox->status;
			cmd_blk->sense_len = next_stat_mbox->sense_len;
			cmd_blk->residual = next_stat_mbox->residual;
		पूर्ण अन्यथा
			dev_err(&cs->pdev->dev,
				"Unhandled command completion %d\n", id);

		स_रखो(next_stat_mbox, 0, माप(काष्ठा myrs_stat_mbox));
		अगर (++next_stat_mbox > cs->last_stat_mbox)
			next_stat_mbox = cs->first_stat_mbox;

		अगर (cmd_blk) अणु
			अगर (id < 3)
				myrs_handle_cmdblk(cs, cmd_blk);
			अन्यथा
				myrs_handle_scsi(cs, cmd_blk, scmd);
		पूर्ण
	पूर्ण
	cs->next_stat_mbox = next_stat_mbox;
	spin_unlock_irqrestore(&cs->queue_lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा myrs_privdata DAC960_LP_privdata = अणु
	.hw_init =		DAC960_LP_hw_init,
	.irq_handler =		DAC960_LP_पूर्णांकr_handler,
	.mmio_size =		DAC960_LP_mmio_size,
पूर्ण;

/*
 * Module functions
 */
अटल पूर्णांक
myrs_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *entry)
अणु
	काष्ठा myrs_hba *cs;
	पूर्णांक ret;

	cs = myrs_detect(dev, entry);
	अगर (!cs)
		वापस -ENODEV;

	ret = myrs_get_config(cs);
	अगर (ret < 0) अणु
		myrs_cleanup(cs);
		वापस ret;
	पूर्ण

	अगर (!myrs_create_mempools(dev, cs)) अणु
		ret = -ENOMEM;
		जाओ failed;
	पूर्ण

	ret = scsi_add_host(cs->host, &dev->dev);
	अगर (ret) अणु
		dev_err(&dev->dev, "scsi_add_host failed with %d\n", ret);
		myrs_destroy_mempools(cs);
		जाओ failed;
	पूर्ण
	scsi_scan_host(cs->host);
	वापस 0;
failed:
	myrs_cleanup(cs);
	वापस ret;
पूर्ण


अटल व्योम myrs_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा myrs_hba *cs = pci_get_drvdata(pdev);

	अगर (cs == शून्य)
		वापस;

	shost_prपूर्णांकk(KERN_NOTICE, cs->host, "Flushing Cache...");
	myrs_flush_cache(cs);
	myrs_destroy_mempools(cs);
	myrs_cleanup(cs);
पूर्ण


अटल स्थिर काष्ठा pci_device_id myrs_id_table[] = अणु
	अणु
		PCI_DEVICE_SUB(PCI_VENDOR_ID_MYLEX,
			       PCI_DEVICE_ID_MYLEX_DAC960_GEM,
			       PCI_VENDOR_ID_MYLEX, PCI_ANY_ID),
		.driver_data	= (अचिन्हित दीर्घ) &DAC960_GEM_privdata,
	पूर्ण,
	अणु
		PCI_DEVICE_DATA(MYLEX, DAC960_BA, &DAC960_BA_privdata),
	पूर्ण,
	अणु
		PCI_DEVICE_DATA(MYLEX, DAC960_LP, &DAC960_LP_privdata),
	पूर्ण,
	अणु0, पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, myrs_id_table);

अटल काष्ठा pci_driver myrs_pci_driver = अणु
	.name		= "myrs",
	.id_table	= myrs_id_table,
	.probe		= myrs_probe,
	.हटाओ		= myrs_हटाओ,
पूर्ण;

अटल पूर्णांक __init myrs_init_module(व्योम)
अणु
	पूर्णांक ret;

	myrs_raid_ढाँचा = raid_class_attach(&myrs_raid_functions);
	अगर (!myrs_raid_ढाँचा)
		वापस -ENODEV;

	ret = pci_रेजिस्टर_driver(&myrs_pci_driver);
	अगर (ret)
		raid_class_release(myrs_raid_ढाँचा);

	वापस ret;
पूर्ण

अटल व्योम __निकास myrs_cleanup_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&myrs_pci_driver);
	raid_class_release(myrs_raid_ढाँचा);
पूर्ण

module_init(myrs_init_module);
module_निकास(myrs_cleanup_module);

MODULE_DESCRIPTION("Mylex DAC960/AcceleRAID/eXtremeRAID driver (SCSI Interface)");
MODULE_AUTHOR("Hannes Reinecke <hare@suse.com>");
MODULE_LICENSE("GPL");
