<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * CXL Flash Device Driver
 *
 * Written by: Manoj N. Kumar <manoj@linux.vnet.ibm.com>, IBM Corporation
 *             Matthew R. Ochs <mrochs@linux.vnet.ibm.com>, IBM Corporation
 *
 * Copyright (C) 2015 IBM Corporation
 */

#समावेश <linux/delay.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश <यंत्र/unaligned.h>

#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_host.h>
#समावेश <uapi/scsi/cxlflash_ioctl.h>

#समावेश "main.h"
#समावेश "sislite.h"
#समावेश "common.h"

MODULE_DESCRIPTION(CXLFLASH_ADAPTER_NAME);
MODULE_AUTHOR("Manoj N. Kumar <manoj@linux.vnet.ibm.com>");
MODULE_AUTHOR("Matthew R. Ochs <mrochs@linux.vnet.ibm.com>");
MODULE_LICENSE("GPL");

अटल काष्ठा class *cxlflash_class;
अटल u32 cxlflash_major;
अटल DECLARE_BITMAP(cxlflash_minor, CXLFLASH_MAX_ADAPTERS);

/**
 * process_cmd_err() - command error handler
 * @cmd:	AFU command that experienced the error.
 * @scp:	SCSI command associated with the AFU command in error.
 *
 * Translates error bits from AFU command to SCSI command results.
 */
अटल व्योम process_cmd_err(काष्ठा afu_cmd *cmd, काष्ठा scsi_cmnd *scp)
अणु
	काष्ठा afu *afu = cmd->parent;
	काष्ठा cxlflash_cfg *cfg = afu->parent;
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा sisl_ioasa *ioasa;
	u32 resid;

	ioasa = &(cmd->sa);

	अगर (ioasa->rc.flags & SISL_RC_FLAGS_UNDERRUN) अणु
		resid = ioasa->resid;
		scsi_set_resid(scp, resid);
		dev_dbg(dev, "%s: cmd underrun cmd = %p scp = %p, resid = %d\n",
			__func__, cmd, scp, resid);
	पूर्ण

	अगर (ioasa->rc.flags & SISL_RC_FLAGS_OVERRUN) अणु
		dev_dbg(dev, "%s: cmd underrun cmd = %p scp = %p\n",
			__func__, cmd, scp);
		scp->result = (DID_ERROR << 16);
	पूर्ण

	dev_dbg(dev, "%s: cmd failed afu_rc=%02x scsi_rc=%02x fc_rc=%02x "
		"afu_extra=%02x scsi_extra=%02x fc_extra=%02x\n", __func__,
		ioasa->rc.afu_rc, ioasa->rc.scsi_rc, ioasa->rc.fc_rc,
		ioasa->afu_extra, ioasa->scsi_extra, ioasa->fc_extra);

	अगर (ioasa->rc.scsi_rc) अणु
		/* We have a SCSI status */
		अगर (ioasa->rc.flags & SISL_RC_FLAGS_SENSE_VALID) अणु
			स_नकल(scp->sense_buffer, ioasa->sense_data,
			       SISL_SENSE_DATA_LEN);
			scp->result = ioasa->rc.scsi_rc;
		पूर्ण अन्यथा
			scp->result = ioasa->rc.scsi_rc | (DID_ERROR << 16);
	पूर्ण

	/*
	 * We encountered an error. Set scp->result based on nature
	 * of error.
	 */
	अगर (ioasa->rc.fc_rc) अणु
		/* We have an FC status */
		चयन (ioasa->rc.fc_rc) अणु
		हाल SISL_FC_RC_LINKDOWN:
			scp->result = (DID_REQUEUE << 16);
			अवरोध;
		हाल SISL_FC_RC_RESID:
			/* This indicates an FCP resid underrun */
			अगर (!(ioasa->rc.flags & SISL_RC_FLAGS_OVERRUN)) अणु
				/* If the SISL_RC_FLAGS_OVERRUN flag was set,
				 * then we will handle this error अन्यथा where.
				 * If not then we must handle it here.
				 * This is probably an AFU bug.
				 */
				scp->result = (DID_ERROR << 16);
			पूर्ण
			अवरोध;
		हाल SISL_FC_RC_RESIDERR:
			/* Resid mismatch between adapter and device */
		हाल SISL_FC_RC_TGTABORT:
		हाल SISL_FC_RC_ABORTOK:
		हाल SISL_FC_RC_ABORTFAIL:
		हाल SISL_FC_RC_NOLOGI:
		हाल SISL_FC_RC_ABORTPEND:
		हाल SISL_FC_RC_WRABORTPEND:
		हाल SISL_FC_RC_NOEXP:
		हाल SISL_FC_RC_INUSE:
			scp->result = (DID_ERROR << 16);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ioasa->rc.afu_rc) अणु
		/* We have an AFU error */
		चयन (ioasa->rc.afu_rc) अणु
		हाल SISL_AFU_RC_NO_CHANNELS:
			scp->result = (DID_NO_CONNECT << 16);
			अवरोध;
		हाल SISL_AFU_RC_DATA_DMA_ERR:
			चयन (ioasa->afu_extra) अणु
			हाल SISL_AFU_DMA_ERR_PAGE_IN:
				/* Retry */
				scp->result = (DID_IMM_RETRY << 16);
				अवरोध;
			हाल SISL_AFU_DMA_ERR_INVALID_EA:
			शेष:
				scp->result = (DID_ERROR << 16);
			पूर्ण
			अवरोध;
		हाल SISL_AFU_RC_OUT_OF_DATA_BUFS:
			/* Retry */
			scp->result = (DID_ALLOC_FAILURE << 16);
			अवरोध;
		शेष:
			scp->result = (DID_ERROR << 16);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * cmd_complete() - command completion handler
 * @cmd:	AFU command that has completed.
 *
 * For SCSI commands this routine prepares and submits commands that have
 * either completed or समयd out to the SCSI stack. For पूर्णांकernal commands
 * (TMF or AFU), this routine simply notअगरies the originator that the
 * command has completed.
 */
अटल व्योम cmd_complete(काष्ठा afu_cmd *cmd)
अणु
	काष्ठा scsi_cmnd *scp;
	uदीर्घ lock_flags;
	काष्ठा afu *afu = cmd->parent;
	काष्ठा cxlflash_cfg *cfg = afu->parent;
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा hwq *hwq = get_hwq(afu, cmd->hwq_index);

	spin_lock_irqsave(&hwq->hsq_slock, lock_flags);
	list_del(&cmd->list);
	spin_unlock_irqrestore(&hwq->hsq_slock, lock_flags);

	अगर (cmd->scp) अणु
		scp = cmd->scp;
		अगर (unlikely(cmd->sa.ioasc))
			process_cmd_err(cmd, scp);
		अन्यथा
			scp->result = (DID_OK << 16);

		dev_dbg_ratelimited(dev, "%s:scp=%p result=%08x ioasc=%08x\n",
				    __func__, scp, scp->result, cmd->sa.ioasc);
		scp->scsi_करोne(scp);
	पूर्ण अन्यथा अगर (cmd->cmd_पंचांगf) अणु
		spin_lock_irqsave(&cfg->पंचांगf_slock, lock_flags);
		cfg->पंचांगf_active = false;
		wake_up_all_locked(&cfg->पंचांगf_रुकोq);
		spin_unlock_irqrestore(&cfg->पंचांगf_slock, lock_flags);
	पूर्ण अन्यथा
		complete(&cmd->cevent);
पूर्ण

/**
 * flush_pending_cmds() - flush all pending commands on this hardware queue
 * @hwq:	Hardware queue to flush.
 *
 * The hardware send queue lock associated with this hardware queue must be
 * held when calling this routine.
 */
अटल व्योम flush_pending_cmds(काष्ठा hwq *hwq)
अणु
	काष्ठा cxlflash_cfg *cfg = hwq->afu->parent;
	काष्ठा afu_cmd *cmd, *पंचांगp;
	काष्ठा scsi_cmnd *scp;
	uदीर्घ lock_flags;

	list_क्रम_each_entry_safe(cmd, पंचांगp, &hwq->pending_cmds, list) अणु
		/* Bypass command when on a करोneq, cmd_complete() will handle */
		अगर (!list_empty(&cmd->queue))
			जारी;

		list_del(&cmd->list);

		अगर (cmd->scp) अणु
			scp = cmd->scp;
			scp->result = (DID_IMM_RETRY << 16);
			scp->scsi_करोne(scp);
		पूर्ण अन्यथा अणु
			cmd->cmd_पातed = true;

			अगर (cmd->cmd_पंचांगf) अणु
				spin_lock_irqsave(&cfg->पंचांगf_slock, lock_flags);
				cfg->पंचांगf_active = false;
				wake_up_all_locked(&cfg->पंचांगf_रुकोq);
				spin_unlock_irqrestore(&cfg->पंचांगf_slock,
						       lock_flags);
			पूर्ण अन्यथा
				complete(&cmd->cevent);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * context_reset() - reset context via specअगरied रेजिस्टर
 * @hwq:	Hardware queue owning the context to be reset.
 * @reset_reg:	MMIO रेजिस्टर to perक्रमm reset.
 *
 * When the reset is successful, the SISLite specअगरication guarantees that
 * the AFU has पातed all currently pending I/O. Accordingly, these commands
 * must be flushed.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक context_reset(काष्ठा hwq *hwq, __be64 __iomem *reset_reg)
अणु
	काष्ठा cxlflash_cfg *cfg = hwq->afu->parent;
	काष्ठा device *dev = &cfg->dev->dev;
	पूर्णांक rc = -ETIMEDOUT;
	पूर्णांक nretry = 0;
	u64 val = 0x1;
	uदीर्घ lock_flags;

	dev_dbg(dev, "%s: hwq=%p\n", __func__, hwq);

	spin_lock_irqsave(&hwq->hsq_slock, lock_flags);

	ग_लिखोq_be(val, reset_reg);
	करो अणु
		val = पढ़ोq_be(reset_reg);
		अगर ((val & 0x1) == 0x0) अणु
			rc = 0;
			अवरोध;
		पूर्ण

		/* Double delay each समय */
		udelay(1 << nretry);
	पूर्ण जबतक (nretry++ < MC_ROOM_RETRY_CNT);

	अगर (!rc)
		flush_pending_cmds(hwq);

	spin_unlock_irqrestore(&hwq->hsq_slock, lock_flags);

	dev_dbg(dev, "%s: returning rc=%d, val=%016llx nretry=%d\n",
		__func__, rc, val, nretry);
	वापस rc;
पूर्ण

/**
 * context_reset_ioarrin() - reset context via IOARRIN रेजिस्टर
 * @hwq:	Hardware queue owning the context to be reset.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक context_reset_ioarrin(काष्ठा hwq *hwq)
अणु
	वापस context_reset(hwq, &hwq->host_map->ioarrin);
पूर्ण

/**
 * context_reset_sq() - reset context via SQ_CONTEXT_RESET रेजिस्टर
 * @hwq:	Hardware queue owning the context to be reset.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक context_reset_sq(काष्ठा hwq *hwq)
अणु
	वापस context_reset(hwq, &hwq->host_map->sq_ctx_reset);
पूर्ण

/**
 * send_cmd_ioarrin() - sends an AFU command via IOARRIN रेजिस्टर
 * @afu:	AFU associated with the host.
 * @cmd:	AFU command to send.
 *
 * Return:
 *	0 on success, SCSI_MLQUEUE_HOST_BUSY on failure
 */
अटल पूर्णांक send_cmd_ioarrin(काष्ठा afu *afu, काष्ठा afu_cmd *cmd)
अणु
	काष्ठा cxlflash_cfg *cfg = afu->parent;
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा hwq *hwq = get_hwq(afu, cmd->hwq_index);
	पूर्णांक rc = 0;
	s64 room;
	uदीर्घ lock_flags;

	/*
	 * To aव्योम the perक्रमmance penalty of MMIO, spपढ़ो the update of
	 * 'room' over multiple commands.
	 */
	spin_lock_irqsave(&hwq->hsq_slock, lock_flags);
	अगर (--hwq->room < 0) अणु
		room = पढ़ोq_be(&hwq->host_map->cmd_room);
		अगर (room <= 0) अणु
			dev_dbg_ratelimited(dev, "%s: no cmd_room to send "
					    "0x%02X, room=0x%016llX\n",
					    __func__, cmd->rcb.cdb[0], room);
			hwq->room = 0;
			rc = SCSI_MLQUEUE_HOST_BUSY;
			जाओ out;
		पूर्ण
		hwq->room = room - 1;
	पूर्ण

	list_add(&cmd->list, &hwq->pending_cmds);
	ग_लिखोq_be((u64)&cmd->rcb, &hwq->host_map->ioarrin);
out:
	spin_unlock_irqrestore(&hwq->hsq_slock, lock_flags);
	dev_dbg_ratelimited(dev, "%s: cmd=%p len=%u ea=%016llx rc=%d\n",
		__func__, cmd, cmd->rcb.data_len, cmd->rcb.data_ea, rc);
	वापस rc;
पूर्ण

/**
 * send_cmd_sq() - sends an AFU command via SQ ring
 * @afu:	AFU associated with the host.
 * @cmd:	AFU command to send.
 *
 * Return:
 *	0 on success, SCSI_MLQUEUE_HOST_BUSY on failure
 */
अटल पूर्णांक send_cmd_sq(काष्ठा afu *afu, काष्ठा afu_cmd *cmd)
अणु
	काष्ठा cxlflash_cfg *cfg = afu->parent;
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा hwq *hwq = get_hwq(afu, cmd->hwq_index);
	पूर्णांक rc = 0;
	पूर्णांक newval;
	uदीर्घ lock_flags;

	newval = atomic_dec_अगर_positive(&hwq->hsq_credits);
	अगर (newval <= 0) अणु
		rc = SCSI_MLQUEUE_HOST_BUSY;
		जाओ out;
	पूर्ण

	cmd->rcb.ioasa = &cmd->sa;

	spin_lock_irqsave(&hwq->hsq_slock, lock_flags);

	*hwq->hsq_curr = cmd->rcb;
	अगर (hwq->hsq_curr < hwq->hsq_end)
		hwq->hsq_curr++;
	अन्यथा
		hwq->hsq_curr = hwq->hsq_start;

	list_add(&cmd->list, &hwq->pending_cmds);
	ग_लिखोq_be((u64)hwq->hsq_curr, &hwq->host_map->sq_tail);

	spin_unlock_irqrestore(&hwq->hsq_slock, lock_flags);
out:
	dev_dbg(dev, "%s: cmd=%p len=%u ea=%016llx ioasa=%p rc=%d curr=%p "
	       "head=%016llx tail=%016llx\n", __func__, cmd, cmd->rcb.data_len,
	       cmd->rcb.data_ea, cmd->rcb.ioasa, rc, hwq->hsq_curr,
	       पढ़ोq_be(&hwq->host_map->sq_head),
	       पढ़ोq_be(&hwq->host_map->sq_tail));
	वापस rc;
पूर्ण

/**
 * रुको_resp() - polls क्रम a response or समयout to a sent AFU command
 * @afu:	AFU associated with the host.
 * @cmd:	AFU command that was sent.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक रुको_resp(काष्ठा afu *afu, काष्ठा afu_cmd *cmd)
अणु
	काष्ठा cxlflash_cfg *cfg = afu->parent;
	काष्ठा device *dev = &cfg->dev->dev;
	पूर्णांक rc = 0;
	uदीर्घ समयout = msecs_to_jअगरfies(cmd->rcb.समयout * 2 * 1000);

	समयout = रुको_क्रम_completion_समयout(&cmd->cevent, समयout);
	अगर (!समयout)
		rc = -ETIMEDOUT;

	अगर (cmd->cmd_पातed)
		rc = -EAGAIN;

	अगर (unlikely(cmd->sa.ioasc != 0)) अणु
		dev_err(dev, "%s: cmd %02x failed, ioasc=%08x\n",
			__func__, cmd->rcb.cdb[0], cmd->sa.ioasc);
		rc = -EIO;
	पूर्ण

	वापस rc;
पूर्ण

/**
 * cmd_to_target_hwq() - selects a target hardware queue क्रम a SCSI command
 * @host:	SCSI host associated with device.
 * @scp:	SCSI command to send.
 * @afu:	SCSI command to send.
 *
 * Hashes a command based upon the hardware queue mode.
 *
 * Return: Trusted index of target hardware queue
 */
अटल u32 cmd_to_target_hwq(काष्ठा Scsi_Host *host, काष्ठा scsi_cmnd *scp,
			     काष्ठा afu *afu)
अणु
	u32 tag;
	u32 hwq = 0;

	अगर (afu->num_hwqs == 1)
		वापस 0;

	चयन (afu->hwq_mode) अणु
	हाल HWQ_MODE_RR:
		hwq = afu->hwq_rr_count++ % afu->num_hwqs;
		अवरोध;
	हाल HWQ_MODE_TAG:
		tag = blk_mq_unique_tag(scp->request);
		hwq = blk_mq_unique_tag_to_hwq(tag);
		अवरोध;
	हाल HWQ_MODE_CPU:
		hwq = smp_processor_id() % afu->num_hwqs;
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
	पूर्ण

	वापस hwq;
पूर्ण

/**
 * send_पंचांगf() - sends a Task Management Function (TMF)
 * @cfg:	Internal काष्ठाure associated with the host.
 * @sdev:	SCSI device destined क्रम TMF.
 * @पंचांगfcmd:	TMF command to send.
 *
 * Return:
 *	0 on success, SCSI_MLQUEUE_HOST_BUSY or -त्रुटि_सं on failure
 */
अटल पूर्णांक send_पंचांगf(काष्ठा cxlflash_cfg *cfg, काष्ठा scsi_device *sdev,
		    u64 पंचांगfcmd)
अणु
	काष्ठा afu *afu = cfg->afu;
	काष्ठा afu_cmd *cmd = शून्य;
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा hwq *hwq = get_hwq(afu, PRIMARY_HWQ);
	bool needs_deletion = false;
	अक्षर *buf = शून्य;
	uदीर्घ lock_flags;
	पूर्णांक rc = 0;
	uदीर्घ to;

	buf = kzalloc(माप(*cmd) + __alignof__(*cmd) - 1, GFP_KERNEL);
	अगर (unlikely(!buf)) अणु
		dev_err(dev, "%s: no memory for command\n", __func__);
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	cmd = (काष्ठा afu_cmd *)PTR_ALIGN(buf, __alignof__(*cmd));
	INIT_LIST_HEAD(&cmd->queue);

	/* When Task Management Function is active करो not send another */
	spin_lock_irqsave(&cfg->पंचांगf_slock, lock_flags);
	अगर (cfg->पंचांगf_active)
		रुको_event_पूर्णांकerruptible_lock_irq(cfg->पंचांगf_रुकोq,
						  !cfg->पंचांगf_active,
						  cfg->पंचांगf_slock);
	cfg->पंचांगf_active = true;
	spin_unlock_irqrestore(&cfg->पंचांगf_slock, lock_flags);

	cmd->parent = afu;
	cmd->cmd_पंचांगf = true;
	cmd->hwq_index = hwq->index;

	cmd->rcb.ctx_id = hwq->ctx_hndl;
	cmd->rcb.msi = SISL_MSI_RRQ_UPDATED;
	cmd->rcb.port_sel = CHAN2PORTMASK(sdev->channel);
	cmd->rcb.lun_id = lun_to_lunid(sdev->lun);
	cmd->rcb.req_flags = (SISL_REQ_FLAGS_PORT_LUN_ID |
			      SISL_REQ_FLAGS_SUP_UNDERRUN |
			      SISL_REQ_FLAGS_TMF_CMD);
	स_नकल(cmd->rcb.cdb, &पंचांगfcmd, माप(पंचांगfcmd));

	rc = afu->send_cmd(afu, cmd);
	अगर (unlikely(rc)) अणु
		spin_lock_irqsave(&cfg->पंचांगf_slock, lock_flags);
		cfg->पंचांगf_active = false;
		spin_unlock_irqrestore(&cfg->पंचांगf_slock, lock_flags);
		जाओ out;
	पूर्ण

	spin_lock_irqsave(&cfg->पंचांगf_slock, lock_flags);
	to = msecs_to_jअगरfies(5000);
	to = रुको_event_पूर्णांकerruptible_lock_irq_समयout(cfg->पंचांगf_रुकोq,
						       !cfg->पंचांगf_active,
						       cfg->पंचांगf_slock,
						       to);
	अगर (!to) अणु
		dev_err(dev, "%s: TMF timed out\n", __func__);
		rc = -ETIMEDOUT;
		needs_deletion = true;
	पूर्ण अन्यथा अगर (cmd->cmd_पातed) अणु
		dev_err(dev, "%s: TMF aborted\n", __func__);
		rc = -EAGAIN;
	पूर्ण अन्यथा अगर (cmd->sa.ioasc) अणु
		dev_err(dev, "%s: TMF failed ioasc=%08x\n",
			__func__, cmd->sa.ioasc);
		rc = -EIO;
	पूर्ण
	cfg->पंचांगf_active = false;
	spin_unlock_irqrestore(&cfg->पंचांगf_slock, lock_flags);

	अगर (needs_deletion) अणु
		spin_lock_irqsave(&hwq->hsq_slock, lock_flags);
		list_del(&cmd->list);
		spin_unlock_irqrestore(&hwq->hsq_slock, lock_flags);
	पूर्ण
out:
	kमुक्त(buf);
	वापस rc;
पूर्ण

/**
 * cxlflash_driver_info() - inक्रमmation handler क्रम this host driver
 * @host:	SCSI host associated with device.
 *
 * Return: A string describing the device.
 */
अटल स्थिर अक्षर *cxlflash_driver_info(काष्ठा Scsi_Host *host)
अणु
	वापस CXLFLASH_ADAPTER_NAME;
पूर्ण

/**
 * cxlflash_queuecommand() - sends a mid-layer request
 * @host:	SCSI host associated with device.
 * @scp:	SCSI command to send.
 *
 * Return: 0 on success, SCSI_MLQUEUE_HOST_BUSY on failure
 */
अटल पूर्णांक cxlflash_queuecommand(काष्ठा Scsi_Host *host, काष्ठा scsi_cmnd *scp)
अणु
	काष्ठा cxlflash_cfg *cfg = shost_priv(host);
	काष्ठा afu *afu = cfg->afu;
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा afu_cmd *cmd = sc_to_afuci(scp);
	काष्ठा scatterlist *sg = scsi_sglist(scp);
	पूर्णांक hwq_index = cmd_to_target_hwq(host, scp, afu);
	काष्ठा hwq *hwq = get_hwq(afu, hwq_index);
	u16 req_flags = SISL_REQ_FLAGS_SUP_UNDERRUN;
	uदीर्घ lock_flags;
	पूर्णांक rc = 0;

	dev_dbg_ratelimited(dev, "%s: (scp=%p) %d/%d/%d/%llu "
			    "cdb=(%08x-%08x-%08x-%08x)\n",
			    __func__, scp, host->host_no, scp->device->channel,
			    scp->device->id, scp->device->lun,
			    get_unaligned_be32(&((u32 *)scp->cmnd)[0]),
			    get_unaligned_be32(&((u32 *)scp->cmnd)[1]),
			    get_unaligned_be32(&((u32 *)scp->cmnd)[2]),
			    get_unaligned_be32(&((u32 *)scp->cmnd)[3]));

	/*
	 * If a Task Management Function is active, रुको क्रम it to complete
	 * beक्रमe continuing with regular commands.
	 */
	spin_lock_irqsave(&cfg->पंचांगf_slock, lock_flags);
	अगर (cfg->पंचांगf_active) अणु
		spin_unlock_irqrestore(&cfg->पंचांगf_slock, lock_flags);
		rc = SCSI_MLQUEUE_HOST_BUSY;
		जाओ out;
	पूर्ण
	spin_unlock_irqrestore(&cfg->पंचांगf_slock, lock_flags);

	चयन (cfg->state) अणु
	हाल STATE_PROBING:
	हाल STATE_PROBED:
	हाल STATE_RESET:
		dev_dbg_ratelimited(dev, "%s: device is in reset\n", __func__);
		rc = SCSI_MLQUEUE_HOST_BUSY;
		जाओ out;
	हाल STATE_FAILTERM:
		dev_dbg_ratelimited(dev, "%s: device has failed\n", __func__);
		scp->result = (DID_NO_CONNECT << 16);
		scp->scsi_करोne(scp);
		rc = 0;
		जाओ out;
	शेष:
		atomic_inc(&afu->cmds_active);
		अवरोध;
	पूर्ण

	अगर (likely(sg)) अणु
		cmd->rcb.data_len = sg->length;
		cmd->rcb.data_ea = (uपूर्णांकptr_t)sg_virt(sg);
	पूर्ण

	cmd->scp = scp;
	cmd->parent = afu;
	cmd->hwq_index = hwq_index;

	cmd->sa.ioasc = 0;
	cmd->rcb.ctx_id = hwq->ctx_hndl;
	cmd->rcb.msi = SISL_MSI_RRQ_UPDATED;
	cmd->rcb.port_sel = CHAN2PORTMASK(scp->device->channel);
	cmd->rcb.lun_id = lun_to_lunid(scp->device->lun);

	अगर (scp->sc_data_direction == DMA_TO_DEVICE)
		req_flags |= SISL_REQ_FLAGS_HOST_WRITE;

	cmd->rcb.req_flags = req_flags;
	स_नकल(cmd->rcb.cdb, scp->cmnd, माप(cmd->rcb.cdb));

	rc = afu->send_cmd(afu, cmd);
	atomic_dec(&afu->cmds_active);
out:
	वापस rc;
पूर्ण

/**
 * cxlflash_रुको_क्रम_pci_err_recovery() - रुको क्रम error recovery during probe
 * @cfg:	Internal काष्ठाure associated with the host.
 */
अटल व्योम cxlflash_रुको_क्रम_pci_err_recovery(काष्ठा cxlflash_cfg *cfg)
अणु
	काष्ठा pci_dev *pdev = cfg->dev;

	अगर (pci_channel_offline(pdev))
		रुको_event_समयout(cfg->reset_रुकोq,
				   !pci_channel_offline(pdev),
				   CXLFLASH_PCI_ERROR_RECOVERY_TIMEOUT);
पूर्ण

/**
 * मुक्त_mem() - मुक्त memory associated with the AFU
 * @cfg:	Internal काष्ठाure associated with the host.
 */
अटल व्योम मुक्त_mem(काष्ठा cxlflash_cfg *cfg)
अणु
	काष्ठा afu *afu = cfg->afu;

	अगर (cfg->afu) अणु
		मुक्त_pages((uदीर्घ)afu, get_order(माप(काष्ठा afu)));
		cfg->afu = शून्य;
	पूर्ण
पूर्ण

/**
 * cxlflash_reset_sync() - synchronizing poपूर्णांक क्रम asynchronous resets
 * @cfg:	Internal काष्ठाure associated with the host.
 */
अटल व्योम cxlflash_reset_sync(काष्ठा cxlflash_cfg *cfg)
अणु
	अगर (cfg->async_reset_cookie == 0)
		वापस;

	/* Wait until all async calls prior to this cookie have completed */
	async_synchronize_cookie(cfg->async_reset_cookie + 1);
	cfg->async_reset_cookie = 0;
पूर्ण

/**
 * stop_afu() - stops the AFU command समयrs and unmaps the MMIO space
 * @cfg:	Internal काष्ठाure associated with the host.
 *
 * Safe to call with AFU in a partially allocated/initialized state.
 *
 * Cancels scheduled worker thपढ़ोs, रुकोs क्रम any active पूर्णांकernal AFU
 * commands to समयout, disables IRQ polling and then unmaps the MMIO space.
 */
अटल व्योम stop_afu(काष्ठा cxlflash_cfg *cfg)
अणु
	काष्ठा afu *afu = cfg->afu;
	काष्ठा hwq *hwq;
	पूर्णांक i;

	cancel_work_sync(&cfg->work_q);
	अगर (!current_is_async())
		cxlflash_reset_sync(cfg);

	अगर (likely(afu)) अणु
		जबतक (atomic_पढ़ो(&afu->cmds_active))
			ssleep(1);

		अगर (afu_is_irqpoll_enabled(afu)) अणु
			क्रम (i = 0; i < afu->num_hwqs; i++) अणु
				hwq = get_hwq(afu, i);

				irq_poll_disable(&hwq->irqpoll);
			पूर्ण
		पूर्ण

		अगर (likely(afu->afu_map)) अणु
			cfg->ops->psa_unmap(afu->afu_map);
			afu->afu_map = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * term_पूर्णांकr() - disables all AFU पूर्णांकerrupts
 * @cfg:	Internal काष्ठाure associated with the host.
 * @level:	Depth of allocation, where to begin waterfall tear करोwn.
 * @index:	Index of the hardware queue.
 *
 * Safe to call with AFU/MC in partially allocated/initialized state.
 */
अटल व्योम term_पूर्णांकr(काष्ठा cxlflash_cfg *cfg, क्रमागत unकरो_level level,
		      u32 index)
अणु
	काष्ठा afu *afu = cfg->afu;
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा hwq *hwq;

	अगर (!afu) अणु
		dev_err(dev, "%s: returning with NULL afu\n", __func__);
		वापस;
	पूर्ण

	hwq = get_hwq(afu, index);

	अगर (!hwq->ctx_cookie) अणु
		dev_err(dev, "%s: returning with NULL MC\n", __func__);
		वापस;
	पूर्ण

	चयन (level) अणु
	हाल UNMAP_THREE:
		/* SISL_MSI_ASYNC_ERROR is setup only क्रम the primary HWQ */
		अगर (index == PRIMARY_HWQ)
			cfg->ops->unmap_afu_irq(hwq->ctx_cookie, 3, hwq);
		fallthrough;
	हाल UNMAP_TWO:
		cfg->ops->unmap_afu_irq(hwq->ctx_cookie, 2, hwq);
		fallthrough;
	हाल UNMAP_ONE:
		cfg->ops->unmap_afu_irq(hwq->ctx_cookie, 1, hwq);
		fallthrough;
	हाल FREE_IRQ:
		cfg->ops->मुक्त_afu_irqs(hwq->ctx_cookie);
		fallthrough;
	हाल UNDO_NOOP:
		/* No action required */
		अवरोध;
	पूर्ण
पूर्ण

/**
 * term_mc() - terminates the master context
 * @cfg:	Internal काष्ठाure associated with the host.
 * @index:	Index of the hardware queue.
 *
 * Safe to call with AFU/MC in partially allocated/initialized state.
 */
अटल व्योम term_mc(काष्ठा cxlflash_cfg *cfg, u32 index)
अणु
	काष्ठा afu *afu = cfg->afu;
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा hwq *hwq;
	uदीर्घ lock_flags;

	अगर (!afu) अणु
		dev_err(dev, "%s: returning with NULL afu\n", __func__);
		वापस;
	पूर्ण

	hwq = get_hwq(afu, index);

	अगर (!hwq->ctx_cookie) अणु
		dev_err(dev, "%s: returning with NULL MC\n", __func__);
		वापस;
	पूर्ण

	WARN_ON(cfg->ops->stop_context(hwq->ctx_cookie));
	अगर (index != PRIMARY_HWQ)
		WARN_ON(cfg->ops->release_context(hwq->ctx_cookie));
	hwq->ctx_cookie = शून्य;

	spin_lock_irqsave(&hwq->hrrq_slock, lock_flags);
	hwq->hrrq_online = false;
	spin_unlock_irqrestore(&hwq->hrrq_slock, lock_flags);

	spin_lock_irqsave(&hwq->hsq_slock, lock_flags);
	flush_pending_cmds(hwq);
	spin_unlock_irqrestore(&hwq->hsq_slock, lock_flags);
पूर्ण

/**
 * term_afu() - terminates the AFU
 * @cfg:	Internal काष्ठाure associated with the host.
 *
 * Safe to call with AFU/MC in partially allocated/initialized state.
 */
अटल व्योम term_afu(काष्ठा cxlflash_cfg *cfg)
अणु
	काष्ठा device *dev = &cfg->dev->dev;
	पूर्णांक k;

	/*
	 * Tear करोwn is carefully orchestrated to ensure
	 * no पूर्णांकerrupts can come in when the problem state
	 * area is unmapped.
	 *
	 * 1) Disable all AFU पूर्णांकerrupts क्रम each master
	 * 2) Unmap the problem state area
	 * 3) Stop each master context
	 */
	क्रम (k = cfg->afu->num_hwqs - 1; k >= 0; k--)
		term_पूर्णांकr(cfg, UNMAP_THREE, k);

	stop_afu(cfg);

	क्रम (k = cfg->afu->num_hwqs - 1; k >= 0; k--)
		term_mc(cfg, k);

	dev_dbg(dev, "%s: returning\n", __func__);
पूर्ण

/**
 * notअगरy_shutकरोwn() - notअगरies device of pending shutकरोwn
 * @cfg:	Internal काष्ठाure associated with the host.
 * @रुको:	Whether to रुको क्रम shutकरोwn processing to complete.
 *
 * This function will notअगरy the AFU that the adapter is being shutकरोwn
 * and will रुको क्रम shutकरोwn processing to complete अगर रुको is true.
 * This notअगरication should flush pending I/Os to the device and halt
 * further I/Os until the next AFU reset is issued and device restarted.
 */
अटल व्योम notअगरy_shutकरोwn(काष्ठा cxlflash_cfg *cfg, bool रुको)
अणु
	काष्ठा afu *afu = cfg->afu;
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा dev_dependent_vals *ddv;
	__be64 __iomem *fc_port_regs;
	u64 reg, status;
	पूर्णांक i, retry_cnt = 0;

	ddv = (काष्ठा dev_dependent_vals *)cfg->dev_id->driver_data;
	अगर (!(ddv->flags & CXLFLASH_NOTIFY_SHUTDOWN))
		वापस;

	अगर (!afu || !afu->afu_map) अणु
		dev_dbg(dev, "%s: Problem state area not mapped\n", __func__);
		वापस;
	पूर्ण

	/* Notअगरy AFU */
	क्रम (i = 0; i < cfg->num_fc_ports; i++) अणु
		fc_port_regs = get_fc_port_regs(cfg, i);

		reg = पढ़ोq_be(&fc_port_regs[FC_CONFIG2 / 8]);
		reg |= SISL_FC_SHUTDOWN_NORMAL;
		ग_लिखोq_be(reg, &fc_port_regs[FC_CONFIG2 / 8]);
	पूर्ण

	अगर (!रुको)
		वापस;

	/* Wait up to 1.5 seconds क्रम shutकरोwn processing to complete */
	क्रम (i = 0; i < cfg->num_fc_ports; i++) अणु
		fc_port_regs = get_fc_port_regs(cfg, i);
		retry_cnt = 0;

		जबतक (true) अणु
			status = पढ़ोq_be(&fc_port_regs[FC_STATUS / 8]);
			अगर (status & SISL_STATUS_SHUTDOWN_COMPLETE)
				अवरोध;
			अगर (++retry_cnt >= MC_RETRY_CNT) अणु
				dev_dbg(dev, "%s: port %d shutdown processing "
					"not yet completed\n", __func__, i);
				अवरोध;
			पूर्ण
			msleep(100 * retry_cnt);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * cxlflash_get_minor() - माला_लो the first available minor number
 *
 * Return: Unique minor number that can be used to create the अक्षरacter device.
 */
अटल पूर्णांक cxlflash_get_minor(व्योम)
अणु
	पूर्णांक minor;
	दीर्घ bit;

	bit = find_first_zero_bit(cxlflash_minor, CXLFLASH_MAX_ADAPTERS);
	अगर (bit >= CXLFLASH_MAX_ADAPTERS)
		वापस -1;

	minor = bit & MINORMASK;
	set_bit(minor, cxlflash_minor);
	वापस minor;
पूर्ण

/**
 * cxlflash_put_minor() - releases the minor number
 * @minor:	Minor number that is no दीर्घer needed.
 */
अटल व्योम cxlflash_put_minor(पूर्णांक minor)
अणु
	clear_bit(minor, cxlflash_minor);
पूर्ण

/**
 * cxlflash_release_chrdev() - release the अक्षरacter device क्रम the host
 * @cfg:	Internal काष्ठाure associated with the host.
 */
अटल व्योम cxlflash_release_chrdev(काष्ठा cxlflash_cfg *cfg)
अणु
	device_unरेजिस्टर(cfg->अक्षरdev);
	cfg->अक्षरdev = शून्य;
	cdev_del(&cfg->cdev);
	cxlflash_put_minor(MINOR(cfg->cdev.dev));
पूर्ण

/**
 * cxlflash_हटाओ() - PCI entry poपूर्णांक to tear करोwn host
 * @pdev:	PCI device associated with the host.
 *
 * Safe to use as a cleanup in partially allocated/initialized state. Note that
 * the reset_रुकोq is flushed as part of the stop/termination of user contexts.
 */
अटल व्योम cxlflash_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा cxlflash_cfg *cfg = pci_get_drvdata(pdev);
	काष्ठा device *dev = &pdev->dev;
	uदीर्घ lock_flags;

	अगर (!pci_is_enabled(pdev)) अणु
		dev_dbg(dev, "%s: Device is disabled\n", __func__);
		वापस;
	पूर्ण

	/* Yield to running recovery thपढ़ोs beक्रमe continuing with हटाओ */
	रुको_event(cfg->reset_रुकोq, cfg->state != STATE_RESET &&
				     cfg->state != STATE_PROBING);
	spin_lock_irqsave(&cfg->पंचांगf_slock, lock_flags);
	अगर (cfg->पंचांगf_active)
		रुको_event_पूर्णांकerruptible_lock_irq(cfg->पंचांगf_रुकोq,
						  !cfg->पंचांगf_active,
						  cfg->पंचांगf_slock);
	spin_unlock_irqrestore(&cfg->पंचांगf_slock, lock_flags);

	/* Notअगरy AFU and रुको क्रम shutकरोwn processing to complete */
	notअगरy_shutकरोwn(cfg, true);

	cfg->state = STATE_FAILTERM;
	cxlflash_stop_term_user_contexts(cfg);

	चयन (cfg->init_state) अणु
	हाल INIT_STATE_CDEV:
		cxlflash_release_chrdev(cfg);
		fallthrough;
	हाल INIT_STATE_SCSI:
		cxlflash_term_local_luns(cfg);
		scsi_हटाओ_host(cfg->host);
		fallthrough;
	हाल INIT_STATE_AFU:
		term_afu(cfg);
		fallthrough;
	हाल INIT_STATE_PCI:
		cfg->ops->destroy_afu(cfg->afu_cookie);
		pci_disable_device(pdev);
		fallthrough;
	हाल INIT_STATE_NONE:
		मुक्त_mem(cfg);
		scsi_host_put(cfg->host);
		अवरोध;
	पूर्ण

	dev_dbg(dev, "%s: returning\n", __func__);
पूर्ण

/**
 * alloc_mem() - allocates the AFU and its command pool
 * @cfg:	Internal काष्ठाure associated with the host.
 *
 * A partially allocated state reमुख्यs on failure.
 *
 * Return:
 *	0 on success
 *	-ENOMEM on failure to allocate memory
 */
अटल पूर्णांक alloc_mem(काष्ठा cxlflash_cfg *cfg)
अणु
	पूर्णांक rc = 0;
	काष्ठा device *dev = &cfg->dev->dev;

	/* AFU is ~28k, i.e. only one 64k page or up to seven 4k pages */
	cfg->afu = (व्योम *)__get_मुक्त_pages(GFP_KERNEL | __GFP_ZERO,
					    get_order(माप(काष्ठा afu)));
	अगर (unlikely(!cfg->afu)) अणु
		dev_err(dev, "%s: cannot get %d free pages\n",
			__func__, get_order(माप(काष्ठा afu)));
		rc = -ENOMEM;
		जाओ out;
	पूर्ण
	cfg->afu->parent = cfg;
	cfg->afu->desired_hwqs = CXLFLASH_DEF_HWQS;
	cfg->afu->afu_map = शून्य;
out:
	वापस rc;
पूर्ण

/**
 * init_pci() - initializes the host as a PCI device
 * @cfg:	Internal काष्ठाure associated with the host.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक init_pci(काष्ठा cxlflash_cfg *cfg)
अणु
	काष्ठा pci_dev *pdev = cfg->dev;
	काष्ठा device *dev = &cfg->dev->dev;
	पूर्णांक rc = 0;

	rc = pci_enable_device(pdev);
	अगर (rc || pci_channel_offline(pdev)) अणु
		अगर (pci_channel_offline(pdev)) अणु
			cxlflash_रुको_क्रम_pci_err_recovery(cfg);
			rc = pci_enable_device(pdev);
		पूर्ण

		अगर (rc) अणु
			dev_err(dev, "%s: Cannot enable adapter\n", __func__);
			cxlflash_रुको_क्रम_pci_err_recovery(cfg);
			जाओ out;
		पूर्ण
	पूर्ण

out:
	dev_dbg(dev, "%s: returning rc=%d\n", __func__, rc);
	वापस rc;
पूर्ण

/**
 * init_scsi() - adds the host to the SCSI stack and kicks off host scan
 * @cfg:	Internal काष्ठाure associated with the host.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक init_scsi(काष्ठा cxlflash_cfg *cfg)
अणु
	काष्ठा pci_dev *pdev = cfg->dev;
	काष्ठा device *dev = &cfg->dev->dev;
	पूर्णांक rc = 0;

	rc = scsi_add_host(cfg->host, &pdev->dev);
	अगर (rc) अणु
		dev_err(dev, "%s: scsi_add_host failed rc=%d\n", __func__, rc);
		जाओ out;
	पूर्ण

	scsi_scan_host(cfg->host);

out:
	dev_dbg(dev, "%s: returning rc=%d\n", __func__, rc);
	वापस rc;
पूर्ण

/**
 * set_port_online() - transitions the specअगरied host FC port to online state
 * @fc_regs:	Top of MMIO region defined क्रम specअगरied port.
 *
 * The provided MMIO region must be mapped prior to call. Online state means
 * that the FC link layer has synced, completed the handshaking process, and
 * is पढ़ोy क्रम login to start.
 */
अटल व्योम set_port_online(__be64 __iomem *fc_regs)
अणु
	u64 cmdcfg;

	cmdcfg = पढ़ोq_be(&fc_regs[FC_MTIP_CMDCONFIG / 8]);
	cmdcfg &= (~FC_MTIP_CMDCONFIG_OFFLINE);	/* clear OFF_LINE */
	cmdcfg |= (FC_MTIP_CMDCONFIG_ONLINE);	/* set ON_LINE */
	ग_लिखोq_be(cmdcfg, &fc_regs[FC_MTIP_CMDCONFIG / 8]);
पूर्ण

/**
 * set_port_offline() - transitions the specअगरied host FC port to offline state
 * @fc_regs:	Top of MMIO region defined क्रम specअगरied port.
 *
 * The provided MMIO region must be mapped prior to call.
 */
अटल व्योम set_port_offline(__be64 __iomem *fc_regs)
अणु
	u64 cmdcfg;

	cmdcfg = पढ़ोq_be(&fc_regs[FC_MTIP_CMDCONFIG / 8]);
	cmdcfg &= (~FC_MTIP_CMDCONFIG_ONLINE);	/* clear ON_LINE */
	cmdcfg |= (FC_MTIP_CMDCONFIG_OFFLINE);	/* set OFF_LINE */
	ग_लिखोq_be(cmdcfg, &fc_regs[FC_MTIP_CMDCONFIG / 8]);
पूर्ण

/**
 * रुको_port_online() - रुकोs क्रम the specअगरied host FC port come online
 * @fc_regs:	Top of MMIO region defined क्रम specअगरied port.
 * @delay_us:	Number of microseconds to delay between पढ़ोing port status.
 * @nretry:	Number of cycles to retry पढ़ोing port status.
 *
 * The provided MMIO region must be mapped prior to call. This will समयout
 * when the cable is not plugged in.
 *
 * Return:
 *	TRUE (1) when the specअगरied port is online
 *	FALSE (0) when the specअगरied port fails to come online after समयout
 */
अटल bool रुको_port_online(__be64 __iomem *fc_regs, u32 delay_us, u32 nretry)
अणु
	u64 status;

	WARN_ON(delay_us < 1000);

	करो अणु
		msleep(delay_us / 1000);
		status = पढ़ोq_be(&fc_regs[FC_MTIP_STATUS / 8]);
		अगर (status == U64_MAX)
			nretry /= 2;
	पूर्ण जबतक ((status & FC_MTIP_STATUS_MASK) != FC_MTIP_STATUS_ONLINE &&
		 nretry--);

	वापस ((status & FC_MTIP_STATUS_MASK) == FC_MTIP_STATUS_ONLINE);
पूर्ण

/**
 * रुको_port_offline() - रुकोs क्रम the specअगरied host FC port go offline
 * @fc_regs:	Top of MMIO region defined क्रम specअगरied port.
 * @delay_us:	Number of microseconds to delay between पढ़ोing port status.
 * @nretry:	Number of cycles to retry पढ़ोing port status.
 *
 * The provided MMIO region must be mapped prior to call.
 *
 * Return:
 *	TRUE (1) when the specअगरied port is offline
 *	FALSE (0) when the specअगरied port fails to go offline after समयout
 */
अटल bool रुको_port_offline(__be64 __iomem *fc_regs, u32 delay_us, u32 nretry)
अणु
	u64 status;

	WARN_ON(delay_us < 1000);

	करो अणु
		msleep(delay_us / 1000);
		status = पढ़ोq_be(&fc_regs[FC_MTIP_STATUS / 8]);
		अगर (status == U64_MAX)
			nretry /= 2;
	पूर्ण जबतक ((status & FC_MTIP_STATUS_MASK) != FC_MTIP_STATUS_OFFLINE &&
		 nretry--);

	वापस ((status & FC_MTIP_STATUS_MASK) == FC_MTIP_STATUS_OFFLINE);
पूर्ण

/**
 * afu_set_wwpn() - configures the WWPN क्रम the specअगरied host FC port
 * @afu:	AFU associated with the host that owns the specअगरied FC port.
 * @port:	Port number being configured.
 * @fc_regs:	Top of MMIO region defined क्रम specअगरied port.
 * @wwpn:	The world-wide-port-number previously discovered क्रम port.
 *
 * The provided MMIO region must be mapped prior to call. As part of the
 * sequence to configure the WWPN, the port is toggled offline and then back
 * online. This toggling action can cause this routine to delay up to a few
 * seconds. When configured to use the पूर्णांकernal LUN feature of the AFU, a
 * failure to come online is overridden.
 */
अटल व्योम afu_set_wwpn(काष्ठा afu *afu, पूर्णांक port, __be64 __iomem *fc_regs,
			 u64 wwpn)
अणु
	काष्ठा cxlflash_cfg *cfg = afu->parent;
	काष्ठा device *dev = &cfg->dev->dev;

	set_port_offline(fc_regs);
	अगर (!रुको_port_offline(fc_regs, FC_PORT_STATUS_RETRY_INTERVAL_US,
			       FC_PORT_STATUS_RETRY_CNT)) अणु
		dev_dbg(dev, "%s: wait on port %d to go offline timed out\n",
			__func__, port);
	पूर्ण

	ग_लिखोq_be(wwpn, &fc_regs[FC_PNAME / 8]);

	set_port_online(fc_regs);
	अगर (!रुको_port_online(fc_regs, FC_PORT_STATUS_RETRY_INTERVAL_US,
			      FC_PORT_STATUS_RETRY_CNT)) अणु
		dev_dbg(dev, "%s: wait on port %d to go online timed out\n",
			__func__, port);
	पूर्ण
पूर्ण

/**
 * afu_link_reset() - resets the specअगरied host FC port
 * @afu:	AFU associated with the host that owns the specअगरied FC port.
 * @port:	Port number being configured.
 * @fc_regs:	Top of MMIO region defined क्रम specअगरied port.
 *
 * The provided MMIO region must be mapped prior to call. The sequence to
 * reset the port involves toggling it offline and then back online. This
 * action can cause this routine to delay up to a few seconds. An efक्रमt
 * is made to मुख्यtain link with the device by चयनing to host to use
 * the alternate port exclusively जबतक the reset takes place.
 * failure to come online is overridden.
 */
अटल व्योम afu_link_reset(काष्ठा afu *afu, पूर्णांक port, __be64 __iomem *fc_regs)
अणु
	काष्ठा cxlflash_cfg *cfg = afu->parent;
	काष्ठा device *dev = &cfg->dev->dev;
	u64 port_sel;

	/* first चयन the AFU to the other links, अगर any */
	port_sel = पढ़ोq_be(&afu->afu_map->global.regs.afu_port_sel);
	port_sel &= ~(1ULL << port);
	ग_लिखोq_be(port_sel, &afu->afu_map->global.regs.afu_port_sel);
	cxlflash_afu_sync(afu, 0, 0, AFU_GSYNC);

	set_port_offline(fc_regs);
	अगर (!रुको_port_offline(fc_regs, FC_PORT_STATUS_RETRY_INTERVAL_US,
			       FC_PORT_STATUS_RETRY_CNT))
		dev_err(dev, "%s: wait on port %d to go offline timed out\n",
			__func__, port);

	set_port_online(fc_regs);
	अगर (!रुको_port_online(fc_regs, FC_PORT_STATUS_RETRY_INTERVAL_US,
			      FC_PORT_STATUS_RETRY_CNT))
		dev_err(dev, "%s: wait on port %d to go online timed out\n",
			__func__, port);

	/* चयन back to include this port */
	port_sel |= (1ULL << port);
	ग_लिखोq_be(port_sel, &afu->afu_map->global.regs.afu_port_sel);
	cxlflash_afu_sync(afu, 0, 0, AFU_GSYNC);

	dev_dbg(dev, "%s: returning port_sel=%016llx\n", __func__, port_sel);
पूर्ण

/**
 * afu_err_पूर्णांकr_init() - clears and initializes the AFU क्रम error पूर्णांकerrupts
 * @afu:	AFU associated with the host.
 */
अटल व्योम afu_err_पूर्णांकr_init(काष्ठा afu *afu)
अणु
	काष्ठा cxlflash_cfg *cfg = afu->parent;
	__be64 __iomem *fc_port_regs;
	पूर्णांक i;
	काष्ठा hwq *hwq = get_hwq(afu, PRIMARY_HWQ);
	u64 reg;

	/* global async पूर्णांकerrupts: AFU clears afu_ctrl on context निकास
	 * अगर async पूर्णांकerrupts were sent to that context. This prevents
	 * the AFU क्रमm sending further async पूर्णांकerrupts when
	 * there is
	 * nobody to receive them.
	 */

	/* mask all */
	ग_लिखोq_be(-1ULL, &afu->afu_map->global.regs.aपूर्णांकr_mask);
	/* set LISN# to send and poपूर्णांक to primary master context */
	reg = ((u64) (((hwq->ctx_hndl << 8) | SISL_MSI_ASYNC_ERROR)) << 40);

	अगर (afu->पूर्णांकernal_lun)
		reg |= 1;	/* Bit 63 indicates local lun */
	ग_लिखोq_be(reg, &afu->afu_map->global.regs.afu_ctrl);
	/* clear all */
	ग_लिखोq_be(-1ULL, &afu->afu_map->global.regs.aपूर्णांकr_clear);
	/* unmask bits that are of पूर्णांकerest */
	/* note: afu can send an पूर्णांकerrupt after this step */
	ग_लिखोq_be(SISL_ASTATUS_MASK, &afu->afu_map->global.regs.aपूर्णांकr_mask);
	/* clear again in हाल a bit came on after previous clear but beक्रमe */
	/* unmask */
	ग_लिखोq_be(-1ULL, &afu->afu_map->global.regs.aपूर्णांकr_clear);

	/* Clear/Set पूर्णांकernal lun bits */
	fc_port_regs = get_fc_port_regs(cfg, 0);
	reg = पढ़ोq_be(&fc_port_regs[FC_CONFIG2 / 8]);
	reg &= SISL_FC_INTERNAL_MASK;
	अगर (afu->पूर्णांकernal_lun)
		reg |= ((u64)(afu->पूर्णांकernal_lun - 1) << SISL_FC_INTERNAL_SHIFT);
	ग_लिखोq_be(reg, &fc_port_regs[FC_CONFIG2 / 8]);

	/* now clear FC errors */
	क्रम (i = 0; i < cfg->num_fc_ports; i++) अणु
		fc_port_regs = get_fc_port_regs(cfg, i);

		ग_लिखोq_be(0xFFFFFFFFU, &fc_port_regs[FC_ERROR / 8]);
		ग_लिखोq_be(0, &fc_port_regs[FC_ERRCAP / 8]);
	पूर्ण

	/* sync पूर्णांकerrupts क्रम master's IOARRIN ग_लिखो */
	/* note that unlike asyncs, there can be no pending sync पूर्णांकerrupts */
	/* at this समय (this is a fresh context and master has not written */
	/* IOARRIN yet), so there is nothing to clear. */

	/* set LISN#, it is always sent to the context that wrote IOARRIN */
	क्रम (i = 0; i < afu->num_hwqs; i++) अणु
		hwq = get_hwq(afu, i);

		reg = पढ़ोq_be(&hwq->host_map->ctx_ctrl);
		WARN_ON((reg & SISL_CTX_CTRL_LISN_MASK) != 0);
		reg |= SISL_MSI_SYNC_ERROR;
		ग_लिखोq_be(reg, &hwq->host_map->ctx_ctrl);
		ग_लिखोq_be(SISL_ISTATUS_MASK, &hwq->host_map->पूर्णांकr_mask);
	पूर्ण
पूर्ण

/**
 * cxlflash_sync_err_irq() - पूर्णांकerrupt handler क्रम synchronous errors
 * @irq:	Interrupt number.
 * @data:	Private data provided at पूर्णांकerrupt registration, the AFU.
 *
 * Return: Always वापस IRQ_HANDLED.
 */
अटल irqवापस_t cxlflash_sync_err_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा hwq *hwq = (काष्ठा hwq *)data;
	काष्ठा cxlflash_cfg *cfg = hwq->afu->parent;
	काष्ठा device *dev = &cfg->dev->dev;
	u64 reg;
	u64 reg_unmasked;

	reg = पढ़ोq_be(&hwq->host_map->पूर्णांकr_status);
	reg_unmasked = (reg & SISL_ISTATUS_UNMASK);

	अगर (reg_unmasked == 0UL) अणु
		dev_err(dev, "%s: spurious interrupt, intr_status=%016llx\n",
			__func__, reg);
		जाओ cxlflash_sync_err_irq_निकास;
	पूर्ण

	dev_err(dev, "%s: unexpected interrupt, intr_status=%016llx\n",
		__func__, reg);

	ग_लिखोq_be(reg_unmasked, &hwq->host_map->पूर्णांकr_clear);

cxlflash_sync_err_irq_निकास:
	वापस IRQ_HANDLED;
पूर्ण

/**
 * process_hrrq() - process the पढ़ो-response queue
 * @hwq:	HWQ associated with the host.
 * @करोneq:	Queue of commands harvested from the RRQ.
 * @budget:	Threshold of RRQ entries to process.
 *
 * This routine must be called holding the disabled RRQ spin lock.
 *
 * Return: The number of entries processed.
 */
अटल पूर्णांक process_hrrq(काष्ठा hwq *hwq, काष्ठा list_head *करोneq, पूर्णांक budget)
अणु
	काष्ठा afu *afu = hwq->afu;
	काष्ठा afu_cmd *cmd;
	काष्ठा sisl_ioasa *ioasa;
	काष्ठा sisl_ioarcb *ioarcb;
	bool toggle = hwq->toggle;
	पूर्णांक num_hrrq = 0;
	u64 entry,
	    *hrrq_start = hwq->hrrq_start,
	    *hrrq_end = hwq->hrrq_end,
	    *hrrq_curr = hwq->hrrq_curr;

	/* Process पढ़ोy RRQ entries up to the specअगरied budget (अगर any) */
	जबतक (true) अणु
		entry = *hrrq_curr;

		अगर ((entry & SISL_RESP_HANDLE_T_BIT) != toggle)
			अवरोध;

		entry &= ~SISL_RESP_HANDLE_T_BIT;

		अगर (afu_is_sq_cmd_mode(afu)) अणु
			ioasa = (काष्ठा sisl_ioasa *)entry;
			cmd = container_of(ioasa, काष्ठा afu_cmd, sa);
		पूर्ण अन्यथा अणु
			ioarcb = (काष्ठा sisl_ioarcb *)entry;
			cmd = container_of(ioarcb, काष्ठा afu_cmd, rcb);
		पूर्ण

		list_add_tail(&cmd->queue, करोneq);

		/* Advance to next entry or wrap and flip the toggle bit */
		अगर (hrrq_curr < hrrq_end)
			hrrq_curr++;
		अन्यथा अणु
			hrrq_curr = hrrq_start;
			toggle ^= SISL_RESP_HANDLE_T_BIT;
		पूर्ण

		atomic_inc(&hwq->hsq_credits);
		num_hrrq++;

		अगर (budget > 0 && num_hrrq >= budget)
			अवरोध;
	पूर्ण

	hwq->hrrq_curr = hrrq_curr;
	hwq->toggle = toggle;

	वापस num_hrrq;
पूर्ण

/**
 * process_cmd_करोneq() - process a queue of harvested RRQ commands
 * @करोneq:	Queue of completed commands.
 *
 * Note that upon वापस the queue can no दीर्घer be trusted.
 */
अटल व्योम process_cmd_करोneq(काष्ठा list_head *करोneq)
अणु
	काष्ठा afu_cmd *cmd, *पंचांगp;

	WARN_ON(list_empty(करोneq));

	list_क्रम_each_entry_safe(cmd, पंचांगp, करोneq, queue)
		cmd_complete(cmd);
पूर्ण

/**
 * cxlflash_irqpoll() - process a queue of harvested RRQ commands
 * @irqpoll:	IRQ poll काष्ठाure associated with queue to poll.
 * @budget:	Threshold of RRQ entries to process per poll.
 *
 * Return: The number of entries processed.
 */
अटल पूर्णांक cxlflash_irqpoll(काष्ठा irq_poll *irqpoll, पूर्णांक budget)
अणु
	काष्ठा hwq *hwq = container_of(irqpoll, काष्ठा hwq, irqpoll);
	अचिन्हित दीर्घ hrrq_flags;
	LIST_HEAD(करोneq);
	पूर्णांक num_entries = 0;

	spin_lock_irqsave(&hwq->hrrq_slock, hrrq_flags);

	num_entries = process_hrrq(hwq, &करोneq, budget);
	अगर (num_entries < budget)
		irq_poll_complete(irqpoll);

	spin_unlock_irqrestore(&hwq->hrrq_slock, hrrq_flags);

	process_cmd_करोneq(&करोneq);
	वापस num_entries;
पूर्ण

/**
 * cxlflash_rrq_irq() - पूर्णांकerrupt handler क्रम पढ़ो-response queue (normal path)
 * @irq:	Interrupt number.
 * @data:	Private data provided at पूर्णांकerrupt registration, the AFU.
 *
 * Return: IRQ_HANDLED or IRQ_NONE when no पढ़ोy entries found.
 */
अटल irqवापस_t cxlflash_rrq_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा hwq *hwq = (काष्ठा hwq *)data;
	काष्ठा afu *afu = hwq->afu;
	अचिन्हित दीर्घ hrrq_flags;
	LIST_HEAD(करोneq);
	पूर्णांक num_entries = 0;

	spin_lock_irqsave(&hwq->hrrq_slock, hrrq_flags);

	/* Silently drop spurious पूर्णांकerrupts when queue is not online */
	अगर (!hwq->hrrq_online) अणु
		spin_unlock_irqrestore(&hwq->hrrq_slock, hrrq_flags);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (afu_is_irqpoll_enabled(afu)) अणु
		irq_poll_sched(&hwq->irqpoll);
		spin_unlock_irqrestore(&hwq->hrrq_slock, hrrq_flags);
		वापस IRQ_HANDLED;
	पूर्ण

	num_entries = process_hrrq(hwq, &करोneq, -1);
	spin_unlock_irqrestore(&hwq->hrrq_slock, hrrq_flags);

	अगर (num_entries == 0)
		वापस IRQ_NONE;

	process_cmd_करोneq(&करोneq);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * Asynchronous पूर्णांकerrupt inक्रमmation table
 *
 * NOTE:
 *	- Order matters here as this array is indexed by bit position.
 *
 *	- The checkpatch script considers the BUILD_SISL_ASTATUS_FC_PORT macro
 *	  as complex and complains due to a lack of parentheses/braces.
 */
#घोषणा ASTATUS_FC(_a, _b, _c, _d)					 \
	अणु SISL_ASTATUS_FC##_a##_##_b, _c, _a, (_d) पूर्ण

#घोषणा BUILD_SISL_ASTATUS_FC_PORT(_a)					 \
	ASTATUS_FC(_a, LINK_UP, "link up", 0),				 \
	ASTATUS_FC(_a, LINK_DN, "link down", 0),			 \
	ASTATUS_FC(_a, LOGI_S, "login succeeded", SCAN_HOST),		 \
	ASTATUS_FC(_a, LOGI_F, "login failed", CLR_FC_ERROR),		 \
	ASTATUS_FC(_a, LOGI_R, "login timed out, retrying", LINK_RESET), \
	ASTATUS_FC(_a, CRC_T, "CRC threshold exceeded", LINK_RESET),	 \
	ASTATUS_FC(_a, LOGO, "target initiated LOGO", 0),		 \
	ASTATUS_FC(_a, OTHER, "other error", CLR_FC_ERROR | LINK_RESET)

अटल स्थिर काष्ठा asyc_पूर्णांकr_info ainfo[] = अणु
	BUILD_SISL_ASTATUS_FC_PORT(1),
	BUILD_SISL_ASTATUS_FC_PORT(0),
	BUILD_SISL_ASTATUS_FC_PORT(3),
	BUILD_SISL_ASTATUS_FC_PORT(2)
पूर्ण;

/**
 * cxlflash_async_err_irq() - पूर्णांकerrupt handler क्रम asynchronous errors
 * @irq:	Interrupt number.
 * @data:	Private data provided at पूर्णांकerrupt registration, the AFU.
 *
 * Return: Always वापस IRQ_HANDLED.
 */
अटल irqवापस_t cxlflash_async_err_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा hwq *hwq = (काष्ठा hwq *)data;
	काष्ठा afu *afu = hwq->afu;
	काष्ठा cxlflash_cfg *cfg = afu->parent;
	काष्ठा device *dev = &cfg->dev->dev;
	स्थिर काष्ठा asyc_पूर्णांकr_info *info;
	काष्ठा sisl_global_map __iomem *global = &afu->afu_map->global;
	__be64 __iomem *fc_port_regs;
	u64 reg_unmasked;
	u64 reg;
	u64 bit;
	u8 port;

	reg = पढ़ोq_be(&global->regs.aपूर्णांकr_status);
	reg_unmasked = (reg & SISL_ASTATUS_UNMASK);

	अगर (unlikely(reg_unmasked == 0)) अणु
		dev_err(dev, "%s: spurious interrupt, aintr_status=%016llx\n",
			__func__, reg);
		जाओ out;
	पूर्ण

	/* FYI, it is 'okay' to clear AFU status beक्रमe FC_ERROR */
	ग_लिखोq_be(reg_unmasked, &global->regs.aपूर्णांकr_clear);

	/* Check each bit that is on */
	क्रम_each_set_bit(bit, (uदीर्घ *)&reg_unmasked, BITS_PER_LONG) अणु
		अगर (unlikely(bit >= ARRAY_SIZE(ainfo))) अणु
			WARN_ON_ONCE(1);
			जारी;
		पूर्ण

		info = &ainfo[bit];
		अगर (unlikely(info->status != 1ULL << bit)) अणु
			WARN_ON_ONCE(1);
			जारी;
		पूर्ण

		port = info->port;
		fc_port_regs = get_fc_port_regs(cfg, port);

		dev_err(dev, "%s: FC Port %d -> %s, fc_status=%016llx\n",
			__func__, port, info->desc,
		       पढ़ोq_be(&fc_port_regs[FC_STATUS / 8]));

		/*
		 * Do link reset first, some OTHER errors will set FC_ERROR
		 * again अगर cleared beक्रमe or w/o a reset
		 */
		अगर (info->action & LINK_RESET) अणु
			dev_err(dev, "%s: FC Port %d: resetting link\n",
				__func__, port);
			cfg->lr_state = LINK_RESET_REQUIRED;
			cfg->lr_port = port;
			schedule_work(&cfg->work_q);
		पूर्ण

		अगर (info->action & CLR_FC_ERROR) अणु
			reg = पढ़ोq_be(&fc_port_regs[FC_ERROR / 8]);

			/*
			 * Since all errors are unmasked, FC_ERROR and FC_ERRCAP
			 * should be the same and tracing one is sufficient.
			 */

			dev_err(dev, "%s: fc %d: clearing fc_error=%016llx\n",
				__func__, port, reg);

			ग_लिखोq_be(reg, &fc_port_regs[FC_ERROR / 8]);
			ग_लिखोq_be(0, &fc_port_regs[FC_ERRCAP / 8]);
		पूर्ण

		अगर (info->action & SCAN_HOST) अणु
			atomic_inc(&cfg->scan_host_needed);
			schedule_work(&cfg->work_q);
		पूर्ण
	पूर्ण

out:
	वापस IRQ_HANDLED;
पूर्ण

/**
 * पढ़ो_vpd() - obtains the WWPNs from VPD
 * @cfg:	Internal काष्ठाure associated with the host.
 * @wwpn:	Array of size MAX_FC_PORTS to pass back WWPNs
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक पढ़ो_vpd(काष्ठा cxlflash_cfg *cfg, u64 wwpn[])
अणु
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा pci_dev *pdev = cfg->dev;
	पूर्णांक rc = 0;
	पूर्णांक ro_start, ro_size, i, j, k;
	sमाप_प्रकार vpd_size;
	अक्षर vpd_data[CXLFLASH_VPD_LEN];
	अक्षर पंचांगp_buf[WWPN_BUF_LEN] = अणु 0 पूर्ण;
	स्थिर काष्ठा dev_dependent_vals *ddv = (काष्ठा dev_dependent_vals *)
						cfg->dev_id->driver_data;
	स्थिर bool wwpn_vpd_required = ddv->flags & CXLFLASH_WWPN_VPD_REQUIRED;
	स्थिर अक्षर *wwpn_vpd_tags[MAX_FC_PORTS] = अणु "V5", "V6", "V7", "V8" पूर्ण;

	/* Get the VPD data from the device */
	vpd_size = cfg->ops->पढ़ो_adapter_vpd(pdev, vpd_data, माप(vpd_data));
	अगर (unlikely(vpd_size <= 0)) अणु
		dev_err(dev, "%s: Unable to read VPD (size = %ld)\n",
			__func__, vpd_size);
		rc = -ENODEV;
		जाओ out;
	पूर्ण

	/* Get the पढ़ो only section offset */
	ro_start = pci_vpd_find_tag(vpd_data, vpd_size, PCI_VPD_LRDT_RO_DATA);
	अगर (unlikely(ro_start < 0)) अणु
		dev_err(dev, "%s: VPD Read-only data not found\n", __func__);
		rc = -ENODEV;
		जाओ out;
	पूर्ण

	/* Get the पढ़ो only section size, cap when extends beyond पढ़ो VPD */
	ro_size = pci_vpd_lrdt_size(&vpd_data[ro_start]);
	j = ro_size;
	i = ro_start + PCI_VPD_LRDT_TAG_SIZE;
	अगर (unlikely((i + j) > vpd_size)) अणु
		dev_dbg(dev, "%s: Might need to read more VPD (%d > %ld)\n",
			__func__, (i + j), vpd_size);
		ro_size = vpd_size - i;
	पूर्ण

	/*
	 * Find the offset of the WWPN tag within the पढ़ो only
	 * VPD data and validate the found field (partials are
	 * no good to us). Convert the ASCII data to an पूर्णांकeger
	 * value. Note that we must copy to a temporary buffer
	 * because the conversion service requires that the ASCII
	 * string be terminated.
	 *
	 * Allow क्रम WWPN not being found क्रम all devices, setting
	 * the वापसed WWPN to zero when not found. Notअगरy with a
	 * log error क्रम cards that should have had WWPN keywords
	 * in the VPD - cards requiring WWPN will not have their
	 * ports programmed and operate in an undefined state.
	 */
	क्रम (k = 0; k < cfg->num_fc_ports; k++) अणु
		j = ro_size;
		i = ro_start + PCI_VPD_LRDT_TAG_SIZE;

		i = pci_vpd_find_info_keyword(vpd_data, i, j, wwpn_vpd_tags[k]);
		अगर (i < 0) अणु
			अगर (wwpn_vpd_required)
				dev_err(dev, "%s: Port %d WWPN not found\n",
					__func__, k);
			wwpn[k] = 0ULL;
			जारी;
		पूर्ण

		j = pci_vpd_info_field_size(&vpd_data[i]);
		i += PCI_VPD_INFO_FLD_HDR_SIZE;
		अगर (unlikely((i + j > vpd_size) || (j != WWPN_LEN))) अणु
			dev_err(dev, "%s: Port %d WWPN incomplete or bad VPD\n",
				__func__, k);
			rc = -ENODEV;
			जाओ out;
		पूर्ण

		स_नकल(पंचांगp_buf, &vpd_data[i], WWPN_LEN);
		rc = kम_से_अदीर्घ(पंचांगp_buf, WWPN_LEN, (uदीर्घ *)&wwpn[k]);
		अगर (unlikely(rc)) अणु
			dev_err(dev, "%s: WWPN conversion failed for port %d\n",
				__func__, k);
			rc = -ENODEV;
			जाओ out;
		पूर्ण

		dev_dbg(dev, "%s: wwpn%d=%016llx\n", __func__, k, wwpn[k]);
	पूर्ण

out:
	dev_dbg(dev, "%s: returning rc=%d\n", __func__, rc);
	वापस rc;
पूर्ण

/**
 * init_pcr() - initialize the provisioning and control रेजिस्टरs
 * @cfg:	Internal काष्ठाure associated with the host.
 *
 * Also sets up fast access to the mapped रेजिस्टरs and initializes AFU
 * command fields that never change.
 */
अटल व्योम init_pcr(काष्ठा cxlflash_cfg *cfg)
अणु
	काष्ठा afu *afu = cfg->afu;
	काष्ठा sisl_ctrl_map __iomem *ctrl_map;
	काष्ठा hwq *hwq;
	व्योम *cookie;
	पूर्णांक i;

	क्रम (i = 0; i < MAX_CONTEXT; i++) अणु
		ctrl_map = &afu->afu_map->ctrls[i].ctrl;
		/* Disrupt any clients that could be running */
		/* e.g. clients that survived a master restart */
		ग_लिखोq_be(0, &ctrl_map->rht_start);
		ग_लिखोq_be(0, &ctrl_map->rht_cnt_id);
		ग_लिखोq_be(0, &ctrl_map->ctx_cap);
	पूर्ण

	/* Copy frequently used fields पूर्णांकo hwq */
	क्रम (i = 0; i < afu->num_hwqs; i++) अणु
		hwq = get_hwq(afu, i);
		cookie = hwq->ctx_cookie;

		hwq->ctx_hndl = (u16) cfg->ops->process_element(cookie);
		hwq->host_map = &afu->afu_map->hosts[hwq->ctx_hndl].host;
		hwq->ctrl_map = &afu->afu_map->ctrls[hwq->ctx_hndl].ctrl;

		/* Program the Endian Control क्रम the master context */
		ग_लिखोq_be(SISL_ENDIAN_CTRL, &hwq->host_map->endian_ctrl);
	पूर्ण
पूर्ण

/**
 * init_global() - initialize AFU global रेजिस्टरs
 * @cfg:	Internal काष्ठाure associated with the host.
 */
अटल पूर्णांक init_global(काष्ठा cxlflash_cfg *cfg)
अणु
	काष्ठा afu *afu = cfg->afu;
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा hwq *hwq;
	काष्ठा sisl_host_map __iomem *hmap;
	__be64 __iomem *fc_port_regs;
	u64 wwpn[MAX_FC_PORTS];	/* wwpn of AFU ports */
	पूर्णांक i = 0, num_ports = 0;
	पूर्णांक rc = 0;
	पूर्णांक j;
	व्योम *ctx;
	u64 reg;

	rc = पढ़ो_vpd(cfg, &wwpn[0]);
	अगर (rc) अणु
		dev_err(dev, "%s: could not read vpd rc=%d\n", __func__, rc);
		जाओ out;
	पूर्ण

	/* Set up RRQ and SQ in HWQ क्रम master issued cmds */
	क्रम (i = 0; i < afu->num_hwqs; i++) अणु
		hwq = get_hwq(afu, i);
		hmap = hwq->host_map;

		ग_लिखोq_be((u64) hwq->hrrq_start, &hmap->rrq_start);
		ग_लिखोq_be((u64) hwq->hrrq_end, &hmap->rrq_end);
		hwq->hrrq_online = true;

		अगर (afu_is_sq_cmd_mode(afu)) अणु
			ग_लिखोq_be((u64)hwq->hsq_start, &hmap->sq_start);
			ग_लिखोq_be((u64)hwq->hsq_end, &hmap->sq_end);
		पूर्ण
	पूर्ण

	/* AFU configuration */
	reg = पढ़ोq_be(&afu->afu_map->global.regs.afu_config);
	reg |= SISL_AFUCONF_AR_ALL|SISL_AFUCONF_ENDIAN;
	/* enable all स्वतः retry options and control endianness */
	/* leave others at शेष: */
	/* CTX_CAP ग_लिखो रक्षित, mbox_r करोes not clear on पढ़ो and */
	/* checker on अगर dual afu */
	ग_लिखोq_be(reg, &afu->afu_map->global.regs.afu_config);

	/* Global port select: select either port */
	अगर (afu->पूर्णांकernal_lun) अणु
		/* Only use port 0 */
		ग_लिखोq_be(PORT0, &afu->afu_map->global.regs.afu_port_sel);
		num_ports = 0;
	पूर्ण अन्यथा अणु
		ग_लिखोq_be(PORT_MASK(cfg->num_fc_ports),
			  &afu->afu_map->global.regs.afu_port_sel);
		num_ports = cfg->num_fc_ports;
	पूर्ण

	क्रम (i = 0; i < num_ports; i++) अणु
		fc_port_regs = get_fc_port_regs(cfg, i);

		/* Unmask all errors (but they are still masked at AFU) */
		ग_लिखोq_be(0, &fc_port_regs[FC_ERRMSK / 8]);
		/* Clear CRC error cnt & set a threshold */
		(व्योम)पढ़ोq_be(&fc_port_regs[FC_CNT_CRCERR / 8]);
		ग_लिखोq_be(MC_CRC_THRESH, &fc_port_regs[FC_CRC_THRESH / 8]);

		/* Set WWPNs. If alपढ़ोy programmed, wwpn[i] is 0 */
		अगर (wwpn[i] != 0)
			afu_set_wwpn(afu, i, &fc_port_regs[0], wwpn[i]);
		/* Programming WWPN back to back causes additional
		 * offline/online transitions and a PLOGI
		 */
		msleep(100);
	पूर्ण

	अगर (afu_is_ocxl_lisn(afu)) अणु
		/* Set up the LISN effective address क्रम each master */
		क्रम (i = 0; i < afu->num_hwqs; i++) अणु
			hwq = get_hwq(afu, i);
			ctx = hwq->ctx_cookie;

			क्रम (j = 0; j < hwq->num_irqs; j++) अणु
				reg = cfg->ops->get_irq_objhndl(ctx, j);
				ग_लिखोq_be(reg, &hwq->ctrl_map->lisn_ea[j]);
			पूर्ण

			reg = hwq->ctx_hndl;
			ग_लिखोq_be(SISL_LISN_PASID(reg, reg),
				  &hwq->ctrl_map->lisn_pasid[0]);
			ग_लिखोq_be(SISL_LISN_PASID(0UL, reg),
				  &hwq->ctrl_map->lisn_pasid[1]);
		पूर्ण
	पूर्ण

	/* Set up master's own CTX_CAP to allow real mode, host translation */
	/* tables, afu cmds and पढ़ो/ग_लिखो GSCSI cmds. */
	/* First, unlock ctx_cap ग_लिखो by पढ़ोing mbox */
	क्रम (i = 0; i < afu->num_hwqs; i++) अणु
		hwq = get_hwq(afu, i);

		(व्योम)पढ़ोq_be(&hwq->ctrl_map->mbox_r);	/* unlock ctx_cap */
		ग_लिखोq_be((SISL_CTX_CAP_REAL_MODE | SISL_CTX_CAP_HOST_XLATE |
			SISL_CTX_CAP_READ_CMD | SISL_CTX_CAP_WRITE_CMD |
			SISL_CTX_CAP_AFU_CMD | SISL_CTX_CAP_GSCSI_CMD),
			&hwq->ctrl_map->ctx_cap);
	पूर्ण

	/*
	 * Determine ग_लिखो-same unmap support क्रम host by evaluating the unmap
	 * sector support bit of the context control रेजिस्टर associated with
	 * the primary hardware queue. Note that जबतक this status is reflected
	 * in a context रेजिस्टर, the outcome can be assumed to be host-wide.
	 */
	hwq = get_hwq(afu, PRIMARY_HWQ);
	reg = पढ़ोq_be(&hwq->host_map->ctx_ctrl);
	अगर (reg & SISL_CTX_CTRL_UNMAP_SECTOR)
		cfg->ws_unmap = true;

	/* Initialize heartbeat */
	afu->hb = पढ़ोq_be(&afu->afu_map->global.regs.afu_hb);
out:
	वापस rc;
पूर्ण

/**
 * start_afu() - initializes and starts the AFU
 * @cfg:	Internal काष्ठाure associated with the host.
 */
अटल पूर्णांक start_afu(काष्ठा cxlflash_cfg *cfg)
अणु
	काष्ठा afu *afu = cfg->afu;
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा hwq *hwq;
	पूर्णांक rc = 0;
	पूर्णांक i;

	init_pcr(cfg);

	/* Initialize each HWQ */
	क्रम (i = 0; i < afu->num_hwqs; i++) अणु
		hwq = get_hwq(afu, i);

		/* After an AFU reset, RRQ entries are stale, clear them */
		स_रखो(&hwq->rrq_entry, 0, माप(hwq->rrq_entry));

		/* Initialize RRQ poपूर्णांकers */
		hwq->hrrq_start = &hwq->rrq_entry[0];
		hwq->hrrq_end = &hwq->rrq_entry[NUM_RRQ_ENTRY - 1];
		hwq->hrrq_curr = hwq->hrrq_start;
		hwq->toggle = 1;

		/* Initialize spin locks */
		spin_lock_init(&hwq->hrrq_slock);
		spin_lock_init(&hwq->hsq_slock);

		/* Initialize SQ */
		अगर (afu_is_sq_cmd_mode(afu)) अणु
			स_रखो(&hwq->sq, 0, माप(hwq->sq));
			hwq->hsq_start = &hwq->sq[0];
			hwq->hsq_end = &hwq->sq[NUM_SQ_ENTRY - 1];
			hwq->hsq_curr = hwq->hsq_start;

			atomic_set(&hwq->hsq_credits, NUM_SQ_ENTRY - 1);
		पूर्ण

		/* Initialize IRQ poll */
		अगर (afu_is_irqpoll_enabled(afu))
			irq_poll_init(&hwq->irqpoll, afu->irqpoll_weight,
				      cxlflash_irqpoll);

	पूर्ण

	rc = init_global(cfg);

	dev_dbg(dev, "%s: returning rc=%d\n", __func__, rc);
	वापस rc;
पूर्ण

/**
 * init_पूर्णांकr() - setup पूर्णांकerrupt handlers क्रम the master context
 * @cfg:	Internal काष्ठाure associated with the host.
 * @hwq:	Hardware queue to initialize.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल क्रमागत unकरो_level init_पूर्णांकr(काष्ठा cxlflash_cfg *cfg,
				 काष्ठा hwq *hwq)
अणु
	काष्ठा device *dev = &cfg->dev->dev;
	व्योम *ctx = hwq->ctx_cookie;
	पूर्णांक rc = 0;
	क्रमागत unकरो_level level = UNDO_NOOP;
	bool is_primary_hwq = (hwq->index == PRIMARY_HWQ);
	पूर्णांक num_irqs = hwq->num_irqs;

	rc = cfg->ops->allocate_afu_irqs(ctx, num_irqs);
	अगर (unlikely(rc)) अणु
		dev_err(dev, "%s: allocate_afu_irqs failed rc=%d\n",
			__func__, rc);
		level = UNDO_NOOP;
		जाओ out;
	पूर्ण

	rc = cfg->ops->map_afu_irq(ctx, 1, cxlflash_sync_err_irq, hwq,
				   "SISL_MSI_SYNC_ERROR");
	अगर (unlikely(rc <= 0)) अणु
		dev_err(dev, "%s: SISL_MSI_SYNC_ERROR map failed\n", __func__);
		level = FREE_IRQ;
		जाओ out;
	पूर्ण

	rc = cfg->ops->map_afu_irq(ctx, 2, cxlflash_rrq_irq, hwq,
				   "SISL_MSI_RRQ_UPDATED");
	अगर (unlikely(rc <= 0)) अणु
		dev_err(dev, "%s: SISL_MSI_RRQ_UPDATED map failed\n", __func__);
		level = UNMAP_ONE;
		जाओ out;
	पूर्ण

	/* SISL_MSI_ASYNC_ERROR is setup only क्रम the primary HWQ */
	अगर (!is_primary_hwq)
		जाओ out;

	rc = cfg->ops->map_afu_irq(ctx, 3, cxlflash_async_err_irq, hwq,
				   "SISL_MSI_ASYNC_ERROR");
	अगर (unlikely(rc <= 0)) अणु
		dev_err(dev, "%s: SISL_MSI_ASYNC_ERROR map failed\n", __func__);
		level = UNMAP_TWO;
		जाओ out;
	पूर्ण
out:
	वापस level;
पूर्ण

/**
 * init_mc() - create and रेजिस्टर as the master context
 * @cfg:	Internal काष्ठाure associated with the host.
 * @index:	HWQ Index of the master context.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक init_mc(काष्ठा cxlflash_cfg *cfg, u32 index)
अणु
	व्योम *ctx;
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा hwq *hwq = get_hwq(cfg->afu, index);
	पूर्णांक rc = 0;
	पूर्णांक num_irqs;
	क्रमागत unकरो_level level;

	hwq->afu = cfg->afu;
	hwq->index = index;
	INIT_LIST_HEAD(&hwq->pending_cmds);

	अगर (index == PRIMARY_HWQ) अणु
		ctx = cfg->ops->get_context(cfg->dev, cfg->afu_cookie);
		num_irqs = 3;
	पूर्ण अन्यथा अणु
		ctx = cfg->ops->dev_context_init(cfg->dev, cfg->afu_cookie);
		num_irqs = 2;
	पूर्ण
	अगर (IS_ERR_OR_शून्य(ctx)) अणु
		rc = -ENOMEM;
		जाओ err1;
	पूर्ण

	WARN_ON(hwq->ctx_cookie);
	hwq->ctx_cookie = ctx;
	hwq->num_irqs = num_irqs;

	/* Set it up as a master with the CXL */
	cfg->ops->set_master(ctx);

	/* Reset AFU when initializing primary context */
	अगर (index == PRIMARY_HWQ) अणु
		rc = cfg->ops->afu_reset(ctx);
		अगर (unlikely(rc)) अणु
			dev_err(dev, "%s: AFU reset failed rc=%d\n",
				      __func__, rc);
			जाओ err1;
		पूर्ण
	पूर्ण

	level = init_पूर्णांकr(cfg, hwq);
	अगर (unlikely(level)) अणु
		dev_err(dev, "%s: interrupt init failed rc=%d\n", __func__, rc);
		जाओ err2;
	पूर्ण

	/* Finally, activate the context by starting it */
	rc = cfg->ops->start_context(hwq->ctx_cookie);
	अगर (unlikely(rc)) अणु
		dev_err(dev, "%s: start context failed rc=%d\n", __func__, rc);
		level = UNMAP_THREE;
		जाओ err2;
	पूर्ण

out:
	dev_dbg(dev, "%s: returning rc=%d\n", __func__, rc);
	वापस rc;
err2:
	term_पूर्णांकr(cfg, level, index);
	अगर (index != PRIMARY_HWQ)
		cfg->ops->release_context(ctx);
err1:
	hwq->ctx_cookie = शून्य;
	जाओ out;
पूर्ण

/**
 * get_num_afu_ports() - determines and configures the number of AFU ports
 * @cfg:	Internal काष्ठाure associated with the host.
 *
 * This routine determines the number of AFU ports by converting the global
 * port selection mask. The converted value is only valid following an AFU
 * reset (explicit or घातer-on). This routine must be invoked लघुly after
 * mapping as other routines are dependent on the number of ports during the
 * initialization sequence.
 *
 * To support legacy AFUs that might not have reflected an initial global
 * port mask (value पढ़ो is 0), शेष to the number of ports originally
 * supported by the cxlflash driver (2) beक्रमe hardware with other port
 * offerings was पूर्णांकroduced.
 */
अटल व्योम get_num_afu_ports(काष्ठा cxlflash_cfg *cfg)
अणु
	काष्ठा afu *afu = cfg->afu;
	काष्ठा device *dev = &cfg->dev->dev;
	u64 port_mask;
	पूर्णांक num_fc_ports = LEGACY_FC_PORTS;

	port_mask = पढ़ोq_be(&afu->afu_map->global.regs.afu_port_sel);
	अगर (port_mask != 0ULL)
		num_fc_ports = min(ilog2(port_mask) + 1, MAX_FC_PORTS);

	dev_dbg(dev, "%s: port_mask=%016llx num_fc_ports=%d\n",
		__func__, port_mask, num_fc_ports);

	cfg->num_fc_ports = num_fc_ports;
	cfg->host->max_channel = PORTNUM2CHAN(num_fc_ports);
पूर्ण

/**
 * init_afu() - setup as master context and start AFU
 * @cfg:	Internal काष्ठाure associated with the host.
 *
 * This routine is a higher level of control क्रम configuring the
 * AFU on probe and reset paths.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक init_afu(काष्ठा cxlflash_cfg *cfg)
अणु
	u64 reg;
	पूर्णांक rc = 0;
	काष्ठा afu *afu = cfg->afu;
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा hwq *hwq;
	पूर्णांक i;

	cfg->ops->perst_reloads_same_image(cfg->afu_cookie, true);

	mutex_init(&afu->sync_active);
	afu->num_hwqs = afu->desired_hwqs;
	क्रम (i = 0; i < afu->num_hwqs; i++) अणु
		rc = init_mc(cfg, i);
		अगर (rc) अणु
			dev_err(dev, "%s: init_mc failed rc=%d index=%d\n",
				__func__, rc, i);
			जाओ err1;
		पूर्ण
	पूर्ण

	/* Map the entire MMIO space of the AFU using the first context */
	hwq = get_hwq(afu, PRIMARY_HWQ);
	afu->afu_map = cfg->ops->psa_map(hwq->ctx_cookie);
	अगर (!afu->afu_map) अणु
		dev_err(dev, "%s: psa_map failed\n", __func__);
		rc = -ENOMEM;
		जाओ err1;
	पूर्ण

	/* No byte reverse on पढ़ोing afu_version or string will be backwards */
	reg = पढ़ोq(&afu->afu_map->global.regs.afu_version);
	स_नकल(afu->version, &reg, माप(reg));
	afu->पूर्णांकerface_version =
	    पढ़ोq_be(&afu->afu_map->global.regs.पूर्णांकerface_version);
	अगर ((afu->पूर्णांकerface_version + 1) == 0) अणु
		dev_err(dev, "Back level AFU, please upgrade. AFU version %s "
			"interface version %016llx\n", afu->version,
		       afu->पूर्णांकerface_version);
		rc = -EINVAL;
		जाओ err1;
	पूर्ण

	अगर (afu_is_sq_cmd_mode(afu)) अणु
		afu->send_cmd = send_cmd_sq;
		afu->context_reset = context_reset_sq;
	पूर्ण अन्यथा अणु
		afu->send_cmd = send_cmd_ioarrin;
		afu->context_reset = context_reset_ioarrin;
	पूर्ण

	dev_dbg(dev, "%s: afu_ver=%s interface_ver=%016llx\n", __func__,
		afu->version, afu->पूर्णांकerface_version);

	get_num_afu_ports(cfg);

	rc = start_afu(cfg);
	अगर (rc) अणु
		dev_err(dev, "%s: start_afu failed, rc=%d\n", __func__, rc);
		जाओ err1;
	पूर्ण

	afu_err_पूर्णांकr_init(cfg->afu);
	क्रम (i = 0; i < afu->num_hwqs; i++) अणु
		hwq = get_hwq(afu, i);

		hwq->room = पढ़ोq_be(&hwq->host_map->cmd_room);
	पूर्ण

	/* Restore the LUN mappings */
	cxlflash_restore_luntable(cfg);
out:
	dev_dbg(dev, "%s: returning rc=%d\n", __func__, rc);
	वापस rc;

err1:
	क्रम (i = afu->num_hwqs - 1; i >= 0; i--) अणु
		term_पूर्णांकr(cfg, UNMAP_THREE, i);
		term_mc(cfg, i);
	पूर्ण
	जाओ out;
पूर्ण

/**
 * afu_reset() - resets the AFU
 * @cfg:	Internal काष्ठाure associated with the host.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक afu_reset(काष्ठा cxlflash_cfg *cfg)
अणु
	काष्ठा device *dev = &cfg->dev->dev;
	पूर्णांक rc = 0;

	/* Stop the context beक्रमe the reset. Since the context is
	 * no दीर्घer available restart it after the reset is complete
	 */
	term_afu(cfg);

	rc = init_afu(cfg);

	dev_dbg(dev, "%s: returning rc=%d\n", __func__, rc);
	वापस rc;
पूर्ण

/**
 * drain_ioctls() - रुको until all currently executing ioctls have completed
 * @cfg:	Internal काष्ठाure associated with the host.
 *
 * Obtain ग_लिखो access to पढ़ो/ग_लिखो semaphore that wraps ioctl
 * handling to 'drain' ioctls currently executing.
 */
अटल व्योम drain_ioctls(काष्ठा cxlflash_cfg *cfg)
अणु
	करोwn_ग_लिखो(&cfg->ioctl_rwsem);
	up_ग_लिखो(&cfg->ioctl_rwsem);
पूर्ण

/**
 * cxlflash_async_reset_host() - asynchronous host reset handler
 * @data:	Private data provided जबतक scheduling reset.
 * @cookie:	Cookie that can be used क्रम checkpoपूर्णांकing.
 */
अटल व्योम cxlflash_async_reset_host(व्योम *data, async_cookie_t cookie)
अणु
	काष्ठा cxlflash_cfg *cfg = data;
	काष्ठा device *dev = &cfg->dev->dev;
	पूर्णांक rc = 0;

	अगर (cfg->state != STATE_RESET) अणु
		dev_dbg(dev, "%s: Not performing a reset, state=%d\n",
			__func__, cfg->state);
		जाओ out;
	पूर्ण

	drain_ioctls(cfg);
	cxlflash_mark_contexts_error(cfg);
	rc = afu_reset(cfg);
	अगर (rc)
		cfg->state = STATE_FAILTERM;
	अन्यथा
		cfg->state = STATE_NORMAL;
	wake_up_all(&cfg->reset_रुकोq);

out:
	scsi_unblock_requests(cfg->host);
पूर्ण

/**
 * cxlflash_schedule_async_reset() - schedule an asynchronous host reset
 * @cfg:	Internal काष्ठाure associated with the host.
 */
अटल व्योम cxlflash_schedule_async_reset(काष्ठा cxlflash_cfg *cfg)
अणु
	काष्ठा device *dev = &cfg->dev->dev;

	अगर (cfg->state != STATE_NORMAL) अणु
		dev_dbg(dev, "%s: Not performing reset state=%d\n",
			__func__, cfg->state);
		वापस;
	पूर्ण

	cfg->state = STATE_RESET;
	scsi_block_requests(cfg->host);
	cfg->async_reset_cookie = async_schedule(cxlflash_async_reset_host,
						 cfg);
पूर्ण

/**
 * send_afu_cmd() - builds and sends an पूर्णांकernal AFU command
 * @afu:	AFU associated with the host.
 * @rcb:	Pre-populated IOARCB describing command to send.
 *
 * The AFU can only take one पूर्णांकernal AFU command at a समय. This limitation is
 * enक्रमced by using a mutex to provide exclusive access to the AFU during the
 * operation. This design poपूर्णांक requires calling thपढ़ोs to not be on पूर्णांकerrupt
 * context due to the possibility of sleeping during concurrent AFU operations.
 *
 * The command status is optionally passed back to the caller when the caller
 * populates the IOASA field of the IOARCB with a poपूर्णांकer to an IOASA काष्ठाure.
 *
 * Return:
 *	0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक send_afu_cmd(काष्ठा afu *afu, काष्ठा sisl_ioarcb *rcb)
अणु
	काष्ठा cxlflash_cfg *cfg = afu->parent;
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा afu_cmd *cmd = शून्य;
	काष्ठा hwq *hwq = get_hwq(afu, PRIMARY_HWQ);
	uदीर्घ lock_flags;
	अक्षर *buf = शून्य;
	पूर्णांक rc = 0;
	पूर्णांक nretry = 0;

	अगर (cfg->state != STATE_NORMAL) अणु
		dev_dbg(dev, "%s: Sync not required state=%u\n",
			__func__, cfg->state);
		वापस 0;
	पूर्ण

	mutex_lock(&afu->sync_active);
	atomic_inc(&afu->cmds_active);
	buf = kदो_स्मृति(माप(*cmd) + __alignof__(*cmd) - 1, GFP_KERNEL);
	अगर (unlikely(!buf)) अणु
		dev_err(dev, "%s: no memory for command\n", __func__);
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	cmd = (काष्ठा afu_cmd *)PTR_ALIGN(buf, __alignof__(*cmd));

retry:
	स_रखो(cmd, 0, माप(*cmd));
	स_नकल(&cmd->rcb, rcb, माप(*rcb));
	INIT_LIST_HEAD(&cmd->queue);
	init_completion(&cmd->cevent);
	cmd->parent = afu;
	cmd->hwq_index = hwq->index;
	cmd->rcb.ctx_id = hwq->ctx_hndl;

	dev_dbg(dev, "%s: afu=%p cmd=%p type=%02x nretry=%d\n",
		__func__, afu, cmd, cmd->rcb.cdb[0], nretry);

	rc = afu->send_cmd(afu, cmd);
	अगर (unlikely(rc)) अणु
		rc = -ENOBUFS;
		जाओ out;
	पूर्ण

	rc = रुको_resp(afu, cmd);
	चयन (rc) अणु
	हाल -ETIMEDOUT:
		rc = afu->context_reset(hwq);
		अगर (rc) अणु
			/* Delete the command from pending_cmds list */
			spin_lock_irqsave(&hwq->hsq_slock, lock_flags);
			list_del(&cmd->list);
			spin_unlock_irqrestore(&hwq->hsq_slock, lock_flags);

			cxlflash_schedule_async_reset(cfg);
			अवरोध;
		पूर्ण
		fallthrough;	/* to retry */
	हाल -EAGAIN:
		अगर (++nretry < 2)
			जाओ retry;
		fallthrough;	/* to निकास */
	शेष:
		अवरोध;
	पूर्ण

	अगर (rcb->ioasa)
		*rcb->ioasa = cmd->sa;
out:
	atomic_dec(&afu->cmds_active);
	mutex_unlock(&afu->sync_active);
	kमुक्त(buf);
	dev_dbg(dev, "%s: returning rc=%d\n", __func__, rc);
	वापस rc;
पूर्ण

/**
 * cxlflash_afu_sync() - builds and sends an AFU sync command
 * @afu:	AFU associated with the host.
 * @ctx:	Identअगरies context requesting sync.
 * @res:	Identअगरies resource requesting sync.
 * @mode:	Type of sync to issue (lightweight, heavyweight, global).
 *
 * AFU sync operations are only necessary and allowed when the device is
 * operating normally. When not operating normally, sync requests can occur as
 * part of cleaning up resources associated with an adapter prior to removal.
 * In this scenario, these requests are simply ignored (safe due to the AFU
 * going away).
 *
 * Return:
 *	0 on success, -त्रुटि_सं on failure
 */
पूर्णांक cxlflash_afu_sync(काष्ठा afu *afu, ctx_hndl_t ctx, res_hndl_t res, u8 mode)
अणु
	काष्ठा cxlflash_cfg *cfg = afu->parent;
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा sisl_ioarcb rcb = अणु 0 पूर्ण;

	dev_dbg(dev, "%s: afu=%p ctx=%u res=%u mode=%u\n",
		__func__, afu, ctx, res, mode);

	rcb.req_flags = SISL_REQ_FLAGS_AFU_CMD;
	rcb.msi = SISL_MSI_RRQ_UPDATED;
	rcb.समयout = MC_AFU_SYNC_TIMEOUT;

	rcb.cdb[0] = SISL_AFU_CMD_SYNC;
	rcb.cdb[1] = mode;
	put_unaligned_be16(ctx, &rcb.cdb[2]);
	put_unaligned_be32(res, &rcb.cdb[4]);

	वापस send_afu_cmd(afu, &rcb);
पूर्ण

/**
 * cxlflash_eh_पात_handler() - पात a SCSI command
 * @scp:	SCSI command to पात.
 *
 * CXL Flash devices करो not support a single command पात. Reset the context
 * as per SISLite specअगरication. Flush any pending commands in the hardware
 * queue beक्रमe the reset.
 *
 * Return: SUCCESS/FAILED as defined in scsi/scsi.h
 */
अटल पूर्णांक cxlflash_eh_पात_handler(काष्ठा scsi_cmnd *scp)
अणु
	पूर्णांक rc = FAILED;
	काष्ठा Scsi_Host *host = scp->device->host;
	काष्ठा cxlflash_cfg *cfg = shost_priv(host);
	काष्ठा afu_cmd *cmd = sc_to_afuc(scp);
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा afu *afu = cfg->afu;
	काष्ठा hwq *hwq = get_hwq(afu, cmd->hwq_index);

	dev_dbg(dev, "%s: (scp=%p) %d/%d/%d/%llu "
		"cdb=(%08x-%08x-%08x-%08x)\n", __func__, scp, host->host_no,
		scp->device->channel, scp->device->id, scp->device->lun,
		get_unaligned_be32(&((u32 *)scp->cmnd)[0]),
		get_unaligned_be32(&((u32 *)scp->cmnd)[1]),
		get_unaligned_be32(&((u32 *)scp->cmnd)[2]),
		get_unaligned_be32(&((u32 *)scp->cmnd)[3]));

	/* When the state is not normal, another reset/reload is in progress.
	 * Return failed and the mid-layer will invoke host reset handler.
	 */
	अगर (cfg->state != STATE_NORMAL) अणु
		dev_dbg(dev, "%s: Invalid state for abort, state=%d\n",
			__func__, cfg->state);
		जाओ out;
	पूर्ण

	rc = afu->context_reset(hwq);
	अगर (unlikely(rc))
		जाओ out;

	rc = SUCCESS;

out:
	dev_dbg(dev, "%s: returning rc=%d\n", __func__, rc);
	वापस rc;
पूर्ण

/**
 * cxlflash_eh_device_reset_handler() - reset a single LUN
 * @scp:	SCSI command to send.
 *
 * Return:
 *	SUCCESS as defined in scsi/scsi.h
 *	FAILED as defined in scsi/scsi.h
 */
अटल पूर्णांक cxlflash_eh_device_reset_handler(काष्ठा scsi_cmnd *scp)
अणु
	पूर्णांक rc = SUCCESS;
	काष्ठा scsi_device *sdev = scp->device;
	काष्ठा Scsi_Host *host = sdev->host;
	काष्ठा cxlflash_cfg *cfg = shost_priv(host);
	काष्ठा device *dev = &cfg->dev->dev;
	पूर्णांक rcr = 0;

	dev_dbg(dev, "%s: %d/%d/%d/%llu\n", __func__,
		host->host_no, sdev->channel, sdev->id, sdev->lun);
retry:
	चयन (cfg->state) अणु
	हाल STATE_NORMAL:
		rcr = send_पंचांगf(cfg, sdev, TMF_LUN_RESET);
		अगर (unlikely(rcr))
			rc = FAILED;
		अवरोध;
	हाल STATE_RESET:
		रुको_event(cfg->reset_रुकोq, cfg->state != STATE_RESET);
		जाओ retry;
	शेष:
		rc = FAILED;
		अवरोध;
	पूर्ण

	dev_dbg(dev, "%s: returning rc=%d\n", __func__, rc);
	वापस rc;
पूर्ण

/**
 * cxlflash_eh_host_reset_handler() - reset the host adapter
 * @scp:	SCSI command from stack identअगरying host.
 *
 * Following a reset, the state is evaluated again in हाल an EEH occurred
 * during the reset. In such a scenario, the host reset will either yield
 * until the EEH recovery is complete or वापस success or failure based
 * upon the current device state.
 *
 * Return:
 *	SUCCESS as defined in scsi/scsi.h
 *	FAILED as defined in scsi/scsi.h
 */
अटल पूर्णांक cxlflash_eh_host_reset_handler(काष्ठा scsi_cmnd *scp)
अणु
	पूर्णांक rc = SUCCESS;
	पूर्णांक rcr = 0;
	काष्ठा Scsi_Host *host = scp->device->host;
	काष्ठा cxlflash_cfg *cfg = shost_priv(host);
	काष्ठा device *dev = &cfg->dev->dev;

	dev_dbg(dev, "%s: %d\n", __func__, host->host_no);

	चयन (cfg->state) अणु
	हाल STATE_NORMAL:
		cfg->state = STATE_RESET;
		drain_ioctls(cfg);
		cxlflash_mark_contexts_error(cfg);
		rcr = afu_reset(cfg);
		अगर (rcr) अणु
			rc = FAILED;
			cfg->state = STATE_FAILTERM;
		पूर्ण अन्यथा
			cfg->state = STATE_NORMAL;
		wake_up_all(&cfg->reset_रुकोq);
		ssleep(1);
		fallthrough;
	हाल STATE_RESET:
		रुको_event(cfg->reset_रुकोq, cfg->state != STATE_RESET);
		अगर (cfg->state == STATE_NORMAL)
			अवरोध;
		fallthrough;
	शेष:
		rc = FAILED;
		अवरोध;
	पूर्ण

	dev_dbg(dev, "%s: returning rc=%d\n", __func__, rc);
	वापस rc;
पूर्ण

/**
 * cxlflash_change_queue_depth() - change the queue depth क्रम the device
 * @sdev:	SCSI device destined क्रम queue depth change.
 * @qdepth:	Requested queue depth value to set.
 *
 * The requested queue depth is capped to the maximum supported value.
 *
 * Return: The actual queue depth set.
 */
अटल पूर्णांक cxlflash_change_queue_depth(काष्ठा scsi_device *sdev, पूर्णांक qdepth)
अणु

	अगर (qdepth > CXLFLASH_MAX_CMDS_PER_LUN)
		qdepth = CXLFLASH_MAX_CMDS_PER_LUN;

	scsi_change_queue_depth(sdev, qdepth);
	वापस sdev->queue_depth;
पूर्ण

/**
 * cxlflash_show_port_status() - queries and presents the current port status
 * @port:	Desired port क्रम status reporting.
 * @cfg:	Internal काष्ठाure associated with the host.
 * @buf:	Buffer of length PAGE_SIZE to report back port status in ASCII.
 *
 * Return: The size of the ASCII string वापसed in @buf or -EINVAL.
 */
अटल sमाप_प्रकार cxlflash_show_port_status(u32 port,
					 काष्ठा cxlflash_cfg *cfg,
					 अक्षर *buf)
अणु
	काष्ठा device *dev = &cfg->dev->dev;
	अक्षर *disp_status;
	u64 status;
	__be64 __iomem *fc_port_regs;

	WARN_ON(port >= MAX_FC_PORTS);

	अगर (port >= cfg->num_fc_ports) अणु
		dev_info(dev, "%s: Port %d not supported on this card.\n",
			__func__, port);
		वापस -EINVAL;
	पूर्ण

	fc_port_regs = get_fc_port_regs(cfg, port);
	status = पढ़ोq_be(&fc_port_regs[FC_MTIP_STATUS / 8]);
	status &= FC_MTIP_STATUS_MASK;

	अगर (status == FC_MTIP_STATUS_ONLINE)
		disp_status = "online";
	अन्यथा अगर (status == FC_MTIP_STATUS_OFFLINE)
		disp_status = "offline";
	अन्यथा
		disp_status = "unknown";

	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", disp_status);
पूर्ण

/**
 * port0_show() - queries and presents the current status of port 0
 * @dev:	Generic device associated with the host owning the port.
 * @attr:	Device attribute representing the port.
 * @buf:	Buffer of length PAGE_SIZE to report back port status in ASCII.
 *
 * Return: The size of the ASCII string वापसed in @buf.
 */
अटल sमाप_प्रकार port0_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा cxlflash_cfg *cfg = shost_priv(class_to_shost(dev));

	वापस cxlflash_show_port_status(0, cfg, buf);
पूर्ण

/**
 * port1_show() - queries and presents the current status of port 1
 * @dev:	Generic device associated with the host owning the port.
 * @attr:	Device attribute representing the port.
 * @buf:	Buffer of length PAGE_SIZE to report back port status in ASCII.
 *
 * Return: The size of the ASCII string वापसed in @buf.
 */
अटल sमाप_प्रकार port1_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा cxlflash_cfg *cfg = shost_priv(class_to_shost(dev));

	वापस cxlflash_show_port_status(1, cfg, buf);
पूर्ण

/**
 * port2_show() - queries and presents the current status of port 2
 * @dev:	Generic device associated with the host owning the port.
 * @attr:	Device attribute representing the port.
 * @buf:	Buffer of length PAGE_SIZE to report back port status in ASCII.
 *
 * Return: The size of the ASCII string वापसed in @buf.
 */
अटल sमाप_प्रकार port2_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा cxlflash_cfg *cfg = shost_priv(class_to_shost(dev));

	वापस cxlflash_show_port_status(2, cfg, buf);
पूर्ण

/**
 * port3_show() - queries and presents the current status of port 3
 * @dev:	Generic device associated with the host owning the port.
 * @attr:	Device attribute representing the port.
 * @buf:	Buffer of length PAGE_SIZE to report back port status in ASCII.
 *
 * Return: The size of the ASCII string वापसed in @buf.
 */
अटल sमाप_प्रकार port3_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा cxlflash_cfg *cfg = shost_priv(class_to_shost(dev));

	वापस cxlflash_show_port_status(3, cfg, buf);
पूर्ण

/**
 * lun_mode_show() - presents the current LUN mode of the host
 * @dev:	Generic device associated with the host.
 * @attr:	Device attribute representing the LUN mode.
 * @buf:	Buffer of length PAGE_SIZE to report back the LUN mode in ASCII.
 *
 * Return: The size of the ASCII string वापसed in @buf.
 */
अटल sमाप_प्रकार lun_mode_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा cxlflash_cfg *cfg = shost_priv(class_to_shost(dev));
	काष्ठा afu *afu = cfg->afu;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", afu->पूर्णांकernal_lun);
पूर्ण

/**
 * lun_mode_store() - sets the LUN mode of the host
 * @dev:	Generic device associated with the host.
 * @attr:	Device attribute representing the LUN mode.
 * @buf:	Buffer of length PAGE_SIZE containing the LUN mode in ASCII.
 * @count:	Length of data resizing in @buf.
 *
 * The CXL Flash AFU supports a dummy LUN mode where the बाह्यal
 * links and storage are not required. Space on the FPGA is used
 * to create 1 or 2 small LUNs which are presented to the प्रणाली
 * as अगर they were a normal storage device. This feature is useful
 * during development and also provides manufacturing with a way
 * to test the AFU without an actual device.
 *
 * 0 = बाह्यal LUN[s] (शेष)
 * 1 = पूर्णांकernal LUN (1 x 64K, 512B blocks, id 0)
 * 2 = पूर्णांकernal LUN (1 x 64K, 4K blocks, id 0)
 * 3 = पूर्णांकernal LUN (2 x 32K, 512B blocks, ids 0,1)
 * 4 = पूर्णांकernal LUN (2 x 32K, 4K blocks, ids 0,1)
 *
 * Return: The size of the ASCII string वापसed in @buf.
 */
अटल sमाप_प्रकार lun_mode_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा cxlflash_cfg *cfg = shost_priv(shost);
	काष्ठा afu *afu = cfg->afu;
	पूर्णांक rc;
	u32 lun_mode;

	rc = kstrtouपूर्णांक(buf, 10, &lun_mode);
	अगर (!rc && (lun_mode < 5) && (lun_mode != afu->पूर्णांकernal_lun)) अणु
		afu->पूर्णांकernal_lun = lun_mode;

		/*
		 * When configured क्रम पूर्णांकernal LUN, there is only one channel,
		 * channel number 0, अन्यथा there will be one less than the number
		 * of fc ports क्रम this card.
		 */
		अगर (afu->पूर्णांकernal_lun)
			shost->max_channel = 0;
		अन्यथा
			shost->max_channel = PORTNUM2CHAN(cfg->num_fc_ports);

		afu_reset(cfg);
		scsi_scan_host(cfg->host);
	पूर्ण

	वापस count;
पूर्ण

/**
 * ioctl_version_show() - presents the current ioctl version of the host
 * @dev:	Generic device associated with the host.
 * @attr:	Device attribute representing the ioctl version.
 * @buf:	Buffer of length PAGE_SIZE to report back the ioctl version.
 *
 * Return: The size of the ASCII string वापसed in @buf.
 */
अटल sमाप_प्रकार ioctl_version_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	sमाप_प्रकार bytes = 0;

	bytes = scnम_लिखो(buf, PAGE_SIZE,
			  "disk: %u\n", DK_CXLFLASH_VERSION_0);
	bytes += scnम_लिखो(buf + bytes, PAGE_SIZE - bytes,
			   "host: %u\n", HT_CXLFLASH_VERSION_0);

	वापस bytes;
पूर्ण

/**
 * cxlflash_show_port_lun_table() - queries and presents the port LUN table
 * @port:	Desired port क्रम status reporting.
 * @cfg:	Internal काष्ठाure associated with the host.
 * @buf:	Buffer of length PAGE_SIZE to report back port status in ASCII.
 *
 * Return: The size of the ASCII string वापसed in @buf or -EINVAL.
 */
अटल sमाप_प्रकार cxlflash_show_port_lun_table(u32 port,
					    काष्ठा cxlflash_cfg *cfg,
					    अक्षर *buf)
अणु
	काष्ठा device *dev = &cfg->dev->dev;
	__be64 __iomem *fc_port_luns;
	पूर्णांक i;
	sमाप_प्रकार bytes = 0;

	WARN_ON(port >= MAX_FC_PORTS);

	अगर (port >= cfg->num_fc_ports) अणु
		dev_info(dev, "%s: Port %d not supported on this card.\n",
			__func__, port);
		वापस -EINVAL;
	पूर्ण

	fc_port_luns = get_fc_port_luns(cfg, port);

	क्रम (i = 0; i < CXLFLASH_NUM_VLUNS; i++)
		bytes += scnम_लिखो(buf + bytes, PAGE_SIZE - bytes,
				   "%03d: %016llx\n",
				   i, पढ़ोq_be(&fc_port_luns[i]));
	वापस bytes;
पूर्ण

/**
 * port0_lun_table_show() - presents the current LUN table of port 0
 * @dev:	Generic device associated with the host owning the port.
 * @attr:	Device attribute representing the port.
 * @buf:	Buffer of length PAGE_SIZE to report back port status in ASCII.
 *
 * Return: The size of the ASCII string वापसed in @buf.
 */
अटल sमाप_प्रकार port0_lun_table_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा cxlflash_cfg *cfg = shost_priv(class_to_shost(dev));

	वापस cxlflash_show_port_lun_table(0, cfg, buf);
पूर्ण

/**
 * port1_lun_table_show() - presents the current LUN table of port 1
 * @dev:	Generic device associated with the host owning the port.
 * @attr:	Device attribute representing the port.
 * @buf:	Buffer of length PAGE_SIZE to report back port status in ASCII.
 *
 * Return: The size of the ASCII string वापसed in @buf.
 */
अटल sमाप_प्रकार port1_lun_table_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा cxlflash_cfg *cfg = shost_priv(class_to_shost(dev));

	वापस cxlflash_show_port_lun_table(1, cfg, buf);
पूर्ण

/**
 * port2_lun_table_show() - presents the current LUN table of port 2
 * @dev:	Generic device associated with the host owning the port.
 * @attr:	Device attribute representing the port.
 * @buf:	Buffer of length PAGE_SIZE to report back port status in ASCII.
 *
 * Return: The size of the ASCII string वापसed in @buf.
 */
अटल sमाप_प्रकार port2_lun_table_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा cxlflash_cfg *cfg = shost_priv(class_to_shost(dev));

	वापस cxlflash_show_port_lun_table(2, cfg, buf);
पूर्ण

/**
 * port3_lun_table_show() - presents the current LUN table of port 3
 * @dev:	Generic device associated with the host owning the port.
 * @attr:	Device attribute representing the port.
 * @buf:	Buffer of length PAGE_SIZE to report back port status in ASCII.
 *
 * Return: The size of the ASCII string वापसed in @buf.
 */
अटल sमाप_प्रकार port3_lun_table_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा cxlflash_cfg *cfg = shost_priv(class_to_shost(dev));

	वापस cxlflash_show_port_lun_table(3, cfg, buf);
पूर्ण

/**
 * irqpoll_weight_show() - presents the current IRQ poll weight क्रम the host
 * @dev:	Generic device associated with the host.
 * @attr:	Device attribute representing the IRQ poll weight.
 * @buf:	Buffer of length PAGE_SIZE to report back the current IRQ poll
 *		weight in ASCII.
 *
 * An IRQ poll weight of 0 indicates polling is disabled.
 *
 * Return: The size of the ASCII string वापसed in @buf.
 */
अटल sमाप_प्रकार irqpoll_weight_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा cxlflash_cfg *cfg = shost_priv(class_to_shost(dev));
	काष्ठा afu *afu = cfg->afu;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", afu->irqpoll_weight);
पूर्ण

/**
 * irqpoll_weight_store() - sets the current IRQ poll weight क्रम the host
 * @dev:	Generic device associated with the host.
 * @attr:	Device attribute representing the IRQ poll weight.
 * @buf:	Buffer of length PAGE_SIZE containing the desired IRQ poll
 *		weight in ASCII.
 * @count:	Length of data resizing in @buf.
 *
 * An IRQ poll weight of 0 indicates polling is disabled.
 *
 * Return: The size of the ASCII string वापसed in @buf.
 */
अटल sमाप_प्रकार irqpoll_weight_store(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा cxlflash_cfg *cfg = shost_priv(class_to_shost(dev));
	काष्ठा device *cfgdev = &cfg->dev->dev;
	काष्ठा afu *afu = cfg->afu;
	काष्ठा hwq *hwq;
	u32 weight;
	पूर्णांक rc, i;

	rc = kstrtouपूर्णांक(buf, 10, &weight);
	अगर (rc)
		वापस -EINVAL;

	अगर (weight > 256) अणु
		dev_info(cfgdev,
			 "Invalid IRQ poll weight. It must be 256 or less.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (weight == afu->irqpoll_weight) अणु
		dev_info(cfgdev,
			 "Current IRQ poll weight has the same weight.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (afu_is_irqpoll_enabled(afu)) अणु
		क्रम (i = 0; i < afu->num_hwqs; i++) अणु
			hwq = get_hwq(afu, i);

			irq_poll_disable(&hwq->irqpoll);
		पूर्ण
	पूर्ण

	afu->irqpoll_weight = weight;

	अगर (weight > 0) अणु
		क्रम (i = 0; i < afu->num_hwqs; i++) अणु
			hwq = get_hwq(afu, i);

			irq_poll_init(&hwq->irqpoll, weight, cxlflash_irqpoll);
		पूर्ण
	पूर्ण

	वापस count;
पूर्ण

/**
 * num_hwqs_show() - presents the number of hardware queues क्रम the host
 * @dev:	Generic device associated with the host.
 * @attr:	Device attribute representing the number of hardware queues.
 * @buf:	Buffer of length PAGE_SIZE to report back the number of hardware
 *		queues in ASCII.
 *
 * Return: The size of the ASCII string वापसed in @buf.
 */
अटल sमाप_प्रकार num_hwqs_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा cxlflash_cfg *cfg = shost_priv(class_to_shost(dev));
	काष्ठा afu *afu = cfg->afu;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", afu->num_hwqs);
पूर्ण

/**
 * num_hwqs_store() - sets the number of hardware queues क्रम the host
 * @dev:	Generic device associated with the host.
 * @attr:	Device attribute representing the number of hardware queues.
 * @buf:	Buffer of length PAGE_SIZE containing the number of hardware
 *		queues in ASCII.
 * @count:	Length of data resizing in @buf.
 *
 * n > 0: num_hwqs = n
 * n = 0: num_hwqs = num_online_cpus()
 * n < 0: num_online_cpus() / असल(n)
 *
 * Return: The size of the ASCII string वापसed in @buf.
 */
अटल sमाप_प्रकार num_hwqs_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा cxlflash_cfg *cfg = shost_priv(class_to_shost(dev));
	काष्ठा afu *afu = cfg->afu;
	पूर्णांक rc;
	पूर्णांक nhwqs, num_hwqs;

	rc = kstrtoपूर्णांक(buf, 10, &nhwqs);
	अगर (rc)
		वापस -EINVAL;

	अगर (nhwqs >= 1)
		num_hwqs = nhwqs;
	अन्यथा अगर (nhwqs == 0)
		num_hwqs = num_online_cpus();
	अन्यथा
		num_hwqs = num_online_cpus() / असल(nhwqs);

	afu->desired_hwqs = min(num_hwqs, CXLFLASH_MAX_HWQS);
	WARN_ON_ONCE(afu->desired_hwqs == 0);

retry:
	चयन (cfg->state) अणु
	हाल STATE_NORMAL:
		cfg->state = STATE_RESET;
		drain_ioctls(cfg);
		cxlflash_mark_contexts_error(cfg);
		rc = afu_reset(cfg);
		अगर (rc)
			cfg->state = STATE_FAILTERM;
		अन्यथा
			cfg->state = STATE_NORMAL;
		wake_up_all(&cfg->reset_रुकोq);
		अवरोध;
	हाल STATE_RESET:
		रुको_event(cfg->reset_रुकोq, cfg->state != STATE_RESET);
		अगर (cfg->state == STATE_NORMAL)
			जाओ retry;
		fallthrough;
	शेष:
		/* Ideally should not happen */
		dev_err(dev, "%s: Device is not ready, state=%d\n",
			__func__, cfg->state);
		अवरोध;
	पूर्ण

	वापस count;
पूर्ण

अटल स्थिर अक्षर *hwq_mode_name[MAX_HWQ_MODE] = अणु "rr", "tag", "cpu" पूर्ण;

/**
 * hwq_mode_show() - presents the HWQ steering mode क्रम the host
 * @dev:	Generic device associated with the host.
 * @attr:	Device attribute representing the HWQ steering mode.
 * @buf:	Buffer of length PAGE_SIZE to report back the HWQ steering mode
 *		as a अक्षरacter string.
 *
 * Return: The size of the ASCII string वापसed in @buf.
 */
अटल sमाप_प्रकार hwq_mode_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा cxlflash_cfg *cfg = shost_priv(class_to_shost(dev));
	काष्ठा afu *afu = cfg->afu;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", hwq_mode_name[afu->hwq_mode]);
पूर्ण

/**
 * hwq_mode_store() - sets the HWQ steering mode क्रम the host
 * @dev:	Generic device associated with the host.
 * @attr:	Device attribute representing the HWQ steering mode.
 * @buf:	Buffer of length PAGE_SIZE containing the HWQ steering mode
 *		as a अक्षरacter string.
 * @count:	Length of data resizing in @buf.
 *
 * rr = Round-Robin
 * tag = Block MQ Tagging
 * cpu = CPU Affinity
 *
 * Return: The size of the ASCII string वापसed in @buf.
 */
अटल sमाप_प्रकार hwq_mode_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा cxlflash_cfg *cfg = shost_priv(shost);
	काष्ठा device *cfgdev = &cfg->dev->dev;
	काष्ठा afu *afu = cfg->afu;
	पूर्णांक i;
	u32 mode = MAX_HWQ_MODE;

	क्रम (i = 0; i < MAX_HWQ_MODE; i++) अणु
		अगर (!म_भेदन(hwq_mode_name[i], buf, म_माप(hwq_mode_name[i]))) अणु
			mode = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (mode >= MAX_HWQ_MODE) अणु
		dev_info(cfgdev, "Invalid HWQ steering mode.\n");
		वापस -EINVAL;
	पूर्ण

	afu->hwq_mode = mode;

	वापस count;
पूर्ण

/**
 * mode_show() - presents the current mode of the device
 * @dev:	Generic device associated with the device.
 * @attr:	Device attribute representing the device mode.
 * @buf:	Buffer of length PAGE_SIZE to report back the dev mode in ASCII.
 *
 * Return: The size of the ASCII string वापसed in @buf.
 */
अटल sमाप_प्रकार mode_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n",
			 sdev->hostdata ? "superpipe" : "legacy");
पूर्ण

/*
 * Host attributes
 */
अटल DEVICE_ATTR_RO(port0);
अटल DEVICE_ATTR_RO(port1);
अटल DEVICE_ATTR_RO(port2);
अटल DEVICE_ATTR_RO(port3);
अटल DEVICE_ATTR_RW(lun_mode);
अटल DEVICE_ATTR_RO(ioctl_version);
अटल DEVICE_ATTR_RO(port0_lun_table);
अटल DEVICE_ATTR_RO(port1_lun_table);
अटल DEVICE_ATTR_RO(port2_lun_table);
अटल DEVICE_ATTR_RO(port3_lun_table);
अटल DEVICE_ATTR_RW(irqpoll_weight);
अटल DEVICE_ATTR_RW(num_hwqs);
अटल DEVICE_ATTR_RW(hwq_mode);

अटल काष्ठा device_attribute *cxlflash_host_attrs[] = अणु
	&dev_attr_port0,
	&dev_attr_port1,
	&dev_attr_port2,
	&dev_attr_port3,
	&dev_attr_lun_mode,
	&dev_attr_ioctl_version,
	&dev_attr_port0_lun_table,
	&dev_attr_port1_lun_table,
	&dev_attr_port2_lun_table,
	&dev_attr_port3_lun_table,
	&dev_attr_irqpoll_weight,
	&dev_attr_num_hwqs,
	&dev_attr_hwq_mode,
	शून्य
पूर्ण;

/*
 * Device attributes
 */
अटल DEVICE_ATTR_RO(mode);

अटल काष्ठा device_attribute *cxlflash_dev_attrs[] = अणु
	&dev_attr_mode,
	शून्य
पूर्ण;

/*
 * Host ढाँचा
 */
अटल काष्ठा scsi_host_ढाँचा driver_ढाँचा = अणु
	.module = THIS_MODULE,
	.name = CXLFLASH_ADAPTER_NAME,
	.info = cxlflash_driver_info,
	.ioctl = cxlflash_ioctl,
	.proc_name = CXLFLASH_NAME,
	.queuecommand = cxlflash_queuecommand,
	.eh_पात_handler = cxlflash_eh_पात_handler,
	.eh_device_reset_handler = cxlflash_eh_device_reset_handler,
	.eh_host_reset_handler = cxlflash_eh_host_reset_handler,
	.change_queue_depth = cxlflash_change_queue_depth,
	.cmd_per_lun = CXLFLASH_MAX_CMDS_PER_LUN,
	.can_queue = CXLFLASH_MAX_CMDS,
	.cmd_size = माप(काष्ठा afu_cmd) + __alignof__(काष्ठा afu_cmd) - 1,
	.this_id = -1,
	.sg_tablesize = 1,	/* No scatter gather support */
	.max_sectors = CXLFLASH_MAX_SECTORS,
	.shost_attrs = cxlflash_host_attrs,
	.sdev_attrs = cxlflash_dev_attrs,
पूर्ण;

/*
 * Device dependent values
 */
अटल काष्ठा dev_dependent_vals dev_corsa_vals = अणु CXLFLASH_MAX_SECTORS,
					CXLFLASH_WWPN_VPD_REQUIRED पूर्ण;
अटल काष्ठा dev_dependent_vals dev_flash_gt_vals = अणु CXLFLASH_MAX_SECTORS,
					CXLFLASH_NOTIFY_SHUTDOWN पूर्ण;
अटल काष्ठा dev_dependent_vals dev_briard_vals = अणु CXLFLASH_MAX_SECTORS,
					(CXLFLASH_NOTIFY_SHUTDOWN |
					CXLFLASH_OCXL_DEV) पूर्ण;

/*
 * PCI device binding table
 */
अटल काष्ठा pci_device_id cxlflash_pci_table[] = अणु
	अणुPCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_CORSA,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, (kernel_uदीर्घ_t)&dev_corsa_valsपूर्ण,
	अणुPCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_FLASH_GT,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, (kernel_uदीर्घ_t)&dev_flash_gt_valsपूर्ण,
	अणुPCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_BRIARD,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, (kernel_uदीर्घ_t)&dev_briard_valsपूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, cxlflash_pci_table);

/**
 * cxlflash_worker_thपढ़ो() - work thपढ़ो handler क्रम the AFU
 * @work:	Work काष्ठाure contained within cxlflash associated with host.
 *
 * Handles the following events:
 * - Link reset which cannot be perक्रमmed on पूर्णांकerrupt context due to
 * blocking up to a few seconds
 * - Rescan the host
 */
अटल व्योम cxlflash_worker_thपढ़ो(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cxlflash_cfg *cfg = container_of(work, काष्ठा cxlflash_cfg,
						work_q);
	काष्ठा afu *afu = cfg->afu;
	काष्ठा device *dev = &cfg->dev->dev;
	__be64 __iomem *fc_port_regs;
	पूर्णांक port;
	uदीर्घ lock_flags;

	/* Aव्योम MMIO अगर the device has failed */

	अगर (cfg->state != STATE_NORMAL)
		वापस;

	spin_lock_irqsave(cfg->host->host_lock, lock_flags);

	अगर (cfg->lr_state == LINK_RESET_REQUIRED) अणु
		port = cfg->lr_port;
		अगर (port < 0)
			dev_err(dev, "%s: invalid port index %d\n",
				__func__, port);
		अन्यथा अणु
			spin_unlock_irqrestore(cfg->host->host_lock,
					       lock_flags);

			/* The reset can block... */
			fc_port_regs = get_fc_port_regs(cfg, port);
			afu_link_reset(afu, port, fc_port_regs);
			spin_lock_irqsave(cfg->host->host_lock, lock_flags);
		पूर्ण

		cfg->lr_state = LINK_RESET_COMPLETE;
	पूर्ण

	spin_unlock_irqrestore(cfg->host->host_lock, lock_flags);

	अगर (atomic_dec_अगर_positive(&cfg->scan_host_needed) >= 0)
		scsi_scan_host(cfg->host);
पूर्ण

/**
 * cxlflash_chr_खोलो() - अक्षरacter device खोलो handler
 * @inode:	Device inode associated with this अक्षरacter device.
 * @file:	File poपूर्णांकer क्रम this device.
 *
 * Only users with admin privileges are allowed to खोलो the अक्षरacter device.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक cxlflash_chr_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा cxlflash_cfg *cfg;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EACCES;

	cfg = container_of(inode->i_cdev, काष्ठा cxlflash_cfg, cdev);
	file->निजी_data = cfg;

	वापस 0;
पूर्ण

/**
 * decode_hioctl() - translates encoded host ioctl to easily identअगरiable string
 * @cmd:        The host ioctl command to decode.
 *
 * Return: A string identअगरying the decoded host ioctl.
 */
अटल अक्षर *decode_hioctl(अचिन्हित पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	हाल HT_CXLFLASH_LUN_PROVISION:
		वापस __stringअगरy_1(HT_CXLFLASH_LUN_PROVISION);
	पूर्ण

	वापस "UNKNOWN";
पूर्ण

/**
 * cxlflash_lun_provision() - host LUN provisioning handler
 * @cfg:	Internal काष्ठाure associated with the host.
 * @lunprov:	Kernel copy of userspace ioctl data काष्ठाure.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक cxlflash_lun_provision(काष्ठा cxlflash_cfg *cfg,
				  काष्ठा ht_cxlflash_lun_provision *lunprov)
अणु
	काष्ठा afu *afu = cfg->afu;
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा sisl_ioarcb rcb;
	काष्ठा sisl_ioasa asa;
	__be64 __iomem *fc_port_regs;
	u16 port = lunprov->port;
	u16 scmd = lunprov->hdr.subcmd;
	u16 type;
	u64 reg;
	u64 size;
	u64 lun_id;
	पूर्णांक rc = 0;

	अगर (!afu_is_lun_provision(afu)) अणु
		rc = -ENOTSUPP;
		जाओ out;
	पूर्ण

	अगर (port >= cfg->num_fc_ports) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	चयन (scmd) अणु
	हाल HT_CXLFLASH_LUN_PROVISION_SUBCMD_CREATE_LUN:
		type = SISL_AFU_LUN_PROVISION_CREATE;
		size = lunprov->size;
		lun_id = 0;
		अवरोध;
	हाल HT_CXLFLASH_LUN_PROVISION_SUBCMD_DELETE_LUN:
		type = SISL_AFU_LUN_PROVISION_DELETE;
		size = 0;
		lun_id = lunprov->lun_id;
		अवरोध;
	हाल HT_CXLFLASH_LUN_PROVISION_SUBCMD_QUERY_PORT:
		fc_port_regs = get_fc_port_regs(cfg, port);

		reg = पढ़ोq_be(&fc_port_regs[FC_MAX_NUM_LUNS / 8]);
		lunprov->max_num_luns = reg;
		reg = पढ़ोq_be(&fc_port_regs[FC_CUR_NUM_LUNS / 8]);
		lunprov->cur_num_luns = reg;
		reg = पढ़ोq_be(&fc_port_regs[FC_MAX_CAP_PORT / 8]);
		lunprov->max_cap_port = reg;
		reg = पढ़ोq_be(&fc_port_regs[FC_CUR_CAP_PORT / 8]);
		lunprov->cur_cap_port = reg;

		जाओ out;
	शेष:
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	स_रखो(&rcb, 0, माप(rcb));
	स_रखो(&asa, 0, माप(asa));
	rcb.req_flags = SISL_REQ_FLAGS_AFU_CMD;
	rcb.lun_id = lun_id;
	rcb.msi = SISL_MSI_RRQ_UPDATED;
	rcb.समयout = MC_LUN_PROV_TIMEOUT;
	rcb.ioasa = &asa;

	rcb.cdb[0] = SISL_AFU_CMD_LUN_PROVISION;
	rcb.cdb[1] = type;
	rcb.cdb[2] = port;
	put_unaligned_be64(size, &rcb.cdb[8]);

	rc = send_afu_cmd(afu, &rcb);
	अगर (rc) अणु
		dev_err(dev, "%s: send_afu_cmd failed rc=%d asc=%08x afux=%x\n",
			__func__, rc, asa.ioasc, asa.afu_extra);
		जाओ out;
	पूर्ण

	अगर (scmd == HT_CXLFLASH_LUN_PROVISION_SUBCMD_CREATE_LUN) अणु
		lunprov->lun_id = (u64)asa.lunid_hi << 32 | asa.lunid_lo;
		स_नकल(lunprov->wwid, asa.wwid, माप(lunprov->wwid));
	पूर्ण
out:
	dev_dbg(dev, "%s: returning rc=%d\n", __func__, rc);
	वापस rc;
पूर्ण

/**
 * cxlflash_afu_debug() - host AFU debug handler
 * @cfg:	Internal काष्ठाure associated with the host.
 * @afu_dbg:	Kernel copy of userspace ioctl data काष्ठाure.
 *
 * For debug requests requiring a data buffer, always provide an aligned
 * (cache line) buffer to the AFU to appease any alignment requirements.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक cxlflash_afu_debug(काष्ठा cxlflash_cfg *cfg,
			      काष्ठा ht_cxlflash_afu_debug *afu_dbg)
अणु
	काष्ठा afu *afu = cfg->afu;
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा sisl_ioarcb rcb;
	काष्ठा sisl_ioasa asa;
	अक्षर *buf = शून्य;
	अक्षर *kbuf = शून्य;
	व्योम __user *ubuf = (__क्रमce व्योम __user *)afu_dbg->data_ea;
	u16 req_flags = SISL_REQ_FLAGS_AFU_CMD;
	u32 ulen = afu_dbg->data_len;
	bool is_ग_लिखो = afu_dbg->hdr.flags & HT_CXLFLASH_HOST_WRITE;
	पूर्णांक rc = 0;

	अगर (!afu_is_afu_debug(afu)) अणु
		rc = -ENOTSUPP;
		जाओ out;
	पूर्ण

	अगर (ulen) अणु
		req_flags |= SISL_REQ_FLAGS_SUP_UNDERRUN;

		अगर (ulen > HT_CXLFLASH_AFU_DEBUG_MAX_DATA_LEN) अणु
			rc = -EINVAL;
			जाओ out;
		पूर्ण

		buf = kदो_स्मृति(ulen + cache_line_size() - 1, GFP_KERNEL);
		अगर (unlikely(!buf)) अणु
			rc = -ENOMEM;
			जाओ out;
		पूर्ण

		kbuf = PTR_ALIGN(buf, cache_line_size());

		अगर (is_ग_लिखो) अणु
			req_flags |= SISL_REQ_FLAGS_HOST_WRITE;

			अगर (copy_from_user(kbuf, ubuf, ulen)) अणु
				rc = -EFAULT;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	स_रखो(&rcb, 0, माप(rcb));
	स_रखो(&asa, 0, माप(asa));

	rcb.req_flags = req_flags;
	rcb.msi = SISL_MSI_RRQ_UPDATED;
	rcb.समयout = MC_AFU_DEBUG_TIMEOUT;
	rcb.ioasa = &asa;

	अगर (ulen) अणु
		rcb.data_len = ulen;
		rcb.data_ea = (uपूर्णांकptr_t)kbuf;
	पूर्ण

	rcb.cdb[0] = SISL_AFU_CMD_DEBUG;
	स_नकल(&rcb.cdb[4], afu_dbg->afu_subcmd,
	       HT_CXLFLASH_AFU_DEBUG_SUBCMD_LEN);

	rc = send_afu_cmd(afu, &rcb);
	अगर (rc) अणु
		dev_err(dev, "%s: send_afu_cmd failed rc=%d asc=%08x afux=%x\n",
			__func__, rc, asa.ioasc, asa.afu_extra);
		जाओ out;
	पूर्ण

	अगर (ulen && !is_ग_लिखो) अणु
		अगर (copy_to_user(ubuf, kbuf, ulen))
			rc = -EFAULT;
	पूर्ण
out:
	kमुक्त(buf);
	dev_dbg(dev, "%s: returning rc=%d\n", __func__, rc);
	वापस rc;
पूर्ण

/**
 * cxlflash_chr_ioctl() - अक्षरacter device IOCTL handler
 * @file:	File poपूर्णांकer क्रम this device.
 * @cmd:	IOCTL command.
 * @arg:	Userspace ioctl data काष्ठाure.
 *
 * A पढ़ो/ग_लिखो semaphore is used to implement a 'drain' of currently
 * running ioctls. The पढ़ो semaphore is taken at the beginning of each
 * ioctl thपढ़ो and released upon concluding execution. Additionally the
 * semaphore should be released and then reacquired in any ioctl execution
 * path which will रुको क्रम an event to occur that is outside the scope of
 * the ioctl (i.e. an adapter reset). To drain the ioctls currently running,
 * a thपढ़ो simply needs to acquire the ग_लिखो semaphore.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल दीर्घ cxlflash_chr_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			       अचिन्हित दीर्घ arg)
अणु
	प्रकार पूर्णांक (*hioctl) (काष्ठा cxlflash_cfg *, व्योम *);

	काष्ठा cxlflash_cfg *cfg = file->निजी_data;
	काष्ठा device *dev = &cfg->dev->dev;
	अक्षर buf[माप(जोड़ cxlflash_ht_ioctls)];
	व्योम __user *uarg = (व्योम __user *)arg;
	काष्ठा ht_cxlflash_hdr *hdr;
	माप_प्रकार size = 0;
	bool known_ioctl = false;
	पूर्णांक idx = 0;
	पूर्णांक rc = 0;
	hioctl करो_ioctl = शून्य;

	अटल स्थिर काष्ठा अणु
		माप_प्रकार size;
		hioctl ioctl;
	पूर्ण ioctl_tbl[] = अणु	/* NOTE: order matters here */
	अणु माप(काष्ठा ht_cxlflash_lun_provision),
		(hioctl)cxlflash_lun_provision पूर्ण,
	अणु माप(काष्ठा ht_cxlflash_afu_debug),
		(hioctl)cxlflash_afu_debug पूर्ण,
	पूर्ण;

	/* Hold पढ़ो semaphore so we can drain अगर needed */
	करोwn_पढ़ो(&cfg->ioctl_rwsem);

	dev_dbg(dev, "%s: cmd=%u idx=%d tbl_size=%lu\n",
		__func__, cmd, idx, माप(ioctl_tbl));

	चयन (cmd) अणु
	हाल HT_CXLFLASH_LUN_PROVISION:
	हाल HT_CXLFLASH_AFU_DEBUG:
		known_ioctl = true;
		idx = _IOC_NR(HT_CXLFLASH_LUN_PROVISION) - _IOC_NR(cmd);
		size = ioctl_tbl[idx].size;
		करो_ioctl = ioctl_tbl[idx].ioctl;

		अगर (likely(करो_ioctl))
			अवरोध;

		fallthrough;
	शेष:
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (unlikely(copy_from_user(&buf, uarg, size))) अणु
		dev_err(dev, "%s: copy_from_user() fail "
			"size=%lu cmd=%d (%s) uarg=%p\n",
			__func__, size, cmd, decode_hioctl(cmd), uarg);
		rc = -EFAULT;
		जाओ out;
	पूर्ण

	hdr = (काष्ठा ht_cxlflash_hdr *)&buf;
	अगर (hdr->version != HT_CXLFLASH_VERSION_0) अणु
		dev_dbg(dev, "%s: Version %u not supported for %s\n",
			__func__, hdr->version, decode_hioctl(cmd));
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (hdr->rsvd[0] || hdr->rsvd[1] || hdr->वापस_flags) अणु
		dev_dbg(dev, "%s: Reserved/rflags populated\n", __func__);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	rc = करो_ioctl(cfg, (व्योम *)&buf);
	अगर (likely(!rc))
		अगर (unlikely(copy_to_user(uarg, &buf, size))) अणु
			dev_err(dev, "%s: copy_to_user() fail "
				"size=%lu cmd=%d (%s) uarg=%p\n",
				__func__, size, cmd, decode_hioctl(cmd), uarg);
			rc = -EFAULT;
		पूर्ण

	/* fall through to निकास */

out:
	up_पढ़ो(&cfg->ioctl_rwsem);
	अगर (unlikely(rc && known_ioctl))
		dev_err(dev, "%s: ioctl %s (%08X) returned rc=%d\n",
			__func__, decode_hioctl(cmd), cmd, rc);
	अन्यथा
		dev_dbg(dev, "%s: ioctl %s (%08X) returned rc=%d\n",
			__func__, decode_hioctl(cmd), cmd, rc);
	वापस rc;
पूर्ण

/*
 * Character device file operations
 */
अटल स्थिर काष्ठा file_operations cxlflash_chr_fops = अणु
	.owner          = THIS_MODULE,
	.खोलो           = cxlflash_chr_खोलो,
	.unlocked_ioctl	= cxlflash_chr_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
पूर्ण;

/**
 * init_chrdev() - initialize the अक्षरacter device क्रम the host
 * @cfg:	Internal काष्ठाure associated with the host.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक init_chrdev(काष्ठा cxlflash_cfg *cfg)
अणु
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा device *अक्षर_dev;
	dev_t devno;
	पूर्णांक minor;
	पूर्णांक rc = 0;

	minor = cxlflash_get_minor();
	अगर (unlikely(minor < 0)) अणु
		dev_err(dev, "%s: Exhausted allowed adapters\n", __func__);
		rc = -ENOSPC;
		जाओ out;
	पूर्ण

	devno = MKDEV(cxlflash_major, minor);
	cdev_init(&cfg->cdev, &cxlflash_chr_fops);

	rc = cdev_add(&cfg->cdev, devno, 1);
	अगर (rc) अणु
		dev_err(dev, "%s: cdev_add failed rc=%d\n", __func__, rc);
		जाओ err1;
	पूर्ण

	अक्षर_dev = device_create(cxlflash_class, शून्य, devno,
				 शून्य, "cxlflash%d", minor);
	अगर (IS_ERR(अक्षर_dev)) अणु
		rc = PTR_ERR(अक्षर_dev);
		dev_err(dev, "%s: device_create failed rc=%d\n",
			__func__, rc);
		जाओ err2;
	पूर्ण

	cfg->अक्षरdev = अक्षर_dev;
out:
	dev_dbg(dev, "%s: returning rc=%d\n", __func__, rc);
	वापस rc;
err2:
	cdev_del(&cfg->cdev);
err1:
	cxlflash_put_minor(minor);
	जाओ out;
पूर्ण

/**
 * cxlflash_probe() - PCI entry poपूर्णांक to add host
 * @pdev:	PCI device associated with the host.
 * @dev_id:	PCI device id associated with device.
 *
 * The device will initially start out in a 'probing' state and
 * transition to the 'normal' state at the end of a successful
 * probe. Should an EEH event occur during probe, the notअगरication
 * thपढ़ो (error_detected()) will रुको until the probe handler
 * is nearly complete. At that समय, the device will be moved to
 * a 'probed' state and the EEH thपढ़ो woken up to drive the slot
 * reset and recovery (device moves to 'normal' state). Meanजबतक,
 * the probe will be allowed to निकास successfully.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक cxlflash_probe(काष्ठा pci_dev *pdev,
			  स्थिर काष्ठा pci_device_id *dev_id)
अणु
	काष्ठा Scsi_Host *host;
	काष्ठा cxlflash_cfg *cfg = शून्य;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा dev_dependent_vals *ddv;
	पूर्णांक rc = 0;
	पूर्णांक k;

	dev_dbg(&pdev->dev, "%s: Found CXLFLASH with IRQ: %d\n",
		__func__, pdev->irq);

	ddv = (काष्ठा dev_dependent_vals *)dev_id->driver_data;
	driver_ढाँचा.max_sectors = ddv->max_sectors;

	host = scsi_host_alloc(&driver_ढाँचा, माप(काष्ठा cxlflash_cfg));
	अगर (!host) अणु
		dev_err(dev, "%s: scsi_host_alloc failed\n", __func__);
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	host->max_id = CXLFLASH_MAX_NUM_TARGETS_PER_BUS;
	host->max_lun = CXLFLASH_MAX_NUM_LUNS_PER_TARGET;
	host->unique_id = host->host_no;
	host->max_cmd_len = CXLFLASH_MAX_CDB_LEN;

	cfg = shost_priv(host);
	cfg->state = STATE_PROBING;
	cfg->host = host;
	rc = alloc_mem(cfg);
	अगर (rc) अणु
		dev_err(dev, "%s: alloc_mem failed\n", __func__);
		rc = -ENOMEM;
		scsi_host_put(cfg->host);
		जाओ out;
	पूर्ण

	cfg->init_state = INIT_STATE_NONE;
	cfg->dev = pdev;
	cfg->cxl_fops = cxlflash_cxl_fops;
	cfg->ops = cxlflash_assign_ops(ddv);
	WARN_ON_ONCE(!cfg->ops);

	/*
	 * Promoted LUNs move to the top of the LUN table. The rest stay on
	 * the bottom half. The bottom half grows from the end (index = 255),
	 * whereas the top half grows from the beginning (index = 0).
	 *
	 * Initialize the last LUN index क्रम all possible ports.
	 */
	cfg->promote_lun_index = 0;

	क्रम (k = 0; k < MAX_FC_PORTS; k++)
		cfg->last_lun_index[k] = CXLFLASH_NUM_VLUNS/2 - 1;

	cfg->dev_id = (काष्ठा pci_device_id *)dev_id;

	init_रुकोqueue_head(&cfg->पंचांगf_रुकोq);
	init_रुकोqueue_head(&cfg->reset_रुकोq);

	INIT_WORK(&cfg->work_q, cxlflash_worker_thपढ़ो);
	cfg->lr_state = LINK_RESET_INVALID;
	cfg->lr_port = -1;
	spin_lock_init(&cfg->पंचांगf_slock);
	mutex_init(&cfg->ctx_tbl_list_mutex);
	mutex_init(&cfg->ctx_recovery_mutex);
	init_rwsem(&cfg->ioctl_rwsem);
	INIT_LIST_HEAD(&cfg->ctx_err_recovery);
	INIT_LIST_HEAD(&cfg->lluns);

	pci_set_drvdata(pdev, cfg);

	rc = init_pci(cfg);
	अगर (rc) अणु
		dev_err(dev, "%s: init_pci failed rc=%d\n", __func__, rc);
		जाओ out_हटाओ;
	पूर्ण
	cfg->init_state = INIT_STATE_PCI;

	cfg->afu_cookie = cfg->ops->create_afu(pdev);
	अगर (unlikely(!cfg->afu_cookie)) अणु
		dev_err(dev, "%s: create_afu failed\n", __func__);
		rc = -ENOMEM;
		जाओ out_हटाओ;
	पूर्ण

	rc = init_afu(cfg);
	अगर (rc && !wq_has_sleeper(&cfg->reset_रुकोq)) अणु
		dev_err(dev, "%s: init_afu failed rc=%d\n", __func__, rc);
		जाओ out_हटाओ;
	पूर्ण
	cfg->init_state = INIT_STATE_AFU;

	rc = init_scsi(cfg);
	अगर (rc) अणु
		dev_err(dev, "%s: init_scsi failed rc=%d\n", __func__, rc);
		जाओ out_हटाओ;
	पूर्ण
	cfg->init_state = INIT_STATE_SCSI;

	rc = init_chrdev(cfg);
	अगर (rc) अणु
		dev_err(dev, "%s: init_chrdev failed rc=%d\n", __func__, rc);
		जाओ out_हटाओ;
	पूर्ण
	cfg->init_state = INIT_STATE_CDEV;

	अगर (wq_has_sleeper(&cfg->reset_रुकोq)) अणु
		cfg->state = STATE_PROBED;
		wake_up_all(&cfg->reset_रुकोq);
	पूर्ण अन्यथा
		cfg->state = STATE_NORMAL;
out:
	dev_dbg(dev, "%s: returning rc=%d\n", __func__, rc);
	वापस rc;

out_हटाओ:
	cfg->state = STATE_PROBED;
	cxlflash_हटाओ(pdev);
	जाओ out;
पूर्ण

/**
 * cxlflash_pci_error_detected() - called when a PCI error is detected
 * @pdev:	PCI device काष्ठा.
 * @state:	PCI channel state.
 *
 * When an EEH occurs during an active reset, रुको until the reset is
 * complete and then take action based upon the device state.
 *
 * Return: PCI_ERS_RESULT_NEED_RESET or PCI_ERS_RESULT_DISCONNECT
 */
अटल pci_ers_result_t cxlflash_pci_error_detected(काष्ठा pci_dev *pdev,
						    pci_channel_state_t state)
अणु
	पूर्णांक rc = 0;
	काष्ठा cxlflash_cfg *cfg = pci_get_drvdata(pdev);
	काष्ठा device *dev = &cfg->dev->dev;

	dev_dbg(dev, "%s: pdev=%p state=%u\n", __func__, pdev, state);

	चयन (state) अणु
	हाल pci_channel_io_frozen:
		रुको_event(cfg->reset_रुकोq, cfg->state != STATE_RESET &&
					     cfg->state != STATE_PROBING);
		अगर (cfg->state == STATE_FAILTERM)
			वापस PCI_ERS_RESULT_DISCONNECT;

		cfg->state = STATE_RESET;
		scsi_block_requests(cfg->host);
		drain_ioctls(cfg);
		rc = cxlflash_mark_contexts_error(cfg);
		अगर (unlikely(rc))
			dev_err(dev, "%s: Failed to mark user contexts rc=%d\n",
				__func__, rc);
		term_afu(cfg);
		वापस PCI_ERS_RESULT_NEED_RESET;
	हाल pci_channel_io_perm_failure:
		cfg->state = STATE_FAILTERM;
		wake_up_all(&cfg->reset_रुकोq);
		scsi_unblock_requests(cfg->host);
		वापस PCI_ERS_RESULT_DISCONNECT;
	शेष:
		अवरोध;
	पूर्ण
	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

/**
 * cxlflash_pci_slot_reset() - called when PCI slot has been reset
 * @pdev:	PCI device काष्ठा.
 *
 * This routine is called by the pci error recovery code after the PCI
 * slot has been reset, just beक्रमe we should resume normal operations.
 *
 * Return: PCI_ERS_RESULT_RECOVERED or PCI_ERS_RESULT_DISCONNECT
 */
अटल pci_ers_result_t cxlflash_pci_slot_reset(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक rc = 0;
	काष्ठा cxlflash_cfg *cfg = pci_get_drvdata(pdev);
	काष्ठा device *dev = &cfg->dev->dev;

	dev_dbg(dev, "%s: pdev=%p\n", __func__, pdev);

	rc = init_afu(cfg);
	अगर (unlikely(rc)) अणु
		dev_err(dev, "%s: EEH recovery failed rc=%d\n", __func__, rc);
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	वापस PCI_ERS_RESULT_RECOVERED;
पूर्ण

/**
 * cxlflash_pci_resume() - called when normal operation can resume
 * @pdev:	PCI device काष्ठा
 */
अटल व्योम cxlflash_pci_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा cxlflash_cfg *cfg = pci_get_drvdata(pdev);
	काष्ठा device *dev = &cfg->dev->dev;

	dev_dbg(dev, "%s: pdev=%p\n", __func__, pdev);

	cfg->state = STATE_NORMAL;
	wake_up_all(&cfg->reset_रुकोq);
	scsi_unblock_requests(cfg->host);
पूर्ण

/**
 * cxlflash_devnode() - provides devपंचांगpfs क्रम devices in the cxlflash class
 * @dev:	Character device.
 * @mode:	Mode that can be used to verअगरy access.
 *
 * Return: Allocated string describing the devपंचांगpfs काष्ठाure.
 */
अटल अक्षर *cxlflash_devnode(काष्ठा device *dev, umode_t *mode)
अणु
	वापस kaप्र_लिखो(GFP_KERNEL, "cxlflash/%s", dev_name(dev));
पूर्ण

/**
 * cxlflash_class_init() - create अक्षरacter device class
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक cxlflash_class_init(व्योम)
अणु
	dev_t devno;
	पूर्णांक rc = 0;

	rc = alloc_chrdev_region(&devno, 0, CXLFLASH_MAX_ADAPTERS, "cxlflash");
	अगर (unlikely(rc)) अणु
		pr_err("%s: alloc_chrdev_region failed rc=%d\n", __func__, rc);
		जाओ out;
	पूर्ण

	cxlflash_major = MAJOR(devno);

	cxlflash_class = class_create(THIS_MODULE, "cxlflash");
	अगर (IS_ERR(cxlflash_class)) अणु
		rc = PTR_ERR(cxlflash_class);
		pr_err("%s: class_create failed rc=%d\n", __func__, rc);
		जाओ err;
	पूर्ण

	cxlflash_class->devnode = cxlflash_devnode;
out:
	pr_debug("%s: returning rc=%d\n", __func__, rc);
	वापस rc;
err:
	unरेजिस्टर_chrdev_region(devno, CXLFLASH_MAX_ADAPTERS);
	जाओ out;
पूर्ण

/**
 * cxlflash_class_निकास() - destroy अक्षरacter device class
 */
अटल व्योम cxlflash_class_निकास(व्योम)
अणु
	dev_t devno = MKDEV(cxlflash_major, 0);

	class_destroy(cxlflash_class);
	unरेजिस्टर_chrdev_region(devno, CXLFLASH_MAX_ADAPTERS);
पूर्ण

अटल स्थिर काष्ठा pci_error_handlers cxlflash_err_handler = अणु
	.error_detected = cxlflash_pci_error_detected,
	.slot_reset = cxlflash_pci_slot_reset,
	.resume = cxlflash_pci_resume,
पूर्ण;

/*
 * PCI device काष्ठाure
 */
अटल काष्ठा pci_driver cxlflash_driver = अणु
	.name = CXLFLASH_NAME,
	.id_table = cxlflash_pci_table,
	.probe = cxlflash_probe,
	.हटाओ = cxlflash_हटाओ,
	.shutकरोwn = cxlflash_हटाओ,
	.err_handler = &cxlflash_err_handler,
पूर्ण;

/**
 * init_cxlflash() - module entry poपूर्णांक
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक __init init_cxlflash(व्योम)
अणु
	पूर्णांक rc;

	check_sizes();
	cxlflash_list_init();
	rc = cxlflash_class_init();
	अगर (unlikely(rc))
		जाओ out;

	rc = pci_रेजिस्टर_driver(&cxlflash_driver);
	अगर (unlikely(rc))
		जाओ err;
out:
	pr_debug("%s: returning rc=%d\n", __func__, rc);
	वापस rc;
err:
	cxlflash_class_निकास();
	जाओ out;
पूर्ण

/**
 * निकास_cxlflash() - module निकास poपूर्णांक
 */
अटल व्योम __निकास निकास_cxlflash(व्योम)
अणु
	cxlflash_term_global_luns();
	cxlflash_मुक्त_errpage();

	pci_unरेजिस्टर_driver(&cxlflash_driver);
	cxlflash_class_निकास();
पूर्ण

module_init(init_cxlflash);
module_निकास(निकास_cxlflash);
