<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Greybus "AP" USB driver क्रम "ES2" controller chips
 *
 * Copyright 2014-2015 Google Inc.
 * Copyright 2014-2015 Linaro Ltd.
 */
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/sizes.h>
#समावेश <linux/usb.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/list.h>
#समावेश <linux/greybus.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "arpc.h"
#समावेश "greybus_trace.h"


/* Default समयout क्रम USB venकरोr requests. */
#घोषणा ES2_USB_CTRL_TIMEOUT	500

/* Default समयout क्रम ARPC CPort requests */
#घोषणा ES2_ARPC_CPORT_TIMEOUT	500

/* Fixed CPort numbers */
#घोषणा ES2_CPORT_CDSI0		16
#घोषणा ES2_CPORT_CDSI1		17

/* Memory sizes क्रम the buffers sent to/from the ES2 controller */
#घोषणा ES2_GBUF_MSG_SIZE_MAX	2048

/* Memory sizes क्रम the ARPC buffers */
#घोषणा ARPC_OUT_SIZE_MAX	U16_MAX
#घोषणा ARPC_IN_SIZE_MAX	128

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु USB_DEVICE(0x18d1, 0x1eaf) पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(usb, id_table);

#घोषणा APB1_LOG_SIZE		SZ_16K

/*
 * Number of CPort IN urbs in flight at any poपूर्णांक in समय.
 * Adjust अगर we are having stalls in the USB buffer due to not enough urbs in
 * flight.
 */
#घोषणा NUM_CPORT_IN_URB	4

/* Number of CPort OUT urbs in flight at any poपूर्णांक in समय.
 * Adjust अगर we get messages saying we are out of urbs in the प्रणाली log.
 */
#घोषणा NUM_CPORT_OUT_URB	8

/*
 * Number of ARPC in urbs in flight at any poपूर्णांक in समय.
 */
#घोषणा NUM_ARPC_IN_URB		2

/*
 * @endpoपूर्णांक: bulk in endpoपूर्णांक क्रम CPort data
 * @urb: array of urbs क्रम the CPort in messages
 * @buffer: array of buffers क्रम the @cport_in_urb urbs
 */
काष्ठा es2_cport_in अणु
	__u8 endpoपूर्णांक;
	काष्ठा urb *urb[NUM_CPORT_IN_URB];
	u8 *buffer[NUM_CPORT_IN_URB];
पूर्ण;

/**
 * काष्ठा es2_ap_dev - ES2 USB Bridge to AP काष्ठाure
 * @usb_dev: poपूर्णांकer to the USB device we are.
 * @usb_पूर्णांकf: poपूर्णांकer to the USB पूर्णांकerface we are bound to.
 * @hd: poपूर्णांकer to our gb_host_device काष्ठाure
 *
 * @cport_in: endpoपूर्णांक, urbs and buffer क्रम cport in messages
 * @cport_out_endpoपूर्णांक: endpoपूर्णांक क्रम क्रम cport out messages
 * @cport_out_urb: array of urbs क्रम the CPort out messages
 * @cport_out_urb_busy: array of flags to see अगर the @cport_out_urb is busy or
 *			not.
 * @cport_out_urb_cancelled: array of flags indicating whether the
 *			corresponding @cport_out_urb is being cancelled
 * @cport_out_urb_lock: locks the @cport_out_urb_busy "list"
 * @cdsi1_in_use: true अगर cport CDSI1 is in use
 * @apb_log_task: task poपूर्णांकer क्रम logging thपढ़ो
 * @apb_log_dentry: file प्रणाली entry क्रम the log file पूर्णांकerface
 * @apb_log_enable_dentry: file प्रणाली entry क्रम enabling logging
 * @apb_log_fअगरo: kernel FIFO to carry logged data
 * @arpc_urb: array of urbs क्रम the ARPC in messages
 * @arpc_buffer: array of buffers क्रम the @arpc_urb urbs
 * @arpc_endpoपूर्णांक_in: bulk in endpoपूर्णांक क्रम APBridgeA RPC
 * @arpc_id_cycle: gives an unique id to ARPC
 * @arpc_lock: locks ARPC list
 * @arpcs: list of in progress ARPCs
 */
काष्ठा es2_ap_dev अणु
	काष्ठा usb_device *usb_dev;
	काष्ठा usb_पूर्णांकerface *usb_पूर्णांकf;
	काष्ठा gb_host_device *hd;

	काष्ठा es2_cport_in cport_in;
	__u8 cport_out_endpoपूर्णांक;
	काष्ठा urb *cport_out_urb[NUM_CPORT_OUT_URB];
	bool cport_out_urb_busy[NUM_CPORT_OUT_URB];
	bool cport_out_urb_cancelled[NUM_CPORT_OUT_URB];
	spinlock_t cport_out_urb_lock;

	bool cdsi1_in_use;

	काष्ठा task_काष्ठा *apb_log_task;
	काष्ठा dentry *apb_log_dentry;
	काष्ठा dentry *apb_log_enable_dentry;
	DECLARE_KFIFO(apb_log_fअगरo, अक्षर, APB1_LOG_SIZE);

	__u8 arpc_endpoपूर्णांक_in;
	काष्ठा urb *arpc_urb[NUM_ARPC_IN_URB];
	u8 *arpc_buffer[NUM_ARPC_IN_URB];

	पूर्णांक arpc_id_cycle;
	spinlock_t arpc_lock;
	काष्ठा list_head arpcs;
पूर्ण;

काष्ठा arpc अणु
	काष्ठा list_head list;
	काष्ठा arpc_request_message *req;
	काष्ठा arpc_response_message *resp;
	काष्ठा completion response_received;
	bool active;
पूर्ण;

अटल अंतरभूत काष्ठा es2_ap_dev *hd_to_es2(काष्ठा gb_host_device *hd)
अणु
	वापस (काष्ठा es2_ap_dev *)&hd->hd_priv;
पूर्ण

अटल व्योम cport_out_callback(काष्ठा urb *urb);
अटल व्योम usb_log_enable(काष्ठा es2_ap_dev *es2);
अटल व्योम usb_log_disable(काष्ठा es2_ap_dev *es2);
अटल पूर्णांक arpc_sync(काष्ठा es2_ap_dev *es2, u8 type, व्योम *payload,
		     माप_प्रकार size, पूर्णांक *result, अचिन्हित पूर्णांक समयout);

अटल पूर्णांक output_sync(काष्ठा es2_ap_dev *es2, व्योम *req, u16 size, u8 cmd)
अणु
	काष्ठा usb_device *udev = es2->usb_dev;
	u8 *data;
	पूर्णांक retval;

	data = kmemdup(req, size, GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	retval = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
				 cmd,
				 USB_सूची_OUT | USB_TYPE_VENDOR |
				 USB_RECIP_INTERFACE,
				 0, 0, data, size, ES2_USB_CTRL_TIMEOUT);
	अगर (retval < 0)
		dev_err(&udev->dev, "%s: return error %d\n", __func__, retval);
	अन्यथा
		retval = 0;

	kमुक्त(data);
	वापस retval;
पूर्ण

अटल व्योम ap_urb_complete(काष्ठा urb *urb)
अणु
	काष्ठा usb_ctrlrequest *dr = urb->context;

	kमुक्त(dr);
	usb_मुक्त_urb(urb);
पूर्ण

अटल पूर्णांक output_async(काष्ठा es2_ap_dev *es2, व्योम *req, u16 size, u8 cmd)
अणु
	काष्ठा usb_device *udev = es2->usb_dev;
	काष्ठा urb *urb;
	काष्ठा usb_ctrlrequest *dr;
	u8 *buf;
	पूर्णांक retval;

	urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!urb)
		वापस -ENOMEM;

	dr = kदो_स्मृति(माप(*dr) + size, GFP_ATOMIC);
	अगर (!dr) अणु
		usb_मुक्त_urb(urb);
		वापस -ENOMEM;
	पूर्ण

	buf = (u8 *)dr + माप(*dr);
	स_नकल(buf, req, size);

	dr->bRequest = cmd;
	dr->bRequestType = USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_INTERFACE;
	dr->wValue = 0;
	dr->wIndex = 0;
	dr->wLength = cpu_to_le16(size);

	usb_fill_control_urb(urb, udev, usb_sndctrlpipe(udev, 0),
			     (अचिन्हित अक्षर *)dr, buf, size,
			     ap_urb_complete, dr);
	retval = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (retval) अणु
		usb_मुक्त_urb(urb);
		kमुक्त(dr);
	पूर्ण
	वापस retval;
पूर्ण

अटल पूर्णांक output(काष्ठा gb_host_device *hd, व्योम *req, u16 size, u8 cmd,
		  bool async)
अणु
	काष्ठा es2_ap_dev *es2 = hd_to_es2(hd);

	अगर (async)
		वापस output_async(es2, req, size, cmd);

	वापस output_sync(es2, req, size, cmd);
पूर्ण

अटल पूर्णांक es2_cport_in_enable(काष्ठा es2_ap_dev *es2,
			       काष्ठा es2_cport_in *cport_in)
अणु
	काष्ठा urb *urb;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < NUM_CPORT_IN_URB; ++i) अणु
		urb = cport_in->urb[i];

		ret = usb_submit_urb(urb, GFP_KERNEL);
		अगर (ret) अणु
			dev_err(&es2->usb_dev->dev,
				"failed to submit in-urb: %d\n", ret);
			जाओ err_समाप्त_urbs;
		पूर्ण
	पूर्ण

	वापस 0;

err_समाप्त_urbs:
	क्रम (--i; i >= 0; --i) अणु
		urb = cport_in->urb[i];
		usb_समाप्त_urb(urb);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम es2_cport_in_disable(काष्ठा es2_ap_dev *es2,
				 काष्ठा es2_cport_in *cport_in)
अणु
	काष्ठा urb *urb;
	पूर्णांक i;

	क्रम (i = 0; i < NUM_CPORT_IN_URB; ++i) अणु
		urb = cport_in->urb[i];
		usb_समाप्त_urb(urb);
	पूर्ण
पूर्ण

अटल पूर्णांक es2_arpc_in_enable(काष्ठा es2_ap_dev *es2)
अणु
	काष्ठा urb *urb;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < NUM_ARPC_IN_URB; ++i) अणु
		urb = es2->arpc_urb[i];

		ret = usb_submit_urb(urb, GFP_KERNEL);
		अगर (ret) अणु
			dev_err(&es2->usb_dev->dev,
				"failed to submit arpc in-urb: %d\n", ret);
			जाओ err_समाप्त_urbs;
		पूर्ण
	पूर्ण

	वापस 0;

err_समाप्त_urbs:
	क्रम (--i; i >= 0; --i) अणु
		urb = es2->arpc_urb[i];
		usb_समाप्त_urb(urb);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम es2_arpc_in_disable(काष्ठा es2_ap_dev *es2)
अणु
	काष्ठा urb *urb;
	पूर्णांक i;

	क्रम (i = 0; i < NUM_ARPC_IN_URB; ++i) अणु
		urb = es2->arpc_urb[i];
		usb_समाप्त_urb(urb);
	पूर्ण
पूर्ण

अटल काष्ठा urb *next_मुक्त_urb(काष्ठा es2_ap_dev *es2, gfp_t gfp_mask)
अणु
	काष्ठा urb *urb = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&es2->cport_out_urb_lock, flags);

	/* Look in our pool of allocated urbs first, as that's the "fastest" */
	क्रम (i = 0; i < NUM_CPORT_OUT_URB; ++i) अणु
		अगर (!es2->cport_out_urb_busy[i] &&
		    !es2->cport_out_urb_cancelled[i]) अणु
			es2->cport_out_urb_busy[i] = true;
			urb = es2->cport_out_urb[i];
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&es2->cport_out_urb_lock, flags);
	अगर (urb)
		वापस urb;

	/*
	 * Crap, pool is empty, complain to the syslog and go allocate one
	 * dynamically as we have to succeed.
	 */
	dev_dbg(&es2->usb_dev->dev,
		"No free CPort OUT urbs, having to dynamically allocate one!\n");
	वापस usb_alloc_urb(0, gfp_mask);
पूर्ण

अटल व्योम मुक्त_urb(काष्ठा es2_ap_dev *es2, काष्ठा urb *urb)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	/*
	 * See अगर this was an urb in our pool, अगर so mark it "free", otherwise
	 * we need to मुक्त it ourselves.
	 */
	spin_lock_irqsave(&es2->cport_out_urb_lock, flags);
	क्रम (i = 0; i < NUM_CPORT_OUT_URB; ++i) अणु
		अगर (urb == es2->cport_out_urb[i]) अणु
			es2->cport_out_urb_busy[i] = false;
			urb = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&es2->cport_out_urb_lock, flags);

	/* If urb is not शून्य, then we need to मुक्त this urb */
	usb_मुक्त_urb(urb);
पूर्ण

/*
 * We (ab)use the operation-message header pad bytes to transfer the
 * cport id in order to minimise overhead.
 */
अटल व्योम
gb_message_cport_pack(काष्ठा gb_operation_msg_hdr *header, u16 cport_id)
अणु
	header->pad[0] = cport_id;
पूर्ण

/* Clear the pad bytes used क्रम the CPort id */
अटल व्योम gb_message_cport_clear(काष्ठा gb_operation_msg_hdr *header)
अणु
	header->pad[0] = 0;
पूर्ण

/* Extract the CPort id packed पूर्णांकo the header, and clear it */
अटल u16 gb_message_cport_unpack(काष्ठा gb_operation_msg_hdr *header)
अणु
	u16 cport_id = header->pad[0];

	gb_message_cport_clear(header);

	वापस cport_id;
पूर्ण

/*
 * Returns zero अगर the message was successfully queued, or a negative त्रुटि_सं
 * otherwise.
 */
अटल पूर्णांक message_send(काष्ठा gb_host_device *hd, u16 cport_id,
			काष्ठा gb_message *message, gfp_t gfp_mask)
अणु
	काष्ठा es2_ap_dev *es2 = hd_to_es2(hd);
	काष्ठा usb_device *udev = es2->usb_dev;
	माप_प्रकार buffer_size;
	पूर्णांक retval;
	काष्ठा urb *urb;
	अचिन्हित दीर्घ flags;

	/*
	 * The data actually transferred will include an indication
	 * of where the data should be sent.  Do one last check of
	 * the target CPort id beक्रमe filling it in.
	 */
	अगर (!cport_id_valid(hd, cport_id)) अणु
		dev_err(&udev->dev, "invalid cport %u\n", cport_id);
		वापस -EINVAL;
	पूर्ण

	/* Find a मुक्त urb */
	urb = next_मुक्त_urb(es2, gfp_mask);
	अगर (!urb)
		वापस -ENOMEM;

	spin_lock_irqsave(&es2->cport_out_urb_lock, flags);
	message->hcpriv = urb;
	spin_unlock_irqrestore(&es2->cport_out_urb_lock, flags);

	/* Pack the cport id पूर्णांकo the message header */
	gb_message_cport_pack(message->header, cport_id);

	buffer_size = माप(*message->header) + message->payload_size;

	usb_fill_bulk_urb(urb, udev,
			  usb_sndbulkpipe(udev,
					  es2->cport_out_endpoपूर्णांक),
			  message->buffer, buffer_size,
			  cport_out_callback, message);
	urb->transfer_flags |= URB_ZERO_PACKET;

	trace_gb_message_submit(message);

	retval = usb_submit_urb(urb, gfp_mask);
	अगर (retval) अणु
		dev_err(&udev->dev, "failed to submit out-urb: %d\n", retval);

		spin_lock_irqsave(&es2->cport_out_urb_lock, flags);
		message->hcpriv = शून्य;
		spin_unlock_irqrestore(&es2->cport_out_urb_lock, flags);

		मुक्त_urb(es2, urb);
		gb_message_cport_clear(message->header);

		वापस retval;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Can not be called in atomic context.
 */
अटल व्योम message_cancel(काष्ठा gb_message *message)
अणु
	काष्ठा gb_host_device *hd = message->operation->connection->hd;
	काष्ठा es2_ap_dev *es2 = hd_to_es2(hd);
	काष्ठा urb *urb;
	पूर्णांक i;

	might_sleep();

	spin_lock_irq(&es2->cport_out_urb_lock);
	urb = message->hcpriv;

	/* Prevent dynamically allocated urb from being deallocated. */
	usb_get_urb(urb);

	/* Prevent pre-allocated urb from being reused. */
	क्रम (i = 0; i < NUM_CPORT_OUT_URB; ++i) अणु
		अगर (urb == es2->cport_out_urb[i]) अणु
			es2->cport_out_urb_cancelled[i] = true;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irq(&es2->cport_out_urb_lock);

	usb_समाप्त_urb(urb);

	अगर (i < NUM_CPORT_OUT_URB) अणु
		spin_lock_irq(&es2->cport_out_urb_lock);
		es2->cport_out_urb_cancelled[i] = false;
		spin_unlock_irq(&es2->cport_out_urb_lock);
	पूर्ण

	usb_मुक्त_urb(urb);
पूर्ण

अटल पूर्णांक es2_cport_allocate(काष्ठा gb_host_device *hd, पूर्णांक cport_id,
			      अचिन्हित दीर्घ flags)
अणु
	काष्ठा es2_ap_dev *es2 = hd_to_es2(hd);
	काष्ठा ida *id_map = &hd->cport_id_map;
	पूर्णांक ida_start, ida_end;

	चयन (cport_id) अणु
	हाल ES2_CPORT_CDSI0:
	हाल ES2_CPORT_CDSI1:
		dev_err(&hd->dev, "cport %d not available\n", cport_id);
		वापस -EBUSY;
	पूर्ण

	अगर (flags & GB_CONNECTION_FLAG_OFFLOADED &&
	    flags & GB_CONNECTION_FLAG_CDSI1) अणु
		अगर (es2->cdsi1_in_use) अणु
			dev_err(&hd->dev, "CDSI1 already in use\n");
			वापस -EBUSY;
		पूर्ण

		es2->cdsi1_in_use = true;

		वापस ES2_CPORT_CDSI1;
	पूर्ण

	अगर (cport_id < 0) अणु
		ida_start = 0;
		ida_end = hd->num_cports;
	पूर्ण अन्यथा अगर (cport_id < hd->num_cports) अणु
		ida_start = cport_id;
		ida_end = cport_id + 1;
	पूर्ण अन्यथा अणु
		dev_err(&hd->dev, "cport %d not available\n", cport_id);
		वापस -EINVAL;
	पूर्ण

	वापस ida_simple_get(id_map, ida_start, ida_end, GFP_KERNEL);
पूर्ण

अटल व्योम es2_cport_release(काष्ठा gb_host_device *hd, u16 cport_id)
अणु
	काष्ठा es2_ap_dev *es2 = hd_to_es2(hd);

	चयन (cport_id) अणु
	हाल ES2_CPORT_CDSI1:
		es2->cdsi1_in_use = false;
		वापस;
	पूर्ण

	ida_simple_हटाओ(&hd->cport_id_map, cport_id);
पूर्ण

अटल पूर्णांक cport_enable(काष्ठा gb_host_device *hd, u16 cport_id,
			अचिन्हित दीर्घ flags)
अणु
	काष्ठा es2_ap_dev *es2 = hd_to_es2(hd);
	काष्ठा usb_device *udev = es2->usb_dev;
	काष्ठा gb_apb_request_cport_flags *req;
	u32 connection_flags;
	पूर्णांक ret;

	req = kzalloc(माप(*req), GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;

	connection_flags = 0;
	अगर (flags & GB_CONNECTION_FLAG_CONTROL)
		connection_flags |= GB_APB_CPORT_FLAG_CONTROL;
	अगर (flags & GB_CONNECTION_FLAG_HIGH_PRIO)
		connection_flags |= GB_APB_CPORT_FLAG_HIGH_PRIO;

	req->flags = cpu_to_le32(connection_flags);

	dev_dbg(&hd->dev, "%s - cport = %u, flags = %02x\n", __func__,
		cport_id, connection_flags);

	ret = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
			      GB_APB_REQUEST_CPORT_FLAGS,
			      USB_सूची_OUT | USB_TYPE_VENDOR |
			      USB_RECIP_INTERFACE, cport_id, 0,
			      req, माप(*req), ES2_USB_CTRL_TIMEOUT);
	अगर (ret < 0) अणु
		dev_err(&udev->dev, "failed to set cport flags for port %d\n",
			cport_id);
		जाओ out;
	पूर्ण

	ret = 0;
out:
	kमुक्त(req);

	वापस ret;
पूर्ण

अटल पूर्णांक es2_cport_connected(काष्ठा gb_host_device *hd, u16 cport_id)
अणु
	काष्ठा es2_ap_dev *es2 = hd_to_es2(hd);
	काष्ठा device *dev = &es2->usb_dev->dev;
	काष्ठा arpc_cport_connected_req req;
	पूर्णांक ret;

	req.cport_id = cpu_to_le16(cport_id);
	ret = arpc_sync(es2, ARPC_TYPE_CPORT_CONNECTED, &req, माप(req),
			शून्य, ES2_ARPC_CPORT_TIMEOUT);
	अगर (ret) अणु
		dev_err(dev, "failed to set connected state for cport %u: %d\n",
			cport_id, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक es2_cport_flush(काष्ठा gb_host_device *hd, u16 cport_id)
अणु
	काष्ठा es2_ap_dev *es2 = hd_to_es2(hd);
	काष्ठा device *dev = &es2->usb_dev->dev;
	काष्ठा arpc_cport_flush_req req;
	पूर्णांक ret;

	req.cport_id = cpu_to_le16(cport_id);
	ret = arpc_sync(es2, ARPC_TYPE_CPORT_FLUSH, &req, माप(req),
			शून्य, ES2_ARPC_CPORT_TIMEOUT);
	अगर (ret) अणु
		dev_err(dev, "failed to flush cport %u: %d\n", cport_id, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक es2_cport_shutकरोwn(काष्ठा gb_host_device *hd, u16 cport_id,
			      u8 phase, अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा es2_ap_dev *es2 = hd_to_es2(hd);
	काष्ठा device *dev = &es2->usb_dev->dev;
	काष्ठा arpc_cport_shutकरोwn_req req;
	पूर्णांक result;
	पूर्णांक ret;

	अगर (समयout > U16_MAX)
		वापस -EINVAL;

	req.cport_id = cpu_to_le16(cport_id);
	req.समयout = cpu_to_le16(समयout);
	req.phase = phase;
	ret = arpc_sync(es2, ARPC_TYPE_CPORT_SHUTDOWN, &req, माप(req),
			&result, ES2_ARPC_CPORT_TIMEOUT + समयout);
	अगर (ret) अणु
		dev_err(dev, "failed to send shutdown over cport %u: %d (%d)\n",
			cport_id, ret, result);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक es2_cport_quiesce(काष्ठा gb_host_device *hd, u16 cport_id,
			     माप_प्रकार peer_space, अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा es2_ap_dev *es2 = hd_to_es2(hd);
	काष्ठा device *dev = &es2->usb_dev->dev;
	काष्ठा arpc_cport_quiesce_req req;
	पूर्णांक result;
	पूर्णांक ret;

	अगर (peer_space > U16_MAX)
		वापस -EINVAL;

	अगर (समयout > U16_MAX)
		वापस -EINVAL;

	req.cport_id = cpu_to_le16(cport_id);
	req.peer_space = cpu_to_le16(peer_space);
	req.समयout = cpu_to_le16(समयout);
	ret = arpc_sync(es2, ARPC_TYPE_CPORT_QUIESCE, &req, माप(req),
			&result, ES2_ARPC_CPORT_TIMEOUT + समयout);
	अगर (ret) अणु
		dev_err(dev, "failed to quiesce cport %u: %d (%d)\n",
			cport_id, ret, result);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक es2_cport_clear(काष्ठा gb_host_device *hd, u16 cport_id)
अणु
	काष्ठा es2_ap_dev *es2 = hd_to_es2(hd);
	काष्ठा device *dev = &es2->usb_dev->dev;
	काष्ठा arpc_cport_clear_req req;
	पूर्णांक ret;

	req.cport_id = cpu_to_le16(cport_id);
	ret = arpc_sync(es2, ARPC_TYPE_CPORT_CLEAR, &req, माप(req),
			शून्य, ES2_ARPC_CPORT_TIMEOUT);
	अगर (ret) अणु
		dev_err(dev, "failed to clear cport %u: %d\n", cport_id, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक latency_tag_enable(काष्ठा gb_host_device *hd, u16 cport_id)
अणु
	पूर्णांक retval;
	काष्ठा es2_ap_dev *es2 = hd_to_es2(hd);
	काष्ठा usb_device *udev = es2->usb_dev;

	retval = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
				 GB_APB_REQUEST_LATENCY_TAG_EN,
				 USB_सूची_OUT | USB_TYPE_VENDOR |
				 USB_RECIP_INTERFACE, cport_id, 0, शून्य,
				 0, ES2_USB_CTRL_TIMEOUT);

	अगर (retval < 0)
		dev_err(&udev->dev, "Cannot enable latency tag for cport %d\n",
			cport_id);
	वापस retval;
पूर्ण

अटल पूर्णांक latency_tag_disable(काष्ठा gb_host_device *hd, u16 cport_id)
अणु
	पूर्णांक retval;
	काष्ठा es2_ap_dev *es2 = hd_to_es2(hd);
	काष्ठा usb_device *udev = es2->usb_dev;

	retval = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
				 GB_APB_REQUEST_LATENCY_TAG_DIS,
				 USB_सूची_OUT | USB_TYPE_VENDOR |
				 USB_RECIP_INTERFACE, cport_id, 0, शून्य,
				 0, ES2_USB_CTRL_TIMEOUT);

	अगर (retval < 0)
		dev_err(&udev->dev, "Cannot disable latency tag for cport %d\n",
			cport_id);
	वापस retval;
पूर्ण

अटल काष्ठा gb_hd_driver es2_driver = अणु
	.hd_priv_size			= माप(काष्ठा es2_ap_dev),
	.message_send			= message_send,
	.message_cancel			= message_cancel,
	.cport_allocate			= es2_cport_allocate,
	.cport_release			= es2_cport_release,
	.cport_enable			= cport_enable,
	.cport_connected		= es2_cport_connected,
	.cport_flush			= es2_cport_flush,
	.cport_shutकरोwn			= es2_cport_shutकरोwn,
	.cport_quiesce			= es2_cport_quiesce,
	.cport_clear			= es2_cport_clear,
	.latency_tag_enable		= latency_tag_enable,
	.latency_tag_disable		= latency_tag_disable,
	.output				= output,
पूर्ण;

/* Common function to report consistent warnings based on URB status */
अटल पूर्णांक check_urb_status(काष्ठा urb *urb)
अणु
	काष्ठा device *dev = &urb->dev->dev;
	पूर्णांक status = urb->status;

	चयन (status) अणु
	हाल 0:
		वापस 0;

	हाल -EOVERFLOW:
		dev_err(dev, "%s: overflow actual length is %d\n",
			__func__, urb->actual_length);
		fallthrough;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
	हाल -EILSEQ:
	हाल -EPROTO:
		/* device is gone, stop sending */
		वापस status;
	पूर्ण
	dev_err(dev, "%s: unknown status %d\n", __func__, status);

	वापस -EAGAIN;
पूर्ण

अटल व्योम es2_destroy(काष्ठा es2_ap_dev *es2)
अणु
	काष्ठा usb_device *udev;
	काष्ठा urb *urb;
	पूर्णांक i;

	debugfs_हटाओ(es2->apb_log_enable_dentry);
	usb_log_disable(es2);

	/* Tear करोwn everything! */
	क्रम (i = 0; i < NUM_CPORT_OUT_URB; ++i) अणु
		urb = es2->cport_out_urb[i];
		usb_समाप्त_urb(urb);
		usb_मुक्त_urb(urb);
		es2->cport_out_urb[i] = शून्य;
		es2->cport_out_urb_busy[i] = false;	/* just to be anal */
	पूर्ण

	क्रम (i = 0; i < NUM_ARPC_IN_URB; ++i) अणु
		usb_मुक्त_urb(es2->arpc_urb[i]);
		kमुक्त(es2->arpc_buffer[i]);
		es2->arpc_buffer[i] = शून्य;
	पूर्ण

	क्रम (i = 0; i < NUM_CPORT_IN_URB; ++i) अणु
		usb_मुक्त_urb(es2->cport_in.urb[i]);
		kमुक्त(es2->cport_in.buffer[i]);
		es2->cport_in.buffer[i] = शून्य;
	पूर्ण

	/* release reserved CDSI0 and CDSI1 cports */
	gb_hd_cport_release_reserved(es2->hd, ES2_CPORT_CDSI1);
	gb_hd_cport_release_reserved(es2->hd, ES2_CPORT_CDSI0);

	udev = es2->usb_dev;
	gb_hd_put(es2->hd);

	usb_put_dev(udev);
पूर्ण

अटल व्योम cport_in_callback(काष्ठा urb *urb)
अणु
	काष्ठा gb_host_device *hd = urb->context;
	काष्ठा device *dev = &urb->dev->dev;
	काष्ठा gb_operation_msg_hdr *header;
	पूर्णांक status = check_urb_status(urb);
	पूर्णांक retval;
	u16 cport_id;

	अगर (status) अणु
		अगर ((status == -EAGAIN) || (status == -EPROTO))
			जाओ निकास;

		/* The urb is being unlinked */
		अगर (status == -ENOENT || status == -ESHUTDOWN)
			वापस;

		dev_err(dev, "urb cport in error %d (dropped)\n", status);
		वापस;
	पूर्ण

	अगर (urb->actual_length < माप(*header)) अणु
		dev_err(dev, "short message received\n");
		जाओ निकास;
	पूर्ण

	/* Extract the CPort id, which is packed in the message header */
	header = urb->transfer_buffer;
	cport_id = gb_message_cport_unpack(header);

	अगर (cport_id_valid(hd, cport_id)) अणु
		greybus_data_rcvd(hd, cport_id, urb->transfer_buffer,
				  urb->actual_length);
	पूर्ण अन्यथा अणु
		dev_err(dev, "invalid cport id %u received\n", cport_id);
	पूर्ण
निकास:
	/* put our urb back in the request pool */
	retval = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (retval)
		dev_err(dev, "failed to resubmit in-urb: %d\n", retval);
पूर्ण

अटल व्योम cport_out_callback(काष्ठा urb *urb)
अणु
	काष्ठा gb_message *message = urb->context;
	काष्ठा gb_host_device *hd = message->operation->connection->hd;
	काष्ठा es2_ap_dev *es2 = hd_to_es2(hd);
	पूर्णांक status = check_urb_status(urb);
	अचिन्हित दीर्घ flags;

	gb_message_cport_clear(message->header);

	spin_lock_irqsave(&es2->cport_out_urb_lock, flags);
	message->hcpriv = शून्य;
	spin_unlock_irqrestore(&es2->cport_out_urb_lock, flags);

	/*
	 * Tell the submitter that the message send (attempt) is
	 * complete, and report the status.
	 */
	greybus_message_sent(hd, message, status);

	मुक्त_urb(es2, urb);
पूर्ण

अटल काष्ठा arpc *arpc_alloc(व्योम *payload, u16 size, u8 type)
अणु
	काष्ठा arpc *rpc;

	अगर (size + माप(*rpc->req) > ARPC_OUT_SIZE_MAX)
		वापस शून्य;

	rpc = kzalloc(माप(*rpc), GFP_KERNEL);
	अगर (!rpc)
		वापस शून्य;

	INIT_LIST_HEAD(&rpc->list);
	rpc->req = kzalloc(माप(*rpc->req) + size, GFP_KERNEL);
	अगर (!rpc->req)
		जाओ err_मुक्त_rpc;

	rpc->resp = kzalloc(माप(*rpc->resp), GFP_KERNEL);
	अगर (!rpc->resp)
		जाओ err_मुक्त_req;

	rpc->req->type = type;
	rpc->req->size = cpu_to_le16(माप(*rpc->req) + size);
	स_नकल(rpc->req->data, payload, size);

	init_completion(&rpc->response_received);

	वापस rpc;

err_मुक्त_req:
	kमुक्त(rpc->req);
err_मुक्त_rpc:
	kमुक्त(rpc);

	वापस शून्य;
पूर्ण

अटल व्योम arpc_मुक्त(काष्ठा arpc *rpc)
अणु
	kमुक्त(rpc->req);
	kमुक्त(rpc->resp);
	kमुक्त(rpc);
पूर्ण

अटल काष्ठा arpc *arpc_find(काष्ठा es2_ap_dev *es2, __le16 id)
अणु
	काष्ठा arpc *rpc;

	list_क्रम_each_entry(rpc, &es2->arpcs, list) अणु
		अगर (rpc->req->id == id)
			वापस rpc;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम arpc_add(काष्ठा es2_ap_dev *es2, काष्ठा arpc *rpc)
अणु
	rpc->active = true;
	rpc->req->id = cpu_to_le16(es2->arpc_id_cycle++);
	list_add_tail(&rpc->list, &es2->arpcs);
पूर्ण

अटल व्योम arpc_del(काष्ठा es2_ap_dev *es2, काष्ठा arpc *rpc)
अणु
	अगर (rpc->active) अणु
		rpc->active = false;
		list_del(&rpc->list);
	पूर्ण
पूर्ण

अटल पूर्णांक arpc_send(काष्ठा es2_ap_dev *es2, काष्ठा arpc *rpc, पूर्णांक समयout)
अणु
	काष्ठा usb_device *udev = es2->usb_dev;
	पूर्णांक retval;

	retval = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
				 GB_APB_REQUEST_ARPC_RUN,
				 USB_सूची_OUT | USB_TYPE_VENDOR |
				 USB_RECIP_INTERFACE,
				 0, 0,
				 rpc->req, le16_to_cpu(rpc->req->size),
				 ES2_USB_CTRL_TIMEOUT);
	अगर (retval < 0) अणु
		dev_err(&udev->dev,
			"failed to send ARPC request %d: %d\n",
			rpc->req->type, retval);
		वापस retval;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक arpc_sync(काष्ठा es2_ap_dev *es2, u8 type, व्योम *payload,
		     माप_प्रकार size, पूर्णांक *result, अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा arpc *rpc;
	अचिन्हित दीर्घ flags;
	पूर्णांक retval;

	अगर (result)
		*result = 0;

	rpc = arpc_alloc(payload, size, type);
	अगर (!rpc)
		वापस -ENOMEM;

	spin_lock_irqsave(&es2->arpc_lock, flags);
	arpc_add(es2, rpc);
	spin_unlock_irqrestore(&es2->arpc_lock, flags);

	retval = arpc_send(es2, rpc, समयout);
	अगर (retval)
		जाओ out_arpc_del;

	retval = रुको_क्रम_completion_पूर्णांकerruptible_समयout(
						&rpc->response_received,
						msecs_to_jअगरfies(समयout));
	अगर (retval <= 0) अणु
		अगर (!retval)
			retval = -ETIMEDOUT;
		जाओ out_arpc_del;
	पूर्ण

	अगर (rpc->resp->result) अणु
		retval = -EREMOTEIO;
		अगर (result)
			*result = rpc->resp->result;
	पूर्ण अन्यथा अणु
		retval = 0;
	पूर्ण

out_arpc_del:
	spin_lock_irqsave(&es2->arpc_lock, flags);
	arpc_del(es2, rpc);
	spin_unlock_irqrestore(&es2->arpc_lock, flags);
	arpc_मुक्त(rpc);

	अगर (retval < 0 && retval != -EREMOTEIO) अणु
		dev_err(&es2->usb_dev->dev,
			"failed to execute ARPC: %d\n", retval);
	पूर्ण

	वापस retval;
पूर्ण

अटल व्योम arpc_in_callback(काष्ठा urb *urb)
अणु
	काष्ठा es2_ap_dev *es2 = urb->context;
	काष्ठा device *dev = &urb->dev->dev;
	पूर्णांक status = check_urb_status(urb);
	काष्ठा arpc *rpc;
	काष्ठा arpc_response_message *resp;
	अचिन्हित दीर्घ flags;
	पूर्णांक retval;

	अगर (status) अणु
		अगर ((status == -EAGAIN) || (status == -EPROTO))
			जाओ निकास;

		/* The urb is being unlinked */
		अगर (status == -ENOENT || status == -ESHUTDOWN)
			वापस;

		dev_err(dev, "arpc in-urb error %d (dropped)\n", status);
		वापस;
	पूर्ण

	अगर (urb->actual_length < माप(*resp)) अणु
		dev_err(dev, "short aprc response received\n");
		जाओ निकास;
	पूर्ण

	resp = urb->transfer_buffer;
	spin_lock_irqsave(&es2->arpc_lock, flags);
	rpc = arpc_find(es2, resp->id);
	अगर (!rpc) अणु
		dev_err(dev, "invalid arpc response id received: %u\n",
			le16_to_cpu(resp->id));
		spin_unlock_irqrestore(&es2->arpc_lock, flags);
		जाओ निकास;
	पूर्ण

	arpc_del(es2, rpc);
	स_नकल(rpc->resp, resp, माप(*resp));
	complete(&rpc->response_received);
	spin_unlock_irqrestore(&es2->arpc_lock, flags);

निकास:
	/* put our urb back in the request pool */
	retval = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (retval)
		dev_err(dev, "failed to resubmit arpc in-urb: %d\n", retval);
पूर्ण

#घोषणा APB1_LOG_MSG_SIZE	64
अटल व्योम apb_log_get(काष्ठा es2_ap_dev *es2, अक्षर *buf)
अणु
	पूर्णांक retval;

	करो अणु
		retval = usb_control_msg(es2->usb_dev,
					 usb_rcvctrlpipe(es2->usb_dev, 0),
					 GB_APB_REQUEST_LOG,
					 USB_सूची_IN | USB_TYPE_VENDOR |
					 USB_RECIP_INTERFACE,
					 0x00, 0x00,
					 buf,
					 APB1_LOG_MSG_SIZE,
					 ES2_USB_CTRL_TIMEOUT);
		अगर (retval > 0)
			kfअगरo_in(&es2->apb_log_fअगरo, buf, retval);
	पूर्ण जबतक (retval > 0);
पूर्ण

अटल पूर्णांक apb_log_poll(व्योम *data)
अणु
	काष्ठा es2_ap_dev *es2 = data;
	अक्षर *buf;

	buf = kदो_स्मृति(APB1_LOG_MSG_SIZE, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	जबतक (!kthपढ़ो_should_stop()) अणु
		msleep(1000);
		apb_log_get(es2, buf);
	पूर्ण

	kमुक्त(buf);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार apb_log_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
			    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा es2_ap_dev *es2 = file_inode(f)->i_निजी;
	sमाप_प्रकार ret;
	माप_प्रकार copied;
	अक्षर *पंचांगp_buf;

	अगर (count > APB1_LOG_SIZE)
		count = APB1_LOG_SIZE;

	पंचांगp_buf = kदो_स्मृति(count, GFP_KERNEL);
	अगर (!पंचांगp_buf)
		वापस -ENOMEM;

	copied = kfअगरo_out(&es2->apb_log_fअगरo, पंचांगp_buf, count);
	ret = simple_पढ़ो_from_buffer(buf, count, ppos, पंचांगp_buf, copied);

	kमुक्त(पंचांगp_buf);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations apb_log_fops = अणु
	.पढ़ो	= apb_log_पढ़ो,
पूर्ण;

अटल व्योम usb_log_enable(काष्ठा es2_ap_dev *es2)
अणु
	अगर (!IS_ERR_OR_शून्य(es2->apb_log_task))
		वापस;

	/* get log from APB1 */
	es2->apb_log_task = kthपढ़ो_run(apb_log_poll, es2, "apb_log");
	अगर (IS_ERR(es2->apb_log_task))
		वापस;
	/* XXX We will need to नाम this per APB */
	es2->apb_log_dentry = debugfs_create_file("apb_log", 0444,
						  gb_debugfs_get(), es2,
						  &apb_log_fops);
पूर्ण

अटल व्योम usb_log_disable(काष्ठा es2_ap_dev *es2)
अणु
	अगर (IS_ERR_OR_शून्य(es2->apb_log_task))
		वापस;

	debugfs_हटाओ(es2->apb_log_dentry);
	es2->apb_log_dentry = शून्य;

	kthपढ़ो_stop(es2->apb_log_task);
	es2->apb_log_task = शून्य;
पूर्ण

अटल sमाप_प्रकार apb_log_enable_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा es2_ap_dev *es2 = file_inode(f)->i_निजी;
	पूर्णांक enable = !IS_ERR_OR_शून्य(es2->apb_log_task);
	अक्षर पंचांगp_buf[3];

	प्र_लिखो(पंचांगp_buf, "%d\n", enable);
	वापस simple_पढ़ो_from_buffer(buf, count, ppos, पंचांगp_buf, 2);
पूर्ण

अटल sमाप_प्रकार apb_log_enable_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *buf,
				    माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक enable;
	sमाप_प्रकार retval;
	काष्ठा es2_ap_dev *es2 = file_inode(f)->i_निजी;

	retval = kstrtoपूर्णांक_from_user(buf, count, 10, &enable);
	अगर (retval)
		वापस retval;

	अगर (enable)
		usb_log_enable(es2);
	अन्यथा
		usb_log_disable(es2);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations apb_log_enable_fops = अणु
	.पढ़ो	= apb_log_enable_पढ़ो,
	.ग_लिखो	= apb_log_enable_ग_लिखो,
पूर्ण;

अटल पूर्णांक apb_get_cport_count(काष्ठा usb_device *udev)
अणु
	पूर्णांक retval;
	__le16 *cport_count;

	cport_count = kzalloc(माप(*cport_count), GFP_KERNEL);
	अगर (!cport_count)
		वापस -ENOMEM;

	retval = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
				 GB_APB_REQUEST_CPORT_COUNT,
				 USB_सूची_IN | USB_TYPE_VENDOR |
				 USB_RECIP_INTERFACE, 0, 0, cport_count,
				 माप(*cport_count), ES2_USB_CTRL_TIMEOUT);
	अगर (retval != माप(*cport_count)) अणु
		dev_err(&udev->dev, "Cannot retrieve CPort count: %d\n",
			retval);

		अगर (retval >= 0)
			retval = -EIO;

		जाओ out;
	पूर्ण

	retval = le16_to_cpu(*cport_count);

	/* We need to fit a CPort ID in one byte of a message header */
	अगर (retval > U8_MAX) अणु
		retval = U8_MAX;
		dev_warn(&udev->dev, "Limiting number of CPorts to U8_MAX\n");
	पूर्ण

out:
	kमुक्त(cport_count);
	वापस retval;
पूर्ण

/*
 * The ES2 USB Bridge device has 15 endpoपूर्णांकs
 * 1 Control - usual USB stuff + AP -> APBridgeA messages
 * 7 Bulk IN - CPort data in
 * 7 Bulk OUT - CPort data out
 */
अटल पूर्णांक ap_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
		    स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा es2_ap_dev *es2;
	काष्ठा gb_host_device *hd;
	काष्ठा usb_device *udev;
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	__u8 ep_addr;
	पूर्णांक retval;
	पूर्णांक i;
	पूर्णांक num_cports;
	bool bulk_out_found = false;
	bool bulk_in_found = false;
	bool arpc_in_found = false;

	udev = usb_get_dev(पूर्णांकerface_to_usbdev(पूर्णांकerface));

	num_cports = apb_get_cport_count(udev);
	अगर (num_cports < 0) अणु
		usb_put_dev(udev);
		dev_err(&udev->dev, "Cannot retrieve CPort count: %d\n",
			num_cports);
		वापस num_cports;
	पूर्ण

	hd = gb_hd_create(&es2_driver, &udev->dev, ES2_GBUF_MSG_SIZE_MAX,
			  num_cports);
	अगर (IS_ERR(hd)) अणु
		usb_put_dev(udev);
		वापस PTR_ERR(hd);
	पूर्ण

	es2 = hd_to_es2(hd);
	es2->hd = hd;
	es2->usb_पूर्णांकf = पूर्णांकerface;
	es2->usb_dev = udev;
	spin_lock_init(&es2->cport_out_urb_lock);
	INIT_KFIFO(es2->apb_log_fअगरo);
	usb_set_पूर्णांकfdata(पूर्णांकerface, es2);

	/*
	 * Reserve the CDSI0 and CDSI1 CPorts so they won't be allocated
	 * dynamically.
	 */
	retval = gb_hd_cport_reserve(hd, ES2_CPORT_CDSI0);
	अगर (retval)
		जाओ error;
	retval = gb_hd_cport_reserve(hd, ES2_CPORT_CDSI1);
	अगर (retval)
		जाओ error;

	/* find all bulk endpoपूर्णांकs */
	अगरace_desc = पूर्णांकerface->cur_altsetting;
	क्रम (i = 0; i < अगरace_desc->desc.bNumEndpoपूर्णांकs; ++i) अणु
		endpoपूर्णांक = &अगरace_desc->endpoपूर्णांक[i].desc;
		ep_addr = endpoपूर्णांक->bEndpoपूर्णांकAddress;

		अगर (usb_endpoपूर्णांक_is_bulk_in(endpoपूर्णांक)) अणु
			अगर (!bulk_in_found) अणु
				es2->cport_in.endpoपूर्णांक = ep_addr;
				bulk_in_found = true;
			पूर्ण अन्यथा अगर (!arpc_in_found) अणु
				es2->arpc_endpoपूर्णांक_in = ep_addr;
				arpc_in_found = true;
			पूर्ण अन्यथा अणु
				dev_warn(&udev->dev,
					 "Unused bulk IN endpoint found: 0x%02x\n",
					 ep_addr);
			पूर्ण
			जारी;
		पूर्ण
		अगर (usb_endpoपूर्णांक_is_bulk_out(endpoपूर्णांक)) अणु
			अगर (!bulk_out_found) अणु
				es2->cport_out_endpoपूर्णांक = ep_addr;
				bulk_out_found = true;
			पूर्ण अन्यथा अणु
				dev_warn(&udev->dev,
					 "Unused bulk OUT endpoint found: 0x%02x\n",
					 ep_addr);
			पूर्ण
			जारी;
		पूर्ण
		dev_warn(&udev->dev,
			 "Unknown endpoint type found, address 0x%02x\n",
			 ep_addr);
	पूर्ण
	अगर (!bulk_in_found || !arpc_in_found || !bulk_out_found) अणु
		dev_err(&udev->dev, "Not enough endpoints found in device, aborting!\n");
		retval = -ENODEV;
		जाओ error;
	पूर्ण

	/* Allocate buffers क्रम our cport in messages */
	क्रम (i = 0; i < NUM_CPORT_IN_URB; ++i) अणु
		काष्ठा urb *urb;
		u8 *buffer;

		urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!urb) अणु
			retval = -ENOMEM;
			जाओ error;
		पूर्ण
		es2->cport_in.urb[i] = urb;

		buffer = kदो_स्मृति(ES2_GBUF_MSG_SIZE_MAX, GFP_KERNEL);
		अगर (!buffer) अणु
			retval = -ENOMEM;
			जाओ error;
		पूर्ण

		usb_fill_bulk_urb(urb, udev,
				  usb_rcvbulkpipe(udev, es2->cport_in.endpoपूर्णांक),
				  buffer, ES2_GBUF_MSG_SIZE_MAX,
				  cport_in_callback, hd);

		es2->cport_in.buffer[i] = buffer;
	पूर्ण

	/* Allocate buffers क्रम ARPC in messages */
	क्रम (i = 0; i < NUM_ARPC_IN_URB; ++i) अणु
		काष्ठा urb *urb;
		u8 *buffer;

		urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!urb) अणु
			retval = -ENOMEM;
			जाओ error;
		पूर्ण
		es2->arpc_urb[i] = urb;

		buffer = kदो_स्मृति(ARPC_IN_SIZE_MAX, GFP_KERNEL);
		अगर (!buffer) अणु
			retval = -ENOMEM;
			जाओ error;
		पूर्ण

		usb_fill_bulk_urb(urb, udev,
				  usb_rcvbulkpipe(udev,
						  es2->arpc_endpoपूर्णांक_in),
				  buffer, ARPC_IN_SIZE_MAX,
				  arpc_in_callback, es2);

		es2->arpc_buffer[i] = buffer;
	पूर्ण

	/* Allocate urbs क्रम our CPort OUT messages */
	क्रम (i = 0; i < NUM_CPORT_OUT_URB; ++i) अणु
		काष्ठा urb *urb;

		urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!urb) अणु
			retval = -ENOMEM;
			जाओ error;
		पूर्ण

		es2->cport_out_urb[i] = urb;
		es2->cport_out_urb_busy[i] = false;	/* just to be anal */
	पूर्ण

	/* XXX We will need to नाम this per APB */
	es2->apb_log_enable_dentry = debugfs_create_file("apb_log_enable",
							 0644,
							 gb_debugfs_get(), es2,
							 &apb_log_enable_fops);

	INIT_LIST_HEAD(&es2->arpcs);
	spin_lock_init(&es2->arpc_lock);

	retval = es2_arpc_in_enable(es2);
	अगर (retval)
		जाओ error;

	retval = gb_hd_add(hd);
	अगर (retval)
		जाओ err_disable_arpc_in;

	retval = es2_cport_in_enable(es2, &es2->cport_in);
	अगर (retval)
		जाओ err_hd_del;

	वापस 0;

err_hd_del:
	gb_hd_del(hd);
err_disable_arpc_in:
	es2_arpc_in_disable(es2);
error:
	es2_destroy(es2);

	वापस retval;
पूर्ण

अटल व्योम ap_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा es2_ap_dev *es2 = usb_get_पूर्णांकfdata(पूर्णांकerface);

	gb_hd_del(es2->hd);

	es2_cport_in_disable(es2, &es2->cport_in);
	es2_arpc_in_disable(es2);

	es2_destroy(es2);
पूर्ण

अटल काष्ठा usb_driver es2_ap_driver = अणु
	.name =		"es2_ap_driver",
	.probe =	ap_probe,
	.disconnect =	ap_disconnect,
	.id_table =	id_table,
	.soft_unbind =	1,
पूर्ण;

module_usb_driver(es2_ap_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Greg Kroah-Hartman <gregkh@linuxfoundation.org>");
