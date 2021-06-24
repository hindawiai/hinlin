<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Driver क्रम Microtek Scanmaker X6 USB scanner, and possibly others.
 *
 * (C) Copyright 2000 John Fremlin <vii@penguinघातered.com>
 * (C) Copyright 2000 Oliver Neukum <Oliver.Neukum@lrz.uni-muenchen.de>
 *
 * Parts shamelessly stolen from usb-storage and copyright by their
 * authors. Thanks to Matt Dharm क्रम giving us permission!
 *
 * This driver implements a SCSI host controller driver and a USB
 * device driver. To aव्योम confusion, all the USB related stuff is
 * prefixed by mts_usb_ and all the SCSI stuff by mts_scsi_.
 *
 * Microtek (www.microtek.com) did not release the specअगरications क्रम
 * their USB protocol to us, so we had to reverse engineer them. We
 * करोn't know क्रम which models they are valid.
 *
 * The X6 USB has three bulk endpoपूर्णांकs, one output (0x1) करोwn which
 * commands and outgoing data are sent, and two input: 0x82 from which
 * normal data is पढ़ो from the scanner (in packets of maximum 32
 * bytes) and from which the status byte is पढ़ो, and 0x83 from which
 * the results of a scan (or preview) are पढ़ो in up to 64 * 1024 byte
 * chunks by the Winकरोws driver. We करोn't know how much it is possible
 * to पढ़ो at a समय from 0x83.
 *
 * It seems possible to पढ़ो (with URB transfers) everything from 0x82
 * in one go, without bothering to पढ़ो in 32 byte chunks.
 *
 * There seems to be an optimisation of a further READ implicit अगर
 * you simply पढ़ो from 0x83.
 *
 * Guessed protocol:
 *
 *	Send raw SCSI command to EP 0x1
 *
 *	If there is data to receive:
 *		If the command was READ datatype=image:
 *			Read a lot of data from EP 0x83
 *		Else:
 *			Read data from EP 0x82
 *	Else:
 *		If there is data to transmit:
 *			Write it to EP 0x1
 *
 *	Read status byte from EP 0x82
 *
 * References:
 *
 * The SCSI command set क्रम the scanner is available from
 *	ftp://ftp.microtek.com/microtek/devpack/
 *
 * Microtek NV sent us a more up to date version of the करोcument. If
 * you want it, just send mail.
 *
 * Status:
 *
 *	Untested with multiple scanners.
 *	Untested on SMP.
 *	Untested on a bigendian machine.
 *
 * History:
 *
 *	20000417 starting history
 *	20000417 fixed load oops
 *	20000417 fixed unload oops
 *	20000419 fixed READ IMAGE detection
 *	20000424 started conversion to use URBs
 *	20000502 handled लघु transfers as errors
 *	20000513 नाम and organisation of functions (john)
 *	20000513 added IDs क्रम all products supported by Winकरोws driver (john)
 *	20000514 Rewrote mts_scsi_queuecommand to use URBs (john)
 *	20000514 Version 0.0.8j
 *      20000514 Fix reporting of non-existent devices to SCSI layer (john)
 *	20000514 Added MTS_DEBUG_INT (john)
 *	20000514 Changed "usb-microtek" to "microtek" क्रम consistency (john)
 *	20000514 Stupid bug fixes (john)
 *	20000514 Version 0.0.9j
 *	20000515 Put transfer context and URB in mts_desc (john)
 *	20000515 Added prelim turn off debugging support (john)
 *	20000515 Version 0.0.10j
 *      20000515 Fixed up URB allocation (clear URB on alloc) (john)
 *      20000515 Version 0.0.11j
 *	20000516 Removed unnecessary spinlock in mts_transfer_context (john)
 *	20000516 Removed unnecessary up on instance lock in mts_हटाओ_nolock (john)
 *	20000516 Implemented (badly) scsi_पात (john)
 *	20000516 Version 0.0.12j
 *      20000517 Hopefully हटाओd mts_हटाओ_nolock quasideadlock (john)
 *      20000517 Added mts_debug_dump to prपूर्णांक ll USB info (john)
 *	20000518 Tweaks and करोcumentation updates (john)
 *	20000518 Version 0.0.13j
 *	20000518 Cleaned up पात handling (john)
 *	20000523 Removed scsi_command and various scsi_..._resets (john)
 *	20000523 Added unlink URB on scsi_पात, now OHCI supports it (john)
 *	20000523 Fixed last tiresome compile warning (john)
 *	20000523 Version 0.0.14j (though version 0.1 has come out?)
 *	20000602 Added primitive reset
 *	20000602 Version 0.2.0
 *	20000603 various cosmetic changes
 *	20000603 Version 0.2.1
 *	20000620 minor cosmetic changes
 *	20000620 Version 0.2.2
 *	20000822 Hopefully fixed deadlock in mts_हटाओ_nolock()
 *	20000822 Fixed minor race in mts_transfer_cleanup()
 *	20000822 Fixed deadlock on submission error in queuecommand
 *	20000822 Version 0.2.3
 *	20000913 Reduced module size अगर debugging is off
 *	20000913 Version 0.2.4
 *      20010210 New पात logic
 *      20010210 Version 0.3.0
 *	20010217 Merged scatter/gather
 *	20010218 Version 0.4.0
 *	20010218 Cosmetic fixes
 *	20010218 Version 0.4.1
 *      20010306 Abort जबतक using scatter/gather
 *      20010306 Version 0.4.2
 *      20010311 Remove all समयouts and tidy up generally (john)
 *	20010320 check वापस value of scsi_रेजिस्टर()
 *	20010320 Version 0.4.3
 *	20010408 Identअगरy version on module load.
 *	20011003 Fix multiple requests
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/poll.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/usb.h>
#समावेश <linux/proc_fs.h>

#समावेश <linux/atomic.h>
#समावेश <linux/blkdev.h>
#समावेश "../../scsi/scsi.h"
#समावेश <scsi/scsi_host.h>

#समावेश "microtek.h"

#घोषणा DRIVER_AUTHOR "John Fremlin <vii@penguinpowered.com>, Oliver Neukum <Oliver.Neukum@lrz.uni-muenchen.de>"
#घोषणा DRIVER_DESC "Microtek Scanmaker X6 USB scanner driver"

/* Should we करो debugging? */

//#घोषणा MTS_DO_DEBUG

/* USB layer driver पूर्णांकerface */

अटल पूर्णांक mts_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			 स्थिर काष्ठा usb_device_id *id);
अटल व्योम mts_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf);

अटल स्थिर काष्ठा usb_device_id mts_usb_ids[];

अटल काष्ठा usb_driver mts_usb_driver = अणु
	.name =		"microtekX6",
	.probe =	mts_usb_probe,
	.disconnect =	mts_usb_disconnect,
	.id_table =	mts_usb_ids,
पूर्ण;


/* Internal driver stuff */

#घोषणा MTS_VERSION	"0.4.3"
#घोषणा MTS_NAME	"microtek usb (rev " MTS_VERSION "): "

#घोषणा MTS_WARNING(x...) \
	prपूर्णांकk( KERN_WARNING MTS_NAME x )
#घोषणा MTS_ERROR(x...) \
	prपूर्णांकk( KERN_ERR MTS_NAME x )
#घोषणा MTS_INT_ERROR(x...) \
	MTS_ERROR(x)
#घोषणा MTS_MESSAGE(x...) \
	prपूर्णांकk( KERN_INFO MTS_NAME x )

#अगर defined MTS_DO_DEBUG

#घोषणा MTS_DEBUG(x...) \
	prपूर्णांकk( KERN_DEBUG MTS_NAME x )

#घोषणा MTS_DEBUG_GOT_HERE() \
	MTS_DEBUG("got to %s:%d (%s)\n", __खाता__, (पूर्णांक)__LINE__, __func__ )
#घोषणा MTS_DEBUG_INT() \
	करो अणु MTS_DEBUG_GOT_HERE(); \
	     MTS_DEBUG("transfer = 0x%x context = 0x%x\n",(पूर्णांक)transfer,(पूर्णांक)context ); \
	     MTS_DEBUG("status = 0x%x data-length = 0x%x sent = 0x%x\n",transfer->status,(पूर्णांक)context->data_length, (पूर्णांक)transfer->actual_length ); \
             mts_debug_dump(context->instance);\
	   पूर्ण जबतक(0)
#अन्यथा

#घोषणा MTS_NUL_STATEMENT करो अणु पूर्ण जबतक(0)

#घोषणा MTS_DEBUG(x...)	MTS_NUL_STATEMENT
#घोषणा MTS_DEBUG_GOT_HERE() MTS_NUL_STATEMENT
#घोषणा MTS_DEBUG_INT() MTS_NUL_STATEMENT

#पूर्ण_अगर



#घोषणा MTS_INT_INIT()\
	काष्ठा mts_transfer_context* context = (काष्ठा mts_transfer_context*)transfer->context; \
	MTS_DEBUG_INT();\

#अगर_घोषित MTS_DO_DEBUG

अटल अंतरभूत व्योम mts_debug_dump(काष्ठा mts_desc* desc) अणु
	MTS_DEBUG("desc at 0x%x: toggle = %02x%02x\n",
		  (पूर्णांक)desc,
		  (पूर्णांक)desc->usb_dev->toggle[1],(पूर्णांक)desc->usb_dev->toggle[0]
		);
	MTS_DEBUG("ep_out=%x ep_response=%x ep_image=%x\n",
		  usb_sndbulkpipe(desc->usb_dev,desc->ep_out),
		  usb_rcvbulkpipe(desc->usb_dev,desc->ep_response),
		  usb_rcvbulkpipe(desc->usb_dev,desc->ep_image)
		);
पूर्ण


अटल अंतरभूत व्योम mts_show_command(काष्ठा scsi_cmnd *srb)
अणु
	अक्षर *what = शून्य;

	चयन (srb->cmnd[0]) अणु
	हाल TEST_UNIT_READY: what = "TEST_UNIT_READY"; अवरोध;
	हाल REZERO_UNIT: what = "REZERO_UNIT"; अवरोध;
	हाल REQUEST_SENSE: what = "REQUEST_SENSE"; अवरोध;
	हाल FORMAT_UNIT: what = "FORMAT_UNIT"; अवरोध;
	हाल READ_BLOCK_LIMITS: what = "READ_BLOCK_LIMITS"; अवरोध;
	हाल REASSIGN_BLOCKS: what = "REASSIGN_BLOCKS"; अवरोध;
	हाल READ_6: what = "READ_6"; अवरोध;
	हाल WRITE_6: what = "WRITE_6"; अवरोध;
	हाल SEEK_6: what = "SEEK_6"; अवरोध;
	हाल READ_REVERSE: what = "READ_REVERSE"; अवरोध;
	हाल WRITE_खाताMARKS: what = "WRITE_FILEMARKS"; अवरोध;
	हाल SPACE: what = "SPACE"; अवरोध;
	हाल INQUIRY: what = "INQUIRY"; अवरोध;
	हाल RECOVER_BUFFERED_DATA: what = "RECOVER_BUFFERED_DATA"; अवरोध;
	हाल MODE_SELECT: what = "MODE_SELECT"; अवरोध;
	हाल RESERVE: what = "RESERVE"; अवरोध;
	हाल RELEASE: what = "RELEASE"; अवरोध;
	हाल COPY: what = "COPY"; अवरोध;
	हाल ERASE: what = "ERASE"; अवरोध;
	हाल MODE_SENSE: what = "MODE_SENSE"; अवरोध;
	हाल START_STOP: what = "START_STOP"; अवरोध;
	हाल RECEIVE_DIAGNOSTIC: what = "RECEIVE_DIAGNOSTIC"; अवरोध;
	हाल SEND_DIAGNOSTIC: what = "SEND_DIAGNOSTIC"; अवरोध;
	हाल ALLOW_MEDIUM_REMOVAL: what = "ALLOW_MEDIUM_REMOVAL"; अवरोध;
	हाल SET_WINDOW: what = "SET_WINDOW"; अवरोध;
	हाल READ_CAPACITY: what = "READ_CAPACITY"; अवरोध;
	हाल READ_10: what = "READ_10"; अवरोध;
	हाल WRITE_10: what = "WRITE_10"; अवरोध;
	हाल SEEK_10: what = "SEEK_10"; अवरोध;
	हाल WRITE_VERIFY: what = "WRITE_VERIFY"; अवरोध;
	हाल VERIFY: what = "VERIFY"; अवरोध;
	हाल SEARCH_HIGH: what = "SEARCH_HIGH"; अवरोध;
	हाल SEARCH_EQUAL: what = "SEARCH_EQUAL"; अवरोध;
	हाल SEARCH_LOW: what = "SEARCH_LOW"; अवरोध;
	हाल SET_LIMITS: what = "SET_LIMITS"; अवरोध;
	हाल READ_POSITION: what = "READ_POSITION"; अवरोध;
	हाल SYNCHRONIZE_CACHE: what = "SYNCHRONIZE_CACHE"; अवरोध;
	हाल LOCK_UNLOCK_CACHE: what = "LOCK_UNLOCK_CACHE"; अवरोध;
	हाल READ_DEFECT_DATA: what = "READ_DEFECT_DATA"; अवरोध;
	हाल MEDIUM_SCAN: what = "MEDIUM_SCAN"; अवरोध;
	हाल COMPARE: what = "COMPARE"; अवरोध;
	हाल COPY_VERIFY: what = "COPY_VERIFY"; अवरोध;
	हाल WRITE_BUFFER: what = "WRITE_BUFFER"; अवरोध;
	हाल READ_BUFFER: what = "READ_BUFFER"; अवरोध;
	हाल UPDATE_BLOCK: what = "UPDATE_BLOCK"; अवरोध;
	हाल READ_LONG: what = "READ_LONG"; अवरोध;
	हाल WRITE_LONG: what = "WRITE_LONG"; अवरोध;
	हाल CHANGE_DEFINITION: what = "CHANGE_DEFINITION"; अवरोध;
	हाल WRITE_SAME: what = "WRITE_SAME"; अवरोध;
	हाल READ_TOC: what = "READ_TOC"; अवरोध;
	हाल LOG_SELECT: what = "LOG_SELECT"; अवरोध;
	हाल LOG_SENSE: what = "LOG_SENSE"; अवरोध;
	हाल MODE_SELECT_10: what = "MODE_SELECT_10"; अवरोध;
	हाल MODE_SENSE_10: what = "MODE_SENSE_10"; अवरोध;
	हाल MOVE_MEDIUM: what = "MOVE_MEDIUM"; अवरोध;
	हाल READ_12: what = "READ_12"; अवरोध;
	हाल WRITE_12: what = "WRITE_12"; अवरोध;
	हाल WRITE_VERIFY_12: what = "WRITE_VERIFY_12"; अवरोध;
	हाल SEARCH_HIGH_12: what = "SEARCH_HIGH_12"; अवरोध;
	हाल SEARCH_EQUAL_12: what = "SEARCH_EQUAL_12"; अवरोध;
	हाल SEARCH_LOW_12: what = "SEARCH_LOW_12"; अवरोध;
	हाल READ_ELEMENT_STATUS: what = "READ_ELEMENT_STATUS"; अवरोध;
	हाल SEND_VOLUME_TAG: what = "SEND_VOLUME_TAG"; अवरोध;
	हाल WRITE_LONG_2: what = "WRITE_LONG_2"; अवरोध;
	शेष:
		MTS_DEBUG("can't decode command\n");
		जाओ out;
		अवरोध;
	पूर्ण
	MTS_DEBUG( "Command %s (%d bytes)\n", what, srb->cmd_len);

 out:
	MTS_DEBUG( "  %10ph\n", srb->cmnd);
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम mts_show_command(काष्ठा scsi_cmnd * dummy)
अणु
पूर्ण

अटल अंतरभूत व्योम mts_debug_dump(काष्ठा mts_desc* dummy)
अणु
पूर्ण

#पूर्ण_अगर

अटल अंतरभूत व्योम mts_urb_पात(काष्ठा mts_desc* desc) अणु
	MTS_DEBUG_GOT_HERE();
	mts_debug_dump(desc);

	usb_समाप्त_urb( desc->urb );
पूर्ण

अटल पूर्णांक mts_slave_alloc (काष्ठा scsi_device *s)
अणु
	s->inquiry_len = 0x24;
	वापस 0;
पूर्ण

अटल पूर्णांक mts_slave_configure (काष्ठा scsi_device *s)
अणु
	blk_queue_dma_alignment(s->request_queue, (512 - 1));
	वापस 0;
पूर्ण

अटल पूर्णांक mts_scsi_पात(काष्ठा scsi_cmnd *srb)
अणु
	काष्ठा mts_desc* desc = (काष्ठा mts_desc*)(srb->device->host->hostdata[0]);

	MTS_DEBUG_GOT_HERE();

	mts_urb_पात(desc);

	वापस FAILED;
पूर्ण

अटल पूर्णांक mts_scsi_host_reset(काष्ठा scsi_cmnd *srb)
अणु
	काष्ठा mts_desc* desc = (काष्ठा mts_desc*)(srb->device->host->hostdata[0]);
	पूर्णांक result;

	MTS_DEBUG_GOT_HERE();
	mts_debug_dump(desc);

	result = usb_lock_device_क्रम_reset(desc->usb_dev, desc->usb_पूर्णांकf);
	अगर (result == 0) अणु
		result = usb_reset_device(desc->usb_dev);
		usb_unlock_device(desc->usb_dev);
	पूर्ण
	वापस result ? FAILED : SUCCESS;
पूर्ण

अटल पूर्णांक
mts_scsi_queuecommand(काष्ठा Scsi_Host *shost, काष्ठा scsi_cmnd *srb);

अटल व्योम mts_transfer_cleanup( काष्ठा urb *transfer );
अटल व्योम mts_करो_sg(काष्ठा urb * transfer);

अटल अंतरभूत
व्योम mts_पूर्णांक_submit_urb (काष्ठा urb* transfer,
			पूर्णांक pipe,
			व्योम* data,
			अचिन्हित length,
			usb_complete_t callback )
/* Interrupt context! */

/* Holding transfer->context->lock! */
अणु
	पूर्णांक res;

	MTS_INT_INIT();

	usb_fill_bulk_urb(transfer,
		      context->instance->usb_dev,
		      pipe,
		      data,
		      length,
		      callback,
		      context
		);

	res = usb_submit_urb( transfer, GFP_ATOMIC );
	अगर ( unlikely(res) ) अणु
		MTS_INT_ERROR( "could not submit URB! Error was %d\n",(पूर्णांक)res );
		set_host_byte(context->srb, DID_ERROR);
		mts_transfer_cleanup(transfer);
	पूर्ण
पूर्ण


अटल व्योम mts_transfer_cleanup( काष्ठा urb *transfer )
/* Interrupt context! */
अणु
	MTS_INT_INIT();

	अगर ( likely(context->final_callback != शून्य) )
		context->final_callback(context->srb);
पूर्ण

अटल व्योम mts_transfer_करोne( काष्ठा urb *transfer )
अणु
	MTS_INT_INIT();

	context->srb->result &= MTS_SCSI_ERR_MASK;
	context->srb->result |= (अचिन्हित)(*context->scsi_status)<<1;

	mts_transfer_cleanup(transfer);
पूर्ण


अटल व्योम mts_get_status( काष्ठा urb *transfer )
/* Interrupt context! */
अणु
	MTS_INT_INIT();

	mts_पूर्णांक_submit_urb(transfer,
			   usb_rcvbulkpipe(context->instance->usb_dev,
					   context->instance->ep_response),
			   context->scsi_status,
			   1,
			   mts_transfer_करोne );
पूर्ण

अटल व्योम mts_data_करोne( काष्ठा urb* transfer )
/* Interrupt context! */
अणु
	पूर्णांक status = transfer->status;
	MTS_INT_INIT();

	अगर ( context->data_length != transfer->actual_length ) अणु
		scsi_set_resid(context->srb, context->data_length -
			       transfer->actual_length);
	पूर्ण अन्यथा अगर ( unlikely(status) ) अणु
		set_host_byte(context->srb, (status == -ENOENT ? DID_ABORT : DID_ERROR));
	पूर्ण

	mts_get_status(transfer);
पूर्ण


अटल व्योम mts_command_करोne( काष्ठा urb *transfer )
/* Interrupt context! */
अणु
	पूर्णांक status = transfer->status;
	MTS_INT_INIT();

	अगर ( unlikely(status) ) अणु
	        अगर (status == -ENOENT) अणु
		        /* We are being समाप्तed */
			MTS_DEBUG_GOT_HERE();
			set_host_byte(context->srb, DID_ABORT);
                पूर्ण अन्यथा अणु
		        /* A genuine error has occurred */
			MTS_DEBUG_GOT_HERE();

		        set_host_byte(context->srb, DID_ERROR);
                पूर्ण
		mts_transfer_cleanup(transfer);

		वापस;
	पूर्ण

	अगर (context->srb->cmnd[0] == REQUEST_SENSE) अणु
		mts_पूर्णांक_submit_urb(transfer,
				   context->data_pipe,
				   context->srb->sense_buffer,
				   context->data_length,
				   mts_data_करोne);
	पूर्ण अन्यथा अणु अगर ( context->data ) अणु
			mts_पूर्णांक_submit_urb(transfer,
					   context->data_pipe,
					   context->data,
					   context->data_length,
					   scsi_sg_count(context->srb) > 1 ?
					           mts_करो_sg : mts_data_करोne);
		पूर्ण अन्यथा अणु
			mts_get_status(transfer);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mts_करो_sg (काष्ठा urb* transfer)
अणु
	पूर्णांक status = transfer->status;
	MTS_INT_INIT();

	MTS_DEBUG("Processing fragment %d of %d\n", context->fragment,
	                                          scsi_sg_count(context->srb));

	अगर (unlikely(status)) अणु
                set_host_byte(context->srb, (status == -ENOENT ? DID_ABORT : DID_ERROR));
		mts_transfer_cleanup(transfer);
        पूर्ण

	context->curr_sg = sg_next(context->curr_sg);
	mts_पूर्णांक_submit_urb(transfer,
			   context->data_pipe,
			   sg_virt(context->curr_sg),
			   context->curr_sg->length,
			   sg_is_last(context->curr_sg) ?
			   mts_data_करोne : mts_करो_sg);
पूर्ण

अटल स्थिर u8 mts_पढ़ो_image_sig[] = अणु 0x28, 00, 00, 00 पूर्ण;
अटल स्थिर u8 mts_पढ़ो_image_sig_len = 4;
अटल स्थिर अचिन्हित अक्षर mts_direction[256/8] = अणु
	0x28, 0x81, 0x14, 0x14, 0x20, 0x01, 0x90, 0x77,
	0x0C, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
पूर्ण;


#घोषणा MTS_सूचीECTION_IS_IN(x) ((mts_direction[x>>3] >> (x & 7)) & 1)

अटल व्योम
mts_build_transfer_context(काष्ठा scsi_cmnd *srb, काष्ठा mts_desc* desc)
अणु
	पूर्णांक pipe;

	MTS_DEBUG_GOT_HERE();

	desc->context.instance = desc;
	desc->context.srb = srb;

	अगर (!scsi_bufflen(srb)) अणु
		desc->context.data = शून्य;
		desc->context.data_length = 0;
		वापस;
	पूर्ण अन्यथा अणु
		desc->context.curr_sg = scsi_sglist(srb);
		desc->context.data = sg_virt(desc->context.curr_sg);
		desc->context.data_length = desc->context.curr_sg->length;
	पूर्ण


	/* can't rely on srb->sc_data_direction */

	/* Brutally ripped from usb-storage */

	अगर ( !स_भेद( srb->cmnd, mts_पढ़ो_image_sig, mts_पढ़ो_image_sig_len )
) अणु 		pipe = usb_rcvbulkpipe(desc->usb_dev,desc->ep_image);
		MTS_DEBUG( "transferring from desc->ep_image == %d\n",
			   (पूर्णांक)desc->ep_image );
	पूर्ण अन्यथा अगर ( MTS_सूचीECTION_IS_IN(srb->cmnd[0]) ) अणु
			pipe = usb_rcvbulkpipe(desc->usb_dev,desc->ep_response);
			MTS_DEBUG( "transferring from desc->ep_response == %d\n",
				   (पूर्णांक)desc->ep_response);
	पूर्ण अन्यथा अणु
		MTS_DEBUG("transferring to desc->ep_out == %d\n",
			  (पूर्णांक)desc->ep_out);
		pipe = usb_sndbulkpipe(desc->usb_dev,desc->ep_out);
	पूर्ण
	desc->context.data_pipe = pipe;
पूर्ण


अटल पूर्णांक
mts_scsi_queuecommand_lck(काष्ठा scsi_cmnd *srb, mts_scsi_cmnd_callback callback)
अणु
	काष्ठा mts_desc* desc = (काष्ठा mts_desc*)(srb->device->host->hostdata[0]);
	पूर्णांक res;

	MTS_DEBUG_GOT_HERE();
	mts_show_command(srb);
	mts_debug_dump(desc);

	अगर ( srb->device->lun || srb->device->id || srb->device->channel ) अणु

		MTS_DEBUG("Command to LUN=%d ID=%d CHANNEL=%d from SCSI layer\n",(पूर्णांक)srb->device->lun,(पूर्णांक)srb->device->id, (पूर्णांक)srb->device->channel );

		MTS_DEBUG("this device doesn't exist\n");

		set_host_byte(srb, DID_BAD_TARGET);

		अगर(likely(callback != शून्य))
			callback(srb);

		जाओ out;
	पूर्ण

	
	usb_fill_bulk_urb(desc->urb,
		      desc->usb_dev,
		      usb_sndbulkpipe(desc->usb_dev,desc->ep_out),
		      srb->cmnd,
		      srb->cmd_len,
		      mts_command_करोne,
		      &desc->context
		      );


	mts_build_transfer_context( srb, desc );
	desc->context.final_callback = callback;
	
	/* here we need ATOMIC as we are called with the iolock */
	res=usb_submit_urb(desc->urb, GFP_ATOMIC);

	अगर(unlikely(res))अणु
		MTS_ERROR("error %d submitting URB\n",(पूर्णांक)res);
		set_host_byte(srb, DID_ERROR);

		अगर(likely(callback != शून्य))
			callback(srb);

	पूर्ण
out:
	वापस 0;
पूर्ण

अटल DEF_SCSI_QCMD(mts_scsi_queuecommand)

अटल काष्ठा scsi_host_ढाँचा mts_scsi_host_ढाँचा = अणु
	.module			= THIS_MODULE,
	.name			= "microtekX6",
	.proc_name		= "microtekX6",
	.queuecommand		= mts_scsi_queuecommand,
	.eh_पात_handler	= mts_scsi_पात,
	.eh_host_reset_handler	= mts_scsi_host_reset,
	.sg_tablesize =		SG_ALL,
	.can_queue =		1,
	.this_id =		-1,
	.emulated =		1,
	.slave_alloc =		mts_slave_alloc,
	.slave_configure =	mts_slave_configure,
	.max_sectors=		256, /* 128 K */
पूर्ण;

/* The entries of microtek_table must correspond, line-by-line to
   the entries of mts_supported_products[]. */

अटल स्थिर काष्ठा usb_device_id mts_usb_ids[] =
अणु
	अणु USB_DEVICE(0x4ce, 0x0300) पूर्ण,
	अणु USB_DEVICE(0x5da, 0x0094) पूर्ण,
	अणु USB_DEVICE(0x5da, 0x0099) पूर्ण,
	अणु USB_DEVICE(0x5da, 0x009a) पूर्ण,
	अणु USB_DEVICE(0x5da, 0x00a0) पूर्ण,
	अणु USB_DEVICE(0x5da, 0x00a3) पूर्ण,
	अणु USB_DEVICE(0x5da, 0x80a3) पूर्ण,
	अणु USB_DEVICE(0x5da, 0x80ac) पूर्ण,
	अणु USB_DEVICE(0x5da, 0x00b6) पूर्ण,
	अणु पूर्ण						/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE (usb, mts_usb_ids);


अटल पूर्णांक mts_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	पूर्णांक i;
	पूर्णांक ep_out = -1;
	पूर्णांक ep_in_set[3]; /* this will अवरोध अगर we have more than three endpoपूर्णांकs
			   which is why we check */
	पूर्णांक *ep_in_current = ep_in_set;
	पूर्णांक err_retval = -ENOMEM;

	काष्ठा mts_desc * new_desc;
	काष्ठा usb_device *dev = पूर्णांकerface_to_usbdev (पूर्णांकf);

	/* the current altsetting on the पूर्णांकerface we're probing */
	काष्ठा usb_host_पूर्णांकerface *altsetting;

	MTS_DEBUG_GOT_HERE();
	MTS_DEBUG( "usb-device descriptor at %x\n", (पूर्णांक)dev );

	MTS_DEBUG( "product id = 0x%x, vendor id = 0x%x\n",
		   le16_to_cpu(dev->descriptor.idProduct),
		   le16_to_cpu(dev->descriptor.idVenकरोr) );

	MTS_DEBUG_GOT_HERE();

	/* the current altsetting on the पूर्णांकerface we're probing */
	altsetting = पूर्णांकf->cur_altsetting;


	/* Check अगर the config is sane */

	अगर ( altsetting->desc.bNumEndpoपूर्णांकs != MTS_EP_TOTAL ) अणु
		MTS_WARNING( "expecting %d got %d endpoints! Bailing out.\n",
			     (पूर्णांक)MTS_EP_TOTAL, (पूर्णांक)altsetting->desc.bNumEndpoपूर्णांकs );
		वापस -ENODEV;
	पूर्ण

	क्रम( i = 0; i < altsetting->desc.bNumEndpoपूर्णांकs; i++ ) अणु
		अगर ((altsetting->endpoपूर्णांक[i].desc.bmAttributes &
		     USB_ENDPOINT_XFERTYPE_MASK) != USB_ENDPOINT_XFER_BULK) अणु

			MTS_WARNING( "can only deal with bulk endpoints; endpoint %d is not bulk.\n",
			     (पूर्णांक)altsetting->endpoपूर्णांक[i].desc.bEndpoपूर्णांकAddress );
		पूर्ण अन्यथा अणु
			अगर (altsetting->endpoपूर्णांक[i].desc.bEndpoपूर्णांकAddress &
			    USB_सूची_IN)
				*ep_in_current++
					= altsetting->endpoपूर्णांक[i].desc.bEndpoपूर्णांकAddress &
					USB_ENDPOINT_NUMBER_MASK;
			अन्यथा अणु
				अगर ( ep_out != -1 ) अणु
					MTS_WARNING( "can only deal with one output endpoints. Bailing out." );
					वापस -ENODEV;
				पूर्ण

				ep_out = altsetting->endpoपूर्णांक[i].desc.bEndpoपूर्णांकAddress &
					USB_ENDPOINT_NUMBER_MASK;
			पूर्ण
		पूर्ण

	पूर्ण

	अगर (ep_in_current != &ep_in_set[2]) अणु
		MTS_WARNING("couldn't find two input bulk endpoints. Bailing out.\n");
		वापस -ENODEV;
	पूर्ण

	अगर ( ep_out == -1 ) अणु
		MTS_WARNING( "couldn't find an output bulk endpoint. Bailing out.\n" );
		वापस -ENODEV;
	पूर्ण


	new_desc = kzalloc(माप(काष्ठा mts_desc), GFP_KERNEL);
	अगर (!new_desc)
		जाओ out;

	new_desc->urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!new_desc->urb)
		जाओ out_kमुक्त;

	new_desc->context.scsi_status = kदो_स्मृति(1, GFP_KERNEL);
	अगर (!new_desc->context.scsi_status)
		जाओ out_मुक्त_urb;

	new_desc->usb_dev = dev;
	new_desc->usb_पूर्णांकf = पूर्णांकf;

	/* endpoपूर्णांकs */
	new_desc->ep_out = ep_out;
	new_desc->ep_response = ep_in_set[0];
	new_desc->ep_image = ep_in_set[1];

	अगर ( new_desc->ep_out != MTS_EP_OUT )
		MTS_WARNING( "will this work? Command EP is not usually %d\n",
			     (पूर्णांक)new_desc->ep_out );

	अगर ( new_desc->ep_response != MTS_EP_RESPONSE )
		MTS_WARNING( "will this work? Response EP is not usually %d\n",
			     (पूर्णांक)new_desc->ep_response );

	अगर ( new_desc->ep_image != MTS_EP_IMAGE )
		MTS_WARNING( "will this work? Image data EP is not usually %d\n",
			     (पूर्णांक)new_desc->ep_image );

	new_desc->host = scsi_host_alloc(&mts_scsi_host_ढाँचा,
			माप(new_desc));
	अगर (!new_desc->host)
		जाओ out_kमुक्त2;

	new_desc->host->hostdata[0] = (अचिन्हित दीर्घ)new_desc;
	अगर (scsi_add_host(new_desc->host, &dev->dev)) अणु
		err_retval = -EIO;
		जाओ out_host_put;
	पूर्ण
	scsi_scan_host(new_desc->host);

	usb_set_पूर्णांकfdata(पूर्णांकf, new_desc);
	वापस 0;

 out_host_put:
	scsi_host_put(new_desc->host);
 out_kमुक्त2:
	kमुक्त(new_desc->context.scsi_status);
 out_मुक्त_urb:
	usb_मुक्त_urb(new_desc->urb);
 out_kमुक्त:
	kमुक्त(new_desc);
 out:
	वापस err_retval;
पूर्ण

अटल व्योम mts_usb_disconnect (काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा mts_desc *desc = usb_get_पूर्णांकfdata(पूर्णांकf);

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);

	usb_समाप्त_urb(desc->urb);
	scsi_हटाओ_host(desc->host);

	scsi_host_put(desc->host);
	usb_मुक्त_urb(desc->urb);
	kमुक्त(desc->context.scsi_status);
	kमुक्त(desc);
पूर्ण

module_usb_driver(mts_usb_driver);

MODULE_AUTHOR( DRIVER_AUTHOR );
MODULE_DESCRIPTION( DRIVER_DESC );
MODULE_LICENSE("GPL");
