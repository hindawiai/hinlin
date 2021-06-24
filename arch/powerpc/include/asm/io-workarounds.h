<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Support PCI IO workaround
 *
 * (C) Copyright 2007-2008 TOSHIBA CORPORATION
 */

#अगर_अघोषित _IO_WORKAROUNDS_H
#घोषणा _IO_WORKAROUNDS_H

#अगर_घोषित CONFIG_PPC_IO_WORKAROUNDS
#समावेश <linux/पन.स>
#समावेश <यंत्र/pci-bridge.h>

/* Bus info */
काष्ठा iowa_bus अणु
	काष्ठा pci_controller *phb;
	काष्ठा ppc_pci_io *ops;
	व्योम   *निजी;
पूर्ण;

व्योम iowa_रेजिस्टर_bus(काष्ठा pci_controller *, काष्ठा ppc_pci_io *,
		       पूर्णांक (*)(काष्ठा iowa_bus *, व्योम *), व्योम *);
काष्ठा iowa_bus *iowa_mem_find_bus(स्थिर PCI_IO_ADDR);
काष्ठा iowa_bus *iowa_pio_find_bus(अचिन्हित दीर्घ);

बाह्य काष्ठा ppc_pci_io spiderpci_ops;
बाह्य पूर्णांक spiderpci_iowa_init(काष्ठा iowa_bus *, व्योम *);

#घोषणा SPIDER_PCI_REG_BASE		0xd000
#घोषणा SPIDER_PCI_REG_SIZE		0x1000
#घोषणा SPIDER_PCI_VCI_CNTL_STAT	0x0110
#घोषणा SPIDER_PCI_DUMMY_READ		0x0810
#घोषणा SPIDER_PCI_DUMMY_READ_BASE	0x0814

#पूर्ण_अगर

#अगर defined(CONFIG_PPC_IO_WORKAROUNDS) && defined(CONFIG_PPC_INसूचीECT_MMIO)
बाह्य bool io_workaround_inited;

अटल अंतरभूत bool iowa_is_active(व्योम)
अणु
	वापस unlikely(io_workaround_inited);
पूर्ण
#अन्यथा
अटल अंतरभूत bool iowa_is_active(व्योम)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

व्योम __iomem *iowa_ioremap(phys_addr_t addr, अचिन्हित दीर्घ size,
			   pgprot_t prot, व्योम *caller);

#पूर्ण_अगर /* _IO_WORKAROUNDS_H */
