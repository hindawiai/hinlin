<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <यंत्र/pci-direct.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/pci_x86.h>

/* Direct PCI access. This is used क्रम PCI accesses in early boot beक्रमe
   the PCI subप्रणाली works. */

u32 पढ़ो_pci_config(u8 bus, u8 slot, u8 func, u8 offset)
अणु
	u32 v;
	outl(0x80000000 | (bus<<16) | (slot<<11) | (func<<8) | offset, 0xcf8);
	v = inl(0xcfc);
	वापस v;
पूर्ण

u8 पढ़ो_pci_config_byte(u8 bus, u8 slot, u8 func, u8 offset)
अणु
	u8 v;
	outl(0x80000000 | (bus<<16) | (slot<<11) | (func<<8) | offset, 0xcf8);
	v = inb(0xcfc + (offset&3));
	वापस v;
पूर्ण

u16 पढ़ो_pci_config_16(u8 bus, u8 slot, u8 func, u8 offset)
अणु
	u16 v;
	outl(0x80000000 | (bus<<16) | (slot<<11) | (func<<8) | offset, 0xcf8);
	v = inw(0xcfc + (offset&2));
	वापस v;
पूर्ण

व्योम ग_लिखो_pci_config(u8 bus, u8 slot, u8 func, u8 offset,
				    u32 val)
अणु
	outl(0x80000000 | (bus<<16) | (slot<<11) | (func<<8) | offset, 0xcf8);
	outl(val, 0xcfc);
पूर्ण

व्योम ग_लिखो_pci_config_byte(u8 bus, u8 slot, u8 func, u8 offset, u8 val)
अणु
	outl(0x80000000 | (bus<<16) | (slot<<11) | (func<<8) | offset, 0xcf8);
	outb(val, 0xcfc + (offset&3));
पूर्ण

व्योम ग_लिखो_pci_config_16(u8 bus, u8 slot, u8 func, u8 offset, u16 val)
अणु
	outl(0x80000000 | (bus<<16) | (slot<<11) | (func<<8) | offset, 0xcf8);
	outw(val, 0xcfc + (offset&2));
पूर्ण

पूर्णांक early_pci_allowed(व्योम)
अणु
	वापस (pci_probe & (PCI_PROBE_CONF1|PCI_PROBE_NOEARLY)) ==
			PCI_PROBE_CONF1;
पूर्ण

