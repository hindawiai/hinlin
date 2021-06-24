<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Copyright (c) 2006,2007 Daniel Mack
*/

#समावेश <linux/device.h>
#समावेश <linux/usb.h>
#समावेश <linux/gfp.h>
#समावेश <sound/rawmidi.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>

#समावेश "device.h"
#समावेश "midi.h"

अटल पूर्णांक snd_usb_caiaq_midi_input_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक snd_usb_caiaq_midi_input_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	वापस 0;
पूर्ण

अटल व्योम snd_usb_caiaq_midi_input_trigger(काष्ठा snd_rawmidi_substream *substream, पूर्णांक up)
अणु
	काष्ठा snd_usb_caiaqdev *cdev = substream->rmidi->निजी_data;

	अगर (!cdev)
		वापस;

	cdev->midi_receive_substream = up ? substream : शून्य;
पूर्ण


अटल पूर्णांक snd_usb_caiaq_midi_output_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक snd_usb_caiaq_midi_output_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_usb_caiaqdev *cdev = substream->rmidi->निजी_data;
	अगर (cdev->midi_out_active) अणु
		usb_समाप्त_urb(&cdev->midi_out_urb);
		cdev->midi_out_active = 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम snd_usb_caiaq_midi_send(काष्ठा snd_usb_caiaqdev *cdev,
				    काष्ठा snd_rawmidi_substream *substream)
अणु
	पूर्णांक len, ret;
	काष्ठा device *dev = caiaqdev_to_dev(cdev);

	cdev->midi_out_buf[0] = EP1_CMD_MIDI_WRITE;
	cdev->midi_out_buf[1] = 0; /* port */
	len = snd_rawmidi_transmit(substream, cdev->midi_out_buf + 3,
				   EP1_बफ_मानE - 3);

	अगर (len <= 0)
		वापस;

	cdev->midi_out_buf[2] = len;
	cdev->midi_out_urb.transfer_buffer_length = len+3;

	ret = usb_submit_urb(&cdev->midi_out_urb, GFP_ATOMIC);
	अगर (ret < 0)
		dev_err(dev,
			"snd_usb_caiaq_midi_send(%p): usb_submit_urb() failed,"
			"ret=%d, len=%d\n", substream, ret, len);
	अन्यथा
		cdev->midi_out_active = 1;
पूर्ण

अटल व्योम snd_usb_caiaq_midi_output_trigger(काष्ठा snd_rawmidi_substream *substream, पूर्णांक up)
अणु
	काष्ठा snd_usb_caiaqdev *cdev = substream->rmidi->निजी_data;

	अगर (up) अणु
		cdev->midi_out_substream = substream;
		अगर (!cdev->midi_out_active)
			snd_usb_caiaq_midi_send(cdev, substream);
	पूर्ण अन्यथा अणु
		cdev->midi_out_substream = शून्य;
	पूर्ण
पूर्ण


अटल स्थिर काष्ठा snd_rawmidi_ops snd_usb_caiaq_midi_output =
अणु
	.खोलो =		snd_usb_caiaq_midi_output_खोलो,
	.बंद =	snd_usb_caiaq_midi_output_बंद,
	.trigger =      snd_usb_caiaq_midi_output_trigger,
पूर्ण;

अटल स्थिर काष्ठा snd_rawmidi_ops snd_usb_caiaq_midi_input =
अणु
	.खोलो =		snd_usb_caiaq_midi_input_खोलो,
	.बंद =	snd_usb_caiaq_midi_input_बंद,
	.trigger =      snd_usb_caiaq_midi_input_trigger,
पूर्ण;

व्योम snd_usb_caiaq_midi_handle_input(काष्ठा snd_usb_caiaqdev *cdev,
				     पूर्णांक port, स्थिर अक्षर *buf, पूर्णांक len)
अणु
	अगर (!cdev->midi_receive_substream)
		वापस;

	snd_rawmidi_receive(cdev->midi_receive_substream, buf, len);
पूर्ण

पूर्णांक snd_usb_caiaq_midi_init(काष्ठा snd_usb_caiaqdev *device)
अणु
	पूर्णांक ret;
	काष्ठा snd_rawmidi *rmidi;

	ret = snd_rawmidi_new(device->chip.card, device->product_name, 0,
					device->spec.num_midi_out,
					device->spec.num_midi_in,
					&rmidi);

	अगर (ret < 0)
		वापस ret;

	strscpy(rmidi->name, device->product_name, माप(rmidi->name));

	rmidi->info_flags = SNDRV_RAWMIDI_INFO_DUPLEX;
	rmidi->निजी_data = device;

	अगर (device->spec.num_midi_out > 0) अणु
		rmidi->info_flags |= SNDRV_RAWMIDI_INFO_OUTPUT;
		snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT,
				    &snd_usb_caiaq_midi_output);
	पूर्ण

	अगर (device->spec.num_midi_in > 0) अणु
		rmidi->info_flags |= SNDRV_RAWMIDI_INFO_INPUT;
		snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_INPUT,
				    &snd_usb_caiaq_midi_input);
	पूर्ण

	device->rmidi = rmidi;

	वापस 0;
पूर्ण

व्योम snd_usb_caiaq_midi_output_करोne(काष्ठा urb* urb)
अणु
	काष्ठा snd_usb_caiaqdev *cdev = urb->context;

	cdev->midi_out_active = 0;
	अगर (urb->status != 0)
		वापस;

	अगर (!cdev->midi_out_substream)
		वापस;

	snd_usb_caiaq_midi_send(cdev, cdev->midi_out_substream);
पूर्ण
