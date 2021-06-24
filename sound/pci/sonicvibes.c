<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम S3 SonicVibes soundcard
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *
 *  BUGS:
 *    It looks like 86c617 rev 3 करोesn't supports DDMA buffers above 16MB?
 *    Driver someबार hangs... Nobody knows why at this moment...
 */

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/gameport.h>
#समावेश <linux/module.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/info.h>
#समावेश <sound/control.h>
#समावेश <sound/mpu401.h>
#समावेश <sound/opl3.h>
#समावेश <sound/initval.h>

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("S3 SonicVibes PCI");
MODULE_LICENSE("GPL");

#अगर IS_REACHABLE(CONFIG_GAMEPORT)
#घोषणा SUPPORT_JOYSTICK 1
#पूर्ण_अगर

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;	/* Enable this card */
अटल bool reverb[SNDRV_CARDS];
अटल bool mge[SNDRV_CARDS];
अटल अचिन्हित पूर्णांक dmaio = 0x7a00;	/* DDMA i/o address */

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for S3 SonicVibes soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for S3 SonicVibes soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable S3 SonicVibes soundcard.");
module_param_array(reverb, bool, शून्य, 0444);
MODULE_PARM_DESC(reverb, "Enable reverb (SRAM is present) for S3 SonicVibes soundcard.");
module_param_array(mge, bool, शून्य, 0444);
MODULE_PARM_DESC(mge, "MIC Gain Enable for S3 SonicVibes soundcard.");
module_param_hw(dmaio, uपूर्णांक, ioport, 0444);
MODULE_PARM_DESC(dmaio, "DDMA i/o base address for S3 SonicVibes soundcard.");

/*
 * Enhanced port direct रेजिस्टरs
 */

#घोषणा SV_REG(sonic, x) ((sonic)->enh_port + SV_REG_##x)

#घोषणा SV_REG_CONTROL	0x00	/* R/W: CODEC/Mixer control रेजिस्टर */
#घोषणा   SV_ENHANCED	  0x01	/* audio mode select - enhanced mode */
#घोषणा   SV_TEST	  0x02	/* test bit */
#घोषणा   SV_REVERB	  0x04	/* reverb enable */
#घोषणा   SV_WAVETABLE	  0x08	/* wavetable active / FM active अगर not set */
#घोषणा   SV_INTA	  0x20	/* INTA driving - should be always 1 */
#घोषणा   SV_RESET	  0x80	/* reset chip */
#घोषणा SV_REG_IRQMASK	0x01	/* R/W: CODEC/Mixer पूर्णांकerrupt mask रेजिस्टर */
#घोषणा   SV_DMAA_MASK	  0x01	/* mask DMA-A पूर्णांकerrupt */
#घोषणा   SV_DMAC_MASK	  0x04	/* mask DMA-C पूर्णांकerrupt */
#घोषणा   SV_SPEC_MASK	  0x08	/* special पूर्णांकerrupt mask - should be always masked */
#घोषणा   SV_UD_MASK	  0x40	/* Up/Down button पूर्णांकerrupt mask */
#घोषणा   SV_MIDI_MASK	  0x80	/* mask MIDI पूर्णांकerrupt */
#घोषणा SV_REG_STATUS	0x02	/* R/O: CODEC/Mixer status रेजिस्टर */
#घोषणा   SV_DMAA_IRQ	  0x01	/* DMA-A पूर्णांकerrupt */
#घोषणा   SV_DMAC_IRQ	  0x04	/* DMA-C पूर्णांकerrupt */
#घोषणा   SV_SPEC_IRQ	  0x08	/* special पूर्णांकerrupt */
#घोषणा   SV_UD_IRQ	  0x40	/* Up/Down पूर्णांकerrupt */
#घोषणा   SV_MIDI_IRQ	  0x80	/* MIDI पूर्णांकerrupt */
#घोषणा SV_REG_INDEX	0x04	/* R/W: CODEC/Mixer index address रेजिस्टर */
#घोषणा   SV_MCE          0x40	/* mode change enable */
#घोषणा   SV_TRD	  0x80	/* DMA transfer request disabled */
#घोषणा SV_REG_DATA	0x05	/* R/W: CODEC/Mixer index data रेजिस्टर */

/*
 * Enhanced port indirect रेजिस्टरs
 */

#घोषणा SV_IREG_LEFT_ADC	0x00	/* Left ADC Input Control */
#घोषणा SV_IREG_RIGHT_ADC	0x01	/* Right ADC Input Control */
#घोषणा SV_IREG_LEFT_AUX1	0x02	/* Left AUX1 Input Control */
#घोषणा SV_IREG_RIGHT_AUX1	0x03	/* Right AUX1 Input Control */
#घोषणा SV_IREG_LEFT_CD		0x04	/* Left CD Input Control */
#घोषणा SV_IREG_RIGHT_CD	0x05	/* Right CD Input Control */
#घोषणा SV_IREG_LEFT_LINE	0x06	/* Left Line Input Control */
#घोषणा SV_IREG_RIGHT_LINE	0x07	/* Right Line Input Control */
#घोषणा SV_IREG_MIC		0x08	/* MIC Input Control */
#घोषणा SV_IREG_GAME_PORT	0x09	/* Game Port Control */
#घोषणा SV_IREG_LEFT_SYNTH	0x0a	/* Left Synth Input Control */
#घोषणा SV_IREG_RIGHT_SYNTH	0x0b	/* Right Synth Input Control */
#घोषणा SV_IREG_LEFT_AUX2	0x0c	/* Left AUX2 Input Control */
#घोषणा SV_IREG_RIGHT_AUX2	0x0d	/* Right AUX2 Input Control */
#घोषणा SV_IREG_LEFT_ANALOG	0x0e	/* Left Analog Mixer Output Control */
#घोषणा SV_IREG_RIGHT_ANALOG	0x0f	/* Right Analog Mixer Output Control */
#घोषणा SV_IREG_LEFT_PCM	0x10	/* Left PCM Input Control */
#घोषणा SV_IREG_RIGHT_PCM	0x11	/* Right PCM Input Control */
#घोषणा SV_IREG_DMA_DATA_FMT	0x12	/* DMA Data Format */
#घोषणा SV_IREG_PC_ENABLE	0x13	/* Playback/Capture Enable Register */
#घोषणा SV_IREG_UD_BUTTON	0x14	/* Up/Down Button Register */
#घोषणा SV_IREG_REVISION	0x15	/* Revision */
#घोषणा SV_IREG_ADC_OUTPUT_CTRL	0x16	/* ADC Output Control */
#घोषणा SV_IREG_DMA_A_UPPER	0x18	/* DMA A Upper Base Count */
#घोषणा SV_IREG_DMA_A_LOWER	0x19	/* DMA A Lower Base Count */
#घोषणा SV_IREG_DMA_C_UPPER	0x1c	/* DMA C Upper Base Count */
#घोषणा SV_IREG_DMA_C_LOWER	0x1d	/* DMA C Lower Base Count */
#घोषणा SV_IREG_PCM_RATE_LOW	0x1e	/* PCM Sampling Rate Low Byte */
#घोषणा SV_IREG_PCM_RATE_HIGH	0x1f	/* PCM Sampling Rate High Byte */
#घोषणा SV_IREG_SYNTH_RATE_LOW	0x20	/* Synthesizer Sampling Rate Low Byte */
#घोषणा SV_IREG_SYNTH_RATE_HIGH 0x21	/* Synthesizer Sampling Rate High Byte */
#घोषणा SV_IREG_ADC_CLOCK	0x22	/* ADC Clock Source Selection */
#घोषणा SV_IREG_ADC_ALT_RATE	0x23	/* ADC Alternative Sampling Rate Selection */
#घोषणा SV_IREG_ADC_PLL_M	0x24	/* ADC PLL M Register */
#घोषणा SV_IREG_ADC_PLL_N	0x25	/* ADC PLL N Register */
#घोषणा SV_IREG_SYNTH_PLL_M	0x26	/* Synthesizer PLL M Register */
#घोषणा SV_IREG_SYNTH_PLL_N	0x27	/* Synthesizer PLL N Register */
#घोषणा SV_IREG_MPU401		0x2a	/* MPU-401 UART Operation */
#घोषणा SV_IREG_DRIVE_CTRL	0x2b	/* Drive Control */
#घोषणा SV_IREG_SRS_SPACE	0x2c	/* SRS Space Control */
#घोषणा SV_IREG_SRS_CENTER	0x2d	/* SRS Center Control */
#घोषणा SV_IREG_WAVE_SOURCE	0x2e	/* Wavetable Sample Source Select */
#घोषणा SV_IREG_ANALOG_POWER	0x30	/* Analog Power Down Control */
#घोषणा SV_IREG_DIGITAL_POWER	0x31	/* Digital Power Down Control */

#घोषणा SV_IREG_ADC_PLL		SV_IREG_ADC_PLL_M
#घोषणा SV_IREG_SYNTH_PLL	SV_IREG_SYNTH_PLL_M

/*
 *  DMA रेजिस्टरs
 */

#घोषणा SV_DMA_ADDR0		0x00
#घोषणा SV_DMA_ADDR1		0x01
#घोषणा SV_DMA_ADDR2		0x02
#घोषणा SV_DMA_ADDR3		0x03
#घोषणा SV_DMA_COUNT0		0x04
#घोषणा SV_DMA_COUNT1		0x05
#घोषणा SV_DMA_COUNT2		0x06
#घोषणा SV_DMA_MODE		0x0b
#घोषणा SV_DMA_RESET		0x0d
#घोषणा SV_DMA_MASK		0x0f

/*
 *  Record sources
 */

#घोषणा SV_RECSRC_RESERVED	(0x00<<5)
#घोषणा SV_RECSRC_CD		(0x01<<5)
#घोषणा SV_RECSRC_DAC		(0x02<<5)
#घोषणा SV_RECSRC_AUX2		(0x03<<5)
#घोषणा SV_RECSRC_LINE		(0x04<<5)
#घोषणा SV_RECSRC_AUX1		(0x05<<5)
#घोषणा SV_RECSRC_MIC		(0x06<<5)
#घोषणा SV_RECSRC_OUT		(0x07<<5)

/*
 *  स्थिरants
 */

#घोषणा SV_FULLRATE		48000
#घोषणा SV_REFFREQUENCY		24576000
#घोषणा SV_ADCMULT		512

#घोषणा SV_MODE_PLAY		1
#घोषणा SV_MODE_CAPTURE		2

/*

 */

काष्ठा sonicvibes अणु
	अचिन्हित दीर्घ dma1size;
	अचिन्हित दीर्घ dma2size;
	पूर्णांक irq;

	अचिन्हित दीर्घ sb_port;
	अचिन्हित दीर्घ enh_port;
	अचिन्हित दीर्घ synth_port;
	अचिन्हित दीर्घ midi_port;
	अचिन्हित दीर्घ game_port;
	अचिन्हित पूर्णांक dmaa_port;
	काष्ठा resource *res_dmaa;
	अचिन्हित पूर्णांक dmac_port;
	काष्ठा resource *res_dmac;

	अचिन्हित अक्षर enable;
	अचिन्हित अक्षर irqmask;
	अचिन्हित अक्षर revision;
	अचिन्हित अक्षर क्रमmat;
	अचिन्हित अक्षर srs_space;
	अचिन्हित अक्षर srs_center;
	अचिन्हित अक्षर mpu_चयन;
	अचिन्हित अक्षर wave_source;

	अचिन्हित पूर्णांक mode;

	काष्ठा pci_dev *pci;
	काष्ठा snd_card *card;
	काष्ठा snd_pcm *pcm;
	काष्ठा snd_pcm_substream *playback_substream;
	काष्ठा snd_pcm_substream *capture_substream;
	काष्ठा snd_rawmidi *rmidi;
	काष्ठा snd_hwdep *fmsynth;	/* S3FM */

	spinlock_t reg_lock;

	अचिन्हित पूर्णांक p_dma_size;
	अचिन्हित पूर्णांक c_dma_size;

	काष्ठा snd_kcontrol *master_mute;
	काष्ठा snd_kcontrol *master_volume;

#अगर_घोषित SUPPORT_JOYSTICK
	काष्ठा gameport *gameport;
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा pci_device_id snd_sonic_ids[] = अणु
	अणु PCI_VDEVICE(S3, 0xca00), 0, पूर्ण,
        अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, snd_sonic_ids);

अटल स्थिर काष्ठा snd_ratden sonicvibes_adc_घड़ी = अणु
	.num_min = 4000 * 65536,
	.num_max = 48000UL * 65536,
	.num_step = 1,
	.den = 65536,
पूर्ण;
अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_ratdens snd_sonicvibes_hw_स्थिरraपूर्णांकs_adc_घड़ी = अणु
	.nrats = 1,
	.rats = &sonicvibes_adc_घड़ी,
पूर्ण;

/*
 *  common I/O routines
 */

अटल अंतरभूत व्योम snd_sonicvibes_setdmaa(काष्ठा sonicvibes * sonic,
					  अचिन्हित पूर्णांक addr,
					  अचिन्हित पूर्णांक count)
अणु
	count--;
	outl(addr, sonic->dmaa_port + SV_DMA_ADDR0);
	outl(count, sonic->dmaa_port + SV_DMA_COUNT0);
	outb(0x18, sonic->dmaa_port + SV_DMA_MODE);
#अगर 0
	dev_dbg(sonic->card->dev, "program dmaa: addr = 0x%x, paddr = 0x%x\n",
	       addr, inl(sonic->dmaa_port + SV_DMA_ADDR0));
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम snd_sonicvibes_setdmac(काष्ठा sonicvibes * sonic,
					  अचिन्हित पूर्णांक addr,
					  अचिन्हित पूर्णांक count)
अणु
	/* note: dmac is working in word mode!!! */
	count >>= 1;
	count--;
	outl(addr, sonic->dmac_port + SV_DMA_ADDR0);
	outl(count, sonic->dmac_port + SV_DMA_COUNT0);
	outb(0x14, sonic->dmac_port + SV_DMA_MODE);
#अगर 0
	dev_dbg(sonic->card->dev, "program dmac: addr = 0x%x, paddr = 0x%x\n",
	       addr, inl(sonic->dmac_port + SV_DMA_ADDR0));
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक snd_sonicvibes_getdmaa(काष्ठा sonicvibes * sonic)
अणु
	वापस (inl(sonic->dmaa_port + SV_DMA_COUNT0) & 0xffffff) + 1;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक snd_sonicvibes_getdmac(काष्ठा sonicvibes * sonic)
अणु
	/* note: dmac is working in word mode!!! */
	वापस ((inl(sonic->dmac_port + SV_DMA_COUNT0) & 0xffffff) + 1) << 1;
पूर्ण

अटल व्योम snd_sonicvibes_out1(काष्ठा sonicvibes * sonic,
				अचिन्हित अक्षर reg,
				अचिन्हित अक्षर value)
अणु
	outb(reg, SV_REG(sonic, INDEX));
	udelay(10);
	outb(value, SV_REG(sonic, DATA));
	udelay(10);
पूर्ण

अटल व्योम snd_sonicvibes_out(काष्ठा sonicvibes * sonic,
			       अचिन्हित अक्षर reg,
			       अचिन्हित अक्षर value)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sonic->reg_lock, flags);
	outb(reg, SV_REG(sonic, INDEX));
	udelay(10);
	outb(value, SV_REG(sonic, DATA));
	udelay(10);
	spin_unlock_irqrestore(&sonic->reg_lock, flags);
पूर्ण

अटल अचिन्हित अक्षर snd_sonicvibes_in1(काष्ठा sonicvibes * sonic, अचिन्हित अक्षर reg)
अणु
	अचिन्हित अक्षर value;

	outb(reg, SV_REG(sonic, INDEX));
	udelay(10);
	value = inb(SV_REG(sonic, DATA));
	udelay(10);
	वापस value;
पूर्ण

अटल अचिन्हित अक्षर snd_sonicvibes_in(काष्ठा sonicvibes * sonic, अचिन्हित अक्षर reg)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर value;

	spin_lock_irqsave(&sonic->reg_lock, flags);
	outb(reg, SV_REG(sonic, INDEX));
	udelay(10);
	value = inb(SV_REG(sonic, DATA));
	udelay(10);
	spin_unlock_irqrestore(&sonic->reg_lock, flags);
	वापस value;
पूर्ण

#अगर 0
अटल व्योम snd_sonicvibes_debug(काष्ठा sonicvibes * sonic)
अणु
	dev_dbg(sonic->card->dev,
		"SV REGS:          INDEX = 0x%02x                   STATUS = 0x%02x\n",
		inb(SV_REG(sonic, INDEX)), inb(SV_REG(sonic, STATUS)));
	dev_dbg(sonic->card->dev,
		"  0x00: left input      = 0x%02x    0x20: synth rate low  = 0x%02x\n",
		snd_sonicvibes_in(sonic, 0x00), snd_sonicvibes_in(sonic, 0x20));
	dev_dbg(sonic->card->dev,
		"  0x01: right input     = 0x%02x    0x21: synth rate high = 0x%02x\n",
		snd_sonicvibes_in(sonic, 0x01), snd_sonicvibes_in(sonic, 0x21));
	dev_dbg(sonic->card->dev,
		"  0x02: left AUX1       = 0x%02x    0x22: ADC clock       = 0x%02x\n",
		snd_sonicvibes_in(sonic, 0x02), snd_sonicvibes_in(sonic, 0x22));
	dev_dbg(sonic->card->dev,
		"  0x03: right AUX1      = 0x%02x    0x23: ADC alt rate    = 0x%02x\n",
		snd_sonicvibes_in(sonic, 0x03), snd_sonicvibes_in(sonic, 0x23));
	dev_dbg(sonic->card->dev,
		"  0x04: left CD         = 0x%02x    0x24: ADC pll M       = 0x%02x\n",
		snd_sonicvibes_in(sonic, 0x04), snd_sonicvibes_in(sonic, 0x24));
	dev_dbg(sonic->card->dev,
		"  0x05: right CD        = 0x%02x    0x25: ADC pll N       = 0x%02x\n",
		snd_sonicvibes_in(sonic, 0x05), snd_sonicvibes_in(sonic, 0x25));
	dev_dbg(sonic->card->dev,
		"  0x06: left line       = 0x%02x    0x26: Synth pll M     = 0x%02x\n",
		snd_sonicvibes_in(sonic, 0x06), snd_sonicvibes_in(sonic, 0x26));
	dev_dbg(sonic->card->dev,
		"  0x07: right line      = 0x%02x    0x27: Synth pll N     = 0x%02x\n",
		snd_sonicvibes_in(sonic, 0x07), snd_sonicvibes_in(sonic, 0x27));
	dev_dbg(sonic->card->dev,
		"  0x08: MIC             = 0x%02x    0x28: ---             = 0x%02x\n",
		snd_sonicvibes_in(sonic, 0x08), snd_sonicvibes_in(sonic, 0x28));
	dev_dbg(sonic->card->dev,
		"  0x09: Game port       = 0x%02x    0x29: ---             = 0x%02x\n",
		snd_sonicvibes_in(sonic, 0x09), snd_sonicvibes_in(sonic, 0x29));
	dev_dbg(sonic->card->dev,
		"  0x0a: left synth      = 0x%02x    0x2a: MPU401          = 0x%02x\n",
		snd_sonicvibes_in(sonic, 0x0a), snd_sonicvibes_in(sonic, 0x2a));
	dev_dbg(sonic->card->dev,
		"  0x0b: right synth     = 0x%02x    0x2b: drive ctrl      = 0x%02x\n",
		snd_sonicvibes_in(sonic, 0x0b), snd_sonicvibes_in(sonic, 0x2b));
	dev_dbg(sonic->card->dev,
		"  0x0c: left AUX2       = 0x%02x    0x2c: SRS space       = 0x%02x\n",
		snd_sonicvibes_in(sonic, 0x0c), snd_sonicvibes_in(sonic, 0x2c));
	dev_dbg(sonic->card->dev,
		"  0x0d: right AUX2      = 0x%02x    0x2d: SRS center      = 0x%02x\n",
		snd_sonicvibes_in(sonic, 0x0d), snd_sonicvibes_in(sonic, 0x2d));
	dev_dbg(sonic->card->dev,
		"  0x0e: left analog     = 0x%02x    0x2e: wave source     = 0x%02x\n",
		snd_sonicvibes_in(sonic, 0x0e), snd_sonicvibes_in(sonic, 0x2e));
	dev_dbg(sonic->card->dev,
		"  0x0f: right analog    = 0x%02x    0x2f: ---             = 0x%02x\n",
		snd_sonicvibes_in(sonic, 0x0f), snd_sonicvibes_in(sonic, 0x2f));
	dev_dbg(sonic->card->dev,
		"  0x10: left PCM        = 0x%02x    0x30: analog power    = 0x%02x\n",
		snd_sonicvibes_in(sonic, 0x10), snd_sonicvibes_in(sonic, 0x30));
	dev_dbg(sonic->card->dev,
		"  0x11: right PCM       = 0x%02x    0x31: analog power    = 0x%02x\n",
		snd_sonicvibes_in(sonic, 0x11), snd_sonicvibes_in(sonic, 0x31));
	dev_dbg(sonic->card->dev,
		"  0x12: DMA data format = 0x%02x    0x32: ---             = 0x%02x\n",
		snd_sonicvibes_in(sonic, 0x12), snd_sonicvibes_in(sonic, 0x32));
	dev_dbg(sonic->card->dev,
		"  0x13: P/C enable      = 0x%02x    0x33: ---             = 0x%02x\n",
		snd_sonicvibes_in(sonic, 0x13), snd_sonicvibes_in(sonic, 0x33));
	dev_dbg(sonic->card->dev,
		"  0x14: U/D button      = 0x%02x    0x34: ---             = 0x%02x\n",
		snd_sonicvibes_in(sonic, 0x14), snd_sonicvibes_in(sonic, 0x34));
	dev_dbg(sonic->card->dev,
		"  0x15: revision        = 0x%02x    0x35: ---             = 0x%02x\n",
		snd_sonicvibes_in(sonic, 0x15), snd_sonicvibes_in(sonic, 0x35));
	dev_dbg(sonic->card->dev,
		"  0x16: ADC output ctrl = 0x%02x    0x36: ---             = 0x%02x\n",
		snd_sonicvibes_in(sonic, 0x16), snd_sonicvibes_in(sonic, 0x36));
	dev_dbg(sonic->card->dev,
		"  0x17: ---             = 0x%02x    0x37: ---             = 0x%02x\n",
		snd_sonicvibes_in(sonic, 0x17), snd_sonicvibes_in(sonic, 0x37));
	dev_dbg(sonic->card->dev,
		"  0x18: DMA A upper cnt = 0x%02x    0x38: ---             = 0x%02x\n",
		snd_sonicvibes_in(sonic, 0x18), snd_sonicvibes_in(sonic, 0x38));
	dev_dbg(sonic->card->dev,
		"  0x19: DMA A lower cnt = 0x%02x    0x39: ---             = 0x%02x\n",
		snd_sonicvibes_in(sonic, 0x19), snd_sonicvibes_in(sonic, 0x39));
	dev_dbg(sonic->card->dev,
		"  0x1a: ---             = 0x%02x    0x3a: ---             = 0x%02x\n",
		snd_sonicvibes_in(sonic, 0x1a), snd_sonicvibes_in(sonic, 0x3a));
	dev_dbg(sonic->card->dev,
		"  0x1b: ---             = 0x%02x    0x3b: ---             = 0x%02x\n",
		snd_sonicvibes_in(sonic, 0x1b), snd_sonicvibes_in(sonic, 0x3b));
	dev_dbg(sonic->card->dev,
		"  0x1c: DMA C upper cnt = 0x%02x    0x3c: ---             = 0x%02x\n",
		snd_sonicvibes_in(sonic, 0x1c), snd_sonicvibes_in(sonic, 0x3c));
	dev_dbg(sonic->card->dev,
		"  0x1d: DMA C upper cnt = 0x%02x    0x3d: ---             = 0x%02x\n",
		snd_sonicvibes_in(sonic, 0x1d), snd_sonicvibes_in(sonic, 0x3d));
	dev_dbg(sonic->card->dev,
		"  0x1e: PCM rate low    = 0x%02x    0x3e: ---             = 0x%02x\n",
		snd_sonicvibes_in(sonic, 0x1e), snd_sonicvibes_in(sonic, 0x3e));
	dev_dbg(sonic->card->dev,
		"  0x1f: PCM rate high   = 0x%02x    0x3f: ---             = 0x%02x\n",
		snd_sonicvibes_in(sonic, 0x1f), snd_sonicvibes_in(sonic, 0x3f));
पूर्ण

#पूर्ण_अगर

अटल व्योम snd_sonicvibes_setfmt(काष्ठा sonicvibes * sonic,
                                  अचिन्हित अक्षर mask,
                                  अचिन्हित अक्षर value)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sonic->reg_lock, flags);
	outb(SV_MCE | SV_IREG_DMA_DATA_FMT, SV_REG(sonic, INDEX));
	अगर (mask) अणु
		sonic->क्रमmat = inb(SV_REG(sonic, DATA));
		udelay(10);
	पूर्ण
	sonic->क्रमmat = (sonic->क्रमmat & mask) | value;
	outb(sonic->क्रमmat, SV_REG(sonic, DATA));
	udelay(10);
	outb(0, SV_REG(sonic, INDEX));
	udelay(10);
	spin_unlock_irqrestore(&sonic->reg_lock, flags);
पूर्ण

अटल व्योम snd_sonicvibes_pll(अचिन्हित पूर्णांक rate,
			       अचिन्हित पूर्णांक *res_r,
			       अचिन्हित पूर्णांक *res_m,
			       अचिन्हित पूर्णांक *res_n)
अणु
	अचिन्हित पूर्णांक r, m = 0, n = 0;
	अचिन्हित पूर्णांक xm, xn, xr, xd, metric = ~0U;

	अगर (rate < 625000 / SV_ADCMULT)
		rate = 625000 / SV_ADCMULT;
	अगर (rate > 150000000 / SV_ADCMULT)
		rate = 150000000 / SV_ADCMULT;
	/* slight violation of specs, needed क्रम continuous sampling rates */
	क्रम (r = 0; rate < 75000000 / SV_ADCMULT; r += 0x20, rate <<= 1);
	क्रम (xn = 3; xn < 33; xn++)	/* 35 */
		क्रम (xm = 3; xm < 257; xm++) अणु
			xr = ((SV_REFFREQUENCY / SV_ADCMULT) * xm) / xn;
			अगर (xr >= rate)
				xd = xr - rate;
			अन्यथा
				xd = rate - xr;
			अगर (xd < metric) अणु
				metric = xd;
				m = xm - 2;
				n = xn - 2;
			पूर्ण
		पूर्ण
	*res_r = r;
	*res_m = m;
	*res_n = n;
#अगर 0
	dev_dbg(sonic->card->dev,
		"metric = %i, xm = %i, xn = %i\n", metric, xm, xn);
	dev_dbg(sonic->card->dev,
		"pll: m = 0x%x, r = 0x%x, n = 0x%x\n", reg, m, r, n);
#पूर्ण_अगर
पूर्ण

अटल व्योम snd_sonicvibes_setpll(काष्ठा sonicvibes * sonic,
                                  अचिन्हित अक्षर reg,
                                  अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक r, m, n;

	snd_sonicvibes_pll(rate, &r, &m, &n);
	अगर (sonic != शून्य) अणु
		spin_lock_irqsave(&sonic->reg_lock, flags);
		snd_sonicvibes_out1(sonic, reg, m);
		snd_sonicvibes_out1(sonic, reg + 1, r | n);
		spin_unlock_irqrestore(&sonic->reg_lock, flags);
	पूर्ण
पूर्ण

अटल व्योम snd_sonicvibes_set_adc_rate(काष्ठा sonicvibes * sonic, अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक भाग;
	अचिन्हित अक्षर घड़ी;

	भाग = 48000 / rate;
	अगर (भाग > 8)
		भाग = 8;
	अगर ((48000 / भाग) == rate) अणु	/* use the alternate घड़ी */
		घड़ी = 0x10;
	पूर्ण अन्यथा अणु			/* use the PLL source */
		घड़ी = 0x00;
		snd_sonicvibes_setpll(sonic, SV_IREG_ADC_PLL, rate);
	पूर्ण
	spin_lock_irqsave(&sonic->reg_lock, flags);
	snd_sonicvibes_out1(sonic, SV_IREG_ADC_ALT_RATE, (भाग - 1) << 4);
	snd_sonicvibes_out1(sonic, SV_IREG_ADC_CLOCK, घड़ी);
	spin_unlock_irqrestore(&sonic->reg_lock, flags);
पूर्ण

अटल पूर्णांक snd_sonicvibes_hw_स्थिरraपूर्णांक_dac_rate(काष्ठा snd_pcm_hw_params *params,
						 काष्ठा snd_pcm_hw_rule *rule)
अणु
	अचिन्हित पूर्णांक rate, भाग, r, m, n;

	अगर (hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_RATE)->min == 
	    hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_RATE)->max) अणु
		rate = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_RATE)->min;
		भाग = 48000 / rate;
		अगर (भाग > 8)
			भाग = 8;
		अगर ((48000 / भाग) == rate) अणु
			params->rate_num = rate;
			params->rate_den = 1;
		पूर्ण अन्यथा अणु
			snd_sonicvibes_pll(rate, &r, &m, &n);
			snd_BUG_ON(SV_REFFREQUENCY % 16);
			snd_BUG_ON(SV_ADCMULT % 512);
			params->rate_num = (SV_REFFREQUENCY/16) * (n+2) * r;
			params->rate_den = (SV_ADCMULT/512) * (m+2);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम snd_sonicvibes_set_dac_rate(काष्ठा sonicvibes * sonic, अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित पूर्णांक भाग;
	अचिन्हित दीर्घ flags;

	भाग = DIV_ROUND_CLOSEST(rate * 65536, SV_FULLRATE);
	अगर (भाग > 65535)
		भाग = 65535;
	spin_lock_irqsave(&sonic->reg_lock, flags);
	snd_sonicvibes_out1(sonic, SV_IREG_PCM_RATE_HIGH, भाग >> 8);
	snd_sonicvibes_out1(sonic, SV_IREG_PCM_RATE_LOW, भाग);
	spin_unlock_irqrestore(&sonic->reg_lock, flags);
पूर्ण

अटल पूर्णांक snd_sonicvibes_trigger(काष्ठा sonicvibes * sonic, पूर्णांक what, पूर्णांक cmd)
अणु
	पूर्णांक result = 0;

	spin_lock(&sonic->reg_lock);
	अगर (cmd == SNDRV_PCM_TRIGGER_START) अणु
		अगर (!(sonic->enable & what)) अणु
			sonic->enable |= what;
			snd_sonicvibes_out1(sonic, SV_IREG_PC_ENABLE, sonic->enable);
		पूर्ण
	पूर्ण अन्यथा अगर (cmd == SNDRV_PCM_TRIGGER_STOP) अणु
		अगर (sonic->enable & what) अणु
			sonic->enable &= ~what;
			snd_sonicvibes_out1(sonic, SV_IREG_PC_ENABLE, sonic->enable);
		पूर्ण
	पूर्ण अन्यथा अणु
		result = -EINVAL;
	पूर्ण
	spin_unlock(&sonic->reg_lock);
	वापस result;
पूर्ण

अटल irqवापस_t snd_sonicvibes_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sonicvibes *sonic = dev_id;
	अचिन्हित अक्षर status;

	status = inb(SV_REG(sonic, STATUS));
	अगर (!(status & (SV_DMAA_IRQ | SV_DMAC_IRQ | SV_MIDI_IRQ)))
		वापस IRQ_NONE;
	अगर (status == 0xff) अणु	/* failure */
		outb(sonic->irqmask = ~0, SV_REG(sonic, IRQMASK));
		dev_err(sonic->card->dev,
			"IRQ failure - interrupts disabled!!\n");
		वापस IRQ_HANDLED;
	पूर्ण
	अगर (sonic->pcm) अणु
		अगर (status & SV_DMAA_IRQ)
			snd_pcm_period_elapsed(sonic->playback_substream);
		अगर (status & SV_DMAC_IRQ)
			snd_pcm_period_elapsed(sonic->capture_substream);
	पूर्ण
	अगर (sonic->rmidi) अणु
		अगर (status & SV_MIDI_IRQ)
			snd_mpu401_uart_पूर्णांकerrupt(irq, sonic->rmidi->निजी_data);
	पूर्ण
	अगर (status & SV_UD_IRQ) अणु
		अचिन्हित अक्षर udreg;
		पूर्णांक vol, oleft, oright, mleft, mright;

		spin_lock(&sonic->reg_lock);
		udreg = snd_sonicvibes_in1(sonic, SV_IREG_UD_BUTTON);
		vol = udreg & 0x3f;
		अगर (!(udreg & 0x40))
			vol = -vol;
		oleft = mleft = snd_sonicvibes_in1(sonic, SV_IREG_LEFT_ANALOG);
		oright = mright = snd_sonicvibes_in1(sonic, SV_IREG_RIGHT_ANALOG);
		oleft &= 0x1f;
		oright &= 0x1f;
		oleft += vol;
		अगर (oleft < 0)
			oleft = 0;
		अगर (oleft > 0x1f)
			oleft = 0x1f;
		oright += vol;
		अगर (oright < 0)
			oright = 0;
		अगर (oright > 0x1f)
			oright = 0x1f;
		अगर (udreg & 0x80) अणु
			mleft ^= 0x80;
			mright ^= 0x80;
		पूर्ण
		oleft |= mleft & 0x80;
		oright |= mright & 0x80;
		snd_sonicvibes_out1(sonic, SV_IREG_LEFT_ANALOG, oleft);
		snd_sonicvibes_out1(sonic, SV_IREG_RIGHT_ANALOG, oright);
		spin_unlock(&sonic->reg_lock);
		snd_ctl_notअगरy(sonic->card, SNDRV_CTL_EVENT_MASK_VALUE, &sonic->master_mute->id);
		snd_ctl_notअगरy(sonic->card, SNDRV_CTL_EVENT_MASK_VALUE, &sonic->master_volume->id);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

/*
 *  PCM part
 */

अटल पूर्णांक snd_sonicvibes_playback_trigger(काष्ठा snd_pcm_substream *substream,
					   पूर्णांक cmd)
अणु
	काष्ठा sonicvibes *sonic = snd_pcm_substream_chip(substream);
	वापस snd_sonicvibes_trigger(sonic, 1, cmd);
पूर्ण

अटल पूर्णांक snd_sonicvibes_capture_trigger(काष्ठा snd_pcm_substream *substream,
					  पूर्णांक cmd)
अणु
	काष्ठा sonicvibes *sonic = snd_pcm_substream_chip(substream);
	वापस snd_sonicvibes_trigger(sonic, 2, cmd);
पूर्ण

अटल पूर्णांक snd_sonicvibes_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा sonicvibes *sonic = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित अक्षर fmt = 0;
	अचिन्हित पूर्णांक size = snd_pcm_lib_buffer_bytes(substream);
	अचिन्हित पूर्णांक count = snd_pcm_lib_period_bytes(substream);

	sonic->p_dma_size = size;
	count--;
	अगर (runसमय->channels > 1)
		fmt |= 1;
	अगर (snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 16)
		fmt |= 2;
	snd_sonicvibes_setfmt(sonic, ~3, fmt);
	snd_sonicvibes_set_dac_rate(sonic, runसमय->rate);
	spin_lock_irq(&sonic->reg_lock);
	snd_sonicvibes_setdmaa(sonic, runसमय->dma_addr, size);
	snd_sonicvibes_out1(sonic, SV_IREG_DMA_A_UPPER, count >> 8);
	snd_sonicvibes_out1(sonic, SV_IREG_DMA_A_LOWER, count);
	spin_unlock_irq(&sonic->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sonicvibes_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा sonicvibes *sonic = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित अक्षर fmt = 0;
	अचिन्हित पूर्णांक size = snd_pcm_lib_buffer_bytes(substream);
	अचिन्हित पूर्णांक count = snd_pcm_lib_period_bytes(substream);

	sonic->c_dma_size = size;
	count >>= 1;
	count--;
	अगर (runसमय->channels > 1)
		fmt |= 0x10;
	अगर (snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 16)
		fmt |= 0x20;
	snd_sonicvibes_setfmt(sonic, ~0x30, fmt);
	snd_sonicvibes_set_adc_rate(sonic, runसमय->rate);
	spin_lock_irq(&sonic->reg_lock);
	snd_sonicvibes_setdmac(sonic, runसमय->dma_addr, size);
	snd_sonicvibes_out1(sonic, SV_IREG_DMA_C_UPPER, count >> 8);
	snd_sonicvibes_out1(sonic, SV_IREG_DMA_C_LOWER, count);
	spin_unlock_irq(&sonic->reg_lock);
	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t snd_sonicvibes_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा sonicvibes *sonic = snd_pcm_substream_chip(substream);
	माप_प्रकार ptr;

	अगर (!(sonic->enable & 1))
		वापस 0;
	ptr = sonic->p_dma_size - snd_sonicvibes_getdmaa(sonic);
	वापस bytes_to_frames(substream->runसमय, ptr);
पूर्ण

अटल snd_pcm_uframes_t snd_sonicvibes_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा sonicvibes *sonic = snd_pcm_substream_chip(substream);
	माप_प्रकार ptr;
	अगर (!(sonic->enable & 2))
		वापस 0;
	ptr = sonic->c_dma_size - snd_sonicvibes_getdmac(sonic);
	वापस bytes_to_frames(substream->runसमय, ptr);
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware snd_sonicvibes_playback =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =		SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		4000,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	(128*1024),
	.period_bytes_min =	32,
	.period_bytes_max =	(128*1024),
	.periods_min =		1,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_sonicvibes_capture =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =		SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		4000,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	(128*1024),
	.period_bytes_min =	32,
	.period_bytes_max =	(128*1024),
	.periods_min =		1,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

अटल पूर्णांक snd_sonicvibes_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा sonicvibes *sonic = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	sonic->mode |= SV_MODE_PLAY;
	sonic->playback_substream = substream;
	runसमय->hw = snd_sonicvibes_playback;
	snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE, snd_sonicvibes_hw_स्थिरraपूर्णांक_dac_rate, शून्य, SNDRV_PCM_HW_PARAM_RATE, -1);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sonicvibes_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा sonicvibes *sonic = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	sonic->mode |= SV_MODE_CAPTURE;
	sonic->capture_substream = substream;
	runसमय->hw = snd_sonicvibes_capture;
	snd_pcm_hw_स्थिरraपूर्णांक_ratdens(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				      &snd_sonicvibes_hw_स्थिरraपूर्णांकs_adc_घड़ी);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sonicvibes_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा sonicvibes *sonic = snd_pcm_substream_chip(substream);

	sonic->playback_substream = शून्य;
	sonic->mode &= ~SV_MODE_PLAY;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sonicvibes_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा sonicvibes *sonic = snd_pcm_substream_chip(substream);

	sonic->capture_substream = शून्य;
	sonic->mode &= ~SV_MODE_CAPTURE;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_sonicvibes_playback_ops = अणु
	.खोलो =		snd_sonicvibes_playback_खोलो,
	.बंद =	snd_sonicvibes_playback_बंद,
	.prepare =	snd_sonicvibes_playback_prepare,
	.trigger =	snd_sonicvibes_playback_trigger,
	.poपूर्णांकer =	snd_sonicvibes_playback_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_sonicvibes_capture_ops = अणु
	.खोलो =		snd_sonicvibes_capture_खोलो,
	.बंद =	snd_sonicvibes_capture_बंद,
	.prepare =	snd_sonicvibes_capture_prepare,
	.trigger =	snd_sonicvibes_capture_trigger,
	.poपूर्णांकer =	snd_sonicvibes_capture_poपूर्णांकer,
पूर्ण;

अटल पूर्णांक snd_sonicvibes_pcm(काष्ठा sonicvibes *sonic, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	अगर ((err = snd_pcm_new(sonic->card, "s3_86c617", device, 1, 1, &pcm)) < 0)
		वापस err;
	अगर (snd_BUG_ON(!pcm))
		वापस -EINVAL;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_sonicvibes_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_sonicvibes_capture_ops);

	pcm->निजी_data = sonic;
	pcm->info_flags = 0;
	म_नकल(pcm->name, "S3 SonicVibes");
	sonic->pcm = pcm;

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
				       &sonic->pci->dev, 64*1024, 128*1024);

	वापस 0;
पूर्ण

/*
 *  Mixer part
 */

#घोषणा SONICVIBES_MUX(xname, xindex) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .info = snd_sonicvibes_info_mux, \
  .get = snd_sonicvibes_get_mux, .put = snd_sonicvibes_put_mux पूर्ण

अटल पूर्णांक snd_sonicvibes_info_mux(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[7] = अणु
		"CD", "PCM", "Aux1", "Line", "Aux0", "Mic", "Mix"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 2, 7, texts);
पूर्ण

अटल पूर्णांक snd_sonicvibes_get_mux(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा sonicvibes *sonic = snd_kcontrol_chip(kcontrol);
	
	spin_lock_irq(&sonic->reg_lock);
	ucontrol->value.क्रमागतerated.item[0] = ((snd_sonicvibes_in1(sonic, SV_IREG_LEFT_ADC) & SV_RECSRC_OUT) >> 5) - 1;
	ucontrol->value.क्रमागतerated.item[1] = ((snd_sonicvibes_in1(sonic, SV_IREG_RIGHT_ADC) & SV_RECSRC_OUT) >> 5) - 1;
	spin_unlock_irq(&sonic->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sonicvibes_put_mux(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा sonicvibes *sonic = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु left, right, oval1, oval2;
	पूर्णांक change;
	
	अगर (ucontrol->value.क्रमागतerated.item[0] >= 7 ||
	    ucontrol->value.क्रमागतerated.item[1] >= 7)
		वापस -EINVAL;
	left = (ucontrol->value.क्रमागतerated.item[0] + 1) << 5;
	right = (ucontrol->value.क्रमागतerated.item[1] + 1) << 5;
	spin_lock_irq(&sonic->reg_lock);
	oval1 = snd_sonicvibes_in1(sonic, SV_IREG_LEFT_ADC);
	oval2 = snd_sonicvibes_in1(sonic, SV_IREG_RIGHT_ADC);
	left = (oval1 & ~SV_RECSRC_OUT) | left;
	right = (oval2 & ~SV_RECSRC_OUT) | right;
	change = left != oval1 || right != oval2;
	snd_sonicvibes_out1(sonic, SV_IREG_LEFT_ADC, left);
	snd_sonicvibes_out1(sonic, SV_IREG_RIGHT_ADC, right);
	spin_unlock_irq(&sonic->reg_lock);
	वापस change;
पूर्ण

#घोषणा SONICVIBES_SINGLE(xname, xindex, reg, shअगरt, mask, invert) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .info = snd_sonicvibes_info_single, \
  .get = snd_sonicvibes_get_single, .put = snd_sonicvibes_put_single, \
  .निजी_value = reg | (shअगरt << 8) | (mask << 16) | (invert << 24) पूर्ण

अटल पूर्णांक snd_sonicvibes_info_single(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;

	uinfo->type = mask == 1 ? SNDRV_CTL_ELEM_TYPE_BOOLEAN : SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = mask;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sonicvibes_get_single(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा sonicvibes *sonic = snd_kcontrol_chip(kcontrol);
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 24) & 0xff;
	
	spin_lock_irq(&sonic->reg_lock);
	ucontrol->value.पूर्णांकeger.value[0] = (snd_sonicvibes_in1(sonic, reg)>> shअगरt) & mask;
	spin_unlock_irq(&sonic->reg_lock);
	अगर (invert)
		ucontrol->value.पूर्णांकeger.value[0] = mask - ucontrol->value.पूर्णांकeger.value[0];
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sonicvibes_put_single(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा sonicvibes *sonic = snd_kcontrol_chip(kcontrol);
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 24) & 0xff;
	पूर्णांक change;
	अचिन्हित लघु val, oval;
	
	val = (ucontrol->value.पूर्णांकeger.value[0] & mask);
	अगर (invert)
		val = mask - val;
	val <<= shअगरt;
	spin_lock_irq(&sonic->reg_lock);
	oval = snd_sonicvibes_in1(sonic, reg);
	val = (oval & ~(mask << shअगरt)) | val;
	change = val != oval;
	snd_sonicvibes_out1(sonic, reg, val);
	spin_unlock_irq(&sonic->reg_lock);
	वापस change;
पूर्ण

#घोषणा SONICVIBES_DOUBLE(xname, xindex, left_reg, right_reg, shअगरt_left, shअगरt_right, mask, invert) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .info = snd_sonicvibes_info_द्विगुन, \
  .get = snd_sonicvibes_get_द्विगुन, .put = snd_sonicvibes_put_द्विगुन, \
  .निजी_value = left_reg | (right_reg << 8) | (shअगरt_left << 16) | (shअगरt_right << 19) | (mask << 24) | (invert << 22) पूर्ण

अटल पूर्णांक snd_sonicvibes_info_द्विगुन(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक mask = (kcontrol->निजी_value >> 24) & 0xff;

	uinfo->type = mask == 1 ? SNDRV_CTL_ELEM_TYPE_BOOLEAN : SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = mask;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sonicvibes_get_द्विगुन(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा sonicvibes *sonic = snd_kcontrol_chip(kcontrol);
	पूर्णांक left_reg = kcontrol->निजी_value & 0xff;
	पूर्णांक right_reg = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक shअगरt_left = (kcontrol->निजी_value >> 16) & 0x07;
	पूर्णांक shअगरt_right = (kcontrol->निजी_value >> 19) & 0x07;
	पूर्णांक mask = (kcontrol->निजी_value >> 24) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 22) & 1;
	
	spin_lock_irq(&sonic->reg_lock);
	ucontrol->value.पूर्णांकeger.value[0] = (snd_sonicvibes_in1(sonic, left_reg) >> shअगरt_left) & mask;
	ucontrol->value.पूर्णांकeger.value[1] = (snd_sonicvibes_in1(sonic, right_reg) >> shअगरt_right) & mask;
	spin_unlock_irq(&sonic->reg_lock);
	अगर (invert) अणु
		ucontrol->value.पूर्णांकeger.value[0] = mask - ucontrol->value.पूर्णांकeger.value[0];
		ucontrol->value.पूर्णांकeger.value[1] = mask - ucontrol->value.पूर्णांकeger.value[1];
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sonicvibes_put_द्विगुन(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा sonicvibes *sonic = snd_kcontrol_chip(kcontrol);
	पूर्णांक left_reg = kcontrol->निजी_value & 0xff;
	पूर्णांक right_reg = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक shअगरt_left = (kcontrol->निजी_value >> 16) & 0x07;
	पूर्णांक shअगरt_right = (kcontrol->निजी_value >> 19) & 0x07;
	पूर्णांक mask = (kcontrol->निजी_value >> 24) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 22) & 1;
	पूर्णांक change;
	अचिन्हित लघु val1, val2, oval1, oval2;
	
	val1 = ucontrol->value.पूर्णांकeger.value[0] & mask;
	val2 = ucontrol->value.पूर्णांकeger.value[1] & mask;
	अगर (invert) अणु
		val1 = mask - val1;
		val2 = mask - val2;
	पूर्ण
	val1 <<= shअगरt_left;
	val2 <<= shअगरt_right;
	spin_lock_irq(&sonic->reg_lock);
	oval1 = snd_sonicvibes_in1(sonic, left_reg);
	oval2 = snd_sonicvibes_in1(sonic, right_reg);
	val1 = (oval1 & ~(mask << shअगरt_left)) | val1;
	val2 = (oval2 & ~(mask << shअगरt_right)) | val2;
	change = val1 != oval1 || val2 != oval2;
	snd_sonicvibes_out1(sonic, left_reg, val1);
	snd_sonicvibes_out1(sonic, right_reg, val2);
	spin_unlock_irq(&sonic->reg_lock);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_sonicvibes_controls[] = अणु
SONICVIBES_DOUBLE("Capture Volume", 0, SV_IREG_LEFT_ADC, SV_IREG_RIGHT_ADC, 0, 0, 15, 0),
SONICVIBES_DOUBLE("Aux Playback Switch", 0, SV_IREG_LEFT_AUX1, SV_IREG_RIGHT_AUX1, 7, 7, 1, 1),
SONICVIBES_DOUBLE("Aux Playback Volume", 0, SV_IREG_LEFT_AUX1, SV_IREG_RIGHT_AUX1, 0, 0, 31, 1),
SONICVIBES_DOUBLE("CD Playback Switch", 0, SV_IREG_LEFT_CD, SV_IREG_RIGHT_CD, 7, 7, 1, 1),
SONICVIBES_DOUBLE("CD Playback Volume", 0, SV_IREG_LEFT_CD, SV_IREG_RIGHT_CD, 0, 0, 31, 1),
SONICVIBES_DOUBLE("Line Playback Switch", 0, SV_IREG_LEFT_LINE, SV_IREG_RIGHT_LINE, 7, 7, 1, 1),
SONICVIBES_DOUBLE("Line Playback Volume", 0, SV_IREG_LEFT_LINE, SV_IREG_RIGHT_LINE, 0, 0, 31, 1),
SONICVIBES_SINGLE("Mic Playback Switch", 0, SV_IREG_MIC, 7, 1, 1),
SONICVIBES_SINGLE("Mic Playback Volume", 0, SV_IREG_MIC, 0, 15, 1),
SONICVIBES_SINGLE("Mic Boost", 0, SV_IREG_LEFT_ADC, 4, 1, 0),
SONICVIBES_DOUBLE("Synth Playback Switch", 0, SV_IREG_LEFT_SYNTH, SV_IREG_RIGHT_SYNTH, 7, 7, 1, 1),
SONICVIBES_DOUBLE("Synth Playback Volume", 0, SV_IREG_LEFT_SYNTH, SV_IREG_RIGHT_SYNTH, 0, 0, 31, 1),
SONICVIBES_DOUBLE("Aux Playback Switch", 1, SV_IREG_LEFT_AUX2, SV_IREG_RIGHT_AUX2, 7, 7, 1, 1),
SONICVIBES_DOUBLE("Aux Playback Volume", 1, SV_IREG_LEFT_AUX2, SV_IREG_RIGHT_AUX2, 0, 0, 31, 1),
SONICVIBES_DOUBLE("Master Playback Switch", 0, SV_IREG_LEFT_ANALOG, SV_IREG_RIGHT_ANALOG, 7, 7, 1, 1),
SONICVIBES_DOUBLE("Master Playback Volume", 0, SV_IREG_LEFT_ANALOG, SV_IREG_RIGHT_ANALOG, 0, 0, 31, 1),
SONICVIBES_DOUBLE("PCM Playback Switch", 0, SV_IREG_LEFT_PCM, SV_IREG_RIGHT_PCM, 7, 7, 1, 1),
SONICVIBES_DOUBLE("PCM Playback Volume", 0, SV_IREG_LEFT_PCM, SV_IREG_RIGHT_PCM, 0, 0, 63, 1),
SONICVIBES_SINGLE("Loopback Capture Switch", 0, SV_IREG_ADC_OUTPUT_CTRL, 0, 1, 0),
SONICVIBES_SINGLE("Loopback Capture Volume", 0, SV_IREG_ADC_OUTPUT_CTRL, 2, 63, 1),
SONICVIBES_MUX("Capture Source", 0)
पूर्ण;

अटल व्योम snd_sonicvibes_master_मुक्त(काष्ठा snd_kcontrol *kcontrol)
अणु
	काष्ठा sonicvibes *sonic = snd_kcontrol_chip(kcontrol);
	sonic->master_mute = शून्य;
	sonic->master_volume = शून्य;
पूर्ण

अटल पूर्णांक snd_sonicvibes_mixer(काष्ठा sonicvibes *sonic)
अणु
	काष्ठा snd_card *card;
	काष्ठा snd_kcontrol *kctl;
	अचिन्हित पूर्णांक idx;
	पूर्णांक err;

	अगर (snd_BUG_ON(!sonic || !sonic->card))
		वापस -EINVAL;
	card = sonic->card;
	म_नकल(card->mixername, "S3 SonicVibes");

	क्रम (idx = 0; idx < ARRAY_SIZE(snd_sonicvibes_controls); idx++) अणु
		अगर ((err = snd_ctl_add(card, kctl = snd_ctl_new1(&snd_sonicvibes_controls[idx], sonic))) < 0)
			वापस err;
		चयन (idx) अणु
		हाल 0:
		हाल 1: kctl->निजी_मुक्त = snd_sonicvibes_master_मुक्त; अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*

 */

अटल व्योम snd_sonicvibes_proc_पढ़ो(काष्ठा snd_info_entry *entry, 
				     काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा sonicvibes *sonic = entry->निजी_data;
	अचिन्हित अक्षर पंचांगp;

	पंचांगp = sonic->srs_space & 0x0f;
	snd_iम_लिखो(buffer, "SRS 3D           : %s\n",
		    sonic->srs_space & 0x80 ? "off" : "on");
	snd_iम_लिखो(buffer, "SRS Space        : %s\n",
		    पंचांगp == 0x00 ? "100%" :
		    पंचांगp == 0x01 ? "75%" :
		    पंचांगp == 0x02 ? "50%" :
		    पंचांगp == 0x03 ? "25%" : "0%");
	पंचांगp = sonic->srs_center & 0x0f;
	snd_iम_लिखो(buffer, "SRS Center       : %s\n",
		    पंचांगp == 0x00 ? "100%" :
		    पंचांगp == 0x01 ? "75%" :
		    पंचांगp == 0x02 ? "50%" :
		    पंचांगp == 0x03 ? "25%" : "0%");
	पंचांगp = sonic->wave_source & 0x03;
	snd_iम_लिखो(buffer, "WaveTable Source : %s\n",
		    पंचांगp == 0x00 ? "on-board ROM" :
		    पंचांगp == 0x01 ? "PCI bus" : "on-board ROM + PCI bus");
	पंचांगp = sonic->mpu_चयन;
	snd_iम_लिखो(buffer, "Onboard synth    : %s\n", पंचांगp & 0x01 ? "on" : "off");
	snd_iम_लिखो(buffer, "Ext. Rx to synth : %s\n", पंचांगp & 0x02 ? "on" : "off");
	snd_iम_लिखो(buffer, "MIDI to ext. Tx  : %s\n", पंचांगp & 0x04 ? "on" : "off");
पूर्ण

अटल व्योम snd_sonicvibes_proc_init(काष्ठा sonicvibes *sonic)
अणु
	snd_card_ro_proc_new(sonic->card, "sonicvibes", sonic,
			     snd_sonicvibes_proc_पढ़ो);
पूर्ण

/*

 */

#अगर_घोषित SUPPORT_JOYSTICK
अटल स्थिर काष्ठा snd_kcontrol_new snd_sonicvibes_game_control =
SONICVIBES_SINGLE("Joystick Speed", 0, SV_IREG_GAME_PORT, 1, 15, 0);

अटल पूर्णांक snd_sonicvibes_create_gameport(काष्ठा sonicvibes *sonic)
अणु
	काष्ठा gameport *gp;
	पूर्णांक err;

	sonic->gameport = gp = gameport_allocate_port();
	अगर (!gp) अणु
		dev_err(sonic->card->dev,
			"sonicvibes: cannot allocate memory for gameport\n");
		वापस -ENOMEM;
	पूर्ण

	gameport_set_name(gp, "SonicVibes Gameport");
	gameport_set_phys(gp, "pci%s/gameport0", pci_name(sonic->pci));
	gameport_set_dev_parent(gp, &sonic->pci->dev);
	gp->io = sonic->game_port;

	gameport_रेजिस्टर_port(gp);

	err = snd_ctl_add(sonic->card,
		snd_ctl_new1(&snd_sonicvibes_game_control, sonic));
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल व्योम snd_sonicvibes_मुक्त_gameport(काष्ठा sonicvibes *sonic)
अणु
	अगर (sonic->gameport) अणु
		gameport_unरेजिस्टर_port(sonic->gameport);
		sonic->gameport = शून्य;
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक snd_sonicvibes_create_gameport(काष्ठा sonicvibes *sonic) अणु वापस -ENOSYS; पूर्ण
अटल अंतरभूत व्योम snd_sonicvibes_मुक्त_gameport(काष्ठा sonicvibes *sonic) अणु पूर्ण
#पूर्ण_अगर

अटल पूर्णांक snd_sonicvibes_मुक्त(काष्ठा sonicvibes *sonic)
अणु
	snd_sonicvibes_मुक्त_gameport(sonic);
	pci_ग_लिखो_config_dword(sonic->pci, 0x40, sonic->dmaa_port);
	pci_ग_लिखो_config_dword(sonic->pci, 0x48, sonic->dmac_port);
	अगर (sonic->irq >= 0)
		मुक्त_irq(sonic->irq, sonic);
	release_and_मुक्त_resource(sonic->res_dmaa);
	release_and_मुक्त_resource(sonic->res_dmac);
	pci_release_regions(sonic->pci);
	pci_disable_device(sonic->pci);
	kमुक्त(sonic);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sonicvibes_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा sonicvibes *sonic = device->device_data;
	वापस snd_sonicvibes_मुक्त(sonic);
पूर्ण

अटल पूर्णांक snd_sonicvibes_create(काष्ठा snd_card *card,
				 काष्ठा pci_dev *pci,
				 पूर्णांक reverb,
				 पूर्णांक mge,
				 काष्ठा sonicvibes **rsonic)
अणु
	काष्ठा sonicvibes *sonic;
	अचिन्हित पूर्णांक dmaa, dmac;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =	snd_sonicvibes_dev_मुक्त,
	पूर्ण;

	*rsonic = शून्य;
	/* enable PCI device */
	अगर ((err = pci_enable_device(pci)) < 0)
		वापस err;
	/* check, अगर we can restrict PCI DMA transfers to 24 bits */
	अगर (dma_set_mask_and_coherent(&pci->dev, DMA_BIT_MASK(24))) अणु
		dev_err(card->dev,
			"architecture does not support 24bit PCI busmaster DMA\n");
		pci_disable_device(pci);
                वापस -ENXIO;
        पूर्ण

	sonic = kzalloc(माप(*sonic), GFP_KERNEL);
	अगर (sonic == शून्य) अणु
		pci_disable_device(pci);
		वापस -ENOMEM;
	पूर्ण
	spin_lock_init(&sonic->reg_lock);
	sonic->card = card;
	sonic->pci = pci;
	sonic->irq = -1;

	अगर ((err = pci_request_regions(pci, "S3 SonicVibes")) < 0) अणु
		kमुक्त(sonic);
		pci_disable_device(pci);
		वापस err;
	पूर्ण

	sonic->sb_port = pci_resource_start(pci, 0);
	sonic->enh_port = pci_resource_start(pci, 1);
	sonic->synth_port = pci_resource_start(pci, 2);
	sonic->midi_port = pci_resource_start(pci, 3);
	sonic->game_port = pci_resource_start(pci, 4);

	अगर (request_irq(pci->irq, snd_sonicvibes_पूर्णांकerrupt, IRQF_SHARED,
			KBUILD_MODNAME, sonic)) अणु
		dev_err(card->dev, "unable to grab IRQ %d\n", pci->irq);
		snd_sonicvibes_मुक्त(sonic);
		वापस -EBUSY;
	पूर्ण
	sonic->irq = pci->irq;
	card->sync_irq = sonic->irq;

	pci_पढ़ो_config_dword(pci, 0x40, &dmaa);
	pci_पढ़ो_config_dword(pci, 0x48, &dmac);
	dmaio &= ~0x0f;
	dmaa &= ~0x0f;
	dmac &= ~0x0f;
	अगर (!dmaa) अणु
		dmaa = dmaio;
		dmaio += 0x10;
		dev_info(card->dev,
			 "BIOS did not allocate DDMA channel A i/o, allocated at 0x%x\n",
			 dmaa);
	पूर्ण
	अगर (!dmac) अणु
		dmac = dmaio;
		dmaio += 0x10;
		dev_info(card->dev,
			 "BIOS did not allocate DDMA channel C i/o, allocated at 0x%x\n",
			 dmac);
	पूर्ण
	pci_ग_लिखो_config_dword(pci, 0x40, dmaa);
	pci_ग_लिखो_config_dword(pci, 0x48, dmac);

	अगर ((sonic->res_dmaa = request_region(dmaa, 0x10, "S3 SonicVibes DDMA-A")) == शून्य) अणु
		snd_sonicvibes_मुक्त(sonic);
		dev_err(card->dev,
			"unable to grab DDMA-A port at 0x%x-0x%x\n",
			dmaa, dmaa + 0x10 - 1);
		वापस -EBUSY;
	पूर्ण
	अगर ((sonic->res_dmac = request_region(dmac, 0x10, "S3 SonicVibes DDMA-C")) == शून्य) अणु
		snd_sonicvibes_मुक्त(sonic);
		dev_err(card->dev,
			"unable to grab DDMA-C port at 0x%x-0x%x\n",
			dmac, dmac + 0x10 - 1);
		वापस -EBUSY;
	पूर्ण

	pci_पढ़ो_config_dword(pci, 0x40, &sonic->dmaa_port);
	pci_पढ़ो_config_dword(pci, 0x48, &sonic->dmac_port);
	sonic->dmaa_port &= ~0x0f;
	sonic->dmac_port &= ~0x0f;
	pci_ग_लिखो_config_dword(pci, 0x40, sonic->dmaa_port | 9);	/* enable + enhanced */
	pci_ग_लिखो_config_dword(pci, 0x48, sonic->dmac_port | 9);	/* enable */
	/* ok.. initialize S3 SonicVibes chip */
	outb(SV_RESET, SV_REG(sonic, CONTROL));		/* reset chip */
	udelay(100);
	outb(0, SV_REG(sonic, CONTROL));	/* release reset */
	udelay(100);
	outb(SV_ENHANCED | SV_INTA | (reverb ? SV_REVERB : 0), SV_REG(sonic, CONTROL));
	inb(SV_REG(sonic, STATUS));	/* clear IRQs */
#अगर 1
	snd_sonicvibes_out(sonic, SV_IREG_DRIVE_CTRL, 0);	/* drive current 16mA */
#अन्यथा
	snd_sonicvibes_out(sonic, SV_IREG_DRIVE_CTRL, 0x40);	/* drive current 8mA */
#पूर्ण_अगर
	snd_sonicvibes_out(sonic, SV_IREG_PC_ENABLE, sonic->enable = 0);	/* disable playback & capture */
	outb(sonic->irqmask = ~(SV_DMAA_MASK | SV_DMAC_MASK | SV_UD_MASK), SV_REG(sonic, IRQMASK));
	inb(SV_REG(sonic, STATUS));	/* clear IRQs */
	snd_sonicvibes_out(sonic, SV_IREG_ADC_CLOCK, 0);	/* use PLL as घड़ी source */
	snd_sonicvibes_out(sonic, SV_IREG_ANALOG_POWER, 0);	/* घातer up analog parts */
	snd_sonicvibes_out(sonic, SV_IREG_DIGITAL_POWER, 0);	/* घातer up digital parts */
	snd_sonicvibes_setpll(sonic, SV_IREG_ADC_PLL, 8000);
	snd_sonicvibes_out(sonic, SV_IREG_SRS_SPACE, sonic->srs_space = 0x80);	/* SRS space off */
	snd_sonicvibes_out(sonic, SV_IREG_SRS_CENTER, sonic->srs_center = 0x00);/* SRS center off */
	snd_sonicvibes_out(sonic, SV_IREG_MPU401, sonic->mpu_चयन = 0x05);	/* MPU-401 चयन */
	snd_sonicvibes_out(sonic, SV_IREG_WAVE_SOURCE, sonic->wave_source = 0x00);	/* onboard ROM */
	snd_sonicvibes_out(sonic, SV_IREG_PCM_RATE_LOW, (8000 * 65536 / SV_FULLRATE) & 0xff);
	snd_sonicvibes_out(sonic, SV_IREG_PCM_RATE_HIGH, ((8000 * 65536 / SV_FULLRATE) >> 8) & 0xff);
	snd_sonicvibes_out(sonic, SV_IREG_LEFT_ADC, mge ? 0xd0 : 0xc0);
	snd_sonicvibes_out(sonic, SV_IREG_RIGHT_ADC, 0xc0);
	snd_sonicvibes_out(sonic, SV_IREG_LEFT_AUX1, 0x9f);
	snd_sonicvibes_out(sonic, SV_IREG_RIGHT_AUX1, 0x9f);
	snd_sonicvibes_out(sonic, SV_IREG_LEFT_CD, 0x9f);
	snd_sonicvibes_out(sonic, SV_IREG_RIGHT_CD, 0x9f);
	snd_sonicvibes_out(sonic, SV_IREG_LEFT_LINE, 0x9f);
	snd_sonicvibes_out(sonic, SV_IREG_RIGHT_LINE, 0x9f);
	snd_sonicvibes_out(sonic, SV_IREG_MIC, 0x8f);
	snd_sonicvibes_out(sonic, SV_IREG_LEFT_SYNTH, 0x9f);
	snd_sonicvibes_out(sonic, SV_IREG_RIGHT_SYNTH, 0x9f);
	snd_sonicvibes_out(sonic, SV_IREG_LEFT_AUX2, 0x9f);
	snd_sonicvibes_out(sonic, SV_IREG_RIGHT_AUX2, 0x9f);
	snd_sonicvibes_out(sonic, SV_IREG_LEFT_ANALOG, 0x9f);
	snd_sonicvibes_out(sonic, SV_IREG_RIGHT_ANALOG, 0x9f);
	snd_sonicvibes_out(sonic, SV_IREG_LEFT_PCM, 0xbf);
	snd_sonicvibes_out(sonic, SV_IREG_RIGHT_PCM, 0xbf);
	snd_sonicvibes_out(sonic, SV_IREG_ADC_OUTPUT_CTRL, 0xfc);
#अगर 0
	snd_sonicvibes_debug(sonic);
#पूर्ण_अगर
	sonic->revision = snd_sonicvibes_in(sonic, SV_IREG_REVISION);

	अगर ((err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, sonic, &ops)) < 0) अणु
		snd_sonicvibes_मुक्त(sonic);
		वापस err;
	पूर्ण

	snd_sonicvibes_proc_init(sonic);

	*rsonic = sonic;
	वापस 0;
पूर्ण

/*
 *  MIDI section
 */

अटल स्थिर काष्ठा snd_kcontrol_new snd_sonicvibes_midi_controls[] = अणु
SONICVIBES_SINGLE("SonicVibes Wave Source RAM", 0, SV_IREG_WAVE_SOURCE, 0, 1, 0),
SONICVIBES_SINGLE("SonicVibes Wave Source RAM+ROM", 0, SV_IREG_WAVE_SOURCE, 1, 1, 0),
SONICVIBES_SINGLE("SonicVibes Onboard Synth", 0, SV_IREG_MPU401, 0, 1, 0),
SONICVIBES_SINGLE("SonicVibes External Rx to Synth", 0, SV_IREG_MPU401, 1, 1, 0),
SONICVIBES_SINGLE("SonicVibes External Tx", 0, SV_IREG_MPU401, 2, 1, 0)
पूर्ण;

अटल पूर्णांक snd_sonicvibes_midi_input_खोलो(काष्ठा snd_mpu401 * mpu)
अणु
	काष्ठा sonicvibes *sonic = mpu->निजी_data;
	outb(sonic->irqmask &= ~SV_MIDI_MASK, SV_REG(sonic, IRQMASK));
	वापस 0;
पूर्ण

अटल व्योम snd_sonicvibes_midi_input_बंद(काष्ठा snd_mpu401 * mpu)
अणु
	काष्ठा sonicvibes *sonic = mpu->निजी_data;
	outb(sonic->irqmask |= SV_MIDI_MASK, SV_REG(sonic, IRQMASK));
पूर्ण

अटल पूर्णांक snd_sonicvibes_midi(काष्ठा sonicvibes *sonic,
			       काष्ठा snd_rawmidi *rmidi)
अणु
	काष्ठा snd_mpu401 * mpu = rmidi->निजी_data;
	काष्ठा snd_card *card = sonic->card;
	अचिन्हित पूर्णांक idx;
	पूर्णांक err;

	mpu->निजी_data = sonic;
	mpu->खोलो_input = snd_sonicvibes_midi_input_खोलो;
	mpu->बंद_input = snd_sonicvibes_midi_input_बंद;
	क्रम (idx = 0; idx < ARRAY_SIZE(snd_sonicvibes_midi_controls); idx++)
		अगर ((err = snd_ctl_add(card, snd_ctl_new1(&snd_sonicvibes_midi_controls[idx], sonic))) < 0)
			वापस err;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sonic_probe(काष्ठा pci_dev *pci,
			   स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_card *card;
	काष्ठा sonicvibes *sonic;
	काष्ठा snd_rawmidi *midi_uart;
	काष्ठा snd_opl3 *opl3;
	पूर्णांक idx, err;

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
	क्रम (idx = 0; idx < 5; idx++) अणु
		अगर (pci_resource_start(pci, idx) == 0 ||
		    !(pci_resource_flags(pci, idx) & IORESOURCE_IO)) अणु
			snd_card_मुक्त(card);
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	अगर ((err = snd_sonicvibes_create(card, pci,
					 reverb[dev] ? 1 : 0,
					 mge[dev] ? 1 : 0,
					 &sonic)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	म_नकल(card->driver, "SonicVibes");
	म_नकल(card->लघुname, "S3 SonicVibes");
	प्र_लिखो(card->दीर्घname, "%s rev %i at 0x%llx, irq %i",
		card->लघुname,
		sonic->revision,
		(अचिन्हित दीर्घ दीर्घ)pci_resource_start(pci, 1),
		sonic->irq);

	अगर ((err = snd_sonicvibes_pcm(sonic, 0)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	अगर ((err = snd_sonicvibes_mixer(sonic)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	अगर ((err = snd_mpu401_uart_new(card, 0, MPU401_HW_SONICVIBES,
				       sonic->midi_port,
				       MPU401_INFO_INTEGRATED |
				       MPU401_INFO_IRQ_HOOK,
				       -1, &midi_uart)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	snd_sonicvibes_midi(sonic, midi_uart);
	अगर ((err = snd_opl3_create(card, sonic->synth_port,
				   sonic->synth_port + 2,
				   OPL3_HW_OPL3_SV, 1, &opl3)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	अगर ((err = snd_opl3_hwdep_new(opl3, 0, 1, शून्य)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	err = snd_sonicvibes_create_gameport(sonic);
	अगर (err < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	अगर ((err = snd_card_रेजिस्टर(card)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	
	pci_set_drvdata(pci, card);
	dev++;
	वापस 0;
पूर्ण

अटल व्योम snd_sonic_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण

अटल काष्ठा pci_driver sonicvibes_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_sonic_ids,
	.probe = snd_sonic_probe,
	.हटाओ = snd_sonic_हटाओ,
पूर्ण;

module_pci_driver(sonicvibes_driver);
