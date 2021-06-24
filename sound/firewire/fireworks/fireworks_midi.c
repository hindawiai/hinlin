<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * fireworks_midi.c - a part of driver क्रम Fireworks based devices
 *
 * Copyright (c) 2009-2010 Clemens Ladisch
 * Copyright (c) 2013-2014 Takashi Sakamoto
 */
#समावेश "fireworks.h"

अटल पूर्णांक midi_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_efw *efw = substream->rmidi->निजी_data;
	पूर्णांक err;

	err = snd_efw_stream_lock_try(efw);
	अगर (err < 0)
		जाओ end;

	mutex_lock(&efw->mutex);
	err = snd_efw_stream_reserve_duplex(efw, 0, 0, 0);
	अगर (err >= 0) अणु
		++efw->substreams_counter;
		err = snd_efw_stream_start_duplex(efw);
		अगर (err < 0)
			--efw->substreams_counter;
	पूर्ण
	mutex_unlock(&efw->mutex);
	अगर (err < 0)
		snd_efw_stream_lock_release(efw);
end:
	वापस err;
पूर्ण

अटल पूर्णांक midi_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_efw *efw = substream->rmidi->निजी_data;

	mutex_lock(&efw->mutex);
	--efw->substreams_counter;
	snd_efw_stream_stop_duplex(efw);
	mutex_unlock(&efw->mutex);

	snd_efw_stream_lock_release(efw);
	वापस 0;
पूर्ण

अटल व्योम midi_capture_trigger(काष्ठा snd_rawmidi_substream *substrm, पूर्णांक up)
अणु
	काष्ठा snd_efw *efw = substrm->rmidi->निजी_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&efw->lock, flags);

	अगर (up)
		amdtp_am824_midi_trigger(&efw->tx_stream,
					  substrm->number, substrm);
	अन्यथा
		amdtp_am824_midi_trigger(&efw->tx_stream,
					  substrm->number, शून्य);

	spin_unlock_irqrestore(&efw->lock, flags);
पूर्ण

अटल व्योम midi_playback_trigger(काष्ठा snd_rawmidi_substream *substrm, पूर्णांक up)
अणु
	काष्ठा snd_efw *efw = substrm->rmidi->निजी_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&efw->lock, flags);

	अगर (up)
		amdtp_am824_midi_trigger(&efw->rx_stream,
					 substrm->number, substrm);
	अन्यथा
		amdtp_am824_midi_trigger(&efw->rx_stream,
					 substrm->number, शून्य);

	spin_unlock_irqrestore(&efw->lock, flags);
पूर्ण

अटल व्योम set_midi_substream_names(काष्ठा snd_efw *efw,
				     काष्ठा snd_rawmidi_str *str)
अणु
	काष्ठा snd_rawmidi_substream *subs;

	list_क्रम_each_entry(subs, &str->substreams, list) अणु
		snम_लिखो(subs->name, माप(subs->name),
			 "%s MIDI %d", efw->card->लघुname, subs->number + 1);
	पूर्ण
पूर्ण

पूर्णांक snd_efw_create_midi_devices(काष्ठा snd_efw *efw)
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
	err = snd_rawmidi_new(efw->card, efw->card->driver, 0,
			      efw->midi_out_ports, efw->midi_in_ports,
			      &rmidi);
	अगर (err < 0)
		वापस err;

	snम_लिखो(rmidi->name, माप(rmidi->name),
		 "%s MIDI", efw->card->लघुname);
	rmidi->निजी_data = efw;

	अगर (efw->midi_in_ports > 0) अणु
		rmidi->info_flags |= SNDRV_RAWMIDI_INFO_INPUT;

		snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_INPUT,
				    &capture_ops);

		str = &rmidi->streams[SNDRV_RAWMIDI_STREAM_INPUT];

		set_midi_substream_names(efw, str);
	पूर्ण

	अगर (efw->midi_out_ports > 0) अणु
		rmidi->info_flags |= SNDRV_RAWMIDI_INFO_OUTPUT;

		snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT,
				    &playback_ops);

		str = &rmidi->streams[SNDRV_RAWMIDI_STREAM_OUTPUT];

		set_midi_substream_names(efw, str);
	पूर्ण

	अगर ((efw->midi_out_ports > 0) && (efw->midi_in_ports > 0))
		rmidi->info_flags |= SNDRV_RAWMIDI_INFO_DUPLEX;

	वापस 0;
पूर्ण
