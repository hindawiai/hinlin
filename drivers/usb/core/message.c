<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * message.c - synchronous message handling
 *
 * Released under the GPLv2 only.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/pci.h>	/* क्रम scatterlist macros */
#समावेश <linux/usb.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/समयr.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/nls.h>
#समावेश <linux/device.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/usb/cdc.h>
#समावेश <linux/usb/quirks.h>
#समावेश <linux/usb/hcd.h>	/* क्रम usbcore पूर्णांकernals */
#समावेश <linux/usb/of.h>
#समावेश <यंत्र/byteorder.h>

#समावेश "usb.h"

अटल व्योम cancel_async_set_config(काष्ठा usb_device *udev);

काष्ठा api_context अणु
	काष्ठा completion	करोne;
	पूर्णांक			status;
पूर्ण;

अटल व्योम usb_api_blocking_completion(काष्ठा urb *urb)
अणु
	काष्ठा api_context *ctx = urb->context;

	ctx->status = urb->status;
	complete(&ctx->करोne);
पूर्ण


/*
 * Starts urb and रुकोs क्रम completion or समयout. Note that this call
 * is NOT पूर्णांकerruptible. Many device driver i/o requests should be
 * पूर्णांकerruptible and thereक्रमe these drivers should implement their
 * own पूर्णांकerruptible routines.
 */
अटल पूर्णांक usb_start_रुको_urb(काष्ठा urb *urb, पूर्णांक समयout, पूर्णांक *actual_length)
अणु
	काष्ठा api_context ctx;
	अचिन्हित दीर्घ expire;
	पूर्णांक retval;

	init_completion(&ctx.करोne);
	urb->context = &ctx;
	urb->actual_length = 0;
	retval = usb_submit_urb(urb, GFP_NOIO);
	अगर (unlikely(retval))
		जाओ out;

	expire = समयout ? msecs_to_jअगरfies(समयout) : MAX_SCHEDULE_TIMEOUT;
	अगर (!रुको_क्रम_completion_समयout(&ctx.करोne, expire)) अणु
		usb_समाप्त_urb(urb);
		retval = (ctx.status == -ENOENT ? -ETIMEDOUT : ctx.status);

		dev_dbg(&urb->dev->dev,
			"%s timed out on ep%d%s len=%u/%u\n",
			current->comm,
			usb_endpoपूर्णांक_num(&urb->ep->desc),
			usb_urb_dir_in(urb) ? "in" : "out",
			urb->actual_length,
			urb->transfer_buffer_length);
	पूर्ण अन्यथा
		retval = ctx.status;
out:
	अगर (actual_length)
		*actual_length = urb->actual_length;

	usb_मुक्त_urb(urb);
	वापस retval;
पूर्ण

/*-------------------------------------------------------------------*/
/* वापसs status (negative) or length (positive) */
अटल पूर्णांक usb_पूर्णांकernal_control_msg(काष्ठा usb_device *usb_dev,
				    अचिन्हित पूर्णांक pipe,
				    काष्ठा usb_ctrlrequest *cmd,
				    व्योम *data, पूर्णांक len, पूर्णांक समयout)
अणु
	काष्ठा urb *urb;
	पूर्णांक retv;
	पूर्णांक length;

	urb = usb_alloc_urb(0, GFP_NOIO);
	अगर (!urb)
		वापस -ENOMEM;

	usb_fill_control_urb(urb, usb_dev, pipe, (अचिन्हित अक्षर *)cmd, data,
			     len, usb_api_blocking_completion, शून्य);

	retv = usb_start_रुको_urb(urb, समयout, &length);
	अगर (retv < 0)
		वापस retv;
	अन्यथा
		वापस length;
पूर्ण

/**
 * usb_control_msg - Builds a control urb, sends it off and रुकोs क्रम completion
 * @dev: poपूर्णांकer to the usb device to send the message to
 * @pipe: endpoपूर्णांक "pipe" to send the message to
 * @request: USB message request value
 * @requesttype: USB message request type value
 * @value: USB message value
 * @index: USB message index value
 * @data: poपूर्णांकer to the data to send
 * @size: length in bytes of the data to send
 * @समयout: समय in msecs to रुको क्रम the message to complete beक्रमe timing
 *	out (अगर 0 the रुको is क्रमever)
 *
 * Context: task context, might sleep.
 *
 * This function sends a simple control message to a specअगरied endpoपूर्णांक and
 * रुकोs क्रम the message to complete, or समयout.
 *
 * Don't use this function from within an पूर्णांकerrupt context. If you need
 * an asynchronous message, or need to send a message from within पूर्णांकerrupt
 * context, use usb_submit_urb(). If a thपढ़ो in your driver uses this call,
 * make sure your disconnect() method can रुको क्रम it to complete. Since you
 * करोn't have a handle on the URB used, you can't cancel the request.
 *
 * Return: If successful, the number of bytes transferred. Otherwise, a negative
 * error number.
 */
पूर्णांक usb_control_msg(काष्ठा usb_device *dev, अचिन्हित पूर्णांक pipe, __u8 request,
		    __u8 requesttype, __u16 value, __u16 index, व्योम *data,
		    __u16 size, पूर्णांक समयout)
अणु
	काष्ठा usb_ctrlrequest *dr;
	पूर्णांक ret;

	dr = kदो_स्मृति(माप(काष्ठा usb_ctrlrequest), GFP_NOIO);
	अगर (!dr)
		वापस -ENOMEM;

	dr->bRequestType = requesttype;
	dr->bRequest = request;
	dr->wValue = cpu_to_le16(value);
	dr->wIndex = cpu_to_le16(index);
	dr->wLength = cpu_to_le16(size);

	ret = usb_पूर्णांकernal_control_msg(dev, pipe, dr, data, size, समयout);

	/* Linger a bit, prior to the next control message. */
	अगर (dev->quirks & USB_QUIRK_DELAY_CTRL_MSG)
		msleep(200);

	kमुक्त(dr);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_control_msg);

/**
 * usb_control_msg_send - Builds a control "send" message, sends it off and रुकोs क्रम completion
 * @dev: poपूर्णांकer to the usb device to send the message to
 * @endpoपूर्णांक: endpoपूर्णांक to send the message to
 * @request: USB message request value
 * @requesttype: USB message request type value
 * @value: USB message value
 * @index: USB message index value
 * @driver_data: poपूर्णांकer to the data to send
 * @size: length in bytes of the data to send
 * @समयout: समय in msecs to रुको क्रम the message to complete beक्रमe timing
 *	out (अगर 0 the रुको is क्रमever)
 * @memflags: the flags क्रम memory allocation क्रम buffers
 *
 * Context: !in_पूर्णांकerrupt ()
 *
 * This function sends a control message to a specअगरied endpoपूर्णांक that is not
 * expected to fill in a response (i.e. a "send message") and रुकोs क्रम the
 * message to complete, or समयout.
 *
 * Do not use this function from within an पूर्णांकerrupt context. If you need
 * an asynchronous message, or need to send a message from within पूर्णांकerrupt
 * context, use usb_submit_urb(). If a thपढ़ो in your driver uses this call,
 * make sure your disconnect() method can रुको क्रम it to complete. Since you
 * करोn't have a handle on the URB used, you can't cancel the request.
 *
 * The data poपूर्णांकer can be made to a reference on the stack, or anywhere अन्यथा,
 * as it will not be modअगरied at all.  This करोes not have the restriction that
 * usb_control_msg() has where the data poपूर्णांकer must be to dynamically allocated
 * memory (i.e. memory that can be successfully DMAed to a device).
 *
 * Return: If successful, 0 is वापसed, Otherwise, a negative error number.
 */
पूर्णांक usb_control_msg_send(काष्ठा usb_device *dev, __u8 endpoपूर्णांक, __u8 request,
			 __u8 requesttype, __u16 value, __u16 index,
			 स्थिर व्योम *driver_data, __u16 size, पूर्णांक समयout,
			 gfp_t memflags)
अणु
	अचिन्हित पूर्णांक pipe = usb_sndctrlpipe(dev, endpoपूर्णांक);
	पूर्णांक ret;
	u8 *data = शून्य;

	अगर (size) अणु
		data = kmemdup(driver_data, size, memflags);
		अगर (!data)
			वापस -ENOMEM;
	पूर्ण

	ret = usb_control_msg(dev, pipe, request, requesttype, value, index,
			      data, size, समयout);
	kमुक्त(data);

	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(usb_control_msg_send);

/**
 * usb_control_msg_recv - Builds a control "receive" message, sends it off and रुकोs क्रम completion
 * @dev: poपूर्णांकer to the usb device to send the message to
 * @endpoपूर्णांक: endpoपूर्णांक to send the message to
 * @request: USB message request value
 * @requesttype: USB message request type value
 * @value: USB message value
 * @index: USB message index value
 * @driver_data: poपूर्णांकer to the data to be filled in by the message
 * @size: length in bytes of the data to be received
 * @समयout: समय in msecs to रुको क्रम the message to complete beक्रमe timing
 *	out (अगर 0 the रुको is क्रमever)
 * @memflags: the flags क्रम memory allocation क्रम buffers
 *
 * Context: !in_पूर्णांकerrupt ()
 *
 * This function sends a control message to a specअगरied endpoपूर्णांक that is
 * expected to fill in a response (i.e. a "receive message") and रुकोs क्रम the
 * message to complete, or समयout.
 *
 * Do not use this function from within an पूर्णांकerrupt context. If you need
 * an asynchronous message, or need to send a message from within पूर्णांकerrupt
 * context, use usb_submit_urb(). If a thपढ़ो in your driver uses this call,
 * make sure your disconnect() method can रुको क्रम it to complete. Since you
 * करोn't have a handle on the URB used, you can't cancel the request.
 *
 * The data poपूर्णांकer can be made to a reference on the stack, or anywhere अन्यथा
 * that can be successfully written to.  This function करोes not have the
 * restriction that usb_control_msg() has where the data poपूर्णांकer must be to
 * dynamically allocated memory (i.e. memory that can be successfully DMAed to a
 * device).
 *
 * The "whole" message must be properly received from the device in order क्रम
 * this function to be successful.  If a device वापसs less than the expected
 * amount of data, then the function will fail.  Do not use this क्रम messages
 * where a variable amount of data might be वापसed.
 *
 * Return: If successful, 0 is वापसed, Otherwise, a negative error number.
 */
पूर्णांक usb_control_msg_recv(काष्ठा usb_device *dev, __u8 endpoपूर्णांक, __u8 request,
			 __u8 requesttype, __u16 value, __u16 index,
			 व्योम *driver_data, __u16 size, पूर्णांक समयout,
			 gfp_t memflags)
अणु
	अचिन्हित पूर्णांक pipe = usb_rcvctrlpipe(dev, endpoपूर्णांक);
	पूर्णांक ret;
	u8 *data;

	अगर (!size || !driver_data)
		वापस -EINVAL;

	data = kदो_स्मृति(size, memflags);
	अगर (!data)
		वापस -ENOMEM;

	ret = usb_control_msg(dev, pipe, request, requesttype, value, index,
			      data, size, समयout);

	अगर (ret < 0)
		जाओ निकास;

	अगर (ret == size) अणु
		स_नकल(driver_data, data, size);
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = -EREMOTEIO;
	पूर्ण

निकास:
	kमुक्त(data);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_control_msg_recv);

/**
 * usb_पूर्णांकerrupt_msg - Builds an पूर्णांकerrupt urb, sends it off and रुकोs क्रम completion
 * @usb_dev: poपूर्णांकer to the usb device to send the message to
 * @pipe: endpoपूर्णांक "pipe" to send the message to
 * @data: poपूर्णांकer to the data to send
 * @len: length in bytes of the data to send
 * @actual_length: poपूर्णांकer to a location to put the actual length transferred
 *	in bytes
 * @समयout: समय in msecs to रुको क्रम the message to complete beक्रमe
 *	timing out (अगर 0 the रुको is क्रमever)
 *
 * Context: task context, might sleep.
 *
 * This function sends a simple पूर्णांकerrupt message to a specअगरied endpoपूर्णांक and
 * रुकोs क्रम the message to complete, or समयout.
 *
 * Don't use this function from within an पूर्णांकerrupt context. If you need
 * an asynchronous message, or need to send a message from within पूर्णांकerrupt
 * context, use usb_submit_urb() If a thपढ़ो in your driver uses this call,
 * make sure your disconnect() method can रुको क्रम it to complete. Since you
 * करोn't have a handle on the URB used, you can't cancel the request.
 *
 * Return:
 * If successful, 0. Otherwise a negative error number. The number of actual
 * bytes transferred will be stored in the @actual_length parameter.
 */
पूर्णांक usb_पूर्णांकerrupt_msg(काष्ठा usb_device *usb_dev, अचिन्हित पूर्णांक pipe,
		      व्योम *data, पूर्णांक len, पूर्णांक *actual_length, पूर्णांक समयout)
अणु
	वापस usb_bulk_msg(usb_dev, pipe, data, len, actual_length, समयout);
पूर्ण
EXPORT_SYMBOL_GPL(usb_पूर्णांकerrupt_msg);

/**
 * usb_bulk_msg - Builds a bulk urb, sends it off and रुकोs क्रम completion
 * @usb_dev: poपूर्णांकer to the usb device to send the message to
 * @pipe: endpoपूर्णांक "pipe" to send the message to
 * @data: poपूर्णांकer to the data to send
 * @len: length in bytes of the data to send
 * @actual_length: poपूर्णांकer to a location to put the actual length transferred
 *	in bytes
 * @समयout: समय in msecs to रुको क्रम the message to complete beक्रमe
 *	timing out (अगर 0 the रुको is क्रमever)
 *
 * Context: task context, might sleep.
 *
 * This function sends a simple bulk message to a specअगरied endpoपूर्णांक
 * and रुकोs क्रम the message to complete, or समयout.
 *
 * Don't use this function from within an पूर्णांकerrupt context. If you need
 * an asynchronous message, or need to send a message from within पूर्णांकerrupt
 * context, use usb_submit_urb() If a thपढ़ो in your driver uses this call,
 * make sure your disconnect() method can रुको क्रम it to complete. Since you
 * करोn't have a handle on the URB used, you can't cancel the request.
 *
 * Because there is no usb_पूर्णांकerrupt_msg() and no USBDEVFS_INTERRUPT ioctl,
 * users are क्रमced to abuse this routine by using it to submit URBs क्रम
 * पूर्णांकerrupt endpoपूर्णांकs.  We will take the liberty of creating an पूर्णांकerrupt URB
 * (with the शेष पूर्णांकerval) अगर the target is an पूर्णांकerrupt endpoपूर्णांक.
 *
 * Return:
 * If successful, 0. Otherwise a negative error number. The number of actual
 * bytes transferred will be stored in the @actual_length parameter.
 *
 */
पूर्णांक usb_bulk_msg(काष्ठा usb_device *usb_dev, अचिन्हित पूर्णांक pipe,
		 व्योम *data, पूर्णांक len, पूर्णांक *actual_length, पूर्णांक समयout)
अणु
	काष्ठा urb *urb;
	काष्ठा usb_host_endpoपूर्णांक *ep;

	ep = usb_pipe_endpoपूर्णांक(usb_dev, pipe);
	अगर (!ep || len < 0)
		वापस -EINVAL;

	urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!urb)
		वापस -ENOMEM;

	अगर ((ep->desc.bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) ==
			USB_ENDPOINT_XFER_INT) अणु
		pipe = (pipe & ~(3 << 30)) | (PIPE_INTERRUPT << 30);
		usb_fill_पूर्णांक_urb(urb, usb_dev, pipe, data, len,
				usb_api_blocking_completion, शून्य,
				ep->desc.bInterval);
	पूर्ण अन्यथा
		usb_fill_bulk_urb(urb, usb_dev, pipe, data, len,
				usb_api_blocking_completion, शून्य);

	वापस usb_start_रुको_urb(urb, समयout, actual_length);
पूर्ण
EXPORT_SYMBOL_GPL(usb_bulk_msg);

/*-------------------------------------------------------------------*/

अटल व्योम sg_clean(काष्ठा usb_sg_request *io)
अणु
	अगर (io->urbs) अणु
		जबतक (io->entries--)
			usb_मुक्त_urb(io->urbs[io->entries]);
		kमुक्त(io->urbs);
		io->urbs = शून्य;
	पूर्ण
	io->dev = शून्य;
पूर्ण

अटल व्योम sg_complete(काष्ठा urb *urb)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा usb_sg_request *io = urb->context;
	पूर्णांक status = urb->status;

	spin_lock_irqsave(&io->lock, flags);

	/* In 2.5 we require hcds' endpoपूर्णांक queues not to progress after fault
	 * reports, until the completion callback (this!) वापसs.  That lets
	 * device driver code (like this routine) unlink queued urbs first,
	 * अगर it needs to, since the HC won't work on them at all.  So it's
	 * not possible क्रम page N+1 to overग_लिखो page N, and so on.
	 *
	 * That's only क्रम "hard" faults; "soft" faults (unlinks) someबार
	 * complete beक्रमe the HCD can get requests away from hardware,
	 * though never during cleanup after a hard fault.
	 */
	अगर (io->status
			&& (io->status != -ECONNRESET
				|| status != -ECONNRESET)
			&& urb->actual_length) अणु
		dev_err(io->dev->bus->controller,
			"dev %s ep%d%s scatterlist error %d/%d\n",
			io->dev->devpath,
			usb_endpoपूर्णांक_num(&urb->ep->desc),
			usb_urb_dir_in(urb) ? "in" : "out",
			status, io->status);
		/* BUG (); */
	पूर्ण

	अगर (io->status == 0 && status && status != -ECONNRESET) अणु
		पूर्णांक i, found, retval;

		io->status = status;

		/* the previous urbs, and this one, completed alपढ़ोy.
		 * unlink pending urbs so they won't rx/tx bad data.
		 * careful: unlink can someबार be synchronous...
		 */
		spin_unlock_irqrestore(&io->lock, flags);
		क्रम (i = 0, found = 0; i < io->entries; i++) अणु
			अगर (!io->urbs[i])
				जारी;
			अगर (found) अणु
				usb_block_urb(io->urbs[i]);
				retval = usb_unlink_urb(io->urbs[i]);
				अगर (retval != -EINPROGRESS &&
				    retval != -ENODEV &&
				    retval != -EBUSY &&
				    retval != -EIDRM)
					dev_err(&io->dev->dev,
						"%s, unlink --> %d\n",
						__func__, retval);
			पूर्ण अन्यथा अगर (urb == io->urbs[i])
				found = 1;
		पूर्ण
		spin_lock_irqsave(&io->lock, flags);
	पूर्ण

	/* on the last completion, संकेत usb_sg_रुको() */
	io->bytes += urb->actual_length;
	io->count--;
	अगर (!io->count)
		complete(&io->complete);

	spin_unlock_irqrestore(&io->lock, flags);
पूर्ण


/**
 * usb_sg_init - initializes scatterlist-based bulk/पूर्णांकerrupt I/O request
 * @io: request block being initialized.  until usb_sg_रुको() वापसs,
 *	treat this as a poपूर्णांकer to an opaque block of memory,
 * @dev: the usb device that will send or receive the data
 * @pipe: endpoपूर्णांक "pipe" used to transfer the data
 * @period: polling rate क्रम पूर्णांकerrupt endpoपूर्णांकs, in frames or
 * 	(क्रम high speed endpoपूर्णांकs) microframes; ignored क्रम bulk
 * @sg: scatterlist entries
 * @nents: how many entries in the scatterlist
 * @length: how many bytes to send from the scatterlist, or zero to
 * 	send every byte identअगरied in the list.
 * @mem_flags: SLAB_* flags affecting memory allocations in this call
 *
 * This initializes a scatter/gather request, allocating resources such as
 * I/O mappings and urb memory (except maybe memory used by USB controller
 * drivers).
 *
 * The request must be issued using usb_sg_रुको(), which रुकोs क्रम the I/O to
 * complete (or to be canceled) and then cleans up all resources allocated by
 * usb_sg_init().
 *
 * The request may be canceled with usb_sg_cancel(), either beक्रमe or after
 * usb_sg_रुको() is called.
 *
 * Return: Zero क्रम success, अन्यथा a negative त्रुटि_सं value.
 */
पूर्णांक usb_sg_init(काष्ठा usb_sg_request *io, काष्ठा usb_device *dev,
		अचिन्हित pipe, अचिन्हित	period, काष्ठा scatterlist *sg,
		पूर्णांक nents, माप_प्रकार length, gfp_t mem_flags)
अणु
	पूर्णांक i;
	पूर्णांक urb_flags;
	पूर्णांक use_sg;

	अगर (!io || !dev || !sg
			|| usb_pipecontrol(pipe)
			|| usb_pipeisoc(pipe)
			|| nents <= 0)
		वापस -EINVAL;

	spin_lock_init(&io->lock);
	io->dev = dev;
	io->pipe = pipe;

	अगर (dev->bus->sg_tablesize > 0) अणु
		use_sg = true;
		io->entries = 1;
	पूर्ण अन्यथा अणु
		use_sg = false;
		io->entries = nents;
	पूर्ण

	/* initialize all the urbs we'll use */
	io->urbs = kदो_स्मृति_array(io->entries, माप(*io->urbs), mem_flags);
	अगर (!io->urbs)
		जाओ nomem;

	urb_flags = URB_NO_INTERRUPT;
	अगर (usb_pipein(pipe))
		urb_flags |= URB_SHORT_NOT_OK;

	क्रम_each_sg(sg, sg, io->entries, i) अणु
		काष्ठा urb *urb;
		अचिन्हित len;

		urb = usb_alloc_urb(0, mem_flags);
		अगर (!urb) अणु
			io->entries = i;
			जाओ nomem;
		पूर्ण
		io->urbs[i] = urb;

		urb->dev = शून्य;
		urb->pipe = pipe;
		urb->पूर्णांकerval = period;
		urb->transfer_flags = urb_flags;
		urb->complete = sg_complete;
		urb->context = io;
		urb->sg = sg;

		अगर (use_sg) अणु
			/* There is no single transfer buffer */
			urb->transfer_buffer = शून्य;
			urb->num_sgs = nents;

			/* A length of zero means transfer the whole sg list */
			len = length;
			अगर (len == 0) अणु
				काष्ठा scatterlist	*sg2;
				पूर्णांक			j;

				क्रम_each_sg(sg, sg2, nents, j)
					len += sg2->length;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * Some प्रणालीs can't use DMA; they use PIO instead.
			 * For their sakes, transfer_buffer is set whenever
			 * possible.
			 */
			अगर (!PageHighMem(sg_page(sg)))
				urb->transfer_buffer = sg_virt(sg);
			अन्यथा
				urb->transfer_buffer = शून्य;

			len = sg->length;
			अगर (length) अणु
				len = min_t(माप_प्रकार, len, length);
				length -= len;
				अगर (length == 0)
					io->entries = i + 1;
			पूर्ण
		पूर्ण
		urb->transfer_buffer_length = len;
	पूर्ण
	io->urbs[--i]->transfer_flags &= ~URB_NO_INTERRUPT;

	/* transaction state */
	io->count = io->entries;
	io->status = 0;
	io->bytes = 0;
	init_completion(&io->complete);
	वापस 0;

nomem:
	sg_clean(io);
	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL_GPL(usb_sg_init);

/**
 * usb_sg_रुको - synchronously execute scatter/gather request
 * @io: request block handle, as initialized with usb_sg_init().
 * 	some fields become accessible when this call वापसs.
 *
 * Context: task context, might sleep.
 *
 * This function blocks until the specअगरied I/O operation completes.  It
 * leverages the grouping of the related I/O requests to get good transfer
 * rates, by queueing the requests.  At higher speeds, such queuing can
 * signअगरicantly improve USB throughput.
 *
 * There are three kinds of completion क्रम this function.
 *
 * (1) success, where io->status is zero.  The number of io->bytes
 *     transferred is as requested.
 * (2) error, where io->status is a negative त्रुटि_सं value.  The number
 *     of io->bytes transferred beक्रमe the error is usually less
 *     than requested, and can be nonzero.
 * (3) cancellation, a type of error with status -ECONNRESET that
 *     is initiated by usb_sg_cancel().
 *
 * When this function वापसs, all memory allocated through usb_sg_init() or
 * this call will have been मुक्तd.  The request block parameter may still be
 * passed to usb_sg_cancel(), or it may be मुक्तd.  It could also be
 * reinitialized and then reused.
 *
 * Data Transfer Rates:
 *
 * Bulk transfers are valid क्रम full or high speed endpoपूर्णांकs.
 * The best full speed data rate is 19 packets of 64 bytes each
 * per frame, or 1216 bytes per millisecond.
 * The best high speed data rate is 13 packets of 512 bytes each
 * per microframe, or 52 KBytes per millisecond.
 *
 * The reason to use पूर्णांकerrupt transfers through this API would most likely
 * be to reserve high speed bandwidth, where up to 24 KBytes per millisecond
 * could be transferred.  That capability is less useful क्रम low or full
 * speed पूर्णांकerrupt endpoपूर्णांकs, which allow at most one packet per millisecond,
 * of at most 8 or 64 bytes (respectively).
 *
 * It is not necessary to call this function to reserve bandwidth क्रम devices
 * under an xHCI host controller, as the bandwidth is reserved when the
 * configuration or पूर्णांकerface alt setting is selected.
 */
व्योम usb_sg_रुको(काष्ठा usb_sg_request *io)
अणु
	पूर्णांक i;
	पूर्णांक entries = io->entries;

	/* queue the urbs.  */
	spin_lock_irq(&io->lock);
	i = 0;
	जबतक (i < entries && !io->status) अणु
		पूर्णांक retval;

		io->urbs[i]->dev = io->dev;
		spin_unlock_irq(&io->lock);

		retval = usb_submit_urb(io->urbs[i], GFP_NOIO);

		चयन (retval) अणु
			/* maybe we retrying will recover */
		हाल -ENXIO:	/* hc didn't queue this one */
		हाल -EAGAIN:
		हाल -ENOMEM:
			retval = 0;
			yield();
			अवरोध;

			/* no error? जारी immediately.
			 *
			 * NOTE: to work better with UHCI (4K I/O buffer may
			 * need 3K of TDs) it may be good to limit how many
			 * URBs are queued at once; N milliseconds?
			 */
		हाल 0:
			++i;
			cpu_relax();
			अवरोध;

			/* fail any uncompleted urbs */
		शेष:
			io->urbs[i]->status = retval;
			dev_dbg(&io->dev->dev, "%s, submit --> %d\n",
				__func__, retval);
			usb_sg_cancel(io);
		पूर्ण
		spin_lock_irq(&io->lock);
		अगर (retval && (io->status == 0 || io->status == -ECONNRESET))
			io->status = retval;
	पूर्ण
	io->count -= entries - i;
	अगर (io->count == 0)
		complete(&io->complete);
	spin_unlock_irq(&io->lock);

	/* OK, yes, this could be packaged as non-blocking.
	 * So could the submit loop above ... but it's easier to
	 * solve neither problem than to solve both!
	 */
	रुको_क्रम_completion(&io->complete);

	sg_clean(io);
पूर्ण
EXPORT_SYMBOL_GPL(usb_sg_रुको);

/**
 * usb_sg_cancel - stop scatter/gather i/o issued by usb_sg_रुको()
 * @io: request block, initialized with usb_sg_init()
 *
 * This stops a request after it has been started by usb_sg_रुको().
 * It can also prevents one initialized by usb_sg_init() from starting,
 * so that call just मुक्तs resources allocated to the request.
 */
व्योम usb_sg_cancel(काष्ठा usb_sg_request *io)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i, retval;

	spin_lock_irqsave(&io->lock, flags);
	अगर (io->status || io->count == 0) अणु
		spin_unlock_irqrestore(&io->lock, flags);
		वापस;
	पूर्ण
	/* shut everything करोwn */
	io->status = -ECONNRESET;
	io->count++;		/* Keep the request alive until we're करोne */
	spin_unlock_irqrestore(&io->lock, flags);

	क्रम (i = io->entries - 1; i >= 0; --i) अणु
		usb_block_urb(io->urbs[i]);

		retval = usb_unlink_urb(io->urbs[i]);
		अगर (retval != -EINPROGRESS
		    && retval != -ENODEV
		    && retval != -EBUSY
		    && retval != -EIDRM)
			dev_warn(&io->dev->dev, "%s, unlink --> %d\n",
				 __func__, retval);
	पूर्ण

	spin_lock_irqsave(&io->lock, flags);
	io->count--;
	अगर (!io->count)
		complete(&io->complete);
	spin_unlock_irqrestore(&io->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(usb_sg_cancel);

/*-------------------------------------------------------------------*/

/**
 * usb_get_descriptor - issues a generic GET_DESCRIPTOR request
 * @dev: the device whose descriptor is being retrieved
 * @type: the descriptor type (USB_DT_*)
 * @index: the number of the descriptor
 * @buf: where to put the descriptor
 * @size: how big is "buf"?
 *
 * Context: task context, might sleep.
 *
 * Gets a USB descriptor.  Convenience functions exist to simplअगरy
 * getting some types of descriptors.  Use
 * usb_get_string() or usb_string() क्रम USB_DT_STRING.
 * Device (USB_DT_DEVICE) and configuration descriptors (USB_DT_CONFIG)
 * are part of the device काष्ठाure.
 * In addition to a number of USB-standard descriptors, some
 * devices also use class-specअगरic or venकरोr-specअगरic descriptors.
 *
 * This call is synchronous, and may not be used in an पूर्णांकerrupt context.
 *
 * Return: The number of bytes received on success, or अन्यथा the status code
 * वापसed by the underlying usb_control_msg() call.
 */
पूर्णांक usb_get_descriptor(काष्ठा usb_device *dev, अचिन्हित अक्षर type,
		       अचिन्हित अक्षर index, व्योम *buf, पूर्णांक size)
अणु
	पूर्णांक i;
	पूर्णांक result;

	स_रखो(buf, 0, size);	/* Make sure we parse really received data */

	क्रम (i = 0; i < 3; ++i) अणु
		/* retry on length 0 or error; some devices are flakey */
		result = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
				USB_REQ_GET_DESCRIPTOR, USB_सूची_IN,
				(type << 8) + index, 0, buf, size,
				USB_CTRL_GET_TIMEOUT);
		अगर (result <= 0 && result != -ETIMEDOUT)
			जारी;
		अगर (result > 1 && ((u8 *)buf)[1] != type) अणु
			result = -ENODATA;
			जारी;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(usb_get_descriptor);

/**
 * usb_get_string - माला_लो a string descriptor
 * @dev: the device whose string descriptor is being retrieved
 * @langid: code क्रम language chosen (from string descriptor zero)
 * @index: the number of the descriptor
 * @buf: where to put the string
 * @size: how big is "buf"?
 *
 * Context: task context, might sleep.
 *
 * Retrieves a string, encoded using UTF-16LE (Unicode, 16 bits per अक्षरacter,
 * in little-endian byte order).
 * The usb_string() function will often be a convenient way to turn
 * these strings पूर्णांकo kernel-prपूर्णांकable क्रमm.
 *
 * Strings may be referenced in device, configuration, पूर्णांकerface, or other
 * descriptors, and could also be used in venकरोr-specअगरic ways.
 *
 * This call is synchronous, and may not be used in an पूर्णांकerrupt context.
 *
 * Return: The number of bytes received on success, or अन्यथा the status code
 * वापसed by the underlying usb_control_msg() call.
 */
अटल पूर्णांक usb_get_string(काष्ठा usb_device *dev, अचिन्हित लघु langid,
			  अचिन्हित अक्षर index, व्योम *buf, पूर्णांक size)
अणु
	पूर्णांक i;
	पूर्णांक result;

	क्रम (i = 0; i < 3; ++i) अणु
		/* retry on length 0 or stall; some devices are flakey */
		result = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
			USB_REQ_GET_DESCRIPTOR, USB_सूची_IN,
			(USB_DT_STRING << 8) + index, langid, buf, size,
			USB_CTRL_GET_TIMEOUT);
		अगर (result == 0 || result == -EPIPE)
			जारी;
		अगर (result > 1 && ((u8 *) buf)[1] != USB_DT_STRING) अणु
			result = -ENODATA;
			जारी;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस result;
पूर्ण

अटल व्योम usb_try_string_workarounds(अचिन्हित अक्षर *buf, पूर्णांक *length)
अणु
	पूर्णांक newlength, oldlength = *length;

	क्रम (newlength = 2; newlength + 1 < oldlength; newlength += 2)
		अगर (!है_छाप(buf[newlength]) || buf[newlength + 1])
			अवरोध;

	अगर (newlength > 2) अणु
		buf[0] = newlength;
		*length = newlength;
	पूर्ण
पूर्ण

अटल पूर्णांक usb_string_sub(काष्ठा usb_device *dev, अचिन्हित पूर्णांक langid,
			  अचिन्हित पूर्णांक index, अचिन्हित अक्षर *buf)
अणु
	पूर्णांक rc;

	/* Try to पढ़ो the string descriptor by asking क्रम the maximum
	 * possible number of bytes */
	अगर (dev->quirks & USB_QUIRK_STRING_FETCH_255)
		rc = -EIO;
	अन्यथा
		rc = usb_get_string(dev, langid, index, buf, 255);

	/* If that failed try to पढ़ो the descriptor length, then
	 * ask क्रम just that many bytes */
	अगर (rc < 2) अणु
		rc = usb_get_string(dev, langid, index, buf, 2);
		अगर (rc == 2)
			rc = usb_get_string(dev, langid, index, buf, buf[0]);
	पूर्ण

	अगर (rc >= 2) अणु
		अगर (!buf[0] && !buf[1])
			usb_try_string_workarounds(buf, &rc);

		/* There might be extra junk at the end of the descriptor */
		अगर (buf[0] < rc)
			rc = buf[0];

		rc = rc - (rc & 1); /* क्रमce a multiple of two */
	पूर्ण

	अगर (rc < 2)
		rc = (rc < 0 ? rc : -EINVAL);

	वापस rc;
पूर्ण

अटल पूर्णांक usb_get_langid(काष्ठा usb_device *dev, अचिन्हित अक्षर *tbuf)
अणु
	पूर्णांक err;

	अगर (dev->have_langid)
		वापस 0;

	अगर (dev->string_langid < 0)
		वापस -EPIPE;

	err = usb_string_sub(dev, 0, 0, tbuf);

	/* If the string was reported but is malक्रमmed, शेष to english
	 * (0x0409) */
	अगर (err == -ENODATA || (err > 0 && err < 4)) अणु
		dev->string_langid = 0x0409;
		dev->have_langid = 1;
		dev_err(&dev->dev,
			"language id specifier not provided by device, defaulting to English\n");
		वापस 0;
	पूर्ण

	/* In हाल of all other errors, we assume the device is not able to
	 * deal with strings at all. Set string_langid to -1 in order to
	 * prevent any string to be retrieved from the device */
	अगर (err < 0) अणु
		dev_info(&dev->dev, "string descriptor 0 read error: %d\n",
					err);
		dev->string_langid = -1;
		वापस -EPIPE;
	पूर्ण

	/* always use the first langid listed */
	dev->string_langid = tbuf[2] | (tbuf[3] << 8);
	dev->have_langid = 1;
	dev_dbg(&dev->dev, "default language 0x%04x\n",
				dev->string_langid);
	वापस 0;
पूर्ण

/**
 * usb_string - वापसs UTF-8 version of a string descriptor
 * @dev: the device whose string descriptor is being retrieved
 * @index: the number of the descriptor
 * @buf: where to put the string
 * @size: how big is "buf"?
 *
 * Context: task context, might sleep.
 *
 * This converts the UTF-16LE encoded strings वापसed by devices, from
 * usb_get_string_descriptor(), to null-terminated UTF-8 encoded ones
 * that are more usable in most kernel contexts.  Note that this function
 * chooses strings in the first language supported by the device.
 *
 * This call is synchronous, and may not be used in an पूर्णांकerrupt context.
 *
 * Return: length of the string (>= 0) or usb_control_msg status (< 0).
 */
पूर्णांक usb_string(काष्ठा usb_device *dev, पूर्णांक index, अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित अक्षर *tbuf;
	पूर्णांक err;

	अगर (dev->state == USB_STATE_SUSPENDED)
		वापस -EHOSTUNREACH;
	अगर (size <= 0 || !buf)
		वापस -EINVAL;
	buf[0] = 0;
	अगर (index <= 0 || index >= 256)
		वापस -EINVAL;
	tbuf = kदो_स्मृति(256, GFP_NOIO);
	अगर (!tbuf)
		वापस -ENOMEM;

	err = usb_get_langid(dev, tbuf);
	अगर (err < 0)
		जाओ errout;

	err = usb_string_sub(dev, dev->string_langid, index, tbuf);
	अगर (err < 0)
		जाओ errout;

	size--;		/* leave room क्रम trailing शून्य अक्षर in output buffer */
	err = utf16s_to_utf8s((ब_अक्षर_प्रकार *) &tbuf[2], (err - 2) / 2,
			UTF16_LITTLE_ENDIAN, buf, size);
	buf[err] = 0;

	अगर (tbuf[1] != USB_DT_STRING)
		dev_dbg(&dev->dev,
			"wrong descriptor type %02x for string %d (\"%s\")\n",
			tbuf[1], index, buf);

 errout:
	kमुक्त(tbuf);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(usb_string);

/* one UTF-8-encoded 16-bit अक्षरacter has at most three bytes */
#घोषणा MAX_USB_STRING_SIZE (127 * 3 + 1)

/**
 * usb_cache_string - पढ़ो a string descriptor and cache it क्रम later use
 * @udev: the device whose string descriptor is being पढ़ो
 * @index: the descriptor index
 *
 * Return: A poपूर्णांकer to a kदो_स्मृति'ed buffer containing the descriptor string,
 * or %शून्य अगर the index is 0 or the string could not be पढ़ो.
 */
अक्षर *usb_cache_string(काष्ठा usb_device *udev, पूर्णांक index)
अणु
	अक्षर *buf;
	अक्षर *smallbuf = शून्य;
	पूर्णांक len;

	अगर (index <= 0)
		वापस शून्य;

	buf = kदो_स्मृति(MAX_USB_STRING_SIZE, GFP_NOIO);
	अगर (buf) अणु
		len = usb_string(udev, index, buf, MAX_USB_STRING_SIZE);
		अगर (len > 0) अणु
			smallbuf = kदो_स्मृति(++len, GFP_NOIO);
			अगर (!smallbuf)
				वापस buf;
			स_नकल(smallbuf, buf, len);
		पूर्ण
		kमुक्त(buf);
	पूर्ण
	वापस smallbuf;
पूर्ण

/*
 * usb_get_device_descriptor - (re)पढ़ोs the device descriptor (usbcore)
 * @dev: the device whose device descriptor is being updated
 * @size: how much of the descriptor to पढ़ो
 *
 * Context: task context, might sleep.
 *
 * Updates the copy of the device descriptor stored in the device काष्ठाure,
 * which dedicates space क्रम this purpose.
 *
 * Not exported, only क्रम use by the core.  If drivers really want to पढ़ो
 * the device descriptor directly, they can call usb_get_descriptor() with
 * type = USB_DT_DEVICE and index = 0.
 *
 * This call is synchronous, and may not be used in an पूर्णांकerrupt context.
 *
 * Return: The number of bytes received on success, or अन्यथा the status code
 * वापसed by the underlying usb_control_msg() call.
 */
पूर्णांक usb_get_device_descriptor(काष्ठा usb_device *dev, अचिन्हित पूर्णांक size)
अणु
	काष्ठा usb_device_descriptor *desc;
	पूर्णांक ret;

	अगर (size > माप(*desc))
		वापस -EINVAL;
	desc = kदो_स्मृति(माप(*desc), GFP_NOIO);
	अगर (!desc)
		वापस -ENOMEM;

	ret = usb_get_descriptor(dev, USB_DT_DEVICE, 0, desc, size);
	अगर (ret >= 0)
		स_नकल(&dev->descriptor, desc, size);
	kमुक्त(desc);
	वापस ret;
पूर्ण

/*
 * usb_set_isoch_delay - inक्रमms the device of the packet transmit delay
 * @dev: the device whose delay is to be inक्रमmed
 * Context: task context, might sleep
 *
 * Since this is an optional request, we करोn't bother अगर it fails.
 */
पूर्णांक usb_set_isoch_delay(काष्ठा usb_device *dev)
अणु
	/* skip hub devices */
	अगर (dev->descriptor.bDeviceClass == USB_CLASS_HUB)
		वापस 0;

	/* skip non-SS/non-SSP devices */
	अगर (dev->speed < USB_SPEED_SUPER)
		वापस 0;

	वापस usb_control_msg_send(dev, 0,
			USB_REQ_SET_ISOCH_DELAY,
			USB_सूची_OUT | USB_TYPE_STANDARD | USB_RECIP_DEVICE,
			dev->hub_delay, 0, शून्य, 0,
			USB_CTRL_SET_TIMEOUT,
			GFP_NOIO);
पूर्ण

/**
 * usb_get_status - issues a GET_STATUS call
 * @dev: the device whose status is being checked
 * @recip: USB_RECIP_*; क्रम device, पूर्णांकerface, or endpoपूर्णांक
 * @type: USB_STATUS_TYPE_*; क्रम standard or PTM status types
 * @target: zero (क्रम device), अन्यथा पूर्णांकerface or endpoपूर्णांक number
 * @data: poपूर्णांकer to two bytes of biपंचांगap data
 *
 * Context: task context, might sleep.
 *
 * Returns device, पूर्णांकerface, or endpoपूर्णांक status.  Normally only of
 * पूर्णांकerest to see अगर the device is self घातered, or has enabled the
 * remote wakeup facility; or whether a bulk or पूर्णांकerrupt endpoपूर्णांक
 * is halted ("stalled").
 *
 * Bits in these status biपंचांगaps are set using the SET_FEATURE request,
 * and cleared using the CLEAR_FEATURE request.  The usb_clear_halt()
 * function should be used to clear halt ("stall") status.
 *
 * This call is synchronous, and may not be used in an पूर्णांकerrupt context.
 *
 * Returns 0 and the status value in *@data (in host byte order) on success,
 * or अन्यथा the status code from the underlying usb_control_msg() call.
 */
पूर्णांक usb_get_status(काष्ठा usb_device *dev, पूर्णांक recip, पूर्णांक type, पूर्णांक target,
		व्योम *data)
अणु
	पूर्णांक ret;
	व्योम *status;
	पूर्णांक length;

	चयन (type) अणु
	हाल USB_STATUS_TYPE_STANDARD:
		length = 2;
		अवरोध;
	हाल USB_STATUS_TYPE_PTM:
		अगर (recip != USB_RECIP_DEVICE)
			वापस -EINVAL;

		length = 4;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	status =  kदो_स्मृति(length, GFP_KERNEL);
	अगर (!status)
		वापस -ENOMEM;

	ret = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
		USB_REQ_GET_STATUS, USB_सूची_IN | recip, USB_STATUS_TYPE_STANDARD,
		target, status, length, USB_CTRL_GET_TIMEOUT);

	चयन (ret) अणु
	हाल 4:
		अगर (type != USB_STATUS_TYPE_PTM) अणु
			ret = -EIO;
			अवरोध;
		पूर्ण

		*(u32 *) data = le32_to_cpu(*(__le32 *) status);
		ret = 0;
		अवरोध;
	हाल 2:
		अगर (type != USB_STATUS_TYPE_STANDARD) अणु
			ret = -EIO;
			अवरोध;
		पूर्ण

		*(u16 *) data = le16_to_cpu(*(__le16 *) status);
		ret = 0;
		अवरोध;
	शेष:
		ret = -EIO;
	पूर्ण

	kमुक्त(status);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_get_status);

/**
 * usb_clear_halt - tells device to clear endpoपूर्णांक halt/stall condition
 * @dev: device whose endpoपूर्णांक is halted
 * @pipe: endpoपूर्णांक "pipe" being cleared
 *
 * Context: task context, might sleep.
 *
 * This is used to clear halt conditions क्रम bulk and पूर्णांकerrupt endpoपूर्णांकs,
 * as reported by URB completion status.  Endpoपूर्णांकs that are halted are
 * someबार referred to as being "stalled".  Such endpoपूर्णांकs are unable
 * to transmit or receive data until the halt status is cleared.  Any URBs
 * queued क्रम such an endpoपूर्णांक should normally be unlinked by the driver
 * beक्रमe clearing the halt condition, as described in sections 5.7.5
 * and 5.8.5 of the USB 2.0 spec.
 *
 * Note that control and isochronous endpoपूर्णांकs करोn't halt, although control
 * endpoपूर्णांकs report "protocol stall" (क्रम unsupported requests) using the
 * same status code used to report a true stall.
 *
 * This call is synchronous, and may not be used in an पूर्णांकerrupt context.
 *
 * Return: Zero on success, or अन्यथा the status code वापसed by the
 * underlying usb_control_msg() call.
 */
पूर्णांक usb_clear_halt(काष्ठा usb_device *dev, पूर्णांक pipe)
अणु
	पूर्णांक result;
	पूर्णांक endp = usb_pipeendpoपूर्णांक(pipe);

	अगर (usb_pipein(pipe))
		endp |= USB_सूची_IN;

	/* we करोn't care if it wasn't halted first. in fact some devices
	 * (like some ibmcam model 1 units) seem to expect hosts to make
	 * this request क्रम iso endpoपूर्णांकs, which can't halt!
	 */
	result = usb_control_msg_send(dev, 0,
				      USB_REQ_CLEAR_FEATURE, USB_RECIP_ENDPOINT,
				      USB_ENDPOINT_HALT, endp, शून्य, 0,
				      USB_CTRL_SET_TIMEOUT, GFP_NOIO);

	/* करोn't un-halt or क्रमce to DATA0 except on success */
	अगर (result)
		वापस result;

	/* NOTE:  seems like Microsoft and Apple करोn't bother verअगरying
	 * the clear "took", so some devices could lock up अगर you check...
	 * such as the Hagiwara FlashGate DUAL.  So we won't bother.
	 *
	 * NOTE:  make sure the logic here करोesn't भागerge much from
	 * the copy in usb-storage, क्रम as दीर्घ as we need two copies.
	 */

	usb_reset_endpoपूर्णांक(dev, endp);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(usb_clear_halt);

अटल पूर्णांक create_पूर्णांकf_ep_devs(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा usb_host_पूर्णांकerface *alt = पूर्णांकf->cur_altsetting;
	पूर्णांक i;

	अगर (पूर्णांकf->ep_devs_created || पूर्णांकf->unरेजिस्टरing)
		वापस 0;

	क्रम (i = 0; i < alt->desc.bNumEndpoपूर्णांकs; ++i)
		(व्योम) usb_create_ep_devs(&पूर्णांकf->dev, &alt->endpoपूर्णांक[i], udev);
	पूर्णांकf->ep_devs_created = 1;
	वापस 0;
पूर्ण

अटल व्योम हटाओ_पूर्णांकf_ep_devs(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_host_पूर्णांकerface *alt = पूर्णांकf->cur_altsetting;
	पूर्णांक i;

	अगर (!पूर्णांकf->ep_devs_created)
		वापस;

	क्रम (i = 0; i < alt->desc.bNumEndpoपूर्णांकs; ++i)
		usb_हटाओ_ep_devs(&alt->endpoपूर्णांक[i]);
	पूर्णांकf->ep_devs_created = 0;
पूर्ण

/**
 * usb_disable_endpoपूर्णांक -- Disable an endpoपूर्णांक by address
 * @dev: the device whose endpoपूर्णांक is being disabled
 * @epaddr: the endpoपूर्णांक's address.  Endpoपूर्णांक number क्रम output,
 *	endpoपूर्णांक number + USB_सूची_IN क्रम input
 * @reset_hardware: flag to erase any endpoपूर्णांक state stored in the
 *	controller hardware
 *
 * Disables the endpoपूर्णांक क्रम URB submission and nukes all pending URBs.
 * If @reset_hardware is set then also deallocates hcd/hardware state
 * क्रम the endpoपूर्णांक.
 */
व्योम usb_disable_endpoपूर्णांक(काष्ठा usb_device *dev, अचिन्हित पूर्णांक epaddr,
		bool reset_hardware)
अणु
	अचिन्हित पूर्णांक epnum = epaddr & USB_ENDPOINT_NUMBER_MASK;
	काष्ठा usb_host_endpoपूर्णांक *ep;

	अगर (!dev)
		वापस;

	अगर (usb_endpoपूर्णांक_out(epaddr)) अणु
		ep = dev->ep_out[epnum];
		अगर (reset_hardware && epnum != 0)
			dev->ep_out[epnum] = शून्य;
	पूर्ण अन्यथा अणु
		ep = dev->ep_in[epnum];
		अगर (reset_hardware && epnum != 0)
			dev->ep_in[epnum] = शून्य;
	पूर्ण
	अगर (ep) अणु
		ep->enabled = 0;
		usb_hcd_flush_endpoपूर्णांक(dev, ep);
		अगर (reset_hardware)
			usb_hcd_disable_endpoपूर्णांक(dev, ep);
	पूर्ण
पूर्ण

/**
 * usb_reset_endpoपूर्णांक - Reset an endpoपूर्णांक's state.
 * @dev: the device whose endpoपूर्णांक is to be reset
 * @epaddr: the endpoपूर्णांक's address.  Endpoपूर्णांक number क्रम output,
 *	endpoपूर्णांक number + USB_सूची_IN क्रम input
 *
 * Resets any host-side endpoपूर्णांक state such as the toggle bit,
 * sequence number or current winकरोw.
 */
व्योम usb_reset_endpoपूर्णांक(काष्ठा usb_device *dev, अचिन्हित पूर्णांक epaddr)
अणु
	अचिन्हित पूर्णांक epnum = epaddr & USB_ENDPOINT_NUMBER_MASK;
	काष्ठा usb_host_endpoपूर्णांक *ep;

	अगर (usb_endpoपूर्णांक_out(epaddr))
		ep = dev->ep_out[epnum];
	अन्यथा
		ep = dev->ep_in[epnum];
	अगर (ep)
		usb_hcd_reset_endpoपूर्णांक(dev, ep);
पूर्ण
EXPORT_SYMBOL_GPL(usb_reset_endpoपूर्णांक);


/**
 * usb_disable_पूर्णांकerface -- Disable all endpoपूर्णांकs क्रम an पूर्णांकerface
 * @dev: the device whose पूर्णांकerface is being disabled
 * @पूर्णांकf: poपूर्णांकer to the पूर्णांकerface descriptor
 * @reset_hardware: flag to erase any endpoपूर्णांक state stored in the
 *	controller hardware
 *
 * Disables all the endpoपूर्णांकs क्रम the पूर्णांकerface's current altsetting.
 */
व्योम usb_disable_पूर्णांकerface(काष्ठा usb_device *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		bool reset_hardware)
अणु
	काष्ठा usb_host_पूर्णांकerface *alt = पूर्णांकf->cur_altsetting;
	पूर्णांक i;

	क्रम (i = 0; i < alt->desc.bNumEndpoपूर्णांकs; ++i) अणु
		usb_disable_endpoपूर्णांक(dev,
				alt->endpoपूर्णांक[i].desc.bEndpoपूर्णांकAddress,
				reset_hardware);
	पूर्ण
पूर्ण

/*
 * usb_disable_device_endpoपूर्णांकs -- Disable all endpoपूर्णांकs क्रम a device
 * @dev: the device whose endpoपूर्णांकs are being disabled
 * @skip_ep0: 0 to disable endpoपूर्णांक 0, 1 to skip it.
 */
अटल व्योम usb_disable_device_endpoपूर्णांकs(काष्ठा usb_device *dev, पूर्णांक skip_ep0)
अणु
	काष्ठा usb_hcd *hcd = bus_to_hcd(dev->bus);
	पूर्णांक i;

	अगर (hcd->driver->check_bandwidth) अणु
		/* First pass: Cancel URBs, leave endpoपूर्णांक poपूर्णांकers पूर्णांकact. */
		क्रम (i = skip_ep0; i < 16; ++i) अणु
			usb_disable_endpoपूर्णांक(dev, i, false);
			usb_disable_endpoपूर्णांक(dev, i + USB_सूची_IN, false);
		पूर्ण
		/* Remove endpoपूर्णांकs from the host controller पूर्णांकernal state */
		mutex_lock(hcd->bandwidth_mutex);
		usb_hcd_alloc_bandwidth(dev, शून्य, शून्य, शून्य);
		mutex_unlock(hcd->bandwidth_mutex);
	पूर्ण
	/* Second pass: हटाओ endpoपूर्णांक poपूर्णांकers */
	क्रम (i = skip_ep0; i < 16; ++i) अणु
		usb_disable_endpoपूर्णांक(dev, i, true);
		usb_disable_endpoपूर्णांक(dev, i + USB_सूची_IN, true);
	पूर्ण
पूर्ण

/**
 * usb_disable_device - Disable all the endpoपूर्णांकs क्रम a USB device
 * @dev: the device whose endpoपूर्णांकs are being disabled
 * @skip_ep0: 0 to disable endpoपूर्णांक 0, 1 to skip it.
 *
 * Disables all the device's endpoपूर्णांकs, potentially including endpoपूर्णांक 0.
 * Deallocates hcd/hardware state क्रम the endpoपूर्णांकs (nuking all or most
 * pending urbs) and usbcore state क्रम the पूर्णांकerfaces, so that usbcore
 * must usb_set_configuration() beक्रमe any पूर्णांकerfaces could be used.
 */
व्योम usb_disable_device(काष्ठा usb_device *dev, पूर्णांक skip_ep0)
अणु
	पूर्णांक i;

	/* getting rid of पूर्णांकerfaces will disconnect
	 * any drivers bound to them (a key side effect)
	 */
	अगर (dev->actconfig) अणु
		/*
		 * FIXME: In order to aव्योम self-deadlock involving the
		 * bandwidth_mutex, we have to mark all the पूर्णांकerfaces
		 * beक्रमe unरेजिस्टरing any of them.
		 */
		क्रम (i = 0; i < dev->actconfig->desc.bNumInterfaces; i++)
			dev->actconfig->पूर्णांकerface[i]->unरेजिस्टरing = 1;

		क्रम (i = 0; i < dev->actconfig->desc.bNumInterfaces; i++) अणु
			काष्ठा usb_पूर्णांकerface	*पूर्णांकerface;

			/* हटाओ this पूर्णांकerface अगर it has been रेजिस्टरed */
			पूर्णांकerface = dev->actconfig->पूर्णांकerface[i];
			अगर (!device_is_रेजिस्टरed(&पूर्णांकerface->dev))
				जारी;
			dev_dbg(&dev->dev, "unregistering interface %s\n",
				dev_name(&पूर्णांकerface->dev));
			हटाओ_पूर्णांकf_ep_devs(पूर्णांकerface);
			device_del(&पूर्णांकerface->dev);
		पूर्ण

		/* Now that the पूर्णांकerfaces are unbound, nobody should
		 * try to access them.
		 */
		क्रम (i = 0; i < dev->actconfig->desc.bNumInterfaces; i++) अणु
			put_device(&dev->actconfig->पूर्णांकerface[i]->dev);
			dev->actconfig->पूर्णांकerface[i] = शून्य;
		पूर्ण

		usb_disable_usb2_hardware_lpm(dev);
		usb_unlocked_disable_lpm(dev);
		usb_disable_lपंचांग(dev);

		dev->actconfig = शून्य;
		अगर (dev->state == USB_STATE_CONFIGURED)
			usb_set_device_state(dev, USB_STATE_ADDRESS);
	पूर्ण

	dev_dbg(&dev->dev, "%s nuking %s URBs\n", __func__,
		skip_ep0 ? "non-ep0" : "all");

	usb_disable_device_endpoपूर्णांकs(dev, skip_ep0);
पूर्ण

/**
 * usb_enable_endpoपूर्णांक - Enable an endpoपूर्णांक क्रम USB communications
 * @dev: the device whose पूर्णांकerface is being enabled
 * @ep: the endpoपूर्णांक
 * @reset_ep: flag to reset the endpoपूर्णांक state
 *
 * Resets the endpoपूर्णांक state अगर asked, and sets dev->ep_अणुin,outपूर्ण poपूर्णांकers.
 * For control endpoपूर्णांकs, both the input and output sides are handled.
 */
व्योम usb_enable_endpoपूर्णांक(काष्ठा usb_device *dev, काष्ठा usb_host_endpoपूर्णांक *ep,
		bool reset_ep)
अणु
	पूर्णांक epnum = usb_endpoपूर्णांक_num(&ep->desc);
	पूर्णांक is_out = usb_endpoपूर्णांक_dir_out(&ep->desc);
	पूर्णांक is_control = usb_endpoपूर्णांक_xfer_control(&ep->desc);

	अगर (reset_ep)
		usb_hcd_reset_endpoपूर्णांक(dev, ep);
	अगर (is_out || is_control)
		dev->ep_out[epnum] = ep;
	अगर (!is_out || is_control)
		dev->ep_in[epnum] = ep;
	ep->enabled = 1;
पूर्ण

/**
 * usb_enable_पूर्णांकerface - Enable all the endpoपूर्णांकs क्रम an पूर्णांकerface
 * @dev: the device whose पूर्णांकerface is being enabled
 * @पूर्णांकf: poपूर्णांकer to the पूर्णांकerface descriptor
 * @reset_eps: flag to reset the endpoपूर्णांकs' state
 *
 * Enables all the endpoपूर्णांकs क्रम the पूर्णांकerface's current altsetting.
 */
व्योम usb_enable_पूर्णांकerface(काष्ठा usb_device *dev,
		काष्ठा usb_पूर्णांकerface *पूर्णांकf, bool reset_eps)
अणु
	काष्ठा usb_host_पूर्णांकerface *alt = पूर्णांकf->cur_altsetting;
	पूर्णांक i;

	क्रम (i = 0; i < alt->desc.bNumEndpoपूर्णांकs; ++i)
		usb_enable_endpoपूर्णांक(dev, &alt->endpoपूर्णांक[i], reset_eps);
पूर्ण

/**
 * usb_set_पूर्णांकerface - Makes a particular alternate setting be current
 * @dev: the device whose पूर्णांकerface is being updated
 * @पूर्णांकerface: the पूर्णांकerface being updated
 * @alternate: the setting being chosen.
 *
 * Context: task context, might sleep.
 *
 * This is used to enable data transfers on पूर्णांकerfaces that may not
 * be enabled by शेष.  Not all devices support such configurability.
 * Only the driver bound to an पूर्णांकerface may change its setting.
 *
 * Within any given configuration, each पूर्णांकerface may have several
 * alternative settings.  These are often used to control levels of
 * bandwidth consumption.  For example, the शेष setting क्रम a high
 * speed पूर्णांकerrupt endpoपूर्णांक may not send more than 64 bytes per microframe,
 * जबतक पूर्णांकerrupt transfers of up to 3KBytes per microframe are legal.
 * Also, isochronous endpoपूर्णांकs may never be part of an
 * पूर्णांकerface's शेष setting.  To access such bandwidth, alternate
 * पूर्णांकerface settings must be made current.
 *
 * Note that in the Linux USB subप्रणाली, bandwidth associated with
 * an endpoपूर्णांक in a given alternate setting is not reserved until an URB
 * is submitted that needs that bandwidth.  Some other operating प्रणालीs
 * allocate bandwidth early, when a configuration is chosen.
 *
 * xHCI reserves bandwidth and configures the alternate setting in
 * usb_hcd_alloc_bandwidth(). If it fails the original पूर्णांकerface altsetting
 * may be disabled. Drivers cannot rely on any particular alternate
 * setting being in effect after a failure.
 *
 * This call is synchronous, and may not be used in an पूर्णांकerrupt context.
 * Also, drivers must not change altsettings जबतक urbs are scheduled क्रम
 * endpoपूर्णांकs in that पूर्णांकerface; all such urbs must first be completed
 * (perhaps क्रमced by unlinking).
 *
 * Return: Zero on success, or अन्यथा the status code वापसed by the
 * underlying usb_control_msg() call.
 */
पूर्णांक usb_set_पूर्णांकerface(काष्ठा usb_device *dev, पूर्णांक पूर्णांकerface, पूर्णांक alternate)
अणु
	काष्ठा usb_पूर्णांकerface *अगरace;
	काष्ठा usb_host_पूर्णांकerface *alt;
	काष्ठा usb_hcd *hcd = bus_to_hcd(dev->bus);
	पूर्णांक i, ret, manual = 0;
	अचिन्हित पूर्णांक epaddr;
	अचिन्हित पूर्णांक pipe;

	अगर (dev->state == USB_STATE_SUSPENDED)
		वापस -EHOSTUNREACH;

	अगरace = usb_अगरnum_to_अगर(dev, पूर्णांकerface);
	अगर (!अगरace) अणु
		dev_dbg(&dev->dev, "selecting invalid interface %d\n",
			पूर्णांकerface);
		वापस -EINVAL;
	पूर्ण
	अगर (अगरace->unरेजिस्टरing)
		वापस -ENODEV;

	alt = usb_altnum_to_altsetting(अगरace, alternate);
	अगर (!alt) अणु
		dev_warn(&dev->dev, "selecting invalid altsetting %d\n",
			 alternate);
		वापस -EINVAL;
	पूर्ण
	/*
	 * usb3 hosts configure the पूर्णांकerface in usb_hcd_alloc_bandwidth,
	 * including मुक्तing dropped endpoपूर्णांक ring buffers.
	 * Make sure the पूर्णांकerface endpoपूर्णांकs are flushed beक्रमe that
	 */
	usb_disable_पूर्णांकerface(dev, अगरace, false);

	/* Make sure we have enough bandwidth क्रम this alternate पूर्णांकerface.
	 * Remove the current alt setting and add the new alt setting.
	 */
	mutex_lock(hcd->bandwidth_mutex);
	/* Disable LPM, and re-enable it once the new alt setting is installed,
	 * so that the xHCI driver can recalculate the U1/U2 समयouts.
	 */
	अगर (usb_disable_lpm(dev)) अणु
		dev_err(&अगरace->dev, "%s Failed to disable LPM\n", __func__);
		mutex_unlock(hcd->bandwidth_mutex);
		वापस -ENOMEM;
	पूर्ण
	/* Changing alt-setting also मुक्तs any allocated streams */
	क्रम (i = 0; i < अगरace->cur_altsetting->desc.bNumEndpoपूर्णांकs; i++)
		अगरace->cur_altsetting->endpoपूर्णांक[i].streams = 0;

	ret = usb_hcd_alloc_bandwidth(dev, शून्य, अगरace->cur_altsetting, alt);
	अगर (ret < 0) अणु
		dev_info(&dev->dev, "Not enough bandwidth for altsetting %d\n",
				alternate);
		usb_enable_lpm(dev);
		mutex_unlock(hcd->bandwidth_mutex);
		वापस ret;
	पूर्ण

	अगर (dev->quirks & USB_QUIRK_NO_SET_INTF)
		ret = -EPIPE;
	अन्यथा
		ret = usb_control_msg_send(dev, 0,
					   USB_REQ_SET_INTERFACE,
					   USB_RECIP_INTERFACE, alternate,
					   पूर्णांकerface, शून्य, 0, 5000,
					   GFP_NOIO);

	/* 9.4.10 says devices करोn't need this and are मुक्त to STALL the
	 * request अगर the पूर्णांकerface only has one alternate setting.
	 */
	अगर (ret == -EPIPE && अगरace->num_altsetting == 1) अणु
		dev_dbg(&dev->dev,
			"manual set_interface for iface %d, alt %d\n",
			पूर्णांकerface, alternate);
		manual = 1;
	पूर्ण अन्यथा अगर (ret) अणु
		/* Re-instate the old alt setting */
		usb_hcd_alloc_bandwidth(dev, शून्य, alt, अगरace->cur_altsetting);
		usb_enable_lpm(dev);
		mutex_unlock(hcd->bandwidth_mutex);
		वापस ret;
	पूर्ण
	mutex_unlock(hcd->bandwidth_mutex);

	/* FIXME drivers shouldn't need to replicate/bugfix the logic here
	 * when they implement async or easily-समाप्तable versions of this or
	 * other "should-be-internal" functions (like clear_halt).
	 * should hcd+usbcore postprocess control requests?
	 */

	/* prevent submissions using previous endpoपूर्णांक settings */
	अगर (अगरace->cur_altsetting != alt) अणु
		हटाओ_पूर्णांकf_ep_devs(अगरace);
		usb_हटाओ_sysfs_पूर्णांकf_files(अगरace);
	पूर्ण
	usb_disable_पूर्णांकerface(dev, अगरace, true);

	अगरace->cur_altsetting = alt;

	/* Now that the पूर्णांकerface is installed, re-enable LPM. */
	usb_unlocked_enable_lpm(dev);

	/* If the पूर्णांकerface only has one altsetting and the device didn't
	 * accept the request, we attempt to carry out the equivalent action
	 * by manually clearing the HALT feature क्रम each endpoपूर्णांक in the
	 * new altsetting.
	 */
	अगर (manual) अणु
		क्रम (i = 0; i < alt->desc.bNumEndpoपूर्णांकs; i++) अणु
			epaddr = alt->endpoपूर्णांक[i].desc.bEndpoपूर्णांकAddress;
			pipe = __create_pipe(dev,
					USB_ENDPOINT_NUMBER_MASK & epaddr) |
					(usb_endpoपूर्णांक_out(epaddr) ?
					USB_सूची_OUT : USB_सूची_IN);

			usb_clear_halt(dev, pipe);
		पूर्ण
	पूर्ण

	/* 9.1.1.5: reset toggles क्रम all endpoपूर्णांकs in the new altsetting
	 *
	 * Note:
	 * Despite EP0 is always present in all पूर्णांकerfaces/AS, the list of
	 * endpoपूर्णांकs from the descriptor करोes not contain EP0. Due to its
	 * omnipresence one might expect EP0 being considered "affected" by
	 * any SetInterface request and hence assume toggles need to be reset.
	 * However, EP0 toggles are re-synced क्रम every inभागidual transfer
	 * during the SETUP stage - hence EP0 toggles are "don't care" here.
	 * (Likewise, EP0 never "halts" on well deचिन्हित devices.)
	 */
	usb_enable_पूर्णांकerface(dev, अगरace, true);
	अगर (device_is_रेजिस्टरed(&अगरace->dev)) अणु
		usb_create_sysfs_पूर्णांकf_files(अगरace);
		create_पूर्णांकf_ep_devs(अगरace);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(usb_set_पूर्णांकerface);

/**
 * usb_reset_configuration - lightweight device reset
 * @dev: the device whose configuration is being reset
 *
 * This issues a standard SET_CONFIGURATION request to the device using
 * the current configuration.  The effect is to reset most USB-related
 * state in the device, including पूर्णांकerface altsettings (reset to zero),
 * endpoपूर्णांक halts (cleared), and endpoपूर्णांक state (only क्रम bulk and पूर्णांकerrupt
 * endpoपूर्णांकs).  Other usbcore state is unchanged, including bindings of
 * usb device drivers to पूर्णांकerfaces.
 *
 * Because this affects multiple पूर्णांकerfaces, aव्योम using this with composite
 * (multi-पूर्णांकerface) devices.  Instead, the driver क्रम each पूर्णांकerface may
 * use usb_set_पूर्णांकerface() on the पूर्णांकerfaces it claims.  Be careful though;
 * some devices करोn't support the SET_INTERFACE request, and others won't
 * reset all the पूर्णांकerface state (notably endpoपूर्णांक state).  Resetting the whole
 * configuration would affect other drivers' पूर्णांकerfaces.
 *
 * The caller must own the device lock.
 *
 * Return: Zero on success, अन्यथा a negative error code.
 *
 * If this routine fails the device will probably be in an unusable state
 * with endpoपूर्णांकs disabled, and पूर्णांकerfaces only partially enabled.
 */
पूर्णांक usb_reset_configuration(काष्ठा usb_device *dev)
अणु
	पूर्णांक			i, retval;
	काष्ठा usb_host_config	*config;
	काष्ठा usb_hcd *hcd = bus_to_hcd(dev->bus);

	अगर (dev->state == USB_STATE_SUSPENDED)
		वापस -EHOSTUNREACH;

	/* caller must have locked the device and must own
	 * the usb bus पढ़ोlock (so driver bindings are stable);
	 * calls during probe() are fine
	 */

	usb_disable_device_endpoपूर्णांकs(dev, 1); /* skip ep0*/

	config = dev->actconfig;
	retval = 0;
	mutex_lock(hcd->bandwidth_mutex);
	/* Disable LPM, and re-enable it once the configuration is reset, so
	 * that the xHCI driver can recalculate the U1/U2 समयouts.
	 */
	अगर (usb_disable_lpm(dev)) अणु
		dev_err(&dev->dev, "%s Failed to disable LPM\n", __func__);
		mutex_unlock(hcd->bandwidth_mutex);
		वापस -ENOMEM;
	पूर्ण

	/* xHCI adds all endpoपूर्णांकs in usb_hcd_alloc_bandwidth */
	retval = usb_hcd_alloc_bandwidth(dev, config, शून्य, शून्य);
	अगर (retval < 0) अणु
		usb_enable_lpm(dev);
		mutex_unlock(hcd->bandwidth_mutex);
		वापस retval;
	पूर्ण
	retval = usb_control_msg_send(dev, 0, USB_REQ_SET_CONFIGURATION, 0,
				      config->desc.bConfigurationValue, 0,
				      शून्य, 0, USB_CTRL_SET_TIMEOUT,
				      GFP_NOIO);
	अगर (retval) अणु
		usb_hcd_alloc_bandwidth(dev, शून्य, शून्य, शून्य);
		usb_enable_lpm(dev);
		mutex_unlock(hcd->bandwidth_mutex);
		वापस retval;
	पूर्ण
	mutex_unlock(hcd->bandwidth_mutex);

	/* re-init hc/hcd पूर्णांकerface/endpoपूर्णांक state */
	क्रम (i = 0; i < config->desc.bNumInterfaces; i++) अणु
		काष्ठा usb_पूर्णांकerface *पूर्णांकf = config->पूर्णांकerface[i];
		काष्ठा usb_host_पूर्णांकerface *alt;

		alt = usb_altnum_to_altsetting(पूर्णांकf, 0);

		/* No altsetting 0?  We'll assume the first altsetting.
		 * We could use a GetInterface call, but अगर a device is
		 * so non-compliant that it करोesn't have altsetting 0
		 * then I wouldn't trust its reply anyway.
		 */
		अगर (!alt)
			alt = &पूर्णांकf->altsetting[0];

		अगर (alt != पूर्णांकf->cur_altsetting) अणु
			हटाओ_पूर्णांकf_ep_devs(पूर्णांकf);
			usb_हटाओ_sysfs_पूर्णांकf_files(पूर्णांकf);
		पूर्ण
		पूर्णांकf->cur_altsetting = alt;
		usb_enable_पूर्णांकerface(dev, पूर्णांकf, true);
		अगर (device_is_रेजिस्टरed(&पूर्णांकf->dev)) अणु
			usb_create_sysfs_पूर्णांकf_files(पूर्णांकf);
			create_पूर्णांकf_ep_devs(पूर्णांकf);
		पूर्ण
	पूर्ण
	/* Now that the पूर्णांकerfaces are installed, re-enable LPM. */
	usb_unlocked_enable_lpm(dev);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(usb_reset_configuration);

अटल व्योम usb_release_पूर्णांकerface(काष्ठा device *dev)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा usb_पूर्णांकerface_cache *पूर्णांकfc =
			altsetting_to_usb_पूर्णांकerface_cache(पूर्णांकf->altsetting);

	kref_put(&पूर्णांकfc->ref, usb_release_पूर्णांकerface_cache);
	usb_put_dev(पूर्णांकerface_to_usbdev(पूर्णांकf));
	of_node_put(dev->of_node);
	kमुक्त(पूर्णांकf);
पूर्ण

/*
 * usb_deauthorize_पूर्णांकerface - deauthorize an USB पूर्णांकerface
 *
 * @पूर्णांकf: USB पूर्णांकerface काष्ठाure
 */
व्योम usb_deauthorize_पूर्णांकerface(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा device *dev = &पूर्णांकf->dev;

	device_lock(dev->parent);

	अगर (पूर्णांकf->authorized) अणु
		device_lock(dev);
		पूर्णांकf->authorized = 0;
		device_unlock(dev);

		usb_क्रमced_unbind_पूर्णांकf(पूर्णांकf);
	पूर्ण

	device_unlock(dev->parent);
पूर्ण

/*
 * usb_authorize_पूर्णांकerface - authorize an USB पूर्णांकerface
 *
 * @पूर्णांकf: USB पूर्णांकerface काष्ठाure
 */
व्योम usb_authorize_पूर्णांकerface(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा device *dev = &पूर्णांकf->dev;

	अगर (!पूर्णांकf->authorized) अणु
		device_lock(dev);
		पूर्णांकf->authorized = 1; /* authorize पूर्णांकerface */
		device_unlock(dev);
	पूर्ण
पूर्ण

अटल पूर्णांक usb_अगर_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा usb_device *usb_dev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा usb_host_पूर्णांकerface *alt;

	पूर्णांकf = to_usb_पूर्णांकerface(dev);
	usb_dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	alt = पूर्णांकf->cur_altsetting;

	अगर (add_uevent_var(env, "INTERFACE=%d/%d/%d",
		   alt->desc.bInterfaceClass,
		   alt->desc.bInterfaceSubClass,
		   alt->desc.bInterfaceProtocol))
		वापस -ENOMEM;

	अगर (add_uevent_var(env,
		   "MODALIAS=usb:"
		   "v%04Xp%04Xd%04Xdc%02Xdsc%02Xdp%02Xic%02Xisc%02Xip%02Xin%02X",
		   le16_to_cpu(usb_dev->descriptor.idVenकरोr),
		   le16_to_cpu(usb_dev->descriptor.idProduct),
		   le16_to_cpu(usb_dev->descriptor.bcdDevice),
		   usb_dev->descriptor.bDeviceClass,
		   usb_dev->descriptor.bDeviceSubClass,
		   usb_dev->descriptor.bDeviceProtocol,
		   alt->desc.bInterfaceClass,
		   alt->desc.bInterfaceSubClass,
		   alt->desc.bInterfaceProtocol,
		   alt->desc.bInterfaceNumber))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

काष्ठा device_type usb_अगर_device_type = अणु
	.name =		"usb_interface",
	.release =	usb_release_पूर्णांकerface,
	.uevent =	usb_अगर_uevent,
पूर्ण;

अटल काष्ठा usb_पूर्णांकerface_assoc_descriptor *find_iad(काष्ठा usb_device *dev,
						काष्ठा usb_host_config *config,
						u8 inum)
अणु
	काष्ठा usb_पूर्णांकerface_assoc_descriptor *retval = शून्य;
	काष्ठा usb_पूर्णांकerface_assoc_descriptor *पूर्णांकf_assoc;
	पूर्णांक first_पूर्णांकf;
	पूर्णांक last_पूर्णांकf;
	पूर्णांक i;

	क्रम (i = 0; (i < USB_MAXIADS && config->पूर्णांकf_assoc[i]); i++) अणु
		पूर्णांकf_assoc = config->पूर्णांकf_assoc[i];
		अगर (पूर्णांकf_assoc->bInterfaceCount == 0)
			जारी;

		first_पूर्णांकf = पूर्णांकf_assoc->bFirstInterface;
		last_पूर्णांकf = first_पूर्णांकf + (पूर्णांकf_assoc->bInterfaceCount - 1);
		अगर (inum >= first_पूर्णांकf && inum <= last_पूर्णांकf) अणु
			अगर (!retval)
				retval = पूर्णांकf_assoc;
			अन्यथा
				dev_err(&dev->dev, "Interface #%d referenced"
					" by multiple IADs\n", inum);
		पूर्ण
	पूर्ण

	वापस retval;
पूर्ण


/*
 * Internal function to queue a device reset
 * See usb_queue_reset_device() क्रम more details
 */
अटल व्योम __usb_queue_reset_device(काष्ठा work_काष्ठा *ws)
अणु
	पूर्णांक rc;
	काष्ठा usb_पूर्णांकerface *अगरace =
		container_of(ws, काष्ठा usb_पूर्णांकerface, reset_ws);
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(अगरace);

	rc = usb_lock_device_क्रम_reset(udev, अगरace);
	अगर (rc >= 0) अणु
		usb_reset_device(udev);
		usb_unlock_device(udev);
	पूर्ण
	usb_put_पूर्णांकf(अगरace);	/* Unकरो _get_ in usb_queue_reset_device() */
पूर्ण


/*
 * usb_set_configuration - Makes a particular device setting be current
 * @dev: the device whose configuration is being updated
 * @configuration: the configuration being chosen.
 *
 * Context: task context, might sleep. Caller holds device lock.
 *
 * This is used to enable non-शेष device modes.  Not all devices
 * use this kind of configurability; many devices only have one
 * configuration.
 *
 * @configuration is the value of the configuration to be installed.
 * According to the USB spec (e.g. section 9.1.1.5), configuration values
 * must be non-zero; a value of zero indicates that the device in
 * unconfigured.  However some devices erroneously use 0 as one of their
 * configuration values.  To help manage such devices, this routine will
 * accept @configuration = -1 as indicating the device should be put in
 * an unconfigured state.
 *
 * USB device configurations may affect Linux पूर्णांकeroperability,
 * घातer consumption and the functionality available.  For example,
 * the शेष configuration is limited to using 100mA of bus घातer,
 * so that when certain device functionality requires more घातer,
 * and the device is bus घातered, that functionality should be in some
 * non-शेष device configuration.  Other device modes may also be
 * reflected as configuration options, such as whether two ISDN
 * channels are available independently; and choosing between खोलो
 * standard device protocols (like CDC) or proprietary ones.
 *
 * Note that a non-authorized device (dev->authorized == 0) will only
 * be put in unconfigured mode.
 *
 * Note that USB has an additional level of device configurability,
 * associated with पूर्णांकerfaces.  That configurability is accessed using
 * usb_set_पूर्णांकerface().
 *
 * This call is synchronous. The calling context must be able to sleep,
 * must own the device lock, and must not hold the driver model's USB
 * bus mutex; usb पूर्णांकerface driver probe() methods cannot use this routine.
 *
 * Returns zero on success, or अन्यथा the status code वापसed by the
 * underlying call that failed.  On successful completion, each पूर्णांकerface
 * in the original device configuration has been destroyed, and each one
 * in the new configuration has been probed by all relevant usb device
 * drivers currently known to the kernel.
 */
पूर्णांक usb_set_configuration(काष्ठा usb_device *dev, पूर्णांक configuration)
अणु
	पूर्णांक i, ret;
	काष्ठा usb_host_config *cp = शून्य;
	काष्ठा usb_पूर्णांकerface **new_पूर्णांकerfaces = शून्य;
	काष्ठा usb_hcd *hcd = bus_to_hcd(dev->bus);
	पूर्णांक n, nपूर्णांकf;

	अगर (dev->authorized == 0 || configuration == -1)
		configuration = 0;
	अन्यथा अणु
		क्रम (i = 0; i < dev->descriptor.bNumConfigurations; i++) अणु
			अगर (dev->config[i].desc.bConfigurationValue ==
					configuration) अणु
				cp = &dev->config[i];
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर ((!cp && configuration != 0))
		वापस -EINVAL;

	/* The USB spec says configuration 0 means unconfigured.
	 * But अगर a device includes a configuration numbered 0,
	 * we will accept it as a correctly configured state.
	 * Use -1 अगर you really want to unconfigure the device.
	 */
	अगर (cp && configuration == 0)
		dev_warn(&dev->dev, "config 0 descriptor??\n");

	/* Allocate memory क्रम new पूर्णांकerfaces beक्रमe करोing anything अन्यथा,
	 * so that अगर we run out then nothing will have changed. */
	n = nपूर्णांकf = 0;
	अगर (cp) अणु
		nपूर्णांकf = cp->desc.bNumInterfaces;
		new_पूर्णांकerfaces = kदो_स्मृति_array(nपूर्णांकf, माप(*new_पूर्णांकerfaces),
					       GFP_NOIO);
		अगर (!new_पूर्णांकerfaces)
			वापस -ENOMEM;

		क्रम (; n < nपूर्णांकf; ++n) अणु
			new_पूर्णांकerfaces[n] = kzalloc(
					माप(काष्ठा usb_पूर्णांकerface),
					GFP_NOIO);
			अगर (!new_पूर्णांकerfaces[n]) अणु
				ret = -ENOMEM;
मुक्त_पूर्णांकerfaces:
				जबतक (--n >= 0)
					kमुक्त(new_पूर्णांकerfaces[n]);
				kमुक्त(new_पूर्णांकerfaces);
				वापस ret;
			पूर्ण
		पूर्ण

		i = dev->bus_mA - usb_get_max_घातer(dev, cp);
		अगर (i < 0)
			dev_warn(&dev->dev, "new config #%d exceeds power "
					"limit by %dmA\n",
					configuration, -i);
	पूर्ण

	/* Wake up the device so we can send it the Set-Config request */
	ret = usb_स्वतःresume_device(dev);
	अगर (ret)
		जाओ मुक्त_पूर्णांकerfaces;

	/* अगर it's alपढ़ोy configured, clear out old state first.
	 * getting rid of old पूर्णांकerfaces means unbinding their drivers.
	 */
	अगर (dev->state != USB_STATE_ADDRESS)
		usb_disable_device(dev, 1);	/* Skip ep0 */

	/* Get rid of pending async Set-Config requests क्रम this device */
	cancel_async_set_config(dev);

	/* Make sure we have bandwidth (and available HCD resources) क्रम this
	 * configuration.  Remove endpoपूर्णांकs from the schedule अगर we're dropping
	 * this configuration to set configuration 0.  After this poपूर्णांक, the
	 * host controller will not allow submissions to dropped endpoपूर्णांकs.  If
	 * this call fails, the device state is unchanged.
	 */
	mutex_lock(hcd->bandwidth_mutex);
	/* Disable LPM, and re-enable it once the new configuration is
	 * installed, so that the xHCI driver can recalculate the U1/U2
	 * समयouts.
	 */
	अगर (dev->actconfig && usb_disable_lpm(dev)) अणु
		dev_err(&dev->dev, "%s Failed to disable LPM\n", __func__);
		mutex_unlock(hcd->bandwidth_mutex);
		ret = -ENOMEM;
		जाओ मुक्त_पूर्णांकerfaces;
	पूर्ण
	ret = usb_hcd_alloc_bandwidth(dev, cp, शून्य, शून्य);
	अगर (ret < 0) अणु
		अगर (dev->actconfig)
			usb_enable_lpm(dev);
		mutex_unlock(hcd->bandwidth_mutex);
		usb_स्वतःsuspend_device(dev);
		जाओ मुक्त_पूर्णांकerfaces;
	पूर्ण

	/*
	 * Initialize the new पूर्णांकerface काष्ठाures and the
	 * hc/hcd/usbcore पूर्णांकerface/endpoपूर्णांक state.
	 */
	क्रम (i = 0; i < nपूर्णांकf; ++i) अणु
		काष्ठा usb_पूर्णांकerface_cache *पूर्णांकfc;
		काष्ठा usb_पूर्णांकerface *पूर्णांकf;
		काष्ठा usb_host_पूर्णांकerface *alt;
		u8 अगरnum;

		cp->पूर्णांकerface[i] = पूर्णांकf = new_पूर्णांकerfaces[i];
		पूर्णांकfc = cp->पूर्णांकf_cache[i];
		पूर्णांकf->altsetting = पूर्णांकfc->altsetting;
		पूर्णांकf->num_altsetting = पूर्णांकfc->num_altsetting;
		पूर्णांकf->authorized = !!HCD_INTF_AUTHORIZED(hcd);
		kref_get(&पूर्णांकfc->ref);

		alt = usb_altnum_to_altsetting(पूर्णांकf, 0);

		/* No altsetting 0?  We'll assume the first altsetting.
		 * We could use a GetInterface call, but अगर a device is
		 * so non-compliant that it करोesn't have altsetting 0
		 * then I wouldn't trust its reply anyway.
		 */
		अगर (!alt)
			alt = &पूर्णांकf->altsetting[0];

		अगरnum = alt->desc.bInterfaceNumber;
		पूर्णांकf->पूर्णांकf_assoc = find_iad(dev, cp, अगरnum);
		पूर्णांकf->cur_altsetting = alt;
		usb_enable_पूर्णांकerface(dev, पूर्णांकf, true);
		पूर्णांकf->dev.parent = &dev->dev;
		अगर (usb_of_has_combined_node(dev)) अणु
			device_set_of_node_from_dev(&पूर्णांकf->dev, &dev->dev);
		पूर्ण अन्यथा अणु
			पूर्णांकf->dev.of_node = usb_of_get_पूर्णांकerface_node(dev,
					configuration, अगरnum);
		पूर्ण
		ACPI_COMPANION_SET(&पूर्णांकf->dev, ACPI_COMPANION(&dev->dev));
		पूर्णांकf->dev.driver = शून्य;
		पूर्णांकf->dev.bus = &usb_bus_type;
		पूर्णांकf->dev.type = &usb_अगर_device_type;
		पूर्णांकf->dev.groups = usb_पूर्णांकerface_groups;
		INIT_WORK(&पूर्णांकf->reset_ws, __usb_queue_reset_device);
		पूर्णांकf->minor = -1;
		device_initialize(&पूर्णांकf->dev);
		pm_runसमय_no_callbacks(&पूर्णांकf->dev);
		dev_set_name(&पूर्णांकf->dev, "%d-%s:%d.%d", dev->bus->busnum,
				dev->devpath, configuration, अगरnum);
		usb_get_dev(dev);
	पूर्ण
	kमुक्त(new_पूर्णांकerfaces);

	ret = usb_control_msg_send(dev, 0, USB_REQ_SET_CONFIGURATION, 0,
				   configuration, 0, शून्य, 0,
				   USB_CTRL_SET_TIMEOUT, GFP_NOIO);
	अगर (ret && cp) अणु
		/*
		 * All the old state is gone, so what अन्यथा can we करो?
		 * The device is probably useless now anyway.
		 */
		usb_hcd_alloc_bandwidth(dev, शून्य, शून्य, शून्य);
		क्रम (i = 0; i < nपूर्णांकf; ++i) अणु
			usb_disable_पूर्णांकerface(dev, cp->पूर्णांकerface[i], true);
			put_device(&cp->पूर्णांकerface[i]->dev);
			cp->पूर्णांकerface[i] = शून्य;
		पूर्ण
		cp = शून्य;
	पूर्ण

	dev->actconfig = cp;
	mutex_unlock(hcd->bandwidth_mutex);

	अगर (!cp) अणु
		usb_set_device_state(dev, USB_STATE_ADDRESS);

		/* Leave LPM disabled जबतक the device is unconfigured. */
		usb_स्वतःsuspend_device(dev);
		वापस ret;
	पूर्ण
	usb_set_device_state(dev, USB_STATE_CONFIGURED);

	अगर (cp->string == शून्य &&
			!(dev->quirks & USB_QUIRK_CONFIG_INTF_STRINGS))
		cp->string = usb_cache_string(dev, cp->desc.iConfiguration);

	/* Now that the पूर्णांकerfaces are installed, re-enable LPM. */
	usb_unlocked_enable_lpm(dev);
	/* Enable LTM अगर it was turned off by usb_disable_device. */
	usb_enable_lपंचांग(dev);

	/* Now that all the पूर्णांकerfaces are set up, रेजिस्टर them
	 * to trigger binding of drivers to पूर्णांकerfaces.  probe()
	 * routines may install dअगरferent altsettings and may
	 * claim() any पूर्णांकerfaces not yet bound.  Many class drivers
	 * need that: CDC, audio, video, etc.
	 */
	क्रम (i = 0; i < nपूर्णांकf; ++i) अणु
		काष्ठा usb_पूर्णांकerface *पूर्णांकf = cp->पूर्णांकerface[i];

		अगर (पूर्णांकf->dev.of_node &&
		    !of_device_is_available(पूर्णांकf->dev.of_node)) अणु
			dev_info(&dev->dev, "skipping disabled interface %d\n",
				 पूर्णांकf->cur_altsetting->desc.bInterfaceNumber);
			जारी;
		पूर्ण

		dev_dbg(&dev->dev,
			"adding %s (config #%d, interface %d)\n",
			dev_name(&पूर्णांकf->dev), configuration,
			पूर्णांकf->cur_altsetting->desc.bInterfaceNumber);
		device_enable_async_suspend(&पूर्णांकf->dev);
		ret = device_add(&पूर्णांकf->dev);
		अगर (ret != 0) अणु
			dev_err(&dev->dev, "device_add(%s) --> %d\n",
				dev_name(&पूर्णांकf->dev), ret);
			जारी;
		पूर्ण
		create_पूर्णांकf_ep_devs(पूर्णांकf);
	पूर्ण

	usb_स्वतःsuspend_device(dev);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(usb_set_configuration);

अटल LIST_HEAD(set_config_list);
अटल DEFINE_SPINLOCK(set_config_lock);

काष्ठा set_config_request अणु
	काष्ठा usb_device	*udev;
	पूर्णांक			config;
	काष्ठा work_काष्ठा	work;
	काष्ठा list_head	node;
पूर्ण;

/* Worker routine क्रम usb_driver_set_configuration() */
अटल व्योम driver_set_config_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा set_config_request *req =
		container_of(work, काष्ठा set_config_request, work);
	काष्ठा usb_device *udev = req->udev;

	usb_lock_device(udev);
	spin_lock(&set_config_lock);
	list_del(&req->node);
	spin_unlock(&set_config_lock);

	अगर (req->config >= -1)		/* Is req still valid? */
		usb_set_configuration(udev, req->config);
	usb_unlock_device(udev);
	usb_put_dev(udev);
	kमुक्त(req);
पूर्ण

/* Cancel pending Set-Config requests क्रम a device whose configuration
 * was just changed
 */
अटल व्योम cancel_async_set_config(काष्ठा usb_device *udev)
अणु
	काष्ठा set_config_request *req;

	spin_lock(&set_config_lock);
	list_क्रम_each_entry(req, &set_config_list, node) अणु
		अगर (req->udev == udev)
			req->config = -999;	/* Mark as cancelled */
	पूर्ण
	spin_unlock(&set_config_lock);
पूर्ण

/**
 * usb_driver_set_configuration - Provide a way क्रम drivers to change device configurations
 * @udev: the device whose configuration is being updated
 * @config: the configuration being chosen.
 * Context: In process context, must be able to sleep
 *
 * Device पूर्णांकerface drivers are not allowed to change device configurations.
 * This is because changing configurations will destroy the पूर्णांकerface the
 * driver is bound to and create new ones; it would be like a floppy-disk
 * driver telling the computer to replace the floppy-disk drive with a
 * tape drive!
 *
 * Still, in certain specialized circumstances the need may arise.  This
 * routine माला_लो around the normal restrictions by using a work thपढ़ो to
 * submit the change-config request.
 *
 * Return: 0 अगर the request was successfully queued, error code otherwise.
 * The caller has no way to know whether the queued request will eventually
 * succeed.
 */
पूर्णांक usb_driver_set_configuration(काष्ठा usb_device *udev, पूर्णांक config)
अणु
	काष्ठा set_config_request *req;

	req = kदो_स्मृति(माप(*req), GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;
	req->udev = udev;
	req->config = config;
	INIT_WORK(&req->work, driver_set_config_work);

	spin_lock(&set_config_lock);
	list_add(&req->node, &set_config_list);
	spin_unlock(&set_config_lock);

	usb_get_dev(udev);
	schedule_work(&req->work);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(usb_driver_set_configuration);

/**
 * cdc_parse_cdc_header - parse the extra headers present in CDC devices
 * @hdr: the place to put the results of the parsing
 * @पूर्णांकf: the पूर्णांकerface क्रम which parsing is requested
 * @buffer: poपूर्णांकer to the extra headers to be parsed
 * @buflen: length of the extra headers
 *
 * This evaluates the extra headers present in CDC devices which
 * bind the पूर्णांकerfaces क्रम data and control and provide details
 * about the capabilities of the device.
 *
 * Return: number of descriptors parsed or -EINVAL
 * अगर the header is contradictory beyond salvage
 */

पूर्णांक cdc_parse_cdc_header(काष्ठा usb_cdc_parsed_header *hdr,
				काष्ठा usb_पूर्णांकerface *पूर्णांकf,
				u8 *buffer,
				पूर्णांक buflen)
अणु
	/* duplicates are ignored */
	काष्ठा usb_cdc_जोड़_desc *जोड़_header = शून्य;

	/* duplicates are not tolerated */
	काष्ठा usb_cdc_header_desc *header = शून्य;
	काष्ठा usb_cdc_ether_desc *ether = शून्य;
	काष्ठा usb_cdc_mdlm_detail_desc *detail = शून्य;
	काष्ठा usb_cdc_mdlm_desc *desc = शून्य;

	अचिन्हित पूर्णांक elength;
	पूर्णांक cnt = 0;

	स_रखो(hdr, 0x00, माप(काष्ठा usb_cdc_parsed_header));
	hdr->phonet_magic_present = false;
	जबतक (buflen > 0) अणु
		elength = buffer[0];
		अगर (!elength) अणु
			dev_err(&पूर्णांकf->dev, "skipping garbage byte\n");
			elength = 1;
			जाओ next_desc;
		पूर्ण
		अगर ((buflen < elength) || (elength < 3)) अणु
			dev_err(&पूर्णांकf->dev, "invalid descriptor buffer length\n");
			अवरोध;
		पूर्ण
		अगर (buffer[1] != USB_DT_CS_INTERFACE) अणु
			dev_err(&पूर्णांकf->dev, "skipping garbage\n");
			जाओ next_desc;
		पूर्ण

		चयन (buffer[2]) अणु
		हाल USB_CDC_UNION_TYPE: /* we've found it */
			अगर (elength < माप(काष्ठा usb_cdc_जोड़_desc))
				जाओ next_desc;
			अगर (जोड़_header) अणु
				dev_err(&पूर्णांकf->dev, "More than one union descriptor, skipping ...\n");
				जाओ next_desc;
			पूर्ण
			जोड़_header = (काष्ठा usb_cdc_जोड़_desc *)buffer;
			अवरोध;
		हाल USB_CDC_COUNTRY_TYPE:
			अगर (elength < माप(काष्ठा usb_cdc_country_functional_desc))
				जाओ next_desc;
			hdr->usb_cdc_country_functional_desc =
				(काष्ठा usb_cdc_country_functional_desc *)buffer;
			अवरोध;
		हाल USB_CDC_HEADER_TYPE:
			अगर (elength != माप(काष्ठा usb_cdc_header_desc))
				जाओ next_desc;
			अगर (header)
				वापस -EINVAL;
			header = (काष्ठा usb_cdc_header_desc *)buffer;
			अवरोध;
		हाल USB_CDC_ACM_TYPE:
			अगर (elength < माप(काष्ठा usb_cdc_acm_descriptor))
				जाओ next_desc;
			hdr->usb_cdc_acm_descriptor =
				(काष्ठा usb_cdc_acm_descriptor *)buffer;
			अवरोध;
		हाल USB_CDC_ETHERNET_TYPE:
			अगर (elength != माप(काष्ठा usb_cdc_ether_desc))
				जाओ next_desc;
			अगर (ether)
				वापस -EINVAL;
			ether = (काष्ठा usb_cdc_ether_desc *)buffer;
			अवरोध;
		हाल USB_CDC_CALL_MANAGEMENT_TYPE:
			अगर (elength < माप(काष्ठा usb_cdc_call_mgmt_descriptor))
				जाओ next_desc;
			hdr->usb_cdc_call_mgmt_descriptor =
				(काष्ठा usb_cdc_call_mgmt_descriptor *)buffer;
			अवरोध;
		हाल USB_CDC_DMM_TYPE:
			अगर (elength < माप(काष्ठा usb_cdc_dmm_desc))
				जाओ next_desc;
			hdr->usb_cdc_dmm_desc =
				(काष्ठा usb_cdc_dmm_desc *)buffer;
			अवरोध;
		हाल USB_CDC_MDLM_TYPE:
			अगर (elength < माप(काष्ठा usb_cdc_mdlm_desc))
				जाओ next_desc;
			अगर (desc)
				वापस -EINVAL;
			desc = (काष्ठा usb_cdc_mdlm_desc *)buffer;
			अवरोध;
		हाल USB_CDC_MDLM_DETAIL_TYPE:
			अगर (elength < माप(काष्ठा usb_cdc_mdlm_detail_desc))
				जाओ next_desc;
			अगर (detail)
				वापस -EINVAL;
			detail = (काष्ठा usb_cdc_mdlm_detail_desc *)buffer;
			अवरोध;
		हाल USB_CDC_NCM_TYPE:
			अगर (elength < माप(काष्ठा usb_cdc_ncm_desc))
				जाओ next_desc;
			hdr->usb_cdc_ncm_desc = (काष्ठा usb_cdc_ncm_desc *)buffer;
			अवरोध;
		हाल USB_CDC_MBIM_TYPE:
			अगर (elength < माप(काष्ठा usb_cdc_mbim_desc))
				जाओ next_desc;

			hdr->usb_cdc_mbim_desc = (काष्ठा usb_cdc_mbim_desc *)buffer;
			अवरोध;
		हाल USB_CDC_MBIM_EXTENDED_TYPE:
			अगर (elength < माप(काष्ठा usb_cdc_mbim_extended_desc))
				अवरोध;
			hdr->usb_cdc_mbim_extended_desc =
				(काष्ठा usb_cdc_mbim_extended_desc *)buffer;
			अवरोध;
		हाल CDC_PHONET_MAGIC_NUMBER:
			hdr->phonet_magic_present = true;
			अवरोध;
		शेष:
			/*
			 * there are LOTS more CDC descriptors that
			 * could legitimately be found here.
			 */
			dev_dbg(&पूर्णांकf->dev, "Ignoring descriptor: type %02x, length %ud\n",
					buffer[2], elength);
			जाओ next_desc;
		पूर्ण
		cnt++;
next_desc:
		buflen -= elength;
		buffer += elength;
	पूर्ण
	hdr->usb_cdc_जोड़_desc = जोड़_header;
	hdr->usb_cdc_header_desc = header;
	hdr->usb_cdc_mdlm_detail_desc = detail;
	hdr->usb_cdc_mdlm_desc = desc;
	hdr->usb_cdc_ether_desc = ether;
	वापस cnt;
पूर्ण

EXPORT_SYMBOL(cdc_parse_cdc_header);
