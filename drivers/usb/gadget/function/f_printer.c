<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * f_prपूर्णांकer.c - USB prपूर्णांकer function driver
 *
 * Copied from drivers/usb/gadget/legacy/prपूर्णांकer.c,
 * which was:
 *
 * prपूर्णांकer.c -- Prपूर्णांकer gadget driver
 *
 * Copyright (C) 2003-2005 David Brownell
 * Copyright (C) 2006 Craig W. Nadler
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/idr.h>
#समावेश <linux/समयr.h>
#समावेश <linux/list.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/fs.h>
#समावेश <linux/poll.h>
#समावेश <linux/types.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/cdev.h>
#समावेश <linux/kref.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/composite.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/g_prपूर्णांकer.h>

#समावेश "u_printer.h"

#घोषणा PRINTER_MINORS		4
#घोषणा GET_DEVICE_ID		0
#घोषणा GET_PORT_STATUS		1
#घोषणा SOFT_RESET		2

#घोषणा DEFAULT_Q_LEN		10 /* same as legacy g_prपूर्णांकer gadget */

अटल पूर्णांक major, minors;
अटल काष्ठा class *usb_gadget_class;
अटल DEFINE_IDA(prपूर्णांकer_ida);
अटल DEFINE_MUTEX(prपूर्णांकer_ida_lock); /* protects access करो prपूर्णांकer_ida */

/*-------------------------------------------------------------------------*/

काष्ठा prपूर्णांकer_dev अणु
	spinlock_t		lock;		/* lock this काष्ठाure */
	/* lock buffer lists during पढ़ो/ग_लिखो calls */
	काष्ठा mutex		lock_prपूर्णांकer_io;
	काष्ठा usb_gadget	*gadget;
	s8			पूर्णांकerface;
	काष्ठा usb_ep		*in_ep, *out_ep;
	काष्ठा kref             kref;
	काष्ठा list_head	rx_reqs;	/* List of मुक्त RX काष्ठाs */
	काष्ठा list_head	rx_reqs_active;	/* List of Active RX xfers */
	काष्ठा list_head	rx_buffers;	/* List of completed xfers */
	/* रुको until there is data to be पढ़ो. */
	रुको_queue_head_t	rx_रुको;
	काष्ठा list_head	tx_reqs;	/* List of मुक्त TX काष्ठाs */
	काष्ठा list_head	tx_reqs_active; /* List of Active TX xfers */
	/* Wait until there are ग_लिखो buffers available to use. */
	रुको_queue_head_t	tx_रुको;
	/* Wait until all ग_लिखो buffers have been sent. */
	रुको_queue_head_t	tx_flush_रुको;
	काष्ठा usb_request	*current_rx_req;
	माप_प्रकार			current_rx_bytes;
	u8			*current_rx_buf;
	u8			prपूर्णांकer_status;
	u8			reset_prपूर्णांकer;
	पूर्णांक			minor;
	काष्ठा cdev		prपूर्णांकer_cdev;
	u8			prपूर्णांकer_cdev_खोलो;
	रुको_queue_head_t	रुको;
	अचिन्हित		q_len;
	अक्षर			*pnp_string;	/* We करोn't own memory! */
	काष्ठा usb_function	function;
पूर्ण;

अटल अंतरभूत काष्ठा prपूर्णांकer_dev *func_to_prपूर्णांकer(काष्ठा usb_function *f)
अणु
	वापस container_of(f, काष्ठा prपूर्णांकer_dev, function);
पूर्ण

/*-------------------------------------------------------------------------*/

/*
 * DESCRIPTORS ... most are अटल, but strings and (full) configuration
 * descriptors are built on demand.
 */

/* holds our biggest descriptor */
#घोषणा USB_DESC_बफ_मानE		256
#घोषणा USB_बफ_मानE			8192

अटल काष्ठा usb_पूर्णांकerface_descriptor पूर्णांकf_desc = अणु
	.bLength =		माप(पूर्णांकf_desc),
	.bDescriptorType =	USB_DT_INTERFACE,
	.bNumEndpoपूर्णांकs =	2,
	.bInterfaceClass =	USB_CLASS_PRINTER,
	.bInterfaceSubClass =	1,	/* Prपूर्णांकer Sub-Class */
	.bInterfaceProtocol =	2,	/* Bi-Directional */
	.iInterface =		0
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor fs_ep_in_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor fs_ep_out_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress =	USB_सूची_OUT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK
पूर्ण;

अटल काष्ठा usb_descriptor_header *fs_prपूर्णांकer_function[] = अणु
	(काष्ठा usb_descriptor_header *) &पूर्णांकf_desc,
	(काष्ठा usb_descriptor_header *) &fs_ep_in_desc,
	(काष्ठा usb_descriptor_header *) &fs_ep_out_desc,
	शून्य
पूर्ण;

/*
 * usb 2.0 devices need to expose both high speed and full speed
 * descriptors, unless they only run at full speed.
 */

अटल काष्ठा usb_endpoपूर्णांक_descriptor hs_ep_in_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(512)
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor hs_ep_out_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(512)
पूर्ण;

अटल काष्ठा usb_descriptor_header *hs_prपूर्णांकer_function[] = अणु
	(काष्ठा usb_descriptor_header *) &पूर्णांकf_desc,
	(काष्ठा usb_descriptor_header *) &hs_ep_in_desc,
	(काष्ठा usb_descriptor_header *) &hs_ep_out_desc,
	शून्य
पूर्ण;

/*
 * Added endpoपूर्णांक descriptors क्रम 3.0 devices
 */

अटल काष्ठा usb_endpoपूर्णांक_descriptor ss_ep_in_desc = अणु
	.bLength =              USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =      USB_DT_ENDPOINT,
	.bmAttributes =         USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =       cpu_to_le16(1024),
पूर्ण;

अटल काष्ठा usb_ss_ep_comp_descriptor ss_ep_in_comp_desc = अणु
	.bLength =              माप(ss_ep_in_comp_desc),
	.bDescriptorType =      USB_DT_SS_ENDPOINT_COMP,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor ss_ep_out_desc = अणु
	.bLength =              USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =      USB_DT_ENDPOINT,
	.bmAttributes =         USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =       cpu_to_le16(1024),
पूर्ण;

अटल काष्ठा usb_ss_ep_comp_descriptor ss_ep_out_comp_desc = अणु
	.bLength =              माप(ss_ep_out_comp_desc),
	.bDescriptorType =      USB_DT_SS_ENDPOINT_COMP,
पूर्ण;

अटल काष्ठा usb_descriptor_header *ss_prपूर्णांकer_function[] = अणु
	(काष्ठा usb_descriptor_header *) &पूर्णांकf_desc,
	(काष्ठा usb_descriptor_header *) &ss_ep_in_desc,
	(काष्ठा usb_descriptor_header *) &ss_ep_in_comp_desc,
	(काष्ठा usb_descriptor_header *) &ss_ep_out_desc,
	(काष्ठा usb_descriptor_header *) &ss_ep_out_comp_desc,
	शून्य
पूर्ण;

/* maxpacket and other transfer अक्षरacteristics vary by speed. */
अटल अंतरभूत काष्ठा usb_endpoपूर्णांक_descriptor *ep_desc(काष्ठा usb_gadget *gadget,
					काष्ठा usb_endpoपूर्णांक_descriptor *fs,
					काष्ठा usb_endpoपूर्णांक_descriptor *hs,
					काष्ठा usb_endpoपूर्णांक_descriptor *ss)
अणु
	चयन (gadget->speed) अणु
	हाल USB_SPEED_SUPER:
		वापस ss;
	हाल USB_SPEED_HIGH:
		वापस hs;
	शेष:
		वापस fs;
	पूर्ण
पूर्ण

/*-------------------------------------------------------------------------*/

अटल व्योम prपूर्णांकer_dev_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा prपूर्णांकer_dev *dev = container_of(kref, काष्ठा prपूर्णांकer_dev, kref);

	kमुक्त(dev);
पूर्ण

अटल काष्ठा usb_request *
prपूर्णांकer_req_alloc(काष्ठा usb_ep *ep, अचिन्हित len, gfp_t gfp_flags)
अणु
	काष्ठा usb_request	*req;

	req = usb_ep_alloc_request(ep, gfp_flags);

	अगर (req != शून्य) अणु
		req->length = len;
		req->buf = kदो_स्मृति(len, gfp_flags);
		अगर (req->buf == शून्य) अणु
			usb_ep_मुक्त_request(ep, req);
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस req;
पूर्ण

अटल व्योम
prपूर्णांकer_req_मुक्त(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	अगर (ep != शून्य && req != शून्य) अणु
		kमुक्त(req->buf);
		usb_ep_मुक्त_request(ep, req);
	पूर्ण
पूर्ण

/*-------------------------------------------------------------------------*/

अटल व्योम rx_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा prपूर्णांकer_dev	*dev = ep->driver_data;
	पूर्णांक			status = req->status;
	अचिन्हित दीर्घ		flags;

	spin_lock_irqsave(&dev->lock, flags);

	list_del_init(&req->list);	/* Remode from Active List */

	चयन (status) अणु

	/* normal completion */
	हाल 0:
		अगर (req->actual > 0) अणु
			list_add_tail(&req->list, &dev->rx_buffers);
			DBG(dev, "G_Printer : rx length %d\n", req->actual);
		पूर्ण अन्यथा अणु
			list_add(&req->list, &dev->rx_reqs);
		पूर्ण
		अवरोध;

	/* software-driven पूर्णांकerface shutकरोwn */
	हाल -ECONNRESET:		/* unlink */
	हाल -ESHUTDOWN:		/* disconnect etc */
		VDBG(dev, "rx shutdown, code %d\n", status);
		list_add(&req->list, &dev->rx_reqs);
		अवरोध;

	/* क्रम hardware स्वतःmagic (such as pxa) */
	हाल -ECONNABORTED:		/* endpoपूर्णांक reset */
		DBG(dev, "rx %s reset\n", ep->name);
		list_add(&req->list, &dev->rx_reqs);
		अवरोध;

	/* data overrun */
	हाल -EOVERFLOW:
		fallthrough;

	शेष:
		DBG(dev, "rx status %d\n", status);
		list_add(&req->list, &dev->rx_reqs);
		अवरोध;
	पूर्ण

	wake_up_पूर्णांकerruptible(&dev->rx_रुको);
	spin_unlock_irqrestore(&dev->lock, flags);
पूर्ण

अटल व्योम tx_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा prपूर्णांकer_dev	*dev = ep->driver_data;

	चयन (req->status) अणु
	शेष:
		VDBG(dev, "tx err %d\n", req->status);
		fallthrough;
	हाल -ECONNRESET:		/* unlink */
	हाल -ESHUTDOWN:		/* disconnect etc */
		अवरोध;
	हाल 0:
		अवरोध;
	पूर्ण

	spin_lock(&dev->lock);
	/* Take the request काष्ठा off the active list and put it on the
	 * मुक्त list.
	 */
	list_del_init(&req->list);
	list_add(&req->list, &dev->tx_reqs);
	wake_up_पूर्णांकerruptible(&dev->tx_रुको);
	अगर (likely(list_empty(&dev->tx_reqs_active)))
		wake_up_पूर्णांकerruptible(&dev->tx_flush_रुको);

	spin_unlock(&dev->lock);
पूर्ण

/*-------------------------------------------------------------------------*/

अटल पूर्णांक
prपूर्णांकer_खोलो(काष्ठा inode *inode, काष्ठा file *fd)
अणु
	काष्ठा prपूर्णांकer_dev	*dev;
	अचिन्हित दीर्घ		flags;
	पूर्णांक			ret = -EBUSY;

	dev = container_of(inode->i_cdev, काष्ठा prपूर्णांकer_dev, prपूर्णांकer_cdev);

	spin_lock_irqsave(&dev->lock, flags);

	अगर (dev->पूर्णांकerface < 0) अणु
		spin_unlock_irqrestore(&dev->lock, flags);
		वापस -ENODEV;
	पूर्ण

	अगर (!dev->prपूर्णांकer_cdev_खोलो) अणु
		dev->prपूर्णांकer_cdev_खोलो = 1;
		fd->निजी_data = dev;
		ret = 0;
		/* Change the prपूर्णांकer status to show that it's on-line. */
		dev->prपूर्णांकer_status |= PRINTER_SELECTED;
	पूर्ण

	spin_unlock_irqrestore(&dev->lock, flags);

	kref_get(&dev->kref);
	DBG(dev, "printer_open returned %x\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक
prपूर्णांकer_बंद(काष्ठा inode *inode, काष्ठा file *fd)
अणु
	काष्ठा prपूर्णांकer_dev	*dev = fd->निजी_data;
	अचिन्हित दीर्घ		flags;

	spin_lock_irqsave(&dev->lock, flags);
	dev->prपूर्णांकer_cdev_खोलो = 0;
	fd->निजी_data = शून्य;
	/* Change prपूर्णांकer status to show that the prपूर्णांकer is off-line. */
	dev->prपूर्णांकer_status &= ~PRINTER_SELECTED;
	spin_unlock_irqrestore(&dev->lock, flags);

	kref_put(&dev->kref, prपूर्णांकer_dev_मुक्त);
	DBG(dev, "printer_close\n");

	वापस 0;
पूर्ण

/* This function must be called with पूर्णांकerrupts turned off. */
अटल व्योम
setup_rx_reqs(काष्ठा prपूर्णांकer_dev *dev)
अणु
	काष्ठा usb_request              *req;

	जबतक (likely(!list_empty(&dev->rx_reqs))) अणु
		पूर्णांक error;

		req = container_of(dev->rx_reqs.next,
				काष्ठा usb_request, list);
		list_del_init(&req->list);

		/* The USB Host sends us whatever amount of data it wants to
		 * so we always set the length field to the full USB_बफ_मानE.
		 * If the amount of data is more than the पढ़ो() caller asked
		 * क्रम it will be stored in the request buffer until it is
		 * asked क्रम by पढ़ो().
		 */
		req->length = USB_बफ_मानE;
		req->complete = rx_complete;

		/* here, we unlock, and only unlock, to aव्योम deadlock. */
		spin_unlock(&dev->lock);
		error = usb_ep_queue(dev->out_ep, req, GFP_ATOMIC);
		spin_lock(&dev->lock);
		अगर (error) अणु
			DBG(dev, "rx submit --> %d\n", error);
			list_add(&req->list, &dev->rx_reqs);
			अवरोध;
		पूर्ण
		/* अगर the req is empty, then add it पूर्णांकo dev->rx_reqs_active. */
		अन्यथा अगर (list_empty(&req->list))
			list_add(&req->list, &dev->rx_reqs_active);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार
prपूर्णांकer_पढ़ो(काष्ठा file *fd, अक्षर __user *buf, माप_प्रकार len, loff_t *ptr)
अणु
	काष्ठा prपूर्णांकer_dev		*dev = fd->निजी_data;
	अचिन्हित दीर्घ			flags;
	माप_प्रकार				size;
	माप_प्रकार				bytes_copied;
	काष्ठा usb_request		*req;
	/* This is a poपूर्णांकer to the current USB rx request. */
	काष्ठा usb_request		*current_rx_req;
	/* This is the number of bytes in the current rx buffer. */
	माप_प्रकार				current_rx_bytes;
	/* This is a poपूर्णांकer to the current rx buffer. */
	u8				*current_rx_buf;

	अगर (len == 0)
		वापस -EINVAL;

	DBG(dev, "printer_read trying to read %d bytes\n", (पूर्णांक)len);

	mutex_lock(&dev->lock_prपूर्णांकer_io);
	spin_lock_irqsave(&dev->lock, flags);

	अगर (dev->पूर्णांकerface < 0) अणु
		spin_unlock_irqrestore(&dev->lock, flags);
		mutex_unlock(&dev->lock_prपूर्णांकer_io);
		वापस -ENODEV;
	पूर्ण

	/* We will use this flag later to check अगर a prपूर्णांकer reset happened
	 * after we turn पूर्णांकerrupts back on.
	 */
	dev->reset_prपूर्णांकer = 0;

	setup_rx_reqs(dev);

	bytes_copied = 0;
	current_rx_req = dev->current_rx_req;
	current_rx_bytes = dev->current_rx_bytes;
	current_rx_buf = dev->current_rx_buf;
	dev->current_rx_req = शून्य;
	dev->current_rx_bytes = 0;
	dev->current_rx_buf = शून्य;

	/* Check अगर there is any data in the पढ़ो buffers. Please note that
	 * current_rx_bytes is the number of bytes in the current rx buffer.
	 * If it is zero then check अगर there are any other rx_buffers that
	 * are on the completed list. We are only out of data अगर all rx
	 * buffers are empty.
	 */
	अगर ((current_rx_bytes == 0) &&
			(likely(list_empty(&dev->rx_buffers)))) अणु
		/* Turn पूर्णांकerrupts back on beक्रमe sleeping. */
		spin_unlock_irqrestore(&dev->lock, flags);

		/*
		 * If no data is available check अगर this is a NON-Blocking
		 * call or not.
		 */
		अगर (fd->f_flags & (O_NONBLOCK|O_NDELAY)) अणु
			mutex_unlock(&dev->lock_prपूर्णांकer_io);
			वापस -EAGAIN;
		पूर्ण

		/* Sleep until data is available */
		रुको_event_पूर्णांकerruptible(dev->rx_रुको,
				(likely(!list_empty(&dev->rx_buffers))));
		spin_lock_irqsave(&dev->lock, flags);
	पूर्ण

	/* We have data to वापस then copy it to the caller's buffer.*/
	जबतक ((current_rx_bytes || likely(!list_empty(&dev->rx_buffers)))
			&& len) अणु
		अगर (current_rx_bytes == 0) अणु
			req = container_of(dev->rx_buffers.next,
					काष्ठा usb_request, list);
			list_del_init(&req->list);

			अगर (req->actual && req->buf) अणु
				current_rx_req = req;
				current_rx_bytes = req->actual;
				current_rx_buf = req->buf;
			पूर्ण अन्यथा अणु
				list_add(&req->list, &dev->rx_reqs);
				जारी;
			पूर्ण
		पूर्ण

		/* Don't leave irqs off जबतक करोing memory copies */
		spin_unlock_irqrestore(&dev->lock, flags);

		अगर (len > current_rx_bytes)
			size = current_rx_bytes;
		अन्यथा
			size = len;

		size -= copy_to_user(buf, current_rx_buf, size);
		bytes_copied += size;
		len -= size;
		buf += size;

		spin_lock_irqsave(&dev->lock, flags);

		/* We've disconnected or reset so वापस. */
		अगर (dev->reset_prपूर्णांकer) अणु
			list_add(&current_rx_req->list, &dev->rx_reqs);
			spin_unlock_irqrestore(&dev->lock, flags);
			mutex_unlock(&dev->lock_prपूर्णांकer_io);
			वापस -EAGAIN;
		पूर्ण

		/* If we not वापसing all the data left in this RX request
		 * buffer then adjust the amount of data left in the buffer.
		 * Othewise अगर we are करोne with this RX request buffer then
		 * requeue it to get any incoming data from the USB host.
		 */
		अगर (size < current_rx_bytes) अणु
			current_rx_bytes -= size;
			current_rx_buf += size;
		पूर्ण अन्यथा अणु
			list_add(&current_rx_req->list, &dev->rx_reqs);
			current_rx_bytes = 0;
			current_rx_buf = शून्य;
			current_rx_req = शून्य;
		पूर्ण
	पूर्ण

	dev->current_rx_req = current_rx_req;
	dev->current_rx_bytes = current_rx_bytes;
	dev->current_rx_buf = current_rx_buf;

	spin_unlock_irqrestore(&dev->lock, flags);
	mutex_unlock(&dev->lock_prपूर्णांकer_io);

	DBG(dev, "printer_read returned %d bytes\n", (पूर्णांक)bytes_copied);

	अगर (bytes_copied)
		वापस bytes_copied;
	अन्यथा
		वापस -EAGAIN;
पूर्ण

अटल sमाप_प्रकार
prपूर्णांकer_ग_लिखो(काष्ठा file *fd, स्थिर अक्षर __user *buf, माप_प्रकार len, loff_t *ptr)
अणु
	काष्ठा prपूर्णांकer_dev	*dev = fd->निजी_data;
	अचिन्हित दीर्घ		flags;
	माप_प्रकार			size;	/* Amount of data in a TX request. */
	माप_प्रकार			bytes_copied = 0;
	काष्ठा usb_request	*req;
	पूर्णांक			value;

	DBG(dev, "printer_write trying to send %d bytes\n", (पूर्णांक)len);

	अगर (len == 0)
		वापस -EINVAL;

	mutex_lock(&dev->lock_prपूर्णांकer_io);
	spin_lock_irqsave(&dev->lock, flags);

	अगर (dev->पूर्णांकerface < 0) अणु
		spin_unlock_irqrestore(&dev->lock, flags);
		mutex_unlock(&dev->lock_prपूर्णांकer_io);
		वापस -ENODEV;
	पूर्ण

	/* Check अगर a prपूर्णांकer reset happens जबतक we have पूर्णांकerrupts on */
	dev->reset_prपूर्णांकer = 0;

	/* Check अगर there is any available ग_लिखो buffers */
	अगर (likely(list_empty(&dev->tx_reqs))) अणु
		/* Turn पूर्णांकerrupts back on beक्रमe sleeping. */
		spin_unlock_irqrestore(&dev->lock, flags);

		/*
		 * If ग_लिखो buffers are available check अगर this is
		 * a NON-Blocking call or not.
		 */
		अगर (fd->f_flags & (O_NONBLOCK|O_NDELAY)) अणु
			mutex_unlock(&dev->lock_prपूर्णांकer_io);
			वापस -EAGAIN;
		पूर्ण

		/* Sleep until a ग_लिखो buffer is available */
		रुको_event_पूर्णांकerruptible(dev->tx_रुको,
				(likely(!list_empty(&dev->tx_reqs))));
		spin_lock_irqsave(&dev->lock, flags);
	पूर्ण

	जबतक (likely(!list_empty(&dev->tx_reqs)) && len) अणु

		अगर (len > USB_बफ_मानE)
			size = USB_बफ_मानE;
		अन्यथा
			size = len;

		req = container_of(dev->tx_reqs.next, काष्ठा usb_request,
				list);
		list_del_init(&req->list);

		req->complete = tx_complete;
		req->length = size;

		/* Check अगर we need to send a zero length packet. */
		अगर (len > size)
			/* They will be more TX requests so no yet. */
			req->zero = 0;
		अन्यथा
			/* If the data amount is not a multiple of the
			 * maxpacket size then send a zero length packet.
			 */
			req->zero = ((len % dev->in_ep->maxpacket) == 0);

		/* Don't leave irqs off जबतक करोing memory copies */
		spin_unlock_irqrestore(&dev->lock, flags);

		अगर (copy_from_user(req->buf, buf, size)) अणु
			list_add(&req->list, &dev->tx_reqs);
			mutex_unlock(&dev->lock_prपूर्णांकer_io);
			वापस bytes_copied;
		पूर्ण

		bytes_copied += size;
		len -= size;
		buf += size;

		spin_lock_irqsave(&dev->lock, flags);

		/* We've disconnected or reset so मुक्त the req and buffer */
		अगर (dev->reset_prपूर्णांकer) अणु
			list_add(&req->list, &dev->tx_reqs);
			spin_unlock_irqrestore(&dev->lock, flags);
			mutex_unlock(&dev->lock_prपूर्णांकer_io);
			वापस -EAGAIN;
		पूर्ण

		list_add(&req->list, &dev->tx_reqs_active);

		/* here, we unlock, and only unlock, to aव्योम deadlock. */
		spin_unlock(&dev->lock);
		value = usb_ep_queue(dev->in_ep, req, GFP_ATOMIC);
		spin_lock(&dev->lock);
		अगर (value) अणु
			list_del(&req->list);
			list_add(&req->list, &dev->tx_reqs);
			spin_unlock_irqrestore(&dev->lock, flags);
			mutex_unlock(&dev->lock_prपूर्णांकer_io);
			वापस -EAGAIN;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&dev->lock, flags);
	mutex_unlock(&dev->lock_prपूर्णांकer_io);

	DBG(dev, "printer_write sent %d bytes\n", (पूर्णांक)bytes_copied);

	अगर (bytes_copied)
		वापस bytes_copied;
	अन्यथा
		वापस -EAGAIN;
पूर्ण

अटल पूर्णांक
prपूर्णांकer_fsync(काष्ठा file *fd, loff_t start, loff_t end, पूर्णांक datasync)
अणु
	काष्ठा prपूर्णांकer_dev	*dev = fd->निजी_data;
	काष्ठा inode *inode = file_inode(fd);
	अचिन्हित दीर्घ		flags;
	पूर्णांक			tx_list_empty;

	inode_lock(inode);
	spin_lock_irqsave(&dev->lock, flags);

	अगर (dev->पूर्णांकerface < 0) अणु
		spin_unlock_irqrestore(&dev->lock, flags);
		inode_unlock(inode);
		वापस -ENODEV;
	पूर्ण

	tx_list_empty = (likely(list_empty(&dev->tx_reqs)));
	spin_unlock_irqrestore(&dev->lock, flags);

	अगर (!tx_list_empty) अणु
		/* Sleep until all data has been sent */
		रुको_event_पूर्णांकerruptible(dev->tx_flush_रुको,
				(likely(list_empty(&dev->tx_reqs_active))));
	पूर्ण
	inode_unlock(inode);

	वापस 0;
पूर्ण

अटल __poll_t
prपूर्णांकer_poll(काष्ठा file *fd, poll_table *रुको)
अणु
	काष्ठा prपूर्णांकer_dev	*dev = fd->निजी_data;
	अचिन्हित दीर्घ		flags;
	__poll_t		status = 0;

	mutex_lock(&dev->lock_prपूर्णांकer_io);
	spin_lock_irqsave(&dev->lock, flags);

	अगर (dev->पूर्णांकerface < 0) अणु
		spin_unlock_irqrestore(&dev->lock, flags);
		mutex_unlock(&dev->lock_prपूर्णांकer_io);
		वापस EPOLLERR | EPOLLHUP;
	पूर्ण

	setup_rx_reqs(dev);
	spin_unlock_irqrestore(&dev->lock, flags);
	mutex_unlock(&dev->lock_prपूर्णांकer_io);

	poll_रुको(fd, &dev->rx_रुको, रुको);
	poll_रुको(fd, &dev->tx_रुको, रुको);

	spin_lock_irqsave(&dev->lock, flags);
	अगर (likely(!list_empty(&dev->tx_reqs)))
		status |= EPOLLOUT | EPOLLWRNORM;

	अगर (likely(dev->current_rx_bytes) ||
			likely(!list_empty(&dev->rx_buffers)))
		status |= EPOLLIN | EPOLLRDNORM;

	spin_unlock_irqrestore(&dev->lock, flags);

	वापस status;
पूर्ण

अटल दीर्घ
prपूर्णांकer_ioctl(काष्ठा file *fd, अचिन्हित पूर्णांक code, अचिन्हित दीर्घ arg)
अणु
	काष्ठा prपूर्णांकer_dev	*dev = fd->निजी_data;
	अचिन्हित दीर्घ		flags;
	पूर्णांक			status = 0;

	DBG(dev, "printer_ioctl: cmd=0x%4.4x, arg=%lu\n", code, arg);

	/* handle ioctls */

	spin_lock_irqsave(&dev->lock, flags);

	अगर (dev->पूर्णांकerface < 0) अणु
		spin_unlock_irqrestore(&dev->lock, flags);
		वापस -ENODEV;
	पूर्ण

	चयन (code) अणु
	हाल GADGET_GET_PRINTER_STATUS:
		status = (पूर्णांक)dev->prपूर्णांकer_status;
		अवरोध;
	हाल GADGET_SET_PRINTER_STATUS:
		dev->prपूर्णांकer_status = (u8)arg;
		अवरोध;
	शेष:
		/* could not handle ioctl */
		DBG(dev, "printer_ioctl: ERROR cmd=0x%4.4xis not supported\n",
				code);
		status = -ENOTTY;
	पूर्ण

	spin_unlock_irqrestore(&dev->lock, flags);

	वापस status;
पूर्ण

/* used after endpoपूर्णांक configuration */
अटल स्थिर काष्ठा file_operations prपूर्णांकer_io_operations = अणु
	.owner =	THIS_MODULE,
	.खोलो =		prपूर्णांकer_खोलो,
	.पढ़ो =		prपूर्णांकer_पढ़ो,
	.ग_लिखो =	prपूर्णांकer_ग_लिखो,
	.fsync =	prपूर्णांकer_fsync,
	.poll =		prपूर्णांकer_poll,
	.unlocked_ioctl = prपूर्णांकer_ioctl,
	.release =	prपूर्णांकer_बंद,
	.llseek =	noop_llseek,
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल पूर्णांक
set_prपूर्णांकer_पूर्णांकerface(काष्ठा prपूर्णांकer_dev *dev)
अणु
	पूर्णांक			result = 0;

	dev->in_ep->desc = ep_desc(dev->gadget, &fs_ep_in_desc, &hs_ep_in_desc,
				&ss_ep_in_desc);
	dev->in_ep->driver_data = dev;

	dev->out_ep->desc = ep_desc(dev->gadget, &fs_ep_out_desc,
				    &hs_ep_out_desc, &ss_ep_out_desc);
	dev->out_ep->driver_data = dev;

	result = usb_ep_enable(dev->in_ep);
	अगर (result != 0) अणु
		DBG(dev, "enable %s --> %d\n", dev->in_ep->name, result);
		जाओ करोne;
	पूर्ण

	result = usb_ep_enable(dev->out_ep);
	अगर (result != 0) अणु
		DBG(dev, "enable %s --> %d\n", dev->out_ep->name, result);
		जाओ करोne;
	पूर्ण

करोne:
	/* on error, disable any endpoपूर्णांकs  */
	अगर (result != 0) अणु
		(व्योम) usb_ep_disable(dev->in_ep);
		(व्योम) usb_ep_disable(dev->out_ep);
		dev->in_ep->desc = शून्य;
		dev->out_ep->desc = शून्य;
	पूर्ण

	/* caller is responsible क्रम cleanup on error */
	वापस result;
पूर्ण

अटल व्योम prपूर्णांकer_reset_पूर्णांकerface(काष्ठा prपूर्णांकer_dev *dev)
अणु
	अचिन्हित दीर्घ	flags;

	अगर (dev->पूर्णांकerface < 0)
		वापस;

	DBG(dev, "%s\n", __func__);

	अगर (dev->in_ep->desc)
		usb_ep_disable(dev->in_ep);

	अगर (dev->out_ep->desc)
		usb_ep_disable(dev->out_ep);

	spin_lock_irqsave(&dev->lock, flags);
	dev->in_ep->desc = शून्य;
	dev->out_ep->desc = शून्य;
	dev->पूर्णांकerface = -1;
	spin_unlock_irqrestore(&dev->lock, flags);
पूर्ण

/* Change our operational Interface. */
अटल पूर्णांक set_पूर्णांकerface(काष्ठा prपूर्णांकer_dev *dev, अचिन्हित number)
अणु
	पूर्णांक			result = 0;

	/* Free the current पूर्णांकerface */
	prपूर्णांकer_reset_पूर्णांकerface(dev);

	result = set_prपूर्णांकer_पूर्णांकerface(dev);
	अगर (result)
		prपूर्णांकer_reset_पूर्णांकerface(dev);
	अन्यथा
		dev->पूर्णांकerface = number;

	अगर (!result)
		INFO(dev, "Using interface %x\n", number);

	वापस result;
पूर्ण

अटल व्योम prपूर्णांकer_soft_reset(काष्ठा prपूर्णांकer_dev *dev)
अणु
	काष्ठा usb_request	*req;

	INFO(dev, "Received Printer Reset Request\n");

	अगर (usb_ep_disable(dev->in_ep))
		DBG(dev, "Failed to disable USB in_ep\n");
	अगर (usb_ep_disable(dev->out_ep))
		DBG(dev, "Failed to disable USB out_ep\n");

	अगर (dev->current_rx_req != शून्य) अणु
		list_add(&dev->current_rx_req->list, &dev->rx_reqs);
		dev->current_rx_req = शून्य;
	पूर्ण
	dev->current_rx_bytes = 0;
	dev->current_rx_buf = शून्य;
	dev->reset_prपूर्णांकer = 1;

	जबतक (likely(!(list_empty(&dev->rx_buffers)))) अणु
		req = container_of(dev->rx_buffers.next, काष्ठा usb_request,
				list);
		list_del_init(&req->list);
		list_add(&req->list, &dev->rx_reqs);
	पूर्ण

	जबतक (likely(!(list_empty(&dev->rx_reqs_active)))) अणु
		req = container_of(dev->rx_buffers.next, काष्ठा usb_request,
				list);
		list_del_init(&req->list);
		list_add(&req->list, &dev->rx_reqs);
	पूर्ण

	जबतक (likely(!(list_empty(&dev->tx_reqs_active)))) अणु
		req = container_of(dev->tx_reqs_active.next,
				काष्ठा usb_request, list);
		list_del_init(&req->list);
		list_add(&req->list, &dev->tx_reqs);
	पूर्ण

	अगर (usb_ep_enable(dev->in_ep))
		DBG(dev, "Failed to enable USB in_ep\n");
	अगर (usb_ep_enable(dev->out_ep))
		DBG(dev, "Failed to enable USB out_ep\n");

	wake_up_पूर्णांकerruptible(&dev->rx_रुको);
	wake_up_पूर्णांकerruptible(&dev->tx_रुको);
	wake_up_पूर्णांकerruptible(&dev->tx_flush_रुको);
पूर्ण

/*-------------------------------------------------------------------------*/

अटल bool gprपूर्णांकer_req_match(काष्ठा usb_function *f,
			       स्थिर काष्ठा usb_ctrlrequest *ctrl,
			       bool config0)
अणु
	काष्ठा prपूर्णांकer_dev	*dev = func_to_prपूर्णांकer(f);
	u16			w_index = le16_to_cpu(ctrl->wIndex);
	u16			w_value = le16_to_cpu(ctrl->wValue);
	u16			w_length = le16_to_cpu(ctrl->wLength);

	अगर (config0)
		वापस false;

	अगर ((ctrl->bRequestType & USB_RECIP_MASK) != USB_RECIP_INTERFACE ||
	    (ctrl->bRequestType & USB_TYPE_MASK) != USB_TYPE_CLASS)
		वापस false;

	चयन (ctrl->bRequest) अणु
	हाल GET_DEVICE_ID:
		w_index >>= 8;
		अगर (USB_सूची_IN & ctrl->bRequestType)
			अवरोध;
		वापस false;
	हाल GET_PORT_STATUS:
		अगर (!w_value && w_length == 1 &&
		    (USB_सूची_IN & ctrl->bRequestType))
			अवरोध;
		वापस false;
	हाल SOFT_RESET:
		अगर (!w_value && !w_length &&
		   !(USB_सूची_IN & ctrl->bRequestType))
			अवरोध;
		fallthrough;
	शेष:
		वापस false;
	पूर्ण
	वापस w_index == dev->पूर्णांकerface;
पूर्ण

/*
 * The setup() callback implements all the ep0 functionality that's not
 * handled lower करोwn.
 */
अटल पूर्णांक prपूर्णांकer_func_setup(काष्ठा usb_function *f,
		स्थिर काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा prपूर्णांकer_dev *dev = func_to_prपूर्णांकer(f);
	काष्ठा usb_composite_dev *cdev = f->config->cdev;
	काष्ठा usb_request	*req = cdev->req;
	u8			*buf = req->buf;
	पूर्णांक			value = -EOPNOTSUPP;
	u16			wIndex = le16_to_cpu(ctrl->wIndex);
	u16			wValue = le16_to_cpu(ctrl->wValue);
	u16			wLength = le16_to_cpu(ctrl->wLength);

	DBG(dev, "ctrl req%02x.%02x v%04x i%04x l%d\n",
		ctrl->bRequestType, ctrl->bRequest, wValue, wIndex, wLength);

	चयन (ctrl->bRequestType&USB_TYPE_MASK) अणु
	हाल USB_TYPE_CLASS:
		चयन (ctrl->bRequest) अणु
		हाल GET_DEVICE_ID: /* Get the IEEE-1284 PNP String */
			/* Only one prपूर्णांकer पूर्णांकerface is supported. */
			अगर ((wIndex>>8) != dev->पूर्णांकerface)
				अवरोध;

			अगर (!dev->pnp_string) अणु
				value = 0;
				अवरोध;
			पूर्ण
			value = म_माप(dev->pnp_string);
			buf[0] = (value >> 8) & 0xFF;
			buf[1] = value & 0xFF;
			स_नकल(buf + 2, dev->pnp_string, value);
			DBG(dev, "1284 PNP String: %x %s\n", value,
			    dev->pnp_string);
			अवरोध;

		हाल GET_PORT_STATUS: /* Get Port Status */
			/* Only one prपूर्णांकer पूर्णांकerface is supported. */
			अगर (wIndex != dev->पूर्णांकerface)
				अवरोध;

			buf[0] = dev->prपूर्णांकer_status;
			value = min_t(u16, wLength, 1);
			अवरोध;

		हाल SOFT_RESET: /* Soft Reset */
			/* Only one prपूर्णांकer पूर्णांकerface is supported. */
			अगर (wIndex != dev->पूर्णांकerface)
				अवरोध;

			prपूर्णांकer_soft_reset(dev);

			value = 0;
			अवरोध;

		शेष:
			जाओ unknown;
		पूर्ण
		अवरोध;

	शेष:
unknown:
		VDBG(dev,
			"unknown ctrl req%02x.%02x v%04x i%04x l%d\n",
			ctrl->bRequestType, ctrl->bRequest,
			wValue, wIndex, wLength);
		अवरोध;
	पूर्ण
	/* host either stalls (value < 0) or reports success */
	अगर (value >= 0) अणु
		req->length = value;
		req->zero = value < wLength;
		value = usb_ep_queue(cdev->gadget->ep0, req, GFP_ATOMIC);
		अगर (value < 0) अणु
			ERROR(dev, "%s:%d Error!\n", __func__, __LINE__);
			req->status = 0;
		पूर्ण
	पूर्ण
	वापस value;
पूर्ण

अटल पूर्णांक prपूर्णांकer_func_bind(काष्ठा usb_configuration *c,
		काष्ठा usb_function *f)
अणु
	काष्ठा usb_gadget *gadget = c->cdev->gadget;
	काष्ठा prपूर्णांकer_dev *dev = func_to_prपूर्णांकer(f);
	काष्ठा device *pdev;
	काष्ठा usb_composite_dev *cdev = c->cdev;
	काष्ठा usb_ep *in_ep;
	काष्ठा usb_ep *out_ep = शून्य;
	काष्ठा usb_request *req;
	dev_t devt;
	पूर्णांक id;
	पूर्णांक ret;
	u32 i;

	id = usb_पूर्णांकerface_id(c, f);
	अगर (id < 0)
		वापस id;
	पूर्णांकf_desc.bInterfaceNumber = id;

	/* finish hookup to lower layer ... */
	dev->gadget = gadget;

	/* all we really need is bulk IN/OUT */
	in_ep = usb_ep_स्वतःconfig(cdev->gadget, &fs_ep_in_desc);
	अगर (!in_ep) अणु
स्वतःconf_fail:
		dev_err(&cdev->gadget->dev, "can't autoconfigure on %s\n",
			cdev->gadget->name);
		वापस -ENODEV;
	पूर्ण

	out_ep = usb_ep_स्वतःconfig(cdev->gadget, &fs_ep_out_desc);
	अगर (!out_ep)
		जाओ स्वतःconf_fail;

	/* assumes that all endpoपूर्णांकs are dual-speed */
	hs_ep_in_desc.bEndpoपूर्णांकAddress = fs_ep_in_desc.bEndpoपूर्णांकAddress;
	hs_ep_out_desc.bEndpoपूर्णांकAddress = fs_ep_out_desc.bEndpoपूर्णांकAddress;
	ss_ep_in_desc.bEndpoपूर्णांकAddress = fs_ep_in_desc.bEndpoपूर्णांकAddress;
	ss_ep_out_desc.bEndpoपूर्णांकAddress = fs_ep_out_desc.bEndpoपूर्णांकAddress;

	ret = usb_assign_descriptors(f, fs_prपूर्णांकer_function,
			hs_prपूर्णांकer_function, ss_prपूर्णांकer_function,
			ss_prपूर्णांकer_function);
	अगर (ret)
		वापस ret;

	dev->in_ep = in_ep;
	dev->out_ep = out_ep;

	ret = -ENOMEM;
	क्रम (i = 0; i < dev->q_len; i++) अणु
		req = prपूर्णांकer_req_alloc(dev->in_ep, USB_बफ_मानE, GFP_KERNEL);
		अगर (!req)
			जाओ fail_tx_reqs;
		list_add(&req->list, &dev->tx_reqs);
	पूर्ण

	क्रम (i = 0; i < dev->q_len; i++) अणु
		req = prपूर्णांकer_req_alloc(dev->out_ep, USB_बफ_मानE, GFP_KERNEL);
		अगर (!req)
			जाओ fail_rx_reqs;
		list_add(&req->list, &dev->rx_reqs);
	पूर्ण

	/* Setup the sysfs files क्रम the prपूर्णांकer gadget. */
	devt = MKDEV(major, dev->minor);
	pdev = device_create(usb_gadget_class, शून्य, devt,
				  शून्य, "g_printer%d", dev->minor);
	अगर (IS_ERR(pdev)) अणु
		ERROR(dev, "Failed to create device: g_printer\n");
		ret = PTR_ERR(pdev);
		जाओ fail_rx_reqs;
	पूर्ण

	/*
	 * Register a अक्षरacter device as an पूर्णांकerface to a user mode
	 * program that handles the prपूर्णांकer specअगरic functionality.
	 */
	cdev_init(&dev->prपूर्णांकer_cdev, &prपूर्णांकer_io_operations);
	dev->prपूर्णांकer_cdev.owner = THIS_MODULE;
	ret = cdev_add(&dev->prपूर्णांकer_cdev, devt, 1);
	अगर (ret) अणु
		ERROR(dev, "Failed to open char device\n");
		जाओ fail_cdev_add;
	पूर्ण

	वापस 0;

fail_cdev_add:
	device_destroy(usb_gadget_class, devt);

fail_rx_reqs:
	जबतक (!list_empty(&dev->rx_reqs)) अणु
		req = container_of(dev->rx_reqs.next, काष्ठा usb_request, list);
		list_del(&req->list);
		prपूर्णांकer_req_मुक्त(dev->out_ep, req);
	पूर्ण

fail_tx_reqs:
	जबतक (!list_empty(&dev->tx_reqs)) अणु
		req = container_of(dev->tx_reqs.next, काष्ठा usb_request, list);
		list_del(&req->list);
		prपूर्णांकer_req_मुक्त(dev->in_ep, req);
	पूर्ण

	usb_मुक्त_all_descriptors(f);
	वापस ret;

पूर्ण

अटल पूर्णांक prपूर्णांकer_func_set_alt(काष्ठा usb_function *f,
		अचिन्हित पूर्णांकf, अचिन्हित alt)
अणु
	काष्ठा prपूर्णांकer_dev *dev = func_to_prपूर्णांकer(f);
	पूर्णांक ret = -ENOTSUPP;

	अगर (!alt)
		ret = set_पूर्णांकerface(dev, पूर्णांकf);

	वापस ret;
पूर्ण

अटल व्योम prपूर्णांकer_func_disable(काष्ठा usb_function *f)
अणु
	काष्ठा prपूर्णांकer_dev *dev = func_to_prपूर्णांकer(f);

	DBG(dev, "%s\n", __func__);

	prपूर्णांकer_reset_पूर्णांकerface(dev);
पूर्ण

अटल अंतरभूत काष्ठा f_prपूर्णांकer_opts
*to_f_prपूर्णांकer_opts(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा f_prपूर्णांकer_opts,
			    func_inst.group);
पूर्ण

अटल व्योम prपूर्णांकer_attr_release(काष्ठा config_item *item)
अणु
	काष्ठा f_prपूर्णांकer_opts *opts = to_f_prपूर्णांकer_opts(item);

	usb_put_function_instance(&opts->func_inst);
पूर्ण

अटल काष्ठा configfs_item_operations prपूर्णांकer_item_ops = अणु
	.release	= prपूर्णांकer_attr_release,
पूर्ण;

अटल sमाप_प्रकार f_prपूर्णांकer_opts_pnp_string_show(काष्ठा config_item *item,
					      अक्षर *page)
अणु
	काष्ठा f_prपूर्णांकer_opts *opts = to_f_prपूर्णांकer_opts(item);
	पूर्णांक result = 0;

	mutex_lock(&opts->lock);
	अगर (!opts->pnp_string)
		जाओ unlock;

	result = strlcpy(page, opts->pnp_string, PAGE_SIZE);
	अगर (result >= PAGE_SIZE) अणु
		result = PAGE_SIZE;
	पूर्ण अन्यथा अगर (page[result - 1] != '\n' && result + 1 < PAGE_SIZE) अणु
		page[result++] = '\n';
		page[result] = '\0';
	पूर्ण

unlock:
	mutex_unlock(&opts->lock);

	वापस result;
पूर्ण

अटल sमाप_प्रकार f_prपूर्णांकer_opts_pnp_string_store(काष्ठा config_item *item,
					       स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा f_prपूर्णांकer_opts *opts = to_f_prपूर्णांकer_opts(item);
	अक्षर *new_pnp;
	पूर्णांक result;

	mutex_lock(&opts->lock);

	new_pnp = kstrndup(page, len, GFP_KERNEL);
	अगर (!new_pnp) अणु
		result = -ENOMEM;
		जाओ unlock;
	पूर्ण

	अगर (opts->pnp_string_allocated)
		kमुक्त(opts->pnp_string);

	opts->pnp_string_allocated = true;
	opts->pnp_string = new_pnp;
	result = len;
unlock:
	mutex_unlock(&opts->lock);

	वापस result;
पूर्ण

CONFIGFS_ATTR(f_prपूर्णांकer_opts_, pnp_string);

अटल sमाप_प्रकार f_prपूर्णांकer_opts_q_len_show(काष्ठा config_item *item,
					 अक्षर *page)
अणु
	काष्ठा f_prपूर्णांकer_opts *opts = to_f_prपूर्णांकer_opts(item);
	पूर्णांक result;

	mutex_lock(&opts->lock);
	result = प्र_लिखो(page, "%d\n", opts->q_len);
	mutex_unlock(&opts->lock);

	वापस result;
पूर्ण

अटल sमाप_प्रकार f_prपूर्णांकer_opts_q_len_store(काष्ठा config_item *item,
					  स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा f_prपूर्णांकer_opts *opts = to_f_prपूर्णांकer_opts(item);
	पूर्णांक ret;
	u16 num;

	mutex_lock(&opts->lock);
	अगर (opts->refcnt) अणु
		ret = -EBUSY;
		जाओ end;
	पूर्ण

	ret = kstrtou16(page, 0, &num);
	अगर (ret)
		जाओ end;

	opts->q_len = (अचिन्हित)num;
	ret = len;
end:
	mutex_unlock(&opts->lock);
	वापस ret;
पूर्ण

CONFIGFS_ATTR(f_prपूर्णांकer_opts_, q_len);

अटल काष्ठा configfs_attribute *prपूर्णांकer_attrs[] = अणु
	&f_prपूर्णांकer_opts_attr_pnp_string,
	&f_prपूर्णांकer_opts_attr_q_len,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा config_item_type prपूर्णांकer_func_type = अणु
	.ct_item_ops	= &prपूर्णांकer_item_ops,
	.ct_attrs	= prपूर्णांकer_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल अंतरभूत पूर्णांक gprपूर्णांकer_get_minor(व्योम)
अणु
	पूर्णांक ret;

	ret = ida_simple_get(&prपूर्णांकer_ida, 0, 0, GFP_KERNEL);
	अगर (ret >= PRINTER_MINORS) अणु
		ida_simple_हटाओ(&prपूर्णांकer_ida, ret);
		ret = -ENODEV;
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम gprपूर्णांकer_put_minor(पूर्णांक minor)
अणु
	ida_simple_हटाओ(&prपूर्णांकer_ida, minor);
पूर्ण

अटल पूर्णांक gprपूर्णांकer_setup(पूर्णांक);
अटल व्योम gprपूर्णांकer_cleanup(व्योम);

अटल व्योम gprपूर्णांकer_मुक्त_inst(काष्ठा usb_function_instance *f)
अणु
	काष्ठा f_prपूर्णांकer_opts *opts;

	opts = container_of(f, काष्ठा f_prपूर्णांकer_opts, func_inst);

	mutex_lock(&prपूर्णांकer_ida_lock);

	gprपूर्णांकer_put_minor(opts->minor);
	अगर (ida_is_empty(&prपूर्णांकer_ida))
		gprपूर्णांकer_cleanup();

	mutex_unlock(&prपूर्णांकer_ida_lock);

	अगर (opts->pnp_string_allocated)
		kमुक्त(opts->pnp_string);
	kमुक्त(opts);
पूर्ण

अटल काष्ठा usb_function_instance *gprपूर्णांकer_alloc_inst(व्योम)
अणु
	काष्ठा f_prपूर्णांकer_opts *opts;
	काष्ठा usb_function_instance *ret;
	पूर्णांक status = 0;

	opts = kzalloc(माप(*opts), GFP_KERNEL);
	अगर (!opts)
		वापस ERR_PTR(-ENOMEM);

	mutex_init(&opts->lock);
	opts->func_inst.मुक्त_func_inst = gprपूर्णांकer_मुक्त_inst;
	ret = &opts->func_inst;

	/* Make sure q_len is initialized, otherwise the bound device can't support पढ़ो/ग_लिखो! */
	opts->q_len = DEFAULT_Q_LEN;

	mutex_lock(&prपूर्णांकer_ida_lock);

	अगर (ida_is_empty(&prपूर्णांकer_ida)) अणु
		status = gprपूर्णांकer_setup(PRINTER_MINORS);
		अगर (status) अणु
			ret = ERR_PTR(status);
			kमुक्त(opts);
			जाओ unlock;
		पूर्ण
	पूर्ण

	opts->minor = gprपूर्णांकer_get_minor();
	अगर (opts->minor < 0) अणु
		ret = ERR_PTR(opts->minor);
		kमुक्त(opts);
		अगर (ida_is_empty(&prपूर्णांकer_ida))
			gprपूर्णांकer_cleanup();
		जाओ unlock;
	पूर्ण
	config_group_init_type_name(&opts->func_inst.group, "",
				    &prपूर्णांकer_func_type);

unlock:
	mutex_unlock(&prपूर्णांकer_ida_lock);
	वापस ret;
पूर्ण

अटल व्योम gprपूर्णांकer_मुक्त(काष्ठा usb_function *f)
अणु
	काष्ठा prपूर्णांकer_dev *dev = func_to_prपूर्णांकer(f);
	काष्ठा f_prपूर्णांकer_opts *opts;

	opts = container_of(f->fi, काष्ठा f_prपूर्णांकer_opts, func_inst);

	kref_put(&dev->kref, prपूर्णांकer_dev_मुक्त);
	mutex_lock(&opts->lock);
	--opts->refcnt;
	mutex_unlock(&opts->lock);
पूर्ण

अटल व्योम prपूर्णांकer_func_unbind(काष्ठा usb_configuration *c,
		काष्ठा usb_function *f)
अणु
	काष्ठा prपूर्णांकer_dev	*dev;
	काष्ठा usb_request	*req;

	dev = func_to_prपूर्णांकer(f);

	device_destroy(usb_gadget_class, MKDEV(major, dev->minor));

	/* Remove Character Device */
	cdev_del(&dev->prपूर्णांकer_cdev);

	/* we must alपढ़ोy have been disconnected ... no i/o may be active */
	WARN_ON(!list_empty(&dev->tx_reqs_active));
	WARN_ON(!list_empty(&dev->rx_reqs_active));

	/* Free all memory क्रम this driver. */
	जबतक (!list_empty(&dev->tx_reqs)) अणु
		req = container_of(dev->tx_reqs.next, काष्ठा usb_request,
				list);
		list_del(&req->list);
		prपूर्णांकer_req_मुक्त(dev->in_ep, req);
	पूर्ण

	अगर (dev->current_rx_req != शून्य)
		prपूर्णांकer_req_मुक्त(dev->out_ep, dev->current_rx_req);

	जबतक (!list_empty(&dev->rx_reqs)) अणु
		req = container_of(dev->rx_reqs.next,
				काष्ठा usb_request, list);
		list_del(&req->list);
		prपूर्णांकer_req_मुक्त(dev->out_ep, req);
	पूर्ण

	जबतक (!list_empty(&dev->rx_buffers)) अणु
		req = container_of(dev->rx_buffers.next,
				काष्ठा usb_request, list);
		list_del(&req->list);
		prपूर्णांकer_req_मुक्त(dev->out_ep, req);
	पूर्ण
	usb_मुक्त_all_descriptors(f);
पूर्ण

अटल काष्ठा usb_function *gprपूर्णांकer_alloc(काष्ठा usb_function_instance *fi)
अणु
	काष्ठा prपूर्णांकer_dev	*dev;
	काष्ठा f_prपूर्णांकer_opts	*opts;

	opts = container_of(fi, काष्ठा f_prपूर्णांकer_opts, func_inst);

	mutex_lock(&opts->lock);
	अगर (opts->minor >= minors) अणु
		mutex_unlock(&opts->lock);
		वापस ERR_PTR(-ENOENT);
	पूर्ण

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev) अणु
		mutex_unlock(&opts->lock);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	kref_init(&dev->kref);
	++opts->refcnt;
	dev->minor = opts->minor;
	dev->pnp_string = opts->pnp_string;
	dev->q_len = opts->q_len;
	mutex_unlock(&opts->lock);

	dev->function.name = "printer";
	dev->function.bind = prपूर्णांकer_func_bind;
	dev->function.setup = prपूर्णांकer_func_setup;
	dev->function.unbind = prपूर्णांकer_func_unbind;
	dev->function.set_alt = prपूर्णांकer_func_set_alt;
	dev->function.disable = prपूर्णांकer_func_disable;
	dev->function.req_match = gprपूर्णांकer_req_match;
	dev->function.मुक्त_func = gprपूर्णांकer_मुक्त;

	INIT_LIST_HEAD(&dev->tx_reqs);
	INIT_LIST_HEAD(&dev->rx_reqs);
	INIT_LIST_HEAD(&dev->rx_buffers);
	INIT_LIST_HEAD(&dev->tx_reqs_active);
	INIT_LIST_HEAD(&dev->rx_reqs_active);

	spin_lock_init(&dev->lock);
	mutex_init(&dev->lock_prपूर्णांकer_io);
	init_रुकोqueue_head(&dev->rx_रुको);
	init_रुकोqueue_head(&dev->tx_रुको);
	init_रुकोqueue_head(&dev->tx_flush_रुको);

	dev->पूर्णांकerface = -1;
	dev->prपूर्णांकer_cdev_खोलो = 0;
	dev->prपूर्णांकer_status = PRINTER_NOT_ERROR;
	dev->current_rx_req = शून्य;
	dev->current_rx_bytes = 0;
	dev->current_rx_buf = शून्य;

	वापस &dev->function;
पूर्ण

DECLARE_USB_FUNCTION_INIT(prपूर्णांकer, gprपूर्णांकer_alloc_inst, gprपूर्णांकer_alloc);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Craig Nadler");

अटल पूर्णांक gprपूर्णांकer_setup(पूर्णांक count)
अणु
	पूर्णांक status;
	dev_t devt;

	usb_gadget_class = class_create(THIS_MODULE, "usb_printer_gadget");
	अगर (IS_ERR(usb_gadget_class)) अणु
		status = PTR_ERR(usb_gadget_class);
		usb_gadget_class = शून्य;
		pr_err("unable to create usb_gadget class %d\n", status);
		वापस status;
	पूर्ण

	status = alloc_chrdev_region(&devt, 0, count, "USB printer gadget");
	अगर (status) अणु
		pr_err("alloc_chrdev_region %d\n", status);
		class_destroy(usb_gadget_class);
		usb_gadget_class = शून्य;
		वापस status;
	पूर्ण

	major = MAJOR(devt);
	minors = count;

	वापस status;
पूर्ण

अटल व्योम gprपूर्णांकer_cleanup(व्योम)
अणु
	अगर (major) अणु
		unरेजिस्टर_chrdev_region(MKDEV(major, 0), minors);
		major = minors = 0;
	पूर्ण
	class_destroy(usb_gadget_class);
	usb_gadget_class = शून्य;
पूर्ण
