<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright(c) 2008 - 2010 Realtek Corporation. All rights reserved.
 *
 * Based on the r8180 driver, which is:
 * Copyright 2004-2005 Andrea Merello <andrea.merello@gmail.com>, et al.
 *
 * Contact Inक्रमmation: wlanfae <wlanfae@realtek.com>
 */
#समावेश "rtl_pci.h"
#समावेश "rtl_core.h"

अटल व्योम _rtl92e_parse_pci_configuration(काष्ठा pci_dev *pdev,
					    काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = (काष्ठा r8192_priv *)rtllib_priv(dev);

	u8 पंचांगp;
	u16 LinkCtrlReg;

	pcie_capability_पढ़ो_word(priv->pdev, PCI_EXP_LNKCTL, &LinkCtrlReg);

	RT_TRACE(COMP_INIT, "Link Control Register =%x\n", LinkCtrlReg);

	pci_पढ़ो_config_byte(pdev, 0x98, &पंचांगp);
	पंचांगp |= BIT4;
	pci_ग_लिखो_config_byte(pdev, 0x98, पंचांगp);

	पंचांगp = 0x17;
	pci_ग_लिखो_config_byte(pdev, 0x70f, पंचांगp);
पूर्ण

bool rtl92e_check_adapter(काष्ठा pci_dev *pdev, काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = (काष्ठा r8192_priv *)rtllib_priv(dev);
	u16 DeviceID;
	u8  RevisionID;
	u16 IrqLine;

	DeviceID = pdev->device;
	RevisionID = pdev->revision;
	pci_पढ़ो_config_word(pdev, 0x3C, &IrqLine);

	priv->card_8192 = priv->ops->nic_type;

	अगर (DeviceID == 0x8192) अणु
		चयन (RevisionID) अणु
		हाल HAL_HW_PCI_REVISION_ID_8192PCIE:
			dev_info(&pdev->dev,
				 "Adapter(8192 PCI-E) is found - DeviceID=%x\n",
				 DeviceID);
			priv->card_8192 = NIC_8192E;
			अवरोध;
		हाल HAL_HW_PCI_REVISION_ID_8192SE:
			dev_info(&pdev->dev,
				 "Adapter(8192SE) is found - DeviceID=%x\n",
				 DeviceID);
			priv->card_8192 = NIC_8192SE;
			अवरोध;
		शेष:
			dev_info(&pdev->dev,
				 "UNKNOWN nic type(%4x:%4x)\n",
				 pdev->venकरोr, pdev->device);
			priv->card_8192 = NIC_UNKNOWN;
			वापस false;
		पूर्ण
	पूर्ण

	अगर (priv->ops->nic_type != priv->card_8192) अणु
		dev_info(&pdev->dev,
			 "Detect info(%x) and hardware info(%x) not match!\n",
			 priv->ops->nic_type, priv->card_8192);
		dev_info(&pdev->dev,
			 "Please select proper driver before install!!!!\n");
		वापस false;
	पूर्ण

	_rtl92e_parse_pci_configuration(pdev, dev);

	वापस true;
पूर्ण
