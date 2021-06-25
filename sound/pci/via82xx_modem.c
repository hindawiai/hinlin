<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA modem driver क्रम VIA VT82xx (South Bridge)
 *
 *   VT82C686A/B/C, VT8233A/C, VT8235
 *
 *	Copyright (c) 2000 Jaroslav Kysela <perex@perex.cz>
 *	                   Tjeerd.Mulder <Tjeerd.Mulder@fujitsu-siemens.com>
 *                    2002 Takashi Iwai <tiwai@suse.de>
 */

/*
 * Changes:
 *
 * Sep. 2,  2004  Sasha Khapyorsky <sashak@alsa-project.org>
 *      Modअगरied from original audio driver 'via82xx.c' to support AC97
 *      modems.
 */

#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/info.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/initval.h>

#अगर 0
#घोषणा POINTER_DEBUG
#पूर्ण_अगर

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("VIA VT82xx modem");
MODULE_LICENSE("GPL");

अटल पूर्णांक index = -2; /* Exclude the first card */
अटल अक्षर *id = SNDRV_DEFAULT_STR1;	/* ID क्रम this card */
अटल पूर्णांक ac97_घड़ी = 48000;

module_param(index, पूर्णांक, 0444);
MODULE_PARM_DESC(index, "Index value for VIA 82xx bridge.");
module_param(id, अक्षरp, 0444);
MODULE_PARM_DESC(id, "ID string for VIA 82xx bridge.");
module_param(ac97_घड़ी, पूर्णांक, 0444);
MODULE_PARM_DESC(ac97_घड़ी, "AC'97 codec clock (default 48000Hz).");

/* just क्रम backward compatibility */
अटल bool enable;
module_param(enable, bool, 0444);


/*
 *  Direct रेजिस्टरs
 */

#घोषणा VIAREG(via, x) ((via)->port + VIA_REG_##x)
#घोषणा VIADEV_REG(viadev, x) ((viadev)->port + VIA_REG_##x)

/* common offsets */
#घोषणा VIA_REG_OFFSET_STATUS		0x00	/* byte - channel status */
#घोषणा   VIA_REG_STAT_ACTIVE		0x80	/* RO */
#घोषणा   VIA_REG_STAT_PAUSED		0x40	/* RO */
#घोषणा   VIA_REG_STAT_TRIGGER_QUEUED	0x08	/* RO */
#घोषणा   VIA_REG_STAT_STOPPED		0x04	/* RWC */
#घोषणा   VIA_REG_STAT_EOL		0x02	/* RWC */
#घोषणा   VIA_REG_STAT_FLAG		0x01	/* RWC */
#घोषणा VIA_REG_OFFSET_CONTROL		0x01	/* byte - channel control */
#घोषणा   VIA_REG_CTRL_START		0x80	/* WO */
#घोषणा   VIA_REG_CTRL_TERMINATE	0x40	/* WO */
#घोषणा   VIA_REG_CTRL_AUTOSTART	0x20
#घोषणा   VIA_REG_CTRL_PAUSE		0x08	/* RW */
#घोषणा   VIA_REG_CTRL_INT_STOP		0x04		
#घोषणा   VIA_REG_CTRL_INT_EOL		0x02
#घोषणा   VIA_REG_CTRL_INT_FLAG		0x01
#घोषणा   VIA_REG_CTRL_RESET		0x01	/* RW - probably reset? unकरोcumented */
#घोषणा   VIA_REG_CTRL_INT (VIA_REG_CTRL_INT_FLAG | VIA_REG_CTRL_INT_EOL | VIA_REG_CTRL_AUTOSTART)
#घोषणा VIA_REG_OFFSET_TYPE		0x02	/* byte - channel type (686 only) */
#घोषणा   VIA_REG_TYPE_AUTOSTART	0x80	/* RW - स्वतःstart at EOL */
#घोषणा   VIA_REG_TYPE_16BIT		0x20	/* RW */
#घोषणा   VIA_REG_TYPE_STEREO		0x10	/* RW */
#घोषणा   VIA_REG_TYPE_INT_LLINE	0x00
#घोषणा   VIA_REG_TYPE_INT_LSAMPLE	0x04
#घोषणा   VIA_REG_TYPE_INT_LESSONE	0x08
#घोषणा   VIA_REG_TYPE_INT_MASK		0x0c
#घोषणा   VIA_REG_TYPE_INT_EOL		0x02
#घोषणा   VIA_REG_TYPE_INT_FLAG		0x01
#घोषणा VIA_REG_OFFSET_TABLE_PTR	0x04	/* dword - channel table poपूर्णांकer */
#घोषणा VIA_REG_OFFSET_CURR_PTR		0x04	/* dword - channel current poपूर्णांकer */
#घोषणा VIA_REG_OFFSET_STOP_IDX		0x08	/* dword - stop index, channel type, sample rate */
#घोषणा VIA_REG_OFFSET_CURR_COUNT	0x0c	/* dword - channel current count (24 bit) */
#घोषणा VIA_REG_OFFSET_CURR_INDEX	0x0f	/* byte - channel current index (क्रम via8233 only) */

#घोषणा DEFINE_VIA_REGSET(name,val) \
क्रमागत अणु\
	VIA_REG_##name##_STATUS		= (val),\
	VIA_REG_##name##_CONTROL	= (val) + 0x01,\
	VIA_REG_##name##_TYPE		= (val) + 0x02,\
	VIA_REG_##name##_TABLE_PTR	= (val) + 0x04,\
	VIA_REG_##name##_CURR_PTR	= (val) + 0x04,\
	VIA_REG_##name##_STOP_IDX	= (val) + 0x08,\
	VIA_REG_##name##_CURR_COUNT	= (val) + 0x0c,\
पूर्ण

/* modem block */
DEFINE_VIA_REGSET(MO, 0x40);
DEFINE_VIA_REGSET(MI, 0x50);

/* AC'97 */
#घोषणा VIA_REG_AC97			0x80	/* dword */
#घोषणा   VIA_REG_AC97_CODEC_ID_MASK	(3<<30)
#घोषणा   VIA_REG_AC97_CODEC_ID_SHIFT	30
#घोषणा   VIA_REG_AC97_CODEC_ID_PRIMARY	0x00
#घोषणा   VIA_REG_AC97_CODEC_ID_SECONDARY 0x01
#घोषणा   VIA_REG_AC97_SECONDARY_VALID	(1<<27)
#घोषणा   VIA_REG_AC97_PRIMARY_VALID	(1<<25)
#घोषणा   VIA_REG_AC97_BUSY		(1<<24)
#घोषणा   VIA_REG_AC97_READ		(1<<23)
#घोषणा   VIA_REG_AC97_CMD_SHIFT	16
#घोषणा   VIA_REG_AC97_CMD_MASK		0x7e
#घोषणा   VIA_REG_AC97_DATA_SHIFT	0
#घोषणा   VIA_REG_AC97_DATA_MASK	0xffff

#घोषणा VIA_REG_SGD_SHADOW		0x84	/* dword */
#घोषणा   VIA_REG_SGD_STAT_PB_FLAG	(1<<0)
#घोषणा   VIA_REG_SGD_STAT_CP_FLAG	(1<<1)
#घोषणा   VIA_REG_SGD_STAT_FM_FLAG	(1<<2)
#घोषणा   VIA_REG_SGD_STAT_PB_EOL	(1<<4)
#घोषणा   VIA_REG_SGD_STAT_CP_EOL	(1<<5)
#घोषणा   VIA_REG_SGD_STAT_FM_EOL	(1<<6)
#घोषणा   VIA_REG_SGD_STAT_PB_STOP	(1<<8)
#घोषणा   VIA_REG_SGD_STAT_CP_STOP	(1<<9)
#घोषणा   VIA_REG_SGD_STAT_FM_STOP	(1<<10)
#घोषणा   VIA_REG_SGD_STAT_PB_ACTIVE	(1<<12)
#घोषणा   VIA_REG_SGD_STAT_CP_ACTIVE	(1<<13)
#घोषणा   VIA_REG_SGD_STAT_FM_ACTIVE	(1<<14)
#घोषणा   VIA_REG_SGD_STAT_MR_FLAG      (1<<16)
#घोषणा   VIA_REG_SGD_STAT_MW_FLAG      (1<<17)
#घोषणा   VIA_REG_SGD_STAT_MR_EOL       (1<<20)
#घोषणा   VIA_REG_SGD_STAT_MW_EOL       (1<<21)
#घोषणा   VIA_REG_SGD_STAT_MR_STOP      (1<<24)
#घोषणा   VIA_REG_SGD_STAT_MW_STOP      (1<<25)
#घोषणा   VIA_REG_SGD_STAT_MR_ACTIVE    (1<<28)
#घोषणा   VIA_REG_SGD_STAT_MW_ACTIVE    (1<<29)

#घोषणा VIA_REG_GPI_STATUS		0x88
#घोषणा VIA_REG_GPI_INTR		0x8c

#घोषणा VIA_TBL_BIT_FLAG	0x40000000
#घोषणा VIA_TBL_BIT_EOL		0x80000000

/* pci space */
#घोषणा VIA_ACLINK_STAT		0x40
#घोषणा  VIA_ACLINK_C11_READY	0x20
#घोषणा  VIA_ACLINK_C10_READY	0x10
#घोषणा  VIA_ACLINK_C01_READY	0x04 /* secondary codec पढ़ोy */
#घोषणा  VIA_ACLINK_LOWPOWER	0x02 /* low-घातer state */
#घोषणा  VIA_ACLINK_C00_READY	0x01 /* primary codec पढ़ोy */
#घोषणा VIA_ACLINK_CTRL		0x41
#घोषणा  VIA_ACLINK_CTRL_ENABLE	0x80 /* 0: disable, 1: enable */
#घोषणा  VIA_ACLINK_CTRL_RESET	0x40 /* 0: निश्चित, 1: de-निश्चित */
#घोषणा  VIA_ACLINK_CTRL_SYNC	0x20 /* 0: release SYNC, 1: क्रमce SYNC hi */
#घोषणा  VIA_ACLINK_CTRL_SDO	0x10 /* 0: release SDO, 1: क्रमce SDO hi */
#घोषणा  VIA_ACLINK_CTRL_VRA	0x08 /* 0: disable VRA, 1: enable VRA */
#घोषणा  VIA_ACLINK_CTRL_PCM	0x04 /* 0: disable PCM, 1: enable PCM */
#घोषणा  VIA_ACLINK_CTRL_FM	0x02 /* via686 only */
#घोषणा  VIA_ACLINK_CTRL_SB	0x01 /* via686 only */
#घोषणा  VIA_ACLINK_CTRL_INIT	(VIA_ACLINK_CTRL_ENABLE|\
				 VIA_ACLINK_CTRL_RESET|\
				 VIA_ACLINK_CTRL_PCM)
#घोषणा VIA_FUNC_ENABLE		0x42
#घोषणा  VIA_FUNC_MIDI_PNP	0x80 /* FIXME: it's 0x40 in the datasheet! */
#घोषणा  VIA_FUNC_MIDI_IRQMASK	0x40 /* FIXME: not करोcumented! */
#घोषणा  VIA_FUNC_RX2C_WRITE	0x20
#घोषणा  VIA_FUNC_SB_FIFO_EMPTY	0x10
#घोषणा  VIA_FUNC_ENABLE_GAME	0x08
#घोषणा  VIA_FUNC_ENABLE_FM	0x04
#घोषणा  VIA_FUNC_ENABLE_MIDI	0x02
#घोषणा  VIA_FUNC_ENABLE_SB	0x01
#घोषणा VIA_PNP_CONTROL		0x43
#घोषणा VIA_MC97_CTRL		0x44
#घोषणा  VIA_MC97_CTRL_ENABLE   0x80
#घोषणा  VIA_MC97_CTRL_SECONDARY 0x40
#घोषणा  VIA_MC97_CTRL_INIT     (VIA_MC97_CTRL_ENABLE|\
                                 VIA_MC97_CTRL_SECONDARY)


/*
 * pcm stream
 */

काष्ठा snd_via_sg_table अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक size;
पूर्ण ;

#घोषणा VIA_TABLE_SIZE	255

काष्ठा viadev अणु
	अचिन्हित पूर्णांक reg_offset;
	अचिन्हित दीर्घ port;
	पूर्णांक direction;	/* playback = 0, capture = 1 */
        काष्ठा snd_pcm_substream *substream;
	पूर्णांक running;
	अचिन्हित पूर्णांक tbl_entries; /* # descriptors */
	काष्ठा snd_dma_buffer table;
	काष्ठा snd_via_sg_table *idx_table;
	/* क्रम recovery from the unexpected poपूर्णांकer */
	अचिन्हित पूर्णांक lastpos;
	अचिन्हित पूर्णांक bufsize;
	अचिन्हित पूर्णांक bufsize2;
पूर्ण;

क्रमागत अणु TYPE_CARD_VIA82XX_MODEM = 1 पूर्ण;

#घोषणा VIA_MAX_MODEM_DEVS	2

काष्ठा via82xx_modem अणु
	पूर्णांक irq;

	अचिन्हित दीर्घ port;

	अचिन्हित पूर्णांक पूर्णांकr_mask; /* SGD_SHADOW mask to check पूर्णांकerrupts */

	काष्ठा pci_dev *pci;
	काष्ठा snd_card *card;

	अचिन्हित पूर्णांक num_devs;
	अचिन्हित पूर्णांक playback_devno, capture_devno;
	काष्ठा viadev devs[VIA_MAX_MODEM_DEVS];

	काष्ठा snd_pcm *pcms[2];

	काष्ठा snd_ac97_bus *ac97_bus;
	काष्ठा snd_ac97 *ac97;
	अचिन्हित पूर्णांक ac97_घड़ी;
	अचिन्हित पूर्णांक ac97_secondary;	/* secondary AC'97 codec is present */

	spinlock_t reg_lock;
	काष्ठा snd_info_entry *proc_entry;
पूर्ण;

अटल स्थिर काष्ठा pci_device_id snd_via82xx_modem_ids[] = अणु
	अणु PCI_VDEVICE(VIA, 0x3068), TYPE_CARD_VIA82XX_MODEM, पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, snd_via82xx_modem_ids);

/*
 */

/*
 * allocate and initialize the descriptor buffers
 * periods = number of periods
 * fragsize = period size in bytes
 */
अटल पूर्णांक build_via_table(काष्ठा viadev *dev, काष्ठा snd_pcm_substream *substream,
			   काष्ठा pci_dev *pci,
			   अचिन्हित पूर्णांक periods, अचिन्हित पूर्णांक fragsize)
अणु
	अचिन्हित पूर्णांक i, idx, ofs, rest;
	काष्ठा via82xx_modem *chip = snd_pcm_substream_chip(substream);
	__le32 *pgtbl;

	अगर (dev->table.area == शून्य) अणु
		/* the start of each lists must be aligned to 8 bytes,
		 * but the kernel pages are much bigger, so we करोn't care
		 */
		अगर (snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, &chip->pci->dev,
					PAGE_ALIGN(VIA_TABLE_SIZE * 2 * 8),
					&dev->table) < 0)
			वापस -ENOMEM;
	पूर्ण
	अगर (! dev->idx_table) अणु
		dev->idx_table = kदो_स्मृति_array(VIA_TABLE_SIZE,
					       माप(*dev->idx_table),
					       GFP_KERNEL);
		अगर (! dev->idx_table)
			वापस -ENOMEM;
	पूर्ण

	/* fill the entries */
	idx = 0;
	ofs = 0;
	pgtbl = (__le32 *)dev->table.area;
	क्रम (i = 0; i < periods; i++) अणु
		rest = fragsize;
		/* fill descriptors क्रम a period.
		 * a period can be split to several descriptors अगर it's
		 * over page boundary.
		 */
		करो अणु
			अचिन्हित पूर्णांक r;
			अचिन्हित पूर्णांक flag;
			अचिन्हित पूर्णांक addr;

			अगर (idx >= VIA_TABLE_SIZE) अणु
				dev_err(&pci->dev, "too much table size!\n");
				वापस -EINVAL;
			पूर्ण
			addr = snd_pcm_sgbuf_get_addr(substream, ofs);
			pgtbl[idx << 1] = cpu_to_le32(addr);
			r = PAGE_SIZE - (ofs % PAGE_SIZE);
			अगर (rest < r)
				r = rest;
			rest -= r;
			अगर (! rest) अणु
				अगर (i == periods - 1)
					flag = VIA_TBL_BIT_EOL; /* buffer boundary */
				अन्यथा
					flag = VIA_TBL_BIT_FLAG; /* period boundary */
			पूर्ण अन्यथा
				flag = 0; /* period जारीs to the next */
			/*
			dev_dbg(&pci->dev,
				"tbl %d: at %d  size %d (rest %d)\n",
				idx, ofs, r, rest);
			*/
			pgtbl[(idx<<1) + 1] = cpu_to_le32(r | flag);
			dev->idx_table[idx].offset = ofs;
			dev->idx_table[idx].size = r;
			ofs += r;
			idx++;
		पूर्ण जबतक (rest > 0);
	पूर्ण
	dev->tbl_entries = idx;
	dev->bufsize = periods * fragsize;
	dev->bufsize2 = dev->bufsize / 2;
	वापस 0;
पूर्ण


अटल पूर्णांक clean_via_table(काष्ठा viadev *dev, काष्ठा snd_pcm_substream *substream,
			   काष्ठा pci_dev *pci)
अणु
	अगर (dev->table.area) अणु
		snd_dma_मुक्त_pages(&dev->table);
		dev->table.area = शून्य;
	पूर्ण
	kमुक्त(dev->idx_table);
	dev->idx_table = शून्य;
	वापस 0;
पूर्ण

/*
 *  Basic I/O
 */

अटल अंतरभूत अचिन्हित पूर्णांक snd_via82xx_codec_xपढ़ो(काष्ठा via82xx_modem *chip)
अणु
	वापस inl(VIAREG(chip, AC97));
पूर्ण
 
अटल अंतरभूत व्योम snd_via82xx_codec_xग_लिखो(काष्ठा via82xx_modem *chip, अचिन्हित पूर्णांक val)
अणु
	outl(val, VIAREG(chip, AC97));
पूर्ण
 
अटल पूर्णांक snd_via82xx_codec_पढ़ोy(काष्ठा via82xx_modem *chip, पूर्णांक secondary)
अणु
	अचिन्हित पूर्णांक समयout = 1000;	/* 1ms */
	अचिन्हित पूर्णांक val;
	
	जबतक (समयout-- > 0) अणु
		udelay(1);
		अगर (!((val = snd_via82xx_codec_xपढ़ो(chip)) & VIA_REG_AC97_BUSY))
			वापस val & 0xffff;
	पूर्ण
	dev_err(chip->card->dev, "codec_ready: codec %i is not ready [0x%x]\n",
		   secondary, snd_via82xx_codec_xपढ़ो(chip));
	वापस -EIO;
पूर्ण
 
अटल पूर्णांक snd_via82xx_codec_valid(काष्ठा via82xx_modem *chip, पूर्णांक secondary)
अणु
	अचिन्हित पूर्णांक समयout = 1000;	/* 1ms */
	अचिन्हित पूर्णांक val, val1;
	अचिन्हित पूर्णांक stat = !secondary ? VIA_REG_AC97_PRIMARY_VALID :
					 VIA_REG_AC97_SECONDARY_VALID;
	
	जबतक (समयout-- > 0) अणु
		val = snd_via82xx_codec_xपढ़ो(chip);
		val1 = val & (VIA_REG_AC97_BUSY | stat);
		अगर (val1 == stat)
			वापस val & 0xffff;
		udelay(1);
	पूर्ण
	वापस -EIO;
पूर्ण
 
अटल व्योम snd_via82xx_codec_रुको(काष्ठा snd_ac97 *ac97)
अणु
	काष्ठा via82xx_modem *chip = ac97->निजी_data;
	__always_unused पूर्णांक err;
	err = snd_via82xx_codec_पढ़ोy(chip, ac97->num);
	/* here we need to रुको fairly क्रम दीर्घ समय.. */
	msleep(500);
पूर्ण

अटल व्योम snd_via82xx_codec_ग_लिखो(काष्ठा snd_ac97 *ac97,
				    अचिन्हित लघु reg,
				    अचिन्हित लघु val)
अणु
	काष्ठा via82xx_modem *chip = ac97->निजी_data;
	अचिन्हित पूर्णांक xval;
	अगर(reg == AC97_GPIO_STATUS) अणु
		outl(val, VIAREG(chip, GPI_STATUS));
		वापस;
	पूर्ण	
	xval = !ac97->num ? VIA_REG_AC97_CODEC_ID_PRIMARY : VIA_REG_AC97_CODEC_ID_SECONDARY;
	xval <<= VIA_REG_AC97_CODEC_ID_SHIFT;
	xval |= reg << VIA_REG_AC97_CMD_SHIFT;
	xval |= val << VIA_REG_AC97_DATA_SHIFT;
	snd_via82xx_codec_xग_लिखो(chip, xval);
	snd_via82xx_codec_पढ़ोy(chip, ac97->num);
पूर्ण

अटल अचिन्हित लघु snd_via82xx_codec_पढ़ो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg)
अणु
	काष्ठा via82xx_modem *chip = ac97->निजी_data;
	अचिन्हित पूर्णांक xval, val = 0xffff;
	पूर्णांक again = 0;

	xval = ac97->num << VIA_REG_AC97_CODEC_ID_SHIFT;
	xval |= ac97->num ? VIA_REG_AC97_SECONDARY_VALID : VIA_REG_AC97_PRIMARY_VALID;
	xval |= VIA_REG_AC97_READ;
	xval |= (reg & 0x7f) << VIA_REG_AC97_CMD_SHIFT;
      	जबतक (1) अणु
      		अगर (again++ > 3) अणु
			dev_err(chip->card->dev,
				"codec_read: codec %i is not valid [0x%x]\n",
				   ac97->num, snd_via82xx_codec_xपढ़ो(chip));
		      	वापस 0xffff;
		पूर्ण
		snd_via82xx_codec_xग_लिखो(chip, xval);
		udelay (20);
		अगर (snd_via82xx_codec_valid(chip, ac97->num) >= 0) अणु
			udelay(25);
			val = snd_via82xx_codec_xपढ़ो(chip);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस val & 0xffff;
पूर्ण

अटल व्योम snd_via82xx_channel_reset(काष्ठा via82xx_modem *chip, काष्ठा viadev *viadev)
अणु
	outb(VIA_REG_CTRL_PAUSE | VIA_REG_CTRL_TERMINATE | VIA_REG_CTRL_RESET,
	     VIADEV_REG(viadev, OFFSET_CONTROL));
	inb(VIADEV_REG(viadev, OFFSET_CONTROL));
	udelay(50);
	/* disable पूर्णांकerrupts */
	outb(0x00, VIADEV_REG(viadev, OFFSET_CONTROL));
	/* clear पूर्णांकerrupts */
	outb(0x03, VIADEV_REG(viadev, OFFSET_STATUS));
	outb(0x00, VIADEV_REG(viadev, OFFSET_TYPE)); /* क्रम via686 */
	// outl(0, VIADEV_REG(viadev, OFFSET_CURR_PTR));
	viadev->lastpos = 0;
पूर्ण


/*
 *  Interrupt handler
 */

अटल irqवापस_t snd_via82xx_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा via82xx_modem *chip = dev_id;
	अचिन्हित पूर्णांक status;
	अचिन्हित पूर्णांक i;

	status = inl(VIAREG(chip, SGD_SHADOW));
	अगर (! (status & chip->पूर्णांकr_mask)) अणु
		वापस IRQ_NONE;
	पूर्ण
// _skip_sgd:

	/* check status क्रम each stream */
	spin_lock(&chip->reg_lock);
	क्रम (i = 0; i < chip->num_devs; i++) अणु
		काष्ठा viadev *viadev = &chip->devs[i];
		अचिन्हित अक्षर c_status = inb(VIADEV_REG(viadev, OFFSET_STATUS));
		c_status &= (VIA_REG_STAT_EOL|VIA_REG_STAT_FLAG|VIA_REG_STAT_STOPPED);
		अगर (! c_status)
			जारी;
		अगर (viadev->substream && viadev->running) अणु
			spin_unlock(&chip->reg_lock);
			snd_pcm_period_elapsed(viadev->substream);
			spin_lock(&chip->reg_lock);
		पूर्ण
		outb(c_status, VIADEV_REG(viadev, OFFSET_STATUS)); /* ack */
	पूर्ण
	spin_unlock(&chip->reg_lock);
	वापस IRQ_HANDLED;
पूर्ण

/*
 *  PCM callbacks
 */

/*
 * trigger callback
 */
अटल पूर्णांक snd_via82xx_pcm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा via82xx_modem *chip = snd_pcm_substream_chip(substream);
	काष्ठा viadev *viadev = substream->runसमय->निजी_data;
	अचिन्हित अक्षर val = 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		val |= VIA_REG_CTRL_START;
		viadev->running = 1;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		val = VIA_REG_CTRL_TERMINATE;
		viadev->running = 0;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		val |= VIA_REG_CTRL_PAUSE;
		viadev->running = 0;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		viadev->running = 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	outb(val, VIADEV_REG(viadev, OFFSET_CONTROL));
	अगर (cmd == SNDRV_PCM_TRIGGER_STOP)
		snd_via82xx_channel_reset(chip, viadev);
	वापस 0;
पूर्ण

/*
 * poपूर्णांकer callbacks
 */

/*
 * calculate the linear position at the given sg-buffer index and the rest count
 */

#घोषणा check_invalid_pos(viadev,pos) \
	((pos) < viadev->lastpos && ((pos) >= viadev->bufsize2 ||\
				     viadev->lastpos < viadev->bufsize2))

अटल अंतरभूत अचिन्हित पूर्णांक calc_linear_pos(काष्ठा via82xx_modem *chip,
					   काष्ठा viadev *viadev,
					   अचिन्हित पूर्णांक idx,
					   अचिन्हित पूर्णांक count)
अणु
	अचिन्हित पूर्णांक size, res;

	size = viadev->idx_table[idx].size;
	res = viadev->idx_table[idx].offset + size - count;

	/* check the validity of the calculated position */
	अगर (size < count) अणु
		dev_err(chip->card->dev,
			"invalid via82xx_cur_ptr (size = %d, count = %d)\n",
			   (पूर्णांक)size, (पूर्णांक)count);
		res = viadev->lastpos;
	पूर्ण अन्यथा अगर (check_invalid_pos(viadev, res)) अणु
#अगर_घोषित POINTER_DEBUG
		dev_dbg(chip->card->dev,
			"fail: idx = %i/%i, lastpos = 0x%x, bufsize2 = 0x%x, offsize = 0x%x, size = 0x%x, count = 0x%x\n",
			idx, viadev->tbl_entries, viadev->lastpos,
		       viadev->bufsize2, viadev->idx_table[idx].offset,
		       viadev->idx_table[idx].size, count);
#पूर्ण_अगर
		अगर (count && size < count) अणु
			dev_dbg(chip->card->dev,
				"invalid via82xx_cur_ptr, using last valid pointer\n");
			res = viadev->lastpos;
		पूर्ण अन्यथा अणु
			अगर (! count)
				/* bogus count 0 on the DMA boundary? */
				res = viadev->idx_table[idx].offset;
			अन्यथा
				/* count रेजिस्टर वापसs full size
				 * when end of buffer is reached
				 */
				res = viadev->idx_table[idx].offset + size;
			अगर (check_invalid_pos(viadev, res)) अणु
				dev_dbg(chip->card->dev,
					"invalid via82xx_cur_ptr (2), using last valid pointer\n");
				res = viadev->lastpos;
			पूर्ण
		पूर्ण
	पूर्ण
	viadev->lastpos = res; /* remember the last position */
	अगर (res >= viadev->bufsize)
		res -= viadev->bufsize;
	वापस res;
पूर्ण

/*
 * get the current poपूर्णांकer on via686
 */
अटल snd_pcm_uframes_t snd_via686_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा via82xx_modem *chip = snd_pcm_substream_chip(substream);
	काष्ठा viadev *viadev = substream->runसमय->निजी_data;
	अचिन्हित पूर्णांक idx, ptr, count, res;

	अगर (snd_BUG_ON(!viadev->tbl_entries))
		वापस 0;
	अगर (!(inb(VIADEV_REG(viadev, OFFSET_STATUS)) & VIA_REG_STAT_ACTIVE))
		वापस 0;

	spin_lock(&chip->reg_lock);
	count = inl(VIADEV_REG(viadev, OFFSET_CURR_COUNT)) & 0xffffff;
	/* The via686a करोes not have the current index रेजिस्टर,
	 * so we need to calculate the index from CURR_PTR.
	 */
	ptr = inl(VIADEV_REG(viadev, OFFSET_CURR_PTR));
	अगर (ptr <= (अचिन्हित पूर्णांक)viadev->table.addr)
		idx = 0;
	अन्यथा /* CURR_PTR holds the address + 8 */
		idx = ((ptr - (अचिन्हित पूर्णांक)viadev->table.addr) / 8 - 1) %
			viadev->tbl_entries;
	res = calc_linear_pos(chip, viadev, idx, count);
	spin_unlock(&chip->reg_lock);

	वापस bytes_to_frames(substream->runसमय, res);
पूर्ण

/*
 * hw_params callback:
 * allocate the buffer and build up the buffer description table
 */
अटल पूर्णांक snd_via82xx_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा via82xx_modem *chip = snd_pcm_substream_chip(substream);
	काष्ठा viadev *viadev = substream->runसमय->निजी_data;
	पूर्णांक err;

	err = build_via_table(viadev, substream, chip->pci,
			      params_periods(hw_params),
			      params_period_bytes(hw_params));
	अगर (err < 0)
		वापस err;

	snd_ac97_ग_लिखो(chip->ac97, AC97_LINE1_RATE, params_rate(hw_params));
	snd_ac97_ग_लिखो(chip->ac97, AC97_LINE1_LEVEL, 0);

	वापस 0;
पूर्ण

/*
 * hw_मुक्त callback:
 * clean up the buffer description table and release the buffer
 */
अटल पूर्णांक snd_via82xx_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा via82xx_modem *chip = snd_pcm_substream_chip(substream);
	काष्ठा viadev *viadev = substream->runसमय->निजी_data;

	clean_via_table(viadev, substream, chip->pci);
	वापस 0;
पूर्ण


/*
 * set up the table poपूर्णांकer
 */
अटल व्योम snd_via82xx_set_table_ptr(काष्ठा via82xx_modem *chip, काष्ठा viadev *viadev)
अणु
	snd_via82xx_codec_पढ़ोy(chip, chip->ac97_secondary);
	outl((u32)viadev->table.addr, VIADEV_REG(viadev, OFFSET_TABLE_PTR));
	udelay(20);
	snd_via82xx_codec_पढ़ोy(chip, chip->ac97_secondary);
पूर्ण

/*
 * prepare callback क्रम playback and capture
 */
अटल पूर्णांक snd_via82xx_pcm_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा via82xx_modem *chip = snd_pcm_substream_chip(substream);
	काष्ठा viadev *viadev = substream->runसमय->निजी_data;

	snd_via82xx_channel_reset(chip, viadev);
	/* this must be set after channel_reset */
	snd_via82xx_set_table_ptr(chip, viadev);
	outb(VIA_REG_TYPE_AUTOSTART|VIA_REG_TYPE_INT_EOL|VIA_REG_TYPE_INT_FLAG,
	     VIADEV_REG(viadev, OFFSET_TYPE));
	वापस 0;
पूर्ण

/*
 * pcm hardware definition, identical क्रम both playback and capture
 */
अटल स्थिर काष्ठा snd_pcm_hardware snd_via82xx_hw =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_MMAP_VALID |
				 /* SNDRV_PCM_INFO_RESUME | */
				 SNDRV_PCM_INFO_PAUSE),
	.क्रमmats =		SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000 | SNDRV_PCM_RATE_KNOT,
	.rate_min =		8000,
	.rate_max =		16000,
	.channels_min =		1,
	.channels_max =		1,
	.buffer_bytes_max =	128 * 1024,
	.period_bytes_min =	32,
	.period_bytes_max =	128 * 1024,
	.periods_min =		2,
	.periods_max =		VIA_TABLE_SIZE / 2,
	.fअगरo_size =		0,
पूर्ण;


/*
 * खोलो callback skeleton
 */
अटल पूर्णांक snd_via82xx_modem_pcm_खोलो(काष्ठा via82xx_modem *chip, काष्ठा viadev *viadev,
				      काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;
	अटल स्थिर अचिन्हित पूर्णांक rates[] = अणु 8000,  9600, 12000, 16000 पूर्ण;
	अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list hw_स्थिरraपूर्णांकs_rates = अणु
                .count = ARRAY_SIZE(rates),
                .list = rates,
                .mask = 0,
        पूर्ण;

	runसमय->hw = snd_via82xx_hw;
	
        अगर ((err = snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
					      &hw_स्थिरraपूर्णांकs_rates)) < 0)
                वापस err;

	/* we may हटाओ following स्थिरaपूर्णांक when we modअगरy table entries
	   in पूर्णांकerrupt */
	अगर ((err = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय, SNDRV_PCM_HW_PARAM_PERIODS)) < 0)
		वापस err;

	runसमय->निजी_data = viadev;
	viadev->substream = substream;

	वापस 0;
पूर्ण


/*
 * खोलो callback क्रम playback
 */
अटल पूर्णांक snd_via82xx_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा via82xx_modem *chip = snd_pcm_substream_chip(substream);
	काष्ठा viadev *viadev = &chip->devs[chip->playback_devno + substream->number];

	वापस snd_via82xx_modem_pcm_खोलो(chip, viadev, substream);
पूर्ण

/*
 * खोलो callback क्रम capture
 */
अटल पूर्णांक snd_via82xx_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा via82xx_modem *chip = snd_pcm_substream_chip(substream);
	काष्ठा viadev *viadev = &chip->devs[chip->capture_devno + substream->pcm->device];

	वापस snd_via82xx_modem_pcm_खोलो(chip, viadev, substream);
पूर्ण

/*
 * बंद callback
 */
अटल पूर्णांक snd_via82xx_pcm_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा viadev *viadev = substream->runसमय->निजी_data;

	viadev->substream = शून्य;
	वापस 0;
पूर्ण


/* via686 playback callbacks */
अटल स्थिर काष्ठा snd_pcm_ops snd_via686_playback_ops = अणु
	.खोलो =		snd_via82xx_playback_खोलो,
	.बंद =	snd_via82xx_pcm_बंद,
	.hw_params =	snd_via82xx_hw_params,
	.hw_मुक्त =	snd_via82xx_hw_मुक्त,
	.prepare =	snd_via82xx_pcm_prepare,
	.trigger =	snd_via82xx_pcm_trigger,
	.poपूर्णांकer =	snd_via686_pcm_poपूर्णांकer,
पूर्ण;

/* via686 capture callbacks */
अटल स्थिर काष्ठा snd_pcm_ops snd_via686_capture_ops = अणु
	.खोलो =		snd_via82xx_capture_खोलो,
	.बंद =	snd_via82xx_pcm_बंद,
	.hw_params =	snd_via82xx_hw_params,
	.hw_मुक्त =	snd_via82xx_hw_मुक्त,
	.prepare =	snd_via82xx_pcm_prepare,
	.trigger =	snd_via82xx_pcm_trigger,
	.poपूर्णांकer =	snd_via686_pcm_poपूर्णांकer,
पूर्ण;


अटल व्योम init_viadev(काष्ठा via82xx_modem *chip, पूर्णांक idx, अचिन्हित पूर्णांक reg_offset,
			पूर्णांक direction)
अणु
	chip->devs[idx].reg_offset = reg_offset;
	chip->devs[idx].direction = direction;
	chip->devs[idx].port = chip->port + reg_offset;
पूर्ण

/*
 * create a pcm instance क्रम via686a/b
 */
अटल पूर्णांक snd_via686_pcm_new(काष्ठा via82xx_modem *chip)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	chip->playback_devno = 0;
	chip->capture_devno = 1;
	chip->num_devs = 2;
	chip->पूर्णांकr_mask = 0x330000; /* FLAGS | EOL क्रम MR, MW */

	err = snd_pcm_new(chip->card, chip->card->लघुname, 0, 1, 1, &pcm);
	अगर (err < 0)
		वापस err;
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_via686_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_via686_capture_ops);
	pcm->dev_class = SNDRV_PCM_CLASS_MODEM;
	pcm->निजी_data = chip;
	म_नकल(pcm->name, chip->card->लघुname);
	chip->pcms[0] = pcm;
	init_viadev(chip, 0, VIA_REG_MO_STATUS, 0);
	init_viadev(chip, 1, VIA_REG_MI_STATUS, 1);

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV_SG,
				       &chip->pci->dev, 64*1024, 128*1024);
	वापस 0;
पूर्ण


/*
 *  Mixer part
 */


अटल व्योम snd_via82xx_mixer_मुक्त_ac97_bus(काष्ठा snd_ac97_bus *bus)
अणु
	काष्ठा via82xx_modem *chip = bus->निजी_data;
	chip->ac97_bus = शून्य;
पूर्ण

अटल व्योम snd_via82xx_mixer_मुक्त_ac97(काष्ठा snd_ac97 *ac97)
अणु
	काष्ठा via82xx_modem *chip = ac97->निजी_data;
	chip->ac97 = शून्य;
पूर्ण


अटल पूर्णांक snd_via82xx_mixer_new(काष्ठा via82xx_modem *chip)
अणु
	काष्ठा snd_ac97_ढाँचा ac97;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_ac97_bus_ops ops = अणु
		.ग_लिखो = snd_via82xx_codec_ग_लिखो,
		.पढ़ो = snd_via82xx_codec_पढ़ो,
		.रुको = snd_via82xx_codec_रुको,
	पूर्ण;

	अगर ((err = snd_ac97_bus(chip->card, 0, &ops, chip, &chip->ac97_bus)) < 0)
		वापस err;
	chip->ac97_bus->निजी_मुक्त = snd_via82xx_mixer_मुक्त_ac97_bus;
	chip->ac97_bus->घड़ी = chip->ac97_घड़ी;

	स_रखो(&ac97, 0, माप(ac97));
	ac97.निजी_data = chip;
	ac97.निजी_मुक्त = snd_via82xx_mixer_मुक्त_ac97;
	ac97.pci = chip->pci;
	ac97.scaps = AC97_SCAP_SKIP_AUDIO | AC97_SCAP_POWER_SAVE;
	ac97.num = chip->ac97_secondary;

	अगर ((err = snd_ac97_mixer(chip->ac97_bus, &ac97, &chip->ac97)) < 0)
		वापस err;

	वापस 0;
पूर्ण


/*
 * proc पूर्णांकerface
 */
अटल व्योम snd_via82xx_proc_पढ़ो(काष्ठा snd_info_entry *entry, काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा via82xx_modem *chip = entry->निजी_data;
	पूर्णांक i;
	
	snd_iम_लिखो(buffer, "%s\n\n", chip->card->दीर्घname);
	क्रम (i = 0; i < 0xa0; i += 4) अणु
		snd_iम_लिखो(buffer, "%02x: %08x\n", i, inl(chip->port + i));
	पूर्ण
पूर्ण

अटल व्योम snd_via82xx_proc_init(काष्ठा via82xx_modem *chip)
अणु
	snd_card_ro_proc_new(chip->card, "via82xx", chip,
			     snd_via82xx_proc_पढ़ो);
पूर्ण

/*
 *
 */

अटल पूर्णांक snd_via82xx_chip_init(काष्ठा via82xx_modem *chip)
अणु
	अचिन्हित पूर्णांक val;
	अचिन्हित दीर्घ end_समय;
	अचिन्हित अक्षर pval;

	pci_पढ़ो_config_byte(chip->pci, VIA_MC97_CTRL, &pval);
	अगर((pval & VIA_MC97_CTRL_INIT) != VIA_MC97_CTRL_INIT) अणु
		pci_ग_लिखो_config_byte(chip->pci, 0x44, pval|VIA_MC97_CTRL_INIT);
		udelay(100);
	पूर्ण

	pci_पढ़ो_config_byte(chip->pci, VIA_ACLINK_STAT, &pval);
	अगर (! (pval & VIA_ACLINK_C00_READY)) अणु /* codec not पढ़ोy? */
		/* deनिश्चित ACLink reset, क्रमce SYNC */
		pci_ग_लिखो_config_byte(chip->pci, VIA_ACLINK_CTRL,
				      VIA_ACLINK_CTRL_ENABLE |
				      VIA_ACLINK_CTRL_RESET |
				      VIA_ACLINK_CTRL_SYNC);
		udelay(100);
#अगर 1 /* FIXME: should we करो full reset here क्रम all chip models? */
		pci_ग_लिखो_config_byte(chip->pci, VIA_ACLINK_CTRL, 0x00);
		udelay(100);
#अन्यथा
		/* deनिश्चित ACLink reset, क्रमce SYNC (warm AC'97 reset) */
		pci_ग_लिखो_config_byte(chip->pci, VIA_ACLINK_CTRL,
				      VIA_ACLINK_CTRL_RESET|VIA_ACLINK_CTRL_SYNC);
		udelay(2);
#पूर्ण_अगर
		/* ACLink on, deनिश्चित ACLink reset, VSR, SGD data out */
		pci_ग_लिखो_config_byte(chip->pci, VIA_ACLINK_CTRL, VIA_ACLINK_CTRL_INIT);
		udelay(100);
	पूर्ण
	
	pci_पढ़ो_config_byte(chip->pci, VIA_ACLINK_CTRL, &pval);
	अगर ((pval & VIA_ACLINK_CTRL_INIT) != VIA_ACLINK_CTRL_INIT) अणु
		/* ACLink on, deनिश्चित ACLink reset, VSR, SGD data out */
		pci_ग_लिखो_config_byte(chip->pci, VIA_ACLINK_CTRL, VIA_ACLINK_CTRL_INIT);
		udelay(100);
	पूर्ण

	/* रुको until codec पढ़ोy */
	end_समय = jअगरfies + msecs_to_jअगरfies(750);
	करो अणु
		pci_पढ़ो_config_byte(chip->pci, VIA_ACLINK_STAT, &pval);
		अगर (pval & VIA_ACLINK_C00_READY) /* primary codec पढ़ोy */
			अवरोध;
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, end_समय));

	अगर ((val = snd_via82xx_codec_xपढ़ो(chip)) & VIA_REG_AC97_BUSY)
		dev_err(chip->card->dev,
			"AC'97 codec is not ready [0x%x]\n", val);

	snd_via82xx_codec_xग_लिखो(chip, VIA_REG_AC97_READ |
				 VIA_REG_AC97_SECONDARY_VALID |
				 (VIA_REG_AC97_CODEC_ID_SECONDARY << VIA_REG_AC97_CODEC_ID_SHIFT));
	end_समय = jअगरfies + msecs_to_jअगरfies(750);
	snd_via82xx_codec_xग_लिखो(chip, VIA_REG_AC97_READ |
				 VIA_REG_AC97_SECONDARY_VALID |
				 (VIA_REG_AC97_CODEC_ID_SECONDARY << VIA_REG_AC97_CODEC_ID_SHIFT));
	करो अणु
		अगर ((val = snd_via82xx_codec_xपढ़ो(chip)) & VIA_REG_AC97_SECONDARY_VALID) अणु
			chip->ac97_secondary = 1;
			जाओ __ac97_ok2;
		पूर्ण
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, end_समय));
	/* This is ok, the most of motherboards have only one codec */

      __ac97_ok2:

	/* route FM trap to IRQ, disable FM trap */
	// pci_ग_लिखो_config_byte(chip->pci, VIA_FM_NMI_CTRL, 0);
	/* disable all GPI पूर्णांकerrupts */
	outl(0, VIAREG(chip, GPI_INTR));

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
/*
 * घातer management
 */
अटल पूर्णांक snd_via82xx_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा via82xx_modem *chip = card->निजी_data;
	पूर्णांक i;

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);
	क्रम (i = 0; i < chip->num_devs; i++)
		snd_via82xx_channel_reset(chip, &chip->devs[i]);
	snd_ac97_suspend(chip->ac97);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_via82xx_resume(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा via82xx_modem *chip = card->निजी_data;
	पूर्णांक i;

	snd_via82xx_chip_init(chip);

	snd_ac97_resume(chip->ac97);

	क्रम (i = 0; i < chip->num_devs; i++)
		snd_via82xx_channel_reset(chip, &chip->devs[i]);

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(snd_via82xx_pm, snd_via82xx_suspend, snd_via82xx_resume);
#घोषणा SND_VIA82XX_PM_OPS	&snd_via82xx_pm
#अन्यथा
#घोषणा SND_VIA82XX_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल पूर्णांक snd_via82xx_मुक्त(काष्ठा via82xx_modem *chip)
अणु
	अचिन्हित पूर्णांक i;

	अगर (chip->irq < 0)
		जाओ __end_hw;
	/* disable पूर्णांकerrupts */
	क्रम (i = 0; i < chip->num_devs; i++)
		snd_via82xx_channel_reset(chip, &chip->devs[i]);

      __end_hw:
	अगर (chip->irq >= 0)
		मुक्त_irq(chip->irq, chip);
	pci_release_regions(chip->pci);
	pci_disable_device(chip->pci);
	kमुक्त(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_via82xx_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा via82xx_modem *chip = device->device_data;
	वापस snd_via82xx_मुक्त(chip);
पूर्ण

अटल पूर्णांक snd_via82xx_create(काष्ठा snd_card *card,
			      काष्ठा pci_dev *pci,
			      पूर्णांक chip_type,
			      पूर्णांक revision,
			      अचिन्हित पूर्णांक ac97_घड़ी,
			      काष्ठा via82xx_modem **r_via)
अणु
	काष्ठा via82xx_modem *chip;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =	snd_via82xx_dev_मुक्त,
        पूर्ण;

	अगर ((err = pci_enable_device(pci)) < 0)
		वापस err;

	अगर ((chip = kzalloc(माप(*chip), GFP_KERNEL)) == शून्य) अणु
		pci_disable_device(pci);
		वापस -ENOMEM;
	पूर्ण

	spin_lock_init(&chip->reg_lock);
	chip->card = card;
	chip->pci = pci;
	chip->irq = -1;

	अगर ((err = pci_request_regions(pci, card->driver)) < 0) अणु
		kमुक्त(chip);
		pci_disable_device(pci);
		वापस err;
	पूर्ण
	chip->port = pci_resource_start(pci, 0);
	अगर (request_irq(pci->irq, snd_via82xx_पूर्णांकerrupt, IRQF_SHARED,
			KBUILD_MODNAME, chip)) अणु
		dev_err(card->dev, "unable to grab IRQ %d\n", pci->irq);
		snd_via82xx_मुक्त(chip);
		वापस -EBUSY;
	पूर्ण
	chip->irq = pci->irq;
	card->sync_irq = chip->irq;
	अगर (ac97_घड़ी >= 8000 && ac97_घड़ी <= 48000)
		chip->ac97_घड़ी = ac97_घड़ी;

	अगर ((err = snd_via82xx_chip_init(chip)) < 0) अणु
		snd_via82xx_मुक्त(chip);
		वापस err;
	पूर्ण

	अगर ((err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops)) < 0) अणु
		snd_via82xx_मुक्त(chip);
		वापस err;
	पूर्ण

	/* The 8233 ac97 controller करोes not implement the master bit
	 * in the pci command रेजिस्टर. IMHO this is a violation of the PCI spec.
	 * We call pci_set_master here because it करोes not hurt. */
	pci_set_master(pci);

	*r_via = chip;
	वापस 0;
पूर्ण


अटल पूर्णांक snd_via82xx_probe(काष्ठा pci_dev *pci,
			     स्थिर काष्ठा pci_device_id *pci_id)
अणु
	काष्ठा snd_card *card;
	काष्ठा via82xx_modem *chip;
	पूर्णांक chip_type = 0, card_type;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	err = snd_card_new(&pci->dev, index, id, THIS_MODULE, 0, &card);
	अगर (err < 0)
		वापस err;

	card_type = pci_id->driver_data;
	चयन (card_type) अणु
	हाल TYPE_CARD_VIA82XX_MODEM:
		म_नकल(card->driver, "VIA82XX-MODEM");
		प्र_लिखो(card->लघुname, "VIA 82XX modem");
		अवरोध;
	शेष:
		dev_err(card->dev, "invalid card type %d\n", card_type);
		err = -EINVAL;
		जाओ __error;
	पूर्ण
		
	अगर ((err = snd_via82xx_create(card, pci, chip_type, pci->revision,
				      ac97_घड़ी, &chip)) < 0)
		जाओ __error;
	card->निजी_data = chip;
	अगर ((err = snd_via82xx_mixer_new(chip)) < 0)
		जाओ __error;

	अगर ((err = snd_via686_pcm_new(chip)) < 0 )
		जाओ __error;

	/* disable पूर्णांकerrupts */
	क्रम (i = 0; i < chip->num_devs; i++)
		snd_via82xx_channel_reset(chip, &chip->devs[i]);

	प्र_लिखो(card->दीर्घname, "%s at 0x%lx, irq %d",
		card->लघुname, chip->port, chip->irq);

	snd_via82xx_proc_init(chip);

	अगर ((err = snd_card_रेजिस्टर(card)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	pci_set_drvdata(pci, card);
	वापस 0;

 __error:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

अटल व्योम snd_via82xx_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण

अटल काष्ठा pci_driver via82xx_modem_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_via82xx_modem_ids,
	.probe = snd_via82xx_probe,
	.हटाओ = snd_via82xx_हटाओ,
	.driver = अणु
		.pm = SND_VIA82XX_PM_OPS,
	पूर्ण,
पूर्ण;

module_pci_driver(via82xx_modem_driver);
