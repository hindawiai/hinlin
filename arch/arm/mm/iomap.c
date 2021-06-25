<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/arm/mm/iomap.c
 *
 * Map IO port and PCI memory spaces so that अणुपढ़ो,ग_लिखोपूर्ण[bwl] can
 * be used to access this memory.
 */
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/vga.h>

अचिन्हित दीर्घ vga_base;
EXPORT_SYMBOL(vga_base);

#अगर_घोषित __io
व्योम __iomem *ioport_map(अचिन्हित दीर्घ port, अचिन्हित पूर्णांक nr)
अणु
	वापस __io(port);
पूर्ण
EXPORT_SYMBOL(ioport_map);

व्योम ioport_unmap(व्योम __iomem *addr)
अणु
पूर्ण
EXPORT_SYMBOL(ioport_unmap);
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCI
अचिन्हित दीर्घ pcibios_min_io = 0x1000;
EXPORT_SYMBOL(pcibios_min_io);

अचिन्हित दीर्घ pcibios_min_mem = 0x01000000;
EXPORT_SYMBOL(pcibios_min_mem);

व्योम pci_iounmap(काष्ठा pci_dev *dev, व्योम __iomem *addr)
अणु
	अगर ((अचिन्हित दीर्घ)addr >= VMALLOC_START &&
	    (अचिन्हित दीर्घ)addr < VMALLOC_END)
		iounmap(addr);
पूर्ण
EXPORT_SYMBOL(pci_iounmap);
#पूर्ण_अगर
