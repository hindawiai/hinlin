<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *  Routines क्रम control of ESS ES1688/688/488 chip
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <sound/core.h>
#समावेश <sound/es1688.h>
#समावेश <sound/initval.h>

#समावेश <यंत्र/dma.h>

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("ESS ESx688 lowlevel module");
MODULE_LICENSE("GPL");

अटल पूर्णांक snd_es1688_dsp_command(काष्ठा snd_es1688 *chip, अचिन्हित अक्षर val)
अणु
	पूर्णांक i;

	क्रम (i = 10000; i; i--)
		अगर ((inb(ES1688P(chip, STATUS)) & 0x80) == 0) अणु
			outb(val, ES1688P(chip, COMMAND));
			वापस 1;
		पूर्ण
#अगर_घोषित CONFIG_SND_DEBUG
	prपूर्णांकk(KERN_DEBUG "snd_es1688_dsp_command: timeout (0x%x)\n", val);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1688_dsp_get_byte(काष्ठा snd_es1688 *chip)
अणु
	पूर्णांक i;

	क्रम (i = 1000; i; i--)
		अगर (inb(ES1688P(chip, DATA_AVAIL)) & 0x80)
			वापस inb(ES1688P(chip, READ));
	snd_prपूर्णांकd("es1688 get byte failed: 0x%lx = 0x%x!!!\n", ES1688P(chip, DATA_AVAIL), inb(ES1688P(chip, DATA_AVAIL)));
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक snd_es1688_ग_लिखो(काष्ठा snd_es1688 *chip,
			    अचिन्हित अक्षर reg, अचिन्हित अक्षर data)
अणु
	अगर (!snd_es1688_dsp_command(chip, reg))
		वापस 0;
	वापस snd_es1688_dsp_command(chip, data);
पूर्ण

अटल पूर्णांक snd_es1688_पढ़ो(काष्ठा snd_es1688 *chip, अचिन्हित अक्षर reg)
अणु
	/* Read a byte from an extended mode रेजिस्टर of ES1688 */
	अगर (!snd_es1688_dsp_command(chip, 0xc0))
		वापस -1;
	अगर (!snd_es1688_dsp_command(chip, reg))
		वापस -1;
	वापस snd_es1688_dsp_get_byte(chip);
पूर्ण

व्योम snd_es1688_mixer_ग_लिखो(काष्ठा snd_es1688 *chip,
			    अचिन्हित अक्षर reg, अचिन्हित अक्षर data)
अणु
	outb(reg, ES1688P(chip, MIXER_ADDR));
	udelay(10);
	outb(data, ES1688P(chip, MIXER_DATA));
	udelay(10);
पूर्ण

अटल अचिन्हित अक्षर snd_es1688_mixer_पढ़ो(काष्ठा snd_es1688 *chip, अचिन्हित अक्षर reg)
अणु
	अचिन्हित अक्षर result;

	outb(reg, ES1688P(chip, MIXER_ADDR));
	udelay(10);
	result = inb(ES1688P(chip, MIXER_DATA));
	udelay(10);
	वापस result;
पूर्ण

पूर्णांक snd_es1688_reset(काष्ठा snd_es1688 *chip)
अणु
	पूर्णांक i;

	outb(3, ES1688P(chip, RESET));		/* valid only क्रम ESS chips, SB -> 1 */
	udelay(10);
	outb(0, ES1688P(chip, RESET));
	udelay(30);
	क्रम (i = 0; i < 1000 && !(inb(ES1688P(chip, DATA_AVAIL)) & 0x80); i++);
	अगर (inb(ES1688P(chip, READ)) != 0xaa) अणु
		snd_prपूर्णांकd("ess_reset at 0x%lx: failed!!!\n", chip->port);
		वापस -ENODEV;
	पूर्ण
	snd_es1688_dsp_command(chip, 0xc6);	/* enable extended mode */
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_es1688_reset);

अटल पूर्णांक snd_es1688_probe(काष्ठा snd_es1688 *chip)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित लघु major, minor;
	पूर्णांक i;

	/*
	 *  initialization sequence
	 */

	spin_lock_irqsave(&chip->reg_lock, flags);	/* Some ESS1688 cards need this */
	inb(ES1688P(chip, ENABLE1));	/* ENABLE1 */
	inb(ES1688P(chip, ENABLE1));	/* ENABLE1 */
	inb(ES1688P(chip, ENABLE1));	/* ENABLE1 */
	inb(ES1688P(chip, ENABLE2));	/* ENABLE2 */
	inb(ES1688P(chip, ENABLE1));	/* ENABLE1 */
	inb(ES1688P(chip, ENABLE2));	/* ENABLE2 */
	inb(ES1688P(chip, ENABLE1));	/* ENABLE1 */
	inb(ES1688P(chip, ENABLE1));	/* ENABLE1 */
	inb(ES1688P(chip, ENABLE2));	/* ENABLE2 */
	inb(ES1688P(chip, ENABLE1));	/* ENABLE1 */
	inb(ES1688P(chip, ENABLE0));	/* ENABLE0 */

	अगर (snd_es1688_reset(chip) < 0) अणु
		snd_prपूर्णांकdd("ESS: [0x%lx] reset failed... 0x%x\n", chip->port, inb(ES1688P(chip, READ)));
		spin_unlock_irqrestore(&chip->reg_lock, flags);
		वापस -ENODEV;
	पूर्ण
	snd_es1688_dsp_command(chip, 0xe7);	/* वापस identअगरication */

	क्रम (i = 1000, major = minor = 0; i; i--) अणु
		अगर (inb(ES1688P(chip, DATA_AVAIL)) & 0x80) अणु
			अगर (major == 0) अणु
				major = inb(ES1688P(chip, READ));
			पूर्ण अन्यथा अणु
				minor = inb(ES1688P(chip, READ));
			पूर्ण
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&chip->reg_lock, flags);

	snd_prपूर्णांकdd("ESS: [0x%lx] found.. major = 0x%x, minor = 0x%x\n", chip->port, major, minor);

	chip->version = (major << 8) | minor;
	अगर (!chip->version)
		वापस -ENODEV;	/* probably SB */

	चयन (chip->version & 0xfff0) अणु
	हाल 0x4880:
		snd_prपूर्णांकk(KERN_ERR "[0x%lx] ESS: AudioDrive ES488 detected, "
			   "but driver is in another place\n", chip->port);
		वापस -ENODEV;
	हाल 0x6880:
		अवरोध;
	शेष:
		snd_prपूर्णांकk(KERN_ERR "[0x%lx] ESS: unknown AudioDrive chip "
			   "with version 0x%x (Jazz16 soundcard?)\n",
			   chip->port, chip->version);
		वापस -ENODEV;
	पूर्ण

	spin_lock_irqsave(&chip->reg_lock, flags);
	snd_es1688_ग_लिखो(chip, 0xb1, 0x10);	/* disable IRQ */
	snd_es1688_ग_लिखो(chip, 0xb2, 0x00);	/* disable DMA */
	spin_unlock_irqrestore(&chip->reg_lock, flags);

	/* enable joystick, but disable OPL3 */
	spin_lock_irqsave(&chip->mixer_lock, flags);
	snd_es1688_mixer_ग_लिखो(chip, 0x40, 0x01);
	spin_unlock_irqrestore(&chip->mixer_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1688_init(काष्ठा snd_es1688 * chip, पूर्णांक enable)
अणु
	अटल स्थिर पूर्णांक irqs[16] = अणु-1, -1, 0, -1, -1, 1, -1, 2, -1, 0, 3, -1, -1, -1, -1, -1पूर्ण;
	अचिन्हित दीर्घ flags;
	पूर्णांक cfg, irq_bits, dma, dma_bits, पंचांगp, पंचांगp1;

	/* ok.. setup MPU-401 port and joystick and OPL3 */
	cfg = 0x01;		/* enable joystick, but disable OPL3 */
	अगर (enable && chip->mpu_port >= 0x300 && chip->mpu_irq > 0 && chip->hardware != ES1688_HW_688) अणु
		पंचांगp = (chip->mpu_port & 0x0f0) >> 4;
		अगर (पंचांगp <= 3) अणु
			चयन (chip->mpu_irq) अणु
			हाल 9:
				पंचांगp1 = 4;
				अवरोध;
			हाल 5:
				पंचांगp1 = 5;
				अवरोध;
			हाल 7:
				पंचांगp1 = 6;
				अवरोध;
			हाल 10:
				पंचांगp1 = 7;
				अवरोध;
			शेष:
				पंचांगp1 = 0;
			पूर्ण
			अगर (पंचांगp1) अणु
				cfg |= (पंचांगp << 3) | (पंचांगp1 << 5);
			पूर्ण
		पूर्ण
	पूर्ण
#अगर 0
	snd_prपूर्णांकk(KERN_DEBUG "mpu cfg = 0x%x\n", cfg);
#पूर्ण_अगर
	spin_lock_irqsave(&chip->reg_lock, flags);
	snd_es1688_mixer_ग_लिखो(chip, 0x40, cfg);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	/* --- */
	spin_lock_irqsave(&chip->reg_lock, flags);
	snd_es1688_पढ़ो(chip, 0xb1);
	snd_es1688_पढ़ो(chip, 0xb2);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	अगर (enable) अणु
		cfg = 0xf0;	/* enable only DMA counter पूर्णांकerrupt */
		irq_bits = irqs[chip->irq & 0x0f];
		अगर (irq_bits < 0) अणु
			snd_prपूर्णांकk(KERN_ERR "[0x%lx] ESS: bad IRQ %d "
				   "for ES1688 chip!!\n",
				   chip->port, chip->irq);
#अगर 0
			irq_bits = 0;
			cfg = 0x10;
#पूर्ण_अगर
			वापस -EINVAL;
		पूर्ण
		spin_lock_irqsave(&chip->reg_lock, flags);
		snd_es1688_ग_लिखो(chip, 0xb1, cfg | (irq_bits << 2));
		spin_unlock_irqrestore(&chip->reg_lock, flags);
		cfg = 0xf0;	/* extended mode DMA enable */
		dma = chip->dma8;
		अगर (dma > 3 || dma == 2) अणु
			snd_prपूर्णांकk(KERN_ERR "[0x%lx] ESS: bad DMA channel %d "
				   "for ES1688 chip!!\n", chip->port, dma);
#अगर 0
			dma_bits = 0;
			cfg = 0x00;	/* disable all DMA */
#पूर्ण_अगर
			वापस -EINVAL;
		पूर्ण अन्यथा अणु
			dma_bits = dma;
			अगर (dma != 3)
				dma_bits++;
		पूर्ण
		spin_lock_irqsave(&chip->reg_lock, flags);
		snd_es1688_ग_लिखो(chip, 0xb2, cfg | (dma_bits << 2));
		spin_unlock_irqrestore(&chip->reg_lock, flags);
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(&chip->reg_lock, flags);
		snd_es1688_ग_लिखो(chip, 0xb1, 0x10);	/* disable IRQ */
		snd_es1688_ग_लिखो(chip, 0xb2, 0x00);	/* disable DMA */
		spin_unlock_irqrestore(&chip->reg_lock, flags);
	पूर्ण
	spin_lock_irqsave(&chip->reg_lock, flags);
	snd_es1688_पढ़ो(chip, 0xb1);
	snd_es1688_पढ़ो(chip, 0xb2);
	snd_es1688_reset(chip);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस 0;
पूर्ण

/*

 */

अटल स्थिर काष्ठा snd_ratnum घड़ीs[2] = अणु
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

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_ratnums hw_स्थिरraपूर्णांकs_घड़ीs  = अणु
	.nrats = 2,
	.rats = घड़ीs,
पूर्ण;

अटल व्योम snd_es1688_set_rate(काष्ठा snd_es1688 *chip, काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित पूर्णांक bits, भागider;

	अगर (runसमय->rate_num == घड़ीs[0].num)
		bits = 256 - runसमय->rate_den;
	अन्यथा
		bits = 128 - runसमय->rate_den;
	/* set filter रेजिस्टर */
	भागider = 256 - 7160000*20/(8*82*runसमय->rate);
	/* ग_लिखो result to hardware */
	snd_es1688_ग_लिखो(chip, 0xa1, bits);
	snd_es1688_ग_लिखो(chip, 0xa2, भागider);
पूर्ण

अटल पूर्णांक snd_es1688_trigger(काष्ठा snd_es1688 *chip, पूर्णांक cmd, अचिन्हित अक्षर value)
अणु
	पूर्णांक val;

	अगर (cmd == SNDRV_PCM_TRIGGER_STOP) अणु
		value = 0x00;
	पूर्ण अन्यथा अगर (cmd != SNDRV_PCM_TRIGGER_START) अणु
		वापस -EINVAL;
	पूर्ण
	spin_lock(&chip->reg_lock);
	chip->trigger_value = value;
	val = snd_es1688_पढ़ो(chip, 0xb8);
	अगर ((val < 0) || (val & 0x0f) == value) अणु
		spin_unlock(&chip->reg_lock);
		वापस -EINVAL;	/* something is wrong */
	पूर्ण
#अगर 0
	prपूर्णांकk(KERN_DEBUG "trigger: val = 0x%x, value = 0x%x\n", val, value);
	prपूर्णांकk(KERN_DEBUG "trigger: pointer = 0x%x\n",
	       snd_dma_poपूर्णांकer(chip->dma8, chip->dma_size));
#पूर्ण_अगर
	snd_es1688_ग_लिखो(chip, 0xb8, (val & 0xf0) | value);
	spin_unlock(&chip->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1688_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_es1688 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित पूर्णांक size = snd_pcm_lib_buffer_bytes(substream);
	अचिन्हित पूर्णांक count = snd_pcm_lib_period_bytes(substream);

	chip->dma_size = size;
	spin_lock_irqsave(&chip->reg_lock, flags);
	snd_es1688_reset(chip);
	snd_es1688_set_rate(chip, substream);
	snd_es1688_ग_लिखो(chip, 0xb8, 4);	/* स्वतः init DMA mode */
	snd_es1688_ग_लिखो(chip, 0xa8, (snd_es1688_पढ़ो(chip, 0xa8) & ~0x03) | (3 - runसमय->channels));
	snd_es1688_ग_लिखो(chip, 0xb9, 2);	/* demand mode (4 bytes/request) */
	अगर (runसमय->channels == 1) अणु
		अगर (snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 8) अणु
			/* 8. bit mono */
			snd_es1688_ग_लिखो(chip, 0xb6, 0x80);
			snd_es1688_ग_लिखो(chip, 0xb7, 0x51);
			snd_es1688_ग_लिखो(chip, 0xb7, 0xd0);
		पूर्ण अन्यथा अणु
			/* 16. bit mono */
			snd_es1688_ग_लिखो(chip, 0xb6, 0x00);
			snd_es1688_ग_लिखो(chip, 0xb7, 0x71);
			snd_es1688_ग_लिखो(chip, 0xb7, 0xf4);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 8) अणु
			/* 8. bit stereo */
			snd_es1688_ग_लिखो(chip, 0xb6, 0x80);
			snd_es1688_ग_लिखो(chip, 0xb7, 0x51);
			snd_es1688_ग_लिखो(chip, 0xb7, 0x98);
		पूर्ण अन्यथा अणु
			/* 16. bit stereo */
			snd_es1688_ग_लिखो(chip, 0xb6, 0x00);
			snd_es1688_ग_लिखो(chip, 0xb7, 0x71);
			snd_es1688_ग_लिखो(chip, 0xb7, 0xbc);
		पूर्ण
	पूर्ण
	snd_es1688_ग_लिखो(chip, 0xb1, (snd_es1688_पढ़ो(chip, 0xb1) & 0x0f) | 0x50);
	snd_es1688_ग_लिखो(chip, 0xb2, (snd_es1688_पढ़ो(chip, 0xb2) & 0x0f) | 0x50);
	snd_es1688_dsp_command(chip, ES1688_DSP_CMD_SPKON);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	/* --- */
	count = -count;
	snd_dma_program(chip->dma8, runसमय->dma_addr, size, DMA_MODE_WRITE | DMA_AUTOINIT);
	spin_lock_irqsave(&chip->reg_lock, flags);
	snd_es1688_ग_लिखो(chip, 0xa4, (अचिन्हित अक्षर) count);
	snd_es1688_ग_लिखो(chip, 0xa5, (अचिन्हित अक्षर) (count >> 8));
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1688_playback_trigger(काष्ठा snd_pcm_substream *substream,
				       पूर्णांक cmd)
अणु
	काष्ठा snd_es1688 *chip = snd_pcm_substream_chip(substream);
	वापस snd_es1688_trigger(chip, cmd, 0x05);
पूर्ण

अटल पूर्णांक snd_es1688_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_es1688 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित पूर्णांक size = snd_pcm_lib_buffer_bytes(substream);
	अचिन्हित पूर्णांक count = snd_pcm_lib_period_bytes(substream);

	chip->dma_size = size;
	spin_lock_irqsave(&chip->reg_lock, flags);
	snd_es1688_reset(chip);
	snd_es1688_set_rate(chip, substream);
	snd_es1688_dsp_command(chip, ES1688_DSP_CMD_SPKOFF);
	snd_es1688_ग_लिखो(chip, 0xb8, 0x0e);	/* स्वतः init DMA mode */
	snd_es1688_ग_लिखो(chip, 0xa8, (snd_es1688_पढ़ो(chip, 0xa8) & ~0x03) | (3 - runसमय->channels));
	snd_es1688_ग_लिखो(chip, 0xb9, 2);	/* demand mode (4 bytes/request) */
	अगर (runसमय->channels == 1) अणु
		अगर (snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 8) अणु
			/* 8. bit mono */
			snd_es1688_ग_लिखो(chip, 0xb7, 0x51);
			snd_es1688_ग_लिखो(chip, 0xb7, 0xd0);
		पूर्ण अन्यथा अणु
			/* 16. bit mono */
			snd_es1688_ग_लिखो(chip, 0xb7, 0x71);
			snd_es1688_ग_लिखो(chip, 0xb7, 0xf4);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 8) अणु
			/* 8. bit stereo */
			snd_es1688_ग_लिखो(chip, 0xb7, 0x51);
			snd_es1688_ग_लिखो(chip, 0xb7, 0x98);
		पूर्ण अन्यथा अणु
			/* 16. bit stereo */
			snd_es1688_ग_लिखो(chip, 0xb7, 0x71);
			snd_es1688_ग_लिखो(chip, 0xb7, 0xbc);
		पूर्ण
	पूर्ण
	snd_es1688_ग_लिखो(chip, 0xb1, (snd_es1688_पढ़ो(chip, 0xb1) & 0x0f) | 0x50);
	snd_es1688_ग_लिखो(chip, 0xb2, (snd_es1688_पढ़ो(chip, 0xb2) & 0x0f) | 0x50);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	/* --- */
	count = -count;
	snd_dma_program(chip->dma8, runसमय->dma_addr, size, DMA_MODE_READ | DMA_AUTOINIT);
	spin_lock_irqsave(&chip->reg_lock, flags);
	snd_es1688_ग_लिखो(chip, 0xa4, (अचिन्हित अक्षर) count);
	snd_es1688_ग_लिखो(chip, 0xa5, (अचिन्हित अक्षर) (count >> 8));
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1688_capture_trigger(काष्ठा snd_pcm_substream *substream,
				      पूर्णांक cmd)
अणु
	काष्ठा snd_es1688 *chip = snd_pcm_substream_chip(substream);
	वापस snd_es1688_trigger(chip, cmd, 0x0f);
पूर्ण

अटल irqवापस_t snd_es1688_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा snd_es1688 *chip = dev_id;

	अगर (chip->trigger_value == 0x05)	/* ok.. playback is active */
		snd_pcm_period_elapsed(chip->playback_substream);
	अगर (chip->trigger_value == 0x0f)	/* ok.. capture is active */
		snd_pcm_period_elapsed(chip->capture_substream);

	inb(ES1688P(chip, DATA_AVAIL));	/* ack पूर्णांकerrupt */
	वापस IRQ_HANDLED;
पूर्ण

अटल snd_pcm_uframes_t snd_es1688_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_es1688 *chip = snd_pcm_substream_chip(substream);
	माप_प्रकार ptr;
	
	अगर (chip->trigger_value != 0x05)
		वापस 0;
	ptr = snd_dma_poपूर्णांकer(chip->dma8, chip->dma_size);
	वापस bytes_to_frames(substream->runसमय, ptr);
पूर्ण

अटल snd_pcm_uframes_t snd_es1688_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_es1688 *chip = snd_pcm_substream_chip(substream);
	माप_प्रकार ptr;
	
	अगर (chip->trigger_value != 0x0f)
		वापस 0;
	ptr = snd_dma_poपूर्णांकer(chip->dma8, chip->dma_size);
	वापस bytes_to_frames(substream->runसमय, ptr);
पूर्ण

/*

 */

अटल स्थिर काष्ठा snd_pcm_hardware snd_es1688_playback =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =		SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE,
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

अटल स्थिर काष्ठा snd_pcm_hardware snd_es1688_capture =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =		SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE,
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

/*

 */

अटल पूर्णांक snd_es1688_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_es1688 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	अगर (chip->capture_substream != शून्य)
		वापस -EAGAIN;
	chip->playback_substream = substream;
	runसमय->hw = snd_es1688_playback;
	snd_pcm_hw_स्थिरraपूर्णांक_ratnums(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				      &hw_स्थिरraपूर्णांकs_घड़ीs);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1688_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_es1688 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	अगर (chip->playback_substream != शून्य)
		वापस -EAGAIN;
	chip->capture_substream = substream;
	runसमय->hw = snd_es1688_capture;
	snd_pcm_hw_स्थिरraपूर्णांक_ratnums(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				      &hw_स्थिरraपूर्णांकs_घड़ीs);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1688_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_es1688 *chip = snd_pcm_substream_chip(substream);

	chip->playback_substream = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1688_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_es1688 *chip = snd_pcm_substream_chip(substream);

	chip->capture_substream = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1688_मुक्त(काष्ठा snd_es1688 *chip)
अणु
	अगर (chip->hardware != ES1688_HW_UNDEF)
		snd_es1688_init(chip, 0);
	release_and_मुक्त_resource(chip->res_port);
	अगर (chip->irq >= 0)
		मुक्त_irq(chip->irq, (व्योम *) chip);
	अगर (chip->dma8 >= 0) अणु
		disable_dma(chip->dma8);
		मुक्त_dma(chip->dma8);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1688_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_es1688 *chip = device->device_data;
	वापस snd_es1688_मुक्त(chip);
पूर्ण

अटल स्थिर अक्षर *snd_es1688_chip_id(काष्ठा snd_es1688 *chip)
अणु
	अटल अक्षर पंचांगp[16];
	प्र_लिखो(पंचांगp, "ES%s688 rev %i", chip->hardware == ES1688_HW_688 ? "" : "1", chip->version & 0x0f);
	वापस पंचांगp;
पूर्ण

पूर्णांक snd_es1688_create(काष्ठा snd_card *card,
		      काष्ठा snd_es1688 *chip,
		      अचिन्हित दीर्घ port,
		      अचिन्हित दीर्घ mpu_port,
		      पूर्णांक irq,
		      पूर्णांक mpu_irq,
		      पूर्णांक dma8,
		      अचिन्हित लघु hardware)
अणु
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =	snd_es1688_dev_मुक्त,
	पूर्ण;
                                
	पूर्णांक err;

	अगर (chip == शून्य)
		वापस -ENOMEM;
	chip->irq = -1;
	chip->dma8 = -1;
	chip->hardware = ES1688_HW_UNDEF;
	
	chip->res_port = request_region(port + 4, 12, "ES1688");
	अगर (chip->res_port == शून्य) अणु
		snd_prपूर्णांकk(KERN_ERR "es1688: can't grab port 0x%lx\n", port + 4);
		err = -EBUSY;
		जाओ निकास;
	पूर्ण

	err = request_irq(irq, snd_es1688_पूर्णांकerrupt, 0, "ES1688", (व्योम *) chip);
	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "es1688: can't grab IRQ %d\n", irq);
		जाओ निकास;
	पूर्ण

	chip->irq = irq;
	card->sync_irq = chip->irq;
	err = request_dma(dma8, "ES1688");

	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "es1688: can't grab DMA8 %d\n", dma8);
		जाओ निकास;
	पूर्ण
	chip->dma8 = dma8;

	spin_lock_init(&chip->reg_lock);
	spin_lock_init(&chip->mixer_lock);
	chip->port = port;
	mpu_port &= ~0x000f;
	अगर (mpu_port < 0x300 || mpu_port > 0x330)
		mpu_port = 0;
	chip->mpu_port = mpu_port;
	chip->mpu_irq = mpu_irq;
	chip->hardware = hardware;

	err = snd_es1688_probe(chip);
	अगर (err < 0)
		जाओ निकास;

	err = snd_es1688_init(chip, 1);
	अगर (err < 0)
		जाओ निकास;

	/* Register device */
	err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops);
निकास:
	अगर (err)
		snd_es1688_मुक्त(chip);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_es1688_playback_ops = अणु
	.खोलो =			snd_es1688_playback_खोलो,
	.बंद =		snd_es1688_playback_बंद,
	.prepare =		snd_es1688_playback_prepare,
	.trigger =		snd_es1688_playback_trigger,
	.poपूर्णांकer =		snd_es1688_playback_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_es1688_capture_ops = अणु
	.खोलो =			snd_es1688_capture_खोलो,
	.बंद =		snd_es1688_capture_बंद,
	.prepare =		snd_es1688_capture_prepare,
	.trigger =		snd_es1688_capture_trigger,
	.poपूर्णांकer =		snd_es1688_capture_poपूर्णांकer,
पूर्ण;

पूर्णांक snd_es1688_pcm(काष्ठा snd_card *card, काष्ठा snd_es1688 *chip, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	err = snd_pcm_new(card, "ESx688", device, 1, 1, &pcm);
	अगर (err < 0)
		वापस err;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_es1688_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_es1688_capture_ops);

	pcm->निजी_data = chip;
	pcm->info_flags = SNDRV_PCM_INFO_HALF_DUPLEX;
	म_नकल(pcm->name, snd_es1688_chip_id(chip));
	chip->pcm = pcm;

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV, card->dev,
				       64*1024, 64*1024);
	वापस 0;
पूर्ण

/*
 *  MIXER part
 */

अटल पूर्णांक snd_es1688_info_mux(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[8] = अणु
		"Mic", "Mic Master", "CD", "AOUT",
		"Mic1", "Mix", "Line", "Master"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 8, texts);
पूर्ण

अटल पूर्णांक snd_es1688_get_mux(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_es1688 *chip = snd_kcontrol_chip(kcontrol);
	ucontrol->value.क्रमागतerated.item[0] = snd_es1688_mixer_पढ़ो(chip, ES1688_REC_DEV) & 7;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1688_put_mux(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_es1688 *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर oval, nval;
	पूर्णांक change;
	
	अगर (ucontrol->value.क्रमागतerated.item[0] > 8)
		वापस -EINVAL;
	spin_lock_irqsave(&chip->reg_lock, flags);
	oval = snd_es1688_mixer_पढ़ो(chip, ES1688_REC_DEV);
	nval = (ucontrol->value.क्रमागतerated.item[0] & 7) | (oval & ~15);
	change = nval != oval;
	अगर (change)
		snd_es1688_mixer_ग_लिखो(chip, ES1688_REC_DEV, nval);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस change;
पूर्ण

#घोषणा ES1688_SINGLE(xname, xindex, reg, shअगरt, mask, invert) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .info = snd_es1688_info_single, \
  .get = snd_es1688_get_single, .put = snd_es1688_put_single, \
  .निजी_value = reg | (shअगरt << 8) | (mask << 16) | (invert << 24) पूर्ण

अटल पूर्णांक snd_es1688_info_single(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;

	uinfo->type = mask == 1 ? SNDRV_CTL_ELEM_TYPE_BOOLEAN : SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = mask;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1688_get_single(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_es1688 *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 24) & 0xff;
	
	spin_lock_irqsave(&chip->reg_lock, flags);
	ucontrol->value.पूर्णांकeger.value[0] = (snd_es1688_mixer_पढ़ो(chip, reg) >> shअगरt) & mask;
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	अगर (invert)
		ucontrol->value.पूर्णांकeger.value[0] = mask - ucontrol->value.पूर्णांकeger.value[0];
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1688_put_single(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_es1688 *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 24) & 0xff;
	पूर्णांक change;
	अचिन्हित अक्षर oval, nval;
	
	nval = (ucontrol->value.पूर्णांकeger.value[0] & mask);
	अगर (invert)
		nval = mask - nval;
	nval <<= shअगरt;
	spin_lock_irqsave(&chip->reg_lock, flags);
	oval = snd_es1688_mixer_पढ़ो(chip, reg);
	nval = (oval & ~(mask << shअगरt)) | nval;
	change = nval != oval;
	अगर (change)
		snd_es1688_mixer_ग_लिखो(chip, reg, nval);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस change;
पूर्ण

#घोषणा ES1688_DOUBLE(xname, xindex, left_reg, right_reg, shअगरt_left, shअगरt_right, mask, invert) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .info = snd_es1688_info_द्विगुन, \
  .get = snd_es1688_get_द्विगुन, .put = snd_es1688_put_द्विगुन, \
  .निजी_value = left_reg | (right_reg << 8) | (shअगरt_left << 16) | (shअगरt_right << 19) | (mask << 24) | (invert << 22) पूर्ण

अटल पूर्णांक snd_es1688_info_द्विगुन(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक mask = (kcontrol->निजी_value >> 24) & 0xff;

	uinfo->type = mask == 1 ? SNDRV_CTL_ELEM_TYPE_BOOLEAN : SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = mask;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1688_get_द्विगुन(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_es1688 *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक left_reg = kcontrol->निजी_value & 0xff;
	पूर्णांक right_reg = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक shअगरt_left = (kcontrol->निजी_value >> 16) & 0x07;
	पूर्णांक shअगरt_right = (kcontrol->निजी_value >> 19) & 0x07;
	पूर्णांक mask = (kcontrol->निजी_value >> 24) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 22) & 1;
	अचिन्हित अक्षर left, right;
	
	spin_lock_irqsave(&chip->reg_lock, flags);
	अगर (left_reg < 0xa0)
		left = snd_es1688_mixer_पढ़ो(chip, left_reg);
	अन्यथा
		left = snd_es1688_पढ़ो(chip, left_reg);
	अगर (left_reg != right_reg) अणु
		अगर (right_reg < 0xa0) 
			right = snd_es1688_mixer_पढ़ो(chip, right_reg);
		अन्यथा
			right = snd_es1688_पढ़ो(chip, right_reg);
	पूर्ण अन्यथा
		right = left;
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	ucontrol->value.पूर्णांकeger.value[0] = (left >> shअगरt_left) & mask;
	ucontrol->value.पूर्णांकeger.value[1] = (right >> shअगरt_right) & mask;
	अगर (invert) अणु
		ucontrol->value.पूर्णांकeger.value[0] = mask - ucontrol->value.पूर्णांकeger.value[0];
		ucontrol->value.पूर्णांकeger.value[1] = mask - ucontrol->value.पूर्णांकeger.value[1];
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1688_put_द्विगुन(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_es1688 *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक left_reg = kcontrol->निजी_value & 0xff;
	पूर्णांक right_reg = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक shअगरt_left = (kcontrol->निजी_value >> 16) & 0x07;
	पूर्णांक shअगरt_right = (kcontrol->निजी_value >> 19) & 0x07;
	पूर्णांक mask = (kcontrol->निजी_value >> 24) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 22) & 1;
	पूर्णांक change;
	अचिन्हित अक्षर val1, val2, oval1, oval2;
	
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
		अगर (left_reg < 0xa0)
			oval1 = snd_es1688_mixer_पढ़ो(chip, left_reg);
		अन्यथा
			oval1 = snd_es1688_पढ़ो(chip, left_reg);
		अगर (right_reg < 0xa0)
			oval2 = snd_es1688_mixer_पढ़ो(chip, right_reg);
		अन्यथा
			oval2 = snd_es1688_पढ़ो(chip, right_reg);
		val1 = (oval1 & ~(mask << shअगरt_left)) | val1;
		val2 = (oval2 & ~(mask << shअगरt_right)) | val2;
		change = val1 != oval1 || val2 != oval2;
		अगर (change) अणु
			अगर (left_reg < 0xa0)
				snd_es1688_mixer_ग_लिखो(chip, left_reg, val1);
			अन्यथा
				snd_es1688_ग_लिखो(chip, left_reg, val1);
			अगर (right_reg < 0xa0)
				snd_es1688_mixer_ग_लिखो(chip, right_reg, val1);
			अन्यथा
				snd_es1688_ग_लिखो(chip, right_reg, val1);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (left_reg < 0xa0)
			oval1 = snd_es1688_mixer_पढ़ो(chip, left_reg);
		अन्यथा
			oval1 = snd_es1688_पढ़ो(chip, left_reg);
		val1 = (oval1 & ~((mask << shअगरt_left) | (mask << shअगरt_right))) | val1 | val2;
		change = val1 != oval1;
		अगर (change) अणु
			अगर (left_reg < 0xa0)
				snd_es1688_mixer_ग_लिखो(chip, left_reg, val1);
			अन्यथा
				snd_es1688_ग_लिखो(chip, left_reg, val1);
		पूर्ण
			
	पूर्ण
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_es1688_controls[] = अणु
ES1688_DOUBLE("Master Playback Volume", 0, ES1688_MASTER_DEV, ES1688_MASTER_DEV, 4, 0, 15, 0),
ES1688_DOUBLE("PCM Playback Volume", 0, ES1688_PCM_DEV, ES1688_PCM_DEV, 4, 0, 15, 0),
ES1688_DOUBLE("Line Playback Volume", 0, ES1688_LINE_DEV, ES1688_LINE_DEV, 4, 0, 15, 0),
ES1688_DOUBLE("CD Playback Volume", 0, ES1688_CD_DEV, ES1688_CD_DEV, 4, 0, 15, 0),
ES1688_DOUBLE("FM Playback Volume", 0, ES1688_FM_DEV, ES1688_FM_DEV, 4, 0, 15, 0),
ES1688_DOUBLE("Mic Playback Volume", 0, ES1688_MIC_DEV, ES1688_MIC_DEV, 4, 0, 15, 0),
ES1688_DOUBLE("Aux Playback Volume", 0, ES1688_AUX_DEV, ES1688_AUX_DEV, 4, 0, 15, 0),
ES1688_SINGLE("Beep Playback Volume", 0, ES1688_SPEAKER_DEV, 0, 7, 0),
ES1688_DOUBLE("Capture Volume", 0, ES1688_RECLEV_DEV, ES1688_RECLEV_DEV, 4, 0, 15, 0),
ES1688_SINGLE("Capture Switch", 0, ES1688_REC_DEV, 4, 1, 1),
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Capture Source",
	.info = snd_es1688_info_mux,
	.get = snd_es1688_get_mux,
	.put = snd_es1688_put_mux,
पूर्ण,
पूर्ण;

#घोषणा ES1688_INIT_TABLE_SIZE (माप(snd_es1688_init_table)/2)

अटल स्थिर अचिन्हित अक्षर snd_es1688_init_table[][2] = अणु
	अणु ES1688_MASTER_DEV, 0 पूर्ण,
	अणु ES1688_PCM_DEV, 0 पूर्ण,
	अणु ES1688_LINE_DEV, 0 पूर्ण,
	अणु ES1688_CD_DEV, 0 पूर्ण,
	अणु ES1688_FM_DEV, 0 पूर्ण,
	अणु ES1688_MIC_DEV, 0 पूर्ण,
	अणु ES1688_AUX_DEV, 0 पूर्ण,
	अणु ES1688_SPEAKER_DEV, 0 पूर्ण,
	अणु ES1688_RECLEV_DEV, 0 पूर्ण,
	अणु ES1688_REC_DEV, 0x17 पूर्ण
पूर्ण;
                                        
पूर्णांक snd_es1688_mixer(काष्ठा snd_card *card, काष्ठा snd_es1688 *chip)
अणु
	अचिन्हित पूर्णांक idx;
	पूर्णांक err;
	अचिन्हित अक्षर reg, val;

	अगर (snd_BUG_ON(!chip || !card))
		वापस -EINVAL;

	म_नकल(card->mixername, snd_es1688_chip_id(chip));

	क्रम (idx = 0; idx < ARRAY_SIZE(snd_es1688_controls); idx++) अणु
		अगर ((err = snd_ctl_add(card, snd_ctl_new1(&snd_es1688_controls[idx], chip))) < 0)
			वापस err;
	पूर्ण
	क्रम (idx = 0; idx < ES1688_INIT_TABLE_SIZE; idx++) अणु
		reg = snd_es1688_init_table[idx][0];
		val = snd_es1688_init_table[idx][1];
		अगर (reg < 0xa0)
			snd_es1688_mixer_ग_लिखो(chip, reg, val);
		अन्यथा
			snd_es1688_ग_लिखो(chip, reg, val);
	पूर्ण
	वापस 0;
पूर्ण

EXPORT_SYMBOL(snd_es1688_mixer_ग_लिखो);
EXPORT_SYMBOL(snd_es1688_create);
EXPORT_SYMBOL(snd_es1688_pcm);
EXPORT_SYMBOL(snd_es1688_mixer);
