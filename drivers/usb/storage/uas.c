<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * USB Attached SCSI
 * Note that this is not the same as the USB Mass Storage driver
 *
 * Copyright Hans de Goede <hdegoede@redhat.com> क्रम Red Hat, Inc. 2013 - 2016
 * Copyright Matthew Wilcox क्रम Intel Corp, 2010
 * Copyright Sarah Sharp क्रम Intel Corp, 2010
 */

#समावेश <linux/blkdev.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb_usual.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/usb/storage.h>
#समावेश <linux/usb/uas.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_dbg.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_tcq.h>

#समावेश "uas-detect.h"
#समावेश "scsiglue.h"

#घोषणा MAX_CMNDS 256

काष्ठा uas_dev_info अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा usb_device *udev;
	काष्ठा usb_anchor cmd_urbs;
	काष्ठा usb_anchor sense_urbs;
	काष्ठा usb_anchor data_urbs;
	अचिन्हित दीर्घ flags;
	पूर्णांक qdepth, resetting;
	अचिन्हित cmd_pipe, status_pipe, data_in_pipe, data_out_pipe;
	अचिन्हित use_streams:1;
	अचिन्हित shutकरोwn:1;
	काष्ठा scsi_cmnd *cmnd[MAX_CMNDS];
	spinlock_t lock;
	काष्ठा work_काष्ठा work;
	काष्ठा work_काष्ठा scan_work;      /* क्रम async scanning */
पूर्ण;

क्रमागत अणु
	SUBMIT_STATUS_URB	= BIT(1),
	ALLOC_DATA_IN_URB	= BIT(2),
	SUBMIT_DATA_IN_URB	= BIT(3),
	ALLOC_DATA_OUT_URB	= BIT(4),
	SUBMIT_DATA_OUT_URB	= BIT(5),
	ALLOC_CMD_URB		= BIT(6),
	SUBMIT_CMD_URB		= BIT(7),
	COMMAND_INFLIGHT        = BIT(8),
	DATA_IN_URB_INFLIGHT    = BIT(9),
	DATA_OUT_URB_INFLIGHT   = BIT(10),
	COMMAND_ABORTED         = BIT(11),
	IS_IN_WORK_LIST         = BIT(12),
पूर्ण;

/* Overrides scsi_poपूर्णांकer */
काष्ठा uas_cmd_info अणु
	अचिन्हित पूर्णांक state;
	अचिन्हित पूर्णांक uas_tag;
	काष्ठा urb *cmd_urb;
	काष्ठा urb *data_in_urb;
	काष्ठा urb *data_out_urb;
पूर्ण;

/* I hate क्रमward declarations, but I actually have a loop */
अटल पूर्णांक uas_submit_urbs(काष्ठा scsi_cmnd *cmnd,
				काष्ठा uas_dev_info *devinfo);
अटल व्योम uas_करो_work(काष्ठा work_काष्ठा *work);
अटल पूर्णांक uas_try_complete(काष्ठा scsi_cmnd *cmnd, स्थिर अक्षर *caller);
अटल व्योम uas_मुक्त_streams(काष्ठा uas_dev_info *devinfo);
अटल व्योम uas_log_cmd_state(काष्ठा scsi_cmnd *cmnd, स्थिर अक्षर *prefix,
				पूर्णांक status);

/*
 * This driver needs its own workqueue, as we need to control memory allocation.
 *
 * In the course of error handling and घातer management uas_रुको_क्रम_pending_cmnds()
 * needs to flush pending work items. In these contexts we cannot allocate memory
 * by करोing block IO as we would deadlock. For the same reason we cannot रुको
 * क्रम anything allocating memory not heeding these स्थिरraपूर्णांकs.
 *
 * So we have to control all work items that can be on the workqueue we flush.
 * Hence we cannot share a queue and need our own.
 */
अटल काष्ठा workqueue_काष्ठा *workqueue;

अटल व्योम uas_करो_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा uas_dev_info *devinfo =
		container_of(work, काष्ठा uas_dev_info, work);
	काष्ठा uas_cmd_info *cmdinfo;
	काष्ठा scsi_cmnd *cmnd;
	अचिन्हित दीर्घ flags;
	पूर्णांक i, err;

	spin_lock_irqsave(&devinfo->lock, flags);

	अगर (devinfo->resetting)
		जाओ out;

	क्रम (i = 0; i < devinfo->qdepth; i++) अणु
		अगर (!devinfo->cmnd[i])
			जारी;

		cmnd = devinfo->cmnd[i];
		cmdinfo = (व्योम *)&cmnd->SCp;

		अगर (!(cmdinfo->state & IS_IN_WORK_LIST))
			जारी;

		err = uas_submit_urbs(cmnd, cmnd->device->hostdata);
		अगर (!err)
			cmdinfo->state &= ~IS_IN_WORK_LIST;
		अन्यथा
			queue_work(workqueue, &devinfo->work);
	पूर्ण
out:
	spin_unlock_irqrestore(&devinfo->lock, flags);
पूर्ण

अटल व्योम uas_scan_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा uas_dev_info *devinfo =
		container_of(work, काष्ठा uas_dev_info, scan_work);
	काष्ठा Scsi_Host *shost = usb_get_पूर्णांकfdata(devinfo->पूर्णांकf);

	dev_dbg(&devinfo->पूर्णांकf->dev, "starting scan\n");
	scsi_scan_host(shost);
	dev_dbg(&devinfo->पूर्णांकf->dev, "scan complete\n");
पूर्ण

अटल व्योम uas_add_work(काष्ठा uas_cmd_info *cmdinfo)
अणु
	काष्ठा scsi_poपूर्णांकer *scp = (व्योम *)cmdinfo;
	काष्ठा scsi_cmnd *cmnd = container_of(scp, काष्ठा scsi_cmnd, SCp);
	काष्ठा uas_dev_info *devinfo = cmnd->device->hostdata;

	lockdep_निश्चित_held(&devinfo->lock);
	cmdinfo->state |= IS_IN_WORK_LIST;
	queue_work(workqueue, &devinfo->work);
पूर्ण

अटल व्योम uas_zap_pending(काष्ठा uas_dev_info *devinfo, पूर्णांक result)
अणु
	काष्ठा uas_cmd_info *cmdinfo;
	काष्ठा scsi_cmnd *cmnd;
	अचिन्हित दीर्घ flags;
	पूर्णांक i, err;

	spin_lock_irqsave(&devinfo->lock, flags);
	क्रम (i = 0; i < devinfo->qdepth; i++) अणु
		अगर (!devinfo->cmnd[i])
			जारी;

		cmnd = devinfo->cmnd[i];
		cmdinfo = (व्योम *)&cmnd->SCp;
		uas_log_cmd_state(cmnd, __func__, 0);
		/* Sense urbs were समाप्तed, clear COMMAND_INFLIGHT manually */
		cmdinfo->state &= ~COMMAND_INFLIGHT;
		cmnd->result = result << 16;
		err = uas_try_complete(cmnd, __func__);
		WARN_ON(err != 0);
	पूर्ण
	spin_unlock_irqrestore(&devinfo->lock, flags);
पूर्ण

अटल व्योम uas_sense(काष्ठा urb *urb, काष्ठा scsi_cmnd *cmnd)
अणु
	काष्ठा sense_iu *sense_iu = urb->transfer_buffer;
	काष्ठा scsi_device *sdev = cmnd->device;

	अगर (urb->actual_length > 16) अणु
		अचिन्हित len = be16_to_cpup(&sense_iu->len);
		अगर (len + 16 != urb->actual_length) अणु
			पूर्णांक newlen = min(len + 16, urb->actual_length) - 16;
			अगर (newlen < 0)
				newlen = 0;
			sdev_prपूर्णांकk(KERN_INFO, sdev, "%s: urb length %d "
				"disagrees with IU sense data length %d, "
				"using %d bytes of sense data\n", __func__,
					urb->actual_length, len, newlen);
			len = newlen;
		पूर्ण
		स_नकल(cmnd->sense_buffer, sense_iu->sense, len);
	पूर्ण

	cmnd->result = sense_iu->status;
पूर्ण

अटल व्योम uas_log_cmd_state(काष्ठा scsi_cmnd *cmnd, स्थिर अक्षर *prefix,
			      पूर्णांक status)
अणु
	काष्ठा uas_cmd_info *ci = (व्योम *)&cmnd->SCp;
	काष्ठा uas_cmd_info *cmdinfo = (व्योम *)&cmnd->SCp;

	अगर (status == -ENODEV) /* too late */
		वापस;

	scmd_prपूर्णांकk(KERN_INFO, cmnd,
		    "%s %d uas-tag %d inflight:%s%s%s%s%s%s%s%s%s%s%s%s ",
		    prefix, status, cmdinfo->uas_tag,
		    (ci->state & SUBMIT_STATUS_URB)     ? " s-st"  : "",
		    (ci->state & ALLOC_DATA_IN_URB)     ? " a-in"  : "",
		    (ci->state & SUBMIT_DATA_IN_URB)    ? " s-in"  : "",
		    (ci->state & ALLOC_DATA_OUT_URB)    ? " a-out" : "",
		    (ci->state & SUBMIT_DATA_OUT_URB)   ? " s-out" : "",
		    (ci->state & ALLOC_CMD_URB)         ? " a-cmd" : "",
		    (ci->state & SUBMIT_CMD_URB)        ? " s-cmd" : "",
		    (ci->state & COMMAND_INFLIGHT)      ? " CMD"   : "",
		    (ci->state & DATA_IN_URB_INFLIGHT)  ? " IN"    : "",
		    (ci->state & DATA_OUT_URB_INFLIGHT) ? " OUT"   : "",
		    (ci->state & COMMAND_ABORTED)       ? " abort" : "",
		    (ci->state & IS_IN_WORK_LIST)       ? " work"  : "");
	scsi_prपूर्णांक_command(cmnd);
पूर्ण

अटल व्योम uas_मुक्त_unsubmitted_urbs(काष्ठा scsi_cmnd *cmnd)
अणु
	काष्ठा uas_cmd_info *cmdinfo;

	अगर (!cmnd)
		वापस;

	cmdinfo = (व्योम *)&cmnd->SCp;

	अगर (cmdinfo->state & SUBMIT_CMD_URB)
		usb_मुक्त_urb(cmdinfo->cmd_urb);

	/* data urbs may have never gotten their submit flag set */
	अगर (!(cmdinfo->state & DATA_IN_URB_INFLIGHT))
		usb_मुक्त_urb(cmdinfo->data_in_urb);
	अगर (!(cmdinfo->state & DATA_OUT_URB_INFLIGHT))
		usb_मुक्त_urb(cmdinfo->data_out_urb);
पूर्ण

अटल पूर्णांक uas_try_complete(काष्ठा scsi_cmnd *cmnd, स्थिर अक्षर *caller)
अणु
	काष्ठा uas_cmd_info *cmdinfo = (व्योम *)&cmnd->SCp;
	काष्ठा uas_dev_info *devinfo = (व्योम *)cmnd->device->hostdata;

	lockdep_निश्चित_held(&devinfo->lock);
	अगर (cmdinfo->state & (COMMAND_INFLIGHT |
			      DATA_IN_URB_INFLIGHT |
			      DATA_OUT_URB_INFLIGHT |
			      COMMAND_ABORTED))
		वापस -EBUSY;
	devinfo->cmnd[cmdinfo->uas_tag - 1] = शून्य;
	uas_मुक्त_unsubmitted_urbs(cmnd);
	cmnd->scsi_करोne(cmnd);
	वापस 0;
पूर्ण

अटल व्योम uas_xfer_data(काष्ठा urb *urb, काष्ठा scsi_cmnd *cmnd,
			  अचिन्हित direction)
अणु
	काष्ठा uas_cmd_info *cmdinfo = (व्योम *)&cmnd->SCp;
	पूर्णांक err;

	cmdinfo->state |= direction | SUBMIT_STATUS_URB;
	err = uas_submit_urbs(cmnd, cmnd->device->hostdata);
	अगर (err) अणु
		uas_add_work(cmdinfo);
	पूर्ण
पूर्ण

अटल bool uas_evaluate_response_iu(काष्ठा response_iu *riu, काष्ठा scsi_cmnd *cmnd)
अणु
	u8 response_code = riu->response_code;

	चयन (response_code) अणु
	हाल RC_INCORRECT_LUN:
		set_host_byte(cmnd, DID_BAD_TARGET);
		अवरोध;
	हाल RC_TMF_SUCCEEDED:
		set_host_byte(cmnd, DID_OK);
		अवरोध;
	हाल RC_TMF_NOT_SUPPORTED:
		set_host_byte(cmnd, DID_TARGET_FAILURE);
		अवरोध;
	शेष:
		uas_log_cmd_state(cmnd, "response iu", response_code);
		set_host_byte(cmnd, DID_ERROR);
		अवरोध;
	पूर्ण

	वापस response_code == RC_TMF_SUCCEEDED;
पूर्ण

अटल व्योम uas_stat_cmplt(काष्ठा urb *urb)
अणु
	काष्ठा iu *iu = urb->transfer_buffer;
	काष्ठा Scsi_Host *shost = urb->context;
	काष्ठा uas_dev_info *devinfo = (काष्ठा uas_dev_info *)shost->hostdata;
	काष्ठा urb *data_in_urb = शून्य;
	काष्ठा urb *data_out_urb = शून्य;
	काष्ठा scsi_cmnd *cmnd;
	काष्ठा uas_cmd_info *cmdinfo;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक idx;
	पूर्णांक status = urb->status;
	bool success;

	spin_lock_irqsave(&devinfo->lock, flags);

	अगर (devinfo->resetting)
		जाओ out;

	अगर (status) अणु
		अगर (status != -ENOENT && status != -ECONNRESET && status != -ESHUTDOWN)
			dev_err(&urb->dev->dev, "stat urb: status %d\n", status);
		जाओ out;
	पूर्ण

	idx = be16_to_cpup(&iu->tag) - 1;
	अगर (idx >= MAX_CMNDS || !devinfo->cmnd[idx]) अणु
		dev_err(&urb->dev->dev,
			"stat urb: no pending cmd for uas-tag %d\n", idx + 1);
		जाओ out;
	पूर्ण

	cmnd = devinfo->cmnd[idx];
	cmdinfo = (व्योम *)&cmnd->SCp;

	अगर (!(cmdinfo->state & COMMAND_INFLIGHT)) अणु
		uas_log_cmd_state(cmnd, "unexpected status cmplt", 0);
		जाओ out;
	पूर्ण

	चयन (iu->iu_id) अणु
	हाल IU_ID_STATUS:
		uas_sense(urb, cmnd);
		अगर (cmnd->result != 0) अणु
			/* cancel data transfers on error */
			data_in_urb = usb_get_urb(cmdinfo->data_in_urb);
			data_out_urb = usb_get_urb(cmdinfo->data_out_urb);
		पूर्ण
		cmdinfo->state &= ~COMMAND_INFLIGHT;
		uas_try_complete(cmnd, __func__);
		अवरोध;
	हाल IU_ID_READ_READY:
		अगर (!cmdinfo->data_in_urb ||
				(cmdinfo->state & DATA_IN_URB_INFLIGHT)) अणु
			uas_log_cmd_state(cmnd, "unexpected read rdy", 0);
			अवरोध;
		पूर्ण
		uas_xfer_data(urb, cmnd, SUBMIT_DATA_IN_URB);
		अवरोध;
	हाल IU_ID_WRITE_READY:
		अगर (!cmdinfo->data_out_urb ||
				(cmdinfo->state & DATA_OUT_URB_INFLIGHT)) अणु
			uas_log_cmd_state(cmnd, "unexpected write rdy", 0);
			अवरोध;
		पूर्ण
		uas_xfer_data(urb, cmnd, SUBMIT_DATA_OUT_URB);
		अवरोध;
	हाल IU_ID_RESPONSE:
		cmdinfo->state &= ~COMMAND_INFLIGHT;
		success = uas_evaluate_response_iu((काष्ठा response_iu *)iu, cmnd);
		अगर (!success) अणु
			/* Error, cancel data transfers */
			data_in_urb = usb_get_urb(cmdinfo->data_in_urb);
			data_out_urb = usb_get_urb(cmdinfo->data_out_urb);
		पूर्ण
		uas_try_complete(cmnd, __func__);
		अवरोध;
	शेष:
		uas_log_cmd_state(cmnd, "bogus IU", iu->iu_id);
	पूर्ण
out:
	usb_मुक्त_urb(urb);
	spin_unlock_irqrestore(&devinfo->lock, flags);

	/* Unlinking of data urbs must be करोne without holding the lock */
	अगर (data_in_urb) अणु
		usb_unlink_urb(data_in_urb);
		usb_put_urb(data_in_urb);
	पूर्ण
	अगर (data_out_urb) अणु
		usb_unlink_urb(data_out_urb);
		usb_put_urb(data_out_urb);
	पूर्ण
पूर्ण

अटल व्योम uas_data_cmplt(काष्ठा urb *urb)
अणु
	काष्ठा scsi_cmnd *cmnd = urb->context;
	काष्ठा uas_cmd_info *cmdinfo = (व्योम *)&cmnd->SCp;
	काष्ठा uas_dev_info *devinfo = (व्योम *)cmnd->device->hostdata;
	काष्ठा scsi_data_buffer *sdb = &cmnd->sdb;
	अचिन्हित दीर्घ flags;
	पूर्णांक status = urb->status;

	spin_lock_irqsave(&devinfo->lock, flags);

	अगर (cmdinfo->data_in_urb == urb) अणु
		cmdinfo->state &= ~DATA_IN_URB_INFLIGHT;
		cmdinfo->data_in_urb = शून्य;
	पूर्ण अन्यथा अगर (cmdinfo->data_out_urb == urb) अणु
		cmdinfo->state &= ~DATA_OUT_URB_INFLIGHT;
		cmdinfo->data_out_urb = शून्य;
	पूर्ण

	अगर (devinfo->resetting)
		जाओ out;

	/* Data urbs should not complete beक्रमe the cmd urb is submitted */
	अगर (cmdinfo->state & SUBMIT_CMD_URB) अणु
		uas_log_cmd_state(cmnd, "unexpected data cmplt", 0);
		जाओ out;
	पूर्ण

	अगर (status) अणु
		अगर (status != -ENOENT && status != -ECONNRESET && status != -ESHUTDOWN)
			uas_log_cmd_state(cmnd, "data cmplt err", status);
		/* error: no data transfered */
		scsi_set_resid(cmnd, sdb->length);
	पूर्ण अन्यथा अणु
		scsi_set_resid(cmnd, sdb->length - urb->actual_length);
	पूर्ण
	uas_try_complete(cmnd, __func__);
out:
	usb_मुक्त_urb(urb);
	spin_unlock_irqrestore(&devinfo->lock, flags);
पूर्ण

अटल व्योम uas_cmd_cmplt(काष्ठा urb *urb)
अणु
	अगर (urb->status)
		dev_err(&urb->dev->dev, "cmd cmplt err %d\n", urb->status);

	usb_मुक्त_urb(urb);
पूर्ण

अटल काष्ठा urb *uas_alloc_data_urb(काष्ठा uas_dev_info *devinfo, gfp_t gfp,
				      काष्ठा scsi_cmnd *cmnd,
				      क्रमागत dma_data_direction dir)
अणु
	काष्ठा usb_device *udev = devinfo->udev;
	काष्ठा uas_cmd_info *cmdinfo = (व्योम *)&cmnd->SCp;
	काष्ठा urb *urb = usb_alloc_urb(0, gfp);
	काष्ठा scsi_data_buffer *sdb = &cmnd->sdb;
	अचिन्हित पूर्णांक pipe = (dir == DMA_FROM_DEVICE)
		? devinfo->data_in_pipe : devinfo->data_out_pipe;

	अगर (!urb)
		जाओ out;
	usb_fill_bulk_urb(urb, udev, pipe, शून्य, sdb->length,
			  uas_data_cmplt, cmnd);
	अगर (devinfo->use_streams)
		urb->stream_id = cmdinfo->uas_tag;
	urb->num_sgs = udev->bus->sg_tablesize ? sdb->table.nents : 0;
	urb->sg = sdb->table.sgl;
 out:
	वापस urb;
पूर्ण

अटल काष्ठा urb *uas_alloc_sense_urb(काष्ठा uas_dev_info *devinfo, gfp_t gfp,
				       काष्ठा scsi_cmnd *cmnd)
अणु
	काष्ठा usb_device *udev = devinfo->udev;
	काष्ठा uas_cmd_info *cmdinfo = (व्योम *)&cmnd->SCp;
	काष्ठा urb *urb = usb_alloc_urb(0, gfp);
	काष्ठा sense_iu *iu;

	अगर (!urb)
		जाओ out;

	iu = kzalloc(माप(*iu), gfp);
	अगर (!iu)
		जाओ मुक्त;

	usb_fill_bulk_urb(urb, udev, devinfo->status_pipe, iu, माप(*iu),
			  uas_stat_cmplt, cmnd->device->host);
	अगर (devinfo->use_streams)
		urb->stream_id = cmdinfo->uas_tag;
	urb->transfer_flags |= URB_FREE_BUFFER;
 out:
	वापस urb;
 मुक्त:
	usb_मुक्त_urb(urb);
	वापस शून्य;
पूर्ण

अटल काष्ठा urb *uas_alloc_cmd_urb(काष्ठा uas_dev_info *devinfo, gfp_t gfp,
					काष्ठा scsi_cmnd *cmnd)
अणु
	काष्ठा usb_device *udev = devinfo->udev;
	काष्ठा scsi_device *sdev = cmnd->device;
	काष्ठा uas_cmd_info *cmdinfo = (व्योम *)&cmnd->SCp;
	काष्ठा urb *urb = usb_alloc_urb(0, gfp);
	काष्ठा command_iu *iu;
	पूर्णांक len;

	अगर (!urb)
		जाओ out;

	len = cmnd->cmd_len - 16;
	अगर (len < 0)
		len = 0;
	len = ALIGN(len, 4);
	iu = kzalloc(माप(*iu) + len, gfp);
	अगर (!iu)
		जाओ मुक्त;

	iu->iu_id = IU_ID_COMMAND;
	iu->tag = cpu_to_be16(cmdinfo->uas_tag);
	iu->prio_attr = UAS_SIMPLE_TAG;
	iu->len = len;
	पूर्णांक_to_scsilun(sdev->lun, &iu->lun);
	स_नकल(iu->cdb, cmnd->cmnd, cmnd->cmd_len);

	usb_fill_bulk_urb(urb, udev, devinfo->cmd_pipe, iu, माप(*iu) + len,
							uas_cmd_cmplt, शून्य);
	urb->transfer_flags |= URB_FREE_BUFFER;
 out:
	वापस urb;
 मुक्त:
	usb_मुक्त_urb(urb);
	वापस शून्य;
पूर्ण

/*
 * Why should I request the Status IU beक्रमe sending the Command IU?  Spec
 * says to, but also says the device may receive them in any order.  Seems
 * daft to me.
 */

अटल काष्ठा urb *uas_submit_sense_urb(काष्ठा scsi_cmnd *cmnd, gfp_t gfp)
अणु
	काष्ठा uas_dev_info *devinfo = cmnd->device->hostdata;
	काष्ठा urb *urb;
	पूर्णांक err;

	urb = uas_alloc_sense_urb(devinfo, gfp, cmnd);
	अगर (!urb)
		वापस शून्य;
	usb_anchor_urb(urb, &devinfo->sense_urbs);
	err = usb_submit_urb(urb, gfp);
	अगर (err) अणु
		usb_unanchor_urb(urb);
		uas_log_cmd_state(cmnd, "sense submit err", err);
		usb_मुक्त_urb(urb);
		वापस शून्य;
	पूर्ण
	वापस urb;
पूर्ण

अटल पूर्णांक uas_submit_urbs(काष्ठा scsi_cmnd *cmnd,
			   काष्ठा uas_dev_info *devinfo)
अणु
	काष्ठा uas_cmd_info *cmdinfo = (व्योम *)&cmnd->SCp;
	काष्ठा urb *urb;
	पूर्णांक err;

	lockdep_निश्चित_held(&devinfo->lock);
	अगर (cmdinfo->state & SUBMIT_STATUS_URB) अणु
		urb = uas_submit_sense_urb(cmnd, GFP_ATOMIC);
		अगर (!urb)
			वापस SCSI_MLQUEUE_DEVICE_BUSY;
		cmdinfo->state &= ~SUBMIT_STATUS_URB;
	पूर्ण

	अगर (cmdinfo->state & ALLOC_DATA_IN_URB) अणु
		cmdinfo->data_in_urb = uas_alloc_data_urb(devinfo, GFP_ATOMIC,
							cmnd, DMA_FROM_DEVICE);
		अगर (!cmdinfo->data_in_urb)
			वापस SCSI_MLQUEUE_DEVICE_BUSY;
		cmdinfo->state &= ~ALLOC_DATA_IN_URB;
	पूर्ण

	अगर (cmdinfo->state & SUBMIT_DATA_IN_URB) अणु
		usb_anchor_urb(cmdinfo->data_in_urb, &devinfo->data_urbs);
		err = usb_submit_urb(cmdinfo->data_in_urb, GFP_ATOMIC);
		अगर (err) अणु
			usb_unanchor_urb(cmdinfo->data_in_urb);
			uas_log_cmd_state(cmnd, "data in submit err", err);
			वापस SCSI_MLQUEUE_DEVICE_BUSY;
		पूर्ण
		cmdinfo->state &= ~SUBMIT_DATA_IN_URB;
		cmdinfo->state |= DATA_IN_URB_INFLIGHT;
	पूर्ण

	अगर (cmdinfo->state & ALLOC_DATA_OUT_URB) अणु
		cmdinfo->data_out_urb = uas_alloc_data_urb(devinfo, GFP_ATOMIC,
							cmnd, DMA_TO_DEVICE);
		अगर (!cmdinfo->data_out_urb)
			वापस SCSI_MLQUEUE_DEVICE_BUSY;
		cmdinfo->state &= ~ALLOC_DATA_OUT_URB;
	पूर्ण

	अगर (cmdinfo->state & SUBMIT_DATA_OUT_URB) अणु
		usb_anchor_urb(cmdinfo->data_out_urb, &devinfo->data_urbs);
		err = usb_submit_urb(cmdinfo->data_out_urb, GFP_ATOMIC);
		अगर (err) अणु
			usb_unanchor_urb(cmdinfo->data_out_urb);
			uas_log_cmd_state(cmnd, "data out submit err", err);
			वापस SCSI_MLQUEUE_DEVICE_BUSY;
		पूर्ण
		cmdinfo->state &= ~SUBMIT_DATA_OUT_URB;
		cmdinfo->state |= DATA_OUT_URB_INFLIGHT;
	पूर्ण

	अगर (cmdinfo->state & ALLOC_CMD_URB) अणु
		cmdinfo->cmd_urb = uas_alloc_cmd_urb(devinfo, GFP_ATOMIC, cmnd);
		अगर (!cmdinfo->cmd_urb)
			वापस SCSI_MLQUEUE_DEVICE_BUSY;
		cmdinfo->state &= ~ALLOC_CMD_URB;
	पूर्ण

	अगर (cmdinfo->state & SUBMIT_CMD_URB) अणु
		usb_anchor_urb(cmdinfo->cmd_urb, &devinfo->cmd_urbs);
		err = usb_submit_urb(cmdinfo->cmd_urb, GFP_ATOMIC);
		अगर (err) अणु
			usb_unanchor_urb(cmdinfo->cmd_urb);
			uas_log_cmd_state(cmnd, "cmd submit err", err);
			वापस SCSI_MLQUEUE_DEVICE_BUSY;
		पूर्ण
		cmdinfo->cmd_urb = शून्य;
		cmdinfo->state &= ~SUBMIT_CMD_URB;
		cmdinfo->state |= COMMAND_INFLIGHT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक uas_queuecommand_lck(काष्ठा scsi_cmnd *cmnd,
					व्योम (*करोne)(काष्ठा scsi_cmnd *))
अणु
	काष्ठा scsi_device *sdev = cmnd->device;
	काष्ठा uas_dev_info *devinfo = sdev->hostdata;
	काष्ठा uas_cmd_info *cmdinfo = (व्योम *)&cmnd->SCp;
	अचिन्हित दीर्घ flags;
	पूर्णांक idx, err;

	BUILD_BUG_ON(माप(काष्ठा uas_cmd_info) > माप(काष्ठा scsi_poपूर्णांकer));

	/* Re-check scsi_block_requests now that we've the host-lock */
	अगर (cmnd->device->host->host_self_blocked)
		वापस SCSI_MLQUEUE_DEVICE_BUSY;

	अगर ((devinfo->flags & US_FL_NO_ATA_1X) &&
			(cmnd->cmnd[0] == ATA_12 || cmnd->cmnd[0] == ATA_16)) अणु
		स_नकल(cmnd->sense_buffer, usb_stor_sense_invalidCDB,
		       माप(usb_stor_sense_invalidCDB));
		cmnd->result = SAM_STAT_CHECK_CONDITION;
		cmnd->scsi_करोne(cmnd);
		वापस 0;
	पूर्ण

	spin_lock_irqsave(&devinfo->lock, flags);

	अगर (devinfo->resetting) अणु
		set_host_byte(cmnd, DID_ERROR);
		cmnd->scsi_करोne(cmnd);
		जाओ zombie;
	पूर्ण

	/* Find a मुक्त uas-tag */
	क्रम (idx = 0; idx < devinfo->qdepth; idx++) अणु
		अगर (!devinfo->cmnd[idx])
			अवरोध;
	पूर्ण
	अगर (idx == devinfo->qdepth) अणु
		spin_unlock_irqrestore(&devinfo->lock, flags);
		वापस SCSI_MLQUEUE_DEVICE_BUSY;
	पूर्ण

	cmnd->scsi_करोne = करोne;

	स_रखो(cmdinfo, 0, माप(*cmdinfo));
	cmdinfo->uas_tag = idx + 1; /* uas-tag == usb-stream-id, so 1 based */
	cmdinfo->state = SUBMIT_STATUS_URB | ALLOC_CMD_URB | SUBMIT_CMD_URB;

	चयन (cmnd->sc_data_direction) अणु
	हाल DMA_FROM_DEVICE:
		cmdinfo->state |= ALLOC_DATA_IN_URB | SUBMIT_DATA_IN_URB;
		अवरोध;
	हाल DMA_BIसूचीECTIONAL:
		cmdinfo->state |= ALLOC_DATA_IN_URB | SUBMIT_DATA_IN_URB;
		fallthrough;
	हाल DMA_TO_DEVICE:
		cmdinfo->state |= ALLOC_DATA_OUT_URB | SUBMIT_DATA_OUT_URB;
		अवरोध;
	हाल DMA_NONE:
		अवरोध;
	पूर्ण

	अगर (!devinfo->use_streams)
		cmdinfo->state &= ~(SUBMIT_DATA_IN_URB | SUBMIT_DATA_OUT_URB);

	err = uas_submit_urbs(cmnd, devinfo);
	/*
	 * in हाल of fatal errors the SCSI layer is peculiar
	 * a command that has finished is a success क्रम the purpose
	 * of queueing, no matter how fatal the error
	 */
	अगर (err == -ENODEV) अणु
		set_host_byte(cmnd, DID_ERROR);
		cmnd->scsi_करोne(cmnd);
		जाओ zombie;
	पूर्ण
	अगर (err) अणु
		/* If we did nothing, give up now */
		अगर (cmdinfo->state & SUBMIT_STATUS_URB) अणु
			spin_unlock_irqrestore(&devinfo->lock, flags);
			वापस SCSI_MLQUEUE_DEVICE_BUSY;
		पूर्ण
		uas_add_work(cmdinfo);
	पूर्ण

	devinfo->cmnd[idx] = cmnd;
zombie:
	spin_unlock_irqrestore(&devinfo->lock, flags);
	वापस 0;
पूर्ण

अटल DEF_SCSI_QCMD(uas_queuecommand)

/*
 * For now we करो not support actually sending an पात to the device, so
 * this eh always fails. Still we must define it to make sure that we've
 * dropped all references to the cmnd in question once this function निकासs.
 */
अटल पूर्णांक uas_eh_पात_handler(काष्ठा scsi_cmnd *cmnd)
अणु
	काष्ठा uas_cmd_info *cmdinfo = (व्योम *)&cmnd->SCp;
	काष्ठा uas_dev_info *devinfo = (व्योम *)cmnd->device->hostdata;
	काष्ठा urb *data_in_urb = शून्य;
	काष्ठा urb *data_out_urb = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&devinfo->lock, flags);

	uas_log_cmd_state(cmnd, __func__, 0);

	/* Ensure that try_complete करोes not call scsi_करोne */
	cmdinfo->state |= COMMAND_ABORTED;

	/* Drop all refs to this cmnd, समाप्त data urbs to अवरोध their ref */
	devinfo->cmnd[cmdinfo->uas_tag - 1] = शून्य;
	अगर (cmdinfo->state & DATA_IN_URB_INFLIGHT)
		data_in_urb = usb_get_urb(cmdinfo->data_in_urb);
	अगर (cmdinfo->state & DATA_OUT_URB_INFLIGHT)
		data_out_urb = usb_get_urb(cmdinfo->data_out_urb);

	uas_मुक्त_unsubmitted_urbs(cmnd);

	spin_unlock_irqrestore(&devinfo->lock, flags);

	अगर (data_in_urb) अणु
		usb_समाप्त_urb(data_in_urb);
		usb_put_urb(data_in_urb);
	पूर्ण
	अगर (data_out_urb) अणु
		usb_समाप्त_urb(data_out_urb);
		usb_put_urb(data_out_urb);
	पूर्ण

	वापस FAILED;
पूर्ण

अटल पूर्णांक uas_eh_device_reset_handler(काष्ठा scsi_cmnd *cmnd)
अणु
	काष्ठा scsi_device *sdev = cmnd->device;
	काष्ठा uas_dev_info *devinfo = sdev->hostdata;
	काष्ठा usb_device *udev = devinfo->udev;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	err = usb_lock_device_क्रम_reset(udev, devinfo->पूर्णांकf);
	अगर (err) अणु
		shost_prपूर्णांकk(KERN_ERR, sdev->host,
			     "%s FAILED to get lock err %d\n", __func__, err);
		वापस FAILED;
	पूर्ण

	shost_prपूर्णांकk(KERN_INFO, sdev->host, "%s start\n", __func__);

	spin_lock_irqsave(&devinfo->lock, flags);
	devinfo->resetting = 1;
	spin_unlock_irqrestore(&devinfo->lock, flags);

	usb_समाप्त_anchored_urbs(&devinfo->cmd_urbs);
	usb_समाप्त_anchored_urbs(&devinfo->sense_urbs);
	usb_समाप्त_anchored_urbs(&devinfo->data_urbs);
	uas_zap_pending(devinfo, DID_RESET);

	err = usb_reset_device(udev);

	spin_lock_irqsave(&devinfo->lock, flags);
	devinfo->resetting = 0;
	spin_unlock_irqrestore(&devinfo->lock, flags);

	usb_unlock_device(udev);

	अगर (err) अणु
		shost_prपूर्णांकk(KERN_INFO, sdev->host, "%s FAILED err %d\n",
			     __func__, err);
		वापस FAILED;
	पूर्ण

	shost_prपूर्णांकk(KERN_INFO, sdev->host, "%s success\n", __func__);
	वापस SUCCESS;
पूर्ण

अटल पूर्णांक uas_target_alloc(काष्ठा scsi_target *starget)
अणु
	काष्ठा uas_dev_info *devinfo = (काष्ठा uas_dev_info *)
			dev_to_shost(starget->dev.parent)->hostdata;

	अगर (devinfo->flags & US_FL_NO_REPORT_LUNS)
		starget->no_report_luns = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक uas_slave_alloc(काष्ठा scsi_device *sdev)
अणु
	काष्ठा uas_dev_info *devinfo =
		(काष्ठा uas_dev_info *)sdev->host->hostdata;

	sdev->hostdata = devinfo;

	/*
	 * The protocol has no requirements on alignment in the strict sense.
	 * Controllers may or may not have alignment restrictions.
	 * As this is not exported, we use an extremely conservative guess.
	 */
	blk_queue_update_dma_alignment(sdev->request_queue, (512 - 1));

	अगर (devinfo->flags & US_FL_MAX_SECTORS_64)
		blk_queue_max_hw_sectors(sdev->request_queue, 64);
	अन्यथा अगर (devinfo->flags & US_FL_MAX_SECTORS_240)
		blk_queue_max_hw_sectors(sdev->request_queue, 240);

	वापस 0;
पूर्ण

अटल पूर्णांक uas_slave_configure(काष्ठा scsi_device *sdev)
अणु
	काष्ठा uas_dev_info *devinfo = sdev->hostdata;

	अगर (devinfo->flags & US_FL_NO_REPORT_OPCODES)
		sdev->no_report_opcodes = 1;

	/* A few buggy USB-ATA bridges करोn't understand FUA */
	अगर (devinfo->flags & US_FL_BROKEN_FUA)
		sdev->broken_fua = 1;

	/* UAS also needs to support FL_ALWAYS_SYNC */
	अगर (devinfo->flags & US_FL_ALWAYS_SYNC) अणु
		sdev->skip_ms_page_3f = 1;
		sdev->skip_ms_page_8 = 1;
		sdev->wce_शेष_on = 1;
	पूर्ण

	/* Some disks cannot handle READ_CAPACITY_16 */
	अगर (devinfo->flags & US_FL_NO_READ_CAPACITY_16)
		sdev->no_पढ़ो_capacity_16 = 1;

	/* Some disks cannot handle WRITE_SAME */
	अगर (devinfo->flags & US_FL_NO_SAME)
		sdev->no_ग_लिखो_same = 1;
	/*
	 * Some disks वापस the total number of blocks in response
	 * to READ CAPACITY rather than the highest block number.
	 * If this device makes that mistake, tell the sd driver.
	 */
	अगर (devinfo->flags & US_FL_FIX_CAPACITY)
		sdev->fix_capacity = 1;

	/*
	 * in some हालs we have to guess
	 */
	अगर (devinfo->flags & US_FL_CAPACITY_HEURISTICS)
		sdev->guess_capacity = 1;

	/*
	 * Some devices करोn't like MODE SENSE with page=0x3f,
	 * which is the command used क्रम checking अगर a device
	 * is ग_लिखो-रक्षित.  Now that we tell the sd driver
	 * to करो a 192-byte transfer with this command the
	 * majority of devices work fine, but a few still can't
	 * handle it.  The sd driver will simply assume those
	 * devices are ग_लिखो-enabled.
	 */
	अगर (devinfo->flags & US_FL_NO_WP_DETECT)
		sdev->skip_ms_page_3f = 1;

	scsi_change_queue_depth(sdev, devinfo->qdepth - 2);
	वापस 0;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा uas_host_ढाँचा = अणु
	.module = THIS_MODULE,
	.name = "uas",
	.queuecommand = uas_queuecommand,
	.target_alloc = uas_target_alloc,
	.slave_alloc = uas_slave_alloc,
	.slave_configure = uas_slave_configure,
	.eh_पात_handler = uas_eh_पात_handler,
	.eh_device_reset_handler = uas_eh_device_reset_handler,
	.this_id = -1,
	.skip_settle_delay = 1,
	.dma_boundary = PAGE_SIZE - 1,
पूर्ण;

#घोषणा UNUSUAL_DEV(id_venकरोr, id_product, bcdDeviceMin, bcdDeviceMax, \
		    venकरोrName, productName, useProtocol, useTransport, \
		    initFunction, flags) \
अणु USB_DEVICE_VER(id_venकरोr, id_product, bcdDeviceMin, bcdDeviceMax), \
	.driver_info = (flags) पूर्ण

अटल काष्ठा usb_device_id uas_usb_ids[] = अणु
#	include "unusual_uas.h"
	अणु USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, USB_SC_SCSI, USB_PR_BULK) पूर्ण,
	अणु USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, USB_SC_SCSI, USB_PR_UAS) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, uas_usb_ids);

#अघोषित UNUSUAL_DEV

अटल पूर्णांक uas_चयन_पूर्णांकerface(काष्ठा usb_device *udev,
				काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_host_पूर्णांकerface *alt;

	alt = uas_find_uas_alt_setting(पूर्णांकf);
	अगर (!alt)
		वापस -ENODEV;

	वापस usb_set_पूर्णांकerface(udev, alt->desc.bInterfaceNumber,
			alt->desc.bAlternateSetting);
पूर्ण

अटल पूर्णांक uas_configure_endpoपूर्णांकs(काष्ठा uas_dev_info *devinfo)
अणु
	काष्ठा usb_host_endpoपूर्णांक *eps[4] = अणु पूर्ण;
	काष्ठा usb_device *udev = devinfo->udev;
	पूर्णांक r;

	r = uas_find_endpoपूर्णांकs(devinfo->पूर्णांकf->cur_altsetting, eps);
	अगर (r)
		वापस r;

	devinfo->cmd_pipe = usb_sndbulkpipe(udev,
					    usb_endpoपूर्णांक_num(&eps[0]->desc));
	devinfo->status_pipe = usb_rcvbulkpipe(udev,
					    usb_endpoपूर्णांक_num(&eps[1]->desc));
	devinfo->data_in_pipe = usb_rcvbulkpipe(udev,
					    usb_endpoपूर्णांक_num(&eps[2]->desc));
	devinfo->data_out_pipe = usb_sndbulkpipe(udev,
					    usb_endpoपूर्णांक_num(&eps[3]->desc));

	अगर (udev->speed < USB_SPEED_SUPER) अणु
		devinfo->qdepth = 32;
		devinfo->use_streams = 0;
	पूर्ण अन्यथा अणु
		devinfo->qdepth = usb_alloc_streams(devinfo->पूर्णांकf, eps + 1,
						    3, MAX_CMNDS, GFP_NOIO);
		अगर (devinfo->qdepth < 0)
			वापस devinfo->qdepth;
		devinfo->use_streams = 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम uas_मुक्त_streams(काष्ठा uas_dev_info *devinfo)
अणु
	काष्ठा usb_device *udev = devinfo->udev;
	काष्ठा usb_host_endpoपूर्णांक *eps[3];

	eps[0] = usb_pipe_endpoपूर्णांक(udev, devinfo->status_pipe);
	eps[1] = usb_pipe_endpoपूर्णांक(udev, devinfo->data_in_pipe);
	eps[2] = usb_pipe_endpoपूर्णांक(udev, devinfo->data_out_pipe);
	usb_मुक्त_streams(devinfo->पूर्णांकf, eps, 3, GFP_NOIO);
पूर्ण

अटल पूर्णांक uas_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id)
अणु
	पूर्णांक result = -ENOMEM;
	काष्ठा Scsi_Host *shost = शून्य;
	काष्ठा uas_dev_info *devinfo;
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	अचिन्हित दीर्घ dev_flags;

	अगर (!uas_use_uas_driver(पूर्णांकf, id, &dev_flags))
		वापस -ENODEV;

	अगर (uas_चयन_पूर्णांकerface(udev, पूर्णांकf))
		वापस -ENODEV;

	shost = scsi_host_alloc(&uas_host_ढाँचा,
				माप(काष्ठा uas_dev_info));
	अगर (!shost)
		जाओ set_alt0;

	shost->max_cmd_len = 16 + 252;
	shost->max_id = 1;
	shost->max_lun = 256;
	shost->max_channel = 0;
	shost->sg_tablesize = udev->bus->sg_tablesize;

	devinfo = (काष्ठा uas_dev_info *)shost->hostdata;
	devinfo->पूर्णांकf = पूर्णांकf;
	devinfo->udev = udev;
	devinfo->resetting = 0;
	devinfo->shutकरोwn = 0;
	devinfo->flags = dev_flags;
	init_usb_anchor(&devinfo->cmd_urbs);
	init_usb_anchor(&devinfo->sense_urbs);
	init_usb_anchor(&devinfo->data_urbs);
	spin_lock_init(&devinfo->lock);
	INIT_WORK(&devinfo->work, uas_करो_work);
	INIT_WORK(&devinfo->scan_work, uas_scan_work);

	result = uas_configure_endpoपूर्णांकs(devinfo);
	अगर (result)
		जाओ set_alt0;

	/*
	 * 1 tag is reserved क्रम untagged commands +
	 * 1 tag to aव्योम off by one errors in some bridge firmwares
	 */
	shost->can_queue = devinfo->qdepth - 2;

	usb_set_पूर्णांकfdata(पूर्णांकf, shost);
	result = scsi_add_host(shost, &पूर्णांकf->dev);
	अगर (result)
		जाओ मुक्त_streams;

	/* Submit the delayed_work क्रम SCSI-device scanning */
	schedule_work(&devinfo->scan_work);

	वापस result;

मुक्त_streams:
	uas_मुक्त_streams(devinfo);
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
set_alt0:
	usb_set_पूर्णांकerface(udev, पूर्णांकf->altsetting[0].desc.bInterfaceNumber, 0);
	अगर (shost)
		scsi_host_put(shost);
	वापस result;
पूर्ण

अटल पूर्णांक uas_cmnd_list_empty(काष्ठा uas_dev_info *devinfo)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i, r = 1;

	spin_lock_irqsave(&devinfo->lock, flags);

	क्रम (i = 0; i < devinfo->qdepth; i++) अणु
		अगर (devinfo->cmnd[i]) अणु
			r = 0; /* Not empty */
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&devinfo->lock, flags);

	वापस r;
पूर्ण

/*
 * Wait क्रम any pending cmnds to complete, on usb-2 sense_urbs may temporarily
 * get empty जबतक there still is more work to करो due to sense-urbs completing
 * with a READ/WRITE_READY iu code, so keep रुकोing until the list माला_लो empty.
 */
अटल पूर्णांक uas_रुको_क्रम_pending_cmnds(काष्ठा uas_dev_info *devinfo)
अणु
	अचिन्हित दीर्घ start_समय;
	पूर्णांक r;

	start_समय = jअगरfies;
	करो अणु
		flush_work(&devinfo->work);

		r = usb_रुको_anchor_empty_समयout(&devinfo->sense_urbs, 5000);
		अगर (r == 0)
			वापस -ETIME;

		r = usb_रुको_anchor_empty_समयout(&devinfo->data_urbs, 500);
		अगर (r == 0)
			वापस -ETIME;

		अगर (समय_after(jअगरfies, start_समय + 5 * HZ))
			वापस -ETIME;
	पूर्ण जबतक (!uas_cmnd_list_empty(devinfo));

	वापस 0;
पूर्ण

अटल पूर्णांक uas_pre_reset(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा Scsi_Host *shost = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा uas_dev_info *devinfo = (काष्ठा uas_dev_info *)shost->hostdata;
	अचिन्हित दीर्घ flags;

	अगर (devinfo->shutकरोwn)
		वापस 0;

	/* Block new requests */
	spin_lock_irqsave(shost->host_lock, flags);
	scsi_block_requests(shost);
	spin_unlock_irqrestore(shost->host_lock, flags);

	अगर (uas_रुको_क्रम_pending_cmnds(devinfo) != 0) अणु
		shost_prपूर्णांकk(KERN_ERR, shost, "%s: timed out\n", __func__);
		scsi_unblock_requests(shost);
		वापस 1;
	पूर्ण

	uas_मुक्त_streams(devinfo);

	वापस 0;
पूर्ण

अटल पूर्णांक uas_post_reset(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा Scsi_Host *shost = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा uas_dev_info *devinfo = (काष्ठा uas_dev_info *)shost->hostdata;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	अगर (devinfo->shutकरोwn)
		वापस 0;

	err = uas_configure_endpoपूर्णांकs(devinfo);
	अगर (err && err != -ENODEV)
		shost_prपूर्णांकk(KERN_ERR, shost,
			     "%s: alloc streams error %d after reset",
			     __func__, err);

	/* we must unblock the host in every हाल lest we deadlock */
	spin_lock_irqsave(shost->host_lock, flags);
	scsi_report_bus_reset(shost, 0);
	spin_unlock_irqrestore(shost->host_lock, flags);

	scsi_unblock_requests(shost);

	वापस err ? 1 : 0;
पूर्ण

अटल पूर्णांक uas_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा Scsi_Host *shost = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा uas_dev_info *devinfo = (काष्ठा uas_dev_info *)shost->hostdata;

	अगर (uas_रुको_क्रम_pending_cmnds(devinfo) != 0) अणु
		shost_prपूर्णांकk(KERN_ERR, shost, "%s: timed out\n", __func__);
		वापस -ETIME;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक uas_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक uas_reset_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा Scsi_Host *shost = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा uas_dev_info *devinfo = (काष्ठा uas_dev_info *)shost->hostdata;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	err = uas_configure_endpoपूर्णांकs(devinfo);
	अगर (err) अणु
		shost_prपूर्णांकk(KERN_ERR, shost,
			     "%s: alloc streams error %d after reset",
			     __func__, err);
		वापस -EIO;
	पूर्ण

	spin_lock_irqsave(shost->host_lock, flags);
	scsi_report_bus_reset(shost, 0);
	spin_unlock_irqrestore(shost->host_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम uas_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा Scsi_Host *shost = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा uas_dev_info *devinfo = (काष्ठा uas_dev_info *)shost->hostdata;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&devinfo->lock, flags);
	devinfo->resetting = 1;
	spin_unlock_irqrestore(&devinfo->lock, flags);

	cancel_work_sync(&devinfo->work);
	usb_समाप्त_anchored_urbs(&devinfo->cmd_urbs);
	usb_समाप्त_anchored_urbs(&devinfo->sense_urbs);
	usb_समाप्त_anchored_urbs(&devinfo->data_urbs);
	uas_zap_pending(devinfo, DID_NO_CONNECT);

	/*
	 * Prevent SCSI scanning (अगर it hasn't started yet)
	 * or रुको क्रम the SCSI-scanning routine to stop.
	 */
	cancel_work_sync(&devinfo->scan_work);

	scsi_हटाओ_host(shost);
	uas_मुक्त_streams(devinfo);
	scsi_host_put(shost);
पूर्ण

/*
 * Put the device back in usb-storage mode on shutकरोwn, as some BIOS-es
 * hang on reboot when the device is still in uas mode. Note the reset is
 * necessary as some devices won't revert to usb-storage mode without it.
 */
अटल व्योम uas_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा Scsi_Host *shost = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा uas_dev_info *devinfo = (काष्ठा uas_dev_info *)shost->hostdata;

	अगर (प्रणाली_state != SYSTEM_RESTART)
		वापस;

	devinfo->shutकरोwn = 1;
	uas_मुक्त_streams(devinfo);
	usb_set_पूर्णांकerface(udev, पूर्णांकf->altsetting[0].desc.bInterfaceNumber, 0);
	usb_reset_device(udev);
पूर्ण

अटल काष्ठा usb_driver uas_driver = अणु
	.name = "uas",
	.probe = uas_probe,
	.disconnect = uas_disconnect,
	.pre_reset = uas_pre_reset,
	.post_reset = uas_post_reset,
	.suspend = uas_suspend,
	.resume = uas_resume,
	.reset_resume = uas_reset_resume,
	.drvwrap.driver.shutकरोwn = uas_shutकरोwn,
	.id_table = uas_usb_ids,
पूर्ण;

अटल पूर्णांक __init uas_init(व्योम)
अणु
	पूर्णांक rv;

	workqueue = alloc_workqueue("uas", WQ_MEM_RECLAIM, 0);
	अगर (!workqueue)
		वापस -ENOMEM;

	rv = usb_रेजिस्टर(&uas_driver);
	अगर (rv) अणु
		destroy_workqueue(workqueue);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास uas_निकास(व्योम)
अणु
	usb_deरेजिस्टर(&uas_driver);
	destroy_workqueue(workqueue);
पूर्ण

module_init(uas_init);
module_निकास(uas_निकास);

MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(USB_STORAGE);
MODULE_AUTHOR(
	"Hans de Goede <hdegoede@redhat.com>, Matthew Wilcox and Sarah Sharp");
