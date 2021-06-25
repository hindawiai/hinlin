<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/mach/pci.h
 *
 *  Copyright (C) 2000 Russell King
 */

#अगर_अघोषित __ASM_MACH_PCI_H
#घोषणा __ASM_MACH_PCI_H

#समावेश <linux/ioport.h>

काष्ठा pci_sys_data;
काष्ठा pci_ops;
काष्ठा pci_bus;
काष्ठा pci_host_bridge;
काष्ठा device;

काष्ठा hw_pci अणु
	काष्ठा pci_ops	*ops;
	पूर्णांक		nr_controllers;
	व्योम		**निजी_data;
	पूर्णांक		(*setup)(पूर्णांक nr, काष्ठा pci_sys_data *);
	पूर्णांक		(*scan)(पूर्णांक nr, काष्ठा pci_host_bridge *);
	व्योम		(*preinit)(व्योम);
	व्योम		(*postinit)(व्योम);
	u8		(*swizzle)(काष्ठा pci_dev *dev, u8 *pin);
	पूर्णांक		(*map_irq)(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin);
पूर्ण;

/*
 * Per-controller काष्ठाure
 */
काष्ठा pci_sys_data अणु
	काष्ठा list_head node;
	पूर्णांक		busnr;		/* primary bus number			*/
	u64		mem_offset;	/* bus->cpu memory mapping offset	*/
	अचिन्हित दीर्घ	io_offset;	/* bus->cpu IO mapping offset		*/
	काष्ठा pci_bus	*bus;		/* PCI bus				*/
	काष्ठा list_head resources;	/* root bus resources (apertures)       */
	काष्ठा resource io_res;
	अक्षर		io_res_name[12];
					/* Bridge swizzling			*/
	u8		(*swizzle)(काष्ठा pci_dev *, u8 *);
					/* IRQ mapping				*/
	पूर्णांक		(*map_irq)(स्थिर काष्ठा pci_dev *, u8, u8);
	व्योम		*निजी_data;	/* platक्रमm controller निजी data	*/
पूर्ण;

/*
 * Call this with your hw_pci काष्ठा to initialise the PCI प्रणाली.
 */
व्योम pci_common_init_dev(काष्ठा device *, काष्ठा hw_pci *);

/*
 * Compatibility wrapper क्रम older platक्रमms that करो not care about
 * passing the parent device.
 */
अटल अंतरभूत व्योम pci_common_init(काष्ठा hw_pci *hw)
अणु
	pci_common_init_dev(शून्य, hw);
पूर्ण

/*
 * Setup early fixed I/O mapping.
 */
#अगर defined(CONFIG_PCI)
बाह्य व्योम pci_map_io_early(अचिन्हित दीर्घ pfn);
#अन्यथा
अटल अंतरभूत व्योम pci_map_io_early(अचिन्हित दीर्घ pfn) अणुपूर्ण
#पूर्ण_अगर

/*
 * PCI controllers
 */
बाह्य काष्ठा pci_ops iop3xx_ops;
बाह्य पूर्णांक iop3xx_pci_setup(पूर्णांक nr, काष्ठा pci_sys_data *);
बाह्य व्योम iop3xx_pci_preinit(व्योम);
बाह्य व्योम iop3xx_pci_preinit_cond(व्योम);

बाह्य काष्ठा pci_ops dc21285_ops;
बाह्य पूर्णांक dc21285_setup(पूर्णांक nr, काष्ठा pci_sys_data *);
बाह्य व्योम dc21285_preinit(व्योम);
बाह्य व्योम dc21285_postinit(व्योम);

#पूर्ण_अगर /* __ASM_MACH_PCI_H */
