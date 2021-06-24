<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  card-als4000.c - driver क्रम Avance Logic ALS4000 based soundcards.
 *  Copyright (C) 2000 by Bart Hartgers <bart@etpmod.phys.tue.nl>,
 *			  Jaroslav Kysela <perex@perex.cz>
 *  Copyright (C) 2002, 2008 by Andreas Mohr <hw7oshyuv3001@sneakemail.com>
 *
 *  Framework borrowed from Massimo Piccioni's card-als100.c.
 *
 * NOTES
 *
 *  Since Avance करोes not provide any meaningful करोcumentation, and I
 *  bought an ALS4000 based soundcard, I was क्रमced to base this driver
 *  on reverse engineering.
 *
 *  Note: this is no दीर्घer true (thank you!):
 *  pretty verbose chip करोcu (ALS4000a.PDF) can be found on the ALSA web site.
 *  Page numbers stated anywhere below with the "SPECS_PAGE:" tag
 *  refer to: ALS4000a.PDF specs Ver 1.0, May 28th, 1998.
 *
 *  The ALS4000 seems to be the PCI-cousin of the ALS100. It contains an
 *  ALS100-like SB DSP/mixer, an OPL3 synth, a MPU401 and a gameport 
 *  पूर्णांकerface. These subप्रणालीs can be mapped पूर्णांकo ISA io-port space, 
 *  using the PCI-पूर्णांकerface. In addition, the PCI-bit provides DMA and IRQ 
 *  services to the subप्रणालीs.
 * 
 * While ALS4000 is very similar to a SoundBlaster, the dअगरferences in
 * DMA and capturing require more changes to the SoundBlaster than
 * desirable, so I made this separate driver.
 * 
 * The ALS4000 can करो real full duplex playback/capture.
 *
 * FMDAC:
 * - 0x4f -> port 0x14
 * - port 0x15 |= 1
 *
 * Enable/disable 3D sound:
 * - 0x50 -> port 0x14
 * - change bit 6 (0x40) of port 0x15
 *
 * Set QSound:
 * - 0xdb -> port 0x14
 * - set port 0x15:
 *   0x3e (mode 3), 0x3c (mode 2), 0x3a (mode 1), 0x38 (mode 0)
 *
 * Set KSound:
 * - value -> some port 0x0c0d
 *
 * ToDo:
 * - by शेष, करोn't enable legacy game and use PCI game I/O
 * - घातer management? (card can करो voice wakeup according to datasheet!!)
 */

#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/gameport.h>
#समावेश <linux/module.h>
#समावेश <linux/dma-mapping.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/rawmidi.h>
#समावेश <sound/mpu401.h>
#समावेश <sound/opl3.h>
#समावेश <sound/sb.h>
#समावेश <sound/initval.h>

MODULE_AUTHOR("Bart Hartgers <bart@etpmod.phys.tue.nl>, Andreas Mohr");
MODULE_DESCRIPTION("Avance Logic ALS4000");
MODULE_LICENSE("GPL");

#अगर IS_REACHABLE(CONFIG_GAMEPORT)
#घोषणा SUPPORT_JOYSTICK 1
#पूर्ण_अगर

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;	/* Enable this card */
#अगर_घोषित SUPPORT_JOYSTICK
अटल पूर्णांक joystick_port[SNDRV_CARDS];
#पूर्ण_अगर

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for ALS4000 soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for ALS4000 soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable ALS4000 soundcard.");
#अगर_घोषित SUPPORT_JOYSTICK
module_param_hw_array(joystick_port, पूर्णांक, ioport, शून्य, 0444);
MODULE_PARM_DESC(joystick_port, "Joystick port address for ALS4000 soundcard. (0 = disabled)");
#पूर्ण_अगर

काष्ठा snd_card_als4000 अणु
	/* most frequent access first */
	अचिन्हित दीर्घ iobase;
	काष्ठा pci_dev *pci;
	काष्ठा snd_sb *chip;
#अगर_घोषित SUPPORT_JOYSTICK
	काष्ठा gameport *gameport;
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा pci_device_id snd_als4000_ids[] = अणु
	अणु 0x4005, 0x4000, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0, पूर्ण,   /* ALS4000 */
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, snd_als4000_ids);

क्रमागत als4k_iobase_t अणु
	/* IOx: B == Byte, W = Word, D = DWord; SPECS_PAGE: 37 */
	ALS4K_IOD_00_AC97_ACCESS = 0x00,
	ALS4K_IOW_04_AC97_READ = 0x04,
	ALS4K_IOB_06_AC97_STATUS = 0x06,
	ALS4K_IOB_07_IRQSTATUS = 0x07,
	ALS4K_IOD_08_GCR_DATA = 0x08,
	ALS4K_IOB_0C_GCR_INDEX = 0x0c,
	ALS4K_IOB_0E_IRQTYPE_SB_CR1E_MPU = 0x0e,
	ALS4K_IOB_10_ADLIB_ADDR0 = 0x10,
	ALS4K_IOB_11_ADLIB_ADDR1 = 0x11,
	ALS4K_IOB_12_ADLIB_ADDR2 = 0x12,
	ALS4K_IOB_13_ADLIB_ADDR3 = 0x13,
	ALS4K_IOB_14_MIXER_INDEX = 0x14,
	ALS4K_IOB_15_MIXER_DATA = 0x15,
	ALS4K_IOB_16_ESP_RESET = 0x16,
	ALS4K_IOB_16_ACK_FOR_CR1E = 0x16, /* 2nd function */
	ALS4K_IOB_18_OPL_ADDR0 = 0x18,
	ALS4K_IOB_19_OPL_ADDR1 = 0x19,
	ALS4K_IOB_1A_ESP_RD_DATA = 0x1a,
	ALS4K_IOB_1C_ESP_CMD_DATA = 0x1c,
	ALS4K_IOB_1C_ESP_WR_STATUS = 0x1c, /* 2nd function */
	ALS4K_IOB_1E_ESP_RD_STATUS8 = 0x1e,
	ALS4K_IOB_1F_ESP_RD_STATUS16 = 0x1f,
	ALS4K_IOB_20_ESP_GAMEPORT_200 = 0x20,
	ALS4K_IOB_21_ESP_GAMEPORT_201 = 0x21,
	ALS4K_IOB_30_MIDI_DATA = 0x30,
	ALS4K_IOB_31_MIDI_STATUS = 0x31,
	ALS4K_IOB_31_MIDI_COMMAND = 0x31, /* 2nd function */
पूर्ण;

क्रमागत als4k_iobase_0e_t अणु
	ALS4K_IOB_0E_MPU_IRQ = 0x10,
	ALS4K_IOB_0E_CR1E_IRQ = 0x40,
	ALS4K_IOB_0E_SB_DMA_IRQ = 0x80,
पूर्ण;

क्रमागत als4k_gcr_t अणु /* all रेजिस्टरs 32bit wide; SPECS_PAGE: 38 to 42 */
	ALS4K_GCR8C_MISC_CTRL = 0x8c,
	ALS4K_GCR90_TEST_MODE_REG = 0x90,
	ALS4K_GCR91_DMA0_ADDR = 0x91,
	ALS4K_GCR92_DMA0_MODE_COUNT = 0x92,
	ALS4K_GCR93_DMA1_ADDR = 0x93,
	ALS4K_GCR94_DMA1_MODE_COUNT = 0x94,
	ALS4K_GCR95_DMA3_ADDR = 0x95,
	ALS4K_GCR96_DMA3_MODE_COUNT = 0x96,
	ALS4K_GCR99_DMA_EMULATION_CTRL = 0x99,
	ALS4K_GCRA0_FIFO1_CURRENT_ADDR = 0xa0,
	ALS4K_GCRA1_FIFO1_STATUS_BYTECOUNT = 0xa1,
	ALS4K_GCRA2_FIFO2_PCIADDR = 0xa2,
	ALS4K_GCRA3_FIFO2_COUNT = 0xa3,
	ALS4K_GCRA4_FIFO2_CURRENT_ADDR = 0xa4,
	ALS4K_GCRA5_FIFO1_STATUS_BYTECOUNT = 0xa5,
	ALS4K_GCRA6_PM_CTRL = 0xa6,
	ALS4K_GCRA7_PCI_ACCESS_STORAGE = 0xa7,
	ALS4K_GCRA8_LEGACY_CFG1 = 0xa8,
	ALS4K_GCRA9_LEGACY_CFG2 = 0xa9,
	ALS4K_GCRFF_DUMMY_SCRATCH = 0xff,
पूर्ण;

क्रमागत als4k_gcr8c_t अणु
	ALS4K_GCR8C_IRQ_MASK_CTRL_ENABLE = 0x8000,
	ALS4K_GCR8C_CHIP_REV_MASK = 0xf0000
पूर्ण;

अटल अंतरभूत व्योम snd_als4k_iobase_ग_लिखोb(अचिन्हित दीर्घ iobase,
						क्रमागत als4k_iobase_t reg,
						u8 val)
अणु
	outb(val, iobase + reg);
पूर्ण

अटल अंतरभूत व्योम snd_als4k_iobase_ग_लिखोl(अचिन्हित दीर्घ iobase,
						क्रमागत als4k_iobase_t reg,
						u32 val)
अणु
	outl(val, iobase + reg);
पूर्ण

अटल अंतरभूत u8 snd_als4k_iobase_पढ़ोb(अचिन्हित दीर्घ iobase,
						क्रमागत als4k_iobase_t reg)
अणु
	वापस inb(iobase + reg);
पूर्ण

अटल अंतरभूत u32 snd_als4k_iobase_पढ़ोl(अचिन्हित दीर्घ iobase,
						क्रमागत als4k_iobase_t reg)
अणु
	वापस inl(iobase + reg);
पूर्ण

अटल अंतरभूत व्योम snd_als4k_gcr_ग_लिखो_addr(अचिन्हित दीर्घ iobase,
						 क्रमागत als4k_gcr_t reg,
						 u32 val)
अणु
	snd_als4k_iobase_ग_लिखोb(iobase, ALS4K_IOB_0C_GCR_INDEX, reg);
	snd_als4k_iobase_ग_लिखोl(iobase, ALS4K_IOD_08_GCR_DATA, val);
पूर्ण

अटल अंतरभूत व्योम snd_als4k_gcr_ग_लिखो(काष्ठा snd_sb *sb,
					 क्रमागत als4k_gcr_t reg,
					 u32 val)
अणु
	snd_als4k_gcr_ग_लिखो_addr(sb->alt_port, reg, val);
पूर्ण	

अटल अंतरभूत u32 snd_als4k_gcr_पढ़ो_addr(अचिन्हित दीर्घ iobase,
						 क्रमागत als4k_gcr_t reg)
अणु
	/* SPECS_PAGE: 37/38 */
	snd_als4k_iobase_ग_लिखोb(iobase, ALS4K_IOB_0C_GCR_INDEX, reg);
	वापस snd_als4k_iobase_पढ़ोl(iobase, ALS4K_IOD_08_GCR_DATA);
पूर्ण

अटल अंतरभूत u32 snd_als4k_gcr_पढ़ो(काष्ठा snd_sb *sb, क्रमागत als4k_gcr_t reg)
अणु
	वापस snd_als4k_gcr_पढ़ो_addr(sb->alt_port, reg);
पूर्ण

क्रमागत als4k_cr_t अणु /* all रेजिस्टरs 8bit wide; SPECS_PAGE: 20 to 23 */
	ALS4K_CR0_SB_CONFIG = 0x00,
	ALS4K_CR2_MISC_CONTROL = 0x02,
	ALS4K_CR3_CONFIGURATION = 0x03,
	ALS4K_CR17_FIFO_STATUS = 0x17,
	ALS4K_CR18_ESP_MAJOR_VERSION = 0x18,
	ALS4K_CR19_ESP_MINOR_VERSION = 0x19,
	ALS4K_CR1A_MPU401_UART_MODE_CONTROL = 0x1a,
	ALS4K_CR1C_FIFO2_BLOCK_LENGTH_LO = 0x1c,
	ALS4K_CR1D_FIFO2_BLOCK_LENGTH_HI = 0x1d,
	ALS4K_CR1E_FIFO2_CONTROL = 0x1e, /* secondary PCM FIFO (recording) */
	ALS4K_CR3A_MISC_CONTROL = 0x3a,
	ALS4K_CR3B_CRC32_BYTE0 = 0x3b, /* क्रम testing, activate via CR3A */
	ALS4K_CR3C_CRC32_BYTE1 = 0x3c,
	ALS4K_CR3D_CRC32_BYTE2 = 0x3d,
	ALS4K_CR3E_CRC32_BYTE3 = 0x3e,
पूर्ण;

क्रमागत als4k_cr0_t अणु
	ALS4K_CR0_DMA_CONTIN_MODE_CTRL = 0x02, /* IRQ/FIFO controlled क्रम 0/1 */
	ALS4K_CR0_DMA_90H_MODE_CTRL = 0x04, /* IRQ/FIFO controlled क्रम 0/1 */
	ALS4K_CR0_MX80_81_REG_WRITE_ENABLE = 0x80,
पूर्ण;

अटल अंतरभूत व्योम snd_als4_cr_ग_लिखो(काष्ठा snd_sb *chip,
					क्रमागत als4k_cr_t reg,
					u8 data)
अणु
	/* Control Register is reg | 0xc0 (bit 7, 6 set) on sbmixer_index
	 * NOTE: assumes chip->mixer_lock to be locked बाह्यally alपढ़ोy!
	 * SPECS_PAGE: 6 */
	snd_sbmixer_ग_लिखो(chip, reg | 0xc0, data);
पूर्ण

अटल अंतरभूत u8 snd_als4_cr_पढ़ो(काष्ठा snd_sb *chip,
					क्रमागत als4k_cr_t reg)
अणु
	/* NOTE: assumes chip->mixer_lock to be locked बाह्यally alपढ़ोy! */
	वापस snd_sbmixer_पढ़ो(chip, reg | 0xc0);
पूर्ण



अटल व्योम snd_als4000_set_rate(काष्ठा snd_sb *chip, अचिन्हित पूर्णांक rate)
अणु
	अगर (!(chip->mode & SB_RATE_LOCK)) अणु
		snd_sbdsp_command(chip, SB_DSP_SAMPLE_RATE_OUT);
		snd_sbdsp_command(chip, rate>>8);
		snd_sbdsp_command(chip, rate);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम snd_als4000_set_capture_dma(काष्ठा snd_sb *chip,
					       dma_addr_t addr, अचिन्हित size)
अणु
	/* SPECS_PAGE: 40 */
	snd_als4k_gcr_ग_लिखो(chip, ALS4K_GCRA2_FIFO2_PCIADDR, addr);
	snd_als4k_gcr_ग_लिखो(chip, ALS4K_GCRA3_FIFO2_COUNT, (size-1));
पूर्ण

अटल अंतरभूत व्योम snd_als4000_set_playback_dma(काष्ठा snd_sb *chip,
						dma_addr_t addr,
						अचिन्हित size)
अणु
	/* SPECS_PAGE: 38 */
	snd_als4k_gcr_ग_लिखो(chip, ALS4K_GCR91_DMA0_ADDR, addr);
	snd_als4k_gcr_ग_लिखो(chip, ALS4K_GCR92_DMA0_MODE_COUNT,
							(size-1)|0x180000);
पूर्ण

#घोषणा ALS4000_FORMAT_SIGNED	(1<<0)
#घोषणा ALS4000_FORMAT_16BIT	(1<<1)
#घोषणा ALS4000_FORMAT_STEREO	(1<<2)

अटल पूर्णांक snd_als4000_get_क्रमmat(काष्ठा snd_pcm_runसमय *runसमय)
अणु
	पूर्णांक result;

	result = 0;
	अगर (snd_pcm_क्रमmat_चिन्हित(runसमय->क्रमmat))
		result |= ALS4000_FORMAT_SIGNED;
	अगर (snd_pcm_क्रमmat_physical_width(runसमय->क्रमmat) == 16)
		result |= ALS4000_FORMAT_16BIT;
	अगर (runसमय->channels > 1)
		result |= ALS4000_FORMAT_STEREO;
	वापस result;
पूर्ण

/* काष्ठाure क्रम setting up playback */
अटल स्थिर काष्ठा अणु
	अचिन्हित अक्षर dsp_cmd, dma_on, dma_off, क्रमmat;
पूर्ण playback_cmd_vals[]=अणु
/* ALS4000_FORMAT_U8_MONO */
अणु SB_DSP4_OUT8_AI, SB_DSP_DMA8_ON, SB_DSP_DMA8_OFF, SB_DSP4_MODE_UNS_MONO पूर्ण,
/* ALS4000_FORMAT_S8_MONO */	
अणु SB_DSP4_OUT8_AI, SB_DSP_DMA8_ON, SB_DSP_DMA8_OFF, SB_DSP4_MODE_SIGN_MONO पूर्ण,
/* ALS4000_FORMAT_U16L_MONO */
अणु SB_DSP4_OUT16_AI, SB_DSP_DMA16_ON, SB_DSP_DMA16_OFF, SB_DSP4_MODE_UNS_MONO पूर्ण,
/* ALS4000_FORMAT_S16L_MONO */
अणु SB_DSP4_OUT16_AI, SB_DSP_DMA16_ON, SB_DSP_DMA16_OFF, SB_DSP4_MODE_SIGN_MONO पूर्ण,
/* ALS4000_FORMAT_U8_STEREO */
अणु SB_DSP4_OUT8_AI, SB_DSP_DMA8_ON, SB_DSP_DMA8_OFF, SB_DSP4_MODE_UNS_STEREO पूर्ण,
/* ALS4000_FORMAT_S8_STEREO */	
अणु SB_DSP4_OUT8_AI, SB_DSP_DMA8_ON, SB_DSP_DMA8_OFF, SB_DSP4_MODE_SIGN_STEREO पूर्ण,
/* ALS4000_FORMAT_U16L_STEREO */
अणु SB_DSP4_OUT16_AI, SB_DSP_DMA16_ON, SB_DSP_DMA16_OFF, SB_DSP4_MODE_UNS_STEREO पूर्ण,
/* ALS4000_FORMAT_S16L_STEREO */
अणु SB_DSP4_OUT16_AI, SB_DSP_DMA16_ON, SB_DSP_DMA16_OFF, SB_DSP4_MODE_SIGN_STEREO पूर्ण,
पूर्ण;
#घोषणा playback_cmd(chip) (playback_cmd_vals[(chip)->playback_क्रमmat])

/* काष्ठाure क्रम setting up capture */
क्रमागत अणु CMD_WIDTH8=0x04, CMD_SIGNED=0x10, CMD_MONO=0x80, CMD_STEREO=0xA0 पूर्ण;
अटल स्थिर अचिन्हित अक्षर capture_cmd_vals[]=
अणु
CMD_WIDTH8|CMD_MONO,			/* ALS4000_FORMAT_U8_MONO */
CMD_WIDTH8|CMD_SIGNED|CMD_MONO,		/* ALS4000_FORMAT_S8_MONO */	
CMD_MONO,				/* ALS4000_FORMAT_U16L_MONO */
CMD_SIGNED|CMD_MONO,			/* ALS4000_FORMAT_S16L_MONO */
CMD_WIDTH8|CMD_STEREO,			/* ALS4000_FORMAT_U8_STEREO */
CMD_WIDTH8|CMD_SIGNED|CMD_STEREO,	/* ALS4000_FORMAT_S8_STEREO */	
CMD_STEREO,				/* ALS4000_FORMAT_U16L_STEREO */
CMD_SIGNED|CMD_STEREO,			/* ALS4000_FORMAT_S16L_STEREO */
पूर्ण;	
#घोषणा capture_cmd(chip) (capture_cmd_vals[(chip)->capture_क्रमmat])

अटल पूर्णांक snd_als4000_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_sb *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित दीर्घ size;
	अचिन्हित count;

	chip->capture_क्रमmat = snd_als4000_get_क्रमmat(runसमय);
		
	size = snd_pcm_lib_buffer_bytes(substream);
	count = snd_pcm_lib_period_bytes(substream);
	
	अगर (chip->capture_क्रमmat & ALS4000_FORMAT_16BIT)
		count >>= 1;
	count--;

	spin_lock_irq(&chip->reg_lock);
	snd_als4000_set_rate(chip, runसमय->rate);
	snd_als4000_set_capture_dma(chip, runसमय->dma_addr, size);
	spin_unlock_irq(&chip->reg_lock);
	spin_lock_irq(&chip->mixer_lock);
	snd_als4_cr_ग_लिखो(chip, ALS4K_CR1C_FIFO2_BLOCK_LENGTH_LO, count & 0xff);
	snd_als4_cr_ग_लिखो(chip, ALS4K_CR1D_FIFO2_BLOCK_LENGTH_HI, count >> 8);
	spin_unlock_irq(&chip->mixer_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_als4000_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_sb *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित दीर्घ size;
	अचिन्हित count;

	chip->playback_क्रमmat = snd_als4000_get_क्रमmat(runसमय);
	
	size = snd_pcm_lib_buffer_bytes(substream);
	count = snd_pcm_lib_period_bytes(substream);
	
	अगर (chip->playback_क्रमmat & ALS4000_FORMAT_16BIT)
		count >>= 1;
	count--;
	
	/* FIXME: from second playback on, there's a lot more clicks and pops
	 * involved here than on first playback. Fiddling with
	 * tons of dअगरferent settings didn't help (DMA, speaker on/off,
	 * reordering, ...). Something seems to get enabled on playback
	 * that I haven't found out how to disable again, which then causes
	 * the चयनing pops to reach the speakers the next समय here. */
	spin_lock_irq(&chip->reg_lock);
	snd_als4000_set_rate(chip, runसमय->rate);
	snd_als4000_set_playback_dma(chip, runसमय->dma_addr, size);
	
	/* SPEAKER_ON not needed, since dma_on seems to also enable speaker */
	/* snd_sbdsp_command(chip, SB_DSP_SPEAKER_ON); */
	snd_sbdsp_command(chip, playback_cmd(chip).dsp_cmd);
	snd_sbdsp_command(chip, playback_cmd(chip).क्रमmat);
	snd_sbdsp_command(chip, count & 0xff);
	snd_sbdsp_command(chip, count >> 8);
	snd_sbdsp_command(chip, playback_cmd(chip).dma_off);	
	spin_unlock_irq(&chip->reg_lock);
	
	वापस 0;
पूर्ण

अटल पूर्णांक snd_als4000_capture_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_sb *chip = snd_pcm_substream_chip(substream);
	पूर्णांक result = 0;
	
	/* FIXME race condition in here!!!
	   chip->mode non-atomic update माला_लो consistently रक्षित
	   by reg_lock always, _except_ क्रम this place!!
	   Probably need to take reg_lock as outer (or inner??) lock, too.
	   (or serialize both lock operations? probably not, though... - racy?)
	*/
	spin_lock(&chip->mixer_lock);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		chip->mode |= SB_RATE_LOCK_CAPTURE;
		snd_als4_cr_ग_लिखो(chip, ALS4K_CR1E_FIFO2_CONTROL,
							 capture_cmd(chip));
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		chip->mode &= ~SB_RATE_LOCK_CAPTURE;
		snd_als4_cr_ग_लिखो(chip, ALS4K_CR1E_FIFO2_CONTROL,
							 capture_cmd(chip));
		अवरोध;
	शेष:
		result = -EINVAL;
		अवरोध;
	पूर्ण
	spin_unlock(&chip->mixer_lock);
	वापस result;
पूर्ण

अटल पूर्णांक snd_als4000_playback_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_sb *chip = snd_pcm_substream_chip(substream);
	पूर्णांक result = 0;

	spin_lock(&chip->reg_lock);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		chip->mode |= SB_RATE_LOCK_PLAYBACK;
		snd_sbdsp_command(chip, playback_cmd(chip).dma_on);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		snd_sbdsp_command(chip, playback_cmd(chip).dma_off);
		chip->mode &= ~SB_RATE_LOCK_PLAYBACK;
		अवरोध;
	शेष:
		result = -EINVAL;
		अवरोध;
	पूर्ण
	spin_unlock(&chip->reg_lock);
	वापस result;
पूर्ण

अटल snd_pcm_uframes_t snd_als4000_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_sb *chip = snd_pcm_substream_chip(substream);
	अचिन्हित पूर्णांक result;

	spin_lock(&chip->reg_lock);	
	result = snd_als4k_gcr_पढ़ो(chip, ALS4K_GCRA4_FIFO2_CURRENT_ADDR);
	spin_unlock(&chip->reg_lock);
	result &= 0xffff;
	वापस bytes_to_frames( substream->runसमय, result );
पूर्ण

अटल snd_pcm_uframes_t snd_als4000_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_sb *chip = snd_pcm_substream_chip(substream);
	अचिन्हित result;

	spin_lock(&chip->reg_lock);	
	result = snd_als4k_gcr_पढ़ो(chip, ALS4K_GCRA0_FIFO1_CURRENT_ADDR);
	spin_unlock(&chip->reg_lock);
	result &= 0xffff;
	वापस bytes_to_frames( substream->runसमय, result );
पूर्ण

/* FIXME: this IRQ routine करोesn't really support IRQ sharing (we always
 * वापस IRQ_HANDLED no matter whether we actually had an IRQ flag or not).
 * ALS4000a.PDF ग_लिखोs that जबतक ACKing IRQ in PCI block will *not* ACK
 * the IRQ in the SB core, ACKing IRQ in SB block *will* ACK the PCI IRQ
 * रेजिस्टर (alt_port + ALS4K_IOB_0E_IRQTYPE_SB_CR1E_MPU). Probably something
 * could be optimized here to query/ग_लिखो one रेजिस्टर only...
 * And even अगर both रेजिस्टरs need to be queried, then there's still the
 * question of whether it's actually correct to ACK PCI IRQ beक्रमe पढ़ोing
 * SB IRQ like we करो now, since ALS4000a.PDF mentions that PCI IRQ will *clear*
 * SB IRQ status.
 * (hmm, SPECS_PAGE: 38 mentions it the other way around!)
 * And करो we *really* need the lock here क्रम *पढ़ोing* SB_DSP4_IRQSTATUS??
 * */
अटल irqवापस_t snd_als4000_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा snd_sb *chip = dev_id;
	अचिन्हित pci_irqstatus;
	अचिन्हित sb_irqstatus;

	/* find out which bit of the ALS4000 PCI block produced the पूर्णांकerrupt,
	   SPECS_PAGE: 38, 5 */
	pci_irqstatus = snd_als4k_iobase_पढ़ोb(chip->alt_port,
				 ALS4K_IOB_0E_IRQTYPE_SB_CR1E_MPU);
	अगर ((pci_irqstatus & ALS4K_IOB_0E_SB_DMA_IRQ)
	 && (chip->playback_substream)) /* playback */
		snd_pcm_period_elapsed(chip->playback_substream);
	अगर ((pci_irqstatus & ALS4K_IOB_0E_CR1E_IRQ)
	 && (chip->capture_substream)) /* capturing */
		snd_pcm_period_elapsed(chip->capture_substream);
	अगर ((pci_irqstatus & ALS4K_IOB_0E_MPU_IRQ)
	 && (chip->rmidi)) /* MPU401 पूर्णांकerrupt */
		snd_mpu401_uart_पूर्णांकerrupt(irq, chip->rmidi->निजी_data);
	/* ACK the PCI block IRQ */
	snd_als4k_iobase_ग_लिखोb(chip->alt_port,
			 ALS4K_IOB_0E_IRQTYPE_SB_CR1E_MPU, pci_irqstatus);
	
	spin_lock(&chip->mixer_lock);
	/* SPECS_PAGE: 20 */
	sb_irqstatus = snd_sbmixer_पढ़ो(chip, SB_DSP4_IRQSTATUS);
	spin_unlock(&chip->mixer_lock);
	
	अगर (sb_irqstatus & SB_IRQTYPE_8BIT)
		snd_sb_ack_8bit(chip);
	अगर (sb_irqstatus & SB_IRQTYPE_16BIT)
		snd_sb_ack_16bit(chip);
	अगर (sb_irqstatus & SB_IRQTYPE_MPUIN)
		inb(chip->mpu_port);
	अगर (sb_irqstatus & ALS4K_IRQTYPE_CR1E_DMA)
		snd_als4k_iobase_पढ़ोb(chip->alt_port,
					ALS4K_IOB_16_ACK_FOR_CR1E);

	/* dev_dbg(chip->card->dev, "als4000: irq 0x%04x 0x%04x\n",
					 pci_irqstatus, sb_irqstatus); */

	/* only ack the things we actually handled above */
	वापस IRQ_RETVAL(
	     (pci_irqstatus & (ALS4K_IOB_0E_SB_DMA_IRQ|ALS4K_IOB_0E_CR1E_IRQ|
				ALS4K_IOB_0E_MPU_IRQ))
	  || (sb_irqstatus & (SB_IRQTYPE_8BIT|SB_IRQTYPE_16BIT|
				SB_IRQTYPE_MPUIN|ALS4K_IRQTYPE_CR1E_DMA))
	);
पूर्ण

/*****************************************************************/

अटल स्थिर काष्ठा snd_pcm_hardware snd_als4000_playback =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =		SNDRV_PCM_FMTBIT_S8 | SNDRV_PCM_FMTBIT_U8 |
				SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_U16_LE,	/* क्रमmats */
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
	.fअगरo_size =		0
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_als4000_capture =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =		SNDRV_PCM_FMTBIT_S8 | SNDRV_PCM_FMTBIT_U8 |
				SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_U16_LE,	/* क्रमmats */
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
	.fअगरo_size =		0
पूर्ण;

/*****************************************************************/

अटल पूर्णांक snd_als4000_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_sb *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	chip->playback_substream = substream;
	runसमय->hw = snd_als4000_playback;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_als4000_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_sb *chip = snd_pcm_substream_chip(substream);

	chip->playback_substream = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_als4000_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_sb *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	chip->capture_substream = substream;
	runसमय->hw = snd_als4000_capture;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_als4000_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_sb *chip = snd_pcm_substream_chip(substream);

	chip->capture_substream = शून्य;
	वापस 0;
पूर्ण

/******************************************************************/

अटल स्थिर काष्ठा snd_pcm_ops snd_als4000_playback_ops = अणु
	.खोलो =		snd_als4000_playback_खोलो,
	.बंद =	snd_als4000_playback_बंद,
	.prepare =	snd_als4000_playback_prepare,
	.trigger =	snd_als4000_playback_trigger,
	.poपूर्णांकer =	snd_als4000_playback_poपूर्णांकer
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_als4000_capture_ops = अणु
	.खोलो =		snd_als4000_capture_खोलो,
	.बंद =	snd_als4000_capture_बंद,
	.prepare =	snd_als4000_capture_prepare,
	.trigger =	snd_als4000_capture_trigger,
	.poपूर्णांकer =	snd_als4000_capture_poपूर्णांकer
पूर्ण;

अटल पूर्णांक snd_als4000_pcm(काष्ठा snd_sb *chip, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	err = snd_pcm_new(chip->card, "ALS4000 DSP", device, 1, 1, &pcm);
	अगर (err < 0)
		वापस err;
	pcm->निजी_data = chip;
	pcm->info_flags = SNDRV_PCM_INFO_JOINT_DUPLEX;
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_als4000_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_als4000_capture_ops);

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
				       &chip->pci->dev, 64*1024, 64*1024);

	chip->pcm = pcm;

	वापस 0;
पूर्ण

/******************************************************************/

अटल व्योम snd_als4000_set_addr(अचिन्हित दीर्घ iobase,
					अचिन्हित पूर्णांक sb_io,
					अचिन्हित पूर्णांक mpu_io,
					अचिन्हित पूर्णांक opl_io,
					अचिन्हित पूर्णांक game_io)
अणु
	u32 cfg1 = 0;
	u32 cfg2 = 0;

	अगर (mpu_io > 0)
		cfg2 |= (mpu_io | 1) << 16;
	अगर (sb_io > 0)
		cfg2 |= (sb_io | 1);
	अगर (game_io > 0)
		cfg1 |= (game_io | 1) << 16;
	अगर (opl_io > 0)
		cfg1 |= (opl_io | 1);
	snd_als4k_gcr_ग_लिखो_addr(iobase, ALS4K_GCRA8_LEGACY_CFG1, cfg1);
	snd_als4k_gcr_ग_लिखो_addr(iobase, ALS4K_GCRA9_LEGACY_CFG2, cfg2);
पूर्ण

अटल व्योम snd_als4000_configure(काष्ठा snd_sb *chip)
अणु
	u8 पंचांगp;
	पूर्णांक i;

	/* करो some more configuration */
	spin_lock_irq(&chip->mixer_lock);
	पंचांगp = snd_als4_cr_पढ़ो(chip, ALS4K_CR0_SB_CONFIG);
	snd_als4_cr_ग_लिखो(chip, ALS4K_CR0_SB_CONFIG,
				पंचांगp|ALS4K_CR0_MX80_81_REG_WRITE_ENABLE);
	/* always select DMA channel 0, since we करो not actually use DMA
	 * SPECS_PAGE: 19/20 */
	snd_sbmixer_ग_लिखो(chip, SB_DSP4_DMASETUP, SB_DMASETUP_DMA0);
	snd_als4_cr_ग_लिखो(chip, ALS4K_CR0_SB_CONFIG,
				 पंचांगp & ~ALS4K_CR0_MX80_81_REG_WRITE_ENABLE);
	spin_unlock_irq(&chip->mixer_lock);
	
	spin_lock_irq(&chip->reg_lock);
	/* enable पूर्णांकerrupts */
	snd_als4k_gcr_ग_लिखो(chip, ALS4K_GCR8C_MISC_CTRL,
					ALS4K_GCR8C_IRQ_MASK_CTRL_ENABLE);

	/* SPECS_PAGE: 39 */
	क्रम (i = ALS4K_GCR91_DMA0_ADDR; i <= ALS4K_GCR96_DMA3_MODE_COUNT; ++i)
		snd_als4k_gcr_ग_लिखो(chip, i, 0);
	/* enable burst mode to prevent dropouts during high PCI bus usage */
	snd_als4k_gcr_ग_लिखो(chip, ALS4K_GCR99_DMA_EMULATION_CTRL,
		(snd_als4k_gcr_पढ़ो(chip, ALS4K_GCR99_DMA_EMULATION_CTRL) & ~0x07) | 0x04);
	spin_unlock_irq(&chip->reg_lock);
पूर्ण

#अगर_घोषित SUPPORT_JOYSTICK
अटल पूर्णांक snd_als4000_create_gameport(काष्ठा snd_card_als4000 *acard, पूर्णांक dev)
अणु
	काष्ठा gameport *gp;
	काष्ठा resource *r;
	पूर्णांक io_port;

	अगर (joystick_port[dev] == 0)
		वापस -ENODEV;

	अगर (joystick_port[dev] == 1) अणु /* स्वतः-detect */
		क्रम (io_port = 0x200; io_port <= 0x218; io_port += 8) अणु
			r = request_region(io_port, 8, "ALS4000 gameport");
			अगर (r)
				अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		io_port = joystick_port[dev];
		r = request_region(io_port, 8, "ALS4000 gameport");
	पूर्ण

	अगर (!r) अणु
		dev_warn(&acard->pci->dev, "cannot reserve joystick ports\n");
		वापस -EBUSY;
	पूर्ण

	acard->gameport = gp = gameport_allocate_port();
	अगर (!gp) अणु
		dev_err(&acard->pci->dev, "cannot allocate memory for gameport\n");
		release_and_मुक्त_resource(r);
		वापस -ENOMEM;
	पूर्ण

	gameport_set_name(gp, "ALS4000 Gameport");
	gameport_set_phys(gp, "pci%s/gameport0", pci_name(acard->pci));
	gameport_set_dev_parent(gp, &acard->pci->dev);
	gp->io = io_port;
	gameport_set_port_data(gp, r);

	/* Enable legacy joystick port */
	snd_als4000_set_addr(acard->iobase, 0, 0, 0, 1);

	gameport_रेजिस्टर_port(acard->gameport);

	वापस 0;
पूर्ण

अटल व्योम snd_als4000_मुक्त_gameport(काष्ठा snd_card_als4000 *acard)
अणु
	अगर (acard->gameport) अणु
		काष्ठा resource *r = gameport_get_port_data(acard->gameport);

		gameport_unरेजिस्टर_port(acard->gameport);
		acard->gameport = शून्य;

		/* disable joystick */
		snd_als4000_set_addr(acard->iobase, 0, 0, 0, 0);

		release_and_मुक्त_resource(r);
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक snd_als4000_create_gameport(काष्ठा snd_card_als4000 *acard, पूर्णांक dev) अणु वापस -ENOSYS; पूर्ण
अटल अंतरभूत व्योम snd_als4000_मुक्त_gameport(काष्ठा snd_card_als4000 *acard) अणु पूर्ण
#पूर्ण_अगर

अटल व्योम snd_card_als4000_मुक्त( काष्ठा snd_card *card )
अणु
	काष्ठा snd_card_als4000 *acard = card->निजी_data;

	/* make sure that पूर्णांकerrupts are disabled */
	snd_als4k_gcr_ग_लिखो_addr(acard->iobase, ALS4K_GCR8C_MISC_CTRL, 0);
	/* मुक्त resources */
	snd_als4000_मुक्त_gameport(acard);
	pci_release_regions(acard->pci);
	pci_disable_device(acard->pci);
पूर्ण

अटल पूर्णांक snd_card_als4000_probe(काष्ठा pci_dev *pci,
				  स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_card *card;
	काष्ठा snd_card_als4000 *acard;
	अचिन्हित दीर्घ iobase;
	काष्ठा snd_sb *chip;
	काष्ठा snd_opl3 *opl3;
	अचिन्हित लघु word;
	पूर्णांक err;

	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;
	अगर (!enable[dev]) अणु
		dev++;
		वापस -ENOENT;
	पूर्ण

	/* enable PCI device */
	अगर ((err = pci_enable_device(pci)) < 0) अणु
		वापस err;
	पूर्ण
	/* check, अगर we can restrict PCI DMA transfers to 24 bits */
	अगर (dma_set_mask_and_coherent(&pci->dev, DMA_BIT_MASK(24))) अणु
		dev_err(&pci->dev, "architecture does not support 24bit PCI busmaster DMA\n");
		pci_disable_device(pci);
		वापस -ENXIO;
	पूर्ण

	अगर ((err = pci_request_regions(pci, "ALS4000")) < 0) अणु
		pci_disable_device(pci);
		वापस err;
	पूर्ण
	iobase = pci_resource_start(pci, 0);

	pci_पढ़ो_config_word(pci, PCI_COMMAND, &word);
	pci_ग_लिखो_config_word(pci, PCI_COMMAND, word | PCI_COMMAND_IO);
	pci_set_master(pci);
	
	err = snd_card_new(&pci->dev, index[dev], id[dev], THIS_MODULE,
			   माप(*acard) /* निजी_data: acard */,
			   &card);
	अगर (err < 0) अणु
		pci_release_regions(pci);
		pci_disable_device(pci);
		वापस err;
	पूर्ण

	acard = card->निजी_data;
	acard->pci = pci;
	acard->iobase = iobase;
	card->निजी_मुक्त = snd_card_als4000_मुक्त;

	/* disable all legacy ISA stuff */
	snd_als4000_set_addr(acard->iobase, 0, 0, 0, 0);

	अगर ((err = snd_sbdsp_create(card,
				    iobase + ALS4K_IOB_10_ADLIB_ADDR0,
				    pci->irq,
		/* पूर्णांकernally रेजिस्टरed as IRQF_SHARED in हाल of ALS4000 SB */
				    snd_als4000_पूर्णांकerrupt,
				    -1,
				    -1,
				    SB_HW_ALS4000,
				    &chip)) < 0) अणु
		जाओ out_err;
	पूर्ण
	acard->chip = chip;

	chip->pci = pci;
	chip->alt_port = iobase;

	snd_als4000_configure(chip);

	म_नकल(card->driver, "ALS4000");
	म_नकल(card->लघुname, "Avance Logic ALS4000");
	प्र_लिखो(card->दीर्घname, "%s at 0x%lx, irq %i",
		card->लघुname, chip->alt_port, chip->irq);

	अगर ((err = snd_mpu401_uart_new( card, 0, MPU401_HW_ALS4000,
					iobase + ALS4K_IOB_30_MIDI_DATA,
					MPU401_INFO_INTEGRATED |
					MPU401_INFO_IRQ_HOOK,
					-1, &chip->rmidi)) < 0) अणु
		dev_err(&pci->dev, "no MPU-401 device at 0x%lx?\n",
				iobase + ALS4K_IOB_30_MIDI_DATA);
		जाओ out_err;
	पूर्ण
	/* FIXME: ALS4000 has पूर्णांकeresting MPU401 configuration features
	 * at ALS4K_CR1A_MPU401_UART_MODE_CONTROL
	 * (pass-thru / UART चयनing, fast MIDI घड़ी, etc.),
	 * however there करोesn't seem to be an ALSA API क्रम this...
	 * SPECS_PAGE: 21 */

	अगर ((err = snd_als4000_pcm(chip, 0)) < 0) अणु
		जाओ out_err;
	पूर्ण
	अगर ((err = snd_sbmixer_new(chip)) < 0) अणु
		जाओ out_err;
	पूर्ण	    

	अगर (snd_opl3_create(card,
				iobase + ALS4K_IOB_10_ADLIB_ADDR0,
				iobase + ALS4K_IOB_12_ADLIB_ADDR2,
			    OPL3_HW_AUTO, 1, &opl3) < 0) अणु
		dev_err(&pci->dev, "no OPL device at 0x%lx-0x%lx?\n",
			   iobase + ALS4K_IOB_10_ADLIB_ADDR0,
			   iobase + ALS4K_IOB_12_ADLIB_ADDR2);
	पूर्ण अन्यथा अणु
		अगर ((err = snd_opl3_hwdep_new(opl3, 0, 1, शून्य)) < 0) अणु
			जाओ out_err;
		पूर्ण
	पूर्ण

	snd_als4000_create_gameport(acard, dev);

	अगर ((err = snd_card_रेजिस्टर(card)) < 0) अणु
		जाओ out_err;
	पूर्ण
	pci_set_drvdata(pci, card);
	dev++;
	err = 0;
	जाओ out;

out_err:
	snd_card_मुक्त(card);
	
out:
	वापस err;
पूर्ण

अटल व्योम snd_card_als4000_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक snd_als4000_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा snd_card_als4000 *acard = card->निजी_data;
	काष्ठा snd_sb *chip = acard->chip;

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);
	
	snd_sbmixer_suspend(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_als4000_resume(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा snd_card_als4000 *acard = card->निजी_data;
	काष्ठा snd_sb *chip = acard->chip;

	snd_als4000_configure(chip);
	snd_sbdsp_reset(chip);
	snd_sbmixer_resume(chip);

#अगर_घोषित SUPPORT_JOYSTICK
	अगर (acard->gameport)
		snd_als4000_set_addr(acard->iobase, 0, 0, 0, 1);
#पूर्ण_अगर

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(snd_als4000_pm, snd_als4000_suspend, snd_als4000_resume);
#घोषणा SND_ALS4000_PM_OPS	&snd_als4000_pm
#अन्यथा
#घोषणा SND_ALS4000_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल काष्ठा pci_driver als4000_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_als4000_ids,
	.probe = snd_card_als4000_probe,
	.हटाओ = snd_card_als4000_हटाओ,
	.driver = अणु
		.pm = SND_ALS4000_PM_OPS,
	पूर्ण,
पूर्ण;

module_pci_driver(als4000_driver);
