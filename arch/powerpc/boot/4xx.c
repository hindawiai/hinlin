<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2007 David Gibson, IBM Corporation.
 *
 * Based on earlier code:
 *   Matt Porter <mporter@kernel.crashing.org>
 *   Copyright 2002-2005 MontaVista Software Inc.
 *
 *   Eugene Surovegin <eugene.surovegin@zultys.com> or <ebs@ebshome.net>
 *   Copyright (c) 2003, 2004 Zultys Technologies
 *
 * Copyright (C) 2009 Wind River Systems, Inc.
 *   Updated क्रम supporting PPC405EX on Kilauea.
 *   Tiejun Chen <tiejun.chen@windriver.com>
 */
#समावेश <मानकघोष.स>
#समावेश "types.h"
#समावेश "string.h"
#समावेश "stdio.h"
#समावेश "ops.h"
#समावेश "reg.h"
#समावेश "dcr.h"

अटल अचिन्हित दीर्घ chip_11_errata(अचिन्हित दीर्घ memsize)
अणु
	अचिन्हित दीर्घ pvr;

	pvr = mfpvr();

	चयन (pvr & 0xf0000ff0) अणु
		हाल 0x40000850:
		हाल 0x400008d0:
		हाल 0x200008d0:
			memsize -= 4096;
			अवरोध;
		शेष:
			अवरोध;
	पूर्ण

	वापस memsize;
पूर्ण

/* Read the 4xx SDRAM controller to get size of प्रणाली memory. */
व्योम ibm4xx_sdram_fixup_memsize(व्योम)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ memsize, bank_config;

	memsize = 0;
	क्रम (i = 0; i < ARRAY_SIZE(sdram_bxcr); i++) अणु
		bank_config = SDRAM0_READ(sdram_bxcr[i]);
		अगर (bank_config & SDRAM_CONFIG_BANK_ENABLE)
			memsize += SDRAM_CONFIG_BANK_SIZE(bank_config);
	पूर्ण

	memsize = chip_11_errata(memsize);
	dt_fixup_memory(0, memsize);
पूर्ण

/* Read the 440SPe MQ controller to get size of प्रणाली memory. */
#घोषणा DCRN_MQ0_B0BAS		0x40
#घोषणा DCRN_MQ0_B1BAS		0x41
#घोषणा DCRN_MQ0_B2BAS		0x42
#घोषणा DCRN_MQ0_B3BAS		0x43

अटल u64 ibm440spe_decode_bas(u32 bas)
अणु
	u64 base = ((u64)(bas & 0xFFE00000u)) << 2;

	/* खोलो coded because I'm paranoid about invalid values */
	चयन ((bas >> 4) & 0xFFF) अणु
	हाल 0:
		वापस 0;
	हाल 0xffc:
		वापस base + 0x000800000ull;
	हाल 0xff8:
		वापस base + 0x001000000ull;
	हाल 0xff0:
		वापस base + 0x002000000ull;
	हाल 0xfe0:
		वापस base + 0x004000000ull;
	हाल 0xfc0:
		वापस base + 0x008000000ull;
	हाल 0xf80:
		वापस base + 0x010000000ull;
	हाल 0xf00:
		वापस base + 0x020000000ull;
	हाल 0xe00:
		वापस base + 0x040000000ull;
	हाल 0xc00:
		वापस base + 0x080000000ull;
	हाल 0x800:
		वापस base + 0x100000000ull;
	पूर्ण
	म_लिखो("Memory BAS value 0x%08x unsupported !\n", bas);
	वापस 0;
पूर्ण

व्योम ibm440spe_fixup_memsize(व्योम)
अणु
	u64 banktop, memsize = 0;

	/* Ultimately, we should directly स्थिरruct the memory node
	 * so we are able to handle holes in the memory address space
	 */
	banktop = ibm440spe_decode_bas(mfdcr(DCRN_MQ0_B0BAS));
	अगर (banktop > memsize)
		memsize = banktop;
	banktop = ibm440spe_decode_bas(mfdcr(DCRN_MQ0_B1BAS));
	अगर (banktop > memsize)
		memsize = banktop;
	banktop = ibm440spe_decode_bas(mfdcr(DCRN_MQ0_B2BAS));
	अगर (banktop > memsize)
		memsize = banktop;
	banktop = ibm440spe_decode_bas(mfdcr(DCRN_MQ0_B3BAS));
	अगर (banktop > memsize)
		memsize = banktop;

	dt_fixup_memory(0, memsize);
पूर्ण


/* 4xx DDR1/2 Denali memory controller support */
/* DDR0 रेजिस्टरs */
#घोषणा DDR0_02			2
#घोषणा DDR0_08			8
#घोषणा DDR0_10			10
#घोषणा DDR0_14			14
#घोषणा DDR0_42			42
#घोषणा DDR0_43			43

/* DDR0_02 */
#घोषणा DDR_START		0x1
#घोषणा DDR_START_SHIFT		0
#घोषणा DDR_MAX_CS_REG		0x3
#घोषणा DDR_MAX_CS_REG_SHIFT	24
#घोषणा DDR_MAX_COL_REG		0xf
#घोषणा DDR_MAX_COL_REG_SHIFT	16
#घोषणा DDR_MAX_ROW_REG		0xf
#घोषणा DDR_MAX_ROW_REG_SHIFT	8
/* DDR0_08 */
#घोषणा DDR_DDR2_MODE		0x1
#घोषणा DDR_DDR2_MODE_SHIFT	0
/* DDR0_10 */
#घोषणा DDR_CS_MAP		0x3
#घोषणा DDR_CS_MAP_SHIFT	8
/* DDR0_14 */
#घोषणा DDR_REDUC		0x1
#घोषणा DDR_REDUC_SHIFT		16
/* DDR0_42 */
#घोषणा DDR_APIN		0x7
#घोषणा DDR_APIN_SHIFT		24
/* DDR0_43 */
#घोषणा DDR_COL_SZ		0x7
#घोषणा DDR_COL_SZ_SHIFT	8
#घोषणा DDR_BANK8		0x1
#घोषणा DDR_BANK8_SHIFT		0

#घोषणा DDR_GET_VAL(val, mask, shअगरt)	(((val) >> (shअगरt)) & (mask))

/*
 * Some U-Boot versions set the number of chipselects to two
 * क्रम Sequoia/Rainier boards जबतक they only have one chipselect
 * hardwired. Hardcode the number of chipselects to one
 * क्रम sequioa/rainer board models or पढ़ो the actual value
 * from the memory controller रेजिस्टर DDR0_10 otherwise.
 */
अटल अंतरभूत u32 ibm4xx_denali_get_cs(व्योम)
अणु
	व्योम *devp;
	अक्षर model[64];
	u32 val, cs;

	devp = finddevice("/");
	अगर (!devp)
		जाओ पढ़ो_cs;

	अगर (getprop(devp, "model", model, माप(model)) <= 0)
		जाओ पढ़ो_cs;

	model[माप(model)-1] = 0;

	अगर (!म_भेद(model, "amcc,sequoia") ||
	    !म_भेद(model, "amcc,rainier"))
		वापस 1;

पढ़ो_cs:
	/* get CS value */
	val = SDRAM0_READ(DDR0_10);

	val = DDR_GET_VAL(val, DDR_CS_MAP, DDR_CS_MAP_SHIFT);
	cs = 0;
	जबतक (val) अणु
		अगर (val & 0x1)
			cs++;
		val = val >> 1;
	पूर्ण
	वापस cs;
पूर्ण

व्योम ibm4xx_denali_fixup_memsize(व्योम)
अणु
	u32 val, max_cs, max_col, max_row;
	u32 cs, col, row, bank, dpath;
	अचिन्हित दीर्घ memsize;

	val = SDRAM0_READ(DDR0_02);
	अगर (!DDR_GET_VAL(val, DDR_START, DDR_START_SHIFT))
		fatal("DDR controller is not initialized\n");

	/* get maximum cs col and row values */
	max_cs  = DDR_GET_VAL(val, DDR_MAX_CS_REG, DDR_MAX_CS_REG_SHIFT);
	max_col = DDR_GET_VAL(val, DDR_MAX_COL_REG, DDR_MAX_COL_REG_SHIFT);
	max_row = DDR_GET_VAL(val, DDR_MAX_ROW_REG, DDR_MAX_ROW_REG_SHIFT);

	cs = ibm4xx_denali_get_cs();
	अगर (!cs)
		fatal("No memory installed\n");
	अगर (cs > max_cs)
		fatal("DDR wrong CS configuration\n");

	/* get data path bytes */
	val = SDRAM0_READ(DDR0_14);

	अगर (DDR_GET_VAL(val, DDR_REDUC, DDR_REDUC_SHIFT))
		dpath = 4; /* 32 bits */
	अन्यथा
		dpath = 8; /* 64 bits */

	/* get address pins (rows) */
	val = SDRAM0_READ(DDR0_42);

	row = DDR_GET_VAL(val, DDR_APIN, DDR_APIN_SHIFT);
	अगर (row > max_row)
		fatal("DDR wrong APIN configuration\n");
	row = max_row - row;

	/* get collomn size and banks */
	val = SDRAM0_READ(DDR0_43);

	col = DDR_GET_VAL(val, DDR_COL_SZ, DDR_COL_SZ_SHIFT);
	अगर (col > max_col)
		fatal("DDR wrong COL configuration\n");
	col = max_col - col;

	अगर (DDR_GET_VAL(val, DDR_BANK8, DDR_BANK8_SHIFT))
		bank = 8; /* 8 banks */
	अन्यथा
		bank = 4; /* 4 banks */

	memsize = cs * (1 << (col+row)) * bank * dpath;
	memsize = chip_11_errata(memsize);
	dt_fixup_memory(0, memsize);
पूर्ण

#घोषणा SPRN_DBCR0_40X 0x3F2
#घोषणा SPRN_DBCR0_44X 0x134
#घोषणा DBCR0_RST_SYSTEM 0x30000000

व्योम ibm44x_dbcr_reset(व्योम)
अणु
	अचिन्हित दीर्घ पंचांगp;

	यंत्र अस्थिर (
		"mfspr	%0,%1\n"
		"oris	%0,%0,%2@h\n"
		"mtspr	%1,%0"
		: "=&r"(पंचांगp) : "i"(SPRN_DBCR0_44X), "i"(DBCR0_RST_SYSTEM)
		);

पूर्ण

व्योम ibm40x_dbcr_reset(व्योम)
अणु
	अचिन्हित दीर्घ पंचांगp;

	यंत्र अस्थिर (
		"mfspr	%0,%1\n"
		"oris	%0,%0,%2@h\n"
		"mtspr	%1,%0"
		: "=&r"(पंचांगp) : "i"(SPRN_DBCR0_40X), "i"(DBCR0_RST_SYSTEM)
		);
पूर्ण

#घोषणा EMAC_RESET 0x20000000
व्योम ibm4xx_quiesce_eth(u32 *emac0, u32 *emac1)
अणु
	/* Quiesce the MAL and EMAC(s) since PIBS/OpenBIOS करोn't
	 * करो this क्रम us
	 */
	अगर (emac0)
		*emac0 = EMAC_RESET;
	अगर (emac1)
		*emac1 = EMAC_RESET;

	mtdcr(DCRN_MAL0_CFG, MAL_RESET);
	जबतक (mfdcr(DCRN_MAL0_CFG) & MAL_RESET)
		; /* loop until reset takes effect */
पूर्ण

/* Read 4xx EBC bus bridge रेजिस्टरs to get mappings of the peripheral
 * banks पूर्णांकo the OPB address space */
व्योम ibm4xx_fixup_ebc_ranges(स्थिर अक्षर *ebc)
अणु
	व्योम *devp;
	u32 bxcr;
	u32 ranges[EBC_NUM_BANKS*4];
	u32 *p = ranges;
	पूर्णांक i;

	क्रम (i = 0; i < EBC_NUM_BANKS; i++) अणु
		mtdcr(DCRN_EBC0_CFGADDR, EBC_BXCR(i));
		bxcr = mfdcr(DCRN_EBC0_CFGDATA);

		अगर ((bxcr & EBC_BXCR_BU) != EBC_BXCR_BU_OFF) अणु
			*p++ = i;
			*p++ = 0;
			*p++ = bxcr & EBC_BXCR_BAS;
			*p++ = EBC_BXCR_BANK_SIZE(bxcr);
		पूर्ण
	पूर्ण

	devp = finddevice(ebc);
	अगर (! devp)
		fatal("Couldn't locate EBC node %s\n\r", ebc);

	setprop(devp, "ranges", ranges, (p - ranges) * माप(u32));
पूर्ण

/* Calculate 440GP घड़ीs */
व्योम ibm440gp_fixup_घड़ीs(अचिन्हित पूर्णांक sys_clk, अचिन्हित पूर्णांक ser_clk)
अणु
	u32 sys0 = mfdcr(DCRN_CPC0_SYS0);
	u32 cr0 = mfdcr(DCRN_CPC0_CR0);
	u32 cpu, plb, opb, ebc, tb, uart0, uart1, m;
	u32 opdv = CPC0_SYS0_OPDV(sys0);
	u32 epdv = CPC0_SYS0_EPDV(sys0);

	अगर (sys0 & CPC0_SYS0_BYPASS) अणु
		/* Bypass प्रणाली PLL */
		cpu = plb = sys_clk;
	पूर्ण अन्यथा अणु
		अगर (sys0 & CPC0_SYS0_EXTSL)
			/* PerClk */
			m = CPC0_SYS0_FWDVB(sys0) * opdv * epdv;
		अन्यथा
			/* CPU घड़ी */
			m = CPC0_SYS0_FBDV(sys0) * CPC0_SYS0_FWDVA(sys0);
		cpu = sys_clk * m / CPC0_SYS0_FWDVA(sys0);
		plb = sys_clk * m / CPC0_SYS0_FWDVB(sys0);
	पूर्ण

	opb = plb / opdv;
	ebc = opb / epdv;

	/* FIXME: Check अगर this is क्रम all 440GP, or just Ebony */
	अगर ((mfpvr() & 0xf0000fff) == 0x40000440)
		/* Rev. B 440GP, use बाह्यal प्रणाली घड़ी */
		tb = sys_clk;
	अन्यथा
		/* Rev. C 440GP, errata क्रमce us to use पूर्णांकernal घड़ी */
		tb = cpu;

	अगर (cr0 & CPC0_CR0_U0EC)
		/* External UART घड़ी */
		uart0 = ser_clk;
	अन्यथा
		/* Internal UART घड़ी */
		uart0 = plb / CPC0_CR0_UDIV(cr0);

	अगर (cr0 & CPC0_CR0_U1EC)
		/* External UART घड़ी */
		uart1 = ser_clk;
	अन्यथा
		/* Internal UART घड़ी */
		uart1 = plb / CPC0_CR0_UDIV(cr0);

	म_लिखो("PPC440GP: SysClk = %dMHz (%x)\n\r",
	       (sys_clk + 500000) / 1000000, sys_clk);

	dt_fixup_cpu_घड़ीs(cpu, tb, 0);

	dt_fixup_घड़ी("/plb", plb);
	dt_fixup_घड़ी("/plb/opb", opb);
	dt_fixup_घड़ी("/plb/opb/ebc", ebc);
	dt_fixup_घड़ी("/plb/opb/serial@40000200", uart0);
	dt_fixup_घड़ी("/plb/opb/serial@40000300", uart1);
पूर्ण

#घोषणा SPRN_CCR1 0x378

अटल अंतरभूत u32 __fix_zero(u32 v, u32 def)
अणु
	वापस v ? v : def;
पूर्ण

अटल अचिन्हित पूर्णांक __ibm440eplike_fixup_घड़ीs(अचिन्हित पूर्णांक sys_clk,
						अचिन्हित पूर्णांक पंचांगr_clk,
						पूर्णांक per_clk_from_opb)
अणु
	/* PLL config */
	u32 pllc  = CPR0_READ(DCRN_CPR0_PLLC);
	u32 plld  = CPR0_READ(DCRN_CPR0_PLLD);

	/* Dividers */
	u32 fbdv   = __fix_zero((plld >> 24) & 0x1f, 32);
	u32 fwdva  = __fix_zero((plld >> 16) & 0xf, 16);
	u32 fwdvb  = __fix_zero((plld >> 8) & 7, 8);
	u32 lfbdv  = __fix_zero(plld & 0x3f, 64);
	u32 pradv0 = __fix_zero((CPR0_READ(DCRN_CPR0_PRIMAD) >> 24) & 7, 8);
	u32 prbdv0 = __fix_zero((CPR0_READ(DCRN_CPR0_PRIMBD) >> 24) & 7, 8);
	u32 opbdv0 = __fix_zero((CPR0_READ(DCRN_CPR0_OPBD) >> 24) & 3, 4);
	u32 perdv0 = __fix_zero((CPR0_READ(DCRN_CPR0_PERD) >> 24) & 3, 4);

	/* Input घड़ीs क्रम primary भागiders */
	u32 clk_a, clk_b;

	/* Resulting घड़ीs */
	u32 cpu, plb, opb, ebc, vco;

	/* Timebase */
	u32 ccr1, tb = पंचांगr_clk;

	अगर (pllc & 0x40000000) अणु
		u32 m;

		/* Feedback path */
		चयन ((pllc >> 24) & 7) अणु
		हाल 0:
			/* PLLOUTx */
			m = ((pllc & 0x20000000) ? fwdvb : fwdva) * lfbdv;
			अवरोध;
		हाल 1:
			/* CPU */
			m = fwdva * pradv0;
			अवरोध;
		हाल 5:
			/* PERClk */
			m = fwdvb * prbdv0 * opbdv0 * perdv0;
			अवरोध;
		शेष:
			म_लिखो("WARNING ! Invalid PLL feedback source !\n");
			जाओ bypass;
		पूर्ण
		m *= fbdv;
		vco = sys_clk * m;
		clk_a = vco / fwdva;
		clk_b = vco / fwdvb;
	पूर्ण अन्यथा अणु
bypass:
		/* Bypass प्रणाली PLL */
		vco = 0;
		clk_a = clk_b = sys_clk;
	पूर्ण

	cpu = clk_a / pradv0;
	plb = clk_b / prbdv0;
	opb = plb / opbdv0;
	ebc = (per_clk_from_opb ? opb : plb) / perdv0;

	/* Figure out समयbase.  Either CPU or शेष TmrClk */
	ccr1 = mfspr(SPRN_CCR1);

	/* If passed a 0 पंचांगr_clk, क्रमce CPU घड़ी */
	अगर (tb == 0) अणु
		ccr1 &= ~0x80u;
		mtspr(SPRN_CCR1, ccr1);
	पूर्ण
	अगर ((ccr1 & 0x0080) == 0)
		tb = cpu;

	dt_fixup_cpu_घड़ीs(cpu, tb, 0);
	dt_fixup_घड़ी("/plb", plb);
	dt_fixup_घड़ी("/plb/opb", opb);
	dt_fixup_घड़ी("/plb/opb/ebc", ebc);

	वापस plb;
पूर्ण

अटल व्योम eplike_fixup_uart_clk(पूर्णांक index, स्थिर अक्षर *path,
				  अचिन्हित पूर्णांक ser_clk,
				  अचिन्हित पूर्णांक plb_clk)
अणु
	अचिन्हित पूर्णांक sdr;
	अचिन्हित पूर्णांक घड़ी;

	चयन (index) अणु
	हाल 0:
		sdr = SDR0_READ(DCRN_SDR0_UART0);
		अवरोध;
	हाल 1:
		sdr = SDR0_READ(DCRN_SDR0_UART1);
		अवरोध;
	हाल 2:
		sdr = SDR0_READ(DCRN_SDR0_UART2);
		अवरोध;
	हाल 3:
		sdr = SDR0_READ(DCRN_SDR0_UART3);
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	अगर (sdr & 0x00800000u)
		घड़ी = ser_clk;
	अन्यथा
		घड़ी = plb_clk / __fix_zero(sdr & 0xff, 256);

	dt_fixup_घड़ी(path, घड़ी);
पूर्ण

व्योम ibm440ep_fixup_घड़ीs(अचिन्हित पूर्णांक sys_clk,
			   अचिन्हित पूर्णांक ser_clk,
			   अचिन्हित पूर्णांक पंचांगr_clk)
अणु
	अचिन्हित पूर्णांक plb_clk = __ibm440eplike_fixup_घड़ीs(sys_clk, पंचांगr_clk, 0);

	/* serial घड़ीs need fixup based on पूर्णांक/ext */
	eplike_fixup_uart_clk(0, "/plb/opb/serial@ef600300", ser_clk, plb_clk);
	eplike_fixup_uart_clk(1, "/plb/opb/serial@ef600400", ser_clk, plb_clk);
	eplike_fixup_uart_clk(2, "/plb/opb/serial@ef600500", ser_clk, plb_clk);
	eplike_fixup_uart_clk(3, "/plb/opb/serial@ef600600", ser_clk, plb_clk);
पूर्ण

व्योम ibm440gx_fixup_घड़ीs(अचिन्हित पूर्णांक sys_clk,
			   अचिन्हित पूर्णांक ser_clk,
			   अचिन्हित पूर्णांक पंचांगr_clk)
अणु
	अचिन्हित पूर्णांक plb_clk = __ibm440eplike_fixup_घड़ीs(sys_clk, पंचांगr_clk, 1);

	/* serial घड़ीs need fixup based on पूर्णांक/ext */
	eplike_fixup_uart_clk(0, "/plb/opb/serial@40000200", ser_clk, plb_clk);
	eplike_fixup_uart_clk(1, "/plb/opb/serial@40000300", ser_clk, plb_clk);
पूर्ण

व्योम ibm440spe_fixup_घड़ीs(अचिन्हित पूर्णांक sys_clk,
			    अचिन्हित पूर्णांक ser_clk,
			    अचिन्हित पूर्णांक पंचांगr_clk)
अणु
	अचिन्हित पूर्णांक plb_clk = __ibm440eplike_fixup_घड़ीs(sys_clk, पंचांगr_clk, 1);

	/* serial घड़ीs need fixup based on पूर्णांक/ext */
	eplike_fixup_uart_clk(0, "/plb/opb/serial@f0000200", ser_clk, plb_clk);
	eplike_fixup_uart_clk(1, "/plb/opb/serial@f0000300", ser_clk, plb_clk);
	eplike_fixup_uart_clk(2, "/plb/opb/serial@f0000600", ser_clk, plb_clk);
पूर्ण

व्योम ibm405gp_fixup_घड़ीs(अचिन्हित पूर्णांक sys_clk, अचिन्हित पूर्णांक ser_clk)
अणु
	u32 pllmr = mfdcr(DCRN_CPC0_PLLMR);
	u32 cpc0_cr0 = mfdcr(DCRN_405_CPC0_CR0);
	u32 cpc0_cr1 = mfdcr(DCRN_405_CPC0_CR1);
	u32 psr = mfdcr(DCRN_405_CPC0_PSR);
	u32 cpu, plb, opb, ebc, tb, uart0, uart1, m;
	u32 fwdv, fwdvb, fbdv, cbdv, opdv, epdv, ppdv, uभाग;

	fwdv = (8 - ((pllmr & 0xe0000000) >> 29));
	fbdv = (pllmr & 0x1e000000) >> 25;
	अगर (fbdv == 0)
		fbdv = 16;
	cbdv = ((pllmr & 0x00060000) >> 17) + 1; /* CPU:PLB */
	opdv = ((pllmr & 0x00018000) >> 15) + 1; /* PLB:OPB */
	ppdv = ((pllmr & 0x00006000) >> 13) + 1; /* PLB:PCI */
	epdv = ((pllmr & 0x00001800) >> 11) + 2; /* PLB:EBC */
	uभाग = ((cpc0_cr0 & 0x3e) >> 1) + 1;

	/* check क्रम 405GPr */
	अगर ((mfpvr() & 0xfffffff0) == (0x50910951 & 0xfffffff0)) अणु
		fwdvb = 8 - (pllmr & 0x00000007);
		अगर (!(psr & 0x00001000)) /* PCI async mode enable == 0 */
			अगर (psr & 0x00000020) /* New mode enable */
				m = fwdvb * 2 * ppdv;
			अन्यथा
				m = fwdvb * cbdv * ppdv;
		अन्यथा अगर (psr & 0x00000020) /* New mode enable */
			अगर (psr & 0x00000800) /* PerClk synch mode */
				m = fwdvb * 2 * epdv;
			अन्यथा
				m = fbdv * fwdv;
		अन्यथा अगर (epdv == fbdv)
			m = fbdv * cbdv * epdv;
		अन्यथा
			m = fbdv * fwdvb * cbdv;

		cpu = sys_clk * m / fwdv;
		plb = sys_clk * m / (fwdvb * cbdv);
	पूर्ण अन्यथा अणु
		m = fwdv * fbdv * cbdv;
		cpu = sys_clk * m / fwdv;
		plb = cpu / cbdv;
	पूर्ण
	opb = plb / opdv;
	ebc = plb / epdv;

	अगर (cpc0_cr0 & 0x80)
		/* uart0 uses the बाह्यal घड़ी */
		uart0 = ser_clk;
	अन्यथा
		uart0 = cpu / uभाग;

	अगर (cpc0_cr0 & 0x40)
		/* uart1 uses the बाह्यal घड़ी */
		uart1 = ser_clk;
	अन्यथा
		uart1 = cpu / uभाग;

	/* setup the समयbase घड़ी to tick at the cpu frequency */
	cpc0_cr1 = cpc0_cr1 & ~0x00800000;
	mtdcr(DCRN_405_CPC0_CR1, cpc0_cr1);
	tb = cpu;

	dt_fixup_cpu_घड़ीs(cpu, tb, 0);
	dt_fixup_घड़ी("/plb", plb);
	dt_fixup_घड़ी("/plb/opb", opb);
	dt_fixup_घड़ी("/plb/ebc", ebc);
	dt_fixup_घड़ी("/plb/opb/serial@ef600300", uart0);
	dt_fixup_घड़ी("/plb/opb/serial@ef600400", uart1);
पूर्ण


व्योम ibm405ep_fixup_घड़ीs(अचिन्हित पूर्णांक sys_clk)
अणु
	u32 pllmr0 = mfdcr(DCRN_CPC0_PLLMR0);
	u32 pllmr1 = mfdcr(DCRN_CPC0_PLLMR1);
	u32 cpc0_ucr = mfdcr(DCRN_CPC0_UCR);
	u32 cpu, plb, opb, ebc, uart0, uart1;
	u32 fwdva, fwdvb, fbdv, cbdv, opdv, epdv;
	u32 pllmr0_ccdv, tb, m;

	fwdva = 8 - ((pllmr1 & 0x00070000) >> 16);
	fwdvb = 8 - ((pllmr1 & 0x00007000) >> 12);
	fbdv = (pllmr1 & 0x00f00000) >> 20;
	अगर (fbdv == 0)
		fbdv = 16;

	cbdv = ((pllmr0 & 0x00030000) >> 16) + 1; /* CPU:PLB */
	epdv = ((pllmr0 & 0x00000300) >> 8) + 2;  /* PLB:EBC */
	opdv = ((pllmr0 & 0x00003000) >> 12) + 1; /* PLB:OPB */

	m = fbdv * fwdvb;

	pllmr0_ccdv = ((pllmr0 & 0x00300000) >> 20) + 1;
	अगर (pllmr1 & 0x80000000)
		cpu = sys_clk * m / (fwdva * pllmr0_ccdv);
	अन्यथा
		cpu = sys_clk / pllmr0_ccdv;

	plb = cpu / cbdv;
	opb = plb / opdv;
	ebc = plb / epdv;
	tb = cpu;
	uart0 = cpu / (cpc0_ucr & 0x0000007f);
	uart1 = cpu / ((cpc0_ucr & 0x00007f00) >> 8);

	dt_fixup_cpu_घड़ीs(cpu, tb, 0);
	dt_fixup_घड़ी("/plb", plb);
	dt_fixup_घड़ी("/plb/opb", opb);
	dt_fixup_घड़ी("/plb/ebc", ebc);
	dt_fixup_घड़ी("/plb/opb/serial@ef600300", uart0);
	dt_fixup_घड़ी("/plb/opb/serial@ef600400", uart1);
पूर्ण

अटल u8 ibm405ex_fwdv_multi_bits[] = अणु
	/* values क्रम:  1 - 16 */
	0x01, 0x02, 0x0e, 0x09, 0x04, 0x0b, 0x10, 0x0d, 0x0c, 0x05,
	0x06, 0x0f, 0x0a, 0x07, 0x08, 0x03
पूर्ण;

u32 ibm405ex_get_fwdva(अचिन्हित दीर्घ cpr_fwdv)
अणु
	u32 index;

	क्रम (index = 0; index < ARRAY_SIZE(ibm405ex_fwdv_multi_bits); index++)
		अगर (cpr_fwdv == (u32)ibm405ex_fwdv_multi_bits[index])
			वापस index + 1;

	वापस 0;
पूर्ण

अटल u8 ibm405ex_fbdv_multi_bits[] = अणु
	/* values क्रम:  1 - 100 */
	0x00, 0xff, 0x7e, 0xfd, 0x7a, 0xf5, 0x6a, 0xd5, 0x2a, 0xd4,
	0x29, 0xd3, 0x26, 0xcc, 0x19, 0xb3, 0x67, 0xce, 0x1d, 0xbb,
	0x77, 0xee, 0x5d, 0xba, 0x74, 0xe9, 0x52, 0xa5, 0x4b, 0x96,
	0x2c, 0xd8, 0x31, 0xe3, 0x46, 0x8d, 0x1b, 0xb7, 0x6f, 0xde,
	0x3d, 0xfb, 0x76, 0xed, 0x5a, 0xb5, 0x6b, 0xd6, 0x2d, 0xdb,
	0x36, 0xec, 0x59, 0xb2, 0x64, 0xc9, 0x12, 0xa4, 0x48, 0x91,
	0x23, 0xc7, 0x0e, 0x9c, 0x38, 0xf0, 0x61, 0xc2, 0x05, 0x8b,
	0x17, 0xaf, 0x5f, 0xbe, 0x7c, 0xf9, 0x72, 0xe5, 0x4a, 0x95,
	0x2b, 0xd7, 0x2e, 0xdc, 0x39, 0xf3, 0x66, 0xcd, 0x1a, 0xb4,
	0x68, 0xd1, 0x22, 0xc4, 0x09, 0x93, 0x27, 0xcf, 0x1e, 0xbc,
	/* values क्रम:  101 - 200 */
	0x78, 0xf1, 0x62, 0xc5, 0x0a, 0x94, 0x28, 0xd0, 0x21, 0xc3,
	0x06, 0x8c, 0x18, 0xb0, 0x60, 0xc1, 0x02, 0x84, 0x08, 0x90,
	0x20, 0xc0, 0x01, 0x83, 0x07, 0x8f, 0x1f, 0xbf, 0x7f, 0xfe,
	0x7d, 0xfa, 0x75, 0xea, 0x55, 0xaa, 0x54, 0xa9, 0x53, 0xa6,
	0x4c, 0x99, 0x33, 0xe7, 0x4e, 0x9d, 0x3b, 0xf7, 0x6e, 0xdd,
	0x3a, 0xf4, 0x69, 0xd2, 0x25, 0xcb, 0x16, 0xac, 0x58, 0xb1,
	0x63, 0xc6, 0x0d, 0x9b, 0x37, 0xef, 0x5e, 0xbd, 0x7b, 0xf6,
	0x6d, 0xda, 0x35, 0xeb, 0x56, 0xad, 0x5b, 0xb6, 0x6c, 0xd9,
	0x32, 0xe4, 0x49, 0x92, 0x24, 0xc8, 0x11, 0xa3, 0x47, 0x8e,
	0x1c, 0xb8, 0x70, 0xe1, 0x42, 0x85, 0x0b, 0x97, 0x2f, 0xdf,
	/* values क्रम:  201 - 255 */
	0x3e, 0xfc, 0x79, 0xf2, 0x65, 0xca, 0x15, 0xab, 0x57, 0xae,
	0x5c, 0xb9, 0x73, 0xe6, 0x4d, 0x9a, 0x34, 0xe8, 0x51, 0xa2,
	0x44, 0x89, 0x13, 0xa7, 0x4f, 0x9e, 0x3c, 0xf8, 0x71, 0xe2,
	0x45, 0x8a, 0x14, 0xa8, 0x50, 0xa1, 0x43, 0x86, 0x0c, 0x98,
	0x30, 0xe0, 0x41, 0x82, 0x04, 0x88, 0x10, 0xa0, 0x40, 0x81,
	0x03, 0x87, 0x0f, 0x9f, 0x3f  /* END */
पूर्ण;

u32 ibm405ex_get_fbdv(अचिन्हित दीर्घ cpr_fbdv)
अणु
	u32 index;

	क्रम (index = 0; index < ARRAY_SIZE(ibm405ex_fbdv_multi_bits); index++)
		अगर (cpr_fbdv == (u32)ibm405ex_fbdv_multi_bits[index])
			वापस index + 1;

	वापस 0;
पूर्ण

व्योम ibm405ex_fixup_घड़ीs(अचिन्हित पूर्णांक sys_clk, अचिन्हित पूर्णांक uart_clk)
अणु
	/* PLL config */
	u32 pllc  = CPR0_READ(DCRN_CPR0_PLLC);
	u32 plld  = CPR0_READ(DCRN_CPR0_PLLD);
	u32 cpud  = CPR0_READ(DCRN_CPR0_PRIMAD);
	u32 plbd  = CPR0_READ(DCRN_CPR0_PRIMBD);
	u32 opbd  = CPR0_READ(DCRN_CPR0_OPBD);
	u32 perd  = CPR0_READ(DCRN_CPR0_PERD);

	/* Dividers */
	u32 fbdv   = ibm405ex_get_fbdv(__fix_zero((plld >> 24) & 0xff, 1));

	u32 fwdva  = ibm405ex_get_fwdva(__fix_zero((plld >> 16) & 0x0f, 1));

	u32 cpudv0 = __fix_zero((cpud >> 24) & 7, 8);

	/* PLBDV0 is hardwared to 010. */
	u32 plbdv0 = 2;
	u32 plb2xdv0 = __fix_zero((plbd >> 16) & 7, 8);

	u32 opbdv0 = __fix_zero((opbd >> 24) & 3, 4);

	u32 perdv0 = __fix_zero((perd >> 24) & 3, 4);

	/* Resulting घड़ीs */
	u32 cpu, plb, opb, ebc, vco, tb, uart0, uart1;

	/* PLL's VCO is the source क्रम primary क्रमward ? */
	अगर (pllc & 0x40000000) अणु
		u32 m;

		/* Feedback path */
		चयन ((pllc >> 24) & 7) अणु
		हाल 0:
			/* PLLOUTx */
			m = fbdv;
			अवरोध;
		हाल 1:
			/* CPU */
			m = fbdv * fwdva * cpudv0;
			अवरोध;
		हाल 5:
			/* PERClk */
			m = fbdv * fwdva * plb2xdv0 * plbdv0 * opbdv0 * perdv0;
			अवरोध;
		शेष:
			म_लिखो("WARNING ! Invalid PLL feedback source !\n");
			जाओ bypass;
		पूर्ण

		vco = (अचिन्हित पूर्णांक)(sys_clk * m);
	पूर्ण अन्यथा अणु
bypass:
		/* Bypass प्रणाली PLL */
		vco = 0;
	पूर्ण

	/* CPU = VCO / ( FWDVA x CPUDV0) */
	cpu = vco / (fwdva * cpudv0);
	/* PLB = VCO / ( FWDVA x PLB2XDV0 x PLBDV0) */
	plb = vco / (fwdva * plb2xdv0 * plbdv0);
	/* OPB = PLB / OPBDV0 */
	opb = plb / opbdv0;
	/* EBC = OPB / PERDV0 */
	ebc = opb / perdv0;

	tb = cpu;
	uart0 = uart1 = uart_clk;

	dt_fixup_cpu_घड़ीs(cpu, tb, 0);
	dt_fixup_घड़ी("/plb", plb);
	dt_fixup_घड़ी("/plb/opb", opb);
	dt_fixup_घड़ी("/plb/opb/ebc", ebc);
	dt_fixup_घड़ी("/plb/opb/serial@ef600200", uart0);
	dt_fixup_घड़ी("/plb/opb/serial@ef600300", uart1);
पूर्ण
