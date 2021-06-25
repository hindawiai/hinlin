<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2019-2020 Linaro Limited */

#अगर_अघोषित XHCI_PCI_H
#घोषणा XHCI_PCI_H

#अगर IS_ENABLED(CONFIG_USB_XHCI_PCI_RENESAS)
पूर्णांक renesas_xhci_check_request_fw(काष्ठा pci_dev *dev,
				  स्थिर काष्ठा pci_device_id *id);
व्योम renesas_xhci_pci_निकास(काष्ठा pci_dev *dev);

#अन्यथा
अटल पूर्णांक renesas_xhci_check_request_fw(काष्ठा pci_dev *dev,
					 स्थिर काष्ठा pci_device_id *id)
अणु
	वापस 0;
पूर्ण

अटल व्योम renesas_xhci_pci_निकास(काष्ठा pci_dev *dev) अणु पूर्ण;

#पूर्ण_अगर

काष्ठा xhci_driver_data अणु
	u64 quirks;
	स्थिर अक्षर *firmware;
पूर्ण;

#पूर्ण_अगर
