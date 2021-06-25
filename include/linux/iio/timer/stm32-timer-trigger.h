<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) STMicroelectronics 2016
 *
 * Author: Benjamin Gaignard <benjamin.gaignard@st.com>
 */

#अगर_अघोषित _STM32_TIMER_TRIGGER_H_
#घोषणा _STM32_TIMER_TRIGGER_H_

#घोषणा TIM1_TRGO	"tim1_trgo"
#घोषणा TIM1_TRGO2	"tim1_trgo2"
#घोषणा TIM1_CH1	"tim1_ch1"
#घोषणा TIM1_CH2	"tim1_ch2"
#घोषणा TIM1_CH3	"tim1_ch3"
#घोषणा TIM1_CH4	"tim1_ch4"

#घोषणा TIM2_TRGO	"tim2_trgo"
#घोषणा TIM2_CH1	"tim2_ch1"
#घोषणा TIM2_CH2	"tim2_ch2"
#घोषणा TIM2_CH3	"tim2_ch3"
#घोषणा TIM2_CH4	"tim2_ch4"

#घोषणा TIM3_TRGO	"tim3_trgo"
#घोषणा TIM3_CH1	"tim3_ch1"
#घोषणा TIM3_CH2	"tim3_ch2"
#घोषणा TIM3_CH3	"tim3_ch3"
#घोषणा TIM3_CH4	"tim3_ch4"

#घोषणा TIM4_TRGO	"tim4_trgo"
#घोषणा TIM4_CH1	"tim4_ch1"
#घोषणा TIM4_CH2	"tim4_ch2"
#घोषणा TIM4_CH3	"tim4_ch3"
#घोषणा TIM4_CH4	"tim4_ch4"

#घोषणा TIM5_TRGO	"tim5_trgo"
#घोषणा TIM5_CH1	"tim5_ch1"
#घोषणा TIM5_CH2	"tim5_ch2"
#घोषणा TIM5_CH3	"tim5_ch3"
#घोषणा TIM5_CH4	"tim5_ch4"

#घोषणा TIM6_TRGO	"tim6_trgo"

#घोषणा TIM7_TRGO	"tim7_trgo"

#घोषणा TIM8_TRGO	"tim8_trgo"
#घोषणा TIM8_TRGO2	"tim8_trgo2"
#घोषणा TIM8_CH1	"tim8_ch1"
#घोषणा TIM8_CH2	"tim8_ch2"
#घोषणा TIM8_CH3	"tim8_ch3"
#घोषणा TIM8_CH4	"tim8_ch4"

#घोषणा TIM9_TRGO	"tim9_trgo"
#घोषणा TIM9_CH1	"tim9_ch1"
#घोषणा TIM9_CH2	"tim9_ch2"

#घोषणा TIM10_OC1	"tim10_oc1"

#घोषणा TIM11_OC1	"tim11_oc1"

#घोषणा TIM12_TRGO	"tim12_trgo"
#घोषणा TIM12_CH1	"tim12_ch1"
#घोषणा TIM12_CH2	"tim12_ch2"

#घोषणा TIM13_OC1	"tim13_oc1"

#घोषणा TIM14_OC1	"tim14_oc1"

#घोषणा TIM15_TRGO	"tim15_trgo"

#घोषणा TIM16_OC1	"tim16_oc1"

#घोषणा TIM17_OC1	"tim17_oc1"

#अगर IS_REACHABLE(CONFIG_IIO_STM32_TIMER_TRIGGER)
bool is_sपंचांग32_समयr_trigger(काष्ठा iio_trigger *trig);
#अन्यथा
अटल अंतरभूत bool is_sपंचांग32_समयr_trigger(काष्ठा iio_trigger *trig)
अणु
#अगर IS_ENABLED(CONFIG_IIO_STM32_TIMER_TRIGGER)
	pr_warn_once("stm32-timer-trigger not linked in\n");
#पूर्ण_अगर
	वापस false;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
