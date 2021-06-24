<शैली गुरु>
/*
 * usbmidi.c - ALSA USB MIDI driver
 *
 * Copyright (c) 2002-2009 Clemens Ladisch
 * All rights reserved.
 *
 * Based on the OSS usb-midi driver by NAGANO Daisuke,
 *          NetBSD's umidi driver by Takuya SHIOZAKI,
 *          the "USB Device Class Definition for MIDI Devices" by Roland
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. The name of the author may not be used to enकरोrse or promote products
 *    derived from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed and/or modअगरied under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR
 * ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/bitops.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयr.h>
#समावेश <linux/usb.h>
#समावेश <linux/रुको.h>
#समावेश <linux/usb/audपन.स>
#समावेश <linux/usb/midi.h>
#समावेश <linux/module.h>

#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/rawmidi.h>
#समावेश <sound/asequencer.h>
#समावेश "usbaudio.h"
#समावेश "midi.h"
#समावेश "power.h"
#समावेश "helper.h"

/*
 * define this to log all USB packets
 */
/* #घोषणा DUMP_PACKETS */

/*
 * how दीर्घ to रुको after some USB errors, so that hub_wq can disconnect() us
 * without too many spurious errors
 */
#घोषणा ERROR_DELAY_JIFFIES (HZ / 10)

#घोषणा OUTPUT_URBS 7
#घोषणा INPUT_URBS 7


MODULE_AUTHOR("Clemens Ladisch <clemens@ladisch.de>");
MODULE_DESCRIPTION("USB Audio/MIDI helper module");
MODULE_LICENSE("Dual BSD/GPL");

काष्ठा snd_usb_midi_in_endpoपूर्णांक;
काष्ठा snd_usb_midi_out_endpoपूर्णांक;
काष्ठा snd_usb_midi_endpoपूर्णांक;

काष्ठा usb_protocol_ops अणु
	व्योम (*input)(काष्ठा snd_usb_midi_in_endpoपूर्णांक*, uपूर्णांक8_t*, पूर्णांक);
	व्योम (*output)(काष्ठा snd_usb_midi_out_endpoपूर्णांक *ep, काष्ठा urb *urb);
	व्योम (*output_packet)(काष्ठा urb*, uपूर्णांक8_t, uपूर्णांक8_t, uपूर्णांक8_t, uपूर्णांक8_t);
	व्योम (*init_out_endpoपूर्णांक)(काष्ठा snd_usb_midi_out_endpoपूर्णांक *);
	व्योम (*finish_out_endpoपूर्णांक)(काष्ठा snd_usb_midi_out_endpoपूर्णांक *);
पूर्ण;

काष्ठा snd_usb_midi अणु
	काष्ठा usb_device *dev;
	काष्ठा snd_card *card;
	काष्ठा usb_पूर्णांकerface *अगरace;
	स्थिर काष्ठा snd_usb_audio_quirk *quirk;
	काष्ठा snd_rawmidi *rmidi;
	स्थिर काष्ठा usb_protocol_ops *usb_protocol_ops;
	काष्ठा list_head list;
	काष्ठा समयr_list error_समयr;
	spinlock_t disc_lock;
	काष्ठा rw_semaphore disc_rwsem;
	काष्ठा mutex mutex;
	u32 usb_id;
	पूर्णांक next_midi_device;

	काष्ठा snd_usb_midi_endpoपूर्णांक अणु
		काष्ठा snd_usb_midi_out_endpoपूर्णांक *out;
		काष्ठा snd_usb_midi_in_endpoपूर्णांक *in;
	पूर्ण endpoपूर्णांकs[MIDI_MAX_ENDPOINTS];
	अचिन्हित दीर्घ input_triggered;
	अचिन्हित पूर्णांक खोलोed[2];
	अचिन्हित अक्षर disconnected;
	अचिन्हित अक्षर input_running;

	काष्ठा snd_kcontrol *roland_load_ctl;
पूर्ण;

काष्ठा snd_usb_midi_out_endpoपूर्णांक अणु
	काष्ठा snd_usb_midi *umidi;
	काष्ठा out_urb_context अणु
		काष्ठा urb *urb;
		काष्ठा snd_usb_midi_out_endpoपूर्णांक *ep;
	पूर्ण urbs[OUTPUT_URBS];
	अचिन्हित पूर्णांक active_urbs;
	अचिन्हित पूर्णांक drain_urbs;
	पूर्णांक max_transfer;		/* size of urb buffer */
	काष्ठा work_काष्ठा work;
	अचिन्हित पूर्णांक next_urb;
	spinlock_t buffer_lock;

	काष्ठा usbmidi_out_port अणु
		काष्ठा snd_usb_midi_out_endpoपूर्णांक *ep;
		काष्ठा snd_rawmidi_substream *substream;
		पूर्णांक active;
		uपूर्णांक8_t cable;		/* cable number << 4 */
		uपूर्णांक8_t state;
#घोषणा STATE_UNKNOWN	0
#घोषणा STATE_1PARAM	1
#घोषणा STATE_2PARAM_1	2
#घोषणा STATE_2PARAM_2	3
#घोषणा STATE_SYSEX_0	4
#घोषणा STATE_SYSEX_1	5
#घोषणा STATE_SYSEX_2	6
		uपूर्णांक8_t data[2];
	पूर्ण ports[0x10];
	पूर्णांक current_port;

	रुको_queue_head_t drain_रुको;
पूर्ण;

काष्ठा snd_usb_midi_in_endpoपूर्णांक अणु
	काष्ठा snd_usb_midi *umidi;
	काष्ठा urb *urbs[INPUT_URBS];
	काष्ठा usbmidi_in_port अणु
		काष्ठा snd_rawmidi_substream *substream;
		u8 running_status_length;
	पूर्ण ports[0x10];
	u8 seen_f5;
	bool in_sysex;
	u8 last_cin;
	u8 error_resubmit;
	पूर्णांक current_port;
पूर्ण;

अटल व्योम snd_usbmidi_करो_output(काष्ठा snd_usb_midi_out_endpoपूर्णांक *ep);

अटल स्थिर uपूर्णांक8_t snd_usbmidi_cin_length[] = अणु
	0, 0, 2, 3, 3, 1, 2, 3, 3, 3, 3, 3, 2, 2, 3, 1
पूर्ण;

/*
 * Submits the URB, with error handling.
 */
अटल पूर्णांक snd_usbmidi_submit_urb(काष्ठा urb *urb, gfp_t flags)
अणु
	पूर्णांक err = usb_submit_urb(urb, flags);
	अगर (err < 0 && err != -ENODEV)
		dev_err(&urb->dev->dev, "usb_submit_urb: %d\n", err);
	वापस err;
पूर्ण

/*
 * Error handling क्रम URB completion functions.
 */
अटल पूर्णांक snd_usbmidi_urb_error(स्थिर काष्ठा urb *urb)
अणु
	चयन (urb->status) अणु
	/* manually unlinked, or device gone */
	हाल -ENOENT:
	हाल -ECONNRESET:
	हाल -ESHUTDOWN:
	हाल -ENODEV:
		वापस -ENODEV;
	/* errors that might occur during unplugging */
	हाल -EPROTO:
	हाल -ETIME:
	हाल -EILSEQ:
		वापस -EIO;
	शेष:
		dev_err(&urb->dev->dev, "urb status %d\n", urb->status);
		वापस 0; /* जारी */
	पूर्ण
पूर्ण

/*
 * Receives a chunk of MIDI data.
 */
अटल व्योम snd_usbmidi_input_data(काष्ठा snd_usb_midi_in_endpoपूर्णांक *ep,
				   पूर्णांक portidx, uपूर्णांक8_t *data, पूर्णांक length)
अणु
	काष्ठा usbmidi_in_port *port = &ep->ports[portidx];

	अगर (!port->substream) अणु
		dev_dbg(&ep->umidi->dev->dev, "unexpected port %d!\n", portidx);
		वापस;
	पूर्ण
	अगर (!test_bit(port->substream->number, &ep->umidi->input_triggered))
		वापस;
	snd_rawmidi_receive(port->substream, data, length);
पूर्ण

#अगर_घोषित DUMP_PACKETS
अटल व्योम dump_urb(स्थिर अक्षर *type, स्थिर u8 *data, पूर्णांक length)
अणु
	snd_prपूर्णांकk(KERN_DEBUG "%s packet: [", type);
	क्रम (; length > 0; ++data, --length)
		prपूर्णांकk(KERN_CONT " %02x", *data);
	prपूर्णांकk(KERN_CONT " ]\n");
पूर्ण
#अन्यथा
#घोषणा dump_urb(type, data, length) /* nothing */
#पूर्ण_अगर

/*
 * Processes the data पढ़ो from the device.
 */
अटल व्योम snd_usbmidi_in_urb_complete(काष्ठा urb *urb)
अणु
	काष्ठा snd_usb_midi_in_endpoपूर्णांक *ep = urb->context;

	अगर (urb->status == 0) अणु
		dump_urb("received", urb->transfer_buffer, urb->actual_length);
		ep->umidi->usb_protocol_ops->input(ep, urb->transfer_buffer,
						   urb->actual_length);
	पूर्ण अन्यथा अणु
		पूर्णांक err = snd_usbmidi_urb_error(urb);
		अगर (err < 0) अणु
			अगर (err != -ENODEV) अणु
				ep->error_resubmit = 1;
				mod_समयr(&ep->umidi->error_समयr,
					  jअगरfies + ERROR_DELAY_JIFFIES);
			पूर्ण
			वापस;
		पूर्ण
	पूर्ण

	urb->dev = ep->umidi->dev;
	snd_usbmidi_submit_urb(urb, GFP_ATOMIC);
पूर्ण

अटल व्योम snd_usbmidi_out_urb_complete(काष्ठा urb *urb)
अणु
	काष्ठा out_urb_context *context = urb->context;
	काष्ठा snd_usb_midi_out_endpoपूर्णांक *ep = context->ep;
	अचिन्हित पूर्णांक urb_index;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ep->buffer_lock, flags);
	urb_index = context - ep->urbs;
	ep->active_urbs &= ~(1 << urb_index);
	अगर (unlikely(ep->drain_urbs)) अणु
		ep->drain_urbs &= ~(1 << urb_index);
		wake_up(&ep->drain_रुको);
	पूर्ण
	spin_unlock_irqrestore(&ep->buffer_lock, flags);
	अगर (urb->status < 0) अणु
		पूर्णांक err = snd_usbmidi_urb_error(urb);
		अगर (err < 0) अणु
			अगर (err != -ENODEV)
				mod_समयr(&ep->umidi->error_समयr,
					  jअगरfies + ERROR_DELAY_JIFFIES);
			वापस;
		पूर्ण
	पूर्ण
	snd_usbmidi_करो_output(ep);
पूर्ण

/*
 * This is called when some data should be transferred to the device
 * (from one or more substreams).
 */
अटल व्योम snd_usbmidi_करो_output(काष्ठा snd_usb_midi_out_endpoपूर्णांक *ep)
अणु
	अचिन्हित पूर्णांक urb_index;
	काष्ठा urb *urb;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ep->buffer_lock, flags);
	अगर (ep->umidi->disconnected) अणु
		spin_unlock_irqrestore(&ep->buffer_lock, flags);
		वापस;
	पूर्ण

	urb_index = ep->next_urb;
	क्रम (;;) अणु
		अगर (!(ep->active_urbs & (1 << urb_index))) अणु
			urb = ep->urbs[urb_index].urb;
			urb->transfer_buffer_length = 0;
			ep->umidi->usb_protocol_ops->output(ep, urb);
			अगर (urb->transfer_buffer_length == 0)
				अवरोध;

			dump_urb("sending", urb->transfer_buffer,
				 urb->transfer_buffer_length);
			urb->dev = ep->umidi->dev;
			अगर (snd_usbmidi_submit_urb(urb, GFP_ATOMIC) < 0)
				अवरोध;
			ep->active_urbs |= 1 << urb_index;
		पूर्ण
		अगर (++urb_index >= OUTPUT_URBS)
			urb_index = 0;
		अगर (urb_index == ep->next_urb)
			अवरोध;
	पूर्ण
	ep->next_urb = urb_index;
	spin_unlock_irqrestore(&ep->buffer_lock, flags);
पूर्ण

अटल व्योम snd_usbmidi_out_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा snd_usb_midi_out_endpoपूर्णांक *ep =
		container_of(work, काष्ठा snd_usb_midi_out_endpoपूर्णांक, work);

	snd_usbmidi_करो_output(ep);
पूर्ण

/* called after transfers had been पूर्णांकerrupted due to some USB error */
अटल व्योम snd_usbmidi_error_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा snd_usb_midi *umidi = from_समयr(umidi, t, error_समयr);
	अचिन्हित पूर्णांक i, j;

	spin_lock(&umidi->disc_lock);
	अगर (umidi->disconnected) अणु
		spin_unlock(&umidi->disc_lock);
		वापस;
	पूर्ण
	क्रम (i = 0; i < MIDI_MAX_ENDPOINTS; ++i) अणु
		काष्ठा snd_usb_midi_in_endpoपूर्णांक *in = umidi->endpoपूर्णांकs[i].in;
		अगर (in && in->error_resubmit) अणु
			in->error_resubmit = 0;
			क्रम (j = 0; j < INPUT_URBS; ++j) अणु
				अगर (atomic_पढ़ो(&in->urbs[j]->use_count))
					जारी;
				in->urbs[j]->dev = umidi->dev;
				snd_usbmidi_submit_urb(in->urbs[j], GFP_ATOMIC);
			पूर्ण
		पूर्ण
		अगर (umidi->endpoपूर्णांकs[i].out)
			snd_usbmidi_करो_output(umidi->endpoपूर्णांकs[i].out);
	पूर्ण
	spin_unlock(&umidi->disc_lock);
पूर्ण

/* helper function to send अटल data that may not DMA-able */
अटल पूर्णांक send_bulk_अटल_data(काष्ठा snd_usb_midi_out_endpoपूर्णांक *ep,
				 स्थिर व्योम *data, पूर्णांक len)
अणु
	पूर्णांक err = 0;
	व्योम *buf = kmemdup(data, len, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;
	dump_urb("sending", buf, len);
	अगर (ep->urbs[0].urb)
		err = usb_bulk_msg(ep->umidi->dev, ep->urbs[0].urb->pipe,
				   buf, len, शून्य, 250);
	kमुक्त(buf);
	वापस err;
पूर्ण

/*
 * Standard USB MIDI protocol: see the spec.
 * Midiman protocol: like the standard protocol, but the control byte is the
 * fourth byte in each packet, and uses length instead of CIN.
 */

अटल व्योम snd_usbmidi_standard_input(काष्ठा snd_usb_midi_in_endpoपूर्णांक *ep,
				       uपूर्णांक8_t *buffer, पूर्णांक buffer_length)
अणु
	पूर्णांक i;

	क्रम (i = 0; i + 3 < buffer_length; i += 4)
		अगर (buffer[i] != 0) अणु
			पूर्णांक cable = buffer[i] >> 4;
			पूर्णांक length = snd_usbmidi_cin_length[buffer[i] & 0x0f];
			snd_usbmidi_input_data(ep, cable, &buffer[i + 1],
					       length);
		पूर्ण
पूर्ण

अटल व्योम snd_usbmidi_midiman_input(काष्ठा snd_usb_midi_in_endpoपूर्णांक *ep,
				      uपूर्णांक8_t *buffer, पूर्णांक buffer_length)
अणु
	पूर्णांक i;

	क्रम (i = 0; i + 3 < buffer_length; i += 4)
		अगर (buffer[i + 3] != 0) अणु
			पूर्णांक port = buffer[i + 3] >> 4;
			पूर्णांक length = buffer[i + 3] & 3;
			snd_usbmidi_input_data(ep, port, &buffer[i], length);
		पूर्ण
पूर्ण

/*
 * Buggy M-Audio device: running status on input results in a packet that has
 * the data bytes but not the status byte and that is marked with CIN 4.
 */
अटल व्योम snd_usbmidi_maudio_broken_running_status_input(
					काष्ठा snd_usb_midi_in_endpoपूर्णांक *ep,
					uपूर्णांक8_t *buffer, पूर्णांक buffer_length)
अणु
	पूर्णांक i;

	क्रम (i = 0; i + 3 < buffer_length; i += 4)
		अगर (buffer[i] != 0) अणु
			पूर्णांक cable = buffer[i] >> 4;
			u8 cin = buffer[i] & 0x0f;
			काष्ठा usbmidi_in_port *port = &ep->ports[cable];
			पूर्णांक length;

			length = snd_usbmidi_cin_length[cin];
			अगर (cin == 0xf && buffer[i + 1] >= 0xf8)
				; /* realसमय msg: no running status change */
			अन्यथा अगर (cin >= 0x8 && cin <= 0xe)
				/* channel msg */
				port->running_status_length = length - 1;
			अन्यथा अगर (cin == 0x4 &&
				 port->running_status_length != 0 &&
				 buffer[i + 1] < 0x80)
				/* CIN 4 that is not a SysEx */
				length = port->running_status_length;
			अन्यथा
				/*
				 * All other msgs cannot begin running status.
				 * (A channel msg sent as two or three CIN 0xF
				 * packets could in theory, but this device
				 * करोesn't use this क्रमmat.)
				 */
				port->running_status_length = 0;
			snd_usbmidi_input_data(ep, cable, &buffer[i + 1],
					       length);
		पूर्ण
पूर्ण

/*
 * QinHeng CH345 is buggy: every second packet inside a SysEx has not CIN 4
 * but the previously seen CIN, but still with three data bytes.
 */
अटल व्योम ch345_broken_sysex_input(काष्ठा snd_usb_midi_in_endpoपूर्णांक *ep,
				     uपूर्णांक8_t *buffer, पूर्णांक buffer_length)
अणु
	अचिन्हित पूर्णांक i, cin, length;

	क्रम (i = 0; i + 3 < buffer_length; i += 4) अणु
		अगर (buffer[i] == 0 && i > 0)
			अवरोध;
		cin = buffer[i] & 0x0f;
		अगर (ep->in_sysex &&
		    cin == ep->last_cin &&
		    (buffer[i + 1 + (cin == 0x6)] & 0x80) == 0)
			cin = 0x4;
#अगर 0
		अगर (buffer[i + 1] == 0x90) अणु
			/*
			 * Either a corrupted running status or a real note-on
			 * message; impossible to detect reliably.
			 */
		पूर्ण
#पूर्ण_अगर
		length = snd_usbmidi_cin_length[cin];
		snd_usbmidi_input_data(ep, 0, &buffer[i + 1], length);
		ep->in_sysex = cin == 0x4;
		अगर (!ep->in_sysex)
			ep->last_cin = cin;
	पूर्ण
पूर्ण

/*
 * CME protocol: like the standard protocol, but SysEx commands are sent as a
 * single USB packet preceded by a 0x0F byte.
 */
अटल व्योम snd_usbmidi_cme_input(काष्ठा snd_usb_midi_in_endpoपूर्णांक *ep,
				  uपूर्णांक8_t *buffer, पूर्णांक buffer_length)
अणु
	अगर (buffer_length < 2 || (buffer[0] & 0x0f) != 0x0f)
		snd_usbmidi_standard_input(ep, buffer, buffer_length);
	अन्यथा
		snd_usbmidi_input_data(ep, buffer[0] >> 4,
				       &buffer[1], buffer_length - 1);
पूर्ण

/*
 * Adds one USB MIDI packet to the output buffer.
 */
अटल व्योम snd_usbmidi_output_standard_packet(काष्ठा urb *urb, uपूर्णांक8_t p0,
					       uपूर्णांक8_t p1, uपूर्णांक8_t p2,
					       uपूर्णांक8_t p3)
अणु

	uपूर्णांक8_t *buf =
		(uपूर्णांक8_t *)urb->transfer_buffer + urb->transfer_buffer_length;
	buf[0] = p0;
	buf[1] = p1;
	buf[2] = p2;
	buf[3] = p3;
	urb->transfer_buffer_length += 4;
पूर्ण

/*
 * Adds one Midiman packet to the output buffer.
 */
अटल व्योम snd_usbmidi_output_midiman_packet(काष्ठा urb *urb, uपूर्णांक8_t p0,
					      uपूर्णांक8_t p1, uपूर्णांक8_t p2,
					      uपूर्णांक8_t p3)
अणु

	uपूर्णांक8_t *buf =
		(uपूर्णांक8_t *)urb->transfer_buffer + urb->transfer_buffer_length;
	buf[0] = p1;
	buf[1] = p2;
	buf[2] = p3;
	buf[3] = (p0 & 0xf0) | snd_usbmidi_cin_length[p0 & 0x0f];
	urb->transfer_buffer_length += 4;
पूर्ण

/*
 * Converts MIDI commands to USB MIDI packets.
 */
अटल व्योम snd_usbmidi_transmit_byte(काष्ठा usbmidi_out_port *port,
				      uपूर्णांक8_t b, काष्ठा urb *urb)
अणु
	uपूर्णांक8_t p0 = port->cable;
	व्योम (*output_packet)(काष्ठा urb*, uपूर्णांक8_t, uपूर्णांक8_t, uपूर्णांक8_t, uपूर्णांक8_t) =
		port->ep->umidi->usb_protocol_ops->output_packet;

	अगर (b >= 0xf8) अणु
		output_packet(urb, p0 | 0x0f, b, 0, 0);
	पूर्ण अन्यथा अगर (b >= 0xf0) अणु
		चयन (b) अणु
		हाल 0xf0:
			port->data[0] = b;
			port->state = STATE_SYSEX_1;
			अवरोध;
		हाल 0xf1:
		हाल 0xf3:
			port->data[0] = b;
			port->state = STATE_1PARAM;
			अवरोध;
		हाल 0xf2:
			port->data[0] = b;
			port->state = STATE_2PARAM_1;
			अवरोध;
		हाल 0xf4:
		हाल 0xf5:
			port->state = STATE_UNKNOWN;
			अवरोध;
		हाल 0xf6:
			output_packet(urb, p0 | 0x05, 0xf6, 0, 0);
			port->state = STATE_UNKNOWN;
			अवरोध;
		हाल 0xf7:
			चयन (port->state) अणु
			हाल STATE_SYSEX_0:
				output_packet(urb, p0 | 0x05, 0xf7, 0, 0);
				अवरोध;
			हाल STATE_SYSEX_1:
				output_packet(urb, p0 | 0x06, port->data[0],
					      0xf7, 0);
				अवरोध;
			हाल STATE_SYSEX_2:
				output_packet(urb, p0 | 0x07, port->data[0],
					      port->data[1], 0xf7);
				अवरोध;
			पूर्ण
			port->state = STATE_UNKNOWN;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (b >= 0x80) अणु
		port->data[0] = b;
		अगर (b >= 0xc0 && b <= 0xdf)
			port->state = STATE_1PARAM;
		अन्यथा
			port->state = STATE_2PARAM_1;
	पूर्ण अन्यथा अणु /* b < 0x80 */
		चयन (port->state) अणु
		हाल STATE_1PARAM:
			अगर (port->data[0] < 0xf0) अणु
				p0 |= port->data[0] >> 4;
			पूर्ण अन्यथा अणु
				p0 |= 0x02;
				port->state = STATE_UNKNOWN;
			पूर्ण
			output_packet(urb, p0, port->data[0], b, 0);
			अवरोध;
		हाल STATE_2PARAM_1:
			port->data[1] = b;
			port->state = STATE_2PARAM_2;
			अवरोध;
		हाल STATE_2PARAM_2:
			अगर (port->data[0] < 0xf0) अणु
				p0 |= port->data[0] >> 4;
				port->state = STATE_2PARAM_1;
			पूर्ण अन्यथा अणु
				p0 |= 0x03;
				port->state = STATE_UNKNOWN;
			पूर्ण
			output_packet(urb, p0, port->data[0], port->data[1], b);
			अवरोध;
		हाल STATE_SYSEX_0:
			port->data[0] = b;
			port->state = STATE_SYSEX_1;
			अवरोध;
		हाल STATE_SYSEX_1:
			port->data[1] = b;
			port->state = STATE_SYSEX_2;
			अवरोध;
		हाल STATE_SYSEX_2:
			output_packet(urb, p0 | 0x04, port->data[0],
				      port->data[1], b);
			port->state = STATE_SYSEX_0;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम snd_usbmidi_standard_output(काष्ठा snd_usb_midi_out_endpoपूर्णांक *ep,
					काष्ठा urb *urb)
अणु
	पूर्णांक p;

	/* FIXME: lower-numbered ports can starve higher-numbered ports */
	क्रम (p = 0; p < 0x10; ++p) अणु
		काष्ठा usbmidi_out_port *port = &ep->ports[p];
		अगर (!port->active)
			जारी;
		जबतक (urb->transfer_buffer_length + 3 < ep->max_transfer) अणु
			uपूर्णांक8_t b;
			अगर (snd_rawmidi_transmit(port->substream, &b, 1) != 1) अणु
				port->active = 0;
				अवरोध;
			पूर्ण
			snd_usbmidi_transmit_byte(port, b, urb);
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा usb_protocol_ops snd_usbmidi_standard_ops = अणु
	.input = snd_usbmidi_standard_input,
	.output = snd_usbmidi_standard_output,
	.output_packet = snd_usbmidi_output_standard_packet,
पूर्ण;

अटल स्थिर काष्ठा usb_protocol_ops snd_usbmidi_midiman_ops = अणु
	.input = snd_usbmidi_midiman_input,
	.output = snd_usbmidi_standard_output,
	.output_packet = snd_usbmidi_output_midiman_packet,
पूर्ण;

अटल स्थिर
काष्ठा usb_protocol_ops snd_usbmidi_maudio_broken_running_status_ops = अणु
	.input = snd_usbmidi_maudio_broken_running_status_input,
	.output = snd_usbmidi_standard_output,
	.output_packet = snd_usbmidi_output_standard_packet,
पूर्ण;

अटल स्थिर काष्ठा usb_protocol_ops snd_usbmidi_cme_ops = अणु
	.input = snd_usbmidi_cme_input,
	.output = snd_usbmidi_standard_output,
	.output_packet = snd_usbmidi_output_standard_packet,
पूर्ण;

अटल स्थिर काष्ठा usb_protocol_ops snd_usbmidi_ch345_broken_sysex_ops = अणु
	.input = ch345_broken_sysex_input,
	.output = snd_usbmidi_standard_output,
	.output_packet = snd_usbmidi_output_standard_packet,
पूर्ण;

/*
 * AKAI MPD16 protocol:
 *
 * For control port (endpoपूर्णांक 1):
 * ==============================
 * One or more chunks consisting of first byte of (0x10 | msg_len) and then a
 * SysEx message (msg_len=9 bytes दीर्घ).
 *
 * For data port (endpoपूर्णांक 2):
 * ===========================
 * One or more chunks consisting of first byte of (0x20 | msg_len) and then a
 * MIDI message (msg_len bytes दीर्घ)
 *
 * Messages sent: Active Sense, Note On, Poly Pressure, Control Change.
 */
अटल व्योम snd_usbmidi_akai_input(काष्ठा snd_usb_midi_in_endpoपूर्णांक *ep,
				   uपूर्णांक8_t *buffer, पूर्णांक buffer_length)
अणु
	अचिन्हित पूर्णांक pos = 0;
	अचिन्हित पूर्णांक len = (अचिन्हित पूर्णांक)buffer_length;
	जबतक (pos < len) अणु
		अचिन्हित पूर्णांक port = (buffer[pos] >> 4) - 1;
		अचिन्हित पूर्णांक msg_len = buffer[pos] & 0x0f;
		pos++;
		अगर (pos + msg_len <= len && port < 2)
			snd_usbmidi_input_data(ep, 0, &buffer[pos], msg_len);
		pos += msg_len;
	पूर्ण
पूर्ण

#घोषणा MAX_AKAI_SYSEX_LEN 9

अटल व्योम snd_usbmidi_akai_output(काष्ठा snd_usb_midi_out_endpoपूर्णांक *ep,
				    काष्ठा urb *urb)
अणु
	uपूर्णांक8_t *msg;
	पूर्णांक pos, end, count, buf_end;
	uपूर्णांक8_t पंचांगp[MAX_AKAI_SYSEX_LEN];
	काष्ठा snd_rawmidi_substream *substream = ep->ports[0].substream;

	अगर (!ep->ports[0].active)
		वापस;

	msg = urb->transfer_buffer + urb->transfer_buffer_length;
	buf_end = ep->max_transfer - MAX_AKAI_SYSEX_LEN - 1;

	/* only try adding more data when there's space क्रम at least 1 SysEx */
	जबतक (urb->transfer_buffer_length < buf_end) अणु
		count = snd_rawmidi_transmit_peek(substream,
						  पंचांगp, MAX_AKAI_SYSEX_LEN);
		अगर (!count) अणु
			ep->ports[0].active = 0;
			वापस;
		पूर्ण
		/* try to skip non-SysEx data */
		क्रम (pos = 0; pos < count && पंचांगp[pos] != 0xF0; pos++)
			;

		अगर (pos > 0) अणु
			snd_rawmidi_transmit_ack(substream, pos);
			जारी;
		पूर्ण

		/* look क्रम the start or end marker */
		क्रम (end = 1; end < count && पंचांगp[end] < 0xF0; end++)
			;

		/* next SysEx started beक्रमe the end of current one */
		अगर (end < count && पंचांगp[end] == 0xF0) अणु
			/* it's incomplete - drop it */
			snd_rawmidi_transmit_ack(substream, end);
			जारी;
		पूर्ण
		/* SysEx complete */
		अगर (end < count && पंचांगp[end] == 0xF7) अणु
			/* queue it, ack it, and get the next one */
			count = end + 1;
			msg[0] = 0x10 | count;
			स_नकल(&msg[1], पंचांगp, count);
			snd_rawmidi_transmit_ack(substream, count);
			urb->transfer_buffer_length += count + 1;
			msg += count + 1;
			जारी;
		पूर्ण
		/* less than 9 bytes and no end byte - रुको क्रम more */
		अगर (count < MAX_AKAI_SYSEX_LEN) अणु
			ep->ports[0].active = 0;
			वापस;
		पूर्ण
		/* 9 bytes and no end marker in sight - malक्रमmed, skip it */
		snd_rawmidi_transmit_ack(substream, count);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा usb_protocol_ops snd_usbmidi_akai_ops = अणु
	.input = snd_usbmidi_akai_input,
	.output = snd_usbmidi_akai_output,
पूर्ण;

/*
 * Novation USB MIDI protocol: number of data bytes is in the first byte
 * (when receiving) (+1!) or in the second byte (when sending); data begins
 * at the third byte.
 */

अटल व्योम snd_usbmidi_novation_input(काष्ठा snd_usb_midi_in_endpoपूर्णांक *ep,
				       uपूर्णांक8_t *buffer, पूर्णांक buffer_length)
अणु
	अगर (buffer_length < 2 || !buffer[0] || buffer_length < buffer[0] + 1)
		वापस;
	snd_usbmidi_input_data(ep, 0, &buffer[2], buffer[0] - 1);
पूर्ण

अटल व्योम snd_usbmidi_novation_output(काष्ठा snd_usb_midi_out_endpoपूर्णांक *ep,
					काष्ठा urb *urb)
अणु
	uपूर्णांक8_t *transfer_buffer;
	पूर्णांक count;

	अगर (!ep->ports[0].active)
		वापस;
	transfer_buffer = urb->transfer_buffer;
	count = snd_rawmidi_transmit(ep->ports[0].substream,
				     &transfer_buffer[2],
				     ep->max_transfer - 2);
	अगर (count < 1) अणु
		ep->ports[0].active = 0;
		वापस;
	पूर्ण
	transfer_buffer[0] = 0;
	transfer_buffer[1] = count;
	urb->transfer_buffer_length = 2 + count;
पूर्ण

अटल स्थिर काष्ठा usb_protocol_ops snd_usbmidi_novation_ops = अणु
	.input = snd_usbmidi_novation_input,
	.output = snd_usbmidi_novation_output,
पूर्ण;

/*
 * "raw" protocol: just move raw MIDI bytes from/to the endpoपूर्णांक
 */

अटल व्योम snd_usbmidi_raw_input(काष्ठा snd_usb_midi_in_endpoपूर्णांक *ep,
				  uपूर्णांक8_t *buffer, पूर्णांक buffer_length)
अणु
	snd_usbmidi_input_data(ep, 0, buffer, buffer_length);
पूर्ण

अटल व्योम snd_usbmidi_raw_output(काष्ठा snd_usb_midi_out_endpoपूर्णांक *ep,
				   काष्ठा urb *urb)
अणु
	पूर्णांक count;

	अगर (!ep->ports[0].active)
		वापस;
	count = snd_rawmidi_transmit(ep->ports[0].substream,
				     urb->transfer_buffer,
				     ep->max_transfer);
	अगर (count < 1) अणु
		ep->ports[0].active = 0;
		वापस;
	पूर्ण
	urb->transfer_buffer_length = count;
पूर्ण

अटल स्थिर काष्ठा usb_protocol_ops snd_usbmidi_raw_ops = अणु
	.input = snd_usbmidi_raw_input,
	.output = snd_usbmidi_raw_output,
पूर्ण;

/*
 * FTDI protocol: raw MIDI bytes, but input packets have two modem status bytes.
 */

अटल व्योम snd_usbmidi_ftdi_input(काष्ठा snd_usb_midi_in_endpoपूर्णांक *ep,
				   uपूर्णांक8_t *buffer, पूर्णांक buffer_length)
अणु
	अगर (buffer_length > 2)
		snd_usbmidi_input_data(ep, 0, buffer + 2, buffer_length - 2);
पूर्ण

अटल स्थिर काष्ठा usb_protocol_ops snd_usbmidi_ftdi_ops = अणु
	.input = snd_usbmidi_ftdi_input,
	.output = snd_usbmidi_raw_output,
पूर्ण;

अटल व्योम snd_usbmidi_us122l_input(काष्ठा snd_usb_midi_in_endpoपूर्णांक *ep,
				     uपूर्णांक8_t *buffer, पूर्णांक buffer_length)
अणु
	अगर (buffer_length != 9)
		वापस;
	buffer_length = 8;
	जबतक (buffer_length && buffer[buffer_length - 1] == 0xFD)
		buffer_length--;
	अगर (buffer_length)
		snd_usbmidi_input_data(ep, 0, buffer, buffer_length);
पूर्ण

अटल व्योम snd_usbmidi_us122l_output(काष्ठा snd_usb_midi_out_endpoपूर्णांक *ep,
				      काष्ठा urb *urb)
अणु
	पूर्णांक count;

	अगर (!ep->ports[0].active)
		वापस;
	चयन (snd_usb_get_speed(ep->umidi->dev)) अणु
	हाल USB_SPEED_HIGH:
	हाल USB_SPEED_SUPER:
	हाल USB_SPEED_SUPER_PLUS:
		count = 1;
		अवरोध;
	शेष:
		count = 2;
	पूर्ण
	count = snd_rawmidi_transmit(ep->ports[0].substream,
				     urb->transfer_buffer,
				     count);
	अगर (count < 1) अणु
		ep->ports[0].active = 0;
		वापस;
	पूर्ण

	स_रखो(urb->transfer_buffer + count, 0xFD, ep->max_transfer - count);
	urb->transfer_buffer_length = ep->max_transfer;
पूर्ण

अटल स्थिर काष्ठा usb_protocol_ops snd_usbmidi_122l_ops = अणु
	.input = snd_usbmidi_us122l_input,
	.output = snd_usbmidi_us122l_output,
पूर्ण;

/*
 * Emagic USB MIDI protocol: raw MIDI with "F5 xx" port चयनing.
 */

अटल व्योम snd_usbmidi_emagic_init_out(काष्ठा snd_usb_midi_out_endpoपूर्णांक *ep)
अणु
	अटल स्थिर u8 init_data[] = अणु
		/* initialization magic: "get version" */
		0xf0,
		0x00, 0x20, 0x31,	/* Emagic */
		0x64,			/* Unitor8 */
		0x0b,			/* version number request */
		0x00,			/* command version */
		0x00,			/* EEPROM, box 0 */
		0xf7
	पूर्ण;
	send_bulk_अटल_data(ep, init_data, माप(init_data));
	/* जबतक we're at it, pour on more magic */
	send_bulk_अटल_data(ep, init_data, माप(init_data));
पूर्ण

अटल व्योम snd_usbmidi_emagic_finish_out(काष्ठा snd_usb_midi_out_endpoपूर्णांक *ep)
अणु
	अटल स्थिर u8 finish_data[] = अणु
		/* चयन to patch mode with last preset */
		0xf0,
		0x00, 0x20, 0x31,	/* Emagic */
		0x64,			/* Unitor8 */
		0x10,			/* patch चयन command */
		0x00,			/* command version */
		0x7f,			/* to all boxes */
		0x40,			/* last preset in EEPROM */
		0xf7
	पूर्ण;
	send_bulk_अटल_data(ep, finish_data, माप(finish_data));
पूर्ण

अटल व्योम snd_usbmidi_emagic_input(काष्ठा snd_usb_midi_in_endpoपूर्णांक *ep,
				     uपूर्णांक8_t *buffer, पूर्णांक buffer_length)
अणु
	पूर्णांक i;

	/* FF indicates end of valid data */
	क्रम (i = 0; i < buffer_length; ++i)
		अगर (buffer[i] == 0xff) अणु
			buffer_length = i;
			अवरोध;
		पूर्ण

	/* handle F5 at end of last buffer */
	अगर (ep->seen_f5)
		जाओ चयन_port;

	जबतक (buffer_length > 0) अणु
		/* determine size of data until next F5 */
		क्रम (i = 0; i < buffer_length; ++i)
			अगर (buffer[i] == 0xf5)
				अवरोध;
		snd_usbmidi_input_data(ep, ep->current_port, buffer, i);
		buffer += i;
		buffer_length -= i;

		अगर (buffer_length <= 0)
			अवरोध;
		/* निश्चित(buffer[0] == 0xf5); */
		ep->seen_f5 = 1;
		++buffer;
		--buffer_length;

	चयन_port:
		अगर (buffer_length <= 0)
			अवरोध;
		अगर (buffer[0] < 0x80) अणु
			ep->current_port = (buffer[0] - 1) & 15;
			++buffer;
			--buffer_length;
		पूर्ण
		ep->seen_f5 = 0;
	पूर्ण
पूर्ण

अटल व्योम snd_usbmidi_emagic_output(काष्ठा snd_usb_midi_out_endpoपूर्णांक *ep,
				      काष्ठा urb *urb)
अणु
	पूर्णांक port0 = ep->current_port;
	uपूर्णांक8_t *buf = urb->transfer_buffer;
	पूर्णांक buf_मुक्त = ep->max_transfer;
	पूर्णांक length, i;

	क्रम (i = 0; i < 0x10; ++i) अणु
		/* round-robin, starting at the last current port */
		पूर्णांक portnum = (port0 + i) & 15;
		काष्ठा usbmidi_out_port *port = &ep->ports[portnum];

		अगर (!port->active)
			जारी;
		अगर (snd_rawmidi_transmit_peek(port->substream, buf, 1) != 1) अणु
			port->active = 0;
			जारी;
		पूर्ण

		अगर (portnum != ep->current_port) अणु
			अगर (buf_मुक्त < 2)
				अवरोध;
			ep->current_port = portnum;
			buf[0] = 0xf5;
			buf[1] = (portnum + 1) & 15;
			buf += 2;
			buf_मुक्त -= 2;
		पूर्ण

		अगर (buf_मुक्त < 1)
			अवरोध;
		length = snd_rawmidi_transmit(port->substream, buf, buf_मुक्त);
		अगर (length > 0) अणु
			buf += length;
			buf_मुक्त -= length;
			अगर (buf_मुक्त < 1)
				अवरोध;
		पूर्ण
	पूर्ण
	अगर (buf_मुक्त < ep->max_transfer && buf_मुक्त > 0) अणु
		*buf = 0xff;
		--buf_मुक्त;
	पूर्ण
	urb->transfer_buffer_length = ep->max_transfer - buf_मुक्त;
पूर्ण

अटल स्थिर काष्ठा usb_protocol_ops snd_usbmidi_emagic_ops = अणु
	.input = snd_usbmidi_emagic_input,
	.output = snd_usbmidi_emagic_output,
	.init_out_endpoपूर्णांक = snd_usbmidi_emagic_init_out,
	.finish_out_endpoपूर्णांक = snd_usbmidi_emagic_finish_out,
पूर्ण;


अटल व्योम update_roland_altsetting(काष्ठा snd_usb_midi *umidi)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा usb_host_पूर्णांकerface *hostअगर;
	काष्ठा usb_पूर्णांकerface_descriptor *पूर्णांकfd;
	पूर्णांक is_light_load;

	पूर्णांकf = umidi->अगरace;
	is_light_load = पूर्णांकf->cur_altsetting != पूर्णांकf->altsetting;
	अगर (umidi->roland_load_ctl->निजी_value == is_light_load)
		वापस;
	hostअगर = &पूर्णांकf->altsetting[umidi->roland_load_ctl->निजी_value];
	पूर्णांकfd = get_अगरace_desc(hostअगर);
	snd_usbmidi_input_stop(&umidi->list);
	usb_set_पूर्णांकerface(umidi->dev, पूर्णांकfd->bInterfaceNumber,
			  पूर्णांकfd->bAlternateSetting);
	snd_usbmidi_input_start(&umidi->list);
पूर्ण

अटल पूर्णांक substream_खोलो(काष्ठा snd_rawmidi_substream *substream, पूर्णांक dir,
			  पूर्णांक खोलो)
अणु
	काष्ठा snd_usb_midi *umidi = substream->rmidi->निजी_data;
	काष्ठा snd_kcontrol *ctl;

	करोwn_पढ़ो(&umidi->disc_rwsem);
	अगर (umidi->disconnected) अणु
		up_पढ़ो(&umidi->disc_rwsem);
		वापस खोलो ? -ENODEV : 0;
	पूर्ण

	mutex_lock(&umidi->mutex);
	अगर (खोलो) अणु
		अगर (!umidi->खोलोed[0] && !umidi->खोलोed[1]) अणु
			अगर (umidi->roland_load_ctl) अणु
				ctl = umidi->roland_load_ctl;
				ctl->vd[0].access |=
					SNDRV_CTL_ELEM_ACCESS_INACTIVE;
				snd_ctl_notअगरy(umidi->card,
				       SNDRV_CTL_EVENT_MASK_INFO, &ctl->id);
				update_roland_altsetting(umidi);
			पूर्ण
		पूर्ण
		umidi->खोलोed[dir]++;
		अगर (umidi->खोलोed[1])
			snd_usbmidi_input_start(&umidi->list);
	पूर्ण अन्यथा अणु
		umidi->खोलोed[dir]--;
		अगर (!umidi->खोलोed[1])
			snd_usbmidi_input_stop(&umidi->list);
		अगर (!umidi->खोलोed[0] && !umidi->खोलोed[1]) अणु
			अगर (umidi->roland_load_ctl) अणु
				ctl = umidi->roland_load_ctl;
				ctl->vd[0].access &=
					~SNDRV_CTL_ELEM_ACCESS_INACTIVE;
				snd_ctl_notअगरy(umidi->card,
				       SNDRV_CTL_EVENT_MASK_INFO, &ctl->id);
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&umidi->mutex);
	up_पढ़ो(&umidi->disc_rwsem);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_usbmidi_output_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_usb_midi *umidi = substream->rmidi->निजी_data;
	काष्ठा usbmidi_out_port *port = शून्य;
	पूर्णांक i, j;

	क्रम (i = 0; i < MIDI_MAX_ENDPOINTS; ++i)
		अगर (umidi->endpoपूर्णांकs[i].out)
			क्रम (j = 0; j < 0x10; ++j)
				अगर (umidi->endpoपूर्णांकs[i].out->ports[j].substream == substream) अणु
					port = &umidi->endpoपूर्णांकs[i].out->ports[j];
					अवरोध;
				पूर्ण
	अगर (!port) अणु
		snd_BUG();
		वापस -ENXIO;
	पूर्ण

	substream->runसमय->निजी_data = port;
	port->state = STATE_UNKNOWN;
	वापस substream_खोलो(substream, 0, 1);
पूर्ण

अटल पूर्णांक snd_usbmidi_output_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	वापस substream_खोलो(substream, 0, 0);
पूर्ण

अटल व्योम snd_usbmidi_output_trigger(काष्ठा snd_rawmidi_substream *substream,
				       पूर्णांक up)
अणु
	काष्ठा usbmidi_out_port *port =
		(काष्ठा usbmidi_out_port *)substream->runसमय->निजी_data;

	port->active = up;
	अगर (up) अणु
		अगर (port->ep->umidi->disconnected) अणु
			/* gobble up reमुख्यing bytes to prevent रुको in
			 * snd_rawmidi_drain_output */
			snd_rawmidi_proceed(substream);
			वापस;
		पूर्ण
		queue_work(प्रणाली_highpri_wq, &port->ep->work);
	पूर्ण
पूर्ण

अटल व्योम snd_usbmidi_output_drain(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा usbmidi_out_port *port = substream->runसमय->निजी_data;
	काष्ठा snd_usb_midi_out_endpoपूर्णांक *ep = port->ep;
	अचिन्हित पूर्णांक drain_urbs;
	DEFINE_WAIT(रुको);
	दीर्घ समयout = msecs_to_jअगरfies(50);

	अगर (ep->umidi->disconnected)
		वापस;
	/*
	 * The substream buffer is empty, but some data might still be in the
	 * currently active URBs, so we have to रुको क्रम those to complete.
	 */
	spin_lock_irq(&ep->buffer_lock);
	drain_urbs = ep->active_urbs;
	अगर (drain_urbs) अणु
		ep->drain_urbs |= drain_urbs;
		करो अणु
			prepare_to_रुको(&ep->drain_रुको, &रुको,
					TASK_UNINTERRUPTIBLE);
			spin_unlock_irq(&ep->buffer_lock);
			समयout = schedule_समयout(समयout);
			spin_lock_irq(&ep->buffer_lock);
			drain_urbs &= ep->drain_urbs;
		पूर्ण जबतक (drain_urbs && समयout);
		finish_रुको(&ep->drain_रुको, &रुको);
	पूर्ण
	spin_unlock_irq(&ep->buffer_lock);
पूर्ण

अटल पूर्णांक snd_usbmidi_input_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	वापस substream_खोलो(substream, 1, 1);
पूर्ण

अटल पूर्णांक snd_usbmidi_input_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	वापस substream_खोलो(substream, 1, 0);
पूर्ण

अटल व्योम snd_usbmidi_input_trigger(काष्ठा snd_rawmidi_substream *substream,
				      पूर्णांक up)
अणु
	काष्ठा snd_usb_midi *umidi = substream->rmidi->निजी_data;

	अगर (up)
		set_bit(substream->number, &umidi->input_triggered);
	अन्यथा
		clear_bit(substream->number, &umidi->input_triggered);
पूर्ण

अटल स्थिर काष्ठा snd_rawmidi_ops snd_usbmidi_output_ops = अणु
	.खोलो = snd_usbmidi_output_खोलो,
	.बंद = snd_usbmidi_output_बंद,
	.trigger = snd_usbmidi_output_trigger,
	.drain = snd_usbmidi_output_drain,
पूर्ण;

अटल स्थिर काष्ठा snd_rawmidi_ops snd_usbmidi_input_ops = अणु
	.खोलो = snd_usbmidi_input_खोलो,
	.बंद = snd_usbmidi_input_बंद,
	.trigger = snd_usbmidi_input_trigger
पूर्ण;

अटल व्योम मुक्त_urb_and_buffer(काष्ठा snd_usb_midi *umidi, काष्ठा urb *urb,
				अचिन्हित पूर्णांक buffer_length)
अणु
	usb_मुक्त_coherent(umidi->dev, buffer_length,
			  urb->transfer_buffer, urb->transfer_dma);
	usb_मुक्त_urb(urb);
पूर्ण

/*
 * Frees an input endpoपूर्णांक.
 * May be called when ep hasn't been initialized completely.
 */
अटल व्योम snd_usbmidi_in_endpoपूर्णांक_delete(काष्ठा snd_usb_midi_in_endpoपूर्णांक *ep)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < INPUT_URBS; ++i)
		अगर (ep->urbs[i])
			मुक्त_urb_and_buffer(ep->umidi, ep->urbs[i],
					    ep->urbs[i]->transfer_buffer_length);
	kमुक्त(ep);
पूर्ण

/*
 * Creates an input endpoपूर्णांक.
 */
अटल पूर्णांक snd_usbmidi_in_endpoपूर्णांक_create(काष्ठा snd_usb_midi *umidi,
					  काष्ठा snd_usb_midi_endpoपूर्णांक_info *ep_info,
					  काष्ठा snd_usb_midi_endpoपूर्णांक *rep)
अणु
	काष्ठा snd_usb_midi_in_endpoपूर्णांक *ep;
	व्योम *buffer;
	अचिन्हित पूर्णांक pipe;
	पूर्णांक length;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	rep->in = शून्य;
	ep = kzalloc(माप(*ep), GFP_KERNEL);
	अगर (!ep)
		वापस -ENOMEM;
	ep->umidi = umidi;

	क्रम (i = 0; i < INPUT_URBS; ++i) अणु
		ep->urbs[i] = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!ep->urbs[i]) अणु
			err = -ENOMEM;
			जाओ error;
		पूर्ण
	पूर्ण
	अगर (ep_info->in_पूर्णांकerval)
		pipe = usb_rcvपूर्णांकpipe(umidi->dev, ep_info->in_ep);
	अन्यथा
		pipe = usb_rcvbulkpipe(umidi->dev, ep_info->in_ep);
	length = usb_maxpacket(umidi->dev, pipe, 0);
	क्रम (i = 0; i < INPUT_URBS; ++i) अणु
		buffer = usb_alloc_coherent(umidi->dev, length, GFP_KERNEL,
					    &ep->urbs[i]->transfer_dma);
		अगर (!buffer) अणु
			err = -ENOMEM;
			जाओ error;
		पूर्ण
		अगर (ep_info->in_पूर्णांकerval)
			usb_fill_पूर्णांक_urb(ep->urbs[i], umidi->dev,
					 pipe, buffer, length,
					 snd_usbmidi_in_urb_complete,
					 ep, ep_info->in_पूर्णांकerval);
		अन्यथा
			usb_fill_bulk_urb(ep->urbs[i], umidi->dev,
					  pipe, buffer, length,
					  snd_usbmidi_in_urb_complete, ep);
		ep->urbs[i]->transfer_flags = URB_NO_TRANSFER_DMA_MAP;
		err = usb_urb_ep_type_check(ep->urbs[i]);
		अगर (err < 0) अणु
			dev_err(&umidi->dev->dev, "invalid MIDI in EP %x\n",
				ep_info->in_ep);
			जाओ error;
		पूर्ण
	पूर्ण

	rep->in = ep;
	वापस 0;

 error:
	snd_usbmidi_in_endpoपूर्णांक_delete(ep);
	वापस err;
पूर्ण

/*
 * Frees an output endpoपूर्णांक.
 * May be called when ep hasn't been initialized completely.
 */
अटल व्योम snd_usbmidi_out_endpoपूर्णांक_clear(काष्ठा snd_usb_midi_out_endpoपूर्णांक *ep)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < OUTPUT_URBS; ++i)
		अगर (ep->urbs[i].urb) अणु
			मुक्त_urb_and_buffer(ep->umidi, ep->urbs[i].urb,
					    ep->max_transfer);
			ep->urbs[i].urb = शून्य;
		पूर्ण
पूर्ण

अटल व्योम snd_usbmidi_out_endpoपूर्णांक_delete(काष्ठा snd_usb_midi_out_endpoपूर्णांक *ep)
अणु
	snd_usbmidi_out_endpoपूर्णांक_clear(ep);
	kमुक्त(ep);
पूर्ण

/*
 * Creates an output endpoपूर्णांक, and initializes output ports.
 */
अटल पूर्णांक snd_usbmidi_out_endpoपूर्णांक_create(काष्ठा snd_usb_midi *umidi,
					   काष्ठा snd_usb_midi_endpoपूर्णांक_info *ep_info,
					   काष्ठा snd_usb_midi_endpoपूर्णांक *rep)
अणु
	काष्ठा snd_usb_midi_out_endpoपूर्णांक *ep;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक pipe;
	व्योम *buffer;
	पूर्णांक err;

	rep->out = शून्य;
	ep = kzalloc(माप(*ep), GFP_KERNEL);
	अगर (!ep)
		वापस -ENOMEM;
	ep->umidi = umidi;

	क्रम (i = 0; i < OUTPUT_URBS; ++i) अणु
		ep->urbs[i].urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!ep->urbs[i].urb) अणु
			err = -ENOMEM;
			जाओ error;
		पूर्ण
		ep->urbs[i].ep = ep;
	पूर्ण
	अगर (ep_info->out_पूर्णांकerval)
		pipe = usb_sndपूर्णांकpipe(umidi->dev, ep_info->out_ep);
	अन्यथा
		pipe = usb_sndbulkpipe(umidi->dev, ep_info->out_ep);
	चयन (umidi->usb_id) अणु
	शेष:
		ep->max_transfer = usb_maxpacket(umidi->dev, pipe, 1);
		अवरोध;
		/*
		 * Various chips declare a packet size larger than 4 bytes, but
		 * करो not actually work with larger packets:
		 */
	हाल USB_ID(0x0a67, 0x5011): /* Medeli DD305 */
	हाल USB_ID(0x0a92, 0x1020): /* ESI M4U */
	हाल USB_ID(0x1430, 0x474b): /* RedOctane GH MIDI INTERFACE */
	हाल USB_ID(0x15ca, 0x0101): /* Textech USB Midi Cable */
	हाल USB_ID(0x15ca, 0x1806): /* Textech USB Midi Cable */
	हाल USB_ID(0x1a86, 0x752d): /* QinHeng CH345 "USB2.0-MIDI" */
	हाल USB_ID(0xfc08, 0x0101): /* Unknown venकरोr Cable */
		ep->max_transfer = 4;
		अवरोध;
		/*
		 * Some devices only work with 9 bytes packet size:
		 */
	हाल USB_ID(0x0644, 0x800e): /* Tascam US-122L */
	हाल USB_ID(0x0644, 0x800f): /* Tascam US-144 */
		ep->max_transfer = 9;
		अवरोध;
	पूर्ण
	क्रम (i = 0; i < OUTPUT_URBS; ++i) अणु
		buffer = usb_alloc_coherent(umidi->dev,
					    ep->max_transfer, GFP_KERNEL,
					    &ep->urbs[i].urb->transfer_dma);
		अगर (!buffer) अणु
			err = -ENOMEM;
			जाओ error;
		पूर्ण
		अगर (ep_info->out_पूर्णांकerval)
			usb_fill_पूर्णांक_urb(ep->urbs[i].urb, umidi->dev,
					 pipe, buffer, ep->max_transfer,
					 snd_usbmidi_out_urb_complete,
					 &ep->urbs[i], ep_info->out_पूर्णांकerval);
		अन्यथा
			usb_fill_bulk_urb(ep->urbs[i].urb, umidi->dev,
					  pipe, buffer, ep->max_transfer,
					  snd_usbmidi_out_urb_complete,
					  &ep->urbs[i]);
		err = usb_urb_ep_type_check(ep->urbs[i].urb);
		अगर (err < 0) अणु
			dev_err(&umidi->dev->dev, "invalid MIDI out EP %x\n",
				ep_info->out_ep);
			जाओ error;
		पूर्ण
		ep->urbs[i].urb->transfer_flags = URB_NO_TRANSFER_DMA_MAP;
	पूर्ण

	spin_lock_init(&ep->buffer_lock);
	INIT_WORK(&ep->work, snd_usbmidi_out_work);
	init_रुकोqueue_head(&ep->drain_रुको);

	क्रम (i = 0; i < 0x10; ++i)
		अगर (ep_info->out_cables & (1 << i)) अणु
			ep->ports[i].ep = ep;
			ep->ports[i].cable = i << 4;
		पूर्ण

	अगर (umidi->usb_protocol_ops->init_out_endpoपूर्णांक)
		umidi->usb_protocol_ops->init_out_endpoपूर्णांक(ep);

	rep->out = ep;
	वापस 0;

 error:
	snd_usbmidi_out_endpoपूर्णांक_delete(ep);
	वापस err;
पूर्ण

/*
 * Frees everything.
 */
अटल व्योम snd_usbmidi_मुक्त(काष्ठा snd_usb_midi *umidi)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MIDI_MAX_ENDPOINTS; ++i) अणु
		काष्ठा snd_usb_midi_endpoपूर्णांक *ep = &umidi->endpoपूर्णांकs[i];
		अगर (ep->out)
			snd_usbmidi_out_endpoपूर्णांक_delete(ep->out);
		अगर (ep->in)
			snd_usbmidi_in_endpoपूर्णांक_delete(ep->in);
	पूर्ण
	mutex_destroy(&umidi->mutex);
	kमुक्त(umidi);
पूर्ण

/*
 * Unlinks all URBs (must be करोne beक्रमe the usb_device is deleted).
 */
व्योम snd_usbmidi_disconnect(काष्ठा list_head *p)
अणु
	काष्ठा snd_usb_midi *umidi;
	अचिन्हित पूर्णांक i, j;

	umidi = list_entry(p, काष्ठा snd_usb_midi, list);
	/*
	 * an URB's completion handler may start the समयr and
	 * a समयr may submit an URB. To reliably अवरोध the cycle
	 * a flag under lock must be used
	 */
	करोwn_ग_लिखो(&umidi->disc_rwsem);
	spin_lock_irq(&umidi->disc_lock);
	umidi->disconnected = 1;
	spin_unlock_irq(&umidi->disc_lock);
	up_ग_लिखो(&umidi->disc_rwsem);

	del_समयr_sync(&umidi->error_समयr);

	क्रम (i = 0; i < MIDI_MAX_ENDPOINTS; ++i) अणु
		काष्ठा snd_usb_midi_endpoपूर्णांक *ep = &umidi->endpoपूर्णांकs[i];
		अगर (ep->out)
			cancel_work_sync(&ep->out->work);
		अगर (ep->out) अणु
			क्रम (j = 0; j < OUTPUT_URBS; ++j)
				usb_समाप्त_urb(ep->out->urbs[j].urb);
			अगर (umidi->usb_protocol_ops->finish_out_endpoपूर्णांक)
				umidi->usb_protocol_ops->finish_out_endpoपूर्णांक(ep->out);
			ep->out->active_urbs = 0;
			अगर (ep->out->drain_urbs) अणु
				ep->out->drain_urbs = 0;
				wake_up(&ep->out->drain_रुको);
			पूर्ण
		पूर्ण
		अगर (ep->in)
			क्रम (j = 0; j < INPUT_URBS; ++j)
				usb_समाप्त_urb(ep->in->urbs[j]);
		/* मुक्त endpoपूर्णांकs here; later call can result in Oops */
		अगर (ep->out)
			snd_usbmidi_out_endpoपूर्णांक_clear(ep->out);
		अगर (ep->in) अणु
			snd_usbmidi_in_endpoपूर्णांक_delete(ep->in);
			ep->in = शून्य;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(snd_usbmidi_disconnect);

अटल व्योम snd_usbmidi_rawmidi_मुक्त(काष्ठा snd_rawmidi *rmidi)
अणु
	काष्ठा snd_usb_midi *umidi = rmidi->निजी_data;
	snd_usbmidi_मुक्त(umidi);
पूर्ण

अटल काष्ठा snd_rawmidi_substream *snd_usbmidi_find_substream(काष्ठा snd_usb_midi *umidi,
								पूर्णांक stream,
								पूर्णांक number)
अणु
	काष्ठा snd_rawmidi_substream *substream;

	list_क्रम_each_entry(substream, &umidi->rmidi->streams[stream].substreams,
			    list) अणु
		अगर (substream->number == number)
			वापस substream;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * This list specअगरies names क्रम ports that करो not fit पूर्णांकo the standard
 * "(product) MIDI (n)" schema because they aren't बाह्यal MIDI ports,
 * such as पूर्णांकernal control or synthesizer ports.
 */
अटल काष्ठा port_info अणु
	u32 id;
	लघु पूर्णांक port;
	लघु पूर्णांक voices;
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक seq_flags;
पूर्ण snd_usbmidi_port_info[] = अणु
#घोषणा PORT_INFO(venकरोr, product, num, name_, voices_, flags) \
	अणु .id = USB_ID(venकरोr, product), \
	  .port = num, .voices = voices_, \
	  .name = name_, .seq_flags = flags पूर्ण
#घोषणा EXTERNAL_PORT(venकरोr, product, num, name) \
	PORT_INFO(venकरोr, product, num, name, 0, \
		  SNDRV_SEQ_PORT_TYPE_MIDI_GENERIC | \
		  SNDRV_SEQ_PORT_TYPE_HARDWARE | \
		  SNDRV_SEQ_PORT_TYPE_PORT)
#घोषणा CONTROL_PORT(venकरोr, product, num, name) \
	PORT_INFO(venकरोr, product, num, name, 0, \
		  SNDRV_SEQ_PORT_TYPE_MIDI_GENERIC | \
		  SNDRV_SEQ_PORT_TYPE_HARDWARE)
#घोषणा GM_SYNTH_PORT(venकरोr, product, num, name, voices) \
	PORT_INFO(venकरोr, product, num, name, voices, \
		  SNDRV_SEQ_PORT_TYPE_MIDI_GENERIC | \
		  SNDRV_SEQ_PORT_TYPE_MIDI_GM | \
		  SNDRV_SEQ_PORT_TYPE_HARDWARE | \
		  SNDRV_SEQ_PORT_TYPE_SYNTHESIZER)
#घोषणा ROLAND_SYNTH_PORT(venकरोr, product, num, name, voices) \
	PORT_INFO(venकरोr, product, num, name, voices, \
		  SNDRV_SEQ_PORT_TYPE_MIDI_GENERIC | \
		  SNDRV_SEQ_PORT_TYPE_MIDI_GM | \
		  SNDRV_SEQ_PORT_TYPE_MIDI_GM2 | \
		  SNDRV_SEQ_PORT_TYPE_MIDI_GS | \
		  SNDRV_SEQ_PORT_TYPE_MIDI_XG | \
		  SNDRV_SEQ_PORT_TYPE_HARDWARE | \
		  SNDRV_SEQ_PORT_TYPE_SYNTHESIZER)
#घोषणा SOUNDCANVAS_PORT(venकरोr, product, num, name, voices) \
	PORT_INFO(venकरोr, product, num, name, voices, \
		  SNDRV_SEQ_PORT_TYPE_MIDI_GENERIC | \
		  SNDRV_SEQ_PORT_TYPE_MIDI_GM | \
		  SNDRV_SEQ_PORT_TYPE_MIDI_GM2 | \
		  SNDRV_SEQ_PORT_TYPE_MIDI_GS | \
		  SNDRV_SEQ_PORT_TYPE_MIDI_XG | \
		  SNDRV_SEQ_PORT_TYPE_MIDI_MT32 | \
		  SNDRV_SEQ_PORT_TYPE_HARDWARE | \
		  SNDRV_SEQ_PORT_TYPE_SYNTHESIZER)
	/* Yamaha MOTIF XF */
	GM_SYNTH_PORT(0x0499, 0x105c, 0, "%s Tone Generator", 128),
	CONTROL_PORT(0x0499, 0x105c, 1, "%s Remote Control"),
	EXTERNAL_PORT(0x0499, 0x105c, 2, "%s Thru"),
	CONTROL_PORT(0x0499, 0x105c, 3, "%s Editor"),
	/* Roland UA-100 */
	CONTROL_PORT(0x0582, 0x0000, 2, "%s Control"),
	/* Roland SC-8850 */
	SOUNDCANVAS_PORT(0x0582, 0x0003, 0, "%s Part A", 128),
	SOUNDCANVAS_PORT(0x0582, 0x0003, 1, "%s Part B", 128),
	SOUNDCANVAS_PORT(0x0582, 0x0003, 2, "%s Part C", 128),
	SOUNDCANVAS_PORT(0x0582, 0x0003, 3, "%s Part D", 128),
	EXTERNAL_PORT(0x0582, 0x0003, 4, "%s MIDI 1"),
	EXTERNAL_PORT(0x0582, 0x0003, 5, "%s MIDI 2"),
	/* Roland U-8 */
	EXTERNAL_PORT(0x0582, 0x0004, 0, "%s MIDI"),
	CONTROL_PORT(0x0582, 0x0004, 1, "%s Control"),
	/* Roland SC-8820 */
	SOUNDCANVAS_PORT(0x0582, 0x0007, 0, "%s Part A", 64),
	SOUNDCANVAS_PORT(0x0582, 0x0007, 1, "%s Part B", 64),
	EXTERNAL_PORT(0x0582, 0x0007, 2, "%s MIDI"),
	/* Roland SK-500 */
	SOUNDCANVAS_PORT(0x0582, 0x000b, 0, "%s Part A", 64),
	SOUNDCANVAS_PORT(0x0582, 0x000b, 1, "%s Part B", 64),
	EXTERNAL_PORT(0x0582, 0x000b, 2, "%s MIDI"),
	/* Roland SC-D70 */
	SOUNDCANVAS_PORT(0x0582, 0x000c, 0, "%s Part A", 64),
	SOUNDCANVAS_PORT(0x0582, 0x000c, 1, "%s Part B", 64),
	EXTERNAL_PORT(0x0582, 0x000c, 2, "%s MIDI"),
	/* Edirol UM-880 */
	CONTROL_PORT(0x0582, 0x0014, 8, "%s Control"),
	/* Edirol SD-90 */
	ROLAND_SYNTH_PORT(0x0582, 0x0016, 0, "%s Part A", 128),
	ROLAND_SYNTH_PORT(0x0582, 0x0016, 1, "%s Part B", 128),
	EXTERNAL_PORT(0x0582, 0x0016, 2, "%s MIDI 1"),
	EXTERNAL_PORT(0x0582, 0x0016, 3, "%s MIDI 2"),
	/* Edirol UM-550 */
	CONTROL_PORT(0x0582, 0x0023, 5, "%s Control"),
	/* Edirol SD-20 */
	ROLAND_SYNTH_PORT(0x0582, 0x0027, 0, "%s Part A", 64),
	ROLAND_SYNTH_PORT(0x0582, 0x0027, 1, "%s Part B", 64),
	EXTERNAL_PORT(0x0582, 0x0027, 2, "%s MIDI"),
	/* Edirol SD-80 */
	ROLAND_SYNTH_PORT(0x0582, 0x0029, 0, "%s Part A", 128),
	ROLAND_SYNTH_PORT(0x0582, 0x0029, 1, "%s Part B", 128),
	EXTERNAL_PORT(0x0582, 0x0029, 2, "%s MIDI 1"),
	EXTERNAL_PORT(0x0582, 0x0029, 3, "%s MIDI 2"),
	/* Edirol UA-700 */
	EXTERNAL_PORT(0x0582, 0x002b, 0, "%s MIDI"),
	CONTROL_PORT(0x0582, 0x002b, 1, "%s Control"),
	/* Roland VariOS */
	EXTERNAL_PORT(0x0582, 0x002f, 0, "%s MIDI"),
	EXTERNAL_PORT(0x0582, 0x002f, 1, "%s External MIDI"),
	EXTERNAL_PORT(0x0582, 0x002f, 2, "%s Sync"),
	/* Edirol PCR */
	EXTERNAL_PORT(0x0582, 0x0033, 0, "%s MIDI"),
	EXTERNAL_PORT(0x0582, 0x0033, 1, "%s 1"),
	EXTERNAL_PORT(0x0582, 0x0033, 2, "%s 2"),
	/* BOSS GS-10 */
	EXTERNAL_PORT(0x0582, 0x003b, 0, "%s MIDI"),
	CONTROL_PORT(0x0582, 0x003b, 1, "%s Control"),
	/* Edirol UA-1000 */
	EXTERNAL_PORT(0x0582, 0x0044, 0, "%s MIDI"),
	CONTROL_PORT(0x0582, 0x0044, 1, "%s Control"),
	/* Edirol UR-80 */
	EXTERNAL_PORT(0x0582, 0x0048, 0, "%s MIDI"),
	EXTERNAL_PORT(0x0582, 0x0048, 1, "%s 1"),
	EXTERNAL_PORT(0x0582, 0x0048, 2, "%s 2"),
	/* Edirol PCR-A */
	EXTERNAL_PORT(0x0582, 0x004d, 0, "%s MIDI"),
	EXTERNAL_PORT(0x0582, 0x004d, 1, "%s 1"),
	EXTERNAL_PORT(0x0582, 0x004d, 2, "%s 2"),
	/* BOSS GT-PRO */
	CONTROL_PORT(0x0582, 0x0089, 0, "%s Control"),
	/* Edirol UM-3EX */
	CONTROL_PORT(0x0582, 0x009a, 3, "%s Control"),
	/* Roland VG-99 */
	CONTROL_PORT(0x0582, 0x00b2, 0, "%s Control"),
	EXTERNAL_PORT(0x0582, 0x00b2, 1, "%s MIDI"),
	/* Cakewalk Sonar V-Studio 100 */
	EXTERNAL_PORT(0x0582, 0x00eb, 0, "%s MIDI"),
	CONTROL_PORT(0x0582, 0x00eb, 1, "%s Control"),
	/* Roland VB-99 */
	CONTROL_PORT(0x0582, 0x0102, 0, "%s Control"),
	EXTERNAL_PORT(0x0582, 0x0102, 1, "%s MIDI"),
	/* Roland A-PRO */
	EXTERNAL_PORT(0x0582, 0x010f, 0, "%s MIDI"),
	CONTROL_PORT(0x0582, 0x010f, 1, "%s 1"),
	CONTROL_PORT(0x0582, 0x010f, 2, "%s 2"),
	/* Roland SD-50 */
	ROLAND_SYNTH_PORT(0x0582, 0x0114, 0, "%s Synth", 128),
	EXTERNAL_PORT(0x0582, 0x0114, 1, "%s MIDI"),
	CONTROL_PORT(0x0582, 0x0114, 2, "%s Control"),
	/* Roland OCTA-CAPTURE */
	EXTERNAL_PORT(0x0582, 0x0120, 0, "%s MIDI"),
	CONTROL_PORT(0x0582, 0x0120, 1, "%s Control"),
	EXTERNAL_PORT(0x0582, 0x0121, 0, "%s MIDI"),
	CONTROL_PORT(0x0582, 0x0121, 1, "%s Control"),
	/* Roland SPD-SX */
	CONTROL_PORT(0x0582, 0x0145, 0, "%s Control"),
	EXTERNAL_PORT(0x0582, 0x0145, 1, "%s MIDI"),
	/* Roland A-Series */
	CONTROL_PORT(0x0582, 0x0156, 0, "%s Keyboard"),
	EXTERNAL_PORT(0x0582, 0x0156, 1, "%s MIDI"),
	/* Roland INTEGRA-7 */
	ROLAND_SYNTH_PORT(0x0582, 0x015b, 0, "%s Synth", 128),
	CONTROL_PORT(0x0582, 0x015b, 1, "%s Control"),
	/* M-Audio MidiSport 8x8 */
	CONTROL_PORT(0x0763, 0x1031, 8, "%s Control"),
	CONTROL_PORT(0x0763, 0x1033, 8, "%s Control"),
	/* MOTU Fastlane */
	EXTERNAL_PORT(0x07fd, 0x0001, 0, "%s MIDI A"),
	EXTERNAL_PORT(0x07fd, 0x0001, 1, "%s MIDI B"),
	/* Emagic Unitor8/AMT8/MT4 */
	EXTERNAL_PORT(0x086a, 0x0001, 8, "%s Broadcast"),
	EXTERNAL_PORT(0x086a, 0x0002, 8, "%s Broadcast"),
	EXTERNAL_PORT(0x086a, 0x0003, 4, "%s Broadcast"),
	/* Akai MPD16 */
	CONTROL_PORT(0x09e8, 0x0062, 0, "%s Control"),
	PORT_INFO(0x09e8, 0x0062, 1, "%s MIDI", 0,
		SNDRV_SEQ_PORT_TYPE_MIDI_GENERIC |
		SNDRV_SEQ_PORT_TYPE_HARDWARE),
	/* Access Music Virus TI */
	EXTERNAL_PORT(0x133e, 0x0815, 0, "%s MIDI"),
	PORT_INFO(0x133e, 0x0815, 1, "%s Synth", 0,
		SNDRV_SEQ_PORT_TYPE_MIDI_GENERIC |
		SNDRV_SEQ_PORT_TYPE_HARDWARE |
		SNDRV_SEQ_PORT_TYPE_SYNTHESIZER),
पूर्ण;

अटल काष्ठा port_info *find_port_info(काष्ठा snd_usb_midi *umidi, पूर्णांक number)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(snd_usbmidi_port_info); ++i) अणु
		अगर (snd_usbmidi_port_info[i].id == umidi->usb_id &&
		    snd_usbmidi_port_info[i].port == number)
			वापस &snd_usbmidi_port_info[i];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम snd_usbmidi_get_port_info(काष्ठा snd_rawmidi *rmidi, पूर्णांक number,
				      काष्ठा snd_seq_port_info *seq_port_info)
अणु
	काष्ठा snd_usb_midi *umidi = rmidi->निजी_data;
	काष्ठा port_info *port_info;

	/* TODO: पढ़ो port flags from descriptors */
	port_info = find_port_info(umidi, number);
	अगर (port_info) अणु
		seq_port_info->type = port_info->seq_flags;
		seq_port_info->midi_voices = port_info->voices;
	पूर्ण
पूर्ण

अटल काष्ठा usb_midi_in_jack_descriptor *find_usb_in_jack_descriptor(
					काष्ठा usb_host_पूर्णांकerface *hostअगर, uपूर्णांक8_t jack_id)
अणु
	अचिन्हित अक्षर *extra = hostअगर->extra;
	पूर्णांक extralen = hostअगर->extralen;

	जबतक (extralen > 4) अणु
		काष्ठा usb_midi_in_jack_descriptor *injd =
				(काष्ठा usb_midi_in_jack_descriptor *)extra;

		अगर (injd->bLength >= माप(*injd) &&
		    injd->bDescriptorType == USB_DT_CS_INTERFACE &&
		    injd->bDescriptorSubtype == UAC_MIDI_IN_JACK &&
				injd->bJackID == jack_id)
			वापस injd;
		अगर (!extra[0])
			अवरोध;
		extralen -= extra[0];
		extra += extra[0];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा usb_midi_out_jack_descriptor *find_usb_out_jack_descriptor(
					काष्ठा usb_host_पूर्णांकerface *hostअगर, uपूर्णांक8_t jack_id)
अणु
	अचिन्हित अक्षर *extra = hostअगर->extra;
	पूर्णांक extralen = hostअगर->extralen;

	जबतक (extralen > 4) अणु
		काष्ठा usb_midi_out_jack_descriptor *outjd =
				(काष्ठा usb_midi_out_jack_descriptor *)extra;

		अगर (outjd->bLength >= माप(*outjd) &&
		    outjd->bDescriptorType == USB_DT_CS_INTERFACE &&
		    outjd->bDescriptorSubtype == UAC_MIDI_OUT_JACK &&
				outjd->bJackID == jack_id)
			वापस outjd;
		अगर (!extra[0])
			अवरोध;
		extralen -= extra[0];
		extra += extra[0];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम snd_usbmidi_init_substream(काष्ठा snd_usb_midi *umidi,
				       पूर्णांक stream, पूर्णांक number, पूर्णांक jack_id,
				       काष्ठा snd_rawmidi_substream **rsubstream)
अणु
	काष्ठा port_info *port_info;
	स्थिर अक्षर *name_क्रमmat;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा usb_host_पूर्णांकerface *hostअगर;
	काष्ठा usb_midi_in_jack_descriptor *injd;
	काष्ठा usb_midi_out_jack_descriptor *outjd;
	uपूर्णांक8_t jack_name_buf[32];
	uपूर्णांक8_t *शेष_jack_name = "MIDI";
	uपूर्णांक8_t *jack_name = शेष_jack_name;
	uपूर्णांक8_t iJack;
	माप_प्रकार sz;
	पूर्णांक res;

	काष्ठा snd_rawmidi_substream *substream =
		snd_usbmidi_find_substream(umidi, stream, number);
	अगर (!substream) अणु
		dev_err(&umidi->dev->dev, "substream %d:%d not found\n", stream,
			number);
		वापस;
	पूर्ण

	पूर्णांकf = umidi->अगरace;
	अगर (पूर्णांकf && jack_id >= 0) अणु
		hostअगर = पूर्णांकf->cur_altsetting;
		iJack = 0;
		अगर (stream != SNDRV_RAWMIDI_STREAM_OUTPUT) अणु
			/* in jacks connect to outs */
			outjd = find_usb_out_jack_descriptor(hostअगर, jack_id);
			अगर (outjd) अणु
				sz = USB_DT_MIDI_OUT_SIZE(outjd->bNrInputPins);
				अगर (outjd->bLength >= sz)
					iJack = *(((uपूर्णांक8_t *) outjd) + sz - माप(uपूर्णांक8_t));
			पूर्ण
		पूर्ण अन्यथा अणु
			/* and out jacks connect to ins */
			injd = find_usb_in_jack_descriptor(hostअगर, jack_id);
			अगर (injd)
				iJack = injd->iJack;
		पूर्ण
		अगर (iJack != 0) अणु
			res = usb_string(umidi->dev, iJack, jack_name_buf,
			  ARRAY_SIZE(jack_name_buf));
			अगर (res)
				jack_name = jack_name_buf;
		पूर्ण
	पूर्ण

	port_info = find_port_info(umidi, number);
	name_क्रमmat = port_info ? port_info->name :
		(jack_name != शेष_jack_name  ? "%s %s" : "%s %s %d");
	snम_लिखो(substream->name, माप(substream->name),
		 name_क्रमmat, umidi->card->लघुname, jack_name, number + 1);

	*rsubstream = substream;
पूर्ण

/*
 * Creates the endpoपूर्णांकs and their ports.
 */
अटल पूर्णांक snd_usbmidi_create_endpoपूर्णांकs(काष्ठा snd_usb_midi *umidi,
					काष्ठा snd_usb_midi_endpoपूर्णांक_info *endpoपूर्णांकs)
अणु
	पूर्णांक i, j, err;
	पूर्णांक out_ports = 0, in_ports = 0;

	क्रम (i = 0; i < MIDI_MAX_ENDPOINTS; ++i) अणु
		अगर (endpoपूर्णांकs[i].out_cables) अणु
			err = snd_usbmidi_out_endpoपूर्णांक_create(umidi,
							      &endpoपूर्णांकs[i],
							      &umidi->endpoपूर्णांकs[i]);
			अगर (err < 0)
				वापस err;
		पूर्ण
		अगर (endpoपूर्णांकs[i].in_cables) अणु
			err = snd_usbmidi_in_endpoपूर्णांक_create(umidi,
							     &endpoपूर्णांकs[i],
							     &umidi->endpoपूर्णांकs[i]);
			अगर (err < 0)
				वापस err;
		पूर्ण

		क्रम (j = 0; j < 0x10; ++j) अणु
			अगर (endpoपूर्णांकs[i].out_cables & (1 << j)) अणु
				snd_usbmidi_init_substream(umidi,
							   SNDRV_RAWMIDI_STREAM_OUTPUT,
							   out_ports,
							   endpoपूर्णांकs[i].assoc_out_jacks[j],
							   &umidi->endpoपूर्णांकs[i].out->ports[j].substream);
				++out_ports;
			पूर्ण
			अगर (endpoपूर्णांकs[i].in_cables & (1 << j)) अणु
				snd_usbmidi_init_substream(umidi,
							   SNDRV_RAWMIDI_STREAM_INPUT,
							   in_ports,
							   endpoपूर्णांकs[i].assoc_in_jacks[j],
							   &umidi->endpoपूर्णांकs[i].in->ports[j].substream);
				++in_ports;
			पूर्ण
		पूर्ण
	पूर्ण
	dev_dbg(&umidi->dev->dev, "created %d output and %d input ports\n",
		    out_ports, in_ports);
	वापस 0;
पूर्ण

अटल काष्ठा usb_ms_endpoपूर्णांक_descriptor *find_usb_ms_endpoपूर्णांक_descriptor(
					काष्ठा usb_host_endpoपूर्णांक *hostep)
अणु
	अचिन्हित अक्षर *extra = hostep->extra;
	पूर्णांक extralen = hostep->extralen;

	जबतक (extralen > 3) अणु
		काष्ठा usb_ms_endpoपूर्णांक_descriptor *ms_ep =
				(काष्ठा usb_ms_endpoपूर्णांक_descriptor *)extra;

		अगर (ms_ep->bLength > 3 &&
		    ms_ep->bDescriptorType == USB_DT_CS_ENDPOINT &&
		    ms_ep->bDescriptorSubtype == UAC_MS_GENERAL)
			वापस ms_ep;
		अगर (!extra[0])
			अवरोध;
		extralen -= extra[0];
		extra += extra[0];
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Returns MIDIStreaming device capabilities.
 */
अटल पूर्णांक snd_usbmidi_get_ms_info(काष्ठा snd_usb_midi *umidi,
				   काष्ठा snd_usb_midi_endpoपूर्णांक_info *endpoपूर्णांकs)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा usb_host_पूर्णांकerface *hostअगर;
	काष्ठा usb_पूर्णांकerface_descriptor *पूर्णांकfd;
	काष्ठा usb_ms_header_descriptor *ms_header;
	काष्ठा usb_host_endpoपूर्णांक *hostep;
	काष्ठा usb_endpoपूर्णांक_descriptor *ep;
	काष्ठा usb_ms_endpoपूर्णांक_descriptor *ms_ep;
	पूर्णांक i, j, epidx;

	पूर्णांकf = umidi->अगरace;
	अगर (!पूर्णांकf)
		वापस -ENXIO;
	hostअगर = &पूर्णांकf->altsetting[0];
	पूर्णांकfd = get_अगरace_desc(hostअगर);
	ms_header = (काष्ठा usb_ms_header_descriptor *)hostअगर->extra;
	अगर (hostअगर->extralen >= 7 &&
	    ms_header->bLength >= 7 &&
	    ms_header->bDescriptorType == USB_DT_CS_INTERFACE &&
	    ms_header->bDescriptorSubtype == UAC_HEADER)
		dev_dbg(&umidi->dev->dev, "MIDIStreaming version %02x.%02x\n",
			    ((uपूर्णांक8_t *)&ms_header->bcdMSC)[1], ((uपूर्णांक8_t *)&ms_header->bcdMSC)[0]);
	अन्यथा
		dev_warn(&umidi->dev->dev,
			 "MIDIStreaming interface descriptor not found\n");

	epidx = 0;
	क्रम (i = 0; i < पूर्णांकfd->bNumEndpoपूर्णांकs; ++i) अणु
		hostep = &hostअगर->endpoपूर्णांक[i];
		ep = get_ep_desc(hostep);
		अगर (!usb_endpoपूर्णांक_xfer_bulk(ep) && !usb_endpoपूर्णांक_xfer_पूर्णांक(ep))
			जारी;
		ms_ep = find_usb_ms_endpoपूर्णांक_descriptor(hostep);
		अगर (!ms_ep)
			जारी;
		अगर (ms_ep->bLength <= माप(*ms_ep))
			जारी;
		अगर (ms_ep->bNumEmbMIDIJack > 0x10)
			जारी;
		अगर (ms_ep->bLength < माप(*ms_ep) + ms_ep->bNumEmbMIDIJack)
			जारी;
		अगर (usb_endpoपूर्णांक_dir_out(ep)) अणु
			अगर (endpoपूर्णांकs[epidx].out_ep) अणु
				अगर (++epidx >= MIDI_MAX_ENDPOINTS) अणु
					dev_warn(&umidi->dev->dev,
						 "too many endpoints\n");
					अवरोध;
				पूर्ण
			पूर्ण
			endpoपूर्णांकs[epidx].out_ep = usb_endpoपूर्णांक_num(ep);
			अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(ep))
				endpoपूर्णांकs[epidx].out_पूर्णांकerval = ep->bInterval;
			अन्यथा अगर (snd_usb_get_speed(umidi->dev) == USB_SPEED_LOW)
				/*
				 * Low speed bulk transfers करोn't exist, so
				 * क्रमce पूर्णांकerrupt transfers क्रम devices like
				 * ESI MIDI Mate that try to use them anyway.
				 */
				endpoपूर्णांकs[epidx].out_पूर्णांकerval = 1;
			endpoपूर्णांकs[epidx].out_cables =
				(1 << ms_ep->bNumEmbMIDIJack) - 1;
			क्रम (j = 0; j < ms_ep->bNumEmbMIDIJack; ++j)
				endpoपूर्णांकs[epidx].assoc_out_jacks[j] = ms_ep->baAssocJackID[j];
			क्रम (; j < ARRAY_SIZE(endpoपूर्णांकs[epidx].assoc_out_jacks); ++j)
				endpoपूर्णांकs[epidx].assoc_out_jacks[j] = -1;
			dev_dbg(&umidi->dev->dev, "EP %02X: %d jack(s)\n",
				ep->bEndpoपूर्णांकAddress, ms_ep->bNumEmbMIDIJack);
		पूर्ण अन्यथा अणु
			अगर (endpoपूर्णांकs[epidx].in_ep) अणु
				अगर (++epidx >= MIDI_MAX_ENDPOINTS) अणु
					dev_warn(&umidi->dev->dev,
						 "too many endpoints\n");
					अवरोध;
				पूर्ण
			पूर्ण
			endpoपूर्णांकs[epidx].in_ep = usb_endpoपूर्णांक_num(ep);
			अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(ep))
				endpoपूर्णांकs[epidx].in_पूर्णांकerval = ep->bInterval;
			अन्यथा अगर (snd_usb_get_speed(umidi->dev) == USB_SPEED_LOW)
				endpoपूर्णांकs[epidx].in_पूर्णांकerval = 1;
			endpoपूर्णांकs[epidx].in_cables =
				(1 << ms_ep->bNumEmbMIDIJack) - 1;
			क्रम (j = 0; j < ms_ep->bNumEmbMIDIJack; ++j)
				endpoपूर्णांकs[epidx].assoc_in_jacks[j] = ms_ep->baAssocJackID[j];
			क्रम (; j < ARRAY_SIZE(endpoपूर्णांकs[epidx].assoc_in_jacks); ++j)
				endpoपूर्णांकs[epidx].assoc_in_jacks[j] = -1;
			dev_dbg(&umidi->dev->dev, "EP %02X: %d jack(s)\n",
				ep->bEndpoपूर्णांकAddress, ms_ep->bNumEmbMIDIJack);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक roland_load_info(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_info *info)
अणु
	अटल स्थिर अक्षर *स्थिर names[] = अणु "High Load", "Light Load" पूर्ण;

	वापस snd_ctl_क्रमागत_info(info, 1, 2, names);
पूर्ण

अटल पूर्णांक roland_load_get(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_value *value)
अणु
	value->value.क्रमागतerated.item[0] = kcontrol->निजी_value;
	वापस 0;
पूर्ण

अटल पूर्णांक roland_load_put(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा snd_usb_midi *umidi = kcontrol->निजी_data;
	पूर्णांक changed;

	अगर (value->value.क्रमागतerated.item[0] > 1)
		वापस -EINVAL;
	mutex_lock(&umidi->mutex);
	changed = value->value.क्रमागतerated.item[0] != kcontrol->निजी_value;
	अगर (changed)
		kcontrol->निजी_value = value->value.क्रमागतerated.item[0];
	mutex_unlock(&umidi->mutex);
	वापस changed;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new roland_load_ctl = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "MIDI Input Mode",
	.info = roland_load_info,
	.get = roland_load_get,
	.put = roland_load_put,
	.निजी_value = 1,
पूर्ण;

/*
 * On Roland devices, use the second alternate setting to be able to use
 * the पूर्णांकerrupt input endpoपूर्णांक.
 */
अटल व्योम snd_usbmidi_चयन_roland_altsetting(काष्ठा snd_usb_midi *umidi)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा usb_host_पूर्णांकerface *hostअगर;
	काष्ठा usb_पूर्णांकerface_descriptor *पूर्णांकfd;

	पूर्णांकf = umidi->अगरace;
	अगर (!पूर्णांकf || पूर्णांकf->num_altsetting != 2)
		वापस;

	hostअगर = &पूर्णांकf->altsetting[1];
	पूर्णांकfd = get_अगरace_desc(hostअगर);
       /* If either or both of the endpoपूर्णांकs support पूर्णांकerrupt transfer,
        * then use the alternate setting
        */
	अगर (पूर्णांकfd->bNumEndpoपूर्णांकs != 2 ||
	    !((get_endpoपूर्णांक(hostअगर, 0)->bmAttributes &
	       USB_ENDPOINT_XFERTYPE_MASK) == USB_ENDPOINT_XFER_INT ||
	      (get_endpoपूर्णांक(hostअगर, 1)->bmAttributes &
	       USB_ENDPOINT_XFERTYPE_MASK) == USB_ENDPOINT_XFER_INT))
		वापस;

	dev_dbg(&umidi->dev->dev, "switching to altsetting %d with int ep\n",
		    पूर्णांकfd->bAlternateSetting);
	usb_set_पूर्णांकerface(umidi->dev, पूर्णांकfd->bInterfaceNumber,
			  पूर्णांकfd->bAlternateSetting);

	umidi->roland_load_ctl = snd_ctl_new1(&roland_load_ctl, umidi);
	अगर (snd_ctl_add(umidi->card, umidi->roland_load_ctl) < 0)
		umidi->roland_load_ctl = शून्य;
पूर्ण

/*
 * Try to find any usable endpoपूर्णांकs in the पूर्णांकerface.
 */
अटल पूर्णांक snd_usbmidi_detect_endpoपूर्णांकs(काष्ठा snd_usb_midi *umidi,
					काष्ठा snd_usb_midi_endpoपूर्णांक_info *endpoपूर्णांक,
					पूर्णांक max_endpoपूर्णांकs)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा usb_host_पूर्णांकerface *hostअगर;
	काष्ठा usb_पूर्णांकerface_descriptor *पूर्णांकfd;
	काष्ठा usb_endpoपूर्णांक_descriptor *epd;
	पूर्णांक i, out_eps = 0, in_eps = 0;

	अगर (USB_ID_VENDOR(umidi->usb_id) == 0x0582)
		snd_usbmidi_चयन_roland_altsetting(umidi);

	अगर (endpoपूर्णांक[0].out_ep || endpoपूर्णांक[0].in_ep)
		वापस 0;

	पूर्णांकf = umidi->अगरace;
	अगर (!पूर्णांकf || पूर्णांकf->num_altsetting < 1)
		वापस -ENOENT;
	hostअगर = पूर्णांकf->cur_altsetting;
	पूर्णांकfd = get_अगरace_desc(hostअगर);

	क्रम (i = 0; i < पूर्णांकfd->bNumEndpoपूर्णांकs; ++i) अणु
		epd = get_endpoपूर्णांक(hostअगर, i);
		अगर (!usb_endpoपूर्णांक_xfer_bulk(epd) &&
		    !usb_endpoपूर्णांक_xfer_पूर्णांक(epd))
			जारी;
		अगर (out_eps < max_endpoपूर्णांकs &&
		    usb_endpoपूर्णांक_dir_out(epd)) अणु
			endpoपूर्णांक[out_eps].out_ep = usb_endpoपूर्णांक_num(epd);
			अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(epd))
				endpoपूर्णांक[out_eps].out_पूर्णांकerval = epd->bInterval;
			++out_eps;
		पूर्ण
		अगर (in_eps < max_endpoपूर्णांकs &&
		    usb_endpoपूर्णांक_dir_in(epd)) अणु
			endpoपूर्णांक[in_eps].in_ep = usb_endpoपूर्णांक_num(epd);
			अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(epd))
				endpoपूर्णांक[in_eps].in_पूर्णांकerval = epd->bInterval;
			++in_eps;
		पूर्ण
	पूर्ण
	वापस (out_eps || in_eps) ? 0 : -ENOENT;
पूर्ण

/*
 * Detects the endpoपूर्णांकs क्रम one-port-per-endpoपूर्णांक protocols.
 */
अटल पूर्णांक snd_usbmidi_detect_per_port_endpoपूर्णांकs(काष्ठा snd_usb_midi *umidi,
						 काष्ठा snd_usb_midi_endpoपूर्णांक_info *endpoपूर्णांकs)
अणु
	पूर्णांक err, i;

	err = snd_usbmidi_detect_endpoपूर्णांकs(umidi, endpoपूर्णांकs, MIDI_MAX_ENDPOINTS);
	क्रम (i = 0; i < MIDI_MAX_ENDPOINTS; ++i) अणु
		अगर (endpoपूर्णांकs[i].out_ep)
			endpoपूर्णांकs[i].out_cables = 0x0001;
		अगर (endpoपूर्णांकs[i].in_ep)
			endpoपूर्णांकs[i].in_cables = 0x0001;
	पूर्ण
	वापस err;
पूर्ण

/*
 * Detects the endpoपूर्णांकs and ports of Yamaha devices.
 */
अटल पूर्णांक snd_usbmidi_detect_yamaha(काष्ठा snd_usb_midi *umidi,
				     काष्ठा snd_usb_midi_endpoपूर्णांक_info *endpoपूर्णांक)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा usb_host_पूर्णांकerface *hostअगर;
	काष्ठा usb_पूर्णांकerface_descriptor *पूर्णांकfd;
	uपूर्णांक8_t *cs_desc;

	पूर्णांकf = umidi->अगरace;
	अगर (!पूर्णांकf)
		वापस -ENOENT;
	hostअगर = पूर्णांकf->altsetting;
	पूर्णांकfd = get_अगरace_desc(hostअगर);
	अगर (पूर्णांकfd->bNumEndpoपूर्णांकs < 1)
		वापस -ENOENT;

	/*
	 * For each port there is one MIDI_IN/OUT_JACK descriptor, not
	 * necessarily with any useful contents.  So simply count 'em.
	 */
	क्रम (cs_desc = hostअगर->extra;
	     cs_desc < hostअगर->extra + hostअगर->extralen && cs_desc[0] >= 2;
	     cs_desc += cs_desc[0]) अणु
		अगर (cs_desc[1] == USB_DT_CS_INTERFACE) अणु
			अगर (cs_desc[2] == UAC_MIDI_IN_JACK)
				endpoपूर्णांक->in_cables =
					(endpoपूर्णांक->in_cables << 1) | 1;
			अन्यथा अगर (cs_desc[2] == UAC_MIDI_OUT_JACK)
				endpoपूर्णांक->out_cables =
					(endpoपूर्णांक->out_cables << 1) | 1;
		पूर्ण
	पूर्ण
	अगर (!endpoपूर्णांक->in_cables && !endpoपूर्णांक->out_cables)
		वापस -ENOENT;

	वापस snd_usbmidi_detect_endpoपूर्णांकs(umidi, endpoपूर्णांक, 1);
पूर्ण

/*
 * Detects the endpoपूर्णांकs and ports of Roland devices.
 */
अटल पूर्णांक snd_usbmidi_detect_roland(काष्ठा snd_usb_midi *umidi,
				     काष्ठा snd_usb_midi_endpoपूर्णांक_info *endpoपूर्णांक)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा usb_host_पूर्णांकerface *hostअगर;
	u8 *cs_desc;

	पूर्णांकf = umidi->अगरace;
	अगर (!पूर्णांकf)
		वापस -ENOENT;
	hostअगर = पूर्णांकf->altsetting;
	/*
	 * Some devices have a descriptor <06 24 F1 02 <inमाला_दो> <outमाला_दो>>,
	 * some have standard class descriptors, or both kinds, or neither.
	 */
	क्रम (cs_desc = hostअगर->extra;
	     cs_desc < hostअगर->extra + hostअगर->extralen && cs_desc[0] >= 2;
	     cs_desc += cs_desc[0]) अणु
		अगर (cs_desc[0] >= 6 &&
		    cs_desc[1] == USB_DT_CS_INTERFACE &&
		    cs_desc[2] == 0xf1 &&
		    cs_desc[3] == 0x02) अणु
			अगर (cs_desc[4] > 0x10 || cs_desc[5] > 0x10)
				जारी;
			endpoपूर्णांक->in_cables  = (1 << cs_desc[4]) - 1;
			endpoपूर्णांक->out_cables = (1 << cs_desc[5]) - 1;
			वापस snd_usbmidi_detect_endpoपूर्णांकs(umidi, endpoपूर्णांक, 1);
		पूर्ण अन्यथा अगर (cs_desc[0] >= 7 &&
			   cs_desc[1] == USB_DT_CS_INTERFACE &&
			   cs_desc[2] == UAC_HEADER) अणु
			वापस snd_usbmidi_get_ms_info(umidi, endpoपूर्णांक);
		पूर्ण
	पूर्ण

	वापस -ENODEV;
पूर्ण

/*
 * Creates the endpoपूर्णांकs and their ports क्रम Midiman devices.
 */
अटल पूर्णांक snd_usbmidi_create_endpoपूर्णांकs_midiman(काष्ठा snd_usb_midi *umidi,
						काष्ठा snd_usb_midi_endpoपूर्णांक_info *endpoपूर्णांक)
अणु
	काष्ठा snd_usb_midi_endpoपूर्णांक_info ep_info;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा usb_host_पूर्णांकerface *hostअगर;
	काष्ठा usb_पूर्णांकerface_descriptor *पूर्णांकfd;
	काष्ठा usb_endpoपूर्णांक_descriptor *epd;
	पूर्णांक cable, err;

	पूर्णांकf = umidi->अगरace;
	अगर (!पूर्णांकf)
		वापस -ENOENT;
	hostअगर = पूर्णांकf->altsetting;
	पूर्णांकfd = get_अगरace_desc(hostअगर);
	/*
	 * The various MidiSport devices have more or less अक्रमom endpoपूर्णांक
	 * numbers, so we have to identअगरy the endpoपूर्णांकs by their index in
	 * the descriptor array, like the driver क्रम that other OS करोes.
	 *
	 * There is one पूर्णांकerrupt input endpoपूर्णांक क्रम all input ports, one
	 * bulk output endpoपूर्णांक क्रम even-numbered ports, and one क्रम odd-
	 * numbered ports.  Both bulk output endpoपूर्णांकs have corresponding
	 * input bulk endpoपूर्णांकs (at indices 1 and 3) which aren't used.
	 */
	अगर (पूर्णांकfd->bNumEndpoपूर्णांकs < (endpoपूर्णांक->out_cables > 0x0001 ? 5 : 3)) अणु
		dev_dbg(&umidi->dev->dev, "not enough endpoints\n");
		वापस -ENOENT;
	पूर्ण

	epd = get_endpoपूर्णांक(hostअगर, 0);
	अगर (!usb_endpoपूर्णांक_dir_in(epd) || !usb_endpoपूर्णांक_xfer_पूर्णांक(epd)) अणु
		dev_dbg(&umidi->dev->dev, "endpoint[0] isn't interrupt\n");
		वापस -ENXIO;
	पूर्ण
	epd = get_endpoपूर्णांक(hostअगर, 2);
	अगर (!usb_endpoपूर्णांक_dir_out(epd) || !usb_endpoपूर्णांक_xfer_bulk(epd)) अणु
		dev_dbg(&umidi->dev->dev, "endpoint[2] isn't bulk output\n");
		वापस -ENXIO;
	पूर्ण
	अगर (endpoपूर्णांक->out_cables > 0x0001) अणु
		epd = get_endpoपूर्णांक(hostअगर, 4);
		अगर (!usb_endpoपूर्णांक_dir_out(epd) ||
		    !usb_endpoपूर्णांक_xfer_bulk(epd)) अणु
			dev_dbg(&umidi->dev->dev,
				"endpoint[4] isn't bulk output\n");
			वापस -ENXIO;
		पूर्ण
	पूर्ण

	ep_info.out_ep = get_endpoपूर्णांक(hostअगर, 2)->bEndpoपूर्णांकAddress &
		USB_ENDPOINT_NUMBER_MASK;
	ep_info.out_पूर्णांकerval = 0;
	ep_info.out_cables = endpoपूर्णांक->out_cables & 0x5555;
	err = snd_usbmidi_out_endpoपूर्णांक_create(umidi, &ep_info,
					      &umidi->endpoपूर्णांकs[0]);
	अगर (err < 0)
		वापस err;

	ep_info.in_ep = get_endpoपूर्णांक(hostअगर, 0)->bEndpoपूर्णांकAddress &
		USB_ENDPOINT_NUMBER_MASK;
	ep_info.in_पूर्णांकerval = get_endpoपूर्णांक(hostअगर, 0)->bInterval;
	ep_info.in_cables = endpoपूर्णांक->in_cables;
	err = snd_usbmidi_in_endpoपूर्णांक_create(umidi, &ep_info,
					     &umidi->endpoपूर्णांकs[0]);
	अगर (err < 0)
		वापस err;

	अगर (endpoपूर्णांक->out_cables > 0x0001) अणु
		ep_info.out_ep = get_endpoपूर्णांक(hostअगर, 4)->bEndpoपूर्णांकAddress &
			USB_ENDPOINT_NUMBER_MASK;
		ep_info.out_cables = endpoपूर्णांक->out_cables & 0xaaaa;
		err = snd_usbmidi_out_endpoपूर्णांक_create(umidi, &ep_info,
						      &umidi->endpoपूर्णांकs[1]);
		अगर (err < 0)
			वापस err;
	पूर्ण

	क्रम (cable = 0; cable < 0x10; ++cable) अणु
		अगर (endpoपूर्णांक->out_cables & (1 << cable))
			snd_usbmidi_init_substream(umidi,
						   SNDRV_RAWMIDI_STREAM_OUTPUT,
						   cable,
						   -1 /* prevent trying to find jack */,
						   &umidi->endpoपूर्णांकs[cable & 1].out->ports[cable].substream);
		अगर (endpoपूर्णांक->in_cables & (1 << cable))
			snd_usbmidi_init_substream(umidi,
						   SNDRV_RAWMIDI_STREAM_INPUT,
						   cable,
						   -1 /* prevent trying to find jack */,
						   &umidi->endpoपूर्णांकs[0].in->ports[cable].substream);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_rawmidi_global_ops snd_usbmidi_ops = अणु
	.get_port_info = snd_usbmidi_get_port_info,
पूर्ण;

अटल पूर्णांक snd_usbmidi_create_rawmidi(काष्ठा snd_usb_midi *umidi,
				      पूर्णांक out_ports, पूर्णांक in_ports)
अणु
	काष्ठा snd_rawmidi *rmidi;
	पूर्णांक err;

	err = snd_rawmidi_new(umidi->card, "USB MIDI",
			      umidi->next_midi_device++,
			      out_ports, in_ports, &rmidi);
	अगर (err < 0)
		वापस err;
	म_नकल(rmidi->name, umidi->card->लघुname);
	rmidi->info_flags = SNDRV_RAWMIDI_INFO_OUTPUT |
			    SNDRV_RAWMIDI_INFO_INPUT |
			    SNDRV_RAWMIDI_INFO_DUPLEX;
	rmidi->ops = &snd_usbmidi_ops;
	rmidi->निजी_data = umidi;
	rmidi->निजी_मुक्त = snd_usbmidi_rawmidi_मुक्त;
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT,
			    &snd_usbmidi_output_ops);
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_INPUT,
			    &snd_usbmidi_input_ops);

	umidi->rmidi = rmidi;
	वापस 0;
पूर्ण

/*
 * Temporarily stop input.
 */
व्योम snd_usbmidi_input_stop(काष्ठा list_head *p)
अणु
	काष्ठा snd_usb_midi *umidi;
	अचिन्हित पूर्णांक i, j;

	umidi = list_entry(p, काष्ठा snd_usb_midi, list);
	अगर (!umidi->input_running)
		वापस;
	क्रम (i = 0; i < MIDI_MAX_ENDPOINTS; ++i) अणु
		काष्ठा snd_usb_midi_endpoपूर्णांक *ep = &umidi->endpoपूर्णांकs[i];
		अगर (ep->in)
			क्रम (j = 0; j < INPUT_URBS; ++j)
				usb_समाप्त_urb(ep->in->urbs[j]);
	पूर्ण
	umidi->input_running = 0;
पूर्ण
EXPORT_SYMBOL(snd_usbmidi_input_stop);

अटल व्योम snd_usbmidi_input_start_ep(काष्ठा snd_usb_midi *umidi,
				       काष्ठा snd_usb_midi_in_endpoपूर्णांक *ep)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ flags;

	अगर (!ep)
		वापस;
	क्रम (i = 0; i < INPUT_URBS; ++i) अणु
		काष्ठा urb *urb = ep->urbs[i];
		spin_lock_irqsave(&umidi->disc_lock, flags);
		अगर (!atomic_पढ़ो(&urb->use_count)) अणु
			urb->dev = ep->umidi->dev;
			snd_usbmidi_submit_urb(urb, GFP_ATOMIC);
		पूर्ण
		spin_unlock_irqrestore(&umidi->disc_lock, flags);
	पूर्ण
पूर्ण

/*
 * Resume input after a call to snd_usbmidi_input_stop().
 */
व्योम snd_usbmidi_input_start(काष्ठा list_head *p)
अणु
	काष्ठा snd_usb_midi *umidi;
	पूर्णांक i;

	umidi = list_entry(p, काष्ठा snd_usb_midi, list);
	अगर (umidi->input_running || !umidi->खोलोed[1])
		वापस;
	क्रम (i = 0; i < MIDI_MAX_ENDPOINTS; ++i)
		snd_usbmidi_input_start_ep(umidi, umidi->endpoपूर्णांकs[i].in);
	umidi->input_running = 1;
पूर्ण
EXPORT_SYMBOL(snd_usbmidi_input_start);

/*
 * Prepare क्रम suspend. Typically called from the USB suspend callback.
 */
व्योम snd_usbmidi_suspend(काष्ठा list_head *p)
अणु
	काष्ठा snd_usb_midi *umidi;

	umidi = list_entry(p, काष्ठा snd_usb_midi, list);
	mutex_lock(&umidi->mutex);
	snd_usbmidi_input_stop(p);
	mutex_unlock(&umidi->mutex);
पूर्ण
EXPORT_SYMBOL(snd_usbmidi_suspend);

/*
 * Resume. Typically called from the USB resume callback.
 */
व्योम snd_usbmidi_resume(काष्ठा list_head *p)
अणु
	काष्ठा snd_usb_midi *umidi;

	umidi = list_entry(p, काष्ठा snd_usb_midi, list);
	mutex_lock(&umidi->mutex);
	snd_usbmidi_input_start(p);
	mutex_unlock(&umidi->mutex);
पूर्ण
EXPORT_SYMBOL(snd_usbmidi_resume);

/*
 * Creates and रेजिस्टरs everything needed क्रम a MIDI streaming पूर्णांकerface.
 */
पूर्णांक __snd_usbmidi_create(काष्ठा snd_card *card,
			 काष्ठा usb_पूर्णांकerface *अगरace,
			 काष्ठा list_head *midi_list,
			 स्थिर काष्ठा snd_usb_audio_quirk *quirk,
			 अचिन्हित पूर्णांक usb_id)
अणु
	काष्ठा snd_usb_midi *umidi;
	काष्ठा snd_usb_midi_endpoपूर्णांक_info endpoपूर्णांकs[MIDI_MAX_ENDPOINTS];
	पूर्णांक out_ports, in_ports;
	पूर्णांक i, err;

	umidi = kzalloc(माप(*umidi), GFP_KERNEL);
	अगर (!umidi)
		वापस -ENOMEM;
	umidi->dev = पूर्णांकerface_to_usbdev(अगरace);
	umidi->card = card;
	umidi->अगरace = अगरace;
	umidi->quirk = quirk;
	umidi->usb_protocol_ops = &snd_usbmidi_standard_ops;
	spin_lock_init(&umidi->disc_lock);
	init_rwsem(&umidi->disc_rwsem);
	mutex_init(&umidi->mutex);
	अगर (!usb_id)
		usb_id = USB_ID(le16_to_cpu(umidi->dev->descriptor.idVenकरोr),
			       le16_to_cpu(umidi->dev->descriptor.idProduct));
	umidi->usb_id = usb_id;
	समयr_setup(&umidi->error_समयr, snd_usbmidi_error_समयr, 0);

	/* detect the endpoपूर्णांक(s) to use */
	स_रखो(endpoपूर्णांकs, 0, माप(endpoपूर्णांकs));
	चयन (quirk ? quirk->type : QUIRK_MIDI_STANDARD_INTERFACE) अणु
	हाल QUIRK_MIDI_STANDARD_INTERFACE:
		err = snd_usbmidi_get_ms_info(umidi, endpoपूर्णांकs);
		अगर (umidi->usb_id == USB_ID(0x0763, 0x0150)) /* M-Audio Uno */
			umidi->usb_protocol_ops =
				&snd_usbmidi_maudio_broken_running_status_ops;
		अवरोध;
	हाल QUIRK_MIDI_US122L:
		umidi->usb_protocol_ops = &snd_usbmidi_122l_ops;
		fallthrough;
	हाल QUIRK_MIDI_FIXED_ENDPOINT:
		स_नकल(&endpoपूर्णांकs[0], quirk->data,
		       माप(काष्ठा snd_usb_midi_endpoपूर्णांक_info));
		err = snd_usbmidi_detect_endpoपूर्णांकs(umidi, &endpoपूर्णांकs[0], 1);
		अवरोध;
	हाल QUIRK_MIDI_YAMAHA:
		err = snd_usbmidi_detect_yamaha(umidi, &endpoपूर्णांकs[0]);
		अवरोध;
	हाल QUIRK_MIDI_ROLAND:
		err = snd_usbmidi_detect_roland(umidi, &endpoपूर्णांकs[0]);
		अवरोध;
	हाल QUIRK_MIDI_MIDIMAN:
		umidi->usb_protocol_ops = &snd_usbmidi_midiman_ops;
		स_नकल(&endpoपूर्णांकs[0], quirk->data,
		       माप(काष्ठा snd_usb_midi_endpoपूर्णांक_info));
		err = 0;
		अवरोध;
	हाल QUIRK_MIDI_NOVATION:
		umidi->usb_protocol_ops = &snd_usbmidi_novation_ops;
		err = snd_usbmidi_detect_per_port_endpoपूर्णांकs(umidi, endpoपूर्णांकs);
		अवरोध;
	हाल QUIRK_MIDI_RAW_BYTES:
		umidi->usb_protocol_ops = &snd_usbmidi_raw_ops;
		/*
		 * Interface 1 contains isochronous endpoपूर्णांकs, but with the same
		 * numbers as in पूर्णांकerface 0.  Since it is पूर्णांकerface 1 that the
		 * USB core has most recently seen, these descriptors are now
		 * associated with the endpoपूर्णांक numbers.  This will foul up our
		 * attempts to submit bulk/पूर्णांकerrupt URBs to the endpoपूर्णांकs in
		 * पूर्णांकerface 0, so we have to make sure that the USB core looks
		 * again at पूर्णांकerface 0 by calling usb_set_पूर्णांकerface() on it.
		 */
		अगर (umidi->usb_id == USB_ID(0x07fd, 0x0001)) /* MOTU Fastlane */
			usb_set_पूर्णांकerface(umidi->dev, 0, 0);
		err = snd_usbmidi_detect_per_port_endpoपूर्णांकs(umidi, endpoपूर्णांकs);
		अवरोध;
	हाल QUIRK_MIDI_EMAGIC:
		umidi->usb_protocol_ops = &snd_usbmidi_emagic_ops;
		स_नकल(&endpoपूर्णांकs[0], quirk->data,
		       माप(काष्ठा snd_usb_midi_endpoपूर्णांक_info));
		err = snd_usbmidi_detect_endpoपूर्णांकs(umidi, &endpoपूर्णांकs[0], 1);
		अवरोध;
	हाल QUIRK_MIDI_CME:
		umidi->usb_protocol_ops = &snd_usbmidi_cme_ops;
		err = snd_usbmidi_detect_per_port_endpoपूर्णांकs(umidi, endpoपूर्णांकs);
		अवरोध;
	हाल QUIRK_MIDI_AKAI:
		umidi->usb_protocol_ops = &snd_usbmidi_akai_ops;
		err = snd_usbmidi_detect_per_port_endpoपूर्णांकs(umidi, endpoपूर्णांकs);
		/* endpoपूर्णांक 1 is input-only */
		endpoपूर्णांकs[1].out_cables = 0;
		अवरोध;
	हाल QUIRK_MIDI_FTDI:
		umidi->usb_protocol_ops = &snd_usbmidi_ftdi_ops;

		/* set baud rate to 31250 (48 MHz / 16 / 96) */
		err = usb_control_msg(umidi->dev, usb_sndctrlpipe(umidi->dev, 0),
				      3, 0x40, 0x60, 0, शून्य, 0, 1000);
		अगर (err < 0)
			अवरोध;

		err = snd_usbmidi_detect_per_port_endpoपूर्णांकs(umidi, endpoपूर्णांकs);
		अवरोध;
	हाल QUIRK_MIDI_CH345:
		umidi->usb_protocol_ops = &snd_usbmidi_ch345_broken_sysex_ops;
		err = snd_usbmidi_detect_per_port_endpoपूर्णांकs(umidi, endpoपूर्णांकs);
		अवरोध;
	शेष:
		dev_err(&umidi->dev->dev, "invalid quirk type %d\n",
			quirk->type);
		err = -ENXIO;
		अवरोध;
	पूर्ण
	अगर (err < 0)
		जाओ मुक्त_midi;

	/* create rawmidi device */
	out_ports = 0;
	in_ports = 0;
	क्रम (i = 0; i < MIDI_MAX_ENDPOINTS; ++i) अणु
		out_ports += hweight16(endpoपूर्णांकs[i].out_cables);
		in_ports += hweight16(endpoपूर्णांकs[i].in_cables);
	पूर्ण
	err = snd_usbmidi_create_rawmidi(umidi, out_ports, in_ports);
	अगर (err < 0)
		जाओ मुक्त_midi;

	/* create endpoपूर्णांक/port काष्ठाures */
	अगर (quirk && quirk->type == QUIRK_MIDI_MIDIMAN)
		err = snd_usbmidi_create_endpoपूर्णांकs_midiman(umidi, &endpoपूर्णांकs[0]);
	अन्यथा
		err = snd_usbmidi_create_endpoपूर्णांकs(umidi, endpoपूर्णांकs);
	अगर (err < 0)
		जाओ निकास;

	usb_स्वतःpm_get_पूर्णांकerface_no_resume(umidi->अगरace);

	list_add_tail(&umidi->list, midi_list);
	वापस 0;

मुक्त_midi:
	kमुक्त(umidi);
निकास:
	वापस err;
पूर्ण
EXPORT_SYMBOL(__snd_usbmidi_create);
