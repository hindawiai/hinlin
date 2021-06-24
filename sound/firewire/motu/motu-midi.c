<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * motu-midi.h - a part of driver क्रम MOTU FireWire series
 *
 * Copyright (c) 2015-2017 Takashi Sakamoto <o-takashi@sakamocchi.jp>
 */
#समावेश "motu.h"

अटल पूर्णांक midi_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_motu *motu = substream->rmidi->निजी_data;
	पूर्णांक err;

	err = snd_motu_stream_lock_try(motu);
	अगर (err < 0)
		वापस err;

	mutex_lock(&motu->mutex);

	err = snd_motu_stream_reserve_duplex(motu, 0, 0, 0);
	अगर (err >= 0) अणु
		++motu->substreams_counter;
		err = snd_motu_stream_start_duplex(motu);
		अगर (err < 0)
			--motu->substreams_counter;
	पूर्ण

	mutex_unlock(&motu->mutex);

	अगर (err < 0)
		snd_motu_stream_lock_release(motu);

	वापस err;
पूर्ण

अटल पूर्णांक midi_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_motu *motu = substream->rmidi->निजी_data;

	mutex_lock(&motu->mutex);

	--motu->substreams_counter;
	snd_motu_stream_stop_duplex(motu);

	mutex_unlock(&motu->mutex);

	snd_motu_stream_lock_release(motu);
	वापस 0;
पूर्ण

अटल व्योम midi_capture_trigger(काष्ठा snd_rawmidi_substream *substrm, पूर्णांक up)
अणु
	काष्ठा snd_motu *motu = substrm->rmidi->निजी_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&motu->lock, flags);

	अगर (up)
		amdtp_motu_midi_trigger(&motu->tx_stream, substrm->number,
					substrm);
	अन्यथा
		amdtp_motu_midi_trigger(&motu->tx_stream, substrm->number,
					शून्य);

	spin_unlock_irqrestore(&motu->lock, flags);
पूर्ण

अटल व्योम midi_playback_trigger(काष्ठा snd_rawmidi_substream *substrm, पूर्णांक up)
अणु
	काष्ठा snd_motu *motu = substrm->rmidi->निजी_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&motu->lock, flags);

	अगर (up)
		amdtp_motu_midi_trigger(&motu->rx_stream, substrm->number,
					substrm);
	अन्यथा
		amdtp_motu_midi_trigger(&motu->rx_stream, substrm->number,
					शून्य);

	spin_unlock_irqrestore(&motu->lock, flags);
पूर्ण

अटल व्योम set_midi_substream_names(काष्ठा snd_motu *motu,
				     काष्ठा snd_rawmidi_str *str)
अणु
	काष्ठा snd_rawmidi_substream *subs;

	list_क्रम_each_entry(subs, &str->substreams, list) अणु
		snम_लिखो(subs->name, माप(subs->name),
			 "%s MIDI %d", motu->card->लघुname, subs->number + 1);
	पूर्ण
पूर्ण

पूर्णांक snd_motu_create_midi_devices(काष्ठा snd_motu *motu)
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
	err = snd_rawmidi_new(motu->card, motu->card->driver, 0, 1, 1, &rmidi);
	अगर (err < 0)
		वापस err;

	snम_लिखो(rmidi->name, माप(rmidi->name),
		 "%s MIDI", motu->card->लघुname);
	rmidi->निजी_data = motu;

	rmidi->info_flags |= SNDRV_RAWMIDI_INFO_INPUT |
			     SNDRV_RAWMIDI_INFO_OUTPUT |
			     SNDRV_RAWMIDI_INFO_DUPLEX;

	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_INPUT,
			    &capture_ops);
	str = &rmidi->streams[SNDRV_RAWMIDI_STREAM_INPUT];
	set_midi_substream_names(motu, str);

	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT,
			    &playback_ops);
	str = &rmidi->streams[SNDRV_RAWMIDI_STREAM_OUTPUT];
	set_midi_substream_names(motu, str);

	वापस 0;
पूर्ण
