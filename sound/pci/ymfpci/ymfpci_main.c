<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *  Routines क्रम control of YMF724/740/744/754 chips
 */

#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>

#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/info.h>
#समावेश <sound/tlv.h>
#समावेश "ymfpci.h"
#समावेश <sound/asoundef.h>
#समावेश <sound/mpu401.h>

#समावेश <यंत्र/byteorder.h>

/*
 *  common I/O routines
 */

अटल व्योम snd_ymfpci_irq_रुको(काष्ठा snd_ymfpci *chip);

अटल अंतरभूत u8 snd_ymfpci_पढ़ोb(काष्ठा snd_ymfpci *chip, u32 offset)
अणु
	वापस पढ़ोb(chip->reg_area_virt + offset);
पूर्ण

अटल अंतरभूत व्योम snd_ymfpci_ग_लिखोb(काष्ठा snd_ymfpci *chip, u32 offset, u8 val)
अणु
	ग_लिखोb(val, chip->reg_area_virt + offset);
पूर्ण

अटल अंतरभूत u16 snd_ymfpci_पढ़ोw(काष्ठा snd_ymfpci *chip, u32 offset)
अणु
	वापस पढ़ोw(chip->reg_area_virt + offset);
पूर्ण

अटल अंतरभूत व्योम snd_ymfpci_ग_लिखोw(काष्ठा snd_ymfpci *chip, u32 offset, u16 val)
अणु
	ग_लिखोw(val, chip->reg_area_virt + offset);
पूर्ण

अटल अंतरभूत u32 snd_ymfpci_पढ़ोl(काष्ठा snd_ymfpci *chip, u32 offset)
अणु
	वापस पढ़ोl(chip->reg_area_virt + offset);
पूर्ण

अटल अंतरभूत व्योम snd_ymfpci_ग_लिखोl(काष्ठा snd_ymfpci *chip, u32 offset, u32 val)
अणु
	ग_लिखोl(val, chip->reg_area_virt + offset);
पूर्ण

अटल पूर्णांक snd_ymfpci_codec_पढ़ोy(काष्ठा snd_ymfpci *chip, पूर्णांक secondary)
अणु
	अचिन्हित दीर्घ end_समय;
	u32 reg = secondary ? YDSXGR_SECSTATUSADR : YDSXGR_PRISTATUSADR;
	
	end_समय = jअगरfies + msecs_to_jअगरfies(750);
	करो अणु
		अगर ((snd_ymfpci_पढ़ोw(chip, reg) & 0x8000) == 0)
			वापस 0;
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, end_समय));
	dev_err(chip->card->dev,
		"codec_ready: codec %i is not ready [0x%x]\n",
		secondary, snd_ymfpci_पढ़ोw(chip, reg));
	वापस -EBUSY;
पूर्ण

अटल व्योम snd_ymfpci_codec_ग_लिखो(काष्ठा snd_ac97 *ac97, u16 reg, u16 val)
अणु
	काष्ठा snd_ymfpci *chip = ac97->निजी_data;
	u32 cmd;
	
	snd_ymfpci_codec_पढ़ोy(chip, 0);
	cmd = ((YDSXG_AC97WRITECMD | reg) << 16) | val;
	snd_ymfpci_ग_लिखोl(chip, YDSXGR_AC97CMDDATA, cmd);
पूर्ण

अटल u16 snd_ymfpci_codec_पढ़ो(काष्ठा snd_ac97 *ac97, u16 reg)
अणु
	काष्ठा snd_ymfpci *chip = ac97->निजी_data;

	अगर (snd_ymfpci_codec_पढ़ोy(chip, 0))
		वापस ~0;
	snd_ymfpci_ग_लिखोw(chip, YDSXGR_AC97CMDADR, YDSXG_AC97READCMD | reg);
	अगर (snd_ymfpci_codec_पढ़ोy(chip, 0))
		वापस ~0;
	अगर (chip->device_id == PCI_DEVICE_ID_YAMAHA_744 && chip->rev < 2) अणु
		पूर्णांक i;
		क्रम (i = 0; i < 600; i++)
			snd_ymfpci_पढ़ोw(chip, YDSXGR_PRISTATUSDATA);
	पूर्ण
	वापस snd_ymfpci_पढ़ोw(chip, YDSXGR_PRISTATUSDATA);
पूर्ण

/*
 *  Misc routines
 */

अटल u32 snd_ymfpci_calc_delta(u32 rate)
अणु
	चयन (rate) अणु
	हाल 8000:	वापस 0x02aaab00;
	हाल 11025:	वापस 0x03accd00;
	हाल 16000:	वापस 0x05555500;
	हाल 22050:	वापस 0x07599a00;
	हाल 32000:	वापस 0x0aaaab00;
	हाल 44100:	वापस 0x0eb33300;
	शेष:	वापस ((rate << 16) / 375) << 5;
	पूर्ण
पूर्ण

अटल स्थिर u32 def_rate[8] = अणु
	100, 2000, 8000, 11025, 16000, 22050, 32000, 48000
पूर्ण;

अटल u32 snd_ymfpci_calc_lpfK(u32 rate)
अणु
	u32 i;
	अटल स्थिर u32 val[8] = अणु
		0x00570000, 0x06AA0000, 0x18B20000, 0x20930000,
		0x2B9A0000, 0x35A10000, 0x3EAA0000, 0x40000000
	पूर्ण;
	
	अगर (rate == 44100)
		वापस 0x40000000;	/* FIXME: What's the right value? */
	क्रम (i = 0; i < 8; i++)
		अगर (rate <= def_rate[i])
			वापस val[i];
	वापस val[0];
पूर्ण

अटल u32 snd_ymfpci_calc_lpfQ(u32 rate)
अणु
	u32 i;
	अटल स्थिर u32 val[8] = अणु
		0x35280000, 0x34A70000, 0x32020000, 0x31770000,
		0x31390000, 0x31C90000, 0x33D00000, 0x40000000
	पूर्ण;
	
	अगर (rate == 44100)
		वापस 0x370A0000;
	क्रम (i = 0; i < 8; i++)
		अगर (rate <= def_rate[i])
			वापस val[i];
	वापस val[0];
पूर्ण

/*
 *  Hardware start management
 */

अटल व्योम snd_ymfpci_hw_start(काष्ठा snd_ymfpci *chip)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->reg_lock, flags);
	अगर (chip->start_count++ > 0)
		जाओ __end;
	snd_ymfpci_ग_लिखोl(chip, YDSXGR_MODE,
			  snd_ymfpci_पढ़ोl(chip, YDSXGR_MODE) | 3);
	chip->active_bank = snd_ymfpci_पढ़ोl(chip, YDSXGR_CTRLSELECT) & 1;
      __end:
      	spin_unlock_irqrestore(&chip->reg_lock, flags);
पूर्ण

अटल व्योम snd_ymfpci_hw_stop(काष्ठा snd_ymfpci *chip)
अणु
	अचिन्हित दीर्घ flags;
	दीर्घ समयout = 1000;

	spin_lock_irqsave(&chip->reg_lock, flags);
	अगर (--chip->start_count > 0)
		जाओ __end;
	snd_ymfpci_ग_लिखोl(chip, YDSXGR_MODE,
			  snd_ymfpci_पढ़ोl(chip, YDSXGR_MODE) & ~3);
	जबतक (समयout-- > 0) अणु
		अगर ((snd_ymfpci_पढ़ोl(chip, YDSXGR_STATUS) & 2) == 0)
			अवरोध;
	पूर्ण
	अगर (atomic_पढ़ो(&chip->पूर्णांकerrupt_sleep_count)) अणु
		atomic_set(&chip->पूर्णांकerrupt_sleep_count, 0);
		wake_up(&chip->पूर्णांकerrupt_sleep);
	पूर्ण
      __end:
      	spin_unlock_irqrestore(&chip->reg_lock, flags);
पूर्ण

/*
 *  Playback voice management
 */

अटल पूर्णांक voice_alloc(काष्ठा snd_ymfpci *chip,
		       क्रमागत snd_ymfpci_voice_type type, पूर्णांक pair,
		       काष्ठा snd_ymfpci_voice **rvoice)
अणु
	काष्ठा snd_ymfpci_voice *voice, *voice2;
	पूर्णांक idx;
	
	*rvoice = शून्य;
	क्रम (idx = 0; idx < YDSXG_PLAYBACK_VOICES; idx += pair ? 2 : 1) अणु
		voice = &chip->voices[idx];
		voice2 = pair ? &chip->voices[idx+1] : शून्य;
		अगर (voice->use || (voice2 && voice2->use))
			जारी;
		voice->use = 1;
		अगर (voice2)
			voice2->use = 1;
		चयन (type) अणु
		हाल YMFPCI_PCM:
			voice->pcm = 1;
			अगर (voice2)
				voice2->pcm = 1;
			अवरोध;
		हाल YMFPCI_SYNTH:
			voice->synth = 1;
			अवरोध;
		हाल YMFPCI_MIDI:
			voice->midi = 1;
			अवरोध;
		पूर्ण
		snd_ymfpci_hw_start(chip);
		अगर (voice2)
			snd_ymfpci_hw_start(chip);
		*rvoice = voice;
		वापस 0;
	पूर्ण
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक snd_ymfpci_voice_alloc(काष्ठा snd_ymfpci *chip,
				  क्रमागत snd_ymfpci_voice_type type, पूर्णांक pair,
				  काष्ठा snd_ymfpci_voice **rvoice)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक result;
	
	अगर (snd_BUG_ON(!rvoice))
		वापस -EINVAL;
	अगर (snd_BUG_ON(pair && type != YMFPCI_PCM))
		वापस -EINVAL;
	
	spin_lock_irqsave(&chip->voice_lock, flags);
	क्रम (;;) अणु
		result = voice_alloc(chip, type, pair, rvoice);
		अगर (result == 0 || type != YMFPCI_PCM)
			अवरोध;
		/* TODO: synth/midi voice deallocation */
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&chip->voice_lock, flags);	
	वापस result;		
पूर्ण

अटल पूर्णांक snd_ymfpci_voice_मुक्त(काष्ठा snd_ymfpci *chip, काष्ठा snd_ymfpci_voice *pvoice)
अणु
	अचिन्हित दीर्घ flags;
	
	अगर (snd_BUG_ON(!pvoice))
		वापस -EINVAL;
	snd_ymfpci_hw_stop(chip);
	spin_lock_irqsave(&chip->voice_lock, flags);
	अगर (pvoice->number == chip->src441_used) अणु
		chip->src441_used = -1;
		pvoice->ypcm->use_441_slot = 0;
	पूर्ण
	pvoice->use = pvoice->pcm = pvoice->synth = pvoice->midi = 0;
	pvoice->ypcm = शून्य;
	pvoice->पूर्णांकerrupt = शून्य;
	spin_unlock_irqrestore(&chip->voice_lock, flags);
	वापस 0;
पूर्ण

/*
 *  PCM part
 */

अटल व्योम snd_ymfpci_pcm_पूर्णांकerrupt(काष्ठा snd_ymfpci *chip, काष्ठा snd_ymfpci_voice *voice)
अणु
	काष्ठा snd_ymfpci_pcm *ypcm;
	u32 pos, delta;
	
	अगर ((ypcm = voice->ypcm) == शून्य)
		वापस;
	अगर (ypcm->substream == शून्य)
		वापस;
	spin_lock(&chip->reg_lock);
	अगर (ypcm->running) अणु
		pos = le32_to_cpu(voice->bank[chip->active_bank].start);
		अगर (pos < ypcm->last_pos)
			delta = pos + (ypcm->buffer_size - ypcm->last_pos);
		अन्यथा
			delta = pos - ypcm->last_pos;
		ypcm->period_pos += delta;
		ypcm->last_pos = pos;
		अगर (ypcm->period_pos >= ypcm->period_size) अणु
			/*
			dev_dbg(chip->card->dev,
			       "done - active_bank = 0x%x, start = 0x%x\n",
			       chip->active_bank,
			       voice->bank[chip->active_bank].start);
			*/
			ypcm->period_pos %= ypcm->period_size;
			spin_unlock(&chip->reg_lock);
			snd_pcm_period_elapsed(ypcm->substream);
			spin_lock(&chip->reg_lock);
		पूर्ण

		अगर (unlikely(ypcm->update_pcm_vol)) अणु
			अचिन्हित पूर्णांक subs = ypcm->substream->number;
			अचिन्हित पूर्णांक next_bank = 1 - chip->active_bank;
			काष्ठा snd_ymfpci_playback_bank *bank;
			__le32 volume;
			
			bank = &voice->bank[next_bank];
			volume = cpu_to_le32(chip->pcm_mixer[subs].left << 15);
			bank->left_gain_end = volume;
			अगर (ypcm->output_rear)
				bank->eff2_gain_end = volume;
			अगर (ypcm->voices[1])
				bank = &ypcm->voices[1]->bank[next_bank];
			volume = cpu_to_le32(chip->pcm_mixer[subs].right << 15);
			bank->right_gain_end = volume;
			अगर (ypcm->output_rear)
				bank->eff3_gain_end = volume;
			ypcm->update_pcm_vol--;
		पूर्ण
	पूर्ण
	spin_unlock(&chip->reg_lock);
पूर्ण

अटल व्योम snd_ymfpci_pcm_capture_पूर्णांकerrupt(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_ymfpci_pcm *ypcm = runसमय->निजी_data;
	काष्ठा snd_ymfpci *chip = ypcm->chip;
	u32 pos, delta;
	
	spin_lock(&chip->reg_lock);
	अगर (ypcm->running) अणु
		pos = le32_to_cpu(chip->bank_capture[ypcm->capture_bank_number][chip->active_bank]->start) >> ypcm->shअगरt;
		अगर (pos < ypcm->last_pos)
			delta = pos + (ypcm->buffer_size - ypcm->last_pos);
		अन्यथा
			delta = pos - ypcm->last_pos;
		ypcm->period_pos += delta;
		ypcm->last_pos = pos;
		अगर (ypcm->period_pos >= ypcm->period_size) अणु
			ypcm->period_pos %= ypcm->period_size;
			/*
			dev_dbg(chip->card->dev,
			       "done - active_bank = 0x%x, start = 0x%x\n",
			       chip->active_bank,
			       voice->bank[chip->active_bank].start);
			*/
			spin_unlock(&chip->reg_lock);
			snd_pcm_period_elapsed(substream);
			spin_lock(&chip->reg_lock);
		पूर्ण
	पूर्ण
	spin_unlock(&chip->reg_lock);
पूर्ण

अटल पूर्णांक snd_ymfpci_playback_trigger(काष्ठा snd_pcm_substream *substream,
				       पूर्णांक cmd)
अणु
	काष्ठा snd_ymfpci *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_ymfpci_pcm *ypcm = substream->runसमय->निजी_data;
	काष्ठा snd_kcontrol *kctl = शून्य;
	पूर्णांक result = 0;

	spin_lock(&chip->reg_lock);
	अगर (ypcm->voices[0] == शून्य) अणु
		result = -EINVAL;
		जाओ __unlock;
	पूर्ण
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		chip->ctrl_playback[ypcm->voices[0]->number + 1] = cpu_to_le32(ypcm->voices[0]->bank_addr);
		अगर (ypcm->voices[1] != शून्य && !ypcm->use_441_slot)
			chip->ctrl_playback[ypcm->voices[1]->number + 1] = cpu_to_le32(ypcm->voices[1]->bank_addr);
		ypcm->running = 1;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		अगर (substream->pcm == chip->pcm && !ypcm->use_441_slot) अणु
			kctl = chip->pcm_mixer[substream->number].ctl;
			kctl->vd[0].access |= SNDRV_CTL_ELEM_ACCESS_INACTIVE;
		पूर्ण
		fallthrough;
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		chip->ctrl_playback[ypcm->voices[0]->number + 1] = 0;
		अगर (ypcm->voices[1] != शून्य && !ypcm->use_441_slot)
			chip->ctrl_playback[ypcm->voices[1]->number + 1] = 0;
		ypcm->running = 0;
		अवरोध;
	शेष:
		result = -EINVAL;
		अवरोध;
	पूर्ण
      __unlock:
	spin_unlock(&chip->reg_lock);
	अगर (kctl)
		snd_ctl_notअगरy(chip->card, SNDRV_CTL_EVENT_MASK_INFO, &kctl->id);
	वापस result;
पूर्ण
अटल पूर्णांक snd_ymfpci_capture_trigger(काष्ठा snd_pcm_substream *substream,
				      पूर्णांक cmd)
अणु
	काष्ठा snd_ymfpci *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_ymfpci_pcm *ypcm = substream->runसमय->निजी_data;
	पूर्णांक result = 0;
	u32 पंचांगp;

	spin_lock(&chip->reg_lock);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		पंचांगp = snd_ymfpci_पढ़ोl(chip, YDSXGR_MAPOFREC) | (1 << ypcm->capture_bank_number);
		snd_ymfpci_ग_लिखोl(chip, YDSXGR_MAPOFREC, पंचांगp);
		ypcm->running = 1;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		पंचांगp = snd_ymfpci_पढ़ोl(chip, YDSXGR_MAPOFREC) & ~(1 << ypcm->capture_bank_number);
		snd_ymfpci_ग_लिखोl(chip, YDSXGR_MAPOFREC, पंचांगp);
		ypcm->running = 0;
		अवरोध;
	शेष:
		result = -EINVAL;
		अवरोध;
	पूर्ण
	spin_unlock(&chip->reg_lock);
	वापस result;
पूर्ण

अटल पूर्णांक snd_ymfpci_pcm_voice_alloc(काष्ठा snd_ymfpci_pcm *ypcm, पूर्णांक voices)
अणु
	पूर्णांक err;

	अगर (ypcm->voices[1] != शून्य && voices < 2) अणु
		snd_ymfpci_voice_मुक्त(ypcm->chip, ypcm->voices[1]);
		ypcm->voices[1] = शून्य;
	पूर्ण
	अगर (voices == 1 && ypcm->voices[0] != शून्य)
		वापस 0;		/* alपढ़ोy allocated */
	अगर (voices == 2 && ypcm->voices[0] != शून्य && ypcm->voices[1] != शून्य)
		वापस 0;		/* alपढ़ोy allocated */
	अगर (voices > 1) अणु
		अगर (ypcm->voices[0] != शून्य && ypcm->voices[1] == शून्य) अणु
			snd_ymfpci_voice_मुक्त(ypcm->chip, ypcm->voices[0]);
			ypcm->voices[0] = शून्य;
		पूर्ण		
	पूर्ण
	err = snd_ymfpci_voice_alloc(ypcm->chip, YMFPCI_PCM, voices > 1, &ypcm->voices[0]);
	अगर (err < 0)
		वापस err;
	ypcm->voices[0]->ypcm = ypcm;
	ypcm->voices[0]->पूर्णांकerrupt = snd_ymfpci_pcm_पूर्णांकerrupt;
	अगर (voices > 1) अणु
		ypcm->voices[1] = &ypcm->chip->voices[ypcm->voices[0]->number + 1];
		ypcm->voices[1]->ypcm = ypcm;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम snd_ymfpci_pcm_init_voice(काष्ठा snd_ymfpci_pcm *ypcm, अचिन्हित पूर्णांक voiceidx,
				      काष्ठा snd_pcm_runसमय *runसमय,
				      पूर्णांक has_pcm_volume)
अणु
	काष्ठा snd_ymfpci_voice *voice = ypcm->voices[voiceidx];
	u32 क्रमmat;
	u32 delta = snd_ymfpci_calc_delta(runसमय->rate);
	u32 lpfQ = snd_ymfpci_calc_lpfQ(runसमय->rate);
	u32 lpfK = snd_ymfpci_calc_lpfK(runसमय->rate);
	काष्ठा snd_ymfpci_playback_bank *bank;
	अचिन्हित पूर्णांक nbank;
	__le32 vol_left, vol_right;
	u8 use_left, use_right;
	अचिन्हित दीर्घ flags;

	अगर (snd_BUG_ON(!voice))
		वापस;
	अगर (runसमय->channels == 1) अणु
		use_left = 1;
		use_right = 1;
	पूर्ण अन्यथा अणु
		use_left = (voiceidx & 1) == 0;
		use_right = !use_left;
	पूर्ण
	अगर (has_pcm_volume) अणु
		vol_left = cpu_to_le32(ypcm->chip->pcm_mixer
				       [ypcm->substream->number].left << 15);
		vol_right = cpu_to_le32(ypcm->chip->pcm_mixer
					[ypcm->substream->number].right << 15);
	पूर्ण अन्यथा अणु
		vol_left = cpu_to_le32(0x40000000);
		vol_right = cpu_to_le32(0x40000000);
	पूर्ण
	spin_lock_irqsave(&ypcm->chip->voice_lock, flags);
	क्रमmat = runसमय->channels == 2 ? 0x00010000 : 0;
	अगर (snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 8)
		क्रमmat |= 0x80000000;
	अन्यथा अगर (ypcm->chip->device_id == PCI_DEVICE_ID_YAMAHA_754 &&
		 runसमय->rate == 44100 && runसमय->channels == 2 &&
		 voiceidx == 0 && (ypcm->chip->src441_used == -1 ||
				   ypcm->chip->src441_used == voice->number)) अणु
		ypcm->chip->src441_used = voice->number;
		ypcm->use_441_slot = 1;
		क्रमmat |= 0x10000000;
	पूर्ण
	अगर (ypcm->chip->src441_used == voice->number &&
	    (क्रमmat & 0x10000000) == 0) अणु
		ypcm->chip->src441_used = -1;
		ypcm->use_441_slot = 0;
	पूर्ण
	अगर (runसमय->channels == 2 && (voiceidx & 1) != 0)
		क्रमmat |= 1;
	spin_unlock_irqrestore(&ypcm->chip->voice_lock, flags);
	क्रम (nbank = 0; nbank < 2; nbank++) अणु
		bank = &voice->bank[nbank];
		स_रखो(bank, 0, माप(*bank));
		bank->क्रमmat = cpu_to_le32(क्रमmat);
		bank->base = cpu_to_le32(runसमय->dma_addr);
		bank->loop_end = cpu_to_le32(ypcm->buffer_size);
		bank->lpfQ = cpu_to_le32(lpfQ);
		bank->delta =
		bank->delta_end = cpu_to_le32(delta);
		bank->lpfK =
		bank->lpfK_end = cpu_to_le32(lpfK);
		bank->eg_gain =
		bank->eg_gain_end = cpu_to_le32(0x40000000);

		अगर (ypcm->output_front) अणु
			अगर (use_left) अणु
				bank->left_gain =
				bank->left_gain_end = vol_left;
			पूर्ण
			अगर (use_right) अणु
				bank->right_gain =
				bank->right_gain_end = vol_right;
			पूर्ण
		पूर्ण
		अगर (ypcm->output_rear) अणु
		        अगर (!ypcm->swap_rear) अणु
        			अगर (use_left) अणु
        				bank->eff2_gain =
        				bank->eff2_gain_end = vol_left;
        			पूर्ण
        			अगर (use_right) अणु
        				bank->eff3_gain =
        				bank->eff3_gain_end = vol_right;
        			पूर्ण
		        पूर्ण अन्यथा अणु
        			/* The SPDIF out channels seem to be swapped, so we have
        			 * to swap them here, too.  The rear analog out channels
        			 * will be wrong, but otherwise AC3 would not work.
        			 */
        			अगर (use_left) अणु
        				bank->eff3_gain =
        				bank->eff3_gain_end = vol_left;
        			पूर्ण
        			अगर (use_right) अणु
        				bank->eff2_gain =
        				bank->eff2_gain_end = vol_right;
        			पूर्ण
        		पूर्ण
                पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक snd_ymfpci_ac3_init(काष्ठा snd_ymfpci *chip)
अणु
	अगर (snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, &chip->pci->dev,
				4096, &chip->ac3_पंचांगp_base) < 0)
		वापस -ENOMEM;

	chip->bank_effect[3][0]->base =
	chip->bank_effect[3][1]->base = cpu_to_le32(chip->ac3_पंचांगp_base.addr);
	chip->bank_effect[3][0]->loop_end =
	chip->bank_effect[3][1]->loop_end = cpu_to_le32(1024);
	chip->bank_effect[4][0]->base =
	chip->bank_effect[4][1]->base = cpu_to_le32(chip->ac3_पंचांगp_base.addr + 2048);
	chip->bank_effect[4][0]->loop_end =
	chip->bank_effect[4][1]->loop_end = cpu_to_le32(1024);

	spin_lock_irq(&chip->reg_lock);
	snd_ymfpci_ग_लिखोl(chip, YDSXGR_MAPOFEFFECT,
			  snd_ymfpci_पढ़ोl(chip, YDSXGR_MAPOFEFFECT) | 3 << 3);
	spin_unlock_irq(&chip->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ymfpci_ac3_करोne(काष्ठा snd_ymfpci *chip)
अणु
	spin_lock_irq(&chip->reg_lock);
	snd_ymfpci_ग_लिखोl(chip, YDSXGR_MAPOFEFFECT,
			  snd_ymfpci_पढ़ोl(chip, YDSXGR_MAPOFEFFECT) & ~(3 << 3));
	spin_unlock_irq(&chip->reg_lock);
	// snd_ymfpci_irq_रुको(chip);
	अगर (chip->ac3_पंचांगp_base.area) अणु
		snd_dma_मुक्त_pages(&chip->ac3_पंचांगp_base);
		chip->ac3_पंचांगp_base.area = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ymfpci_playback_hw_params(काष्ठा snd_pcm_substream *substream,
					 काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_ymfpci_pcm *ypcm = runसमय->निजी_data;
	पूर्णांक err;

	अगर ((err = snd_ymfpci_pcm_voice_alloc(ypcm, params_channels(hw_params))) < 0)
		वापस err;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ymfpci_playback_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ymfpci *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_ymfpci_pcm *ypcm;
	
	अगर (runसमय->निजी_data == शून्य)
		वापस 0;
	ypcm = runसमय->निजी_data;

	/* रुको, until the PCI operations are not finished */
	snd_ymfpci_irq_रुको(chip);
	अगर (ypcm->voices[1]) अणु
		snd_ymfpci_voice_मुक्त(chip, ypcm->voices[1]);
		ypcm->voices[1] = शून्य;
	पूर्ण
	अगर (ypcm->voices[0]) अणु
		snd_ymfpci_voice_मुक्त(chip, ypcm->voices[0]);
		ypcm->voices[0] = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ymfpci_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ymfpci *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_ymfpci_pcm *ypcm = runसमय->निजी_data;
	काष्ठा snd_kcontrol *kctl;
	अचिन्हित पूर्णांक nvoice;

	ypcm->period_size = runसमय->period_size;
	ypcm->buffer_size = runसमय->buffer_size;
	ypcm->period_pos = 0;
	ypcm->last_pos = 0;
	क्रम (nvoice = 0; nvoice < runसमय->channels; nvoice++)
		snd_ymfpci_pcm_init_voice(ypcm, nvoice, runसमय,
					  substream->pcm == chip->pcm);

	अगर (substream->pcm == chip->pcm && !ypcm->use_441_slot) अणु
		kctl = chip->pcm_mixer[substream->number].ctl;
		kctl->vd[0].access &= ~SNDRV_CTL_ELEM_ACCESS_INACTIVE;
		snd_ctl_notअगरy(chip->card, SNDRV_CTL_EVENT_MASK_INFO, &kctl->id);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ymfpci_capture_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ymfpci *chip = snd_pcm_substream_chip(substream);

	/* रुको, until the PCI operations are not finished */
	snd_ymfpci_irq_रुको(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ymfpci_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ymfpci *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_ymfpci_pcm *ypcm = runसमय->निजी_data;
	काष्ठा snd_ymfpci_capture_bank * bank;
	पूर्णांक nbank;
	u32 rate, क्रमmat;

	ypcm->period_size = runसमय->period_size;
	ypcm->buffer_size = runसमय->buffer_size;
	ypcm->period_pos = 0;
	ypcm->last_pos = 0;
	ypcm->shअगरt = 0;
	rate = ((48000 * 4096) / runसमय->rate) - 1;
	क्रमmat = 0;
	अगर (runसमय->channels == 2) अणु
		क्रमmat |= 2;
		ypcm->shअगरt++;
	पूर्ण
	अगर (snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 8)
		क्रमmat |= 1;
	अन्यथा
		ypcm->shअगरt++;
	चयन (ypcm->capture_bank_number) अणु
	हाल 0:
		snd_ymfpci_ग_लिखोl(chip, YDSXGR_RECFORMAT, क्रमmat);
		snd_ymfpci_ग_लिखोl(chip, YDSXGR_RECSLOTSR, rate);
		अवरोध;
	हाल 1:
		snd_ymfpci_ग_लिखोl(chip, YDSXGR_ADCFORMAT, क्रमmat);
		snd_ymfpci_ग_लिखोl(chip, YDSXGR_ADCSLOTSR, rate);
		अवरोध;
	पूर्ण
	क्रम (nbank = 0; nbank < 2; nbank++) अणु
		bank = chip->bank_capture[ypcm->capture_bank_number][nbank];
		bank->base = cpu_to_le32(runसमय->dma_addr);
		bank->loop_end = cpu_to_le32(ypcm->buffer_size << ypcm->shअगरt);
		bank->start = 0;
		bank->num_of_loops = 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t snd_ymfpci_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ymfpci *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_ymfpci_pcm *ypcm = runसमय->निजी_data;
	काष्ठा snd_ymfpci_voice *voice = ypcm->voices[0];

	अगर (!(ypcm->running && voice))
		वापस 0;
	वापस le32_to_cpu(voice->bank[chip->active_bank].start);
पूर्ण

अटल snd_pcm_uframes_t snd_ymfpci_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ymfpci *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_ymfpci_pcm *ypcm = runसमय->निजी_data;

	अगर (!ypcm->running)
		वापस 0;
	वापस le32_to_cpu(chip->bank_capture[ypcm->capture_bank_number][chip->active_bank]->start) >> ypcm->shअगरt;
पूर्ण

अटल व्योम snd_ymfpci_irq_रुको(काष्ठा snd_ymfpci *chip)
अणु
	रुको_queue_entry_t रुको;
	पूर्णांक loops = 4;

	जबतक (loops-- > 0) अणु
		अगर ((snd_ymfpci_पढ़ोl(chip, YDSXGR_MODE) & 3) == 0)
		 	जारी;
		init_रुकोqueue_entry(&रुको, current);
		add_रुको_queue(&chip->पूर्णांकerrupt_sleep, &रुको);
		atomic_inc(&chip->पूर्णांकerrupt_sleep_count);
		schedule_समयout_unपूर्णांकerruptible(msecs_to_jअगरfies(50));
		हटाओ_रुको_queue(&chip->पूर्णांकerrupt_sleep, &रुको);
	पूर्ण
पूर्ण

अटल irqवापस_t snd_ymfpci_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा snd_ymfpci *chip = dev_id;
	u32 status, nvoice, mode;
	काष्ठा snd_ymfpci_voice *voice;

	status = snd_ymfpci_पढ़ोl(chip, YDSXGR_STATUS);
	अगर (status & 0x80000000) अणु
		chip->active_bank = snd_ymfpci_पढ़ोl(chip, YDSXGR_CTRLSELECT) & 1;
		spin_lock(&chip->voice_lock);
		क्रम (nvoice = 0; nvoice < YDSXG_PLAYBACK_VOICES; nvoice++) अणु
			voice = &chip->voices[nvoice];
			अगर (voice->पूर्णांकerrupt)
				voice->पूर्णांकerrupt(chip, voice);
		पूर्ण
		क्रम (nvoice = 0; nvoice < YDSXG_CAPTURE_VOICES; nvoice++) अणु
			अगर (chip->capture_substream[nvoice])
				snd_ymfpci_pcm_capture_पूर्णांकerrupt(chip->capture_substream[nvoice]);
		पूर्ण
#अगर 0
		क्रम (nvoice = 0; nvoice < YDSXG_EFFECT_VOICES; nvoice++) अणु
			अगर (chip->effect_substream[nvoice])
				snd_ymfpci_pcm_effect_पूर्णांकerrupt(chip->effect_substream[nvoice]);
		पूर्ण
#पूर्ण_अगर
		spin_unlock(&chip->voice_lock);
		spin_lock(&chip->reg_lock);
		snd_ymfpci_ग_लिखोl(chip, YDSXGR_STATUS, 0x80000000);
		mode = snd_ymfpci_पढ़ोl(chip, YDSXGR_MODE) | 2;
		snd_ymfpci_ग_लिखोl(chip, YDSXGR_MODE, mode);
		spin_unlock(&chip->reg_lock);

		अगर (atomic_पढ़ो(&chip->पूर्णांकerrupt_sleep_count)) अणु
			atomic_set(&chip->पूर्णांकerrupt_sleep_count, 0);
			wake_up(&chip->पूर्णांकerrupt_sleep);
		पूर्ण
	पूर्ण

	status = snd_ymfpci_पढ़ोw(chip, YDSXGR_INTFLAG);
	अगर (status & 1) अणु
		अगर (chip->समयr)
			snd_समयr_पूर्णांकerrupt(chip->समयr, chip->समयr_ticks);
	पूर्ण
	snd_ymfpci_ग_लिखोw(chip, YDSXGR_INTFLAG, status);

	अगर (chip->rawmidi)
		snd_mpu401_uart_पूर्णांकerrupt(irq, chip->rawmidi->निजी_data);
	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware snd_ymfpci_playback =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP |
				 SNDRV_PCM_INFO_MMAP_VALID | 
				 SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_PAUSE |
				 SNDRV_PCM_INFO_RESUME),
	.क्रमmats =		SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		8000,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	256 * 1024, /* FIXME: enough? */
	.period_bytes_min =	64,
	.period_bytes_max =	256 * 1024, /* FIXME: enough? */
	.periods_min =		3,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_ymfpci_capture =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP |
				 SNDRV_PCM_INFO_MMAP_VALID |
				 SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_PAUSE |
				 SNDRV_PCM_INFO_RESUME),
	.क्रमmats =		SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		8000,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	256 * 1024, /* FIXME: enough? */
	.period_bytes_min =	64,
	.period_bytes_max =	256 * 1024, /* FIXME: enough? */
	.periods_min =		3,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

अटल व्योम snd_ymfpci_pcm_मुक्त_substream(काष्ठा snd_pcm_runसमय *runसमय)
अणु
	kमुक्त(runसमय->निजी_data);
पूर्ण

अटल पूर्णांक snd_ymfpci_playback_खोलो_1(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ymfpci *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_ymfpci_pcm *ypcm;
	पूर्णांक err;

	runसमय->hw = snd_ymfpci_playback;
	/* FIXME? True value is 256/48 = 5.33333 ms */
	err = snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय,
					   SNDRV_PCM_HW_PARAM_PERIOD_TIME,
					   5334, अच_पूर्णांक_उच्च);
	अगर (err < 0)
		वापस err;
	err = snd_pcm_hw_rule_noresample(runसमय, 48000);
	अगर (err < 0)
		वापस err;

	ypcm = kzalloc(माप(*ypcm), GFP_KERNEL);
	अगर (ypcm == शून्य)
		वापस -ENOMEM;
	ypcm->chip = chip;
	ypcm->type = PLAYBACK_VOICE;
	ypcm->substream = substream;
	runसमय->निजी_data = ypcm;
	runसमय->निजी_मुक्त = snd_ymfpci_pcm_मुक्त_substream;
	वापस 0;
पूर्ण

/* call with spinlock held */
अटल व्योम ymfpci_खोलो_extension(काष्ठा snd_ymfpci *chip)
अणु
	अगर (! chip->rear_खोलोed) अणु
		अगर (! chip->spdअगर_खोलोed) /* set AC3 */
			snd_ymfpci_ग_लिखोl(chip, YDSXGR_MODE,
					  snd_ymfpci_पढ़ोl(chip, YDSXGR_MODE) | (1 << 30));
		/* enable second codec (4CHEN) */
		snd_ymfpci_ग_लिखोw(chip, YDSXGR_SECCONFIG,
				  (snd_ymfpci_पढ़ोw(chip, YDSXGR_SECCONFIG) & ~0x0330) | 0x0010);
	पूर्ण
पूर्ण

/* call with spinlock held */
अटल व्योम ymfpci_बंद_extension(काष्ठा snd_ymfpci *chip)
अणु
	अगर (! chip->rear_खोलोed) अणु
		अगर (! chip->spdअगर_खोलोed)
			snd_ymfpci_ग_लिखोl(chip, YDSXGR_MODE,
					  snd_ymfpci_पढ़ोl(chip, YDSXGR_MODE) & ~(1 << 30));
		snd_ymfpci_ग_लिखोw(chip, YDSXGR_SECCONFIG,
				  (snd_ymfpci_पढ़ोw(chip, YDSXGR_SECCONFIG) & ~0x0330) & ~0x0010);
	पूर्ण
पूर्ण

अटल पूर्णांक snd_ymfpci_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ymfpci *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_ymfpci_pcm *ypcm;
	पूर्णांक err;
	
	अगर ((err = snd_ymfpci_playback_खोलो_1(substream)) < 0)
		वापस err;
	ypcm = runसमय->निजी_data;
	ypcm->output_front = 1;
	ypcm->output_rear = chip->mode_dup4ch ? 1 : 0;
	ypcm->swap_rear = 0;
	spin_lock_irq(&chip->reg_lock);
	अगर (ypcm->output_rear) अणु
		ymfpci_खोलो_extension(chip);
		chip->rear_खोलोed++;
	पूर्ण
	spin_unlock_irq(&chip->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ymfpci_playback_spdअगर_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ymfpci *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_ymfpci_pcm *ypcm;
	पूर्णांक err;
	
	अगर ((err = snd_ymfpci_playback_खोलो_1(substream)) < 0)
		वापस err;
	ypcm = runसमय->निजी_data;
	ypcm->output_front = 0;
	ypcm->output_rear = 1;
	ypcm->swap_rear = 1;
	spin_lock_irq(&chip->reg_lock);
	snd_ymfpci_ग_लिखोw(chip, YDSXGR_SPDIFOUTCTRL,
			  snd_ymfpci_पढ़ोw(chip, YDSXGR_SPDIFOUTCTRL) | 2);
	ymfpci_खोलो_extension(chip);
	chip->spdअगर_pcm_bits = chip->spdअगर_bits;
	snd_ymfpci_ग_लिखोw(chip, YDSXGR_SPDIFOUTSTATUS, chip->spdअगर_pcm_bits);
	chip->spdअगर_खोलोed++;
	spin_unlock_irq(&chip->reg_lock);

	chip->spdअगर_pcm_ctl->vd[0].access &= ~SNDRV_CTL_ELEM_ACCESS_INACTIVE;
	snd_ctl_notअगरy(chip->card, SNDRV_CTL_EVENT_MASK_VALUE |
		       SNDRV_CTL_EVENT_MASK_INFO, &chip->spdअगर_pcm_ctl->id);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ymfpci_playback_4ch_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ymfpci *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_ymfpci_pcm *ypcm;
	पूर्णांक err;
	
	अगर ((err = snd_ymfpci_playback_खोलो_1(substream)) < 0)
		वापस err;
	ypcm = runसमय->निजी_data;
	ypcm->output_front = 0;
	ypcm->output_rear = 1;
	ypcm->swap_rear = 0;
	spin_lock_irq(&chip->reg_lock);
	ymfpci_खोलो_extension(chip);
	chip->rear_खोलोed++;
	spin_unlock_irq(&chip->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ymfpci_capture_खोलो(काष्ठा snd_pcm_substream *substream,
				   u32 capture_bank_number)
अणु
	काष्ठा snd_ymfpci *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_ymfpci_pcm *ypcm;
	पूर्णांक err;

	runसमय->hw = snd_ymfpci_capture;
	/* FIXME? True value is 256/48 = 5.33333 ms */
	err = snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय,
					   SNDRV_PCM_HW_PARAM_PERIOD_TIME,
					   5334, अच_पूर्णांक_उच्च);
	अगर (err < 0)
		वापस err;
	err = snd_pcm_hw_rule_noresample(runसमय, 48000);
	अगर (err < 0)
		वापस err;

	ypcm = kzalloc(माप(*ypcm), GFP_KERNEL);
	अगर (ypcm == शून्य)
		वापस -ENOMEM;
	ypcm->chip = chip;
	ypcm->type = capture_bank_number + CAPTURE_REC;
	ypcm->substream = substream;	
	ypcm->capture_bank_number = capture_bank_number;
	chip->capture_substream[capture_bank_number] = substream;
	runसमय->निजी_data = ypcm;
	runसमय->निजी_मुक्त = snd_ymfpci_pcm_मुक्त_substream;
	snd_ymfpci_hw_start(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ymfpci_capture_rec_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_ymfpci_capture_खोलो(substream, 0);
पूर्ण

अटल पूर्णांक snd_ymfpci_capture_ac97_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_ymfpci_capture_खोलो(substream, 1);
पूर्ण

अटल पूर्णांक snd_ymfpci_playback_बंद_1(काष्ठा snd_pcm_substream *substream)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ymfpci_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ymfpci *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_ymfpci_pcm *ypcm = substream->runसमय->निजी_data;

	spin_lock_irq(&chip->reg_lock);
	अगर (ypcm->output_rear && chip->rear_खोलोed > 0) अणु
		chip->rear_खोलोed--;
		ymfpci_बंद_extension(chip);
	पूर्ण
	spin_unlock_irq(&chip->reg_lock);
	वापस snd_ymfpci_playback_बंद_1(substream);
पूर्ण

अटल पूर्णांक snd_ymfpci_playback_spdअगर_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ymfpci *chip = snd_pcm_substream_chip(substream);

	spin_lock_irq(&chip->reg_lock);
	chip->spdअगर_खोलोed = 0;
	ymfpci_बंद_extension(chip);
	snd_ymfpci_ग_लिखोw(chip, YDSXGR_SPDIFOUTCTRL,
			  snd_ymfpci_पढ़ोw(chip, YDSXGR_SPDIFOUTCTRL) & ~2);
	snd_ymfpci_ग_लिखोw(chip, YDSXGR_SPDIFOUTSTATUS, chip->spdअगर_bits);
	spin_unlock_irq(&chip->reg_lock);
	chip->spdअगर_pcm_ctl->vd[0].access |= SNDRV_CTL_ELEM_ACCESS_INACTIVE;
	snd_ctl_notअगरy(chip->card, SNDRV_CTL_EVENT_MASK_VALUE |
		       SNDRV_CTL_EVENT_MASK_INFO, &chip->spdअगर_pcm_ctl->id);
	वापस snd_ymfpci_playback_बंद_1(substream);
पूर्ण

अटल पूर्णांक snd_ymfpci_playback_4ch_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ymfpci *chip = snd_pcm_substream_chip(substream);

	spin_lock_irq(&chip->reg_lock);
	अगर (chip->rear_खोलोed > 0) अणु
		chip->rear_खोलोed--;
		ymfpci_बंद_extension(chip);
	पूर्ण
	spin_unlock_irq(&chip->reg_lock);
	वापस snd_ymfpci_playback_बंद_1(substream);
पूर्ण

अटल पूर्णांक snd_ymfpci_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ymfpci *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_ymfpci_pcm *ypcm = runसमय->निजी_data;

	अगर (ypcm != शून्य) अणु
		chip->capture_substream[ypcm->capture_bank_number] = शून्य;
		snd_ymfpci_hw_stop(chip);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_ymfpci_playback_ops = अणु
	.खोलो =			snd_ymfpci_playback_खोलो,
	.बंद =		snd_ymfpci_playback_बंद,
	.hw_params =		snd_ymfpci_playback_hw_params,
	.hw_मुक्त =		snd_ymfpci_playback_hw_मुक्त,
	.prepare =		snd_ymfpci_playback_prepare,
	.trigger =		snd_ymfpci_playback_trigger,
	.poपूर्णांकer =		snd_ymfpci_playback_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_ymfpci_capture_rec_ops = अणु
	.खोलो =			snd_ymfpci_capture_rec_खोलो,
	.बंद =		snd_ymfpci_capture_बंद,
	.hw_मुक्त =		snd_ymfpci_capture_hw_मुक्त,
	.prepare =		snd_ymfpci_capture_prepare,
	.trigger =		snd_ymfpci_capture_trigger,
	.poपूर्णांकer =		snd_ymfpci_capture_poपूर्णांकer,
पूर्ण;

पूर्णांक snd_ymfpci_pcm(काष्ठा snd_ymfpci *chip, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	अगर ((err = snd_pcm_new(chip->card, "YMFPCI", device, 32, 1, &pcm)) < 0)
		वापस err;
	pcm->निजी_data = chip;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_ymfpci_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_ymfpci_capture_rec_ops);

	/* global setup */
	pcm->info_flags = 0;
	म_नकल(pcm->name, "YMFPCI");
	chip->pcm = pcm;

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
				       &chip->pci->dev, 64*1024, 256*1024);

	वापस snd_pcm_add_chmap_ctls(pcm, SNDRV_PCM_STREAM_PLAYBACK,
				     snd_pcm_std_chmaps, 2, 0, शून्य);
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_ymfpci_capture_ac97_ops = अणु
	.खोलो =			snd_ymfpci_capture_ac97_खोलो,
	.बंद =		snd_ymfpci_capture_बंद,
	.hw_मुक्त =		snd_ymfpci_capture_hw_मुक्त,
	.prepare =		snd_ymfpci_capture_prepare,
	.trigger =		snd_ymfpci_capture_trigger,
	.poपूर्णांकer =		snd_ymfpci_capture_poपूर्णांकer,
पूर्ण;

पूर्णांक snd_ymfpci_pcm2(काष्ठा snd_ymfpci *chip, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	अगर ((err = snd_pcm_new(chip->card, "YMFPCI - PCM2", device, 0, 1, &pcm)) < 0)
		वापस err;
	pcm->निजी_data = chip;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_ymfpci_capture_ac97_ops);

	/* global setup */
	pcm->info_flags = 0;
	प्र_लिखो(pcm->name, "YMFPCI - %s",
		chip->device_id == PCI_DEVICE_ID_YAMAHA_754 ? "Direct Recording" : "AC'97");
	chip->pcm2 = pcm;

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
				       &chip->pci->dev, 64*1024, 256*1024);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_ymfpci_playback_spdअगर_ops = अणु
	.खोलो =			snd_ymfpci_playback_spdअगर_खोलो,
	.बंद =		snd_ymfpci_playback_spdअगर_बंद,
	.hw_params =		snd_ymfpci_playback_hw_params,
	.hw_मुक्त =		snd_ymfpci_playback_hw_मुक्त,
	.prepare =		snd_ymfpci_playback_prepare,
	.trigger =		snd_ymfpci_playback_trigger,
	.poपूर्णांकer =		snd_ymfpci_playback_poपूर्णांकer,
पूर्ण;

पूर्णांक snd_ymfpci_pcm_spdअगर(काष्ठा snd_ymfpci *chip, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	अगर ((err = snd_pcm_new(chip->card, "YMFPCI - IEC958", device, 1, 0, &pcm)) < 0)
		वापस err;
	pcm->निजी_data = chip;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_ymfpci_playback_spdअगर_ops);

	/* global setup */
	pcm->info_flags = 0;
	म_नकल(pcm->name, "YMFPCI - IEC958");
	chip->pcm_spdअगर = pcm;

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
				       &chip->pci->dev, 64*1024, 256*1024);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_ymfpci_playback_4ch_ops = अणु
	.खोलो =			snd_ymfpci_playback_4ch_खोलो,
	.बंद =		snd_ymfpci_playback_4ch_बंद,
	.hw_params =		snd_ymfpci_playback_hw_params,
	.hw_मुक्त =		snd_ymfpci_playback_hw_मुक्त,
	.prepare =		snd_ymfpci_playback_prepare,
	.trigger =		snd_ymfpci_playback_trigger,
	.poपूर्णांकer =		snd_ymfpci_playback_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_chmap_elem surround_map[] = अणु
	अणु .channels = 1,
	  .map = अणु SNDRV_CHMAP_MONO पूर्ण पूर्ण,
	अणु .channels = 2,
	  .map = अणु SNDRV_CHMAP_RL, SNDRV_CHMAP_RR पूर्ण पूर्ण,
	अणु पूर्ण
पूर्ण;

पूर्णांक snd_ymfpci_pcm_4ch(काष्ठा snd_ymfpci *chip, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	अगर ((err = snd_pcm_new(chip->card, "YMFPCI - Rear", device, 1, 0, &pcm)) < 0)
		वापस err;
	pcm->निजी_data = chip;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_ymfpci_playback_4ch_ops);

	/* global setup */
	pcm->info_flags = 0;
	म_नकल(pcm->name, "YMFPCI - Rear PCM");
	chip->pcm_4ch = pcm;

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
				       &chip->pci->dev, 64*1024, 256*1024);

	वापस snd_pcm_add_chmap_ctls(pcm, SNDRV_PCM_STREAM_PLAYBACK,
				     surround_map, 2, 0, शून्य);
पूर्ण

अटल पूर्णांक snd_ymfpci_spdअगर_शेष_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ymfpci_spdअगर_शेष_get(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ymfpci *chip = snd_kcontrol_chip(kcontrol);

	spin_lock_irq(&chip->reg_lock);
	ucontrol->value.iec958.status[0] = (chip->spdअगर_bits >> 0) & 0xff;
	ucontrol->value.iec958.status[1] = (chip->spdअगर_bits >> 8) & 0xff;
	ucontrol->value.iec958.status[3] = IEC958_AES3_CON_FS_48000;
	spin_unlock_irq(&chip->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ymfpci_spdअगर_शेष_put(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ymfpci *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;
	पूर्णांक change;

	val = ((ucontrol->value.iec958.status[0] & 0x3e) << 0) |
	      (ucontrol->value.iec958.status[1] << 8);
	spin_lock_irq(&chip->reg_lock);
	change = chip->spdअगर_bits != val;
	chip->spdअगर_bits = val;
	अगर ((snd_ymfpci_पढ़ोw(chip, YDSXGR_SPDIFOUTCTRL) & 1) && chip->pcm_spdअगर == शून्य)
		snd_ymfpci_ग_लिखोw(chip, YDSXGR_SPDIFOUTSTATUS, chip->spdअगर_bits);
	spin_unlock_irq(&chip->reg_lock);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ymfpci_spdअगर_शेष =
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =         SNDRV_CTL_NAME_IEC958("",PLAYBACK,DEFAULT),
	.info =		snd_ymfpci_spdअगर_शेष_info,
	.get =		snd_ymfpci_spdअगर_शेष_get,
	.put =		snd_ymfpci_spdअगर_शेष_put
पूर्ण;

अटल पूर्णांक snd_ymfpci_spdअगर_mask_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ymfpci_spdअगर_mask_get(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ymfpci *chip = snd_kcontrol_chip(kcontrol);

	spin_lock_irq(&chip->reg_lock);
	ucontrol->value.iec958.status[0] = 0x3e;
	ucontrol->value.iec958.status[1] = 0xff;
	spin_unlock_irq(&chip->reg_lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ymfpci_spdअगर_mask =
अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READ,
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =         SNDRV_CTL_NAME_IEC958("",PLAYBACK,CON_MASK),
	.info =		snd_ymfpci_spdअगर_mask_info,
	.get =		snd_ymfpci_spdअगर_mask_get,
पूर्ण;

अटल पूर्णांक snd_ymfpci_spdअगर_stream_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ymfpci_spdअगर_stream_get(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ymfpci *chip = snd_kcontrol_chip(kcontrol);

	spin_lock_irq(&chip->reg_lock);
	ucontrol->value.iec958.status[0] = (chip->spdअगर_pcm_bits >> 0) & 0xff;
	ucontrol->value.iec958.status[1] = (chip->spdअगर_pcm_bits >> 8) & 0xff;
	ucontrol->value.iec958.status[3] = IEC958_AES3_CON_FS_48000;
	spin_unlock_irq(&chip->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ymfpci_spdअगर_stream_put(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ymfpci *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;
	पूर्णांक change;

	val = ((ucontrol->value.iec958.status[0] & 0x3e) << 0) |
	      (ucontrol->value.iec958.status[1] << 8);
	spin_lock_irq(&chip->reg_lock);
	change = chip->spdअगर_pcm_bits != val;
	chip->spdअगर_pcm_bits = val;
	अगर ((snd_ymfpci_पढ़ोw(chip, YDSXGR_SPDIFOUTCTRL) & 2))
		snd_ymfpci_ग_लिखोw(chip, YDSXGR_SPDIFOUTSTATUS, chip->spdअगर_pcm_bits);
	spin_unlock_irq(&chip->reg_lock);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ymfpci_spdअगर_stream =
अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_INACTIVE,
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =         SNDRV_CTL_NAME_IEC958("",PLAYBACK,PCM_STREAM),
	.info =		snd_ymfpci_spdअगर_stream_info,
	.get =		snd_ymfpci_spdअगर_stream_get,
	.put =		snd_ymfpci_spdअगर_stream_put
पूर्ण;

अटल पूर्णांक snd_ymfpci_drec_source_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *info)
अणु
	अटल स्थिर अक्षर *स्थिर texts[3] = अणु"AC'97", "IEC958", "ZV Port"पूर्ण;

	वापस snd_ctl_क्रमागत_info(info, 1, 3, texts);
पूर्ण

अटल पूर्णांक snd_ymfpci_drec_source_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा snd_ymfpci *chip = snd_kcontrol_chip(kcontrol);
	u16 reg;

	spin_lock_irq(&chip->reg_lock);
	reg = snd_ymfpci_पढ़ोw(chip, YDSXGR_GLOBALCTRL);
	spin_unlock_irq(&chip->reg_lock);
	अगर (!(reg & 0x100))
		value->value.क्रमागतerated.item[0] = 0;
	अन्यथा
		value->value.क्रमागतerated.item[0] = 1 + ((reg & 0x200) != 0);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ymfpci_drec_source_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा snd_ymfpci *chip = snd_kcontrol_chip(kcontrol);
	u16 reg, old_reg;

	spin_lock_irq(&chip->reg_lock);
	old_reg = snd_ymfpci_पढ़ोw(chip, YDSXGR_GLOBALCTRL);
	अगर (value->value.क्रमागतerated.item[0] == 0)
		reg = old_reg & ~0x100;
	अन्यथा
		reg = (old_reg & ~0x300) | 0x100 | ((value->value.क्रमागतerated.item[0] == 2) << 9);
	snd_ymfpci_ग_लिखोw(chip, YDSXGR_GLOBALCTRL, reg);
	spin_unlock_irq(&chip->reg_lock);
	वापस reg != old_reg;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ymfpci_drec_source = अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =		"Direct Recording Source",
	.info =		snd_ymfpci_drec_source_info,
	.get =		snd_ymfpci_drec_source_get,
	.put =		snd_ymfpci_drec_source_put
पूर्ण;

/*
 *  Mixer controls
 */

#घोषणा YMFPCI_SINGLE(xname, xindex, reg, shअगरt) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .info = snd_ymfpci_info_single, \
  .get = snd_ymfpci_get_single, .put = snd_ymfpci_put_single, \
  .निजी_value = ((reg) | ((shअगरt) << 16)) पूर्ण

#घोषणा snd_ymfpci_info_single		snd_ctl_boolean_mono_info

अटल पूर्णांक snd_ymfpci_get_single(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ymfpci *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक reg = kcontrol->निजी_value & 0xffff;
	अचिन्हित पूर्णांक shअगरt = (kcontrol->निजी_value >> 16) & 0xff;
	अचिन्हित पूर्णांक mask = 1;
	
	चयन (reg) अणु
	हाल YDSXGR_SPDIFOUTCTRL: अवरोध;
	हाल YDSXGR_SPDIFINCTRL: अवरोध;
	शेष: वापस -EINVAL;
	पूर्ण
	ucontrol->value.पूर्णांकeger.value[0] =
		(snd_ymfpci_पढ़ोl(chip, reg) >> shअगरt) & mask;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ymfpci_put_single(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ymfpci *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक reg = kcontrol->निजी_value & 0xffff;
	अचिन्हित पूर्णांक shअगरt = (kcontrol->निजी_value >> 16) & 0xff;
 	अचिन्हित पूर्णांक mask = 1;
	पूर्णांक change;
	अचिन्हित पूर्णांक val, oval;
	
	चयन (reg) अणु
	हाल YDSXGR_SPDIFOUTCTRL: अवरोध;
	हाल YDSXGR_SPDIFINCTRL: अवरोध;
	शेष: वापस -EINVAL;
	पूर्ण
	val = (ucontrol->value.पूर्णांकeger.value[0] & mask);
	val <<= shअगरt;
	spin_lock_irq(&chip->reg_lock);
	oval = snd_ymfpci_पढ़ोl(chip, reg);
	val = (oval & ~(mask << shअगरt)) | val;
	change = val != oval;
	snd_ymfpci_ग_लिखोl(chip, reg, val);
	spin_unlock_irq(&chip->reg_lock);
	वापस change;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_LINEAR(db_scale_native, TLV_DB_GAIN_MUTE, 0);

#घोषणा YMFPCI_DOUBLE(xname, xindex, reg) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .access = SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_TLV_READ, \
  .info = snd_ymfpci_info_द्विगुन, \
  .get = snd_ymfpci_get_द्विगुन, .put = snd_ymfpci_put_द्विगुन, \
  .निजी_value = reg, \
  .tlv = अणु .p = db_scale_native पूर्ण पूर्ण

अटल पूर्णांक snd_ymfpci_info_द्विगुन(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अचिन्हित पूर्णांक reg = kcontrol->निजी_value;

	अगर (reg < 0x80 || reg >= 0xc0)
		वापस -EINVAL;
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 16383;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ymfpci_get_द्विगुन(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ymfpci *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक reg = kcontrol->निजी_value;
	अचिन्हित पूर्णांक shअगरt_left = 0, shअगरt_right = 16, mask = 16383;
	अचिन्हित पूर्णांक val;
	
	अगर (reg < 0x80 || reg >= 0xc0)
		वापस -EINVAL;
	spin_lock_irq(&chip->reg_lock);
	val = snd_ymfpci_पढ़ोl(chip, reg);
	spin_unlock_irq(&chip->reg_lock);
	ucontrol->value.पूर्णांकeger.value[0] = (val >> shअगरt_left) & mask;
	ucontrol->value.पूर्णांकeger.value[1] = (val >> shअगरt_right) & mask;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ymfpci_put_द्विगुन(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ymfpci *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक reg = kcontrol->निजी_value;
	अचिन्हित पूर्णांक shअगरt_left = 0, shअगरt_right = 16, mask = 16383;
	पूर्णांक change;
	अचिन्हित पूर्णांक val1, val2, oval;
	
	अगर (reg < 0x80 || reg >= 0xc0)
		वापस -EINVAL;
	val1 = ucontrol->value.पूर्णांकeger.value[0] & mask;
	val2 = ucontrol->value.पूर्णांकeger.value[1] & mask;
	val1 <<= shअगरt_left;
	val2 <<= shअगरt_right;
	spin_lock_irq(&chip->reg_lock);
	oval = snd_ymfpci_पढ़ोl(chip, reg);
	val1 = (oval & ~((mask << shअगरt_left) | (mask << shअगरt_right))) | val1 | val2;
	change = val1 != oval;
	snd_ymfpci_ग_लिखोl(chip, reg, val1);
	spin_unlock_irq(&chip->reg_lock);
	वापस change;
पूर्ण

अटल पूर्णांक snd_ymfpci_put_nativedacvol(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ymfpci *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक reg = YDSXGR_NATIVEDACOUTVOL;
	अचिन्हित पूर्णांक reg2 = YDSXGR_BUF441OUTVOL;
	पूर्णांक change;
	अचिन्हित पूर्णांक value, oval;
	
	value = ucontrol->value.पूर्णांकeger.value[0] & 0x3fff;
	value |= (ucontrol->value.पूर्णांकeger.value[1] & 0x3fff) << 16;
	spin_lock_irq(&chip->reg_lock);
	oval = snd_ymfpci_पढ़ोl(chip, reg);
	change = value != oval;
	snd_ymfpci_ग_लिखोl(chip, reg, value);
	snd_ymfpci_ग_लिखोl(chip, reg2, value);
	spin_unlock_irq(&chip->reg_lock);
	वापस change;
पूर्ण

/*
 * 4ch duplication
 */
#घोषणा snd_ymfpci_info_dup4ch		snd_ctl_boolean_mono_info

अटल पूर्णांक snd_ymfpci_get_dup4ch(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ymfpci *chip = snd_kcontrol_chip(kcontrol);
	ucontrol->value.पूर्णांकeger.value[0] = chip->mode_dup4ch;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ymfpci_put_dup4ch(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ymfpci *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	change = (ucontrol->value.पूर्णांकeger.value[0] != chip->mode_dup4ch);
	अगर (change)
		chip->mode_dup4ch = !!ucontrol->value.पूर्णांकeger.value[0];
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ymfpci_dup4ch = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "4ch Duplication",
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.info = snd_ymfpci_info_dup4ch,
	.get = snd_ymfpci_get_dup4ch,
	.put = snd_ymfpci_put_dup4ch,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_ymfpci_controls[] = अणु
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Wave Playback Volume",
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |
		  SNDRV_CTL_ELEM_ACCESS_TLV_READ,
	.info = snd_ymfpci_info_द्विगुन,
	.get = snd_ymfpci_get_द्विगुन,
	.put = snd_ymfpci_put_nativedacvol,
	.निजी_value = YDSXGR_NATIVEDACOUTVOL,
	.tlv = अणु .p = db_scale_native पूर्ण,
पूर्ण,
YMFPCI_DOUBLE("Wave Capture Volume", 0, YDSXGR_NATIVEDACLOOPVOL),
YMFPCI_DOUBLE("Digital Capture Volume", 0, YDSXGR_NATIVEDACINVOL),
YMFPCI_DOUBLE("Digital Capture Volume", 1, YDSXGR_NATIVEADCINVOL),
YMFPCI_DOUBLE("ADC Playback Volume", 0, YDSXGR_PRIADCOUTVOL),
YMFPCI_DOUBLE("ADC Capture Volume", 0, YDSXGR_PRIADCLOOPVOL),
YMFPCI_DOUBLE("ADC Playback Volume", 1, YDSXGR_SECADCOUTVOL),
YMFPCI_DOUBLE("ADC Capture Volume", 1, YDSXGR_SECADCLOOPVOL),
YMFPCI_DOUBLE("FM Legacy Playback Volume", 0, YDSXGR_LEGACYOUTVOL),
YMFPCI_DOUBLE(SNDRV_CTL_NAME_IEC958("AC97 ", PLAYBACK,VOLUME), 0, YDSXGR_ZVOUTVOL),
YMFPCI_DOUBLE(SNDRV_CTL_NAME_IEC958("", CAPTURE,VOLUME), 0, YDSXGR_ZVLOOPVOL),
YMFPCI_DOUBLE(SNDRV_CTL_NAME_IEC958("AC97 ",PLAYBACK,VOLUME), 1, YDSXGR_SPDIFOUTVOL),
YMFPCI_DOUBLE(SNDRV_CTL_NAME_IEC958("",CAPTURE,VOLUME), 1, YDSXGR_SPDIFLOOPVOL),
YMFPCI_SINGLE(SNDRV_CTL_NAME_IEC958("",PLAYBACK,SWITCH), 0, YDSXGR_SPDIFOUTCTRL, 0),
YMFPCI_SINGLE(SNDRV_CTL_NAME_IEC958("",CAPTURE,SWITCH), 0, YDSXGR_SPDIFINCTRL, 0),
YMFPCI_SINGLE(SNDRV_CTL_NAME_IEC958("Loop",NONE,NONE), 0, YDSXGR_SPDIFINCTRL, 4),
पूर्ण;


/*
 * GPIO
 */

अटल पूर्णांक snd_ymfpci_get_gpio_out(काष्ठा snd_ymfpci *chip, पूर्णांक pin)
अणु
	u16 reg, mode;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->reg_lock, flags);
	reg = snd_ymfpci_पढ़ोw(chip, YDSXGR_GPIOFUNCENABLE);
	reg &= ~(1 << (pin + 8));
	reg |= (1 << pin);
	snd_ymfpci_ग_लिखोw(chip, YDSXGR_GPIOFUNCENABLE, reg);
	/* set the level mode क्रम input line */
	mode = snd_ymfpci_पढ़ोw(chip, YDSXGR_GPIOTYPECONFIG);
	mode &= ~(3 << (pin * 2));
	snd_ymfpci_ग_लिखोw(chip, YDSXGR_GPIOTYPECONFIG, mode);
	snd_ymfpci_ग_लिखोw(chip, YDSXGR_GPIOFUNCENABLE, reg | (1 << (pin + 8)));
	mode = snd_ymfpci_पढ़ोw(chip, YDSXGR_GPIOINSTATUS);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस (mode >> pin) & 1;
पूर्ण

अटल पूर्णांक snd_ymfpci_set_gpio_out(काष्ठा snd_ymfpci *chip, पूर्णांक pin, पूर्णांक enable)
अणु
	u16 reg;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->reg_lock, flags);
	reg = snd_ymfpci_पढ़ोw(chip, YDSXGR_GPIOFUNCENABLE);
	reg &= ~(1 << pin);
	reg &= ~(1 << (pin + 8));
	snd_ymfpci_ग_लिखोw(chip, YDSXGR_GPIOFUNCENABLE, reg);
	snd_ymfpci_ग_लिखोw(chip, YDSXGR_GPIOOUTCTRL, enable << pin);
	snd_ymfpci_ग_लिखोw(chip, YDSXGR_GPIOFUNCENABLE, reg | (1 << (pin + 8)));
	spin_unlock_irqrestore(&chip->reg_lock, flags);

	वापस 0;
पूर्ण

#घोषणा snd_ymfpci_gpio_sw_info		snd_ctl_boolean_mono_info

अटल पूर्णांक snd_ymfpci_gpio_sw_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ymfpci *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक pin = (पूर्णांक)kcontrol->निजी_value;
	ucontrol->value.पूर्णांकeger.value[0] = snd_ymfpci_get_gpio_out(chip, pin);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ymfpci_gpio_sw_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ymfpci *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक pin = (पूर्णांक)kcontrol->निजी_value;

	अगर (snd_ymfpci_get_gpio_out(chip, pin) != ucontrol->value.पूर्णांकeger.value[0]) अणु
		snd_ymfpci_set_gpio_out(chip, pin, !!ucontrol->value.पूर्णांकeger.value[0]);
		ucontrol->value.पूर्णांकeger.value[0] = snd_ymfpci_get_gpio_out(chip, pin);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ymfpci_rear_shared = अणु
	.name = "Shared Rear/Line-In Switch",
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.info = snd_ymfpci_gpio_sw_info,
	.get = snd_ymfpci_gpio_sw_get,
	.put = snd_ymfpci_gpio_sw_put,
	.निजी_value = 2,
पूर्ण;

/*
 * PCM voice volume
 */

अटल पूर्णांक snd_ymfpci_pcm_vol_info(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 0x8000;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ymfpci_pcm_vol_get(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ymfpci *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक subs = kcontrol->id.subdevice;

	ucontrol->value.पूर्णांकeger.value[0] = chip->pcm_mixer[subs].left;
	ucontrol->value.पूर्णांकeger.value[1] = chip->pcm_mixer[subs].right;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ymfpci_pcm_vol_put(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ymfpci *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक subs = kcontrol->id.subdevice;
	काष्ठा snd_pcm_substream *substream;
	अचिन्हित दीर्घ flags;

	अगर (ucontrol->value.पूर्णांकeger.value[0] != chip->pcm_mixer[subs].left ||
	    ucontrol->value.पूर्णांकeger.value[1] != chip->pcm_mixer[subs].right) अणु
		chip->pcm_mixer[subs].left = ucontrol->value.पूर्णांकeger.value[0];
		chip->pcm_mixer[subs].right = ucontrol->value.पूर्णांकeger.value[1];
		अगर (chip->pcm_mixer[subs].left > 0x8000)
			chip->pcm_mixer[subs].left = 0x8000;
		अगर (chip->pcm_mixer[subs].right > 0x8000)
			chip->pcm_mixer[subs].right = 0x8000;

		substream = (काष्ठा snd_pcm_substream *)kcontrol->निजी_value;
		spin_lock_irqsave(&chip->voice_lock, flags);
		अगर (substream->runसमय && substream->runसमय->निजी_data) अणु
			काष्ठा snd_ymfpci_pcm *ypcm = substream->runसमय->निजी_data;
			अगर (!ypcm->use_441_slot)
				ypcm->update_pcm_vol = 2;
		पूर्ण
		spin_unlock_irqrestore(&chip->voice_lock, flags);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ymfpci_pcm_volume = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
	.name = "PCM Playback Volume",
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |
		SNDRV_CTL_ELEM_ACCESS_INACTIVE,
	.info = snd_ymfpci_pcm_vol_info,
	.get = snd_ymfpci_pcm_vol_get,
	.put = snd_ymfpci_pcm_vol_put,
पूर्ण;


/*
 *  Mixer routines
 */

अटल व्योम snd_ymfpci_mixer_मुक्त_ac97_bus(काष्ठा snd_ac97_bus *bus)
अणु
	काष्ठा snd_ymfpci *chip = bus->निजी_data;
	chip->ac97_bus = शून्य;
पूर्ण

अटल व्योम snd_ymfpci_mixer_मुक्त_ac97(काष्ठा snd_ac97 *ac97)
अणु
	काष्ठा snd_ymfpci *chip = ac97->निजी_data;
	chip->ac97 = शून्य;
पूर्ण

पूर्णांक snd_ymfpci_mixer(काष्ठा snd_ymfpci *chip, पूर्णांक rear_चयन)
अणु
	काष्ठा snd_ac97_ढाँचा ac97;
	काष्ठा snd_kcontrol *kctl;
	काष्ठा snd_pcm_substream *substream;
	अचिन्हित पूर्णांक idx;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_ac97_bus_ops ops = अणु
		.ग_लिखो = snd_ymfpci_codec_ग_लिखो,
		.पढ़ो = snd_ymfpci_codec_पढ़ो,
	पूर्ण;

	अगर ((err = snd_ac97_bus(chip->card, 0, &ops, chip, &chip->ac97_bus)) < 0)
		वापस err;
	chip->ac97_bus->निजी_मुक्त = snd_ymfpci_mixer_मुक्त_ac97_bus;
	chip->ac97_bus->no_vra = 1; /* YMFPCI करोesn't need VRA */

	स_रखो(&ac97, 0, माप(ac97));
	ac97.निजी_data = chip;
	ac97.निजी_मुक्त = snd_ymfpci_mixer_मुक्त_ac97;
	अगर ((err = snd_ac97_mixer(chip->ac97_bus, &ac97, &chip->ac97)) < 0)
		वापस err;

	/* to be sure */
	snd_ac97_update_bits(chip->ac97, AC97_EXTENDED_STATUS,
			     AC97_EA_VRA|AC97_EA_VRM, 0);

	क्रम (idx = 0; idx < ARRAY_SIZE(snd_ymfpci_controls); idx++) अणु
		अगर ((err = snd_ctl_add(chip->card, snd_ctl_new1(&snd_ymfpci_controls[idx], chip))) < 0)
			वापस err;
	पूर्ण
	अगर (chip->ac97->ext_id & AC97_EI_SDAC) अणु
		kctl = snd_ctl_new1(&snd_ymfpci_dup4ch, chip);
		err = snd_ctl_add(chip->card, kctl);
		अगर (err < 0)
			वापस err;
	पूर्ण

	/* add S/PDIF control */
	अगर (snd_BUG_ON(!chip->pcm_spdअगर))
		वापस -ENXIO;
	अगर ((err = snd_ctl_add(chip->card, kctl = snd_ctl_new1(&snd_ymfpci_spdअगर_शेष, chip))) < 0)
		वापस err;
	kctl->id.device = chip->pcm_spdअगर->device;
	अगर ((err = snd_ctl_add(chip->card, kctl = snd_ctl_new1(&snd_ymfpci_spdअगर_mask, chip))) < 0)
		वापस err;
	kctl->id.device = chip->pcm_spdअगर->device;
	अगर ((err = snd_ctl_add(chip->card, kctl = snd_ctl_new1(&snd_ymfpci_spdअगर_stream, chip))) < 0)
		वापस err;
	kctl->id.device = chip->pcm_spdअगर->device;
	chip->spdअगर_pcm_ctl = kctl;

	/* direct recording source */
	अगर (chip->device_id == PCI_DEVICE_ID_YAMAHA_754 &&
	    (err = snd_ctl_add(chip->card, kctl = snd_ctl_new1(&snd_ymfpci_drec_source, chip))) < 0)
		वापस err;

	/*
	 * shared rear/line-in
	 */
	अगर (rear_चयन) अणु
		अगर ((err = snd_ctl_add(chip->card, snd_ctl_new1(&snd_ymfpci_rear_shared, chip))) < 0)
			वापस err;
	पूर्ण

	/* per-voice volume */
	substream = chip->pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream;
	क्रम (idx = 0; idx < 32; ++idx) अणु
		kctl = snd_ctl_new1(&snd_ymfpci_pcm_volume, chip);
		अगर (!kctl)
			वापस -ENOMEM;
		kctl->id.device = chip->pcm->device;
		kctl->id.subdevice = idx;
		kctl->निजी_value = (अचिन्हित दीर्घ)substream;
		अगर ((err = snd_ctl_add(chip->card, kctl)) < 0)
			वापस err;
		chip->pcm_mixer[idx].left = 0x8000;
		chip->pcm_mixer[idx].right = 0x8000;
		chip->pcm_mixer[idx].ctl = kctl;
		substream = substream->next;
	पूर्ण

	वापस 0;
पूर्ण


/*
 * समयr
 */

अटल पूर्णांक snd_ymfpci_समयr_start(काष्ठा snd_समयr *समयr)
अणु
	काष्ठा snd_ymfpci *chip;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक count;

	chip = snd_समयr_chip(समयr);
	spin_lock_irqsave(&chip->reg_lock, flags);
	अगर (समयr->sticks > 1) अणु
		chip->समयr_ticks = समयr->sticks;
		count = समयr->sticks - 1;
	पूर्ण अन्यथा अणु
		/*
		 * Divisor 1 is not allowed; fake it by using भागisor 2 and
		 * counting two ticks क्रम each पूर्णांकerrupt.
		 */
		chip->समयr_ticks = 2;
		count = 2 - 1;
	पूर्ण
	snd_ymfpci_ग_लिखोw(chip, YDSXGR_TIMERCOUNT, count);
	snd_ymfpci_ग_लिखोb(chip, YDSXGR_TIMERCTRL, 0x03);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ymfpci_समयr_stop(काष्ठा snd_समयr *समयr)
अणु
	काष्ठा snd_ymfpci *chip;
	अचिन्हित दीर्घ flags;

	chip = snd_समयr_chip(समयr);
	spin_lock_irqsave(&chip->reg_lock, flags);
	snd_ymfpci_ग_लिखोb(chip, YDSXGR_TIMERCTRL, 0x00);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ymfpci_समयr_precise_resolution(काष्ठा snd_समयr *समयr,
					       अचिन्हित दीर्घ *num, अचिन्हित दीर्घ *den)
अणु
	*num = 1;
	*den = 96000;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_समयr_hardware snd_ymfpci_समयr_hw = अणु
	.flags = SNDRV_TIMER_HW_AUTO,
	.resolution = 10417, /* 1 / 96 kHz = 10.41666...us */
	.ticks = 0x10000,
	.start = snd_ymfpci_समयr_start,
	.stop = snd_ymfpci_समयr_stop,
	.precise_resolution = snd_ymfpci_समयr_precise_resolution,
पूर्ण;

पूर्णांक snd_ymfpci_समयr(काष्ठा snd_ymfpci *chip, पूर्णांक device)
अणु
	काष्ठा snd_समयr *समयr = शून्य;
	काष्ठा snd_समयr_id tid;
	पूर्णांक err;

	tid.dev_class = SNDRV_TIMER_CLASS_CARD;
	tid.dev_sclass = SNDRV_TIMER_SCLASS_NONE;
	tid.card = chip->card->number;
	tid.device = device;
	tid.subdevice = 0;
	अगर ((err = snd_समयr_new(chip->card, "YMFPCI", &tid, &समयr)) >= 0) अणु
		म_नकल(समयr->name, "YMFPCI timer");
		समयr->निजी_data = chip;
		समयr->hw = snd_ymfpci_समयr_hw;
	पूर्ण
	chip->समयr = समयr;
	वापस err;
पूर्ण


/*
 *  proc पूर्णांकerface
 */

अटल व्योम snd_ymfpci_proc_पढ़ो(काष्ठा snd_info_entry *entry, 
				 काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_ymfpci *chip = entry->निजी_data;
	पूर्णांक i;
	
	snd_iम_लिखो(buffer, "YMFPCI\n\n");
	क्रम (i = 0; i <= YDSXGR_WORKBASE; i += 4)
		snd_iम_लिखो(buffer, "%04x: %04x\n", i, snd_ymfpci_पढ़ोl(chip, i));
पूर्ण

अटल पूर्णांक snd_ymfpci_proc_init(काष्ठा snd_card *card, काष्ठा snd_ymfpci *chip)
अणु
	वापस snd_card_ro_proc_new(card, "ymfpci", chip, snd_ymfpci_proc_पढ़ो);
पूर्ण

/*
 *  initialization routines
 */

अटल व्योम snd_ymfpci_aclink_reset(काष्ठा pci_dev * pci)
अणु
	u8 cmd;

	pci_पढ़ो_config_byte(pci, PCIR_DSXG_CTRL, &cmd);
#अगर 0 // क्रमce to reset
	अगर (cmd & 0x03) अणु
#पूर्ण_अगर
		pci_ग_लिखो_config_byte(pci, PCIR_DSXG_CTRL, cmd & 0xfc);
		pci_ग_लिखो_config_byte(pci, PCIR_DSXG_CTRL, cmd | 0x03);
		pci_ग_लिखो_config_byte(pci, PCIR_DSXG_CTRL, cmd & 0xfc);
		pci_ग_लिखो_config_word(pci, PCIR_DSXG_PWRCTRL1, 0);
		pci_ग_लिखो_config_word(pci, PCIR_DSXG_PWRCTRL2, 0);
#अगर 0
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम snd_ymfpci_enable_dsp(काष्ठा snd_ymfpci *chip)
अणु
	snd_ymfpci_ग_लिखोl(chip, YDSXGR_CONFIG, 0x00000001);
पूर्ण

अटल व्योम snd_ymfpci_disable_dsp(काष्ठा snd_ymfpci *chip)
अणु
	u32 val;
	पूर्णांक समयout = 1000;

	val = snd_ymfpci_पढ़ोl(chip, YDSXGR_CONFIG);
	अगर (val)
		snd_ymfpci_ग_लिखोl(chip, YDSXGR_CONFIG, 0x00000000);
	जबतक (समयout-- > 0) अणु
		val = snd_ymfpci_पढ़ोl(chip, YDSXGR_STATUS);
		अगर ((val & 0x00000002) == 0)
			अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक snd_ymfpci_request_firmware(काष्ठा snd_ymfpci *chip)
अणु
	पूर्णांक err, is_1e;
	स्थिर अक्षर *name;

	err = request_firmware(&chip->dsp_microcode, "yamaha/ds1_dsp.fw",
			       &chip->pci->dev);
	अगर (err >= 0) अणु
		अगर (chip->dsp_microcode->size != YDSXG_DSPLENGTH) अणु
			dev_err(chip->card->dev,
				"DSP microcode has wrong size\n");
			err = -EINVAL;
		पूर्ण
	पूर्ण
	अगर (err < 0)
		वापस err;
	is_1e = chip->device_id == PCI_DEVICE_ID_YAMAHA_724F ||
		chip->device_id == PCI_DEVICE_ID_YAMAHA_740C ||
		chip->device_id == PCI_DEVICE_ID_YAMAHA_744 ||
		chip->device_id == PCI_DEVICE_ID_YAMAHA_754;
	name = is_1e ? "yamaha/ds1e_ctrl.fw" : "yamaha/ds1_ctrl.fw";
	err = request_firmware(&chip->controller_microcode, name,
			       &chip->pci->dev);
	अगर (err >= 0) अणु
		अगर (chip->controller_microcode->size != YDSXG_CTRLLENGTH) अणु
			dev_err(chip->card->dev,
				"controller microcode has wrong size\n");
			err = -EINVAL;
		पूर्ण
	पूर्ण
	अगर (err < 0)
		वापस err;
	वापस 0;
पूर्ण

MODULE_FIRMWARE("yamaha/ds1_dsp.fw");
MODULE_FIRMWARE("yamaha/ds1_ctrl.fw");
MODULE_FIRMWARE("yamaha/ds1e_ctrl.fw");

अटल व्योम snd_ymfpci_करोwnload_image(काष्ठा snd_ymfpci *chip)
अणु
	पूर्णांक i;
	u16 ctrl;
	स्थिर __le32 *inst;

	snd_ymfpci_ग_लिखोl(chip, YDSXGR_NATIVEDACOUTVOL, 0x00000000);
	snd_ymfpci_disable_dsp(chip);
	snd_ymfpci_ग_लिखोl(chip, YDSXGR_MODE, 0x00010000);
	snd_ymfpci_ग_लिखोl(chip, YDSXGR_MODE, 0x00000000);
	snd_ymfpci_ग_लिखोl(chip, YDSXGR_MAPOFREC, 0x00000000);
	snd_ymfpci_ग_लिखोl(chip, YDSXGR_MAPOFEFFECT, 0x00000000);
	snd_ymfpci_ग_लिखोl(chip, YDSXGR_PLAYCTRLBASE, 0x00000000);
	snd_ymfpci_ग_लिखोl(chip, YDSXGR_RECCTRLBASE, 0x00000000);
	snd_ymfpci_ग_लिखोl(chip, YDSXGR_EFFCTRLBASE, 0x00000000);
	ctrl = snd_ymfpci_पढ़ोw(chip, YDSXGR_GLOBALCTRL);
	snd_ymfpci_ग_लिखोw(chip, YDSXGR_GLOBALCTRL, ctrl & ~0x0007);

	/* setup DSP inकाष्ठाion code */
	inst = (स्थिर __le32 *)chip->dsp_microcode->data;
	क्रम (i = 0; i < YDSXG_DSPLENGTH / 4; i++)
		snd_ymfpci_ग_लिखोl(chip, YDSXGR_DSPINSTRAM + (i << 2),
				  le32_to_cpu(inst[i]));

	/* setup control inकाष्ठाion code */
	inst = (स्थिर __le32 *)chip->controller_microcode->data;
	क्रम (i = 0; i < YDSXG_CTRLLENGTH / 4; i++)
		snd_ymfpci_ग_लिखोl(chip, YDSXGR_CTRLINSTRAM + (i << 2),
				  le32_to_cpu(inst[i]));

	snd_ymfpci_enable_dsp(chip);
पूर्ण

अटल पूर्णांक snd_ymfpci_meदो_स्मृति(काष्ठा snd_ymfpci *chip)
अणु
	दीर्घ size, playback_ctrl_size;
	पूर्णांक voice, bank, reg;
	u8 *ptr;
	dma_addr_t ptr_addr;

	playback_ctrl_size = 4 + 4 * YDSXG_PLAYBACK_VOICES;
	chip->bank_size_playback = snd_ymfpci_पढ़ोl(chip, YDSXGR_PLAYCTRLSIZE) << 2;
	chip->bank_size_capture = snd_ymfpci_पढ़ोl(chip, YDSXGR_RECCTRLSIZE) << 2;
	chip->bank_size_effect = snd_ymfpci_पढ़ोl(chip, YDSXGR_EFFCTRLSIZE) << 2;
	chip->work_size = YDSXG_DEFAULT_WORK_SIZE;
	
	size = ALIGN(playback_ctrl_size, 0x100) +
	       ALIGN(chip->bank_size_playback * 2 * YDSXG_PLAYBACK_VOICES, 0x100) +
	       ALIGN(chip->bank_size_capture * 2 * YDSXG_CAPTURE_VOICES, 0x100) +
	       ALIGN(chip->bank_size_effect * 2 * YDSXG_EFFECT_VOICES, 0x100) +
	       chip->work_size;
	/* work_ptr must be aligned to 256 bytes, but it's alपढ़ोy
	   covered with the kernel page allocation mechanism */
	अगर (snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, &chip->pci->dev,
				size, &chip->work_ptr) < 0) 
		वापस -ENOMEM;
	ptr = chip->work_ptr.area;
	ptr_addr = chip->work_ptr.addr;
	स_रखो(ptr, 0, size);	/* क्रम sure */

	chip->bank_base_playback = ptr;
	chip->bank_base_playback_addr = ptr_addr;
	chip->ctrl_playback = (__le32 *)ptr;
	chip->ctrl_playback[0] = cpu_to_le32(YDSXG_PLAYBACK_VOICES);
	ptr += ALIGN(playback_ctrl_size, 0x100);
	ptr_addr += ALIGN(playback_ctrl_size, 0x100);
	क्रम (voice = 0; voice < YDSXG_PLAYBACK_VOICES; voice++) अणु
		chip->voices[voice].number = voice;
		chip->voices[voice].bank = (काष्ठा snd_ymfpci_playback_bank *)ptr;
		chip->voices[voice].bank_addr = ptr_addr;
		क्रम (bank = 0; bank < 2; bank++) अणु
			chip->bank_playback[voice][bank] = (काष्ठा snd_ymfpci_playback_bank *)ptr;
			ptr += chip->bank_size_playback;
			ptr_addr += chip->bank_size_playback;
		पूर्ण
	पूर्ण
	ptr = (अक्षर *)ALIGN((अचिन्हित दीर्घ)ptr, 0x100);
	ptr_addr = ALIGN(ptr_addr, 0x100);
	chip->bank_base_capture = ptr;
	chip->bank_base_capture_addr = ptr_addr;
	क्रम (voice = 0; voice < YDSXG_CAPTURE_VOICES; voice++)
		क्रम (bank = 0; bank < 2; bank++) अणु
			chip->bank_capture[voice][bank] = (काष्ठा snd_ymfpci_capture_bank *)ptr;
			ptr += chip->bank_size_capture;
			ptr_addr += chip->bank_size_capture;
		पूर्ण
	ptr = (अक्षर *)ALIGN((अचिन्हित दीर्घ)ptr, 0x100);
	ptr_addr = ALIGN(ptr_addr, 0x100);
	chip->bank_base_effect = ptr;
	chip->bank_base_effect_addr = ptr_addr;
	क्रम (voice = 0; voice < YDSXG_EFFECT_VOICES; voice++)
		क्रम (bank = 0; bank < 2; bank++) अणु
			chip->bank_effect[voice][bank] = (काष्ठा snd_ymfpci_effect_bank *)ptr;
			ptr += chip->bank_size_effect;
			ptr_addr += chip->bank_size_effect;
		पूर्ण
	ptr = (अक्षर *)ALIGN((अचिन्हित दीर्घ)ptr, 0x100);
	ptr_addr = ALIGN(ptr_addr, 0x100);
	chip->work_base = ptr;
	chip->work_base_addr = ptr_addr;
	
	snd_BUG_ON(ptr + chip->work_size !=
		   chip->work_ptr.area + chip->work_ptr.bytes);

	snd_ymfpci_ग_लिखोl(chip, YDSXGR_PLAYCTRLBASE, chip->bank_base_playback_addr);
	snd_ymfpci_ग_लिखोl(chip, YDSXGR_RECCTRLBASE, chip->bank_base_capture_addr);
	snd_ymfpci_ग_लिखोl(chip, YDSXGR_EFFCTRLBASE, chip->bank_base_effect_addr);
	snd_ymfpci_ग_लिखोl(chip, YDSXGR_WORKBASE, chip->work_base_addr);
	snd_ymfpci_ग_लिखोl(chip, YDSXGR_WORKSIZE, chip->work_size >> 2);

	/* S/PDIF output initialization */
	chip->spdअगर_bits = chip->spdअगर_pcm_bits = SNDRV_PCM_DEFAULT_CON_SPDIF & 0xffff;
	snd_ymfpci_ग_लिखोw(chip, YDSXGR_SPDIFOUTCTRL, 0);
	snd_ymfpci_ग_लिखोw(chip, YDSXGR_SPDIFOUTSTATUS, chip->spdअगर_bits);

	/* S/PDIF input initialization */
	snd_ymfpci_ग_लिखोw(chip, YDSXGR_SPDIFINCTRL, 0);

	/* digital mixer setup */
	क्रम (reg = 0x80; reg < 0xc0; reg += 4)
		snd_ymfpci_ग_लिखोl(chip, reg, 0);
	snd_ymfpci_ग_लिखोl(chip, YDSXGR_NATIVEDACOUTVOL, 0x3fff3fff);
	snd_ymfpci_ग_लिखोl(chip, YDSXGR_BUF441OUTVOL, 0x3fff3fff);
	snd_ymfpci_ग_लिखोl(chip, YDSXGR_ZVOUTVOL, 0x3fff3fff);
	snd_ymfpci_ग_लिखोl(chip, YDSXGR_SPDIFOUTVOL, 0x3fff3fff);
	snd_ymfpci_ग_लिखोl(chip, YDSXGR_NATIVEADCINVOL, 0x3fff3fff);
	snd_ymfpci_ग_लिखोl(chip, YDSXGR_NATIVEDACINVOL, 0x3fff3fff);
	snd_ymfpci_ग_लिखोl(chip, YDSXGR_PRIADCLOOPVOL, 0x3fff3fff);
	snd_ymfpci_ग_लिखोl(chip, YDSXGR_LEGACYOUTVOL, 0x3fff3fff);
	
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ymfpci_मुक्त(काष्ठा snd_ymfpci *chip)
अणु
	u16 ctrl;

	अगर (snd_BUG_ON(!chip))
		वापस -EINVAL;

	अगर (chip->res_reg_area) अणु	/* करोn't touch busy hardware */
		snd_ymfpci_ग_लिखोl(chip, YDSXGR_NATIVEDACOUTVOL, 0);
		snd_ymfpci_ग_लिखोl(chip, YDSXGR_BUF441OUTVOL, 0);
		snd_ymfpci_ग_लिखोl(chip, YDSXGR_LEGACYOUTVOL, 0);
		snd_ymfpci_ग_लिखोl(chip, YDSXGR_STATUS, ~0);
		snd_ymfpci_disable_dsp(chip);
		snd_ymfpci_ग_लिखोl(chip, YDSXGR_PLAYCTRLBASE, 0);
		snd_ymfpci_ग_लिखोl(chip, YDSXGR_RECCTRLBASE, 0);
		snd_ymfpci_ग_लिखोl(chip, YDSXGR_EFFCTRLBASE, 0);
		snd_ymfpci_ग_लिखोl(chip, YDSXGR_WORKBASE, 0);
		snd_ymfpci_ग_लिखोl(chip, YDSXGR_WORKSIZE, 0);
		ctrl = snd_ymfpci_पढ़ोw(chip, YDSXGR_GLOBALCTRL);
		snd_ymfpci_ग_लिखोw(chip, YDSXGR_GLOBALCTRL, ctrl & ~0x0007);
	पूर्ण

	snd_ymfpci_ac3_करोne(chip);

	/* Set PCI device to D3 state */
#अगर 0
	/* FIXME: temporarily disabled, otherwise we cannot fire up
	 * the chip again unless reboot.  ACPI bug?
	 */
	pci_set_घातer_state(chip->pci, PCI_D3hot);
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_SLEEP
	kमुक्त(chip->saved_regs);
#पूर्ण_अगर
	अगर (chip->irq >= 0)
		मुक्त_irq(chip->irq, chip);
	release_and_मुक्त_resource(chip->mpu_res);
	release_and_मुक्त_resource(chip->fm_res);
	snd_ymfpci_मुक्त_gameport(chip);
	iounmap(chip->reg_area_virt);
	अगर (chip->work_ptr.area)
		snd_dma_मुक्त_pages(&chip->work_ptr);
	
	release_and_मुक्त_resource(chip->res_reg_area);

	pci_ग_लिखो_config_word(chip->pci, 0x40, chip->old_legacy_ctrl);
	
	pci_disable_device(chip->pci);
	release_firmware(chip->dsp_microcode);
	release_firmware(chip->controller_microcode);
	kमुक्त(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ymfpci_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_ymfpci *chip = device->device_data;
	वापस snd_ymfpci_मुक्त(chip);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल स्थिर पूर्णांक saved_regs_index[] = अणु
	/* spdअगर */
	YDSXGR_SPDIFOUTCTRL,
	YDSXGR_SPDIFOUTSTATUS,
	YDSXGR_SPDIFINCTRL,
	/* volumes */
	YDSXGR_PRIADCLOOPVOL,
	YDSXGR_NATIVEDACINVOL,
	YDSXGR_NATIVEDACOUTVOL,
	YDSXGR_BUF441OUTVOL,
	YDSXGR_NATIVEADCINVOL,
	YDSXGR_SPDIFLOOPVOL,
	YDSXGR_SPDIFOUTVOL,
	YDSXGR_ZVOUTVOL,
	YDSXGR_LEGACYOUTVOL,
	/* address bases */
	YDSXGR_PLAYCTRLBASE,
	YDSXGR_RECCTRLBASE,
	YDSXGR_EFFCTRLBASE,
	YDSXGR_WORKBASE,
	/* capture set up */
	YDSXGR_MAPOFREC,
	YDSXGR_RECFORMAT,
	YDSXGR_RECSLOTSR,
	YDSXGR_ADCFORMAT,
	YDSXGR_ADCSLOTSR,
पूर्ण;
#घोषणा YDSXGR_NUM_SAVED_REGS	ARRAY_SIZE(saved_regs_index)

अटल पूर्णांक snd_ymfpci_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा snd_ymfpci *chip = card->निजी_data;
	अचिन्हित पूर्णांक i;
	
	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);
	snd_ac97_suspend(chip->ac97);
	क्रम (i = 0; i < YDSXGR_NUM_SAVED_REGS; i++)
		chip->saved_regs[i] = snd_ymfpci_पढ़ोl(chip, saved_regs_index[i]);
	chip->saved_ydsxgr_mode = snd_ymfpci_पढ़ोl(chip, YDSXGR_MODE);
	pci_पढ़ो_config_word(chip->pci, PCIR_DSXG_LEGACY,
			     &chip->saved_dsxg_legacy);
	pci_पढ़ो_config_word(chip->pci, PCIR_DSXG_ELEGACY,
			     &chip->saved_dsxg_elegacy);
	snd_ymfpci_ग_लिखोl(chip, YDSXGR_NATIVEDACOUTVOL, 0);
	snd_ymfpci_ग_लिखोl(chip, YDSXGR_BUF441OUTVOL, 0);
	snd_ymfpci_disable_dsp(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ymfpci_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci = to_pci_dev(dev);
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा snd_ymfpci *chip = card->निजी_data;
	अचिन्हित पूर्णांक i;

	snd_ymfpci_aclink_reset(pci);
	snd_ymfpci_codec_पढ़ोy(chip, 0);
	snd_ymfpci_करोwnload_image(chip);
	udelay(100);

	क्रम (i = 0; i < YDSXGR_NUM_SAVED_REGS; i++)
		snd_ymfpci_ग_लिखोl(chip, saved_regs_index[i], chip->saved_regs[i]);

	snd_ac97_resume(chip->ac97);

	pci_ग_लिखो_config_word(chip->pci, PCIR_DSXG_LEGACY,
			      chip->saved_dsxg_legacy);
	pci_ग_लिखो_config_word(chip->pci, PCIR_DSXG_ELEGACY,
			      chip->saved_dsxg_elegacy);

	/* start hw again */
	अगर (chip->start_count > 0) अणु
		spin_lock_irq(&chip->reg_lock);
		snd_ymfpci_ग_लिखोl(chip, YDSXGR_MODE, chip->saved_ydsxgr_mode);
		chip->active_bank = snd_ymfpci_पढ़ोl(chip, YDSXGR_CTRLSELECT);
		spin_unlock_irq(&chip->reg_lock);
	पूर्ण
	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण

SIMPLE_DEV_PM_OPS(snd_ymfpci_pm, snd_ymfpci_suspend, snd_ymfpci_resume);
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

पूर्णांक snd_ymfpci_create(काष्ठा snd_card *card,
		      काष्ठा pci_dev *pci,
		      अचिन्हित लघु old_legacy_ctrl,
		      काष्ठा snd_ymfpci **rchip)
अणु
	काष्ठा snd_ymfpci *chip;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =	snd_ymfpci_dev_मुक्त,
	पूर्ण;
	
	*rchip = शून्य;

	/* enable PCI device */
	अगर ((err = pci_enable_device(pci)) < 0)
		वापस err;

	chip = kzalloc(माप(*chip), GFP_KERNEL);
	अगर (chip == शून्य) अणु
		pci_disable_device(pci);
		वापस -ENOMEM;
	पूर्ण
	chip->old_legacy_ctrl = old_legacy_ctrl;
	spin_lock_init(&chip->reg_lock);
	spin_lock_init(&chip->voice_lock);
	init_रुकोqueue_head(&chip->पूर्णांकerrupt_sleep);
	atomic_set(&chip->पूर्णांकerrupt_sleep_count, 0);
	chip->card = card;
	chip->pci = pci;
	chip->irq = -1;
	chip->device_id = pci->device;
	chip->rev = pci->revision;
	chip->reg_area_phys = pci_resource_start(pci, 0);
	chip->reg_area_virt = ioremap(chip->reg_area_phys, 0x8000);
	pci_set_master(pci);
	chip->src441_used = -1;

	अगर ((chip->res_reg_area = request_mem_region(chip->reg_area_phys, 0x8000, "YMFPCI")) == शून्य) अणु
		dev_err(chip->card->dev,
			"unable to grab memory region 0x%lx-0x%lx\n",
			chip->reg_area_phys, chip->reg_area_phys + 0x8000 - 1);
		err = -EBUSY;
		जाओ मुक्त_chip;
	पूर्ण
	अगर (request_irq(pci->irq, snd_ymfpci_पूर्णांकerrupt, IRQF_SHARED,
			KBUILD_MODNAME, chip)) अणु
		dev_err(chip->card->dev, "unable to grab IRQ %d\n", pci->irq);
		err = -EBUSY;
		जाओ मुक्त_chip;
	पूर्ण
	chip->irq = pci->irq;
	card->sync_irq = chip->irq;

	snd_ymfpci_aclink_reset(pci);
	अगर (snd_ymfpci_codec_पढ़ोy(chip, 0) < 0) अणु
		err = -EIO;
		जाओ मुक्त_chip;
	पूर्ण

	err = snd_ymfpci_request_firmware(chip);
	अगर (err < 0) अणु
		dev_err(chip->card->dev, "firmware request failed: %d\n", err);
		जाओ मुक्त_chip;
	पूर्ण
	snd_ymfpci_करोwnload_image(chip);

	udelay(100); /* seems we need a delay after करोwnloading image.. */

	अगर (snd_ymfpci_meदो_स्मृति(chip) < 0) अणु
		err = -EIO;
		जाओ मुक्त_chip;
	पूर्ण

	err = snd_ymfpci_ac3_init(chip);
	अगर (err < 0)
		जाओ मुक्त_chip;

#अगर_घोषित CONFIG_PM_SLEEP
	chip->saved_regs = kदो_स्मृति_array(YDSXGR_NUM_SAVED_REGS, माप(u32),
					 GFP_KERNEL);
	अगर (chip->saved_regs == शून्य) अणु
		err = -ENOMEM;
		जाओ मुक्त_chip;
	पूर्ण
#पूर्ण_अगर

	err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops);
	अगर (err < 0)
		जाओ मुक्त_chip;

	snd_ymfpci_proc_init(card, chip);

	*rchip = chip;
	वापस 0;

मुक्त_chip:
	snd_ymfpci_मुक्त(chip);
	वापस err;
पूर्ण
