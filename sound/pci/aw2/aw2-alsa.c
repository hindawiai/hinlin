<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*****************************************************************************
 *
 * Copyright (C) 2008 Cedric Bregardis <cedric.bregardis@मुक्त.fr> and
 * Jean-Christian Hassler <jhassler@मुक्त.fr>
 *
 * This file is part of the Audiowerk2 ALSA driver
 *
 *****************************************************************************/
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/control.h>

#समावेश "saa7146.h"
#समावेश "aw2-saa7146.h"

MODULE_AUTHOR("Cedric Bregardis <cedric.bregardis@free.fr>, "
	      "Jean-Christian Hassler <jhassler@free.fr>");
MODULE_DESCRIPTION("Emagic Audiowerk 2 sound driver");
MODULE_LICENSE("GPL");

/*********************************
 * DEFINES
 ********************************/
#घोषणा CTL_ROUTE_ANALOG 0
#घोषणा CTL_ROUTE_DIGITAL 1

/*********************************
 * TYPEDEFS
 ********************************/
  /* hardware definition */
अटल स्थिर काष्ठा snd_pcm_hardware snd_aw2_playback_hw = अणु
	.info = (SNDRV_PCM_INFO_MMAP |
		 SNDRV_PCM_INFO_INTERLEAVED |
		 SNDRV_PCM_INFO_BLOCK_TRANSFER | SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	.rates = SNDRV_PCM_RATE_44100,
	.rate_min = 44100,
	.rate_max = 44100,
	.channels_min = 2,
	.channels_max = 4,
	.buffer_bytes_max = 32768,
	.period_bytes_min = 4096,
	.period_bytes_max = 32768,
	.periods_min = 1,
	.periods_max = 1024,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_aw2_capture_hw = अणु
	.info = (SNDRV_PCM_INFO_MMAP |
		 SNDRV_PCM_INFO_INTERLEAVED |
		 SNDRV_PCM_INFO_BLOCK_TRANSFER | SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	.rates = SNDRV_PCM_RATE_44100,
	.rate_min = 44100,
	.rate_max = 44100,
	.channels_min = 2,
	.channels_max = 2,
	.buffer_bytes_max = 32768,
	.period_bytes_min = 4096,
	.period_bytes_max = 32768,
	.periods_min = 1,
	.periods_max = 1024,
पूर्ण;

काष्ठा aw2_pcm_device अणु
	काष्ठा snd_pcm *pcm;
	अचिन्हित पूर्णांक stream_number;
	काष्ठा aw2 *chip;
पूर्ण;

काष्ठा aw2 अणु
	काष्ठा snd_aw2_saa7146 saa7146;

	काष्ठा pci_dev *pci;
	पूर्णांक irq;
	spinlock_t reg_lock;
	काष्ठा mutex mtx;

	अचिन्हित दीर्घ iobase_phys;
	व्योम __iomem *iobase_virt;

	काष्ठा snd_card *card;

	काष्ठा aw2_pcm_device device_playback[NB_STREAM_PLAYBACK];
	काष्ठा aw2_pcm_device device_capture[NB_STREAM_CAPTURE];
पूर्ण;

/*********************************
 * FUNCTION DECLARATIONS
 ********************************/
अटल पूर्णांक snd_aw2_dev_मुक्त(काष्ठा snd_device *device);
अटल पूर्णांक snd_aw2_create(काष्ठा snd_card *card,
			  काष्ठा pci_dev *pci, काष्ठा aw2 **rchip);
अटल पूर्णांक snd_aw2_probe(काष्ठा pci_dev *pci,
			 स्थिर काष्ठा pci_device_id *pci_id);
अटल व्योम snd_aw2_हटाओ(काष्ठा pci_dev *pci);
अटल पूर्णांक snd_aw2_pcm_playback_खोलो(काष्ठा snd_pcm_substream *substream);
अटल पूर्णांक snd_aw2_pcm_playback_बंद(काष्ठा snd_pcm_substream *substream);
अटल पूर्णांक snd_aw2_pcm_capture_खोलो(काष्ठा snd_pcm_substream *substream);
अटल पूर्णांक snd_aw2_pcm_capture_बंद(काष्ठा snd_pcm_substream *substream);
अटल पूर्णांक snd_aw2_pcm_prepare_playback(काष्ठा snd_pcm_substream *substream);
अटल पूर्णांक snd_aw2_pcm_prepare_capture(काष्ठा snd_pcm_substream *substream);
अटल पूर्णांक snd_aw2_pcm_trigger_playback(काष्ठा snd_pcm_substream *substream,
					पूर्णांक cmd);
अटल पूर्णांक snd_aw2_pcm_trigger_capture(काष्ठा snd_pcm_substream *substream,
				       पूर्णांक cmd);
अटल snd_pcm_uframes_t snd_aw2_pcm_poपूर्णांकer_playback(काष्ठा snd_pcm_substream
						      *substream);
अटल snd_pcm_uframes_t snd_aw2_pcm_poपूर्णांकer_capture(काष्ठा snd_pcm_substream
						     *substream);
अटल पूर्णांक snd_aw2_new_pcm(काष्ठा aw2 *chip);

अटल पूर्णांक snd_aw2_control_चयन_capture_info(काष्ठा snd_kcontrol *kcontrol,
					       काष्ठा snd_ctl_elem_info *uinfo);
अटल पूर्णांक snd_aw2_control_चयन_capture_get(काष्ठा snd_kcontrol *kcontrol,
					      काष्ठा snd_ctl_elem_value
					      *ucontrol);
अटल पूर्णांक snd_aw2_control_चयन_capture_put(काष्ठा snd_kcontrol *kcontrol,
					      काष्ठा snd_ctl_elem_value
					      *ucontrol);

/*********************************
 * VARIABLES
 ********************************/
अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for Audiowerk2 soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for the Audiowerk2 soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable Audiowerk2 soundcard.");

अटल स्थिर काष्ठा pci_device_id snd_aw2_ids[] = अणु
	अणुPCI_VENDOR_ID_PHILIPS, PCI_DEVICE_ID_PHILIPS_SAA7146, 0, 0,
	 0, 0, 0पूर्ण,
	अणु0पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, snd_aw2_ids);

/* pci_driver definition */
अटल काष्ठा pci_driver aw2_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_aw2_ids,
	.probe = snd_aw2_probe,
	.हटाओ = snd_aw2_हटाओ,
पूर्ण;

module_pci_driver(aw2_driver);

/* चालकs क्रम playback PCM alsa पूर्णांकerface */
अटल स्थिर काष्ठा snd_pcm_ops snd_aw2_playback_ops = अणु
	.खोलो = snd_aw2_pcm_playback_खोलो,
	.बंद = snd_aw2_pcm_playback_बंद,
	.prepare = snd_aw2_pcm_prepare_playback,
	.trigger = snd_aw2_pcm_trigger_playback,
	.poपूर्णांकer = snd_aw2_pcm_poपूर्णांकer_playback,
पूर्ण;

/* चालकs क्रम capture PCM alsa पूर्णांकerface */
अटल स्थिर काष्ठा snd_pcm_ops snd_aw2_capture_ops = अणु
	.खोलो = snd_aw2_pcm_capture_खोलो,
	.बंद = snd_aw2_pcm_capture_बंद,
	.prepare = snd_aw2_pcm_prepare_capture,
	.trigger = snd_aw2_pcm_trigger_capture,
	.poपूर्णांकer = snd_aw2_pcm_poपूर्णांकer_capture,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new aw2_control = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "PCM Capture Route",
	.index = 0,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.निजी_value = 0xffff,
	.info = snd_aw2_control_चयन_capture_info,
	.get = snd_aw2_control_चयन_capture_get,
	.put = snd_aw2_control_चयन_capture_put
पूर्ण;

/*********************************
 * FUNCTION IMPLEMENTATIONS
 ********************************/

/* component-deकाष्ठाor */
अटल पूर्णांक snd_aw2_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा aw2 *chip = device->device_data;

	/* Free hardware */
	snd_aw2_saa7146_मुक्त(&chip->saa7146);

	/* release the irq */
	अगर (chip->irq >= 0)
		मुक्त_irq(chip->irq, (व्योम *)chip);
	/* release the i/o ports & memory */
	iounmap(chip->iobase_virt);
	pci_release_regions(chip->pci);
	/* disable the PCI entry */
	pci_disable_device(chip->pci);
	/* release the data */
	kमुक्त(chip);

	वापस 0;
पूर्ण

/* chip-specअगरic स्थिरructor */
अटल पूर्णांक snd_aw2_create(काष्ठा snd_card *card,
			  काष्ठा pci_dev *pci, काष्ठा aw2 **rchip)
अणु
	काष्ठा aw2 *chip;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त = snd_aw2_dev_मुक्त,
	पूर्ण;

	*rchip = शून्य;

	/* initialize the PCI entry */
	err = pci_enable_device(pci);
	अगर (err < 0)
		वापस err;
	pci_set_master(pci);

	/* check PCI availability (32bit DMA) */
	अगर (dma_set_mask_and_coherent(&pci->dev, DMA_BIT_MASK(32))) अणु
		dev_err(card->dev, "Impossible to set 32bit mask DMA\n");
		pci_disable_device(pci);
		वापस -ENXIO;
	पूर्ण
	chip = kzalloc(माप(*chip), GFP_KERNEL);
	अगर (chip == शून्य) अणु
		pci_disable_device(pci);
		वापस -ENOMEM;
	पूर्ण

	/* initialize the stuff */
	chip->card = card;
	chip->pci = pci;
	chip->irq = -1;

	/* (1) PCI resource allocation */
	err = pci_request_regions(pci, "Audiowerk2");
	अगर (err < 0) अणु
		pci_disable_device(pci);
		kमुक्त(chip);
		वापस err;
	पूर्ण
	chip->iobase_phys = pci_resource_start(pci, 0);
	chip->iobase_virt =
		ioremap(chip->iobase_phys,
				pci_resource_len(pci, 0));

	अगर (chip->iobase_virt == शून्य) अणु
		dev_err(card->dev, "unable to remap memory region");
		pci_release_regions(pci);
		pci_disable_device(pci);
		kमुक्त(chip);
		वापस -ENOMEM;
	पूर्ण

	/* (2) initialization of the chip hardware */
	snd_aw2_saa7146_setup(&chip->saa7146, chip->iobase_virt);

	अगर (request_irq(pci->irq, snd_aw2_saa7146_पूर्णांकerrupt,
			IRQF_SHARED, KBUILD_MODNAME, chip)) अणु
		dev_err(card->dev, "Cannot grab irq %d\n", pci->irq);

		iounmap(chip->iobase_virt);
		pci_release_regions(chip->pci);
		pci_disable_device(chip->pci);
		kमुक्त(chip);
		वापस -EBUSY;
	पूर्ण
	chip->irq = pci->irq;
	card->sync_irq = chip->irq;

	err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops);
	अगर (err < 0) अणु
		मुक्त_irq(chip->irq, (व्योम *)chip);
		iounmap(chip->iobase_virt);
		pci_release_regions(chip->pci);
		pci_disable_device(chip->pci);
		kमुक्त(chip);
		वापस err;
	पूर्ण

	*rchip = chip;

	dev_info(card->dev,
		 "Audiowerk 2 sound card (saa7146 chipset) detected and managed\n");
	वापस 0;
पूर्ण

/* स्थिरructor */
अटल पूर्णांक snd_aw2_probe(काष्ठा pci_dev *pci,
			 स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_card *card;
	काष्ठा aw2 *chip;
	पूर्णांक err;

	/* (1) Continue अगर device is not enabled, अन्यथा inc dev */
	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;
	अगर (!enable[dev]) अणु
		dev++;
		वापस -ENOENT;
	पूर्ण

	/* (2) Create card instance */
	err = snd_card_new(&pci->dev, index[dev], id[dev], THIS_MODULE,
			   0, &card);
	अगर (err < 0)
		वापस err;

	/* (3) Create मुख्य component */
	err = snd_aw2_create(card, pci, &chip);
	अगर (err < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	/* initialize mutex */
	mutex_init(&chip->mtx);
	/* init spinlock */
	spin_lock_init(&chip->reg_lock);
	/* (4) Define driver ID and name string */
	म_नकल(card->driver, "aw2");
	म_नकल(card->लघुname, "Audiowerk2");

	प्र_लिखो(card->दीर्घname, "%s with SAA7146 irq %i",
		card->लघुname, chip->irq);

	/* (5) Create other components */
	snd_aw2_new_pcm(chip);

	/* (6) Register card instance */
	err = snd_card_रेजिस्टर(card);
	अगर (err < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	/* (7) Set PCI driver data */
	pci_set_drvdata(pci, card);

	dev++;
	वापस 0;
पूर्ण

/* deकाष्ठाor */
अटल व्योम snd_aw2_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण

/* खोलो callback */
अटल पूर्णांक snd_aw2_pcm_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	dev_dbg(substream->pcm->card->dev, "Playback_open\n");
	runसमय->hw = snd_aw2_playback_hw;
	वापस 0;
पूर्ण

/* बंद callback */
अटल पूर्णांक snd_aw2_pcm_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	वापस 0;

पूर्ण

अटल पूर्णांक snd_aw2_pcm_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	dev_dbg(substream->pcm->card->dev, "Capture_open\n");
	runसमय->hw = snd_aw2_capture_hw;
	वापस 0;
पूर्ण

/* बंद callback */
अटल पूर्णांक snd_aw2_pcm_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	/* TODO: something to करो ? */
	वापस 0;
पूर्ण

/* prepare callback क्रम playback */
अटल पूर्णांक snd_aw2_pcm_prepare_playback(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा aw2_pcm_device *pcm_device = snd_pcm_substream_chip(substream);
	काष्ठा aw2 *chip = pcm_device->chip;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित दीर्घ period_size, buffer_size;

	mutex_lock(&chip->mtx);

	period_size = snd_pcm_lib_period_bytes(substream);
	buffer_size = snd_pcm_lib_buffer_bytes(substream);

	snd_aw2_saa7146_pcm_init_playback(&chip->saa7146,
					  pcm_device->stream_number,
					  runसमय->dma_addr, period_size,
					  buffer_size);

	/* Define Interrupt callback */
	snd_aw2_saa7146_define_it_playback_callback(pcm_device->stream_number,
						    (snd_aw2_saa7146_it_cb)
						    snd_pcm_period_elapsed,
						    (व्योम *)substream);

	mutex_unlock(&chip->mtx);

	वापस 0;
पूर्ण

/* prepare callback क्रम capture */
अटल पूर्णांक snd_aw2_pcm_prepare_capture(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा aw2_pcm_device *pcm_device = snd_pcm_substream_chip(substream);
	काष्ठा aw2 *chip = pcm_device->chip;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित दीर्घ period_size, buffer_size;

	mutex_lock(&chip->mtx);

	period_size = snd_pcm_lib_period_bytes(substream);
	buffer_size = snd_pcm_lib_buffer_bytes(substream);

	snd_aw2_saa7146_pcm_init_capture(&chip->saa7146,
					 pcm_device->stream_number,
					 runसमय->dma_addr, period_size,
					 buffer_size);

	/* Define Interrupt callback */
	snd_aw2_saa7146_define_it_capture_callback(pcm_device->stream_number,
						   (snd_aw2_saa7146_it_cb)
						   snd_pcm_period_elapsed,
						   (व्योम *)substream);

	mutex_unlock(&chip->mtx);

	वापस 0;
पूर्ण

/* playback trigger callback */
अटल पूर्णांक snd_aw2_pcm_trigger_playback(काष्ठा snd_pcm_substream *substream,
					पूर्णांक cmd)
अणु
	पूर्णांक status = 0;
	काष्ठा aw2_pcm_device *pcm_device = snd_pcm_substream_chip(substream);
	काष्ठा aw2 *chip = pcm_device->chip;
	spin_lock(&chip->reg_lock);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		snd_aw2_saa7146_pcm_trigger_start_playback(&chip->saa7146,
							   pcm_device->
							   stream_number);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		snd_aw2_saa7146_pcm_trigger_stop_playback(&chip->saa7146,
							  pcm_device->
							  stream_number);
		अवरोध;
	शेष:
		status = -EINVAL;
	पूर्ण
	spin_unlock(&chip->reg_lock);
	वापस status;
पूर्ण

/* capture trigger callback */
अटल पूर्णांक snd_aw2_pcm_trigger_capture(काष्ठा snd_pcm_substream *substream,
				       पूर्णांक cmd)
अणु
	पूर्णांक status = 0;
	काष्ठा aw2_pcm_device *pcm_device = snd_pcm_substream_chip(substream);
	काष्ठा aw2 *chip = pcm_device->chip;
	spin_lock(&chip->reg_lock);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		snd_aw2_saa7146_pcm_trigger_start_capture(&chip->saa7146,
							  pcm_device->
							  stream_number);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		snd_aw2_saa7146_pcm_trigger_stop_capture(&chip->saa7146,
							 pcm_device->
							 stream_number);
		अवरोध;
	शेष:
		status = -EINVAL;
	पूर्ण
	spin_unlock(&chip->reg_lock);
	वापस status;
पूर्ण

/* playback poपूर्णांकer callback */
अटल snd_pcm_uframes_t snd_aw2_pcm_poपूर्णांकer_playback(काष्ठा snd_pcm_substream
						      *substream)
अणु
	काष्ठा aw2_pcm_device *pcm_device = snd_pcm_substream_chip(substream);
	काष्ठा aw2 *chip = pcm_device->chip;
	अचिन्हित पूर्णांक current_ptr;

	/* get the current hardware poपूर्णांकer */
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	current_ptr =
		snd_aw2_saa7146_get_hw_ptr_playback(&chip->saa7146,
						    pcm_device->stream_number,
						    runसमय->dma_area,
						    runसमय->buffer_size);

	वापस bytes_to_frames(substream->runसमय, current_ptr);
पूर्ण

/* capture poपूर्णांकer callback */
अटल snd_pcm_uframes_t snd_aw2_pcm_poपूर्णांकer_capture(काष्ठा snd_pcm_substream
						     *substream)
अणु
	काष्ठा aw2_pcm_device *pcm_device = snd_pcm_substream_chip(substream);
	काष्ठा aw2 *chip = pcm_device->chip;
	अचिन्हित पूर्णांक current_ptr;

	/* get the current hardware poपूर्णांकer */
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	current_ptr =
		snd_aw2_saa7146_get_hw_ptr_capture(&chip->saa7146,
						   pcm_device->stream_number,
						   runसमय->dma_area,
						   runसमय->buffer_size);

	वापस bytes_to_frames(substream->runसमय, current_ptr);
पूर्ण

/* create a pcm device */
अटल पूर्णांक snd_aw2_new_pcm(काष्ठा aw2 *chip)
अणु
	काष्ठा snd_pcm *pcm_playback_ana;
	काष्ठा snd_pcm *pcm_playback_num;
	काष्ठा snd_pcm *pcm_capture;
	काष्ठा aw2_pcm_device *pcm_device;
	पूर्णांक err = 0;

	/* Create new Alsa PCM device */

	err = snd_pcm_new(chip->card, "Audiowerk2 analog playback", 0, 1, 0,
			  &pcm_playback_ana);
	अगर (err < 0) अणु
		dev_err(chip->card->dev, "snd_pcm_new error (0x%X)\n", err);
		वापस err;
	पूर्ण

	/* Creation ok */
	pcm_device = &chip->device_playback[NUM_STREAM_PLAYBACK_ANA];

	/* Set PCM device name */
	म_नकल(pcm_playback_ana->name, "Analog playback");
	/* Associate निजी data to PCM device */
	pcm_playback_ana->निजी_data = pcm_device;
	/* set चालकs of PCM device */
	snd_pcm_set_ops(pcm_playback_ana, SNDRV_PCM_STREAM_PLAYBACK,
			&snd_aw2_playback_ops);
	/* store PCM device */
	pcm_device->pcm = pcm_playback_ana;
	/* give base chip poपूर्णांकer to our पूर्णांकernal pcm device
	   काष्ठाure */
	pcm_device->chip = chip;
	/* Give stream number to PCM device */
	pcm_device->stream_number = NUM_STREAM_PLAYBACK_ANA;

	/* pre-allocation of buffers */
	/* Pपुनः_स्मृतिate continuous pages. */
	snd_pcm_set_managed_buffer_all(pcm_playback_ana,
				       SNDRV_DMA_TYPE_DEV,
				       &chip->pci->dev,
				       64 * 1024, 64 * 1024);

	err = snd_pcm_new(chip->card, "Audiowerk2 digital playback", 1, 1, 0,
			  &pcm_playback_num);

	अगर (err < 0) अणु
		dev_err(chip->card->dev, "snd_pcm_new error (0x%X)\n", err);
		वापस err;
	पूर्ण
	/* Creation ok */
	pcm_device = &chip->device_playback[NUM_STREAM_PLAYBACK_DIG];

	/* Set PCM device name */
	म_नकल(pcm_playback_num->name, "Digital playback");
	/* Associate निजी data to PCM device */
	pcm_playback_num->निजी_data = pcm_device;
	/* set चालकs of PCM device */
	snd_pcm_set_ops(pcm_playback_num, SNDRV_PCM_STREAM_PLAYBACK,
			&snd_aw2_playback_ops);
	/* store PCM device */
	pcm_device->pcm = pcm_playback_num;
	/* give base chip poपूर्णांकer to our पूर्णांकernal pcm device
	   काष्ठाure */
	pcm_device->chip = chip;
	/* Give stream number to PCM device */
	pcm_device->stream_number = NUM_STREAM_PLAYBACK_DIG;

	/* pre-allocation of buffers */
	/* Pपुनः_स्मृतिate continuous pages. */
	snd_pcm_set_managed_buffer_all(pcm_playback_num,
				       SNDRV_DMA_TYPE_DEV,
				       &chip->pci->dev,
				       64 * 1024, 64 * 1024);

	err = snd_pcm_new(chip->card, "Audiowerk2 capture", 2, 0, 1,
			  &pcm_capture);

	अगर (err < 0) अणु
		dev_err(chip->card->dev, "snd_pcm_new error (0x%X)\n", err);
		वापस err;
	पूर्ण

	/* Creation ok */
	pcm_device = &chip->device_capture[NUM_STREAM_CAPTURE_ANA];

	/* Set PCM device name */
	म_नकल(pcm_capture->name, "Capture");
	/* Associate निजी data to PCM device */
	pcm_capture->निजी_data = pcm_device;
	/* set चालकs of PCM device */
	snd_pcm_set_ops(pcm_capture, SNDRV_PCM_STREAM_CAPTURE,
			&snd_aw2_capture_ops);
	/* store PCM device */
	pcm_device->pcm = pcm_capture;
	/* give base chip poपूर्णांकer to our पूर्णांकernal pcm device
	   काष्ठाure */
	pcm_device->chip = chip;
	/* Give stream number to PCM device */
	pcm_device->stream_number = NUM_STREAM_CAPTURE_ANA;

	/* pre-allocation of buffers */
	/* Pपुनः_स्मृतिate continuous pages. */
	snd_pcm_set_managed_buffer_all(pcm_capture,
				       SNDRV_DMA_TYPE_DEV,
				       &chip->pci->dev,
				       64 * 1024, 64 * 1024);

	/* Create control */
	err = snd_ctl_add(chip->card, snd_ctl_new1(&aw2_control, chip));
	अगर (err < 0) अणु
		dev_err(chip->card->dev, "snd_ctl_add error (0x%X)\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_aw2_control_चयन_capture_info(काष्ठा snd_kcontrol *kcontrol,
					       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[2] = अणु
		"Analog", "Digital"
	पूर्ण;
	वापस snd_ctl_क्रमागत_info(uinfo, 1, 2, texts);
पूर्ण

अटल पूर्णांक snd_aw2_control_चयन_capture_get(काष्ठा snd_kcontrol *kcontrol,
					      काष्ठा snd_ctl_elem_value
					      *ucontrol)
अणु
	काष्ठा aw2 *chip = snd_kcontrol_chip(kcontrol);
	अगर (snd_aw2_saa7146_is_using_digital_input(&chip->saa7146))
		ucontrol->value.क्रमागतerated.item[0] = CTL_ROUTE_DIGITAL;
	अन्यथा
		ucontrol->value.क्रमागतerated.item[0] = CTL_ROUTE_ANALOG;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_aw2_control_चयन_capture_put(काष्ठा snd_kcontrol *kcontrol,
					      काष्ठा snd_ctl_elem_value
					      *ucontrol)
अणु
	काष्ठा aw2 *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक changed = 0;
	पूर्णांक is_disgital =
	    snd_aw2_saa7146_is_using_digital_input(&chip->saa7146);

	अगर (((ucontrol->value.पूर्णांकeger.value[0] == CTL_ROUTE_DIGITAL)
	     && !is_disgital)
	    || ((ucontrol->value.पूर्णांकeger.value[0] == CTL_ROUTE_ANALOG)
		&& is_disgital)) अणु
		snd_aw2_saa7146_use_digital_input(&chip->saa7146, !is_disgital);
		changed = 1;
	पूर्ण
	वापस changed;
पूर्ण
