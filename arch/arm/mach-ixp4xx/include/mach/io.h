<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm/mach-ixp4xx/include/mach/पन.स
 *
 * Author: Deepak Saxena <dsaxena@plनिकासy.net>
 *
 * Copyright (C) 2002-2005  MontaVista Software, Inc.
 */

#अगर_अघोषित __ASM_ARM_ARCH_IO_H
#घोषणा __ASM_ARM_ARCH_IO_H

#समावेश <linux/bitops.h>

#समावेश <mach/hardware.h>

बाह्य पूर्णांक (*ixp4xx_pci_पढ़ो)(u32 addr, u32 cmd, u32* data);
बाह्य पूर्णांक ixp4xx_pci_ग_लिखो(u32 addr, u32 cmd, u32 data);


/*
 * IXP4xx provides two methods of accessing PCI memory space:
 *
 * 1) A direct mapped winकरोw from 0x48000000 to 0x4BFFFFFF (64MB).
 *    To access PCI via this space, we simply ioremap() the BAR
 *    पूर्णांकo the kernel and we can use the standard पढ़ो[bwl]/ग_लिखो[bwl]
 *    macros. This is the preffered method due to speed but it
 *    limits the प्रणाली to just 64MB of PCI memory. This can be
 *    problematic अगर using video cards and other memory-heavy tarमाला_लो.
 *
 * 2) If > 64MB of memory space is required, the IXP4xx can use indirect
 *    रेजिस्टरs to access the whole 4 GB of PCI memory space (as we करो below
 *    क्रम I/O transactions). This allows currently क्रम up to 1 GB (0x10000000
 *    to 0x4FFFFFFF) of memory on the bus. The disadvantage of this is that
 *    every PCI access requires three local रेजिस्टर accesses plus a spinlock,
 *    but in some हालs the perक्रमmance hit is acceptable. In addition, you
 *    cannot mmap() PCI devices in this हाल.
 */
#अगर_घोषित	CONFIG_IXP4XX_INसूचीECT_PCI

/*
 * In the हाल of using indirect PCI, we simply वापस the actual PCI
 * address and our पढ़ो/ग_लिखो implementation use that to drive the 
 * access रेजिस्टरs. If something outside of PCI is ioremap'd, we
 * fallback to the शेष.
 */

बाह्य अचिन्हित दीर्घ pcibios_min_mem;
अटल अंतरभूत पूर्णांक is_pci_memory(u32 addr)
अणु
	वापस (addr >= pcibios_min_mem) && (addr <= 0x4FFFFFFF);
पूर्ण

#घोषणा ग_लिखोb(v, p)			__indirect_ग_लिखोb(v, p)
#घोषणा ग_लिखोw(v, p)			__indirect_ग_लिखोw(v, p)
#घोषणा ग_लिखोl(v, p)			__indirect_ग_लिखोl(v, p)

#घोषणा ग_लिखोb_relaxed(v, p)		__indirect_ग_लिखोb(v, p)
#घोषणा ग_लिखोw_relaxed(v, p)		__indirect_ग_लिखोw(v, p)
#घोषणा ग_लिखोl_relaxed(v, p)		__indirect_ग_लिखोl(v, p)

#घोषणा ग_लिखोsb(p, v, l)		__indirect_ग_लिखोsb(p, v, l)
#घोषणा ग_लिखोsw(p, v, l)		__indirect_ग_लिखोsw(p, v, l)
#घोषणा ग_लिखोsl(p, v, l)		__indirect_ग_लिखोsl(p, v, l)

#घोषणा पढ़ोb(p)			__indirect_पढ़ोb(p)
#घोषणा पढ़ोw(p)			__indirect_पढ़ोw(p)
#घोषणा पढ़ोl(p)			__indirect_पढ़ोl(p)

#घोषणा पढ़ोb_relaxed(p)		__indirect_पढ़ोb(p)
#घोषणा पढ़ोw_relaxed(p)		__indirect_पढ़ोw(p)
#घोषणा पढ़ोl_relaxed(p)		__indirect_पढ़ोl(p)

#घोषणा पढ़ोsb(p, v, l)			__indirect_पढ़ोsb(p, v, l)
#घोषणा पढ़ोsw(p, v, l)			__indirect_पढ़ोsw(p, v, l)
#घोषणा पढ़ोsl(p, v, l)			__indirect_पढ़ोsl(p, v, l)

अटल अंतरभूत व्योम __indirect_ग_लिखोb(u8 value, अस्थिर व्योम __iomem *p)
अणु
	u32 addr = (u32)p;
	u32 n, byte_enables, data;

	अगर (!is_pci_memory(addr)) अणु
		__raw_ग_लिखोb(value, p);
		वापस;
	पूर्ण

	n = addr % 4;
	byte_enables = (0xf & ~BIT(n)) << IXP4XX_PCI_NP_CBE_BESL;
	data = value << (8*n);
	ixp4xx_pci_ग_लिखो(addr, byte_enables | NP_CMD_MEMWRITE, data);
पूर्ण

अटल अंतरभूत व्योम __indirect_ग_लिखोsb(अस्थिर व्योम __iomem *bus_addr,
				      स्थिर व्योम *p, पूर्णांक count)
अणु
	स्थिर u8 *vaddr = p;

	जबतक (count--)
		ग_लिखोb(*vaddr++, bus_addr);
पूर्ण

अटल अंतरभूत व्योम __indirect_ग_लिखोw(u16 value, अस्थिर व्योम __iomem *p)
अणु
	u32 addr = (u32)p;
	u32 n, byte_enables, data;

	अगर (!is_pci_memory(addr)) अणु
		__raw_ग_लिखोw(value, p);
		वापस;
	पूर्ण

	n = addr % 4;
	byte_enables = (0xf & ~(BIT(n) | BIT(n+1))) << IXP4XX_PCI_NP_CBE_BESL;
	data = value << (8*n);
	ixp4xx_pci_ग_लिखो(addr, byte_enables | NP_CMD_MEMWRITE, data);
पूर्ण

अटल अंतरभूत व्योम __indirect_ग_लिखोsw(अस्थिर व्योम __iomem *bus_addr,
				      स्थिर व्योम *p, पूर्णांक count)
अणु
	स्थिर u16 *vaddr = p;

	जबतक (count--)
		ग_लिखोw(*vaddr++, bus_addr);
पूर्ण

अटल अंतरभूत व्योम __indirect_ग_लिखोl(u32 value, अस्थिर व्योम __iomem *p)
अणु
	u32 addr = (__क्रमce u32)p;

	अगर (!is_pci_memory(addr)) अणु
		__raw_ग_लिखोl(value, p);
		वापस;
	पूर्ण

	ixp4xx_pci_ग_लिखो(addr, NP_CMD_MEMWRITE, value);
पूर्ण

अटल अंतरभूत व्योम __indirect_ग_लिखोsl(अस्थिर व्योम __iomem *bus_addr,
				      स्थिर व्योम *p, पूर्णांक count)
अणु
	स्थिर u32 *vaddr = p;
	जबतक (count--)
		ग_लिखोl(*vaddr++, bus_addr);
पूर्ण

अटल अंतरभूत u8 __indirect_पढ़ोb(स्थिर अस्थिर व्योम __iomem *p)
अणु
	u32 addr = (u32)p;
	u32 n, byte_enables, data;

	अगर (!is_pci_memory(addr))
		वापस __raw_पढ़ोb(p);

	n = addr % 4;
	byte_enables = (0xf & ~BIT(n)) << IXP4XX_PCI_NP_CBE_BESL;
	अगर (ixp4xx_pci_पढ़ो(addr, byte_enables | NP_CMD_MEMREAD, &data))
		वापस 0xff;

	वापस data >> (8*n);
पूर्ण

अटल अंतरभूत व्योम __indirect_पढ़ोsb(स्थिर अस्थिर व्योम __iomem *bus_addr,
				     व्योम *p, u32 count)
अणु
	u8 *vaddr = p;

	जबतक (count--)
		*vaddr++ = पढ़ोb(bus_addr);
पूर्ण

अटल अंतरभूत u16 __indirect_पढ़ोw(स्थिर अस्थिर व्योम __iomem *p)
अणु
	u32 addr = (u32)p;
	u32 n, byte_enables, data;

	अगर (!is_pci_memory(addr))
		वापस __raw_पढ़ोw(p);

	n = addr % 4;
	byte_enables = (0xf & ~(BIT(n) | BIT(n+1))) << IXP4XX_PCI_NP_CBE_BESL;
	अगर (ixp4xx_pci_पढ़ो(addr, byte_enables | NP_CMD_MEMREAD, &data))
		वापस 0xffff;

	वापस data>>(8*n);
पूर्ण

अटल अंतरभूत व्योम __indirect_पढ़ोsw(स्थिर अस्थिर व्योम __iomem *bus_addr,
				     व्योम *p, u32 count)
अणु
	u16 *vaddr = p;

	जबतक (count--)
		*vaddr++ = पढ़ोw(bus_addr);
पूर्ण

अटल अंतरभूत u32 __indirect_पढ़ोl(स्थिर अस्थिर व्योम __iomem *p)
अणु
	u32 addr = (__क्रमce u32)p;
	u32 data;

	अगर (!is_pci_memory(addr))
		वापस __raw_पढ़ोl(p);

	अगर (ixp4xx_pci_पढ़ो(addr, NP_CMD_MEMREAD, &data))
		वापस 0xffffffff;

	वापस data;
पूर्ण

अटल अंतरभूत व्योम __indirect_पढ़ोsl(स्थिर अस्थिर व्योम __iomem *bus_addr,
				     व्योम *p, u32 count)
अणु
	u32 *vaddr = p;

	जबतक (count--)
		*vaddr++ = पढ़ोl(bus_addr);
पूर्ण


/*
 * We can use the built-in functions b/c they end up calling ग_लिखोb/पढ़ोb
 */
#घोषणा स_रखो_io(c,v,l)		_स_रखो_io((c),(v),(l))
#घोषणा स_नकल_fromio(a,c,l)		_स_नकल_fromio((a),(c),(l))
#घोषणा स_नकल_toio(c,a,l)		_स_नकल_toio((c),(a),(l))

#पूर्ण_अगर /* CONFIG_IXP4XX_INसूचीECT_PCI */

#अगर_अघोषित CONFIG_PCI

#घोषणा	__io(v)		__typesafe_io(v)

#अन्यथा

/*
 * IXP4xx करोes not have a transparent cpu -> PCI I/O translation
 * winकरोw.  Instead, it has a set of रेजिस्टरs that must be tweaked
 * with the proper byte lanes, command types, and address क्रम the
 * transaction.  This means that we need to override the शेष
 * I/O functions.
 */

#घोषणा outb outb
अटल अंतरभूत व्योम outb(u8 value, u32 addr)
अणु
	u32 n, byte_enables, data;
	n = addr % 4;
	byte_enables = (0xf & ~BIT(n)) << IXP4XX_PCI_NP_CBE_BESL;
	data = value << (8*n);
	ixp4xx_pci_ग_लिखो(addr, byte_enables | NP_CMD_IOWRITE, data);
पूर्ण

#घोषणा outsb outsb
अटल अंतरभूत व्योम outsb(u32 io_addr, स्थिर व्योम *p, u32 count)
अणु
	स्थिर u8 *vaddr = p;

	जबतक (count--)
		outb(*vaddr++, io_addr);
पूर्ण

#घोषणा outw outw
अटल अंतरभूत व्योम outw(u16 value, u32 addr)
अणु
	u32 n, byte_enables, data;
	n = addr % 4;
	byte_enables = (0xf & ~(BIT(n) | BIT(n+1))) << IXP4XX_PCI_NP_CBE_BESL;
	data = value << (8*n);
	ixp4xx_pci_ग_लिखो(addr, byte_enables | NP_CMD_IOWRITE, data);
पूर्ण

#घोषणा outsw outsw
अटल अंतरभूत व्योम outsw(u32 io_addr, स्थिर व्योम *p, u32 count)
अणु
	स्थिर u16 *vaddr = p;
	जबतक (count--)
		outw(cpu_to_le16(*vaddr++), io_addr);
पूर्ण

#घोषणा outl outl
अटल अंतरभूत व्योम outl(u32 value, u32 addr)
अणु
	ixp4xx_pci_ग_लिखो(addr, NP_CMD_IOWRITE, value);
पूर्ण

#घोषणा outsl outsl
अटल अंतरभूत व्योम outsl(u32 io_addr, स्थिर व्योम *p, u32 count)
अणु
	स्थिर u32 *vaddr = p;
	जबतक (count--)
		outl(cpu_to_le32(*vaddr++), io_addr);
पूर्ण

#घोषणा inb inb
अटल अंतरभूत u8 inb(u32 addr)
अणु
	u32 n, byte_enables, data;
	n = addr % 4;
	byte_enables = (0xf & ~BIT(n)) << IXP4XX_PCI_NP_CBE_BESL;
	अगर (ixp4xx_pci_पढ़ो(addr, byte_enables | NP_CMD_IOREAD, &data))
		वापस 0xff;

	वापस data >> (8*n);
पूर्ण

#घोषणा insb insb
अटल अंतरभूत व्योम insb(u32 io_addr, व्योम *p, u32 count)
अणु
	u8 *vaddr = p;
	जबतक (count--)
		*vaddr++ = inb(io_addr);
पूर्ण

#घोषणा inw inw
अटल अंतरभूत u16 inw(u32 addr)
अणु
	u32 n, byte_enables, data;
	n = addr % 4;
	byte_enables = (0xf & ~(BIT(n) | BIT(n+1))) << IXP4XX_PCI_NP_CBE_BESL;
	अगर (ixp4xx_pci_पढ़ो(addr, byte_enables | NP_CMD_IOREAD, &data))
		वापस 0xffff;

	वापस data>>(8*n);
पूर्ण

#घोषणा insw insw
अटल अंतरभूत व्योम insw(u32 io_addr, व्योम *p, u32 count)
अणु
	u16 *vaddr = p;
	जबतक (count--)
		*vaddr++ = le16_to_cpu(inw(io_addr));
पूर्ण

#घोषणा inl inl
अटल अंतरभूत u32 inl(u32 addr)
अणु
	u32 data;
	अगर (ixp4xx_pci_पढ़ो(addr, NP_CMD_IOREAD, &data))
		वापस 0xffffffff;

	वापस data;
पूर्ण

#घोषणा insl insl
अटल अंतरभूत व्योम insl(u32 io_addr, व्योम *p, u32 count)
अणु
	u32 *vaddr = p;
	जबतक (count--)
		*vaddr++ = le32_to_cpu(inl(io_addr));
पूर्ण

#घोषणा PIO_OFFSET      0x10000UL
#घोषणा PIO_MASK        0x0ffffUL

#घोषणा	__is_io_address(p)	(((अचिन्हित दीर्घ)p >= PIO_OFFSET) && \
					((अचिन्हित दीर्घ)p <= (PIO_MASK + PIO_OFFSET)))

#घोषणा	ioपढ़ो8(p)			ioपढ़ो8(p)
अटल अंतरभूत u8 ioपढ़ो8(स्थिर व्योम __iomem *addr)
अणु
	अचिन्हित दीर्घ port = (अचिन्हित दीर्घ __क्रमce)addr;
	अगर (__is_io_address(port))
		वापस (अचिन्हित पूर्णांक)inb(port & PIO_MASK);
	अन्यथा
#अगर_अघोषित CONFIG_IXP4XX_INसूचीECT_PCI
		वापस (अचिन्हित पूर्णांक)__raw_पढ़ोb(addr);
#अन्यथा
		वापस (अचिन्हित पूर्णांक)__indirect_पढ़ोb(addr);
#पूर्ण_अगर
पूर्ण

#घोषणा	ioपढ़ो8_rep(p, v, c)		ioपढ़ो8_rep(p, v, c)
अटल अंतरभूत व्योम ioपढ़ो8_rep(स्थिर व्योम __iomem *addr, व्योम *vaddr, u32 count)
अणु
	अचिन्हित दीर्घ port = (अचिन्हित दीर्घ __क्रमce)addr;
	अगर (__is_io_address(port))
		insb(port & PIO_MASK, vaddr, count);
	अन्यथा
#अगर_अघोषित	CONFIG_IXP4XX_INसूचीECT_PCI
		__raw_पढ़ोsb(addr, vaddr, count);
#अन्यथा
		__indirect_पढ़ोsb(addr, vaddr, count);
#पूर्ण_अगर
पूर्ण

#घोषणा	ioपढ़ो16(p)			ioपढ़ो16(p)
अटल अंतरभूत u16 ioपढ़ो16(स्थिर व्योम __iomem *addr)
अणु
	अचिन्हित दीर्घ port = (अचिन्हित दीर्घ __क्रमce)addr;
	अगर (__is_io_address(port))
		वापस	(अचिन्हित पूर्णांक)inw(port & PIO_MASK);
	अन्यथा
#अगर_अघोषित CONFIG_IXP4XX_INसूचीECT_PCI
		वापस le16_to_cpu((__क्रमce __le16)__raw_पढ़ोw(addr));
#अन्यथा
		वापस (अचिन्हित पूर्णांक)__indirect_पढ़ोw(addr);
#पूर्ण_अगर
पूर्ण

#घोषणा	ioपढ़ो16_rep(p, v, c)		ioपढ़ो16_rep(p, v, c)
अटल अंतरभूत व्योम ioपढ़ो16_rep(स्थिर व्योम __iomem *addr, व्योम *vaddr,
				u32 count)
अणु
	अचिन्हित दीर्घ port = (अचिन्हित दीर्घ __क्रमce)addr;
	अगर (__is_io_address(port))
		insw(port & PIO_MASK, vaddr, count);
	अन्यथा
#अगर_अघोषित	CONFIG_IXP4XX_INसूचीECT_PCI
		__raw_पढ़ोsw(addr, vaddr, count);
#अन्यथा
		__indirect_पढ़ोsw(addr, vaddr, count);
#पूर्ण_अगर
पूर्ण

#घोषणा	ioपढ़ो32(p)			ioपढ़ो32(p)
अटल अंतरभूत u32 ioपढ़ो32(स्थिर व्योम __iomem *addr)
अणु
	अचिन्हित दीर्घ port = (अचिन्हित दीर्घ __क्रमce)addr;
	अगर (__is_io_address(port))
		वापस	(अचिन्हित पूर्णांक)inl(port & PIO_MASK);
	अन्यथा अणु
#अगर_अघोषित CONFIG_IXP4XX_INसूचीECT_PCI
		वापस le32_to_cpu((__क्रमce __le32)__raw_पढ़ोl(addr));
#अन्यथा
		वापस (अचिन्हित पूर्णांक)__indirect_पढ़ोl(addr);
#पूर्ण_अगर
	पूर्ण
पूर्ण

#घोषणा	ioपढ़ो32_rep(p, v, c)		ioपढ़ो32_rep(p, v, c)
अटल अंतरभूत व्योम ioपढ़ो32_rep(स्थिर व्योम __iomem *addr, व्योम *vaddr,
				u32 count)
अणु
	अचिन्हित दीर्घ port = (अचिन्हित दीर्घ __क्रमce)addr;
	अगर (__is_io_address(port))
		insl(port & PIO_MASK, vaddr, count);
	अन्यथा
#अगर_अघोषित	CONFIG_IXP4XX_INसूचीECT_PCI
		__raw_पढ़ोsl(addr, vaddr, count);
#अन्यथा
		__indirect_पढ़ोsl(addr, vaddr, count);
#पूर्ण_अगर
पूर्ण

#घोषणा	ioग_लिखो8(v, p)			ioग_लिखो8(v, p)
अटल अंतरभूत व्योम ioग_लिखो8(u8 value, व्योम __iomem *addr)
अणु
	अचिन्हित दीर्घ port = (अचिन्हित दीर्घ __क्रमce)addr;
	अगर (__is_io_address(port))
		outb(value, port & PIO_MASK);
	अन्यथा
#अगर_अघोषित CONFIG_IXP4XX_INसूचीECT_PCI
		__raw_ग_लिखोb(value, addr);
#अन्यथा
		__indirect_ग_लिखोb(value, addr);
#पूर्ण_अगर
पूर्ण

#घोषणा	ioग_लिखो8_rep(p, v, c)		ioग_लिखो8_rep(p, v, c)
अटल अंतरभूत व्योम ioग_लिखो8_rep(व्योम __iomem *addr, स्थिर व्योम *vaddr,
				u32 count)
अणु
	अचिन्हित दीर्घ port = (अचिन्हित दीर्घ __क्रमce)addr;
	अगर (__is_io_address(port))
		outsb(port & PIO_MASK, vaddr, count);
	अन्यथा
#अगर_अघोषित CONFIG_IXP4XX_INसूचीECT_PCI
		__raw_ग_लिखोsb(addr, vaddr, count);
#अन्यथा
		__indirect_ग_लिखोsb(addr, vaddr, count);
#पूर्ण_अगर
पूर्ण

#घोषणा	ioग_लिखो16(v, p)			ioग_लिखो16(v, p)
अटल अंतरभूत व्योम ioग_लिखो16(u16 value, व्योम __iomem *addr)
अणु
	अचिन्हित दीर्घ port = (अचिन्हित दीर्घ __क्रमce)addr;
	अगर (__is_io_address(port))
		outw(value, port & PIO_MASK);
	अन्यथा
#अगर_अघोषित CONFIG_IXP4XX_INसूचीECT_PCI
		__raw_ग_लिखोw(cpu_to_le16(value), addr);
#अन्यथा
		__indirect_ग_लिखोw(value, addr);
#पूर्ण_अगर
पूर्ण

#घोषणा	ioग_लिखो16_rep(p, v, c)		ioग_लिखो16_rep(p, v, c)
अटल अंतरभूत व्योम ioग_लिखो16_rep(व्योम __iomem *addr, स्थिर व्योम *vaddr,
				 u32 count)
अणु
	अचिन्हित दीर्घ port = (अचिन्हित दीर्घ __क्रमce)addr;
	अगर (__is_io_address(port))
		outsw(port & PIO_MASK, vaddr, count);
	अन्यथा
#अगर_अघोषित CONFIG_IXP4XX_INसूचीECT_PCI
		__raw_ग_लिखोsw(addr, vaddr, count);
#अन्यथा
		__indirect_ग_लिखोsw(addr, vaddr, count);
#पूर्ण_अगर
पूर्ण

#घोषणा	ioग_लिखो32(v, p)			ioग_लिखो32(v, p)
अटल अंतरभूत व्योम ioग_लिखो32(u32 value, व्योम __iomem *addr)
अणु
	अचिन्हित दीर्घ port = (अचिन्हित दीर्घ __क्रमce)addr;
	अगर (__is_io_address(port))
		outl(value, port & PIO_MASK);
	अन्यथा
#अगर_अघोषित CONFIG_IXP4XX_INसूचीECT_PCI
		__raw_ग_लिखोl((u32 __क्रमce)cpu_to_le32(value), addr);
#अन्यथा
		__indirect_ग_लिखोl(value, addr);
#पूर्ण_अगर
पूर्ण

#घोषणा	ioग_लिखो32_rep(p, v, c)		ioग_लिखो32_rep(p, v, c)
अटल अंतरभूत व्योम ioग_लिखो32_rep(व्योम __iomem *addr, स्थिर व्योम *vaddr,
				 u32 count)
अणु
	अचिन्हित दीर्घ port = (अचिन्हित दीर्घ __क्रमce)addr;
	अगर (__is_io_address(port))
		outsl(port & PIO_MASK, vaddr, count);
	अन्यथा
#अगर_अघोषित CONFIG_IXP4XX_INसूचीECT_PCI
		__raw_ग_लिखोsl(addr, vaddr, count);
#अन्यथा
		__indirect_ग_लिखोsl(addr, vaddr, count);
#पूर्ण_अगर
पूर्ण

#घोषणा ioport_map(port, nr) ioport_map(port, nr)
अटल अंतरभूत व्योम __iomem *ioport_map(अचिन्हित दीर्घ port, अचिन्हित पूर्णांक nr)
अणु
	वापस ((व्योम __iomem*)((port) + PIO_OFFSET));
पूर्ण
#घोषणा	ioport_unmap(addr) ioport_unmap(addr)
अटल अंतरभूत व्योम ioport_unmap(व्योम __iomem *addr)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_PCI */

#पूर्ण_अगर /* __ASM_ARM_ARCH_IO_H */
