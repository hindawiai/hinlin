<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *  Routines क्रम control of CS4235/4236B/4237B/4238B/4239 chips
 *
 *  Note:
 *     -----
 *
 *  Bugs:
 *     -----
 */

/*
 *  Indirect control रेजिस्टरs (CS4236B+)
 * 
 *  C0
 *     D8: WSS reset (all chips)
 *
 *  C1 (all chips except CS4236)
 *     D7-D5: version 
 *     D4-D0: chip id
 *             11101 - CS4235
 *             01011 - CS4236B
 *             01000 - CS4237B
 *             01001 - CS4238B
 *             11110 - CS4239
 *
 *  C2
 *     D7-D4: 3D Space (CS4235,CS4237B,CS4238B,CS4239)
 *     D3-D0: 3D Center (CS4237B); 3D Volume (CS4238B)
 * 
 *  C3
 *     D7: 3D Enable (CS4237B)
 *     D6: 3D Mono Enable (CS4237B)
 *     D5: 3D Serial Output (CS4237B,CS4238B)
 *     D4: 3D Enable (CS4235,CS4238B,CS4239)
 *
 *  C4
 *     D7: consumer serial port enable (CS4237B,CS4238B)
 *     D6: channels status block reset (CS4237B,CS4238B)
 *     D5: user bit in sub-frame of digital audio data (CS4237B,CS4238B)
 *     D4: validity bit in sub-frame of digital audio data (CS4237B,CS4238B)
 * 
 *  C5  lower channel status (digital serial data description) (CS4237B,CS4238B)
 *     D7-D6: first two bits of category code
 *     D5: lock
 *     D4-D3: pre-emphasis (0 = none, 1 = 50/15us)
 *     D2: copy/copyright (0 = copy inhibited)
 *     D1: 0 = digital audio / 1 = non-digital audio
 *     
 *  C6  upper channel status (digital serial data description) (CS4237B,CS4238B)
 *     D7-D6: sample frequency (0 = 44.1kHz)
 *     D5: generation status (0 = no indication, 1 = original/commercially precaptureed data)
 *     D4-D0: category code (upper bits)
 *
 *  C7  reserved (must ग_लिखो 0)
 *
 *  C8  wavetable control
 *     D7: volume control पूर्णांकerrupt enable (CS4235,CS4239)
 *     D6: hardware volume control क्रमmat (CS4235,CS4239)
 *     D3: wavetable serial port enable (all chips)
 *     D2: DSP serial port चयन (all chips)
 *     D1: disable MCLK (all chips)
 *     D0: क्रमce BRESET low (all chips)
 *
 */

#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/समय.स>
#समावेश <linux/रुको.h>
#समावेश <sound/core.h>
#समावेश <sound/wss.h>
#समावेश <sound/asoundef.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

/*
 *
 */

अटल स्थिर अचिन्हित अक्षर snd_cs4236_ext_map[18] = अणु
	/* CS4236_LEFT_LINE */		0xff,
	/* CS4236_RIGHT_LINE */		0xff,
	/* CS4236_LEFT_MIC */		0xdf,
	/* CS4236_RIGHT_MIC */		0xdf,
	/* CS4236_LEFT_MIX_CTRL */	0xe0 | 0x18,
	/* CS4236_RIGHT_MIX_CTRL */	0xe0,
	/* CS4236_LEFT_FM */		0xbf,
	/* CS4236_RIGHT_FM */		0xbf,
	/* CS4236_LEFT_DSP */		0xbf,
	/* CS4236_RIGHT_DSP */		0xbf,
	/* CS4236_RIGHT_LOOPBACK */	0xbf,
	/* CS4236_DAC_MUTE */		0xe0,
	/* CS4236_ADC_RATE */		0x01,	/* 48kHz */
	/* CS4236_DAC_RATE */		0x01,	/* 48kHz */
	/* CS4236_LEFT_MASTER */	0xbf,
	/* CS4236_RIGHT_MASTER */	0xbf,
	/* CS4236_LEFT_WAVE */		0xbf,
	/* CS4236_RIGHT_WAVE */		0xbf
पूर्ण;

/*
 *
 */

अटल व्योम snd_cs4236_ctrl_out(काष्ठा snd_wss *chip,
				अचिन्हित अक्षर reg, अचिन्हित अक्षर val)
अणु
	outb(reg, chip->cport + 3);
	outb(chip->cimage[reg] = val, chip->cport + 4);
पूर्ण

अटल अचिन्हित अक्षर snd_cs4236_ctrl_in(काष्ठा snd_wss *chip, अचिन्हित अक्षर reg)
अणु
	outb(reg, chip->cport + 3);
	वापस inb(chip->cport + 4);
पूर्ण

/*
 *  PCM
 */

#घोषणा CLOCKS 8

अटल स्थिर काष्ठा snd_ratnum घड़ीs[CLOCKS] = अणु
	अणु .num = 16934400, .den_min = 353, .den_max = 353, .den_step = 1 पूर्ण,
	अणु .num = 16934400, .den_min = 529, .den_max = 529, .den_step = 1 पूर्ण,
	अणु .num = 16934400, .den_min = 617, .den_max = 617, .den_step = 1 पूर्ण,
	अणु .num = 16934400, .den_min = 1058, .den_max = 1058, .den_step = 1 पूर्ण,
	अणु .num = 16934400, .den_min = 1764, .den_max = 1764, .den_step = 1 पूर्ण,
	अणु .num = 16934400, .den_min = 2117, .den_max = 2117, .den_step = 1 पूर्ण,
	अणु .num = 16934400, .den_min = 2558, .den_max = 2558, .den_step = 1 पूर्ण,
	अणु .num = 16934400/16, .den_min = 21, .den_max = 192, .den_step = 1 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_ratnums hw_स्थिरraपूर्णांकs_घड़ीs = अणु
	.nrats = CLOCKS,
	.rats = घड़ीs,
पूर्ण;

अटल पूर्णांक snd_cs4236_xrate(काष्ठा snd_pcm_runसमय *runसमय)
अणु
	वापस snd_pcm_hw_स्थिरraपूर्णांक_ratnums(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
					     &hw_स्थिरraपूर्णांकs_घड़ीs);
पूर्ण

अटल अचिन्हित अक्षर भागisor_to_rate_रेजिस्टर(अचिन्हित पूर्णांक भागisor)
अणु
	चयन (भागisor) अणु
	हाल 353:	वापस 1;
	हाल 529:	वापस 2;
	हाल 617:	वापस 3;
	हाल 1058:	वापस 4;
	हाल 1764:	वापस 5;
	हाल 2117:	वापस 6;
	हाल 2558:	वापस 7;
	शेष:
		अगर (भागisor < 21 || भागisor > 192) अणु
			snd_BUG();
			वापस 192;
		पूर्ण
		वापस भागisor;
	पूर्ण
पूर्ण

अटल व्योम snd_cs4236_playback_क्रमmat(काष्ठा snd_wss *chip,
				       काष्ठा snd_pcm_hw_params *params,
				       अचिन्हित अक्षर pdfr)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर rate = भागisor_to_rate_रेजिस्टर(params->rate_den);
	
	spin_lock_irqsave(&chip->reg_lock, flags);
	/* set fast playback क्रमmat change and clean playback FIFO */
	snd_wss_out(chip, CS4231_ALT_FEATURE_1,
		    chip->image[CS4231_ALT_FEATURE_1] | 0x10);
	snd_wss_out(chip, CS4231_PLAYBK_FORMAT, pdfr & 0xf0);
	snd_wss_out(chip, CS4231_ALT_FEATURE_1,
		    chip->image[CS4231_ALT_FEATURE_1] & ~0x10);
	snd_cs4236_ext_out(chip, CS4236_DAC_RATE, rate);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
पूर्ण

अटल व्योम snd_cs4236_capture_क्रमmat(काष्ठा snd_wss *chip,
				      काष्ठा snd_pcm_hw_params *params,
				      अचिन्हित अक्षर cdfr)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर rate = भागisor_to_rate_रेजिस्टर(params->rate_den);
	
	spin_lock_irqsave(&chip->reg_lock, flags);
	/* set fast capture क्रमmat change and clean capture FIFO */
	snd_wss_out(chip, CS4231_ALT_FEATURE_1,
		    chip->image[CS4231_ALT_FEATURE_1] | 0x20);
	snd_wss_out(chip, CS4231_REC_FORMAT, cdfr & 0xf0);
	snd_wss_out(chip, CS4231_ALT_FEATURE_1,
		    chip->image[CS4231_ALT_FEATURE_1] & ~0x20);
	snd_cs4236_ext_out(chip, CS4236_ADC_RATE, rate);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
पूर्ण

#अगर_घोषित CONFIG_PM

अटल व्योम snd_cs4236_suspend(काष्ठा snd_wss *chip)
अणु
	पूर्णांक reg;
	अचिन्हित दीर्घ flags;
	
	spin_lock_irqsave(&chip->reg_lock, flags);
	क्रम (reg = 0; reg < 32; reg++)
		chip->image[reg] = snd_wss_in(chip, reg);
	क्रम (reg = 0; reg < 18; reg++)
		chip->eimage[reg] = snd_cs4236_ext_in(chip, CS4236_I23VAL(reg));
	क्रम (reg = 2; reg < 9; reg++)
		chip->cimage[reg] = snd_cs4236_ctrl_in(chip, reg);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
पूर्ण

अटल व्योम snd_cs4236_resume(काष्ठा snd_wss *chip)
अणु
	पूर्णांक reg;
	अचिन्हित दीर्घ flags;
	
	snd_wss_mce_up(chip);
	spin_lock_irqsave(&chip->reg_lock, flags);
	क्रम (reg = 0; reg < 32; reg++) अणु
		चयन (reg) अणु
		हाल CS4236_EXT_REG:
		हाल CS4231_VERSION:
		हाल 27:	/* why? CS4235 - master left */
		हाल 29:	/* why? CS4235 - master right */
			अवरोध;
		शेष:
			snd_wss_out(chip, reg, chip->image[reg]);
			अवरोध;
		पूर्ण
	पूर्ण
	क्रम (reg = 0; reg < 18; reg++)
		snd_cs4236_ext_out(chip, CS4236_I23VAL(reg), chip->eimage[reg]);
	क्रम (reg = 2; reg < 9; reg++) अणु
		चयन (reg) अणु
		हाल 7:
			अवरोध;
		शेष:
			snd_cs4236_ctrl_out(chip, reg, chip->cimage[reg]);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	snd_wss_mce_करोwn(chip);
पूर्ण

#पूर्ण_अगर /* CONFIG_PM */
/*
 * This function करोes no fail अगर the chip is not CS4236B or compatible.
 * It just an equivalent to the snd_wss_create() then.
 */
पूर्णांक snd_cs4236_create(काष्ठा snd_card *card,
		      अचिन्हित दीर्घ port,
		      अचिन्हित दीर्घ cport,
		      पूर्णांक irq, पूर्णांक dma1, पूर्णांक dma2,
		      अचिन्हित लघु hardware,
		      अचिन्हित लघु hwshare,
		      काष्ठा snd_wss **rchip)
अणु
	काष्ठा snd_wss *chip;
	अचिन्हित अक्षर ver1, ver2;
	अचिन्हित पूर्णांक reg;
	पूर्णांक err;

	*rchip = शून्य;
	अगर (hardware == WSS_HW_DETECT)
		hardware = WSS_HW_DETECT3;

	err = snd_wss_create(card, port, cport,
			     irq, dma1, dma2, hardware, hwshare, &chip);
	अगर (err < 0)
		वापस err;

	अगर ((chip->hardware & WSS_HW_CS4236B_MASK) == 0) अणु
		snd_prपूर्णांकd("chip is not CS4236+, hardware=0x%x\n",
			   chip->hardware);
		*rchip = chip;
		वापस 0;
	पूर्ण
#अगर 0
	अणु
		पूर्णांक idx;
		क्रम (idx = 0; idx < 8; idx++)
			snd_prपूर्णांकk(KERN_DEBUG "CD%i = 0x%x\n",
				   idx, inb(chip->cport + idx));
		क्रम (idx = 0; idx < 9; idx++)
			snd_prपूर्णांकk(KERN_DEBUG "C%i = 0x%x\n",
				   idx, snd_cs4236_ctrl_in(chip, idx));
	पूर्ण
#पूर्ण_अगर
	अगर (cport < 0x100 || cport == SNDRV_AUTO_PORT) अणु
		snd_prपूर्णांकk(KERN_ERR "please, specify control port "
			   "for CS4236+ chips\n");
		snd_device_मुक्त(card, chip);
		वापस -ENODEV;
	पूर्ण
	ver1 = snd_cs4236_ctrl_in(chip, 1);
	ver2 = snd_cs4236_ext_in(chip, CS4236_VERSION);
	snd_prपूर्णांकdd("CS4236: [0x%lx] C1 (version) = 0x%x, ext = 0x%x\n",
			cport, ver1, ver2);
	अगर (ver1 != ver2) अणु
		snd_prपूर्णांकk(KERN_ERR "CS4236+ chip detected, but "
			   "control port 0x%lx is not valid\n", cport);
		snd_device_मुक्त(card, chip);
		वापस -ENODEV;
	पूर्ण
	snd_cs4236_ctrl_out(chip, 0, 0x00);
	snd_cs4236_ctrl_out(chip, 2, 0xff);
	snd_cs4236_ctrl_out(chip, 3, 0x00);
	snd_cs4236_ctrl_out(chip, 4, 0x80);
	reg = ((IEC958_AES1_CON_PCM_CODER & 3) << 6) |
	      IEC958_AES0_CON_EMPHASIS_NONE;
	snd_cs4236_ctrl_out(chip, 5, reg);
	snd_cs4236_ctrl_out(chip, 6, IEC958_AES1_CON_PCM_CODER >> 2);
	snd_cs4236_ctrl_out(chip, 7, 0x00);
	/*
	 * 0x8c क्रम C8 is valid क्रम Turtle Beach Malibu - the IEC-958
	 * output is working with this setup, other hardware should
	 * have dअगरferent संकेत paths and this value should be
	 * selectable in the future
	 */
	snd_cs4236_ctrl_out(chip, 8, 0x8c);
	chip->rate_स्थिरraपूर्णांक = snd_cs4236_xrate;
	chip->set_playback_क्रमmat = snd_cs4236_playback_क्रमmat;
	chip->set_capture_क्रमmat = snd_cs4236_capture_क्रमmat;
#अगर_घोषित CONFIG_PM
	chip->suspend = snd_cs4236_suspend;
	chip->resume = snd_cs4236_resume;
#पूर्ण_अगर

	/* initialize extended रेजिस्टरs */
	क्रम (reg = 0; reg < माप(snd_cs4236_ext_map); reg++)
		snd_cs4236_ext_out(chip, CS4236_I23VAL(reg),
				   snd_cs4236_ext_map[reg]);

	/* initialize compatible but more featured रेजिस्टरs */
	snd_wss_out(chip, CS4231_LEFT_INPUT, 0x40);
	snd_wss_out(chip, CS4231_RIGHT_INPUT, 0x40);
	snd_wss_out(chip, CS4231_AUX1_LEFT_INPUT, 0xff);
	snd_wss_out(chip, CS4231_AUX1_RIGHT_INPUT, 0xff);
	snd_wss_out(chip, CS4231_AUX2_LEFT_INPUT, 0xdf);
	snd_wss_out(chip, CS4231_AUX2_RIGHT_INPUT, 0xdf);
	snd_wss_out(chip, CS4231_RIGHT_LINE_IN, 0xff);
	snd_wss_out(chip, CS4231_LEFT_LINE_IN, 0xff);
	snd_wss_out(chip, CS4231_RIGHT_LINE_IN, 0xff);
	चयन (chip->hardware) अणु
	हाल WSS_HW_CS4235:
	हाल WSS_HW_CS4239:
		snd_wss_out(chip, CS4235_LEFT_MASTER, 0xff);
		snd_wss_out(chip, CS4235_RIGHT_MASTER, 0xff);
		अवरोध;
	पूर्ण

	*rchip = chip;
	वापस 0;
पूर्ण

पूर्णांक snd_cs4236_pcm(काष्ठा snd_wss *chip, पूर्णांक device)
अणु
	पूर्णांक err;
	
	err = snd_wss_pcm(chip, device);
	अगर (err < 0)
		वापस err;
	chip->pcm->info_flags &= ~SNDRV_PCM_INFO_JOINT_DUPLEX;
	वापस 0;
पूर्ण

/*
 *  MIXER
 */

#घोषणा CS4236_SINGLE(xname, xindex, reg, shअगरt, mask, invert) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .info = snd_cs4236_info_single, \
  .get = snd_cs4236_get_single, .put = snd_cs4236_put_single, \
  .निजी_value = reg | (shअगरt << 8) | (mask << 16) | (invert << 24) पूर्ण

#घोषणा CS4236_SINGLE_TLV(xname, xindex, reg, shअगरt, mask, invert, xtlv) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .access = SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_TLV_READ, \
  .info = snd_cs4236_info_single, \
  .get = snd_cs4236_get_single, .put = snd_cs4236_put_single, \
  .निजी_value = reg | (shअगरt << 8) | (mask << 16) | (invert << 24), \
  .tlv = अणु .p = (xtlv) पूर्ण पूर्ण

अटल पूर्णांक snd_cs4236_info_single(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;

	uinfo->type = mask == 1 ? SNDRV_CTL_ELEM_TYPE_BOOLEAN : SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = mask;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4236_get_single(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_wss *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 24) & 0xff;
	
	spin_lock_irqsave(&chip->reg_lock, flags);
	ucontrol->value.पूर्णांकeger.value[0] = (chip->eimage[CS4236_REG(reg)] >> shअगरt) & mask;
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	अगर (invert)
		ucontrol->value.पूर्णांकeger.value[0] = mask - ucontrol->value.पूर्णांकeger.value[0];
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4236_put_single(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_wss *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 24) & 0xff;
	पूर्णांक change;
	अचिन्हित लघु val;
	
	val = (ucontrol->value.पूर्णांकeger.value[0] & mask);
	अगर (invert)
		val = mask - val;
	val <<= shअगरt;
	spin_lock_irqsave(&chip->reg_lock, flags);
	val = (chip->eimage[CS4236_REG(reg)] & ~(mask << shअगरt)) | val;
	change = val != chip->eimage[CS4236_REG(reg)];
	snd_cs4236_ext_out(chip, reg, val);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस change;
पूर्ण

#घोषणा CS4236_SINGLEC(xname, xindex, reg, shअगरt, mask, invert) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .info = snd_cs4236_info_single, \
  .get = snd_cs4236_get_singlec, .put = snd_cs4236_put_singlec, \
  .निजी_value = reg | (shअगरt << 8) | (mask << 16) | (invert << 24) पूर्ण

अटल पूर्णांक snd_cs4236_get_singlec(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_wss *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 24) & 0xff;
	
	spin_lock_irqsave(&chip->reg_lock, flags);
	ucontrol->value.पूर्णांकeger.value[0] = (chip->cimage[reg] >> shअगरt) & mask;
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	अगर (invert)
		ucontrol->value.पूर्णांकeger.value[0] = mask - ucontrol->value.पूर्णांकeger.value[0];
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4236_put_singlec(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_wss *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 24) & 0xff;
	पूर्णांक change;
	अचिन्हित लघु val;
	
	val = (ucontrol->value.पूर्णांकeger.value[0] & mask);
	अगर (invert)
		val = mask - val;
	val <<= shअगरt;
	spin_lock_irqsave(&chip->reg_lock, flags);
	val = (chip->cimage[reg] & ~(mask << shअगरt)) | val;
	change = val != chip->cimage[reg];
	snd_cs4236_ctrl_out(chip, reg, val);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस change;
पूर्ण

#घोषणा CS4236_DOUBLE(xname, xindex, left_reg, right_reg, shअगरt_left, shअगरt_right, mask, invert) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .info = snd_cs4236_info_द्विगुन, \
  .get = snd_cs4236_get_द्विगुन, .put = snd_cs4236_put_द्विगुन, \
  .निजी_value = left_reg | (right_reg << 8) | (shअगरt_left << 16) | (shअगरt_right << 19) | (mask << 24) | (invert << 22) पूर्ण

#घोषणा CS4236_DOUBLE_TLV(xname, xindex, left_reg, right_reg, shअगरt_left, \
			  shअगरt_right, mask, invert, xtlv) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .access = SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_TLV_READ, \
  .info = snd_cs4236_info_द्विगुन, \
  .get = snd_cs4236_get_द्विगुन, .put = snd_cs4236_put_द्विगुन, \
  .निजी_value = left_reg | (right_reg << 8) | (shअगरt_left << 16) | \
		   (shअगरt_right << 19) | (mask << 24) | (invert << 22), \
  .tlv = अणु .p = (xtlv) पूर्ण पूर्ण

अटल पूर्णांक snd_cs4236_info_द्विगुन(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक mask = (kcontrol->निजी_value >> 24) & 0xff;

	uinfo->type = mask == 1 ? SNDRV_CTL_ELEM_TYPE_BOOLEAN : SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = mask;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4236_get_द्विगुन(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_wss *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक left_reg = kcontrol->निजी_value & 0xff;
	पूर्णांक right_reg = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक shअगरt_left = (kcontrol->निजी_value >> 16) & 0x07;
	पूर्णांक shअगरt_right = (kcontrol->निजी_value >> 19) & 0x07;
	पूर्णांक mask = (kcontrol->निजी_value >> 24) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 22) & 1;
	
	spin_lock_irqsave(&chip->reg_lock, flags);
	ucontrol->value.पूर्णांकeger.value[0] = (chip->eimage[CS4236_REG(left_reg)] >> shअगरt_left) & mask;
	ucontrol->value.पूर्णांकeger.value[1] = (chip->eimage[CS4236_REG(right_reg)] >> shअगरt_right) & mask;
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	अगर (invert) अणु
		ucontrol->value.पूर्णांकeger.value[0] = mask - ucontrol->value.पूर्णांकeger.value[0];
		ucontrol->value.पूर्णांकeger.value[1] = mask - ucontrol->value.पूर्णांकeger.value[1];
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4236_put_द्विगुन(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_wss *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक left_reg = kcontrol->निजी_value & 0xff;
	पूर्णांक right_reg = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक shअगरt_left = (kcontrol->निजी_value >> 16) & 0x07;
	पूर्णांक shअगरt_right = (kcontrol->निजी_value >> 19) & 0x07;
	पूर्णांक mask = (kcontrol->निजी_value >> 24) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 22) & 1;
	पूर्णांक change;
	अचिन्हित लघु val1, val2;
	
	val1 = ucontrol->value.पूर्णांकeger.value[0] & mask;
	val2 = ucontrol->value.पूर्णांकeger.value[1] & mask;
	अगर (invert) अणु
		val1 = mask - val1;
		val2 = mask - val2;
	पूर्ण
	val1 <<= shअगरt_left;
	val2 <<= shअगरt_right;
	spin_lock_irqsave(&chip->reg_lock, flags);
	अगर (left_reg != right_reg) अणु
		val1 = (chip->eimage[CS4236_REG(left_reg)] & ~(mask << shअगरt_left)) | val1;
		val2 = (chip->eimage[CS4236_REG(right_reg)] & ~(mask << shअगरt_right)) | val2;
		change = val1 != chip->eimage[CS4236_REG(left_reg)] || val2 != chip->eimage[CS4236_REG(right_reg)];
		snd_cs4236_ext_out(chip, left_reg, val1);
		snd_cs4236_ext_out(chip, right_reg, val2);
	पूर्ण अन्यथा अणु
		val1 = (chip->eimage[CS4236_REG(left_reg)] & ~((mask << shअगरt_left) | (mask << shअगरt_right))) | val1 | val2;
		change = val1 != chip->eimage[CS4236_REG(left_reg)];
		snd_cs4236_ext_out(chip, left_reg, val1);
	पूर्ण
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस change;
पूर्ण

#घोषणा CS4236_DOUBLE1(xname, xindex, left_reg, right_reg, shअगरt_left, \
			shअगरt_right, mask, invert) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .info = snd_cs4236_info_द्विगुन, \
  .get = snd_cs4236_get_द्विगुन1, .put = snd_cs4236_put_द्विगुन1, \
  .निजी_value = left_reg | (right_reg << 8) | (shअगरt_left << 16) | (shअगरt_right << 19) | (mask << 24) | (invert << 22) पूर्ण

#घोषणा CS4236_DOUBLE1_TLV(xname, xindex, left_reg, right_reg, shअगरt_left, \
			   shअगरt_right, mask, invert, xtlv) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .access = SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_TLV_READ, \
  .info = snd_cs4236_info_द्विगुन, \
  .get = snd_cs4236_get_द्विगुन1, .put = snd_cs4236_put_द्विगुन1, \
  .निजी_value = left_reg | (right_reg << 8) | (shअगरt_left << 16) | \
		   (shअगरt_right << 19) | (mask << 24) | (invert << 22), \
  .tlv = अणु .p = (xtlv) पूर्ण पूर्ण

अटल पूर्णांक snd_cs4236_get_द्विगुन1(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_wss *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक left_reg = kcontrol->निजी_value & 0xff;
	पूर्णांक right_reg = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक shअगरt_left = (kcontrol->निजी_value >> 16) & 0x07;
	पूर्णांक shअगरt_right = (kcontrol->निजी_value >> 19) & 0x07;
	पूर्णांक mask = (kcontrol->निजी_value >> 24) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 22) & 1;
	
	spin_lock_irqsave(&chip->reg_lock, flags);
	ucontrol->value.पूर्णांकeger.value[0] = (chip->image[left_reg] >> shअगरt_left) & mask;
	ucontrol->value.पूर्णांकeger.value[1] = (chip->eimage[CS4236_REG(right_reg)] >> shअगरt_right) & mask;
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	अगर (invert) अणु
		ucontrol->value.पूर्णांकeger.value[0] = mask - ucontrol->value.पूर्णांकeger.value[0];
		ucontrol->value.पूर्णांकeger.value[1] = mask - ucontrol->value.पूर्णांकeger.value[1];
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4236_put_द्विगुन1(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_wss *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक left_reg = kcontrol->निजी_value & 0xff;
	पूर्णांक right_reg = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक shअगरt_left = (kcontrol->निजी_value >> 16) & 0x07;
	पूर्णांक shअगरt_right = (kcontrol->निजी_value >> 19) & 0x07;
	पूर्णांक mask = (kcontrol->निजी_value >> 24) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 22) & 1;
	पूर्णांक change;
	अचिन्हित लघु val1, val2;
	
	val1 = ucontrol->value.पूर्णांकeger.value[0] & mask;
	val2 = ucontrol->value.पूर्णांकeger.value[1] & mask;
	अगर (invert) अणु
		val1 = mask - val1;
		val2 = mask - val2;
	पूर्ण
	val1 <<= shअगरt_left;
	val2 <<= shअगरt_right;
	spin_lock_irqsave(&chip->reg_lock, flags);
	val1 = (chip->image[left_reg] & ~(mask << shअगरt_left)) | val1;
	val2 = (chip->eimage[CS4236_REG(right_reg)] & ~(mask << shअगरt_right)) | val2;
	change = val1 != chip->image[left_reg] || val2 != chip->eimage[CS4236_REG(right_reg)];
	snd_wss_out(chip, left_reg, val1);
	snd_cs4236_ext_out(chip, right_reg, val2);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस change;
पूर्ण

#घोषणा CS4236_MASTER_DIGITAL(xname, xindex, xtlv) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .access = SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_TLV_READ, \
  .info = snd_cs4236_info_द्विगुन, \
  .get = snd_cs4236_get_master_digital, .put = snd_cs4236_put_master_digital, \
  .निजी_value = 71 << 24, \
  .tlv = अणु .p = (xtlv) पूर्ण पूर्ण

अटल अंतरभूत पूर्णांक snd_cs4236_mixer_master_digital_invert_volume(पूर्णांक vol)
अणु
	वापस (vol < 64) ? 63 - vol : 64 + (71 - vol);
पूर्ण

अटल पूर्णांक snd_cs4236_get_master_digital(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_wss *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	
	spin_lock_irqsave(&chip->reg_lock, flags);
	ucontrol->value.पूर्णांकeger.value[0] = snd_cs4236_mixer_master_digital_invert_volume(chip->eimage[CS4236_REG(CS4236_LEFT_MASTER)] & 0x7f);
	ucontrol->value.पूर्णांकeger.value[1] = snd_cs4236_mixer_master_digital_invert_volume(chip->eimage[CS4236_REG(CS4236_RIGHT_MASTER)] & 0x7f);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4236_put_master_digital(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_wss *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक change;
	अचिन्हित लघु val1, val2;
	
	val1 = snd_cs4236_mixer_master_digital_invert_volume(ucontrol->value.पूर्णांकeger.value[0] & 0x7f);
	val2 = snd_cs4236_mixer_master_digital_invert_volume(ucontrol->value.पूर्णांकeger.value[1] & 0x7f);
	spin_lock_irqsave(&chip->reg_lock, flags);
	val1 = (chip->eimage[CS4236_REG(CS4236_LEFT_MASTER)] & ~0x7f) | val1;
	val2 = (chip->eimage[CS4236_REG(CS4236_RIGHT_MASTER)] & ~0x7f) | val2;
	change = val1 != chip->eimage[CS4236_REG(CS4236_LEFT_MASTER)] || val2 != chip->eimage[CS4236_REG(CS4236_RIGHT_MASTER)];
	snd_cs4236_ext_out(chip, CS4236_LEFT_MASTER, val1);
	snd_cs4236_ext_out(chip, CS4236_RIGHT_MASTER, val2);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस change;
पूर्ण

#घोषणा CS4235_OUTPUT_ACCU(xname, xindex, xtlv) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .access = SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_TLV_READ, \
  .info = snd_cs4236_info_द्विगुन, \
  .get = snd_cs4235_get_output_accu, .put = snd_cs4235_put_output_accu, \
  .निजी_value = 3 << 24, \
  .tlv = अणु .p = (xtlv) पूर्ण पूर्ण

अटल अंतरभूत पूर्णांक snd_cs4235_mixer_output_accu_get_volume(पूर्णांक vol)
अणु
	चयन ((vol >> 5) & 3) अणु
	हाल 0: वापस 1;
	हाल 1: वापस 3;
	हाल 2: वापस 2;
	हाल 3: वापस 0;
 	पूर्ण
	वापस 3;
पूर्ण

अटल अंतरभूत पूर्णांक snd_cs4235_mixer_output_accu_set_volume(पूर्णांक vol)
अणु
	चयन (vol & 3) अणु
	हाल 0: वापस 3 << 5;
	हाल 1: वापस 0 << 5;
	हाल 2: वापस 2 << 5;
	हाल 3: वापस 1 << 5;
	पूर्ण
	वापस 1 << 5;
पूर्ण

अटल पूर्णांक snd_cs4235_get_output_accu(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_wss *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	
	spin_lock_irqsave(&chip->reg_lock, flags);
	ucontrol->value.पूर्णांकeger.value[0] = snd_cs4235_mixer_output_accu_get_volume(chip->image[CS4235_LEFT_MASTER]);
	ucontrol->value.पूर्णांकeger.value[1] = snd_cs4235_mixer_output_accu_get_volume(chip->image[CS4235_RIGHT_MASTER]);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4235_put_output_accu(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_wss *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक change;
	अचिन्हित लघु val1, val2;
	
	val1 = snd_cs4235_mixer_output_accu_set_volume(ucontrol->value.पूर्णांकeger.value[0]);
	val2 = snd_cs4235_mixer_output_accu_set_volume(ucontrol->value.पूर्णांकeger.value[1]);
	spin_lock_irqsave(&chip->reg_lock, flags);
	val1 = (chip->image[CS4235_LEFT_MASTER] & ~(3 << 5)) | val1;
	val2 = (chip->image[CS4235_RIGHT_MASTER] & ~(3 << 5)) | val2;
	change = val1 != chip->image[CS4235_LEFT_MASTER] || val2 != chip->image[CS4235_RIGHT_MASTER];
	snd_wss_out(chip, CS4235_LEFT_MASTER, val1);
	snd_wss_out(chip, CS4235_RIGHT_MASTER, val2);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस change;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_7bit, -9450, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_6bit, -9450, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_6bit_12db_max, -8250, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_5bit_12db_max, -3450, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_5bit_22db_max, -2400, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_4bit, -4500, 300, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_2bit, -1800, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_rec_gain, 0, 150, 0);

अटल स्थिर काष्ठा snd_kcontrol_new snd_cs4236_controls[] = अणु

CS4236_DOUBLE("Master Digital Playback Switch", 0,
		CS4236_LEFT_MASTER, CS4236_RIGHT_MASTER, 7, 7, 1, 1),
CS4236_DOUBLE("Master Digital Capture Switch", 0,
		CS4236_DAC_MUTE, CS4236_DAC_MUTE, 7, 6, 1, 1),
CS4236_MASTER_DIGITAL("Master Digital Volume", 0, db_scale_7bit),

CS4236_DOUBLE_TLV("Capture Boost Volume", 0,
		  CS4236_LEFT_MIX_CTRL, CS4236_RIGHT_MIX_CTRL, 5, 5, 3, 1,
		  db_scale_2bit),

WSS_DOUBLE("PCM Playback Switch", 0,
		CS4231_LEFT_OUTPUT, CS4231_RIGHT_OUTPUT, 7, 7, 1, 1),
WSS_DOUBLE_TLV("PCM Playback Volume", 0,
		CS4231_LEFT_OUTPUT, CS4231_RIGHT_OUTPUT, 0, 0, 63, 1,
		db_scale_6bit),

CS4236_DOUBLE("DSP Playback Switch", 0,
		CS4236_LEFT_DSP, CS4236_RIGHT_DSP, 7, 7, 1, 1),
CS4236_DOUBLE_TLV("DSP Playback Volume", 0,
		  CS4236_LEFT_DSP, CS4236_RIGHT_DSP, 0, 0, 63, 1,
		  db_scale_6bit),

CS4236_DOUBLE("FM Playback Switch", 0,
		CS4236_LEFT_FM, CS4236_RIGHT_FM, 7, 7, 1, 1),
CS4236_DOUBLE_TLV("FM Playback Volume", 0,
		  CS4236_LEFT_FM, CS4236_RIGHT_FM, 0, 0, 63, 1,
		  db_scale_6bit),

CS4236_DOUBLE("Wavetable Playback Switch", 0,
		CS4236_LEFT_WAVE, CS4236_RIGHT_WAVE, 7, 7, 1, 1),
CS4236_DOUBLE_TLV("Wavetable Playback Volume", 0,
		  CS4236_LEFT_WAVE, CS4236_RIGHT_WAVE, 0, 0, 63, 1,
		  db_scale_6bit_12db_max),

WSS_DOUBLE("Synth Playback Switch", 0,
		CS4231_LEFT_LINE_IN, CS4231_RIGHT_LINE_IN, 7, 7, 1, 1),
WSS_DOUBLE_TLV("Synth Volume", 0,
		CS4231_LEFT_LINE_IN, CS4231_RIGHT_LINE_IN, 0, 0, 31, 1,
		db_scale_5bit_12db_max),
WSS_DOUBLE("Synth Capture Switch", 0,
		CS4231_LEFT_LINE_IN, CS4231_RIGHT_LINE_IN, 6, 6, 1, 1),
WSS_DOUBLE("Synth Capture Bypass", 0,
		CS4231_LEFT_LINE_IN, CS4231_RIGHT_LINE_IN, 5, 5, 1, 1),

CS4236_DOUBLE("Mic Playback Switch", 0,
		CS4236_LEFT_MIC, CS4236_RIGHT_MIC, 6, 6, 1, 1),
CS4236_DOUBLE("Mic Capture Switch", 0,
		CS4236_LEFT_MIC, CS4236_RIGHT_MIC, 7, 7, 1, 1),
CS4236_DOUBLE_TLV("Mic Volume", 0, CS4236_LEFT_MIC, CS4236_RIGHT_MIC,
		  0, 0, 31, 1, db_scale_5bit_22db_max),
CS4236_DOUBLE("Mic Playback Boost (+20dB)", 0,
		CS4236_LEFT_MIC, CS4236_RIGHT_MIC, 5, 5, 1, 0),

WSS_DOUBLE("Line Playback Switch", 0,
		CS4231_AUX1_LEFT_INPUT, CS4231_AUX1_RIGHT_INPUT, 7, 7, 1, 1),
WSS_DOUBLE_TLV("Line Volume", 0,
		CS4231_AUX1_LEFT_INPUT, CS4231_AUX1_RIGHT_INPUT, 0, 0, 31, 1,
		db_scale_5bit_12db_max),
WSS_DOUBLE("Line Capture Switch", 0,
		CS4231_AUX1_LEFT_INPUT, CS4231_AUX1_RIGHT_INPUT, 6, 6, 1, 1),
WSS_DOUBLE("Line Capture Bypass", 0,
		CS4231_AUX1_LEFT_INPUT, CS4231_AUX1_RIGHT_INPUT, 5, 5, 1, 1),

WSS_DOUBLE("CD Playback Switch", 0,
		CS4231_AUX2_LEFT_INPUT, CS4231_AUX2_RIGHT_INPUT, 7, 7, 1, 1),
WSS_DOUBLE_TLV("CD Volume", 0,
		CS4231_AUX2_LEFT_INPUT, CS4231_AUX2_RIGHT_INPUT, 0, 0, 31, 1,
		db_scale_5bit_12db_max),
WSS_DOUBLE("CD Capture Switch", 0,
		CS4231_AUX2_LEFT_INPUT, CS4231_AUX2_RIGHT_INPUT, 6, 6, 1, 1),

CS4236_DOUBLE1("Mono Output Playback Switch", 0,
		CS4231_MONO_CTRL, CS4236_RIGHT_MIX_CTRL, 6, 7, 1, 1),
CS4236_DOUBLE1("Beep Playback Switch", 0,
		CS4231_MONO_CTRL, CS4236_LEFT_MIX_CTRL, 7, 7, 1, 1),
WSS_SINGLE_TLV("Beep Playback Volume", 0, CS4231_MONO_CTRL, 0, 15, 1,
		db_scale_4bit),
WSS_SINGLE("Beep Bypass Playback Switch", 0, CS4231_MONO_CTRL, 5, 1, 0),

WSS_DOUBLE_TLV("Capture Volume", 0, CS4231_LEFT_INPUT, CS4231_RIGHT_INPUT,
		0, 0, 15, 0, db_scale_rec_gain),
WSS_DOUBLE("Analog Loopback Capture Switch", 0,
		CS4231_LEFT_INPUT, CS4231_RIGHT_INPUT, 7, 7, 1, 0),

WSS_SINGLE("Loopback Digital Playback Switch", 0, CS4231_LOOPBACK, 0, 1, 0),
CS4236_DOUBLE1_TLV("Loopback Digital Playback Volume", 0,
		   CS4231_LOOPBACK, CS4236_RIGHT_LOOPBACK, 2, 0, 63, 1,
		   db_scale_6bit),
पूर्ण;

अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_5bit_6db_max, -5600, 200, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_2bit_16db_max, -2400, 800, 0);

अटल स्थिर काष्ठा snd_kcontrol_new snd_cs4235_controls[] = अणु

WSS_DOUBLE("Master Playback Switch", 0,
		CS4235_LEFT_MASTER, CS4235_RIGHT_MASTER, 7, 7, 1, 1),
WSS_DOUBLE_TLV("Master Playback Volume", 0,
		CS4235_LEFT_MASTER, CS4235_RIGHT_MASTER, 0, 0, 31, 1,
		db_scale_5bit_6db_max),

CS4235_OUTPUT_ACCU("Playback Volume", 0, db_scale_2bit_16db_max),

WSS_DOUBLE("Synth Playback Switch", 1,
		CS4231_LEFT_LINE_IN, CS4231_RIGHT_LINE_IN, 7, 7, 1, 1),
WSS_DOUBLE("Synth Capture Switch", 1,
		CS4231_LEFT_LINE_IN, CS4231_RIGHT_LINE_IN, 6, 6, 1, 1),
WSS_DOUBLE_TLV("Synth Volume", 1,
		CS4231_LEFT_LINE_IN, CS4231_RIGHT_LINE_IN, 0, 0, 31, 1,
		db_scale_5bit_12db_max),

CS4236_DOUBLE_TLV("Capture Volume", 0,
		  CS4236_LEFT_MIX_CTRL, CS4236_RIGHT_MIX_CTRL, 5, 5, 3, 1,
		  db_scale_2bit),

WSS_DOUBLE("PCM Playback Switch", 0,
		CS4231_LEFT_OUTPUT, CS4231_RIGHT_OUTPUT, 7, 7, 1, 1),
WSS_DOUBLE("PCM Capture Switch", 0,
		CS4236_DAC_MUTE, CS4236_DAC_MUTE, 7, 6, 1, 1),
WSS_DOUBLE_TLV("PCM Volume", 0,
		CS4231_LEFT_OUTPUT, CS4231_RIGHT_OUTPUT, 0, 0, 63, 1,
		db_scale_6bit),

CS4236_DOUBLE("DSP Switch", 0, CS4236_LEFT_DSP, CS4236_RIGHT_DSP, 7, 7, 1, 1),

CS4236_DOUBLE("FM Switch", 0, CS4236_LEFT_FM, CS4236_RIGHT_FM, 7, 7, 1, 1),

CS4236_DOUBLE("Wavetable Switch", 0,
		CS4236_LEFT_WAVE, CS4236_RIGHT_WAVE, 7, 7, 1, 1),

CS4236_DOUBLE("Mic Capture Switch", 0,
		CS4236_LEFT_MIC, CS4236_RIGHT_MIC, 7, 7, 1, 1),
CS4236_DOUBLE("Mic Playback Switch", 0,
		CS4236_LEFT_MIC, CS4236_RIGHT_MIC, 6, 6, 1, 1),
CS4236_SINGLE_TLV("Mic Volume", 0, CS4236_LEFT_MIC, 0, 31, 1,
		  db_scale_5bit_22db_max),
CS4236_SINGLE("Mic Boost (+20dB)", 0, CS4236_LEFT_MIC, 5, 1, 0),

WSS_DOUBLE("Line Playback Switch", 0,
		CS4231_AUX1_LEFT_INPUT, CS4231_AUX1_RIGHT_INPUT, 7, 7, 1, 1),
WSS_DOUBLE("Line Capture Switch", 0,
		CS4231_AUX1_LEFT_INPUT, CS4231_AUX1_RIGHT_INPUT, 6, 6, 1, 1),
WSS_DOUBLE_TLV("Line Volume", 0,
		CS4231_AUX1_LEFT_INPUT, CS4231_AUX1_RIGHT_INPUT, 0, 0, 31, 1,
		db_scale_5bit_12db_max),

WSS_DOUBLE("CD Playback Switch", 1,
		CS4231_AUX2_LEFT_INPUT, CS4231_AUX2_RIGHT_INPUT, 7, 7, 1, 1),
WSS_DOUBLE("CD Capture Switch", 1,
		CS4231_AUX2_LEFT_INPUT, CS4231_AUX2_RIGHT_INPUT, 6, 6, 1, 1),
WSS_DOUBLE_TLV("CD Volume", 1,
		CS4231_AUX2_LEFT_INPUT, CS4231_AUX2_RIGHT_INPUT, 0, 0, 31, 1,
		db_scale_5bit_12db_max),

CS4236_DOUBLE1("Beep Playback Switch", 0,
		CS4231_MONO_CTRL, CS4236_LEFT_MIX_CTRL, 7, 7, 1, 1),
WSS_SINGLE("Beep Playback Volume", 0, CS4231_MONO_CTRL, 0, 15, 1),

WSS_DOUBLE("Analog Loopback Switch", 0,
		CS4231_LEFT_INPUT, CS4231_RIGHT_INPUT, 7, 7, 1, 0),
पूर्ण;

#घोषणा CS4236_IEC958_ENABLE(xname, xindex) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .info = snd_cs4236_info_single, \
  .get = snd_cs4236_get_iec958_चयन, .put = snd_cs4236_put_iec958_चयन, \
  .निजी_value = 1 << 16 पूर्ण

अटल पूर्णांक snd_cs4236_get_iec958_चयन(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_wss *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	
	spin_lock_irqsave(&chip->reg_lock, flags);
	ucontrol->value.पूर्णांकeger.value[0] = chip->image[CS4231_ALT_FEATURE_1] & 0x02 ? 1 : 0;
#अगर 0
	prपूर्णांकk(KERN_DEBUG "get valid: ALT = 0x%x, C3 = 0x%x, C4 = 0x%x, "
	       "C5 = 0x%x, C6 = 0x%x, C8 = 0x%x\n",
			snd_wss_in(chip, CS4231_ALT_FEATURE_1),
			snd_cs4236_ctrl_in(chip, 3),
			snd_cs4236_ctrl_in(chip, 4),
			snd_cs4236_ctrl_in(chip, 5),
			snd_cs4236_ctrl_in(chip, 6),
			snd_cs4236_ctrl_in(chip, 8));
#पूर्ण_अगर
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4236_put_iec958_चयन(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_wss *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक change;
	अचिन्हित लघु enable, val;
	
	enable = ucontrol->value.पूर्णांकeger.value[0] & 1;

	mutex_lock(&chip->mce_mutex);
	snd_wss_mce_up(chip);
	spin_lock_irqsave(&chip->reg_lock, flags);
	val = (chip->image[CS4231_ALT_FEATURE_1] & ~0x0e) | (0<<2) | (enable << 1);
	change = val != chip->image[CS4231_ALT_FEATURE_1];
	snd_wss_out(chip, CS4231_ALT_FEATURE_1, val);
	val = snd_cs4236_ctrl_in(chip, 4) | 0xc0;
	snd_cs4236_ctrl_out(chip, 4, val);
	udelay(100);
	val &= ~0x40;
	snd_cs4236_ctrl_out(chip, 4, val);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	snd_wss_mce_करोwn(chip);
	mutex_unlock(&chip->mce_mutex);

#अगर 0
	prपूर्णांकk(KERN_DEBUG "set valid: ALT = 0x%x, C3 = 0x%x, C4 = 0x%x, "
	       "C5 = 0x%x, C6 = 0x%x, C8 = 0x%x\n",
			snd_wss_in(chip, CS4231_ALT_FEATURE_1),
			snd_cs4236_ctrl_in(chip, 3),
			snd_cs4236_ctrl_in(chip, 4),
			snd_cs4236_ctrl_in(chip, 5),
			snd_cs4236_ctrl_in(chip, 6),
			snd_cs4236_ctrl_in(chip, 8));
#पूर्ण_अगर
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_cs4236_iec958_controls[] = अणु
CS4236_IEC958_ENABLE("IEC958 Output Enable", 0),
CS4236_SINGLEC("IEC958 Output Validity", 0, 4, 4, 1, 0),
CS4236_SINGLEC("IEC958 Output User", 0, 4, 5, 1, 0),
CS4236_SINGLEC("IEC958 Output CSBR", 0, 4, 6, 1, 0),
CS4236_SINGLEC("IEC958 Output Channel Status Low", 0, 5, 1, 127, 0),
CS4236_SINGLEC("IEC958 Output Channel Status High", 0, 6, 0, 255, 0)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_cs4236_3d_controls_cs4235[] = अणु
CS4236_SINGLEC("3D Control - Switch", 0, 3, 4, 1, 0),
CS4236_SINGLEC("3D Control - Space", 0, 2, 4, 15, 1)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_cs4236_3d_controls_cs4237[] = अणु
CS4236_SINGLEC("3D Control - Switch", 0, 3, 7, 1, 0),
CS4236_SINGLEC("3D Control - Space", 0, 2, 4, 15, 1),
CS4236_SINGLEC("3D Control - Center", 0, 2, 0, 15, 1),
CS4236_SINGLEC("3D Control - Mono", 0, 3, 6, 1, 0),
CS4236_SINGLEC("3D Control - IEC958", 0, 3, 5, 1, 0)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_cs4236_3d_controls_cs4238[] = अणु
CS4236_SINGLEC("3D Control - Switch", 0, 3, 4, 1, 0),
CS4236_SINGLEC("3D Control - Space", 0, 2, 4, 15, 1),
CS4236_SINGLEC("3D Control - Volume", 0, 2, 0, 15, 1),
CS4236_SINGLEC("3D Control - IEC958", 0, 3, 5, 1, 0)
पूर्ण;

पूर्णांक snd_cs4236_mixer(काष्ठा snd_wss *chip)
अणु
	काष्ठा snd_card *card;
	अचिन्हित पूर्णांक idx, count;
	पूर्णांक err;
	स्थिर काष्ठा snd_kcontrol_new *kcontrol;

	अगर (snd_BUG_ON(!chip || !chip->card))
		वापस -EINVAL;
	card = chip->card;
	म_नकल(card->mixername, snd_wss_chip_id(chip));

	अगर (chip->hardware == WSS_HW_CS4235 ||
	    chip->hardware == WSS_HW_CS4239) अणु
		क्रम (idx = 0; idx < ARRAY_SIZE(snd_cs4235_controls); idx++) अणु
			अगर ((err = snd_ctl_add(card, snd_ctl_new1(&snd_cs4235_controls[idx], chip))) < 0)
				वापस err;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (idx = 0; idx < ARRAY_SIZE(snd_cs4236_controls); idx++) अणु
			अगर ((err = snd_ctl_add(card, snd_ctl_new1(&snd_cs4236_controls[idx], chip))) < 0)
				वापस err;
		पूर्ण
	पूर्ण
	चयन (chip->hardware) अणु
	हाल WSS_HW_CS4235:
	हाल WSS_HW_CS4239:
		count = ARRAY_SIZE(snd_cs4236_3d_controls_cs4235);
		kcontrol = snd_cs4236_3d_controls_cs4235;
		अवरोध;
	हाल WSS_HW_CS4237B:
		count = ARRAY_SIZE(snd_cs4236_3d_controls_cs4237);
		kcontrol = snd_cs4236_3d_controls_cs4237;
		अवरोध;
	हाल WSS_HW_CS4238B:
		count = ARRAY_SIZE(snd_cs4236_3d_controls_cs4238);
		kcontrol = snd_cs4236_3d_controls_cs4238;
		अवरोध;
	शेष:
		count = 0;
		kcontrol = शून्य;
	पूर्ण
	क्रम (idx = 0; idx < count; idx++, kcontrol++) अणु
		अगर ((err = snd_ctl_add(card, snd_ctl_new1(kcontrol, chip))) < 0)
			वापस err;
	पूर्ण
	अगर (chip->hardware == WSS_HW_CS4237B ||
	    chip->hardware == WSS_HW_CS4238B) अणु
		क्रम (idx = 0; idx < ARRAY_SIZE(snd_cs4236_iec958_controls); idx++) अणु
			अगर ((err = snd_ctl_add(card, snd_ctl_new1(&snd_cs4236_iec958_controls[idx], chip))) < 0)
				वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
