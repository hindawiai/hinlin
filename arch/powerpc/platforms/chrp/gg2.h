<शैली गुरु>
/*
 *  include/यंत्र-ppc/gg2.h -- VLSI VAS96011/12 `Golden Gate 2' रेजिस्टर definitions
 *
 *  Copyright (C) 1997 Geert Uytterhoeven
 *
 *  This file is based on the following करोcumentation:
 *
 *	The VAS96011/12 Chipset, Data Book, Edition 1.0
 *	VLSI Technology, Inc.
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of this archive
 *  क्रम more details.
 */

#अगर_अघोषित _ASMPPC_GG2_H
#घोषणा _ASMPPC_GG2_H

    /*
     *  Memory Map (CHRP mode)
     */

#घोषणा GG2_PCI_MEM_BASE	0xc0000000	/* Peripheral memory space */
#घोषणा GG2_ISA_MEM_BASE	0xf7000000	/* Peripheral memory alias */
#घोषणा GG2_ISA_IO_BASE		0xf8000000	/* Peripheral I/O space */
#घोषणा GG2_PCI_CONFIG_BASE	0xfec00000	/* PCI configuration space */
#घोषणा GG2_INT_ACK_SPECIAL	0xfec80000	/* Interrupt acknowledge and */
						/* special PCI cycles */
#घोषणा GG2_ROM_BASE0		0xff000000	/* ROM bank 0 */
#घोषणा GG2_ROM_BASE1		0xff800000	/* ROM bank 1 */


    /*
     *  GG2 specअगरic PCI Registers
     */

बाह्य व्योम __iomem *gg2_pci_config_base;	/* kernel भव address */

#घोषणा GG2_PCI_BUSNO		0x40	/* Bus number */
#घोषणा GG2_PCI_SUBBUSNO	0x41	/* Subordinate bus number */
#घोषणा GG2_PCI_DISCCTR		0x42	/* Disconnect counter */
#घोषणा GG2_PCI_PPC_CTRL	0x50	/* PowerPC पूर्णांकerface control रेजिस्टर */
#घोषणा GG2_PCI_ADDR_MAP	0x5c	/* Address map */
#घोषणा GG2_PCI_PCI_CTRL	0x60	/* PCI पूर्णांकerface control रेजिस्टर */
#घोषणा GG2_PCI_ROM_CTRL	0x70	/* ROM पूर्णांकerface control रेजिस्टर */
#घोषणा GG2_PCI_ROM_TIME	0x74	/* ROM timing */
#घोषणा GG2_PCI_CC_CTRL		0x80	/* Cache controller control रेजिस्टर */
#घोषणा GG2_PCI_DRAM_BANK0	0x90	/* Control रेजिस्टर क्रम DRAM bank #0 */
#घोषणा GG2_PCI_DRAM_BANK1	0x94	/* Control रेजिस्टर क्रम DRAM bank #1 */
#घोषणा GG2_PCI_DRAM_BANK2	0x98	/* Control रेजिस्टर क्रम DRAM bank #2 */
#घोषणा GG2_PCI_DRAM_BANK3	0x9c	/* Control रेजिस्टर क्रम DRAM bank #3 */
#घोषणा GG2_PCI_DRAM_BANK4	0xa0	/* Control रेजिस्टर क्रम DRAM bank #4 */
#घोषणा GG2_PCI_DRAM_BANK5	0xa4	/* Control रेजिस्टर क्रम DRAM bank #5 */
#घोषणा GG2_PCI_DRAM_TIME0	0xb0	/* Timing parameters set #0 */
#घोषणा GG2_PCI_DRAM_TIME1	0xb4	/* Timing parameters set #1 */
#घोषणा GG2_PCI_DRAM_CTRL	0xc0	/* DRAM control */
#घोषणा GG2_PCI_ERR_CTRL	0xd0	/* Error control रेजिस्टर */
#घोषणा GG2_PCI_ERR_STATUS	0xd4	/* Error status रेजिस्टर */
					/* Cleared when पढ़ो */

#पूर्ण_अगर /* _ASMPPC_GG2_H */
