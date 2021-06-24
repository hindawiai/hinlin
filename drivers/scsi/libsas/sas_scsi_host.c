<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Serial Attached SCSI (SAS) class SCSI Host glue.
 *
 * Copyright (C) 2005 Adaptec, Inc.  All rights reserved.
 * Copyright (C) 2005 Luben Tuikov <luben_tuikov@adaptec.com>
 */

#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/firmware.h>
#समावेश <linux/export.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/kernel.h>

#समावेश "sas_internal.h"

#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_transport_sas.h>
#समावेश <scsi/sas_ata.h>
#समावेश "../scsi_sas_internal.h"
#समावेश "../scsi_transport_api.h"
#समावेश "../scsi_priv.h"

#समावेश <linux/err.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/gfp.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/libata.h>

/* record final status and मुक्त the task */
अटल व्योम sas_end_task(काष्ठा scsi_cmnd *sc, काष्ठा sas_task *task)
अणु
	काष्ठा task_status_काष्ठा *ts = &task->task_status;
	पूर्णांक hs = 0, stat = 0;

	अगर (ts->resp == SAS_TASK_UNDELIVERED) अणु
		/* transport error */
		hs = DID_NO_CONNECT;
	पूर्ण अन्यथा अणु /* ts->resp == SAS_TASK_COMPLETE */
		/* task delivered, what happened afterwards? */
		चयन (ts->stat) अणु
		हाल SAS_DEV_NO_RESPONSE:
		हाल SAS_INTERRUPTED:
		हाल SAS_PHY_DOWN:
		हाल SAS_NAK_R_ERR:
		हाल SAS_OPEN_TO:
			hs = DID_NO_CONNECT;
			अवरोध;
		हाल SAS_DATA_UNDERRUN:
			scsi_set_resid(sc, ts->residual);
			अगर (scsi_bufflen(sc) - scsi_get_resid(sc) < sc->underflow)
				hs = DID_ERROR;
			अवरोध;
		हाल SAS_DATA_OVERRUN:
			hs = DID_ERROR;
			अवरोध;
		हाल SAS_QUEUE_FULL:
			hs = DID_SOFT_ERROR; /* retry */
			अवरोध;
		हाल SAS_DEVICE_UNKNOWN:
			hs = DID_BAD_TARGET;
			अवरोध;
		हाल SAS_SG_ERR:
			hs = DID_PARITY;
			अवरोध;
		हाल SAS_OPEN_REJECT:
			अगर (ts->खोलो_rej_reason == SAS_OREJ_RSVD_RETRY)
				hs = DID_SOFT_ERROR; /* retry */
			अन्यथा
				hs = DID_ERROR;
			अवरोध;
		हाल SAS_PROTO_RESPONSE:
			pr_notice("LLDD:%s sent SAS_PROTO_RESP for an SSP task; please report this\n",
				  task->dev->port->ha->sas_ha_name);
			अवरोध;
		हाल SAS_ABORTED_TASK:
			hs = DID_ABORT;
			अवरोध;
		हाल SAM_STAT_CHECK_CONDITION:
			स_नकल(sc->sense_buffer, ts->buf,
			       min(SCSI_SENSE_BUFFERSIZE, ts->buf_valid_size));
			stat = SAM_STAT_CHECK_CONDITION;
			अवरोध;
		शेष:
			stat = ts->stat;
			अवरोध;
		पूर्ण
	पूर्ण

	sc->result = (hs << 16) | stat;
	ASSIGN_SAS_TASK(sc, शून्य);
	sas_मुक्त_task(task);
पूर्ण

अटल व्योम sas_scsi_task_करोne(काष्ठा sas_task *task)
अणु
	काष्ठा scsi_cmnd *sc = task->uldd_task;
	काष्ठा करोमुख्य_device *dev = task->dev;
	काष्ठा sas_ha_काष्ठा *ha = dev->port->ha;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->करोne_lock, flags);
	अगर (test_bit(SAS_HA_FROZEN, &ha->state))
		task = शून्य;
	अन्यथा
		ASSIGN_SAS_TASK(sc, शून्य);
	spin_unlock_irqrestore(&dev->करोne_lock, flags);

	अगर (unlikely(!task)) अणु
		/* task will be completed by the error handler */
		pr_debug("task done but aborted\n");
		वापस;
	पूर्ण

	अगर (unlikely(!sc)) अणु
		pr_debug("task_done called with non existing SCSI cmnd!\n");
		sas_मुक्त_task(task);
		वापस;
	पूर्ण

	sas_end_task(sc, task);
	sc->scsi_करोne(sc);
पूर्ण

अटल काष्ठा sas_task *sas_create_task(काष्ठा scsi_cmnd *cmd,
					       काष्ठा करोमुख्य_device *dev,
					       gfp_t gfp_flags)
अणु
	काष्ठा sas_task *task = sas_alloc_task(gfp_flags);
	काष्ठा scsi_lun lun;

	अगर (!task)
		वापस शून्य;

	task->uldd_task = cmd;
	ASSIGN_SAS_TASK(cmd, task);

	task->dev = dev;
	task->task_proto = task->dev->tproto; /* BUG_ON(!SSP) */

	task->ssp_task.retry_count = 1;
	पूर्णांक_to_scsilun(cmd->device->lun, &lun);
	स_नकल(task->ssp_task.LUN, &lun.scsi_lun, 8);
	task->ssp_task.task_attr = TASK_ATTR_SIMPLE;
	task->ssp_task.cmd = cmd;

	task->scatter = scsi_sglist(cmd);
	task->num_scatter = scsi_sg_count(cmd);
	task->total_xfer_len = scsi_bufflen(cmd);
	task->data_dir = cmd->sc_data_direction;

	task->task_करोne = sas_scsi_task_करोne;

	वापस task;
पूर्ण

पूर्णांक sas_queuecommand(काष्ठा Scsi_Host *host, काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा sas_पूर्णांकernal *i = to_sas_पूर्णांकernal(host->transportt);
	काष्ठा करोमुख्य_device *dev = cmd_to_करोमुख्य_dev(cmd);
	काष्ठा sas_task *task;
	पूर्णांक res = 0;

	/* If the device fell off, no sense in issuing commands */
	अगर (test_bit(SAS_DEV_GONE, &dev->state)) अणु
		cmd->result = DID_BAD_TARGET << 16;
		जाओ out_करोne;
	पूर्ण

	अगर (dev_is_sata(dev)) अणु
		spin_lock_irq(dev->sata_dev.ap->lock);
		res = ata_sas_queuecmd(cmd, dev->sata_dev.ap);
		spin_unlock_irq(dev->sata_dev.ap->lock);
		वापस res;
	पूर्ण

	task = sas_create_task(cmd, dev, GFP_ATOMIC);
	अगर (!task)
		वापस SCSI_MLQUEUE_HOST_BUSY;

	res = i->dft->lldd_execute_task(task, GFP_ATOMIC);
	अगर (res)
		जाओ out_मुक्त_task;
	वापस 0;

out_मुक्त_task:
	pr_debug("lldd_execute_task returned: %d\n", res);
	ASSIGN_SAS_TASK(cmd, शून्य);
	sas_मुक्त_task(task);
	अगर (res == -SAS_QUEUE_FULL)
		cmd->result = DID_SOFT_ERROR << 16; /* retry */
	अन्यथा
		cmd->result = DID_ERROR << 16;
out_करोne:
	cmd->scsi_करोne(cmd);
	वापस 0;
पूर्ण

अटल व्योम sas_eh_finish_cmd(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा sas_ha_काष्ठा *sas_ha = SHOST_TO_SAS_HA(cmd->device->host);
	काष्ठा करोमुख्य_device *dev = cmd_to_करोमुख्य_dev(cmd);
	काष्ठा sas_task *task = TO_SAS_TASK(cmd);

	/* At this poपूर्णांक, we only get called following an actual पात
	 * of the task, so we should be guaranteed not to be racing with
	 * any completions from the LLD.  Task is मुक्तd after this.
	 */
	sas_end_task(cmd, task);

	अगर (dev_is_sata(dev)) अणु
		/* defer commands to libata so that libata EH can
		 * handle ata qcs correctly
		 */
		list_move_tail(&cmd->eh_entry, &sas_ha->eh_ata_q);
		वापस;
	पूर्ण

	/* now finish the command and move it on to the error
	 * handler करोne list, this also takes it off the
	 * error handler pending list.
	 */
	scsi_eh_finish_cmd(cmd, &sas_ha->eh_करोne_q);
पूर्ण

अटल व्योम sas_scsi_clear_queue_lu(काष्ठा list_head *error_q, काष्ठा scsi_cmnd *my_cmd)
अणु
	काष्ठा scsi_cmnd *cmd, *n;

	list_क्रम_each_entry_safe(cmd, n, error_q, eh_entry) अणु
		अगर (cmd->device->sdev_target == my_cmd->device->sdev_target &&
		    cmd->device->lun == my_cmd->device->lun)
			sas_eh_finish_cmd(cmd);
	पूर्ण
पूर्ण

अटल व्योम sas_scsi_clear_queue_I_T(काष्ठा list_head *error_q,
				     काष्ठा करोमुख्य_device *dev)
अणु
	काष्ठा scsi_cmnd *cmd, *n;

	list_क्रम_each_entry_safe(cmd, n, error_q, eh_entry) अणु
		काष्ठा करोमुख्य_device *x = cmd_to_करोमुख्य_dev(cmd);

		अगर (x == dev)
			sas_eh_finish_cmd(cmd);
	पूर्ण
पूर्ण

अटल व्योम sas_scsi_clear_queue_port(काष्ठा list_head *error_q,
				      काष्ठा asd_sas_port *port)
अणु
	काष्ठा scsi_cmnd *cmd, *n;

	list_क्रम_each_entry_safe(cmd, n, error_q, eh_entry) अणु
		काष्ठा करोमुख्य_device *dev = cmd_to_करोमुख्य_dev(cmd);
		काष्ठा asd_sas_port *x = dev->port;

		अगर (x == port)
			sas_eh_finish_cmd(cmd);
	पूर्ण
पूर्ण

क्रमागत task_disposition अणु
	TASK_IS_DONE,
	TASK_IS_ABORTED,
	TASK_IS_AT_LU,
	TASK_IS_NOT_AT_LU,
	TASK_ABORT_FAILED,
पूर्ण;

अटल क्रमागत task_disposition sas_scsi_find_task(काष्ठा sas_task *task)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i, res;
	काष्ठा sas_पूर्णांकernal *si =
		to_sas_पूर्णांकernal(task->dev->port->ha->core.shost->transportt);

	क्रम (i = 0; i < 5; i++) अणु
		pr_notice("%s: aborting task 0x%p\n", __func__, task);
		res = si->dft->lldd_पात_task(task);

		spin_lock_irqsave(&task->task_state_lock, flags);
		अगर (task->task_state_flags & SAS_TASK_STATE_DONE) अणु
			spin_unlock_irqrestore(&task->task_state_lock, flags);
			pr_debug("%s: task 0x%p is done\n", __func__, task);
			वापस TASK_IS_DONE;
		पूर्ण
		spin_unlock_irqrestore(&task->task_state_lock, flags);

		अगर (res == TMF_RESP_FUNC_COMPLETE) अणु
			pr_notice("%s: task 0x%p is aborted\n",
				  __func__, task);
			वापस TASK_IS_ABORTED;
		पूर्ण अन्यथा अगर (si->dft->lldd_query_task) अणु
			pr_notice("%s: querying task 0x%p\n", __func__, task);
			res = si->dft->lldd_query_task(task);
			चयन (res) अणु
			हाल TMF_RESP_FUNC_SUCC:
				pr_notice("%s: task 0x%p at LU\n", __func__,
					  task);
				वापस TASK_IS_AT_LU;
			हाल TMF_RESP_FUNC_COMPLETE:
				pr_notice("%s: task 0x%p not at LU\n",
					  __func__, task);
				वापस TASK_IS_NOT_AT_LU;
			हाल TMF_RESP_FUNC_FAILED:
				pr_notice("%s: task 0x%p failed to abort\n",
					  __func__, task);
				वापस TASK_ABORT_FAILED;
			पूर्ण

		पूर्ण
	पूर्ण
	वापस res;
पूर्ण

अटल पूर्णांक sas_recover_lu(काष्ठा करोमुख्य_device *dev, काष्ठा scsi_cmnd *cmd)
अणु
	पूर्णांक res = TMF_RESP_FUNC_FAILED;
	काष्ठा scsi_lun lun;
	काष्ठा sas_पूर्णांकernal *i =
		to_sas_पूर्णांकernal(dev->port->ha->core.shost->transportt);

	पूर्णांक_to_scsilun(cmd->device->lun, &lun);

	pr_notice("eh: device %016llx LUN 0x%llx has the task\n",
		  SAS_ADDR(dev->sas_addr),
		  cmd->device->lun);

	अगर (i->dft->lldd_पात_task_set)
		res = i->dft->lldd_पात_task_set(dev, lun.scsi_lun);

	अगर (res == TMF_RESP_FUNC_FAILED) अणु
		अगर (i->dft->lldd_clear_task_set)
			res = i->dft->lldd_clear_task_set(dev, lun.scsi_lun);
	पूर्ण

	अगर (res == TMF_RESP_FUNC_FAILED) अणु
		अगर (i->dft->lldd_lu_reset)
			res = i->dft->lldd_lu_reset(dev, lun.scsi_lun);
	पूर्ण

	वापस res;
पूर्ण

अटल पूर्णांक sas_recover_I_T(काष्ठा करोमुख्य_device *dev)
अणु
	पूर्णांक res = TMF_RESP_FUNC_FAILED;
	काष्ठा sas_पूर्णांकernal *i =
		to_sas_पूर्णांकernal(dev->port->ha->core.shost->transportt);

	pr_notice("I_T nexus reset for dev %016llx\n",
		  SAS_ADDR(dev->sas_addr));

	अगर (i->dft->lldd_I_T_nexus_reset)
		res = i->dft->lldd_I_T_nexus_reset(dev);

	वापस res;
पूर्ण

/* take a reference on the last known good phy क्रम this device */
काष्ठा sas_phy *sas_get_local_phy(काष्ठा करोमुख्य_device *dev)
अणु
	काष्ठा sas_ha_काष्ठा *ha = dev->port->ha;
	काष्ठा sas_phy *phy;
	अचिन्हित दीर्घ flags;

	/* a published करोमुख्य device always has a valid phy, it may be
	 * stale, but it is never शून्य
	 */
	BUG_ON(!dev->phy);

	spin_lock_irqsave(&ha->phy_port_lock, flags);
	phy = dev->phy;
	get_device(&phy->dev);
	spin_unlock_irqrestore(&ha->phy_port_lock, flags);

	वापस phy;
पूर्ण
EXPORT_SYMBOL_GPL(sas_get_local_phy);

अटल व्योम sas_रुको_eh(काष्ठा करोमुख्य_device *dev)
अणु
	काष्ठा sas_ha_काष्ठा *ha = dev->port->ha;
	DEFINE_WAIT(रुको);

	अगर (dev_is_sata(dev)) अणु
		ata_port_रुको_eh(dev->sata_dev.ap);
		वापस;
	पूर्ण
 retry:
	spin_lock_irq(&ha->lock);

	जबतक (test_bit(SAS_DEV_EH_PENDING, &dev->state)) अणु
		prepare_to_रुको(&ha->eh_रुको_q, &रुको, TASK_UNINTERRUPTIBLE);
		spin_unlock_irq(&ha->lock);
		schedule();
		spin_lock_irq(&ha->lock);
	पूर्ण
	finish_रुको(&ha->eh_रुको_q, &रुको);

	spin_unlock_irq(&ha->lock);

	/* make sure SCSI EH is complete */
	अगर (scsi_host_in_recovery(ha->core.shost)) अणु
		msleep(10);
		जाओ retry;
	पूर्ण
पूर्ण

अटल पूर्णांक sas_queue_reset(काष्ठा करोमुख्य_device *dev, पूर्णांक reset_type,
			   u64 lun, पूर्णांक रुको)
अणु
	काष्ठा sas_ha_काष्ठा *ha = dev->port->ha;
	पूर्णांक scheduled = 0, tries = 100;

	/* ata: promote lun reset to bus reset */
	अगर (dev_is_sata(dev)) अणु
		sas_ata_schedule_reset(dev);
		अगर (रुको)
			sas_ata_रुको_eh(dev);
		वापस SUCCESS;
	पूर्ण

	जबतक (!scheduled && tries--) अणु
		spin_lock_irq(&ha->lock);
		अगर (!test_bit(SAS_DEV_EH_PENDING, &dev->state) &&
		    !test_bit(reset_type, &dev->state)) अणु
			scheduled = 1;
			ha->eh_active++;
			list_add_tail(&dev->ssp_dev.eh_list_node, &ha->eh_dev_q);
			set_bit(SAS_DEV_EH_PENDING, &dev->state);
			set_bit(reset_type, &dev->state);
			पूर्णांक_to_scsilun(lun, &dev->ssp_dev.reset_lun);
			scsi_schedule_eh(ha->core.shost);
		पूर्ण
		spin_unlock_irq(&ha->lock);

		अगर (रुको)
			sas_रुको_eh(dev);

		अगर (scheduled)
			वापस SUCCESS;
	पूर्ण

	pr_warn("%s reset of %s failed\n",
		reset_type == SAS_DEV_LU_RESET ? "LUN" : "Bus",
		dev_name(&dev->rphy->dev));

	वापस FAILED;
पूर्ण

पूर्णांक sas_eh_पात_handler(काष्ठा scsi_cmnd *cmd)
अणु
	पूर्णांक res = TMF_RESP_FUNC_FAILED;
	काष्ठा sas_task *task = TO_SAS_TASK(cmd);
	काष्ठा Scsi_Host *host = cmd->device->host;
	काष्ठा करोमुख्य_device *dev = cmd_to_करोमुख्य_dev(cmd);
	काष्ठा sas_पूर्णांकernal *i = to_sas_पूर्णांकernal(host->transportt);
	अचिन्हित दीर्घ flags;

	अगर (!i->dft->lldd_पात_task)
		वापस FAILED;

	spin_lock_irqsave(host->host_lock, flags);
	/* We cannot करो async पातs क्रम SATA devices */
	अगर (dev_is_sata(dev) && !host->host_eh_scheduled) अणु
		spin_unlock_irqrestore(host->host_lock, flags);
		वापस FAILED;
	पूर्ण
	spin_unlock_irqrestore(host->host_lock, flags);

	अगर (task)
		res = i->dft->lldd_पात_task(task);
	अन्यथा
		pr_notice("no task to abort\n");
	अगर (res == TMF_RESP_FUNC_SUCC || res == TMF_RESP_FUNC_COMPLETE)
		वापस SUCCESS;

	वापस FAILED;
पूर्ण
EXPORT_SYMBOL_GPL(sas_eh_पात_handler);

/* Attempt to send a LUN reset message to a device */
पूर्णांक sas_eh_device_reset_handler(काष्ठा scsi_cmnd *cmd)
अणु
	पूर्णांक res;
	काष्ठा scsi_lun lun;
	काष्ठा Scsi_Host *host = cmd->device->host;
	काष्ठा करोमुख्य_device *dev = cmd_to_करोमुख्य_dev(cmd);
	काष्ठा sas_पूर्णांकernal *i = to_sas_पूर्णांकernal(host->transportt);

	अगर (current != host->ehandler)
		वापस sas_queue_reset(dev, SAS_DEV_LU_RESET, cmd->device->lun, 0);

	पूर्णांक_to_scsilun(cmd->device->lun, &lun);

	अगर (!i->dft->lldd_lu_reset)
		वापस FAILED;

	res = i->dft->lldd_lu_reset(dev, lun.scsi_lun);
	अगर (res == TMF_RESP_FUNC_SUCC || res == TMF_RESP_FUNC_COMPLETE)
		वापस SUCCESS;

	वापस FAILED;
पूर्ण

पूर्णांक sas_eh_target_reset_handler(काष्ठा scsi_cmnd *cmd)
अणु
	पूर्णांक res;
	काष्ठा Scsi_Host *host = cmd->device->host;
	काष्ठा करोमुख्य_device *dev = cmd_to_करोमुख्य_dev(cmd);
	काष्ठा sas_पूर्णांकernal *i = to_sas_पूर्णांकernal(host->transportt);

	अगर (current != host->ehandler)
		वापस sas_queue_reset(dev, SAS_DEV_RESET, 0, 0);

	अगर (!i->dft->lldd_I_T_nexus_reset)
		वापस FAILED;

	res = i->dft->lldd_I_T_nexus_reset(dev);
	अगर (res == TMF_RESP_FUNC_SUCC || res == TMF_RESP_FUNC_COMPLETE ||
	    res == -ENODEV)
		वापस SUCCESS;

	वापस FAILED;
पूर्ण

/* Try to reset a device */
अटल पूर्णांक try_to_reset_cmd_device(काष्ठा scsi_cmnd *cmd)
अणु
	पूर्णांक res;
	काष्ठा Scsi_Host *shost = cmd->device->host;

	अगर (!shost->hostt->eh_device_reset_handler)
		जाओ try_target_reset;

	res = shost->hostt->eh_device_reset_handler(cmd);
	अगर (res == SUCCESS)
		वापस res;

try_target_reset:
	अगर (shost->hostt->eh_target_reset_handler)
		वापस shost->hostt->eh_target_reset_handler(cmd);

	वापस FAILED;
पूर्ण

अटल व्योम sas_eh_handle_sas_errors(काष्ठा Scsi_Host *shost, काष्ठा list_head *work_q)
अणु
	काष्ठा scsi_cmnd *cmd, *n;
	क्रमागत task_disposition res = TASK_IS_DONE;
	पूर्णांक पंचांगf_resp, need_reset;
	काष्ठा sas_पूर्णांकernal *i = to_sas_पूर्णांकernal(shost->transportt);
	अचिन्हित दीर्घ flags;
	काष्ठा sas_ha_काष्ठा *ha = SHOST_TO_SAS_HA(shost);
	LIST_HEAD(करोne);

	/* clean out any commands that won the completion vs eh race */
	list_क्रम_each_entry_safe(cmd, n, work_q, eh_entry) अणु
		काष्ठा करोमुख्य_device *dev = cmd_to_करोमुख्य_dev(cmd);
		काष्ठा sas_task *task;

		spin_lock_irqsave(&dev->करोne_lock, flags);
		/* by this poपूर्णांक the lldd has either observed
		 * SAS_HA_FROZEN and is leaving the task alone, or has
		 * won the race with eh and decided to complete it
		 */
		task = TO_SAS_TASK(cmd);
		spin_unlock_irqrestore(&dev->करोne_lock, flags);

		अगर (!task)
			list_move_tail(&cmd->eh_entry, &करोne);
	पूर्ण

 Again:
	list_क्रम_each_entry_safe(cmd, n, work_q, eh_entry) अणु
		काष्ठा sas_task *task = TO_SAS_TASK(cmd);

		list_del_init(&cmd->eh_entry);

		spin_lock_irqsave(&task->task_state_lock, flags);
		need_reset = task->task_state_flags & SAS_TASK_NEED_DEV_RESET;
		spin_unlock_irqrestore(&task->task_state_lock, flags);

		अगर (need_reset) अणु
			pr_notice("%s: task 0x%p requests reset\n",
				  __func__, task);
			जाओ reset;
		पूर्ण

		pr_debug("trying to find task 0x%p\n", task);
		res = sas_scsi_find_task(task);

		चयन (res) अणु
		हाल TASK_IS_DONE:
			pr_notice("%s: task 0x%p is done\n", __func__,
				    task);
			sas_eh_finish_cmd(cmd);
			जारी;
		हाल TASK_IS_ABORTED:
			pr_notice("%s: task 0x%p is aborted\n",
				  __func__, task);
			sas_eh_finish_cmd(cmd);
			जारी;
		हाल TASK_IS_AT_LU:
			pr_info("task 0x%p is at LU: lu recover\n", task);
 reset:
			पंचांगf_resp = sas_recover_lu(task->dev, cmd);
			अगर (पंचांगf_resp == TMF_RESP_FUNC_COMPLETE) अणु
				pr_notice("dev %016llx LU 0x%llx is recovered\n",
					  SAS_ADDR(task->dev),
					  cmd->device->lun);
				sas_eh_finish_cmd(cmd);
				sas_scsi_clear_queue_lu(work_q, cmd);
				जाओ Again;
			पूर्ण
			fallthrough;
		हाल TASK_IS_NOT_AT_LU:
		हाल TASK_ABORT_FAILED:
			pr_notice("task 0x%p is not at LU: I_T recover\n",
				  task);
			पंचांगf_resp = sas_recover_I_T(task->dev);
			अगर (पंचांगf_resp == TMF_RESP_FUNC_COMPLETE ||
			    पंचांगf_resp == -ENODEV) अणु
				काष्ठा करोमुख्य_device *dev = task->dev;
				pr_notice("I_T %016llx recovered\n",
					  SAS_ADDR(task->dev->sas_addr));
				sas_eh_finish_cmd(cmd);
				sas_scsi_clear_queue_I_T(work_q, dev);
				जाओ Again;
			पूर्ण
			/* Hammer समय :-) */
			try_to_reset_cmd_device(cmd);
			अगर (i->dft->lldd_clear_nexus_port) अणु
				काष्ठा asd_sas_port *port = task->dev->port;
				pr_debug("clearing nexus for port:%d\n",
					  port->id);
				res = i->dft->lldd_clear_nexus_port(port);
				अगर (res == TMF_RESP_FUNC_COMPLETE) अणु
					pr_notice("clear nexus port:%d succeeded\n",
						  port->id);
					sas_eh_finish_cmd(cmd);
					sas_scsi_clear_queue_port(work_q,
								  port);
					जाओ Again;
				पूर्ण
			पूर्ण
			अगर (i->dft->lldd_clear_nexus_ha) अणु
				pr_debug("clear nexus ha\n");
				res = i->dft->lldd_clear_nexus_ha(ha);
				अगर (res == TMF_RESP_FUNC_COMPLETE) अणु
					pr_notice("clear nexus ha succeeded\n");
					sas_eh_finish_cmd(cmd);
					जाओ clear_q;
				पूर्ण
			पूर्ण
			/* If we are here -- this means that no amount
			 * of efक्रमt could recover from errors.  Quite
			 * possibly the HA just disappeared.
			 */
			pr_err("error from device %016llx, LUN 0x%llx couldn't be recovered in any way\n",
			       SAS_ADDR(task->dev->sas_addr),
			       cmd->device->lun);

			sas_eh_finish_cmd(cmd);
			जाओ clear_q;
		पूर्ण
	पूर्ण
 out:
	list_splice_tail(&करोne, work_q);
	list_splice_tail_init(&ha->eh_ata_q, work_q);
	वापस;

 clear_q:
	pr_debug("--- Exit %s -- clear_q\n", __func__);
	list_क्रम_each_entry_safe(cmd, n, work_q, eh_entry)
		sas_eh_finish_cmd(cmd);
	जाओ out;
पूर्ण

अटल व्योम sas_eh_handle_resets(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा sas_ha_काष्ठा *ha = SHOST_TO_SAS_HA(shost);
	काष्ठा sas_पूर्णांकernal *i = to_sas_पूर्णांकernal(shost->transportt);

	/* handle directed resets to sas devices */
	spin_lock_irq(&ha->lock);
	जबतक (!list_empty(&ha->eh_dev_q)) अणु
		काष्ठा करोमुख्य_device *dev;
		काष्ठा ssp_device *ssp;

		ssp = list_entry(ha->eh_dev_q.next, typeof(*ssp), eh_list_node);
		list_del_init(&ssp->eh_list_node);
		dev = container_of(ssp, typeof(*dev), ssp_dev);
		kref_get(&dev->kref);
		WARN_ONCE(dev_is_sata(dev), "ssp reset to ata device?\n");

		spin_unlock_irq(&ha->lock);

		अगर (test_and_clear_bit(SAS_DEV_LU_RESET, &dev->state))
			i->dft->lldd_lu_reset(dev, ssp->reset_lun.scsi_lun);

		अगर (test_and_clear_bit(SAS_DEV_RESET, &dev->state))
			i->dft->lldd_I_T_nexus_reset(dev);

		sas_put_device(dev);
		spin_lock_irq(&ha->lock);
		clear_bit(SAS_DEV_EH_PENDING, &dev->state);
		ha->eh_active--;
	पूर्ण
	spin_unlock_irq(&ha->lock);
पूर्ण


व्योम sas_scsi_recover_host(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा sas_ha_काष्ठा *ha = SHOST_TO_SAS_HA(shost);
	LIST_HEAD(eh_work_q);
	पूर्णांक tries = 0;
	bool retry;

retry:
	tries++;
	retry = true;
	spin_lock_irq(shost->host_lock);
	list_splice_init(&shost->eh_cmd_q, &eh_work_q);
	spin_unlock_irq(shost->host_lock);

	pr_notice("Enter %s busy: %d failed: %d\n",
		  __func__, scsi_host_busy(shost), shost->host_failed);
	/*
	 * Deal with commands that still have SAS tasks (i.e. they didn't
	 * complete via the normal sas_task completion mechanism),
	 * SAS_HA_FROZEN gives eh करोminion over all sas_task completion.
	 */
	set_bit(SAS_HA_FROZEN, &ha->state);
	sas_eh_handle_sas_errors(shost, &eh_work_q);
	clear_bit(SAS_HA_FROZEN, &ha->state);
	अगर (list_empty(&eh_work_q))
		जाओ out;

	/*
	 * Now deal with SCSI commands that completed ok but have a an error
	 * code (and hopefully sense data) attached.  This is roughly what
	 * scsi_unjam_host करोes, but we skip scsi_eh_पात_cmds because any
	 * command we see here has no sas_task and is thus unknown to the HA.
	 */
	sas_ata_eh(shost, &eh_work_q, &ha->eh_करोne_q);
	अगर (!scsi_eh_get_sense(&eh_work_q, &ha->eh_करोne_q))
		scsi_eh_पढ़ोy_devs(shost, &eh_work_q, &ha->eh_करोne_q);

out:
	sas_eh_handle_resets(shost);

	/* now link पूर्णांकo libata eh --- अगर we have any ata devices */
	sas_ata_strategy_handler(shost);

	scsi_eh_flush_करोne_q(&ha->eh_करोne_q);

	/* check अगर any new eh work was scheduled during the last run */
	spin_lock_irq(&ha->lock);
	अगर (ha->eh_active == 0) अणु
		shost->host_eh_scheduled = 0;
		retry = false;
	पूर्ण
	spin_unlock_irq(&ha->lock);

	अगर (retry)
		जाओ retry;

	pr_notice("--- Exit %s: busy: %d failed: %d tries: %d\n",
		  __func__, scsi_host_busy(shost),
		  shost->host_failed, tries);
पूर्ण

पूर्णांक sas_ioctl(काष्ठा scsi_device *sdev, अचिन्हित पूर्णांक cmd, व्योम __user *arg)
अणु
	काष्ठा करोमुख्य_device *dev = sdev_to_करोमुख्य_dev(sdev);

	अगर (dev_is_sata(dev))
		वापस ata_sas_scsi_ioctl(dev->sata_dev.ap, sdev, cmd, arg);

	वापस -EINVAL;
पूर्ण

काष्ठा करोमुख्य_device *sas_find_dev_by_rphy(काष्ठा sas_rphy *rphy)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(rphy->dev.parent);
	काष्ठा sas_ha_काष्ठा *ha = SHOST_TO_SAS_HA(shost);
	काष्ठा करोमुख्य_device *found_dev = शून्य;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ha->phy_port_lock, flags);
	क्रम (i = 0; i < ha->num_phys; i++) अणु
		काष्ठा asd_sas_port *port = ha->sas_port[i];
		काष्ठा करोमुख्य_device *dev;

		spin_lock(&port->dev_list_lock);
		list_क्रम_each_entry(dev, &port->dev_list, dev_list_node) अणु
			अगर (rphy == dev->rphy) अणु
				found_dev = dev;
				spin_unlock(&port->dev_list_lock);
				जाओ found;
			पूर्ण
		पूर्ण
		spin_unlock(&port->dev_list_lock);
	पूर्ण
 found:
	spin_unlock_irqrestore(&ha->phy_port_lock, flags);

	वापस found_dev;
पूर्ण

पूर्णांक sas_target_alloc(काष्ठा scsi_target *starget)
अणु
	काष्ठा sas_rphy *rphy = dev_to_rphy(starget->dev.parent);
	काष्ठा करोमुख्य_device *found_dev = sas_find_dev_by_rphy(rphy);

	अगर (!found_dev)
		वापस -ENODEV;

	kref_get(&found_dev->kref);
	starget->hostdata = found_dev;
	वापस 0;
पूर्ण

#घोषणा SAS_DEF_QD 256

पूर्णांक sas_slave_configure(काष्ठा scsi_device *scsi_dev)
अणु
	काष्ठा करोमुख्य_device *dev = sdev_to_करोमुख्य_dev(scsi_dev);

	BUG_ON(dev->rphy->identअगरy.device_type != SAS_END_DEVICE);

	अगर (dev_is_sata(dev)) अणु
		ata_sas_slave_configure(scsi_dev, dev->sata_dev.ap);
		वापस 0;
	पूर्ण

	sas_पढ़ो_port_mode_page(scsi_dev);

	अगर (scsi_dev->tagged_supported) अणु
		scsi_change_queue_depth(scsi_dev, SAS_DEF_QD);
	पूर्ण अन्यथा अणु
		pr_notice("device %016llx, LUN 0x%llx doesn't support TCQ\n",
			  SAS_ADDR(dev->sas_addr), scsi_dev->lun);
		scsi_change_queue_depth(scsi_dev, 1);
	पूर्ण

	scsi_dev->allow_restart = 1;

	वापस 0;
पूर्ण

पूर्णांक sas_change_queue_depth(काष्ठा scsi_device *sdev, पूर्णांक depth)
अणु
	काष्ठा करोमुख्य_device *dev = sdev_to_करोमुख्य_dev(sdev);

	अगर (dev_is_sata(dev))
		वापस __ata_change_queue_depth(dev->sata_dev.ap, sdev, depth);

	अगर (!sdev->tagged_supported)
		depth = 1;
	वापस scsi_change_queue_depth(sdev, depth);
पूर्ण

पूर्णांक sas_bios_param(काष्ठा scsi_device *scsi_dev,
			  काष्ठा block_device *bdev,
			  sector_t capacity, पूर्णांक *hsc)
अणु
	hsc[0] = 255;
	hsc[1] = 63;
	sector_भाग(capacity, 255*63);
	hsc[2] = capacity;

	वापस 0;
पूर्ण

/*
 * Tell an upper layer that it needs to initiate an पात क्रम a given task.
 * This should only ever be called by an LLDD.
 */
व्योम sas_task_पात(काष्ठा sas_task *task)
अणु
	काष्ठा scsi_cmnd *sc = task->uldd_task;

	/* Escape क्रम libsas पूर्णांकernal commands */
	अगर (!sc) अणु
		काष्ठा sas_task_slow *slow = task->slow_task;

		अगर (!slow)
			वापस;
		अगर (!del_समयr(&slow->समयr))
			वापस;
		slow->समयr.function(&slow->समयr);
		वापस;
	पूर्ण

	अगर (dev_is_sata(task->dev))
		sas_ata_task_पात(task);
	अन्यथा
		blk_पात_request(sc->request);
पूर्ण

व्योम sas_target_destroy(काष्ठा scsi_target *starget)
अणु
	काष्ठा करोमुख्य_device *found_dev = starget->hostdata;

	अगर (!found_dev)
		वापस;

	starget->hostdata = शून्य;
	sas_put_device(found_dev);
पूर्ण

#घोषणा SAS_STRING_ADDR_SIZE	16

पूर्णांक sas_request_addr(काष्ठा Scsi_Host *shost, u8 *addr)
अणु
	पूर्णांक res;
	स्थिर काष्ठा firmware *fw;

	res = request_firmware(&fw, "sas_addr", &shost->shost_gendev);
	अगर (res)
		वापस res;

	अगर (fw->size < SAS_STRING_ADDR_SIZE) अणु
		res = -ENODEV;
		जाओ out;
	पूर्ण

	res = hex2bin(addr, fw->data, strnlen(fw->data, SAS_ADDR_SIZE * 2) / 2);
	अगर (res)
		जाओ out;

out:
	release_firmware(fw);
	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(sas_request_addr);

EXPORT_SYMBOL_GPL(sas_queuecommand);
EXPORT_SYMBOL_GPL(sas_target_alloc);
EXPORT_SYMBOL_GPL(sas_slave_configure);
EXPORT_SYMBOL_GPL(sas_change_queue_depth);
EXPORT_SYMBOL_GPL(sas_bios_param);
EXPORT_SYMBOL_GPL(sas_task_पात);
EXPORT_SYMBOL_GPL(sas_phy_reset);
EXPORT_SYMBOL_GPL(sas_eh_device_reset_handler);
EXPORT_SYMBOL_GPL(sas_eh_target_reset_handler);
EXPORT_SYMBOL_GPL(sas_target_destroy);
EXPORT_SYMBOL_GPL(sas_ioctl);
