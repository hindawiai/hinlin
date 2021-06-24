<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCI Express Precision Time Measurement
 * Copyright (c) 2016, Intel Corporation.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश "../pci.h"

अटल व्योम pci_pपंचांग_info(काष्ठा pci_dev *dev)
अणु
	अक्षर घड़ी_desc[8];

	चयन (dev->pपंचांग_granularity) अणु
	हाल 0:
		snम_लिखो(घड़ी_desc, माप(घड़ी_desc), "unknown");
		अवरोध;
	हाल 255:
		snम_लिखो(घड़ी_desc, माप(घड़ी_desc), ">254ns");
		अवरोध;
	शेष:
		snम_लिखो(घड़ी_desc, माप(घड़ी_desc), "%uns",
			 dev->pपंचांग_granularity);
		अवरोध;
	पूर्ण
	pci_info(dev, "PTM enabled%s, %s granularity\n",
		 dev->pपंचांग_root ? " (root)" : "", घड़ी_desc);
पूर्ण

व्योम pci_disable_pपंचांग(काष्ठा pci_dev *dev)
अणु
	पूर्णांक pपंचांग;
	u16 ctrl;

	अगर (!pci_is_pcie(dev))
		वापस;

	pपंचांग = pci_find_ext_capability(dev, PCI_EXT_CAP_ID_PTM);
	अगर (!pपंचांग)
		वापस;

	pci_पढ़ो_config_word(dev, pपंचांग + PCI_PTM_CTRL, &ctrl);
	ctrl &= ~(PCI_PTM_CTRL_ENABLE | PCI_PTM_CTRL_ROOT);
	pci_ग_लिखो_config_word(dev, pपंचांग + PCI_PTM_CTRL, ctrl);
पूर्ण

व्योम pci_save_pपंचांग_state(काष्ठा pci_dev *dev)
अणु
	पूर्णांक pपंचांग;
	काष्ठा pci_cap_saved_state *save_state;
	u16 *cap;

	अगर (!pci_is_pcie(dev))
		वापस;

	pपंचांग = pci_find_ext_capability(dev, PCI_EXT_CAP_ID_PTM);
	अगर (!pपंचांग)
		वापस;

	save_state = pci_find_saved_ext_cap(dev, PCI_EXT_CAP_ID_PTM);
	अगर (!save_state) अणु
		pci_err(dev, "no suspend buffer for PTM\n");
		वापस;
	पूर्ण

	cap = (u16 *)&save_state->cap.data[0];
	pci_पढ़ो_config_word(dev, pपंचांग + PCI_PTM_CTRL, cap);
पूर्ण

व्योम pci_restore_pपंचांग_state(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_cap_saved_state *save_state;
	पूर्णांक pपंचांग;
	u16 *cap;

	अगर (!pci_is_pcie(dev))
		वापस;

	save_state = pci_find_saved_ext_cap(dev, PCI_EXT_CAP_ID_PTM);
	pपंचांग = pci_find_ext_capability(dev, PCI_EXT_CAP_ID_PTM);
	अगर (!save_state || !pपंचांग)
		वापस;

	cap = (u16 *)&save_state->cap.data[0];
	pci_ग_लिखो_config_word(dev, pपंचांग + PCI_PTM_CTRL, *cap);
पूर्ण

व्योम pci_pपंचांग_init(काष्ठा pci_dev *dev)
अणु
	पूर्णांक pos;
	u32 cap, ctrl;
	u8 local_घड़ी;
	काष्ठा pci_dev *ups;

	अगर (!pci_is_pcie(dev))
		वापस;

	/*
	 * Enable PTM only on पूर्णांकerior devices (root ports, चयन ports,
	 * etc.) on the assumption that it causes no link traffic until an
	 * endpoपूर्णांक enables it.
	 */
	अगर ((pci_pcie_type(dev) == PCI_EXP_TYPE_ENDPOINT ||
	     pci_pcie_type(dev) == PCI_EXP_TYPE_RC_END))
		वापस;

	/*
	 * Switch Downstream Ports are not permitted to have a PTM
	 * capability; their PTM behavior is controlled by the Upstream
	 * Port (PCIe r5.0, sec 7.9.16).
	 */
	ups = pci_upstream_bridge(dev);
	अगर (pci_pcie_type(dev) == PCI_EXP_TYPE_DOWNSTREAM &&
	    ups && ups->pपंचांग_enabled) अणु
		dev->pपंचांग_granularity = ups->pपंचांग_granularity;
		dev->pपंचांग_enabled = 1;
		वापस;
	पूर्ण

	pos = pci_find_ext_capability(dev, PCI_EXT_CAP_ID_PTM);
	अगर (!pos)
		वापस;

	pci_add_ext_cap_save_buffer(dev, PCI_EXT_CAP_ID_PTM, माप(u16));

	pci_पढ़ो_config_dword(dev, pos + PCI_PTM_CAP, &cap);
	local_घड़ी = (cap & PCI_PTM_GRANULARITY_MASK) >> 8;

	/*
	 * There's no point in enabling PTM unless it's enabled in the
	 * upstream device or this device can be a PTM Root itself.  Per
	 * the spec recommendation (PCIe r3.1, sec 7.32.3), select the
	 * furthest upstream Time Source as the PTM Root.
	 */
	अगर (ups && ups->pपंचांग_enabled) अणु
		ctrl = PCI_PTM_CTRL_ENABLE;
		अगर (ups->pपंचांग_granularity == 0)
			dev->pपंचांग_granularity = 0;
		अन्यथा अगर (ups->pपंचांग_granularity > local_घड़ी)
			dev->pपंचांग_granularity = ups->pपंचांग_granularity;
	पूर्ण अन्यथा अणु
		अगर (cap & PCI_PTM_CAP_ROOT) अणु
			ctrl = PCI_PTM_CTRL_ENABLE | PCI_PTM_CTRL_ROOT;
			dev->pपंचांग_root = 1;
			dev->pपंचांग_granularity = local_घड़ी;
		पूर्ण अन्यथा
			वापस;
	पूर्ण

	ctrl |= dev->pपंचांग_granularity << 8;
	pci_ग_लिखो_config_dword(dev, pos + PCI_PTM_CTRL, ctrl);
	dev->pपंचांग_enabled = 1;

	pci_pपंचांग_info(dev);
पूर्ण

पूर्णांक pci_enable_pपंचांग(काष्ठा pci_dev *dev, u8 *granularity)
अणु
	पूर्णांक pos;
	u32 cap, ctrl;
	काष्ठा pci_dev *ups;

	अगर (!pci_is_pcie(dev))
		वापस -EINVAL;

	pos = pci_find_ext_capability(dev, PCI_EXT_CAP_ID_PTM);
	अगर (!pos)
		वापस -EINVAL;

	pci_पढ़ो_config_dword(dev, pos + PCI_PTM_CAP, &cap);
	अगर (!(cap & PCI_PTM_CAP_REQ))
		वापस -EINVAL;

	/*
	 * For a PCIe Endpoपूर्णांक, PTM is only useful अगर the endpoपूर्णांक can
	 * issue PTM requests to upstream devices that have PTM enabled.
	 *
	 * For Root Complex Integrated Endpoपूर्णांकs, there is no upstream
	 * device, so there must be some implementation-specअगरic way to
	 * associate the endpoपूर्णांक with a समय source.
	 */
	अगर (pci_pcie_type(dev) == PCI_EXP_TYPE_ENDPOINT) अणु
		ups = pci_upstream_bridge(dev);
		अगर (!ups || !ups->pपंचांग_enabled)
			वापस -EINVAL;

		dev->pपंचांग_granularity = ups->pपंचांग_granularity;
	पूर्ण अन्यथा अगर (pci_pcie_type(dev) == PCI_EXP_TYPE_RC_END) अणु
		dev->pपंचांग_granularity = 0;
	पूर्ण अन्यथा
		वापस -EINVAL;

	ctrl = PCI_PTM_CTRL_ENABLE;
	ctrl |= dev->pपंचांग_granularity << 8;
	pci_ग_लिखो_config_dword(dev, pos + PCI_PTM_CTRL, ctrl);
	dev->pपंचांग_enabled = 1;

	pci_pपंचांग_info(dev);

	अगर (granularity)
		*granularity = dev->pपंचांग_granularity;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(pci_enable_pपंचांग);
