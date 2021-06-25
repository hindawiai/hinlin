<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *  Routines क्रम control of SoundBlaster cards - MIDI पूर्णांकerface
 *
 * --
 *
 * Sun May  9 22:54:38 BST 1999 George David Morrison <gdm@gedamo.demon.co.uk>
 *   Fixed typo in snd_sb8dsp_midi_new_device which prevented midi from 
 *   working.
 *
 * Sun May 11 12:34:56 UTC 2003 Clemens Ladisch <clemens@ladisch.de>
 *   Added full duplex UART mode क्रम DSP version 2.0 and later.
 */

#समावेश <linux/पन.स>
#समावेश <linux/समय.स>
#समावेश <sound/core.h>
#समावेश <sound/sb.h>


irqवापस_t snd_sb8dsp_midi_पूर्णांकerrupt(काष्ठा snd_sb *chip)
अणु
	काष्ठा snd_rawmidi *rmidi;
	पूर्णांक max = 64;
	अक्षर byte;

	अगर (!chip)
		वापस IRQ_NONE;
	
	rmidi = chip->rmidi;
	अगर (!rmidi) अणु
		inb(SBP(chip, DATA_AVAIL));	/* ack पूर्णांकerrupt */
		वापस IRQ_NONE;
	पूर्ण

	spin_lock(&chip->midi_input_lock);
	जबतक (max-- > 0) अणु
		अगर (inb(SBP(chip, DATA_AVAIL)) & 0x80) अणु
			byte = inb(SBP(chip, READ));
			अगर (chip->खोलो & SB_OPEN_MIDI_INPUT_TRIGGER) अणु
				snd_rawmidi_receive(chip->midi_substream_input, &byte, 1);
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock(&chip->midi_input_lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक snd_sb8dsp_midi_input_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_sb *chip;
	अचिन्हित पूर्णांक valid_खोलो_flags;

	chip = substream->rmidi->निजी_data;
	valid_खोलो_flags = chip->hardware >= SB_HW_20
		? SB_OPEN_MIDI_OUTPUT | SB_OPEN_MIDI_OUTPUT_TRIGGER : 0;
	spin_lock_irqsave(&chip->खोलो_lock, flags);
	अगर (chip->खोलो & ~valid_खोलो_flags) अणु
		spin_unlock_irqrestore(&chip->खोलो_lock, flags);
		वापस -EAGAIN;
	पूर्ण
	chip->खोलो |= SB_OPEN_MIDI_INPUT;
	chip->midi_substream_input = substream;
	अगर (!(chip->खोलो & SB_OPEN_MIDI_OUTPUT)) अणु
		spin_unlock_irqrestore(&chip->खोलो_lock, flags);
		snd_sbdsp_reset(chip);		/* reset DSP */
		अगर (chip->hardware >= SB_HW_20)
			snd_sbdsp_command(chip, SB_DSP_MIDI_UART_IRQ);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&chip->खोलो_lock, flags);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sb8dsp_midi_output_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_sb *chip;
	अचिन्हित पूर्णांक valid_खोलो_flags;

	chip = substream->rmidi->निजी_data;
	valid_खोलो_flags = chip->hardware >= SB_HW_20
		? SB_OPEN_MIDI_INPUT | SB_OPEN_MIDI_INPUT_TRIGGER : 0;
	spin_lock_irqsave(&chip->खोलो_lock, flags);
	अगर (chip->खोलो & ~valid_खोलो_flags) अणु
		spin_unlock_irqrestore(&chip->खोलो_lock, flags);
		वापस -EAGAIN;
	पूर्ण
	chip->खोलो |= SB_OPEN_MIDI_OUTPUT;
	chip->midi_substream_output = substream;
	अगर (!(chip->खोलो & SB_OPEN_MIDI_INPUT)) अणु
		spin_unlock_irqrestore(&chip->खोलो_lock, flags);
		snd_sbdsp_reset(chip);		/* reset DSP */
		अगर (chip->hardware >= SB_HW_20)
			snd_sbdsp_command(chip, SB_DSP_MIDI_UART_IRQ);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&chip->खोलो_lock, flags);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sb8dsp_midi_input_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_sb *chip;

	chip = substream->rmidi->निजी_data;
	spin_lock_irqsave(&chip->खोलो_lock, flags);
	chip->खोलो &= ~(SB_OPEN_MIDI_INPUT | SB_OPEN_MIDI_INPUT_TRIGGER);
	chip->midi_substream_input = शून्य;
	अगर (!(chip->खोलो & SB_OPEN_MIDI_OUTPUT)) अणु
		spin_unlock_irqrestore(&chip->खोलो_lock, flags);
		snd_sbdsp_reset(chip);		/* reset DSP */
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&chip->खोलो_lock, flags);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sb8dsp_midi_output_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_sb *chip;

	chip = substream->rmidi->निजी_data;
	del_समयr_sync(&chip->midi_समयr);
	spin_lock_irqsave(&chip->खोलो_lock, flags);
	chip->खोलो &= ~(SB_OPEN_MIDI_OUTPUT | SB_OPEN_MIDI_OUTPUT_TRIGGER);
	chip->midi_substream_output = शून्य;
	अगर (!(chip->खोलो & SB_OPEN_MIDI_INPUT)) अणु
		spin_unlock_irqrestore(&chip->खोलो_lock, flags);
		snd_sbdsp_reset(chip);		/* reset DSP */
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&chip->खोलो_lock, flags);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम snd_sb8dsp_midi_input_trigger(काष्ठा snd_rawmidi_substream *substream, पूर्णांक up)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_sb *chip;

	chip = substream->rmidi->निजी_data;
	spin_lock_irqsave(&chip->खोलो_lock, flags);
	अगर (up) अणु
		अगर (!(chip->खोलो & SB_OPEN_MIDI_INPUT_TRIGGER)) अणु
			अगर (chip->hardware < SB_HW_20)
				snd_sbdsp_command(chip, SB_DSP_MIDI_INPUT_IRQ);
			chip->खोलो |= SB_OPEN_MIDI_INPUT_TRIGGER;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (chip->खोलो & SB_OPEN_MIDI_INPUT_TRIGGER) अणु
			अगर (chip->hardware < SB_HW_20)
				snd_sbdsp_command(chip, SB_DSP_MIDI_INPUT_IRQ);
			chip->खोलो &= ~SB_OPEN_MIDI_INPUT_TRIGGER;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&chip->खोलो_lock, flags);
पूर्ण

अटल व्योम snd_sb8dsp_midi_output_ग_लिखो(काष्ठा snd_rawmidi_substream *substream)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_sb *chip;
	अक्षर byte;
	पूर्णांक max = 32;

	/* how big is Tx FIFO? */
	chip = substream->rmidi->निजी_data;
	जबतक (max-- > 0) अणु
		spin_lock_irqsave(&chip->खोलो_lock, flags);
		अगर (snd_rawmidi_transmit_peek(substream, &byte, 1) != 1) अणु
			chip->खोलो &= ~SB_OPEN_MIDI_OUTPUT_TRIGGER;
			del_समयr(&chip->midi_समयr);
			spin_unlock_irqrestore(&chip->खोलो_lock, flags);
			अवरोध;
		पूर्ण
		अगर (chip->hardware >= SB_HW_20) अणु
			पूर्णांक समयout = 8;
			जबतक ((inb(SBP(chip, STATUS)) & 0x80) != 0 && --समयout > 0)
				;
			अगर (समयout == 0) अणु
				/* Tx FIFO full - try again later */
				spin_unlock_irqrestore(&chip->खोलो_lock, flags);
				अवरोध;
			पूर्ण
			outb(byte, SBP(chip, WRITE));
		पूर्ण अन्यथा अणु
			snd_sbdsp_command(chip, SB_DSP_MIDI_OUTPUT);
			snd_sbdsp_command(chip, byte);
		पूर्ण
		snd_rawmidi_transmit_ack(substream, 1);
		spin_unlock_irqrestore(&chip->खोलो_lock, flags);
	पूर्ण
पूर्ण

अटल व्योम snd_sb8dsp_midi_output_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा snd_sb *chip = from_समयr(chip, t, midi_समयr);
	काष्ठा snd_rawmidi_substream *substream = chip->midi_substream_output;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->खोलो_lock, flags);
	mod_समयr(&chip->midi_समयr, 1 + jअगरfies);
	spin_unlock_irqrestore(&chip->खोलो_lock, flags);	
	snd_sb8dsp_midi_output_ग_लिखो(substream);
पूर्ण

अटल व्योम snd_sb8dsp_midi_output_trigger(काष्ठा snd_rawmidi_substream *substream, पूर्णांक up)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_sb *chip;

	chip = substream->rmidi->निजी_data;
	spin_lock_irqsave(&chip->खोलो_lock, flags);
	अगर (up) अणु
		अगर (!(chip->खोलो & SB_OPEN_MIDI_OUTPUT_TRIGGER)) अणु
			mod_समयr(&chip->midi_समयr, 1 + jअगरfies);
			chip->खोलो |= SB_OPEN_MIDI_OUTPUT_TRIGGER;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (chip->खोलो & SB_OPEN_MIDI_OUTPUT_TRIGGER) अणु
			chip->खोलो &= ~SB_OPEN_MIDI_OUTPUT_TRIGGER;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&chip->खोलो_lock, flags);

	अगर (up)
		snd_sb8dsp_midi_output_ग_लिखो(substream);
पूर्ण

अटल स्थिर काष्ठा snd_rawmidi_ops snd_sb8dsp_midi_output =
अणु
	.खोलो =		snd_sb8dsp_midi_output_खोलो,
	.बंद =	snd_sb8dsp_midi_output_बंद,
	.trigger =	snd_sb8dsp_midi_output_trigger,
पूर्ण;

अटल स्थिर काष्ठा snd_rawmidi_ops snd_sb8dsp_midi_input =
अणु
	.खोलो =		snd_sb8dsp_midi_input_खोलो,
	.बंद =	snd_sb8dsp_midi_input_बंद,
	.trigger =	snd_sb8dsp_midi_input_trigger,
पूर्ण;

पूर्णांक snd_sb8dsp_midi(काष्ठा snd_sb *chip, पूर्णांक device)
अणु
	काष्ठा snd_rawmidi *rmidi;
	पूर्णांक err;

	अगर ((err = snd_rawmidi_new(chip->card, "SB8 MIDI", device, 1, 1, &rmidi)) < 0)
		वापस err;
	म_नकल(rmidi->name, "SB8 MIDI");
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT, &snd_sb8dsp_midi_output);
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_INPUT, &snd_sb8dsp_midi_input);
	rmidi->info_flags |= SNDRV_RAWMIDI_INFO_OUTPUT | SNDRV_RAWMIDI_INFO_INPUT;
	अगर (chip->hardware >= SB_HW_20)
		rmidi->info_flags |= SNDRV_RAWMIDI_INFO_DUPLEX;
	rmidi->निजी_data = chip;
	समयr_setup(&chip->midi_समयr, snd_sb8dsp_midi_output_समयr, 0);
	chip->rmidi = rmidi;
	वापस 0;
पूर्ण
