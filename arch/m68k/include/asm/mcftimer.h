<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/****************************************************************************/

/*
 *	mcfसमयr.h -- ColdFire पूर्णांकernal TIMER support defines.
 *
 *	(C) Copyright 1999-2006, Greg Ungerer <gerg@snapgear.com>
 * 	(C) Copyright 2000, Lineo Inc. (www.lineo.com) 
 */

/****************************************************************************/
#अगर_अघोषित	mcfसमयr_h
#घोषणा	mcfसमयr_h
/****************************************************************************/

/*
 *	Define the TIMER रेजिस्टर set addresses.
 */
#घोषणा	MCFTIMER_TMR		0x00		/* Timer Mode reg (r/w) */
#घोषणा	MCFTIMER_TRR		0x04		/* Timer Reference (r/w) */
#घोषणा	MCFTIMER_TCR		0x08		/* Timer Capture reg (r/w) */
#घोषणा	MCFTIMER_TCN		0x0C		/* Timer Counter reg (r/w) */
#अगर defined(CONFIG_M53xx) || defined(CONFIG_M5441x)
#घोषणा	MCFTIMER_TER		0x03		/* Timer Event reg (r/w) */
#अन्यथा
#घोषणा	MCFTIMER_TER		0x11		/* Timer Event reg (r/w) */
#पूर्ण_अगर

/*
 *	Bit definitions क्रम the Timer Mode Register (TMR).
 *	Register bit flags are common across ColdFires.
 */
#घोषणा	MCFTIMER_TMR_PREMASK	0xff00		/* Prescalar mask */
#घोषणा	MCFTIMER_TMR_DISCE	0x0000		/* Disable capture */
#घोषणा	MCFTIMER_TMR_ANYCE	0x00c0		/* Capture any edge */
#घोषणा	MCFTIMER_TMR_FALLCE	0x0080		/* Capture fallingedge */
#घोषणा	MCFTIMER_TMR_RISECE	0x0040		/* Capture rising edge */
#घोषणा	MCFTIMER_TMR_ENOM	0x0020		/* Enable output toggle */
#घोषणा	MCFTIMER_TMR_DISOM	0x0000		/* Do single output pulse  */
#घोषणा	MCFTIMER_TMR_ENORI	0x0010		/* Enable ref पूर्णांकerrupt */
#घोषणा	MCFTIMER_TMR_DISORI	0x0000		/* Disable ref पूर्णांकerrupt */
#घोषणा	MCFTIMER_TMR_RESTART	0x0008		/* Restart counter */
#घोषणा	MCFTIMER_TMR_FREERUN	0x0000		/* Free running counter */
#घोषणा	MCFTIMER_TMR_CLKTIN	0x0006		/* Input घड़ी is TIN */
#घोषणा	MCFTIMER_TMR_CLK16	0x0004		/* Input घड़ी is /16 */
#घोषणा	MCFTIMER_TMR_CLK1	0x0002		/* Input घड़ी is /1 */
#घोषणा	MCFTIMER_TMR_CLKSTOP	0x0000		/* Stop counter */
#घोषणा	MCFTIMER_TMR_ENABLE	0x0001		/* Enable समयr */
#घोषणा	MCFTIMER_TMR_DISABLE	0x0000		/* Disable समयr */

/*
 *	Bit definitions क्रम the Timer Event Registers (TER).
 */
#घोषणा	MCFTIMER_TER_CAP	0x01		/* Capture event */
#घोषणा	MCFTIMER_TER_REF	0x02		/* Reference event */

/****************************************************************************/
#पूर्ण_अगर	/* mcfसमयr_h */
