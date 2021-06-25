<शैली गुरु>
/*
 * Timer/Counter Unit (TC) रेजिस्टरs.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#अगर_अघोषित __SOC_ATMEL_TCB_H
#घोषणा __SOC_ATMEL_TCB_H

#समावेश <linux/compiler.h>
#समावेश <linux/list.h>

/*
 * Many 32-bit Aपंचांगel SOCs include one or more TC blocks, each of which holds
 * three general-purpose 16-bit समयrs.  These समयrs share one रेजिस्टर bank.
 * Depending on the SOC, each समयr may have its own घड़ी and IRQ, or those
 * may be shared by the whole TC block.
 *
 * These TC blocks may have up to nine बाह्यal pins:  TCLK0..2 संकेतs क्रम
 * घड़ीs or घड़ी gates, and per-समयr TIOA and TIOB संकेतs used क्रम PWM
 * or triggering.  Those pins need to be set up क्रम use with the TC block,
 * अन्यथा they will be used as GPIOs or क्रम a dअगरferent controller.
 *
 * Although we expect each TC block to have a platक्रमm_device node, those
 * nodes are not what drivers bind to.  Instead, they ask क्रम a specअगरic
 * TC block, by number ... which is a common approach on प्रणालीs with many
 * समयrs.  Then they use clk_get() and platक्रमm_get_irq() to get घड़ी and
 * IRQ resources.
 */

काष्ठा clk;

/**
 * काष्ठा aपंचांगel_tcb_config - SoC data क्रम a Timer/Counter Block
 * @counter_width: size in bits of a समयr counter रेजिस्टर
 * @has_gclk: boolean indicating अगर a समयr counter has a generic घड़ी
 * @has_qdec: boolean indicating अगर a समयr counter has a quadrature
 * decoder.
 */
काष्ठा aपंचांगel_tcb_config अणु
	माप_प्रकार	counter_width;
	bool    has_gclk;
	bool    has_qdec;
पूर्ण;

/**
 * काष्ठा aपंचांगel_tc - inक्रमmation about a Timer/Counter Block
 * @pdev: physical device
 * @regs: mapping through which the I/O रेजिस्टरs can be accessed
 * @id: block id
 * @tcb_config: configuration data from SoC
 * @irq: irq क्रम each of the three channels
 * @clk: पूर्णांकernal घड़ी source क्रम each of the three channels
 * @node: list node, क्रम tclib पूर्णांकernal use
 * @allocated: अगर alपढ़ोy used, क्रम tclib पूर्णांकernal use
 *
 * On some platक्रमms, each TC channel has its own घड़ीs and IRQs,
 * जबतक on others, all TC channels share the same घड़ी and IRQ.
 * Drivers should clk_enable() all the घड़ीs they need even though
 * all the entries in @clk may poपूर्णांक to the same physical घड़ी.
 * Likewise, drivers should request irqs independently क्रम each
 * channel, but they must use IRQF_SHARED in हाल some of the entries
 * in @irq are actually the same IRQ.
 */
काष्ठा aपंचांगel_tc अणु
	काष्ठा platक्रमm_device	*pdev;
	व्योम __iomem		*regs;
	पूर्णांक                     id;
	स्थिर काष्ठा aपंचांगel_tcb_config *tcb_config;
	पूर्णांक			irq[3];
	काष्ठा clk		*clk[3];
	काष्ठा clk		*slow_clk;
	काष्ठा list_head	node;
	bool			allocated;
पूर्ण;

बाह्य काष्ठा aपंचांगel_tc *aपंचांगel_tc_alloc(अचिन्हित block);
बाह्य व्योम aपंचांगel_tc_मुक्त(काष्ठा aपंचांगel_tc *tc);

/* platक्रमm-specअगरic ATMEL_TC_TIMER_CLOCKx भागisors (0 means 32KiHz) */
बाह्य स्थिर u8 aपंचांगel_tc_भागisors[5];


/*
 * Two रेजिस्टरs have block-wide controls.  These are: configuring the three
 * "external" घड़ीs (or event sources) used by the समयr channels; and
 * synchronizing the समयrs by resetting them all at once.
 *
 * "External" can mean "external to chip" using the TCLK0, TCLK1, or TCLK2
 * संकेतs.  Or, it can mean "external to timer", using the TIOA output from
 * one of the other two समयrs that's being run in waveक्रमm mode.
 */

#घोषणा ATMEL_TC_BCR	0xc0		/* TC Block Control Register */
#घोषणा     ATMEL_TC_SYNC	(1 << 0)	/* synchronize समयrs */

#घोषणा ATMEL_TC_BMR	0xc4		/* TC Block Mode Register */
#घोषणा     ATMEL_TC_TC0XC0S	(3 << 0)	/* बाह्यal घड़ी 0 source */
#घोषणा        ATMEL_TC_TC0XC0S_TCLK0	(0 << 0)
#घोषणा        ATMEL_TC_TC0XC0S_NONE	(1 << 0)
#घोषणा        ATMEL_TC_TC0XC0S_TIOA1	(2 << 0)
#घोषणा        ATMEL_TC_TC0XC0S_TIOA2	(3 << 0)
#घोषणा     ATMEL_TC_TC1XC1S	(3 << 2)	/* बाह्यal घड़ी 1 source */
#घोषणा        ATMEL_TC_TC1XC1S_TCLK1	(0 << 2)
#घोषणा        ATMEL_TC_TC1XC1S_NONE	(1 << 2)
#घोषणा        ATMEL_TC_TC1XC1S_TIOA0	(2 << 2)
#घोषणा        ATMEL_TC_TC1XC1S_TIOA2	(3 << 2)
#घोषणा     ATMEL_TC_TC2XC2S	(3 << 4)	/* बाह्यal घड़ी 2 source */
#घोषणा        ATMEL_TC_TC2XC2S_TCLK2	(0 << 4)
#घोषणा        ATMEL_TC_TC2XC2S_NONE	(1 << 4)
#घोषणा        ATMEL_TC_TC2XC2S_TIOA0	(2 << 4)
#घोषणा        ATMEL_TC_TC2XC2S_TIOA1	(3 << 4)


/*
 * Each TC block has three "channels", each with one counter and controls.
 *
 * Note that the semantics of ATMEL_TC_TIMER_CLOCKx (input घड़ी selection
 * when it's not "external") is silicon-specअगरic.  AT91 platक्रमms use one
 * set of definitions; AVR32 platक्रमms use a dअगरferent set.  Don't hard-wire
 * such knowledge पूर्णांकo your code, use the global "atmel_tc_divisors" ...
 * where index N is the भागisor क्रम घड़ी N+1, अन्यथा zero to indicate it uses
 * the 32 KiHz घड़ी.
 *
 * The समयrs can be chained in various ways, and operated in "waveform"
 * generation mode (including PWM) or "capture" mode (to समय events).  In
 * both modes, behavior can be configured in many ways.
 *
 * Each समयr has two I/O pins, TIOA and TIOB.  Waveक्रमm mode uses TIOA as a
 * PWM output, and TIOB as either another PWM or as a trigger.  Capture mode
 * uses them only as inमाला_दो.
 */
#घोषणा ATMEL_TC_CHAN(idx)	((idx)*0x40)
#घोषणा ATMEL_TC_REG(idx, reg)	(ATMEL_TC_CHAN(idx) + ATMEL_TC_ ## reg)

#घोषणा ATMEL_TC_CCR	0x00		/* Channel Control Register */
#घोषणा     ATMEL_TC_CLKEN	(1 << 0)	/* घड़ी enable */
#घोषणा     ATMEL_TC_CLKDIS	(1 << 1)	/* घड़ी disable */
#घोषणा     ATMEL_TC_SWTRG	(1 << 2)	/* software trigger */

#घोषणा ATMEL_TC_CMR	0x04		/* Channel Mode Register */

/* Both modes share some CMR bits */
#घोषणा     ATMEL_TC_TCCLKS	(7 << 0)	/* घड़ी source */
#घोषणा        ATMEL_TC_TIMER_CLOCK1	(0 << 0)
#घोषणा        ATMEL_TC_TIMER_CLOCK2	(1 << 0)
#घोषणा        ATMEL_TC_TIMER_CLOCK3	(2 << 0)
#घोषणा        ATMEL_TC_TIMER_CLOCK4	(3 << 0)
#घोषणा        ATMEL_TC_TIMER_CLOCK5	(4 << 0)
#घोषणा        ATMEL_TC_XC0		(5 << 0)
#घोषणा        ATMEL_TC_XC1		(6 << 0)
#घोषणा        ATMEL_TC_XC2		(7 << 0)
#घोषणा     ATMEL_TC_CLKI	(1 << 3)	/* घड़ी invert */
#घोषणा     ATMEL_TC_BURST	(3 << 4)	/* घड़ी gating */
#घोषणा        ATMEL_TC_GATE_NONE	(0 << 4)
#घोषणा        ATMEL_TC_GATE_XC0	(1 << 4)
#घोषणा        ATMEL_TC_GATE_XC1	(2 << 4)
#घोषणा        ATMEL_TC_GATE_XC2	(3 << 4)
#घोषणा     ATMEL_TC_WAVE	(1 << 15)	/* true = Waveक्रमm mode */

/* CAPTURE mode CMR bits */
#घोषणा     ATMEL_TC_LDBSTOP	(1 << 6)	/* counter stops on RB load */
#घोषणा     ATMEL_TC_LDBDIS	(1 << 7)	/* counter disable on RB load */
#घोषणा     ATMEL_TC_ETRGEDG	(3 << 8)	/* बाह्यal trigger edge */
#घोषणा        ATMEL_TC_ETRGEDG_NONE	(0 << 8)
#घोषणा        ATMEL_TC_ETRGEDG_RISING	(1 << 8)
#घोषणा        ATMEL_TC_ETRGEDG_FALLING	(2 << 8)
#घोषणा        ATMEL_TC_ETRGEDG_BOTH	(3 << 8)
#घोषणा     ATMEL_TC_ABETRG	(1 << 10)	/* बाह्यal trigger is TIOA? */
#घोषणा     ATMEL_TC_CPCTRG	(1 << 14)	/* RC compare trigger enable */
#घोषणा     ATMEL_TC_LDRA	(3 << 16)	/* RA loading edge (of TIOA) */
#घोषणा        ATMEL_TC_LDRA_NONE	(0 << 16)
#घोषणा        ATMEL_TC_LDRA_RISING	(1 << 16)
#घोषणा        ATMEL_TC_LDRA_FALLING	(2 << 16)
#घोषणा        ATMEL_TC_LDRA_BOTH	(3 << 16)
#घोषणा     ATMEL_TC_LDRB	(3 << 18)	/* RB loading edge (of TIOA) */
#घोषणा        ATMEL_TC_LDRB_NONE	(0 << 18)
#घोषणा        ATMEL_TC_LDRB_RISING	(1 << 18)
#घोषणा        ATMEL_TC_LDRB_FALLING	(2 << 18)
#घोषणा        ATMEL_TC_LDRB_BOTH	(3 << 18)

/* WAVEFORM mode CMR bits */
#घोषणा     ATMEL_TC_CPCSTOP	(1 <<  6)	/* RC compare stops counter */
#घोषणा     ATMEL_TC_CPCDIS	(1 <<  7)	/* RC compare disables counter */
#घोषणा     ATMEL_TC_EEVTEDG	(3 <<  8)	/* बाह्यal event edge */
#घोषणा        ATMEL_TC_EEVTEDG_NONE	(0 << 8)
#घोषणा        ATMEL_TC_EEVTEDG_RISING	(1 << 8)
#घोषणा        ATMEL_TC_EEVTEDG_FALLING	(2 << 8)
#घोषणा        ATMEL_TC_EEVTEDG_BOTH	(3 << 8)
#घोषणा     ATMEL_TC_EEVT	(3 << 10)	/* बाह्यal event source */
#घोषणा        ATMEL_TC_EEVT_TIOB	(0 << 10)
#घोषणा        ATMEL_TC_EEVT_XC0	(1 << 10)
#घोषणा        ATMEL_TC_EEVT_XC1	(2 << 10)
#घोषणा        ATMEL_TC_EEVT_XC2	(3 << 10)
#घोषणा     ATMEL_TC_ENETRG	(1 << 12)	/* बाह्यal event is trigger */
#घोषणा     ATMEL_TC_WAVESEL	(3 << 13)	/* waveक्रमm type */
#घोषणा        ATMEL_TC_WAVESEL_UP	(0 << 13)
#घोषणा        ATMEL_TC_WAVESEL_UPDOWN	(1 << 13)
#घोषणा        ATMEL_TC_WAVESEL_UP_AUTO	(2 << 13)
#घोषणा        ATMEL_TC_WAVESEL_UPDOWN_AUTO (3 << 13)
#घोषणा     ATMEL_TC_ACPA	(3 << 16)	/* RA compare changes TIOA */
#घोषणा        ATMEL_TC_ACPA_NONE	(0 << 16)
#घोषणा        ATMEL_TC_ACPA_SET	(1 << 16)
#घोषणा        ATMEL_TC_ACPA_CLEAR	(2 << 16)
#घोषणा        ATMEL_TC_ACPA_TOGGLE	(3 << 16)
#घोषणा     ATMEL_TC_ACPC	(3 << 18)	/* RC compare changes TIOA */
#घोषणा        ATMEL_TC_ACPC_NONE	(0 << 18)
#घोषणा        ATMEL_TC_ACPC_SET	(1 << 18)
#घोषणा        ATMEL_TC_ACPC_CLEAR	(2 << 18)
#घोषणा        ATMEL_TC_ACPC_TOGGLE	(3 << 18)
#घोषणा     ATMEL_TC_AEEVT	(3 << 20)	/* बाह्यal event changes TIOA */
#घोषणा        ATMEL_TC_AEEVT_NONE	(0 << 20)
#घोषणा        ATMEL_TC_AEEVT_SET	(1 << 20)
#घोषणा        ATMEL_TC_AEEVT_CLEAR	(2 << 20)
#घोषणा        ATMEL_TC_AEEVT_TOGGLE	(3 << 20)
#घोषणा     ATMEL_TC_ASWTRG	(3 << 22)	/* software trigger changes TIOA */
#घोषणा        ATMEL_TC_ASWTRG_NONE	(0 << 22)
#घोषणा        ATMEL_TC_ASWTRG_SET	(1 << 22)
#घोषणा        ATMEL_TC_ASWTRG_CLEAR	(2 << 22)
#घोषणा        ATMEL_TC_ASWTRG_TOGGLE	(3 << 22)
#घोषणा     ATMEL_TC_BCPB	(3 << 24)	/* RB compare changes TIOB */
#घोषणा        ATMEL_TC_BCPB_NONE	(0 << 24)
#घोषणा        ATMEL_TC_BCPB_SET	(1 << 24)
#घोषणा        ATMEL_TC_BCPB_CLEAR	(2 << 24)
#घोषणा        ATMEL_TC_BCPB_TOGGLE	(3 << 24)
#घोषणा     ATMEL_TC_BCPC	(3 << 26)	/* RC compare changes TIOB */
#घोषणा        ATMEL_TC_BCPC_NONE	(0 << 26)
#घोषणा        ATMEL_TC_BCPC_SET	(1 << 26)
#घोषणा        ATMEL_TC_BCPC_CLEAR	(2 << 26)
#घोषणा        ATMEL_TC_BCPC_TOGGLE	(3 << 26)
#घोषणा     ATMEL_TC_BEEVT	(3 << 28)	/* बाह्यal event changes TIOB */
#घोषणा        ATMEL_TC_BEEVT_NONE	(0 << 28)
#घोषणा        ATMEL_TC_BEEVT_SET	(1 << 28)
#घोषणा        ATMEL_TC_BEEVT_CLEAR	(2 << 28)
#घोषणा        ATMEL_TC_BEEVT_TOGGLE	(3 << 28)
#घोषणा     ATMEL_TC_BSWTRG	(3 << 30)	/* software trigger changes TIOB */
#घोषणा        ATMEL_TC_BSWTRG_NONE	(0 << 30)
#घोषणा        ATMEL_TC_BSWTRG_SET	(1 << 30)
#घोषणा        ATMEL_TC_BSWTRG_CLEAR	(2 << 30)
#घोषणा        ATMEL_TC_BSWTRG_TOGGLE	(3 << 30)

#घोषणा ATMEL_TC_CV	0x10		/* counter Value */
#घोषणा ATMEL_TC_RA	0x14		/* रेजिस्टर A */
#घोषणा ATMEL_TC_RB	0x18		/* रेजिस्टर B */
#घोषणा ATMEL_TC_RC	0x1c		/* रेजिस्टर C */

#घोषणा ATMEL_TC_SR	0x20		/* status (पढ़ो-only) */
/* Status-only flags */
#घोषणा     ATMEL_TC_CLKSTA	(1 << 16)	/* घड़ी enabled */
#घोषणा     ATMEL_TC_MTIOA	(1 << 17)	/* TIOA mirror */
#घोषणा     ATMEL_TC_MTIOB	(1 << 18)	/* TIOB mirror */

#घोषणा ATMEL_TC_IER	0x24		/* पूर्णांकerrupt enable (ग_लिखो-only) */
#घोषणा ATMEL_TC_IDR	0x28		/* पूर्णांकerrupt disable (ग_लिखो-only) */
#घोषणा ATMEL_TC_IMR	0x2c		/* पूर्णांकerrupt mask (पढ़ो-only) */

/* Status and IRQ flags */
#घोषणा     ATMEL_TC_COVFS	(1 <<  0)	/* counter overflow */
#घोषणा     ATMEL_TC_LOVRS	(1 <<  1)	/* load overrun */
#घोषणा     ATMEL_TC_CPAS	(1 <<  2)	/* RA compare */
#घोषणा     ATMEL_TC_CPBS	(1 <<  3)	/* RB compare */
#घोषणा     ATMEL_TC_CPCS	(1 <<  4)	/* RC compare */
#घोषणा     ATMEL_TC_LDRAS	(1 <<  5)	/* RA loading */
#घोषणा     ATMEL_TC_LDRBS	(1 <<  6)	/* RB loading */
#घोषणा     ATMEL_TC_ETRGS	(1 <<  7)	/* बाह्यal trigger */
#घोषणा     ATMEL_TC_ALL_IRQ	(ATMEL_TC_COVFS	| ATMEL_TC_LOVRS | \
				 ATMEL_TC_CPAS | ATMEL_TC_CPBS | \
				 ATMEL_TC_CPCS | ATMEL_TC_LDRAS | \
				 ATMEL_TC_LDRBS | ATMEL_TC_ETRGS) \
				 /* all IRQs */

#पूर्ण_अगर
