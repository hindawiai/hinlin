<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम Realtek PCI-Express card पढ़ोer
 *
 * Copyright(c) 2009-2013 Realtek Semiconductor Corp. All rights reserved.
 *
 * Author:
 *   Wei WANG (wei_wang@realsil.com.cn)
 *   Micky Ching (micky_ching@realsil.com.cn)
 */

#समावेश <linux/blkdev.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/sched.h>
#समावेश <linux/workqueue.h>

#समावेश "rtsx.h"
#समावेश "ms.h"
#समावेश "sd.h"
#समावेश "xd.h"

MODULE_DESCRIPTION("Realtek PCI-Express card reader rts5208/rts5288 driver");
MODULE_LICENSE("GPL");

अटल अचिन्हित पूर्णांक delay_use = 1;
module_param(delay_use, uपूर्णांक, 0644);
MODULE_PARM_DESC(delay_use, "seconds to delay before using a new device");

अटल पूर्णांक ss_en;
module_param(ss_en, पूर्णांक, 0644);
MODULE_PARM_DESC(ss_en, "enable selective suspend");

अटल पूर्णांक ss_पूर्णांकerval = 50;
module_param(ss_पूर्णांकerval, पूर्णांक, 0644);
MODULE_PARM_DESC(ss_पूर्णांकerval, "Interval to enter ss state in seconds");

अटल पूर्णांक स्वतः_delink_en;
module_param(स्वतः_delink_en, पूर्णांक, 0644);
MODULE_PARM_DESC(स्वतः_delink_en, "enable auto delink");

अटल अचिन्हित अक्षर aspm_l0s_l1_en;
module_param(aspm_l0s_l1_en, byte, 0644);
MODULE_PARM_DESC(aspm_l0s_l1_en, "enable device aspm");

अटल पूर्णांक msi_en;
module_param(msi_en, पूर्णांक, 0644);
MODULE_PARM_DESC(msi_en, "enable msi");

अटल irqवापस_t rtsx_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);

/***********************************************************************
 * Host functions
 ***********************************************************************/

अटल स्थिर अक्षर *host_info(काष्ठा Scsi_Host *host)
अणु
	वापस "SCSI emulation for PCI-Express Mass Storage devices";
पूर्ण

अटल पूर्णांक slave_alloc(काष्ठा scsi_device *sdev)
अणु
	/*
	 * Set the INQUIRY transfer length to 36.  We करोn't use any of
	 * the extra data and many devices choke अगर asked क्रम more or
	 * less than 36 bytes.
	 */
	sdev->inquiry_len = 36;
	वापस 0;
पूर्ण

अटल पूर्णांक slave_configure(काष्ठा scsi_device *sdev)
अणु
	/*
	 * Scatter-gather buffers (all but the last) must have a length
	 * भागisible by the bulk maxpacket size.  Otherwise a data packet
	 * would end up being लघु, causing a premature end to the data
	 * transfer.  Since high-speed bulk pipes have a maxpacket size
	 * of 512, we'll use that as the scsi device queue's DMA alignment
	 * mask.  Guaranteeing proper alignment of the first buffer will
	 * have the desired effect because, except at the beginning and
	 * the end, scatter-gather buffers follow page boundaries.
	 */
	blk_queue_dma_alignment(sdev->request_queue, (512 - 1));

	/* Set the SCSI level to at least 2.  We'll leave it at 3 if that's
	 * what is originally reported.  We need this to aव्योम confusing
	 * the SCSI layer with devices that report 0 or 1, but need 10-byte
	 * commands (ala ATAPI devices behind certain bridges, or devices
	 * which simply have broken INQUIRY data).
	 *
	 * NOTE: This means /dev/sg programs (ala cdrecord) will get the
	 * actual inक्रमmation.  This seems to be the preference क्रम
	 * programs like that.
	 *
	 * NOTE: This also means that /proc/scsi/scsi and sysfs may report
	 * the actual value or the modअगरied one, depending on where the
	 * data comes from.
	 */
	अगर (sdev->scsi_level < SCSI_2) अणु
		sdev->scsi_level = SCSI_2;
		sdev->sdev_target->scsi_level = SCSI_2;
	पूर्ण

	वापस 0;
पूर्ण

/***********************************************************************
 * /proc/scsi/ functions
 ***********************************************************************/

/* we use this macro to help us ग_लिखो पूर्णांकo the buffer */
#अघोषित SPRINTF
#घोषणा SPRINTF(args...) \
	करो अणु \
		अगर (pos < buffer + length) \
			pos += प्र_लिखो(pos, ## args); \
	पूर्ण जबतक (0)

/* queue a command */
/* This is always called with scsi_lock(host) held */
अटल पूर्णांक queuecommand_lck(काष्ठा scsi_cmnd *srb,
			    व्योम (*करोne)(काष्ठा scsi_cmnd *))
अणु
	काष्ठा rtsx_dev *dev = host_to_rtsx(srb->device->host);
	काष्ठा rtsx_chip *chip = dev->chip;

	/* check क्रम state-transition errors */
	अगर (chip->srb) अणु
		dev_err(&dev->pci->dev, "Error: chip->srb = %p\n",
			chip->srb);
		वापस SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण

	/* fail the command अगर we are disconnecting */
	अगर (rtsx_chk_stat(chip, RTSX_STAT_DISCONNECT)) अणु
		dev_info(&dev->pci->dev, "Fail command during disconnect\n");
		srb->result = DID_NO_CONNECT << 16;
		करोne(srb);
		वापस 0;
	पूर्ण

	/* enqueue the command and wake up the control thपढ़ो */
	srb->scsi_करोne = करोne;
	chip->srb = srb;
	complete(&dev->cmnd_पढ़ोy);

	वापस 0;
पूर्ण

अटल DEF_SCSI_QCMD(queuecommand)

/***********************************************************************
 * Error handling functions
 ***********************************************************************/

/* Command समयout and पात */
अटल पूर्णांक command_पात(काष्ठा scsi_cmnd *srb)
अणु
	काष्ठा Scsi_Host *host = srb->device->host;
	काष्ठा rtsx_dev *dev = host_to_rtsx(host);
	काष्ठा rtsx_chip *chip = dev->chip;

	dev_info(&dev->pci->dev, "%s called\n", __func__);

	scsi_lock(host);

	/* Is this command still active? */
	अगर (chip->srb != srb) अणु
		scsi_unlock(host);
		dev_info(&dev->pci->dev, "-- nothing to abort\n");
		वापस FAILED;
	पूर्ण

	rtsx_set_stat(chip, RTSX_STAT_ABORT);

	scsi_unlock(host);

	/* Wait क्रम the पातed command to finish */
	रुको_क्रम_completion(&dev->notअगरy);

	वापस SUCCESS;
पूर्ण

/*
 * This invokes the transport reset mechanism to reset the state of the
 * device
 */
अटल पूर्णांक device_reset(काष्ठा scsi_cmnd *srb)
अणु
	काष्ठा rtsx_dev *dev = host_to_rtsx(srb->device->host);

	dev_info(&dev->pci->dev, "%s called\n", __func__);

	वापस SUCCESS;
पूर्ण

/*
 * this defines our host ढाँचा, with which we'll allocate hosts
 */

अटल काष्ठा scsi_host_ढाँचा rtsx_host_ढाँचा = अणु
	/* basic userland पूर्णांकerface stuff */
	.name =				CR_DRIVER_NAME,
	.proc_name =			CR_DRIVER_NAME,
	.info =				host_info,

	/* command पूर्णांकerface -- queued only */
	.queuecommand =			queuecommand,

	/* error and पात handlers */
	.eh_पात_handler =		command_पात,
	.eh_device_reset_handler =	device_reset,

	/* queue commands only, only one command per LUN */
	.can_queue =			1,

	/* unknown initiator id */
	.this_id =			-1,

	.slave_alloc =			slave_alloc,
	.slave_configure =		slave_configure,

	/* lots of sg segments can be handled */
	.sg_tablesize =			SG_ALL,

	/* limit the total size of a transfer to 120 KB */
	.max_sectors =                  240,

	/* emulated HBA */
	.emulated =			1,

	/* we करो our own delay after a device or bus reset */
	.skip_settle_delay =		1,

	/* module management */
	.module =			THIS_MODULE
पूर्ण;

अटल पूर्णांक rtsx_acquire_irq(काष्ठा rtsx_dev *dev)
अणु
	काष्ठा rtsx_chip *chip = dev->chip;

	dev_info(&dev->pci->dev, "%s: chip->msi_en = %d, pci->irq = %d\n",
		 __func__, chip->msi_en, dev->pci->irq);

	अगर (request_irq(dev->pci->irq, rtsx_पूर्णांकerrupt,
			chip->msi_en ? 0 : IRQF_SHARED,
			CR_DRIVER_NAME, dev)) अणु
		dev_err(&dev->pci->dev,
			"rtsx: unable to grab IRQ %d, disabling device\n",
			dev->pci->irq);
		वापस -1;
	पूर्ण

	dev->irq = dev->pci->irq;
	pci_पूर्णांकx(dev->pci, !chip->msi_en);

	वापस 0;
पूर्ण

/*
 * घातer management
 */
अटल पूर्णांक __maybe_unused rtsx_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा pci_dev *pci = to_pci_dev(dev_d);
	काष्ठा rtsx_dev *dev = pci_get_drvdata(pci);
	काष्ठा rtsx_chip *chip;

	अगर (!dev)
		वापस 0;

	/* lock the device poपूर्णांकers */
	mutex_lock(&dev->dev_mutex);

	chip = dev->chip;

	rtsx_करो_beक्रमe_घातer_करोwn(chip, PM_S3);

	अगर (dev->irq >= 0) अणु
		मुक्त_irq(dev->irq, (व्योम *)dev);
		dev->irq = -1;
	पूर्ण

	अगर (chip->msi_en)
		pci_मुक्त_irq_vectors(pci);

	device_wakeup_enable(dev_d);

	/* unlock the device poपूर्णांकers */
	mutex_unlock(&dev->dev_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused rtsx_resume(काष्ठा device *dev_d)
अणु
	काष्ठा pci_dev *pci = to_pci_dev(dev_d);
	काष्ठा rtsx_dev *dev = pci_get_drvdata(pci);
	काष्ठा rtsx_chip *chip;

	अगर (!dev)
		वापस 0;

	chip = dev->chip;

	/* lock the device poपूर्णांकers */
	mutex_lock(&dev->dev_mutex);

	pci_set_master(pci);

	अगर (chip->msi_en) अणु
		अगर (pci_alloc_irq_vectors(pci, 1, 1, PCI_IRQ_MSI) < 0)
			chip->msi_en = 0;
	पूर्ण

	अगर (rtsx_acquire_irq(dev) < 0) अणु
		/* unlock the device poपूर्णांकers */
		mutex_unlock(&dev->dev_mutex);
		वापस -EIO;
	पूर्ण

	rtsx_ग_लिखो_रेजिस्टर(chip, HOST_SLEEP_STATE, 0x03, 0x00);
	rtsx_init_chip(chip);

	/* unlock the device poपूर्णांकers */
	mutex_unlock(&dev->dev_mutex);

	वापस 0;
पूर्ण

अटल व्योम rtsx_shutकरोwn(काष्ठा pci_dev *pci)
अणु
	काष्ठा rtsx_dev *dev = pci_get_drvdata(pci);
	काष्ठा rtsx_chip *chip;

	अगर (!dev)
		वापस;

	chip = dev->chip;

	rtsx_करो_beक्रमe_घातer_करोwn(chip, PM_S1);

	अगर (dev->irq >= 0) अणु
		मुक्त_irq(dev->irq, (व्योम *)dev);
		dev->irq = -1;
	पूर्ण

	अगर (chip->msi_en)
		pci_मुक्त_irq_vectors(pci);

	pci_disable_device(pci);
पूर्ण

अटल पूर्णांक rtsx_control_thपढ़ो(व्योम *__dev)
अणु
	काष्ठा rtsx_dev *dev = __dev;
	काष्ठा rtsx_chip *chip = dev->chip;
	काष्ठा Scsi_Host *host = rtsx_to_host(dev);

	क्रम (;;) अणु
		अगर (रुको_क्रम_completion_पूर्णांकerruptible(&dev->cmnd_पढ़ोy))
			अवरोध;

		/* lock the device poपूर्णांकers */
		mutex_lock(&dev->dev_mutex);

		/* अगर the device has disconnected, we are मुक्त to निकास */
		अगर (rtsx_chk_stat(chip, RTSX_STAT_DISCONNECT)) अणु
			dev_info(&dev->pci->dev, "-- rtsx-control exiting\n");
			mutex_unlock(&dev->dev_mutex);
			अवरोध;
		पूर्ण

		/* lock access to the state */
		scsi_lock(host);

		/* has the command पातed ? */
		अगर (rtsx_chk_stat(chip, RTSX_STAT_ABORT)) अणु
			chip->srb->result = DID_ABORT << 16;
			जाओ skip_क्रम_पात;
		पूर्ण

		scsi_unlock(host);

		/* reject the command अगर the direction indicator
		 * is UNKNOWN
		 */
		अगर (chip->srb->sc_data_direction == DMA_BIसूचीECTIONAL) अणु
			dev_err(&dev->pci->dev, "UNKNOWN data direction\n");
			chip->srb->result = DID_ERROR << 16;
		पूर्ण

		/* reject अगर target != 0 or अगर LUN is higher than
		 * the maximum known LUN
		 */
		अन्यथा अगर (chip->srb->device->id) अणु
			dev_err(&dev->pci->dev, "Bad target number (%d:%d)\n",
				chip->srb->device->id,
				(u8)chip->srb->device->lun);
			chip->srb->result = DID_BAD_TARGET << 16;
		पूर्ण

		अन्यथा अगर (chip->srb->device->lun > chip->max_lun) अणु
			dev_err(&dev->pci->dev, "Bad LUN (%d:%d)\n",
				chip->srb->device->id,
				(u8)chip->srb->device->lun);
			chip->srb->result = DID_BAD_TARGET << 16;
		पूर्ण

		/* we've got a command, let's करो it! */
		अन्यथा अणु
			scsi_show_command(chip);
			rtsx_invoke_transport(chip->srb, chip);
		पूर्ण

		/* lock access to the state */
		scsi_lock(host);

		/* did the command alपढ़ोy complete because of a disconnect? */
		अगर (!chip->srb)
			;		/* nothing to करो */

		/* indicate that the command is करोne */
		अन्यथा अगर (chip->srb->result != DID_ABORT << 16) अणु
			chip->srb->scsi_करोne(chip->srb);
		पूर्ण अन्यथा अणु
skip_क्रम_पात:
			dev_err(&dev->pci->dev, "scsi command aborted\n");
		पूर्ण

		अगर (rtsx_chk_stat(chip, RTSX_STAT_ABORT)) अणु
			complete(&dev->notअगरy);

			rtsx_set_stat(chip, RTSX_STAT_IDLE);
		पूर्ण

		/* finished working on this command */
		chip->srb = शून्य;
		scsi_unlock(host);

		/* unlock the device poपूर्णांकers */
		mutex_unlock(&dev->dev_mutex);
	पूर्ण /* क्रम (;;) */

	/* notअगरy the निकास routine that we're actually निकासing now
	 *
	 * complete()/रुको_क्रम_completion() is similar to up()/करोwn(),
	 * except that complete() is safe in the हाल where the काष्ठाure
	 * is getting deleted in a parallel mode of execution (i.e. just
	 * after the करोwn() -- that's necessary क्रम the thपढ़ो-shutकरोwn
	 * हाल.
	 *
	 * complete_and_निकास() goes even further than this -- it is safe in
	 * the हाल that the thपढ़ो of the caller is going away (not just
	 * the काष्ठाure) -- this is necessary क्रम the module-हटाओ हाल.
	 * This is important in preemption kernels, which transfer the flow
	 * of execution immediately upon a complete().
	 */
	complete_and_निकास(&dev->control_निकास, 0);
पूर्ण

अटल पूर्णांक rtsx_polling_thपढ़ो(व्योम *__dev)
अणु
	काष्ठा rtsx_dev *dev = __dev;
	काष्ठा rtsx_chip *chip = dev->chip;
	काष्ठा sd_info *sd_card = &chip->sd_card;
	काष्ठा xd_info *xd_card = &chip->xd_card;
	काष्ठा ms_info *ms_card = &chip->ms_card;

	sd_card->cleanup_counter = 0;
	xd_card->cleanup_counter = 0;
	ms_card->cleanup_counter = 0;

	/* Wait until SCSI scan finished */
	रुको_समयout((delay_use + 5) * 1000);

	क्रम (;;) अणु
		set_current_state(TASK_INTERRUPTIBLE);
		schedule_समयout(msecs_to_jअगरfies(POLLING_INTERVAL));

		/* lock the device poपूर्णांकers */
		mutex_lock(&dev->dev_mutex);

		/* अगर the device has disconnected, we are मुक्त to निकास */
		अगर (rtsx_chk_stat(chip, RTSX_STAT_DISCONNECT)) अणु
			dev_info(&dev->pci->dev, "-- rtsx-polling exiting\n");
			mutex_unlock(&dev->dev_mutex);
			अवरोध;
		पूर्ण

		mutex_unlock(&dev->dev_mutex);

		mspro_polling_क्रमmat_status(chip);

		/* lock the device poपूर्णांकers */
		mutex_lock(&dev->dev_mutex);

		rtsx_polling_func(chip);

		/* unlock the device poपूर्णांकers */
		mutex_unlock(&dev->dev_mutex);
	पूर्ण

	complete_and_निकास(&dev->polling_निकास, 0);
पूर्ण

/*
 * पूर्णांकerrupt handler
 */
अटल irqवापस_t rtsx_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा rtsx_dev *dev = dev_id;
	काष्ठा rtsx_chip *chip;
	पूर्णांक retval;
	u32 status;

	अगर (dev)
		chip = dev->chip;
	अन्यथा
		वापस IRQ_NONE;

	अगर (!chip)
		वापस IRQ_NONE;

	spin_lock(&dev->reg_lock);

	retval = rtsx_pre_handle_पूर्णांकerrupt(chip);
	अगर (retval == STATUS_FAIL) अणु
		spin_unlock(&dev->reg_lock);
		अगर (chip->पूर्णांक_reg == 0xFFFFFFFF)
			वापस IRQ_HANDLED;
		वापस IRQ_NONE;
	पूर्ण

	status = chip->पूर्णांक_reg;

	अगर (dev->check_card_cd) अणु
		अगर (!(dev->check_card_cd & status)) अणु
			/* card not exist, वापस TRANS_RESULT_FAIL */
			dev->trans_result = TRANS_RESULT_FAIL;
			अगर (dev->करोne)
				complete(dev->करोne);
			जाओ निकास;
		पूर्ण
	पूर्ण

	अगर (status & (NEED_COMPLETE_INT | DELINK_INT)) अणु
		अगर (status & (TRANS_FAIL_INT | DELINK_INT)) अणु
			अगर (status & DELINK_INT)
				RTSX_SET_DELINK(chip);
			dev->trans_result = TRANS_RESULT_FAIL;
			अगर (dev->करोne)
				complete(dev->करोne);
		पूर्ण अन्यथा अगर (status & TRANS_OK_INT) अणु
			dev->trans_result = TRANS_RESULT_OK;
			अगर (dev->करोne)
				complete(dev->करोne);
		पूर्ण अन्यथा अगर (status & DATA_DONE_INT) अणु
			dev->trans_result = TRANS_NOT_READY;
			अगर (dev->करोne && (dev->trans_state == STATE_TRANS_SG))
				complete(dev->करोne);
		पूर्ण
	पूर्ण

निकास:
	spin_unlock(&dev->reg_lock);
	वापस IRQ_HANDLED;
पूर्ण

/* Release all our dynamic resources */
अटल व्योम rtsx_release_resources(काष्ठा rtsx_dev *dev)
अणु
	dev_info(&dev->pci->dev, "-- %s\n", __func__);

	/* Tell the control thपढ़ो to निकास.  The SCSI host must
	 * alपढ़ोy have been हटाओd so it won't try to queue
	 * any more commands.
	 */
	dev_info(&dev->pci->dev, "-- sending exit command to thread\n");
	complete(&dev->cmnd_पढ़ोy);
	अगर (dev->ctl_thपढ़ो)
		रुको_क्रम_completion(&dev->control_निकास);
	अगर (dev->polling_thपढ़ो)
		रुको_क्रम_completion(&dev->polling_निकास);

	रुको_समयout(200);

	अगर (dev->rtsx_resv_buf) अणु
		dev->chip->host_cmds_ptr = शून्य;
		dev->chip->host_sg_tbl_ptr = शून्य;
	पूर्ण

	अगर (dev->irq > 0)
		मुक्त_irq(dev->irq, (व्योम *)dev);
	अगर (dev->chip->msi_en)
		pci_मुक्त_irq_vectors(dev->pci);
	अगर (dev->remap_addr)
		iounmap(dev->remap_addr);

	rtsx_release_chip(dev->chip);
	kमुक्त(dev->chip);
पूर्ण

/*
 * First stage of disconnect processing: stop all commands and हटाओ
 * the host
 */
अटल व्योम quiesce_and_हटाओ_host(काष्ठा rtsx_dev *dev)
अणु
	काष्ठा Scsi_Host *host = rtsx_to_host(dev);
	काष्ठा rtsx_chip *chip = dev->chip;

	/*
	 * Prevent new transfers, stop the current command, and
	 * पूर्णांकerrupt a SCSI-scan or device-reset delay
	 */
	mutex_lock(&dev->dev_mutex);
	scsi_lock(host);
	rtsx_set_stat(chip, RTSX_STAT_DISCONNECT);
	scsi_unlock(host);
	mutex_unlock(&dev->dev_mutex);
	wake_up(&dev->delay_रुको);
	रुको_क्रम_completion(&dev->scanning_करोne);

	/* Wait some समय to let other thपढ़ोs exist */
	रुको_समयout(100);

	/*
	 * queuecommand won't accept any new commands and the control
	 * thपढ़ो won't execute a previously-queued command.  If there
	 * is such a command pending, complete it with an error.
	 */
	mutex_lock(&dev->dev_mutex);
	अगर (chip->srb) अणु
		chip->srb->result = DID_NO_CONNECT << 16;
		scsi_lock(host);
		chip->srb->scsi_करोne(dev->chip->srb);
		chip->srb = शून्य;
		scsi_unlock(host);
	पूर्ण
	mutex_unlock(&dev->dev_mutex);

	/* Now we own no commands so it's safe to हटाओ the SCSI host */
	scsi_हटाओ_host(host);
पूर्ण

/* Second stage of disconnect processing: deallocate all resources */
अटल व्योम release_everything(काष्ठा rtsx_dev *dev)
अणु
	rtsx_release_resources(dev);

	/*
	 * Drop our reference to the host; the SCSI core will मुक्त it
	 * when the refcount becomes 0.
	 */
	scsi_host_put(rtsx_to_host(dev));
पूर्ण

/* Thपढ़ो to carry out delayed SCSI-device scanning */
अटल पूर्णांक rtsx_scan_thपढ़ो(व्योम *__dev)
अणु
	काष्ठा rtsx_dev *dev = __dev;
	काष्ठा rtsx_chip *chip = dev->chip;

	/* Wait क्रम the समयout to expire or क्रम a disconnect */
	अगर (delay_use > 0) अणु
		dev_info(&dev->pci->dev,
			 "%s: waiting for device to settle before scanning\n",
			 CR_DRIVER_NAME);
		रुको_event_पूर्णांकerruptible_समयout
			(dev->delay_रुको,
			 rtsx_chk_stat(chip, RTSX_STAT_DISCONNECT),
			 delay_use * HZ);
	पूर्ण

	/* If the device is still connected, perक्रमm the scanning */
	अगर (!rtsx_chk_stat(chip, RTSX_STAT_DISCONNECT)) अणु
		scsi_scan_host(rtsx_to_host(dev));
		dev_info(&dev->pci->dev, "%s: device scan complete\n",
			 CR_DRIVER_NAME);

		/* Should we unbind अगर no devices were detected? */
	पूर्ण

	complete_and_निकास(&dev->scanning_करोne, 0);
पूर्ण

अटल व्योम rtsx_init_options(काष्ठा rtsx_chip *chip)
अणु
	chip->venकरोr_id = chip->rtsx->pci->venकरोr;
	chip->product_id = chip->rtsx->pci->device;
	chip->adma_mode = 1;
	chip->lun_mc = 0;
	chip->driver_first_load = 1;
#अगर_घोषित HW_AUTO_SWITCH_SD_BUS
	chip->sdio_in_अक्षरge = 0;
#पूर्ण_अगर

	chip->mspro_क्रमmatter_enable = 1;
	chip->ignore_sd = 0;
	chip->use_hw_setting = 0;
	chip->lun_mode = DEFAULT_SINGLE;
	chip->स्वतः_delink_en = स्वतः_delink_en;
	chip->ss_en = ss_en;
	chip->ss_idle_period = ss_पूर्णांकerval * 1000;
	chip->remote_wakeup_en = 0;
	chip->aspm_l0s_l1_en = aspm_l0s_l1_en;
	chip->dynamic_aspm = 1;
	chip->fpga_sd_sdr104_clk = CLK_200;
	chip->fpga_sd_ddr50_clk = CLK_100;
	chip->fpga_sd_sdr50_clk = CLK_100;
	chip->fpga_sd_hs_clk = CLK_100;
	chip->fpga_mmc_52m_clk = CLK_80;
	chip->fpga_ms_hg_clk = CLK_80;
	chip->fpga_ms_4bit_clk = CLK_80;
	chip->fpga_ms_1bit_clk = CLK_40;
	chip->asic_sd_sdr104_clk = 203;
	chip->asic_sd_sdr50_clk = 98;
	chip->asic_sd_ddr50_clk = 98;
	chip->asic_sd_hs_clk = 98;
	chip->asic_mmc_52m_clk = 98;
	chip->asic_ms_hg_clk = 117;
	chip->asic_ms_4bit_clk = 78;
	chip->asic_ms_1bit_clk = 39;
	chip->ssc_depth_sd_sdr104 = SSC_DEPTH_2M;
	chip->ssc_depth_sd_sdr50 = SSC_DEPTH_2M;
	chip->ssc_depth_sd_ddr50 = SSC_DEPTH_1M;
	chip->ssc_depth_sd_hs = SSC_DEPTH_1M;
	chip->ssc_depth_mmc_52m = SSC_DEPTH_1M;
	chip->ssc_depth_ms_hg = SSC_DEPTH_1M;
	chip->ssc_depth_ms_4bit = SSC_DEPTH_512K;
	chip->ssc_depth_low_speed = SSC_DEPTH_512K;
	chip->ssc_en = 1;
	chip->sd_speed_prior = 0x01040203;
	chip->sd_current_prior = 0x00010203;
	chip->sd_ctl = SD_PUSH_POINT_AUTO |
		       SD_SAMPLE_POINT_AUTO |
		       SUPPORT_MMC_DDR_MODE;
	chip->sd_ddr_tx_phase = 0;
	chip->mmc_ddr_tx_phase = 1;
	chip->sd_शेष_tx_phase = 15;
	chip->sd_शेष_rx_phase = 15;
	chip->pmos_pwr_on_पूर्णांकerval = 200;
	chip->sd_voltage_चयन_delay = 1000;
	chip->ms_घातer_class_en = 3;

	chip->sd_400mA_ocp_thd = 1;
	chip->sd_800mA_ocp_thd = 5;
	chip->ms_ocp_thd = 2;

	chip->card_drive_sel = 0x55;
	chip->sd30_drive_sel_1v8 = 0x03;
	chip->sd30_drive_sel_3v3 = 0x01;

	chip->करो_delink_beक्रमe_घातer_करोwn = 1;
	chip->स्वतः_घातer_करोwn = 1;
	chip->polling_config = 0;

	chip->क्रमce_clkreq_0 = 1;
	chip->ft2_fast_mode = 0;

	chip->sdio_retry_cnt = 1;

	chip->xd_समयout = 2000;
	chip->sd_समयout = 10000;
	chip->ms_समयout = 2000;
	chip->mspro_समयout = 15000;

	chip->घातer_करोwn_in_ss = 1;

	chip->sdr104_en = 1;
	chip->sdr50_en = 1;
	chip->ddr50_en = 1;

	chip->delink_stage1_step = 100;
	chip->delink_stage2_step = 40;
	chip->delink_stage3_step = 20;

	chip->स्वतः_delink_in_L1 = 1;
	chip->blink_led = 1;
	chip->msi_en = msi_en;
	chip->hp_watch_bios_hotplug = 0;
	chip->max_payload = 0;
	chip->phy_voltage = 0;

	chip->support_ms_8bit = 1;
	chip->s3_pwr_off_delay = 1000;
पूर्ण

अटल पूर्णांक rtsx_probe(काष्ठा pci_dev *pci,
		      स्थिर काष्ठा pci_device_id *pci_id)
अणु
	काष्ठा Scsi_Host *host;
	काष्ठा rtsx_dev *dev;
	पूर्णांक err = 0;
	काष्ठा task_काष्ठा *th;

	dev_dbg(&pci->dev, "Realtek PCI-E card reader detected\n");

	err = pcim_enable_device(pci);
	अगर (err < 0) अणु
		dev_err(&pci->dev, "PCI enable device failed!\n");
		वापस err;
	पूर्ण

	err = pci_request_regions(pci, CR_DRIVER_NAME);
	अगर (err < 0) अणु
		dev_err(&pci->dev, "PCI request regions for %s failed!\n",
			CR_DRIVER_NAME);
		वापस err;
	पूर्ण

	/*
	 * Ask the SCSI layer to allocate a host काष्ठाure, with extra
	 * space at the end क्रम our निजी rtsx_dev काष्ठाure.
	 */
	host = scsi_host_alloc(&rtsx_host_ढाँचा, माप(*dev));
	अगर (!host) अणु
		dev_err(&pci->dev, "Unable to allocate the scsi host\n");
		err = -ENOMEM;
		जाओ scsi_host_alloc_fail;
	पूर्ण

	dev = host_to_rtsx(host);
	स_रखो(dev, 0, माप(काष्ठा rtsx_dev));

	dev->chip = kzalloc(माप(*dev->chip), GFP_KERNEL);
	अगर (!dev->chip) अणु
		err = -ENOMEM;
		जाओ chip_alloc_fail;
	पूर्ण

	spin_lock_init(&dev->reg_lock);
	mutex_init(&dev->dev_mutex);
	init_completion(&dev->cmnd_पढ़ोy);
	init_completion(&dev->control_निकास);
	init_completion(&dev->polling_निकास);
	init_completion(&dev->notअगरy);
	init_completion(&dev->scanning_करोne);
	init_रुकोqueue_head(&dev->delay_रुको);

	dev->pci = pci;
	dev->irq = -1;

	dev_info(&pci->dev, "Resource length: 0x%x\n",
		 (अचिन्हित पूर्णांक)pci_resource_len(pci, 0));
	dev->addr = pci_resource_start(pci, 0);
	dev->remap_addr = ioremap(dev->addr, pci_resource_len(pci, 0));
	अगर (!dev->remap_addr) अणु
		dev_err(&pci->dev, "ioremap error\n");
		err = -ENXIO;
		जाओ ioremap_fail;
	पूर्ण

	/*
	 * Using "unsigned long" cast here to eliminate gcc warning in
	 * 64-bit प्रणाली
	 */
	dev_info(&pci->dev, "Original address: 0x%lx, remapped address: 0x%lx\n",
		 (अचिन्हित दीर्घ)(dev->addr), (अचिन्हित दीर्घ)(dev->remap_addr));

	dev->rtsx_resv_buf = dmam_alloc_coherent(&pci->dev, RTSX_RESV_BUF_LEN,
						 &dev->rtsx_resv_buf_addr,
						 GFP_KERNEL);
	अगर (!dev->rtsx_resv_buf) अणु
		dev_err(&pci->dev, "alloc dma buffer fail\n");
		err = -ENXIO;
		जाओ dma_alloc_fail;
	पूर्ण
	dev->chip->host_cmds_ptr = dev->rtsx_resv_buf;
	dev->chip->host_cmds_addr = dev->rtsx_resv_buf_addr;
	dev->chip->host_sg_tbl_ptr = dev->rtsx_resv_buf + HOST_CMDS_BUF_LEN;
	dev->chip->host_sg_tbl_addr = dev->rtsx_resv_buf_addr +
				      HOST_CMDS_BUF_LEN;

	dev->chip->rtsx = dev;

	rtsx_init_options(dev->chip);

	dev_info(&pci->dev, "pci->irq = %d\n", pci->irq);

	अगर (dev->chip->msi_en) अणु
		अगर (pci_alloc_irq_vectors(pci, 1, 1, PCI_IRQ_MSI) < 0)
			dev->chip->msi_en = 0;
	पूर्ण

	अगर (rtsx_acquire_irq(dev) < 0) अणु
		err = -EBUSY;
		जाओ irq_acquire_fail;
	पूर्ण

	pci_set_master(pci);
	synchronize_irq(dev->irq);

	rtsx_init_chip(dev->chip);

	/*
	 * set the supported max_lun and max_id क्रम the scsi host
	 * NOTE: the minimal value of max_id is 1
	 */
	host->max_id = 1;
	host->max_lun = dev->chip->max_lun;

	/* Start up our control thपढ़ो */
	th = kthपढ़ो_run(rtsx_control_thपढ़ो, dev, CR_DRIVER_NAME);
	अगर (IS_ERR(th)) अणु
		dev_err(&pci->dev, "Unable to start control thread\n");
		err = PTR_ERR(th);
		जाओ control_thपढ़ो_fail;
	पूर्ण
	dev->ctl_thपढ़ो = th;

	err = scsi_add_host(host, &pci->dev);
	अगर (err) अणु
		dev_err(&pci->dev, "Unable to add the scsi host\n");
		जाओ scsi_add_host_fail;
	पूर्ण

	/* Start up the thपढ़ो क्रम delayed SCSI-device scanning */
	th = kthपढ़ो_run(rtsx_scan_thपढ़ो, dev, "rtsx-scan");
	अगर (IS_ERR(th)) अणु
		dev_err(&pci->dev, "Unable to start the device-scanning thread\n");
		complete(&dev->scanning_करोne);
		err = PTR_ERR(th);
		जाओ scan_thपढ़ो_fail;
	पूर्ण

	/* Start up the thपढ़ो क्रम polling thपढ़ो */
	th = kthपढ़ो_run(rtsx_polling_thपढ़ो, dev, "rtsx-polling");
	अगर (IS_ERR(th)) अणु
		dev_err(&pci->dev, "Unable to start the device-polling thread\n");
		err = PTR_ERR(th);
		जाओ scan_thपढ़ो_fail;
	पूर्ण
	dev->polling_thपढ़ो = th;

	pci_set_drvdata(pci, dev);

	वापस 0;

	/* We come here अगर there are any problems */
scan_thपढ़ो_fail:
	quiesce_and_हटाओ_host(dev);
scsi_add_host_fail:
	complete(&dev->cmnd_पढ़ोy);
	रुको_क्रम_completion(&dev->control_निकास);
control_thपढ़ो_fail:
	मुक्त_irq(dev->irq, (व्योम *)dev);
	rtsx_release_chip(dev->chip);
irq_acquire_fail:
	dev->chip->host_cmds_ptr = शून्य;
	dev->chip->host_sg_tbl_ptr = शून्य;
	अगर (dev->chip->msi_en)
		pci_मुक्त_irq_vectors(dev->pci);
dma_alloc_fail:
	iounmap(dev->remap_addr);
ioremap_fail:
	kमुक्त(dev->chip);
chip_alloc_fail:
	dev_err(&pci->dev, "%s failed\n", __func__);
	scsi_host_put(host);
scsi_host_alloc_fail:
	pci_release_regions(pci);
	वापस err;
पूर्ण

अटल व्योम rtsx_हटाओ(काष्ठा pci_dev *pci)
अणु
	काष्ठा rtsx_dev *dev = pci_get_drvdata(pci);

	dev_info(&pci->dev, "%s called\n", __func__);

	quiesce_and_हटाओ_host(dev);
	release_everything(dev);
	pci_release_regions(pci);
पूर्ण

/* PCI IDs */
अटल स्थिर काष्ठा pci_device_id rtsx_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_REALTEK, 0x5208),
		PCI_CLASS_OTHERS << 16, 0xFF0000 पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_REALTEK, 0x5288),
		PCI_CLASS_OTHERS << 16, 0xFF0000 पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, rtsx_ids);

अटल SIMPLE_DEV_PM_OPS(rtsx_pm_ops, rtsx_suspend, rtsx_resume);

/* pci_driver definition */
अटल काष्ठा pci_driver rtsx_driver = अणु
	.name = CR_DRIVER_NAME,
	.id_table = rtsx_ids,
	.probe = rtsx_probe,
	.हटाओ = rtsx_हटाओ,
	.driver.pm = &rtsx_pm_ops,
	.shutकरोwn = rtsx_shutकरोwn,
पूर्ण;

module_pci_driver(rtsx_driver);
