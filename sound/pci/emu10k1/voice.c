<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *                   Creative Lअसल, Inc.
 *                   Lee Revell <rlrevell@joe-job.com>
 *  Routines क्रम control of EMU10K1 chips - voice manager
 *
 *  Rewrote voice allocator क्रम multichannel support - rlrevell 12/2004
 * 
 *  BUGS:
 *    --
 *
 *  TODO:
 *    --
 */

#समावेश <linux/समय.स>
#समावेश <linux/export.h>
#समावेश <sound/core.h>
#समावेश <sound/emu10k1.h>

/* Previously the voice allocator started at 0 every समय.  The new voice 
 * allocator uses a round robin scheme.  The next मुक्त voice is tracked in 
 * the card record and each allocation begins where the last left off.  The 
 * hardware requires stereo पूर्णांकerleaved voices be aligned to an even/odd 
 * boundary.  For multichannel voice allocation we ensure than the block of 
 * voices करोes not cross the 32 voice boundary.  This simplअगरies the 
 * multichannel support and ensures we can use a single ग_लिखो to the 
 * (set|clear)_loop_stop रेजिस्टरs.  Otherwise (क्रम example) the voices would 
 * get out of sync when pausing/resuming a stream.
 *							--rlrevell
 */

अटल पूर्णांक voice_alloc(काष्ठा snd_emu10k1 *emu, पूर्णांक type, पूर्णांक number,
		       काष्ठा snd_emu10k1_voice **rvoice)
अणु
	काष्ठा snd_emu10k1_voice *voice;
	पूर्णांक i, j, k, first_voice, last_voice, skip;

	*rvoice = शून्य;
	first_voice = last_voice = 0;
	क्रम (i = emu->next_मुक्त_voice, j = 0; j < NUM_G ; i += number, j += number) अणु
		/*
		dev_dbg(emu->card->dev, "i %d j %d next free %d!\n",
		       i, j, emu->next_मुक्त_voice);
		*/
		i %= NUM_G;

		/* stereo voices must be even/odd */
		अगर ((number == 2) && (i % 2)) अणु
			i++;
			जारी;
		पूर्ण
			
		skip = 0;
		क्रम (k = 0; k < number; k++) अणु
			voice = &emu->voices[(i+k) % NUM_G];
			अगर (voice->use) अणु
				skip = 1;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!skip) अणु
			/* dev_dbg(emu->card->dev, "allocated voice %d\n", i); */
			first_voice = i;
			last_voice = (i + number) % NUM_G;
			emu->next_मुक्त_voice = last_voice;
			अवरोध;
		पूर्ण
	पूर्ण
	
	अगर (first_voice == last_voice)
		वापस -ENOMEM;
	
	क्रम (i = 0; i < number; i++) अणु
		voice = &emu->voices[(first_voice + i) % NUM_G];
		/*
		dev_dbg(emu->card->dev, "voice alloc - %i, %i of %i\n",
		       voice->number, idx-first_voice+1, number);
		*/
		voice->use = 1;
		चयन (type) अणु
		हाल EMU10K1_PCM:
			voice->pcm = 1;
			अवरोध;
		हाल EMU10K1_SYNTH:
			voice->synth = 1;
			अवरोध;
		हाल EMU10K1_MIDI:
			voice->midi = 1;
			अवरोध;
		हाल EMU10K1_EFX:
			voice->efx = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	*rvoice = &emu->voices[first_voice];
	वापस 0;
पूर्ण

पूर्णांक snd_emu10k1_voice_alloc(काष्ठा snd_emu10k1 *emu, पूर्णांक type, पूर्णांक number,
			    काष्ठा snd_emu10k1_voice **rvoice)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक result;

	अगर (snd_BUG_ON(!rvoice))
		वापस -EINVAL;
	अगर (snd_BUG_ON(!number))
		वापस -EINVAL;

	spin_lock_irqsave(&emu->voice_lock, flags);
	क्रम (;;) अणु
		result = voice_alloc(emu, type, number, rvoice);
		अगर (result == 0 || type == EMU10K1_SYNTH || type == EMU10K1_MIDI)
			अवरोध;

		/* मुक्त a voice from synth */
		अगर (emu->get_synth_voice) अणु
			result = emu->get_synth_voice(emu);
			अगर (result >= 0) अणु
				काष्ठा snd_emu10k1_voice *pvoice = &emu->voices[result];
				pvoice->पूर्णांकerrupt = शून्य;
				pvoice->use = pvoice->pcm = pvoice->synth = pvoice->midi = pvoice->efx = 0;
				pvoice->epcm = शून्य;
			पूर्ण
		पूर्ण
		अगर (result < 0)
			अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&emu->voice_lock, flags);

	वापस result;
पूर्ण

EXPORT_SYMBOL(snd_emu10k1_voice_alloc);

पूर्णांक snd_emu10k1_voice_मुक्त(काष्ठा snd_emu10k1 *emu,
			   काष्ठा snd_emu10k1_voice *pvoice)
अणु
	अचिन्हित दीर्घ flags;

	अगर (snd_BUG_ON(!pvoice))
		वापस -EINVAL;
	spin_lock_irqsave(&emu->voice_lock, flags);
	pvoice->पूर्णांकerrupt = शून्य;
	pvoice->use = pvoice->pcm = pvoice->synth = pvoice->midi = pvoice->efx = 0;
	pvoice->epcm = शून्य;
	snd_emu10k1_voice_init(emu, pvoice->number);
	spin_unlock_irqrestore(&emu->voice_lock, flags);
	वापस 0;
पूर्ण

EXPORT_SYMBOL(snd_emu10k1_voice_मुक्त);
