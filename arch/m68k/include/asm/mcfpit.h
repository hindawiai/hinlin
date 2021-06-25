<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/****************************************************************************/

/*
 *	mcfpit.h -- ColdFire पूर्णांकernal PIT समयr support defines.
 *
 *	(C) Copyright 2003, Greg Ungerer (gerg@snapgear.com)
 */

/****************************************************************************/
#अगर_अघोषित	mcfpit_h
#घोषणा	mcfpit_h
/****************************************************************************/

/*
 *	Define the PIT समयr रेजिस्टर address offsets.
 */
#घोषणा	MCFPIT_PCSR		0x0		/* PIT control रेजिस्टर */
#घोषणा	MCFPIT_PMR		0x2		/* PIT modulus रेजिस्टर */
#घोषणा	MCFPIT_PCNTR		0x4		/* PIT count रेजिस्टर */

/*
 *	Bit definitions क्रम the PIT Control and Status रेजिस्टर.
 */
#घोषणा	MCFPIT_PCSR_CLK1	0x0000		/* System घड़ी भागisor */
#घोषणा	MCFPIT_PCSR_CLK2	0x0100		/* System घड़ी भागisor */
#घोषणा	MCFPIT_PCSR_CLK4	0x0200		/* System घड़ी भागisor */
#घोषणा	MCFPIT_PCSR_CLK8	0x0300		/* System घड़ी भागisor */
#घोषणा	MCFPIT_PCSR_CLK16	0x0400		/* System घड़ी भागisor */
#घोषणा	MCFPIT_PCSR_CLK32	0x0500		/* System घड़ी भागisor */
#घोषणा	MCFPIT_PCSR_CLK64	0x0600		/* System घड़ी भागisor */
#घोषणा	MCFPIT_PCSR_CLK128	0x0700		/* System घड़ी भागisor */
#घोषणा	MCFPIT_PCSR_CLK256	0x0800		/* System घड़ी भागisor */
#घोषणा	MCFPIT_PCSR_CLK512	0x0900		/* System घड़ी भागisor */
#घोषणा	MCFPIT_PCSR_CLK1024	0x0a00		/* System घड़ी भागisor */
#घोषणा	MCFPIT_PCSR_CLK2048	0x0b00		/* System घड़ी भागisor */
#घोषणा	MCFPIT_PCSR_CLK4096	0x0c00		/* System घड़ी भागisor */
#घोषणा	MCFPIT_PCSR_CLK8192	0x0d00		/* System घड़ी भागisor */
#घोषणा	MCFPIT_PCSR_CLK16384	0x0e00		/* System घड़ी भागisor */
#घोषणा	MCFPIT_PCSR_CLK32768	0x0f00		/* System घड़ी भागisor */
#घोषणा	MCFPIT_PCSR_DOZE	0x0040		/* Clock run in करोze mode */
#घोषणा	MCFPIT_PCSR_HALTED	0x0020		/* Clock run in halt mode */
#घोषणा	MCFPIT_PCSR_OVW		0x0010		/* Overग_लिखो PIT counter now */
#घोषणा	MCFPIT_PCSR_PIE		0x0008		/* Enable PIT पूर्णांकerrupt */
#घोषणा	MCFPIT_PCSR_PIF		0x0004		/* PIT पूर्णांकerrupt flag */
#घोषणा	MCFPIT_PCSR_RLD		0x0002		/* Reload counter */
#घोषणा	MCFPIT_PCSR_EN		0x0001		/* Enable PIT */
#घोषणा	MCFPIT_PCSR_DISABLE	0x0000		/* Disable PIT */

/****************************************************************************/
#पूर्ण_अगर	/* mcfpit_h */
