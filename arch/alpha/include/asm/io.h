<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ALPHA_IO_H
#घोषणा __ALPHA_IO_H

#अगर_घोषित __KERNEL__

#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र/compiler.h>
#समावेश <यंत्र/machvec.h>
#समावेश <यंत्र/hwrpb.h>

/* The generic header contains only prototypes.  Including it ensures that
   the implementation we have here matches that पूर्णांकerface.  */
#समावेश <यंत्र-generic/iomap.h>

/* We करोn't use IO slowकरोwns on the Alpha, but.. */
#घोषणा __SLOW_DOWN_IO	करो अणु पूर्ण जबतक (0)
#घोषणा SLOW_DOWN_IO	करो अणु पूर्ण जबतक (0)

/*
 * Virtual -> physical identity mapping starts at this offset
 */
#अगर_घोषित USE_48_BIT_KSEG
#घोषणा IDENT_ADDR     0xffff800000000000UL
#अन्यथा
#घोषणा IDENT_ADDR     0xfffffc0000000000UL
#पूर्ण_अगर

/*
 * We try to aव्योम hae updates (thus the cache), but when we
 * करो need to update the hae, we need to करो it atomically, so
 * that any पूर्णांकerrupts wouldn't get confused with the hae
 * रेजिस्टर not being up-to-date with respect to the hardware
 * value.
 */
बाह्य अंतरभूत व्योम __set_hae(अचिन्हित दीर्घ new_hae)
अणु
	अचिन्हित दीर्घ flags = swpipl(IPL_MAX);

	barrier();

	alpha_mv.hae_cache = new_hae;
	*alpha_mv.hae_रेजिस्टर = new_hae;
	mb();
	/* Re-पढ़ो to make sure it was written.  */
	new_hae = *alpha_mv.hae_रेजिस्टर;

	setipl(flags);
	barrier();
पूर्ण

बाह्य अंतरभूत व्योम set_hae(अचिन्हित दीर्घ new_hae)
अणु
	अगर (new_hae != alpha_mv.hae_cache)
		__set_hae(new_hae);
पूर्ण

/*
 * Change भव addresses to physical addresses and vv.
 */
#अगर_घोषित USE_48_BIT_KSEG
अटल अंतरभूत अचिन्हित दीर्घ virt_to_phys(व्योम *address)
अणु
	वापस (अचिन्हित दीर्घ)address - IDENT_ADDR;
पूर्ण

अटल अंतरभूत व्योम * phys_to_virt(अचिन्हित दीर्घ address)
अणु
	वापस (व्योम *) (address + IDENT_ADDR);
पूर्ण
#अन्यथा
अटल अंतरभूत अचिन्हित दीर्घ virt_to_phys(व्योम *address)
अणु
        अचिन्हित दीर्घ phys = (अचिन्हित दीर्घ)address;

	/* Sign-extend from bit 41.  */
	phys <<= (64 - 41);
	phys = (दीर्घ)phys >> (64 - 41);

	/* Crop to the physical address width of the processor.  */
        phys &= (1ul << hwrpb->pa_bits) - 1;

        वापस phys;
पूर्ण

अटल अंतरभूत व्योम * phys_to_virt(अचिन्हित दीर्घ address)
अणु
        वापस (व्योम *)(IDENT_ADDR + (address & ((1ul << 41) - 1)));
पूर्ण
#पूर्ण_अगर

#घोषणा page_to_phys(page)	page_to_pa(page)

/* Maximum PIO space address supported?  */
#घोषणा IO_SPACE_LIMIT 0xffff

/*
 * Change addresses as seen by the kernel (भव) to addresses as
 * seen by a device (bus), and vice versa.
 *
 * Note that this only works क्रम a limited range of kernel addresses,
 * and very well may not span all memory.  Consider this पूर्णांकerface 
 * deprecated in favour of the DMA-mapping API.
 */
बाह्य अचिन्हित दीर्घ __direct_map_base;
बाह्य अचिन्हित दीर्घ __direct_map_size;

अटल अंतरभूत अचिन्हित दीर्घ __deprecated virt_to_bus(व्योम *address)
अणु
	अचिन्हित दीर्घ phys = virt_to_phys(address);
	अचिन्हित दीर्घ bus = phys + __direct_map_base;
	वापस phys <= __direct_map_size ? bus : 0;
पूर्ण
#घोषणा isa_virt_to_bus virt_to_bus

अटल अंतरभूत व्योम * __deprecated bus_to_virt(अचिन्हित दीर्घ address)
अणु
	व्योम *virt;

	/* This check is a sanity check but also ensures that bus address 0
	   maps to भव address 0 which is useful to detect null poपूर्णांकers
	   (the NCR driver is much simpler अगर शून्य poपूर्णांकers are preserved).  */
	address -= __direct_map_base;
	virt = phys_to_virt(address);
	वापस (दीर्घ)address <= 0 ? शून्य : virt;
पूर्ण
#घोषणा isa_bus_to_virt bus_to_virt

/*
 * There are dअगरferent chipsets to पूर्णांकerface the Alpha CPUs to the world.
 */

#घोषणा IO_CONCAT(a,b)	_IO_CONCAT(a,b)
#घोषणा _IO_CONCAT(a,b)	a ## _ ## b

#अगर_घोषित CONFIG_ALPHA_GENERIC

/* In a generic kernel, we always go through the machine vector.  */

#घोषणा REMAP1(TYPE, NAME, QUAL)					\
अटल अंतरभूत TYPE generic_##NAME(QUAL व्योम __iomem *addr)		\
अणु									\
	वापस alpha_mv.mv_##NAME(addr);				\
पूर्ण

#घोषणा REMAP2(TYPE, NAME, QUAL)					\
अटल अंतरभूत व्योम generic_##NAME(TYPE b, QUAL व्योम __iomem *addr)	\
अणु									\
	alpha_mv.mv_##NAME(b, addr);					\
पूर्ण

REMAP1(अचिन्हित पूर्णांक, ioपढ़ो8, स्थिर)
REMAP1(अचिन्हित पूर्णांक, ioपढ़ो16, स्थिर)
REMAP1(अचिन्हित पूर्णांक, ioपढ़ो32, स्थिर)
REMAP1(u8, पढ़ोb, स्थिर अस्थिर)
REMAP1(u16, पढ़ोw, स्थिर अस्थिर)
REMAP1(u32, पढ़ोl, स्थिर अस्थिर)
REMAP1(u64, पढ़ोq, स्थिर अस्थिर)

REMAP2(u8, ioग_लिखो8, /**/)
REMAP2(u16, ioग_लिखो16, /**/)
REMAP2(u32, ioग_लिखो32, /**/)
REMAP2(u8, ग_लिखोb, अस्थिर)
REMAP2(u16, ग_लिखोw, अस्थिर)
REMAP2(u32, ग_लिखोl, अस्थिर)
REMAP2(u64, ग_लिखोq, अस्थिर)

#अघोषित REMAP1
#अघोषित REMAP2

बाह्य अंतरभूत व्योम __iomem *generic_ioporपंचांगap(अचिन्हित दीर्घ a)
अणु
	वापस alpha_mv.mv_ioporपंचांगap(a);
पूर्ण

अटल अंतरभूत व्योम __iomem *generic_ioremap(अचिन्हित दीर्घ a, अचिन्हित दीर्घ s)
अणु
	वापस alpha_mv.mv_ioremap(a, s);
पूर्ण

अटल अंतरभूत व्योम generic_iounmap(अस्थिर व्योम __iomem *a)
अणु
	वापस alpha_mv.mv_iounmap(a);
पूर्ण

अटल अंतरभूत पूर्णांक generic_is_ioaddr(अचिन्हित दीर्घ a)
अणु
	वापस alpha_mv.mv_is_ioaddr(a);
पूर्ण

अटल अंतरभूत पूर्णांक generic_is_mmio(स्थिर अस्थिर व्योम __iomem *a)
अणु
	वापस alpha_mv.mv_is_mmio(a);
पूर्ण

#घोषणा __IO_PREFIX		generic
#घोषणा generic_trivial_rw_bw	0
#घोषणा generic_trivial_rw_lq	0
#घोषणा generic_trivial_io_bw	0
#घोषणा generic_trivial_io_lq	0
#घोषणा generic_trivial_iounmap	0

#अन्यथा

#अगर defined(CONFIG_ALPHA_APECS)
# include <यंत्र/core_apecs.h>
#या_अगर defined(CONFIG_ALPHA_CIA)
# include <यंत्र/core_cia.h>
#या_अगर defined(CONFIG_ALPHA_IRONGATE)
# include <यंत्र/core_irongate.h>
#या_अगर defined(CONFIG_ALPHA_JENSEN)
# include <यंत्र/jensen.h>
#या_अगर defined(CONFIG_ALPHA_LCA)
# include <यंत्र/core_lca.h>
#या_अगर defined(CONFIG_ALPHA_MARVEL)
# include <यंत्र/core_marvel.h>
#या_अगर defined(CONFIG_ALPHA_MCPCIA)
# include <यंत्र/core_mcpcia.h>
#या_अगर defined(CONFIG_ALPHA_POLARIS)
# include <यंत्र/core_polaris.h>
#या_अगर defined(CONFIG_ALPHA_T2)
# include <यंत्र/core_t2.h>
#या_अगर defined(CONFIG_ALPHA_TSUNAMI)
# include <यंत्र/core_tsunami.h>
#या_अगर defined(CONFIG_ALPHA_TITAN)
# include <यंत्र/core_titan.h>
#या_अगर defined(CONFIG_ALPHA_WILDFIRE)
# include <यंत्र/core_wildfire.h>
#अन्यथा
#त्रुटि "What system is this?"
#पूर्ण_अगर

#पूर्ण_अगर /* GENERIC */

/*
 * We always have बाह्यal versions of these routines.
 */
बाह्य u8		inb(अचिन्हित दीर्घ port);
बाह्य u16		inw(अचिन्हित दीर्घ port);
बाह्य u32		inl(अचिन्हित दीर्घ port);
बाह्य व्योम		outb(u8 b, अचिन्हित दीर्घ port);
बाह्य व्योम		outw(u16 b, अचिन्हित दीर्घ port);
बाह्य व्योम		outl(u32 b, अचिन्हित दीर्घ port);

बाह्य u8		पढ़ोb(स्थिर अस्थिर व्योम __iomem *addr);
बाह्य u16		पढ़ोw(स्थिर अस्थिर व्योम __iomem *addr);
बाह्य u32		पढ़ोl(स्थिर अस्थिर व्योम __iomem *addr);
बाह्य u64		पढ़ोq(स्थिर अस्थिर व्योम __iomem *addr);
बाह्य व्योम		ग_लिखोb(u8 b, अस्थिर व्योम __iomem *addr);
बाह्य व्योम		ग_लिखोw(u16 b, अस्थिर व्योम __iomem *addr);
बाह्य व्योम		ग_लिखोl(u32 b, अस्थिर व्योम __iomem *addr);
बाह्य व्योम		ग_लिखोq(u64 b, अस्थिर व्योम __iomem *addr);

बाह्य u8		__raw_पढ़ोb(स्थिर अस्थिर व्योम __iomem *addr);
बाह्य u16		__raw_पढ़ोw(स्थिर अस्थिर व्योम __iomem *addr);
बाह्य u32		__raw_पढ़ोl(स्थिर अस्थिर व्योम __iomem *addr);
बाह्य u64		__raw_पढ़ोq(स्थिर अस्थिर व्योम __iomem *addr);
बाह्य व्योम		__raw_ग_लिखोb(u8 b, अस्थिर व्योम __iomem *addr);
बाह्य व्योम		__raw_ग_लिखोw(u16 b, अस्थिर व्योम __iomem *addr);
बाह्य व्योम		__raw_ग_लिखोl(u32 b, अस्थिर व्योम __iomem *addr);
बाह्य व्योम		__raw_ग_लिखोq(u64 b, अस्थिर व्योम __iomem *addr);

/*
 * Mapping from port numbers to __iomem space is pretty easy.
 */

/* These two have to be बाह्य अंतरभूत because of the बाह्य prototype from
   <यंत्र-generic/iomap.h>.  It is not legal to mix "extern" and "static" क्रम
   the same declaration.  */
बाह्य अंतरभूत व्योम __iomem *ioport_map(अचिन्हित दीर्घ port, अचिन्हित पूर्णांक size)
अणु
	वापस IO_CONCAT(__IO_PREFIX,ioporपंचांगap) (port);
पूर्ण

बाह्य अंतरभूत व्योम ioport_unmap(व्योम __iomem *addr)
अणु
पूर्ण

अटल अंतरभूत व्योम __iomem *ioremap(अचिन्हित दीर्घ port, अचिन्हित दीर्घ size)
अणु
	वापस IO_CONCAT(__IO_PREFIX,ioremap) (port, size);
पूर्ण

#घोषणा ioremap_wc ioremap
#घोषणा ioremap_uc ioremap

अटल अंतरभूत व्योम iounmap(अस्थिर व्योम __iomem *addr)
अणु
	IO_CONCAT(__IO_PREFIX,iounmap)(addr);
पूर्ण

अटल अंतरभूत पूर्णांक __is_ioaddr(अचिन्हित दीर्घ addr)
अणु
	वापस IO_CONCAT(__IO_PREFIX,is_ioaddr)(addr);
पूर्ण
#घोषणा __is_ioaddr(a)		__is_ioaddr((अचिन्हित दीर्घ)(a))

अटल अंतरभूत पूर्णांक __is_mmio(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस IO_CONCAT(__IO_PREFIX,is_mmio)(addr);
पूर्ण


/*
 * If the actual I/O bits are sufficiently trivial, then expand अंतरभूत.
 */

#अगर IO_CONCAT(__IO_PREFIX,trivial_io_bw)
बाह्य अंतरभूत अचिन्हित पूर्णांक ioपढ़ो8(स्थिर व्योम __iomem *addr)
अणु
	अचिन्हित पूर्णांक ret;
	mb();
	ret = IO_CONCAT(__IO_PREFIX,ioपढ़ो8)(addr);
	mb();
	वापस ret;
पूर्ण

बाह्य अंतरभूत अचिन्हित पूर्णांक ioपढ़ो16(स्थिर व्योम __iomem *addr)
अणु
	अचिन्हित पूर्णांक ret;
	mb();
	ret = IO_CONCAT(__IO_PREFIX,ioपढ़ो16)(addr);
	mb();
	वापस ret;
पूर्ण

बाह्य अंतरभूत व्योम ioग_लिखो8(u8 b, व्योम __iomem *addr)
अणु
	mb();
	IO_CONCAT(__IO_PREFIX, ioग_लिखो8)(b, addr);
पूर्ण

बाह्य अंतरभूत व्योम ioग_लिखो16(u16 b, व्योम __iomem *addr)
अणु
	mb();
	IO_CONCAT(__IO_PREFIX, ioग_लिखो16)(b, addr);
पूर्ण

बाह्य अंतरभूत u8 inb(अचिन्हित दीर्घ port)
अणु
	वापस ioपढ़ो8(ioport_map(port, 1));
पूर्ण

बाह्य अंतरभूत u16 inw(अचिन्हित दीर्घ port)
अणु
	वापस ioपढ़ो16(ioport_map(port, 2));
पूर्ण

बाह्य अंतरभूत व्योम outb(u8 b, अचिन्हित दीर्घ port)
अणु
	ioग_लिखो8(b, ioport_map(port, 1));
पूर्ण

बाह्य अंतरभूत व्योम outw(u16 b, अचिन्हित दीर्घ port)
अणु
	ioग_लिखो16(b, ioport_map(port, 2));
पूर्ण
#पूर्ण_अगर

#अगर IO_CONCAT(__IO_PREFIX,trivial_io_lq)
बाह्य अंतरभूत अचिन्हित पूर्णांक ioपढ़ो32(स्थिर व्योम __iomem *addr)
अणु
	अचिन्हित पूर्णांक ret;
	mb();
	ret = IO_CONCAT(__IO_PREFIX,ioपढ़ो32)(addr);
	mb();
	वापस ret;
पूर्ण

बाह्य अंतरभूत व्योम ioग_लिखो32(u32 b, व्योम __iomem *addr)
अणु
	mb();
	IO_CONCAT(__IO_PREFIX, ioग_लिखो32)(b, addr);
पूर्ण

बाह्य अंतरभूत u32 inl(अचिन्हित दीर्घ port)
अणु
	वापस ioपढ़ो32(ioport_map(port, 4));
पूर्ण

बाह्य अंतरभूत व्योम outl(u32 b, अचिन्हित दीर्घ port)
अणु
	ioग_लिखो32(b, ioport_map(port, 4));
पूर्ण
#पूर्ण_अगर

#अगर IO_CONCAT(__IO_PREFIX,trivial_rw_bw) == 1
बाह्य अंतरभूत u8 __raw_पढ़ोb(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस IO_CONCAT(__IO_PREFIX,पढ़ोb)(addr);
पूर्ण

बाह्य अंतरभूत u16 __raw_पढ़ोw(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस IO_CONCAT(__IO_PREFIX,पढ़ोw)(addr);
पूर्ण

बाह्य अंतरभूत व्योम __raw_ग_लिखोb(u8 b, अस्थिर व्योम __iomem *addr)
अणु
	IO_CONCAT(__IO_PREFIX,ग_लिखोb)(b, addr);
पूर्ण

बाह्य अंतरभूत व्योम __raw_ग_लिखोw(u16 b, अस्थिर व्योम __iomem *addr)
अणु
	IO_CONCAT(__IO_PREFIX,ग_लिखोw)(b, addr);
पूर्ण

बाह्य अंतरभूत u8 पढ़ोb(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u8 ret;
	mb();
	ret = __raw_पढ़ोb(addr);
	mb();
	वापस ret;
पूर्ण

बाह्य अंतरभूत u16 पढ़ोw(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u16 ret;
	mb();
	ret = __raw_पढ़ोw(addr);
	mb();
	वापस ret;
पूर्ण

बाह्य अंतरभूत व्योम ग_लिखोb(u8 b, अस्थिर व्योम __iomem *addr)
अणु
	mb();
	__raw_ग_लिखोb(b, addr);
पूर्ण

बाह्य अंतरभूत व्योम ग_लिखोw(u16 b, अस्थिर व्योम __iomem *addr)
अणु
	mb();
	__raw_ग_लिखोw(b, addr);
पूर्ण
#पूर्ण_अगर

#अगर IO_CONCAT(__IO_PREFIX,trivial_rw_lq) == 1
बाह्य अंतरभूत u32 __raw_पढ़ोl(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस IO_CONCAT(__IO_PREFIX,पढ़ोl)(addr);
पूर्ण

बाह्य अंतरभूत u64 __raw_पढ़ोq(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस IO_CONCAT(__IO_PREFIX,पढ़ोq)(addr);
पूर्ण

बाह्य अंतरभूत व्योम __raw_ग_लिखोl(u32 b, अस्थिर व्योम __iomem *addr)
अणु
	IO_CONCAT(__IO_PREFIX,ग_लिखोl)(b, addr);
पूर्ण

बाह्य अंतरभूत व्योम __raw_ग_लिखोq(u64 b, अस्थिर व्योम __iomem *addr)
अणु
	IO_CONCAT(__IO_PREFIX,ग_लिखोq)(b, addr);
पूर्ण

बाह्य अंतरभूत u32 पढ़ोl(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u32 ret;
	mb();
	ret = __raw_पढ़ोl(addr);
	mb();
	वापस ret;
पूर्ण

बाह्य अंतरभूत u64 पढ़ोq(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u64 ret;
	mb();
	ret = __raw_पढ़ोq(addr);
	mb();
	वापस ret;
पूर्ण

बाह्य अंतरभूत व्योम ग_लिखोl(u32 b, अस्थिर व्योम __iomem *addr)
अणु
	mb();
	__raw_ग_लिखोl(b, addr);
पूर्ण

बाह्य अंतरभूत व्योम ग_लिखोq(u64 b, अस्थिर व्योम __iomem *addr)
अणु
	mb();
	__raw_ग_लिखोq(b, addr);
पूर्ण
#पूर्ण_अगर

#घोषणा ioपढ़ो16be(p) swab16(ioपढ़ो16(p))
#घोषणा ioपढ़ो32be(p) swab32(ioपढ़ो32(p))
#घोषणा ioग_लिखो16be(v,p) ioग_लिखो16(swab16(v), (p))
#घोषणा ioग_लिखो32be(v,p) ioग_लिखो32(swab32(v), (p))

#घोषणा inb_p		inb
#घोषणा inw_p		inw
#घोषणा inl_p		inl
#घोषणा outb_p		outb
#घोषणा outw_p		outw
#घोषणा outl_p		outl

बाह्य u8 पढ़ोb_relaxed(स्थिर अस्थिर व्योम __iomem *addr);
बाह्य u16 पढ़ोw_relaxed(स्थिर अस्थिर व्योम __iomem *addr);
बाह्य u32 पढ़ोl_relaxed(स्थिर अस्थिर व्योम __iomem *addr);
बाह्य u64 पढ़ोq_relaxed(स्थिर अस्थिर व्योम __iomem *addr);

#अगर IO_CONCAT(__IO_PREFIX,trivial_io_bw)
बाह्य अंतरभूत u8 पढ़ोb_relaxed(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	mb();
	वापस __raw_पढ़ोb(addr);
पूर्ण

बाह्य अंतरभूत u16 पढ़ोw_relaxed(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	mb();
	वापस __raw_पढ़ोw(addr);
पूर्ण
#पूर्ण_अगर

#अगर IO_CONCAT(__IO_PREFIX,trivial_io_lq)
बाह्य अंतरभूत u32 पढ़ोl_relaxed(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	mb();
	वापस __raw_पढ़ोl(addr);
पूर्ण

बाह्य अंतरभूत u64 पढ़ोq_relaxed(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	mb();
	वापस __raw_पढ़ोq(addr);
पूर्ण
#पूर्ण_अगर

#घोषणा ग_लिखोb_relaxed	ग_लिखोb
#घोषणा ग_लिखोw_relaxed	ग_लिखोw
#घोषणा ग_लिखोl_relaxed	ग_लिखोl
#घोषणा ग_लिखोq_relaxed	ग_लिखोq

/*
 * String version of IO memory access ops:
 */
बाह्य व्योम स_नकल_fromio(व्योम *, स्थिर अस्थिर व्योम __iomem *, दीर्घ);
बाह्य व्योम स_नकल_toio(अस्थिर व्योम __iomem *, स्थिर व्योम *, दीर्घ);
बाह्य व्योम _स_रखो_c_io(अस्थिर व्योम __iomem *, अचिन्हित दीर्घ, दीर्घ);

अटल अंतरभूत व्योम स_रखो_io(अस्थिर व्योम __iomem *addr, u8 c, दीर्घ len)
अणु
	_स_रखो_c_io(addr, 0x0101010101010101UL * c, len);
पूर्ण

#घोषणा __HAVE_ARCH_MEMSETW_IO
अटल अंतरभूत व्योम स_रखोw_io(अस्थिर व्योम __iomem *addr, u16 c, दीर्घ len)
अणु
	_स_रखो_c_io(addr, 0x0001000100010001UL * c, len);
पूर्ण

/*
 * String versions of in/out ops:
 */
बाह्य व्योम insb (अचिन्हित दीर्घ port, व्योम *dst, अचिन्हित दीर्घ count);
बाह्य व्योम insw (अचिन्हित दीर्घ port, व्योम *dst, अचिन्हित दीर्घ count);
बाह्य व्योम insl (अचिन्हित दीर्घ port, व्योम *dst, अचिन्हित दीर्घ count);
बाह्य व्योम outsb (अचिन्हित दीर्घ port, स्थिर व्योम *src, अचिन्हित दीर्घ count);
बाह्य व्योम outsw (अचिन्हित दीर्घ port, स्थिर व्योम *src, अचिन्हित दीर्घ count);
बाह्य व्योम outsl (अचिन्हित दीर्घ port, स्थिर व्योम *src, अचिन्हित दीर्घ count);

/*
 * The Alpha Jensen hardware क्रम some rather strange reason माला_दो
 * the RTC घड़ी at 0x170 instead of 0x70. Probably due to some
 * misguided idea about using 0x70 क्रम NMI stuff.
 *
 * These defines will override the शेषs when करोing RTC queries
 */

#अगर_घोषित CONFIG_ALPHA_GENERIC
# define RTC_PORT(x)	((x) + alpha_mv.rtc_port)
#अन्यथा
# अगरdef CONFIG_ALPHA_JENSEN
#  define RTC_PORT(x)	(0x170+(x))
# अन्यथा
#  define RTC_PORT(x)	(0x70 + (x))
# endअगर
#पूर्ण_अगर
#घोषणा RTC_ALWAYS_BCD	0

/*
 * Some mucking क्रमons use अगर[n]def ग_लिखोq to check अगर platक्रमm has it.
 * It's a bloody bad idea and we probably want ARCH_HAS_WRITEQ क्रम them
 * to play with; क्रम now just use cpp anti-recursion logics and make sure
 * that damn thing is defined and expands to itself.
 */

#घोषणा ग_लिखोq ग_लिखोq
#घोषणा पढ़ोq पढ़ोq

/*
 * Convert a physical poपूर्णांकer to a भव kernel poपूर्णांकer क्रम /dev/mem
 * access
 */
#घोषणा xlate_dev_mem_ptr(p)	__va(p)

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* __ALPHA_IO_H */
