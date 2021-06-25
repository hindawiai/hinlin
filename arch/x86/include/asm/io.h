<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_IO_H
#घोषणा _ASM_X86_IO_H

/*
 * This file contains the definitions क्रम the x86 IO inकाष्ठाions
 * inb/inw/inl/outb/outw/outl and the "string versions" of the same
 * (insb/insw/insl/outsb/outsw/outsl). You can also use "pausing"
 * versions of the single-IO inकाष्ठाions (inb_p/inw_p/..).
 *
 * This file is not meant to be obfuscating: it's just complicated
 * to (a) handle it all in a way that makes gcc able to optimize it
 * as well as possible and (b) trying to aव्योम writing the same thing
 * over and over again with slight variations and possibly making a
 * mistake somewhere.
 */

/*
 * Thanks to James van Artsdalen क्रम a better timing-fix than
 * the two लघु jumps: using outb's to a nonexistent port seems
 * to guarantee better timings even on fast machines.
 *
 * On the other hand, I'd like to be sure of a non-existent port:
 * I feel a bit unsafe about using 0x80 (should be safe, though)
 *
 *		Linus
 */

 /*
  *  Bit simplअगरied and optimized by Jan Hubicka
  *  Support of BIGMEM added by Gerhard Wichert, Siemens AG, July 1999.
  *
  *  isa_स_रखो_io, isa_स_नकल_fromio, isa_स_नकल_toio added,
  *  isa_पढ़ो[wl] and isa_ग_लिखो[wl] fixed
  *  - Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
  */

#घोषणा ARCH_HAS_IOREMAP_WC
#घोषणा ARCH_HAS_IOREMAP_WT

#समावेश <linux/माला.स>
#समावेश <linux/compiler.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/early_ioremap.h>
#समावेश <यंत्र/pgtable_types.h>

#घोषणा build_mmio_पढ़ो(name, size, type, reg, barrier) \
अटल अंतरभूत type name(स्थिर अस्थिर व्योम __iomem *addr) \
अणु type ret; यंत्र अस्थिर("mov" size " %1,%0":reg (ret) \
:"m" (*(अस्थिर type __क्रमce *)addr) barrier); वापस ret; पूर्ण

#घोषणा build_mmio_ग_लिखो(name, size, type, reg, barrier) \
अटल अंतरभूत व्योम name(type val, अस्थिर व्योम __iomem *addr) \
अणु यंत्र अस्थिर("mov" size " %0,%1": :reg (val), \
"m" (*(अस्थिर type __क्रमce *)addr) barrier); पूर्ण

build_mmio_पढ़ो(पढ़ोb, "b", अचिन्हित अक्षर, "=q", :"memory")
build_mmio_पढ़ो(पढ़ोw, "w", अचिन्हित लघु, "=r", :"memory")
build_mmio_पढ़ो(पढ़ोl, "l", अचिन्हित पूर्णांक, "=r", :"memory")

build_mmio_पढ़ो(__पढ़ोb, "b", अचिन्हित अक्षर, "=q", )
build_mmio_पढ़ो(__पढ़ोw, "w", अचिन्हित लघु, "=r", )
build_mmio_पढ़ो(__पढ़ोl, "l", अचिन्हित पूर्णांक, "=r", )

build_mmio_ग_लिखो(ग_लिखोb, "b", अचिन्हित अक्षर, "q", :"memory")
build_mmio_ग_लिखो(ग_लिखोw, "w", अचिन्हित लघु, "r", :"memory")
build_mmio_ग_लिखो(ग_लिखोl, "l", अचिन्हित पूर्णांक, "r", :"memory")

build_mmio_ग_लिखो(__ग_लिखोb, "b", अचिन्हित अक्षर, "q", )
build_mmio_ग_लिखो(__ग_लिखोw, "w", अचिन्हित लघु, "r", )
build_mmio_ग_लिखो(__ग_लिखोl, "l", अचिन्हित पूर्णांक, "r", )

#घोषणा पढ़ोb पढ़ोb
#घोषणा पढ़ोw पढ़ोw
#घोषणा पढ़ोl पढ़ोl
#घोषणा पढ़ोb_relaxed(a) __पढ़ोb(a)
#घोषणा पढ़ोw_relaxed(a) __पढ़ोw(a)
#घोषणा पढ़ोl_relaxed(a) __पढ़ोl(a)
#घोषणा __raw_पढ़ोb __पढ़ोb
#घोषणा __raw_पढ़ोw __पढ़ोw
#घोषणा __raw_पढ़ोl __पढ़ोl

#घोषणा ग_लिखोb ग_लिखोb
#घोषणा ग_लिखोw ग_लिखोw
#घोषणा ग_लिखोl ग_लिखोl
#घोषणा ग_लिखोb_relaxed(v, a) __ग_लिखोb(v, a)
#घोषणा ग_लिखोw_relaxed(v, a) __ग_लिखोw(v, a)
#घोषणा ग_लिखोl_relaxed(v, a) __ग_लिखोl(v, a)
#घोषणा __raw_ग_लिखोb __ग_लिखोb
#घोषणा __raw_ग_लिखोw __ग_लिखोw
#घोषणा __raw_ग_लिखोl __ग_लिखोl

#अगर_घोषित CONFIG_X86_64

build_mmio_पढ़ो(पढ़ोq, "q", u64, "=r", :"memory")
build_mmio_पढ़ो(__पढ़ोq, "q", u64, "=r", )
build_mmio_ग_लिखो(ग_लिखोq, "q", u64, "r", :"memory")
build_mmio_ग_लिखो(__ग_लिखोq, "q", u64, "r", )

#घोषणा पढ़ोq_relaxed(a)	__पढ़ोq(a)
#घोषणा ग_लिखोq_relaxed(v, a)	__ग_लिखोq(v, a)

#घोषणा __raw_पढ़ोq		__पढ़ोq
#घोषणा __raw_ग_लिखोq		__ग_लिखोq

/* Let people know that we have them */
#घोषणा पढ़ोq			पढ़ोq
#घोषणा ग_लिखोq			ग_लिखोq

#पूर्ण_अगर

#घोषणा ARCH_HAS_VALID_PHYS_ADDR_RANGE
बाह्य पूर्णांक valid_phys_addr_range(phys_addr_t addr, माप_प्रकार size);
बाह्य पूर्णांक valid_mmap_phys_addr_range(अचिन्हित दीर्घ pfn, माप_प्रकार size);

/**
 *	virt_to_phys	-	map भव addresses to physical
 *	@address: address to remap
 *
 *	The वापसed physical address is the physical (CPU) mapping क्रम
 *	the memory address given. It is only valid to use this function on
 *	addresses directly mapped or allocated via kदो_स्मृति.
 *
 *	This function करोes not give bus mappings क्रम DMA transfers. In
 *	almost all conceivable हालs a device driver should not be using
 *	this function
 */

अटल अंतरभूत phys_addr_t virt_to_phys(अस्थिर व्योम *address)
अणु
	वापस __pa(address);
पूर्ण
#घोषणा virt_to_phys virt_to_phys

/**
 *	phys_to_virt	-	map physical address to भव
 *	@address: address to remap
 *
 *	The वापसed भव address is a current CPU mapping क्रम
 *	the memory address given. It is only valid to use this function on
 *	addresses that have a kernel mapping
 *
 *	This function करोes not handle bus mappings क्रम DMA transfers. In
 *	almost all conceivable हालs a device driver should not be using
 *	this function
 */

अटल अंतरभूत व्योम *phys_to_virt(phys_addr_t address)
अणु
	वापस __va(address);
पूर्ण
#घोषणा phys_to_virt phys_to_virt

/*
 * Change "struct page" to physical address.
 */
#घोषणा page_to_phys(page)    ((dma_addr_t)page_to_pfn(page) << PAGE_SHIFT)

/*
 * ISA I/O bus memory addresses are 1:1 with the physical address.
 * However, we truncate the address to अचिन्हित पूर्णांक to aव्योम undesirable
 * promotions in legacy drivers.
 */
अटल अंतरभूत अचिन्हित पूर्णांक isa_virt_to_bus(अस्थिर व्योम *address)
अणु
	वापस (अचिन्हित पूर्णांक)virt_to_phys(address);
पूर्ण
#घोषणा isa_bus_to_virt		phys_to_virt

/*
 * However PCI ones are not necessarily 1:1 and thereक्रमe these पूर्णांकerfaces
 * are क्रमbidden in portable PCI drivers.
 *
 * Allow them on x86 क्रम legacy drivers, though.
 */
#घोषणा virt_to_bus virt_to_phys
#घोषणा bus_to_virt phys_to_virt

/*
 * The शेष ioremap() behavior is non-cached; अगर you need something
 * अन्यथा, you probably want one of the following.
 */
बाह्य व्योम __iomem *ioremap_uc(resource_माप_प्रकार offset, अचिन्हित दीर्घ size);
#घोषणा ioremap_uc ioremap_uc
बाह्य व्योम __iomem *ioremap_cache(resource_माप_प्रकार offset, अचिन्हित दीर्घ size);
#घोषणा ioremap_cache ioremap_cache
बाह्य व्योम __iomem *ioremap_prot(resource_माप_प्रकार offset, अचिन्हित दीर्घ size, अचिन्हित दीर्घ prot_val);
#घोषणा ioremap_prot ioremap_prot
बाह्य व्योम __iomem *ioremap_encrypted(resource_माप_प्रकार phys_addr, अचिन्हित दीर्घ size);
#घोषणा ioremap_encrypted ioremap_encrypted

/**
 * ioremap     -   map bus memory पूर्णांकo CPU space
 * @offset:    bus address of the memory
 * @size:      size of the resource to map
 *
 * ioremap perक्रमms a platक्रमm specअगरic sequence of operations to
 * make bus memory CPU accessible via the पढ़ोb/पढ़ोw/पढ़ोl/ग_लिखोb/
 * ग_लिखोw/ग_लिखोl functions and the other mmio helpers. The वापसed
 * address is not guaranteed to be usable directly as a भव
 * address.
 *
 * If the area you are trying to map is a PCI BAR you should have a
 * look at pci_iomap().
 */
व्योम __iomem *ioremap(resource_माप_प्रकार offset, अचिन्हित दीर्घ size);
#घोषणा ioremap ioremap

बाह्य व्योम iounmap(अस्थिर व्योम __iomem *addr);
#घोषणा iounmap iounmap

बाह्य व्योम set_iounmap_nonlazy(व्योम);

#अगर_घोषित __KERNEL__

व्योम स_नकल_fromio(व्योम *, स्थिर अस्थिर व्योम __iomem *, माप_प्रकार);
व्योम स_नकल_toio(अस्थिर व्योम __iomem *, स्थिर व्योम *, माप_प्रकार);
व्योम स_रखो_io(अस्थिर व्योम __iomem *, पूर्णांक, माप_प्रकार);

#घोषणा स_नकल_fromio स_नकल_fromio
#घोषणा स_नकल_toio स_नकल_toio
#घोषणा स_रखो_io स_रखो_io

#समावेश <यंत्र-generic/iomap.h>

/*
 * ISA space is 'always mapped' on a typical x86 प्रणाली, no need to
 * explicitly ioremap() it. The fact that the ISA IO space is mapped
 * to PAGE_OFFSET is pure coincidence - it करोes not mean ISA values
 * are physical addresses. The following स्थिरant poपूर्णांकer can be
 * used as the IO-area poपूर्णांकer (it can be iounmapped as well, so the
 * analogy with PCI is quite large):
 */
#घोषणा __ISA_IO_base ((अक्षर __iomem *)(PAGE_OFFSET))

#पूर्ण_अगर /* __KERNEL__ */

बाह्य व्योम native_io_delay(व्योम);

बाह्य पूर्णांक io_delay_type;
बाह्य व्योम io_delay_init(व्योम);

#अगर defined(CONFIG_PARAVIRT)
#समावेश <यंत्र/paravirt.h>
#अन्यथा

अटल अंतरभूत व्योम slow_करोwn_io(व्योम)
अणु
	native_io_delay();
#अगर_घोषित REALLY_SLOW_IO
	native_io_delay();
	native_io_delay();
	native_io_delay();
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_AMD_MEM_ENCRYPT
#समावेश <linux/jump_label.h>

बाह्य काष्ठा अटल_key_false sev_enable_key;
अटल अंतरभूत bool sev_key_active(व्योम)
अणु
	वापस अटल_branch_unlikely(&sev_enable_key);
पूर्ण

#अन्यथा /* !CONFIG_AMD_MEM_ENCRYPT */

अटल अंतरभूत bool sev_key_active(व्योम) अणु वापस false; पूर्ण

#पूर्ण_अगर /* CONFIG_AMD_MEM_ENCRYPT */

#घोषणा BUILDIO(bwl, bw, type)						\
अटल अंतरभूत व्योम out##bwl(अचिन्हित type value, पूर्णांक port)		\
अणु									\
	यंत्र अस्थिर("out" #bwl " %" #bw "0, %w1"			\
		     : : "a"(value), "Nd"(port));			\
पूर्ण									\
									\
अटल अंतरभूत अचिन्हित type in##bwl(पूर्णांक port)				\
अणु									\
	अचिन्हित type value;						\
	यंत्र अस्थिर("in" #bwl " %w1, %" #bw "0"			\
		     : "=a"(value) : "Nd"(port));			\
	वापस value;							\
पूर्ण									\
									\
अटल अंतरभूत व्योम out##bwl##_p(अचिन्हित type value, पूर्णांक port)		\
अणु									\
	out##bwl(value, port);						\
	slow_करोwn_io();							\
पूर्ण									\
									\
अटल अंतरभूत अचिन्हित type in##bwl##_p(पूर्णांक port)			\
अणु									\
	अचिन्हित type value = in##bwl(port);				\
	slow_करोwn_io();							\
	वापस value;							\
पूर्ण									\
									\
अटल अंतरभूत व्योम outs##bwl(पूर्णांक port, स्थिर व्योम *addr, अचिन्हित दीर्घ count) \
अणु									\
	अगर (sev_key_active()) अणु						\
		अचिन्हित type *value = (अचिन्हित type *)addr;		\
		जबतक (count) अणु						\
			out##bwl(*value, port);				\
			value++;					\
			count--;					\
		पूर्ण							\
	पूर्ण अन्यथा अणु							\
		यंत्र अस्थिर("rep; outs" #bwl				\
			     : "+S"(addr), "+c"(count)			\
			     : "d"(port) : "memory");			\
	पूर्ण								\
पूर्ण									\
									\
अटल अंतरभूत व्योम ins##bwl(पूर्णांक port, व्योम *addr, अचिन्हित दीर्घ count)	\
अणु									\
	अगर (sev_key_active()) अणु						\
		अचिन्हित type *value = (अचिन्हित type *)addr;		\
		जबतक (count) अणु						\
			*value = in##bwl(port);				\
			value++;					\
			count--;					\
		पूर्ण							\
	पूर्ण अन्यथा अणु							\
		यंत्र अस्थिर("rep; ins" #bwl				\
			     : "+D"(addr), "+c"(count)			\
			     : "d"(port) : "memory");			\
	पूर्ण								\
पूर्ण

BUILDIO(b, b, अक्षर)
BUILDIO(w, w, लघु)
BUILDIO(l, , पूर्णांक)

#घोषणा inb inb
#घोषणा inw inw
#घोषणा inl inl
#घोषणा inb_p inb_p
#घोषणा inw_p inw_p
#घोषणा inl_p inl_p
#घोषणा insb insb
#घोषणा insw insw
#घोषणा insl insl

#घोषणा outb outb
#घोषणा outw outw
#घोषणा outl outl
#घोषणा outb_p outb_p
#घोषणा outw_p outw_p
#घोषणा outl_p outl_p
#घोषणा outsb outsb
#घोषणा outsw outsw
#घोषणा outsl outsl

बाह्य व्योम *xlate_dev_mem_ptr(phys_addr_t phys);
बाह्य व्योम unxlate_dev_mem_ptr(phys_addr_t phys, व्योम *addr);

#घोषणा xlate_dev_mem_ptr xlate_dev_mem_ptr
#घोषणा unxlate_dev_mem_ptr unxlate_dev_mem_ptr

बाह्य पूर्णांक ioremap_change_attr(अचिन्हित दीर्घ vaddr, अचिन्हित दीर्घ size,
				क्रमागत page_cache_mode pcm);
बाह्य व्योम __iomem *ioremap_wc(resource_माप_प्रकार offset, अचिन्हित दीर्घ size);
#घोषणा ioremap_wc ioremap_wc
बाह्य व्योम __iomem *ioremap_wt(resource_माप_प्रकार offset, अचिन्हित दीर्घ size);
#घोषणा ioremap_wt ioremap_wt

बाह्य bool is_early_ioremap_ptep(pte_t *ptep);

#घोषणा IO_SPACE_LIMIT 0xffff

#समावेश <यंत्र-generic/पन.स>
#अघोषित PCI_IOBASE

#अगर_घोषित CONFIG_MTRR
बाह्य पूर्णांक __must_check arch_phys_wc_index(पूर्णांक handle);
#घोषणा arch_phys_wc_index arch_phys_wc_index

बाह्य पूर्णांक __must_check arch_phys_wc_add(अचिन्हित दीर्घ base,
					 अचिन्हित दीर्घ size);
बाह्य व्योम arch_phys_wc_del(पूर्णांक handle);
#घोषणा arch_phys_wc_add arch_phys_wc_add
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_PAT
बाह्य पूर्णांक arch_io_reserve_memtype_wc(resource_माप_प्रकार start, resource_माप_प्रकार size);
बाह्य व्योम arch_io_मुक्त_memtype_wc(resource_माप_प्रकार start, resource_माप_प्रकार size);
#घोषणा arch_io_reserve_memtype_wc arch_io_reserve_memtype_wc
#पूर्ण_अगर

बाह्य bool arch_memremap_can_ram_remap(resource_माप_प्रकार offset,
					अचिन्हित दीर्घ size,
					अचिन्हित दीर्घ flags);
#घोषणा arch_memremap_can_ram_remap arch_memremap_can_ram_remap

बाह्य bool phys_mem_access_encrypted(अचिन्हित दीर्घ phys_addr,
				      अचिन्हित दीर्घ size);

/**
 * iosubmit_cmds512 - copy data to single MMIO location, in 512-bit units
 * @dst: destination, in MMIO space (must be 512-bit aligned)
 * @src: source
 * @count: number of 512 bits quantities to submit
 *
 * Submit data from kernel space to MMIO space, in units of 512 bits at a
 * समय.  Order of access is not guaranteed, nor is a memory barrier
 * perक्रमmed afterwards.
 *
 * Warning: Do not use this helper unless your driver has checked that the CPU
 * inकाष्ठाion is supported on the platक्रमm.
 */
अटल अंतरभूत व्योम iosubmit_cmds512(व्योम __iomem *dst, स्थिर व्योम *src,
				    माप_प्रकार count)
अणु
	स्थिर u8 *from = src;
	स्थिर u8 *end = from + count * 64;

	जबतक (from < end) अणु
		movdir64b(dst, from);
		from += 64;
	पूर्ण
पूर्ण

#पूर्ण_अगर /* _ASM_X86_IO_H */
