<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * tascam-midi.c - a part of driver क्रम TASCAM FireWire series
 *
 * Copyright (c) 2015 Takashi Sakamoto
 */

#समावेश "tascam.h"

अटल पूर्णांक midi_capture_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	/* Do nothing. */
	वापस 0;
पूर्ण

अटल पूर्णांक midi_playback_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_tscm *tscm = substream->rmidi->निजी_data;

	snd_fw_async_midi_port_init(&tscm->out_ports[substream->number]);

	वापस 0;
पूर्ण

अटल पूर्णांक midi_capture_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	/* Do nothing. */
	वापस 0;
पूर्ण

अटल पूर्णांक midi_playback_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	वापस 0;
पूर्ण

अटल व्योम midi_playback_drain(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_tscm *tscm = substream->rmidi->निजी_data;

	snd_fw_async_midi_port_finish(&tscm->out_ports[substream->number]);
पूर्ण

अटल व्योम midi_capture_trigger(काष्ठा snd_rawmidi_substream *substrm, पूर्णांक up)
अणु
	काष्ठा snd_tscm *tscm = substrm->rmidi->निजी_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tscm->lock, flags);

	अगर (up)
		tscm->tx_midi_substreams[substrm->number] = substrm;
	अन्यथा
		tscm->tx_midi_substreams[substrm->number] = शून्य;

	spin_unlock_irqrestore(&tscm->lock, flags);
पूर्ण

अटल व्योम midi_playback_trigger(काष्ठा snd_rawmidi_substream *substrm, पूर्णांक up)
अणु
	काष्ठा snd_tscm *tscm = substrm->rmidi->निजी_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tscm->lock, flags);

	अगर (up)
		snd_fw_async_midi_port_run(&tscm->out_ports[substrm->number],
					   substrm);

	spin_unlock_irqrestore(&tscm->lock, flags);
पूर्ण

पूर्णांक snd_tscm_create_midi_devices(काष्ठा snd_tscm *tscm)
अणु
	अटल स्थिर काष्ठा snd_rawmidi_ops capture_ops = अणु
		.खोलो		= midi_capture_खोलो,
		.बंद		= midi_capture_बंद,
		.trigger	= midi_capture_trigger,
	पूर्ण;
	अटल स्थिर काष्ठा snd_rawmidi_ops playback_ops = अणु
		.खोलो		= midi_playback_खोलो,
		.बंद		= midi_playback_बंद,
		.drain		= midi_playback_drain,
		.trigger	= midi_playback_trigger,
	पूर्ण;
	काष्ठा snd_rawmidi *rmidi;
	काष्ठा snd_rawmidi_str *stream;
	काष्ठा snd_rawmidi_substream *subs;
	पूर्णांक err;

	err = snd_rawmidi_new(tscm->card, tscm->card->driver, 0,
			      tscm->spec->midi_playback_ports,
			      tscm->spec->midi_capture_ports,
			      &rmidi);
	अगर (err < 0)
		वापस err;

	snम_लिखो(rmidi->name, माप(rmidi->name),
		 "%s MIDI", tscm->card->लघुname);
	rmidi->निजी_data = tscm;

	rmidi->info_flags |= SNDRV_RAWMIDI_INFO_INPUT;
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_INPUT,
			    &capture_ops);
	stream = &rmidi->streams[SNDRV_RAWMIDI_STREAM_INPUT];

	/* Set port names क्रम MIDI input. */
	list_क्रम_each_entry(subs, &stream->substreams, list) अणु
		/* TODO: support भव MIDI ports. */
		अगर (subs->number < tscm->spec->midi_capture_ports) अणु
			/* Hardware MIDI ports. */
			snम_लिखो(subs->name, माप(subs->name),
				 "%s MIDI %d",
				 tscm->card->लघुname, subs->number + 1);
		पूर्ण
	पूर्ण

	rmidi->info_flags |= SNDRV_RAWMIDI_INFO_OUTPUT;
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT,
			    &playback_ops);
	stream = &rmidi->streams[SNDRV_RAWMIDI_STREAM_OUTPUT];

	/* Set port names क्रम MIDI ourput. */
	list_क्रम_each_entry(subs, &stream->substreams, list) अणु
		अगर (subs->number < tscm->spec->midi_playback_ports) अणु
			/* Hardware MIDI ports only. */
			snम_लिखो(subs->name, माप(subs->name),
				 "%s MIDI %d",
				 tscm->card->लघुname, subs->number + 1);
		पूर्ण
	पूर्ण

	rmidi->info_flags |= SNDRV_RAWMIDI_INFO_DUPLEX;

	वापस 0;
पूर्ण
