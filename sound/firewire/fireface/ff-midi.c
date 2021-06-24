<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ff-midi.c - a part of driver क्रम RME Fireface series
 *
 * Copyright (c) 2015-2017 Takashi Sakamoto
 */

#समावेश "ff.h"

अटल पूर्णांक midi_capture_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	/* Do nothing. */
	वापस 0;
पूर्ण

अटल पूर्णांक midi_playback_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_ff *ff = substream->rmidi->निजी_data;

	/* Initialize पूर्णांकernal status. */
	ff->on_sysex[substream->number] = 0;
	ff->rx_midi_error[substream->number] = false;

	WRITE_ONCE(ff->rx_midi_substreams[substream->number], substream);

	वापस 0;
पूर्ण

अटल पूर्णांक midi_capture_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	/* Do nothing. */
	वापस 0;
पूर्ण

अटल पूर्णांक midi_playback_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_ff *ff = substream->rmidi->निजी_data;

	cancel_work_sync(&ff->rx_midi_work[substream->number]);
	WRITE_ONCE(ff->rx_midi_substreams[substream->number], शून्य);

	वापस 0;
पूर्ण

अटल व्योम midi_capture_trigger(काष्ठा snd_rawmidi_substream *substream,
				 पूर्णांक up)
अणु
	काष्ठा snd_ff *ff = substream->rmidi->निजी_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ff->lock, flags);

	अगर (up)
		WRITE_ONCE(ff->tx_midi_substreams[substream->number],
			   substream);
	अन्यथा
		WRITE_ONCE(ff->tx_midi_substreams[substream->number], शून्य);

	spin_unlock_irqrestore(&ff->lock, flags);
पूर्ण

अटल व्योम midi_playback_trigger(काष्ठा snd_rawmidi_substream *substream,
				  पूर्णांक up)
अणु
	काष्ठा snd_ff *ff = substream->rmidi->निजी_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ff->lock, flags);

	अगर (up || !ff->rx_midi_error[substream->number])
		schedule_work(&ff->rx_midi_work[substream->number]);

	spin_unlock_irqrestore(&ff->lock, flags);
पूर्ण

अटल व्योम set_midi_substream_names(काष्ठा snd_rawmidi_str *stream,
				     स्थिर अक्षर *स्थिर name)
अणु
	काष्ठा snd_rawmidi_substream *substream;

	list_क्रम_each_entry(substream, &stream->substreams, list) अणु
		snम_लिखो(substream->name, माप(substream->name),
			 "%s MIDI %d", name, substream->number + 1);
	पूर्ण
पूर्ण

पूर्णांक snd_ff_create_midi_devices(काष्ठा snd_ff *ff)
अणु
	अटल स्थिर काष्ठा snd_rawmidi_ops midi_capture_ops = अणु
		.खोलो		= midi_capture_खोलो,
		.बंद		= midi_capture_बंद,
		.trigger	= midi_capture_trigger,
	पूर्ण;
	अटल स्थिर काष्ठा snd_rawmidi_ops midi_playback_ops = अणु
		.खोलो		= midi_playback_खोलो,
		.बंद		= midi_playback_बंद,
		.trigger	= midi_playback_trigger,
	पूर्ण;
	काष्ठा snd_rawmidi *rmidi;
	काष्ठा snd_rawmidi_str *stream;
	पूर्णांक err;

	err = snd_rawmidi_new(ff->card, ff->card->driver, 0,
			      ff->spec->midi_out_ports, ff->spec->midi_in_ports,
			      &rmidi);
	अगर (err < 0)
		वापस err;

	snम_लिखो(rmidi->name, माप(rmidi->name),
		 "%s MIDI", ff->card->लघुname);
	rmidi->निजी_data = ff;

	rmidi->info_flags |= SNDRV_RAWMIDI_INFO_INPUT;
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_INPUT,
			    &midi_capture_ops);
	stream = &rmidi->streams[SNDRV_RAWMIDI_STREAM_INPUT];
	set_midi_substream_names(stream, ff->card->लघुname);

	rmidi->info_flags |= SNDRV_RAWMIDI_INFO_OUTPUT;
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT,
			    &midi_playback_ops);
	stream = &rmidi->streams[SNDRV_RAWMIDI_STREAM_OUTPUT];
	set_midi_substream_names(stream, ff->card->लघुname);

	rmidi->info_flags |= SNDRV_RAWMIDI_INFO_DUPLEX;

	वापस 0;
पूर्ण
