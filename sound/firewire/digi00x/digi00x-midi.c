<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * digi00x-midi.h - a part of driver क्रम Digidesign Digi 002/003 family
 *
 * Copyright (c) 2014-2015 Takashi Sakamoto
 */

#समावेश "digi00x.h"

अटल पूर्णांक midi_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_dg00x *dg00x = substream->rmidi->निजी_data;
	पूर्णांक err;

	err = snd_dg00x_stream_lock_try(dg00x);
	अगर (err < 0)
		वापस err;

	mutex_lock(&dg00x->mutex);
	err = snd_dg00x_stream_reserve_duplex(dg00x, 0, 0, 0);
	अगर (err >= 0) अणु
		++dg00x->substreams_counter;
		err = snd_dg00x_stream_start_duplex(dg00x);
		अगर (err < 0)
			--dg00x->substreams_counter;
	पूर्ण
	mutex_unlock(&dg00x->mutex);
	अगर (err < 0)
		snd_dg00x_stream_lock_release(dg00x);

	वापस err;
पूर्ण

अटल पूर्णांक midi_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_dg00x *dg00x = substream->rmidi->निजी_data;

	mutex_lock(&dg00x->mutex);
	--dg00x->substreams_counter;
	snd_dg00x_stream_stop_duplex(dg00x);
	mutex_unlock(&dg00x->mutex);

	snd_dg00x_stream_lock_release(dg00x);
	वापस 0;
पूर्ण

अटल व्योम midi_capture_trigger(काष्ठा snd_rawmidi_substream *substream,
				 पूर्णांक up)
अणु
	काष्ठा snd_dg00x *dg00x = substream->rmidi->निजी_data;
	अचिन्हित पूर्णांक port;
	अचिन्हित दीर्घ flags;

	अगर (substream->rmidi->device == 0)
		port = substream->number;
	अन्यथा
		port = 2;

	spin_lock_irqsave(&dg00x->lock, flags);

	अगर (up)
		amdtp_करोt_midi_trigger(&dg00x->tx_stream, port, substream);
	अन्यथा
		amdtp_करोt_midi_trigger(&dg00x->tx_stream, port, शून्य);

	spin_unlock_irqrestore(&dg00x->lock, flags);
पूर्ण

अटल व्योम midi_playback_trigger(काष्ठा snd_rawmidi_substream *substream,
				  पूर्णांक up)
अणु
	काष्ठा snd_dg00x *dg00x = substream->rmidi->निजी_data;
	अचिन्हित पूर्णांक port;
	अचिन्हित दीर्घ flags;

	अगर (substream->rmidi->device == 0)
		port = substream->number;
	अन्यथा
		port = 2;

	spin_lock_irqsave(&dg00x->lock, flags);

	अगर (up)
		amdtp_करोt_midi_trigger(&dg00x->rx_stream, port, substream);
	अन्यथा
		amdtp_करोt_midi_trigger(&dg00x->rx_stream, port, शून्य);

	spin_unlock_irqrestore(&dg00x->lock, flags);
पूर्ण

अटल व्योम set_substream_names(काष्ठा snd_dg00x *dg00x,
				काष्ठा snd_rawmidi *rmidi, bool is_console)
अणु
	काष्ठा snd_rawmidi_substream *subs;
	काष्ठा snd_rawmidi_str *str;
	पूर्णांक i;

	क्रम (i = 0; i < 2; ++i) अणु
		str = &rmidi->streams[i];

		list_क्रम_each_entry(subs, &str->substreams, list) अणु
			अगर (!is_console) अणु
				snम_लिखो(subs->name, माप(subs->name),
					 "%s MIDI %d",
					 dg00x->card->लघुname,
					 subs->number + 1);
			पूर्ण अन्यथा अणु
				snम_लिखो(subs->name, माप(subs->name),
					 "%s control",
					 dg00x->card->लघुname);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक add_substream_pair(काष्ठा snd_dg00x *dg00x, अचिन्हित पूर्णांक out_ports,
			      अचिन्हित पूर्णांक in_ports, bool is_console)
अणु
	अटल स्थिर काष्ठा snd_rawmidi_ops capture_ops = अणु
		.खोलो = midi_खोलो,
		.बंद = midi_बंद,
		.trigger = midi_capture_trigger,
	पूर्ण;
	अटल स्थिर काष्ठा snd_rawmidi_ops playback_ops = अणु
		.खोलो = midi_खोलो,
		.बंद = midi_बंद,
		.trigger = midi_playback_trigger,
	पूर्ण;
	स्थिर अक्षर *label;
	काष्ठा snd_rawmidi *rmidi;
	पूर्णांक err;

	/* Add physical midi ports. */
	err = snd_rawmidi_new(dg00x->card, dg00x->card->driver, is_console,
			      out_ports, in_ports, &rmidi);
	अगर (err < 0)
		वापस err;
	rmidi->निजी_data = dg00x;

	अगर (!is_console)
		label = "%s control";
	अन्यथा
		label = "%s MIDI";
	snम_लिखो(rmidi->name, माप(rmidi->name), label,
		 dg00x->card->लघुname);

	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT, &playback_ops);
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_INPUT, &capture_ops);

	rmidi->info_flags |= SNDRV_RAWMIDI_INFO_INPUT |
			     SNDRV_RAWMIDI_INFO_OUTPUT |
			     SNDRV_RAWMIDI_INFO_DUPLEX;

	set_substream_names(dg00x, rmidi, is_console);

	वापस 0;
पूर्ण

पूर्णांक snd_dg00x_create_midi_devices(काष्ठा snd_dg00x *dg00x)
अणु
	पूर्णांक err;

	/* Add physical midi ports. */
	err = add_substream_pair(dg00x, DOT_MIDI_OUT_PORTS, DOT_MIDI_IN_PORTS,
				 false);
	अगर (err < 0)
		वापस err;

	अगर (dg00x->is_console)
		err = add_substream_pair(dg00x, 1, 1, true);

	वापस err;
पूर्ण
