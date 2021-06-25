<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Declarations क्रम maple-specअगरic code.
 *
 * Maple is the name of a PPC970 evaluation board.
 */
बाह्य पूर्णांक maple_set_rtc_समय(काष्ठा rtc_समय *पंचांग);
बाह्य व्योम maple_get_rtc_समय(काष्ठा rtc_समय *पंचांग);
बाह्य समय64_t maple_get_boot_समय(व्योम);
बाह्य व्योम maple_calibrate_decr(व्योम);
बाह्य व्योम maple_pci_init(व्योम);
बाह्य व्योम maple_pci_irq_fixup(काष्ठा pci_dev *dev);
बाह्य पूर्णांक maple_pci_get_legacy_ide_irq(काष्ठा pci_dev *dev, पूर्णांक channel);

बाह्य काष्ठा pci_controller_ops maple_pci_controller_ops;
