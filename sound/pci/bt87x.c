<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * bt87x.c - Brooktree Bt878/Bt879 driver क्रम ALSA
 *
 * Copyright (c) Clemens Ladisch <clemens@ladisch.de>
 *
 * based on btaudio.c by Gerd Knorr <kraxel@bytesex.org>
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/bitops.h>
#समावेश <linux/पन.स>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/control.h>
#समावेश <sound/initval.h>

MODULE_AUTHOR("Clemens Ladisch <clemens@ladisch.de>");
MODULE_DESCRIPTION("Brooktree Bt87x audio driver");
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = -2पूर्ण; /* Exclude the first card */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;	/* Enable this card */
अटल पूर्णांक digital_rate[SNDRV_CARDS];	/* digital input rate */
अटल bool load_all;	/* allow to load cards not the allowlist */

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for Bt87x soundcard");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for Bt87x soundcard");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable Bt87x soundcard");
module_param_array(digital_rate, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(digital_rate, "Digital input rate for Bt87x soundcard");
module_param(load_all, bool, 0444);
MODULE_PARM_DESC(load_all, "Allow to load cards not on the allowlist");


/* रेजिस्टर offsets */
#घोषणा REG_INT_STAT		0x100	/* पूर्णांकerrupt status */
#घोषणा REG_INT_MASK		0x104	/* पूर्णांकerrupt mask */
#घोषणा REG_GPIO_DMA_CTL	0x10c	/* audio control */
#घोषणा REG_PACKET_LEN		0x110	/* audio packet lengths */
#घोषणा REG_RISC_STRT_ADD	0x114	/* RISC program start address */
#घोषणा REG_RISC_COUNT		0x120	/* RISC program counter */

/* पूर्णांकerrupt bits */
#घोषणा INT_OFLOW	(1 <<  3)	/* audio A/D overflow */
#घोषणा INT_RISCI	(1 << 11)	/* RISC inकाष्ठाion IRQ bit set */
#घोषणा INT_FBUS	(1 << 12)	/* FIFO overrun due to bus access latency */
#घोषणा INT_FTRGT	(1 << 13)	/* FIFO overrun due to target latency */
#घोषणा INT_FDSR	(1 << 14)	/* FIFO data stream resynchronization */
#घोषणा INT_PPERR	(1 << 15)	/* PCI parity error */
#घोषणा INT_RIPERR	(1 << 16)	/* RISC inकाष्ठाion parity error */
#घोषणा INT_PABORT	(1 << 17)	/* PCI master or target पात */
#घोषणा INT_OCERR	(1 << 18)	/* invalid opcode */
#घोषणा INT_SCERR	(1 << 19)	/* sync counter overflow */
#घोषणा INT_RISC_EN	(1 << 27)	/* DMA controller running */
#घोषणा INT_RISCS_SHIFT	      28	/* RISC status bits */

/* audio control bits */
#घोषणा CTL_FIFO_ENABLE		(1 <<  0)	/* enable audio data FIFO */
#घोषणा CTL_RISC_ENABLE		(1 <<  1)	/* enable audio DMA controller */
#घोषणा CTL_PKTP_4		(0 <<  2)	/* packet mode FIFO trigger poपूर्णांक - 4 DWORDs */
#घोषणा CTL_PKTP_8		(1 <<  2)	/* 8 DWORDs */
#घोषणा CTL_PKTP_16		(2 <<  2)	/* 16 DWORDs */
#घोषणा CTL_ACAP_EN		(1 <<  4)	/* enable audio capture */
#घोषणा CTL_DA_APP		(1 <<  5)	/* GPIO input */
#घोषणा CTL_DA_IOM_AFE		(0 <<  6)	/* audio A/D input */
#घोषणा CTL_DA_IOM_DA		(1 <<  6)	/* digital audio input */
#घोषणा CTL_DA_SDR_SHIFT	       8	/* DDF first stage decimation rate */
#घोषणा CTL_DA_SDR_MASK		(0xf<< 8)
#घोषणा CTL_DA_LMT		(1 << 12)	/* limit audio data values */
#घोषणा CTL_DA_ES2		(1 << 13)	/* enable DDF stage 2 */
#घोषणा CTL_DA_SBR		(1 << 14)	/* samples rounded to 8 bits */
#घोषणा CTL_DA_DPM		(1 << 15)	/* data packet mode */
#घोषणा CTL_DA_LRD_SHIFT	      16	/* ALRCK delay */
#घोषणा CTL_DA_MLB		(1 << 21)	/* MSB/LSB क्रमmat */
#घोषणा CTL_DA_LRI		(1 << 22)	/* left/right indication */
#घोषणा CTL_DA_SCE		(1 << 23)	/* sample घड़ी edge */
#घोषणा CTL_A_SEL_STV		(0 << 24)	/* TV tuner audio input */
#घोषणा CTL_A_SEL_SFM		(1 << 24)	/* FM audio input */
#घोषणा CTL_A_SEL_SML		(2 << 24)	/* mic/line audio input */
#घोषणा CTL_A_SEL_SMXC		(3 << 24)	/* MUX bypass */
#घोषणा CTL_A_SEL_SHIFT		      24
#घोषणा CTL_A_SEL_MASK		(3 << 24)
#घोषणा CTL_A_PWRDN		(1 << 26)	/* analog audio घातer-करोwn */
#घोषणा CTL_A_G2X		(1 << 27)	/* audio gain boost */
#घोषणा CTL_A_GAIN_SHIFT	      28	/* audio input gain */
#घोषणा CTL_A_GAIN_MASK		(0xf<<28)

/* RISC inकाष्ठाion opcodes */
#घोषणा RISC_WRITE	(0x1 << 28)	/* ग_लिखो FIFO data to memory at address */
#घोषणा RISC_WRITEC	(0x5 << 28)	/* ग_लिखो FIFO data to memory at current address */
#घोषणा RISC_SKIP	(0x2 << 28)	/* skip FIFO data */
#घोषणा RISC_JUMP	(0x7 << 28)	/* jump to address */
#घोषणा RISC_SYNC	(0x8 << 28)	/* synchronize with FIFO */

/* RISC inकाष्ठाion bits */
#घोषणा RISC_BYTES_ENABLE	(0xf << 12)	/* byte enable bits */
#घोषणा RISC_RESYNC		(  1 << 15)	/* disable FDSR errors */
#घोषणा RISC_SET_STATUS_SHIFT	        16	/* set status bits */
#घोषणा RISC_RESET_STATUS_SHIFT	        20	/* clear status bits */
#घोषणा RISC_IRQ		(  1 << 24)	/* पूर्णांकerrupt */
#घोषणा RISC_EOL		(  1 << 26)	/* end of line */
#घोषणा RISC_SOL		(  1 << 27)	/* start of line */

/* SYNC status bits values */
#घोषणा RISC_SYNC_FM1	0x6
#घोषणा RISC_SYNC_VRO	0xc

#घोषणा ANALOG_CLOCK 1792000
#अगर_घोषित CONFIG_SND_BT87X_OVERCLOCK
#घोषणा CLOCK_DIV_MIN 1
#अन्यथा
#घोषणा CLOCK_DIV_MIN 4
#पूर्ण_अगर
#घोषणा CLOCK_DIV_MAX 15

#घोषणा ERROR_INTERRUPTS (INT_FBUS | INT_FTRGT | INT_PPERR | \
			  INT_RIPERR | INT_PABORT | INT_OCERR)
#घोषणा MY_INTERRUPTS (INT_RISCI | ERROR_INTERRUPTS)

/* SYNC, one WRITE per line, one extra WRITE per page boundary, SYNC, JUMP */
#घोषणा MAX_RISC_SIZE ((1 + 255 + (PAGE_ALIGN(255 * 4092) / PAGE_SIZE - 1) + 1 + 1) * 8)

/* Cards with configuration inक्रमmation */
क्रमागत snd_bt87x_boardid अणु
	SND_BT87X_BOARD_UNKNOWN,
	SND_BT87X_BOARD_GENERIC,	/* both an & dig पूर्णांकerfaces, 32kHz */
	SND_BT87X_BOARD_ANALOG,		/* board with no बाह्यal A/D */
	SND_BT87X_BOARD_OSPREY2x0,
	SND_BT87X_BOARD_OSPREY440,
	SND_BT87X_BOARD_AVPHONE98,
पूर्ण;

/* Card configuration */
काष्ठा snd_bt87x_board अणु
	पूर्णांक dig_rate;		/* Digital input sampling rate */
	u32 digital_fmt;	/* Register settings क्रम digital input */
	अचिन्हित no_analog:1;	/* No analog input */
	अचिन्हित no_digital:1;	/* No digital input */
पूर्ण;

अटल स्थिर काष्ठा snd_bt87x_board snd_bt87x_boards[] = अणु
	[SND_BT87X_BOARD_UNKNOWN] = अणु
		.dig_rate = 32000, /* just a guess */
	पूर्ण,
	[SND_BT87X_BOARD_GENERIC] = अणु
		.dig_rate = 32000,
	पूर्ण,
	[SND_BT87X_BOARD_ANALOG] = अणु
		.no_digital = 1,
	पूर्ण,
	[SND_BT87X_BOARD_OSPREY2x0] = अणु
		.dig_rate = 44100,
		.digital_fmt = CTL_DA_LRI | (1 << CTL_DA_LRD_SHIFT),
	पूर्ण,
	[SND_BT87X_BOARD_OSPREY440] = अणु
		.dig_rate = 32000,
		.digital_fmt = CTL_DA_LRI | (1 << CTL_DA_LRD_SHIFT),
		.no_analog = 1,
	पूर्ण,
	[SND_BT87X_BOARD_AVPHONE98] = अणु
		.dig_rate = 48000,
	पूर्ण,
पूर्ण;

काष्ठा snd_bt87x अणु
	काष्ठा snd_card *card;
	काष्ठा pci_dev *pci;
	काष्ठा snd_bt87x_board board;

	व्योम __iomem *mmio;
	पूर्णांक irq;

	spinlock_t reg_lock;
	अचिन्हित दीर्घ खोलोed;
	काष्ठा snd_pcm_substream *substream;

	काष्ठा snd_dma_buffer dma_risc;
	अचिन्हित पूर्णांक line_bytes;
	अचिन्हित पूर्णांक lines;

	u32 reg_control;
	u32 पूर्णांकerrupt_mask;

	पूर्णांक current_line;

	पूर्णांक pci_parity_errors;
पूर्ण;

क्रमागत अणु DEVICE_DIGITAL, DEVICE_ANALOG पूर्ण;

अटल अंतरभूत u32 snd_bt87x_पढ़ोl(काष्ठा snd_bt87x *chip, u32 reg)
अणु
	वापस पढ़ोl(chip->mmio + reg);
पूर्ण

अटल अंतरभूत व्योम snd_bt87x_ग_लिखोl(काष्ठा snd_bt87x *chip, u32 reg, u32 value)
अणु
	ग_लिखोl(value, chip->mmio + reg);
पूर्ण

अटल पूर्णांक snd_bt87x_create_risc(काष्ठा snd_bt87x *chip, काष्ठा snd_pcm_substream *substream,
			       	 अचिन्हित पूर्णांक periods, अचिन्हित पूर्णांक period_bytes)
अणु
	अचिन्हित पूर्णांक i, offset;
	__le32 *risc;

	अगर (chip->dma_risc.area == शून्य) अणु
		अगर (snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, &chip->pci->dev,
					PAGE_ALIGN(MAX_RISC_SIZE), &chip->dma_risc) < 0)
			वापस -ENOMEM;
	पूर्ण
	risc = (__le32 *)chip->dma_risc.area;
	offset = 0;
	*risc++ = cpu_to_le32(RISC_SYNC | RISC_SYNC_FM1);
	*risc++ = cpu_to_le32(0);
	क्रम (i = 0; i < periods; ++i) अणु
		u32 rest;

		rest = period_bytes;
		करो अणु
			u32 cmd, len;
			अचिन्हित पूर्णांक addr;

			len = PAGE_SIZE - (offset % PAGE_SIZE);
			अगर (len > rest)
				len = rest;
			cmd = RISC_WRITE | len;
			अगर (rest == period_bytes) अणु
				u32 block = i * 16 / periods;
				cmd |= RISC_SOL;
				cmd |= block << RISC_SET_STATUS_SHIFT;
				cmd |= (~block & 0xf) << RISC_RESET_STATUS_SHIFT;
			पूर्ण
			अगर (len == rest)
				cmd |= RISC_EOL | RISC_IRQ;
			*risc++ = cpu_to_le32(cmd);
			addr = snd_pcm_sgbuf_get_addr(substream, offset);
			*risc++ = cpu_to_le32(addr);
			offset += len;
			rest -= len;
		पूर्ण जबतक (rest > 0);
	पूर्ण
	*risc++ = cpu_to_le32(RISC_SYNC | RISC_SYNC_VRO);
	*risc++ = cpu_to_le32(0);
	*risc++ = cpu_to_le32(RISC_JUMP);
	*risc++ = cpu_to_le32(chip->dma_risc.addr);
	chip->line_bytes = period_bytes;
	chip->lines = periods;
	वापस 0;
पूर्ण

अटल व्योम snd_bt87x_मुक्त_risc(काष्ठा snd_bt87x *chip)
अणु
	अगर (chip->dma_risc.area) अणु
		snd_dma_मुक्त_pages(&chip->dma_risc);
		chip->dma_risc.area = शून्य;
	पूर्ण
पूर्ण

अटल व्योम snd_bt87x_pci_error(काष्ठा snd_bt87x *chip, अचिन्हित पूर्णांक status)
अणु
	पूर्णांक pci_status = pci_status_get_and_clear_errors(chip->pci);

	अगर (pci_status != PCI_STATUS_DETECTED_PARITY)
		dev_err(chip->card->dev,
			"Aieee - PCI error! status %#08x, PCI status %#04x\n",
			   status & ERROR_INTERRUPTS, pci_status);
	अन्यथा अणु
		dev_err(chip->card->dev,
			"Aieee - PCI parity error detected!\n");
		/* error 'handling' similar to aic7xxx_pci.c: */
		chip->pci_parity_errors++;
		अगर (chip->pci_parity_errors > 20) अणु
			dev_err(chip->card->dev,
				"Too many PCI parity errors observed.\n");
			dev_err(chip->card->dev,
				"Some device on this bus is generating bad parity.\n");
			dev_err(chip->card->dev,
				"This is an error *observed by*, not *generated by*, this card.\n");
			dev_err(chip->card->dev,
				"PCI parity error checking has been disabled.\n");
			chip->पूर्णांकerrupt_mask &= ~(INT_PPERR | INT_RIPERR);
			snd_bt87x_ग_लिखोl(chip, REG_INT_MASK, chip->पूर्णांकerrupt_mask);
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t snd_bt87x_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा snd_bt87x *chip = dev_id;
	अचिन्हित पूर्णांक status, irq_status;

	status = snd_bt87x_पढ़ोl(chip, REG_INT_STAT);
	irq_status = status & chip->पूर्णांकerrupt_mask;
	अगर (!irq_status)
		वापस IRQ_NONE;
	snd_bt87x_ग_लिखोl(chip, REG_INT_STAT, irq_status);

	अगर (irq_status & ERROR_INTERRUPTS) अणु
		अगर (irq_status & (INT_FBUS | INT_FTRGT))
			dev_warn(chip->card->dev,
				 "FIFO overrun, status %#08x\n", status);
		अगर (irq_status & INT_OCERR)
			dev_err(chip->card->dev,
				"internal RISC error, status %#08x\n", status);
		अगर (irq_status & (INT_PPERR | INT_RIPERR | INT_PABORT))
			snd_bt87x_pci_error(chip, irq_status);
	पूर्ण
	अगर ((irq_status & INT_RISCI) && (chip->reg_control & CTL_ACAP_EN)) अणु
		पूर्णांक current_block, irq_block;

		/* assume that exactly one line has been recorded */
		chip->current_line = (chip->current_line + 1) % chip->lines;
		/* but check अगर some पूर्णांकerrupts have been skipped */
		current_block = chip->current_line * 16 / chip->lines;
		irq_block = status >> INT_RISCS_SHIFT;
		अगर (current_block != irq_block)
			chip->current_line = DIV_ROUND_UP(irq_block * chip->lines,
							  16);

		snd_pcm_period_elapsed(chip->substream);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware snd_bt87x_digital_hw = अणु
	.info = SNDRV_PCM_INFO_MMAP |
		SNDRV_PCM_INFO_INTERLEAVED |
		SNDRV_PCM_INFO_BLOCK_TRANSFER |
		SNDRV_PCM_INFO_MMAP_VALID |
		SNDRV_PCM_INFO_BATCH,
	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	.rates = 0, /* set at runसमय */
	.channels_min = 2,
	.channels_max = 2,
	.buffer_bytes_max = 255 * 4092,
	.period_bytes_min = 32,
	.period_bytes_max = 4092,
	.periods_min = 2,
	.periods_max = 255,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_bt87x_analog_hw = अणु
	.info = SNDRV_PCM_INFO_MMAP |
		SNDRV_PCM_INFO_INTERLEAVED |
		SNDRV_PCM_INFO_BLOCK_TRANSFER |
		SNDRV_PCM_INFO_MMAP_VALID |
		SNDRV_PCM_INFO_BATCH,
	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S8,
	.rates = SNDRV_PCM_RATE_KNOT,
	.rate_min = ANALOG_CLOCK / CLOCK_DIV_MAX,
	.rate_max = ANALOG_CLOCK / CLOCK_DIV_MIN,
	.channels_min = 1,
	.channels_max = 1,
	.buffer_bytes_max = 255 * 4092,
	.period_bytes_min = 32,
	.period_bytes_max = 4092,
	.periods_min = 2,
	.periods_max = 255,
पूर्ण;

अटल पूर्णांक snd_bt87x_set_digital_hw(काष्ठा snd_bt87x *chip, काष्ठा snd_pcm_runसमय *runसमय)
अणु
	chip->reg_control |= CTL_DA_IOM_DA | CTL_A_PWRDN;
	runसमय->hw = snd_bt87x_digital_hw;
	runसमय->hw.rates = snd_pcm_rate_to_rate_bit(chip->board.dig_rate);
	runसमय->hw.rate_min = chip->board.dig_rate;
	runसमय->hw.rate_max = chip->board.dig_rate;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_bt87x_set_analog_hw(काष्ठा snd_bt87x *chip, काष्ठा snd_pcm_runसमय *runसमय)
अणु
	अटल स्थिर काष्ठा snd_ratnum analog_घड़ी = अणु
		.num = ANALOG_CLOCK,
		.den_min = CLOCK_DIV_MIN,
		.den_max = CLOCK_DIV_MAX,
		.den_step = 1
	पूर्ण;
	अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_ratnums स्थिरraपूर्णांक_rates = अणु
		.nrats = 1,
		.rats = &analog_घड़ी
	पूर्ण;

	chip->reg_control &= ~(CTL_DA_IOM_DA | CTL_A_PWRDN);
	runसमय->hw = snd_bt87x_analog_hw;
	वापस snd_pcm_hw_स्थिरraपूर्णांक_ratnums(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
					     &स्थिरraपूर्णांक_rates);
पूर्ण

अटल पूर्णांक snd_bt87x_pcm_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_bt87x *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;

	अगर (test_and_set_bit(0, &chip->खोलोed))
		वापस -EBUSY;

	अगर (substream->pcm->device == DEVICE_DIGITAL)
		err = snd_bt87x_set_digital_hw(chip, runसमय);
	अन्यथा
		err = snd_bt87x_set_analog_hw(chip, runसमय);
	अगर (err < 0)
		जाओ _error;

	err = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय, SNDRV_PCM_HW_PARAM_PERIODS);
	अगर (err < 0)
		जाओ _error;

	chip->substream = substream;
	वापस 0;

_error:
	clear_bit(0, &chip->खोलोed);
	smp_mb__after_atomic();
	वापस err;
पूर्ण

अटल पूर्णांक snd_bt87x_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_bt87x *chip = snd_pcm_substream_chip(substream);

	spin_lock_irq(&chip->reg_lock);
	chip->reg_control |= CTL_A_PWRDN;
	snd_bt87x_ग_लिखोl(chip, REG_GPIO_DMA_CTL, chip->reg_control);
	spin_unlock_irq(&chip->reg_lock);

	chip->substream = शून्य;
	clear_bit(0, &chip->खोलोed);
	smp_mb__after_atomic();
	वापस 0;
पूर्ण

अटल पूर्णांक snd_bt87x_hw_params(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_bt87x *chip = snd_pcm_substream_chip(substream);

	वापस snd_bt87x_create_risc(chip, substream,
				     params_periods(hw_params),
				     params_period_bytes(hw_params));
पूर्ण

अटल पूर्णांक snd_bt87x_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_bt87x *chip = snd_pcm_substream_chip(substream);

	snd_bt87x_मुक्त_risc(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_bt87x_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_bt87x *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक decimation;

	spin_lock_irq(&chip->reg_lock);
	chip->reg_control &= ~(CTL_DA_SDR_MASK | CTL_DA_SBR);
	decimation = (ANALOG_CLOCK + runसमय->rate / 4) / runसमय->rate;
	chip->reg_control |= decimation << CTL_DA_SDR_SHIFT;
	अगर (runसमय->क्रमmat == SNDRV_PCM_FORMAT_S8)
		chip->reg_control |= CTL_DA_SBR;
	snd_bt87x_ग_लिखोl(chip, REG_GPIO_DMA_CTL, chip->reg_control);
	spin_unlock_irq(&chip->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_bt87x_start(काष्ठा snd_bt87x *chip)
अणु
	spin_lock(&chip->reg_lock);
	chip->current_line = 0;
	chip->reg_control |= CTL_FIFO_ENABLE | CTL_RISC_ENABLE | CTL_ACAP_EN;
	snd_bt87x_ग_लिखोl(chip, REG_RISC_STRT_ADD, chip->dma_risc.addr);
	snd_bt87x_ग_लिखोl(chip, REG_PACKET_LEN,
			 chip->line_bytes | (chip->lines << 16));
	snd_bt87x_ग_लिखोl(chip, REG_INT_MASK, chip->पूर्णांकerrupt_mask);
	snd_bt87x_ग_लिखोl(chip, REG_GPIO_DMA_CTL, chip->reg_control);
	spin_unlock(&chip->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_bt87x_stop(काष्ठा snd_bt87x *chip)
अणु
	spin_lock(&chip->reg_lock);
	chip->reg_control &= ~(CTL_FIFO_ENABLE | CTL_RISC_ENABLE | CTL_ACAP_EN);
	snd_bt87x_ग_लिखोl(chip, REG_GPIO_DMA_CTL, chip->reg_control);
	snd_bt87x_ग_लिखोl(chip, REG_INT_MASK, 0);
	snd_bt87x_ग_लिखोl(chip, REG_INT_STAT, MY_INTERRUPTS);
	spin_unlock(&chip->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_bt87x_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_bt87x *chip = snd_pcm_substream_chip(substream);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		वापस snd_bt87x_start(chip);
	हाल SNDRV_PCM_TRIGGER_STOP:
		वापस snd_bt87x_stop(chip);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल snd_pcm_uframes_t snd_bt87x_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_bt87x *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	वापस (snd_pcm_uframes_t)bytes_to_frames(runसमय, chip->current_line * chip->line_bytes);
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_bt87x_pcm_ops = अणु
	.खोलो = snd_bt87x_pcm_खोलो,
	.बंद = snd_bt87x_बंद,
	.hw_params = snd_bt87x_hw_params,
	.hw_मुक्त = snd_bt87x_hw_मुक्त,
	.prepare = snd_bt87x_prepare,
	.trigger = snd_bt87x_trigger,
	.poपूर्णांकer = snd_bt87x_poपूर्णांकer,
पूर्ण;

अटल पूर्णांक snd_bt87x_capture_volume_info(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_info *info)
अणु
	info->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	info->count = 1;
	info->value.पूर्णांकeger.min = 0;
	info->value.पूर्णांकeger.max = 15;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_bt87x_capture_volume_get(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा snd_bt87x *chip = snd_kcontrol_chip(kcontrol);

	value->value.पूर्णांकeger.value[0] = (chip->reg_control & CTL_A_GAIN_MASK) >> CTL_A_GAIN_SHIFT;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_bt87x_capture_volume_put(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा snd_bt87x *chip = snd_kcontrol_chip(kcontrol);
	u32 old_control;
	पूर्णांक changed;

	spin_lock_irq(&chip->reg_lock);
	old_control = chip->reg_control;
	chip->reg_control = (chip->reg_control & ~CTL_A_GAIN_MASK)
		| (value->value.पूर्णांकeger.value[0] << CTL_A_GAIN_SHIFT);
	snd_bt87x_ग_लिखोl(chip, REG_GPIO_DMA_CTL, chip->reg_control);
	changed = old_control != chip->reg_control;
	spin_unlock_irq(&chip->reg_lock);
	वापस changed;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_bt87x_capture_volume = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Capture Volume",
	.info = snd_bt87x_capture_volume_info,
	.get = snd_bt87x_capture_volume_get,
	.put = snd_bt87x_capture_volume_put,
पूर्ण;

#घोषणा snd_bt87x_capture_boost_info	snd_ctl_boolean_mono_info

अटल पूर्णांक snd_bt87x_capture_boost_get(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा snd_bt87x *chip = snd_kcontrol_chip(kcontrol);

	value->value.पूर्णांकeger.value[0] = !! (chip->reg_control & CTL_A_G2X);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_bt87x_capture_boost_put(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा snd_bt87x *chip = snd_kcontrol_chip(kcontrol);
	u32 old_control;
	पूर्णांक changed;

	spin_lock_irq(&chip->reg_lock);
	old_control = chip->reg_control;
	chip->reg_control = (chip->reg_control & ~CTL_A_G2X)
		| (value->value.पूर्णांकeger.value[0] ? CTL_A_G2X : 0);
	snd_bt87x_ग_लिखोl(chip, REG_GPIO_DMA_CTL, chip->reg_control);
	changed = chip->reg_control != old_control;
	spin_unlock_irq(&chip->reg_lock);
	वापस changed;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_bt87x_capture_boost = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Capture Boost",
	.info = snd_bt87x_capture_boost_info,
	.get = snd_bt87x_capture_boost_get,
	.put = snd_bt87x_capture_boost_put,
पूर्ण;

अटल पूर्णांक snd_bt87x_capture_source_info(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_info *info)
अणु
	अटल स्थिर अक्षर *स्थिर texts[3] = अणु"TV Tuner", "FM", "Mic/Line"पूर्ण;

	वापस snd_ctl_क्रमागत_info(info, 1, 3, texts);
पूर्ण

अटल पूर्णांक snd_bt87x_capture_source_get(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा snd_bt87x *chip = snd_kcontrol_chip(kcontrol);

	value->value.क्रमागतerated.item[0] = (chip->reg_control & CTL_A_SEL_MASK) >> CTL_A_SEL_SHIFT;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_bt87x_capture_source_put(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा snd_bt87x *chip = snd_kcontrol_chip(kcontrol);
	u32 old_control;
	पूर्णांक changed;

	spin_lock_irq(&chip->reg_lock);
	old_control = chip->reg_control;
	chip->reg_control = (chip->reg_control & ~CTL_A_SEL_MASK)
		| (value->value.क्रमागतerated.item[0] << CTL_A_SEL_SHIFT);
	snd_bt87x_ग_लिखोl(chip, REG_GPIO_DMA_CTL, chip->reg_control);
	changed = chip->reg_control != old_control;
	spin_unlock_irq(&chip->reg_lock);
	वापस changed;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_bt87x_capture_source = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Capture Source",
	.info = snd_bt87x_capture_source_info,
	.get = snd_bt87x_capture_source_get,
	.put = snd_bt87x_capture_source_put,
पूर्ण;

अटल पूर्णांक snd_bt87x_मुक्त(काष्ठा snd_bt87x *chip)
अणु
	अगर (chip->mmio)
		snd_bt87x_stop(chip);
	अगर (chip->irq >= 0)
		मुक्त_irq(chip->irq, chip);
	iounmap(chip->mmio);
	pci_release_regions(chip->pci);
	pci_disable_device(chip->pci);
	kमुक्त(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_bt87x_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_bt87x *chip = device->device_data;
	वापस snd_bt87x_मुक्त(chip);
पूर्ण

अटल पूर्णांक snd_bt87x_pcm(काष्ठा snd_bt87x *chip, पूर्णांक device, अक्षर *name)
अणु
	पूर्णांक err;
	काष्ठा snd_pcm *pcm;

	err = snd_pcm_new(chip->card, name, device, 0, 1, &pcm);
	अगर (err < 0)
		वापस err;
	pcm->निजी_data = chip;
	म_नकल(pcm->name, name);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_bt87x_pcm_ops);
	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV_SG,
				       &chip->pci->dev,
				       128 * 1024,
				       ALIGN(255 * 4092, 1024));
	वापस 0;
पूर्ण

अटल पूर्णांक snd_bt87x_create(काष्ठा snd_card *card,
			    काष्ठा pci_dev *pci,
			    काष्ठा snd_bt87x **rchip)
अणु
	काष्ठा snd_bt87x *chip;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त = snd_bt87x_dev_मुक्त
	पूर्ण;

	*rchip = शून्य;

	err = pci_enable_device(pci);
	अगर (err < 0)
		वापस err;

	chip = kzalloc(माप(*chip), GFP_KERNEL);
	अगर (!chip) अणु
		pci_disable_device(pci);
		वापस -ENOMEM;
	पूर्ण
	chip->card = card;
	chip->pci = pci;
	chip->irq = -1;
	spin_lock_init(&chip->reg_lock);

	अगर ((err = pci_request_regions(pci, "Bt87x audio")) < 0) अणु
		kमुक्त(chip);
		pci_disable_device(pci);
		वापस err;
	पूर्ण
	chip->mmio = pci_ioremap_bar(pci, 0);
	अगर (!chip->mmio) अणु
		dev_err(card->dev, "cannot remap io memory\n");
		err = -ENOMEM;
		जाओ fail;
	पूर्ण

	chip->reg_control = CTL_A_PWRDN | CTL_DA_ES2 |
			    CTL_PKTP_16 | (15 << CTL_DA_SDR_SHIFT);
	chip->पूर्णांकerrupt_mask = MY_INTERRUPTS;
	snd_bt87x_ग_लिखोl(chip, REG_GPIO_DMA_CTL, chip->reg_control);
	snd_bt87x_ग_लिखोl(chip, REG_INT_MASK, 0);
	snd_bt87x_ग_लिखोl(chip, REG_INT_STAT, MY_INTERRUPTS);

	err = request_irq(pci->irq, snd_bt87x_पूर्णांकerrupt, IRQF_SHARED,
			  KBUILD_MODNAME, chip);
	अगर (err < 0) अणु
		dev_err(card->dev, "cannot grab irq %d\n", pci->irq);
		जाओ fail;
	पूर्ण
	chip->irq = pci->irq;
	card->sync_irq = chip->irq;
	pci_set_master(pci);

	err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops);
	अगर (err < 0)
		जाओ fail;

	*rchip = chip;
	वापस 0;

fail:
	snd_bt87x_मुक्त(chip);
	वापस err;
पूर्ण

#घोषणा BT_DEVICE(chip, subvend, subdev, id) \
	अणु .venकरोr = PCI_VENDOR_ID_BROOKTREE, \
	  .device = chip, \
	  .subvenकरोr = subvend, .subdevice = subdev, \
	  .driver_data = SND_BT87X_BOARD_ ## id पूर्ण
/* driver_data is the card id क्रम that device */

अटल स्थिर काष्ठा pci_device_id snd_bt87x_ids[] = अणु
	/* Hauppauge WinTV series */
	BT_DEVICE(PCI_DEVICE_ID_BROOKTREE_878, 0x0070, 0x13eb, GENERIC),
	/* Hauppauge WinTV series */
	BT_DEVICE(PCI_DEVICE_ID_BROOKTREE_879, 0x0070, 0x13eb, GENERIC),
	/* Viewcast Osprey 200 */
	BT_DEVICE(PCI_DEVICE_ID_BROOKTREE_878, 0x0070, 0xff01, OSPREY2x0),
	/* Viewcast Osprey 440 (rate is configurable via gpio) */
	BT_DEVICE(PCI_DEVICE_ID_BROOKTREE_878, 0x0070, 0xff07, OSPREY440),
	/* ATI TV-Wonder */
	BT_DEVICE(PCI_DEVICE_ID_BROOKTREE_878, 0x1002, 0x0001, GENERIC),
	/* Leadtek Winfast tv 2000xp delux */
	BT_DEVICE(PCI_DEVICE_ID_BROOKTREE_878, 0x107d, 0x6606, GENERIC),
	/* Pinnacle PCTV */
	BT_DEVICE(PCI_DEVICE_ID_BROOKTREE_878, 0x11bd, 0x0012, GENERIC),
	/* Vooकरोo TV 200 */
	BT_DEVICE(PCI_DEVICE_ID_BROOKTREE_878, 0x121a, 0x3000, GENERIC),
	/* Askey Computer Corp. MagicTView'99 */
	BT_DEVICE(PCI_DEVICE_ID_BROOKTREE_878, 0x144f, 0x3000, GENERIC),
	/* AVerMedia Studio No. 103, 203, ...? */
	BT_DEVICE(PCI_DEVICE_ID_BROOKTREE_878, 0x1461, 0x0003, AVPHONE98),
	/* Prolink PixelView PV-M4900 */
	BT_DEVICE(PCI_DEVICE_ID_BROOKTREE_878, 0x1554, 0x4011, GENERIC),
	/* Pinnacle  Studio PCTV rave */
	BT_DEVICE(PCI_DEVICE_ID_BROOKTREE_878, 0xbd11, 0x1200, GENERIC),
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, snd_bt87x_ids);

/* cards known not to have audio
 * (DVB cards use the audio function to transfer MPEG data) */
अटल काष्ठा अणु
	अचिन्हित लघु subvenकरोr, subdevice;
पूर्ण denylist[] = अणु
	अणु0x0071, 0x0101पूर्ण, /* Nebula Electronics DigiTV */
	अणु0x11bd, 0x001cपूर्ण, /* Pinnacle PCTV Sat */
	अणु0x11bd, 0x0026पूर्ण, /* Pinnacle PCTV SAT CI */
	अणु0x1461, 0x0761पूर्ण, /* AVermedia AverTV DVB-T */
	अणु0x1461, 0x0771पूर्ण, /* AVermedia DVB-T 771 */
	अणु0x1822, 0x0001पूर्ण, /* Twinhan VisionPlus DVB-T */
	अणु0x18ac, 0xd500पूर्ण, /* DVICO FusionHDTV 5 Lite */
	अणु0x18ac, 0xdb10पूर्ण, /* DVICO FusionHDTV DVB-T Lite */
	अणु0x18ac, 0xdb11पूर्ण, /* Ultraview DVB-T Lite */
	अणु0x270f, 0xfc00पूर्ण, /* Chaपूर्णांकech Digitop DST-1000 DVB-S */
	अणु0x7063, 0x2000पूर्ण, /* pcHDTV HD-2000 TV */
पूर्ण;

अटल काष्ठा pci_driver driver;

/* वापस the id of the card, or a negative value अगर it's on the denylist */
अटल पूर्णांक snd_bt87x_detect_card(काष्ठा pci_dev *pci)
अणु
	पूर्णांक i;
	स्थिर काष्ठा pci_device_id *supported;

	supported = pci_match_id(snd_bt87x_ids, pci);
	अगर (supported && supported->driver_data > 0)
		वापस supported->driver_data;

	क्रम (i = 0; i < ARRAY_SIZE(denylist); ++i)
		अगर (denylist[i].subvenकरोr == pci->subप्रणाली_venकरोr &&
		    denylist[i].subdevice == pci->subप्रणाली_device) अणु
			dev_dbg(&pci->dev,
				"card %#04x-%#04x:%#04x has no audio\n",
				    pci->device, pci->subप्रणाली_venकरोr, pci->subप्रणाली_device);
			वापस -EBUSY;
		पूर्ण

	dev_info(&pci->dev, "unknown card %#04x-%#04x:%#04x\n",
		   pci->device, pci->subप्रणाली_venकरोr, pci->subप्रणाली_device);
	dev_info(&pci->dev, "please mail id, board name, and, "
		   "if it works, the correct digital_rate option to "
		   "<alsa-devel@alsa-project.org>\n");
	वापस SND_BT87X_BOARD_UNKNOWN;
पूर्ण

अटल पूर्णांक snd_bt87x_probe(काष्ठा pci_dev *pci,
			   स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_card *card;
	काष्ठा snd_bt87x *chip;
	पूर्णांक err;
	क्रमागत snd_bt87x_boardid boardid;

	अगर (!pci_id->driver_data) अणु
		err = snd_bt87x_detect_card(pci);
		अगर (err < 0)
			वापस -ENODEV;
		boardid = err;
	पूर्ण अन्यथा
		boardid = pci_id->driver_data;

	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;
	अगर (!enable[dev]) अणु
		++dev;
		वापस -ENOENT;
	पूर्ण

	err = snd_card_new(&pci->dev, index[dev], id[dev], THIS_MODULE,
			   0, &card);
	अगर (err < 0)
		वापस err;

	err = snd_bt87x_create(card, pci, &chip);
	अगर (err < 0)
		जाओ _error;

	स_नकल(&chip->board, &snd_bt87x_boards[boardid], माप(chip->board));

	अगर (!chip->board.no_digital) अणु
		अगर (digital_rate[dev] > 0)
			chip->board.dig_rate = digital_rate[dev];

		chip->reg_control |= chip->board.digital_fmt;

		err = snd_bt87x_pcm(chip, DEVICE_DIGITAL, "Bt87x Digital");
		अगर (err < 0)
			जाओ _error;
	पूर्ण
	अगर (!chip->board.no_analog) अणु
		err = snd_bt87x_pcm(chip, DEVICE_ANALOG, "Bt87x Analog");
		अगर (err < 0)
			जाओ _error;
		err = snd_ctl_add(card, snd_ctl_new1(
				  &snd_bt87x_capture_volume, chip));
		अगर (err < 0)
			जाओ _error;
		err = snd_ctl_add(card, snd_ctl_new1(
				  &snd_bt87x_capture_boost, chip));
		अगर (err < 0)
			जाओ _error;
		err = snd_ctl_add(card, snd_ctl_new1(
				  &snd_bt87x_capture_source, chip));
		अगर (err < 0)
			जाओ _error;
	पूर्ण
	dev_info(card->dev, "bt87x%d: Using board %d, %sanalog, %sdigital "
		   "(rate %d Hz)\n", dev, boardid,
		   chip->board.no_analog ? "no " : "",
		   chip->board.no_digital ? "no " : "", chip->board.dig_rate);

	म_नकल(card->driver, "Bt87x");
	प्र_लिखो(card->लघुname, "Brooktree Bt%x", pci->device);
	प्र_लिखो(card->दीर्घname, "%s at %#llx, irq %i",
		card->लघुname, (अचिन्हित दीर्घ दीर्घ)pci_resource_start(pci, 0),
		chip->irq);
	म_नकल(card->mixername, "Bt87x");

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0)
		जाओ _error;

	pci_set_drvdata(pci, card);
	++dev;
	वापस 0;

_error:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

अटल व्योम snd_bt87x_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण

/* शेष entries क्रम all Bt87x cards - it's not exported */
/* driver_data is set to 0 to call detection */
अटल स्थिर काष्ठा pci_device_id snd_bt87x_शेष_ids[] = अणु
	BT_DEVICE(PCI_DEVICE_ID_BROOKTREE_878, PCI_ANY_ID, PCI_ANY_ID, UNKNOWN),
	BT_DEVICE(PCI_DEVICE_ID_BROOKTREE_879, PCI_ANY_ID, PCI_ANY_ID, UNKNOWN),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा pci_driver driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_bt87x_ids,
	.probe = snd_bt87x_probe,
	.हटाओ = snd_bt87x_हटाओ,
पूर्ण;

अटल पूर्णांक __init alsa_card_bt87x_init(व्योम)
अणु
	अगर (load_all)
		driver.id_table = snd_bt87x_शेष_ids;
	वापस pci_रेजिस्टर_driver(&driver);
पूर्ण

अटल व्योम __निकास alsa_card_bt87x_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&driver);
पूर्ण

module_init(alsa_card_bt87x_init)
module_निकास(alsa_card_bt87x_निकास)
