<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * STM32 Low-Power Timer parent driver.
 * Copyright (C) STMicroelectronics 2017
 * Author: Fabrice Gasnier <fabrice.gasnier@st.com>
 * Inspired by Benjamin Gaignard's sपंचांग32-समयrs driver
 */

#अगर_अघोषित _LINUX_STM32_LPTIMER_H_
#घोषणा _LINUX_STM32_LPTIMER_H_

#समावेश <linux/clk.h>
#समावेश <linux/regmap.h>

#घोषणा STM32_LPTIM_ISR		0x00	/* Interrupt and Status Reg  */
#घोषणा STM32_LPTIM_ICR		0x04	/* Interrupt Clear Reg       */
#घोषणा STM32_LPTIM_IER		0x08	/* Interrupt Enable Reg      */
#घोषणा STM32_LPTIM_CFGR	0x0C	/* Configuration Reg         */
#घोषणा STM32_LPTIM_CR		0x10	/* Control Reg               */
#घोषणा STM32_LPTIM_CMP		0x14	/* Compare Reg               */
#घोषणा STM32_LPTIM_ARR		0x18	/* Autoreload Reg            */
#घोषणा STM32_LPTIM_CNT		0x1C	/* Counter Reg               */

/* STM32_LPTIM_ISR - bit fields */
#घोषणा STM32_LPTIM_CMPOK_ARROK		GENMASK(4, 3)
#घोषणा STM32_LPTIM_ARROK		BIT(4)
#घोषणा STM32_LPTIM_CMPOK		BIT(3)

/* STM32_LPTIM_ICR - bit fields */
#घोषणा STM32_LPTIM_ARRMCF		BIT(1)
#घोषणा STM32_LPTIM_CMPOKCF_ARROKCF	GENMASK(4, 3)

/* STM32_LPTIM_IER - bit flieds */
#घोषणा STM32_LPTIM_ARRMIE	BIT(1)

/* STM32_LPTIM_CR - bit fields */
#घोषणा STM32_LPTIM_CNTSTRT	BIT(2)
#घोषणा STM32_LPTIM_SNGSTRT	BIT(1)
#घोषणा STM32_LPTIM_ENABLE	BIT(0)

/* STM32_LPTIM_CFGR - bit fields */
#घोषणा STM32_LPTIM_ENC		BIT(24)
#घोषणा STM32_LPTIM_COUNTMODE	BIT(23)
#घोषणा STM32_LPTIM_WAVPOL	BIT(21)
#घोषणा STM32_LPTIM_PRESC	GENMASK(11, 9)
#घोषणा STM32_LPTIM_CKPOL	GENMASK(2, 1)

/* STM32_LPTIM_ARR */
#घोषणा STM32_LPTIM_MAX_ARR	0xFFFF

/**
 * काष्ठा sपंचांग32_lpसमयr - STM32 Low-Power Timer data asचिन्हित by parent device
 * @clk: घड़ी reference क्रम this instance
 * @regmap: रेजिस्टर map reference क्रम this instance
 * @has_encoder: indicates this Low-Power Timer supports encoder mode
 */
काष्ठा sपंचांग32_lpसमयr अणु
	काष्ठा clk *clk;
	काष्ठा regmap *regmap;
	bool has_encoder;
पूर्ण;

#पूर्ण_अगर
