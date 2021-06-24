<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2009 Daniel Ribeiro <drwyrm@gmail.com>
 *
 * For further inक्रमmation, please see http://wiki.खोलोezx.org/PCAP2
 */

#अगर_अघोषित EZX_PCAP_H
#घोषणा EZX_PCAP_H

काष्ठा pcap_subdev अणु
	पूर्णांक id;
	स्थिर अक्षर *name;
	व्योम *platक्रमm_data;
पूर्ण;

काष्ठा pcap_platक्रमm_data अणु
	अचिन्हित पूर्णांक irq_base;
	अचिन्हित पूर्णांक config;
	पूर्णांक gpio;
	व्योम (*init) (व्योम *);	/* board specअगरic init */
	पूर्णांक num_subdevs;
	काष्ठा pcap_subdev *subdevs;
पूर्ण;

काष्ठा pcap_chip;

पूर्णांक ezx_pcap_ग_लिखो(काष्ठा pcap_chip *, u8, u32);
पूर्णांक ezx_pcap_पढ़ो(काष्ठा pcap_chip *, u8, u32 *);
पूर्णांक ezx_pcap_set_bits(काष्ठा pcap_chip *, u8, u32, u32);
पूर्णांक pcap_to_irq(काष्ठा pcap_chip *, पूर्णांक);
पूर्णांक irq_to_pcap(काष्ठा pcap_chip *, पूर्णांक);
पूर्णांक pcap_adc_async(काष्ठा pcap_chip *, u8, u32, u8[], व्योम *, व्योम *);
पूर्णांक pcap_adc_sync(काष्ठा pcap_chip *, u8, u32, u8[], u16[]);
व्योम pcap_set_ts_bits(काष्ठा pcap_chip *, u32);

#घोषणा PCAP_SECOND_PORT	1
#घोषणा PCAP_CS_AH		2

#घोषणा PCAP_REGISTER_WRITE_OP_BIT	0x80000000
#घोषणा PCAP_REGISTER_READ_OP_BIT	0x00000000

#घोषणा PCAP_REGISTER_VALUE_MASK	0x01ffffff
#घोषणा PCAP_REGISTER_ADDRESS_MASK	0x7c000000
#घोषणा PCAP_REGISTER_ADDRESS_SHIFT	26
#घोषणा PCAP_REGISTER_NUMBER		32
#घोषणा PCAP_CLEAR_INTERRUPT_REGISTER	0x01ffffff
#घोषणा PCAP_MASK_ALL_INTERRUPT		0x01ffffff

/* रेजिस्टरs accessible by both pcap ports */
#घोषणा PCAP_REG_ISR		0x0	/* Interrupt Status */
#घोषणा PCAP_REG_MSR		0x1	/* Interrupt Mask */
#घोषणा PCAP_REG_PSTAT		0x2	/* Processor Status */
#घोषणा PCAP_REG_VREG2		0x6	/* Regulator Bank 2 Control */
#घोषणा PCAP_REG_AUXVREG	0x7	/* Auxiliary Regulator Control */
#घोषणा PCAP_REG_BATT		0x8	/* Battery Control */
#घोषणा PCAP_REG_ADC		0x9	/* AD Control */
#घोषणा PCAP_REG_ADR		0xa	/* AD Result */
#घोषणा PCAP_REG_CODEC		0xb	/* Audio Codec Control */
#घोषणा PCAP_REG_RX_AMPS	0xc	/* RX Audio Amplअगरiers Control */
#घोषणा PCAP_REG_ST_DAC		0xd	/* Stereo DAC Control */
#घोषणा PCAP_REG_BUSCTRL	0x14	/* Connectivity Control */
#घोषणा PCAP_REG_PERIPH		0x15	/* Peripheral Control */
#घोषणा PCAP_REG_LOWPWR		0x18	/* Regulator Low Power Control */
#घोषणा PCAP_REG_TX_AMPS	0x1a	/* TX Audio Amplअगरiers Control */
#घोषणा PCAP_REG_GP		0x1b	/* General Purpose */
#घोषणा PCAP_REG_TEST1		0x1c
#घोषणा PCAP_REG_TEST2		0x1d
#घोषणा PCAP_REG_VENDOR_TEST1	0x1e
#घोषणा PCAP_REG_VENDOR_TEST2	0x1f

/* रेजिस्टरs accessible by pcap port 1 only (a1200, e2 & e6) */
#घोषणा PCAP_REG_INT_SEL	0x3	/* Interrupt Select */
#घोषणा PCAP_REG_SWCTRL		0x4	/* Switching Regulator Control */
#घोषणा PCAP_REG_VREG1		0x5	/* Regulator Bank 1 Control */
#घोषणा PCAP_REG_RTC_TOD	0xe	/* RTC Time of Day */
#घोषणा PCAP_REG_RTC_TODA	0xf	/* RTC Time of Day Alarm */
#घोषणा PCAP_REG_RTC_DAY	0x10	/* RTC Day */
#घोषणा PCAP_REG_RTC_DAYA	0x11	/* RTC Day Alarm */
#घोषणा PCAP_REG_MTRTMR		0x12	/* AD Monitor Timer */
#घोषणा PCAP_REG_PWR		0x13	/* Power Control */
#घोषणा PCAP_REG_AUXVREG_MASK	0x16	/* Auxiliary Regulator Mask */
#घोषणा PCAP_REG_VENDOR_REV	0x17
#घोषणा PCAP_REG_PERIPH_MASK	0x19	/* Peripheral Mask */

/* PCAP2 Interrupts */
#घोषणा PCAP_NIRQS		23
#घोषणा PCAP_IRQ_ADCDONE	0	/* ADC करोne port 1 */
#घोषणा PCAP_IRQ_TS		1	/* Touch Screen */
#घोषणा PCAP_IRQ_1HZ		2	/* 1HZ समयr */
#घोषणा PCAP_IRQ_WH		3	/* ADC above high limit */
#घोषणा PCAP_IRQ_WL		4	/* ADC below low limit */
#घोषणा PCAP_IRQ_TODA		5	/* Time of day alarm */
#घोषणा PCAP_IRQ_USB4V		6	/* USB above 4V */
#घोषणा PCAP_IRQ_ONOFF		7	/* On/Off button */
#घोषणा PCAP_IRQ_ONOFF2		8	/* On/Off button 2 */
#घोषणा PCAP_IRQ_USB1V		9	/* USB above 1V */
#घोषणा PCAP_IRQ_MOBPORT	10
#घोषणा PCAP_IRQ_MIC		11	/* Mic attach/HS button */
#घोषणा PCAP_IRQ_HS		12	/* Headset attach */
#घोषणा PCAP_IRQ_ST		13
#घोषणा PCAP_IRQ_PC		14	/* Power Cut */
#घोषणा PCAP_IRQ_WARM		15
#घोषणा PCAP_IRQ_EOL		16	/* Battery End Of Lअगरe */
#घोषणा PCAP_IRQ_CLK		17
#घोषणा PCAP_IRQ_SYSRST		18	/* System Reset */
#घोषणा PCAP_IRQ_DUMMY		19
#घोषणा PCAP_IRQ_ADCDONE2	20	/* ADC करोne port 2 */
#घोषणा PCAP_IRQ_SOFTRESET	21
#घोषणा PCAP_IRQ_MNEXB		22

/* voltage regulators */
#घोषणा V1		0
#घोषणा V2		1
#घोषणा V3		2
#घोषणा V4		3
#घोषणा V5		4
#घोषणा V6		5
#घोषणा V7		6
#घोषणा V8		7
#घोषणा V9		8
#घोषणा V10		9
#घोषणा VAUX1		10
#घोषणा VAUX2		11
#घोषणा VAUX3		12
#घोषणा VAUX4		13
#घोषणा VSIM		14
#घोषणा VSIM2		15
#घोषणा VVIB		16
#घोषणा SW1		17
#घोषणा SW2		18
#घोषणा SW3		19
#घोषणा SW1S		20
#घोषणा SW2S		21

#घोषणा PCAP_BATT_DAC_MASK		0x000000ff
#घोषणा PCAP_BATT_DAC_SHIFT		0
#घोषणा PCAP_BATT_B_FDBK		(1 << 8)
#घोषणा PCAP_BATT_EXT_ISENSE		(1 << 9)
#घोषणा PCAP_BATT_V_COIN_MASK		0x00003c00
#घोषणा PCAP_BATT_V_COIN_SHIFT		10
#घोषणा PCAP_BATT_I_COIN		(1 << 14)
#घोषणा PCAP_BATT_COIN_CH_EN		(1 << 15)
#घोषणा PCAP_BATT_EOL_SEL_MASK		0x000e0000
#घोषणा PCAP_BATT_EOL_SEL_SHIFT		17
#घोषणा PCAP_BATT_EOL_CMP_EN		(1 << 20)
#घोषणा PCAP_BATT_BATT_DET_EN		(1 << 21)
#घोषणा PCAP_BATT_THERMBIAS_CTRL	(1 << 22)

#घोषणा PCAP_ADC_ADEN			(1 << 0)
#घोषणा PCAP_ADC_RAND			(1 << 1)
#घोषणा PCAP_ADC_AD_SEL1		(1 << 2)
#घोषणा PCAP_ADC_AD_SEL2		(1 << 3)
#घोषणा PCAP_ADC_ADA1_MASK		0x00000070
#घोषणा PCAP_ADC_ADA1_SHIFT		4
#घोषणा PCAP_ADC_ADA2_MASK		0x00000380
#घोषणा PCAP_ADC_ADA2_SHIFT		7
#घोषणा PCAP_ADC_ATO_MASK		0x00003c00
#घोषणा PCAP_ADC_ATO_SHIFT		10
#घोषणा PCAP_ADC_ATOX			(1 << 14)
#घोषणा PCAP_ADC_MTR1			(1 << 15)
#घोषणा PCAP_ADC_MTR2			(1 << 16)
#घोषणा PCAP_ADC_TS_M_MASK		0x000e0000
#घोषणा PCAP_ADC_TS_M_SHIFT		17
#घोषणा PCAP_ADC_TS_REF_LOWPWR		(1 << 20)
#घोषणा PCAP_ADC_TS_REFENB		(1 << 21)
#घोषणा PCAP_ADC_BATT_I_POLARITY	(1 << 22)
#घोषणा PCAP_ADC_BATT_I_ADC		(1 << 23)

#घोषणा PCAP_ADC_BANK_0			0
#घोषणा PCAP_ADC_BANK_1			1
/* ADC bank 0 */
#घोषणा PCAP_ADC_CH_COIN		0
#घोषणा PCAP_ADC_CH_BATT		1
#घोषणा PCAP_ADC_CH_BPLUS		2
#घोषणा PCAP_ADC_CH_MOBPORTB		3
#घोषणा PCAP_ADC_CH_TEMPERATURE		4
#घोषणा PCAP_ADC_CH_CHARGER_ID		5
#घोषणा PCAP_ADC_CH_AD6			6
/* ADC bank 1 */
#घोषणा PCAP_ADC_CH_AD7			0
#घोषणा PCAP_ADC_CH_AD8			1
#घोषणा PCAP_ADC_CH_AD9			2
#घोषणा PCAP_ADC_CH_TS_X1		3
#घोषणा PCAP_ADC_CH_TS_X2		4
#घोषणा PCAP_ADC_CH_TS_Y1		5
#घोषणा PCAP_ADC_CH_TS_Y2		6

#घोषणा PCAP_ADC_T_NOW			0
#घोषणा PCAP_ADC_T_IN_BURST		1
#घोषणा PCAP_ADC_T_OUT_BURST		2

#घोषणा PCAP_ADC_ATO_IN_BURST		6
#घोषणा PCAP_ADC_ATO_OUT_BURST		0

#घोषणा PCAP_ADC_TS_M_XY		1
#घोषणा PCAP_ADC_TS_M_PRESSURE		2
#घोषणा PCAP_ADC_TS_M_PLATE_X		3
#घोषणा PCAP_ADC_TS_M_PLATE_Y		4
#घोषणा PCAP_ADC_TS_M_STANDBY		5
#घोषणा PCAP_ADC_TS_M_NONTS		6

#घोषणा PCAP_ADR_ADD1_MASK		0x000003ff
#घोषणा PCAP_ADR_ADD1_SHIFT		0
#घोषणा PCAP_ADR_ADD2_MASK		0x000ffc00
#घोषणा PCAP_ADR_ADD2_SHIFT		10
#घोषणा PCAP_ADR_ADINC1			(1 << 20)
#घोषणा PCAP_ADR_ADINC2			(1 << 21)
#घोषणा PCAP_ADR_ASC			(1 << 22)
#घोषणा PCAP_ADR_ONESHOT		(1 << 23)

#घोषणा PCAP_BUSCTRL_FSENB		(1 << 0)
#घोषणा PCAP_BUSCTRL_USB_SUSPEND	(1 << 1)
#घोषणा PCAP_BUSCTRL_USB_PU		(1 << 2)
#घोषणा PCAP_BUSCTRL_USB_PD		(1 << 3)
#घोषणा PCAP_BUSCTRL_VUSB_EN		(1 << 4)
#घोषणा PCAP_BUSCTRL_USB_PS		(1 << 5)
#घोषणा PCAP_BUSCTRL_VUSB_MSTR_EN	(1 << 6)
#घोषणा PCAP_BUSCTRL_VBUS_PD_ENB	(1 << 7)
#घोषणा PCAP_BUSCTRL_CURRLIM		(1 << 8)
#घोषणा PCAP_BUSCTRL_RS232ENB		(1 << 9)
#घोषणा PCAP_BUSCTRL_RS232_सूची		(1 << 10)
#घोषणा PCAP_BUSCTRL_SE0_CONN		(1 << 11)
#घोषणा PCAP_BUSCTRL_USB_PDM		(1 << 12)
#घोषणा PCAP_BUSCTRL_BUS_PRI_ADJ	(1 << 24)

/* leds */
#घोषणा PCAP_LED0		0
#घोषणा PCAP_LED1		1
#घोषणा PCAP_BL0		2
#घोषणा PCAP_BL1		3
#घोषणा PCAP_LED_3MA		0
#घोषणा PCAP_LED_4MA		1
#घोषणा PCAP_LED_5MA		2
#घोषणा PCAP_LED_9MA		3
#घोषणा PCAP_LED_T_MASK		0xf
#घोषणा PCAP_LED_C_MASK		0x3
#घोषणा PCAP_BL_MASK		0x1f
#घोषणा PCAP_BL0_SHIFT		0
#घोषणा PCAP_LED0_EN		(1 << 5)
#घोषणा PCAP_LED1_EN		(1 << 6)
#घोषणा PCAP_LED0_T_SHIFT	7
#घोषणा PCAP_LED1_T_SHIFT	11
#घोषणा PCAP_LED0_C_SHIFT	15
#घोषणा PCAP_LED1_C_SHIFT	17
#घोषणा PCAP_BL1_SHIFT		20

/* RTC */
#घोषणा PCAP_RTC_DAY_MASK	0x3fff
#घोषणा PCAP_RTC_TOD_MASK	0xffff
#घोषणा PCAP_RTC_PC_MASK	0x7
#घोषणा SEC_PER_DAY		86400

#पूर्ण_अगर
