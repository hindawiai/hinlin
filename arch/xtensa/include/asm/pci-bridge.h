<शैली गुरु>
/*
 * include/यंत्र-xtensa/pci-bridge.h
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file "COPYING" in the मुख्य directory of
 * this archive क्रम more details.
 *
 * Copyright (C) 2005 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_PCI_BRIDGE_H
#घोषणा _XTENSA_PCI_BRIDGE_H

काष्ठा device_node;
काष्ठा pci_controller;

/*
 * pciस्वतः_bus_scan() क्रमागतerates the pci space.
 */

बाह्य पूर्णांक pciस्वतः_bus_scan(काष्ठा pci_controller *, पूर्णांक);

काष्ठा pci_space अणु
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ end;
	अचिन्हित दीर्घ base;
पूर्ण;

/*
 * Structure of a PCI controller (host bridge)
 */

काष्ठा pci_controller अणु
	पूर्णांक index;			/* used क्रम pci_controller_num */
	काष्ठा pci_controller *next;
	काष्ठा pci_bus *bus;
	व्योम *arch_data;

	पूर्णांक first_busno;
	पूर्णांक last_busno;

	काष्ठा pci_ops *ops;
	अस्थिर अचिन्हित पूर्णांक *cfg_addr;
	अस्थिर अचिन्हित अक्षर *cfg_data;

	/* Currently, we limit ourselves to 1 IO range and 3 mem
	 * ranges since the common pci_bus काष्ठाure can't handle more
	 */
	काष्ठा resource	io_resource;
	काष्ठा resource mem_resources[3];
	पूर्णांक mem_resource_count;

	/* Host bridge I/O and Memory space
	 * Used क्रम BAR placement algorithms
	 */
	काष्ठा pci_space io_space;
	काष्ठा pci_space mem_space;

	/* Return the पूर्णांकerrupt number fo a device. */
	पूर्णांक (*map_irq)(काष्ठा pci_dev*, u8, u8);

पूर्ण;

अटल अंतरभूत व्योम pcibios_init_resource(काष्ठा resource *res,
		अचिन्हित दीर्घ start, अचिन्हित दीर्घ end, पूर्णांक flags, अक्षर *name)
अणु
	res->start = start;
	res->end = end;
	res->flags = flags;
	res->name = name;
	res->parent = शून्य;
	res->sibling = शून्य;
	res->child = शून्य;
पूर्ण


/* These are used क्रम config access beक्रमe all the PCI probing has been करोne. */
पूर्णांक early_पढ़ो_config_byte(काष्ठा pci_controller*, पूर्णांक, पूर्णांक, पूर्णांक, u8*);
पूर्णांक early_पढ़ो_config_word(काष्ठा pci_controller*, पूर्णांक, पूर्णांक, पूर्णांक, u16*);
पूर्णांक early_पढ़ो_config_dword(काष्ठा pci_controller*, पूर्णांक, पूर्णांक, पूर्णांक, u32*);
पूर्णांक early_ग_लिखो_config_byte(काष्ठा pci_controller*, पूर्णांक, पूर्णांक, पूर्णांक, u8);
पूर्णांक early_ग_लिखो_config_word(काष्ठा pci_controller*, पूर्णांक, पूर्णांक, पूर्णांक, u16);
पूर्णांक early_ग_लिखो_config_dword(काष्ठा pci_controller*, पूर्णांक, पूर्णांक, पूर्णांक, u32);

#पूर्ण_अगर	/* _XTENSA_PCI_BRIDGE_H */
