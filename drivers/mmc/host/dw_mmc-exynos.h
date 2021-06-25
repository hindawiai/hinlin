<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Exynos Specअगरic Extensions क्रम Synopsys DW Mulसमयdia Card Interface driver
 *
 * Copyright (C) 2012-2014 Samsung Electronics Co., Ltd.
 */

#अगर_अघोषित _DW_MMC_EXYNOS_H_
#घोषणा _DW_MMC_EXYNOS_H_

#घोषणा SDMMC_CLKSEL			0x09C
#घोषणा SDMMC_CLKSEL64			0x0A8

/* Extended Register's Offset */
#घोषणा SDMMC_HS400_DQS_EN		0x180
#घोषणा SDMMC_HS400_ASYNC_FIFO_CTRL	0x184
#घोषणा SDMMC_HS400_DLINE_CTRL		0x188

/* CLKSEL रेजिस्टर defines */
#घोषणा SDMMC_CLKSEL_CCLK_SAMPLE(x)	(((x) & 7) << 0)
#घोषणा SDMMC_CLKSEL_CCLK_DRIVE(x)	(((x) & 7) << 16)
#घोषणा SDMMC_CLKSEL_CCLK_DIVIDER(x)	(((x) & 7) << 24)
#घोषणा SDMMC_CLKSEL_GET_DRV_WD3(x)	(((x) >> 16) & 0x7)
#घोषणा SDMMC_CLKSEL_GET_DIV(x)		(((x) >> 24) & 0x7)
#घोषणा SDMMC_CLKSEL_UP_SAMPLE(x, y)	(((x) & ~SDMMC_CLKSEL_CCLK_SAMPLE(7)) |\
					 SDMMC_CLKSEL_CCLK_SAMPLE(y))
#घोषणा SDMMC_CLKSEL_TIMING(x, y, z)	(SDMMC_CLKSEL_CCLK_SAMPLE(x) |	\
					 SDMMC_CLKSEL_CCLK_DRIVE(y) |	\
					 SDMMC_CLKSEL_CCLK_DIVIDER(z))
#घोषणा SDMMC_CLKSEL_TIMING_MASK	SDMMC_CLKSEL_TIMING(0x7, 0x7, 0x7)
#घोषणा SDMMC_CLKSEL_WAKEUP_INT		BIT(11)

/* RCLK_EN रेजिस्टर defines */
#घोषणा DATA_STROBE_EN			BIT(0)
#घोषणा AXI_NON_BLOCKING_WR	BIT(7)

/* DLINE_CTRL रेजिस्टर defines */
#घोषणा DQS_CTRL_RD_DELAY(x, y)		(((x) & ~0x3FF) | ((y) & 0x3FF))
#घोषणा DQS_CTRL_GET_RD_DELAY(x)	((x) & 0x3FF)

/* Protector Register */
#घोषणा SDMMC_EMMCP_BASE	0x1000
#घोषणा SDMMC_MPSECURITY	(SDMMC_EMMCP_BASE + 0x0010)
#घोषणा SDMMC_MPSBEGIN0		(SDMMC_EMMCP_BASE + 0x0200)
#घोषणा SDMMC_MPSEND0		(SDMMC_EMMCP_BASE + 0x0204)
#घोषणा SDMMC_MPSCTRL0		(SDMMC_EMMCP_BASE + 0x020C)

/* SMU control defines */
#घोषणा SDMMC_MPSCTRL_SECURE_READ_BIT		BIT(7)
#घोषणा SDMMC_MPSCTRL_SECURE_WRITE_BIT		BIT(6)
#घोषणा SDMMC_MPSCTRL_NON_SECURE_READ_BIT	BIT(5)
#घोषणा SDMMC_MPSCTRL_NON_SECURE_WRITE_BIT	BIT(4)
#घोषणा SDMMC_MPSCTRL_USE_FUSE_KEY		BIT(3)
#घोषणा SDMMC_MPSCTRL_ECB_MODE			BIT(2)
#घोषणा SDMMC_MPSCTRL_ENCRYPTION		BIT(1)
#घोषणा SDMMC_MPSCTRL_VALID			BIT(0)

/* Maximum number of Ending sector */
#घोषणा SDMMC_ENDING_SEC_NR_MAX	0xFFFFFFFF

/* Fixed घड़ी भागider */
#घोषणा EXYNOS4210_FIXED_CIU_CLK_DIV	2
#घोषणा EXYNOS4412_FIXED_CIU_CLK_DIV	4
#घोषणा HS400_FIXED_CIU_CLK_DIV		1

/* Minimal required घड़ी frequency क्रम cclkin, unit: HZ */
#घोषणा EXYNOS_CCLKIN_MIN	50000000

#पूर्ण_अगर /* _DW_MMC_EXYNOS_H_ */
