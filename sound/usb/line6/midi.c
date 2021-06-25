<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Line 6 Linux USB driver
 *
 * Copyright (C) 2004-2010 Markus Grabner (grabner@icg.tugraz.at)
 */

#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <linux/export.h>
#समावेश <sound/core.h>
#समावेश <sound/rawmidi.h>

#समावेश "driver.h"
#समावेश "midi.h"

#घोषणा line6_rawmidi_substream_midi(substream) \
	((काष्ठा snd_line6_midi *)((substream)->rmidi->निजी_data))

अटल पूर्णांक send_midi_async(काष्ठा usb_line6 *line6, अचिन्हित अक्षर *data,
			   पूर्णांक length);

/*
	Pass data received via USB to MIDI.
*/
व्योम line6_midi_receive(काष्ठा usb_line6 *line6, अचिन्हित अक्षर *data,
			पूर्णांक length)
अणु
	अगर (line6->line6midi->substream_receive)
		snd_rawmidi_receive(line6->line6midi->substream_receive,
				    data, length);
पूर्ण

/*
	Read data from MIDI buffer and transmit them via USB.
*/
अटल व्योम line6_midi_transmit(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा usb_line6 *line6 =
	    line6_rawmidi_substream_midi(substream)->line6;
	काष्ठा snd_line6_midi *line6midi = line6->line6midi;
	काष्ठा midi_buffer *mb = &line6midi->midibuf_out;
	अचिन्हित अक्षर chunk[LINE6_FALLBACK_MAXPACKETSIZE];
	पूर्णांक req, करोne;

	क्रम (;;) अणु
		req = min(line6_midibuf_bytes_मुक्त(mb), line6->max_packet_size);
		करोne = snd_rawmidi_transmit_peek(substream, chunk, req);

		अगर (करोne == 0)
			अवरोध;

		line6_midibuf_ग_लिखो(mb, chunk, करोne);
		snd_rawmidi_transmit_ack(substream, करोne);
	पूर्ण

	क्रम (;;) अणु
		करोne = line6_midibuf_पढ़ो(mb, chunk,
					  LINE6_FALLBACK_MAXPACKETSIZE);

		अगर (करोne == 0)
			अवरोध;

		send_midi_async(line6, chunk, करोne);
	पूर्ण
पूर्ण

/*
	Notअगरication of completion of MIDI transmission.
*/
अटल व्योम midi_sent(काष्ठा urb *urb)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक status;
	पूर्णांक num;
	काष्ठा usb_line6 *line6 = (काष्ठा usb_line6 *)urb->context;

	status = urb->status;
	kमुक्त(urb->transfer_buffer);
	usb_मुक्त_urb(urb);

	अगर (status == -ESHUTDOWN)
		वापस;

	spin_lock_irqsave(&line6->line6midi->lock, flags);
	num = --line6->line6midi->num_active_send_urbs;

	अगर (num == 0) अणु
		line6_midi_transmit(line6->line6midi->substream_transmit);
		num = line6->line6midi->num_active_send_urbs;
	पूर्ण

	अगर (num == 0)
		wake_up(&line6->line6midi->send_रुको);

	spin_unlock_irqrestore(&line6->line6midi->lock, flags);
पूर्ण

/*
	Send an asynchronous MIDI message.
	Assumes that line6->line6midi->lock is held
	(i.e., this function is serialized).
*/
अटल पूर्णांक send_midi_async(काष्ठा usb_line6 *line6, अचिन्हित अक्षर *data,
			   पूर्णांक length)
अणु
	काष्ठा urb *urb;
	पूर्णांक retval;
	अचिन्हित अक्षर *transfer_buffer;

	urb = usb_alloc_urb(0, GFP_ATOMIC);

	अगर (urb == शून्य)
		वापस -ENOMEM;

	transfer_buffer = kmemdup(data, length, GFP_ATOMIC);

	अगर (transfer_buffer == शून्य) अणु
		usb_मुक्त_urb(urb);
		वापस -ENOMEM;
	पूर्ण

	usb_fill_पूर्णांक_urb(urb, line6->usbdev,
			 usb_sndपूर्णांकpipe(line6->usbdev,
					 line6->properties->ep_ctrl_w),
			 transfer_buffer, length, midi_sent, line6,
			 line6->पूर्णांकerval);
	urb->actual_length = 0;
	retval = usb_urb_ep_type_check(urb);
	अगर (retval < 0)
		जाओ error;

	retval = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (retval < 0)
		जाओ error;

	++line6->line6midi->num_active_send_urbs;
	वापस 0;

 error:
	dev_err(line6->अगरcdev, "usb_submit_urb failed\n");
	usb_मुक्त_urb(urb);
	वापस retval;
पूर्ण

अटल पूर्णांक line6_midi_output_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक line6_midi_output_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	वापस 0;
पूर्ण

अटल व्योम line6_midi_output_trigger(काष्ठा snd_rawmidi_substream *substream,
				      पूर्णांक up)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा usb_line6 *line6 =
	    line6_rawmidi_substream_midi(substream)->line6;

	line6->line6midi->substream_transmit = substream;
	spin_lock_irqsave(&line6->line6midi->lock, flags);

	अगर (line6->line6midi->num_active_send_urbs == 0)
		line6_midi_transmit(substream);

	spin_unlock_irqrestore(&line6->line6midi->lock, flags);
पूर्ण

अटल व्योम line6_midi_output_drain(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा usb_line6 *line6 =
	    line6_rawmidi_substream_midi(substream)->line6;
	काष्ठा snd_line6_midi *midi = line6->line6midi;

	रुको_event_पूर्णांकerruptible(midi->send_रुको,
				 midi->num_active_send_urbs == 0);
पूर्ण

अटल पूर्णांक line6_midi_input_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक line6_midi_input_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	वापस 0;
पूर्ण

अटल व्योम line6_midi_input_trigger(काष्ठा snd_rawmidi_substream *substream,
				     पूर्णांक up)
अणु
	काष्ठा usb_line6 *line6 =
	    line6_rawmidi_substream_midi(substream)->line6;

	अगर (up)
		line6->line6midi->substream_receive = substream;
	अन्यथा
		line6->line6midi->substream_receive = शून्य;
पूर्ण

अटल स्थिर काष्ठा snd_rawmidi_ops line6_midi_output_ops = अणु
	.खोलो = line6_midi_output_खोलो,
	.बंद = line6_midi_output_बंद,
	.trigger = line6_midi_output_trigger,
	.drain = line6_midi_output_drain,
पूर्ण;

अटल स्थिर काष्ठा snd_rawmidi_ops line6_midi_input_ops = अणु
	.खोलो = line6_midi_input_खोलो,
	.बंद = line6_midi_input_बंद,
	.trigger = line6_midi_input_trigger,
पूर्ण;

/* Create a MIDI device */
अटल पूर्णांक snd_line6_new_midi(काष्ठा usb_line6 *line6,
			      काष्ठा snd_rawmidi **rmidi_ret)
अणु
	काष्ठा snd_rawmidi *rmidi;
	पूर्णांक err;

	err = snd_rawmidi_new(line6->card, "Line 6 MIDI", 0, 1, 1, rmidi_ret);
	अगर (err < 0)
		वापस err;

	rmidi = *rmidi_ret;
	म_नकल(rmidi->id, line6->properties->id);
	म_नकल(rmidi->name, line6->properties->name);

	rmidi->info_flags =
	    SNDRV_RAWMIDI_INFO_OUTPUT |
	    SNDRV_RAWMIDI_INFO_INPUT | SNDRV_RAWMIDI_INFO_DUPLEX;

	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT,
			    &line6_midi_output_ops);
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_INPUT,
			    &line6_midi_input_ops);
	वापस 0;
पूर्ण

/* MIDI device deकाष्ठाor */
अटल व्योम snd_line6_midi_मुक्त(काष्ठा snd_rawmidi *rmidi)
अणु
	काष्ठा snd_line6_midi *line6midi = rmidi->निजी_data;

	line6_midibuf_destroy(&line6midi->midibuf_in);
	line6_midibuf_destroy(&line6midi->midibuf_out);
	kमुक्त(line6midi);
पूर्ण

/*
	Initialize the Line 6 MIDI subप्रणाली.
*/
पूर्णांक line6_init_midi(काष्ठा usb_line6 *line6)
अणु
	पूर्णांक err;
	काष्ठा snd_rawmidi *rmidi;
	काष्ठा snd_line6_midi *line6midi;

	अगर (!(line6->properties->capabilities & LINE6_CAP_CONTROL_MIDI)) अणु
		/* skip MIDI initialization and report success */
		वापस 0;
	पूर्ण

	err = snd_line6_new_midi(line6, &rmidi);
	अगर (err < 0)
		वापस err;

	line6midi = kzalloc(माप(काष्ठा snd_line6_midi), GFP_KERNEL);
	अगर (!line6midi)
		वापस -ENOMEM;

	rmidi->निजी_data = line6midi;
	rmidi->निजी_मुक्त = snd_line6_midi_मुक्त;

	init_रुकोqueue_head(&line6midi->send_रुको);
	spin_lock_init(&line6midi->lock);
	line6midi->line6 = line6;

	err = line6_midibuf_init(&line6midi->midibuf_in, MIDI_BUFFER_SIZE, 0);
	अगर (err < 0)
		वापस err;

	err = line6_midibuf_init(&line6midi->midibuf_out, MIDI_BUFFER_SIZE, 1);
	अगर (err < 0)
		वापस err;

	line6->line6midi = line6midi;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(line6_init_midi);
