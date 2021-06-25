<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IO_H
#घोषणा _ASM_IO_H

#समावेश <linux/types.h>
#समावेश <linux/pgtable.h>

#घोषणा virt_to_phys(a) ((अचिन्हित दीर्घ)__pa(a))
#घोषणा phys_to_virt(a) __va(a)
#घोषणा virt_to_bus virt_to_phys
#घोषणा bus_to_virt phys_to_virt

अटल अंतरभूत अचिन्हित दीर्घ isa_bus_to_virt(अचिन्हित दीर्घ addr) अणु
	BUG();
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ isa_virt_to_bus(व्योम *addr) अणु
	BUG();
	वापस 0;
पूर्ण

/*
 * Memory mapped I/O
 *
 * पढ़ोX()/ग_लिखोX() करो byteswapping and take an ioremapped address
 * __raw_पढ़ोX()/__raw_ग_लिखोX() करोn't byteswap and take an ioremapped address.
 * gsc_*() करोn't byteswap and operate on physical addresses;
 *   eg dev->hpa or 0xfee00000.
 */

अटल अंतरभूत अचिन्हित अक्षर gsc_पढ़ोb(अचिन्हित दीर्घ addr)
अणु
	दीर्घ flags;
	अचिन्हित अक्षर ret;

	__यंत्र__ __अस्थिर__(
	"	rsm	%3,%0\n"
	"	ldbx	0(%2),%1\n"
	"	mtsm	%0\n"
	: "=&r" (flags), "=r" (ret) : "r" (addr), "i" (PSW_SM_D) );

	वापस ret;
पूर्ण

अटल अंतरभूत अचिन्हित लघु gsc_पढ़ोw(अचिन्हित दीर्घ addr)
अणु
	दीर्घ flags;
	अचिन्हित लघु ret;

	__यंत्र__ __अस्थिर__(
	"	rsm	%3,%0\n"
	"	ldhx	0(%2),%1\n"
	"	mtsm	%0\n"
	: "=&r" (flags), "=r" (ret) : "r" (addr), "i" (PSW_SM_D) );

	वापस ret;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक gsc_पढ़ोl(अचिन्हित दीर्घ addr)
अणु
	u32 ret;

	__यंत्र__ __अस्थिर__(
	"	ldwax	0(%1),%0\n"
	: "=r" (ret) : "r" (addr) );

	वापस ret;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ दीर्घ gsc_पढ़ोq(अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ दीर्घ ret;

#अगर_घोषित CONFIG_64BIT
	__यंत्र__ __अस्थिर__(
	"	ldda	0(%1),%0\n"
	:  "=r" (ret) : "r" (addr) );
#अन्यथा
	/* two पढ़ोs may have side effects.. */
	ret = ((u64) gsc_पढ़ोl(addr)) << 32;
	ret |= gsc_पढ़ोl(addr+4);
#पूर्ण_अगर
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम gsc_ग_लिखोb(अचिन्हित अक्षर val, अचिन्हित दीर्घ addr)
अणु
	दीर्घ flags;
	__यंत्र__ __अस्थिर__(
	"	rsm	%3,%0\n"
	"	stbs	%1,0(%2)\n"
	"	mtsm	%0\n"
	: "=&r" (flags) :  "r" (val), "r" (addr), "i" (PSW_SM_D) );
पूर्ण

अटल अंतरभूत व्योम gsc_ग_लिखोw(अचिन्हित लघु val, अचिन्हित दीर्घ addr)
अणु
	दीर्घ flags;
	__यंत्र__ __अस्थिर__(
	"	rsm	%3,%0\n"
	"	sths	%1,0(%2)\n"
	"	mtsm	%0\n"
	: "=&r" (flags) :  "r" (val), "r" (addr), "i" (PSW_SM_D) );
पूर्ण

अटल अंतरभूत व्योम gsc_ग_लिखोl(अचिन्हित पूर्णांक val, अचिन्हित दीर्घ addr)
अणु
	__यंत्र__ __अस्थिर__(
	"	stwas	%0,0(%1)\n"
	: :  "r" (val), "r" (addr) );
पूर्ण

अटल अंतरभूत व्योम gsc_ग_लिखोq(अचिन्हित दीर्घ दीर्घ val, अचिन्हित दीर्घ addr)
अणु
#अगर_घोषित CONFIG_64BIT
	__यंत्र__ __अस्थिर__(
	"	stda	%0,0(%1)\n"
	: :  "r" (val), "r" (addr) );
#अन्यथा
	/* two ग_लिखोs may have side effects.. */
	gsc_ग_लिखोl(val >> 32, addr);
	gsc_ग_लिखोl(val, addr+4);
#पूर्ण_अगर
पूर्ण

/*
 * The standard PCI ioremap पूर्णांकerfaces
 */
व्योम __iomem *ioremap(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ size);
#घोषणा ioremap_wc			ioremap
#घोषणा ioremap_uc			ioremap

बाह्य व्योम iounmap(स्थिर अस्थिर व्योम __iomem *addr);

अटल अंतरभूत अचिन्हित अक्षर __raw_पढ़ोb(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस (*(अस्थिर अचिन्हित अक्षर __क्रमce *) (addr));
पूर्ण
अटल अंतरभूत अचिन्हित लघु __raw_पढ़ोw(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस *(अस्थिर अचिन्हित लघु __क्रमce *) addr;
पूर्ण
अटल अंतरभूत अचिन्हित पूर्णांक __raw_पढ़ोl(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस *(अस्थिर अचिन्हित पूर्णांक __क्रमce *) addr;
पूर्ण
अटल अंतरभूत अचिन्हित दीर्घ दीर्घ __raw_पढ़ोq(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस *(अस्थिर अचिन्हित दीर्घ दीर्घ __क्रमce *) addr;
पूर्ण

अटल अंतरभूत व्योम __raw_ग_लिखोb(अचिन्हित अक्षर b, अस्थिर व्योम __iomem *addr)
अणु
	*(अस्थिर अचिन्हित अक्षर __क्रमce *) addr = b;
पूर्ण
अटल अंतरभूत व्योम __raw_ग_लिखोw(अचिन्हित लघु b, अस्थिर व्योम __iomem *addr)
अणु
	*(अस्थिर अचिन्हित लघु __क्रमce *) addr = b;
पूर्ण
अटल अंतरभूत व्योम __raw_ग_लिखोl(अचिन्हित पूर्णांक b, अस्थिर व्योम __iomem *addr)
अणु
	*(अस्थिर अचिन्हित पूर्णांक __क्रमce *) addr = b;
पूर्ण
अटल अंतरभूत व्योम __raw_ग_लिखोq(अचिन्हित दीर्घ दीर्घ b, अस्थिर व्योम __iomem *addr)
अणु
	*(अस्थिर अचिन्हित दीर्घ दीर्घ __क्रमce *) addr = b;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर पढ़ोb(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस __raw_पढ़ोb(addr);
पूर्ण
अटल अंतरभूत अचिन्हित लघु पढ़ोw(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस le16_to_cpu((__le16 __क्रमce) __raw_पढ़ोw(addr));
पूर्ण
अटल अंतरभूत अचिन्हित पूर्णांक पढ़ोl(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस le32_to_cpu((__le32 __क्रमce) __raw_पढ़ोl(addr));
पूर्ण
अटल अंतरभूत अचिन्हित दीर्घ दीर्घ पढ़ोq(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस le64_to_cpu((__le64 __क्रमce) __raw_पढ़ोq(addr));
पूर्ण

अटल अंतरभूत व्योम ग_लिखोb(अचिन्हित अक्षर b, अस्थिर व्योम __iomem *addr)
अणु
	__raw_ग_लिखोb(b, addr);
पूर्ण
अटल अंतरभूत व्योम ग_लिखोw(अचिन्हित लघु w, अस्थिर व्योम __iomem *addr)
अणु
	__raw_ग_लिखोw((__u16 __क्रमce) cpu_to_le16(w), addr);
पूर्ण
अटल अंतरभूत व्योम ग_लिखोl(अचिन्हित पूर्णांक l, अस्थिर व्योम __iomem *addr)
अणु
	__raw_ग_लिखोl((__u32 __क्रमce) cpu_to_le32(l), addr);
पूर्ण
अटल अंतरभूत व्योम ग_लिखोq(अचिन्हित दीर्घ दीर्घ q, अस्थिर व्योम __iomem *addr)
अणु
	__raw_ग_लिखोq((__u64 __क्रमce) cpu_to_le64(q), addr);
पूर्ण

#घोषणा	पढ़ोb	पढ़ोb
#घोषणा	पढ़ोw	पढ़ोw
#घोषणा	पढ़ोl	पढ़ोl
#घोषणा पढ़ोq	पढ़ोq
#घोषणा ग_लिखोb	ग_लिखोb
#घोषणा ग_लिखोw	ग_लिखोw
#घोषणा ग_लिखोl	ग_लिखोl
#घोषणा ग_लिखोq	ग_लिखोq

#घोषणा पढ़ोb_relaxed(addr)	पढ़ोb(addr)
#घोषणा पढ़ोw_relaxed(addr)	पढ़ोw(addr)
#घोषणा पढ़ोl_relaxed(addr)	पढ़ोl(addr)
#घोषणा पढ़ोq_relaxed(addr)	पढ़ोq(addr)
#घोषणा ग_लिखोb_relaxed(b, addr)	ग_लिखोb(b, addr)
#घोषणा ग_लिखोw_relaxed(w, addr)	ग_लिखोw(w, addr)
#घोषणा ग_लिखोl_relaxed(l, addr)	ग_लिखोl(l, addr)
#घोषणा ग_लिखोq_relaxed(q, addr)	ग_लिखोq(q, addr)

व्योम स_रखो_io(अस्थिर व्योम __iomem *addr, अचिन्हित अक्षर val, पूर्णांक count);
व्योम स_नकल_fromio(व्योम *dst, स्थिर अस्थिर व्योम __iomem *src, पूर्णांक count);
व्योम स_नकल_toio(अस्थिर व्योम __iomem *dst, स्थिर व्योम *src, पूर्णांक count);

/* Port-space IO */

#घोषणा inb_p inb
#घोषणा inw_p inw
#घोषणा inl_p inl
#घोषणा outb_p outb
#घोषणा outw_p outw
#घोषणा outl_p outl

बाह्य अचिन्हित अक्षर eisa_in8(अचिन्हित लघु port);
बाह्य अचिन्हित लघु eisa_in16(अचिन्हित लघु port);
बाह्य अचिन्हित पूर्णांक eisa_in32(अचिन्हित लघु port);
बाह्य व्योम eisa_out8(अचिन्हित अक्षर data, अचिन्हित लघु port);
बाह्य व्योम eisa_out16(अचिन्हित लघु data, अचिन्हित लघु port);
बाह्य व्योम eisa_out32(अचिन्हित पूर्णांक data, अचिन्हित लघु port);

#अगर defined(CONFIG_PCI)
बाह्य अचिन्हित अक्षर inb(पूर्णांक addr);
बाह्य अचिन्हित लघु inw(पूर्णांक addr);
बाह्य अचिन्हित पूर्णांक inl(पूर्णांक addr);

बाह्य व्योम outb(अचिन्हित अक्षर b, पूर्णांक addr);
बाह्य व्योम outw(अचिन्हित लघु b, पूर्णांक addr);
बाह्य व्योम outl(अचिन्हित पूर्णांक b, पूर्णांक addr);
#या_अगर defined(CONFIG_EISA)
#घोषणा inb eisa_in8
#घोषणा inw eisa_in16
#घोषणा inl eisa_in32
#घोषणा outb eisa_out8
#घोषणा outw eisa_out16
#घोषणा outl eisa_out32
#अन्यथा
अटल अंतरभूत अक्षर inb(अचिन्हित दीर्घ addr)
अणु
	BUG();
	वापस -1;
पूर्ण

अटल अंतरभूत लघु inw(अचिन्हित दीर्घ addr)
अणु
	BUG();
	वापस -1;
पूर्ण

अटल अंतरभूत पूर्णांक inl(अचिन्हित दीर्घ addr)
अणु
	BUG();
	वापस -1;
पूर्ण

#घोषणा outb(x, y)	BUG()
#घोषणा outw(x, y)	BUG()
#घोषणा outl(x, y)	BUG()
#पूर्ण_अगर

/*
 * String versions of in/out ops:
 */
बाह्य व्योम insb (अचिन्हित दीर्घ port, व्योम *dst, अचिन्हित दीर्घ count);
बाह्य व्योम insw (अचिन्हित दीर्घ port, व्योम *dst, अचिन्हित दीर्घ count);
बाह्य व्योम insl (अचिन्हित दीर्घ port, व्योम *dst, अचिन्हित दीर्घ count);
बाह्य व्योम outsb (अचिन्हित दीर्घ port, स्थिर व्योम *src, अचिन्हित दीर्घ count);
बाह्य व्योम outsw (अचिन्हित दीर्घ port, स्थिर व्योम *src, अचिन्हित दीर्घ count);
बाह्य व्योम outsl (अचिन्हित दीर्घ port, स्थिर व्योम *src, अचिन्हित दीर्घ count);


/* IO Port space is :      BBiiii   where BB is HBA number. */
#घोषणा IO_SPACE_LIMIT 0x00ffffff

/* PA machines have an MM I/O space from 0xf0000000-0xffffffff in 32
 * bit mode and from 0xfffffffff0000000-0xfffffffffffffff in 64 bit
 * mode (essentially just sign extending.  This macro takes in a 32
 * bit I/O address (still with the leading f) and outमाला_दो the correct
 * value क्रम either 32 or 64 bit mode */
#घोषणा F_EXTEND(x) ((अचिन्हित दीर्घ)((x) | (0xffffffff00000000ULL)))

#घोषणा ioपढ़ो64 ioपढ़ो64
#घोषणा ioपढ़ो64be ioपढ़ो64be
#घोषणा ioग_लिखो64 ioग_लिखो64
#घोषणा ioग_लिखो64be ioग_लिखो64be
बाह्य u64 ioपढ़ो64(स्थिर व्योम __iomem *addr);
बाह्य u64 ioपढ़ो64be(स्थिर व्योम __iomem *addr);
बाह्य व्योम ioग_लिखो64(u64 val, व्योम __iomem *addr);
बाह्य व्योम ioग_लिखो64be(u64 val, व्योम __iomem *addr);

#समावेश <यंत्र-generic/iomap.h>

/*
 * Convert a physical poपूर्णांकer to a भव kernel poपूर्णांकer क्रम /dev/mem
 * access
 */
#घोषणा xlate_dev_mem_ptr(p)	__va(p)

बाह्य पूर्णांक devmem_is_allowed(अचिन्हित दीर्घ pfn);

#पूर्ण_अगर
