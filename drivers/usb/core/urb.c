<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Released under the GPLv2 only.
 */

#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/bitops.h>
#समावेश <linux/slab.h>
#समावेश <linux/log2.h>
#समावेश <linux/usb.h>
#समावेश <linux/रुको.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/scatterlist.h>

#घोषणा to_urb(d) container_of(d, काष्ठा urb, kref)


अटल व्योम urb_destroy(काष्ठा kref *kref)
अणु
	काष्ठा urb *urb = to_urb(kref);

	अगर (urb->transfer_flags & URB_FREE_BUFFER)
		kमुक्त(urb->transfer_buffer);

	kमुक्त(urb);
पूर्ण

/**
 * usb_init_urb - initializes a urb so that it can be used by a USB driver
 * @urb: poपूर्णांकer to the urb to initialize
 *
 * Initializes a urb so that the USB subप्रणाली can use it properly.
 *
 * If a urb is created with a call to usb_alloc_urb() it is not
 * necessary to call this function.  Only use this अगर you allocate the
 * space क्रम a काष्ठा urb on your own.  If you call this function, be
 * careful when मुक्तing the memory क्रम your urb that it is no दीर्घer in
 * use by the USB core.
 *
 * Only use this function अगर you _really_ understand what you are करोing.
 */
व्योम usb_init_urb(काष्ठा urb *urb)
अणु
	अगर (urb) अणु
		स_रखो(urb, 0, माप(*urb));
		kref_init(&urb->kref);
		INIT_LIST_HEAD(&urb->urb_list);
		INIT_LIST_HEAD(&urb->anchor_list);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(usb_init_urb);

/**
 * usb_alloc_urb - creates a new urb क्रम a USB driver to use
 * @iso_packets: number of iso packets क्रम this urb
 * @mem_flags: the type of memory to allocate, see kदो_स्मृति() क्रम a list of
 *	valid options क्रम this.
 *
 * Creates an urb क्रम the USB driver to use, initializes a few पूर्णांकernal
 * काष्ठाures, increments the usage counter, and वापसs a poपूर्णांकer to it.
 *
 * If the driver want to use this urb क्रम पूर्णांकerrupt, control, or bulk
 * endpoपूर्णांकs, pass '0' as the number of iso packets.
 *
 * The driver must call usb_मुक्त_urb() when it is finished with the urb.
 *
 * Return: A poपूर्णांकer to the new urb, or %शून्य अगर no memory is available.
 */
काष्ठा urb *usb_alloc_urb(पूर्णांक iso_packets, gfp_t mem_flags)
अणु
	काष्ठा urb *urb;

	urb = kदो_स्मृति(काष्ठा_size(urb, iso_frame_desc, iso_packets),
		      mem_flags);
	अगर (!urb)
		वापस शून्य;
	usb_init_urb(urb);
	वापस urb;
पूर्ण
EXPORT_SYMBOL_GPL(usb_alloc_urb);

/**
 * usb_मुक्त_urb - मुक्तs the memory used by a urb when all users of it are finished
 * @urb: poपूर्णांकer to the urb to मुक्त, may be शून्य
 *
 * Must be called when a user of a urb is finished with it.  When the last user
 * of the urb calls this function, the memory of the urb is मुक्तd.
 *
 * Note: The transfer buffer associated with the urb is not मुक्तd unless the
 * URB_FREE_BUFFER transfer flag is set.
 */
व्योम usb_मुक्त_urb(काष्ठा urb *urb)
अणु
	अगर (urb)
		kref_put(&urb->kref, urb_destroy);
पूर्ण
EXPORT_SYMBOL_GPL(usb_मुक्त_urb);

/**
 * usb_get_urb - increments the reference count of the urb
 * @urb: poपूर्णांकer to the urb to modअगरy, may be शून्य
 *
 * This must be  called whenever a urb is transferred from a device driver to a
 * host controller driver.  This allows proper reference counting to happen
 * क्रम urbs.
 *
 * Return: A poपूर्णांकer to the urb with the incremented reference counter.
 */
काष्ठा urb *usb_get_urb(काष्ठा urb *urb)
अणु
	अगर (urb)
		kref_get(&urb->kref);
	वापस urb;
पूर्ण
EXPORT_SYMBOL_GPL(usb_get_urb);

/**
 * usb_anchor_urb - anchors an URB जबतक it is processed
 * @urb: poपूर्णांकer to the urb to anchor
 * @anchor: poपूर्णांकer to the anchor
 *
 * This can be called to have access to URBs which are to be executed
 * without bothering to track them
 */
व्योम usb_anchor_urb(काष्ठा urb *urb, काष्ठा usb_anchor *anchor)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&anchor->lock, flags);
	usb_get_urb(urb);
	list_add_tail(&urb->anchor_list, &anchor->urb_list);
	urb->anchor = anchor;

	अगर (unlikely(anchor->poisoned))
		atomic_inc(&urb->reject);

	spin_unlock_irqrestore(&anchor->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(usb_anchor_urb);

अटल पूर्णांक usb_anchor_check_wakeup(काष्ठा usb_anchor *anchor)
अणु
	वापस atomic_पढ़ो(&anchor->suspend_wakeups) == 0 &&
		list_empty(&anchor->urb_list);
पूर्ण

/* Callers must hold anchor->lock */
अटल व्योम __usb_unanchor_urb(काष्ठा urb *urb, काष्ठा usb_anchor *anchor)
अणु
	urb->anchor = शून्य;
	list_del(&urb->anchor_list);
	usb_put_urb(urb);
	अगर (usb_anchor_check_wakeup(anchor))
		wake_up(&anchor->रुको);
पूर्ण

/**
 * usb_unanchor_urb - unanchors an URB
 * @urb: poपूर्णांकer to the urb to anchor
 *
 * Call this to stop the प्रणाली keeping track of this URB
 */
व्योम usb_unanchor_urb(काष्ठा urb *urb)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा usb_anchor *anchor;

	अगर (!urb)
		वापस;

	anchor = urb->anchor;
	अगर (!anchor)
		वापस;

	spin_lock_irqsave(&anchor->lock, flags);
	/*
	 * At this poपूर्णांक, we could be competing with another thपढ़ो which
	 * has the same पूर्णांकention. To protect the urb from being unanchored
	 * twice, only the winner of the race माला_लो the job.
	 */
	अगर (likely(anchor == urb->anchor))
		__usb_unanchor_urb(urb, anchor);
	spin_unlock_irqrestore(&anchor->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(usb_unanchor_urb);

/*-------------------------------------------------------------------*/

अटल स्थिर पूर्णांक pipetypes[4] = अणु
	PIPE_CONTROL, PIPE_ISOCHRONOUS, PIPE_BULK, PIPE_INTERRUPT
पूर्ण;

/**
 * usb_pipe_type_check - sanity check of a specअगरic pipe क्रम a usb device
 * @dev: काष्ठा usb_device to be checked
 * @pipe: pipe to check
 *
 * This perक्रमms a light-weight sanity check क्रम the endpoपूर्णांक in the
 * given usb device.  It वापसs 0 अगर the pipe is valid क्रम the specअगरic usb
 * device, otherwise a negative error code.
 */
पूर्णांक usb_pipe_type_check(काष्ठा usb_device *dev, अचिन्हित पूर्णांक pipe)
अणु
	स्थिर काष्ठा usb_host_endpoपूर्णांक *ep;

	ep = usb_pipe_endpoपूर्णांक(dev, pipe);
	अगर (!ep)
		वापस -EINVAL;
	अगर (usb_pipetype(pipe) != pipetypes[usb_endpoपूर्णांक_type(&ep->desc)])
		वापस -EINVAL;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(usb_pipe_type_check);

/**
 * usb_urb_ep_type_check - sanity check of endpoपूर्णांक in the given urb
 * @urb: urb to be checked
 *
 * This perक्रमms a light-weight sanity check क्रम the endpoपूर्णांक in the
 * given urb.  It वापसs 0 अगर the urb contains a valid endpoपूर्णांक, otherwise
 * a negative error code.
 */
पूर्णांक usb_urb_ep_type_check(स्थिर काष्ठा urb *urb)
अणु
	वापस usb_pipe_type_check(urb->dev, urb->pipe);
पूर्ण
EXPORT_SYMBOL_GPL(usb_urb_ep_type_check);

/**
 * usb_submit_urb - issue an asynchronous transfer request क्रम an endpoपूर्णांक
 * @urb: poपूर्णांकer to the urb describing the request
 * @mem_flags: the type of memory to allocate, see kदो_स्मृति() क्रम a list
 *	of valid options क्रम this.
 *
 * This submits a transfer request, and transfers control of the URB
 * describing that request to the USB subप्रणाली.  Request completion will
 * be indicated later, asynchronously, by calling the completion handler.
 * The three types of completion are success, error, and unlink
 * (a software-induced fault, also called "request cancellation").
 *
 * URBs may be submitted in पूर्णांकerrupt context.
 *
 * The caller must have correctly initialized the URB beक्रमe submitting
 * it.  Functions such as usb_fill_bulk_urb() and usb_fill_control_urb() are
 * available to ensure that most fields are correctly initialized, क्रम
 * the particular kind of transfer, although they will not initialize
 * any transfer flags.
 *
 * If the submission is successful, the complete() callback from the URB
 * will be called exactly once, when the USB core and Host Controller Driver
 * (HCD) are finished with the URB.  When the completion function is called,
 * control of the URB is वापसed to the device driver which issued the
 * request.  The completion handler may then immediately मुक्त or reuse that
 * URB.
 *
 * With few exceptions, USB device drivers should never access URB fields
 * provided by usbcore or the HCD until its complete() is called.
 * The exceptions relate to periodic transfer scheduling.  For both
 * पूर्णांकerrupt and isochronous urbs, as part of successful URB submission
 * urb->पूर्णांकerval is modअगरied to reflect the actual transfer period used
 * (normally some घातer of two units).  And क्रम isochronous urbs,
 * urb->start_frame is modअगरied to reflect when the URB's transfers were
 * scheduled to start.
 *
 * Not all isochronous transfer scheduling policies will work, but most
 * host controller drivers should easily handle ISO queues going from now
 * until 10-200 msec पूर्णांकo the future.  Drivers should try to keep at
 * least one or two msec of data in the queue; many controllers require
 * that new transfers start at least 1 msec in the future when they are
 * added.  If the driver is unable to keep up and the queue empties out,
 * the behavior क्रम new submissions is governed by the URB_ISO_ASAP flag.
 * If the flag is set, or अगर the queue is idle, then the URB is always
 * asचिन्हित to the first available (and not yet expired) slot in the
 * endpoपूर्णांक's schedule.  If the flag is not set and the queue is active
 * then the URB is always asचिन्हित to the next slot in the schedule
 * following the end of the endpoपूर्णांक's previous URB, even अगर that slot is
 * in the past.  When a packet is asचिन्हित in this way to a slot that has
 * alपढ़ोy expired, the packet is not transmitted and the corresponding
 * usb_iso_packet_descriptor's status field will वापस -EXDEV.  If this
 * would happen to all the packets in the URB, submission fails with a
 * -EXDEV error code.
 *
 * For control endpoपूर्णांकs, the synchronous usb_control_msg() call is
 * often used (in non-पूर्णांकerrupt context) instead of this call.
 * That is often used through convenience wrappers, क्रम the requests
 * that are standardized in the USB 2.0 specअगरication.  For bulk
 * endpoपूर्णांकs, a synchronous usb_bulk_msg() call is available.
 *
 * Return:
 * 0 on successful submissions. A negative error number otherwise.
 *
 * Request Queuing:
 *
 * URBs may be submitted to endpoपूर्णांकs beक्रमe previous ones complete, to
 * minimize the impact of पूर्णांकerrupt latencies and प्रणाली overhead on data
 * throughput.  With that queuing policy, an endpoपूर्णांक's queue would never
 * be empty.  This is required क्रम continuous isochronous data streams,
 * and may also be required क्रम some kinds of पूर्णांकerrupt transfers. Such
 * queuing also maximizes bandwidth utilization by letting USB controllers
 * start work on later requests beक्रमe driver software has finished the
 * completion processing क्रम earlier (successful) requests.
 *
 * As of Linux 2.6, all USB endpoपूर्णांक transfer queues support depths greater
 * than one.  This was previously a HCD-specअगरic behavior, except क्रम ISO
 * transfers.  Non-isochronous endpoपूर्णांक queues are inactive during cleanup
 * after faults (transfer errors or cancellation).
 *
 * Reserved Bandwidth Transfers:
 *
 * Periodic transfers (पूर्णांकerrupt or isochronous) are perक्रमmed repeatedly,
 * using the पूर्णांकerval specअगरied in the urb.  Submitting the first urb to
 * the endpoपूर्णांक reserves the bandwidth necessary to make those transfers.
 * If the USB subप्रणाली can't allocate sufficient bandwidth to perक्रमm
 * the periodic request, submitting such a periodic request should fail.
 *
 * For devices under xHCI, the bandwidth is reserved at configuration समय, or
 * when the alt setting is selected.  If there is not enough bus bandwidth, the
 * configuration/alt setting request will fail.  Thereक्रमe, submissions to
 * periodic endpoपूर्णांकs on devices under xHCI should never fail due to bandwidth
 * स्थिरraपूर्णांकs.
 *
 * Device drivers must explicitly request that repetition, by ensuring that
 * some URB is always on the endpoपूर्णांक's queue (except possibly क्रम लघु
 * periods during completion callbacks).  When there is no दीर्घer an urb
 * queued, the endpoपूर्णांक's bandwidth reservation is canceled.  This means
 * drivers can use their completion handlers to ensure they keep bandwidth
 * they need, by reinitializing and resubmitting the just-completed urb
 * until the driver दीर्घer needs that periodic bandwidth.
 *
 * Memory Flags:
 *
 * The general rules क्रम how to decide which mem_flags to use
 * are the same as क्रम kदो_स्मृति.  There are four
 * dअगरferent possible values; GFP_KERNEL, GFP_NOFS, GFP_NOIO and
 * GFP_ATOMIC.
 *
 * GFP_NOFS is not ever used, as it has not been implemented yet.
 *
 * GFP_ATOMIC is used when
 *   (a) you are inside a completion handler, an पूर्णांकerrupt, bottom half,
 *       tasklet or समयr, or
 *   (b) you are holding a spinlock or rwlock (करोes not apply to
 *       semaphores), or
 *   (c) current->state != TASK_RUNNING, this is the हाल only after
 *       you've changed it.
 *
 * GFP_NOIO is used in the block io path and error handling of storage
 * devices.
 *
 * All other situations use GFP_KERNEL.
 *
 * Some more specअगरic rules क्रम mem_flags can be inferred, such as
 *  (1) start_xmit, समयout, and receive methods of network drivers must
 *      use GFP_ATOMIC (they are called with a spinlock held);
 *  (2) queuecommand methods of scsi drivers must use GFP_ATOMIC (also
 *      called with a spinlock held);
 *  (3) If you use a kernel thपढ़ो with a network driver you must use
 *      GFP_NOIO, unless (b) or (c) apply;
 *  (4) after you have करोne a करोwn() you can use GFP_KERNEL, unless (b) or (c)
 *      apply or your are in a storage driver's block io path;
 *  (5) USB probe and disconnect can use GFP_KERNEL unless (b) or (c) apply; and
 *  (6) changing firmware on a running storage or net device uses
 *      GFP_NOIO, unless b) or c) apply
 *
 */
पूर्णांक usb_submit_urb(काष्ठा urb *urb, gfp_t mem_flags)
अणु
	पूर्णांक				xfertype, max;
	काष्ठा usb_device		*dev;
	काष्ठा usb_host_endpoपूर्णांक	*ep;
	पूर्णांक				is_out;
	अचिन्हित पूर्णांक			allowed;

	अगर (!urb || !urb->complete)
		वापस -EINVAL;
	अगर (urb->hcpriv) अणु
		WARN_ONCE(1, "URB %pK submitted while active\n", urb);
		वापस -EBUSY;
	पूर्ण

	dev = urb->dev;
	अगर ((!dev) || (dev->state < USB_STATE_UNAUTHENTICATED))
		वापस -ENODEV;

	/* For now, get the endpoपूर्णांक from the pipe.  Eventually drivers
	 * will be required to set urb->ep directly and we will eliminate
	 * urb->pipe.
	 */
	ep = usb_pipe_endpoपूर्णांक(dev, urb->pipe);
	अगर (!ep)
		वापस -ENOENT;

	urb->ep = ep;
	urb->status = -EINPROGRESS;
	urb->actual_length = 0;

	/* Lots of sanity checks, so HCDs can rely on clean data
	 * and करोn't need to duplicate tests
	 */
	xfertype = usb_endpoपूर्णांक_type(&ep->desc);
	अगर (xfertype == USB_ENDPOINT_XFER_CONTROL) अणु
		काष्ठा usb_ctrlrequest *setup =
				(काष्ठा usb_ctrlrequest *) urb->setup_packet;

		अगर (!setup)
			वापस -ENOEXEC;
		is_out = !(setup->bRequestType & USB_सूची_IN) ||
				!setup->wLength;
	पूर्ण अन्यथा अणु
		is_out = usb_endpoपूर्णांक_dir_out(&ep->desc);
	पूर्ण

	/* Clear the पूर्णांकernal flags and cache the direction क्रम later use */
	urb->transfer_flags &= ~(URB_सूची_MASK | URB_DMA_MAP_SINGLE |
			URB_DMA_MAP_PAGE | URB_DMA_MAP_SG | URB_MAP_LOCAL |
			URB_SETUP_MAP_SINGLE | URB_SETUP_MAP_LOCAL |
			URB_DMA_SG_COMBINED);
	urb->transfer_flags |= (is_out ? URB_सूची_OUT : URB_सूची_IN);

	अगर (xfertype != USB_ENDPOINT_XFER_CONTROL &&
			dev->state < USB_STATE_CONFIGURED)
		वापस -ENODEV;

	max = usb_endpoपूर्णांक_maxp(&ep->desc);
	अगर (max <= 0) अणु
		dev_dbg(&dev->dev,
			"bogus endpoint ep%d%s in %s (bad maxpacket %d)\n",
			usb_endpoपूर्णांक_num(&ep->desc), is_out ? "out" : "in",
			__func__, max);
		वापस -EMSGSIZE;
	पूर्ण

	/* periodic transfers limit size per frame/uframe,
	 * but drivers only control those sizes क्रम ISO.
	 * जबतक we're checking, initialize वापस status.
	 */
	अगर (xfertype == USB_ENDPOINT_XFER_ISOC) अणु
		पूर्णांक	n, len;

		/* SuperSpeed isoc endpoपूर्णांकs have up to 16 bursts of up to
		 * 3 packets each
		 */
		अगर (dev->speed >= USB_SPEED_SUPER) अणु
			पूर्णांक     burst = 1 + ep->ss_ep_comp.bMaxBurst;
			पूर्णांक     mult = USB_SS_MULT(ep->ss_ep_comp.bmAttributes);
			max *= burst;
			max *= mult;
		पूर्ण

		अगर (dev->speed == USB_SPEED_SUPER_PLUS &&
		    USB_SS_SSP_ISOC_COMP(ep->ss_ep_comp.bmAttributes)) अणु
			काष्ठा usb_ssp_isoc_ep_comp_descriptor *isoc_ep_comp;

			isoc_ep_comp = &ep->ssp_isoc_ep_comp;
			max = le32_to_cpu(isoc_ep_comp->dwBytesPerInterval);
		पूर्ण

		/* "high bandwidth" mode, 1-3 packets/uframe? */
		अगर (dev->speed == USB_SPEED_HIGH)
			max *= usb_endpoपूर्णांक_maxp_mult(&ep->desc);

		अगर (urb->number_of_packets <= 0)
			वापस -EINVAL;
		क्रम (n = 0; n < urb->number_of_packets; n++) अणु
			len = urb->iso_frame_desc[n].length;
			अगर (len < 0 || len > max)
				वापस -EMSGSIZE;
			urb->iso_frame_desc[n].status = -EXDEV;
			urb->iso_frame_desc[n].actual_length = 0;
		पूर्ण
	पूर्ण अन्यथा अगर (urb->num_sgs && !urb->dev->bus->no_sg_स्थिरraपूर्णांक &&
			dev->speed != USB_SPEED_WIRELESS) अणु
		काष्ठा scatterlist *sg;
		पूर्णांक i;

		क्रम_each_sg(urb->sg, sg, urb->num_sgs - 1, i)
			अगर (sg->length % max)
				वापस -EINVAL;
	पूर्ण

	/* the I/O buffer must be mapped/unmapped, except when length=0 */
	अगर (urb->transfer_buffer_length > पूर्णांक_उच्च)
		वापस -EMSGSIZE;

	/*
	 * stuff that drivers shouldn't do, but which shouldn't
	 * cause problems in HCDs अगर they get it wrong.
	 */

	/* Check that the pipe's type matches the endpoint's type */
	अगर (usb_pipe_type_check(urb->dev, urb->pipe))
		dev_WARN(&dev->dev, "BOGUS urb xfer, pipe %x != type %x\n",
			usb_pipetype(urb->pipe), pipetypes[xfertype]);

	/* Check against a simple/standard policy */
	allowed = (URB_NO_TRANSFER_DMA_MAP | URB_NO_INTERRUPT | URB_सूची_MASK |
			URB_FREE_BUFFER);
	चयन (xfertype) अणु
	हाल USB_ENDPOINT_XFER_BULK:
	हाल USB_ENDPOINT_XFER_INT:
		अगर (is_out)
			allowed |= URB_ZERO_PACKET;
		fallthrough;
	शेष:			/* all non-iso endpoपूर्णांकs */
		अगर (!is_out)
			allowed |= URB_SHORT_NOT_OK;
		अवरोध;
	हाल USB_ENDPOINT_XFER_ISOC:
		allowed |= URB_ISO_ASAP;
		अवरोध;
	पूर्ण
	allowed &= urb->transfer_flags;

	/* warn अगर submitter gave bogus flags */
	अगर (allowed != urb->transfer_flags)
		dev_WARN(&dev->dev, "BOGUS urb flags, %x --> %x\n",
			urb->transfer_flags, allowed);

	/*
	 * Force periodic transfer पूर्णांकervals to be legal values that are
	 * a घातer of two (so HCDs करोn't need to).
	 *
	 * FIXME want bus->अणुपूर्णांकr,isoपूर्ण_sched_horizon values here.  Each HC
	 * supports dअगरferent values... this uses EHCI/UHCI शेषs (and
	 * EHCI can use smaller non-शेष values).
	 */
	चयन (xfertype) अणु
	हाल USB_ENDPOINT_XFER_ISOC:
	हाल USB_ENDPOINT_XFER_INT:
		/* too small? */
		चयन (dev->speed) अणु
		हाल USB_SPEED_WIRELESS:
			अगर ((urb->पूर्णांकerval < 6)
				&& (xfertype == USB_ENDPOINT_XFER_INT))
				वापस -EINVAL;
			fallthrough;
		शेष:
			अगर (urb->पूर्णांकerval <= 0)
				वापस -EINVAL;
			अवरोध;
		पूर्ण
		/* too big? */
		चयन (dev->speed) अणु
		हाल USB_SPEED_SUPER_PLUS:
		हाल USB_SPEED_SUPER:	/* units are 125us */
			/* Handle up to 2^(16-1) microframes */
			अगर (urb->पूर्णांकerval > (1 << 15))
				वापस -EINVAL;
			max = 1 << 15;
			अवरोध;
		हाल USB_SPEED_WIRELESS:
			अगर (urb->पूर्णांकerval > 16)
				वापस -EINVAL;
			अवरोध;
		हाल USB_SPEED_HIGH:	/* units are microframes */
			/* NOTE usb handles 2^15 */
			अगर (urb->पूर्णांकerval > (1024 * 8))
				urb->पूर्णांकerval = 1024 * 8;
			max = 1024 * 8;
			अवरोध;
		हाल USB_SPEED_FULL:	/* units are frames/msec */
		हाल USB_SPEED_LOW:
			अगर (xfertype == USB_ENDPOINT_XFER_INT) अणु
				अगर (urb->पूर्णांकerval > 255)
					वापस -EINVAL;
				/* NOTE ohci only handles up to 32 */
				max = 128;
			पूर्ण अन्यथा अणु
				अगर (urb->पूर्णांकerval > 1024)
					urb->पूर्णांकerval = 1024;
				/* NOTE usb and ohci handle up to 2^15 */
				max = 1024;
			पूर्ण
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अगर (dev->speed != USB_SPEED_WIRELESS) अणु
			/* Round करोwn to a घातer of 2, no more than max */
			urb->पूर्णांकerval = min(max, 1 << ilog2(urb->पूर्णांकerval));
		पूर्ण
	पूर्ण

	वापस usb_hcd_submit_urb(urb, mem_flags);
पूर्ण
EXPORT_SYMBOL_GPL(usb_submit_urb);

/*-------------------------------------------------------------------*/

/**
 * usb_unlink_urb - पात/cancel a transfer request क्रम an endpoपूर्णांक
 * @urb: poपूर्णांकer to urb describing a previously submitted request,
 *	may be शून्य
 *
 * This routine cancels an in-progress request.  URBs complete only once
 * per submission, and may be canceled only once per submission.
 * Successful cancellation means termination of @urb will be expedited
 * and the completion handler will be called with a status code
 * indicating that the request has been canceled (rather than any other
 * code).
 *
 * Drivers should not call this routine or related routines, such as
 * usb_समाप्त_urb() or usb_unlink_anchored_urbs(), after their disconnect
 * method has वापसed.  The disconnect function should synchronize with
 * a driver's I/O routines to insure that all URB-related activity has
 * completed beक्रमe it वापसs.
 *
 * This request is asynchronous, however the HCD might call the ->complete()
 * callback during unlink. Thereक्रमe when drivers call usb_unlink_urb(), they
 * must not hold any locks that may be taken by the completion function.
 * Success is indicated by वापसing -EINPROGRESS, at which समय the URB will
 * probably not yet have been given back to the device driver. When it is
 * eventually called, the completion function will see @urb->status ==
 * -ECONNRESET.
 * Failure is indicated by usb_unlink_urb() वापसing any other value.
 * Unlinking will fail when @urb is not currently "linked" (i.e., it was
 * never submitted, or it was unlinked beक्रमe, or the hardware is alपढ़ोy
 * finished with it), even अगर the completion handler has not yet run.
 *
 * The URB must not be deallocated जबतक this routine is running.  In
 * particular, when a driver calls this routine, it must insure that the
 * completion handler cannot deallocate the URB.
 *
 * Return: -EINPROGRESS on success. See description क्रम other values on
 * failure.
 *
 * Unlinking and Endpoपूर्णांक Queues:
 *
 * [The behaviors and guarantees described below करो not apply to भव
 * root hubs but only to endpoपूर्णांक queues क्रम physical USB devices.]
 *
 * Host Controller Drivers (HCDs) place all the URBs क्रम a particular
 * endpoपूर्णांक in a queue.  Normally the queue advances as the controller
 * hardware processes each request.  But when an URB terminates with an
 * error its queue generally stops (see below), at least until that URB's
 * completion routine वापसs.  It is guaranteed that a stopped queue
 * will not restart until all its unlinked URBs have been fully retired,
 * with their completion routines run, even अगर that's not until some समय
 * after the original completion handler वापसs.  The same behavior and
 * guarantee apply when an URB terminates because it was unlinked.
 *
 * Bulk and पूर्णांकerrupt endpoपूर्णांक queues are guaranteed to stop whenever an
 * URB terminates with any sort of error, including -ECONNRESET, -ENOENT,
 * and -EREMOTEIO.  Control endpoपूर्णांक queues behave the same way except
 * that they are not guaranteed to stop क्रम -EREMOTEIO errors.  Queues
 * क्रम isochronous endpoपूर्णांकs are treated dअगरferently, because they must
 * advance at fixed rates.  Such queues करो not stop when an URB
 * encounters an error or is unlinked.  An unlinked isochronous URB may
 * leave a gap in the stream of packets; it is undefined whether such
 * gaps can be filled in.
 *
 * Note that early termination of an URB because a लघु packet was
 * received will generate a -EREMOTEIO error अगर and only अगर the
 * URB_SHORT_NOT_OK flag is set.  By setting this flag, USB device
 * drivers can build deep queues क्रम large or complex bulk transfers
 * and clean them up reliably after any sort of पातed transfer by
 * unlinking all pending URBs at the first fault.
 *
 * When a control URB terminates with an error other than -EREMOTEIO, it
 * is quite likely that the status stage of the transfer will not take
 * place.
 */
पूर्णांक usb_unlink_urb(काष्ठा urb *urb)
अणु
	अगर (!urb)
		वापस -EINVAL;
	अगर (!urb->dev)
		वापस -ENODEV;
	अगर (!urb->ep)
		वापस -EIDRM;
	वापस usb_hcd_unlink_urb(urb, -ECONNRESET);
पूर्ण
EXPORT_SYMBOL_GPL(usb_unlink_urb);

/**
 * usb_समाप्त_urb - cancel a transfer request and रुको क्रम it to finish
 * @urb: poपूर्णांकer to URB describing a previously submitted request,
 *	may be शून्य
 *
 * This routine cancels an in-progress request.  It is guaranteed that
 * upon वापस all completion handlers will have finished and the URB
 * will be totally idle and available क्रम reuse.  These features make
 * this an ideal way to stop I/O in a disconnect() callback or बंद()
 * function.  If the request has not alपढ़ोy finished or been unlinked
 * the completion handler will see urb->status == -ENOENT.
 *
 * While the routine is running, attempts to resubmit the URB will fail
 * with error -EPERM.  Thus even अगर the URB's completion handler always
 * tries to resubmit, it will not succeed and the URB will become idle.
 *
 * The URB must not be deallocated जबतक this routine is running.  In
 * particular, when a driver calls this routine, it must insure that the
 * completion handler cannot deallocate the URB.
 *
 * This routine may not be used in an पूर्णांकerrupt context (such as a bottom
 * half or a completion handler), or when holding a spinlock, or in other
 * situations where the caller can't schedule().
 *
 * This routine should not be called by a driver after its disconnect
 * method has वापसed.
 */
व्योम usb_समाप्त_urb(काष्ठा urb *urb)
अणु
	might_sleep();
	अगर (!(urb && urb->dev && urb->ep))
		वापस;
	atomic_inc(&urb->reject);

	usb_hcd_unlink_urb(urb, -ENOENT);
	रुको_event(usb_समाप्त_urb_queue, atomic_पढ़ो(&urb->use_count) == 0);

	atomic_dec(&urb->reject);
पूर्ण
EXPORT_SYMBOL_GPL(usb_समाप्त_urb);

/**
 * usb_poison_urb - reliably समाप्त a transfer and prevent further use of an URB
 * @urb: poपूर्णांकer to URB describing a previously submitted request,
 *	may be शून्य
 *
 * This routine cancels an in-progress request.  It is guaranteed that
 * upon वापस all completion handlers will have finished and the URB
 * will be totally idle and cannot be reused.  These features make
 * this an ideal way to stop I/O in a disconnect() callback.
 * If the request has not alपढ़ोy finished or been unlinked
 * the completion handler will see urb->status == -ENOENT.
 *
 * After and जबतक the routine runs, attempts to resubmit the URB will fail
 * with error -EPERM.  Thus even अगर the URB's completion handler always
 * tries to resubmit, it will not succeed and the URB will become idle.
 *
 * The URB must not be deallocated जबतक this routine is running.  In
 * particular, when a driver calls this routine, it must insure that the
 * completion handler cannot deallocate the URB.
 *
 * This routine may not be used in an पूर्णांकerrupt context (such as a bottom
 * half or a completion handler), or when holding a spinlock, or in other
 * situations where the caller can't schedule().
 *
 * This routine should not be called by a driver after its disconnect
 * method has वापसed.
 */
व्योम usb_poison_urb(काष्ठा urb *urb)
अणु
	might_sleep();
	अगर (!urb)
		वापस;
	atomic_inc(&urb->reject);

	अगर (!urb->dev || !urb->ep)
		वापस;

	usb_hcd_unlink_urb(urb, -ENOENT);
	रुको_event(usb_समाप्त_urb_queue, atomic_पढ़ो(&urb->use_count) == 0);
पूर्ण
EXPORT_SYMBOL_GPL(usb_poison_urb);

व्योम usb_unpoison_urb(काष्ठा urb *urb)
अणु
	अगर (!urb)
		वापस;

	atomic_dec(&urb->reject);
पूर्ण
EXPORT_SYMBOL_GPL(usb_unpoison_urb);

/**
 * usb_block_urb - reliably prevent further use of an URB
 * @urb: poपूर्णांकer to URB to be blocked, may be शून्य
 *
 * After the routine has run, attempts to resubmit the URB will fail
 * with error -EPERM.  Thus even अगर the URB's completion handler always
 * tries to resubmit, it will not succeed and the URB will become idle.
 *
 * The URB must not be deallocated जबतक this routine is running.  In
 * particular, when a driver calls this routine, it must insure that the
 * completion handler cannot deallocate the URB.
 */
व्योम usb_block_urb(काष्ठा urb *urb)
अणु
	अगर (!urb)
		वापस;

	atomic_inc(&urb->reject);
पूर्ण
EXPORT_SYMBOL_GPL(usb_block_urb);

/**
 * usb_समाप्त_anchored_urbs - समाप्त all URBs associated with an anchor
 * @anchor: anchor the requests are bound to
 *
 * This समाप्तs all outstanding URBs starting from the back of the queue,
 * with guarantee that no completer callbacks will take place from the
 * anchor after this function वापसs.
 *
 * This routine should not be called by a driver after its disconnect
 * method has वापसed.
 */
व्योम usb_समाप्त_anchored_urbs(काष्ठा usb_anchor *anchor)
अणु
	काष्ठा urb *victim;
	पूर्णांक surely_empty;

	करो अणु
		spin_lock_irq(&anchor->lock);
		जबतक (!list_empty(&anchor->urb_list)) अणु
			victim = list_entry(anchor->urb_list.prev,
					    काष्ठा urb, anchor_list);
			/* make sure the URB isn't मुक्तd beक्रमe we समाप्त it */
			usb_get_urb(victim);
			spin_unlock_irq(&anchor->lock);
			/* this will unanchor the URB */
			usb_समाप्त_urb(victim);
			usb_put_urb(victim);
			spin_lock_irq(&anchor->lock);
		पूर्ण
		surely_empty = usb_anchor_check_wakeup(anchor);

		spin_unlock_irq(&anchor->lock);
		cpu_relax();
	पूर्ण जबतक (!surely_empty);
पूर्ण
EXPORT_SYMBOL_GPL(usb_समाप्त_anchored_urbs);


/**
 * usb_poison_anchored_urbs - cease all traffic from an anchor
 * @anchor: anchor the requests are bound to
 *
 * this allows all outstanding URBs to be poisoned starting
 * from the back of the queue. Newly added URBs will also be
 * poisoned
 *
 * This routine should not be called by a driver after its disconnect
 * method has वापसed.
 */
व्योम usb_poison_anchored_urbs(काष्ठा usb_anchor *anchor)
अणु
	काष्ठा urb *victim;
	पूर्णांक surely_empty;

	करो अणु
		spin_lock_irq(&anchor->lock);
		anchor->poisoned = 1;
		जबतक (!list_empty(&anchor->urb_list)) अणु
			victim = list_entry(anchor->urb_list.prev,
					    काष्ठा urb, anchor_list);
			/* make sure the URB isn't मुक्तd beक्रमe we समाप्त it */
			usb_get_urb(victim);
			spin_unlock_irq(&anchor->lock);
			/* this will unanchor the URB */
			usb_poison_urb(victim);
			usb_put_urb(victim);
			spin_lock_irq(&anchor->lock);
		पूर्ण
		surely_empty = usb_anchor_check_wakeup(anchor);

		spin_unlock_irq(&anchor->lock);
		cpu_relax();
	पूर्ण जबतक (!surely_empty);
पूर्ण
EXPORT_SYMBOL_GPL(usb_poison_anchored_urbs);

/**
 * usb_unpoison_anchored_urbs - let an anchor be used successfully again
 * @anchor: anchor the requests are bound to
 *
 * Reverses the effect of usb_poison_anchored_urbs
 * the anchor can be used normally after it वापसs
 */
व्योम usb_unpoison_anchored_urbs(काष्ठा usb_anchor *anchor)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा urb *lazarus;

	spin_lock_irqsave(&anchor->lock, flags);
	list_क्रम_each_entry(lazarus, &anchor->urb_list, anchor_list) अणु
		usb_unpoison_urb(lazarus);
	पूर्ण
	anchor->poisoned = 0;
	spin_unlock_irqrestore(&anchor->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(usb_unpoison_anchored_urbs);
/**
 * usb_unlink_anchored_urbs - asynchronously cancel transfer requests en masse
 * @anchor: anchor the requests are bound to
 *
 * this allows all outstanding URBs to be unlinked starting
 * from the back of the queue. This function is asynchronous.
 * The unlinking is just triggered. It may happen after this
 * function has वापसed.
 *
 * This routine should not be called by a driver after its disconnect
 * method has वापसed.
 */
व्योम usb_unlink_anchored_urbs(काष्ठा usb_anchor *anchor)
अणु
	काष्ठा urb *victim;

	जबतक ((victim = usb_get_from_anchor(anchor)) != शून्य) अणु
		usb_unlink_urb(victim);
		usb_put_urb(victim);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(usb_unlink_anchored_urbs);

/**
 * usb_anchor_suspend_wakeups
 * @anchor: the anchor you want to suspend wakeups on
 *
 * Call this to stop the last urb being unanchored from waking up any
 * usb_रुको_anchor_empty_समयout रुकोers. This is used in the hcd urb give-
 * back path to delay waking up until after the completion handler has run.
 */
व्योम usb_anchor_suspend_wakeups(काष्ठा usb_anchor *anchor)
अणु
	अगर (anchor)
		atomic_inc(&anchor->suspend_wakeups);
पूर्ण
EXPORT_SYMBOL_GPL(usb_anchor_suspend_wakeups);

/**
 * usb_anchor_resume_wakeups
 * @anchor: the anchor you want to resume wakeups on
 *
 * Allow usb_रुको_anchor_empty_समयout रुकोers to be woken up again, and
 * wake up any current रुकोers अगर the anchor is empty.
 */
व्योम usb_anchor_resume_wakeups(काष्ठा usb_anchor *anchor)
अणु
	अगर (!anchor)
		वापस;

	atomic_dec(&anchor->suspend_wakeups);
	अगर (usb_anchor_check_wakeup(anchor))
		wake_up(&anchor->रुको);
पूर्ण
EXPORT_SYMBOL_GPL(usb_anchor_resume_wakeups);

/**
 * usb_रुको_anchor_empty_समयout - रुको क्रम an anchor to be unused
 * @anchor: the anchor you want to become unused
 * @समयout: how दीर्घ you are willing to रुको in milliseconds
 *
 * Call this is you want to be sure all an anchor's
 * URBs have finished
 *
 * Return: Non-zero अगर the anchor became unused. Zero on समयout.
 */
पूर्णांक usb_रुको_anchor_empty_समयout(काष्ठा usb_anchor *anchor,
				  अचिन्हित पूर्णांक समयout)
अणु
	वापस रुको_event_समयout(anchor->रुको,
				  usb_anchor_check_wakeup(anchor),
				  msecs_to_jअगरfies(समयout));
पूर्ण
EXPORT_SYMBOL_GPL(usb_रुको_anchor_empty_समयout);

/**
 * usb_get_from_anchor - get an anchor's oldest urb
 * @anchor: the anchor whose urb you want
 *
 * This will take the oldest urb from an anchor,
 * unanchor and वापस it
 *
 * Return: The oldest urb from @anchor, or %शून्य अगर @anchor has no
 * urbs associated with it.
 */
काष्ठा urb *usb_get_from_anchor(काष्ठा usb_anchor *anchor)
अणु
	काष्ठा urb *victim;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&anchor->lock, flags);
	अगर (!list_empty(&anchor->urb_list)) अणु
		victim = list_entry(anchor->urb_list.next, काष्ठा urb,
				    anchor_list);
		usb_get_urb(victim);
		__usb_unanchor_urb(victim, anchor);
	पूर्ण अन्यथा अणु
		victim = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&anchor->lock, flags);

	वापस victim;
पूर्ण

EXPORT_SYMBOL_GPL(usb_get_from_anchor);

/**
 * usb_scuttle_anchored_urbs - unanchor all an anchor's urbs
 * @anchor: the anchor whose urbs you want to unanchor
 *
 * use this to get rid of all an anchor's urbs
 */
व्योम usb_scuttle_anchored_urbs(काष्ठा usb_anchor *anchor)
अणु
	काष्ठा urb *victim;
	अचिन्हित दीर्घ flags;
	पूर्णांक surely_empty;

	करो अणु
		spin_lock_irqsave(&anchor->lock, flags);
		जबतक (!list_empty(&anchor->urb_list)) अणु
			victim = list_entry(anchor->urb_list.prev,
					    काष्ठा urb, anchor_list);
			__usb_unanchor_urb(victim, anchor);
		पूर्ण
		surely_empty = usb_anchor_check_wakeup(anchor);

		spin_unlock_irqrestore(&anchor->lock, flags);
		cpu_relax();
	पूर्ण जबतक (!surely_empty);
पूर्ण

EXPORT_SYMBOL_GPL(usb_scuttle_anchored_urbs);

/**
 * usb_anchor_empty - is an anchor empty
 * @anchor: the anchor you want to query
 *
 * Return: 1 अगर the anchor has no urbs associated with it.
 */
पूर्णांक usb_anchor_empty(काष्ठा usb_anchor *anchor)
अणु
	वापस list_empty(&anchor->urb_list);
पूर्ण

EXPORT_SYMBOL_GPL(usb_anchor_empty);

