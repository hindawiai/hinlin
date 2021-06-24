<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * udc.c - Core UDC Framework
 *
 * Copyright (C) 2010 Texas Instruments
 * Author: Felipe Balbi <balbi@ti.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/list.h>
#समावेश <linux/err.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/workqueue.h>

#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb.h>

#समावेश "trace.h"

/**
 * काष्ठा usb_udc - describes one usb device controller
 * @driver: the gadget driver poपूर्णांकer. For use by the class code
 * @dev: the child device to the actual controller
 * @gadget: the gadget. For use by the class code
 * @list: क्रम use by the udc class driver
 * @vbus: क्रम udcs who care about vbus status, this value is real vbus status;
 * क्रम udcs who करो not care about vbus status, this value is always true
 * @started: the UDC's started state. True अगर the UDC had started.
 *
 * This represents the पूर्णांकernal data काष्ठाure which is used by the UDC-class
 * to hold inक्रमmation about udc driver and gadget together.
 */
काष्ठा usb_udc अणु
	काष्ठा usb_gadget_driver	*driver;
	काष्ठा usb_gadget		*gadget;
	काष्ठा device			dev;
	काष्ठा list_head		list;
	bool				vbus;
	bool				started;
पूर्ण;

अटल काष्ठा class *udc_class;
अटल LIST_HEAD(udc_list);
अटल LIST_HEAD(gadget_driver_pending_list);
अटल DEFINE_MUTEX(udc_lock);

अटल पूर्णांक udc_bind_to_driver(काष्ठा usb_udc *udc,
		काष्ठा usb_gadget_driver *driver);

/* ------------------------------------------------------------------------- */

/**
 * usb_ep_set_maxpacket_limit - set maximum packet size limit क्रम endpoपूर्णांक
 * @ep:the endpoपूर्णांक being configured
 * @maxpacket_limit:value of maximum packet size limit
 *
 * This function should be used only in UDC drivers to initialize endpoपूर्णांक
 * (usually in probe function).
 */
व्योम usb_ep_set_maxpacket_limit(काष्ठा usb_ep *ep,
					      अचिन्हित maxpacket_limit)
अणु
	ep->maxpacket_limit = maxpacket_limit;
	ep->maxpacket = maxpacket_limit;

	trace_usb_ep_set_maxpacket_limit(ep, 0);
पूर्ण
EXPORT_SYMBOL_GPL(usb_ep_set_maxpacket_limit);

/**
 * usb_ep_enable - configure endpoपूर्णांक, making it usable
 * @ep:the endpoपूर्णांक being configured.  may not be the endpoपूर्णांक named "ep0".
 *	drivers discover endpoपूर्णांकs through the ep_list of a usb_gadget.
 *
 * When configurations are set, or when पूर्णांकerface settings change, the driver
 * will enable or disable the relevant endpoपूर्णांकs.  जबतक it is enabled, an
 * endpoपूर्णांक may be used क्रम i/o until the driver receives a disconnect() from
 * the host or until the endpoपूर्णांक is disabled.
 *
 * the ep0 implementation (which calls this routine) must ensure that the
 * hardware capabilities of each endpoपूर्णांक match the descriptor provided
 * क्रम it.  क्रम example, an endpoपूर्णांक named "ep2in-bulk" would be usable
 * क्रम पूर्णांकerrupt transfers as well as bulk, but it likely couldn't be used
 * क्रम iso transfers or क्रम endpoपूर्णांक 14.  some endpoपूर्णांकs are fully
 * configurable, with more generic names like "ep-a".  (remember that क्रम
 * USB, "in" means "towards the USB host".)
 *
 * This routine must be called in process context.
 *
 * वापसs zero, or a negative error code.
 */
पूर्णांक usb_ep_enable(काष्ठा usb_ep *ep)
अणु
	पूर्णांक ret = 0;

	अगर (ep->enabled)
		जाओ out;

	/* UDC drivers can't handle endpoपूर्णांकs with maxpacket size 0 */
	अगर (usb_endpoपूर्णांक_maxp(ep->desc) == 0) अणु
		/*
		 * We should log an error message here, but we can't call
		 * dev_err() because there's no way to find the gadget
		 * given only ep.
		 */
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = ep->ops->enable(ep, ep->desc);
	अगर (ret)
		जाओ out;

	ep->enabled = true;

out:
	trace_usb_ep_enable(ep, ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_ep_enable);

/**
 * usb_ep_disable - endpoपूर्णांक is no दीर्घer usable
 * @ep:the endpoपूर्णांक being unconfigured.  may not be the endpoपूर्णांक named "ep0".
 *
 * no other task may be using this endpoपूर्णांक when this is called.
 * any pending and uncompleted requests will complete with status
 * indicating disconnect (-ESHUTDOWN) beक्रमe this call वापसs.
 * gadget drivers must call usb_ep_enable() again beक्रमe queueing
 * requests to the endpoपूर्णांक.
 *
 * This routine must be called in process context.
 *
 * वापसs zero, or a negative error code.
 */
पूर्णांक usb_ep_disable(काष्ठा usb_ep *ep)
अणु
	पूर्णांक ret = 0;

	अगर (!ep->enabled)
		जाओ out;

	ret = ep->ops->disable(ep);
	अगर (ret)
		जाओ out;

	ep->enabled = false;

out:
	trace_usb_ep_disable(ep, ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_ep_disable);

/**
 * usb_ep_alloc_request - allocate a request object to use with this endpoपूर्णांक
 * @ep:the endpoपूर्णांक to be used with with the request
 * @gfp_flags:GFP_* flags to use
 *
 * Request objects must be allocated with this call, since they normally
 * need controller-specअगरic setup and may even need endpoपूर्णांक-specअगरic
 * resources such as allocation of DMA descriptors.
 * Requests may be submitted with usb_ep_queue(), and receive a single
 * completion callback.  Free requests with usb_ep_मुक्त_request(), when
 * they are no दीर्घer needed.
 *
 * Returns the request, or null अगर one could not be allocated.
 */
काष्ठा usb_request *usb_ep_alloc_request(काष्ठा usb_ep *ep,
						       gfp_t gfp_flags)
अणु
	काष्ठा usb_request *req = शून्य;

	req = ep->ops->alloc_request(ep, gfp_flags);

	trace_usb_ep_alloc_request(ep, req, req ? 0 : -ENOMEM);

	वापस req;
पूर्ण
EXPORT_SYMBOL_GPL(usb_ep_alloc_request);

/**
 * usb_ep_मुक्त_request - मुक्तs a request object
 * @ep:the endpoपूर्णांक associated with the request
 * @req:the request being मुक्तd
 *
 * Reverses the effect of usb_ep_alloc_request().
 * Caller guarantees the request is not queued, and that it will
 * no दीर्घer be requeued (or otherwise used).
 */
व्योम usb_ep_मुक्त_request(काष्ठा usb_ep *ep,
				       काष्ठा usb_request *req)
अणु
	trace_usb_ep_मुक्त_request(ep, req, 0);
	ep->ops->मुक्त_request(ep, req);
पूर्ण
EXPORT_SYMBOL_GPL(usb_ep_मुक्त_request);

/**
 * usb_ep_queue - queues (submits) an I/O request to an endpoपूर्णांक.
 * @ep:the endpoपूर्णांक associated with the request
 * @req:the request being submitted
 * @gfp_flags: GFP_* flags to use in हाल the lower level driver couldn't
 *	pre-allocate all necessary memory with the request.
 *
 * This tells the device controller to perक्रमm the specअगरied request through
 * that endpoपूर्णांक (पढ़ोing or writing a buffer).  When the request completes,
 * including being canceled by usb_ep_dequeue(), the request's completion
 * routine is called to वापस the request to the driver.  Any endpoपूर्णांक
 * (except control endpoपूर्णांकs like ep0) may have more than one transfer
 * request queued; they complete in FIFO order.  Once a gadget driver
 * submits a request, that request may not be examined or modअगरied until it
 * is given back to that driver through the completion callback.
 *
 * Each request is turned पूर्णांकo one or more packets.  The controller driver
 * never merges adjacent requests पूर्णांकo the same packet.  OUT transfers
 * will someबार use data that's alपढ़ोy buffered in the hardware.
 * Drivers can rely on the fact that the first byte of the request's buffer
 * always corresponds to the first byte of some USB packet, क्रम both
 * IN and OUT transfers.
 *
 * Bulk endpoपूर्णांकs can queue any amount of data; the transfer is packetized
 * स्वतःmatically.  The last packet will be लघु अगर the request करोesn't fill it
 * out completely.  Zero length packets (ZLPs) should be aव्योमed in portable
 * protocols since not all usb hardware can successfully handle zero length
 * packets.  (ZLPs may be explicitly written, and may be implicitly written अगर
 * the request 'zero' flag is set.)  Bulk endpoपूर्णांकs may also be used
 * क्रम पूर्णांकerrupt transfers; but the reverse is not true, and some endpoपूर्णांकs
 * won't support every पूर्णांकerrupt transfer.  (Such as 768 byte packets.)
 *
 * Interrupt-only endpoपूर्णांकs are less functional than bulk endpoपूर्णांकs, क्रम
 * example by not supporting queueing or not handling buffers that are
 * larger than the endpoपूर्णांक's maxpacket size.  They may also treat data
 * toggle dअगरferently.
 *
 * Control endpoपूर्णांकs ... after getting a setup() callback, the driver queues
 * one response (even अगर it would be zero length).  That enables the
 * status ack, after transferring data as specअगरied in the response.  Setup
 * functions may वापस negative error codes to generate protocol stalls.
 * (Note that some USB device controllers disallow protocol stall responses
 * in some हालs.)  When control responses are deferred (the response is
 * written after the setup callback वापसs), then usb_ep_set_halt() may be
 * used on ep0 to trigger protocol stalls.  Depending on the controller,
 * it may not be possible to trigger a status-stage protocol stall when the
 * data stage is over, that is, from within the response's completion
 * routine.
 *
 * For periodic endpoपूर्णांकs, like पूर्णांकerrupt or isochronous ones, the usb host
 * arranges to poll once per पूर्णांकerval, and the gadget driver usually will
 * have queued some data to transfer at that समय.
 *
 * Note that @req's ->complete() callback must never be called from
 * within usb_ep_queue() as that can create deadlock situations.
 *
 * This routine may be called in पूर्णांकerrupt context.
 *
 * Returns zero, or a negative error code.  Endpoपूर्णांकs that are not enabled
 * report errors; errors will also be
 * reported when the usb peripheral is disconnected.
 *
 * If and only अगर @req is successfully queued (the वापस value is zero),
 * @req->complete() will be called exactly once, when the Gadget core and
 * UDC are finished with the request.  When the completion function is called,
 * control of the request is वापसed to the device driver which submitted it.
 * The completion handler may then immediately मुक्त or reuse @req.
 */
पूर्णांक usb_ep_queue(काष्ठा usb_ep *ep,
			       काष्ठा usb_request *req, gfp_t gfp_flags)
अणु
	पूर्णांक ret = 0;

	अगर (WARN_ON_ONCE(!ep->enabled && ep->address)) अणु
		ret = -ESHUTDOWN;
		जाओ out;
	पूर्ण

	ret = ep->ops->queue(ep, req, gfp_flags);

out:
	trace_usb_ep_queue(ep, req, ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_ep_queue);

/**
 * usb_ep_dequeue - dequeues (cancels, unlinks) an I/O request from an endpoपूर्णांक
 * @ep:the endpoपूर्णांक associated with the request
 * @req:the request being canceled
 *
 * If the request is still active on the endpoपूर्णांक, it is dequeued and
 * eventually its completion routine is called (with status -ECONNRESET);
 * अन्यथा a negative error code is वापसed.  This routine is asynchronous,
 * that is, it may वापस beक्रमe the completion routine runs.
 *
 * Note that some hardware can't clear out ग_लिखो fअगरos (to unlink the request
 * at the head of the queue) except as part of disconnecting from usb. Such
 * restrictions prevent drivers from supporting configuration changes,
 * even to configuration zero (a "chapter 9" requirement).
 *
 * This routine may be called in पूर्णांकerrupt context.
 */
पूर्णांक usb_ep_dequeue(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	पूर्णांक ret;

	ret = ep->ops->dequeue(ep, req);
	trace_usb_ep_dequeue(ep, req, ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_ep_dequeue);

/**
 * usb_ep_set_halt - sets the endpoपूर्णांक halt feature.
 * @ep: the non-isochronous endpoपूर्णांक being stalled
 *
 * Use this to stall an endpoपूर्णांक, perhaps as an error report.
 * Except क्रम control endpoपूर्णांकs,
 * the endpoपूर्णांक stays halted (will not stream any data) until the host
 * clears this feature; drivers may need to empty the endpoपूर्णांक's request
 * queue first, to make sure no inappropriate transfers happen.
 *
 * Note that जबतक an endpoपूर्णांक CLEAR_FEATURE will be invisible to the
 * gadget driver, a SET_INTERFACE will not be.  To reset endpoपूर्णांकs क्रम the
 * current altsetting, see usb_ep_clear_halt().  When चयनing altsettings,
 * it's simplest to use usb_ep_enable() or usb_ep_disable() क्रम the endpoपूर्णांकs.
 *
 * This routine may be called in पूर्णांकerrupt context.
 *
 * Returns zero, or a negative error code.  On success, this call sets
 * underlying hardware state that blocks data transfers.
 * Attempts to halt IN endpoपूर्णांकs will fail (वापसing -EAGAIN) अगर any
 * transfer requests are still queued, or अगर the controller hardware
 * (usually a FIFO) still holds bytes that the host hasn't collected.
 */
पूर्णांक usb_ep_set_halt(काष्ठा usb_ep *ep)
अणु
	पूर्णांक ret;

	ret = ep->ops->set_halt(ep, 1);
	trace_usb_ep_set_halt(ep, ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_ep_set_halt);

/**
 * usb_ep_clear_halt - clears endpoपूर्णांक halt, and resets toggle
 * @ep:the bulk or पूर्णांकerrupt endpoपूर्णांक being reset
 *
 * Use this when responding to the standard usb "set interface" request,
 * क्रम endpoपूर्णांकs that aren't reconfigured, after clearing any other state
 * in the endpoपूर्णांक's i/o queue.
 *
 * This routine may be called in पूर्णांकerrupt context.
 *
 * Returns zero, or a negative error code.  On success, this call clears
 * the underlying hardware state reflecting endpoपूर्णांक halt and data toggle.
 * Note that some hardware can't support this request (like pxa2xx_udc),
 * and accordingly can't correctly implement पूर्णांकerface altsettings.
 */
पूर्णांक usb_ep_clear_halt(काष्ठा usb_ep *ep)
अणु
	पूर्णांक ret;

	ret = ep->ops->set_halt(ep, 0);
	trace_usb_ep_clear_halt(ep, ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_ep_clear_halt);

/**
 * usb_ep_set_wedge - sets the halt feature and ignores clear requests
 * @ep: the endpoपूर्णांक being wedged
 *
 * Use this to stall an endpoपूर्णांक and ignore CLEAR_FEATURE(HALT_ENDPOINT)
 * requests. If the gadget driver clears the halt status, it will
 * स्वतःmatically unwedge the endpoपूर्णांक.
 *
 * This routine may be called in पूर्णांकerrupt context.
 *
 * Returns zero on success, अन्यथा negative त्रुटि_सं.
 */
पूर्णांक usb_ep_set_wedge(काष्ठा usb_ep *ep)
अणु
	पूर्णांक ret;

	अगर (ep->ops->set_wedge)
		ret = ep->ops->set_wedge(ep);
	अन्यथा
		ret = ep->ops->set_halt(ep, 1);

	trace_usb_ep_set_wedge(ep, ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_ep_set_wedge);

/**
 * usb_ep_fअगरo_status - वापसs number of bytes in fअगरo, or error
 * @ep: the endpoपूर्णांक whose fअगरo status is being checked.
 *
 * FIFO endpoपूर्णांकs may have "unclaimed data" in them in certain हालs,
 * such as after पातed transfers.  Hosts may not have collected all
 * the IN data written by the gadget driver (and reported by a request
 * completion).  The gadget driver may not have collected all the data
 * written OUT to it by the host.  Drivers that need precise handling क्रम
 * fault reporting or recovery may need to use this call.
 *
 * This routine may be called in पूर्णांकerrupt context.
 *
 * This वापसs the number of such bytes in the fअगरo, or a negative
 * त्रुटि_सं अगर the endpoपूर्णांक करोesn't use a FIFO or doesn't support such
 * precise handling.
 */
पूर्णांक usb_ep_fअगरo_status(काष्ठा usb_ep *ep)
अणु
	पूर्णांक ret;

	अगर (ep->ops->fअगरo_status)
		ret = ep->ops->fअगरo_status(ep);
	अन्यथा
		ret = -EOPNOTSUPP;

	trace_usb_ep_fअगरo_status(ep, ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_ep_fअगरo_status);

/**
 * usb_ep_fअगरo_flush - flushes contents of a fअगरo
 * @ep: the endpoपूर्णांक whose fअगरo is being flushed.
 *
 * This call may be used to flush the "unclaimed data" that may exist in
 * an endpoपूर्णांक fअगरo after abnormal transaction terminations.  The call
 * must never be used except when endpoपूर्णांक is not being used क्रम any
 * protocol translation.
 *
 * This routine may be called in पूर्णांकerrupt context.
 */
व्योम usb_ep_fअगरo_flush(काष्ठा usb_ep *ep)
अणु
	अगर (ep->ops->fअगरo_flush)
		ep->ops->fअगरo_flush(ep);

	trace_usb_ep_fअगरo_flush(ep, 0);
पूर्ण
EXPORT_SYMBOL_GPL(usb_ep_fअगरo_flush);

/* ------------------------------------------------------------------------- */

/**
 * usb_gadget_frame_number - वापसs the current frame number
 * @gadget: controller that reports the frame number
 *
 * Returns the usb frame number, normally eleven bits from a SOF packet,
 * or negative त्रुटि_सं अगर this device करोesn't support this capability.
 */
पूर्णांक usb_gadget_frame_number(काष्ठा usb_gadget *gadget)
अणु
	पूर्णांक ret;

	ret = gadget->ops->get_frame(gadget);

	trace_usb_gadget_frame_number(gadget, ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_gadget_frame_number);

/**
 * usb_gadget_wakeup - tries to wake up the host connected to this gadget
 * @gadget: controller used to wake up the host
 *
 * Returns zero on success, अन्यथा negative error code अगर the hardware
 * करोesn't support such attempts, or its support has not been enabled
 * by the usb host.  Drivers must वापस device descriptors that report
 * their ability to support this, or hosts won't enable it.
 *
 * This may also try to use SRP to wake the host and start क्रमागतeration,
 * even अगर OTG isn't otherwise in use.  OTG devices may also start
 * remote wakeup even when hosts करोn't explicitly enable it.
 */
पूर्णांक usb_gadget_wakeup(काष्ठा usb_gadget *gadget)
अणु
	पूर्णांक ret = 0;

	अगर (!gadget->ops->wakeup) अणु
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	ret = gadget->ops->wakeup(gadget);

out:
	trace_usb_gadget_wakeup(gadget, ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_gadget_wakeup);

/**
 * usb_gadget_set_selfघातered - sets the device selfघातered feature.
 * @gadget:the device being declared as self-घातered
 *
 * this affects the device status reported by the hardware driver
 * to reflect that it now has a local घातer supply.
 *
 * वापसs zero on success, अन्यथा negative त्रुटि_सं.
 */
पूर्णांक usb_gadget_set_selfघातered(काष्ठा usb_gadget *gadget)
अणु
	पूर्णांक ret = 0;

	अगर (!gadget->ops->set_selfघातered) अणु
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	ret = gadget->ops->set_selfघातered(gadget, 1);

out:
	trace_usb_gadget_set_selfघातered(gadget, ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_gadget_set_selfघातered);

/**
 * usb_gadget_clear_selfघातered - clear the device selfघातered feature.
 * @gadget:the device being declared as bus-घातered
 *
 * this affects the device status reported by the hardware driver.
 * some hardware may not support bus-घातered operation, in which
 * हाल this feature's value can never change.
 *
 * वापसs zero on success, अन्यथा negative त्रुटि_सं.
 */
पूर्णांक usb_gadget_clear_selfघातered(काष्ठा usb_gadget *gadget)
अणु
	पूर्णांक ret = 0;

	अगर (!gadget->ops->set_selfघातered) अणु
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	ret = gadget->ops->set_selfघातered(gadget, 0);

out:
	trace_usb_gadget_clear_selfघातered(gadget, ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_gadget_clear_selfघातered);

/**
 * usb_gadget_vbus_connect - Notअगरy controller that VBUS is घातered
 * @gadget:The device which now has VBUS घातer.
 * Context: can sleep
 *
 * This call is used by a driver क्रम an बाह्यal transceiver (or GPIO)
 * that detects a VBUS घातer session starting.  Common responses include
 * resuming the controller, activating the D+ (or D-) pullup to let the
 * host detect that a USB device is attached, and starting to draw घातer
 * (8mA or possibly more, especially after SET_CONFIGURATION).
 *
 * Returns zero on success, अन्यथा negative त्रुटि_सं.
 */
पूर्णांक usb_gadget_vbus_connect(काष्ठा usb_gadget *gadget)
अणु
	पूर्णांक ret = 0;

	अगर (!gadget->ops->vbus_session) अणु
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	ret = gadget->ops->vbus_session(gadget, 1);

out:
	trace_usb_gadget_vbus_connect(gadget, ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_gadget_vbus_connect);

/**
 * usb_gadget_vbus_draw - स्थिरrain controller's VBUS घातer usage
 * @gadget:The device whose VBUS usage is being described
 * @mA:How much current to draw, in milliAmperes.  This should be twice
 *	the value listed in the configuration descriptor bMaxPower field.
 *
 * This call is used by gadget drivers during SET_CONFIGURATION calls,
 * reporting how much घातer the device may consume.  For example, this
 * could affect how quickly batteries are reअक्षरged.
 *
 * Returns zero on success, अन्यथा negative त्रुटि_सं.
 */
पूर्णांक usb_gadget_vbus_draw(काष्ठा usb_gadget *gadget, अचिन्हित mA)
अणु
	पूर्णांक ret = 0;

	अगर (!gadget->ops->vbus_draw) अणु
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	ret = gadget->ops->vbus_draw(gadget, mA);
	अगर (!ret)
		gadget->mA = mA;

out:
	trace_usb_gadget_vbus_draw(gadget, ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_gadget_vbus_draw);

/**
 * usb_gadget_vbus_disconnect - notअगरy controller about VBUS session end
 * @gadget:the device whose VBUS supply is being described
 * Context: can sleep
 *
 * This call is used by a driver क्रम an बाह्यal transceiver (or GPIO)
 * that detects a VBUS घातer session ending.  Common responses include
 * reversing everything करोne in usb_gadget_vbus_connect().
 *
 * Returns zero on success, अन्यथा negative त्रुटि_सं.
 */
पूर्णांक usb_gadget_vbus_disconnect(काष्ठा usb_gadget *gadget)
अणु
	पूर्णांक ret = 0;

	अगर (!gadget->ops->vbus_session) अणु
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	ret = gadget->ops->vbus_session(gadget, 0);

out:
	trace_usb_gadget_vbus_disconnect(gadget, ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_gadget_vbus_disconnect);

/**
 * usb_gadget_connect - software-controlled connect to USB host
 * @gadget:the peripheral being connected
 *
 * Enables the D+ (or potentially D-) pullup.  The host will start
 * क्रमागतerating this gadget when the pullup is active and a VBUS session
 * is active (the link is घातered).
 *
 * Returns zero on success, अन्यथा negative त्रुटि_सं.
 */
पूर्णांक usb_gadget_connect(काष्ठा usb_gadget *gadget)
अणु
	पूर्णांक ret = 0;

	अगर (!gadget->ops->pullup) अणु
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	अगर (gadget->deactivated) अणु
		/*
		 * If gadget is deactivated we only save new state.
		 * Gadget will be connected स्वतःmatically after activation.
		 */
		gadget->connected = true;
		जाओ out;
	पूर्ण

	ret = gadget->ops->pullup(gadget, 1);
	अगर (!ret)
		gadget->connected = 1;

out:
	trace_usb_gadget_connect(gadget, ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_gadget_connect);

/**
 * usb_gadget_disconnect - software-controlled disconnect from USB host
 * @gadget:the peripheral being disconnected
 *
 * Disables the D+ (or potentially D-) pullup, which the host may see
 * as a disconnect (when a VBUS session is active).  Not all प्रणालीs
 * support software pullup controls.
 *
 * Following a successful disconnect, invoke the ->disconnect() callback
 * क्रम the current gadget driver so that UDC drivers करोn't need to.
 *
 * Returns zero on success, अन्यथा negative त्रुटि_सं.
 */
पूर्णांक usb_gadget_disconnect(काष्ठा usb_gadget *gadget)
अणु
	पूर्णांक ret = 0;

	अगर (!gadget->ops->pullup) अणु
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	अगर (!gadget->connected)
		जाओ out;

	अगर (gadget->deactivated) अणु
		/*
		 * If gadget is deactivated we only save new state.
		 * Gadget will stay disconnected after activation.
		 */
		gadget->connected = false;
		जाओ out;
	पूर्ण

	ret = gadget->ops->pullup(gadget, 0);
	अगर (!ret) अणु
		gadget->connected = 0;
		gadget->udc->driver->disconnect(gadget);
	पूर्ण

out:
	trace_usb_gadget_disconnect(gadget, ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_gadget_disconnect);

/**
 * usb_gadget_deactivate - deactivate function which is not पढ़ोy to work
 * @gadget: the peripheral being deactivated
 *
 * This routine may be used during the gadget driver bind() call to prevent
 * the peripheral from ever being visible to the USB host, unless later
 * usb_gadget_activate() is called.  For example, user mode components may
 * need to be activated beक्रमe the प्रणाली can talk to hosts.
 *
 * Returns zero on success, अन्यथा negative त्रुटि_सं.
 */
पूर्णांक usb_gadget_deactivate(काष्ठा usb_gadget *gadget)
अणु
	पूर्णांक ret = 0;

	अगर (gadget->deactivated)
		जाओ out;

	अगर (gadget->connected) अणु
		ret = usb_gadget_disconnect(gadget);
		अगर (ret)
			जाओ out;

		/*
		 * If gadget was being connected beक्रमe deactivation, we want
		 * to reconnect it in usb_gadget_activate().
		 */
		gadget->connected = true;
	पूर्ण
	gadget->deactivated = true;

out:
	trace_usb_gadget_deactivate(gadget, ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_gadget_deactivate);

/**
 * usb_gadget_activate - activate function which is not पढ़ोy to work
 * @gadget: the peripheral being activated
 *
 * This routine activates gadget which was previously deactivated with
 * usb_gadget_deactivate() call. It calls usb_gadget_connect() अगर needed.
 *
 * Returns zero on success, अन्यथा negative त्रुटि_सं.
 */
पूर्णांक usb_gadget_activate(काष्ठा usb_gadget *gadget)
अणु
	पूर्णांक ret = 0;

	अगर (!gadget->deactivated)
		जाओ out;

	gadget->deactivated = false;

	/*
	 * If gadget has been connected beक्रमe deactivation, or became connected
	 * जबतक it was being deactivated, we call usb_gadget_connect().
	 */
	अगर (gadget->connected)
		ret = usb_gadget_connect(gadget);

out:
	trace_usb_gadget_activate(gadget, ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_gadget_activate);

/* ------------------------------------------------------------------------- */

#अगर_घोषित	CONFIG_HAS_DMA

पूर्णांक usb_gadget_map_request_by_dev(काष्ठा device *dev,
		काष्ठा usb_request *req, पूर्णांक is_in)
अणु
	अगर (req->length == 0)
		वापस 0;

	अगर (req->num_sgs) अणु
		पूर्णांक     mapped;

		mapped = dma_map_sg(dev, req->sg, req->num_sgs,
				is_in ? DMA_TO_DEVICE : DMA_FROM_DEVICE);
		अगर (mapped == 0) अणु
			dev_err(dev, "failed to map SGs\n");
			वापस -EFAULT;
		पूर्ण

		req->num_mapped_sgs = mapped;
	पूर्ण अन्यथा अणु
		अगर (is_vदो_स्मृति_addr(req->buf)) अणु
			dev_err(dev, "buffer is not dma capable\n");
			वापस -EFAULT;
		पूर्ण अन्यथा अगर (object_is_on_stack(req->buf)) अणु
			dev_err(dev, "buffer is on stack\n");
			वापस -EFAULT;
		पूर्ण

		req->dma = dma_map_single(dev, req->buf, req->length,
				is_in ? DMA_TO_DEVICE : DMA_FROM_DEVICE);

		अगर (dma_mapping_error(dev, req->dma)) अणु
			dev_err(dev, "failed to map buffer\n");
			वापस -EFAULT;
		पूर्ण

		req->dma_mapped = 1;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(usb_gadget_map_request_by_dev);

पूर्णांक usb_gadget_map_request(काष्ठा usb_gadget *gadget,
		काष्ठा usb_request *req, पूर्णांक is_in)
अणु
	वापस usb_gadget_map_request_by_dev(gadget->dev.parent, req, is_in);
पूर्ण
EXPORT_SYMBOL_GPL(usb_gadget_map_request);

व्योम usb_gadget_unmap_request_by_dev(काष्ठा device *dev,
		काष्ठा usb_request *req, पूर्णांक is_in)
अणु
	अगर (req->length == 0)
		वापस;

	अगर (req->num_mapped_sgs) अणु
		dma_unmap_sg(dev, req->sg, req->num_sgs,
				is_in ? DMA_TO_DEVICE : DMA_FROM_DEVICE);

		req->num_mapped_sgs = 0;
	पूर्ण अन्यथा अगर (req->dma_mapped) अणु
		dma_unmap_single(dev, req->dma, req->length,
				is_in ? DMA_TO_DEVICE : DMA_FROM_DEVICE);
		req->dma_mapped = 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(usb_gadget_unmap_request_by_dev);

व्योम usb_gadget_unmap_request(काष्ठा usb_gadget *gadget,
		काष्ठा usb_request *req, पूर्णांक is_in)
अणु
	usb_gadget_unmap_request_by_dev(gadget->dev.parent, req, is_in);
पूर्ण
EXPORT_SYMBOL_GPL(usb_gadget_unmap_request);

#पूर्ण_अगर	/* CONFIG_HAS_DMA */

/* ------------------------------------------------------------------------- */

/**
 * usb_gadget_giveback_request - give the request back to the gadget layer
 * @ep: the endpoपूर्णांक to be used with with the request
 * @req: the request being given back
 *
 * This is called by device controller drivers in order to वापस the
 * completed request back to the gadget layer.
 */
व्योम usb_gadget_giveback_request(काष्ठा usb_ep *ep,
		काष्ठा usb_request *req)
अणु
	अगर (likely(req->status == 0))
		usb_led_activity(USB_LED_EVENT_GADGET);

	trace_usb_gadget_giveback_request(ep, req, 0);

	req->complete(ep, req);
पूर्ण
EXPORT_SYMBOL_GPL(usb_gadget_giveback_request);

/* ------------------------------------------------------------------------- */

/**
 * gadget_find_ep_by_name - वापसs ep whose name is the same as sting passed
 *	in second parameter or शून्य अगर searched endpoपूर्णांक not found
 * @g: controller to check क्रम quirk
 * @name: name of searched endpoपूर्णांक
 */
काष्ठा usb_ep *gadget_find_ep_by_name(काष्ठा usb_gadget *g, स्थिर अक्षर *name)
अणु
	काष्ठा usb_ep *ep;

	gadget_क्रम_each_ep(ep, g) अणु
		अगर (!म_भेद(ep->name, name))
			वापस ep;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(gadget_find_ep_by_name);

/* ------------------------------------------------------------------------- */

पूर्णांक usb_gadget_ep_match_desc(काष्ठा usb_gadget *gadget,
		काष्ठा usb_ep *ep, काष्ठा usb_endpoपूर्णांक_descriptor *desc,
		काष्ठा usb_ss_ep_comp_descriptor *ep_comp)
अणु
	u8		type;
	u16		max;
	पूर्णांक		num_req_streams = 0;

	/* endpoपूर्णांक alपढ़ोy claimed? */
	अगर (ep->claimed)
		वापस 0;

	type = usb_endpoपूर्णांक_type(desc);
	max = usb_endpoपूर्णांक_maxp(desc);

	अगर (usb_endpoपूर्णांक_dir_in(desc) && !ep->caps.dir_in)
		वापस 0;
	अगर (usb_endpoपूर्णांक_dir_out(desc) && !ep->caps.dir_out)
		वापस 0;

	अगर (max > ep->maxpacket_limit)
		वापस 0;

	/* "high bandwidth" works only at high speed */
	अगर (!gadget_is_dualspeed(gadget) && usb_endpoपूर्णांक_maxp_mult(desc) > 1)
		वापस 0;

	चयन (type) अणु
	हाल USB_ENDPOINT_XFER_CONTROL:
		/* only support ep0 क्रम portable CONTROL traffic */
		वापस 0;
	हाल USB_ENDPOINT_XFER_ISOC:
		अगर (!ep->caps.type_iso)
			वापस 0;
		/* ISO:  limit 1023 bytes full speed, 1024 high/super speed */
		अगर (!gadget_is_dualspeed(gadget) && max > 1023)
			वापस 0;
		अवरोध;
	हाल USB_ENDPOINT_XFER_BULK:
		अगर (!ep->caps.type_bulk)
			वापस 0;
		अगर (ep_comp && gadget_is_superspeed(gadget)) अणु
			/* Get the number of required streams from the
			 * EP companion descriptor and see अगर the EP
			 * matches it
			 */
			num_req_streams = ep_comp->bmAttributes & 0x1f;
			अगर (num_req_streams > ep->max_streams)
				वापस 0;
		पूर्ण
		अवरोध;
	हाल USB_ENDPOINT_XFER_INT:
		/* Bulk endpoपूर्णांकs handle पूर्णांकerrupt transfers,
		 * except the toggle-quirky iso-synch kind
		 */
		अगर (!ep->caps.type_पूर्णांक && !ep->caps.type_bulk)
			वापस 0;
		/* INT:  limit 64 bytes full speed, 1024 high/super speed */
		अगर (!gadget_is_dualspeed(gadget) && max > 64)
			वापस 0;
		अवरोध;
	पूर्ण

	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(usb_gadget_ep_match_desc);

/* ------------------------------------------------------------------------- */

अटल व्योम usb_gadget_state_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा usb_gadget *gadget = work_to_gadget(work);
	काष्ठा usb_udc *udc = gadget->udc;

	अगर (udc)
		sysfs_notअगरy(&udc->dev.kobj, शून्य, "state");
पूर्ण

व्योम usb_gadget_set_state(काष्ठा usb_gadget *gadget,
		क्रमागत usb_device_state state)
अणु
	gadget->state = state;
	schedule_work(&gadget->work);
पूर्ण
EXPORT_SYMBOL_GPL(usb_gadget_set_state);

/* ------------------------------------------------------------------------- */

अटल व्योम usb_udc_connect_control(काष्ठा usb_udc *udc)
अणु
	अगर (udc->vbus)
		usb_gadget_connect(udc->gadget);
	अन्यथा
		usb_gadget_disconnect(udc->gadget);
पूर्ण

/**
 * usb_udc_vbus_handler - updates the udc core vbus status, and try to
 * connect or disconnect gadget
 * @gadget: The gadget which vbus change occurs
 * @status: The vbus status
 *
 * The udc driver calls it when it wants to connect or disconnect gadget
 * according to vbus status.
 */
व्योम usb_udc_vbus_handler(काष्ठा usb_gadget *gadget, bool status)
अणु
	काष्ठा usb_udc *udc = gadget->udc;

	अगर (udc) अणु
		udc->vbus = status;
		usb_udc_connect_control(udc);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(usb_udc_vbus_handler);

/**
 * usb_gadget_udc_reset - notअगरies the udc core that bus reset occurs
 * @gadget: The gadget which bus reset occurs
 * @driver: The gadget driver we want to notअगरy
 *
 * If the udc driver has bus reset handler, it needs to call this when the bus
 * reset occurs, it notअगरies the gadget driver that the bus reset occurs as
 * well as updates gadget state.
 */
व्योम usb_gadget_udc_reset(काष्ठा usb_gadget *gadget,
		काष्ठा usb_gadget_driver *driver)
अणु
	driver->reset(gadget);
	usb_gadget_set_state(gadget, USB_STATE_DEFAULT);
पूर्ण
EXPORT_SYMBOL_GPL(usb_gadget_udc_reset);

/**
 * usb_gadget_udc_start - tells usb device controller to start up
 * @udc: The UDC to be started
 *
 * This call is issued by the UDC Class driver when it's about
 * to रेजिस्टर a gadget driver to the device controller, beक्रमe
 * calling gadget driver's bind() method.
 *
 * It allows the controller to be घातered off until strictly
 * necessary to have it घातered on.
 *
 * Returns zero on success, अन्यथा negative त्रुटि_सं.
 */
अटल अंतरभूत पूर्णांक usb_gadget_udc_start(काष्ठा usb_udc *udc)
अणु
	पूर्णांक ret;

	अगर (udc->started) अणु
		dev_err(&udc->dev, "UDC had already started\n");
		वापस -EBUSY;
	पूर्ण

	ret = udc->gadget->ops->udc_start(udc->gadget, udc->driver);
	अगर (!ret)
		udc->started = true;

	वापस ret;
पूर्ण

/**
 * usb_gadget_udc_stop - tells usb device controller we करोn't need it anymore
 * @udc: The UDC to be stopped
 *
 * This call is issued by the UDC Class driver after calling
 * gadget driver's unbind() method.
 *
 * The details are implementation specअगरic, but it can go as
 * far as घातering off UDC completely and disable its data
 * line pullups.
 */
अटल अंतरभूत व्योम usb_gadget_udc_stop(काष्ठा usb_udc *udc)
अणु
	अगर (!udc->started) अणु
		dev_err(&udc->dev, "UDC had already stopped\n");
		वापस;
	पूर्ण

	udc->gadget->ops->udc_stop(udc->gadget);
	udc->started = false;
पूर्ण

/**
 * usb_gadget_udc_set_speed - tells usb device controller speed supported by
 *    current driver
 * @udc: The device we want to set maximum speed
 * @speed: The maximum speed to allowed to run
 *
 * This call is issued by the UDC Class driver beक्रमe calling
 * usb_gadget_udc_start() in order to make sure that we करोn't try to
 * connect on speeds the gadget driver करोesn't support.
 */
अटल अंतरभूत व्योम usb_gadget_udc_set_speed(काष्ठा usb_udc *udc,
					    क्रमागत usb_device_speed speed)
अणु
	काष्ठा usb_gadget *gadget = udc->gadget;
	क्रमागत usb_device_speed s;

	अगर (speed == USB_SPEED_UNKNOWN)
		s = gadget->max_speed;
	अन्यथा
		s = min(speed, gadget->max_speed);

	अगर (s == USB_SPEED_SUPER_PLUS && gadget->ops->udc_set_ssp_rate)
		gadget->ops->udc_set_ssp_rate(gadget, gadget->max_ssp_rate);
	अन्यथा अगर (gadget->ops->udc_set_speed)
		gadget->ops->udc_set_speed(gadget, s);
पूर्ण

/**
 * usb_udc_release - release the usb_udc काष्ठा
 * @dev: the dev member within usb_udc
 *
 * This is called by driver's core in order to मुक्त memory once the last
 * reference is released.
 */
अटल व्योम usb_udc_release(काष्ठा device *dev)
अणु
	काष्ठा usb_udc *udc;

	udc = container_of(dev, काष्ठा usb_udc, dev);
	dev_dbg(dev, "releasing '%s'\n", dev_name(dev));
	kमुक्त(udc);
पूर्ण

अटल स्थिर काष्ठा attribute_group *usb_udc_attr_groups[];

अटल व्योम usb_udc_nop_release(काष्ठा device *dev)
अणु
	dev_vdbg(dev, "%s\n", __func__);
पूर्ण

/* should be called with udc_lock held */
अटल पूर्णांक check_pending_gadget_drivers(काष्ठा usb_udc *udc)
अणु
	काष्ठा usb_gadget_driver *driver;
	पूर्णांक ret = 0;

	list_क्रम_each_entry(driver, &gadget_driver_pending_list, pending)
		अगर (!driver->udc_name || म_भेद(driver->udc_name,
						dev_name(&udc->dev)) == 0) अणु
			ret = udc_bind_to_driver(udc, driver);
			अगर (ret != -EPROBE_DEFER)
				list_del_init(&driver->pending);
			अवरोध;
		पूर्ण

	वापस ret;
पूर्ण

/**
 * usb_initialize_gadget - initialize a gadget and its embedded काष्ठा device
 * @parent: the parent device to this udc. Usually the controller driver's
 * device.
 * @gadget: the gadget to be initialized.
 * @release: a gadget release function.
 *
 * Returns zero on success, negative त्रुटि_सं otherwise.
 * Calls the gadget release function in the latter हाल.
 */
व्योम usb_initialize_gadget(काष्ठा device *parent, काष्ठा usb_gadget *gadget,
		व्योम (*release)(काष्ठा device *dev))
अणु
	dev_set_name(&gadget->dev, "gadget");
	INIT_WORK(&gadget->work, usb_gadget_state_work);
	gadget->dev.parent = parent;

	अगर (release)
		gadget->dev.release = release;
	अन्यथा
		gadget->dev.release = usb_udc_nop_release;

	device_initialize(&gadget->dev);
पूर्ण
EXPORT_SYMBOL_GPL(usb_initialize_gadget);

/**
 * usb_add_gadget - adds a new gadget to the udc class driver list
 * @gadget: the gadget to be added to the list.
 *
 * Returns zero on success, negative त्रुटि_सं otherwise.
 * Does not करो a final usb_put_gadget() अगर an error occurs.
 */
पूर्णांक usb_add_gadget(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा usb_udc		*udc;
	पूर्णांक			ret = -ENOMEM;

	udc = kzalloc(माप(*udc), GFP_KERNEL);
	अगर (!udc)
		जाओ error;

	device_initialize(&udc->dev);
	udc->dev.release = usb_udc_release;
	udc->dev.class = udc_class;
	udc->dev.groups = usb_udc_attr_groups;
	udc->dev.parent = gadget->dev.parent;
	ret = dev_set_name(&udc->dev, "%s",
			kobject_name(&gadget->dev.parent->kobj));
	अगर (ret)
		जाओ err_put_udc;

	ret = device_add(&gadget->dev);
	अगर (ret)
		जाओ err_put_udc;

	udc->gadget = gadget;
	gadget->udc = udc;

	udc->started = false;

	mutex_lock(&udc_lock);
	list_add_tail(&udc->list, &udc_list);

	ret = device_add(&udc->dev);
	अगर (ret)
		जाओ err_unlist_udc;

	usb_gadget_set_state(gadget, USB_STATE_NOTATTACHED);
	udc->vbus = true;

	/* pick up one of pending gadget drivers */
	ret = check_pending_gadget_drivers(udc);
	अगर (ret)
		जाओ err_del_udc;

	mutex_unlock(&udc_lock);

	वापस 0;

 err_del_udc:
	flush_work(&gadget->work);
	device_del(&udc->dev);

 err_unlist_udc:
	list_del(&udc->list);
	mutex_unlock(&udc_lock);

	device_del(&gadget->dev);

 err_put_udc:
	put_device(&udc->dev);

 error:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_add_gadget);

/**
 * usb_add_gadget_udc_release - adds a new gadget to the udc class driver list
 * @parent: the parent device to this udc. Usually the controller driver's
 * device.
 * @gadget: the gadget to be added to the list.
 * @release: a gadget release function.
 *
 * Returns zero on success, negative त्रुटि_सं otherwise.
 * Calls the gadget release function in the latter हाल.
 */
पूर्णांक usb_add_gadget_udc_release(काष्ठा device *parent, काष्ठा usb_gadget *gadget,
		व्योम (*release)(काष्ठा device *dev))
अणु
	पूर्णांक	ret;

	usb_initialize_gadget(parent, gadget, release);
	ret = usb_add_gadget(gadget);
	अगर (ret)
		usb_put_gadget(gadget);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_add_gadget_udc_release);

/**
 * usb_get_gadget_udc_name - get the name of the first UDC controller
 * This functions वापसs the name of the first UDC controller in the प्रणाली.
 * Please note that this पूर्णांकerface is usefull only क्रम legacy drivers which
 * assume that there is only one UDC controller in the प्रणाली and they need to
 * get its name beक्रमe initialization. There is no guarantee that the UDC
 * of the वापसed name will be still available, when gadget driver रेजिस्टरs
 * itself.
 *
 * Returns poपूर्णांकer to string with UDC controller name on success, शून्य
 * otherwise. Caller should kमुक्त() वापसed string.
 */
अक्षर *usb_get_gadget_udc_name(व्योम)
अणु
	काष्ठा usb_udc *udc;
	अक्षर *name = शून्य;

	/* For now we take the first available UDC */
	mutex_lock(&udc_lock);
	list_क्रम_each_entry(udc, &udc_list, list) अणु
		अगर (!udc->driver) अणु
			name = kstrdup(udc->gadget->name, GFP_KERNEL);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&udc_lock);
	वापस name;
पूर्ण
EXPORT_SYMBOL_GPL(usb_get_gadget_udc_name);

/**
 * usb_add_gadget_udc - adds a new gadget to the udc class driver list
 * @parent: the parent device to this udc. Usually the controller
 * driver's device.
 * @gadget: the gadget to be added to the list
 *
 * Returns zero on success, negative त्रुटि_सं otherwise.
 */
पूर्णांक usb_add_gadget_udc(काष्ठा device *parent, काष्ठा usb_gadget *gadget)
अणु
	वापस usb_add_gadget_udc_release(parent, gadget, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(usb_add_gadget_udc);

अटल व्योम usb_gadget_हटाओ_driver(काष्ठा usb_udc *udc)
अणु
	dev_dbg(&udc->dev, "unregistering UDC driver [%s]\n",
			udc->driver->function);

	kobject_uevent(&udc->dev.kobj, KOBJ_CHANGE);

	usb_gadget_disconnect(udc->gadget);
	अगर (udc->gadget->irq)
		synchronize_irq(udc->gadget->irq);
	udc->driver->unbind(udc->gadget);
	usb_gadget_udc_stop(udc);

	udc->driver = शून्य;
	udc->dev.driver = शून्य;
	udc->gadget->dev.driver = शून्य;
पूर्ण

/**
 * usb_del_gadget - deletes @udc from udc_list
 * @gadget: the gadget to be हटाओd.
 *
 * This will call usb_gadget_unरेजिस्टर_driver() अगर
 * the @udc is still busy.
 * It will not करो a final usb_put_gadget().
 */
व्योम usb_del_gadget(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा usb_udc *udc = gadget->udc;

	अगर (!udc)
		वापस;

	dev_vdbg(gadget->dev.parent, "unregistering gadget\n");

	mutex_lock(&udc_lock);
	list_del(&udc->list);

	अगर (udc->driver) अणु
		काष्ठा usb_gadget_driver *driver = udc->driver;

		usb_gadget_हटाओ_driver(udc);
		list_add(&driver->pending, &gadget_driver_pending_list);
	पूर्ण
	mutex_unlock(&udc_lock);

	kobject_uevent(&udc->dev.kobj, KOBJ_REMOVE);
	flush_work(&gadget->work);
	device_unरेजिस्टर(&udc->dev);
	device_del(&gadget->dev);
पूर्ण
EXPORT_SYMBOL_GPL(usb_del_gadget);

/**
 * usb_del_gadget_udc - deletes @udc from udc_list
 * @gadget: the gadget to be हटाओd.
 *
 * Calls usb_del_gadget() and करोes a final usb_put_gadget().
 */
व्योम usb_del_gadget_udc(काष्ठा usb_gadget *gadget)
अणु
	usb_del_gadget(gadget);
	usb_put_gadget(gadget);
पूर्ण
EXPORT_SYMBOL_GPL(usb_del_gadget_udc);

/* ------------------------------------------------------------------------- */

अटल पूर्णांक udc_bind_to_driver(काष्ठा usb_udc *udc, काष्ठा usb_gadget_driver *driver)
अणु
	पूर्णांक ret;

	dev_dbg(&udc->dev, "registering UDC driver [%s]\n",
			driver->function);

	udc->driver = driver;
	udc->dev.driver = &driver->driver;
	udc->gadget->dev.driver = &driver->driver;

	usb_gadget_udc_set_speed(udc, driver->max_speed);

	ret = driver->bind(udc->gadget, driver);
	अगर (ret)
		जाओ err1;
	ret = usb_gadget_udc_start(udc);
	अगर (ret) अणु
		driver->unbind(udc->gadget);
		जाओ err1;
	पूर्ण
	usb_udc_connect_control(udc);

	kobject_uevent(&udc->dev.kobj, KOBJ_CHANGE);
	वापस 0;
err1:
	अगर (ret != -EISNAM)
		dev_err(&udc->dev, "failed to start %s: %d\n",
			udc->driver->function, ret);
	udc->driver = शून्य;
	udc->dev.driver = शून्य;
	udc->gadget->dev.driver = शून्य;
	वापस ret;
पूर्ण

पूर्णांक usb_gadget_probe_driver(काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा usb_udc		*udc = शून्य;
	पूर्णांक			ret = -ENODEV;

	अगर (!driver || !driver->bind || !driver->setup)
		वापस -EINVAL;

	mutex_lock(&udc_lock);
	अगर (driver->udc_name) अणु
		list_क्रम_each_entry(udc, &udc_list, list) अणु
			ret = म_भेद(driver->udc_name, dev_name(&udc->dev));
			अगर (!ret)
				अवरोध;
		पूर्ण
		अगर (ret)
			ret = -ENODEV;
		अन्यथा अगर (udc->driver)
			ret = -EBUSY;
		अन्यथा
			जाओ found;
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry(udc, &udc_list, list) अणु
			/* For now we take the first one */
			अगर (!udc->driver)
				जाओ found;
		पूर्ण
	पूर्ण

	अगर (!driver->match_existing_only) अणु
		list_add_tail(&driver->pending, &gadget_driver_pending_list);
		pr_info("udc-core: couldn't find an available UDC - added [%s] to list of pending drivers\n",
			driver->function);
		ret = 0;
	पूर्ण

	mutex_unlock(&udc_lock);
	अगर (ret)
		pr_warn("udc-core: couldn't find an available UDC or it's busy\n");
	वापस ret;
found:
	ret = udc_bind_to_driver(udc, driver);
	mutex_unlock(&udc_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_gadget_probe_driver);

पूर्णांक usb_gadget_unरेजिस्टर_driver(काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा usb_udc		*udc = शून्य;
	पूर्णांक			ret = -ENODEV;

	अगर (!driver || !driver->unbind)
		वापस -EINVAL;

	mutex_lock(&udc_lock);
	list_क्रम_each_entry(udc, &udc_list, list) अणु
		अगर (udc->driver == driver) अणु
			usb_gadget_हटाओ_driver(udc);
			usb_gadget_set_state(udc->gadget,
					     USB_STATE_NOTATTACHED);

			/* Maybe there is someone रुकोing क्रम this UDC? */
			check_pending_gadget_drivers(udc);
			/*
			 * For now we ignore bind errors as probably it's
			 * not a valid reason to fail other's gadget unbind
			 */
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret) अणु
		list_del(&driver->pending);
		ret = 0;
	पूर्ण
	mutex_unlock(&udc_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_gadget_unरेजिस्टर_driver);

/* ------------------------------------------------------------------------- */

अटल sमाप_प्रकार srp_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	काष्ठा usb_udc		*udc = container_of(dev, काष्ठा usb_udc, dev);

	अगर (sysfs_streq(buf, "1"))
		usb_gadget_wakeup(udc->gadget);

	वापस n;
पूर्ण
अटल DEVICE_ATTR_WO(srp);

अटल sमाप_प्रकार soft_connect_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	काष्ठा usb_udc		*udc = container_of(dev, काष्ठा usb_udc, dev);
	sमाप_प्रकार			ret;

	mutex_lock(&udc_lock);
	अगर (!udc->driver) अणु
		dev_err(dev, "soft-connect without a gadget driver\n");
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	अगर (sysfs_streq(buf, "connect")) अणु
		usb_gadget_udc_start(udc);
		usb_gadget_connect(udc->gadget);
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "disconnect")) अणु
		usb_gadget_disconnect(udc->gadget);
		usb_gadget_udc_stop(udc);
	पूर्ण अन्यथा अणु
		dev_err(dev, "unsupported command '%s'\n", buf);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = n;
out:
	mutex_unlock(&udc_lock);
	वापस ret;
पूर्ण
अटल DEVICE_ATTR_WO(soft_connect);

अटल sमाप_प्रकार state_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा usb_udc		*udc = container_of(dev, काष्ठा usb_udc, dev);
	काष्ठा usb_gadget	*gadget = udc->gadget;

	वापस प्र_लिखो(buf, "%s\n", usb_state_string(gadget->state));
पूर्ण
अटल DEVICE_ATTR_RO(state);

अटल sमाप_प्रकार function_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा usb_udc		*udc = container_of(dev, काष्ठा usb_udc, dev);
	काष्ठा usb_gadget_driver *drv = udc->driver;

	अगर (!drv || !drv->function)
		वापस 0;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", drv->function);
पूर्ण
अटल DEVICE_ATTR_RO(function);

#घोषणा USB_UDC_SPEED_ATTR(name, param)					\
sमाप_प्रकार name##_show(काष्ठा device *dev,					\
		काष्ठा device_attribute *attr, अक्षर *buf)		\
अणु									\
	काष्ठा usb_udc *udc = container_of(dev, काष्ठा usb_udc, dev);	\
	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n",			\
			usb_speed_string(udc->gadget->param));		\
पूर्ण									\
अटल DEVICE_ATTR_RO(name)

अटल USB_UDC_SPEED_ATTR(current_speed, speed);
अटल USB_UDC_SPEED_ATTR(maximum_speed, max_speed);

#घोषणा USB_UDC_ATTR(name)					\
sमाप_प्रकार name##_show(काष्ठा device *dev,				\
		काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु								\
	काष्ठा usb_udc		*udc = container_of(dev, काष्ठा usb_udc, dev); \
	काष्ठा usb_gadget	*gadget = udc->gadget;		\
								\
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", gadget->name);	\
पूर्ण								\
अटल DEVICE_ATTR_RO(name)

अटल USB_UDC_ATTR(is_otg);
अटल USB_UDC_ATTR(is_a_peripheral);
अटल USB_UDC_ATTR(b_hnp_enable);
अटल USB_UDC_ATTR(a_hnp_support);
अटल USB_UDC_ATTR(a_alt_hnp_support);
अटल USB_UDC_ATTR(is_selfघातered);

अटल काष्ठा attribute *usb_udc_attrs[] = अणु
	&dev_attr_srp.attr,
	&dev_attr_soft_connect.attr,
	&dev_attr_state.attr,
	&dev_attr_function.attr,
	&dev_attr_current_speed.attr,
	&dev_attr_maximum_speed.attr,

	&dev_attr_is_otg.attr,
	&dev_attr_is_a_peripheral.attr,
	&dev_attr_b_hnp_enable.attr,
	&dev_attr_a_hnp_support.attr,
	&dev_attr_a_alt_hnp_support.attr,
	&dev_attr_is_selfघातered.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group usb_udc_attr_group = अणु
	.attrs = usb_udc_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *usb_udc_attr_groups[] = अणु
	&usb_udc_attr_group,
	शून्य,
पूर्ण;

अटल पूर्णांक usb_udc_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा usb_udc		*udc = container_of(dev, काष्ठा usb_udc, dev);
	पूर्णांक			ret;

	ret = add_uevent_var(env, "USB_UDC_NAME=%s", udc->gadget->name);
	अगर (ret) अणु
		dev_err(dev, "failed to add uevent USB_UDC_NAME\n");
		वापस ret;
	पूर्ण

	अगर (udc->driver) अणु
		ret = add_uevent_var(env, "USB_UDC_DRIVER=%s",
				udc->driver->function);
		अगर (ret) अणु
			dev_err(dev, "failed to add uevent USB_UDC_DRIVER\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init usb_udc_init(व्योम)
अणु
	udc_class = class_create(THIS_MODULE, "udc");
	अगर (IS_ERR(udc_class)) अणु
		pr_err("failed to create udc class --> %ld\n",
				PTR_ERR(udc_class));
		वापस PTR_ERR(udc_class);
	पूर्ण

	udc_class->dev_uevent = usb_udc_uevent;
	वापस 0;
पूर्ण
subsys_initcall(usb_udc_init);

अटल व्योम __निकास usb_udc_निकास(व्योम)
अणु
	class_destroy(udc_class);
पूर्ण
module_निकास(usb_udc_निकास);

MODULE_DESCRIPTION("UDC Framework");
MODULE_AUTHOR("Felipe Balbi <balbi@ti.com>");
MODULE_LICENSE("GPL v2");
