<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Linux driver क्रम TerraTec DMX 6Fire USB
 *
 * Rawmidi driver
 *
 * Author:	Torsten Schenk <torsten.schenk@zoho.com>
 * Created:	Jan 01, 2011
 * Copyright:	(C) Torsten Schenk
 */

#समावेश <sound/rawmidi.h>

#समावेश "midi.h"
#समावेश "chip.h"
#समावेश "comm.h"

क्रमागत अणु
	MIDI_बफ_मानE = 64
पूर्ण;

अटल व्योम usb6fire_midi_out_handler(काष्ठा urb *urb)
अणु
	काष्ठा midi_runसमय *rt = urb->context;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rt->out_lock, flags);

	अगर (rt->out) अणु
		ret = snd_rawmidi_transmit(rt->out, rt->out_buffer + 4,
				MIDI_बफ_मानE - 4);
		अगर (ret > 0) अणु /* more data available, send next packet */
			rt->out_buffer[1] = ret + 2;
			rt->out_buffer[3] = rt->out_serial++;
			urb->transfer_buffer_length = ret + 4;

			ret = usb_submit_urb(urb, GFP_ATOMIC);
			अगर (ret < 0)
				dev_err(&urb->dev->dev,
					"midi out urb submit failed: %d\n",
					ret);
		पूर्ण अन्यथा /* no more data to transmit */
			rt->out = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&rt->out_lock, flags);
पूर्ण

अटल व्योम usb6fire_midi_in_received(
		काष्ठा midi_runसमय *rt, u8 *data, पूर्णांक length)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rt->in_lock, flags);
	अगर (rt->in)
		snd_rawmidi_receive(rt->in, data, length);
	spin_unlock_irqrestore(&rt->in_lock, flags);
पूर्ण

अटल पूर्णांक usb6fire_midi_out_खोलो(काष्ठा snd_rawmidi_substream *alsa_sub)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक usb6fire_midi_out_बंद(काष्ठा snd_rawmidi_substream *alsa_sub)
अणु
	वापस 0;
पूर्ण

अटल व्योम usb6fire_midi_out_trigger(
		काष्ठा snd_rawmidi_substream *alsa_sub, पूर्णांक up)
अणु
	काष्ठा midi_runसमय *rt = alsa_sub->rmidi->निजी_data;
	काष्ठा urb *urb = &rt->out_urb;
	__s8 ret;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rt->out_lock, flags);
	अगर (up) अणु /* start transfer */
		अगर (rt->out) अणु /* we are alपढ़ोy transmitting so just वापस */
			spin_unlock_irqrestore(&rt->out_lock, flags);
			वापस;
		पूर्ण

		ret = snd_rawmidi_transmit(alsa_sub, rt->out_buffer + 4,
				MIDI_बफ_मानE - 4);
		अगर (ret > 0) अणु
			rt->out_buffer[1] = ret + 2;
			rt->out_buffer[3] = rt->out_serial++;
			urb->transfer_buffer_length = ret + 4;

			ret = usb_submit_urb(urb, GFP_ATOMIC);
			अगर (ret < 0)
				dev_err(&urb->dev->dev,
					"midi out urb submit failed: %d\n",
					ret);
			अन्यथा
				rt->out = alsa_sub;
		पूर्ण
	पूर्ण अन्यथा अगर (rt->out == alsa_sub)
		rt->out = शून्य;
	spin_unlock_irqrestore(&rt->out_lock, flags);
पूर्ण

अटल व्योम usb6fire_midi_out_drain(काष्ठा snd_rawmidi_substream *alsa_sub)
अणु
	काष्ठा midi_runसमय *rt = alsa_sub->rmidi->निजी_data;
	पूर्णांक retry = 0;

	जबतक (rt->out && retry++ < 100)
		msleep(10);
पूर्ण

अटल पूर्णांक usb6fire_midi_in_खोलो(काष्ठा snd_rawmidi_substream *alsa_sub)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक usb6fire_midi_in_बंद(काष्ठा snd_rawmidi_substream *alsa_sub)
अणु
	वापस 0;
पूर्ण

अटल व्योम usb6fire_midi_in_trigger(
		काष्ठा snd_rawmidi_substream *alsa_sub, पूर्णांक up)
अणु
	काष्ठा midi_runसमय *rt = alsa_sub->rmidi->निजी_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rt->in_lock, flags);
	अगर (up)
		rt->in = alsa_sub;
	अन्यथा
		rt->in = शून्य;
	spin_unlock_irqrestore(&rt->in_lock, flags);
पूर्ण

अटल स्थिर काष्ठा snd_rawmidi_ops out_ops = अणु
	.खोलो = usb6fire_midi_out_खोलो,
	.बंद = usb6fire_midi_out_बंद,
	.trigger = usb6fire_midi_out_trigger,
	.drain = usb6fire_midi_out_drain
पूर्ण;

अटल स्थिर काष्ठा snd_rawmidi_ops in_ops = अणु
	.खोलो = usb6fire_midi_in_खोलो,
	.बंद = usb6fire_midi_in_बंद,
	.trigger = usb6fire_midi_in_trigger
पूर्ण;

पूर्णांक usb6fire_midi_init(काष्ठा sfire_chip *chip)
अणु
	पूर्णांक ret;
	काष्ठा midi_runसमय *rt = kzalloc(माप(काष्ठा midi_runसमय),
			GFP_KERNEL);
	काष्ठा comm_runसमय *comm_rt = chip->comm;

	अगर (!rt)
		वापस -ENOMEM;

	rt->out_buffer = kzalloc(MIDI_बफ_मानE, GFP_KERNEL);
	अगर (!rt->out_buffer) अणु
		kमुक्त(rt);
		वापस -ENOMEM;
	पूर्ण

	rt->chip = chip;
	rt->in_received = usb6fire_midi_in_received;
	rt->out_buffer[0] = 0x80; /* 'send midi' command */
	rt->out_buffer[1] = 0x00; /* size of data */
	rt->out_buffer[2] = 0x00; /* always 0 */
	spin_lock_init(&rt->in_lock);
	spin_lock_init(&rt->out_lock);

	comm_rt->init_urb(comm_rt, &rt->out_urb, rt->out_buffer, rt,
			usb6fire_midi_out_handler);

	ret = snd_rawmidi_new(chip->card, "6FireUSB", 0, 1, 1, &rt->instance);
	अगर (ret < 0) अणु
		kमुक्त(rt->out_buffer);
		kमुक्त(rt);
		dev_err(&chip->dev->dev, "unable to create midi.\n");
		वापस ret;
	पूर्ण
	rt->instance->निजी_data = rt;
	म_नकल(rt->instance->name, "DMX6FireUSB MIDI");
	rt->instance->info_flags = SNDRV_RAWMIDI_INFO_OUTPUT |
			SNDRV_RAWMIDI_INFO_INPUT |
			SNDRV_RAWMIDI_INFO_DUPLEX;
	snd_rawmidi_set_ops(rt->instance, SNDRV_RAWMIDI_STREAM_OUTPUT,
			&out_ops);
	snd_rawmidi_set_ops(rt->instance, SNDRV_RAWMIDI_STREAM_INPUT,
			&in_ops);

	chip->midi = rt;
	वापस 0;
पूर्ण

व्योम usb6fire_midi_पात(काष्ठा sfire_chip *chip)
अणु
	काष्ठा midi_runसमय *rt = chip->midi;

	अगर (rt)
		usb_poison_urb(&rt->out_urb);
पूर्ण

व्योम usb6fire_midi_destroy(काष्ठा sfire_chip *chip)
अणु
	काष्ठा midi_runसमय *rt = chip->midi;

	kमुक्त(rt->out_buffer);
	kमुक्त(rt);
	chip->midi = शून्य;
पूर्ण
