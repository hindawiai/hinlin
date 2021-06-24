<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Line 6 Linux USB driver
 *
 * Copyright (C) 2004-2010 Markus Grabner (grabner@icg.tugraz.at)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>

#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/hwdep.h>

#समावेश "capture.h"
#समावेश "driver.h"
#समावेश "midi.h"
#समावेश "playback.h"

#घोषणा DRIVER_AUTHOR  "Markus Grabner <grabner@icg.tugraz.at>"
#घोषणा DRIVER_DESC    "Line 6 USB Driver"

/*
	This is Line 6's MIDI manufacturer ID.
*/
स्थिर अचिन्हित अक्षर line6_midi_id[3] = अणु
	0x00, 0x01, 0x0c
पूर्ण;
EXPORT_SYMBOL_GPL(line6_midi_id);

/*
	Code to request version of POD, Variax पूर्णांकerface
	(and maybe other devices).
*/
अटल स्थिर अक्षर line6_request_version[] = अणु
	0xf0, 0x7e, 0x7f, 0x06, 0x01, 0xf7
पूर्ण;

/*
	 Class क्रम asynchronous messages.
*/
काष्ठा message अणु
	काष्ठा usb_line6 *line6;
	स्थिर अक्षर *buffer;
	पूर्णांक size;
	पूर्णांक करोne;
पूर्ण;

/*
	Forward declarations.
*/
अटल व्योम line6_data_received(काष्ठा urb *urb);
अटल पूर्णांक line6_send_raw_message_async_part(काष्ठा message *msg,
					     काष्ठा urb *urb);

/*
	Start to listen on endpoपूर्णांक.
*/
अटल पूर्णांक line6_start_listen(काष्ठा usb_line6 *line6)
अणु
	पूर्णांक err;

	अगर (line6->properties->capabilities & LINE6_CAP_CONTROL_MIDI) अणु
		usb_fill_पूर्णांक_urb(line6->urb_listen, line6->usbdev,
			usb_rcvपूर्णांकpipe(line6->usbdev, line6->properties->ep_ctrl_r),
			line6->buffer_listen, LINE6_बफ_मानE_LISTEN,
			line6_data_received, line6, line6->पूर्णांकerval);
	पूर्ण अन्यथा अणु
		usb_fill_bulk_urb(line6->urb_listen, line6->usbdev,
			usb_rcvbulkpipe(line6->usbdev, line6->properties->ep_ctrl_r),
			line6->buffer_listen, LINE6_बफ_मानE_LISTEN,
			line6_data_received, line6);
	पूर्ण

	/* sanity checks of EP beक्रमe actually submitting */
	अगर (usb_urb_ep_type_check(line6->urb_listen)) अणु
		dev_err(line6->अगरcdev, "invalid control EP\n");
		वापस -EINVAL;
	पूर्ण

	line6->urb_listen->actual_length = 0;
	err = usb_submit_urb(line6->urb_listen, GFP_ATOMIC);
	वापस err;
पूर्ण

/*
	Stop listening on endpoपूर्णांक.
*/
अटल व्योम line6_stop_listen(काष्ठा usb_line6 *line6)
अणु
	usb_समाप्त_urb(line6->urb_listen);
पूर्ण

/*
	Send raw message in pieces of wMaxPacketSize bytes.
*/
पूर्णांक line6_send_raw_message(काष्ठा usb_line6 *line6, स्थिर अक्षर *buffer,
				  पूर्णांक size)
अणु
	पूर्णांक i, करोne = 0;
	स्थिर काष्ठा line6_properties *properties = line6->properties;

	क्रम (i = 0; i < size; i += line6->max_packet_size) अणु
		पूर्णांक partial;
		स्थिर अक्षर *frag_buf = buffer + i;
		पूर्णांक frag_size = min(line6->max_packet_size, size - i);
		पूर्णांक retval;

		अगर (properties->capabilities & LINE6_CAP_CONTROL_MIDI) अणु
			retval = usb_पूर्णांकerrupt_msg(line6->usbdev,
						usb_sndपूर्णांकpipe(line6->usbdev, properties->ep_ctrl_w),
						(अक्षर *)frag_buf, frag_size,
						&partial, LINE6_TIMEOUT * HZ);
		पूर्ण अन्यथा अणु
			retval = usb_bulk_msg(line6->usbdev,
						usb_sndbulkpipe(line6->usbdev, properties->ep_ctrl_w),
						(अक्षर *)frag_buf, frag_size,
						&partial, LINE6_TIMEOUT * HZ);
		पूर्ण

		अगर (retval) अणु
			dev_err(line6->अगरcdev,
				"usb_bulk_msg failed (%d)\n", retval);
			अवरोध;
		पूर्ण

		करोne += frag_size;
	पूर्ण

	वापस करोne;
पूर्ण
EXPORT_SYMBOL_GPL(line6_send_raw_message);

/*
	Notअगरication of completion of asynchronous request transmission.
*/
अटल व्योम line6_async_request_sent(काष्ठा urb *urb)
अणु
	काष्ठा message *msg = (काष्ठा message *)urb->context;

	अगर (msg->करोne >= msg->size) अणु
		usb_मुक्त_urb(urb);
		kमुक्त(msg);
	पूर्ण अन्यथा
		line6_send_raw_message_async_part(msg, urb);
पूर्ण

/*
	Asynchronously send part of a raw message.
*/
अटल पूर्णांक line6_send_raw_message_async_part(काष्ठा message *msg,
					     काष्ठा urb *urb)
अणु
	पूर्णांक retval;
	काष्ठा usb_line6 *line6 = msg->line6;
	पूर्णांक करोne = msg->करोne;
	पूर्णांक bytes = min(msg->size - करोne, line6->max_packet_size);

	अगर (line6->properties->capabilities & LINE6_CAP_CONTROL_MIDI) अणु
		usb_fill_पूर्णांक_urb(urb, line6->usbdev,
			usb_sndपूर्णांकpipe(line6->usbdev, line6->properties->ep_ctrl_w),
			(अक्षर *)msg->buffer + करोne, bytes,
			line6_async_request_sent, msg, line6->पूर्णांकerval);
	पूर्ण अन्यथा अणु
		usb_fill_bulk_urb(urb, line6->usbdev,
			usb_sndbulkpipe(line6->usbdev, line6->properties->ep_ctrl_w),
			(अक्षर *)msg->buffer + करोne, bytes,
			line6_async_request_sent, msg);
	पूर्ण

	msg->करोne += bytes;

	/* sanity checks of EP beक्रमe actually submitting */
	retval = usb_urb_ep_type_check(urb);
	अगर (retval < 0)
		जाओ error;

	retval = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (retval < 0)
		जाओ error;

	वापस 0;

 error:
	dev_err(line6->अगरcdev, "%s: usb_submit_urb failed (%d)\n",
		__func__, retval);
	usb_मुक्त_urb(urb);
	kमुक्त(msg);
	वापस retval;
पूर्ण

/*
	Asynchronously send raw message.
*/
पूर्णांक line6_send_raw_message_async(काष्ठा usb_line6 *line6, स्थिर अक्षर *buffer,
				 पूर्णांक size)
अणु
	काष्ठा message *msg;
	काष्ठा urb *urb;

	/* create message: */
	msg = kदो_स्मृति(माप(काष्ठा message), GFP_ATOMIC);
	अगर (msg == शून्य)
		वापस -ENOMEM;

	/* create URB: */
	urb = usb_alloc_urb(0, GFP_ATOMIC);

	अगर (urb == शून्य) अणु
		kमुक्त(msg);
		वापस -ENOMEM;
	पूर्ण

	/* set message data: */
	msg->line6 = line6;
	msg->buffer = buffer;
	msg->size = size;
	msg->करोne = 0;

	/* start sending: */
	वापस line6_send_raw_message_async_part(msg, urb);
पूर्ण
EXPORT_SYMBOL_GPL(line6_send_raw_message_async);

/*
	Send asynchronous device version request.
*/
पूर्णांक line6_version_request_async(काष्ठा usb_line6 *line6)
अणु
	अक्षर *buffer;
	पूर्णांक retval;

	buffer = kmemdup(line6_request_version,
			माप(line6_request_version), GFP_ATOMIC);
	अगर (buffer == शून्य)
		वापस -ENOMEM;

	retval = line6_send_raw_message_async(line6, buffer,
					      माप(line6_request_version));
	kमुक्त(buffer);
	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(line6_version_request_async);

/*
	Send sysex message in pieces of wMaxPacketSize bytes.
*/
पूर्णांक line6_send_sysex_message(काष्ठा usb_line6 *line6, स्थिर अक्षर *buffer,
			     पूर्णांक size)
अणु
	वापस line6_send_raw_message(line6, buffer,
				      size + SYSEX_EXTRA_SIZE) -
	    SYSEX_EXTRA_SIZE;
पूर्ण
EXPORT_SYMBOL_GPL(line6_send_sysex_message);

/*
	Allocate buffer क्रम sysex message and prepare header.
	@param code sysex message code
	@param size number of bytes between code and sysex end
*/
अक्षर *line6_alloc_sysex_buffer(काष्ठा usb_line6 *line6, पूर्णांक code1, पूर्णांक code2,
			       पूर्णांक size)
अणु
	अक्षर *buffer = kदो_स्मृति(size + SYSEX_EXTRA_SIZE, GFP_ATOMIC);

	अगर (!buffer)
		वापस शून्य;

	buffer[0] = LINE6_SYSEX_BEGIN;
	स_नकल(buffer + 1, line6_midi_id, माप(line6_midi_id));
	buffer[माप(line6_midi_id) + 1] = code1;
	buffer[माप(line6_midi_id) + 2] = code2;
	buffer[माप(line6_midi_id) + 3 + size] = LINE6_SYSEX_END;
	वापस buffer;
पूर्ण
EXPORT_SYMBOL_GPL(line6_alloc_sysex_buffer);

/*
	Notअगरication of data received from the Line 6 device.
*/
अटल व्योम line6_data_received(काष्ठा urb *urb)
अणु
	काष्ठा usb_line6 *line6 = (काष्ठा usb_line6 *)urb->context;
	काष्ठा midi_buffer *mb = &line6->line6midi->midibuf_in;
	पूर्णांक करोne;

	अगर (urb->status == -ESHUTDOWN)
		वापस;

	अगर (line6->properties->capabilities & LINE6_CAP_CONTROL_MIDI) अणु
		करोne =
			line6_midibuf_ग_लिखो(mb, urb->transfer_buffer, urb->actual_length);

		अगर (करोne < urb->actual_length) अणु
			line6_midibuf_ignore(mb, करोne);
			dev_dbg(line6->अगरcdev, "%d %d buffer overflow - message skipped\n",
				करोne, urb->actual_length);
		पूर्ण

		क्रम (;;) अणु
			करोne =
				line6_midibuf_पढ़ो(mb, line6->buffer_message,
						LINE6_MIDI_MESSAGE_MAXLEN);

			अगर (करोne <= 0)
				अवरोध;

			line6->message_length = करोne;
			line6_midi_receive(line6, line6->buffer_message, करोne);

			अगर (line6->process_message)
				line6->process_message(line6);
		पूर्ण
	पूर्ण अन्यथा अणु
		line6->buffer_message = urb->transfer_buffer;
		line6->message_length = urb->actual_length;
		अगर (line6->process_message)
			line6->process_message(line6);
		line6->buffer_message = शून्य;
	पूर्ण

	line6_start_listen(line6);
पूर्ण

#घोषणा LINE6_READ_WRITE_STATUS_DELAY 2  /* milliseconds */
#घोषणा LINE6_READ_WRITE_MAX_RETRIES 50

/*
	Read data from device.
*/
पूर्णांक line6_पढ़ो_data(काष्ठा usb_line6 *line6, अचिन्हित address, व्योम *data,
		    अचिन्हित datalen)
अणु
	काष्ठा usb_device *usbdev = line6->usbdev;
	पूर्णांक ret;
	u8 len;
	अचिन्हित count;

	अगर (address > 0xffff || datalen > 0xff)
		वापस -EINVAL;

	/* query the serial number: */
	ret = usb_control_msg_send(usbdev, 0, 0x67,
				   USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_OUT,
				   (datalen << 8) | 0x21, address, शून्य, 0,
				   LINE6_TIMEOUT * HZ, GFP_KERNEL);
	अगर (ret) अणु
		dev_err(line6->अगरcdev, "read request failed (error %d)\n", ret);
		जाओ निकास;
	पूर्ण

	/* Wait क्रम data length. We'll get 0xff until length arrives. */
	क्रम (count = 0; count < LINE6_READ_WRITE_MAX_RETRIES; count++) अणु
		mdelay(LINE6_READ_WRITE_STATUS_DELAY);

		ret = usb_control_msg_recv(usbdev, 0, 0x67,
					   USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_IN,
					   0x0012, 0x0000, &len, 1,
					   LINE6_TIMEOUT * HZ, GFP_KERNEL);
		अगर (ret) अणु
			dev_err(line6->अगरcdev,
				"receive length failed (error %d)\n", ret);
			जाओ निकास;
		पूर्ण

		अगर (len != 0xff)
			अवरोध;
	पूर्ण

	ret = -EIO;
	अगर (len == 0xff) अणु
		dev_err(line6->अगरcdev, "read failed after %d retries\n",
			count);
		जाओ निकास;
	पूर्ण अन्यथा अगर (len != datalen) अणु
		/* should be equal or something went wrong */
		dev_err(line6->अगरcdev,
			"length mismatch (expected %d, got %d)\n",
			(पूर्णांक)datalen, len);
		जाओ निकास;
	पूर्ण

	/* receive the result: */
	ret = usb_control_msg_recv(usbdev, 0, 0x67,
				   USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_IN,
				   0x0013, 0x0000, data, datalen, LINE6_TIMEOUT * HZ,
				   GFP_KERNEL);
	अगर (ret)
		dev_err(line6->अगरcdev, "read failed (error %d)\n", ret);

निकास:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(line6_पढ़ो_data);

/*
	Write data to device.
*/
पूर्णांक line6_ग_लिखो_data(काष्ठा usb_line6 *line6, अचिन्हित address, व्योम *data,
		     अचिन्हित datalen)
अणु
	काष्ठा usb_device *usbdev = line6->usbdev;
	पूर्णांक ret;
	अचिन्हित अक्षर *status;
	पूर्णांक count;

	अगर (address > 0xffff || datalen > 0xffff)
		वापस -EINVAL;

	status = kदो_स्मृति(1, GFP_KERNEL);
	अगर (!status)
		वापस -ENOMEM;

	ret = usb_control_msg_send(usbdev, 0, 0x67,
				   USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_OUT,
				   0x0022, address, data, datalen, LINE6_TIMEOUT * HZ,
				   GFP_KERNEL);
	अगर (ret) अणु
		dev_err(line6->अगरcdev,
			"write request failed (error %d)\n", ret);
		जाओ निकास;
	पूर्ण

	क्रम (count = 0; count < LINE6_READ_WRITE_MAX_RETRIES; count++) अणु
		mdelay(LINE6_READ_WRITE_STATUS_DELAY);

		ret = usb_control_msg_recv(usbdev, 0, 0x67,
					   USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_IN,
					   0x0012, 0x0000, status, 1, LINE6_TIMEOUT * HZ,
					   GFP_KERNEL);
		अगर (ret) अणु
			dev_err(line6->अगरcdev,
				"receiving status failed (error %d)\n", ret);
			जाओ निकास;
		पूर्ण

		अगर (*status != 0xff)
			अवरोध;
	पूर्ण

	अगर (*status == 0xff) अणु
		dev_err(line6->अगरcdev, "write failed after %d retries\n",
			count);
		ret = -EIO;
	पूर्ण अन्यथा अगर (*status != 0) अणु
		dev_err(line6->अगरcdev, "write failed (error %d)\n", ret);
		ret = -EIO;
	पूर्ण
निकास:
	kमुक्त(status);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(line6_ग_लिखो_data);

/*
	Read Line 6 device serial number.
	(POD, TonePort, GuitarPort)
*/
पूर्णांक line6_पढ़ो_serial_number(काष्ठा usb_line6 *line6, u32 *serial_number)
अणु
	वापस line6_पढ़ो_data(line6, 0x80d0, serial_number,
			       माप(*serial_number));
पूर्ण
EXPORT_SYMBOL_GPL(line6_पढ़ो_serial_number);

/*
	Card deकाष्ठाor.
*/
अटल व्योम line6_deकाष्ठा(काष्ठा snd_card *card)
अणु
	काष्ठा usb_line6 *line6 = card->निजी_data;
	काष्ठा usb_device *usbdev = line6->usbdev;

	/* Free buffer memory first. We cannot depend on the existence of निजी
	 * data from the (podhd) module, it may be gone alपढ़ोy during this call
	 */
	kमुक्त(line6->buffer_message);

	kमुक्त(line6->buffer_listen);

	/* then मुक्त URBs: */
	usb_मुक्त_urb(line6->urb_listen);
	line6->urb_listen = शून्य;

	/* decrement reference counters: */
	usb_put_dev(usbdev);
पूर्ण

अटल व्योम line6_get_usb_properties(काष्ठा usb_line6 *line6)
अणु
	काष्ठा usb_device *usbdev = line6->usbdev;
	स्थिर काष्ठा line6_properties *properties = line6->properties;
	पूर्णांक pipe;
	काष्ठा usb_host_endpoपूर्णांक *ep = शून्य;

	अगर (properties->capabilities & LINE6_CAP_CONTROL) अणु
		अगर (properties->capabilities & LINE6_CAP_CONTROL_MIDI) अणु
			pipe = usb_rcvपूर्णांकpipe(line6->usbdev,
				line6->properties->ep_ctrl_r);
		पूर्ण अन्यथा अणु
			pipe = usb_rcvbulkpipe(line6->usbdev,
				line6->properties->ep_ctrl_r);
		पूर्ण
		ep = usbdev->ep_in[usb_pipeendpoपूर्णांक(pipe)];
	पूर्ण

	/* Control data transfer properties */
	अगर (ep) अणु
		line6->पूर्णांकerval = ep->desc.bInterval;
		line6->max_packet_size = le16_to_cpu(ep->desc.wMaxPacketSize);
	पूर्ण अन्यथा अणु
		अगर (properties->capabilities & LINE6_CAP_CONTROL) अणु
			dev_err(line6->अगरcdev,
				"endpoint not available, using fallback values");
		पूर्ण
		line6->पूर्णांकerval = LINE6_FALLBACK_INTERVAL;
		line6->max_packet_size = LINE6_FALLBACK_MAXPACKETSIZE;
	पूर्ण

	/* Isochronous transfer properties */
	अगर (usbdev->speed == USB_SPEED_LOW) अणु
		line6->पूर्णांकervals_per_second = USB_LOW_INTERVALS_PER_SECOND;
		line6->iso_buffers = USB_LOW_ISO_BUFFERS;
	पूर्ण अन्यथा अणु
		line6->पूर्णांकervals_per_second = USB_HIGH_INTERVALS_PER_SECOND;
		line6->iso_buffers = USB_HIGH_ISO_BUFFERS;
	पूर्ण
पूर्ण

/* Enable buffering of incoming messages, flush the buffer */
अटल पूर्णांक line6_hwdep_खोलो(काष्ठा snd_hwdep *hw, काष्ठा file *file)
अणु
	काष्ठा usb_line6 *line6 = hw->निजी_data;

	/* NOTE: hwdep layer provides atomicity here */

	line6->messages.active = 1;
	line6->messages.nonblock = file->f_flags & O_NONBLOCK ? 1 : 0;

	वापस 0;
पूर्ण

/* Stop buffering */
अटल पूर्णांक line6_hwdep_release(काष्ठा snd_hwdep *hw, काष्ठा file *file)
अणु
	काष्ठा usb_line6 *line6 = hw->निजी_data;

	line6->messages.active = 0;

	वापस 0;
पूर्ण

/* Read from circular buffer, वापस to user */
अटल दीर्घ
line6_hwdep_पढ़ो(काष्ठा snd_hwdep *hwdep, अक्षर __user *buf, दीर्घ count,
					loff_t *offset)
अणु
	काष्ठा usb_line6 *line6 = hwdep->निजी_data;
	दीर्घ rv = 0;
	अचिन्हित पूर्णांक out_count;

	अगर (mutex_lock_पूर्णांकerruptible(&line6->messages.पढ़ो_lock))
		वापस -ERESTARTSYS;

	जबतक (kfअगरo_len(&line6->messages.fअगरo) == 0) अणु
		mutex_unlock(&line6->messages.पढ़ो_lock);

		अगर (line6->messages.nonblock)
			वापस -EAGAIN;

		rv = रुको_event_पूर्णांकerruptible(
			line6->messages.रुको_queue,
			kfअगरo_len(&line6->messages.fअगरo) != 0);
		अगर (rv < 0)
			वापस rv;

		अगर (mutex_lock_पूर्णांकerruptible(&line6->messages.पढ़ो_lock))
			वापस -ERESTARTSYS;
	पूर्ण

	अगर (kfअगरo_peek_len(&line6->messages.fअगरo) > count) अणु
		/* Buffer too small; allow re-पढ़ो of the current item... */
		rv = -EINVAL;
	पूर्ण अन्यथा अणु
		rv = kfअगरo_to_user(&line6->messages.fअगरo, buf, count, &out_count);
		अगर (rv == 0)
			rv = out_count;
	पूर्ण

	mutex_unlock(&line6->messages.पढ़ो_lock);
	वापस rv;
पूर्ण

/* Write directly (no buffering) to device by user*/
अटल दीर्घ
line6_hwdep_ग_लिखो(काष्ठा snd_hwdep *hwdep, स्थिर अक्षर __user *data, दीर्घ count,
					loff_t *offset)
अणु
	काष्ठा usb_line6 *line6 = hwdep->निजी_data;
	पूर्णांक rv;
	अक्षर *data_copy;

	अगर (count > line6->max_packet_size * LINE6_RAW_MESSAGES_MAXCOUNT) अणु
		/* This is an arbitrary limit - still better than nothing... */
		वापस -EINVAL;
	पूर्ण

	data_copy = memdup_user(data, count);
	अगर (IS_ERR(data_copy))
		वापस PTR_ERR(data_copy);

	rv = line6_send_raw_message(line6, data_copy, count);

	kमुक्त(data_copy);
	वापस rv;
पूर्ण

अटल __poll_t
line6_hwdep_poll(काष्ठा snd_hwdep *hwdep, काष्ठा file *file, poll_table *रुको)
अणु
	__poll_t rv;
	काष्ठा usb_line6 *line6 = hwdep->निजी_data;

	poll_रुको(file, &line6->messages.रुको_queue, रुको);

	mutex_lock(&line6->messages.पढ़ो_lock);
	rv = kfअगरo_len(&line6->messages.fअगरo) == 0 ? 0 : EPOLLIN | EPOLLRDNORM;
	mutex_unlock(&line6->messages.पढ़ो_lock);

	वापस rv;
पूर्ण

अटल स्थिर काष्ठा snd_hwdep_ops hwdep_ops = अणु
	.खोलो    = line6_hwdep_खोलो,
	.release = line6_hwdep_release,
	.पढ़ो    = line6_hwdep_पढ़ो,
	.ग_लिखो   = line6_hwdep_ग_लिखो,
	.poll    = line6_hwdep_poll,
पूर्ण;

/* Insert पूर्णांकo circular buffer */
अटल व्योम line6_hwdep_push_message(काष्ठा usb_line6 *line6)
अणु
	अगर (!line6->messages.active)
		वापस;

	अगर (kfअगरo_avail(&line6->messages.fअगरo) >= line6->message_length) अणु
		/* No race condition here, there's only one ग_लिखोr */
		kfअगरo_in(&line6->messages.fअगरo,
			line6->buffer_message, line6->message_length);
	पूर्ण /* अन्यथा TODO: संकेत overflow */

	wake_up_पूर्णांकerruptible(&line6->messages.रुको_queue);
पूर्ण

अटल पूर्णांक line6_hwdep_init(काष्ठा usb_line6 *line6)
अणु
	पूर्णांक err;
	काष्ठा snd_hwdep *hwdep;

	/* TODO: usb_driver_claim_पूर्णांकerface(); */
	line6->process_message = line6_hwdep_push_message;
	line6->messages.active = 0;
	init_रुकोqueue_head(&line6->messages.रुको_queue);
	mutex_init(&line6->messages.पढ़ो_lock);
	INIT_KFIFO(line6->messages.fअगरo);

	err = snd_hwdep_new(line6->card, "config", 0, &hwdep);
	अगर (err < 0)
		जाओ end;
	म_नकल(hwdep->name, "config");
	hwdep->अगरace = SNDRV_HWDEP_IFACE_LINE6;
	hwdep->ops = hwdep_ops;
	hwdep->निजी_data = line6;
	hwdep->exclusive = true;

end:
	वापस err;
पूर्ण

अटल पूर्णांक line6_init_cap_control(काष्ठा usb_line6 *line6)
अणु
	पूर्णांक ret;

	/* initialize USB buffers: */
	line6->buffer_listen = kदो_स्मृति(LINE6_बफ_मानE_LISTEN, GFP_KERNEL);
	अगर (!line6->buffer_listen)
		वापस -ENOMEM;

	line6->urb_listen = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!line6->urb_listen)
		वापस -ENOMEM;

	अगर (line6->properties->capabilities & LINE6_CAP_CONTROL_MIDI) अणु
		line6->buffer_message = kदो_स्मृति(LINE6_MIDI_MESSAGE_MAXLEN, GFP_KERNEL);
		अगर (!line6->buffer_message)
			वापस -ENOMEM;

		ret = line6_init_midi(line6);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = line6_hwdep_init(line6);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	ret = line6_start_listen(line6);
	अगर (ret < 0) अणु
		dev_err(line6->अगरcdev, "cannot start listening: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम line6_startup_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा usb_line6 *line6 =
		container_of(work, काष्ठा usb_line6, startup_work.work);

	अगर (line6->startup)
		line6->startup(line6);
पूर्ण

/*
	Probe USB device.
*/
पूर्णांक line6_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
		स्थिर काष्ठा usb_device_id *id,
		स्थिर अक्षर *driver_name,
		स्थिर काष्ठा line6_properties *properties,
		पूर्णांक (*निजी_init)(काष्ठा usb_line6 *, स्थिर काष्ठा usb_device_id *id),
		माप_प्रकार data_size)
अणु
	काष्ठा usb_device *usbdev = पूर्णांकerface_to_usbdev(पूर्णांकerface);
	काष्ठा snd_card *card;
	काष्ठा usb_line6 *line6;
	पूर्णांक पूर्णांकerface_number;
	पूर्णांक ret;

	अगर (WARN_ON(data_size < माप(*line6)))
		वापस -EINVAL;

	/* we करोn't handle multiple configurations */
	अगर (usbdev->descriptor.bNumConfigurations != 1)
		वापस -ENODEV;

	ret = snd_card_new(&पूर्णांकerface->dev,
			   SNDRV_DEFAULT_IDX1, SNDRV_DEFAULT_STR1,
			   THIS_MODULE, data_size, &card);
	अगर (ret < 0)
		वापस ret;

	/* store basic data: */
	line6 = card->निजी_data;
	line6->card = card;
	line6->properties = properties;
	line6->usbdev = usbdev;
	line6->अगरcdev = &पूर्णांकerface->dev;
	INIT_DELAYED_WORK(&line6->startup_work, line6_startup_work);

	म_नकल(card->id, properties->id);
	म_नकल(card->driver, driver_name);
	म_नकल(card->लघुname, properties->name);
	प्र_लिखो(card->दीर्घname, "Line 6 %s at USB %s", properties->name,
		dev_name(line6->अगरcdev));
	card->निजी_मुक्त = line6_deकाष्ठा;

	usb_set_पूर्णांकfdata(पूर्णांकerface, line6);

	/* increment reference counters: */
	usb_get_dev(usbdev);

	/* initialize device info: */
	dev_info(&पूर्णांकerface->dev, "Line 6 %s found\n", properties->name);

	/* query पूर्णांकerface number */
	पूर्णांकerface_number = पूर्णांकerface->cur_altsetting->desc.bInterfaceNumber;

	/* TODO reserves the bus bandwidth even without actual transfer */
	ret = usb_set_पूर्णांकerface(usbdev, पूर्णांकerface_number,
				properties->altsetting);
	अगर (ret < 0) अणु
		dev_err(&पूर्णांकerface->dev, "set_interface failed\n");
		जाओ error;
	पूर्ण

	line6_get_usb_properties(line6);

	अगर (properties->capabilities & LINE6_CAP_CONTROL) अणु
		ret = line6_init_cap_control(line6);
		अगर (ret < 0)
			जाओ error;
	पूर्ण

	/* initialize device data based on device: */
	ret = निजी_init(line6, id);
	अगर (ret < 0)
		जाओ error;

	/* creation of additional special files should go here */

	dev_info(&पूर्णांकerface->dev, "Line 6 %s now attached\n",
		 properties->name);

	वापस 0;

 error:
	/* we can call disconnect callback here because no बंद-sync is
	 * needed yet at this poपूर्णांक
	 */
	line6_disconnect(पूर्णांकerface);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(line6_probe);

/*
	Line 6 device disconnected.
*/
व्योम line6_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा usb_line6 *line6 = usb_get_पूर्णांकfdata(पूर्णांकerface);
	काष्ठा usb_device *usbdev = पूर्णांकerface_to_usbdev(पूर्णांकerface);

	अगर (!line6)
		वापस;

	अगर (WARN_ON(usbdev != line6->usbdev))
		वापस;

	cancel_delayed_work_sync(&line6->startup_work);

	अगर (line6->urb_listen != शून्य)
		line6_stop_listen(line6);

	snd_card_disconnect(line6->card);
	अगर (line6->line6pcm)
		line6_pcm_disconnect(line6->line6pcm);
	अगर (line6->disconnect)
		line6->disconnect(line6);

	dev_info(&पूर्णांकerface->dev, "Line 6 %s now disconnected\n",
		 line6->properties->name);

	/* make sure the device isn't deकाष्ठाed twice: */
	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);

	snd_card_मुक्त_when_बंदd(line6->card);
पूर्ण
EXPORT_SYMBOL_GPL(line6_disconnect);

#अगर_घोषित CONFIG_PM

/*
	Suspend Line 6 device.
*/
पूर्णांक line6_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकerface, pm_message_t message)
अणु
	काष्ठा usb_line6 *line6 = usb_get_पूर्णांकfdata(पूर्णांकerface);
	काष्ठा snd_line6_pcm *line6pcm = line6->line6pcm;

	snd_घातer_change_state(line6->card, SNDRV_CTL_POWER_D3hot);

	अगर (line6->properties->capabilities & LINE6_CAP_CONTROL)
		line6_stop_listen(line6);

	अगर (line6pcm != शून्य)
		line6pcm->flags = 0;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(line6_suspend);

/*
	Resume Line 6 device.
*/
पूर्णांक line6_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा usb_line6 *line6 = usb_get_पूर्णांकfdata(पूर्णांकerface);

	अगर (line6->properties->capabilities & LINE6_CAP_CONTROL)
		line6_start_listen(line6);

	snd_घातer_change_state(line6->card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(line6_resume);

#पूर्ण_अगर /* CONFIG_PM */

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

