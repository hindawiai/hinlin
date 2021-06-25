<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Freescale eSDHC controller driver generics क्रम OF and pltfm.
 *
 * Copyright (c) 2007 Freescale Semiconductor, Inc.
 * Copyright (c) 2009 MontaVista Software, Inc.
 * Copyright (c) 2010 Pengutronix e.K.
 * Copyright 2020 NXP
 *   Author: Wolfram Sang <kernel@pengutronix.de>
 */

#अगर_अघोषित _DRIVERS_MMC_SDHCI_ESDHC_H
#घोषणा _DRIVERS_MMC_SDHCI_ESDHC_H

/*
 * Ops and quirks क्रम the Freescale eSDHC controller.
 */

#घोषणा ESDHC_DEFAULT_QUIRKS	(SDHCI_QUIRK_FORCE_BLK_SZ_2048 | \
				SDHCI_QUIRK_32BIT_DMA_ADDR | \
				SDHCI_QUIRK_NO_BUSY_IRQ | \
				SDHCI_QUIRK_DATA_TIMEOUT_USES_SDCLK | \
				SDHCI_QUIRK_PIO_NEEDS_DELAY | \
				SDHCI_QUIRK_NO_HISPD_BIT)

/* pltfm-specअगरic */
#घोषणा ESDHC_HOST_CONTROL_LE	0x20

/*
 * eSDHC रेजिस्टर definition
 */

/* Present State Register */
#घोषणा ESDHC_PRSSTAT			0x24
#घोषणा ESDHC_CLOCK_GATE_OFF		0x00000080
#घोषणा ESDHC_CLOCK_STABLE		0x00000008

/* Protocol Control Register */
#घोषणा ESDHC_PROCTL			0x28
#घोषणा ESDHC_VOLT_SEL			0x00000400
#घोषणा ESDHC_CTRL_4BITBUS		(0x1 << 1)
#घोषणा ESDHC_CTRL_8BITBUS		(0x2 << 1)
#घोषणा ESDHC_CTRL_BUSWIDTH_MASK	(0x3 << 1)
#घोषणा ESDHC_HOST_CONTROL_RES		0x01

/* System Control Register */
#घोषणा ESDHC_SYSTEM_CONTROL		0x2c
#घोषणा ESDHC_CLOCK_MASK		0x0000fff0
#घोषणा ESDHC_PREDIV_SHIFT		8
#घोषणा ESDHC_DIVIDER_SHIFT		4
#घोषणा ESDHC_CLOCK_SDCLKEN		0x00000008
#घोषणा ESDHC_CLOCK_PEREN		0x00000004
#घोषणा ESDHC_CLOCK_HCKEN		0x00000002
#घोषणा ESDHC_CLOCK_IPGEN		0x00000001

/* System Control 2 Register */
#घोषणा ESDHC_SYSTEM_CONTROL_2		0x3c
#घोषणा ESDHC_SMPCLKSEL			0x00800000
#घोषणा ESDHC_EXTN			0x00400000

/* Host Controller Capabilities Register 2 */
#घोषणा ESDHC_CAPABILITIES_1		0x114

/* Tuning Block Control Register */
#घोषणा ESDHC_TBCTL			0x120
#घोषणा ESDHC_HS400_WNDW_ADJUST		0x00000040
#घोषणा ESDHC_HS400_MODE		0x00000010
#घोषणा ESDHC_TB_EN			0x00000004
#घोषणा ESDHC_TB_MODE_MASK		0x00000003
#घोषणा ESDHC_TB_MODE_SW		0x00000003
#घोषणा ESDHC_TB_MODE_3			0x00000002

#घोषणा ESDHC_TBSTAT			0x124

#घोषणा ESDHC_TBPTR			0x128
#घोषणा ESDHC_WNDW_STRT_PTR_SHIFT	8
#घोषणा ESDHC_WNDW_STRT_PTR_MASK	(0x7f << 8)
#घोषणा ESDHC_WNDW_END_PTR_MASK		0x7f

/* SD Clock Control Register */
#घोषणा ESDHC_SDCLKCTL			0x144
#घोषणा ESDHC_LPBK_CLK_SEL		0x80000000
#घोषणा ESDHC_CMD_CLK_CTL		0x00008000

/* SD Timing Control Register */
#घोषणा ESDHC_SDTIMNGCTL		0x148
#घोषणा ESDHC_FLW_CTL_BG		0x00008000

/* DLL Config 0 Register */
#घोषणा ESDHC_DLLCFG0			0x160
#घोषणा ESDHC_DLL_ENABLE		0x80000000
#घोषणा ESDHC_DLL_RESET			0x40000000
#घोषणा ESDHC_DLL_FREQ_SEL		0x08000000

/* DLL Config 1 Register */
#घोषणा ESDHC_DLLCFG1			0x164
#घोषणा ESDHC_DLL_PD_PULSE_STRETCH_SEL	0x80000000

/* DLL Status 0 Register */
#घोषणा ESDHC_DLLSTAT0			0x170
#घोषणा ESDHC_DLL_STS_SLV_LOCK		0x08000000

/* Control Register क्रम DMA transfer */
#घोषणा ESDHC_DMA_SYSCTL		0x40c
#घोषणा ESDHC_PERIPHERAL_CLK_SEL	0x00080000
#घोषणा ESDHC_FLUSH_ASYNC_FIFO		0x00040000
#घोषणा ESDHC_DMA_SNOOP			0x00000040

#पूर्ण_अगर /* _DRIVERS_MMC_SDHCI_ESDHC_H */
