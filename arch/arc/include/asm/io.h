<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#अगर_अघोषित _ASM_ARC_IO_H
#घोषणा _ASM_ARC_IO_H

#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/unaligned.h>

#अगर_घोषित CONFIG_ISA_ARCV2
#समावेश <यंत्र/barrier.h>
#घोषणा __iormb()		rmb()
#घोषणा __iowmb()		wmb()
#अन्यथा
#घोषणा __iormb()		करो अणु पूर्ण जबतक (0)
#घोषणा __iowmb()		करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

बाह्य व्योम __iomem *ioremap(phys_addr_t paddr, अचिन्हित दीर्घ size);
बाह्य व्योम __iomem *ioremap_prot(phys_addr_t paddr, अचिन्हित दीर्घ size,
				  अचिन्हित दीर्घ flags);
अटल अंतरभूत व्योम __iomem *ioport_map(अचिन्हित दीर्घ port, अचिन्हित पूर्णांक nr)
अणु
	वापस (व्योम __iomem *)port;
पूर्ण

अटल अंतरभूत व्योम ioport_unmap(व्योम __iomem *addr)
अणु
पूर्ण

बाह्य व्योम iounmap(स्थिर व्योम __iomem *addr);

/*
 * ioअणुपढ़ो,ग_लिखोपूर्णअणु16,32पूर्णbe() macros
 */
#घोषणा ioपढ़ो16be(p)		(अणु u16 __v = be16_to_cpu((__क्रमce __be16)__raw_पढ़ोw(p)); __iormb(); __v; पूर्ण)
#घोषणा ioपढ़ो32be(p)		(अणु u32 __v = be32_to_cpu((__क्रमce __be32)__raw_पढ़ोl(p)); __iormb(); __v; पूर्ण)

#घोषणा ioग_लिखो16be(v,p)	(अणु __iowmb(); __raw_ग_लिखोw((__क्रमce u16)cpu_to_be16(v), p); पूर्ण)
#घोषणा ioग_लिखो32be(v,p)	(अणु __iowmb(); __raw_ग_लिखोl((__क्रमce u32)cpu_to_be32(v), p); पूर्ण)

/* Change काष्ठा page to physical address */
#घोषणा page_to_phys(page)		(page_to_pfn(page) << PAGE_SHIFT)

#घोषणा __raw_पढ़ोb __raw_पढ़ोb
अटल अंतरभूत u8 __raw_पढ़ोb(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u8 b;

	__यंत्र__ __अस्थिर__(
	"	ldb%U1 %0, %1	\n"
	: "=r" (b)
	: "m" (*(अस्थिर u8 __क्रमce *)addr)
	: "memory");

	वापस b;
पूर्ण

#घोषणा __raw_पढ़ोw __raw_पढ़ोw
अटल अंतरभूत u16 __raw_पढ़ोw(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u16 s;

	__यंत्र__ __अस्थिर__(
	"	ldw%U1 %0, %1	\n"
	: "=r" (s)
	: "m" (*(अस्थिर u16 __क्रमce *)addr)
	: "memory");

	वापस s;
पूर्ण

#घोषणा __raw_पढ़ोl __raw_पढ़ोl
अटल अंतरभूत u32 __raw_पढ़ोl(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u32 w;

	__यंत्र__ __अस्थिर__(
	"	ld%U1 %0, %1	\n"
	: "=r" (w)
	: "m" (*(अस्थिर u32 __क्रमce *)addr)
	: "memory");

	वापस w;
पूर्ण

/*
 * अणुपढ़ो,ग_लिखोपूर्णsअणुb,w,lपूर्ण() repeatedly access the same IO address in
 * native endianness in 8-, 16-, 32-bit chunks अणुपूर्णांकo,fromपूर्ण memory,
 * @count बार
 */
#घोषणा __raw_पढ़ोsx(t,f) \
अटल अंतरभूत व्योम __raw_पढ़ोs##f(स्थिर अस्थिर व्योम __iomem *addr,	\
				  व्योम *ptr, अचिन्हित पूर्णांक count)	\
अणु									\
	bool is_aligned = ((अचिन्हित दीर्घ)ptr % ((t) / 8)) == 0;	\
	u##t *buf = ptr;						\
									\
	अगर (!count)							\
		वापस;							\
									\
	/* Some ARC CPU's don't support unaligned accesses */		\
	अगर (is_aligned) अणु						\
		करो अणु							\
			u##t x = __raw_पढ़ो##f(addr);			\
			*buf++ = x;					\
		पूर्ण जबतक (--count);					\
	पूर्ण अन्यथा अणु							\
		करो अणु							\
			u##t x = __raw_पढ़ो##f(addr);			\
			put_unaligned(x, buf++);			\
		पूर्ण जबतक (--count);					\
	पूर्ण								\
पूर्ण

#घोषणा __raw_पढ़ोsb __raw_पढ़ोsb
__raw_पढ़ोsx(8, b)
#घोषणा __raw_पढ़ोsw __raw_पढ़ोsw
__raw_पढ़ोsx(16, w)
#घोषणा __raw_पढ़ोsl __raw_पढ़ोsl
__raw_पढ़ोsx(32, l)

#घोषणा __raw_ग_लिखोb __raw_ग_लिखोb
अटल अंतरभूत व्योम __raw_ग_लिखोb(u8 b, अस्थिर व्योम __iomem *addr)
अणु
	__यंत्र__ __अस्थिर__(
	"	stb%U1 %0, %1	\n"
	:
	: "r" (b), "m" (*(अस्थिर u8 __क्रमce *)addr)
	: "memory");
पूर्ण

#घोषणा __raw_ग_लिखोw __raw_ग_लिखोw
अटल अंतरभूत व्योम __raw_ग_लिखोw(u16 s, अस्थिर व्योम __iomem *addr)
अणु
	__यंत्र__ __अस्थिर__(
	"	stw%U1 %0, %1	\n"
	:
	: "r" (s), "m" (*(अस्थिर u16 __क्रमce *)addr)
	: "memory");

पूर्ण

#घोषणा __raw_ग_लिखोl __raw_ग_लिखोl
अटल अंतरभूत व्योम __raw_ग_लिखोl(u32 w, अस्थिर व्योम __iomem *addr)
अणु
	__यंत्र__ __अस्थिर__(
	"	st%U1 %0, %1	\n"
	:
	: "r" (w), "m" (*(अस्थिर u32 __क्रमce *)addr)
	: "memory");

पूर्ण

#घोषणा __raw_ग_लिखोsx(t,f)						\
अटल अंतरभूत व्योम __raw_ग_लिखोs##f(अस्थिर व्योम __iomem *addr, 	\
				   स्थिर व्योम *ptr, अचिन्हित पूर्णांक count)	\
अणु									\
	bool is_aligned = ((अचिन्हित दीर्घ)ptr % ((t) / 8)) == 0;	\
	स्थिर u##t *buf = ptr;						\
									\
	अगर (!count)							\
		वापस;							\
									\
	/* Some ARC CPU's don't support unaligned accesses */		\
	अगर (is_aligned) अणु						\
		करो अणु							\
			__raw_ग_लिखो##f(*buf++, addr);			\
		पूर्ण जबतक (--count);					\
	पूर्ण अन्यथा अणु							\
		करो अणु							\
			__raw_ग_लिखो##f(get_unaligned(buf++), addr);	\
		पूर्ण जबतक (--count);					\
	पूर्ण								\
पूर्ण

#घोषणा __raw_ग_लिखोsb __raw_ग_लिखोsb
__raw_ग_लिखोsx(8, b)
#घोषणा __raw_ग_लिखोsw __raw_ग_लिखोsw
__raw_ग_लिखोsx(16, w)
#घोषणा __raw_ग_लिखोsl __raw_ग_लिखोsl
__raw_ग_लिखोsx(32, l)

/*
 * MMIO can also get buffered/optimized in micro-arch, so barriers needed
 * Based on ARM model क्रम the typical use हाल
 *
 *	<ST [DMA buffer]>
 *	<ग_लिखोl MMIO "go" reg>
 *  or:
 *	<पढ़ोl MMIO "status" reg>
 *	<LD [DMA buffer]>
 *
 * http://lkml.kernel.org/r/20150622133656.GG1583@arm.com
 */
#घोषणा पढ़ोb(c)		(अणु u8  __v = पढ़ोb_relaxed(c); __iormb(); __v; पूर्ण)
#घोषणा पढ़ोw(c)		(अणु u16 __v = पढ़ोw_relaxed(c); __iormb(); __v; पूर्ण)
#घोषणा पढ़ोl(c)		(अणु u32 __v = पढ़ोl_relaxed(c); __iormb(); __v; पूर्ण)
#घोषणा पढ़ोsb(p,d,l)		(अणु __raw_पढ़ोsb(p,d,l); __iormb(); पूर्ण)
#घोषणा पढ़ोsw(p,d,l)		(अणु __raw_पढ़ोsw(p,d,l); __iormb(); पूर्ण)
#घोषणा पढ़ोsl(p,d,l)		(अणु __raw_पढ़ोsl(p,d,l); __iormb(); पूर्ण)

#घोषणा ग_लिखोb(v,c)		(अणु __iowmb(); ग_लिखोb_relaxed(v,c); पूर्ण)
#घोषणा ग_लिखोw(v,c)		(अणु __iowmb(); ग_लिखोw_relaxed(v,c); पूर्ण)
#घोषणा ग_लिखोl(v,c)		(अणु __iowmb(); ग_लिखोl_relaxed(v,c); पूर्ण)
#घोषणा ग_लिखोsb(p,d,l)		(अणु __iowmb(); __raw_ग_लिखोsb(p,d,l); पूर्ण)
#घोषणा ग_लिखोsw(p,d,l)		(अणु __iowmb(); __raw_ग_लिखोsw(p,d,l); पूर्ण)
#घोषणा ग_लिखोsl(p,d,l)		(अणु __iowmb(); __raw_ग_लिखोsl(p,d,l); पूर्ण)

/*
 * Relaxed API क्रम drivers which can handle barrier ordering themselves
 *
 * Also these are defined to perक्रमm little endian accesses.
 * To provide the typical device रेजिस्टर semantics of fixed endian,
 * swap the byte order क्रम Big Endian
 *
 * http://lkml.kernel.org/r/201603100845.30602.arnd@arndb.de
 */
#घोषणा पढ़ोb_relaxed(c)	__raw_पढ़ोb(c)
#घोषणा पढ़ोw_relaxed(c) (अणु u16 __r = le16_to_cpu((__क्रमce __le16) \
					__raw_पढ़ोw(c)); __r; पूर्ण)
#घोषणा पढ़ोl_relaxed(c) (अणु u32 __r = le32_to_cpu((__क्रमce __le32) \
					__raw_पढ़ोl(c)); __r; पूर्ण)

#घोषणा ग_लिखोb_relaxed(v,c)	__raw_ग_लिखोb(v,c)
#घोषणा ग_लिखोw_relaxed(v,c)	__raw_ग_लिखोw((__क्रमce u16) cpu_to_le16(v),c)
#घोषणा ग_लिखोl_relaxed(v,c)	__raw_ग_लिखोl((__क्रमce u32) cpu_to_le32(v),c)

#समावेश <यंत्र-generic/पन.स>

#पूर्ण_अगर /* _ASM_ARC_IO_H */
