<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/पन.स
 *
 *  Copyright (C) 1996-2000 Russell King
 *
 * Modअगरications:
 *  16-Sep-1996	RMK	Inlined the inx/outx functions & optimised क्रम both
 *			स्थिरant addresses and variable addresses.
 *  04-Dec-1997	RMK	Moved a lot of this stuff to the new architecture
 *			specअगरic IO header files.
 *  27-Mar-1999	PJB	Second parameter of स_नकल_toio is स्थिर..
 *  04-Apr-1999	PJB	Added check_signature.
 *  12-Dec-1999	RMK	More cleanups
 *  18-Jun-2000 RMK	Removed virt_to_* and मित्रs definitions
 *  05-Oct-2004 BJD     Moved memory string functions to use व्योम __iomem
 */
#अगर_अघोषित __ASM_ARM_IO_H
#घोषणा __ASM_ARM_IO_H

#अगर_घोषित __KERNEL__

#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र-generic/pci_iomap.h>

/*
 * ISA I/O bus memory addresses are 1:1 with the physical address.
 */
#घोषणा isa_virt_to_bus virt_to_phys
#घोषणा isa_bus_to_virt phys_to_virt

/*
 * Atomic MMIO-wide IO modअगरy
 */
बाह्य व्योम atomic_io_modअगरy(व्योम __iomem *reg, u32 mask, u32 set);
बाह्य व्योम atomic_io_modअगरy_relaxed(व्योम __iomem *reg, u32 mask, u32 set);

/*
 * Generic IO पढ़ो/ग_लिखो.  These perक्रमm native-endian accesses.  Note
 * that some architectures will want to re-define __raw_अणुपढ़ो,ग_लिखोपूर्णw.
 */
व्योम __raw_ग_लिखोsb(अस्थिर व्योम __iomem *addr, स्थिर व्योम *data, पूर्णांक bytelen);
व्योम __raw_ग_लिखोsw(अस्थिर व्योम __iomem *addr, स्थिर व्योम *data, पूर्णांक wordlen);
व्योम __raw_ग_लिखोsl(अस्थिर व्योम __iomem *addr, स्थिर व्योम *data, पूर्णांक दीर्घlen);

व्योम __raw_पढ़ोsb(स्थिर अस्थिर व्योम __iomem *addr, व्योम *data, पूर्णांक bytelen);
व्योम __raw_पढ़ोsw(स्थिर अस्थिर व्योम __iomem *addr, व्योम *data, पूर्णांक wordlen);
व्योम __raw_पढ़ोsl(स्थिर अस्थिर व्योम __iomem *addr, व्योम *data, पूर्णांक दीर्घlen);

#अगर __LINUX_ARM_ARCH__ < 6
/*
 * Half-word accesses are problematic with RiscPC due to limitations of
 * the bus. Rather than special-हाल the machine, just let the compiler
 * generate the access क्रम CPUs prior to ARMv6.
 */
#घोषणा __raw_पढ़ोw(a)         (__chk_io_ptr(a), *(अस्थिर अचिन्हित लघु __क्रमce *)(a))
#घोषणा __raw_ग_लिखोw(v,a)      ((व्योम)(__chk_io_ptr(a), *(अस्थिर अचिन्हित लघु __क्रमce *)(a) = (v)))
#अन्यथा
/*
 * When running under a hypervisor, we want to aव्योम I/O accesses with
 * ग_लिखोback addressing modes as these incur a signअगरicant perक्रमmance
 * overhead (the address generation must be emulated in software).
 */
#घोषणा __raw_ग_लिखोw __raw_ग_लिखोw
अटल अंतरभूत व्योम __raw_ग_लिखोw(u16 val, अस्थिर व्योम __iomem *addr)
अणु
	यंत्र अस्थिर("strh %1, %0"
		     : : "Q" (*(अस्थिर u16 __क्रमce *)addr), "r" (val));
पूर्ण

#घोषणा __raw_पढ़ोw __raw_पढ़ोw
अटल अंतरभूत u16 __raw_पढ़ोw(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u16 val;
	यंत्र अस्थिर("ldrh %0, %1"
		     : "=r" (val)
		     : "Q" (*(अस्थिर u16 __क्रमce *)addr));
	वापस val;
पूर्ण
#पूर्ण_अगर

#घोषणा __raw_ग_लिखोb __raw_ग_लिखोb
अटल अंतरभूत व्योम __raw_ग_लिखोb(u8 val, अस्थिर व्योम __iomem *addr)
अणु
	यंत्र अस्थिर("strb %1, %0"
		     : : "Qo" (*(अस्थिर u8 __क्रमce *)addr), "r" (val));
पूर्ण

#घोषणा __raw_ग_लिखोl __raw_ग_लिखोl
अटल अंतरभूत व्योम __raw_ग_लिखोl(u32 val, अस्थिर व्योम __iomem *addr)
अणु
	यंत्र अस्थिर("str %1, %0"
		     : : "Qo" (*(अस्थिर u32 __क्रमce *)addr), "r" (val));
पूर्ण

#घोषणा __raw_पढ़ोb __raw_पढ़ोb
अटल अंतरभूत u8 __raw_पढ़ोb(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u8 val;
	यंत्र अस्थिर("ldrb %0, %1"
		     : "=r" (val)
		     : "Qo" (*(अस्थिर u8 __क्रमce *)addr));
	वापस val;
पूर्ण

#घोषणा __raw_पढ़ोl __raw_पढ़ोl
अटल अंतरभूत u32 __raw_पढ़ोl(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u32 val;
	यंत्र अस्थिर("ldr %0, %1"
		     : "=r" (val)
		     : "Qo" (*(अस्थिर u32 __क्रमce *)addr));
	वापस val;
पूर्ण

/*
 * Architecture ioremap implementation.
 */
#घोषणा MT_DEVICE		0
#घोषणा MT_DEVICE_NONSHARED	1
#घोषणा MT_DEVICE_CACHED	2
#घोषणा MT_DEVICE_WC		3
/*
 * types 4 onwards can be found in यंत्र/mach/map.h and are undefined
 * क्रम ioremap
 */

/*
 * __arm_ioremap takes CPU physical address.
 * __arm_ioremap_pfn takes a Page Frame Number and an offset पूर्णांकo that page
 * The _caller variety takes a __builtin_वापस_address(0) value क्रम
 * /proc/vदो_स्मृति to use - and should only be used in non-अंतरभूत functions.
 */
बाह्य व्योम __iomem *__arm_ioremap_caller(phys_addr_t, माप_प्रकार, अचिन्हित पूर्णांक,
	व्योम *);
बाह्य व्योम __iomem *__arm_ioremap_pfn(अचिन्हित दीर्घ, अचिन्हित दीर्घ, माप_प्रकार, अचिन्हित पूर्णांक);
बाह्य व्योम __iomem *__arm_ioremap_exec(phys_addr_t, माप_प्रकार, bool cached);
बाह्य व्योम __iounmap(अस्थिर व्योम __iomem *addr);

बाह्य व्योम __iomem * (*arch_ioremap_caller)(phys_addr_t, माप_प्रकार,
	अचिन्हित पूर्णांक, व्योम *);
बाह्य व्योम (*arch_iounmap)(अस्थिर व्योम __iomem *);

/*
 * Bad पढ़ो/ग_लिखो accesses...
 */
बाह्य व्योम __पढ़ोग_लिखो_bug(स्थिर अक्षर *fn);

/*
 * A typesafe __io() helper
 */
अटल अंतरभूत व्योम __iomem *__typesafe_io(अचिन्हित दीर्घ addr)
अणु
	वापस (व्योम __iomem *)addr;
पूर्ण

#घोषणा IOMEM(x)	((व्योम __क्रमce __iomem *)(x))

/* IO barriers */
#अगर_घोषित CONFIG_ARM_DMA_MEM_BUFFERABLE
#समावेश <यंत्र/barrier.h>
#घोषणा __iormb()		rmb()
#घोषणा __iowmb()		wmb()
#अन्यथा
#घोषणा __iormb()		करो अणु पूर्ण जबतक (0)
#घोषणा __iowmb()		करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/* PCI fixed i/o mapping */
#घोषणा PCI_IO_VIRT_BASE	0xfee00000
#घोषणा PCI_IOBASE		((व्योम __iomem *)PCI_IO_VIRT_BASE)

#अगर defined(CONFIG_PCI)
व्योम pci_ioremap_set_mem_type(पूर्णांक mem_type);
#अन्यथा
अटल अंतरभूत व्योम pci_ioremap_set_mem_type(पूर्णांक mem_type) अणुपूर्ण
#पूर्ण_अगर

बाह्य पूर्णांक pci_ioremap_io(अचिन्हित पूर्णांक offset, phys_addr_t phys_addr);

/*
 * PCI configuration space mapping function.
 *
 * The PCI specअगरication करोes not allow configuration ग_लिखो
 * transactions to be posted. Add an arch specअगरic
 * pci_remap_cfgspace() definition that is implemented
 * through strongly ordered memory mappings.
 */
#घोषणा pci_remap_cfgspace pci_remap_cfgspace
व्योम __iomem *pci_remap_cfgspace(resource_माप_प्रकार res_cookie, माप_प्रकार size);
/*
 * Now, pick up the machine-defined IO definitions
 */
#अगर_घोषित CONFIG_NEED_MACH_IO_H
#समावेश <mach/पन.स>
#या_अगर defined(CONFIG_PCI)
#घोषणा IO_SPACE_LIMIT	((resource_माप_प्रकार)0xfffff)
#घोषणा __io(a)		__typesafe_io(PCI_IO_VIRT_BASE + ((a) & IO_SPACE_LIMIT))
#अन्यथा
#घोषणा __io(a)		__typesafe_io((a) & IO_SPACE_LIMIT)
#पूर्ण_अगर

/*
 * This is the limit of PC card/PCI/ISA IO space, which is by शेष
 * 64K अगर we have PC card, PCI or ISA support.  Otherwise, शेष to
 * zero to prevent ISA/PCI drivers claiming IO space (and potentially
 * oopsing.)
 *
 * Only set this larger अगर you really need inb() et.al. to operate over
 * a larger address space.  Note that SOC_COMMON ioremaps each sockets
 * IO space area, and so inb() et.al. must be defined to operate as per
 * पढ़ोb() et.al. on such platक्रमms.
 */
#अगर_अघोषित IO_SPACE_LIMIT
#अगर defined(CONFIG_PCMCIA_SOC_COMMON) || defined(CONFIG_PCMCIA_SOC_COMMON_MODULE)
#घोषणा IO_SPACE_LIMIT ((resource_माप_प्रकार)0xffffffff)
#या_अगर defined(CONFIG_PCI) || defined(CONFIG_ISA) || defined(CONFIG_PCCARD)
#घोषणा IO_SPACE_LIMIT ((resource_माप_प्रकार)0xffff)
#अन्यथा
#घोषणा IO_SPACE_LIMIT ((resource_माप_प्रकार)0)
#पूर्ण_अगर
#पूर्ण_अगर

/*
 *  IO port access primitives
 *  -------------------------
 *
 * The ARM करोesn't have special IO access inकाष्ठाions; all IO is memory
 * mapped.  Note that these are defined to perक्रमm little endian accesses
 * only.  Their primary purpose is to access PCI and ISA peripherals.
 *
 * Note that क्रम a big endian machine, this implies that the following
 * big endian mode connectivity is in place, as described by numerous
 * ARM करोcuments:
 *
 *    PCI:  D0-D7   D8-D15 D16-D23 D24-D31
 *    ARM: D24-D31 D16-D23  D8-D15  D0-D7
 *
 * The machine specअगरic पन.स include defines __io to translate an "IO"
 * address to a memory address.
 *
 * Note that we prevent GCC re-ordering or caching values in expressions
 * by पूर्णांकroducing sequence poपूर्णांकs पूर्णांकo the in*() definitions.  Note that
 * __raw_* करो not guarantee this behaviour.
 *
 * The अणुin,outपूर्ण[bwl] macros are क्रम emulating x86-style PCI/ISA IO space.
 */
#अगर_घोषित __io
#घोषणा outb(v,p)	(अणु __iowmb(); __raw_ग_लिखोb(v,__io(p)); पूर्ण)
#घोषणा outw(v,p)	(अणु __iowmb(); __raw_ग_लिखोw((__क्रमce __u16) \
					cpu_to_le16(v),__io(p)); पूर्ण)
#घोषणा outl(v,p)	(अणु __iowmb(); __raw_ग_लिखोl((__क्रमce __u32) \
					cpu_to_le32(v),__io(p)); पूर्ण)

#घोषणा inb(p)	(अणु __u8 __v = __raw_पढ़ोb(__io(p)); __iormb(); __v; पूर्ण)
#घोषणा inw(p)	(अणु __u16 __v = le16_to_cpu((__क्रमce __le16) \
			__raw_पढ़ोw(__io(p))); __iormb(); __v; पूर्ण)
#घोषणा inl(p)	(अणु __u32 __v = le32_to_cpu((__क्रमce __le32) \
			__raw_पढ़ोl(__io(p))); __iormb(); __v; पूर्ण)

#घोषणा outsb(p,d,l)		__raw_ग_लिखोsb(__io(p),d,l)
#घोषणा outsw(p,d,l)		__raw_ग_लिखोsw(__io(p),d,l)
#घोषणा outsl(p,d,l)		__raw_ग_लिखोsl(__io(p),d,l)

#घोषणा insb(p,d,l)		__raw_पढ़ोsb(__io(p),d,l)
#घोषणा insw(p,d,l)		__raw_पढ़ोsw(__io(p),d,l)
#घोषणा insl(p,d,l)		__raw_पढ़ोsl(__io(p),d,l)
#पूर्ण_अगर

/*
 * String version of IO memory access ops:
 */
बाह्य व्योम _स_नकल_fromio(व्योम *, स्थिर अस्थिर व्योम __iomem *, माप_प्रकार);
बाह्य व्योम _स_नकल_toio(अस्थिर व्योम __iomem *, स्थिर व्योम *, माप_प्रकार);
बाह्य व्योम _स_रखो_io(अस्थिर व्योम __iomem *, पूर्णांक, माप_प्रकार);

/*
 *  Memory access primitives
 *  ------------------------
 *
 * These perक्रमm PCI memory accesses via an ioremap region.  They करोn't
 * take an address as such, but a cookie.
 *
 * Again, these are defined to perक्रमm little endian accesses.  See the
 * IO port primitives क्रम more inक्रमmation.
 */
#अगर_अघोषित पढ़ोl
#घोषणा पढ़ोb_relaxed(c) (अणु u8  __r = __raw_पढ़ोb(c); __r; पूर्ण)
#घोषणा पढ़ोw_relaxed(c) (अणु u16 __r = le16_to_cpu((__क्रमce __le16) \
					__raw_पढ़ोw(c)); __r; पूर्ण)
#घोषणा पढ़ोl_relaxed(c) (अणु u32 __r = le32_to_cpu((__क्रमce __le32) \
					__raw_पढ़ोl(c)); __r; पूर्ण)

#घोषणा ग_लिखोb_relaxed(v,c)	__raw_ग_लिखोb(v,c)
#घोषणा ग_लिखोw_relaxed(v,c)	__raw_ग_लिखोw((__क्रमce u16) cpu_to_le16(v),c)
#घोषणा ग_लिखोl_relaxed(v,c)	__raw_ग_लिखोl((__क्रमce u32) cpu_to_le32(v),c)

#घोषणा पढ़ोb(c)		(अणु u8  __v = पढ़ोb_relaxed(c); __iormb(); __v; पूर्ण)
#घोषणा पढ़ोw(c)		(अणु u16 __v = पढ़ोw_relaxed(c); __iormb(); __v; पूर्ण)
#घोषणा पढ़ोl(c)		(अणु u32 __v = पढ़ोl_relaxed(c); __iormb(); __v; पूर्ण)

#घोषणा ग_लिखोb(v,c)		(अणु __iowmb(); ग_लिखोb_relaxed(v,c); पूर्ण)
#घोषणा ग_लिखोw(v,c)		(अणु __iowmb(); ग_लिखोw_relaxed(v,c); पूर्ण)
#घोषणा ग_लिखोl(v,c)		(अणु __iowmb(); ग_लिखोl_relaxed(v,c); पूर्ण)

#घोषणा पढ़ोsb(p,d,l)		__raw_पढ़ोsb(p,d,l)
#घोषणा पढ़ोsw(p,d,l)		__raw_पढ़ोsw(p,d,l)
#घोषणा पढ़ोsl(p,d,l)		__raw_पढ़ोsl(p,d,l)

#घोषणा ग_लिखोsb(p,d,l)		__raw_ग_लिखोsb(p,d,l)
#घोषणा ग_लिखोsw(p,d,l)		__raw_ग_लिखोsw(p,d,l)
#घोषणा ग_लिखोsl(p,d,l)		__raw_ग_लिखोsl(p,d,l)

#अगर_अघोषित __ARMBE__
अटल अंतरभूत व्योम स_रखो_io(अस्थिर व्योम __iomem *dst, अचिन्हित c,
	माप_प्रकार count)
अणु
	बाह्य व्योम mmioset(व्योम *, अचिन्हित पूर्णांक, माप_प्रकार);
	mmioset((व्योम __क्रमce *)dst, c, count);
पूर्ण
#घोषणा स_रखो_io(dst,c,count) स_रखो_io(dst,c,count)

अटल अंतरभूत व्योम स_नकल_fromio(व्योम *to, स्थिर अस्थिर व्योम __iomem *from,
	माप_प्रकार count)
अणु
	बाह्य व्योम mmiocpy(व्योम *, स्थिर व्योम *, माप_प्रकार);
	mmiocpy(to, (स्थिर व्योम __क्रमce *)from, count);
पूर्ण
#घोषणा स_नकल_fromio(to,from,count) स_नकल_fromio(to,from,count)

अटल अंतरभूत व्योम स_नकल_toio(अस्थिर व्योम __iomem *to, स्थिर व्योम *from,
	माप_प्रकार count)
अणु
	बाह्य व्योम mmiocpy(व्योम *, स्थिर व्योम *, माप_प्रकार);
	mmiocpy((व्योम __क्रमce *)to, from, count);
पूर्ण
#घोषणा स_नकल_toio(to,from,count) स_नकल_toio(to,from,count)

#अन्यथा
#घोषणा स_रखो_io(c,v,l)	_स_रखो_io(c,(v),(l))
#घोषणा स_नकल_fromio(a,c,l)	_स_नकल_fromio((a),c,(l))
#घोषणा स_नकल_toio(c,a,l)	_स_नकल_toio(c,(a),(l))
#पूर्ण_अगर

#पूर्ण_अगर	/* पढ़ोl */

/*
 * ioremap() and मित्रs.
 *
 * ioremap() takes a resource address, and size.  Due to the ARM memory
 * types, it is important to use the correct ioremap() function as each
 * mapping has specअगरic properties.
 *
 * Function		Memory type	Cacheability	Cache hपूर्णांक
 * ioremap()		Device		n/a		n/a
 * ioremap_cache()	Normal		Writeback	Read allocate
 * ioremap_wc()		Normal		Non-cacheable	n/a
 * ioremap_wt()		Normal		Non-cacheable	n/a
 *
 * All device mappings have the following properties:
 * - no access speculation
 * - no repetition (eg, on वापस from an exception)
 * - number, order and size of accesses are मुख्यtained
 * - unaligned accesses are "unpredictable"
 * - ग_लिखोs may be delayed beक्रमe they hit the endpoपूर्णांक device
 *
 * All normal memory mappings have the following properties:
 * - पढ़ोs can be repeated with no side effects
 * - repeated पढ़ोs वापस the last value written
 * - पढ़ोs can fetch additional locations without side effects
 * - ग_लिखोs can be repeated (in certain हालs) with no side effects
 * - ग_लिखोs can be merged beक्रमe accessing the target
 * - unaligned accesses can be supported
 * - ordering is not guaranteed without explicit dependencies or barrier
 *   inकाष्ठाions
 * - ग_लिखोs may be delayed beक्रमe they hit the endpoपूर्णांक memory
 *
 * The cache hपूर्णांक is only a perक्रमmance hपूर्णांक: CPUs may alias these hपूर्णांकs.
 * Eg, a CPU not implementing पढ़ो allocate but implementing ग_लिखो allocate
 * will provide a ग_लिखो allocate mapping instead.
 */
व्योम __iomem *ioremap(resource_माप_प्रकार res_cookie, माप_प्रकार size);
#घोषणा ioremap ioremap

/*
 * Do not use ioremap_cache क्रम mapping memory. Use memremap instead.
 */
व्योम __iomem *ioremap_cache(resource_माप_प्रकार res_cookie, माप_प्रकार size);
#घोषणा ioremap_cache ioremap_cache

व्योम __iomem *ioremap_wc(resource_माप_प्रकार res_cookie, माप_प्रकार size);
#घोषणा ioremap_wc ioremap_wc
#घोषणा ioremap_wt ioremap_wc

व्योम iounmap(अस्थिर व्योम __iomem *iomem_cookie);
#घोषणा iounmap iounmap

व्योम *arch_memremap_wb(phys_addr_t phys_addr, माप_प्रकार size);
#घोषणा arch_memremap_wb arch_memremap_wb

/*
 * ioअणुपढ़ो,ग_लिखोपूर्णअणु16,32पूर्णbe() macros
 */
#घोषणा ioपढ़ो16be(p)		(अणु __u16 __v = be16_to_cpu((__क्रमce __be16)__raw_पढ़ोw(p)); __iormb(); __v; पूर्ण)
#घोषणा ioपढ़ो32be(p)		(अणु __u32 __v = be32_to_cpu((__क्रमce __be32)__raw_पढ़ोl(p)); __iormb(); __v; पूर्ण)

#घोषणा ioग_लिखो16be(v,p)	(अणु __iowmb(); __raw_ग_लिखोw((__क्रमce __u16)cpu_to_be16(v), p); पूर्ण)
#घोषणा ioग_लिखो32be(v,p)	(अणु __iowmb(); __raw_ग_लिखोl((__क्रमce __u32)cpu_to_be32(v), p); पूर्ण)

#अगर_अघोषित ioport_map
#घोषणा ioport_map ioport_map
बाह्य व्योम __iomem *ioport_map(अचिन्हित दीर्घ port, अचिन्हित पूर्णांक nr);
#पूर्ण_अगर
#अगर_अघोषित ioport_unmap
#घोषणा ioport_unmap ioport_unmap
बाह्य व्योम ioport_unmap(व्योम __iomem *addr);
#पूर्ण_अगर

काष्ठा pci_dev;

#घोषणा pci_iounmap pci_iounmap
बाह्य व्योम pci_iounmap(काष्ठा pci_dev *dev, व्योम __iomem *addr);

/*
 * Convert a physical poपूर्णांकer to a भव kernel poपूर्णांकer क्रम /dev/mem
 * access
 */
#घोषणा xlate_dev_mem_ptr(p)	__va(p)

#समावेश <यंत्र-generic/पन.स>

#अगर_घोषित CONFIG_MMU
#घोषणा ARCH_HAS_VALID_PHYS_ADDR_RANGE
बाह्य पूर्णांक valid_phys_addr_range(phys_addr_t addr, माप_प्रकार size);
बाह्य पूर्णांक valid_mmap_phys_addr_range(अचिन्हित दीर्घ pfn, माप_प्रकार size);
#पूर्ण_अगर

/*
 * Register ISA memory and port locations क्रम glibc iopl/inb/outb
 * emulation.
 */
बाह्य व्योम रेजिस्टर_isa_ports(अचिन्हित पूर्णांक mmio, अचिन्हित पूर्णांक io,
			       अचिन्हित पूर्णांक io_shअगरt);

#पूर्ण_अगर	/* __KERNEL__ */
#पूर्ण_अगर	/* __ASM_ARM_IO_H */
