<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ppc64 "iomap" पूर्णांकerface implementation.
 *
 * (C) Copyright 2004 Linus Torvalds
 */
#समावेश <linux/pci.h>
#समावेश <linux/mm.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/isa-bridge.h>

व्योम __iomem *ioport_map(अचिन्हित दीर्घ port, अचिन्हित पूर्णांक len)
अणु
	वापस (व्योम __iomem *) (port + _IO_BASE);
पूर्ण
EXPORT_SYMBOL(ioport_map);

#अगर_घोषित CONFIG_PCI
व्योम pci_iounmap(काष्ठा pci_dev *dev, व्योम __iomem *addr)
अणु
	अगर (isa_vaddr_is_ioport(addr))
		वापस;
	अगर (pcibios_vaddr_is_ioport(addr))
		वापस;
	iounmap(addr);
पूर्ण

EXPORT_SYMBOL(pci_iounmap);
#पूर्ण_अगर /* CONFIG_PCI */
