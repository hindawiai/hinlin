<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 *  Copyright (C) 2010 John Crispin <john@phrozen.org>
 */

#अगर_अघोषित _LTQ_PCI_H__
#घोषणा _LTQ_PCI_H__

बाह्य __iomem व्योम *ltq_pci_mapped_cfg;
बाह्य पूर्णांक ltq_pci_पढ़ो_config_dword(काष्ठा pci_bus *bus,
	अचिन्हित पूर्णांक devfn, पूर्णांक where, पूर्णांक size, u32 *val);
बाह्य पूर्णांक ltq_pci_ग_लिखो_config_dword(काष्ठा pci_bus *bus,
	अचिन्हित पूर्णांक devfn, पूर्णांक where, पूर्णांक size, u32 val);

#पूर्ण_अगर
