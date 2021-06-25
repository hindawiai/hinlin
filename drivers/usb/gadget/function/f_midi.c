<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * f_midi.c -- USB MIDI class function driver
 *
 * Copyright (C) 2006 Thumtronics Pty Ltd.
 * Developed क्रम Thumtronics by Grey Innovation
 * Ben Williamson <ben.williamson@greyinnovation.com>
 *
 * Rewritten क्रम the composite framework
 *   Copyright (C) 2011 Daniel Mack <zonque@gmail.com>
 *
 * Based on drivers/usb/gadget/f_audio.c,
 *   Copyright (C) 2008 Bryan Wu <cooloney@kernel.org>
 *   Copyright (C) 2008 Analog Devices, Inc
 *
 * and drivers/usb/gadget/midi.c,
 *   Copyright (C) 2006 Thumtronics Pty Ltd.
 *   Ben Williamson <ben.williamson@greyinnovation.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/spinlock.h>

#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/rawmidi.h>

#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/audपन.स>
#समावेश <linux/usb/midi.h>

#समावेश "u_f.h"
#समावेश "u_midi.h"

MODULE_AUTHOR("Ben Williamson");
MODULE_LICENSE("GPL v2");

अटल स्थिर अक्षर f_midi_लघुname[] = "f_midi";
अटल स्थिर अक्षर f_midi_दीर्घname[] = "MIDI Gadget";

/*
 * We can only handle 16 cables on one single endpoपूर्णांक, as cable numbers are
 * stored in 4-bit fields. And as the पूर्णांकerface currently only holds one
 * single endpoपूर्णांक, this is the maximum number of ports we can allow.
 */
#घोषणा MAX_PORTS 16

/* MIDI message states */
क्रमागत अणु
	STATE_INITIAL = 0,	/* pseuकरो state */
	STATE_1PARAM,
	STATE_2PARAM_1,
	STATE_2PARAM_2,
	STATE_SYSEX_0,
	STATE_SYSEX_1,
	STATE_SYSEX_2,
	STATE_REAL_TIME,
	STATE_FINISHED,		/* pseuकरो state */
पूर्ण;

/*
 * This is a gadget, and the IN/OUT naming is from the host's perspective.
 * USB -> OUT endpoपूर्णांक -> rawmidi
 * USB <- IN endpoपूर्णांक  <- rawmidi
 */
काष्ठा gmidi_in_port अणु
	काष्ठा snd_rawmidi_substream *substream;
	पूर्णांक active;
	uपूर्णांक8_t cable;
	uपूर्णांक8_t state;
	uपूर्णांक8_t data[2];
पूर्ण;

काष्ठा f_midi अणु
	काष्ठा usb_function	func;
	काष्ठा usb_gadget	*gadget;
	काष्ठा usb_ep		*in_ep, *out_ep;
	काष्ठा snd_card		*card;
	काष्ठा snd_rawmidi	*rmidi;
	u8			ms_id;

	काष्ठा snd_rawmidi_substream *out_substream[MAX_PORTS];

	अचिन्हित दीर्घ		out_triggered;
	काष्ठा work_काष्ठा	work;
	अचिन्हित पूर्णांक in_ports;
	अचिन्हित पूर्णांक out_ports;
	पूर्णांक index;
	अक्षर *id;
	अचिन्हित पूर्णांक buflen, qlen;
	/* This fअगरo is used as a buffer ring क्रम pre-allocated IN usb_requests */
	DECLARE_KFIFO_PTR(in_req_fअगरo, काष्ठा usb_request *);
	spinlock_t transmit_lock;
	अचिन्हित पूर्णांक in_last_port;
	अचिन्हित अक्षर मुक्त_ref;

	काष्ठा gmidi_in_port	in_ports_array[/* in_ports */];
पूर्ण;

अटल अंतरभूत काष्ठा f_midi *func_to_midi(काष्ठा usb_function *f)
अणु
	वापस container_of(f, काष्ठा f_midi, func);
पूर्ण

अटल व्योम f_midi_transmit(काष्ठा f_midi *midi);
अटल व्योम f_midi_rmidi_मुक्त(काष्ठा snd_rawmidi *rmidi);
अटल व्योम f_midi_मुक्त_inst(काष्ठा usb_function_instance *f);

DECLARE_UAC_AC_HEADER_DESCRIPTOR(1);
DECLARE_USB_MIDI_OUT_JACK_DESCRIPTOR(1);
DECLARE_USB_MS_ENDPOINT_DESCRIPTOR(16);

/* B.3.1  Standard AC Interface Descriptor */
अटल काष्ठा usb_पूर्णांकerface_descriptor ac_पूर्णांकerface_desc = अणु
	.bLength =		USB_DT_INTERFACE_SIZE,
	.bDescriptorType =	USB_DT_INTERFACE,
	/* .bInterfaceNumber =	DYNAMIC */
	/* .bNumEndpoपूर्णांकs =	DYNAMIC */
	.bInterfaceClass =	USB_CLASS_AUDIO,
	.bInterfaceSubClass =	USB_SUBCLASS_AUDIOCONTROL,
	/* .iInterface =	DYNAMIC */
पूर्ण;

/* B.3.2  Class-Specअगरic AC Interface Descriptor */
अटल काष्ठा uac1_ac_header_descriptor_1 ac_header_desc = अणु
	.bLength =		UAC_DT_AC_HEADER_SIZE(1),
	.bDescriptorType =	USB_DT_CS_INTERFACE,
	.bDescriptorSubtype =	USB_MS_HEADER,
	.bcdADC =		cpu_to_le16(0x0100),
	.wTotalLength =		cpu_to_le16(UAC_DT_AC_HEADER_SIZE(1)),
	.bInCollection =	1,
	/* .baInterfaceNr =	DYNAMIC */
पूर्ण;

/* B.4.1  Standard MS Interface Descriptor */
अटल काष्ठा usb_पूर्णांकerface_descriptor ms_पूर्णांकerface_desc = अणु
	.bLength =		USB_DT_INTERFACE_SIZE,
	.bDescriptorType =	USB_DT_INTERFACE,
	/* .bInterfaceNumber =	DYNAMIC */
	.bNumEndpoपूर्णांकs =	2,
	.bInterfaceClass =	USB_CLASS_AUDIO,
	.bInterfaceSubClass =	USB_SUBCLASS_MIDISTREAMING,
	/* .iInterface =	DYNAMIC */
पूर्ण;

/* B.4.2  Class-Specअगरic MS Interface Descriptor */
अटल काष्ठा usb_ms_header_descriptor ms_header_desc = अणु
	.bLength =		USB_DT_MS_HEADER_SIZE,
	.bDescriptorType =	USB_DT_CS_INTERFACE,
	.bDescriptorSubtype =	USB_MS_HEADER,
	.bcdMSC =		cpu_to_le16(0x0100),
	/* .wTotalLength =	DYNAMIC */
पूर्ण;

/* B.5.1  Standard Bulk OUT Endpoपूर्णांक Descriptor */
अटल काष्ठा usb_endpoपूर्णांक_descriptor bulk_out_desc = अणु
	.bLength =		USB_DT_ENDPOINT_AUDIO_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress =	USB_सूची_OUT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
पूर्ण;

अटल काष्ठा usb_ss_ep_comp_descriptor bulk_out_ss_comp_desc = अणु
	.bLength                = माप(bulk_out_ss_comp_desc),
	.bDescriptorType        = USB_DT_SS_ENDPOINT_COMP,
	/* .bMaxBurst           = 0, */
	/* .bmAttributes        = 0, */
पूर्ण;

/* B.5.2  Class-specअगरic MS Bulk OUT Endpoपूर्णांक Descriptor */
अटल काष्ठा usb_ms_endpoपूर्णांक_descriptor_16 ms_out_desc = अणु
	/* .bLength =		DYNAMIC */
	.bDescriptorType =	USB_DT_CS_ENDPOINT,
	.bDescriptorSubtype =	USB_MS_GENERAL,
	/* .bNumEmbMIDIJack =	DYNAMIC */
	/* .baAssocJackID =	DYNAMIC */
पूर्ण;

/* B.6.1  Standard Bulk IN Endpoपूर्णांक Descriptor */
अटल काष्ठा usb_endpoपूर्णांक_descriptor bulk_in_desc = अणु
	.bLength =		USB_DT_ENDPOINT_AUDIO_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
पूर्ण;

अटल काष्ठा usb_ss_ep_comp_descriptor bulk_in_ss_comp_desc = अणु
	.bLength                = माप(bulk_in_ss_comp_desc),
	.bDescriptorType        = USB_DT_SS_ENDPOINT_COMP,
	/* .bMaxBurst           = 0, */
	/* .bmAttributes        = 0, */
पूर्ण;

/* B.6.2  Class-specअगरic MS Bulk IN Endpoपूर्णांक Descriptor */
अटल काष्ठा usb_ms_endpoपूर्णांक_descriptor_16 ms_in_desc = अणु
	/* .bLength =		DYNAMIC */
	.bDescriptorType =	USB_DT_CS_ENDPOINT,
	.bDescriptorSubtype =	USB_MS_GENERAL,
	/* .bNumEmbMIDIJack =	DYNAMIC */
	/* .baAssocJackID =	DYNAMIC */
पूर्ण;

/* string IDs are asचिन्हित dynamically */

#घोषणा STRING_FUNC_IDX			0

अटल काष्ठा usb_string midi_string_defs[] = अणु
	[STRING_FUNC_IDX].s = "MIDI function",
	अणु  पूर्ण /* end of list */
पूर्ण;

अटल काष्ठा usb_gadget_strings midi_stringtab = अणु
	.language	= 0x0409,	/* en-us */
	.strings	= midi_string_defs,
पूर्ण;

अटल काष्ठा usb_gadget_strings *midi_strings[] = अणु
	&midi_stringtab,
	शून्य,
पूर्ण;

अटल अंतरभूत काष्ठा usb_request *midi_alloc_ep_req(काष्ठा usb_ep *ep,
						    अचिन्हित length)
अणु
	वापस alloc_ep_req(ep, length);
पूर्ण

अटल स्थिर uपूर्णांक8_t f_midi_cin_length[] = अणु
	0, 0, 2, 3, 3, 1, 2, 3, 3, 3, 3, 3, 2, 2, 3, 1
पूर्ण;

/*
 * Receives a chunk of MIDI data.
 */
अटल व्योम f_midi_पढ़ो_data(काष्ठा usb_ep *ep, पूर्णांक cable,
			     uपूर्णांक8_t *data, पूर्णांक length)
अणु
	काष्ठा f_midi *midi = ep->driver_data;
	काष्ठा snd_rawmidi_substream *substream = midi->out_substream[cable];

	अगर (!substream)
		/* Nobody is listening - throw it on the न्यूनमान. */
		वापस;

	अगर (!test_bit(cable, &midi->out_triggered))
		वापस;

	snd_rawmidi_receive(substream, data, length);
पूर्ण

अटल व्योम f_midi_handle_out_data(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	अचिन्हित पूर्णांक i;
	u8 *buf = req->buf;

	क्रम (i = 0; i + 3 < req->actual; i += 4)
		अगर (buf[i] != 0) अणु
			पूर्णांक cable = buf[i] >> 4;
			पूर्णांक length = f_midi_cin_length[buf[i] & 0x0f];
			f_midi_पढ़ो_data(ep, cable, &buf[i + 1], length);
		पूर्ण
पूर्ण

अटल व्योम
f_midi_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा f_midi *midi = ep->driver_data;
	काष्ठा usb_composite_dev *cdev = midi->func.config->cdev;
	पूर्णांक status = req->status;

	चयन (status) अणु
	हाल 0:			 /* normal completion */
		अगर (ep == midi->out_ep) अणु
			/* We received stuff. req is queued again, below */
			f_midi_handle_out_data(ep, req);
		पूर्ण अन्यथा अगर (ep == midi->in_ep) अणु
			/* Our transmit completed. See अगर there's more to go.
			 * f_midi_transmit eats req, करोn't queue it again. */
			req->length = 0;
			f_midi_transmit(midi);
			वापस;
		पूर्ण
		अवरोध;

	/* this endpoपूर्णांक is normally active जबतक we're configured */
	हाल -ECONNABORTED:	/* hardware क्रमced ep reset */
	हाल -ECONNRESET:	/* request dequeued */
	हाल -ESHUTDOWN:	/* disconnect from host */
		VDBG(cdev, "%s gone (%d), %d/%d\n", ep->name, status,
				req->actual, req->length);
		अगर (ep == midi->out_ep) अणु
			f_midi_handle_out_data(ep, req);
			/* We करोn't need to free IN requests because it's handled
			 * by the midi->in_req_fअगरo. */
			मुक्त_ep_req(ep, req);
		पूर्ण
		वापस;

	हाल -EOVERFLOW:	/* buffer overrun on पढ़ो means that
				 * we didn't provide a big enough buffer.
				 */
	शेष:
		DBG(cdev, "%s complete --> %d, %d/%d\n", ep->name,
				status, req->actual, req->length);
		अवरोध;
	हाल -EREMOTEIO:	/* लघु पढ़ो */
		अवरोध;
	पूर्ण

	status = usb_ep_queue(ep, req, GFP_ATOMIC);
	अगर (status) अणु
		ERROR(cdev, "kill %s:  resubmit %d bytes --> %d\n",
				ep->name, req->length, status);
		usb_ep_set_halt(ep);
		/* FIXME recover later ... somehow */
	पूर्ण
पूर्ण

अटल व्योम f_midi_drop_out_substreams(काष्ठा f_midi *midi)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < midi->in_ports; i++) अणु
		काष्ठा gmidi_in_port *port = midi->in_ports_array + i;
		काष्ठा snd_rawmidi_substream *substream = port->substream;

		अगर (port->active && substream)
			snd_rawmidi_drop_output(substream);
	पूर्ण
पूर्ण

अटल पूर्णांक f_midi_start_ep(काष्ठा f_midi *midi,
			   काष्ठा usb_function *f,
			   काष्ठा usb_ep *ep)
अणु
	पूर्णांक err;
	काष्ठा usb_composite_dev *cdev = f->config->cdev;

	usb_ep_disable(ep);

	err = config_ep_by_speed(midi->gadget, f, ep);
	अगर (err) अणु
		ERROR(cdev, "can't configure %s: %d\n", ep->name, err);
		वापस err;
	पूर्ण

	err = usb_ep_enable(ep);
	अगर (err) अणु
		ERROR(cdev, "can't start %s: %d\n", ep->name, err);
		वापस err;
	पूर्ण

	ep->driver_data = midi;

	वापस 0;
पूर्ण

अटल पूर्णांक f_midi_set_alt(काष्ठा usb_function *f, अचिन्हित पूर्णांकf, अचिन्हित alt)
अणु
	काष्ठा f_midi *midi = func_to_midi(f);
	अचिन्हित i;
	पूर्णांक err;

	/* we only set alt क्रम MIDIStreaming पूर्णांकerface */
	अगर (पूर्णांकf != midi->ms_id)
		वापस 0;

	err = f_midi_start_ep(midi, f, midi->in_ep);
	अगर (err)
		वापस err;

	err = f_midi_start_ep(midi, f, midi->out_ep);
	अगर (err)
		वापस err;

	/* pre-allocate ग_लिखो usb requests to use on f_midi_transmit. */
	जबतक (kfअगरo_avail(&midi->in_req_fअगरo)) अणु
		काष्ठा usb_request *req =
			midi_alloc_ep_req(midi->in_ep, midi->buflen);

		अगर (req == शून्य)
			वापस -ENOMEM;

		req->length = 0;
		req->complete = f_midi_complete;

		kfअगरo_put(&midi->in_req_fअगरo, req);
	पूर्ण

	/* allocate a bunch of पढ़ो buffers and queue them all at once. */
	क्रम (i = 0; i < midi->qlen && err == 0; i++) अणु
		काष्ठा usb_request *req =
			midi_alloc_ep_req(midi->out_ep, midi->buflen);

		अगर (req == शून्य)
			वापस -ENOMEM;

		req->complete = f_midi_complete;
		err = usb_ep_queue(midi->out_ep, req, GFP_ATOMIC);
		अगर (err) अणु
			ERROR(midi, "%s: couldn't enqueue request: %d\n",
				    midi->out_ep->name, err);
			अगर (req->buf != शून्य)
				मुक्त_ep_req(midi->out_ep, req);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम f_midi_disable(काष्ठा usb_function *f)
अणु
	काष्ठा f_midi *midi = func_to_midi(f);
	काष्ठा usb_composite_dev *cdev = f->config->cdev;
	काष्ठा usb_request *req = शून्य;

	DBG(cdev, "disable\n");

	/*
	 * just disable endpoपूर्णांकs, क्रमcing completion of pending i/o.
	 * all our completion handlers मुक्त their requests in this हाल.
	 */
	usb_ep_disable(midi->in_ep);
	usb_ep_disable(midi->out_ep);

	/* release IN requests */
	जबतक (kfअगरo_get(&midi->in_req_fअगरo, &req))
		मुक्त_ep_req(midi->in_ep, req);

	f_midi_drop_out_substreams(midi);
पूर्ण

अटल पूर्णांक f_midi_snd_मुक्त(काष्ठा snd_device *device)
अणु
	वापस 0;
पूर्ण

/*
 * Converts MIDI commands to USB MIDI packets.
 */
अटल व्योम f_midi_transmit_byte(काष्ठा usb_request *req,
				 काष्ठा gmidi_in_port *port, uपूर्णांक8_t b)
अणु
	uपूर्णांक8_t p[4] = अणु port->cable << 4, 0, 0, 0 पूर्ण;
	uपूर्णांक8_t next_state = STATE_INITIAL;

	चयन (b) अणु
	हाल 0xf8 ... 0xff:
		/* System Real-Time Messages */
		p[0] |= 0x0f;
		p[1] = b;
		next_state = port->state;
		port->state = STATE_REAL_TIME;
		अवरोध;

	हाल 0xf7:
		/* End of SysEx */
		चयन (port->state) अणु
		हाल STATE_SYSEX_0:
			p[0] |= 0x05;
			p[1] = 0xf7;
			next_state = STATE_FINISHED;
			अवरोध;
		हाल STATE_SYSEX_1:
			p[0] |= 0x06;
			p[1] = port->data[0];
			p[2] = 0xf7;
			next_state = STATE_FINISHED;
			अवरोध;
		हाल STATE_SYSEX_2:
			p[0] |= 0x07;
			p[1] = port->data[0];
			p[2] = port->data[1];
			p[3] = 0xf7;
			next_state = STATE_FINISHED;
			अवरोध;
		शेष:
			/* Ignore byte */
			next_state = port->state;
			port->state = STATE_INITIAL;
		पूर्ण
		अवरोध;

	हाल 0xf0 ... 0xf6:
		/* System Common Messages */
		port->data[0] = port->data[1] = 0;
		port->state = STATE_INITIAL;
		चयन (b) अणु
		हाल 0xf0:
			port->data[0] = b;
			port->data[1] = 0;
			next_state = STATE_SYSEX_1;
			अवरोध;
		हाल 0xf1:
		हाल 0xf3:
			port->data[0] = b;
			next_state = STATE_1PARAM;
			अवरोध;
		हाल 0xf2:
			port->data[0] = b;
			next_state = STATE_2PARAM_1;
			अवरोध;
		हाल 0xf4:
		हाल 0xf5:
			next_state = STATE_INITIAL;
			अवरोध;
		हाल 0xf6:
			p[0] |= 0x05;
			p[1] = 0xf6;
			next_state = STATE_FINISHED;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल 0x80 ... 0xef:
		/*
		 * Channel Voice Messages, Channel Mode Messages
		 * and Control Change Messages.
		 */
		port->data[0] = b;
		port->data[1] = 0;
		port->state = STATE_INITIAL;
		अगर (b >= 0xc0 && b <= 0xdf)
			next_state = STATE_1PARAM;
		अन्यथा
			next_state = STATE_2PARAM_1;
		अवरोध;

	हाल 0x00 ... 0x7f:
		/* Message parameters */
		चयन (port->state) अणु
		हाल STATE_1PARAM:
			अगर (port->data[0] < 0xf0)
				p[0] |= port->data[0] >> 4;
			अन्यथा
				p[0] |= 0x02;

			p[1] = port->data[0];
			p[2] = b;
			/* This is to allow Running State Messages */
			next_state = STATE_1PARAM;
			अवरोध;
		हाल STATE_2PARAM_1:
			port->data[1] = b;
			next_state = STATE_2PARAM_2;
			अवरोध;
		हाल STATE_2PARAM_2:
			अगर (port->data[0] < 0xf0)
				p[0] |= port->data[0] >> 4;
			अन्यथा
				p[0] |= 0x03;

			p[1] = port->data[0];
			p[2] = port->data[1];
			p[3] = b;
			/* This is to allow Running State Messages */
			next_state = STATE_2PARAM_1;
			अवरोध;
		हाल STATE_SYSEX_0:
			port->data[0] = b;
			next_state = STATE_SYSEX_1;
			अवरोध;
		हाल STATE_SYSEX_1:
			port->data[1] = b;
			next_state = STATE_SYSEX_2;
			अवरोध;
		हाल STATE_SYSEX_2:
			p[0] |= 0x04;
			p[1] = port->data[0];
			p[2] = port->data[1];
			p[3] = b;
			next_state = STATE_SYSEX_0;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	/* States where we have to ग_लिखो पूर्णांकo the USB request */
	अगर (next_state == STATE_FINISHED ||
	    port->state == STATE_SYSEX_2 ||
	    port->state == STATE_1PARAM ||
	    port->state == STATE_2PARAM_2 ||
	    port->state == STATE_REAL_TIME) अणु

		अचिन्हित पूर्णांक length = req->length;
		u8 *buf = (u8 *)req->buf + length;

		स_नकल(buf, p, माप(p));
		req->length = length + माप(p);

		अगर (next_state == STATE_FINISHED) अणु
			next_state = STATE_INITIAL;
			port->data[0] = port->data[1] = 0;
		पूर्ण
	पूर्ण

	port->state = next_state;
पूर्ण

अटल पूर्णांक f_midi_करो_transmit(काष्ठा f_midi *midi, काष्ठा usb_ep *ep)
अणु
	काष्ठा usb_request *req = शून्य;
	अचिन्हित पूर्णांक len, i;
	bool active = false;
	पूर्णांक err;

	/*
	 * We peek the request in order to reuse it अगर it fails to enqueue on
	 * its endpoपूर्णांक
	 */
	len = kfअगरo_peek(&midi->in_req_fअगरo, &req);
	अगर (len != 1) अणु
		ERROR(midi, "%s: Couldn't get usb request\n", __func__);
		वापस -1;
	पूर्ण

	/*
	 * If buffer overrun, then we ignore this transmission.
	 * IMPORTANT: This will cause the user-space rawmidi device to block
	 * until a) usb requests have been completed or b) snd_rawmidi_ग_लिखो()
	 * बार out.
	 */
	अगर (req->length > 0)
		वापस 0;

	क्रम (i = midi->in_last_port; i < midi->in_ports; ++i) अणु
		काष्ठा gmidi_in_port *port = midi->in_ports_array + i;
		काष्ठा snd_rawmidi_substream *substream = port->substream;

		अगर (!port->active || !substream)
			जारी;

		जबतक (req->length + 3 < midi->buflen) अणु
			uपूर्णांक8_t b;

			अगर (snd_rawmidi_transmit(substream, &b, 1) != 1) अणु
				port->active = 0;
				अवरोध;
			पूर्ण
			f_midi_transmit_byte(req, port, b);
		पूर्ण

		active = !!port->active;
		अगर (active)
			अवरोध;
	पूर्ण
	midi->in_last_port = active ? i : 0;

	अगर (req->length <= 0)
		जाओ करोne;

	err = usb_ep_queue(ep, req, GFP_ATOMIC);
	अगर (err < 0) अणु
		ERROR(midi, "%s failed to queue req: %d\n",
		      midi->in_ep->name, err);
		req->length = 0; /* Re-use request next समय. */
	पूर्ण अन्यथा अणु
		/* Upon success, put request at the back of the queue. */
		kfअगरo_skip(&midi->in_req_fअगरo);
		kfअगरo_put(&midi->in_req_fअगरo, req);
	पूर्ण

करोne:
	वापस active;
पूर्ण

अटल व्योम f_midi_transmit(काष्ठा f_midi *midi)
अणु
	काष्ठा usb_ep *ep = midi->in_ep;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	/* We only care about USB requests अगर IN endpoपूर्णांक is enabled */
	अगर (!ep || !ep->enabled)
		जाओ drop_out;

	spin_lock_irqsave(&midi->transmit_lock, flags);

	करो अणु
		ret = f_midi_करो_transmit(midi, ep);
		अगर (ret < 0) अणु
			spin_unlock_irqrestore(&midi->transmit_lock, flags);
			जाओ drop_out;
		पूर्ण
	पूर्ण जबतक (ret);

	spin_unlock_irqrestore(&midi->transmit_lock, flags);

	वापस;

drop_out:
	f_midi_drop_out_substreams(midi);
पूर्ण

अटल व्योम f_midi_in_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा f_midi *midi;

	midi = container_of(work, काष्ठा f_midi, work);
	f_midi_transmit(midi);
पूर्ण

अटल पूर्णांक f_midi_in_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा f_midi *midi = substream->rmidi->निजी_data;
	काष्ठा gmidi_in_port *port;

	अगर (substream->number >= midi->in_ports)
		वापस -EINVAL;

	VDBG(midi, "%s()\n", __func__);
	port = midi->in_ports_array + substream->number;
	port->substream = substream;
	port->state = STATE_INITIAL;
	वापस 0;
पूर्ण

अटल पूर्णांक f_midi_in_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा f_midi *midi = substream->rmidi->निजी_data;

	VDBG(midi, "%s()\n", __func__);
	वापस 0;
पूर्ण

अटल व्योम f_midi_in_trigger(काष्ठा snd_rawmidi_substream *substream, पूर्णांक up)
अणु
	काष्ठा f_midi *midi = substream->rmidi->निजी_data;

	अगर (substream->number >= midi->in_ports)
		वापस;

	VDBG(midi, "%s() %d\n", __func__, up);
	midi->in_ports_array[substream->number].active = up;
	अगर (up)
		queue_work(प्रणाली_highpri_wq, &midi->work);
पूर्ण

अटल पूर्णांक f_midi_out_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा f_midi *midi = substream->rmidi->निजी_data;

	अगर (substream->number >= MAX_PORTS)
		वापस -EINVAL;

	VDBG(midi, "%s()\n", __func__);
	midi->out_substream[substream->number] = substream;
	वापस 0;
पूर्ण

अटल पूर्णांक f_midi_out_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा f_midi *midi = substream->rmidi->निजी_data;

	VDBG(midi, "%s()\n", __func__);
	वापस 0;
पूर्ण

अटल व्योम f_midi_out_trigger(काष्ठा snd_rawmidi_substream *substream, पूर्णांक up)
अणु
	काष्ठा f_midi *midi = substream->rmidi->निजी_data;

	VDBG(midi, "%s()\n", __func__);

	अगर (up)
		set_bit(substream->number, &midi->out_triggered);
	अन्यथा
		clear_bit(substream->number, &midi->out_triggered);
पूर्ण

अटल स्थिर काष्ठा snd_rawmidi_ops gmidi_in_ops = अणु
	.खोलो = f_midi_in_खोलो,
	.बंद = f_midi_in_बंद,
	.trigger = f_midi_in_trigger,
पूर्ण;

अटल स्थिर काष्ठा snd_rawmidi_ops gmidi_out_ops = अणु
	.खोलो = f_midi_out_खोलो,
	.बंद = f_midi_out_बंद,
	.trigger = f_midi_out_trigger
पूर्ण;

अटल अंतरभूत व्योम f_midi_unरेजिस्टर_card(काष्ठा f_midi *midi)
अणु
	अगर (midi->card) अणु
		snd_card_मुक्त(midi->card);
		midi->card = शून्य;
	पूर्ण
पूर्ण

/* रेजिस्टर as a sound "card" */
अटल पूर्णांक f_midi_रेजिस्टर_card(काष्ठा f_midi *midi)
अणु
	काष्ठा snd_card *card;
	काष्ठा snd_rawmidi *rmidi;
	पूर्णांक err;
	अटल काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त = f_midi_snd_मुक्त,
	पूर्ण;

	err = snd_card_new(&midi->gadget->dev, midi->index, midi->id,
			   THIS_MODULE, 0, &card);
	अगर (err < 0) अणु
		ERROR(midi, "snd_card_new() failed\n");
		जाओ fail;
	पूर्ण
	midi->card = card;

	err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, midi, &ops);
	अगर (err < 0) अणु
		ERROR(midi, "snd_device_new() failed: error %d\n", err);
		जाओ fail;
	पूर्ण

	म_नकल(card->driver, f_midi_दीर्घname);
	म_नकल(card->दीर्घname, f_midi_दीर्घname);
	म_नकल(card->लघुname, f_midi_लघुname);

	/* Set up rawmidi */
	snd_component_add(card, "MIDI");
	err = snd_rawmidi_new(card, card->दीर्घname, 0,
			      midi->out_ports, midi->in_ports, &rmidi);
	अगर (err < 0) अणु
		ERROR(midi, "snd_rawmidi_new() failed: error %d\n", err);
		जाओ fail;
	पूर्ण
	midi->rmidi = rmidi;
	midi->in_last_port = 0;
	म_नकल(rmidi->name, card->लघुname);
	rmidi->info_flags = SNDRV_RAWMIDI_INFO_OUTPUT |
			    SNDRV_RAWMIDI_INFO_INPUT |
			    SNDRV_RAWMIDI_INFO_DUPLEX;
	rmidi->निजी_data = midi;
	rmidi->निजी_मुक्त = f_midi_rmidi_मुक्त;
	midi->मुक्त_ref++;

	/*
	 * Yes, rawmidi OUTPUT = USB IN, and rawmidi INPUT = USB OUT.
	 * It's an upside-करोwn world being a gadget.
	 */
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT, &gmidi_in_ops);
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_INPUT, &gmidi_out_ops);

	/* रेजिस्टर it - we're पढ़ोy to go */
	err = snd_card_रेजिस्टर(card);
	अगर (err < 0) अणु
		ERROR(midi, "snd_card_register() failed\n");
		जाओ fail;
	पूर्ण

	VDBG(midi, "%s() finished ok\n", __func__);
	वापस 0;

fail:
	f_midi_unरेजिस्टर_card(midi);
	वापस err;
पूर्ण

/* MIDI function driver setup/binding */

अटल पूर्णांक f_midi_bind(काष्ठा usb_configuration *c, काष्ठा usb_function *f)
अणु
	काष्ठा usb_descriptor_header **midi_function;
	काष्ठा usb_midi_in_jack_descriptor jack_in_ext_desc[MAX_PORTS];
	काष्ठा usb_midi_in_jack_descriptor jack_in_emb_desc[MAX_PORTS];
	काष्ठा usb_midi_out_jack_descriptor_1 jack_out_ext_desc[MAX_PORTS];
	काष्ठा usb_midi_out_jack_descriptor_1 jack_out_emb_desc[MAX_PORTS];
	काष्ठा usb_composite_dev *cdev = c->cdev;
	काष्ठा f_midi *midi = func_to_midi(f);
	काष्ठा usb_string *us;
	पूर्णांक status, n, jack = 1, i = 0, endpoपूर्णांक_descriptor_index = 0;

	midi->gadget = cdev->gadget;
	INIT_WORK(&midi->work, f_midi_in_work);
	status = f_midi_रेजिस्टर_card(midi);
	अगर (status < 0)
		जाओ fail_रेजिस्टर;

	/* maybe allocate device-global string ID */
	us = usb_gstrings_attach(c->cdev, midi_strings,
				 ARRAY_SIZE(midi_string_defs));
	अगर (IS_ERR(us)) अणु
		status = PTR_ERR(us);
		जाओ fail;
	पूर्ण
	ac_पूर्णांकerface_desc.iInterface = us[STRING_FUNC_IDX].id;

	/* We have two पूर्णांकerfaces, AudioControl and MIDIStreaming */
	status = usb_पूर्णांकerface_id(c, f);
	अगर (status < 0)
		जाओ fail;
	ac_पूर्णांकerface_desc.bInterfaceNumber = status;

	status = usb_पूर्णांकerface_id(c, f);
	अगर (status < 0)
		जाओ fail;
	ms_पूर्णांकerface_desc.bInterfaceNumber = status;
	ac_header_desc.baInterfaceNr[0] = status;
	midi->ms_id = status;

	status = -ENODEV;

	/* allocate instance-specअगरic endpoपूर्णांकs */
	midi->in_ep = usb_ep_स्वतःconfig(cdev->gadget, &bulk_in_desc);
	अगर (!midi->in_ep)
		जाओ fail;

	midi->out_ep = usb_ep_स्वतःconfig(cdev->gadget, &bulk_out_desc);
	अगर (!midi->out_ep)
		जाओ fail;

	/* allocate temporary function list */
	midi_function = kसुस्मृति((MAX_PORTS * 4) + 11, माप(*midi_function),
				GFP_KERNEL);
	अगर (!midi_function) अणु
		status = -ENOMEM;
		जाओ fail;
	पूर्ण

	/*
	 * स्थिरruct the function's descriptor set. As the number of
	 * input and output MIDI ports is configurable, we have to करो
	 * it that way.
	 */

	/* add the headers - these are always the same */
	midi_function[i++] = (काष्ठा usb_descriptor_header *) &ac_पूर्णांकerface_desc;
	midi_function[i++] = (काष्ठा usb_descriptor_header *) &ac_header_desc;
	midi_function[i++] = (काष्ठा usb_descriptor_header *) &ms_पूर्णांकerface_desc;

	/* calculate the header's wTotalLength */
	n = USB_DT_MS_HEADER_SIZE
		+ (midi->in_ports + midi->out_ports) *
			(USB_DT_MIDI_IN_SIZE + USB_DT_MIDI_OUT_SIZE(1));
	ms_header_desc.wTotalLength = cpu_to_le16(n);

	midi_function[i++] = (काष्ठा usb_descriptor_header *) &ms_header_desc;

	/* configure the बाह्यal IN jacks, each linked to an embedded OUT jack */
	क्रम (n = 0; n < midi->in_ports; n++) अणु
		काष्ठा usb_midi_in_jack_descriptor *in_ext = &jack_in_ext_desc[n];
		काष्ठा usb_midi_out_jack_descriptor_1 *out_emb = &jack_out_emb_desc[n];

		in_ext->bLength			= USB_DT_MIDI_IN_SIZE;
		in_ext->bDescriptorType		= USB_DT_CS_INTERFACE;
		in_ext->bDescriptorSubtype	= USB_MS_MIDI_IN_JACK;
		in_ext->bJackType		= USB_MS_EXTERNAL;
		in_ext->bJackID			= jack++;
		in_ext->iJack			= 0;
		midi_function[i++] = (काष्ठा usb_descriptor_header *) in_ext;

		out_emb->bLength		= USB_DT_MIDI_OUT_SIZE(1);
		out_emb->bDescriptorType	= USB_DT_CS_INTERFACE;
		out_emb->bDescriptorSubtype	= USB_MS_MIDI_OUT_JACK;
		out_emb->bJackType		= USB_MS_EMBEDDED;
		out_emb->bJackID		= jack++;
		out_emb->bNrInputPins		= 1;
		out_emb->pins[0].baSourcePin	= 1;
		out_emb->pins[0].baSourceID	= in_ext->bJackID;
		out_emb->iJack			= 0;
		midi_function[i++] = (काष्ठा usb_descriptor_header *) out_emb;

		/* link it to the endpoपूर्णांक */
		ms_in_desc.baAssocJackID[n] = out_emb->bJackID;
	पूर्ण

	/* configure the बाह्यal OUT jacks, each linked to an embedded IN jack */
	क्रम (n = 0; n < midi->out_ports; n++) अणु
		काष्ठा usb_midi_in_jack_descriptor *in_emb = &jack_in_emb_desc[n];
		काष्ठा usb_midi_out_jack_descriptor_1 *out_ext = &jack_out_ext_desc[n];

		in_emb->bLength			= USB_DT_MIDI_IN_SIZE;
		in_emb->bDescriptorType		= USB_DT_CS_INTERFACE;
		in_emb->bDescriptorSubtype	= USB_MS_MIDI_IN_JACK;
		in_emb->bJackType		= USB_MS_EMBEDDED;
		in_emb->bJackID			= jack++;
		in_emb->iJack			= 0;
		midi_function[i++] = (काष्ठा usb_descriptor_header *) in_emb;

		out_ext->bLength =		USB_DT_MIDI_OUT_SIZE(1);
		out_ext->bDescriptorType =	USB_DT_CS_INTERFACE;
		out_ext->bDescriptorSubtype =	USB_MS_MIDI_OUT_JACK;
		out_ext->bJackType =		USB_MS_EXTERNAL;
		out_ext->bJackID =		jack++;
		out_ext->bNrInputPins =		1;
		out_ext->iJack =		0;
		out_ext->pins[0].baSourceID =	in_emb->bJackID;
		out_ext->pins[0].baSourcePin =	1;
		midi_function[i++] = (काष्ठा usb_descriptor_header *) out_ext;

		/* link it to the endpoपूर्णांक */
		ms_out_desc.baAssocJackID[n] = in_emb->bJackID;
	पूर्ण

	/* configure the endpoपूर्णांक descriptors ... */
	ms_out_desc.bLength = USB_DT_MS_ENDPOINT_SIZE(midi->in_ports);
	ms_out_desc.bNumEmbMIDIJack = midi->in_ports;

	ms_in_desc.bLength = USB_DT_MS_ENDPOINT_SIZE(midi->out_ports);
	ms_in_desc.bNumEmbMIDIJack = midi->out_ports;

	/* ... and add them to the list */
	endpoपूर्णांक_descriptor_index = i;
	midi_function[i++] = (काष्ठा usb_descriptor_header *) &bulk_out_desc;
	midi_function[i++] = (काष्ठा usb_descriptor_header *) &ms_out_desc;
	midi_function[i++] = (काष्ठा usb_descriptor_header *) &bulk_in_desc;
	midi_function[i++] = (काष्ठा usb_descriptor_header *) &ms_in_desc;
	midi_function[i++] = शून्य;

	/*
	 * support all relevant hardware speeds... we expect that when
	 * hardware is dual speed, all bulk-capable endpoपूर्णांकs work at
	 * both speeds
	 */
	/* copy descriptors, and track endpoपूर्णांक copies */
	f->fs_descriptors = usb_copy_descriptors(midi_function);
	अगर (!f->fs_descriptors)
		जाओ fail_f_midi;

	अगर (gadget_is_dualspeed(c->cdev->gadget)) अणु
		bulk_in_desc.wMaxPacketSize = cpu_to_le16(512);
		bulk_out_desc.wMaxPacketSize = cpu_to_le16(512);
		f->hs_descriptors = usb_copy_descriptors(midi_function);
		अगर (!f->hs_descriptors)
			जाओ fail_f_midi;
	पूर्ण

	अगर (gadget_is_superspeed(c->cdev->gadget)) अणु
		bulk_in_desc.wMaxPacketSize = cpu_to_le16(1024);
		bulk_out_desc.wMaxPacketSize = cpu_to_le16(1024);
		i = endpoपूर्णांक_descriptor_index;
		midi_function[i++] = (काष्ठा usb_descriptor_header *)
				     &bulk_out_desc;
		midi_function[i++] = (काष्ठा usb_descriptor_header *)
				     &bulk_out_ss_comp_desc;
		midi_function[i++] = (काष्ठा usb_descriptor_header *)
				     &ms_out_desc;
		midi_function[i++] = (काष्ठा usb_descriptor_header *)
				     &bulk_in_desc;
		midi_function[i++] = (काष्ठा usb_descriptor_header *)
				     &bulk_in_ss_comp_desc;
		midi_function[i++] = (काष्ठा usb_descriptor_header *)
				     &ms_in_desc;
		f->ss_descriptors = usb_copy_descriptors(midi_function);
		अगर (!f->ss_descriptors)
			जाओ fail_f_midi;

		अगर (gadget_is_superspeed_plus(c->cdev->gadget)) अणु
			f->ssp_descriptors = usb_copy_descriptors(midi_function);
			अगर (!f->ssp_descriptors)
				जाओ fail_f_midi;
		पूर्ण
	पूर्ण

	kमुक्त(midi_function);

	वापस 0;

fail_f_midi:
	kमुक्त(midi_function);
	usb_मुक्त_all_descriptors(f);
fail:
	f_midi_unरेजिस्टर_card(midi);
fail_रेजिस्टर:
	ERROR(cdev, "%s: can't bind, err %d\n", f->name, status);

	वापस status;
पूर्ण

अटल अंतरभूत काष्ठा f_midi_opts *to_f_midi_opts(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा f_midi_opts,
			    func_inst.group);
पूर्ण

अटल व्योम midi_attr_release(काष्ठा config_item *item)
अणु
	काष्ठा f_midi_opts *opts = to_f_midi_opts(item);

	usb_put_function_instance(&opts->func_inst);
पूर्ण

अटल काष्ठा configfs_item_operations midi_item_ops = अणु
	.release	= midi_attr_release,
पूर्ण;

#घोषणा F_MIDI_OPT(name, test_limit, limit)				\
अटल sमाप_प्रकार f_midi_opts_##name##_show(काष्ठा config_item *item, अक्षर *page) \
अणु									\
	काष्ठा f_midi_opts *opts = to_f_midi_opts(item);		\
	पूर्णांक result;							\
									\
	mutex_lock(&opts->lock);					\
	result = प्र_लिखो(page, "%d\n", opts->name);			\
	mutex_unlock(&opts->lock);					\
									\
	वापस result;							\
पूर्ण									\
									\
अटल sमाप_प्रकार f_midi_opts_##name##_store(काष्ठा config_item *item,	\
					 स्थिर अक्षर *page, माप_प्रकार len)	\
अणु									\
	काष्ठा f_midi_opts *opts = to_f_midi_opts(item);		\
	पूर्णांक ret;							\
	u32 num;							\
									\
	mutex_lock(&opts->lock);					\
	अगर (opts->refcnt > 1) अणु						\
		ret = -EBUSY;						\
		जाओ end;						\
	पूर्ण								\
									\
	ret = kstrtou32(page, 0, &num);					\
	अगर (ret)							\
		जाओ end;						\
									\
	अगर (test_limit && num > limit) अणु				\
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
CONFIGFS_ATTR(f_midi_opts_, name);

F_MIDI_OPT(index, true, SNDRV_CARDS);
F_MIDI_OPT(buflen, false, 0);
F_MIDI_OPT(qlen, false, 0);
F_MIDI_OPT(in_ports, true, MAX_PORTS);
F_MIDI_OPT(out_ports, true, MAX_PORTS);

अटल sमाप_प्रकार f_midi_opts_id_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा f_midi_opts *opts = to_f_midi_opts(item);
	पूर्णांक result;

	mutex_lock(&opts->lock);
	अगर (opts->id) अणु
		result = strlcpy(page, opts->id, PAGE_SIZE);
	पूर्ण अन्यथा अणु
		page[0] = 0;
		result = 0;
	पूर्ण

	mutex_unlock(&opts->lock);

	वापस result;
पूर्ण

अटल sमाप_प्रकार f_midi_opts_id_store(काष्ठा config_item *item,
				    स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा f_midi_opts *opts = to_f_midi_opts(item);
	पूर्णांक ret;
	अक्षर *c;

	mutex_lock(&opts->lock);
	अगर (opts->refcnt > 1) अणु
		ret = -EBUSY;
		जाओ end;
	पूर्ण

	c = kstrndup(page, len, GFP_KERNEL);
	अगर (!c) अणु
		ret = -ENOMEM;
		जाओ end;
	पूर्ण
	अगर (opts->id_allocated)
		kमुक्त(opts->id);
	opts->id = c;
	opts->id_allocated = true;
	ret = len;
end:
	mutex_unlock(&opts->lock);
	वापस ret;
पूर्ण

CONFIGFS_ATTR(f_midi_opts_, id);

अटल काष्ठा configfs_attribute *midi_attrs[] = अणु
	&f_midi_opts_attr_index,
	&f_midi_opts_attr_buflen,
	&f_midi_opts_attr_qlen,
	&f_midi_opts_attr_in_ports,
	&f_midi_opts_attr_out_ports,
	&f_midi_opts_attr_id,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा config_item_type midi_func_type = अणु
	.ct_item_ops	= &midi_item_ops,
	.ct_attrs	= midi_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल व्योम f_midi_मुक्त_inst(काष्ठा usb_function_instance *f)
अणु
	काष्ठा f_midi_opts *opts;
	bool मुक्त = false;

	opts = container_of(f, काष्ठा f_midi_opts, func_inst);

	mutex_lock(&opts->lock);
	अगर (!--opts->refcnt) अणु
		मुक्त = true;
	पूर्ण
	mutex_unlock(&opts->lock);

	अगर (मुक्त) अणु
		अगर (opts->id_allocated)
			kमुक्त(opts->id);
		kमुक्त(opts);
	पूर्ण
पूर्ण

अटल काष्ठा usb_function_instance *f_midi_alloc_inst(व्योम)
अणु
	काष्ठा f_midi_opts *opts;

	opts = kzalloc(माप(*opts), GFP_KERNEL);
	अगर (!opts)
		वापस ERR_PTR(-ENOMEM);

	mutex_init(&opts->lock);
	opts->func_inst.मुक्त_func_inst = f_midi_मुक्त_inst;
	opts->index = SNDRV_DEFAULT_IDX1;
	opts->id = SNDRV_DEFAULT_STR1;
	opts->buflen = 512;
	opts->qlen = 32;
	opts->in_ports = 1;
	opts->out_ports = 1;
	opts->refcnt = 1;

	config_group_init_type_name(&opts->func_inst.group, "",
				    &midi_func_type);

	वापस &opts->func_inst;
पूर्ण

अटल व्योम f_midi_मुक्त(काष्ठा usb_function *f)
अणु
	काष्ठा f_midi *midi;
	काष्ठा f_midi_opts *opts;
	bool मुक्त = false;

	midi = func_to_midi(f);
	opts = container_of(f->fi, काष्ठा f_midi_opts, func_inst);
	mutex_lock(&opts->lock);
	अगर (!--midi->मुक्त_ref) अणु
		kमुक्त(midi->id);
		kfअगरo_मुक्त(&midi->in_req_fअगरo);
		kमुक्त(midi);
		मुक्त = true;
	पूर्ण
	mutex_unlock(&opts->lock);

	अगर (मुक्त)
		f_midi_मुक्त_inst(&opts->func_inst);
पूर्ण

अटल व्योम f_midi_rmidi_मुक्त(काष्ठा snd_rawmidi *rmidi)
अणु
	f_midi_मुक्त(rmidi->निजी_data);
पूर्ण

अटल व्योम f_midi_unbind(काष्ठा usb_configuration *c, काष्ठा usb_function *f)
अणु
	काष्ठा usb_composite_dev *cdev = f->config->cdev;
	काष्ठा f_midi *midi = func_to_midi(f);
	काष्ठा snd_card *card;

	DBG(cdev, "unbind\n");

	/* just to be sure */
	f_midi_disable(f);

	card = midi->card;
	midi->card = शून्य;
	अगर (card)
		snd_card_मुक्त_when_बंदd(card);

	usb_मुक्त_all_descriptors(f);
पूर्ण

अटल काष्ठा usb_function *f_midi_alloc(काष्ठा usb_function_instance *fi)
अणु
	काष्ठा f_midi *midi = शून्य;
	काष्ठा f_midi_opts *opts;
	पूर्णांक status, i;

	opts = container_of(fi, काष्ठा f_midi_opts, func_inst);

	mutex_lock(&opts->lock);
	/* sanity check */
	अगर (opts->in_ports > MAX_PORTS || opts->out_ports > MAX_PORTS) अणु
		status = -EINVAL;
		जाओ setup_fail;
	पूर्ण

	/* allocate and initialize one new instance */
	midi = kzalloc(काष्ठा_size(midi, in_ports_array, opts->in_ports),
		       GFP_KERNEL);
	अगर (!midi) अणु
		status = -ENOMEM;
		जाओ setup_fail;
	पूर्ण

	क्रम (i = 0; i < opts->in_ports; i++)
		midi->in_ports_array[i].cable = i;

	/* set up ALSA midi devices */
	midi->id = kstrdup(opts->id, GFP_KERNEL);
	अगर (opts->id && !midi->id) अणु
		status = -ENOMEM;
		जाओ midi_मुक्त;
	पूर्ण
	midi->in_ports = opts->in_ports;
	midi->out_ports = opts->out_ports;
	midi->index = opts->index;
	midi->buflen = opts->buflen;
	midi->qlen = opts->qlen;
	midi->in_last_port = 0;
	midi->मुक्त_ref = 1;

	status = kfअगरo_alloc(&midi->in_req_fअगरo, midi->qlen, GFP_KERNEL);
	अगर (status)
		जाओ midi_मुक्त;

	spin_lock_init(&midi->transmit_lock);

	++opts->refcnt;
	mutex_unlock(&opts->lock);

	midi->func.name		= "gmidi function";
	midi->func.bind		= f_midi_bind;
	midi->func.unbind	= f_midi_unbind;
	midi->func.set_alt	= f_midi_set_alt;
	midi->func.disable	= f_midi_disable;
	midi->func.मुक्त_func	= f_midi_मुक्त;

	वापस &midi->func;

midi_मुक्त:
	अगर (midi)
		kमुक्त(midi->id);
	kमुक्त(midi);
setup_fail:
	mutex_unlock(&opts->lock);

	वापस ERR_PTR(status);
पूर्ण

DECLARE_USB_FUNCTION_INIT(midi, f_midi_alloc_inst, f_midi_alloc);
