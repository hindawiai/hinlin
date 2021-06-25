<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * see notice in hfc_multi.c
 */

#घोषणा DEBUG_HFCMULTI_FIFO	0x00010000
#घोषणा	DEBUG_HFCMULTI_CRC	0x00020000
#घोषणा	DEBUG_HFCMULTI_INIT	0x00040000
#घोषणा	DEBUG_HFCMULTI_PLXSD	0x00080000
#घोषणा	DEBUG_HFCMULTI_MODE	0x00100000
#घोषणा	DEBUG_HFCMULTI_MSG	0x00200000
#घोषणा	DEBUG_HFCMULTI_STATE	0x00400000
#घोषणा	DEBUG_HFCMULTI_FILL	0x00800000
#घोषणा	DEBUG_HFCMULTI_SYNC	0x01000000
#घोषणा	DEBUG_HFCMULTI_DTMF	0x02000000
#घोषणा	DEBUG_HFCMULTI_LOCK	0x80000000

#घोषणा	PCI_ENA_REGIO	0x01
#घोषणा	PCI_ENA_MEMIO	0x02

#घोषणा XHFC_IRQ	4		/* SIU_IRQ2 */
#घोषणा XHFC_MEMBASE	0xFE000000
#घोषणा XHFC_MEMSIZE    0x00001000
#घोषणा XHFC_OFFSET	0x00001000
#घोषणा PA_XHFC_A0	0x0020		/* PA10 */
#घोषणा PB_XHFC_IRQ1	0x00000100	/* PB23 */
#घोषणा PB_XHFC_IRQ2	0x00000200	/* PB22 */
#घोषणा PB_XHFC_IRQ3	0x00000400	/* PB21 */
#घोषणा PB_XHFC_IRQ4	0x00000800	/* PB20 */

/*
 * NOTE: some रेजिस्टरs are asचिन्हित multiple बार due to dअगरferent modes
 *       also रेजिस्टरs are asचिन्हित dअगरferen क्रम HFC-4s/8s and HFC-E1
 */

/*
  #घोषणा MAX_FRAME_SIZE	2048
*/

काष्ठा hfc_chan अणु
	काष्ठा dchannel	*dch;	/* link अगर channel is a D-channel */
	काष्ठा bchannel	*bch;	/* link अगर channel is a B-channel */
	पूर्णांक		port;	/* the पूर्णांकerface port this */
				/* channel is associated with */
	पूर्णांक		nt_समयr; /* -1 अगर off, 0 अगर elapsed, >0 अगर running */
	पूर्णांक		los, ais, slip_tx, slip_rx, rdi; /* current alarms */
	पूर्णांक		jitter;
	u_दीर्घ		cfg;	/* port configuration */
	पूर्णांक		sync;	/* sync state (used by E1) */
	u_पूर्णांक		protocol; /* current protocol */
	पूर्णांक		slot_tx; /* current pcm slot */
	पूर्णांक		bank_tx; /* current pcm bank */
	पूर्णांक		slot_rx;
	पूर्णांक		bank_rx;
	पूर्णांक		conf;	/* conference setting of TX slot */
	पूर्णांक		txpending;	/* अगर there is currently data in */
					/* the FIFO 0=no, 1=yes, 2=splloop */
	पूर्णांक		Zfill;	/* rx-fअगरo level on last hfcmulti_tx */
	पूर्णांक		rx_off; /* set to turn fअगरo receive off */
	पूर्णांक		coeff_count; /* curren coeff block */
	s32		*coeff; /* memory poपूर्णांकer to 8 coeff blocks */
पूर्ण;


काष्ठा hfcm_hw अणु
	u_अक्षर	r_ctrl;
	u_अक्षर	r_irq_ctrl;
	u_अक्षर	r_cirm;
	u_अक्षर	r_ram_sz;
	u_अक्षर	r_pcm_md0;
	u_अक्षर	r_irqmsk_misc;
	u_अक्षर	r_dपंचांगf;
	u_अक्षर	r_st_sync;
	u_अक्षर	r_sci_msk;
	u_अक्षर	r_tx0, r_tx1;
	u_अक्षर	a_st_ctrl0[8];
	u_अक्षर	r_bert_wd_md;
	समयr_t	समयr;
पूर्ण;


/* क्रम each stack these flags are used (cfg) */
#घोषणा	HFC_CFG_NONCAP_TX	1 /* S/T TX पूर्णांकerface has less capacity */
#घोषणा	HFC_CFG_DIS_ECHANNEL	2 /* disable E-channel processing */
#घोषणा	HFC_CFG_REG_ECHANNEL	3 /* रेजिस्टर E-channel */
#घोषणा	HFC_CFG_OPTICAL		4 /* the E1 पूर्णांकerface is optical */
#घोषणा	HFC_CFG_REPORT_LOS	5 /* the card should report loss of संकेत */
#घोषणा	HFC_CFG_REPORT_AIS	6 /* the card should report alarm ind. sign. */
#घोषणा	HFC_CFG_REPORT_SLIP	7 /* the card should report bit slips */
#घोषणा	HFC_CFG_REPORT_RDI	8 /* the card should report remote alarm */
#घोषणा	HFC_CFG_DTMF		9 /* enable DTMF-detection */
#घोषणा	HFC_CFG_CRC4		10 /* disable CRC-4 Multअगरrame mode, */
/* use द्विगुन frame instead. */

#घोषणा HFC_TYPE_E1		1 /* controller is HFC-E1 */
#घोषणा HFC_TYPE_4S		4 /* controller is HFC-4S */
#घोषणा HFC_TYPE_8S		8 /* controller is HFC-8S */
#घोषणा HFC_TYPE_XHFC		5 /* controller is XHFC */

#घोषणा	HFC_CHIP_EXRAM_128	0 /* बाह्यal ram 128k */
#घोषणा	HFC_CHIP_EXRAM_512	1 /* बाह्यal ram 256k */
#घोषणा	HFC_CHIP_REVISION0	2 /* old fअगरo handling */
#घोषणा	HFC_CHIP_PCM_SLAVE	3 /* PCM is slave */
#घोषणा	HFC_CHIP_PCM_MASTER	4 /* PCM is master */
#घोषणा	HFC_CHIP_RX_SYNC	5 /* disable pll sync क्रम pcm */
#घोषणा	HFC_CHIP_DTMF		6 /* DTMF decoding is enabled */
#घोषणा	HFC_CHIP_CONF		7 /* conference handling is enabled */
#घोषणा	HFC_CHIP_ULAW		8 /* ULAW mode */
#घोषणा	HFC_CHIP_CLOCK2		9 /* द्विगुन घड़ी mode */
#घोषणा	HFC_CHIP_E1CLOCK_GET	10 /* always get घड़ी from E1 पूर्णांकerface */
#घोषणा	HFC_CHIP_E1CLOCK_PUT	11 /* always put घड़ी from E1 पूर्णांकerface */
#घोषणा	HFC_CHIP_WATCHDOG	12 /* whether we should send संकेतs */
/* to the watchकरोg */
#घोषणा	HFC_CHIP_B410P		13 /* whether we have a b410p with echocan in */
/* hw */
#घोषणा	HFC_CHIP_PLXSD		14 /* whether we have a Speech-Design PLX */
#घोषणा	HFC_CHIP_EMBSD          15 /* whether we have a SD Embedded board */

#घोषणा HFC_IO_MODE_PCIMEM	0x00 /* normal memory mapped IO */
#घोषणा HFC_IO_MODE_REGIO	0x01 /* PCI io access */
#घोषणा HFC_IO_MODE_PLXSD	0x02 /* access HFC via PLX9030 */
#घोषणा HFC_IO_MODE_EMBSD	0x03 /* direct access */

/* table entry in the PCI devices list */
काष्ठा hm_map अणु
	अक्षर *venकरोr_name;
	अक्षर *card_name;
	पूर्णांक type;
	पूर्णांक ports;
	पूर्णांक घड़ी2;
	पूर्णांक leds;
	पूर्णांक opticalsupport;
	पूर्णांक dip_type;
	पूर्णांक io_mode;
	पूर्णांक irq;
पूर्ण;

काष्ठा hfc_multi अणु
	काष्ठा list_head	list;
	काष्ठा hm_map	*mtyp;
	पूर्णांक		id;
	पूर्णांक		pcm;	/* id of pcm bus */
	पूर्णांक		ctype;	/* controller type */
	पूर्णांक		ports;

	u_पूर्णांक		irq;	/* irq used by card */
	u_पूर्णांक		irqcnt;
	काष्ठा pci_dev	*pci_dev;
	पूर्णांक		io_mode; /* selects mode */
#अगर_घोषित HFC_REGISTER_DEBUG
	व्योम		(*HFC_outb)(काष्ठा hfc_multi *hc, u_अक्षर reg,
				    u_अक्षर val, स्थिर अक्षर *function, पूर्णांक line);
	व्योम		(*HFC_outb_nodebug)(काष्ठा hfc_multi *hc, u_अक्षर reg,
					    u_अक्षर val, स्थिर अक्षर *function, पूर्णांक line);
	u_अक्षर		(*HFC_inb)(काष्ठा hfc_multi *hc, u_अक्षर reg,
				   स्थिर अक्षर *function, पूर्णांक line);
	u_अक्षर		(*HFC_inb_nodebug)(काष्ठा hfc_multi *hc, u_अक्षर reg,
					   स्थिर अक्षर *function, पूर्णांक line);
	u_लघु		(*HFC_inw)(काष्ठा hfc_multi *hc, u_अक्षर reg,
				   स्थिर अक्षर *function, पूर्णांक line);
	u_लघु		(*HFC_inw_nodebug)(काष्ठा hfc_multi *hc, u_अक्षर reg,
					   स्थिर अक्षर *function, पूर्णांक line);
	व्योम		(*HFC_रुको)(काष्ठा hfc_multi *hc,
				    स्थिर अक्षर *function, पूर्णांक line);
	व्योम		(*HFC_रुको_nodebug)(काष्ठा hfc_multi *hc,
					    स्थिर अक्षर *function, पूर्णांक line);
#अन्यथा
	व्योम		(*HFC_outb)(काष्ठा hfc_multi *hc, u_अक्षर reg,
				    u_अक्षर val);
	व्योम		(*HFC_outb_nodebug)(काष्ठा hfc_multi *hc, u_अक्षर reg,
					    u_अक्षर val);
	u_अक्षर		(*HFC_inb)(काष्ठा hfc_multi *hc, u_अक्षर reg);
	u_अक्षर		(*HFC_inb_nodebug)(काष्ठा hfc_multi *hc, u_अक्षर reg);
	u_लघु		(*HFC_inw)(काष्ठा hfc_multi *hc, u_अक्षर reg);
	u_लघु		(*HFC_inw_nodebug)(काष्ठा hfc_multi *hc, u_अक्षर reg);
	व्योम		(*HFC_रुको)(काष्ठा hfc_multi *hc);
	व्योम		(*HFC_रुको_nodebug)(काष्ठा hfc_multi *hc);
#पूर्ण_अगर
	व्योम		(*पढ़ो_fअगरo)(काष्ठा hfc_multi *hc, u_अक्षर *data,
				     पूर्णांक len);
	व्योम		(*ग_लिखो_fअगरo)(काष्ठा hfc_multi *hc, u_अक्षर *data,
				      पूर्णांक len);
	u_दीर्घ		pci_origmembase, plx_origmembase;
	व्योम __iomem	*pci_membase; /* PCI memory */
	व्योम __iomem	*plx_membase; /* PLX memory */
	u_दीर्घ		xhfc_origmembase;
	u_अक्षर		*xhfc_membase;
	u_दीर्घ		*xhfc_memaddr, *xhfc_memdata;
#अगर_घोषित CONFIG_MISDN_HFCMULTI_8xx
	काष्ठा immap	*immap;
#पूर्ण_अगर
	u_दीर्घ		pb_irqmsk;	/* Portbit mask to check the IRQ line */
	u_दीर्घ		pci_iobase; /* PCI IO */
	काष्ठा hfcm_hw	hw;	/* remember data of ग_लिखो-only-रेजिस्टरs */

	u_दीर्घ		chip;	/* chip configuration */
	पूर्णांक		masterclk; /* port that provides master घड़ी -1=off */
	अचिन्हित अक्षर	silence;/* silence byte */
	अचिन्हित अक्षर	silence_data[128];/* silence block */
	पूर्णांक		dपंचांगf;	/* flag that dपंचांगf is currently in process */
	पूर्णांक		Flen;	/* F-buffer size */
	पूर्णांक		Zlen;	/* Z-buffer size (must be पूर्णांक क्रम calculation)*/
	पूर्णांक		max_trans; /* maximum transparent fअगरo fill */
	पूर्णांक		Zmin;	/* Z-buffer offset */
	पूर्णांक		DTMFbase; /* base address of DTMF coefficients */

	u_पूर्णांक		slots;	/* number of PCM slots */
	u_पूर्णांक		leds;	/* type of leds */
	u_दीर्घ		ledstate; /* save last state of leds */
	पूर्णांक		opticalsupport; /* has the e1 board */
					/* an optical Interface */

	u_पूर्णांक		bmask[32]; /* biपंचांगask of bchannels क्रम port */
	u_अक्षर		dnum[32]; /* array of used dchannel numbers क्रम port */
	u_अक्षर		created[32]; /* what port is created */
	u_पूर्णांक		activity_tx; /* अगर there is data TX / RX */
	u_पूर्णांक		activity_rx; /* biपंचांगask according to port number */
				     /* (will be cleared after */
				     /* showing led-states) */
	u_पूर्णांक		flash[8]; /* counter क्रम flashing 8 leds on activity */

	u_दीर्घ		wdcount;	/* every 500 ms we need to */
					/* send the watchकरोg a संकेत */
	u_अक्षर		wdbyte; /* watchकरोg toggle byte */
	पूर्णांक		e1_state; /* keep track of last state */
	पूर्णांक		e1_अ_लोlock; /* अगर sync is retrieved from पूर्णांकerface */
	पूर्णांक		syncronized; /* keep track of existing sync पूर्णांकerface */
	पूर्णांक		e1_resync; /* resync jobs */

	spinlock_t	lock;	/* the lock */

	काष्ठा mISDNघड़ी *iघड़ी; /* isdn घड़ी support */
	पूर्णांक		iघड़ी_on;

	/*
	 * the channel index is counted from 0, regardless where the channel
	 * is located on the hfc-channel.
	 * the bch->channel is equvalent to the hfc-channel
	 */
	काष्ठा hfc_chan	chan[32];
	चिन्हित अक्षर	slot_owner[256]; /* owner channel of slot */
पूर्ण;

/* PLX GPIOs */
#घोषणा	PLX_GPIO4_सूची_BIT	13
#घोषणा	PLX_GPIO4_BIT		14
#घोषणा	PLX_GPIO5_सूची_BIT	16
#घोषणा	PLX_GPIO5_BIT		17
#घोषणा	PLX_GPIO6_सूची_BIT	19
#घोषणा	PLX_GPIO6_BIT		20
#घोषणा	PLX_GPIO7_सूची_BIT	22
#घोषणा	PLX_GPIO7_BIT		23
#घोषणा PLX_GPIO8_सूची_BIT	25
#घोषणा PLX_GPIO8_BIT		26

#घोषणा	PLX_GPIO4		(1 << PLX_GPIO4_BIT)
#घोषणा	PLX_GPIO5		(1 << PLX_GPIO5_BIT)
#घोषणा	PLX_GPIO6		(1 << PLX_GPIO6_BIT)
#घोषणा	PLX_GPIO7		(1 << PLX_GPIO7_BIT)
#घोषणा PLX_GPIO8		(1 << PLX_GPIO8_BIT)

#घोषणा	PLX_GPIO4_सूची		(1 << PLX_GPIO4_सूची_BIT)
#घोषणा	PLX_GPIO5_सूची		(1 << PLX_GPIO5_सूची_BIT)
#घोषणा	PLX_GPIO6_सूची		(1 << PLX_GPIO6_सूची_BIT)
#घोषणा	PLX_GPIO7_सूची		(1 << PLX_GPIO7_सूची_BIT)
#घोषणा PLX_GPIO8_सूची		(1 << PLX_GPIO8_सूची_BIT)

#घोषणा	PLX_TERM_ON			PLX_GPIO7
#घोषणा	PLX_SLAVE_EN_N		PLX_GPIO5
#घोषणा	PLX_MASTER_EN		PLX_GPIO6
#घोषणा	PLX_SYNC_O_EN		PLX_GPIO4
#घोषणा PLX_DSP_RES_N		PLX_GPIO8
/* GPIO4..8 Enable & Set to OUT, SLAVE_EN_N = 1 */
#घोषणा PLX_GPIOC_INIT		(PLX_GPIO4_सूची | PLX_GPIO5_सूची | PLX_GPIO6_सूची \
				 | PLX_GPIO7_सूची | PLX_GPIO8_सूची | PLX_SLAVE_EN_N)

/* PLX Interrupt Control/STATUS */
#घोषणा PLX_INTCSR_LINTI1_ENABLE 0x01
#घोषणा PLX_INTCSR_LINTI1_STATUS 0x04
#घोषणा PLX_INTCSR_LINTI2_ENABLE 0x08
#घोषणा PLX_INTCSR_LINTI2_STATUS 0x20
#घोषणा PLX_INTCSR_PCIINT_ENABLE 0x40

/* PLX Registers */
#घोषणा PLX_INTCSR 0x4c
#घोषणा PLX_CNTRL  0x50
#घोषणा PLX_GPIOC  0x54


/*
 * REGISTER SETTING FOR HFC-4S/8S AND HFC-E1
 */

/* ग_लिखो only रेजिस्टरs */
#घोषणा R_CIRM			0x00
#घोषणा R_CTRL			0x01
#घोषणा R_BRG_PCM_CFG		0x02
#घोषणा R_RAM_ADDR0		0x08
#घोषणा R_RAM_ADDR1		0x09
#घोषणा R_RAM_ADDR2		0x0A
#घोषणा R_FIRST_FIFO		0x0B
#घोषणा R_RAM_SZ		0x0C
#घोषणा R_FIFO_MD		0x0D
#घोषणा R_INC_RES_FIFO		0x0E
#घोषणा R_FSM_IDX		0x0F
#घोषणा R_FIFO			0x0F
#घोषणा R_SLOT			0x10
#घोषणा R_IRQMSK_MISC		0x11
#घोषणा R_SCI_MSK		0x12
#घोषणा R_IRQ_CTRL		0x13
#घोषणा R_PCM_MD0		0x14
#घोषणा R_PCM_MD1		0x15
#घोषणा R_PCM_MD2		0x15
#घोषणा R_SH0H			0x15
#घोषणा R_SH1H			0x15
#घोषणा R_SH0L			0x15
#घोषणा R_SH1L			0x15
#घोषणा R_SL_SEL0		0x15
#घोषणा R_SL_SEL1		0x15
#घोषणा R_SL_SEL2		0x15
#घोषणा R_SL_SEL3		0x15
#घोषणा R_SL_SEL4		0x15
#घोषणा R_SL_SEL5		0x15
#घोषणा R_SL_SEL6		0x15
#घोषणा R_SL_SEL7		0x15
#घोषणा R_ST_SEL		0x16
#घोषणा R_ST_SYNC		0x17
#घोषणा R_CONF_EN		0x18
#घोषणा R_TI_WD			0x1A
#घोषणा R_BERT_WD_MD		0x1B
#घोषणा R_DTMF			0x1C
#घोषणा R_DTMF_N		0x1D
#घोषणा R_E1_WR_STA		0x20
#घोषणा R_E1_RD_STA		0x20
#घोषणा R_LOS0			0x22
#घोषणा R_LOS1			0x23
#घोषणा R_RX0			0x24
#घोषणा R_RX_FR0		0x25
#घोषणा R_RX_FR1		0x26
#घोषणा R_TX0			0x28
#घोषणा R_TX1			0x29
#घोषणा R_TX_FR0		0x2C

#घोषणा R_TX_FR1		0x2D
#घोषणा R_TX_FR2		0x2E
#घोषणा R_JATT_ATT		0x2F /* unकरोcumented */
#घोषणा A_ST_RD_STATE		0x30
#घोषणा A_ST_WR_STATE		0x30
#घोषणा R_RX_OFF		0x30
#घोषणा A_ST_CTRL0		0x31
#घोषणा R_SYNC_OUT		0x31
#घोषणा A_ST_CTRL1		0x32
#घोषणा A_ST_CTRL2		0x33
#घोषणा A_ST_SQ_WR		0x34
#घोषणा R_TX_OFF		0x34
#घोषणा R_SYNC_CTRL		0x35
#घोषणा A_ST_CLK_DLY		0x37
#घोषणा R_PWM0			0x38
#घोषणा R_PWM1			0x39
#घोषणा A_ST_B1_TX		0x3C
#घोषणा A_ST_B2_TX		0x3D
#घोषणा A_ST_D_TX		0x3E
#घोषणा R_GPIO_OUT0		0x40
#घोषणा R_GPIO_OUT1		0x41
#घोषणा R_GPIO_EN0		0x42
#घोषणा R_GPIO_EN1		0x43
#घोषणा R_GPIO_SEL		0x44
#घोषणा R_BRG_CTRL		0x45
#घोषणा R_PWM_MD		0x46
#घोषणा R_BRG_MD		0x47
#घोषणा R_BRG_TIM0		0x48
#घोषणा R_BRG_TIM1		0x49
#घोषणा R_BRG_TIM2		0x4A
#घोषणा R_BRG_TIM3		0x4B
#घोषणा R_BRG_TIM_SEL01		0x4C
#घोषणा R_BRG_TIM_SEL23		0x4D
#घोषणा R_BRG_TIM_SEL45		0x4E
#घोषणा R_BRG_TIM_SEL67		0x4F
#घोषणा A_SL_CFG		0xD0
#घोषणा A_CONF			0xD1
#घोषणा A_CH_MSK		0xF4
#घोषणा A_CON_HDLC		0xFA
#घोषणा A_SUBCH_CFG		0xFB
#घोषणा A_CHANNEL		0xFC
#घोषणा A_FIFO_SEQ		0xFD
#घोषणा A_IRQ_MSK		0xFF

/* पढ़ो only रेजिस्टरs */
#घोषणा A_Z12			0x04
#घोषणा A_Z1L			0x04
#घोषणा A_Z1			0x04
#घोषणा A_Z1H			0x05
#घोषणा A_Z2L			0x06
#घोषणा A_Z2			0x06
#घोषणा A_Z2H			0x07
#घोषणा A_F1			0x0C
#घोषणा A_F12			0x0C
#घोषणा A_F2			0x0D
#घोषणा R_IRQ_OVIEW		0x10
#घोषणा R_IRQ_MISC		0x11
#घोषणा R_IRQ_STATECH		0x12
#घोषणा R_CONF_OFLOW		0x14
#घोषणा R_RAM_USE		0x15
#घोषणा R_CHIP_ID		0x16
#घोषणा R_BERT_STA		0x17
#घोषणा R_F0_CNTL		0x18
#घोषणा R_F0_CNTH		0x19
#घोषणा R_BERT_EC		0x1A
#घोषणा R_BERT_ECL		0x1A
#घोषणा R_BERT_ECH		0x1B
#घोषणा R_STATUS		0x1C
#घोषणा R_CHIP_RV		0x1F
#घोषणा R_STATE			0x20
#घोषणा R_SYNC_STA		0x24
#घोषणा R_RX_SL0_0		0x25
#घोषणा R_RX_SL0_1		0x26
#घोषणा R_RX_SL0_2		0x27
#घोषणा R_JATT_सूची		0x2b /* unकरोcumented */
#घोषणा R_SLIP			0x2c
#घोषणा A_ST_RD_STA		0x30
#घोषणा R_FAS_EC		0x30
#घोषणा R_FAS_ECL		0x30
#घोषणा R_FAS_ECH		0x31
#घोषणा R_VIO_EC		0x32
#घोषणा R_VIO_ECL		0x32
#घोषणा R_VIO_ECH		0x33
#घोषणा A_ST_SQ_RD		0x34
#घोषणा R_CRC_EC		0x34
#घोषणा R_CRC_ECL		0x34
#घोषणा R_CRC_ECH		0x35
#घोषणा R_E_EC			0x36
#घोषणा R_E_ECL			0x36
#घोषणा R_E_ECH			0x37
#घोषणा R_SA6_SA13_EC		0x38
#घोषणा R_SA6_SA13_ECL		0x38
#घोषणा R_SA6_SA13_ECH		0x39
#घोषणा R_SA6_SA23_EC		0x3A
#घोषणा R_SA6_SA23_ECL		0x3A
#घोषणा R_SA6_SA23_ECH		0x3B
#घोषणा A_ST_B1_RX		0x3C
#घोषणा A_ST_B2_RX		0x3D
#घोषणा A_ST_D_RX		0x3E
#घोषणा A_ST_E_RX		0x3F
#घोषणा R_GPIO_IN0		0x40
#घोषणा R_GPIO_IN1		0x41
#घोषणा R_GPI_IN0		0x44
#घोषणा R_GPI_IN1		0x45
#घोषणा R_GPI_IN2		0x46
#घोषणा R_GPI_IN3		0x47
#घोषणा R_INT_DATA		0x88
#घोषणा R_IRQ_FIFO_BL0		0xC8
#घोषणा R_IRQ_FIFO_BL1		0xC9
#घोषणा R_IRQ_FIFO_BL2		0xCA
#घोषणा R_IRQ_FIFO_BL3		0xCB
#घोषणा R_IRQ_FIFO_BL4		0xCC
#घोषणा R_IRQ_FIFO_BL5		0xCD
#घोषणा R_IRQ_FIFO_BL6		0xCE
#घोषणा R_IRQ_FIFO_BL7		0xCF

/* पढ़ो and ग_लिखो रेजिस्टरs */
#घोषणा A_FIFO_DATA0		0x80
#घोषणा A_FIFO_DATA1		0x80
#घोषणा A_FIFO_DATA2		0x80
#घोषणा A_FIFO_DATA0_NOINC	0x84
#घोषणा A_FIFO_DATA1_NOINC	0x84
#घोषणा A_FIFO_DATA2_NOINC	0x84
#घोषणा R_RAM_DATA		0xC0


/*
 * BIT SETTING FOR HFC-4S/8S AND HFC-E1
 */

/* chapter 2: universal bus पूर्णांकerface */
/* R_CIRM */
#घोषणा V_IRQ_SEL		0x01
#घोषणा V_SRES			0x08
#घोषणा V_HFCRES		0x10
#घोषणा V_PCMRES		0x20
#घोषणा V_STRES			0x40
#घोषणा V_ETRES			0x40
#घोषणा V_RLD_EPR		0x80
/* R_CTRL */
#घोषणा V_FIFO_LPRIO		0x02
#घोषणा V_SLOW_RD		0x04
#घोषणा V_EXT_RAM		0x08
#घोषणा V_CLK_OFF		0x20
#घोषणा V_ST_CLK		0x40
/* R_RAM_ADDR0 */
#घोषणा V_RAM_ADDR2		0x01
#घोषणा V_ADDR_RES		0x40
#घोषणा V_ADDR_INC		0x80
/* R_RAM_SZ */
#घोषणा V_RAM_SZ		0x01
#घोषणा V_PWM0_16KHZ		0x10
#घोषणा V_PWM1_16KHZ		0x20
#घोषणा V_FZ_MD			0x80
/* R_CHIP_ID */
#घोषणा V_PNP_IRQ		0x01
#घोषणा V_CHIP_ID		0x10

/* chapter 3: data flow */
/* R_FIRST_FIFO */
#घोषणा V_FIRST_FIRO_सूची	0x01
#घोषणा V_FIRST_FIFO_NUM	0x02
/* R_FIFO_MD */
#घोषणा V_FIFO_MD		0x01
#घोषणा V_CSM_MD		0x04
#घोषणा V_FSM_MD		0x08
#घोषणा V_FIFO_SZ		0x10
/* R_FIFO */
#घोषणा V_FIFO_सूची		0x01
#घोषणा V_FIFO_NUM		0x02
#घोषणा V_REV			0x80
/* R_SLOT */
#घोषणा V_SL_सूची		0x01
#घोषणा V_SL_NUM		0x02
/* A_SL_CFG */
#घोषणा V_CH_सूची		0x01
#घोषणा V_CH_SEL		0x02
#घोषणा V_ROUTING		0x40
/* A_CON_HDLC */
#घोषणा V_IFF			0x01
#घोषणा V_HDLC_TRP		0x02
#घोषणा V_TRP_IRQ		0x04
#घोषणा V_DATA_FLOW		0x20
/* A_SUBCH_CFG */
#घोषणा V_BIT_CNT		0x01
#घोषणा V_START_BIT		0x08
#घोषणा V_LOOP_FIFO		0x40
#घोषणा V_INV_DATA		0x80
/* A_CHANNEL */
#घोषणा V_CH_सूची0		0x01
#घोषणा V_CH_NUM0		0x02
/* A_FIFO_SEQ */
#घोषणा V_NEXT_FIFO_सूची		0x01
#घोषणा V_NEXT_FIFO_NUM		0x02
#घोषणा V_SEQ_END		0x40

/* chapter 4: FIFO handling and HDLC controller */
/* R_INC_RES_FIFO */
#घोषणा V_INC_F			0x01
#घोषणा V_RES_F			0x02
#घोषणा V_RES_LOST		0x04

/* chapter 5: S/T पूर्णांकerface */
/* R_SCI_MSK */
#घोषणा V_SCI_MSK_ST0		0x01
#घोषणा V_SCI_MSK_ST1		0x02
#घोषणा V_SCI_MSK_ST2		0x04
#घोषणा V_SCI_MSK_ST3		0x08
#घोषणा V_SCI_MSK_ST4		0x10
#घोषणा V_SCI_MSK_ST5		0x20
#घोषणा V_SCI_MSK_ST6		0x40
#घोषणा V_SCI_MSK_ST7		0x80
/* R_ST_SEL */
#घोषणा V_ST_SEL		0x01
#घोषणा V_MULT_ST		0x08
/* R_ST_SYNC */
#घोषणा V_SYNC_SEL		0x01
#घोषणा V_AUTO_SYNC		0x08
/* A_ST_WR_STA */
#घोषणा V_ST_SET_STA		0x01
#घोषणा V_ST_LD_STA		0x10
#घोषणा V_ST_ACT		0x20
#घोषणा V_SET_G2_G3		0x80
/* A_ST_CTRL0 */
#घोषणा V_B1_EN			0x01
#घोषणा V_B2_EN			0x02
#घोषणा V_ST_MD			0x04
#घोषणा V_D_PRIO		0x08
#घोषणा V_SQ_EN			0x10
#घोषणा V_96KHZ			0x20
#घोषणा V_TX_LI			0x40
#घोषणा V_ST_STOP		0x80
/* A_ST_CTRL1 */
#घोषणा V_G2_G3_EN		0x01
#घोषणा V_D_HI			0x04
#घोषणा V_E_IGNO		0x08
#घोषणा V_E_LO			0x10
#घोषणा V_B12_SWAP		0x80
/* A_ST_CTRL2 */
#घोषणा V_B1_RX_EN		0x01
#घोषणा V_B2_RX_EN		0x02
#घोषणा V_ST_TRIS		0x40
/* A_ST_CLK_DLY */
#घोषणा V_ST_CK_DLY		0x01
#घोषणा V_ST_SMPL		0x10
/* A_ST_D_TX */
#घोषणा V_ST_D_TX		0x40
/* R_IRQ_STATECH */
#घोषणा V_SCI_ST0		0x01
#घोषणा V_SCI_ST1		0x02
#घोषणा V_SCI_ST2		0x04
#घोषणा V_SCI_ST3		0x08
#घोषणा V_SCI_ST4		0x10
#घोषणा V_SCI_ST5		0x20
#घोषणा V_SCI_ST6		0x40
#घोषणा V_SCI_ST7		0x80
/* A_ST_RD_STA */
#घोषणा V_ST_STA		0x01
#घोषणा V_FR_SYNC_ST		0x10
#घोषणा V_TI2_EXP		0x20
#घोषणा V_INFO0			0x40
#घोषणा V_G2_G3			0x80
/* A_ST_SQ_RD */
#घोषणा V_ST_SQ			0x01
#घोषणा V_MF_RX_RDY		0x10
#घोषणा V_MF_TX_RDY		0x80
/* A_ST_D_RX */
#घोषणा V_ST_D_RX		0x40
/* A_ST_E_RX */
#घोषणा V_ST_E_RX		0x40

/* chapter 5: E1 पूर्णांकerface */
/* R_E1_WR_STA */
/* R_E1_RD_STA */
#घोषणा V_E1_SET_STA		0x01
#घोषणा V_E1_LD_STA		0x10
/* R_RX0 */
#घोषणा V_RX_CODE		0x01
#घोषणा V_RX_FBAUD		0x04
#घोषणा V_RX_CMI		0x08
#घोषणा V_RX_INV_CMI		0x10
#घोषणा V_RX_INV_CLK		0x20
#घोषणा V_RX_INV_DATA		0x40
#घोषणा V_AIS_ITU		0x80
/* R_RX_FR0 */
#घोषणा V_NO_INSYNC		0x01
#घोषणा V_AUTO_RESYNC		0x02
#घोषणा V_AUTO_RECO		0x04
#घोषणा V_SWORD_COND		0x08
#घोषणा V_SYNC_LOSS		0x10
#घोषणा V_XCRC_SYNC		0x20
#घोषणा V_MF_RESYNC		0x40
#घोषणा V_RESYNC		0x80
/* R_RX_FR1 */
#घोषणा V_RX_MF			0x01
#घोषणा V_RX_MF_SYNC		0x02
#घोषणा V_RX_SL0_RAM		0x04
#घोषणा V_ERR_SIM		0x20
#घोषणा V_RES_NMF		0x40
/* R_TX0 */
#घोषणा V_TX_CODE		0x01
#घोषणा V_TX_FBAUD		0x04
#घोषणा V_TX_CMI_CODE		0x08
#घोषणा V_TX_INV_CMI_CODE	0x10
#घोषणा V_TX_INV_CLK		0x20
#घोषणा V_TX_INV_DATA		0x40
#घोषणा V_OUT_EN		0x80
/* R_TX1 */
#घोषणा V_INV_CLK		0x01
#घोषणा V_EXCHG_DATA_LI		0x02
#घोषणा V_AIS_OUT		0x04
#घोषणा V_ATX			0x20
#घोषणा V_NTRI			0x40
#घोषणा V_AUTO_ERR_RES		0x80
/* R_TX_FR0 */
#घोषणा V_TRP_FAS		0x01
#घोषणा V_TRP_NFAS		0x02
#घोषणा V_TRP_RAL		0x04
#घोषणा V_TRP_SA		0x08
/* R_TX_FR1 */
#घोषणा V_TX_FAS		0x01
#घोषणा V_TX_NFAS		0x02
#घोषणा V_TX_RAL		0x04
#घोषणा V_TX_SA			0x08
/* R_TX_FR2 */
#घोषणा V_TX_MF			0x01
#घोषणा V_TRP_SL0		0x02
#घोषणा V_TX_SL0_RAM		0x04
#घोषणा V_TX_E			0x10
#घोषणा V_NEG_E			0x20
#घोषणा V_XS12_ON		0x40
#घोषणा V_XS15_ON		0x80
/* R_RX_OFF */
#घोषणा V_RX_SZ			0x01
#घोषणा V_RX_INIT		0x04
/* R_SYNC_OUT */
#घोषणा V_SYNC_E1_RX		0x01
#घोषणा V_IPATS0		0x20
#घोषणा V_IPATS1		0x40
#घोषणा V_IPATS2		0x80
/* R_TX_OFF */
#घोषणा V_TX_SZ			0x01
#घोषणा V_TX_INIT		0x04
/* R_SYNC_CTRL */
#घोषणा V_EXT_CLK_SYNC		0x01
#घोषणा V_SYNC_OFFS		0x02
#घोषणा V_PCM_SYNC		0x04
#घोषणा V_NEG_CLK		0x08
#घोषणा V_HCLK			0x10
/*
  #घोषणा V_JATT_AUTO_DEL		0x20
  #घोषणा V_JATT_AUTO		0x40
*/
#घोषणा V_JATT_OFF		0x80
/* R_STATE */
#घोषणा V_E1_STA		0x01
#घोषणा V_ALT_FR_RX		0x40
#घोषणा V_ALT_FR_TX		0x80
/* R_SYNC_STA */
#घोषणा V_RX_STA		0x01
#घोषणा V_FR_SYNC_E1		0x04
#घोषणा V_SIG_LOS		0x08
#घोषणा V_MFA_STA		0x10
#घोषणा V_AIS			0x40
#घोषणा V_NO_MF_SYNC		0x80
/* R_RX_SL0_0 */
#घोषणा V_SI_FAS		0x01
#घोषणा V_SI_NFAS		0x02
#घोषणा V_A			0x04
#घोषणा V_CRC_OK		0x08
#घोषणा V_TX_E1			0x10
#घोषणा V_TX_E2			0x20
#घोषणा V_RX_E1			0x40
#घोषणा V_RX_E2			0x80
/* R_SLIP */
#घोषणा V_SLIP_RX		0x01
#घोषणा V_FOSLIP_RX		0x08
#घोषणा V_SLIP_TX		0x10
#घोषणा V_FOSLIP_TX		0x80

/* chapter 6: PCM पूर्णांकerface */
/* R_PCM_MD0 */
#घोषणा V_PCM_MD		0x01
#घोषणा V_C4_POL		0x02
#घोषणा V_F0_NEG		0x04
#घोषणा V_F0_LEN		0x08
#घोषणा V_PCM_ADDR		0x10
/* R_SL_SEL0 */
#घोषणा V_SL_SEL0		0x01
#घोषणा V_SH_SEL0		0x80
/* R_SL_SEL1 */
#घोषणा V_SL_SEL1		0x01
#घोषणा V_SH_SEL1		0x80
/* R_SL_SEL2 */
#घोषणा V_SL_SEL2		0x01
#घोषणा V_SH_SEL2		0x80
/* R_SL_SEL3 */
#घोषणा V_SL_SEL3		0x01
#घोषणा V_SH_SEL3		0x80
/* R_SL_SEL4 */
#घोषणा V_SL_SEL4		0x01
#घोषणा V_SH_SEL4		0x80
/* R_SL_SEL5 */
#घोषणा V_SL_SEL5		0x01
#घोषणा V_SH_SEL5		0x80
/* R_SL_SEL6 */
#घोषणा V_SL_SEL6		0x01
#घोषणा V_SH_SEL6		0x80
/* R_SL_SEL7 */
#घोषणा V_SL_SEL7		0x01
#घोषणा V_SH_SEL7		0x80
/* R_PCM_MD1 */
#घोषणा V_ODEC_CON		0x01
#घोषणा V_PLL_ADJ		0x04
#घोषणा V_PCM_DR		0x10
#घोषणा V_PCM_LOOP		0x40
/* R_PCM_MD2 */
#घोषणा V_SYNC_PLL		0x02
#घोषणा V_SYNC_SRC		0x04
#घोषणा V_SYNC_OUT		0x08
#घोषणा V_ICR_FR_TIME		0x40
#घोषणा V_EN_PLL		0x80

/* chapter 7: pulse width modulation */
/* R_PWM_MD */
#घोषणा V_EXT_IRQ_EN		0x08
#घोषणा V_PWM0_MD		0x10
#घोषणा V_PWM1_MD		0x40

/* chapter 8: multiparty audio conferences */
/* R_CONF_EN */
#घोषणा V_CONF_EN		0x01
#घोषणा V_ULAW			0x80
/* A_CONF */
#घोषणा V_CONF_NUM		0x01
#घोषणा V_NOISE_SUPPR		0x08
#घोषणा V_ATT_LEV		0x20
#घोषणा V_CONF_SL		0x80
/* R_CONF_OFLOW */
#घोषणा V_CONF_OFLOW0		0x01
#घोषणा V_CONF_OFLOW1		0x02
#घोषणा V_CONF_OFLOW2		0x04
#घोषणा V_CONF_OFLOW3		0x08
#घोषणा V_CONF_OFLOW4		0x10
#घोषणा V_CONF_OFLOW5		0x20
#घोषणा V_CONF_OFLOW6		0x40
#घोषणा V_CONF_OFLOW7		0x80

/* chapter 9: DTMF contoller */
/* R_DTMF0 */
#घोषणा V_DTMF_EN		0x01
#घोषणा V_HARM_SEL		0x02
#घोषणा V_DTMF_RX_CH		0x04
#घोषणा V_DTMF_STOP		0x08
#घोषणा V_CHBL_SEL		0x10
#घोषणा V_RST_DTMF		0x40
#घोषणा V_ULAW_SEL		0x80

/* chapter 10: BERT */
/* R_BERT_WD_MD */
#घोषणा V_PAT_SEQ		0x01
#घोषणा V_BERT_ERR		0x08
#घोषणा V_AUTO_WD_RES		0x20
#घोषणा V_WD_RES		0x80
/* R_BERT_STA */
#घोषणा V_BERT_SYNC_SRC		0x01
#घोषणा V_BERT_SYNC		0x10
#घोषणा V_BERT_INV_DATA		0x20

/* chapter 11: auxiliary पूर्णांकerface */
/* R_BRG_PCM_CFG */
#घोषणा V_BRG_EN		0x01
#घोषणा V_BRG_MD		0x02
#घोषणा V_PCM_CLK		0x20
#घोषणा V_ADDR_WRDLY		0x40
/* R_BRG_CTRL */
#घोषणा V_BRG_CS		0x01
#घोषणा V_BRG_ADDR		0x08
#घोषणा V_BRG_CS_SRC		0x80
/* R_BRG_MD */
#घोषणा V_BRG_MD0		0x01
#घोषणा V_BRG_MD1		0x02
#घोषणा V_BRG_MD2		0x04
#घोषणा V_BRG_MD3		0x08
#घोषणा V_BRG_MD4		0x10
#घोषणा V_BRG_MD5		0x20
#घोषणा V_BRG_MD6		0x40
#घोषणा V_BRG_MD7		0x80
/* R_BRG_TIM0 */
#घोषणा V_BRG_TIM0_IDLE		0x01
#घोषणा V_BRG_TIM0_CLK		0x10
/* R_BRG_TIM1 */
#घोषणा V_BRG_TIM1_IDLE		0x01
#घोषणा V_BRG_TIM1_CLK		0x10
/* R_BRG_TIM2 */
#घोषणा V_BRG_TIM2_IDLE		0x01
#घोषणा V_BRG_TIM2_CLK		0x10
/* R_BRG_TIM3 */
#घोषणा V_BRG_TIM3_IDLE		0x01
#घोषणा V_BRG_TIM3_CLK		0x10
/* R_BRG_TIM_SEL01 */
#घोषणा V_BRG_WR_SEL0		0x01
#घोषणा V_BRG_RD_SEL0		0x04
#घोषणा V_BRG_WR_SEL1		0x10
#घोषणा V_BRG_RD_SEL1		0x40
/* R_BRG_TIM_SEL23 */
#घोषणा V_BRG_WR_SEL2		0x01
#घोषणा V_BRG_RD_SEL2		0x04
#घोषणा V_BRG_WR_SEL3		0x10
#घोषणा V_BRG_RD_SEL3		0x40
/* R_BRG_TIM_SEL45 */
#घोषणा V_BRG_WR_SEL4		0x01
#घोषणा V_BRG_RD_SEL4		0x04
#घोषणा V_BRG_WR_SEL5		0x10
#घोषणा V_BRG_RD_SEL5		0x40
/* R_BRG_TIM_SEL67 */
#घोषणा V_BRG_WR_SEL6		0x01
#घोषणा V_BRG_RD_SEL6		0x04
#घोषणा V_BRG_WR_SEL7		0x10
#घोषणा V_BRG_RD_SEL7		0x40

/* chapter 12: घड़ी, reset, पूर्णांकerrupt, समयr and watchकरोg */
/* R_IRQMSK_MISC */
#घोषणा V_STA_IRQMSK		0x01
#घोषणा V_TI_IRQMSK		0x02
#घोषणा V_PROC_IRQMSK		0x04
#घोषणा V_DTMF_IRQMSK		0x08
#घोषणा V_IRQ1S_MSK		0x10
#घोषणा V_SA6_IRQMSK		0x20
#घोषणा V_RX_EOMF_MSK		0x40
#घोषणा V_TX_EOMF_MSK		0x80
/* R_IRQ_CTRL */
#घोषणा V_FIFO_IRQ		0x01
#घोषणा V_GLOB_IRQ_EN		0x08
#घोषणा V_IRQ_POL		0x10
/* R_TI_WD */
#घोषणा V_EV_TS			0x01
#घोषणा V_WD_TS			0x10
/* A_IRQ_MSK */
#घोषणा V_IRQ			0x01
#घोषणा V_BERT_EN		0x02
#घोषणा V_MIX_IRQ		0x04
/* R_IRQ_OVIEW */
#घोषणा V_IRQ_FIFO_BL0		0x01
#घोषणा V_IRQ_FIFO_BL1		0x02
#घोषणा V_IRQ_FIFO_BL2		0x04
#घोषणा V_IRQ_FIFO_BL3		0x08
#घोषणा V_IRQ_FIFO_BL4		0x10
#घोषणा V_IRQ_FIFO_BL5		0x20
#घोषणा V_IRQ_FIFO_BL6		0x40
#घोषणा V_IRQ_FIFO_BL7		0x80
/* R_IRQ_MISC */
#घोषणा V_STA_IRQ		0x01
#घोषणा V_TI_IRQ		0x02
#घोषणा V_IRQ_PROC		0x04
#घोषणा V_DTMF_IRQ		0x08
#घोषणा V_IRQ1S			0x10
#घोषणा V_SA6_IRQ		0x20
#घोषणा V_RX_EOMF		0x40
#घोषणा V_TX_EOMF		0x80
/* R_STATUS */
#घोषणा V_BUSY			0x01
#घोषणा V_PROC			0x02
#घोषणा V_DTMF_STA		0x04
#घोषणा V_LOST_STA		0x08
#घोषणा V_SYNC_IN		0x10
#घोषणा V_EXT_IRQSTA		0x20
#घोषणा V_MISC_IRQSTA		0x40
#घोषणा V_FR_IRQSTA		0x80
/* R_IRQ_FIFO_BL0 */
#घोषणा V_IRQ_FIFO0_TX		0x01
#घोषणा V_IRQ_FIFO0_RX		0x02
#घोषणा V_IRQ_FIFO1_TX		0x04
#घोषणा V_IRQ_FIFO1_RX		0x08
#घोषणा V_IRQ_FIFO2_TX		0x10
#घोषणा V_IRQ_FIFO2_RX		0x20
#घोषणा V_IRQ_FIFO3_TX		0x40
#घोषणा V_IRQ_FIFO3_RX		0x80
/* R_IRQ_FIFO_BL1 */
#घोषणा V_IRQ_FIFO4_TX		0x01
#घोषणा V_IRQ_FIFO4_RX		0x02
#घोषणा V_IRQ_FIFO5_TX		0x04
#घोषणा V_IRQ_FIFO5_RX		0x08
#घोषणा V_IRQ_FIFO6_TX		0x10
#घोषणा V_IRQ_FIFO6_RX		0x20
#घोषणा V_IRQ_FIFO7_TX		0x40
#घोषणा V_IRQ_FIFO7_RX		0x80
/* R_IRQ_FIFO_BL2 */
#घोषणा V_IRQ_FIFO8_TX		0x01
#घोषणा V_IRQ_FIFO8_RX		0x02
#घोषणा V_IRQ_FIFO9_TX		0x04
#घोषणा V_IRQ_FIFO9_RX		0x08
#घोषणा V_IRQ_FIFO10_TX		0x10
#घोषणा V_IRQ_FIFO10_RX		0x20
#घोषणा V_IRQ_FIFO11_TX		0x40
#घोषणा V_IRQ_FIFO11_RX		0x80
/* R_IRQ_FIFO_BL3 */
#घोषणा V_IRQ_FIFO12_TX		0x01
#घोषणा V_IRQ_FIFO12_RX		0x02
#घोषणा V_IRQ_FIFO13_TX		0x04
#घोषणा V_IRQ_FIFO13_RX		0x08
#घोषणा V_IRQ_FIFO14_TX		0x10
#घोषणा V_IRQ_FIFO14_RX		0x20
#घोषणा V_IRQ_FIFO15_TX		0x40
#घोषणा V_IRQ_FIFO15_RX		0x80
/* R_IRQ_FIFO_BL4 */
#घोषणा V_IRQ_FIFO16_TX		0x01
#घोषणा V_IRQ_FIFO16_RX		0x02
#घोषणा V_IRQ_FIFO17_TX		0x04
#घोषणा V_IRQ_FIFO17_RX		0x08
#घोषणा V_IRQ_FIFO18_TX		0x10
#घोषणा V_IRQ_FIFO18_RX		0x20
#घोषणा V_IRQ_FIFO19_TX		0x40
#घोषणा V_IRQ_FIFO19_RX		0x80
/* R_IRQ_FIFO_BL5 */
#घोषणा V_IRQ_FIFO20_TX		0x01
#घोषणा V_IRQ_FIFO20_RX		0x02
#घोषणा V_IRQ_FIFO21_TX		0x04
#घोषणा V_IRQ_FIFO21_RX		0x08
#घोषणा V_IRQ_FIFO22_TX		0x10
#घोषणा V_IRQ_FIFO22_RX		0x20
#घोषणा V_IRQ_FIFO23_TX		0x40
#घोषणा V_IRQ_FIFO23_RX		0x80
/* R_IRQ_FIFO_BL6 */
#घोषणा V_IRQ_FIFO24_TX		0x01
#घोषणा V_IRQ_FIFO24_RX		0x02
#घोषणा V_IRQ_FIFO25_TX		0x04
#घोषणा V_IRQ_FIFO25_RX		0x08
#घोषणा V_IRQ_FIFO26_TX		0x10
#घोषणा V_IRQ_FIFO26_RX		0x20
#घोषणा V_IRQ_FIFO27_TX		0x40
#घोषणा V_IRQ_FIFO27_RX		0x80
/* R_IRQ_FIFO_BL7 */
#घोषणा V_IRQ_FIFO28_TX		0x01
#घोषणा V_IRQ_FIFO28_RX		0x02
#घोषणा V_IRQ_FIFO29_TX		0x04
#घोषणा V_IRQ_FIFO29_RX		0x08
#घोषणा V_IRQ_FIFO30_TX		0x10
#घोषणा V_IRQ_FIFO30_RX		0x20
#घोषणा V_IRQ_FIFO31_TX		0x40
#घोषणा V_IRQ_FIFO31_RX		0x80

/* chapter 13: general purpose I/O pins (GPIO) and input pins (GPI) */
/* R_GPIO_OUT0 */
#घोषणा V_GPIO_OUT0		0x01
#घोषणा V_GPIO_OUT1		0x02
#घोषणा V_GPIO_OUT2		0x04
#घोषणा V_GPIO_OUT3		0x08
#घोषणा V_GPIO_OUT4		0x10
#घोषणा V_GPIO_OUT5		0x20
#घोषणा V_GPIO_OUT6		0x40
#घोषणा V_GPIO_OUT7		0x80
/* R_GPIO_OUT1 */
#घोषणा V_GPIO_OUT8		0x01
#घोषणा V_GPIO_OUT9		0x02
#घोषणा V_GPIO_OUT10		0x04
#घोषणा V_GPIO_OUT11		0x08
#घोषणा V_GPIO_OUT12		0x10
#घोषणा V_GPIO_OUT13		0x20
#घोषणा V_GPIO_OUT14		0x40
#घोषणा V_GPIO_OUT15		0x80
/* R_GPIO_EN0 */
#घोषणा V_GPIO_EN0		0x01
#घोषणा V_GPIO_EN1		0x02
#घोषणा V_GPIO_EN2		0x04
#घोषणा V_GPIO_EN3		0x08
#घोषणा V_GPIO_EN4		0x10
#घोषणा V_GPIO_EN5		0x20
#घोषणा V_GPIO_EN6		0x40
#घोषणा V_GPIO_EN7		0x80
/* R_GPIO_EN1 */
#घोषणा V_GPIO_EN8		0x01
#घोषणा V_GPIO_EN9		0x02
#घोषणा V_GPIO_EN10		0x04
#घोषणा V_GPIO_EN11		0x08
#घोषणा V_GPIO_EN12		0x10
#घोषणा V_GPIO_EN13		0x20
#घोषणा V_GPIO_EN14		0x40
#घोषणा V_GPIO_EN15		0x80
/* R_GPIO_SEL */
#घोषणा V_GPIO_SEL0		0x01
#घोषणा V_GPIO_SEL1		0x02
#घोषणा V_GPIO_SEL2		0x04
#घोषणा V_GPIO_SEL3		0x08
#घोषणा V_GPIO_SEL4		0x10
#घोषणा V_GPIO_SEL5		0x20
#घोषणा V_GPIO_SEL6		0x40
#घोषणा V_GPIO_SEL7		0x80
/* R_GPIO_IN0 */
#घोषणा V_GPIO_IN0		0x01
#घोषणा V_GPIO_IN1		0x02
#घोषणा V_GPIO_IN2		0x04
#घोषणा V_GPIO_IN3		0x08
#घोषणा V_GPIO_IN4		0x10
#घोषणा V_GPIO_IN5		0x20
#घोषणा V_GPIO_IN6		0x40
#घोषणा V_GPIO_IN7		0x80
/* R_GPIO_IN1 */
#घोषणा V_GPIO_IN8		0x01
#घोषणा V_GPIO_IN9		0x02
#घोषणा V_GPIO_IN10		0x04
#घोषणा V_GPIO_IN11		0x08
#घोषणा V_GPIO_IN12		0x10
#घोषणा V_GPIO_IN13		0x20
#घोषणा V_GPIO_IN14		0x40
#घोषणा V_GPIO_IN15		0x80
/* R_GPI_IN0 */
#घोषणा V_GPI_IN0		0x01
#घोषणा V_GPI_IN1		0x02
#घोषणा V_GPI_IN2		0x04
#घोषणा V_GPI_IN3		0x08
#घोषणा V_GPI_IN4		0x10
#घोषणा V_GPI_IN5		0x20
#घोषणा V_GPI_IN6		0x40
#घोषणा V_GPI_IN7		0x80
/* R_GPI_IN1 */
#घोषणा V_GPI_IN8		0x01
#घोषणा V_GPI_IN9		0x02
#घोषणा V_GPI_IN10		0x04
#घोषणा V_GPI_IN11		0x08
#घोषणा V_GPI_IN12		0x10
#घोषणा V_GPI_IN13		0x20
#घोषणा V_GPI_IN14		0x40
#घोषणा V_GPI_IN15		0x80
/* R_GPI_IN2 */
#घोषणा V_GPI_IN16		0x01
#घोषणा V_GPI_IN17		0x02
#घोषणा V_GPI_IN18		0x04
#घोषणा V_GPI_IN19		0x08
#घोषणा V_GPI_IN20		0x10
#घोषणा V_GPI_IN21		0x20
#घोषणा V_GPI_IN22		0x40
#घोषणा V_GPI_IN23		0x80
/* R_GPI_IN3 */
#घोषणा V_GPI_IN24		0x01
#घोषणा V_GPI_IN25		0x02
#घोषणा V_GPI_IN26		0x04
#घोषणा V_GPI_IN27		0x08
#घोषणा V_GPI_IN28		0x10
#घोषणा V_GPI_IN29		0x20
#घोषणा V_GPI_IN30		0x40
#घोषणा V_GPI_IN31		0x80

/* map of all रेजिस्टरs, used क्रम debugging */

#अगर_घोषित HFC_REGISTER_DEBUG
काष्ठा hfc_रेजिस्टर_names अणु
	अक्षर *name;
	u_अक्षर reg;
पूर्ण hfc_रेजिस्टर_names[] = अणु
	/* ग_लिखो रेजिस्टरs */
	अणु"R_CIRM",		0x00पूर्ण,
	अणु"R_CTRL",		0x01पूर्ण,
	अणु"R_BRG_PCM_CFG ",	0x02पूर्ण,
	अणु"R_RAM_ADDR0",		0x08पूर्ण,
	अणु"R_RAM_ADDR1",		0x09पूर्ण,
	अणु"R_RAM_ADDR2",		0x0Aपूर्ण,
	अणु"R_FIRST_FIFO",	0x0Bपूर्ण,
	अणु"R_RAM_SZ",		0x0Cपूर्ण,
	अणु"R_FIFO_MD",		0x0Dपूर्ण,
	अणु"R_INC_RES_FIFO",	0x0Eपूर्ण,
	अणु"R_FIFO / R_FSM_IDX",	0x0Fपूर्ण,
	अणु"R_SLOT",		0x10पूर्ण,
	अणु"R_IRQMSK_MISC",	0x11पूर्ण,
	अणु"R_SCI_MSK",		0x12पूर्ण,
	अणु"R_IRQ_CTRL",		0x13पूर्ण,
	अणु"R_PCM_MD0",		0x14पूर्ण,
	अणु"R_0x15",		0x15पूर्ण,
	अणु"R_ST_SEL",		0x16पूर्ण,
	अणु"R_ST_SYNC",		0x17पूर्ण,
	अणु"R_CONF_EN",		0x18पूर्ण,
	अणु"R_TI_WD",		0x1Aपूर्ण,
	अणु"R_BERT_WD_MD",	0x1Bपूर्ण,
	अणु"R_DTMF",		0x1Cपूर्ण,
	अणु"R_DTMF_N",		0x1Dपूर्ण,
	अणु"R_E1_XX_STA",		0x20पूर्ण,
	अणु"R_LOS0",		0x22पूर्ण,
	अणु"R_LOS1",		0x23पूर्ण,
	अणु"R_RX0",		0x24पूर्ण,
	अणु"R_RX_FR0",		0x25पूर्ण,
	अणु"R_RX_FR1",		0x26पूर्ण,
	अणु"R_TX0",		0x28पूर्ण,
	अणु"R_TX1",		0x29पूर्ण,
	अणु"R_TX_FR0",		0x2Cपूर्ण,
	अणु"R_TX_FR1",		0x2Dपूर्ण,
	अणु"R_TX_FR2",		0x2Eपूर्ण,
	अणु"R_JATT_ATT",		0x2Fपूर्ण,
	अणु"A_ST_xx_STA/R_RX_OFF", 0x30पूर्ण,
	अणु"A_ST_CTRL0/R_SYNC_OUT", 0x31पूर्ण,
	अणु"A_ST_CTRL1",		0x32पूर्ण,
	अणु"A_ST_CTRL2",		0x33पूर्ण,
	अणु"A_ST_SQ_WR",		0x34पूर्ण,
	अणु"R_TX_OFF",		0x34पूर्ण,
	अणु"R_SYNC_CTRL",		0x35पूर्ण,
	अणु"A_ST_CLK_DLY",	0x37पूर्ण,
	अणु"R_PWM0",		0x38पूर्ण,
	अणु"R_PWM1",		0x39पूर्ण,
	अणु"A_ST_B1_TX",		0x3Cपूर्ण,
	अणु"A_ST_B2_TX",		0x3Dपूर्ण,
	अणु"A_ST_D_TX",		0x3Eपूर्ण,
	अणु"R_GPIO_OUT0",		0x40पूर्ण,
	अणु"R_GPIO_OUT1",		0x41पूर्ण,
	अणु"R_GPIO_EN0",		0x42पूर्ण,
	अणु"R_GPIO_EN1",		0x43पूर्ण,
	अणु"R_GPIO_SEL",		0x44पूर्ण,
	अणु"R_BRG_CTRL",		0x45पूर्ण,
	अणु"R_PWM_MD",		0x46पूर्ण,
	अणु"R_BRG_MD",		0x47पूर्ण,
	अणु"R_BRG_TIM0",		0x48पूर्ण,
	अणु"R_BRG_TIM1",		0x49पूर्ण,
	अणु"R_BRG_TIM2",		0x4Aपूर्ण,
	अणु"R_BRG_TIM3",		0x4Bपूर्ण,
	अणु"R_BRG_TIM_SEL01",	0x4Cपूर्ण,
	अणु"R_BRG_TIM_SEL23",	0x4Dपूर्ण,
	अणु"R_BRG_TIM_SEL45",	0x4Eपूर्ण,
	अणु"R_BRG_TIM_SEL67",	0x4Fपूर्ण,
	अणु"A_FIFO_DATA0-2",	0x80पूर्ण,
	अणु"A_FIFO_DATA0-2_NOINC", 0x84पूर्ण,
	अणु"R_RAM_DATA",		0xC0पूर्ण,
	अणु"A_SL_CFG",		0xD0पूर्ण,
	अणु"A_CONF",		0xD1पूर्ण,
	अणु"A_CH_MSK",		0xF4पूर्ण,
	अणु"A_CON_HDLC",		0xFAपूर्ण,
	अणु"A_SUBCH_CFG",		0xFBपूर्ण,
	अणु"A_CHANNEL",		0xFCपूर्ण,
	अणु"A_FIFO_SEQ",		0xFDपूर्ण,
	अणु"A_IRQ_MSK",		0xFFपूर्ण,
	अणुशून्य, 0पूर्ण,

	/* पढ़ो रेजिस्टरs */
	अणु"A_Z1",		0x04पूर्ण,
	अणु"A_Z1H",		0x05पूर्ण,
	अणु"A_Z2",		0x06पूर्ण,
	अणु"A_Z2H",		0x07पूर्ण,
	अणु"A_F1",		0x0Cपूर्ण,
	अणु"A_F2",		0x0Dपूर्ण,
	अणु"R_IRQ_OVIEW",		0x10पूर्ण,
	अणु"R_IRQ_MISC",		0x11पूर्ण,
	अणु"R_IRQ_STATECH",	0x12पूर्ण,
	अणु"R_CONF_OFLOW",	0x14पूर्ण,
	अणु"R_RAM_USE",		0x15पूर्ण,
	अणु"R_CHIP_ID",		0x16पूर्ण,
	अणु"R_BERT_STA",		0x17पूर्ण,
	अणु"R_F0_CNTL",		0x18पूर्ण,
	अणु"R_F0_CNTH",		0x19पूर्ण,
	अणु"R_BERT_ECL",		0x1Aपूर्ण,
	अणु"R_BERT_ECH",		0x1Bपूर्ण,
	अणु"R_STATUS",		0x1Cपूर्ण,
	अणु"R_CHIP_RV",		0x1Fपूर्ण,
	अणु"R_STATE",		0x20पूर्ण,
	अणु"R_SYNC_STA",		0x24पूर्ण,
	अणु"R_RX_SL0_0",		0x25पूर्ण,
	अणु"R_RX_SL0_1",		0x26पूर्ण,
	अणु"R_RX_SL0_2",		0x27पूर्ण,
	अणु"R_JATT_DIR",		0x2bपूर्ण,
	अणु"R_SLIP",		0x2cपूर्ण,
	अणु"A_ST_RD_STA",		0x30पूर्ण,
	अणु"R_FAS_ECL",		0x30पूर्ण,
	अणु"R_FAS_ECH",		0x31पूर्ण,
	अणु"R_VIO_ECL",		0x32पूर्ण,
	अणु"R_VIO_ECH",		0x33पूर्ण,
	अणु"R_CRC_ECL / A_ST_SQ_RD", 0x34पूर्ण,
	अणु"R_CRC_ECH",		0x35पूर्ण,
	अणु"R_E_ECL",		0x36पूर्ण,
	अणु"R_E_ECH",		0x37पूर्ण,
	अणु"R_SA6_SA13_ECL",	0x38पूर्ण,
	अणु"R_SA6_SA13_ECH",	0x39पूर्ण,
	अणु"R_SA6_SA23_ECL",	0x3Aपूर्ण,
	अणु"R_SA6_SA23_ECH",	0x3Bपूर्ण,
	अणु"A_ST_B1_RX",		0x3Cपूर्ण,
	अणु"A_ST_B2_RX",		0x3Dपूर्ण,
	अणु"A_ST_D_RX",		0x3Eपूर्ण,
	अणु"A_ST_E_RX",		0x3Fपूर्ण,
	अणु"R_GPIO_IN0",		0x40पूर्ण,
	अणु"R_GPIO_IN1",		0x41पूर्ण,
	अणु"R_GPI_IN0",		0x44पूर्ण,
	अणु"R_GPI_IN1",		0x45पूर्ण,
	अणु"R_GPI_IN2",		0x46पूर्ण,
	अणु"R_GPI_IN3",		0x47पूर्ण,
	अणु"A_FIFO_DATA0-2",	0x80पूर्ण,
	अणु"A_FIFO_DATA0-2_NOINC", 0x84पूर्ण,
	अणु"R_INT_DATA",		0x88पूर्ण,
	अणु"R_RAM_DATA",		0xC0पूर्ण,
	अणु"R_IRQ_FIFO_BL0",	0xC8पूर्ण,
	अणु"R_IRQ_FIFO_BL1",	0xC9पूर्ण,
	अणु"R_IRQ_FIFO_BL2",	0xCAपूर्ण,
	अणु"R_IRQ_FIFO_BL3",	0xCBपूर्ण,
	अणु"R_IRQ_FIFO_BL4",	0xCCपूर्ण,
	अणु"R_IRQ_FIFO_BL5",	0xCDपूर्ण,
	अणु"R_IRQ_FIFO_BL6",	0xCEपूर्ण,
	अणु"R_IRQ_FIFO_BL7",	0xCFपूर्ण,
पूर्ण;
#पूर्ण_अगर /* HFC_REGISTER_DEBUG */
