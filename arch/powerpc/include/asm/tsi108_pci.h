<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2007 IBM Corp
 */

#अगर_अघोषित _ASM_POWERPC_TSI108_PCI_H
#घोषणा _ASM_POWERPC_TSI108_PCI_H

#समावेश <यंत्र/tsi108.h>

/* Register definitions */
#घोषणा TSI108_PCI_P2O_BAR0 (TSI108_PCI_OFFSET + 0x10)
#घोषणा TSI108_PCI_P2O_BAR0_UPPER (TSI108_PCI_OFFSET + 0x14)
#घोषणा TSI108_PCI_P2O_BAR2 (TSI108_PCI_OFFSET + 0x18)
#घोषणा TSI108_PCI_P2O_BAR2_UPPER (TSI108_PCI_OFFSET + 0x1c)
#घोषणा TSI108_PCI_P2O_PAGE_SIZES (TSI108_PCI_OFFSET + 0x4c)
#घोषणा TSI108_PCI_PFAB_BAR0 (TSI108_PCI_OFFSET + 0x204)
#घोषणा TSI108_PCI_PFAB_BAR0_UPPER (TSI108_PCI_OFFSET + 0x208)
#घोषणा TSI108_PCI_PFAB_IO (TSI108_PCI_OFFSET + 0x20c)
#घोषणा TSI108_PCI_PFAB_IO_UPPER (TSI108_PCI_OFFSET + 0x210)
#घोषणा TSI108_PCI_PFAB_MEM32 (TSI108_PCI_OFFSET + 0x214)
#घोषणा TSI108_PCI_PFAB_PFM3 (TSI108_PCI_OFFSET + 0x220)
#घोषणा TSI108_PCI_PFAB_PFM4 (TSI108_PCI_OFFSET + 0x230)

बाह्य पूर्णांक tsi108_setup_pci(काष्ठा device_node *dev, u32 cfg_phys, पूर्णांक primary);
बाह्य व्योम tsi108_pci_पूर्णांक_init(काष्ठा device_node *node);
बाह्य व्योम tsi108_irq_cascade(काष्ठा irq_desc *desc);
बाह्य व्योम tsi108_clear_pci_cfg_error(व्योम);

#पूर्ण_अगर				/*  _ASM_POWERPC_TSI108_PCI_H */
