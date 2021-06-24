<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम C-Media's CMI8330 and CMI8329 soundcards.
 *  Copyright (c) by George Talusan <gstalusan@uwaterloo.ca>
 *    http://www.undergrad.math.uwaterloo.ca/~gstalusa
 */

/*
 * NOTES
 *
 *  The extended रेजिस्टरs contain mixer settings which are largely
 *  untapped क्रम the समय being.
 *
 *  MPU401 and SPDIF are not supported yet.  I करोn't have the hardware
 *  to aid in coding and testing, so I won't bother.
 *
 *  To quickly load the module,
 *
 *  modprobe -a snd-cmi8330 sbport=0x220 sbirq=5 sbdma8=1
 *    sbdma16=5 wssport=0x530 wssirq=11 wssdma=0 fmport=0x388
 *
 *  This card has two mixers and two PCM devices.  I've cheesed it such
 *  that recording and playback can be करोne through the same device.
 *  The driver "magically" routes the capturing to the AD1848 codec,
 *  and playback to the SB16 codec.  This allows क्रम full-duplex mode
 *  to some extent.
 *  The utilities in alsa-utils are aware of both devices, so passing
 *  the appropriate parameters to amixer and alsactl will give you
 *  full control over both mixers.
 */

#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/isa.h>
#समावेश <linux/pnp.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/wss.h>
#समावेश <sound/opl3.h>
#समावेश <sound/mpu401.h>
#समावेश <sound/sb.h>
#समावेश <sound/initval.h>

/*
 */
/* #घोषणा ENABLE_SB_MIXER */
#घोषणा PLAYBACK_ON_SB

/*
 */
MODULE_AUTHOR("George Talusan <gstalusan@uwaterloo.ca>");
MODULE_DESCRIPTION("C-Media CMI8330/CMI8329");
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_ISAPNP;
#अगर_घोषित CONFIG_PNP
अटल bool isapnp[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 1पूर्ण;
#पूर्ण_अगर
अटल दीर्घ sbport[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;
अटल पूर्णांक sbirq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ;
अटल पूर्णांक sbdma8[SNDRV_CARDS] = SNDRV_DEFAULT_DMA;
अटल पूर्णांक sbdma16[SNDRV_CARDS] = SNDRV_DEFAULT_DMA;
अटल दीर्घ wssport[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;
अटल पूर्णांक wssirq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ;
अटल पूर्णांक wssdma[SNDRV_CARDS] = SNDRV_DEFAULT_DMA;
अटल दीर्घ fmport[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;
अटल दीर्घ mpuport[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;
अटल पूर्णांक mpuirq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for CMI8330/CMI8329 soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string  for CMI8330/CMI8329 soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable CMI8330/CMI8329 soundcard.");
#अगर_घोषित CONFIG_PNP
module_param_array(isapnp, bool, शून्य, 0444);
MODULE_PARM_DESC(isapnp, "PnP detection for specified soundcard.");
#पूर्ण_अगर

module_param_hw_array(sbport, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(sbport, "Port # for CMI8330/CMI8329 SB driver.");
module_param_hw_array(sbirq, पूर्णांक, irq, शून्य, 0444);
MODULE_PARM_DESC(sbirq, "IRQ # for CMI8330/CMI8329 SB driver.");
module_param_hw_array(sbdma8, पूर्णांक, dma, शून्य, 0444);
MODULE_PARM_DESC(sbdma8, "DMA8 for CMI8330/CMI8329 SB driver.");
module_param_hw_array(sbdma16, पूर्णांक, dma, शून्य, 0444);
MODULE_PARM_DESC(sbdma16, "DMA16 for CMI8330/CMI8329 SB driver.");

module_param_hw_array(wssport, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(wssport, "Port # for CMI8330/CMI8329 WSS driver.");
module_param_hw_array(wssirq, पूर्णांक, irq, शून्य, 0444);
MODULE_PARM_DESC(wssirq, "IRQ # for CMI8330/CMI8329 WSS driver.");
module_param_hw_array(wssdma, पूर्णांक, dma, शून्य, 0444);
MODULE_PARM_DESC(wssdma, "DMA for CMI8330/CMI8329 WSS driver.");

module_param_hw_array(fmport, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(fmport, "FM port # for CMI8330/CMI8329 driver.");
module_param_hw_array(mpuport, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(mpuport, "MPU-401 port # for CMI8330/CMI8329 driver.");
module_param_hw_array(mpuirq, पूर्णांक, irq, शून्य, 0444);
MODULE_PARM_DESC(mpuirq, "IRQ # for CMI8330/CMI8329 MPU-401 port.");
#अगर_घोषित CONFIG_PNP
अटल पूर्णांक isa_रेजिस्टरed;
अटल पूर्णांक pnp_रेजिस्टरed;
#पूर्ण_अगर

#घोषणा CMI8330_RMUX3D    16
#घोषणा CMI8330_MUTEMUX   17
#घोषणा CMI8330_OUTPUTVOL 18
#घोषणा CMI8330_MASTVOL   19
#घोषणा CMI8330_LINVOL    20
#घोषणा CMI8330_CDINVOL   21
#घोषणा CMI8330_WAVVOL    22
#घोषणा CMI8330_RECMUX    23
#घोषणा CMI8330_WAVGAIN   24
#घोषणा CMI8330_LINGAIN   25
#घोषणा CMI8330_CDINGAIN  26

अटल स्थिर अचिन्हित अक्षर snd_cmi8330_image[((CMI8330_CDINGAIN)-16) + 1] =
अणु
	0x40,			/* 16 - recording mux (SB-mixer-enabled) */
#अगर_घोषित ENABLE_SB_MIXER
	0x40,			/* 17 - mute mux (Mode2) */
#अन्यथा
	0x0,			/* 17 - mute mux */
#पूर्ण_अगर
	0x0,			/* 18 - vol */
	0x0,			/* 19 - master volume */
	0x0,			/* 20 - line-in volume */
	0x0,			/* 21 - cd-in volume */
	0x0,			/* 22 - wave volume */
	0x0,			/* 23 - mute/rec mux */
	0x0,			/* 24 - wave rec gain */
	0x0,			/* 25 - line-in rec gain */
	0x0			/* 26 - cd-in rec gain */
पूर्ण;

प्रकार पूर्णांक (*snd_pcm_खोलो_callback_t)(काष्ठा snd_pcm_substream *);

क्रमागत card_type अणु
	CMI8330,
	CMI8329
पूर्ण;

काष्ठा snd_cmi8330 अणु
#अगर_घोषित CONFIG_PNP
	काष्ठा pnp_dev *cap;
	काष्ठा pnp_dev *play;
	काष्ठा pnp_dev *mpu;
#पूर्ण_अगर
	काष्ठा snd_card *card;
	काष्ठा snd_wss *wss;
	काष्ठा snd_sb *sb;

	काष्ठा snd_pcm *pcm;
	काष्ठा snd_cmi8330_stream अणु
		काष्ठा snd_pcm_ops ops;
		snd_pcm_खोलो_callback_t खोलो;
		व्योम *निजी_data; /* sb or wss */
	पूर्ण streams[2];

	क्रमागत card_type type;
पूर्ण;

#अगर_घोषित CONFIG_PNP

अटल स्थिर काष्ठा pnp_card_device_id snd_cmi8330_pnpids[] = अणु
	अणु .id = "CMI0001", .devs = अणु अणु "@X@0001" पूर्ण, अणु "@@@0001" पूर्ण, अणु "@H@0001" पूर्ण, अणु "A@@0001" पूर्ण पूर्ण पूर्ण,
	अणु .id = "CMI0001", .devs = अणु अणु "@@@0001" पूर्ण, अणु "@X@0001" पूर्ण, अणु "@H@0001" पूर्ण पूर्ण पूर्ण,
	अणु .id = "" पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pnp_card, snd_cmi8330_pnpids);

#पूर्ण_अगर


अटल स्थिर काष्ठा snd_kcontrol_new snd_cmi8330_controls[] = अणु
WSS_DOUBLE("Master Playback Volume", 0,
		CMI8330_MASTVOL, CMI8330_MASTVOL, 4, 0, 15, 0),
WSS_SINGLE("Loud Playback Switch", 0,
		CMI8330_MUTEMUX, 6, 1, 1),
WSS_DOUBLE("PCM Playback Switch", 0,
		CS4231_LEFT_OUTPUT, CS4231_RIGHT_OUTPUT, 7, 7, 1, 1),
WSS_DOUBLE("PCM Playback Volume", 0,
		CS4231_LEFT_OUTPUT, CS4231_RIGHT_OUTPUT, 0, 0, 63, 1),
WSS_DOUBLE("Line Playback Switch", 0,
		CMI8330_MUTEMUX, CMI8330_MUTEMUX, 4, 3, 1, 0),
WSS_DOUBLE("Line Playback Volume", 0,
		CMI8330_LINVOL, CMI8330_LINVOL, 4, 0, 15, 0),
WSS_DOUBLE("Line Capture Switch", 0,
		CMI8330_RMUX3D, CMI8330_RMUX3D, 2, 1, 1, 0),
WSS_DOUBLE("Line Capture Volume", 0,
		CMI8330_LINGAIN, CMI8330_LINGAIN, 4, 0, 15, 0),
WSS_DOUBLE("CD Playback Switch", 0,
		CMI8330_MUTEMUX, CMI8330_MUTEMUX, 2, 1, 1, 0),
WSS_DOUBLE("CD Capture Switch", 0,
		CMI8330_RMUX3D, CMI8330_RMUX3D, 4, 3, 1, 0),
WSS_DOUBLE("CD Playback Volume", 0,
		CMI8330_CDINVOL, CMI8330_CDINVOL, 4, 0, 15, 0),
WSS_DOUBLE("CD Capture Volume", 0,
		CMI8330_CDINGAIN, CMI8330_CDINGAIN, 4, 0, 15, 0),
WSS_SINGLE("Mic Playback Switch", 0,
		CMI8330_MUTEMUX, 0, 1, 0),
WSS_SINGLE("Mic Playback Volume", 0,
		CMI8330_OUTPUTVOL, 0, 7, 0),
WSS_SINGLE("Mic Capture Switch", 0,
		CMI8330_RMUX3D, 0, 1, 0),
WSS_SINGLE("Mic Capture Volume", 0,
		CMI8330_OUTPUTVOL, 5, 7, 0),
WSS_DOUBLE("Wavetable Playback Switch", 0,
		CMI8330_RECMUX, CMI8330_RECMUX, 1, 0, 1, 0),
WSS_DOUBLE("Wavetable Playback Volume", 0,
		CMI8330_WAVVOL, CMI8330_WAVVOL, 4, 0, 15, 0),
WSS_DOUBLE("Wavetable Capture Switch", 0,
		CMI8330_RECMUX, CMI8330_RECMUX, 5, 4, 1, 0),
WSS_DOUBLE("Wavetable Capture Volume", 0,
		CMI8330_WAVGAIN, CMI8330_WAVGAIN, 4, 0, 15, 0),
WSS_SINGLE("3D Control - Switch", 0,
		CMI8330_RMUX3D, 5, 1, 1),
WSS_SINGLE("Beep Playback Volume", 0,
		CMI8330_OUTPUTVOL, 3, 3, 0),
WSS_DOUBLE("FM Playback Switch", 0,
		CS4231_AUX2_LEFT_INPUT, CS4231_AUX2_RIGHT_INPUT, 7, 7, 1, 1),
WSS_DOUBLE("FM Playback Volume", 0,
		CS4231_AUX2_LEFT_INPUT, CS4231_AUX2_RIGHT_INPUT, 0, 0, 31, 1),
WSS_SINGLE(SNDRV_CTL_NAME_IEC958("Input ", CAPTURE, SWITCH), 0,
		CMI8330_RMUX3D, 7, 1, 1),
WSS_SINGLE(SNDRV_CTL_NAME_IEC958("Input ", PLAYBACK, SWITCH), 0,
		CMI8330_MUTEMUX, 7, 1, 1),
पूर्ण;

#अगर_घोषित ENABLE_SB_MIXER
अटल स्थिर काष्ठा sbmix_elem cmi8330_sb_mixers[] = अणु
SB_DOUBLE("SB Master Playback Volume", SB_DSP4_MASTER_DEV, (SB_DSP4_MASTER_DEV + 1), 3, 3, 31),
SB_DOUBLE("Tone Control - Bass", SB_DSP4_BASS_DEV, (SB_DSP4_BASS_DEV + 1), 4, 4, 15),
SB_DOUBLE("Tone Control - Treble", SB_DSP4_TREBLE_DEV, (SB_DSP4_TREBLE_DEV + 1), 4, 4, 15),
SB_DOUBLE("SB PCM Playback Volume", SB_DSP4_PCM_DEV, (SB_DSP4_PCM_DEV + 1), 3, 3, 31),
SB_DOUBLE("SB Synth Playback Volume", SB_DSP4_SYNTH_DEV, (SB_DSP4_SYNTH_DEV + 1), 3, 3, 31),
SB_DOUBLE("SB CD Playback Switch", SB_DSP4_OUTPUT_SW, SB_DSP4_OUTPUT_SW, 2, 1, 1),
SB_DOUBLE("SB CD Playback Volume", SB_DSP4_CD_DEV, (SB_DSP4_CD_DEV + 1), 3, 3, 31),
SB_DOUBLE("SB Line Playback Switch", SB_DSP4_OUTPUT_SW, SB_DSP4_OUTPUT_SW, 4, 3, 1),
SB_DOUBLE("SB Line Playback Volume", SB_DSP4_LINE_DEV, (SB_DSP4_LINE_DEV + 1), 3, 3, 31),
SB_SINGLE("SB Mic Playback Switch", SB_DSP4_OUTPUT_SW, 0, 1),
SB_SINGLE("SB Mic Playback Volume", SB_DSP4_MIC_DEV, 3, 31),
SB_SINGLE("SB Beep Volume", SB_DSP4_SPEAKER_DEV, 6, 3),
SB_DOUBLE("SB Capture Volume", SB_DSP4_IGAIN_DEV, (SB_DSP4_IGAIN_DEV + 1), 6, 6, 3),
SB_DOUBLE("SB Playback Volume", SB_DSP4_OGAIN_DEV, (SB_DSP4_OGAIN_DEV + 1), 6, 6, 3),
SB_SINGLE("SB Mic Auto Gain", SB_DSP4_MIC_AGC, 0, 1),
पूर्ण;

अटल स्थिर अचिन्हित अक्षर cmi8330_sb_init_values[][2] = अणु
	अणु SB_DSP4_MASTER_DEV + 0, 0 पूर्ण,
	अणु SB_DSP4_MASTER_DEV + 1, 0 पूर्ण,
	अणु SB_DSP4_PCM_DEV + 0, 0 पूर्ण,
	अणु SB_DSP4_PCM_DEV + 1, 0 पूर्ण,
	अणु SB_DSP4_SYNTH_DEV + 0, 0 पूर्ण,
	अणु SB_DSP4_SYNTH_DEV + 1, 0 पूर्ण,
	अणु SB_DSP4_INPUT_LEFT, 0 पूर्ण,
	अणु SB_DSP4_INPUT_RIGHT, 0 पूर्ण,
	अणु SB_DSP4_OUTPUT_SW, 0 पूर्ण,
	अणु SB_DSP4_SPEAKER_DEV, 0 पूर्ण,
पूर्ण;


अटल पूर्णांक cmi8330_add_sb_mixers(काष्ठा snd_sb *chip)
अणु
	पूर्णांक idx, err;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->mixer_lock, flags);
	snd_sbmixer_ग_लिखो(chip, 0x00, 0x00);		/* mixer reset */
	spin_unlock_irqrestore(&chip->mixer_lock, flags);

	/* mute and zero volume channels */
	क्रम (idx = 0; idx < ARRAY_SIZE(cmi8330_sb_init_values); idx++) अणु
		spin_lock_irqsave(&chip->mixer_lock, flags);
		snd_sbmixer_ग_लिखो(chip, cmi8330_sb_init_values[idx][0],
				  cmi8330_sb_init_values[idx][1]);
		spin_unlock_irqrestore(&chip->mixer_lock, flags);
	पूर्ण

	क्रम (idx = 0; idx < ARRAY_SIZE(cmi8330_sb_mixers); idx++) अणु
		अगर ((err = snd_sbmixer_add_ctl_elem(chip, &cmi8330_sb_mixers[idx])) < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक snd_cmi8330_mixer(काष्ठा snd_card *card, काष्ठा snd_cmi8330 *acard)
अणु
	अचिन्हित पूर्णांक idx;
	पूर्णांक err;

	म_नकल(card->mixername, (acard->type == CMI8329) ? "CMI8329" : "CMI8330/C3D");

	क्रम (idx = 0; idx < ARRAY_SIZE(snd_cmi8330_controls); idx++) अणु
		err = snd_ctl_add(card,
				snd_ctl_new1(&snd_cmi8330_controls[idx],
					     acard->wss));
		अगर (err < 0)
			वापस err;
	पूर्ण

#अगर_घोषित ENABLE_SB_MIXER
	अगर ((err = cmi8330_add_sb_mixers(acard->sb)) < 0)
		वापस err;
#पूर्ण_अगर
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PNP
अटल पूर्णांक snd_cmi8330_pnp(पूर्णांक dev, काष्ठा snd_cmi8330 *acard,
			   काष्ठा pnp_card_link *card,
			   स्थिर काष्ठा pnp_card_device_id *id)
अणु
	काष्ठा pnp_dev *pdev;
	पूर्णांक err;

	/* CMI8329 has a device with ID A@@0001, CMI8330 करोes not */
	acard->type = (id->devs[3].id[0]) ? CMI8329 : CMI8330;

	acard->cap = pnp_request_card_device(card, id->devs[0].id, शून्य);
	अगर (acard->cap == शून्य)
		वापस -EBUSY;

	acard->play = pnp_request_card_device(card, id->devs[1].id, शून्य);
	अगर (acard->play == शून्य)
		वापस -EBUSY;

	acard->mpu = pnp_request_card_device(card, id->devs[2].id, शून्य);
	अगर (acard->mpu == शून्य)
		वापस -EBUSY;

	pdev = acard->cap;

	err = pnp_activate_dev(pdev);
	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "AD1848 PnP configure failure\n");
		वापस -EBUSY;
	पूर्ण
	wssport[dev] = pnp_port_start(pdev, 0);
	wssdma[dev] = pnp_dma(pdev, 0);
	wssirq[dev] = pnp_irq(pdev, 0);
	अगर (pnp_port_start(pdev, 1))
		fmport[dev] = pnp_port_start(pdev, 1);

	/* allocate SB16 resources */
	pdev = acard->play;

	err = pnp_activate_dev(pdev);
	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "SB16 PnP configure failure\n");
		वापस -EBUSY;
	पूर्ण
	sbport[dev] = pnp_port_start(pdev, 0);
	sbdma8[dev] = pnp_dma(pdev, 0);
	sbdma16[dev] = pnp_dma(pdev, 1);
	sbirq[dev] = pnp_irq(pdev, 0);
	/* On CMI8239, the OPL3 port might be present in SB16 PnP resources */
	अगर (fmport[dev] == SNDRV_AUTO_PORT) अणु
		अगर (pnp_port_start(pdev, 1))
			fmport[dev] = pnp_port_start(pdev, 1);
		अन्यथा
			fmport[dev] = 0x388;	/* Or hardwired */
	पूर्ण

	/* allocate MPU-401 resources */
	pdev = acard->mpu;

	err = pnp_activate_dev(pdev);
	अगर (err < 0)
		snd_prपूर्णांकk(KERN_ERR "MPU-401 PnP configure failure: will be disabled\n");
	अन्यथा अणु
		mpuport[dev] = pnp_port_start(pdev, 0);
		mpuirq[dev] = pnp_irq(pdev, 0);
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * PCM पूर्णांकerface
 *
 * since we call the dअगरferent chip पूर्णांकerfaces क्रम playback and capture
 * directions, we need a trick.
 *
 * - copy the ops क्रम each direction पूर्णांकo a local record.
 * - replace the खोलो callback with the new one, which replaces the
 *   substream->निजी_data with the corresponding chip instance
 *   and calls again the original खोलो callback of the chip.
 *
 */

#अगर_घोषित PLAYBACK_ON_SB
#घोषणा CMI_SB_STREAM	SNDRV_PCM_STREAM_PLAYBACK
#घोषणा CMI_AD_STREAM	SNDRV_PCM_STREAM_CAPTURE
#अन्यथा
#घोषणा CMI_SB_STREAM	SNDRV_PCM_STREAM_CAPTURE
#घोषणा CMI_AD_STREAM	SNDRV_PCM_STREAM_PLAYBACK
#पूर्ण_अगर

अटल पूर्णांक snd_cmi8330_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_cmi8330 *chip = snd_pcm_substream_chip(substream);

	/* replace the निजी_data and call the original खोलो callback */
	substream->निजी_data = chip->streams[SNDRV_PCM_STREAM_PLAYBACK].निजी_data;
	वापस chip->streams[SNDRV_PCM_STREAM_PLAYBACK].खोलो(substream);
पूर्ण

अटल पूर्णांक snd_cmi8330_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_cmi8330 *chip = snd_pcm_substream_chip(substream);

	/* replace the निजी_data and call the original खोलो callback */
	substream->निजी_data = chip->streams[SNDRV_PCM_STREAM_CAPTURE].निजी_data;
	वापस chip->streams[SNDRV_PCM_STREAM_CAPTURE].खोलो(substream);
पूर्ण

अटल पूर्णांक snd_cmi8330_pcm(काष्ठा snd_card *card, काष्ठा snd_cmi8330 *chip)
अणु
	काष्ठा snd_pcm *pcm;
	स्थिर काष्ठा snd_pcm_ops *ops;
	पूर्णांक err;
	अटल स्थिर snd_pcm_खोलो_callback_t cmi_खोलो_callbacks[2] = अणु
		snd_cmi8330_playback_खोलो,
		snd_cmi8330_capture_खोलो
	पूर्ण;

	अगर ((err = snd_pcm_new(card, (chip->type == CMI8329) ? "CMI8329" : "CMI8330", 0, 1, 1, &pcm)) < 0)
		वापस err;
	म_नकल(pcm->name, (chip->type == CMI8329) ? "CMI8329" : "CMI8330");
	pcm->निजी_data = chip;
	
	/* SB16 */
	ops = snd_sb16dsp_get_pcm_ops(CMI_SB_STREAM);
	chip->streams[CMI_SB_STREAM].ops = *ops;
	chip->streams[CMI_SB_STREAM].खोलो = ops->खोलो;
	chip->streams[CMI_SB_STREAM].ops.खोलो = cmi_खोलो_callbacks[CMI_SB_STREAM];
	chip->streams[CMI_SB_STREAM].निजी_data = chip->sb;

	/* AD1848 */
	ops = snd_wss_get_pcm_ops(CMI_AD_STREAM);
	chip->streams[CMI_AD_STREAM].ops = *ops;
	chip->streams[CMI_AD_STREAM].खोलो = ops->खोलो;
	chip->streams[CMI_AD_STREAM].ops.खोलो = cmi_खोलो_callbacks[CMI_AD_STREAM];
	chip->streams[CMI_AD_STREAM].निजी_data = chip->wss;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &chip->streams[SNDRV_PCM_STREAM_PLAYBACK].ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &chip->streams[SNDRV_PCM_STREAM_CAPTURE].ops);

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
				       card->dev, 64*1024, 128*1024);
	chip->pcm = pcm;

	वापस 0;
पूर्ण


#अगर_घोषित CONFIG_PM
अटल पूर्णांक snd_cmi8330_suspend(काष्ठा snd_card *card)
अणु
	काष्ठा snd_cmi8330 *acard = card->निजी_data;

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);
	acard->wss->suspend(acard->wss);
	snd_sbmixer_suspend(acard->sb);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cmi8330_resume(काष्ठा snd_card *card)
अणु
	काष्ठा snd_cmi8330 *acard = card->निजी_data;

	snd_sbdsp_reset(acard->sb);
	snd_sbmixer_suspend(acard->sb);
	acard->wss->resume(acard->wss);
	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण
#पूर्ण_अगर


/*
 */

#अगर_घोषित CONFIG_PNP
#घोषणा is_isapnp_selected(dev)		isapnp[dev]
#अन्यथा
#घोषणा is_isapnp_selected(dev)		0
#पूर्ण_अगर

#घोषणा PFX	"cmi8330: "

अटल पूर्णांक snd_cmi8330_card_new(काष्ठा device *pdev, पूर्णांक dev,
				काष्ठा snd_card **cardp)
अणु
	काष्ठा snd_card *card;
	काष्ठा snd_cmi8330 *acard;
	पूर्णांक err;

	err = snd_card_new(pdev, index[dev], id[dev], THIS_MODULE,
			   माप(काष्ठा snd_cmi8330), &card);
	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR PFX "could not get a new card\n");
		वापस err;
	पूर्ण
	acard = card->निजी_data;
	acard->card = card;
	*cardp = card;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cmi8330_probe(काष्ठा snd_card *card, पूर्णांक dev)
अणु
	काष्ठा snd_cmi8330 *acard;
	पूर्णांक i, err;
	काष्ठा snd_opl3 *opl3;

	acard = card->निजी_data;
	err = snd_wss_create(card, wssport[dev] + 4, -1,
			     wssirq[dev],
			     wssdma[dev], -1,
			     WSS_HW_DETECT, 0, &acard->wss);
	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR PFX "AD1848 device busy??\n");
		वापस err;
	पूर्ण
	अगर (acard->wss->hardware != WSS_HW_CMI8330) अणु
		snd_prपूर्णांकk(KERN_ERR PFX "AD1848 not found during probe\n");
		वापस -ENODEV;
	पूर्ण

	अगर ((err = snd_sbdsp_create(card, sbport[dev],
				    sbirq[dev],
				    snd_sb16dsp_पूर्णांकerrupt,
				    sbdma8[dev],
				    sbdma16[dev],
				    SB_HW_AUTO, &acard->sb)) < 0) अणु
		snd_prपूर्णांकk(KERN_ERR PFX "SB16 device busy??\n");
		वापस err;
	पूर्ण
	अगर (acard->sb->hardware != SB_HW_16) अणु
		snd_prपूर्णांकk(KERN_ERR PFX "SB16 not found during probe\n");
		वापस err;
	पूर्ण

	snd_wss_out(acard->wss, CS4231_MISC_INFO, 0x40); /* चयन on MODE2 */
	क्रम (i = CMI8330_RMUX3D; i <= CMI8330_CDINGAIN; i++)
		snd_wss_out(acard->wss, i,
			    snd_cmi8330_image[i - CMI8330_RMUX3D]);

	अगर ((err = snd_cmi8330_mixer(card, acard)) < 0) अणु
		snd_prपूर्णांकk(KERN_ERR PFX "failed to create mixers\n");
		वापस err;
	पूर्ण

	अगर ((err = snd_cmi8330_pcm(card, acard)) < 0) अणु
		snd_prपूर्णांकk(KERN_ERR PFX "failed to create pcms\n");
		वापस err;
	पूर्ण
	अगर (fmport[dev] != SNDRV_AUTO_PORT) अणु
		अगर (snd_opl3_create(card,
				    fmport[dev], fmport[dev] + 2,
				    OPL3_HW_AUTO, 0, &opl3) < 0) अणु
			snd_prपूर्णांकk(KERN_ERR PFX
				   "no OPL device at 0x%lx-0x%lx ?\n",
				   fmport[dev], fmport[dev] + 2);
		पूर्ण अन्यथा अणु
			err = snd_opl3_hwdep_new(opl3, 0, 1, शून्य);
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण

	अगर (mpuport[dev] != SNDRV_AUTO_PORT) अणु
		अगर (snd_mpu401_uart_new(card, 0, MPU401_HW_MPU401,
					mpuport[dev], 0, mpuirq[dev],
					शून्य) < 0)
			prपूर्णांकk(KERN_ERR PFX "no MPU-401 device at 0x%lx.\n",
				mpuport[dev]);
	पूर्ण

	म_नकल(card->driver, (acard->type == CMI8329) ? "CMI8329" : "CMI8330/C3D");
	म_नकल(card->लघुname, (acard->type == CMI8329) ? "C-Media CMI8329" : "C-Media CMI8330/C3D");
	प्र_लिखो(card->दीर्घname, "%s at 0x%lx, irq %d, dma %d",
		card->लघुname,
		acard->wss->port,
		wssirq[dev],
		wssdma[dev]);

	वापस snd_card_रेजिस्टर(card);
पूर्ण

अटल पूर्णांक snd_cmi8330_isa_match(काष्ठा device *pdev,
				 अचिन्हित पूर्णांक dev)
अणु
	अगर (!enable[dev] || is_isapnp_selected(dev))
		वापस 0;
	अगर (wssport[dev] == SNDRV_AUTO_PORT) अणु
		snd_prपूर्णांकk(KERN_ERR PFX "specify wssport\n");
		वापस 0;
	पूर्ण
	अगर (sbport[dev] == SNDRV_AUTO_PORT) अणु
		snd_prपूर्णांकk(KERN_ERR PFX "specify sbport\n");
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक snd_cmi8330_isa_probe(काष्ठा device *pdev,
				 अचिन्हित पूर्णांक dev)
अणु
	काष्ठा snd_card *card;
	पूर्णांक err;

	err = snd_cmi8330_card_new(pdev, dev, &card);
	अगर (err < 0)
		वापस err;
	अगर ((err = snd_cmi8330_probe(card, dev)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	dev_set_drvdata(pdev, card);
	वापस 0;
पूर्ण

अटल व्योम snd_cmi8330_isa_हटाओ(काष्ठा device *devptr,
				  अचिन्हित पूर्णांक dev)
अणु
	snd_card_मुक्त(dev_get_drvdata(devptr));
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक snd_cmi8330_isa_suspend(काष्ठा device *dev, अचिन्हित पूर्णांक n,
				   pm_message_t state)
अणु
	वापस snd_cmi8330_suspend(dev_get_drvdata(dev));
पूर्ण

अटल पूर्णांक snd_cmi8330_isa_resume(काष्ठा device *dev, अचिन्हित पूर्णांक n)
अणु
	वापस snd_cmi8330_resume(dev_get_drvdata(dev));
पूर्ण
#पूर्ण_अगर

#घोषणा DEV_NAME	"cmi8330"

अटल काष्ठा isa_driver snd_cmi8330_driver = अणु
	.match		= snd_cmi8330_isa_match,
	.probe		= snd_cmi8330_isa_probe,
	.हटाओ		= snd_cmi8330_isa_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= snd_cmi8330_isa_suspend,
	.resume		= snd_cmi8330_isa_resume,
#पूर्ण_अगर
	.driver		= अणु
		.name	= DEV_NAME
	पूर्ण,
पूर्ण;


#अगर_घोषित CONFIG_PNP
अटल पूर्णांक snd_cmi8330_pnp_detect(काष्ठा pnp_card_link *pcard,
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
			       
	res = snd_cmi8330_card_new(&pcard->card->dev, dev, &card);
	अगर (res < 0)
		वापस res;
	अगर ((res = snd_cmi8330_pnp(dev, card->निजी_data, pcard, pid)) < 0) अणु
		snd_prपूर्णांकk(KERN_ERR PFX "PnP detection failed\n");
		snd_card_मुक्त(card);
		वापस res;
	पूर्ण
	अगर ((res = snd_cmi8330_probe(card, dev)) < 0) अणु
		snd_card_मुक्त(card);
		वापस res;
	पूर्ण
	pnp_set_card_drvdata(pcard, card);
	dev++;
	वापस 0;
पूर्ण

अटल व्योम snd_cmi8330_pnp_हटाओ(काष्ठा pnp_card_link *pcard)
अणु
	snd_card_मुक्त(pnp_get_card_drvdata(pcard));
	pnp_set_card_drvdata(pcard, शून्य);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक snd_cmi8330_pnp_suspend(काष्ठा pnp_card_link *pcard, pm_message_t state)
अणु
	वापस snd_cmi8330_suspend(pnp_get_card_drvdata(pcard));
पूर्ण

अटल पूर्णांक snd_cmi8330_pnp_resume(काष्ठा pnp_card_link *pcard)
अणु
	वापस snd_cmi8330_resume(pnp_get_card_drvdata(pcard));
पूर्ण
#पूर्ण_अगर

अटल काष्ठा pnp_card_driver cmi8330_pnpc_driver = अणु
	.flags = PNP_DRIVER_RES_DISABLE,
	.name = "cmi8330",
	.id_table = snd_cmi8330_pnpids,
	.probe = snd_cmi8330_pnp_detect,
	.हटाओ = snd_cmi8330_pnp_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= snd_cmi8330_pnp_suspend,
	.resume		= snd_cmi8330_pnp_resume,
#पूर्ण_अगर
पूर्ण;
#पूर्ण_अगर /* CONFIG_PNP */

अटल पूर्णांक __init alsa_card_cmi8330_init(व्योम)
अणु
	पूर्णांक err;

	err = isa_रेजिस्टर_driver(&snd_cmi8330_driver, SNDRV_CARDS);
#अगर_घोषित CONFIG_PNP
	अगर (!err)
		isa_रेजिस्टरed = 1;

	err = pnp_रेजिस्टर_card_driver(&cmi8330_pnpc_driver);
	अगर (!err)
		pnp_रेजिस्टरed = 1;

	अगर (isa_रेजिस्टरed)
		err = 0;
#पूर्ण_अगर
	वापस err;
पूर्ण

अटल व्योम __निकास alsa_card_cmi8330_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_PNP
	अगर (pnp_रेजिस्टरed)
		pnp_unरेजिस्टर_card_driver(&cmi8330_pnpc_driver);

	अगर (isa_रेजिस्टरed)
#पूर्ण_अगर
		isa_unरेजिस्टर_driver(&snd_cmi8330_driver);
पूर्ण

module_init(alsa_card_cmi8330_init)
module_निकास(alsa_card_cmi8330_निकास)
