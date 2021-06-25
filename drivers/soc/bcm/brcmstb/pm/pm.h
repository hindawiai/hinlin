<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Definitions क्रम Broadcom STB घातer management / Always ON (AON) block
 *
 * Copyright तऊ 2016-2017 Broadcom
 */

#अगर_अघोषित __BRCMSTB_PM_H__
#घोषणा __BRCMSTB_PM_H__

#घोषणा AON_CTRL_RESET_CTRL		0x00
#घोषणा AON_CTRL_PM_CTRL		0x04
#घोषणा AON_CTRL_PM_STATUS		0x08
#घोषणा AON_CTRL_PM_CPU_WAIT_COUNT	0x10
#घोषणा AON_CTRL_PM_INITIATE		0x88
#घोषणा AON_CTRL_HOST_MISC_CMDS		0x8c
#घोषणा AON_CTRL_SYSTEM_DATA_RAM_OFS	0x200

/* MIPS PM स्थिरants */
/* MEMC0 offsets */
#घोषणा DDR40_PHY_CONTROL_REGS_0_PLL_STATUS	0x10
#घोषणा DDR40_PHY_CONTROL_REGS_0_STANDBY_CTRL	0xa4

/* TIMER offsets */
#घोषणा TIMER_TIMER1_CTRL		0x0c
#घोषणा TIMER_TIMER1_STAT		0x1c

/* TIMER defines */
#घोषणा RESET_TIMER			0x0
#घोषणा START_TIMER			0xbfffffff
#घोषणा TIMER_MASK			0x3fffffff

/* PM_CTRL bitfield (Method #0) */
#घोषणा PM_FAST_PWRDOWN			(1 << 6)
#घोषणा PM_WARM_BOOT			(1 << 5)
#घोषणा PM_DEEP_STANDBY			(1 << 4)
#घोषणा PM_CPU_PWR			(1 << 3)
#घोषणा PM_USE_CPU_RDY			(1 << 2)
#घोषणा PM_PLL_PWRDOWN			(1 << 1)
#घोषणा PM_PWR_DOWN			(1 << 0)

/* PM_CTRL bitfield (Method #1) */
#घोषणा PM_DPHY_STANDBY_CLEAR		(1 << 20)
#घोषणा PM_MIN_S3_WIDTH_TIMER_BYPASS	(1 << 7)

#घोषणा PM_S2_COMMAND	(PM_PLL_PWRDOWN | PM_USE_CPU_RDY | PM_PWR_DOWN)

/* Method 0 biपंचांगasks */
#घोषणा PM_COLD_CONFIG	(PM_PLL_PWRDOWN | PM_DEEP_STANDBY)
#घोषणा PM_WARM_CONFIG	(PM_COLD_CONFIG | PM_USE_CPU_RDY | PM_WARM_BOOT)

/* Method 1 biपंचांगask */
#घोषणा M1_PM_WARM_CONFIG (PM_DPHY_STANDBY_CLEAR | \
			   PM_MIN_S3_WIDTH_TIMER_BYPASS | \
			   PM_WARM_BOOT | PM_DEEP_STANDBY | \
			   PM_PLL_PWRDOWN | PM_PWR_DOWN)

#घोषणा M1_PM_COLD_CONFIG (PM_DPHY_STANDBY_CLEAR | \
			   PM_MIN_S3_WIDTH_TIMER_BYPASS | \
			   PM_DEEP_STANDBY | \
			   PM_PLL_PWRDOWN | PM_PWR_DOWN)

#अगर_अघोषित __ASSEMBLY__

#अगर_अघोषित CONFIG_MIPS
बाह्य स्थिर अचिन्हित दीर्घ brcmstb_pm_करो_s2_sz;
बाह्य यंत्रlinkage पूर्णांक brcmstb_pm_करो_s2(व्योम __iomem *aon_ctrl_base,
		व्योम __iomem *ddr_phy_pll_status);
#अन्यथा
/* s2 यंत्र */
बाह्य यंत्रlinkage पूर्णांक brcm_pm_करो_s2(u32 *s2_params);

/* s3 यंत्र */
बाह्य यंत्रlinkage पूर्णांक brcm_pm_करो_s3(व्योम __iomem *aon_ctrl_base,
		पूर्णांक dcache_linesz);
बाह्य पूर्णांक s3_reentry;
#पूर्ण_अगर /* CONFIG_MIPS */

#पूर्ण_अगर 

#पूर्ण_अगर /* __BRCMSTB_PM_H__ */
