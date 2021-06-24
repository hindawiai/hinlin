<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2010 Broadcom Corporation
 */

#अगर_अघोषित	_SBCHIPC_H
#घोषणा	_SBCHIPC_H

#समावेश "defs.h"		/* क्रम PAD macro */

#घोषणा CHIPCREGOFFS(field)	दुरत्व(काष्ठा chipcregs, field)

काष्ठा chipcregs अणु
	u32 chipid;		/* 0x0 */
	u32 capabilities;
	u32 corecontrol;	/* corerev >= 1 */
	u32 bist;

	/* OTP */
	u32 otpstatus;	/* 0x10, corerev >= 10 */
	u32 otpcontrol;
	u32 otpprog;
	u32 otplayout;	/* corerev >= 23 */

	/* Interrupt control */
	u32 पूर्णांकstatus;	/* 0x20 */
	u32 पूर्णांकmask;

	/* Chip specअगरic regs */
	u32 chipcontrol;	/* 0x28, rev >= 11 */
	u32 chipstatus;	/* 0x2c, rev >= 11 */

	/* Jtag Master */
	u32 jtagcmd;		/* 0x30, rev >= 10 */
	u32 jtagir;
	u32 jtagdr;
	u32 jtagctrl;

	/* serial flash पूर्णांकerface रेजिस्टरs */
	u32 flashcontrol;	/* 0x40 */
	u32 flashaddress;
	u32 flashdata;
	u32 PAD[1];

	/* Silicon backplane configuration broadcast control */
	u32 broadcastaddress;	/* 0x50 */
	u32 broadcastdata;

	/* gpio - cleared only by घातer-on-reset */
	u32 gpiopullup;	/* 0x58, corerev >= 20 */
	u32 gpiopullकरोwn;	/* 0x5c, corerev >= 20 */
	u32 gpioin;		/* 0x60 */
	u32 gpioout;		/* 0x64 */
	u32 gpioouten;	/* 0x68 */
	u32 gpiocontrol;	/* 0x6C */
	u32 gpioपूर्णांकpolarity;	/* 0x70 */
	u32 gpioपूर्णांकmask;	/* 0x74 */

	/* GPIO events corerev >= 11 */
	u32 gpioevent;
	u32 gpioeventपूर्णांकmask;

	/* Watchकरोg समयr */
	u32 watchकरोg;	/* 0x80 */

	/* GPIO events corerev >= 11 */
	u32 gpioeventपूर्णांकpolarity;

	/* GPIO based LED घातersave रेजिस्टरs corerev >= 16 */
	u32 gpioसमयrval;	/* 0x88 */
	u32 gpioसमयrouपंचांगask;

	/* घड़ी control */
	u32 घड़ीcontrol_n;	/* 0x90 */
	u32 घड़ीcontrol_sb;	/* aka m0 */
	u32 घड़ीcontrol_pci;	/* aka m1 */
	u32 घड़ीcontrol_m2;	/* mii/uart/mipsref */
	u32 घड़ीcontrol_m3;	/* cpu */
	u32 clkभाग;		/* corerev >= 3 */
	u32 gpiodebugsel;	/* corerev >= 28 */
	u32 capabilities_ext;	/* 0xac  */

	/* pll delay रेजिस्टरs (corerev >= 4) */
	u32 pll_on_delay;	/* 0xb0 */
	u32 fref_sel_delay;
	u32 slow_clk_ctl;	/* 5 < corerev < 10 */
	u32 PAD;

	/* Instaघड़ी रेजिस्टरs (corerev >= 10) */
	u32 प्रणाली_clk_ctl;	/* 0xc0 */
	u32 clkstatestretch;
	u32 PAD[2];

	/* Indirect backplane access (corerev >= 22) */
	u32 bp_addrlow;	/* 0xd0 */
	u32 bp_addrhigh;
	u32 bp_data;
	u32 PAD;
	u32 bp_indaccess;
	u32 PAD[3];

	/* More घड़ी भागiders (corerev >= 32) */
	u32 clkभाग2;
	u32 PAD[2];

	/* In AI chips, poपूर्णांकer to erom */
	u32 eromptr;		/* 0xfc */

	/* ExtBus control रेजिस्टरs (corerev >= 3) */
	u32 pcmcia_config;	/* 0x100 */
	u32 pcmcia_memरुको;
	u32 pcmcia_attrरुको;
	u32 pcmcia_ioरुको;
	u32 ide_config;
	u32 ide_memरुको;
	u32 ide_attrरुको;
	u32 ide_ioरुको;
	u32 prog_config;
	u32 prog_रुकोcount;
	u32 flash_config;
	u32 flash_रुकोcount;
	u32 SECI_config;	/* 0x130 SECI configuration */
	u32 PAD[3];

	/* Enhanced Coexistence Interface (ECI) रेजिस्टरs (corerev >= 21) */
	u32 eci_output;	/* 0x140 */
	u32 eci_control;
	u32 eci_inputlo;
	u32 eci_inpuपंचांगi;
	u32 eci_inputhi;
	u32 eci_inputपूर्णांकpolaritylo;
	u32 eci_inputपूर्णांकpolaritymi;
	u32 eci_inputपूर्णांकpolarityhi;
	u32 eci_पूर्णांकmasklo;
	u32 eci_पूर्णांकmaskmi;
	u32 eci_पूर्णांकmaskhi;
	u32 eci_eventlo;
	u32 eci_evenपंचांगi;
	u32 eci_eventhi;
	u32 eci_evenपंचांगasklo;
	u32 eci_evenपंचांगaskmi;
	u32 eci_evenपंचांगaskhi;
	u32 PAD[3];

	/* SROM पूर्णांकerface (corerev >= 32) */
	u32 sromcontrol;	/* 0x190 */
	u32 sromaddress;
	u32 sromdata;
	u32 PAD[17];

	/* Clock control and hardware workarounds (corerev >= 20) */
	u32 clk_ctl_st;	/* 0x1e0 */
	u32 hw_war;
	u32 PAD[70];

	/* UARTs */
	u8 uart0data;	/* 0x300 */
	u8 uart0imr;
	u8 uart0fcr;
	u8 uart0lcr;
	u8 uart0mcr;
	u8 uart0lsr;
	u8 uart0msr;
	u8 uart0scratch;
	u8 PAD[248];		/* corerev >= 1 */

	u8 uart1data;	/* 0x400 */
	u8 uart1imr;
	u8 uart1fcr;
	u8 uart1lcr;
	u8 uart1mcr;
	u8 uart1lsr;
	u8 uart1msr;
	u8 uart1scratch;
	u32 PAD[62];

	/* save/restore, corerev >= 48 */
	u32 sr_capability;          /* 0x500 */
	u32 sr_control0;            /* 0x504 */
	u32 sr_control1;            /* 0x508 */
	u32 gpio_control;           /* 0x50C */
	u32 PAD[60];

	/* PMU रेजिस्टरs (corerev >= 20) */
	u32 pmucontrol;	/* 0x600 */
	u32 pmucapabilities;
	u32 pmustatus;
	u32 res_state;
	u32 res_pending;
	u32 pmuसमयr;
	u32 min_res_mask;
	u32 max_res_mask;
	u32 res_table_sel;
	u32 res_dep_mask;
	u32 res_updn_समयr;
	u32 res_समयr;
	u32 clkstretch;
	u32 pmuwatchकरोg;
	u32 gpiosel;		/* 0x638, rev >= 1 */
	u32 gpioenable;	/* 0x63c, rev >= 1 */
	u32 res_req_समयr_sel;
	u32 res_req_समयr;
	u32 res_req_mask;
	u32 pmucapabilities_ext; /* 0x64c, pmurev >=15 */
	u32 chipcontrol_addr;	/* 0x650 */
	u32 chipcontrol_data;	/* 0x654 */
	u32 regcontrol_addr;
	u32 regcontrol_data;
	u32 pllcontrol_addr;
	u32 pllcontrol_data;
	u32 pmustrapopt;	/* 0x668, corerev >= 28 */
	u32 pmu_xtalfreq;	/* 0x66C, pmurev >= 10 */
	u32 retention_ctl;          /* 0x670, pmurev >= 15 */
	u32 PAD[3];
	u32 retention_grpidx;       /* 0x680 */
	u32 retention_grpctl;       /* 0x684 */
	u32 PAD[94];
	u16 sromotp[768];
पूर्ण;

/* chipid */
#घोषणा	CID_ID_MASK		0x0000ffff	/* Chip Id mask */
#घोषणा	CID_REV_MASK		0x000f0000	/* Chip Revision mask */
#घोषणा	CID_REV_SHIFT		16	/* Chip Revision shअगरt */
#घोषणा	CID_PKG_MASK		0x00f00000	/* Package Option mask */
#घोषणा	CID_PKG_SHIFT		20	/* Package Option shअगरt */
#घोषणा	CID_CC_MASK		0x0f000000	/* CoreCount (corerev >= 4) */
#घोषणा CID_CC_SHIFT		24
#घोषणा	CID_TYPE_MASK		0xf0000000	/* Chip Type */
#घोषणा CID_TYPE_SHIFT		28

/* capabilities */
#घोषणा	CC_CAP_UARTS_MASK	0x00000003	/* Number of UARTs */
#घोषणा CC_CAP_MIPSEB		0x00000004	/* MIPS is in big-endian mode */
#घोषणा CC_CAP_UCLKSEL		0x00000018	/* UARTs घड़ी select */
/* UARTs are driven by पूर्णांकernal भागided घड़ी */
#घोषणा CC_CAP_UINTCLK		0x00000008
#घोषणा CC_CAP_UARTGPIO		0x00000020	/* UARTs own GPIOs 15:12 */
#घोषणा CC_CAP_EXTBUS_MASK	0x000000c0	/* External bus mask */
#घोषणा CC_CAP_EXTBUS_NONE	0x00000000	/* No ExtBus present */
#घोषणा CC_CAP_EXTBUS_FULL	0x00000040	/* ExtBus: PCMCIA, IDE & Prog */
#घोषणा CC_CAP_EXTBUS_PROG	0x00000080	/* ExtBus: ProgIf only */
#घोषणा	CC_CAP_FLASH_MASK	0x00000700	/* Type of flash */
#घोषणा	CC_CAP_PLL_MASK		0x00038000	/* Type of PLL */
#घोषणा CC_CAP_PWR_CTL		0x00040000	/* Power control */
#घोषणा CC_CAP_OTPSIZE		0x00380000	/* OTP Size (0 = none) */
#घोषणा CC_CAP_OTPSIZE_SHIFT	19	/* OTP Size shअगरt */
#घोषणा CC_CAP_OTPSIZE_BASE	5	/* OTP Size base */
#घोषणा CC_CAP_JTAGP		0x00400000	/* JTAG Master Present */
#घोषणा CC_CAP_ROM		0x00800000	/* Internal boot rom active */
#घोषणा CC_CAP_BKPLN64		0x08000000	/* 64-bit backplane */
#घोषणा	CC_CAP_PMU		0x10000000	/* PMU Present, rev >= 20 */
#घोषणा	CC_CAP_SROM		0x40000000	/* Srom Present, rev >= 32 */
/* Nand flash present, rev >= 35 */
#घोषणा	CC_CAP_NFLASH		0x80000000

#घोषणा	CC_CAP2_SECI		0x00000001	/* SECI Present, rev >= 36 */
/* GSIO (spi/i2c) present, rev >= 37 */
#घोषणा	CC_CAP2_GSIO		0x00000002

/* sr_control0, rev >= 48 */
#घोषणा CC_SR_CTL0_ENABLE_MASK			BIT(0)
#घोषणा CC_SR_CTL0_ENABLE_SHIFT		0
#घोषणा CC_SR_CTL0_EN_SR_ENG_CLK_SHIFT	1 /* sr_clk to sr_memory enable */
#घोषणा CC_SR_CTL0_RSRC_TRIGGER_SHIFT	2 /* Rising edge resource trigger 0 to
					   * sr_engine
					   */
#घोषणा CC_SR_CTL0_MIN_DIV_SHIFT	6 /* Min भागision value क्रम fast clk
					   * in sr_engine
					   */
#घोषणा CC_SR_CTL0_EN_SBC_STBY_SHIFT		16
#घोषणा CC_SR_CTL0_EN_SR_ALP_CLK_MASK_SHIFT	18
#घोषणा CC_SR_CTL0_EN_SR_HT_CLK_SHIFT		19
#घोषणा CC_SR_CTL0_ALLOW_PIC_SHIFT	20 /* Allow pic to separate घातer
					    * करोमुख्यs
					    */
#घोषणा CC_SR_CTL0_MAX_SR_LQ_CLK_CNT_SHIFT	25
#घोषणा CC_SR_CTL0_EN_MEM_DISABLE_FOR_SLEEP	30

/* pmucapabilities */
#घोषणा PCAP_REV_MASK	0x000000ff
#घोषणा PCAP_RC_MASK	0x00001f00
#घोषणा PCAP_RC_SHIFT	8
#घोषणा PCAP_TC_MASK	0x0001e000
#घोषणा PCAP_TC_SHIFT	13
#घोषणा PCAP_PC_MASK	0x001e0000
#घोषणा PCAP_PC_SHIFT	17
#घोषणा PCAP_VC_MASK	0x01e00000
#घोषणा PCAP_VC_SHIFT	21
#घोषणा PCAP_CC_MASK	0x1e000000
#घोषणा PCAP_CC_SHIFT	25
#घोषणा PCAP5_PC_MASK	0x003e0000	/* PMU corerev >= 5 */
#घोषणा PCAP5_PC_SHIFT	17
#घोषणा PCAP5_VC_MASK	0x07c00000
#घोषणा PCAP5_VC_SHIFT	22
#घोषणा PCAP5_CC_MASK	0xf8000000
#घोषणा PCAP5_CC_SHIFT	27
/* pmucapabilites_ext PMU rev >= 15 */
#घोषणा PCAPEXT_SR_SUPPORTED_MASK	(1 << 1)
/* retention_ctl PMU rev >= 15 */
#घोषणा PMU_RCTL_MACPHY_DISABLE_MASK        (1 << 26)
#घोषणा PMU_RCTL_LOGIC_DISABLE_MASK         (1 << 27)


/*
* Maximum delay क्रम the PMU state transition in us.
* This is an upper bound पूर्णांकended क्रम spinरुकोs etc.
*/
#घोषणा PMU_MAX_TRANSITION_DLY	15000

#पूर्ण_अगर				/* _SBCHIPC_H */
