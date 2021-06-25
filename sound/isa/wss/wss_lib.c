<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *  Routines क्रम control of CS4231(A)/CS4232/InterWave & compatible chips
 *
 *  Bugs:
 *     - someबार record brokes playback with WSS portion of
 *       Yamaha OPL3-SA3 chip
 *     - CS4231 (GUS MAX) - still trouble with occasional noises
 *			  - broken initialization?
 */

#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <sound/core.h>
#समावेश <sound/wss.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/tlv.h>

#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/irq.h>

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("Routines for control of CS4231(A)/CS4232/InterWave & compatible chips");
MODULE_LICENSE("GPL");

#अगर 0
#घोषणा SNDRV_DEBUG_MCE
#पूर्ण_अगर

/*
 *  Some variables
 */

अटल स्थिर अचिन्हित अक्षर freq_bits[14] = अणु
	/* 5510 */	0x00 | CS4231_XTAL2,
	/* 6620 */	0x0E | CS4231_XTAL2,
	/* 8000 */	0x00 | CS4231_XTAL1,
	/* 9600 */	0x0E | CS4231_XTAL1,
	/* 11025 */	0x02 | CS4231_XTAL2,
	/* 16000 */	0x02 | CS4231_XTAL1,
	/* 18900 */	0x04 | CS4231_XTAL2,
	/* 22050 */	0x06 | CS4231_XTAL2,
	/* 27042 */	0x04 | CS4231_XTAL1,
	/* 32000 */	0x06 | CS4231_XTAL1,
	/* 33075 */	0x0C | CS4231_XTAL2,
	/* 37800 */	0x08 | CS4231_XTAL2,
	/* 44100 */	0x0A | CS4231_XTAL2,
	/* 48000 */	0x0C | CS4231_XTAL1
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक rates[14] = अणु
	5510, 6620, 8000, 9600, 11025, 16000, 18900, 22050,
	27042, 32000, 33075, 37800, 44100, 48000
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list hw_स्थिरraपूर्णांकs_rates = अणु
	.count = ARRAY_SIZE(rates),
	.list = rates,
	.mask = 0,
पूर्ण;

अटल पूर्णांक snd_wss_xrate(काष्ठा snd_pcm_runसमय *runसमय)
अणु
	वापस snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
					  &hw_स्थिरraपूर्णांकs_rates);
पूर्ण

अटल स्थिर अचिन्हित अक्षर snd_wss_original_image[32] =
अणु
	0x00,			/* 00/00 - lic */
	0x00,			/* 01/01 - ric */
	0x9f,			/* 02/02 - la1ic */
	0x9f,			/* 03/03 - ra1ic */
	0x9f,			/* 04/04 - la2ic */
	0x9f,			/* 05/05 - ra2ic */
	0xbf,			/* 06/06 - loc */
	0xbf,			/* 07/07 - roc */
	0x20,			/* 08/08 - pdfr */
	CS4231_AUTOCALIB,	/* 09/09 - ic */
	0x00,			/* 0a/10 - pc */
	0x00,			/* 0b/11 - ti */
	CS4231_MODE2,		/* 0c/12 - mi */
	0xfc,			/* 0d/13 - lbc */
	0x00,			/* 0e/14 - pbru */
	0x00,			/* 0f/15 - pbrl */
	0x80,			/* 10/16 - afei */
	0x01,			/* 11/17 - afeii */
	0x9f,			/* 12/18 - llic */
	0x9f,			/* 13/19 - rlic */
	0x00,			/* 14/20 - tlb */
	0x00,			/* 15/21 - thb */
	0x00,			/* 16/22 - la3mic/reserved */
	0x00,			/* 17/23 - ra3mic/reserved */
	0x00,			/* 18/24 - afs */
	0x00,			/* 19/25 - lamoc/version */
	0xcf,			/* 1a/26 - mioc */
	0x00,			/* 1b/27 - ramoc/reserved */
	0x20,			/* 1c/28 - cdfr */
	0x00,			/* 1d/29 - res4 */
	0x00,			/* 1e/30 - cbru */
	0x00,			/* 1f/31 - cbrl */
पूर्ण;

अटल स्थिर अचिन्हित अक्षर snd_opti93x_original_image[32] =
अणु
	0x00,		/* 00/00 - l_mixout_outctrl */
	0x00,		/* 01/01 - r_mixout_outctrl */
	0x88,		/* 02/02 - l_cd_inctrl */
	0x88,		/* 03/03 - r_cd_inctrl */
	0x88,		/* 04/04 - l_a1/fm_inctrl */
	0x88,		/* 05/05 - r_a1/fm_inctrl */
	0x80,		/* 06/06 - l_dac_inctrl */
	0x80,		/* 07/07 - r_dac_inctrl */
	0x00,		/* 08/08 - ply_dataक्रमm_reg */
	0x00,		/* 09/09 - अगर_conf */
	0x00,		/* 0a/10 - pin_ctrl */
	0x00,		/* 0b/11 - err_init_reg */
	0x0a,		/* 0c/12 - id_reg */
	0x00,		/* 0d/13 - reserved */
	0x00,		/* 0e/14 - ply_upcount_reg */
	0x00,		/* 0f/15 - ply_lowcount_reg */
	0x88,		/* 10/16 - reserved/l_a1_inctrl */
	0x88,		/* 11/17 - reserved/r_a1_inctrl */
	0x88,		/* 12/18 - l_line_inctrl */
	0x88,		/* 13/19 - r_line_inctrl */
	0x88,		/* 14/20 - l_mic_inctrl */
	0x88,		/* 15/21 - r_mic_inctrl */
	0x80,		/* 16/22 - l_out_outctrl */
	0x80,		/* 17/23 - r_out_outctrl */
	0x00,		/* 18/24 - reserved */
	0x00,		/* 19/25 - reserved */
	0x00,		/* 1a/26 - reserved */
	0x00,		/* 1b/27 - reserved */
	0x00,		/* 1c/28 - cap_dataक्रमm_reg */
	0x00,		/* 1d/29 - reserved */
	0x00,		/* 1e/30 - cap_upcount_reg */
	0x00		/* 1f/31 - cap_lowcount_reg */
पूर्ण;

/*
 *  Basic I/O functions
 */

अटल अंतरभूत व्योम wss_outb(काष्ठा snd_wss *chip, u8 offset, u8 val)
अणु
	outb(val, chip->port + offset);
पूर्ण

अटल अंतरभूत u8 wss_inb(काष्ठा snd_wss *chip, u8 offset)
अणु
	वापस inb(chip->port + offset);
पूर्ण

अटल व्योम snd_wss_रुको(काष्ठा snd_wss *chip)
अणु
	पूर्णांक समयout;

	क्रम (समयout = 250;
	     समयout > 0 && (wss_inb(chip, CS4231P(REGSEL)) & CS4231_INIT);
	     समयout--)
		udelay(100);
पूर्ण

अटल व्योम snd_wss_करोut(काष्ठा snd_wss *chip, अचिन्हित अक्षर reg,
			 अचिन्हित अक्षर value)
अणु
	पूर्णांक समयout;

	क्रम (समयout = 250;
	     समयout > 0 && (wss_inb(chip, CS4231P(REGSEL)) & CS4231_INIT);
	     समयout--)
		udelay(10);
	wss_outb(chip, CS4231P(REGSEL), chip->mce_bit | reg);
	wss_outb(chip, CS4231P(REG), value);
	mb();
पूर्ण

व्योम snd_wss_out(काष्ठा snd_wss *chip, अचिन्हित अक्षर reg, अचिन्हित अक्षर value)
अणु
	snd_wss_रुको(chip);
#अगर_घोषित CONFIG_SND_DEBUG
	अगर (wss_inb(chip, CS4231P(REGSEL)) & CS4231_INIT)
		snd_prपूर्णांकk(KERN_DEBUG "out: auto calibration time out "
			   "- reg = 0x%x, value = 0x%x\n", reg, value);
#पूर्ण_अगर
	wss_outb(chip, CS4231P(REGSEL), chip->mce_bit | reg);
	wss_outb(chip, CS4231P(REG), value);
	chip->image[reg] = value;
	mb();
	snd_prपूर्णांकdd("codec out - reg 0x%x = 0x%x\n",
			chip->mce_bit | reg, value);
पूर्ण
EXPORT_SYMBOL(snd_wss_out);

अचिन्हित अक्षर snd_wss_in(काष्ठा snd_wss *chip, अचिन्हित अक्षर reg)
अणु
	snd_wss_रुको(chip);
#अगर_घोषित CONFIG_SND_DEBUG
	अगर (wss_inb(chip, CS4231P(REGSEL)) & CS4231_INIT)
		snd_prपूर्णांकk(KERN_DEBUG "in: auto calibration time out "
			   "- reg = 0x%x\n", reg);
#पूर्ण_अगर
	wss_outb(chip, CS4231P(REGSEL), chip->mce_bit | reg);
	mb();
	वापस wss_inb(chip, CS4231P(REG));
पूर्ण
EXPORT_SYMBOL(snd_wss_in);

व्योम snd_cs4236_ext_out(काष्ठा snd_wss *chip, अचिन्हित अक्षर reg,
			अचिन्हित अक्षर val)
अणु
	wss_outb(chip, CS4231P(REGSEL), chip->mce_bit | 0x17);
	wss_outb(chip, CS4231P(REG),
		 reg | (chip->image[CS4236_EXT_REG] & 0x01));
	wss_outb(chip, CS4231P(REG), val);
	chip->eimage[CS4236_REG(reg)] = val;
#अगर 0
	prपूर्णांकk(KERN_DEBUG "ext out : reg = 0x%x, val = 0x%x\n", reg, val);
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(snd_cs4236_ext_out);

अचिन्हित अक्षर snd_cs4236_ext_in(काष्ठा snd_wss *chip, अचिन्हित अक्षर reg)
अणु
	wss_outb(chip, CS4231P(REGSEL), chip->mce_bit | 0x17);
	wss_outb(chip, CS4231P(REG),
		 reg | (chip->image[CS4236_EXT_REG] & 0x01));
#अगर 1
	वापस wss_inb(chip, CS4231P(REG));
#अन्यथा
	अणु
		अचिन्हित अक्षर res;
		res = wss_inb(chip, CS4231P(REG));
		prपूर्णांकk(KERN_DEBUG "ext in : reg = 0x%x, val = 0x%x\n",
		       reg, res);
		वापस res;
	पूर्ण
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(snd_cs4236_ext_in);

#अगर 0

अटल व्योम snd_wss_debug(काष्ठा snd_wss *chip)
अणु
	prपूर्णांकk(KERN_DEBUG
		"CS4231 REGS:      INDEX = 0x%02x  "
		"                 STATUS = 0x%02x\n",
					wss_inb(chip, CS4231P(REGSEL)),
					wss_inb(chip, CS4231P(STATUS)));
	prपूर्णांकk(KERN_DEBUG
		"  0x00: left input      = 0x%02x  "
		"  0x10: alt 1 (CFIG 2)  = 0x%02x\n",
					snd_wss_in(chip, 0x00),
					snd_wss_in(chip, 0x10));
	prपूर्णांकk(KERN_DEBUG
		"  0x01: right input     = 0x%02x  "
		"  0x11: alt 2 (CFIG 3)  = 0x%02x\n",
					snd_wss_in(chip, 0x01),
					snd_wss_in(chip, 0x11));
	prपूर्णांकk(KERN_DEBUG
		"  0x02: GF1 left input  = 0x%02x  "
		"  0x12: left line in    = 0x%02x\n",
					snd_wss_in(chip, 0x02),
					snd_wss_in(chip, 0x12));
	prपूर्णांकk(KERN_DEBUG
		"  0x03: GF1 right input = 0x%02x  "
		"  0x13: right line in   = 0x%02x\n",
					snd_wss_in(chip, 0x03),
					snd_wss_in(chip, 0x13));
	prपूर्णांकk(KERN_DEBUG
		"  0x04: CD left input   = 0x%02x  "
		"  0x14: timer low       = 0x%02x\n",
					snd_wss_in(chip, 0x04),
					snd_wss_in(chip, 0x14));
	prपूर्णांकk(KERN_DEBUG
		"  0x05: CD right input  = 0x%02x  "
		"  0x15: timer high      = 0x%02x\n",
					snd_wss_in(chip, 0x05),
					snd_wss_in(chip, 0x15));
	prपूर्णांकk(KERN_DEBUG
		"  0x06: left output     = 0x%02x  "
		"  0x16: left MIC (PnP)  = 0x%02x\n",
					snd_wss_in(chip, 0x06),
					snd_wss_in(chip, 0x16));
	prपूर्णांकk(KERN_DEBUG
		"  0x07: right output    = 0x%02x  "
		"  0x17: right MIC (PnP) = 0x%02x\n",
					snd_wss_in(chip, 0x07),
					snd_wss_in(chip, 0x17));
	prपूर्णांकk(KERN_DEBUG
		"  0x08: playback format = 0x%02x  "
		"  0x18: IRQ status      = 0x%02x\n",
					snd_wss_in(chip, 0x08),
					snd_wss_in(chip, 0x18));
	prपूर्णांकk(KERN_DEBUG
		"  0x09: iface (CFIG 1)  = 0x%02x  "
		"  0x19: left line out   = 0x%02x\n",
					snd_wss_in(chip, 0x09),
					snd_wss_in(chip, 0x19));
	prपूर्णांकk(KERN_DEBUG
		"  0x0a: pin control     = 0x%02x  "
		"  0x1a: mono control    = 0x%02x\n",
					snd_wss_in(chip, 0x0a),
					snd_wss_in(chip, 0x1a));
	prपूर्णांकk(KERN_DEBUG
		"  0x0b: init & status   = 0x%02x  "
		"  0x1b: right line out  = 0x%02x\n",
					snd_wss_in(chip, 0x0b),
					snd_wss_in(chip, 0x1b));
	prपूर्णांकk(KERN_DEBUG
		"  0x0c: revision & mode = 0x%02x  "
		"  0x1c: record format   = 0x%02x\n",
					snd_wss_in(chip, 0x0c),
					snd_wss_in(chip, 0x1c));
	prपूर्णांकk(KERN_DEBUG
		"  0x0d: loopback        = 0x%02x  "
		"  0x1d: var freq (PnP)  = 0x%02x\n",
					snd_wss_in(chip, 0x0d),
					snd_wss_in(chip, 0x1d));
	prपूर्णांकk(KERN_DEBUG
		"  0x0e: ply upr count   = 0x%02x  "
		"  0x1e: ply lwr count   = 0x%02x\n",
					snd_wss_in(chip, 0x0e),
					snd_wss_in(chip, 0x1e));
	prपूर्णांकk(KERN_DEBUG
		"  0x0f: rec upr count   = 0x%02x  "
		"  0x1f: rec lwr count   = 0x%02x\n",
					snd_wss_in(chip, 0x0f),
					snd_wss_in(chip, 0x1f));
पूर्ण

#पूर्ण_अगर

/*
 *  CS4231 detection / MCE routines
 */

अटल व्योम snd_wss_busy_रुको(काष्ठा snd_wss *chip)
अणु
	पूर्णांक समयout;

	/* huh.. looks like this sequence is proper क्रम CS4231A chip (GUS MAX) */
	क्रम (समयout = 5; समयout > 0; समयout--)
		wss_inb(chip, CS4231P(REGSEL));
	/* end of cleanup sequence */
	क्रम (समयout = 25000;
	     समयout > 0 && (wss_inb(chip, CS4231P(REGSEL)) & CS4231_INIT);
	     समयout--)
		udelay(10);
पूर्ण

व्योम snd_wss_mce_up(काष्ठा snd_wss *chip)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक समयout;

	snd_wss_रुको(chip);
#अगर_घोषित CONFIG_SND_DEBUG
	अगर (wss_inb(chip, CS4231P(REGSEL)) & CS4231_INIT)
		snd_prपूर्णांकk(KERN_DEBUG
			   "mce_up - auto calibration time out (0)\n");
#पूर्ण_अगर
	spin_lock_irqsave(&chip->reg_lock, flags);
	chip->mce_bit |= CS4231_MCE;
	समयout = wss_inb(chip, CS4231P(REGSEL));
	अगर (समयout == 0x80)
		snd_prपूर्णांकk(KERN_DEBUG "mce_up [0x%lx]: "
			   "serious init problem - codec still busy\n",
			   chip->port);
	अगर (!(समयout & CS4231_MCE))
		wss_outb(chip, CS4231P(REGSEL),
			 chip->mce_bit | (समयout & 0x1f));
	spin_unlock_irqrestore(&chip->reg_lock, flags);
पूर्ण
EXPORT_SYMBOL(snd_wss_mce_up);

व्योम snd_wss_mce_करोwn(काष्ठा snd_wss *chip)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ end_समय;
	पूर्णांक समयout;
	पूर्णांक hw_mask = WSS_HW_CS4231_MASK | WSS_HW_CS4232_MASK | WSS_HW_AD1848;

	snd_wss_busy_रुको(chip);

#अगर_घोषित CONFIG_SND_DEBUG
	अगर (wss_inb(chip, CS4231P(REGSEL)) & CS4231_INIT)
		snd_prपूर्णांकk(KERN_DEBUG "mce_down [0x%lx] - "
			   "auto calibration time out (0)\n",
			   (दीर्घ)CS4231P(REGSEL));
#पूर्ण_अगर
	spin_lock_irqsave(&chip->reg_lock, flags);
	chip->mce_bit &= ~CS4231_MCE;
	समयout = wss_inb(chip, CS4231P(REGSEL));
	wss_outb(chip, CS4231P(REGSEL), chip->mce_bit | (समयout & 0x1f));
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	अगर (समयout == 0x80)
		snd_prपूर्णांकk(KERN_DEBUG "mce_down [0x%lx]: "
			   "serious init problem - codec still busy\n",
			   chip->port);
	अगर ((समयout & CS4231_MCE) == 0 || !(chip->hardware & hw_mask))
		वापस;

	/*
	 * Wait क्रम (possible -- during init स्वतः-calibration may not be set)
	 * calibration process to start. Needs up to 5 sample periods on AD1848
	 * which at the slowest possible rate of 5.5125 kHz means 907 us.
	 */
	msleep(1);

	snd_prपूर्णांकdd("(1) jiffies = %lu\n", jअगरfies);

	/* check condition up to 250 ms */
	end_समय = jअगरfies + msecs_to_jअगरfies(250);
	जबतक (snd_wss_in(chip, CS4231_TEST_INIT) &
		CS4231_CALIB_IN_PROGRESS) अणु

		अगर (समय_after(jअगरfies, end_समय)) अणु
			snd_prपूर्णांकk(KERN_ERR "mce_down - "
					"auto calibration time out (2)\n");
			वापस;
		पूर्ण
		msleep(1);
	पूर्ण

	snd_prपूर्णांकdd("(2) jiffies = %lu\n", jअगरfies);

	/* check condition up to 100 ms */
	end_समय = jअगरfies + msecs_to_jअगरfies(100);
	जबतक (wss_inb(chip, CS4231P(REGSEL)) & CS4231_INIT) अणु
		अगर (समय_after(jअगरfies, end_समय)) अणु
			snd_prपूर्णांकk(KERN_ERR "mce_down - auto calibration time out (3)\n");
			वापस;
		पूर्ण
		msleep(1);
	पूर्ण

	snd_prपूर्णांकdd("(3) jiffies = %lu\n", jअगरfies);
	snd_prपूर्णांकd("mce_down - exit = 0x%x\n", wss_inb(chip, CS4231P(REGSEL)));
पूर्ण
EXPORT_SYMBOL(snd_wss_mce_करोwn);

अटल अचिन्हित पूर्णांक snd_wss_get_count(अचिन्हित अक्षर क्रमmat, अचिन्हित पूर्णांक size)
अणु
	चयन (क्रमmat & 0xe0) अणु
	हाल CS4231_LINEAR_16:
	हाल CS4231_LINEAR_16_BIG:
		size >>= 1;
		अवरोध;
	हाल CS4231_ADPCM_16:
		वापस size >> 2;
	पूर्ण
	अगर (क्रमmat & CS4231_STEREO)
		size >>= 1;
	वापस size;
पूर्ण

अटल पूर्णांक snd_wss_trigger(काष्ठा snd_pcm_substream *substream,
			   पूर्णांक cmd)
अणु
	काष्ठा snd_wss *chip = snd_pcm_substream_chip(substream);
	पूर्णांक result = 0;
	अचिन्हित पूर्णांक what;
	काष्ठा snd_pcm_substream *s;
	पूर्णांक करो_start;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		करो_start = 1; अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		करो_start = 0; अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	what = 0;
	snd_pcm_group_क्रम_each_entry(s, substream) अणु
		अगर (s == chip->playback_substream) अणु
			what |= CS4231_PLAYBACK_ENABLE;
			snd_pcm_trigger_करोne(s, substream);
		पूर्ण अन्यथा अगर (s == chip->capture_substream) अणु
			what |= CS4231_RECORD_ENABLE;
			snd_pcm_trigger_करोne(s, substream);
		पूर्ण
	पूर्ण
	spin_lock(&chip->reg_lock);
	अगर (करो_start) अणु
		chip->image[CS4231_IFACE_CTRL] |= what;
		अगर (chip->trigger)
			chip->trigger(chip, what, 1);
	पूर्ण अन्यथा अणु
		chip->image[CS4231_IFACE_CTRL] &= ~what;
		अगर (chip->trigger)
			chip->trigger(chip, what, 0);
	पूर्ण
	snd_wss_out(chip, CS4231_IFACE_CTRL, chip->image[CS4231_IFACE_CTRL]);
	spin_unlock(&chip->reg_lock);
#अगर 0
	snd_wss_debug(chip);
#पूर्ण_अगर
	वापस result;
पूर्ण

/*
 *  CODEC I/O
 */

अटल अचिन्हित अक्षर snd_wss_get_rate(अचिन्हित पूर्णांक rate)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(rates); i++)
		अगर (rate == rates[i])
			वापस freq_bits[i];
	// snd_BUG();
	वापस freq_bits[ARRAY_SIZE(rates) - 1];
पूर्ण

अटल अचिन्हित अक्षर snd_wss_get_क्रमmat(काष्ठा snd_wss *chip,
					snd_pcm_क्रमmat_t क्रमmat,
					पूर्णांक channels)
अणु
	अचिन्हित अक्षर rक्रमmat;

	rक्रमmat = CS4231_LINEAR_8;
	चयन (क्रमmat) अणु
	हाल SNDRV_PCM_FORMAT_MU_LAW:	rक्रमmat = CS4231_ULAW_8; अवरोध;
	हाल SNDRV_PCM_FORMAT_A_LAW:	rक्रमmat = CS4231_ALAW_8; अवरोध;
	हाल SNDRV_PCM_FORMAT_S16_LE:	rक्रमmat = CS4231_LINEAR_16; अवरोध;
	हाल SNDRV_PCM_FORMAT_S16_BE:	rक्रमmat = CS4231_LINEAR_16_BIG; अवरोध;
	हाल SNDRV_PCM_FORMAT_IMA_ADPCM:	rक्रमmat = CS4231_ADPCM_16; अवरोध;
	पूर्ण
	अगर (channels > 1)
		rक्रमmat |= CS4231_STEREO;
#अगर 0
	snd_prपूर्णांकk(KERN_DEBUG "get_format: 0x%x (mode=0x%x)\n", क्रमmat, mode);
#पूर्ण_अगर
	वापस rक्रमmat;
पूर्ण

अटल व्योम snd_wss_calibrate_mute(काष्ठा snd_wss *chip, पूर्णांक mute)
अणु
	अचिन्हित दीर्घ flags;

	mute = mute ? 0x80 : 0;
	spin_lock_irqsave(&chip->reg_lock, flags);
	अगर (chip->calibrate_mute == mute) अणु
		spin_unlock_irqrestore(&chip->reg_lock, flags);
		वापस;
	पूर्ण
	अगर (!mute) अणु
		snd_wss_करोut(chip, CS4231_LEFT_INPUT,
			     chip->image[CS4231_LEFT_INPUT]);
		snd_wss_करोut(chip, CS4231_RIGHT_INPUT,
			     chip->image[CS4231_RIGHT_INPUT]);
		snd_wss_करोut(chip, CS4231_LOOPBACK,
			     chip->image[CS4231_LOOPBACK]);
	पूर्ण अन्यथा अणु
		snd_wss_करोut(chip, CS4231_LEFT_INPUT,
			     0);
		snd_wss_करोut(chip, CS4231_RIGHT_INPUT,
			     0);
		snd_wss_करोut(chip, CS4231_LOOPBACK,
			     0xfd);
	पूर्ण

	snd_wss_करोut(chip, CS4231_AUX1_LEFT_INPUT,
		     mute | chip->image[CS4231_AUX1_LEFT_INPUT]);
	snd_wss_करोut(chip, CS4231_AUX1_RIGHT_INPUT,
		     mute | chip->image[CS4231_AUX1_RIGHT_INPUT]);
	snd_wss_करोut(chip, CS4231_AUX2_LEFT_INPUT,
		     mute | chip->image[CS4231_AUX2_LEFT_INPUT]);
	snd_wss_करोut(chip, CS4231_AUX2_RIGHT_INPUT,
		     mute | chip->image[CS4231_AUX2_RIGHT_INPUT]);
	snd_wss_करोut(chip, CS4231_LEFT_OUTPUT,
		     mute | chip->image[CS4231_LEFT_OUTPUT]);
	snd_wss_करोut(chip, CS4231_RIGHT_OUTPUT,
		     mute | chip->image[CS4231_RIGHT_OUTPUT]);
	अगर (!(chip->hardware & WSS_HW_AD1848_MASK)) अणु
		snd_wss_करोut(chip, CS4231_LEFT_LINE_IN,
			     mute | chip->image[CS4231_LEFT_LINE_IN]);
		snd_wss_करोut(chip, CS4231_RIGHT_LINE_IN,
			     mute | chip->image[CS4231_RIGHT_LINE_IN]);
		snd_wss_करोut(chip, CS4231_MONO_CTRL,
			     mute ? 0xc0 : chip->image[CS4231_MONO_CTRL]);
	पूर्ण
	अगर (chip->hardware == WSS_HW_INTERWAVE) अणु
		snd_wss_करोut(chip, CS4231_LEFT_MIC_INPUT,
			     mute | chip->image[CS4231_LEFT_MIC_INPUT]);
		snd_wss_करोut(chip, CS4231_RIGHT_MIC_INPUT,
			     mute | chip->image[CS4231_RIGHT_MIC_INPUT]);
		snd_wss_करोut(chip, CS4231_LINE_LEFT_OUTPUT,
			     mute | chip->image[CS4231_LINE_LEFT_OUTPUT]);
		snd_wss_करोut(chip, CS4231_LINE_RIGHT_OUTPUT,
			     mute | chip->image[CS4231_LINE_RIGHT_OUTPUT]);
	पूर्ण
	chip->calibrate_mute = mute;
	spin_unlock_irqrestore(&chip->reg_lock, flags);
पूर्ण

अटल व्योम snd_wss_playback_क्रमmat(काष्ठा snd_wss *chip,
				       काष्ठा snd_pcm_hw_params *params,
				       अचिन्हित अक्षर pdfr)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक full_calib = 1;

	mutex_lock(&chip->mce_mutex);
	अगर (chip->hardware == WSS_HW_CS4231A ||
	    (chip->hardware & WSS_HW_CS4232_MASK)) अणु
		spin_lock_irqsave(&chip->reg_lock, flags);
		अगर ((chip->image[CS4231_PLAYBK_FORMAT] & 0x0f) == (pdfr & 0x0f)) अणु	/* rate is same? */
			snd_wss_out(chip, CS4231_ALT_FEATURE_1,
				    chip->image[CS4231_ALT_FEATURE_1] | 0x10);
			chip->image[CS4231_PLAYBK_FORMAT] = pdfr;
			snd_wss_out(chip, CS4231_PLAYBK_FORMAT,
				    chip->image[CS4231_PLAYBK_FORMAT]);
			snd_wss_out(chip, CS4231_ALT_FEATURE_1,
				    chip->image[CS4231_ALT_FEATURE_1] &= ~0x10);
			udelay(100); /* Fixes audible clicks at least on GUS MAX */
			full_calib = 0;
		पूर्ण
		spin_unlock_irqrestore(&chip->reg_lock, flags);
	पूर्ण अन्यथा अगर (chip->hardware == WSS_HW_AD1845) अणु
		अचिन्हित rate = params_rate(params);

		/*
		 * Program the AD1845 correctly क्रम the playback stream.
		 * Note that we करो NOT need to toggle the MCE bit because
		 * the PLAYBACK_ENABLE bit of the Interface Configuration
		 * रेजिस्टर is set.
		 *
		 * NOTE: We seem to need to ग_लिखो to the MSB beक्रमe the LSB
		 *       to get the correct sample frequency.
		 */
		spin_lock_irqsave(&chip->reg_lock, flags);
		snd_wss_out(chip, CS4231_PLAYBK_FORMAT, (pdfr & 0xf0));
		snd_wss_out(chip, AD1845_UPR_FREQ_SEL, (rate >> 8) & 0xff);
		snd_wss_out(chip, AD1845_LWR_FREQ_SEL, rate & 0xff);
		full_calib = 0;
		spin_unlock_irqrestore(&chip->reg_lock, flags);
	पूर्ण
	अगर (full_calib) अणु
		snd_wss_mce_up(chip);
		spin_lock_irqsave(&chip->reg_lock, flags);
		अगर (chip->hardware != WSS_HW_INTERWAVE && !chip->single_dma) अणु
			अगर (chip->image[CS4231_IFACE_CTRL] & CS4231_RECORD_ENABLE)
				pdfr = (pdfr & 0xf0) |
				       (chip->image[CS4231_REC_FORMAT] & 0x0f);
		पूर्ण अन्यथा अणु
			chip->image[CS4231_PLAYBK_FORMAT] = pdfr;
		पूर्ण
		snd_wss_out(chip, CS4231_PLAYBK_FORMAT, pdfr);
		spin_unlock_irqrestore(&chip->reg_lock, flags);
		अगर (chip->hardware == WSS_HW_OPL3SA2)
			udelay(100);	/* this seems to help */
		snd_wss_mce_करोwn(chip);
	पूर्ण
	mutex_unlock(&chip->mce_mutex);
पूर्ण

अटल व्योम snd_wss_capture_क्रमmat(काष्ठा snd_wss *chip,
				   काष्ठा snd_pcm_hw_params *params,
				   अचिन्हित अक्षर cdfr)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक full_calib = 1;

	mutex_lock(&chip->mce_mutex);
	अगर (chip->hardware == WSS_HW_CS4231A ||
	    (chip->hardware & WSS_HW_CS4232_MASK)) अणु
		spin_lock_irqsave(&chip->reg_lock, flags);
		अगर ((chip->image[CS4231_PLAYBK_FORMAT] & 0x0f) == (cdfr & 0x0f) ||	/* rate is same? */
		    (chip->image[CS4231_IFACE_CTRL] & CS4231_PLAYBACK_ENABLE)) अणु
			snd_wss_out(chip, CS4231_ALT_FEATURE_1,
				chip->image[CS4231_ALT_FEATURE_1] | 0x20);
			snd_wss_out(chip, CS4231_REC_FORMAT,
				chip->image[CS4231_REC_FORMAT] = cdfr);
			snd_wss_out(chip, CS4231_ALT_FEATURE_1,
				chip->image[CS4231_ALT_FEATURE_1] &= ~0x20);
			full_calib = 0;
		पूर्ण
		spin_unlock_irqrestore(&chip->reg_lock, flags);
	पूर्ण अन्यथा अगर (chip->hardware == WSS_HW_AD1845) अणु
		अचिन्हित rate = params_rate(params);

		/*
		 * Program the AD1845 correctly क्रम the capture stream.
		 * Note that we करो NOT need to toggle the MCE bit because
		 * the PLAYBACK_ENABLE bit of the Interface Configuration
		 * रेजिस्टर is set.
		 *
		 * NOTE: We seem to need to ग_लिखो to the MSB beक्रमe the LSB
		 *       to get the correct sample frequency.
		 */
		spin_lock_irqsave(&chip->reg_lock, flags);
		snd_wss_out(chip, CS4231_REC_FORMAT, (cdfr & 0xf0));
		snd_wss_out(chip, AD1845_UPR_FREQ_SEL, (rate >> 8) & 0xff);
		snd_wss_out(chip, AD1845_LWR_FREQ_SEL, rate & 0xff);
		full_calib = 0;
		spin_unlock_irqrestore(&chip->reg_lock, flags);
	पूर्ण
	अगर (full_calib) अणु
		snd_wss_mce_up(chip);
		spin_lock_irqsave(&chip->reg_lock, flags);
		अगर (chip->hardware != WSS_HW_INTERWAVE &&
		    !(chip->image[CS4231_IFACE_CTRL] & CS4231_PLAYBACK_ENABLE)) अणु
			अगर (chip->single_dma)
				snd_wss_out(chip, CS4231_PLAYBK_FORMAT, cdfr);
			अन्यथा
				snd_wss_out(chip, CS4231_PLAYBK_FORMAT,
				   (chip->image[CS4231_PLAYBK_FORMAT] & 0xf0) |
				   (cdfr & 0x0f));
			spin_unlock_irqrestore(&chip->reg_lock, flags);
			snd_wss_mce_करोwn(chip);
			snd_wss_mce_up(chip);
			spin_lock_irqsave(&chip->reg_lock, flags);
		पूर्ण
		अगर (chip->hardware & WSS_HW_AD1848_MASK)
			snd_wss_out(chip, CS4231_PLAYBK_FORMAT, cdfr);
		अन्यथा
			snd_wss_out(chip, CS4231_REC_FORMAT, cdfr);
		spin_unlock_irqrestore(&chip->reg_lock, flags);
		snd_wss_mce_करोwn(chip);
	पूर्ण
	mutex_unlock(&chip->mce_mutex);
पूर्ण

/*
 *  Timer पूर्णांकerface
 */

अटल अचिन्हित दीर्घ snd_wss_समयr_resolution(काष्ठा snd_समयr *समयr)
अणु
	काष्ठा snd_wss *chip = snd_समयr_chip(समयr);
	अगर (chip->hardware & WSS_HW_CS4236B_MASK)
		वापस 14467;
	अन्यथा
		वापस chip->image[CS4231_PLAYBK_FORMAT] & 1 ? 9969 : 9920;
पूर्ण

अटल पूर्णांक snd_wss_समयr_start(काष्ठा snd_समयr *समयr)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक ticks;
	काष्ठा snd_wss *chip = snd_समयr_chip(समयr);
	spin_lock_irqsave(&chip->reg_lock, flags);
	ticks = समयr->sticks;
	अगर ((chip->image[CS4231_ALT_FEATURE_1] & CS4231_TIMER_ENABLE) == 0 ||
	    (अचिन्हित अक्षर)(ticks >> 8) != chip->image[CS4231_TIMER_HIGH] ||
	    (अचिन्हित अक्षर)ticks != chip->image[CS4231_TIMER_LOW]) अणु
		chip->image[CS4231_TIMER_HIGH] = (अचिन्हित अक्षर) (ticks >> 8);
		snd_wss_out(chip, CS4231_TIMER_HIGH,
			    chip->image[CS4231_TIMER_HIGH]);
		chip->image[CS4231_TIMER_LOW] = (अचिन्हित अक्षर) ticks;
		snd_wss_out(chip, CS4231_TIMER_LOW,
			    chip->image[CS4231_TIMER_LOW]);
		snd_wss_out(chip, CS4231_ALT_FEATURE_1,
			    chip->image[CS4231_ALT_FEATURE_1] |
			    CS4231_TIMER_ENABLE);
	पूर्ण
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_wss_समयr_stop(काष्ठा snd_समयr *समयr)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_wss *chip = snd_समयr_chip(समयr);
	spin_lock_irqsave(&chip->reg_lock, flags);
	chip->image[CS4231_ALT_FEATURE_1] &= ~CS4231_TIMER_ENABLE;
	snd_wss_out(chip, CS4231_ALT_FEATURE_1,
		    chip->image[CS4231_ALT_FEATURE_1]);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस 0;
पूर्ण

अटल व्योम snd_wss_init(काष्ठा snd_wss *chip)
अणु
	अचिन्हित दीर्घ flags;

	snd_wss_calibrate_mute(chip, 1);
	snd_wss_mce_करोwn(chip);

#अगर_घोषित SNDRV_DEBUG_MCE
	snd_prपूर्णांकk(KERN_DEBUG "init: (1)\n");
#पूर्ण_अगर
	snd_wss_mce_up(chip);
	spin_lock_irqsave(&chip->reg_lock, flags);
	chip->image[CS4231_IFACE_CTRL] &= ~(CS4231_PLAYBACK_ENABLE |
					    CS4231_PLAYBACK_PIO |
					    CS4231_RECORD_ENABLE |
					    CS4231_RECORD_PIO |
					    CS4231_CALIB_MODE);
	chip->image[CS4231_IFACE_CTRL] |= CS4231_AUTOCALIB;
	snd_wss_out(chip, CS4231_IFACE_CTRL, chip->image[CS4231_IFACE_CTRL]);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	snd_wss_mce_करोwn(chip);

#अगर_घोषित SNDRV_DEBUG_MCE
	snd_prपूर्णांकk(KERN_DEBUG "init: (2)\n");
#पूर्ण_अगर

	snd_wss_mce_up(chip);
	spin_lock_irqsave(&chip->reg_lock, flags);
	chip->image[CS4231_IFACE_CTRL] &= ~CS4231_AUTOCALIB;
	snd_wss_out(chip, CS4231_IFACE_CTRL, chip->image[CS4231_IFACE_CTRL]);
	snd_wss_out(chip,
		    CS4231_ALT_FEATURE_1, chip->image[CS4231_ALT_FEATURE_1]);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	snd_wss_mce_करोwn(chip);

#अगर_घोषित SNDRV_DEBUG_MCE
	snd_prपूर्णांकk(KERN_DEBUG "init: (3) - afei = 0x%x\n",
		   chip->image[CS4231_ALT_FEATURE_1]);
#पूर्ण_अगर

	spin_lock_irqsave(&chip->reg_lock, flags);
	snd_wss_out(chip, CS4231_ALT_FEATURE_2,
		    chip->image[CS4231_ALT_FEATURE_2]);
	spin_unlock_irqrestore(&chip->reg_lock, flags);

	snd_wss_mce_up(chip);
	spin_lock_irqsave(&chip->reg_lock, flags);
	snd_wss_out(chip, CS4231_PLAYBK_FORMAT,
		    chip->image[CS4231_PLAYBK_FORMAT]);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	snd_wss_mce_करोwn(chip);

#अगर_घोषित SNDRV_DEBUG_MCE
	snd_prपूर्णांकk(KERN_DEBUG "init: (4)\n");
#पूर्ण_अगर

	snd_wss_mce_up(chip);
	spin_lock_irqsave(&chip->reg_lock, flags);
	अगर (!(chip->hardware & WSS_HW_AD1848_MASK))
		snd_wss_out(chip, CS4231_REC_FORMAT,
			    chip->image[CS4231_REC_FORMAT]);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	snd_wss_mce_करोwn(chip);
	snd_wss_calibrate_mute(chip, 0);

#अगर_घोषित SNDRV_DEBUG_MCE
	snd_prपूर्णांकk(KERN_DEBUG "init: (5)\n");
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक snd_wss_खोलो(काष्ठा snd_wss *chip, अचिन्हित पूर्णांक mode)
अणु
	अचिन्हित दीर्घ flags;

	mutex_lock(&chip->खोलो_mutex);
	अगर ((chip->mode & mode) ||
	    ((chip->mode & WSS_MODE_OPEN) && chip->single_dma)) अणु
		mutex_unlock(&chip->खोलो_mutex);
		वापस -EAGAIN;
	पूर्ण
	अगर (chip->mode & WSS_MODE_OPEN) अणु
		chip->mode |= mode;
		mutex_unlock(&chip->खोलो_mutex);
		वापस 0;
	पूर्ण
	/* ok. now enable and ack CODEC IRQ */
	spin_lock_irqsave(&chip->reg_lock, flags);
	अगर (!(chip->hardware & WSS_HW_AD1848_MASK)) अणु
		snd_wss_out(chip, CS4231_IRQ_STATUS,
			    CS4231_PLAYBACK_IRQ |
			    CS4231_RECORD_IRQ |
			    CS4231_TIMER_IRQ);
		snd_wss_out(chip, CS4231_IRQ_STATUS, 0);
	पूर्ण
	wss_outb(chip, CS4231P(STATUS), 0);	/* clear IRQ */
	wss_outb(chip, CS4231P(STATUS), 0);	/* clear IRQ */
	chip->image[CS4231_PIN_CTRL] |= CS4231_IRQ_ENABLE;
	snd_wss_out(chip, CS4231_PIN_CTRL, chip->image[CS4231_PIN_CTRL]);
	अगर (!(chip->hardware & WSS_HW_AD1848_MASK)) अणु
		snd_wss_out(chip, CS4231_IRQ_STATUS,
			    CS4231_PLAYBACK_IRQ |
			    CS4231_RECORD_IRQ |
			    CS4231_TIMER_IRQ);
		snd_wss_out(chip, CS4231_IRQ_STATUS, 0);
	पूर्ण
	spin_unlock_irqrestore(&chip->reg_lock, flags);

	chip->mode = mode;
	mutex_unlock(&chip->खोलो_mutex);
	वापस 0;
पूर्ण

अटल व्योम snd_wss_बंद(काष्ठा snd_wss *chip, अचिन्हित पूर्णांक mode)
अणु
	अचिन्हित दीर्घ flags;

	mutex_lock(&chip->खोलो_mutex);
	chip->mode &= ~mode;
	अगर (chip->mode & WSS_MODE_OPEN) अणु
		mutex_unlock(&chip->खोलो_mutex);
		वापस;
	पूर्ण
	/* disable IRQ */
	spin_lock_irqsave(&chip->reg_lock, flags);
	अगर (!(chip->hardware & WSS_HW_AD1848_MASK))
		snd_wss_out(chip, CS4231_IRQ_STATUS, 0);
	wss_outb(chip, CS4231P(STATUS), 0);	/* clear IRQ */
	wss_outb(chip, CS4231P(STATUS), 0);	/* clear IRQ */
	chip->image[CS4231_PIN_CTRL] &= ~CS4231_IRQ_ENABLE;
	snd_wss_out(chip, CS4231_PIN_CTRL, chip->image[CS4231_PIN_CTRL]);

	/* now disable record & playback */

	अगर (chip->image[CS4231_IFACE_CTRL] & (CS4231_PLAYBACK_ENABLE | CS4231_PLAYBACK_PIO |
					       CS4231_RECORD_ENABLE | CS4231_RECORD_PIO)) अणु
		spin_unlock_irqrestore(&chip->reg_lock, flags);
		snd_wss_mce_up(chip);
		spin_lock_irqsave(&chip->reg_lock, flags);
		chip->image[CS4231_IFACE_CTRL] &= ~(CS4231_PLAYBACK_ENABLE | CS4231_PLAYBACK_PIO |
						     CS4231_RECORD_ENABLE | CS4231_RECORD_PIO);
		snd_wss_out(chip, CS4231_IFACE_CTRL,
			    chip->image[CS4231_IFACE_CTRL]);
		spin_unlock_irqrestore(&chip->reg_lock, flags);
		snd_wss_mce_करोwn(chip);
		spin_lock_irqsave(&chip->reg_lock, flags);
	पूर्ण

	/* clear IRQ again */
	अगर (!(chip->hardware & WSS_HW_AD1848_MASK))
		snd_wss_out(chip, CS4231_IRQ_STATUS, 0);
	wss_outb(chip, CS4231P(STATUS), 0);	/* clear IRQ */
	wss_outb(chip, CS4231P(STATUS), 0);	/* clear IRQ */
	spin_unlock_irqrestore(&chip->reg_lock, flags);

	chip->mode = 0;
	mutex_unlock(&chip->खोलो_mutex);
पूर्ण

/*
 *  समयr खोलो/बंद
 */

अटल पूर्णांक snd_wss_समयr_खोलो(काष्ठा snd_समयr *समयr)
अणु
	काष्ठा snd_wss *chip = snd_समयr_chip(समयr);
	snd_wss_खोलो(chip, WSS_MODE_TIMER);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_wss_समयr_बंद(काष्ठा snd_समयr *समयr)
अणु
	काष्ठा snd_wss *chip = snd_समयr_chip(समयr);
	snd_wss_बंद(chip, WSS_MODE_TIMER);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_समयr_hardware snd_wss_समयr_table =
अणु
	.flags =	SNDRV_TIMER_HW_AUTO,
	.resolution =	9945,
	.ticks =	65535,
	.खोलो =		snd_wss_समयr_खोलो,
	.बंद =	snd_wss_समयr_बंद,
	.c_resolution = snd_wss_समयr_resolution,
	.start =	snd_wss_समयr_start,
	.stop =		snd_wss_समयr_stop,
पूर्ण;

/*
 *  ok.. exported functions..
 */

अटल पूर्णांक snd_wss_playback_hw_params(काष्ठा snd_pcm_substream *substream,
					 काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_wss *chip = snd_pcm_substream_chip(substream);
	अचिन्हित अक्षर new_pdfr;

	new_pdfr = snd_wss_get_क्रमmat(chip, params_क्रमmat(hw_params),
				params_channels(hw_params)) |
				snd_wss_get_rate(params_rate(hw_params));
	chip->set_playback_क्रमmat(chip, hw_params, new_pdfr);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_wss_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_wss *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक size = snd_pcm_lib_buffer_bytes(substream);
	अचिन्हित पूर्णांक count = snd_pcm_lib_period_bytes(substream);

	spin_lock_irqsave(&chip->reg_lock, flags);
	chip->p_dma_size = size;
	chip->image[CS4231_IFACE_CTRL] &= ~(CS4231_PLAYBACK_ENABLE | CS4231_PLAYBACK_PIO);
	snd_dma_program(chip->dma1, runसमय->dma_addr, size, DMA_MODE_WRITE | DMA_AUTOINIT);
	count = snd_wss_get_count(chip->image[CS4231_PLAYBK_FORMAT], count) - 1;
	snd_wss_out(chip, CS4231_PLY_LWR_CNT, (अचिन्हित अक्षर) count);
	snd_wss_out(chip, CS4231_PLY_UPR_CNT, (अचिन्हित अक्षर) (count >> 8));
	spin_unlock_irqrestore(&chip->reg_lock, flags);
#अगर 0
	snd_wss_debug(chip);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक snd_wss_capture_hw_params(काष्ठा snd_pcm_substream *substream,
					काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_wss *chip = snd_pcm_substream_chip(substream);
	अचिन्हित अक्षर new_cdfr;

	new_cdfr = snd_wss_get_क्रमmat(chip, params_क्रमmat(hw_params),
			   params_channels(hw_params)) |
			   snd_wss_get_rate(params_rate(hw_params));
	chip->set_capture_क्रमmat(chip, hw_params, new_cdfr);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_wss_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_wss *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक size = snd_pcm_lib_buffer_bytes(substream);
	अचिन्हित पूर्णांक count = snd_pcm_lib_period_bytes(substream);

	spin_lock_irqsave(&chip->reg_lock, flags);
	chip->c_dma_size = size;
	chip->image[CS4231_IFACE_CTRL] &= ~(CS4231_RECORD_ENABLE | CS4231_RECORD_PIO);
	snd_dma_program(chip->dma2, runसमय->dma_addr, size, DMA_MODE_READ | DMA_AUTOINIT);
	अगर (chip->hardware & WSS_HW_AD1848_MASK)
		count = snd_wss_get_count(chip->image[CS4231_PLAYBK_FORMAT],
					  count);
	अन्यथा
		count = snd_wss_get_count(chip->image[CS4231_REC_FORMAT],
					  count);
	count--;
	अगर (chip->single_dma && chip->hardware != WSS_HW_INTERWAVE) अणु
		snd_wss_out(chip, CS4231_PLY_LWR_CNT, (अचिन्हित अक्षर) count);
		snd_wss_out(chip, CS4231_PLY_UPR_CNT,
			    (अचिन्हित अक्षर) (count >> 8));
	पूर्ण अन्यथा अणु
		snd_wss_out(chip, CS4231_REC_LWR_CNT, (अचिन्हित अक्षर) count);
		snd_wss_out(chip, CS4231_REC_UPR_CNT,
			    (अचिन्हित अक्षर) (count >> 8));
	पूर्ण
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस 0;
पूर्ण

व्योम snd_wss_overrange(काष्ठा snd_wss *chip)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर res;

	spin_lock_irqsave(&chip->reg_lock, flags);
	res = snd_wss_in(chip, CS4231_TEST_INIT);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	अगर (res & (0x08 | 0x02))	/* detect overrange only above 0dB; may be user selectable? */
		chip->capture_substream->runसमय->overrange++;
पूर्ण
EXPORT_SYMBOL(snd_wss_overrange);

irqवापस_t snd_wss_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा snd_wss *chip = dev_id;
	अचिन्हित अक्षर status;

	अगर (chip->hardware & WSS_HW_AD1848_MASK)
		/* pretend it was the only possible irq क्रम AD1848 */
		status = CS4231_PLAYBACK_IRQ;
	अन्यथा
		status = snd_wss_in(chip, CS4231_IRQ_STATUS);
	अगर (status & CS4231_TIMER_IRQ) अणु
		अगर (chip->समयr)
			snd_समयr_पूर्णांकerrupt(chip->समयr, chip->समयr->sticks);
	पूर्ण
	अगर (chip->single_dma && chip->hardware != WSS_HW_INTERWAVE) अणु
		अगर (status & CS4231_PLAYBACK_IRQ) अणु
			अगर (chip->mode & WSS_MODE_PLAY) अणु
				अगर (chip->playback_substream)
					snd_pcm_period_elapsed(chip->playback_substream);
			पूर्ण
			अगर (chip->mode & WSS_MODE_RECORD) अणु
				अगर (chip->capture_substream) अणु
					snd_wss_overrange(chip);
					snd_pcm_period_elapsed(chip->capture_substream);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (status & CS4231_PLAYBACK_IRQ) अणु
			अगर (chip->playback_substream)
				snd_pcm_period_elapsed(chip->playback_substream);
		पूर्ण
		अगर (status & CS4231_RECORD_IRQ) अणु
			अगर (chip->capture_substream) अणु
				snd_wss_overrange(chip);
				snd_pcm_period_elapsed(chip->capture_substream);
			पूर्ण
		पूर्ण
	पूर्ण

	spin_lock(&chip->reg_lock);
	status = ~CS4231_ALL_IRQS | ~status;
	अगर (chip->hardware & WSS_HW_AD1848_MASK)
		wss_outb(chip, CS4231P(STATUS), 0);
	अन्यथा
		snd_wss_out(chip, CS4231_IRQ_STATUS, status);
	spin_unlock(&chip->reg_lock);
	वापस IRQ_HANDLED;
पूर्ण
EXPORT_SYMBOL(snd_wss_पूर्णांकerrupt);

अटल snd_pcm_uframes_t snd_wss_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_wss *chip = snd_pcm_substream_chip(substream);
	माप_प्रकार ptr;

	अगर (!(chip->image[CS4231_IFACE_CTRL] & CS4231_PLAYBACK_ENABLE))
		वापस 0;
	ptr = snd_dma_poपूर्णांकer(chip->dma1, chip->p_dma_size);
	वापस bytes_to_frames(substream->runसमय, ptr);
पूर्ण

अटल snd_pcm_uframes_t snd_wss_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_wss *chip = snd_pcm_substream_chip(substream);
	माप_प्रकार ptr;

	अगर (!(chip->image[CS4231_IFACE_CTRL] & CS4231_RECORD_ENABLE))
		वापस 0;
	ptr = snd_dma_poपूर्णांकer(chip->dma2, chip->c_dma_size);
	वापस bytes_to_frames(substream->runसमय, ptr);
पूर्ण

/*

 */

अटल पूर्णांक snd_ad1848_probe(काष्ठा snd_wss *chip)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(1000);
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर r;
	अचिन्हित लघु hardware = 0;
	पूर्णांक err = 0;
	पूर्णांक i;

	जबतक (wss_inb(chip, CS4231P(REGSEL)) & CS4231_INIT) अणु
		अगर (समय_after(jअगरfies, समयout))
			वापस -ENODEV;
		cond_resched();
	पूर्ण
	spin_lock_irqsave(&chip->reg_lock, flags);

	/* set CS423x MODE 1 */
	snd_wss_करोut(chip, CS4231_MISC_INFO, 0);

	snd_wss_करोut(chip, CS4231_RIGHT_INPUT, 0x45); /* 0x55 & ~0x10 */
	r = snd_wss_in(chip, CS4231_RIGHT_INPUT);
	अगर (r != 0x45) अणु
		/* RMGE always high on AD1847 */
		अगर ((r & ~CS4231_ENABLE_MIC_GAIN) != 0x45) अणु
			err = -ENODEV;
			जाओ out;
		पूर्ण
		hardware = WSS_HW_AD1847;
	पूर्ण अन्यथा अणु
		snd_wss_करोut(chip, CS4231_LEFT_INPUT,  0xaa);
		r = snd_wss_in(chip, CS4231_LEFT_INPUT);
		/* L/RMGE always low on AT2320 */
		अगर ((r | CS4231_ENABLE_MIC_GAIN) != 0xaa) अणु
			err = -ENODEV;
			जाओ out;
		पूर्ण
	पूर्ण

	/* clear pending IRQ */
	wss_inb(chip, CS4231P(STATUS));
	wss_outb(chip, CS4231P(STATUS), 0);
	mb();

	अगर ((chip->hardware & WSS_HW_TYPE_MASK) != WSS_HW_DETECT)
		जाओ out;

	अगर (hardware) अणु
		chip->hardware = hardware;
		जाओ out;
	पूर्ण

	r = snd_wss_in(chip, CS4231_MISC_INFO);

	/* set CS423x MODE 2 */
	snd_wss_करोut(chip, CS4231_MISC_INFO, CS4231_MODE2);
	क्रम (i = 0; i < 16; i++) अणु
		अगर (snd_wss_in(chip, i) != snd_wss_in(chip, 16 + i)) अणु
			/* we have more than 16 रेजिस्टरs: check ID */
			अगर ((r & 0xf) != 0xa)
				जाओ out_mode;
			/*
			 * on CMI8330, CS4231_VERSION is volume control and
			 * can be set to 0
			 */
			snd_wss_करोut(chip, CS4231_VERSION, 0);
			r = snd_wss_in(chip, CS4231_VERSION) & 0xe7;
			अगर (!r)
				chip->hardware = WSS_HW_CMI8330;
			जाओ out_mode;
		पूर्ण
	पूर्ण
	अगर (r & 0x80)
		chip->hardware = WSS_HW_CS4248;
	अन्यथा
		chip->hardware = WSS_HW_AD1848;
out_mode:
	snd_wss_करोut(chip, CS4231_MISC_INFO, 0);
out:
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस err;
पूर्ण

अटल पूर्णांक snd_wss_probe(काष्ठा snd_wss *chip)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i, id, rev, regnum;
	अचिन्हित अक्षर *ptr;
	अचिन्हित पूर्णांक hw;

	id = snd_ad1848_probe(chip);
	अगर (id < 0)
		वापस id;

	hw = chip->hardware;
	अगर ((hw & WSS_HW_TYPE_MASK) == WSS_HW_DETECT) अणु
		क्रम (i = 0; i < 50; i++) अणु
			mb();
			अगर (wss_inb(chip, CS4231P(REGSEL)) & CS4231_INIT)
				msleep(2);
			अन्यथा अणु
				spin_lock_irqsave(&chip->reg_lock, flags);
				snd_wss_out(chip, CS4231_MISC_INFO,
					    CS4231_MODE2);
				id = snd_wss_in(chip, CS4231_MISC_INFO) & 0x0f;
				spin_unlock_irqrestore(&chip->reg_lock, flags);
				अगर (id == 0x0a)
					अवरोध;	/* this is valid value */
			पूर्ण
		पूर्ण
		snd_prपूर्णांकdd("wss: port = 0x%lx, id = 0x%x\n", chip->port, id);
		अगर (id != 0x0a)
			वापस -ENODEV;	/* no valid device found */

		rev = snd_wss_in(chip, CS4231_VERSION) & 0xe7;
		snd_prपूर्णांकdd("CS4231: VERSION (I25) = 0x%x\n", rev);
		अगर (rev == 0x80) अणु
			अचिन्हित अक्षर पंचांगp = snd_wss_in(chip, 23);
			snd_wss_out(chip, 23, ~पंचांगp);
			अगर (snd_wss_in(chip, 23) != पंचांगp)
				chip->hardware = WSS_HW_AD1845;
			अन्यथा
				chip->hardware = WSS_HW_CS4231;
		पूर्ण अन्यथा अगर (rev == 0xa0) अणु
			chip->hardware = WSS_HW_CS4231A;
		पूर्ण अन्यथा अगर (rev == 0xa2) अणु
			chip->hardware = WSS_HW_CS4232;
		पूर्ण अन्यथा अगर (rev == 0xb2) अणु
			chip->hardware = WSS_HW_CS4232A;
		पूर्ण अन्यथा अगर (rev == 0x83) अणु
			chip->hardware = WSS_HW_CS4236;
		पूर्ण अन्यथा अगर (rev == 0x03) अणु
			chip->hardware = WSS_HW_CS4236B;
		पूर्ण अन्यथा अणु
			snd_prपूर्णांकk(KERN_ERR
				   "unknown CS chip with version 0x%x\n", rev);
			वापस -ENODEV;		/* unknown CS4231 chip? */
		पूर्ण
	पूर्ण
	spin_lock_irqsave(&chip->reg_lock, flags);
	wss_inb(chip, CS4231P(STATUS));	/* clear any pendings IRQ */
	wss_outb(chip, CS4231P(STATUS), 0);
	mb();
	spin_unlock_irqrestore(&chip->reg_lock, flags);

	अगर (!(chip->hardware & WSS_HW_AD1848_MASK))
		chip->image[CS4231_MISC_INFO] = CS4231_MODE2;
	चयन (chip->hardware) अणु
	हाल WSS_HW_INTERWAVE:
		chip->image[CS4231_MISC_INFO] = CS4231_IW_MODE3;
		अवरोध;
	हाल WSS_HW_CS4235:
	हाल WSS_HW_CS4236B:
	हाल WSS_HW_CS4237B:
	हाल WSS_HW_CS4238B:
	हाल WSS_HW_CS4239:
		अगर (hw == WSS_HW_DETECT3)
			chip->image[CS4231_MISC_INFO] = CS4231_4236_MODE3;
		अन्यथा
			chip->hardware = WSS_HW_CS4236;
		अवरोध;
	पूर्ण

	chip->image[CS4231_IFACE_CTRL] =
	    (chip->image[CS4231_IFACE_CTRL] & ~CS4231_SINGLE_DMA) |
	    (chip->single_dma ? CS4231_SINGLE_DMA : 0);
	अगर (chip->hardware != WSS_HW_OPTI93X) अणु
		chip->image[CS4231_ALT_FEATURE_1] = 0x80;
		chip->image[CS4231_ALT_FEATURE_2] =
			chip->hardware == WSS_HW_INTERWAVE ? 0xc2 : 0x01;
	पूर्ण
	/* enable fine grained frequency selection */
	अगर (chip->hardware == WSS_HW_AD1845)
		chip->image[AD1845_PWR_DOWN] = 8;

	ptr = (अचिन्हित अक्षर *) &chip->image;
	regnum = (chip->hardware & WSS_HW_AD1848_MASK) ? 16 : 32;
	snd_wss_mce_करोwn(chip);
	spin_lock_irqsave(&chip->reg_lock, flags);
	क्रम (i = 0; i < regnum; i++)	/* ok.. fill all रेजिस्टरs */
		snd_wss_out(chip, i, *ptr++);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	snd_wss_mce_up(chip);
	snd_wss_mce_करोwn(chip);

	mdelay(2);

	/* ok.. try check hardware version क्रम CS4236+ chips */
	अगर ((hw & WSS_HW_TYPE_MASK) == WSS_HW_DETECT) अणु
		अगर (chip->hardware == WSS_HW_CS4236B) अणु
			rev = snd_cs4236_ext_in(chip, CS4236_VERSION);
			snd_cs4236_ext_out(chip, CS4236_VERSION, 0xff);
			id = snd_cs4236_ext_in(chip, CS4236_VERSION);
			snd_cs4236_ext_out(chip, CS4236_VERSION, rev);
			snd_prपूर्णांकdd("CS4231: ext version; rev = 0x%x, id = 0x%x\n", rev, id);
			अगर ((id & 0x1f) == 0x1d) अणु	/* CS4235 */
				chip->hardware = WSS_HW_CS4235;
				चयन (id >> 5) अणु
				हाल 4:
				हाल 5:
				हाल 6:
					अवरोध;
				शेष:
					snd_prपूर्णांकk(KERN_WARNING
						"unknown CS4235 chip "
						"(enhanced version = 0x%x)\n",
						id);
				पूर्ण
			पूर्ण अन्यथा अगर ((id & 0x1f) == 0x0b) अणु	/* CS4236/B */
				चयन (id >> 5) अणु
				हाल 4:
				हाल 5:
				हाल 6:
				हाल 7:
					chip->hardware = WSS_HW_CS4236B;
					अवरोध;
				शेष:
					snd_prपूर्णांकk(KERN_WARNING
						"unknown CS4236 chip "
						"(enhanced version = 0x%x)\n",
						id);
				पूर्ण
			पूर्ण अन्यथा अगर ((id & 0x1f) == 0x08) अणु	/* CS4237B */
				chip->hardware = WSS_HW_CS4237B;
				चयन (id >> 5) अणु
				हाल 4:
				हाल 5:
				हाल 6:
				हाल 7:
					अवरोध;
				शेष:
					snd_prपूर्णांकk(KERN_WARNING
						"unknown CS4237B chip "
						"(enhanced version = 0x%x)\n",
						id);
				पूर्ण
			पूर्ण अन्यथा अगर ((id & 0x1f) == 0x09) अणु	/* CS4238B */
				chip->hardware = WSS_HW_CS4238B;
				चयन (id >> 5) अणु
				हाल 5:
				हाल 6:
				हाल 7:
					अवरोध;
				शेष:
					snd_prपूर्णांकk(KERN_WARNING
						"unknown CS4238B chip "
						"(enhanced version = 0x%x)\n",
						id);
				पूर्ण
			पूर्ण अन्यथा अगर ((id & 0x1f) == 0x1e) अणु	/* CS4239 */
				chip->hardware = WSS_HW_CS4239;
				चयन (id >> 5) अणु
				हाल 4:
				हाल 5:
				हाल 6:
					अवरोध;
				शेष:
					snd_prपूर्णांकk(KERN_WARNING
						"unknown CS4239 chip "
						"(enhanced version = 0x%x)\n",
						id);
				पूर्ण
			पूर्ण अन्यथा अणु
				snd_prपूर्णांकk(KERN_WARNING
					   "unknown CS4236/CS423xB chip "
					   "(enhanced version = 0x%x)\n", id);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;		/* all things are ok.. */
पूर्ण

/*

 */

अटल स्थिर काष्ठा snd_pcm_hardware snd_wss_playback =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_MMAP_VALID |
				 SNDRV_PCM_INFO_SYNC_START),
	.क्रमmats =		(SNDRV_PCM_FMTBIT_MU_LAW | SNDRV_PCM_FMTBIT_A_LAW | SNDRV_PCM_FMTBIT_IMA_ADPCM |
				 SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S16_BE),
	.rates =		SNDRV_PCM_RATE_KNOT | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		5510,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	(128*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(128*1024),
	.periods_min =		1,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_wss_capture =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_MMAP_VALID |
				 SNDRV_PCM_INFO_RESUME |
				 SNDRV_PCM_INFO_SYNC_START),
	.क्रमmats =		(SNDRV_PCM_FMTBIT_MU_LAW | SNDRV_PCM_FMTBIT_A_LAW | SNDRV_PCM_FMTBIT_IMA_ADPCM |
				 SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S16_BE),
	.rates =		SNDRV_PCM_RATE_KNOT | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		5510,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	(128*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(128*1024),
	.periods_min =		1,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

/*

 */

अटल पूर्णांक snd_wss_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_wss *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;

	runसमय->hw = snd_wss_playback;

	/* hardware limitation of older chipsets */
	अगर (chip->hardware & WSS_HW_AD1848_MASK)
		runसमय->hw.क्रमmats &= ~(SNDRV_PCM_FMTBIT_IMA_ADPCM |
					 SNDRV_PCM_FMTBIT_S16_BE);

	/* hardware bug in InterWave chipset */
	अगर (chip->hardware == WSS_HW_INTERWAVE && chip->dma1 > 3)
		runसमय->hw.क्रमmats &= ~SNDRV_PCM_FMTBIT_MU_LAW;

	/* hardware limitation of cheap chips */
	अगर (chip->hardware == WSS_HW_CS4235 ||
	    chip->hardware == WSS_HW_CS4239)
		runसमय->hw.क्रमmats = SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE;

	snd_pcm_limit_isa_dma_size(chip->dma1, &runसमय->hw.buffer_bytes_max);
	snd_pcm_limit_isa_dma_size(chip->dma1, &runसमय->hw.period_bytes_max);

	अगर (chip->claim_dma) अणु
		अगर ((err = chip->claim_dma(chip, chip->dma_निजी_data, chip->dma1)) < 0)
			वापस err;
	पूर्ण

	err = snd_wss_खोलो(chip, WSS_MODE_PLAY);
	अगर (err < 0) अणु
		अगर (chip->release_dma)
			chip->release_dma(chip, chip->dma_निजी_data, chip->dma1);
		वापस err;
	पूर्ण
	chip->playback_substream = substream;
	snd_pcm_set_sync(substream);
	chip->rate_स्थिरraपूर्णांक(runसमय);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_wss_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_wss *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;

	runसमय->hw = snd_wss_capture;

	/* hardware limitation of older chipsets */
	अगर (chip->hardware & WSS_HW_AD1848_MASK)
		runसमय->hw.क्रमmats &= ~(SNDRV_PCM_FMTBIT_IMA_ADPCM |
					 SNDRV_PCM_FMTBIT_S16_BE);

	/* hardware limitation of cheap chips */
	अगर (chip->hardware == WSS_HW_CS4235 ||
	    chip->hardware == WSS_HW_CS4239 ||
	    chip->hardware == WSS_HW_OPTI93X)
		runसमय->hw.क्रमmats = SNDRV_PCM_FMTBIT_U8 |
				      SNDRV_PCM_FMTBIT_S16_LE;

	snd_pcm_limit_isa_dma_size(chip->dma2, &runसमय->hw.buffer_bytes_max);
	snd_pcm_limit_isa_dma_size(chip->dma2, &runसमय->hw.period_bytes_max);

	अगर (chip->claim_dma) अणु
		अगर ((err = chip->claim_dma(chip, chip->dma_निजी_data, chip->dma2)) < 0)
			वापस err;
	पूर्ण

	err = snd_wss_खोलो(chip, WSS_MODE_RECORD);
	अगर (err < 0) अणु
		अगर (chip->release_dma)
			chip->release_dma(chip, chip->dma_निजी_data, chip->dma2);
		वापस err;
	पूर्ण
	chip->capture_substream = substream;
	snd_pcm_set_sync(substream);
	chip->rate_स्थिरraपूर्णांक(runसमय);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_wss_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_wss *chip = snd_pcm_substream_chip(substream);

	chip->playback_substream = शून्य;
	snd_wss_बंद(chip, WSS_MODE_PLAY);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_wss_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_wss *chip = snd_pcm_substream_chip(substream);

	chip->capture_substream = शून्य;
	snd_wss_बंद(chip, WSS_MODE_RECORD);
	वापस 0;
पूर्ण

अटल व्योम snd_wss_thinkpad_twiddle(काष्ठा snd_wss *chip, पूर्णांक on)
अणु
	पूर्णांक पंचांगp;

	अगर (!chip->thinkpad_flag)
		वापस;

	outb(0x1c, AD1848_THINKPAD_CTL_PORT1);
	पंचांगp = inb(AD1848_THINKPAD_CTL_PORT2);

	अगर (on)
		/* turn it on */
		पंचांगp |= AD1848_THINKPAD_CS4248_ENABLE_BIT;
	अन्यथा
		/* turn it off */
		पंचांगp &= ~AD1848_THINKPAD_CS4248_ENABLE_BIT;

	outb(पंचांगp, AD1848_THINKPAD_CTL_PORT2);
पूर्ण

#अगर_घोषित CONFIG_PM

/* lowlevel suspend callback क्रम CS4231 */
अटल व्योम snd_wss_suspend(काष्ठा snd_wss *chip)
अणु
	पूर्णांक reg;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->reg_lock, flags);
	क्रम (reg = 0; reg < 32; reg++)
		chip->image[reg] = snd_wss_in(chip, reg);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	अगर (chip->thinkpad_flag)
		snd_wss_thinkpad_twiddle(chip, 0);
पूर्ण

/* lowlevel resume callback क्रम CS4231 */
अटल व्योम snd_wss_resume(काष्ठा snd_wss *chip)
अणु
	पूर्णांक reg;
	अचिन्हित दीर्घ flags;
	/* पूर्णांक समयout; */

	अगर (chip->thinkpad_flag)
		snd_wss_thinkpad_twiddle(chip, 1);
	snd_wss_mce_up(chip);
	spin_lock_irqsave(&chip->reg_lock, flags);
	क्रम (reg = 0; reg < 32; reg++) अणु
		चयन (reg) अणु
		हाल CS4231_VERSION:
			अवरोध;
		शेष:
			snd_wss_out(chip, reg, chip->image[reg]);
			अवरोध;
		पूर्ण
	पूर्ण
	/* Yamaha needs this to resume properly */
	अगर (chip->hardware == WSS_HW_OPL3SA2)
		snd_wss_out(chip, CS4231_PLAYBK_FORMAT,
			    chip->image[CS4231_PLAYBK_FORMAT]);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
#अगर 1
	snd_wss_mce_करोwn(chip);
#अन्यथा
	/* The following is a workaround to aव्योम मुक्तze after resume on TP600E.
	   This is the first half of copy of snd_wss_mce_करोwn(), but करोesn't
	   include rescheduling.  -- iwai
	   */
	snd_wss_busy_रुको(chip);
	spin_lock_irqsave(&chip->reg_lock, flags);
	chip->mce_bit &= ~CS4231_MCE;
	समयout = wss_inb(chip, CS4231P(REGSEL));
	wss_outb(chip, CS4231P(REGSEL), chip->mce_bit | (समयout & 0x1f));
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	अगर (समयout == 0x80)
		snd_prपूर्णांकk(KERN_ERR "down [0x%lx]: serious init problem "
			   "- codec still busy\n", chip->port);
	अगर ((समयout & CS4231_MCE) == 0 ||
	    !(chip->hardware & (WSS_HW_CS4231_MASK | WSS_HW_CS4232_MASK))) अणु
		वापस;
	पूर्ण
	snd_wss_busy_रुको(chip);
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल पूर्णांक snd_wss_मुक्त(काष्ठा snd_wss *chip)
अणु
	release_and_मुक्त_resource(chip->res_port);
	release_and_मुक्त_resource(chip->res_cport);
	अगर (chip->irq >= 0) अणु
		disable_irq(chip->irq);
		अगर (!(chip->hwshare & WSS_HWSHARE_IRQ))
			मुक्त_irq(chip->irq, (व्योम *) chip);
	पूर्ण
	अगर (!(chip->hwshare & WSS_HWSHARE_DMA1) && chip->dma1 >= 0) अणु
		snd_dma_disable(chip->dma1);
		मुक्त_dma(chip->dma1);
	पूर्ण
	अगर (!(chip->hwshare & WSS_HWSHARE_DMA2) &&
	    chip->dma2 >= 0 && chip->dma2 != chip->dma1) अणु
		snd_dma_disable(chip->dma2);
		मुक्त_dma(chip->dma2);
	पूर्ण
	अगर (chip->समयr)
		snd_device_मुक्त(chip->card, chip->समयr);
	kमुक्त(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_wss_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_wss *chip = device->device_data;
	वापस snd_wss_मुक्त(chip);
पूर्ण

स्थिर अक्षर *snd_wss_chip_id(काष्ठा snd_wss *chip)
अणु
	चयन (chip->hardware) अणु
	हाल WSS_HW_CS4231:
		वापस "CS4231";
	हाल WSS_HW_CS4231A:
		वापस "CS4231A";
	हाल WSS_HW_CS4232:
		वापस "CS4232";
	हाल WSS_HW_CS4232A:
		वापस "CS4232A";
	हाल WSS_HW_CS4235:
		वापस "CS4235";
	हाल WSS_HW_CS4236:
		वापस "CS4236";
	हाल WSS_HW_CS4236B:
		वापस "CS4236B";
	हाल WSS_HW_CS4237B:
		वापस "CS4237B";
	हाल WSS_HW_CS4238B:
		वापस "CS4238B";
	हाल WSS_HW_CS4239:
		वापस "CS4239";
	हाल WSS_HW_INTERWAVE:
		वापस "AMD InterWave";
	हाल WSS_HW_OPL3SA2:
		वापस chip->card->लघुname;
	हाल WSS_HW_AD1845:
		वापस "AD1845";
	हाल WSS_HW_OPTI93X:
		वापस "OPTi 93x";
	हाल WSS_HW_AD1847:
		वापस "AD1847";
	हाल WSS_HW_AD1848:
		वापस "AD1848";
	हाल WSS_HW_CS4248:
		वापस "CS4248";
	हाल WSS_HW_CMI8330:
		वापस "CMI8330/C3D";
	शेष:
		वापस "???";
	पूर्ण
पूर्ण
EXPORT_SYMBOL(snd_wss_chip_id);

अटल पूर्णांक snd_wss_new(काष्ठा snd_card *card,
			  अचिन्हित लघु hardware,
			  अचिन्हित लघु hwshare,
			  काष्ठा snd_wss **rchip)
अणु
	काष्ठा snd_wss *chip;

	*rchip = शून्य;
	chip = kzalloc(माप(*chip), GFP_KERNEL);
	अगर (chip == शून्य)
		वापस -ENOMEM;
	chip->hardware = hardware;
	chip->hwshare = hwshare;

	spin_lock_init(&chip->reg_lock);
	mutex_init(&chip->mce_mutex);
	mutex_init(&chip->खोलो_mutex);
	chip->card = card;
	chip->rate_स्थिरraपूर्णांक = snd_wss_xrate;
	chip->set_playback_क्रमmat = snd_wss_playback_क्रमmat;
	chip->set_capture_क्रमmat = snd_wss_capture_क्रमmat;
	अगर (chip->hardware == WSS_HW_OPTI93X)
		स_नकल(&chip->image, &snd_opti93x_original_image,
		       माप(snd_opti93x_original_image));
	अन्यथा
		स_नकल(&chip->image, &snd_wss_original_image,
		       माप(snd_wss_original_image));
	अगर (chip->hardware & WSS_HW_AD1848_MASK) अणु
		chip->image[CS4231_PIN_CTRL] = 0;
		chip->image[CS4231_TEST_INIT] = 0;
	पूर्ण

	*rchip = chip;
	वापस 0;
पूर्ण

पूर्णांक snd_wss_create(काष्ठा snd_card *card,
		      अचिन्हित दीर्घ port,
		      अचिन्हित दीर्घ cport,
		      पूर्णांक irq, पूर्णांक dma1, पूर्णांक dma2,
		      अचिन्हित लघु hardware,
		      अचिन्हित लघु hwshare,
		      काष्ठा snd_wss **rchip)
अणु
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =	snd_wss_dev_मुक्त,
	पूर्ण;
	काष्ठा snd_wss *chip;
	पूर्णांक err;

	err = snd_wss_new(card, hardware, hwshare, &chip);
	अगर (err < 0)
		वापस err;

	chip->irq = -1;
	chip->dma1 = -1;
	chip->dma2 = -1;

	chip->res_port = request_region(port, 4, "WSS");
	अगर (!chip->res_port) अणु
		snd_prपूर्णांकk(KERN_ERR "wss: can't grab port 0x%lx\n", port);
		snd_wss_मुक्त(chip);
		वापस -EBUSY;
	पूर्ण
	chip->port = port;
	अगर ((दीर्घ)cport >= 0) अणु
		chip->res_cport = request_region(cport, 8, "CS4232 Control");
		अगर (!chip->res_cport) अणु
			snd_prपूर्णांकk(KERN_ERR
				"wss: can't grab control port 0x%lx\n", cport);
			snd_wss_मुक्त(chip);
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	chip->cport = cport;
	अगर (!(hwshare & WSS_HWSHARE_IRQ))
		अगर (request_irq(irq, snd_wss_पूर्णांकerrupt, 0,
				"WSS", (व्योम *) chip)) अणु
			snd_prपूर्णांकk(KERN_ERR "wss: can't grab IRQ %d\n", irq);
			snd_wss_मुक्त(chip);
			वापस -EBUSY;
		पूर्ण
	chip->irq = irq;
	card->sync_irq = chip->irq;
	अगर (!(hwshare & WSS_HWSHARE_DMA1) && request_dma(dma1, "WSS - 1")) अणु
		snd_prपूर्णांकk(KERN_ERR "wss: can't grab DMA1 %d\n", dma1);
		snd_wss_मुक्त(chip);
		वापस -EBUSY;
	पूर्ण
	chip->dma1 = dma1;
	अगर (!(hwshare & WSS_HWSHARE_DMA2) && dma1 != dma2 &&
	      dma2 >= 0 && request_dma(dma2, "WSS - 2")) अणु
		snd_prपूर्णांकk(KERN_ERR "wss: can't grab DMA2 %d\n", dma2);
		snd_wss_मुक्त(chip);
		वापस -EBUSY;
	पूर्ण
	अगर (dma1 == dma2 || dma2 < 0) अणु
		chip->single_dma = 1;
		chip->dma2 = chip->dma1;
	पूर्ण अन्यथा
		chip->dma2 = dma2;

	अगर (hardware == WSS_HW_THINKPAD) अणु
		chip->thinkpad_flag = 1;
		chip->hardware = WSS_HW_DETECT; /* reset */
		snd_wss_thinkpad_twiddle(chip, 1);
	पूर्ण

	/* global setup */
	अगर (snd_wss_probe(chip) < 0) अणु
		snd_wss_मुक्त(chip);
		वापस -ENODEV;
	पूर्ण
	snd_wss_init(chip);

#अगर 0
	अगर (chip->hardware & WSS_HW_CS4232_MASK) अणु
		अगर (chip->res_cport == शून्य)
			snd_prपूर्णांकk(KERN_ERR "CS4232 control port features are "
				   "not accessible\n");
	पूर्ण
#पूर्ण_अगर

	/* Register device */
	err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops);
	अगर (err < 0) अणु
		snd_wss_मुक्त(chip);
		वापस err;
	पूर्ण

#अगर_घोषित CONFIG_PM
	/* Power Management */
	chip->suspend = snd_wss_suspend;
	chip->resume = snd_wss_resume;
#पूर्ण_अगर

	*rchip = chip;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_wss_create);

अटल स्थिर काष्ठा snd_pcm_ops snd_wss_playback_ops = अणु
	.खोलो =		snd_wss_playback_खोलो,
	.बंद =	snd_wss_playback_बंद,
	.hw_params =	snd_wss_playback_hw_params,
	.prepare =	snd_wss_playback_prepare,
	.trigger =	snd_wss_trigger,
	.poपूर्णांकer =	snd_wss_playback_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_wss_capture_ops = अणु
	.खोलो =		snd_wss_capture_खोलो,
	.बंद =	snd_wss_capture_बंद,
	.hw_params =	snd_wss_capture_hw_params,
	.prepare =	snd_wss_capture_prepare,
	.trigger =	snd_wss_trigger,
	.poपूर्णांकer =	snd_wss_capture_poपूर्णांकer,
पूर्ण;

पूर्णांक snd_wss_pcm(काष्ठा snd_wss *chip, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	err = snd_pcm_new(chip->card, "WSS", device, 1, 1, &pcm);
	अगर (err < 0)
		वापस err;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_wss_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_wss_capture_ops);

	/* global setup */
	pcm->निजी_data = chip;
	pcm->info_flags = 0;
	अगर (chip->single_dma)
		pcm->info_flags |= SNDRV_PCM_INFO_HALF_DUPLEX;
	अगर (chip->hardware != WSS_HW_INTERWAVE)
		pcm->info_flags |= SNDRV_PCM_INFO_JOINT_DUPLEX;
	म_नकल(pcm->name, snd_wss_chip_id(chip));

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV, chip->card->dev,
				       64*1024, chip->dma1 > 3 || chip->dma2 > 3 ? 128*1024 : 64*1024);

	chip->pcm = pcm;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_wss_pcm);

अटल व्योम snd_wss_समयr_मुक्त(काष्ठा snd_समयr *समयr)
अणु
	काष्ठा snd_wss *chip = समयr->निजी_data;
	chip->समयr = शून्य;
पूर्ण

पूर्णांक snd_wss_समयr(काष्ठा snd_wss *chip, पूर्णांक device)
अणु
	काष्ठा snd_समयr *समयr;
	काष्ठा snd_समयr_id tid;
	पूर्णांक err;

	/* Timer initialization */
	tid.dev_class = SNDRV_TIMER_CLASS_CARD;
	tid.dev_sclass = SNDRV_TIMER_SCLASS_NONE;
	tid.card = chip->card->number;
	tid.device = device;
	tid.subdevice = 0;
	अगर ((err = snd_समयr_new(chip->card, "CS4231", &tid, &समयr)) < 0)
		वापस err;
	म_नकल(समयr->name, snd_wss_chip_id(chip));
	समयr->निजी_data = chip;
	समयr->निजी_मुक्त = snd_wss_समयr_मुक्त;
	समयr->hw = snd_wss_समयr_table;
	chip->समयr = समयr;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_wss_समयr);

/*
 *  MIXER part
 */

अटल पूर्णांक snd_wss_info_mux(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[4] = अणु
		"Line", "Aux", "Mic", "Mix"
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर opl3sa_texts[4] = अणु
		"Line", "CD", "Mic", "Mix"
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर gusmax_texts[4] = अणु
		"Line", "Synth", "Mic", "Mix"
	पूर्ण;
	स्थिर अक्षर * स्थिर *ptexts = texts;
	काष्ठा snd_wss *chip = snd_kcontrol_chip(kcontrol);

	अगर (snd_BUG_ON(!chip->card))
		वापस -EINVAL;
	अगर (!म_भेद(chip->card->driver, "GUS MAX"))
		ptexts = gusmax_texts;
	चयन (chip->hardware) अणु
	हाल WSS_HW_INTERWAVE:
		ptexts = gusmax_texts;
		अवरोध;
	हाल WSS_HW_OPTI93X:
	हाल WSS_HW_OPL3SA2:
		ptexts = opl3sa_texts;
		अवरोध;
	पूर्ण
	वापस snd_ctl_क्रमागत_info(uinfo, 2, 4, ptexts);
पूर्ण

अटल पूर्णांक snd_wss_get_mux(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_wss *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->reg_lock, flags);
	ucontrol->value.क्रमागतerated.item[0] = (chip->image[CS4231_LEFT_INPUT] & CS4231_MIXS_ALL) >> 6;
	ucontrol->value.क्रमागतerated.item[1] = (chip->image[CS4231_RIGHT_INPUT] & CS4231_MIXS_ALL) >> 6;
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_wss_put_mux(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_wss *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	अचिन्हित लघु left, right;
	पूर्णांक change;

	अगर (ucontrol->value.क्रमागतerated.item[0] > 3 ||
	    ucontrol->value.क्रमागतerated.item[1] > 3)
		वापस -EINVAL;
	left = ucontrol->value.क्रमागतerated.item[0] << 6;
	right = ucontrol->value.क्रमागतerated.item[1] << 6;
	spin_lock_irqsave(&chip->reg_lock, flags);
	left = (chip->image[CS4231_LEFT_INPUT] & ~CS4231_MIXS_ALL) | left;
	right = (chip->image[CS4231_RIGHT_INPUT] & ~CS4231_MIXS_ALL) | right;
	change = left != chip->image[CS4231_LEFT_INPUT] ||
		 right != chip->image[CS4231_RIGHT_INPUT];
	snd_wss_out(chip, CS4231_LEFT_INPUT, left);
	snd_wss_out(chip, CS4231_RIGHT_INPUT, right);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस change;
पूर्ण

पूर्णांक snd_wss_info_single(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;

	uinfo->type = mask == 1 ? SNDRV_CTL_ELEM_TYPE_BOOLEAN : SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = mask;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_wss_info_single);

पूर्णांक snd_wss_get_single(काष्ठा snd_kcontrol *kcontrol,
		       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_wss *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 24) & 0xff;

	spin_lock_irqsave(&chip->reg_lock, flags);
	ucontrol->value.पूर्णांकeger.value[0] = (chip->image[reg] >> shअगरt) & mask;
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	अगर (invert)
		ucontrol->value.पूर्णांकeger.value[0] = mask - ucontrol->value.पूर्णांकeger.value[0];
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_wss_get_single);

पूर्णांक snd_wss_put_single(काष्ठा snd_kcontrol *kcontrol,
		       काष्ठा snd_ctl_elem_value *ucontrol)
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
	val = (chip->image[reg] & ~(mask << shअगरt)) | val;
	change = val != chip->image[reg];
	snd_wss_out(chip, reg, val);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस change;
पूर्ण
EXPORT_SYMBOL(snd_wss_put_single);

पूर्णांक snd_wss_info_द्विगुन(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक mask = (kcontrol->निजी_value >> 24) & 0xff;

	uinfo->type = mask == 1 ? SNDRV_CTL_ELEM_TYPE_BOOLEAN : SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = mask;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_wss_info_द्विगुन);

पूर्णांक snd_wss_get_द्विगुन(काष्ठा snd_kcontrol *kcontrol,
		       काष्ठा snd_ctl_elem_value *ucontrol)
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
	ucontrol->value.पूर्णांकeger.value[1] = (chip->image[right_reg] >> shअगरt_right) & mask;
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	अगर (invert) अणु
		ucontrol->value.पूर्णांकeger.value[0] = mask - ucontrol->value.पूर्णांकeger.value[0];
		ucontrol->value.पूर्णांकeger.value[1] = mask - ucontrol->value.पूर्णांकeger.value[1];
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_wss_get_द्विगुन);

पूर्णांक snd_wss_put_द्विगुन(काष्ठा snd_kcontrol *kcontrol,
		       काष्ठा snd_ctl_elem_value *ucontrol)
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
		val1 = (chip->image[left_reg] & ~(mask << shअगरt_left)) | val1;
		val2 = (chip->image[right_reg] & ~(mask << shअगरt_right)) | val2;
		change = val1 != chip->image[left_reg] ||
			 val2 != chip->image[right_reg];
		snd_wss_out(chip, left_reg, val1);
		snd_wss_out(chip, right_reg, val2);
	पूर्ण अन्यथा अणु
		mask = (mask << shअगरt_left) | (mask << shअगरt_right);
		val1 = (chip->image[left_reg] & ~mask) | val1 | val2;
		change = val1 != chip->image[left_reg];
		snd_wss_out(chip, left_reg, val1);
	पूर्ण
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस change;
पूर्ण
EXPORT_SYMBOL(snd_wss_put_द्विगुन);

अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_6bit, -9450, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_5bit_12db_max, -3450, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_rec_gain, 0, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_4bit, -4500, 300, 0);

अटल स्थिर काष्ठा snd_kcontrol_new snd_wss_controls[] = अणु
WSS_DOUBLE("PCM Playback Switch", 0,
		CS4231_LEFT_OUTPUT, CS4231_RIGHT_OUTPUT, 7, 7, 1, 1),
WSS_DOUBLE_TLV("PCM Playback Volume", 0,
		CS4231_LEFT_OUTPUT, CS4231_RIGHT_OUTPUT, 0, 0, 63, 1,
		db_scale_6bit),
WSS_DOUBLE("Aux Playback Switch", 0,
		CS4231_AUX1_LEFT_INPUT, CS4231_AUX1_RIGHT_INPUT, 7, 7, 1, 1),
WSS_DOUBLE_TLV("Aux Playback Volume", 0,
		CS4231_AUX1_LEFT_INPUT, CS4231_AUX1_RIGHT_INPUT, 0, 0, 31, 1,
		db_scale_5bit_12db_max),
WSS_DOUBLE("Aux Playback Switch", 1,
		CS4231_AUX2_LEFT_INPUT, CS4231_AUX2_RIGHT_INPUT, 7, 7, 1, 1),
WSS_DOUBLE_TLV("Aux Playback Volume", 1,
		CS4231_AUX2_LEFT_INPUT, CS4231_AUX2_RIGHT_INPUT, 0, 0, 31, 1,
		db_scale_5bit_12db_max),
WSS_DOUBLE_TLV("Capture Volume", 0, CS4231_LEFT_INPUT, CS4231_RIGHT_INPUT,
		0, 0, 15, 0, db_scale_rec_gain),
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Capture Source",
	.info = snd_wss_info_mux,
	.get = snd_wss_get_mux,
	.put = snd_wss_put_mux,
पूर्ण,
WSS_DOUBLE("Mic Boost (+20dB)", 0,
		CS4231_LEFT_INPUT, CS4231_RIGHT_INPUT, 5, 5, 1, 0),
WSS_SINGLE("Loopback Capture Switch", 0,
		CS4231_LOOPBACK, 0, 1, 0),
WSS_SINGLE_TLV("Loopback Capture Volume", 0, CS4231_LOOPBACK, 2, 63, 1,
		db_scale_6bit),
WSS_DOUBLE("Line Playback Switch", 0,
		CS4231_LEFT_LINE_IN, CS4231_RIGHT_LINE_IN, 7, 7, 1, 1),
WSS_DOUBLE_TLV("Line Playback Volume", 0,
		CS4231_LEFT_LINE_IN, CS4231_RIGHT_LINE_IN, 0, 0, 31, 1,
		db_scale_5bit_12db_max),
WSS_SINGLE("Beep Playback Switch", 0,
		CS4231_MONO_CTRL, 7, 1, 1),
WSS_SINGLE_TLV("Beep Playback Volume", 0,
		CS4231_MONO_CTRL, 0, 15, 1,
		db_scale_4bit),
WSS_SINGLE("Mono Output Playback Switch", 0,
		CS4231_MONO_CTRL, 6, 1, 1),
WSS_SINGLE("Beep Bypass Playback Switch", 0,
		CS4231_MONO_CTRL, 5, 1, 0),
पूर्ण;

पूर्णांक snd_wss_mixer(काष्ठा snd_wss *chip)
अणु
	काष्ठा snd_card *card;
	अचिन्हित पूर्णांक idx;
	पूर्णांक err;
	पूर्णांक count = ARRAY_SIZE(snd_wss_controls);

	अगर (snd_BUG_ON(!chip || !chip->pcm))
		वापस -EINVAL;

	card = chip->card;

	म_नकल(card->mixername, chip->pcm->name);

	/* Use only the first 11 entries on AD1848 */
	अगर (chip->hardware & WSS_HW_AD1848_MASK)
		count = 11;
	/* There is no loopback on OPTI93X */
	अन्यथा अगर (chip->hardware == WSS_HW_OPTI93X)
		count = 9;

	क्रम (idx = 0; idx < count; idx++) अणु
		err = snd_ctl_add(card,
				snd_ctl_new1(&snd_wss_controls[idx],
					     chip));
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_wss_mixer);

स्थिर काष्ठा snd_pcm_ops *snd_wss_get_pcm_ops(पूर्णांक direction)
अणु
	वापस direction == SNDRV_PCM_STREAM_PLAYBACK ?
		&snd_wss_playback_ops : &snd_wss_capture_ops;
पूर्ण
EXPORT_SYMBOL(snd_wss_get_pcm_ops);
