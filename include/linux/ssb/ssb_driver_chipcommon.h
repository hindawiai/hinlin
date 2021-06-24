<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित LINUX_SSB_CHIPCO_H_
#घोषणा LINUX_SSB_CHIPCO_H_

/* SonicsSiliconBackplane CHIPCOMMON core hardware definitions
 *
 * The chipcommon core provides chip identअगरication, SB control,
 * jtag, 0/1/2 uarts, घड़ी frequency control, a watchकरोg पूर्णांकerrupt समयr,
 * gpio पूर्णांकerface, extbus, and support क्रम serial and parallel flashes.
 *
 * Copyright 2005, Broadcom Corporation
 * Copyright 2006, Michael Buesch <m@bues.ch>
 */

/** ChipCommon core रेजिस्टरs. **/

#घोषणा SSB_CHIPCO_CHIPID		0x0000
#घोषणा  SSB_CHIPCO_IDMASK		0x0000FFFF
#घोषणा  SSB_CHIPCO_REVMASK		0x000F0000
#घोषणा  SSB_CHIPCO_REVSHIFT		16
#घोषणा  SSB_CHIPCO_PACKMASK		0x00F00000
#घोषणा  SSB_CHIPCO_PACKSHIFT		20
#घोषणा  SSB_CHIPCO_NRCORESMASK		0x0F000000
#घोषणा  SSB_CHIPCO_NRCORESSHIFT	24
#घोषणा SSB_CHIPCO_CAP	 		0x0004		/* Capabilities */
#घोषणा  SSB_CHIPCO_CAP_NRUART		0x00000003	/* # of UARTs */
#घोषणा  SSB_CHIPCO_CAP_MIPSEB		0x00000004	/* MIPS in BigEndian Mode */
#घोषणा  SSB_CHIPCO_CAP_UARTCLK		0x00000018	/* UART घड़ी select */
#घोषणा   SSB_CHIPCO_CAP_UARTCLK_INT	0x00000008	/* UARTs are driven by पूर्णांकernal भागided घड़ी */
#घोषणा  SSB_CHIPCO_CAP_UARTGPIO	0x00000020	/* UARTs on GPIO 15-12 */
#घोषणा  SSB_CHIPCO_CAP_EXTBUS		0x000000C0	/* External buses present */
#घोषणा  SSB_CHIPCO_CAP_FLASHT		0x00000700	/* Flash Type */
#घोषणा   SSB_CHIPCO_FLASHT_NONE	0x00000000	/* No flash */
#घोषणा   SSB_CHIPCO_FLASHT_STSER	0x00000100	/* ST serial flash */
#घोषणा   SSB_CHIPCO_FLASHT_ATSER	0x00000200	/* Aपंचांगel serial flash */
#घोषणा	  SSB_CHIPCO_FLASHT_PARA	0x00000700	/* Parallel flash */
#घोषणा  SSB_CHIPCO_CAP_PLLT		0x00038000	/* PLL Type */
#घोषणा   SSB_PLLTYPE_NONE		0x00000000
#घोषणा   SSB_PLLTYPE_1			0x00010000	/* 48Mhz base, 3 भागiders */
#घोषणा   SSB_PLLTYPE_2			0x00020000	/* 48Mhz, 4 भागiders */
#घोषणा   SSB_PLLTYPE_3			0x00030000	/* 25Mhz, 2 भागiders */
#घोषणा   SSB_PLLTYPE_4			0x00008000	/* 48Mhz, 4 भागiders */
#घोषणा   SSB_PLLTYPE_5			0x00018000	/* 25Mhz, 4 भागiders */
#घोषणा   SSB_PLLTYPE_6			0x00028000	/* 100/200 or 120/240 only */
#घोषणा   SSB_PLLTYPE_7			0x00038000	/* 25Mhz, 4 भागiders */
#घोषणा  SSB_CHIPCO_CAP_PCTL		0x00040000	/* Power Control */
#घोषणा  SSB_CHIPCO_CAP_OTPS		0x00380000	/* OTP size */
#घोषणा  SSB_CHIPCO_CAP_OTPS_SHIFT	19
#घोषणा  SSB_CHIPCO_CAP_OTPS_BASE	5
#घोषणा  SSB_CHIPCO_CAP_JTAGM		0x00400000	/* JTAG master present */
#घोषणा  SSB_CHIPCO_CAP_BROM		0x00800000	/* Internal boot ROM active */
#घोषणा  SSB_CHIPCO_CAP_64BIT		0x08000000	/* 64-bit Backplane */
#घोषणा  SSB_CHIPCO_CAP_PMU		0x10000000	/* PMU available (rev >= 20) */
#घोषणा  SSB_CHIPCO_CAP_ECI		0x20000000	/* ECI available (rev >= 20) */
#घोषणा  SSB_CHIPCO_CAP_SPROM		0x40000000	/* SPROM present */
#घोषणा SSB_CHIPCO_CORECTL		0x0008
#घोषणा  SSB_CHIPCO_CORECTL_UARTCLK0	0x00000001	/* Drive UART with पूर्णांकernal घड़ी */
#घोषणा	 SSB_CHIPCO_CORECTL_SE		0x00000002	/* sync clk out enable (corerev >= 3) */
#घोषणा  SSB_CHIPCO_CORECTL_UARTCLKEN	0x00000008	/* UART घड़ी enable (rev >= 21) */
#घोषणा SSB_CHIPCO_BIST			0x000C
#घोषणा SSB_CHIPCO_OTPS			0x0010		/* OTP status */
#घोषणा	 SSB_CHIPCO_OTPS_PROGFAIL	0x80000000
#घोषणा	 SSB_CHIPCO_OTPS_PROTECT	0x00000007
#घोषणा	 SSB_CHIPCO_OTPS_HW_PROTECT	0x00000001
#घोषणा	 SSB_CHIPCO_OTPS_SW_PROTECT	0x00000002
#घोषणा	 SSB_CHIPCO_OTPS_CID_PROTECT	0x00000004
#घोषणा SSB_CHIPCO_OTPC			0x0014		/* OTP control */
#घोषणा	 SSB_CHIPCO_OTPC_RECWAIT	0xFF000000
#घोषणा	 SSB_CHIPCO_OTPC_PROGWAIT	0x00FFFF00
#घोषणा	 SSB_CHIPCO_OTPC_PRW_SHIFT	8
#घोषणा	 SSB_CHIPCO_OTPC_MAXFAIL	0x00000038
#घोषणा	 SSB_CHIPCO_OTPC_VSEL		0x00000006
#घोषणा	 SSB_CHIPCO_OTPC_SELVL		0x00000001
#घोषणा SSB_CHIPCO_OTPP			0x0018		/* OTP prog */
#घोषणा	 SSB_CHIPCO_OTPP_COL		0x000000FF
#घोषणा	 SSB_CHIPCO_OTPP_ROW		0x0000FF00
#घोषणा	 SSB_CHIPCO_OTPP_ROW_SHIFT	8
#घोषणा	 SSB_CHIPCO_OTPP_READERR	0x10000000
#घोषणा	 SSB_CHIPCO_OTPP_VALUE		0x20000000
#घोषणा	 SSB_CHIPCO_OTPP_READ		0x40000000
#घोषणा	 SSB_CHIPCO_OTPP_START		0x80000000
#घोषणा	 SSB_CHIPCO_OTPP_BUSY		0x80000000
#घोषणा SSB_CHIPCO_IRQSTAT		0x0020
#घोषणा SSB_CHIPCO_IRQMASK		0x0024
#घोषणा	 SSB_CHIPCO_IRQ_GPIO		0x00000001	/* gpio पूर्णांकr */
#घोषणा	 SSB_CHIPCO_IRQ_EXT		0x00000002	/* ro: ext पूर्णांकr pin (corerev >= 3) */
#घोषणा	 SSB_CHIPCO_IRQ_WDRESET		0x80000000	/* watchकरोg reset occurred */
#घोषणा SSB_CHIPCO_CHIPCTL		0x0028		/* Rev >= 11 only */
#घोषणा SSB_CHIPCO_CHIPSTAT		0x002C		/* Rev >= 11 only */
#घोषणा SSB_CHIPCO_JCMD			0x0030		/* Rev >= 10 only */
#घोषणा  SSB_CHIPCO_JCMD_START		0x80000000
#घोषणा  SSB_CHIPCO_JCMD_BUSY		0x80000000
#घोषणा  SSB_CHIPCO_JCMD_PAUSE		0x40000000
#घोषणा  SSB_CHIPCO_JCMD0_ACC_MASK	0x0000F000
#घोषणा  SSB_CHIPCO_JCMD0_ACC_IRDR	0x00000000
#घोषणा  SSB_CHIPCO_JCMD0_ACC_DR	0x00001000
#घोषणा  SSB_CHIPCO_JCMD0_ACC_IR	0x00002000
#घोषणा  SSB_CHIPCO_JCMD0_ACC_RESET	0x00003000
#घोषणा  SSB_CHIPCO_JCMD0_ACC_IRPDR	0x00004000
#घोषणा  SSB_CHIPCO_JCMD0_ACC_PDR	0x00005000
#घोषणा  SSB_CHIPCO_JCMD0_IRW_MASK	0x00000F00
#घोषणा  SSB_CHIPCO_JCMD_ACC_MASK	0x000F0000	/* Changes क्रम corerev 11 */
#घोषणा  SSB_CHIPCO_JCMD_ACC_IRDR	0x00000000
#घोषणा  SSB_CHIPCO_JCMD_ACC_DR		0x00010000
#घोषणा  SSB_CHIPCO_JCMD_ACC_IR		0x00020000
#घोषणा  SSB_CHIPCO_JCMD_ACC_RESET	0x00030000
#घोषणा  SSB_CHIPCO_JCMD_ACC_IRPDR	0x00040000
#घोषणा  SSB_CHIPCO_JCMD_ACC_PDR	0x00050000
#घोषणा  SSB_CHIPCO_JCMD_IRW_MASK	0x00001F00
#घोषणा  SSB_CHIPCO_JCMD_IRW_SHIFT	8
#घोषणा  SSB_CHIPCO_JCMD_DRW_MASK	0x0000003F
#घोषणा SSB_CHIPCO_JIR			0x0034		/* Rev >= 10 only */
#घोषणा SSB_CHIPCO_JDR			0x0038		/* Rev >= 10 only */
#घोषणा SSB_CHIPCO_JCTL			0x003C		/* Rev >= 10 only */
#घोषणा  SSB_CHIPCO_JCTL_FORCE_CLK	4		/* Force घड़ी */
#घोषणा  SSB_CHIPCO_JCTL_EXT_EN		2		/* Enable बाह्यal tarमाला_लो */
#घोषणा  SSB_CHIPCO_JCTL_EN		1		/* Enable Jtag master */
#घोषणा SSB_CHIPCO_FLASHCTL		0x0040
#घोषणा  SSB_CHIPCO_FLASHCTL_START	0x80000000
#घोषणा  SSB_CHIPCO_FLASHCTL_BUSY	SSB_CHIPCO_FLASHCTL_START
#घोषणा SSB_CHIPCO_FLASHADDR		0x0044
#घोषणा SSB_CHIPCO_FLASHDATA		0x0048
#घोषणा SSB_CHIPCO_BCAST_ADDR		0x0050
#घोषणा SSB_CHIPCO_BCAST_DATA		0x0054
#घोषणा SSB_CHIPCO_GPIOPULLUP		0x0058		/* Rev >= 20 only */
#घोषणा SSB_CHIPCO_GPIOPULLDOWN		0x005C		/* Rev >= 20 only */
#घोषणा SSB_CHIPCO_GPIOIN		0x0060
#घोषणा SSB_CHIPCO_GPIOOUT		0x0064
#घोषणा SSB_CHIPCO_GPIOOUTEN		0x0068
#घोषणा SSB_CHIPCO_GPIOCTL		0x006C
#घोषणा SSB_CHIPCO_GPIOPOL		0x0070
#घोषणा SSB_CHIPCO_GPIOIRQ		0x0074
#घोषणा SSB_CHIPCO_WATCHDOG		0x0080
#घोषणा SSB_CHIPCO_GPIOTIMER		0x0088		/* LED घातersave (corerev >= 16) */
#घोषणा  SSB_CHIPCO_GPIOTIMER_OFFTIME	0x0000FFFF
#घोषणा  SSB_CHIPCO_GPIOTIMER_OFFTIME_SHIFT	0
#घोषणा  SSB_CHIPCO_GPIOTIMER_ONTIME	0xFFFF0000
#घोषणा  SSB_CHIPCO_GPIOTIMER_ONTIME_SHIFT	16
#घोषणा SSB_CHIPCO_GPIOTOUTM		0x008C		/* LED घातersave (corerev >= 16) */
#घोषणा SSB_CHIPCO_CLOCK_N		0x0090
#घोषणा SSB_CHIPCO_CLOCK_SB		0x0094
#घोषणा SSB_CHIPCO_CLOCK_PCI		0x0098
#घोषणा SSB_CHIPCO_CLOCK_M2		0x009C
#घोषणा SSB_CHIPCO_CLOCK_MIPS		0x00A0
#घोषणा SSB_CHIPCO_CLKDIV		0x00A4		/* Rev >= 3 only */
#घोषणा	 SSB_CHIPCO_CLKDIV_SFLASH	0x0F000000
#घोषणा	 SSB_CHIPCO_CLKDIV_SFLASH_SHIFT	24
#घोषणा	 SSB_CHIPCO_CLKDIV_OTP		0x000F0000
#घोषणा	 SSB_CHIPCO_CLKDIV_OTP_SHIFT	16
#घोषणा	 SSB_CHIPCO_CLKDIV_JTAG		0x00000F00
#घोषणा	 SSB_CHIPCO_CLKDIV_JTAG_SHIFT	8
#घोषणा	 SSB_CHIPCO_CLKDIV_UART		0x000000FF
#घोषणा SSB_CHIPCO_PLLONDELAY		0x00B0		/* Rev >= 4 only */
#घोषणा SSB_CHIPCO_FREFSELDELAY		0x00B4		/* Rev >= 4 only */
#घोषणा SSB_CHIPCO_SLOWCLKCTL		0x00B8		/* 6 <= Rev <= 9 only */
#घोषणा  SSB_CHIPCO_SLOWCLKCTL_SRC	0x00000007	/* slow घड़ी source mask */
#घोषणा	  SSB_CHIPCO_SLOWCLKCTL_SRC_LPO		0x00000000	/* source of slow घड़ी is LPO */
#घोषणा   SSB_CHIPCO_SLOWCLKCTL_SRC_XTAL	0x00000001	/* source of slow घड़ी is crystal */
#घोषणा	  SSB_CHIPCO_SLOECLKCTL_SRC_PCI		0x00000002	/* source of slow घड़ी is PCI */
#घोषणा  SSB_CHIPCO_SLOWCLKCTL_LPOFREQ	0x00000200	/* LPOFreqSel, 1: 160Khz, 0: 32KHz */
#घोषणा  SSB_CHIPCO_SLOWCLKCTL_LPOPD	0x00000400	/* LPOPowerDown, 1: LPO is disabled, 0: LPO is enabled */
#घोषणा  SSB_CHIPCO_SLOWCLKCTL_FSLOW	0x00000800	/* ForceSlowClk, 1: sb/cores running on slow घड़ी, 0: घातer logic control */
#घोषणा  SSB_CHIPCO_SLOWCLKCTL_IPLL	0x00001000	/* IgnorePllOffReq, 1/0: घातer logic ignores/honors PLL घड़ी disable requests from core */
#घोषणा  SSB_CHIPCO_SLOWCLKCTL_ENXTAL	0x00002000	/* XtalControlEn, 1/0: घातer logic करोes/करोesn't disable crystal when appropriate */
#घोषणा  SSB_CHIPCO_SLOWCLKCTL_XTALPU	0x00004000	/* XtalPU (RO), 1/0: crystal running/disabled */
#घोषणा  SSB_CHIPCO_SLOWCLKCTL_CLKDIV	0xFFFF0000	/* ClockDivider (SlowClk = 1/(4+भागisor)) */
#घोषणा  SSB_CHIPCO_SLOWCLKCTL_CLKDIV_SHIFT	16
#घोषणा SSB_CHIPCO_SYSCLKCTL		0x00C0		/* Rev >= 3 only */
#घोषणा	 SSB_CHIPCO_SYSCLKCTL_IDLPEN	0x00000001	/* ILPen: Enable Idle Low Power */
#घोषणा	 SSB_CHIPCO_SYSCLKCTL_ALPEN	0x00000002	/* ALPen: Enable Active Low Power */
#घोषणा	 SSB_CHIPCO_SYSCLKCTL_PLLEN	0x00000004	/* ForcePLLOn */
#घोषणा	 SSB_CHIPCO_SYSCLKCTL_FORCEALP	0x00000008	/* Force ALP (or HT अगर ALPen is not set */
#घोषणा	 SSB_CHIPCO_SYSCLKCTL_FORCEHT	0x00000010	/* Force HT */
#घोषणा  SSB_CHIPCO_SYSCLKCTL_CLKDIV	0xFFFF0000	/* ClkDiv  (ILP = 1/(4+भागisor)) */
#घोषणा  SSB_CHIPCO_SYSCLKCTL_CLKDIV_SHIFT	16
#घोषणा SSB_CHIPCO_CLKSTSTR		0x00C4		/* Rev >= 3 only */
#घोषणा SSB_CHIPCO_PCMCIA_CFG		0x0100
#घोषणा SSB_CHIPCO_PCMCIA_MEMWAIT	0x0104
#घोषणा SSB_CHIPCO_PCMCIA_ATTRWAIT	0x0108
#घोषणा SSB_CHIPCO_PCMCIA_IOWAIT	0x010C
#घोषणा SSB_CHIPCO_IDE_CFG		0x0110
#घोषणा SSB_CHIPCO_IDE_MEMWAIT		0x0114
#घोषणा SSB_CHIPCO_IDE_ATTRWAIT		0x0118
#घोषणा SSB_CHIPCO_IDE_IOWAIT		0x011C
#घोषणा SSB_CHIPCO_PROG_CFG		0x0120
#घोषणा SSB_CHIPCO_PROG_WAITCNT		0x0124
#घोषणा SSB_CHIPCO_FLASH_CFG		0x0128
#घोषणा SSB_CHIPCO_FLASH_WAITCNT	0x012C
#घोषणा SSB_CHIPCO_CLKCTLST		0x01E0 /* Clock control and status (rev >= 20) */
#घोषणा  SSB_CHIPCO_CLKCTLST_FORCEALP	0x00000001 /* Force ALP request */
#घोषणा  SSB_CHIPCO_CLKCTLST_FORCEHT	0x00000002 /* Force HT request */
#घोषणा  SSB_CHIPCO_CLKCTLST_FORCEILP	0x00000004 /* Force ILP request */
#घोषणा  SSB_CHIPCO_CLKCTLST_HAVEALPREQ	0x00000008 /* ALP available request */
#घोषणा  SSB_CHIPCO_CLKCTLST_HAVEHTREQ	0x00000010 /* HT available request */
#घोषणा  SSB_CHIPCO_CLKCTLST_HWCROFF	0x00000020 /* Force HW घड़ी request off */
#घोषणा  SSB_CHIPCO_CLKCTLST_HAVEALP	0x00010000 /* ALP available */
#घोषणा  SSB_CHIPCO_CLKCTLST_HAVEHT	0x00020000 /* HT available */
#घोषणा  SSB_CHIPCO_CLKCTLST_4328A0_HAVEHT	0x00010000 /* 4328a0 has reversed bits */
#घोषणा  SSB_CHIPCO_CLKCTLST_4328A0_HAVEALP	0x00020000 /* 4328a0 has reversed bits */
#घोषणा SSB_CHIPCO_HW_WORKAROUND	0x01E4 /* Hardware workaround (rev >= 20) */
#घोषणा SSB_CHIPCO_UART0_DATA		0x0300
#घोषणा SSB_CHIPCO_UART0_IMR		0x0304
#घोषणा SSB_CHIPCO_UART0_FCR		0x0308
#घोषणा SSB_CHIPCO_UART0_LCR		0x030C
#घोषणा SSB_CHIPCO_UART0_MCR		0x0310
#घोषणा SSB_CHIPCO_UART0_LSR		0x0314
#घोषणा SSB_CHIPCO_UART0_MSR		0x0318
#घोषणा SSB_CHIPCO_UART0_SCRATCH	0x031C
#घोषणा SSB_CHIPCO_UART1_DATA		0x0400
#घोषणा SSB_CHIPCO_UART1_IMR		0x0404
#घोषणा SSB_CHIPCO_UART1_FCR		0x0408
#घोषणा SSB_CHIPCO_UART1_LCR		0x040C
#घोषणा SSB_CHIPCO_UART1_MCR		0x0410
#घोषणा SSB_CHIPCO_UART1_LSR		0x0414
#घोषणा SSB_CHIPCO_UART1_MSR		0x0418
#घोषणा SSB_CHIPCO_UART1_SCRATCH	0x041C
/* PMU रेजिस्टरs (rev >= 20) */
#घोषणा SSB_CHIPCO_PMU_CTL			0x0600 /* PMU control */
#घोषणा  SSB_CHIPCO_PMU_CTL_ILP_DIV		0xFFFF0000 /* ILP भाग mask */
#घोषणा  SSB_CHIPCO_PMU_CTL_ILP_DIV_SHIFT	16
#घोषणा  SSB_CHIPCO_PMU_CTL_PLL_UPD		0x00000400
#घोषणा  SSB_CHIPCO_PMU_CTL_NOILPONW		0x00000200 /* No ILP on रुको */
#घोषणा  SSB_CHIPCO_PMU_CTL_HTREQEN		0x00000100 /* HT req enable */
#घोषणा  SSB_CHIPCO_PMU_CTL_ALPREQEN		0x00000080 /* ALP req enable */
#घोषणा  SSB_CHIPCO_PMU_CTL_XTALFREQ		0x0000007C /* Crystal freq */
#घोषणा  SSB_CHIPCO_PMU_CTL_XTALFREQ_SHIFT	2
#घोषणा  SSB_CHIPCO_PMU_CTL_ILPDIVEN		0x00000002 /* ILP भाग enable */
#घोषणा  SSB_CHIPCO_PMU_CTL_LPOSEL		0x00000001 /* LPO sel */
#घोषणा SSB_CHIPCO_PMU_CAP			0x0604 /* PMU capabilities */
#घोषणा  SSB_CHIPCO_PMU_CAP_REVISION		0x000000FF /* Revision mask */
#घोषणा SSB_CHIPCO_PMU_STAT			0x0608 /* PMU status */
#घोषणा  SSB_CHIPCO_PMU_STAT_INTPEND		0x00000040 /* Interrupt pending */
#घोषणा  SSB_CHIPCO_PMU_STAT_SBCLKST		0x00000030 /* Backplane घड़ी status? */
#घोषणा  SSB_CHIPCO_PMU_STAT_HAVEALP		0x00000008 /* ALP available */
#घोषणा  SSB_CHIPCO_PMU_STAT_HAVEHT		0x00000004 /* HT available */
#घोषणा  SSB_CHIPCO_PMU_STAT_RESINIT		0x00000003 /* Res init */
#घोषणा SSB_CHIPCO_PMU_RES_STAT			0x060C /* PMU res status */
#घोषणा SSB_CHIPCO_PMU_RES_PEND			0x0610 /* PMU res pending */
#घोषणा SSB_CHIPCO_PMU_TIMER			0x0614 /* PMU समयr */
#घोषणा SSB_CHIPCO_PMU_MINRES_MSK		0x0618 /* PMU min res mask */
#घोषणा SSB_CHIPCO_PMU_MAXRES_MSK		0x061C /* PMU max res mask */
#घोषणा SSB_CHIPCO_PMU_RES_TABSEL		0x0620 /* PMU res table sel */
#घोषणा SSB_CHIPCO_PMU_RES_DEPMSK		0x0624 /* PMU res dep mask */
#घोषणा SSB_CHIPCO_PMU_RES_UPDNTM		0x0628 /* PMU res upकरोwn समयr */
#घोषणा SSB_CHIPCO_PMU_RES_TIMER		0x062C /* PMU res समयr */
#घोषणा SSB_CHIPCO_PMU_CLKSTRETCH		0x0630 /* PMU घड़ीstretch */
#घोषणा SSB_CHIPCO_PMU_WATCHDOG			0x0634 /* PMU watchकरोg */
#घोषणा SSB_CHIPCO_PMU_RES_REQTS		0x0640 /* PMU res req समयr sel */
#घोषणा SSB_CHIPCO_PMU_RES_REQT			0x0644 /* PMU res req समयr */
#घोषणा SSB_CHIPCO_PMU_RES_REQM			0x0648 /* PMU res req mask */
#घोषणा SSB_CHIPCO_CHIPCTL_ADDR			0x0650
#घोषणा SSB_CHIPCO_CHIPCTL_DATA			0x0654
#घोषणा SSB_CHIPCO_REGCTL_ADDR			0x0658
#घोषणा SSB_CHIPCO_REGCTL_DATA			0x065C
#घोषणा SSB_CHIPCO_PLLCTL_ADDR			0x0660
#घोषणा SSB_CHIPCO_PLLCTL_DATA			0x0664



/** PMU PLL रेजिस्टरs */

/* PMU rev 0 PLL रेजिस्टरs */
#घोषणा SSB_PMU0_PLLCTL0			0
#घोषणा  SSB_PMU0_PLLCTL0_PDIV_MSK		0x00000001
#घोषणा  SSB_PMU0_PLLCTL0_PDIV_FREQ		25000 /* kHz */
#घोषणा SSB_PMU0_PLLCTL1			1
#घोषणा  SSB_PMU0_PLLCTL1_WILD_IMSK		0xF0000000 /* Wild पूर्णांक mask (low nibble) */
#घोषणा  SSB_PMU0_PLLCTL1_WILD_IMSK_SHIFT	28
#घोषणा  SSB_PMU0_PLLCTL1_WILD_FMSK		0x0FFFFF00 /* Wild frac mask */
#घोषणा  SSB_PMU0_PLLCTL1_WILD_FMSK_SHIFT	8
#घोषणा  SSB_PMU0_PLLCTL1_STOPMOD		0x00000040 /* Stop mod */
#घोषणा SSB_PMU0_PLLCTL2			2
#घोषणा  SSB_PMU0_PLLCTL2_WILD_IMSKHI		0x0000000F /* Wild पूर्णांक mask (high nibble) */
#घोषणा  SSB_PMU0_PLLCTL2_WILD_IMSKHI_SHIFT	0

/* PMU rev 1 PLL रेजिस्टरs */
#घोषणा SSB_PMU1_PLLCTL0			0
#घोषणा  SSB_PMU1_PLLCTL0_P1DIV			0x00F00000 /* P1 भाग */
#घोषणा  SSB_PMU1_PLLCTL0_P1DIV_SHIFT		20
#घोषणा  SSB_PMU1_PLLCTL0_P2DIV			0x0F000000 /* P2 भाग */
#घोषणा  SSB_PMU1_PLLCTL0_P2DIV_SHIFT		24
#घोषणा SSB_PMU1_PLLCTL1			1
#घोषणा  SSB_PMU1_PLLCTL1_M1DIV			0x000000FF /* M1 भाग */
#घोषणा  SSB_PMU1_PLLCTL1_M1DIV_SHIFT		0
#घोषणा  SSB_PMU1_PLLCTL1_M2DIV			0x0000FF00 /* M2 भाग */
#घोषणा  SSB_PMU1_PLLCTL1_M2DIV_SHIFT		8
#घोषणा  SSB_PMU1_PLLCTL1_M3DIV			0x00FF0000 /* M3 भाग */
#घोषणा  SSB_PMU1_PLLCTL1_M3DIV_SHIFT		16
#घोषणा  SSB_PMU1_PLLCTL1_M4DIV			0xFF000000 /* M4 भाग */
#घोषणा  SSB_PMU1_PLLCTL1_M4DIV_SHIFT		24
#घोषणा SSB_PMU1_PLLCTL2			2
#घोषणा  SSB_PMU1_PLLCTL2_M5DIV			0x000000FF /* M5 भाग */
#घोषणा  SSB_PMU1_PLLCTL2_M5DIV_SHIFT		0
#घोषणा  SSB_PMU1_PLLCTL2_M6DIV			0x0000FF00 /* M6 भाग */
#घोषणा  SSB_PMU1_PLLCTL2_M6DIV_SHIFT		8
#घोषणा  SSB_PMU1_PLLCTL2_NDIVMODE		0x000E0000 /* NDIV mode */
#घोषणा  SSB_PMU1_PLLCTL2_NDIVMODE_SHIFT	17
#घोषणा  SSB_PMU1_PLLCTL2_NDIVINT		0x1FF00000 /* NDIV पूर्णांक */
#घोषणा  SSB_PMU1_PLLCTL2_NDIVINT_SHIFT		20
#घोषणा SSB_PMU1_PLLCTL3			3
#घोषणा  SSB_PMU1_PLLCTL3_NDIVFRAC		0x00FFFFFF /* NDIV frac */
#घोषणा  SSB_PMU1_PLLCTL3_NDIVFRAC_SHIFT	0
#घोषणा SSB_PMU1_PLLCTL4			4
#घोषणा SSB_PMU1_PLLCTL5			5
#घोषणा  SSB_PMU1_PLLCTL5_CLKDRV		0xFFFFFF00 /* clk drv */
#घोषणा  SSB_PMU1_PLLCTL5_CLKDRV_SHIFT		8

/* BCM4312 PLL resource numbers. */
#घोषणा SSB_PMURES_4312_SWITCHER_BURST		0
#घोषणा SSB_PMURES_4312_SWITCHER_PWM    	1
#घोषणा SSB_PMURES_4312_PA_REF_LDO		2
#घोषणा SSB_PMURES_4312_CORE_LDO_BURST		3
#घोषणा SSB_PMURES_4312_CORE_LDO_PWM		4
#घोषणा SSB_PMURES_4312_RADIO_LDO		5
#घोषणा SSB_PMURES_4312_ILP_REQUEST		6
#घोषणा SSB_PMURES_4312_BG_FILTBYP		7
#घोषणा SSB_PMURES_4312_TX_FILTBYP		8
#घोषणा SSB_PMURES_4312_RX_FILTBYP		9
#घोषणा SSB_PMURES_4312_XTAL_PU			10
#घोषणा SSB_PMURES_4312_ALP_AVAIL		11
#घोषणा SSB_PMURES_4312_BB_PLL_FILTBYP		12
#घोषणा SSB_PMURES_4312_RF_PLL_FILTBYP		13
#घोषणा SSB_PMURES_4312_HT_AVAIL		14

/* BCM4325 PLL resource numbers. */
#घोषणा SSB_PMURES_4325_BUCK_BOOST_BURST	0
#घोषणा SSB_PMURES_4325_CBUCK_BURST		1
#घोषणा SSB_PMURES_4325_CBUCK_PWM		2
#घोषणा SSB_PMURES_4325_CLDO_CBUCK_BURST	3
#घोषणा SSB_PMURES_4325_CLDO_CBUCK_PWM		4
#घोषणा SSB_PMURES_4325_BUCK_BOOST_PWM		5
#घोषणा SSB_PMURES_4325_ILP_REQUEST		6
#घोषणा SSB_PMURES_4325_ABUCK_BURST		7
#घोषणा SSB_PMURES_4325_ABUCK_PWM		8
#घोषणा SSB_PMURES_4325_LNLDO1_PU		9
#घोषणा SSB_PMURES_4325_LNLDO2_PU		10
#घोषणा SSB_PMURES_4325_LNLDO3_PU		11
#घोषणा SSB_PMURES_4325_LNLDO4_PU		12
#घोषणा SSB_PMURES_4325_XTAL_PU			13
#घोषणा SSB_PMURES_4325_ALP_AVAIL		14
#घोषणा SSB_PMURES_4325_RX_PWRSW_PU		15
#घोषणा SSB_PMURES_4325_TX_PWRSW_PU		16
#घोषणा SSB_PMURES_4325_RFPLL_PWRSW_PU		17
#घोषणा SSB_PMURES_4325_LOGEN_PWRSW_PU		18
#घोषणा SSB_PMURES_4325_AFE_PWRSW_PU		19
#घोषणा SSB_PMURES_4325_BBPLL_PWRSW_PU		20
#घोषणा SSB_PMURES_4325_HT_AVAIL		21

/* BCM4328 PLL resource numbers. */
#घोषणा SSB_PMURES_4328_EXT_SWITCHER_PWM	0
#घोषणा SSB_PMURES_4328_BB_SWITCHER_PWM		1
#घोषणा SSB_PMURES_4328_BB_SWITCHER_BURST	2
#घोषणा SSB_PMURES_4328_BB_EXT_SWITCHER_BURST	3
#घोषणा SSB_PMURES_4328_ILP_REQUEST		4
#घोषणा SSB_PMURES_4328_RADIO_SWITCHER_PWM	5
#घोषणा SSB_PMURES_4328_RADIO_SWITCHER_BURST	6
#घोषणा SSB_PMURES_4328_ROM_SWITCH		7
#घोषणा SSB_PMURES_4328_PA_REF_LDO		8
#घोषणा SSB_PMURES_4328_RADIO_LDO		9
#घोषणा SSB_PMURES_4328_AFE_LDO			10
#घोषणा SSB_PMURES_4328_PLL_LDO			11
#घोषणा SSB_PMURES_4328_BG_FILTBYP		12
#घोषणा SSB_PMURES_4328_TX_FILTBYP		13
#घोषणा SSB_PMURES_4328_RX_FILTBYP		14
#घोषणा SSB_PMURES_4328_XTAL_PU			15
#घोषणा SSB_PMURES_4328_XTAL_EN			16
#घोषणा SSB_PMURES_4328_BB_PLL_FILTBYP		17
#घोषणा SSB_PMURES_4328_RF_PLL_FILTBYP		18
#घोषणा SSB_PMURES_4328_BB_PLL_PU		19

/* BCM5354 PLL resource numbers. */
#घोषणा SSB_PMURES_5354_EXT_SWITCHER_PWM	0
#घोषणा SSB_PMURES_5354_BB_SWITCHER_PWM		1
#घोषणा SSB_PMURES_5354_BB_SWITCHER_BURST	2
#घोषणा SSB_PMURES_5354_BB_EXT_SWITCHER_BURST	3
#घोषणा SSB_PMURES_5354_ILP_REQUEST		4
#घोषणा SSB_PMURES_5354_RADIO_SWITCHER_PWM	5
#घोषणा SSB_PMURES_5354_RADIO_SWITCHER_BURST	6
#घोषणा SSB_PMURES_5354_ROM_SWITCH		7
#घोषणा SSB_PMURES_5354_PA_REF_LDO		8
#घोषणा SSB_PMURES_5354_RADIO_LDO		9
#घोषणा SSB_PMURES_5354_AFE_LDO			10
#घोषणा SSB_PMURES_5354_PLL_LDO			11
#घोषणा SSB_PMURES_5354_BG_FILTBYP		12
#घोषणा SSB_PMURES_5354_TX_FILTBYP		13
#घोषणा SSB_PMURES_5354_RX_FILTBYP		14
#घोषणा SSB_PMURES_5354_XTAL_PU			15
#घोषणा SSB_PMURES_5354_XTAL_EN			16
#घोषणा SSB_PMURES_5354_BB_PLL_FILTBYP		17
#घोषणा SSB_PMURES_5354_RF_PLL_FILTBYP		18
#घोषणा SSB_PMURES_5354_BB_PLL_PU		19



/** Chip specअगरic Chip-Status रेजिस्टर contents. */
#घोषणा SSB_CHIPCO_CHST_4322_SPROM_EXISTS	0x00000040 /* SPROM present */
#घोषणा SSB_CHIPCO_CHST_4325_SPROM_OTP_SEL	0x00000003
#घोषणा SSB_CHIPCO_CHST_4325_DEFCIS_SEL		0 /* OTP is घातered up, use def. CIS, no SPROM */
#घोषणा SSB_CHIPCO_CHST_4325_SPROM_SEL		1 /* OTP is घातered up, SPROM is present */
#घोषणा SSB_CHIPCO_CHST_4325_OTP_SEL		2 /* OTP is घातered up, no SPROM */
#घोषणा SSB_CHIPCO_CHST_4325_OTP_PWRDN		3 /* OTP is घातered करोwn, SPROM is present */
#घोषणा SSB_CHIPCO_CHST_4325_SDIO_USB_MODE	0x00000004
#घोषणा SSB_CHIPCO_CHST_4325_SDIO_USB_MODE_SHIFT  2
#घोषणा SSB_CHIPCO_CHST_4325_RCAL_VALID		0x00000008
#घोषणा SSB_CHIPCO_CHST_4325_RCAL_VALID_SHIFT	3
#घोषणा SSB_CHIPCO_CHST_4325_RCAL_VALUE		0x000001F0
#घोषणा SSB_CHIPCO_CHST_4325_RCAL_VALUE_SHIFT	4
#घोषणा SSB_CHIPCO_CHST_4325_PMUTOP_2B 		0x00000200 /* 1 क्रम 2b, 0 क्रम to 2a */

/** Macros to determine SPROM presence based on Chip-Status रेजिस्टर. */
#घोषणा SSB_CHIPCO_CHST_4312_SPROM_PRESENT(status) \
	((status & SSB_CHIPCO_CHST_4325_SPROM_OTP_SEL) != \
		SSB_CHIPCO_CHST_4325_OTP_SEL)
#घोषणा SSB_CHIPCO_CHST_4322_SPROM_PRESENT(status) \
	(status & SSB_CHIPCO_CHST_4322_SPROM_EXISTS)
#घोषणा SSB_CHIPCO_CHST_4325_SPROM_PRESENT(status) \
	(((status & SSB_CHIPCO_CHST_4325_SPROM_OTP_SEL) != \
		SSB_CHIPCO_CHST_4325_DEFCIS_SEL) && \
	 ((status & SSB_CHIPCO_CHST_4325_SPROM_OTP_SEL) != \
		SSB_CHIPCO_CHST_4325_OTP_SEL))



/** Clockcontrol masks and values **/

/* SSB_CHIPCO_CLOCK_N */
#घोषणा	SSB_CHIPCO_CLK_N1		0x0000003F	/* n1 control */
#घोषणा	SSB_CHIPCO_CLK_N2		0x00003F00	/* n2 control */
#घोषणा	SSB_CHIPCO_CLK_N2_SHIFT		8
#घोषणा	SSB_CHIPCO_CLK_PLLC		0x000F0000	/* pll control */
#घोषणा	SSB_CHIPCO_CLK_PLLC_SHIFT	16

/* SSB_CHIPCO_CLOCK_SB/PCI/UART */
#घोषणा	SSB_CHIPCO_CLK_M1		0x0000003F	/* m1 control */
#घोषणा	SSB_CHIPCO_CLK_M2		0x00003F00	/* m2 control */
#घोषणा	SSB_CHIPCO_CLK_M2_SHIFT		8
#घोषणा	SSB_CHIPCO_CLK_M3		0x003F0000	/* m3 control */
#घोषणा	SSB_CHIPCO_CLK_M3_SHIFT		16
#घोषणा	SSB_CHIPCO_CLK_MC		0x1F000000	/* mux control */
#घोषणा	SSB_CHIPCO_CLK_MC_SHIFT		24

/* N3M Clock control magic field values */
#घोषणा	SSB_CHIPCO_CLK_F6_2		0x02		/* A factor of 2 in */
#घोषणा	SSB_CHIPCO_CLK_F6_3		0x03		/* 6-bit fields like */
#घोषणा	SSB_CHIPCO_CLK_F6_4		0x05		/* N1, M1 or M3 */
#घोषणा	SSB_CHIPCO_CLK_F6_5		0x09
#घोषणा	SSB_CHIPCO_CLK_F6_6		0x11
#घोषणा	SSB_CHIPCO_CLK_F6_7		0x21

#घोषणा	SSB_CHIPCO_CLK_F5_BIAS		5		/* 5-bit fields get this added */

#घोषणा	SSB_CHIPCO_CLK_MC_BYPASS	0x08
#घोषणा	SSB_CHIPCO_CLK_MC_M1		0x04
#घोषणा	SSB_CHIPCO_CLK_MC_M1M2		0x02
#घोषणा	SSB_CHIPCO_CLK_MC_M1M2M3	0x01
#घोषणा	SSB_CHIPCO_CLK_MC_M1M3		0x11

/* Type 2 Clock control magic field values */
#घोषणा	SSB_CHIPCO_CLK_T2_BIAS		2		/* n1, n2, m1 & m3 bias */
#घोषणा	SSB_CHIPCO_CLK_T2M2_BIAS	3		/* m2 bias */

#घोषणा	SSB_CHIPCO_CLK_T2MC_M1BYP	1
#घोषणा	SSB_CHIPCO_CLK_T2MC_M2BYP	2
#घोषणा	SSB_CHIPCO_CLK_T2MC_M3BYP	4

/* Type 6 Clock control magic field values */
#घोषणा	SSB_CHIPCO_CLK_T6_MMASK		1		/* bits of पूर्णांकerest in m */
#घोषणा	SSB_CHIPCO_CLK_T6_M0		120000000	/* sb घड़ी क्रम m = 0 */
#घोषणा	SSB_CHIPCO_CLK_T6_M1		100000000	/* sb घड़ी क्रम m = 1 */
#घोषणा	SSB_CHIPCO_CLK_SB2MIPS_T6(sb)	(2 * (sb))

/* Common घड़ी base */
#घोषणा	SSB_CHIPCO_CLK_BASE1		24000000	/* Half the घड़ी freq */
#घोषणा SSB_CHIPCO_CLK_BASE2		12500000	/* Alternate crystal on some PLL's */

/* Clock control values क्रम 200Mhz in 5350 */
#घोषणा	SSB_CHIPCO_CLK_5350_N		0x0311
#घोषणा	SSB_CHIPCO_CLK_5350_M		0x04020009


/** Bits in the config रेजिस्टरs **/

#घोषणा	SSB_CHIPCO_CFG_EN		0x0001		/* Enable */
#घोषणा	SSB_CHIPCO_CFG_EXTM		0x000E		/* Extअगर Mode */
#घोषणा	 SSB_CHIPCO_CFG_EXTM_ASYNC	0x0002		/* Async/Parallel flash */
#घोषणा	 SSB_CHIPCO_CFG_EXTM_SYNC	0x0004		/* Synchronous */
#घोषणा	 SSB_CHIPCO_CFG_EXTM_PCMCIA	0x0008		/* PCMCIA */
#घोषणा	 SSB_CHIPCO_CFG_EXTM_IDE	0x000A		/* IDE */
#घोषणा	SSB_CHIPCO_CFG_DS16		0x0010		/* Data size, 0=8bit, 1=16bit */
#घोषणा	SSB_CHIPCO_CFG_CLKDIV		0x0060		/* Sync: Clock भागisor */
#घोषणा	SSB_CHIPCO_CFG_CLKEN		0x0080		/* Sync: Clock enable */
#घोषणा	SSB_CHIPCO_CFG_BSTRO		0x0100		/* Sync: Size/Bytestrobe */


/** Flash-specअगरic control/status values */

/* flashcontrol opcodes क्रम ST flashes */
#घोषणा SSB_CHIPCO_FLASHCTL_ST_WREN	0x0006		/* Write Enable */
#घोषणा SSB_CHIPCO_FLASHCTL_ST_WRDIS	0x0004		/* Write Disable */
#घोषणा SSB_CHIPCO_FLASHCTL_ST_RDSR	0x0105		/* Read Status Register */
#घोषणा SSB_CHIPCO_FLASHCTL_ST_WRSR	0x0101		/* Write Status Register */
#घोषणा SSB_CHIPCO_FLASHCTL_ST_READ	0x0303		/* Read Data Bytes */
#घोषणा SSB_CHIPCO_FLASHCTL_ST_PP	0x0302		/* Page Program */
#घोषणा SSB_CHIPCO_FLASHCTL_ST_SE	0x02D8		/* Sector Erase */
#घोषणा SSB_CHIPCO_FLASHCTL_ST_BE	0x00C7		/* Bulk Erase */
#घोषणा SSB_CHIPCO_FLASHCTL_ST_DP	0x00B9		/* Deep Power-करोwn */
#घोषणा SSB_CHIPCO_FLASHCTL_ST_RES	0x03AB		/* Read Electronic Signature */
#घोषणा SSB_CHIPCO_FLASHCTL_ST_CSA	0x1000		/* Keep chip select निश्चितed */
#घोषणा SSB_CHIPCO_FLASHCTL_ST_SSE	0x0220		/* Sub-sector Erase */

/* Status रेजिस्टर bits क्रम ST flashes */
#घोषणा SSB_CHIPCO_FLASHSTA_ST_WIP	0x01		/* Write In Progress */
#घोषणा SSB_CHIPCO_FLASHSTA_ST_WEL	0x02		/* Write Enable Latch */
#घोषणा SSB_CHIPCO_FLASHSTA_ST_BP	0x1C		/* Block Protect */
#घोषणा SSB_CHIPCO_FLASHSTA_ST_BP_SHIFT	2
#घोषणा SSB_CHIPCO_FLASHSTA_ST_SRWD	0x80		/* Status Register Write Disable */

/* flashcontrol opcodes क्रम Aपंचांगel flashes */
#घोषणा SSB_CHIPCO_FLASHCTL_AT_READ		0x07E8
#घोषणा SSB_CHIPCO_FLASHCTL_AT_PAGE_READ	0x07D2
#घोषणा SSB_CHIPCO_FLASHCTL_AT_BUF1_READ	/* FIXME */
#घोषणा SSB_CHIPCO_FLASHCTL_AT_BUF2_READ	/* FIXME */
#घोषणा SSB_CHIPCO_FLASHCTL_AT_STATUS		0x01D7
#घोषणा SSB_CHIPCO_FLASHCTL_AT_BUF1_WRITE	0x0384
#घोषणा SSB_CHIPCO_FLASHCTL_AT_BUF2_WRITE	0x0387
#घोषणा SSB_CHIPCO_FLASHCTL_AT_BUF1_ERASE_PRGM	0x0283	/* Erase program */
#घोषणा SSB_CHIPCO_FLASHCTL_AT_BUF2_ERASE_PRGM	0x0286	/* Erase program */
#घोषणा SSB_CHIPCO_FLASHCTL_AT_BUF1_PROGRAM	0x0288
#घोषणा SSB_CHIPCO_FLASHCTL_AT_BUF2_PROGRAM	0x0289
#घोषणा SSB_CHIPCO_FLASHCTL_AT_PAGE_ERASE	0x0281
#घोषणा SSB_CHIPCO_FLASHCTL_AT_BLOCK_ERASE	0x0250
#घोषणा SSB_CHIPCO_FLASHCTL_AT_BUF1_WRER_PRGM	0x0382	/* Write erase program */
#घोषणा SSB_CHIPCO_FLASHCTL_AT_BUF2_WRER_PRGM	0x0385	/* Write erase program */
#घोषणा SSB_CHIPCO_FLASHCTL_AT_BUF1_LOAD	0x0253
#घोषणा SSB_CHIPCO_FLASHCTL_AT_BUF2_LOAD	0x0255
#घोषणा SSB_CHIPCO_FLASHCTL_AT_BUF1_COMPARE	0x0260
#घोषणा SSB_CHIPCO_FLASHCTL_AT_BUF2_COMPARE	0x0261
#घोषणा SSB_CHIPCO_FLASHCTL_AT_BUF1_REPROGRAM	0x0258
#घोषणा SSB_CHIPCO_FLASHCTL_AT_BUF2_REPROGRAM	0x0259

/* Status रेजिस्टर bits क्रम Aपंचांगel flashes */
#घोषणा SSB_CHIPCO_FLASHSTA_AT_READY	0x80
#घोषणा SSB_CHIPCO_FLASHSTA_AT_MISMATCH	0x40
#घोषणा SSB_CHIPCO_FLASHSTA_AT_ID	0x38
#घोषणा SSB_CHIPCO_FLASHSTA_AT_ID_SHIFT	3


/** OTP **/

/* OTP regions */
#घोषणा	SSB_CHIPCO_OTP_HW_REGION	SSB_CHIPCO_OTPS_HW_PROTECT
#घोषणा	SSB_CHIPCO_OTP_SW_REGION	SSB_CHIPCO_OTPS_SW_PROTECT
#घोषणा	SSB_CHIPCO_OTP_CID_REGION	SSB_CHIPCO_OTPS_CID_PROTECT

/* OTP regions (Byte offsets from otp size) */
#घोषणा	SSB_CHIPCO_OTP_SWLIM_OFF	(-8)
#घोषणा	SSB_CHIPCO_OTP_CIDBASE_OFF	0
#घोषणा	SSB_CHIPCO_OTP_CIDLIM_OFF	8

/* Predefined OTP words (Word offset from otp size) */
#घोषणा	SSB_CHIPCO_OTP_BOUNDARY_OFF	(-4)
#घोषणा	SSB_CHIPCO_OTP_HWSIGN_OFF	(-3)
#घोषणा	SSB_CHIPCO_OTP_SWSIGN_OFF	(-2)
#घोषणा	SSB_CHIPCO_OTP_CIDSIGN_OFF	(-1)

#घोषणा	SSB_CHIPCO_OTP_CID_OFF		0
#घोषणा	SSB_CHIPCO_OTP_PKG_OFF		1
#घोषणा	SSB_CHIPCO_OTP_FID_OFF		2
#घोषणा	SSB_CHIPCO_OTP_RSV_OFF		3
#घोषणा	SSB_CHIPCO_OTP_LIM_OFF		4

#घोषणा	SSB_CHIPCO_OTP_SIGNATURE	0x578A
#घोषणा	SSB_CHIPCO_OTP_MAGIC		0x4E56


काष्ठा ssb_device;
काष्ठा ssb_serial_port;

/* Data क्रम the PMU, अगर available.
 * Check availability with ((काष्ठा ssb_chipcommon)->capabilities & SSB_CHIPCO_CAP_PMU)
 */
काष्ठा ssb_chipcommon_pmu अणु
	u8 rev;			/* PMU revision */
	u32 crystalfreq;	/* The active crystal frequency (in kHz) */
पूर्ण;

काष्ठा ssb_chipcommon अणु
	काष्ठा ssb_device *dev;
	u32 capabilities;
	u32 status;
	/* Fast Powerup Delay स्थिरant */
	u16 fast_pwrup_delay;
	spinlock_t gpio_lock;
	काष्ठा ssb_chipcommon_pmu pmu;
	u32 ticks_per_ms;
	u32 max_समयr_ms;
पूर्ण;

अटल अंतरभूत bool ssb_chipco_available(काष्ठा ssb_chipcommon *cc)
अणु
	वापस (cc->dev != शून्य);
पूर्ण

/* Register access */
#घोषणा chipco_पढ़ो32(cc, offset)	ssb_पढ़ो32((cc)->dev, offset)
#घोषणा chipco_ग_लिखो32(cc, offset, val)	ssb_ग_लिखो32((cc)->dev, offset, val)

#घोषणा chipco_mask32(cc, offset, mask) \
		chipco_ग_लिखो32(cc, offset, chipco_पढ़ो32(cc, offset) & (mask))
#घोषणा chipco_set32(cc, offset, set) \
		chipco_ग_लिखो32(cc, offset, chipco_पढ़ो32(cc, offset) | (set))
#घोषणा chipco_maskset32(cc, offset, mask, set) \
		chipco_ग_लिखो32(cc, offset, (chipco_पढ़ो32(cc, offset) & (mask)) | (set))

बाह्य व्योम ssb_chipcommon_init(काष्ठा ssb_chipcommon *cc);

बाह्य व्योम ssb_chipco_suspend(काष्ठा ssb_chipcommon *cc);
बाह्य व्योम ssb_chipco_resume(काष्ठा ssb_chipcommon *cc);

बाह्य व्योम ssb_chipco_get_घड़ीcpu(काष्ठा ssb_chipcommon *cc,
                                    u32 *plltype, u32 *n, u32 *m);
बाह्य व्योम ssb_chipco_get_घड़ीcontrol(काष्ठा ssb_chipcommon *cc,
					u32 *plltype, u32 *n, u32 *m);
बाह्य व्योम ssb_chipco_timing_init(काष्ठा ssb_chipcommon *cc,
				   अचिन्हित दीर्घ ns_per_cycle);

क्रमागत ssb_clkmode अणु
	SSB_CLKMODE_SLOW,
	SSB_CLKMODE_FAST,
	SSB_CLKMODE_DYNAMIC,
पूर्ण;

बाह्य व्योम ssb_chipco_set_घड़ीmode(काष्ठा ssb_chipcommon *cc,
				     क्रमागत ssb_clkmode mode);

बाह्य u32 ssb_chipco_watchकरोg_समयr_set(काष्ठा ssb_chipcommon *cc, u32 ticks);

व्योम ssb_chipco_irq_mask(काष्ठा ssb_chipcommon *cc, u32 mask, u32 value);

u32 ssb_chipco_irq_status(काष्ठा ssb_chipcommon *cc, u32 mask);

/* Chipcommon GPIO pin access. */
u32 ssb_chipco_gpio_in(काष्ठा ssb_chipcommon *cc, u32 mask);
u32 ssb_chipco_gpio_out(काष्ठा ssb_chipcommon *cc, u32 mask, u32 value);
u32 ssb_chipco_gpio_outen(काष्ठा ssb_chipcommon *cc, u32 mask, u32 value);
u32 ssb_chipco_gpio_control(काष्ठा ssb_chipcommon *cc, u32 mask, u32 value);
u32 ssb_chipco_gpio_पूर्णांकmask(काष्ठा ssb_chipcommon *cc, u32 mask, u32 value);
u32 ssb_chipco_gpio_polarity(काष्ठा ssb_chipcommon *cc, u32 mask, u32 value);
u32 ssb_chipco_gpio_pullup(काष्ठा ssb_chipcommon *cc, u32 mask, u32 value);
u32 ssb_chipco_gpio_pullकरोwn(काष्ठा ssb_chipcommon *cc, u32 mask, u32 value);

#अगर_घोषित CONFIG_SSB_SERIAL
बाह्य पूर्णांक ssb_chipco_serial_init(काष्ठा ssb_chipcommon *cc,
				  काष्ठा ssb_serial_port *ports);
#पूर्ण_अगर /* CONFIG_SSB_SERIAL */

/* PMU support */
बाह्य व्योम ssb_pmu_init(काष्ठा ssb_chipcommon *cc);

क्रमागत ssb_pmu_lकरो_volt_id अणु
	LDO_PAREF = 0,
	LDO_VOLT1,
	LDO_VOLT2,
	LDO_VOLT3,
पूर्ण;

व्योम ssb_pmu_set_lकरो_voltage(काष्ठा ssb_chipcommon *cc,
			     क्रमागत ssb_pmu_lकरो_volt_id id, u32 voltage);
व्योम ssb_pmu_set_lकरो_paref(काष्ठा ssb_chipcommon *cc, bool on);
व्योम ssb_pmu_spuraव्योम_pllupdate(काष्ठा ssb_chipcommon *cc, पूर्णांक spuraव्योम);

#पूर्ण_अगर /* LINUX_SSB_CHIPCO_H_ */
