<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2010 OMICRON electronics GmbH
 * Copyright 2018 NXP
 */
#अगर_अघोषित __PTP_QORIQ_H__
#घोषणा __PTP_QORIQ_H__

#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ptp_घड़ी_kernel.h>

/*
 * qoriq ptp रेजिस्टरs
 */
काष्ठा ctrl_regs अणु
	u32 पंचांगr_ctrl;     /* Timer control रेजिस्टर */
	u32 पंचांगr_tevent;   /* Timestamp event रेजिस्टर */
	u32 पंचांगr_temask;   /* Timer event mask रेजिस्टर */
	u32 पंचांगr_pevent;   /* Timestamp event रेजिस्टर */
	u32 पंचांगr_pemask;   /* Timer event mask रेजिस्टर */
	u32 पंचांगr_stat;     /* Timestamp status रेजिस्टर */
	u32 पंचांगr_cnt_h;    /* Timer counter high रेजिस्टर */
	u32 पंचांगr_cnt_l;    /* Timer counter low रेजिस्टर */
	u32 पंचांगr_add;      /* Timer drअगरt compensation addend रेजिस्टर */
	u32 पंचांगr_acc;      /* Timer accumulator रेजिस्टर */
	u32 पंचांगr_prsc;     /* Timer prescale */
	u8  res1[4];
	u32 पंचांगroff_h;     /* Timer offset high */
	u32 पंचांगroff_l;     /* Timer offset low */
पूर्ण;

काष्ठा alarm_regs अणु
	u32 पंचांगr_alarm1_h; /* Timer alarm 1 high रेजिस्टर */
	u32 पंचांगr_alarm1_l; /* Timer alarm 1 high रेजिस्टर */
	u32 पंचांगr_alarm2_h; /* Timer alarm 2 high रेजिस्टर */
	u32 पंचांगr_alarm2_l; /* Timer alarm 2 high रेजिस्टर */
पूर्ण;

काष्ठा fiper_regs अणु
	u32 पंचांगr_fiper1;   /* Timer fixed period पूर्णांकerval */
	u32 पंचांगr_fiper2;   /* Timer fixed period पूर्णांकerval */
	u32 पंचांगr_fiper3;   /* Timer fixed period पूर्णांकerval */
पूर्ण;

काष्ठा etts_regs अणु
	u32 पंचांगr_etts1_h;  /* Timestamp of general purpose बाह्यal trigger */
	u32 पंचांगr_etts1_l;  /* Timestamp of general purpose बाह्यal trigger */
	u32 पंचांगr_etts2_h;  /* Timestamp of general purpose बाह्यal trigger */
	u32 पंचांगr_etts2_l;  /* Timestamp of general purpose बाह्यal trigger */
पूर्ण;

काष्ठा ptp_qoriq_रेजिस्टरs अणु
	काष्ठा ctrl_regs __iomem *ctrl_regs;
	काष्ठा alarm_regs __iomem *alarm_regs;
	काष्ठा fiper_regs __iomem *fiper_regs;
	काष्ठा etts_regs __iomem *etts_regs;
पूर्ण;

/* Offset definitions क्रम the four रेजिस्टर groups */
#घोषणा ETSEC_CTRL_REGS_OFFSET	0x0
#घोषणा ETSEC_ALARM_REGS_OFFSET	0x40
#घोषणा ETSEC_FIPER_REGS_OFFSET	0x80
#घोषणा ETSEC_ETTS_REGS_OFFSET	0xa0

#घोषणा CTRL_REGS_OFFSET	0x80
#घोषणा ALARM_REGS_OFFSET	0xb8
#घोषणा FIPER_REGS_OFFSET	0xd0
#घोषणा ETTS_REGS_OFFSET	0xe0


/* Bit definitions क्रम the TMR_CTRL रेजिस्टर */
#घोषणा ALM1P                 (1<<31) /* Alarm1 output polarity */
#घोषणा ALM2P                 (1<<30) /* Alarm2 output polarity */
#घोषणा FIPERST               (1<<28) /* FIPER start indication */
#घोषणा PP1L                  (1<<27) /* Fiper1 pulse loopback mode enabled. */
#घोषणा PP2L                  (1<<26) /* Fiper2 pulse loopback mode enabled. */
#घोषणा TCLK_PERIOD_SHIFT     (16) /* 1588 समयr reference घड़ी period. */
#घोषणा TCLK_PERIOD_MASK      (0x3ff)
#घोषणा RTPE                  (1<<15) /* Record Tx Timestamp to PAL Enable. */
#घोषणा FRD                   (1<<14) /* FIPER Realignment Disable */
#घोषणा ESFDP                 (1<<11) /* External Tx/Rx SFD Polarity. */
#घोषणा ESFDE                 (1<<10) /* External Tx/Rx SFD Enable. */
#घोषणा ETEP2                 (1<<9) /* External trigger 2 edge polarity */
#घोषणा ETEP1                 (1<<8) /* External trigger 1 edge polarity */
#घोषणा COPH                  (1<<7) /* Generated घड़ी output phase. */
#घोषणा CIPH                  (1<<6) /* External oscillator input घड़ी phase */
#घोषणा TMSR                  (1<<5) /* Timer soft reset. */
#घोषणा BYP                   (1<<3) /* Bypass drअगरt compensated घड़ी */
#घोषणा TE                    (1<<2) /* 1588 समयr enable. */
#घोषणा CKSEL_SHIFT           (0)    /* 1588 Timer reference घड़ी source */
#घोषणा CKSEL_MASK            (0x3)

/* Bit definitions क्रम the TMR_TEVENT रेजिस्टर */
#घोषणा ETS2                  (1<<25) /* External trigger 2 बारtamp sampled */
#घोषणा ETS1                  (1<<24) /* External trigger 1 बारtamp sampled */
#घोषणा ALM2                  (1<<17) /* Current समय = alarm समय रेजिस्टर 2 */
#घोषणा ALM1                  (1<<16) /* Current समय = alarm समय रेजिस्टर 1 */
#घोषणा PP1                   (1<<7)  /* periodic pulse generated on FIPER1 */
#घोषणा PP2                   (1<<6)  /* periodic pulse generated on FIPER2 */
#घोषणा PP3                   (1<<5)  /* periodic pulse generated on FIPER3 */

/* Bit definitions क्रम the TMR_TEMASK रेजिस्टर */
#घोषणा ETS2EN                (1<<25) /* External trigger 2 बारtamp enable */
#घोषणा ETS1EN                (1<<24) /* External trigger 1 बारtamp enable */
#घोषणा ALM2EN                (1<<17) /* Timer ALM2 event enable */
#घोषणा ALM1EN                (1<<16) /* Timer ALM1 event enable */
#घोषणा PP1EN                 (1<<7) /* Periodic pulse event 1 enable */
#घोषणा PP2EN                 (1<<6) /* Periodic pulse event 2 enable */

/* Bit definitions क्रम the TMR_PEVENT रेजिस्टर */
#घोषणा TXP2                  (1<<9) /* PTP transmitted बारtamp im TXTS2 */
#घोषणा TXP1                  (1<<8) /* PTP transmitted बारtamp in TXTS1 */
#घोषणा RXP                   (1<<0) /* PTP frame has been received */

/* Bit definitions क्रम the TMR_PEMASK रेजिस्टर */
#घोषणा TXP2EN                (1<<9) /* Transmit PTP packet event 2 enable */
#घोषणा TXP1EN                (1<<8) /* Transmit PTP packet event 1 enable */
#घोषणा RXPEN                 (1<<0) /* Receive PTP packet event enable */

/* Bit definitions क्रम the TMR_STAT रेजिस्टर */
#घोषणा STAT_VEC_SHIFT        (0) /* Timer general purpose status vector */
#घोषणा STAT_VEC_MASK         (0x3f)
#घोषणा ETS1_VLD              (1<<24)
#घोषणा ETS2_VLD              (1<<25)

/* Bit definitions क्रम the TMR_PRSC रेजिस्टर */
#घोषणा PRSC_OCK_SHIFT        (0) /* Output घड़ी भागision/prescale factor. */
#घोषणा PRSC_OCK_MASK         (0xffff)


#घोषणा DRIVER		"ptp_qoriq"
#घोषणा N_EXT_TS	2

#घोषणा DEFAULT_CKSEL		1
#घोषणा DEFAULT_TMR_PRSC	2
#घोषणा DEFAULT_FIPER1_PERIOD	1000000000
#घोषणा DEFAULT_FIPER2_PERIOD	1000000000
#घोषणा DEFAULT_FIPER3_PERIOD	1000000000

काष्ठा ptp_qoriq अणु
	व्योम __iomem *base;
	काष्ठा ptp_qoriq_रेजिस्टरs regs;
	spinlock_t lock; /* protects regs */
	काष्ठा ptp_घड़ी *घड़ी;
	काष्ठा ptp_घड़ी_info caps;
	काष्ठा resource *rsrc;
	काष्ठा dentry *debugfs_root;
	काष्ठा device *dev;
	bool extts_fअगरo_support;
	bool fiper3_support;
	पूर्णांक irq;
	पूर्णांक phc_index;
	u32 tclk_period;  /* nanoseconds */
	u32 पंचांगr_prsc;
	u32 पंचांगr_add;
	u32 cksel;
	u32 पंचांगr_fiper1;
	u32 पंचांगr_fiper2;
	u32 पंचांगr_fiper3;
	u32 (*पढ़ो)(अचिन्हित __iomem *addr);
	व्योम (*ग_लिखो)(अचिन्हित __iomem *addr, u32 val);
पूर्ण;

अटल अंतरभूत u32 qoriq_पढ़ो_be(अचिन्हित __iomem *addr)
अणु
	वापस ioपढ़ो32be(addr);
पूर्ण

अटल अंतरभूत व्योम qoriq_ग_लिखो_be(अचिन्हित __iomem *addr, u32 val)
अणु
	ioग_लिखो32be(val, addr);
पूर्ण

अटल अंतरभूत u32 qoriq_पढ़ो_le(अचिन्हित __iomem *addr)
अणु
	वापस ioपढ़ो32(addr);
पूर्ण

अटल अंतरभूत व्योम qoriq_ग_लिखो_le(अचिन्हित __iomem *addr, u32 val)
अणु
	ioग_लिखो32(val, addr);
पूर्ण

irqवापस_t ptp_qoriq_isr(पूर्णांक irq, व्योम *priv);
पूर्णांक ptp_qoriq_init(काष्ठा ptp_qoriq *ptp_qoriq, व्योम __iomem *base,
		   स्थिर काष्ठा ptp_घड़ी_info *caps);
व्योम ptp_qoriq_मुक्त(काष्ठा ptp_qoriq *ptp_qoriq);
पूर्णांक ptp_qoriq_adjfine(काष्ठा ptp_घड़ी_info *ptp, दीर्घ scaled_ppm);
पूर्णांक ptp_qoriq_adjसमय(काष्ठा ptp_घड़ी_info *ptp, s64 delta);
पूर्णांक ptp_qoriq_समय_लो(काष्ठा ptp_घड़ी_info *ptp, काष्ठा बारpec64 *ts);
पूर्णांक ptp_qoriq_समय_रखो(काष्ठा ptp_घड़ी_info *ptp,
		      स्थिर काष्ठा बारpec64 *ts);
पूर्णांक ptp_qoriq_enable(काष्ठा ptp_घड़ी_info *ptp,
		     काष्ठा ptp_घड़ी_request *rq, पूर्णांक on);
पूर्णांक extts_clean_up(काष्ठा ptp_qoriq *ptp_qoriq, पूर्णांक index, bool update_event);
#अगर_घोषित CONFIG_DEBUG_FS
व्योम ptp_qoriq_create_debugfs(काष्ठा ptp_qoriq *ptp_qoriq);
व्योम ptp_qoriq_हटाओ_debugfs(काष्ठा ptp_qoriq *ptp_qoriq);
#अन्यथा
अटल अंतरभूत व्योम ptp_qoriq_create_debugfs(काष्ठा ptp_qoriq *ptp_qoriq)
अणु पूर्ण
अटल अंतरभूत व्योम ptp_qoriq_हटाओ_debugfs(काष्ठा ptp_qoriq *ptp_qoriq)
अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
