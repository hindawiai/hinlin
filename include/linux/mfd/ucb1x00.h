<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/include/mfd/ucb1x00.h
 *
 *  Copyright (C) 2001 Russell King, All Rights Reserved.
 */
#अगर_अघोषित UCB1200_H
#घोषणा UCB1200_H

#समावेश <linux/device.h>
#समावेश <linux/mfd/mcp.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/mutex.h>

#घोषणा UCB_IO_DATA	0x00
#घोषणा UCB_IO_सूची	0x01

#घोषणा UCB_IO_0		(1 << 0)
#घोषणा UCB_IO_1		(1 << 1)
#घोषणा UCB_IO_2		(1 << 2)
#घोषणा UCB_IO_3		(1 << 3)
#घोषणा UCB_IO_4		(1 << 4)
#घोषणा UCB_IO_5		(1 << 5)
#घोषणा UCB_IO_6		(1 << 6)
#घोषणा UCB_IO_7		(1 << 7)
#घोषणा UCB_IO_8		(1 << 8)
#घोषणा UCB_IO_9		(1 << 9)

#घोषणा UCB_IE_RIS	0x02
#घोषणा UCB_IE_FAL	0x03
#घोषणा UCB_IE_STATUS	0x04
#घोषणा UCB_IE_CLEAR	0x04
#घोषणा UCB_IE_ADC		(1 << 11)
#घोषणा UCB_IE_TSPX		(1 << 12)
#घोषणा UCB_IE_TSMX		(1 << 13)
#घोषणा UCB_IE_TCLIP		(1 << 14)
#घोषणा UCB_IE_ACLIP		(1 << 15)

#घोषणा UCB_IRQ_TSPX		12

#घोषणा UCB_TC_A	0x05
#घोषणा UCB_TC_A_LOOP		(1 << 7)	/* UCB1200 */
#घोषणा UCB_TC_A_AMPL		(1 << 7)	/* UCB1300 */

#घोषणा UCB_TC_B	0x06
#घोषणा UCB_TC_B_VOICE_ENA	(1 << 3)
#घोषणा UCB_TC_B_CLIP		(1 << 4)
#घोषणा UCB_TC_B_ATT		(1 << 6)
#घोषणा UCB_TC_B_SIDE_ENA	(1 << 11)
#घोषणा UCB_TC_B_MUTE		(1 << 13)
#घोषणा UCB_TC_B_IN_ENA		(1 << 14)
#घोषणा UCB_TC_B_OUT_ENA	(1 << 15)

#घोषणा UCB_AC_A	0x07
#घोषणा UCB_AC_B	0x08
#घोषणा UCB_AC_B_LOOP		(1 << 8)
#घोषणा UCB_AC_B_MUTE		(1 << 13)
#घोषणा UCB_AC_B_IN_ENA		(1 << 14)
#घोषणा UCB_AC_B_OUT_ENA	(1 << 15)

#घोषणा UCB_TS_CR	0x09
#घोषणा UCB_TS_CR_TSMX_POW	(1 << 0)
#घोषणा UCB_TS_CR_TSPX_POW	(1 << 1)
#घोषणा UCB_TS_CR_TSMY_POW	(1 << 2)
#घोषणा UCB_TS_CR_TSPY_POW	(1 << 3)
#घोषणा UCB_TS_CR_TSMX_GND	(1 << 4)
#घोषणा UCB_TS_CR_TSPX_GND	(1 << 5)
#घोषणा UCB_TS_CR_TSMY_GND	(1 << 6)
#घोषणा UCB_TS_CR_TSPY_GND	(1 << 7)
#घोषणा UCB_TS_CR_MODE_INT	(0 << 8)
#घोषणा UCB_TS_CR_MODE_PRES	(1 << 8)
#घोषणा UCB_TS_CR_MODE_POS	(2 << 8)
#घोषणा UCB_TS_CR_BIAS_ENA	(1 << 11)
#घोषणा UCB_TS_CR_TSPX_LOW	(1 << 12)
#घोषणा UCB_TS_CR_TSMX_LOW	(1 << 13)

#घोषणा UCB_ADC_CR	0x0a
#घोषणा UCB_ADC_SYNC_ENA	(1 << 0)
#घोषणा UCB_ADC_VREFBYP_CON	(1 << 1)
#घोषणा UCB_ADC_INP_TSPX	(0 << 2)
#घोषणा UCB_ADC_INP_TSMX	(1 << 2)
#घोषणा UCB_ADC_INP_TSPY	(2 << 2)
#घोषणा UCB_ADC_INP_TSMY	(3 << 2)
#घोषणा UCB_ADC_INP_AD0		(4 << 2)
#घोषणा UCB_ADC_INP_AD1		(5 << 2)
#घोषणा UCB_ADC_INP_AD2		(6 << 2)
#घोषणा UCB_ADC_INP_AD3		(7 << 2)
#घोषणा UCB_ADC_EXT_REF		(1 << 5)
#घोषणा UCB_ADC_START		(1 << 7)
#घोषणा UCB_ADC_ENA		(1 << 15)

#घोषणा UCB_ADC_DATA	0x0b
#घोषणा UCB_ADC_DAT_VAL		(1 << 15)
#घोषणा UCB_ADC_DAT(x)		(((x) & 0x7fe0) >> 5)

#घोषणा UCB_ID		0x0c
#घोषणा UCB_ID_1200		0x1004
#घोषणा UCB_ID_1300		0x1005
#घोषणा UCB_ID_TC35143          0x9712

#घोषणा UCB_MODE	0x0d
#घोषणा UCB_MODE_DYN_VFLAG_ENA	(1 << 12)
#घोषणा UCB_MODE_AUD_OFF_CAN	(1 << 13)

क्रमागत ucb1x00_reset अणु
	UCB_RST_PROBE,
	UCB_RST_RESUME,
	UCB_RST_SUSPEND,
	UCB_RST_REMOVE,
	UCB_RST_PROBE_FAIL,
पूर्ण;

काष्ठा ucb1x00_plat_data अणु
	व्योम			(*reset)(क्रमागत ucb1x00_reset);
	अचिन्हित		irq_base;
	पूर्णांक			gpio_base;
	अचिन्हित		can_wakeup;
पूर्ण;

काष्ठा ucb1x00 अणु
	raw_spinlock_t		irq_lock;
	काष्ठा mcp		*mcp;
	अचिन्हित पूर्णांक		irq;
	पूर्णांक			irq_base;
	काष्ठा mutex		adc_mutex;
	spinlock_t		io_lock;
	u16			id;
	u16			io_dir;
	u16			io_out;
	u16			adc_cr;
	u16			irq_fal_enbl;
	u16			irq_ris_enbl;
	u16			irq_mask;
	u16			irq_wake;
	काष्ठा device		dev;
	काष्ठा list_head	node;
	काष्ठा list_head	devs;
	काष्ठा gpio_chip 	gpio;
पूर्ण;

काष्ठा ucb1x00_driver;

काष्ठा ucb1x00_dev अणु
	काष्ठा list_head	dev_node;
	काष्ठा list_head	drv_node;
	काष्ठा ucb1x00		*ucb;
	काष्ठा ucb1x00_driver	*drv;
	व्योम			*priv;
पूर्ण;

काष्ठा ucb1x00_driver अणु
	काष्ठा list_head	node;
	काष्ठा list_head	devs;
	पूर्णांक	(*add)(काष्ठा ucb1x00_dev *dev);
	व्योम	(*हटाओ)(काष्ठा ucb1x00_dev *dev);
	पूर्णांक	(*suspend)(काष्ठा ucb1x00_dev *dev);
	पूर्णांक	(*resume)(काष्ठा ucb1x00_dev *dev);
पूर्ण;

#घोषणा classdev_to_ucb1x00(cd)	container_of(cd, काष्ठा ucb1x00, dev)

पूर्णांक ucb1x00_रेजिस्टर_driver(काष्ठा ucb1x00_driver *);
व्योम ucb1x00_unरेजिस्टर_driver(काष्ठा ucb1x00_driver *);

/**
 *	ucb1x00_clkrate - वापस the UCB1x00 SIB घड़ी rate
 *	@ucb: UCB1x00 काष्ठाure describing chip
 *
 *	Return the SIB घड़ी rate in Hz.
 */
अटल अंतरभूत अचिन्हित पूर्णांक ucb1x00_clkrate(काष्ठा ucb1x00 *ucb)
अणु
	वापस mcp_get_sclk_rate(ucb->mcp);
पूर्ण

/**
 *	ucb1x00_enable - enable the UCB1x00 SIB घड़ी
 *	@ucb: UCB1x00 काष्ठाure describing chip
 *
 *	Enable the SIB घड़ी.  This can be called multiple बार.
 */
अटल अंतरभूत व्योम ucb1x00_enable(काष्ठा ucb1x00 *ucb)
अणु
	mcp_enable(ucb->mcp);
पूर्ण

/**
 *	ucb1x00_disable - disable the UCB1x00 SIB घड़ी
 *	@ucb: UCB1x00 काष्ठाure describing chip
 *
 *	Disable the SIB घड़ी.  The SIB घड़ी will only be disabled
 *	when the number of ucb1x00_enable calls match the number of
 *	ucb1x00_disable calls.
 */
अटल अंतरभूत व्योम ucb1x00_disable(काष्ठा ucb1x00 *ucb)
अणु
	mcp_disable(ucb->mcp);
पूर्ण

/**
 *	ucb1x00_reg_ग_लिखो - ग_लिखो a UCB1x00 रेजिस्टर
 *	@ucb: UCB1x00 काष्ठाure describing chip
 *	@reg: UCB1x00 4-bit रेजिस्टर index to ग_लिखो
 *	@val: UCB1x00 16-bit value to ग_लिखो
 *
 *	Write the UCB1x00 रेजिस्टर @reg with value @val.  The SIB
 *	घड़ी must be running क्रम this function to वापस.
 */
अटल अंतरभूत व्योम ucb1x00_reg_ग_लिखो(काष्ठा ucb1x00 *ucb, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	mcp_reg_ग_लिखो(ucb->mcp, reg, val);
पूर्ण

/**
 *	ucb1x00_reg_पढ़ो - पढ़ो a UCB1x00 रेजिस्टर
 *	@ucb: UCB1x00 काष्ठाure describing chip
 *	@reg: UCB1x00 4-bit रेजिस्टर index to ग_लिखो
 *
 *	Read the UCB1x00 रेजिस्टर @reg and वापस its value.  The SIB
 *	घड़ी must be running क्रम this function to वापस.
 */
अटल अंतरभूत अचिन्हित पूर्णांक ucb1x00_reg_पढ़ो(काष्ठा ucb1x00 *ucb, अचिन्हित पूर्णांक reg)
अणु
	वापस mcp_reg_पढ़ो(ucb->mcp, reg);
पूर्ण
/**
 *	ucb1x00_set_audio_भागisor - 
 *	@ucb: UCB1x00 काष्ठाure describing chip
 *	@भाग: SIB घड़ी भागisor
 */
अटल अंतरभूत व्योम ucb1x00_set_audio_भागisor(काष्ठा ucb1x00 *ucb, अचिन्हित पूर्णांक भाग)
अणु
	mcp_set_audio_भागisor(ucb->mcp, भाग);
पूर्ण

/**
 *	ucb1x00_set_telecom_भागisor -
 *	@ucb: UCB1x00 काष्ठाure describing chip
 *	@भाग: SIB घड़ी भागisor
 */
अटल अंतरभूत व्योम ucb1x00_set_telecom_भागisor(काष्ठा ucb1x00 *ucb, अचिन्हित पूर्णांक भाग)
अणु
	mcp_set_telecom_भागisor(ucb->mcp, भाग);
पूर्ण

व्योम ucb1x00_io_set_dir(काष्ठा ucb1x00 *ucb, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);
व्योम ucb1x00_io_ग_लिखो(काष्ठा ucb1x00 *ucb, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);
अचिन्हित पूर्णांक ucb1x00_io_पढ़ो(काष्ठा ucb1x00 *ucb);

#घोषणा UCB_NOSYNC	(0)
#घोषणा UCB_SYNC	(1)

अचिन्हित पूर्णांक ucb1x00_adc_पढ़ो(काष्ठा ucb1x00 *ucb, पूर्णांक adc_channel, पूर्णांक sync);
व्योम ucb1x00_adc_enable(काष्ठा ucb1x00 *ucb);
व्योम ucb1x00_adc_disable(काष्ठा ucb1x00 *ucb);

#पूर्ण_अगर
