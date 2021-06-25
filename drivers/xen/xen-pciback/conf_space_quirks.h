<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * PCI Backend - Data काष्ठाures क्रम special overlays क्रम broken devices.
 *
 * Ryan Wilson <hap9@epoch.ncsc.mil>
 * Chris Bookholt <hap10@epoch.ncsc.mil>
 */

#अगर_अघोषित __XEN_PCIBACK_CONF_SPACE_QUIRKS_H__
#घोषणा __XEN_PCIBACK_CONF_SPACE_QUIRKS_H__

#समावेश <linux/pci.h>
#समावेश <linux/list.h>

काष्ठा xen_pcibk_config_quirk अणु
	काष्ठा list_head quirks_list;
	काष्ठा pci_device_id devid;
	काष्ठा pci_dev *pdev;
पूर्ण;

पूर्णांक xen_pcibk_config_quirks_add_field(काष्ठा pci_dev *dev, काष्ठा config_field
				    *field);

पूर्णांक xen_pcibk_config_quirks_हटाओ_field(काष्ठा pci_dev *dev, पूर्णांक reg);

पूर्णांक xen_pcibk_config_quirks_init(काष्ठा pci_dev *dev);

व्योम xen_pcibk_config_field_मुक्त(काष्ठा config_field *field);

पूर्णांक xen_pcibk_config_quirk_release(काष्ठा pci_dev *dev);

पूर्णांक xen_pcibk_field_is_dup(काष्ठा pci_dev *dev, अचिन्हित पूर्णांक reg);

#पूर्ण_अगर
