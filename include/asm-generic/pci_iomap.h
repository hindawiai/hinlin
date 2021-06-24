<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* Generic I/O port emulation.
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */
#अगर_अघोषित __ASM_GENERIC_PCI_IOMAP_H
#घोषणा __ASM_GENERIC_PCI_IOMAP_H

काष्ठा pci_dev;
#अगर_घोषित CONFIG_PCI
/* Create a भव mapping cookie क्रम a PCI BAR (memory or IO) */
बाह्य व्योम __iomem *pci_iomap(काष्ठा pci_dev *dev, पूर्णांक bar, अचिन्हित दीर्घ max);
बाह्य व्योम __iomem *pci_iomap_wc(काष्ठा pci_dev *dev, पूर्णांक bar, अचिन्हित दीर्घ max);
बाह्य व्योम __iomem *pci_iomap_range(काष्ठा pci_dev *dev, पूर्णांक bar,
				     अचिन्हित दीर्घ offset,
				     अचिन्हित दीर्घ maxlen);
बाह्य व्योम __iomem *pci_iomap_wc_range(काष्ठा pci_dev *dev, पूर्णांक bar,
					अचिन्हित दीर्घ offset,
					अचिन्हित दीर्घ maxlen);
/* Create a भव mapping cookie क्रम a port on a given PCI device.
 * Do not call this directly, it exists to make it easier क्रम architectures
 * to override */
#अगर_घोषित CONFIG_NO_GENERIC_PCI_IOPORT_MAP
बाह्य व्योम __iomem *__pci_ioport_map(काष्ठा pci_dev *dev, अचिन्हित दीर्घ port,
				      अचिन्हित पूर्णांक nr);
#अन्यथा
#घोषणा __pci_ioport_map(dev, port, nr) ioport_map((port), (nr))
#पूर्ण_अगर

#या_अगर defined(CONFIG_GENERIC_PCI_IOMAP)
अटल अंतरभूत व्योम __iomem *pci_iomap(काष्ठा pci_dev *dev, पूर्णांक bar, अचिन्हित दीर्घ max)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम __iomem *pci_iomap_wc(काष्ठा pci_dev *dev, पूर्णांक bar, अचिन्हित दीर्घ max)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम __iomem *pci_iomap_range(काष्ठा pci_dev *dev, पूर्णांक bar,
					    अचिन्हित दीर्घ offset,
					    अचिन्हित दीर्घ maxlen)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम __iomem *pci_iomap_wc_range(काष्ठा pci_dev *dev, पूर्णांक bar,
					       अचिन्हित दीर्घ offset,
					       अचिन्हित दीर्घ maxlen)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_GENERIC_IO_H */
