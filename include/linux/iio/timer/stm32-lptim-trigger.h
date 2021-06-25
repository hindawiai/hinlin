<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) STMicroelectronics 2017
 *
 * Author: Fabrice Gasnier <fabrice.gasnier@st.com>
 */

#अगर_अघोषित _STM32_LPTIM_TRIGGER_H_
#घोषणा _STM32_LPTIM_TRIGGER_H_

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/trigger.h>

#घोषणा LPTIM1_OUT	"lptim1_out"
#घोषणा LPTIM2_OUT	"lptim2_out"
#घोषणा LPTIM3_OUT	"lptim3_out"

#अगर IS_REACHABLE(CONFIG_IIO_STM32_LPTIMER_TRIGGER)
bool is_sपंचांग32_lptim_trigger(काष्ठा iio_trigger *trig);
#अन्यथा
अटल अंतरभूत bool is_sपंचांग32_lptim_trigger(काष्ठा iio_trigger *trig)
अणु
#अगर IS_ENABLED(CONFIG_IIO_STM32_LPTIMER_TRIGGER)
	pr_warn_once("stm32 lptim_trigger not linked in\n");
#पूर्ण_अगर
	वापस false;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
