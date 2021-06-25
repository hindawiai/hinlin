<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * IO definitions क्रम the Hexagon architecture
 *
 * Copyright (c) 2010-2013, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _ASM_IO_H
#घोषणा _ASM_IO_H

#अगर_घोषित __KERNEL__

#समावेश <linux/types.h>
#समावेश <यंत्र/iomap.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/cacheflush.h>

/*
 * We करोn't have PCI yet.
 * _IO_BASE is poपूर्णांकing at what should be unused भव space.
 */
#घोषणा IO_SPACE_LIMIT 0xffff
#घोषणा _IO_BASE ((व्योम __iomem *)0xfe000000)

#घोषणा IOMEM(x)        ((व्योम __क्रमce __iomem *)(x))

बाह्य पूर्णांक remap_area_pages(अचिन्हित दीर्घ start, अचिन्हित दीर्घ phys_addr,
				अचिन्हित दीर्घ end, अचिन्हित दीर्घ flags);

बाह्य व्योम iounmap(स्थिर अस्थिर व्योम __iomem *addr);

/* Defined in lib/io.c, needed क्रम smc91x driver. */
बाह्य व्योम __raw_पढ़ोsw(स्थिर व्योम __iomem *addr, व्योम *data, पूर्णांक wordlen);
बाह्य व्योम __raw_ग_लिखोsw(व्योम __iomem *addr, स्थिर व्योम *data, पूर्णांक wordlen);

बाह्य व्योम __raw_पढ़ोsl(स्थिर व्योम __iomem *addr, व्योम *data, पूर्णांक wordlen);
बाह्य व्योम __raw_ग_लिखोsl(व्योम __iomem *addr, स्थिर व्योम *data, पूर्णांक wordlen);

#घोषणा पढ़ोsw(p, d, l)	__raw_पढ़ोsw(p, d, l)
#घोषणा ग_लिखोsw(p, d, l) __raw_ग_लिखोsw(p, d, l)

#घोषणा पढ़ोsl(p, d, l)   __raw_पढ़ोsl(p, d, l)
#घोषणा ग_लिखोsl(p, d, l)  __raw_ग_लिखोsl(p, d, l)

/*
 * virt_to_phys - map भव address to physical
 * @address:  address to map
 */
अटल अंतरभूत अचिन्हित दीर्घ virt_to_phys(अस्थिर व्योम *address)
अणु
	वापस __pa(address);
पूर्ण

/*
 * phys_to_virt - map physical address to भव
 * @address: address to map
 */
अटल अंतरभूत व्योम *phys_to_virt(अचिन्हित दीर्घ address)
अणु
	वापस __va(address);
पूर्ण

/*
 * convert a physical poपूर्णांकer to a भव kernel poपूर्णांकer क्रम
 * /dev/mem access.
 */
#घोषणा xlate_dev_mem_ptr(p)    __va(p)

/*
 * IO port access primitives.  Hexagon करोesn't have special IO access
 * inकाष्ठाions; all I/O is memory mapped.
 *
 * in/out are used क्रम "ports", but we करोn't have "port instructions",
 * so these are really just memory mapped too.
 */

/*
 * पढ़ोb - पढ़ो byte from memory mapped device
 * @addr:  poपूर्णांकer to memory
 *
 * Operates on "I/O bus memory space"
 */
अटल अंतरभूत u8 पढ़ोb(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u8 val;
	यंत्र अस्थिर(
		"%0 = memb(%1);"
		: "=&r" (val)
		: "r" (addr)
	);
	वापस val;
पूर्ण

अटल अंतरभूत u16 पढ़ोw(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u16 val;
	यंत्र अस्थिर(
		"%0 = memh(%1);"
		: "=&r" (val)
		: "r" (addr)
	);
	वापस val;
पूर्ण

अटल अंतरभूत u32 पढ़ोl(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u32 val;
	यंत्र अस्थिर(
		"%0 = memw(%1);"
		: "=&r" (val)
		: "r" (addr)
	);
	वापस val;
पूर्ण

/*
 * ग_लिखोb - ग_लिखो a byte to a memory location
 * @data: data to ग_लिखो to
 * @addr:  poपूर्णांकer to memory
 *
 */
अटल अंतरभूत व्योम ग_लिखोb(u8 data, अस्थिर व्योम __iomem *addr)
अणु
	यंत्र अस्थिर(
		"memb(%0) = %1;"
		:
		: "r" (addr), "r" (data)
		: "memory"
	);
पूर्ण

अटल अंतरभूत व्योम ग_लिखोw(u16 data, अस्थिर व्योम __iomem *addr)
अणु
	यंत्र अस्थिर(
		"memh(%0) = %1;"
		:
		: "r" (addr), "r" (data)
		: "memory"
	);

पूर्ण

अटल अंतरभूत व्योम ग_लिखोl(u32 data, अस्थिर व्योम __iomem *addr)
अणु
	यंत्र अस्थिर(
		"memw(%0) = %1;"
		:
		: "r" (addr), "r" (data)
		: "memory"
	);
पूर्ण

#घोषणा __raw_ग_लिखोb ग_लिखोb
#घोषणा __raw_ग_लिखोw ग_लिखोw
#घोषणा __raw_ग_लिखोl ग_लिखोl

#घोषणा __raw_पढ़ोb पढ़ोb
#घोषणा __raw_पढ़ोw पढ़ोw
#घोषणा __raw_पढ़ोl पढ़ोl

/*
 * http://comments.gmane.org/gmane.linux.ports.arm.kernel/117626
 */

#घोषणा पढ़ोb_relaxed __raw_पढ़ोb
#घोषणा पढ़ोw_relaxed __raw_पढ़ोw
#घोषणा पढ़ोl_relaxed __raw_पढ़ोl

#घोषणा ग_लिखोb_relaxed __raw_ग_लिखोb
#घोषणा ग_लिखोw_relaxed __raw_ग_लिखोw
#घोषणा ग_लिखोl_relaxed __raw_ग_लिखोl

व्योम __iomem *ioremap(अचिन्हित दीर्घ phys_addr, अचिन्हित दीर्घ size);
#घोषणा ioremap_uc(X, Y) ioremap((X), (Y))


#घोषणा __raw_ग_लिखोl ग_लिखोl

अटल अंतरभूत व्योम स_नकल_fromio(व्योम *dst, स्थिर अस्थिर व्योम __iomem *src,
	पूर्णांक count)
अणु
	स_नकल(dst, (व्योम *) src, count);
पूर्ण

अटल अंतरभूत व्योम स_नकल_toio(अस्थिर व्योम __iomem *dst, स्थिर व्योम *src,
	पूर्णांक count)
अणु
	स_नकल((व्योम *) dst, src, count);
पूर्ण

अटल अंतरभूत व्योम स_रखो_io(अस्थिर व्योम __iomem *addr, पूर्णांक value,
			     माप_प्रकार size)
अणु
	स_रखो((व्योम __क्रमce *)addr, value, size);
पूर्ण

#घोषणा PCI_IO_ADDR	(अस्थिर व्योम __iomem *)

/*
 * inb - पढ़ो byte from I/O port or something
 * @port:  address in I/O space
 *
 * Operates on "I/O bus I/O space"
 */
अटल अंतरभूत u8 inb(अचिन्हित दीर्घ port)
अणु
	वापस पढ़ोb(_IO_BASE + (port & IO_SPACE_LIMIT));
पूर्ण

अटल अंतरभूत u16 inw(अचिन्हित दीर्घ port)
अणु
	वापस पढ़ोw(_IO_BASE + (port & IO_SPACE_LIMIT));
पूर्ण

अटल अंतरभूत u32 inl(अचिन्हित दीर्घ port)
अणु
	वापस पढ़ोl(_IO_BASE + (port & IO_SPACE_LIMIT));
पूर्ण

/*
 * outb - ग_लिखो a byte to a memory location
 * @data: data to ग_लिखो to
 * @addr:  address in I/O space
 */
अटल अंतरभूत व्योम outb(u8 data, अचिन्हित दीर्घ port)
अणु
	ग_लिखोb(data, _IO_BASE + (port & IO_SPACE_LIMIT));
पूर्ण

अटल अंतरभूत व्योम outw(u16 data, अचिन्हित दीर्घ port)
अणु
	ग_लिखोw(data, _IO_BASE + (port & IO_SPACE_LIMIT));
पूर्ण

अटल अंतरभूत व्योम outl(u32 data, अचिन्हित दीर्घ port)
अणु
	ग_लिखोl(data, _IO_BASE + (port & IO_SPACE_LIMIT));
पूर्ण

#घोषणा outb_p outb
#घोषणा outw_p outw
#घोषणा outl_p outl

#घोषणा inb_p inb
#घोषणा inw_p inw
#घोषणा inl_p inl

अटल अंतरभूत व्योम insb(अचिन्हित दीर्घ port, व्योम *buffer, पूर्णांक count)
अणु
	अगर (count) अणु
		u8 *buf = buffer;
		करो अणु
			u8 x = inb(port);
			*buf++ = x;
		पूर्ण जबतक (--count);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम insw(अचिन्हित दीर्घ port, व्योम *buffer, पूर्णांक count)
अणु
	अगर (count) अणु
		u16 *buf = buffer;
		करो अणु
			u16 x = inw(port);
			*buf++ = x;
		पूर्ण जबतक (--count);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम insl(अचिन्हित दीर्घ port, व्योम *buffer, पूर्णांक count)
अणु
	अगर (count) अणु
		u32 *buf = buffer;
		करो अणु
			u32 x = inw(port);
			*buf++ = x;
		पूर्ण जबतक (--count);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम outsb(अचिन्हित दीर्घ port, स्थिर व्योम *buffer, पूर्णांक count)
अणु
	अगर (count) अणु
		स्थिर u8 *buf = buffer;
		करो अणु
			outb(*buf++, port);
		पूर्ण जबतक (--count);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम outsw(अचिन्हित दीर्घ port, स्थिर व्योम *buffer, पूर्णांक count)
अणु
	अगर (count) अणु
		स्थिर u16 *buf = buffer;
		करो अणु
			outw(*buf++, port);
		पूर्ण जबतक (--count);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम outsl(अचिन्हित दीर्घ port, स्थिर व्योम *buffer, पूर्णांक count)
अणु
	अगर (count) अणु
		स्थिर u32 *buf = buffer;
		करो अणु
			outl(*buf++, port);
		पूर्ण जबतक (--count);
	पूर्ण
पूर्ण

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर
