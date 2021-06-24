<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * oxfw_midi.c - a part of driver क्रम OXFW970/971 based devices
 *
 * Copyright (c) 2014 Takashi Sakamoto
 */

#समावेश "oxfw.h"

अटल पूर्णांक midi_capture_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_oxfw *oxfw = substream->rmidi->निजी_data;
	पूर्णांक err;

	err = snd_oxfw_stream_lock_try(oxfw);
	अगर (err < 0)
		वापस err;

	mutex_lock(&oxfw->mutex);

	err = snd_oxfw_stream_reserve_duplex(oxfw, &oxfw->tx_stream, 0, 0, 0, 0);
	अगर (err >= 0) अणु
		++oxfw->substreams_count;
		err = snd_oxfw_stream_start_duplex(oxfw);
		अगर (err < 0)
			--oxfw->substreams_count;
	पूर्ण

	mutex_unlock(&oxfw->mutex);

	अगर (err < 0)
		snd_oxfw_stream_lock_release(oxfw);

	वापस err;
पूर्ण

अटल पूर्णांक midi_playback_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_oxfw *oxfw = substream->rmidi->निजी_data;
	पूर्णांक err;

	err = snd_oxfw_stream_lock_try(oxfw);
	अगर (err < 0)
		वापस err;

	mutex_lock(&oxfw->mutex);

	err = snd_oxfw_stream_reserve_duplex(oxfw, &oxfw->rx_stream, 0, 0, 0, 0);
	अगर (err >= 0) अणु
		++oxfw->substreams_count;
		err = snd_oxfw_stream_start_duplex(oxfw);
	पूर्ण

	mutex_unlock(&oxfw->mutex);

	अगर (err < 0)
		snd_oxfw_stream_lock_release(oxfw);

	वापस err;
पूर्ण

अटल पूर्णांक midi_capture_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_oxfw *oxfw = substream->rmidi->निजी_data;

	mutex_lock(&oxfw->mutex);

	--oxfw->substreams_count;
	snd_oxfw_stream_stop_duplex(oxfw);

	mutex_unlock(&oxfw->mutex);

	snd_oxfw_stream_lock_release(oxfw);
	वापस 0;
पूर्ण

अटल पूर्णांक midi_playback_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_oxfw *oxfw = substream->rmidi->निजी_data;

	mutex_lock(&oxfw->mutex);

	--oxfw->substreams_count;
	snd_oxfw_stream_stop_duplex(oxfw);

	mutex_unlock(&oxfw->mutex);

	snd_oxfw_stream_lock_release(oxfw);
	वापस 0;
पूर्ण

अटल व्योम midi_capture_trigger(काष्ठा snd_rawmidi_substream *substrm, पूर्णांक up)
अणु
	काष्ठा snd_oxfw *oxfw = substrm->rmidi->निजी_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&oxfw->lock, flags);

	अगर (up)
		amdtp_am824_midi_trigger(&oxfw->tx_stream,
					 substrm->number, substrm);
	अन्यथा
		amdtp_am824_midi_trigger(&oxfw->tx_stream,
					 substrm->number, शून्य);

	spin_unlock_irqrestore(&oxfw->lock, flags);
पूर्ण

अटल व्योम midi_playback_trigger(काष्ठा snd_rawmidi_substream *substrm, पूर्णांक up)
अणु
	काष्ठा snd_oxfw *oxfw = substrm->rmidi->निजी_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&oxfw->lock, flags);

	अगर (up)
		amdtp_am824_midi_trigger(&oxfw->rx_stream,
					 substrm->number, substrm);
	अन्यथा
		amdtp_am824_midi_trigger(&oxfw->rx_stream,
					 substrm->number, शून्य);

	spin_unlock_irqrestore(&oxfw->lock, flags);
पूर्ण

अटल व्योम set_midi_substream_names(काष्ठा snd_oxfw *oxfw,
				     काष्ठा snd_rawmidi_str *str)
अणु
	काष्ठा snd_rawmidi_substream *subs;

	list_क्रम_each_entry(subs, &str->substreams, list) अणु
		snम_लिखो(subs->name, माप(subs->name),
			 "%s MIDI %d",
			 oxfw->card->लघुname, subs->number + 1);
	पूर्ण
पूर्ण

पूर्णांक snd_oxfw_create_midi(काष्ठा snd_oxfw *oxfw)
अणु
	अटल स्थिर काष्ठा snd_rawmidi_ops capture_ops = अणु
		.खोलो		= midi_capture_खोलो,
		.बंद		= midi_capture_बंद,
		.trigger	= midi_capture_trigger,
	पूर्ण;
	अटल स्थिर काष्ठा snd_rawmidi_ops playback_ops = अणु
		.खोलो		= midi_playback_खोलो,
		.बंद		= midi_playback_बंद,
		.trigger	= midi_playback_trigger,
	पूर्ण;
	काष्ठा snd_rawmidi *rmidi;
	काष्ठा snd_rawmidi_str *str;
	पूर्णांक err;

	अगर (oxfw->midi_input_ports == 0 && oxfw->midi_output_ports == 0)
		वापस 0;

	/* create midi ports */
	err = snd_rawmidi_new(oxfw->card, oxfw->card->driver, 0,
			      oxfw->midi_output_ports, oxfw->midi_input_ports,
			      &rmidi);
	अगर (err < 0)
		वापस err;

	snम_लिखो(rmidi->name, माप(rmidi->name),
		 "%s MIDI", oxfw->card->लघुname);
	rmidi->निजी_data = oxfw;

	अगर (oxfw->midi_input_ports > 0) अणु
		rmidi->info_flags |= SNDRV_RAWMIDI_INFO_INPUT;

		snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_INPUT,
				    &capture_ops);

		str = &rmidi->streams[SNDRV_RAWMIDI_STREAM_INPUT];

		set_midi_substream_names(oxfw, str);
	पूर्ण

	अगर (oxfw->midi_output_ports > 0) अणु
		rmidi->info_flags |= SNDRV_RAWMIDI_INFO_OUTPUT;

		snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT,
				    &playback_ops);

		str = &rmidi->streams[SNDRV_RAWMIDI_STREAM_OUTPUT];

		set_midi_substream_names(oxfw, str);
	पूर्ण

	अगर ((oxfw->midi_output_ports > 0) && (oxfw->midi_input_ports > 0))
		rmidi->info_flags |= SNDRV_RAWMIDI_INFO_DUPLEX;

	वापस 0;
पूर्ण
