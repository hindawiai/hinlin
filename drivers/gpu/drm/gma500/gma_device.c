<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/**************************************************************************
 * Copyright (c) 2011, Intel Corporation.
 * All Rights Reserved.
 *
 **************************************************************************/

#समावेश "psb_drv.h"
#समावेश "gma_device.h"

व्योम gma_get_core_freq(काष्ठा drm_device *dev)
अणु
	uपूर्णांक32_t घड़ी;
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	काष्ठा pci_dev *pci_root =
		pci_get_करोमुख्य_bus_and_slot(pci_करोमुख्य_nr(pdev->bus),
					    0, 0);
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;

	/*pci_ग_लिखो_config_dword(pci_root, 0xD4, 0x00C32004);*/
	/*pci_ग_लिखो_config_dword(pci_root, 0xD0, 0xE0033000);*/

	pci_ग_लिखो_config_dword(pci_root, 0xD0, 0xD0050300);
	pci_पढ़ो_config_dword(pci_root, 0xD4, &घड़ी);
	pci_dev_put(pci_root);

	चयन (घड़ी & 0x07) अणु
	हाल 0:
		dev_priv->core_freq = 100;
		अवरोध;
	हाल 1:
		dev_priv->core_freq = 133;
		अवरोध;
	हाल 2:
		dev_priv->core_freq = 150;
		अवरोध;
	हाल 3:
		dev_priv->core_freq = 178;
		अवरोध;
	हाल 4:
		dev_priv->core_freq = 200;
		अवरोध;
	हाल 5:
	हाल 6:
	हाल 7:
		dev_priv->core_freq = 266;
		अवरोध;
	शेष:
		dev_priv->core_freq = 0;
	पूर्ण
पूर्ण
