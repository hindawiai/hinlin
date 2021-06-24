<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ISA_BRIDGE_H
#घोषणा __ISA_BRIDGE_H

#अगर_घोषित CONFIG_PPC64

बाह्य व्योम isa_bridge_find_early(काष्ठा pci_controller *hose);
बाह्य व्योम isa_bridge_init_non_pci(काष्ठा device_node *np);

अटल अंतरभूत पूर्णांक isa_vaddr_is_ioport(व्योम __iomem *address)
अणु
	/* Check अगर address hits the reserved legacy IO range */
	अचिन्हित दीर्घ ea = (अचिन्हित दीर्घ)address;
	वापस ea >= ISA_IO_BASE && ea < ISA_IO_END;
पूर्ण

#अन्यथा

अटल अंतरभूत पूर्णांक isa_vaddr_is_ioport(व्योम __iomem *address)
अणु
	/* No specअगरic ISA handling on ppc32 at this stage, it
	 * all goes through PCI
	 */
	वापस 0;
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* __ISA_BRIDGE_H */

