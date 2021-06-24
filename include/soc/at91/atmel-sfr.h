<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Aपंचांगel SFR (Special Function Registers) रेजिस्टर offsets and bit definitions.
 *
 * Copyright (C) 2016 Aपंचांगel
 *
 * Author: Luकरोvic Desroches <luकरोvic.desroches@aपंचांगel.com>
 */

#अगर_अघोषित _LINUX_MFD_SYSCON_ATMEL_SFR_H
#घोषणा _LINUX_MFD_SYSCON_ATMEL_SFR_H

#घोषणा AT91_SFR_DDRCFG		0x04	/* DDR Configuration Register */
#घोषणा AT91_SFR_CCFG_EBICSA	0x04	/* EBI Chip Select Register */
/* 0x08 ~ 0x0c: Reserved */
#घोषणा AT91_SFR_OHCIICR	0x10	/* OHCI INT Configuration Register */
#घोषणा AT91_SFR_OHCIISR	0x14	/* OHCI INT Status Register */
#घोषणा AT91_SFR_UTMICKTRIM	0x30	/* UTMI Clock Trimming Register */
#घोषणा AT91_SFR_UTMISWAP	0x3c	/* UTMI DP/DM Pin Swapping Register */
#घोषणा AT91_SFR_LS		0x7c	/* Light Sleep Register */
#घोषणा AT91_SFR_I2SCLKSEL	0x90	/* I2SC Register */
#घोषणा AT91_SFR_WPMR		0xe4	/* Write Protection Mode Register */

/* Field definitions */
#घोषणा AT91_SFR_CCFG_EBI_CSA(cs, val)		((val) << (cs))
#घोषणा AT91_SFR_CCFG_EBI_DBPUC			BIT(8)
#घोषणा AT91_SFR_CCFG_EBI_DBPDC			BIT(9)
#घोषणा AT91_SFR_CCFG_EBI_DRIVE			BIT(17)
#घोषणा AT91_SFR_CCFG_NFD0_ON_D16		BIT(24)
#घोषणा AT91_SFR_CCFG_DDR_MP_EN			BIT(25)

#घोषणा AT91_SFR_OHCIICR_RES(x)			BIT(x)
#घोषणा AT91_SFR_OHCIICR_ARIE			BIT(4)
#घोषणा AT91_SFR_OHCIICR_APPSTART		BIT(5)
#घोषणा AT91_SFR_OHCIICR_USB_SUSP(x)		BIT(8 + (x))
#घोषणा AT91_SFR_OHCIICR_UDPPUDIS		BIT(23)
#घोषणा AT91_OHCIICR_USB_SUSPEND		GENMASK(10, 8)

#घोषणा AT91_SFR_OHCIISR_RIS(x)			BIT(x)

#घोषणा AT91_UTMICKTRIM_FREQ			GENMASK(1, 0)

#घोषणा AT91_SFR_UTMISWAP_PORT(x)		BIT(x)

#घोषणा AT91_SFR_LS_VALUE(x)			BIT(x)
#घोषणा AT91_SFR_LS_MEM_POWER_GATING_ULP1_EN	BIT(16)

#घोषणा AT91_SFR_WPMR_WPEN			BIT(0)
#घोषणा AT91_SFR_WPMR_WPKEY_MASK		GENMASK(31, 8)

#पूर्ण_अगर /* _LINUX_MFD_SYSCON_ATMEL_SFR_H */
