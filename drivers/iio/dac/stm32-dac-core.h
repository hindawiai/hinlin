<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This file is part of STM32 DAC driver
 *
 * Copyright (C) 2017, STMicroelectronics - All Rights Reserved
 * Author: Fabrice Gasnier <fabrice.gasnier@st.com>.
 */

#अगर_अघोषित __STM32_DAC_CORE_H
#घोषणा __STM32_DAC_CORE_H

#समावेश <linux/regmap.h>

/* STM32 DAC रेजिस्टरs */
#घोषणा STM32_DAC_CR		0x00
#घोषणा STM32_DAC_DHR12R1	0x08
#घोषणा STM32_DAC_DHR12R2	0x14
#घोषणा STM32_DAC_DOR1		0x2C
#घोषणा STM32_DAC_DOR2		0x30

/* STM32_DAC_CR bit fields */
#घोषणा STM32_DAC_CR_EN1		BIT(0)
#घोषणा STM32H7_DAC_CR_HFSEL		BIT(15)
#घोषणा STM32_DAC_CR_EN2		BIT(16)

/**
 * काष्ठा sपंचांग32_dac_common - sपंचांग32 DAC driver common data (क्रम all instances)
 * @regmap: DAC रेजिस्टरs shared via regmap
 * @vref_mv: reference voltage (mv)
 * @hfsel: high speed bus घड़ी selected
 */
काष्ठा sपंचांग32_dac_common अणु
	काष्ठा regmap			*regmap;
	पूर्णांक				vref_mv;
	bool				hfsel;
पूर्ण;

#पूर्ण_अगर
