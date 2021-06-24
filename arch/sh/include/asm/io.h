<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_IO_H
#घोषणा __ASM_SH_IO_H

/*
 * Convention:
 *    पढ़ोअणुb,w,l,qपूर्ण/ग_लिखोअणुb,w,l,qपूर्ण are क्रम PCI,
 *    जबतक inअणुb,w,lपूर्ण/outअणुb,w,lपूर्ण are क्रम ISA
 *
 * In addition we have 'pausing' versions: inअणुb,w,lपूर्ण_p/outअणुb,w,lपूर्ण_p
 * and 'string' versions: insअणुb,w,lपूर्ण/outsअणुb,w,lपूर्ण
 *
 * While पढ़ोअणुb,w,l,qपूर्ण and ग_लिखोअणुb,w,l,qपूर्ण contain memory barriers
 * स्वतःmatically, there are also __raw versions, which करो not.
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/machvec.h>
#समावेश <यंत्र/page.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र-generic/iomap.h>

#घोषणा __IO_PREFIX     generic
#समावेश <यंत्र/io_generic.h>
#समावेश <यंत्र-generic/pci_iomap.h>
#समावेश <mach/mangle-port.h>

#घोषणा __raw_ग_लिखोb(v,a)	(__chk_io_ptr(a), *(अस्थिर u8  __क्रमce *)(a) = (v))
#घोषणा __raw_ग_लिखोw(v,a)	(__chk_io_ptr(a), *(अस्थिर u16 __क्रमce *)(a) = (v))
#घोषणा __raw_ग_लिखोl(v,a)	(__chk_io_ptr(a), *(अस्थिर u32 __क्रमce *)(a) = (v))
#घोषणा __raw_ग_लिखोq(v,a)	(__chk_io_ptr(a), *(अस्थिर u64 __क्रमce *)(a) = (v))

#घोषणा __raw_पढ़ोb(a)		(__chk_io_ptr(a), *(अस्थिर u8  __क्रमce *)(a))
#घोषणा __raw_पढ़ोw(a)		(__chk_io_ptr(a), *(अस्थिर u16 __क्रमce *)(a))
#घोषणा __raw_पढ़ोl(a)		(__chk_io_ptr(a), *(अस्थिर u32 __क्रमce *)(a))
#घोषणा __raw_पढ़ोq(a)		(__chk_io_ptr(a), *(अस्थिर u64 __क्रमce *)(a))

#घोषणा पढ़ोb_relaxed(c)	(अणु u8  __v = ioswabb(__raw_पढ़ोb(c)); __v; पूर्ण)
#घोषणा पढ़ोw_relaxed(c)	(अणु u16 __v = ioswabw(__raw_पढ़ोw(c)); __v; पूर्ण)
#घोषणा पढ़ोl_relaxed(c)	(अणु u32 __v = ioswabl(__raw_पढ़ोl(c)); __v; पूर्ण)
#घोषणा पढ़ोq_relaxed(c)	(अणु u64 __v = ioswabq(__raw_पढ़ोq(c)); __v; पूर्ण)

#घोषणा ग_लिखोb_relaxed(v,c)	((व्योम)__raw_ग_लिखोb((__क्रमce  u8)ioswabb(v),c))
#घोषणा ग_लिखोw_relaxed(v,c)	((व्योम)__raw_ग_लिखोw((__क्रमce u16)ioswabw(v),c))
#घोषणा ग_लिखोl_relaxed(v,c)	((व्योम)__raw_ग_लिखोl((__क्रमce u32)ioswabl(v),c))
#घोषणा ग_लिखोq_relaxed(v,c)	((व्योम)__raw_ग_लिखोq((__क्रमce u64)ioswabq(v),c))

#घोषणा पढ़ोb(a)		(अणु u8  r_ = पढ़ोb_relaxed(a); rmb(); r_; पूर्ण)
#घोषणा पढ़ोw(a)		(अणु u16 r_ = पढ़ोw_relaxed(a); rmb(); r_; पूर्ण)
#घोषणा पढ़ोl(a)		(अणु u32 r_ = पढ़ोl_relaxed(a); rmb(); r_; पूर्ण)
#घोषणा पढ़ोq(a)		(अणु u64 r_ = पढ़ोq_relaxed(a); rmb(); r_; पूर्ण)

#घोषणा ग_लिखोb(v,a)		(अणु wmb(); ग_लिखोb_relaxed((v),(a)); पूर्ण)
#घोषणा ग_लिखोw(v,a)		(अणु wmb(); ग_लिखोw_relaxed((v),(a)); पूर्ण)
#घोषणा ग_लिखोl(v,a)		(अणु wmb(); ग_लिखोl_relaxed((v),(a)); पूर्ण)
#घोषणा ग_लिखोq(v,a)		(अणु wmb(); ग_लिखोq_relaxed((v),(a)); पूर्ण)

#घोषणा पढ़ोsb(p,d,l)		__raw_पढ़ोsb(p,d,l)
#घोषणा पढ़ोsw(p,d,l)		__raw_पढ़ोsw(p,d,l)
#घोषणा पढ़ोsl(p,d,l)		__raw_पढ़ोsl(p,d,l)

#घोषणा ग_लिखोsb(p,d,l)		__raw_ग_लिखोsb(p,d,l)
#घोषणा ग_लिखोsw(p,d,l)		__raw_ग_लिखोsw(p,d,l)
#घोषणा ग_लिखोsl(p,d,l)		__raw_ग_लिखोsl(p,d,l)

#घोषणा __BUILD_UNCACHED_IO(bwlq, type)					\
अटल अंतरभूत type पढ़ो##bwlq##_uncached(अचिन्हित दीर्घ addr)		\
अणु									\
	type ret;							\
	jump_to_uncached();						\
	ret = __raw_पढ़ो##bwlq(addr);					\
	back_to_cached();						\
	वापस ret;							\
पूर्ण									\
									\
अटल अंतरभूत व्योम ग_लिखो##bwlq##_uncached(type v, अचिन्हित दीर्घ addr)	\
अणु									\
	jump_to_uncached();						\
	__raw_ग_लिखो##bwlq(v, addr);					\
	back_to_cached();						\
पूर्ण

__BUILD_UNCACHED_IO(b, u8)
__BUILD_UNCACHED_IO(w, u16)
__BUILD_UNCACHED_IO(l, u32)
__BUILD_UNCACHED_IO(q, u64)

#घोषणा __BUILD_MEMORY_STRING(pfx, bwlq, type)				\
									\
अटल अंतरभूत व्योम							\
pfx##ग_लिखोs##bwlq(अस्थिर व्योम __iomem *mem, स्थिर व्योम *addr,		\
		  अचिन्हित पूर्णांक count)					\
अणु									\
	स्थिर अस्थिर type *__addr = addr;				\
									\
	जबतक (count--) अणु						\
		__raw_ग_लिखो##bwlq(*__addr, mem);			\
		__addr++;						\
	पूर्ण								\
पूर्ण									\
									\
अटल अंतरभूत व्योम pfx##पढ़ोs##bwlq(अस्थिर व्योम __iomem *mem,		\
				    व्योम *addr, अचिन्हित पूर्णांक count)	\
अणु									\
	अस्थिर type *__addr = addr;					\
									\
	जबतक (count--) अणु						\
		*__addr = __raw_पढ़ो##bwlq(mem);			\
		__addr++;						\
	पूर्ण								\
पूर्ण

__BUILD_MEMORY_STRING(__raw_, b, u8)
__BUILD_MEMORY_STRING(__raw_, w, u16)

व्योम __raw_ग_लिखोsl(व्योम __iomem *addr, स्थिर व्योम *data, पूर्णांक दीर्घlen);
व्योम __raw_पढ़ोsl(स्थिर व्योम __iomem *addr, व्योम *data, पूर्णांक दीर्घlen);

__BUILD_MEMORY_STRING(__raw_, q, u64)

#अगर_घोषित CONFIG_HAS_IOPORT_MAP

/*
 * Slowकरोwn I/O port space accesses क्रम antique hardware.
 */
#अघोषित CONF_SLOWDOWN_IO

/*
 * On SuperH I/O ports are memory mapped, so we access them using normal
 * load/store inकाष्ठाions. sh_io_port_base is the भव address to
 * which all ports are being mapped.
 */
बाह्य अचिन्हित दीर्घ sh_io_port_base;

अटल अंतरभूत व्योम __set_io_port_base(अचिन्हित दीर्घ pbase)
अणु
	*(अचिन्हित दीर्घ *)&sh_io_port_base = pbase;
	barrier();
पूर्ण

#अगर_घोषित CONFIG_GENERIC_IOMAP
#घोषणा __ioport_map ioport_map
#अन्यथा
बाह्य व्योम __iomem *__ioport_map(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक size);
#पूर्ण_अगर

#अगर_घोषित CONF_SLOWDOWN_IO
#घोषणा SLOW_DOWN_IO __raw_पढ़ोw(sh_io_port_base)
#अन्यथा
#घोषणा SLOW_DOWN_IO
#पूर्ण_अगर

#घोषणा __BUILD_IOPORT_SINGLE(pfx, bwlq, type, p, slow)			\
									\
अटल अंतरभूत व्योम pfx##out##bwlq##p(type val, अचिन्हित दीर्घ port)	\
अणु									\
	अस्थिर type *__addr;						\
									\
	__addr = __ioport_map(port, माप(type));			\
	*__addr = val;							\
	slow;								\
पूर्ण									\
									\
अटल अंतरभूत type pfx##in##bwlq##p(अचिन्हित दीर्घ port)			\
अणु									\
	अस्थिर type *__addr;						\
	type __val;							\
									\
	__addr = __ioport_map(port, माप(type));			\
	__val = *__addr;						\
	slow;								\
									\
	वापस __val;							\
पूर्ण

#घोषणा __BUILD_IOPORT_PFX(bus, bwlq, type)				\
	__BUILD_IOPORT_SINGLE(bus, bwlq, type, ,)			\
	__BUILD_IOPORT_SINGLE(bus, bwlq, type, _p, SLOW_DOWN_IO)

#घोषणा BUILDIO_IOPORT(bwlq, type)					\
	__BUILD_IOPORT_PFX(, bwlq, type)

BUILDIO_IOPORT(b, u8)
BUILDIO_IOPORT(w, u16)
BUILDIO_IOPORT(l, u32)
BUILDIO_IOPORT(q, u64)

#घोषणा __BUILD_IOPORT_STRING(bwlq, type)				\
									\
अटल अंतरभूत व्योम outs##bwlq(अचिन्हित दीर्घ port, स्थिर व्योम *addr,	\
			      अचिन्हित पूर्णांक count)			\
अणु									\
	स्थिर अस्थिर type *__addr = addr;				\
									\
	जबतक (count--) अणु						\
		out##bwlq(*__addr, port);				\
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
		*__addr = in##bwlq(port);				\
		__addr++;						\
	पूर्ण								\
पूर्ण

__BUILD_IOPORT_STRING(b, u8)
__BUILD_IOPORT_STRING(w, u16)
__BUILD_IOPORT_STRING(l, u32)
__BUILD_IOPORT_STRING(q, u64)

#अन्यथा /* !CONFIG_HAS_IOPORT_MAP */

#समावेश <यंत्र/io_noioport.h>

#पूर्ण_अगर


#घोषणा IO_SPACE_LIMIT 0xffffffff

/* We really want to try and get these to स_नकल etc */
व्योम स_नकल_fromio(व्योम *, स्थिर अस्थिर व्योम __iomem *, अचिन्हित दीर्घ);
व्योम स_नकल_toio(अस्थिर व्योम __iomem *, स्थिर व्योम *, अचिन्हित दीर्घ);
व्योम स_रखो_io(अस्थिर व्योम __iomem *, पूर्णांक, अचिन्हित दीर्घ);

/* Quad-word real-mode I/O, करोn't ask.. */
अचिन्हित दीर्घ दीर्घ peek_real_address_q(अचिन्हित दीर्घ दीर्घ addr);
अचिन्हित दीर्घ दीर्घ poke_real_address_q(अचिन्हित दीर्घ दीर्घ addr,
				       अचिन्हित दीर्घ दीर्घ val);

#अगर !defined(CONFIG_MMU)
#घोषणा virt_to_phys(address)	((अचिन्हित दीर्घ)(address))
#घोषणा phys_to_virt(address)	((व्योम *)(address))
#अन्यथा
#घोषणा virt_to_phys(address)	(__pa(address))
#घोषणा phys_to_virt(address)	(__va(address))
#पूर्ण_अगर

#अगर_घोषित CONFIG_MMU
व्योम iounmap(व्योम __iomem *addr);
व्योम __iomem *__ioremap_caller(phys_addr_t offset, अचिन्हित दीर्घ size,
			       pgprot_t prot, व्योम *caller);

अटल अंतरभूत व्योम __iomem *ioremap(phys_addr_t offset, अचिन्हित दीर्घ size)
अणु
	वापस __ioremap_caller(offset, size, PAGE_KERNEL_NOCACHE,
			__builtin_वापस_address(0));
पूर्ण

अटल अंतरभूत व्योम __iomem *
ioremap_cache(phys_addr_t offset, अचिन्हित दीर्घ size)
अणु
	वापस __ioremap_caller(offset, size, PAGE_KERNEL,
			__builtin_वापस_address(0));
पूर्ण
#घोषणा ioremap_cache ioremap_cache

#अगर_घोषित CONFIG_HAVE_IOREMAP_PROT
अटल अंतरभूत व्योम __iomem *ioremap_prot(phys_addr_t offset, अचिन्हित दीर्घ size,
		अचिन्हित दीर्घ flags)
अणु
	वापस __ioremap_caller(offset, size, __pgprot(flags),
			__builtin_वापस_address(0));
पूर्ण
#पूर्ण_अगर /* CONFIG_HAVE_IOREMAP_PROT */

#अन्यथा /* CONFIG_MMU */
#घोषणा iounmap(addr)		करो अणु पूर्ण जबतक (0)
#घोषणा ioremap(offset, size)	((व्योम __iomem *)(अचिन्हित दीर्घ)(offset))
#पूर्ण_अगर /* CONFIG_MMU */

#घोषणा ioremap_uc	ioremap

/*
 * Convert a physical poपूर्णांकer to a भव kernel poपूर्णांकer क्रम /dev/mem
 * access
 */
#घोषणा xlate_dev_mem_ptr(p)	__va(p)

#घोषणा ARCH_HAS_VALID_PHYS_ADDR_RANGE
पूर्णांक valid_phys_addr_range(phys_addr_t addr, माप_प्रकार size);
पूर्णांक valid_mmap_phys_addr_range(अचिन्हित दीर्घ pfn, माप_प्रकार size);

#पूर्ण_अगर /* __ASM_SH_IO_H */
