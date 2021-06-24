<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  ALSA card-level driver क्रम Turtle Beach Wavefront cards 
 *						(Maui,Tropez,Tropez+)
 *
 *  Copyright (c) 1997-1999 by Paul Barton-Davis <pbd@op.net>
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/err.h>
#समावेश <linux/isa.h>
#समावेश <linux/pnp.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/opl3.h>
#समावेश <sound/wss.h>
#समावेश <sound/snd_wavefront.h>

MODULE_AUTHOR("Paul Barton-Davis <pbd@op.net>");
MODULE_DESCRIPTION("Turtle Beach Wavefront");
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	    /* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	    /* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE;	    /* Enable this card */
#अगर_घोषित CONFIG_PNP
अटल bool isapnp[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 1पूर्ण;
#पूर्ण_अगर
अटल दीर्घ cs4232_pcm_port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;	/* PnP setup */
अटल पूर्णांक cs4232_pcm_irq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ; /* 5,7,9,11,12,15 */
अटल दीर्घ cs4232_mpu_port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT; /* PnP setup */
अटल पूर्णांक cs4232_mpu_irq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ; /* 9,11,12,15 */
अटल दीर्घ ics2115_port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT; /* PnP setup */
अटल पूर्णांक ics2115_irq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ;    /* 2,9,11,12,15 */
अटल दीर्घ fm_port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;	    /* PnP setup */
अटल पूर्णांक dma1[SNDRV_CARDS] = SNDRV_DEFAULT_DMA;	    /* 0,1,3,5,6,7 */
अटल पूर्णांक dma2[SNDRV_CARDS] = SNDRV_DEFAULT_DMA;	    /* 0,1,3,5,6,7 */
अटल bool use_cs4232_midi[SNDRV_CARDS];

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for WaveFront soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for WaveFront soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable WaveFront soundcard.");
#अगर_घोषित CONFIG_PNP
module_param_array(isapnp, bool, शून्य, 0444);
MODULE_PARM_DESC(isapnp, "ISA PnP detection for WaveFront soundcards.");
#पूर्ण_अगर
module_param_hw_array(cs4232_pcm_port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(cs4232_pcm_port, "Port # for CS4232 PCM interface.");
module_param_hw_array(cs4232_pcm_irq, पूर्णांक, irq, शून्य, 0444);
MODULE_PARM_DESC(cs4232_pcm_irq, "IRQ # for CS4232 PCM interface.");
module_param_hw_array(dma1, पूर्णांक, dma, शून्य, 0444);
MODULE_PARM_DESC(dma1, "DMA1 # for CS4232 PCM interface.");
module_param_hw_array(dma2, पूर्णांक, dma, शून्य, 0444);
MODULE_PARM_DESC(dma2, "DMA2 # for CS4232 PCM interface.");
module_param_hw_array(cs4232_mpu_port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(cs4232_mpu_port, "port # for CS4232 MPU-401 interface.");
module_param_hw_array(cs4232_mpu_irq, पूर्णांक, irq, शून्य, 0444);
MODULE_PARM_DESC(cs4232_mpu_irq, "IRQ # for CS4232 MPU-401 interface.");
module_param_hw_array(ics2115_irq, पूर्णांक, irq, शून्य, 0444);
MODULE_PARM_DESC(ics2115_irq, "IRQ # for ICS2115.");
module_param_hw_array(ics2115_port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(ics2115_port, "Port # for ICS2115.");
module_param_hw_array(fm_port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(fm_port, "FM port #.");
module_param_array(use_cs4232_midi, bool, शून्य, 0444);
MODULE_PARM_DESC(use_cs4232_midi, "Use CS4232 MPU-401 interface (inaccessibly located inside your computer)");

#अगर_घोषित CONFIG_PNP
अटल पूर्णांक isa_रेजिस्टरed;
अटल पूर्णांक pnp_रेजिस्टरed;

अटल स्थिर काष्ठा pnp_card_device_id snd_wavefront_pnpids[] = अणु
	/* Tropez */
	अणु .id = "CSC7532", .devs = अणु अणु "CSC0000" पूर्ण, अणु "CSC0010" पूर्ण, अणु "PnPb006" पूर्ण, अणु "CSC0004" पूर्ण पूर्ण पूर्ण,
	/* Tropez+ */
	अणु .id = "CSC7632", .devs = अणु अणु "CSC0000" पूर्ण, अणु "CSC0010" पूर्ण, अणु "PnPb006" पूर्ण, अणु "CSC0004" पूर्ण पूर्ण पूर्ण,
	अणु .id = "" पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pnp_card, snd_wavefront_pnpids);

अटल पूर्णांक
snd_wavefront_pnp (पूर्णांक dev, snd_wavefront_card_t *acard, काष्ठा pnp_card_link *card,
		   स्थिर काष्ठा pnp_card_device_id *id)
अणु
	काष्ठा pnp_dev *pdev;
	पूर्णांक err;

	/* Check क्रम each logical device. */

	/* CS4232 chip (aka "windows sound system") is logical device 0 */

	acard->wss = pnp_request_card_device(card, id->devs[0].id, शून्य);
	अगर (acard->wss == शून्य)
		वापस -EBUSY;

	/* there is a game port at logical device 1, but we ignore it completely */

	/* the control पूर्णांकerface is logical device 2, but we ignore it
	   completely. in fact, nobody even seems to know what it
	   करोes.
	*/

	/* Only configure the CS4232 MIDI पूर्णांकerface अगर its been
	   specअगरically requested. It is logical device 3.
	*/

	अगर (use_cs4232_midi[dev]) अणु
		acard->mpu = pnp_request_card_device(card, id->devs[2].id, शून्य);
		अगर (acard->mpu == शून्य)
			वापस -EBUSY;
	पूर्ण

	/* The ICS2115 synth is logical device 4 */

	acard->synth = pnp_request_card_device(card, id->devs[3].id, शून्य);
	अगर (acard->synth == शून्य)
		वापस -EBUSY;

	/* PCM/FM initialization */

	pdev = acard->wss;

	/* An पूर्णांकeresting note from the Tropez+ FAQ:

	   Q. [Ports] Why is the base address of the WSS I/O ports off by 4?

	   A. WSS I/O requires a block of 8 I/O addresses ("ports"). Of these, the first
	   4 are used to identअगरy and configure the board. With the advent of PnP,
	   these first 4 addresses have become obsolete, and software applications
	   only use the last 4 addresses to control the codec chip. Thereक्रमe, the
	   base address setting "skips past" the 4 unused addresses.

	*/

	err = pnp_activate_dev(pdev);
	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "PnP WSS pnp configure failure\n");
		वापस err;
	पूर्ण

	cs4232_pcm_port[dev] = pnp_port_start(pdev, 0);
	fm_port[dev] = pnp_port_start(pdev, 1);
	dma1[dev] = pnp_dma(pdev, 0);
	dma2[dev] = pnp_dma(pdev, 1);
	cs4232_pcm_irq[dev] = pnp_irq(pdev, 0);

	/* Synth initialization */

	pdev = acard->synth;
	
	err = pnp_activate_dev(pdev);
	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "PnP ICS2115 pnp configure failure\n");
		वापस err;
	पूर्ण

	ics2115_port[dev] = pnp_port_start(pdev, 0);
	ics2115_irq[dev] = pnp_irq(pdev, 0);

	/* CS4232 MPU initialization. Configure this only अगर
	   explicitly requested, since its physically inaccessible and
	   consumes another IRQ.
	*/

	अगर (use_cs4232_midi[dev]) अणु

		pdev = acard->mpu;

		err = pnp_activate_dev(pdev);
		अगर (err < 0) अणु
			snd_prपूर्णांकk(KERN_ERR "PnP MPU401 pnp configure failure\n");
			cs4232_mpu_port[dev] = SNDRV_AUTO_PORT;
		पूर्ण अन्यथा अणु
			cs4232_mpu_port[dev] = pnp_port_start(pdev, 0);
			cs4232_mpu_irq[dev] = pnp_irq(pdev, 0);
		पूर्ण

		snd_prपूर्णांकk (KERN_INFO "CS4232 MPU: port=0x%lx, irq=%i\n", 
			    cs4232_mpu_port[dev], 
			    cs4232_mpu_irq[dev]);
	पूर्ण

	snd_prपूर्णांकdd ("CS4232: pcm port=0x%lx, fm port=0x%lx, dma1=%i, dma2=%i, irq=%i\nICS2115: port=0x%lx, irq=%i\n", 
		    cs4232_pcm_port[dev], 
		    fm_port[dev],
		    dma1[dev], 
		    dma2[dev], 
		    cs4232_pcm_irq[dev],
		    ics2115_port[dev], 
		    ics2115_irq[dev]);
	
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_PNP */

अटल irqवापस_t snd_wavefront_ics2115_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	snd_wavefront_card_t *acard;

	acard = (snd_wavefront_card_t *) dev_id;

	अगर (acard == शून्य) 
		वापस IRQ_NONE;

	अगर (acard->wavefront.पूर्णांकerrupts_are_midi) अणु
		snd_wavefront_midi_पूर्णांकerrupt (acard);
	पूर्ण अन्यथा अणु
		snd_wavefront_पूर्णांकernal_पूर्णांकerrupt (acard);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा snd_hwdep *snd_wavefront_new_synth(काष्ठा snd_card *card,
						 पूर्णांक hw_dev,
						 snd_wavefront_card_t *acard)
अणु
	काष्ठा snd_hwdep *wavefront_synth;

	अगर (snd_wavefront_detect (acard) < 0) अणु
		वापस शून्य;
	पूर्ण

	अगर (snd_wavefront_start (&acard->wavefront) < 0) अणु
		वापस शून्य;
	पूर्ण

	अगर (snd_hwdep_new(card, "WaveFront", hw_dev, &wavefront_synth) < 0)
		वापस शून्य;
	म_नकल (wavefront_synth->name, 
		"WaveFront (ICS2115) wavetable synthesizer");
	wavefront_synth->ops.खोलो = snd_wavefront_synth_खोलो;
	wavefront_synth->ops.release = snd_wavefront_synth_release;
	wavefront_synth->ops.ioctl = snd_wavefront_synth_ioctl;

	वापस wavefront_synth;
पूर्ण

अटल काष्ठा snd_hwdep *snd_wavefront_new_fx(काष्ठा snd_card *card,
					      पूर्णांक hw_dev,
					      snd_wavefront_card_t *acard,
					      अचिन्हित दीर्घ port)

अणु
	काष्ठा snd_hwdep *fx_processor;

	अगर (snd_wavefront_fx_start (&acard->wavefront)) अणु
		snd_prपूर्णांकk (KERN_ERR "cannot initialize YSS225 FX processor");
		वापस शून्य;
	पूर्ण

	अगर (snd_hwdep_new (card, "YSS225", hw_dev, &fx_processor) < 0)
		वापस शून्य;
	प्र_लिखो (fx_processor->name, "YSS225 FX Processor at 0x%lx", port);
	fx_processor->ops.खोलो = snd_wavefront_fx_खोलो;
	fx_processor->ops.release = snd_wavefront_fx_release;
	fx_processor->ops.ioctl = snd_wavefront_fx_ioctl;
	
	वापस fx_processor;
पूर्ण

अटल snd_wavefront_mpu_id पूर्णांकernal_id = पूर्णांकernal_mpu;
अटल snd_wavefront_mpu_id बाह्यal_id = बाह्यal_mpu;

अटल काष्ठा snd_rawmidi *snd_wavefront_new_midi(काष्ठा snd_card *card,
						  पूर्णांक midi_dev,
						  snd_wavefront_card_t *acard,
						  अचिन्हित दीर्घ port,
						  snd_wavefront_mpu_id mpu)

अणु
	काष्ठा snd_rawmidi *rmidi;
	अटल पूर्णांक first = 1;

	अगर (first) अणु
		first = 0;
		acard->wavefront.midi.base = port;
		अगर (snd_wavefront_midi_start (acard)) अणु
			snd_prपूर्णांकk (KERN_ERR "cannot initialize MIDI interface\n");
			वापस शून्य;
		पूर्ण
	पूर्ण

	अगर (snd_rawmidi_new (card, "WaveFront MIDI", midi_dev, 1, 1, &rmidi) < 0)
		वापस शून्य;

	अगर (mpu == पूर्णांकernal_mpu) अणु
		म_नकल(rmidi->name, "WaveFront MIDI (Internal)");
		rmidi->निजी_data = &पूर्णांकernal_id;
	पूर्ण अन्यथा अणु
		म_नकल(rmidi->name, "WaveFront MIDI (External)");
		rmidi->निजी_data = &बाह्यal_id;
	पूर्ण

	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT, &snd_wavefront_midi_output);
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_INPUT, &snd_wavefront_midi_input);

	rmidi->info_flags |= SNDRV_RAWMIDI_INFO_OUTPUT |
			     SNDRV_RAWMIDI_INFO_INPUT |
			     SNDRV_RAWMIDI_INFO_DUPLEX;

	वापस rmidi;
पूर्ण

अटल व्योम
snd_wavefront_मुक्त(काष्ठा snd_card *card)
अणु
	snd_wavefront_card_t *acard = (snd_wavefront_card_t *)card->निजी_data;
	
	अगर (acard) अणु
		release_and_मुक्त_resource(acard->wavefront.res_base);
		अगर (acard->wavefront.irq > 0)
			मुक्त_irq(acard->wavefront.irq, (व्योम *)acard);
	पूर्ण
पूर्ण

अटल पूर्णांक snd_wavefront_card_new(काष्ठा device *pdev, पूर्णांक dev,
				  काष्ठा snd_card **cardp)
अणु
	काष्ठा snd_card *card;
	snd_wavefront_card_t *acard;
	पूर्णांक err;

	err = snd_card_new(pdev, index[dev], id[dev], THIS_MODULE,
			   माप(snd_wavefront_card_t), &card);
	अगर (err < 0)
		वापस err;

	acard = card->निजी_data;
	acard->wavefront.irq = -1;
	spin_lock_init(&acard->wavefront.irq_lock);
	init_रुकोqueue_head(&acard->wavefront.पूर्णांकerrupt_sleeper);
	spin_lock_init(&acard->wavefront.midi.खोलो);
	spin_lock_init(&acard->wavefront.midi.भव);
	acard->wavefront.card = card;
	card->निजी_मुक्त = snd_wavefront_मुक्त;

	*cardp = card;
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_wavefront_probe (काष्ठा snd_card *card, पूर्णांक dev)
अणु
	snd_wavefront_card_t *acard = card->निजी_data;
	काष्ठा snd_wss *chip;
	काष्ठा snd_hwdep *wavefront_synth;
	काष्ठा snd_rawmidi *ics2115_पूर्णांकernal_rmidi = शून्य;
	काष्ठा snd_rawmidi *ics2115_बाह्यal_rmidi = शून्य;
	काष्ठा snd_hwdep *fx_processor;
	पूर्णांक hw_dev = 0, midi_dev = 0, err;

	/* --------- PCM --------------- */

	err = snd_wss_create(card, cs4232_pcm_port[dev], -1,
			     cs4232_pcm_irq[dev], dma1[dev], dma2[dev],
			     WSS_HW_DETECT, 0, &chip);
	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "can't allocate WSS device\n");
		वापस err;
	पूर्ण

	err = snd_wss_pcm(chip, 0);
	अगर (err < 0)
		वापस err;

	err = snd_wss_समयr(chip, 0);
	अगर (err < 0)
		वापस err;

	/* ---------- OPL3 synth --------- */

	अगर (fm_port[dev] > 0 && fm_port[dev] != SNDRV_AUTO_PORT) अणु
		काष्ठा snd_opl3 *opl3;

		err = snd_opl3_create(card, fm_port[dev], fm_port[dev] + 2,
				      OPL3_HW_OPL3_CS, 0, &opl3);
		अगर (err < 0) अणु
			snd_prपूर्णांकk (KERN_ERR "can't allocate or detect OPL3 synth\n");
			वापस err;
		पूर्ण

		err = snd_opl3_hwdep_new(opl3, hw_dev, 1, शून्य);
		अगर (err < 0)
			वापस err;
		hw_dev++;
	पूर्ण

	/* ------- ICS2115 Wavetable synth ------- */

	acard->wavefront.res_base = request_region(ics2115_port[dev], 16,
						   "ICS2115");
	अगर (acard->wavefront.res_base == शून्य) अणु
		snd_prपूर्णांकk(KERN_ERR "unable to grab ICS2115 i/o region 0x%lx-0x%lx\n",
			   ics2115_port[dev], ics2115_port[dev] + 16 - 1);
		वापस -EBUSY;
	पूर्ण
	अगर (request_irq(ics2115_irq[dev], snd_wavefront_ics2115_पूर्णांकerrupt,
			0, "ICS2115", acard)) अणु
		snd_prपूर्णांकk(KERN_ERR "unable to use ICS2115 IRQ %d\n", ics2115_irq[dev]);
		वापस -EBUSY;
	पूर्ण
	
	acard->wavefront.irq = ics2115_irq[dev];
	card->sync_irq = acard->wavefront.irq;
	acard->wavefront.base = ics2115_port[dev];

	wavefront_synth = snd_wavefront_new_synth(card, hw_dev, acard);
	अगर (wavefront_synth == शून्य) अणु
		snd_prपूर्णांकk (KERN_ERR "can't create WaveFront synth device\n");
		वापस -ENOMEM;
	पूर्ण

	म_नकल (wavefront_synth->name, "ICS2115 Wavetable MIDI Synthesizer");
	wavefront_synth->अगरace = SNDRV_HWDEP_IFACE_ICS2115;
	hw_dev++;

	/* --------- Mixer ------------ */

	err = snd_wss_mixer(chip);
	अगर (err < 0) अणु
		snd_prपूर्णांकk (KERN_ERR "can't allocate mixer device\n");
		वापस err;
	पूर्ण

	/* -------- CS4232 MPU-401 पूर्णांकerface -------- */

	अगर (cs4232_mpu_port[dev] > 0 && cs4232_mpu_port[dev] != SNDRV_AUTO_PORT) अणु
		err = snd_mpu401_uart_new(card, midi_dev, MPU401_HW_CS4232,
					  cs4232_mpu_port[dev], 0,
					  cs4232_mpu_irq[dev], शून्य);
		अगर (err < 0) अणु
			snd_prपूर्णांकk (KERN_ERR "can't allocate CS4232 MPU-401 device\n");
			वापस err;
		पूर्ण
		midi_dev++;
	पूर्ण

	/* ------ ICS2115 पूर्णांकernal MIDI ------------ */

	अगर (ics2115_port[dev] > 0 && ics2115_port[dev] != SNDRV_AUTO_PORT) अणु
		ics2115_पूर्णांकernal_rmidi = 
			snd_wavefront_new_midi (card, 
						midi_dev,
						acard,
						ics2115_port[dev],
						पूर्णांकernal_mpu);
		अगर (ics2115_पूर्णांकernal_rmidi == शून्य) अणु
			snd_prपूर्णांकk (KERN_ERR "can't setup ICS2115 internal MIDI device\n");
			वापस -ENOMEM;
		पूर्ण
		midi_dev++;
	पूर्ण

	/* ------ ICS2115 बाह्यal MIDI ------------ */

	अगर (ics2115_port[dev] > 0 && ics2115_port[dev] != SNDRV_AUTO_PORT) अणु
		ics2115_बाह्यal_rmidi = 
			snd_wavefront_new_midi (card, 
						midi_dev,
						acard,
						ics2115_port[dev],
						बाह्यal_mpu);
		अगर (ics2115_बाह्यal_rmidi == शून्य) अणु
			snd_prपूर्णांकk (KERN_ERR "can't setup ICS2115 external MIDI device\n");
			वापस -ENOMEM;
		पूर्ण
		midi_dev++;
	पूर्ण

	/* FX processor क्रम Tropez+ */

	अगर (acard->wavefront.has_fx) अणु
		fx_processor = snd_wavefront_new_fx (card,
						     hw_dev,
						     acard,
						     ics2115_port[dev]);
		अगर (fx_processor == शून्य) अणु
			snd_prपूर्णांकk (KERN_ERR "can't setup FX device\n");
			वापस -ENOMEM;
		पूर्ण

		hw_dev++;

		म_नकल(card->driver, "Tropez+");
		म_नकल(card->लघुname, "Turtle Beach Tropez+");
	पूर्ण अन्यथा अणु
		/* Need a way to distinguish between Maui and Tropez */
		म_नकल(card->driver, "WaveFront");
		म_नकल(card->लघुname, "Turtle Beach WaveFront");
	पूर्ण

	/* ----- Register the card --------- */

	/* Not safe to include "Turtle Beach" in दीर्घname, due to 
	   length restrictions
	*/

	प्र_लिखो(card->दीर्घname, "%s PCM 0x%lx irq %d dma %d",
		card->driver,
		chip->port,
		cs4232_pcm_irq[dev],
		dma1[dev]);

	अगर (dma2[dev] >= 0 && dma2[dev] < 8)
		प्र_लिखो(card->दीर्घname + म_माप(card->दीर्घname), "&%d", dma2[dev]);

	अगर (cs4232_mpu_port[dev] > 0 && cs4232_mpu_port[dev] != SNDRV_AUTO_PORT) अणु
		प्र_लिखो (card->दीर्घname + म_माप (card->दीर्घname), 
			 " MPU-401 0x%lx irq %d",
			 cs4232_mpu_port[dev],
			 cs4232_mpu_irq[dev]);
	पूर्ण

	प्र_लिखो (card->दीर्घname + म_माप (card->दीर्घname), 
		 " SYNTH 0x%lx irq %d",
		 ics2115_port[dev],
		 ics2115_irq[dev]);

	वापस snd_card_रेजिस्टर(card);
पूर्ण	

अटल पूर्णांक snd_wavefront_isa_match(काष्ठा device *pdev,
				   अचिन्हित पूर्णांक dev)
अणु
	अगर (!enable[dev])
		वापस 0;
#अगर_घोषित CONFIG_PNP
	अगर (isapnp[dev])
		वापस 0;
#पूर्ण_अगर
	अगर (cs4232_pcm_port[dev] == SNDRV_AUTO_PORT) अणु
		snd_prपूर्णांकk(KERN_ERR "specify CS4232 port\n");
		वापस 0;
	पूर्ण
	अगर (ics2115_port[dev] == SNDRV_AUTO_PORT) अणु
		snd_prपूर्णांकk(KERN_ERR "specify ICS2115 port\n");
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक snd_wavefront_isa_probe(काष्ठा device *pdev,
				   अचिन्हित पूर्णांक dev)
अणु
	काष्ठा snd_card *card;
	पूर्णांक err;

	err = snd_wavefront_card_new(pdev, dev, &card);
	अगर (err < 0)
		वापस err;
	अगर ((err = snd_wavefront_probe(card, dev)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	
	dev_set_drvdata(pdev, card);
	वापस 0;
पूर्ण

अटल व्योम snd_wavefront_isa_हटाओ(काष्ठा device *devptr,
				    अचिन्हित पूर्णांक dev)
अणु
	snd_card_मुक्त(dev_get_drvdata(devptr));
पूर्ण

#घोषणा DEV_NAME "wavefront"

अटल काष्ठा isa_driver snd_wavefront_driver = अणु
	.match		= snd_wavefront_isa_match,
	.probe		= snd_wavefront_isa_probe,
	.हटाओ		= snd_wavefront_isa_हटाओ,
	/* FIXME: suspend, resume */
	.driver		= अणु
		.name	= DEV_NAME
	पूर्ण,
पूर्ण;


#अगर_घोषित CONFIG_PNP
अटल पूर्णांक snd_wavefront_pnp_detect(काष्ठा pnp_card_link *pcard,
				    स्थिर काष्ठा pnp_card_device_id *pid)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_card *card;
	पूर्णांक res;

	क्रम ( ; dev < SNDRV_CARDS; dev++) अणु
		अगर (enable[dev] && isapnp[dev])
			अवरोध;
	पूर्ण
	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;

	res = snd_wavefront_card_new(&pcard->card->dev, dev, &card);
	अगर (res < 0)
		वापस res;

	अगर (snd_wavefront_pnp (dev, card->निजी_data, pcard, pid) < 0) अणु
		अगर (cs4232_pcm_port[dev] == SNDRV_AUTO_PORT) अणु
			snd_prपूर्णांकk (KERN_ERR "isapnp detection failed\n");
			snd_card_मुक्त (card);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	अगर ((res = snd_wavefront_probe(card, dev)) < 0)
		वापस res;

	pnp_set_card_drvdata(pcard, card);
	dev++;
	वापस 0;
पूर्ण

अटल व्योम snd_wavefront_pnp_हटाओ(काष्ठा pnp_card_link *pcard)
अणु
	snd_card_मुक्त(pnp_get_card_drvdata(pcard));
	pnp_set_card_drvdata(pcard, शून्य);
पूर्ण

अटल काष्ठा pnp_card_driver wavefront_pnpc_driver = अणु
	.flags		= PNP_DRIVER_RES_DISABLE,
	.name		= "wavefront",
	.id_table	= snd_wavefront_pnpids,
	.probe		= snd_wavefront_pnp_detect,
	.हटाओ		= snd_wavefront_pnp_हटाओ,
	/* FIXME: suspend,resume */
पूर्ण;

#पूर्ण_अगर /* CONFIG_PNP */

अटल पूर्णांक __init alsa_card_wavefront_init(व्योम)
अणु
	पूर्णांक err;

	err = isa_रेजिस्टर_driver(&snd_wavefront_driver, SNDRV_CARDS);
#अगर_घोषित CONFIG_PNP
	अगर (!err)
		isa_रेजिस्टरed = 1;

	err = pnp_रेजिस्टर_card_driver(&wavefront_pnpc_driver);
	अगर (!err)
		pnp_रेजिस्टरed = 1;

	अगर (isa_रेजिस्टरed)
		err = 0;
#पूर्ण_अगर
	वापस err;
पूर्ण

अटल व्योम __निकास alsa_card_wavefront_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_PNP
	अगर (pnp_रेजिस्टरed)
		pnp_unरेजिस्टर_card_driver(&wavefront_pnpc_driver);
	अगर (isa_रेजिस्टरed)
#पूर्ण_अगर
		isa_unरेजिस्टर_driver(&snd_wavefront_driver);
पूर्ण

module_init(alsa_card_wavefront_init)
module_निकास(alsa_card_wavefront_निकास)
