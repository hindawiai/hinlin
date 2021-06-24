<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/************************************************************************
 * Include file क्रम TRIZEPS4 SoM and ConXS eval-board
 * Copyright (c) Jथञrgen Schindele
 * 2006
 ************************************************************************/

/*
 * Includes/Defines
 */
#अगर_अघोषित _TRIPEPS4_H_
#घोषणा _TRIPEPS4_H_

#समावेश "irqs.h" /* PXA_GPIO_TO_IRQ */

/* physical memory regions */
#घोषणा TRIZEPS4_FLASH_PHYS	(PXA_CS0_PHYS)  /* Flash region */
#घोषणा TRIZEPS4_DISK_PHYS	(PXA_CS1_PHYS)  /* Disk On Chip region */
#घोषणा TRIZEPS4_ETH_PHYS	(PXA_CS2_PHYS)  /* Ethernet DM9000 region */
#घोषणा TRIZEPS4_PIC_PHYS	(PXA_CS3_PHYS)	/* Logic chip on ConXS-Board */
#घोषणा TRIZEPS4_SDRAM_BASE	0xa0000000      /* SDRAM region */

				/* Logic on ConXS-board CSFR रेजिस्टर*/
#घोषणा TRIZEPS4_CFSR_PHYS	(PXA_CS3_PHYS)
				/* Logic on ConXS-board BOCR रेजिस्टर*/
#घोषणा TRIZEPS4_BOCR_PHYS	(PXA_CS3_PHYS+0x02000000)
				/* Logic on ConXS-board IRCR रेजिस्टर*/
#घोषणा TRIZEPS4_IRCR_PHYS	(PXA_CS3_PHYS+0x02400000)
				/* Logic on ConXS-board UPSR रेजिस्टर*/
#घोषणा TRIZEPS4_UPSR_PHYS	(PXA_CS3_PHYS+0x02800000)
				/* Logic on ConXS-board DICR रेजिस्टर*/
#घोषणा TRIZEPS4_DICR_PHYS	(PXA_CS3_PHYS+0x03800000)

/* भव memory regions */
#घोषणा TRIZEPS4_DISK_VIRT	0xF0000000	/* Disk On Chip region */

#घोषणा TRIZEPS4_PIC_VIRT	0xF0100000	/* not used */
#घोषणा TRIZEPS4_CFSR_VIRT	0xF0100000
#घोषणा TRIZEPS4_BOCR_VIRT	0xF0200000
#घोषणा TRIZEPS4_DICR_VIRT	0xF0300000
#घोषणा TRIZEPS4_IRCR_VIRT	0xF0400000
#घोषणा TRIZEPS4_UPSR_VIRT	0xF0500000

/* size of flash */
#घोषणा TRIZEPS4_FLASH_SIZE	0x02000000	/* Flash size 32 MB */

/* Ethernet Controller Davicom DM9000 */
#घोषणा GPIO_DM9000		101
#घोषणा TRIZEPS4_ETH_IRQ	PXA_GPIO_TO_IRQ(GPIO_DM9000)

/* UCB1400 audio / TS-controller */
#घोषणा GPIO_UCB1400		1
#घोषणा TRIZEPS4_UCB1400_IRQ	PXA_GPIO_TO_IRQ(GPIO_UCB1400)

/* PCMCIA socket Compact Flash */
#घोषणा GPIO_PCD		11		/* PCMCIA Card Detect */
#घोषणा TRIZEPS4_CD_IRQ		PXA_GPIO_TO_IRQ(GPIO_PCD)
#घोषणा GPIO_PRDY		13		/* READY / nINT */
#घोषणा TRIZEPS4_READY_NINT	PXA_GPIO_TO_IRQ(GPIO_PRDY)

/* MMC socket */
#घोषणा GPIO_MMC_DET		12
#घोषणा TRIZEPS4_MMC_IRQ	PXA_GPIO_TO_IRQ(GPIO_MMC_DET)

/* DOC न_अंकD chip */
#घोषणा GPIO_DOC_LOCK           94
#घोषणा GPIO_DOC_IRQ            93
#घोषणा TRIZEPS4_DOC_IRQ        PXA_GPIO_TO_IRQ(GPIO_DOC_IRQ)

/* SPI पूर्णांकerface */
#घोषणा GPIO_SPI                53
#घोषणा TRIZEPS4_SPI_IRQ        PXA_GPIO_TO_IRQ(GPIO_SPI)

/* LEDS using tx2 / rx2 */
#घोषणा GPIO_SYS_BUSY_LED	46
#घोषणा GPIO_HEARTBEAT_LED	47

/* Off-module PIC on ConXS board */
#घोषणा GPIO_PIC		0
#घोषणा TRIZEPS4_PIC_IRQ	PXA_GPIO_TO_IRQ(GPIO_PIC)

#अगर_घोषित CONFIG_MACH_TRIZEPS_CONXS
/* क्रम CONXS base board define these रेजिस्टरs */
#घोषणा CFSR_P2V(x)	((x) - TRIZEPS4_CFSR_PHYS + TRIZEPS4_CFSR_VIRT)
#घोषणा CFSR_V2P(x)	((x) - TRIZEPS4_CFSR_VIRT + TRIZEPS4_CFSR_PHYS)

#घोषणा BCR_P2V(x)	((x) - TRIZEPS4_BOCR_PHYS + TRIZEPS4_BOCR_VIRT)
#घोषणा BCR_V2P(x)	((x) - TRIZEPS4_BOCR_VIRT + TRIZEPS4_BOCR_PHYS)

#घोषणा DCR_P2V(x)	((x) - TRIZEPS4_DICR_PHYS + TRIZEPS4_DICR_VIRT)
#घोषणा DCR_V2P(x)	((x) - TRIZEPS4_DICR_VIRT + TRIZEPS4_DICR_PHYS)

#घोषणा IRCR_P2V(x)	((x) - TRIZEPS4_IRCR_PHYS + TRIZEPS4_IRCR_VIRT)
#घोषणा IRCR_V2P(x)	((x) - TRIZEPS4_IRCR_VIRT + TRIZEPS4_IRCR_PHYS)

#अगर_अघोषित __ASSEMBLY__
अटल अंतरभूत अचिन्हित लघु CFSR_पढ़ोw(व्योम)
अणु
	/* [Compact Flash Status Register] is पढ़ो only */
	वापस *((अचिन्हित लघु *)CFSR_P2V(0x0C000000));
पूर्ण
अटल अंतरभूत व्योम BCR_ग_लिखोw(अचिन्हित लघु value)
अणु
	/* [Board Control Regsiter] is ग_लिखो only */
	*((अचिन्हित लघु *)BCR_P2V(0x0E000000)) = value;
पूर्ण
अटल अंतरभूत व्योम DCR_ग_लिखोw(अचिन्हित लघु value)
अणु
	/* [Display Control Register] is ग_लिखो only */
	*((अचिन्हित लघु *)DCR_P2V(0x0E000000)) = value;
पूर्ण
अटल अंतरभूत व्योम IRCR_ग_लिखोw(अचिन्हित लघु value)
अणु
	/* [InfraRed data Control Register] is ग_लिखो only */
	*((अचिन्हित लघु *)IRCR_P2V(0x0E000000)) = value;
पूर्ण
#अन्यथा
#घोषणा ConXS_CFSR		CFSR_P2V(0x0C000000)
#घोषणा ConXS_BCR		BCR_P2V(0x0E000000)
#घोषणा ConXS_DCR		DCR_P2V(0x0F800000)
#घोषणा ConXS_IRCR		IRCR_P2V(0x0F800000)
#पूर्ण_अगर
#अन्यथा
/* क्रम whatever baseboard define function रेजिस्टरs */
अटल अंतरभूत अचिन्हित लघु CFSR_पढ़ोw(व्योम)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम BCR_ग_लिखोw(अचिन्हित लघु value)
अणु
	;
पूर्ण
अटल अंतरभूत व्योम DCR_ग_लिखोw(अचिन्हित लघु value)
अणु
	;
पूर्ण
अटल अंतरभूत व्योम IRCR_ग_लिखोw(अचिन्हित लघु value)
अणु
	;
पूर्ण
#पूर्ण_अगर	/* CONFIG_MACH_TRIZEPS_CONXS */

#घोषणा ConXS_CFSR_BVD_MASK	0x0003
#घोषणा ConXS_CFSR_BVD1		(1 << 0)
#घोषणा ConXS_CFSR_BVD2		(1 << 1)
#घोषणा ConXS_CFSR_VS_MASK	0x000C
#घोषणा ConXS_CFSR_VS1		(1 << 2)
#घोषणा ConXS_CFSR_VS2		(1 << 3)
#घोषणा ConXS_CFSR_VS_5V	(0x3 << 2)
#घोषणा ConXS_CFSR_VS_3V3	0x0

#घोषणा ConXS_BCR_S0_POW_EN0	(1 << 0)
#घोषणा ConXS_BCR_S0_POW_EN1	(1 << 1)
#घोषणा ConXS_BCR_L_DISP	(1 << 4)
#घोषणा ConXS_BCR_CF_BUF_EN	(1 << 5)
#घोषणा ConXS_BCR_CF_RESET	(1 << 7)
#घोषणा ConXS_BCR_S0_VCC_3V3	0x1
#घोषणा ConXS_BCR_S0_VCC_5V0	0x2
#घोषणा ConXS_BCR_S0_VPP_12V	0x4
#घोषणा ConXS_BCR_S0_VPP_3V3	0x8

#घोषणा ConXS_IRCR_MODE		(1 << 0)
#घोषणा ConXS_IRCR_SD		(1 << 1)

#पूर्ण_अगर /* _TRIPEPS4_H_ */
