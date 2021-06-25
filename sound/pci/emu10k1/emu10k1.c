<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  The driver क्रम the EMU10K1 (SB Live!) based soundcards
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *
 *  Copyright (c) by James Courtier-Dutton <James@superbug.demon.co.uk>
 *      Added support क्रम Audigy 2 Value.
 */

#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/समय.स>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/emu10k1.h>
#समावेश <sound/initval.h>

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("EMU10K1");
MODULE_LICENSE("GPL");

#अगर IS_ENABLED(CONFIG_SND_SEQUENCER)
#घोषणा ENABLE_SYNTH
#समावेश <sound/emu10k1_synth.h>
#पूर्ण_अगर

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;	/* Enable this card */
अटल पूर्णांक extin[SNDRV_CARDS];
अटल पूर्णांक extout[SNDRV_CARDS];
अटल पूर्णांक seq_ports[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 4पूर्ण;
अटल पूर्णांक max_synth_voices[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 64पूर्ण;
अटल पूर्णांक max_buffer_size[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 128पूर्ण;
अटल bool enable_ir[SNDRV_CARDS];
अटल uपूर्णांक subप्रणाली[SNDRV_CARDS]; /* Force card subप्रणाली model */
अटल uपूर्णांक delay_pcm_irq[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 2पूर्ण;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for the EMU10K1 soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for the EMU10K1 soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable the EMU10K1 soundcard.");
module_param_array(extin, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(extin, "Available external inputs for FX8010. Zero=default.");
module_param_array(extout, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(extout, "Available external outputs for FX8010. Zero=default.");
module_param_array(seq_ports, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(seq_ports, "Allocated sequencer ports for internal synthesizer.");
module_param_array(max_synth_voices, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(max_synth_voices, "Maximum number of voices for WaveTable.");
module_param_array(max_buffer_size, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(max_buffer_size, "Maximum sample buffer size in MB.");
module_param_array(enable_ir, bool, शून्य, 0444);
MODULE_PARM_DESC(enable_ir, "Enable IR.");
module_param_array(subप्रणाली, uपूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(subप्रणाली, "Force card subsystem model.");
module_param_array(delay_pcm_irq, uपूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(delay_pcm_irq, "Delay PCM interrupt by specified number of samples (default 0).");
/*
 * Class 0401: 1102:0008 (rev 00) Subप्रणाली: 1102:1001 -> Audigy2 Value  Model:SB0400
 */
अटल स्थिर काष्ठा pci_device_id snd_emu10k1_ids[] = अणु
	अणु PCI_VDEVICE(CREATIVE, 0x0002), 0 पूर्ण,	/* EMU10K1 */
	अणु PCI_VDEVICE(CREATIVE, 0x0004), 1 पूर्ण,	/* Audigy */
	अणु PCI_VDEVICE(CREATIVE, 0x0008), 1 पूर्ण,	/* Audigy 2 Value SB0400 */
	अणु 0, पूर्ण
पूर्ण;

/*
 * Audigy 2 Value notes:
 * A_IOCFG Input (GPIO)
 * 0x400  = Front analog jack plugged in. (Green socket)
 * 0x1000 = Read analog jack plugged in. (Black socket)
 * 0x2000 = Center/LFE analog jack plugged in. (Orange socket)
 * A_IOCFG Output (GPIO)
 * 0x60 = Sound out of front Left.
 * Win sets it to 0xXX61
 */

MODULE_DEVICE_TABLE(pci, snd_emu10k1_ids);

अटल पूर्णांक snd_card_emu10k1_probe(काष्ठा pci_dev *pci,
				  स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_card *card;
	काष्ठा snd_emu10k1 *emu;
#अगर_घोषित ENABLE_SYNTH
	काष्ठा snd_seq_device *wave = शून्य;
#पूर्ण_अगर
	पूर्णांक err;

	अगर (dev >= SNDRV_CARDS)
        	वापस -ENODEV;
	अगर (!enable[dev]) अणु
		dev++;
		वापस -ENOENT;
	पूर्ण

	err = snd_card_new(&pci->dev, index[dev], id[dev], THIS_MODULE,
			   0, &card);
	अगर (err < 0)
		वापस err;
	अगर (max_buffer_size[dev] < 32)
		max_buffer_size[dev] = 32;
	अन्यथा अगर (max_buffer_size[dev] > 1024)
		max_buffer_size[dev] = 1024;
	अगर ((err = snd_emu10k1_create(card, pci, extin[dev], extout[dev],
				      (दीर्घ)max_buffer_size[dev] * 1024 * 1024,
				      enable_ir[dev], subप्रणाली[dev],
				      &emu)) < 0)
		जाओ error;
	card->निजी_data = emu;
	emu->delay_pcm_irq = delay_pcm_irq[dev] & 0x1f;
	अगर ((err = snd_emu10k1_pcm(emu, 0)) < 0)
		जाओ error;
	अगर ((err = snd_emu10k1_pcm_mic(emu, 1)) < 0)
		जाओ error;
	अगर ((err = snd_emu10k1_pcm_efx(emu, 2)) < 0)
		जाओ error;
	/* This stores the periods table. */
	अगर (emu->card_capabilities->ca0151_chip) अणु /* P16V */	
		err = snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, &pci->dev,
					  1024, &emu->p16v_buffer);
		अगर (err < 0)
			जाओ error;
	पूर्ण

	अगर ((err = snd_emu10k1_mixer(emu, 0, 3)) < 0)
		जाओ error;
	
	अगर ((err = snd_emu10k1_समयr(emu, 0)) < 0)
		जाओ error;

	अगर ((err = snd_emu10k1_pcm_multi(emu, 3)) < 0)
		जाओ error;
	अगर (emu->card_capabilities->ca0151_chip) अणु /* P16V */
		अगर ((err = snd_p16v_pcm(emu, 4)) < 0)
			जाओ error;
	पूर्ण
	अगर (emu->audigy) अणु
		अगर ((err = snd_emu10k1_audigy_midi(emu)) < 0)
			जाओ error;
	पूर्ण अन्यथा अणु
		अगर ((err = snd_emu10k1_midi(emu)) < 0)
			जाओ error;
	पूर्ण
	अगर ((err = snd_emu10k1_fx8010_new(emu, 0)) < 0)
		जाओ error;
#अगर_घोषित ENABLE_SYNTH
	अगर (snd_seq_device_new(card, 1, SNDRV_SEQ_DEV_ID_EMU10K1_SYNTH,
			       माप(काष्ठा snd_emu10k1_synth_arg), &wave) < 0 ||
	    wave == शून्य) अणु
		dev_warn(emu->card->dev,
			 "can't initialize Emu10k1 wavetable synth\n");
	पूर्ण अन्यथा अणु
		काष्ठा snd_emu10k1_synth_arg *arg;
		arg = SNDRV_SEQ_DEVICE_ARGPTR(wave);
		म_नकल(wave->name, "Emu-10k1 Synth");
		arg->hwptr = emu;
		arg->index = 1;
		arg->seq_ports = seq_ports[dev];
		arg->max_voices = max_synth_voices[dev];
	पूर्ण
#पूर्ण_अगर
 
	strscpy(card->driver, emu->card_capabilities->driver,
		माप(card->driver));
	strscpy(card->लघुname, emu->card_capabilities->name,
		माप(card->लघुname));
	snम_लिखो(card->दीर्घname, माप(card->दीर्घname),
		 "%s (rev.%d, serial:0x%x) at 0x%lx, irq %i",
		 card->लघुname, emu->revision, emu->serial, emu->port, emu->irq);

	अगर ((err = snd_card_रेजिस्टर(card)) < 0)
		जाओ error;

	अगर (emu->card_capabilities->emu_model)
		schedule_delayed_work(&emu->emu1010.firmware_work, 0);

	pci_set_drvdata(pci, card);
	dev++;
	वापस 0;

 error:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

अटल व्योम snd_card_emu10k1_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण


#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक snd_emu10k1_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा snd_emu10k1 *emu = card->निजी_data;

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);

	emu->suspend = 1;

	cancel_delayed_work_sync(&emu->emu1010.firmware_work);

	snd_ac97_suspend(emu->ac97);

	snd_emu10k1_efx_suspend(emu);
	snd_emu10k1_suspend_regs(emu);
	अगर (emu->card_capabilities->ca0151_chip)
		snd_p16v_suspend(emu);

	snd_emu10k1_करोne(emu);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_resume(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा snd_emu10k1 *emu = card->निजी_data;

	snd_emu10k1_resume_init(emu);
	snd_emu10k1_efx_resume(emu);
	snd_ac97_resume(emu->ac97);
	snd_emu10k1_resume_regs(emu);

	अगर (emu->card_capabilities->ca0151_chip)
		snd_p16v_resume(emu);

	emu->suspend = 0;

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);

	अगर (emu->card_capabilities->emu_model)
		schedule_delayed_work(&emu->emu1010.firmware_work, 0);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(snd_emu10k1_pm, snd_emu10k1_suspend, snd_emu10k1_resume);
#घोषणा SND_EMU10K1_PM_OPS	&snd_emu10k1_pm
#अन्यथा
#घोषणा SND_EMU10K1_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल काष्ठा pci_driver emu10k1_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_emu10k1_ids,
	.probe = snd_card_emu10k1_probe,
	.हटाओ = snd_card_emu10k1_हटाओ,
	.driver = अणु
		.pm = SND_EMU10K1_PM_OPS,
	पूर्ण,
पूर्ण;

module_pci_driver(emu10k1_driver);
