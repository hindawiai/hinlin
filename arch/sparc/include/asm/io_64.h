<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SPARC64_IO_H
#घोषणा __SPARC64_IO_H

#समावेश <linux/kernel.h>
#समावेश <linux/compiler.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/page.h>      /* IO address mapping routines need this */
#समावेश <यंत्र/asi.h>
#समावेश <यंत्र-generic/pci_iomap.h>

/* BIO layer definitions. */
बाह्य अचिन्हित दीर्घ kern_base, kern_size;

/* __raw_अणुपढ़ो,ग_लिखोपूर्णअणुb,w,l,qपूर्ण uses direct access.
 * Access the memory as big endian bypassing the cache
 * by using ASI_PHYS_BYPASS_EC_E
 */
#घोषणा __raw_पढ़ोb __raw_पढ़ोb
अटल अंतरभूत u8 __raw_पढ़ोb(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u8 ret;

	__यंत्र__ __अस्थिर__("lduba\t[%1] %2, %0\t/* pci_raw_readb */"
			     : "=r" (ret)
			     : "r" (addr), "i" (ASI_PHYS_BYPASS_EC_E));

	वापस ret;
पूर्ण

#घोषणा __raw_पढ़ोw __raw_पढ़ोw
अटल अंतरभूत u16 __raw_पढ़ोw(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u16 ret;

	__यंत्र__ __अस्थिर__("lduha\t[%1] %2, %0\t/* pci_raw_readw */"
			     : "=r" (ret)
			     : "r" (addr), "i" (ASI_PHYS_BYPASS_EC_E));

	वापस ret;
पूर्ण

#घोषणा __raw_पढ़ोl __raw_पढ़ोl
अटल अंतरभूत u32 __raw_पढ़ोl(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u32 ret;

	__यंत्र__ __अस्थिर__("lduwa\t[%1] %2, %0\t/* pci_raw_readl */"
			     : "=r" (ret)
			     : "r" (addr), "i" (ASI_PHYS_BYPASS_EC_E));

	वापस ret;
पूर्ण

#घोषणा __raw_पढ़ोq __raw_पढ़ोq
अटल अंतरभूत u64 __raw_पढ़ोq(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u64 ret;

	__यंत्र__ __अस्थिर__("ldxa\t[%1] %2, %0\t/* pci_raw_readq */"
			     : "=r" (ret)
			     : "r" (addr), "i" (ASI_PHYS_BYPASS_EC_E));

	वापस ret;
पूर्ण

#घोषणा __raw_ग_लिखोb __raw_ग_लिखोb
अटल अंतरभूत व्योम __raw_ग_लिखोb(u8 b, स्थिर अस्थिर व्योम __iomem *addr)
अणु
	__यंत्र__ __अस्थिर__("stba\t%r0, [%1] %2\t/* pci_raw_writeb */"
			     : /* no outमाला_दो */
			     : "Jr" (b), "r" (addr), "i" (ASI_PHYS_BYPASS_EC_E));
पूर्ण

#घोषणा __raw_ग_लिखोw __raw_ग_लिखोw
अटल अंतरभूत व्योम __raw_ग_लिखोw(u16 w, स्थिर अस्थिर व्योम __iomem *addr)
अणु
	__यंत्र__ __अस्थिर__("stha\t%r0, [%1] %2\t/* pci_raw_writew */"
			     : /* no outमाला_दो */
			     : "Jr" (w), "r" (addr), "i" (ASI_PHYS_BYPASS_EC_E));
पूर्ण

#घोषणा __raw_ग_लिखोl __raw_ग_लिखोl
अटल अंतरभूत व्योम __raw_ग_लिखोl(u32 l, स्थिर अस्थिर व्योम __iomem *addr)
अणु
	__यंत्र__ __अस्थिर__("stwa\t%r0, [%1] %2\t/* pci_raw_writel */"
			     : /* no outमाला_दो */
			     : "Jr" (l), "r" (addr), "i" (ASI_PHYS_BYPASS_EC_E));
पूर्ण

#घोषणा __raw_ग_लिखोq __raw_ग_लिखोq
अटल अंतरभूत व्योम __raw_ग_लिखोq(u64 q, स्थिर अस्थिर व्योम __iomem *addr)
अणु
	__यंत्र__ __अस्थिर__("stxa\t%r0, [%1] %2\t/* pci_raw_writeq */"
			     : /* no outमाला_दो */
			     : "Jr" (q), "r" (addr), "i" (ASI_PHYS_BYPASS_EC_E));
पूर्ण

/* Memory functions, same as I/O accesses on Ultra.
 * Access memory as little endian bypassing
 * the cache by using ASI_PHYS_BYPASS_EC_E_L
 */
#घोषणा पढ़ोb पढ़ोb
#घोषणा पढ़ोb_relaxed पढ़ोb
अटल अंतरभूत u8 पढ़ोb(स्थिर अस्थिर व्योम __iomem *addr)
अणु	u8 ret;

	__यंत्र__ __अस्थिर__("lduba\t[%1] %2, %0\t/* pci_readb */"
			     : "=r" (ret)
			     : "r" (addr), "i" (ASI_PHYS_BYPASS_EC_E_L)
			     : "memory");
	वापस ret;
पूर्ण

#घोषणा पढ़ोw पढ़ोw
#घोषणा पढ़ोw_relaxed पढ़ोw
अटल अंतरभूत u16 पढ़ोw(स्थिर अस्थिर व्योम __iomem *addr)
अणु	u16 ret;

	__यंत्र__ __अस्थिर__("lduha\t[%1] %2, %0\t/* pci_readw */"
			     : "=r" (ret)
			     : "r" (addr), "i" (ASI_PHYS_BYPASS_EC_E_L)
			     : "memory");

	वापस ret;
पूर्ण

#घोषणा पढ़ोl पढ़ोl
#घोषणा पढ़ोl_relaxed पढ़ोl
अटल अंतरभूत u32 पढ़ोl(स्थिर अस्थिर व्योम __iomem *addr)
अणु	u32 ret;

	__यंत्र__ __अस्थिर__("lduwa\t[%1] %2, %0\t/* pci_readl */"
			     : "=r" (ret)
			     : "r" (addr), "i" (ASI_PHYS_BYPASS_EC_E_L)
			     : "memory");

	वापस ret;
पूर्ण

#घोषणा पढ़ोq पढ़ोq
#घोषणा पढ़ोq_relaxed पढ़ोq
अटल अंतरभूत u64 पढ़ोq(स्थिर अस्थिर व्योम __iomem *addr)
अणु	u64 ret;

	__यंत्र__ __अस्थिर__("ldxa\t[%1] %2, %0\t/* pci_readq */"
			     : "=r" (ret)
			     : "r" (addr), "i" (ASI_PHYS_BYPASS_EC_E_L)
			     : "memory");

	वापस ret;
पूर्ण

#घोषणा ग_लिखोb ग_लिखोb
#घोषणा ग_लिखोb_relaxed ग_लिखोb
अटल अंतरभूत व्योम ग_लिखोb(u8 b, अस्थिर व्योम __iomem *addr)
अणु
	__यंत्र__ __अस्थिर__("stba\t%r0, [%1] %2\t/* pci_writeb */"
			     : /* no outमाला_दो */
			     : "Jr" (b), "r" (addr), "i" (ASI_PHYS_BYPASS_EC_E_L)
			     : "memory");
पूर्ण

#घोषणा ग_लिखोw ग_लिखोw
#घोषणा ग_लिखोw_relaxed ग_लिखोw
अटल अंतरभूत व्योम ग_लिखोw(u16 w, अस्थिर व्योम __iomem *addr)
अणु
	__यंत्र__ __अस्थिर__("stha\t%r0, [%1] %2\t/* pci_writew */"
			     : /* no outमाला_दो */
			     : "Jr" (w), "r" (addr), "i" (ASI_PHYS_BYPASS_EC_E_L)
			     : "memory");
पूर्ण

#घोषणा ग_लिखोl ग_लिखोl
#घोषणा ग_लिखोl_relaxed ग_लिखोl
अटल अंतरभूत व्योम ग_लिखोl(u32 l, अस्थिर व्योम __iomem *addr)
अणु
	__यंत्र__ __अस्थिर__("stwa\t%r0, [%1] %2\t/* pci_writel */"
			     : /* no outमाला_दो */
			     : "Jr" (l), "r" (addr), "i" (ASI_PHYS_BYPASS_EC_E_L)
			     : "memory");
पूर्ण

#घोषणा ग_लिखोq ग_लिखोq
#घोषणा ग_लिखोq_relaxed ग_लिखोq
अटल अंतरभूत व्योम ग_लिखोq(u64 q, अस्थिर व्योम __iomem *addr)
अणु
	__यंत्र__ __अस्थिर__("stxa\t%r0, [%1] %2\t/* pci_writeq */"
			     : /* no outमाला_दो */
			     : "Jr" (q), "r" (addr), "i" (ASI_PHYS_BYPASS_EC_E_L)
			     : "memory");
पूर्ण

#घोषणा inb inb
अटल अंतरभूत u8 inb(अचिन्हित दीर्घ addr)
अणु
	वापस पढ़ोb((अस्थिर व्योम __iomem *)addr);
पूर्ण

#घोषणा inw inw
अटल अंतरभूत u16 inw(अचिन्हित दीर्घ addr)
अणु
	वापस पढ़ोw((अस्थिर व्योम __iomem *)addr);
पूर्ण

#घोषणा inl inl
अटल अंतरभूत u32 inl(अचिन्हित दीर्घ addr)
अणु
	वापस पढ़ोl((अस्थिर व्योम __iomem *)addr);
पूर्ण

#घोषणा outb outb
अटल अंतरभूत व्योम outb(u8 b, अचिन्हित दीर्घ addr)
अणु
	ग_लिखोb(b, (अस्थिर व्योम __iomem *)addr);
पूर्ण

#घोषणा outw outw
अटल अंतरभूत व्योम outw(u16 w, अचिन्हित दीर्घ addr)
अणु
	ग_लिखोw(w, (अस्थिर व्योम __iomem *)addr);
पूर्ण

#घोषणा outl outl
अटल अंतरभूत व्योम outl(u32 l, अचिन्हित दीर्घ addr)
अणु
	ग_लिखोl(l, (अस्थिर व्योम __iomem *)addr);
पूर्ण


#घोषणा inb_p(__addr) 		inb(__addr)
#घोषणा outb_p(__b, __addr)	outb(__b, __addr)
#घोषणा inw_p(__addr)		inw(__addr)
#घोषणा outw_p(__w, __addr)	outw(__w, __addr)
#घोषणा inl_p(__addr)		inl(__addr)
#घोषणा outl_p(__l, __addr)	outl(__l, __addr)

व्योम outsb(अचिन्हित दीर्घ, स्थिर व्योम *, अचिन्हित दीर्घ);
व्योम outsw(अचिन्हित दीर्घ, स्थिर व्योम *, अचिन्हित दीर्घ);
व्योम outsl(अचिन्हित दीर्घ, स्थिर व्योम *, अचिन्हित दीर्घ);
व्योम insb(अचिन्हित दीर्घ, व्योम *, अचिन्हित दीर्घ);
व्योम insw(अचिन्हित दीर्घ, व्योम *, अचिन्हित दीर्घ);
व्योम insl(अचिन्हित दीर्घ, व्योम *, अचिन्हित दीर्घ);

अटल अंतरभूत व्योम पढ़ोsb(व्योम __iomem *port, व्योम *buf, अचिन्हित दीर्घ count)
अणु
	insb((अचिन्हित दीर्घ __क्रमce)port, buf, count);
पूर्ण
अटल अंतरभूत व्योम पढ़ोsw(व्योम __iomem *port, व्योम *buf, अचिन्हित दीर्घ count)
अणु
	insw((अचिन्हित दीर्घ __क्रमce)port, buf, count);
पूर्ण

अटल अंतरभूत व्योम पढ़ोsl(व्योम __iomem *port, व्योम *buf, अचिन्हित दीर्घ count)
अणु
	insl((अचिन्हित दीर्घ __क्रमce)port, buf, count);
पूर्ण

अटल अंतरभूत व्योम ग_लिखोsb(व्योम __iomem *port, स्थिर व्योम *buf, अचिन्हित दीर्घ count)
अणु
	outsb((अचिन्हित दीर्घ __क्रमce)port, buf, count);
पूर्ण

अटल अंतरभूत व्योम ग_लिखोsw(व्योम __iomem *port, स्थिर व्योम *buf, अचिन्हित दीर्घ count)
अणु
	outsw((अचिन्हित दीर्घ __क्रमce)port, buf, count);
पूर्ण

अटल अंतरभूत व्योम ग_लिखोsl(व्योम __iomem *port, स्थिर व्योम *buf, अचिन्हित दीर्घ count)
अणु
	outsl((अचिन्हित दीर्घ __क्रमce)port, buf, count);
पूर्ण

#घोषणा ioपढ़ो8_rep(p,d,l)	पढ़ोsb(p,d,l)
#घोषणा ioपढ़ो16_rep(p,d,l)	पढ़ोsw(p,d,l)
#घोषणा ioपढ़ो32_rep(p,d,l)	पढ़ोsl(p,d,l)
#घोषणा ioग_लिखो8_rep(p,d,l)	ग_लिखोsb(p,d,l)
#घोषणा ioग_लिखो16_rep(p,d,l)	ग_लिखोsw(p,d,l)
#घोषणा ioग_लिखो32_rep(p,d,l)	ग_लिखोsl(p,d,l)

/* Valid I/O Space regions are anywhere, because each PCI bus supported
 * can live in an arbitrary area of the physical address range.
 */
#घोषणा IO_SPACE_LIMIT 0xffffffffffffffffUL

/* Now, SBUS variants, only dअगरference from PCI is that we करो
 * not use little-endian ASIs.
 */
अटल अंतरभूत u8 sbus_पढ़ोb(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस __raw_पढ़ोb(addr);
पूर्ण

अटल अंतरभूत u16 sbus_पढ़ोw(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस __raw_पढ़ोw(addr);
पूर्ण

अटल अंतरभूत u32 sbus_पढ़ोl(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस __raw_पढ़ोl(addr);
पूर्ण

अटल अंतरभूत u64 sbus_पढ़ोq(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस __raw_पढ़ोq(addr);
पूर्ण

अटल अंतरभूत व्योम sbus_ग_लिखोb(u8 b, अस्थिर व्योम __iomem *addr)
अणु
	__raw_ग_लिखोb(b, addr);
पूर्ण

अटल अंतरभूत व्योम sbus_ग_लिखोw(u16 w, अस्थिर व्योम __iomem *addr)
अणु
	__raw_ग_लिखोw(w, addr);
पूर्ण

अटल अंतरभूत व्योम sbus_ग_लिखोl(u32 l, अस्थिर व्योम __iomem *addr)
अणु
	__raw_ग_लिखोl(l, addr);
पूर्ण

अटल अंतरभूत व्योम sbus_ग_लिखोq(u64 q, अस्थिर व्योम __iomem *addr)
अणु
	__raw_ग_लिखोq(q, addr);
पूर्ण

अटल अंतरभूत व्योम sbus_स_रखो_io(अस्थिर व्योम __iomem *dst, पूर्णांक c, __kernel_माप_प्रकार n)
अणु
	जबतक(n--) अणु
		sbus_ग_लिखोb(c, dst);
		dst++;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम स_रखो_io(अस्थिर व्योम __iomem *dst, पूर्णांक c, __kernel_माप_प्रकार n)
अणु
	अस्थिर व्योम __iomem *d = dst;

	जबतक (n--) अणु
		ग_लिखोb(c, d);
		d++;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम sbus_स_नकल_fromio(व्योम *dst, स्थिर अस्थिर व्योम __iomem *src,
				      __kernel_माप_प्रकार n)
अणु
	अक्षर *d = dst;

	जबतक (n--) अणु
		अक्षर पंचांगp = sbus_पढ़ोb(src);
		*d++ = पंचांगp;
		src++;
	पूर्ण
पूर्ण


अटल अंतरभूत व्योम स_नकल_fromio(व्योम *dst, स्थिर अस्थिर व्योम __iomem *src,
				 __kernel_माप_प्रकार n)
अणु
	अक्षर *d = dst;

	जबतक (n--) अणु
		अक्षर पंचांगp = पढ़ोb(src);
		*d++ = पंचांगp;
		src++;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम sbus_स_नकल_toio(अस्थिर व्योम __iomem *dst, स्थिर व्योम *src,
				    __kernel_माप_प्रकार n)
अणु
	स्थिर अक्षर *s = src;
	अस्थिर व्योम __iomem *d = dst;

	जबतक (n--) अणु
		अक्षर पंचांगp = *s++;
		sbus_ग_लिखोb(पंचांगp, d);
		d++;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम स_नकल_toio(अस्थिर व्योम __iomem *dst, स्थिर व्योम *src,
			       __kernel_माप_प्रकार n)
अणु
	स्थिर अक्षर *s = src;
	अस्थिर व्योम __iomem *d = dst;

	जबतक (n--) अणु
		अक्षर पंचांगp = *s++;
		ग_लिखोb(पंचांगp, d);
		d++;
	पूर्ण
पूर्ण

#अगर_घोषित __KERNEL__

/* On sparc64 we have the whole physical IO address space accessible
 * using physically addressed loads and stores, so this करोes nothing.
 */
अटल अंतरभूत व्योम __iomem *ioremap(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ size)
अणु
	वापस (व्योम __iomem *)offset;
पूर्ण

#घोषणा ioremap_uc(X,Y)			ioremap((X),(Y))
#घोषणा ioremap_wc(X,Y)			ioremap((X),(Y))
#घोषणा ioremap_wt(X,Y)			ioremap((X),(Y))
अटल अंतरभूत व्योम __iomem *ioremap_np(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ size)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम iounmap(अस्थिर व्योम __iomem *addr)
अणु
पूर्ण

#घोषणा ioपढ़ो8			पढ़ोb
#घोषणा ioपढ़ो16		पढ़ोw
#घोषणा ioपढ़ो16be		__raw_पढ़ोw
#घोषणा ioपढ़ो32		पढ़ोl
#घोषणा ioपढ़ो32be		__raw_पढ़ोl
#घोषणा ioग_लिखो8		ग_लिखोb
#घोषणा ioग_लिखो16		ग_लिखोw
#घोषणा ioग_लिखो16be		__raw_ग_लिखोw
#घोषणा ioग_लिखो32		ग_लिखोl
#घोषणा ioग_लिखो32be		__raw_ग_लिखोl

/* Create a भव mapping cookie क्रम an IO port range */
व्योम __iomem *ioport_map(अचिन्हित दीर्घ port, अचिन्हित पूर्णांक nr);
व्योम ioport_unmap(व्योम __iomem *);

/* Create a भव mapping cookie क्रम a PCI BAR (memory or IO) */
काष्ठा pci_dev;
व्योम pci_iounmap(काष्ठा pci_dev *dev, व्योम __iomem *);

अटल अंतरभूत पूर्णांक sbus_can_dma_64bit(व्योम)
अणु
	वापस 1;
पूर्ण
अटल अंतरभूत पूर्णांक sbus_can_burst64(व्योम)
अणु
	वापस 1;
पूर्ण
काष्ठा device;
व्योम sbus_set_sbus64(काष्ठा device *, पूर्णांक);

/*
 * Convert a physical poपूर्णांकer to a भव kernel poपूर्णांकer क्रम /dev/mem
 * access
 */
#घोषणा xlate_dev_mem_ptr(p)	__va(p)

#पूर्ण_अगर

#पूर्ण_अगर /* !(__SPARC64_IO_H) */
