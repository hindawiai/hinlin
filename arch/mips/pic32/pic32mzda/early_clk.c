<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Joshua Henderson <joshua.henderson@microchip.com>
 * Copyright (C) 2015 Microchip Technology Inc.  All rights reserved.
 */
#समावेश <यंत्र/mach-pic32/pic32.h>

#समावेश "pic32mzda.h"

/* Oscillators, PLL & घड़ीs */
#घोषणा ICLK_MASK	0x00000080
#घोषणा PLLDIV_MASK	0x00000007
#घोषणा CUROSC_MASK	0x00000007
#घोषणा PLLMUL_MASK	0x0000007F
#घोषणा PB_MASK		0x00000007
#घोषणा FRC1		0
#घोषणा FRC2		7
#घोषणा SPLL		1
#घोषणा POSC		2
#घोषणा FRC_CLK		8000000

#घोषणा PIC32_POSC_FREQ	24000000

#घोषणा OSCCON		0x0000
#घोषणा SPLLCON		0x0020
#घोषणा PB1DIV		0x0140

u32 pic32_get_sysclk(व्योम)
अणु
	u32 osc_freq = 0;
	u32 pllclk;
	u32 frcभागn;
	u32 osccon;
	u32 spllcon;
	पूर्णांक curr_osc;

	u32 plliclk;
	u32 plliभाग;
	u32 plloभाग;
	u32 pllmult;
	u32 frcभाग;

	व्योम __iomem *osc_base = ioremap(PIC32_BASE_OSC, 0x200);

	osccon = __raw_पढ़ोl(osc_base + OSCCON);
	spllcon = __raw_पढ़ोl(osc_base + SPLLCON);

	plliclk = (spllcon & ICLK_MASK);
	plliभाग = ((spllcon >> 8) & PLLDIV_MASK) + 1;
	plloभाग = ((spllcon >> 24) & PLLDIV_MASK);
	pllmult = ((spllcon >> 16) & PLLMUL_MASK) + 1;
	frcभाग = ((osccon >> 24) & PLLDIV_MASK);

	pllclk = plliclk ? FRC_CLK : PIC32_POSC_FREQ;
	frcभागn = ((1 << frcभाग) + 1) + (128 * (frcभाग == 7));

	अगर (plloभाग < 2)
		plloभाग = 2;
	अन्यथा अगर (plloभाग < 5)
		plloभाग = (1 << plloभाग);
	अन्यथा
		plloभाग = 32;

	curr_osc = (पूर्णांक)((osccon >> 12) & CUROSC_MASK);

	चयन (curr_osc) अणु
	हाल FRC1:
	हाल FRC2:
		osc_freq = FRC_CLK / frcभागn;
		अवरोध;
	हाल SPLL:
		osc_freq = ((pllclk / plliभाग) * pllmult) / plloभाग;
		अवरोध;
	हाल POSC:
		osc_freq = PIC32_POSC_FREQ;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	iounmap(osc_base);

	वापस osc_freq;
पूर्ण

u32 pic32_get_pbclk(पूर्णांक bus)
अणु
	u32 clk_freq;
	व्योम __iomem *osc_base = ioremap(PIC32_BASE_OSC, 0x200);
	u32 pbxभाग = PB1DIV + ((bus - 1) * 0x10);
	u32 pbभाग = (__raw_पढ़ोl(osc_base + pbxभाग) & PB_MASK) + 1;

	iounmap(osc_base);

	clk_freq = pic32_get_sysclk();

	वापस clk_freq / pbभाग;
पूर्ण
