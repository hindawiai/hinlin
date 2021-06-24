<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_USB_PCI_QUIRKS_H
#घोषणा __LINUX_USB_PCI_QUIRKS_H

#अगर_घोषित CONFIG_USB_PCI
व्योम uhci_reset_hc(काष्ठा pci_dev *pdev, अचिन्हित दीर्घ base);
पूर्णांक uhci_check_and_reset_hc(काष्ठा pci_dev *pdev, अचिन्हित दीर्घ base);
पूर्णांक usb_hcd_amd_remote_wakeup_quirk(काष्ठा pci_dev *pdev);
bool usb_amd_hang_symptom_quirk(व्योम);
bool usb_amd_prefetch_quirk(व्योम);
व्योम usb_amd_dev_put(व्योम);
bool usb_amd_quirk_pll_check(व्योम);
व्योम usb_amd_quirk_pll_disable(व्योम);
व्योम usb_amd_quirk_pll_enable(व्योम);
व्योम usb_यंत्रedia_modअगरyflowcontrol(काष्ठा pci_dev *pdev);
व्योम usb_enable_पूर्णांकel_xhci_ports(काष्ठा pci_dev *xhci_pdev);
व्योम usb_disable_xhci_ports(काष्ठा pci_dev *xhci_pdev);
व्योम sb800_prefetch(काष्ठा device *dev, पूर्णांक on);
bool usb_amd_pt_check_port(काष्ठा device *device, पूर्णांक port);
#अन्यथा
काष्ठा pci_dev;
अटल अंतरभूत व्योम usb_amd_quirk_pll_disable(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम usb_amd_quirk_pll_enable(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम usb_यंत्रedia_modअगरyflowcontrol(काष्ठा pci_dev *pdev) अणुपूर्ण
अटल अंतरभूत व्योम usb_amd_dev_put(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम usb_disable_xhci_ports(काष्ठा pci_dev *xhci_pdev) अणुपूर्ण
अटल अंतरभूत व्योम sb800_prefetch(काष्ठा device *dev, पूर्णांक on) अणुपूर्ण
अटल अंतरभूत bool usb_amd_pt_check_port(काष्ठा device *device, पूर्णांक port)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर  /* CONFIG_USB_PCI */

#पूर्ण_अगर  /*  __LINUX_USB_PCI_QUIRKS_H  */
