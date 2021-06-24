<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम ESS Solo-1 (ES1938, ES1946, ES1969) soundcard
 *  Copyright (c) by Jaromir Koutek <miri@punknet.cz>,
 *                   Jaroslav Kysela <perex@perex.cz>,
 *                   Thomas Sailer <sailer@अगरe.ee.ethz.ch>,
 *                   Abramo Bagnara <abramo@alsa-project.org>,
 *                   Markus Gruber <gruber@eikon.tum.de>
 * 
 * Rewritten from sonicvibes.c source.
 *
 *  TODO:
 *    Reग_लिखो better spinlocks
 */

/*
  NOTES:
  - Capture data is written unaligned starting from dma_base + 1 so I need to
    disable mmap and to add a copy callback.
  - After several cycle of the following:
    जबतक : ; करो arecord -d1 -f cd -t raw | aplay -f cd ; करोne
    a "playback write error (DMA or IRQ trouble?)" may happen.
    This is due to playback पूर्णांकerrupts not generated.
    I suspect a timing issue.
  - Someबार the पूर्णांकerrupt handler is invoked wrongly during playback.
    This generates some harmless "Unexpected hw_poपूर्णांकer: wrong पूर्णांकerrupt
    acknowledge".
    I've seen that using small period sizes.
    Reproducible with:
    mpg123 test.mp3 &
    hdparm -t -T /dev/hda
*/


#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/gameport.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#समावेश <sound/opl3.h>
#समावेश <sound/mpu401.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

MODULE_AUTHOR("Jaromir Koutek <miri@punknet.cz>");
MODULE_DESCRIPTION("ESS Solo-1");
MODULE_LICENSE("GPL");

#अगर IS_REACHABLE(CONFIG_GAMEPORT)
#घोषणा SUPPORT_JOYSTICK 1
#पूर्ण_अगर

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;	/* Enable this card */

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for ESS Solo-1 soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for ESS Solo-1 soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable ESS Solo-1 soundcard.");

#घोषणा SLIO_REG(chip, x) ((chip)->io_port + ESSIO_REG_##x)

#घोषणा SLDM_REG(chip, x) ((chip)->ddma_port + ESSDM_REG_##x)

#घोषणा SLSB_REG(chip, x) ((chip)->sb_port + ESSSB_REG_##x)

#घोषणा SL_PCI_LEGACYCONTROL		0x40
#घोषणा SL_PCI_CONFIG			0x50
#घोषणा SL_PCI_DDMACONTROL		0x60

#घोषणा ESSIO_REG_AUDIO2DMAADDR		0
#घोषणा ESSIO_REG_AUDIO2DMACOUNT	4
#घोषणा ESSIO_REG_AUDIO2MODE		6
#घोषणा ESSIO_REG_IRQCONTROL		7

#घोषणा ESSDM_REG_DMAADDR		0x00
#घोषणा ESSDM_REG_DMACOUNT		0x04
#घोषणा ESSDM_REG_DMACOMMAND		0x08
#घोषणा ESSDM_REG_DMASTATUS		0x08
#घोषणा ESSDM_REG_DMAMODE		0x0b
#घोषणा ESSDM_REG_DMACLEAR		0x0d
#घोषणा ESSDM_REG_DMAMASK		0x0f

#घोषणा ESSSB_REG_FMLOWADDR		0x00
#घोषणा ESSSB_REG_FMHIGHADDR		0x02
#घोषणा ESSSB_REG_MIXERADDR		0x04
#घोषणा ESSSB_REG_MIXERDATA		0x05

#घोषणा ESSSB_IREG_AUDIO1		0x14
#घोषणा ESSSB_IREG_MICMIX		0x1a
#घोषणा ESSSB_IREG_RECSRC		0x1c
#घोषणा ESSSB_IREG_MASTER		0x32
#घोषणा ESSSB_IREG_FM			0x36
#घोषणा ESSSB_IREG_AUXACD		0x38
#घोषणा ESSSB_IREG_AUXB			0x3a
#घोषणा ESSSB_IREG_PCSPEAKER		0x3c
#घोषणा ESSSB_IREG_LINE			0x3e
#घोषणा ESSSB_IREG_SPATCONTROL		0x50
#घोषणा ESSSB_IREG_SPATLEVEL		0x52
#घोषणा ESSSB_IREG_MASTER_LEFT		0x60
#घोषणा ESSSB_IREG_MASTER_RIGHT		0x62
#घोषणा ESSSB_IREG_MPU401CONTROL	0x64
#घोषणा ESSSB_IREG_MICMIXRECORD		0x68
#घोषणा ESSSB_IREG_AUDIO2RECORD		0x69
#घोषणा ESSSB_IREG_AUXACDRECORD		0x6a
#घोषणा ESSSB_IREG_FMRECORD		0x6b
#घोषणा ESSSB_IREG_AUXBRECORD		0x6c
#घोषणा ESSSB_IREG_MONO			0x6d
#घोषणा ESSSB_IREG_LINERECORD		0x6e
#घोषणा ESSSB_IREG_MONORECORD		0x6f
#घोषणा ESSSB_IREG_AUDIO2SAMPLE		0x70
#घोषणा ESSSB_IREG_AUDIO2MODE		0x71
#घोषणा ESSSB_IREG_AUDIO2FILTER		0x72
#घोषणा ESSSB_IREG_AUDIO2TCOUNTL	0x74
#घोषणा ESSSB_IREG_AUDIO2TCOUNTH	0x76
#घोषणा ESSSB_IREG_AUDIO2CONTROL1	0x78
#घोषणा ESSSB_IREG_AUDIO2CONTROL2	0x7a
#घोषणा ESSSB_IREG_AUDIO2		0x7c

#घोषणा ESSSB_REG_RESET			0x06

#घोषणा ESSSB_REG_READDATA		0x0a
#घोषणा ESSSB_REG_WRITEDATA		0x0c
#घोषणा ESSSB_REG_READSTATUS		0x0c

#घोषणा ESSSB_REG_STATUS		0x0e

#घोषणा ESS_CMD_EXTSAMPLERATE		0xa1
#घोषणा ESS_CMD_FILTERDIV		0xa2
#घोषणा ESS_CMD_DMACNTRELOADL		0xa4
#घोषणा ESS_CMD_DMACNTRELOADH		0xa5
#घोषणा ESS_CMD_ANALOGCONTROL		0xa8
#घोषणा ESS_CMD_IRQCONTROL		0xb1
#घोषणा ESS_CMD_DRQCONTROL		0xb2
#घोषणा ESS_CMD_RECLEVEL		0xb4
#घोषणा ESS_CMD_SETFORMAT		0xb6
#घोषणा ESS_CMD_SETFORMAT2		0xb7
#घोषणा ESS_CMD_DMACONTROL		0xb8
#घोषणा ESS_CMD_DMATYPE			0xb9
#घोषणा ESS_CMD_OFFSETLEFT		0xba	
#घोषणा ESS_CMD_OFFSETRIGHT		0xbb
#घोषणा ESS_CMD_READREG			0xc0
#घोषणा ESS_CMD_ENABLEEXT		0xc6
#घोषणा ESS_CMD_PAUSEDMA		0xd0
#घोषणा ESS_CMD_ENABLEAUDIO1		0xd1
#घोषणा ESS_CMD_STOPAUDIO1		0xd3
#घोषणा ESS_CMD_AUDIO1STATUS		0xd8
#घोषणा ESS_CMD_CONTDMA			0xd4
#घोषणा ESS_CMD_TESTIRQ			0xf2

#घोषणा ESS_RECSRC_MIC		0
#घोषणा ESS_RECSRC_AUXACD	2
#घोषणा ESS_RECSRC_AUXB		5
#घोषणा ESS_RECSRC_LINE		6
#घोषणा ESS_RECSRC_NONE		7

#घोषणा DAC1 0x01
#घोषणा ADC1 0x02
#घोषणा DAC2 0x04

/*

 */

#घोषणा SAVED_REG_SIZE	32 /* max. number of रेजिस्टरs to save */

काष्ठा es1938 अणु
	पूर्णांक irq;

	अचिन्हित दीर्घ io_port;
	अचिन्हित दीर्घ sb_port;
	अचिन्हित दीर्घ vc_port;
	अचिन्हित दीर्घ mpu_port;
	अचिन्हित दीर्घ game_port;
	अचिन्हित दीर्घ ddma_port;

	अचिन्हित अक्षर irqmask;
	अचिन्हित अक्षर revision;

	काष्ठा snd_kcontrol *hw_volume;
	काष्ठा snd_kcontrol *hw_चयन;
	काष्ठा snd_kcontrol *master_volume;
	काष्ठा snd_kcontrol *master_चयन;

	काष्ठा pci_dev *pci;
	काष्ठा snd_card *card;
	काष्ठा snd_pcm *pcm;
	काष्ठा snd_pcm_substream *capture_substream;
	काष्ठा snd_pcm_substream *playback1_substream;
	काष्ठा snd_pcm_substream *playback2_substream;
	काष्ठा snd_rawmidi *rmidi;

	अचिन्हित पूर्णांक dma1_size;
	अचिन्हित पूर्णांक dma2_size;
	अचिन्हित पूर्णांक dma1_start;
	अचिन्हित पूर्णांक dma2_start;
	अचिन्हित पूर्णांक dma1_shअगरt;
	अचिन्हित पूर्णांक dma2_shअगरt;
	अचिन्हित पूर्णांक last_capture_dmaaddr;
	अचिन्हित पूर्णांक active;

	spinlock_t reg_lock;
	spinlock_t mixer_lock;
        काष्ठा snd_info_entry *proc_entry;

#अगर_घोषित SUPPORT_JOYSTICK
	काष्ठा gameport *gameport;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PM_SLEEP
	अचिन्हित अक्षर saved_regs[SAVED_REG_SIZE];
#पूर्ण_अगर
पूर्ण;

अटल irqवापस_t snd_es1938_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);

अटल स्थिर काष्ठा pci_device_id snd_es1938_ids[] = अणु
	अणु PCI_VDEVICE(ESS, 0x1969), 0, पूर्ण,   /* Solo-1 */
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, snd_es1938_ids);

#घोषणा RESET_LOOP_TIMEOUT	0x10000
#घोषणा WRITE_LOOP_TIMEOUT	0x10000
#घोषणा GET_LOOP_TIMEOUT	0x01000

/* -----------------------------------------------------------------
 * Write to a mixer रेजिस्टर
 * -----------------------------------------------------------------*/
अटल व्योम snd_es1938_mixer_ग_लिखो(काष्ठा es1938 *chip, अचिन्हित अक्षर reg, अचिन्हित अक्षर val)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&chip->mixer_lock, flags);
	outb(reg, SLSB_REG(chip, MIXERADDR));
	outb(val, SLSB_REG(chip, MIXERDATA));
	spin_unlock_irqrestore(&chip->mixer_lock, flags);
	dev_dbg(chip->card->dev, "Mixer reg %02x set to %02x\n", reg, val);
पूर्ण

/* -----------------------------------------------------------------
 * Read from a mixer रेजिस्टर
 * -----------------------------------------------------------------*/
अटल पूर्णांक snd_es1938_mixer_पढ़ो(काष्ठा es1938 *chip, अचिन्हित अक्षर reg)
अणु
	पूर्णांक data;
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&chip->mixer_lock, flags);
	outb(reg, SLSB_REG(chip, MIXERADDR));
	data = inb(SLSB_REG(chip, MIXERDATA));
	spin_unlock_irqrestore(&chip->mixer_lock, flags);
	dev_dbg(chip->card->dev, "Mixer reg %02x now is %02x\n", reg, data);
	वापस data;
पूर्ण

/* -----------------------------------------------------------------
 * Write to some bits of a mixer रेजिस्टर (वापस old value)
 * -----------------------------------------------------------------*/
अटल पूर्णांक snd_es1938_mixer_bits(काष्ठा es1938 *chip, अचिन्हित अक्षर reg,
				 अचिन्हित अक्षर mask, अचिन्हित अक्षर val)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर old, new, oval;
	spin_lock_irqsave(&chip->mixer_lock, flags);
	outb(reg, SLSB_REG(chip, MIXERADDR));
	old = inb(SLSB_REG(chip, MIXERDATA));
	oval = old & mask;
	अगर (val != oval) अणु
		new = (old & ~mask) | (val & mask);
		outb(new, SLSB_REG(chip, MIXERDATA));
		dev_dbg(chip->card->dev,
			"Mixer reg %02x was %02x, set to %02x\n",
			   reg, old, new);
	पूर्ण
	spin_unlock_irqrestore(&chip->mixer_lock, flags);
	वापस oval;
पूर्ण

/* -----------------------------------------------------------------
 * Write command to Controller Registers
 * -----------------------------------------------------------------*/
अटल व्योम snd_es1938_ग_लिखो_cmd(काष्ठा es1938 *chip, अचिन्हित अक्षर cmd)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर v;
	क्रम (i = 0; i < WRITE_LOOP_TIMEOUT; i++) अणु
		अगर (!(v = inb(SLSB_REG(chip, READSTATUS)) & 0x80)) अणु
			outb(cmd, SLSB_REG(chip, WRITEDATA));
			वापस;
		पूर्ण
	पूर्ण
	dev_err(chip->card->dev,
		"snd_es1938_write_cmd timeout (0x02%x/0x02%x)\n", cmd, v);
पूर्ण

/* -----------------------------------------------------------------
 * Read the Read Data Buffer
 * -----------------------------------------------------------------*/
अटल पूर्णांक snd_es1938_get_byte(काष्ठा es1938 *chip)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर v;
	क्रम (i = GET_LOOP_TIMEOUT; i; i--)
		अगर ((v = inb(SLSB_REG(chip, STATUS))) & 0x80)
			वापस inb(SLSB_REG(chip, READDATA));
	dev_err(chip->card->dev, "get_byte timeout: status 0x02%x\n", v);
	वापस -ENODEV;
पूर्ण

/* -----------------------------------------------------------------
 * Write value cmd रेजिस्टर
 * -----------------------------------------------------------------*/
अटल व्योम snd_es1938_ग_लिखो(काष्ठा es1938 *chip, अचिन्हित अक्षर reg, अचिन्हित अक्षर val)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&chip->reg_lock, flags);
	snd_es1938_ग_लिखो_cmd(chip, reg);
	snd_es1938_ग_लिखो_cmd(chip, val);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	dev_dbg(chip->card->dev, "Reg %02x set to %02x\n", reg, val);
पूर्ण

/* -----------------------------------------------------------------
 * Read data from cmd रेजिस्टर and वापस it
 * -----------------------------------------------------------------*/
अटल अचिन्हित अक्षर snd_es1938_पढ़ो(काष्ठा es1938 *chip, अचिन्हित अक्षर reg)
अणु
	अचिन्हित अक्षर val;
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&chip->reg_lock, flags);
	snd_es1938_ग_लिखो_cmd(chip, ESS_CMD_READREG);
	snd_es1938_ग_लिखो_cmd(chip, reg);
	val = snd_es1938_get_byte(chip);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	dev_dbg(chip->card->dev, "Reg %02x now is %02x\n", reg, val);
	वापस val;
पूर्ण

/* -----------------------------------------------------------------
 * Write data to cmd रेजिस्टर and वापस old value
 * -----------------------------------------------------------------*/
अटल पूर्णांक snd_es1938_bits(काष्ठा es1938 *chip, अचिन्हित अक्षर reg, अचिन्हित अक्षर mask,
			   अचिन्हित अक्षर val)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर old, new, oval;
	spin_lock_irqsave(&chip->reg_lock, flags);
	snd_es1938_ग_लिखो_cmd(chip, ESS_CMD_READREG);
	snd_es1938_ग_लिखो_cmd(chip, reg);
	old = snd_es1938_get_byte(chip);
	oval = old & mask;
	अगर (val != oval) अणु
		snd_es1938_ग_लिखो_cmd(chip, reg);
		new = (old & ~mask) | (val & mask);
		snd_es1938_ग_लिखो_cmd(chip, new);
		dev_dbg(chip->card->dev, "Reg %02x was %02x, set to %02x\n",
			   reg, old, new);
	पूर्ण
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस oval;
पूर्ण

/* --------------------------------------------------------------------
 * Reset the chip
 * --------------------------------------------------------------------*/
अटल व्योम snd_es1938_reset(काष्ठा es1938 *chip)
अणु
	पूर्णांक i;

	outb(3, SLSB_REG(chip, RESET));
	inb(SLSB_REG(chip, RESET));
	outb(0, SLSB_REG(chip, RESET));
	क्रम (i = 0; i < RESET_LOOP_TIMEOUT; i++) अणु
		अगर (inb(SLSB_REG(chip, STATUS)) & 0x80) अणु
			अगर (inb(SLSB_REG(chip, READDATA)) == 0xaa)
				जाओ __next;
		पूर्ण
	पूर्ण
	dev_err(chip->card->dev, "ESS Solo-1 reset failed\n");

     __next:
	snd_es1938_ग_लिखो_cmd(chip, ESS_CMD_ENABLEEXT);

	/* Demand transfer DMA: 4 bytes per DMA request */
	snd_es1938_ग_लिखो(chip, ESS_CMD_DMATYPE, 2);

	/* Change behaviour of रेजिस्टर A1
	   4x oversampling
	   2nd channel DAC asynchronous */                                                      
	snd_es1938_mixer_ग_लिखो(chip, ESSSB_IREG_AUDIO2MODE, 0x32);
	/* enable/select DMA channel and IRQ channel */
	snd_es1938_bits(chip, ESS_CMD_IRQCONTROL, 0xf0, 0x50);
	snd_es1938_bits(chip, ESS_CMD_DRQCONTROL, 0xf0, 0x50);
	snd_es1938_ग_लिखो_cmd(chip, ESS_CMD_ENABLEAUDIO1);
	/* Set spatializer parameters to recommended values */
	snd_es1938_mixer_ग_लिखो(chip, 0x54, 0x8f);
	snd_es1938_mixer_ग_लिखो(chip, 0x56, 0x95);
	snd_es1938_mixer_ग_लिखो(chip, 0x58, 0x94);
	snd_es1938_mixer_ग_लिखो(chip, 0x5a, 0x80);
पूर्ण

/* --------------------------------------------------------------------
 * Reset the FIFOs
 * --------------------------------------------------------------------*/
अटल व्योम snd_es1938_reset_fअगरo(काष्ठा es1938 *chip)
अणु
	outb(2, SLSB_REG(chip, RESET));
	outb(0, SLSB_REG(chip, RESET));
पूर्ण

अटल स्थिर काष्ठा snd_ratnum घड़ीs[2] = अणु
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

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_ratnums hw_स्थिरraपूर्णांकs_घड़ीs = अणु
	.nrats = 2,
	.rats = घड़ीs,
पूर्ण;


अटल व्योम snd_es1938_rate_set(काष्ठा es1938 *chip, 
				काष्ठा snd_pcm_substream *substream,
				पूर्णांक mode)
अणु
	अचिन्हित पूर्णांक bits, भाग0;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अगर (runसमय->rate_num == घड़ीs[0].num)
		bits = 128 - runसमय->rate_den;
	अन्यथा
		bits = 256 - runसमय->rate_den;

	/* set filter रेजिस्टर */
	भाग0 = 256 - 7160000*20/(8*82*runसमय->rate);
		
	अगर (mode == DAC2) अणु
		snd_es1938_mixer_ग_लिखो(chip, 0x70, bits);
		snd_es1938_mixer_ग_लिखो(chip, 0x72, भाग0);
	पूर्ण अन्यथा अणु
		snd_es1938_ग_लिखो(chip, 0xA1, bits);
		snd_es1938_ग_लिखो(chip, 0xA2, भाग0);
	पूर्ण
पूर्ण

/* --------------------------------------------------------------------
 * Configure Solo1 builtin DMA Controller
 * --------------------------------------------------------------------*/

अटल व्योम snd_es1938_playback1_setdma(काष्ठा es1938 *chip)
अणु
	outb(0x00, SLIO_REG(chip, AUDIO2MODE));
	outl(chip->dma2_start, SLIO_REG(chip, AUDIO2DMAADDR));
	outw(0, SLIO_REG(chip, AUDIO2DMACOUNT));
	outw(chip->dma2_size, SLIO_REG(chip, AUDIO2DMACOUNT));
पूर्ण

अटल व्योम snd_es1938_playback2_setdma(काष्ठा es1938 *chip)
अणु
	/* Enable DMA controller */
	outb(0xc4, SLDM_REG(chip, DMACOMMAND));
	/* 1. Master reset */
	outb(0, SLDM_REG(chip, DMACLEAR));
	/* 2. Mask DMA */
	outb(1, SLDM_REG(chip, DMAMASK));
	outb(0x18, SLDM_REG(chip, DMAMODE));
	outl(chip->dma1_start, SLDM_REG(chip, DMAADDR));
	outw(chip->dma1_size - 1, SLDM_REG(chip, DMACOUNT));
	/* 3. Unmask DMA */
	outb(0, SLDM_REG(chip, DMAMASK));
पूर्ण

अटल व्योम snd_es1938_capture_setdma(काष्ठा es1938 *chip)
अणु
	/* Enable DMA controller */
	outb(0xc4, SLDM_REG(chip, DMACOMMAND));
	/* 1. Master reset */
	outb(0, SLDM_REG(chip, DMACLEAR));
	/* 2. Mask DMA */
	outb(1, SLDM_REG(chip, DMAMASK));
	outb(0x14, SLDM_REG(chip, DMAMODE));
	outl(chip->dma1_start, SLDM_REG(chip, DMAADDR));
	chip->last_capture_dmaaddr = chip->dma1_start;
	outw(chip->dma1_size - 1, SLDM_REG(chip, DMACOUNT));
	/* 3. Unmask DMA */
	outb(0, SLDM_REG(chip, DMAMASK));
पूर्ण

/* ----------------------------------------------------------------------
 *
 *                           *** PCM part ***
 */

अटल पूर्णांक snd_es1938_capture_trigger(काष्ठा snd_pcm_substream *substream,
				      पूर्णांक cmd)
अणु
	काष्ठा es1938 *chip = snd_pcm_substream_chip(substream);
	पूर्णांक val;
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		val = 0x0f;
		chip->active |= ADC1;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		val = 0x00;
		chip->active &= ~ADC1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	snd_es1938_ग_लिखो(chip, ESS_CMD_DMACONTROL, val);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1938_playback1_trigger(काष्ठा snd_pcm_substream *substream,
					पूर्णांक cmd)
अणु
	काष्ठा es1938 *chip = snd_pcm_substream_chip(substream);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		/* According to the करोcumentation this should be:
		   0x13 but that value may अक्रमomly swap stereo channels */
                snd_es1938_mixer_ग_लिखो(chip, ESSSB_IREG_AUDIO2CONTROL1, 0x92);
                udelay(10);
		snd_es1938_mixer_ग_लिखो(chip, ESSSB_IREG_AUDIO2CONTROL1, 0x93);
                /* This two stage init gives the FIFO -> DAC connection समय to
                 * settle beक्रमe first data from DMA flows in.  This should ensure
                 * no swapping of stereo channels.  Report a bug अगर otherwise :-) */
		outb(0x0a, SLIO_REG(chip, AUDIO2MODE));
		chip->active |= DAC2;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		outb(0, SLIO_REG(chip, AUDIO2MODE));
		snd_es1938_mixer_ग_लिखो(chip, ESSSB_IREG_AUDIO2CONTROL1, 0);
		chip->active &= ~DAC2;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1938_playback2_trigger(काष्ठा snd_pcm_substream *substream,
					पूर्णांक cmd)
अणु
	काष्ठा es1938 *chip = snd_pcm_substream_chip(substream);
	पूर्णांक val;
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		val = 5;
		chip->active |= DAC1;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		val = 0;
		chip->active &= ~DAC1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	snd_es1938_ग_लिखो(chip, ESS_CMD_DMACONTROL, val);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1938_playback_trigger(काष्ठा snd_pcm_substream *substream,
				       पूर्णांक cmd)
अणु
	चयन (substream->number) अणु
	हाल 0:
		वापस snd_es1938_playback1_trigger(substream, cmd);
	हाल 1:
		वापस snd_es1938_playback2_trigger(substream, cmd);
	पूर्ण
	snd_BUG();
	वापस -EINVAL;
पूर्ण

/* --------------------------------------------------------------------
 * First channel क्रम Extended Mode Audio 1 ADC Operation
 * --------------------------------------------------------------------*/
अटल पूर्णांक snd_es1938_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा es1938 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक u, is8, mono;
	अचिन्हित पूर्णांक size = snd_pcm_lib_buffer_bytes(substream);
	अचिन्हित पूर्णांक count = snd_pcm_lib_period_bytes(substream);

	chip->dma1_size = size;
	chip->dma1_start = runसमय->dma_addr;

	mono = (runसमय->channels > 1) ? 0 : 1;
	is8 = snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 16 ? 0 : 1;
	u = snd_pcm_क्रमmat_अचिन्हित(runसमय->क्रमmat);

	chip->dma1_shअगरt = 2 - mono - is8;

	snd_es1938_reset_fअगरo(chip);
	
	/* program type */
	snd_es1938_bits(chip, ESS_CMD_ANALOGCONTROL, 0x03, (mono ? 2 : 1));

	/* set घड़ी and counters */
        snd_es1938_rate_set(chip, substream, ADC1);

	count = 0x10000 - count;
	snd_es1938_ग_लिखो(chip, ESS_CMD_DMACNTRELOADL, count & 0xff);
	snd_es1938_ग_लिखो(chip, ESS_CMD_DMACNTRELOADH, count >> 8);

	/* initialize and configure ADC */
	snd_es1938_ग_लिखो(chip, ESS_CMD_SETFORMAT2, u ? 0x51 : 0x71);
	snd_es1938_ग_लिखो(chip, ESS_CMD_SETFORMAT2, 0x90 | 
		       (u ? 0x00 : 0x20) | 
		       (is8 ? 0x00 : 0x04) | 
		       (mono ? 0x40 : 0x08));

	//	snd_es1938_reset_fअगरo(chip);	

	/* 11. configure प्रणाली पूर्णांकerrupt controller and DMA controller */
	snd_es1938_capture_setdma(chip);

	वापस 0;
पूर्ण


/* ------------------------------------------------------------------------------
 * Second Audio channel DAC Operation
 * ------------------------------------------------------------------------------*/
अटल पूर्णांक snd_es1938_playback1_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा es1938 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक u, is8, mono;
	अचिन्हित पूर्णांक size = snd_pcm_lib_buffer_bytes(substream);
	अचिन्हित पूर्णांक count = snd_pcm_lib_period_bytes(substream);

	chip->dma2_size = size;
	chip->dma2_start = runसमय->dma_addr;

	mono = (runसमय->channels > 1) ? 0 : 1;
	is8 = snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 16 ? 0 : 1;
	u = snd_pcm_क्रमmat_अचिन्हित(runसमय->क्रमmat);

	chip->dma2_shअगरt = 2 - mono - is8;

        snd_es1938_reset_fअगरo(chip);

	/* set घड़ी and counters */
        snd_es1938_rate_set(chip, substream, DAC2);

	count >>= 1;
	count = 0x10000 - count;
	snd_es1938_mixer_ग_लिखो(chip, ESSSB_IREG_AUDIO2TCOUNTL, count & 0xff);
	snd_es1938_mixer_ग_लिखो(chip, ESSSB_IREG_AUDIO2TCOUNTH, count >> 8);

	/* initialize and configure Audio 2 DAC */
	snd_es1938_mixer_ग_लिखो(chip, ESSSB_IREG_AUDIO2CONTROL2, 0x40 | (u ? 0 : 4) |
			       (mono ? 0 : 2) | (is8 ? 0 : 1));

	/* program DMA */
	snd_es1938_playback1_setdma(chip);
	
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1938_playback2_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा es1938 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक u, is8, mono;
	अचिन्हित पूर्णांक size = snd_pcm_lib_buffer_bytes(substream);
	अचिन्हित पूर्णांक count = snd_pcm_lib_period_bytes(substream);

	chip->dma1_size = size;
	chip->dma1_start = runसमय->dma_addr;

	mono = (runसमय->channels > 1) ? 0 : 1;
	is8 = snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 16 ? 0 : 1;
	u = snd_pcm_क्रमmat_अचिन्हित(runसमय->क्रमmat);

	chip->dma1_shअगरt = 2 - mono - is8;

	count = 0x10000 - count;
 
	/* reset */
	snd_es1938_reset_fअगरo(chip);
	
	snd_es1938_bits(chip, ESS_CMD_ANALOGCONTROL, 0x03, (mono ? 2 : 1));

	/* set घड़ी and counters */
        snd_es1938_rate_set(chip, substream, DAC1);
	snd_es1938_ग_लिखो(chip, ESS_CMD_DMACNTRELOADL, count & 0xff);
	snd_es1938_ग_लिखो(chip, ESS_CMD_DMACNTRELOADH, count >> 8);

	/* initialized and configure DAC */
        snd_es1938_ग_लिखो(chip, ESS_CMD_SETFORMAT, u ? 0x80 : 0x00);
        snd_es1938_ग_लिखो(chip, ESS_CMD_SETFORMAT, u ? 0x51 : 0x71);
        snd_es1938_ग_लिखो(chip, ESS_CMD_SETFORMAT2, 
			 0x90 | (mono ? 0x40 : 0x08) |
			 (is8 ? 0x00 : 0x04) | (u ? 0x00 : 0x20));

	/* program DMA */
	snd_es1938_playback2_setdma(chip);
	
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1938_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	चयन (substream->number) अणु
	हाल 0:
		वापस snd_es1938_playback1_prepare(substream);
	हाल 1:
		वापस snd_es1938_playback2_prepare(substream);
	पूर्ण
	snd_BUG();
	वापस -EINVAL;
पूर्ण

/* during the incrementing of dma counters the DMA रेजिस्टर पढ़ोs someबार
   वापसs garbage. To ensure a valid hw poपूर्णांकer, the following checks which
   should be very unlikely to fail are used:
   - is the current DMA address in the valid DMA range ?
   - is the sum of DMA address and DMA counter poपूर्णांकing to the last DMA byte ?
   One can argue this could dअगरfer by one byte depending on which रेजिस्टर is
   updated first, so the implementation below allows क्रम that.
*/
अटल snd_pcm_uframes_t snd_es1938_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा es1938 *chip = snd_pcm_substream_chip(substream);
	माप_प्रकार ptr;
#अगर 0
	माप_प्रकार old, new;
	/* This stuff is *needed*, करोn't ask why - AB */
	old = inw(SLDM_REG(chip, DMACOUNT));
	जबतक ((new = inw(SLDM_REG(chip, DMACOUNT))) != old)
		old = new;
	ptr = chip->dma1_size - 1 - new;
#अन्यथा
	माप_प्रकार count;
	अचिन्हित पूर्णांक dअगरf;

	ptr = inl(SLDM_REG(chip, DMAADDR));
	count = inw(SLDM_REG(chip, DMACOUNT));
	dअगरf = chip->dma1_start + chip->dma1_size - ptr - count;

	अगर (dअगरf > 3 || ptr < chip->dma1_start
	      || ptr >= chip->dma1_start+chip->dma1_size)
	  ptr = chip->last_capture_dmaaddr;            /* bad, use last saved */
	अन्यथा
	  chip->last_capture_dmaaddr = ptr;            /* good, remember it */

	ptr -= chip->dma1_start;
#पूर्ण_अगर
	वापस ptr >> chip->dma1_shअगरt;
पूर्ण

अटल snd_pcm_uframes_t snd_es1938_playback1_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा es1938 *chip = snd_pcm_substream_chip(substream);
	माप_प्रकार ptr;
#अगर 1
	ptr = chip->dma2_size - inw(SLIO_REG(chip, AUDIO2DMACOUNT));
#अन्यथा
	ptr = inl(SLIO_REG(chip, AUDIO2DMAADDR)) - chip->dma2_start;
#पूर्ण_अगर
	वापस ptr >> chip->dma2_shअगरt;
पूर्ण

अटल snd_pcm_uframes_t snd_es1938_playback2_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा es1938 *chip = snd_pcm_substream_chip(substream);
	माप_प्रकार ptr;
	माप_प्रकार old, new;
#अगर 1
	/* This stuff is *needed*, करोn't ask why - AB */
	old = inw(SLDM_REG(chip, DMACOUNT));
	जबतक ((new = inw(SLDM_REG(chip, DMACOUNT))) != old)
		old = new;
	ptr = chip->dma1_size - 1 - new;
#अन्यथा
	ptr = inl(SLDM_REG(chip, DMAADDR)) - chip->dma1_start;
#पूर्ण_अगर
	वापस ptr >> chip->dma1_shअगरt;
पूर्ण

अटल snd_pcm_uframes_t snd_es1938_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	चयन (substream->number) अणु
	हाल 0:
		वापस snd_es1938_playback1_poपूर्णांकer(substream);
	हाल 1:
		वापस snd_es1938_playback2_poपूर्णांकer(substream);
	पूर्ण
	snd_BUG();
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक snd_es1938_capture_copy(काष्ठा snd_pcm_substream *substream,
				   पूर्णांक channel, अचिन्हित दीर्घ pos,
				   व्योम __user *dst, अचिन्हित दीर्घ count)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा es1938 *chip = snd_pcm_substream_chip(substream);

	अगर (snd_BUG_ON(pos + count > chip->dma1_size))
		वापस -EINVAL;
	अगर (pos + count < chip->dma1_size) अणु
		अगर (copy_to_user(dst, runसमय->dma_area + pos + 1, count))
			वापस -EFAULT;
	पूर्ण अन्यथा अणु
		अगर (copy_to_user(dst, runसमय->dma_area + pos + 1, count - 1))
			वापस -EFAULT;
		अगर (put_user(runसमय->dma_area[0],
			     ((अचिन्हित अक्षर __user *)dst) + count - 1))
			वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1938_capture_copy_kernel(काष्ठा snd_pcm_substream *substream,
					  पूर्णांक channel, अचिन्हित दीर्घ pos,
					  व्योम *dst, अचिन्हित दीर्घ count)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा es1938 *chip = snd_pcm_substream_chip(substream);

	अगर (snd_BUG_ON(pos + count > chip->dma1_size))
		वापस -EINVAL;
	अगर (pos + count < chip->dma1_size) अणु
		स_नकल(dst, runसमय->dma_area + pos + 1, count);
	पूर्ण अन्यथा अणु
		स_नकल(dst, runसमय->dma_area + pos + 1, count - 1);
		runसमय->dma_area[0] = *((अचिन्हित अक्षर *)dst + count - 1);
	पूर्ण
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------
 * Audio1 Capture (ADC)
 * ----------------------------------------------------------------------*/
अटल स्थिर काष्ठा snd_pcm_hardware snd_es1938_capture =
अणु
	.info =			(SNDRV_PCM_INFO_INTERLEAVED |
				SNDRV_PCM_INFO_BLOCK_TRANSFER),
	.क्रमmats =		(SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE |
				 SNDRV_PCM_FMTBIT_S8 | SNDRV_PCM_FMTBIT_U16_LE),
	.rates =		SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		6000,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		2,
        .buffer_bytes_max =	0x8000,       /* DMA controller screws on higher values */
	.period_bytes_min =	64,
	.period_bytes_max =	0x8000,
	.periods_min =		1,
	.periods_max =		1024,
	.fअगरo_size =		256,
पूर्ण;

/* -----------------------------------------------------------------------
 * Audio2 Playback (DAC)
 * -----------------------------------------------------------------------*/
अटल स्थिर काष्ठा snd_pcm_hardware snd_es1938_playback =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =		(SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE |
				 SNDRV_PCM_FMTBIT_S8 | SNDRV_PCM_FMTBIT_U16_LE),
	.rates =		SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		6000,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		2,
        .buffer_bytes_max =	0x8000,       /* DMA controller screws on higher values */
	.period_bytes_min =	64,
	.period_bytes_max =	0x8000,
	.periods_min =		1,
	.periods_max =		1024,
	.fअगरo_size =		256,
पूर्ण;

अटल पूर्णांक snd_es1938_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा es1938 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	अगर (chip->playback2_substream)
		वापस -EAGAIN;
	chip->capture_substream = substream;
	runसमय->hw = snd_es1938_capture;
	snd_pcm_hw_स्थिरraपूर्णांक_ratnums(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				      &hw_स्थिरraपूर्णांकs_घड़ीs);
	snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय, SNDRV_PCM_HW_PARAM_BUFFER_BYTES, 0, 0xff00);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1938_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा es1938 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	चयन (substream->number) अणु
	हाल 0:
		chip->playback1_substream = substream;
		अवरोध;
	हाल 1:
		अगर (chip->capture_substream)
			वापस -EAGAIN;
		chip->playback2_substream = substream;
		अवरोध;
	शेष:
		snd_BUG();
		वापस -EINVAL;
	पूर्ण
	runसमय->hw = snd_es1938_playback;
	snd_pcm_hw_स्थिरraपूर्णांक_ratnums(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				      &hw_स्थिरraपूर्णांकs_घड़ीs);
	snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय, SNDRV_PCM_HW_PARAM_BUFFER_BYTES, 0, 0xff00);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1938_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा es1938 *chip = snd_pcm_substream_chip(substream);

	chip->capture_substream = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1938_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा es1938 *chip = snd_pcm_substream_chip(substream);

	चयन (substream->number) अणु
	हाल 0:
		chip->playback1_substream = शून्य;
		अवरोध;
	हाल 1:
		chip->playback2_substream = शून्य;
		अवरोध;
	शेष:
		snd_BUG();
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_es1938_playback_ops = अणु
	.खोलो =		snd_es1938_playback_खोलो,
	.बंद =	snd_es1938_playback_बंद,
	.prepare =	snd_es1938_playback_prepare,
	.trigger =	snd_es1938_playback_trigger,
	.poपूर्णांकer =	snd_es1938_playback_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_es1938_capture_ops = अणु
	.खोलो =		snd_es1938_capture_खोलो,
	.बंद =	snd_es1938_capture_बंद,
	.prepare =	snd_es1938_capture_prepare,
	.trigger =	snd_es1938_capture_trigger,
	.poपूर्णांकer =	snd_es1938_capture_poपूर्णांकer,
	.copy_user =	snd_es1938_capture_copy,
	.copy_kernel =	snd_es1938_capture_copy_kernel,
पूर्ण;

अटल पूर्णांक snd_es1938_new_pcm(काष्ठा es1938 *chip, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	अगर ((err = snd_pcm_new(chip->card, "es-1938-1946", device, 2, 1, &pcm)) < 0)
		वापस err;
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_es1938_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_es1938_capture_ops);
	
	pcm->निजी_data = chip;
	pcm->info_flags = 0;
	म_नकल(pcm->name, "ESS Solo-1");

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
				       &chip->pci->dev, 64*1024, 64*1024);

	chip->pcm = pcm;
	वापस 0;
पूर्ण

/* -------------------------------------------------------------------
 * 
 *                       *** Mixer part ***
 */

अटल पूर्णांक snd_es1938_info_mux(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[8] = अणु
		"Mic", "Mic Master", "CD", "AOUT",
		"Mic1", "Mix", "Line", "Master"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 8, texts);
पूर्ण

अटल पूर्णांक snd_es1938_get_mux(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा es1938 *chip = snd_kcontrol_chip(kcontrol);
	ucontrol->value.क्रमागतerated.item[0] = snd_es1938_mixer_पढ़ो(chip, 0x1c) & 0x07;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1938_put_mux(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा es1938 *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर val = ucontrol->value.क्रमागतerated.item[0];
	
	अगर (val > 7)
		वापस -EINVAL;
	वापस snd_es1938_mixer_bits(chip, 0x1c, 0x07, val) != val;
पूर्ण

#घोषणा snd_es1938_info_spatializer_enable	snd_ctl_boolean_mono_info

अटल पूर्णांक snd_es1938_get_spatializer_enable(काष्ठा snd_kcontrol *kcontrol,
					     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा es1938 *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर val = snd_es1938_mixer_पढ़ो(chip, 0x50);
	ucontrol->value.पूर्णांकeger.value[0] = !!(val & 8);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1938_put_spatializer_enable(काष्ठा snd_kcontrol *kcontrol,
					     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा es1938 *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर oval, nval;
	पूर्णांक change;
	nval = ucontrol->value.पूर्णांकeger.value[0] ? 0x0c : 0x04;
	oval = snd_es1938_mixer_पढ़ो(chip, 0x50) & 0x0c;
	change = nval != oval;
	अगर (change) अणु
		snd_es1938_mixer_ग_लिखो(chip, 0x50, nval & ~0x04);
		snd_es1938_mixer_ग_लिखो(chip, 0x50, nval);
	पूर्ण
	वापस change;
पूर्ण

अटल पूर्णांक snd_es1938_info_hw_volume(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 63;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1938_get_hw_volume(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा es1938 *chip = snd_kcontrol_chip(kcontrol);
	ucontrol->value.पूर्णांकeger.value[0] = snd_es1938_mixer_पढ़ो(chip, 0x61) & 0x3f;
	ucontrol->value.पूर्णांकeger.value[1] = snd_es1938_mixer_पढ़ो(chip, 0x63) & 0x3f;
	वापस 0;
पूर्ण

#घोषणा snd_es1938_info_hw_चयन		snd_ctl_boolean_stereo_info

अटल पूर्णांक snd_es1938_get_hw_चयन(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा es1938 *chip = snd_kcontrol_chip(kcontrol);
	ucontrol->value.पूर्णांकeger.value[0] = !(snd_es1938_mixer_पढ़ो(chip, 0x61) & 0x40);
	ucontrol->value.पूर्णांकeger.value[1] = !(snd_es1938_mixer_पढ़ो(chip, 0x63) & 0x40);
	वापस 0;
पूर्ण

अटल व्योम snd_es1938_hwv_मुक्त(काष्ठा snd_kcontrol *kcontrol)
अणु
	काष्ठा es1938 *chip = snd_kcontrol_chip(kcontrol);
	chip->master_volume = शून्य;
	chip->master_चयन = शून्य;
	chip->hw_volume = शून्य;
	chip->hw_चयन = शून्य;
पूर्ण

अटल पूर्णांक snd_es1938_reg_bits(काष्ठा es1938 *chip, अचिन्हित अक्षर reg,
			       अचिन्हित अक्षर mask, अचिन्हित अक्षर val)
अणु
	अगर (reg < 0xa0)
		वापस snd_es1938_mixer_bits(chip, reg, mask, val);
	अन्यथा
		वापस snd_es1938_bits(chip, reg, mask, val);
पूर्ण

अटल पूर्णांक snd_es1938_reg_पढ़ो(काष्ठा es1938 *chip, अचिन्हित अक्षर reg)
अणु
	अगर (reg < 0xa0)
		वापस snd_es1938_mixer_पढ़ो(chip, reg);
	अन्यथा
		वापस snd_es1938_पढ़ो(chip, reg);
पूर्ण

#घोषणा ES1938_SINGLE_TLV(xname, xindex, reg, shअगरt, mask, invert, xtlv)    \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
  .access = SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_TLV_READ,\
  .name = xname, .index = xindex, \
  .info = snd_es1938_info_single, \
  .get = snd_es1938_get_single, .put = snd_es1938_put_single, \
  .निजी_value = reg | (shअगरt << 8) | (mask << 16) | (invert << 24), \
  .tlv = अणु .p = xtlv पूर्ण पूर्ण
#घोषणा ES1938_SINGLE(xname, xindex, reg, shअगरt, mask, invert) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .info = snd_es1938_info_single, \
  .get = snd_es1938_get_single, .put = snd_es1938_put_single, \
  .निजी_value = reg | (shअगरt << 8) | (mask << 16) | (invert << 24) पूर्ण

अटल पूर्णांक snd_es1938_info_single(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;

	uinfo->type = mask == 1 ? SNDRV_CTL_ELEM_TYPE_BOOLEAN : SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = mask;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1938_get_single(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा es1938 *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 24) & 0xff;
	पूर्णांक val;
	
	val = snd_es1938_reg_पढ़ो(chip, reg);
	ucontrol->value.पूर्णांकeger.value[0] = (val >> shअगरt) & mask;
	अगर (invert)
		ucontrol->value.पूर्णांकeger.value[0] = mask - ucontrol->value.पूर्णांकeger.value[0];
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1938_put_single(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा es1938 *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 24) & 0xff;
	अचिन्हित अक्षर val;
	
	val = (ucontrol->value.पूर्णांकeger.value[0] & mask);
	अगर (invert)
		val = mask - val;
	mask <<= shअगरt;
	val <<= shअगरt;
	वापस snd_es1938_reg_bits(chip, reg, mask, val) != val;
पूर्ण

#घोषणा ES1938_DOUBLE_TLV(xname, xindex, left_reg, right_reg, shअगरt_left, shअगरt_right, mask, invert, xtlv) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
  .access = SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_TLV_READ,\
  .name = xname, .index = xindex, \
  .info = snd_es1938_info_द्विगुन, \
  .get = snd_es1938_get_द्विगुन, .put = snd_es1938_put_द्विगुन, \
  .निजी_value = left_reg | (right_reg << 8) | (shअगरt_left << 16) | (shअगरt_right << 19) | (mask << 24) | (invert << 22), \
  .tlv = अणु .p = xtlv पूर्ण पूर्ण
#घोषणा ES1938_DOUBLE(xname, xindex, left_reg, right_reg, shअगरt_left, shअगरt_right, mask, invert) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .info = snd_es1938_info_द्विगुन, \
  .get = snd_es1938_get_द्विगुन, .put = snd_es1938_put_द्विगुन, \
  .निजी_value = left_reg | (right_reg << 8) | (shअगरt_left << 16) | (shअगरt_right << 19) | (mask << 24) | (invert << 22) पूर्ण

अटल पूर्णांक snd_es1938_info_द्विगुन(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक mask = (kcontrol->निजी_value >> 24) & 0xff;

	uinfo->type = mask == 1 ? SNDRV_CTL_ELEM_TYPE_BOOLEAN : SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = mask;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1938_get_द्विगुन(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा es1938 *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक left_reg = kcontrol->निजी_value & 0xff;
	पूर्णांक right_reg = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक shअगरt_left = (kcontrol->निजी_value >> 16) & 0x07;
	पूर्णांक shअगरt_right = (kcontrol->निजी_value >> 19) & 0x07;
	पूर्णांक mask = (kcontrol->निजी_value >> 24) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 22) & 1;
	अचिन्हित अक्षर left, right;
	
	left = snd_es1938_reg_पढ़ो(chip, left_reg);
	अगर (left_reg != right_reg)
		right = snd_es1938_reg_पढ़ो(chip, right_reg);
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

अटल पूर्णांक snd_es1938_put_द्विगुन(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा es1938 *chip = snd_kcontrol_chip(kcontrol);
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
		अगर (snd_es1938_reg_bits(chip, left_reg, mask1, val1) != val1)
			change = 1;
		अगर (snd_es1938_reg_bits(chip, right_reg, mask2, val2) != val2)
			change = 1;
	पूर्ण अन्यथा अणु
		change = (snd_es1938_reg_bits(chip, left_reg, mask1 | mask2, 
					      val1 | val2) != (val1 | val2));
	पूर्ण
	वापस change;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_RANGE(db_scale_master,
	0, 54, TLV_DB_SCALE_ITEM(-3600, 50, 1),
	54, 63, TLV_DB_SCALE_ITEM(-900, 100, 0),
);

अटल स्थिर DECLARE_TLV_DB_RANGE(db_scale_audio1,
	0, 8, TLV_DB_SCALE_ITEM(-3300, 300, 1),
	8, 15, TLV_DB_SCALE_ITEM(-900, 150, 0),
);

अटल स्थिर DECLARE_TLV_DB_RANGE(db_scale_audio2,
	0, 8, TLV_DB_SCALE_ITEM(-3450, 300, 1),
	8, 15, TLV_DB_SCALE_ITEM(-1050, 150, 0),
);

अटल स्थिर DECLARE_TLV_DB_RANGE(db_scale_mic,
	0, 8, TLV_DB_SCALE_ITEM(-2400, 300, 1),
	8, 15, TLV_DB_SCALE_ITEM(0, 150, 0),
);

अटल स्थिर DECLARE_TLV_DB_RANGE(db_scale_line,
	0, 8, TLV_DB_SCALE_ITEM(-3150, 300, 1),
	8, 15, TLV_DB_SCALE_ITEM(-750, 150, 0),
);

अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_capture, 0, 150, 0);

अटल स्थिर काष्ठा snd_kcontrol_new snd_es1938_controls[] = अणु
ES1938_DOUBLE_TLV("Master Playback Volume", 0, 0x60, 0x62, 0, 0, 63, 0,
		  db_scale_master),
ES1938_DOUBLE("Master Playback Switch", 0, 0x60, 0x62, 6, 6, 1, 1),
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Hardware Master Playback Volume",
	.access = SNDRV_CTL_ELEM_ACCESS_READ,
	.info = snd_es1938_info_hw_volume,
	.get = snd_es1938_get_hw_volume,
पूर्ण,
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = (SNDRV_CTL_ELEM_ACCESS_READ |
		   SNDRV_CTL_ELEM_ACCESS_TLV_READ),
	.name = "Hardware Master Playback Switch",
	.info = snd_es1938_info_hw_चयन,
	.get = snd_es1938_get_hw_चयन,
	.tlv = अणु .p = db_scale_master पूर्ण,
पूर्ण,
ES1938_SINGLE("Hardware Volume Split", 0, 0x64, 7, 1, 0),
ES1938_DOUBLE_TLV("Line Playback Volume", 0, 0x3e, 0x3e, 4, 0, 15, 0,
		  db_scale_line),
ES1938_DOUBLE("CD Playback Volume", 0, 0x38, 0x38, 4, 0, 15, 0),
ES1938_DOUBLE_TLV("FM Playback Volume", 0, 0x36, 0x36, 4, 0, 15, 0,
		  db_scale_mic),
ES1938_DOUBLE_TLV("Mono Playback Volume", 0, 0x6d, 0x6d, 4, 0, 15, 0,
		  db_scale_line),
ES1938_DOUBLE_TLV("Mic Playback Volume", 0, 0x1a, 0x1a, 4, 0, 15, 0,
		  db_scale_mic),
ES1938_DOUBLE_TLV("Aux Playback Volume", 0, 0x3a, 0x3a, 4, 0, 15, 0,
		  db_scale_line),
ES1938_DOUBLE_TLV("Capture Volume", 0, 0xb4, 0xb4, 4, 0, 15, 0,
		  db_scale_capture),
ES1938_SINGLE("Beep Volume", 0, 0x3c, 0, 7, 0),
ES1938_SINGLE("Record Monitor", 0, 0xa8, 3, 1, 0),
ES1938_SINGLE("Capture Switch", 0, 0x1c, 4, 1, 1),
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Capture Source",
	.info = snd_es1938_info_mux,
	.get = snd_es1938_get_mux,
	.put = snd_es1938_put_mux,
पूर्ण,
ES1938_DOUBLE_TLV("Mono Input Playback Volume", 0, 0x6d, 0x6d, 4, 0, 15, 0,
		  db_scale_line),
ES1938_DOUBLE_TLV("PCM Capture Volume", 0, 0x69, 0x69, 4, 0, 15, 0,
		  db_scale_audio2),
ES1938_DOUBLE_TLV("Mic Capture Volume", 0, 0x68, 0x68, 4, 0, 15, 0,
		  db_scale_mic),
ES1938_DOUBLE_TLV("Line Capture Volume", 0, 0x6e, 0x6e, 4, 0, 15, 0,
		  db_scale_line),
ES1938_DOUBLE_TLV("FM Capture Volume", 0, 0x6b, 0x6b, 4, 0, 15, 0,
		  db_scale_mic),
ES1938_DOUBLE_TLV("Mono Capture Volume", 0, 0x6f, 0x6f, 4, 0, 15, 0,
		  db_scale_line),
ES1938_DOUBLE_TLV("CD Capture Volume", 0, 0x6a, 0x6a, 4, 0, 15, 0,
		  db_scale_line),
ES1938_DOUBLE_TLV("Aux Capture Volume", 0, 0x6c, 0x6c, 4, 0, 15, 0,
		  db_scale_line),
ES1938_DOUBLE_TLV("PCM Playback Volume", 0, 0x7c, 0x7c, 4, 0, 15, 0,
		  db_scale_audio2),
ES1938_DOUBLE_TLV("PCM Playback Volume", 1, 0x14, 0x14, 4, 0, 15, 0,
		  db_scale_audio1),
ES1938_SINGLE("3D Control - Level", 0, 0x52, 0, 63, 0),
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "3D Control - Switch",
	.info = snd_es1938_info_spatializer_enable,
	.get = snd_es1938_get_spatializer_enable,
	.put = snd_es1938_put_spatializer_enable,
पूर्ण,
ES1938_SINGLE("Mic Boost (+26dB)", 0, 0x7d, 3, 1, 0)
पूर्ण;


/* ---------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------- */

/*
 * initialize the chip - used by resume callback, too
 */
अटल व्योम snd_es1938_chip_init(काष्ठा es1938 *chip)
अणु
	/* reset chip */
	snd_es1938_reset(chip);

	/* configure native mode */

	/* enable bus master */
	pci_set_master(chip->pci);

	/* disable legacy audio */
	pci_ग_लिखो_config_word(chip->pci, SL_PCI_LEGACYCONTROL, 0x805f);

	/* set DDMA base */
	pci_ग_लिखो_config_word(chip->pci, SL_PCI_DDMACONTROL, chip->ddma_port | 1);

	/* set DMA/IRQ policy */
	pci_ग_लिखो_config_dword(chip->pci, SL_PCI_CONFIG, 0);

	/* enable Audio 1, Audio 2, MPU401 IRQ and HW volume IRQ*/
	outb(0xf0, SLIO_REG(chip, IRQCONTROL));

	/* reset DMA */
	outb(0, SLDM_REG(chip, DMACLEAR));
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
/*
 * PM support
 */

अटल स्थिर अचिन्हित अक्षर saved_regs[SAVED_REG_SIZE+1] = अणु
	0x14, 0x1a, 0x1c, 0x3a, 0x3c, 0x3e, 0x36, 0x38,
	0x50, 0x52, 0x60, 0x61, 0x62, 0x63, 0x64, 0x68,
	0x69, 0x6a, 0x6b, 0x6d, 0x6e, 0x6f, 0x7c, 0x7d,
	0xa8, 0xb4,
पूर्ण;


अटल पूर्णांक es1938_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा es1938 *chip = card->निजी_data;
	स्थिर अचिन्हित अक्षर *s;
	अचिन्हित अक्षर *d;

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);

	/* save mixer-related रेजिस्टरs */
	क्रम (s = saved_regs, d = chip->saved_regs; *s; s++, d++)
		*d = snd_es1938_reg_पढ़ो(chip, *s);

	outb(0x00, SLIO_REG(chip, IRQCONTROL)); /* disable irqs */
	अगर (chip->irq >= 0) अणु
		मुक्त_irq(chip->irq, chip);
		chip->irq = -1;
		card->sync_irq = -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक es1938_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci = to_pci_dev(dev);
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा es1938 *chip = card->निजी_data;
	स्थिर अचिन्हित अक्षर *s;
	अचिन्हित अक्षर *d;

	अगर (request_irq(pci->irq, snd_es1938_पूर्णांकerrupt,
			IRQF_SHARED, KBUILD_MODNAME, chip)) अणु
		dev_err(dev, "unable to grab IRQ %d, disabling device\n",
			pci->irq);
		snd_card_disconnect(card);
		वापस -EIO;
	पूर्ण
	chip->irq = pci->irq;
	card->sync_irq = chip->irq;
	snd_es1938_chip_init(chip);

	/* restore mixer-related रेजिस्टरs */
	क्रम (s = saved_regs, d = chip->saved_regs; *s; s++, d++) अणु
		अगर (*s < 0xa0)
			snd_es1938_mixer_ग_लिखो(chip, *s, *d);
		अन्यथा
			snd_es1938_ग_लिखो(chip, *s, *d);
	पूर्ण

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(es1938_pm, es1938_suspend, es1938_resume);
#घोषणा ES1938_PM_OPS	&es1938_pm
#अन्यथा
#घोषणा ES1938_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

#अगर_घोषित SUPPORT_JOYSTICK
अटल पूर्णांक snd_es1938_create_gameport(काष्ठा es1938 *chip)
अणु
	काष्ठा gameport *gp;

	chip->gameport = gp = gameport_allocate_port();
	अगर (!gp) अणु
		dev_err(chip->card->dev,
			"cannot allocate memory for gameport\n");
		वापस -ENOMEM;
	पूर्ण

	gameport_set_name(gp, "ES1938");
	gameport_set_phys(gp, "pci%s/gameport0", pci_name(chip->pci));
	gameport_set_dev_parent(gp, &chip->pci->dev);
	gp->io = chip->game_port;

	gameport_रेजिस्टर_port(gp);

	वापस 0;
पूर्ण

अटल व्योम snd_es1938_मुक्त_gameport(काष्ठा es1938 *chip)
अणु
	अगर (chip->gameport) अणु
		gameport_unरेजिस्टर_port(chip->gameport);
		chip->gameport = शून्य;
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक snd_es1938_create_gameport(काष्ठा es1938 *chip) अणु वापस -ENOSYS; पूर्ण
अटल अंतरभूत व्योम snd_es1938_मुक्त_gameport(काष्ठा es1938 *chip) अणु पूर्ण
#पूर्ण_अगर /* SUPPORT_JOYSTICK */

अटल पूर्णांक snd_es1938_मुक्त(काष्ठा es1938 *chip)
अणु
	/* disable irqs */
	outb(0x00, SLIO_REG(chip, IRQCONTROL));
	अगर (chip->rmidi)
		snd_es1938_mixer_bits(chip, ESSSB_IREG_MPU401CONTROL, 0x40, 0);

	snd_es1938_मुक्त_gameport(chip);

	अगर (chip->irq >= 0)
		मुक्त_irq(chip->irq, chip);
	pci_release_regions(chip->pci);
	pci_disable_device(chip->pci);
	kमुक्त(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1938_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा es1938 *chip = device->device_data;
	वापस snd_es1938_मुक्त(chip);
पूर्ण

अटल पूर्णांक snd_es1938_create(काष्ठा snd_card *card,
			     काष्ठा pci_dev *pci,
			     काष्ठा es1938 **rchip)
अणु
	काष्ठा es1938 *chip;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =	snd_es1938_dev_मुक्त,
	पूर्ण;

	*rchip = शून्य;

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

	chip = kzalloc(माप(*chip), GFP_KERNEL);
	अगर (chip == शून्य) अणु
		pci_disable_device(pci);
		वापस -ENOMEM;
	पूर्ण
	spin_lock_init(&chip->reg_lock);
	spin_lock_init(&chip->mixer_lock);
	chip->card = card;
	chip->pci = pci;
	chip->irq = -1;
	अगर ((err = pci_request_regions(pci, "ESS Solo-1")) < 0) अणु
		kमुक्त(chip);
		pci_disable_device(pci);
		वापस err;
	पूर्ण
	chip->io_port = pci_resource_start(pci, 0);
	chip->sb_port = pci_resource_start(pci, 1);
	chip->vc_port = pci_resource_start(pci, 2);
	chip->mpu_port = pci_resource_start(pci, 3);
	chip->game_port = pci_resource_start(pci, 4);
	अगर (request_irq(pci->irq, snd_es1938_पूर्णांकerrupt, IRQF_SHARED,
			KBUILD_MODNAME, chip)) अणु
		dev_err(card->dev, "unable to grab IRQ %d\n", pci->irq);
		snd_es1938_मुक्त(chip);
		वापस -EBUSY;
	पूर्ण
	chip->irq = pci->irq;
	card->sync_irq = chip->irq;
	dev_dbg(card->dev,
		"create: io: 0x%lx, sb: 0x%lx, vc: 0x%lx, mpu: 0x%lx, game: 0x%lx\n",
		   chip->io_port, chip->sb_port, chip->vc_port, chip->mpu_port, chip->game_port);

	chip->ddma_port = chip->vc_port + 0x00;		/* fix from Thomas Sailer */

	snd_es1938_chip_init(chip);

	अगर ((err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops)) < 0) अणु
		snd_es1938_मुक्त(chip);
		वापस err;
	पूर्ण

	*rchip = chip;
	वापस 0;
पूर्ण

/* --------------------------------------------------------------------
 * Interrupt handler
 * -------------------------------------------------------------------- */
अटल irqवापस_t snd_es1938_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा es1938 *chip = dev_id;
	अचिन्हित अक्षर status;
	__always_unused अचिन्हित अक्षर audiostatus;
	पूर्णांक handled = 0;

	status = inb(SLIO_REG(chip, IRQCONTROL));
#अगर 0
	dev_dbg(chip->card->dev,
		"Es1938debug - interrupt status: =0x%x\n", status);
#पूर्ण_अगर
	
	/* AUDIO 1 */
	अगर (status & 0x10) अणु
#अगर 0
		dev_dbg(chip->card->dev,
		       "Es1938debug - AUDIO channel 1 interrupt\n");
		dev_dbg(chip->card->dev,
		       "Es1938debug - AUDIO channel 1 DMAC DMA count: %u\n",
		       inw(SLDM_REG(chip, DMACOUNT)));
		dev_dbg(chip->card->dev,
		       "Es1938debug - AUDIO channel 1 DMAC DMA base: %u\n",
		       inl(SLDM_REG(chip, DMAADDR)));
		dev_dbg(chip->card->dev,
		       "Es1938debug - AUDIO channel 1 DMAC DMA status: 0x%x\n",
		       inl(SLDM_REG(chip, DMASTATUS)));
#पूर्ण_अगर
		/* clear irq */
		handled = 1;
		audiostatus = inb(SLSB_REG(chip, STATUS));
		अगर (chip->active & ADC1)
			snd_pcm_period_elapsed(chip->capture_substream);
		अन्यथा अगर (chip->active & DAC1)
			snd_pcm_period_elapsed(chip->playback2_substream);
	पूर्ण
	
	/* AUDIO 2 */
	अगर (status & 0x20) अणु
#अगर 0
		dev_dbg(chip->card->dev,
		       "Es1938debug - AUDIO channel 2 interrupt\n");
		dev_dbg(chip->card->dev,
		       "Es1938debug - AUDIO channel 2 DMAC DMA count: %u\n",
		       inw(SLIO_REG(chip, AUDIO2DMACOUNT)));
		dev_dbg(chip->card->dev,
		       "Es1938debug - AUDIO channel 2 DMAC DMA base: %u\n",
		       inl(SLIO_REG(chip, AUDIO2DMAADDR)));

#पूर्ण_अगर
		/* clear irq */
		handled = 1;
		snd_es1938_mixer_bits(chip, ESSSB_IREG_AUDIO2CONTROL2, 0x80, 0);
		अगर (chip->active & DAC2)
			snd_pcm_period_elapsed(chip->playback1_substream);
	पूर्ण

	/* Hardware volume */
	अगर (status & 0x40) अणु
		पूर्णांक split = snd_es1938_mixer_पढ़ो(chip, 0x64) & 0x80;
		handled = 1;
		snd_ctl_notअगरy(chip->card, SNDRV_CTL_EVENT_MASK_VALUE, &chip->hw_चयन->id);
		snd_ctl_notअगरy(chip->card, SNDRV_CTL_EVENT_MASK_VALUE, &chip->hw_volume->id);
		अगर (!split) अणु
			snd_ctl_notअगरy(chip->card, SNDRV_CTL_EVENT_MASK_VALUE,
				       &chip->master_चयन->id);
			snd_ctl_notअगरy(chip->card, SNDRV_CTL_EVENT_MASK_VALUE,
				       &chip->master_volume->id);
		पूर्ण
		/* ack पूर्णांकerrupt */
		snd_es1938_mixer_ग_लिखो(chip, 0x66, 0x00);
	पूर्ण

	/* MPU401 */
	अगर (status & 0x80) अणु
		// the following line is evil! It चयनes off MIDI पूर्णांकerrupt handling after the first पूर्णांकerrupt received.
		// replacing the last 0 by 0x40 works क्रम ESS-Solo1, but just करोing nothing works as well!
		// andreas@flying-snail.de
		// snd_es1938_mixer_bits(chip, ESSSB_IREG_MPU401CONTROL, 0x40, 0); /* ack? */
		अगर (chip->rmidi) अणु
			handled = 1;
			snd_mpu401_uart_पूर्णांकerrupt(irq, chip->rmidi->निजी_data);
		पूर्ण
	पूर्ण
	वापस IRQ_RETVAL(handled);
पूर्ण

#घोषणा ES1938_DMA_SIZE 64

अटल पूर्णांक snd_es1938_mixer(काष्ठा es1938 *chip)
अणु
	काष्ठा snd_card *card;
	अचिन्हित पूर्णांक idx;
	पूर्णांक err;

	card = chip->card;

	म_नकल(card->mixername, "ESS Solo-1");

	क्रम (idx = 0; idx < ARRAY_SIZE(snd_es1938_controls); idx++) अणु
		काष्ठा snd_kcontrol *kctl;
		kctl = snd_ctl_new1(&snd_es1938_controls[idx], chip);
		चयन (idx) अणु
			हाल 0:
				chip->master_volume = kctl;
				kctl->निजी_मुक्त = snd_es1938_hwv_मुक्त;
				अवरोध;
			हाल 1:
				chip->master_चयन = kctl;
				kctl->निजी_मुक्त = snd_es1938_hwv_मुक्त;
				अवरोध;
			हाल 2:
				chip->hw_volume = kctl;
				kctl->निजी_मुक्त = snd_es1938_hwv_मुक्त;
				अवरोध;
			हाल 3:
				chip->hw_चयन = kctl;
				kctl->निजी_मुक्त = snd_es1938_hwv_मुक्त;
				अवरोध;
			पूर्ण
		अगर ((err = snd_ctl_add(card, kctl)) < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण
       

अटल पूर्णांक snd_es1938_probe(काष्ठा pci_dev *pci,
			    स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_card *card;
	काष्ठा es1938 *chip;
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
	अगर ((err = snd_es1938_create(card, pci, &chip)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	card->निजी_data = chip;

	म_नकल(card->driver, "ES1938");
	म_नकल(card->लघुname, "ESS ES1938 (Solo-1)");
	प्र_लिखो(card->दीर्घname, "%s rev %i, irq %i",
		card->लघुname,
		chip->revision,
		chip->irq);

	अगर ((err = snd_es1938_new_pcm(chip, 0)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	अगर ((err = snd_es1938_mixer(chip)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	अगर (snd_opl3_create(card,
			    SLSB_REG(chip, FMLOWADDR),
			    SLSB_REG(chip, FMHIGHADDR),
			    OPL3_HW_OPL3, 1, &opl3) < 0) अणु
		dev_err(card->dev, "OPL3 not detected at 0x%lx\n",
			   SLSB_REG(chip, FMLOWADDR));
	पूर्ण अन्यथा अणु
	        अगर ((err = snd_opl3_समयr_new(opl3, 0, 1)) < 0) अणु
	                snd_card_मुक्त(card);
	                वापस err;
		पूर्ण
	        अगर ((err = snd_opl3_hwdep_new(opl3, 0, 1, शून्य)) < 0) अणु
	                snd_card_मुक्त(card);
	                वापस err;
		पूर्ण
	पूर्ण
	अगर (snd_mpu401_uart_new(card, 0, MPU401_HW_MPU401,
				chip->mpu_port,
				MPU401_INFO_INTEGRATED | MPU401_INFO_IRQ_HOOK,
				-1, &chip->rmidi) < 0) अणु
		dev_err(card->dev, "unable to initialize MPU-401\n");
	पूर्ण अन्यथा अणु
		// this line is vital क्रम MIDI पूर्णांकerrupt handling on ess-solo1
		// andreas@flying-snail.de
		snd_es1938_mixer_bits(chip, ESSSB_IREG_MPU401CONTROL, 0x40, 0x40);
	पूर्ण

	snd_es1938_create_gameport(chip);

	अगर ((err = snd_card_रेजिस्टर(card)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	pci_set_drvdata(pci, card);
	dev++;
	वापस 0;
पूर्ण

अटल व्योम snd_es1938_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण

अटल काष्ठा pci_driver es1938_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_es1938_ids,
	.probe = snd_es1938_probe,
	.हटाओ = snd_es1938_हटाओ,
	.driver = अणु
		.pm = ES1938_PM_OPS,
	पूर्ण,
पूर्ण;

module_pci_driver(es1938_driver);
