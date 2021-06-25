<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Support क्रम SATA devices on Serial Attached SCSI (SAS) controllers
 *
 * Copyright (C) 2006 IBM Corporation
 *
 * Written by: Darrick J. Wong <djwong@us.ibm.com>, IBM Corporation
 */

#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>
#समावेश <linux/async.h>
#समावेश <linux/export.h>

#समावेश <scsi/sas_ata.h>
#समावेश "sas_internal.h"
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_transport_sas.h>
#समावेश "../scsi_sas_internal.h"
#समावेश "../scsi_transport_api.h"
#समावेश <scsi/scsi_eh.h>

अटल क्रमागत ata_completion_errors sas_to_ata_err(काष्ठा task_status_काष्ठा *ts)
अणु
	/* Cheesy attempt to translate SAS errors पूर्णांकo ATA.  Hah! */

	/* transport error */
	अगर (ts->resp == SAS_TASK_UNDELIVERED)
		वापस AC_ERR_ATA_BUS;

	/* ts->resp == SAS_TASK_COMPLETE */
	/* task delivered, what happened afterwards? */
	चयन (ts->stat) अणु
	हाल SAS_DEV_NO_RESPONSE:
		वापस AC_ERR_TIMEOUT;
	हाल SAS_INTERRUPTED:
	हाल SAS_PHY_DOWN:
	हाल SAS_NAK_R_ERR:
		वापस AC_ERR_ATA_BUS;
	हाल SAS_DATA_UNDERRUN:
		/*
		 * Some programs that use the taskfile पूर्णांकerface
		 * (smartctl in particular) can cause underrun
		 * problems.  Ignore these errors, perhaps at our
		 * peril.
		 */
		वापस 0;
	हाल SAS_DATA_OVERRUN:
	हाल SAS_QUEUE_FULL:
	हाल SAS_DEVICE_UNKNOWN:
	हाल SAS_SG_ERR:
		वापस AC_ERR_INVALID;
	हाल SAS_OPEN_TO:
	हाल SAS_OPEN_REJECT:
		pr_warn("%s: Saw error %d.  What to do?\n",
			__func__, ts->stat);
		वापस AC_ERR_OTHER;
	हाल SAM_STAT_CHECK_CONDITION:
	हाल SAS_ABORTED_TASK:
		वापस AC_ERR_DEV;
	हाल SAS_PROTO_RESPONSE:
		/* This means the ending_fis has the error
		 * value; वापस 0 here to collect it
		 */
		वापस 0;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम sas_ata_task_करोne(काष्ठा sas_task *task)
अणु
	काष्ठा ata_queued_cmd *qc = task->uldd_task;
	काष्ठा करोमुख्य_device *dev = task->dev;
	काष्ठा task_status_काष्ठा *stat = &task->task_status;
	काष्ठा ata_task_resp *resp = (काष्ठा ata_task_resp *)stat->buf;
	काष्ठा sas_ha_काष्ठा *sas_ha = dev->port->ha;
	क्रमागत ata_completion_errors ac;
	अचिन्हित दीर्घ flags;
	काष्ठा ata_link *link;
	काष्ठा ata_port *ap;

	spin_lock_irqsave(&dev->करोne_lock, flags);
	अगर (test_bit(SAS_HA_FROZEN, &sas_ha->state))
		task = शून्य;
	अन्यथा अगर (qc && qc->scsicmd)
		ASSIGN_SAS_TASK(qc->scsicmd, शून्य);
	spin_unlock_irqrestore(&dev->करोne_lock, flags);

	/* check अगर libsas-eh got to the task beक्रमe us */
	अगर (unlikely(!task))
		वापस;

	अगर (!qc)
		जाओ qc_alपढ़ोy_gone;

	ap = qc->ap;
	link = &ap->link;

	spin_lock_irqsave(ap->lock, flags);
	/* check अगर we lost the race with libata/sas_ata_post_पूर्णांकernal() */
	अगर (unlikely(ap->pflags & ATA_PFLAG_FROZEN)) अणु
		spin_unlock_irqrestore(ap->lock, flags);
		अगर (qc->scsicmd)
			जाओ qc_alपढ़ोy_gone;
		अन्यथा अणु
			/* अगर eh is not involved and the port is frozen then the
			 * ata पूर्णांकernal पात process has taken responsibility
			 * क्रम this sas_task
			 */
			वापस;
		पूर्ण
	पूर्ण

	अगर (stat->stat == SAS_PROTO_RESPONSE || stat->stat == SAM_STAT_GOOD ||
	    ((stat->stat == SAM_STAT_CHECK_CONDITION &&
	      dev->sata_dev.class == ATA_DEV_ATAPI))) अणु
		स_नकल(dev->sata_dev.fis, resp->ending_fis, ATA_RESP_FIS_SIZE);

		अगर (!link->sactive) अणु
			qc->err_mask |= ac_err_mask(dev->sata_dev.fis[2]);
		पूर्ण अन्यथा अणु
			link->eh_info.err_mask |= ac_err_mask(dev->sata_dev.fis[2]);
			अगर (unlikely(link->eh_info.err_mask))
				qc->flags |= ATA_QCFLAG_FAILED;
		पूर्ण
	पूर्ण अन्यथा अणु
		ac = sas_to_ata_err(stat);
		अगर (ac) अणु
			pr_warn("%s: SAS error 0x%x\n", __func__, stat->stat);
			/* We saw a SAS error. Send a vague error. */
			अगर (!link->sactive) अणु
				qc->err_mask = ac;
			पूर्ण अन्यथा अणु
				link->eh_info.err_mask |= AC_ERR_DEV;
				qc->flags |= ATA_QCFLAG_FAILED;
			पूर्ण

			dev->sata_dev.fis[3] = 0x04; /* status err */
			dev->sata_dev.fis[2] = ATA_ERR;
		पूर्ण
	पूर्ण

	qc->lldd_task = शून्य;
	ata_qc_complete(qc);
	spin_unlock_irqrestore(ap->lock, flags);

qc_alपढ़ोy_gone:
	sas_मुक्त_task(task);
पूर्ण

अटल अचिन्हित पूर्णांक sas_ata_qc_issue(काष्ठा ata_queued_cmd *qc)
	__must_hold(ap->lock)
अणु
	काष्ठा sas_task *task;
	काष्ठा scatterlist *sg;
	पूर्णांक ret = AC_ERR_SYSTEM;
	अचिन्हित पूर्णांक si, xfer = 0;
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा करोमुख्य_device *dev = ap->निजी_data;
	काष्ठा sas_ha_काष्ठा *sas_ha = dev->port->ha;
	काष्ठा Scsi_Host *host = sas_ha->core.shost;
	काष्ठा sas_पूर्णांकernal *i = to_sas_पूर्णांकernal(host->transportt);

	/* TODO: we should try to हटाओ that unlock */
	spin_unlock(ap->lock);

	/* If the device fell off, no sense in issuing commands */
	अगर (test_bit(SAS_DEV_GONE, &dev->state))
		जाओ out;

	task = sas_alloc_task(GFP_ATOMIC);
	अगर (!task)
		जाओ out;
	task->dev = dev;
	task->task_proto = SAS_PROTOCOL_STP;
	task->task_करोne = sas_ata_task_करोne;

	अगर (qc->tf.command == ATA_CMD_FPDMA_WRITE ||
	    qc->tf.command == ATA_CMD_FPDMA_READ ||
	    qc->tf.command == ATA_CMD_FPDMA_RECV ||
	    qc->tf.command == ATA_CMD_FPDMA_SEND ||
	    qc->tf.command == ATA_CMD_NCQ_NON_DATA) अणु
		/* Need to zero out the tag libata asचिन्हित us */
		qc->tf.nsect = 0;
	पूर्ण

	ata_tf_to_fis(&qc->tf, qc->dev->link->pmp, 1, (u8 *)&task->ata_task.fis);
	task->uldd_task = qc;
	अगर (ata_is_atapi(qc->tf.protocol)) अणु
		स_नकल(task->ata_task.atapi_packet, qc->cdb, qc->dev->cdb_len);
		task->total_xfer_len = qc->nbytes;
		task->num_scatter = qc->n_elem;
		task->data_dir = qc->dma_dir;
	पूर्ण अन्यथा अगर (qc->tf.protocol == ATA_PROT_NODATA) अणु
		task->data_dir = DMA_NONE;
	पूर्ण अन्यथा अणु
		क्रम_each_sg(qc->sg, sg, qc->n_elem, si)
			xfer += sg_dma_len(sg);

		task->total_xfer_len = xfer;
		task->num_scatter = si;
		task->data_dir = qc->dma_dir;
	पूर्ण
	task->scatter = qc->sg;
	task->ata_task.retry_count = 1;
	task->task_state_flags = SAS_TASK_STATE_PENDING;
	qc->lldd_task = task;

	task->ata_task.use_ncq = ata_is_ncq(qc->tf.protocol);
	task->ata_task.dma_xfer = ata_is_dma(qc->tf.protocol);

	अगर (qc->scsicmd)
		ASSIGN_SAS_TASK(qc->scsicmd, task);

	ret = i->dft->lldd_execute_task(task, GFP_ATOMIC);
	अगर (ret) अणु
		pr_debug("lldd_execute_task returned: %d\n", ret);

		अगर (qc->scsicmd)
			ASSIGN_SAS_TASK(qc->scsicmd, शून्य);
		sas_मुक्त_task(task);
		qc->lldd_task = शून्य;
		ret = AC_ERR_SYSTEM;
	पूर्ण

 out:
	spin_lock(ap->lock);
	वापस ret;
पूर्ण

अटल bool sas_ata_qc_fill_rtf(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा करोमुख्य_device *dev = qc->ap->निजी_data;

	ata_tf_from_fis(dev->sata_dev.fis, &qc->result_tf);
	वापस true;
पूर्ण

अटल काष्ठा sas_पूर्णांकernal *dev_to_sas_पूर्णांकernal(काष्ठा करोमुख्य_device *dev)
अणु
	वापस to_sas_पूर्णांकernal(dev->port->ha->core.shost->transportt);
पूर्ण

अटल पूर्णांक sas_get_ata_command_set(काष्ठा करोमुख्य_device *dev);

पूर्णांक sas_get_ata_info(काष्ठा करोमुख्य_device *dev, काष्ठा ex_phy *phy)
अणु
	अगर (phy->attached_tproto & SAS_PROTOCOL_STP)
		dev->tproto = phy->attached_tproto;
	अगर (phy->attached_sata_dev)
		dev->tproto |= SAS_SATA_DEV;

	अगर (phy->attached_dev_type == SAS_SATA_PENDING)
		dev->dev_type = SAS_SATA_PENDING;
	अन्यथा अणु
		पूर्णांक res;

		dev->dev_type = SAS_SATA_DEV;
		res = sas_get_report_phy_sata(dev->parent, phy->phy_id,
					      &dev->sata_dev.rps_resp);
		अगर (res) अणु
			pr_debug("report phy sata to %016llx:%02d returned 0x%x\n",
				 SAS_ADDR(dev->parent->sas_addr),
				 phy->phy_id, res);
			वापस res;
		पूर्ण
		स_नकल(dev->frame_rcvd, &dev->sata_dev.rps_resp.rps.fis,
		       माप(काष्ठा dev_to_host_fis));
		dev->sata_dev.class = sas_get_ata_command_set(dev);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sas_ata_clear_pending(काष्ठा करोमुख्य_device *dev, काष्ठा ex_phy *phy)
अणु
	पूर्णांक res;

	/* we weren't pending, so successfully end the reset sequence now */
	अगर (dev->dev_type != SAS_SATA_PENDING)
		वापस 1;

	/* hmmm, अगर this succeeds करो we need to repost the करोमुख्य_device to the
	 * lldd so it can pick up new parameters?
	 */
	res = sas_get_ata_info(dev, phy);
	अगर (res)
		वापस 0; /* retry */
	अन्यथा
		वापस 1;
पूर्ण

अटल पूर्णांक smp_ata_check_पढ़ोy(काष्ठा ata_link *link)
अणु
	पूर्णांक res;
	काष्ठा ata_port *ap = link->ap;
	काष्ठा करोमुख्य_device *dev = ap->निजी_data;
	काष्ठा करोमुख्य_device *ex_dev = dev->parent;
	काष्ठा sas_phy *phy = sas_get_local_phy(dev);
	काष्ठा ex_phy *ex_phy = &ex_dev->ex_dev.ex_phy[phy->number];

	res = sas_ex_phy_discover(ex_dev, phy->number);
	sas_put_local_phy(phy);

	/* अवरोध the रुको early अगर the expander is unreachable,
	 * otherwise keep polling
	 */
	अगर (res == -ECOMM)
		वापस res;
	अगर (res != SMP_RESP_FUNC_ACC)
		वापस 0;

	चयन (ex_phy->attached_dev_type) अणु
	हाल SAS_SATA_PENDING:
		वापस 0;
	हाल SAS_END_DEVICE:
		अगर (ex_phy->attached_sata_dev)
			वापस sas_ata_clear_pending(dev, ex_phy);
		fallthrough;
	शेष:
		वापस -ENODEV;
	पूर्ण
पूर्ण

अटल पूर्णांक local_ata_check_पढ़ोy(काष्ठा ata_link *link)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा करोमुख्य_device *dev = ap->निजी_data;
	काष्ठा sas_पूर्णांकernal *i = dev_to_sas_पूर्णांकernal(dev);

	अगर (i->dft->lldd_ata_check_पढ़ोy)
		वापस i->dft->lldd_ata_check_पढ़ोy(dev);
	अन्यथा अणु
		/* lldd's that don't implement 'ready' checking get the
		 * old शेष behavior of not coordinating reset
		 * recovery with libata
		 */
		वापस 1;
	पूर्ण
पूर्ण

अटल पूर्णांक sas_ata_prपूर्णांकk(स्थिर अक्षर *level, स्थिर काष्ठा करोमुख्य_device *ddev,
			  स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा ata_port *ap = ddev->sata_dev.ap;
	काष्ठा device *dev = &ddev->rphy->dev;
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;
	पूर्णांक r;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	r = prपूर्णांकk("%s" SAS_FMT "ata%u: %s: %pV",
		   level, ap->prपूर्णांक_id, dev_name(dev), &vaf);

	बहु_पूर्ण(args);

	वापस r;
पूर्ण

अटल पूर्णांक sas_ata_hard_reset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
			      अचिन्हित दीर्घ deadline)
अणु
	पूर्णांक ret = 0, res;
	काष्ठा sas_phy *phy;
	काष्ठा ata_port *ap = link->ap;
	पूर्णांक (*check_पढ़ोy)(काष्ठा ata_link *link);
	काष्ठा करोमुख्य_device *dev = ap->निजी_data;
	काष्ठा sas_पूर्णांकernal *i = dev_to_sas_पूर्णांकernal(dev);

	res = i->dft->lldd_I_T_nexus_reset(dev);
	अगर (res == -ENODEV)
		वापस res;

	अगर (res != TMF_RESP_FUNC_COMPLETE)
		sas_ata_prपूर्णांकk(KERN_DEBUG, dev, "Unable to reset ata device?\n");

	phy = sas_get_local_phy(dev);
	अगर (scsi_is_sas_phy_local(phy))
		check_पढ़ोy = local_ata_check_पढ़ोy;
	अन्यथा
		check_पढ़ोy = smp_ata_check_पढ़ोy;
	sas_put_local_phy(phy);

	ret = ata_रुको_after_reset(link, deadline, check_पढ़ोy);
	अगर (ret && ret != -EAGAIN)
		sas_ata_prपूर्णांकk(KERN_ERR, dev, "reset failed (errno=%d)\n", ret);

	*class = dev->sata_dev.class;

	ap->cbl = ATA_CBL_SATA;
	वापस ret;
पूर्ण

/*
 * notअगरy the lldd to क्रमget the sas_task क्रम this पूर्णांकernal ata command
 * that bypasses scsi-eh
 */
अटल व्योम sas_ata_पूर्णांकernal_पात(काष्ठा sas_task *task)
अणु
	काष्ठा sas_पूर्णांकernal *si = dev_to_sas_पूर्णांकernal(task->dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक res;

	spin_lock_irqsave(&task->task_state_lock, flags);
	अगर (task->task_state_flags & SAS_TASK_STATE_ABORTED ||
	    task->task_state_flags & SAS_TASK_STATE_DONE) अणु
		spin_unlock_irqrestore(&task->task_state_lock, flags);
		pr_debug("%s: Task %p already finished.\n", __func__, task);
		जाओ out;
	पूर्ण
	task->task_state_flags |= SAS_TASK_STATE_ABORTED;
	spin_unlock_irqrestore(&task->task_state_lock, flags);

	res = si->dft->lldd_पात_task(task);

	spin_lock_irqsave(&task->task_state_lock, flags);
	अगर (task->task_state_flags & SAS_TASK_STATE_DONE ||
	    res == TMF_RESP_FUNC_COMPLETE) अणु
		spin_unlock_irqrestore(&task->task_state_lock, flags);
		जाओ out;
	पूर्ण

	/* XXX we are not prepared to deal with ->lldd_पात_task()
	 * failures.  TODO: lldds need to unconditionally क्रमget about
	 * पातed ata tasks, otherwise we (likely) leak the sas task
	 * here
	 */
	pr_warn("%s: Task %p leaked.\n", __func__, task);

	अगर (!(task->task_state_flags & SAS_TASK_STATE_DONE))
		task->task_state_flags &= ~SAS_TASK_STATE_ABORTED;
	spin_unlock_irqrestore(&task->task_state_lock, flags);

	वापस;
 out:
	sas_मुक्त_task(task);
पूर्ण

अटल व्योम sas_ata_post_पूर्णांकernal(काष्ठा ata_queued_cmd *qc)
अणु
	अगर (qc->flags & ATA_QCFLAG_FAILED)
		qc->err_mask |= AC_ERR_OTHER;

	अगर (qc->err_mask) अणु
		/*
		 * Find the sas_task and समाप्त it.  By this poपूर्णांक, libata
		 * has decided to समाप्त the qc and has frozen the port.
		 * In this state sas_ata_task_करोne() will no दीर्घer मुक्त
		 * the sas_task, so we need to notअगरy the lldd (via
		 * ->lldd_पात_task) that the task is dead and मुक्त it
		 *  ourselves.
		 */
		काष्ठा sas_task *task = qc->lldd_task;

		qc->lldd_task = शून्य;
		अगर (!task)
			वापस;
		task->uldd_task = शून्य;
		sas_ata_पूर्णांकernal_पात(task);
	पूर्ण
पूर्ण


अटल व्योम sas_ata_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *ata_dev)
अणु
	काष्ठा करोमुख्य_device *dev = ap->निजी_data;
	काष्ठा sas_पूर्णांकernal *i = dev_to_sas_पूर्णांकernal(dev);

	अगर (i->dft->lldd_ata_set_dmamode)
		i->dft->lldd_ata_set_dmamode(dev);
पूर्ण

अटल व्योम sas_ata_sched_eh(काष्ठा ata_port *ap)
अणु
	काष्ठा करोमुख्य_device *dev = ap->निजी_data;
	काष्ठा sas_ha_काष्ठा *ha = dev->port->ha;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ha->lock, flags);
	अगर (!test_and_set_bit(SAS_DEV_EH_PENDING, &dev->state))
		ha->eh_active++;
	ata_std_sched_eh(ap);
	spin_unlock_irqrestore(&ha->lock, flags);
पूर्ण

व्योम sas_ata_end_eh(काष्ठा ata_port *ap)
अणु
	काष्ठा करोमुख्य_device *dev = ap->निजी_data;
	काष्ठा sas_ha_काष्ठा *ha = dev->port->ha;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ha->lock, flags);
	अगर (test_and_clear_bit(SAS_DEV_EH_PENDING, &dev->state))
		ha->eh_active--;
	spin_unlock_irqrestore(&ha->lock, flags);
पूर्ण

अटल पूर्णांक sas_ata_prereset(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा करोमुख्य_device *dev = ap->निजी_data;
	काष्ठा sas_phy *local_phy = sas_get_local_phy(dev);
	पूर्णांक res = 0;

	अगर (!local_phy->enabled || test_bit(SAS_DEV_GONE, &dev->state))
		res = -ENOENT;
	sas_put_local_phy(local_phy);

	वापस res;
पूर्ण

अटल काष्ठा ata_port_operations sas_sata_ops = अणु
	.prereset		= sas_ata_prereset,
	.hardreset		= sas_ata_hard_reset,
	.error_handler		= ata_std_error_handler,
	.post_पूर्णांकernal_cmd	= sas_ata_post_पूर्णांकernal,
	.qc_defer               = ata_std_qc_defer,
	.qc_prep		= ata_noop_qc_prep,
	.qc_issue		= sas_ata_qc_issue,
	.qc_fill_rtf		= sas_ata_qc_fill_rtf,
	.port_start		= ata_sas_port_start,
	.port_stop		= ata_sas_port_stop,
	.set_dmamode		= sas_ata_set_dmamode,
	.sched_eh		= sas_ata_sched_eh,
	.end_eh			= sas_ata_end_eh,
पूर्ण;

अटल काष्ठा ata_port_info sata_port_info = अणु
	.flags = ATA_FLAG_SATA | ATA_FLAG_PIO_DMA | ATA_FLAG_NCQ |
		 ATA_FLAG_SAS_HOST | ATA_FLAG_FPDMA_AUX,
	.pio_mask = ATA_PIO4,
	.mwdma_mask = ATA_MWDMA2,
	.udma_mask = ATA_UDMA6,
	.port_ops = &sas_sata_ops
पूर्ण;

पूर्णांक sas_ata_init(काष्ठा करोमुख्य_device *found_dev)
अणु
	काष्ठा sas_ha_काष्ठा *ha = found_dev->port->ha;
	काष्ठा Scsi_Host *shost = ha->core.shost;
	काष्ठा ata_host *ata_host;
	काष्ठा ata_port *ap;
	पूर्णांक rc;

	ata_host = kzalloc(माप(*ata_host), GFP_KERNEL);
	अगर (!ata_host)	अणु
		pr_err("ata host alloc failed.\n");
		वापस -ENOMEM;
	पूर्ण

	ata_host_init(ata_host, ha->dev, &sas_sata_ops);

	ap = ata_sas_port_alloc(ata_host, &sata_port_info, shost);
	अगर (!ap) अणु
		pr_err("ata_sas_port_alloc failed.\n");
		rc = -ENODEV;
		जाओ मुक्त_host;
	पूर्ण

	ap->निजी_data = found_dev;
	ap->cbl = ATA_CBL_SATA;
	ap->scsi_host = shost;
	rc = ata_sas_port_init(ap);
	अगर (rc)
		जाओ destroy_port;

	rc = ata_sas_tport_add(ata_host->dev, ap);
	अगर (rc)
		जाओ destroy_port;

	found_dev->sata_dev.ata_host = ata_host;
	found_dev->sata_dev.ap = ap;

	वापस 0;

destroy_port:
	ata_sas_port_destroy(ap);
मुक्त_host:
	ata_host_put(ata_host);
	वापस rc;
पूर्ण

व्योम sas_ata_task_पात(काष्ठा sas_task *task)
अणु
	काष्ठा ata_queued_cmd *qc = task->uldd_task;
	काष्ठा completion *रुकोing;

	/* Bounce SCSI-initiated commands to the SCSI EH */
	अगर (qc->scsicmd) अणु
		blk_पात_request(qc->scsicmd->request);
		वापस;
	पूर्ण

	/* Internal command, fake a समयout and complete. */
	qc->flags &= ~ATA_QCFLAG_ACTIVE;
	qc->flags |= ATA_QCFLAG_FAILED;
	qc->err_mask |= AC_ERR_TIMEOUT;
	रुकोing = qc->निजी_data;
	complete(रुकोing);
पूर्ण

अटल पूर्णांक sas_get_ata_command_set(काष्ठा करोमुख्य_device *dev)
अणु
	काष्ठा dev_to_host_fis *fis =
		(काष्ठा dev_to_host_fis *) dev->frame_rcvd;
	काष्ठा ata_taskfile tf;

	अगर (dev->dev_type == SAS_SATA_PENDING)
		वापस ATA_DEV_UNKNOWN;

	ata_tf_from_fis((स्थिर u8 *)fis, &tf);

	वापस ata_dev_classअगरy(&tf);
पूर्ण

व्योम sas_probe_sata(काष्ठा asd_sas_port *port)
अणु
	काष्ठा करोमुख्य_device *dev, *n;

	mutex_lock(&port->ha->disco_mutex);
	list_क्रम_each_entry(dev, &port->disco_list, disco_list_node) अणु
		अगर (!dev_is_sata(dev))
			जारी;

		ata_sas_async_probe(dev->sata_dev.ap);
	पूर्ण
	mutex_unlock(&port->ha->disco_mutex);

	list_क्रम_each_entry_safe(dev, n, &port->disco_list, disco_list_node) अणु
		अगर (!dev_is_sata(dev))
			जारी;

		sas_ata_रुको_eh(dev);

		/* अगर libata could not bring the link up, करोn't surface
		 * the device
		 */
		अगर (!ata_dev_enabled(sas_to_ata_dev(dev)))
			sas_fail_probe(dev, __func__, -ENODEV);
	पूर्ण

पूर्ण

अटल व्योम sas_ata_flush_pm_eh(काष्ठा asd_sas_port *port, स्थिर अक्षर *func)
अणु
	काष्ठा करोमुख्य_device *dev, *n;

	list_क्रम_each_entry_safe(dev, n, &port->dev_list, dev_list_node) अणु
		अगर (!dev_is_sata(dev))
			जारी;

		sas_ata_रुको_eh(dev);

		/* अगर libata failed to घातer manage the device, tear it करोwn */
		अगर (ata_dev_disabled(sas_to_ata_dev(dev)))
			sas_fail_probe(dev, func, -ENODEV);
	पूर्ण
पूर्ण

व्योम sas_suspend_sata(काष्ठा asd_sas_port *port)
अणु
	काष्ठा करोमुख्य_device *dev;

	mutex_lock(&port->ha->disco_mutex);
	list_क्रम_each_entry(dev, &port->dev_list, dev_list_node) अणु
		काष्ठा sata_device *sata;

		अगर (!dev_is_sata(dev))
			जारी;

		sata = &dev->sata_dev;
		अगर (sata->ap->pm_mesg.event == PM_EVENT_SUSPEND)
			जारी;

		ata_sas_port_suspend(sata->ap);
	पूर्ण
	mutex_unlock(&port->ha->disco_mutex);

	sas_ata_flush_pm_eh(port, __func__);
पूर्ण

व्योम sas_resume_sata(काष्ठा asd_sas_port *port)
अणु
	काष्ठा करोमुख्य_device *dev;

	mutex_lock(&port->ha->disco_mutex);
	list_क्रम_each_entry(dev, &port->dev_list, dev_list_node) अणु
		काष्ठा sata_device *sata;

		अगर (!dev_is_sata(dev))
			जारी;

		sata = &dev->sata_dev;
		अगर (sata->ap->pm_mesg.event == PM_EVENT_ON)
			जारी;

		ata_sas_port_resume(sata->ap);
	पूर्ण
	mutex_unlock(&port->ha->disco_mutex);

	sas_ata_flush_pm_eh(port, __func__);
पूर्ण

/**
 * sas_discover_sata - discover an STP/SATA करोमुख्य device
 * @dev: poपूर्णांकer to काष्ठा करोमुख्य_device of पूर्णांकerest
 *
 * Devices directly attached to a HA port, have no parents.  All other
 * devices करो, and should have their "parent" poपूर्णांकer set appropriately
 * beक्रमe calling this function.
 */
पूर्णांक sas_discover_sata(काष्ठा करोमुख्य_device *dev)
अणु
	अगर (dev->dev_type == SAS_SATA_PM)
		वापस -ENODEV;

	dev->sata_dev.class = sas_get_ata_command_set(dev);
	sas_fill_in_rphy(dev, dev->rphy);

	वापस sas_notअगरy_lldd_dev_found(dev);
पूर्ण

अटल व्योम async_sas_ata_eh(व्योम *data, async_cookie_t cookie)
अणु
	काष्ठा करोमुख्य_device *dev = data;
	काष्ठा ata_port *ap = dev->sata_dev.ap;
	काष्ठा sas_ha_काष्ठा *ha = dev->port->ha;

	sas_ata_prपूर्णांकk(KERN_DEBUG, dev, "dev error handler\n");
	ata_scsi_port_error_handler(ha->core.shost, ap);
	sas_put_device(dev);
पूर्ण

व्योम sas_ata_strategy_handler(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा sas_ha_काष्ठा *sas_ha = SHOST_TO_SAS_HA(shost);
	ASYNC_DOMAIN_EXCLUSIVE(async);
	पूर्णांक i;

	/* it's ok to defer revalidation events during ata eh, these
	 * disks are in one of three states:
	 * 1/ present क्रम initial करोमुख्य discovery, and these
	 *    resets will cause bcn flutters
	 * 2/ hot हटाओd, we'll discover that after eh fails
	 * 3/ hot added after initial discovery, lost the race, and need
	 *    to catch the next train.
	 */
	sas_disable_revalidation(sas_ha);

	spin_lock_irq(&sas_ha->phy_port_lock);
	क्रम (i = 0; i < sas_ha->num_phys; i++) अणु
		काष्ठा asd_sas_port *port = sas_ha->sas_port[i];
		काष्ठा करोमुख्य_device *dev;

		spin_lock(&port->dev_list_lock);
		list_क्रम_each_entry(dev, &port->dev_list, dev_list_node) अणु
			अगर (!dev_is_sata(dev))
				जारी;

			/* hold a reference over eh since we may be
			 * racing with final हटाओ once all commands
			 * are completed
			 */
			kref_get(&dev->kref);

			async_schedule_करोमुख्य(async_sas_ata_eh, dev, &async);
		पूर्ण
		spin_unlock(&port->dev_list_lock);
	पूर्ण
	spin_unlock_irq(&sas_ha->phy_port_lock);

	async_synchronize_full_करोमुख्य(&async);

	sas_enable_revalidation(sas_ha);
पूर्ण

व्योम sas_ata_eh(काष्ठा Scsi_Host *shost, काष्ठा list_head *work_q,
		काष्ठा list_head *करोne_q)
अणु
	काष्ठा scsi_cmnd *cmd, *n;
	काष्ठा करोमुख्य_device *eh_dev;

	करो अणु
		LIST_HEAD(sata_q);
		eh_dev = शून्य;

		list_क्रम_each_entry_safe(cmd, n, work_q, eh_entry) अणु
			काष्ठा करोमुख्य_device *ddev = cmd_to_करोमुख्य_dev(cmd);

			अगर (!dev_is_sata(ddev) || TO_SAS_TASK(cmd))
				जारी;
			अगर (eh_dev && eh_dev != ddev)
				जारी;
			eh_dev = ddev;
			list_move(&cmd->eh_entry, &sata_q);
		पूर्ण

		अगर (!list_empty(&sata_q)) अणु
			काष्ठा ata_port *ap = eh_dev->sata_dev.ap;

			sas_ata_prपूर्णांकk(KERN_DEBUG, eh_dev, "cmd error handler\n");
			ata_scsi_cmd_error_handler(shost, ap, &sata_q);
			/*
			 * ata's error handler may leave the cmd on the list
			 * so make sure they करोn't reमुख्य on a stack list
			 * about to go out of scope.
			 *
			 * This looks strange, since the commands are
			 * now part of no list, but the next error
			 * action will be ata_port_error_handler()
			 * which takes no list and sweeps them up
			 * anyway from the ata tag array.
			 */
			जबतक (!list_empty(&sata_q))
				list_del_init(sata_q.next);
		पूर्ण
	पूर्ण जबतक (eh_dev);
पूर्ण

व्योम sas_ata_schedule_reset(काष्ठा करोमुख्य_device *dev)
अणु
	काष्ठा ata_eh_info *ehi;
	काष्ठा ata_port *ap;
	अचिन्हित दीर्घ flags;

	अगर (!dev_is_sata(dev))
		वापस;

	ap = dev->sata_dev.ap;
	ehi = &ap->link.eh_info;

	spin_lock_irqsave(ap->lock, flags);
	ehi->err_mask |= AC_ERR_TIMEOUT;
	ehi->action |= ATA_EH_RESET;
	ata_port_schedule_eh(ap);
	spin_unlock_irqrestore(ap->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(sas_ata_schedule_reset);

व्योम sas_ata_रुको_eh(काष्ठा करोमुख्य_device *dev)
अणु
	काष्ठा ata_port *ap;

	अगर (!dev_is_sata(dev))
		वापस;

	ap = dev->sata_dev.ap;
	ata_port_रुको_eh(ap);
पूर्ण
