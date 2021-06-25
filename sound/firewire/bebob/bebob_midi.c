<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * bebob_midi.c - a part of driver क्रम BeBoB based devices
 *
 * Copyright (c) 2013-2014 Takashi Sakamoto
 */

#समावेश "bebob.h"

अटल पूर्णांक midi_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_bebob *bebob = substream->rmidi->निजी_data;
	पूर्णांक err;

	err = snd_bebob_stream_lock_try(bebob);
	अगर (err < 0)
		वापस err;

	mutex_lock(&bebob->mutex);
	err = snd_bebob_stream_reserve_duplex(bebob, 0, 0, 0);
	अगर (err >= 0) अणु
		++bebob->substreams_counter;
		err = snd_bebob_stream_start_duplex(bebob);
		अगर (err < 0)
			--bebob->substreams_counter;
	पूर्ण
	mutex_unlock(&bebob->mutex);
	अगर (err < 0)
		snd_bebob_stream_lock_release(bebob);

	वापस err;
पूर्ण

अटल पूर्णांक midi_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_bebob *bebob = substream->rmidi->निजी_data;

	mutex_lock(&bebob->mutex);
	bebob->substreams_counter--;
	snd_bebob_stream_stop_duplex(bebob);
	mutex_unlock(&bebob->mutex);

	snd_bebob_stream_lock_release(bebob);
	वापस 0;
पूर्ण

अटल व्योम midi_capture_trigger(काष्ठा snd_rawmidi_substream *substrm, पूर्णांक up)
अणु
	काष्ठा snd_bebob *bebob = substrm->rmidi->निजी_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bebob->lock, flags);

	अगर (up)
		amdtp_am824_midi_trigger(&bebob->tx_stream,
					 substrm->number, substrm);
	अन्यथा
		amdtp_am824_midi_trigger(&bebob->tx_stream,
					 substrm->number, शून्य);

	spin_unlock_irqrestore(&bebob->lock, flags);
पूर्ण

अटल व्योम midi_playback_trigger(काष्ठा snd_rawmidi_substream *substrm, पूर्णांक up)
अणु
	काष्ठा snd_bebob *bebob = substrm->rmidi->निजी_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bebob->lock, flags);

	अगर (up)
		amdtp_am824_midi_trigger(&bebob->rx_stream,
					 substrm->number, substrm);
	अन्यथा
		amdtp_am824_midi_trigger(&bebob->rx_stream,
					 substrm->number, शून्य);

	spin_unlock_irqrestore(&bebob->lock, flags);
पूर्ण

अटल व्योम set_midi_substream_names(काष्ठा snd_bebob *bebob,
				     काष्ठा snd_rawmidi_str *str)
अणु
	काष्ठा snd_rawmidi_substream *subs;

	list_क्रम_each_entry(subs, &str->substreams, list) अणु
		snम_लिखो(subs->name, माप(subs->name),
			 "%s MIDI %d",
			 bebob->card->लघुname, subs->number + 1);
	पूर्ण
पूर्ण

पूर्णांक snd_bebob_create_midi_devices(काष्ठा snd_bebob *bebob)
अणु
	अटल स्थिर काष्ठा snd_rawmidi_ops capture_ops = अणु
		.खोलो		= midi_खोलो,
		.बंद		= midi_बंद,
		.trigger	= midi_capture_trigger,
	पूर्ण;
	अटल स्थिर काष्ठा snd_rawmidi_ops playback_ops = अणु
		.खोलो		= midi_खोलो,
		.बंद		= midi_बंद,
		.trigger	= midi_playback_trigger,
	पूर्ण;
	काष्ठा snd_rawmidi *rmidi;
	काष्ठा snd_rawmidi_str *str;
	पूर्णांक err;

	/* create midi ports */
	err = snd_rawmidi_new(bebob->card, bebob->card->driver, 0,
			      bebob->midi_output_ports, bebob->midi_input_ports,
			      &rmidi);
	अगर (err < 0)
		वापस err;

	snम_लिखो(rmidi->name, माप(rmidi->name),
		 "%s MIDI", bebob->card->लघुname);
	rmidi->निजी_data = bebob;

	अगर (bebob->midi_input_ports > 0) अणु
		rmidi->info_flags |= SNDRV_RAWMIDI_INFO_INPUT;

		snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_INPUT,
				    &capture_ops);

		str = &rmidi->streams[SNDRV_RAWMIDI_STREAM_INPUT];

		set_midi_substream_names(bebob, str);
	पूर्ण

	अगर (bebob->midi_output_ports > 0) अणु
		rmidi->info_flags |= SNDRV_RAWMIDI_INFO_OUTPUT;

		snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT,
				    &playback_ops);

		str = &rmidi->streams[SNDRV_RAWMIDI_STREAM_OUTPUT];

		set_midi_substream_names(bebob, str);
	पूर्ण

	अगर ((bebob->midi_output_ports > 0) && (bebob->midi_input_ports > 0))
		rmidi->info_flags |= SNDRV_RAWMIDI_INFO_DUPLEX;

	वापस 0;
पूर्ण
