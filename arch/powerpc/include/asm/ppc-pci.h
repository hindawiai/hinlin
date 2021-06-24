<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * c 2001 PPC 64 Team, IBM Corp
 */
#अगर_अघोषित _ASM_POWERPC_PPC_PCI_H
#घोषणा _ASM_POWERPC_PPC_PCI_H
#अगर_घोषित __KERNEL__

#अगर_घोषित CONFIG_PCI

#समावेश <linux/pci.h>
#समावेश <यंत्र/pci-bridge.h>

बाह्य अचिन्हित दीर्घ isa_io_base;

बाह्य काष्ठा list_head hose_list;

बाह्य काष्ठा pci_dev *isa_bridge_pcidev;	/* may be शून्य अगर no ISA bus */

/** Bus Unit ID macros; get low and hi 32-bits of the 64-bit BUID */
#घोषणा BUID_HI(buid) upper_32_bits(buid)
#घोषणा BUID_LO(buid) lower_32_bits(buid)

/* PCI device_node operations */
काष्ठा device_node;
काष्ठा pci_dn;

व्योम *pci_traverse_device_nodes(काष्ठा device_node *start,
				व्योम *(*fn)(काष्ठा device_node *, व्योम *),
				व्योम *data);
बाह्य व्योम pci_devs_phb_init_dynamic(काष्ठा pci_controller *phb);

/* From rtas_pci.h */
बाह्य व्योम init_pci_config_tokens (व्योम);
बाह्य अचिन्हित दीर्घ get_phb_buid (काष्ठा device_node *);
बाह्य पूर्णांक rtas_setup_phb(काष्ठा pci_controller *phb);

#अगर_घोषित CONFIG_EEH

व्योम eeh_addr_cache_insert_dev(काष्ठा pci_dev *dev);
व्योम eeh_addr_cache_rmv_dev(काष्ठा pci_dev *dev);
काष्ठा eeh_dev *eeh_addr_cache_get_dev(अचिन्हित दीर्घ addr);
व्योम eeh_slot_error_detail(काष्ठा eeh_pe *pe, पूर्णांक severity);
पूर्णांक eeh_pci_enable(काष्ठा eeh_pe *pe, पूर्णांक function);
पूर्णांक eeh_pe_reset_full(काष्ठा eeh_pe *pe, bool include_passed);
व्योम eeh_save_bars(काष्ठा eeh_dev *edev);
पूर्णांक rtas_ग_लिखो_config(काष्ठा pci_dn *, पूर्णांक where, पूर्णांक size, u32 val);
पूर्णांक rtas_पढ़ो_config(काष्ठा pci_dn *, पूर्णांक where, पूर्णांक size, u32 *val);
व्योम eeh_pe_state_mark(काष्ठा eeh_pe *pe, पूर्णांक state);
व्योम eeh_pe_mark_isolated(काष्ठा eeh_pe *pe);
व्योम eeh_pe_state_clear(काष्ठा eeh_pe *pe, पूर्णांक state, bool include_passed);
व्योम eeh_pe_state_mark_with_cfg(काष्ठा eeh_pe *pe, पूर्णांक state);
व्योम eeh_pe_dev_mode_mark(काष्ठा eeh_pe *pe, पूर्णांक mode);

व्योम eeh_sysfs_add_device(काष्ठा pci_dev *pdev);
व्योम eeh_sysfs_हटाओ_device(काष्ठा pci_dev *pdev);

अटल अंतरभूत स्थिर अक्षर *eeh_driver_name(काष्ठा pci_dev *pdev)
अणु
	वापस (pdev && pdev->driver) ? pdev->driver->name : "<null>";
पूर्ण

#पूर्ण_अगर /* CONFIG_EEH */

#घोषणा PCI_BUSNO(bdfn) ((bdfn >> 8) & 0xff)

#अन्यथा /* CONFIG_PCI */
अटल अंतरभूत व्योम init_pci_config_tokens(व्योम) अणु पूर्ण
#पूर्ण_अगर /* !CONFIG_PCI */

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_POWERPC_PPC_PCI_H */
