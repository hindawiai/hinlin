<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * TI DaVinci Audio definitions
 */
#अगर_अघोषित __ASM_ARCH_DAVINCI_ASP_H
#घोषणा __ASM_ARCH_DAVINCI_ASP_H

/* Bases of dm644x and dm355 रेजिस्टर banks */
#घोषणा DAVINCI_ASP0_BASE	0x01E02000
#घोषणा DAVINCI_ASP1_BASE	0x01E04000

/* Bases of dm365 रेजिस्टर banks */
#घोषणा DAVINCI_DM365_ASP0_BASE	0x01D02000

/* Bases of dm646x रेजिस्टर banks */
#घोषणा DAVINCI_DM646X_MCASP0_REG_BASE		0x01D01000
#घोषणा DAVINCI_DM646X_MCASP1_REG_BASE		0x01D01800

/* Bases of da850/da830 McASP0  रेजिस्टर banks */
#घोषणा DAVINCI_DA8XX_MCASP0_REG_BASE	0x01D00000

/* Bases of da830 McASP1 रेजिस्टर banks */
#घोषणा DAVINCI_DA830_MCASP1_REG_BASE	0x01D04000

/* Bases of da830 McASP2 रेजिस्टर banks */
#घोषणा DAVINCI_DA830_MCASP2_REG_BASE	0x01D08000

/* EDMA channels of dm644x and dm355 */
#घोषणा DAVINCI_DMA_ASP0_TX	2
#घोषणा DAVINCI_DMA_ASP0_RX	3
#घोषणा DAVINCI_DMA_ASP1_TX	8
#घोषणा DAVINCI_DMA_ASP1_RX	9

/* EDMA channels of dm646x */
#घोषणा DAVINCI_DM646X_DMA_MCASP0_AXEVT0	6
#घोषणा DAVINCI_DM646X_DMA_MCASP0_AREVT0	9
#घोषणा DAVINCI_DM646X_DMA_MCASP1_AXEVT1	12

/* EDMA channels of da850/da830 McASP0 */
#घोषणा DAVINCI_DA8XX_DMA_MCASP0_AREVT	0
#घोषणा DAVINCI_DA8XX_DMA_MCASP0_AXEVT	1

/* EDMA channels of da830 McASP1 */
#घोषणा DAVINCI_DA830_DMA_MCASP1_AREVT	2
#घोषणा DAVINCI_DA830_DMA_MCASP1_AXEVT	3

/* EDMA channels of da830 McASP2 */
#घोषणा DAVINCI_DA830_DMA_MCASP2_AREVT	4
#घोषणा DAVINCI_DA830_DMA_MCASP2_AXEVT	5

/* Interrupts */
#घोषणा DAVINCI_ASP0_RX_INT	DAVINCI_INTC_IRQ(IRQ_MBRINT)
#घोषणा DAVINCI_ASP0_TX_INT	DAVINCI_INTC_IRQ(IRQ_MBXINT)
#घोषणा DAVINCI_ASP1_RX_INT	DAVINCI_INTC_IRQ(IRQ_MBRINT)
#घोषणा DAVINCI_ASP1_TX_INT	DAVINCI_INTC_IRQ(IRQ_MBXINT)

#पूर्ण_अगर /* __ASM_ARCH_DAVINCI_ASP_H */
