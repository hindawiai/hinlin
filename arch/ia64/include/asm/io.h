<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_IO_H
#घोषणा _ASM_IA64_IO_H

/*
 * This file contains the definitions क्रम the emulated IO inकाष्ठाions
 * inb/inw/inl/outb/outw/outl and the "string versions" of the same
 * (insb/insw/insl/outsb/outsw/outsl). You can also use "pausing"
 * versions of the single-IO inकाष्ठाions (inb_p/inw_p/..).
 *
 * This file is not meant to be obfuscating: it's just complicated to
 * (a) handle it all in a way that makes gcc able to optimize it as
 * well as possible and (b) trying to aव्योम writing the same thing
 * over and over again with slight variations and possibly making a
 * mistake somewhere.
 *
 * Copyright (C) 1998-2003 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 * Copyright (C) 1999 Asit Mallick <asit.k.mallick@पूर्णांकel.com>
 * Copyright (C) 1999 Don Dugger <करोn.dugger@पूर्णांकel.com>
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <यंत्र/early_ioremap.h>

/* We करोn't use IO slowकरोwns on the ia64, but.. */
#घोषणा __SLOW_DOWN_IO	करो अणु पूर्ण जबतक (0)
#घोषणा SLOW_DOWN_IO	करो अणु पूर्ण जबतक (0)

#घोषणा __IA64_UNCACHED_OFFSET	RGN_BASE(RGN_UNCACHED)

/*
 * The legacy I/O space defined by the ia64 architecture supports only 65536 ports, but
 * large machines may have multiple other I/O spaces so we can't place any a priori limit
 * on IO_SPACE_LIMIT.  These additional spaces are described in ACPI.
 */
#घोषणा IO_SPACE_LIMIT		0xffffffffffffffffUL

#घोषणा MAX_IO_SPACES_BITS		8
#घोषणा MAX_IO_SPACES			(1UL << MAX_IO_SPACES_BITS)
#घोषणा IO_SPACE_BITS			24
#घोषणा IO_SPACE_SIZE			(1UL << IO_SPACE_BITS)

#घोषणा IO_SPACE_NR(port)		((port) >> IO_SPACE_BITS)
#घोषणा IO_SPACE_BASE(space)		((space) << IO_SPACE_BITS)
#घोषणा IO_SPACE_PORT(port)		((port) & (IO_SPACE_SIZE - 1))

#घोषणा IO_SPACE_SPARSE_ENCODING(p)	((((p) >> 2) << 12) | ((p) & 0xfff))

काष्ठा io_space अणु
	अचिन्हित दीर्घ mmio_base;	/* base in MMIO space */
	पूर्णांक sparse;
पूर्ण;

बाह्य काष्ठा io_space io_space[];
बाह्य अचिन्हित पूर्णांक num_io_spaces;

# अगरdef __KERNEL__

/*
 * All MMIO iomem cookies are in region 6; anything less is a PIO cookie:
 *	0xCxxxxxxxxxxxxxxx	MMIO cookie (वापस from ioremap)
 *	0x000000001SPPPPPP	PIO cookie (S=space number, P..P=port)
 *
 * ioपढ़ो/ग_लिखोX() uses the leading 1 in PIO cookies (PIO_OFFSET) to catch
 * code that uses bare port numbers without the prerequisite pci_iomap().
 */
#घोषणा PIO_OFFSET		(1UL << (MAX_IO_SPACES_BITS + IO_SPACE_BITS))
#घोषणा PIO_MASK		(PIO_OFFSET - 1)
#घोषणा PIO_RESERVED		__IA64_UNCACHED_OFFSET
#घोषणा HAVE_ARCH_PIO_SIZE

#समावेश <यंत्र/पूर्णांकrinsics.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र-generic/iomap.h>

/*
 * Change भव addresses to physical addresses and vv.
 */
अटल अंतरभूत अचिन्हित दीर्घ
virt_to_phys (अस्थिर व्योम *address)
अणु
	वापस (अचिन्हित दीर्घ) address - PAGE_OFFSET;
पूर्ण
#घोषणा virt_to_phys virt_to_phys

अटल अंतरभूत व्योम*
phys_to_virt (अचिन्हित दीर्घ address)
अणु
	वापस (व्योम *) (address + PAGE_OFFSET);
पूर्ण
#घोषणा phys_to_virt phys_to_virt

#घोषणा ARCH_HAS_VALID_PHYS_ADDR_RANGE
बाह्य u64 kern_mem_attribute (अचिन्हित दीर्घ phys_addr, अचिन्हित दीर्घ size);
बाह्य पूर्णांक valid_phys_addr_range (phys_addr_t addr, माप_प्रकार count); /* efi.c */
बाह्य पूर्णांक valid_mmap_phys_addr_range (अचिन्हित दीर्घ pfn, माप_प्रकार count);

/*
 * The following two macros are deprecated and scheduled क्रम removal.
 * Please use the PCI-DMA पूर्णांकerface defined in <यंत्र/pci.h> instead.
 */
#घोषणा bus_to_virt	phys_to_virt
#घोषणा virt_to_bus	virt_to_phys
#घोषणा page_to_bus	page_to_phys

# endअगर /* KERNEL */

/*
 * Memory fence w/accept.  This should never be used in code that is
 * not IA-64 specअगरic.
 */
#घोषणा __ia64_mf_a()	ia64_mfa()

अटल अंतरभूत व्योम*
__ia64_mk_io_addr (अचिन्हित दीर्घ port)
अणु
	काष्ठा io_space *space;
	अचिन्हित दीर्घ offset;

	space = &io_space[IO_SPACE_NR(port)];
	port = IO_SPACE_PORT(port);
	अगर (space->sparse)
		offset = IO_SPACE_SPARSE_ENCODING(port);
	अन्यथा
		offset = port;

	वापस (व्योम *) (space->mmio_base | offset);
पूर्ण

/*
 * For the in/out routines, we need to करो "mf.a" _after_ करोing the I/O access to ensure
 * that the access has completed beक्रमe executing other I/O accesses.  Since we're करोing
 * the accesses through an uncachable (UC) translation, the CPU will execute them in
 * program order.  However, we still need to tell the compiler not to shuffle them around
 * during optimization, which is why we use "volatile" poपूर्णांकers.
 */

#घोषणा inb inb
अटल अंतरभूत अचिन्हित पूर्णांक inb(अचिन्हित दीर्घ port)
अणु
	अस्थिर अचिन्हित अक्षर *addr = __ia64_mk_io_addr(port);
	अचिन्हित अक्षर ret;

	ret = *addr;
	__ia64_mf_a();
	वापस ret;
पूर्ण

#घोषणा inw inw
अटल अंतरभूत अचिन्हित पूर्णांक inw(अचिन्हित दीर्घ port)
अणु
	अस्थिर अचिन्हित लघु *addr = __ia64_mk_io_addr(port);
	अचिन्हित लघु ret;

	ret = *addr;
	__ia64_mf_a();
	वापस ret;
पूर्ण

#घोषणा inl inl
अटल अंतरभूत अचिन्हित पूर्णांक inl(अचिन्हित दीर्घ port)
अणु
	अस्थिर अचिन्हित पूर्णांक *addr = __ia64_mk_io_addr(port);
	अचिन्हित पूर्णांक ret;

	ret = *addr;
	__ia64_mf_a();
	वापस ret;
पूर्ण

#घोषणा outb outb
अटल अंतरभूत व्योम outb(अचिन्हित अक्षर val, अचिन्हित दीर्घ port)
अणु
	अस्थिर अचिन्हित अक्षर *addr = __ia64_mk_io_addr(port);

	*addr = val;
	__ia64_mf_a();
पूर्ण

#घोषणा outw outw
अटल अंतरभूत व्योम outw(अचिन्हित लघु val, अचिन्हित दीर्घ port)
अणु
	अस्थिर अचिन्हित लघु *addr = __ia64_mk_io_addr(port);

	*addr = val;
	__ia64_mf_a();
पूर्ण

#घोषणा outl outl
अटल अंतरभूत व्योम outl(अचिन्हित पूर्णांक val, अचिन्हित दीर्घ port)
अणु
	अस्थिर अचिन्हित पूर्णांक *addr = __ia64_mk_io_addr(port);

	*addr = val;
	__ia64_mf_a();
पूर्ण

#घोषणा insb insb
अटल अंतरभूत व्योम insb(अचिन्हित दीर्घ port, व्योम *dst, अचिन्हित दीर्घ count)
अणु
	अचिन्हित अक्षर *dp = dst;

	जबतक (count--)
		*dp++ = inb(port);
पूर्ण

#घोषणा insw insw
अटल अंतरभूत व्योम insw(अचिन्हित दीर्घ port, व्योम *dst, अचिन्हित दीर्घ count)
अणु
	अचिन्हित लघु *dp = dst;

	जबतक (count--)
		put_unaligned(inw(port), dp++);
पूर्ण

#घोषणा insl insl
अटल अंतरभूत व्योम insl(अचिन्हित दीर्घ port, व्योम *dst, अचिन्हित दीर्घ count)
अणु
	अचिन्हित पूर्णांक *dp = dst;

	जबतक (count--)
		put_unaligned(inl(port), dp++);
पूर्ण

#घोषणा outsb outsb
अटल अंतरभूत व्योम outsb(अचिन्हित दीर्घ port, स्थिर व्योम *src,
		अचिन्हित दीर्घ count)
अणु
	स्थिर अचिन्हित अक्षर *sp = src;

	जबतक (count--)
		outb(*sp++, port);
पूर्ण

#घोषणा outsw outsw
अटल अंतरभूत व्योम outsw(अचिन्हित दीर्घ port, स्थिर व्योम *src,
		अचिन्हित दीर्घ count)
अणु
	स्थिर अचिन्हित लघु *sp = src;

	जबतक (count--)
		outw(get_unaligned(sp++), port);
पूर्ण

#घोषणा outsl outsl
अटल अंतरभूत व्योम outsl(अचिन्हित दीर्घ port, स्थिर व्योम *src,
		अचिन्हित दीर्घ count)
अणु
	स्थिर अचिन्हित पूर्णांक *sp = src;

	जबतक (count--)
		outl(get_unaligned(sp++), port);
पूर्ण

# अगरdef __KERNEL__

बाह्य व्योम __iomem * ioremap(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ size);
बाह्य व्योम __iomem * ioremap_uc(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ size);
बाह्य व्योम iounmap (अस्थिर व्योम __iomem *addr);
अटल अंतरभूत व्योम __iomem * ioremap_cache (अचिन्हित दीर्घ phys_addr, अचिन्हित दीर्घ size)
अणु
	वापस ioremap(phys_addr, size);
पूर्ण
#घोषणा ioremap ioremap
#घोषणा ioremap_cache ioremap_cache
#घोषणा ioremap_uc ioremap_uc
#घोषणा iounmap iounmap

/*
 * String version of IO memory access ops:
 */
बाह्य व्योम स_नकल_fromio(व्योम *dst, स्थिर अस्थिर व्योम __iomem *src, दीर्घ n);
बाह्य व्योम स_नकल_toio(अस्थिर व्योम __iomem *dst, स्थिर व्योम *src, दीर्घ n);
बाह्य व्योम स_रखो_io(अस्थिर व्योम __iomem *s, पूर्णांक c, दीर्घ n);

#घोषणा स_नकल_fromio स_नकल_fromio
#घोषणा स_नकल_toio स_नकल_toio
#घोषणा स_रखो_io स_रखो_io
#घोषणा xlate_dev_mem_ptr xlate_dev_mem_ptr
#समावेश <यंत्र-generic/पन.स>
#अघोषित PCI_IOBASE

# endअगर /* __KERNEL__ */

#पूर्ण_अगर /* _ASM_IA64_IO_H */
