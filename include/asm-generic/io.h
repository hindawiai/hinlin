<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Generic I/O port emulation.
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */
#अगर_अघोषित __ASM_GENERIC_IO_H
#घोषणा __ASM_GENERIC_IO_H

#समावेश <यंत्र/page.h> /* I/O is all करोne through memory accesses */
#समावेश <linux/माला.स> /* क्रम स_रखो() and स_नकल() */
#समावेश <linux/types.h>

#अगर_घोषित CONFIG_GENERIC_IOMAP
#समावेश <यंत्र-generic/iomap.h>
#पूर्ण_अगर

#समावेश <यंत्र/mmiowb.h>
#समावेश <यंत्र-generic/pci_iomap.h>

#अगर_अघोषित __io_br
#घोषणा __io_br()      barrier()
#पूर्ण_अगर

/* prevent prefetching of coherent DMA data ahead of a dma-complete */
#अगर_अघोषित __io_ar
#अगर_घोषित rmb
#घोषणा __io_ar(v)      rmb()
#अन्यथा
#घोषणा __io_ar(v)      barrier()
#पूर्ण_अगर
#पूर्ण_अगर

/* flush ग_लिखोs to coherent DMA data beक्रमe possibly triggering a DMA पढ़ो */
#अगर_अघोषित __io_bw
#अगर_घोषित wmb
#घोषणा __io_bw()      wmb()
#अन्यथा
#घोषणा __io_bw()      barrier()
#पूर्ण_अगर
#पूर्ण_अगर

/* serialize device access against a spin_unlock, usually handled there. */
#अगर_अघोषित __io_aw
#घोषणा __io_aw()      mmiowb_set_pending()
#पूर्ण_अगर

#अगर_अघोषित __io_pbw
#घोषणा __io_pbw()     __io_bw()
#पूर्ण_अगर

#अगर_अघोषित __io_paw
#घोषणा __io_paw()     __io_aw()
#पूर्ण_अगर

#अगर_अघोषित __io_pbr
#घोषणा __io_pbr()     __io_br()
#पूर्ण_अगर

#अगर_अघोषित __io_par
#घोषणा __io_par(v)     __io_ar(v)
#पूर्ण_अगर


/*
 * __raw_अणुपढ़ो,ग_लिखोपूर्णअणुb,w,l,qपूर्ण() access memory in native endianness.
 *
 * On some architectures memory mapped IO needs to be accessed dअगरferently.
 * On the simple architectures, we just पढ़ो/ग_लिखो the memory location
 * directly.
 */

#अगर_अघोषित __raw_पढ़ोb
#घोषणा __raw_पढ़ोb __raw_पढ़ोb
अटल अंतरभूत u8 __raw_पढ़ोb(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस *(स्थिर अस्थिर u8 __क्रमce *)addr;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __raw_पढ़ोw
#घोषणा __raw_पढ़ोw __raw_पढ़ोw
अटल अंतरभूत u16 __raw_पढ़ोw(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस *(स्थिर अस्थिर u16 __क्रमce *)addr;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __raw_पढ़ोl
#घोषणा __raw_पढ़ोl __raw_पढ़ोl
अटल अंतरभूत u32 __raw_पढ़ोl(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस *(स्थिर अस्थिर u32 __क्रमce *)addr;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_64BIT
#अगर_अघोषित __raw_पढ़ोq
#घोषणा __raw_पढ़ोq __raw_पढ़ोq
अटल अंतरभूत u64 __raw_पढ़ोq(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस *(स्थिर अस्थिर u64 __क्रमce *)addr;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_64BIT */

#अगर_अघोषित __raw_ग_लिखोb
#घोषणा __raw_ग_लिखोb __raw_ग_लिखोb
अटल अंतरभूत व्योम __raw_ग_लिखोb(u8 value, अस्थिर व्योम __iomem *addr)
अणु
	*(अस्थिर u8 __क्रमce *)addr = value;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __raw_ग_लिखोw
#घोषणा __raw_ग_लिखोw __raw_ग_लिखोw
अटल अंतरभूत व्योम __raw_ग_लिखोw(u16 value, अस्थिर व्योम __iomem *addr)
अणु
	*(अस्थिर u16 __क्रमce *)addr = value;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __raw_ग_लिखोl
#घोषणा __raw_ग_लिखोl __raw_ग_लिखोl
अटल अंतरभूत व्योम __raw_ग_लिखोl(u32 value, अस्थिर व्योम __iomem *addr)
अणु
	*(अस्थिर u32 __क्रमce *)addr = value;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_64BIT
#अगर_अघोषित __raw_ग_लिखोq
#घोषणा __raw_ग_लिखोq __raw_ग_लिखोq
अटल अंतरभूत व्योम __raw_ग_लिखोq(u64 value, अस्थिर व्योम __iomem *addr)
अणु
	*(अस्थिर u64 __क्रमce *)addr = value;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_64BIT */

/*
 * अणुपढ़ो,ग_लिखोपूर्णअणुb,w,l,qपूर्ण() access little endian memory and वापस result in
 * native endianness.
 */

#अगर_अघोषित पढ़ोb
#घोषणा पढ़ोb पढ़ोb
अटल अंतरभूत u8 पढ़ोb(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u8 val;

	__io_br();
	val = __raw_पढ़ोb(addr);
	__io_ar(val);
	वापस val;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित पढ़ोw
#घोषणा पढ़ोw पढ़ोw
अटल अंतरभूत u16 पढ़ोw(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u16 val;

	__io_br();
	val = __le16_to_cpu((__le16 __क्रमce)__raw_पढ़ोw(addr));
	__io_ar(val);
	वापस val;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित पढ़ोl
#घोषणा पढ़ोl पढ़ोl
अटल अंतरभूत u32 पढ़ोl(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u32 val;

	__io_br();
	val = __le32_to_cpu((__le32 __क्रमce)__raw_पढ़ोl(addr));
	__io_ar(val);
	वापस val;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_64BIT
#अगर_अघोषित पढ़ोq
#घोषणा पढ़ोq पढ़ोq
अटल अंतरभूत u64 पढ़ोq(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u64 val;

	__io_br();
	val = __le64_to_cpu(__raw_पढ़ोq(addr));
	__io_ar(val);
	वापस val;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_64BIT */

#अगर_अघोषित ग_लिखोb
#घोषणा ग_लिखोb ग_लिखोb
अटल अंतरभूत व्योम ग_लिखोb(u8 value, अस्थिर व्योम __iomem *addr)
अणु
	__io_bw();
	__raw_ग_लिखोb(value, addr);
	__io_aw();
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित ग_लिखोw
#घोषणा ग_लिखोw ग_लिखोw
अटल अंतरभूत व्योम ग_लिखोw(u16 value, अस्थिर व्योम __iomem *addr)
अणु
	__io_bw();
	__raw_ग_लिखोw((u16 __क्रमce)cpu_to_le16(value), addr);
	__io_aw();
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित ग_लिखोl
#घोषणा ग_लिखोl ग_लिखोl
अटल अंतरभूत व्योम ग_लिखोl(u32 value, अस्थिर व्योम __iomem *addr)
अणु
	__io_bw();
	__raw_ग_लिखोl((u32 __क्रमce)__cpu_to_le32(value), addr);
	__io_aw();
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_64BIT
#अगर_अघोषित ग_लिखोq
#घोषणा ग_लिखोq ग_लिखोq
अटल अंतरभूत व्योम ग_लिखोq(u64 value, अस्थिर व्योम __iomem *addr)
अणु
	__io_bw();
	__raw_ग_लिखोq(__cpu_to_le64(value), addr);
	__io_aw();
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_64BIT */

/*
 * अणुपढ़ो,ग_लिखोपूर्णअणुb,w,l,qपूर्ण_relaxed() are like the regular version, but
 * are not guaranteed to provide ordering against spinlocks or memory
 * accesses.
 */
#अगर_अघोषित पढ़ोb_relaxed
#घोषणा पढ़ोb_relaxed पढ़ोb_relaxed
अटल अंतरभूत u8 पढ़ोb_relaxed(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस __raw_पढ़ोb(addr);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित पढ़ोw_relaxed
#घोषणा पढ़ोw_relaxed पढ़ोw_relaxed
अटल अंतरभूत u16 पढ़ोw_relaxed(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस __le16_to_cpu(__raw_पढ़ोw(addr));
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित पढ़ोl_relaxed
#घोषणा पढ़ोl_relaxed पढ़ोl_relaxed
अटल अंतरभूत u32 पढ़ोl_relaxed(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस __le32_to_cpu(__raw_पढ़ोl(addr));
पूर्ण
#पूर्ण_अगर

#अगर defined(पढ़ोq) && !defined(पढ़ोq_relaxed)
#घोषणा पढ़ोq_relaxed पढ़ोq_relaxed
अटल अंतरभूत u64 पढ़ोq_relaxed(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस __le64_to_cpu(__raw_पढ़ोq(addr));
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित ग_लिखोb_relaxed
#घोषणा ग_लिखोb_relaxed ग_लिखोb_relaxed
अटल अंतरभूत व्योम ग_लिखोb_relaxed(u8 value, अस्थिर व्योम __iomem *addr)
अणु
	__raw_ग_लिखोb(value, addr);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित ग_लिखोw_relaxed
#घोषणा ग_लिखोw_relaxed ग_लिखोw_relaxed
अटल अंतरभूत व्योम ग_लिखोw_relaxed(u16 value, अस्थिर व्योम __iomem *addr)
अणु
	__raw_ग_लिखोw(cpu_to_le16(value), addr);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित ग_लिखोl_relaxed
#घोषणा ग_लिखोl_relaxed ग_लिखोl_relaxed
अटल अंतरभूत व्योम ग_लिखोl_relaxed(u32 value, अस्थिर व्योम __iomem *addr)
अणु
	__raw_ग_लिखोl(__cpu_to_le32(value), addr);
पूर्ण
#पूर्ण_अगर

#अगर defined(ग_लिखोq) && !defined(ग_लिखोq_relaxed)
#घोषणा ग_लिखोq_relaxed ग_लिखोq_relaxed
अटल अंतरभूत व्योम ग_लिखोq_relaxed(u64 value, अस्थिर व्योम __iomem *addr)
अणु
	__raw_ग_लिखोq(__cpu_to_le64(value), addr);
पूर्ण
#पूर्ण_अगर

/*
 * अणुपढ़ो,ग_लिखोपूर्णsअणुb,w,l,qपूर्ण() repeatedly access the same memory address in
 * native endianness in 8-, 16-, 32- or 64-bit chunks (@count बार).
 */
#अगर_अघोषित पढ़ोsb
#घोषणा पढ़ोsb पढ़ोsb
अटल अंतरभूत व्योम पढ़ोsb(स्थिर अस्थिर व्योम __iomem *addr, व्योम *buffer,
			  अचिन्हित पूर्णांक count)
अणु
	अगर (count) अणु
		u8 *buf = buffer;

		करो अणु
			u8 x = __raw_पढ़ोb(addr);
			*buf++ = x;
		पूर्ण जबतक (--count);
	पूर्ण
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित पढ़ोsw
#घोषणा पढ़ोsw पढ़ोsw
अटल अंतरभूत व्योम पढ़ोsw(स्थिर अस्थिर व्योम __iomem *addr, व्योम *buffer,
			  अचिन्हित पूर्णांक count)
अणु
	अगर (count) अणु
		u16 *buf = buffer;

		करो अणु
			u16 x = __raw_पढ़ोw(addr);
			*buf++ = x;
		पूर्ण जबतक (--count);
	पूर्ण
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित पढ़ोsl
#घोषणा पढ़ोsl पढ़ोsl
अटल अंतरभूत व्योम पढ़ोsl(स्थिर अस्थिर व्योम __iomem *addr, व्योम *buffer,
			  अचिन्हित पूर्णांक count)
अणु
	अगर (count) अणु
		u32 *buf = buffer;

		करो अणु
			u32 x = __raw_पढ़ोl(addr);
			*buf++ = x;
		पूर्ण जबतक (--count);
	पूर्ण
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_64BIT
#अगर_अघोषित पढ़ोsq
#घोषणा पढ़ोsq पढ़ोsq
अटल अंतरभूत व्योम पढ़ोsq(स्थिर अस्थिर व्योम __iomem *addr, व्योम *buffer,
			  अचिन्हित पूर्णांक count)
अणु
	अगर (count) अणु
		u64 *buf = buffer;

		करो अणु
			u64 x = __raw_पढ़ोq(addr);
			*buf++ = x;
		पूर्ण जबतक (--count);
	पूर्ण
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_64BIT */

#अगर_अघोषित ग_लिखोsb
#घोषणा ग_लिखोsb ग_लिखोsb
अटल अंतरभूत व्योम ग_लिखोsb(अस्थिर व्योम __iomem *addr, स्थिर व्योम *buffer,
			   अचिन्हित पूर्णांक count)
अणु
	अगर (count) अणु
		स्थिर u8 *buf = buffer;

		करो अणु
			__raw_ग_लिखोb(*buf++, addr);
		पूर्ण जबतक (--count);
	पूर्ण
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित ग_लिखोsw
#घोषणा ग_लिखोsw ग_लिखोsw
अटल अंतरभूत व्योम ग_लिखोsw(अस्थिर व्योम __iomem *addr, स्थिर व्योम *buffer,
			   अचिन्हित पूर्णांक count)
अणु
	अगर (count) अणु
		स्थिर u16 *buf = buffer;

		करो अणु
			__raw_ग_लिखोw(*buf++, addr);
		पूर्ण जबतक (--count);
	पूर्ण
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित ग_लिखोsl
#घोषणा ग_लिखोsl ग_लिखोsl
अटल अंतरभूत व्योम ग_लिखोsl(अस्थिर व्योम __iomem *addr, स्थिर व्योम *buffer,
			   अचिन्हित पूर्णांक count)
अणु
	अगर (count) अणु
		स्थिर u32 *buf = buffer;

		करो अणु
			__raw_ग_लिखोl(*buf++, addr);
		पूर्ण जबतक (--count);
	पूर्ण
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_64BIT
#अगर_अघोषित ग_लिखोsq
#घोषणा ग_लिखोsq ग_लिखोsq
अटल अंतरभूत व्योम ग_लिखोsq(अस्थिर व्योम __iomem *addr, स्थिर व्योम *buffer,
			   अचिन्हित पूर्णांक count)
अणु
	अगर (count) अणु
		स्थिर u64 *buf = buffer;

		करो अणु
			__raw_ग_लिखोq(*buf++, addr);
		पूर्ण जबतक (--count);
	पूर्ण
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_64BIT */

#अगर_अघोषित PCI_IOBASE
#घोषणा PCI_IOBASE ((व्योम __iomem *)0)
#पूर्ण_अगर

#अगर_अघोषित IO_SPACE_LIMIT
#घोषणा IO_SPACE_LIMIT 0xffff
#पूर्ण_अगर

/*
 * अणुin,outपूर्णअणुb,w,lपूर्ण() access little endian I/O. अणुin,outपूर्णअणुb,w,lपूर्ण_p() can be
 * implemented on hardware that needs an additional delay क्रम I/O accesses to
 * take effect.
 */

#अगर !defined(inb) && !defined(_inb)
#घोषणा _inb _inb
अटल अंतरभूत u8 _inb(अचिन्हित दीर्घ addr)
अणु
	u8 val;

	__io_pbr();
	val = __raw_पढ़ोb(PCI_IOBASE + addr);
	__io_par(val);
	वापस val;
पूर्ण
#पूर्ण_अगर

#अगर !defined(inw) && !defined(_inw)
#घोषणा _inw _inw
अटल अंतरभूत u16 _inw(अचिन्हित दीर्घ addr)
अणु
	u16 val;

	__io_pbr();
	val = __le16_to_cpu((__le16 __क्रमce)__raw_पढ़ोw(PCI_IOBASE + addr));
	__io_par(val);
	वापस val;
पूर्ण
#पूर्ण_अगर

#अगर !defined(inl) && !defined(_inl)
#घोषणा _inl _inl
अटल अंतरभूत u32 _inl(अचिन्हित दीर्घ addr)
अणु
	u32 val;

	__io_pbr();
	val = __le32_to_cpu((__le32 __क्रमce)__raw_पढ़ोl(PCI_IOBASE + addr));
	__io_par(val);
	वापस val;
पूर्ण
#पूर्ण_अगर

#अगर !defined(outb) && !defined(_outb)
#घोषणा _outb _outb
अटल अंतरभूत व्योम _outb(u8 value, अचिन्हित दीर्घ addr)
अणु
	__io_pbw();
	__raw_ग_लिखोb(value, PCI_IOBASE + addr);
	__io_paw();
पूर्ण
#पूर्ण_अगर

#अगर !defined(outw) && !defined(_outw)
#घोषणा _outw _outw
अटल अंतरभूत व्योम _outw(u16 value, अचिन्हित दीर्घ addr)
अणु
	__io_pbw();
	__raw_ग_लिखोw((u16 __क्रमce)cpu_to_le16(value), PCI_IOBASE + addr);
	__io_paw();
पूर्ण
#पूर्ण_अगर

#अगर !defined(outl) && !defined(_outl)
#घोषणा _outl _outl
अटल अंतरभूत व्योम _outl(u32 value, अचिन्हित दीर्घ addr)
अणु
	__io_pbw();
	__raw_ग_लिखोl((u32 __क्रमce)cpu_to_le32(value), PCI_IOBASE + addr);
	__io_paw();
पूर्ण
#पूर्ण_अगर

#समावेश <linux/logic_pपन.स>

#अगर_अघोषित inb
#घोषणा inb _inb
#पूर्ण_अगर

#अगर_अघोषित inw
#घोषणा inw _inw
#पूर्ण_अगर

#अगर_अघोषित inl
#घोषणा inl _inl
#पूर्ण_अगर

#अगर_अघोषित outb
#घोषणा outb _outb
#पूर्ण_अगर

#अगर_अघोषित outw
#घोषणा outw _outw
#पूर्ण_अगर

#अगर_अघोषित outl
#घोषणा outl _outl
#पूर्ण_अगर

#अगर_अघोषित inb_p
#घोषणा inb_p inb_p
अटल अंतरभूत u8 inb_p(अचिन्हित दीर्घ addr)
अणु
	वापस inb(addr);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित inw_p
#घोषणा inw_p inw_p
अटल अंतरभूत u16 inw_p(अचिन्हित दीर्घ addr)
अणु
	वापस inw(addr);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित inl_p
#घोषणा inl_p inl_p
अटल अंतरभूत u32 inl_p(अचिन्हित दीर्घ addr)
अणु
	वापस inl(addr);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित outb_p
#घोषणा outb_p outb_p
अटल अंतरभूत व्योम outb_p(u8 value, अचिन्हित दीर्घ addr)
अणु
	outb(value, addr);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित outw_p
#घोषणा outw_p outw_p
अटल अंतरभूत व्योम outw_p(u16 value, अचिन्हित दीर्घ addr)
अणु
	outw(value, addr);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित outl_p
#घोषणा outl_p outl_p
अटल अंतरभूत व्योम outl_p(u32 value, अचिन्हित दीर्घ addr)
अणु
	outl(value, addr);
पूर्ण
#पूर्ण_अगर

/*
 * अणुin,outपूर्णsअणुb,w,lपूर्णअणु,_pपूर्ण() are variants of the above that repeatedly access a
 * single I/O port multiple बार.
 */

#अगर_अघोषित insb
#घोषणा insb insb
अटल अंतरभूत व्योम insb(अचिन्हित दीर्घ addr, व्योम *buffer, अचिन्हित पूर्णांक count)
अणु
	पढ़ोsb(PCI_IOBASE + addr, buffer, count);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित insw
#घोषणा insw insw
अटल अंतरभूत व्योम insw(अचिन्हित दीर्घ addr, व्योम *buffer, अचिन्हित पूर्णांक count)
अणु
	पढ़ोsw(PCI_IOBASE + addr, buffer, count);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित insl
#घोषणा insl insl
अटल अंतरभूत व्योम insl(अचिन्हित दीर्घ addr, व्योम *buffer, अचिन्हित पूर्णांक count)
अणु
	पढ़ोsl(PCI_IOBASE + addr, buffer, count);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित outsb
#घोषणा outsb outsb
अटल अंतरभूत व्योम outsb(अचिन्हित दीर्घ addr, स्थिर व्योम *buffer,
			 अचिन्हित पूर्णांक count)
अणु
	ग_लिखोsb(PCI_IOBASE + addr, buffer, count);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित outsw
#घोषणा outsw outsw
अटल अंतरभूत व्योम outsw(अचिन्हित दीर्घ addr, स्थिर व्योम *buffer,
			 अचिन्हित पूर्णांक count)
अणु
	ग_लिखोsw(PCI_IOBASE + addr, buffer, count);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित outsl
#घोषणा outsl outsl
अटल अंतरभूत व्योम outsl(अचिन्हित दीर्घ addr, स्थिर व्योम *buffer,
			 अचिन्हित पूर्णांक count)
अणु
	ग_लिखोsl(PCI_IOBASE + addr, buffer, count);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित insb_p
#घोषणा insb_p insb_p
अटल अंतरभूत व्योम insb_p(अचिन्हित दीर्घ addr, व्योम *buffer, अचिन्हित पूर्णांक count)
अणु
	insb(addr, buffer, count);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित insw_p
#घोषणा insw_p insw_p
अटल अंतरभूत व्योम insw_p(अचिन्हित दीर्घ addr, व्योम *buffer, अचिन्हित पूर्णांक count)
अणु
	insw(addr, buffer, count);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित insl_p
#घोषणा insl_p insl_p
अटल अंतरभूत व्योम insl_p(अचिन्हित दीर्घ addr, व्योम *buffer, अचिन्हित पूर्णांक count)
अणु
	insl(addr, buffer, count);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित outsb_p
#घोषणा outsb_p outsb_p
अटल अंतरभूत व्योम outsb_p(अचिन्हित दीर्घ addr, स्थिर व्योम *buffer,
			   अचिन्हित पूर्णांक count)
अणु
	outsb(addr, buffer, count);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित outsw_p
#घोषणा outsw_p outsw_p
अटल अंतरभूत व्योम outsw_p(अचिन्हित दीर्घ addr, स्थिर व्योम *buffer,
			   अचिन्हित पूर्णांक count)
अणु
	outsw(addr, buffer, count);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित outsl_p
#घोषणा outsl_p outsl_p
अटल अंतरभूत व्योम outsl_p(अचिन्हित दीर्घ addr, स्थिर व्योम *buffer,
			   अचिन्हित पूर्णांक count)
अणु
	outsl(addr, buffer, count);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित CONFIG_GENERIC_IOMAP
#अगर_अघोषित ioपढ़ो8
#घोषणा ioपढ़ो8 ioपढ़ो8
अटल अंतरभूत u8 ioपढ़ो8(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस पढ़ोb(addr);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित ioपढ़ो16
#घोषणा ioपढ़ो16 ioपढ़ो16
अटल अंतरभूत u16 ioपढ़ो16(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस पढ़ोw(addr);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित ioपढ़ो32
#घोषणा ioपढ़ो32 ioपढ़ो32
अटल अंतरभूत u32 ioपढ़ो32(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस पढ़ोl(addr);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_64BIT
#अगर_अघोषित ioपढ़ो64
#घोषणा ioपढ़ो64 ioपढ़ो64
अटल अंतरभूत u64 ioपढ़ो64(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस पढ़ोq(addr);
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_64BIT */

#अगर_अघोषित ioग_लिखो8
#घोषणा ioग_लिखो8 ioग_लिखो8
अटल अंतरभूत व्योम ioग_लिखो8(u8 value, अस्थिर व्योम __iomem *addr)
अणु
	ग_लिखोb(value, addr);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित ioग_लिखो16
#घोषणा ioग_लिखो16 ioग_लिखो16
अटल अंतरभूत व्योम ioग_लिखो16(u16 value, अस्थिर व्योम __iomem *addr)
अणु
	ग_लिखोw(value, addr);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित ioग_लिखो32
#घोषणा ioग_लिखो32 ioग_लिखो32
अटल अंतरभूत व्योम ioग_लिखो32(u32 value, अस्थिर व्योम __iomem *addr)
अणु
	ग_लिखोl(value, addr);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_64BIT
#अगर_अघोषित ioग_लिखो64
#घोषणा ioग_लिखो64 ioग_लिखो64
अटल अंतरभूत व्योम ioग_लिखो64(u64 value, अस्थिर व्योम __iomem *addr)
अणु
	ग_लिखोq(value, addr);
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_64BIT */

#अगर_अघोषित ioपढ़ो16be
#घोषणा ioपढ़ो16be ioपढ़ो16be
अटल अंतरभूत u16 ioपढ़ो16be(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस swab16(पढ़ोw(addr));
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित ioपढ़ो32be
#घोषणा ioपढ़ो32be ioपढ़ो32be
अटल अंतरभूत u32 ioपढ़ो32be(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस swab32(पढ़ोl(addr));
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_64BIT
#अगर_अघोषित ioपढ़ो64be
#घोषणा ioपढ़ो64be ioपढ़ो64be
अटल अंतरभूत u64 ioपढ़ो64be(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस swab64(पढ़ोq(addr));
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_64BIT */

#अगर_अघोषित ioग_लिखो16be
#घोषणा ioग_लिखो16be ioग_लिखो16be
अटल अंतरभूत व्योम ioग_लिखो16be(u16 value, व्योम अस्थिर __iomem *addr)
अणु
	ग_लिखोw(swab16(value), addr);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित ioग_लिखो32be
#घोषणा ioग_लिखो32be ioग_लिखो32be
अटल अंतरभूत व्योम ioग_लिखो32be(u32 value, अस्थिर व्योम __iomem *addr)
अणु
	ग_लिखोl(swab32(value), addr);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_64BIT
#अगर_अघोषित ioग_लिखो64be
#घोषणा ioग_लिखो64be ioग_लिखो64be
अटल अंतरभूत व्योम ioग_लिखो64be(u64 value, अस्थिर व्योम __iomem *addr)
अणु
	ग_लिखोq(swab64(value), addr);
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_64BIT */

#अगर_अघोषित ioपढ़ो8_rep
#घोषणा ioपढ़ो8_rep ioपढ़ो8_rep
अटल अंतरभूत व्योम ioपढ़ो8_rep(स्थिर अस्थिर व्योम __iomem *addr, व्योम *buffer,
			       अचिन्हित पूर्णांक count)
अणु
	पढ़ोsb(addr, buffer, count);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित ioपढ़ो16_rep
#घोषणा ioपढ़ो16_rep ioपढ़ो16_rep
अटल अंतरभूत व्योम ioपढ़ो16_rep(स्थिर अस्थिर व्योम __iomem *addr,
				व्योम *buffer, अचिन्हित पूर्णांक count)
अणु
	पढ़ोsw(addr, buffer, count);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित ioपढ़ो32_rep
#घोषणा ioपढ़ो32_rep ioपढ़ो32_rep
अटल अंतरभूत व्योम ioपढ़ो32_rep(स्थिर अस्थिर व्योम __iomem *addr,
				व्योम *buffer, अचिन्हित पूर्णांक count)
अणु
	पढ़ोsl(addr, buffer, count);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_64BIT
#अगर_अघोषित ioपढ़ो64_rep
#घोषणा ioपढ़ो64_rep ioपढ़ो64_rep
अटल अंतरभूत व्योम ioपढ़ो64_rep(स्थिर अस्थिर व्योम __iomem *addr,
				व्योम *buffer, अचिन्हित पूर्णांक count)
अणु
	पढ़ोsq(addr, buffer, count);
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_64BIT */

#अगर_अघोषित ioग_लिखो8_rep
#घोषणा ioग_लिखो8_rep ioग_लिखो8_rep
अटल अंतरभूत व्योम ioग_लिखो8_rep(अस्थिर व्योम __iomem *addr,
				स्थिर व्योम *buffer,
				अचिन्हित पूर्णांक count)
अणु
	ग_लिखोsb(addr, buffer, count);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित ioग_लिखो16_rep
#घोषणा ioग_लिखो16_rep ioग_लिखो16_rep
अटल अंतरभूत व्योम ioग_लिखो16_rep(अस्थिर व्योम __iomem *addr,
				 स्थिर व्योम *buffer,
				 अचिन्हित पूर्णांक count)
अणु
	ग_लिखोsw(addr, buffer, count);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित ioग_लिखो32_rep
#घोषणा ioग_लिखो32_rep ioग_लिखो32_rep
अटल अंतरभूत व्योम ioग_लिखो32_rep(अस्थिर व्योम __iomem *addr,
				 स्थिर व्योम *buffer,
				 अचिन्हित पूर्णांक count)
अणु
	ग_लिखोsl(addr, buffer, count);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_64BIT
#अगर_अघोषित ioग_लिखो64_rep
#घोषणा ioग_लिखो64_rep ioग_लिखो64_rep
अटल अंतरभूत व्योम ioग_लिखो64_rep(अस्थिर व्योम __iomem *addr,
				 स्थिर व्योम *buffer,
				 अचिन्हित पूर्णांक count)
अणु
	ग_लिखोsq(addr, buffer, count);
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_64BIT */
#पूर्ण_अगर /* CONFIG_GENERIC_IOMAP */

#अगर_घोषित __KERNEL__

#समावेश <linux/vदो_स्मृति.h>
#घोषणा __io_virt(x) ((व्योम __क्रमce *)(x))

/*
 * Change भव addresses to physical addresses and vv.
 * These are pretty trivial
 */
#अगर_अघोषित virt_to_phys
#घोषणा virt_to_phys virt_to_phys
अटल अंतरभूत अचिन्हित दीर्घ virt_to_phys(अस्थिर व्योम *address)
अणु
	वापस __pa((अचिन्हित दीर्घ)address);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित phys_to_virt
#घोषणा phys_to_virt phys_to_virt
अटल अंतरभूत व्योम *phys_to_virt(अचिन्हित दीर्घ address)
अणु
	वापस __va(address);
पूर्ण
#पूर्ण_अगर

/**
 * DOC: ioremap() and ioremap_*() variants
 *
 * Architectures with an MMU are expected to provide ioremap() and iounmap()
 * themselves or rely on GENERIC_IOREMAP.  For NOMMU architectures we provide
 * a शेष nop-op implementation that expect that the physical address used
 * क्रम MMIO are alपढ़ोy marked as uncached, and can be used as kernel भव
 * addresses.
 *
 * ioremap_wc() and ioremap_wt() can provide more relaxed caching attributes
 * क्रम specअगरic drivers अगर the architecture choses to implement them.  If they
 * are not implemented we fall back to plain ioremap. Conversely, ioremap_np()
 * can provide stricter non-posted ग_लिखो semantics अगर the architecture
 * implements them.
 */
#अगर_अघोषित CONFIG_MMU
#अगर_अघोषित ioremap
#घोषणा ioremap ioremap
अटल अंतरभूत व्योम __iomem *ioremap(phys_addr_t offset, माप_प्रकार size)
अणु
	वापस (व्योम __iomem *)(अचिन्हित दीर्घ)offset;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित iounmap
#घोषणा iounmap iounmap
अटल अंतरभूत व्योम iounmap(व्योम __iomem *addr)
अणु
पूर्ण
#पूर्ण_अगर
#या_अगर defined(CONFIG_GENERIC_IOREMAP)
#समावेश <linux/pgtable.h>

व्योम __iomem *ioremap_prot(phys_addr_t addr, माप_प्रकार size, अचिन्हित दीर्घ prot);
व्योम iounmap(अस्थिर व्योम __iomem *addr);

अटल अंतरभूत व्योम __iomem *ioremap(phys_addr_t addr, माप_प्रकार size)
अणु
	/* _PAGE_IOREMAP needs to be supplied by the architecture */
	वापस ioremap_prot(addr, size, _PAGE_IOREMAP);
पूर्ण
#पूर्ण_अगर /* !CONFIG_MMU || CONFIG_GENERIC_IOREMAP */

#अगर_अघोषित ioremap_wc
#घोषणा ioremap_wc ioremap
#पूर्ण_अगर

#अगर_अघोषित ioremap_wt
#घोषणा ioremap_wt ioremap
#पूर्ण_अगर

/*
 * ioremap_uc is special in that we करो require an explicit architecture
 * implementation.  In general you करो not want to use this function in a
 * driver and use plain ioremap, which is uncached by शेष.  Similarly
 * architectures should not implement it unless they have a very good
 * reason.
 */
#अगर_अघोषित ioremap_uc
#घोषणा ioremap_uc ioremap_uc
अटल अंतरभूत व्योम __iomem *ioremap_uc(phys_addr_t offset, माप_प्रकार size)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

/*
 * ioremap_np needs an explicit architecture implementation, as it
 * requests stronger semantics than regular ioremap(). Portable drivers
 * should instead use one of the higher-level असलtractions, like
 * devm_ioremap_resource(), to choose the correct variant क्रम any given
 * device and bus. Portable drivers with a good reason to want non-posted
 * ग_लिखो semantics should always provide an ioremap() fallback in हाल
 * ioremap_np() is not available.
 */
#अगर_अघोषित ioremap_np
#घोषणा ioremap_np ioremap_np
अटल अंतरभूत व्योम __iomem *ioremap_np(phys_addr_t offset, माप_प्रकार size)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_HAS_IOPORT_MAP
#अगर_अघोषित CONFIG_GENERIC_IOMAP
#अगर_अघोषित ioport_map
#घोषणा ioport_map ioport_map
अटल अंतरभूत व्योम __iomem *ioport_map(अचिन्हित दीर्घ port, अचिन्हित पूर्णांक nr)
अणु
	port &= IO_SPACE_LIMIT;
	वापस (port > MMIO_UPPER_LIMIT) ? शून्य : PCI_IOBASE + port;
पूर्ण
#घोषणा __pci_ioport_unmap __pci_ioport_unmap
अटल अंतरभूत व्योम __pci_ioport_unmap(व्योम __iomem *p)
अणु
	uपूर्णांकptr_t start = (uपूर्णांकptr_t) PCI_IOBASE;
	uपूर्णांकptr_t addr = (uपूर्णांकptr_t) p;

	अगर (addr >= start && addr < start + IO_SPACE_LIMIT)
		वापस;
	iounmap(p);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित ioport_unmap
#घोषणा ioport_unmap ioport_unmap
अटल अंतरभूत व्योम ioport_unmap(व्योम __iomem *p)
अणु
पूर्ण
#पूर्ण_अगर
#अन्यथा /* CONFIG_GENERIC_IOMAP */
बाह्य व्योम __iomem *ioport_map(अचिन्हित दीर्घ port, अचिन्हित पूर्णांक nr);
बाह्य व्योम ioport_unmap(व्योम __iomem *p);
#पूर्ण_अगर /* CONFIG_GENERIC_IOMAP */
#पूर्ण_अगर /* CONFIG_HAS_IOPORT_MAP */

#अगर_अघोषित CONFIG_GENERIC_IOMAP
काष्ठा pci_dev;
बाह्य व्योम __iomem *pci_iomap(काष्ठा pci_dev *dev, पूर्णांक bar, अचिन्हित दीर्घ max);

#अगर_अघोषित __pci_ioport_unmap
अटल अंतरभूत व्योम __pci_ioport_unmap(व्योम __iomem *p) अणुपूर्ण
#पूर्ण_अगर

#अगर_अघोषित pci_iounmap
#घोषणा pci_iounmap pci_iounmap
अटल अंतरभूत व्योम pci_iounmap(काष्ठा pci_dev *dev, व्योम __iomem *p)
अणु
	__pci_ioport_unmap(p);
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_GENERIC_IOMAP */

#अगर_अघोषित xlate_dev_mem_ptr
#घोषणा xlate_dev_mem_ptr xlate_dev_mem_ptr
अटल अंतरभूत व्योम *xlate_dev_mem_ptr(phys_addr_t addr)
अणु
	वापस __va(addr);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित unxlate_dev_mem_ptr
#घोषणा unxlate_dev_mem_ptr unxlate_dev_mem_ptr
अटल अंतरभूत व्योम unxlate_dev_mem_ptr(phys_addr_t phys, व्योम *addr)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_VIRT_TO_BUS
#अगर_अघोषित virt_to_bus
अटल अंतरभूत अचिन्हित दीर्घ virt_to_bus(व्योम *address)
अणु
	वापस (अचिन्हित दीर्घ)address;
पूर्ण

अटल अंतरभूत व्योम *bus_to_virt(अचिन्हित दीर्घ address)
अणु
	वापस (व्योम *)address;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_अघोषित स_रखो_io
#घोषणा स_रखो_io स_रखो_io
/**
 * स_रखो_io	Set a range of I/O memory to a स्थिरant value
 * @addr:	The beginning of the I/O-memory range to set
 * @val:	The value to set the memory to
 * @count:	The number of bytes to set
 *
 * Set a range of I/O memory to a given value.
 */
अटल अंतरभूत व्योम स_रखो_io(अस्थिर व्योम __iomem *addr, पूर्णांक value,
			     माप_प्रकार size)
अणु
	स_रखो(__io_virt(addr), value, size);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित स_नकल_fromio
#घोषणा स_नकल_fromio स_नकल_fromio
/**
 * स_नकल_fromio	Copy a block of data from I/O memory
 * @dst:		The (RAM) destination क्रम the copy
 * @src:		The (I/O memory) source क्रम the data
 * @count:		The number of bytes to copy
 *
 * Copy a block of data from I/O memory.
 */
अटल अंतरभूत व्योम स_नकल_fromio(व्योम *buffer,
				 स्थिर अस्थिर व्योम __iomem *addr,
				 माप_प्रकार size)
अणु
	स_नकल(buffer, __io_virt(addr), size);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित स_नकल_toio
#घोषणा स_नकल_toio स_नकल_toio
/**
 * स_नकल_toio		Copy a block of data पूर्णांकo I/O memory
 * @dst:		The (I/O memory) destination क्रम the copy
 * @src:		The (RAM) source क्रम the data
 * @count:		The number of bytes to copy
 *
 * Copy a block of data to I/O memory.
 */
अटल अंतरभूत व्योम स_नकल_toio(अस्थिर व्योम __iomem *addr, स्थिर व्योम *buffer,
			       माप_प्रकार size)
अणु
	स_नकल(__io_virt(addr), buffer, size);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित CONFIG_GENERIC_DEVMEM_IS_ALLOWED
बाह्य पूर्णांक devmem_is_allowed(अचिन्हित दीर्घ pfn);
#पूर्ण_अगर

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* __ASM_GENERIC_IO_H */
