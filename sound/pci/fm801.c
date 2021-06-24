<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  The driver क्रम the ForteMedia FM801 based soundcards
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/tlv.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/mpu401.h>
#समावेश <sound/opl3.h>
#समावेश <sound/initval.h>

#अगर_घोषित CONFIG_SND_FM801_TEA575X_BOOL
#समावेश <media/drv-पूर्णांकf/tea575x.h>
#पूर्ण_अगर

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("ForteMedia FM801");
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;	/* Enable this card */
/*
 *  Enable TEA575x tuner
 *    1 = MediaForte 256-PCS
 *    2 = MediaForte 256-PCP
 *    3 = MediaForte 64-PCR
 *   16 = setup tuner only (this is additional bit), i.e. SF64-PCR FM card
 *  High 16-bits are video (radio) device number + 1
 */
अटल पूर्णांक tea575x_tuner[SNDRV_CARDS];
अटल पूर्णांक radio_nr[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = -1पूर्ण;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for the FM801 soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for the FM801 soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable FM801 soundcard.");
module_param_array(tea575x_tuner, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(tea575x_tuner, "TEA575x tuner access method (0 = auto, 1 = SF256-PCS, 2=SF256-PCP, 3=SF64-PCR, 8=disable, +16=tuner-only).");
module_param_array(radio_nr, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(radio_nr, "Radio device numbers");


#घोषणा TUNER_DISABLED		(1<<3)
#घोषणा TUNER_ONLY		(1<<4)
#घोषणा TUNER_TYPE_MASK		(~TUNER_ONLY & 0xFFFF)

/*
 *  Direct रेजिस्टरs
 */

#घोषणा fm801_ग_लिखोw(chip,reg,value)	outw((value), chip->port + FM801_##reg)
#घोषणा fm801_पढ़ोw(chip,reg)		inw(chip->port + FM801_##reg)

#घोषणा fm801_ग_लिखोl(chip,reg,value)	outl((value), chip->port + FM801_##reg)

#घोषणा FM801_PCM_VOL		0x00	/* PCM Output Volume */
#घोषणा FM801_FM_VOL		0x02	/* FM Output Volume */
#घोषणा FM801_I2S_VOL		0x04	/* I2S Volume */
#घोषणा FM801_REC_SRC		0x06	/* Record Source */
#घोषणा FM801_PLY_CTRL		0x08	/* Playback Control */
#घोषणा FM801_PLY_COUNT		0x0a	/* Playback Count */
#घोषणा FM801_PLY_BUF1		0x0c	/* Playback Bufer I */
#घोषणा FM801_PLY_BUF2		0x10	/* Playback Buffer II */
#घोषणा FM801_CAP_CTRL		0x14	/* Capture Control */
#घोषणा FM801_CAP_COUNT		0x16	/* Capture Count */
#घोषणा FM801_CAP_BUF1		0x18	/* Capture Buffer I */
#घोषणा FM801_CAP_BUF2		0x1c	/* Capture Buffer II */
#घोषणा FM801_CODEC_CTRL	0x22	/* Codec Control */
#घोषणा FM801_I2S_MODE		0x24	/* I2S Mode Control */
#घोषणा FM801_VOLUME		0x26	/* Volume Up/Down/Mute Status */
#घोषणा FM801_I2C_CTRL		0x29	/* I2C Control */
#घोषणा FM801_AC97_CMD		0x2a	/* AC'97 Command */
#घोषणा FM801_AC97_DATA		0x2c	/* AC'97 Data */
#घोषणा FM801_MPU401_DATA	0x30	/* MPU401 Data */
#घोषणा FM801_MPU401_CMD	0x31	/* MPU401 Command */
#घोषणा FM801_GPIO_CTRL		0x52	/* General Purpose I/O Control */
#घोषणा FM801_GEN_CTRL		0x54	/* General Control */
#घोषणा FM801_IRQ_MASK		0x56	/* Interrupt Mask */
#घोषणा FM801_IRQ_STATUS	0x5a	/* Interrupt Status */
#घोषणा FM801_OPL3_BANK0	0x68	/* OPL3 Status Read / Bank 0 Write */
#घोषणा FM801_OPL3_DATA0	0x69	/* OPL3 Data 0 Write */
#घोषणा FM801_OPL3_BANK1	0x6a	/* OPL3 Bank 1 Write */
#घोषणा FM801_OPL3_DATA1	0x6b	/* OPL3 Bank 1 Write */
#घोषणा FM801_POWERDOWN		0x70	/* Blocks Power Down Control */

/* codec access */
#घोषणा FM801_AC97_READ		(1<<7)	/* पढ़ो=1, ग_लिखो=0 */
#घोषणा FM801_AC97_VALID	(1<<8)	/* port valid=1 */
#घोषणा FM801_AC97_BUSY		(1<<9)	/* busy=1 */
#घोषणा FM801_AC97_ADDR_SHIFT	10	/* codec id (2bit) */

/* playback and record control रेजिस्टर bits */
#घोषणा FM801_BUF1_LAST		(1<<1)
#घोषणा FM801_BUF2_LAST		(1<<2)
#घोषणा FM801_START		(1<<5)
#घोषणा FM801_PAUSE		(1<<6)
#घोषणा FM801_IMMED_STOP	(1<<7)
#घोषणा FM801_RATE_SHIFT	8
#घोषणा FM801_RATE_MASK		(15 << FM801_RATE_SHIFT)
#घोषणा FM801_CHANNELS_4	(1<<12)	/* playback only */
#घोषणा FM801_CHANNELS_6	(2<<12)	/* playback only */
#घोषणा FM801_CHANNELS_6MS	(3<<12)	/* playback only */
#घोषणा FM801_CHANNELS_MASK	(3<<12)
#घोषणा FM801_16BIT		(1<<14)
#घोषणा FM801_STEREO		(1<<15)

/* IRQ status bits */
#घोषणा FM801_IRQ_PLAYBACK	(1<<8)
#घोषणा FM801_IRQ_CAPTURE	(1<<9)
#घोषणा FM801_IRQ_VOLUME	(1<<14)
#घोषणा FM801_IRQ_MPU		(1<<15)

/* GPIO control रेजिस्टर */
#घोषणा FM801_GPIO_GP0		(1<<0)	/* पढ़ो/ग_लिखो */
#घोषणा FM801_GPIO_GP1		(1<<1)
#घोषणा FM801_GPIO_GP2		(1<<2)
#घोषणा FM801_GPIO_GP3		(1<<3)
#घोषणा FM801_GPIO_GP(x)	(1<<(0+(x)))
#घोषणा FM801_GPIO_GD0		(1<<8)	/* directions: 1 = input, 0 = output*/
#घोषणा FM801_GPIO_GD1		(1<<9)
#घोषणा FM801_GPIO_GD2		(1<<10)
#घोषणा FM801_GPIO_GD3		(1<<11)
#घोषणा FM801_GPIO_GD(x)	(1<<(8+(x)))
#घोषणा FM801_GPIO_GS0		(1<<12)	/* function select: */
#घोषणा FM801_GPIO_GS1		(1<<13)	/*    1 = GPIO */
#घोषणा FM801_GPIO_GS2		(1<<14)	/*    0 = other (S/PDIF, VOL) */
#घोषणा FM801_GPIO_GS3		(1<<15)
#घोषणा FM801_GPIO_GS(x)	(1<<(12+(x)))
	
/**
 * काष्ठा fm801 - describes FM801 chip
 * @dev:		device क्रम this chio
 * @irq:		irq number
 * @port:		I/O port number
 * @multichannel:	multichannel support
 * @secondary:		secondary codec
 * @secondary_addr:	address of the secondary codec
 * @tea575x_tuner:	tuner access method & flags
 * @ply_ctrl:		playback control
 * @cap_ctrl:		capture control
 * @ply_buffer:		playback buffer
 * @ply_buf:		playback buffer index
 * @ply_count:		playback buffer count
 * @ply_size:		playback buffer size
 * @ply_pos:		playback position
 * @cap_buffer:		capture buffer
 * @cap_buf:		capture buffer index
 * @cap_count:		capture buffer count
 * @cap_size:		capture buffer size
 * @cap_pos:		capture position
 * @ac97_bus:		ac97 bus handle
 * @ac97:		ac97 handle
 * @ac97_sec:		ac97 secondary handle
 * @card:		ALSA card
 * @pcm:		PCM devices
 * @rmidi:		rmidi device
 * @playback_substream:	substream क्रम playback
 * @capture_substream:	substream क्रम capture
 * @p_dma_size:		playback DMA size
 * @c_dma_size:		capture DMA size
 * @reg_lock:		lock
 * @proc_entry:		/proc entry
 * @v4l2_dev:		v4l2 device
 * @tea:		tea575a काष्ठाure
 * @saved_regs:		context saved during suspend
 */
काष्ठा fm801 अणु
	काष्ठा device *dev;
	पूर्णांक irq;

	अचिन्हित दीर्घ port;
	अचिन्हित पूर्णांक multichannel: 1,
		     secondary: 1;
	अचिन्हित अक्षर secondary_addr;
	अचिन्हित पूर्णांक tea575x_tuner;

	अचिन्हित लघु ply_ctrl;
	अचिन्हित लघु cap_ctrl;

	अचिन्हित दीर्घ ply_buffer;
	अचिन्हित पूर्णांक ply_buf;
	अचिन्हित पूर्णांक ply_count;
	अचिन्हित पूर्णांक ply_size;
	अचिन्हित पूर्णांक ply_pos;

	अचिन्हित दीर्घ cap_buffer;
	अचिन्हित पूर्णांक cap_buf;
	अचिन्हित पूर्णांक cap_count;
	अचिन्हित पूर्णांक cap_size;
	अचिन्हित पूर्णांक cap_pos;

	काष्ठा snd_ac97_bus *ac97_bus;
	काष्ठा snd_ac97 *ac97;
	काष्ठा snd_ac97 *ac97_sec;

	काष्ठा snd_card *card;
	काष्ठा snd_pcm *pcm;
	काष्ठा snd_rawmidi *rmidi;
	काष्ठा snd_pcm_substream *playback_substream;
	काष्ठा snd_pcm_substream *capture_substream;
	अचिन्हित पूर्णांक p_dma_size;
	अचिन्हित पूर्णांक c_dma_size;

	spinlock_t reg_lock;
	काष्ठा snd_info_entry *proc_entry;

#अगर_घोषित CONFIG_SND_FM801_TEA575X_BOOL
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा snd_tea575x tea;
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_SLEEP
	u16 saved_regs[0x20];
#पूर्ण_अगर
पूर्ण;

/*
 * IO accessors
 */

अटल अंतरभूत व्योम fm801_ioग_लिखो16(काष्ठा fm801 *chip, अचिन्हित लघु offset, u16 value)
अणु
	outw(value, chip->port + offset);
पूर्ण

अटल अंतरभूत u16 fm801_ioपढ़ो16(काष्ठा fm801 *chip, अचिन्हित लघु offset)
अणु
	वापस inw(chip->port + offset);
पूर्ण

अटल स्थिर काष्ठा pci_device_id snd_fm801_ids[] = अणु
	अणु 0x1319, 0x0801, PCI_ANY_ID, PCI_ANY_ID, PCI_CLASS_MULTIMEDIA_AUDIO << 8, 0xffff00, 0, पूर्ण,   /* FM801 */
	अणु 0x5213, 0x0510, PCI_ANY_ID, PCI_ANY_ID, PCI_CLASS_MULTIMEDIA_AUDIO << 8, 0xffff00, 0, पूर्ण,   /* Gallant Odyssey Sound 4 */
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, snd_fm801_ids);

/*
 *  common I/O routines
 */

अटल bool fm801_ac97_is_पढ़ोy(काष्ठा fm801 *chip, अचिन्हित पूर्णांक iterations)
अणु
	अचिन्हित पूर्णांक idx;

	क्रम (idx = 0; idx < iterations; idx++) अणु
		अगर (!(fm801_पढ़ोw(chip, AC97_CMD) & FM801_AC97_BUSY))
			वापस true;
		udelay(10);
	पूर्ण
	वापस false;
पूर्ण

अटल bool fm801_ac97_is_valid(काष्ठा fm801 *chip, अचिन्हित पूर्णांक iterations)
अणु
	अचिन्हित पूर्णांक idx;

	क्रम (idx = 0; idx < iterations; idx++) अणु
		अगर (fm801_पढ़ोw(chip, AC97_CMD) & FM801_AC97_VALID)
			वापस true;
		udelay(10);
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक snd_fm801_update_bits(काष्ठा fm801 *chip, अचिन्हित लघु reg,
				 अचिन्हित लघु mask, अचिन्हित लघु value)
अणु
	पूर्णांक change;
	अचिन्हित दीर्घ flags;
	अचिन्हित लघु old, new;

	spin_lock_irqsave(&chip->reg_lock, flags);
	old = fm801_ioपढ़ो16(chip, reg);
	new = (old & ~mask) | value;
	change = old != new;
	अगर (change)
		fm801_ioग_लिखो16(chip, reg, new);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस change;
पूर्ण

अटल व्योम snd_fm801_codec_ग_लिखो(काष्ठा snd_ac97 *ac97,
				  अचिन्हित लघु reg,
				  अचिन्हित लघु val)
अणु
	काष्ठा fm801 *chip = ac97->निजी_data;

	/*
	 *  Wait until the codec पूर्णांकerface is not पढ़ोy..
	 */
	अगर (!fm801_ac97_is_पढ़ोy(chip, 100)) अणु
		dev_err(chip->card->dev, "AC'97 interface is busy (1)\n");
		वापस;
	पूर्ण

	/* ग_लिखो data and address */
	fm801_ग_लिखोw(chip, AC97_DATA, val);
	fm801_ग_लिखोw(chip, AC97_CMD, reg | (ac97->addr << FM801_AC97_ADDR_SHIFT));
	/*
	 *  Wait until the ग_लिखो command is not completed..
	 */
	अगर (!fm801_ac97_is_पढ़ोy(chip, 1000))
		dev_err(chip->card->dev, "AC'97 interface #%d is busy (2)\n",
		ac97->num);
पूर्ण

अटल अचिन्हित लघु snd_fm801_codec_पढ़ो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg)
अणु
	काष्ठा fm801 *chip = ac97->निजी_data;

	/*
	 *  Wait until the codec पूर्णांकerface is not पढ़ोy..
	 */
	अगर (!fm801_ac97_is_पढ़ोy(chip, 100)) अणु
		dev_err(chip->card->dev, "AC'97 interface is busy (1)\n");
		वापस 0;
	पूर्ण

	/* पढ़ो command */
	fm801_ग_लिखोw(chip, AC97_CMD,
		     reg | (ac97->addr << FM801_AC97_ADDR_SHIFT) | FM801_AC97_READ);
	अगर (!fm801_ac97_is_पढ़ोy(chip, 100)) अणु
		dev_err(chip->card->dev, "AC'97 interface #%d is busy (2)\n",
			ac97->num);
		वापस 0;
	पूर्ण

	अगर (!fm801_ac97_is_valid(chip, 1000)) अणु
		dev_err(chip->card->dev,
			"AC'97 interface #%d is not valid (2)\n", ac97->num);
		वापस 0;
	पूर्ण

	वापस fm801_पढ़ोw(chip, AC97_DATA);
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक rates[] = अणु
  5500,  8000,  9600, 11025,
  16000, 19200, 22050, 32000,
  38400, 44100, 48000
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list hw_स्थिरraपूर्णांकs_rates = अणु
	.count = ARRAY_SIZE(rates),
	.list = rates,
	.mask = 0,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक channels[] = अणु
  2, 4, 6
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list hw_स्थिरraपूर्णांकs_channels = अणु
	.count = ARRAY_SIZE(channels),
	.list = channels,
	.mask = 0,
पूर्ण;

/*
 *  Sample rate routines
 */

अटल अचिन्हित लघु snd_fm801_rate_bits(अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित पूर्णांक idx;

	क्रम (idx = 0; idx < ARRAY_SIZE(rates); idx++)
		अगर (rates[idx] == rate)
			वापस idx;
	snd_BUG();
	वापस ARRAY_SIZE(rates) - 1;
पूर्ण

/*
 *  PCM part
 */

अटल पूर्णांक snd_fm801_playback_trigger(काष्ठा snd_pcm_substream *substream,
				      पूर्णांक cmd)
अणु
	काष्ठा fm801 *chip = snd_pcm_substream_chip(substream);

	spin_lock(&chip->reg_lock);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		chip->ply_ctrl &= ~(FM801_BUF1_LAST |
				     FM801_BUF2_LAST |
				     FM801_PAUSE);
		chip->ply_ctrl |= FM801_START |
				   FM801_IMMED_STOP;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		chip->ply_ctrl &= ~(FM801_START | FM801_PAUSE);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		chip->ply_ctrl |= FM801_PAUSE;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		chip->ply_ctrl &= ~FM801_PAUSE;
		अवरोध;
	शेष:
		spin_unlock(&chip->reg_lock);
		snd_BUG();
		वापस -EINVAL;
	पूर्ण
	fm801_ग_लिखोw(chip, PLY_CTRL, chip->ply_ctrl);
	spin_unlock(&chip->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_fm801_capture_trigger(काष्ठा snd_pcm_substream *substream,
				     पूर्णांक cmd)
अणु
	काष्ठा fm801 *chip = snd_pcm_substream_chip(substream);

	spin_lock(&chip->reg_lock);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		chip->cap_ctrl &= ~(FM801_BUF1_LAST |
				     FM801_BUF2_LAST |
				     FM801_PAUSE);
		chip->cap_ctrl |= FM801_START |
				   FM801_IMMED_STOP;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		chip->cap_ctrl &= ~(FM801_START | FM801_PAUSE);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		chip->cap_ctrl |= FM801_PAUSE;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		chip->cap_ctrl &= ~FM801_PAUSE;
		अवरोध;
	शेष:
		spin_unlock(&chip->reg_lock);
		snd_BUG();
		वापस -EINVAL;
	पूर्ण
	fm801_ग_लिखोw(chip, CAP_CTRL, chip->cap_ctrl);
	spin_unlock(&chip->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_fm801_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा fm801 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	chip->ply_size = snd_pcm_lib_buffer_bytes(substream);
	chip->ply_count = snd_pcm_lib_period_bytes(substream);
	spin_lock_irq(&chip->reg_lock);
	chip->ply_ctrl &= ~(FM801_START | FM801_16BIT |
			     FM801_STEREO | FM801_RATE_MASK |
			     FM801_CHANNELS_MASK);
	अगर (snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 16)
		chip->ply_ctrl |= FM801_16BIT;
	अगर (runसमय->channels > 1) अणु
		chip->ply_ctrl |= FM801_STEREO;
		अगर (runसमय->channels == 4)
			chip->ply_ctrl |= FM801_CHANNELS_4;
		अन्यथा अगर (runसमय->channels == 6)
			chip->ply_ctrl |= FM801_CHANNELS_6;
	पूर्ण
	chip->ply_ctrl |= snd_fm801_rate_bits(runसमय->rate) << FM801_RATE_SHIFT;
	chip->ply_buf = 0;
	fm801_ग_लिखोw(chip, PLY_CTRL, chip->ply_ctrl);
	fm801_ग_लिखोw(chip, PLY_COUNT, chip->ply_count - 1);
	chip->ply_buffer = runसमय->dma_addr;
	chip->ply_pos = 0;
	fm801_ग_लिखोl(chip, PLY_BUF1, chip->ply_buffer);
	fm801_ग_लिखोl(chip, PLY_BUF2,
		     chip->ply_buffer + (chip->ply_count % chip->ply_size));
	spin_unlock_irq(&chip->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_fm801_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा fm801 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	chip->cap_size = snd_pcm_lib_buffer_bytes(substream);
	chip->cap_count = snd_pcm_lib_period_bytes(substream);
	spin_lock_irq(&chip->reg_lock);
	chip->cap_ctrl &= ~(FM801_START | FM801_16BIT |
			     FM801_STEREO | FM801_RATE_MASK);
	अगर (snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 16)
		chip->cap_ctrl |= FM801_16BIT;
	अगर (runसमय->channels > 1)
		chip->cap_ctrl |= FM801_STEREO;
	chip->cap_ctrl |= snd_fm801_rate_bits(runसमय->rate) << FM801_RATE_SHIFT;
	chip->cap_buf = 0;
	fm801_ग_लिखोw(chip, CAP_CTRL, chip->cap_ctrl);
	fm801_ग_लिखोw(chip, CAP_COUNT, chip->cap_count - 1);
	chip->cap_buffer = runसमय->dma_addr;
	chip->cap_pos = 0;
	fm801_ग_लिखोl(chip, CAP_BUF1, chip->cap_buffer);
	fm801_ग_लिखोl(chip, CAP_BUF2,
		     chip->cap_buffer + (chip->cap_count % chip->cap_size));
	spin_unlock_irq(&chip->reg_lock);
	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t snd_fm801_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा fm801 *chip = snd_pcm_substream_chip(substream);
	माप_प्रकार ptr;

	अगर (!(chip->ply_ctrl & FM801_START))
		वापस 0;
	spin_lock(&chip->reg_lock);
	ptr = chip->ply_pos + (chip->ply_count - 1) - fm801_पढ़ोw(chip, PLY_COUNT);
	अगर (fm801_पढ़ोw(chip, IRQ_STATUS) & FM801_IRQ_PLAYBACK) अणु
		ptr += chip->ply_count;
		ptr %= chip->ply_size;
	पूर्ण
	spin_unlock(&chip->reg_lock);
	वापस bytes_to_frames(substream->runसमय, ptr);
पूर्ण

अटल snd_pcm_uframes_t snd_fm801_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा fm801 *chip = snd_pcm_substream_chip(substream);
	माप_प्रकार ptr;

	अगर (!(chip->cap_ctrl & FM801_START))
		वापस 0;
	spin_lock(&chip->reg_lock);
	ptr = chip->cap_pos + (chip->cap_count - 1) - fm801_पढ़ोw(chip, CAP_COUNT);
	अगर (fm801_पढ़ोw(chip, IRQ_STATUS) & FM801_IRQ_CAPTURE) अणु
		ptr += chip->cap_count;
		ptr %= chip->cap_size;
	पूर्ण
	spin_unlock(&chip->reg_lock);
	वापस bytes_to_frames(substream->runसमय, ptr);
पूर्ण

अटल irqवापस_t snd_fm801_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा fm801 *chip = dev_id;
	अचिन्हित लघु status;
	अचिन्हित पूर्णांक पंचांगp;

	status = fm801_पढ़ोw(chip, IRQ_STATUS);
	status &= FM801_IRQ_PLAYBACK|FM801_IRQ_CAPTURE|FM801_IRQ_MPU|FM801_IRQ_VOLUME;
	अगर (! status)
		वापस IRQ_NONE;
	/* ack first */
	fm801_ग_लिखोw(chip, IRQ_STATUS, status);
	अगर (chip->pcm && (status & FM801_IRQ_PLAYBACK) && chip->playback_substream) अणु
		spin_lock(&chip->reg_lock);
		chip->ply_buf++;
		chip->ply_pos += chip->ply_count;
		chip->ply_pos %= chip->ply_size;
		पंचांगp = chip->ply_pos + chip->ply_count;
		पंचांगp %= chip->ply_size;
		अगर (chip->ply_buf & 1)
			fm801_ग_लिखोl(chip, PLY_BUF1, chip->ply_buffer + पंचांगp);
		अन्यथा
			fm801_ग_लिखोl(chip, PLY_BUF2, chip->ply_buffer + पंचांगp);
		spin_unlock(&chip->reg_lock);
		snd_pcm_period_elapsed(chip->playback_substream);
	पूर्ण
	अगर (chip->pcm && (status & FM801_IRQ_CAPTURE) && chip->capture_substream) अणु
		spin_lock(&chip->reg_lock);
		chip->cap_buf++;
		chip->cap_pos += chip->cap_count;
		chip->cap_pos %= chip->cap_size;
		पंचांगp = chip->cap_pos + chip->cap_count;
		पंचांगp %= chip->cap_size;
		अगर (chip->cap_buf & 1)
			fm801_ग_लिखोl(chip, CAP_BUF1, chip->cap_buffer + पंचांगp);
		अन्यथा
			fm801_ग_लिखोl(chip, CAP_BUF2, chip->cap_buffer + पंचांगp);
		spin_unlock(&chip->reg_lock);
		snd_pcm_period_elapsed(chip->capture_substream);
	पूर्ण
	अगर (chip->rmidi && (status & FM801_IRQ_MPU))
		snd_mpu401_uart_पूर्णांकerrupt(irq, chip->rmidi->निजी_data);
	अगर (status & FM801_IRQ_VOLUME) अणु
		/* TODO */
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware snd_fm801_playback =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_PAUSE | SNDRV_PCM_INFO_RESUME |
				 SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =		SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_KNOT | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		5500,
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

अटल स्थिर काष्ठा snd_pcm_hardware snd_fm801_capture =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_PAUSE | SNDRV_PCM_INFO_RESUME |
				 SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =		SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_KNOT | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		5500,
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

अटल पूर्णांक snd_fm801_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा fm801 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;

	chip->playback_substream = substream;
	runसमय->hw = snd_fm801_playback;
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				   &hw_स्थिरraपूर्णांकs_rates);
	अगर (chip->multichannel) अणु
		runसमय->hw.channels_max = 6;
		snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0,
					   SNDRV_PCM_HW_PARAM_CHANNELS,
					   &hw_स्थिरraपूर्णांकs_channels);
	पूर्ण
	अगर ((err = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय, SNDRV_PCM_HW_PARAM_PERIODS)) < 0)
		वापस err;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_fm801_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा fm801 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;

	chip->capture_substream = substream;
	runसमय->hw = snd_fm801_capture;
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				   &hw_स्थिरraपूर्णांकs_rates);
	अगर ((err = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय, SNDRV_PCM_HW_PARAM_PERIODS)) < 0)
		वापस err;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_fm801_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा fm801 *chip = snd_pcm_substream_chip(substream);

	chip->playback_substream = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_fm801_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा fm801 *chip = snd_pcm_substream_chip(substream);

	chip->capture_substream = शून्य;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_fm801_playback_ops = अणु
	.खोलो =		snd_fm801_playback_खोलो,
	.बंद =	snd_fm801_playback_बंद,
	.prepare =	snd_fm801_playback_prepare,
	.trigger =	snd_fm801_playback_trigger,
	.poपूर्णांकer =	snd_fm801_playback_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_fm801_capture_ops = अणु
	.खोलो =		snd_fm801_capture_खोलो,
	.बंद =	snd_fm801_capture_बंद,
	.prepare =	snd_fm801_capture_prepare,
	.trigger =	snd_fm801_capture_trigger,
	.poपूर्णांकer =	snd_fm801_capture_poपूर्णांकer,
पूर्ण;

अटल पूर्णांक snd_fm801_pcm(काष्ठा fm801 *chip, पूर्णांक device)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(chip->dev);
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	अगर ((err = snd_pcm_new(chip->card, "FM801", device, 1, 1, &pcm)) < 0)
		वापस err;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_fm801_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_fm801_capture_ops);

	pcm->निजी_data = chip;
	pcm->info_flags = 0;
	म_नकल(pcm->name, "FM801");
	chip->pcm = pcm;

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV, &pdev->dev,
				       chip->multichannel ? 128*1024 : 64*1024, 128*1024);

	वापस snd_pcm_add_chmap_ctls(pcm, SNDRV_PCM_STREAM_PLAYBACK,
				     snd_pcm_alt_chmaps,
				     chip->multichannel ? 6 : 2, 0,
				     शून्य);
पूर्ण

/*
 *  TEA5757 radio
 */

#अगर_घोषित CONFIG_SND_FM801_TEA575X_BOOL

/* GPIO to TEA575x maps */
काष्ठा snd_fm801_tea575x_gpio अणु
	u8 data, clk, wren, most;
	अक्षर *name;
पूर्ण;

अटल स्थिर काष्ठा snd_fm801_tea575x_gpio snd_fm801_tea575x_gpios[] = अणु
	अणु .data = 1, .clk = 3, .wren = 2, .most = 0, .name = "SF256-PCS" पूर्ण,
	अणु .data = 1, .clk = 0, .wren = 2, .most = 3, .name = "SF256-PCP" पूर्ण,
	अणु .data = 2, .clk = 0, .wren = 1, .most = 3, .name = "SF64-PCR" पूर्ण,
पूर्ण;

#घोषणा get_tea575x_gpio(chip) \
	(&snd_fm801_tea575x_gpios[((chip)->tea575x_tuner & TUNER_TYPE_MASK) - 1])

अटल व्योम snd_fm801_tea575x_set_pins(काष्ठा snd_tea575x *tea, u8 pins)
अणु
	काष्ठा fm801 *chip = tea->निजी_data;
	अचिन्हित लघु reg = fm801_पढ़ोw(chip, GPIO_CTRL);
	काष्ठा snd_fm801_tea575x_gpio gpio = *get_tea575x_gpio(chip);

	reg &= ~(FM801_GPIO_GP(gpio.data) |
		 FM801_GPIO_GP(gpio.clk) |
		 FM801_GPIO_GP(gpio.wren));

	reg |= (pins & TEA575X_DATA) ? FM801_GPIO_GP(gpio.data) : 0;
	reg |= (pins & TEA575X_CLK)  ? FM801_GPIO_GP(gpio.clk) : 0;
	/* WRITE_ENABLE is inverted */
	reg |= (pins & TEA575X_WREN) ? 0 : FM801_GPIO_GP(gpio.wren);

	fm801_ग_लिखोw(chip, GPIO_CTRL, reg);
पूर्ण

अटल u8 snd_fm801_tea575x_get_pins(काष्ठा snd_tea575x *tea)
अणु
	काष्ठा fm801 *chip = tea->निजी_data;
	अचिन्हित लघु reg = fm801_पढ़ोw(chip, GPIO_CTRL);
	काष्ठा snd_fm801_tea575x_gpio gpio = *get_tea575x_gpio(chip);
	u8 ret;

	ret = 0;
	अगर (reg & FM801_GPIO_GP(gpio.data))
		ret |= TEA575X_DATA;
	अगर (reg & FM801_GPIO_GP(gpio.most))
		ret |= TEA575X_MOST;
	वापस ret;
पूर्ण

अटल व्योम snd_fm801_tea575x_set_direction(काष्ठा snd_tea575x *tea, bool output)
अणु
	काष्ठा fm801 *chip = tea->निजी_data;
	अचिन्हित लघु reg = fm801_पढ़ोw(chip, GPIO_CTRL);
	काष्ठा snd_fm801_tea575x_gpio gpio = *get_tea575x_gpio(chip);

	/* use GPIO lines and set ग_लिखो enable bit */
	reg |= FM801_GPIO_GS(gpio.data) |
	       FM801_GPIO_GS(gpio.wren) |
	       FM801_GPIO_GS(gpio.clk) |
	       FM801_GPIO_GS(gpio.most);
	अगर (output) अणु
		/* all of lines are in the ग_लिखो direction */
		/* clear data and घड़ी lines */
		reg &= ~(FM801_GPIO_GD(gpio.data) |
			 FM801_GPIO_GD(gpio.wren) |
			 FM801_GPIO_GD(gpio.clk) |
			 FM801_GPIO_GP(gpio.data) |
			 FM801_GPIO_GP(gpio.clk) |
			 FM801_GPIO_GP(gpio.wren));
	पूर्ण अन्यथा अणु
		/* use GPIO lines, set data direction to input */
		reg |= FM801_GPIO_GD(gpio.data) |
		       FM801_GPIO_GD(gpio.most) |
		       FM801_GPIO_GP(gpio.data) |
		       FM801_GPIO_GP(gpio.most) |
		       FM801_GPIO_GP(gpio.wren);
		/* all of lines are in the ग_लिखो direction, except data */
		/* clear data, ग_लिखो enable and घड़ी lines */
		reg &= ~(FM801_GPIO_GD(gpio.wren) |
			 FM801_GPIO_GD(gpio.clk) |
			 FM801_GPIO_GP(gpio.clk));
	पूर्ण

	fm801_ग_लिखोw(chip, GPIO_CTRL, reg);
पूर्ण

अटल स्थिर काष्ठा snd_tea575x_ops snd_fm801_tea_ops = अणु
	.set_pins = snd_fm801_tea575x_set_pins,
	.get_pins = snd_fm801_tea575x_get_pins,
	.set_direction = snd_fm801_tea575x_set_direction,
पूर्ण;
#पूर्ण_अगर

/*
 *  Mixer routines
 */

#घोषणा FM801_SINGLE(xname, reg, shअगरt, mask, invert) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .info = snd_fm801_info_single, \
  .get = snd_fm801_get_single, .put = snd_fm801_put_single, \
  .निजी_value = reg | (shअगरt << 8) | (mask << 16) | (invert << 24) पूर्ण

अटल पूर्णांक snd_fm801_info_single(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;

	uinfo->type = mask == 1 ? SNDRV_CTL_ELEM_TYPE_BOOLEAN : SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = mask;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_fm801_get_single(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा fm801 *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 24) & 0xff;
	दीर्घ *value = ucontrol->value.पूर्णांकeger.value;

	value[0] = (fm801_ioपढ़ो16(chip, reg) >> shअगरt) & mask;
	अगर (invert)
		value[0] = mask - value[0];
	वापस 0;
पूर्ण

अटल पूर्णांक snd_fm801_put_single(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा fm801 *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 24) & 0xff;
	अचिन्हित लघु val;

	val = (ucontrol->value.पूर्णांकeger.value[0] & mask);
	अगर (invert)
		val = mask - val;
	वापस snd_fm801_update_bits(chip, reg, mask << shअगरt, val << shअगरt);
पूर्ण

#घोषणा FM801_DOUBLE(xname, reg, shअगरt_left, shअगरt_right, mask, invert) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .info = snd_fm801_info_द्विगुन, \
  .get = snd_fm801_get_द्विगुन, .put = snd_fm801_put_द्विगुन, \
  .निजी_value = reg | (shअगरt_left << 8) | (shअगरt_right << 12) | (mask << 16) | (invert << 24) पूर्ण
#घोषणा FM801_DOUBLE_TLV(xname, reg, shअगरt_left, shअगरt_right, mask, invert, xtlv) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
  .access = SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_TLV_READ, \
  .name = xname, .info = snd_fm801_info_द्विगुन, \
  .get = snd_fm801_get_द्विगुन, .put = snd_fm801_put_द्विगुन, \
  .निजी_value = reg | (shअगरt_left << 8) | (shअगरt_right << 12) | (mask << 16) | (invert << 24), \
  .tlv = अणु .p = (xtlv) पूर्ण पूर्ण

अटल पूर्णांक snd_fm801_info_द्विगुन(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;

	uinfo->type = mask == 1 ? SNDRV_CTL_ELEM_TYPE_BOOLEAN : SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = mask;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_fm801_get_द्विगुन(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा fm801 *chip = snd_kcontrol_chip(kcontrol);
        पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt_left = (kcontrol->निजी_value >> 8) & 0x0f;
	पूर्णांक shअगरt_right = (kcontrol->निजी_value >> 12) & 0x0f;
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 24) & 0xff;
	दीर्घ *value = ucontrol->value.पूर्णांकeger.value;

	spin_lock_irq(&chip->reg_lock);
	value[0] = (fm801_ioपढ़ो16(chip, reg) >> shअगरt_left) & mask;
	value[1] = (fm801_ioपढ़ो16(chip, reg) >> shअगरt_right) & mask;
	spin_unlock_irq(&chip->reg_lock);
	अगर (invert) अणु
		value[0] = mask - value[0];
		value[1] = mask - value[1];
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_fm801_put_द्विगुन(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा fm801 *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt_left = (kcontrol->निजी_value >> 8) & 0x0f;
	पूर्णांक shअगरt_right = (kcontrol->निजी_value >> 12) & 0x0f;
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 24) & 0xff;
	अचिन्हित लघु val1, val2;
 
	val1 = ucontrol->value.पूर्णांकeger.value[0] & mask;
	val2 = ucontrol->value.पूर्णांकeger.value[1] & mask;
	अगर (invert) अणु
		val1 = mask - val1;
		val2 = mask - val2;
	पूर्ण
	वापस snd_fm801_update_bits(chip, reg,
				     (mask << shअगरt_left) | (mask << shअगरt_right),
				     (val1 << shअगरt_left ) | (val2 << shअगरt_right));
पूर्ण

अटल पूर्णांक snd_fm801_info_mux(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[5] = अणु
		"AC97 Primary", "FM", "I2S", "PCM", "AC97 Secondary"
	पूर्ण;
 
	वापस snd_ctl_क्रमागत_info(uinfo, 1, 5, texts);
पूर्ण

अटल पूर्णांक snd_fm801_get_mux(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा fm801 *chip = snd_kcontrol_chip(kcontrol);
        अचिन्हित लघु val;
 
	val = fm801_पढ़ोw(chip, REC_SRC) & 7;
	अगर (val > 4)
		val = 4;
        ucontrol->value.क्रमागतerated.item[0] = val;
        वापस 0;
पूर्ण

अटल पूर्णांक snd_fm801_put_mux(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा fm801 *chip = snd_kcontrol_chip(kcontrol);
        अचिन्हित लघु val;
 
        अगर ((val = ucontrol->value.क्रमागतerated.item[0]) > 4)
                वापस -EINVAL;
	वापस snd_fm801_update_bits(chip, FM801_REC_SRC, 7, val);
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_dsp, -3450, 150, 0);

#घोषणा FM801_CONTROLS ARRAY_SIZE(snd_fm801_controls)

अटल स्थिर काष्ठा snd_kcontrol_new snd_fm801_controls[] = अणु
FM801_DOUBLE_TLV("Wave Playback Volume", FM801_PCM_VOL, 0, 8, 31, 1,
		 db_scale_dsp),
FM801_SINGLE("Wave Playback Switch", FM801_PCM_VOL, 15, 1, 1),
FM801_DOUBLE_TLV("I2S Playback Volume", FM801_I2S_VOL, 0, 8, 31, 1,
		 db_scale_dsp),
FM801_SINGLE("I2S Playback Switch", FM801_I2S_VOL, 15, 1, 1),
FM801_DOUBLE_TLV("FM Playback Volume", FM801_FM_VOL, 0, 8, 31, 1,
		 db_scale_dsp),
FM801_SINGLE("FM Playback Switch", FM801_FM_VOL, 15, 1, 1),
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Digital Capture Source",
	.info = snd_fm801_info_mux,
	.get = snd_fm801_get_mux,
	.put = snd_fm801_put_mux,
पूर्ण
पूर्ण;

#घोषणा FM801_CONTROLS_MULTI ARRAY_SIZE(snd_fm801_controls_multi)

अटल स्थिर काष्ठा snd_kcontrol_new snd_fm801_controls_multi[] = अणु
FM801_SINGLE("AC97 2ch->4ch Copy Switch", FM801_CODEC_CTRL, 7, 1, 0),
FM801_SINGLE("AC97 18-bit Switch", FM801_CODEC_CTRL, 10, 1, 0),
FM801_SINGLE(SNDRV_CTL_NAME_IEC958("",CAPTURE,SWITCH), FM801_I2S_MODE, 8, 1, 0),
FM801_SINGLE(SNDRV_CTL_NAME_IEC958("Raw Data ",PLAYBACK,SWITCH), FM801_I2S_MODE, 9, 1, 0),
FM801_SINGLE(SNDRV_CTL_NAME_IEC958("Raw Data ",CAPTURE,SWITCH), FM801_I2S_MODE, 10, 1, 0),
FM801_SINGLE(SNDRV_CTL_NAME_IEC958("",PLAYBACK,SWITCH), FM801_GEN_CTRL, 2, 1, 0),
पूर्ण;

अटल व्योम snd_fm801_mixer_मुक्त_ac97_bus(काष्ठा snd_ac97_bus *bus)
अणु
	काष्ठा fm801 *chip = bus->निजी_data;
	chip->ac97_bus = शून्य;
पूर्ण

अटल व्योम snd_fm801_mixer_मुक्त_ac97(काष्ठा snd_ac97 *ac97)
अणु
	काष्ठा fm801 *chip = ac97->निजी_data;
	अगर (ac97->num == 0) अणु
		chip->ac97 = शून्य;
	पूर्ण अन्यथा अणु
		chip->ac97_sec = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक snd_fm801_mixer(काष्ठा fm801 *chip)
अणु
	काष्ठा snd_ac97_ढाँचा ac97;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_ac97_bus_ops ops = अणु
		.ग_लिखो = snd_fm801_codec_ग_लिखो,
		.पढ़ो = snd_fm801_codec_पढ़ो,
	पूर्ण;

	अगर ((err = snd_ac97_bus(chip->card, 0, &ops, chip, &chip->ac97_bus)) < 0)
		वापस err;
	chip->ac97_bus->निजी_मुक्त = snd_fm801_mixer_मुक्त_ac97_bus;

	स_रखो(&ac97, 0, माप(ac97));
	ac97.निजी_data = chip;
	ac97.निजी_मुक्त = snd_fm801_mixer_मुक्त_ac97;
	अगर ((err = snd_ac97_mixer(chip->ac97_bus, &ac97, &chip->ac97)) < 0)
		वापस err;
	अगर (chip->secondary) अणु
		ac97.num = 1;
		ac97.addr = chip->secondary_addr;
		अगर ((err = snd_ac97_mixer(chip->ac97_bus, &ac97, &chip->ac97_sec)) < 0)
			वापस err;
	पूर्ण
	क्रम (i = 0; i < FM801_CONTROLS; i++) अणु
		err = snd_ctl_add(chip->card,
			snd_ctl_new1(&snd_fm801_controls[i], chip));
		अगर (err < 0)
			वापस err;
	पूर्ण
	अगर (chip->multichannel) अणु
		क्रम (i = 0; i < FM801_CONTROLS_MULTI; i++) अणु
			err = snd_ctl_add(chip->card,
				snd_ctl_new1(&snd_fm801_controls_multi[i], chip));
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 *  initialization routines
 */

अटल पूर्णांक रुको_क्रम_codec(काष्ठा fm801 *chip, अचिन्हित पूर्णांक codec_id,
			  अचिन्हित लघु reg, अचिन्हित दीर्घ रुकोs)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + रुकोs;

	fm801_ग_लिखोw(chip, AC97_CMD,
		     reg | (codec_id << FM801_AC97_ADDR_SHIFT) | FM801_AC97_READ);
	udelay(5);
	करो अणु
		अगर ((fm801_पढ़ोw(chip, AC97_CMD) &
		     (FM801_AC97_VALID | FM801_AC97_BUSY)) == FM801_AC97_VALID)
			वापस 0;
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण जबतक (समय_after(समयout, jअगरfies));
	वापस -EIO;
पूर्ण

अटल पूर्णांक reset_codec(काष्ठा fm801 *chip)
अणु
	/* codec cold reset + AC'97 warm reset */
	fm801_ग_लिखोw(chip, CODEC_CTRL, (1 << 5) | (1 << 6));
	fm801_पढ़ोw(chip, CODEC_CTRL); /* flush posting data */
	udelay(100);
	fm801_ग_लिखोw(chip, CODEC_CTRL, 0);

	वापस रुको_क्रम_codec(chip, 0, AC97_RESET, msecs_to_jअगरfies(750));
पूर्ण

अटल व्योम snd_fm801_chip_multichannel_init(काष्ठा fm801 *chip)
अणु
	अचिन्हित लघु cmdw;

	अगर (chip->multichannel) अणु
		अगर (chip->secondary_addr) अणु
			रुको_क्रम_codec(chip, chip->secondary_addr,
				       AC97_VENDOR_ID1, msecs_to_jअगरfies(50));
		पूर्ण अन्यथा अणु
			/* my card has the secondary codec */
			/* at address #3, so the loop is inverted */
			पूर्णांक i;
			क्रम (i = 3; i > 0; i--) अणु
				अगर (!रुको_क्रम_codec(chip, i, AC97_VENDOR_ID1,
						     msecs_to_jअगरfies(50))) अणु
					cmdw = fm801_पढ़ोw(chip, AC97_DATA);
					अगर (cmdw != 0xffff && cmdw != 0) अणु
						chip->secondary = 1;
						chip->secondary_addr = i;
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण

		/* the recovery phase, it seems that probing क्रम non-existing codec might */
		/* cause समयout problems */
		रुको_क्रम_codec(chip, 0, AC97_VENDOR_ID1, msecs_to_jअगरfies(750));
	पूर्ण
पूर्ण

अटल व्योम snd_fm801_chip_init(काष्ठा fm801 *chip)
अणु
	अचिन्हित लघु cmdw;

	/* init volume */
	fm801_ग_लिखोw(chip, PCM_VOL, 0x0808);
	fm801_ग_लिखोw(chip, FM_VOL, 0x9f1f);
	fm801_ग_लिखोw(chip, I2S_VOL, 0x8808);

	/* I2S control - I2S mode */
	fm801_ग_लिखोw(chip, I2S_MODE, 0x0003);

	/* पूर्णांकerrupt setup */
	cmdw = fm801_पढ़ोw(chip, IRQ_MASK);
	अगर (chip->irq < 0)
		cmdw |= 0x00c3;		/* mask everything, no PCM nor MPU */
	अन्यथा
		cmdw &= ~0x0083;	/* unmask MPU, PLAYBACK & CAPTURE */
	fm801_ग_लिखोw(chip, IRQ_MASK, cmdw);

	/* पूर्णांकerrupt clear */
	fm801_ग_लिखोw(chip, IRQ_STATUS,
		     FM801_IRQ_PLAYBACK | FM801_IRQ_CAPTURE | FM801_IRQ_MPU);
पूर्ण

अटल पूर्णांक snd_fm801_मुक्त(काष्ठा fm801 *chip)
अणु
	अचिन्हित लघु cmdw;

	अगर (chip->irq < 0)
		जाओ __end_hw;

	/* पूर्णांकerrupt setup - mask everything */
	cmdw = fm801_पढ़ोw(chip, IRQ_MASK);
	cmdw |= 0x00c3;
	fm801_ग_लिखोw(chip, IRQ_MASK, cmdw);

	devm_मुक्त_irq(chip->dev, chip->irq, chip);

      __end_hw:
#अगर_घोषित CONFIG_SND_FM801_TEA575X_BOOL
	अगर (!(chip->tea575x_tuner & TUNER_DISABLED)) अणु
		snd_tea575x_निकास(&chip->tea);
		v4l2_device_unरेजिस्टर(&chip->v4l2_dev);
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक snd_fm801_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा fm801 *chip = device->device_data;
	वापस snd_fm801_मुक्त(chip);
पूर्ण

अटल पूर्णांक snd_fm801_create(काष्ठा snd_card *card,
			    काष्ठा pci_dev *pci,
			    पूर्णांक tea575x_tuner,
			    पूर्णांक radio_nr,
			    काष्ठा fm801 **rchip)
अणु
	काष्ठा fm801 *chip;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =	snd_fm801_dev_मुक्त,
	पूर्ण;

	*rchip = शून्य;
	अगर ((err = pcim_enable_device(pci)) < 0)
		वापस err;
	chip = devm_kzalloc(&pci->dev, माप(*chip), GFP_KERNEL);
	अगर (chip == शून्य)
		वापस -ENOMEM;
	spin_lock_init(&chip->reg_lock);
	chip->card = card;
	chip->dev = &pci->dev;
	chip->irq = -1;
	chip->tea575x_tuner = tea575x_tuner;
	अगर ((err = pci_request_regions(pci, "FM801")) < 0)
		वापस err;
	chip->port = pci_resource_start(pci, 0);

	अगर (pci->revision >= 0xb1)	/* FM801-AU */
		chip->multichannel = 1;

	अगर (!(chip->tea575x_tuner & TUNER_ONLY)) अणु
		अगर (reset_codec(chip) < 0) अणु
			dev_info(chip->card->dev,
				 "Primary AC'97 codec not found, assume SF64-PCR (tuner-only)\n");
			chip->tea575x_tuner = 3 | TUNER_ONLY;
		पूर्ण अन्यथा अणु
			snd_fm801_chip_multichannel_init(chip);
		पूर्ण
	पूर्ण

	अगर ((chip->tea575x_tuner & TUNER_ONLY) == 0) अणु
		अगर (devm_request_irq(&pci->dev, pci->irq, snd_fm801_पूर्णांकerrupt,
				IRQF_SHARED, KBUILD_MODNAME, chip)) अणु
			dev_err(card->dev, "unable to grab IRQ %d\n", pci->irq);
			snd_fm801_मुक्त(chip);
			वापस -EBUSY;
		पूर्ण
		chip->irq = pci->irq;
		card->sync_irq = chip->irq;
		pci_set_master(pci);
	पूर्ण

	snd_fm801_chip_init(chip);

	अगर ((err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops)) < 0) अणु
		snd_fm801_मुक्त(chip);
		वापस err;
	पूर्ण

#अगर_घोषित CONFIG_SND_FM801_TEA575X_BOOL
	err = v4l2_device_रेजिस्टर(&pci->dev, &chip->v4l2_dev);
	अगर (err < 0) अणु
		snd_fm801_मुक्त(chip);
		वापस err;
	पूर्ण
	chip->tea.v4l2_dev = &chip->v4l2_dev;
	chip->tea.radio_nr = radio_nr;
	chip->tea.निजी_data = chip;
	chip->tea.ops = &snd_fm801_tea_ops;
	प्र_लिखो(chip->tea.bus_info, "PCI:%s", pci_name(pci));
	अगर ((chip->tea575x_tuner & TUNER_TYPE_MASK) > 0 &&
	    (chip->tea575x_tuner & TUNER_TYPE_MASK) < 4) अणु
		अगर (snd_tea575x_init(&chip->tea, THIS_MODULE)) अणु
			dev_err(card->dev, "TEA575x radio not found\n");
			snd_fm801_मुक्त(chip);
			वापस -ENODEV;
		पूर्ण
	पूर्ण अन्यथा अगर ((chip->tea575x_tuner & TUNER_TYPE_MASK) == 0) अणु
		अचिन्हित पूर्णांक tuner_only = chip->tea575x_tuner & TUNER_ONLY;

		/* स्वतःdetect tuner connection */
		क्रम (tea575x_tuner = 1; tea575x_tuner <= 3; tea575x_tuner++) अणु
			chip->tea575x_tuner = tea575x_tuner;
			अगर (!snd_tea575x_init(&chip->tea, THIS_MODULE)) अणु
				dev_info(card->dev,
					 "detected TEA575x radio type %s\n",
					   get_tea575x_gpio(chip)->name);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (tea575x_tuner == 4) अणु
			dev_err(card->dev, "TEA575x radio not found\n");
			chip->tea575x_tuner = TUNER_DISABLED;
		पूर्ण

		chip->tea575x_tuner |= tuner_only;
	पूर्ण
	अगर (!(chip->tea575x_tuner & TUNER_DISABLED)) अणु
		strscpy(chip->tea.card, get_tea575x_gpio(chip)->name,
			माप(chip->tea.card));
	पूर्ण
#पूर्ण_अगर

	*rchip = chip;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_card_fm801_probe(काष्ठा pci_dev *pci,
				स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_card *card;
	काष्ठा fm801 *chip;
	काष्ठा snd_opl3 *opl3;
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
	अगर ((err = snd_fm801_create(card, pci, tea575x_tuner[dev], radio_nr[dev], &chip)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	card->निजी_data = chip;

	म_नकल(card->driver, "FM801");
	म_नकल(card->लघुname, "ForteMedia FM801-");
	म_जोड़ो(card->लघुname, chip->multichannel ? "AU" : "AS");
	प्र_लिखो(card->दीर्घname, "%s at 0x%lx, irq %i",
		card->लघुname, chip->port, chip->irq);

	अगर (chip->tea575x_tuner & TUNER_ONLY)
		जाओ __fm801_tuner_only;

	अगर ((err = snd_fm801_pcm(chip, 0)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	अगर ((err = snd_fm801_mixer(chip)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	अगर ((err = snd_mpu401_uart_new(card, 0, MPU401_HW_FM801,
				       chip->port + FM801_MPU401_DATA,
				       MPU401_INFO_INTEGRATED |
				       MPU401_INFO_IRQ_HOOK,
				       -1, &chip->rmidi)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	अगर ((err = snd_opl3_create(card, chip->port + FM801_OPL3_BANK0,
				   chip->port + FM801_OPL3_BANK1,
				   OPL3_HW_OPL3_FM801, 1, &opl3)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	अगर ((err = snd_opl3_hwdep_new(opl3, 0, 1, शून्य)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

      __fm801_tuner_only:
	अगर ((err = snd_card_रेजिस्टर(card)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	pci_set_drvdata(pci, card);
	dev++;
	वापस 0;
पूर्ण

अटल व्योम snd_card_fm801_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल स्थिर अचिन्हित अक्षर saved_regs[] = अणु
	FM801_PCM_VOL, FM801_I2S_VOL, FM801_FM_VOL, FM801_REC_SRC,
	FM801_PLY_CTRL, FM801_PLY_COUNT, FM801_PLY_BUF1, FM801_PLY_BUF2,
	FM801_CAP_CTRL, FM801_CAP_COUNT, FM801_CAP_BUF1, FM801_CAP_BUF2,
	FM801_CODEC_CTRL, FM801_I2S_MODE, FM801_VOLUME, FM801_GEN_CTRL,
पूर्ण;

अटल पूर्णांक snd_fm801_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा fm801 *chip = card->निजी_data;
	पूर्णांक i;

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);

	क्रम (i = 0; i < ARRAY_SIZE(saved_regs); i++)
		chip->saved_regs[i] = fm801_ioपढ़ो16(chip, saved_regs[i]);

	अगर (chip->tea575x_tuner & TUNER_ONLY) अणु
		/* FIXME: tea575x suspend */
	पूर्ण अन्यथा अणु
		snd_ac97_suspend(chip->ac97);
		snd_ac97_suspend(chip->ac97_sec);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_fm801_resume(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा fm801 *chip = card->निजी_data;
	पूर्णांक i;

	अगर (chip->tea575x_tuner & TUNER_ONLY) अणु
		snd_fm801_chip_init(chip);
	पूर्ण अन्यथा अणु
		reset_codec(chip);
		snd_fm801_chip_multichannel_init(chip);
		snd_fm801_chip_init(chip);
		snd_ac97_resume(chip->ac97);
		snd_ac97_resume(chip->ac97_sec);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(saved_regs); i++)
		fm801_ioग_लिखो16(chip, saved_regs[i], chip->saved_regs[i]);

#अगर_घोषित CONFIG_SND_FM801_TEA575X_BOOL
	अगर (!(chip->tea575x_tuner & TUNER_DISABLED))
		snd_tea575x_set_freq(&chip->tea);
#पूर्ण_अगर

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(snd_fm801_pm, snd_fm801_suspend, snd_fm801_resume);
#घोषणा SND_FM801_PM_OPS	&snd_fm801_pm
#अन्यथा
#घोषणा SND_FM801_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल काष्ठा pci_driver fm801_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_fm801_ids,
	.probe = snd_card_fm801_probe,
	.हटाओ = snd_card_fm801_हटाओ,
	.driver = अणु
		.pm = SND_FM801_PM_OPS,
	पूर्ण,
पूर्ण;

module_pci_driver(fm801_driver);
