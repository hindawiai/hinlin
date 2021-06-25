<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Linux driver क्रम TerraTec DMX 6Fire USB
 *
 * Device communications
 *
 * Author:	Torsten Schenk <torsten.schenk@zoho.com>
 * Created:	Jan 01, 2011
 * Copyright:	(C) Torsten Schenk
 */

#समावेश "comm.h"
#समावेश "chip.h"
#समावेश "midi.h"

क्रमागत अणु
	COMM_EP = 1,
	COMM_FPGA_EP = 2
पूर्ण;

अटल व्योम usb6fire_comm_init_urb(काष्ठा comm_runसमय *rt, काष्ठा urb *urb,
		u8 *buffer, व्योम *context, व्योम(*handler)(काष्ठा urb *urb))
अणु
	usb_init_urb(urb);
	urb->transfer_buffer = buffer;
	urb->pipe = usb_sndपूर्णांकpipe(rt->chip->dev, COMM_EP);
	urb->complete = handler;
	urb->context = context;
	urb->पूर्णांकerval = 1;
	urb->dev = rt->chip->dev;
पूर्ण

अटल व्योम usb6fire_comm_receiver_handler(काष्ठा urb *urb)
अणु
	काष्ठा comm_runसमय *rt = urb->context;
	काष्ठा midi_runसमय *midi_rt = rt->chip->midi;

	अगर (!urb->status) अणु
		अगर (rt->receiver_buffer[0] == 0x10) /* midi in event */
			अगर (midi_rt)
				midi_rt->in_received(midi_rt,
						rt->receiver_buffer + 2,
						rt->receiver_buffer[1]);
	पूर्ण

	अगर (!rt->chip->shutकरोwn) अणु
		urb->status = 0;
		urb->actual_length = 0;
		अगर (usb_submit_urb(urb, GFP_ATOMIC) < 0)
			dev_warn(&urb->dev->dev,
					"comm data receiver aborted.\n");
	पूर्ण
पूर्ण

अटल व्योम usb6fire_comm_init_buffer(u8 *buffer, u8 id, u8 request,
		u8 reg, u8 vl, u8 vh)
अणु
	buffer[0] = 0x01;
	buffer[2] = request;
	buffer[3] = id;
	चयन (request) अणु
	हाल 0x02:
		buffer[1] = 0x05; /* length (starting at buffer[2]) */
		buffer[4] = reg;
		buffer[5] = vl;
		buffer[6] = vh;
		अवरोध;

	हाल 0x12:
		buffer[1] = 0x0b; /* length (starting at buffer[2]) */
		buffer[4] = 0x00;
		buffer[5] = 0x18;
		buffer[6] = 0x05;
		buffer[7] = 0x00;
		buffer[8] = 0x01;
		buffer[9] = 0x00;
		buffer[10] = 0x9e;
		buffer[11] = reg;
		buffer[12] = vl;
		अवरोध;

	हाल 0x20:
	हाल 0x21:
	हाल 0x22:
		buffer[1] = 0x04;
		buffer[4] = reg;
		buffer[5] = vl;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक usb6fire_comm_send_buffer(u8 *buffer, काष्ठा usb_device *dev)
अणु
	पूर्णांक ret;
	पूर्णांक actual_len;

	ret = usb_पूर्णांकerrupt_msg(dev, usb_sndपूर्णांकpipe(dev, COMM_EP),
			buffer, buffer[1] + 2, &actual_len, HZ);
	अगर (ret < 0)
		वापस ret;
	अन्यथा अगर (actual_len != buffer[1] + 2)
		वापस -EIO;
	वापस 0;
पूर्ण

अटल पूर्णांक usb6fire_comm_ग_लिखो8(काष्ठा comm_runसमय *rt, u8 request,
		u8 reg, u8 value)
अणु
	u8 *buffer;
	पूर्णांक ret;

	/* 13: maximum length of message */
	buffer = kदो_स्मृति(13, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	usb6fire_comm_init_buffer(buffer, 0x00, request, reg, value, 0x00);
	ret = usb6fire_comm_send_buffer(buffer, rt->chip->dev);

	kमुक्त(buffer);
	वापस ret;
पूर्ण

अटल पूर्णांक usb6fire_comm_ग_लिखो16(काष्ठा comm_runसमय *rt, u8 request,
		u8 reg, u8 vl, u8 vh)
अणु
	u8 *buffer;
	पूर्णांक ret;

	/* 13: maximum length of message */
	buffer = kदो_स्मृति(13, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	usb6fire_comm_init_buffer(buffer, 0x00, request, reg, vl, vh);
	ret = usb6fire_comm_send_buffer(buffer, rt->chip->dev);

	kमुक्त(buffer);
	वापस ret;
पूर्ण

पूर्णांक usb6fire_comm_init(काष्ठा sfire_chip *chip)
अणु
	काष्ठा comm_runसमय *rt = kzalloc(माप(काष्ठा comm_runसमय),
			GFP_KERNEL);
	काष्ठा urb *urb;
	पूर्णांक ret;

	अगर (!rt)
		वापस -ENOMEM;

	rt->receiver_buffer = kzalloc(COMM_RECEIVER_बफ_मानE, GFP_KERNEL);
	अगर (!rt->receiver_buffer) अणु
		kमुक्त(rt);
		वापस -ENOMEM;
	पूर्ण

	urb = &rt->receiver;
	rt->serial = 1;
	rt->chip = chip;
	usb_init_urb(urb);
	rt->init_urb = usb6fire_comm_init_urb;
	rt->ग_लिखो8 = usb6fire_comm_ग_लिखो8;
	rt->ग_लिखो16 = usb6fire_comm_ग_लिखो16;

	/* submit an urb that receives communication data from device */
	urb->transfer_buffer = rt->receiver_buffer;
	urb->transfer_buffer_length = COMM_RECEIVER_बफ_मानE;
	urb->pipe = usb_rcvपूर्णांकpipe(chip->dev, COMM_EP);
	urb->dev = chip->dev;
	urb->complete = usb6fire_comm_receiver_handler;
	urb->context = rt;
	urb->पूर्णांकerval = 1;
	ret = usb_submit_urb(urb, GFP_KERNEL);
	अगर (ret < 0) अणु
		kमुक्त(rt->receiver_buffer);
		kमुक्त(rt);
		dev_err(&chip->dev->dev, "cannot create comm data receiver.");
		वापस ret;
	पूर्ण
	chip->comm = rt;
	वापस 0;
पूर्ण

व्योम usb6fire_comm_पात(काष्ठा sfire_chip *chip)
अणु
	काष्ठा comm_runसमय *rt = chip->comm;

	अगर (rt)
		usb_poison_urb(&rt->receiver);
पूर्ण

व्योम usb6fire_comm_destroy(काष्ठा sfire_chip *chip)
अणु
	काष्ठा comm_runसमय *rt = chip->comm;

	kमुक्त(rt->receiver_buffer);
	kमुक्त(rt);
	chip->comm = शून्य;
पूर्ण
