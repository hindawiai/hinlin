<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * f_hid.c -- USB HID function driver
 *
 * Copyright (C) 2010 Fabien Chouteau <fabien.chouteau@barco.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/hid.h>
#समावेश <linux/idr.h>
#समावेश <linux/cdev.h>
#समावेश <linux/mutex.h>
#समावेश <linux/poll.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/रुको.h>
#समावेश <linux/sched.h>
#समावेश <linux/usb/g_hid.h>

#समावेश "u_f.h"
#समावेश "u_hid.h"

#घोषणा HIDG_MINORS	4

अटल पूर्णांक major, minors;
अटल काष्ठा class *hidg_class;
अटल DEFINE_IDA(hidg_ida);
अटल DEFINE_MUTEX(hidg_ida_lock); /* protects access to hidg_ida */

/*-------------------------------------------------------------------------*/
/*                            HID gadget काष्ठा                            */

काष्ठा f_hidg_req_list अणु
	काष्ठा usb_request	*req;
	अचिन्हित पूर्णांक		pos;
	काष्ठा list_head 	list;
पूर्ण;

काष्ठा f_hidg अणु
	/* configuration */
	अचिन्हित अक्षर			bInterfaceSubClass;
	अचिन्हित अक्षर			bInterfaceProtocol;
	अचिन्हित अक्षर			protocol;
	अचिन्हित लघु			report_desc_length;
	अक्षर				*report_desc;
	अचिन्हित लघु			report_length;

	/* recv report */
	काष्ठा list_head		completed_out_req;
	spinlock_t			पढ़ो_spinlock;
	रुको_queue_head_t		पढ़ो_queue;
	अचिन्हित पूर्णांक			qlen;

	/* send report */
	spinlock_t			ग_लिखो_spinlock;
	bool				ग_लिखो_pending;
	रुको_queue_head_t		ग_लिखो_queue;
	काष्ठा usb_request		*req;

	पूर्णांक				minor;
	काष्ठा cdev			cdev;
	काष्ठा usb_function		func;

	काष्ठा usb_ep			*in_ep;
	काष्ठा usb_ep			*out_ep;
पूर्ण;

अटल अंतरभूत काष्ठा f_hidg *func_to_hidg(काष्ठा usb_function *f)
अणु
	वापस container_of(f, काष्ठा f_hidg, func);
पूर्ण

/*-------------------------------------------------------------------------*/
/*                           Static descriptors                            */

अटल काष्ठा usb_पूर्णांकerface_descriptor hidg_पूर्णांकerface_desc = अणु
	.bLength		= माप hidg_पूर्णांकerface_desc,
	.bDescriptorType	= USB_DT_INTERFACE,
	/* .bInterfaceNumber	= DYNAMIC */
	.bAlternateSetting	= 0,
	.bNumEndpoपूर्णांकs		= 2,
	.bInterfaceClass	= USB_CLASS_HID,
	/* .bInterfaceSubClass	= DYNAMIC */
	/* .bInterfaceProtocol	= DYNAMIC */
	/* .iInterface		= DYNAMIC */
पूर्ण;

अटल काष्ठा hid_descriptor hidg_desc = अणु
	.bLength			= माप hidg_desc,
	.bDescriptorType		= HID_DT_HID,
	.bcdHID				= 0x0101,
	.bCountryCode			= 0x00,
	.bNumDescriptors		= 0x1,
	/*.desc[0].bDescriptorType	= DYNAMIC */
	/*.desc[0].wDescriptorLenght	= DYNAMIC */
पूर्ण;

/* Super-Speed Support */

अटल काष्ठा usb_endpoपूर्णांक_descriptor hidg_ss_in_ep_desc = अणु
	.bLength		= USB_DT_ENDPOINT_SIZE,
	.bDescriptorType	= USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress	= USB_सूची_IN,
	.bmAttributes		= USB_ENDPOINT_XFER_INT,
	/*.wMaxPacketSize	= DYNAMIC */
	.bInterval		= 4, /* FIXME: Add this field in the
				      * HID gadget configuration?
				      * (काष्ठा hidg_func_descriptor)
				      */
पूर्ण;

अटल काष्ठा usb_ss_ep_comp_descriptor hidg_ss_in_comp_desc = अणु
	.bLength                = माप(hidg_ss_in_comp_desc),
	.bDescriptorType        = USB_DT_SS_ENDPOINT_COMP,

	/* .bMaxBurst           = 0, */
	/* .bmAttributes        = 0, */
	/* .wBytesPerInterval   = DYNAMIC */
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor hidg_ss_out_ep_desc = अणु
	.bLength		= USB_DT_ENDPOINT_SIZE,
	.bDescriptorType	= USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress	= USB_सूची_OUT,
	.bmAttributes		= USB_ENDPOINT_XFER_INT,
	/*.wMaxPacketSize	= DYNAMIC */
	.bInterval		= 4, /* FIXME: Add this field in the
				      * HID gadget configuration?
				      * (काष्ठा hidg_func_descriptor)
				      */
पूर्ण;

अटल काष्ठा usb_ss_ep_comp_descriptor hidg_ss_out_comp_desc = अणु
	.bLength                = माप(hidg_ss_out_comp_desc),
	.bDescriptorType        = USB_DT_SS_ENDPOINT_COMP,

	/* .bMaxBurst           = 0, */
	/* .bmAttributes        = 0, */
	/* .wBytesPerInterval   = DYNAMIC */
पूर्ण;

अटल काष्ठा usb_descriptor_header *hidg_ss_descriptors[] = अणु
	(काष्ठा usb_descriptor_header *)&hidg_पूर्णांकerface_desc,
	(काष्ठा usb_descriptor_header *)&hidg_desc,
	(काष्ठा usb_descriptor_header *)&hidg_ss_in_ep_desc,
	(काष्ठा usb_descriptor_header *)&hidg_ss_in_comp_desc,
	(काष्ठा usb_descriptor_header *)&hidg_ss_out_ep_desc,
	(काष्ठा usb_descriptor_header *)&hidg_ss_out_comp_desc,
	शून्य,
पूर्ण;

/* High-Speed Support */

अटल काष्ठा usb_endpoपूर्णांक_descriptor hidg_hs_in_ep_desc = अणु
	.bLength		= USB_DT_ENDPOINT_SIZE,
	.bDescriptorType	= USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress	= USB_सूची_IN,
	.bmAttributes		= USB_ENDPOINT_XFER_INT,
	/*.wMaxPacketSize	= DYNAMIC */
	.bInterval		= 4, /* FIXME: Add this field in the
				      * HID gadget configuration?
				      * (काष्ठा hidg_func_descriptor)
				      */
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor hidg_hs_out_ep_desc = अणु
	.bLength		= USB_DT_ENDPOINT_SIZE,
	.bDescriptorType	= USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress	= USB_सूची_OUT,
	.bmAttributes		= USB_ENDPOINT_XFER_INT,
	/*.wMaxPacketSize	= DYNAMIC */
	.bInterval		= 4, /* FIXME: Add this field in the
				      * HID gadget configuration?
				      * (काष्ठा hidg_func_descriptor)
				      */
पूर्ण;

अटल काष्ठा usb_descriptor_header *hidg_hs_descriptors[] = अणु
	(काष्ठा usb_descriptor_header *)&hidg_पूर्णांकerface_desc,
	(काष्ठा usb_descriptor_header *)&hidg_desc,
	(काष्ठा usb_descriptor_header *)&hidg_hs_in_ep_desc,
	(काष्ठा usb_descriptor_header *)&hidg_hs_out_ep_desc,
	शून्य,
पूर्ण;

/* Full-Speed Support */

अटल काष्ठा usb_endpoपूर्णांक_descriptor hidg_fs_in_ep_desc = अणु
	.bLength		= USB_DT_ENDPOINT_SIZE,
	.bDescriptorType	= USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress	= USB_सूची_IN,
	.bmAttributes		= USB_ENDPOINT_XFER_INT,
	/*.wMaxPacketSize	= DYNAMIC */
	.bInterval		= 10, /* FIXME: Add this field in the
				       * HID gadget configuration?
				       * (काष्ठा hidg_func_descriptor)
				       */
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor hidg_fs_out_ep_desc = अणु
	.bLength		= USB_DT_ENDPOINT_SIZE,
	.bDescriptorType	= USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress	= USB_सूची_OUT,
	.bmAttributes		= USB_ENDPOINT_XFER_INT,
	/*.wMaxPacketSize	= DYNAMIC */
	.bInterval		= 10, /* FIXME: Add this field in the
				       * HID gadget configuration?
				       * (काष्ठा hidg_func_descriptor)
				       */
पूर्ण;

अटल काष्ठा usb_descriptor_header *hidg_fs_descriptors[] = अणु
	(काष्ठा usb_descriptor_header *)&hidg_पूर्णांकerface_desc,
	(काष्ठा usb_descriptor_header *)&hidg_desc,
	(काष्ठा usb_descriptor_header *)&hidg_fs_in_ep_desc,
	(काष्ठा usb_descriptor_header *)&hidg_fs_out_ep_desc,
	शून्य,
पूर्ण;

/*-------------------------------------------------------------------------*/
/*                                 Strings                                 */

#घोषणा CT_FUNC_HID_IDX	0

अटल काष्ठा usb_string ct_func_string_defs[] = अणु
	[CT_FUNC_HID_IDX].s	= "HID Interface",
	अणुपूर्ण,			/* end of list */
पूर्ण;

अटल काष्ठा usb_gadget_strings ct_func_string_table = अणु
	.language	= 0x0409,	/* en-US */
	.strings	= ct_func_string_defs,
पूर्ण;

अटल काष्ठा usb_gadget_strings *ct_func_strings[] = अणु
	&ct_func_string_table,
	शून्य,
पूर्ण;

/*-------------------------------------------------------------------------*/
/*                              Char Device                                */

अटल sमाप_प्रकार f_hidg_पढ़ो(काष्ठा file *file, अक्षर __user *buffer,
			माप_प्रकार count, loff_t *ptr)
अणु
	काष्ठा f_hidg *hidg = file->निजी_data;
	काष्ठा f_hidg_req_list *list;
	काष्ठा usb_request *req;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (!count)
		वापस 0;

	spin_lock_irqsave(&hidg->पढ़ो_spinlock, flags);

#घोषणा READ_COND (!list_empty(&hidg->completed_out_req))

	/* रुको क्रम at least one buffer to complete */
	जबतक (!READ_COND) अणु
		spin_unlock_irqrestore(&hidg->पढ़ो_spinlock, flags);
		अगर (file->f_flags & O_NONBLOCK)
			वापस -EAGAIN;

		अगर (रुको_event_पूर्णांकerruptible(hidg->पढ़ो_queue, READ_COND))
			वापस -ERESTARTSYS;

		spin_lock_irqsave(&hidg->पढ़ो_spinlock, flags);
	पूर्ण

	/* pick the first one */
	list = list_first_entry(&hidg->completed_out_req,
				काष्ठा f_hidg_req_list, list);

	/*
	 * Remove this from list to protect it from beign मुक्त()
	 * जबतक host disables our function
	 */
	list_del(&list->list);

	req = list->req;
	count = min_t(अचिन्हित पूर्णांक, count, req->actual - list->pos);
	spin_unlock_irqrestore(&hidg->पढ़ो_spinlock, flags);

	/* copy to user outside spinlock */
	count -= copy_to_user(buffer, req->buf + list->pos, count);
	list->pos += count;

	/*
	 * अगर this request is completely handled and transfered to
	 * userspace, हटाओ its entry from the list and requeue it
	 * again. Otherwise, we will revisit it again upon the next
	 * call, taking पूर्णांकo account its current पढ़ो position.
	 */
	अगर (list->pos == req->actual) अणु
		kमुक्त(list);

		req->length = hidg->report_length;
		ret = usb_ep_queue(hidg->out_ep, req, GFP_KERNEL);
		अगर (ret < 0) अणु
			मुक्त_ep_req(hidg->out_ep, req);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(&hidg->पढ़ो_spinlock, flags);
		list_add(&list->list, &hidg->completed_out_req);
		spin_unlock_irqrestore(&hidg->पढ़ो_spinlock, flags);

		wake_up(&hidg->पढ़ो_queue);
	पूर्ण

	वापस count;
पूर्ण

अटल व्योम f_hidg_req_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा f_hidg *hidg = (काष्ठा f_hidg *)ep->driver_data;
	अचिन्हित दीर्घ flags;

	अगर (req->status != 0) अणु
		ERROR(hidg->func.config->cdev,
			"End Point Request ERROR: %d\n", req->status);
	पूर्ण

	spin_lock_irqsave(&hidg->ग_लिखो_spinlock, flags);
	hidg->ग_लिखो_pending = 0;
	spin_unlock_irqrestore(&hidg->ग_लिखो_spinlock, flags);
	wake_up(&hidg->ग_लिखो_queue);
पूर्ण

अटल sमाप_प्रकार f_hidg_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
			    माप_प्रकार count, loff_t *offp)
अणु
	काष्ठा f_hidg *hidg  = file->निजी_data;
	काष्ठा usb_request *req;
	अचिन्हित दीर्घ flags;
	sमाप_प्रकार status = -ENOMEM;

	spin_lock_irqsave(&hidg->ग_लिखो_spinlock, flags);

#घोषणा WRITE_COND (!hidg->ग_लिखो_pending)
try_again:
	/* ग_लिखो queue */
	जबतक (!WRITE_COND) अणु
		spin_unlock_irqrestore(&hidg->ग_लिखो_spinlock, flags);
		अगर (file->f_flags & O_NONBLOCK)
			वापस -EAGAIN;

		अगर (रुको_event_पूर्णांकerruptible_exclusive(
				hidg->ग_लिखो_queue, WRITE_COND))
			वापस -ERESTARTSYS;

		spin_lock_irqsave(&hidg->ग_लिखो_spinlock, flags);
	पूर्ण

	hidg->ग_लिखो_pending = 1;
	req = hidg->req;
	count  = min_t(अचिन्हित, count, hidg->report_length);

	spin_unlock_irqrestore(&hidg->ग_लिखो_spinlock, flags);
	status = copy_from_user(req->buf, buffer, count);

	अगर (status != 0) अणु
		ERROR(hidg->func.config->cdev,
			"copy_from_user error\n");
		status = -EINVAL;
		जाओ release_ग_लिखो_pending;
	पूर्ण

	spin_lock_irqsave(&hidg->ग_लिखो_spinlock, flags);

	/* when our function has been disabled by host */
	अगर (!hidg->req) अणु
		मुक्त_ep_req(hidg->in_ep, req);
		/*
		 * TODO
		 * Should we fail with error here?
		 */
		जाओ try_again;
	पूर्ण

	req->status   = 0;
	req->zero     = 0;
	req->length   = count;
	req->complete = f_hidg_req_complete;
	req->context  = hidg;

	spin_unlock_irqrestore(&hidg->ग_लिखो_spinlock, flags);

	status = usb_ep_queue(hidg->in_ep, req, GFP_ATOMIC);
	अगर (status < 0) अणु
		ERROR(hidg->func.config->cdev,
			"usb_ep_queue error on int endpoint %zd\n", status);
		जाओ release_ग_लिखो_pending;
	पूर्ण अन्यथा अणु
		status = count;
	पूर्ण

	वापस status;
release_ग_लिखो_pending:
	spin_lock_irqsave(&hidg->ग_लिखो_spinlock, flags);
	hidg->ग_लिखो_pending = 0;
	spin_unlock_irqrestore(&hidg->ग_लिखो_spinlock, flags);

	wake_up(&hidg->ग_लिखो_queue);

	वापस status;
पूर्ण

अटल __poll_t f_hidg_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा f_hidg	*hidg  = file->निजी_data;
	__poll_t	ret = 0;

	poll_रुको(file, &hidg->पढ़ो_queue, रुको);
	poll_रुको(file, &hidg->ग_लिखो_queue, रुको);

	अगर (WRITE_COND)
		ret |= EPOLLOUT | EPOLLWRNORM;

	अगर (READ_COND)
		ret |= EPOLLIN | EPOLLRDNORM;

	वापस ret;
पूर्ण

#अघोषित WRITE_COND
#अघोषित READ_COND

अटल पूर्णांक f_hidg_release(काष्ठा inode *inode, काष्ठा file *fd)
अणु
	fd->निजी_data = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक f_hidg_खोलो(काष्ठा inode *inode, काष्ठा file *fd)
अणु
	काष्ठा f_hidg *hidg =
		container_of(inode->i_cdev, काष्ठा f_hidg, cdev);

	fd->निजी_data = hidg;

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/
/*                                usb_function                             */

अटल अंतरभूत काष्ठा usb_request *hidg_alloc_ep_req(काष्ठा usb_ep *ep,
						    अचिन्हित length)
अणु
	वापस alloc_ep_req(ep, length);
पूर्ण

अटल व्योम hidg_set_report_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा f_hidg *hidg = (काष्ठा f_hidg *) req->context;
	काष्ठा usb_composite_dev *cdev = hidg->func.config->cdev;
	काष्ठा f_hidg_req_list *req_list;
	अचिन्हित दीर्घ flags;

	चयन (req->status) अणु
	हाल 0:
		req_list = kzalloc(माप(*req_list), GFP_ATOMIC);
		अगर (!req_list) अणु
			ERROR(cdev, "Unable to allocate mem for req_list\n");
			जाओ मुक्त_req;
		पूर्ण

		req_list->req = req;

		spin_lock_irqsave(&hidg->पढ़ो_spinlock, flags);
		list_add_tail(&req_list->list, &hidg->completed_out_req);
		spin_unlock_irqrestore(&hidg->पढ़ो_spinlock, flags);

		wake_up(&hidg->पढ़ो_queue);
		अवरोध;
	शेष:
		ERROR(cdev, "Set report failed %d\n", req->status);
		fallthrough;
	हाल -ECONNABORTED:		/* hardware क्रमced ep reset */
	हाल -ECONNRESET:		/* request dequeued */
	हाल -ESHUTDOWN:		/* disconnect from host */
मुक्त_req:
		मुक्त_ep_req(ep, req);
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक hidg_setup(काष्ठा usb_function *f,
		स्थिर काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा f_hidg			*hidg = func_to_hidg(f);
	काष्ठा usb_composite_dev	*cdev = f->config->cdev;
	काष्ठा usb_request		*req  = cdev->req;
	पूर्णांक status = 0;
	__u16 value, length;

	value	= __le16_to_cpu(ctrl->wValue);
	length	= __le16_to_cpu(ctrl->wLength);

	VDBG(cdev,
	     "%s crtl_request : bRequestType:0x%x bRequest:0x%x Value:0x%x\n",
	     __func__, ctrl->bRequestType, ctrl->bRequest, value);

	चयन ((ctrl->bRequestType << 8) | ctrl->bRequest) अणु
	हाल ((USB_सूची_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE) << 8
		  | HID_REQ_GET_REPORT):
		VDBG(cdev, "get_report\n");

		/* send an empty report */
		length = min_t(अचिन्हित, length, hidg->report_length);
		स_रखो(req->buf, 0x0, length);

		जाओ respond;
		अवरोध;

	हाल ((USB_सूची_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE) << 8
		  | HID_REQ_GET_PROTOCOL):
		VDBG(cdev, "get_protocol\n");
		length = min_t(अचिन्हित पूर्णांक, length, 1);
		((u8 *) req->buf)[0] = hidg->protocol;
		जाओ respond;
		अवरोध;

	हाल ((USB_सूची_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE) << 8
		  | HID_REQ_SET_REPORT):
		VDBG(cdev, "set_report | wLength=%d\n", ctrl->wLength);
		जाओ stall;
		अवरोध;

	हाल ((USB_सूची_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE) << 8
		  | HID_REQ_SET_PROTOCOL):
		VDBG(cdev, "set_protocol\n");
		अगर (value > HID_REPORT_PROTOCOL)
			जाओ stall;
		length = 0;
		/*
		 * We assume that programs implementing the Boot protocol
		 * are also compatible with the Report Protocol
		 */
		अगर (hidg->bInterfaceSubClass == USB_INTERFACE_SUBCLASS_BOOT) अणु
			hidg->protocol = value;
			जाओ respond;
		पूर्ण
		जाओ stall;
		अवरोध;

	हाल ((USB_सूची_IN | USB_TYPE_STANDARD | USB_RECIP_INTERFACE) << 8
		  | USB_REQ_GET_DESCRIPTOR):
		चयन (value >> 8) अणु
		हाल HID_DT_HID:
		अणु
			काष्ठा hid_descriptor hidg_desc_copy = hidg_desc;

			VDBG(cdev, "USB_REQ_GET_DESCRIPTOR: HID\n");
			hidg_desc_copy.desc[0].bDescriptorType = HID_DT_REPORT;
			hidg_desc_copy.desc[0].wDescriptorLength =
				cpu_to_le16(hidg->report_desc_length);

			length = min_t(अचिन्हित लघु, length,
						   hidg_desc_copy.bLength);
			स_नकल(req->buf, &hidg_desc_copy, length);
			जाओ respond;
			अवरोध;
		पूर्ण
		हाल HID_DT_REPORT:
			VDBG(cdev, "USB_REQ_GET_DESCRIPTOR: REPORT\n");
			length = min_t(अचिन्हित लघु, length,
						   hidg->report_desc_length);
			स_नकल(req->buf, hidg->report_desc, length);
			जाओ respond;
			अवरोध;

		शेष:
			VDBG(cdev, "Unknown descriptor request 0x%x\n",
				 value >> 8);
			जाओ stall;
			अवरोध;
		पूर्ण
		अवरोध;

	शेष:
		VDBG(cdev, "Unknown request 0x%x\n",
			 ctrl->bRequest);
		जाओ stall;
		अवरोध;
	पूर्ण

stall:
	वापस -EOPNOTSUPP;

respond:
	req->zero = 0;
	req->length = length;
	status = usb_ep_queue(cdev->gadget->ep0, req, GFP_ATOMIC);
	अगर (status < 0)
		ERROR(cdev, "usb_ep_queue error on ep0 %d\n", value);
	वापस status;
पूर्ण

अटल व्योम hidg_disable(काष्ठा usb_function *f)
अणु
	काष्ठा f_hidg *hidg = func_to_hidg(f);
	काष्ठा f_hidg_req_list *list, *next;
	अचिन्हित दीर्घ flags;

	usb_ep_disable(hidg->in_ep);
	usb_ep_disable(hidg->out_ep);

	spin_lock_irqsave(&hidg->पढ़ो_spinlock, flags);
	list_क्रम_each_entry_safe(list, next, &hidg->completed_out_req, list) अणु
		मुक्त_ep_req(hidg->out_ep, list->req);
		list_del(&list->list);
		kमुक्त(list);
	पूर्ण
	spin_unlock_irqrestore(&hidg->पढ़ो_spinlock, flags);

	spin_lock_irqsave(&hidg->ग_लिखो_spinlock, flags);
	अगर (!hidg->ग_लिखो_pending) अणु
		मुक्त_ep_req(hidg->in_ep, hidg->req);
		hidg->ग_लिखो_pending = 1;
	पूर्ण

	hidg->req = शून्य;
	spin_unlock_irqrestore(&hidg->ग_लिखो_spinlock, flags);
पूर्ण

अटल पूर्णांक hidg_set_alt(काष्ठा usb_function *f, अचिन्हित पूर्णांकf, अचिन्हित alt)
अणु
	काष्ठा usb_composite_dev		*cdev = f->config->cdev;
	काष्ठा f_hidg				*hidg = func_to_hidg(f);
	काष्ठा usb_request			*req_in = शून्य;
	अचिन्हित दीर्घ				flags;
	पूर्णांक i, status = 0;

	VDBG(cdev, "hidg_set_alt intf:%d alt:%d\n", पूर्णांकf, alt);

	अगर (hidg->in_ep != शून्य) अणु
		/* restart endpoपूर्णांक */
		usb_ep_disable(hidg->in_ep);

		status = config_ep_by_speed(f->config->cdev->gadget, f,
					    hidg->in_ep);
		अगर (status) अणु
			ERROR(cdev, "config_ep_by_speed FAILED!\n");
			जाओ fail;
		पूर्ण
		status = usb_ep_enable(hidg->in_ep);
		अगर (status < 0) अणु
			ERROR(cdev, "Enable IN endpoint FAILED!\n");
			जाओ fail;
		पूर्ण
		hidg->in_ep->driver_data = hidg;

		req_in = hidg_alloc_ep_req(hidg->in_ep, hidg->report_length);
		अगर (!req_in) अणु
			status = -ENOMEM;
			जाओ disable_ep_in;
		पूर्ण
	पूर्ण


	अगर (hidg->out_ep != शून्य) अणु
		/* restart endpoपूर्णांक */
		usb_ep_disable(hidg->out_ep);

		status = config_ep_by_speed(f->config->cdev->gadget, f,
					    hidg->out_ep);
		अगर (status) अणु
			ERROR(cdev, "config_ep_by_speed FAILED!\n");
			जाओ मुक्त_req_in;
		पूर्ण
		status = usb_ep_enable(hidg->out_ep);
		अगर (status < 0) अणु
			ERROR(cdev, "Enable OUT endpoint FAILED!\n");
			जाओ मुक्त_req_in;
		पूर्ण
		hidg->out_ep->driver_data = hidg;

		/*
		 * allocate a bunch of पढ़ो buffers and queue them all at once.
		 */
		क्रम (i = 0; i < hidg->qlen && status == 0; i++) अणु
			काष्ठा usb_request *req =
					hidg_alloc_ep_req(hidg->out_ep,
							  hidg->report_length);
			अगर (req) अणु
				req->complete = hidg_set_report_complete;
				req->context  = hidg;
				status = usb_ep_queue(hidg->out_ep, req,
						      GFP_ATOMIC);
				अगर (status) अणु
					ERROR(cdev, "%s queue req --> %d\n",
						hidg->out_ep->name, status);
					मुक्त_ep_req(hidg->out_ep, req);
				पूर्ण
			पूर्ण अन्यथा अणु
				status = -ENOMEM;
				जाओ disable_out_ep;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (hidg->in_ep != शून्य) अणु
		spin_lock_irqsave(&hidg->ग_लिखो_spinlock, flags);
		hidg->req = req_in;
		hidg->ग_लिखो_pending = 0;
		spin_unlock_irqrestore(&hidg->ग_लिखो_spinlock, flags);

		wake_up(&hidg->ग_लिखो_queue);
	पूर्ण
	वापस 0;
disable_out_ep:
	usb_ep_disable(hidg->out_ep);
मुक्त_req_in:
	अगर (req_in)
		मुक्त_ep_req(hidg->in_ep, req_in);

disable_ep_in:
	अगर (hidg->in_ep)
		usb_ep_disable(hidg->in_ep);

fail:
	वापस status;
पूर्ण

अटल स्थिर काष्ठा file_operations f_hidg_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= f_hidg_खोलो,
	.release	= f_hidg_release,
	.ग_लिखो		= f_hidg_ग_लिखो,
	.पढ़ो		= f_hidg_पढ़ो,
	.poll		= f_hidg_poll,
	.llseek		= noop_llseek,
पूर्ण;

अटल पूर्णांक hidg_bind(काष्ठा usb_configuration *c, काष्ठा usb_function *f)
अणु
	काष्ठा usb_ep		*ep;
	काष्ठा f_hidg		*hidg = func_to_hidg(f);
	काष्ठा usb_string	*us;
	काष्ठा device		*device;
	पूर्णांक			status;
	dev_t			dev;

	/* maybe allocate device-global string IDs, and patch descriptors */
	us = usb_gstrings_attach(c->cdev, ct_func_strings,
				 ARRAY_SIZE(ct_func_string_defs));
	अगर (IS_ERR(us))
		वापस PTR_ERR(us);
	hidg_पूर्णांकerface_desc.iInterface = us[CT_FUNC_HID_IDX].id;

	/* allocate instance-specअगरic पूर्णांकerface IDs, and patch descriptors */
	status = usb_पूर्णांकerface_id(c, f);
	अगर (status < 0)
		जाओ fail;
	hidg_पूर्णांकerface_desc.bInterfaceNumber = status;

	/* allocate instance-specअगरic endpoपूर्णांकs */
	status = -ENODEV;
	ep = usb_ep_स्वतःconfig(c->cdev->gadget, &hidg_fs_in_ep_desc);
	अगर (!ep)
		जाओ fail;
	hidg->in_ep = ep;

	ep = usb_ep_स्वतःconfig(c->cdev->gadget, &hidg_fs_out_ep_desc);
	अगर (!ep)
		जाओ fail;
	hidg->out_ep = ep;

	/* set descriptor dynamic values */
	hidg_पूर्णांकerface_desc.bInterfaceSubClass = hidg->bInterfaceSubClass;
	hidg_पूर्णांकerface_desc.bInterfaceProtocol = hidg->bInterfaceProtocol;
	hidg->protocol = HID_REPORT_PROTOCOL;
	hidg_ss_in_ep_desc.wMaxPacketSize = cpu_to_le16(hidg->report_length);
	hidg_ss_in_comp_desc.wBytesPerInterval =
				cpu_to_le16(hidg->report_length);
	hidg_hs_in_ep_desc.wMaxPacketSize = cpu_to_le16(hidg->report_length);
	hidg_fs_in_ep_desc.wMaxPacketSize = cpu_to_le16(hidg->report_length);
	hidg_ss_out_ep_desc.wMaxPacketSize = cpu_to_le16(hidg->report_length);
	hidg_ss_out_comp_desc.wBytesPerInterval =
				cpu_to_le16(hidg->report_length);
	hidg_hs_out_ep_desc.wMaxPacketSize = cpu_to_le16(hidg->report_length);
	hidg_fs_out_ep_desc.wMaxPacketSize = cpu_to_le16(hidg->report_length);
	/*
	 * We can use hidg_desc काष्ठा here but we should not relay
	 * that its content won't change after वापसing from this function.
	 */
	hidg_desc.desc[0].bDescriptorType = HID_DT_REPORT;
	hidg_desc.desc[0].wDescriptorLength =
		cpu_to_le16(hidg->report_desc_length);

	hidg_hs_in_ep_desc.bEndpoपूर्णांकAddress =
		hidg_fs_in_ep_desc.bEndpoपूर्णांकAddress;
	hidg_hs_out_ep_desc.bEndpoपूर्णांकAddress =
		hidg_fs_out_ep_desc.bEndpoपूर्णांकAddress;

	hidg_ss_in_ep_desc.bEndpoपूर्णांकAddress =
		hidg_fs_in_ep_desc.bEndpoपूर्णांकAddress;
	hidg_ss_out_ep_desc.bEndpoपूर्णांकAddress =
		hidg_fs_out_ep_desc.bEndpoपूर्णांकAddress;

	status = usb_assign_descriptors(f, hidg_fs_descriptors,
			hidg_hs_descriptors, hidg_ss_descriptors,
			hidg_ss_descriptors);
	अगर (status)
		जाओ fail;

	spin_lock_init(&hidg->ग_लिखो_spinlock);
	hidg->ग_लिखो_pending = 1;
	hidg->req = शून्य;
	spin_lock_init(&hidg->पढ़ो_spinlock);
	init_रुकोqueue_head(&hidg->ग_लिखो_queue);
	init_रुकोqueue_head(&hidg->पढ़ो_queue);
	INIT_LIST_HEAD(&hidg->completed_out_req);

	/* create अक्षर device */
	cdev_init(&hidg->cdev, &f_hidg_fops);
	dev = MKDEV(major, hidg->minor);
	status = cdev_add(&hidg->cdev, dev, 1);
	अगर (status)
		जाओ fail_मुक्त_descs;

	device = device_create(hidg_class, शून्य, dev, शून्य,
			       "%s%d", "hidg", hidg->minor);
	अगर (IS_ERR(device)) अणु
		status = PTR_ERR(device);
		जाओ del;
	पूर्ण

	वापस 0;
del:
	cdev_del(&hidg->cdev);
fail_मुक्त_descs:
	usb_मुक्त_all_descriptors(f);
fail:
	ERROR(f->config->cdev, "hidg_bind FAILED\n");
	अगर (hidg->req != शून्य)
		मुक्त_ep_req(hidg->in_ep, hidg->req);

	वापस status;
पूर्ण

अटल अंतरभूत पूर्णांक hidg_get_minor(व्योम)
अणु
	पूर्णांक ret;

	ret = ida_simple_get(&hidg_ida, 0, 0, GFP_KERNEL);
	अगर (ret >= HIDG_MINORS) अणु
		ida_simple_हटाओ(&hidg_ida, ret);
		ret = -ENODEV;
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत काष्ठा f_hid_opts *to_f_hid_opts(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा f_hid_opts,
			    func_inst.group);
पूर्ण

अटल व्योम hid_attr_release(काष्ठा config_item *item)
अणु
	काष्ठा f_hid_opts *opts = to_f_hid_opts(item);

	usb_put_function_instance(&opts->func_inst);
पूर्ण

अटल काष्ठा configfs_item_operations hidg_item_ops = अणु
	.release	= hid_attr_release,
पूर्ण;

#घोषणा F_HID_OPT(name, prec, limit)					\
अटल sमाप_प्रकार f_hid_opts_##name##_show(काष्ठा config_item *item, अक्षर *page)\
अणु									\
	काष्ठा f_hid_opts *opts = to_f_hid_opts(item);			\
	पूर्णांक result;							\
									\
	mutex_lock(&opts->lock);					\
	result = प्र_लिखो(page, "%d\n", opts->name);			\
	mutex_unlock(&opts->lock);					\
									\
	वापस result;							\
पूर्ण									\
									\
अटल sमाप_प्रकार f_hid_opts_##name##_store(काष्ठा config_item *item,	\
					 स्थिर अक्षर *page, माप_प्रकार len)	\
अणु									\
	काष्ठा f_hid_opts *opts = to_f_hid_opts(item);			\
	पूर्णांक ret;							\
	u##prec num;							\
									\
	mutex_lock(&opts->lock);					\
	अगर (opts->refcnt) अणु						\
		ret = -EBUSY;						\
		जाओ end;						\
	पूर्ण								\
									\
	ret = kstrtou##prec(page, 0, &num);				\
	अगर (ret)							\
		जाओ end;						\
									\
	अगर (num > limit) अणु						\
		ret = -EINVAL;						\
		जाओ end;						\
	पूर्ण								\
	opts->name = num;						\
	ret = len;							\
									\
end:									\
	mutex_unlock(&opts->lock);					\
	वापस ret;							\
पूर्ण									\
									\
CONFIGFS_ATTR(f_hid_opts_, name)

F_HID_OPT(subclass, 8, 255);
F_HID_OPT(protocol, 8, 255);
F_HID_OPT(report_length, 16, 65535);

अटल sमाप_प्रकार f_hid_opts_report_desc_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा f_hid_opts *opts = to_f_hid_opts(item);
	पूर्णांक result;

	mutex_lock(&opts->lock);
	result = opts->report_desc_length;
	स_नकल(page, opts->report_desc, opts->report_desc_length);
	mutex_unlock(&opts->lock);

	वापस result;
पूर्ण

अटल sमाप_प्रकार f_hid_opts_report_desc_store(काष्ठा config_item *item,
					    स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा f_hid_opts *opts = to_f_hid_opts(item);
	पूर्णांक ret = -EBUSY;
	अक्षर *d;

	mutex_lock(&opts->lock);

	अगर (opts->refcnt)
		जाओ end;
	अगर (len > PAGE_SIZE) अणु
		ret = -ENOSPC;
		जाओ end;
	पूर्ण
	d = kmemdup(page, len, GFP_KERNEL);
	अगर (!d) अणु
		ret = -ENOMEM;
		जाओ end;
	पूर्ण
	kमुक्त(opts->report_desc);
	opts->report_desc = d;
	opts->report_desc_length = len;
	opts->report_desc_alloc = true;
	ret = len;
end:
	mutex_unlock(&opts->lock);
	वापस ret;
पूर्ण

CONFIGFS_ATTR(f_hid_opts_, report_desc);

अटल sमाप_प्रकार f_hid_opts_dev_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा f_hid_opts *opts = to_f_hid_opts(item);

	वापस प्र_लिखो(page, "%d:%d\n", major, opts->minor);
पूर्ण

CONFIGFS_ATTR_RO(f_hid_opts_, dev);

अटल काष्ठा configfs_attribute *hid_attrs[] = अणु
	&f_hid_opts_attr_subclass,
	&f_hid_opts_attr_protocol,
	&f_hid_opts_attr_report_length,
	&f_hid_opts_attr_report_desc,
	&f_hid_opts_attr_dev,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा config_item_type hid_func_type = अणु
	.ct_item_ops	= &hidg_item_ops,
	.ct_attrs	= hid_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल अंतरभूत व्योम hidg_put_minor(पूर्णांक minor)
अणु
	ida_simple_हटाओ(&hidg_ida, minor);
पूर्ण

अटल व्योम hidg_मुक्त_inst(काष्ठा usb_function_instance *f)
अणु
	काष्ठा f_hid_opts *opts;

	opts = container_of(f, काष्ठा f_hid_opts, func_inst);

	mutex_lock(&hidg_ida_lock);

	hidg_put_minor(opts->minor);
	अगर (ida_is_empty(&hidg_ida))
		ghid_cleanup();

	mutex_unlock(&hidg_ida_lock);

	अगर (opts->report_desc_alloc)
		kमुक्त(opts->report_desc);

	kमुक्त(opts);
पूर्ण

अटल काष्ठा usb_function_instance *hidg_alloc_inst(व्योम)
अणु
	काष्ठा f_hid_opts *opts;
	काष्ठा usb_function_instance *ret;
	पूर्णांक status = 0;

	opts = kzalloc(माप(*opts), GFP_KERNEL);
	अगर (!opts)
		वापस ERR_PTR(-ENOMEM);
	mutex_init(&opts->lock);
	opts->func_inst.मुक्त_func_inst = hidg_मुक्त_inst;
	ret = &opts->func_inst;

	mutex_lock(&hidg_ida_lock);

	अगर (ida_is_empty(&hidg_ida)) अणु
		status = ghid_setup(शून्य, HIDG_MINORS);
		अगर (status)  अणु
			ret = ERR_PTR(status);
			kमुक्त(opts);
			जाओ unlock;
		पूर्ण
	पूर्ण

	opts->minor = hidg_get_minor();
	अगर (opts->minor < 0) अणु
		ret = ERR_PTR(opts->minor);
		kमुक्त(opts);
		अगर (ida_is_empty(&hidg_ida))
			ghid_cleanup();
		जाओ unlock;
	पूर्ण
	config_group_init_type_name(&opts->func_inst.group, "", &hid_func_type);

unlock:
	mutex_unlock(&hidg_ida_lock);
	वापस ret;
पूर्ण

अटल व्योम hidg_मुक्त(काष्ठा usb_function *f)
अणु
	काष्ठा f_hidg *hidg;
	काष्ठा f_hid_opts *opts;

	hidg = func_to_hidg(f);
	opts = container_of(f->fi, काष्ठा f_hid_opts, func_inst);
	kमुक्त(hidg->report_desc);
	kमुक्त(hidg);
	mutex_lock(&opts->lock);
	--opts->refcnt;
	mutex_unlock(&opts->lock);
पूर्ण

अटल व्योम hidg_unbind(काष्ठा usb_configuration *c, काष्ठा usb_function *f)
अणु
	काष्ठा f_hidg *hidg = func_to_hidg(f);

	device_destroy(hidg_class, MKDEV(major, hidg->minor));
	cdev_del(&hidg->cdev);

	usb_मुक्त_all_descriptors(f);
पूर्ण

अटल काष्ठा usb_function *hidg_alloc(काष्ठा usb_function_instance *fi)
अणु
	काष्ठा f_hidg *hidg;
	काष्ठा f_hid_opts *opts;

	/* allocate and initialize one new instance */
	hidg = kzalloc(माप(*hidg), GFP_KERNEL);
	अगर (!hidg)
		वापस ERR_PTR(-ENOMEM);

	opts = container_of(fi, काष्ठा f_hid_opts, func_inst);

	mutex_lock(&opts->lock);
	++opts->refcnt;

	hidg->minor = opts->minor;
	hidg->bInterfaceSubClass = opts->subclass;
	hidg->bInterfaceProtocol = opts->protocol;
	hidg->report_length = opts->report_length;
	hidg->report_desc_length = opts->report_desc_length;
	अगर (opts->report_desc) अणु
		hidg->report_desc = kmemdup(opts->report_desc,
					    opts->report_desc_length,
					    GFP_KERNEL);
		अगर (!hidg->report_desc) अणु
			kमुक्त(hidg);
			mutex_unlock(&opts->lock);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
	पूर्ण

	mutex_unlock(&opts->lock);

	hidg->func.name    = "hid";
	hidg->func.bind    = hidg_bind;
	hidg->func.unbind  = hidg_unbind;
	hidg->func.set_alt = hidg_set_alt;
	hidg->func.disable = hidg_disable;
	hidg->func.setup   = hidg_setup;
	hidg->func.मुक्त_func = hidg_मुक्त;

	/* this could me made configurable at some poपूर्णांक */
	hidg->qlen	   = 4;

	वापस &hidg->func;
पूर्ण

DECLARE_USB_FUNCTION_INIT(hid, hidg_alloc_inst, hidg_alloc);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Fabien Chouteau");

पूर्णांक ghid_setup(काष्ठा usb_gadget *g, पूर्णांक count)
अणु
	पूर्णांक status;
	dev_t dev;

	hidg_class = class_create(THIS_MODULE, "hidg");
	अगर (IS_ERR(hidg_class)) अणु
		status = PTR_ERR(hidg_class);
		hidg_class = शून्य;
		वापस status;
	पूर्ण

	status = alloc_chrdev_region(&dev, 0, count, "hidg");
	अगर (status) अणु
		class_destroy(hidg_class);
		hidg_class = शून्य;
		वापस status;
	पूर्ण

	major = MAJOR(dev);
	minors = count;

	वापस 0;
पूर्ण

व्योम ghid_cleanup(व्योम)
अणु
	अगर (major) अणु
		unरेजिस्टर_chrdev_region(MKDEV(major, 0), minors);
		major = minors = 0;
	पूर्ण

	class_destroy(hidg_class);
	hidg_class = शून्य;
पूर्ण
