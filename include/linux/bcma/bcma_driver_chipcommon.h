<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_BCMA_DRIVER_CC_H_
#घोषणा LINUX_BCMA_DRIVER_CC_H_

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpपन.स>

/** ChipCommon core रेजिस्टरs. **/
#घोषणा BCMA_CC_ID			0x0000
#घोषणा  BCMA_CC_ID_ID			0x0000FFFF
#घोषणा  BCMA_CC_ID_ID_SHIFT		0
#घोषणा  BCMA_CC_ID_REV			0x000F0000
#घोषणा  BCMA_CC_ID_REV_SHIFT		16
#घोषणा  BCMA_CC_ID_PKG			0x00F00000
#घोषणा  BCMA_CC_ID_PKG_SHIFT		20
#घोषणा  BCMA_CC_ID_NRCORES		0x0F000000
#घोषणा  BCMA_CC_ID_NRCORES_SHIFT	24
#घोषणा  BCMA_CC_ID_TYPE		0xF0000000
#घोषणा  BCMA_CC_ID_TYPE_SHIFT		28
#घोषणा BCMA_CC_CAP			0x0004		/* Capabilities */
#घोषणा  BCMA_CC_CAP_NRUART		0x00000003	/* # of UARTs */
#घोषणा  BCMA_CC_CAP_MIPSEB		0x00000004	/* MIPS in BigEndian Mode */
#घोषणा  BCMA_CC_CAP_UARTCLK		0x00000018	/* UART घड़ी select */
#घोषणा   BCMA_CC_CAP_UARTCLK_INT	0x00000008	/* UARTs are driven by पूर्णांकernal भागided घड़ी */
#घोषणा  BCMA_CC_CAP_UARTGPIO		0x00000020	/* UARTs on GPIO 15-12 */
#घोषणा  BCMA_CC_CAP_EXTBUS		0x000000C0	/* External buses present */
#घोषणा  BCMA_CC_CAP_FLASHT		0x00000700	/* Flash Type */
#घोषणा   BCMA_CC_FLASHT_NONE		0x00000000	/* No flash */
#घोषणा   BCMA_CC_FLASHT_STSER		0x00000100	/* ST serial flash */
#घोषणा   BCMA_CC_FLASHT_ATSER		0x00000200	/* Aपंचांगel serial flash */
#घोषणा   BCMA_CC_FLASHT_न_अंकD		0x00000300	/* न_अंकD flash */
#घोषणा	  BCMA_CC_FLASHT_PARA		0x00000700	/* Parallel flash */
#घोषणा  BCMA_CC_CAP_PLLT		0x00038000	/* PLL Type */
#घोषणा   BCMA_PLLTYPE_NONE		0x00000000
#घोषणा   BCMA_PLLTYPE_1		0x00010000	/* 48Mhz base, 3 भागiders */
#घोषणा   BCMA_PLLTYPE_2		0x00020000	/* 48Mhz, 4 भागiders */
#घोषणा   BCMA_PLLTYPE_3		0x00030000	/* 25Mhz, 2 भागiders */
#घोषणा   BCMA_PLLTYPE_4		0x00008000	/* 48Mhz, 4 भागiders */
#घोषणा   BCMA_PLLTYPE_5		0x00018000	/* 25Mhz, 4 भागiders */
#घोषणा   BCMA_PLLTYPE_6		0x00028000	/* 100/200 or 120/240 only */
#घोषणा   BCMA_PLLTYPE_7		0x00038000	/* 25Mhz, 4 भागiders */
#घोषणा  BCMA_CC_CAP_PCTL		0x00040000	/* Power Control */
#घोषणा  BCMA_CC_CAP_OTPS		0x00380000	/* OTP size */
#घोषणा  BCMA_CC_CAP_OTPS_SHIFT		19
#घोषणा  BCMA_CC_CAP_OTPS_BASE		5
#घोषणा  BCMA_CC_CAP_JTAGM		0x00400000	/* JTAG master present */
#घोषणा  BCMA_CC_CAP_BROM		0x00800000	/* Internal boot ROM active */
#घोषणा  BCMA_CC_CAP_64BIT		0x08000000	/* 64-bit Backplane */
#घोषणा  BCMA_CC_CAP_PMU		0x10000000	/* PMU available (rev >= 20) */
#घोषणा  BCMA_CC_CAP_ECI		0x20000000	/* ECI available (rev >= 20) */
#घोषणा  BCMA_CC_CAP_SPROM		0x40000000	/* SPROM present */
#घोषणा  BCMA_CC_CAP_NFLASH		0x80000000	/* न_अंकD flash present (rev >= 35 or BCM4706?) */
#घोषणा BCMA_CC_CORECTL			0x0008
#घोषणा  BCMA_CC_CORECTL_UARTCLK0	0x00000001	/* Drive UART with पूर्णांकernal घड़ी */
#घोषणा	 BCMA_CC_CORECTL_SE		0x00000002	/* sync clk out enable (corerev >= 3) */
#घोषणा  BCMA_CC_CORECTL_UARTCLKEN	0x00000008	/* UART घड़ी enable (rev >= 21) */
#घोषणा BCMA_CC_BIST			0x000C
#घोषणा BCMA_CC_OTPS			0x0010		/* OTP status */
#घोषणा	 BCMA_CC_OTPS_PROGFAIL		0x80000000
#घोषणा	 BCMA_CC_OTPS_PROTECT		0x00000007
#घोषणा	 BCMA_CC_OTPS_HW_PROTECT	0x00000001
#घोषणा	 BCMA_CC_OTPS_SW_PROTECT	0x00000002
#घोषणा	 BCMA_CC_OTPS_CID_PROTECT	0x00000004
#घोषणा  BCMA_CC_OTPS_GU_PROG_IND	0x00000F00	/* General Use programmed indication */
#घोषणा  BCMA_CC_OTPS_GU_PROG_IND_SHIFT	8
#घोषणा  BCMA_CC_OTPS_GU_PROG_HW	0x00000100	/* HW region programmed */
#घोषणा BCMA_CC_OTPC			0x0014		/* OTP control */
#घोषणा	 BCMA_CC_OTPC_RECWAIT		0xFF000000
#घोषणा	 BCMA_CC_OTPC_PROGWAIT		0x00FFFF00
#घोषणा	 BCMA_CC_OTPC_PRW_SHIFT		8
#घोषणा	 BCMA_CC_OTPC_MAXFAIL		0x00000038
#घोषणा	 BCMA_CC_OTPC_VSEL		0x00000006
#घोषणा	 BCMA_CC_OTPC_SELVL		0x00000001
#घोषणा BCMA_CC_OTPP			0x0018		/* OTP prog */
#घोषणा	 BCMA_CC_OTPP_COL		0x000000FF
#घोषणा	 BCMA_CC_OTPP_ROW		0x0000FF00
#घोषणा	 BCMA_CC_OTPP_ROW_SHIFT		8
#घोषणा	 BCMA_CC_OTPP_READERR		0x10000000
#घोषणा	 BCMA_CC_OTPP_VALUE		0x20000000
#घोषणा	 BCMA_CC_OTPP_READ		0x40000000
#घोषणा	 BCMA_CC_OTPP_START		0x80000000
#घोषणा	 BCMA_CC_OTPP_BUSY		0x80000000
#घोषणा BCMA_CC_OTPL			0x001C		/* OTP layout */
#घोषणा  BCMA_CC_OTPL_GURGN_OFFSET	0x00000FFF	/* offset of general use region */
#घोषणा BCMA_CC_IRQSTAT			0x0020
#घोषणा BCMA_CC_IRQMASK			0x0024
#घोषणा	 BCMA_CC_IRQ_GPIO		0x00000001	/* gpio पूर्णांकr */
#घोषणा	 BCMA_CC_IRQ_EXT		0x00000002	/* ro: ext पूर्णांकr pin (corerev >= 3) */
#घोषणा	 BCMA_CC_IRQ_WDRESET		0x80000000	/* watchकरोg reset occurred */
#घोषणा BCMA_CC_CHIPCTL			0x0028		/* Rev >= 11 only */
#घोषणा BCMA_CC_CHIPSTAT		0x002C		/* Rev >= 11 only */
#घोषणा  BCMA_CC_CHIPST_4313_SPROM_PRESENT	1
#घोषणा  BCMA_CC_CHIPST_4313_OTP_PRESENT	2
#घोषणा  BCMA_CC_CHIPST_4331_SPROM_PRESENT	2
#घोषणा  BCMA_CC_CHIPST_4331_OTP_PRESENT	4
#घोषणा  BCMA_CC_CHIPST_43228_ILP_DIV_EN	0x00000001
#घोषणा  BCMA_CC_CHIPST_43228_OTP_PRESENT	0x00000002
#घोषणा  BCMA_CC_CHIPST_43228_SERDES_REFCLK_PADSEL	0x00000004
#घोषणा  BCMA_CC_CHIPST_43228_SDIO_MODE		0x00000008
#घोषणा  BCMA_CC_CHIPST_43228_SDIO_OTP_PRESENT	0x00000010
#घोषणा  BCMA_CC_CHIPST_43228_SDIO_RESET	0x00000020
#घोषणा  BCMA_CC_CHIPST_4706_PKG_OPTION		BIT(0) /* 0: full-featured package 1: low-cost package */
#घोषणा  BCMA_CC_CHIPST_4706_SFLASH_PRESENT	BIT(1) /* 0: parallel, 1: serial flash is present */
#घोषणा  BCMA_CC_CHIPST_4706_SFLASH_TYPE	BIT(2) /* 0: 8b-p/ST-s flash, 1: 16b-p/Aपंचांगal-s flash */
#घोषणा  BCMA_CC_CHIPST_4706_MIPS_BENDIAN	BIT(3) /* 0: little, 1: big endian */
#घोषणा  BCMA_CC_CHIPST_4706_PCIE1_DISABLE	BIT(5) /* PCIE1 enable strap pin */
#घोषणा  BCMA_CC_CHIPST_5357_न_अंकD_BOOT		BIT(4) /* न_अंकD boot, valid क्रम CC rev 38 and/or BCM5357 */
#घोषणा  BCMA_CC_CHIPST_4360_XTAL_40MZ		0x00000001
#घोषणा BCMA_CC_JCMD			0x0030		/* Rev >= 10 only */
#घोषणा  BCMA_CC_JCMD_START		0x80000000
#घोषणा  BCMA_CC_JCMD_BUSY		0x80000000
#घोषणा  BCMA_CC_JCMD_PAUSE		0x40000000
#घोषणा  BCMA_CC_JCMD0_ACC_MASK		0x0000F000
#घोषणा  BCMA_CC_JCMD0_ACC_IRDR		0x00000000
#घोषणा  BCMA_CC_JCMD0_ACC_DR		0x00001000
#घोषणा  BCMA_CC_JCMD0_ACC_IR		0x00002000
#घोषणा  BCMA_CC_JCMD0_ACC_RESET	0x00003000
#घोषणा  BCMA_CC_JCMD0_ACC_IRPDR	0x00004000
#घोषणा  BCMA_CC_JCMD0_ACC_PDR		0x00005000
#घोषणा  BCMA_CC_JCMD0_IRW_MASK		0x00000F00
#घोषणा  BCMA_CC_JCMD_ACC_MASK		0x000F0000	/* Changes क्रम corerev 11 */
#घोषणा  BCMA_CC_JCMD_ACC_IRDR		0x00000000
#घोषणा  BCMA_CC_JCMD_ACC_DR		0x00010000
#घोषणा  BCMA_CC_JCMD_ACC_IR		0x00020000
#घोषणा  BCMA_CC_JCMD_ACC_RESET		0x00030000
#घोषणा  BCMA_CC_JCMD_ACC_IRPDR		0x00040000
#घोषणा  BCMA_CC_JCMD_ACC_PDR		0x00050000
#घोषणा  BCMA_CC_JCMD_IRW_MASK		0x00001F00
#घोषणा  BCMA_CC_JCMD_IRW_SHIFT		8
#घोषणा  BCMA_CC_JCMD_DRW_MASK		0x0000003F
#घोषणा BCMA_CC_JIR			0x0034		/* Rev >= 10 only */
#घोषणा BCMA_CC_JDR			0x0038		/* Rev >= 10 only */
#घोषणा BCMA_CC_JCTL			0x003C		/* Rev >= 10 only */
#घोषणा  BCMA_CC_JCTL_FORCE_CLK		4		/* Force घड़ी */
#घोषणा  BCMA_CC_JCTL_EXT_EN		2		/* Enable बाह्यal tarमाला_लो */
#घोषणा  BCMA_CC_JCTL_EN		1		/* Enable Jtag master */
#घोषणा BCMA_CC_FLASHCTL		0x0040
/* Start/busy bit in flashcontrol */
#घोषणा  BCMA_CC_FLASHCTL_OPCODE	0x000000ff
#घोषणा  BCMA_CC_FLASHCTL_ACTION	0x00000700
#घोषणा  BCMA_CC_FLASHCTL_CS_ACTIVE	0x00001000	/* Chip Select Active, rev >= 20 */
#घोषणा  BCMA_CC_FLASHCTL_START		0x80000000
#घोषणा  BCMA_CC_FLASHCTL_BUSY		BCMA_CC_FLASHCTL_START
/* Flashcontrol action + opcodes क्रम ST flashes */
#घोषणा  BCMA_CC_FLASHCTL_ST_WREN	0x0006		/* Write Enable */
#घोषणा  BCMA_CC_FLASHCTL_ST_WRDIS	0x0004		/* Write Disable */
#घोषणा  BCMA_CC_FLASHCTL_ST_RDSR	0x0105		/* Read Status Register */
#घोषणा  BCMA_CC_FLASHCTL_ST_WRSR	0x0101		/* Write Status Register */
#घोषणा  BCMA_CC_FLASHCTL_ST_READ	0x0303		/* Read Data Bytes */
#घोषणा  BCMA_CC_FLASHCTL_ST_PP		0x0302		/* Page Program */
#घोषणा  BCMA_CC_FLASHCTL_ST_SE		0x02d8		/* Sector Erase */
#घोषणा  BCMA_CC_FLASHCTL_ST_BE		0x00c7		/* Bulk Erase */
#घोषणा  BCMA_CC_FLASHCTL_ST_DP		0x00b9		/* Deep Power-करोwn */
#घोषणा  BCMA_CC_FLASHCTL_ST_RES	0x03ab		/* Read Electronic Signature */
#घोषणा  BCMA_CC_FLASHCTL_ST_CSA	0x1000		/* Keep chip select निश्चितed */
#घोषणा  BCMA_CC_FLASHCTL_ST_SSE	0x0220		/* Sub-sector Erase */
/* Flashcontrol action + opcodes क्रम Aपंचांगel flashes */
#घोषणा  BCMA_CC_FLASHCTL_AT_READ			0x07e8
#घोषणा  BCMA_CC_FLASHCTL_AT_PAGE_READ			0x07d2
#घोषणा  BCMA_CC_FLASHCTL_AT_STATUS			0x01d7
#घोषणा  BCMA_CC_FLASHCTL_AT_BUF1_WRITE			0x0384
#घोषणा  BCMA_CC_FLASHCTL_AT_BUF2_WRITE			0x0387
#घोषणा  BCMA_CC_FLASHCTL_AT_BUF1_ERASE_PROGRAM		0x0283
#घोषणा  BCMA_CC_FLASHCTL_AT_BUF2_ERASE_PROGRAM		0x0286
#घोषणा  BCMA_CC_FLASHCTL_AT_BUF1_PROGRAM		0x0288
#घोषणा  BCMA_CC_FLASHCTL_AT_BUF2_PROGRAM		0x0289
#घोषणा  BCMA_CC_FLASHCTL_AT_PAGE_ERASE			0x0281
#घोषणा  BCMA_CC_FLASHCTL_AT_BLOCK_ERASE		0x0250
#घोषणा  BCMA_CC_FLASHCTL_AT_BUF1_WRITE_ERASE_PROGRAM	0x0382
#घोषणा  BCMA_CC_FLASHCTL_AT_BUF2_WRITE_ERASE_PROGRAM	0x0385
#घोषणा  BCMA_CC_FLASHCTL_AT_BUF1_LOAD			0x0253
#घोषणा  BCMA_CC_FLASHCTL_AT_BUF2_LOAD			0x0255
#घोषणा  BCMA_CC_FLASHCTL_AT_BUF1_COMPARE		0x0260
#घोषणा  BCMA_CC_FLASHCTL_AT_BUF2_COMPARE		0x0261
#घोषणा  BCMA_CC_FLASHCTL_AT_BUF1_REPROGRAM		0x0258
#घोषणा  BCMA_CC_FLASHCTL_AT_BUF2_REPROGRAM		0x0259
#घोषणा BCMA_CC_FLASHADDR		0x0044
#घोषणा BCMA_CC_FLASHDATA		0x0048
/* Status रेजिस्टर bits क्रम ST flashes */
#घोषणा  BCMA_CC_FLASHDATA_ST_WIP	0x01		/* Write In Progress */
#घोषणा  BCMA_CC_FLASHDATA_ST_WEL	0x02		/* Write Enable Latch */
#घोषणा  BCMA_CC_FLASHDATA_ST_BP_MASK	0x1c		/* Block Protect */
#घोषणा  BCMA_CC_FLASHDATA_ST_BP_SHIFT	2
#घोषणा  BCMA_CC_FLASHDATA_ST_SRWD	0x80		/* Status Register Write Disable */
/* Status रेजिस्टर bits क्रम Aपंचांगel flashes */
#घोषणा  BCMA_CC_FLASHDATA_AT_READY	0x80
#घोषणा  BCMA_CC_FLASHDATA_AT_MISMATCH	0x40
#घोषणा  BCMA_CC_FLASHDATA_AT_ID_MASK	0x38
#घोषणा  BCMA_CC_FLASHDATA_AT_ID_SHIFT	3
#घोषणा BCMA_CC_BCAST_ADDR		0x0050
#घोषणा BCMA_CC_BCAST_DATA		0x0054
#घोषणा BCMA_CC_GPIOPULLUP		0x0058		/* Rev >= 20 only */
#घोषणा BCMA_CC_GPIOPULLDOWN		0x005C		/* Rev >= 20 only */
#घोषणा BCMA_CC_GPIOIN			0x0060
#घोषणा BCMA_CC_GPIOOUT			0x0064
#घोषणा BCMA_CC_GPIOOUTEN		0x0068
#घोषणा BCMA_CC_GPIOCTL			0x006C
#घोषणा BCMA_CC_GPIOPOL			0x0070
#घोषणा BCMA_CC_GPIOIRQ			0x0074
#घोषणा BCMA_CC_WATCHDOG		0x0080
#घोषणा BCMA_CC_GPIOTIMER		0x0088		/* LED घातersave (corerev >= 16) */
#घोषणा  BCMA_CC_GPIOTIMER_OFFTIME	0x0000FFFF
#घोषणा  BCMA_CC_GPIOTIMER_OFFTIME_SHIFT	0
#घोषणा  BCMA_CC_GPIOTIMER_ONTIME	0xFFFF0000
#घोषणा  BCMA_CC_GPIOTIMER_ONTIME_SHIFT	16
#घोषणा BCMA_CC_GPIOTOUTM		0x008C		/* LED घातersave (corerev >= 16) */
#घोषणा BCMA_CC_CLOCK_N			0x0090
#घोषणा BCMA_CC_CLOCK_SB		0x0094
#घोषणा BCMA_CC_CLOCK_PCI		0x0098
#घोषणा BCMA_CC_CLOCK_M2		0x009C
#घोषणा BCMA_CC_CLOCK_MIPS		0x00A0
#घोषणा BCMA_CC_CLKDIV			0x00A4		/* Rev >= 3 only */
#घोषणा	 BCMA_CC_CLKDIV_SFLASH		0x0F000000
#घोषणा	 BCMA_CC_CLKDIV_SFLASH_SHIFT	24
#घोषणा	 BCMA_CC_CLKDIV_OTP		0x000F0000
#घोषणा	 BCMA_CC_CLKDIV_OTP_SHIFT	16
#घोषणा	 BCMA_CC_CLKDIV_JTAG		0x00000F00
#घोषणा	 BCMA_CC_CLKDIV_JTAG_SHIFT	8
#घोषणा	 BCMA_CC_CLKDIV_UART		0x000000FF
#घोषणा BCMA_CC_CAP_EXT			0x00AC		/* Capabilities */
#घोषणा  BCMA_CC_CAP_EXT_SECI_PRESENT	0x00000001
#घोषणा  BCMA_CC_CAP_EXT_GSIO_PRESENT	0x00000002
#घोषणा  BCMA_CC_CAP_EXT_GCI_PRESENT	0x00000004
#घोषणा  BCMA_CC_CAP_EXT_SECI_PUART_PRESENT		0x00000008    /* UART present */
#घोषणा  BCMA_CC_CAP_EXT_AOB_PRESENT	0x00000040
#घोषणा BCMA_CC_PLLONDELAY		0x00B0		/* Rev >= 4 only */
#घोषणा BCMA_CC_FREFSELDELAY		0x00B4		/* Rev >= 4 only */
#घोषणा BCMA_CC_SLOWCLKCTL		0x00B8		/* 6 <= Rev <= 9 only */
#घोषणा  BCMA_CC_SLOWCLKCTL_SRC		0x00000007	/* slow घड़ी source mask */
#घोषणा	  BCMA_CC_SLOWCLKCTL_SRC_LPO	0x00000000	/* source of slow घड़ी is LPO */
#घोषणा   BCMA_CC_SLOWCLKCTL_SRC_XTAL	0x00000001	/* source of slow घड़ी is crystal */
#घोषणा	  BCMA_CC_SLOECLKCTL_SRC_PCI	0x00000002	/* source of slow घड़ी is PCI */
#घोषणा  BCMA_CC_SLOWCLKCTL_LPOFREQ	0x00000200	/* LPOFreqSel, 1: 160Khz, 0: 32KHz */
#घोषणा  BCMA_CC_SLOWCLKCTL_LPOPD	0x00000400	/* LPOPowerDown, 1: LPO is disabled, 0: LPO is enabled */
#घोषणा  BCMA_CC_SLOWCLKCTL_FSLOW	0x00000800	/* ForceSlowClk, 1: sb/cores running on slow घड़ी, 0: घातer logic control */
#घोषणा  BCMA_CC_SLOWCLKCTL_IPLL	0x00001000	/* IgnorePllOffReq, 1/0: घातer logic ignores/honors PLL घड़ी disable requests from core */
#घोषणा  BCMA_CC_SLOWCLKCTL_ENXTAL	0x00002000	/* XtalControlEn, 1/0: घातer logic करोes/करोesn't disable crystal when appropriate */
#घोषणा  BCMA_CC_SLOWCLKCTL_XTALPU	0x00004000	/* XtalPU (RO), 1/0: crystal running/disabled */
#घोषणा  BCMA_CC_SLOWCLKCTL_CLKDIV	0xFFFF0000	/* ClockDivider (SlowClk = 1/(4+भागisor)) */
#घोषणा  BCMA_CC_SLOWCLKCTL_CLKDIV_SHIFT	16
#घोषणा BCMA_CC_SYSCLKCTL		0x00C0		/* Rev >= 3 only */
#घोषणा	 BCMA_CC_SYSCLKCTL_IDLPEN	0x00000001	/* ILPen: Enable Idle Low Power */
#घोषणा	 BCMA_CC_SYSCLKCTL_ALPEN	0x00000002	/* ALPen: Enable Active Low Power */
#घोषणा	 BCMA_CC_SYSCLKCTL_PLLEN	0x00000004	/* ForcePLLOn */
#घोषणा	 BCMA_CC_SYSCLKCTL_FORCEALP	0x00000008	/* Force ALP (or HT अगर ALPen is not set */
#घोषणा	 BCMA_CC_SYSCLKCTL_FORCEHT	0x00000010	/* Force HT */
#घोषणा  BCMA_CC_SYSCLKCTL_CLKDIV	0xFFFF0000	/* ClkDiv  (ILP = 1/(4+भागisor)) */
#घोषणा  BCMA_CC_SYSCLKCTL_CLKDIV_SHIFT	16
#घोषणा BCMA_CC_CLKSTSTR		0x00C4		/* Rev >= 3 only */
#घोषणा BCMA_CC_EROM			0x00FC
#घोषणा BCMA_CC_PCMCIA_CFG		0x0100
#घोषणा BCMA_CC_PCMCIA_MEMWAIT		0x0104
#घोषणा BCMA_CC_PCMCIA_ATTRWAIT		0x0108
#घोषणा BCMA_CC_PCMCIA_IOWAIT		0x010C
#घोषणा BCMA_CC_IDE_CFG			0x0110
#घोषणा BCMA_CC_IDE_MEMWAIT		0x0114
#घोषणा BCMA_CC_IDE_ATTRWAIT		0x0118
#घोषणा BCMA_CC_IDE_IOWAIT		0x011C
#घोषणा BCMA_CC_PROG_CFG		0x0120
#घोषणा BCMA_CC_PROG_WAITCNT		0x0124
#घोषणा BCMA_CC_FLASH_CFG		0x0128
#घोषणा  BCMA_CC_FLASH_CFG_DS		0x0010	/* Data size, 0=8bit, 1=16bit */
#घोषणा BCMA_CC_FLASH_WAITCNT		0x012C
#घोषणा BCMA_CC_SROM_CONTROL		0x0190
#घोषणा  BCMA_CC_SROM_CONTROL_START	0x80000000
#घोषणा  BCMA_CC_SROM_CONTROL_BUSY	0x80000000
#घोषणा  BCMA_CC_SROM_CONTROL_OPCODE	0x60000000
#घोषणा  BCMA_CC_SROM_CONTROL_OP_READ	0x00000000
#घोषणा  BCMA_CC_SROM_CONTROL_OP_WRITE	0x20000000
#घोषणा  BCMA_CC_SROM_CONTROL_OP_WRDIS	0x40000000
#घोषणा  BCMA_CC_SROM_CONTROL_OP_WREN	0x60000000
#घोषणा  BCMA_CC_SROM_CONTROL_OTPSEL	0x00000010
#घोषणा  BCMA_CC_SROM_CONTROL_LOCK	0x00000008
#घोषणा  BCMA_CC_SROM_CONTROL_SIZE_MASK	0x00000006
#घोषणा  BCMA_CC_SROM_CONTROL_SIZE_1K	0x00000000
#घोषणा  BCMA_CC_SROM_CONTROL_SIZE_4K	0x00000002
#घोषणा  BCMA_CC_SROM_CONTROL_SIZE_16K	0x00000004
#घोषणा  BCMA_CC_SROM_CONTROL_SIZE_SHIFT	1
#घोषणा  BCMA_CC_SROM_CONTROL_PRESENT	0x00000001
/* Block 0x140 - 0x190 रेजिस्टरs are chipset specअगरic */
#घोषणा BCMA_CC_4706_FLASHSCFG		0x18C		/* Flash काष्ठा configuration */
#घोषणा  BCMA_CC_4706_FLASHSCFG_MASK	0x000000ff
#घोषणा  BCMA_CC_4706_FLASHSCFG_SF1	0x00000001	/* 2nd serial flash present */
#घोषणा  BCMA_CC_4706_FLASHSCFG_PF1	0x00000002	/* 2nd parallel flash present */
#घोषणा  BCMA_CC_4706_FLASHSCFG_SF1_TYPE	0x00000004	/* 2nd serial flash type : 0 : ST, 1 : Aपंचांगel */
#घोषणा  BCMA_CC_4706_FLASHSCFG_NF1	0x00000008	/* 2nd न_अंकD flash present */
#घोषणा  BCMA_CC_4706_FLASHSCFG_1ST_MADDR_SEG_MASK	0x000000f0
#घोषणा  BCMA_CC_4706_FLASHSCFG_1ST_MADDR_SEG_4MB	0x00000010	/* 4MB */
#घोषणा  BCMA_CC_4706_FLASHSCFG_1ST_MADDR_SEG_8MB	0x00000020	/* 8MB */
#घोषणा  BCMA_CC_4706_FLASHSCFG_1ST_MADDR_SEG_16MB	0x00000030	/* 16MB */
#घोषणा  BCMA_CC_4706_FLASHSCFG_1ST_MADDR_SEG_32MB	0x00000040	/* 32MB */
#घोषणा  BCMA_CC_4706_FLASHSCFG_1ST_MADDR_SEG_64MB	0x00000050	/* 64MB */
#घोषणा  BCMA_CC_4706_FLASHSCFG_1ST_MADDR_SEG_128MB	0x00000060	/* 128MB */
#घोषणा  BCMA_CC_4706_FLASHSCFG_1ST_MADDR_SEG_256MB	0x00000070	/* 256MB */
/* न_अंकD flash रेजिस्टरs क्रम BCM4706 (corerev = 31) */
#घोषणा BCMA_CC_NFLASH_CTL		0x01A0
#घोषणा  BCMA_CC_NFLASH_CTL_ERR		0x08000000
#घोषणा BCMA_CC_NFLASH_CONF		0x01A4
#घोषणा BCMA_CC_NFLASH_COL_ADDR		0x01A8
#घोषणा BCMA_CC_NFLASH_ROW_ADDR		0x01AC
#घोषणा BCMA_CC_NFLASH_DATA		0x01B0
#घोषणा BCMA_CC_NFLASH_WAITCNT0		0x01B4
/* 0x1E0 is defined as shared BCMA_CLKCTLST */
#घोषणा BCMA_CC_HW_WORKAROUND		0x01E4 /* Hardware workaround (rev >= 20) */
#घोषणा BCMA_CC_UART0_DATA		0x0300
#घोषणा BCMA_CC_UART0_IMR		0x0304
#घोषणा BCMA_CC_UART0_FCR		0x0308
#घोषणा BCMA_CC_UART0_LCR		0x030C
#घोषणा BCMA_CC_UART0_MCR		0x0310
#घोषणा BCMA_CC_UART0_LSR		0x0314
#घोषणा BCMA_CC_UART0_MSR		0x0318
#घोषणा BCMA_CC_UART0_SCRATCH		0x031C
#घोषणा BCMA_CC_UART1_DATA		0x0400
#घोषणा BCMA_CC_UART1_IMR		0x0404
#घोषणा BCMA_CC_UART1_FCR		0x0408
#घोषणा BCMA_CC_UART1_LCR		0x040C
#घोषणा BCMA_CC_UART1_MCR		0x0410
#घोषणा BCMA_CC_UART1_LSR		0x0414
#घोषणा BCMA_CC_UART1_MSR		0x0418
#घोषणा BCMA_CC_UART1_SCRATCH		0x041C
/* PMU रेजिस्टरs (rev >= 20) */
#घोषणा BCMA_CC_PMU_CTL			0x0600 /* PMU control */
#घोषणा  BCMA_CC_PMU_CTL_ILP_DIV	0xFFFF0000 /* ILP भाग mask */
#घोषणा  BCMA_CC_PMU_CTL_ILP_DIV_SHIFT	16
#घोषणा  BCMA_CC_PMU_CTL_RES		0x00006000 /* reset control mask */
#घोषणा  BCMA_CC_PMU_CTL_RES_SHIFT	13
#घोषणा  BCMA_CC_PMU_CTL_RES_RELOAD	0x2	/* reload POR values */
#घोषणा  BCMA_CC_PMU_CTL_PLL_UPD	0x00000400
#घोषणा  BCMA_CC_PMU_CTL_NOILPONW	0x00000200 /* No ILP on रुको */
#घोषणा  BCMA_CC_PMU_CTL_HTREQEN	0x00000100 /* HT req enable */
#घोषणा  BCMA_CC_PMU_CTL_ALPREQEN	0x00000080 /* ALP req enable */
#घोषणा  BCMA_CC_PMU_CTL_XTALFREQ	0x0000007C /* Crystal freq */
#घोषणा  BCMA_CC_PMU_CTL_XTALFREQ_SHIFT	2
#घोषणा  BCMA_CC_PMU_CTL_ILPDIVEN	0x00000002 /* ILP भाग enable */
#घोषणा  BCMA_CC_PMU_CTL_LPOSEL		0x00000001 /* LPO sel */
#घोषणा BCMA_CC_PMU_CAP			0x0604 /* PMU capabilities */
#घोषणा  BCMA_CC_PMU_CAP_REVISION	0x000000FF /* Revision mask */
#घोषणा BCMA_CC_PMU_STAT		0x0608 /* PMU status */
#घोषणा  BCMA_CC_PMU_STAT_EXT_LPO_AVAIL	0x00000100
#घोषणा  BCMA_CC_PMU_STAT_WDRESET	0x00000080
#घोषणा  BCMA_CC_PMU_STAT_INTPEND	0x00000040 /* Interrupt pending */
#घोषणा  BCMA_CC_PMU_STAT_SBCLKST	0x00000030 /* Backplane घड़ी status? */
#घोषणा  BCMA_CC_PMU_STAT_HAVEALP	0x00000008 /* ALP available */
#घोषणा  BCMA_CC_PMU_STAT_HAVEHT	0x00000004 /* HT available */
#घोषणा  BCMA_CC_PMU_STAT_RESINIT	0x00000003 /* Res init */
#घोषणा BCMA_CC_PMU_RES_STAT		0x060C /* PMU res status */
#घोषणा BCMA_CC_PMU_RES_PEND		0x0610 /* PMU res pending */
#घोषणा BCMA_CC_PMU_TIMER		0x0614 /* PMU समयr */
#घोषणा BCMA_CC_PMU_MINRES_MSK		0x0618 /* PMU min res mask */
#घोषणा BCMA_CC_PMU_MAXRES_MSK		0x061C /* PMU max res mask */
#घोषणा BCMA_CC_PMU_RES_TABSEL		0x0620 /* PMU res table sel */
#घोषणा BCMA_CC_PMU_RES_DEPMSK		0x0624 /* PMU res dep mask */
#घोषणा BCMA_CC_PMU_RES_UPDNTM		0x0628 /* PMU res upकरोwn समयr */
#घोषणा BCMA_CC_PMU_RES_TIMER		0x062C /* PMU res समयr */
#घोषणा BCMA_CC_PMU_CLKSTRETCH		0x0630 /* PMU घड़ीstretch */
#घोषणा BCMA_CC_PMU_WATCHDOG		0x0634 /* PMU watchकरोg */
#घोषणा BCMA_CC_PMU_RES_REQTS		0x0640 /* PMU res req समयr sel */
#घोषणा BCMA_CC_PMU_RES_REQT		0x0644 /* PMU res req समयr */
#घोषणा BCMA_CC_PMU_RES_REQM		0x0648 /* PMU res req mask */
#घोषणा BCMA_CC_PMU_CHIPCTL_ADDR	0x0650
#घोषणा BCMA_CC_PMU_CHIPCTL_DATA	0x0654
#घोषणा BCMA_CC_PMU_REGCTL_ADDR		0x0658
#घोषणा BCMA_CC_PMU_REGCTL_DATA		0x065C
#घोषणा BCMA_CC_PMU_PLLCTL_ADDR		0x0660
#घोषणा BCMA_CC_PMU_PLLCTL_DATA		0x0664
#घोषणा BCMA_CC_PMU_STRAPOPT		0x0668 /* (corerev >= 28) */
#घोषणा BCMA_CC_PMU_XTAL_FREQ		0x066C /* (pmurev >= 10) */
#घोषणा  BCMA_CC_PMU_XTAL_FREQ_ILPCTL_MASK	0x00001FFF
#घोषणा  BCMA_CC_PMU_XTAL_FREQ_MEASURE_MASK	0x80000000
#घोषणा  BCMA_CC_PMU_XTAL_FREQ_MEASURE_SHIFT	31
#घोषणा BCMA_CC_SPROM			0x0800 /* SPROM beginning */
/* न_अंकD flash MLC controller रेजिस्टरs (corerev >= 38) */
#घोषणा BCMA_CC_न_अंकD_REVISION		0x0C00
#घोषणा BCMA_CC_न_अंकD_CMD_START		0x0C04
#घोषणा BCMA_CC_न_अंकD_CMD_ADDR_X		0x0C08
#घोषणा BCMA_CC_न_अंकD_CMD_ADDR		0x0C0C
#घोषणा BCMA_CC_न_अंकD_CMD_END_ADDR	0x0C10
#घोषणा BCMA_CC_न_अंकD_CS_न_अंकD_SELECT	0x0C14
#घोषणा BCMA_CC_न_अंकD_CS_न_अंकD_XOR	0x0C18
#घोषणा BCMA_CC_न_अंकD_SPARE_RD0		0x0C20
#घोषणा BCMA_CC_न_अंकD_SPARE_RD4		0x0C24
#घोषणा BCMA_CC_न_अंकD_SPARE_RD8		0x0C28
#घोषणा BCMA_CC_न_अंकD_SPARE_RD12		0x0C2C
#घोषणा BCMA_CC_न_अंकD_SPARE_WR0		0x0C30
#घोषणा BCMA_CC_न_अंकD_SPARE_WR4		0x0C34
#घोषणा BCMA_CC_न_अंकD_SPARE_WR8		0x0C38
#घोषणा BCMA_CC_न_अंकD_SPARE_WR12		0x0C3C
#घोषणा BCMA_CC_न_अंकD_ACC_CONTROL	0x0C40
#घोषणा BCMA_CC_न_अंकD_CONFIG		0x0C48
#घोषणा BCMA_CC_न_अंकD_TIMING_1		0x0C50
#घोषणा BCMA_CC_न_अंकD_TIMING_2		0x0C54
#घोषणा BCMA_CC_न_अंकD_SEMAPHORE		0x0C58
#घोषणा BCMA_CC_न_अंकD_DEVID		0x0C60
#घोषणा BCMA_CC_न_अंकD_DEVID_X		0x0C64
#घोषणा BCMA_CC_न_अंकD_BLOCK_LOCK_STATUS	0x0C68
#घोषणा BCMA_CC_न_अंकD_INTFC_STATUS	0x0C6C
#घोषणा BCMA_CC_न_अंकD_ECC_CORR_ADDR_X	0x0C70
#घोषणा BCMA_CC_न_अंकD_ECC_CORR_ADDR	0x0C74
#घोषणा BCMA_CC_न_अंकD_ECC_UNC_ADDR_X	0x0C78
#घोषणा BCMA_CC_न_अंकD_ECC_UNC_ADDR	0x0C7C
#घोषणा BCMA_CC_न_अंकD_READ_ERROR_COUNT	0x0C80
#घोषणा BCMA_CC_न_अंकD_CORR_STAT_THRESHOLD	0x0C84
#घोषणा BCMA_CC_न_अंकD_READ_ADDR_X	0x0C90
#घोषणा BCMA_CC_न_अंकD_READ_ADDR		0x0C94
#घोषणा BCMA_CC_न_अंकD_PAGE_PROGRAM_ADDR_X	0x0C98
#घोषणा BCMA_CC_न_अंकD_PAGE_PROGRAM_ADDR	0x0C9C
#घोषणा BCMA_CC_न_अंकD_COPY_BACK_ADDR_X	0x0CA0
#घोषणा BCMA_CC_न_अंकD_COPY_BACK_ADDR	0x0CA4
#घोषणा BCMA_CC_न_अंकD_BLOCK_ERASE_ADDR_X	0x0CA8
#घोषणा BCMA_CC_न_अंकD_BLOCK_ERASE_ADDR	0x0CAC
#घोषणा BCMA_CC_न_अंकD_INV_READ_ADDR_X	0x0CB0
#घोषणा BCMA_CC_न_अंकD_INV_READ_ADDR	0x0CB4
#घोषणा BCMA_CC_न_अंकD_BLK_WR_PROTECT	0x0CC0
#घोषणा BCMA_CC_न_अंकD_ACC_CONTROL_CS1	0x0CD0
#घोषणा BCMA_CC_न_अंकD_CONFIG_CS1		0x0CD4
#घोषणा BCMA_CC_न_अंकD_TIMING_1_CS1	0x0CD8
#घोषणा BCMA_CC_न_अंकD_TIMING_2_CS1	0x0CDC
#घोषणा BCMA_CC_न_अंकD_SPARE_RD16		0x0D30
#घोषणा BCMA_CC_न_अंकD_SPARE_RD20		0x0D34
#घोषणा BCMA_CC_न_अंकD_SPARE_RD24		0x0D38
#घोषणा BCMA_CC_न_अंकD_SPARE_RD28		0x0D3C
#घोषणा BCMA_CC_न_अंकD_CACHE_ADDR		0x0D40
#घोषणा BCMA_CC_न_अंकD_CACHE_DATA		0x0D44
#घोषणा BCMA_CC_न_अंकD_CTRL_CONFIG	0x0D48
#घोषणा BCMA_CC_न_अंकD_CTRL_STATUS	0x0D4C

/* Divider allocation in 4716/47162/5356 */
#घोषणा BCMA_CC_PMU5_MAINPLL_CPU	1
#घोषणा BCMA_CC_PMU5_MAINPLL_MEM	2
#घोषणा BCMA_CC_PMU5_MAINPLL_SSB	3

/* PLL usage in 4716/47162 */
#घोषणा BCMA_CC_PMU4716_MAINPLL_PLL0	12

/* PLL usage in 5356/5357 */
#घोषणा BCMA_CC_PMU5356_MAINPLL_PLL0	0
#घोषणा BCMA_CC_PMU5357_MAINPLL_PLL0	0

/* 4706 PMU */
#घोषणा BCMA_CC_PMU4706_MAINPLL_PLL0	0
#घोषणा BCMA_CC_PMU6_4706_PROCPLL_OFF	4	/* The CPU PLL */
#घोषणा  BCMA_CC_PMU6_4706_PROC_P2DIV_MASK	0x000f0000
#घोषणा  BCMA_CC_PMU6_4706_PROC_P2DIV_SHIFT	16
#घोषणा  BCMA_CC_PMU6_4706_PROC_P1DIV_MASK	0x0000f000
#घोषणा  BCMA_CC_PMU6_4706_PROC_P1DIV_SHIFT	12
#घोषणा  BCMA_CC_PMU6_4706_PROC_NDIV_INT_MASK	0x00000ff8
#घोषणा  BCMA_CC_PMU6_4706_PROC_NDIV_INT_SHIFT	3
#घोषणा  BCMA_CC_PMU6_4706_PROC_NDIV_MODE_MASK	0x00000007
#घोषणा  BCMA_CC_PMU6_4706_PROC_NDIV_MODE_SHIFT	0

/* PMU rev 15 */
#घोषणा BCMA_CC_PMU15_PLL_PLLCTL0	0
#घोषणा  BCMA_CC_PMU15_PLL_PC0_CLKSEL_MASK	0x00000003
#घोषणा  BCMA_CC_PMU15_PLL_PC0_CLKSEL_SHIFT	0
#घोषणा  BCMA_CC_PMU15_PLL_PC0_FREQTGT_MASK	0x003FFFFC
#घोषणा  BCMA_CC_PMU15_PLL_PC0_FREQTGT_SHIFT	2
#घोषणा  BCMA_CC_PMU15_PLL_PC0_PRESCALE_MASK	0x00C00000
#घोषणा  BCMA_CC_PMU15_PLL_PC0_PRESCALE_SHIFT	22
#घोषणा  BCMA_CC_PMU15_PLL_PC0_KPCTRL_MASK	0x07000000
#घोषणा  BCMA_CC_PMU15_PLL_PC0_KPCTRL_SHIFT	24
#घोषणा  BCMA_CC_PMU15_PLL_PC0_FCNTCTRL_MASK	0x38000000
#घोषणा  BCMA_CC_PMU15_PLL_PC0_FCNTCTRL_SHIFT	27
#घोषणा  BCMA_CC_PMU15_PLL_PC0_FDCMODE_MASK	0x40000000
#घोषणा  BCMA_CC_PMU15_PLL_PC0_FDCMODE_SHIFT	30
#घोषणा  BCMA_CC_PMU15_PLL_PC0_CTRLBIAS_MASK	0x80000000
#घोषणा  BCMA_CC_PMU15_PLL_PC0_CTRLBIAS_SHIFT	31

/* ALP घड़ी on pre-PMU chips */
#घोषणा BCMA_CC_PMU_ALP_CLOCK		20000000
/* HT घड़ी क्रम प्रणालीs with PMU-enabled chipcommon */
#घोषणा BCMA_CC_PMU_HT_CLOCK		80000000

/* PMU rev 5 (& 6) */
#घोषणा BCMA_CC_PPL_P1P2_OFF		0
#घोषणा BCMA_CC_PPL_P1_MASK		0x0f000000
#घोषणा BCMA_CC_PPL_P1_SHIFT		24
#घोषणा BCMA_CC_PPL_P2_MASK		0x00f00000
#घोषणा BCMA_CC_PPL_P2_SHIFT		20
#घोषणा BCMA_CC_PPL_M14_OFF		1
#घोषणा BCMA_CC_PPL_MDIV_MASK		0x000000ff
#घोषणा BCMA_CC_PPL_MDIV_WIDTH		8
#घोषणा BCMA_CC_PPL_NM5_OFF		2
#घोषणा BCMA_CC_PPL_NDIV_MASK		0xfff00000
#घोषणा BCMA_CC_PPL_NDIV_SHIFT		20
#घोषणा BCMA_CC_PPL_FMAB_OFF		3
#घोषणा BCMA_CC_PPL_MRAT_MASK		0xf0000000
#घोषणा BCMA_CC_PPL_MRAT_SHIFT		28
#घोषणा BCMA_CC_PPL_ABRAT_MASK		0x08000000
#घोषणा BCMA_CC_PPL_ABRAT_SHIFT		27
#घोषणा BCMA_CC_PPL_FDIV_MASK		0x07ffffff
#घोषणा BCMA_CC_PPL_PLLCTL_OFF		4
#घोषणा BCMA_CC_PPL_PCHI_OFF		5
#घोषणा BCMA_CC_PPL_PCHI_MASK		0x0000003f

#घोषणा BCMA_CC_PMU_PLL_CTL0		0
#घोषणा BCMA_CC_PMU_PLL_CTL1		1
#घोषणा BCMA_CC_PMU_PLL_CTL2		2
#घोषणा BCMA_CC_PMU_PLL_CTL3		3
#घोषणा BCMA_CC_PMU_PLL_CTL4		4
#घोषणा BCMA_CC_PMU_PLL_CTL5		5

#घोषणा BCMA_CC_PMU1_PLL0_PC0_P1DIV_MASK	0x00f00000
#घोषणा BCMA_CC_PMU1_PLL0_PC0_P1DIV_SHIFT	20

#घोषणा BCMA_CC_PMU1_PLL0_PC2_NDIV_INT_MASK	0x1ff00000
#घोषणा BCMA_CC_PMU1_PLL0_PC2_NDIV_INT_SHIFT	20

#घोषणा BCMA_CCB_MII_MNG_CTL		0x0000
#घोषणा BCMA_CCB_MII_MNG_CMD_DATA	0x0004

/* BCM4331 ChipControl numbers. */
#घोषणा BCMA_CHIPCTL_4331_BT_COEXIST		BIT(0)	/* 0 disable */
#घोषणा BCMA_CHIPCTL_4331_SECI			BIT(1)	/* 0 SECI is disabled (JATG functional) */
#घोषणा BCMA_CHIPCTL_4331_EXT_LNA		BIT(2)	/* 0 disable */
#घोषणा BCMA_CHIPCTL_4331_SPROM_GPIO13_15	BIT(3)	/* sprom/gpio13-15 mux */
#घोषणा BCMA_CHIPCTL_4331_EXTPA_EN		BIT(4)	/* 0 ext pa disable, 1 ext pa enabled */
#घोषणा BCMA_CHIPCTL_4331_GPIOCLK_ON_SPROMCS	BIT(5)	/* set drive out GPIO_CLK on sprom_cs pin */
#घोषणा BCMA_CHIPCTL_4331_PCIE_MDIO_ON_SPROMCS	BIT(6)	/* use sprom_cs pin as PCIE mdio पूर्णांकerface */
#घोषणा BCMA_CHIPCTL_4331_EXTPA_ON_GPIO2_5	BIT(7)	/* aband extpa will be at gpio2/5 and sprom_करोut */
#घोषणा BCMA_CHIPCTL_4331_OVR_PIPEAUXCLKEN	BIT(8)	/* override core control on pipe_AuxClkEnable */
#घोषणा BCMA_CHIPCTL_4331_OVR_PIPEAUXPWRDOWN	BIT(9)	/* override core control on pipe_AuxPowerDown */
#घोषणा BCMA_CHIPCTL_4331_PCIE_AUXCLKEN		BIT(10)	/* pcie_auxclkenable */
#घोषणा BCMA_CHIPCTL_4331_PCIE_PIPE_PLLDOWN	BIT(11)	/* pcie_pipe_pllघातerकरोwn */
#घोषणा BCMA_CHIPCTL_4331_EXTPA_EN2		BIT(12)	/* 0 ext pa disable, 1 ext pa enabled */
#घोषणा BCMA_CHIPCTL_4331_BT_SHD0_ON_GPIO4	BIT(16)	/* enable bt_shd0 at gpio4 */
#घोषणा BCMA_CHIPCTL_4331_BT_SHD1_ON_GPIO5	BIT(17)	/* enable bt_shd1 at gpio5 */

/* 43224 chip-specअगरic ChipControl रेजिस्टर bits */
#घोषणा BCMA_CCTRL_43224_GPIO_TOGGLE		0x8000		/* gpio[3:0] pins as btcoex or s/w gpio */
#घोषणा BCMA_CCTRL_43224A0_12MA_LED_DRIVE	0x00F000F0	/* 12 mA drive strength */
#घोषणा BCMA_CCTRL_43224B0_12MA_LED_DRIVE	0xF0		/* 12 mA drive strength क्रम later 43224s */

/* 4313 Chip specअगरic ChipControl रेजिस्टर bits */
#घोषणा BCMA_CCTRL_4313_12MA_LED_DRIVE		0x00000007	/* 12 mA drive strengh क्रम later 4313 */

/* BCM5357 ChipControl रेजिस्टर bits */
#घोषणा BCMA_CHIPCTL_5357_EXTPA			BIT(14)
#घोषणा BCMA_CHIPCTL_5357_ANT_MUX_2O3		BIT(15)
#घोषणा BCMA_CHIPCTL_5357_NFLASH		BIT(16)
#घोषणा BCMA_CHIPCTL_5357_I2S_PINS_ENABLE	BIT(18)
#घोषणा BCMA_CHIPCTL_5357_I2CSPI_PINS_ENABLE	BIT(19)

#घोषणा BCMA_RES_4314_LPLDO_PU			BIT(0)
#घोषणा BCMA_RES_4314_PMU_SLEEP_DIS		BIT(1)
#घोषणा BCMA_RES_4314_PMU_BG_PU			BIT(2)
#घोषणा BCMA_RES_4314_CBUCK_LPOM_PU		BIT(3)
#घोषणा BCMA_RES_4314_CBUCK_PFM_PU		BIT(4)
#घोषणा BCMA_RES_4314_CLDO_PU			BIT(5)
#घोषणा BCMA_RES_4314_LPLDO2_LVM		BIT(6)
#घोषणा BCMA_RES_4314_WL_PMU_PU			BIT(7)
#घोषणा BCMA_RES_4314_LNLDO_PU			BIT(8)
#घोषणा BCMA_RES_4314_LDO3P3_PU			BIT(9)
#घोषणा BCMA_RES_4314_OTP_PU			BIT(10)
#घोषणा BCMA_RES_4314_XTAL_PU			BIT(11)
#घोषणा BCMA_RES_4314_WL_PWRSW_PU		BIT(12)
#घोषणा BCMA_RES_4314_LQ_AVAIL			BIT(13)
#घोषणा BCMA_RES_4314_LOGIC_RET			BIT(14)
#घोषणा BCMA_RES_4314_MEM_SLEEP			BIT(15)
#घोषणा BCMA_RES_4314_MACPHY_RET		BIT(16)
#घोषणा BCMA_RES_4314_WL_CORE_READY		BIT(17)
#घोषणा BCMA_RES_4314_ILP_REQ			BIT(18)
#घोषणा BCMA_RES_4314_ALP_AVAIL			BIT(19)
#घोषणा BCMA_RES_4314_MISC_PWRSW_PU		BIT(20)
#घोषणा BCMA_RES_4314_SYNTH_PWRSW_PU		BIT(21)
#घोषणा BCMA_RES_4314_RX_PWRSW_PU		BIT(22)
#घोषणा BCMA_RES_4314_RADIO_PU			BIT(23)
#घोषणा BCMA_RES_4314_VCO_LDO_PU		BIT(24)
#घोषणा BCMA_RES_4314_AFE_LDO_PU		BIT(25)
#घोषणा BCMA_RES_4314_RX_LDO_PU			BIT(26)
#घोषणा BCMA_RES_4314_TX_LDO_PU			BIT(27)
#घोषणा BCMA_RES_4314_HT_AVAIL			BIT(28)
#घोषणा BCMA_RES_4314_MACPHY_CLK_AVAIL		BIT(29)

/* Data क्रम the PMU, अगर available.
 * Check availability with ((काष्ठा bcma_chipcommon)->capabilities & BCMA_CC_CAP_PMU)
 */
काष्ठा bcma_chipcommon_pmu अणु
	काष्ठा bcma_device *core;	/* Can be separated core or just ChipCommon one */
	u8 rev;			/* PMU revision */
	u32 crystalfreq;	/* The active crystal frequency (in kHz) */
पूर्ण;

#अगर_घोषित CONFIG_BCMA_PFLASH
काष्ठा bcma_pflash अणु
	bool present;
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_BCMA_SFLASH
काष्ठा mtd_info;

काष्ठा bcma_sflash अणु
	bool present;
	u32 blocksize;
	u16 numblocks;
	u32 size;
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_BCMA_NFLASH
काष्ठा bcma_nflash अणु
	bool present;
	bool boot;		/* This is the flash the SoC boots from */
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_BCMA_DRIVER_MIPS
काष्ठा bcma_serial_port अणु
	व्योम *regs;
	अचिन्हित दीर्घ घड़ीspeed;
	अचिन्हित पूर्णांक irq;
	अचिन्हित पूर्णांक baud_base;
	अचिन्हित पूर्णांक reg_shअगरt;
पूर्ण;
#पूर्ण_अगर /* CONFIG_BCMA_DRIVER_MIPS */

काष्ठा bcma_drv_cc अणु
	काष्ठा bcma_device *core;
	u32 status;
	u32 capabilities;
	u32 capabilities_ext;
	u8 setup_करोne:1;
	u8 early_setup_करोne:1;
	/* Fast Powerup Delay स्थिरant */
	u16 fast_pwrup_delay;
	काष्ठा bcma_chipcommon_pmu pmu;
#अगर_घोषित CONFIG_BCMA_PFLASH
	काष्ठा bcma_pflash pflash;
#पूर्ण_अगर
#अगर_घोषित CONFIG_BCMA_SFLASH
	काष्ठा bcma_sflash sflash;
#पूर्ण_अगर
#अगर_घोषित CONFIG_BCMA_NFLASH
	काष्ठा bcma_nflash nflash;
#पूर्ण_अगर

#अगर_घोषित CONFIG_BCMA_DRIVER_MIPS
	पूर्णांक nr_serial_ports;
	काष्ठा bcma_serial_port serial_ports[4];
#पूर्ण_अगर /* CONFIG_BCMA_DRIVER_MIPS */
	u32 ticks_per_ms;
	काष्ठा platक्रमm_device *watchकरोg;

	/* Lock क्रम GPIO रेजिस्टर access. */
	spinlock_t gpio_lock;
#अगर_घोषित CONFIG_BCMA_DRIVER_GPIO
	काष्ठा gpio_chip gpio;
#पूर्ण_अगर
पूर्ण;

काष्ठा bcma_drv_cc_b अणु
	काष्ठा bcma_device *core;
	u8 setup_करोne:1;
	व्योम __iomem *mii;
पूर्ण;

/* Register access */
#घोषणा bcma_cc_पढ़ो32(cc, offset) \
	bcma_पढ़ो32((cc)->core, offset)
#घोषणा bcma_cc_ग_लिखो32(cc, offset, val) \
	bcma_ग_लिखो32((cc)->core, offset, val)

#घोषणा bcma_cc_mask32(cc, offset, mask) \
	bcma_cc_ग_लिखो32(cc, offset, bcma_cc_पढ़ो32(cc, offset) & (mask))
#घोषणा bcma_cc_set32(cc, offset, set) \
	bcma_cc_ग_लिखो32(cc, offset, bcma_cc_पढ़ो32(cc, offset) | (set))
#घोषणा bcma_cc_maskset32(cc, offset, mask, set) \
	bcma_cc_ग_लिखो32(cc, offset, (bcma_cc_पढ़ो32(cc, offset) & (mask)) | (set))

/* PMU रेजिस्टरs access */
#घोषणा bcma_pmu_पढ़ो32(cc, offset) \
	bcma_पढ़ो32((cc)->pmu.core, offset)
#घोषणा bcma_pmu_ग_लिखो32(cc, offset, val) \
	bcma_ग_लिखो32((cc)->pmu.core, offset, val)

#घोषणा bcma_pmu_mask32(cc, offset, mask) \
	bcma_pmu_ग_लिखो32(cc, offset, bcma_pmu_पढ़ो32(cc, offset) & (mask))
#घोषणा bcma_pmu_set32(cc, offset, set) \
	bcma_pmu_ग_लिखो32(cc, offset, bcma_pmu_पढ़ो32(cc, offset) | (set))
#घोषणा bcma_pmu_maskset32(cc, offset, mask, set) \
	bcma_pmu_ग_लिखो32(cc, offset, (bcma_pmu_पढ़ो32(cc, offset) & (mask)) | (set))

बाह्य u32 bcma_chipco_watchकरोg_समयr_set(काष्ठा bcma_drv_cc *cc, u32 ticks);

बाह्य u32 bcma_chipco_get_alp_घड़ी(काष्ठा bcma_drv_cc *cc);

व्योम bcma_chipco_irq_mask(काष्ठा bcma_drv_cc *cc, u32 mask, u32 value);

u32 bcma_chipco_irq_status(काष्ठा bcma_drv_cc *cc, u32 mask);

/* Chipcommon GPIO pin access. */
u32 bcma_chipco_gpio_in(काष्ठा bcma_drv_cc *cc, u32 mask);
u32 bcma_chipco_gpio_out(काष्ठा bcma_drv_cc *cc, u32 mask, u32 value);
u32 bcma_chipco_gpio_outen(काष्ठा bcma_drv_cc *cc, u32 mask, u32 value);
u32 bcma_chipco_gpio_control(काष्ठा bcma_drv_cc *cc, u32 mask, u32 value);
u32 bcma_chipco_gpio_पूर्णांकmask(काष्ठा bcma_drv_cc *cc, u32 mask, u32 value);
u32 bcma_chipco_gpio_polarity(काष्ठा bcma_drv_cc *cc, u32 mask, u32 value);
u32 bcma_chipco_gpio_pullup(काष्ठा bcma_drv_cc *cc, u32 mask, u32 value);
u32 bcma_chipco_gpio_pullकरोwn(काष्ठा bcma_drv_cc *cc, u32 mask, u32 value);

/* PMU support */
बाह्य व्योम bcma_chipco_pll_ग_लिखो(काष्ठा bcma_drv_cc *cc, u32 offset,
				  u32 value);
बाह्य व्योम bcma_chipco_pll_maskset(काष्ठा bcma_drv_cc *cc, u32 offset,
				    u32 mask, u32 set);
बाह्य व्योम bcma_chipco_chipctl_maskset(काष्ठा bcma_drv_cc *cc,
					u32 offset, u32 mask, u32 set);
बाह्य व्योम bcma_chipco_regctl_maskset(काष्ठा bcma_drv_cc *cc,
				       u32 offset, u32 mask, u32 set);
बाह्य व्योम bcma_pmu_spuraव्योम_pllupdate(काष्ठा bcma_drv_cc *cc, पूर्णांक spuraव्योम);

बाह्य u32 bcma_pmu_get_bus_घड़ी(काष्ठा bcma_drv_cc *cc);

व्योम bcma_chipco_b_mii_ग_लिखो(काष्ठा bcma_drv_cc_b *ccb, u32 offset, u32 value);

#पूर्ण_अगर /* LINUX_BCMA_DRIVER_CC_H_ */
