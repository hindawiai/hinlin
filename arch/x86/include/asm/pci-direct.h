<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_PCI_सूचीECT_H
#घोषणा _ASM_X86_PCI_सूचीECT_H

#समावेश <linux/types.h>

/* Direct PCI access. This is used क्रम PCI accesses in early boot beक्रमe
   the PCI subप्रणाली works. */

बाह्य u32 पढ़ो_pci_config(u8 bus, u8 slot, u8 func, u8 offset);
बाह्य u8 पढ़ो_pci_config_byte(u8 bus, u8 slot, u8 func, u8 offset);
बाह्य u16 पढ़ो_pci_config_16(u8 bus, u8 slot, u8 func, u8 offset);
बाह्य व्योम ग_लिखो_pci_config(u8 bus, u8 slot, u8 func, u8 offset, u32 val);
बाह्य व्योम ग_लिखो_pci_config_byte(u8 bus, u8 slot, u8 func, u8 offset, u8 val);
बाह्य व्योम ग_लिखो_pci_config_16(u8 bus, u8 slot, u8 func, u8 offset, u16 val);

बाह्य पूर्णांक early_pci_allowed(व्योम);
#पूर्ण_अगर /* _ASM_X86_PCI_सूचीECT_H */
