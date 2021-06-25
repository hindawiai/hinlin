<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Old U-boot compatibility क्रम Acadia
 *
 * Author: Josh Boyer <jwboyer@linux.vnet.ibm.com>
 *
 * Copyright 2008 IBM Corporation
 */

#समावेश "ops.h"
#समावेश "io.h"
#समावेश "dcr.h"
#समावेश "stdio.h"
#समावेश "4xx.h"
#समावेश "44x.h"
#समावेश "cuboot.h"

#घोषणा TARGET_4xx
#समावेश "ppcboot.h"

अटल bd_t bd;

#घोषणा CPR_PERD0_SPIDV_MASK   0x000F0000     /* SPI Clock Divider */

#घोषणा PLLC_SRC_MASK	       0x20000000     /* PLL feedback source */

#घोषणा PLLD_FBDV_MASK	       0x1F000000     /* PLL feedback भागider value */
#घोषणा PLLD_FWDVA_MASK        0x000F0000     /* PLL क्रमward भागider A value */
#घोषणा PLLD_FWDVB_MASK        0x00000700     /* PLL क्रमward भागider B value */

#घोषणा PRIMAD_CPUDV_MASK      0x0F000000     /* CPU Clock Divisor Mask */
#घोषणा PRIMAD_PLBDV_MASK      0x000F0000     /* PLB Clock Divisor Mask */
#घोषणा PRIMAD_OPBDV_MASK      0x00000F00     /* OPB Clock Divisor Mask */
#घोषणा PRIMAD_EBCDV_MASK      0x0000000F     /* EBC Clock Divisor Mask */

#घोषणा PERD0_PWMDV_MASK       0xFF000000     /* PWM Divider Mask */
#घोषणा PERD0_SPIDV_MASK       0x000F0000     /* SPI Divider Mask */
#घोषणा PERD0_U0DV_MASK        0x0000FF00     /* UART 0 Divider Mask */
#घोषणा PERD0_U1DV_MASK        0x000000FF     /* UART 1 Divider Mask */

अटल व्योम get_घड़ीs(व्योम)
अणु
	अचिन्हित दीर्घ sysclk, cpr_plld, cpr_pllc, cpr_primad, plloutb, i;
	अचिन्हित दीर्घ pllFwdDiv, pllFwdDivB, pllFbkDiv, pllPlbDiv, pllExtBusDiv;
	अचिन्हित दीर्घ pllOpbDiv, freqEBC, freqUART, freqOPB;
	अचिन्हित दीर्घ भाग;		/* total भागisor uभाग * bभाग */
	अचिन्हित दीर्घ umin;		/* minimum uभाग	*/
	अचिन्हित लघु dअगरf;		/* smallest dअगरf */
	अचिन्हित दीर्घ uभाग;		/* best uभाग */
	अचिन्हित लघु idअगरf;		/* current dअगरf */
	अचिन्हित लघु ibभाग;		/* current bभाग */
	अचिन्हित दीर्घ est;		/* current estimate */
	अचिन्हित दीर्घ baud;
	व्योम *np;

	/* पढ़ो the sysclk value from the CPLD */
	sysclk = (in_8((अचिन्हित अक्षर *)0x80000000) == 0xc) ? 66666666 : 33333000;

	/*
	 * Read PLL Mode रेजिस्टरs
	 */
	cpr_plld = CPR0_READ(DCRN_CPR0_PLLD);
	cpr_pllc = CPR0_READ(DCRN_CPR0_PLLC);

	/*
	 * Determine क्रमward भागider A
	 */
	pllFwdDiv = ((cpr_plld & PLLD_FWDVA_MASK) >> 16);

	/*
	 * Determine क्रमward भागider B
	 */
	pllFwdDivB = ((cpr_plld & PLLD_FWDVB_MASK) >> 8);
	अगर (pllFwdDivB == 0)
		pllFwdDivB = 8;

	/*
	 * Determine FBK_DIV.
	 */
	pllFbkDiv = ((cpr_plld & PLLD_FBDV_MASK) >> 24);
	अगर (pllFbkDiv == 0)
		pllFbkDiv = 256;

	/*
	 * Read CPR_PRIMAD रेजिस्टर
	 */
	cpr_primad = CPR0_READ(DCRN_CPR0_PRIMAD);

	/*
	 * Determine PLB_DIV.
	 */
	pllPlbDiv = ((cpr_primad & PRIMAD_PLBDV_MASK) >> 16);
	अगर (pllPlbDiv == 0)
		pllPlbDiv = 16;

	/*
	 * Determine EXTBUS_DIV.
	 */
	pllExtBusDiv = (cpr_primad & PRIMAD_EBCDV_MASK);
	अगर (pllExtBusDiv == 0)
		pllExtBusDiv = 16;

	/*
	 * Determine OPB_DIV.
	 */
	pllOpbDiv = ((cpr_primad & PRIMAD_OPBDV_MASK) >> 8);
	अगर (pllOpbDiv == 0)
		pllOpbDiv = 16;

	/* There is a bug in U-Boot that prevents us from using
	 * bd.bi_opbfreq because U-Boot करोesn't populate it क्रम
	 * 405EZ.  We get to calculate it, yay!
	 */
	freqOPB = (sysclk *pllFbkDiv) /pllOpbDiv;

	freqEBC = (sysclk * pllFbkDiv) / pllExtBusDiv;

	plloutb = ((sysclk * ((cpr_pllc & PLLC_SRC_MASK) ?
					   pllFwdDivB : pllFwdDiv) *
		    pllFbkDiv) / pllFwdDivB);

	np = find_node_by_alias("serial0");
	अगर (getprop(np, "current-speed", &baud, माप(baud)) != माप(baud))
		fatal("no current-speed property\n\r");

	uभाग = 256;			/* Assume lowest possible serial clk */
	भाग = plloutb / (16 * baud); /* total भागisor */
	umin = (plloutb / freqOPB) << 1;	/* 2 x OPB भागisor */
	dअगरf = 256;			/* highest possible */

	/* i is the test uभाग value -- start with the largest
	 * possible (256) to minimize serial घड़ी and स्थिरrain
	 * search to umin.
	 */
	क्रम (i = 256; i > umin; i--) अणु
		ibभाग = भाग / i;
		est = i * ibभाग;
		idअगरf = (est > भाग) ? (est-भाग) : (भाग-est);
		अगर (idअगरf == 0) अणु
			uभाग = i;
			अवरोध;      /* can't करो better */
		पूर्ण अन्यथा अगर (idअगरf < dअगरf) अणु
			uभाग = i;       /* best so far */
			dअगरf = idअगरf;   /* update lowest dअगरf*/
		पूर्ण
	पूर्ण
	freqUART = plloutb / uभाग;

	dt_fixup_cpu_घड़ीs(bd.bi_procfreq, bd.bi_पूर्णांकfreq, bd.bi_plb_busfreq);
	dt_fixup_घड़ी("/plb/ebc", freqEBC);
	dt_fixup_घड़ी("/plb/opb", freqOPB);
	dt_fixup_घड़ी("/plb/opb/serial@ef600300", freqUART);
	dt_fixup_घड़ी("/plb/opb/serial@ef600400", freqUART);
पूर्ण

अटल व्योम acadia_fixups(व्योम)
अणु
	dt_fixup_memory(bd.bi_memstart, bd.bi_memsize);
	get_घड़ीs();
	dt_fixup_mac_address_by_alias("ethernet0", bd.bi_enetaddr);
पूर्ण
	
व्योम platक्रमm_init(अचिन्हित दीर्घ r3, अचिन्हित दीर्घ r4, अचिन्हित दीर्घ r5,
		अचिन्हित दीर्घ r6, अचिन्हित दीर्घ r7)
अणु
	CUBOOT_INIT();
	platक्रमm_ops.fixups = acadia_fixups;
	platक्रमm_ops.निकास = ibm40x_dbcr_reset;
	fdt_init(_dtb_start);
	serial_console_init();
पूर्ण
