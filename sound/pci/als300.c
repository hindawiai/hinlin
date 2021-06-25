<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  als300.c - driver क्रम Avance Logic ALS300/ALS300+ soundcards.
 *  Copyright (C) 2005 by Ash Willis <ashwillis@programmer.net>
 *
 *  TODO
 *  4 channel playback क्रम ALS300+
 *  gameport
 *  mpu401
 *  opl3
 *
 *  NOTES
 *  The BLOCK_COUNTER रेजिस्टरs क्रम the ALS300(+) वापस a figure related to
 *  the position in the current period, NOT the whole buffer. It is important
 *  to know which period we are in so we can calculate the correct poपूर्णांकer.
 *  This is why we always use 2 periods. We can then use a flip-flop variable
 *  to keep track of what period we are in.
 */

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>

#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/opl3.h>

/* snd_als300_set_irq_flag */
#घोषणा IRQ_DISABLE		0
#घोषणा IRQ_ENABLE		1

/* I/O port layout */
#घोषणा AC97_ACCESS		0x00
#घोषणा AC97_READ		0x04
#घोषणा AC97_STATUS		0x06
#घोषणा   AC97_DATA_AVAIL		(1<<6)
#घोषणा   AC97_BUSY			(1<<7)
#घोषणा ALS300_IRQ_STATUS	0x07		/* ALS300 Only */
#घोषणा   IRQ_PLAYBACK			(1<<3)
#घोषणा   IRQ_CAPTURE			(1<<2)
#घोषणा GCR_DATA		0x08
#घोषणा GCR_INDEX		0x0C
#घोषणा ALS300P_DRAM_IRQ_STATUS	0x0D		/* ALS300+ Only */
#घोषणा MPU_IRQ_STATUS		0x0E		/* ALS300 Rev. E+, ALS300+ */
#घोषणा ALS300P_IRQ_STATUS	0x0F		/* ALS300+ Only */

/* General Control Registers */
#घोषणा PLAYBACK_START		0x80
#घोषणा PLAYBACK_END		0x81
#घोषणा PLAYBACK_CONTROL	0x82
#घोषणा   TRANSFER_START		(1<<16)
#घोषणा   FIFO_PAUSE			(1<<17)
#घोषणा RECORD_START		0x83
#घोषणा RECORD_END		0x84
#घोषणा RECORD_CONTROL		0x85
#घोषणा DRAM_WRITE_CONTROL	0x8B
#घोषणा   WRITE_TRANS_START		(1<<16)
#घोषणा   DRAM_MODE_2			(1<<17)
#घोषणा MISC_CONTROL		0x8C
#घोषणा   IRQ_SET_BIT			(1<<15)
#घोषणा   VMUTE_NORMAL			(1<<20)
#घोषणा   MMUTE_NORMAL			(1<<21)
#घोषणा MUS_VOC_VOL		0x8E
#घोषणा PLAYBACK_BLOCK_COUNTER	0x9A
#घोषणा RECORD_BLOCK_COUNTER	0x9B

#घोषणा DEBUG_PLAY_REC	0

#अगर DEBUG_PLAY_REC
#घोषणा snd_als300_dbgplay(क्रमmat, args...) prपूर्णांकk(KERN_ERR क्रमmat, ##args)
#अन्यथा
#घोषणा snd_als300_dbgplay(क्रमmat, args...)
#पूर्ण_अगर		

क्रमागत अणुDEVICE_ALS300, DEVICE_ALS300_PLUSपूर्ण;

MODULE_AUTHOR("Ash Willis <ashwillis@programmer.net>");
MODULE_DESCRIPTION("Avance Logic ALS300");
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for ALS300 sound card.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for ALS300 sound card.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable ALS300 sound card.");

काष्ठा snd_als300 अणु
	अचिन्हित दीर्घ port;
	spinlock_t reg_lock;
	काष्ठा snd_card *card;
	काष्ठा pci_dev *pci;

	काष्ठा snd_pcm *pcm;
	काष्ठा snd_pcm_substream *playback_substream;
	काष्ठा snd_pcm_substream *capture_substream;

	काष्ठा snd_ac97 *ac97;
	काष्ठा snd_opl3 *opl3;

	काष्ठा resource *res_port;

	पूर्णांक irq;

	पूर्णांक chip_type; /* ALS300 or ALS300+ */

	अक्षर revision;	
पूर्ण;

काष्ठा snd_als300_substream_data अणु
	पूर्णांक period_flipflop;
	पूर्णांक control_रेजिस्टर;
	पूर्णांक block_counter_रेजिस्टर;
पूर्ण;

अटल स्थिर काष्ठा pci_device_id snd_als300_ids[] = अणु
	अणु 0x4005, 0x0300, PCI_ANY_ID, PCI_ANY_ID, 0, 0, DEVICE_ALS300 पूर्ण,
	अणु 0x4005, 0x0308, PCI_ANY_ID, PCI_ANY_ID, 0, 0, DEVICE_ALS300_PLUS पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, snd_als300_ids);

अटल अंतरभूत u32 snd_als300_gcr_पढ़ो(अचिन्हित दीर्घ port, अचिन्हित लघु reg)
अणु
	outb(reg, port+GCR_INDEX);
	वापस inl(port+GCR_DATA);
पूर्ण

अटल अंतरभूत व्योम snd_als300_gcr_ग_लिखो(अचिन्हित दीर्घ port,
						अचिन्हित लघु reg, u32 val)
अणु
	outb(reg, port+GCR_INDEX);
	outl(val, port+GCR_DATA);
पूर्ण

/* Enable/Disable Interrupts */
अटल व्योम snd_als300_set_irq_flag(काष्ठा snd_als300 *chip, पूर्णांक cmd)
अणु
	u32 पंचांगp = snd_als300_gcr_पढ़ो(chip->port, MISC_CONTROL);

	/* boolean XOR check, since old vs. new hardware have
	   directly reversed bit setting क्रम ENABLE and DISABLE.
	   ALS300+ acts like newer versions of ALS300 */
	अगर (((chip->revision > 5 || chip->chip_type == DEVICE_ALS300_PLUS) ^
						(cmd == IRQ_ENABLE)) == 0)
		पंचांगp |= IRQ_SET_BIT;
	अन्यथा
		पंचांगp &= ~IRQ_SET_BIT;
	snd_als300_gcr_ग_लिखो(chip->port, MISC_CONTROL, पंचांगp);
पूर्ण

अटल पूर्णांक snd_als300_मुक्त(काष्ठा snd_als300 *chip)
अणु
	snd_als300_set_irq_flag(chip, IRQ_DISABLE);
	अगर (chip->irq >= 0)
		मुक्त_irq(chip->irq, chip);
	pci_release_regions(chip->pci);
	pci_disable_device(chip->pci);
	kमुक्त(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_als300_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_als300 *chip = device->device_data;
	वापस snd_als300_मुक्त(chip);
पूर्ण

अटल irqवापस_t snd_als300_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	u8 status;
	काष्ठा snd_als300 *chip = dev_id;
	काष्ठा snd_als300_substream_data *data;

	status = inb(chip->port+ALS300_IRQ_STATUS);
	अगर (!status) /* shared IRQ, क्रम dअगरferent device?? Exit ASAP! */
		वापस IRQ_NONE;

	/* ACK everything ASAP */
	outb(status, chip->port+ALS300_IRQ_STATUS);
	अगर (status & IRQ_PLAYBACK) अणु
		अगर (chip->pcm && chip->playback_substream) अणु
			data = chip->playback_substream->runसमय->निजी_data;
			data->period_flipflop ^= 1;
			snd_pcm_period_elapsed(chip->playback_substream);
			snd_als300_dbgplay("IRQ_PLAYBACK\n");
		पूर्ण
	पूर्ण
	अगर (status & IRQ_CAPTURE) अणु
		अगर (chip->pcm && chip->capture_substream) अणु
			data = chip->capture_substream->runसमय->निजी_data;
			data->period_flipflop ^= 1;
			snd_pcm_period_elapsed(chip->capture_substream);
			snd_als300_dbgplay("IRQ_CAPTURE\n");
		पूर्ण
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t snd_als300plus_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	u8 general, mpu, dram;
	काष्ठा snd_als300 *chip = dev_id;
	काष्ठा snd_als300_substream_data *data;
	
	general = inb(chip->port+ALS300P_IRQ_STATUS);
	mpu = inb(chip->port+MPU_IRQ_STATUS);
	dram = inb(chip->port+ALS300P_DRAM_IRQ_STATUS);

	/* shared IRQ, क्रम dअगरferent device?? Exit ASAP! */
	अगर ((general == 0) && ((mpu & 0x80) == 0) && ((dram & 0x01) == 0))
		वापस IRQ_NONE;

	अगर (general & IRQ_PLAYBACK) अणु
		अगर (chip->pcm && chip->playback_substream) अणु
			outb(IRQ_PLAYBACK, chip->port+ALS300P_IRQ_STATUS);
			data = chip->playback_substream->runसमय->निजी_data;
			data->period_flipflop ^= 1;
			snd_pcm_period_elapsed(chip->playback_substream);
			snd_als300_dbgplay("IRQ_PLAYBACK\n");
		पूर्ण
	पूर्ण
	अगर (general & IRQ_CAPTURE) अणु
		अगर (chip->pcm && chip->capture_substream) अणु
			outb(IRQ_CAPTURE, chip->port+ALS300P_IRQ_STATUS);
			data = chip->capture_substream->runसमय->निजी_data;
			data->period_flipflop ^= 1;
			snd_pcm_period_elapsed(chip->capture_substream);
			snd_als300_dbgplay("IRQ_CAPTURE\n");
		पूर्ण
	पूर्ण
	/* FIXME: Ack other पूर्णांकerrupt types. Not important right now as
	 * those other devices aren't enabled. */
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम snd_als300_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण

अटल अचिन्हित लघु snd_als300_ac97_पढ़ो(काष्ठा snd_ac97 *ac97,
							अचिन्हित लघु reg)
अणु
	पूर्णांक i;
	काष्ठा snd_als300 *chip = ac97->निजी_data;

	क्रम (i = 0; i < 1000; i++) अणु
		अगर ((inb(chip->port+AC97_STATUS) & (AC97_BUSY)) == 0)
			अवरोध;
		udelay(10);
	पूर्ण
	outl((reg << 24) | (1 << 31), chip->port+AC97_ACCESS);

	क्रम (i = 0; i < 1000; i++) अणु
		अगर ((inb(chip->port+AC97_STATUS) & (AC97_DATA_AVAIL)) != 0)
			अवरोध;
		udelay(10);
	पूर्ण
	वापस inw(chip->port+AC97_READ);
पूर्ण

अटल व्योम snd_als300_ac97_ग_लिखो(काष्ठा snd_ac97 *ac97,
				अचिन्हित लघु reg, अचिन्हित लघु val)
अणु
	पूर्णांक i;
	काष्ठा snd_als300 *chip = ac97->निजी_data;

	क्रम (i = 0; i < 1000; i++) अणु
		अगर ((inb(chip->port+AC97_STATUS) & (AC97_BUSY)) == 0)
			अवरोध;
		udelay(10);
	पूर्ण
	outl((reg << 24) | val, chip->port+AC97_ACCESS);
पूर्ण

अटल पूर्णांक snd_als300_ac97(काष्ठा snd_als300 *chip)
अणु
	काष्ठा snd_ac97_bus *bus;
	काष्ठा snd_ac97_ढाँचा ac97;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_ac97_bus_ops ops = अणु
		.ग_लिखो = snd_als300_ac97_ग_लिखो,
		.पढ़ो = snd_als300_ac97_पढ़ो,
	पूर्ण;

	अगर ((err = snd_ac97_bus(chip->card, 0, &ops, शून्य, &bus)) < 0)
		वापस err;

	स_रखो(&ac97, 0, माप(ac97));
	ac97.निजी_data = chip;

	वापस snd_ac97_mixer(bus, &ac97, &chip->ac97);
पूर्ण

/* hardware definition
 *
 * In AC97 mode, we always use 48k/16bit/stereo.
 * Any request to change data type is ignored by
 * the card when it is running outside of legacy
 * mode.
 */
अटल स्थिर काष्ठा snd_pcm_hardware snd_als300_playback_hw =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP |
				SNDRV_PCM_INFO_INTERLEAVED |
				SNDRV_PCM_INFO_PAUSE |
				SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =		SNDRV_PCM_FMTBIT_S16,
	.rates =		SNDRV_PCM_RATE_48000,
	.rate_min =		48000,
	.rate_max =		48000,
	.channels_min =		2,
	.channels_max =		2,
	.buffer_bytes_max =	64 * 1024,
	.period_bytes_min =	64,
	.period_bytes_max =	32 * 1024,
	.periods_min =		2,
	.periods_max =		2,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_als300_capture_hw =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP |
				SNDRV_PCM_INFO_INTERLEAVED |
				SNDRV_PCM_INFO_PAUSE |
				SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =		SNDRV_PCM_FMTBIT_S16,
	.rates =		SNDRV_PCM_RATE_48000,
	.rate_min =		48000,
	.rate_max =		48000,
	.channels_min =		2,
	.channels_max =		2,
	.buffer_bytes_max =	64 * 1024,
	.period_bytes_min =	64,
	.period_bytes_max =	32 * 1024,
	.periods_min =		2,
	.periods_max =		2,
पूर्ण;

अटल पूर्णांक snd_als300_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_als300 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_als300_substream_data *data = kzalloc(माप(*data),
								GFP_KERNEL);

	अगर (!data)
		वापस -ENOMEM;
	chip->playback_substream = substream;
	runसमय->hw = snd_als300_playback_hw;
	runसमय->निजी_data = data;
	data->control_रेजिस्टर = PLAYBACK_CONTROL;
	data->block_counter_रेजिस्टर = PLAYBACK_BLOCK_COUNTER;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_als300_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_als300 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_als300_substream_data *data;

	data = substream->runसमय->निजी_data;
	kमुक्त(data);
	chip->playback_substream = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_als300_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_als300 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_als300_substream_data *data = kzalloc(माप(*data),
								GFP_KERNEL);

	अगर (!data)
		वापस -ENOMEM;
	chip->capture_substream = substream;
	runसमय->hw = snd_als300_capture_hw;
	runसमय->निजी_data = data;
	data->control_रेजिस्टर = RECORD_CONTROL;
	data->block_counter_रेजिस्टर = RECORD_BLOCK_COUNTER;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_als300_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_als300 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_als300_substream_data *data;

	data = substream->runसमय->निजी_data;
	kमुक्त(data);
	chip->capture_substream = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_als300_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	u32 पंचांगp;
	काष्ठा snd_als300 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित लघु period_bytes = snd_pcm_lib_period_bytes(substream);
	अचिन्हित लघु buffer_bytes = snd_pcm_lib_buffer_bytes(substream);
	
	spin_lock_irq(&chip->reg_lock);
	पंचांगp = snd_als300_gcr_पढ़ो(chip->port, PLAYBACK_CONTROL);
	पंचांगp &= ~TRANSFER_START;

	snd_als300_dbgplay("Period bytes: %d Buffer bytes %d\n",
						period_bytes, buffer_bytes);
	
	/* set block size */
	पंचांगp &= 0xffff0000;
	पंचांगp |= period_bytes - 1;
	snd_als300_gcr_ग_लिखो(chip->port, PLAYBACK_CONTROL, पंचांगp);

	/* set dma area */
	snd_als300_gcr_ग_लिखो(chip->port, PLAYBACK_START,
					runसमय->dma_addr);
	snd_als300_gcr_ग_लिखो(chip->port, PLAYBACK_END,
					runसमय->dma_addr + buffer_bytes - 1);
	spin_unlock_irq(&chip->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_als300_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	u32 पंचांगp;
	काष्ठा snd_als300 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित लघु period_bytes = snd_pcm_lib_period_bytes(substream);
	अचिन्हित लघु buffer_bytes = snd_pcm_lib_buffer_bytes(substream);

	spin_lock_irq(&chip->reg_lock);
	पंचांगp = snd_als300_gcr_पढ़ो(chip->port, RECORD_CONTROL);
	पंचांगp &= ~TRANSFER_START;

	snd_als300_dbgplay("Period bytes: %d Buffer bytes %d\n", period_bytes,
							buffer_bytes);

	/* set block size */
	पंचांगp &= 0xffff0000;
	पंचांगp |= period_bytes - 1;

	/* set dma area */
	snd_als300_gcr_ग_लिखो(chip->port, RECORD_CONTROL, पंचांगp);
	snd_als300_gcr_ग_लिखो(chip->port, RECORD_START,
					runसमय->dma_addr);
	snd_als300_gcr_ग_लिखो(chip->port, RECORD_END,
					runसमय->dma_addr + buffer_bytes - 1);
	spin_unlock_irq(&chip->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_als300_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_als300 *chip = snd_pcm_substream_chip(substream);
	u32 पंचांगp;
	काष्ठा snd_als300_substream_data *data;
	अचिन्हित लघु reg;
	पूर्णांक ret = 0;

	data = substream->runसमय->निजी_data;
	reg = data->control_रेजिस्टर;

	spin_lock(&chip->reg_lock);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		पंचांगp = snd_als300_gcr_पढ़ो(chip->port, reg);
		data->period_flipflop = 1;
		snd_als300_gcr_ग_लिखो(chip->port, reg, पंचांगp | TRANSFER_START);
		snd_als300_dbgplay("TRIGGER START\n");
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		पंचांगp = snd_als300_gcr_पढ़ो(chip->port, reg);
		snd_als300_gcr_ग_लिखो(chip->port, reg, पंचांगp & ~TRANSFER_START);
		snd_als300_dbgplay("TRIGGER STOP\n");
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		पंचांगp = snd_als300_gcr_पढ़ो(chip->port, reg);
		snd_als300_gcr_ग_लिखो(chip->port, reg, पंचांगp | FIFO_PAUSE);
		snd_als300_dbgplay("TRIGGER PAUSE\n");
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		पंचांगp = snd_als300_gcr_पढ़ो(chip->port, reg);
		snd_als300_gcr_ग_लिखो(chip->port, reg, पंचांगp & ~FIFO_PAUSE);
		snd_als300_dbgplay("TRIGGER RELEASE\n");
		अवरोध;
	शेष:
		snd_als300_dbgplay("TRIGGER INVALID\n");
		ret = -EINVAL;
	पूर्ण
	spin_unlock(&chip->reg_lock);
	वापस ret;
पूर्ण

अटल snd_pcm_uframes_t snd_als300_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	u16 current_ptr;
	काष्ठा snd_als300 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_als300_substream_data *data;
	अचिन्हित लघु period_bytes;

	data = substream->runसमय->निजी_data;
	period_bytes = snd_pcm_lib_period_bytes(substream);
	
	spin_lock(&chip->reg_lock);
	current_ptr = (u16) snd_als300_gcr_पढ़ो(chip->port,
					data->block_counter_रेजिस्टर) + 4;
	spin_unlock(&chip->reg_lock);
	अगर (current_ptr > period_bytes)
		current_ptr = 0;
	अन्यथा
		current_ptr = period_bytes - current_ptr;

	अगर (data->period_flipflop == 0)
		current_ptr += period_bytes;
	snd_als300_dbgplay("Pointer (bytes): %d\n", current_ptr);
	वापस bytes_to_frames(substream->runसमय, current_ptr);
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_als300_playback_ops = अणु
	.खोलो =		snd_als300_playback_खोलो,
	.बंद =	snd_als300_playback_बंद,
	.prepare =	snd_als300_playback_prepare,
	.trigger =	snd_als300_trigger,
	.poपूर्णांकer =	snd_als300_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_als300_capture_ops = अणु
	.खोलो =		snd_als300_capture_खोलो,
	.बंद =	snd_als300_capture_बंद,
	.prepare =	snd_als300_capture_prepare,
	.trigger =	snd_als300_trigger,
	.poपूर्णांकer =	snd_als300_poपूर्णांकer,
पूर्ण;

अटल पूर्णांक snd_als300_new_pcm(काष्ठा snd_als300 *chip)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	err = snd_pcm_new(chip->card, "ALS300", 0, 1, 1, &pcm);
	अगर (err < 0)
		वापस err;
	pcm->निजी_data = chip;
	म_नकल(pcm->name, "ALS300");
	chip->pcm = pcm;

	/* set चालकs */
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK,
				&snd_als300_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE,
				&snd_als300_capture_ops);

	/* pre-allocation of buffers */
	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV, &chip->pci->dev,
				       64*1024, 64*1024);
	वापस 0;
पूर्ण

अटल व्योम snd_als300_init(काष्ठा snd_als300 *chip)
अणु
	अचिन्हित दीर्घ flags;
	u32 पंचांगp;
	
	spin_lock_irqsave(&chip->reg_lock, flags);
	chip->revision = (snd_als300_gcr_पढ़ो(chip->port, MISC_CONTROL) >> 16)
								& 0x0000000F;
	/* Setup DRAM */
	पंचांगp = snd_als300_gcr_पढ़ो(chip->port, DRAM_WRITE_CONTROL);
	snd_als300_gcr_ग_लिखो(chip->port, DRAM_WRITE_CONTROL,
						(पंचांगp | DRAM_MODE_2)
						& ~WRITE_TRANS_START);

	/* Enable IRQ output */
	snd_als300_set_irq_flag(chip, IRQ_ENABLE);

	/* Unmute hardware devices so their outमाला_दो get routed to
	 * the onboard mixer */
	पंचांगp = snd_als300_gcr_पढ़ो(chip->port, MISC_CONTROL);
	snd_als300_gcr_ग_लिखो(chip->port, MISC_CONTROL,
			पंचांगp | VMUTE_NORMAL | MMUTE_NORMAL);

	/* Reset volumes */
	snd_als300_gcr_ग_लिखो(chip->port, MUS_VOC_VOL, 0);

	/* Make sure playback transfer is stopped */
	पंचांगp = snd_als300_gcr_पढ़ो(chip->port, PLAYBACK_CONTROL);
	snd_als300_gcr_ग_लिखो(chip->port, PLAYBACK_CONTROL,
			पंचांगp & ~TRANSFER_START);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
पूर्ण

अटल पूर्णांक snd_als300_create(काष्ठा snd_card *card,
			     काष्ठा pci_dev *pci, पूर्णांक chip_type,
			     काष्ठा snd_als300 **rchip)
अणु
	काष्ठा snd_als300 *chip;
	व्योम *irq_handler;
	पूर्णांक err;

	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त = snd_als300_dev_मुक्त,
	पूर्ण;
	*rchip = शून्य;

	अगर ((err = pci_enable_device(pci)) < 0)
		वापस err;

	अगर (dma_set_mask_and_coherent(&pci->dev, DMA_BIT_MASK(28))) अणु
		dev_err(card->dev, "error setting 28bit DMA mask\n");
		pci_disable_device(pci);
		वापस -ENXIO;
	पूर्ण
	pci_set_master(pci);

	chip = kzalloc(माप(*chip), GFP_KERNEL);
	अगर (chip == शून्य) अणु
		pci_disable_device(pci);
		वापस -ENOMEM;
	पूर्ण

	chip->card = card;
	chip->pci = pci;
	chip->irq = -1;
	chip->chip_type = chip_type;
	spin_lock_init(&chip->reg_lock);

	अगर ((err = pci_request_regions(pci, "ALS300")) < 0) अणु
		kमुक्त(chip);
		pci_disable_device(pci);
		वापस err;
	पूर्ण
	chip->port = pci_resource_start(pci, 0);

	अगर (chip->chip_type == DEVICE_ALS300_PLUS)
		irq_handler = snd_als300plus_पूर्णांकerrupt;
	अन्यथा
		irq_handler = snd_als300_पूर्णांकerrupt;

	अगर (request_irq(pci->irq, irq_handler, IRQF_SHARED,
			KBUILD_MODNAME, chip)) अणु
		dev_err(card->dev, "unable to grab IRQ %d\n", pci->irq);
		snd_als300_मुक्त(chip);
		वापस -EBUSY;
	पूर्ण
	chip->irq = pci->irq;
	card->sync_irq = chip->irq;

	snd_als300_init(chip);

	err = snd_als300_ac97(chip);
	अगर (err < 0) अणु
		dev_err(card->dev, "Could not create ac97\n");
		snd_als300_मुक्त(chip);
		वापस err;
	पूर्ण

	अगर ((err = snd_als300_new_pcm(chip)) < 0) अणु
		dev_err(card->dev, "Could not create PCM\n");
		snd_als300_मुक्त(chip);
		वापस err;
	पूर्ण

	अगर ((err = snd_device_new(card, SNDRV_DEV_LOWLEVEL,
						chip, &ops)) < 0) अणु
		snd_als300_मुक्त(chip);
		वापस err;
	पूर्ण

	*rchip = chip;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक snd_als300_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा snd_als300 *chip = card->निजी_data;

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);
	snd_ac97_suspend(chip->ac97);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_als300_resume(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा snd_als300 *chip = card->निजी_data;

	snd_als300_init(chip);
	snd_ac97_resume(chip->ac97);

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(snd_als300_pm, snd_als300_suspend, snd_als300_resume);
#घोषणा SND_ALS300_PM_OPS	&snd_als300_pm
#अन्यथा
#घोषणा SND_ALS300_PM_OPS	शून्य
#पूर्ण_अगर

अटल पूर्णांक snd_als300_probe(काष्ठा pci_dev *pci,
                             स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_card *card;
	काष्ठा snd_als300 *chip;
	पूर्णांक err, chip_type;

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

	chip_type = pci_id->driver_data;

	अगर ((err = snd_als300_create(card, pci, chip_type, &chip)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	card->निजी_data = chip;

	म_नकल(card->driver, "ALS300");
	अगर (chip->chip_type == DEVICE_ALS300_PLUS)
		/* करोn't know much about ALS300+ yet
		 * prपूर्णांक revision number क्रम now */
		प्र_लिखो(card->लघुname, "ALS300+ (Rev. %d)", chip->revision);
	अन्यथा
		प्र_लिखो(card->लघुname, "ALS300 (Rev. %c)", 'A' +
							chip->revision - 1);
	प्र_लिखो(card->दीर्घname, "%s at 0x%lx irq %i",
				card->लघुname, chip->port, chip->irq);

	अगर ((err = snd_card_रेजिस्टर(card)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	pci_set_drvdata(pci, card);
	dev++;
	वापस 0;
पूर्ण

अटल काष्ठा pci_driver als300_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_als300_ids,
	.probe = snd_als300_probe,
	.हटाओ = snd_als300_हटाओ,
	.driver = अणु
		.pm = SND_ALS300_PM_OPS,
	पूर्ण,
पूर्ण;

module_pci_driver(als300_driver);
