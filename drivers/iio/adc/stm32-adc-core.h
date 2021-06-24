<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This file is part of STM32 ADC driver
 *
 * Copyright (C) 2016, STMicroelectronics - All Rights Reserved
 * Author: Fabrice Gasnier <fabrice.gasnier@st.com>.
 *
 */

#अगर_अघोषित __STM32_ADC_H
#घोषणा __STM32_ADC_H

/*
 * STM32 - ADC global रेजिस्टर map
 * ________________________________________________________
 * | Offset |                 Register                    |
 * --------------------------------------------------------
 * | 0x000  |                Master ADC1                  |
 * --------------------------------------------------------
 * | 0x100  |                Slave ADC2                   |
 * --------------------------------------------------------
 * | 0x200  |                Slave ADC3                   |
 * --------------------------------------------------------
 * | 0x300  |         Master & Slave common regs          |
 * --------------------------------------------------------
 */
#घोषणा STM32_ADC_MAX_ADCS		3
#घोषणा STM32_ADC_OFFSET		0x100
#घोषणा STM32_ADCX_COMN_OFFSET		0x300

/* STM32F4 - Registers क्रम each ADC instance */
#घोषणा STM32F4_ADC_SR			0x00
#घोषणा STM32F4_ADC_CR1			0x04
#घोषणा STM32F4_ADC_CR2			0x08
#घोषणा STM32F4_ADC_SMPR1		0x0C
#घोषणा STM32F4_ADC_SMPR2		0x10
#घोषणा STM32F4_ADC_HTR			0x24
#घोषणा STM32F4_ADC_LTR			0x28
#घोषणा STM32F4_ADC_SQR1		0x2C
#घोषणा STM32F4_ADC_SQR2		0x30
#घोषणा STM32F4_ADC_SQR3		0x34
#घोषणा STM32F4_ADC_JSQR		0x38
#घोषणा STM32F4_ADC_JDR1		0x3C
#घोषणा STM32F4_ADC_JDR2		0x40
#घोषणा STM32F4_ADC_JDR3		0x44
#घोषणा STM32F4_ADC_JDR4		0x48
#घोषणा STM32F4_ADC_DR			0x4C

/* STM32F4 - common रेजिस्टरs क्रम all ADC instances: 1, 2 & 3 */
#घोषणा STM32F4_ADC_CSR			(STM32_ADCX_COMN_OFFSET + 0x00)
#घोषणा STM32F4_ADC_CCR			(STM32_ADCX_COMN_OFFSET + 0x04)

/* STM32F4_ADC_SR - bit fields */
#घोषणा STM32F4_OVR			BIT(5)
#घोषणा STM32F4_STRT			BIT(4)
#घोषणा STM32F4_EOC			BIT(1)

/* STM32F4_ADC_CR1 - bit fields */
#घोषणा STM32F4_OVRIE			BIT(26)
#घोषणा STM32F4_RES_SHIFT		24
#घोषणा STM32F4_RES_MASK		GENMASK(25, 24)
#घोषणा STM32F4_SCAN			BIT(8)
#घोषणा STM32F4_EOCIE			BIT(5)

/* STM32F4_ADC_CR2 - bit fields */
#घोषणा STM32F4_SWSTART			BIT(30)
#घोषणा STM32F4_EXTEN_SHIFT		28
#घोषणा STM32F4_EXTEN_MASK		GENMASK(29, 28)
#घोषणा STM32F4_EXTSEL_SHIFT		24
#घोषणा STM32F4_EXTSEL_MASK		GENMASK(27, 24)
#घोषणा STM32F4_EOCS			BIT(10)
#घोषणा STM32F4_DDS			BIT(9)
#घोषणा STM32F4_DMA			BIT(8)
#घोषणा STM32F4_ADON			BIT(0)

/* STM32F4_ADC_CSR - bit fields */
#घोषणा STM32F4_OVR3			BIT(21)
#घोषणा STM32F4_EOC3			BIT(17)
#घोषणा STM32F4_OVR2			BIT(13)
#घोषणा STM32F4_EOC2			BIT(9)
#घोषणा STM32F4_OVR1			BIT(5)
#घोषणा STM32F4_EOC1			BIT(1)

/* STM32F4_ADC_CCR - bit fields */
#घोषणा STM32F4_ADC_ADCPRE_SHIFT	16
#घोषणा STM32F4_ADC_ADCPRE_MASK		GENMASK(17, 16)

/* STM32H7 - Registers क्रम each ADC instance */
#घोषणा STM32H7_ADC_ISR			0x00
#घोषणा STM32H7_ADC_IER			0x04
#घोषणा STM32H7_ADC_CR			0x08
#घोषणा STM32H7_ADC_CFGR		0x0C
#घोषणा STM32H7_ADC_SMPR1		0x14
#घोषणा STM32H7_ADC_SMPR2		0x18
#घोषणा STM32H7_ADC_PCSEL		0x1C
#घोषणा STM32H7_ADC_SQR1		0x30
#घोषणा STM32H7_ADC_SQR2		0x34
#घोषणा STM32H7_ADC_SQR3		0x38
#घोषणा STM32H7_ADC_SQR4		0x3C
#घोषणा STM32H7_ADC_DR			0x40
#घोषणा STM32H7_ADC_DIFSEL		0xC0
#घोषणा STM32H7_ADC_CALFACT		0xC4
#घोषणा STM32H7_ADC_CALFACT2		0xC8

/* STM32H7 - common रेजिस्टरs क्रम all ADC instances */
#घोषणा STM32H7_ADC_CSR			(STM32_ADCX_COMN_OFFSET + 0x00)
#घोषणा STM32H7_ADC_CCR			(STM32_ADCX_COMN_OFFSET + 0x08)

/* STM32H7_ADC_ISR - bit fields */
#घोषणा STM32MP1_VREGREADY		BIT(12)
#घोषणा STM32H7_OVR			BIT(4)
#घोषणा STM32H7_EOC			BIT(2)
#घोषणा STM32H7_ADRDY			BIT(0)

/* STM32H7_ADC_IER - bit fields */
#घोषणा STM32H7_OVRIE			STM32H7_OVR
#घोषणा STM32H7_EOCIE			STM32H7_EOC

/* STM32H7_ADC_CR - bit fields */
#घोषणा STM32H7_ADCAL			BIT(31)
#घोषणा STM32H7_ADCALDIF		BIT(30)
#घोषणा STM32H7_DEEPPWD			BIT(29)
#घोषणा STM32H7_ADVREGEN		BIT(28)
#घोषणा STM32H7_LINCALRDYW6		BIT(27)
#घोषणा STM32H7_LINCALRDYW5		BIT(26)
#घोषणा STM32H7_LINCALRDYW4		BIT(25)
#घोषणा STM32H7_LINCALRDYW3		BIT(24)
#घोषणा STM32H7_LINCALRDYW2		BIT(23)
#घोषणा STM32H7_LINCALRDYW1		BIT(22)
#घोषणा STM32H7_ADCALLIN		BIT(16)
#घोषणा STM32H7_BOOST			BIT(8)
#घोषणा STM32H7_ADSTP			BIT(4)
#घोषणा STM32H7_ADSTART			BIT(2)
#घोषणा STM32H7_ADDIS			BIT(1)
#घोषणा STM32H7_ADEN			BIT(0)

/* STM32H7_ADC_CFGR bit fields */
#घोषणा STM32H7_EXTEN_SHIFT		10
#घोषणा STM32H7_EXTEN_MASK		GENMASK(11, 10)
#घोषणा STM32H7_EXTSEL_SHIFT		5
#घोषणा STM32H7_EXTSEL_MASK		GENMASK(9, 5)
#घोषणा STM32H7_RES_SHIFT		2
#घोषणा STM32H7_RES_MASK		GENMASK(4, 2)
#घोषणा STM32H7_DMNGT_SHIFT		0
#घोषणा STM32H7_DMNGT_MASK		GENMASK(1, 0)

क्रमागत sपंचांग32h7_adc_dmngt अणु
	STM32H7_DMNGT_DR_ONLY,		/* Regular data in DR only */
	STM32H7_DMNGT_DMA_ONESHOT,	/* DMA one shot mode */
	STM32H7_DMNGT_DFSDM,		/* DFSDM mode */
	STM32H7_DMNGT_DMA_CIRC,		/* DMA circular mode */
पूर्ण;

/* STM32H7_ADC_CALFACT - bit fields */
#घोषणा STM32H7_CALFACT_D_SHIFT		16
#घोषणा STM32H7_CALFACT_D_MASK		GENMASK(26, 16)
#घोषणा STM32H7_CALFACT_S_SHIFT		0
#घोषणा STM32H7_CALFACT_S_MASK		GENMASK(10, 0)

/* STM32H7_ADC_CALFACT2 - bit fields */
#घोषणा STM32H7_LINCALFACT_SHIFT	0
#घोषणा STM32H7_LINCALFACT_MASK		GENMASK(29, 0)

/* STM32H7_ADC_CSR - bit fields */
#घोषणा STM32H7_OVR_SLV			BIT(20)
#घोषणा STM32H7_EOC_SLV			BIT(18)
#घोषणा STM32H7_OVR_MST			BIT(4)
#घोषणा STM32H7_EOC_MST			BIT(2)

/* STM32H7_ADC_CCR - bit fields */
#घोषणा STM32H7_PRESC_SHIFT		18
#घोषणा STM32H7_PRESC_MASK		GENMASK(21, 18)
#घोषणा STM32H7_CKMODE_SHIFT		16
#घोषणा STM32H7_CKMODE_MASK		GENMASK(17, 16)

/**
 * काष्ठा sपंचांग32_adc_common - sपंचांग32 ADC driver common data (क्रम all instances)
 * @base:		control रेजिस्टरs base cpu addr
 * @phys_base:		control रेजिस्टरs base physical addr
 * @rate:		घड़ी rate used क्रम analog circuitry
 * @vref_mv:		vref voltage (mv)
 */
काष्ठा sपंचांग32_adc_common अणु
	व्योम __iomem			*base;
	phys_addr_t			phys_base;
	अचिन्हित दीर्घ			rate;
	पूर्णांक				vref_mv;
पूर्ण;

#पूर्ण_अगर
