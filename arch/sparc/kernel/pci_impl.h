<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* pci_impl.h: Helper definitions क्रम PCI controller support.
 *
 * Copyright (C) 1999, 2007 David S. Miller (davem@davemloft.net)
 */

#अगर_अघोषित PCI_IMPL_H
#घोषणा PCI_IMPL_H

#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/pci.h>
#समावेश <linux/msi.h>
#समावेश <linux/of_device.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/iommu.h>

/* The असलtraction used here is that there are PCI controllers,
 * each with one (Sabre) or two (PSYCHO/SCHIZO) PCI bus modules
 * underneath.  Each PCI bus module uses an IOMMU (shared by both
 * PBMs of a controller, or per-PBM), and अगर a streaming buffer
 * is present, each PCI bus module has it's own. (ie. the IOMMU
 * might be shared between PBMs, the STC is never shared)
 * Furthermore, each PCI bus module controls it's own स्वतःnomous
 * PCI bus.
 */

#घोषणा PCI_STC_FLUSHFLAG_INIT(STC) \
	(*((STC)->strbuf_flushflag) = 0UL)
#घोषणा PCI_STC_FLUSHFLAG_SET(STC) \
	(*((STC)->strbuf_flushflag) != 0UL)

#अगर_घोषित CONFIG_PCI_MSI
काष्ठा pci_pbm_info;
काष्ठा sparc64_msiq_ops अणु
	पूर्णांक (*get_head)(काष्ठा pci_pbm_info *pbm, अचिन्हित दीर्घ msiqid,
			अचिन्हित दीर्घ *head);
	पूर्णांक (*dequeue_msi)(काष्ठा pci_pbm_info *pbm, अचिन्हित दीर्घ msiqid,
			   अचिन्हित दीर्घ *head, अचिन्हित दीर्घ *msi);
	पूर्णांक (*set_head)(काष्ठा pci_pbm_info *pbm, अचिन्हित दीर्घ msiqid,
			अचिन्हित दीर्घ head);
	पूर्णांक (*msi_setup)(काष्ठा pci_pbm_info *pbm, अचिन्हित दीर्घ msiqid,
			 अचिन्हित दीर्घ msi, पूर्णांक is_msi64);
	पूर्णांक (*msi_tearकरोwn)(काष्ठा pci_pbm_info *pbm, अचिन्हित दीर्घ msi);
	पूर्णांक (*msiq_alloc)(काष्ठा pci_pbm_info *pbm);
	व्योम (*msiq_मुक्त)(काष्ठा pci_pbm_info *pbm);
	पूर्णांक (*msiq_build_irq)(काष्ठा pci_pbm_info *pbm, अचिन्हित दीर्घ msiqid,
			      अचिन्हित दीर्घ devino);
पूर्ण;

व्योम sparc64_pbm_msi_init(काष्ठा pci_pbm_info *pbm,
			  स्थिर काष्ठा sparc64_msiq_ops *ops);

काष्ठा sparc64_msiq_cookie अणु
	काष्ठा pci_pbm_info *pbm;
	अचिन्हित दीर्घ msiqid;
पूर्ण;
#पूर्ण_अगर

काष्ठा pci_pbm_info अणु
	काष्ठा pci_pbm_info		*next;
	काष्ठा pci_pbm_info		*sibling;
	पूर्णांक				index;

	/* Physical address base of controller रेजिस्टरs. */
	अचिन्हित दीर्घ			controller_regs;

	/* Physical address base of PBM रेजिस्टरs. */
	अचिन्हित दीर्घ			pbm_regs;

	/* Physical address of DMA sync रेजिस्टर, अगर any.  */
	अचिन्हित दीर्घ			sync_reg;

	/* Opaque 32-bit प्रणाली bus Port ID. */
	u32				portid;

	/* Opaque 32-bit handle used क्रम hypervisor calls.  */
	u32				devhandle;

	/* Chipset version inक्रमmation. */
	पूर्णांक				chip_type;
#घोषणा PBM_CHIP_TYPE_SABRE		1
#घोषणा PBM_CHIP_TYPE_PSYCHO		2
#घोषणा PBM_CHIP_TYPE_SCHIZO		3
#घोषणा PBM_CHIP_TYPE_SCHIZO_PLUS	4
#घोषणा PBM_CHIP_TYPE_TOMATILLO		5
	पूर्णांक				chip_version;
	पूर्णांक				chip_revision;

	/* Name used क्रम top-level resources. */
	स्थिर अक्षर			*name;

	/* OBP specअगरic inक्रमmation. */
	काष्ठा platक्रमm_device		*op;
	u64				ino_biपंचांगap;

	/* PBM I/O and Memory space resources. */
	काष्ठा resource			io_space;
	काष्ठा resource			mem_space;
	काष्ठा resource			mem64_space;
	काष्ठा resource			busn;
	/* offset */
	resource_माप_प्रकार			io_offset;
	resource_माप_प्रकार			mem_offset;
	resource_माप_प्रकार			mem64_offset;

	/* Base of PCI Config space, can be per-PBM or shared. */
	अचिन्हित दीर्घ			config_space;

	/* This will be 12 on PCI-E controllers, 8 अन्यथाwhere.  */
	अचिन्हित दीर्घ			config_space_reg_bits;

	अचिन्हित दीर्घ			pci_afsr;
	अचिन्हित दीर्घ			pci_afar;
	अचिन्हित दीर्घ			pci_csr;

	/* State of 66MHz capabilities on this PBM. */
	पूर्णांक				is_66mhz_capable;
	पूर्णांक				all_devs_66mhz;

#अगर_घोषित CONFIG_PCI_MSI
	/* MSI info.  */
	u32				msiq_num;
	u32				msiq_ent_count;
	u32				msiq_first;
	u32				msiq_first_devino;
	u32				msiq_rotor;
	काष्ठा sparc64_msiq_cookie	*msiq_irq_cookies;
	u32				msi_num;
	u32				msi_first;
	u32				msi_data_mask;
	u32				msix_data_width;
	u64				msi32_start;
	u64				msi64_start;
	u32				msi32_len;
	u32				msi64_len;
	व्योम				*msi_queues;
	अचिन्हित दीर्घ			*msi_biपंचांगap;
	अचिन्हित पूर्णांक			*msi_irq_table;
	पूर्णांक (*setup_msi_irq)(अचिन्हित पूर्णांक *irq_p, काष्ठा pci_dev *pdev,
			     काष्ठा msi_desc *entry);
	व्योम (*tearकरोwn_msi_irq)(अचिन्हित पूर्णांक irq, काष्ठा pci_dev *pdev);
	स्थिर काष्ठा sparc64_msiq_ops	*msi_ops;
#पूर्ण_अगर /* !(CONFIG_PCI_MSI) */

	/* This PBM's streaming buffer. */
	काष्ठा strbuf			stc;

	/* IOMMU state, potentially shared by both PBM segments. */
	काष्ठा iommu			*iommu;

	/* Now things क्रम the actual PCI bus probes. */
	अचिन्हित पूर्णांक			pci_first_busno;
	अचिन्हित पूर्णांक			pci_last_busno;
	काष्ठा pci_bus			*pci_bus;
	काष्ठा pci_ops			*pci_ops;

	पूर्णांक				numa_node;
पूर्ण;

बाह्य काष्ठा pci_pbm_info *pci_pbm_root;

बाह्य पूर्णांक pci_num_pbms;

/* PCI bus scanning and fixup support. */
व्योम pci_get_pbm_props(काष्ठा pci_pbm_info *pbm);
काष्ठा pci_bus *pci_scan_one_pbm(काष्ठा pci_pbm_info *pbm,
				 काष्ठा device *parent);
व्योम pci_determine_mem_io_space(काष्ठा pci_pbm_info *pbm);

/* Error reporting support. */
व्योम pci_scan_क्रम_target_पात(काष्ठा pci_pbm_info *, काष्ठा pci_bus *);
व्योम pci_scan_क्रम_master_पात(काष्ठा pci_pbm_info *, काष्ठा pci_bus *);
व्योम pci_scan_क्रम_parity_error(काष्ठा pci_pbm_info *, काष्ठा pci_bus *);

/* Configuration space access. */
व्योम pci_config_पढ़ो8(u8 *addr, u8 *ret);
व्योम pci_config_पढ़ो16(u16 *addr, u16 *ret);
व्योम pci_config_पढ़ो32(u32 *addr, u32 *ret);
व्योम pci_config_ग_लिखो8(u8 *addr, u8 val);
व्योम pci_config_ग_लिखो16(u16 *addr, u16 val);
व्योम pci_config_ग_लिखो32(u32 *addr, u32 val);

बाह्य काष्ठा pci_ops sun4u_pci_ops;
बाह्य काष्ठा pci_ops sun4v_pci_ops;

बाह्य अस्थिर पूर्णांक pci_poke_in_progress;
बाह्य अस्थिर पूर्णांक pci_poke_cpu;
बाह्य अस्थिर पूर्णांक pci_poke_faulted;

#पूर्ण_अगर /* !(PCI_IMPL_H) */
