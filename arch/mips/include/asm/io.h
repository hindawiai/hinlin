<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1994, 1995 Walकरोrf GmbH
 * Copyright (C) 1994 - 2000, 06 Ralf Baechle
 * Copyright (C) 1999, 2000 Silicon Graphics, Inc.
 * Copyright (C) 2004, 2005  MIPS Technologies, Inc.  All rights reserved.
 *	Author: Maciej W. Rozycki <macro@mips.com>
 */
#अगर_अघोषित _ASM_IO_H
#घोषणा _ASM_IO_H

#घोषणा ARCH_HAS_IOREMAP_WC

#समावेश <linux/compiler.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/irqflags.h>

#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/bug.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/cpu-features.h>
#समावेश <यंत्र-generic/iomap.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/pgtable-bits.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/माला.स>
#समावेश <mangle-port.h>

/*
 * Raw operations are never swapped in software.  OTOH values that raw
 * operations are working on may or may not have been swapped by the bus
 * hardware.  An example use would be क्रम flash memory that's used क्रम
 * execute in place.
 */
# define __raw_ioswabb(a, x)	(x)
# define __raw_ioswabw(a, x)	(x)
# define __raw_ioswabl(a, x)	(x)
# define __raw_ioswabq(a, x)	(x)
# define ____raw_ioswabq(a, x)	(x)

# define __relaxed_ioswabb ioswabb
# define __relaxed_ioswabw ioswabw
# define __relaxed_ioswabl ioswabl
# define __relaxed_ioswabq ioswabq

/* ioswab[bwlq], __mem_ioswab[bwlq] are defined in mangle-port.h */

/*
 * On MIPS I/O ports are memory mapped, so we access them using normal
 * load/store inकाष्ठाions. mips_io_port_base is the भव address to
 * which all ports are being mapped.  For sake of efficiency some code
 * assumes that this is an address that can be loaded with a single lui
 * inकाष्ठाion, so the lower 16 bits must be zero.  Should be true on
 * any sane architecture; generic code करोes not use this assumption.
 */
बाह्य अचिन्हित दीर्घ mips_io_port_base;

अटल अंतरभूत व्योम set_io_port_base(अचिन्हित दीर्घ base)
अणु
	mips_io_port_base = base;
पूर्ण

/*
 * Provide the necessary definitions क्रम generic iomap. We make use of
 * mips_io_port_base क्रम iomap(), but we करोn't reserve any low addresses क्रम
 * use with I/O ports.
 */

#घोषणा HAVE_ARCH_PIO_SIZE
#घोषणा PIO_OFFSET	mips_io_port_base
#घोषणा PIO_MASK	IO_SPACE_LIMIT
#घोषणा PIO_RESERVED	0x0UL

/*
 * Enक्रमce in-order execution of data I/O.  In the MIPS architecture
 * these are equivalent to corresponding platक्रमm-specअगरic memory
 * barriers defined in <यंत्र/barrier.h>.  API pinched from PowerPC,
 * with sync additionally defined.
 */
#घोषणा iobarrier_rw() mb()
#घोषणा iobarrier_r() rmb()
#घोषणा iobarrier_w() wmb()
#घोषणा iobarrier_sync() iob()

/*
 *     virt_to_phys    -       map भव addresses to physical
 *     @address: address to remap
 *
 *     The वापसed physical address is the physical (CPU) mapping क्रम
 *     the memory address given. It is only valid to use this function on
 *     addresses directly mapped or allocated via kदो_स्मृति.
 *
 *     This function करोes not give bus mappings क्रम DMA transfers. In
 *     almost all conceivable हालs a device driver should not be using
 *     this function
 */
अटल अंतरभूत अचिन्हित दीर्घ __virt_to_phys_nodebug(अस्थिर स्थिर व्योम *address)
अणु
	वापस __pa(address);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_VIRTUAL
बाह्य phys_addr_t __virt_to_phys(अस्थिर स्थिर व्योम *x);
#अन्यथा
#घोषणा __virt_to_phys(x)	__virt_to_phys_nodebug(x)
#पूर्ण_अगर

#घोषणा virt_to_phys virt_to_phys
अटल अंतरभूत phys_addr_t virt_to_phys(स्थिर अस्थिर व्योम *x)
अणु
	वापस __virt_to_phys(x);
पूर्ण

/*
 *     phys_to_virt    -       map physical address to भव
 *     @address: address to remap
 *
 *     The वापसed भव address is a current CPU mapping क्रम
 *     the memory address given. It is only valid to use this function on
 *     addresses that have a kernel mapping
 *
 *     This function करोes not handle bus mappings क्रम DMA transfers. In
 *     almost all conceivable हालs a device driver should not be using
 *     this function
 */
अटल अंतरभूत व्योम * phys_to_virt(अचिन्हित दीर्घ address)
अणु
	वापस (व्योम *)(address + PAGE_OFFSET - PHYS_OFFSET);
पूर्ण

/*
 * ISA I/O bus memory addresses are 1:1 with the physical address.
 */
अटल अंतरभूत अचिन्हित दीर्घ isa_virt_to_bus(अस्थिर व्योम *address)
अणु
	वापस virt_to_phys(address);
पूर्ण

अटल अंतरभूत व्योम *isa_bus_to_virt(अचिन्हित दीर्घ address)
अणु
	वापस phys_to_virt(address);
पूर्ण

/*
 * However PCI ones are not necessarily 1:1 and thereक्रमe these पूर्णांकerfaces
 * are क्रमbidden in portable PCI drivers.
 *
 * Allow them क्रम x86 क्रम legacy drivers, though.
 */
#घोषणा virt_to_bus virt_to_phys
#घोषणा bus_to_virt phys_to_virt

/*
 * Change "struct page" to physical address.
 */
#घोषणा page_to_phys(page)	((dma_addr_t)page_to_pfn(page) << PAGE_SHIFT)

व्योम __iomem *ioremap_prot(phys_addr_t offset, अचिन्हित दीर्घ size,
		अचिन्हित दीर्घ prot_val);
व्योम iounmap(स्थिर अस्थिर व्योम __iomem *addr);

/*
 * ioremap     -   map bus memory पूर्णांकo CPU space
 * @offset:    bus address of the memory
 * @size:      size of the resource to map
 *
 * ioremap perक्रमms a platक्रमm specअगरic sequence of operations to
 * make bus memory CPU accessible via the पढ़ोb/पढ़ोw/पढ़ोl/ग_लिखोb/
 * ग_लिखोw/ग_लिखोl functions and the other mmio helpers. The वापसed
 * address is not guaranteed to be usable directly as a भव
 * address.
 */
#घोषणा ioremap(offset, size)						\
	ioremap_prot((offset), (size), _CACHE_UNCACHED)
#घोषणा ioremap_uc		ioremap

/*
 * ioremap_cache -	map bus memory पूर्णांकo CPU space
 * @offset:	    bus address of the memory
 * @size:	    size of the resource to map
 *
 * ioremap_cache perक्रमms a platक्रमm specअगरic sequence of operations to
 * make bus memory CPU accessible via the पढ़ोb/पढ़ोw/पढ़ोl/ग_लिखोb/
 * ग_लिखोw/ग_लिखोl functions and the other mmio helpers. The वापसed
 * address is not guaranteed to be usable directly as a भव
 * address.
 *
 * This version of ioremap ensures that the memory is marked cachable by
 * the CPU.  Also enables full ग_लिखो-combining.	 Useful क्रम some
 * memory-like regions on I/O busses.
 */
#घोषणा ioremap_cache(offset, size)					\
	ioremap_prot((offset), (size), _page_cachable_शेष)

/*
 * ioremap_wc     -   map bus memory पूर्णांकo CPU space
 * @offset:    bus address of the memory
 * @size:      size of the resource to map
 *
 * ioremap_wc perक्रमms a platक्रमm specअगरic sequence of operations to
 * make bus memory CPU accessible via the पढ़ोb/पढ़ोw/पढ़ोl/ग_लिखोb/
 * ग_लिखोw/ग_लिखोl functions and the other mmio helpers. The वापसed
 * address is not guaranteed to be usable directly as a भव
 * address.
 *
 * This version of ioremap ensures that the memory is marked uncachable
 * but accelerated by means of ग_लिखो-combining feature. It is specअगरically
 * useful क्रम PCIe prefetchable winकरोws, which may vastly improve a
 * communications perक्रमmance. If it was determined on boot stage, what
 * CPU CCA करोesn't support UCA, the method shall fall-back to the
 * _CACHE_UNCACHED option (see cpu_probe() method).
 */
#घोषणा ioremap_wc(offset, size)					\
	ioremap_prot((offset), (size), boot_cpu_data.ग_लिखोcombine)

#अगर defined(CONFIG_CPU_CAVIUM_OCTEON) || defined(CONFIG_CPU_LOONGSON64)
#घोषणा war_io_reorder_wmb()		wmb()
#अन्यथा
#घोषणा war_io_reorder_wmb()		barrier()
#पूर्ण_अगर

#घोषणा __BUILD_MEMORY_SINGLE(pfx, bwlq, type, barrier, relax, irq)	\
									\
अटल अंतरभूत व्योम pfx##ग_लिखो##bwlq(type val,				\
				    अस्थिर व्योम __iomem *mem)		\
अणु									\
	अस्थिर type *__mem;						\
	type __val;							\
									\
	अगर (barrier)							\
		iobarrier_rw();						\
	अन्यथा								\
		war_io_reorder_wmb();					\
									\
	__mem = (व्योम *)__swizzle_addr_##bwlq((अचिन्हित दीर्घ)(mem));	\
									\
	__val = pfx##ioswab##bwlq(__mem, val);				\
									\
	अगर (माप(type) != माप(u64) || माप(u64) == माप(दीर्घ)) \
		*__mem = __val;						\
	अन्यथा अगर (cpu_has_64bits) अणु					\
		अचिन्हित दीर्घ __flags;					\
		type __पंचांगp;						\
									\
		अगर (irq)						\
			local_irq_save(__flags);			\
		__यंत्र__ __अस्थिर__(					\
			".set	push"		"\t\t# __writeq""\n\t"	\
			".set	arch=r4000"			"\n\t"	\
			"dsll32 %L0, %L0, 0"			"\n\t"	\
			"dsrl32 %L0, %L0, 0"			"\n\t"	\
			"dsll32 %M0, %M0, 0"			"\n\t"	\
			"or	%L0, %L0, %M0"			"\n\t"	\
			"sd	%L0, %2"			"\n\t"	\
			".set	pop"				"\n"	\
			: "=r" (__पंचांगp)					\
			: "0" (__val), "m" (*__mem));			\
		अगर (irq)						\
			local_irq_restore(__flags);			\
	पूर्ण अन्यथा								\
		BUG();							\
पूर्ण									\
									\
अटल अंतरभूत type pfx##पढ़ो##bwlq(स्थिर अस्थिर व्योम __iomem *mem)	\
अणु									\
	अस्थिर type *__mem;						\
	type __val;							\
									\
	__mem = (व्योम *)__swizzle_addr_##bwlq((अचिन्हित दीर्घ)(mem));	\
									\
	अगर (barrier)							\
		iobarrier_rw();						\
									\
	अगर (माप(type) != माप(u64) || माप(u64) == माप(दीर्घ)) \
		__val = *__mem;						\
	अन्यथा अगर (cpu_has_64bits) अणु					\
		अचिन्हित दीर्घ __flags;					\
									\
		अगर (irq)						\
			local_irq_save(__flags);			\
		__यंत्र__ __अस्थिर__(					\
			".set	push"		"\t\t# __readq" "\n\t"	\
			".set	arch=r4000"			"\n\t"	\
			"ld	%L0, %1"			"\n\t"	\
			"dsra32 %M0, %L0, 0"			"\n\t"	\
			"sll	%L0, %L0, 0"			"\n\t"	\
			".set	pop"				"\n"	\
			: "=r" (__val)					\
			: "m" (*__mem));				\
		अगर (irq)						\
			local_irq_restore(__flags);			\
	पूर्ण अन्यथा अणु							\
		__val = 0;						\
		BUG();							\
	पूर्ण								\
									\
	/* prevent prefetching of coherent DMA data prematurely */	\
	अगर (!relax)							\
		rmb();							\
	वापस pfx##ioswab##bwlq(__mem, __val);				\
पूर्ण

#घोषणा __BUILD_IOPORT_SINGLE(pfx, bwlq, type, barrier, relax, p)	\
									\
अटल अंतरभूत व्योम pfx##out##bwlq##p(type val, अचिन्हित दीर्घ port)	\
अणु									\
	अस्थिर type *__addr;						\
	type __val;							\
									\
	अगर (barrier)							\
		iobarrier_rw();						\
	अन्यथा								\
		war_io_reorder_wmb();					\
									\
	__addr = (व्योम *)__swizzle_addr_##bwlq(mips_io_port_base + port); \
									\
	__val = pfx##ioswab##bwlq(__addr, val);				\
									\
	/* Really, we want this to be atomic */				\
	BUILD_BUG_ON(माप(type) > माप(अचिन्हित दीर्घ));		\
									\
	*__addr = __val;						\
पूर्ण									\
									\
अटल अंतरभूत type pfx##in##bwlq##p(अचिन्हित दीर्घ port)			\
अणु									\
	अस्थिर type *__addr;						\
	type __val;							\
									\
	__addr = (व्योम *)__swizzle_addr_##bwlq(mips_io_port_base + port); \
									\
	BUILD_BUG_ON(माप(type) > माप(अचिन्हित दीर्घ));		\
									\
	अगर (barrier)							\
		iobarrier_rw();						\
									\
	__val = *__addr;						\
									\
	/* prevent prefetching of coherent DMA data prematurely */	\
	अगर (!relax)							\
		rmb();							\
	वापस pfx##ioswab##bwlq(__addr, __val);			\
पूर्ण

#घोषणा __BUILD_MEMORY_PFX(bus, bwlq, type, relax)			\
									\
__BUILD_MEMORY_SINGLE(bus, bwlq, type, 1, relax, 1)

#घोषणा BUILDIO_MEM(bwlq, type)						\
									\
__BUILD_MEMORY_PFX(__raw_, bwlq, type, 0)				\
__BUILD_MEMORY_PFX(__relaxed_, bwlq, type, 1)				\
__BUILD_MEMORY_PFX(__mem_, bwlq, type, 0)				\
__BUILD_MEMORY_PFX(, bwlq, type, 0)

BUILDIO_MEM(b, u8)
BUILDIO_MEM(w, u16)
BUILDIO_MEM(l, u32)
#अगर_घोषित CONFIG_64BIT
BUILDIO_MEM(q, u64)
#अन्यथा
__BUILD_MEMORY_PFX(__raw_, q, u64, 0)
__BUILD_MEMORY_PFX(__mem_, q, u64, 0)
#पूर्ण_अगर

#घोषणा __BUILD_IOPORT_PFX(bus, bwlq, type)				\
	__BUILD_IOPORT_SINGLE(bus, bwlq, type, 1, 0,)			\
	__BUILD_IOPORT_SINGLE(bus, bwlq, type, 1, 0, _p)

#घोषणा BUILDIO_IOPORT(bwlq, type)					\
	__BUILD_IOPORT_PFX(, bwlq, type)				\
	__BUILD_IOPORT_PFX(__mem_, bwlq, type)

BUILDIO_IOPORT(b, u8)
BUILDIO_IOPORT(w, u16)
BUILDIO_IOPORT(l, u32)
#अगर_घोषित CONFIG_64BIT
BUILDIO_IOPORT(q, u64)
#पूर्ण_अगर

#घोषणा __BUILDIO(bwlq, type)						\
									\
__BUILD_MEMORY_SINGLE(____raw_, bwlq, type, 1, 0, 0)

__BUILDIO(q, u64)

#घोषणा पढ़ोb_relaxed			__relaxed_पढ़ोb
#घोषणा पढ़ोw_relaxed			__relaxed_पढ़ोw
#घोषणा पढ़ोl_relaxed			__relaxed_पढ़ोl
#अगर_घोषित CONFIG_64BIT
#घोषणा पढ़ोq_relaxed			__relaxed_पढ़ोq
#पूर्ण_अगर

#घोषणा ग_लिखोb_relaxed			__relaxed_ग_लिखोb
#घोषणा ग_लिखोw_relaxed			__relaxed_ग_लिखोw
#घोषणा ग_लिखोl_relaxed			__relaxed_ग_लिखोl
#अगर_घोषित CONFIG_64BIT
#घोषणा ग_लिखोq_relaxed			__relaxed_ग_लिखोq
#पूर्ण_अगर

#घोषणा पढ़ोb_be(addr)							\
	__raw_पढ़ोb((__क्रमce अचिन्हित *)(addr))
#घोषणा पढ़ोw_be(addr)							\
	be16_to_cpu(__raw_पढ़ोw((__क्रमce अचिन्हित *)(addr)))
#घोषणा पढ़ोl_be(addr)							\
	be32_to_cpu(__raw_पढ़ोl((__क्रमce अचिन्हित *)(addr)))
#घोषणा पढ़ोq_be(addr)							\
	be64_to_cpu(__raw_पढ़ोq((__क्रमce अचिन्हित *)(addr)))

#घोषणा ग_लिखोb_be(val, addr)						\
	__raw_ग_लिखोb((val), (__क्रमce अचिन्हित *)(addr))
#घोषणा ग_लिखोw_be(val, addr)						\
	__raw_ग_लिखोw(cpu_to_be16((val)), (__क्रमce अचिन्हित *)(addr))
#घोषणा ग_लिखोl_be(val, addr)						\
	__raw_ग_लिखोl(cpu_to_be32((val)), (__क्रमce अचिन्हित *)(addr))
#घोषणा ग_लिखोq_be(val, addr)						\
	__raw_ग_लिखोq(cpu_to_be64((val)), (__क्रमce अचिन्हित *)(addr))

/*
 * Some code tests क्रम these symbols
 */
#अगर_घोषित CONFIG_64BIT
#घोषणा पढ़ोq				पढ़ोq
#घोषणा ग_लिखोq				ग_लिखोq
#पूर्ण_अगर

#घोषणा __BUILD_MEMORY_STRING(bwlq, type)				\
									\
अटल अंतरभूत व्योम ग_लिखोs##bwlq(अस्थिर व्योम __iomem *mem,		\
				स्थिर व्योम *addr, अचिन्हित पूर्णांक count)	\
अणु									\
	स्थिर अस्थिर type *__addr = addr;				\
									\
	जबतक (count--) अणु						\
		__mem_ग_लिखो##bwlq(*__addr, mem);			\
		__addr++;						\
	पूर्ण								\
पूर्ण									\
									\
अटल अंतरभूत व्योम पढ़ोs##bwlq(अस्थिर व्योम __iomem *mem, व्योम *addr,	\
			       अचिन्हित पूर्णांक count)			\
अणु									\
	अस्थिर type *__addr = addr;					\
									\
	जबतक (count--) अणु						\
		*__addr = __mem_पढ़ो##bwlq(mem);			\
		__addr++;						\
	पूर्ण								\
पूर्ण

#घोषणा __BUILD_IOPORT_STRING(bwlq, type)				\
									\
अटल अंतरभूत व्योम outs##bwlq(अचिन्हित दीर्घ port, स्थिर व्योम *addr,	\
			      अचिन्हित पूर्णांक count)			\
अणु									\
	स्थिर अस्थिर type *__addr = addr;				\
									\
	जबतक (count--) अणु						\
		__mem_out##bwlq(*__addr, port);				\
		__addr++;						\
	पूर्ण								\
पूर्ण									\
									\
अटल अंतरभूत व्योम ins##bwlq(अचिन्हित दीर्घ port, व्योम *addr,		\
			     अचिन्हित पूर्णांक count)			\
अणु									\
	अस्थिर type *__addr = addr;					\
									\
	जबतक (count--) अणु						\
		*__addr = __mem_in##bwlq(port);				\
		__addr++;						\
	पूर्ण								\
पूर्ण

#घोषणा BUILDSTRING(bwlq, type)						\
									\
__BUILD_MEMORY_STRING(bwlq, type)					\
__BUILD_IOPORT_STRING(bwlq, type)

BUILDSTRING(b, u8)
BUILDSTRING(w, u16)
BUILDSTRING(l, u32)
#अगर_घोषित CONFIG_64BIT
BUILDSTRING(q, u64)
#पूर्ण_अगर

अटल अंतरभूत व्योम स_रखो_io(अस्थिर व्योम __iomem *addr, अचिन्हित अक्षर val, पूर्णांक count)
अणु
	स_रखो((व्योम __क्रमce *) addr, val, count);
पूर्ण
अटल अंतरभूत व्योम स_नकल_fromio(व्योम *dst, स्थिर अस्थिर व्योम __iomem *src, पूर्णांक count)
अणु
	स_नकल(dst, (व्योम __क्रमce *) src, count);
पूर्ण
अटल अंतरभूत व्योम स_नकल_toio(अस्थिर व्योम __iomem *dst, स्थिर व्योम *src, पूर्णांक count)
अणु
	स_नकल((व्योम __क्रमce *) dst, src, count);
पूर्ण

/*
 * The caches on some architectures aren't dma-coherent and have need to
 * handle this in software.  There are three types of operations that
 * can be applied to dma buffers.
 *
 *  - dma_cache_wback_inv(start, size) makes caches and coherent by
 *    writing the content of the caches back to memory, अगर necessary.
 *    The function also invalidates the affected part of the caches as
 *    necessary beक्रमe DMA transfers from outside to memory.
 *  - dma_cache_wback(start, size) makes caches and coherent by
 *    writing the content of the caches back to memory, अगर necessary.
 *    The function also invalidates the affected part of the caches as
 *    necessary beक्रमe DMA transfers from outside to memory.
 *  - dma_cache_inv(start, size) invalidates the affected parts of the
 *    caches.  Dirty lines of the caches may be written back or simply
 *    be discarded.  This operation is necessary beक्रमe dma operations
 *    to the memory.
 *
 * This API used to be exported; it now is क्रम arch code पूर्णांकernal use only.
 */
#अगर_घोषित CONFIG_DMA_NONCOHERENT

बाह्य व्योम (*_dma_cache_wback_inv)(अचिन्हित दीर्घ start, अचिन्हित दीर्घ size);
बाह्य व्योम (*_dma_cache_wback)(अचिन्हित दीर्घ start, अचिन्हित दीर्घ size);
बाह्य व्योम (*_dma_cache_inv)(अचिन्हित दीर्घ start, अचिन्हित दीर्घ size);

#घोषणा dma_cache_wback_inv(start, size)	_dma_cache_wback_inv(start, size)
#घोषणा dma_cache_wback(start, size)		_dma_cache_wback(start, size)
#घोषणा dma_cache_inv(start, size)		_dma_cache_inv(start, size)

#अन्यथा /* Sane hardware */

#घोषणा dma_cache_wback_inv(start,size) \
	करो अणु (व्योम) (start); (व्योम) (size); पूर्ण जबतक (0)
#घोषणा dma_cache_wback(start,size)	\
	करो अणु (व्योम) (start); (व्योम) (size); पूर्ण जबतक (0)
#घोषणा dma_cache_inv(start,size)	\
	करो अणु (व्योम) (start); (व्योम) (size); पूर्ण जबतक (0)

#पूर्ण_अगर /* CONFIG_DMA_NONCOHERENT */

/*
 * Read a 32-bit रेजिस्टर that requires a 64-bit पढ़ो cycle on the bus.
 * Aव्योम पूर्णांकerrupt mucking, just adjust the address क्रम 4-byte access.
 * Assume the addresses are 8-byte aligned.
 */
#अगर_घोषित __MIPSEB__
#घोषणा __CSR_32_ADJUST 4
#अन्यथा
#घोषणा __CSR_32_ADJUST 0
#पूर्ण_अगर

#घोषणा csr_out32(v, a) (*(अस्थिर u32 *)((अचिन्हित दीर्घ)(a) + __CSR_32_ADJUST) = (v))
#घोषणा csr_in32(a)    (*(अस्थिर u32 *)((अचिन्हित दीर्घ)(a) + __CSR_32_ADJUST))

/*
 * Convert a physical poपूर्णांकer to a भव kernel poपूर्णांकer क्रम /dev/mem
 * access
 */
#घोषणा xlate_dev_mem_ptr(p)	__va(p)

व्योम __ioपढ़ो64_copy(व्योम *to, स्थिर व्योम __iomem *from, माप_प्रकार count);

#पूर्ण_अगर /* _ASM_IO_H */
