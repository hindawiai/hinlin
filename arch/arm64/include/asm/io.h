<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Based on arch/arm/include/यंत्र/पन.स
 *
 * Copyright (C) 1996-2000 Russell King
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_IO_H
#घोषणा __ASM_IO_H

#समावेश <linux/types.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/early_ioremap.h>
#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/cpufeature.h>

/*
 * Generic IO पढ़ो/ग_लिखो.  These perक्रमm native-endian accesses.
 */
#घोषणा __raw_ग_लिखोb __raw_ग_लिखोb
अटल अंतरभूत व्योम __raw_ग_लिखोb(u8 val, अस्थिर व्योम __iomem *addr)
अणु
	यंत्र अस्थिर("strb %w0, [%1]" : : "rZ" (val), "r" (addr));
पूर्ण

#घोषणा __raw_ग_लिखोw __raw_ग_लिखोw
अटल अंतरभूत व्योम __raw_ग_लिखोw(u16 val, अस्थिर व्योम __iomem *addr)
अणु
	यंत्र अस्थिर("strh %w0, [%1]" : : "rZ" (val), "r" (addr));
पूर्ण

#घोषणा __raw_ग_लिखोl __raw_ग_लिखोl
अटल __always_अंतरभूत व्योम __raw_ग_लिखोl(u32 val, अस्थिर व्योम __iomem *addr)
अणु
	यंत्र अस्थिर("str %w0, [%1]" : : "rZ" (val), "r" (addr));
पूर्ण

#घोषणा __raw_ग_लिखोq __raw_ग_लिखोq
अटल अंतरभूत व्योम __raw_ग_लिखोq(u64 val, अस्थिर व्योम __iomem *addr)
अणु
	यंत्र अस्थिर("str %x0, [%1]" : : "rZ" (val), "r" (addr));
पूर्ण

#घोषणा __raw_पढ़ोb __raw_पढ़ोb
अटल अंतरभूत u8 __raw_पढ़ोb(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u8 val;
	यंत्र अस्थिर(ALTERNATIVE("ldrb %w0, [%1]",
				 "ldarb %w0, [%1]",
				 ARM64_WORKAROUND_DEVICE_LOAD_ACQUIRE)
		     : "=r" (val) : "r" (addr));
	वापस val;
पूर्ण

#घोषणा __raw_पढ़ोw __raw_पढ़ोw
अटल अंतरभूत u16 __raw_पढ़ोw(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u16 val;

	यंत्र अस्थिर(ALTERNATIVE("ldrh %w0, [%1]",
				 "ldarh %w0, [%1]",
				 ARM64_WORKAROUND_DEVICE_LOAD_ACQUIRE)
		     : "=r" (val) : "r" (addr));
	वापस val;
पूर्ण

#घोषणा __raw_पढ़ोl __raw_पढ़ोl
अटल __always_अंतरभूत u32 __raw_पढ़ोl(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u32 val;
	यंत्र अस्थिर(ALTERNATIVE("ldr %w0, [%1]",
				 "ldar %w0, [%1]",
				 ARM64_WORKAROUND_DEVICE_LOAD_ACQUIRE)
		     : "=r" (val) : "r" (addr));
	वापस val;
पूर्ण

#घोषणा __raw_पढ़ोq __raw_पढ़ोq
अटल अंतरभूत u64 __raw_पढ़ोq(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u64 val;
	यंत्र अस्थिर(ALTERNATIVE("ldr %0, [%1]",
				 "ldar %0, [%1]",
				 ARM64_WORKAROUND_DEVICE_LOAD_ACQUIRE)
		     : "=r" (val) : "r" (addr));
	वापस val;
पूर्ण

/* IO barriers */
#घोषणा __iormb(v)							\
(अणु									\
	अचिन्हित दीर्घ पंचांगp;						\
									\
	dma_rmb();								\
									\
	/*								\
	 * Create a dummy control dependency from the IO पढ़ो to any	\
	 * later inकाष्ठाions. This ensures that a subsequent call to	\
	 * udelay() will be ordered due to the ISB in get_cycles().	\
	 */								\
	यंत्र अस्थिर("eor	%0, %1, %1\n"				\
		     "cbnz	%0, ."					\
		     : "=r" (पंचांगp) : "r" ((अचिन्हित दीर्घ)(v))		\
		     : "memory");					\
पूर्ण)

#घोषणा __io_par(v)		__iormb(v)
#घोषणा __iowmb()		dma_wmb()
#घोषणा __iomb()		dma_mb()

/*
 * Relaxed I/O memory access primitives. These follow the Device memory
 * ordering rules but करो not guarantee any ordering relative to Normal memory
 * accesses.
 */
#घोषणा पढ़ोb_relaxed(c)	(अणु u8  __r = __raw_पढ़ोb(c); __r; पूर्ण)
#घोषणा पढ़ोw_relaxed(c)	(अणु u16 __r = le16_to_cpu((__क्रमce __le16)__raw_पढ़ोw(c)); __r; पूर्ण)
#घोषणा पढ़ोl_relaxed(c)	(अणु u32 __r = le32_to_cpu((__क्रमce __le32)__raw_पढ़ोl(c)); __r; पूर्ण)
#घोषणा पढ़ोq_relaxed(c)	(अणु u64 __r = le64_to_cpu((__क्रमce __le64)__raw_पढ़ोq(c)); __r; पूर्ण)

#घोषणा ग_लिखोb_relaxed(v,c)	((व्योम)__raw_ग_लिखोb((v),(c)))
#घोषणा ग_लिखोw_relaxed(v,c)	((व्योम)__raw_ग_लिखोw((__क्रमce u16)cpu_to_le16(v),(c)))
#घोषणा ग_लिखोl_relaxed(v,c)	((व्योम)__raw_ग_लिखोl((__क्रमce u32)cpu_to_le32(v),(c)))
#घोषणा ग_लिखोq_relaxed(v,c)	((व्योम)__raw_ग_लिखोq((__क्रमce u64)cpu_to_le64(v),(c)))

/*
 * I/O memory access primitives. Reads are ordered relative to any
 * following Normal memory access. Writes are ordered relative to any prior
 * Normal memory access.
 */
#घोषणा पढ़ोb(c)		(अणु u8  __v = पढ़ोb_relaxed(c); __iormb(__v); __v; पूर्ण)
#घोषणा पढ़ोw(c)		(अणु u16 __v = पढ़ोw_relaxed(c); __iormb(__v); __v; पूर्ण)
#घोषणा पढ़ोl(c)		(अणु u32 __v = पढ़ोl_relaxed(c); __iormb(__v); __v; पूर्ण)
#घोषणा पढ़ोq(c)		(अणु u64 __v = पढ़ोq_relaxed(c); __iormb(__v); __v; पूर्ण)

#घोषणा ग_लिखोb(v,c)		(अणु __iowmb(); ग_लिखोb_relaxed((v),(c)); पूर्ण)
#घोषणा ग_लिखोw(v,c)		(अणु __iowmb(); ग_लिखोw_relaxed((v),(c)); पूर्ण)
#घोषणा ग_लिखोl(v,c)		(अणु __iowmb(); ग_लिखोl_relaxed((v),(c)); पूर्ण)
#घोषणा ग_लिखोq(v,c)		(अणु __iowmb(); ग_लिखोq_relaxed((v),(c)); पूर्ण)

/*
 *  I/O port access primitives.
 */
#घोषणा arch_has_dev_port()	(1)
#घोषणा IO_SPACE_LIMIT		(PCI_IO_SIZE - 1)
#घोषणा PCI_IOBASE		((व्योम __iomem *)PCI_IO_START)

/*
 * String version of I/O memory access operations.
 */
बाह्य व्योम __स_नकल_fromio(व्योम *, स्थिर अस्थिर व्योम __iomem *, माप_प्रकार);
बाह्य व्योम __स_नकल_toio(अस्थिर व्योम __iomem *, स्थिर व्योम *, माप_प्रकार);
बाह्य व्योम __स_रखो_io(अस्थिर व्योम __iomem *, पूर्णांक, माप_प्रकार);

#घोषणा स_रखो_io(c,v,l)	__स_रखो_io((c),(v),(l))
#घोषणा स_नकल_fromio(a,c,l)	__स_नकल_fromio((a),(c),(l))
#घोषणा स_नकल_toio(c,a,l)	__स_नकल_toio((c),(a),(l))

/*
 * I/O memory mapping functions.
 */
बाह्य व्योम __iomem *__ioremap(phys_addr_t phys_addr, माप_प्रकार size, pgprot_t prot);
बाह्य व्योम iounmap(अस्थिर व्योम __iomem *addr);
बाह्य व्योम __iomem *ioremap_cache(phys_addr_t phys_addr, माप_प्रकार size);

#घोषणा ioremap(addr, size)		__ioremap((addr), (size), __pgprot(PROT_DEVICE_nGnRE))
#घोषणा ioremap_wc(addr, size)		__ioremap((addr), (size), __pgprot(PROT_NORMAL_NC))
#घोषणा ioremap_np(addr, size)		__ioremap((addr), (size), __pgprot(PROT_DEVICE_nGnRnE))

/*
 * ioअणुपढ़ो,ग_लिखोपूर्णअणु16,32,64पूर्णbe() macros
 */
#घोषणा ioपढ़ो16be(p)		(अणु __u16 __v = be16_to_cpu((__क्रमce __be16)__raw_पढ़ोw(p)); __iormb(__v); __v; पूर्ण)
#घोषणा ioपढ़ो32be(p)		(अणु __u32 __v = be32_to_cpu((__क्रमce __be32)__raw_पढ़ोl(p)); __iormb(__v); __v; पूर्ण)
#घोषणा ioपढ़ो64be(p)		(अणु __u64 __v = be64_to_cpu((__क्रमce __be64)__raw_पढ़ोq(p)); __iormb(__v); __v; पूर्ण)

#घोषणा ioग_लिखो16be(v,p)	(अणु __iowmb(); __raw_ग_लिखोw((__क्रमce __u16)cpu_to_be16(v), p); पूर्ण)
#घोषणा ioग_लिखो32be(v,p)	(अणु __iowmb(); __raw_ग_लिखोl((__क्रमce __u32)cpu_to_be32(v), p); पूर्ण)
#घोषणा ioग_लिखो64be(v,p)	(अणु __iowmb(); __raw_ग_लिखोq((__क्रमce __u64)cpu_to_be64(v), p); पूर्ण)

#समावेश <यंत्र-generic/पन.स>

/*
 * More restrictive address range checking than the शेष implementation
 * (PHYS_OFFSET and PHYS_MASK taken पूर्णांकo account).
 */
#घोषणा ARCH_HAS_VALID_PHYS_ADDR_RANGE
बाह्य पूर्णांक valid_phys_addr_range(phys_addr_t addr, माप_प्रकार size);
बाह्य पूर्णांक valid_mmap_phys_addr_range(अचिन्हित दीर्घ pfn, माप_प्रकार size);

#पूर्ण_अगर	/* __ASM_IO_H */
