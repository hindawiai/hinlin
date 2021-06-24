<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम generic ESS AudioDrive ES18xx soundcards
 *  Copyright (c) by Christian Fischbach <fishbach@pool.inक्रमmatik.rwth-aachen.de>
 *  Copyright (c) by Abramo Bagnara <abramo@alsa-project.org>
 */
/* GENERAL NOTES:
 *
 * BUGS:
 * - There are pops (we can't delay in trigger function, cause midlevel 
 *   often need to trigger करोwn and then up very quickly).
 *   Any ideas?
 * - Support क्रम 16 bit DMA seems to be broken. I've no hardware to tune it.
 */

/*
 * ES1868  NOTES:
 * - The chip has one half duplex pcm (with very limited full duplex support).
 *
 * - Duplex stereophonic sound is impossible.
 * - Record and playback must share the same frequency rate.
 *
 * - The driver use dma2 क्रम playback and dma1 क्रम capture.
 */

/*
 * ES1869 NOTES:
 *
 * - there are a first full duplex pcm and a second playback only pcm
 *   (incompatible with first pcm capture)
 * 
 * - there is support क्रम the capture volume and ESS Spatializer 3D effect.
 *
 * - contrarily to some pages in DS_1869.PDF the rates can be set
 *   independently.
 *
 * - Zoom Video is implemented by sharing the FM DAC, thus the user can
 *   have either FM playback or Video playback but not both simultaneously.
 *   The Video Playback Switch mixer control toggles this choice.
 *
 * BUGS:
 *
 * - There is a major trouble I noted:
 *
 *   using both channel क्रम playback stereo 16 bit samples at 44100 Hz
 *   the second pcm (Audio1) DMA slows करोwn irregularly and sound is garbled.
 *   
 *   The same happens using Audio1 क्रम captureing.
 *
 *   The Winकरोws driver करोes not suffer of this (although it use Audio1
 *   only क्रम captureing). I'm unable to discover why.
 *
 */

/*
 * ES1879 NOTES:
 * - When Zoom Video is enabled (reg 0x71 bit 6 toggled on) the PCM playback
 *   seems to be effected (speaker_test plays a lower frequency). Can't find
 *   anything in the datasheet to account क्रम this, so a Video Playback Switch
 *   control has been included to allow ZV to be enabled only when necessary.
 *   Then again on at least one test प्रणाली the 0x71 bit 6 enable bit is not 
 *   needed क्रम ZV, so maybe the datasheet is entirely wrong here.
 */
 
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/isa.h>
#समावेश <linux/pnp.h>
#समावेश <linux/isapnp.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/dma.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/mpu401.h>
#समावेश <sound/opl3.h>
#घोषणा SNDRV_LEGACY_FIND_FREE_IRQ
#घोषणा SNDRV_LEGACY_FIND_FREE_DMA
#समावेश <sound/initval.h>

#घोषणा PFX "es18xx: "

काष्ठा snd_es18xx अणु
	अचिन्हित दीर्घ port;		/* port of ESS chip */
	अचिन्हित दीर्घ ctrl_port;	/* Control port of ESS chip */
	काष्ठा resource *res_port;
	काष्ठा resource *res_mpu_port;
	काष्ठा resource *res_ctrl_port;
	पूर्णांक irq;			/* IRQ number of ESS chip */
	पूर्णांक dma1;			/* DMA1 */
	पूर्णांक dma2;			/* DMA2 */
	अचिन्हित लघु version;		/* version of ESS chip */
	पूर्णांक caps;			/* Chip capabilities */
	अचिन्हित लघु audio2_vol;	/* volume level of audio2 */

	अचिन्हित लघु active;		/* active channel mask */
	अचिन्हित पूर्णांक dma1_shअगरt;
	अचिन्हित पूर्णांक dma2_shअगरt;

	काष्ठा snd_pcm *pcm;
	काष्ठा snd_pcm_substream *playback_a_substream;
	काष्ठा snd_pcm_substream *capture_a_substream;
	काष्ठा snd_pcm_substream *playback_b_substream;

	काष्ठा snd_rawmidi *rmidi;

	काष्ठा snd_kcontrol *hw_volume;
	काष्ठा snd_kcontrol *hw_चयन;
	काष्ठा snd_kcontrol *master_volume;
	काष्ठा snd_kcontrol *master_चयन;

	spinlock_t reg_lock;
	spinlock_t mixer_lock;
#अगर_घोषित CONFIG_PM
	अचिन्हित अक्षर pm_reg;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PNP
	काष्ठा pnp_dev *dev;
	काष्ठा pnp_dev *devc;
#पूर्ण_अगर
पूर्ण;

#घोषणा AUDIO1_IRQ	0x01
#घोषणा AUDIO2_IRQ	0x02
#घोषणा HWV_IRQ		0x04
#घोषणा MPU_IRQ		0x08

#घोषणा ES18XX_PCM2	0x0001	/* Has two useable PCM */
#घोषणा ES18XX_SPATIALIZER 0x0002	/* Has 3D Spatializer */
#घोषणा ES18XX_RECMIX	0x0004	/* Has record mixer */
#घोषणा ES18XX_DUPLEX_MONO 0x0008	/* Has mono duplex only */
#घोषणा ES18XX_DUPLEX_SAME 0x0010	/* Playback and record must share the same rate */
#घोषणा ES18XX_NEW_RATE	0x0020	/* More precise rate setting */
#घोषणा ES18XX_AUXB	0x0040	/* AuxB mixer control */
#घोषणा ES18XX_HWV	0x0080	/* Has separate hardware volume mixer controls*/
#घोषणा ES18XX_MONO	0x0100	/* Mono_in mixer control */
#घोषणा ES18XX_I2S	0x0200	/* I2S mixer control */
#घोषणा ES18XX_MUTEREC	0x0400	/* Record source can be muted */
#घोषणा ES18XX_CONTROL	0x0800	/* Has control ports */
#घोषणा ES18XX_GPO_2BIT	0x1000	/* GPO0,1 controlled by PM port */

/* Power Management */
#घोषणा ES18XX_PM	0x07
#घोषणा ES18XX_PM_GPO0	0x01
#घोषणा ES18XX_PM_GPO1	0x02
#घोषणा ES18XX_PM_PDR	0x04
#घोषणा ES18XX_PM_ANA	0x08
#घोषणा ES18XX_PM_FM	0x020
#घोषणा ES18XX_PM_SUS	0x080

/* Lowlevel */

#घोषणा DAC1 0x01
#घोषणा ADC1 0x02
#घोषणा DAC2 0x04
#घोषणा MILLISECOND 10000

अटल पूर्णांक snd_es18xx_dsp_command(काष्ठा snd_es18xx *chip, अचिन्हित अक्षर val)
अणु
        पूर्णांक i;

        क्रम(i = MILLISECOND; i; i--)
                अगर ((inb(chip->port + 0x0C) & 0x80) == 0) अणु
                        outb(val, chip->port + 0x0C);
                        वापस 0;
                पूर्ण
	snd_prपूर्णांकk(KERN_ERR "dsp_command: timeout (0x%x)\n", val);
        वापस -EINVAL;
पूर्ण

अटल पूर्णांक snd_es18xx_dsp_get_byte(काष्ठा snd_es18xx *chip)
अणु
        पूर्णांक i;

        क्रम(i = MILLISECOND/10; i; i--)
                अगर (inb(chip->port + 0x0C) & 0x40)
                        वापस inb(chip->port + 0x0A);
	snd_prपूर्णांकk(KERN_ERR "dsp_get_byte failed: 0x%lx = 0x%x!!!\n",
		   chip->port + 0x0A, inb(chip->port + 0x0A));
        वापस -ENODEV;
पूर्ण

#अघोषित REG_DEBUG

अटल पूर्णांक snd_es18xx_ग_लिखो(काष्ठा snd_es18xx *chip,
			    अचिन्हित अक्षर reg, अचिन्हित अक्षर data)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;
	
        spin_lock_irqsave(&chip->reg_lock, flags);
	ret = snd_es18xx_dsp_command(chip, reg);
	अगर (ret < 0)
		जाओ end;
        ret = snd_es18xx_dsp_command(chip, data);
 end:
        spin_unlock_irqrestore(&chip->reg_lock, flags);
#अगर_घोषित REG_DEBUG
	snd_prपूर्णांकk(KERN_DEBUG "Reg %02x set to %02x\n", reg, data);
#पूर्ण_अगर
	वापस ret;
पूर्ण

अटल पूर्णांक snd_es18xx_पढ़ो(काष्ठा snd_es18xx *chip, अचिन्हित अक्षर reg)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret, data;
        spin_lock_irqsave(&chip->reg_lock, flags);
	ret = snd_es18xx_dsp_command(chip, 0xC0);
	अगर (ret < 0)
		जाओ end;
        ret = snd_es18xx_dsp_command(chip, reg);
	अगर (ret < 0)
		जाओ end;
	data = snd_es18xx_dsp_get_byte(chip);
	ret = data;
#अगर_घोषित REG_DEBUG
	snd_prपूर्णांकk(KERN_DEBUG "Reg %02x now is %02x (%d)\n", reg, data, ret);
#पूर्ण_अगर
 end:
        spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस ret;
पूर्ण

/* Return old value */
अटल पूर्णांक snd_es18xx_bits(काष्ठा snd_es18xx *chip, अचिन्हित अक्षर reg,
			   अचिन्हित अक्षर mask, अचिन्हित अक्षर val)
अणु
        पूर्णांक ret;
	अचिन्हित अक्षर old, new, oval;
	अचिन्हित दीर्घ flags;
        spin_lock_irqsave(&chip->reg_lock, flags);
        ret = snd_es18xx_dsp_command(chip, 0xC0);
	अगर (ret < 0)
		जाओ end;
        ret = snd_es18xx_dsp_command(chip, reg);
	अगर (ret < 0)
		जाओ end;
	ret = snd_es18xx_dsp_get_byte(chip);
	अगर (ret < 0) अणु
		जाओ end;
	पूर्ण
	old = ret;
	oval = old & mask;
	अगर (val != oval) अणु
		ret = snd_es18xx_dsp_command(chip, reg);
		अगर (ret < 0)
			जाओ end;
		new = (old & ~mask) | (val & mask);
		ret = snd_es18xx_dsp_command(chip, new);
		अगर (ret < 0)
			जाओ end;
#अगर_घोषित REG_DEBUG
		snd_prपूर्णांकk(KERN_DEBUG "Reg %02x was %02x, set to %02x (%d)\n",
			   reg, old, new, ret);
#पूर्ण_अगर
	पूर्ण
	ret = oval;
 end:
        spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम snd_es18xx_mixer_ग_लिखो(काष्ठा snd_es18xx *chip,
			    अचिन्हित अक्षर reg, अचिन्हित अक्षर data)
अणु
	अचिन्हित दीर्घ flags;
        spin_lock_irqsave(&chip->mixer_lock, flags);
        outb(reg, chip->port + 0x04);
        outb(data, chip->port + 0x05);
        spin_unlock_irqrestore(&chip->mixer_lock, flags);
#अगर_घोषित REG_DEBUG
	snd_prपूर्णांकk(KERN_DEBUG "Mixer reg %02x set to %02x\n", reg, data);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक snd_es18xx_mixer_पढ़ो(काष्ठा snd_es18xx *chip, अचिन्हित अक्षर reg)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक data;
        spin_lock_irqsave(&chip->mixer_lock, flags);
        outb(reg, chip->port + 0x04);
	data = inb(chip->port + 0x05);
        spin_unlock_irqrestore(&chip->mixer_lock, flags);
#अगर_घोषित REG_DEBUG
	snd_prपूर्णांकk(KERN_DEBUG "Mixer reg %02x now is %02x\n", reg, data);
#पूर्ण_अगर
        वापस data;
पूर्ण

/* Return old value */
अटल अंतरभूत पूर्णांक snd_es18xx_mixer_bits(काष्ठा snd_es18xx *chip, अचिन्हित अक्षर reg,
					अचिन्हित अक्षर mask, अचिन्हित अक्षर val)
अणु
	अचिन्हित अक्षर old, new, oval;
	अचिन्हित दीर्घ flags;
        spin_lock_irqsave(&chip->mixer_lock, flags);
        outb(reg, chip->port + 0x04);
	old = inb(chip->port + 0x05);
	oval = old & mask;
	अगर (val != oval) अणु
		new = (old & ~mask) | (val & mask);
		outb(new, chip->port + 0x05);
#अगर_घोषित REG_DEBUG
		snd_prपूर्णांकk(KERN_DEBUG "Mixer reg %02x was %02x, set to %02x\n",
			   reg, old, new);
#पूर्ण_अगर
	पूर्ण
        spin_unlock_irqrestore(&chip->mixer_lock, flags);
	वापस oval;
पूर्ण

अटल अंतरभूत पूर्णांक snd_es18xx_mixer_writable(काष्ठा snd_es18xx *chip, अचिन्हित अक्षर reg,
					    अचिन्हित अक्षर mask)
अणु
	पूर्णांक old, expected, new;
	अचिन्हित दीर्घ flags;
        spin_lock_irqsave(&chip->mixer_lock, flags);
        outb(reg, chip->port + 0x04);
	old = inb(chip->port + 0x05);
	expected = old ^ mask;
	outb(expected, chip->port + 0x05);
	new = inb(chip->port + 0x05);
        spin_unlock_irqrestore(&chip->mixer_lock, flags);
#अगर_घोषित REG_DEBUG
	snd_prपूर्णांकk(KERN_DEBUG "Mixer reg %02x was %02x, set to %02x, now is %02x\n",
		   reg, old, expected, new);
#पूर्ण_अगर
	वापस expected == new;
पूर्ण


अटल पूर्णांक snd_es18xx_reset(काष्ठा snd_es18xx *chip)
अणु
	पूर्णांक i;
        outb(0x03, chip->port + 0x06);
        inb(chip->port + 0x06);
        outb(0x00, chip->port + 0x06);
        क्रम(i = 0; i < MILLISECOND && !(inb(chip->port + 0x0E) & 0x80); i++);
        अगर (inb(chip->port + 0x0A) != 0xAA)
                वापस -1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es18xx_reset_fअगरo(काष्ठा snd_es18xx *chip)
अणु
        outb(0x02, chip->port + 0x06);
        inb(chip->port + 0x06);
        outb(0x00, chip->port + 0x06);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_ratnum new_घड़ीs[2] = अणु
	अणु
		.num = 793800,
		.den_min = 1,
		.den_max = 128,
		.den_step = 1,
	पूर्ण,
	अणु
		.num = 768000,
		.den_min = 1,
		.den_max = 128,
		.den_step = 1,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_ratnums new_hw_स्थिरraपूर्णांकs_घड़ीs = अणु
	.nrats = 2,
	.rats = new_घड़ीs,
पूर्ण;

अटल स्थिर काष्ठा snd_ratnum old_घड़ीs[2] = अणु
	अणु
		.num = 795444,
		.den_min = 1,
		.den_max = 128,
		.den_step = 1,
	पूर्ण,
	अणु
		.num = 397722,
		.den_min = 1,
		.den_max = 128,
		.den_step = 1,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_ratnums old_hw_स्थिरraपूर्णांकs_घड़ीs  = अणु
	.nrats = 2,
	.rats = old_घड़ीs,
पूर्ण;


अटल व्योम snd_es18xx_rate_set(काष्ठा snd_es18xx *chip, 
				काष्ठा snd_pcm_substream *substream,
				पूर्णांक mode)
अणु
	अचिन्हित पूर्णांक bits, भाग0;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अगर (chip->caps & ES18XX_NEW_RATE) अणु
		अगर (runसमय->rate_num == new_घड़ीs[0].num)
			bits = 128 - runसमय->rate_den;
		अन्यथा
			bits = 256 - runसमय->rate_den;
	पूर्ण अन्यथा अणु
		अगर (runसमय->rate_num == old_घड़ीs[0].num)
			bits = 256 - runसमय->rate_den;
		अन्यथा
			bits = 128 - runसमय->rate_den;
	पूर्ण

	/* set filter रेजिस्टर */
	भाग0 = 256 - 7160000*20/(8*82*runसमय->rate);
		
	अगर ((chip->caps & ES18XX_PCM2) && mode == DAC2) अणु
		snd_es18xx_mixer_ग_लिखो(chip, 0x70, bits);
		/*
		 * Comment from kernel oss driver:
		 * FKS: fascinating: 0x72 करोesn't seem to work.
		 */
		snd_es18xx_ग_लिखो(chip, 0xA2, भाग0);
		snd_es18xx_mixer_ग_लिखो(chip, 0x72, भाग0);
	पूर्ण अन्यथा अणु
		snd_es18xx_ग_लिखो(chip, 0xA1, bits);
		snd_es18xx_ग_लिखो(chip, 0xA2, भाग0);
	पूर्ण
पूर्ण

अटल पूर्णांक snd_es18xx_playback_hw_params(काष्ठा snd_pcm_substream *substream,
					 काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_es18xx *chip = snd_pcm_substream_chip(substream);
	पूर्णांक shअगरt;

	shअगरt = 0;
	अगर (params_channels(hw_params) == 2)
		shअगरt++;
	अगर (snd_pcm_क्रमmat_width(params_क्रमmat(hw_params)) == 16)
		shअगरt++;

	अगर (substream->number == 0 && (chip->caps & ES18XX_PCM2)) अणु
		अगर ((chip->caps & ES18XX_DUPLEX_MONO) &&
		    (chip->capture_a_substream) &&
		    params_channels(hw_params) != 1) अणु
			_snd_pcm_hw_param_setempty(hw_params, SNDRV_PCM_HW_PARAM_CHANNELS);
			वापस -EBUSY;
		पूर्ण
		chip->dma2_shअगरt = shअगरt;
	पूर्ण अन्यथा अणु
		chip->dma1_shअगरt = shअगरt;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es18xx_playback1_prepare(काष्ठा snd_es18xx *chip,
					काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित पूर्णांक size = snd_pcm_lib_buffer_bytes(substream);
	अचिन्हित पूर्णांक count = snd_pcm_lib_period_bytes(substream);

        snd_es18xx_rate_set(chip, substream, DAC2);

        /* Transfer Count Reload */
        count = 0x10000 - count;
        snd_es18xx_mixer_ग_लिखो(chip, 0x74, count & 0xff);
        snd_es18xx_mixer_ग_लिखो(chip, 0x76, count >> 8);

	/* Set क्रमmat */
        snd_es18xx_mixer_bits(chip, 0x7A, 0x07,
			      ((runसमय->channels == 1) ? 0x00 : 0x02) |
			      (snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 16 ? 0x01 : 0x00) |
			      (snd_pcm_क्रमmat_अचिन्हित(runसमय->क्रमmat) ? 0x00 : 0x04));

        /* Set DMA controller */
        snd_dma_program(chip->dma2, runसमय->dma_addr, size, DMA_MODE_WRITE | DMA_AUTOINIT);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_es18xx_playback1_trigger(काष्ठा snd_es18xx *chip,
					काष्ठा snd_pcm_substream *substream,
					पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		अगर (chip->active & DAC2)
			वापस 0;
		chip->active |= DAC2;
                /* Start DMA */
		अगर (chip->dma2 >= 4)
			snd_es18xx_mixer_ग_लिखो(chip, 0x78, 0xb3);
		अन्यथा
			snd_es18xx_mixer_ग_लिखो(chip, 0x78, 0x93);
#अगर_घोषित AVOID_POPS
		/* Aव्योम pops */
		mdelay(100);
		अगर (chip->caps & ES18XX_PCM2)
			/* Restore Audio 2 volume */
			snd_es18xx_mixer_ग_लिखो(chip, 0x7C, chip->audio2_vol);
		अन्यथा
			/* Enable PCM output */
			snd_es18xx_dsp_command(chip, 0xD1);
#पूर्ण_अगर
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		अगर (!(chip->active & DAC2))
			वापस 0;
		chip->active &= ~DAC2;
                /* Stop DMA */
                snd_es18xx_mixer_ग_लिखो(chip, 0x78, 0x00);
#अगर_घोषित AVOID_POPS
		mdelay(25);
		अगर (chip->caps & ES18XX_PCM2)
			/* Set Audio 2 volume to 0 */
			snd_es18xx_mixer_ग_लिखो(chip, 0x7C, 0);
		अन्यथा
			/* Disable PCM output */
			snd_es18xx_dsp_command(chip, 0xD3);
#पूर्ण_अगर
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_es18xx_capture_hw_params(काष्ठा snd_pcm_substream *substream,
					काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_es18xx *chip = snd_pcm_substream_chip(substream);
	पूर्णांक shअगरt;

	shअगरt = 0;
	अगर ((chip->caps & ES18XX_DUPLEX_MONO) &&
	    chip->playback_a_substream &&
	    params_channels(hw_params) != 1) अणु
		_snd_pcm_hw_param_setempty(hw_params, SNDRV_PCM_HW_PARAM_CHANNELS);
		वापस -EBUSY;
	पूर्ण
	अगर (params_channels(hw_params) == 2)
		shअगरt++;
	अगर (snd_pcm_क्रमmat_width(params_क्रमmat(hw_params)) == 16)
		shअगरt++;
	chip->dma1_shअगरt = shअगरt;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es18xx_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
        काष्ठा snd_es18xx *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित पूर्णांक size = snd_pcm_lib_buffer_bytes(substream);
	अचिन्हित पूर्णांक count = snd_pcm_lib_period_bytes(substream);

	snd_es18xx_reset_fअगरo(chip);

        /* Set stereo/mono */
        snd_es18xx_bits(chip, 0xA8, 0x03, runसमय->channels == 1 ? 0x02 : 0x01);

        snd_es18xx_rate_set(chip, substream, ADC1);

        /* Transfer Count Reload */
	count = 0x10000 - count;
	snd_es18xx_ग_लिखो(chip, 0xA4, count & 0xff);
	snd_es18xx_ग_लिखो(chip, 0xA5, count >> 8);

#अगर_घोषित AVOID_POPS
	mdelay(100);
#पूर्ण_अगर

        /* Set क्रमmat */
        snd_es18xx_ग_लिखो(chip, 0xB7, 
                         snd_pcm_क्रमmat_अचिन्हित(runसमय->क्रमmat) ? 0x51 : 0x71);
        snd_es18xx_ग_लिखो(chip, 0xB7, 0x90 |
                         ((runसमय->channels == 1) ? 0x40 : 0x08) |
                         (snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 16 ? 0x04 : 0x00) |
                         (snd_pcm_क्रमmat_अचिन्हित(runसमय->क्रमmat) ? 0x00 : 0x20));

        /* Set DMA controller */
        snd_dma_program(chip->dma1, runसमय->dma_addr, size, DMA_MODE_READ | DMA_AUTOINIT);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_es18xx_capture_trigger(काष्ठा snd_pcm_substream *substream,
				      पूर्णांक cmd)
अणु
        काष्ठा snd_es18xx *chip = snd_pcm_substream_chip(substream);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		अगर (chip->active & ADC1)
			वापस 0;
		chip->active |= ADC1;
                /* Start DMA */
                snd_es18xx_ग_लिखो(chip, 0xB8, 0x0f);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		अगर (!(chip->active & ADC1))
			वापस 0;
		chip->active &= ~ADC1;
                /* Stop DMA */
                snd_es18xx_ग_लिखो(chip, 0xB8, 0x00);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_es18xx_playback2_prepare(काष्ठा snd_es18xx *chip,
					काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित पूर्णांक size = snd_pcm_lib_buffer_bytes(substream);
	अचिन्हित पूर्णांक count = snd_pcm_lib_period_bytes(substream);

	snd_es18xx_reset_fअगरo(chip);

        /* Set stereo/mono */
        snd_es18xx_bits(chip, 0xA8, 0x03, runसमय->channels == 1 ? 0x02 : 0x01);

        snd_es18xx_rate_set(chip, substream, DAC1);

        /* Transfer Count Reload */
	count = 0x10000 - count;
	snd_es18xx_ग_लिखो(chip, 0xA4, count & 0xff);
	snd_es18xx_ग_लिखो(chip, 0xA5, count >> 8);

        /* Set क्रमmat */
        snd_es18xx_ग_लिखो(chip, 0xB6,
                         snd_pcm_क्रमmat_अचिन्हित(runसमय->क्रमmat) ? 0x80 : 0x00);
        snd_es18xx_ग_लिखो(chip, 0xB7, 
                         snd_pcm_क्रमmat_अचिन्हित(runसमय->क्रमmat) ? 0x51 : 0x71);
        snd_es18xx_ग_लिखो(chip, 0xB7, 0x90 |
                         (runसमय->channels == 1 ? 0x40 : 0x08) |
                         (snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 16 ? 0x04 : 0x00) |
                         (snd_pcm_क्रमmat_अचिन्हित(runसमय->क्रमmat) ? 0x00 : 0x20));

        /* Set DMA controller */
        snd_dma_program(chip->dma1, runसमय->dma_addr, size, DMA_MODE_WRITE | DMA_AUTOINIT);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_es18xx_playback2_trigger(काष्ठा snd_es18xx *chip,
					काष्ठा snd_pcm_substream *substream,
					पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		अगर (chip->active & DAC1)
			वापस 0;
		chip->active |= DAC1;
                /* Start DMA */
                snd_es18xx_ग_लिखो(chip, 0xB8, 0x05);
#अगर_घोषित AVOID_POPS
		/* Aव्योम pops */
		mdelay(100);
                /* Enable Audio 1 */
                snd_es18xx_dsp_command(chip, 0xD1);
#पूर्ण_अगर
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		अगर (!(chip->active & DAC1))
			वापस 0;
		chip->active &= ~DAC1;
                /* Stop DMA */
                snd_es18xx_ग_लिखो(chip, 0xB8, 0x00);
#अगर_घोषित AVOID_POPS
		/* Aव्योम pops */
		mdelay(25);
                /* Disable Audio 1 */
                snd_es18xx_dsp_command(chip, 0xD3);
#पूर्ण_अगर
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_es18xx_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
        काष्ठा snd_es18xx *chip = snd_pcm_substream_chip(substream);
	अगर (substream->number == 0 && (chip->caps & ES18XX_PCM2))
		वापस snd_es18xx_playback1_prepare(chip, substream);
	अन्यथा
		वापस snd_es18xx_playback2_prepare(chip, substream);
पूर्ण

अटल पूर्णांक snd_es18xx_playback_trigger(काष्ठा snd_pcm_substream *substream,
				       पूर्णांक cmd)
अणु
        काष्ठा snd_es18xx *chip = snd_pcm_substream_chip(substream);
	अगर (substream->number == 0 && (chip->caps & ES18XX_PCM2))
		वापस snd_es18xx_playback1_trigger(chip, substream, cmd);
	अन्यथा
		वापस snd_es18xx_playback2_trigger(chip, substream, cmd);
पूर्ण

अटल irqवापस_t snd_es18xx_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा snd_card *card = dev_id;
	काष्ठा snd_es18xx *chip = card->निजी_data;
	अचिन्हित अक्षर status;

	अगर (chip->caps & ES18XX_CONTROL) अणु
		/* Read Interrupt status */
		status = inb(chip->ctrl_port + 6);
	पूर्ण अन्यथा अणु
		/* Read Interrupt status */
		status = snd_es18xx_mixer_पढ़ो(chip, 0x7f) >> 4;
	पूर्ण
#अगर 0
	अन्यथा अणु
		status = 0;
		अगर (inb(chip->port + 0x0C) & 0x01)
			status |= AUDIO1_IRQ;
		अगर (snd_es18xx_mixer_पढ़ो(chip, 0x7A) & 0x80)
			status |= AUDIO2_IRQ;
		अगर ((chip->caps & ES18XX_HWV) &&
		    snd_es18xx_mixer_पढ़ो(chip, 0x64) & 0x10)
			status |= HWV_IRQ;
	पूर्ण
#पूर्ण_अगर

	/* Audio 1 & Audio 2 */
        अगर (status & AUDIO2_IRQ) अणु
                अगर (chip->active & DAC2)
                	snd_pcm_period_elapsed(chip->playback_a_substream);
		/* ack पूर्णांकerrupt */
                snd_es18xx_mixer_bits(chip, 0x7A, 0x80, 0x00);
        पूर्ण
        अगर (status & AUDIO1_IRQ) अणु
                /* ok.. capture is active */
                अगर (chip->active & ADC1)
                	snd_pcm_period_elapsed(chip->capture_a_substream);
                /* ok.. playback2 is active */
                अन्यथा अगर (chip->active & DAC1)
                	snd_pcm_period_elapsed(chip->playback_b_substream);
		/* ack पूर्णांकerrupt */
		inb(chip->port + 0x0E);
        पूर्ण

	/* MPU */
	अगर ((status & MPU_IRQ) && chip->rmidi)
		snd_mpu401_uart_पूर्णांकerrupt(irq, chip->rmidi->निजी_data);

	/* Hardware volume */
	अगर (status & HWV_IRQ) अणु
		पूर्णांक split = 0;
		अगर (chip->caps & ES18XX_HWV) अणु
			split = snd_es18xx_mixer_पढ़ो(chip, 0x64) & 0x80;
			snd_ctl_notअगरy(card, SNDRV_CTL_EVENT_MASK_VALUE,
					&chip->hw_चयन->id);
			snd_ctl_notअगरy(card, SNDRV_CTL_EVENT_MASK_VALUE,
					&chip->hw_volume->id);
		पूर्ण
		अगर (!split) अणु
			snd_ctl_notअगरy(card, SNDRV_CTL_EVENT_MASK_VALUE,
					&chip->master_चयन->id);
			snd_ctl_notअगरy(card, SNDRV_CTL_EVENT_MASK_VALUE,
					&chip->master_volume->id);
		पूर्ण
		/* ack पूर्णांकerrupt */
		snd_es18xx_mixer_ग_लिखो(chip, 0x66, 0x00);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल snd_pcm_uframes_t snd_es18xx_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
        काष्ठा snd_es18xx *chip = snd_pcm_substream_chip(substream);
	अचिन्हित पूर्णांक size = snd_pcm_lib_buffer_bytes(substream);
	पूर्णांक pos;

	अगर (substream->number == 0 && (chip->caps & ES18XX_PCM2)) अणु
		अगर (!(chip->active & DAC2))
			वापस 0;
		pos = snd_dma_poपूर्णांकer(chip->dma2, size);
		वापस pos >> chip->dma2_shअगरt;
	पूर्ण अन्यथा अणु
		अगर (!(chip->active & DAC1))
			वापस 0;
		pos = snd_dma_poपूर्णांकer(chip->dma1, size);
		वापस pos >> chip->dma1_shअगरt;
	पूर्ण
पूर्ण

अटल snd_pcm_uframes_t snd_es18xx_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
        काष्ठा snd_es18xx *chip = snd_pcm_substream_chip(substream);
	अचिन्हित पूर्णांक size = snd_pcm_lib_buffer_bytes(substream);
	पूर्णांक pos;

        अगर (!(chip->active & ADC1))
                वापस 0;
	pos = snd_dma_poपूर्णांकer(chip->dma1, size);
	वापस pos >> chip->dma1_shअगरt;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware snd_es18xx_playback =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_RESUME |
				 SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =		(SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S8 | 
				 SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_U16_LE),
	.rates =		SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		4000,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	65536,
	.period_bytes_min =	64,
	.period_bytes_max =	65536,
	.periods_min =		1,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_es18xx_capture =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_RESUME |
				 SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =		(SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S8 | 
				 SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_U16_LE),
	.rates =		SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		4000,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	65536,
	.period_bytes_min =	64,
	.period_bytes_max =	65536,
	.periods_min =		1,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

अटल पूर्णांक snd_es18xx_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
        काष्ठा snd_es18xx *chip = snd_pcm_substream_chip(substream);

	अगर (substream->number == 0 && (chip->caps & ES18XX_PCM2)) अणु
		अगर ((chip->caps & ES18XX_DUPLEX_MONO) &&
		    chip->capture_a_substream && 
		    chip->capture_a_substream->runसमय->channels != 1)
			वापस -EAGAIN;
		chip->playback_a_substream = substream;
	पूर्ण अन्यथा अगर (substream->number <= 1) अणु
		अगर (chip->capture_a_substream)
			वापस -EAGAIN;
		chip->playback_b_substream = substream;
	पूर्ण अन्यथा अणु
		snd_BUG();
		वापस -EINVAL;
	पूर्ण
	substream->runसमय->hw = snd_es18xx_playback;
	snd_pcm_hw_स्थिरraपूर्णांक_ratnums(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				      (chip->caps & ES18XX_NEW_RATE) ? &new_hw_स्थिरraपूर्णांकs_घड़ीs : &old_hw_स्थिरraपूर्णांकs_घड़ीs);
        वापस 0;
पूर्ण

अटल पूर्णांक snd_es18xx_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
        काष्ठा snd_es18xx *chip = snd_pcm_substream_chip(substream);

        अगर (chip->playback_b_substream)
                वापस -EAGAIN;
	अगर ((chip->caps & ES18XX_DUPLEX_MONO) &&
	    chip->playback_a_substream &&
	    chip->playback_a_substream->runसमय->channels != 1)
		वापस -EAGAIN;
        chip->capture_a_substream = substream;
	substream->runसमय->hw = snd_es18xx_capture;
	snd_pcm_hw_स्थिरraपूर्णांक_ratnums(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				      (chip->caps & ES18XX_NEW_RATE) ? &new_hw_स्थिरraपूर्णांकs_घड़ीs : &old_hw_स्थिरraपूर्णांकs_घड़ीs);
        वापस 0;
पूर्ण

अटल पूर्णांक snd_es18xx_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
        काष्ठा snd_es18xx *chip = snd_pcm_substream_chip(substream);

	अगर (substream->number == 0 && (chip->caps & ES18XX_PCM2))
		chip->playback_a_substream = शून्य;
	अन्यथा
		chip->playback_b_substream = शून्य;
	
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es18xx_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
        काष्ठा snd_es18xx *chip = snd_pcm_substream_chip(substream);

        chip->capture_a_substream = शून्य;
        वापस 0;
पूर्ण

/*
 *  MIXER part
 */

/* Record source mux routines:
 * Depending on the chipset this mux चयनes between 4, 5, or 8 possible inमाला_दो.
 * bit table क्रम the 4/5 source mux:
 * reg 1C:
 *  b2 b1 b0   muxSource
 *   x  0  x   microphone
 *   0  1  x   CD
 *   1  1  0   line
 *   1  1  1   mixer
 * अगर it's "mixer" and it's a 5 source mux chipset then reg 7A bit 3 determines
 * either the play mixer or the capture mixer.
 *
 * "map4Source" translates from source number to reg bit pattern
 * "invMap4Source" translates from reg bit pattern to source number
 */

अटल पूर्णांक snd_es18xx_info_mux(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts5Source[5] = अणु
		"Mic", "CD", "Line", "Master", "Mix"
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर texts8Source[8] = अणु
		"Mic", "Mic Master", "CD", "AOUT",
		"Mic1", "Mix", "Line", "Master"
	पूर्ण;
	काष्ठा snd_es18xx *chip = snd_kcontrol_chip(kcontrol);

	चयन (chip->version) अणु
	हाल 0x1868:
	हाल 0x1878:
		वापस snd_ctl_क्रमागत_info(uinfo, 1, 4, texts5Source);
	हाल 0x1887:
	हाल 0x1888:
		वापस snd_ctl_क्रमागत_info(uinfo, 1, 5, texts5Source);
	हाल 0x1869: /* DS somewhat contradictory क्रम 1869: could be 5 or 8 */
	हाल 0x1879:
		वापस snd_ctl_क्रमागत_info(uinfo, 1, 8, texts8Source);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक snd_es18xx_get_mux(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	अटल स्थिर अचिन्हित अक्षर invMap4Source[8] = अणु0, 0, 1, 1, 0, 0, 2, 3पूर्ण;
	काष्ठा snd_es18xx *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक muxSource = snd_es18xx_mixer_पढ़ो(chip, 0x1c) & 0x07;
	अगर (!(chip->version == 0x1869 || chip->version == 0x1879)) अणु
		muxSource = invMap4Source[muxSource];
		अगर (muxSource==3 && 
		    (chip->version == 0x1887 || chip->version == 0x1888) &&
		    (snd_es18xx_mixer_पढ़ो(chip, 0x7a) & 0x08)
		) 
			muxSource = 4;
	पूर्ण
	ucontrol->value.क्रमागतerated.item[0] = muxSource;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es18xx_put_mux(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	अटल स्थिर अचिन्हित अक्षर map4Source[4] = अणु0, 2, 6, 7पूर्ण;
	काष्ठा snd_es18xx *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर val = ucontrol->value.क्रमागतerated.item[0];
	अचिन्हित अक्षर retVal = 0;

	चयन (chip->version) अणु
 /* 5 source chips */
	हाल 0x1887:
	हाल 0x1888:
		अगर (val > 4)
			वापस -EINVAL;
		अगर (val == 4) अणु
			retVal = snd_es18xx_mixer_bits(chip, 0x7a, 0x08, 0x08) != 0x08;
			val = 3;
		पूर्ण अन्यथा
			retVal = snd_es18xx_mixer_bits(chip, 0x7a, 0x08, 0x00) != 0x00;
		fallthrough;
 /* 4 source chips */
	हाल 0x1868:
	हाल 0x1878:
		अगर (val > 3)
			वापस -EINVAL;
		val = map4Source[val];
		अवरोध;
 /* 8 source chips */
	हाल 0x1869:
	हाल 0x1879:
		अगर (val > 7)
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस (snd_es18xx_mixer_bits(chip, 0x1c, 0x07, val) != val) || retVal;
पूर्ण

#घोषणा snd_es18xx_info_spatializer_enable	snd_ctl_boolean_mono_info

अटल पूर्णांक snd_es18xx_get_spatializer_enable(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_es18xx *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर val = snd_es18xx_mixer_पढ़ो(chip, 0x50);
	ucontrol->value.पूर्णांकeger.value[0] = !!(val & 8);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es18xx_put_spatializer_enable(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_es18xx *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर oval, nval;
	पूर्णांक change;
	nval = ucontrol->value.पूर्णांकeger.value[0] ? 0x0c : 0x04;
	oval = snd_es18xx_mixer_पढ़ो(chip, 0x50) & 0x0c;
	change = nval != oval;
	अगर (change) अणु
		snd_es18xx_mixer_ग_लिखो(chip, 0x50, nval & ~0x04);
		snd_es18xx_mixer_ग_लिखो(chip, 0x50, nval);
	पूर्ण
	वापस change;
पूर्ण

अटल पूर्णांक snd_es18xx_info_hw_volume(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 63;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es18xx_get_hw_volume(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_es18xx *chip = snd_kcontrol_chip(kcontrol);
	ucontrol->value.पूर्णांकeger.value[0] = snd_es18xx_mixer_पढ़ो(chip, 0x61) & 0x3f;
	ucontrol->value.पूर्णांकeger.value[1] = snd_es18xx_mixer_पढ़ो(chip, 0x63) & 0x3f;
	वापस 0;
पूर्ण

#घोषणा snd_es18xx_info_hw_चयन	snd_ctl_boolean_stereo_info

अटल पूर्णांक snd_es18xx_get_hw_चयन(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_es18xx *chip = snd_kcontrol_chip(kcontrol);
	ucontrol->value.पूर्णांकeger.value[0] = !(snd_es18xx_mixer_पढ़ो(chip, 0x61) & 0x40);
	ucontrol->value.पूर्णांकeger.value[1] = !(snd_es18xx_mixer_पढ़ो(chip, 0x63) & 0x40);
	वापस 0;
पूर्ण

अटल व्योम snd_es18xx_hwv_मुक्त(काष्ठा snd_kcontrol *kcontrol)
अणु
	काष्ठा snd_es18xx *chip = snd_kcontrol_chip(kcontrol);
	chip->master_volume = शून्य;
	chip->master_चयन = शून्य;
	chip->hw_volume = शून्य;
	chip->hw_चयन = शून्य;
पूर्ण

अटल पूर्णांक snd_es18xx_reg_bits(काष्ठा snd_es18xx *chip, अचिन्हित अक्षर reg,
			       अचिन्हित अक्षर mask, अचिन्हित अक्षर val)
अणु
	अगर (reg < 0xa0)
		वापस snd_es18xx_mixer_bits(chip, reg, mask, val);
	अन्यथा
		वापस snd_es18xx_bits(chip, reg, mask, val);
पूर्ण

अटल पूर्णांक snd_es18xx_reg_पढ़ो(काष्ठा snd_es18xx *chip, अचिन्हित अक्षर reg)
अणु
	अगर (reg < 0xa0)
		वापस snd_es18xx_mixer_पढ़ो(chip, reg);
	अन्यथा
		वापस snd_es18xx_पढ़ो(chip, reg);
पूर्ण

#घोषणा ES18XX_SINGLE(xname, xindex, reg, shअगरt, mask, flags) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .info = snd_es18xx_info_single, \
  .get = snd_es18xx_get_single, .put = snd_es18xx_put_single, \
  .निजी_value = reg | (shअगरt << 8) | (mask << 16) | (flags << 24) पूर्ण

#घोषणा ES18XX_FL_INVERT	(1 << 0)
#घोषणा ES18XX_FL_PMPORT	(1 << 1)

अटल पूर्णांक snd_es18xx_info_single(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;

	uinfo->type = mask == 1 ? SNDRV_CTL_ELEM_TYPE_BOOLEAN : SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = mask;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es18xx_get_single(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_es18xx *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 24) & ES18XX_FL_INVERT;
	पूर्णांक pm_port = (kcontrol->निजी_value >> 24) & ES18XX_FL_PMPORT;
	पूर्णांक val;

	अगर (pm_port)
		val = inb(chip->port + ES18XX_PM);
	अन्यथा
		val = snd_es18xx_reg_पढ़ो(chip, reg);
	ucontrol->value.पूर्णांकeger.value[0] = (val >> shअगरt) & mask;
	अगर (invert)
		ucontrol->value.पूर्णांकeger.value[0] = mask - ucontrol->value.पूर्णांकeger.value[0];
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es18xx_put_single(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_es18xx *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 24) & ES18XX_FL_INVERT;
	पूर्णांक pm_port = (kcontrol->निजी_value >> 24) & ES18XX_FL_PMPORT;
	अचिन्हित अक्षर val;
	
	val = (ucontrol->value.पूर्णांकeger.value[0] & mask);
	अगर (invert)
		val = mask - val;
	mask <<= shअगरt;
	val <<= shअगरt;
	अगर (pm_port) अणु
		अचिन्हित अक्षर cur = inb(chip->port + ES18XX_PM);

		अगर ((cur & mask) == val)
			वापस 0;
		outb((cur & ~mask) | val, chip->port + ES18XX_PM);
		वापस 1;
	पूर्ण

	वापस snd_es18xx_reg_bits(chip, reg, mask, val) != val;
पूर्ण

#घोषणा ES18XX_DOUBLE(xname, xindex, left_reg, right_reg, shअगरt_left, shअगरt_right, mask, invert) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .info = snd_es18xx_info_द्विगुन, \
  .get = snd_es18xx_get_द्विगुन, .put = snd_es18xx_put_द्विगुन, \
  .निजी_value = left_reg | (right_reg << 8) | (shअगरt_left << 16) | (shअगरt_right << 19) | (mask << 24) | (invert << 22) पूर्ण

अटल पूर्णांक snd_es18xx_info_द्विगुन(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक mask = (kcontrol->निजी_value >> 24) & 0xff;

	uinfo->type = mask == 1 ? SNDRV_CTL_ELEM_TYPE_BOOLEAN : SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = mask;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es18xx_get_द्विगुन(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_es18xx *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक left_reg = kcontrol->निजी_value & 0xff;
	पूर्णांक right_reg = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक shअगरt_left = (kcontrol->निजी_value >> 16) & 0x07;
	पूर्णांक shअगरt_right = (kcontrol->निजी_value >> 19) & 0x07;
	पूर्णांक mask = (kcontrol->निजी_value >> 24) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 22) & 1;
	अचिन्हित अक्षर left, right;
	
	left = snd_es18xx_reg_पढ़ो(chip, left_reg);
	अगर (left_reg != right_reg)
		right = snd_es18xx_reg_पढ़ो(chip, right_reg);
	अन्यथा
		right = left;
	ucontrol->value.पूर्णांकeger.value[0] = (left >> shअगरt_left) & mask;
	ucontrol->value.पूर्णांकeger.value[1] = (right >> shअगरt_right) & mask;
	अगर (invert) अणु
		ucontrol->value.पूर्णांकeger.value[0] = mask - ucontrol->value.पूर्णांकeger.value[0];
		ucontrol->value.पूर्णांकeger.value[1] = mask - ucontrol->value.पूर्णांकeger.value[1];
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es18xx_put_द्विगुन(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_es18xx *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक left_reg = kcontrol->निजी_value & 0xff;
	पूर्णांक right_reg = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक shअगरt_left = (kcontrol->निजी_value >> 16) & 0x07;
	पूर्णांक shअगरt_right = (kcontrol->निजी_value >> 19) & 0x07;
	पूर्णांक mask = (kcontrol->निजी_value >> 24) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 22) & 1;
	पूर्णांक change;
	अचिन्हित अक्षर val1, val2, mask1, mask2;
	
	val1 = ucontrol->value.पूर्णांकeger.value[0] & mask;
	val2 = ucontrol->value.पूर्णांकeger.value[1] & mask;
	अगर (invert) अणु
		val1 = mask - val1;
		val2 = mask - val2;
	पूर्ण
	val1 <<= shअगरt_left;
	val2 <<= shअगरt_right;
	mask1 = mask << shअगरt_left;
	mask2 = mask << shअगरt_right;
	अगर (left_reg != right_reg) अणु
		change = 0;
		अगर (snd_es18xx_reg_bits(chip, left_reg, mask1, val1) != val1)
			change = 1;
		अगर (snd_es18xx_reg_bits(chip, right_reg, mask2, val2) != val2)
			change = 1;
	पूर्ण अन्यथा अणु
		change = (snd_es18xx_reg_bits(chip, left_reg, mask1 | mask2, 
					      val1 | val2) != (val1 | val2));
	पूर्ण
	वापस change;
पूर्ण

/* Mixer controls
 * These arrays contain setup data क्रम mixer controls.
 * 
 * The controls that are universal to all chipsets are fully initialized
 * here.
 */
अटल स्थिर काष्ठा snd_kcontrol_new snd_es18xx_base_controls[] = अणु
ES18XX_DOUBLE("Master Playback Volume", 0, 0x60, 0x62, 0, 0, 63, 0),
ES18XX_DOUBLE("Master Playback Switch", 0, 0x60, 0x62, 6, 6, 1, 1),
ES18XX_DOUBLE("Line Playback Volume", 0, 0x3e, 0x3e, 4, 0, 15, 0),
ES18XX_DOUBLE("CD Playback Volume", 0, 0x38, 0x38, 4, 0, 15, 0),
ES18XX_DOUBLE("FM Playback Volume", 0, 0x36, 0x36, 4, 0, 15, 0),
ES18XX_DOUBLE("Mic Playback Volume", 0, 0x1a, 0x1a, 4, 0, 15, 0),
ES18XX_DOUBLE("Aux Playback Volume", 0, 0x3a, 0x3a, 4, 0, 15, 0),
ES18XX_SINGLE("Record Monitor", 0, 0xa8, 3, 1, 0),
ES18XX_DOUBLE("Capture Volume", 0, 0xb4, 0xb4, 4, 0, 15, 0),
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Capture Source",
	.info = snd_es18xx_info_mux,
	.get = snd_es18xx_get_mux,
	.put = snd_es18xx_put_mux,
पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_es18xx_recmix_controls[] = अणु
ES18XX_DOUBLE("PCM Capture Volume", 0, 0x69, 0x69, 4, 0, 15, 0),
ES18XX_DOUBLE("Mic Capture Volume", 0, 0x68, 0x68, 4, 0, 15, 0),
ES18XX_DOUBLE("Line Capture Volume", 0, 0x6e, 0x6e, 4, 0, 15, 0),
ES18XX_DOUBLE("FM Capture Volume", 0, 0x6b, 0x6b, 4, 0, 15, 0),
ES18XX_DOUBLE("CD Capture Volume", 0, 0x6a, 0x6a, 4, 0, 15, 0),
ES18XX_DOUBLE("Aux Capture Volume", 0, 0x6c, 0x6c, 4, 0, 15, 0)
पूर्ण;

/*
 * The chipset specअगरic mixer controls
 */
अटल स्थिर काष्ठा snd_kcontrol_new snd_es18xx_opt_speaker =
	ES18XX_SINGLE("Beep Playback Volume", 0, 0x3c, 0, 7, 0);

अटल स्थिर काष्ठा snd_kcontrol_new snd_es18xx_opt_1869[] = अणु
ES18XX_SINGLE("Capture Switch", 0, 0x1c, 4, 1, ES18XX_FL_INVERT),
ES18XX_SINGLE("Video Playback Switch", 0, 0x7f, 0, 1, 0),
ES18XX_DOUBLE("Mono Playback Volume", 0, 0x6d, 0x6d, 4, 0, 15, 0),
ES18XX_DOUBLE("Mono Capture Volume", 0, 0x6f, 0x6f, 4, 0, 15, 0)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_es18xx_opt_1878 =
	ES18XX_DOUBLE("Video Playback Volume", 0, 0x68, 0x68, 4, 0, 15, 0);

अटल स्थिर काष्ठा snd_kcontrol_new snd_es18xx_opt_1879[] = अणु
ES18XX_SINGLE("Video Playback Switch", 0, 0x71, 6, 1, 0),
ES18XX_DOUBLE("Video Playback Volume", 0, 0x6d, 0x6d, 4, 0, 15, 0),
ES18XX_DOUBLE("Video Capture Volume", 0, 0x6f, 0x6f, 4, 0, 15, 0)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_es18xx_pcm1_controls[] = अणु
ES18XX_DOUBLE("PCM Playback Volume", 0, 0x14, 0x14, 4, 0, 15, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_es18xx_pcm2_controls[] = अणु
ES18XX_DOUBLE("PCM Playback Volume", 0, 0x7c, 0x7c, 4, 0, 15, 0),
ES18XX_DOUBLE("PCM Playback Volume", 1, 0x14, 0x14, 4, 0, 15, 0)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_es18xx_spatializer_controls[] = अणु
ES18XX_SINGLE("3D Control - Level", 0, 0x52, 0, 63, 0),
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "3D Control - Switch",
	.info = snd_es18xx_info_spatializer_enable,
	.get = snd_es18xx_get_spatializer_enable,
	.put = snd_es18xx_put_spatializer_enable,
पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_es18xx_micpre1_control =
ES18XX_SINGLE("Mic Boost (+26dB)", 0, 0xa9, 2, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new snd_es18xx_micpre2_control =
ES18XX_SINGLE("Mic Boost (+26dB)", 0, 0x7d, 3, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new snd_es18xx_hw_volume_controls[] = अणु
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Hardware Master Playback Volume",
	.access = SNDRV_CTL_ELEM_ACCESS_READ,
	.info = snd_es18xx_info_hw_volume,
	.get = snd_es18xx_get_hw_volume,
पूर्ण,
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Hardware Master Playback Switch",
	.access = SNDRV_CTL_ELEM_ACCESS_READ,
	.info = snd_es18xx_info_hw_चयन,
	.get = snd_es18xx_get_hw_चयन,
पूर्ण,
ES18XX_SINGLE("Hardware Master Volume Split", 0, 0x64, 7, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_es18xx_opt_gpo_2bit[] = अणु
ES18XX_SINGLE("GPO0 Switch", 0, ES18XX_PM, 0, 1, ES18XX_FL_PMPORT),
ES18XX_SINGLE("GPO1 Switch", 0, ES18XX_PM, 1, 1, ES18XX_FL_PMPORT),
पूर्ण;

अटल पूर्णांक snd_es18xx_config_पढ़ो(काष्ठा snd_es18xx *chip, अचिन्हित अक्षर reg)
अणु
	पूर्णांक data;

	outb(reg, chip->ctrl_port);
	data = inb(chip->ctrl_port + 1);
	वापस data;
पूर्ण

अटल व्योम snd_es18xx_config_ग_लिखो(काष्ठा snd_es18xx *chip,
				    अचिन्हित अक्षर reg, अचिन्हित अक्षर data)
अणु
	/* No need क्रम spinlocks, this function is used only in
	   otherwise रक्षित init code */
	outb(reg, chip->ctrl_port);
	outb(data, chip->ctrl_port + 1);
#अगर_घोषित REG_DEBUG
	snd_prपूर्णांकk(KERN_DEBUG "Config reg %02x set to %02x\n", reg, data);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक snd_es18xx_initialize(काष्ठा snd_es18xx *chip,
				 अचिन्हित दीर्घ mpu_port,
				 अचिन्हित दीर्घ fm_port)
अणु
	पूर्णांक mask = 0;

        /* enable extended mode */
        snd_es18xx_dsp_command(chip, 0xC6);
	/* Reset mixer रेजिस्टरs */
	snd_es18xx_mixer_ग_लिखो(chip, 0x00, 0x00);

        /* Audio 1 DMA demand mode (4 bytes/request) */
        snd_es18xx_ग_लिखो(chip, 0xB9, 2);
	अगर (chip->caps & ES18XX_CONTROL) अणु
		/* Hardware volume IRQ */
		snd_es18xx_config_ग_लिखो(chip, 0x27, chip->irq);
		अगर (fm_port > 0 && fm_port != SNDRV_AUTO_PORT) अणु
			/* FM I/O */
			snd_es18xx_config_ग_लिखो(chip, 0x62, fm_port >> 8);
			snd_es18xx_config_ग_लिखो(chip, 0x63, fm_port & 0xff);
		पूर्ण
		अगर (mpu_port > 0 && mpu_port != SNDRV_AUTO_PORT) अणु
			/* MPU-401 I/O */
			snd_es18xx_config_ग_लिखो(chip, 0x64, mpu_port >> 8);
			snd_es18xx_config_ग_लिखो(chip, 0x65, mpu_port & 0xff);
			/* MPU-401 IRQ */
			snd_es18xx_config_ग_लिखो(chip, 0x28, chip->irq);
		पूर्ण
		/* Audio1 IRQ */
		snd_es18xx_config_ग_लिखो(chip, 0x70, chip->irq);
		/* Audio2 IRQ */
		snd_es18xx_config_ग_लिखो(chip, 0x72, chip->irq);
		/* Audio1 DMA */
		snd_es18xx_config_ग_लिखो(chip, 0x74, chip->dma1);
		/* Audio2 DMA */
		snd_es18xx_config_ग_लिखो(chip, 0x75, chip->dma2);

		/* Enable Audio 1 IRQ */
		snd_es18xx_ग_लिखो(chip, 0xB1, 0x50);
		/* Enable Audio 2 IRQ */
		snd_es18xx_mixer_ग_लिखो(chip, 0x7A, 0x40);
		/* Enable Audio 1 DMA */
		snd_es18xx_ग_लिखो(chip, 0xB2, 0x50);
		/* Enable MPU and hardware volume पूर्णांकerrupt */
		snd_es18xx_mixer_ग_लिखो(chip, 0x64, 0x42);
		/* Enable ESS wavetable input */
		snd_es18xx_mixer_bits(chip, 0x48, 0x10, 0x10);
	पूर्ण
	अन्यथा अणु
		पूर्णांक irqmask, dma1mask, dma2mask;
		चयन (chip->irq) अणु
		हाल 2:
		हाल 9:
			irqmask = 0;
			अवरोध;
		हाल 5:
			irqmask = 1;
			अवरोध;
		हाल 7:
			irqmask = 2;
			अवरोध;
		हाल 10:
			irqmask = 3;
			अवरोध;
		शेष:
			snd_prपूर्णांकk(KERN_ERR "invalid irq %d\n", chip->irq);
			वापस -ENODEV;
		पूर्ण
		चयन (chip->dma1) अणु
		हाल 0:
			dma1mask = 1;
			अवरोध;
		हाल 1:
			dma1mask = 2;
			अवरोध;
		हाल 3:
			dma1mask = 3;
			अवरोध;
		शेष:
			snd_prपूर्णांकk(KERN_ERR "invalid dma1 %d\n", chip->dma1);
			वापस -ENODEV;
		पूर्ण
		चयन (chip->dma2) अणु
		हाल 0:
			dma2mask = 0;
			अवरोध;
		हाल 1:
			dma2mask = 1;
			अवरोध;
		हाल 3:
			dma2mask = 2;
			अवरोध;
		हाल 5:
			dma2mask = 3;
			अवरोध;
		शेष:
			snd_prपूर्णांकk(KERN_ERR "invalid dma2 %d\n", chip->dma2);
			वापस -ENODEV;
		पूर्ण

		/* Enable and set Audio 1 IRQ */
		snd_es18xx_ग_लिखो(chip, 0xB1, 0x50 | (irqmask << 2));
		/* Enable and set Audio 1 DMA */
		snd_es18xx_ग_लिखो(chip, 0xB2, 0x50 | (dma1mask << 2));
		/* Set Audio 2 DMA */
		snd_es18xx_mixer_bits(chip, 0x7d, 0x07, 0x04 | dma2mask);
		/* Enable Audio 2 IRQ and DMA
		   Set capture mixer input */
		snd_es18xx_mixer_ग_लिखो(chip, 0x7A, 0x68);
		/* Enable and set hardware volume पूर्णांकerrupt */
		snd_es18xx_mixer_ग_लिखो(chip, 0x64, 0x06);
		अगर (mpu_port > 0 && mpu_port != SNDRV_AUTO_PORT) अणु
			/* MPU401 share irq with audio
			   Joystick enabled
			   FM enabled */
			snd_es18xx_mixer_ग_लिखो(chip, 0x40,
					       0x43 | (mpu_port & 0xf0) >> 1);
		पूर्ण
		snd_es18xx_mixer_ग_लिखो(chip, 0x7f, ((irqmask + 1) << 1) | 0x01);
	पूर्ण
	अगर (chip->caps & ES18XX_NEW_RATE) अणु
		/* Change behaviour of रेजिस्टर A1
		   4x oversampling
		   2nd channel DAC asynchronous */
		snd_es18xx_mixer_ग_लिखो(chip, 0x71, 0x32);
	पूर्ण
	अगर (!(chip->caps & ES18XX_PCM2)) अणु
		/* Enable DMA FIFO */
		snd_es18xx_ग_लिखो(chip, 0xB7, 0x80);
	पूर्ण
	अगर (chip->caps & ES18XX_SPATIALIZER) अणु
		/* Set spatializer parameters to recommended values */
		snd_es18xx_mixer_ग_लिखो(chip, 0x54, 0x8f);
		snd_es18xx_mixer_ग_लिखो(chip, 0x56, 0x95);
		snd_es18xx_mixer_ग_लिखो(chip, 0x58, 0x94);
		snd_es18xx_mixer_ग_लिखो(chip, 0x5a, 0x80);
	पूर्ण
	/* Flip the "enable I2S" bits क्रम those chipsets that need it */
	चयन (chip->version) अणु
	हाल 0x1879:
		//Leaving I2S enabled on the 1879 screws up the PCM playback (rate effected somehow)
		//so a Switch control has been added to toggle this 0x71 bit on/off:
		//snd_es18xx_mixer_bits(chip, 0x71, 0x40, 0x40);
		/* Note: we fall through on purpose here. */
	हाल 0x1878:
		snd_es18xx_config_ग_लिखो(chip, 0x29, snd_es18xx_config_पढ़ो(chip, 0x29) | 0x40);
		अवरोध;
	पूर्ण
	/* Mute input source */
	अगर (chip->caps & ES18XX_MUTEREC)
		mask = 0x10;
	अगर (chip->caps & ES18XX_RECMIX)
		snd_es18xx_mixer_ग_लिखो(chip, 0x1c, 0x05 | mask);
	अन्यथा अणु
		snd_es18xx_mixer_ग_लिखो(chip, 0x1c, 0x00 | mask);
		snd_es18xx_ग_लिखो(chip, 0xb4, 0x00);
	पूर्ण
#अगर_अघोषित AVOID_POPS
	/* Enable PCM output */
	snd_es18xx_dsp_command(chip, 0xD1);
#पूर्ण_अगर

        वापस 0;
पूर्ण

अटल पूर्णांक snd_es18xx_identअगरy(काष्ठा snd_es18xx *chip)
अणु
	पूर्णांक hi,lo;

	/* reset */
	अगर (snd_es18xx_reset(chip) < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "reset at 0x%lx failed!!!\n", chip->port);
		वापस -ENODEV;
	पूर्ण

	snd_es18xx_dsp_command(chip, 0xe7);
	hi = snd_es18xx_dsp_get_byte(chip);
	अगर (hi < 0) अणु
		वापस hi;
	पूर्ण
	lo = snd_es18xx_dsp_get_byte(chip);
	अगर ((lo & 0xf0) != 0x80) अणु
		वापस -ENODEV;
	पूर्ण
	अगर (hi == 0x48) अणु
		chip->version = 0x488;
		वापस 0;
	पूर्ण
	अगर (hi != 0x68) अणु
		वापस -ENODEV;
	पूर्ण
	अगर ((lo & 0x0f) < 8) अणु
		chip->version = 0x688;
		वापस 0;
	पूर्ण
			
        outb(0x40, chip->port + 0x04);
	udelay(10);
	hi = inb(chip->port + 0x05);
	udelay(10);
	lo = inb(chip->port + 0x05);
	अगर (hi != lo) अणु
		chip->version = hi << 8 | lo;
		chip->ctrl_port = inb(chip->port + 0x05) << 8;
		udelay(10);
		chip->ctrl_port += inb(chip->port + 0x05);

		अगर ((chip->res_ctrl_port = request_region(chip->ctrl_port, 8, "ES18xx - CTRL")) == शून्य) अणु
			snd_prपूर्णांकk(KERN_ERR PFX "unable go grab port 0x%lx\n", chip->ctrl_port);
			वापस -EBUSY;
		पूर्ण

		वापस 0;
	पूर्ण

	/* If has Hardware volume */
	अगर (snd_es18xx_mixer_writable(chip, 0x64, 0x04)) अणु
		/* If has Audio2 */
		अगर (snd_es18xx_mixer_writable(chip, 0x70, 0x7f)) अणु
			/* If has volume count */
			अगर (snd_es18xx_mixer_writable(chip, 0x64, 0x20)) अणु
				chip->version = 0x1887;
			पूर्ण अन्यथा अणु
				chip->version = 0x1888;
			पूर्ण
		पूर्ण अन्यथा अणु
			chip->version = 0x1788;
		पूर्ण
	पूर्ण
	अन्यथा
		chip->version = 0x1688;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es18xx_probe(काष्ठा snd_es18xx *chip,
			    अचिन्हित दीर्घ mpu_port,
			    अचिन्हित दीर्घ fm_port)
अणु
	अगर (snd_es18xx_identअगरy(chip) < 0) अणु
		snd_prपूर्णांकk(KERN_ERR PFX "[0x%lx] ESS chip not found\n", chip->port);
                वापस -ENODEV;
	पूर्ण

	चयन (chip->version) अणु
	हाल 0x1868:
		chip->caps = ES18XX_DUPLEX_MONO | ES18XX_DUPLEX_SAME | ES18XX_CONTROL | ES18XX_GPO_2BIT;
		अवरोध;
	हाल 0x1869:
		chip->caps = ES18XX_PCM2 | ES18XX_SPATIALIZER | ES18XX_RECMIX | ES18XX_NEW_RATE | ES18XX_AUXB | ES18XX_MONO | ES18XX_MUTEREC | ES18XX_CONTROL | ES18XX_HWV | ES18XX_GPO_2BIT;
		अवरोध;
	हाल 0x1878:
		chip->caps = ES18XX_DUPLEX_MONO | ES18XX_DUPLEX_SAME | ES18XX_I2S | ES18XX_CONTROL;
		अवरोध;
	हाल 0x1879:
		chip->caps = ES18XX_PCM2 | ES18XX_SPATIALIZER | ES18XX_RECMIX | ES18XX_NEW_RATE | ES18XX_AUXB | ES18XX_I2S | ES18XX_CONTROL | ES18XX_HWV;
		अवरोध;
	हाल 0x1887:
	हाल 0x1888:
		chip->caps = ES18XX_PCM2 | ES18XX_RECMIX | ES18XX_AUXB | ES18XX_DUPLEX_SAME | ES18XX_GPO_2BIT;
		अवरोध;
	शेष:
		snd_prपूर्णांकk(KERN_ERR "[0x%lx] unsupported chip ES%x\n",
                           chip->port, chip->version);
                वापस -ENODEV;
        पूर्ण

        snd_prपूर्णांकd("[0x%lx] ESS%x chip found\n", chip->port, chip->version);

	अगर (chip->dma1 == chip->dma2)
		chip->caps &= ~(ES18XX_PCM2 | ES18XX_DUPLEX_SAME);

	वापस snd_es18xx_initialize(chip, mpu_port, fm_port);
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_es18xx_playback_ops = अणु
	.खोलो =		snd_es18xx_playback_खोलो,
	.बंद =	snd_es18xx_playback_बंद,
	.hw_params =	snd_es18xx_playback_hw_params,
	.prepare =	snd_es18xx_playback_prepare,
	.trigger =	snd_es18xx_playback_trigger,
	.poपूर्णांकer =	snd_es18xx_playback_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_es18xx_capture_ops = अणु
	.खोलो =		snd_es18xx_capture_खोलो,
	.बंद =	snd_es18xx_capture_बंद,
	.hw_params =	snd_es18xx_capture_hw_params,
	.prepare =	snd_es18xx_capture_prepare,
	.trigger =	snd_es18xx_capture_trigger,
	.poपूर्णांकer =	snd_es18xx_capture_poपूर्णांकer,
पूर्ण;

अटल पूर्णांक snd_es18xx_pcm(काष्ठा snd_card *card, पूर्णांक device)
अणु
	काष्ठा snd_es18xx *chip = card->निजी_data;
        काष्ठा snd_pcm *pcm;
	अक्षर str[16];
	पूर्णांक err;

	प्र_लिखो(str, "ES%x", chip->version);
	अगर (chip->caps & ES18XX_PCM2)
		err = snd_pcm_new(card, str, device, 2, 1, &pcm);
	अन्यथा
		err = snd_pcm_new(card, str, device, 1, 1, &pcm);
        अगर (err < 0)
                वापस err;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_es18xx_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_es18xx_capture_ops);

	/* global setup */
        pcm->निजी_data = chip;
        pcm->info_flags = 0;
	अगर (chip->caps & ES18XX_DUPLEX_SAME)
		pcm->info_flags |= SNDRV_PCM_INFO_JOINT_DUPLEX;
	अगर (! (chip->caps & ES18XX_PCM2))
		pcm->info_flags |= SNDRV_PCM_INFO_HALF_DUPLEX;
	प्र_लिखो(pcm->name, "ESS AudioDrive ES%x", chip->version);
        chip->pcm = pcm;

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV, card->dev,
				       64*1024,
				       chip->dma1 > 3 || chip->dma2 > 3 ? 128*1024 : 64*1024);
	वापस 0;
पूर्ण

/* Power Management support functions */
#अगर_घोषित CONFIG_PM
अटल पूर्णांक snd_es18xx_suspend(काष्ठा snd_card *card, pm_message_t state)
अणु
	काष्ठा snd_es18xx *chip = card->निजी_data;

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);

	/* घातer करोwn */
	chip->pm_reg = (अचिन्हित अक्षर)snd_es18xx_पढ़ो(chip, ES18XX_PM);
	chip->pm_reg |= (ES18XX_PM_FM | ES18XX_PM_SUS);
	snd_es18xx_ग_लिखो(chip, ES18XX_PM, chip->pm_reg);
	snd_es18xx_ग_लिखो(chip, ES18XX_PM, chip->pm_reg ^= ES18XX_PM_SUS);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_es18xx_resume(काष्ठा snd_card *card)
अणु
	काष्ठा snd_es18xx *chip = card->निजी_data;

	/* restore PM रेजिस्टर, we won't wake till (not 0x07) i/o activity though */
	snd_es18xx_ग_लिखो(chip, ES18XX_PM, chip->pm_reg ^= ES18XX_PM_FM);

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल पूर्णांक snd_es18xx_मुक्त(काष्ठा snd_card *card)
अणु
	काष्ठा snd_es18xx *chip = card->निजी_data;

	release_and_मुक्त_resource(chip->res_port);
	release_and_मुक्त_resource(chip->res_ctrl_port);
	release_and_मुक्त_resource(chip->res_mpu_port);
	अगर (chip->irq >= 0)
		मुक्त_irq(chip->irq, (व्योम *) card);
	अगर (chip->dma1 >= 0) अणु
		disable_dma(chip->dma1);
		मुक्त_dma(chip->dma1);
	पूर्ण
	अगर (chip->dma2 >= 0 && chip->dma1 != chip->dma2) अणु
		disable_dma(chip->dma2);
		मुक्त_dma(chip->dma2);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es18xx_dev_मुक्त(काष्ठा snd_device *device)
अणु
	वापस snd_es18xx_मुक्त(device->card);
पूर्ण

अटल पूर्णांक snd_es18xx_new_device(काष्ठा snd_card *card,
				 अचिन्हित दीर्घ port,
				 अचिन्हित दीर्घ mpu_port,
				 अचिन्हित दीर्घ fm_port,
				 पूर्णांक irq, पूर्णांक dma1, पूर्णांक dma2)
अणु
	काष्ठा snd_es18xx *chip = card->निजी_data;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =	snd_es18xx_dev_मुक्त,
        पूर्ण;
	पूर्णांक err;

	spin_lock_init(&chip->reg_lock);
 	spin_lock_init(&chip->mixer_lock);
        chip->port = port;
        chip->irq = -1;
        chip->dma1 = -1;
        chip->dma2 = -1;
        chip->audio2_vol = 0x00;
	chip->active = 0;

	chip->res_port = request_region(port, 16, "ES18xx");
	अगर (chip->res_port == शून्य) अणु
		snd_es18xx_मुक्त(card);
		snd_prपूर्णांकk(KERN_ERR PFX "unable to grap ports 0x%lx-0x%lx\n", port, port + 16 - 1);
		वापस -EBUSY;
	पूर्ण

	अगर (request_irq(irq, snd_es18xx_पूर्णांकerrupt, 0, "ES18xx",
			(व्योम *) card)) अणु
		snd_es18xx_मुक्त(card);
		snd_prपूर्णांकk(KERN_ERR PFX "unable to grap IRQ %d\n", irq);
		वापस -EBUSY;
	पूर्ण
	chip->irq = irq;
	card->sync_irq = chip->irq;

	अगर (request_dma(dma1, "ES18xx DMA 1")) अणु
		snd_es18xx_मुक्त(card);
		snd_prपूर्णांकk(KERN_ERR PFX "unable to grap DMA1 %d\n", dma1);
		वापस -EBUSY;
	पूर्ण
	chip->dma1 = dma1;

	अगर (dma2 != dma1 && request_dma(dma2, "ES18xx DMA 2")) अणु
		snd_es18xx_मुक्त(card);
		snd_prपूर्णांकk(KERN_ERR PFX "unable to grap DMA2 %d\n", dma2);
		वापस -EBUSY;
	पूर्ण
	chip->dma2 = dma2;

	अगर (snd_es18xx_probe(chip, mpu_port, fm_port) < 0) अणु
		snd_es18xx_मुक्त(card);
		वापस -ENODEV;
	पूर्ण
	err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops);
	अगर (err < 0) अणु
		snd_es18xx_मुक्त(card);
		वापस err;
	पूर्ण
        वापस 0;
पूर्ण

अटल पूर्णांक snd_es18xx_mixer(काष्ठा snd_card *card)
अणु
	काष्ठा snd_es18xx *chip = card->निजी_data;
	पूर्णांक err;
	अचिन्हित पूर्णांक idx;

	म_नकल(card->mixername, chip->pcm->name);

	क्रम (idx = 0; idx < ARRAY_SIZE(snd_es18xx_base_controls); idx++) अणु
		काष्ठा snd_kcontrol *kctl;
		kctl = snd_ctl_new1(&snd_es18xx_base_controls[idx], chip);
		अगर (chip->caps & ES18XX_HWV) अणु
			चयन (idx) अणु
			हाल 0:
				chip->master_volume = kctl;
				kctl->निजी_मुक्त = snd_es18xx_hwv_मुक्त;
				अवरोध;
			हाल 1:
				chip->master_चयन = kctl;
				kctl->निजी_मुक्त = snd_es18xx_hwv_मुक्त;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर ((err = snd_ctl_add(card, kctl)) < 0)
			वापस err;
	पूर्ण
	अगर (chip->caps & ES18XX_PCM2) अणु
		क्रम (idx = 0; idx < ARRAY_SIZE(snd_es18xx_pcm2_controls); idx++) अणु
			अगर ((err = snd_ctl_add(card, snd_ctl_new1(&snd_es18xx_pcm2_controls[idx], chip))) < 0)
				वापस err;
		पूर्ण 
	पूर्ण अन्यथा अणु
		क्रम (idx = 0; idx < ARRAY_SIZE(snd_es18xx_pcm1_controls); idx++) अणु
			अगर ((err = snd_ctl_add(card, snd_ctl_new1(&snd_es18xx_pcm1_controls[idx], chip))) < 0)
				वापस err;
		पूर्ण
	पूर्ण

	अगर (chip->caps & ES18XX_RECMIX) अणु
		क्रम (idx = 0; idx < ARRAY_SIZE(snd_es18xx_recmix_controls); idx++) अणु
			अगर ((err = snd_ctl_add(card, snd_ctl_new1(&snd_es18xx_recmix_controls[idx], chip))) < 0)
				वापस err;
		पूर्ण
	पूर्ण
	चयन (chip->version) अणु
	शेष:
		अगर ((err = snd_ctl_add(card, snd_ctl_new1(&snd_es18xx_micpre1_control, chip))) < 0)
			वापस err;
		अवरोध;
	हाल 0x1869:
	हाल 0x1879:
		अगर ((err = snd_ctl_add(card, snd_ctl_new1(&snd_es18xx_micpre2_control, chip))) < 0)
			वापस err;
		अवरोध;
	पूर्ण
	अगर (chip->caps & ES18XX_SPATIALIZER) अणु
		क्रम (idx = 0; idx < ARRAY_SIZE(snd_es18xx_spatializer_controls); idx++) अणु
			अगर ((err = snd_ctl_add(card, snd_ctl_new1(&snd_es18xx_spatializer_controls[idx], chip))) < 0)
				वापस err;
		पूर्ण
	पूर्ण
	अगर (chip->caps & ES18XX_HWV) अणु
		क्रम (idx = 0; idx < ARRAY_SIZE(snd_es18xx_hw_volume_controls); idx++) अणु
			काष्ठा snd_kcontrol *kctl;
			kctl = snd_ctl_new1(&snd_es18xx_hw_volume_controls[idx], chip);
			अगर (idx == 0)
				chip->hw_volume = kctl;
			अन्यथा
				chip->hw_चयन = kctl;
			kctl->निजी_मुक्त = snd_es18xx_hwv_मुक्त;
			अगर ((err = snd_ctl_add(card, kctl)) < 0)
				वापस err;
			
		पूर्ण
	पूर्ण
	/* finish initializing other chipset specअगरic controls
	 */
	अगर (chip->version != 0x1868) अणु
		err = snd_ctl_add(card, snd_ctl_new1(&snd_es18xx_opt_speaker,
						     chip));
		अगर (err < 0)
			वापस err;
	पूर्ण
	अगर (chip->version == 0x1869) अणु
		क्रम (idx = 0; idx < ARRAY_SIZE(snd_es18xx_opt_1869); idx++) अणु
			err = snd_ctl_add(card,
					  snd_ctl_new1(&snd_es18xx_opt_1869[idx],
						       chip));
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण अन्यथा अगर (chip->version == 0x1878) अणु
		err = snd_ctl_add(card, snd_ctl_new1(&snd_es18xx_opt_1878,
						     chip));
		अगर (err < 0)
			वापस err;
	पूर्ण अन्यथा अगर (chip->version == 0x1879) अणु
		क्रम (idx = 0; idx < ARRAY_SIZE(snd_es18xx_opt_1879); idx++) अणु
			err = snd_ctl_add(card,
					  snd_ctl_new1(&snd_es18xx_opt_1879[idx],
						       chip));
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण
	अगर (chip->caps & ES18XX_GPO_2BIT) अणु
		क्रम (idx = 0; idx < ARRAY_SIZE(snd_es18xx_opt_gpo_2bit); idx++) अणु
			err = snd_ctl_add(card,
					  snd_ctl_new1(&snd_es18xx_opt_gpo_2bit[idx],
						       chip));
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
       

/* Card level */

MODULE_AUTHOR("Christian Fischbach <fishbach@pool.informatik.rwth-aachen.de>, Abramo Bagnara <abramo@alsa-project.org>");
MODULE_DESCRIPTION("ESS ES18xx AudioDrive");
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_ISAPNP; /* Enable this card */
#अगर_घोषित CONFIG_PNP
अटल bool isapnp[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_ISAPNP;
#पूर्ण_अगर
अटल दीर्घ port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;	/* 0x220,0x240,0x260,0x280 */
#अगर_अघोषित CONFIG_PNP
अटल दीर्घ mpu_port[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = -1पूर्ण;
#अन्यथा
अटल दीर्घ mpu_port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;
#पूर्ण_अगर
अटल दीर्घ fm_port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;
अटल पूर्णांक irq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ;	/* 5,7,9,10 */
अटल पूर्णांक dma1[SNDRV_CARDS] = SNDRV_DEFAULT_DMA;	/* 0,1,3 */
अटल पूर्णांक dma2[SNDRV_CARDS] = SNDRV_DEFAULT_DMA;	/* 0,1,3 */

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for ES18xx soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for ES18xx soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable ES18xx soundcard.");
#अगर_घोषित CONFIG_PNP
module_param_array(isapnp, bool, शून्य, 0444);
MODULE_PARM_DESC(isapnp, "PnP detection for specified soundcard.");
#पूर्ण_अगर
module_param_hw_array(port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(port, "Port # for ES18xx driver.");
module_param_hw_array(mpu_port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(mpu_port, "MPU-401 port # for ES18xx driver.");
module_param_hw_array(fm_port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(fm_port, "FM port # for ES18xx driver.");
module_param_hw_array(irq, पूर्णांक, irq, शून्य, 0444);
MODULE_PARM_DESC(irq, "IRQ # for ES18xx driver.");
module_param_hw_array(dma1, पूर्णांक, dma, शून्य, 0444);
MODULE_PARM_DESC(dma1, "DMA 1 # for ES18xx driver.");
module_param_hw_array(dma2, पूर्णांक, dma, शून्य, 0444);
MODULE_PARM_DESC(dma2, "DMA 2 # for ES18xx driver.");

#अगर_घोषित CONFIG_PNP
अटल पूर्णांक isa_रेजिस्टरed;
अटल पूर्णांक pnp_रेजिस्टरed;
अटल पूर्णांक pnpc_रेजिस्टरed;

अटल स्थिर काष्ठा pnp_device_id snd_audiodrive_pnpbiosids[] = अणु
	अणु .id = "ESS1869" पूर्ण,
	अणु .id = "ESS1879" पूर्ण,
	अणु .id = "" पूर्ण		/* end */
पूर्ण;

MODULE_DEVICE_TABLE(pnp, snd_audiodrive_pnpbiosids);

/* PnP मुख्य device initialization */
अटल पूर्णांक snd_audiodrive_pnp_init_मुख्य(पूर्णांक dev, काष्ठा pnp_dev *pdev)
अणु
	अगर (pnp_activate_dev(pdev) < 0) अणु
		snd_prपूर्णांकk(KERN_ERR PFX "PnP configure failure (out of resources?)\n");
		वापस -EBUSY;
	पूर्ण
	/* ok. hack using Venकरोr-Defined Card-Level रेजिस्टरs */
	/* skip csn and logdev initialization - alपढ़ोy करोne in isapnp_configure */
	अगर (pnp_device_is_isapnp(pdev)) अणु
		isapnp_cfg_begin(isapnp_card_number(pdev), isapnp_csn_number(pdev));
		isapnp_ग_लिखो_byte(0x27, pnp_irq(pdev, 0));	/* Hardware Volume IRQ Number */
		अगर (mpu_port[dev] != SNDRV_AUTO_PORT)
			isapnp_ग_लिखो_byte(0x28, pnp_irq(pdev, 0)); /* MPU-401 IRQ Number */
		isapnp_ग_लिखो_byte(0x72, pnp_irq(pdev, 0));	/* second IRQ */
		isapnp_cfg_end();
	पूर्ण
	port[dev] = pnp_port_start(pdev, 0);
	fm_port[dev] = pnp_port_start(pdev, 1);
	mpu_port[dev] = pnp_port_start(pdev, 2);
	dma1[dev] = pnp_dma(pdev, 0);
	dma2[dev] = pnp_dma(pdev, 1);
	irq[dev] = pnp_irq(pdev, 0);
	snd_prपूर्णांकdd("PnP ES18xx: port=0x%lx, fm port=0x%lx, mpu port=0x%lx\n", port[dev], fm_port[dev], mpu_port[dev]);
	snd_prपूर्णांकdd("PnP ES18xx: dma1=%i, dma2=%i, irq=%i\n", dma1[dev], dma2[dev], irq[dev]);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_audiodrive_pnp(पूर्णांक dev, काष्ठा snd_es18xx *chip,
			      काष्ठा pnp_dev *pdev)
अणु
	chip->dev = pdev;
	अगर (snd_audiodrive_pnp_init_मुख्य(dev, chip->dev) < 0)
		वापस -EBUSY;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pnp_card_device_id snd_audiodrive_pnpids[] = अणु
	/* ESS 1868 (पूर्णांकegrated on Compaq dual P-Pro motherboard and Genius 18PnP 3D) */
	अणु .id = "ESS1868", .devs = अणु अणु "ESS1868" पूर्ण, अणु "ESS0000" पूर्ण पूर्ण पूर्ण,
	/* ESS 1868 (पूर्णांकegrated on Maxisound Cards) */
	अणु .id = "ESS1868", .devs = अणु अणु "ESS8601" पूर्ण, अणु "ESS8600" पूर्ण पूर्ण पूर्ण,
	/* ESS 1868 (पूर्णांकegrated on Maxisound Cards) */
	अणु .id = "ESS1868", .devs = अणु अणु "ESS8611" पूर्ण, अणु "ESS8610" पूर्ण पूर्ण पूर्ण,
	/* ESS ES1869 Plug and Play AudioDrive */
	अणु .id = "ESS0003", .devs = अणु अणु "ESS1869" पूर्ण, अणु "ESS0006" पूर्ण पूर्ण पूर्ण,
	/* ESS 1869 */
	अणु .id = "ESS1869", .devs = अणु अणु "ESS1869" पूर्ण, अणु "ESS0006" पूर्ण पूर्ण पूर्ण,
	/* ESS 1878 */
	अणु .id = "ESS1878", .devs = अणु अणु "ESS1878" पूर्ण, अणु "ESS0004" पूर्ण पूर्ण पूर्ण,
	/* ESS 1879 */
	अणु .id = "ESS1879", .devs = अणु अणु "ESS1879" पूर्ण, अणु "ESS0009" पूर्ण पूर्ण पूर्ण,
	/* --- */
	अणु .id = "" पूर्ण /* end */
पूर्ण;

MODULE_DEVICE_TABLE(pnp_card, snd_audiodrive_pnpids);

अटल पूर्णांक snd_audiodrive_pnpc(पूर्णांक dev, काष्ठा snd_es18xx *chip,
			       काष्ठा pnp_card_link *card,
			       स्थिर काष्ठा pnp_card_device_id *id)
अणु
	chip->dev = pnp_request_card_device(card, id->devs[0].id, शून्य);
	अगर (chip->dev == शून्य)
		वापस -EBUSY;

	chip->devc = pnp_request_card_device(card, id->devs[1].id, शून्य);
	अगर (chip->devc == शून्य)
		वापस -EBUSY;

	/* Control port initialization */
	अगर (pnp_activate_dev(chip->devc) < 0) अणु
		snd_prपूर्णांकk(KERN_ERR PFX "PnP control configure failure (out of resources?)\n");
		वापस -EAGAIN;
	पूर्ण
	snd_prपूर्णांकdd("pnp: port=0x%llx\n",
			(अचिन्हित दीर्घ दीर्घ)pnp_port_start(chip->devc, 0));
	अगर (snd_audiodrive_pnp_init_मुख्य(dev, chip->dev) < 0)
		वापस -EBUSY;

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PNP */

#अगर_घोषित CONFIG_PNP
#घोषणा is_isapnp_selected(dev)		isapnp[dev]
#अन्यथा
#घोषणा is_isapnp_selected(dev)		0
#पूर्ण_अगर

अटल पूर्णांक snd_es18xx_card_new(काष्ठा device *pdev, पूर्णांक dev,
			       काष्ठा snd_card **cardp)
अणु
	वापस snd_card_new(pdev, index[dev], id[dev], THIS_MODULE,
			    माप(काष्ठा snd_es18xx), cardp);
पूर्ण

अटल पूर्णांक snd_audiodrive_probe(काष्ठा snd_card *card, पूर्णांक dev)
अणु
	काष्ठा snd_es18xx *chip = card->निजी_data;
	काष्ठा snd_opl3 *opl3;
	पूर्णांक err;

	err = snd_es18xx_new_device(card,
				    port[dev], mpu_port[dev], fm_port[dev],
				    irq[dev], dma1[dev], dma2[dev]);
	अगर (err < 0)
		वापस err;

	प्र_लिखो(card->driver, "ES%x", chip->version);
	
	प्र_लिखो(card->लघुname, "ESS AudioDrive ES%x", chip->version);
	अगर (dma1[dev] != dma2[dev])
		प्र_लिखो(card->दीर्घname, "%s at 0x%lx, irq %d, dma1 %d, dma2 %d",
			card->लघुname,
			chip->port,
			irq[dev], dma1[dev], dma2[dev]);
	अन्यथा
		प्र_लिखो(card->दीर्घname, "%s at 0x%lx, irq %d, dma %d",
			card->लघुname,
			chip->port,
			irq[dev], dma1[dev]);

	err = snd_es18xx_pcm(card, 0);
	अगर (err < 0)
		वापस err;

	err = snd_es18xx_mixer(card);
	अगर (err < 0)
		वापस err;

	अगर (fm_port[dev] > 0 && fm_port[dev] != SNDRV_AUTO_PORT) अणु
		अगर (snd_opl3_create(card, fm_port[dev], fm_port[dev] + 2,
				    OPL3_HW_OPL3, 0, &opl3) < 0) अणु
			snd_prपूर्णांकk(KERN_WARNING PFX
				   "opl3 not detected at 0x%lx\n",
				   fm_port[dev]);
		पूर्ण अन्यथा अणु
			err = snd_opl3_hwdep_new(opl3, 0, 1, शून्य);
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण

	अगर (mpu_port[dev] > 0 && mpu_port[dev] != SNDRV_AUTO_PORT) अणु
		err = snd_mpu401_uart_new(card, 0, MPU401_HW_ES18XX,
					  mpu_port[dev], MPU401_INFO_IRQ_HOOK,
					  -1, &chip->rmidi);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस snd_card_रेजिस्टर(card);
पूर्ण

अटल पूर्णांक snd_es18xx_isa_match(काष्ठा device *pdev, अचिन्हित पूर्णांक dev)
अणु
	वापस enable[dev] && !is_isapnp_selected(dev);
पूर्ण

अटल पूर्णांक snd_es18xx_isa_probe1(पूर्णांक dev, काष्ठा device *devptr)
अणु
	काष्ठा snd_card *card;
	पूर्णांक err;

	err = snd_es18xx_card_new(devptr, dev, &card);
	अगर (err < 0)
		वापस err;
	अगर ((err = snd_audiodrive_probe(card, dev)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	dev_set_drvdata(devptr, card);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es18xx_isa_probe(काष्ठा device *pdev, अचिन्हित पूर्णांक dev)
अणु
	पूर्णांक err;
	अटल स्थिर पूर्णांक possible_irqs[] = अणु5, 9, 10, 7, 11, 12, -1पूर्ण;
	अटल स्थिर पूर्णांक possible_dmas[] = अणु1, 0, 3, 5, -1पूर्ण;

	अगर (irq[dev] == SNDRV_AUTO_IRQ) अणु
		अगर ((irq[dev] = snd_legacy_find_मुक्त_irq(possible_irqs)) < 0) अणु
			snd_prपूर्णांकk(KERN_ERR PFX "unable to find a free IRQ\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	अगर (dma1[dev] == SNDRV_AUTO_DMA) अणु
		अगर ((dma1[dev] = snd_legacy_find_मुक्त_dma(possible_dmas)) < 0) अणु
			snd_prपूर्णांकk(KERN_ERR PFX "unable to find a free DMA1\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	अगर (dma2[dev] == SNDRV_AUTO_DMA) अणु
		अगर ((dma2[dev] = snd_legacy_find_मुक्त_dma(possible_dmas)) < 0) अणु
			snd_prपूर्णांकk(KERN_ERR PFX "unable to find a free DMA2\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	अगर (port[dev] != SNDRV_AUTO_PORT) अणु
		वापस snd_es18xx_isa_probe1(dev, pdev);
	पूर्ण अन्यथा अणु
		अटल स्थिर अचिन्हित दीर्घ possible_ports[] = अणु0x220, 0x240, 0x260, 0x280पूर्ण;
		पूर्णांक i;
		क्रम (i = 0; i < ARRAY_SIZE(possible_ports); i++) अणु
			port[dev] = possible_ports[i];
			err = snd_es18xx_isa_probe1(dev, pdev);
			अगर (! err)
				वापस 0;
		पूर्ण
		वापस err;
	पूर्ण
पूर्ण

अटल व्योम snd_es18xx_isa_हटाओ(काष्ठा device *devptr,
				  अचिन्हित पूर्णांक dev)
अणु
	snd_card_मुक्त(dev_get_drvdata(devptr));
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक snd_es18xx_isa_suspend(काष्ठा device *dev, अचिन्हित पूर्णांक n,
				  pm_message_t state)
अणु
	वापस snd_es18xx_suspend(dev_get_drvdata(dev), state);
पूर्ण

अटल पूर्णांक snd_es18xx_isa_resume(काष्ठा device *dev, अचिन्हित पूर्णांक n)
अणु
	वापस snd_es18xx_resume(dev_get_drvdata(dev));
पूर्ण
#पूर्ण_अगर

#घोषणा DEV_NAME "es18xx"

अटल काष्ठा isa_driver snd_es18xx_isa_driver = अणु
	.match		= snd_es18xx_isa_match,
	.probe		= snd_es18xx_isa_probe,
	.हटाओ		= snd_es18xx_isa_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= snd_es18xx_isa_suspend,
	.resume		= snd_es18xx_isa_resume,
#पूर्ण_अगर
	.driver		= अणु
		.name	= DEV_NAME
	पूर्ण,
पूर्ण;


#अगर_घोषित CONFIG_PNP
अटल पूर्णांक snd_audiodrive_pnp_detect(काष्ठा pnp_dev *pdev,
				     स्थिर काष्ठा pnp_device_id *id)
अणु
	अटल पूर्णांक dev;
	पूर्णांक err;
	काष्ठा snd_card *card;

	अगर (pnp_device_is_isapnp(pdev))
		वापस -ENOENT;	/* we have another procedure - card */
	क्रम (; dev < SNDRV_CARDS; dev++) अणु
		अगर (enable[dev] && isapnp[dev])
			अवरोध;
	पूर्ण
	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;

	err = snd_es18xx_card_new(&pdev->dev, dev, &card);
	अगर (err < 0)
		वापस err;
	अगर ((err = snd_audiodrive_pnp(dev, card->निजी_data, pdev)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	अगर ((err = snd_audiodrive_probe(card, dev)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	pnp_set_drvdata(pdev, card);
	dev++;
	वापस 0;
पूर्ण

अटल व्योम snd_audiodrive_pnp_हटाओ(काष्ठा pnp_dev *pdev)
अणु
	snd_card_मुक्त(pnp_get_drvdata(pdev));
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक snd_audiodrive_pnp_suspend(काष्ठा pnp_dev *pdev, pm_message_t state)
अणु
	वापस snd_es18xx_suspend(pnp_get_drvdata(pdev), state);
पूर्ण
अटल पूर्णांक snd_audiodrive_pnp_resume(काष्ठा pnp_dev *pdev)
अणु
	वापस snd_es18xx_resume(pnp_get_drvdata(pdev));
पूर्ण
#पूर्ण_अगर

अटल काष्ठा pnp_driver es18xx_pnp_driver = अणु
	.name = "es18xx-pnpbios",
	.id_table = snd_audiodrive_pnpbiosids,
	.probe = snd_audiodrive_pnp_detect,
	.हटाओ = snd_audiodrive_pnp_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend = snd_audiodrive_pnp_suspend,
	.resume = snd_audiodrive_pnp_resume,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक snd_audiodrive_pnpc_detect(काष्ठा pnp_card_link *pcard,
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

	res = snd_es18xx_card_new(&pcard->card->dev, dev, &card);
	अगर (res < 0)
		वापस res;

	अगर ((res = snd_audiodrive_pnpc(dev, card->निजी_data, pcard, pid)) < 0) अणु
		snd_card_मुक्त(card);
		वापस res;
	पूर्ण
	अगर ((res = snd_audiodrive_probe(card, dev)) < 0) अणु
		snd_card_मुक्त(card);
		वापस res;
	पूर्ण

	pnp_set_card_drvdata(pcard, card);
	dev++;
	वापस 0;
पूर्ण

अटल व्योम snd_audiodrive_pnpc_हटाओ(काष्ठा pnp_card_link *pcard)
अणु
	snd_card_मुक्त(pnp_get_card_drvdata(pcard));
	pnp_set_card_drvdata(pcard, शून्य);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक snd_audiodrive_pnpc_suspend(काष्ठा pnp_card_link *pcard, pm_message_t state)
अणु
	वापस snd_es18xx_suspend(pnp_get_card_drvdata(pcard), state);
पूर्ण

अटल पूर्णांक snd_audiodrive_pnpc_resume(काष्ठा pnp_card_link *pcard)
अणु
	वापस snd_es18xx_resume(pnp_get_card_drvdata(pcard));
पूर्ण

#पूर्ण_अगर

अटल काष्ठा pnp_card_driver es18xx_pnpc_driver = अणु
	.flags = PNP_DRIVER_RES_DISABLE,
	.name = "es18xx",
	.id_table = snd_audiodrive_pnpids,
	.probe = snd_audiodrive_pnpc_detect,
	.हटाओ = snd_audiodrive_pnpc_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= snd_audiodrive_pnpc_suspend,
	.resume		= snd_audiodrive_pnpc_resume,
#पूर्ण_अगर
पूर्ण;
#पूर्ण_अगर /* CONFIG_PNP */

अटल पूर्णांक __init alsa_card_es18xx_init(व्योम)
अणु
	पूर्णांक err;

	err = isa_रेजिस्टर_driver(&snd_es18xx_isa_driver, SNDRV_CARDS);
#अगर_घोषित CONFIG_PNP
	अगर (!err)
		isa_रेजिस्टरed = 1;

	err = pnp_रेजिस्टर_driver(&es18xx_pnp_driver);
	अगर (!err)
		pnp_रेजिस्टरed = 1;

	err = pnp_रेजिस्टर_card_driver(&es18xx_pnpc_driver);
	अगर (!err)
		pnpc_रेजिस्टरed = 1;

	अगर (isa_रेजिस्टरed || pnp_रेजिस्टरed)
		err = 0;
#पूर्ण_अगर
	वापस err;
पूर्ण

अटल व्योम __निकास alsa_card_es18xx_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_PNP
	अगर (pnpc_रेजिस्टरed)
		pnp_unरेजिस्टर_card_driver(&es18xx_pnpc_driver);
	अगर (pnp_रेजिस्टरed)
		pnp_unरेजिस्टर_driver(&es18xx_pnp_driver);
	अगर (isa_रेजिस्टरed)
#पूर्ण_अगर
		isa_unरेजिस्टर_driver(&snd_es18xx_isa_driver);
पूर्ण

module_init(alsa_card_es18xx_init)
module_निकास(alsa_card_es18xx_निकास)
