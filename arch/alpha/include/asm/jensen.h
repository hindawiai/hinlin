<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ALPHA_JENSEN_H
#घोषणा __ALPHA_JENSEN_H

#समावेश <यंत्र/compiler.h>

/*
 * Defines क्रम the AlphaPC EISA IO and memory address space.
 */

/*
 * NOTE! The memory operations करो not set any memory barriers, as it's
 * not needed क्रम हालs like a frame buffer that is essentially memory-like.
 * You need to करो them by hand अगर the operations depend on ordering.
 *
 * Similarly, the port IO operations करो a "mb" only after a ग_लिखो operation:
 * अगर an mb is needed beक्रमe (as in the हाल of करोing memory mapped IO
 * first, and then a port IO operation to the same device), it needs to be
 * करोne by hand.
 *
 * After the above has bitten me 100 बार, I'll give up and just करो the
 * mb all the समय, but right now I'm hoping this will work out.  Aव्योमing
 * mb's may potentially be a noticeable speed improvement, but I can't
 * honestly say I've tested it.
 *
 * Handling पूर्णांकerrupts that need to करो mb's to synchronize to non-पूर्णांकerrupts
 * is another fun race area.  Don't do it (because if you do, I'll have to
 * करो *everything* with पूर्णांकerrupts disabled, ugh).
 */

/*
 * EISA Interrupt Acknowledge address
 */
#घोषणा EISA_INTA		(IDENT_ADDR + 0x100000000UL)

/*
 * FEPROM addresses
 */
#घोषणा EISA_FEPROM0		(IDENT_ADDR + 0x180000000UL)
#घोषणा EISA_FEPROM1		(IDENT_ADDR + 0x1A0000000UL)

/*
 * VL82C106 base address
 */
#घोषणा EISA_VL82C106		(IDENT_ADDR + 0x1C0000000UL)

/*
 * EISA "Host Address Extension" address (bits 25-31 of the EISA address)
 */
#घोषणा EISA_HAE		(IDENT_ADDR + 0x1D0000000UL)

/*
 * "SYSCTL" रेजिस्टर address
 */
#घोषणा EISA_SYSCTL		(IDENT_ADDR + 0x1E0000000UL)

/*
 * "spare" रेजिस्टर address
 */
#घोषणा EISA_SPARE		(IDENT_ADDR + 0x1F0000000UL)

/*
 * EISA memory address offset
 */
#घोषणा EISA_MEM		(IDENT_ADDR + 0x200000000UL)

/*
 * EISA IO address offset
 */
#घोषणा EISA_IO			(IDENT_ADDR + 0x300000000UL)


#अगर_घोषित __KERNEL__

#अगर_अघोषित __EXTERN_INLINE
#घोषणा __EXTERN_INLINE बाह्य अंतरभूत
#घोषणा __IO_EXTERN_INLINE
#पूर्ण_अगर

/*
 * Handle the "host address register". This needs to be set
 * to the high 7 bits of the EISA address.  This is also needed
 * क्रम EISA IO addresses, which are only 16 bits wide (the
 * hae needs to be set to 0).
 *
 * HAE isn't needed क्रम the local IO operations, though.
 */

#घोषणा JENSEN_HAE_ADDRESS	EISA_HAE
#घोषणा JENSEN_HAE_MASK		0x1ffffff

__EXTERN_INLINE व्योम jensen_set_hae(अचिन्हित दीर्घ addr)
अणु
	/* hae on the Jensen is bits 31:25 shअगरted right */
	addr >>= 25;
	अगर (addr != alpha_mv.hae_cache)
		set_hae(addr);
पूर्ण

#घोषणा vuip	अस्थिर अचिन्हित पूर्णांक *

/*
 * IO functions
 *
 * The "local" functions are those that करोn't go out to the EISA bus,
 * but instead act on the VL82C106 chip directly.. This is मुख्यly the
 * keyboard, RTC,  prपूर्णांकer and first two serial lines..
 *
 * The local stuff makes क्रम some complications, but it seems to be
 * gone in the PCI version. I hope I can get DEC suckered^H^H^H^H^H^H^H^H
 * convinced that I need one of the newer machines.
 */

अटल अंतरभूत अचिन्हित पूर्णांक jensen_local_inb(अचिन्हित दीर्घ addr)
अणु
	वापस 0xff & *(vuip)((addr << 9) + EISA_VL82C106);
पूर्ण

अटल अंतरभूत व्योम jensen_local_outb(u8 b, अचिन्हित दीर्घ addr)
अणु
	*(vuip)((addr << 9) + EISA_VL82C106) = b;
	mb();
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक jensen_bus_inb(अचिन्हित दीर्घ addr)
अणु
	दीर्घ result;

	jensen_set_hae(0);
	result = *(अस्थिर पूर्णांक *)((addr << 7) + EISA_IO + 0x00);
	वापस __kernel_extbl(result, addr & 3);
पूर्ण

अटल अंतरभूत व्योम jensen_bus_outb(u8 b, अचिन्हित दीर्घ addr)
अणु
	jensen_set_hae(0);
	*(vuip)((addr << 7) + EISA_IO + 0x00) = b * 0x01010101;
	mb();
पूर्ण

/*
 * It seems gcc is not very good at optimizing away logical
 * operations that result in operations across अंतरभूत functions.
 * Which is why this is a macro.
 */

#घोषणा jensen_is_local(addr) ( \
/* keyboard */	(addr == 0x60 || addr == 0x64) || \
/* RTC */	(addr == 0x170 || addr == 0x171) || \
/* mb COM2 */	(addr >= 0x2f8 && addr <= 0x2ff) || \
/* mb LPT1 */	(addr >= 0x3bc && addr <= 0x3be) || \
/* mb COM2 */	(addr >= 0x3f8 && addr <= 0x3ff))

__EXTERN_INLINE u8 jensen_inb(अचिन्हित दीर्घ addr)
अणु
	अगर (jensen_is_local(addr))
		वापस jensen_local_inb(addr);
	अन्यथा
		वापस jensen_bus_inb(addr);
पूर्ण

__EXTERN_INLINE व्योम jensen_outb(u8 b, अचिन्हित दीर्घ addr)
अणु
	अगर (jensen_is_local(addr))
		jensen_local_outb(b, addr);
	अन्यथा
		jensen_bus_outb(b, addr);
पूर्ण

__EXTERN_INLINE u16 jensen_inw(अचिन्हित दीर्घ addr)
अणु
	दीर्घ result;

	jensen_set_hae(0);
	result = *(अस्थिर पूर्णांक *) ((addr << 7) + EISA_IO + 0x20);
	result >>= (addr & 3) * 8;
	वापस 0xffffUL & result;
पूर्ण

__EXTERN_INLINE u32 jensen_inl(अचिन्हित दीर्घ addr)
अणु
	jensen_set_hae(0);
	वापस *(vuip) ((addr << 7) + EISA_IO + 0x60);
पूर्ण

__EXTERN_INLINE व्योम jensen_outw(u16 b, अचिन्हित दीर्घ addr)
अणु
	jensen_set_hae(0);
	*(vuip) ((addr << 7) + EISA_IO + 0x20) = b * 0x00010001;
	mb();
पूर्ण

__EXTERN_INLINE व्योम jensen_outl(u32 b, अचिन्हित दीर्घ addr)
अणु
	jensen_set_hae(0);
	*(vuip) ((addr << 7) + EISA_IO + 0x60) = b;
	mb();
पूर्ण

/*
 * Memory functions.
 */

__EXTERN_INLINE u8 jensen_पढ़ोb(स्थिर अस्थिर व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr;
	दीर्घ result;

	jensen_set_hae(addr);
	addr &= JENSEN_HAE_MASK;
	result = *(अस्थिर पूर्णांक *) ((addr << 7) + EISA_MEM + 0x00);
	result >>= (addr & 3) * 8;
	वापस 0xffUL & result;
पूर्ण

__EXTERN_INLINE u16 jensen_पढ़ोw(स्थिर अस्थिर व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr;
	दीर्घ result;

	jensen_set_hae(addr);
	addr &= JENSEN_HAE_MASK;
	result = *(अस्थिर पूर्णांक *) ((addr << 7) + EISA_MEM + 0x20);
	result >>= (addr & 3) * 8;
	वापस 0xffffUL & result;
पूर्ण

__EXTERN_INLINE u32 jensen_पढ़ोl(स्थिर अस्थिर व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr;
	jensen_set_hae(addr);
	addr &= JENSEN_HAE_MASK;
	वापस *(vuip) ((addr << 7) + EISA_MEM + 0x60);
पूर्ण

__EXTERN_INLINE u64 jensen_पढ़ोq(स्थिर अस्थिर व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr;
	अचिन्हित दीर्घ r0, r1;

	jensen_set_hae(addr);
	addr &= JENSEN_HAE_MASK;
	addr = (addr << 7) + EISA_MEM + 0x60;
	r0 = *(vuip) (addr);
	r1 = *(vuip) (addr + (4 << 7));
	वापस r1 << 32 | r0;
पूर्ण

__EXTERN_INLINE व्योम jensen_ग_लिखोb(u8 b, अस्थिर व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr;
	jensen_set_hae(addr);
	addr &= JENSEN_HAE_MASK;
	*(vuip) ((addr << 7) + EISA_MEM + 0x00) = b * 0x01010101;
पूर्ण

__EXTERN_INLINE व्योम jensen_ग_लिखोw(u16 b, अस्थिर व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr;
	jensen_set_hae(addr);
	addr &= JENSEN_HAE_MASK;
	*(vuip) ((addr << 7) + EISA_MEM + 0x20) = b * 0x00010001;
पूर्ण

__EXTERN_INLINE व्योम jensen_ग_लिखोl(u32 b, अस्थिर व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr;
	jensen_set_hae(addr);
	addr &= JENSEN_HAE_MASK;
	*(vuip) ((addr << 7) + EISA_MEM + 0x60) = b;
पूर्ण

__EXTERN_INLINE व्योम jensen_ग_लिखोq(u64 b, अस्थिर व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr;
	jensen_set_hae(addr);
	addr &= JENSEN_HAE_MASK;
	addr = (addr << 7) + EISA_MEM + 0x60;
	*(vuip) (addr) = b;
	*(vuip) (addr + (4 << 7)) = b >> 32;
पूर्ण

__EXTERN_INLINE व्योम __iomem *jensen_ioporपंचांगap(अचिन्हित दीर्घ addr)
अणु
	वापस (व्योम __iomem *)addr;
पूर्ण

__EXTERN_INLINE व्योम __iomem *jensen_ioremap(अचिन्हित दीर्घ addr,
					     अचिन्हित दीर्घ size)
अणु
	वापस (व्योम __iomem *)(addr + 0x100000000ul);
पूर्ण

__EXTERN_INLINE पूर्णांक jensen_is_ioaddr(अचिन्हित दीर्घ addr)
अणु
	वापस (दीर्घ)addr >= 0;
पूर्ण

__EXTERN_INLINE पूर्णांक jensen_is_mmio(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस (अचिन्हित दीर्घ)addr >= 0x100000000ul;
पूर्ण

/* New-style ioपढ़ो पूर्णांकerface.  All the routines are so ugly क्रम Jensen
   that it करोesn't make sense to merge them.  */

#घोषणा IOPORT(OS, NS)							\
__EXTERN_INLINE अचिन्हित पूर्णांक jensen_ioपढ़ो##NS(स्थिर व्योम __iomem *xaddr)	\
अणु									\
	अगर (jensen_is_mmio(xaddr))					\
		वापस jensen_पढ़ो##OS(xaddr - 0x100000000ul);		\
	अन्यथा								\
		वापस jensen_in##OS((अचिन्हित दीर्घ)xaddr);		\
पूर्ण									\
__EXTERN_INLINE व्योम jensen_ioग_लिखो##NS(u##NS b, व्योम __iomem *xaddr)	\
अणु									\
	अगर (jensen_is_mmio(xaddr))					\
		jensen_ग_लिखो##OS(b, xaddr - 0x100000000ul);		\
	अन्यथा								\
		jensen_out##OS(b, (अचिन्हित दीर्घ)xaddr);		\
पूर्ण

IOPORT(b, 8)
IOPORT(w, 16)
IOPORT(l, 32)

#अघोषित IOPORT

#अघोषित vuip

#अघोषित __IO_PREFIX
#घोषणा __IO_PREFIX		jensen
#घोषणा jensen_trivial_rw_bw	0
#घोषणा jensen_trivial_rw_lq	0
#घोषणा jensen_trivial_io_bw	0
#घोषणा jensen_trivial_io_lq	0
#घोषणा jensen_trivial_iounmap	1
#समावेश <यंत्र/io_trivial.h>

#अगर_घोषित __IO_EXTERN_INLINE
#अघोषित __EXTERN_INLINE
#अघोषित __IO_EXTERN_INLINE
#पूर्ण_अगर

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* __ALPHA_JENSEN_H */
