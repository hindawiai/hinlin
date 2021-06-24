<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/***************************************************************************/

/*
 *	m53xx.c -- platक्रमm support क्रम ColdFire 53xx based boards
 *
 *	Copyright (C) 1999-2002, Greg Ungerer (gerg@snapgear.com)
 *	Copyright (C) 2000, Lineo (www.lineo.com)
 *	Yaroslav Vinograकरोv yaroslav.vinograकरोv@मुक्तscale.com
 *	Copyright Freescale Semiconductor, Inc 2006
 *	Copyright (c) 2006, emlix, Sebastian Hess <shess@hessware.de>
 */

/***************************************************************************/

#समावेश <linux/kernel.h>
#समावेश <linux/param.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/coldfire.h>
#समावेश <यंत्र/mcfsim.h>
#समावेश <यंत्र/mcfuart.h>
#समावेश <यंत्र/mcfdma.h>
#समावेश <यंत्र/mcfwdebug.h>
#समावेश <यंत्र/mcfclk.h>

/***************************************************************************/

DEFINE_CLK(0, "flexbus", 2, MCF_CLK);
DEFINE_CLK(0, "mcfcan.0", 8, MCF_CLK);
DEFINE_CLK(0, "fec.0", 12, MCF_CLK);
DEFINE_CLK(0, "edma", 17, MCF_CLK);
DEFINE_CLK(0, "intc.0", 18, MCF_CLK);
DEFINE_CLK(0, "intc.1", 19, MCF_CLK);
DEFINE_CLK(0, "iack.0", 21, MCF_CLK);
DEFINE_CLK(0, "imx1-i2c.0", 22, MCF_CLK);
DEFINE_CLK(0, "mcfqspi.0", 23, MCF_CLK);
DEFINE_CLK(0, "mcfuart.0", 24, MCF_BUSCLK);
DEFINE_CLK(0, "mcfuart.1", 25, MCF_BUSCLK);
DEFINE_CLK(0, "mcfuart.2", 26, MCF_BUSCLK);
DEFINE_CLK(0, "mcftmr.0", 28, MCF_CLK);
DEFINE_CLK(0, "mcftmr.1", 29, MCF_CLK);
DEFINE_CLK(0, "mcftmr.2", 30, MCF_CLK);
DEFINE_CLK(0, "mcftmr.3", 31, MCF_CLK);

DEFINE_CLK(0, "mcfpit.0", 32, MCF_CLK);
DEFINE_CLK(0, "mcfpit.1", 33, MCF_CLK);
DEFINE_CLK(0, "mcfpit.2", 34, MCF_CLK);
DEFINE_CLK(0, "mcfpit.3", 35, MCF_CLK);
DEFINE_CLK(0, "mcfpwm.0", 36, MCF_CLK);
DEFINE_CLK(0, "mcfeport.0", 37, MCF_CLK);
DEFINE_CLK(0, "mcfwdt.0", 38, MCF_CLK);
DEFINE_CLK(0, "sys.0", 40, MCF_BUSCLK);
DEFINE_CLK(0, "gpio.0", 41, MCF_BUSCLK);
DEFINE_CLK(0, "mcfrtc.0", 42, MCF_CLK);
DEFINE_CLK(0, "mcflcd.0", 43, MCF_CLK);
DEFINE_CLK(0, "mcfusb-otg.0", 44, MCF_CLK);
DEFINE_CLK(0, "mcfusb-host.0", 45, MCF_CLK);
DEFINE_CLK(0, "sdram.0", 46, MCF_CLK);
DEFINE_CLK(0, "ssi.0", 47, MCF_CLK);
DEFINE_CLK(0, "pll.0", 48, MCF_CLK);

DEFINE_CLK(1, "mdha.0", 32, MCF_CLK);
DEFINE_CLK(1, "skha.0", 33, MCF_CLK);
DEFINE_CLK(1, "rng.0", 34, MCF_CLK);

काष्ठा clk *mcf_clks[] = अणु
	&__clk_0_2,	/* flexbus */
	&__clk_0_8,	/* mcfcan.0 */
	&__clk_0_12,	/* fec.0 */
	&__clk_0_17,	/* edma */
	&__clk_0_18,	/* पूर्णांकc.0 */
	&__clk_0_19,	/* पूर्णांकc.1 */
	&__clk_0_21,	/* iack.0 */
	&__clk_0_22,	/* imx1-i2c.0 */
	&__clk_0_23,	/* mcfqspi.0 */
	&__clk_0_24,	/* mcfuart.0 */
	&__clk_0_25,	/* mcfuart.1 */
	&__clk_0_26,	/* mcfuart.2 */
	&__clk_0_28,	/* mcfपंचांगr.0 */
	&__clk_0_29,	/* mcfपंचांगr.1 */
	&__clk_0_30,	/* mcfपंचांगr.2 */
	&__clk_0_31,	/* mcfपंचांगr.3 */

	&__clk_0_32,	/* mcfpit.0 */
	&__clk_0_33,	/* mcfpit.1 */
	&__clk_0_34,	/* mcfpit.2 */
	&__clk_0_35,	/* mcfpit.3 */
	&__clk_0_36,	/* mcfpwm.0 */
	&__clk_0_37,	/* mcfeport.0 */
	&__clk_0_38,	/* mcfwdt.0 */
	&__clk_0_40,	/* sys.0 */
	&__clk_0_41,	/* gpio.0 */
	&__clk_0_42,	/* mcfrtc.0 */
	&__clk_0_43,	/* mcflcd.0 */
	&__clk_0_44,	/* mcfusb-otg.0 */
	&__clk_0_45,	/* mcfusb-host.0 */
	&__clk_0_46,	/* sdram.0 */
	&__clk_0_47,	/* ssi.0 */
	&__clk_0_48,	/* pll.0 */

	&__clk_1_32,	/* mdha.0 */
	&__clk_1_33,	/* skha.0 */
	&__clk_1_34,	/* rng.0 */
	शून्य,
पूर्ण;

अटल काष्ठा clk * स्थिर enable_clks[] __initस्थिर = अणु
	&__clk_0_2,	/* flexbus */
	&__clk_0_18,	/* पूर्णांकc.0 */
	&__clk_0_19,	/* पूर्णांकc.1 */
	&__clk_0_21,	/* iack.0 */
	&__clk_0_24,	/* mcfuart.0 */
	&__clk_0_25,	/* mcfuart.1 */
	&__clk_0_26,	/* mcfuart.2 */
	&__clk_0_28,	/* mcfपंचांगr.0 */
	&__clk_0_29,	/* mcfपंचांगr.1 */
	&__clk_0_32,	/* mcfpit.0 */
	&__clk_0_33,	/* mcfpit.1 */
	&__clk_0_37,	/* mcfeport.0 */
	&__clk_0_40,	/* sys.0 */
	&__clk_0_41,	/* gpio.0 */
	&__clk_0_46,	/* sdram.0 */
	&__clk_0_48,	/* pll.0 */
पूर्ण;

अटल काष्ठा clk * स्थिर disable_clks[] __initस्थिर = अणु
	&__clk_0_8,	/* mcfcan.0 */
	&__clk_0_12,	/* fec.0 */
	&__clk_0_17,	/* edma */
	&__clk_0_22,	/* imx1-i2c.0 */
	&__clk_0_23,	/* mcfqspi.0 */
	&__clk_0_30,	/* mcfपंचांगr.2 */
	&__clk_0_31,	/* mcfपंचांगr.3 */
	&__clk_0_34,	/* mcfpit.2 */
	&__clk_0_35,	/* mcfpit.3 */
	&__clk_0_36,	/* mcfpwm.0 */
	&__clk_0_38,	/* mcfwdt.0 */
	&__clk_0_42,	/* mcfrtc.0 */
	&__clk_0_43,	/* mcflcd.0 */
	&__clk_0_44,	/* mcfusb-otg.0 */
	&__clk_0_45,	/* mcfusb-host.0 */
	&__clk_0_47,	/* ssi.0 */
	&__clk_1_32,	/* mdha.0 */
	&__clk_1_33,	/* skha.0 */
	&__clk_1_34,	/* rng.0 */
पूर्ण;


अटल व्योम __init m53xx_clk_init(व्योम)
अणु
	अचिन्हित i;

	/* make sure these घड़ीs are enabled */
	क्रम (i = 0; i < ARRAY_SIZE(enable_clks); ++i)
		__clk_init_enabled(enable_clks[i]);
	/* make sure these घड़ीs are disabled */
	क्रम (i = 0; i < ARRAY_SIZE(disable_clks); ++i)
		__clk_init_disabled(disable_clks[i]);
पूर्ण

/***************************************************************************/

अटल व्योम __init m53xx_qspi_init(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_SPI_COLDFIRE_QSPI)
	/* setup QSPS pins क्रम QSPI with gpio CS control */
	ग_लिखोw(0x01f0, MCFGPIO_PAR_QSPI);
#पूर्ण_अगर /* IS_ENABLED(CONFIG_SPI_COLDFIRE_QSPI) */
पूर्ण

/***************************************************************************/

अटल व्योम __init m53xx_i2c_init(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_I2C_IMX)
	/* setup Port AS Pin Assignment Register क्रम I2C */
	/*  set PASPA0 to SCL and PASPA1 to SDA */
	u8 r = पढ़ोb(MCFGPIO_PAR_FECI2C);
	r |= 0x0f;
	ग_लिखोb(r, MCFGPIO_PAR_FECI2C);
#पूर्ण_अगर /* IS_ENABLED(CONFIG_I2C_IMX) */
पूर्ण

/***************************************************************************/

अटल व्योम __init m53xx_uarts_init(व्योम)
अणु
	/* UART GPIO initialization */
	ग_लिखोw(पढ़ोw(MCFGPIO_PAR_UART) | 0x0FFF, MCFGPIO_PAR_UART);
पूर्ण

/***************************************************************************/

अटल व्योम __init m53xx_fec_init(व्योम)
अणु
	u8 v;

	/* Set multi-function pins to ethernet mode क्रम fec0 */
	v = पढ़ोb(MCFGPIO_PAR_FECI2C);
	v |= MCF_GPIO_PAR_FECI2C_PAR_MDC_EMDC |
		MCF_GPIO_PAR_FECI2C_PAR_MDIO_EMDIO;
	ग_लिखोb(v, MCFGPIO_PAR_FECI2C);

	v = पढ़ोb(MCFGPIO_PAR_FEC);
	v = MCF_GPIO_PAR_FEC_PAR_FEC_7W_FEC | MCF_GPIO_PAR_FEC_PAR_FEC_MII_FEC;
	ग_लिखोb(v, MCFGPIO_PAR_FEC);
पूर्ण

/***************************************************************************/

व्योम __init config_BSP(अक्षर *commandp, पूर्णांक size)
अणु
#अगर !defined(CONFIG_BOOTPARAM)
	/* Copy command line from FLASH to local buffer... */
	स_नकल(commandp, (अक्षर *) 0x4000, 4);
	अगर(म_भेदन(commandp, "kcl ", 4) == 0)अणु
		स_नकल(commandp, (अक्षर *) 0x4004, size);
		commandp[size-1] = 0;
	पूर्ण अन्यथा अणु
		स_रखो(commandp, 0, size);
	पूर्ण
#पूर्ण_अगर
	mach_sched_init = hw_समयr_init;
	m53xx_clk_init();
	m53xx_uarts_init();
	m53xx_fec_init();
	m53xx_qspi_init();
	m53xx_i2c_init();

#अगर_घोषित CONFIG_BDM_DISABLE
	/*
	 * Disable the BDM घड़ीing.  This also turns off most of the rest of
	 * the BDM device.  This is good क्रम EMC reasons. This option is not
	 * incompatible with the memory protection option.
	 */
	wdebug(MCFDEBUG_CSR, MCFDEBUG_CSR_PSTCLK);
#पूर्ण_अगर
पूर्ण

/***************************************************************************/
/* Board initialization */
/***************************************************************************/
/* 
 * PLL min/max specअगरications
 */
#घोषणा MAX_FVCO	500000	/* KHz */
#घोषणा MAX_FSYS	80000 	/* KHz */
#घोषणा MIN_FSYS	58333 	/* KHz */
#घोषणा FREF		16000   /* KHz */


#घोषणा MAX_MFD		135     /* Multiplier */
#घोषणा MIN_MFD		88      /* Multiplier */
#घोषणा BUSDIV		6       /* Divider */

/*
 * Low Power Divider specअगरications
 */
#घोषणा MIN_LPD		(1 << 0)    /* Divider (not encoded) */
#घोषणा MAX_LPD		(1 << 15)   /* Divider (not encoded) */
#घोषणा DEFAULT_LPD	(1 << 1)	/* Divider (not encoded) */

#घोषणा SYS_CLK_KHZ	80000
#घोषणा SYSTEM_PERIOD	12.5
/*
 *  SDRAM Timing Parameters
 */  
#घोषणा SDRAM_BL	8	/* # of beats in a burst */
#घोषणा SDRAM_TWR	2	/* in घड़ीs */
#घोषणा SDRAM_CASL	2.5	/* CASL in घड़ीs */
#घोषणा SDRAM_TRCD	2	/* in घड़ीs */
#घोषणा SDRAM_TRP	2	/* in घड़ीs */
#घोषणा SDRAM_TRFC	7	/* in घड़ीs */
#घोषणा SDRAM_TREFI	7800	/* in ns */

#घोषणा EXT_SRAM_ADDRESS	(0xC0000000)
#घोषणा FLASH_ADDRESS		(0x00000000)
#घोषणा SDRAM_ADDRESS		(0x40000000)

#घोषणा न_अंकD_FLASH_ADDRESS	(0xD0000000)

व्योम wपंचांग_init(व्योम);
व्योम scm_init(व्योम);
व्योम gpio_init(व्योम);
व्योम fbcs_init(व्योम);
व्योम sdramc_init(व्योम);
पूर्णांक  घड़ी_pll (पूर्णांक fsys, पूर्णांक flags);
पूर्णांक  घड़ी_limp (पूर्णांक);
पूर्णांक  घड़ी_निकास_limp (व्योम);
पूर्णांक  get_sys_घड़ी (व्योम);

यंत्रlinkage व्योम __init sysinit(व्योम)
अणु
	घड़ी_pll(0, 0);

	wपंचांग_init();
	scm_init();
	gpio_init();
	fbcs_init();
	sdramc_init();
पूर्ण

व्योम wपंचांग_init(व्योम)
अणु
	/* Disable watchकरोg समयr */
	ग_लिखोw(0, MCF_WTM_WCR);
पूर्ण

#घोषणा MCF_SCM_BCR_GBW		(0x00000100)
#घोषणा MCF_SCM_BCR_GBR		(0x00000200)

व्योम scm_init(व्योम)
अणु
	/* All masters are trusted */
	ग_लिखोl(0x77777777, MCF_SCM_MPR);
    
	/* Allow supervisor/user, पढ़ो/ग_लिखो, and trusted/untrusted
	   access to all slaves */
	ग_लिखोl(0, MCF_SCM_PACRA);
	ग_लिखोl(0, MCF_SCM_PACRB);
	ग_लिखोl(0, MCF_SCM_PACRC);
	ग_लिखोl(0, MCF_SCM_PACRD);
	ग_लिखोl(0, MCF_SCM_PACRE);
	ग_लिखोl(0, MCF_SCM_PACRF);

	/* Enable bursts */
	ग_लिखोl(MCF_SCM_BCR_GBR | MCF_SCM_BCR_GBW, MCF_SCM_BCR);
पूर्ण


व्योम fbcs_init(व्योम)
अणु
	ग_लिखोb(0x3E, MCFGPIO_PAR_CS);

	/* Latch chip select */
	ग_लिखोl(0x10080000, MCF_FBCS1_CSAR);

	ग_लिखोl(0x002A3780, MCF_FBCS1_CSCR);
	ग_लिखोl(MCF_FBCS_CSMR_BAM_2M | MCF_FBCS_CSMR_V, MCF_FBCS1_CSMR);

	/* Initialize latch to drive संकेतs to inactive states */
	ग_लिखोw(0xffff, 0x10080000);

	/* External SRAM */
	ग_लिखोl(EXT_SRAM_ADDRESS, MCF_FBCS1_CSAR);
	ग_लिखोl(MCF_FBCS_CSCR_PS_16 |
		MCF_FBCS_CSCR_AA |
		MCF_FBCS_CSCR_SBM |
		MCF_FBCS_CSCR_WS(1),
		MCF_FBCS1_CSCR);
	ग_लिखोl(MCF_FBCS_CSMR_BAM_512K | MCF_FBCS_CSMR_V, MCF_FBCS1_CSMR);

	/* Boot Flash connected to FBCS0 */
	ग_लिखोl(FLASH_ADDRESS, MCF_FBCS0_CSAR);
	ग_लिखोl(MCF_FBCS_CSCR_PS_16 |
		MCF_FBCS_CSCR_BEM |
		MCF_FBCS_CSCR_AA |
		MCF_FBCS_CSCR_SBM |
		MCF_FBCS_CSCR_WS(7),
		MCF_FBCS0_CSCR);
	ग_लिखोl(MCF_FBCS_CSMR_BAM_32M | MCF_FBCS_CSMR_V, MCF_FBCS0_CSMR);
पूर्ण

व्योम sdramc_init(व्योम)
अणु
	/*
	 * Check to see अगर the SDRAM has alपढ़ोy been initialized
	 * by a run control tool
	 */
	अगर (!(पढ़ोl(MCF_SDRAMC_SDCR) & MCF_SDRAMC_SDCR_REF)) अणु
		/* SDRAM chip select initialization */
		
		/* Initialize SDRAM chip select */
		ग_लिखोl(MCF_SDRAMC_SDCS_BA(SDRAM_ADDRESS) |
			MCF_SDRAMC_SDCS_CSSZ(MCF_SDRAMC_SDCS_CSSZ_32MBYTE),
			MCF_SDRAMC_SDCS0);

	/*
	 * Basic configuration and initialization
	 */
	ग_लिखोl(MCF_SDRAMC_SDCFG1_SRD2RW((पूर्णांक)((SDRAM_CASL + 2) + 0.5)) |
		MCF_SDRAMC_SDCFG1_SWT2RD(SDRAM_TWR + 1) |
		MCF_SDRAMC_SDCFG1_RDLAT((पूर्णांक)((SDRAM_CASL * 2) + 2)) |
		MCF_SDRAMC_SDCFG1_ACT2RW((पूर्णांक)(SDRAM_TRCD + 0.5)) |
		MCF_SDRAMC_SDCFG1_PRE2ACT((पूर्णांक)(SDRAM_TRP + 0.5)) |
		MCF_SDRAMC_SDCFG1_REF2ACT((पूर्णांक)(SDRAM_TRFC + 0.5)) |
		MCF_SDRAMC_SDCFG1_WTLAT(3),
		MCF_SDRAMC_SDCFG1);
	ग_लिखोl(MCF_SDRAMC_SDCFG2_BRD2PRE(SDRAM_BL / 2 + 1) |
		MCF_SDRAMC_SDCFG2_BWT2RW(SDRAM_BL / 2 + SDRAM_TWR) |
		MCF_SDRAMC_SDCFG2_BRD2WT((पूर्णांक)((SDRAM_CASL + SDRAM_BL / 2 - 1.0) + 0.5)) |
		MCF_SDRAMC_SDCFG2_BL(SDRAM_BL - 1),
		MCF_SDRAMC_SDCFG2);

            
	/*
	 * Preअक्षरge and enable ग_लिखो to SDMR
	 */
	ग_लिखोl(MCF_SDRAMC_SDCR_MODE_EN |
		MCF_SDRAMC_SDCR_CKE |
		MCF_SDRAMC_SDCR_DDR |
		MCF_SDRAMC_SDCR_MUX(1) |
		MCF_SDRAMC_SDCR_RCNT((पूर्णांक)(((SDRAM_TREFI / (SYSTEM_PERIOD * 64)) - 1) + 0.5)) |
		MCF_SDRAMC_SDCR_PS_16 |
		MCF_SDRAMC_SDCR_IPALL,
		MCF_SDRAMC_SDCR);

	/*
	 * Write extended mode रेजिस्टर
	 */
	ग_लिखोl(MCF_SDRAMC_SDMR_BNKAD_LEMR |
		MCF_SDRAMC_SDMR_AD(0x0) |
		MCF_SDRAMC_SDMR_CMD,
		MCF_SDRAMC_SDMR);

	/*
	 * Write mode रेजिस्टर and reset DLL
	 */
	ग_लिखोl(MCF_SDRAMC_SDMR_BNKAD_LMR |
		MCF_SDRAMC_SDMR_AD(0x163) |
		MCF_SDRAMC_SDMR_CMD,
		MCF_SDRAMC_SDMR);

	/*
	 * Execute a PALL command
	 */
	ग_लिखोl(पढ़ोl(MCF_SDRAMC_SDCR) | MCF_SDRAMC_SDCR_IPALL, MCF_SDRAMC_SDCR);

	/*
	 * Perक्रमm two REF cycles
	 */
	ग_लिखोl(पढ़ोl(MCF_SDRAMC_SDCR) | MCF_SDRAMC_SDCR_IREF, MCF_SDRAMC_SDCR);
	ग_लिखोl(पढ़ोl(MCF_SDRAMC_SDCR) | MCF_SDRAMC_SDCR_IREF, MCF_SDRAMC_SDCR);

	/*
	 * Write mode रेजिस्टर and clear reset DLL
	 */
	ग_लिखोl(MCF_SDRAMC_SDMR_BNKAD_LMR |
		MCF_SDRAMC_SDMR_AD(0x063) |
		MCF_SDRAMC_SDMR_CMD,
		MCF_SDRAMC_SDMR);
				
	/*
	 * Enable स्वतः refresh and lock SDMR
	 */
	ग_लिखोl(पढ़ोl(MCF_SDRAMC_SDCR) & ~MCF_SDRAMC_SDCR_MODE_EN,
		MCF_SDRAMC_SDCR);
	ग_लिखोl(MCF_SDRAMC_SDCR_REF | MCF_SDRAMC_SDCR_DQS_OE(0xC),
		MCF_SDRAMC_SDCR);
	पूर्ण
पूर्ण

व्योम gpio_init(व्योम)
अणु
	/* Enable UART0 pins */
	ग_लिखोw(MCF_GPIO_PAR_UART_PAR_URXD0 | MCF_GPIO_PAR_UART_PAR_UTXD0,
		MCFGPIO_PAR_UART);

	/*
	 * Initialize TIN3 as a GPIO output to enable the ग_लिखो
	 * half of the latch.
	 */
	ग_लिखोb(0x00, MCFGPIO_PAR_TIMER);
	ग_लिखोb(0x08, MCFGPIO_PDDR_TIMER);
	ग_लिखोb(0x00, MCFGPIO_PCLRR_TIMER);
पूर्ण

पूर्णांक घड़ी_pll(पूर्णांक fsys, पूर्णांक flags)
अणु
	पूर्णांक fref, temp, fout, mfd;
	u32 i;

	fref = FREF;
        
	अगर (fsys == 0) अणु
		/* Return current PLL output */
		mfd = पढ़ोb(MCF_PLL_PFDR);

		वापस (fref * mfd / (BUSDIV * 4));
	पूर्ण

	/* Check bounds of requested प्रणाली घड़ी */
	अगर (fsys > MAX_FSYS)
		fsys = MAX_FSYS;
	अगर (fsys < MIN_FSYS)
		fsys = MIN_FSYS;

	/* Multiplying by 100 when calculating the temp value,
	   and then भागiding by 100 to calculate the mfd allows
	   क्रम exact values without needing to include भग्नing
	   poपूर्णांक libraries. */
	temp = 100 * fsys / fref;
	mfd = 4 * BUSDIV * temp / 100;
    	    	    	
	/* Determine the output frequency क्रम selected values */
	fout = (fref * mfd / (BUSDIV * 4));

	/*
	 * Check to see अगर the SDRAM has alपढ़ोy been initialized.
	 * If it has then the SDRAM needs to be put पूर्णांकo self refresh
	 * mode beक्रमe reprogramming the PLL.
	 */
	अगर (पढ़ोl(MCF_SDRAMC_SDCR) & MCF_SDRAMC_SDCR_REF)
		/* Put SDRAM पूर्णांकo self refresh mode */
		ग_लिखोl(पढ़ोl(MCF_SDRAMC_SDCR) & ~MCF_SDRAMC_SDCR_CKE,
			MCF_SDRAMC_SDCR);

	/*
	 * Initialize the PLL to generate the new प्रणाली घड़ी frequency.
	 * The device must be put पूर्णांकo LIMP mode to reprogram the PLL.
	 */

	/* Enter LIMP mode */
	घड़ी_limp(DEFAULT_LPD);
     					
	/* Reprogram PLL क्रम desired fsys */
	ग_लिखोb(MCF_PLL_PODR_CPUDIV(BUSDIV/3) | MCF_PLL_PODR_BUSDIV(BUSDIV),
		MCF_PLL_PODR);
						
	ग_लिखोb(mfd, MCF_PLL_PFDR);
		
	/* Exit LIMP mode */
	घड़ी_निकास_limp();
	
	/*
	 * Return the SDRAM to normal operation अगर it is in use.
	 */
	अगर (पढ़ोl(MCF_SDRAMC_SDCR) & MCF_SDRAMC_SDCR_REF)
		/* Exit self refresh mode */
		ग_लिखोl(पढ़ोl(MCF_SDRAMC_SDCR) | MCF_SDRAMC_SDCR_CKE,
			MCF_SDRAMC_SDCR);

	/* Errata - workaround क्रम SDRAM opeartion after निकासing LIMP mode */
	ग_लिखोl(MCF_SDRAMC_REFRESH, MCF_SDRAMC_LIMP_FIX);

	/* रुको क्रम DQS logic to relock */
	क्रम (i = 0; i < 0x200; i++)
		;

	वापस fout;
पूर्ण

पूर्णांक घड़ी_limp(पूर्णांक भाग)
अणु
	u32 temp;

	/* Check bounds of भागider */
	अगर (भाग < MIN_LPD)
		भाग = MIN_LPD;
	अगर (भाग > MAX_LPD)
		भाग = MAX_LPD;
    
	/* Save of the current value of the SSIDIV so we करोn't
	   overग_लिखो the value*/
	temp = पढ़ोw(MCF_CCM_CDR) & MCF_CCM_CDR_SSIDIV(0xF);
      
	/* Apply the भागider to the प्रणाली घड़ी */
	ग_लिखोw(MCF_CCM_CDR_LPDIV(भाग) | MCF_CCM_CDR_SSIDIV(temp), MCF_CCM_CDR);
    
	ग_लिखोw(पढ़ोw(MCF_CCM_MISCCR) | MCF_CCM_MISCCR_LIMP, MCF_CCM_MISCCR);
    
	वापस (FREF/(3*(1 << भाग)));
पूर्ण

पूर्णांक घड़ी_निकास_limp(व्योम)
अणु
	पूर्णांक fout;
	
	/* Exit LIMP mode */
	ग_लिखोw(पढ़ोw(MCF_CCM_MISCCR) & ~MCF_CCM_MISCCR_LIMP, MCF_CCM_MISCCR);

	/* Wait क्रम PLL to lock */
	जबतक (!(पढ़ोw(MCF_CCM_MISCCR) & MCF_CCM_MISCCR_PLL_LOCK))
		;
	
	fout = get_sys_घड़ी();

	वापस fout;
पूर्ण

पूर्णांक get_sys_घड़ी(व्योम)
अणु
	पूर्णांक भागider;
	
	/* Test to see अगर device is in LIMP mode */
	अगर (पढ़ोw(MCF_CCM_MISCCR) & MCF_CCM_MISCCR_LIMP) अणु
		भागider = पढ़ोw(MCF_CCM_CDR) & MCF_CCM_CDR_LPDIV(0xF);
		वापस (FREF/(2 << भागider));
	पूर्ण
	अन्यथा
		वापस (FREF * पढ़ोb(MCF_PLL_PFDR)) / (BUSDIV * 4);
पूर्ण
