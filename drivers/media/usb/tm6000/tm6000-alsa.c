<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Support क्रम audio capture क्रम पंचांग5600/6000/6010
// Copyright (c) 2007-2008 Mauro Carvalho Chehab <mchehab@kernel.org>
//
// Based on cx88-alsa.c

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/usb.h>
#समावेश <linux/slab.h>

#समावेश <linux/delay.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/control.h>
#समावेश <sound/initval.h>


#समावेश "tm6000.h"
#समावेश "tm6000-regs.h"

#अघोषित dprपूर्णांकk

#घोषणा dprपूर्णांकk(level, fmt, arg...) करो अणु				   \
	अगर (debug >= level)						   \
		prपूर्णांकk(KERN_INFO "%s/1: " fmt, chip->core->name , ## arg); \
	पूर्ण जबतक (0)

/****************************************************************************
			Module global अटल vars
 ****************************************************************************/

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */

अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;

module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable tm6000x soundcard. default enabled.");

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for tm6000x capture interface(s).");


/****************************************************************************
				Module macros
 ****************************************************************************/

MODULE_DESCRIPTION("ALSA driver module for tm5600/tm6000/tm6010 based TV cards");
MODULE_AUTHOR("Mauro Carvalho Chehab");
MODULE_LICENSE("GPL v2");
अटल अचिन्हित पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "enable debug messages");

/****************************************************************************
			Module specअगरic functions
 ****************************************************************************/

/*
 * BOARD Specअगरic: Sets audio DMA
 */

अटल पूर्णांक _पंचांग6000_start_audio_dma(काष्ठा snd_पंचांग6000_card *chip)
अणु
	काष्ठा पंचांग6000_core *core = chip->core;

	dprपूर्णांकk(1, "Starting audio DMA\n");

	/* Enables audio */
	पंचांग6000_set_reg_mask(core, TM6010_REQ07_RCC_ACTIVE_IF, 0x40, 0x40);

	पंचांग6000_set_audio_bitrate(core, 48000);

	वापस 0;
पूर्ण

/*
 * BOARD Specअगरic: Resets audio DMA
 */
अटल पूर्णांक _पंचांग6000_stop_audio_dma(काष्ठा snd_पंचांग6000_card *chip)
अणु
	काष्ठा पंचांग6000_core *core = chip->core;

	dprपूर्णांकk(1, "Stopping audio DMA\n");

	/* Disables audio */
	पंचांग6000_set_reg_mask(core, TM6010_REQ07_RCC_ACTIVE_IF, 0x00, 0x40);

	वापस 0;
पूर्ण

/****************************************************************************
				ALSA PCM Interface
 ****************************************************************************/

/*
 * Digital hardware definition
 */
#घोषणा DEFAULT_FIFO_SIZE	4096

अटल स्थिर काष्ठा snd_pcm_hardware snd_पंचांग6000_digital_hw = अणु
	.info = SNDRV_PCM_INFO_BATCH |
		SNDRV_PCM_INFO_MMAP |
		SNDRV_PCM_INFO_INTERLEAVED |
		SNDRV_PCM_INFO_BLOCK_TRANSFER |
		SNDRV_PCM_INFO_MMAP_VALID,
	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,

	.rates = SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_KNOT,
	.rate_min = 48000,
	.rate_max = 48000,
	.channels_min = 2,
	.channels_max = 2,
	.period_bytes_min = 64,
	.period_bytes_max = 12544,
	.periods_min = 2,
	.periods_max = 98,
	.buffer_bytes_max = 62720 * 8,
पूर्ण;

/*
 * audio pcm capture खोलो callback
 */
अटल पूर्णांक snd_पंचांग6000_pcm_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_पंचांग6000_card *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;

	err = snd_pcm_hw_स्थिरraपूर्णांक_घात2(runसमय, 0,
					 SNDRV_PCM_HW_PARAM_PERIODS);
	अगर (err < 0)
		जाओ _error;

	chip->substream = substream;

	runसमय->hw = snd_पंचांग6000_digital_hw;
	snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय, SNDRV_PCM_HW_PARAM_PERIODS);

	वापस 0;
_error:
	dprपूर्णांकk(1, "Error opening PCM!\n");
	वापस err;
पूर्ण

/*
 * audio बंद callback
 */
अटल पूर्णांक snd_पंचांग6000_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_पंचांग6000_card *chip = snd_pcm_substream_chip(substream);
	काष्ठा पंचांग6000_core *core = chip->core;

	अगर (atomic_पढ़ो(&core->stream_started) > 0) अणु
		atomic_set(&core->stream_started, 0);
		schedule_work(&core->wq_trigger);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पंचांग6000_fillbuf(काष्ठा पंचांग6000_core *core, अक्षर *buf, पूर्णांक size)
अणु
	काष्ठा snd_पंचांग6000_card *chip = core->adev;
	काष्ठा snd_pcm_substream *substream = chip->substream;
	काष्ठा snd_pcm_runसमय *runसमय;
	पूर्णांक period_elapsed = 0;
	अचिन्हित पूर्णांक stride, buf_pos;
	पूर्णांक length;

	अगर (atomic_पढ़ो(&core->stream_started) == 0)
		वापस 0;

	अगर (!size || !substream) अणु
		dprपूर्णांकk(1, "substream was NULL\n");
		वापस -EINVAL;
	पूर्ण

	runसमय = substream->runसमय;
	अगर (!runसमय || !runसमय->dma_area) अणु
		dprपूर्णांकk(1, "runtime was NULL\n");
		वापस -EINVAL;
	पूर्ण

	buf_pos = chip->buf_pos;
	stride = runसमय->frame_bits >> 3;

	अगर (stride == 0) अणु
		dprपूर्णांकk(1, "stride is zero\n");
		वापस -EINVAL;
	पूर्ण

	length = size / stride;
	अगर (length == 0) अणु
		dprपूर्णांकk(1, "%s: length was zero\n", __func__);
		वापस -EINVAL;
	पूर्ण

	dprपूर्णांकk(1, "Copying %d bytes at %p[%d] - buf size=%d x %d\n", size,
		runसमय->dma_area, buf_pos,
		(अचिन्हित पूर्णांक)runसमय->buffer_size, stride);

	अगर (buf_pos + length >= runसमय->buffer_size) अणु
		अचिन्हित पूर्णांक cnt = runसमय->buffer_size - buf_pos;
		स_नकल(runसमय->dma_area + buf_pos * stride, buf, cnt * stride);
		स_नकल(runसमय->dma_area, buf + cnt * stride,
			length * stride - cnt * stride);
	पूर्ण अन्यथा
		स_नकल(runसमय->dma_area + buf_pos * stride, buf,
			length * stride);

	snd_pcm_stream_lock(substream);

	chip->buf_pos += length;
	अगर (chip->buf_pos >= runसमय->buffer_size)
		chip->buf_pos -= runसमय->buffer_size;

	chip->period_pos += length;
	अगर (chip->period_pos >= runसमय->period_size) अणु
		chip->period_pos -= runसमय->period_size;
		period_elapsed = 1;
	पूर्ण

	snd_pcm_stream_unlock(substream);

	अगर (period_elapsed)
		snd_pcm_period_elapsed(substream);

	वापस 0;
पूर्ण

/*
 * prepare callback
 */
अटल पूर्णांक snd_पंचांग6000_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_पंचांग6000_card *chip = snd_pcm_substream_chip(substream);

	chip->buf_pos = 0;
	chip->period_pos = 0;

	वापस 0;
पूर्ण


/*
 * trigger callback
 */
अटल व्योम audio_trigger(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा पंचांग6000_core *core = container_of(work, काष्ठा पंचांग6000_core,
						wq_trigger);
	काष्ठा snd_पंचांग6000_card *chip = core->adev;

	अगर (atomic_पढ़ो(&core->stream_started)) अणु
		dprपूर्णांकk(1, "starting capture");
		_पंचांग6000_start_audio_dma(chip);
	पूर्ण अन्यथा अणु
		dprपूर्णांकk(1, "stopping capture");
		_पंचांग6000_stop_audio_dma(chip);
	पूर्ण
पूर्ण

अटल पूर्णांक snd_पंचांग6000_card_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_पंचांग6000_card *chip = snd_pcm_substream_chip(substream);
	काष्ठा पंचांग6000_core *core = chip->core;
	पूर्णांक err = 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_START:
		atomic_set(&core->stream_started, 1);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_STOP:
		atomic_set(&core->stream_started, 0);
		अवरोध;
	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण
	schedule_work(&core->wq_trigger);

	वापस err;
पूर्ण
/*
 * poपूर्णांकer callback
 */
अटल snd_pcm_uframes_t snd_पंचांग6000_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_पंचांग6000_card *chip = snd_pcm_substream_chip(substream);

	वापस chip->buf_pos;
पूर्ण

/*
 * चालकs
 */
अटल स्थिर काष्ठा snd_pcm_ops snd_पंचांग6000_pcm_ops = अणु
	.खोलो = snd_पंचांग6000_pcm_खोलो,
	.बंद = snd_पंचांग6000_बंद,
	.prepare = snd_पंचांग6000_prepare,
	.trigger = snd_पंचांग6000_card_trigger,
	.poपूर्णांकer = snd_पंचांग6000_poपूर्णांकer,
पूर्ण;

/*
 * create a PCM device
 */

/* FIXME: Control पूर्णांकerface - How to control volume/mute? */

/****************************************************************************
			Basic Flow क्रम Sound Devices
 ****************************************************************************/

/*
 * Alsa Conकाष्ठाor - Component probe
 */
अटल पूर्णांक पंचांग6000_audio_init(काष्ठा पंचांग6000_core *dev)
अणु
	काष्ठा snd_card		*card;
	काष्ठा snd_पंचांग6000_card	*chip;
	पूर्णांक			rc;
	अटल पूर्णांक		devnr;
	अक्षर			component[14];
	काष्ठा snd_pcm		*pcm;

	अगर (!dev)
		वापस 0;

	अगर (devnr >= SNDRV_CARDS)
		वापस -ENODEV;

	अगर (!enable[devnr])
		वापस -ENOENT;

	rc = snd_card_new(&dev->udev->dev, index[devnr], "tm6000",
			  THIS_MODULE, 0, &card);
	अगर (rc < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "cannot create card instance %d\n", devnr);
		वापस rc;
	पूर्ण
	strscpy(card->driver, "tm6000-alsa", माप(card->driver));
	strscpy(card->लघुname, "TM5600/60x0", माप(card->लघुname));
	प्र_लिखो(card->दीर्घname, "TM5600/60x0 Audio at bus %d device %d",
		dev->udev->bus->busnum, dev->udev->devnum);

	प्र_लिखो(component, "USB%04x:%04x",
		le16_to_cpu(dev->udev->descriptor.idVenकरोr),
		le16_to_cpu(dev->udev->descriptor.idProduct));
	snd_component_add(card, component);

	chip = kzalloc(माप(काष्ठा snd_पंचांग6000_card), GFP_KERNEL);
	अगर (!chip) अणु
		rc = -ENOMEM;
		जाओ error;
	पूर्ण

	chip->core = dev;
	chip->card = card;
	dev->adev = chip;
	spin_lock_init(&chip->reg_lock);

	rc = snd_pcm_new(card, "TM6000 Audio", 0, 0, 1, &pcm);
	अगर (rc < 0)
		जाओ error_chip;

	pcm->info_flags = 0;
	pcm->निजी_data = chip;
	strscpy(pcm->name, "Trident TM5600/60x0", माप(pcm->name));

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_पंचांग6000_pcm_ops);
	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_VMALLOC, शून्य, 0, 0);

	INIT_WORK(&dev->wq_trigger, audio_trigger);
	rc = snd_card_रेजिस्टर(card);
	अगर (rc < 0)
		जाओ error_chip;

	dprपूर्णांकk(1, "Registered audio driver for %s\n", card->दीर्घname);

	वापस 0;

error_chip:
	kमुक्त(chip);
	dev->adev = शून्य;
error:
	snd_card_मुक्त(card);
	वापस rc;
पूर्ण

अटल पूर्णांक पंचांग6000_audio_fini(काष्ठा पंचांग6000_core *dev)
अणु
	काष्ठा snd_पंचांग6000_card *chip;

	अगर (!dev)
		वापस 0;
	chip = dev->adev;

	अगर (!chip)
		वापस 0;

	अगर (!chip->card)
		वापस 0;

	snd_card_मुक्त(chip->card);
	chip->card = शून्य;
	kमुक्त(chip);
	dev->adev = शून्य;

	वापस 0;
पूर्ण

अटल काष्ठा पंचांग6000_ops audio_ops = अणु
	.type	= TM6000_AUDIO,
	.name	= "TM6000 Audio Extension",
	.init	= पंचांग6000_audio_init,
	.fini	= पंचांग6000_audio_fini,
	.fillbuf = पंचांग6000_fillbuf,
पूर्ण;

अटल पूर्णांक __init पंचांग6000_alsa_रेजिस्टर(व्योम)
अणु
	वापस पंचांग6000_रेजिस्टर_extension(&audio_ops);
पूर्ण

अटल व्योम __निकास पंचांग6000_alsa_unरेजिस्टर(व्योम)
अणु
	पंचांग6000_unरेजिस्टर_extension(&audio_ops);
पूर्ण

module_init(पंचांग6000_alsa_रेजिस्टर);
module_निकास(पंचांग6000_alsa_unरेजिस्टर);
