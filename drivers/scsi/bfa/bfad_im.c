<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2005-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014- QLogic Corporation.
 * All rights reserved
 * www.qlogic.com
 *
 * Linux driver क्रम QLogic BR-series Fibre Channel Host Bus Adapter.
 */

/*
 *  bfad_im.c Linux driver IM module.
 */

#समावेश <linux/export.h>

#समावेश "bfad_drv.h"
#समावेश "bfad_im.h"
#समावेश "bfa_fcs.h"

BFA_TRC_खाता(LDRV, IM);

DEFINE_IDR(bfad_im_port_index);
काष्ठा scsi_transport_ढाँचा *bfad_im_scsi_transport_ढाँचा;
काष्ठा scsi_transport_ढाँचा *bfad_im_scsi_vport_transport_ढाँचा;
अटल व्योम bfad_im_itnim_work_handler(काष्ठा work_काष्ठा *work);
अटल पूर्णांक bfad_im_queuecommand(काष्ठा Scsi_Host *h, काष्ठा scsi_cmnd *cmnd);
अटल पूर्णांक bfad_im_slave_alloc(काष्ठा scsi_device *sdev);
अटल व्योम bfad_im_fc_rport_add(काष्ठा bfad_im_port_s  *im_port,
				काष्ठा bfad_itnim_s *itnim);

व्योम
bfa_cb_ioim_करोne(व्योम *drv, काष्ठा bfad_ioim_s *dio,
			क्रमागत bfi_ioim_status io_status, u8 scsi_status,
			पूर्णांक sns_len, u8 *sns_info, s32 residue)
अणु
	काष्ठा scsi_cmnd *cmnd = (काष्ठा scsi_cmnd *)dio;
	काष्ठा bfad_s         *bfad = drv;
	काष्ठा bfad_itnim_data_s *itnim_data;
	काष्ठा bfad_itnim_s *itnim;
	u8         host_status = DID_OK;

	चयन (io_status) अणु
	हाल BFI_IOIM_STS_OK:
		bfa_trc(bfad, scsi_status);
		scsi_set_resid(cmnd, 0);

		अगर (sns_len > 0) अणु
			bfa_trc(bfad, sns_len);
			अगर (sns_len > SCSI_SENSE_BUFFERSIZE)
				sns_len = SCSI_SENSE_BUFFERSIZE;
			स_नकल(cmnd->sense_buffer, sns_info, sns_len);
		पूर्ण

		अगर (residue > 0) अणु
			bfa_trc(bfad, residue);
			scsi_set_resid(cmnd, residue);
			अगर (!sns_len && (scsi_status == SAM_STAT_GOOD) &&
				(scsi_bufflen(cmnd) - residue) <
					cmnd->underflow) अणु
				bfa_trc(bfad, 0);
				host_status = DID_ERROR;
			पूर्ण
		पूर्ण
		cmnd->result = host_status << 16 | scsi_status;

		अवरोध;

	हाल BFI_IOIM_STS_TIMEDOUT:
		cmnd->result = DID_TIME_OUT << 16;
		अवरोध;
	हाल BFI_IOIM_STS_PATHTOV:
		cmnd->result = DID_TRANSPORT_DISRUPTED << 16;
		अवरोध;
	शेष:
		cmnd->result = DID_ERROR << 16;
	पूर्ण

	/* Unmap DMA, अगर host is शून्य, it means a scsi passthru cmd */
	अगर (cmnd->device->host != शून्य)
		scsi_dma_unmap(cmnd);

	cmnd->host_scribble = शून्य;
	bfa_trc(bfad, cmnd->result);

	itnim_data = cmnd->device->hostdata;
	अगर (itnim_data) अणु
		itnim = itnim_data->itnim;
		अगर (!cmnd->result && itnim &&
			 (bfa_lun_queue_depth > cmnd->device->queue_depth)) अणु
			/* Queue depth adjusपंचांगent क्रम good status completion */
			bfad_ramp_up_qdepth(itnim, cmnd->device);
		पूर्ण अन्यथा अगर (cmnd->result == SAM_STAT_TASK_SET_FULL && itnim) अणु
			/* qfull handling */
			bfad_handle_qfull(itnim, cmnd->device);
		पूर्ण
	पूर्ण

	cmnd->scsi_करोne(cmnd);
पूर्ण

व्योम
bfa_cb_ioim_good_comp(व्योम *drv, काष्ठा bfad_ioim_s *dio)
अणु
	काष्ठा scsi_cmnd *cmnd = (काष्ठा scsi_cmnd *)dio;
	काष्ठा bfad_itnim_data_s *itnim_data;
	काष्ठा bfad_itnim_s *itnim;

	cmnd->result = DID_OK << 16 | SAM_STAT_GOOD;

	/* Unmap DMA, अगर host is शून्य, it means a scsi passthru cmd */
	अगर (cmnd->device->host != शून्य)
		scsi_dma_unmap(cmnd);

	cmnd->host_scribble = शून्य;

	/* Queue depth adjusपंचांगent */
	अगर (bfa_lun_queue_depth > cmnd->device->queue_depth) अणु
		itnim_data = cmnd->device->hostdata;
		अगर (itnim_data) अणु
			itnim = itnim_data->itnim;
			अगर (itnim)
				bfad_ramp_up_qdepth(itnim, cmnd->device);
		पूर्ण
	पूर्ण

	cmnd->scsi_करोne(cmnd);
पूर्ण

व्योम
bfa_cb_ioim_पात(व्योम *drv, काष्ठा bfad_ioim_s *dio)
अणु
	काष्ठा scsi_cmnd *cmnd = (काष्ठा scsi_cmnd *)dio;
	काष्ठा bfad_s         *bfad = drv;

	cmnd->result = DID_ERROR << 16;

	/* Unmap DMA, अगर host is शून्य, it means a scsi passthru cmd */
	अगर (cmnd->device->host != शून्य)
		scsi_dma_unmap(cmnd);

	bfa_trc(bfad, cmnd->result);
	cmnd->host_scribble = शून्य;
पूर्ण

व्योम
bfa_cb_tskim_करोne(व्योम *bfad, काष्ठा bfad_tskim_s *dtsk,
		   क्रमागत bfi_tskim_status tsk_status)
अणु
	काष्ठा scsi_cmnd *cmnd = (काष्ठा scsi_cmnd *)dtsk;
	रुको_queue_head_t *wq;

	cmnd->SCp.Status |= tsk_status << 1;
	set_bit(IO_DONE_BIT, (अचिन्हित दीर्घ *)&cmnd->SCp.Status);
	wq = (रुको_queue_head_t *) cmnd->SCp.ptr;
	cmnd->SCp.ptr = शून्य;

	अगर (wq)
		wake_up(wq);
पूर्ण

/*
 *  Scsi_Host_ढाँचा SCSI host ढाँचा
 */
/*
 * Scsi_Host ढाँचा entry, वापसs BFAD PCI info.
 */
अटल स्थिर अक्षर *
bfad_im_info(काष्ठा Scsi_Host *shost)
अणु
	अटल अक्षर     bfa_buf[256];
	काष्ठा bfad_im_port_s *im_port =
			(काष्ठा bfad_im_port_s *) shost->hostdata[0];
	काष्ठा bfad_s *bfad = im_port->bfad;

	स_रखो(bfa_buf, 0, माप(bfa_buf));
	snम_लिखो(bfa_buf, माप(bfa_buf),
		"QLogic BR-series FC/FCOE Adapter, hwpath: %s driver: %s",
		bfad->pci_name, BFAD_DRIVER_VERSION);

	वापस bfa_buf;
पूर्ण

/*
 * Scsi_Host ढाँचा entry, पातs the specअगरied SCSI command.
 *
 * Returns: SUCCESS or FAILED.
 */
अटल पूर्णांक
bfad_im_पात_handler(काष्ठा scsi_cmnd *cmnd)
अणु
	काष्ठा Scsi_Host *shost = cmnd->device->host;
	काष्ठा bfad_im_port_s *im_port =
			(काष्ठा bfad_im_port_s *) shost->hostdata[0];
	काष्ठा bfad_s         *bfad = im_port->bfad;
	काष्ठा bfa_ioim_s *hal_io;
	अचिन्हित दीर्घ   flags;
	u32        समयout;
	पूर्णांक             rc = FAILED;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	hal_io = (काष्ठा bfa_ioim_s *) cmnd->host_scribble;
	अगर (!hal_io) अणु
		/* IO has been completed, वापस success */
		rc = SUCCESS;
		जाओ out;
	पूर्ण
	अगर (hal_io->dio != (काष्ठा bfad_ioim_s *) cmnd) अणु
		rc = FAILED;
		जाओ out;
	पूर्ण

	bfa_trc(bfad, hal_io->iotag);
	BFA_LOG(KERN_INFO, bfad, bfa_log_level,
		"scsi%d: abort cmnd %p iotag %x\n",
		im_port->shost->host_no, cmnd, hal_io->iotag);
	(व्योम) bfa_ioim_पात(hal_io);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	/* Need to रुको until the command get पातed */
	समयout = 10;
	जबतक ((काष्ठा bfa_ioim_s *) cmnd->host_scribble == hal_io) अणु
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_समयout(समयout);
		अगर (समयout < 4 * HZ)
			समयout *= 2;
	पूर्ण

	cmnd->scsi_करोne(cmnd);
	bfa_trc(bfad, hal_io->iotag);
	BFA_LOG(KERN_INFO, bfad, bfa_log_level,
		"scsi%d: complete abort 0x%p iotag 0x%x\n",
		im_port->shost->host_no, cmnd, hal_io->iotag);
	वापस SUCCESS;
out:
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	वापस rc;
पूर्ण

अटल bfa_status_t
bfad_im_target_reset_send(काष्ठा bfad_s *bfad, काष्ठा scsi_cmnd *cmnd,
		     काष्ठा bfad_itnim_s *itnim)
अणु
	काष्ठा bfa_tskim_s *tskim;
	काष्ठा bfa_itnim_s *bfa_itnim;
	bfa_status_t    rc = BFA_STATUS_OK;
	काष्ठा scsi_lun scsilun;

	tskim = bfa_tskim_alloc(&bfad->bfa, (काष्ठा bfad_tskim_s *) cmnd);
	अगर (!tskim) अणु
		BFA_LOG(KERN_ERR, bfad, bfa_log_level,
			"target reset, fail to allocate tskim\n");
		rc = BFA_STATUS_FAILED;
		जाओ out;
	पूर्ण

	/*
	 * Set host_scribble to शून्य to aव्योम पातing a task command अगर
	 * happens.
	 */
	cmnd->host_scribble = शून्य;
	cmnd->SCp.Status = 0;
	bfa_itnim = bfa_fcs_itnim_get_halitn(&itnim->fcs_itnim);
	/*
	 * bfa_itnim can be शून्य अगर the port माला_लो disconnected and the bfa
	 * and fcs layers have cleaned up their nexus with the tarमाला_लो and
	 * the same has not been cleaned up by the shim
	 */
	अगर (bfa_itnim == शून्य) अणु
		bfa_tskim_मुक्त(tskim);
		BFA_LOG(KERN_ERR, bfad, bfa_log_level,
			"target reset, bfa_itnim is NULL\n");
		rc = BFA_STATUS_FAILED;
		जाओ out;
	पूर्ण

	स_रखो(&scsilun, 0, माप(scsilun));
	bfa_tskim_start(tskim, bfa_itnim, scsilun,
			    FCP_TM_TARGET_RESET, BFAD_TARGET_RESET_TMO);
out:
	वापस rc;
पूर्ण

/*
 * Scsi_Host ढाँचा entry, resets a LUN and पात its all commands.
 *
 * Returns: SUCCESS or FAILED.
 *
 */
अटल पूर्णांक
bfad_im_reset_lun_handler(काष्ठा scsi_cmnd *cmnd)
अणु
	काष्ठा Scsi_Host *shost = cmnd->device->host;
	काष्ठा bfad_im_port_s *im_port =
			(काष्ठा bfad_im_port_s *) shost->hostdata[0];
	काष्ठा bfad_itnim_data_s *itnim_data = cmnd->device->hostdata;
	काष्ठा bfad_s         *bfad = im_port->bfad;
	काष्ठा bfa_tskim_s *tskim;
	काष्ठा bfad_itnim_s   *itnim;
	काष्ठा bfa_itnim_s *bfa_itnim;
	DECLARE_WAIT_QUEUE_HEAD_ONSTACK(wq);
	पूर्णांक             rc = SUCCESS;
	अचिन्हित दीर्घ   flags;
	क्रमागत bfi_tskim_status task_status;
	काष्ठा scsi_lun scsilun;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	itnim = itnim_data->itnim;
	अगर (!itnim) अणु
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		rc = FAILED;
		जाओ out;
	पूर्ण

	tskim = bfa_tskim_alloc(&bfad->bfa, (काष्ठा bfad_tskim_s *) cmnd);
	अगर (!tskim) अणु
		BFA_LOG(KERN_ERR, bfad, bfa_log_level,
				"LUN reset, fail to allocate tskim");
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		rc = FAILED;
		जाओ out;
	पूर्ण

	/*
	 * Set host_scribble to शून्य to aव्योम पातing a task command
	 * अगर happens.
	 */
	cmnd->host_scribble = शून्य;
	cmnd->SCp.ptr = (अक्षर *)&wq;
	cmnd->SCp.Status = 0;
	bfa_itnim = bfa_fcs_itnim_get_halitn(&itnim->fcs_itnim);
	/*
	 * bfa_itnim can be शून्य अगर the port माला_लो disconnected and the bfa
	 * and fcs layers have cleaned up their nexus with the tarमाला_लो and
	 * the same has not been cleaned up by the shim
	 */
	अगर (bfa_itnim == शून्य) अणु
		bfa_tskim_मुक्त(tskim);
		BFA_LOG(KERN_ERR, bfad, bfa_log_level,
			"lun reset, bfa_itnim is NULL\n");
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		rc = FAILED;
		जाओ out;
	पूर्ण
	पूर्णांक_to_scsilun(cmnd->device->lun, &scsilun);
	bfa_tskim_start(tskim, bfa_itnim, scsilun,
			    FCP_TM_LUN_RESET, BFAD_LUN_RESET_TMO);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	रुको_event(wq, test_bit(IO_DONE_BIT,
			(अचिन्हित दीर्घ *)&cmnd->SCp.Status));

	task_status = cmnd->SCp.Status >> 1;
	अगर (task_status != BFI_TSKIM_STS_OK) अणु
		BFA_LOG(KERN_ERR, bfad, bfa_log_level,
			"LUN reset failure, status: %d\n", task_status);
		rc = FAILED;
	पूर्ण

out:
	वापस rc;
पूर्ण

/*
 * Scsi_Host ढाँचा entry, resets the target and पात all commands.
 */
अटल पूर्णांक
bfad_im_reset_target_handler(काष्ठा scsi_cmnd *cmnd)
अणु
	काष्ठा Scsi_Host *shost = cmnd->device->host;
	काष्ठा scsi_target *starget = scsi_target(cmnd->device);
	काष्ठा bfad_im_port_s *im_port =
				(काष्ठा bfad_im_port_s *) shost->hostdata[0];
	काष्ठा bfad_s         *bfad = im_port->bfad;
	काष्ठा bfad_itnim_s   *itnim;
	अचिन्हित दीर्घ   flags;
	u32        rc, rtn = FAILED;
	DECLARE_WAIT_QUEUE_HEAD_ONSTACK(wq);
	क्रमागत bfi_tskim_status task_status;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	itnim = bfad_get_itnim(im_port, starget->id);
	अगर (itnim) अणु
		cmnd->SCp.ptr = (अक्षर *)&wq;
		rc = bfad_im_target_reset_send(bfad, cmnd, itnim);
		अगर (rc == BFA_STATUS_OK) अणु
			/* रुको target reset to complete */
			spin_unlock_irqrestore(&bfad->bfad_lock, flags);
			रुको_event(wq, test_bit(IO_DONE_BIT,
					(अचिन्हित दीर्घ *)&cmnd->SCp.Status));
			spin_lock_irqsave(&bfad->bfad_lock, flags);

			task_status = cmnd->SCp.Status >> 1;
			अगर (task_status != BFI_TSKIM_STS_OK)
				BFA_LOG(KERN_ERR, bfad, bfa_log_level,
					"target reset failure,"
					" status: %d\n", task_status);
			अन्यथा
				rtn = SUCCESS;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	वापस rtn;
पूर्ण

/*
 * Scsi_Host ढाँचा entry slave_destroy.
 */
अटल व्योम
bfad_im_slave_destroy(काष्ठा scsi_device *sdev)
अणु
	sdev->hostdata = शून्य;
	वापस;
पूर्ण

/*
 *  BFA FCS itnim callbacks
 */

/*
 * BFA FCS itnim alloc callback, after successful PRLI
 * Context: Interrupt
 */
पूर्णांक
bfa_fcb_itnim_alloc(काष्ठा bfad_s *bfad, काष्ठा bfa_fcs_itnim_s **itnim,
		    काष्ठा bfad_itnim_s **itnim_drv)
अणु
	*itnim_drv = kzalloc(माप(काष्ठा bfad_itnim_s), GFP_ATOMIC);
	अगर (*itnim_drv == शून्य)
		वापस -ENOMEM;

	(*itnim_drv)->im = bfad->im;
	*itnim = &(*itnim_drv)->fcs_itnim;
	(*itnim_drv)->state = ITNIM_STATE_NONE;

	/*
	 * Initiaze the itnim_work
	 */
	INIT_WORK(&(*itnim_drv)->itnim_work, bfad_im_itnim_work_handler);
	bfad->bfad_flags |= BFAD_RPORT_ONLINE;
	वापस 0;
पूर्ण

/*
 * BFA FCS itnim मुक्त callback.
 * Context: Interrupt. bfad_lock is held
 */
व्योम
bfa_fcb_itnim_मुक्त(काष्ठा bfad_s *bfad, काष्ठा bfad_itnim_s *itnim_drv)
अणु
	काष्ठा bfad_port_s    *port;
	wwn_t wwpn;
	u32 fcid;
	अक्षर wwpn_str[32], fcid_str[16];
	काष्ठा bfad_im_s	*im = itnim_drv->im;

	/* online to मुक्त state transtion should not happen */
	WARN_ON(itnim_drv->state == ITNIM_STATE_ONLINE);

	itnim_drv->queue_work = 1;
	/* offline request is not yet करोne, use the same request to मुक्त */
	अगर (itnim_drv->state == ITNIM_STATE_OFFLINE_PENDING)
		itnim_drv->queue_work = 0;

	itnim_drv->state = ITNIM_STATE_FREE;
	port = bfa_fcs_itnim_get_drvport(&itnim_drv->fcs_itnim);
	itnim_drv->im_port = port->im_port;
	wwpn = bfa_fcs_itnim_get_pwwn(&itnim_drv->fcs_itnim);
	fcid = bfa_fcs_itnim_get_fcid(&itnim_drv->fcs_itnim);
	wwn2str(wwpn_str, wwpn);
	fcid2str(fcid_str, fcid);
	BFA_LOG(KERN_INFO, bfad, bfa_log_level,
		"ITNIM FREE scsi%d: FCID: %s WWPN: %s\n",
		port->im_port->shost->host_no,
		fcid_str, wwpn_str);

	/* ITNIM processing */
	अगर (itnim_drv->queue_work)
		queue_work(im->drv_workq, &itnim_drv->itnim_work);
पूर्ण

/*
 * BFA FCS itnim online callback.
 * Context: Interrupt. bfad_lock is held
 */
व्योम
bfa_fcb_itnim_online(काष्ठा bfad_itnim_s *itnim_drv)
अणु
	काष्ठा bfad_port_s    *port;
	काष्ठा bfad_im_s	*im = itnim_drv->im;

	itnim_drv->bfa_itnim = bfa_fcs_itnim_get_halitn(&itnim_drv->fcs_itnim);
	port = bfa_fcs_itnim_get_drvport(&itnim_drv->fcs_itnim);
	itnim_drv->state = ITNIM_STATE_ONLINE;
	itnim_drv->queue_work = 1;
	itnim_drv->im_port = port->im_port;

	/* ITNIM processing */
	अगर (itnim_drv->queue_work)
		queue_work(im->drv_workq, &itnim_drv->itnim_work);
पूर्ण

/*
 * BFA FCS itnim offline callback.
 * Context: Interrupt. bfad_lock is held
 */
व्योम
bfa_fcb_itnim_offline(काष्ठा bfad_itnim_s *itnim_drv)
अणु
	काष्ठा bfad_port_s    *port;
	काष्ठा bfad_s *bfad;
	काष्ठा bfad_im_s	*im = itnim_drv->im;

	port = bfa_fcs_itnim_get_drvport(&itnim_drv->fcs_itnim);
	bfad = port->bfad;
	अगर ((bfad->pport.flags & BFAD_PORT_DELETE) ||
		 (port->flags & BFAD_PORT_DELETE)) अणु
		itnim_drv->state = ITNIM_STATE_OFFLINE;
		वापस;
	पूर्ण
	itnim_drv->im_port = port->im_port;
	itnim_drv->state = ITNIM_STATE_OFFLINE_PENDING;
	itnim_drv->queue_work = 1;

	/* ITNIM processing */
	अगर (itnim_drv->queue_work)
		queue_work(im->drv_workq, &itnim_drv->itnim_work);
पूर्ण

/*
 * Allocate a Scsi_Host क्रम a port.
 */
पूर्णांक
bfad_im_scsi_host_alloc(काष्ठा bfad_s *bfad, काष्ठा bfad_im_port_s *im_port,
			काष्ठा device *dev)
अणु
	काष्ठा bfad_im_port_poपूर्णांकer *im_portp;
	पूर्णांक error;

	mutex_lock(&bfad_mutex);
	error = idr_alloc(&bfad_im_port_index, im_port, 0, 0, GFP_KERNEL);
	अगर (error < 0) अणु
		mutex_unlock(&bfad_mutex);
		prपूर्णांकk(KERN_WARNING "idr_alloc failure\n");
		जाओ out;
	पूर्ण
	im_port->idr_id = error;
	mutex_unlock(&bfad_mutex);

	im_port->shost = bfad_scsi_host_alloc(im_port, bfad);
	अगर (!im_port->shost) अणु
		error = 1;
		जाओ out_मुक्त_idr;
	पूर्ण

	im_portp = shost_priv(im_port->shost);
	im_portp->p = im_port;
	im_port->shost->unique_id = im_port->idr_id;
	im_port->shost->this_id = -1;
	im_port->shost->max_id = MAX_FCP_TARGET;
	im_port->shost->max_lun = MAX_FCP_LUN;
	im_port->shost->max_cmd_len = 16;
	im_port->shost->can_queue = bfad->cfg_data.ioc_queue_depth;
	अगर (im_port->port->pvb_type == BFAD_PORT_PHYS_BASE)
		im_port->shost->transportt = bfad_im_scsi_transport_ढाँचा;
	अन्यथा
		im_port->shost->transportt =
				bfad_im_scsi_vport_transport_ढाँचा;

	error = scsi_add_host_with_dma(im_port->shost, dev, &bfad->pcidev->dev);
	अगर (error) अणु
		prपूर्णांकk(KERN_WARNING "scsi_add_host failure %d\n", error);
		जाओ out_fc_rel;
	पूर्ण

	वापस 0;

out_fc_rel:
	scsi_host_put(im_port->shost);
	im_port->shost = शून्य;
out_मुक्त_idr:
	mutex_lock(&bfad_mutex);
	idr_हटाओ(&bfad_im_port_index, im_port->idr_id);
	mutex_unlock(&bfad_mutex);
out:
	वापस error;
पूर्ण

व्योम
bfad_im_scsi_host_मुक्त(काष्ठा bfad_s *bfad, काष्ठा bfad_im_port_s *im_port)
अणु
	bfa_trc(bfad, bfad->inst_no);
	BFA_LOG(KERN_INFO, bfad, bfa_log_level, "Free scsi%d\n",
			im_port->shost->host_no);

	fc_हटाओ_host(im_port->shost);

	scsi_हटाओ_host(im_port->shost);
	scsi_host_put(im_port->shost);

	mutex_lock(&bfad_mutex);
	idr_हटाओ(&bfad_im_port_index, im_port->idr_id);
	mutex_unlock(&bfad_mutex);
पूर्ण

अटल व्योम
bfad_im_port_delete_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bfad_im_port_s *im_port =
		container_of(work, काष्ठा bfad_im_port_s, port_delete_work);

	अगर (im_port->port->pvb_type != BFAD_PORT_PHYS_BASE) अणु
		im_port->flags |= BFAD_PORT_DELETE;
		fc_vport_terminate(im_port->fc_vport);
	पूर्ण
पूर्ण

bfa_status_t
bfad_im_port_new(काष्ठा bfad_s *bfad, काष्ठा bfad_port_s *port)
अणु
	पूर्णांक             rc = BFA_STATUS_OK;
	काष्ठा bfad_im_port_s *im_port;

	im_port = kzalloc(माप(काष्ठा bfad_im_port_s), GFP_ATOMIC);
	अगर (im_port == शून्य) अणु
		rc = BFA_STATUS_ENOMEM;
		जाओ ext;
	पूर्ण
	port->im_port = im_port;
	im_port->port = port;
	im_port->bfad = bfad;

	INIT_WORK(&im_port->port_delete_work, bfad_im_port_delete_handler);
	INIT_LIST_HEAD(&im_port->itnim_mapped_list);
	INIT_LIST_HEAD(&im_port->binding_list);

ext:
	वापस rc;
पूर्ण

व्योम
bfad_im_port_delete(काष्ठा bfad_s *bfad, काष्ठा bfad_port_s *port)
अणु
	काष्ठा bfad_im_port_s *im_port = port->im_port;

	queue_work(bfad->im->drv_workq,
				&im_port->port_delete_work);
पूर्ण

व्योम
bfad_im_port_clean(काष्ठा bfad_im_port_s *im_port)
अणु
	काष्ठा bfad_fcp_binding *bp, *bp_new;
	अचिन्हित दीर्घ flags;
	काष्ठा bfad_s *bfad =  im_port->bfad;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	list_क्रम_each_entry_safe(bp, bp_new, &im_port->binding_list,
					list_entry) अणु
		list_del(&bp->list_entry);
		kमुक्त(bp);
	पूर्ण

	/* the itnim_mapped_list must be empty at this समय */
	WARN_ON(!list_empty(&im_port->itnim_mapped_list));

	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
पूर्ण

अटल व्योम bfad_aen_im_notअगरy_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bfad_im_s *im =
		container_of(work, काष्ठा bfad_im_s, aen_im_notअगरy_work);
	काष्ठा bfa_aen_entry_s *aen_entry;
	काष्ठा bfad_s *bfad = im->bfad;
	काष्ठा Scsi_Host *shost = bfad->pport.im_port->shost;
	व्योम *event_data;
	अचिन्हित दीर्घ flags;

	जबतक (!list_empty(&bfad->active_aen_q)) अणु
		spin_lock_irqsave(&bfad->bfad_aen_spinlock, flags);
		bfa_q_deq(&bfad->active_aen_q, &aen_entry);
		spin_unlock_irqrestore(&bfad->bfad_aen_spinlock, flags);
		event_data = (अक्षर *)aen_entry + माप(काष्ठा list_head);
		fc_host_post_venकरोr_event(shost, fc_get_event_number(),
				माप(काष्ठा bfa_aen_entry_s) -
				माप(काष्ठा list_head),
				(अक्षर *)event_data, BFAD_NL_VENDOR_ID);
		spin_lock_irqsave(&bfad->bfad_aen_spinlock, flags);
		list_add_tail(&aen_entry->qe, &bfad->मुक्त_aen_q);
		spin_unlock_irqrestore(&bfad->bfad_aen_spinlock, flags);
	पूर्ण
पूर्ण

bfa_status_t
bfad_im_probe(काष्ठा bfad_s *bfad)
अणु
	काष्ठा bfad_im_s      *im;

	im = kzalloc(माप(काष्ठा bfad_im_s), GFP_KERNEL);
	अगर (im == शून्य)
		वापस BFA_STATUS_ENOMEM;

	bfad->im = im;
	im->bfad = bfad;

	अगर (bfad_thपढ़ो_workq(bfad) != BFA_STATUS_OK) अणु
		kमुक्त(im);
		वापस BFA_STATUS_FAILED;
	पूर्ण

	INIT_WORK(&im->aen_im_notअगरy_work, bfad_aen_im_notअगरy_handler);
	वापस BFA_STATUS_OK;
पूर्ण

व्योम
bfad_im_probe_unकरो(काष्ठा bfad_s *bfad)
अणु
	अगर (bfad->im) अणु
		bfad_destroy_workq(bfad->im);
		kमुक्त(bfad->im);
		bfad->im = शून्य;
	पूर्ण
पूर्ण

काष्ठा Scsi_Host *
bfad_scsi_host_alloc(काष्ठा bfad_im_port_s *im_port, काष्ठा bfad_s *bfad)
अणु
	काष्ठा scsi_host_ढाँचा *sht;

	अगर (im_port->port->pvb_type == BFAD_PORT_PHYS_BASE)
		sht = &bfad_im_scsi_host_ढाँचा;
	अन्यथा
		sht = &bfad_im_vport_ढाँचा;

	अगर (max_xfer_size != BFAD_MAX_SECTORS >> 1)
		sht->max_sectors = max_xfer_size << 1;

	sht->sg_tablesize = bfad->cfg_data.io_max_sge;

	वापस scsi_host_alloc(sht, माप(काष्ठा bfad_im_port_poपूर्णांकer));
पूर्ण

व्योम
bfad_scsi_host_मुक्त(काष्ठा bfad_s *bfad, काष्ठा bfad_im_port_s *im_port)
अणु
	अगर (!(im_port->flags & BFAD_PORT_DELETE))
		flush_workqueue(bfad->im->drv_workq);
	bfad_im_scsi_host_मुक्त(im_port->bfad, im_port);
	bfad_im_port_clean(im_port);
	kमुक्त(im_port);
पूर्ण

व्योम
bfad_destroy_workq(काष्ठा bfad_im_s *im)
अणु
	अगर (im && im->drv_workq) अणु
		flush_workqueue(im->drv_workq);
		destroy_workqueue(im->drv_workq);
		im->drv_workq = शून्य;
	पूर्ण
पूर्ण

bfa_status_t
bfad_thपढ़ो_workq(काष्ठा bfad_s *bfad)
अणु
	काष्ठा bfad_im_s      *im = bfad->im;

	bfa_trc(bfad, 0);
	snम_लिखो(im->drv_workq_name, KOBJ_NAME_LEN, "bfad_wq_%d",
		 bfad->inst_no);
	im->drv_workq = create_singlethपढ़ो_workqueue(im->drv_workq_name);
	अगर (!im->drv_workq)
		वापस BFA_STATUS_FAILED;

	वापस BFA_STATUS_OK;
पूर्ण

/*
 * Scsi_Host ढाँचा entry.
 *
 * Description:
 * OS entry poपूर्णांक to adjust the queue_depths on a per-device basis.
 * Called once per device during the bus scan.
 * Return non-zero अगर fails.
 */
अटल पूर्णांक
bfad_im_slave_configure(काष्ठा scsi_device *sdev)
अणु
	scsi_change_queue_depth(sdev, bfa_lun_queue_depth);
	वापस 0;
पूर्ण

काष्ठा scsi_host_ढाँचा bfad_im_scsi_host_ढाँचा = अणु
	.module = THIS_MODULE,
	.name = BFAD_DRIVER_NAME,
	.info = bfad_im_info,
	.queuecommand = bfad_im_queuecommand,
	.eh_समयd_out = fc_eh_समयd_out,
	.eh_पात_handler = bfad_im_पात_handler,
	.eh_device_reset_handler = bfad_im_reset_lun_handler,
	.eh_target_reset_handler = bfad_im_reset_target_handler,

	.slave_alloc = bfad_im_slave_alloc,
	.slave_configure = bfad_im_slave_configure,
	.slave_destroy = bfad_im_slave_destroy,

	.this_id = -1,
	.sg_tablesize = BFAD_IO_MAX_SGE,
	.cmd_per_lun = 3,
	.shost_attrs = bfad_im_host_attrs,
	.max_sectors = BFAD_MAX_SECTORS,
	.venकरोr_id = BFA_PCI_VENDOR_ID_BROCADE,
पूर्ण;

काष्ठा scsi_host_ढाँचा bfad_im_vport_ढाँचा = अणु
	.module = THIS_MODULE,
	.name = BFAD_DRIVER_NAME,
	.info = bfad_im_info,
	.queuecommand = bfad_im_queuecommand,
	.eh_समयd_out = fc_eh_समयd_out,
	.eh_पात_handler = bfad_im_पात_handler,
	.eh_device_reset_handler = bfad_im_reset_lun_handler,
	.eh_target_reset_handler = bfad_im_reset_target_handler,

	.slave_alloc = bfad_im_slave_alloc,
	.slave_configure = bfad_im_slave_configure,
	.slave_destroy = bfad_im_slave_destroy,

	.this_id = -1,
	.sg_tablesize = BFAD_IO_MAX_SGE,
	.cmd_per_lun = 3,
	.shost_attrs = bfad_im_vport_attrs,
	.max_sectors = BFAD_MAX_SECTORS,
पूर्ण;

bfa_status_t
bfad_im_module_init(व्योम)
अणु
	bfad_im_scsi_transport_ढाँचा =
		fc_attach_transport(&bfad_im_fc_function_ढाँचा);
	अगर (!bfad_im_scsi_transport_ढाँचा)
		वापस BFA_STATUS_ENOMEM;

	bfad_im_scsi_vport_transport_ढाँचा =
		fc_attach_transport(&bfad_im_vport_fc_function_ढाँचा);
	अगर (!bfad_im_scsi_vport_transport_ढाँचा) अणु
		fc_release_transport(bfad_im_scsi_transport_ढाँचा);
		वापस BFA_STATUS_ENOMEM;
	पूर्ण

	वापस BFA_STATUS_OK;
पूर्ण

व्योम
bfad_im_module_निकास(व्योम)
अणु
	अगर (bfad_im_scsi_transport_ढाँचा)
		fc_release_transport(bfad_im_scsi_transport_ढाँचा);

	अगर (bfad_im_scsi_vport_transport_ढाँचा)
		fc_release_transport(bfad_im_scsi_vport_transport_ढाँचा);

	idr_destroy(&bfad_im_port_index);
पूर्ण

व्योम
bfad_ramp_up_qdepth(काष्ठा bfad_itnim_s *itnim, काष्ठा scsi_device *sdev)
अणु
	काष्ठा scsi_device *पंचांगp_sdev;

	अगर (((jअगरfies - itnim->last_ramp_up_समय) >
		BFA_QUEUE_FULL_RAMP_UP_TIME * HZ) &&
		((jअगरfies - itnim->last_queue_full_समय) >
		BFA_QUEUE_FULL_RAMP_UP_TIME * HZ)) अणु
		shost_क्रम_each_device(पंचांगp_sdev, sdev->host) अणु
			अगर (bfa_lun_queue_depth > पंचांगp_sdev->queue_depth) अणु
				अगर (पंचांगp_sdev->id != sdev->id)
					जारी;
				scsi_change_queue_depth(पंचांगp_sdev,
					पंचांगp_sdev->queue_depth + 1);

				itnim->last_ramp_up_समय = jअगरfies;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम
bfad_handle_qfull(काष्ठा bfad_itnim_s *itnim, काष्ठा scsi_device *sdev)
अणु
	काष्ठा scsi_device *पंचांगp_sdev;

	itnim->last_queue_full_समय = jअगरfies;

	shost_क्रम_each_device(पंचांगp_sdev, sdev->host) अणु
		अगर (पंचांगp_sdev->id != sdev->id)
			जारी;
		scsi_track_queue_full(पंचांगp_sdev, पंचांगp_sdev->queue_depth - 1);
	पूर्ण
पूर्ण

काष्ठा bfad_itnim_s *
bfad_get_itnim(काष्ठा bfad_im_port_s *im_port, पूर्णांक id)
अणु
	काष्ठा bfad_itnim_s   *itnim = शून्य;

	/* Search the mapped list क्रम this target ID */
	list_क्रम_each_entry(itnim, &im_port->itnim_mapped_list, list_entry) अणु
		अगर (id == itnim->scsi_tgt_id)
			वापस itnim;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Function is invoked from the SCSI Host Template slave_alloc() entry poपूर्णांक.
 * Has the logic to query the LUN Mask database to check अगर this LUN needs to
 * be made visible to the SCSI mid-layer or not.
 *
 * Returns BFA_STATUS_OK अगर this LUN needs to be added to the OS stack.
 * Returns -ENXIO to notअगरy SCSI mid-layer to not add this LUN to the OS stack.
 */
अटल पूर्णांक
bfad_im_check_अगर_make_lun_visible(काष्ठा scsi_device *sdev,
				  काष्ठा fc_rport *rport)
अणु
	काष्ठा bfad_itnim_data_s *itnim_data =
				(काष्ठा bfad_itnim_data_s *) rport->dd_data;
	काष्ठा bfa_s *bfa = itnim_data->itnim->bfa_itnim->bfa;
	काष्ठा bfa_rport_s *bfa_rport = itnim_data->itnim->bfa_itnim->rport;
	काष्ठा bfa_lun_mask_s *lun_list = bfa_get_lun_mask_list(bfa);
	पूर्णांक i = 0, ret = -ENXIO;

	क्रम (i = 0; i < MAX_LUN_MASK_CFG; i++) अणु
		अगर (lun_list[i].state == BFA_IOIM_LUN_MASK_ACTIVE &&
		    scsilun_to_पूर्णांक(&lun_list[i].lun) == sdev->lun &&
		    lun_list[i].rp_tag == bfa_rport->rport_tag &&
		    lun_list[i].lp_tag == (u8)bfa_rport->rport_info.lp_tag) अणु
			ret = BFA_STATUS_OK;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Scsi_Host ढाँचा entry slave_alloc
 */
अटल पूर्णांक
bfad_im_slave_alloc(काष्ठा scsi_device *sdev)
अणु
	काष्ठा fc_rport *rport = starget_to_rport(scsi_target(sdev));
	काष्ठा bfad_itnim_data_s *itnim_data;
	काष्ठा bfa_s *bfa;

	अगर (!rport || fc_remote_port_chkपढ़ोy(rport))
		वापस -ENXIO;

	itnim_data = (काष्ठा bfad_itnim_data_s *) rport->dd_data;
	bfa = itnim_data->itnim->bfa_itnim->bfa;

	अगर (bfa_get_lun_mask_status(bfa) == BFA_LUNMASK_ENABLED) अणु
		/*
		 * We should not mask LUN 0 - since this will translate
		 * to no LUN / TARGET क्रम SCSI ml resulting no scan.
		 */
		अगर (sdev->lun == 0) अणु
			sdev->sdev_bflags |= BLIST_NOREPORTLUN |
					     BLIST_SPARSELUN;
			जाओ करोne;
		पूर्ण

		/*
		 * Query LUN Mask configuration - to expose this LUN
		 * to the SCSI mid-layer or to mask it.
		 */
		अगर (bfad_im_check_अगर_make_lun_visible(sdev, rport) !=
							BFA_STATUS_OK)
			वापस -ENXIO;
	पूर्ण
करोne:
	sdev->hostdata = rport->dd_data;

	वापस 0;
पूर्ण

u32
bfad_im_supported_speeds(काष्ठा bfa_s *bfa)
अणु
	काष्ठा bfa_ioc_attr_s *ioc_attr;
	u32 supported_speed = 0;

	ioc_attr = kzalloc(माप(काष्ठा bfa_ioc_attr_s), GFP_KERNEL);
	अगर (!ioc_attr)
		वापस 0;

	bfa_ioc_get_attr(&bfa->ioc, ioc_attr);
	अगर (ioc_attr->adapter_attr.max_speed == BFA_PORT_SPEED_16GBPS)
		supported_speed |=  FC_PORTSPEED_16GBIT | FC_PORTSPEED_8GBIT |
				FC_PORTSPEED_4GBIT | FC_PORTSPEED_2GBIT;
	अन्यथा अगर (ioc_attr->adapter_attr.max_speed == BFA_PORT_SPEED_8GBPS) अणु
		अगर (ioc_attr->adapter_attr.is_mezz) अणु
			supported_speed |= FC_PORTSPEED_8GBIT |
				FC_PORTSPEED_4GBIT |
				FC_PORTSPEED_2GBIT | FC_PORTSPEED_1GBIT;
		पूर्ण अन्यथा अणु
			supported_speed |= FC_PORTSPEED_8GBIT |
				FC_PORTSPEED_4GBIT |
				FC_PORTSPEED_2GBIT;
		पूर्ण
	पूर्ण अन्यथा अगर (ioc_attr->adapter_attr.max_speed == BFA_PORT_SPEED_4GBPS) अणु
		supported_speed |=  FC_PORTSPEED_4GBIT | FC_PORTSPEED_2GBIT |
				FC_PORTSPEED_1GBIT;
	पूर्ण अन्यथा अगर (ioc_attr->adapter_attr.max_speed == BFA_PORT_SPEED_10GBPS) अणु
		supported_speed |= FC_PORTSPEED_10GBIT;
	पूर्ण
	kमुक्त(ioc_attr);
	वापस supported_speed;
पूर्ण

व्योम
bfad_fc_host_init(काष्ठा bfad_im_port_s *im_port)
अणु
	काष्ठा Scsi_Host *host = im_port->shost;
	काष्ठा bfad_s         *bfad = im_port->bfad;
	काष्ठा bfad_port_s    *port = im_port->port;
	अक्षर symname[BFA_SYMNAME_MAXLEN];
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(&bfad->bfa);

	fc_host_node_name(host) =
		cpu_to_be64((bfa_fcs_lport_get_nwwn(port->fcs_port)));
	fc_host_port_name(host) =
		cpu_to_be64((bfa_fcs_lport_get_pwwn(port->fcs_port)));
	fc_host_max_npiv_vports(host) = bfa_lps_get_max_vport(&bfad->bfa);

	fc_host_supported_classes(host) = FC_COS_CLASS3;

	स_रखो(fc_host_supported_fc4s(host), 0,
	       माप(fc_host_supported_fc4s(host)));
	अगर (supported_fc4s & BFA_LPORT_ROLE_FCP_IM)
		/* For FCP type 0x08 */
		fc_host_supported_fc4s(host)[2] = 1;
	/* For fibre channel services type 0x20 */
	fc_host_supported_fc4s(host)[7] = 1;

	strlcpy(symname, bfad->bfa_fcs.fabric.bport.port_cfg.sym_name.symname,
		BFA_SYMNAME_MAXLEN);
	प्र_लिखो(fc_host_symbolic_name(host), "%s", symname);

	fc_host_supported_speeds(host) = bfad_im_supported_speeds(&bfad->bfa);
	fc_host_maxframe_size(host) = fcport->cfg.maxfrsize;
पूर्ण

अटल व्योम
bfad_im_fc_rport_add(काष्ठा bfad_im_port_s *im_port, काष्ठा bfad_itnim_s *itnim)
अणु
	काष्ठा fc_rport_identअगरiers rport_ids;
	काष्ठा fc_rport *fc_rport;
	काष्ठा bfad_itnim_data_s *itnim_data;

	rport_ids.node_name =
		cpu_to_be64(bfa_fcs_itnim_get_nwwn(&itnim->fcs_itnim));
	rport_ids.port_name =
		cpu_to_be64(bfa_fcs_itnim_get_pwwn(&itnim->fcs_itnim));
	rport_ids.port_id =
		bfa_hton3b(bfa_fcs_itnim_get_fcid(&itnim->fcs_itnim));
	rport_ids.roles = FC_RPORT_ROLE_UNKNOWN;

	itnim->fc_rport = fc_rport =
		fc_remote_port_add(im_port->shost, 0, &rport_ids);

	अगर (!fc_rport)
		वापस;

	fc_rport->maxframe_size =
		bfa_fcs_itnim_get_maxfrsize(&itnim->fcs_itnim);
	fc_rport->supported_classes = bfa_fcs_itnim_get_cos(&itnim->fcs_itnim);

	itnim_data = fc_rport->dd_data;
	itnim_data->itnim = itnim;

	rport_ids.roles |= FC_RPORT_ROLE_FCP_TARGET;

	अगर (rport_ids.roles != FC_RPORT_ROLE_UNKNOWN)
		fc_remote_port_rolechg(fc_rport, rport_ids.roles);

	अगर ((fc_rport->scsi_target_id != -1)
	    && (fc_rport->scsi_target_id < MAX_FCP_TARGET))
		itnim->scsi_tgt_id = fc_rport->scsi_target_id;

	itnim->channel = fc_rport->channel;

	वापस;
पूर्ण

/*
 * Work queue handler using FC transport service
* Context: kernel
 */
अटल व्योम
bfad_im_itnim_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bfad_itnim_s   *itnim = container_of(work, काष्ठा bfad_itnim_s,
							itnim_work);
	काष्ठा bfad_im_s      *im = itnim->im;
	काष्ठा bfad_s         *bfad = im->bfad;
	काष्ठा bfad_im_port_s *im_port;
	अचिन्हित दीर्घ   flags;
	काष्ठा fc_rport *fc_rport;
	wwn_t wwpn;
	u32 fcid;
	अक्षर wwpn_str[32], fcid_str[16];

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	im_port = itnim->im_port;
	bfa_trc(bfad, itnim->state);
	चयन (itnim->state) अणु
	हाल ITNIM_STATE_ONLINE:
		अगर (!itnim->fc_rport) अणु
			spin_unlock_irqrestore(&bfad->bfad_lock, flags);
			bfad_im_fc_rport_add(im_port, itnim);
			spin_lock_irqsave(&bfad->bfad_lock, flags);
			wwpn = bfa_fcs_itnim_get_pwwn(&itnim->fcs_itnim);
			fcid = bfa_fcs_itnim_get_fcid(&itnim->fcs_itnim);
			wwn2str(wwpn_str, wwpn);
			fcid2str(fcid_str, fcid);
			list_add_tail(&itnim->list_entry,
				&im_port->itnim_mapped_list);
			BFA_LOG(KERN_INFO, bfad, bfa_log_level,
				"ITNIM ONLINE Target: %d:0:%d "
				"FCID: %s WWPN: %s\n",
				im_port->shost->host_no,
				itnim->scsi_tgt_id,
				fcid_str, wwpn_str);
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_WARNING
				"%s: itnim %llx is already in online state\n",
				__func__,
				bfa_fcs_itnim_get_pwwn(&itnim->fcs_itnim));
		पूर्ण

		अवरोध;
	हाल ITNIM_STATE_OFFLINE_PENDING:
		itnim->state = ITNIM_STATE_OFFLINE;
		अगर (itnim->fc_rport) अणु
			fc_rport = itnim->fc_rport;
			((काष्ठा bfad_itnim_data_s *)
				fc_rport->dd_data)->itnim = शून्य;
			itnim->fc_rport = शून्य;
			अगर (!(im_port->port->flags & BFAD_PORT_DELETE)) अणु
				spin_unlock_irqrestore(&bfad->bfad_lock, flags);
				fc_rport->dev_loss_पंचांगo =
					bfa_fcpim_path_tov_get(&bfad->bfa) + 1;
				fc_remote_port_delete(fc_rport);
				spin_lock_irqsave(&bfad->bfad_lock, flags);
			पूर्ण
			wwpn = bfa_fcs_itnim_get_pwwn(&itnim->fcs_itnim);
			fcid = bfa_fcs_itnim_get_fcid(&itnim->fcs_itnim);
			wwn2str(wwpn_str, wwpn);
			fcid2str(fcid_str, fcid);
			list_del(&itnim->list_entry);
			BFA_LOG(KERN_INFO, bfad, bfa_log_level,
				"ITNIM OFFLINE Target: %d:0:%d "
				"FCID: %s WWPN: %s\n",
				im_port->shost->host_no,
				itnim->scsi_tgt_id,
				fcid_str, wwpn_str);
		पूर्ण
		अवरोध;
	हाल ITNIM_STATE_FREE:
		अगर (itnim->fc_rport) अणु
			fc_rport = itnim->fc_rport;
			((काष्ठा bfad_itnim_data_s *)
				fc_rport->dd_data)->itnim = शून्य;
			itnim->fc_rport = शून्य;
			अगर (!(im_port->port->flags & BFAD_PORT_DELETE)) अणु
				spin_unlock_irqrestore(&bfad->bfad_lock, flags);
				fc_rport->dev_loss_पंचांगo =
					bfa_fcpim_path_tov_get(&bfad->bfa) + 1;
				fc_remote_port_delete(fc_rport);
				spin_lock_irqsave(&bfad->bfad_lock, flags);
			पूर्ण
			list_del(&itnim->list_entry);
		पूर्ण

		kमुक्त(itnim);
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
पूर्ण

/*
 * Scsi_Host ढाँचा entry, queue a SCSI command to the BFAD.
 */
अटल पूर्णांक
bfad_im_queuecommand_lck(काष्ठा scsi_cmnd *cmnd, व्योम (*करोne) (काष्ठा scsi_cmnd *))
अणु
	काष्ठा bfad_im_port_s *im_port =
		(काष्ठा bfad_im_port_s *) cmnd->device->host->hostdata[0];
	काष्ठा bfad_s         *bfad = im_port->bfad;
	काष्ठा bfad_itnim_data_s *itnim_data = cmnd->device->hostdata;
	काष्ठा bfad_itnim_s   *itnim;
	काष्ठा bfa_ioim_s *hal_io;
	अचिन्हित दीर्घ   flags;
	पूर्णांक             rc;
	पूर्णांक       sg_cnt = 0;
	काष्ठा fc_rport *rport = starget_to_rport(scsi_target(cmnd->device));

	rc = fc_remote_port_chkपढ़ोy(rport);
	अगर (rc) अणु
		cmnd->result = rc;
		करोne(cmnd);
		वापस 0;
	पूर्ण

	अगर (bfad->bfad_flags & BFAD_EEH_BUSY) अणु
		अगर (bfad->bfad_flags & BFAD_EEH_PCI_CHANNEL_IO_PERM_FAILURE)
			cmnd->result = DID_NO_CONNECT << 16;
		अन्यथा
			cmnd->result = DID_REQUEUE << 16;
		करोne(cmnd);
		वापस 0;
	पूर्ण

	sg_cnt = scsi_dma_map(cmnd);
	अगर (sg_cnt < 0)
		वापस SCSI_MLQUEUE_HOST_BUSY;

	cmnd->scsi_करोne = करोne;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	अगर (!(bfad->bfad_flags & BFAD_HAL_START_DONE)) अणु
		prपूर्णांकk(KERN_WARNING
			"bfad%d, queuecommand %p %x failed, BFA stopped\n",
		       bfad->inst_no, cmnd, cmnd->cmnd[0]);
		cmnd->result = DID_NO_CONNECT << 16;
		जाओ out_fail_cmd;
	पूर्ण


	itnim = itnim_data->itnim;
	अगर (!itnim) अणु
		cmnd->result = DID_IMM_RETRY << 16;
		जाओ out_fail_cmd;
	पूर्ण

	hal_io = bfa_ioim_alloc(&bfad->bfa, (काष्ठा bfad_ioim_s *) cmnd,
				    itnim->bfa_itnim, sg_cnt);
	अगर (!hal_io) अणु
		prपूर्णांकk(KERN_WARNING "hal_io failure\n");
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		scsi_dma_unmap(cmnd);
		वापस SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण

	cmnd->host_scribble = (अक्षर *)hal_io;
	bfa_ioim_start(hal_io);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	वापस 0;

out_fail_cmd:
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	scsi_dma_unmap(cmnd);
	अगर (करोne)
		करोne(cmnd);

	वापस 0;
पूर्ण

अटल DEF_SCSI_QCMD(bfad_im_queuecommand)

व्योम
bfad_rport_online_रुको(काष्ठा bfad_s *bfad)
अणु
	पूर्णांक i;
	पूर्णांक rport_delay = 10;

	क्रम (i = 0; !(bfad->bfad_flags & BFAD_PORT_ONLINE)
		&& i < bfa_linkup_delay; i++) अणु
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_समयout(HZ);
	पूर्ण

	अगर (bfad->bfad_flags & BFAD_PORT_ONLINE) अणु
		rport_delay = rport_delay < bfa_linkup_delay ?
			rport_delay : bfa_linkup_delay;
		क्रम (i = 0; !(bfad->bfad_flags & BFAD_RPORT_ONLINE)
			&& i < rport_delay; i++) अणु
			set_current_state(TASK_UNINTERRUPTIBLE);
			schedule_समयout(HZ);
		पूर्ण

		अगर (rport_delay > 0 && (bfad->bfad_flags & BFAD_RPORT_ONLINE)) अणु
			set_current_state(TASK_UNINTERRUPTIBLE);
			schedule_समयout(rport_delay * HZ);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक
bfad_get_linkup_delay(काष्ठा bfad_s *bfad)
अणु
	u8		nwwns = 0;
	wwn_t		wwns[BFA_PREBOOT_BOOTLUN_MAX];
	पूर्णांक		linkup_delay;

	/*
	 * Querying क्रम the boot target port wwns
	 * -- पढ़ो from boot inक्रमmation in flash.
	 * If nwwns > 0 => boot over SAN and set linkup_delay = 30
	 * अन्यथा => local boot machine set linkup_delay = 0
	 */

	bfa_iocfc_get_bootwwns(&bfad->bfa, &nwwns, wwns);

	अगर (nwwns > 0)
		/* If Boot over SAN set linkup_delay = 30sec */
		linkup_delay = 30;
	अन्यथा
		/* If local boot; no linkup_delay */
		linkup_delay = 0;

	वापस linkup_delay;
पूर्ण
