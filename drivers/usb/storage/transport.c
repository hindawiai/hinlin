<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम USB Mass Storage compliant devices
 *
 * Current development and मुख्यtenance by:
 *   (c) 1999-2002 Matthew Dharm (mdharm-usb@one-eyed-alien.net)
 *
 * Developed with the assistance of:
 *   (c) 2000 David L. Brown, Jr. (usb-storage@davidb.org)
 *   (c) 2000 Stephen J. Gowdy (SGowdy@lbl.gov)
 *   (c) 2002 Alan Stern <stern@rowland.org>
 *
 * Initial work by:
 *   (c) 1999 Michael Gee (michael@linuxspecअगरic.com)
 *
 * This driver is based on the 'USB Mass Storage Class' करोcument. This
 * describes in detail the protocol used to communicate with such
 * devices.  Clearly, the designers had SCSI and ATAPI commands in
 * mind when they created this करोcument.  The commands are all very
 * similar to commands in the SCSI-II and ATAPI specअगरications.
 *
 * It is important to note that in a number of हालs this class
 * exhibits class-specअगरic exemptions from the USB specअगरication.
 * Notably the usage of NAK, STALL and ACK dअगरfers from the norm, in
 * that they are used to communicate रुको, failed and OK on commands.
 *
 * Also, क्रम certain devices, the पूर्णांकerrupt endpoपूर्णांक is used to convey
 * status of a command.
 */

#समावेश <linux/sched.h>
#समावेश <linux/gfp.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>

#समावेश <linux/usb/quirks.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_device.h>

#समावेश "usb.h"
#समावेश "transport.h"
#समावेश "protocol.h"
#समावेश "scsiglue.h"
#समावेश "debug.h"

#समावेश <linux/blkdev.h>
#समावेश "../../scsi/sd.h"


/***********************************************************************
 * Data transfer routines
 ***********************************************************************/

/*
 * This is subtle, so pay attention:
 * ---------------------------------
 * We're very concerned about races with a command पात.  Hanging this code
 * is a sure fire way to hang the kernel.  (Note that this discussion applies
 * only to transactions resulting from a scsi queued-command, since only
 * these transactions are subject to a scsi पात.  Other transactions, such
 * as those occurring during device-specअगरic initialization, must be handled
 * by a separate code path.)
 *
 * The पात function (usb_storage_command_पात() in scsiglue.c) first
 * sets the machine state and the ABORTING bit in us->dflags to prevent
 * new URBs from being submitted.  It then calls usb_stor_stop_transport()
 * below, which atomically tests-and-clears the URB_ACTIVE bit in us->dflags
 * to see अगर the current_urb needs to be stopped.  Likewise, the SG_ACTIVE
 * bit is tested to see अगर the current_sg scatter-gather request needs to be
 * stopped.  The समयout callback routine करोes much the same thing.
 *
 * When a disconnect occurs, the DISCONNECTING bit in us->dflags is set to
 * prevent new URBs from being submitted, and usb_stor_stop_transport() is
 * called to stop any ongoing requests.
 *
 * The submit function first verअगरies that the submitting is allowed
 * (neither ABORTING nor DISCONNECTING bits are set) and that the submit
 * completes without errors, and only then sets the URB_ACTIVE bit.  This
 * prevents the stop_transport() function from trying to cancel the URB
 * जबतक the submit call is underway.  Next, the submit function must test
 * the flags to see अगर an पात or disconnect occurred during the submission
 * or beक्रमe the URB_ACTIVE bit was set.  If so, it's essential to cancel
 * the URB अगर it hasn't been cancelled alपढ़ोy (i.e., अगर the URB_ACTIVE bit
 * is still set).  Either way, the function must then रुको क्रम the URB to
 * finish.  Note that the URB can still be in progress even after a call to
 * usb_unlink_urb() वापसs.
 *
 * The idea is that (1) once the ABORTING or DISCONNECTING bit is set,
 * either the stop_transport() function or the submitting function
 * is guaranteed to call usb_unlink_urb() क्रम an active URB,
 * and (2) test_and_clear_bit() prevents usb_unlink_urb() from being
 * called more than once or from being called during usb_submit_urb().
 */

/*
 * This is the completion handler which will wake us up when an URB
 * completes.
 */
अटल व्योम usb_stor_blocking_completion(काष्ठा urb *urb)
अणु
	काष्ठा completion *urb_करोne_ptr = urb->context;

	complete(urb_करोne_ptr);
पूर्ण

/*
 * This is the common part of the URB message submission code
 *
 * All URBs from the usb-storage driver involved in handling a queued scsi
 * command _must_ pass through this function (or something like it) क्रम the
 * पात mechanisms to work properly.
 */
अटल पूर्णांक usb_stor_msg_common(काष्ठा us_data *us, पूर्णांक समयout)
अणु
	काष्ठा completion urb_करोne;
	दीर्घ समयleft;
	पूर्णांक status;

	/* करोn't submit URBs during पात processing */
	अगर (test_bit(US_FLIDX_ABORTING, &us->dflags))
		वापस -EIO;

	/* set up data काष्ठाures क्रम the wakeup प्रणाली */
	init_completion(&urb_करोne);

	/* fill the common fields in the URB */
	us->current_urb->context = &urb_करोne;
	us->current_urb->transfer_flags = 0;

	/*
	 * we assume that अगर transfer_buffer isn't us->iobuf then it
	 * hasn't been mapped for DMA.  Yes, this is clunky, but it's
	 * easier than always having the caller tell us whether the
	 * transfer buffer has alपढ़ोy been mapped.
	 */
	अगर (us->current_urb->transfer_buffer == us->iobuf)
		us->current_urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
	us->current_urb->transfer_dma = us->iobuf_dma;

	/* submit the URB */
	status = usb_submit_urb(us->current_urb, GFP_NOIO);
	अगर (status) अणु
		/* something went wrong */
		वापस status;
	पूर्ण

	/*
	 * since the URB has been submitted successfully, it's now okay
	 * to cancel it
	 */
	set_bit(US_FLIDX_URB_ACTIVE, &us->dflags);

	/* did an पात occur during the submission? */
	अगर (test_bit(US_FLIDX_ABORTING, &us->dflags)) अणु

		/* cancel the URB, अगर it hasn't been cancelled alपढ़ोy */
		अगर (test_and_clear_bit(US_FLIDX_URB_ACTIVE, &us->dflags)) अणु
			usb_stor_dbg(us, "-- cancelling URB\n");
			usb_unlink_urb(us->current_urb);
		पूर्ण
	पूर्ण
 
	/* रुको क्रम the completion of the URB */
	समयleft = रुको_क्रम_completion_पूर्णांकerruptible_समयout(
			&urb_करोne, समयout ? : MAX_SCHEDULE_TIMEOUT);
 
	clear_bit(US_FLIDX_URB_ACTIVE, &us->dflags);

	अगर (समयleft <= 0) अणु
		usb_stor_dbg(us, "%s -- cancelling URB\n",
			     समयleft == 0 ? "Timeout" : "Signal");
		usb_समाप्त_urb(us->current_urb);
	पूर्ण

	/* वापस the URB status */
	वापस us->current_urb->status;
पूर्ण

/*
 * Transfer one control message, with समयouts, and allowing early
 * termination.  Return codes are usual -Exxx, *not* USB_STOR_XFER_xxx.
 */
पूर्णांक usb_stor_control_msg(काष्ठा us_data *us, अचिन्हित पूर्णांक pipe,
		 u8 request, u8 requesttype, u16 value, u16 index, 
		 व्योम *data, u16 size, पूर्णांक समयout)
अणु
	पूर्णांक status;

	usb_stor_dbg(us, "rq=%02x rqtype=%02x value=%04x index=%02x len=%u\n",
		     request, requesttype, value, index, size);

	/* fill in the devrequest काष्ठाure */
	us->cr->bRequestType = requesttype;
	us->cr->bRequest = request;
	us->cr->wValue = cpu_to_le16(value);
	us->cr->wIndex = cpu_to_le16(index);
	us->cr->wLength = cpu_to_le16(size);

	/* fill and submit the URB */
	usb_fill_control_urb(us->current_urb, us->pusb_dev, pipe, 
			 (अचिन्हित अक्षर*) us->cr, data, size, 
			 usb_stor_blocking_completion, शून्य);
	status = usb_stor_msg_common(us, समयout);

	/* वापस the actual length of the data transferred अगर no error */
	अगर (status == 0)
		status = us->current_urb->actual_length;
	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(usb_stor_control_msg);

/*
 * This is a version of usb_clear_halt() that allows early termination and
 * करोesn't पढ़ो the status from the device -- this is because some devices
 * crash their पूर्णांकernal firmware when the status is requested after a halt.
 *
 * A definitive list of these 'bad' devices is too dअगरficult to मुख्यtain or
 * make complete enough to be useful.  This problem was first observed on the
 * Hagiwara FlashGate DUAL unit.  However, bus traces reveal that neither
 * MacOS nor Winकरोws checks the status after clearing a halt.
 *
 * Since many venकरोrs in this space limit their testing to पूर्णांकeroperability
 * with these two OSes, specअगरication violations like this one are common.
 */
पूर्णांक usb_stor_clear_halt(काष्ठा us_data *us, अचिन्हित पूर्णांक pipe)
अणु
	पूर्णांक result;
	पूर्णांक endp = usb_pipeendpoपूर्णांक(pipe);

	अगर (usb_pipein (pipe))
		endp |= USB_सूची_IN;

	result = usb_stor_control_msg(us, us->send_ctrl_pipe,
		USB_REQ_CLEAR_FEATURE, USB_RECIP_ENDPOINT,
		USB_ENDPOINT_HALT, endp,
		शून्य, 0, 3*HZ);

	अगर (result >= 0)
		usb_reset_endpoपूर्णांक(us->pusb_dev, endp);

	usb_stor_dbg(us, "result = %d\n", result);
	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(usb_stor_clear_halt);


/*
 * Interpret the results of a URB transfer
 *
 * This function prपूर्णांकs appropriate debugging messages, clears halts on
 * non-control endpoपूर्णांकs, and translates the status to the corresponding
 * USB_STOR_XFER_xxx वापस code.
 */
अटल पूर्णांक पूर्णांकerpret_urb_result(काष्ठा us_data *us, अचिन्हित पूर्णांक pipe,
		अचिन्हित पूर्णांक length, पूर्णांक result, अचिन्हित पूर्णांक partial)
अणु
	usb_stor_dbg(us, "Status code %d; transferred %u/%u\n",
		     result, partial, length);
	चयन (result) अणु

	/* no error code; did we send all the data? */
	हाल 0:
		अगर (partial != length) अणु
			usb_stor_dbg(us, "-- short transfer\n");
			वापस USB_STOR_XFER_SHORT;
		पूर्ण

		usb_stor_dbg(us, "-- transfer complete\n");
		वापस USB_STOR_XFER_GOOD;

	/* stalled */
	हाल -EPIPE:
		/*
		 * क्रम control endpoपूर्णांकs, (used by CB[I]) a stall indicates
		 * a failed command
		 */
		अगर (usb_pipecontrol(pipe)) अणु
			usb_stor_dbg(us, "-- stall on control pipe\n");
			वापस USB_STOR_XFER_STALLED;
		पूर्ण

		/* क्रम other sorts of endpoपूर्णांक, clear the stall */
		usb_stor_dbg(us, "clearing endpoint halt for pipe 0x%x\n",
			     pipe);
		अगर (usb_stor_clear_halt(us, pipe) < 0)
			वापस USB_STOR_XFER_ERROR;
		वापस USB_STOR_XFER_STALLED;

	/* babble - the device tried to send more than we wanted to पढ़ो */
	हाल -EOVERFLOW:
		usb_stor_dbg(us, "-- babble\n");
		वापस USB_STOR_XFER_LONG;

	/* the transfer was cancelled by पात, disconnect, or समयout */
	हाल -ECONNRESET:
		usb_stor_dbg(us, "-- transfer cancelled\n");
		वापस USB_STOR_XFER_ERROR;

	/* लघु scatter-gather पढ़ो transfer */
	हाल -EREMOTEIO:
		usb_stor_dbg(us, "-- short read transfer\n");
		वापस USB_STOR_XFER_SHORT;

	/* पात or disconnect in progress */
	हाल -EIO:
		usb_stor_dbg(us, "-- abort or disconnect in progress\n");
		वापस USB_STOR_XFER_ERROR;

	/* the catch-all error हाल */
	शेष:
		usb_stor_dbg(us, "-- unknown error\n");
		वापस USB_STOR_XFER_ERROR;
	पूर्ण
पूर्ण

/*
 * Transfer one control message, without समयouts, but allowing early
 * termination.  Return codes are USB_STOR_XFER_xxx.
 */
पूर्णांक usb_stor_ctrl_transfer(काष्ठा us_data *us, अचिन्हित पूर्णांक pipe,
		u8 request, u8 requesttype, u16 value, u16 index,
		व्योम *data, u16 size)
अणु
	पूर्णांक result;

	usb_stor_dbg(us, "rq=%02x rqtype=%02x value=%04x index=%02x len=%u\n",
		     request, requesttype, value, index, size);

	/* fill in the devrequest काष्ठाure */
	us->cr->bRequestType = requesttype;
	us->cr->bRequest = request;
	us->cr->wValue = cpu_to_le16(value);
	us->cr->wIndex = cpu_to_le16(index);
	us->cr->wLength = cpu_to_le16(size);

	/* fill and submit the URB */
	usb_fill_control_urb(us->current_urb, us->pusb_dev, pipe, 
			 (अचिन्हित अक्षर*) us->cr, data, size, 
			 usb_stor_blocking_completion, शून्य);
	result = usb_stor_msg_common(us, 0);

	वापस पूर्णांकerpret_urb_result(us, pipe, size, result,
			us->current_urb->actual_length);
पूर्ण
EXPORT_SYMBOL_GPL(usb_stor_ctrl_transfer);

/*
 * Receive one पूर्णांकerrupt buffer, without समयouts, but allowing early
 * termination.  Return codes are USB_STOR_XFER_xxx.
 *
 * This routine always uses us->recv_पूर्णांकr_pipe as the pipe and
 * us->ep_bInterval as the पूर्णांकerrupt पूर्णांकerval.
 */
अटल पूर्णांक usb_stor_पूर्णांकr_transfer(काष्ठा us_data *us, व्योम *buf,
				  अचिन्हित पूर्णांक length)
अणु
	पूर्णांक result;
	अचिन्हित पूर्णांक pipe = us->recv_पूर्णांकr_pipe;
	अचिन्हित पूर्णांक maxp;

	usb_stor_dbg(us, "xfer %u bytes\n", length);

	/* calculate the max packet size */
	maxp = usb_maxpacket(us->pusb_dev, pipe, usb_pipeout(pipe));
	अगर (maxp > length)
		maxp = length;

	/* fill and submit the URB */
	usb_fill_पूर्णांक_urb(us->current_urb, us->pusb_dev, pipe, buf,
			maxp, usb_stor_blocking_completion, शून्य,
			us->ep_bInterval);
	result = usb_stor_msg_common(us, 0);

	वापस पूर्णांकerpret_urb_result(us, pipe, length, result,
			us->current_urb->actual_length);
पूर्ण

/*
 * Transfer one buffer via bulk pipe, without समयouts, but allowing early
 * termination.  Return codes are USB_STOR_XFER_xxx.  If the bulk pipe
 * stalls during the transfer, the halt is स्वतःmatically cleared.
 */
पूर्णांक usb_stor_bulk_transfer_buf(काष्ठा us_data *us, अचिन्हित पूर्णांक pipe,
	व्योम *buf, अचिन्हित पूर्णांक length, अचिन्हित पूर्णांक *act_len)
अणु
	पूर्णांक result;

	usb_stor_dbg(us, "xfer %u bytes\n", length);

	/* fill and submit the URB */
	usb_fill_bulk_urb(us->current_urb, us->pusb_dev, pipe, buf, length,
		      usb_stor_blocking_completion, शून्य);
	result = usb_stor_msg_common(us, 0);

	/* store the actual length of the data transferred */
	अगर (act_len)
		*act_len = us->current_urb->actual_length;
	वापस पूर्णांकerpret_urb_result(us, pipe, length, result, 
			us->current_urb->actual_length);
पूर्ण
EXPORT_SYMBOL_GPL(usb_stor_bulk_transfer_buf);

/*
 * Transfer a scatter-gather list via bulk transfer
 *
 * This function करोes basically the same thing as usb_stor_bulk_transfer_buf()
 * above, but it uses the usbcore scatter-gather library.
 */
अटल पूर्णांक usb_stor_bulk_transfer_sglist(काष्ठा us_data *us, अचिन्हित पूर्णांक pipe,
		काष्ठा scatterlist *sg, पूर्णांक num_sg, अचिन्हित पूर्णांक length,
		अचिन्हित पूर्णांक *act_len)
अणु
	पूर्णांक result;

	/* करोn't submit s-g requests during पात processing */
	अगर (test_bit(US_FLIDX_ABORTING, &us->dflags))
		जाओ usb_stor_xfer_error;

	/* initialize the scatter-gather request block */
	usb_stor_dbg(us, "xfer %u bytes, %d entries\n", length, num_sg);
	result = usb_sg_init(&us->current_sg, us->pusb_dev, pipe, 0,
			sg, num_sg, length, GFP_NOIO);
	अगर (result) अणु
		usb_stor_dbg(us, "usb_sg_init returned %d\n", result);
		जाओ usb_stor_xfer_error;
	पूर्ण

	/*
	 * since the block has been initialized successfully, it's now
	 * okay to cancel it
	 */
	set_bit(US_FLIDX_SG_ACTIVE, &us->dflags);

	/* did an पात occur during the submission? */
	अगर (test_bit(US_FLIDX_ABORTING, &us->dflags)) अणु

		/* cancel the request, अगर it hasn't been cancelled alपढ़ोy */
		अगर (test_and_clear_bit(US_FLIDX_SG_ACTIVE, &us->dflags)) अणु
			usb_stor_dbg(us, "-- cancelling sg request\n");
			usb_sg_cancel(&us->current_sg);
		पूर्ण
	पूर्ण

	/* रुको क्रम the completion of the transfer */
	usb_sg_रुको(&us->current_sg);
	clear_bit(US_FLIDX_SG_ACTIVE, &us->dflags);

	result = us->current_sg.status;
	अगर (act_len)
		*act_len = us->current_sg.bytes;
	वापस पूर्णांकerpret_urb_result(us, pipe, length, result,
			us->current_sg.bytes);

usb_stor_xfer_error:
	अगर (act_len)
		*act_len = 0;
	वापस USB_STOR_XFER_ERROR;
पूर्ण

/*
 * Common used function. Transfer a complete command
 * via usb_stor_bulk_transfer_sglist() above. Set cmnd resid
 */
पूर्णांक usb_stor_bulk_srb(काष्ठा us_data* us, अचिन्हित पूर्णांक pipe,
		      काष्ठा scsi_cmnd* srb)
अणु
	अचिन्हित पूर्णांक partial;
	पूर्णांक result = usb_stor_bulk_transfer_sglist(us, pipe, scsi_sglist(srb),
				      scsi_sg_count(srb), scsi_bufflen(srb),
				      &partial);

	scsi_set_resid(srb, scsi_bufflen(srb) - partial);
	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(usb_stor_bulk_srb);

/*
 * Transfer an entire SCSI command's worth of data payload over the bulk
 * pipe.
 *
 * Note that this uses usb_stor_bulk_transfer_buf() and
 * usb_stor_bulk_transfer_sglist() to achieve its goals --
 * this function simply determines whether we're going to use
 * scatter-gather or not, and acts appropriately.
 */
पूर्णांक usb_stor_bulk_transfer_sg(काष्ठा us_data* us, अचिन्हित पूर्णांक pipe,
		व्योम *buf, अचिन्हित पूर्णांक length_left, पूर्णांक use_sg, पूर्णांक *residual)
अणु
	पूर्णांक result;
	अचिन्हित पूर्णांक partial;

	/* are we scatter-gathering? */
	अगर (use_sg) अणु
		/* use the usb core scatter-gather primitives */
		result = usb_stor_bulk_transfer_sglist(us, pipe,
				(काष्ठा scatterlist *) buf, use_sg,
				length_left, &partial);
		length_left -= partial;
	पूर्ण अन्यथा अणु
		/* no scatter-gather, just make the request */
		result = usb_stor_bulk_transfer_buf(us, pipe, buf, 
				length_left, &partial);
		length_left -= partial;
	पूर्ण

	/* store the residual and वापस the error code */
	अगर (residual)
		*residual = length_left;
	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(usb_stor_bulk_transfer_sg);

/***********************************************************************
 * Transport routines
 ***********************************************************************/

/*
 * There are so many devices that report the capacity incorrectly,
 * this routine was written to counteract some of the resulting
 * problems.
 */
अटल व्योम last_sector_hacks(काष्ठा us_data *us, काष्ठा scsi_cmnd *srb)
अणु
	काष्ठा gendisk *disk;
	काष्ठा scsi_disk *sdkp;
	u32 sector;

	/* To Report "Medium Error: Record Not Found */
	अटल अचिन्हित अक्षर record_not_found[18] = अणु
		[0]	= 0x70,			/* current error */
		[2]	= MEDIUM_ERROR,		/* = 0x03 */
		[7]	= 0x0a,			/* additional length */
		[12]	= 0x14			/* Record Not Found */
	पूर्ण;

	/*
	 * If last-sector problems can't occur, whether because the
	 * capacity was alपढ़ोy decremented or because the device is
	 * known to report the correct capacity, then we करोn't need
	 * to करो anything.
	 */
	अगर (!us->use_last_sector_hacks)
		वापस;

	/* Was this command a READ(10) or a WRITE(10)? */
	अगर (srb->cmnd[0] != READ_10 && srb->cmnd[0] != WRITE_10)
		जाओ करोne;

	/* Did this command access the last sector? */
	sector = (srb->cmnd[2] << 24) | (srb->cmnd[3] << 16) |
			(srb->cmnd[4] << 8) | (srb->cmnd[5]);
	disk = srb->request->rq_disk;
	अगर (!disk)
		जाओ करोne;
	sdkp = scsi_disk(disk);
	अगर (!sdkp)
		जाओ करोne;
	अगर (sector + 1 != sdkp->capacity)
		जाओ करोne;

	अगर (srb->result == SAM_STAT_GOOD && scsi_get_resid(srb) == 0) अणु

		/*
		 * The command succeeded.  We know this device करोesn't
		 * have the last-sector bug, so stop checking it.
		 */
		us->use_last_sector_hacks = 0;

	पूर्ण अन्यथा अणु
		/*
		 * The command failed.  Allow up to 3 retries in हाल this
		 * is some normal sort of failure.  After that, assume the
		 * capacity is wrong and we're trying to access the sector
		 * beyond the end.  Replace the result code and sense data
		 * with values that will cause the SCSI core to fail the
		 * command immediately, instead of going पूर्णांकo an infinite
		 * (or even just a very दीर्घ) retry loop.
		 */
		अगर (++us->last_sector_retries < 3)
			वापस;
		srb->result = SAM_STAT_CHECK_CONDITION;
		स_नकल(srb->sense_buffer, record_not_found,
				माप(record_not_found));
	पूर्ण

 करोne:
	/*
	 * Don't reset the retry counter क्रम TEST UNIT READY commands,
	 * because they get issued after device resets which might be
	 * caused by a failed last-sector access.
	 */
	अगर (srb->cmnd[0] != TEST_UNIT_READY)
		us->last_sector_retries = 0;
पूर्ण

/*
 * Invoke the transport and basic error-handling/recovery methods
 *
 * This is used by the protocol layers to actually send the message to
 * the device and receive the response.
 */
व्योम usb_stor_invoke_transport(काष्ठा scsi_cmnd *srb, काष्ठा us_data *us)
अणु
	पूर्णांक need_स्वतः_sense;
	पूर्णांक result;

	/* send the command to the transport layer */
	scsi_set_resid(srb, 0);
	result = us->transport(srb, us);

	/*
	 * अगर the command माला_लो पातed by the higher layers, we need to
	 * लघु-circuit all other processing
	 */
	अगर (test_bit(US_FLIDX_TIMED_OUT, &us->dflags)) अणु
		usb_stor_dbg(us, "-- command was aborted\n");
		srb->result = DID_ABORT << 16;
		जाओ Handle_Errors;
	पूर्ण

	/* अगर there is a transport error, reset and करोn't स्वतः-sense */
	अगर (result == USB_STOR_TRANSPORT_ERROR) अणु
		usb_stor_dbg(us, "-- transport indicates error, resetting\n");
		srb->result = DID_ERROR << 16;
		जाओ Handle_Errors;
	पूर्ण

	/* अगर the transport provided its own sense data, करोn't स्वतः-sense */
	अगर (result == USB_STOR_TRANSPORT_NO_SENSE) अणु
		srb->result = SAM_STAT_CHECK_CONDITION;
		last_sector_hacks(us, srb);
		वापस;
	पूर्ण

	srb->result = SAM_STAT_GOOD;

	/*
	 * Determine अगर we need to स्वतः-sense
	 *
	 * I normally करोn't use a flag like this, but it's almost impossible
	 * to understand what's going on here if I don't.
	 */
	need_स्वतः_sense = 0;

	/*
	 * If we're running the CB transport, which is incapable
	 * of determining status on its own, we will स्वतः-sense
	 * unless the operation involved a data-in transfer.  Devices
	 * can संकेत most data-in errors by stalling the bulk-in pipe.
	 */
	अगर ((us->protocol == USB_PR_CB || us->protocol == USB_PR_DPCM_USB) &&
			srb->sc_data_direction != DMA_FROM_DEVICE) अणु
		usb_stor_dbg(us, "-- CB transport device requiring auto-sense\n");
		need_स्वतः_sense = 1;
	पूर्ण

	/* Some devices (Kindle) require another command after SYNC CACHE */
	अगर ((us->fflags & US_FL_SENSE_AFTER_SYNC) &&
			srb->cmnd[0] == SYNCHRONIZE_CACHE) अणु
		usb_stor_dbg(us, "-- sense after SYNC CACHE\n");
		need_स्वतः_sense = 1;
	पूर्ण

	/*
	 * If we have a failure, we're going to करो a REQUEST_SENSE 
	 * स्वतःmatically.  Note that we dअगरferentiate between a command
	 * "failure" and an "error" in the transport mechanism.
	 */
	अगर (result == USB_STOR_TRANSPORT_FAILED) अणु
		usb_stor_dbg(us, "-- transport indicates command failure\n");
		need_स्वतः_sense = 1;
	पूर्ण

	/*
	 * Determine अगर this device is SAT by seeing अगर the
	 * command executed successfully.  Otherwise we'll have
	 * to रुको क्रम at least one CHECK_CONDITION to determine
	 * SANE_SENSE support
	 */
	अगर (unlikely((srb->cmnd[0] == ATA_16 || srb->cmnd[0] == ATA_12) &&
	    result == USB_STOR_TRANSPORT_GOOD &&
	    !(us->fflags & US_FL_SANE_SENSE) &&
	    !(us->fflags & US_FL_BAD_SENSE) &&
	    !(srb->cmnd[2] & 0x20))) अणु
		usb_stor_dbg(us, "-- SAT supported, increasing auto-sense\n");
		us->fflags |= US_FL_SANE_SENSE;
	पूर्ण

	/*
	 * A लघु transfer on a command where we करोn't expect it
	 * is unusual, but it करोesn't mean we need to स्वतः-sense.
	 */
	अगर ((scsi_get_resid(srb) > 0) &&
	    !((srb->cmnd[0] == REQUEST_SENSE) ||
	      (srb->cmnd[0] == INQUIRY) ||
	      (srb->cmnd[0] == MODE_SENSE) ||
	      (srb->cmnd[0] == LOG_SENSE) ||
	      (srb->cmnd[0] == MODE_SENSE_10))) अणु
		usb_stor_dbg(us, "-- unexpectedly short transfer\n");
	पूर्ण

	/* Now, अगर we need to करो the स्वतः-sense, let's करो it */
	अगर (need_स्वतः_sense) अणु
		पूर्णांक temp_result;
		काष्ठा scsi_eh_save ses;
		पूर्णांक sense_size = US_SENSE_SIZE;
		काष्ठा scsi_sense_hdr sshdr;
		स्थिर u8 *scdd;
		u8 fm_ili;

		/* device supports and needs bigger sense buffer */
		अगर (us->fflags & US_FL_SANE_SENSE)
			sense_size = ~0;
Retry_Sense:
		usb_stor_dbg(us, "Issuing auto-REQUEST_SENSE\n");

		scsi_eh_prep_cmnd(srb, &ses, शून्य, 0, sense_size);

		/* FIXME: we must करो the protocol translation here */
		अगर (us->subclass == USB_SC_RBC || us->subclass == USB_SC_SCSI ||
				us->subclass == USB_SC_CYP_ATACB)
			srb->cmd_len = 6;
		अन्यथा
			srb->cmd_len = 12;

		/* issue the स्वतः-sense command */
		scsi_set_resid(srb, 0);
		temp_result = us->transport(us->srb, us);

		/* let's clean up right away */
		scsi_eh_restore_cmnd(srb, &ses);

		अगर (test_bit(US_FLIDX_TIMED_OUT, &us->dflags)) अणु
			usb_stor_dbg(us, "-- auto-sense aborted\n");
			srb->result = DID_ABORT << 16;

			/* If SANE_SENSE caused this problem, disable it */
			अगर (sense_size != US_SENSE_SIZE) अणु
				us->fflags &= ~US_FL_SANE_SENSE;
				us->fflags |= US_FL_BAD_SENSE;
			पूर्ण
			जाओ Handle_Errors;
		पूर्ण

		/*
		 * Some devices claim to support larger sense but fail when
		 * trying to request it. When a transport failure happens
		 * using US_FS_SANE_SENSE, we always retry with a standard
		 * (small) sense request. This fixes some USB GSM modems
		 */
		अगर (temp_result == USB_STOR_TRANSPORT_FAILED &&
				sense_size != US_SENSE_SIZE) अणु
			usb_stor_dbg(us, "-- auto-sense failure, retry small sense\n");
			sense_size = US_SENSE_SIZE;
			us->fflags &= ~US_FL_SANE_SENSE;
			us->fflags |= US_FL_BAD_SENSE;
			जाओ Retry_Sense;
		पूर्ण

		/* Other failures */
		अगर (temp_result != USB_STOR_TRANSPORT_GOOD) अणु
			usb_stor_dbg(us, "-- auto-sense failure\n");

			/*
			 * we skip the reset अगर this happens to be a
			 * multi-target device, since failure of an
			 * स्वतः-sense is perfectly valid
			 */
			srb->result = DID_ERROR << 16;
			अगर (!(us->fflags & US_FL_SCM_MULT_TARG))
				जाओ Handle_Errors;
			वापस;
		पूर्ण

		/*
		 * If the sense data वापसed is larger than 18-bytes then we
		 * assume this device supports requesting more in the future.
		 * The response code must be 70h through 73h inclusive.
		 */
		अगर (srb->sense_buffer[7] > (US_SENSE_SIZE - 8) &&
		    !(us->fflags & US_FL_SANE_SENSE) &&
		    !(us->fflags & US_FL_BAD_SENSE) &&
		    (srb->sense_buffer[0] & 0x7C) == 0x70) अणु
			usb_stor_dbg(us, "-- SANE_SENSE support enabled\n");
			us->fflags |= US_FL_SANE_SENSE;

			/*
			 * Indicate to the user that we truncated their sense
			 * because we didn't know it supported larger sense.
			 */
			usb_stor_dbg(us, "-- Sense data truncated to %i from %i\n",
				     US_SENSE_SIZE,
				     srb->sense_buffer[7] + 8);
			srb->sense_buffer[7] = (US_SENSE_SIZE - 8);
		पूर्ण

		scsi_normalize_sense(srb->sense_buffer, SCSI_SENSE_BUFFERSIZE,
				     &sshdr);

		usb_stor_dbg(us, "-- Result from auto-sense is %d\n",
			     temp_result);
		usb_stor_dbg(us, "-- code: 0x%x, key: 0x%x, ASC: 0x%x, ASCQ: 0x%x\n",
			     sshdr.response_code, sshdr.sense_key,
			     sshdr.asc, sshdr.ascq);
#अगर_घोषित CONFIG_USB_STORAGE_DEBUG
		usb_stor_show_sense(us, sshdr.sense_key, sshdr.asc, sshdr.ascq);
#पूर्ण_अगर

		/* set the result so the higher layers expect this data */
		srb->result = SAM_STAT_CHECK_CONDITION;

		scdd = scsi_sense_desc_find(srb->sense_buffer,
					    SCSI_SENSE_BUFFERSIZE, 4);
		fm_ili = (scdd ? scdd[3] : srb->sense_buffer[2]) & 0xA0;

		/*
		 * We often get empty sense data.  This could indicate that
		 * everything worked or that there was an unspecअगरied
		 * problem.  We have to decide which.
		 */
		अगर (sshdr.sense_key == 0 && sshdr.asc == 0 && sshdr.ascq == 0 &&
		    fm_ili == 0) अणु
			/*
			 * If things are really okay, then let's show that.
			 * Zero out the sense buffer so the higher layers
			 * won't realize we did an unsolicited स्वतः-sense.
			 */
			अगर (result == USB_STOR_TRANSPORT_GOOD) अणु
				srb->result = SAM_STAT_GOOD;
				srb->sense_buffer[0] = 0x0;
			पूर्ण

			/*
			 * ATA-passthru commands use sense data to report
			 * the command completion status, and often devices
			 * वापस Check Condition status when nothing is
			 * wrong.
			 */
			अन्यथा अगर (srb->cmnd[0] == ATA_16 ||
					srb->cmnd[0] == ATA_12) अणु
				/* leave the data alone */
			पूर्ण

			/*
			 * If there was a problem, report an unspecअगरied
			 * hardware error to prevent the higher layers from
			 * entering an infinite retry loop.
			 */
			अन्यथा अणु
				srb->result = DID_ERROR << 16;
				अगर ((sshdr.response_code & 0x72) == 0x72)
					srb->sense_buffer[1] = HARDWARE_ERROR;
				अन्यथा
					srb->sense_buffer[2] = HARDWARE_ERROR;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Some devices करोn't work or वापस incorrect data the first
	 * समय they get a READ(10) command, or क्रम the first READ(10)
	 * after a media change.  If the INITIAL_READ10 flag is set,
	 * keep track of whether READ(10) commands succeed.  If the
	 * previous one succeeded and this one failed, set the REDO_READ10
	 * flag to क्रमce a retry.
	 */
	अगर (unlikely((us->fflags & US_FL_INITIAL_READ10) &&
			srb->cmnd[0] == READ_10)) अणु
		अगर (srb->result == SAM_STAT_GOOD) अणु
			set_bit(US_FLIDX_READ10_WORKED, &us->dflags);
		पूर्ण अन्यथा अगर (test_bit(US_FLIDX_READ10_WORKED, &us->dflags)) अणु
			clear_bit(US_FLIDX_READ10_WORKED, &us->dflags);
			set_bit(US_FLIDX_REDO_READ10, &us->dflags);
		पूर्ण

		/*
		 * Next, अगर the REDO_READ10 flag is set, वापस a result
		 * code that will cause the SCSI core to retry the READ(10)
		 * command immediately.
		 */
		अगर (test_bit(US_FLIDX_REDO_READ10, &us->dflags)) अणु
			clear_bit(US_FLIDX_REDO_READ10, &us->dflags);
			srb->result = DID_IMM_RETRY << 16;
			srb->sense_buffer[0] = 0;
		पूर्ण
	पूर्ण

	/* Did we transfer less than the minimum amount required? */
	अगर ((srb->result == SAM_STAT_GOOD || srb->sense_buffer[2] == 0) &&
			scsi_bufflen(srb) - scsi_get_resid(srb) < srb->underflow)
		srb->result = DID_ERROR << 16;

	last_sector_hacks(us, srb);
	वापस;

	/*
	 * Error and पात processing: try to resynchronize with the device
	 * by issuing a port reset.  If that fails, try a class-specअगरic
	 * device reset.
	 */
  Handle_Errors:

	/*
	 * Set the RESETTING bit, and clear the ABORTING bit so that
	 * the reset may proceed.
	 */
	scsi_lock(us_to_host(us));
	set_bit(US_FLIDX_RESETTING, &us->dflags);
	clear_bit(US_FLIDX_ABORTING, &us->dflags);
	scsi_unlock(us_to_host(us));

	/*
	 * We must release the device lock because the pre_reset routine
	 * will want to acquire it.
	 */
	mutex_unlock(&us->dev_mutex);
	result = usb_stor_port_reset(us);
	mutex_lock(&us->dev_mutex);

	अगर (result < 0) अणु
		scsi_lock(us_to_host(us));
		usb_stor_report_device_reset(us);
		scsi_unlock(us_to_host(us));
		us->transport_reset(us);
	पूर्ण
	clear_bit(US_FLIDX_RESETTING, &us->dflags);
	last_sector_hacks(us, srb);
पूर्ण

/* Stop the current URB transfer */
व्योम usb_stor_stop_transport(काष्ठा us_data *us)
अणु
	/*
	 * If the state machine is blocked रुकोing क्रम an URB,
	 * let's wake it up.  The test_and_clear_bit() call
	 * guarantees that अगर a URB has just been submitted,
	 * it won't be cancelled more than once.
	 */
	अगर (test_and_clear_bit(US_FLIDX_URB_ACTIVE, &us->dflags)) अणु
		usb_stor_dbg(us, "-- cancelling URB\n");
		usb_unlink_urb(us->current_urb);
	पूर्ण

	/* If we are रुकोing क्रम a scatter-gather operation, cancel it. */
	अगर (test_and_clear_bit(US_FLIDX_SG_ACTIVE, &us->dflags)) अणु
		usb_stor_dbg(us, "-- cancelling sg request\n");
		usb_sg_cancel(&us->current_sg);
	पूर्ण
पूर्ण

/*
 * Control/Bulk and Control/Bulk/Interrupt transport
 */

पूर्णांक usb_stor_CB_transport(काष्ठा scsi_cmnd *srb, काष्ठा us_data *us)
अणु
	अचिन्हित पूर्णांक transfer_length = scsi_bufflen(srb);
	अचिन्हित पूर्णांक pipe = 0;
	पूर्णांक result;

	/* COMMAND STAGE */
	/* let's send the command via the control pipe */
	/*
	 * Command is someसमय (f.e. after scsi_eh_prep_cmnd) on the stack.
	 * Stack may be vदो_स्मृतिated.  So no DMA क्रम us.  Make a copy.
	 */
	स_नकल(us->iobuf, srb->cmnd, srb->cmd_len);
	result = usb_stor_ctrl_transfer(us, us->send_ctrl_pipe,
				      US_CBI_ADSC, 
				      USB_TYPE_CLASS | USB_RECIP_INTERFACE, 0, 
				      us->अगरnum, us->iobuf, srb->cmd_len);

	/* check the वापस code क्रम the command */
	usb_stor_dbg(us, "Call to usb_stor_ctrl_transfer() returned %d\n",
		     result);

	/* अगर we stalled the command, it means command failed */
	अगर (result == USB_STOR_XFER_STALLED) अणु
		वापस USB_STOR_TRANSPORT_FAILED;
	पूर्ण

	/* Uh oh... serious problem here */
	अगर (result != USB_STOR_XFER_GOOD) अणु
		वापस USB_STOR_TRANSPORT_ERROR;
	पूर्ण

	/* DATA STAGE */
	/* transfer the data payload क्रम this command, अगर one exists*/
	अगर (transfer_length) अणु
		pipe = srb->sc_data_direction == DMA_FROM_DEVICE ? 
				us->recv_bulk_pipe : us->send_bulk_pipe;
		result = usb_stor_bulk_srb(us, pipe, srb);
		usb_stor_dbg(us, "CBI data stage result is 0x%x\n", result);

		/* अगर we stalled the data transfer it means command failed */
		अगर (result == USB_STOR_XFER_STALLED)
			वापस USB_STOR_TRANSPORT_FAILED;
		अगर (result > USB_STOR_XFER_STALLED)
			वापस USB_STOR_TRANSPORT_ERROR;
	पूर्ण

	/* STATUS STAGE */

	/*
	 * NOTE: CB करोes not have a status stage.  Silly, I know.  So
	 * we have to catch this at a higher level.
	 */
	अगर (us->protocol != USB_PR_CBI)
		वापस USB_STOR_TRANSPORT_GOOD;

	result = usb_stor_पूर्णांकr_transfer(us, us->iobuf, 2);
	usb_stor_dbg(us, "Got interrupt data (0x%x, 0x%x)\n",
		     us->iobuf[0], us->iobuf[1]);
	अगर (result != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	/*
	 * UFI gives us ASC and ASCQ, like a request sense
	 *
	 * REQUEST_SENSE and INQUIRY करोn't affect the sense data on UFI
	 * devices, so we ignore the inक्रमmation क्रम those commands.  Note
	 * that this means we could be ignoring a real error on these
	 * commands, but that can't be helped.
	 */
	अगर (us->subclass == USB_SC_UFI) अणु
		अगर (srb->cmnd[0] == REQUEST_SENSE ||
		    srb->cmnd[0] == INQUIRY)
			वापस USB_STOR_TRANSPORT_GOOD;
		अगर (us->iobuf[0])
			जाओ Failed;
		वापस USB_STOR_TRANSPORT_GOOD;
	पूर्ण

	/*
	 * If not UFI, we पूर्णांकerpret the data as a result code 
	 * The first byte should always be a 0x0.
	 *
	 * Some bogus devices करोn't follow that rule.  They stuff the ASC
	 * पूर्णांकo the first byte -- so अगर it's non-zero, call it a failure.
	 */
	अगर (us->iobuf[0]) अणु
		usb_stor_dbg(us, "CBI IRQ data showed reserved bType 0x%x\n",
			     us->iobuf[0]);
		जाओ Failed;

	पूर्ण

	/* The second byte & 0x0F should be 0x0 क्रम good, otherwise error */
	चयन (us->iobuf[1] & 0x0F) अणु
		हाल 0x00: 
			वापस USB_STOR_TRANSPORT_GOOD;
		हाल 0x01: 
			जाओ Failed;
	पूर्ण
	वापस USB_STOR_TRANSPORT_ERROR;

	/*
	 * the CBI spec requires that the bulk pipe must be cleared
	 * following any data-in/out command failure (section 2.4.3.1.3)
	 */
  Failed:
	अगर (pipe)
		usb_stor_clear_halt(us, pipe);
	वापस USB_STOR_TRANSPORT_FAILED;
पूर्ण
EXPORT_SYMBOL_GPL(usb_stor_CB_transport);

/*
 * Bulk only transport
 */

/* Determine what the maximum LUN supported is */
पूर्णांक usb_stor_Bulk_max_lun(काष्ठा us_data *us)
अणु
	पूर्णांक result;

	/* issue the command */
	us->iobuf[0] = 0;
	result = usb_stor_control_msg(us, us->recv_ctrl_pipe,
				 US_BULK_GET_MAX_LUN, 
				 USB_सूची_IN | USB_TYPE_CLASS | 
				 USB_RECIP_INTERFACE,
				 0, us->अगरnum, us->iobuf, 1, 10*HZ);

	usb_stor_dbg(us, "GetMaxLUN command result is %d, data is %d\n",
		     result, us->iobuf[0]);

	/*
	 * If we have a successful request, वापस the result अगर valid. The
	 * CBW LUN field is 4 bits wide, so the value reported by the device
	 * should fit पूर्णांकo that.
	 */
	अगर (result > 0) अणु
		अगर (us->iobuf[0] < 16) अणु
			वापस us->iobuf[0];
		पूर्ण अन्यथा अणु
			dev_info(&us->pusb_पूर्णांकf->dev,
				 "Max LUN %d is not valid, using 0 instead",
				 us->iobuf[0]);
		पूर्ण
	पूर्ण

	/*
	 * Some devices करोn't like GetMaxLUN.  They may STALL the control
	 * pipe, they may वापस a zero-length result, they may करो nothing at
	 * all and समयout, or they may fail in even more bizarrely creative
	 * ways.  In these हालs the best approach is to use the शेष
	 * value: only one LUN.
	 */
	वापस 0;
पूर्ण

पूर्णांक usb_stor_Bulk_transport(काष्ठा scsi_cmnd *srb, काष्ठा us_data *us)
अणु
	काष्ठा bulk_cb_wrap *bcb = (काष्ठा bulk_cb_wrap *) us->iobuf;
	काष्ठा bulk_cs_wrap *bcs = (काष्ठा bulk_cs_wrap *) us->iobuf;
	अचिन्हित पूर्णांक transfer_length = scsi_bufflen(srb);
	अचिन्हित पूर्णांक residue;
	पूर्णांक result;
	पूर्णांक fake_sense = 0;
	अचिन्हित पूर्णांक cswlen;
	अचिन्हित पूर्णांक cbwlen = US_BULK_CB_WRAP_LEN;

	/* Take care of BULK32 devices; set extra byte to 0 */
	अगर (unlikely(us->fflags & US_FL_BULK32)) अणु
		cbwlen = 32;
		us->iobuf[31] = 0;
	पूर्ण

	/* set up the command wrapper */
	bcb->Signature = cpu_to_le32(US_BULK_CB_SIGN);
	bcb->DataTransferLength = cpu_to_le32(transfer_length);
	bcb->Flags = srb->sc_data_direction == DMA_FROM_DEVICE ?
		US_BULK_FLAG_IN : 0;
	bcb->Tag = ++us->tag;
	bcb->Lun = srb->device->lun;
	अगर (us->fflags & US_FL_SCM_MULT_TARG)
		bcb->Lun |= srb->device->id << 4;
	bcb->Length = srb->cmd_len;

	/* copy the command payload */
	स_रखो(bcb->CDB, 0, माप(bcb->CDB));
	स_नकल(bcb->CDB, srb->cmnd, bcb->Length);

	/* send it to out endpoपूर्णांक */
	usb_stor_dbg(us, "Bulk Command S 0x%x T 0x%x L %d F %d Trg %d LUN %d CL %d\n",
		     le32_to_cpu(bcb->Signature), bcb->Tag,
		     le32_to_cpu(bcb->DataTransferLength), bcb->Flags,
		     (bcb->Lun >> 4), (bcb->Lun & 0x0F),
		     bcb->Length);
	result = usb_stor_bulk_transfer_buf(us, us->send_bulk_pipe,
				bcb, cbwlen, शून्य);
	usb_stor_dbg(us, "Bulk command transfer result=%d\n", result);
	अगर (result != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

	/* DATA STAGE */
	/* send/receive data payload, अगर there is any */

	/*
	 * Some USB-IDE converter chips need a 100us delay between the
	 * command phase and the data phase.  Some devices need a little
	 * more than that, probably because of घड़ी rate inaccuracies.
	 */
	अगर (unlikely(us->fflags & US_FL_GO_SLOW))
		usleep_range(125, 150);

	अगर (transfer_length) अणु
		अचिन्हित पूर्णांक pipe = srb->sc_data_direction == DMA_FROM_DEVICE ? 
				us->recv_bulk_pipe : us->send_bulk_pipe;
		result = usb_stor_bulk_srb(us, pipe, srb);
		usb_stor_dbg(us, "Bulk data transfer result 0x%x\n", result);
		अगर (result == USB_STOR_XFER_ERROR)
			वापस USB_STOR_TRANSPORT_ERROR;

		/*
		 * If the device tried to send back more data than the
		 * amount requested, the spec requires us to transfer
		 * the CSW anyway.  Since there's no poपूर्णांक retrying the
		 * the command, we'll वापस fake sense data indicating
		 * Illegal Request, Invalid Field in CDB.
		 */
		अगर (result == USB_STOR_XFER_LONG)
			fake_sense = 1;

		/*
		 * Someबार a device will mistakenly skip the data phase
		 * and go directly to the status phase without sending a
		 * zero-length packet.  If we get a 13-byte response here,
		 * check whether it really is a CSW.
		 */
		अगर (result == USB_STOR_XFER_SHORT &&
				srb->sc_data_direction == DMA_FROM_DEVICE &&
				transfer_length - scsi_get_resid(srb) ==
					US_BULK_CS_WRAP_LEN) अणु
			काष्ठा scatterlist *sg = शून्य;
			अचिन्हित पूर्णांक offset = 0;

			अगर (usb_stor_access_xfer_buf((अचिन्हित अक्षर *) bcs,
					US_BULK_CS_WRAP_LEN, srb, &sg,
					&offset, FROM_XFER_BUF) ==
						US_BULK_CS_WRAP_LEN &&
					bcs->Signature ==
						cpu_to_le32(US_BULK_CS_SIGN)) अणु
				usb_stor_dbg(us, "Device skipped data phase\n");
				scsi_set_resid(srb, transfer_length);
				जाओ skipped_data_phase;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * See flow अक्षरt on pg 15 of the Bulk Only Transport spec क्रम
	 * an explanation of how this code works.
	 */

	/* get CSW क्रम device status */
	usb_stor_dbg(us, "Attempting to get CSW...\n");
	result = usb_stor_bulk_transfer_buf(us, us->recv_bulk_pipe,
				bcs, US_BULK_CS_WRAP_LEN, &cswlen);

	/*
	 * Some broken devices add unnecessary zero-length packets to the
	 * end of their data transfers.  Such packets show up as 0-length
	 * CSWs.  If we encounter such a thing, try to पढ़ो the CSW again.
	 */
	अगर (result == USB_STOR_XFER_SHORT && cswlen == 0) अणु
		usb_stor_dbg(us, "Received 0-length CSW; retrying...\n");
		result = usb_stor_bulk_transfer_buf(us, us->recv_bulk_pipe,
				bcs, US_BULK_CS_WRAP_LEN, &cswlen);
	पूर्ण

	/* did the attempt to पढ़ो the CSW fail? */
	अगर (result == USB_STOR_XFER_STALLED) अणु

		/* get the status again */
		usb_stor_dbg(us, "Attempting to get CSW (2nd try)...\n");
		result = usb_stor_bulk_transfer_buf(us, us->recv_bulk_pipe,
				bcs, US_BULK_CS_WRAP_LEN, शून्य);
	पूर्ण

	/* अगर we still have a failure at this poपूर्णांक, we're in trouble */
	usb_stor_dbg(us, "Bulk status result = %d\n", result);
	अगर (result != USB_STOR_XFER_GOOD)
		वापस USB_STOR_TRANSPORT_ERROR;

 skipped_data_phase:
	/* check bulk status */
	residue = le32_to_cpu(bcs->Residue);
	usb_stor_dbg(us, "Bulk Status S 0x%x T 0x%x R %u Stat 0x%x\n",
		     le32_to_cpu(bcs->Signature), bcs->Tag,
		     residue, bcs->Status);
	अगर (!(bcs->Tag == us->tag || (us->fflags & US_FL_BULK_IGNORE_TAG)) ||
		bcs->Status > US_BULK_STAT_PHASE) अणु
		usb_stor_dbg(us, "Bulk logical error\n");
		वापस USB_STOR_TRANSPORT_ERROR;
	पूर्ण

	/*
	 * Some broken devices report odd signatures, so we करो not check them
	 * क्रम validity against the spec. We store the first one we see,
	 * and check subsequent transfers क्रम validity against this signature.
	 */
	अगर (!us->bcs_signature) अणु
		us->bcs_signature = bcs->Signature;
		अगर (us->bcs_signature != cpu_to_le32(US_BULK_CS_SIGN))
			usb_stor_dbg(us, "Learnt BCS signature 0x%08X\n",
				     le32_to_cpu(us->bcs_signature));
	पूर्ण अन्यथा अगर (bcs->Signature != us->bcs_signature) अणु
		usb_stor_dbg(us, "Signature mismatch: got %08X, expecting %08X\n",
			     le32_to_cpu(bcs->Signature),
			     le32_to_cpu(us->bcs_signature));
		वापस USB_STOR_TRANSPORT_ERROR;
	पूर्ण

	/*
	 * try to compute the actual residue, based on how much data
	 * was really transferred and what the device tells us
	 */
	अगर (residue && !(us->fflags & US_FL_IGNORE_RESIDUE)) अणु

		/*
		 * Heuristically detect devices that generate bogus residues
		 * by seeing what happens with INQUIRY and READ CAPACITY
		 * commands.
		 */
		अगर (bcs->Status == US_BULK_STAT_OK &&
				scsi_get_resid(srb) == 0 &&
					((srb->cmnd[0] == INQUIRY &&
						transfer_length == 36) ||
					(srb->cmnd[0] == READ_CAPACITY &&
						transfer_length == 8))) अणु
			us->fflags |= US_FL_IGNORE_RESIDUE;

		पूर्ण अन्यथा अणु
			residue = min(residue, transfer_length);
			scsi_set_resid(srb, max(scsi_get_resid(srb), residue));
		पूर्ण
	पूर्ण

	/* based on the status code, we report good or bad */
	चयन (bcs->Status) अणु
		हाल US_BULK_STAT_OK:
			/* device babbled -- वापस fake sense data */
			अगर (fake_sense) अणु
				स_नकल(srb->sense_buffer, 
				       usb_stor_sense_invalidCDB, 
				       माप(usb_stor_sense_invalidCDB));
				वापस USB_STOR_TRANSPORT_NO_SENSE;
			पूर्ण

			/* command good -- note that data could be लघु */
			वापस USB_STOR_TRANSPORT_GOOD;

		हाल US_BULK_STAT_FAIL:
			/* command failed */
			वापस USB_STOR_TRANSPORT_FAILED;

		हाल US_BULK_STAT_PHASE:
			/*
			 * phase error -- note that a transport reset will be
			 * invoked by the invoke_transport() function
			 */
			वापस USB_STOR_TRANSPORT_ERROR;
	पूर्ण

	/* we should never get here, but अगर we करो, we're in trouble */
	वापस USB_STOR_TRANSPORT_ERROR;
पूर्ण
EXPORT_SYMBOL_GPL(usb_stor_Bulk_transport);

/***********************************************************************
 * Reset routines
 ***********************************************************************/

/*
 * This is the common part of the device reset code.
 *
 * It's handy that every transport mechanism uses the control endpoपूर्णांक क्रम
 * resets.
 *
 * Basically, we send a reset with a 5-second समयout, so we करोn't get
 * jammed attempting to करो the reset.
 */
अटल पूर्णांक usb_stor_reset_common(काष्ठा us_data *us,
		u8 request, u8 requesttype,
		u16 value, u16 index, व्योम *data, u16 size)
अणु
	पूर्णांक result;
	पूर्णांक result2;

	अगर (test_bit(US_FLIDX_DISCONNECTING, &us->dflags)) अणु
		usb_stor_dbg(us, "No reset during disconnect\n");
		वापस -EIO;
	पूर्ण

	result = usb_stor_control_msg(us, us->send_ctrl_pipe,
			request, requesttype, value, index, data, size,
			5*HZ);
	अगर (result < 0) अणु
		usb_stor_dbg(us, "Soft reset failed: %d\n", result);
		वापस result;
	पूर्ण

	/*
	 * Give the device some समय to recover from the reset,
	 * but करोn't delay disconnect processing.
	 */
	रुको_event_पूर्णांकerruptible_समयout(us->delay_रुको,
			test_bit(US_FLIDX_DISCONNECTING, &us->dflags),
			HZ*6);
	अगर (test_bit(US_FLIDX_DISCONNECTING, &us->dflags)) अणु
		usb_stor_dbg(us, "Reset interrupted by disconnect\n");
		वापस -EIO;
	पूर्ण

	usb_stor_dbg(us, "Soft reset: clearing bulk-in endpoint halt\n");
	result = usb_stor_clear_halt(us, us->recv_bulk_pipe);

	usb_stor_dbg(us, "Soft reset: clearing bulk-out endpoint halt\n");
	result2 = usb_stor_clear_halt(us, us->send_bulk_pipe);

	/* वापस a result code based on the result of the clear-halts */
	अगर (result >= 0)
		result = result2;
	अगर (result < 0)
		usb_stor_dbg(us, "Soft reset failed\n");
	अन्यथा
		usb_stor_dbg(us, "Soft reset done\n");
	वापस result;
पूर्ण

/* This issues a CB[I] Reset to the device in question */
#घोषणा CB_RESET_CMD_SIZE	12

पूर्णांक usb_stor_CB_reset(काष्ठा us_data *us)
अणु
	स_रखो(us->iobuf, 0xFF, CB_RESET_CMD_SIZE);
	us->iobuf[0] = SEND_DIAGNOSTIC;
	us->iobuf[1] = 4;
	वापस usb_stor_reset_common(us, US_CBI_ADSC, 
				 USB_TYPE_CLASS | USB_RECIP_INTERFACE,
				 0, us->अगरnum, us->iobuf, CB_RESET_CMD_SIZE);
पूर्ण
EXPORT_SYMBOL_GPL(usb_stor_CB_reset);

/*
 * This issues a Bulk-only Reset to the device in question, including
 * clearing the subsequent endpoपूर्णांक halts that may occur.
 */
पूर्णांक usb_stor_Bulk_reset(काष्ठा us_data *us)
अणु
	वापस usb_stor_reset_common(us, US_BULK_RESET_REQUEST, 
				 USB_TYPE_CLASS | USB_RECIP_INTERFACE,
				 0, us->अगरnum, शून्य, 0);
पूर्ण
EXPORT_SYMBOL_GPL(usb_stor_Bulk_reset);

/*
 * Issue a USB port reset to the device.  The caller must not hold
 * us->dev_mutex.
 */
पूर्णांक usb_stor_port_reset(काष्ठा us_data *us)
अणु
	पूर्णांक result;

	/*क्रम these devices we must use the class specअगरic method */
	अगर (us->pusb_dev->quirks & USB_QUIRK_RESET)
		वापस -EPERM;

	result = usb_lock_device_क्रम_reset(us->pusb_dev, us->pusb_पूर्णांकf);
	अगर (result < 0)
		usb_stor_dbg(us, "unable to lock device for reset: %d\n",
			     result);
	अन्यथा अणु
		/* Were we disconnected जबतक रुकोing क्रम the lock? */
		अगर (test_bit(US_FLIDX_DISCONNECTING, &us->dflags)) अणु
			result = -EIO;
			usb_stor_dbg(us, "No reset during disconnect\n");
		पूर्ण अन्यथा अणु
			result = usb_reset_device(us->pusb_dev);
			usb_stor_dbg(us, "usb_reset_device returns %d\n",
				     result);
		पूर्ण
		usb_unlock_device(us->pusb_dev);
	पूर्ण
	वापस result;
पूर्ण
