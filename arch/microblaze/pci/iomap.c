<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ppc64 "iomap" पूर्णांकerface implementation.
 *
 * (C) Copyright 2004 Linus Torvalds
 */
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/mm.h>
#समावेश <linux/export.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/pci-bridge.h>

व्योम pci_iounmap(काष्ठा pci_dev *dev, व्योम __iomem *addr)
अणु
	अगर (isa_vaddr_is_ioport(addr))
		वापस;
	अगर (pcibios_vaddr_is_ioport(addr))
		वापस;
	iounmap(addr);
पूर्ण
EXPORT_SYMBOL(pci_iounmap);
