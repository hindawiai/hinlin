<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * hp6x0 Power Management Routines
 *
 * Copyright (c) 2006 Andriy Skulysh <askulsyh@gmail.com>
 */
#समावेश <linux/init.h>
#समावेश <linux/suspend.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/समय.स>
#समावेश <linux/delay.h>
#समावेश <linux/gfp.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/hd64461.h>
#समावेश <यंत्र/bl_bit.h>
#समावेश <mach/hp6xx.h>
#समावेश <cpu/dac.h>
#समावेश <यंत्र/freq.h>
#समावेश <यंत्र/watchकरोg.h>

#घोषणा INTR_OFFSET	0x600

#घोषणा STBCR		0xffffff82
#घोषणा STBCR2		0xffffff88

#घोषणा STBCR_STBY	0x80
#घोषणा STBCR_MSTP2	0x04

#घोषणा MCR		0xffffff68
#घोषणा RTCNT		0xffffff70

#घोषणा MCR_RMODE	2
#घोषणा MCR_RFSH	4

बाह्य u8 wakeup_start;
बाह्य u8 wakeup_end;

अटल व्योम pm_enter(व्योम)
अणु
	u8 stbcr, csr;
	u16 frqcr, mcr;
	u32 vbr_new, vbr_old;

	set_bl_bit();

	/* set wdt */
	csr = sh_wdt_पढ़ो_csr();
	csr &= ~WTCSR_TME;
	csr |= WTCSR_CKS_4096;
	sh_wdt_ग_लिखो_csr(csr);
	csr = sh_wdt_पढ़ो_csr();
	sh_wdt_ग_लिखो_cnt(0);

	/* disable PLL1 */
	frqcr = __raw_पढ़ोw(FRQCR);
	frqcr &= ~(FRQCR_PLLEN | FRQCR_PSTBY);
	__raw_ग_लिखोw(frqcr, FRQCR);

	/* enable standby */
	stbcr = __raw_पढ़ोb(STBCR);
	__raw_ग_लिखोb(stbcr | STBCR_STBY | STBCR_MSTP2, STBCR);

	/* set self-refresh */
	mcr = __raw_पढ़ोw(MCR);
	__raw_ग_लिखोw(mcr & ~MCR_RFSH, MCR);

	/* set पूर्णांकerrupt handler */
	यंत्र अस्थिर("stc vbr, %0" : "=r" (vbr_old));
	vbr_new = get_zeroed_page(GFP_ATOMIC);
	udelay(50);
	स_नकल((व्योम*)(vbr_new + INTR_OFFSET),
	       &wakeup_start, &wakeup_end - &wakeup_start);
	यंत्र अस्थिर("ldc %0, vbr" : : "r" (vbr_new));

	__raw_ग_लिखोw(0, RTCNT);
	__raw_ग_लिखोw(mcr | MCR_RFSH | MCR_RMODE, MCR);

	cpu_sleep();

	यंत्र अस्थिर("ldc %0, vbr" : : "r" (vbr_old));

	मुक्त_page(vbr_new);

	/* enable PLL1 */
	frqcr = __raw_पढ़ोw(FRQCR);
	frqcr |= FRQCR_PSTBY;
	__raw_ग_लिखोw(frqcr, FRQCR);
	udelay(50);
	frqcr |= FRQCR_PLLEN;
	__raw_ग_लिखोw(frqcr, FRQCR);

	__raw_ग_लिखोb(stbcr, STBCR);

	clear_bl_bit();
पूर्ण

अटल पूर्णांक hp6x0_pm_enter(suspend_state_t state)
अणु
	u8 stbcr, stbcr2;
#अगर_घोषित CONFIG_HD64461_ENABLER
	u8 scr;
	u16 hd64461_stbcr;
#पूर्ण_अगर

#अगर_घोषित CONFIG_HD64461_ENABLER
	outb(0, HD64461_PCC1CSCIER);

	scr = inb(HD64461_PCC1SCR);
	scr |= HD64461_PCCSCR_VCC1;
	outb(scr, HD64461_PCC1SCR);

	hd64461_stbcr = inw(HD64461_STBCR);
	hd64461_stbcr |= HD64461_STBCR_SPC1ST;
	outw(hd64461_stbcr, HD64461_STBCR);
#पूर्ण_अगर

	__raw_ग_लिखोb(0x1f, DACR);

	stbcr = __raw_पढ़ोb(STBCR);
	__raw_ग_लिखोb(0x01, STBCR);

	stbcr2 = __raw_पढ़ोb(STBCR2);
	__raw_ग_लिखोb(0x7f , STBCR2);

	outw(0xf07f, HD64461_SCPUCR);

	pm_enter();

	outw(0, HD64461_SCPUCR);
	__raw_ग_लिखोb(stbcr, STBCR);
	__raw_ग_लिखोb(stbcr2, STBCR2);

#अगर_घोषित CONFIG_HD64461_ENABLER
	hd64461_stbcr = inw(HD64461_STBCR);
	hd64461_stbcr &= ~HD64461_STBCR_SPC1ST;
	outw(hd64461_stbcr, HD64461_STBCR);

	outb(0x4c, HD64461_PCC1CSCIER);
	outb(0x00, HD64461_PCC1CSCR);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops hp6x0_pm_ops = अणु
	.enter		= hp6x0_pm_enter,
	.valid		= suspend_valid_only_mem,
पूर्ण;

अटल पूर्णांक __init hp6x0_pm_init(व्योम)
अणु
	suspend_set_ops(&hp6x0_pm_ops);
	वापस 0;
पूर्ण

late_initcall(hp6x0_pm_init);
