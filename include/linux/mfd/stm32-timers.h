<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) STMicroelectronics 2016
 * Author: Benjamin Gaignard <benjamin.gaignard@st.com>
 */

#अगर_अघोषित _LINUX_STM32_GPTIMER_H_
#घोषणा _LINUX_STM32_GPTIMER_H_

#समावेश <linux/clk.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/regmap.h>

#घोषणा TIM_CR1		0x00	/* Control Register 1      */
#घोषणा TIM_CR2		0x04	/* Control Register 2      */
#घोषणा TIM_SMCR	0x08	/* Slave mode control reg  */
#घोषणा TIM_DIER	0x0C	/* DMA/पूर्णांकerrupt रेजिस्टर  */
#घोषणा TIM_SR		0x10	/* Status रेजिस्टर	   */
#घोषणा TIM_EGR		0x14	/* Event Generation Reg    */
#घोषणा TIM_CCMR1	0x18	/* Capt/Comp 1 Mode Reg    */
#घोषणा TIM_CCMR2	0x1C	/* Capt/Comp 2 Mode Reg    */
#घोषणा TIM_CCER	0x20	/* Capt/Comp Enable Reg    */
#घोषणा TIM_CNT		0x24	/* Counter		   */
#घोषणा TIM_PSC		0x28	/* Prescaler               */
#घोषणा TIM_ARR		0x2c	/* Auto-Reload Register    */
#घोषणा TIM_CCR1	0x34	/* Capt/Comp Register 1    */
#घोषणा TIM_CCR2	0x38	/* Capt/Comp Register 2    */
#घोषणा TIM_CCR3	0x3C	/* Capt/Comp Register 3    */
#घोषणा TIM_CCR4	0x40	/* Capt/Comp Register 4    */
#घोषणा TIM_BDTR	0x44	/* Break and Dead-Time Reg */
#घोषणा TIM_DCR		0x48	/* DMA control रेजिस्टर    */
#घोषणा TIM_DMAR	0x4C	/* DMA रेजिस्टर क्रम transfer */

#घोषणा TIM_CR1_CEN	BIT(0)	/* Counter Enable	   */
#घोषणा TIM_CR1_सूची	BIT(4)  /* Counter Direction	   */
#घोषणा TIM_CR1_ARPE	BIT(7)	/* Auto-reload Preload Ena */
#घोषणा TIM_CR2_MMS	(BIT(4) | BIT(5) | BIT(6)) /* Master mode selection */
#घोषणा TIM_CR2_MMS2	GENMASK(23, 20) /* Master mode selection 2 */
#घोषणा TIM_SMCR_SMS	(BIT(0) | BIT(1) | BIT(2)) /* Slave mode selection */
#घोषणा TIM_SMCR_TS	(BIT(4) | BIT(5) | BIT(6)) /* Trigger selection */
#घोषणा TIM_DIER_UIE	BIT(0)	/* Update पूर्णांकerrupt	   */
#घोषणा TIM_DIER_UDE	BIT(8)  /* Update DMA request Enable */
#घोषणा TIM_DIER_CC1DE	BIT(9)  /* CC1 DMA request Enable  */
#घोषणा TIM_DIER_CC2DE	BIT(10) /* CC2 DMA request Enable  */
#घोषणा TIM_DIER_CC3DE	BIT(11) /* CC3 DMA request Enable  */
#घोषणा TIM_DIER_CC4DE	BIT(12) /* CC4 DMA request Enable  */
#घोषणा TIM_DIER_COMDE	BIT(13) /* COM DMA request Enable  */
#घोषणा TIM_DIER_TDE	BIT(14) /* Trigger DMA request Enable */
#घोषणा TIM_SR_UIF	BIT(0)	/* Update पूर्णांकerrupt flag   */
#घोषणा TIM_EGR_UG	BIT(0)	/* Update Generation       */
#घोषणा TIM_CCMR_PE	BIT(3)	/* Channel Preload Enable  */
#घोषणा TIM_CCMR_M1	(BIT(6) | BIT(5))  /* Channel PWM Mode 1 */
#घोषणा TIM_CCMR_CC1S		(BIT(0) | BIT(1)) /* Capture/compare 1 sel */
#घोषणा TIM_CCMR_IC1PSC		GENMASK(3, 2)	/* Input capture 1 prescaler */
#घोषणा TIM_CCMR_CC2S		(BIT(8) | BIT(9)) /* Capture/compare 2 sel */
#घोषणा TIM_CCMR_IC2PSC		GENMASK(11, 10)	/* Input capture 2 prescaler */
#घोषणा TIM_CCMR_CC1S_TI1	BIT(0)	/* IC1/IC3 selects TI1/TI3 */
#घोषणा TIM_CCMR_CC1S_TI2	BIT(1)	/* IC1/IC3 selects TI2/TI4 */
#घोषणा TIM_CCMR_CC2S_TI2	BIT(8)	/* IC2/IC4 selects TI2/TI4 */
#घोषणा TIM_CCMR_CC2S_TI1	BIT(9)	/* IC2/IC4 selects TI1/TI3 */
#घोषणा TIM_CCER_CC1E	BIT(0)	/* Capt/Comp 1  out Ena    */
#घोषणा TIM_CCER_CC1P	BIT(1)	/* Capt/Comp 1  Polarity   */
#घोषणा TIM_CCER_CC1NE	BIT(2)	/* Capt/Comp 1N out Ena    */
#घोषणा TIM_CCER_CC1NP	BIT(3)	/* Capt/Comp 1N Polarity   */
#घोषणा TIM_CCER_CC2E	BIT(4)	/* Capt/Comp 2  out Ena    */
#घोषणा TIM_CCER_CC2P	BIT(5)	/* Capt/Comp 2  Polarity   */
#घोषणा TIM_CCER_CC3E	BIT(8)	/* Capt/Comp 3  out Ena    */
#घोषणा TIM_CCER_CC3P	BIT(9)	/* Capt/Comp 3  Polarity   */
#घोषणा TIM_CCER_CC4E	BIT(12)	/* Capt/Comp 4  out Ena    */
#घोषणा TIM_CCER_CC4P	BIT(13)	/* Capt/Comp 4  Polarity   */
#घोषणा TIM_CCER_CCXE	(BIT(0) | BIT(4) | BIT(8) | BIT(12))
#घोषणा TIM_BDTR_BKE(x)	BIT(12 + (x) * 12) /* Break input enable */
#घोषणा TIM_BDTR_BKP(x)	BIT(13 + (x) * 12) /* Break input polarity */
#घोषणा TIM_BDTR_AOE	BIT(14)	/* Automatic Output Enable */
#घोषणा TIM_BDTR_MOE	BIT(15)	/* Main Output Enable      */
#घोषणा TIM_BDTR_BKF(x)	(0xf << (16 + (x) * 4))
#घोषणा TIM_DCR_DBA	GENMASK(4, 0)	/* DMA base addr */
#घोषणा TIM_DCR_DBL	GENMASK(12, 8)	/* DMA burst len */

#घोषणा MAX_TIM_PSC		0xFFFF
#घोषणा MAX_TIM_ICPSC		0x3
#घोषणा TIM_CR2_MMS_SHIFT	4
#घोषणा TIM_CR2_MMS2_SHIFT	20
#घोषणा TIM_SMCR_TS_SHIFT	4
#घोषणा TIM_BDTR_BKF_MASK	0xF
#घोषणा TIM_BDTR_BKF_SHIFT(x)	(16 + (x) * 4)

क्रमागत sपंचांग32_समयrs_dmas अणु
	STM32_TIMERS_DMA_CH1,
	STM32_TIMERS_DMA_CH2,
	STM32_TIMERS_DMA_CH3,
	STM32_TIMERS_DMA_CH4,
	STM32_TIMERS_DMA_UP,
	STM32_TIMERS_DMA_TRIG,
	STM32_TIMERS_DMA_COM,
	STM32_TIMERS_MAX_DMAS,
पूर्ण;

/**
 * काष्ठा sपंचांग32_समयrs_dma - STM32 समयr DMA handling.
 * @completion:		end of DMA transfer completion
 * @phys_base:		control रेजिस्टरs physical base address
 * @lock:		protect DMA access
 * @chan:		DMA channel in use
 * @chans:		DMA channels available क्रम this समयr instance
 */
काष्ठा sपंचांग32_समयrs_dma अणु
	काष्ठा completion completion;
	phys_addr_t phys_base;
	काष्ठा mutex lock;
	काष्ठा dma_chan *chan;
	काष्ठा dma_chan *chans[STM32_TIMERS_MAX_DMAS];
पूर्ण;

काष्ठा sपंचांग32_समयrs अणु
	काष्ठा clk *clk;
	काष्ठा regmap *regmap;
	u32 max_arr;
	काष्ठा sपंचांग32_समयrs_dma dma; /* Only to be used by the parent */
पूर्ण;

#अगर IS_REACHABLE(CONFIG_MFD_STM32_TIMERS)
पूर्णांक sपंचांग32_समयrs_dma_burst_पढ़ो(काष्ठा device *dev, u32 *buf,
				क्रमागत sपंचांग32_समयrs_dmas id, u32 reg,
				अचिन्हित पूर्णांक num_reg, अचिन्हित पूर्णांक bursts,
				अचिन्हित दीर्घ पंचांगo_ms);
#अन्यथा
अटल अंतरभूत पूर्णांक sपंचांग32_समयrs_dma_burst_पढ़ो(काष्ठा device *dev, u32 *buf,
					      क्रमागत sपंचांग32_समयrs_dmas id,
					      u32 reg,
					      अचिन्हित पूर्णांक num_reg,
					      अचिन्हित पूर्णांक bursts,
					      अचिन्हित दीर्घ पंचांगo_ms)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
