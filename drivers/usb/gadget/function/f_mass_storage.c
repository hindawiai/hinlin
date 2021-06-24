<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/*
 * f_mass_storage.c -- Mass Storage USB Composite Function
 *
 * Copyright (C) 2003-2008 Alan Stern
 * Copyright (C) 2009 Samsung Electronics
 *                    Author: Michal Nazarewicz <mina86@mina86.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. The names of the above-listed copyright holders may not be used
 *    to enकरोrse or promote products derived from this software without
 *    specअगरic prior written permission.
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * The Mass Storage Function acts as a USB Mass Storage device,
 * appearing to the host as a disk drive or as a CD-ROM drive.  In
 * addition to providing an example of a genuinely useful composite
 * function क्रम a USB device, it also illustrates a technique of
 * द्विगुन-buffering क्रम increased throughput.
 *
 * For more inक्रमmation about MSF and in particular its module
 * parameters and sysfs पूर्णांकerface पढ़ो the
 * <Documentation/usb/mass-storage.rst> file.
 */

/*
 * MSF is configured by specअगरying a fsg_config काष्ठाure.  It has the
 * following fields:
 *
 *	nluns		Number of LUNs function have (anywhere from 1
 *				to FSG_MAX_LUNS).
 *	luns		An array of LUN configuration values.  This
 *				should be filled क्रम each LUN that
 *				function will include (ie. क्रम "nluns"
 *				LUNs).  Each element of the array has
 *				the following fields:
 *	->filename	The path to the backing file क्रम the LUN.
 *				Required अगर LUN is not marked as
 *				removable.
 *	->ro		Flag specअगरying access to the LUN shall be
 *				पढ़ो-only.  This is implied अगर CD-ROM
 *				emulation is enabled as well as when
 *				it was impossible to खोलो "filename"
 *				in R/W mode.
 *	->removable	Flag specअगरying that LUN shall be indicated as
 *				being removable.
 *	->cdrom		Flag specअगरying that LUN shall be reported as
 *				being a CD-ROM.
 *	->nofua		Flag specअगरying that FUA flag in SCSI WRITE(10,12)
 *				commands क्रम this LUN shall be ignored.
 *
 *	venकरोr_name
 *	product_name
 *	release		Inक्रमmation used as a reply to INQUIRY
 *				request.  To use शेष set to शून्य,
 *				शून्य, 0xffff respectively.  The first
 *				field should be 8 and the second 16
 *				अक्षरacters or less.
 *
 *	can_stall	Set to permit function to halt bulk endpoपूर्णांकs.
 *				Disabled on some USB devices known not
 *				to work correctly.  You should set it
 *				to true.
 *
 * If "removable" is not set क्रम a LUN then a backing file must be
 * specअगरied.  If it is set, then शून्य filename means the LUN's medium
 * is not loaded (an empty string as "filename" in the fsg_config
 * काष्ठाure causes error).  The CD-ROM emulation includes a single
 * data track and no audio tracks; hence there need be only one
 * backing file per LUN.
 *
 * This function is heavily based on "File-backed Storage Gadget" by
 * Alan Stern which in turn is heavily based on "Gadget Zero" by David
 * Brownell.  The driver's SCSI command पूर्णांकerface was based on the
 * "Information technology - Small Computer System Interface - 2"
 * करोcument from X3T9.2 Project 375D, Revision 10L, 7-SEP-93,
 * available at <http://www.t10.org/ftp/t10/drafts/s2/s2-r10l.pdf>.
 * The single exception is opcode 0x23 (READ FORMAT CAPACITIES), which
 * was based on the "Universal Serial Bus Mass Storage Class UFI
 * Command Specअगरication" करोcument, Revision 1.0, December 14, 1998,
 * available at
 * <http://www.usb.org/developers/devclass_करोcs/usbmass-ufi10.pdf>.
 */

/*
 *				Driver Design
 *
 * The MSF is fairly straightक्रमward.  There is a मुख्य kernel
 * thपढ़ो that handles most of the work.  Interrupt routines field
 * callbacks from the controller driver: bulk- and पूर्णांकerrupt-request
 * completion notअगरications, endpoपूर्णांक-0 events, and disconnect events.
 * Completion events are passed to the मुख्य thपढ़ो by wakeup calls.  Many
 * ep0 requests are handled at पूर्णांकerrupt समय, but SetInterface,
 * SetConfiguration, and device reset requests are क्रमwarded to the
 * thपढ़ो in the क्रमm of "exceptions" using SIGUSR1 संकेतs (since they
 * should पूर्णांकerrupt any ongoing file I/O operations).
 *
 * The thपढ़ो's मुख्य routine implements the standard command/data/status
 * parts of a SCSI पूर्णांकeraction.  It and its subroutines are full of tests
 * क्रम pending संकेतs/exceptions -- all this polling is necessary since
 * the kernel has no बनाओ_लाँघ/दीर्घ_लाँघ equivalents.  (Maybe this is an
 * indication that the driver really wants to be running in userspace.)
 * An important poपूर्णांक is that so दीर्घ as the thपढ़ो is alive it keeps an
 * खोलो reference to the backing file.  This will prevent unmounting
 * the backing file's underlying fileप्रणाली and could cause problems
 * during प्रणाली shutकरोwn, क्रम example.  To prevent such problems, the
 * thपढ़ो catches INT, TERM, and KILL संकेतs and converts them पूर्णांकo
 * an EXIT exception.
 *
 * In normal operation the मुख्य thपढ़ो is started during the gadget's
 * fsg_bind() callback and stopped during fsg_unbind().  But it can
 * also निकास when it receives a संकेत, and there's no poपूर्णांक leaving
 * the gadget running when the thपढ़ो is dead.  As of this moment, MSF
 * provides no way to deरेजिस्टर the gadget when thपढ़ो dies -- maybe
 * a callback functions is needed.
 *
 * To provide maximum throughput, the driver uses a circular pipeline of
 * buffer heads (काष्ठा fsg_buffhd).  In principle the pipeline can be
 * arbitrarily दीर्घ; in practice the benefits करोn't justअगरy having more
 * than 2 stages (i.e., द्विगुन buffering).  But it helps to think of the
 * pipeline as being a दीर्घ one.  Each buffer head contains a bulk-in and
 * a bulk-out request poपूर्णांकer (since the buffer can be used क्रम both
 * output and input -- directions always are given from the host's
 * poपूर्णांक of view) as well as a poपूर्णांकer to the buffer and various state
 * variables.
 *
 * Use of the pipeline follows a simple protocol.  There is a variable
 * (fsg->next_buffhd_to_fill) that poपूर्णांकs to the next buffer head to use.
 * At any समय that buffer head may still be in use from an earlier
 * request, so each buffer head has a state variable indicating whether
 * it is EMPTY, FULL, or BUSY.  Typical use involves रुकोing क्रम the
 * buffer head to be EMPTY, filling the buffer either by file I/O or by
 * USB I/O (during which the buffer head is BUSY), and marking the buffer
 * head FULL when the I/O is complete.  Then the buffer will be emptied
 * (again possibly by USB I/O, during which it is marked BUSY) and
 * finally marked EMPTY again (possibly by a completion routine).
 *
 * A module parameter tells the driver to aव्योम stalling the bulk
 * endpoपूर्णांकs wherever the transport specअगरication allows.  This is
 * necessary क्रम some UDCs like the SuperH, which cannot reliably clear a
 * halt on a bulk endpoपूर्णांक.  However, under certain circumstances the
 * Bulk-only specअगरication requires a stall.  In such हालs the driver
 * will halt the endpoपूर्णांक and set a flag indicating that it should clear
 * the halt in software during the next device reset.  Hopefully this
 * will permit everything to work correctly.  Furthermore, although the
 * specअगरication allows the bulk-out endpoपूर्णांक to halt when the host sends
 * too much data, implementing this would cause an unaव्योमable race.
 * The driver will always use the "no-stall" approach क्रम OUT transfers.
 *
 * One subtle poपूर्णांक concerns sending status-stage responses क्रम ep0
 * requests.  Some of these requests, such as device reset, can involve
 * पूर्णांकerrupting an ongoing file I/O operation, which might take an
 * arbitrarily दीर्घ समय.  During that delay the host might give up on
 * the original ep0 request and issue a new one.  When that happens the
 * driver should not notअगरy the host about completion of the original
 * request, as the host will no दीर्घer be रुकोing क्रम it.  So the driver
 * assigns to each ep0 request a unique tag, and it keeps track of the
 * tag value of the request associated with a दीर्घ-running exception
 * (device-reset, पूर्णांकerface-change, or configuration-change).  When the
 * exception handler is finished, the status-stage response is submitted
 * only अगर the current ep0 request tag is equal to the exception request
 * tag.  Thus only the most recently received ep0 request will get a
 * status-stage response.
 *
 * Warning: This driver source file is too दीर्घ.  It ought to be split up
 * पूर्णांकo a header file plus about 3 separate .c files, to handle the details
 * of the Gadget, USB Mass Storage, and SCSI protocols.
 */


/* #घोषणा VERBOSE_DEBUG */
/* #घोषणा DUMP_MSGS */

#समावेश <linux/blkdev.h>
#समावेश <linux/completion.h>
#समावेश <linux/dcache.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/सीमा.स>
#समावेश <linux/rwsem.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/composite.h>

#समावेश <linux/nospec.h>

#समावेश "configfs.h"


/*------------------------------------------------------------------------*/

#घोषणा FSG_DRIVER_DESC		"Mass Storage Function"
#घोषणा FSG_DRIVER_VERSION	"2009/09/11"

अटल स्थिर अक्षर fsg_string_पूर्णांकerface[] = "Mass Storage";

#समावेश "storage_common.h"
#समावेश "f_mass_storage.h"

/* Static strings, in UTF-8 (क्रम simplicity we use only ASCII अक्षरacters) */
अटल काष्ठा usb_string		fsg_strings[] = अणु
	अणुFSG_STRING_INTERFACE,		fsg_string_पूर्णांकerfaceपूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा usb_gadget_strings	fsg_stringtab = अणु
	.language	= 0x0409,		/* en-us */
	.strings	= fsg_strings,
पूर्ण;

अटल काष्ठा usb_gadget_strings *fsg_strings_array[] = अणु
	&fsg_stringtab,
	शून्य,
पूर्ण;

/*-------------------------------------------------------------------------*/

काष्ठा fsg_dev;
काष्ठा fsg_common;

/* Data shared by all the FSG instances. */
काष्ठा fsg_common अणु
	काष्ठा usb_gadget	*gadget;
	काष्ठा usb_composite_dev *cdev;
	काष्ठा fsg_dev		*fsg;
	रुको_queue_head_t	io_रुको;
	रुको_queue_head_t	fsg_रुको;

	/* filesem protects: backing files in use */
	काष्ठा rw_semaphore	filesem;

	/* lock protects: state and thपढ़ो_task */
	spinlock_t		lock;

	काष्ठा usb_ep		*ep0;		/* Copy of gadget->ep0 */
	काष्ठा usb_request	*ep0req;	/* Copy of cdev->req */
	अचिन्हित पूर्णांक		ep0_req_tag;

	काष्ठा fsg_buffhd	*next_buffhd_to_fill;
	काष्ठा fsg_buffhd	*next_buffhd_to_drain;
	काष्ठा fsg_buffhd	*buffhds;
	अचिन्हित पूर्णांक		fsg_num_buffers;

	पूर्णांक			cmnd_size;
	u8			cmnd[MAX_COMMAND_SIZE];

	अचिन्हित पूर्णांक		lun;
	काष्ठा fsg_lun		*luns[FSG_MAX_LUNS];
	काष्ठा fsg_lun		*curlun;

	अचिन्हित पूर्णांक		bulk_out_maxpacket;
	क्रमागत fsg_state		state;		/* For exception handling */
	अचिन्हित पूर्णांक		exception_req_tag;
	व्योम			*exception_arg;

	क्रमागत data_direction	data_dir;
	u32			data_size;
	u32			data_size_from_cmnd;
	u32			tag;
	u32			residue;
	u32			usb_amount_left;

	अचिन्हित पूर्णांक		can_stall:1;
	अचिन्हित पूर्णांक		मुक्त_storage_on_release:1;
	अचिन्हित पूर्णांक		phase_error:1;
	अचिन्हित पूर्णांक		लघु_packet_received:1;
	अचिन्हित पूर्णांक		bad_lun_okay:1;
	अचिन्हित पूर्णांक		running:1;
	अचिन्हित पूर्णांक		sysfs:1;

	काष्ठा completion	thपढ़ो_notअगरier;
	काष्ठा task_काष्ठा	*thपढ़ो_task;

	/* Gadget's निजी data. */
	व्योम			*निजी_data;

	अक्षर inquiry_string[INQUIRY_STRING_LEN];
पूर्ण;

काष्ठा fsg_dev अणु
	काष्ठा usb_function	function;
	काष्ठा usb_gadget	*gadget;	/* Copy of cdev->gadget */
	काष्ठा fsg_common	*common;

	u16			पूर्णांकerface_number;

	अचिन्हित पूर्णांक		bulk_in_enabled:1;
	अचिन्हित पूर्णांक		bulk_out_enabled:1;

	अचिन्हित दीर्घ		atomic_bitflags;
#घोषणा IGNORE_BULK_OUT		0

	काष्ठा usb_ep		*bulk_in;
	काष्ठा usb_ep		*bulk_out;
पूर्ण;

अटल अंतरभूत पूर्णांक __fsg_is_set(काष्ठा fsg_common *common,
			       स्थिर अक्षर *func, अचिन्हित line)
अणु
	अगर (common->fsg)
		वापस 1;
	ERROR(common, "common->fsg is NULL in %s at %u\n", func, line);
	WARN_ON(1);
	वापस 0;
पूर्ण

#घोषणा fsg_is_set(common) likely(__fsg_is_set(common, __func__, __LINE__))

अटल अंतरभूत काष्ठा fsg_dev *fsg_from_func(काष्ठा usb_function *f)
अणु
	वापस container_of(f, काष्ठा fsg_dev, function);
पूर्ण

अटल पूर्णांक exception_in_progress(काष्ठा fsg_common *common)
अणु
	वापस common->state > FSG_STATE_NORMAL;
पूर्ण

/* Make bulk-out requests be भागisible by the maxpacket size */
अटल व्योम set_bulk_out_req_length(काष्ठा fsg_common *common,
				    काष्ठा fsg_buffhd *bh, अचिन्हित पूर्णांक length)
अणु
	अचिन्हित पूर्णांक	rem;

	bh->bulk_out_पूर्णांकended_length = length;
	rem = length % common->bulk_out_maxpacket;
	अगर (rem > 0)
		length += common->bulk_out_maxpacket - rem;
	bh->outreq->length = length;
पूर्ण


/*-------------------------------------------------------------------------*/

अटल पूर्णांक fsg_set_halt(काष्ठा fsg_dev *fsg, काष्ठा usb_ep *ep)
अणु
	स्थिर अक्षर	*name;

	अगर (ep == fsg->bulk_in)
		name = "bulk-in";
	अन्यथा अगर (ep == fsg->bulk_out)
		name = "bulk-out";
	अन्यथा
		name = ep->name;
	DBG(fsg, "%s set halt\n", name);
	वापस usb_ep_set_halt(ep);
पूर्ण


/*-------------------------------------------------------------------------*/

/* These routines may be called in process context or in_irq */

अटल व्योम __उठाओ_exception(काष्ठा fsg_common *common, क्रमागत fsg_state new_state,
			      व्योम *arg)
अणु
	अचिन्हित दीर्घ		flags;

	/*
	 * Do nothing अगर a higher-priority exception is alपढ़ोy in progress.
	 * If a lower-or-equal priority exception is in progress, preempt it
	 * and notअगरy the मुख्य thपढ़ो by sending it a संकेत.
	 */
	spin_lock_irqsave(&common->lock, flags);
	अगर (common->state <= new_state) अणु
		common->exception_req_tag = common->ep0_req_tag;
		common->state = new_state;
		common->exception_arg = arg;
		अगर (common->thपढ़ो_task)
			send_sig_info(SIGUSR1, SEND_SIG_PRIV,
				      common->thपढ़ो_task);
	पूर्ण
	spin_unlock_irqrestore(&common->lock, flags);
पूर्ण

अटल व्योम उठाओ_exception(काष्ठा fsg_common *common, क्रमागत fsg_state new_state)
अणु
	__उठाओ_exception(common, new_state, शून्य);
पूर्ण

/*-------------------------------------------------------------------------*/

अटल पूर्णांक ep0_queue(काष्ठा fsg_common *common)
अणु
	पूर्णांक	rc;

	rc = usb_ep_queue(common->ep0, common->ep0req, GFP_ATOMIC);
	common->ep0->driver_data = common;
	अगर (rc != 0 && rc != -ESHUTDOWN) अणु
		/* We can't करो much more than रुको क्रम a reset */
		WARNING(common, "error in submission: %s --> %d\n",
			common->ep0->name, rc);
	पूर्ण
	वापस rc;
पूर्ण


/*-------------------------------------------------------------------------*/

/* Completion handlers. These always run in_irq. */

अटल व्योम bulk_in_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा fsg_common	*common = ep->driver_data;
	काष्ठा fsg_buffhd	*bh = req->context;

	अगर (req->status || req->actual != req->length)
		DBG(common, "%s --> %d, %u/%u\n", __func__,
		    req->status, req->actual, req->length);
	अगर (req->status == -ECONNRESET)		/* Request was cancelled */
		usb_ep_fअगरo_flush(ep);

	/* Synchronize with the smp_load_acquire() in sleep_thपढ़ो() */
	smp_store_release(&bh->state, BUF_STATE_EMPTY);
	wake_up(&common->io_रुको);
पूर्ण

अटल व्योम bulk_out_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा fsg_common	*common = ep->driver_data;
	काष्ठा fsg_buffhd	*bh = req->context;

	dump_msg(common, "bulk-out", req->buf, req->actual);
	अगर (req->status || req->actual != bh->bulk_out_पूर्णांकended_length)
		DBG(common, "%s --> %d, %u/%u\n", __func__,
		    req->status, req->actual, bh->bulk_out_पूर्णांकended_length);
	अगर (req->status == -ECONNRESET)		/* Request was cancelled */
		usb_ep_fअगरo_flush(ep);

	/* Synchronize with the smp_load_acquire() in sleep_thपढ़ो() */
	smp_store_release(&bh->state, BUF_STATE_FULL);
	wake_up(&common->io_रुको);
पूर्ण

अटल पूर्णांक _fsg_common_get_max_lun(काष्ठा fsg_common *common)
अणु
	पूर्णांक i = ARRAY_SIZE(common->luns) - 1;

	जबतक (i >= 0 && !common->luns[i])
		--i;

	वापस i;
पूर्ण

अटल पूर्णांक fsg_setup(काष्ठा usb_function *f,
		     स्थिर काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा fsg_dev		*fsg = fsg_from_func(f);
	काष्ठा usb_request	*req = fsg->common->ep0req;
	u16			w_index = le16_to_cpu(ctrl->wIndex);
	u16			w_value = le16_to_cpu(ctrl->wValue);
	u16			w_length = le16_to_cpu(ctrl->wLength);

	अगर (!fsg_is_set(fsg->common))
		वापस -EOPNOTSUPP;

	++fsg->common->ep0_req_tag;	/* Record arrival of a new request */
	req->context = शून्य;
	req->length = 0;
	dump_msg(fsg, "ep0-setup", (u8 *) ctrl, माप(*ctrl));

	चयन (ctrl->bRequest) अणु

	हाल US_BULK_RESET_REQUEST:
		अगर (ctrl->bRequestType !=
		    (USB_सूची_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE))
			अवरोध;
		अगर (w_index != fsg->पूर्णांकerface_number || w_value != 0 ||
				w_length != 0)
			वापस -गलत_तर्क;

		/*
		 * Raise an exception to stop the current operation
		 * and reinitialize our state.
		 */
		DBG(fsg, "bulk reset request\n");
		उठाओ_exception(fsg->common, FSG_STATE_PROTOCOL_RESET);
		वापस USB_GADGET_DELAYED_STATUS;

	हाल US_BULK_GET_MAX_LUN:
		अगर (ctrl->bRequestType !=
		    (USB_सूची_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE))
			अवरोध;
		अगर (w_index != fsg->पूर्णांकerface_number || w_value != 0 ||
				w_length != 1)
			वापस -गलत_तर्क;
		VDBG(fsg, "get max LUN\n");
		*(u8 *)req->buf = _fsg_common_get_max_lun(fsg->common);

		/* Respond with data/status */
		req->length = min((u16)1, w_length);
		वापस ep0_queue(fsg->common);
	पूर्ण

	VDBG(fsg,
	     "unknown class-specific control req %02x.%02x v%04x i%04x l%u\n",
	     ctrl->bRequestType, ctrl->bRequest,
	     le16_to_cpu(ctrl->wValue), w_index, w_length);
	वापस -EOPNOTSUPP;
पूर्ण


/*-------------------------------------------------------------------------*/

/* All the following routines run in process context */

/* Use this क्रम bulk or पूर्णांकerrupt transfers, not ep0 */
अटल पूर्णांक start_transfer(काष्ठा fsg_dev *fsg, काष्ठा usb_ep *ep,
			   काष्ठा usb_request *req)
अणु
	पूर्णांक	rc;

	अगर (ep == fsg->bulk_in)
		dump_msg(fsg, "bulk-in", req->buf, req->length);

	rc = usb_ep_queue(ep, req, GFP_KERNEL);
	अगर (rc) अणु

		/* We can't करो much more than रुको क्रम a reset */
		req->status = rc;

		/*
		 * Note: currently the net2280 driver fails zero-length
		 * submissions अगर DMA is enabled.
		 */
		अगर (rc != -ESHUTDOWN &&
				!(rc == -EOPNOTSUPP && req->length == 0))
			WARNING(fsg, "error in submission: %s --> %d\n",
					ep->name, rc);
	पूर्ण
	वापस rc;
पूर्ण

अटल bool start_in_transfer(काष्ठा fsg_common *common, काष्ठा fsg_buffhd *bh)
अणु
	अगर (!fsg_is_set(common))
		वापस false;
	bh->state = BUF_STATE_SENDING;
	अगर (start_transfer(common->fsg, common->fsg->bulk_in, bh->inreq))
		bh->state = BUF_STATE_EMPTY;
	वापस true;
पूर्ण

अटल bool start_out_transfer(काष्ठा fsg_common *common, काष्ठा fsg_buffhd *bh)
अणु
	अगर (!fsg_is_set(common))
		वापस false;
	bh->state = BUF_STATE_RECEIVING;
	अगर (start_transfer(common->fsg, common->fsg->bulk_out, bh->outreq))
		bh->state = BUF_STATE_FULL;
	वापस true;
पूर्ण

अटल पूर्णांक sleep_thपढ़ो(काष्ठा fsg_common *common, bool can_मुक्तze,
		काष्ठा fsg_buffhd *bh)
अणु
	पूर्णांक	rc;

	/* Wait until a संकेत arrives or bh is no दीर्घer busy */
	अगर (can_मुक्तze)
		/*
		 * synchronize with the smp_store_release(&bh->state) in
		 * bulk_in_complete() or bulk_out_complete()
		 */
		rc = रुको_event_मुक्तzable(common->io_रुको,
				bh && smp_load_acquire(&bh->state) >=
					BUF_STATE_EMPTY);
	अन्यथा
		rc = रुको_event_पूर्णांकerruptible(common->io_रुको,
				bh && smp_load_acquire(&bh->state) >=
					BUF_STATE_EMPTY);
	वापस rc ? -EINTR : 0;
पूर्ण


/*-------------------------------------------------------------------------*/

अटल पूर्णांक करो_पढ़ो(काष्ठा fsg_common *common)
अणु
	काष्ठा fsg_lun		*curlun = common->curlun;
	u32			lba;
	काष्ठा fsg_buffhd	*bh;
	पूर्णांक			rc;
	u32			amount_left;
	loff_t			file_offset, file_offset_पंचांगp;
	अचिन्हित पूर्णांक		amount;
	sमाप_प्रकार			nपढ़ो;

	/*
	 * Get the starting Logical Block Address and check that it's
	 * not too big.
	 */
	अगर (common->cmnd[0] == READ_6)
		lba = get_unaligned_be24(&common->cmnd[1]);
	अन्यथा अणु
		lba = get_unaligned_be32(&common->cmnd[2]);

		/*
		 * We allow DPO (Disable Page Out = करोn't save data in the
		 * cache) and FUA (Force Unit Access = करोn't पढ़ो from the
		 * cache), but we करोn't implement them.
		 */
		अगर ((common->cmnd[1] & ~0x18) != 0) अणु
			curlun->sense_data = SS_INVALID_FIELD_IN_CDB;
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	अगर (lba >= curlun->num_sectors) अणु
		curlun->sense_data = SS_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE;
		वापस -EINVAL;
	पूर्ण
	file_offset = ((loff_t) lba) << curlun->blkbits;

	/* Carry out the file पढ़ोs */
	amount_left = common->data_size_from_cmnd;
	अगर (unlikely(amount_left == 0))
		वापस -EIO;		/* No शेष reply */

	क्रम (;;) अणु
		/*
		 * Figure out how much we need to पढ़ो:
		 * Try to पढ़ो the reमुख्यing amount.
		 * But करोn't पढ़ो more than the buffer size.
		 * And करोn't try to पढ़ो past the end of the file.
		 */
		amount = min(amount_left, FSG_BUFLEN);
		amount = min((loff_t)amount,
			     curlun->file_length - file_offset);

		/* Wait क्रम the next buffer to become available */
		bh = common->next_buffhd_to_fill;
		rc = sleep_thपढ़ो(common, false, bh);
		अगर (rc)
			वापस rc;

		/*
		 * If we were asked to पढ़ो past the end of file,
		 * end with an empty buffer.
		 */
		अगर (amount == 0) अणु
			curlun->sense_data =
					SS_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE;
			curlun->sense_data_info =
					file_offset >> curlun->blkbits;
			curlun->info_valid = 1;
			bh->inreq->length = 0;
			bh->state = BUF_STATE_FULL;
			अवरोध;
		पूर्ण

		/* Perक्रमm the पढ़ो */
		file_offset_पंचांगp = file_offset;
		nपढ़ो = kernel_पढ़ो(curlun->filp, bh->buf, amount,
				&file_offset_पंचांगp);
		VLDBG(curlun, "file read %u @ %llu -> %d\n", amount,
		      (अचिन्हित दीर्घ दीर्घ)file_offset, (पूर्णांक)nपढ़ो);
		अगर (संकेत_pending(current))
			वापस -EINTR;

		अगर (nपढ़ो < 0) अणु
			LDBG(curlun, "error in file read: %d\n", (पूर्णांक)nपढ़ो);
			nपढ़ो = 0;
		पूर्ण अन्यथा अगर (nपढ़ो < amount) अणु
			LDBG(curlun, "partial file read: %d/%u\n",
			     (पूर्णांक)nपढ़ो, amount);
			nपढ़ो = round_करोwn(nपढ़ो, curlun->blksize);
		पूर्ण
		file_offset  += nपढ़ो;
		amount_left  -= nपढ़ो;
		common->residue -= nपढ़ो;

		/*
		 * Except at the end of the transfer, nपढ़ो will be
		 * equal to the buffer size, which is भागisible by the
		 * bulk-in maxpacket size.
		 */
		bh->inreq->length = nपढ़ो;
		bh->state = BUF_STATE_FULL;

		/* If an error occurred, report it and its position */
		अगर (nपढ़ो < amount) अणु
			curlun->sense_data = SS_UNRECOVERED_READ_ERROR;
			curlun->sense_data_info =
					file_offset >> curlun->blkbits;
			curlun->info_valid = 1;
			अवरोध;
		पूर्ण

		अगर (amount_left == 0)
			अवरोध;		/* No more left to पढ़ो */

		/* Send this buffer and go पढ़ो some more */
		bh->inreq->zero = 0;
		अगर (!start_in_transfer(common, bh))
			/* Don't know what to करो अगर common->fsg is शून्य */
			वापस -EIO;
		common->next_buffhd_to_fill = bh->next;
	पूर्ण

	वापस -EIO;		/* No शेष reply */
पूर्ण


/*-------------------------------------------------------------------------*/

अटल पूर्णांक करो_ग_लिखो(काष्ठा fsg_common *common)
अणु
	काष्ठा fsg_lun		*curlun = common->curlun;
	u32			lba;
	काष्ठा fsg_buffhd	*bh;
	पूर्णांक			get_some_more;
	u32			amount_left_to_req, amount_left_to_ग_लिखो;
	loff_t			usb_offset, file_offset, file_offset_पंचांगp;
	अचिन्हित पूर्णांक		amount;
	sमाप_प्रकार			nwritten;
	पूर्णांक			rc;

	अगर (curlun->ro) अणु
		curlun->sense_data = SS_WRITE_PROTECTED;
		वापस -EINVAL;
	पूर्ण
	spin_lock(&curlun->filp->f_lock);
	curlun->filp->f_flags &= ~O_SYNC;	/* Default is not to रुको */
	spin_unlock(&curlun->filp->f_lock);

	/*
	 * Get the starting Logical Block Address and check that it's
	 * not too big
	 */
	अगर (common->cmnd[0] == WRITE_6)
		lba = get_unaligned_be24(&common->cmnd[1]);
	अन्यथा अणु
		lba = get_unaligned_be32(&common->cmnd[2]);

		/*
		 * We allow DPO (Disable Page Out = करोn't save data in the
		 * cache) and FUA (Force Unit Access = ग_लिखो directly to the
		 * medium).  We करोn't implement DPO; we implement FUA by
		 * perक्रमming synchronous output.
		 */
		अगर (common->cmnd[1] & ~0x18) अणु
			curlun->sense_data = SS_INVALID_FIELD_IN_CDB;
			वापस -EINVAL;
		पूर्ण
		अगर (!curlun->nofua && (common->cmnd[1] & 0x08)) अणु /* FUA */
			spin_lock(&curlun->filp->f_lock);
			curlun->filp->f_flags |= O_SYNC;
			spin_unlock(&curlun->filp->f_lock);
		पूर्ण
	पूर्ण
	अगर (lba >= curlun->num_sectors) अणु
		curlun->sense_data = SS_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE;
		वापस -EINVAL;
	पूर्ण

	/* Carry out the file ग_लिखोs */
	get_some_more = 1;
	file_offset = usb_offset = ((loff_t) lba) << curlun->blkbits;
	amount_left_to_req = common->data_size_from_cmnd;
	amount_left_to_ग_लिखो = common->data_size_from_cmnd;

	जबतक (amount_left_to_ग_लिखो > 0) अणु

		/* Queue a request क्रम more data from the host */
		bh = common->next_buffhd_to_fill;
		अगर (bh->state == BUF_STATE_EMPTY && get_some_more) अणु

			/*
			 * Figure out how much we want to get:
			 * Try to get the reमुख्यing amount,
			 * but not more than the buffer size.
			 */
			amount = min(amount_left_to_req, FSG_BUFLEN);

			/* Beyond the end of the backing file? */
			अगर (usb_offset >= curlun->file_length) अणु
				get_some_more = 0;
				curlun->sense_data =
					SS_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE;
				curlun->sense_data_info =
					usb_offset >> curlun->blkbits;
				curlun->info_valid = 1;
				जारी;
			पूर्ण

			/* Get the next buffer */
			usb_offset += amount;
			common->usb_amount_left -= amount;
			amount_left_to_req -= amount;
			अगर (amount_left_to_req == 0)
				get_some_more = 0;

			/*
			 * Except at the end of the transfer, amount will be
			 * equal to the buffer size, which is भागisible by
			 * the bulk-out maxpacket size.
			 */
			set_bulk_out_req_length(common, bh, amount);
			अगर (!start_out_transfer(common, bh))
				/* Dunno what to करो अगर common->fsg is शून्य */
				वापस -EIO;
			common->next_buffhd_to_fill = bh->next;
			जारी;
		पूर्ण

		/* Write the received data to the backing file */
		bh = common->next_buffhd_to_drain;
		अगर (bh->state == BUF_STATE_EMPTY && !get_some_more)
			अवरोध;			/* We stopped early */

		/* Wait क्रम the data to be received */
		rc = sleep_thपढ़ो(common, false, bh);
		अगर (rc)
			वापस rc;

		common->next_buffhd_to_drain = bh->next;
		bh->state = BUF_STATE_EMPTY;

		/* Did something go wrong with the transfer? */
		अगर (bh->outreq->status != 0) अणु
			curlun->sense_data = SS_COMMUNICATION_FAILURE;
			curlun->sense_data_info =
					file_offset >> curlun->blkbits;
			curlun->info_valid = 1;
			अवरोध;
		पूर्ण

		amount = bh->outreq->actual;
		अगर (curlun->file_length - file_offset < amount) अणु
			LERROR(curlun, "write %u @ %llu beyond end %llu\n",
				       amount, (अचिन्हित दीर्घ दीर्घ)file_offset,
				       (अचिन्हित दीर्घ दीर्घ)curlun->file_length);
			amount = curlun->file_length - file_offset;
		पूर्ण

		/*
		 * Don't accept excess data.  The spec doesn't say
		 * what to करो in this हाल.  We'll ignore the error.
		 */
		amount = min(amount, bh->bulk_out_पूर्णांकended_length);

		/* Don't ग_लिखो a partial block */
		amount = round_करोwn(amount, curlun->blksize);
		अगर (amount == 0)
			जाओ empty_ग_लिखो;

		/* Perक्रमm the ग_लिखो */
		file_offset_पंचांगp = file_offset;
		nwritten = kernel_ग_लिखो(curlun->filp, bh->buf, amount,
				&file_offset_पंचांगp);
		VLDBG(curlun, "file write %u @ %llu -> %d\n", amount,
				(अचिन्हित दीर्घ दीर्घ)file_offset, (पूर्णांक)nwritten);
		अगर (संकेत_pending(current))
			वापस -EINTR;		/* Interrupted! */

		अगर (nwritten < 0) अणु
			LDBG(curlun, "error in file write: %d\n",
					(पूर्णांक) nwritten);
			nwritten = 0;
		पूर्ण अन्यथा अगर (nwritten < amount) अणु
			LDBG(curlun, "partial file write: %d/%u\n",
					(पूर्णांक) nwritten, amount);
			nwritten = round_करोwn(nwritten, curlun->blksize);
		पूर्ण
		file_offset += nwritten;
		amount_left_to_ग_लिखो -= nwritten;
		common->residue -= nwritten;

		/* If an error occurred, report it and its position */
		अगर (nwritten < amount) अणु
			curlun->sense_data = SS_WRITE_ERROR;
			curlun->sense_data_info =
					file_offset >> curlun->blkbits;
			curlun->info_valid = 1;
			अवरोध;
		पूर्ण

 empty_ग_लिखो:
		/* Did the host decide to stop early? */
		अगर (bh->outreq->actual < bh->bulk_out_पूर्णांकended_length) अणु
			common->लघु_packet_received = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस -EIO;		/* No शेष reply */
पूर्ण


/*-------------------------------------------------------------------------*/

अटल पूर्णांक करो_synchronize_cache(काष्ठा fsg_common *common)
अणु
	काष्ठा fsg_lun	*curlun = common->curlun;
	पूर्णांक		rc;

	/* We ignore the requested LBA and ग_लिखो out all file's
	 * dirty data buffers. */
	rc = fsg_lun_fsync_sub(curlun);
	अगर (rc)
		curlun->sense_data = SS_WRITE_ERROR;
	वापस 0;
पूर्ण


/*-------------------------------------------------------------------------*/

अटल व्योम invalidate_sub(काष्ठा fsg_lun *curlun)
अणु
	काष्ठा file	*filp = curlun->filp;
	काष्ठा inode	*inode = file_inode(filp);
	अचिन्हित दीर्घ	rc;

	rc = invalidate_mapping_pages(inode->i_mapping, 0, -1);
	VLDBG(curlun, "invalidate_mapping_pages -> %ld\n", rc);
पूर्ण

अटल पूर्णांक करो_verअगरy(काष्ठा fsg_common *common)
अणु
	काष्ठा fsg_lun		*curlun = common->curlun;
	u32			lba;
	u32			verअगरication_length;
	काष्ठा fsg_buffhd	*bh = common->next_buffhd_to_fill;
	loff_t			file_offset, file_offset_पंचांगp;
	u32			amount_left;
	अचिन्हित पूर्णांक		amount;
	sमाप_प्रकार			nपढ़ो;

	/*
	 * Get the starting Logical Block Address and check that it's
	 * not too big.
	 */
	lba = get_unaligned_be32(&common->cmnd[2]);
	अगर (lba >= curlun->num_sectors) अणु
		curlun->sense_data = SS_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE;
		वापस -EINVAL;
	पूर्ण

	/*
	 * We allow DPO (Disable Page Out = करोn't save data in the
	 * cache) but we करोn't implement it.
	 */
	अगर (common->cmnd[1] & ~0x10) अणु
		curlun->sense_data = SS_INVALID_FIELD_IN_CDB;
		वापस -EINVAL;
	पूर्ण

	verअगरication_length = get_unaligned_be16(&common->cmnd[7]);
	अगर (unlikely(verअगरication_length == 0))
		वापस -EIO;		/* No शेष reply */

	/* Prepare to carry out the file verअगरy */
	amount_left = verअगरication_length << curlun->blkbits;
	file_offset = ((loff_t) lba) << curlun->blkbits;

	/* Write out all the dirty buffers beक्रमe invalidating them */
	fsg_lun_fsync_sub(curlun);
	अगर (संकेत_pending(current))
		वापस -EINTR;

	invalidate_sub(curlun);
	अगर (संकेत_pending(current))
		वापस -EINTR;

	/* Just try to पढ़ो the requested blocks */
	जबतक (amount_left > 0) अणु
		/*
		 * Figure out how much we need to पढ़ो:
		 * Try to पढ़ो the reमुख्यing amount, but not more than
		 * the buffer size.
		 * And करोn't try to पढ़ो past the end of the file.
		 */
		amount = min(amount_left, FSG_BUFLEN);
		amount = min((loff_t)amount,
			     curlun->file_length - file_offset);
		अगर (amount == 0) अणु
			curlun->sense_data =
					SS_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE;
			curlun->sense_data_info =
				file_offset >> curlun->blkbits;
			curlun->info_valid = 1;
			अवरोध;
		पूर्ण

		/* Perक्रमm the पढ़ो */
		file_offset_पंचांगp = file_offset;
		nपढ़ो = kernel_पढ़ो(curlun->filp, bh->buf, amount,
				&file_offset_पंचांगp);
		VLDBG(curlun, "file read %u @ %llu -> %d\n", amount,
				(अचिन्हित दीर्घ दीर्घ) file_offset,
				(पूर्णांक) nपढ़ो);
		अगर (संकेत_pending(current))
			वापस -EINTR;

		अगर (nपढ़ो < 0) अणु
			LDBG(curlun, "error in file verify: %d\n", (पूर्णांक)nपढ़ो);
			nपढ़ो = 0;
		पूर्ण अन्यथा अगर (nपढ़ो < amount) अणु
			LDBG(curlun, "partial file verify: %d/%u\n",
			     (पूर्णांक)nपढ़ो, amount);
			nपढ़ो = round_करोwn(nपढ़ो, curlun->blksize);
		पूर्ण
		अगर (nपढ़ो == 0) अणु
			curlun->sense_data = SS_UNRECOVERED_READ_ERROR;
			curlun->sense_data_info =
				file_offset >> curlun->blkbits;
			curlun->info_valid = 1;
			अवरोध;
		पूर्ण
		file_offset += nपढ़ो;
		amount_left -= nपढ़ो;
	पूर्ण
	वापस 0;
पूर्ण


/*-------------------------------------------------------------------------*/

अटल पूर्णांक करो_inquiry(काष्ठा fsg_common *common, काष्ठा fsg_buffhd *bh)
अणु
	काष्ठा fsg_lun *curlun = common->curlun;
	u8	*buf = (u8 *) bh->buf;

	अगर (!curlun) अणु		/* Unsupported LUNs are okay */
		common->bad_lun_okay = 1;
		स_रखो(buf, 0, 36);
		buf[0] = TYPE_NO_LUN;	/* Unsupported, no device-type */
		buf[4] = 31;		/* Additional length */
		वापस 36;
	पूर्ण

	buf[0] = curlun->cdrom ? TYPE_ROM : TYPE_DISK;
	buf[1] = curlun->removable ? 0x80 : 0;
	buf[2] = 2;		/* ANSI SCSI level 2 */
	buf[3] = 2;		/* SCSI-2 INQUIRY data क्रमmat */
	buf[4] = 31;		/* Additional length */
	buf[5] = 0;		/* No special options */
	buf[6] = 0;
	buf[7] = 0;
	अगर (curlun->inquiry_string[0])
		स_नकल(buf + 8, curlun->inquiry_string,
		       माप(curlun->inquiry_string));
	अन्यथा
		स_नकल(buf + 8, common->inquiry_string,
		       माप(common->inquiry_string));
	वापस 36;
पूर्ण

अटल पूर्णांक करो_request_sense(काष्ठा fsg_common *common, काष्ठा fsg_buffhd *bh)
अणु
	काष्ठा fsg_lun	*curlun = common->curlun;
	u8		*buf = (u8 *) bh->buf;
	u32		sd, sdinfo;
	पूर्णांक		valid;

	/*
	 * From the SCSI-2 spec., section 7.9 (Unit attention condition):
	 *
	 * If a REQUEST SENSE command is received from an initiator
	 * with a pending unit attention condition (beक्रमe the target
	 * generates the contingent allegiance condition), then the
	 * target shall either:
	 *   a) report any pending sense data and preserve the unit
	 *	attention condition on the logical unit, or,
	 *   b) report the unit attention condition, may discard any
	 *	pending sense data, and clear the unit attention
	 *	condition on the logical unit क्रम that initiator.
	 *
	 * FSG normally uses option a); enable this code to use option b).
	 */
#अगर 0
	अगर (curlun && curlun->unit_attention_data != SS_NO_SENSE) अणु
		curlun->sense_data = curlun->unit_attention_data;
		curlun->unit_attention_data = SS_NO_SENSE;
	पूर्ण
#पूर्ण_अगर

	अगर (!curlun) अणु		/* Unsupported LUNs are okay */
		common->bad_lun_okay = 1;
		sd = SS_LOGICAL_UNIT_NOT_SUPPORTED;
		sdinfo = 0;
		valid = 0;
	पूर्ण अन्यथा अणु
		sd = curlun->sense_data;
		sdinfo = curlun->sense_data_info;
		valid = curlun->info_valid << 7;
		curlun->sense_data = SS_NO_SENSE;
		curlun->sense_data_info = 0;
		curlun->info_valid = 0;
	पूर्ण

	स_रखो(buf, 0, 18);
	buf[0] = valid | 0x70;			/* Valid, current error */
	buf[2] = SK(sd);
	put_unaligned_be32(sdinfo, &buf[3]);	/* Sense inक्रमmation */
	buf[7] = 18 - 8;			/* Additional sense length */
	buf[12] = ASC(sd);
	buf[13] = ASCQ(sd);
	वापस 18;
पूर्ण

अटल पूर्णांक करो_पढ़ो_capacity(काष्ठा fsg_common *common, काष्ठा fsg_buffhd *bh)
अणु
	काष्ठा fsg_lun	*curlun = common->curlun;
	u32		lba = get_unaligned_be32(&common->cmnd[2]);
	पूर्णांक		pmi = common->cmnd[8];
	u8		*buf = (u8 *)bh->buf;

	/* Check the PMI and LBA fields */
	अगर (pmi > 1 || (pmi == 0 && lba != 0)) अणु
		curlun->sense_data = SS_INVALID_FIELD_IN_CDB;
		वापस -EINVAL;
	पूर्ण

	put_unaligned_be32(curlun->num_sectors - 1, &buf[0]);
						/* Max logical block */
	put_unaligned_be32(curlun->blksize, &buf[4]);/* Block length */
	वापस 8;
पूर्ण

अटल पूर्णांक करो_पढ़ो_header(काष्ठा fsg_common *common, काष्ठा fsg_buffhd *bh)
अणु
	काष्ठा fsg_lun	*curlun = common->curlun;
	पूर्णांक		msf = common->cmnd[1] & 0x02;
	u32		lba = get_unaligned_be32(&common->cmnd[2]);
	u8		*buf = (u8 *)bh->buf;

	अगर (common->cmnd[1] & ~0x02) अणु		/* Mask away MSF */
		curlun->sense_data = SS_INVALID_FIELD_IN_CDB;
		वापस -EINVAL;
	पूर्ण
	अगर (lba >= curlun->num_sectors) अणु
		curlun->sense_data = SS_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE;
		वापस -EINVAL;
	पूर्ण

	स_रखो(buf, 0, 8);
	buf[0] = 0x01;		/* 2048 bytes of user data, rest is EC */
	store_cdrom_address(&buf[4], msf, lba);
	वापस 8;
पूर्ण

अटल पूर्णांक करो_पढ़ो_toc(काष्ठा fsg_common *common, काष्ठा fsg_buffhd *bh)
अणु
	काष्ठा fsg_lun	*curlun = common->curlun;
	पूर्णांक		msf = common->cmnd[1] & 0x02;
	पूर्णांक		start_track = common->cmnd[6];
	u8		*buf = (u8 *)bh->buf;

	अगर ((common->cmnd[1] & ~0x02) != 0 ||	/* Mask away MSF */
			start_track > 1) अणु
		curlun->sense_data = SS_INVALID_FIELD_IN_CDB;
		वापस -EINVAL;
	पूर्ण

	स_रखो(buf, 0, 20);
	buf[1] = (20-2);		/* TOC data length */
	buf[2] = 1;			/* First track number */
	buf[3] = 1;			/* Last track number */
	buf[5] = 0x16;			/* Data track, copying allowed */
	buf[6] = 0x01;			/* Only track is number 1 */
	store_cdrom_address(&buf[8], msf, 0);

	buf[13] = 0x16;			/* Lead-out track is data */
	buf[14] = 0xAA;			/* Lead-out track number */
	store_cdrom_address(&buf[16], msf, curlun->num_sectors);
	वापस 20;
पूर्ण

अटल पूर्णांक करो_mode_sense(काष्ठा fsg_common *common, काष्ठा fsg_buffhd *bh)
अणु
	काष्ठा fsg_lun	*curlun = common->curlun;
	पूर्णांक		mscmnd = common->cmnd[0];
	u8		*buf = (u8 *) bh->buf;
	u8		*buf0 = buf;
	पूर्णांक		pc, page_code;
	पूर्णांक		changeable_values, all_pages;
	पूर्णांक		valid_page = 0;
	पूर्णांक		len, limit;

	अगर ((common->cmnd[1] & ~0x08) != 0) अणु	/* Mask away DBD */
		curlun->sense_data = SS_INVALID_FIELD_IN_CDB;
		वापस -EINVAL;
	पूर्ण
	pc = common->cmnd[2] >> 6;
	page_code = common->cmnd[2] & 0x3f;
	अगर (pc == 3) अणु
		curlun->sense_data = SS_SAVING_PARAMETERS_NOT_SUPPORTED;
		वापस -EINVAL;
	पूर्ण
	changeable_values = (pc == 1);
	all_pages = (page_code == 0x3f);

	/*
	 * Write the mode parameter header.  Fixed values are: शेष
	 * medium type, no cache control (DPOFUA), and no block descriptors.
	 * The only variable value is the WriteProtect bit.  We will fill in
	 * the mode data length later.
	 */
	स_रखो(buf, 0, 8);
	अगर (mscmnd == MODE_SENSE) अणु
		buf[2] = (curlun->ro ? 0x80 : 0x00);		/* WP, DPOFUA */
		buf += 4;
		limit = 255;
	पूर्ण अन्यथा अणु			/* MODE_SENSE_10 */
		buf[3] = (curlun->ro ? 0x80 : 0x00);		/* WP, DPOFUA */
		buf += 8;
		limit = 65535;		/* Should really be FSG_BUFLEN */
	पूर्ण

	/* No block descriptors */

	/*
	 * The mode pages, in numerical order.  The only page we support
	 * is the Caching page.
	 */
	अगर (page_code == 0x08 || all_pages) अणु
		valid_page = 1;
		buf[0] = 0x08;		/* Page code */
		buf[1] = 10;		/* Page length */
		स_रखो(buf+2, 0, 10);	/* None of the fields are changeable */

		अगर (!changeable_values) अणु
			buf[2] = 0x04;	/* Write cache enable, */
					/* Read cache not disabled */
					/* No cache retention priorities */
			put_unaligned_be16(0xffff, &buf[4]);
					/* Don't disable prefetch */
					/* Minimum prefetch = 0 */
			put_unaligned_be16(0xffff, &buf[8]);
					/* Maximum prefetch */
			put_unaligned_be16(0xffff, &buf[10]);
					/* Maximum prefetch उच्चमानing */
		पूर्ण
		buf += 12;
	पूर्ण

	/*
	 * Check that a valid page was requested and the mode data length
	 * isn't too दीर्घ.
	 */
	len = buf - buf0;
	अगर (!valid_page || len > limit) अणु
		curlun->sense_data = SS_INVALID_FIELD_IN_CDB;
		वापस -EINVAL;
	पूर्ण

	/*  Store the mode data length */
	अगर (mscmnd == MODE_SENSE)
		buf0[0] = len - 1;
	अन्यथा
		put_unaligned_be16(len - 2, buf0);
	वापस len;
पूर्ण

अटल पूर्णांक करो_start_stop(काष्ठा fsg_common *common)
अणु
	काष्ठा fsg_lun	*curlun = common->curlun;
	पूर्णांक		loej, start;

	अगर (!curlun) अणु
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (!curlun->removable) अणु
		curlun->sense_data = SS_INVALID_COMMAND;
		वापस -EINVAL;
	पूर्ण अन्यथा अगर ((common->cmnd[1] & ~0x01) != 0 || /* Mask away Immed */
		   (common->cmnd[4] & ~0x03) != 0) अणु /* Mask LoEj, Start */
		curlun->sense_data = SS_INVALID_FIELD_IN_CDB;
		वापस -EINVAL;
	पूर्ण

	loej  = common->cmnd[4] & 0x02;
	start = common->cmnd[4] & 0x01;

	/*
	 * Our emulation करोesn't support mounting; the medium is
	 * available क्रम use as soon as it is loaded.
	 */
	अगर (start) अणु
		अगर (!fsg_lun_is_खोलो(curlun)) अणु
			curlun->sense_data = SS_MEDIUM_NOT_PRESENT;
			वापस -EINVAL;
		पूर्ण
		वापस 0;
	पूर्ण

	/* Are we allowed to unload the media? */
	अगर (curlun->prevent_medium_removal) अणु
		LDBG(curlun, "unload attempt prevented\n");
		curlun->sense_data = SS_MEDIUM_REMOVAL_PREVENTED;
		वापस -EINVAL;
	पूर्ण

	अगर (!loej)
		वापस 0;

	up_पढ़ो(&common->filesem);
	करोwn_ग_लिखो(&common->filesem);
	fsg_lun_बंद(curlun);
	up_ग_लिखो(&common->filesem);
	करोwn_पढ़ो(&common->filesem);

	वापस 0;
पूर्ण

अटल पूर्णांक करो_prevent_allow(काष्ठा fsg_common *common)
अणु
	काष्ठा fsg_lun	*curlun = common->curlun;
	पूर्णांक		prevent;

	अगर (!common->curlun) अणु
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (!common->curlun->removable) अणु
		common->curlun->sense_data = SS_INVALID_COMMAND;
		वापस -EINVAL;
	पूर्ण

	prevent = common->cmnd[4] & 0x01;
	अगर ((common->cmnd[4] & ~0x01) != 0) अणु	/* Mask away Prevent */
		curlun->sense_data = SS_INVALID_FIELD_IN_CDB;
		वापस -EINVAL;
	पूर्ण

	अगर (curlun->prevent_medium_removal && !prevent)
		fsg_lun_fsync_sub(curlun);
	curlun->prevent_medium_removal = prevent;
	वापस 0;
पूर्ण

अटल पूर्णांक करो_पढ़ो_क्रमmat_capacities(काष्ठा fsg_common *common,
			काष्ठा fsg_buffhd *bh)
अणु
	काष्ठा fsg_lun	*curlun = common->curlun;
	u8		*buf = (u8 *) bh->buf;

	buf[0] = buf[1] = buf[2] = 0;
	buf[3] = 8;	/* Only the Current/Maximum Capacity Descriptor */
	buf += 4;

	put_unaligned_be32(curlun->num_sectors, &buf[0]);
						/* Number of blocks */
	put_unaligned_be32(curlun->blksize, &buf[4]);/* Block length */
	buf[4] = 0x02;				/* Current capacity */
	वापस 12;
पूर्ण

अटल पूर्णांक करो_mode_select(काष्ठा fsg_common *common, काष्ठा fsg_buffhd *bh)
अणु
	काष्ठा fsg_lun	*curlun = common->curlun;

	/* We करोn't support MODE SELECT */
	अगर (curlun)
		curlun->sense_data = SS_INVALID_COMMAND;
	वापस -EINVAL;
पूर्ण


/*-------------------------------------------------------------------------*/

अटल पूर्णांक halt_bulk_in_endpoपूर्णांक(काष्ठा fsg_dev *fsg)
अणु
	पूर्णांक	rc;

	rc = fsg_set_halt(fsg, fsg->bulk_in);
	अगर (rc == -EAGAIN)
		VDBG(fsg, "delayed bulk-in endpoint halt\n");
	जबतक (rc != 0) अणु
		अगर (rc != -EAGAIN) अणु
			WARNING(fsg, "usb_ep_set_halt -> %d\n", rc);
			rc = 0;
			अवरोध;
		पूर्ण

		/* Wait क्रम a लघु समय and then try again */
		अगर (msleep_पूर्णांकerruptible(100) != 0)
			वापस -EINTR;
		rc = usb_ep_set_halt(fsg->bulk_in);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक wedge_bulk_in_endpoपूर्णांक(काष्ठा fsg_dev *fsg)
अणु
	पूर्णांक	rc;

	DBG(fsg, "bulk-in set wedge\n");
	rc = usb_ep_set_wedge(fsg->bulk_in);
	अगर (rc == -EAGAIN)
		VDBG(fsg, "delayed bulk-in endpoint wedge\n");
	जबतक (rc != 0) अणु
		अगर (rc != -EAGAIN) अणु
			WARNING(fsg, "usb_ep_set_wedge -> %d\n", rc);
			rc = 0;
			अवरोध;
		पूर्ण

		/* Wait क्रम a लघु समय and then try again */
		अगर (msleep_पूर्णांकerruptible(100) != 0)
			वापस -EINTR;
		rc = usb_ep_set_wedge(fsg->bulk_in);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक throw_away_data(काष्ठा fsg_common *common)
अणु
	काष्ठा fsg_buffhd	*bh, *bh2;
	u32			amount;
	पूर्णांक			rc;

	क्रम (bh = common->next_buffhd_to_drain;
	     bh->state != BUF_STATE_EMPTY || common->usb_amount_left > 0;
	     bh = common->next_buffhd_to_drain) अणु

		/* Try to submit another request अगर we need one */
		bh2 = common->next_buffhd_to_fill;
		अगर (bh2->state == BUF_STATE_EMPTY &&
				common->usb_amount_left > 0) अणु
			amount = min(common->usb_amount_left, FSG_BUFLEN);

			/*
			 * Except at the end of the transfer, amount will be
			 * equal to the buffer size, which is भागisible by
			 * the bulk-out maxpacket size.
			 */
			set_bulk_out_req_length(common, bh2, amount);
			अगर (!start_out_transfer(common, bh2))
				/* Dunno what to करो अगर common->fsg is शून्य */
				वापस -EIO;
			common->next_buffhd_to_fill = bh2->next;
			common->usb_amount_left -= amount;
			जारी;
		पूर्ण

		/* Wait क्रम the data to be received */
		rc = sleep_thपढ़ो(common, false, bh);
		अगर (rc)
			वापस rc;

		/* Throw away the data in a filled buffer */
		bh->state = BUF_STATE_EMPTY;
		common->next_buffhd_to_drain = bh->next;

		/* A लघु packet or an error ends everything */
		अगर (bh->outreq->actual < bh->bulk_out_पूर्णांकended_length ||
				bh->outreq->status != 0) अणु
			उठाओ_exception(common, FSG_STATE_ABORT_BULK_OUT);
			वापस -EINTR;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक finish_reply(काष्ठा fsg_common *common)
अणु
	काष्ठा fsg_buffhd	*bh = common->next_buffhd_to_fill;
	पूर्णांक			rc = 0;

	चयन (common->data_dir) अणु
	हाल DATA_सूची_NONE:
		अवरोध;			/* Nothing to send */

	/*
	 * If we करोn't know whether the host wants to पढ़ो or ग_लिखो,
	 * this must be CB or CBI with an unknown command.  We mustn't
	 * try to send or receive any data.  So stall both bulk pipes
	 * अगर we can and रुको क्रम a reset.
	 */
	हाल DATA_सूची_UNKNOWN:
		अगर (!common->can_stall) अणु
			/* Nothing */
		पूर्ण अन्यथा अगर (fsg_is_set(common)) अणु
			fsg_set_halt(common->fsg, common->fsg->bulk_out);
			rc = halt_bulk_in_endpoपूर्णांक(common->fsg);
		पूर्ण अन्यथा अणु
			/* Don't know what to करो अगर common->fsg is शून्य */
			rc = -EIO;
		पूर्ण
		अवरोध;

	/* All but the last buffer of data must have alपढ़ोy been sent */
	हाल DATA_सूची_TO_HOST:
		अगर (common->data_size == 0) अणु
			/* Nothing to send */

		/* Don't know what to करो अगर common->fsg is शून्य */
		पूर्ण अन्यथा अगर (!fsg_is_set(common)) अणु
			rc = -EIO;

		/* If there's no residue, simply send the last buffer */
		पूर्ण अन्यथा अगर (common->residue == 0) अणु
			bh->inreq->zero = 0;
			अगर (!start_in_transfer(common, bh))
				वापस -EIO;
			common->next_buffhd_to_fill = bh->next;

		/*
		 * For Bulk-only, mark the end of the data with a लघु
		 * packet.  If we are allowed to stall, halt the bulk-in
		 * endpoपूर्णांक.  (Note: This violates the Bulk-Only Transport
		 * specअगरication, which requires us to pad the data अगर we
		 * करोn't halt the endpoपूर्णांक.  Presumably nobody will mind.)
		 */
		पूर्ण अन्यथा अणु
			bh->inreq->zero = 1;
			अगर (!start_in_transfer(common, bh))
				rc = -EIO;
			common->next_buffhd_to_fill = bh->next;
			अगर (common->can_stall)
				rc = halt_bulk_in_endpoपूर्णांक(common->fsg);
		पूर्ण
		अवरोध;

	/*
	 * We have processed all we want from the data the host has sent.
	 * There may still be outstanding bulk-out requests.
	 */
	हाल DATA_सूची_FROM_HOST:
		अगर (common->residue == 0) अणु
			/* Nothing to receive */

		/* Did the host stop sending unexpectedly early? */
		पूर्ण अन्यथा अगर (common->लघु_packet_received) अणु
			उठाओ_exception(common, FSG_STATE_ABORT_BULK_OUT);
			rc = -EINTR;

		/*
		 * We haven't processed all the incoming data.  Even though
		 * we may be allowed to stall, करोing so would cause a race.
		 * The controller may alपढ़ोy have ACK'ed all the reमुख्यing
		 * bulk-out packets, in which हाल the host wouldn't see a
		 * STALL.  Not realizing the endpoपूर्णांक was halted, it wouldn't
		 * clear the halt -- leading to problems later on.
		 */
#अगर 0
		पूर्ण अन्यथा अगर (common->can_stall) अणु
			अगर (fsg_is_set(common))
				fsg_set_halt(common->fsg,
					     common->fsg->bulk_out);
			उठाओ_exception(common, FSG_STATE_ABORT_BULK_OUT);
			rc = -EINTR;
#पूर्ण_अगर

		/*
		 * We can't stall.  Read in the excess data and throw it
		 * all away.
		 */
		पूर्ण अन्यथा अणु
			rc = throw_away_data(common);
		पूर्ण
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम send_status(काष्ठा fsg_common *common)
अणु
	काष्ठा fsg_lun		*curlun = common->curlun;
	काष्ठा fsg_buffhd	*bh;
	काष्ठा bulk_cs_wrap	*csw;
	पूर्णांक			rc;
	u8			status = US_BULK_STAT_OK;
	u32			sd, sdinfo = 0;

	/* Wait क्रम the next buffer to become available */
	bh = common->next_buffhd_to_fill;
	rc = sleep_thपढ़ो(common, false, bh);
	अगर (rc)
		वापस;

	अगर (curlun) अणु
		sd = curlun->sense_data;
		sdinfo = curlun->sense_data_info;
	पूर्ण अन्यथा अगर (common->bad_lun_okay)
		sd = SS_NO_SENSE;
	अन्यथा
		sd = SS_LOGICAL_UNIT_NOT_SUPPORTED;

	अगर (common->phase_error) अणु
		DBG(common, "sending phase-error status\n");
		status = US_BULK_STAT_PHASE;
		sd = SS_INVALID_COMMAND;
	पूर्ण अन्यथा अगर (sd != SS_NO_SENSE) अणु
		DBG(common, "sending command-failure status\n");
		status = US_BULK_STAT_FAIL;
		VDBG(common, "  sense data: SK x%02x, ASC x%02x, ASCQ x%02x;"
				"  info x%x\n",
				SK(sd), ASC(sd), ASCQ(sd), sdinfo);
	पूर्ण

	/* Store and send the Bulk-only CSW */
	csw = (व्योम *)bh->buf;

	csw->Signature = cpu_to_le32(US_BULK_CS_SIGN);
	csw->Tag = common->tag;
	csw->Residue = cpu_to_le32(common->residue);
	csw->Status = status;

	bh->inreq->length = US_BULK_CS_WRAP_LEN;
	bh->inreq->zero = 0;
	अगर (!start_in_transfer(common, bh))
		/* Don't know what to करो अगर common->fsg is शून्य */
		वापस;

	common->next_buffhd_to_fill = bh->next;
	वापस;
पूर्ण


/*-------------------------------------------------------------------------*/

/*
 * Check whether the command is properly क्रमmed and whether its data size
 * and direction agree with the values we alपढ़ोy have.
 */
अटल पूर्णांक check_command(काष्ठा fsg_common *common, पूर्णांक cmnd_size,
			 क्रमागत data_direction data_dir, अचिन्हित पूर्णांक mask,
			 पूर्णांक needs_medium, स्थिर अक्षर *name)
अणु
	पूर्णांक			i;
	अचिन्हित पूर्णांक		lun = common->cmnd[1] >> 5;
	अटल स्थिर अक्षर	dirletter[4] = अणु'u', 'o', 'i', 'n'पूर्ण;
	अक्षर			hdlen[20];
	काष्ठा fsg_lun		*curlun;

	hdlen[0] = 0;
	अगर (common->data_dir != DATA_सूची_UNKNOWN)
		प्र_लिखो(hdlen, ", H%c=%u", dirletter[(पूर्णांक) common->data_dir],
			common->data_size);
	VDBG(common, "SCSI command: %s;  Dc=%d, D%c=%u;  Hc=%d%s\n",
	     name, cmnd_size, dirletter[(पूर्णांक) data_dir],
	     common->data_size_from_cmnd, common->cmnd_size, hdlen);

	/*
	 * We can't reply at all until we know the correct data direction
	 * and size.
	 */
	अगर (common->data_size_from_cmnd == 0)
		data_dir = DATA_सूची_NONE;
	अगर (common->data_size < common->data_size_from_cmnd) अणु
		/*
		 * Host data size < Device data size is a phase error.
		 * Carry out the command, but only transfer as much as
		 * we are allowed.
		 */
		common->data_size_from_cmnd = common->data_size;
		common->phase_error = 1;
	पूर्ण
	common->residue = common->data_size;
	common->usb_amount_left = common->data_size;

	/* Conflicting data directions is a phase error */
	अगर (common->data_dir != data_dir && common->data_size_from_cmnd > 0) अणु
		common->phase_error = 1;
		वापस -EINVAL;
	पूर्ण

	/* Verअगरy the length of the command itself */
	अगर (cmnd_size != common->cmnd_size) अणु

		/*
		 * Special हाल workaround: There are plenty of buggy SCSI
		 * implementations. Many have issues with cbw->Length
		 * field passing a wrong command size. For those हालs we
		 * always try to work around the problem by using the length
		 * sent by the host side provided it is at least as large
		 * as the correct command length.
		 * Examples of such हालs would be MS-Winकरोws, which issues
		 * REQUEST SENSE with cbw->Length == 12 where it should
		 * be 6, and xbox360 issuing INQUIRY, TEST UNIT READY and
		 * REQUEST SENSE with cbw->Length == 10 where it should
		 * be 6 as well.
		 */
		अगर (cmnd_size <= common->cmnd_size) अणु
			DBG(common, "%s is buggy! Expected length %d "
			    "but we got %d\n", name,
			    cmnd_size, common->cmnd_size);
			cmnd_size = common->cmnd_size;
		पूर्ण अन्यथा अणु
			common->phase_error = 1;
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Check that the LUN values are consistent */
	अगर (common->lun != lun)
		DBG(common, "using LUN %u from CBW, not LUN %u from CDB\n",
		    common->lun, lun);

	/* Check the LUN */
	curlun = common->curlun;
	अगर (curlun) अणु
		अगर (common->cmnd[0] != REQUEST_SENSE) अणु
			curlun->sense_data = SS_NO_SENSE;
			curlun->sense_data_info = 0;
			curlun->info_valid = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		common->bad_lun_okay = 0;

		/*
		 * INQUIRY and REQUEST SENSE commands are explicitly allowed
		 * to use unsupported LUNs; all others may not.
		 */
		अगर (common->cmnd[0] != INQUIRY &&
		    common->cmnd[0] != REQUEST_SENSE) अणु
			DBG(common, "unsupported LUN %u\n", common->lun);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/*
	 * If a unit attention condition exists, only INQUIRY and
	 * REQUEST SENSE commands are allowed; anything अन्यथा must fail.
	 */
	अगर (curlun && curlun->unit_attention_data != SS_NO_SENSE &&
	    common->cmnd[0] != INQUIRY &&
	    common->cmnd[0] != REQUEST_SENSE) अणु
		curlun->sense_data = curlun->unit_attention_data;
		curlun->unit_attention_data = SS_NO_SENSE;
		वापस -EINVAL;
	पूर्ण

	/* Check that only command bytes listed in the mask are non-zero */
	common->cmnd[1] &= 0x1f;			/* Mask away the LUN */
	क्रम (i = 1; i < cmnd_size; ++i) अणु
		अगर (common->cmnd[i] && !(mask & (1 << i))) अणु
			अगर (curlun)
				curlun->sense_data = SS_INVALID_FIELD_IN_CDB;
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* If the medium isn't mounted and the command needs to access
	 * it, वापस an error. */
	अगर (curlun && !fsg_lun_is_खोलो(curlun) && needs_medium) अणु
		curlun->sense_data = SS_MEDIUM_NOT_PRESENT;
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* wrapper of check_command क्रम data size in blocks handling */
अटल पूर्णांक check_command_size_in_blocks(काष्ठा fsg_common *common,
		पूर्णांक cmnd_size, क्रमागत data_direction data_dir,
		अचिन्हित पूर्णांक mask, पूर्णांक needs_medium, स्थिर अक्षर *name)
अणु
	अगर (common->curlun)
		common->data_size_from_cmnd <<= common->curlun->blkbits;
	वापस check_command(common, cmnd_size, data_dir,
			mask, needs_medium, name);
पूर्ण

अटल पूर्णांक करो_scsi_command(काष्ठा fsg_common *common)
अणु
	काष्ठा fsg_buffhd	*bh;
	पूर्णांक			rc;
	पूर्णांक			reply = -EINVAL;
	पूर्णांक			i;
	अटल अक्षर		unknown[16];

	dump_cdb(common);

	/* Wait क्रम the next buffer to become available क्रम data or status */
	bh = common->next_buffhd_to_fill;
	common->next_buffhd_to_drain = bh;
	rc = sleep_thपढ़ो(common, false, bh);
	अगर (rc)
		वापस rc;

	common->phase_error = 0;
	common->लघु_packet_received = 0;

	करोwn_पढ़ो(&common->filesem);	/* We're using the backing file */
	चयन (common->cmnd[0]) अणु

	हाल INQUIRY:
		common->data_size_from_cmnd = common->cmnd[4];
		reply = check_command(common, 6, DATA_सूची_TO_HOST,
				      (1<<4), 0,
				      "INQUIRY");
		अगर (reply == 0)
			reply = करो_inquiry(common, bh);
		अवरोध;

	हाल MODE_SELECT:
		common->data_size_from_cmnd = common->cmnd[4];
		reply = check_command(common, 6, DATA_सूची_FROM_HOST,
				      (1<<1) | (1<<4), 0,
				      "MODE SELECT(6)");
		अगर (reply == 0)
			reply = करो_mode_select(common, bh);
		अवरोध;

	हाल MODE_SELECT_10:
		common->data_size_from_cmnd =
			get_unaligned_be16(&common->cmnd[7]);
		reply = check_command(common, 10, DATA_सूची_FROM_HOST,
				      (1<<1) | (3<<7), 0,
				      "MODE SELECT(10)");
		अगर (reply == 0)
			reply = करो_mode_select(common, bh);
		अवरोध;

	हाल MODE_SENSE:
		common->data_size_from_cmnd = common->cmnd[4];
		reply = check_command(common, 6, DATA_सूची_TO_HOST,
				      (1<<1) | (1<<2) | (1<<4), 0,
				      "MODE SENSE(6)");
		अगर (reply == 0)
			reply = करो_mode_sense(common, bh);
		अवरोध;

	हाल MODE_SENSE_10:
		common->data_size_from_cmnd =
			get_unaligned_be16(&common->cmnd[7]);
		reply = check_command(common, 10, DATA_सूची_TO_HOST,
				      (1<<1) | (1<<2) | (3<<7), 0,
				      "MODE SENSE(10)");
		अगर (reply == 0)
			reply = करो_mode_sense(common, bh);
		अवरोध;

	हाल ALLOW_MEDIUM_REMOVAL:
		common->data_size_from_cmnd = 0;
		reply = check_command(common, 6, DATA_सूची_NONE,
				      (1<<4), 0,
				      "PREVENT-ALLOW MEDIUM REMOVAL");
		अगर (reply == 0)
			reply = करो_prevent_allow(common);
		अवरोध;

	हाल READ_6:
		i = common->cmnd[4];
		common->data_size_from_cmnd = (i == 0) ? 256 : i;
		reply = check_command_size_in_blocks(common, 6,
				      DATA_सूची_TO_HOST,
				      (7<<1) | (1<<4), 1,
				      "READ(6)");
		अगर (reply == 0)
			reply = करो_पढ़ो(common);
		अवरोध;

	हाल READ_10:
		common->data_size_from_cmnd =
				get_unaligned_be16(&common->cmnd[7]);
		reply = check_command_size_in_blocks(common, 10,
				      DATA_सूची_TO_HOST,
				      (1<<1) | (0xf<<2) | (3<<7), 1,
				      "READ(10)");
		अगर (reply == 0)
			reply = करो_पढ़ो(common);
		अवरोध;

	हाल READ_12:
		common->data_size_from_cmnd =
				get_unaligned_be32(&common->cmnd[6]);
		reply = check_command_size_in_blocks(common, 12,
				      DATA_सूची_TO_HOST,
				      (1<<1) | (0xf<<2) | (0xf<<6), 1,
				      "READ(12)");
		अगर (reply == 0)
			reply = करो_पढ़ो(common);
		अवरोध;

	हाल READ_CAPACITY:
		common->data_size_from_cmnd = 8;
		reply = check_command(common, 10, DATA_सूची_TO_HOST,
				      (0xf<<2) | (1<<8), 1,
				      "READ CAPACITY");
		अगर (reply == 0)
			reply = करो_पढ़ो_capacity(common, bh);
		अवरोध;

	हाल READ_HEADER:
		अगर (!common->curlun || !common->curlun->cdrom)
			जाओ unknown_cmnd;
		common->data_size_from_cmnd =
			get_unaligned_be16(&common->cmnd[7]);
		reply = check_command(common, 10, DATA_सूची_TO_HOST,
				      (3<<7) | (0x1f<<1), 1,
				      "READ HEADER");
		अगर (reply == 0)
			reply = करो_पढ़ो_header(common, bh);
		अवरोध;

	हाल READ_TOC:
		अगर (!common->curlun || !common->curlun->cdrom)
			जाओ unknown_cmnd;
		common->data_size_from_cmnd =
			get_unaligned_be16(&common->cmnd[7]);
		reply = check_command(common, 10, DATA_सूची_TO_HOST,
				      (7<<6) | (1<<1), 1,
				      "READ TOC");
		अगर (reply == 0)
			reply = करो_पढ़ो_toc(common, bh);
		अवरोध;

	हाल READ_FORMAT_CAPACITIES:
		common->data_size_from_cmnd =
			get_unaligned_be16(&common->cmnd[7]);
		reply = check_command(common, 10, DATA_सूची_TO_HOST,
				      (3<<7), 1,
				      "READ FORMAT CAPACITIES");
		अगर (reply == 0)
			reply = करो_पढ़ो_क्रमmat_capacities(common, bh);
		अवरोध;

	हाल REQUEST_SENSE:
		common->data_size_from_cmnd = common->cmnd[4];
		reply = check_command(common, 6, DATA_सूची_TO_HOST,
				      (1<<4), 0,
				      "REQUEST SENSE");
		अगर (reply == 0)
			reply = करो_request_sense(common, bh);
		अवरोध;

	हाल START_STOP:
		common->data_size_from_cmnd = 0;
		reply = check_command(common, 6, DATA_सूची_NONE,
				      (1<<1) | (1<<4), 0,
				      "START-STOP UNIT");
		अगर (reply == 0)
			reply = करो_start_stop(common);
		अवरोध;

	हाल SYNCHRONIZE_CACHE:
		common->data_size_from_cmnd = 0;
		reply = check_command(common, 10, DATA_सूची_NONE,
				      (0xf<<2) | (3<<7), 1,
				      "SYNCHRONIZE CACHE");
		अगर (reply == 0)
			reply = करो_synchronize_cache(common);
		अवरोध;

	हाल TEST_UNIT_READY:
		common->data_size_from_cmnd = 0;
		reply = check_command(common, 6, DATA_सूची_NONE,
				0, 1,
				"TEST UNIT READY");
		अवरोध;

	/*
	 * Although optional, this command is used by MS-Winकरोws.  We
	 * support a minimal version: BytChk must be 0.
	 */
	हाल VERIFY:
		common->data_size_from_cmnd = 0;
		reply = check_command(common, 10, DATA_सूची_NONE,
				      (1<<1) | (0xf<<2) | (3<<7), 1,
				      "VERIFY");
		अगर (reply == 0)
			reply = करो_verअगरy(common);
		अवरोध;

	हाल WRITE_6:
		i = common->cmnd[4];
		common->data_size_from_cmnd = (i == 0) ? 256 : i;
		reply = check_command_size_in_blocks(common, 6,
				      DATA_सूची_FROM_HOST,
				      (7<<1) | (1<<4), 1,
				      "WRITE(6)");
		अगर (reply == 0)
			reply = करो_ग_लिखो(common);
		अवरोध;

	हाल WRITE_10:
		common->data_size_from_cmnd =
				get_unaligned_be16(&common->cmnd[7]);
		reply = check_command_size_in_blocks(common, 10,
				      DATA_सूची_FROM_HOST,
				      (1<<1) | (0xf<<2) | (3<<7), 1,
				      "WRITE(10)");
		अगर (reply == 0)
			reply = करो_ग_लिखो(common);
		अवरोध;

	हाल WRITE_12:
		common->data_size_from_cmnd =
				get_unaligned_be32(&common->cmnd[6]);
		reply = check_command_size_in_blocks(common, 12,
				      DATA_सूची_FROM_HOST,
				      (1<<1) | (0xf<<2) | (0xf<<6), 1,
				      "WRITE(12)");
		अगर (reply == 0)
			reply = करो_ग_लिखो(common);
		अवरोध;

	/*
	 * Some mandatory commands that we recognize but करोn't implement.
	 * They करोn't mean much in this setting.  It's left as an exercise
	 * क्रम anyone पूर्णांकerested to implement RESERVE and RELEASE in terms
	 * of Posix locks.
	 */
	हाल FORMAT_UNIT:
	हाल RELEASE:
	हाल RESERVE:
	हाल SEND_DIAGNOSTIC:

	शेष:
unknown_cmnd:
		common->data_size_from_cmnd = 0;
		प्र_लिखो(unknown, "Unknown x%02x", common->cmnd[0]);
		reply = check_command(common, common->cmnd_size,
				      DATA_सूची_UNKNOWN, ~0, 0, unknown);
		अगर (reply == 0) अणु
			common->curlun->sense_data = SS_INVALID_COMMAND;
			reply = -EINVAL;
		पूर्ण
		अवरोध;
	पूर्ण
	up_पढ़ो(&common->filesem);

	अगर (reply == -EINTR || संकेत_pending(current))
		वापस -EINTR;

	/* Set up the single reply buffer क्रम finish_reply() */
	अगर (reply == -EINVAL)
		reply = 0;		/* Error reply length */
	अगर (reply >= 0 && common->data_dir == DATA_सूची_TO_HOST) अणु
		reply = min((u32)reply, common->data_size_from_cmnd);
		bh->inreq->length = reply;
		bh->state = BUF_STATE_FULL;
		common->residue -= reply;
	पूर्ण				/* Otherwise it's alपढ़ोy set */

	वापस 0;
पूर्ण


/*-------------------------------------------------------------------------*/

अटल पूर्णांक received_cbw(काष्ठा fsg_dev *fsg, काष्ठा fsg_buffhd *bh)
अणु
	काष्ठा usb_request	*req = bh->outreq;
	काष्ठा bulk_cb_wrap	*cbw = req->buf;
	काष्ठा fsg_common	*common = fsg->common;

	/* Was this a real packet?  Should it be ignored? */
	अगर (req->status || test_bit(IGNORE_BULK_OUT, &fsg->atomic_bitflags))
		वापस -EINVAL;

	/* Is the CBW valid? */
	अगर (req->actual != US_BULK_CB_WRAP_LEN ||
			cbw->Signature != cpu_to_le32(
				US_BULK_CB_SIGN)) अणु
		DBG(fsg, "invalid CBW: len %u sig 0x%x\n",
				req->actual,
				le32_to_cpu(cbw->Signature));

		/*
		 * The Bulk-only spec says we MUST stall the IN endpoपूर्णांक
		 * (6.6.1), so it's unaव्योमable.  It also says we must
		 * retain this state until the next reset, but there's
		 * no way to tell the controller driver it should ignore
		 * Clear-Feature(HALT) requests.
		 *
		 * We aren't required to halt the OUT endpoपूर्णांक; instead
		 * we can simply accept and discard any data received
		 * until the next reset.
		 */
		wedge_bulk_in_endpoपूर्णांक(fsg);
		set_bit(IGNORE_BULK_OUT, &fsg->atomic_bitflags);
		वापस -EINVAL;
	पूर्ण

	/* Is the CBW meaningful? */
	अगर (cbw->Lun >= ARRAY_SIZE(common->luns) ||
	    cbw->Flags & ~US_BULK_FLAG_IN || cbw->Length <= 0 ||
	    cbw->Length > MAX_COMMAND_SIZE) अणु
		DBG(fsg, "non-meaningful CBW: lun = %u, flags = 0x%x, "
				"cmdlen %u\n",
				cbw->Lun, cbw->Flags, cbw->Length);

		/*
		 * We can करो anything we want here, so let's stall the
		 * bulk pipes अगर we are allowed to.
		 */
		अगर (common->can_stall) अणु
			fsg_set_halt(fsg, fsg->bulk_out);
			halt_bulk_in_endpoपूर्णांक(fsg);
		पूर्ण
		वापस -EINVAL;
	पूर्ण

	/* Save the command क्रम later */
	common->cmnd_size = cbw->Length;
	स_नकल(common->cmnd, cbw->CDB, common->cmnd_size);
	अगर (cbw->Flags & US_BULK_FLAG_IN)
		common->data_dir = DATA_सूची_TO_HOST;
	अन्यथा
		common->data_dir = DATA_सूची_FROM_HOST;
	common->data_size = le32_to_cpu(cbw->DataTransferLength);
	अगर (common->data_size == 0)
		common->data_dir = DATA_सूची_NONE;
	common->lun = cbw->Lun;
	अगर (common->lun < ARRAY_SIZE(common->luns))
		common->curlun = common->luns[common->lun];
	अन्यथा
		common->curlun = शून्य;
	common->tag = cbw->Tag;
	वापस 0;
पूर्ण

अटल पूर्णांक get_next_command(काष्ठा fsg_common *common)
अणु
	काष्ठा fsg_buffhd	*bh;
	पूर्णांक			rc = 0;

	/* Wait क्रम the next buffer to become available */
	bh = common->next_buffhd_to_fill;
	rc = sleep_thपढ़ो(common, true, bh);
	अगर (rc)
		वापस rc;

	/* Queue a request to पढ़ो a Bulk-only CBW */
	set_bulk_out_req_length(common, bh, US_BULK_CB_WRAP_LEN);
	अगर (!start_out_transfer(common, bh))
		/* Don't know what to करो अगर common->fsg is शून्य */
		वापस -EIO;

	/*
	 * We will drain the buffer in software, which means we
	 * can reuse it क्रम the next filling.  No need to advance
	 * next_buffhd_to_fill.
	 */

	/* Wait क्रम the CBW to arrive */
	rc = sleep_thपढ़ो(common, true, bh);
	अगर (rc)
		वापस rc;

	rc = fsg_is_set(common) ? received_cbw(common->fsg, bh) : -EIO;
	bh->state = BUF_STATE_EMPTY;

	वापस rc;
पूर्ण


/*-------------------------------------------------------------------------*/

अटल पूर्णांक alloc_request(काष्ठा fsg_common *common, काष्ठा usb_ep *ep,
		काष्ठा usb_request **preq)
अणु
	*preq = usb_ep_alloc_request(ep, GFP_ATOMIC);
	अगर (*preq)
		वापस 0;
	ERROR(common, "can't allocate request for %s\n", ep->name);
	वापस -ENOMEM;
पूर्ण

/* Reset पूर्णांकerface setting and re-init endpoपूर्णांक state (toggle etc). */
अटल पूर्णांक करो_set_पूर्णांकerface(काष्ठा fsg_common *common, काष्ठा fsg_dev *new_fsg)
अणु
	काष्ठा fsg_dev *fsg;
	पूर्णांक i, rc = 0;

	अगर (common->running)
		DBG(common, "reset interface\n");

reset:
	/* Deallocate the requests */
	अगर (common->fsg) अणु
		fsg = common->fsg;

		क्रम (i = 0; i < common->fsg_num_buffers; ++i) अणु
			काष्ठा fsg_buffhd *bh = &common->buffhds[i];

			अगर (bh->inreq) अणु
				usb_ep_मुक्त_request(fsg->bulk_in, bh->inreq);
				bh->inreq = शून्य;
			पूर्ण
			अगर (bh->outreq) अणु
				usb_ep_मुक्त_request(fsg->bulk_out, bh->outreq);
				bh->outreq = शून्य;
			पूर्ण
		पूर्ण

		/* Disable the endpoपूर्णांकs */
		अगर (fsg->bulk_in_enabled) अणु
			usb_ep_disable(fsg->bulk_in);
			fsg->bulk_in_enabled = 0;
		पूर्ण
		अगर (fsg->bulk_out_enabled) अणु
			usb_ep_disable(fsg->bulk_out);
			fsg->bulk_out_enabled = 0;
		पूर्ण

		common->fsg = शून्य;
		wake_up(&common->fsg_रुको);
	पूर्ण

	common->running = 0;
	अगर (!new_fsg || rc)
		वापस rc;

	common->fsg = new_fsg;
	fsg = common->fsg;

	/* Enable the endpoपूर्णांकs */
	rc = config_ep_by_speed(common->gadget, &(fsg->function), fsg->bulk_in);
	अगर (rc)
		जाओ reset;
	rc = usb_ep_enable(fsg->bulk_in);
	अगर (rc)
		जाओ reset;
	fsg->bulk_in->driver_data = common;
	fsg->bulk_in_enabled = 1;

	rc = config_ep_by_speed(common->gadget, &(fsg->function),
				fsg->bulk_out);
	अगर (rc)
		जाओ reset;
	rc = usb_ep_enable(fsg->bulk_out);
	अगर (rc)
		जाओ reset;
	fsg->bulk_out->driver_data = common;
	fsg->bulk_out_enabled = 1;
	common->bulk_out_maxpacket = usb_endpoपूर्णांक_maxp(fsg->bulk_out->desc);
	clear_bit(IGNORE_BULK_OUT, &fsg->atomic_bitflags);

	/* Allocate the requests */
	क्रम (i = 0; i < common->fsg_num_buffers; ++i) अणु
		काष्ठा fsg_buffhd	*bh = &common->buffhds[i];

		rc = alloc_request(common, fsg->bulk_in, &bh->inreq);
		अगर (rc)
			जाओ reset;
		rc = alloc_request(common, fsg->bulk_out, &bh->outreq);
		अगर (rc)
			जाओ reset;
		bh->inreq->buf = bh->outreq->buf = bh->buf;
		bh->inreq->context = bh->outreq->context = bh;
		bh->inreq->complete = bulk_in_complete;
		bh->outreq->complete = bulk_out_complete;
	पूर्ण

	common->running = 1;
	क्रम (i = 0; i < ARRAY_SIZE(common->luns); ++i)
		अगर (common->luns[i])
			common->luns[i]->unit_attention_data =
				SS_RESET_OCCURRED;
	वापस rc;
पूर्ण


/****************************** ALT CONFIGS ******************************/

अटल पूर्णांक fsg_set_alt(काष्ठा usb_function *f, अचिन्हित पूर्णांकf, अचिन्हित alt)
अणु
	काष्ठा fsg_dev *fsg = fsg_from_func(f);

	__उठाओ_exception(fsg->common, FSG_STATE_CONFIG_CHANGE, fsg);
	वापस USB_GADGET_DELAYED_STATUS;
पूर्ण

अटल व्योम fsg_disable(काष्ठा usb_function *f)
अणु
	काष्ठा fsg_dev *fsg = fsg_from_func(f);

	__उठाओ_exception(fsg->common, FSG_STATE_CONFIG_CHANGE, शून्य);
पूर्ण


/*-------------------------------------------------------------------------*/

अटल व्योम handle_exception(काष्ठा fsg_common *common)
अणु
	पूर्णांक			i;
	काष्ठा fsg_buffhd	*bh;
	क्रमागत fsg_state		old_state;
	काष्ठा fsg_lun		*curlun;
	अचिन्हित पूर्णांक		exception_req_tag;
	काष्ठा fsg_dev		*new_fsg;

	/*
	 * Clear the existing संकेतs.  Anything but SIGUSR1 is converted
	 * पूर्णांकo a high-priority EXIT exception.
	 */
	क्रम (;;) अणु
		पूर्णांक sig = kernel_dequeue_संकेत();
		अगर (!sig)
			अवरोध;
		अगर (sig != SIGUSR1) अणु
			spin_lock_irq(&common->lock);
			अगर (common->state < FSG_STATE_EXIT)
				DBG(common, "Main thread exiting on signal\n");
			common->state = FSG_STATE_EXIT;
			spin_unlock_irq(&common->lock);
		पूर्ण
	पूर्ण

	/* Cancel all the pending transfers */
	अगर (likely(common->fsg)) अणु
		क्रम (i = 0; i < common->fsg_num_buffers; ++i) अणु
			bh = &common->buffhds[i];
			अगर (bh->state == BUF_STATE_SENDING)
				usb_ep_dequeue(common->fsg->bulk_in, bh->inreq);
			अगर (bh->state == BUF_STATE_RECEIVING)
				usb_ep_dequeue(common->fsg->bulk_out,
					       bh->outreq);

			/* Wait क्रम a transfer to become idle */
			अगर (sleep_thपढ़ो(common, false, bh))
				वापस;
		पूर्ण

		/* Clear out the controller's fअगरos */
		अगर (common->fsg->bulk_in_enabled)
			usb_ep_fअगरo_flush(common->fsg->bulk_in);
		अगर (common->fsg->bulk_out_enabled)
			usb_ep_fअगरo_flush(common->fsg->bulk_out);
	पूर्ण

	/*
	 * Reset the I/O buffer states and poपूर्णांकers, the SCSI
	 * state, and the exception.  Then invoke the handler.
	 */
	spin_lock_irq(&common->lock);

	क्रम (i = 0; i < common->fsg_num_buffers; ++i) अणु
		bh = &common->buffhds[i];
		bh->state = BUF_STATE_EMPTY;
	पूर्ण
	common->next_buffhd_to_fill = &common->buffhds[0];
	common->next_buffhd_to_drain = &common->buffhds[0];
	exception_req_tag = common->exception_req_tag;
	new_fsg = common->exception_arg;
	old_state = common->state;
	common->state = FSG_STATE_NORMAL;

	अगर (old_state != FSG_STATE_ABORT_BULK_OUT) अणु
		क्रम (i = 0; i < ARRAY_SIZE(common->luns); ++i) अणु
			curlun = common->luns[i];
			अगर (!curlun)
				जारी;
			curlun->prevent_medium_removal = 0;
			curlun->sense_data = SS_NO_SENSE;
			curlun->unit_attention_data = SS_NO_SENSE;
			curlun->sense_data_info = 0;
			curlun->info_valid = 0;
		पूर्ण
	पूर्ण
	spin_unlock_irq(&common->lock);

	/* Carry out any extra actions required क्रम the exception */
	चयन (old_state) अणु
	हाल FSG_STATE_NORMAL:
		अवरोध;

	हाल FSG_STATE_ABORT_BULK_OUT:
		send_status(common);
		अवरोध;

	हाल FSG_STATE_PROTOCOL_RESET:
		/*
		 * In हाल we were क्रमced against our will to halt a
		 * bulk endpoपूर्णांक, clear the halt now.  (The SuperH UDC
		 * requires this.)
		 */
		अगर (!fsg_is_set(common))
			अवरोध;
		अगर (test_and_clear_bit(IGNORE_BULK_OUT,
				       &common->fsg->atomic_bitflags))
			usb_ep_clear_halt(common->fsg->bulk_in);

		अगर (common->ep0_req_tag == exception_req_tag)
			ep0_queue(common);	/* Complete the status stage */

		/*
		 * Technically this should go here, but it would only be
		 * a waste of समय.  Ditto क्रम the INTERFACE_CHANGE and
		 * CONFIG_CHANGE हालs.
		 */
		/* क्रम (i = 0; i < common->ARRAY_SIZE(common->luns); ++i) */
		/*	अगर (common->luns[i]) */
		/*		common->luns[i]->unit_attention_data = */
		/*			SS_RESET_OCCURRED;  */
		अवरोध;

	हाल FSG_STATE_CONFIG_CHANGE:
		करो_set_पूर्णांकerface(common, new_fsg);
		अगर (new_fsg)
			usb_composite_setup_जारी(common->cdev);
		अवरोध;

	हाल FSG_STATE_EXIT:
		करो_set_पूर्णांकerface(common, शून्य);		/* Free resources */
		spin_lock_irq(&common->lock);
		common->state = FSG_STATE_TERMINATED;	/* Stop the thपढ़ो */
		spin_unlock_irq(&common->lock);
		अवरोध;

	हाल FSG_STATE_TERMINATED:
		अवरोध;
	पूर्ण
पूर्ण


/*-------------------------------------------------------------------------*/

अटल पूर्णांक fsg_मुख्य_thपढ़ो(व्योम *common_)
अणु
	काष्ठा fsg_common	*common = common_;
	पूर्णांक			i;

	/*
	 * Allow the thपढ़ो to be समाप्तed by a संकेत, but set the संकेत mask
	 * to block everything but INT, TERM, KILL, and USR1.
	 */
	allow_संकेत(संक_विघ्न);
	allow_संकेत(संक_इति);
	allow_संकेत(SIGKILL);
	allow_संकेत(SIGUSR1);

	/* Allow the thपढ़ो to be frozen */
	set_मुक्तzable();

	/* The मुख्य loop */
	जबतक (common->state != FSG_STATE_TERMINATED) अणु
		अगर (exception_in_progress(common) || संकेत_pending(current)) अणु
			handle_exception(common);
			जारी;
		पूर्ण

		अगर (!common->running) अणु
			sleep_thपढ़ो(common, true, शून्य);
			जारी;
		पूर्ण

		अगर (get_next_command(common) || exception_in_progress(common))
			जारी;
		अगर (करो_scsi_command(common) || exception_in_progress(common))
			जारी;
		अगर (finish_reply(common) || exception_in_progress(common))
			जारी;
		send_status(common);
	पूर्ण

	spin_lock_irq(&common->lock);
	common->thपढ़ो_task = शून्य;
	spin_unlock_irq(&common->lock);

	/* Eject media from all LUNs */

	करोwn_ग_लिखो(&common->filesem);
	क्रम (i = 0; i < ARRAY_SIZE(common->luns); i++) अणु
		काष्ठा fsg_lun *curlun = common->luns[i];

		अगर (curlun && fsg_lun_is_खोलो(curlun))
			fsg_lun_बंद(curlun);
	पूर्ण
	up_ग_लिखो(&common->filesem);

	/* Let fsg_unbind() know the thपढ़ो has निकासed */
	complete_and_निकास(&common->thपढ़ो_notअगरier, 0);
पूर्ण


/*************************** DEVICE ATTRIBUTES ***************************/

अटल sमाप_प्रकार ro_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fsg_lun		*curlun = fsg_lun_from_dev(dev);

	वापस fsg_show_ro(curlun, buf);
पूर्ण

अटल sमाप_प्रकार nofua_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा fsg_lun		*curlun = fsg_lun_from_dev(dev);

	वापस fsg_show_nofua(curlun, buf);
पूर्ण

अटल sमाप_प्रकार file_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा fsg_lun		*curlun = fsg_lun_from_dev(dev);
	काष्ठा rw_semaphore	*filesem = dev_get_drvdata(dev);

	वापस fsg_show_file(curlun, filesem, buf);
पूर्ण

अटल sमाप_प्रकार ro_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fsg_lun		*curlun = fsg_lun_from_dev(dev);
	काष्ठा rw_semaphore	*filesem = dev_get_drvdata(dev);

	वापस fsg_store_ro(curlun, filesem, buf, count);
पूर्ण

अटल sमाप_प्रकार nofua_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fsg_lun		*curlun = fsg_lun_from_dev(dev);

	वापस fsg_store_nofua(curlun, buf, count);
पूर्ण

अटल sमाप_प्रकार file_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fsg_lun		*curlun = fsg_lun_from_dev(dev);
	काष्ठा rw_semaphore	*filesem = dev_get_drvdata(dev);

	वापस fsg_store_file(curlun, filesem, buf, count);
पूर्ण

अटल DEVICE_ATTR_RW(nofua);
/* mode wil be set in fsg_lun_attr_is_visible() */
अटल DEVICE_ATTR(ro, 0, ro_show, ro_store);
अटल DEVICE_ATTR(file, 0, file_show, file_store);

/****************************** FSG COMMON ******************************/

अटल व्योम fsg_lun_release(काष्ठा device *dev)
अणु
	/* Nothing needs to be करोne */
पूर्ण

अटल काष्ठा fsg_common *fsg_common_setup(काष्ठा fsg_common *common)
अणु
	अगर (!common) अणु
		common = kzalloc(माप(*common), GFP_KERNEL);
		अगर (!common)
			वापस ERR_PTR(-ENOMEM);
		common->मुक्त_storage_on_release = 1;
	पूर्ण अन्यथा अणु
		common->मुक्त_storage_on_release = 0;
	पूर्ण
	init_rwsem(&common->filesem);
	spin_lock_init(&common->lock);
	init_completion(&common->thपढ़ो_notअगरier);
	init_रुकोqueue_head(&common->io_रुको);
	init_रुकोqueue_head(&common->fsg_रुको);
	common->state = FSG_STATE_TERMINATED;
	स_रखो(common->luns, 0, माप(common->luns));

	वापस common;
पूर्ण

व्योम fsg_common_set_sysfs(काष्ठा fsg_common *common, bool sysfs)
अणु
	common->sysfs = sysfs;
पूर्ण
EXPORT_SYMBOL_GPL(fsg_common_set_sysfs);

अटल व्योम _fsg_common_मुक्त_buffers(काष्ठा fsg_buffhd *buffhds, अचिन्हित n)
अणु
	अगर (buffhds) अणु
		काष्ठा fsg_buffhd *bh = buffhds;
		जबतक (n--) अणु
			kमुक्त(bh->buf);
			++bh;
		पूर्ण
		kमुक्त(buffhds);
	पूर्ण
पूर्ण

पूर्णांक fsg_common_set_num_buffers(काष्ठा fsg_common *common, अचिन्हित पूर्णांक n)
अणु
	काष्ठा fsg_buffhd *bh, *buffhds;
	पूर्णांक i;

	buffhds = kसुस्मृति(n, माप(*buffhds), GFP_KERNEL);
	अगर (!buffhds)
		वापस -ENOMEM;

	/* Data buffers cyclic list */
	bh = buffhds;
	i = n;
	जाओ buffhds_first_it;
	करो अणु
		bh->next = bh + 1;
		++bh;
buffhds_first_it:
		bh->buf = kदो_स्मृति(FSG_BUFLEN, GFP_KERNEL);
		अगर (unlikely(!bh->buf))
			जाओ error_release;
	पूर्ण जबतक (--i);
	bh->next = buffhds;

	_fsg_common_मुक्त_buffers(common->buffhds, common->fsg_num_buffers);
	common->fsg_num_buffers = n;
	common->buffhds = buffhds;

	वापस 0;

error_release:
	/*
	 * "buf"s poपूर्णांकed to by heads after n - i are शून्य
	 * so releasing them won't hurt
	 */
	_fsg_common_मुक्त_buffers(buffhds, n);

	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL_GPL(fsg_common_set_num_buffers);

व्योम fsg_common_हटाओ_lun(काष्ठा fsg_lun *lun)
अणु
	अगर (device_is_रेजिस्टरed(&lun->dev))
		device_unरेजिस्टर(&lun->dev);
	fsg_lun_बंद(lun);
	kमुक्त(lun);
पूर्ण
EXPORT_SYMBOL_GPL(fsg_common_हटाओ_lun);

अटल व्योम _fsg_common_हटाओ_luns(काष्ठा fsg_common *common, पूर्णांक n)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < n; ++i)
		अगर (common->luns[i]) अणु
			fsg_common_हटाओ_lun(common->luns[i]);
			common->luns[i] = शून्य;
		पूर्ण
पूर्ण

व्योम fsg_common_हटाओ_luns(काष्ठा fsg_common *common)
अणु
	_fsg_common_हटाओ_luns(common, ARRAY_SIZE(common->luns));
पूर्ण
EXPORT_SYMBOL_GPL(fsg_common_हटाओ_luns);

व्योम fsg_common_मुक्त_buffers(काष्ठा fsg_common *common)
अणु
	_fsg_common_मुक्त_buffers(common->buffhds, common->fsg_num_buffers);
	common->buffhds = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(fsg_common_मुक्त_buffers);

पूर्णांक fsg_common_set_cdev(काष्ठा fsg_common *common,
			 काष्ठा usb_composite_dev *cdev, bool can_stall)
अणु
	काष्ठा usb_string *us;

	common->gadget = cdev->gadget;
	common->ep0 = cdev->gadget->ep0;
	common->ep0req = cdev->req;
	common->cdev = cdev;

	us = usb_gstrings_attach(cdev, fsg_strings_array,
				 ARRAY_SIZE(fsg_strings));
	अगर (IS_ERR(us))
		वापस PTR_ERR(us);

	fsg_पूर्णांकf_desc.iInterface = us[FSG_STRING_INTERFACE].id;

	/*
	 * Some peripheral controllers are known not to be able to
	 * halt bulk endpoपूर्णांकs correctly.  If one of them is present,
	 * disable stalls.
	 */
	common->can_stall = can_stall &&
			gadget_is_stall_supported(common->gadget);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(fsg_common_set_cdev);

अटल काष्ठा attribute *fsg_lun_dev_attrs[] = अणु
	&dev_attr_ro.attr,
	&dev_attr_file.attr,
	&dev_attr_nofua.attr,
	शून्य
पूर्ण;

अटल umode_t fsg_lun_dev_is_visible(काष्ठा kobject *kobj,
				      काष्ठा attribute *attr, पूर्णांक idx)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा fsg_lun *lun = fsg_lun_from_dev(dev);

	अगर (attr == &dev_attr_ro.attr)
		वापस lun->cdrom ? S_IRUGO : (S_IWUSR | S_IRUGO);
	अगर (attr == &dev_attr_file.attr)
		वापस lun->removable ? (S_IWUSR | S_IRUGO) : S_IRUGO;
	वापस attr->mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group fsg_lun_dev_group = अणु
	.attrs = fsg_lun_dev_attrs,
	.is_visible = fsg_lun_dev_is_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *fsg_lun_dev_groups[] = अणु
	&fsg_lun_dev_group,
	शून्य
पूर्ण;

पूर्णांक fsg_common_create_lun(काष्ठा fsg_common *common, काष्ठा fsg_lun_config *cfg,
			  अचिन्हित पूर्णांक id, स्थिर अक्षर *name,
			  स्थिर अक्षर **name_pfx)
अणु
	काष्ठा fsg_lun *lun;
	अक्षर *pathbuf, *p;
	पूर्णांक rc = -ENOMEM;

	अगर (id >= ARRAY_SIZE(common->luns))
		वापस -ENODEV;

	अगर (common->luns[id])
		वापस -EBUSY;

	अगर (!cfg->filename && !cfg->removable) अणु
		pr_err("no file given for LUN%d\n", id);
		वापस -EINVAL;
	पूर्ण

	lun = kzalloc(माप(*lun), GFP_KERNEL);
	अगर (!lun)
		वापस -ENOMEM;

	lun->name_pfx = name_pfx;

	lun->cdrom = !!cfg->cdrom;
	lun->ro = cfg->cdrom || cfg->ro;
	lun->initially_ro = lun->ro;
	lun->removable = !!cfg->removable;

	अगर (!common->sysfs) अणु
		/* we DON'T own the name!*/
		lun->name = name;
	पूर्ण अन्यथा अणु
		lun->dev.release = fsg_lun_release;
		lun->dev.parent = &common->gadget->dev;
		lun->dev.groups = fsg_lun_dev_groups;
		dev_set_drvdata(&lun->dev, &common->filesem);
		dev_set_name(&lun->dev, "%s", name);
		lun->name = dev_name(&lun->dev);

		rc = device_रेजिस्टर(&lun->dev);
		अगर (rc) अणु
			pr_info("failed to register LUN%d: %d\n", id, rc);
			put_device(&lun->dev);
			जाओ error_sysfs;
		पूर्ण
	पूर्ण

	common->luns[id] = lun;

	अगर (cfg->filename) अणु
		rc = fsg_lun_खोलो(lun, cfg->filename);
		अगर (rc)
			जाओ error_lun;
	पूर्ण

	pathbuf = kदो_स्मृति(PATH_MAX, GFP_KERNEL);
	p = "(no medium)";
	अगर (fsg_lun_is_खोलो(lun)) अणु
		p = "(error)";
		अगर (pathbuf) अणु
			p = file_path(lun->filp, pathbuf, PATH_MAX);
			अगर (IS_ERR(p))
				p = "(error)";
		पूर्ण
	पूर्ण
	pr_info("LUN: %s%s%sfile: %s\n",
	      lun->removable ? "removable " : "",
	      lun->ro ? "read only " : "",
	      lun->cdrom ? "CD-ROM " : "",
	      p);
	kमुक्त(pathbuf);

	वापस 0;

error_lun:
	अगर (device_is_रेजिस्टरed(&lun->dev))
		device_unरेजिस्टर(&lun->dev);
	fsg_lun_बंद(lun);
	common->luns[id] = शून्य;
error_sysfs:
	kमुक्त(lun);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(fsg_common_create_lun);

पूर्णांक fsg_common_create_luns(काष्ठा fsg_common *common, काष्ठा fsg_config *cfg)
अणु
	अक्षर buf[8]; /* enough क्रम 100000000 dअगरferent numbers, decimal */
	पूर्णांक i, rc;

	fsg_common_हटाओ_luns(common);

	क्रम (i = 0; i < cfg->nluns; ++i) अणु
		snम_लिखो(buf, माप(buf), "lun%d", i);
		rc = fsg_common_create_lun(common, &cfg->luns[i], i, buf, शून्य);
		अगर (rc)
			जाओ fail;
	पूर्ण

	pr_info("Number of LUNs=%d\n", cfg->nluns);

	वापस 0;

fail:
	_fsg_common_हटाओ_luns(common, i);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(fsg_common_create_luns);

व्योम fsg_common_set_inquiry_string(काष्ठा fsg_common *common, स्थिर अक्षर *vn,
				   स्थिर अक्षर *pn)
अणु
	पूर्णांक i;

	/* Prepare inquiryString */
	i = get_शेष_bcdDevice();
	snम_लिखो(common->inquiry_string, माप(common->inquiry_string),
		 "%-8s%-16s%04x", vn ?: "Linux",
		 /* Assume product name dependent on the first LUN */
		 pn ?: ((*common->luns)->cdrom
		     ? "File-CD Gadget"
		     : "File-Stor Gadget"),
		 i);
पूर्ण
EXPORT_SYMBOL_GPL(fsg_common_set_inquiry_string);

अटल व्योम fsg_common_release(काष्ठा fsg_common *common)
अणु
	पूर्णांक i;

	/* If the thपढ़ो isn't alपढ़ोy dead, tell it to निकास now */
	अगर (common->state != FSG_STATE_TERMINATED) अणु
		उठाओ_exception(common, FSG_STATE_EXIT);
		रुको_क्रम_completion(&common->thपढ़ो_notअगरier);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(common->luns); ++i) अणु
		काष्ठा fsg_lun *lun = common->luns[i];
		अगर (!lun)
			जारी;
		fsg_lun_बंद(lun);
		अगर (device_is_रेजिस्टरed(&lun->dev))
			device_unरेजिस्टर(&lun->dev);
		kमुक्त(lun);
	पूर्ण

	_fsg_common_मुक्त_buffers(common->buffhds, common->fsg_num_buffers);
	अगर (common->मुक्त_storage_on_release)
		kमुक्त(common);
पूर्ण


/*-------------------------------------------------------------------------*/

अटल पूर्णांक fsg_bind(काष्ठा usb_configuration *c, काष्ठा usb_function *f)
अणु
	काष्ठा fsg_dev		*fsg = fsg_from_func(f);
	काष्ठा fsg_common	*common = fsg->common;
	काष्ठा usb_gadget	*gadget = c->cdev->gadget;
	पूर्णांक			i;
	काष्ठा usb_ep		*ep;
	अचिन्हित		max_burst;
	पूर्णांक			ret;
	काष्ठा fsg_opts		*opts;

	/* Don't allow to bind if we don't have at least one LUN */
	ret = _fsg_common_get_max_lun(common);
	अगर (ret < 0) अणु
		pr_err("There should be at least one LUN.\n");
		वापस -EINVAL;
	पूर्ण

	opts = fsg_opts_from_func_inst(f->fi);
	अगर (!opts->no_configfs) अणु
		ret = fsg_common_set_cdev(fsg->common, c->cdev,
					  fsg->common->can_stall);
		अगर (ret)
			वापस ret;
		fsg_common_set_inquiry_string(fsg->common, शून्य, शून्य);
	पूर्ण

	अगर (!common->thपढ़ो_task) अणु
		common->state = FSG_STATE_NORMAL;
		common->thपढ़ो_task =
			kthपढ़ो_create(fsg_मुख्य_thपढ़ो, common, "file-storage");
		अगर (IS_ERR(common->thपढ़ो_task)) अणु
			ret = PTR_ERR(common->thपढ़ो_task);
			common->thपढ़ो_task = शून्य;
			common->state = FSG_STATE_TERMINATED;
			वापस ret;
		पूर्ण
		DBG(common, "I/O thread pid: %d\n",
		    task_pid_nr(common->thपढ़ो_task));
		wake_up_process(common->thपढ़ो_task);
	पूर्ण

	fsg->gadget = gadget;

	/* New पूर्णांकerface */
	i = usb_पूर्णांकerface_id(c, f);
	अगर (i < 0)
		जाओ fail;
	fsg_पूर्णांकf_desc.bInterfaceNumber = i;
	fsg->पूर्णांकerface_number = i;

	/* Find all the endpoपूर्णांकs we will use */
	ep = usb_ep_स्वतःconfig(gadget, &fsg_fs_bulk_in_desc);
	अगर (!ep)
		जाओ स्वतःconf_fail;
	fsg->bulk_in = ep;

	ep = usb_ep_स्वतःconfig(gadget, &fsg_fs_bulk_out_desc);
	अगर (!ep)
		जाओ स्वतःconf_fail;
	fsg->bulk_out = ep;

	/* Assume endpoपूर्णांक addresses are the same क्रम both speeds */
	fsg_hs_bulk_in_desc.bEndpoपूर्णांकAddress =
		fsg_fs_bulk_in_desc.bEndpoपूर्णांकAddress;
	fsg_hs_bulk_out_desc.bEndpoपूर्णांकAddress =
		fsg_fs_bulk_out_desc.bEndpoपूर्णांकAddress;

	/* Calculate bMaxBurst, we know packet size is 1024 */
	max_burst = min_t(अचिन्हित, FSG_BUFLEN / 1024, 15);

	fsg_ss_bulk_in_desc.bEndpoपूर्णांकAddress =
		fsg_fs_bulk_in_desc.bEndpoपूर्णांकAddress;
	fsg_ss_bulk_in_comp_desc.bMaxBurst = max_burst;

	fsg_ss_bulk_out_desc.bEndpoपूर्णांकAddress =
		fsg_fs_bulk_out_desc.bEndpoपूर्णांकAddress;
	fsg_ss_bulk_out_comp_desc.bMaxBurst = max_burst;

	ret = usb_assign_descriptors(f, fsg_fs_function, fsg_hs_function,
			fsg_ss_function, fsg_ss_function);
	अगर (ret)
		जाओ स्वतःconf_fail;

	वापस 0;

स्वतःconf_fail:
	ERROR(fsg, "unable to autoconfigure all endpoints\n");
	i = -ENOTSUPP;
fail:
	/* terminate the thपढ़ो */
	अगर (fsg->common->state != FSG_STATE_TERMINATED) अणु
		उठाओ_exception(fsg->common, FSG_STATE_EXIT);
		रुको_क्रम_completion(&fsg->common->thपढ़ो_notअगरier);
	पूर्ण
	वापस i;
पूर्ण

/****************************** ALLOCATE FUNCTION *************************/

अटल व्योम fsg_unbind(काष्ठा usb_configuration *c, काष्ठा usb_function *f)
अणु
	काष्ठा fsg_dev		*fsg = fsg_from_func(f);
	काष्ठा fsg_common	*common = fsg->common;

	DBG(fsg, "unbind\n");
	अगर (fsg->common->fsg == fsg) अणु
		__उठाओ_exception(fsg->common, FSG_STATE_CONFIG_CHANGE, शून्य);
		/* FIXME: make पूर्णांकerruptible or समाप्तable somehow? */
		रुको_event(common->fsg_रुको, common->fsg != fsg);
	पूर्ण

	usb_मुक्त_all_descriptors(&fsg->function);
पूर्ण

अटल अंतरभूत काष्ठा fsg_lun_opts *to_fsg_lun_opts(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा fsg_lun_opts, group);
पूर्ण

अटल अंतरभूत काष्ठा fsg_opts *to_fsg_opts(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा fsg_opts,
			    func_inst.group);
पूर्ण

अटल व्योम fsg_lun_attr_release(काष्ठा config_item *item)
अणु
	काष्ठा fsg_lun_opts *lun_opts;

	lun_opts = to_fsg_lun_opts(item);
	kमुक्त(lun_opts);
पूर्ण

अटल काष्ठा configfs_item_operations fsg_lun_item_ops = अणु
	.release		= fsg_lun_attr_release,
पूर्ण;

अटल sमाप_प्रकार fsg_lun_opts_file_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा fsg_lun_opts *opts = to_fsg_lun_opts(item);
	काष्ठा fsg_opts *fsg_opts = to_fsg_opts(opts->group.cg_item.ci_parent);

	वापस fsg_show_file(opts->lun, &fsg_opts->common->filesem, page);
पूर्ण

अटल sमाप_प्रकार fsg_lun_opts_file_store(काष्ठा config_item *item,
				       स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा fsg_lun_opts *opts = to_fsg_lun_opts(item);
	काष्ठा fsg_opts *fsg_opts = to_fsg_opts(opts->group.cg_item.ci_parent);

	वापस fsg_store_file(opts->lun, &fsg_opts->common->filesem, page, len);
पूर्ण

CONFIGFS_ATTR(fsg_lun_opts_, file);

अटल sमाप_प्रकार fsg_lun_opts_ro_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस fsg_show_ro(to_fsg_lun_opts(item)->lun, page);
पूर्ण

अटल sमाप_प्रकार fsg_lun_opts_ro_store(काष्ठा config_item *item,
				       स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा fsg_lun_opts *opts = to_fsg_lun_opts(item);
	काष्ठा fsg_opts *fsg_opts = to_fsg_opts(opts->group.cg_item.ci_parent);

	वापस fsg_store_ro(opts->lun, &fsg_opts->common->filesem, page, len);
पूर्ण

CONFIGFS_ATTR(fsg_lun_opts_, ro);

अटल sमाप_प्रकार fsg_lun_opts_removable_show(काष्ठा config_item *item,
					   अक्षर *page)
अणु
	वापस fsg_show_removable(to_fsg_lun_opts(item)->lun, page);
पूर्ण

अटल sमाप_प्रकार fsg_lun_opts_removable_store(काष्ठा config_item *item,
				       स्थिर अक्षर *page, माप_प्रकार len)
अणु
	वापस fsg_store_removable(to_fsg_lun_opts(item)->lun, page, len);
पूर्ण

CONFIGFS_ATTR(fsg_lun_opts_, removable);

अटल sमाप_प्रकार fsg_lun_opts_cdrom_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस fsg_show_cdrom(to_fsg_lun_opts(item)->lun, page);
पूर्ण

अटल sमाप_प्रकार fsg_lun_opts_cdrom_store(काष्ठा config_item *item,
				       स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा fsg_lun_opts *opts = to_fsg_lun_opts(item);
	काष्ठा fsg_opts *fsg_opts = to_fsg_opts(opts->group.cg_item.ci_parent);

	वापस fsg_store_cdrom(opts->lun, &fsg_opts->common->filesem, page,
			       len);
पूर्ण

CONFIGFS_ATTR(fsg_lun_opts_, cdrom);

अटल sमाप_प्रकार fsg_lun_opts_nofua_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस fsg_show_nofua(to_fsg_lun_opts(item)->lun, page);
पूर्ण

अटल sमाप_प्रकार fsg_lun_opts_nofua_store(काष्ठा config_item *item,
				       स्थिर अक्षर *page, माप_प्रकार len)
अणु
	वापस fsg_store_nofua(to_fsg_lun_opts(item)->lun, page, len);
पूर्ण

CONFIGFS_ATTR(fsg_lun_opts_, nofua);

अटल sमाप_प्रकार fsg_lun_opts_inquiry_string_show(काष्ठा config_item *item,
						अक्षर *page)
अणु
	वापस fsg_show_inquiry_string(to_fsg_lun_opts(item)->lun, page);
पूर्ण

अटल sमाप_प्रकार fsg_lun_opts_inquiry_string_store(काष्ठा config_item *item,
						 स्थिर अक्षर *page, माप_प्रकार len)
अणु
	वापस fsg_store_inquiry_string(to_fsg_lun_opts(item)->lun, page, len);
पूर्ण

CONFIGFS_ATTR(fsg_lun_opts_, inquiry_string);

अटल काष्ठा configfs_attribute *fsg_lun_attrs[] = अणु
	&fsg_lun_opts_attr_file,
	&fsg_lun_opts_attr_ro,
	&fsg_lun_opts_attr_removable,
	&fsg_lun_opts_attr_cdrom,
	&fsg_lun_opts_attr_nofua,
	&fsg_lun_opts_attr_inquiry_string,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा config_item_type fsg_lun_type = अणु
	.ct_item_ops	= &fsg_lun_item_ops,
	.ct_attrs	= fsg_lun_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल काष्ठा config_group *fsg_lun_make(काष्ठा config_group *group,
					 स्थिर अक्षर *name)
अणु
	काष्ठा fsg_lun_opts *opts;
	काष्ठा fsg_opts *fsg_opts;
	काष्ठा fsg_lun_config config;
	अक्षर *num_str;
	u8 num;
	पूर्णांक ret;

	num_str = म_अक्षर(name, '.');
	अगर (!num_str) अणु
		pr_err("Unable to locate . in LUN.NUMBER\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	num_str++;

	ret = kstrtou8(num_str, 0, &num);
	अगर (ret)
		वापस ERR_PTR(ret);

	fsg_opts = to_fsg_opts(&group->cg_item);
	अगर (num >= FSG_MAX_LUNS)
		वापस ERR_PTR(-दुस्फल);
	num = array_index_nospec(num, FSG_MAX_LUNS);

	mutex_lock(&fsg_opts->lock);
	अगर (fsg_opts->refcnt || fsg_opts->common->luns[num]) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	opts = kzalloc(माप(*opts), GFP_KERNEL);
	अगर (!opts) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	स_रखो(&config, 0, माप(config));
	config.removable = true;

	ret = fsg_common_create_lun(fsg_opts->common, &config, num, name,
				    (स्थिर अक्षर **)&group->cg_item.ci_name);
	अगर (ret) अणु
		kमुक्त(opts);
		जाओ out;
	पूर्ण
	opts->lun = fsg_opts->common->luns[num];
	opts->lun_id = num;
	mutex_unlock(&fsg_opts->lock);

	config_group_init_type_name(&opts->group, name, &fsg_lun_type);

	वापस &opts->group;
out:
	mutex_unlock(&fsg_opts->lock);
	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम fsg_lun_drop(काष्ठा config_group *group, काष्ठा config_item *item)
अणु
	काष्ठा fsg_lun_opts *lun_opts;
	काष्ठा fsg_opts *fsg_opts;

	lun_opts = to_fsg_lun_opts(item);
	fsg_opts = to_fsg_opts(&group->cg_item);

	mutex_lock(&fsg_opts->lock);
	अगर (fsg_opts->refcnt) अणु
		काष्ठा config_item *gadget;

		gadget = group->cg_item.ci_parent->ci_parent;
		unरेजिस्टर_gadget_item(gadget);
	पूर्ण

	fsg_common_हटाओ_lun(lun_opts->lun);
	fsg_opts->common->luns[lun_opts->lun_id] = शून्य;
	lun_opts->lun_id = 0;
	mutex_unlock(&fsg_opts->lock);

	config_item_put(item);
पूर्ण

अटल व्योम fsg_attr_release(काष्ठा config_item *item)
अणु
	काष्ठा fsg_opts *opts = to_fsg_opts(item);

	usb_put_function_instance(&opts->func_inst);
पूर्ण

अटल काष्ठा configfs_item_operations fsg_item_ops = अणु
	.release		= fsg_attr_release,
पूर्ण;

अटल sमाप_प्रकार fsg_opts_stall_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा fsg_opts *opts = to_fsg_opts(item);
	पूर्णांक result;

	mutex_lock(&opts->lock);
	result = प्र_लिखो(page, "%d", opts->common->can_stall);
	mutex_unlock(&opts->lock);

	वापस result;
पूर्ण

अटल sमाप_प्रकार fsg_opts_stall_store(काष्ठा config_item *item, स्थिर अक्षर *page,
				    माप_प्रकार len)
अणु
	काष्ठा fsg_opts *opts = to_fsg_opts(item);
	पूर्णांक ret;
	bool stall;

	mutex_lock(&opts->lock);

	अगर (opts->refcnt) अणु
		mutex_unlock(&opts->lock);
		वापस -EBUSY;
	पूर्ण

	ret = strtobool(page, &stall);
	अगर (!ret) अणु
		opts->common->can_stall = stall;
		ret = len;
	पूर्ण

	mutex_unlock(&opts->lock);

	वापस ret;
पूर्ण

CONFIGFS_ATTR(fsg_opts_, stall);

#अगर_घोषित CONFIG_USB_GADGET_DEBUG_खाताS
अटल sमाप_प्रकार fsg_opts_num_buffers_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा fsg_opts *opts = to_fsg_opts(item);
	पूर्णांक result;

	mutex_lock(&opts->lock);
	result = प्र_लिखो(page, "%d", opts->common->fsg_num_buffers);
	mutex_unlock(&opts->lock);

	वापस result;
पूर्ण

अटल sमाप_प्रकार fsg_opts_num_buffers_store(काष्ठा config_item *item,
					  स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा fsg_opts *opts = to_fsg_opts(item);
	पूर्णांक ret;
	u8 num;

	mutex_lock(&opts->lock);
	अगर (opts->refcnt) अणु
		ret = -EBUSY;
		जाओ end;
	पूर्ण
	ret = kstrtou8(page, 0, &num);
	अगर (ret)
		जाओ end;

	ret = fsg_common_set_num_buffers(opts->common, num);
	अगर (ret)
		जाओ end;
	ret = len;

end:
	mutex_unlock(&opts->lock);
	वापस ret;
पूर्ण

CONFIGFS_ATTR(fsg_opts_, num_buffers);
#पूर्ण_अगर

अटल काष्ठा configfs_attribute *fsg_attrs[] = अणु
	&fsg_opts_attr_stall,
#अगर_घोषित CONFIG_USB_GADGET_DEBUG_खाताS
	&fsg_opts_attr_num_buffers,
#पूर्ण_अगर
	शून्य,
पूर्ण;

अटल काष्ठा configfs_group_operations fsg_group_ops = अणु
	.make_group	= fsg_lun_make,
	.drop_item	= fsg_lun_drop,
पूर्ण;

अटल स्थिर काष्ठा config_item_type fsg_func_type = अणु
	.ct_item_ops	= &fsg_item_ops,
	.ct_group_ops	= &fsg_group_ops,
	.ct_attrs	= fsg_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल व्योम fsg_मुक्त_inst(काष्ठा usb_function_instance *fi)
अणु
	काष्ठा fsg_opts *opts;

	opts = fsg_opts_from_func_inst(fi);
	fsg_common_release(opts->common);
	kमुक्त(opts);
पूर्ण

अटल काष्ठा usb_function_instance *fsg_alloc_inst(व्योम)
अणु
	काष्ठा fsg_opts *opts;
	काष्ठा fsg_lun_config config;
	पूर्णांक rc;

	opts = kzalloc(माप(*opts), GFP_KERNEL);
	अगर (!opts)
		वापस ERR_PTR(-ENOMEM);
	mutex_init(&opts->lock);
	opts->func_inst.मुक्त_func_inst = fsg_मुक्त_inst;
	opts->common = fsg_common_setup(opts->common);
	अगर (IS_ERR(opts->common)) अणु
		rc = PTR_ERR(opts->common);
		जाओ release_opts;
	पूर्ण

	rc = fsg_common_set_num_buffers(opts->common,
					CONFIG_USB_GADGET_STORAGE_NUM_BUFFERS);
	अगर (rc)
		जाओ release_common;

	pr_info(FSG_DRIVER_DESC ", version: " FSG_DRIVER_VERSION "\n");

	स_रखो(&config, 0, माप(config));
	config.removable = true;
	rc = fsg_common_create_lun(opts->common, &config, 0, "lun.0",
			(स्थिर अक्षर **)&opts->func_inst.group.cg_item.ci_name);
	अगर (rc)
		जाओ release_buffers;

	opts->lun0.lun = opts->common->luns[0];
	opts->lun0.lun_id = 0;

	config_group_init_type_name(&opts->func_inst.group, "", &fsg_func_type);

	config_group_init_type_name(&opts->lun0.group, "lun.0", &fsg_lun_type);
	configfs_add_शेष_group(&opts->lun0.group, &opts->func_inst.group);

	वापस &opts->func_inst;

release_buffers:
	fsg_common_मुक्त_buffers(opts->common);
release_common:
	kमुक्त(opts->common);
release_opts:
	kमुक्त(opts);
	वापस ERR_PTR(rc);
पूर्ण

अटल व्योम fsg_मुक्त(काष्ठा usb_function *f)
अणु
	काष्ठा fsg_dev *fsg;
	काष्ठा fsg_opts *opts;

	fsg = container_of(f, काष्ठा fsg_dev, function);
	opts = container_of(f->fi, काष्ठा fsg_opts, func_inst);

	mutex_lock(&opts->lock);
	opts->refcnt--;
	mutex_unlock(&opts->lock);

	kमुक्त(fsg);
पूर्ण

अटल काष्ठा usb_function *fsg_alloc(काष्ठा usb_function_instance *fi)
अणु
	काष्ठा fsg_opts *opts = fsg_opts_from_func_inst(fi);
	काष्ठा fsg_common *common = opts->common;
	काष्ठा fsg_dev *fsg;

	fsg = kzalloc(माप(*fsg), GFP_KERNEL);
	अगर (unlikely(!fsg))
		वापस ERR_PTR(-ENOMEM);

	mutex_lock(&opts->lock);
	opts->refcnt++;
	mutex_unlock(&opts->lock);

	fsg->function.name	= FSG_DRIVER_DESC;
	fsg->function.bind	= fsg_bind;
	fsg->function.unbind	= fsg_unbind;
	fsg->function.setup	= fsg_setup;
	fsg->function.set_alt	= fsg_set_alt;
	fsg->function.disable	= fsg_disable;
	fsg->function.मुक्त_func	= fsg_मुक्त;

	fsg->common               = common;

	वापस &fsg->function;
पूर्ण

DECLARE_USB_FUNCTION_INIT(mass_storage, fsg_alloc_inst, fsg_alloc);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Michal Nazarewicz");

/************************* Module parameters *************************/


व्योम fsg_config_from_params(काष्ठा fsg_config *cfg,
		       स्थिर काष्ठा fsg_module_parameters *params,
		       अचिन्हित पूर्णांक fsg_num_buffers)
अणु
	काष्ठा fsg_lun_config *lun;
	अचिन्हित i;

	/* Configure LUNs */
	cfg->nluns =
		min(params->luns ?: (params->file_count ?: 1u),
		    (अचिन्हित)FSG_MAX_LUNS);
	क्रम (i = 0, lun = cfg->luns; i < cfg->nluns; ++i, ++lun) अणु
		lun->ro = !!params->ro[i];
		lun->cdrom = !!params->cdrom[i];
		lun->removable = !!params->removable[i];
		lun->filename =
			params->file_count > i && params->file[i][0]
			? params->file[i]
			: शून्य;
	पूर्ण

	/* Let MSF use शेषs */
	cfg->venकरोr_name = शून्य;
	cfg->product_name = शून्य;

	cfg->ops = शून्य;
	cfg->निजी_data = शून्य;

	/* Finalise */
	cfg->can_stall = params->stall;
	cfg->fsg_num_buffers = fsg_num_buffers;
पूर्ण
EXPORT_SYMBOL_GPL(fsg_config_from_params);
