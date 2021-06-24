<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Power management क्रम audio on multअगरunction CS5535 companion device
 * Copyright (C) Jaya Kumar
 */

#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/initval.h>
#समावेश <sound/asoundef.h>
#समावेश <sound/pcm.h>
#समावेश <sound/ac97_codec.h>
#समावेश "cs5535audio.h"

अटल व्योम snd_cs5535audio_stop_hardware(काष्ठा cs5535audio *cs5535au)
अणु
	/* 
	we depend on snd_ac97_suspend to tell the
	AC97 codec to shutकरोwn. the amd spec suggests
	that the LNK_SHUTDOWN be करोne at the same समय
	that the codec घातer-करोwn is issued. instead,
	we करो it just after rather than at the same 
	समय. excluding codec specअगरic build_ops->suspend
	ac97 घातerकरोwn hits:
	0x8000 EAPD 
	0x4000 Headphone amplअगरier 
	0x0300 ADC & DAC 
	0x0400 Analog Mixer घातerकरोwn (Vref on) 
	I am not sure अगर this is the best that we can करो.
	The reमुख्यder to be investigated are:
	- analog mixer (vref off) 0x0800
	- AC-link घातerकरोwn 0x1000
	- codec पूर्णांकernal घड़ी 0x2000
	*/

	/* set LNK_SHUTDOWN to shutकरोwn AC link */
	cs_ग_लिखोl(cs5535au, ACC_CODEC_CNTL, ACC_CODEC_CNTL_LNK_SHUTDOWN);

पूर्ण

अटल पूर्णांक __maybe_unused snd_cs5535audio_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा cs5535audio *cs5535au = card->निजी_data;
	पूर्णांक i;

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);
	snd_ac97_suspend(cs5535au->ac97);
	क्रम (i = 0; i < NUM_CS5535AUDIO_DMAS; i++) अणु
		काष्ठा cs5535audio_dma *dma = &cs5535au->dmas[i];
		अगर (dma && dma->substream)
			dma->saved_prd = dma->ops->पढ़ो_prd(cs5535au);
	पूर्ण
	/* save important regs, then disable aclink in hw */
	snd_cs5535audio_stop_hardware(cs5535au);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused snd_cs5535audio_resume(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा cs5535audio *cs5535au = card->निजी_data;
	u32 पंचांगp;
	पूर्णांक समयout;
	पूर्णांक i;

	/* set LNK_WRM_RST to reset AC link */
	cs_ग_लिखोl(cs5535au, ACC_CODEC_CNTL, ACC_CODEC_CNTL_LNK_WRM_RST);

	समयout = 50;
	करो अणु
		पंचांगp = cs_पढ़ोl(cs5535au, ACC_CODEC_STATUS);
		अगर (पंचांगp & PRM_RDY_STS)
			अवरोध;
		udelay(1);
	पूर्ण जबतक (--समयout);

	अगर (!समयout)
		dev_err(cs5535au->card->dev, "Failure getting AC Link ready\n");

	/* set up rate regs, dma. actual initiation is करोne in trig */
	क्रम (i = 0; i < NUM_CS5535AUDIO_DMAS; i++) अणु
		काष्ठा cs5535audio_dma *dma = &cs5535au->dmas[i];
		अगर (dma && dma->substream) अणु
			dma->substream->ops->prepare(dma->substream);
			dma->ops->setup_prd(cs5535au, dma->saved_prd);
		पूर्ण
	पूर्ण

	/* we depend on ac97 to perक्रमm the codec घातer up */
	snd_ac97_resume(cs5535au->ac97);
	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);

	वापस 0;
पूर्ण

SIMPLE_DEV_PM_OPS(snd_cs5535audio_pm, snd_cs5535audio_suspend, snd_cs5535audio_resume);
