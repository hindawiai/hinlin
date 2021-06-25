<शैली गुरु>
/*
 * Sonics Silicon Backplane
 * Broadcom ChipCommon Power Management Unit driver
 *
 * Copyright 2009, Michael Buesch <m@bues.ch>
 * Copyright 2007, Broadcom Corporation
 *
 * Licensed under the GNU/GPL. See COPYING क्रम details.
 */

#समावेश "ssb_private.h"

#समावेश <linux/ssb/ssb.h>
#समावेश <linux/ssb/ssb_regs.h>
#समावेश <linux/ssb/ssb_driver_chipcommon.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#अगर_घोषित CONFIG_BCM47XX
#समावेश <linux/bcm47xx_nvram.h>
#पूर्ण_अगर

अटल u32 ssb_chipco_pll_पढ़ो(काष्ठा ssb_chipcommon *cc, u32 offset)
अणु
	chipco_ग_लिखो32(cc, SSB_CHIPCO_PLLCTL_ADDR, offset);
	वापस chipco_पढ़ो32(cc, SSB_CHIPCO_PLLCTL_DATA);
पूर्ण

अटल व्योम ssb_chipco_pll_ग_लिखो(काष्ठा ssb_chipcommon *cc,
				 u32 offset, u32 value)
अणु
	chipco_ग_लिखो32(cc, SSB_CHIPCO_PLLCTL_ADDR, offset);
	chipco_ग_लिखो32(cc, SSB_CHIPCO_PLLCTL_DATA, value);
पूर्ण

अटल व्योम ssb_chipco_regctl_maskset(काष्ठा ssb_chipcommon *cc,
				   u32 offset, u32 mask, u32 set)
अणु
	u32 value;

	chipco_पढ़ो32(cc, SSB_CHIPCO_REGCTL_ADDR);
	chipco_ग_लिखो32(cc, SSB_CHIPCO_REGCTL_ADDR, offset);
	chipco_पढ़ो32(cc, SSB_CHIPCO_REGCTL_ADDR);
	value = chipco_पढ़ो32(cc, SSB_CHIPCO_REGCTL_DATA);
	value &= mask;
	value |= set;
	chipco_ग_लिखो32(cc, SSB_CHIPCO_REGCTL_DATA, value);
	chipco_पढ़ो32(cc, SSB_CHIPCO_REGCTL_DATA);
पूर्ण

काष्ठा pmu0_plltab_entry अणु
	u16 freq;	/* Crystal frequency in kHz.*/
	u8 xf;		/* Crystal frequency value क्रम PMU control */
	u8 wb_पूर्णांक;
	u32 wb_frac;
पूर्ण;

अटल स्थिर काष्ठा pmu0_plltab_entry pmu0_plltab[] = अणु
	अणु .freq = 12000, .xf =  1, .wb_पूर्णांक = 73, .wb_frac = 349525, पूर्ण,
	अणु .freq = 13000, .xf =  2, .wb_पूर्णांक = 67, .wb_frac = 725937, पूर्ण,
	अणु .freq = 14400, .xf =  3, .wb_पूर्णांक = 61, .wb_frac = 116508, पूर्ण,
	अणु .freq = 15360, .xf =  4, .wb_पूर्णांक = 57, .wb_frac = 305834, पूर्ण,
	अणु .freq = 16200, .xf =  5, .wb_पूर्णांक = 54, .wb_frac = 336579, पूर्ण,
	अणु .freq = 16800, .xf =  6, .wb_पूर्णांक = 52, .wb_frac = 399457, पूर्ण,
	अणु .freq = 19200, .xf =  7, .wb_पूर्णांक = 45, .wb_frac = 873813, पूर्ण,
	अणु .freq = 19800, .xf =  8, .wb_पूर्णांक = 44, .wb_frac = 466033, पूर्ण,
	अणु .freq = 20000, .xf =  9, .wb_पूर्णांक = 44, .wb_frac = 0,      पूर्ण,
	अणु .freq = 25000, .xf = 10, .wb_पूर्णांक = 70, .wb_frac = 419430, पूर्ण,
	अणु .freq = 26000, .xf = 11, .wb_पूर्णांक = 67, .wb_frac = 725937, पूर्ण,
	अणु .freq = 30000, .xf = 12, .wb_पूर्णांक = 58, .wb_frac = 699050, पूर्ण,
	अणु .freq = 38400, .xf = 13, .wb_पूर्णांक = 45, .wb_frac = 873813, पूर्ण,
	अणु .freq = 40000, .xf = 14, .wb_पूर्णांक = 45, .wb_frac = 0,      पूर्ण,
पूर्ण;
#घोषणा SSB_PMU0_DEFAULT_XTALFREQ	20000

अटल स्थिर काष्ठा pmu0_plltab_entry * pmu0_plltab_find_entry(u32 crystalfreq)
अणु
	स्थिर काष्ठा pmu0_plltab_entry *e;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pmu0_plltab); i++) अणु
		e = &pmu0_plltab[i];
		अगर (e->freq == crystalfreq)
			वापस e;
	पूर्ण

	वापस शून्य;
पूर्ण

/* Tune the PLL to the crystal speed. crystalfreq is in kHz. */
अटल व्योम ssb_pmu0_pllinit_r0(काष्ठा ssb_chipcommon *cc,
				u32 crystalfreq)
अणु
	काष्ठा ssb_bus *bus = cc->dev->bus;
	स्थिर काष्ठा pmu0_plltab_entry *e = शून्य;
	u32 pmuctl, पंचांगp, pllctl;
	अचिन्हित पूर्णांक i;

	अगर (crystalfreq)
		e = pmu0_plltab_find_entry(crystalfreq);
	अगर (!e)
		e = pmu0_plltab_find_entry(SSB_PMU0_DEFAULT_XTALFREQ);
	BUG_ON(!e);
	crystalfreq = e->freq;
	cc->pmu.crystalfreq = e->freq;

	/* Check अगर the PLL alपढ़ोy is programmed to this frequency. */
	pmuctl = chipco_पढ़ो32(cc, SSB_CHIPCO_PMU_CTL);
	अगर (((pmuctl & SSB_CHIPCO_PMU_CTL_XTALFREQ) >> SSB_CHIPCO_PMU_CTL_XTALFREQ_SHIFT) == e->xf) अणु
		/* We're alपढ़ोy there... */
		वापस;
	पूर्ण

	dev_info(cc->dev->dev, "Programming PLL to %u.%03u MHz\n",
		 crystalfreq / 1000, crystalfreq % 1000);

	/* First turn the PLL off. */
	चयन (bus->chip_id) अणु
	हाल 0x4328:
		chipco_mask32(cc, SSB_CHIPCO_PMU_MINRES_MSK,
			      ~(1 << SSB_PMURES_4328_BB_PLL_PU));
		chipco_mask32(cc, SSB_CHIPCO_PMU_MAXRES_MSK,
			      ~(1 << SSB_PMURES_4328_BB_PLL_PU));
		अवरोध;
	हाल 0x5354:
		chipco_mask32(cc, SSB_CHIPCO_PMU_MINRES_MSK,
			      ~(1 << SSB_PMURES_5354_BB_PLL_PU));
		chipco_mask32(cc, SSB_CHIPCO_PMU_MAXRES_MSK,
			      ~(1 << SSB_PMURES_5354_BB_PLL_PU));
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण
	क्रम (i = 1500; i; i--) अणु
		पंचांगp = chipco_पढ़ो32(cc, SSB_CHIPCO_CLKCTLST);
		अगर (!(पंचांगp & SSB_CHIPCO_CLKCTLST_HAVEHT))
			अवरोध;
		udelay(10);
	पूर्ण
	पंचांगp = chipco_पढ़ो32(cc, SSB_CHIPCO_CLKCTLST);
	अगर (पंचांगp & SSB_CHIPCO_CLKCTLST_HAVEHT)
		dev_emerg(cc->dev->dev, "Failed to turn the PLL off!\n");

	/* Set PDIV in PLL control 0. */
	pllctl = ssb_chipco_pll_पढ़ो(cc, SSB_PMU0_PLLCTL0);
	अगर (crystalfreq >= SSB_PMU0_PLLCTL0_PDIV_FREQ)
		pllctl |= SSB_PMU0_PLLCTL0_PDIV_MSK;
	अन्यथा
		pllctl &= ~SSB_PMU0_PLLCTL0_PDIV_MSK;
	ssb_chipco_pll_ग_लिखो(cc, SSB_PMU0_PLLCTL0, pllctl);

	/* Set WILD in PLL control 1. */
	pllctl = ssb_chipco_pll_पढ़ो(cc, SSB_PMU0_PLLCTL1);
	pllctl &= ~SSB_PMU0_PLLCTL1_STOPMOD;
	pllctl &= ~(SSB_PMU0_PLLCTL1_WILD_IMSK | SSB_PMU0_PLLCTL1_WILD_FMSK);
	pllctl |= ((u32)e->wb_पूर्णांक << SSB_PMU0_PLLCTL1_WILD_IMSK_SHIFT) & SSB_PMU0_PLLCTL1_WILD_IMSK;
	pllctl |= ((u32)e->wb_frac << SSB_PMU0_PLLCTL1_WILD_FMSK_SHIFT) & SSB_PMU0_PLLCTL1_WILD_FMSK;
	अगर (e->wb_frac == 0)
		pllctl |= SSB_PMU0_PLLCTL1_STOPMOD;
	ssb_chipco_pll_ग_लिखो(cc, SSB_PMU0_PLLCTL1, pllctl);

	/* Set WILD in PLL control 2. */
	pllctl = ssb_chipco_pll_पढ़ो(cc, SSB_PMU0_PLLCTL2);
	pllctl &= ~SSB_PMU0_PLLCTL2_WILD_IMSKHI;
	pllctl |= (((u32)e->wb_पूर्णांक >> 4) << SSB_PMU0_PLLCTL2_WILD_IMSKHI_SHIFT) & SSB_PMU0_PLLCTL2_WILD_IMSKHI;
	ssb_chipco_pll_ग_लिखो(cc, SSB_PMU0_PLLCTL2, pllctl);

	/* Set the crystalfrequency and the भागisor. */
	pmuctl = chipco_पढ़ो32(cc, SSB_CHIPCO_PMU_CTL);
	pmuctl &= ~SSB_CHIPCO_PMU_CTL_ILP_DIV;
	pmuctl |= (((crystalfreq + 127) / 128 - 1) << SSB_CHIPCO_PMU_CTL_ILP_DIV_SHIFT)
			& SSB_CHIPCO_PMU_CTL_ILP_DIV;
	pmuctl &= ~SSB_CHIPCO_PMU_CTL_XTALFREQ;
	pmuctl |= ((u32)e->xf << SSB_CHIPCO_PMU_CTL_XTALFREQ_SHIFT) & SSB_CHIPCO_PMU_CTL_XTALFREQ;
	chipco_ग_लिखो32(cc, SSB_CHIPCO_PMU_CTL, pmuctl);
पूर्ण

काष्ठा pmu1_plltab_entry अणु
	u16 freq;	/* Crystal frequency in kHz.*/
	u8 xf;		/* Crystal frequency value क्रम PMU control */
	u8 nभाग_पूर्णांक;
	u32 nभाग_frac;
	u8 p1भाग;
	u8 p2भाग;
पूर्ण;

अटल स्थिर काष्ठा pmu1_plltab_entry pmu1_plltab[] = अणु
	अणु .freq = 12000, .xf =  1, .p1भाग = 3, .p2भाग = 22, .nभाग_पूर्णांक =  0x9, .nभाग_frac = 0xFFFFEF, पूर्ण,
	अणु .freq = 13000, .xf =  2, .p1भाग = 1, .p2भाग =  6, .nभाग_पूर्णांक =  0xb, .nभाग_frac = 0x483483, पूर्ण,
	अणु .freq = 14400, .xf =  3, .p1भाग = 1, .p2भाग = 10, .nभाग_पूर्णांक =  0xa, .nभाग_frac = 0x1C71C7, पूर्ण,
	अणु .freq = 15360, .xf =  4, .p1भाग = 1, .p2भाग =  5, .nभाग_पूर्णांक =  0xb, .nभाग_frac = 0x755555, पूर्ण,
	अणु .freq = 16200, .xf =  5, .p1भाग = 1, .p2भाग = 10, .nभाग_पूर्णांक =  0x5, .nभाग_frac = 0x6E9E06, पूर्ण,
	अणु .freq = 16800, .xf =  6, .p1भाग = 1, .p2भाग = 10, .nभाग_पूर्णांक =  0x5, .nभाग_frac = 0x3CF3CF, पूर्ण,
	अणु .freq = 19200, .xf =  7, .p1भाग = 1, .p2भाग =  9, .nभाग_पूर्णांक =  0x5, .nभाग_frac = 0x17B425, पूर्ण,
	अणु .freq = 19800, .xf =  8, .p1भाग = 1, .p2भाग = 11, .nभाग_पूर्णांक =  0x4, .nभाग_frac = 0xA57EB,  पूर्ण,
	अणु .freq = 20000, .xf =  9, .p1भाग = 1, .p2भाग = 11, .nभाग_पूर्णांक =  0x4, .nभाग_frac = 0,        पूर्ण,
	अणु .freq = 24000, .xf = 10, .p1भाग = 3, .p2भाग = 11, .nभाग_पूर्णांक =  0xa, .nभाग_frac = 0,        पूर्ण,
	अणु .freq = 25000, .xf = 11, .p1भाग = 5, .p2भाग = 16, .nभाग_पूर्णांक =  0xb, .nभाग_frac = 0,        पूर्ण,
	अणु .freq = 26000, .xf = 12, .p1भाग = 1, .p2भाग =  2, .nभाग_पूर्णांक = 0x10, .nभाग_frac = 0xEC4EC4, पूर्ण,
	अणु .freq = 30000, .xf = 13, .p1भाग = 3, .p2भाग =  8, .nभाग_पूर्णांक =  0xb, .nभाग_frac = 0,        पूर्ण,
	अणु .freq = 38400, .xf = 14, .p1भाग = 1, .p2भाग =  5, .nभाग_पूर्णांक =  0x4, .nभाग_frac = 0x955555, पूर्ण,
	अणु .freq = 40000, .xf = 15, .p1भाग = 1, .p2भाग =  2, .nभाग_पूर्णांक =  0xb, .nभाग_frac = 0,        पूर्ण,
पूर्ण;

#घोषणा SSB_PMU1_DEFAULT_XTALFREQ	15360

अटल स्थिर काष्ठा pmu1_plltab_entry * pmu1_plltab_find_entry(u32 crystalfreq)
अणु
	स्थिर काष्ठा pmu1_plltab_entry *e;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pmu1_plltab); i++) अणु
		e = &pmu1_plltab[i];
		अगर (e->freq == crystalfreq)
			वापस e;
	पूर्ण

	वापस शून्य;
पूर्ण

/* Tune the PLL to the crystal speed. crystalfreq is in kHz. */
अटल व्योम ssb_pmu1_pllinit_r0(काष्ठा ssb_chipcommon *cc,
				u32 crystalfreq)
अणु
	काष्ठा ssb_bus *bus = cc->dev->bus;
	स्थिर काष्ठा pmu1_plltab_entry *e = शून्य;
	u32 buffer_strength = 0;
	u32 पंचांगp, pllctl, pmuctl;
	अचिन्हित पूर्णांक i;

	अगर (bus->chip_id == 0x4312) अणु
		/* We करो not touch the BCM4312 PLL and assume
		 * the शेष crystal settings work out-of-the-box. */
		cc->pmu.crystalfreq = 20000;
		वापस;
	पूर्ण

	अगर (crystalfreq)
		e = pmu1_plltab_find_entry(crystalfreq);
	अगर (!e)
		e = pmu1_plltab_find_entry(SSB_PMU1_DEFAULT_XTALFREQ);
	BUG_ON(!e);
	crystalfreq = e->freq;
	cc->pmu.crystalfreq = e->freq;

	/* Check अगर the PLL alपढ़ोy is programmed to this frequency. */
	pmuctl = chipco_पढ़ो32(cc, SSB_CHIPCO_PMU_CTL);
	अगर (((pmuctl & SSB_CHIPCO_PMU_CTL_XTALFREQ) >> SSB_CHIPCO_PMU_CTL_XTALFREQ_SHIFT) == e->xf) अणु
		/* We're alपढ़ोy there... */
		वापस;
	पूर्ण

	dev_info(cc->dev->dev, "Programming PLL to %u.%03u MHz\n",
		 crystalfreq / 1000, crystalfreq % 1000);

	/* First turn the PLL off. */
	चयन (bus->chip_id) अणु
	हाल 0x4325:
		chipco_mask32(cc, SSB_CHIPCO_PMU_MINRES_MSK,
			      ~((1 << SSB_PMURES_4325_BBPLL_PWRSW_PU) |
				(1 << SSB_PMURES_4325_HT_AVAIL)));
		chipco_mask32(cc, SSB_CHIPCO_PMU_MAXRES_MSK,
			      ~((1 << SSB_PMURES_4325_BBPLL_PWRSW_PU) |
				(1 << SSB_PMURES_4325_HT_AVAIL)));
		/* Adjust the BBPLL to 2 on all channels later. */
		buffer_strength = 0x222222;
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण
	क्रम (i = 1500; i; i--) अणु
		पंचांगp = chipco_पढ़ो32(cc, SSB_CHIPCO_CLKCTLST);
		अगर (!(पंचांगp & SSB_CHIPCO_CLKCTLST_HAVEHT))
			अवरोध;
		udelay(10);
	पूर्ण
	पंचांगp = chipco_पढ़ो32(cc, SSB_CHIPCO_CLKCTLST);
	अगर (पंचांगp & SSB_CHIPCO_CLKCTLST_HAVEHT)
		dev_emerg(cc->dev->dev, "Failed to turn the PLL off!\n");

	/* Set p1भाग and p2भाग. */
	pllctl = ssb_chipco_pll_पढ़ो(cc, SSB_PMU1_PLLCTL0);
	pllctl &= ~(SSB_PMU1_PLLCTL0_P1DIV | SSB_PMU1_PLLCTL0_P2DIV);
	pllctl |= ((u32)e->p1भाग << SSB_PMU1_PLLCTL0_P1DIV_SHIFT) & SSB_PMU1_PLLCTL0_P1DIV;
	pllctl |= ((u32)e->p2भाग << SSB_PMU1_PLLCTL0_P2DIV_SHIFT) & SSB_PMU1_PLLCTL0_P2DIV;
	ssb_chipco_pll_ग_लिखो(cc, SSB_PMU1_PLLCTL0, pllctl);

	/* Set nभाग पूर्णांक and nभाग mode */
	pllctl = ssb_chipco_pll_पढ़ो(cc, SSB_PMU1_PLLCTL2);
	pllctl &= ~(SSB_PMU1_PLLCTL2_NDIVINT | SSB_PMU1_PLLCTL2_NDIVMODE);
	pllctl |= ((u32)e->nभाग_पूर्णांक << SSB_PMU1_PLLCTL2_NDIVINT_SHIFT) & SSB_PMU1_PLLCTL2_NDIVINT;
	pllctl |= (1 << SSB_PMU1_PLLCTL2_NDIVMODE_SHIFT) & SSB_PMU1_PLLCTL2_NDIVMODE;
	ssb_chipco_pll_ग_लिखो(cc, SSB_PMU1_PLLCTL2, pllctl);

	/* Set nभाग frac */
	pllctl = ssb_chipco_pll_पढ़ो(cc, SSB_PMU1_PLLCTL3);
	pllctl &= ~SSB_PMU1_PLLCTL3_NDIVFRAC;
	pllctl |= ((u32)e->nभाग_frac << SSB_PMU1_PLLCTL3_NDIVFRAC_SHIFT) & SSB_PMU1_PLLCTL3_NDIVFRAC;
	ssb_chipco_pll_ग_लिखो(cc, SSB_PMU1_PLLCTL3, pllctl);

	/* Change the drive strength, अगर required. */
	अगर (buffer_strength) अणु
		pllctl = ssb_chipco_pll_पढ़ो(cc, SSB_PMU1_PLLCTL5);
		pllctl &= ~SSB_PMU1_PLLCTL5_CLKDRV;
		pllctl |= (buffer_strength << SSB_PMU1_PLLCTL5_CLKDRV_SHIFT) & SSB_PMU1_PLLCTL5_CLKDRV;
		ssb_chipco_pll_ग_लिखो(cc, SSB_PMU1_PLLCTL5, pllctl);
	पूर्ण

	/* Tune the crystalfreq and the भागisor. */
	pmuctl = chipco_पढ़ो32(cc, SSB_CHIPCO_PMU_CTL);
	pmuctl &= ~(SSB_CHIPCO_PMU_CTL_ILP_DIV | SSB_CHIPCO_PMU_CTL_XTALFREQ);
	pmuctl |= ((((u32)e->freq + 127) / 128 - 1) << SSB_CHIPCO_PMU_CTL_ILP_DIV_SHIFT)
			& SSB_CHIPCO_PMU_CTL_ILP_DIV;
	pmuctl |= ((u32)e->xf << SSB_CHIPCO_PMU_CTL_XTALFREQ_SHIFT) & SSB_CHIPCO_PMU_CTL_XTALFREQ;
	chipco_ग_लिखो32(cc, SSB_CHIPCO_PMU_CTL, pmuctl);
पूर्ण

अटल व्योम ssb_pmu_pll_init(काष्ठा ssb_chipcommon *cc)
अणु
	काष्ठा ssb_bus *bus = cc->dev->bus;
	u32 crystalfreq = 0; /* in kHz. 0 = keep शेष freq. */

	अगर (bus->bustype == SSB_BUSTYPE_SSB) अणु
#अगर_घोषित CONFIG_BCM47XX
		अक्षर buf[20];
		अगर (bcm47xx_nvram_दो_पर्या("xtalfreq", buf, माप(buf)) >= 0)
			crystalfreq = simple_म_से_अदीर्घ(buf, शून्य, 0);
#पूर्ण_अगर
	पूर्ण

	चयन (bus->chip_id) अणु
	हाल 0x4312:
	हाल 0x4325:
		ssb_pmu1_pllinit_r0(cc, crystalfreq);
		अवरोध;
	हाल 0x4328:
		ssb_pmu0_pllinit_r0(cc, crystalfreq);
		अवरोध;
	हाल 0x5354:
		अगर (crystalfreq == 0)
			crystalfreq = 25000;
		ssb_pmu0_pllinit_r0(cc, crystalfreq);
		अवरोध;
	हाल 0x4322:
		अगर (cc->pmu.rev == 2) अणु
			chipco_ग_लिखो32(cc, SSB_CHIPCO_PLLCTL_ADDR, 0x0000000A);
			chipco_ग_लिखो32(cc, SSB_CHIPCO_PLLCTL_DATA, 0x380005C0);
		पूर्ण
		अवरोध;
	हाल 43222:
		अवरोध;
	शेष:
		dev_err(cc->dev->dev, "ERROR: PLL init unknown for device %04X\n",
			bus->chip_id);
	पूर्ण
पूर्ण

काष्ठा pmu_res_upकरोwn_tab_entry अणु
	u8 resource;	/* The resource number */
	u16 upकरोwn;	/* The upकरोwn value */
पूर्ण;

क्रमागत pmu_res_depend_tab_task अणु
	PMU_RES_DEP_SET = 1,
	PMU_RES_DEP_ADD,
	PMU_RES_DEP_REMOVE,
पूर्ण;

काष्ठा pmu_res_depend_tab_entry अणु
	u8 resource;	/* The resource number */
	u8 task;	/* SET | ADD | REMOVE */
	u32 depend;	/* The depend mask */
पूर्ण;

अटल स्थिर काष्ठा pmu_res_upकरोwn_tab_entry pmu_res_upकरोwn_tab_4328a0[] = अणु
	अणु .resource = SSB_PMURES_4328_EXT_SWITCHER_PWM,		.upकरोwn = 0x0101, पूर्ण,
	अणु .resource = SSB_PMURES_4328_BB_SWITCHER_PWM,		.upकरोwn = 0x1F01, पूर्ण,
	अणु .resource = SSB_PMURES_4328_BB_SWITCHER_BURST,	.upकरोwn = 0x010F, पूर्ण,
	अणु .resource = SSB_PMURES_4328_BB_EXT_SWITCHER_BURST,	.upकरोwn = 0x0101, पूर्ण,
	अणु .resource = SSB_PMURES_4328_ILP_REQUEST,		.upकरोwn = 0x0202, पूर्ण,
	अणु .resource = SSB_PMURES_4328_RADIO_SWITCHER_PWM,	.upकरोwn = 0x0F01, पूर्ण,
	अणु .resource = SSB_PMURES_4328_RADIO_SWITCHER_BURST,	.upकरोwn = 0x0F01, पूर्ण,
	अणु .resource = SSB_PMURES_4328_ROM_SWITCH,		.upकरोwn = 0x0101, पूर्ण,
	अणु .resource = SSB_PMURES_4328_PA_REF_LDO,		.upकरोwn = 0x0F01, पूर्ण,
	अणु .resource = SSB_PMURES_4328_RADIO_LDO,		.upकरोwn = 0x0F01, पूर्ण,
	अणु .resource = SSB_PMURES_4328_AFE_LDO,			.upकरोwn = 0x0F01, पूर्ण,
	अणु .resource = SSB_PMURES_4328_PLL_LDO,			.upकरोwn = 0x0F01, पूर्ण,
	अणु .resource = SSB_PMURES_4328_BG_FILTBYP,		.upकरोwn = 0x0101, पूर्ण,
	अणु .resource = SSB_PMURES_4328_TX_FILTBYP,		.upकरोwn = 0x0101, पूर्ण,
	अणु .resource = SSB_PMURES_4328_RX_FILTBYP,		.upकरोwn = 0x0101, पूर्ण,
	अणु .resource = SSB_PMURES_4328_XTAL_PU,			.upकरोwn = 0x0101, पूर्ण,
	अणु .resource = SSB_PMURES_4328_XTAL_EN,			.upकरोwn = 0xA001, पूर्ण,
	अणु .resource = SSB_PMURES_4328_BB_PLL_FILTBYP,		.upकरोwn = 0x0101, पूर्ण,
	अणु .resource = SSB_PMURES_4328_RF_PLL_FILTBYP,		.upकरोwn = 0x0101, पूर्ण,
	अणु .resource = SSB_PMURES_4328_BB_PLL_PU,		.upकरोwn = 0x0701, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pmu_res_depend_tab_entry pmu_res_depend_tab_4328a0[] = अणु
	अणु
		/* Adjust ILP Request to aव्योम क्रमcing EXT/BB पूर्णांकo burst mode. */
		.resource = SSB_PMURES_4328_ILP_REQUEST,
		.task = PMU_RES_DEP_SET,
		.depend = ((1 << SSB_PMURES_4328_EXT_SWITCHER_PWM) |
			   (1 << SSB_PMURES_4328_BB_SWITCHER_PWM)),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pmu_res_upकरोwn_tab_entry pmu_res_upकरोwn_tab_4325a0[] = अणु
	अणु .resource = SSB_PMURES_4325_XTAL_PU,			.upकरोwn = 0x1501, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pmu_res_depend_tab_entry pmu_res_depend_tab_4325a0[] = अणु
	अणु
		/* Adjust HT-Available dependencies. */
		.resource = SSB_PMURES_4325_HT_AVAIL,
		.task = PMU_RES_DEP_ADD,
		.depend = ((1 << SSB_PMURES_4325_RX_PWRSW_PU) |
			   (1 << SSB_PMURES_4325_TX_PWRSW_PU) |
			   (1 << SSB_PMURES_4325_LOGEN_PWRSW_PU) |
			   (1 << SSB_PMURES_4325_AFE_PWRSW_PU)),
	पूर्ण,
पूर्ण;

अटल व्योम ssb_pmu_resources_init(काष्ठा ssb_chipcommon *cc)
अणु
	काष्ठा ssb_bus *bus = cc->dev->bus;
	u32 min_msk = 0, max_msk = 0;
	अचिन्हित पूर्णांक i;
	स्थिर काष्ठा pmu_res_upकरोwn_tab_entry *upकरोwn_tab = शून्य;
	अचिन्हित पूर्णांक upकरोwn_tab_size = 0;
	स्थिर काष्ठा pmu_res_depend_tab_entry *depend_tab = शून्य;
	अचिन्हित पूर्णांक depend_tab_size = 0;

	चयन (bus->chip_id) अणु
	हाल 0x4312:
		 min_msk = 0xCBB;
		 अवरोध;
	हाल 0x4322:
	हाल 43222:
		/* We keep the शेष settings:
		 * min_msk = 0xCBB
		 * max_msk = 0x7FFFF
		 */
		अवरोध;
	हाल 0x4325:
		/* Power OTP करोwn later. */
		min_msk = (1 << SSB_PMURES_4325_CBUCK_BURST) |
			  (1 << SSB_PMURES_4325_LNLDO2_PU);
		अगर (chipco_पढ़ो32(cc, SSB_CHIPCO_CHIPSTAT) &
		    SSB_CHIPCO_CHST_4325_PMUTOP_2B)
			min_msk |= (1 << SSB_PMURES_4325_CLDO_CBUCK_BURST);
		/* The PLL may turn on, अगर it decides so. */
		max_msk = 0xFFFFF;
		upकरोwn_tab = pmu_res_upकरोwn_tab_4325a0;
		upकरोwn_tab_size = ARRAY_SIZE(pmu_res_upकरोwn_tab_4325a0);
		depend_tab = pmu_res_depend_tab_4325a0;
		depend_tab_size = ARRAY_SIZE(pmu_res_depend_tab_4325a0);
		अवरोध;
	हाल 0x4328:
		min_msk = (1 << SSB_PMURES_4328_EXT_SWITCHER_PWM) |
			  (1 << SSB_PMURES_4328_BB_SWITCHER_PWM) |
			  (1 << SSB_PMURES_4328_XTAL_EN);
		/* The PLL may turn on, अगर it decides so. */
		max_msk = 0xFFFFF;
		upकरोwn_tab = pmu_res_upकरोwn_tab_4328a0;
		upकरोwn_tab_size = ARRAY_SIZE(pmu_res_upकरोwn_tab_4328a0);
		depend_tab = pmu_res_depend_tab_4328a0;
		depend_tab_size = ARRAY_SIZE(pmu_res_depend_tab_4328a0);
		अवरोध;
	हाल 0x5354:
		/* The PLL may turn on, अगर it decides so. */
		max_msk = 0xFFFFF;
		अवरोध;
	शेष:
		dev_err(cc->dev->dev, "ERROR: PMU resource config unknown for device %04X\n",
			bus->chip_id);
	पूर्ण

	अगर (upकरोwn_tab) अणु
		क्रम (i = 0; i < upकरोwn_tab_size; i++) अणु
			chipco_ग_लिखो32(cc, SSB_CHIPCO_PMU_RES_TABSEL,
				       upकरोwn_tab[i].resource);
			chipco_ग_लिखो32(cc, SSB_CHIPCO_PMU_RES_UPDNTM,
				       upकरोwn_tab[i].upकरोwn);
		पूर्ण
	पूर्ण
	अगर (depend_tab) अणु
		क्रम (i = 0; i < depend_tab_size; i++) अणु
			chipco_ग_लिखो32(cc, SSB_CHIPCO_PMU_RES_TABSEL,
				       depend_tab[i].resource);
			चयन (depend_tab[i].task) अणु
			हाल PMU_RES_DEP_SET:
				chipco_ग_लिखो32(cc, SSB_CHIPCO_PMU_RES_DEPMSK,
					       depend_tab[i].depend);
				अवरोध;
			हाल PMU_RES_DEP_ADD:
				chipco_set32(cc, SSB_CHIPCO_PMU_RES_DEPMSK,
					     depend_tab[i].depend);
				अवरोध;
			हाल PMU_RES_DEP_REMOVE:
				chipco_mask32(cc, SSB_CHIPCO_PMU_RES_DEPMSK,
					      ~(depend_tab[i].depend));
				अवरोध;
			शेष:
				WARN_ON(1);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Set the resource masks. */
	अगर (min_msk)
		chipco_ग_लिखो32(cc, SSB_CHIPCO_PMU_MINRES_MSK, min_msk);
	अगर (max_msk)
		chipco_ग_लिखो32(cc, SSB_CHIPCO_PMU_MAXRES_MSK, max_msk);
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/SSB/PmuInit */
व्योम ssb_pmu_init(काष्ठा ssb_chipcommon *cc)
अणु
	u32 pmucap;

	अगर (!(cc->capabilities & SSB_CHIPCO_CAP_PMU))
		वापस;

	pmucap = chipco_पढ़ो32(cc, SSB_CHIPCO_PMU_CAP);
	cc->pmu.rev = (pmucap & SSB_CHIPCO_PMU_CAP_REVISION);

	dev_dbg(cc->dev->dev, "Found rev %u PMU (capabilities 0x%08X)\n",
		cc->pmu.rev, pmucap);

	अगर (cc->pmu.rev == 1)
		chipco_mask32(cc, SSB_CHIPCO_PMU_CTL,
			      ~SSB_CHIPCO_PMU_CTL_NOILPONW);
	अन्यथा
		chipco_set32(cc, SSB_CHIPCO_PMU_CTL,
			     SSB_CHIPCO_PMU_CTL_NOILPONW);
	ssb_pmu_pll_init(cc);
	ssb_pmu_resources_init(cc);
पूर्ण

व्योम ssb_pmu_set_lकरो_voltage(काष्ठा ssb_chipcommon *cc,
			     क्रमागत ssb_pmu_lकरो_volt_id id, u32 voltage)
अणु
	काष्ठा ssb_bus *bus = cc->dev->bus;
	u32 addr, shअगरt, mask;

	चयन (bus->chip_id) अणु
	हाल 0x4328:
	हाल 0x5354:
		चयन (id) अणु
		हाल LDO_VOLT1:
			addr = 2;
			shअगरt = 25;
			mask = 0xF;
			अवरोध;
		हाल LDO_VOLT2:
			addr = 3;
			shअगरt = 1;
			mask = 0xF;
			अवरोध;
		हाल LDO_VOLT3:
			addr = 3;
			shअगरt = 9;
			mask = 0xF;
			अवरोध;
		हाल LDO_PAREF:
			addr = 3;
			shअगरt = 17;
			mask = 0x3F;
			अवरोध;
		शेष:
			WARN_ON(1);
			वापस;
		पूर्ण
		अवरोध;
	हाल 0x4312:
		अगर (WARN_ON(id != LDO_PAREF))
			वापस;
		addr = 0;
		shअगरt = 21;
		mask = 0x3F;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	ssb_chipco_regctl_maskset(cc, addr, ~(mask << shअगरt),
				  (voltage & mask) << shअगरt);
पूर्ण

व्योम ssb_pmu_set_lकरो_paref(काष्ठा ssb_chipcommon *cc, bool on)
अणु
	काष्ठा ssb_bus *bus = cc->dev->bus;
	पूर्णांक lकरो;

	चयन (bus->chip_id) अणु
	हाल 0x4312:
		lकरो = SSB_PMURES_4312_PA_REF_LDO;
		अवरोध;
	हाल 0x4328:
		lकरो = SSB_PMURES_4328_PA_REF_LDO;
		अवरोध;
	हाल 0x5354:
		lकरो = SSB_PMURES_5354_PA_REF_LDO;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	अगर (on)
		chipco_set32(cc, SSB_CHIPCO_PMU_MINRES_MSK, 1 << lकरो);
	अन्यथा
		chipco_mask32(cc, SSB_CHIPCO_PMU_MINRES_MSK, ~(1 << lकरो));
	chipco_पढ़ो32(cc, SSB_CHIPCO_PMU_MINRES_MSK); //SPEC FIXME found via mmiotrace - dummy पढ़ो?
पूर्ण

EXPORT_SYMBOL(ssb_pmu_set_lकरो_voltage);
EXPORT_SYMBOL(ssb_pmu_set_lकरो_paref);

अटल u32 ssb_pmu_get_alp_घड़ी_clk0(काष्ठा ssb_chipcommon *cc)
अणु
	u32 crystalfreq;
	स्थिर काष्ठा pmu0_plltab_entry *e = शून्य;

	crystalfreq = (chipco_पढ़ो32(cc, SSB_CHIPCO_PMU_CTL) &
		       SSB_CHIPCO_PMU_CTL_XTALFREQ)  >> SSB_CHIPCO_PMU_CTL_XTALFREQ_SHIFT;
	e = pmu0_plltab_find_entry(crystalfreq);
	BUG_ON(!e);
	वापस e->freq * 1000;
पूर्ण

u32 ssb_pmu_get_alp_घड़ी(काष्ठा ssb_chipcommon *cc)
अणु
	काष्ठा ssb_bus *bus = cc->dev->bus;

	चयन (bus->chip_id) अणु
	हाल 0x5354:
		वापस ssb_pmu_get_alp_घड़ी_clk0(cc);
	शेष:
		dev_err(cc->dev->dev, "ERROR: PMU alp clock unknown for device %04X\n",
			bus->chip_id);
		वापस 0;
	पूर्ण
पूर्ण

u32 ssb_pmu_get_cpu_घड़ी(काष्ठा ssb_chipcommon *cc)
अणु
	काष्ठा ssb_bus *bus = cc->dev->bus;

	चयन (bus->chip_id) अणु
	हाल 0x5354:
		/* 5354 chip uses a non programmable PLL of frequency 240MHz */
		वापस 240000000;
	शेष:
		dev_err(cc->dev->dev, "ERROR: PMU cpu clock unknown for device %04X\n",
			bus->chip_id);
		वापस 0;
	पूर्ण
पूर्ण

u32 ssb_pmu_get_controlघड़ी(काष्ठा ssb_chipcommon *cc)
अणु
	काष्ठा ssb_bus *bus = cc->dev->bus;

	चयन (bus->chip_id) अणु
	हाल 0x5354:
		वापस 120000000;
	शेष:
		dev_err(cc->dev->dev, "ERROR: PMU controlclock unknown for device %04X\n",
			bus->chip_id);
		वापस 0;
	पूर्ण
पूर्ण

व्योम ssb_pmu_spuraव्योम_pllupdate(काष्ठा ssb_chipcommon *cc, पूर्णांक spuraव्योम)
अणु
	u32 pmu_ctl = 0;

	चयन (cc->dev->bus->chip_id) अणु
	हाल 0x4322:
		ssb_chipco_pll_ग_लिखो(cc, SSB_PMU1_PLLCTL0, 0x11100070);
		ssb_chipco_pll_ग_लिखो(cc, SSB_PMU1_PLLCTL1, 0x1014140a);
		ssb_chipco_pll_ग_लिखो(cc, SSB_PMU1_PLLCTL5, 0x88888854);
		अगर (spuraव्योम == 1)
			ssb_chipco_pll_ग_लिखो(cc, SSB_PMU1_PLLCTL2, 0x05201828);
		अन्यथा
			ssb_chipco_pll_ग_लिखो(cc, SSB_PMU1_PLLCTL2, 0x05001828);
		pmu_ctl = SSB_CHIPCO_PMU_CTL_PLL_UPD;
		अवरोध;
	हाल 43222:
		अगर (spuraव्योम == 1) अणु
			ssb_chipco_pll_ग_लिखो(cc, SSB_PMU1_PLLCTL0, 0x11500008);
			ssb_chipco_pll_ग_लिखो(cc, SSB_PMU1_PLLCTL1, 0x0C000C06);
			ssb_chipco_pll_ग_लिखो(cc, SSB_PMU1_PLLCTL2, 0x0F600a08);
			ssb_chipco_pll_ग_लिखो(cc, SSB_PMU1_PLLCTL3, 0x00000000);
			ssb_chipco_pll_ग_लिखो(cc, SSB_PMU1_PLLCTL4, 0x2001E920);
			ssb_chipco_pll_ग_लिखो(cc, SSB_PMU1_PLLCTL5, 0x88888815);
		पूर्ण अन्यथा अणु
			ssb_chipco_pll_ग_लिखो(cc, SSB_PMU1_PLLCTL0, 0x11100008);
			ssb_chipco_pll_ग_लिखो(cc, SSB_PMU1_PLLCTL1, 0x0c000c06);
			ssb_chipco_pll_ग_लिखो(cc, SSB_PMU1_PLLCTL2, 0x03000a08);
			ssb_chipco_pll_ग_लिखो(cc, SSB_PMU1_PLLCTL3, 0x00000000);
			ssb_chipco_pll_ग_लिखो(cc, SSB_PMU1_PLLCTL4, 0x200005c0);
			ssb_chipco_pll_ग_लिखो(cc, SSB_PMU1_PLLCTL5, 0x88888855);
		पूर्ण
		pmu_ctl = SSB_CHIPCO_PMU_CTL_PLL_UPD;
		अवरोध;
	शेष:
		dev_err(cc->dev->dev,
			"Unknown spuravoidance settings for chip 0x%04X, not changing PLL\n",
			cc->dev->bus->chip_id);
		वापस;
	पूर्ण

	chipco_set32(cc, SSB_CHIPCO_PMU_CTL, pmu_ctl);
पूर्ण
EXPORT_SYMBOL_GPL(ssb_pmu_spuraव्योम_pllupdate);
