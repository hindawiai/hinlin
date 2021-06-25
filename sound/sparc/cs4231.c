<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम CS4231 sound chips found on Sparcs.
 * Copyright (C) 2002, 2008 David S. Miller <davem@davemloft.net>
 *
 * Based entirely upon drivers/sbus/audio/cs4231.c which is:
 * Copyright (C) 1996, 1997, 1998 Derrick J Brashear (shaकरोw@andrew.cmu.edu)
 * and also sound/isa/cs423x/cs4231_lib.c which is:
 * Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/info.h>
#समावेश <sound/control.h>
#समावेश <sound/समयr.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm_params.h>

#अगर_घोषित CONFIG_SBUS
#घोषणा SBUS_SUPPORT
#पूर्ण_अगर

#अगर defined(CONFIG_PCI) && defined(CONFIG_SPARC64)
#घोषणा EBUS_SUPPORT
#समावेश <linux/pci.h>
#समावेश <यंत्र/ebus_dma.h>
#पूर्ण_अगर

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
/* Enable this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for Sun CS4231 soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for Sun CS4231 soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable Sun CS4231 soundcard.");
MODULE_AUTHOR("Jaroslav Kysela, Derrick J. Brashear and David S. Miller");
MODULE_DESCRIPTION("Sun CS4231");
MODULE_LICENSE("GPL");

#अगर_घोषित SBUS_SUPPORT
काष्ठा sbus_dma_info अणु
       spinlock_t	lock;	/* DMA access lock */
       पूर्णांक		dir;
       व्योम __iomem	*regs;
पूर्ण;
#पूर्ण_अगर

काष्ठा snd_cs4231;
काष्ठा cs4231_dma_control अणु
	व्योम		(*prepare)(काष्ठा cs4231_dma_control *dma_cont,
				   पूर्णांक dir);
	व्योम		(*enable)(काष्ठा cs4231_dma_control *dma_cont, पूर्णांक on);
	पूर्णांक		(*request)(काष्ठा cs4231_dma_control *dma_cont,
				   dma_addr_t bus_addr, माप_प्रकार len);
	अचिन्हित पूर्णांक	(*address)(काष्ठा cs4231_dma_control *dma_cont);
#अगर_घोषित EBUS_SUPPORT
	काष्ठा		ebus_dma_info	ebus_info;
#पूर्ण_अगर
#अगर_घोषित SBUS_SUPPORT
	काष्ठा		sbus_dma_info	sbus_info;
#पूर्ण_अगर
पूर्ण;

काष्ठा snd_cs4231 अणु
	spinlock_t		lock;	/* रेजिस्टरs access lock */
	व्योम __iomem		*port;

	काष्ठा cs4231_dma_control	p_dma;
	काष्ठा cs4231_dma_control	c_dma;

	u32			flags;
#घोषणा CS4231_FLAG_EBUS	0x00000001
#घोषणा CS4231_FLAG_PLAYBACK	0x00000002
#घोषणा CS4231_FLAG_CAPTURE	0x00000004

	काष्ठा snd_card		*card;
	काष्ठा snd_pcm		*pcm;
	काष्ठा snd_pcm_substream	*playback_substream;
	अचिन्हित पूर्णांक		p_periods_sent;
	काष्ठा snd_pcm_substream	*capture_substream;
	अचिन्हित पूर्णांक		c_periods_sent;
	काष्ठा snd_समयr	*समयr;

	अचिन्हित लघु mode;
#घोषणा CS4231_MODE_NONE	0x0000
#घोषणा CS4231_MODE_PLAY	0x0001
#घोषणा CS4231_MODE_RECORD	0x0002
#घोषणा CS4231_MODE_TIMER	0x0004
#घोषणा CS4231_MODE_OPEN	(CS4231_MODE_PLAY | CS4231_MODE_RECORD | \
				 CS4231_MODE_TIMER)

	अचिन्हित अक्षर		image[32];	/* रेजिस्टरs image */
	पूर्णांक			mce_bit;
	पूर्णांक			calibrate_mute;
	काष्ठा mutex		mce_mutex;	/* mutex क्रम mce रेजिस्टर */
	काष्ठा mutex		खोलो_mutex;	/* mutex क्रम ALSA खोलो/बंद */

	काष्ठा platक्रमm_device	*op;
	अचिन्हित पूर्णांक		irq[2];
	अचिन्हित पूर्णांक		regs_size;
	काष्ठा snd_cs4231	*next;
पूर्ण;

/* Eventually we can use sound/isa/cs423x/cs4231_lib.c directly, but क्रम
 * now....  -DaveM
 */

/* IO ports */
#समावेश <sound/cs4231-regs.h>

/* XXX offsets are dअगरferent than PC ISA chips... */
#घोषणा CS4231U(chip, x)	((chip)->port + ((c_d_c_CS4231##x) << 2))

/* SBUS DMA रेजिस्टर defines.  */

#घोषणा APCCSR	0x10UL	/* APC DMA CSR */
#घोषणा APCCVA	0x20UL	/* APC Capture DMA Address */
#घोषणा APCCC	0x24UL	/* APC Capture Count */
#घोषणा APCCNVA	0x28UL	/* APC Capture DMA Next Address */
#घोषणा APCCNC	0x2cUL	/* APC Capture Next Count */
#घोषणा APCPVA	0x30UL	/* APC Play DMA Address */
#घोषणा APCPC	0x34UL	/* APC Play Count */
#घोषणा APCPNVA	0x38UL	/* APC Play DMA Next Address */
#घोषणा APCPNC	0x3cUL	/* APC Play Next Count */

/* Defines क्रम SBUS DMA-routines */

#घोषणा APCVA  0x0UL	/* APC DMA Address */
#घोषणा APCC   0x4UL	/* APC Count */
#घोषणा APCNVA 0x8UL	/* APC DMA Next Address */
#घोषणा APCNC  0xcUL	/* APC Next Count */
#घोषणा APC_PLAY 0x30UL	/* Play रेजिस्टरs start at 0x30 */
#घोषणा APC_RECORD 0x20UL /* Record रेजिस्टरs start at 0x20 */

/* APCCSR bits */

#घोषणा APC_INT_PENDING 0x800000 /* Interrupt Pending */
#घोषणा APC_PLAY_INT    0x400000 /* Playback पूर्णांकerrupt */
#घोषणा APC_CAPT_INT    0x200000 /* Capture पूर्णांकerrupt */
#घोषणा APC_GENL_INT    0x100000 /* General पूर्णांकerrupt */
#घोषणा APC_XINT_ENA    0x80000  /* General ext पूर्णांक. enable */
#घोषणा APC_XINT_PLAY   0x40000  /* Playback ext पूर्णांकr */
#घोषणा APC_XINT_CAPT   0x20000  /* Capture ext पूर्णांकr */
#घोषणा APC_XINT_GENL   0x10000  /* Error ext पूर्णांकr */
#घोषणा APC_XINT_EMPT   0x8000   /* Pipe empty पूर्णांकerrupt (0 ग_लिखो to pva) */
#घोषणा APC_XINT_PEMP   0x4000   /* Play pipe empty (pva and pnva not set) */
#घोषणा APC_XINT_PNVA   0x2000   /* Playback NVA dirty */
#घोषणा APC_XINT_PENA   0x1000   /* play pipe empty Int enable */
#घोषणा APC_XINT_COVF   0x800    /* Cap data dropped on न्यूनमान */
#घोषणा APC_XINT_CNVA   0x400    /* Capture NVA dirty */
#घोषणा APC_XINT_CEMP   0x200    /* Capture pipe empty (cva and cnva not set) */
#घोषणा APC_XINT_CENA   0x100    /* Cap. pipe empty पूर्णांक enable */
#घोषणा APC_PPAUSE      0x80     /* Pause the play DMA */
#घोषणा APC_CPAUSE      0x40     /* Pause the capture DMA */
#घोषणा APC_CDC_RESET   0x20     /* CODEC RESET */
#घोषणा APC_PDMA_READY  0x08     /* Play DMA Go */
#घोषणा APC_CDMA_READY  0x04     /* Capture DMA Go */
#घोषणा APC_CHIP_RESET  0x01     /* Reset the chip */

/* EBUS DMA रेजिस्टर offsets  */

#घोषणा EBDMA_CSR	0x00UL	/* Control/Status */
#घोषणा EBDMA_ADDR	0x04UL	/* DMA Address */
#घोषणा EBDMA_COUNT	0x08UL	/* DMA Count */

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
	.count	= ARRAY_SIZE(rates),
	.list	= rates,
पूर्ण;

अटल पूर्णांक snd_cs4231_xrate(काष्ठा snd_pcm_runसमय *runसमय)
अणु
	वापस snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0,
					  SNDRV_PCM_HW_PARAM_RATE,
					  &hw_स्थिरraपूर्णांकs_rates);
पूर्ण

अटल स्थिर अचिन्हित अक्षर snd_cs4231_original_image[32] =
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
	0x00,			/* 0d/13 - lbc */
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
	0x00,			/* 1a/26 - mioc */
	0x00,			/* 1b/27 - ramoc/reserved */
	0x20,			/* 1c/28 - cdfr */
	0x00,			/* 1d/29 - res4 */
	0x00,			/* 1e/30 - cbru */
	0x00,			/* 1f/31 - cbrl */
पूर्ण;

अटल u8 __cs4231_पढ़ोb(काष्ठा snd_cs4231 *cp, व्योम __iomem *reg_addr)
अणु
	अगर (cp->flags & CS4231_FLAG_EBUS)
		वापस पढ़ोb(reg_addr);
	अन्यथा
		वापस sbus_पढ़ोb(reg_addr);
पूर्ण

अटल व्योम __cs4231_ग_लिखोb(काष्ठा snd_cs4231 *cp, u8 val,
			    व्योम __iomem *reg_addr)
अणु
	अगर (cp->flags & CS4231_FLAG_EBUS)
		वापस ग_लिखोb(val, reg_addr);
	अन्यथा
		वापस sbus_ग_लिखोb(val, reg_addr);
पूर्ण

/*
 *  Basic I/O functions
 */

अटल व्योम snd_cs4231_पढ़ोy(काष्ठा snd_cs4231 *chip)
अणु
	पूर्णांक समयout;

	क्रम (समयout = 250; समयout > 0; समयout--) अणु
		पूर्णांक val = __cs4231_पढ़ोb(chip, CS4231U(chip, REGSEL));
		अगर ((val & CS4231_INIT) == 0)
			अवरोध;
		udelay(100);
	पूर्ण
पूर्ण

अटल व्योम snd_cs4231_करोut(काष्ठा snd_cs4231 *chip, अचिन्हित अक्षर reg,
			    अचिन्हित अक्षर value)
अणु
	snd_cs4231_पढ़ोy(chip);
#अगर_घोषित CONFIG_SND_DEBUG
	अगर (__cs4231_पढ़ोb(chip, CS4231U(chip, REGSEL)) & CS4231_INIT)
		snd_prपूर्णांकdd("out: auto calibration time out - reg = 0x%x, "
			    "value = 0x%x\n",
			    reg, value);
#पूर्ण_अगर
	__cs4231_ग_लिखोb(chip, chip->mce_bit | reg, CS4231U(chip, REGSEL));
	wmb();
	__cs4231_ग_लिखोb(chip, value, CS4231U(chip, REG));
	mb();
पूर्ण

अटल अंतरभूत व्योम snd_cs4231_ouपंचांग(काष्ठा snd_cs4231 *chip, अचिन्हित अक्षर reg,
		     अचिन्हित अक्षर mask, अचिन्हित अक्षर value)
अणु
	अचिन्हित अक्षर पंचांगp = (chip->image[reg] & mask) | value;

	chip->image[reg] = पंचांगp;
	अगर (!chip->calibrate_mute)
		snd_cs4231_करोut(chip, reg, पंचांगp);
पूर्ण

अटल व्योम snd_cs4231_out(काष्ठा snd_cs4231 *chip, अचिन्हित अक्षर reg,
			   अचिन्हित अक्षर value)
अणु
	snd_cs4231_करोut(chip, reg, value);
	chip->image[reg] = value;
	mb();
पूर्ण

अटल अचिन्हित अक्षर snd_cs4231_in(काष्ठा snd_cs4231 *chip, अचिन्हित अक्षर reg)
अणु
	snd_cs4231_पढ़ोy(chip);
#अगर_घोषित CONFIG_SND_DEBUG
	अगर (__cs4231_पढ़ोb(chip, CS4231U(chip, REGSEL)) & CS4231_INIT)
		snd_prपूर्णांकdd("in: auto calibration time out - reg = 0x%x\n",
			    reg);
#पूर्ण_अगर
	__cs4231_ग_लिखोb(chip, chip->mce_bit | reg, CS4231U(chip, REGSEL));
	mb();
	वापस __cs4231_पढ़ोb(chip, CS4231U(chip, REG));
पूर्ण

/*
 *  CS4231 detection / MCE routines
 */

अटल व्योम snd_cs4231_busy_रुको(काष्ठा snd_cs4231 *chip)
अणु
	पूर्णांक समयout;

	/* looks like this sequence is proper क्रम CS4231A chip (GUS MAX) */
	क्रम (समयout = 5; समयout > 0; समयout--)
		__cs4231_पढ़ोb(chip, CS4231U(chip, REGSEL));

	/* end of cleanup sequence */
	क्रम (समयout = 500; समयout > 0; समयout--) अणु
		पूर्णांक val = __cs4231_पढ़ोb(chip, CS4231U(chip, REGSEL));
		अगर ((val & CS4231_INIT) == 0)
			अवरोध;
		msleep(1);
	पूर्ण
पूर्ण

अटल व्योम snd_cs4231_mce_up(काष्ठा snd_cs4231 *chip)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक समयout;

	spin_lock_irqsave(&chip->lock, flags);
	snd_cs4231_पढ़ोy(chip);
#अगर_घोषित CONFIG_SND_DEBUG
	अगर (__cs4231_पढ़ोb(chip, CS4231U(chip, REGSEL)) & CS4231_INIT)
		snd_prपूर्णांकdd("mce_up - auto calibration time out (0)\n");
#पूर्ण_अगर
	chip->mce_bit |= CS4231_MCE;
	समयout = __cs4231_पढ़ोb(chip, CS4231U(chip, REGSEL));
	अगर (समयout == 0x80)
		snd_prपूर्णांकdd("mce_up [%p]: serious init problem - "
			    "codec still busy\n",
			    chip->port);
	अगर (!(समयout & CS4231_MCE))
		__cs4231_ग_लिखोb(chip, chip->mce_bit | (समयout & 0x1f),
				CS4231U(chip, REGSEL));
	spin_unlock_irqrestore(&chip->lock, flags);
पूर्ण

अटल व्योम snd_cs4231_mce_करोwn(काष्ठा snd_cs4231 *chip)
अणु
	अचिन्हित दीर्घ flags, समयout;
	पूर्णांक reg;

	snd_cs4231_busy_रुको(chip);
	spin_lock_irqsave(&chip->lock, flags);
#अगर_घोषित CONFIG_SND_DEBUG
	अगर (__cs4231_पढ़ोb(chip, CS4231U(chip, REGSEL)) & CS4231_INIT)
		snd_prपूर्णांकdd("mce_down [%p] - auto calibration time out (0)\n",
			    CS4231U(chip, REGSEL));
#पूर्ण_अगर
	chip->mce_bit &= ~CS4231_MCE;
	reg = __cs4231_पढ़ोb(chip, CS4231U(chip, REGSEL));
	__cs4231_ग_लिखोb(chip, chip->mce_bit | (reg & 0x1f),
			CS4231U(chip, REGSEL));
	अगर (reg == 0x80)
		snd_prपूर्णांकdd("mce_down [%p]: serious init problem "
			    "- codec still busy\n", chip->port);
	अगर ((reg & CS4231_MCE) == 0) अणु
		spin_unlock_irqrestore(&chip->lock, flags);
		वापस;
	पूर्ण

	/*
	 * Wait क्रम स्वतः-calibration (AC) process to finish, i.e. ACI to go low.
	 */
	समयout = jअगरfies + msecs_to_jअगरfies(250);
	करो अणु
		spin_unlock_irqrestore(&chip->lock, flags);
		msleep(1);
		spin_lock_irqsave(&chip->lock, flags);
		reg = snd_cs4231_in(chip, CS4231_TEST_INIT);
		reg &= CS4231_CALIB_IN_PROGRESS;
	पूर्ण जबतक (reg && समय_beक्रमe(jअगरfies, समयout));
	spin_unlock_irqrestore(&chip->lock, flags);

	अगर (reg)
		snd_prपूर्णांकk(KERN_ERR
			   "mce_down - auto calibration time out (2)\n");
पूर्ण

अटल व्योम snd_cs4231_advance_dma(काष्ठा cs4231_dma_control *dma_cont,
				   काष्ठा snd_pcm_substream *substream,
				   अचिन्हित पूर्णांक *periods_sent)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	जबतक (1) अणु
		अचिन्हित पूर्णांक period_size = snd_pcm_lib_period_bytes(substream);
		अचिन्हित पूर्णांक offset = period_size * (*periods_sent);

		अगर (WARN_ON(period_size >= (1 << 24)))
			वापस;

		अगर (dma_cont->request(dma_cont,
				      runसमय->dma_addr + offset, period_size))
			वापस;
		(*periods_sent) = ((*periods_sent) + 1) % runसमय->periods;
	पूर्ण
पूर्ण

अटल व्योम cs4231_dma_trigger(काष्ठा snd_pcm_substream *substream,
			       अचिन्हित पूर्णांक what, पूर्णांक on)
अणु
	काष्ठा snd_cs4231 *chip = snd_pcm_substream_chip(substream);
	काष्ठा cs4231_dma_control *dma_cont;

	अगर (what & CS4231_PLAYBACK_ENABLE) अणु
		dma_cont = &chip->p_dma;
		अगर (on) अणु
			dma_cont->prepare(dma_cont, 0);
			dma_cont->enable(dma_cont, 1);
			snd_cs4231_advance_dma(dma_cont,
				chip->playback_substream,
				&chip->p_periods_sent);
		पूर्ण अन्यथा अणु
			dma_cont->enable(dma_cont, 0);
		पूर्ण
	पूर्ण
	अगर (what & CS4231_RECORD_ENABLE) अणु
		dma_cont = &chip->c_dma;
		अगर (on) अणु
			dma_cont->prepare(dma_cont, 1);
			dma_cont->enable(dma_cont, 1);
			snd_cs4231_advance_dma(dma_cont,
				chip->capture_substream,
				&chip->c_periods_sent);
		पूर्ण अन्यथा अणु
			dma_cont->enable(dma_cont, 0);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक snd_cs4231_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_cs4231 *chip = snd_pcm_substream_chip(substream);
	पूर्णांक result = 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_STOP:
	अणु
		अचिन्हित पूर्णांक what = 0;
		काष्ठा snd_pcm_substream *s;
		अचिन्हित दीर्घ flags;

		snd_pcm_group_क्रम_each_entry(s, substream) अणु
			अगर (s == chip->playback_substream) अणु
				what |= CS4231_PLAYBACK_ENABLE;
				snd_pcm_trigger_करोne(s, substream);
			पूर्ण अन्यथा अगर (s == chip->capture_substream) अणु
				what |= CS4231_RECORD_ENABLE;
				snd_pcm_trigger_करोne(s, substream);
			पूर्ण
		पूर्ण

		spin_lock_irqsave(&chip->lock, flags);
		अगर (cmd == SNDRV_PCM_TRIGGER_START) अणु
			cs4231_dma_trigger(substream, what, 1);
			chip->image[CS4231_IFACE_CTRL] |= what;
		पूर्ण अन्यथा अणु
			cs4231_dma_trigger(substream, what, 0);
			chip->image[CS4231_IFACE_CTRL] &= ~what;
		पूर्ण
		snd_cs4231_out(chip, CS4231_IFACE_CTRL,
			       chip->image[CS4231_IFACE_CTRL]);
		spin_unlock_irqrestore(&chip->lock, flags);
		अवरोध;
	पूर्ण
	शेष:
		result = -EINVAL;
		अवरोध;
	पूर्ण

	वापस result;
पूर्ण

/*
 *  CODEC I/O
 */

अटल अचिन्हित अक्षर snd_cs4231_get_rate(अचिन्हित पूर्णांक rate)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 14; i++)
		अगर (rate == rates[i])
			वापस freq_bits[i];

	वापस freq_bits[13];
पूर्ण

अटल अचिन्हित अक्षर snd_cs4231_get_क्रमmat(काष्ठा snd_cs4231 *chip, पूर्णांक क्रमmat,
					   पूर्णांक channels)
अणु
	अचिन्हित अक्षर rक्रमmat;

	rक्रमmat = CS4231_LINEAR_8;
	चयन (क्रमmat) अणु
	हाल SNDRV_PCM_FORMAT_MU_LAW:
		rक्रमmat = CS4231_ULAW_8;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_A_LAW:
		rक्रमmat = CS4231_ALAW_8;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S16_LE:
		rक्रमmat = CS4231_LINEAR_16;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S16_BE:
		rक्रमmat = CS4231_LINEAR_16_BIG;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_IMA_ADPCM:
		rक्रमmat = CS4231_ADPCM_16;
		अवरोध;
	पूर्ण
	अगर (channels > 1)
		rक्रमmat |= CS4231_STEREO;
	वापस rक्रमmat;
पूर्ण

अटल व्योम snd_cs4231_calibrate_mute(काष्ठा snd_cs4231 *chip, पूर्णांक mute)
अणु
	अचिन्हित दीर्घ flags;

	mute = mute ? 1 : 0;
	spin_lock_irqsave(&chip->lock, flags);
	अगर (chip->calibrate_mute == mute) अणु
		spin_unlock_irqrestore(&chip->lock, flags);
		वापस;
	पूर्ण
	अगर (!mute) अणु
		snd_cs4231_करोut(chip, CS4231_LEFT_INPUT,
				chip->image[CS4231_LEFT_INPUT]);
		snd_cs4231_करोut(chip, CS4231_RIGHT_INPUT,
				chip->image[CS4231_RIGHT_INPUT]);
		snd_cs4231_करोut(chip, CS4231_LOOPBACK,
				chip->image[CS4231_LOOPBACK]);
	पूर्ण
	snd_cs4231_करोut(chip, CS4231_AUX1_LEFT_INPUT,
			mute ? 0x80 : chip->image[CS4231_AUX1_LEFT_INPUT]);
	snd_cs4231_करोut(chip, CS4231_AUX1_RIGHT_INPUT,
			mute ? 0x80 : chip->image[CS4231_AUX1_RIGHT_INPUT]);
	snd_cs4231_करोut(chip, CS4231_AUX2_LEFT_INPUT,
			mute ? 0x80 : chip->image[CS4231_AUX2_LEFT_INPUT]);
	snd_cs4231_करोut(chip, CS4231_AUX2_RIGHT_INPUT,
			mute ? 0x80 : chip->image[CS4231_AUX2_RIGHT_INPUT]);
	snd_cs4231_करोut(chip, CS4231_LEFT_OUTPUT,
			mute ? 0x80 : chip->image[CS4231_LEFT_OUTPUT]);
	snd_cs4231_करोut(chip, CS4231_RIGHT_OUTPUT,
			mute ? 0x80 : chip->image[CS4231_RIGHT_OUTPUT]);
	snd_cs4231_करोut(chip, CS4231_LEFT_LINE_IN,
			mute ? 0x80 : chip->image[CS4231_LEFT_LINE_IN]);
	snd_cs4231_करोut(chip, CS4231_RIGHT_LINE_IN,
			mute ? 0x80 : chip->image[CS4231_RIGHT_LINE_IN]);
	snd_cs4231_करोut(chip, CS4231_MONO_CTRL,
			mute ? 0xc0 : chip->image[CS4231_MONO_CTRL]);
	chip->calibrate_mute = mute;
	spin_unlock_irqrestore(&chip->lock, flags);
पूर्ण

अटल व्योम snd_cs4231_playback_क्रमmat(काष्ठा snd_cs4231 *chip,
				       काष्ठा snd_pcm_hw_params *params,
				       अचिन्हित अक्षर pdfr)
अणु
	अचिन्हित दीर्घ flags;

	mutex_lock(&chip->mce_mutex);
	snd_cs4231_calibrate_mute(chip, 1);

	snd_cs4231_mce_up(chip);

	spin_lock_irqsave(&chip->lock, flags);
	snd_cs4231_out(chip, CS4231_PLAYBK_FORMAT,
		       (chip->image[CS4231_IFACE_CTRL] & CS4231_RECORD_ENABLE) ?
		       (pdfr & 0xf0) | (chip->image[CS4231_REC_FORMAT] & 0x0f) :
		       pdfr);
	spin_unlock_irqrestore(&chip->lock, flags);

	snd_cs4231_mce_करोwn(chip);

	snd_cs4231_calibrate_mute(chip, 0);
	mutex_unlock(&chip->mce_mutex);
पूर्ण

अटल व्योम snd_cs4231_capture_क्रमmat(काष्ठा snd_cs4231 *chip,
				      काष्ठा snd_pcm_hw_params *params,
				      अचिन्हित अक्षर cdfr)
अणु
	अचिन्हित दीर्घ flags;

	mutex_lock(&chip->mce_mutex);
	snd_cs4231_calibrate_mute(chip, 1);

	snd_cs4231_mce_up(chip);

	spin_lock_irqsave(&chip->lock, flags);
	अगर (!(chip->image[CS4231_IFACE_CTRL] & CS4231_PLAYBACK_ENABLE)) अणु
		snd_cs4231_out(chip, CS4231_PLAYBK_FORMAT,
			       ((chip->image[CS4231_PLAYBK_FORMAT]) & 0xf0) |
			       (cdfr & 0x0f));
		spin_unlock_irqrestore(&chip->lock, flags);
		snd_cs4231_mce_करोwn(chip);
		snd_cs4231_mce_up(chip);
		spin_lock_irqsave(&chip->lock, flags);
	पूर्ण
	snd_cs4231_out(chip, CS4231_REC_FORMAT, cdfr);
	spin_unlock_irqrestore(&chip->lock, flags);

	snd_cs4231_mce_करोwn(chip);

	snd_cs4231_calibrate_mute(chip, 0);
	mutex_unlock(&chip->mce_mutex);
पूर्ण

/*
 *  Timer पूर्णांकerface
 */

अटल अचिन्हित दीर्घ snd_cs4231_समयr_resolution(काष्ठा snd_समयr *समयr)
अणु
	काष्ठा snd_cs4231 *chip = snd_समयr_chip(समयr);

	वापस chip->image[CS4231_PLAYBK_FORMAT] & 1 ? 9969 : 9920;
पूर्ण

अटल पूर्णांक snd_cs4231_समयr_start(काष्ठा snd_समयr *समयr)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक ticks;
	काष्ठा snd_cs4231 *chip = snd_समयr_chip(समयr);

	spin_lock_irqsave(&chip->lock, flags);
	ticks = समयr->sticks;
	अगर ((chip->image[CS4231_ALT_FEATURE_1] & CS4231_TIMER_ENABLE) == 0 ||
	    (अचिन्हित अक्षर)(ticks >> 8) != chip->image[CS4231_TIMER_HIGH] ||
	    (अचिन्हित अक्षर)ticks != chip->image[CS4231_TIMER_LOW]) अणु
		snd_cs4231_out(chip, CS4231_TIMER_HIGH,
			       chip->image[CS4231_TIMER_HIGH] =
			       (अचिन्हित अक्षर) (ticks >> 8));
		snd_cs4231_out(chip, CS4231_TIMER_LOW,
			       chip->image[CS4231_TIMER_LOW] =
			       (अचिन्हित अक्षर) ticks);
		snd_cs4231_out(chip, CS4231_ALT_FEATURE_1,
			       chip->image[CS4231_ALT_FEATURE_1] |
					CS4231_TIMER_ENABLE);
	पूर्ण
	spin_unlock_irqrestore(&chip->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4231_समयr_stop(काष्ठा snd_समयr *समयr)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_cs4231 *chip = snd_समयr_chip(समयr);

	spin_lock_irqsave(&chip->lock, flags);
	chip->image[CS4231_ALT_FEATURE_1] &= ~CS4231_TIMER_ENABLE;
	snd_cs4231_out(chip, CS4231_ALT_FEATURE_1,
		       chip->image[CS4231_ALT_FEATURE_1]);
	spin_unlock_irqrestore(&chip->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम snd_cs4231_init(काष्ठा snd_cs4231 *chip)
अणु
	अचिन्हित दीर्घ flags;

	snd_cs4231_mce_करोwn(chip);

#अगर_घोषित SNDRV_DEBUG_MCE
	snd_prपूर्णांकdd("init: (1)\n");
#पूर्ण_अगर
	snd_cs4231_mce_up(chip);
	spin_lock_irqsave(&chip->lock, flags);
	chip->image[CS4231_IFACE_CTRL] &= ~(CS4231_PLAYBACK_ENABLE |
					    CS4231_PLAYBACK_PIO |
					    CS4231_RECORD_ENABLE |
					    CS4231_RECORD_PIO |
					    CS4231_CALIB_MODE);
	chip->image[CS4231_IFACE_CTRL] |= CS4231_AUTOCALIB;
	snd_cs4231_out(chip, CS4231_IFACE_CTRL, chip->image[CS4231_IFACE_CTRL]);
	spin_unlock_irqrestore(&chip->lock, flags);
	snd_cs4231_mce_करोwn(chip);

#अगर_घोषित SNDRV_DEBUG_MCE
	snd_prपूर्णांकdd("init: (2)\n");
#पूर्ण_अगर

	snd_cs4231_mce_up(chip);
	spin_lock_irqsave(&chip->lock, flags);
	snd_cs4231_out(chip, CS4231_ALT_FEATURE_1,
			chip->image[CS4231_ALT_FEATURE_1]);
	spin_unlock_irqrestore(&chip->lock, flags);
	snd_cs4231_mce_करोwn(chip);

#अगर_घोषित SNDRV_DEBUG_MCE
	snd_prपूर्णांकdd("init: (3) - afei = 0x%x\n",
		    chip->image[CS4231_ALT_FEATURE_1]);
#पूर्ण_अगर

	spin_lock_irqsave(&chip->lock, flags);
	snd_cs4231_out(chip, CS4231_ALT_FEATURE_2,
			chip->image[CS4231_ALT_FEATURE_2]);
	spin_unlock_irqrestore(&chip->lock, flags);

	snd_cs4231_mce_up(chip);
	spin_lock_irqsave(&chip->lock, flags);
	snd_cs4231_out(chip, CS4231_PLAYBK_FORMAT,
			chip->image[CS4231_PLAYBK_FORMAT]);
	spin_unlock_irqrestore(&chip->lock, flags);
	snd_cs4231_mce_करोwn(chip);

#अगर_घोषित SNDRV_DEBUG_MCE
	snd_prपूर्णांकdd("init: (4)\n");
#पूर्ण_अगर

	snd_cs4231_mce_up(chip);
	spin_lock_irqsave(&chip->lock, flags);
	snd_cs4231_out(chip, CS4231_REC_FORMAT, chip->image[CS4231_REC_FORMAT]);
	spin_unlock_irqrestore(&chip->lock, flags);
	snd_cs4231_mce_करोwn(chip);

#अगर_घोषित SNDRV_DEBUG_MCE
	snd_prपूर्णांकdd("init: (5)\n");
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक snd_cs4231_खोलो(काष्ठा snd_cs4231 *chip, अचिन्हित पूर्णांक mode)
अणु
	अचिन्हित दीर्घ flags;

	mutex_lock(&chip->खोलो_mutex);
	अगर ((chip->mode & mode)) अणु
		mutex_unlock(&chip->खोलो_mutex);
		वापस -EAGAIN;
	पूर्ण
	अगर (chip->mode & CS4231_MODE_OPEN) अणु
		chip->mode |= mode;
		mutex_unlock(&chip->खोलो_mutex);
		वापस 0;
	पूर्ण
	/* ok. now enable and ack CODEC IRQ */
	spin_lock_irqsave(&chip->lock, flags);
	snd_cs4231_out(chip, CS4231_IRQ_STATUS, CS4231_PLAYBACK_IRQ |
		       CS4231_RECORD_IRQ |
		       CS4231_TIMER_IRQ);
	snd_cs4231_out(chip, CS4231_IRQ_STATUS, 0);
	__cs4231_ग_लिखोb(chip, 0, CS4231U(chip, STATUS));	/* clear IRQ */
	__cs4231_ग_लिखोb(chip, 0, CS4231U(chip, STATUS));	/* clear IRQ */

	snd_cs4231_out(chip, CS4231_IRQ_STATUS, CS4231_PLAYBACK_IRQ |
		       CS4231_RECORD_IRQ |
		       CS4231_TIMER_IRQ);
	snd_cs4231_out(chip, CS4231_IRQ_STATUS, 0);

	spin_unlock_irqrestore(&chip->lock, flags);

	chip->mode = mode;
	mutex_unlock(&chip->खोलो_mutex);
	वापस 0;
पूर्ण

अटल व्योम snd_cs4231_बंद(काष्ठा snd_cs4231 *chip, अचिन्हित पूर्णांक mode)
अणु
	अचिन्हित दीर्घ flags;

	mutex_lock(&chip->खोलो_mutex);
	chip->mode &= ~mode;
	अगर (chip->mode & CS4231_MODE_OPEN) अणु
		mutex_unlock(&chip->खोलो_mutex);
		वापस;
	पूर्ण
	snd_cs4231_calibrate_mute(chip, 1);

	/* disable IRQ */
	spin_lock_irqsave(&chip->lock, flags);
	snd_cs4231_out(chip, CS4231_IRQ_STATUS, 0);
	__cs4231_ग_लिखोb(chip, 0, CS4231U(chip, STATUS));	/* clear IRQ */
	__cs4231_ग_लिखोb(chip, 0, CS4231U(chip, STATUS));	/* clear IRQ */

	/* now disable record & playback */

	अगर (chip->image[CS4231_IFACE_CTRL] &
	    (CS4231_PLAYBACK_ENABLE | CS4231_PLAYBACK_PIO |
	     CS4231_RECORD_ENABLE | CS4231_RECORD_PIO)) अणु
		spin_unlock_irqrestore(&chip->lock, flags);
		snd_cs4231_mce_up(chip);
		spin_lock_irqsave(&chip->lock, flags);
		chip->image[CS4231_IFACE_CTRL] &=
			~(CS4231_PLAYBACK_ENABLE | CS4231_PLAYBACK_PIO |
			  CS4231_RECORD_ENABLE | CS4231_RECORD_PIO);
		snd_cs4231_out(chip, CS4231_IFACE_CTRL,
				chip->image[CS4231_IFACE_CTRL]);
		spin_unlock_irqrestore(&chip->lock, flags);
		snd_cs4231_mce_करोwn(chip);
		spin_lock_irqsave(&chip->lock, flags);
	पूर्ण

	/* clear IRQ again */
	snd_cs4231_out(chip, CS4231_IRQ_STATUS, 0);
	__cs4231_ग_लिखोb(chip, 0, CS4231U(chip, STATUS));	/* clear IRQ */
	__cs4231_ग_लिखोb(chip, 0, CS4231U(chip, STATUS));	/* clear IRQ */
	spin_unlock_irqrestore(&chip->lock, flags);

	snd_cs4231_calibrate_mute(chip, 0);

	chip->mode = 0;
	mutex_unlock(&chip->खोलो_mutex);
पूर्ण

/*
 *  समयr खोलो/बंद
 */

अटल पूर्णांक snd_cs4231_समयr_खोलो(काष्ठा snd_समयr *समयr)
अणु
	काष्ठा snd_cs4231 *chip = snd_समयr_chip(समयr);
	snd_cs4231_खोलो(chip, CS4231_MODE_TIMER);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4231_समयr_बंद(काष्ठा snd_समयr *समयr)
अणु
	काष्ठा snd_cs4231 *chip = snd_समयr_chip(समयr);
	snd_cs4231_बंद(chip, CS4231_MODE_TIMER);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_समयr_hardware snd_cs4231_समयr_table = अणु
	.flags		=	SNDRV_TIMER_HW_AUTO,
	.resolution	=	9945,
	.ticks		=	65535,
	.खोलो		=	snd_cs4231_समयr_खोलो,
	.बंद		=	snd_cs4231_समयr_बंद,
	.c_resolution	=	snd_cs4231_समयr_resolution,
	.start		=	snd_cs4231_समयr_start,
	.stop		=	snd_cs4231_समयr_stop,
पूर्ण;

/*
 *  ok.. exported functions..
 */

अटल पूर्णांक snd_cs4231_playback_hw_params(काष्ठा snd_pcm_substream *substream,
					 काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_cs4231 *chip = snd_pcm_substream_chip(substream);
	अचिन्हित अक्षर new_pdfr;

	new_pdfr = snd_cs4231_get_क्रमmat(chip, params_क्रमmat(hw_params),
					 params_channels(hw_params)) |
		snd_cs4231_get_rate(params_rate(hw_params));
	snd_cs4231_playback_क्रमmat(chip, hw_params, new_pdfr);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4231_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_cs4231 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&chip->lock, flags);

	chip->image[CS4231_IFACE_CTRL] &= ~(CS4231_PLAYBACK_ENABLE |
					    CS4231_PLAYBACK_PIO);

	अगर (WARN_ON(runसमय->period_size > 0xffff + 1)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	chip->p_periods_sent = 0;

out:
	spin_unlock_irqrestore(&chip->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक snd_cs4231_capture_hw_params(काष्ठा snd_pcm_substream *substream,
					काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_cs4231 *chip = snd_pcm_substream_chip(substream);
	अचिन्हित अक्षर new_cdfr;

	new_cdfr = snd_cs4231_get_क्रमmat(chip, params_क्रमmat(hw_params),
					 params_channels(hw_params)) |
		snd_cs4231_get_rate(params_rate(hw_params));
	snd_cs4231_capture_क्रमmat(chip, hw_params, new_cdfr);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4231_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_cs4231 *chip = snd_pcm_substream_chip(substream);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->lock, flags);
	chip->image[CS4231_IFACE_CTRL] &= ~(CS4231_RECORD_ENABLE |
					    CS4231_RECORD_PIO);


	chip->c_periods_sent = 0;
	spin_unlock_irqrestore(&chip->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम snd_cs4231_overrange(काष्ठा snd_cs4231 *chip)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर res;

	spin_lock_irqsave(&chip->lock, flags);
	res = snd_cs4231_in(chip, CS4231_TEST_INIT);
	spin_unlock_irqrestore(&chip->lock, flags);

	/* detect overrange only above 0dB; may be user selectable? */
	अगर (res & (0x08 | 0x02))
		chip->capture_substream->runसमय->overrange++;
पूर्ण

अटल व्योम snd_cs4231_play_callback(काष्ठा snd_cs4231 *chip)
अणु
	अगर (chip->image[CS4231_IFACE_CTRL] & CS4231_PLAYBACK_ENABLE) अणु
		snd_pcm_period_elapsed(chip->playback_substream);
		snd_cs4231_advance_dma(&chip->p_dma, chip->playback_substream,
					    &chip->p_periods_sent);
	पूर्ण
पूर्ण

अटल व्योम snd_cs4231_capture_callback(काष्ठा snd_cs4231 *chip)
अणु
	अगर (chip->image[CS4231_IFACE_CTRL] & CS4231_RECORD_ENABLE) अणु
		snd_pcm_period_elapsed(chip->capture_substream);
		snd_cs4231_advance_dma(&chip->c_dma, chip->capture_substream,
					    &chip->c_periods_sent);
	पूर्ण
पूर्ण

अटल snd_pcm_uframes_t snd_cs4231_playback_poपूर्णांकer(
					काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_cs4231 *chip = snd_pcm_substream_chip(substream);
	काष्ठा cs4231_dma_control *dma_cont = &chip->p_dma;
	माप_प्रकार ptr;

	अगर (!(chip->image[CS4231_IFACE_CTRL] & CS4231_PLAYBACK_ENABLE))
		वापस 0;
	ptr = dma_cont->address(dma_cont);
	अगर (ptr != 0)
		ptr -= substream->runसमय->dma_addr;

	वापस bytes_to_frames(substream->runसमय, ptr);
पूर्ण

अटल snd_pcm_uframes_t snd_cs4231_capture_poपूर्णांकer(
					काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_cs4231 *chip = snd_pcm_substream_chip(substream);
	काष्ठा cs4231_dma_control *dma_cont = &chip->c_dma;
	माप_प्रकार ptr;

	अगर (!(chip->image[CS4231_IFACE_CTRL] & CS4231_RECORD_ENABLE))
		वापस 0;
	ptr = dma_cont->address(dma_cont);
	अगर (ptr != 0)
		ptr -= substream->runसमय->dma_addr;

	वापस bytes_to_frames(substream->runसमय, ptr);
पूर्ण

अटल पूर्णांक snd_cs4231_probe(काष्ठा snd_cs4231 *chip)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	पूर्णांक id = 0;
	पूर्णांक vers = 0;
	अचिन्हित अक्षर *ptr;

	क्रम (i = 0; i < 50; i++) अणु
		mb();
		अगर (__cs4231_पढ़ोb(chip, CS4231U(chip, REGSEL)) & CS4231_INIT)
			msleep(2);
		अन्यथा अणु
			spin_lock_irqsave(&chip->lock, flags);
			snd_cs4231_out(chip, CS4231_MISC_INFO, CS4231_MODE2);
			id = snd_cs4231_in(chip, CS4231_MISC_INFO) & 0x0f;
			vers = snd_cs4231_in(chip, CS4231_VERSION);
			spin_unlock_irqrestore(&chip->lock, flags);
			अगर (id == 0x0a)
				अवरोध;	/* this is valid value */
		पूर्ण
	पूर्ण
	snd_prपूर्णांकdd("cs4231: port = %p, id = 0x%x\n", chip->port, id);
	अगर (id != 0x0a)
		वापस -ENODEV;	/* no valid device found */

	spin_lock_irqsave(&chip->lock, flags);

	/* clear any pendings IRQ */
	__cs4231_पढ़ोb(chip, CS4231U(chip, STATUS));
	__cs4231_ग_लिखोb(chip, 0, CS4231U(chip, STATUS));
	mb();

	spin_unlock_irqrestore(&chip->lock, flags);

	chip->image[CS4231_MISC_INFO] = CS4231_MODE2;
	chip->image[CS4231_IFACE_CTRL] =
		chip->image[CS4231_IFACE_CTRL] & ~CS4231_SINGLE_DMA;
	chip->image[CS4231_ALT_FEATURE_1] = 0x80;
	chip->image[CS4231_ALT_FEATURE_2] = 0x01;
	अगर (vers & 0x20)
		chip->image[CS4231_ALT_FEATURE_2] |= 0x02;

	ptr = (अचिन्हित अक्षर *) &chip->image;

	snd_cs4231_mce_करोwn(chip);

	spin_lock_irqsave(&chip->lock, flags);

	क्रम (i = 0; i < 32; i++)	/* ok.. fill all CS4231 रेजिस्टरs */
		snd_cs4231_out(chip, i, *ptr++);

	spin_unlock_irqrestore(&chip->lock, flags);

	snd_cs4231_mce_up(chip);

	snd_cs4231_mce_करोwn(chip);

	mdelay(2);

	वापस 0;		/* all things are ok.. */
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware snd_cs4231_playback = अणु
	.info			= SNDRV_PCM_INFO_MMAP |
				  SNDRV_PCM_INFO_INTERLEAVED |
				  SNDRV_PCM_INFO_MMAP_VALID |
				  SNDRV_PCM_INFO_SYNC_START,
	.क्रमmats		= SNDRV_PCM_FMTBIT_MU_LAW |
				  SNDRV_PCM_FMTBIT_A_LAW |
				  SNDRV_PCM_FMTBIT_IMA_ADPCM |
				  SNDRV_PCM_FMTBIT_U8 |
				  SNDRV_PCM_FMTBIT_S16_LE |
				  SNDRV_PCM_FMTBIT_S16_BE,
	.rates			= SNDRV_PCM_RATE_KNOT |
				  SNDRV_PCM_RATE_8000_48000,
	.rate_min		= 5510,
	.rate_max		= 48000,
	.channels_min		= 1,
	.channels_max		= 2,
	.buffer_bytes_max	= 32 * 1024,
	.period_bytes_min	= 64,
	.period_bytes_max	= 32 * 1024,
	.periods_min		= 1,
	.periods_max		= 1024,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_cs4231_capture = अणु
	.info			= SNDRV_PCM_INFO_MMAP |
				  SNDRV_PCM_INFO_INTERLEAVED |
				  SNDRV_PCM_INFO_MMAP_VALID |
				  SNDRV_PCM_INFO_SYNC_START,
	.क्रमmats		= SNDRV_PCM_FMTBIT_MU_LAW |
				  SNDRV_PCM_FMTBIT_A_LAW |
				  SNDRV_PCM_FMTBIT_IMA_ADPCM |
				  SNDRV_PCM_FMTBIT_U8 |
				  SNDRV_PCM_FMTBIT_S16_LE |
				  SNDRV_PCM_FMTBIT_S16_BE,
	.rates			= SNDRV_PCM_RATE_KNOT |
				  SNDRV_PCM_RATE_8000_48000,
	.rate_min		= 5510,
	.rate_max		= 48000,
	.channels_min		= 1,
	.channels_max		= 2,
	.buffer_bytes_max	= 32 * 1024,
	.period_bytes_min	= 64,
	.period_bytes_max	= 32 * 1024,
	.periods_min		= 1,
	.periods_max		= 1024,
पूर्ण;

अटल पूर्णांक snd_cs4231_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_cs4231 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;

	runसमय->hw = snd_cs4231_playback;

	err = snd_cs4231_खोलो(chip, CS4231_MODE_PLAY);
	अगर (err < 0)
		वापस err;
	chip->playback_substream = substream;
	chip->p_periods_sent = 0;
	snd_pcm_set_sync(substream);
	snd_cs4231_xrate(runसमय);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4231_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_cs4231 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;

	runसमय->hw = snd_cs4231_capture;

	err = snd_cs4231_खोलो(chip, CS4231_MODE_RECORD);
	अगर (err < 0)
		वापस err;
	chip->capture_substream = substream;
	chip->c_periods_sent = 0;
	snd_pcm_set_sync(substream);
	snd_cs4231_xrate(runसमय);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4231_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_cs4231 *chip = snd_pcm_substream_chip(substream);

	snd_cs4231_बंद(chip, CS4231_MODE_PLAY);
	chip->playback_substream = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4231_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_cs4231 *chip = snd_pcm_substream_chip(substream);

	snd_cs4231_बंद(chip, CS4231_MODE_RECORD);
	chip->capture_substream = शून्य;

	वापस 0;
पूर्ण

/* XXX We can करो some घातer-management, in particular on EBUS using
 * XXX the audio AUXIO रेजिस्टर...
 */

अटल स्थिर काष्ठा snd_pcm_ops snd_cs4231_playback_ops = अणु
	.खोलो		=	snd_cs4231_playback_खोलो,
	.बंद		=	snd_cs4231_playback_बंद,
	.hw_params	=	snd_cs4231_playback_hw_params,
	.prepare	=	snd_cs4231_playback_prepare,
	.trigger	=	snd_cs4231_trigger,
	.poपूर्णांकer	=	snd_cs4231_playback_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_cs4231_capture_ops = अणु
	.खोलो		=	snd_cs4231_capture_खोलो,
	.बंद		=	snd_cs4231_capture_बंद,
	.hw_params	=	snd_cs4231_capture_hw_params,
	.prepare	=	snd_cs4231_capture_prepare,
	.trigger	=	snd_cs4231_trigger,
	.poपूर्णांकer	=	snd_cs4231_capture_poपूर्णांकer,
पूर्ण;

अटल पूर्णांक snd_cs4231_pcm(काष्ठा snd_card *card)
अणु
	काष्ठा snd_cs4231 *chip = card->निजी_data;
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	err = snd_pcm_new(card, "CS4231", 0, 1, 1, &pcm);
	अगर (err < 0)
		वापस err;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK,
			&snd_cs4231_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE,
			&snd_cs4231_capture_ops);

	/* global setup */
	pcm->निजी_data = chip;
	pcm->info_flags = SNDRV_PCM_INFO_JOINT_DUPLEX;
	म_नकल(pcm->name, "CS4231");

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
				       &chip->op->dev, 64 * 1024, 128 * 1024);

	chip->pcm = pcm;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4231_समयr(काष्ठा snd_card *card)
अणु
	काष्ठा snd_cs4231 *chip = card->निजी_data;
	काष्ठा snd_समयr *समयr;
	काष्ठा snd_समयr_id tid;
	पूर्णांक err;

	/* Timer initialization */
	tid.dev_class = SNDRV_TIMER_CLASS_CARD;
	tid.dev_sclass = SNDRV_TIMER_SCLASS_NONE;
	tid.card = card->number;
	tid.device = 0;
	tid.subdevice = 0;
	err = snd_समयr_new(card, "CS4231", &tid, &समयr);
	अगर (err < 0)
		वापस err;
	म_नकल(समयr->name, "CS4231");
	समयr->निजी_data = chip;
	समयr->hw = snd_cs4231_समयr_table;
	chip->समयr = समयr;

	वापस 0;
पूर्ण

/*
 *  MIXER part
 */

अटल पूर्णांक snd_cs4231_info_mux(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[4] = अणु
		"Line", "CD", "Mic", "Mix"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 2, 4, texts);
पूर्ण

अटल पूर्णांक snd_cs4231_get_mux(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_cs4231 *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->lock, flags);
	ucontrol->value.क्रमागतerated.item[0] =
		(chip->image[CS4231_LEFT_INPUT] & CS4231_MIXS_ALL) >> 6;
	ucontrol->value.क्रमागतerated.item[1] =
		(chip->image[CS4231_RIGHT_INPUT] & CS4231_MIXS_ALL) >> 6;
	spin_unlock_irqrestore(&chip->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4231_put_mux(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_cs4231 *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	अचिन्हित लघु left, right;
	पूर्णांक change;

	अगर (ucontrol->value.क्रमागतerated.item[0] > 3 ||
	    ucontrol->value.क्रमागतerated.item[1] > 3)
		वापस -EINVAL;
	left = ucontrol->value.क्रमागतerated.item[0] << 6;
	right = ucontrol->value.क्रमागतerated.item[1] << 6;

	spin_lock_irqsave(&chip->lock, flags);

	left = (chip->image[CS4231_LEFT_INPUT] & ~CS4231_MIXS_ALL) | left;
	right = (chip->image[CS4231_RIGHT_INPUT] & ~CS4231_MIXS_ALL) | right;
	change = left != chip->image[CS4231_LEFT_INPUT] ||
		 right != chip->image[CS4231_RIGHT_INPUT];
	snd_cs4231_out(chip, CS4231_LEFT_INPUT, left);
	snd_cs4231_out(chip, CS4231_RIGHT_INPUT, right);

	spin_unlock_irqrestore(&chip->lock, flags);

	वापस change;
पूर्ण

अटल पूर्णांक snd_cs4231_info_single(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;

	uinfo->type = (mask == 1) ?
		SNDRV_CTL_ELEM_TYPE_BOOLEAN : SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = mask;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4231_get_single(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_cs4231 *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 24) & 0xff;

	spin_lock_irqsave(&chip->lock, flags);

	ucontrol->value.पूर्णांकeger.value[0] = (chip->image[reg] >> shअगरt) & mask;

	spin_unlock_irqrestore(&chip->lock, flags);

	अगर (invert)
		ucontrol->value.पूर्णांकeger.value[0] =
			(mask - ucontrol->value.पूर्णांकeger.value[0]);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4231_put_single(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_cs4231 *chip = snd_kcontrol_chip(kcontrol);
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

	spin_lock_irqsave(&chip->lock, flags);

	val = (chip->image[reg] & ~(mask << shअगरt)) | val;
	change = val != chip->image[reg];
	snd_cs4231_out(chip, reg, val);

	spin_unlock_irqrestore(&chip->lock, flags);

	वापस change;
पूर्ण

अटल पूर्णांक snd_cs4231_info_द्विगुन(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक mask = (kcontrol->निजी_value >> 24) & 0xff;

	uinfo->type = mask == 1 ?
		SNDRV_CTL_ELEM_TYPE_BOOLEAN : SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = mask;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4231_get_द्विगुन(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_cs4231 *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक left_reg = kcontrol->निजी_value & 0xff;
	पूर्णांक right_reg = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक shअगरt_left = (kcontrol->निजी_value >> 16) & 0x07;
	पूर्णांक shअगरt_right = (kcontrol->निजी_value >> 19) & 0x07;
	पूर्णांक mask = (kcontrol->निजी_value >> 24) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 22) & 1;

	spin_lock_irqsave(&chip->lock, flags);

	ucontrol->value.पूर्णांकeger.value[0] =
		(chip->image[left_reg] >> shअगरt_left) & mask;
	ucontrol->value.पूर्णांकeger.value[1] =
		(chip->image[right_reg] >> shअगरt_right) & mask;

	spin_unlock_irqrestore(&chip->lock, flags);

	अगर (invert) अणु
		ucontrol->value.पूर्णांकeger.value[0] =
			(mask - ucontrol->value.पूर्णांकeger.value[0]);
		ucontrol->value.पूर्णांकeger.value[1] =
			(mask - ucontrol->value.पूर्णांकeger.value[1]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4231_put_द्विगुन(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_cs4231 *chip = snd_kcontrol_chip(kcontrol);
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

	spin_lock_irqsave(&chip->lock, flags);

	val1 = (chip->image[left_reg] & ~(mask << shअगरt_left)) | val1;
	val2 = (chip->image[right_reg] & ~(mask << shअगरt_right)) | val2;
	change = val1 != chip->image[left_reg];
	change |= val2 != chip->image[right_reg];
	snd_cs4231_out(chip, left_reg, val1);
	snd_cs4231_out(chip, right_reg, val2);

	spin_unlock_irqrestore(&chip->lock, flags);

	वापस change;
पूर्ण

#घोषणा CS4231_SINGLE(xname, xindex, reg, shअगरt, mask, invert) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = (xname), .index = (xindex), \
  .info = snd_cs4231_info_single,	\
  .get = snd_cs4231_get_single, .put = snd_cs4231_put_single,	\
  .निजी_value = (reg) | ((shअगरt) << 8) | ((mask) << 16) | ((invert) << 24) पूर्ण

#घोषणा CS4231_DOUBLE(xname, xindex, left_reg, right_reg, shअगरt_left, \
			shअगरt_right, mask, invert) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = (xname), .index = (xindex), \
  .info = snd_cs4231_info_द्विगुन,	\
  .get = snd_cs4231_get_द्विगुन, .put = snd_cs4231_put_द्विगुन,	\
  .निजी_value = (left_reg) | ((right_reg) << 8) | ((shअगरt_left) << 16) | \
		   ((shअगरt_right) << 19) | ((mask) << 24) | ((invert) << 22) पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_cs4231_controls[] = अणु
CS4231_DOUBLE("PCM Playback Switch", 0, CS4231_LEFT_OUTPUT,
		CS4231_RIGHT_OUTPUT, 7, 7, 1, 1),
CS4231_DOUBLE("PCM Playback Volume", 0, CS4231_LEFT_OUTPUT,
		CS4231_RIGHT_OUTPUT, 0, 0, 63, 1),
CS4231_DOUBLE("Line Playback Switch", 0, CS4231_LEFT_LINE_IN,
		CS4231_RIGHT_LINE_IN, 7, 7, 1, 1),
CS4231_DOUBLE("Line Playback Volume", 0, CS4231_LEFT_LINE_IN,
		CS4231_RIGHT_LINE_IN, 0, 0, 31, 1),
CS4231_DOUBLE("Aux Playback Switch", 0, CS4231_AUX1_LEFT_INPUT,
		CS4231_AUX1_RIGHT_INPUT, 7, 7, 1, 1),
CS4231_DOUBLE("Aux Playback Volume", 0, CS4231_AUX1_LEFT_INPUT,
		CS4231_AUX1_RIGHT_INPUT, 0, 0, 31, 1),
CS4231_DOUBLE("Aux Playback Switch", 1, CS4231_AUX2_LEFT_INPUT,
		CS4231_AUX2_RIGHT_INPUT, 7, 7, 1, 1),
CS4231_DOUBLE("Aux Playback Volume", 1, CS4231_AUX2_LEFT_INPUT,
		CS4231_AUX2_RIGHT_INPUT, 0, 0, 31, 1),
CS4231_SINGLE("Mono Playback Switch", 0, CS4231_MONO_CTRL, 7, 1, 1),
CS4231_SINGLE("Mono Playback Volume", 0, CS4231_MONO_CTRL, 0, 15, 1),
CS4231_SINGLE("Mono Output Playback Switch", 0, CS4231_MONO_CTRL, 6, 1, 1),
CS4231_SINGLE("Mono Output Playback Bypass", 0, CS4231_MONO_CTRL, 5, 1, 0),
CS4231_DOUBLE("Capture Volume", 0, CS4231_LEFT_INPUT, CS4231_RIGHT_INPUT, 0, 0,
		15, 0),
अणु
	.अगरace	= SNDRV_CTL_ELEM_IFACE_MIXER,
	.name	= "Capture Source",
	.info	= snd_cs4231_info_mux,
	.get	= snd_cs4231_get_mux,
	.put	= snd_cs4231_put_mux,
पूर्ण,
CS4231_DOUBLE("Mic Boost", 0, CS4231_LEFT_INPUT, CS4231_RIGHT_INPUT, 5, 5,
		1, 0),
CS4231_SINGLE("Loopback Capture Switch", 0, CS4231_LOOPBACK, 0, 1, 0),
CS4231_SINGLE("Loopback Capture Volume", 0, CS4231_LOOPBACK, 2, 63, 1),
/* SPARC specअगरic uses of XCTLअणु0,1पूर्ण general purpose outमाला_दो.  */
CS4231_SINGLE("Line Out Switch", 0, CS4231_PIN_CTRL, 6, 1, 1),
CS4231_SINGLE("Headphone Out Switch", 0, CS4231_PIN_CTRL, 7, 1, 1)
पूर्ण;

अटल पूर्णांक snd_cs4231_mixer(काष्ठा snd_card *card)
अणु
	काष्ठा snd_cs4231 *chip = card->निजी_data;
	पूर्णांक err, idx;

	अगर (snd_BUG_ON(!chip || !chip->pcm))
		वापस -EINVAL;

	म_नकल(card->mixername, chip->pcm->name);

	क्रम (idx = 0; idx < ARRAY_SIZE(snd_cs4231_controls); idx++) अणु
		err = snd_ctl_add(card,
				 snd_ctl_new1(&snd_cs4231_controls[idx], chip));
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dev;

अटल पूर्णांक cs4231_attach_begin(काष्ठा platक्रमm_device *op,
			       काष्ठा snd_card **rcard)
अणु
	काष्ठा snd_card *card;
	काष्ठा snd_cs4231 *chip;
	पूर्णांक err;

	*rcard = शून्य;

	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;

	अगर (!enable[dev]) अणु
		dev++;
		वापस -ENOENT;
	पूर्ण

	err = snd_card_new(&op->dev, index[dev], id[dev], THIS_MODULE,
			   माप(काष्ठा snd_cs4231), &card);
	अगर (err < 0)
		वापस err;

	म_नकल(card->driver, "CS4231");
	म_नकल(card->लघुname, "Sun CS4231");

	chip = card->निजी_data;
	chip->card = card;

	*rcard = card;
	वापस 0;
पूर्ण

अटल पूर्णांक cs4231_attach_finish(काष्ठा snd_card *card)
अणु
	काष्ठा snd_cs4231 *chip = card->निजी_data;
	पूर्णांक err;

	err = snd_cs4231_pcm(card);
	अगर (err < 0)
		जाओ out_err;

	err = snd_cs4231_mixer(card);
	अगर (err < 0)
		जाओ out_err;

	err = snd_cs4231_समयr(card);
	अगर (err < 0)
		जाओ out_err;

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0)
		जाओ out_err;

	dev_set_drvdata(&chip->op->dev, chip);

	dev++;
	वापस 0;

out_err:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

#अगर_घोषित SBUS_SUPPORT

अटल irqवापस_t snd_cs4231_sbus_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर status;
	u32 csr;
	काष्ठा snd_cs4231 *chip = dev_id;

	/*This is IRQ is not उठाओd by the cs4231*/
	अगर (!(__cs4231_पढ़ोb(chip, CS4231U(chip, STATUS)) & CS4231_GLOBALIRQ))
		वापस IRQ_NONE;

	/* ACK the APC पूर्णांकerrupt. */
	csr = sbus_पढ़ोl(chip->port + APCCSR);

	sbus_ग_लिखोl(csr, chip->port + APCCSR);

	अगर ((csr & APC_PDMA_READY) &&
	    (csr & APC_PLAY_INT) &&
	    (csr & APC_XINT_PNVA) &&
	    !(csr & APC_XINT_EMPT))
			snd_cs4231_play_callback(chip);

	अगर ((csr & APC_CDMA_READY) &&
	    (csr & APC_CAPT_INT) &&
	    (csr & APC_XINT_CNVA) &&
	    !(csr & APC_XINT_EMPT))
			snd_cs4231_capture_callback(chip);

	status = snd_cs4231_in(chip, CS4231_IRQ_STATUS);

	अगर (status & CS4231_TIMER_IRQ) अणु
		अगर (chip->समयr)
			snd_समयr_पूर्णांकerrupt(chip->समयr, chip->समयr->sticks);
	पूर्ण

	अगर ((status & CS4231_RECORD_IRQ) && (csr & APC_CDMA_READY))
		snd_cs4231_overrange(chip);

	/* ACK the CS4231 पूर्णांकerrupt. */
	spin_lock_irqsave(&chip->lock, flags);
	snd_cs4231_ouपंचांग(chip, CS4231_IRQ_STATUS, ~CS4231_ALL_IRQS | ~status, 0);
	spin_unlock_irqrestore(&chip->lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * SBUS DMA routines
 */

अटल पूर्णांक sbus_dma_request(काष्ठा cs4231_dma_control *dma_cont,
			    dma_addr_t bus_addr, माप_प्रकार len)
अणु
	अचिन्हित दीर्घ flags;
	u32 test, csr;
	पूर्णांक err;
	काष्ठा sbus_dma_info *base = &dma_cont->sbus_info;

	अगर (len >= (1 << 24))
		वापस -EINVAL;
	spin_lock_irqsave(&base->lock, flags);
	csr = sbus_पढ़ोl(base->regs + APCCSR);
	err = -EINVAL;
	test = APC_CDMA_READY;
	अगर (base->dir == APC_PLAY)
		test = APC_PDMA_READY;
	अगर (!(csr & test))
		जाओ out;
	err = -EBUSY;
	test = APC_XINT_CNVA;
	अगर (base->dir == APC_PLAY)
		test = APC_XINT_PNVA;
	अगर (!(csr & test))
		जाओ out;
	err = 0;
	sbus_ग_लिखोl(bus_addr, base->regs + base->dir + APCNVA);
	sbus_ग_लिखोl(len, base->regs + base->dir + APCNC);
out:
	spin_unlock_irqrestore(&base->lock, flags);
	वापस err;
पूर्ण

अटल व्योम sbus_dma_prepare(काष्ठा cs4231_dma_control *dma_cont, पूर्णांक d)
अणु
	अचिन्हित दीर्घ flags;
	u32 csr, test;
	काष्ठा sbus_dma_info *base = &dma_cont->sbus_info;

	spin_lock_irqsave(&base->lock, flags);
	csr = sbus_पढ़ोl(base->regs + APCCSR);
	test =  APC_GENL_INT | APC_PLAY_INT | APC_XINT_ENA |
		APC_XINT_PLAY | APC_XINT_PEMP | APC_XINT_GENL |
		 APC_XINT_PENA;
	अगर (base->dir == APC_RECORD)
		test = APC_GENL_INT | APC_CAPT_INT | APC_XINT_ENA |
			APC_XINT_CAPT | APC_XINT_CEMP | APC_XINT_GENL;
	csr |= test;
	sbus_ग_लिखोl(csr, base->regs + APCCSR);
	spin_unlock_irqrestore(&base->lock, flags);
पूर्ण

अटल व्योम sbus_dma_enable(काष्ठा cs4231_dma_control *dma_cont, पूर्णांक on)
अणु
	अचिन्हित दीर्घ flags;
	u32 csr, shअगरt;
	काष्ठा sbus_dma_info *base = &dma_cont->sbus_info;

	spin_lock_irqsave(&base->lock, flags);
	अगर (!on) अणु
		sbus_ग_लिखोl(0, base->regs + base->dir + APCNC);
		sbus_ग_लिखोl(0, base->regs + base->dir + APCNVA);
		अगर (base->dir == APC_PLAY) अणु
			sbus_ग_लिखोl(0, base->regs + base->dir + APCC);
			sbus_ग_लिखोl(0, base->regs + base->dir + APCVA);
		पूर्ण

		udelay(1200);
	पूर्ण
	csr = sbus_पढ़ोl(base->regs + APCCSR);
	shअगरt = 0;
	अगर (base->dir == APC_PLAY)
		shअगरt = 1;
	अगर (on)
		csr &= ~(APC_CPAUSE << shअगरt);
	अन्यथा
		csr |= (APC_CPAUSE << shअगरt);
	sbus_ग_लिखोl(csr, base->regs + APCCSR);
	अगर (on)
		csr |= (APC_CDMA_READY << shअगरt);
	अन्यथा
		csr &= ~(APC_CDMA_READY << shअगरt);
	sbus_ग_लिखोl(csr, base->regs + APCCSR);

	spin_unlock_irqrestore(&base->lock, flags);
पूर्ण

अटल अचिन्हित पूर्णांक sbus_dma_addr(काष्ठा cs4231_dma_control *dma_cont)
अणु
	काष्ठा sbus_dma_info *base = &dma_cont->sbus_info;

	वापस sbus_पढ़ोl(base->regs + base->dir + APCVA);
पूर्ण

/*
 * Init and निकास routines
 */

अटल पूर्णांक snd_cs4231_sbus_मुक्त(काष्ठा snd_cs4231 *chip)
अणु
	काष्ठा platक्रमm_device *op = chip->op;

	अगर (chip->irq[0])
		मुक्त_irq(chip->irq[0], chip);

	अगर (chip->port)
		of_iounmap(&op->resource[0], chip->port, chip->regs_size);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4231_sbus_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_cs4231 *cp = device->device_data;

	वापस snd_cs4231_sbus_मुक्त(cp);
पूर्ण

अटल स्थिर काष्ठा snd_device_ops snd_cs4231_sbus_dev_ops = अणु
	.dev_मुक्त	=	snd_cs4231_sbus_dev_मुक्त,
पूर्ण;

अटल पूर्णांक snd_cs4231_sbus_create(काष्ठा snd_card *card,
				  काष्ठा platक्रमm_device *op,
				  पूर्णांक dev)
अणु
	काष्ठा snd_cs4231 *chip = card->निजी_data;
	पूर्णांक err;

	spin_lock_init(&chip->lock);
	spin_lock_init(&chip->c_dma.sbus_info.lock);
	spin_lock_init(&chip->p_dma.sbus_info.lock);
	mutex_init(&chip->mce_mutex);
	mutex_init(&chip->खोलो_mutex);
	chip->op = op;
	chip->regs_size = resource_size(&op->resource[0]);
	स_नकल(&chip->image, &snd_cs4231_original_image,
	       माप(snd_cs4231_original_image));

	chip->port = of_ioremap(&op->resource[0], 0,
				chip->regs_size, "cs4231");
	अगर (!chip->port) अणु
		snd_prपूर्णांकdd("cs4231-%d: Unable to map chip registers.\n", dev);
		वापस -EIO;
	पूर्ण

	chip->c_dma.sbus_info.regs = chip->port;
	chip->p_dma.sbus_info.regs = chip->port;
	chip->c_dma.sbus_info.dir = APC_RECORD;
	chip->p_dma.sbus_info.dir = APC_PLAY;

	chip->p_dma.prepare = sbus_dma_prepare;
	chip->p_dma.enable = sbus_dma_enable;
	chip->p_dma.request = sbus_dma_request;
	chip->p_dma.address = sbus_dma_addr;

	chip->c_dma.prepare = sbus_dma_prepare;
	chip->c_dma.enable = sbus_dma_enable;
	chip->c_dma.request = sbus_dma_request;
	chip->c_dma.address = sbus_dma_addr;

	अगर (request_irq(op->archdata.irqs[0], snd_cs4231_sbus_पूर्णांकerrupt,
			IRQF_SHARED, "cs4231", chip)) अणु
		snd_prपूर्णांकdd("cs4231-%d: Unable to grab SBUS IRQ %d\n",
			    dev, op->archdata.irqs[0]);
		snd_cs4231_sbus_मुक्त(chip);
		वापस -EBUSY;
	पूर्ण
	chip->irq[0] = op->archdata.irqs[0];

	अगर (snd_cs4231_probe(chip) < 0) अणु
		snd_cs4231_sbus_मुक्त(chip);
		वापस -ENODEV;
	पूर्ण
	snd_cs4231_init(chip);

	अगर ((err = snd_device_new(card, SNDRV_DEV_LOWLEVEL,
				  chip, &snd_cs4231_sbus_dev_ops)) < 0) अणु
		snd_cs4231_sbus_मुक्त(chip);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cs4231_sbus_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा resource *rp = &op->resource[0];
	काष्ठा snd_card *card;
	पूर्णांक err;

	err = cs4231_attach_begin(op, &card);
	अगर (err)
		वापस err;

	प्र_लिखो(card->दीर्घname, "%s at 0x%02lx:0x%016Lx, irq %d",
		card->लघुname,
		rp->flags & 0xffL,
		(अचिन्हित दीर्घ दीर्घ)rp->start,
		op->archdata.irqs[0]);

	err = snd_cs4231_sbus_create(card, op, dev);
	अगर (err < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	वापस cs4231_attach_finish(card);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित EBUS_SUPPORT

अटल व्योम snd_cs4231_ebus_play_callback(काष्ठा ebus_dma_info *p, पूर्णांक event,
					  व्योम *cookie)
अणु
	काष्ठा snd_cs4231 *chip = cookie;

	snd_cs4231_play_callback(chip);
पूर्ण

अटल व्योम snd_cs4231_ebus_capture_callback(काष्ठा ebus_dma_info *p,
					     पूर्णांक event, व्योम *cookie)
अणु
	काष्ठा snd_cs4231 *chip = cookie;

	snd_cs4231_capture_callback(chip);
पूर्ण

/*
 * EBUS DMA wrappers
 */

अटल पूर्णांक _ebus_dma_request(काष्ठा cs4231_dma_control *dma_cont,
			     dma_addr_t bus_addr, माप_प्रकार len)
अणु
	वापस ebus_dma_request(&dma_cont->ebus_info, bus_addr, len);
पूर्ण

अटल व्योम _ebus_dma_enable(काष्ठा cs4231_dma_control *dma_cont, पूर्णांक on)
अणु
	ebus_dma_enable(&dma_cont->ebus_info, on);
पूर्ण

अटल व्योम _ebus_dma_prepare(काष्ठा cs4231_dma_control *dma_cont, पूर्णांक dir)
अणु
	ebus_dma_prepare(&dma_cont->ebus_info, dir);
पूर्ण

अटल अचिन्हित पूर्णांक _ebus_dma_addr(काष्ठा cs4231_dma_control *dma_cont)
अणु
	वापस ebus_dma_addr(&dma_cont->ebus_info);
पूर्ण

/*
 * Init and निकास routines
 */

अटल पूर्णांक snd_cs4231_ebus_मुक्त(काष्ठा snd_cs4231 *chip)
अणु
	काष्ठा platक्रमm_device *op = chip->op;

	अगर (chip->c_dma.ebus_info.regs) अणु
		ebus_dma_unरेजिस्टर(&chip->c_dma.ebus_info);
		of_iounmap(&op->resource[2], chip->c_dma.ebus_info.regs, 0x10);
	पूर्ण
	अगर (chip->p_dma.ebus_info.regs) अणु
		ebus_dma_unरेजिस्टर(&chip->p_dma.ebus_info);
		of_iounmap(&op->resource[1], chip->p_dma.ebus_info.regs, 0x10);
	पूर्ण

	अगर (chip->port)
		of_iounmap(&op->resource[0], chip->port, 0x10);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4231_ebus_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_cs4231 *cp = device->device_data;

	वापस snd_cs4231_ebus_मुक्त(cp);
पूर्ण

अटल स्थिर काष्ठा snd_device_ops snd_cs4231_ebus_dev_ops = अणु
	.dev_मुक्त	=	snd_cs4231_ebus_dev_मुक्त,
पूर्ण;

अटल पूर्णांक snd_cs4231_ebus_create(काष्ठा snd_card *card,
				  काष्ठा platक्रमm_device *op,
				  पूर्णांक dev)
अणु
	काष्ठा snd_cs4231 *chip = card->निजी_data;
	पूर्णांक err;

	spin_lock_init(&chip->lock);
	spin_lock_init(&chip->c_dma.ebus_info.lock);
	spin_lock_init(&chip->p_dma.ebus_info.lock);
	mutex_init(&chip->mce_mutex);
	mutex_init(&chip->खोलो_mutex);
	chip->flags |= CS4231_FLAG_EBUS;
	chip->op = op;
	स_नकल(&chip->image, &snd_cs4231_original_image,
	       माप(snd_cs4231_original_image));
	म_नकल(chip->c_dma.ebus_info.name, "cs4231(capture)");
	chip->c_dma.ebus_info.flags = EBUS_DMA_FLAG_USE_EBDMA_HANDLER;
	chip->c_dma.ebus_info.callback = snd_cs4231_ebus_capture_callback;
	chip->c_dma.ebus_info.client_cookie = chip;
	chip->c_dma.ebus_info.irq = op->archdata.irqs[0];
	म_नकल(chip->p_dma.ebus_info.name, "cs4231(play)");
	chip->p_dma.ebus_info.flags = EBUS_DMA_FLAG_USE_EBDMA_HANDLER;
	chip->p_dma.ebus_info.callback = snd_cs4231_ebus_play_callback;
	chip->p_dma.ebus_info.client_cookie = chip;
	chip->p_dma.ebus_info.irq = op->archdata.irqs[1];

	chip->p_dma.prepare = _ebus_dma_prepare;
	chip->p_dma.enable = _ebus_dma_enable;
	chip->p_dma.request = _ebus_dma_request;
	chip->p_dma.address = _ebus_dma_addr;

	chip->c_dma.prepare = _ebus_dma_prepare;
	chip->c_dma.enable = _ebus_dma_enable;
	chip->c_dma.request = _ebus_dma_request;
	chip->c_dma.address = _ebus_dma_addr;

	chip->port = of_ioremap(&op->resource[0], 0, 0x10, "cs4231");
	chip->p_dma.ebus_info.regs =
		of_ioremap(&op->resource[1], 0, 0x10, "cs4231_pdma");
	chip->c_dma.ebus_info.regs =
		of_ioremap(&op->resource[2], 0, 0x10, "cs4231_cdma");
	अगर (!chip->port || !chip->p_dma.ebus_info.regs ||
	    !chip->c_dma.ebus_info.regs) अणु
		snd_cs4231_ebus_मुक्त(chip);
		snd_prपूर्णांकdd("cs4231-%d: Unable to map chip registers.\n", dev);
		वापस -EIO;
	पूर्ण

	अगर (ebus_dma_रेजिस्टर(&chip->c_dma.ebus_info)) अणु
		snd_cs4231_ebus_मुक्त(chip);
		snd_prपूर्णांकdd("cs4231-%d: Unable to register EBUS capture DMA\n",
			    dev);
		वापस -EBUSY;
	पूर्ण
	अगर (ebus_dma_irq_enable(&chip->c_dma.ebus_info, 1)) अणु
		snd_cs4231_ebus_मुक्त(chip);
		snd_prपूर्णांकdd("cs4231-%d: Unable to enable EBUS capture IRQ\n",
			    dev);
		वापस -EBUSY;
	पूर्ण

	अगर (ebus_dma_रेजिस्टर(&chip->p_dma.ebus_info)) अणु
		snd_cs4231_ebus_मुक्त(chip);
		snd_prपूर्णांकdd("cs4231-%d: Unable to register EBUS play DMA\n",
			    dev);
		वापस -EBUSY;
	पूर्ण
	अगर (ebus_dma_irq_enable(&chip->p_dma.ebus_info, 1)) अणु
		snd_cs4231_ebus_मुक्त(chip);
		snd_prपूर्णांकdd("cs4231-%d: Unable to enable EBUS play IRQ\n", dev);
		वापस -EBUSY;
	पूर्ण

	अगर (snd_cs4231_probe(chip) < 0) अणु
		snd_cs4231_ebus_मुक्त(chip);
		वापस -ENODEV;
	पूर्ण
	snd_cs4231_init(chip);

	अगर ((err = snd_device_new(card, SNDRV_DEV_LOWLEVEL,
				  chip, &snd_cs4231_ebus_dev_ops)) < 0) अणु
		snd_cs4231_ebus_मुक्त(chip);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cs4231_ebus_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा snd_card *card;
	पूर्णांक err;

	err = cs4231_attach_begin(op, &card);
	अगर (err)
		वापस err;

	प्र_लिखो(card->दीर्घname, "%s at 0x%llx, irq %d",
		card->लघुname,
		op->resource[0].start,
		op->archdata.irqs[0]);

	err = snd_cs4231_ebus_create(card, op, dev);
	अगर (err < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	वापस cs4231_attach_finish(card);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक cs4231_probe(काष्ठा platक्रमm_device *op)
अणु
#अगर_घोषित EBUS_SUPPORT
	अगर (of_node_name_eq(op->dev.of_node->parent, "ebus"))
		वापस cs4231_ebus_probe(op);
#पूर्ण_अगर
#अगर_घोषित SBUS_SUPPORT
	अगर (of_node_name_eq(op->dev.of_node->parent, "sbus") ||
	    of_node_name_eq(op->dev.of_node->parent, "sbi"))
		वापस cs4231_sbus_probe(op);
#पूर्ण_अगर
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक cs4231_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा snd_cs4231 *chip = dev_get_drvdata(&op->dev);

	snd_card_मुक्त(chip->card);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id cs4231_match[] = अणु
	अणु
		.name = "SUNW,CS4231",
	पूर्ण,
	अणु
		.name = "audio",
		.compatible = "SUNW,CS4231",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, cs4231_match);

अटल काष्ठा platक्रमm_driver cs4231_driver = अणु
	.driver = अणु
		.name = "audio",
		.of_match_table = cs4231_match,
	पूर्ण,
	.probe		= cs4231_probe,
	.हटाओ		= cs4231_हटाओ,
पूर्ण;

module_platक्रमm_driver(cs4231_driver);
