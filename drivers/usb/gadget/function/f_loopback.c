<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * f_loopback.c - USB peripheral loopback configuration driver
 *
 * Copyright (C) 2003-2008 David Brownell
 * Copyright (C) 2008 by Nokia Corporation
 */

/* #घोषणा VERBOSE_DEBUG */

#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/usb/composite.h>

#समावेश "g_zero.h"
#समावेश "u_f.h"

/*
 * LOOPBACK FUNCTION ... a testing vehicle क्रम USB peripherals,
 *
 * This takes messages of various sizes written OUT to a device, and loops
 * them back so they can be पढ़ो IN from it.  It has been used by certain
 * test applications.  It supports limited testing of data queueing logic.
 */
काष्ठा f_loopback अणु
	काष्ठा usb_function	function;

	काष्ठा usb_ep		*in_ep;
	काष्ठा usb_ep		*out_ep;

	अचिन्हित                qlen;
	अचिन्हित                buflen;
पूर्ण;

अटल अंतरभूत काष्ठा f_loopback *func_to_loop(काष्ठा usb_function *f)
अणु
	वापस container_of(f, काष्ठा f_loopback, function);
पूर्ण

/*-------------------------------------------------------------------------*/

अटल काष्ठा usb_पूर्णांकerface_descriptor loopback_पूर्णांकf = अणु
	.bLength =		माप(loopback_पूर्णांकf),
	.bDescriptorType =	USB_DT_INTERFACE,

	.bNumEndpoपूर्णांकs =	2,
	.bInterfaceClass =	USB_CLASS_VENDOR_SPEC,
	/* .iInterface = DYNAMIC */
पूर्ण;

/* full speed support: */

अटल काष्ठा usb_endpoपूर्णांक_descriptor fs_loop_source_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor fs_loop_sink_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_OUT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
पूर्ण;

अटल काष्ठा usb_descriptor_header *fs_loopback_descs[] = अणु
	(काष्ठा usb_descriptor_header *) &loopback_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &fs_loop_sink_desc,
	(काष्ठा usb_descriptor_header *) &fs_loop_source_desc,
	शून्य,
पूर्ण;

/* high speed support: */

अटल काष्ठा usb_endpoपूर्णांक_descriptor hs_loop_source_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(512),
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor hs_loop_sink_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(512),
पूर्ण;

अटल काष्ठा usb_descriptor_header *hs_loopback_descs[] = अणु
	(काष्ठा usb_descriptor_header *) &loopback_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &hs_loop_source_desc,
	(काष्ठा usb_descriptor_header *) &hs_loop_sink_desc,
	शून्य,
पूर्ण;

/* super speed support: */

अटल काष्ठा usb_endpoपूर्णांक_descriptor ss_loop_source_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(1024),
पूर्ण;

अटल काष्ठा usb_ss_ep_comp_descriptor ss_loop_source_comp_desc = अणु
	.bLength =		USB_DT_SS_EP_COMP_SIZE,
	.bDescriptorType =	USB_DT_SS_ENDPOINT_COMP,
	.bMaxBurst =		0,
	.bmAttributes =		0,
	.wBytesPerInterval =	0,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor ss_loop_sink_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(1024),
पूर्ण;

अटल काष्ठा usb_ss_ep_comp_descriptor ss_loop_sink_comp_desc = अणु
	.bLength =		USB_DT_SS_EP_COMP_SIZE,
	.bDescriptorType =	USB_DT_SS_ENDPOINT_COMP,
	.bMaxBurst =		0,
	.bmAttributes =		0,
	.wBytesPerInterval =	0,
पूर्ण;

अटल काष्ठा usb_descriptor_header *ss_loopback_descs[] = अणु
	(काष्ठा usb_descriptor_header *) &loopback_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &ss_loop_source_desc,
	(काष्ठा usb_descriptor_header *) &ss_loop_source_comp_desc,
	(काष्ठा usb_descriptor_header *) &ss_loop_sink_desc,
	(काष्ठा usb_descriptor_header *) &ss_loop_sink_comp_desc,
	शून्य,
पूर्ण;

/* function-specअगरic strings: */

अटल काष्ठा usb_string strings_loopback[] = अणु
	[0].s = "loop input to output",
	अणु  पूर्ण			/* end of list */
पूर्ण;

अटल काष्ठा usb_gadget_strings stringtab_loop = अणु
	.language	= 0x0409,	/* en-us */
	.strings	= strings_loopback,
पूर्ण;

अटल काष्ठा usb_gadget_strings *loopback_strings[] = अणु
	&stringtab_loop,
	शून्य,
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल पूर्णांक loopback_bind(काष्ठा usb_configuration *c, काष्ठा usb_function *f)
अणु
	काष्ठा usb_composite_dev *cdev = c->cdev;
	काष्ठा f_loopback	*loop = func_to_loop(f);
	पूर्णांक			id;
	पूर्णांक ret;

	/* allocate पूर्णांकerface ID(s) */
	id = usb_पूर्णांकerface_id(c, f);
	अगर (id < 0)
		वापस id;
	loopback_पूर्णांकf.bInterfaceNumber = id;

	id = usb_string_id(cdev);
	अगर (id < 0)
		वापस id;
	strings_loopback[0].id = id;
	loopback_पूर्णांकf.iInterface = id;

	/* allocate endpoपूर्णांकs */

	loop->in_ep = usb_ep_स्वतःconfig(cdev->gadget, &fs_loop_source_desc);
	अगर (!loop->in_ep) अणु
स्वतःconf_fail:
		ERROR(cdev, "%s: can't autoconfigure on %s\n",
			f->name, cdev->gadget->name);
		वापस -ENODEV;
	पूर्ण

	loop->out_ep = usb_ep_स्वतःconfig(cdev->gadget, &fs_loop_sink_desc);
	अगर (!loop->out_ep)
		जाओ स्वतःconf_fail;

	/* support high speed hardware */
	hs_loop_source_desc.bEndpoपूर्णांकAddress =
		fs_loop_source_desc.bEndpoपूर्णांकAddress;
	hs_loop_sink_desc.bEndpoपूर्णांकAddress = fs_loop_sink_desc.bEndpoपूर्णांकAddress;

	/* support super speed hardware */
	ss_loop_source_desc.bEndpoपूर्णांकAddress =
		fs_loop_source_desc.bEndpoपूर्णांकAddress;
	ss_loop_sink_desc.bEndpoपूर्णांकAddress = fs_loop_sink_desc.bEndpoपूर्णांकAddress;

	ret = usb_assign_descriptors(f, fs_loopback_descs, hs_loopback_descs,
			ss_loopback_descs, ss_loopback_descs);
	अगर (ret)
		वापस ret;

	DBG(cdev, "%s speed %s: IN/%s, OUT/%s\n",
	    (gadget_is_superspeed(c->cdev->gadget) ? "super" :
	     (gadget_is_dualspeed(c->cdev->gadget) ? "dual" : "full")),
			f->name, loop->in_ep->name, loop->out_ep->name);
	वापस 0;
पूर्ण

अटल व्योम lb_मुक्त_func(काष्ठा usb_function *f)
अणु
	काष्ठा f_lb_opts *opts;

	opts = container_of(f->fi, काष्ठा f_lb_opts, func_inst);

	mutex_lock(&opts->lock);
	opts->refcnt--;
	mutex_unlock(&opts->lock);

	usb_मुक्त_all_descriptors(f);
	kमुक्त(func_to_loop(f));
पूर्ण

अटल व्योम loopback_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा f_loopback	*loop = ep->driver_data;
	काष्ठा usb_composite_dev *cdev = loop->function.config->cdev;
	पूर्णांक			status = req->status;

	चयन (status) अणु
	हाल 0:				/* normal completion? */
		अगर (ep == loop->out_ep) अणु
			/*
			 * We received some data from the host so let's
			 * queue it so host can पढ़ो the from our in ep
			 */
			काष्ठा usb_request *in_req = req->context;

			in_req->zero = (req->actual < req->length);
			in_req->length = req->actual;
			ep = loop->in_ep;
			req = in_req;
		पूर्ण अन्यथा अणु
			/*
			 * We have just looped back a bunch of data
			 * to host. Now let's रुको क्रम some more data.
			 */
			req = req->context;
			ep = loop->out_ep;
		पूर्ण

		/* queue the buffer back to host or क्रम next bunch of data */
		status = usb_ep_queue(ep, req, GFP_ATOMIC);
		अगर (status == 0) अणु
			वापस;
		पूर्ण अन्यथा अणु
			ERROR(cdev, "Unable to loop back buffer to %s: %d\n",
			      ep->name, status);
			जाओ मुक्त_req;
		पूर्ण

		/* "should never get here" */
	शेष:
		ERROR(cdev, "%s loop complete --> %d, %d/%d\n", ep->name,
				status, req->actual, req->length);
		fallthrough;

	/* NOTE:  since this driver करोesn't मुख्यtain an explicit record
	 * of requests it submitted (just मुख्यtains qlen count), we
	 * rely on the hardware driver to clean up on disconnect or
	 * endpoपूर्णांक disable.
	 */
	हाल -ECONNABORTED:		/* hardware क्रमced ep reset */
	हाल -ECONNRESET:		/* request dequeued */
	हाल -ESHUTDOWN:		/* disconnect from host */
मुक्त_req:
		usb_ep_मुक्त_request(ep == loop->in_ep ?
				    loop->out_ep : loop->in_ep,
				    req->context);
		मुक्त_ep_req(ep, req);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम disable_loopback(काष्ठा f_loopback *loop)
अणु
	काष्ठा usb_composite_dev	*cdev;

	cdev = loop->function.config->cdev;
	disable_endpoपूर्णांकs(cdev, loop->in_ep, loop->out_ep, शून्य, शून्य);
	VDBG(cdev, "%s disabled\n", loop->function.name);
पूर्ण

अटल अंतरभूत काष्ठा usb_request *lb_alloc_ep_req(काष्ठा usb_ep *ep, पूर्णांक len)
अणु
	वापस alloc_ep_req(ep, len);
पूर्ण

अटल पूर्णांक alloc_requests(काष्ठा usb_composite_dev *cdev,
			  काष्ठा f_loopback *loop)
अणु
	काष्ठा usb_request *in_req, *out_req;
	पूर्णांक i;
	पूर्णांक result = 0;

	/*
	 * allocate a bunch of पढ़ो buffers and queue them all at once.
	 * we buffer at most 'qlen' transfers; We allocate buffers only
	 * क्रम out transfer and reuse them in IN transfers to implement
	 * our loopback functionality
	 */
	क्रम (i = 0; i < loop->qlen && result == 0; i++) अणु
		result = -ENOMEM;

		in_req = usb_ep_alloc_request(loop->in_ep, GFP_ATOMIC);
		अगर (!in_req)
			जाओ fail;

		out_req = lb_alloc_ep_req(loop->out_ep, loop->buflen);
		अगर (!out_req)
			जाओ fail_in;

		in_req->complete = loopback_complete;
		out_req->complete = loopback_complete;

		in_req->buf = out_req->buf;
		/* length will be set in complete routine */
		in_req->context = out_req;
		out_req->context = in_req;

		result = usb_ep_queue(loop->out_ep, out_req, GFP_ATOMIC);
		अगर (result) अणु
			ERROR(cdev, "%s queue req --> %d\n",
					loop->out_ep->name, result);
			जाओ fail_out;
		पूर्ण
	पूर्ण

	वापस 0;

fail_out:
	मुक्त_ep_req(loop->out_ep, out_req);
fail_in:
	usb_ep_मुक्त_request(loop->in_ep, in_req);
fail:
	वापस result;
पूर्ण

अटल पूर्णांक enable_endpoपूर्णांक(काष्ठा usb_composite_dev *cdev,
			   काष्ठा f_loopback *loop, काष्ठा usb_ep *ep)
अणु
	पूर्णांक					result;

	result = config_ep_by_speed(cdev->gadget, &(loop->function), ep);
	अगर (result)
		जाओ out;

	result = usb_ep_enable(ep);
	अगर (result < 0)
		जाओ out;
	ep->driver_data = loop;
	result = 0;

out:
	वापस result;
पूर्ण

अटल पूर्णांक
enable_loopback(काष्ठा usb_composite_dev *cdev, काष्ठा f_loopback *loop)
अणु
	पूर्णांक					result = 0;

	result = enable_endpoपूर्णांक(cdev, loop, loop->in_ep);
	अगर (result)
		जाओ out;

	result = enable_endpoपूर्णांक(cdev, loop, loop->out_ep);
	अगर (result)
		जाओ disable_in;

	result = alloc_requests(cdev, loop);
	अगर (result)
		जाओ disable_out;

	DBG(cdev, "%s enabled\n", loop->function.name);
	वापस 0;

disable_out:
	usb_ep_disable(loop->out_ep);
disable_in:
	usb_ep_disable(loop->in_ep);
out:
	वापस result;
पूर्ण

अटल पूर्णांक loopback_set_alt(काष्ठा usb_function *f,
		अचिन्हित पूर्णांकf, अचिन्हित alt)
अणु
	काष्ठा f_loopback	*loop = func_to_loop(f);
	काष्ठा usb_composite_dev *cdev = f->config->cdev;

	/* we know alt is zero */
	disable_loopback(loop);
	वापस enable_loopback(cdev, loop);
पूर्ण

अटल व्योम loopback_disable(काष्ठा usb_function *f)
अणु
	काष्ठा f_loopback	*loop = func_to_loop(f);

	disable_loopback(loop);
पूर्ण

अटल काष्ठा usb_function *loopback_alloc(काष्ठा usb_function_instance *fi)
अणु
	काष्ठा f_loopback	*loop;
	काष्ठा f_lb_opts	*lb_opts;

	loop = kzalloc(माप *loop, GFP_KERNEL);
	अगर (!loop)
		वापस ERR_PTR(-ENOMEM);

	lb_opts = container_of(fi, काष्ठा f_lb_opts, func_inst);

	mutex_lock(&lb_opts->lock);
	lb_opts->refcnt++;
	mutex_unlock(&lb_opts->lock);

	loop->buflen = lb_opts->bulk_buflen;
	loop->qlen = lb_opts->qlen;
	अगर (!loop->qlen)
		loop->qlen = 32;

	loop->function.name = "loopback";
	loop->function.bind = loopback_bind;
	loop->function.set_alt = loopback_set_alt;
	loop->function.disable = loopback_disable;
	loop->function.strings = loopback_strings;

	loop->function.मुक्त_func = lb_मुक्त_func;

	वापस &loop->function;
पूर्ण

अटल अंतरभूत काष्ठा f_lb_opts *to_f_lb_opts(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा f_lb_opts,
			    func_inst.group);
पूर्ण

अटल व्योम lb_attr_release(काष्ठा config_item *item)
अणु
	काष्ठा f_lb_opts *lb_opts = to_f_lb_opts(item);

	usb_put_function_instance(&lb_opts->func_inst);
पूर्ण

अटल काष्ठा configfs_item_operations lb_item_ops = अणु
	.release		= lb_attr_release,
पूर्ण;

अटल sमाप_प्रकार f_lb_opts_qlen_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा f_lb_opts *opts = to_f_lb_opts(item);
	पूर्णांक result;

	mutex_lock(&opts->lock);
	result = प्र_लिखो(page, "%d\n", opts->qlen);
	mutex_unlock(&opts->lock);

	वापस result;
पूर्ण

अटल sमाप_प्रकार f_lb_opts_qlen_store(काष्ठा config_item *item,
				    स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा f_lb_opts *opts = to_f_lb_opts(item);
	पूर्णांक ret;
	u32 num;

	mutex_lock(&opts->lock);
	अगर (opts->refcnt) अणु
		ret = -EBUSY;
		जाओ end;
	पूर्ण

	ret = kstrtou32(page, 0, &num);
	अगर (ret)
		जाओ end;

	opts->qlen = num;
	ret = len;
end:
	mutex_unlock(&opts->lock);
	वापस ret;
पूर्ण

CONFIGFS_ATTR(f_lb_opts_, qlen);

अटल sमाप_प्रकार f_lb_opts_bulk_buflen_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा f_lb_opts *opts = to_f_lb_opts(item);
	पूर्णांक result;

	mutex_lock(&opts->lock);
	result = प्र_लिखो(page, "%d\n", opts->bulk_buflen);
	mutex_unlock(&opts->lock);

	वापस result;
पूर्ण

अटल sमाप_प्रकार f_lb_opts_bulk_buflen_store(काष्ठा config_item *item,
				    स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा f_lb_opts *opts = to_f_lb_opts(item);
	पूर्णांक ret;
	u32 num;

	mutex_lock(&opts->lock);
	अगर (opts->refcnt) अणु
		ret = -EBUSY;
		जाओ end;
	पूर्ण

	ret = kstrtou32(page, 0, &num);
	अगर (ret)
		जाओ end;

	opts->bulk_buflen = num;
	ret = len;
end:
	mutex_unlock(&opts->lock);
	वापस ret;
पूर्ण

CONFIGFS_ATTR(f_lb_opts_, bulk_buflen);

अटल काष्ठा configfs_attribute *lb_attrs[] = अणु
	&f_lb_opts_attr_qlen,
	&f_lb_opts_attr_bulk_buflen,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा config_item_type lb_func_type = अणु
	.ct_item_ops    = &lb_item_ops,
	.ct_attrs	= lb_attrs,
	.ct_owner       = THIS_MODULE,
पूर्ण;

अटल व्योम lb_मुक्त_instance(काष्ठा usb_function_instance *fi)
अणु
	काष्ठा f_lb_opts *lb_opts;

	lb_opts = container_of(fi, काष्ठा f_lb_opts, func_inst);
	kमुक्त(lb_opts);
पूर्ण

अटल काष्ठा usb_function_instance *loopback_alloc_instance(व्योम)
अणु
	काष्ठा f_lb_opts *lb_opts;

	lb_opts = kzalloc(माप(*lb_opts), GFP_KERNEL);
	अगर (!lb_opts)
		वापस ERR_PTR(-ENOMEM);
	mutex_init(&lb_opts->lock);
	lb_opts->func_inst.मुक्त_func_inst = lb_मुक्त_instance;
	lb_opts->bulk_buflen = GZERO_BULK_BUFLEN;
	lb_opts->qlen = GZERO_QLEN;

	config_group_init_type_name(&lb_opts->func_inst.group, "",
				    &lb_func_type);

	वापस  &lb_opts->func_inst;
पूर्ण
DECLARE_USB_FUNCTION(Loopback, loopback_alloc_instance, loopback_alloc);

पूर्णांक __init lb_modinit(व्योम)
अणु
	वापस usb_function_रेजिस्टर(&Loopbackusb_func);
पूर्ण

व्योम __निकास lb_modनिकास(व्योम)
अणु
	usb_function_unरेजिस्टर(&Loopbackusb_func);
पूर्ण

MODULE_LICENSE("GPL");
