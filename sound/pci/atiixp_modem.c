<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA driver क्रम ATI IXP 150/200/250 AC97 modem controllers
 *
 *	Copyright (c) 2004 Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/info.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/initval.h>

MODULE_AUTHOR("Takashi Iwai <tiwai@suse.de>");
MODULE_DESCRIPTION("ATI IXP MC97 controller");
MODULE_LICENSE("GPL");

अटल पूर्णांक index = -2; /* Exclude the first card */
अटल अक्षर *id = SNDRV_DEFAULT_STR1;	/* ID क्रम this card */
अटल पूर्णांक ac97_घड़ी = 48000;

module_param(index, पूर्णांक, 0444);
MODULE_PARM_DESC(index, "Index value for ATI IXP controller.");
module_param(id, अक्षरp, 0444);
MODULE_PARM_DESC(id, "ID string for ATI IXP controller.");
module_param(ac97_घड़ी, पूर्णांक, 0444);
MODULE_PARM_DESC(ac97_घड़ी, "AC'97 codec clock (default 48000Hz).");

/* just क्रम backward compatibility */
अटल bool enable;
module_param(enable, bool, 0444);


/*
 */

#घोषणा ATI_REG_ISR			0x00	/* पूर्णांकerrupt source */
#घोषणा  ATI_REG_ISR_MODEM_IN_XRUN	(1U<<0)
#घोषणा  ATI_REG_ISR_MODEM_IN_STATUS	(1U<<1)
#घोषणा  ATI_REG_ISR_MODEM_OUT1_XRUN	(1U<<2)
#घोषणा  ATI_REG_ISR_MODEM_OUT1_STATUS	(1U<<3)
#घोषणा  ATI_REG_ISR_MODEM_OUT2_XRUN	(1U<<4)
#घोषणा  ATI_REG_ISR_MODEM_OUT2_STATUS	(1U<<5)
#घोषणा  ATI_REG_ISR_MODEM_OUT3_XRUN	(1U<<6)
#घोषणा  ATI_REG_ISR_MODEM_OUT3_STATUS	(1U<<7)
#घोषणा  ATI_REG_ISR_PHYS_INTR		(1U<<8)
#घोषणा  ATI_REG_ISR_PHYS_MISMATCH	(1U<<9)
#घोषणा  ATI_REG_ISR_CODEC0_NOT_READY	(1U<<10)
#घोषणा  ATI_REG_ISR_CODEC1_NOT_READY	(1U<<11)
#घोषणा  ATI_REG_ISR_CODEC2_NOT_READY	(1U<<12)
#घोषणा  ATI_REG_ISR_NEW_FRAME		(1U<<13)
#घोषणा  ATI_REG_ISR_MODEM_GPIO_DATA	(1U<<14)

#घोषणा ATI_REG_IER			0x04	/* पूर्णांकerrupt enable */
#घोषणा  ATI_REG_IER_MODEM_IN_XRUN_EN	(1U<<0)
#घोषणा  ATI_REG_IER_MODEM_STATUS_EN	(1U<<1)
#घोषणा  ATI_REG_IER_MODEM_OUT1_XRUN_EN	(1U<<2)
#घोषणा  ATI_REG_IER_MODEM_OUT2_XRUN_EN	(1U<<4)
#घोषणा  ATI_REG_IER_MODEM_OUT3_XRUN_EN	(1U<<6)
#घोषणा  ATI_REG_IER_PHYS_INTR_EN	(1U<<8)
#घोषणा  ATI_REG_IER_PHYS_MISMATCH_EN	(1U<<9)
#घोषणा  ATI_REG_IER_CODEC0_INTR_EN	(1U<<10)
#घोषणा  ATI_REG_IER_CODEC1_INTR_EN	(1U<<11)
#घोषणा  ATI_REG_IER_CODEC2_INTR_EN	(1U<<12)
#घोषणा  ATI_REG_IER_NEW_FRAME_EN	(1U<<13)	/* (RO */
#घोषणा  ATI_REG_IER_MODEM_GPIO_DATA_EN	(1U<<14)	/* (WO) modem is running */
#घोषणा  ATI_REG_IER_MODEM_SET_BUS_BUSY	(1U<<15)

#घोषणा ATI_REG_CMD			0x08	/* command */
#घोषणा  ATI_REG_CMD_POWERDOWN	(1U<<0)
#घोषणा  ATI_REG_CMD_MODEM_RECEIVE_EN	(1U<<1)	/* modem only */
#घोषणा  ATI_REG_CMD_MODEM_SEND1_EN	(1U<<2)	/* modem only */
#घोषणा  ATI_REG_CMD_MODEM_SEND2_EN	(1U<<3)	/* modem only */
#घोषणा  ATI_REG_CMD_MODEM_SEND3_EN	(1U<<4)	/* modem only */
#घोषणा  ATI_REG_CMD_MODEM_STATUS_MEM	(1U<<5)	/* modem only */
#घोषणा  ATI_REG_CMD_MODEM_IN_DMA_EN	(1U<<8)	/* modem only */
#घोषणा  ATI_REG_CMD_MODEM_OUT_DMA1_EN	(1U<<9)	/* modem only */
#घोषणा  ATI_REG_CMD_MODEM_OUT_DMA2_EN	(1U<<10)	/* modem only */
#घोषणा  ATI_REG_CMD_MODEM_OUT_DMA3_EN	(1U<<11)	/* modem only */
#घोषणा  ATI_REG_CMD_AUDIO_PRESENT	(1U<<20)
#घोषणा  ATI_REG_CMD_MODEM_GPIO_THRU_DMA	(1U<<22)	/* modem only */
#घोषणा  ATI_REG_CMD_LOOPBACK_EN	(1U<<23)
#घोषणा  ATI_REG_CMD_PACKED_DIS		(1U<<24)
#घोषणा  ATI_REG_CMD_BURST_EN		(1U<<25)
#घोषणा  ATI_REG_CMD_PANIC_EN		(1U<<26)
#घोषणा  ATI_REG_CMD_MODEM_PRESENT	(1U<<27)
#घोषणा  ATI_REG_CMD_ACLINK_ACTIVE	(1U<<28)
#घोषणा  ATI_REG_CMD_AC_SOFT_RESET	(1U<<29)
#घोषणा  ATI_REG_CMD_AC_SYNC		(1U<<30)
#घोषणा  ATI_REG_CMD_AC_RESET		(1U<<31)

#घोषणा ATI_REG_PHYS_OUT_ADDR		0x0c
#घोषणा  ATI_REG_PHYS_OUT_CODEC_MASK	(3U<<0)
#घोषणा  ATI_REG_PHYS_OUT_RW		(1U<<2)
#घोषणा  ATI_REG_PHYS_OUT_ADDR_EN	(1U<<8)
#घोषणा  ATI_REG_PHYS_OUT_ADDR_SHIFT	9
#घोषणा  ATI_REG_PHYS_OUT_DATA_SHIFT	16

#घोषणा ATI_REG_PHYS_IN_ADDR		0x10
#घोषणा  ATI_REG_PHYS_IN_READ_FLAG	(1U<<8)
#घोषणा  ATI_REG_PHYS_IN_ADDR_SHIFT	9
#घोषणा  ATI_REG_PHYS_IN_DATA_SHIFT	16

#घोषणा ATI_REG_SLOTREQ			0x14

#घोषणा ATI_REG_COUNTER			0x18
#घोषणा  ATI_REG_COUNTER_SLOT		(3U<<0)	/* slot # */
#घोषणा  ATI_REG_COUNTER_BITCLOCK	(31U<<8)

#घोषणा ATI_REG_IN_FIFO_THRESHOLD	0x1c

#घोषणा ATI_REG_MODEM_IN_DMA_LINKPTR	0x20
#घोषणा ATI_REG_MODEM_IN_DMA_DT_START	0x24	/* RO */
#घोषणा ATI_REG_MODEM_IN_DMA_DT_NEXT	0x28	/* RO */
#घोषणा ATI_REG_MODEM_IN_DMA_DT_CUR	0x2c	/* RO */
#घोषणा ATI_REG_MODEM_IN_DMA_DT_SIZE	0x30
#घोषणा ATI_REG_MODEM_OUT_FIFO		0x34	/* output threshold */
#घोषणा  ATI_REG_MODEM_OUT1_DMA_THRESHOLD_MASK	(0xf<<16)
#घोषणा  ATI_REG_MODEM_OUT1_DMA_THRESHOLD_SHIFT	16
#घोषणा ATI_REG_MODEM_OUT_DMA1_LINKPTR	0x38
#घोषणा ATI_REG_MODEM_OUT_DMA2_LINKPTR	0x3c
#घोषणा ATI_REG_MODEM_OUT_DMA3_LINKPTR	0x40
#घोषणा ATI_REG_MODEM_OUT_DMA1_DT_START	0x44
#घोषणा ATI_REG_MODEM_OUT_DMA1_DT_NEXT	0x48
#घोषणा ATI_REG_MODEM_OUT_DMA1_DT_CUR	0x4c
#घोषणा ATI_REG_MODEM_OUT_DMA2_DT_START	0x50
#घोषणा ATI_REG_MODEM_OUT_DMA2_DT_NEXT	0x54
#घोषणा ATI_REG_MODEM_OUT_DMA2_DT_CUR	0x58
#घोषणा ATI_REG_MODEM_OUT_DMA3_DT_START	0x5c
#घोषणा ATI_REG_MODEM_OUT_DMA3_DT_NEXT	0x60
#घोषणा ATI_REG_MODEM_OUT_DMA3_DT_CUR	0x64
#घोषणा ATI_REG_MODEM_OUT_DMA12_DT_SIZE	0x68
#घोषणा ATI_REG_MODEM_OUT_DMA3_DT_SIZE	0x6c
#घोषणा ATI_REG_MODEM_OUT_FIFO_USED     0x70
#घोषणा ATI_REG_MODEM_OUT_GPIO		0x74
#घोषणा  ATI_REG_MODEM_OUT_GPIO_EN	   1
#घोषणा  ATI_REG_MODEM_OUT_GPIO_DATA_SHIFT 5
#घोषणा ATI_REG_MODEM_IN_GPIO		0x78

#घोषणा ATI_REG_MODEM_MIRROR		0x7c
#घोषणा ATI_REG_AUDIO_MIRROR		0x80

#घोषणा ATI_REG_MODEM_FIFO_FLUSH	0x88
#घोषणा  ATI_REG_MODEM_FIFO_OUT1_FLUSH	(1U<<0)
#घोषणा  ATI_REG_MODEM_FIFO_OUT2_FLUSH	(1U<<1)
#घोषणा  ATI_REG_MODEM_FIFO_OUT3_FLUSH	(1U<<2)
#घोषणा  ATI_REG_MODEM_FIFO_IN_FLUSH	(1U<<3)

/* LINKPTR */
#घोषणा  ATI_REG_LINKPTR_EN		(1U<<0)

#घोषणा ATI_MAX_DESCRIPTORS	256	/* max number of descriptor packets */


काष्ठा atiixp_modem;

/*
 * DMA packate descriptor
 */

काष्ठा atiixp_dma_desc अणु
	__le32 addr;	/* DMA buffer address */
	u16 status;	/* status bits */
	u16 size;	/* size of the packet in dwords */
	__le32 next;	/* address of the next packet descriptor */
पूर्ण;

/*
 * stream क्रमागत
 */
क्रमागत अणु ATI_DMA_PLAYBACK, ATI_DMA_CAPTURE, NUM_ATI_DMAS पूर्ण; /* DMAs */
क्रमागत अणु ATI_PCM_OUT, ATI_PCM_IN, NUM_ATI_PCMS पूर्ण; /* AC97 pcm slots */
क्रमागत अणु ATI_PCMDEV_ANALOG, NUM_ATI_PCMDEVS पूर्ण; /* pcm devices */

#घोषणा NUM_ATI_CODECS	3


/*
 * स्थिरants and callbacks क्रम each DMA type
 */
काष्ठा atiixp_dma_ops अणु
	पूर्णांक type;			/* ATI_DMA_XXX */
	अचिन्हित पूर्णांक llp_offset;	/* LINKPTR offset */
	अचिन्हित पूर्णांक dt_cur;		/* DT_CUR offset */
	/* called from खोलो callback */
	व्योम (*enable_dma)(काष्ठा atiixp_modem *chip, पूर्णांक on);
	/* called from trigger (START/STOP) */
	व्योम (*enable_transfer)(काष्ठा atiixp_modem *chip, पूर्णांक on);
 	/* called from trigger (STOP only) */
	व्योम (*flush_dma)(काष्ठा atiixp_modem *chip);
पूर्ण;

/*
 * DMA stream
 */
काष्ठा atiixp_dma अणु
	स्थिर काष्ठा atiixp_dma_ops *ops;
	काष्ठा snd_dma_buffer desc_buf;
	काष्ठा snd_pcm_substream *substream;	/* asचिन्हित PCM substream */
	अचिन्हित पूर्णांक buf_addr, buf_bytes;	/* DMA buffer address, bytes */
	अचिन्हित पूर्णांक period_bytes, periods;
	पूर्णांक खोलोed;
	पूर्णांक running;
	पूर्णांक pcm_खोलो_flag;
	पूर्णांक ac97_pcm_type;	/* index # of ac97_pcm to access, -1 = not used */
पूर्ण;

/*
 * ATI IXP chip
 */
काष्ठा atiixp_modem अणु
	काष्ठा snd_card *card;
	काष्ठा pci_dev *pci;

	काष्ठा resource *res;		/* memory i/o */
	अचिन्हित दीर्घ addr;
	व्योम __iomem *remap_addr;
	पूर्णांक irq;
	
	काष्ठा snd_ac97_bus *ac97_bus;
	काष्ठा snd_ac97 *ac97[NUM_ATI_CODECS];

	spinlock_t reg_lock;

	काष्ठा atiixp_dma dmas[NUM_ATI_DMAS];
	काष्ठा ac97_pcm *pcms[NUM_ATI_PCMS];
	काष्ठा snd_pcm *pcmdevs[NUM_ATI_PCMDEVS];

	पूर्णांक max_channels;		/* max. channels क्रम PCM out */

	अचिन्हित पूर्णांक codec_not_पढ़ोy_bits;	/* क्रम codec detection */

	पूर्णांक spdअगर_over_aclink;		/* passed from the module option */
	काष्ठा mutex खोलो_mutex;	/* playback खोलो mutex */
पूर्ण;


/*
 */
अटल स्थिर काष्ठा pci_device_id snd_atiixp_ids[] = अणु
	अणु PCI_VDEVICE(ATI, 0x434d), 0 पूर्ण, /* SB200 */
	अणु PCI_VDEVICE(ATI, 0x4378), 0 पूर्ण, /* SB400 */
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, snd_atiixp_ids);


/*
 * lowlevel functions
 */

/*
 * update the bits of the given रेजिस्टर.
 * वापस 1 अगर the bits changed.
 */
अटल पूर्णांक snd_atiixp_update_bits(काष्ठा atiixp_modem *chip, अचिन्हित पूर्णांक reg,
				  अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक value)
अणु
	व्योम __iomem *addr = chip->remap_addr + reg;
	अचिन्हित पूर्णांक data, old_data;
	old_data = data = पढ़ोl(addr);
	data &= ~mask;
	data |= value;
	अगर (old_data == data)
		वापस 0;
	ग_लिखोl(data, addr);
	वापस 1;
पूर्ण

/*
 * macros क्रम easy use
 */
#घोषणा atiixp_ग_लिखो(chip,reg,value) \
	ग_लिखोl(value, chip->remap_addr + ATI_REG_##reg)
#घोषणा atiixp_पढ़ो(chip,reg) \
	पढ़ोl(chip->remap_addr + ATI_REG_##reg)
#घोषणा atiixp_update(chip,reg,mask,val) \
	snd_atiixp_update_bits(chip, ATI_REG_##reg, mask, val)

/*
 * handling DMA packets
 *
 * we allocate a linear buffer क्रम the DMA, and split it to  each packet.
 * in a future version, a scatter-gather buffer should be implemented.
 */

#घोषणा ATI_DESC_LIST_SIZE \
	PAGE_ALIGN(ATI_MAX_DESCRIPTORS * माप(काष्ठा atiixp_dma_desc))

/*
 * build packets ring क्रम the given buffer size.
 *
 * IXP handles the buffer descriptors, which are connected as a linked
 * list.  although we can change the list dynamically, in this version,
 * a अटल RING of buffer descriptors is used.
 *
 * the ring is built in this function, and is set up to the hardware. 
 */
अटल पूर्णांक atiixp_build_dma_packets(काष्ठा atiixp_modem *chip,
				    काष्ठा atiixp_dma *dma,
				    काष्ठा snd_pcm_substream *substream,
				    अचिन्हित पूर्णांक periods,
				    अचिन्हित पूर्णांक period_bytes)
अणु
	अचिन्हित पूर्णांक i;
	u32 addr, desc_addr;
	अचिन्हित दीर्घ flags;

	अगर (periods > ATI_MAX_DESCRIPTORS)
		वापस -ENOMEM;

	अगर (dma->desc_buf.area == शून्य) अणु
		अगर (snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, &chip->pci->dev,
					ATI_DESC_LIST_SIZE, &dma->desc_buf) < 0)
			वापस -ENOMEM;
		dma->period_bytes = dma->periods = 0; /* clear */
	पूर्ण

	अगर (dma->periods == periods && dma->period_bytes == period_bytes)
		वापस 0;

	/* reset DMA beक्रमe changing the descriptor table */
	spin_lock_irqsave(&chip->reg_lock, flags);
	ग_लिखोl(0, chip->remap_addr + dma->ops->llp_offset);
	dma->ops->enable_dma(chip, 0);
	dma->ops->enable_dma(chip, 1);
	spin_unlock_irqrestore(&chip->reg_lock, flags);

	/* fill the entries */
	addr = (u32)substream->runसमय->dma_addr;
	desc_addr = (u32)dma->desc_buf.addr;
	क्रम (i = 0; i < periods; i++) अणु
		काष्ठा atiixp_dma_desc *desc;
		desc = &((काष्ठा atiixp_dma_desc *)dma->desc_buf.area)[i];
		desc->addr = cpu_to_le32(addr);
		desc->status = 0;
		desc->size = period_bytes >> 2; /* in dwords */
		desc_addr += माप(काष्ठा atiixp_dma_desc);
		अगर (i == periods - 1)
			desc->next = cpu_to_le32((u32)dma->desc_buf.addr);
		अन्यथा
			desc->next = cpu_to_le32(desc_addr);
		addr += period_bytes;
	पूर्ण

	ग_लिखोl((u32)dma->desc_buf.addr | ATI_REG_LINKPTR_EN,
	       chip->remap_addr + dma->ops->llp_offset);

	dma->period_bytes = period_bytes;
	dma->periods = periods;

	वापस 0;
पूर्ण

/*
 * हटाओ the ring buffer and release it अगर asचिन्हित
 */
अटल व्योम atiixp_clear_dma_packets(काष्ठा atiixp_modem *chip,
				     काष्ठा atiixp_dma *dma,
				     काष्ठा snd_pcm_substream *substream)
अणु
	अगर (dma->desc_buf.area) अणु
		ग_लिखोl(0, chip->remap_addr + dma->ops->llp_offset);
		snd_dma_मुक्त_pages(&dma->desc_buf);
		dma->desc_buf.area = शून्य;
	पूर्ण
पूर्ण

/*
 * AC97 पूर्णांकerface
 */
अटल पूर्णांक snd_atiixp_acquire_codec(काष्ठा atiixp_modem *chip)
अणु
	पूर्णांक समयout = 1000;

	जबतक (atiixp_पढ़ो(chip, PHYS_OUT_ADDR) & ATI_REG_PHYS_OUT_ADDR_EN) अणु
		अगर (! समयout--) अणु
			dev_warn(chip->card->dev, "codec acquire timeout\n");
			वापस -EBUSY;
		पूर्ण
		udelay(1);
	पूर्ण
	वापस 0;
पूर्ण

अटल अचिन्हित लघु snd_atiixp_codec_पढ़ो(काष्ठा atiixp_modem *chip,
					    अचिन्हित लघु codec,
					    अचिन्हित लघु reg)
अणु
	अचिन्हित पूर्णांक data;
	पूर्णांक समयout;

	अगर (snd_atiixp_acquire_codec(chip) < 0)
		वापस 0xffff;
	data = (reg << ATI_REG_PHYS_OUT_ADDR_SHIFT) |
		ATI_REG_PHYS_OUT_ADDR_EN |
		ATI_REG_PHYS_OUT_RW |
		codec;
	atiixp_ग_लिखो(chip, PHYS_OUT_ADDR, data);
	अगर (snd_atiixp_acquire_codec(chip) < 0)
		वापस 0xffff;
	समयout = 1000;
	करो अणु
		data = atiixp_पढ़ो(chip, PHYS_IN_ADDR);
		अगर (data & ATI_REG_PHYS_IN_READ_FLAG)
			वापस data >> ATI_REG_PHYS_IN_DATA_SHIFT;
		udelay(1);
	पूर्ण जबतक (--समयout);
	/* समय out may happen during reset */
	अगर (reg < 0x7c)
		dev_warn(chip->card->dev, "codec read timeout (reg %x)\n", reg);
	वापस 0xffff;
पूर्ण


अटल व्योम snd_atiixp_codec_ग_लिखो(काष्ठा atiixp_modem *chip,
				   अचिन्हित लघु codec,
				   अचिन्हित लघु reg, अचिन्हित लघु val)
अणु
	अचिन्हित पूर्णांक data;
    
	अगर (snd_atiixp_acquire_codec(chip) < 0)
		वापस;
	data = ((अचिन्हित पूर्णांक)val << ATI_REG_PHYS_OUT_DATA_SHIFT) |
		((अचिन्हित पूर्णांक)reg << ATI_REG_PHYS_OUT_ADDR_SHIFT) |
		ATI_REG_PHYS_OUT_ADDR_EN | codec;
	atiixp_ग_लिखो(chip, PHYS_OUT_ADDR, data);
पूर्ण


अटल अचिन्हित लघु snd_atiixp_ac97_पढ़ो(काष्ठा snd_ac97 *ac97,
					   अचिन्हित लघु reg)
अणु
	काष्ठा atiixp_modem *chip = ac97->निजी_data;
	वापस snd_atiixp_codec_पढ़ो(chip, ac97->num, reg);
    
पूर्ण

अटल व्योम snd_atiixp_ac97_ग_लिखो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg,
				  अचिन्हित लघु val)
अणु
	काष्ठा atiixp_modem *chip = ac97->निजी_data;
	अगर (reg == AC97_GPIO_STATUS) अणु
		atiixp_ग_लिखो(chip, MODEM_OUT_GPIO,
			(val << ATI_REG_MODEM_OUT_GPIO_DATA_SHIFT) | ATI_REG_MODEM_OUT_GPIO_EN);
		वापस;
	पूर्ण
	snd_atiixp_codec_ग_लिखो(chip, ac97->num, reg, val);
पूर्ण

/*
 * reset AC link
 */
अटल पूर्णांक snd_atiixp_aclink_reset(काष्ठा atiixp_modem *chip)
अणु
	पूर्णांक समयout;

	/* reset घातerकरोewn */
	अगर (atiixp_update(chip, CMD, ATI_REG_CMD_POWERDOWN, 0))
		udelay(10);

	/* perक्रमm a software reset */
	atiixp_update(chip, CMD, ATI_REG_CMD_AC_SOFT_RESET, ATI_REG_CMD_AC_SOFT_RESET);
	atiixp_पढ़ो(chip, CMD);
	udelay(10);
	atiixp_update(chip, CMD, ATI_REG_CMD_AC_SOFT_RESET, 0);
    
	समयout = 10;
	जबतक (! (atiixp_पढ़ो(chip, CMD) & ATI_REG_CMD_ACLINK_ACTIVE)) अणु
		/* करो a hard reset */
		atiixp_update(chip, CMD, ATI_REG_CMD_AC_SYNC|ATI_REG_CMD_AC_RESET,
			      ATI_REG_CMD_AC_SYNC);
		atiixp_पढ़ो(chip, CMD);
		msleep(1);
		atiixp_update(chip, CMD, ATI_REG_CMD_AC_RESET, ATI_REG_CMD_AC_RESET);
		अगर (!--समयout) अणु
			dev_err(chip->card->dev, "codec reset timeout\n");
			अवरोध;
		पूर्ण
	पूर्ण

	/* deनिश्चित RESET and निश्चित SYNC to make sure */
	atiixp_update(chip, CMD, ATI_REG_CMD_AC_SYNC|ATI_REG_CMD_AC_RESET,
		      ATI_REG_CMD_AC_SYNC|ATI_REG_CMD_AC_RESET);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक snd_atiixp_aclink_करोwn(काष्ठा atiixp_modem *chip)
अणु
	// अगर (atiixp_पढ़ो(chip, MODEM_MIRROR) & 0x1) /* modem running, too? */
	//	वापस -EBUSY;
	atiixp_update(chip, CMD,
		     ATI_REG_CMD_POWERDOWN | ATI_REG_CMD_AC_RESET,
		     ATI_REG_CMD_POWERDOWN);
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * स्वतः-detection of codecs
 *
 * the IXP chip can generate पूर्णांकerrupts क्रम the non-existing codecs.
 * NEW_FRAME पूर्णांकerrupt is used to make sure that the पूर्णांकerrupt is generated
 * even अगर all three codecs are connected.
 */

#घोषणा ALL_CODEC_NOT_READY \
	    (ATI_REG_ISR_CODEC0_NOT_READY |\
	     ATI_REG_ISR_CODEC1_NOT_READY |\
	     ATI_REG_ISR_CODEC2_NOT_READY)
#घोषणा CODEC_CHECK_BITS (ALL_CODEC_NOT_READY|ATI_REG_ISR_NEW_FRAME)

अटल पूर्णांक snd_atiixp_codec_detect(काष्ठा atiixp_modem *chip)
अणु
	पूर्णांक समयout;

	chip->codec_not_पढ़ोy_bits = 0;
	atiixp_ग_लिखो(chip, IER, CODEC_CHECK_BITS);
	/* रुको क्रम the पूर्णांकerrupts */
	समयout = 50;
	जबतक (समयout-- > 0) अणु
		msleep(1);
		अगर (chip->codec_not_पढ़ोy_bits)
			अवरोध;
	पूर्ण
	atiixp_ग_लिखो(chip, IER, 0); /* disable irqs */

	अगर ((chip->codec_not_पढ़ोy_bits & ALL_CODEC_NOT_READY) == ALL_CODEC_NOT_READY) अणु
		dev_err(chip->card->dev, "no codec detected!\n");
		वापस -ENXIO;
	पूर्ण
	वापस 0;
पूर्ण


/*
 * enable DMA and irqs
 */
अटल पूर्णांक snd_atiixp_chip_start(काष्ठा atiixp_modem *chip)
अणु
	अचिन्हित पूर्णांक reg;

	/* set up spdअगर, enable burst mode */
	reg = atiixp_पढ़ो(chip, CMD);
	reg |= ATI_REG_CMD_BURST_EN;
	अगर(!(reg & ATI_REG_CMD_MODEM_PRESENT))
		reg |= ATI_REG_CMD_MODEM_PRESENT;
	atiixp_ग_लिखो(chip, CMD, reg);

	/* clear all पूर्णांकerrupt source */
	atiixp_ग_लिखो(chip, ISR, 0xffffffff);
	/* enable irqs */
	atiixp_ग_लिखो(chip, IER,
		     ATI_REG_IER_MODEM_STATUS_EN |
		     ATI_REG_IER_MODEM_IN_XRUN_EN |
		     ATI_REG_IER_MODEM_OUT1_XRUN_EN);
	वापस 0;
पूर्ण


/*
 * disable DMA and IRQs
 */
अटल पूर्णांक snd_atiixp_chip_stop(काष्ठा atiixp_modem *chip)
अणु
	/* clear पूर्णांकerrupt source */
	atiixp_ग_लिखो(chip, ISR, atiixp_पढ़ो(chip, ISR));
	/* disable irqs */
	atiixp_ग_लिखो(chip, IER, 0);
	वापस 0;
पूर्ण


/*
 * PCM section
 */

/*
 * poपूर्णांकer callback simplly पढ़ोs XXX_DMA_DT_CUR रेजिस्टर as the current
 * position.  when SG-buffer is implemented, the offset must be calculated
 * correctly...
 */
अटल snd_pcm_uframes_t snd_atiixp_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा atiixp_modem *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा atiixp_dma *dma = runसमय->निजी_data;
	अचिन्हित पूर्णांक curptr;
	पूर्णांक समयout = 1000;

	जबतक (समयout--) अणु
		curptr = पढ़ोl(chip->remap_addr + dma->ops->dt_cur);
		अगर (curptr < dma->buf_addr)
			जारी;
		curptr -= dma->buf_addr;
		अगर (curptr >= dma->buf_bytes)
			जारी;
		वापस bytes_to_frames(runसमय, curptr);
	पूर्ण
	dev_dbg(chip->card->dev, "invalid DMA pointer read 0x%x (buf=%x)\n",
		   पढ़ोl(chip->remap_addr + dma->ops->dt_cur), dma->buf_addr);
	वापस 0;
पूर्ण

/*
 * XRUN detected, and stop the PCM substream
 */
अटल व्योम snd_atiixp_xrun_dma(काष्ठा atiixp_modem *chip,
				काष्ठा atiixp_dma *dma)
अणु
	अगर (! dma->substream || ! dma->running)
		वापस;
	dev_dbg(chip->card->dev, "XRUN detected (DMA %d)\n", dma->ops->type);
	snd_pcm_stop_xrun(dma->substream);
पूर्ण

/*
 * the period ack.  update the substream.
 */
अटल व्योम snd_atiixp_update_dma(काष्ठा atiixp_modem *chip,
				  काष्ठा atiixp_dma *dma)
अणु
	अगर (! dma->substream || ! dma->running)
		वापस;
	snd_pcm_period_elapsed(dma->substream);
पूर्ण

/* set BUS_BUSY पूर्णांकerrupt bit अगर any DMA is running */
/* call with spinlock held */
अटल व्योम snd_atiixp_check_bus_busy(काष्ठा atiixp_modem *chip)
अणु
	अचिन्हित पूर्णांक bus_busy;
	अगर (atiixp_पढ़ो(chip, CMD) & (ATI_REG_CMD_MODEM_SEND1_EN |
				      ATI_REG_CMD_MODEM_RECEIVE_EN))
		bus_busy = ATI_REG_IER_MODEM_SET_BUS_BUSY;
	अन्यथा
		bus_busy = 0;
	atiixp_update(chip, IER, ATI_REG_IER_MODEM_SET_BUS_BUSY, bus_busy);
पूर्ण

/* common trigger callback
 * calling the lowlevel callbacks in it
 */
अटल पूर्णांक snd_atiixp_pcm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा atiixp_modem *chip = snd_pcm_substream_chip(substream);
	काष्ठा atiixp_dma *dma = substream->runसमय->निजी_data;
	पूर्णांक err = 0;

	अगर (snd_BUG_ON(!dma->ops->enable_transfer ||
		       !dma->ops->flush_dma))
		वापस -EINVAL;

	spin_lock(&chip->reg_lock);
	चयन(cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		dma->ops->enable_transfer(chip, 1);
		dma->running = 1;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		dma->ops->enable_transfer(chip, 0);
		dma->running = 0;
		अवरोध;
	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण
	अगर (! err) अणु
	snd_atiixp_check_bus_busy(chip);
	अगर (cmd == SNDRV_PCM_TRIGGER_STOP) अणु
		dma->ops->flush_dma(chip);
		snd_atiixp_check_bus_busy(chip);
	पूर्ण
	पूर्ण
	spin_unlock(&chip->reg_lock);
	वापस err;
पूर्ण


/*
 * lowlevel callbacks क्रम each DMA type
 *
 * every callback is supposed to be called in chip->reg_lock spinlock
 */

/* flush FIFO of analog OUT DMA */
अटल व्योम atiixp_out_flush_dma(काष्ठा atiixp_modem *chip)
अणु
	atiixp_ग_लिखो(chip, MODEM_FIFO_FLUSH, ATI_REG_MODEM_FIFO_OUT1_FLUSH);
पूर्ण

/* enable/disable analog OUT DMA */
अटल व्योम atiixp_out_enable_dma(काष्ठा atiixp_modem *chip, पूर्णांक on)
अणु
	अचिन्हित पूर्णांक data;
	data = atiixp_पढ़ो(chip, CMD);
	अगर (on) अणु
		अगर (data & ATI_REG_CMD_MODEM_OUT_DMA1_EN)
			वापस;
		atiixp_out_flush_dma(chip);
		data |= ATI_REG_CMD_MODEM_OUT_DMA1_EN;
	पूर्ण अन्यथा
		data &= ~ATI_REG_CMD_MODEM_OUT_DMA1_EN;
	atiixp_ग_लिखो(chip, CMD, data);
पूर्ण

/* start/stop transfer over OUT DMA */
अटल व्योम atiixp_out_enable_transfer(काष्ठा atiixp_modem *chip, पूर्णांक on)
अणु
	atiixp_update(chip, CMD, ATI_REG_CMD_MODEM_SEND1_EN,
		      on ? ATI_REG_CMD_MODEM_SEND1_EN : 0);
पूर्ण

/* enable/disable analog IN DMA */
अटल व्योम atiixp_in_enable_dma(काष्ठा atiixp_modem *chip, पूर्णांक on)
अणु
	atiixp_update(chip, CMD, ATI_REG_CMD_MODEM_IN_DMA_EN,
		      on ? ATI_REG_CMD_MODEM_IN_DMA_EN : 0);
पूर्ण

/* start/stop analog IN DMA */
अटल व्योम atiixp_in_enable_transfer(काष्ठा atiixp_modem *chip, पूर्णांक on)
अणु
	अगर (on) अणु
		अचिन्हित पूर्णांक data = atiixp_पढ़ो(chip, CMD);
		अगर (! (data & ATI_REG_CMD_MODEM_RECEIVE_EN)) अणु
			data |= ATI_REG_CMD_MODEM_RECEIVE_EN;
			atiixp_ग_लिखो(chip, CMD, data);
		पूर्ण
	पूर्ण अन्यथा
		atiixp_update(chip, CMD, ATI_REG_CMD_MODEM_RECEIVE_EN, 0);
पूर्ण

/* flush FIFO of analog IN DMA */
अटल व्योम atiixp_in_flush_dma(काष्ठा atiixp_modem *chip)
अणु
	atiixp_ग_लिखो(chip, MODEM_FIFO_FLUSH, ATI_REG_MODEM_FIFO_IN_FLUSH);
पूर्ण

/* set up slots and क्रमmats क्रम analog OUT */
अटल पूर्णांक snd_atiixp_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा atiixp_modem *chip = snd_pcm_substream_chip(substream);
	अचिन्हित पूर्णांक data;

	spin_lock_irq(&chip->reg_lock);
	/* set output threshold */
	data = atiixp_पढ़ो(chip, MODEM_OUT_FIFO);
	data &= ~ATI_REG_MODEM_OUT1_DMA_THRESHOLD_MASK;
	data |= 0x04 << ATI_REG_MODEM_OUT1_DMA_THRESHOLD_SHIFT;
	atiixp_ग_लिखो(chip, MODEM_OUT_FIFO, data);
	spin_unlock_irq(&chip->reg_lock);
	वापस 0;
पूर्ण

/* set up slots and क्रमmats क्रम analog IN */
अटल पूर्णांक snd_atiixp_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	वापस 0;
पूर्ण

/*
 * hw_params - allocate the buffer and set up buffer descriptors
 */
अटल पूर्णांक snd_atiixp_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा atiixp_modem *chip = snd_pcm_substream_chip(substream);
	काष्ठा atiixp_dma *dma = substream->runसमय->निजी_data;
	पूर्णांक err;
	पूर्णांक i;

	dma->buf_addr = substream->runसमय->dma_addr;
	dma->buf_bytes = params_buffer_bytes(hw_params);

	err = atiixp_build_dma_packets(chip, dma, substream,
				       params_periods(hw_params),
				       params_period_bytes(hw_params));
	अगर (err < 0)
		वापस err;

	/* set up modem rate */
	क्रम (i = 0; i < NUM_ATI_CODECS; i++) अणु
		अगर (! chip->ac97[i])
			जारी;
		snd_ac97_ग_लिखो(chip->ac97[i], AC97_LINE1_RATE, params_rate(hw_params));
		snd_ac97_ग_लिखो(chip->ac97[i], AC97_LINE1_LEVEL, 0);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक snd_atiixp_pcm_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा atiixp_modem *chip = snd_pcm_substream_chip(substream);
	काष्ठा atiixp_dma *dma = substream->runसमय->निजी_data;

	atiixp_clear_dma_packets(chip, dma, substream);
	वापस 0;
पूर्ण


/*
 * pcm hardware definition, identical क्रम all DMA types
 */
अटल स्थिर काष्ठा snd_pcm_hardware snd_atiixp_pcm_hw =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =		SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		(SNDRV_PCM_RATE_8000 |
				 SNDRV_PCM_RATE_16000 |
				 SNDRV_PCM_RATE_KNOT),
	.rate_min =		8000,
	.rate_max =		16000,
	.channels_min =		2,
	.channels_max =		2,
	.buffer_bytes_max =	256 * 1024,
	.period_bytes_min =	32,
	.period_bytes_max =	128 * 1024,
	.periods_min =		2,
	.periods_max =		ATI_MAX_DESCRIPTORS,
पूर्ण;

अटल पूर्णांक snd_atiixp_pcm_खोलो(काष्ठा snd_pcm_substream *substream,
			       काष्ठा atiixp_dma *dma, पूर्णांक pcm_type)
अणु
	काष्ठा atiixp_modem *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;
	अटल स्थिर अचिन्हित पूर्णांक rates[] = अणु 8000,  9600, 12000, 16000 पूर्ण;
	अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list hw_स्थिरraपूर्णांकs_rates = अणु
		.count = ARRAY_SIZE(rates),
		.list = rates,
		.mask = 0,
	पूर्ण;

	अगर (snd_BUG_ON(!dma->ops || !dma->ops->enable_dma))
		वापस -EINVAL;

	अगर (dma->खोलोed)
		वापस -EBUSY;
	dma->substream = substream;
	runसमय->hw = snd_atiixp_pcm_hw;
	dma->ac97_pcm_type = pcm_type;
	अगर ((err = snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0,
					      SNDRV_PCM_HW_PARAM_RATE,
					      &hw_स्थिरraपूर्णांकs_rates)) < 0)
		वापस err;
	अगर ((err = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय,
						 SNDRV_PCM_HW_PARAM_PERIODS)) < 0)
		वापस err;
	runसमय->निजी_data = dma;

	/* enable DMA bits */
	spin_lock_irq(&chip->reg_lock);
	dma->ops->enable_dma(chip, 1);
	spin_unlock_irq(&chip->reg_lock);
	dma->खोलोed = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_atiixp_pcm_बंद(काष्ठा snd_pcm_substream *substream,
				काष्ठा atiixp_dma *dma)
अणु
	काष्ठा atiixp_modem *chip = snd_pcm_substream_chip(substream);
	/* disable DMA bits */
	अगर (snd_BUG_ON(!dma->ops || !dma->ops->enable_dma))
		वापस -EINVAL;
	spin_lock_irq(&chip->reg_lock);
	dma->ops->enable_dma(chip, 0);
	spin_unlock_irq(&chip->reg_lock);
	dma->substream = शून्य;
	dma->खोलोed = 0;
	वापस 0;
पूर्ण

/*
 */
अटल पूर्णांक snd_atiixp_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा atiixp_modem *chip = snd_pcm_substream_chip(substream);
	पूर्णांक err;

	mutex_lock(&chip->खोलो_mutex);
	err = snd_atiixp_pcm_खोलो(substream, &chip->dmas[ATI_DMA_PLAYBACK], 0);
	mutex_unlock(&chip->खोलो_mutex);
	अगर (err < 0)
		वापस err;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_atiixp_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा atiixp_modem *chip = snd_pcm_substream_chip(substream);
	पूर्णांक err;
	mutex_lock(&chip->खोलो_mutex);
	err = snd_atiixp_pcm_बंद(substream, &chip->dmas[ATI_DMA_PLAYBACK]);
	mutex_unlock(&chip->खोलो_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक snd_atiixp_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा atiixp_modem *chip = snd_pcm_substream_chip(substream);
	वापस snd_atiixp_pcm_खोलो(substream, &chip->dmas[ATI_DMA_CAPTURE], 1);
पूर्ण

अटल पूर्णांक snd_atiixp_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा atiixp_modem *chip = snd_pcm_substream_chip(substream);
	वापस snd_atiixp_pcm_बंद(substream, &chip->dmas[ATI_DMA_CAPTURE]);
पूर्ण


/* AC97 playback */
अटल स्थिर काष्ठा snd_pcm_ops snd_atiixp_playback_ops = अणु
	.खोलो =		snd_atiixp_playback_खोलो,
	.बंद =	snd_atiixp_playback_बंद,
	.hw_params =	snd_atiixp_pcm_hw_params,
	.hw_मुक्त =	snd_atiixp_pcm_hw_मुक्त,
	.prepare =	snd_atiixp_playback_prepare,
	.trigger =	snd_atiixp_pcm_trigger,
	.poपूर्णांकer =	snd_atiixp_pcm_poपूर्णांकer,
पूर्ण;

/* AC97 capture */
अटल स्थिर काष्ठा snd_pcm_ops snd_atiixp_capture_ops = अणु
	.खोलो =		snd_atiixp_capture_खोलो,
	.बंद =	snd_atiixp_capture_बंद,
	.hw_params =	snd_atiixp_pcm_hw_params,
	.hw_मुक्त =	snd_atiixp_pcm_hw_मुक्त,
	.prepare =	snd_atiixp_capture_prepare,
	.trigger =	snd_atiixp_pcm_trigger,
	.poपूर्णांकer =	snd_atiixp_pcm_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा atiixp_dma_ops snd_atiixp_playback_dma_ops = अणु
	.type = ATI_DMA_PLAYBACK,
	.llp_offset = ATI_REG_MODEM_OUT_DMA1_LINKPTR,
	.dt_cur = ATI_REG_MODEM_OUT_DMA1_DT_CUR,
	.enable_dma = atiixp_out_enable_dma,
	.enable_transfer = atiixp_out_enable_transfer,
	.flush_dma = atiixp_out_flush_dma,
पूर्ण;
	
अटल स्थिर काष्ठा atiixp_dma_ops snd_atiixp_capture_dma_ops = अणु
	.type = ATI_DMA_CAPTURE,
	.llp_offset = ATI_REG_MODEM_IN_DMA_LINKPTR,
	.dt_cur = ATI_REG_MODEM_IN_DMA_DT_CUR,
	.enable_dma = atiixp_in_enable_dma,
	.enable_transfer = atiixp_in_enable_transfer,
	.flush_dma = atiixp_in_flush_dma,
पूर्ण;

अटल पूर्णांक snd_atiixp_pcm_new(काष्ठा atiixp_modem *chip)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	/* initialize स्थिरants */
	chip->dmas[ATI_DMA_PLAYBACK].ops = &snd_atiixp_playback_dma_ops;
	chip->dmas[ATI_DMA_CAPTURE].ops = &snd_atiixp_capture_dma_ops;

	/* PCM #0: analog I/O */
	err = snd_pcm_new(chip->card, "ATI IXP MC97", ATI_PCMDEV_ANALOG, 1, 1, &pcm);
	अगर (err < 0)
		वापस err;
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_atiixp_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_atiixp_capture_ops);
	pcm->dev_class = SNDRV_PCM_CLASS_MODEM;
	pcm->निजी_data = chip;
	म_नकल(pcm->name, "ATI IXP MC97");
	chip->pcmdevs[ATI_PCMDEV_ANALOG] = pcm;

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
				       &chip->pci->dev, 64*1024, 128*1024);

	वापस 0;
पूर्ण



/*
 * पूर्णांकerrupt handler
 */
अटल irqवापस_t snd_atiixp_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा atiixp_modem *chip = dev_id;
	अचिन्हित पूर्णांक status;

	status = atiixp_पढ़ो(chip, ISR);

	अगर (! status)
		वापस IRQ_NONE;

	/* process audio DMA */
	अगर (status & ATI_REG_ISR_MODEM_OUT1_XRUN)
		snd_atiixp_xrun_dma(chip,  &chip->dmas[ATI_DMA_PLAYBACK]);
	अन्यथा अगर (status & ATI_REG_ISR_MODEM_OUT1_STATUS)
		snd_atiixp_update_dma(chip, &chip->dmas[ATI_DMA_PLAYBACK]);
	अगर (status & ATI_REG_ISR_MODEM_IN_XRUN)
		snd_atiixp_xrun_dma(chip,  &chip->dmas[ATI_DMA_CAPTURE]);
	अन्यथा अगर (status & ATI_REG_ISR_MODEM_IN_STATUS)
		snd_atiixp_update_dma(chip, &chip->dmas[ATI_DMA_CAPTURE]);

	/* क्रम codec detection */
	अगर (status & CODEC_CHECK_BITS) अणु
		अचिन्हित पूर्णांक detected;
		detected = status & CODEC_CHECK_BITS;
		spin_lock(&chip->reg_lock);
		chip->codec_not_पढ़ोy_bits |= detected;
		atiixp_update(chip, IER, detected, 0); /* disable the detected irqs */
		spin_unlock(&chip->reg_lock);
	पूर्ण

	/* ack */
	atiixp_ग_लिखो(chip, ISR, status);

	वापस IRQ_HANDLED;
पूर्ण


/*
 * ac97 mixer section
 */

अटल पूर्णांक snd_atiixp_mixer_new(काष्ठा atiixp_modem *chip, पूर्णांक घड़ी)
अणु
	काष्ठा snd_ac97_bus *pbus;
	काष्ठा snd_ac97_ढाँचा ac97;
	पूर्णांक i, err;
	पूर्णांक codec_count;
	अटल स्थिर काष्ठा snd_ac97_bus_ops ops = अणु
		.ग_लिखो = snd_atiixp_ac97_ग_लिखो,
		.पढ़ो = snd_atiixp_ac97_पढ़ो,
	पूर्ण;
	अटल स्थिर अचिन्हित पूर्णांक codec_skip[NUM_ATI_CODECS] = अणु
		ATI_REG_ISR_CODEC0_NOT_READY,
		ATI_REG_ISR_CODEC1_NOT_READY,
		ATI_REG_ISR_CODEC2_NOT_READY,
	पूर्ण;

	अगर (snd_atiixp_codec_detect(chip) < 0)
		वापस -ENXIO;

	अगर ((err = snd_ac97_bus(chip->card, 0, &ops, chip, &pbus)) < 0)
		वापस err;
	pbus->घड़ी = घड़ी;
	chip->ac97_bus = pbus;

	codec_count = 0;
	क्रम (i = 0; i < NUM_ATI_CODECS; i++) अणु
		अगर (chip->codec_not_पढ़ोy_bits & codec_skip[i])
			जारी;
		स_रखो(&ac97, 0, माप(ac97));
		ac97.निजी_data = chip;
		ac97.pci = chip->pci;
		ac97.num = i;
		ac97.scaps = AC97_SCAP_SKIP_AUDIO | AC97_SCAP_POWER_SAVE;
		अगर ((err = snd_ac97_mixer(pbus, &ac97, &chip->ac97[i])) < 0) अणु
			chip->ac97[i] = शून्य; /* to be sure */
			dev_dbg(chip->card->dev,
				"codec %d not available for modem\n", i);
			जारी;
		पूर्ण
		codec_count++;
	पूर्ण

	अगर (! codec_count) अणु
		dev_err(chip->card->dev, "no codec available\n");
		वापस -ENODEV;
	पूर्ण

	/* snd_ac97_tune_hardware(chip->ac97, ac97_quirks); */

	वापस 0;
पूर्ण


#अगर_घोषित CONFIG_PM_SLEEP
/*
 * घातer management
 */
अटल पूर्णांक snd_atiixp_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा atiixp_modem *chip = card->निजी_data;
	पूर्णांक i;

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);
	क्रम (i = 0; i < NUM_ATI_CODECS; i++)
		snd_ac97_suspend(chip->ac97[i]);
	snd_atiixp_aclink_करोwn(chip);
	snd_atiixp_chip_stop(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_atiixp_resume(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा atiixp_modem *chip = card->निजी_data;
	पूर्णांक i;

	snd_atiixp_aclink_reset(chip);
	snd_atiixp_chip_start(chip);

	क्रम (i = 0; i < NUM_ATI_CODECS; i++)
		snd_ac97_resume(chip->ac97[i]);

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(snd_atiixp_pm, snd_atiixp_suspend, snd_atiixp_resume);
#घोषणा SND_ATIIXP_PM_OPS	&snd_atiixp_pm
#अन्यथा
#घोषणा SND_ATIIXP_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

/*
 * proc पूर्णांकerface क्रम रेजिस्टर dump
 */

अटल व्योम snd_atiixp_proc_पढ़ो(काष्ठा snd_info_entry *entry,
				 काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा atiixp_modem *chip = entry->निजी_data;
	पूर्णांक i;

	क्रम (i = 0; i < 256; i += 4)
		snd_iम_लिखो(buffer, "%02x: %08x\n", i, पढ़ोl(chip->remap_addr + i));
पूर्ण

अटल व्योम snd_atiixp_proc_init(काष्ठा atiixp_modem *chip)
अणु
	snd_card_ro_proc_new(chip->card, "atiixp-modem", chip,
			     snd_atiixp_proc_पढ़ो);
पूर्ण


/*
 * deकाष्ठाor
 */

अटल पूर्णांक snd_atiixp_मुक्त(काष्ठा atiixp_modem *chip)
अणु
	अगर (chip->irq < 0)
		जाओ __hw_end;
	snd_atiixp_chip_stop(chip);

      __hw_end:
	अगर (chip->irq >= 0)
		मुक्त_irq(chip->irq, chip);
	iounmap(chip->remap_addr);
	pci_release_regions(chip->pci);
	pci_disable_device(chip->pci);
	kमुक्त(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_atiixp_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा atiixp_modem *chip = device->device_data;
	वापस snd_atiixp_मुक्त(chip);
पूर्ण

/*
 * स्थिरructor क्रम chip instance
 */
अटल पूर्णांक snd_atiixp_create(काष्ठा snd_card *card,
			     काष्ठा pci_dev *pci,
			     काष्ठा atiixp_modem **r_chip)
अणु
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =	snd_atiixp_dev_मुक्त,
	पूर्ण;
	काष्ठा atiixp_modem *chip;
	पूर्णांक err;

	अगर ((err = pci_enable_device(pci)) < 0)
		वापस err;

	chip = kzalloc(माप(*chip), GFP_KERNEL);
	अगर (chip == शून्य) अणु
		pci_disable_device(pci);
		वापस -ENOMEM;
	पूर्ण

	spin_lock_init(&chip->reg_lock);
	mutex_init(&chip->खोलो_mutex);
	chip->card = card;
	chip->pci = pci;
	chip->irq = -1;
	अगर ((err = pci_request_regions(pci, "ATI IXP MC97")) < 0) अणु
		kमुक्त(chip);
		pci_disable_device(pci);
		वापस err;
	पूर्ण
	chip->addr = pci_resource_start(pci, 0);
	chip->remap_addr = pci_ioremap_bar(pci, 0);
	अगर (chip->remap_addr == शून्य) अणु
		dev_err(card->dev, "AC'97 space ioremap problem\n");
		snd_atiixp_मुक्त(chip);
		वापस -EIO;
	पूर्ण

	अगर (request_irq(pci->irq, snd_atiixp_पूर्णांकerrupt, IRQF_SHARED,
			KBUILD_MODNAME, chip)) अणु
		dev_err(card->dev, "unable to grab IRQ %d\n", pci->irq);
		snd_atiixp_मुक्त(chip);
		वापस -EBUSY;
	पूर्ण
	chip->irq = pci->irq;
	card->sync_irq = chip->irq;
	pci_set_master(pci);

	अगर ((err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops)) < 0) अणु
		snd_atiixp_मुक्त(chip);
		वापस err;
	पूर्ण

	*r_chip = chip;
	वापस 0;
पूर्ण


अटल पूर्णांक snd_atiixp_probe(काष्ठा pci_dev *pci,
			    स्थिर काष्ठा pci_device_id *pci_id)
अणु
	काष्ठा snd_card *card;
	काष्ठा atiixp_modem *chip;
	पूर्णांक err;

	err = snd_card_new(&pci->dev, index, id, THIS_MODULE, 0, &card);
	अगर (err < 0)
		वापस err;

	म_नकल(card->driver, "ATIIXP-MODEM");
	म_नकल(card->लघुname, "ATI IXP Modem");
	अगर ((err = snd_atiixp_create(card, pci, &chip)) < 0)
		जाओ __error;
	card->निजी_data = chip;

	अगर ((err = snd_atiixp_aclink_reset(chip)) < 0)
		जाओ __error;

	अगर ((err = snd_atiixp_mixer_new(chip, ac97_घड़ी)) < 0)
		जाओ __error;

	अगर ((err = snd_atiixp_pcm_new(chip)) < 0)
		जाओ __error;
	
	snd_atiixp_proc_init(chip);

	snd_atiixp_chip_start(chip);

	प्र_लिखो(card->दीर्घname, "%s rev %x at 0x%lx, irq %i",
		card->लघुname, pci->revision, chip->addr, chip->irq);

	अगर ((err = snd_card_रेजिस्टर(card)) < 0)
		जाओ __error;

	pci_set_drvdata(pci, card);
	वापस 0;

 __error:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

अटल व्योम snd_atiixp_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण

अटल काष्ठा pci_driver atiixp_modem_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_atiixp_ids,
	.probe = snd_atiixp_probe,
	.हटाओ = snd_atiixp_हटाओ,
	.driver = अणु
		.pm = SND_ATIIXP_PM_OPS,
	पूर्ण,
पूर्ण;

module_pci_driver(atiixp_modem_driver);
