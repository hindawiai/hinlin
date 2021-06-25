<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA modem driver क्रम Intel ICH (i8x0) chipsets
 *
 *	Copyright (c) 2000 Jaroslav Kysela <perex@perex.cz>
 *
 *   This is modअगरied (by Sasha Khapyorsky <sashak@alsa-project.org>) version
 *   of ALSA ICH sound driver पूर्णांकel8x0.c .
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
#समावेश <sound/ac97_codec.h>
#समावेश <sound/info.h>
#समावेश <sound/initval.h>

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("Intel 82801AA,82901AB,i810,i820,i830,i840,i845,MX440; "
		   "SiS 7013; NVidia MCP/2/2S/3 modems");
MODULE_LICENSE("GPL");

अटल पूर्णांक index = -2; /* Exclude the first card */
अटल अक्षर *id = SNDRV_DEFAULT_STR1;	/* ID क्रम this card */
अटल पूर्णांक ac97_घड़ी;

module_param(index, पूर्णांक, 0444);
MODULE_PARM_DESC(index, "Index value for Intel i8x0 modemcard.");
module_param(id, अक्षरp, 0444);
MODULE_PARM_DESC(id, "ID string for Intel i8x0 modemcard.");
module_param(ac97_घड़ी, पूर्णांक, 0444);
MODULE_PARM_DESC(ac97_घड़ी, "AC'97 codec clock (0 = auto-detect).");

/* just क्रम backward compatibility */
अटल bool enable;
module_param(enable, bool, 0444);

/*
 *  Direct रेजिस्टरs
 */
क्रमागत अणु DEVICE_INTEL, DEVICE_SIS, DEVICE_ALI, DEVICE_NFORCE पूर्ण;

#घोषणा ICHREG(x) ICH_REG_##x

#घोषणा DEFINE_REGSET(name,base) \
क्रमागत अणु \
	ICH_REG_##name##_BDBAR	= base + 0x0,	/* dword - buffer descriptor list base address */ \
	ICH_REG_##name##_CIV	= base + 0x04,	/* byte - current index value */ \
	ICH_REG_##name##_LVI	= base + 0x05,	/* byte - last valid index */ \
	ICH_REG_##name##_SR	= base + 0x06,	/* byte - status रेजिस्टर */ \
	ICH_REG_##name##_PICB	= base + 0x08,	/* word - position in current buffer */ \
	ICH_REG_##name##_PIV	= base + 0x0a,	/* byte - prefetched index value */ \
	ICH_REG_##name##_CR	= base + 0x0b,	/* byte - control रेजिस्टर */ \
पूर्ण;

/* busmaster blocks */
DEFINE_REGSET(OFF, 0);		/* offset */

/* values क्रम each busmaster block */

/* LVI */
#घोषणा ICH_REG_LVI_MASK		0x1f

/* SR */
#घोषणा ICH_FIFOE			0x10	/* FIFO error */
#घोषणा ICH_BCIS			0x08	/* buffer completion पूर्णांकerrupt status */
#घोषणा ICH_LVBCI			0x04	/* last valid buffer completion पूर्णांकerrupt */
#घोषणा ICH_CELV			0x02	/* current equals last valid */
#घोषणा ICH_DCH				0x01	/* DMA controller halted */

/* PIV */
#घोषणा ICH_REG_PIV_MASK		0x1f	/* mask */

/* CR */
#घोषणा ICH_IOCE			0x10	/* पूर्णांकerrupt on completion enable */
#घोषणा ICH_FEIE			0x08	/* fअगरo error पूर्णांकerrupt enable */
#घोषणा ICH_LVBIE			0x04	/* last valid buffer पूर्णांकerrupt enable */
#घोषणा ICH_RESETREGS			0x02	/* reset busmaster रेजिस्टरs */
#घोषणा ICH_STARTBM			0x01	/* start busmaster operation */


/* global block */
#घोषणा ICH_REG_GLOB_CNT		0x3c	/* dword - global control */
#घोषणा   ICH_TRIE		0x00000040	/* tertiary resume पूर्णांकerrupt enable */
#घोषणा   ICH_SRIE		0x00000020	/* secondary resume पूर्णांकerrupt enable */
#घोषणा   ICH_PRIE		0x00000010	/* primary resume पूर्णांकerrupt enable */
#घोषणा   ICH_ACLINK		0x00000008	/* AClink shut off */
#घोषणा   ICH_AC97WARM		0x00000004	/* AC'97 warm reset */
#घोषणा   ICH_AC97COLD		0x00000002	/* AC'97 cold reset */
#घोषणा   ICH_GIE		0x00000001	/* GPI पूर्णांकerrupt enable */
#घोषणा ICH_REG_GLOB_STA		0x40	/* dword - global status */
#घोषणा   ICH_TRI		0x20000000	/* ICH4: tertiary (AC_SDIN2) resume पूर्णांकerrupt */
#घोषणा   ICH_TCR		0x10000000	/* ICH4: tertiary (AC_SDIN2) codec पढ़ोy */
#घोषणा   ICH_BCS		0x08000000	/* ICH4: bit घड़ी stopped */
#घोषणा   ICH_SPINT		0x04000000	/* ICH4: S/PDIF पूर्णांकerrupt */
#घोषणा   ICH_P2INT		0x02000000	/* ICH4: PCM2-In पूर्णांकerrupt */
#घोषणा   ICH_M2INT		0x01000000	/* ICH4: Mic2-In पूर्णांकerrupt */
#घोषणा   ICH_SAMPLE_CAP	0x00c00000	/* ICH4: sample capability bits (RO) */
#घोषणा   ICH_MULTICHAN_CAP	0x00300000	/* ICH4: multi-channel capability bits (RO) */
#घोषणा   ICH_MD3		0x00020000	/* modem घातer करोwn semaphore */
#घोषणा   ICH_AD3		0x00010000	/* audio घातer करोwn semaphore */
#घोषणा   ICH_RCS		0x00008000	/* पढ़ो completion status */
#घोषणा   ICH_BIT3		0x00004000	/* bit 3 slot 12 */
#घोषणा   ICH_BIT2		0x00002000	/* bit 2 slot 12 */
#घोषणा   ICH_BIT1		0x00001000	/* bit 1 slot 12 */
#घोषणा   ICH_SRI		0x00000800	/* secondary (AC_SDIN1) resume पूर्णांकerrupt */
#घोषणा   ICH_PRI		0x00000400	/* primary (AC_SDIN0) resume पूर्णांकerrupt */
#घोषणा   ICH_SCR		0x00000200	/* secondary (AC_SDIN1) codec पढ़ोy */
#घोषणा   ICH_PCR		0x00000100	/* primary (AC_SDIN0) codec पढ़ोy */
#घोषणा   ICH_MCINT		0x00000080	/* MIC capture पूर्णांकerrupt */
#घोषणा   ICH_POINT		0x00000040	/* playback पूर्णांकerrupt */
#घोषणा   ICH_PIINT		0x00000020	/* capture पूर्णांकerrupt */
#घोषणा   ICH_NVSPINT		0x00000010	/* nक्रमce spdअगर पूर्णांकerrupt */
#घोषणा   ICH_MOINT		0x00000004	/* modem playback पूर्णांकerrupt */
#घोषणा   ICH_MIINT		0x00000002	/* modem capture पूर्णांकerrupt */
#घोषणा   ICH_GSCI		0x00000001	/* GPI status change पूर्णांकerrupt */
#घोषणा ICH_REG_ACC_SEMA		0x44	/* byte - codec ग_लिखो semaphore */
#घोषणा   ICH_CAS		0x01		/* codec access semaphore */

#घोषणा ICH_MAX_FRAGS		32		/* max hw frags */


/*
 *  
 */

क्रमागत अणु ICHD_MDMIN, ICHD_MDMOUT, ICHD_MDMLAST = ICHD_MDMOUT पूर्ण;
क्रमागत अणु ALID_MDMIN, ALID_MDMOUT, ALID_MDMLAST = ALID_MDMOUT पूर्ण;

#घोषणा get_ichdev(substream) (substream->runसमय->निजी_data)

काष्ठा ichdev अणु
	अचिन्हित पूर्णांक ichd;			/* ich device number */
	अचिन्हित दीर्घ reg_offset;		/* offset to bmaddr */
	__le32 *bdbar;				/* CPU address (32bit) */
	अचिन्हित पूर्णांक bdbar_addr;		/* PCI bus address (32bit) */
	काष्ठा snd_pcm_substream *substream;
	अचिन्हित पूर्णांक physbuf;			/* physical address (32bit) */
        अचिन्हित पूर्णांक size;
        अचिन्हित पूर्णांक fragsize;
        अचिन्हित पूर्णांक fragsize1;
        अचिन्हित पूर्णांक position;
        पूर्णांक frags;
        पूर्णांक lvi;
        पूर्णांक lvi_frag;
	पूर्णांक civ;
	पूर्णांक ack;
	पूर्णांक ack_reload;
	अचिन्हित पूर्णांक ack_bit;
	अचिन्हित पूर्णांक roff_sr;
	अचिन्हित पूर्णांक roff_picb;
	अचिन्हित पूर्णांक पूर्णांक_sta_mask;		/* पूर्णांकerrupt status mask */
	अचिन्हित पूर्णांक ali_slot;			/* ALI DMA slot */
	काष्ठा snd_ac97 *ac97;
पूर्ण;

काष्ठा पूर्णांकel8x0m अणु
	अचिन्हित पूर्णांक device_type;

	पूर्णांक irq;

	व्योम __iomem *addr;
	व्योम __iomem *bmaddr;

	काष्ठा pci_dev *pci;
	काष्ठा snd_card *card;

	पूर्णांक pcm_devs;
	काष्ठा snd_pcm *pcm[2];
	काष्ठा ichdev ichd[2];

	अचिन्हित पूर्णांक in_ac97_init: 1;

	काष्ठा snd_ac97_bus *ac97_bus;
	काष्ठा snd_ac97 *ac97;

	spinlock_t reg_lock;
	
	काष्ठा snd_dma_buffer bdbars;
	u32 bdbars_count;
	u32 पूर्णांक_sta_reg;		/* पूर्णांकerrupt status रेजिस्टर */
	u32 पूर्णांक_sta_mask;		/* पूर्णांकerrupt status mask */
	अचिन्हित पूर्णांक pcm_pos_shअगरt;
पूर्ण;

अटल स्थिर काष्ठा pci_device_id snd_पूर्णांकel8x0m_ids[] = अणु
	अणु PCI_VDEVICE(INTEL, 0x2416), DEVICE_INTEL पूर्ण,	/* 82801AA */
	अणु PCI_VDEVICE(INTEL, 0x2426), DEVICE_INTEL पूर्ण,	/* 82901AB */
	अणु PCI_VDEVICE(INTEL, 0x2446), DEVICE_INTEL पूर्ण,	/* 82801BA */
	अणु PCI_VDEVICE(INTEL, 0x2486), DEVICE_INTEL पूर्ण,	/* ICH3 */
	अणु PCI_VDEVICE(INTEL, 0x24c6), DEVICE_INTEL पूर्ण, /* ICH4 */
	अणु PCI_VDEVICE(INTEL, 0x24d6), DEVICE_INTEL पूर्ण, /* ICH5 */
	अणु PCI_VDEVICE(INTEL, 0x266d), DEVICE_INTEL पूर्ण,	/* ICH6 */
	अणु PCI_VDEVICE(INTEL, 0x27dd), DEVICE_INTEL पूर्ण,	/* ICH7 */
	अणु PCI_VDEVICE(INTEL, 0x7196), DEVICE_INTEL पूर्ण,	/* 440MX */
	अणु PCI_VDEVICE(AMD, 0x7446), DEVICE_INTEL पूर्ण,	/* AMD768 */
	अणु PCI_VDEVICE(SI, 0x7013), DEVICE_SIS पूर्ण,	/* SI7013 */
	अणु PCI_VDEVICE(NVIDIA, 0x01c1), DEVICE_NFORCE पूर्ण, /* NFORCE */
	अणु PCI_VDEVICE(NVIDIA, 0x0069), DEVICE_NFORCE पूर्ण, /* NFORCE2 */
	अणु PCI_VDEVICE(NVIDIA, 0x0089), DEVICE_NFORCE पूर्ण, /* NFORCE2s */
	अणु PCI_VDEVICE(NVIDIA, 0x00d9), DEVICE_NFORCE पूर्ण, /* NFORCE3 */
	अणु PCI_VDEVICE(AMD, 0x746e), DEVICE_INTEL पूर्ण,	/* AMD8111 */
#अगर 0
	अणु PCI_VDEVICE(AL, 0x5455), DEVICE_ALI पूर्ण,   /* Ali5455 */
#पूर्ण_अगर
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, snd_पूर्णांकel8x0m_ids);

/*
 *  Lowlevel I/O - busmaster
 */

अटल अंतरभूत u8 igetbyte(काष्ठा पूर्णांकel8x0m *chip, u32 offset)
अणु
	वापस ioपढ़ो8(chip->bmaddr + offset);
पूर्ण

अटल अंतरभूत u16 igetword(काष्ठा पूर्णांकel8x0m *chip, u32 offset)
अणु
	वापस ioपढ़ो16(chip->bmaddr + offset);
पूर्ण

अटल अंतरभूत u32 igetdword(काष्ठा पूर्णांकel8x0m *chip, u32 offset)
अणु
	वापस ioपढ़ो32(chip->bmaddr + offset);
पूर्ण

अटल अंतरभूत व्योम iputbyte(काष्ठा पूर्णांकel8x0m *chip, u32 offset, u8 val)
अणु
	ioग_लिखो8(val, chip->bmaddr + offset);
पूर्ण

अटल अंतरभूत व्योम iputword(काष्ठा पूर्णांकel8x0m *chip, u32 offset, u16 val)
अणु
	ioग_लिखो16(val, chip->bmaddr + offset);
पूर्ण

अटल अंतरभूत व्योम iputdword(काष्ठा पूर्णांकel8x0m *chip, u32 offset, u32 val)
अणु
	ioग_लिखो32(val, chip->bmaddr + offset);
पूर्ण

/*
 *  Lowlevel I/O - AC'97 रेजिस्टरs
 */

अटल अंतरभूत u16 iagetword(काष्ठा पूर्णांकel8x0m *chip, u32 offset)
अणु
	वापस ioपढ़ो16(chip->addr + offset);
पूर्ण

अटल अंतरभूत व्योम iaputword(काष्ठा पूर्णांकel8x0m *chip, u32 offset, u16 val)
अणु
	ioग_लिखो16(val, chip->addr + offset);
पूर्ण

/*
 *  Basic I/O
 */

/*
 * access to AC97 codec via normal i/o (क्रम ICH and SIS7013)
 */

/* वापस the GLOB_STA bit क्रम the corresponding codec */
अटल अचिन्हित पूर्णांक get_ich_codec_bit(काष्ठा पूर्णांकel8x0m *chip, अचिन्हित पूर्णांक codec)
अणु
	अटल स्थिर अचिन्हित पूर्णांक codec_bit[3] = अणु
		ICH_PCR, ICH_SCR, ICH_TCR
	पूर्ण;
	अगर (snd_BUG_ON(codec >= 3))
		वापस ICH_PCR;
	वापस codec_bit[codec];
पूर्ण

अटल पूर्णांक snd_पूर्णांकel8x0m_codec_semaphore(काष्ठा पूर्णांकel8x0m *chip, अचिन्हित पूर्णांक codec)
अणु
	पूर्णांक समय;
	
	अगर (codec > 1)
		वापस -EIO;
	codec = get_ich_codec_bit(chip, codec);

	/* codec पढ़ोy ? */
	अगर ((igetdword(chip, ICHREG(GLOB_STA)) & codec) == 0)
		वापस -EIO;

	/* Anyone holding a semaphore क्रम 1 msec should be shot... */
	समय = 100;
      	करो अणु
      		अगर (!(igetbyte(chip, ICHREG(ACC_SEMA)) & ICH_CAS))
      			वापस 0;
		udelay(10);
	पूर्ण जबतक (समय--);

	/* access to some क्रमbidden (non existent) ac97 रेजिस्टरs will not
	 * reset the semaphore. So even अगर you करोn't get the semaphore, still
	 * जारी the access. We करोn't need the semaphore anyway. */
	dev_err(chip->card->dev,
		"codec_semaphore: semaphore is not ready [0x%x][0x%x]\n",
			igetbyte(chip, ICHREG(ACC_SEMA)), igetdword(chip, ICHREG(GLOB_STA)));
	iagetword(chip, 0);	/* clear semaphore flag */
	/* I करोn't care about the semaphore */
	वापस -EBUSY;
पूर्ण
 
अटल व्योम snd_पूर्णांकel8x0m_codec_ग_लिखो(काष्ठा snd_ac97 *ac97,
				      अचिन्हित लघु reg,
				      अचिन्हित लघु val)
अणु
	काष्ठा पूर्णांकel8x0m *chip = ac97->निजी_data;
	
	अगर (snd_पूर्णांकel8x0m_codec_semaphore(chip, ac97->num) < 0) अणु
		अगर (! chip->in_ac97_init)
			dev_err(chip->card->dev,
				"codec_write %d: semaphore is not ready for register 0x%x\n",
				ac97->num, reg);
	पूर्ण
	iaputword(chip, reg + ac97->num * 0x80, val);
पूर्ण

अटल अचिन्हित लघु snd_पूर्णांकel8x0m_codec_पढ़ो(काष्ठा snd_ac97 *ac97,
					       अचिन्हित लघु reg)
अणु
	काष्ठा पूर्णांकel8x0m *chip = ac97->निजी_data;
	अचिन्हित लघु res;
	अचिन्हित पूर्णांक पंचांगp;

	अगर (snd_पूर्णांकel8x0m_codec_semaphore(chip, ac97->num) < 0) अणु
		अगर (! chip->in_ac97_init)
			dev_err(chip->card->dev,
				"codec_read %d: semaphore is not ready for register 0x%x\n",
				ac97->num, reg);
		res = 0xffff;
	पूर्ण अन्यथा अणु
		res = iagetword(chip, reg + ac97->num * 0x80);
		अगर ((पंचांगp = igetdword(chip, ICHREG(GLOB_STA))) & ICH_RCS) अणु
			/* reset RCS and preserve other R/WC bits */
			iputdword(chip, ICHREG(GLOB_STA),
				  पंचांगp & ~(ICH_SRI|ICH_PRI|ICH_TRI|ICH_GSCI));
			अगर (! chip->in_ac97_init)
				dev_err(chip->card->dev,
					"codec_read %d: read timeout for register 0x%x\n",
					ac97->num, reg);
			res = 0xffff;
		पूर्ण
	पूर्ण
	अगर (reg == AC97_GPIO_STATUS)
		iagetword(chip, 0); /* clear semaphore */
	वापस res;
पूर्ण


/*
 * DMA I/O
 */
अटल व्योम snd_पूर्णांकel8x0m_setup_periods(काष्ठा पूर्णांकel8x0m *chip, काष्ठा ichdev *ichdev)
अणु
	पूर्णांक idx;
	__le32 *bdbar = ichdev->bdbar;
	अचिन्हित दीर्घ port = ichdev->reg_offset;

	iputdword(chip, port + ICH_REG_OFF_BDBAR, ichdev->bdbar_addr);
	अगर (ichdev->size == ichdev->fragsize) अणु
		ichdev->ack_reload = ichdev->ack = 2;
		ichdev->fragsize1 = ichdev->fragsize >> 1;
		क्रम (idx = 0; idx < (ICH_REG_LVI_MASK + 1) * 2; idx += 4) अणु
			bdbar[idx + 0] = cpu_to_le32(ichdev->physbuf);
			bdbar[idx + 1] = cpu_to_le32(0x80000000 | /* पूर्णांकerrupt on completion */
						     ichdev->fragsize1 >> chip->pcm_pos_shअगरt);
			bdbar[idx + 2] = cpu_to_le32(ichdev->physbuf + (ichdev->size >> 1));
			bdbar[idx + 3] = cpu_to_le32(0x80000000 | /* पूर्णांकerrupt on completion */
						     ichdev->fragsize1 >> chip->pcm_pos_shअगरt);
		पूर्ण
		ichdev->frags = 2;
	पूर्ण अन्यथा अणु
		ichdev->ack_reload = ichdev->ack = 1;
		ichdev->fragsize1 = ichdev->fragsize;
		क्रम (idx = 0; idx < (ICH_REG_LVI_MASK + 1) * 2; idx += 2) अणु
			bdbar[idx + 0] = cpu_to_le32(ichdev->physbuf + (((idx >> 1) * ichdev->fragsize) % ichdev->size));
			bdbar[idx + 1] = cpu_to_le32(0x80000000 | /* पूर्णांकerrupt on completion */
						     ichdev->fragsize >> chip->pcm_pos_shअगरt);
			/*
			dev_dbg(chip->card->dev, "bdbar[%i] = 0x%x [0x%x]\n",
			       idx + 0, bdbar[idx + 0], bdbar[idx + 1]);
			*/
		पूर्ण
		ichdev->frags = ichdev->size / ichdev->fragsize;
	पूर्ण
	iputbyte(chip, port + ICH_REG_OFF_LVI, ichdev->lvi = ICH_REG_LVI_MASK);
	ichdev->civ = 0;
	iputbyte(chip, port + ICH_REG_OFF_CIV, 0);
	ichdev->lvi_frag = ICH_REG_LVI_MASK % ichdev->frags;
	ichdev->position = 0;
#अगर 0
	dev_dbg(chip->card->dev,
		"lvi_frag = %i, frags = %i, period_size = 0x%x, period_size1 = 0x%x\n",
	       ichdev->lvi_frag, ichdev->frags, ichdev->fragsize,
	       ichdev->fragsize1);
#पूर्ण_अगर
	/* clear पूर्णांकerrupts */
	iputbyte(chip, port + ichdev->roff_sr, ICH_FIFOE | ICH_BCIS | ICH_LVBCI);
पूर्ण

/*
 *  Interrupt handler
 */

अटल अंतरभूत व्योम snd_पूर्णांकel8x0m_update(काष्ठा पूर्णांकel8x0m *chip, काष्ठा ichdev *ichdev)
अणु
	अचिन्हित दीर्घ port = ichdev->reg_offset;
	पूर्णांक civ, i, step;
	पूर्णांक ack = 0;

	civ = igetbyte(chip, port + ICH_REG_OFF_CIV);
	अगर (civ == ichdev->civ) अणु
		// snd_prपूर्णांकd("civ same %d\n", civ);
		step = 1;
		ichdev->civ++;
		ichdev->civ &= ICH_REG_LVI_MASK;
	पूर्ण अन्यथा अणु
		step = civ - ichdev->civ;
		अगर (step < 0)
			step += ICH_REG_LVI_MASK + 1;
		// अगर (step != 1)
		//	snd_prपूर्णांकd("step = %d, %d -> %d\n", step, ichdev->civ, civ);
		ichdev->civ = civ;
	पूर्ण

	ichdev->position += step * ichdev->fragsize1;
	ichdev->position %= ichdev->size;
	ichdev->lvi += step;
	ichdev->lvi &= ICH_REG_LVI_MASK;
	iputbyte(chip, port + ICH_REG_OFF_LVI, ichdev->lvi);
	क्रम (i = 0; i < step; i++) अणु
		ichdev->lvi_frag++;
		ichdev->lvi_frag %= ichdev->frags;
		ichdev->bdbar[ichdev->lvi * 2] = cpu_to_le32(ichdev->physbuf +
							     ichdev->lvi_frag *
							     ichdev->fragsize1);
#अगर 0
		dev_dbg(chip->card->dev,
			"new: bdbar[%i] = 0x%x [0x%x], prefetch = %i, all = 0x%x, 0x%x\n",
		       ichdev->lvi * 2, ichdev->bdbar[ichdev->lvi * 2],
		       ichdev->bdbar[ichdev->lvi * 2 + 1], inb(ICH_REG_OFF_PIV + port),
		       inl(port + 4), inb(port + ICH_REG_OFF_CR));
#पूर्ण_अगर
		अगर (--ichdev->ack == 0) अणु
			ichdev->ack = ichdev->ack_reload;
			ack = 1;
		पूर्ण
	पूर्ण
	अगर (ack && ichdev->substream) अणु
		spin_unlock(&chip->reg_lock);
		snd_pcm_period_elapsed(ichdev->substream);
		spin_lock(&chip->reg_lock);
	पूर्ण
	iputbyte(chip, port + ichdev->roff_sr, ICH_FIFOE | ICH_BCIS | ICH_LVBCI);
पूर्ण

अटल irqवापस_t snd_पूर्णांकel8x0m_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा पूर्णांकel8x0m *chip = dev_id;
	काष्ठा ichdev *ichdev;
	अचिन्हित पूर्णांक status;
	अचिन्हित पूर्णांक i;

	spin_lock(&chip->reg_lock);
	status = igetdword(chip, chip->पूर्णांक_sta_reg);
	अगर (status == 0xffffffff) अणु /* we are not yet resumed */
		spin_unlock(&chip->reg_lock);
		वापस IRQ_NONE;
	पूर्ण
	अगर ((status & chip->पूर्णांक_sta_mask) == 0) अणु
		अगर (status)
			iputdword(chip, chip->पूर्णांक_sta_reg, status);
		spin_unlock(&chip->reg_lock);
		वापस IRQ_NONE;
	पूर्ण

	क्रम (i = 0; i < chip->bdbars_count; i++) अणु
		ichdev = &chip->ichd[i];
		अगर (status & ichdev->पूर्णांक_sta_mask)
			snd_पूर्णांकel8x0m_update(chip, ichdev);
	पूर्ण

	/* ack them */
	iputdword(chip, chip->पूर्णांक_sta_reg, status & chip->पूर्णांक_sta_mask);
	spin_unlock(&chip->reg_lock);
	
	वापस IRQ_HANDLED;
पूर्ण

/*
 *  PCM part
 */

अटल पूर्णांक snd_पूर्णांकel8x0m_pcm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा पूर्णांकel8x0m *chip = snd_pcm_substream_chip(substream);
	काष्ठा ichdev *ichdev = get_ichdev(substream);
	अचिन्हित अक्षर val = 0;
	अचिन्हित दीर्घ port = ichdev->reg_offset;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		val = ICH_IOCE | ICH_STARTBM;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		val = 0;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		val = ICH_IOCE;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		val = ICH_IOCE | ICH_STARTBM;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	iputbyte(chip, port + ICH_REG_OFF_CR, val);
	अगर (cmd == SNDRV_PCM_TRIGGER_STOP) अणु
		/* रुको until DMA stopped */
		जबतक (!(igetbyte(chip, port + ichdev->roff_sr) & ICH_DCH)) ;
		/* reset whole DMA things */
		iputbyte(chip, port + ICH_REG_OFF_CR, ICH_RESETREGS);
	पूर्ण
	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t snd_पूर्णांकel8x0m_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा पूर्णांकel8x0m *chip = snd_pcm_substream_chip(substream);
	काष्ठा ichdev *ichdev = get_ichdev(substream);
	माप_प्रकार ptr1, ptr;

	ptr1 = igetword(chip, ichdev->reg_offset + ichdev->roff_picb) << chip->pcm_pos_shअगरt;
	अगर (ptr1 != 0)
		ptr = ichdev->fragsize1 - ptr1;
	अन्यथा
		ptr = 0;
	ptr += ichdev->position;
	अगर (ptr >= ichdev->size)
		वापस 0;
	वापस bytes_to_frames(substream->runसमय, ptr);
पूर्ण

अटल पूर्णांक snd_पूर्णांकel8x0m_pcm_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा पूर्णांकel8x0m *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा ichdev *ichdev = get_ichdev(substream);

	ichdev->physbuf = runसमय->dma_addr;
	ichdev->size = snd_pcm_lib_buffer_bytes(substream);
	ichdev->fragsize = snd_pcm_lib_period_bytes(substream);
	snd_ac97_ग_लिखो(ichdev->ac97, AC97_LINE1_RATE, runसमय->rate);
	snd_ac97_ग_लिखो(ichdev->ac97, AC97_LINE1_LEVEL, 0);
	snd_पूर्णांकel8x0m_setup_periods(chip, ichdev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware snd_पूर्णांकel8x0m_stream =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_MMAP_VALID |
				 SNDRV_PCM_INFO_PAUSE |
				 SNDRV_PCM_INFO_RESUME),
	.क्रमmats =		SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000 | SNDRV_PCM_RATE_KNOT,
	.rate_min =		8000,
	.rate_max =		16000,
	.channels_min =		1,
	.channels_max =		1,
	.buffer_bytes_max =	64 * 1024,
	.period_bytes_min =	32,
	.period_bytes_max =	64 * 1024,
	.periods_min =		1,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;


अटल पूर्णांक snd_पूर्णांकel8x0m_pcm_खोलो(काष्ठा snd_pcm_substream *substream, काष्ठा ichdev *ichdev)
अणु
	अटल स्थिर अचिन्हित पूर्णांक rates[] = अणु 8000,  9600, 12000, 16000 पूर्ण;
	अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list hw_स्थिरraपूर्णांकs_rates = अणु
		.count = ARRAY_SIZE(rates),
		.list = rates,
		.mask = 0,
	पूर्ण;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;

	ichdev->substream = substream;
	runसमय->hw = snd_पूर्णांकel8x0m_stream;
	err = snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
					 &hw_स्थिरraपूर्णांकs_rates);
	अगर ( err < 0 )
		वापस err;
	runसमय->निजी_data = ichdev;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_पूर्णांकel8x0m_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा पूर्णांकel8x0m *chip = snd_pcm_substream_chip(substream);

	वापस snd_पूर्णांकel8x0m_pcm_खोलो(substream, &chip->ichd[ICHD_MDMOUT]);
पूर्ण

अटल पूर्णांक snd_पूर्णांकel8x0m_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा पूर्णांकel8x0m *chip = snd_pcm_substream_chip(substream);

	chip->ichd[ICHD_MDMOUT].substream = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_पूर्णांकel8x0m_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा पूर्णांकel8x0m *chip = snd_pcm_substream_chip(substream);

	वापस snd_पूर्णांकel8x0m_pcm_खोलो(substream, &chip->ichd[ICHD_MDMIN]);
पूर्ण

अटल पूर्णांक snd_पूर्णांकel8x0m_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा पूर्णांकel8x0m *chip = snd_pcm_substream_chip(substream);

	chip->ichd[ICHD_MDMIN].substream = शून्य;
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा snd_pcm_ops snd_पूर्णांकel8x0m_playback_ops = अणु
	.खोलो =		snd_पूर्णांकel8x0m_playback_खोलो,
	.बंद =	snd_पूर्णांकel8x0m_playback_बंद,
	.prepare =	snd_पूर्णांकel8x0m_pcm_prepare,
	.trigger =	snd_पूर्णांकel8x0m_pcm_trigger,
	.poपूर्णांकer =	snd_पूर्णांकel8x0m_pcm_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_पूर्णांकel8x0m_capture_ops = अणु
	.खोलो =		snd_पूर्णांकel8x0m_capture_खोलो,
	.बंद =	snd_पूर्णांकel8x0m_capture_बंद,
	.prepare =	snd_पूर्णांकel8x0m_pcm_prepare,
	.trigger =	snd_पूर्णांकel8x0m_pcm_trigger,
	.poपूर्णांकer =	snd_पूर्णांकel8x0m_pcm_poपूर्णांकer,
पूर्ण;


काष्ठा ich_pcm_table अणु
	अक्षर *suffix;
	स्थिर काष्ठा snd_pcm_ops *playback_ops;
	स्थिर काष्ठा snd_pcm_ops *capture_ops;
	माप_प्रकार pपुनः_स्मृति_size;
	माप_प्रकार pपुनः_स्मृति_max_size;
	पूर्णांक ac97_idx;
पूर्ण;

अटल पूर्णांक snd_पूर्णांकel8x0m_pcm1(काष्ठा पूर्णांकel8x0m *chip, पूर्णांक device,
			      स्थिर काष्ठा ich_pcm_table *rec)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;
	अक्षर name[32];

	अगर (rec->suffix)
		प्र_लिखो(name, "Intel ICH - %s", rec->suffix);
	अन्यथा
		म_नकल(name, "Intel ICH");
	err = snd_pcm_new(chip->card, name, device,
			  rec->playback_ops ? 1 : 0,
			  rec->capture_ops ? 1 : 0, &pcm);
	अगर (err < 0)
		वापस err;

	अगर (rec->playback_ops)
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, rec->playback_ops);
	अगर (rec->capture_ops)
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, rec->capture_ops);

	pcm->निजी_data = chip;
	pcm->info_flags = 0;
	pcm->dev_class = SNDRV_PCM_CLASS_MODEM;
	अगर (rec->suffix)
		प्र_लिखो(pcm->name, "%s - %s", chip->card->लघुname, rec->suffix);
	अन्यथा
		म_नकल(pcm->name, chip->card->लघुname);
	chip->pcm[device] = pcm;

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
				       &chip->pci->dev,
				       rec->pपुनः_स्मृति_size,
				       rec->pपुनः_स्मृति_max_size);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ich_pcm_table पूर्णांकel_pcms[] = अणु
	अणु
		.suffix = "Modem",
		.playback_ops = &snd_पूर्णांकel8x0m_playback_ops,
		.capture_ops = &snd_पूर्णांकel8x0m_capture_ops,
		.pपुनः_स्मृति_size = 32 * 1024,
		.pपुनः_स्मृति_max_size = 64 * 1024,
	पूर्ण,
पूर्ण;

अटल पूर्णांक snd_पूर्णांकel8x0m_pcm(काष्ठा पूर्णांकel8x0m *chip)
अणु
	पूर्णांक i, tblsize, device, err;
	स्थिर काष्ठा ich_pcm_table *tbl, *rec;

#अगर 1
	tbl = पूर्णांकel_pcms;
	tblsize = 1;
#अन्यथा
	चयन (chip->device_type) अणु
	हाल DEVICE_NFORCE:
		tbl = nक्रमce_pcms;
		tblsize = ARRAY_SIZE(nक्रमce_pcms);
		अवरोध;
	हाल DEVICE_ALI:
		tbl = ali_pcms;
		tblsize = ARRAY_SIZE(ali_pcms);
		अवरोध;
	शेष:
		tbl = पूर्णांकel_pcms;
		tblsize = 2;
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	device = 0;
	क्रम (i = 0; i < tblsize; i++) अणु
		rec = tbl + i;
		अगर (i > 0 && rec->ac97_idx) अणु
			/* activate PCM only when associated AC'97 codec */
			अगर (! chip->ichd[rec->ac97_idx].ac97)
				जारी;
		पूर्ण
		err = snd_पूर्णांकel8x0m_pcm1(chip, device, rec);
		अगर (err < 0)
			वापस err;
		device++;
	पूर्ण

	chip->pcm_devs = device;
	वापस 0;
पूर्ण
	

/*
 *  Mixer part
 */

अटल व्योम snd_पूर्णांकel8x0m_mixer_मुक्त_ac97_bus(काष्ठा snd_ac97_bus *bus)
अणु
	काष्ठा पूर्णांकel8x0m *chip = bus->निजी_data;
	chip->ac97_bus = शून्य;
पूर्ण

अटल व्योम snd_पूर्णांकel8x0m_mixer_मुक्त_ac97(काष्ठा snd_ac97 *ac97)
अणु
	काष्ठा पूर्णांकel8x0m *chip = ac97->निजी_data;
	chip->ac97 = शून्य;
पूर्ण


अटल पूर्णांक snd_पूर्णांकel8x0m_mixer(काष्ठा पूर्णांकel8x0m *chip, पूर्णांक ac97_घड़ी)
अणु
	काष्ठा snd_ac97_bus *pbus;
	काष्ठा snd_ac97_ढाँचा ac97;
	काष्ठा snd_ac97 *x97;
	पूर्णांक err;
	अचिन्हित पूर्णांक glob_sta = 0;
	अटल स्थिर काष्ठा snd_ac97_bus_ops ops = अणु
		.ग_लिखो = snd_पूर्णांकel8x0m_codec_ग_लिखो,
		.पढ़ो = snd_पूर्णांकel8x0m_codec_पढ़ो,
	पूर्ण;

	chip->in_ac97_init = 1;
	
	स_रखो(&ac97, 0, माप(ac97));
	ac97.निजी_data = chip;
	ac97.निजी_मुक्त = snd_पूर्णांकel8x0m_mixer_मुक्त_ac97;
	ac97.scaps = AC97_SCAP_SKIP_AUDIO | AC97_SCAP_POWER_SAVE;

	glob_sta = igetdword(chip, ICHREG(GLOB_STA));

	अगर ((err = snd_ac97_bus(chip->card, 0, &ops, chip, &pbus)) < 0)
		जाओ __err;
	pbus->निजी_मुक्त = snd_पूर्णांकel8x0m_mixer_मुक्त_ac97_bus;
	अगर (ac97_घड़ी >= 8000 && ac97_घड़ी <= 48000)
		pbus->घड़ी = ac97_घड़ी;
	chip->ac97_bus = pbus;

	ac97.pci = chip->pci;
	ac97.num = glob_sta & ICH_SCR ? 1 : 0;
	अगर ((err = snd_ac97_mixer(pbus, &ac97, &x97)) < 0) अणु
		dev_err(chip->card->dev,
			"Unable to initialize codec #%d\n", ac97.num);
		अगर (ac97.num == 0)
			जाओ __err;
		वापस err;
	पूर्ण
	chip->ac97 = x97;
	अगर(ac97_is_modem(x97) && !chip->ichd[ICHD_MDMIN].ac97) अणु
		chip->ichd[ICHD_MDMIN].ac97 = x97;
		chip->ichd[ICHD_MDMOUT].ac97 = x97;
	पूर्ण

	chip->in_ac97_init = 0;
	वापस 0;

 __err:
	/* clear the cold-reset bit क्रम the next chance */
	अगर (chip->device_type != DEVICE_ALI)
		iputdword(chip, ICHREG(GLOB_CNT),
			  igetdword(chip, ICHREG(GLOB_CNT)) & ~ICH_AC97COLD);
	वापस err;
पूर्ण


/*
 *
 */

अटल पूर्णांक snd_पूर्णांकel8x0m_ich_chip_init(काष्ठा पूर्णांकel8x0m *chip, पूर्णांक probing)
अणु
	अचिन्हित दीर्घ end_समय;
	अचिन्हित पूर्णांक cnt, status, nstatus;
	
	/* put logic to right state */
	/* first clear status bits */
	status = ICH_RCS | ICH_MIINT | ICH_MOINT;
	cnt = igetdword(chip, ICHREG(GLOB_STA));
	iputdword(chip, ICHREG(GLOB_STA), cnt & status);

	/* ACLink on, 2 channels */
	cnt = igetdword(chip, ICHREG(GLOB_CNT));
	cnt &= ~(ICH_ACLINK);
	/* finish cold or करो warm reset */
	cnt |= (cnt & ICH_AC97COLD) == 0 ? ICH_AC97COLD : ICH_AC97WARM;
	iputdword(chip, ICHREG(GLOB_CNT), cnt);
	usleep_range(500, 1000); /* give warm reset some समय */
	end_समय = jअगरfies + HZ / 4;
	करो अणु
		अगर ((igetdword(chip, ICHREG(GLOB_CNT)) & ICH_AC97WARM) == 0)
			जाओ __ok;
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण जबतक (समय_after_eq(end_समय, jअगरfies));
	dev_err(chip->card->dev, "AC'97 warm reset still in progress? [0x%x]\n",
		   igetdword(chip, ICHREG(GLOB_CNT)));
	वापस -EIO;

      __ok:
	अगर (probing) अणु
		/* रुको क्रम any codec पढ़ोy status.
		 * Once it becomes पढ़ोy it should reमुख्य पढ़ोy
		 * as दीर्घ as we करो not disable the ac97 link.
		 */
		end_समय = jअगरfies + HZ;
		करो अणु
			status = igetdword(chip, ICHREG(GLOB_STA)) &
				(ICH_PCR | ICH_SCR | ICH_TCR);
			अगर (status)
				अवरोध;
			schedule_समयout_unपूर्णांकerruptible(1);
		पूर्ण जबतक (समय_after_eq(end_समय, jअगरfies));
		अगर (! status) अणु
			/* no codec is found */
			dev_err(chip->card->dev,
				"codec_ready: codec is not ready [0x%x]\n",
				   igetdword(chip, ICHREG(GLOB_STA)));
			वापस -EIO;
		पूर्ण

		/* up to two codecs (modem cannot be tertiary with ICH4) */
		nstatus = ICH_PCR | ICH_SCR;

		/* रुको क्रम other codecs पढ़ोy status. */
		end_समय = jअगरfies + HZ / 4;
		जबतक (status != nstatus && समय_after_eq(end_समय, jअगरfies)) अणु
			schedule_समयout_unपूर्णांकerruptible(1);
			status |= igetdword(chip, ICHREG(GLOB_STA)) & nstatus;
		पूर्ण

	पूर्ण अन्यथा अणु
		/* resume phase */
		status = 0;
		अगर (chip->ac97)
			status |= get_ich_codec_bit(chip, chip->ac97->num);
		/* रुको until all the probed codecs are पढ़ोy */
		end_समय = jअगरfies + HZ;
		करो अणु
			nstatus = igetdword(chip, ICHREG(GLOB_STA)) &
				(ICH_PCR | ICH_SCR | ICH_TCR);
			अगर (status == nstatus)
				अवरोध;
			schedule_समयout_unपूर्णांकerruptible(1);
		पूर्ण जबतक (समय_after_eq(end_समय, jअगरfies));
	पूर्ण

	अगर (chip->device_type == DEVICE_SIS) अणु
		/* unmute the output on SIS7012 */
		iputword(chip, 0x4c, igetword(chip, 0x4c) | 1);
	पूर्ण

      	वापस 0;
पूर्ण

अटल पूर्णांक snd_पूर्णांकel8x0m_chip_init(काष्ठा पूर्णांकel8x0m *chip, पूर्णांक probing)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;
	
	अगर ((err = snd_पूर्णांकel8x0m_ich_chip_init(chip, probing)) < 0)
		वापस err;
	iagetword(chip, 0);	/* clear semaphore flag */

	/* disable पूर्णांकerrupts */
	क्रम (i = 0; i < chip->bdbars_count; i++)
		iputbyte(chip, ICH_REG_OFF_CR + chip->ichd[i].reg_offset, 0x00);
	/* reset channels */
	क्रम (i = 0; i < chip->bdbars_count; i++)
		iputbyte(chip, ICH_REG_OFF_CR + chip->ichd[i].reg_offset, ICH_RESETREGS);
	/* initialize Buffer Descriptor Lists */
	क्रम (i = 0; i < chip->bdbars_count; i++)
		iputdword(chip, ICH_REG_OFF_BDBAR + chip->ichd[i].reg_offset, chip->ichd[i].bdbar_addr);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_पूर्णांकel8x0m_मुक्त(काष्ठा पूर्णांकel8x0m *chip)
अणु
	अचिन्हित पूर्णांक i;

	अगर (chip->irq < 0)
		जाओ __hw_end;
	/* disable पूर्णांकerrupts */
	क्रम (i = 0; i < chip->bdbars_count; i++)
		iputbyte(chip, ICH_REG_OFF_CR + chip->ichd[i].reg_offset, 0x00);
	/* reset channels */
	क्रम (i = 0; i < chip->bdbars_count; i++)
		iputbyte(chip, ICH_REG_OFF_CR + chip->ichd[i].reg_offset, ICH_RESETREGS);
 __hw_end:
	अगर (chip->irq >= 0)
		मुक्त_irq(chip->irq, chip);
	अगर (chip->bdbars.area)
		snd_dma_मुक्त_pages(&chip->bdbars);
	अगर (chip->addr)
		pci_iounmap(chip->pci, chip->addr);
	अगर (chip->bmaddr)
		pci_iounmap(chip->pci, chip->bmaddr);
	pci_release_regions(chip->pci);
	pci_disable_device(chip->pci);
	kमुक्त(chip);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
/*
 * घातer management
 */
अटल पूर्णांक पूर्णांकel8x0m_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा पूर्णांकel8x0m *chip = card->निजी_data;

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);
	snd_ac97_suspend(chip->ac97);
	अगर (chip->irq >= 0) अणु
		मुक्त_irq(chip->irq, chip);
		chip->irq = -1;
		card->sync_irq = -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel8x0m_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci = to_pci_dev(dev);
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा पूर्णांकel8x0m *chip = card->निजी_data;

	अगर (request_irq(pci->irq, snd_पूर्णांकel8x0m_पूर्णांकerrupt,
			IRQF_SHARED, KBUILD_MODNAME, chip)) अणु
		dev_err(dev, "unable to grab IRQ %d, disabling device\n",
			pci->irq);
		snd_card_disconnect(card);
		वापस -EIO;
	पूर्ण
	chip->irq = pci->irq;
	card->sync_irq = chip->irq;
	snd_पूर्णांकel8x0m_chip_init(chip, 0);
	snd_ac97_resume(chip->ac97);

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(पूर्णांकel8x0m_pm, पूर्णांकel8x0m_suspend, पूर्णांकel8x0m_resume);
#घोषणा INTEL8X0M_PM_OPS	&पूर्णांकel8x0m_pm
#अन्यथा
#घोषणा INTEL8X0M_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल व्योम snd_पूर्णांकel8x0m_proc_पढ़ो(काष्ठा snd_info_entry * entry,
				   काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा पूर्णांकel8x0m *chip = entry->निजी_data;
	अचिन्हित पूर्णांक पंचांगp;

	snd_iम_लिखो(buffer, "Intel8x0m\n\n");
	अगर (chip->device_type == DEVICE_ALI)
		वापस;
	पंचांगp = igetdword(chip, ICHREG(GLOB_STA));
	snd_iम_लिखो(buffer, "Global control        : 0x%08x\n",
		    igetdword(chip, ICHREG(GLOB_CNT)));
	snd_iम_लिखो(buffer, "Global status         : 0x%08x\n", पंचांगp);
	snd_iम_लिखो(buffer, "AC'97 codecs ready    :%s%s%s%s\n",
			पंचांगp & ICH_PCR ? " primary" : "",
			पंचांगp & ICH_SCR ? " secondary" : "",
			पंचांगp & ICH_TCR ? " tertiary" : "",
			(पंचांगp & (ICH_PCR | ICH_SCR | ICH_TCR)) == 0 ? " none" : "");
पूर्ण

अटल व्योम snd_पूर्णांकel8x0m_proc_init(काष्ठा पूर्णांकel8x0m *chip)
अणु
	snd_card_ro_proc_new(chip->card, "intel8x0m", chip,
			     snd_पूर्णांकel8x0m_proc_पढ़ो);
पूर्ण

अटल पूर्णांक snd_पूर्णांकel8x0m_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा पूर्णांकel8x0m *chip = device->device_data;
	वापस snd_पूर्णांकel8x0m_मुक्त(chip);
पूर्ण

काष्ठा ich_reg_info अणु
	अचिन्हित पूर्णांक पूर्णांक_sta_mask;
	अचिन्हित पूर्णांक offset;
पूर्ण;

अटल पूर्णांक snd_पूर्णांकel8x0m_create(काष्ठा snd_card *card,
				काष्ठा pci_dev *pci,
				अचिन्हित दीर्घ device_type,
				काष्ठा पूर्णांकel8x0m **r_पूर्णांकel8x0m)
अणु
	काष्ठा पूर्णांकel8x0m *chip;
	पूर्णांक err;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक पूर्णांक_sta_masks;
	काष्ठा ichdev *ichdev;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =	snd_पूर्णांकel8x0m_dev_मुक्त,
	पूर्ण;
	अटल स्थिर काष्ठा ich_reg_info पूर्णांकel_regs[2] = अणु
		अणु ICH_MIINT, 0 पूर्ण,
		अणु ICH_MOINT, 0x10 पूर्ण,
	पूर्ण;
	स्थिर काष्ठा ich_reg_info *tbl;

	*r_पूर्णांकel8x0m = शून्य;

	अगर ((err = pci_enable_device(pci)) < 0)
		वापस err;

	chip = kzalloc(माप(*chip), GFP_KERNEL);
	अगर (chip == शून्य) अणु
		pci_disable_device(pci);
		वापस -ENOMEM;
	पूर्ण
	spin_lock_init(&chip->reg_lock);
	chip->device_type = device_type;
	chip->card = card;
	chip->pci = pci;
	chip->irq = -1;

	अगर ((err = pci_request_regions(pci, card->लघुname)) < 0) अणु
		kमुक्त(chip);
		pci_disable_device(pci);
		वापस err;
	पूर्ण

	अगर (device_type == DEVICE_ALI) अणु
		/* ALI5455 has no ac97 region */
		chip->bmaddr = pci_iomap(pci, 0, 0);
		जाओ port_inited;
	पूर्ण

	अगर (pci_resource_flags(pci, 2) & IORESOURCE_MEM) /* ICH4 and Nक्रमce */
		chip->addr = pci_iomap(pci, 2, 0);
	अन्यथा
		chip->addr = pci_iomap(pci, 0, 0);
	अगर (!chip->addr) अणु
		dev_err(card->dev, "AC'97 space ioremap problem\n");
		snd_पूर्णांकel8x0m_मुक्त(chip);
		वापस -EIO;
	पूर्ण
	अगर (pci_resource_flags(pci, 3) & IORESOURCE_MEM) /* ICH4 */
		chip->bmaddr = pci_iomap(pci, 3, 0);
	अन्यथा
		chip->bmaddr = pci_iomap(pci, 1, 0);

port_inited:
	अगर (!chip->bmaddr) अणु
		dev_err(card->dev, "Controller space ioremap problem\n");
		snd_पूर्णांकel8x0m_मुक्त(chip);
		वापस -EIO;
	पूर्ण

	/* initialize offsets */
	chip->bdbars_count = 2;
	tbl = पूर्णांकel_regs;

	क्रम (i = 0; i < chip->bdbars_count; i++) अणु
		ichdev = &chip->ichd[i];
		ichdev->ichd = i;
		ichdev->reg_offset = tbl[i].offset;
		ichdev->पूर्णांक_sta_mask = tbl[i].पूर्णांक_sta_mask;
		अगर (device_type == DEVICE_SIS) अणु
			/* SiS 7013 swaps the रेजिस्टरs */
			ichdev->roff_sr = ICH_REG_OFF_PICB;
			ichdev->roff_picb = ICH_REG_OFF_SR;
		पूर्ण अन्यथा अणु
			ichdev->roff_sr = ICH_REG_OFF_SR;
			ichdev->roff_picb = ICH_REG_OFF_PICB;
		पूर्ण
		अगर (device_type == DEVICE_ALI)
			ichdev->ali_slot = (ichdev->reg_offset - 0x40) / 0x10;
	पूर्ण
	/* SIS7013 handles the pcm data in bytes, others are in words */
	chip->pcm_pos_shअगरt = (device_type == DEVICE_SIS) ? 0 : 1;

	/* allocate buffer descriptor lists */
	/* the start of each lists must be aligned to 8 bytes */
	अगर (snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, &pci->dev,
				chip->bdbars_count * माप(u32) * ICH_MAX_FRAGS * 2,
				&chip->bdbars) < 0) अणु
		snd_पूर्णांकel8x0m_मुक्त(chip);
		वापस -ENOMEM;
	पूर्ण
	/* tables must be aligned to 8 bytes here, but the kernel pages
	   are much bigger, so we करोn't care (on i386) */
	पूर्णांक_sta_masks = 0;
	क्रम (i = 0; i < chip->bdbars_count; i++) अणु
		ichdev = &chip->ichd[i];
		ichdev->bdbar = ((__le32 *)chip->bdbars.area) + (i * ICH_MAX_FRAGS * 2);
		ichdev->bdbar_addr = chip->bdbars.addr + (i * माप(u32) * ICH_MAX_FRAGS * 2);
		पूर्णांक_sta_masks |= ichdev->पूर्णांक_sta_mask;
	पूर्ण
	chip->पूर्णांक_sta_reg = ICH_REG_GLOB_STA;
	chip->पूर्णांक_sta_mask = पूर्णांक_sta_masks;

	pci_set_master(pci);

	अगर ((err = snd_पूर्णांकel8x0m_chip_init(chip, 1)) < 0) अणु
		snd_पूर्णांकel8x0m_मुक्त(chip);
		वापस err;
	पूर्ण

	अगर (request_irq(pci->irq, snd_पूर्णांकel8x0m_पूर्णांकerrupt, IRQF_SHARED,
			KBUILD_MODNAME, chip)) अणु
		dev_err(card->dev, "unable to grab IRQ %d\n", pci->irq);
		snd_पूर्णांकel8x0m_मुक्त(chip);
		वापस -EBUSY;
	पूर्ण
	chip->irq = pci->irq;
	card->sync_irq = chip->irq;

	अगर ((err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops)) < 0) अणु
		snd_पूर्णांकel8x0m_मुक्त(chip);
		वापस err;
	पूर्ण

	*r_पूर्णांकel8x0m = chip;
	वापस 0;
पूर्ण

अटल काष्ठा लघुname_table अणु
	अचिन्हित पूर्णांक id;
	स्थिर अक्षर *s;
पूर्ण लघुnames[] = अणु
	अणु PCI_DEVICE_ID_INTEL_82801AA_6, "Intel 82801AA-ICH" पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82801AB_6, "Intel 82901AB-ICH0" पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82801BA_6, "Intel 82801BA-ICH2" पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_440MX_6, "Intel 440MX" पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82801CA_6, "Intel 82801CA-ICH3" पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82801DB_6, "Intel 82801DB-ICH4" पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82801EB_6, "Intel ICH5" पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_ICH6_17, "Intel ICH6" पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_ICH7_19, "Intel ICH7" पूर्ण,
	अणु 0x7446, "AMD AMD768" पूर्ण,
	अणु PCI_DEVICE_ID_SI_7013, "SiS SI7013" पूर्ण,
	अणु PCI_DEVICE_ID_NVIDIA_MCP1_MODEM, "NVidia nForce" पूर्ण,
	अणु PCI_DEVICE_ID_NVIDIA_MCP2_MODEM, "NVidia nForce2" पूर्ण,
	अणु PCI_DEVICE_ID_NVIDIA_MCP2S_MODEM, "NVidia nForce2s" पूर्ण,
	अणु PCI_DEVICE_ID_NVIDIA_MCP3_MODEM, "NVidia nForce3" पूर्ण,
	अणु 0x746e, "AMD AMD8111" पूर्ण,
#अगर 0
	अणु 0x5455, "ALi M5455" पूर्ण,
#पूर्ण_अगर
	अणु 0 पूर्ण,
पूर्ण;

अटल पूर्णांक snd_पूर्णांकel8x0m_probe(काष्ठा pci_dev *pci,
			       स्थिर काष्ठा pci_device_id *pci_id)
अणु
	काष्ठा snd_card *card;
	काष्ठा पूर्णांकel8x0m *chip;
	पूर्णांक err;
	काष्ठा लघुname_table *name;

	err = snd_card_new(&pci->dev, index, id, THIS_MODULE, 0, &card);
	अगर (err < 0)
		वापस err;

	म_नकल(card->driver, "ICH-MODEM");
	म_नकल(card->लघुname, "Intel ICH");
	क्रम (name = लघुnames; name->id; name++) अणु
		अगर (pci->device == name->id) अणु
			म_नकल(card->लघुname, name->s);
			अवरोध;
		पूर्ण
	पूर्ण
	म_जोड़ो(card->लघुname," Modem");

	अगर ((err = snd_पूर्णांकel8x0m_create(card, pci, pci_id->driver_data, &chip)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	card->निजी_data = chip;

	अगर ((err = snd_पूर्णांकel8x0m_mixer(chip, ac97_घड़ी)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	अगर ((err = snd_पूर्णांकel8x0m_pcm(chip)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	
	snd_पूर्णांकel8x0m_proc_init(chip);

	प्र_लिखो(card->दीर्घname, "%s at irq %i",
		card->लघुname, chip->irq);

	अगर ((err = snd_card_रेजिस्टर(card)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	pci_set_drvdata(pci, card);
	वापस 0;
पूर्ण

अटल व्योम snd_पूर्णांकel8x0m_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण

अटल काष्ठा pci_driver पूर्णांकel8x0m_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_पूर्णांकel8x0m_ids,
	.probe = snd_पूर्णांकel8x0m_probe,
	.हटाओ = snd_पूर्णांकel8x0m_हटाओ,
	.driver = अणु
		.pm = INTEL8X0M_PM_OPS,
	पूर्ण,
पूर्ण;

module_pci_driver(पूर्णांकel8x0m_driver);
