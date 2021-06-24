<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * dice_midi.c - a part of driver क्रम Dice based devices
 *
 * Copyright (c) 2014 Takashi Sakamoto
 */
#समावेश "dice.h"

अटल पूर्णांक midi_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_dice *dice = substream->rmidi->निजी_data;
	पूर्णांक err;

	err = snd_dice_stream_lock_try(dice);
	अगर (err < 0)
		वापस err;

	mutex_lock(&dice->mutex);

	err = snd_dice_stream_reserve_duplex(dice, 0, 0, 0);
	अगर (err >= 0) अणु
		++dice->substreams_counter;
		err = snd_dice_stream_start_duplex(dice);
		अगर (err < 0)
			--dice->substreams_counter;
	पूर्ण

	mutex_unlock(&dice->mutex);

	अगर (err < 0)
		snd_dice_stream_lock_release(dice);

	वापस err;
पूर्ण

अटल पूर्णांक midi_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_dice *dice = substream->rmidi->निजी_data;

	mutex_lock(&dice->mutex);

	--dice->substreams_counter;
	snd_dice_stream_stop_duplex(dice);

	mutex_unlock(&dice->mutex);

	snd_dice_stream_lock_release(dice);
	वापस 0;
पूर्ण

अटल व्योम midi_capture_trigger(काष्ठा snd_rawmidi_substream *substrm, पूर्णांक up)
अणु
	काष्ठा snd_dice *dice = substrm->rmidi->निजी_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dice->lock, flags);

	अगर (up)
		amdtp_am824_midi_trigger(&dice->tx_stream[0],
					  substrm->number, substrm);
	अन्यथा
		amdtp_am824_midi_trigger(&dice->tx_stream[0],
					  substrm->number, शून्य);

	spin_unlock_irqrestore(&dice->lock, flags);
पूर्ण

अटल व्योम midi_playback_trigger(काष्ठा snd_rawmidi_substream *substrm, पूर्णांक up)
अणु
	काष्ठा snd_dice *dice = substrm->rmidi->निजी_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dice->lock, flags);

	अगर (up)
		amdtp_am824_midi_trigger(&dice->rx_stream[0],
					 substrm->number, substrm);
	अन्यथा
		amdtp_am824_midi_trigger(&dice->rx_stream[0],
					 substrm->number, शून्य);

	spin_unlock_irqrestore(&dice->lock, flags);
पूर्ण

अटल व्योम set_midi_substream_names(काष्ठा snd_dice *dice,
				     काष्ठा snd_rawmidi_str *str)
अणु
	काष्ठा snd_rawmidi_substream *subs;

	list_क्रम_each_entry(subs, &str->substreams, list) अणु
		snम_लिखो(subs->name, माप(subs->name),
			 "%s MIDI %d", dice->card->लघुname, subs->number + 1);
	पूर्ण
पूर्ण

पूर्णांक snd_dice_create_midi(काष्ठा snd_dice *dice)
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
	अचिन्हित पूर्णांक midi_in_ports, midi_out_ports;
	पूर्णांक i;
	पूर्णांक err;

	midi_in_ports = 0;
	midi_out_ports = 0;
	क्रम (i = 0; i < MAX_STREAMS; ++i) अणु
		midi_in_ports = max(midi_in_ports, dice->tx_midi_ports[i]);
		midi_out_ports = max(midi_out_ports, dice->rx_midi_ports[i]);
	पूर्ण

	अगर (midi_in_ports + midi_out_ports == 0)
		वापस 0;

	/* create midi ports */
	err = snd_rawmidi_new(dice->card, dice->card->driver, 0,
			      midi_out_ports, midi_in_ports,
			      &rmidi);
	अगर (err < 0)
		वापस err;

	snम_लिखो(rmidi->name, माप(rmidi->name),
		 "%s MIDI", dice->card->लघुname);
	rmidi->निजी_data = dice;

	अगर (midi_in_ports > 0) अणु
		rmidi->info_flags |= SNDRV_RAWMIDI_INFO_INPUT;

		snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_INPUT,
				    &capture_ops);

		str = &rmidi->streams[SNDRV_RAWMIDI_STREAM_INPUT];

		set_midi_substream_names(dice, str);
	पूर्ण

	अगर (midi_out_ports > 0) अणु
		rmidi->info_flags |= SNDRV_RAWMIDI_INFO_OUTPUT;

		snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT,
				    &playback_ops);

		str = &rmidi->streams[SNDRV_RAWMIDI_STREAM_OUTPUT];

		set_midi_substream_names(dice, str);
	पूर्ण

	अगर ((midi_out_ports > 0) && (midi_in_ports > 0))
		rmidi->info_flags |= SNDRV_RAWMIDI_INFO_DUPLEX;

	वापस 0;
पूर्ण
