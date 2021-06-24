<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PCI_SH4_H
#घोषणा __PCI_SH4_H

#अगर defined(CONFIG_CPU_SUBTYPE_SH7780) || \
    defined(CONFIG_CPU_SUBTYPE_SH7785) || \
    defined(CONFIG_CPU_SUBTYPE_SH7763)
#समावेश "pci-sh7780.h"
#अन्यथा
#समावेश "pci-sh7751.h"
#पूर्ण_अगर

#समावेश <यंत्र/पन.स>

#घोषणा SH4_PCICR		0x100		/* PCI Control Register */
  #घोषणा SH4_PCICR_PREFIX	  0xA5000000	/* CR prefix क्रम ग_लिखो */
  #घोषणा SH4_PCICR_FTO		  0x00000400	/* TRDY/IRDY Enable */
  #घोषणा SH4_PCICR_TRSB	  0x00000200	/* Target Read Single */
  #घोषणा SH4_PCICR_BSWP	  0x00000100	/* Target Byte Swap */
  #घोषणा SH4_PCICR_PLUP	  0x00000080	/* Enable PCI Pullup */
  #घोषणा SH4_PCICR_ARBM	  0x00000040	/* PCI Arbitration Mode */
  #घोषणा SH4_PCICR_MD		  0x00000030	/* MD9 and MD10 status */
  #घोषणा SH4_PCICR_SERR	  0x00000008	/* SERR output निश्चित */
  #घोषणा SH4_PCICR_INTA	  0x00000004	/* INTA output निश्चित */
  #घोषणा SH4_PCICR_PRST	  0x00000002	/* PCI Reset Assert */
  #घोषणा SH4_PCICR_CFIN	  0x00000001	/* Central Fun. Init Done */
#घोषणा SH4_PCILSR0		0x104		/* PCI Local Space Register0 */
#घोषणा SH4_PCILSR1		0x108		/* PCI Local Space Register1 */
#घोषणा SH4_PCILAR0		0x10C		/* PCI Local Addr Register1 */
#घोषणा SH4_PCILAR1		0x110		/* PCI Local Addr Register1 */
#घोषणा SH4_PCIINT		0x114		/* PCI Interrupt Register */
  #घोषणा SH4_PCIINT_MLCK	  0x00008000	/* Master Lock Error */
  #घोषणा SH4_PCIINT_TABT	  0x00004000	/* Target Abort Error */
  #घोषणा SH4_PCIINT_TRET	  0x00000200	/* Target Retry Error */
  #घोषणा SH4_PCIINT_MFDE	  0x00000100	/* Master Func. Disable Error */
  #घोषणा SH4_PCIINT_PRTY	  0x00000080	/* Address Parity Error */
  #घोषणा SH4_PCIINT_SERR	  0x00000040	/* SERR Detection Error */
  #घोषणा SH4_PCIINT_TWDP	  0x00000020	/* Tgt. Write Parity Error */
  #घोषणा SH4_PCIINT_TRDP	  0x00000010	/* Tgt. Read Parity Err Det. */
  #घोषणा SH4_PCIINT_MTABT	  0x00000008	/* Master-Tgt. Abort Error */
  #घोषणा SH4_PCIINT_MMABT	  0x00000004	/* Master-Master Abort Error */
  #घोषणा SH4_PCIINT_MWPD	  0x00000002	/* Master Write PERR Detect */
  #घोषणा SH4_PCIINT_MRPD	  0x00000001	/* Master Read PERR Detect */
#घोषणा SH4_PCIINTM		0x118		/* PCI Interrupt Mask */
  #घोषणा SH4_PCIINTM_TTADIM	  BIT(14)	/* Target-target पात पूर्णांकerrupt */
  #घोषणा SH4_PCIINTM_TMTOIM	  BIT(9)	/* Target retry समयout */
  #घोषणा SH4_PCIINTM_MDEIM	  BIT(8)	/* Master function disable error */
  #घोषणा SH4_PCIINTM_APEDIM	  BIT(7)	/* Address parity error detection */
  #घोषणा SH4_PCIINTM_SDIM	  BIT(6)	/* SERR detection */
  #घोषणा SH4_PCIINTM_DPEITWM	  BIT(5)	/* Data parity error क्रम target ग_लिखो */
  #घोषणा SH4_PCIINTM_PEDITRM	  BIT(4)	/* PERR detection क्रम target पढ़ो */
  #घोषणा SH4_PCIINTM_TADIMM	  BIT(3)	/* Target पात क्रम master */
  #घोषणा SH4_PCIINTM_MADIMM	  BIT(2)	/* Master पात क्रम master */
  #घोषणा SH4_PCIINTM_MWPDIM	  BIT(1)	/* Master ग_लिखो data parity error */
  #घोषणा SH4_PCIINTM_MRDPEIM	  BIT(0)	/* Master पढ़ो data parity error */
#घोषणा SH4_PCIALR		0x11C		/* Error Address Register */
#घोषणा SH4_PCICLR		0x120		/* Error Command/Data */
  #घोषणा SH4_PCICLR_MPIO	  0x80000000
  #घोषणा SH4_PCICLR_MDMA0	  0x40000000	/* DMA0 Transfer Error */
  #घोषणा SH4_PCICLR_MDMA1	  0x20000000	/* DMA1 Transfer Error */
  #घोषणा SH4_PCICLR_MDMA2	  0x10000000	/* DMA2 Transfer Error */
  #घोषणा SH4_PCICLR_MDMA3	  0x08000000	/* DMA3 Transfer Error */
  #घोषणा SH4_PCICLR_TGT	  0x04000000	/* Target Transfer Error */
  #घोषणा SH4_PCICLR_CMDL	  0x0000000F	/* PCI Command at Error */
#घोषणा SH4_PCIAINT		0x130		/* Arbiter Interrupt Register */
  #घोषणा SH4_PCIAINT_MBKN	  0x00002000	/* Master Broken Interrupt */
  #घोषणा SH4_PCIAINT_TBTO	  0x00001000	/* Target Bus Time Out */
  #घोषणा SH4_PCIAINT_MBTO	  0x00000800	/* Master Bus Time Out */
  #घोषणा SH4_PCIAINT_TABT	  0x00000008	/* Target Abort */
  #घोषणा SH4_PCIAINT_MABT	  0x00000004	/* Master Abort */
  #घोषणा SH4_PCIAINT_RDPE	  0x00000002	/* Read Data Parity Error */
  #घोषणा SH4_PCIAINT_WDPE	  0x00000001	/* Write Data Parity Error */
#घोषणा SH4_PCIAINTM            0x134		/* Arbiter Int. Mask Register */
#घोषणा SH4_PCIBMLR		0x138		/* Error Bus Master Register */
  #घोषणा SH4_PCIBMLR_REQ4	  0x00000010	/* REQ4 bus master at error */
  #घोषणा SH4_PCIBMLR_REQ3	  0x00000008	/* REQ3 bus master at error */
  #घोषणा SH4_PCIBMLR_REQ2	  0x00000004	/* REQ2 bus master at error */
  #घोषणा SH4_PCIBMLR_REQ1	  0x00000002	/* REQ1 bus master at error */
  #घोषणा SH4_PCIBMLR_REQ0	  0x00000001	/* REQ0 bus master at error */
#घोषणा SH4_PCIDMABT		0x140		/* DMA Transfer Arb. Register */
  #घोषणा SH4_PCIDMABT_RRBN	  0x00000001	/* DMA Arbitor Round-Robin */
#घोषणा SH4_PCIDPA0		0x180		/* DMA0 Transfer Addr. */
#घोषणा SH4_PCIDLA0		0x184		/* DMA0 Local Addr. */
#घोषणा SH4_PCIDTC0		0x188		/* DMA0 Transfer Cnt. */
#घोषणा SH4_PCIDCR0		0x18C		/* DMA0 Control Register */
  #घोषणा SH4_PCIDCR_ALGN	  0x00000600	/* DMA Alignment Mode */
  #घोषणा SH4_PCIDCR_MAST	  0x00000100	/* DMA Termination Type */
  #घोषणा SH4_PCIDCR_INTM	  0x00000080	/* DMA Interrupt Done Mask*/
  #घोषणा SH4_PCIDCR_INTS	  0x00000040	/* DMA Interrupt Done Status */
  #घोषणा SH4_PCIDCR_LHLD	  0x00000020	/* Local Address Control */
  #घोषणा SH4_PCIDCR_PHLD	  0x00000010	/* PCI Address Control*/
  #घोषणा SH4_PCIDCR_IOSEL	  0x00000008	/* PCI Address Space Type */
  #घोषणा SH4_PCIDCR_सूची	  0x00000004	/* DMA Transfer Direction */
  #घोषणा SH4_PCIDCR_STOP	  0x00000002	/* Force DMA Stop */
  #घोषणा SH4_PCIDCR_STRT	  0x00000001	/* DMA Start */
#घोषणा SH4_PCIDPA1		0x190		/* DMA1 Transfer Addr. */
#घोषणा SH4_PCIDLA1		0x194		/* DMA1 Local Addr. */
#घोषणा SH4_PCIDTC1		0x198		/* DMA1 Transfer Cnt. */
#घोषणा SH4_PCIDCR1		0x19C		/* DMA1 Control Register */
#घोषणा SH4_PCIDPA2		0x1A0		/* DMA2 Transfer Addr. */
#घोषणा SH4_PCIDLA2		0x1A4		/* DMA2 Local Addr. */
#घोषणा SH4_PCIDTC2		0x1A8		/* DMA2 Transfer Cnt. */
#घोषणा SH4_PCIDCR2		0x1AC		/* DMA2 Control Register */
#घोषणा SH4_PCIDPA3		0x1B0		/* DMA3 Transfer Addr. */
#घोषणा SH4_PCIDLA3		0x1B4		/* DMA3 Local Addr. */
#घोषणा SH4_PCIDTC3		0x1B8		/* DMA3 Transfer Cnt. */
#घोषणा SH4_PCIDCR3		0x1BC		/* DMA3 Control Register */
#घोषणा SH4_PCIPAR		0x1C0		/* PIO Address Register */
  #घोषणा SH4_PCIPAR_CFGEN	  0x80000000	/* Configuration Enable */
  #घोषणा SH4_PCIPAR_BUSNO	  0x00FF0000	/* Config. Bus Number */
  #घोषणा SH4_PCIPAR_DEVNO	  0x0000FF00	/* Config. Device Number */
  #घोषणा SH4_PCIPAR_REGAD	  0x000000FC	/* Register Address Number */
#घोषणा SH4_PCIMBR		0x1C4		/* Memory Base Address */
  #घोषणा SH4_PCIMBR_MASK	  0xFF000000	/* Memory Space Mask */
  #घोषणा SH4_PCIMBR_LOCK	  0x00000001	/* Lock Memory Space */
#घोषणा SH4_PCIIOBR		0x1C8		/* I/O Base Address Register */
  #घोषणा SH4_PCIIOBR_MASK	  0xFFFC0000	/* IO Space Mask */
  #घोषणा SH4_PCIIOBR_LOCK	  0x00000001	/* Lock IO Space */
#घोषणा SH4_PCIPINT		0x1CC		/* Power Mgmnt Int. Register */
  #घोषणा SH4_PCIPINT_D3	  0x00000002	/* D3 Pwr Mgmt. Interrupt */
  #घोषणा SH4_PCIPINT_D0	  0x00000001	/* D0 Pwr Mgmt. Interrupt */
#घोषणा SH4_PCIPINTM		0x1D0		/* Power Mgmnt Mask Register */
#घोषणा SH4_PCICLKR		0x1D4		/* Clock Ctrl. Register */
  #घोषणा SH4_PCICLKR_PCSTP	  0x00000002	/* PCI Clock Stop */
  #घोषणा SH4_PCICLKR_BCSTP	  0x00000001	/* BCLK Clock Stop */
/* For definitions of BCR, MCR see ... */
#घोषणा SH4_PCIBCR1		0x1E0		/* Memory BCR1 Register */
  #घोषणा SH4_PCIMBR0		SH4_PCIBCR1
#घोषणा SH4_PCIBCR2		0x1E4		/* Memory BCR2 Register */
  #घोषणा SH4_PCIMBMR0		SH4_PCIBCR2
#घोषणा SH4_PCIWCR1		0x1E8		/* Wait Control 1 Register */
#घोषणा SH4_PCIWCR2		0x1EC		/* Wait Control 2 Register */
#घोषणा SH4_PCIWCR3		0x1F0		/* Wait Control 3 Register */
  #घोषणा SH4_PCIMBR2		SH4_PCIWCR3
#घोषणा SH4_PCIMCR		0x1F4		/* Memory Control Register */
#घोषणा SH4_PCIBCR3		0x1f8		/* Memory BCR3 Register */
#घोषणा SH4_PCIPCTR             0x200		/* Port Control Register */
  #घोषणा SH4_PCIPCTR_P2EN	  0x000400000	/* Port 2 Enable */
  #घोषणा SH4_PCIPCTR_P1EN	  0x000200000	/* Port 1 Enable */
  #घोषणा SH4_PCIPCTR_P0EN	  0x000100000	/* Port 0 Enable */
  #घोषणा SH4_PCIPCTR_P2UP	  0x000000020	/* Port2 Pull Up Enable */
  #घोषणा SH4_PCIPCTR_P2IO	  0x000000010	/* Port2 Output Enable */
  #घोषणा SH4_PCIPCTR_P1UP	  0x000000008	/* Port1 Pull Up Enable */
  #घोषणा SH4_PCIPCTR_P1IO	  0x000000004	/* Port1 Output Enable */
  #घोषणा SH4_PCIPCTR_P0UP	  0x000000002	/* Port0 Pull Up Enable */
  #घोषणा SH4_PCIPCTR_P0IO	  0x000000001	/* Port0 Output Enable */
#घोषणा SH4_PCIPDTR		0x204		/* Port Data Register */
  #घोषणा SH4_PCIPDTR_PB5	  0x000000020	/* Port 5 Enable */
  #घोषणा SH4_PCIPDTR_PB4	  0x000000010	/* Port 4 Enable */
  #घोषणा SH4_PCIPDTR_PB3	  0x000000008	/* Port 3 Enable */
  #घोषणा SH4_PCIPDTR_PB2	  0x000000004	/* Port 2 Enable */
  #घोषणा SH4_PCIPDTR_PB1	  0x000000002	/* Port 1 Enable */
  #घोषणा SH4_PCIPDTR_PB0	  0x000000001	/* Port 0 Enable */
#घोषणा SH4_PCIPDR		0x220		/* Port IO Data Register */

/* arch/sh/kernel/drivers/pci/ops-sh4.c */
बाह्य काष्ठा pci_ops sh4_pci_ops;
पूर्णांक pci_fixup_pcic(काष्ठा pci_channel *chan);

काष्ठा sh4_pci_address_space अणु
	अचिन्हित दीर्घ base;
	अचिन्हित दीर्घ size;
पूर्ण;

काष्ठा sh4_pci_address_map अणु
	काष्ठा sh4_pci_address_space winकरोw0;
	काष्ठा sh4_pci_address_space winकरोw1;
पूर्ण;

अटल अंतरभूत व्योम pci_ग_लिखो_reg(काष्ठा pci_channel *chan,
				 अचिन्हित दीर्घ val, अचिन्हित दीर्घ reg)
अणु
	__raw_ग_लिखोl(val, chan->reg_base + reg);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pci_पढ़ो_reg(काष्ठा pci_channel *chan,
					 अचिन्हित दीर्घ reg)
अणु
	वापस __raw_पढ़ोl(chan->reg_base + reg);
पूर्ण

#पूर्ण_अगर /* __PCI_SH4_H */
