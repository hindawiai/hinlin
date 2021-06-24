<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * sh_dac_audio.c - SuperH DAC audio driver क्रम ALSA
 *
 * Copyright (c) 2009 by Rafael Ignacio Zurita <rizurita@yahoo.com>
 *
 * Based on sh_dac_audio.c (Copyright (C) 2004, 2005 by Andriy Skulysh)
 */

#समावेश <linux/hrसमयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm.h>
#समावेश <sound/sh_dac_audपन.स>
#समावेश <यंत्र/घड़ी.h>
#समावेश <यंत्र/hd64461.h>
#समावेश <mach/hp6xx.h>
#समावेश <cpu/dac.h>

MODULE_AUTHOR("Rafael Ignacio Zurita <rizurita@yahoo.com>");
MODULE_DESCRIPTION("SuperH DAC audio driver");
MODULE_LICENSE("GPL");

/* Module Parameters */
अटल पूर्णांक index = SNDRV_DEFAULT_IDX1;
अटल अक्षर *id = SNDRV_DEFAULT_STR1;
module_param(index, पूर्णांक, 0444);
MODULE_PARM_DESC(index, "Index value for SuperH DAC audio.");
module_param(id, अक्षरp, 0444);
MODULE_PARM_DESC(id, "ID string for SuperH DAC audio.");

/* मुख्य काष्ठा */
काष्ठा snd_sh_dac अणु
	काष्ठा snd_card *card;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा hrसमयr hrसमयr;
	kसमय_प्रकार wakeups_per_second;

	पूर्णांक rate;
	पूर्णांक empty;
	अक्षर *data_buffer, *buffer_begin, *buffer_end;
	पूर्णांक processed; /* bytes proccesed, to compare with period_size */
	पूर्णांक buffer_size;
	काष्ठा dac_audio_pdata *pdata;
पूर्ण;


अटल व्योम dac_audio_start_समयr(काष्ठा snd_sh_dac *chip)
अणु
	hrसमयr_start(&chip->hrसमयr, chip->wakeups_per_second,
		      HRTIMER_MODE_REL);
पूर्ण

अटल व्योम dac_audio_stop_समयr(काष्ठा snd_sh_dac *chip)
अणु
	hrसमयr_cancel(&chip->hrसमयr);
पूर्ण

अटल व्योम dac_audio_reset(काष्ठा snd_sh_dac *chip)
अणु
	dac_audio_stop_समयr(chip);
	chip->buffer_begin = chip->buffer_end = chip->data_buffer;
	chip->processed = 0;
	chip->empty = 1;
पूर्ण

अटल व्योम dac_audio_set_rate(काष्ठा snd_sh_dac *chip)
अणु
	chip->wakeups_per_second = 1000000000 / chip->rate;
पूर्ण


/* PCM INTERFACE */

अटल स्थिर काष्ठा snd_pcm_hardware snd_sh_dac_pcm_hw = अणु
	.info			= (SNDRV_PCM_INFO_MMAP |
					SNDRV_PCM_INFO_MMAP_VALID |
					SNDRV_PCM_INFO_INTERLEAVED |
					SNDRV_PCM_INFO_HALF_DUPLEX),
	.क्रमmats		= SNDRV_PCM_FMTBIT_U8,
	.rates			= SNDRV_PCM_RATE_8000,
	.rate_min		= 8000,
	.rate_max		= 8000,
	.channels_min		= 1,
	.channels_max		= 1,
	.buffer_bytes_max	= (48*1024),
	.period_bytes_min	= 1,
	.period_bytes_max	= (48*1024),
	.periods_min		= 1,
	.periods_max		= 1024,
पूर्ण;

अटल पूर्णांक snd_sh_dac_pcm_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_sh_dac *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	runसमय->hw = snd_sh_dac_pcm_hw;

	chip->substream = substream;
	chip->buffer_begin = chip->buffer_end = chip->data_buffer;
	chip->processed = 0;
	chip->empty = 1;

	chip->pdata->start(chip->pdata);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_sh_dac_pcm_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_sh_dac *chip = snd_pcm_substream_chip(substream);

	chip->substream = शून्य;

	dac_audio_stop_समयr(chip);
	chip->pdata->stop(chip->pdata);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_sh_dac_pcm_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_sh_dac *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = chip->substream->runसमय;

	chip->buffer_size = runसमय->buffer_size;
	स_रखो(chip->data_buffer, 0, chip->pdata->buffer_size);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_sh_dac_pcm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_sh_dac *chip = snd_pcm_substream_chip(substream);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		dac_audio_start_समयr(chip);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		chip->buffer_begin = chip->buffer_end = chip->data_buffer;
		chip->processed = 0;
		chip->empty = 1;
		dac_audio_stop_समयr(chip);
		अवरोध;
	शेष:
		 वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_sh_dac_pcm_copy(काष्ठा snd_pcm_substream *substream,
			       पूर्णांक channel, अचिन्हित दीर्घ pos,
			       व्योम __user *src, अचिन्हित दीर्घ count)
अणु
	/* channel is not used (पूर्णांकerleaved data) */
	काष्ठा snd_sh_dac *chip = snd_pcm_substream_chip(substream);

	अगर (copy_from_user_toio(chip->data_buffer + pos, src, count))
		वापस -EFAULT;
	chip->buffer_end = chip->data_buffer + pos + count;

	अगर (chip->empty) अणु
		chip->empty = 0;
		dac_audio_start_समयr(chip);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_sh_dac_pcm_copy_kernel(काष्ठा snd_pcm_substream *substream,
				      पूर्णांक channel, अचिन्हित दीर्घ pos,
				      व्योम *src, अचिन्हित दीर्घ count)
अणु
	/* channel is not used (पूर्णांकerleaved data) */
	काष्ठा snd_sh_dac *chip = snd_pcm_substream_chip(substream);

	स_नकल_toio(chip->data_buffer + pos, src, count);
	chip->buffer_end = chip->data_buffer + pos + count;

	अगर (chip->empty) अणु
		chip->empty = 0;
		dac_audio_start_समयr(chip);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_sh_dac_pcm_silence(काष्ठा snd_pcm_substream *substream,
				  पूर्णांक channel, अचिन्हित दीर्घ pos,
				  अचिन्हित दीर्घ count)
अणु
	/* channel is not used (पूर्णांकerleaved data) */
	काष्ठा snd_sh_dac *chip = snd_pcm_substream_chip(substream);

	स_रखो_io(chip->data_buffer + pos, 0, count);
	chip->buffer_end = chip->data_buffer + pos + count;

	अगर (chip->empty) अणु
		chip->empty = 0;
		dac_audio_start_समयr(chip);
	पूर्ण

	वापस 0;
पूर्ण

अटल
snd_pcm_uframes_t snd_sh_dac_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_sh_dac *chip = snd_pcm_substream_chip(substream);
	पूर्णांक poपूर्णांकer = chip->buffer_begin - chip->data_buffer;

	वापस poपूर्णांकer;
पूर्ण

/* pcm ops */
अटल स्थिर काष्ठा snd_pcm_ops snd_sh_dac_pcm_ops = अणु
	.खोलो		= snd_sh_dac_pcm_खोलो,
	.बंद		= snd_sh_dac_pcm_बंद,
	.prepare	= snd_sh_dac_pcm_prepare,
	.trigger	= snd_sh_dac_pcm_trigger,
	.poपूर्णांकer	= snd_sh_dac_pcm_poपूर्णांकer,
	.copy_user	= snd_sh_dac_pcm_copy,
	.copy_kernel	= snd_sh_dac_pcm_copy_kernel,
	.fill_silence	= snd_sh_dac_pcm_silence,
	.mmap		= snd_pcm_lib_mmap_iomem,
पूर्ण;

अटल पूर्णांक snd_sh_dac_pcm(काष्ठा snd_sh_dac *chip, पूर्णांक device)
अणु
	पूर्णांक err;
	काष्ठा snd_pcm *pcm;

	/* device should be always 0 क्रम us */
	err = snd_pcm_new(chip->card, "SH_DAC PCM", device, 1, 0, &pcm);
	अगर (err < 0)
		वापस err;

	pcm->निजी_data = chip;
	म_नकल(pcm->name, "SH_DAC PCM");
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_sh_dac_pcm_ops);

	/* buffer size=48K */
	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_CONTINUOUS,
				       शून्य, 48 * 1024, 48 * 1024);

	वापस 0;
पूर्ण
/* END OF PCM INTERFACE */


/* driver .हटाओ  --  deकाष्ठाor */
अटल पूर्णांक snd_sh_dac_हटाओ(काष्ठा platक्रमm_device *devptr)
अणु
	snd_card_मुक्त(platक्रमm_get_drvdata(devptr));
	वापस 0;
पूर्ण

/* मुक्त -- it has been defined by create */
अटल पूर्णांक snd_sh_dac_मुक्त(काष्ठा snd_sh_dac *chip)
अणु
	/* release the data */
	kमुक्त(chip->data_buffer);
	kमुक्त(chip);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_sh_dac_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_sh_dac *chip = device->device_data;

	वापस snd_sh_dac_मुक्त(chip);
पूर्ण

अटल क्रमागत hrसमयr_restart sh_dac_audio_समयr(काष्ठा hrसमयr *handle)
अणु
	काष्ठा snd_sh_dac *chip = container_of(handle, काष्ठा snd_sh_dac,
					       hrसमयr);
	काष्ठा snd_pcm_runसमय *runसमय = chip->substream->runसमय;
	sमाप_प्रकार b_ps = frames_to_bytes(runसमय, runसमय->period_size);

	अगर (!chip->empty) अणु
		sh_dac_output(*chip->buffer_begin, chip->pdata->channel);
		chip->buffer_begin++;

		chip->processed++;
		अगर (chip->processed >= b_ps) अणु
			chip->processed -= b_ps;
			snd_pcm_period_elapsed(chip->substream);
		पूर्ण

		अगर (chip->buffer_begin == (chip->data_buffer +
					   chip->buffer_size - 1))
			chip->buffer_begin = chip->data_buffer;

		अगर (chip->buffer_begin == chip->buffer_end)
			chip->empty = 1;

	पूर्ण

	अगर (!chip->empty)
		hrसमयr_start(&chip->hrसमयr, chip->wakeups_per_second,
			      HRTIMER_MODE_REL);

	वापस HRTIMER_NORESTART;
पूर्ण

/* create  --  chip-specअगरic स्थिरructor क्रम the cards components */
अटल पूर्णांक snd_sh_dac_create(काष्ठा snd_card *card,
			     काष्ठा platक्रमm_device *devptr,
			     काष्ठा snd_sh_dac **rchip)
अणु
	काष्ठा snd_sh_dac *chip;
	पूर्णांक err;

	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		   .dev_मुक्त = snd_sh_dac_dev_मुक्त,
	पूर्ण;

	*rchip = शून्य;

	chip = kzalloc(माप(*chip), GFP_KERNEL);
	अगर (chip == शून्य)
		वापस -ENOMEM;

	chip->card = card;

	hrसमयr_init(&chip->hrसमयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	chip->hrसमयr.function = sh_dac_audio_समयr;

	dac_audio_reset(chip);
	chip->rate = 8000;
	dac_audio_set_rate(chip);

	chip->pdata = devptr->dev.platक्रमm_data;

	chip->data_buffer = kदो_स्मृति(chip->pdata->buffer_size, GFP_KERNEL);
	अगर (chip->data_buffer == शून्य) अणु
		kमुक्त(chip);
		वापस -ENOMEM;
	पूर्ण

	err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops);
	अगर (err < 0) अणु
		snd_sh_dac_मुक्त(chip);
		वापस err;
	पूर्ण

	*rchip = chip;

	वापस 0;
पूर्ण

/* driver .probe  --  स्थिरructor */
अटल पूर्णांक snd_sh_dac_probe(काष्ठा platक्रमm_device *devptr)
अणु
	काष्ठा snd_sh_dac *chip;
	काष्ठा snd_card *card;
	पूर्णांक err;

	err = snd_card_new(&devptr->dev, index, id, THIS_MODULE, 0, &card);
	अगर (err < 0) अणु
			snd_prपूर्णांकk(KERN_ERR "cannot allocate the card\n");
			वापस err;
	पूर्ण

	err = snd_sh_dac_create(card, devptr, &chip);
	अगर (err < 0)
		जाओ probe_error;

	err = snd_sh_dac_pcm(chip, 0);
	अगर (err < 0)
		जाओ probe_error;

	म_नकल(card->driver, "snd_sh_dac");
	म_नकल(card->लघुname, "SuperH DAC audio driver");
	prपूर्णांकk(KERN_INFO "%s %s", card->दीर्घname, card->लघुname);

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0)
		जाओ probe_error;

	snd_prपूर्णांकk(KERN_INFO "ALSA driver for SuperH DAC audio");

	platक्रमm_set_drvdata(devptr, card);
	वापस 0;

probe_error:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

/*
 * "driver" definition
 */
अटल काष्ठा platक्रमm_driver sh_dac_driver = अणु
	.probe	= snd_sh_dac_probe,
	.हटाओ = snd_sh_dac_हटाओ,
	.driver = अणु
		.name = "dac_audio",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sh_dac_driver);
