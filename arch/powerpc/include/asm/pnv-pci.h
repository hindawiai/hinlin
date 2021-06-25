<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2014 IBM Corp.
 */

#अगर_अघोषित _ASM_PNV_PCI_H
#घोषणा _ASM_PNV_PCI_H

#समावेश <linux/pci.h>
#समावेश <linux/pci_hotplug.h>
#समावेश <linux/irq.h>
#समावेश <misc/cxl-base.h>
#समावेश <यंत्र/opal-api.h>

#घोषणा PCI_SLOT_ID_PREFIX	(1UL << 63)
#घोषणा PCI_SLOT_ID(phb_id, bdfn)	\
	(PCI_SLOT_ID_PREFIX | ((uपूर्णांक64_t)(bdfn) << 16) | (phb_id))
#घोषणा PCI_PHB_SLOT_ID(phb_id)		(phb_id)

बाह्य पूर्णांक pnv_pci_get_slot_id(काष्ठा device_node *np, uपूर्णांक64_t *id);
बाह्य पूर्णांक pnv_pci_get_device_tree(uपूर्णांक32_t phandle, व्योम *buf, uपूर्णांक64_t len);
बाह्य पूर्णांक pnv_pci_get_presence_state(uपूर्णांक64_t id, uपूर्णांक8_t *state);
बाह्य पूर्णांक pnv_pci_get_घातer_state(uपूर्णांक64_t id, uपूर्णांक8_t *state);
बाह्य पूर्णांक pnv_pci_set_घातer_state(uपूर्णांक64_t id, uपूर्णांक8_t state,
				   काष्ठा opal_msg *msg);

बाह्य पूर्णांक pnv_pci_set_tunnel_bar(काष्ठा pci_dev *dev, uपूर्णांक64_t addr,
				  पूर्णांक enable);
पूर्णांक pnv_phb_to_cxl_mode(काष्ठा pci_dev *dev, uपूर्णांक64_t mode);
पूर्णांक pnv_cxl_ioda_msi_setup(काष्ठा pci_dev *dev, अचिन्हित पूर्णांक hwirq,
			   अचिन्हित पूर्णांक virq);
पूर्णांक pnv_cxl_alloc_hwirqs(काष्ठा pci_dev *dev, पूर्णांक num);
व्योम pnv_cxl_release_hwirqs(काष्ठा pci_dev *dev, पूर्णांक hwirq, पूर्णांक num);
पूर्णांक pnv_cxl_get_irq_count(काष्ठा pci_dev *dev);
काष्ठा device_node *pnv_pci_get_phb_node(काष्ठा pci_dev *dev);
पूर्णांक64_t pnv_opal_pci_msi_eoi(काष्ठा irq_chip *chip, अचिन्हित पूर्णांक hw_irq);
bool is_pnv_opal_msi(काष्ठा irq_chip *chip);

#अगर_घोषित CONFIG_CXL_BASE
पूर्णांक pnv_cxl_alloc_hwirq_ranges(काष्ठा cxl_irq_ranges *irqs,
			       काष्ठा pci_dev *dev, पूर्णांक num);
व्योम pnv_cxl_release_hwirq_ranges(काष्ठा cxl_irq_ranges *irqs,
				  काष्ठा pci_dev *dev);
#पूर्ण_अगर

काष्ठा pnv_php_slot अणु
	काष्ठा hotplug_slot		slot;
	uपूर्णांक64_t			id;
	अक्षर				*name;
	पूर्णांक				slot_no;
	अचिन्हित पूर्णांक			flags;
#घोषणा PNV_PHP_FLAG_BROKEN_PDC		0x1
	काष्ठा kref			kref;
#घोषणा PNV_PHP_STATE_INITIALIZED	0
#घोषणा PNV_PHP_STATE_REGISTERED	1
#घोषणा PNV_PHP_STATE_POPULATED		2
#घोषणा PNV_PHP_STATE_OFFLINE		3
	पूर्णांक				state;
	पूर्णांक				irq;
	काष्ठा workqueue_काष्ठा		*wq;
	काष्ठा device_node		*dn;
	काष्ठा pci_dev			*pdev;
	काष्ठा pci_bus			*bus;
	bool				घातer_state_check;
	u8				attention_state;
	व्योम				*fdt;
	व्योम				*dt;
	काष्ठा of_changeset		ocs;
	काष्ठा pnv_php_slot		*parent;
	काष्ठा list_head		children;
	काष्ठा list_head		link;
पूर्ण;
बाह्य काष्ठा pnv_php_slot *pnv_php_find_slot(काष्ठा device_node *dn);
बाह्य पूर्णांक pnv_php_set_slot_घातer_state(काष्ठा hotplug_slot *slot,
					uपूर्णांक8_t state);

#पूर्ण_अगर
