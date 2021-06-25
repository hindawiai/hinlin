<शैली गुरु>
/*
 * include/यंत्र-mips/txx9पंचांगr.h
 * TX39/TX49 समयr controller definitions.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#अगर_अघोषित __ASM_TXX9TMR_H
#घोषणा __ASM_TXX9TMR_H

#समावेश <linux/types.h>

काष्ठा txx9_पंचांगr_reg अणु
	u32 tcr;
	u32 tisr;
	u32 cpra;
	u32 cprb;
	u32 iपंचांगr;
	u32 unused0[3];
	u32 ccdr;
	u32 unused1[3];
	u32 pgmr;
	u32 unused2[3];
	u32 wपंचांगr;
	u32 unused3[43];
	u32 trr;
पूर्ण;

/* TMTCR : Timer Control */
#घोषणा TXx9_TMTCR_TCE		0x00000080
#घोषणा TXx9_TMTCR_CCDE		0x00000040
#घोषणा TXx9_TMTCR_CRE		0x00000020
#घोषणा TXx9_TMTCR_ECES		0x00000008
#घोषणा TXx9_TMTCR_CCS		0x00000004
#घोषणा TXx9_TMTCR_TMODE_MASK	0x00000003
#घोषणा TXx9_TMTCR_TMODE_ITVL	0x00000000
#घोषणा TXx9_TMTCR_TMODE_PGEN	0x00000001
#घोषणा TXx9_TMTCR_TMODE_WDOG	0x00000002

/* TMTISR : Timer Int. Status */
#घोषणा TXx9_TMTISR_TPIBS	0x00000004
#घोषणा TXx9_TMTISR_TPIAS	0x00000002
#घोषणा TXx9_TMTISR_TIIS	0x00000001

/* TMITMR : Interval Timer Mode */
#घोषणा TXx9_TMITMR_TIIE	0x00008000
#घोषणा TXx9_TMITMR_TZCE	0x00000001

/* TMWTMR : Watchकरोg Timer Mode */
#घोषणा TXx9_TMWTMR_TWIE	0x00008000
#घोषणा TXx9_TMWTMR_WDIS	0x00000080
#घोषणा TXx9_TMWTMR_TWC		0x00000001

व्योम txx9_घड़ीsource_init(अचिन्हित दीर्घ baseaddr,
			   अचिन्हित पूर्णांक imbusclk);
व्योम txx9_घड़ीevent_init(अचिन्हित दीर्घ baseaddr, पूर्णांक irq,
			  अचिन्हित पूर्णांक imbusclk);
व्योम txx9_पंचांगr_init(अचिन्हित दीर्घ baseaddr);

#अगर_घोषित CONFIG_CPU_TX39XX
#घोषणा TXX9_TIMER_BITS 24
#अन्यथा
#घोषणा TXX9_TIMER_BITS 32
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_TXX9TMR_H */
