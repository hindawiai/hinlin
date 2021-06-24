<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * यंत्र/leon_pci.h
 *
 * Copyright (C) 2011 Aeroflex Gaisler AB, Daniel Hellstrom
 */

#अगर_अघोषित _ASM_LEON_PCI_H_
#घोषणा _ASM_LEON_PCI_H_

/* PCI related definitions */
काष्ठा leon_pci_info अणु
	काष्ठा pci_ops *ops;
	काष्ठा resource	io_space;
	काष्ठा resource	mem_space;
	काष्ठा resource	busn;
	पूर्णांक (*map_irq)(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin);
पूर्ण;

व्योम leon_pci_init(काष्ठा platक्रमm_device *ofdev,
		   काष्ठा leon_pci_info *info);

#पूर्ण_अगर /* _ASM_LEON_PCI_H_ */
