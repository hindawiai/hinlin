<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 *	Low-Level PCI Support क्रम SH7780 tarमाला_लो
 *
 *  Dustin McIntire (dustin@sensoria.com) (c) 2001
 *  Paul Mundt (lethal@linux-sh.org) (c) 2003
 */

#अगर_अघोषित _PCI_SH7780_H_
#घोषणा _PCI_SH7780_H_

/* SH7780 Control Registers */
#घोषणा	PCIECR			0xFE000008
#घोषणा PCIECR_ENBL		0x01

/* SH7780 Specअगरic Values */
#घोषणा SH7780_PCI_CONFIG_BASE	0xFD000000	/* Config space base addr */
#घोषणा SH7780_PCI_CONFIG_SIZE	0x01000000	/* Config space size */

#घोषणा SH7780_PCIREG_BASE	0xFE040000	/* PCI regs base address */

/* SH7780 PCI Config Registers */
#घोषणा SH7780_PCIIR		0x114		/* PCI Interrupt Register */
#घोषणा SH7780_PCIIMR		0x118		/* PCI Interrupt Mask Register */
#घोषणा SH7780_PCIAIR		0x11C		/* Error Address Register */
#घोषणा SH7780_PCICIR		0x120		/* Error Command/Data Register */
#घोषणा SH7780_PCIAINT		0x130		/* Arbiter Interrupt Register */
#घोषणा SH7780_PCIAINTM		0x134		/* Arbiter Int. Mask Register */
#घोषणा SH7780_PCIBMIR		0x138		/* Error Bus Master Register */
#घोषणा SH7780_PCIPAR		0x1C0		/* PIO Address Register */
#घोषणा SH7780_PCIPINT		0x1CC		/* Power Mgmnt Int. Register */
#घोषणा SH7780_PCIPINTM		0x1D0		/* Power Mgmnt Mask Register */

#घोषणा SH7780_PCIMBR(x)	(0x1E0 + ((x) * 8))
#घोषणा SH7780_PCIMBMR(x)	(0x1E4 + ((x) * 8))
#घोषणा SH7780_PCIIOBR		0x1F8
#घोषणा SH7780_PCIIOBMR		0x1FC
#घोषणा SH7780_PCICSCR0		0x210		/* Cache Snoop1 Cnt. Register */
#घोषणा SH7780_PCICSCR1		0x214		/* Cache Snoop2 Cnt. Register */
#घोषणा SH7780_PCICSAR0		0x218	/* Cache Snoop1 Addr. Register */
#घोषणा SH7780_PCICSAR1		0x21C	/* Cache Snoop2 Addr. Register */

#पूर्ण_अगर /* _PCI_SH7780_H_ */
