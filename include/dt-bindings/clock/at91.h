<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * This header provides स्थिरants क्रम AT91 pmc status.
 *
 * The स्थिरants defined in this header are being used in dts.
 */

#अगर_अघोषित _DT_BINDINGS_CLK_AT91_H
#घोषणा _DT_BINDINGS_CLK_AT91_H

#घोषणा PMC_TYPE_CORE		0
#घोषणा PMC_TYPE_SYSTEM		1
#घोषणा PMC_TYPE_PERIPHERAL	2
#घोषणा PMC_TYPE_GCK		3
#घोषणा PMC_TYPE_PROGRAMMABLE	4

#घोषणा PMC_SLOW		0
#घोषणा PMC_MCK			1
#घोषणा PMC_UTMI		2
#घोषणा PMC_MAIN		3
#घोषणा PMC_MCK2		4
#घोषणा PMC_I2S0_MUX		5
#घोषणा PMC_I2S1_MUX		6
#घोषणा PMC_PLLACK		7
#घोषणा PMC_PLLBCK		8
#घोषणा PMC_AUDIOPLLCK		9

/* SAMA7G5 */
#घोषणा PMC_CPUPLL		(PMC_MAIN + 1)
#घोषणा PMC_SYSPLL		(PMC_MAIN + 2)
#घोषणा PMC_DDRPLL		(PMC_MAIN + 3)
#घोषणा PMC_IMGPLL		(PMC_MAIN + 4)
#घोषणा PMC_BAUDPLL		(PMC_MAIN + 5)
#घोषणा PMC_AUDIOPMCPLL		(PMC_MAIN + 6)
#घोषणा PMC_AUDIOIOPLL		(PMC_MAIN + 7)
#घोषणा PMC_ETHPLL		(PMC_MAIN + 8)
#घोषणा PMC_CPU			(PMC_MAIN + 9)

#अगर_अघोषित AT91_PMC_MOSCS
#घोषणा AT91_PMC_MOSCS		0		/* MOSCS Flag */
#घोषणा AT91_PMC_LOCKA		1		/* PLLA Lock */
#घोषणा AT91_PMC_LOCKB		2		/* PLLB Lock */
#घोषणा AT91_PMC_MCKRDY		3		/* Master Clock */
#घोषणा AT91_PMC_LOCKU		6		/* UPLL Lock */
#घोषणा AT91_PMC_PCKRDY(id)	(8 + (id))	/* Programmable Clock */
#घोषणा AT91_PMC_MOSCSELS	16		/* Main Oscillator Selection */
#घोषणा AT91_PMC_MOSCRCS	17		/* Main On-Chip RC */
#घोषणा AT91_PMC_CFDEV		18		/* Clock Failure Detector Event */
#घोषणा AT91_PMC_GCKRDY		24		/* Generated Clocks */
#पूर्ण_अगर

#पूर्ण_अगर
