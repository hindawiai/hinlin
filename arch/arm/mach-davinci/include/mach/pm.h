<शैली गुरु>
/*
 * TI DaVinci platक्रमm support क्रम घातer management.
 *
 * Copyright (C) 2009 Texas Instruments, Inc. https://www.ti.com/
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */
#अगर_अघोषित _MACH_DAVINCI_PM_H
#घोषणा _MACH_DAVINCI_PM_H

/*
 * Caution: Assembly code in sleep.S makes assumtion on the order
 * of the members of this काष्ठाure.
 */
काष्ठा davinci_pm_config अणु
	व्योम __iomem *ddr2_ctlr_base;
	व्योम __iomem *ddrpsc_reg_base;
	पूर्णांक ddrpsc_num;
	व्योम __iomem *ddrpll_reg_base;
	व्योम __iomem *deepsleep_reg;
	व्योम __iomem *cpupll_reg_base;
	/*
	 * Note on SLEEPCOUNT:
	 * The SLEEPCOUNT feature is मुख्यly पूर्णांकended क्रम हालs in which
	 * the पूर्णांकernal oscillator is used. The पूर्णांकernal oscillator is
	 * fully disabled in deep sleep mode.  When you exist deep sleep
	 * mode, the oscillator will be turned on and will generate very
	 * small oscillations which will not be detected by the deep sleep
	 * counter.  Eventually those oscillations will grow to an amplitude
	 * large enough to start incrementing the deep sleep counter.
	 * In this हाल recommendation from hardware engineers is that the
	 * SLEEPCOUNT be set to 4096.  This means that 4096 valid घड़ी cycles
	 * must be detected beक्रमe the घड़ी is passed to the rest of the
	 * प्रणाली.
	 * In the हाल that the पूर्णांकernal oscillator is not used and the
	 * घड़ी is generated बाह्यally, the SLEEPCOUNT value can be very
	 * small since the घड़ी input is assumed to be stable beक्रमe SoC
	 * is taken out of deepsleep mode.  A value of 128 would be more than
	 * adequate.
	 */
	पूर्णांक sleepcount;
पूर्ण;

बाह्य अचिन्हित पूर्णांक davinci_cpu_suspend_sz;
बाह्य व्योम davinci_cpu_suspend(काष्ठा davinci_pm_config *);

#पूर्ण_अगर
