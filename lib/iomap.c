<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Implement the शेष iomap पूर्णांकerfaces
 *
 * (C) Copyright 2004 Linus Torvalds
 */
#समावेश <linux/pci.h>
#समावेश <linux/पन.स>

#समावेश <linux/export.h>

/*
 * Read/ग_लिखो from/to an (offsettable) iomem cookie. It might be a PIO
 * access or a MMIO access, these functions करोn't care. The info is
 * encoded in the hardware mapping set up by the mapping functions
 * (or the cookie itself, depending on implementation and hw).
 *
 * The generic routines करोn't assume any hardware mappings, and just
 * encode the PIO/MMIO as part of the cookie. They coldly assume that
 * the MMIO IO mappings are not in the low address range.
 *
 * Architectures क्रम which this is not true can't use this generic
 * implementation and should करो their own copy.
 */

#अगर_अघोषित HAVE_ARCH_PIO_SIZE
/*
 * We encode the physical PIO addresses (0-0xffff) पूर्णांकo the
 * poपूर्णांकer by offsetting them with a स्थिरant (0x10000) and
 * assuming that all the low addresses are always PIO. That means
 * we can करो some sanity checks on the low bits, and करोn't
 * need to just take things क्रम granted.
 */
#घोषणा PIO_OFFSET	0x10000UL
#घोषणा PIO_MASK	0x0ffffUL
#घोषणा PIO_RESERVED	0x40000UL
#पूर्ण_अगर

अटल व्योम bad_io_access(अचिन्हित दीर्घ port, स्थिर अक्षर *access)
अणु
	अटल पूर्णांक count = 10;
	अगर (count) अणु
		count--;
		WARN(1, KERN_ERR "Bad IO access at port %#lx (%s)\n", port, access);
	पूर्ण
पूर्ण

/*
 * Ugly macros are a way of lअगरe.
 */
#घोषणा IO_COND(addr, is_pio, is_mmio) करो अणु			\
	अचिन्हित दीर्घ port = (अचिन्हित दीर्घ __क्रमce)addr;	\
	अगर (port >= PIO_RESERVED) अणु				\
		is_mmio;					\
	पूर्ण अन्यथा अगर (port > PIO_OFFSET) अणु				\
		port &= PIO_MASK;				\
		is_pio;						\
	पूर्ण अन्यथा							\
		bad_io_access(port, #is_pio );			\
पूर्ण जबतक (0)

#अगर_अघोषित pio_पढ़ो16be
#घोषणा pio_पढ़ो16be(port) swab16(inw(port))
#घोषणा pio_पढ़ो32be(port) swab32(inl(port))
#पूर्ण_अगर

#अगर_अघोषित mmio_पढ़ो16be
#घोषणा mmio_पढ़ो16be(addr) swab16(पढ़ोw(addr))
#घोषणा mmio_पढ़ो32be(addr) swab32(पढ़ोl(addr))
#घोषणा mmio_पढ़ो64be(addr) swab64(पढ़ोq(addr))
#पूर्ण_अगर

अचिन्हित पूर्णांक ioपढ़ो8(स्थिर व्योम __iomem *addr)
अणु
	IO_COND(addr, वापस inb(port), वापस पढ़ोb(addr));
	वापस 0xff;
पूर्ण
अचिन्हित पूर्णांक ioपढ़ो16(स्थिर व्योम __iomem *addr)
अणु
	IO_COND(addr, वापस inw(port), वापस पढ़ोw(addr));
	वापस 0xffff;
पूर्ण
अचिन्हित पूर्णांक ioपढ़ो16be(स्थिर व्योम __iomem *addr)
अणु
	IO_COND(addr, वापस pio_पढ़ो16be(port), वापस mmio_पढ़ो16be(addr));
	वापस 0xffff;
पूर्ण
अचिन्हित पूर्णांक ioपढ़ो32(स्थिर व्योम __iomem *addr)
अणु
	IO_COND(addr, वापस inl(port), वापस पढ़ोl(addr));
	वापस 0xffffffff;
पूर्ण
अचिन्हित पूर्णांक ioपढ़ो32be(स्थिर व्योम __iomem *addr)
अणु
	IO_COND(addr, वापस pio_पढ़ो32be(port), वापस mmio_पढ़ो32be(addr));
	वापस 0xffffffff;
पूर्ण
EXPORT_SYMBOL(ioपढ़ो8);
EXPORT_SYMBOL(ioपढ़ो16);
EXPORT_SYMBOL(ioपढ़ो16be);
EXPORT_SYMBOL(ioपढ़ो32);
EXPORT_SYMBOL(ioपढ़ो32be);

#अगर_घोषित पढ़ोq
अटल u64 pio_पढ़ो64_lo_hi(अचिन्हित दीर्घ port)
अणु
	u64 lo, hi;

	lo = inl(port);
	hi = inl(port + माप(u32));

	वापस lo | (hi << 32);
पूर्ण

अटल u64 pio_पढ़ो64_hi_lo(अचिन्हित दीर्घ port)
अणु
	u64 lo, hi;

	hi = inl(port + माप(u32));
	lo = inl(port);

	वापस lo | (hi << 32);
पूर्ण

अटल u64 pio_पढ़ो64be_lo_hi(अचिन्हित दीर्घ port)
अणु
	u64 lo, hi;

	lo = pio_पढ़ो32be(port + माप(u32));
	hi = pio_पढ़ो32be(port);

	वापस lo | (hi << 32);
पूर्ण

अटल u64 pio_पढ़ो64be_hi_lo(अचिन्हित दीर्घ port)
अणु
	u64 lo, hi;

	hi = pio_पढ़ो32be(port);
	lo = pio_पढ़ो32be(port + माप(u32));

	वापस lo | (hi << 32);
पूर्ण

u64 ioपढ़ो64_lo_hi(स्थिर व्योम __iomem *addr)
अणु
	IO_COND(addr, वापस pio_पढ़ो64_lo_hi(port), वापस पढ़ोq(addr));
	वापस 0xffffffffffffffffULL;
पूर्ण

u64 ioपढ़ो64_hi_lo(स्थिर व्योम __iomem *addr)
अणु
	IO_COND(addr, वापस pio_पढ़ो64_hi_lo(port), वापस पढ़ोq(addr));
	वापस 0xffffffffffffffffULL;
पूर्ण

u64 ioपढ़ो64be_lo_hi(स्थिर व्योम __iomem *addr)
अणु
	IO_COND(addr, वापस pio_पढ़ो64be_lo_hi(port),
		वापस mmio_पढ़ो64be(addr));
	वापस 0xffffffffffffffffULL;
पूर्ण

u64 ioपढ़ो64be_hi_lo(स्थिर व्योम __iomem *addr)
अणु
	IO_COND(addr, वापस pio_पढ़ो64be_hi_lo(port),
		वापस mmio_पढ़ो64be(addr));
	वापस 0xffffffffffffffffULL;
पूर्ण

EXPORT_SYMBOL(ioपढ़ो64_lo_hi);
EXPORT_SYMBOL(ioपढ़ो64_hi_lo);
EXPORT_SYMBOL(ioपढ़ो64be_lo_hi);
EXPORT_SYMBOL(ioपढ़ो64be_hi_lo);

#पूर्ण_अगर /* पढ़ोq */

#अगर_अघोषित pio_ग_लिखो16be
#घोषणा pio_ग_लिखो16be(val,port) outw(swab16(val),port)
#घोषणा pio_ग_लिखो32be(val,port) outl(swab32(val),port)
#पूर्ण_अगर

#अगर_अघोषित mmio_ग_लिखो16be
#घोषणा mmio_ग_लिखो16be(val,port) ग_लिखोw(swab16(val),port)
#घोषणा mmio_ग_लिखो32be(val,port) ग_लिखोl(swab32(val),port)
#घोषणा mmio_ग_लिखो64be(val,port) ग_लिखोq(swab64(val),port)
#पूर्ण_अगर

व्योम ioग_लिखो8(u8 val, व्योम __iomem *addr)
अणु
	IO_COND(addr, outb(val,port), ग_लिखोb(val, addr));
पूर्ण
व्योम ioग_लिखो16(u16 val, व्योम __iomem *addr)
अणु
	IO_COND(addr, outw(val,port), ग_लिखोw(val, addr));
पूर्ण
व्योम ioग_लिखो16be(u16 val, व्योम __iomem *addr)
अणु
	IO_COND(addr, pio_ग_लिखो16be(val,port), mmio_ग_लिखो16be(val, addr));
पूर्ण
व्योम ioग_लिखो32(u32 val, व्योम __iomem *addr)
अणु
	IO_COND(addr, outl(val,port), ग_लिखोl(val, addr));
पूर्ण
व्योम ioग_लिखो32be(u32 val, व्योम __iomem *addr)
अणु
	IO_COND(addr, pio_ग_लिखो32be(val,port), mmio_ग_लिखो32be(val, addr));
पूर्ण
EXPORT_SYMBOL(ioग_लिखो8);
EXPORT_SYMBOL(ioग_लिखो16);
EXPORT_SYMBOL(ioग_लिखो16be);
EXPORT_SYMBOL(ioग_लिखो32);
EXPORT_SYMBOL(ioग_लिखो32be);

#अगर_घोषित ग_लिखोq
अटल व्योम pio_ग_लिखो64_lo_hi(u64 val, अचिन्हित दीर्घ port)
अणु
	outl(val, port);
	outl(val >> 32, port + माप(u32));
पूर्ण

अटल व्योम pio_ग_लिखो64_hi_lo(u64 val, अचिन्हित दीर्घ port)
अणु
	outl(val >> 32, port + माप(u32));
	outl(val, port);
पूर्ण

अटल व्योम pio_ग_लिखो64be_lo_hi(u64 val, अचिन्हित दीर्घ port)
अणु
	pio_ग_लिखो32be(val, port + माप(u32));
	pio_ग_लिखो32be(val >> 32, port);
पूर्ण

अटल व्योम pio_ग_लिखो64be_hi_lo(u64 val, अचिन्हित दीर्घ port)
अणु
	pio_ग_लिखो32be(val >> 32, port);
	pio_ग_लिखो32be(val, port + माप(u32));
पूर्ण

व्योम ioग_लिखो64_lo_hi(u64 val, व्योम __iomem *addr)
अणु
	IO_COND(addr, pio_ग_लिखो64_lo_hi(val, port),
		ग_लिखोq(val, addr));
पूर्ण

व्योम ioग_लिखो64_hi_lo(u64 val, व्योम __iomem *addr)
अणु
	IO_COND(addr, pio_ग_लिखो64_hi_lo(val, port),
		ग_लिखोq(val, addr));
पूर्ण

व्योम ioग_लिखो64be_lo_hi(u64 val, व्योम __iomem *addr)
अणु
	IO_COND(addr, pio_ग_लिखो64be_lo_hi(val, port),
		mmio_ग_लिखो64be(val, addr));
पूर्ण

व्योम ioग_लिखो64be_hi_lo(u64 val, व्योम __iomem *addr)
अणु
	IO_COND(addr, pio_ग_लिखो64be_hi_lo(val, port),
		mmio_ग_लिखो64be(val, addr));
पूर्ण

EXPORT_SYMBOL(ioग_लिखो64_lo_hi);
EXPORT_SYMBOL(ioग_लिखो64_hi_lo);
EXPORT_SYMBOL(ioग_लिखो64be_lo_hi);
EXPORT_SYMBOL(ioग_लिखो64be_hi_lo);

#पूर्ण_अगर /* पढ़ोq */

/*
 * These are the "repeat MMIO read/write" functions.
 * Note the "__raw" accesses, since we करोn't want to
 * convert to CPU byte order. We ग_लिखो in "IO byte
 * order" (we also करोn't have IO barriers).
 */
#अगर_अघोषित mmio_insb
अटल अंतरभूत व्योम mmio_insb(स्थिर व्योम __iomem *addr, u8 *dst, पूर्णांक count)
अणु
	जबतक (--count >= 0) अणु
		u8 data = __raw_पढ़ोb(addr);
		*dst = data;
		dst++;
	पूर्ण
पूर्ण
अटल अंतरभूत व्योम mmio_insw(स्थिर व्योम __iomem *addr, u16 *dst, पूर्णांक count)
अणु
	जबतक (--count >= 0) अणु
		u16 data = __raw_पढ़ोw(addr);
		*dst = data;
		dst++;
	पूर्ण
पूर्ण
अटल अंतरभूत व्योम mmio_insl(स्थिर व्योम __iomem *addr, u32 *dst, पूर्णांक count)
अणु
	जबतक (--count >= 0) अणु
		u32 data = __raw_पढ़ोl(addr);
		*dst = data;
		dst++;
	पूर्ण
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित mmio_outsb
अटल अंतरभूत व्योम mmio_outsb(व्योम __iomem *addr, स्थिर u8 *src, पूर्णांक count)
अणु
	जबतक (--count >= 0) अणु
		__raw_ग_लिखोb(*src, addr);
		src++;
	पूर्ण
पूर्ण
अटल अंतरभूत व्योम mmio_outsw(व्योम __iomem *addr, स्थिर u16 *src, पूर्णांक count)
अणु
	जबतक (--count >= 0) अणु
		__raw_ग_लिखोw(*src, addr);
		src++;
	पूर्ण
पूर्ण
अटल अंतरभूत व्योम mmio_outsl(व्योम __iomem *addr, स्थिर u32 *src, पूर्णांक count)
अणु
	जबतक (--count >= 0) अणु
		__raw_ग_लिखोl(*src, addr);
		src++;
	पूर्ण
पूर्ण
#पूर्ण_अगर

व्योम ioपढ़ो8_rep(स्थिर व्योम __iomem *addr, व्योम *dst, अचिन्हित दीर्घ count)
अणु
	IO_COND(addr, insb(port,dst,count), mmio_insb(addr, dst, count));
पूर्ण
व्योम ioपढ़ो16_rep(स्थिर व्योम __iomem *addr, व्योम *dst, अचिन्हित दीर्घ count)
अणु
	IO_COND(addr, insw(port,dst,count), mmio_insw(addr, dst, count));
पूर्ण
व्योम ioपढ़ो32_rep(स्थिर व्योम __iomem *addr, व्योम *dst, अचिन्हित दीर्घ count)
अणु
	IO_COND(addr, insl(port,dst,count), mmio_insl(addr, dst, count));
पूर्ण
EXPORT_SYMBOL(ioपढ़ो8_rep);
EXPORT_SYMBOL(ioपढ़ो16_rep);
EXPORT_SYMBOL(ioपढ़ो32_rep);

व्योम ioग_लिखो8_rep(व्योम __iomem *addr, स्थिर व्योम *src, अचिन्हित दीर्घ count)
अणु
	IO_COND(addr, outsb(port, src, count), mmio_outsb(addr, src, count));
पूर्ण
व्योम ioग_लिखो16_rep(व्योम __iomem *addr, स्थिर व्योम *src, अचिन्हित दीर्घ count)
अणु
	IO_COND(addr, outsw(port, src, count), mmio_outsw(addr, src, count));
पूर्ण
व्योम ioग_लिखो32_rep(व्योम __iomem *addr, स्थिर व्योम *src, अचिन्हित दीर्घ count)
अणु
	IO_COND(addr, outsl(port, src,count), mmio_outsl(addr, src, count));
पूर्ण
EXPORT_SYMBOL(ioग_लिखो8_rep);
EXPORT_SYMBOL(ioग_लिखो16_rep);
EXPORT_SYMBOL(ioग_लिखो32_rep);

#अगर_घोषित CONFIG_HAS_IOPORT_MAP
/* Create a भव mapping cookie क्रम an IO port range */
व्योम __iomem *ioport_map(अचिन्हित दीर्घ port, अचिन्हित पूर्णांक nr)
अणु
	अगर (port > PIO_MASK)
		वापस शून्य;
	वापस (व्योम __iomem *) (अचिन्हित दीर्घ) (port + PIO_OFFSET);
पूर्ण

व्योम ioport_unmap(व्योम __iomem *addr)
अणु
	/* Nothing to करो */
पूर्ण
EXPORT_SYMBOL(ioport_map);
EXPORT_SYMBOL(ioport_unmap);
#पूर्ण_अगर /* CONFIG_HAS_IOPORT_MAP */

#अगर_घोषित CONFIG_PCI
/* Hide the details अगर this is a MMIO or PIO address space and just करो what
 * you expect in the correct way. */
व्योम pci_iounmap(काष्ठा pci_dev *dev, व्योम __iomem * addr)
अणु
	IO_COND(addr, /* nothing */, iounmap(addr));
पूर्ण
EXPORT_SYMBOL(pci_iounmap);
#पूर्ण_अगर /* CONFIG_PCI */
