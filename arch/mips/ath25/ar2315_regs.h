<शैली गुरु>
/*
 * Register definitions क्रम AR2315+
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2003 Atheros Communications, Inc.,  All Rights Reserved.
 * Copyright (C) 2006 FON Technology, SL.
 * Copyright (C) 2006 Imre Kaloz <kaloz@खोलोwrt.org>
 * Copyright (C) 2006-2008 Felix Fietkau <nbd@खोलोwrt.org>
 */

#अगर_अघोषित __ASM_MACH_ATH25_AR2315_REGS_H
#घोषणा __ASM_MACH_ATH25_AR2315_REGS_H

/*
 * IRQs
 */
#घोषणा AR2315_IRQ_MISC		(MIPS_CPU_IRQ_BASE + 2)	/* C0_CAUSE: 0x0400 */
#घोषणा AR2315_IRQ_WLAN0	(MIPS_CPU_IRQ_BASE + 3)	/* C0_CAUSE: 0x0800 */
#घोषणा AR2315_IRQ_ENET0	(MIPS_CPU_IRQ_BASE + 4)	/* C0_CAUSE: 0x1000 */
#घोषणा AR2315_IRQ_LCBUS_PCI	(MIPS_CPU_IRQ_BASE + 5)	/* C0_CAUSE: 0x2000 */
#घोषणा AR2315_IRQ_WLAN0_POLL	(MIPS_CPU_IRQ_BASE + 6)	/* C0_CAUSE: 0x4000 */

/*
 * Miscellaneous पूर्णांकerrupts, which share IP2.
 */
#घोषणा AR2315_MISC_IRQ_UART0		0
#घोषणा AR2315_MISC_IRQ_I2C_RSVD	1
#घोषणा AR2315_MISC_IRQ_SPI		2
#घोषणा AR2315_MISC_IRQ_AHB		3
#घोषणा AR2315_MISC_IRQ_APB		4
#घोषणा AR2315_MISC_IRQ_TIMER		5
#घोषणा AR2315_MISC_IRQ_GPIO		6
#घोषणा AR2315_MISC_IRQ_WATCHDOG	7
#घोषणा AR2315_MISC_IRQ_IR_RSVD		8
#घोषणा AR2315_MISC_IRQ_COUNT		9

/*
 * Address map
 */
#घोषणा AR2315_SPI_READ_BASE	0x08000000	/* SPI flash */
#घोषणा AR2315_SPI_READ_SIZE	0x01000000
#घोषणा AR2315_WLAN0_BASE	0x10000000	/* Wireless MMR */
#घोषणा AR2315_PCI_BASE		0x10100000	/* PCI MMR */
#घोषणा AR2315_PCI_SIZE		0x00001000
#घोषणा AR2315_SDRAMCTL_BASE	0x10300000	/* SDRAM MMR */
#घोषणा AR2315_SDRAMCTL_SIZE	0x00000020
#घोषणा AR2315_LOCAL_BASE	0x10400000	/* Local bus MMR */
#घोषणा AR2315_ENET0_BASE	0x10500000	/* Ethernet MMR */
#घोषणा AR2315_RST_BASE		0x11000000	/* Reset control MMR */
#घोषणा AR2315_RST_SIZE		0x00000100
#घोषणा AR2315_UART0_BASE	0x11100000	/* UART MMR */
#घोषणा AR2315_SPI_MMR_BASE	0x11300000	/* SPI flash MMR */
#घोषणा AR2315_SPI_MMR_SIZE	0x00000010
#घोषणा AR2315_PCI_EXT_BASE	0x80000000	/* PCI बाह्यal */
#घोषणा AR2315_PCI_EXT_SIZE	0x40000000

/*
 * Configuration रेजिस्टरs
 */

/* Cold reset रेजिस्टर */
#घोषणा AR2315_COLD_RESET		0x0000

#घोषणा AR2315_RESET_COLD_AHB		0x00000001
#घोषणा AR2315_RESET_COLD_APB		0x00000002
#घोषणा AR2315_RESET_COLD_CPU		0x00000004
#घोषणा AR2315_RESET_COLD_CPUWARM	0x00000008
#घोषणा AR2315_RESET_SYSTEM		(RESET_COLD_CPU |\
					 RESET_COLD_APB |\
					 RESET_COLD_AHB)  /* full प्रणाली */
#घोषणा AR2317_RESET_SYSTEM		0x00000010

/* Reset रेजिस्टर */
#घोषणा AR2315_RESET			0x0004

#घोषणा AR2315_RESET_WARM_WLAN0_MAC	0x00000001  /* warm reset WLAN0 MAC */
#घोषणा AR2315_RESET_WARM_WLAN0_BB	0x00000002  /* warm reset WLAN0 BB */
#घोषणा AR2315_RESET_MPEGTS_RSVD	0x00000004  /* warm reset MPEG-TS */
#घोषणा AR2315_RESET_PCIDMA		0x00000008  /* warm reset PCI ahb/dma */
#घोषणा AR2315_RESET_MEMCTL		0x00000010  /* warm reset mem control */
#घोषणा AR2315_RESET_LOCAL		0x00000020  /* warm reset local bus */
#घोषणा AR2315_RESET_I2C_RSVD		0x00000040  /* warm reset I2C bus */
#घोषणा AR2315_RESET_SPI		0x00000080  /* warm reset SPI अगरace */
#घोषणा AR2315_RESET_UART0		0x00000100  /* warm reset UART0 */
#घोषणा AR2315_RESET_IR_RSVD		0x00000200  /* warm reset IR अगरace */
#घोषणा AR2315_RESET_EPHY0		0x00000400  /* cold reset ENET0 phy */
#घोषणा AR2315_RESET_ENET0		0x00000800  /* cold reset ENET0 MAC */

/* AHB master arbitration control */
#घोषणा AR2315_AHB_ARB_CTL		0x0008

#घोषणा AR2315_ARB_CPU			0x00000001  /* CPU, शेष */
#घोषणा AR2315_ARB_WLAN			0x00000002  /* WLAN */
#घोषणा AR2315_ARB_MPEGTS_RSVD		0x00000004  /* MPEG-TS */
#घोषणा AR2315_ARB_LOCAL		0x00000008  /* Local bus */
#घोषणा AR2315_ARB_PCI			0x00000010  /* PCI bus */
#घोषणा AR2315_ARB_ETHERNET		0x00000020  /* Ethernet */
#घोषणा AR2315_ARB_RETRY		0x00000100  /* Retry policy (debug) */

/* Config Register */
#घोषणा AR2315_ENDIAN_CTL		0x000c

#घोषणा AR2315_CONFIG_AHB		0x00000001  /* EC-AHB bridge endian */
#घोषणा AR2315_CONFIG_WLAN		0x00000002  /* WLAN byteswap */
#घोषणा AR2315_CONFIG_MPEGTS_RSVD	0x00000004  /* MPEG-TS byteswap */
#घोषणा AR2315_CONFIG_PCI		0x00000008  /* PCI byteswap */
#घोषणा AR2315_CONFIG_MEMCTL		0x00000010  /* Mem controller endian */
#घोषणा AR2315_CONFIG_LOCAL		0x00000020  /* Local bus byteswap */
#घोषणा AR2315_CONFIG_ETHERNET		0x00000040  /* Ethernet byteswap */
#घोषणा AR2315_CONFIG_MERGE		0x00000200  /* CPU ग_लिखो buffer merge */
#घोषणा AR2315_CONFIG_CPU		0x00000400  /* CPU big endian */
#घोषणा AR2315_CONFIG_BIG		0x00000400
#घोषणा AR2315_CONFIG_PCIAHB		0x00000800
#घोषणा AR2315_CONFIG_PCIAHB_BRIDGE	0x00001000
#घोषणा AR2315_CONFIG_SPI		0x00008000  /* SPI byteswap */
#घोषणा AR2315_CONFIG_CPU_DRAM		0x00010000
#घोषणा AR2315_CONFIG_CPU_PCI		0x00020000
#घोषणा AR2315_CONFIG_CPU_MMR		0x00040000

/* NMI control */
#घोषणा AR2315_NMI_CTL			0x0010

#घोषणा AR2315_NMI_EN			1

/* Revision Register - Initial value is 0x3010 (WMAC 3.0, AR231X 1.0). */
#घोषणा AR2315_SREV			0x0014

#घोषणा AR2315_REV_MAJ			0x000000f0
#घोषणा AR2315_REV_MAJ_S		4
#घोषणा AR2315_REV_MIN			0x0000000f
#घोषणा AR2315_REV_MIN_S		0
#घोषणा AR2315_REV_CHIP			(AR2315_REV_MAJ | AR2315_REV_MIN)

/* Interface Enable */
#घोषणा AR2315_IF_CTL			0x0018

#घोषणा AR2315_IF_MASK			0x00000007
#घोषणा AR2315_IF_DISABLED		0		/* Disable all */
#घोषणा AR2315_IF_PCI			1		/* PCI */
#घोषणा AR2315_IF_TS_LOCAL		2		/* Local bus */
#घोषणा AR2315_IF_ALL			3		/* Emulation only */
#घोषणा AR2315_IF_LOCAL_HOST		0x00000008
#घोषणा AR2315_IF_PCI_HOST		0x00000010
#घोषणा AR2315_IF_PCI_INTR		0x00000020
#घोषणा AR2315_IF_PCI_CLK_MASK		0x00030000
#घोषणा AR2315_IF_PCI_CLK_INPUT		0
#घोषणा AR2315_IF_PCI_CLK_OUTPUT_LOW	1
#घोषणा AR2315_IF_PCI_CLK_OUTPUT_CLK	2
#घोषणा AR2315_IF_PCI_CLK_OUTPUT_HIGH	3
#घोषणा AR2315_IF_PCI_CLK_SHIFT		16

/* APB Interrupt control */
#घोषणा AR2315_ISR			0x0020
#घोषणा AR2315_IMR			0x0024
#घोषणा AR2315_GISR			0x0028

#घोषणा AR2315_ISR_UART0	0x00000001	/* high speed UART */
#घोषणा AR2315_ISR_I2C_RSVD	0x00000002	/* I2C bus */
#घोषणा AR2315_ISR_SPI		0x00000004	/* SPI bus */
#घोषणा AR2315_ISR_AHB		0x00000008	/* AHB error */
#घोषणा AR2315_ISR_APB		0x00000010	/* APB error */
#घोषणा AR2315_ISR_TIMER	0x00000020	/* Timer */
#घोषणा AR2315_ISR_GPIO		0x00000040	/* GPIO */
#घोषणा AR2315_ISR_WD		0x00000080	/* Watchकरोg */
#घोषणा AR2315_ISR_IR_RSVD	0x00000100	/* IR */

#घोषणा AR2315_GISR_MISC	0x00000001	/* Misc */
#घोषणा AR2315_GISR_WLAN0	0x00000002	/* WLAN0 */
#घोषणा AR2315_GISR_MPEGTS_RSVD	0x00000004	/* MPEG-TS */
#घोषणा AR2315_GISR_LOCALPCI	0x00000008	/* Local/PCI bus */
#घोषणा AR2315_GISR_WMACPOLL	0x00000010
#घोषणा AR2315_GISR_TIMER	0x00000020
#घोषणा AR2315_GISR_ETHERNET	0x00000040	/* Ethernet */

/* Generic समयr */
#घोषणा AR2315_TIMER			0x0030
#घोषणा AR2315_RELOAD			0x0034

/* Watchकरोg समयr */
#घोषणा AR2315_WDT_TIMER		0x0038
#घोषणा AR2315_WDT_CTRL			0x003c

#घोषणा AR2315_WDT_CTRL_IGNORE	0x00000000	/* ignore expiration */
#घोषणा AR2315_WDT_CTRL_NMI	0x00000001	/* NMI on watchकरोg */
#घोषणा AR2315_WDT_CTRL_RESET	0x00000002	/* reset on watchकरोg */

/* CPU Perक्रमmance Counters */
#घोषणा AR2315_PERFCNT0			0x0048
#घोषणा AR2315_PERFCNT1			0x004c

#घोषणा AR2315_PERF0_DATAHIT	0x00000001  /* Count Data Cache Hits */
#घोषणा AR2315_PERF0_DATAMISS	0x00000002  /* Count Data Cache Misses */
#घोषणा AR2315_PERF0_INSTHIT	0x00000004  /* Count Inकाष्ठाion Cache Hits */
#घोषणा AR2315_PERF0_INSTMISS	0x00000008  /* Count Inकाष्ठाion Cache Misses */
#घोषणा AR2315_PERF0_ACTIVE	0x00000010  /* Count Active Processor Cycles */
#घोषणा AR2315_PERF0_WBHIT	0x00000020  /* Count CPU Write Buffer Hits */
#घोषणा AR2315_PERF0_WBMISS	0x00000040  /* Count CPU Write Buffer Misses */

#घोषणा AR2315_PERF1_EB_ARDY	0x00000001  /* Count EB_ARdy संकेत */
#घोषणा AR2315_PERF1_EB_AVALID	0x00000002  /* Count EB_AValid संकेत */
#घोषणा AR2315_PERF1_EB_WDRDY	0x00000004  /* Count EB_WDRdy संकेत */
#घोषणा AR2315_PERF1_EB_RDVAL	0x00000008  /* Count EB_RdVal संकेत */
#घोषणा AR2315_PERF1_VRADDR	0x00000010  /* Count valid पढ़ो address cycles*/
#घोषणा AR2315_PERF1_VWADDR	0x00000020  /* Count valid ग_लिखो address cycl.*/
#घोषणा AR2315_PERF1_VWDATA	0x00000040  /* Count valid ग_लिखो data cycles */

/* AHB Error Reporting */
#घोषणा AR2315_AHB_ERR0			0x0050  /* error  */
#घोषणा AR2315_AHB_ERR1			0x0054  /* haddr  */
#घोषणा AR2315_AHB_ERR2			0x0058  /* hwdata */
#घोषणा AR2315_AHB_ERR3			0x005c  /* hrdata */
#घोषणा AR2315_AHB_ERR4			0x0060  /* status */

#घोषणा AR2315_AHB_ERROR_DET	1 /* AHB Error has been detected,          */
				  /* ग_लिखो 1 to clear all bits in ERR0     */
#घोषणा AR2315_AHB_ERROR_OVR	2 /* AHB Error overflow has been detected  */
#घोषणा AR2315_AHB_ERROR_WDT	4 /* AHB Error due to wdt instead of hresp */

#घोषणा AR2315_PROCERR_HMAST		0x0000000f
#घोषणा AR2315_PROCERR_HMAST_DFLT	0
#घोषणा AR2315_PROCERR_HMAST_WMAC	1
#घोषणा AR2315_PROCERR_HMAST_ENET	2
#घोषणा AR2315_PROCERR_HMAST_PCIENDPT	3
#घोषणा AR2315_PROCERR_HMAST_LOCAL	4
#घोषणा AR2315_PROCERR_HMAST_CPU	5
#घोषणा AR2315_PROCERR_HMAST_PCITGT	6
#घोषणा AR2315_PROCERR_HMAST_S		0
#घोषणा AR2315_PROCERR_HWRITE		0x00000010
#घोषणा AR2315_PROCERR_HSIZE		0x00000060
#घोषणा AR2315_PROCERR_HSIZE_S		5
#घोषणा AR2315_PROCERR_HTRANS		0x00000180
#घोषणा AR2315_PROCERR_HTRANS_S		7
#घोषणा AR2315_PROCERR_HBURST		0x00000e00
#घोषणा AR2315_PROCERR_HBURST_S		9

/* Clock Control */
#घोषणा AR2315_PLLC_CTL			0x0064
#घोषणा AR2315_PLLV_CTL			0x0068
#घोषणा AR2315_CPUCLK			0x006c
#घोषणा AR2315_AMBACLK			0x0070
#घोषणा AR2315_SYNCCLK			0x0074
#घोषणा AR2315_DSL_SLEEP_CTL		0x0080
#घोषणा AR2315_DSL_SLEEP_DUR		0x0084

/* PLLc Control fields */
#घोषणा AR2315_PLLC_REF_DIV_M		0x00000003
#घोषणा AR2315_PLLC_REF_DIV_S		0
#घोषणा AR2315_PLLC_FDBACK_DIV_M	0x0000007c
#घोषणा AR2315_PLLC_FDBACK_DIV_S	2
#घोषणा AR2315_PLLC_ADD_FDBACK_DIV_M	0x00000080
#घोषणा AR2315_PLLC_ADD_FDBACK_DIV_S	7
#घोषणा AR2315_PLLC_CLKC_DIV_M		0x0001c000
#घोषणा AR2315_PLLC_CLKC_DIV_S		14
#घोषणा AR2315_PLLC_CLKM_DIV_M		0x00700000
#घोषणा AR2315_PLLC_CLKM_DIV_S		20

/* CPU CLK Control fields */
#घोषणा AR2315_CPUCLK_CLK_SEL_M		0x00000003
#घोषणा AR2315_CPUCLK_CLK_SEL_S		0
#घोषणा AR2315_CPUCLK_CLK_DIV_M		0x0000000c
#घोषणा AR2315_CPUCLK_CLK_DIV_S		2

/* AMBA CLK Control fields */
#घोषणा AR2315_AMBACLK_CLK_SEL_M	0x00000003
#घोषणा AR2315_AMBACLK_CLK_SEL_S	0
#घोषणा AR2315_AMBACLK_CLK_DIV_M	0x0000000c
#घोषणा AR2315_AMBACLK_CLK_DIV_S	2

/* PCI Clock Control */
#घोषणा AR2315_PCICLK			0x00a4

#घोषणा AR2315_PCICLK_INPUT_M		0x00000003
#घोषणा AR2315_PCICLK_INPUT_S		0
#घोषणा AR2315_PCICLK_PLLC_CLKM		0
#घोषणा AR2315_PCICLK_PLLC_CLKM1	1
#घोषणा AR2315_PCICLK_PLLC_CLKC		2
#घोषणा AR2315_PCICLK_REF_CLK		3
#घोषणा AR2315_PCICLK_DIV_M		0x0000000c
#घोषणा AR2315_PCICLK_DIV_S		2
#घोषणा AR2315_PCICLK_IN_FREQ		0
#घोषणा AR2315_PCICLK_IN_FREQ_DIV_6	1
#घोषणा AR2315_PCICLK_IN_FREQ_DIV_8	2
#घोषणा AR2315_PCICLK_IN_FREQ_DIV_10	3

/* Observation Control Register */
#घोषणा AR2315_OCR			0x00b0

#घोषणा AR2315_OCR_GPIO0_IRIN		0x00000040
#घोषणा AR2315_OCR_GPIO1_IROUT		0x00000080
#घोषणा AR2315_OCR_GPIO3_RXCLR		0x00000200

/* General Clock Control */
#घोषणा AR2315_MISCCLK			0x00b4

#घोषणा AR2315_MISCCLK_PLLBYPASS_EN	0x00000001
#घोषणा AR2315_MISCCLK_PROCREFCLK	0x00000002

/*
 * SDRAM Controller
 *   - No पढ़ो or ग_लिखो buffers are included.
 */
#घोषणा AR2315_MEM_CFG			0x0000
#घोषणा AR2315_MEM_CTRL			0x000c
#घोषणा AR2315_MEM_REF			0x0010

#घोषणा AR2315_MEM_CFG_DATA_WIDTH_M	0x00006000
#घोषणा AR2315_MEM_CFG_DATA_WIDTH_S	13
#घोषणा AR2315_MEM_CFG_COL_WIDTH_M	0x00001e00
#घोषणा AR2315_MEM_CFG_COL_WIDTH_S	9
#घोषणा AR2315_MEM_CFG_ROW_WIDTH_M	0x000001e0
#घोषणा AR2315_MEM_CFG_ROW_WIDTH_S	5
#घोषणा AR2315_MEM_CFG_BANKADDR_BITS_M	0x00000018
#घोषणा AR2315_MEM_CFG_BANKADDR_BITS_S	3

/*
 * Local Bus Interface Registers
 */
#घोषणा AR2315_LB_CONFIG		0x0000

#घोषणा AR2315_LBCONF_OE	0x00000001	/* =1 OE is low-true */
#घोषणा AR2315_LBCONF_CS0	0x00000002	/* =1 first CS is low-true */
#घोषणा AR2315_LBCONF_CS1	0x00000004	/* =1 2nd CS is low-true */
#घोषणा AR2315_LBCONF_RDY	0x00000008	/* =1 RDY is low-true */
#घोषणा AR2315_LBCONF_WE	0x00000010	/* =1 Write En is low-true */
#घोषणा AR2315_LBCONF_WAIT	0x00000020	/* =1 WAIT is low-true */
#घोषणा AR2315_LBCONF_ADS	0x00000040	/* =1 Adr Strobe is low-true */
#घोषणा AR2315_LBCONF_MOT	0x00000080	/* =0 Intel, =1 Motorola */
#घोषणा AR2315_LBCONF_8CS	0x00000100	/* =1 8 bits CS, 0= 16bits */
#घोषणा AR2315_LBCONF_8DS	0x00000200	/* =1 8 bits Data S, 0=16bits */
#घोषणा AR2315_LBCONF_ADS_EN	0x00000400	/* =1 Enable ADS */
#घोषणा AR2315_LBCONF_ADR_OE	0x00000800	/* =1 Adr cap on OE, WE or DS */
#घोषणा AR2315_LBCONF_ADDT_MUX	0x00001000	/* =1 Adr and Data share bus */
#घोषणा AR2315_LBCONF_DATA_OE	0x00002000	/* =1 Data cap on OE, WE, DS */
#घोषणा AR2315_LBCONF_16DATA	0x00004000	/* =1 Data is 16 bits wide */
#घोषणा AR2315_LBCONF_SWAPDT	0x00008000	/* =1 Byte swap data */
#घोषणा AR2315_LBCONF_SYNC	0x00010000	/* =1 Bus synchronous to clk */
#घोषणा AR2315_LBCONF_INT	0x00020000	/* =1 Intr is low true */
#घोषणा AR2315_LBCONF_INT_CTR0	0x00000000	/* GND high-Z, Vdd is high-Z */
#घोषणा AR2315_LBCONF_INT_CTR1	0x00040000	/* GND drive, Vdd is high-Z */
#घोषणा AR2315_LBCONF_INT_CTR2	0x00080000	/* GND high-Z, Vdd drive */
#घोषणा AR2315_LBCONF_INT_CTR3	0x000c0000	/* GND drive, Vdd drive */
#घोषणा AR2315_LBCONF_RDY_WAIT	0x00100000	/* =1 RDY is negative of WAIT */
#घोषणा AR2315_LBCONF_INT_PULSE	0x00200000	/* =1 Interrupt is a pulse */
#घोषणा AR2315_LBCONF_ENABLE	0x00400000	/* =1 Falcon respond to LB */

#घोषणा AR2315_LB_CLKSEL		0x0004

#घोषणा AR2315_LBCLK_EXT	0x00000001	/* use बाह्यal clk क्रम lb */

#घोषणा AR2315_LB_1MS			0x0008

#घोषणा AR2315_LB1MS_MASK	0x0003ffff	/* # of AHB clk cycles in 1ms */

#घोषणा AR2315_LB_MISCCFG		0x000c

#घोषणा AR2315_LBM_TXD_EN	0x00000001	/* Enable TXD क्रम fragments */
#घोषणा AR2315_LBM_RX_INTEN	0x00000002	/* Enable LB पूर्णांकs on RX पढ़ोy */
#घोषणा AR2315_LBM_MBOXWR_INTEN	0x00000004	/* Enable LB पूर्णांकs on mbox wr */
#घोषणा AR2315_LBM_MBOXRD_INTEN	0x00000008	/* Enable LB पूर्णांकs on mbox rd */
#घोषणा AR2315_LMB_DESCSWAP_EN	0x00000010	/* Byte swap desc enable */
#घोषणा AR2315_LBM_TIMEOUT_M	0x00ffff80
#घोषणा AR2315_LBM_TIMEOUT_S	7
#घोषणा AR2315_LBM_PORTMUX	0x07000000

#घोषणा AR2315_LB_RXTSOFF		0x0010

#घोषणा AR2315_LB_TX_CHAIN_EN		0x0100

#घोषणा AR2315_LB_TXEN_0	0x00000001
#घोषणा AR2315_LB_TXEN_1	0x00000002
#घोषणा AR2315_LB_TXEN_2	0x00000004
#घोषणा AR2315_LB_TXEN_3	0x00000008

#घोषणा AR2315_LB_TX_CHAIN_DIS		0x0104
#घोषणा AR2315_LB_TX_DESC_PTR		0x0200

#घोषणा AR2315_LB_RX_CHAIN_EN		0x0400

#घोषणा AR2315_LB_RXEN		0x00000001

#घोषणा AR2315_LB_RX_CHAIN_DIS		0x0404
#घोषणा AR2315_LB_RX_DESC_PTR		0x0408

#घोषणा AR2315_LB_INT_STATUS		0x0500

#घोषणा AR2315_LB_INT_TX_DESC		0x00000001
#घोषणा AR2315_LB_INT_TX_OK		0x00000002
#घोषणा AR2315_LB_INT_TX_ERR		0x00000004
#घोषणा AR2315_LB_INT_TX_खातापूर्ण		0x00000008
#घोषणा AR2315_LB_INT_RX_DESC		0x00000010
#घोषणा AR2315_LB_INT_RX_OK		0x00000020
#घोषणा AR2315_LB_INT_RX_ERR		0x00000040
#घोषणा AR2315_LB_INT_RX_खातापूर्ण		0x00000080
#घोषणा AR2315_LB_INT_TX_TRUNC		0x00000100
#घोषणा AR2315_LB_INT_TX_STARVE		0x00000200
#घोषणा AR2315_LB_INT_LB_TIMEOUT	0x00000400
#घोषणा AR2315_LB_INT_LB_ERR		0x00000800
#घोषणा AR2315_LB_INT_MBOX_WR		0x00001000
#घोषणा AR2315_LB_INT_MBOX_RD		0x00002000

/* Bit definitions क्रम INT MASK are the same as INT_STATUS */
#घोषणा AR2315_LB_INT_MASK		0x0504

#घोषणा AR2315_LB_INT_EN		0x0508
#घोषणा AR2315_LB_MBOX			0x0600

#पूर्ण_अगर /* __ASM_MACH_ATH25_AR2315_REGS_H */
