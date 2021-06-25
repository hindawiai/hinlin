<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SPARC_IO_H
#घोषणा __SPARC_IO_H

#समावेश <linux/kernel.h>
#समावेश <linux/ioport.h>  /* काष्ठा resource */

#घोषणा IO_SPACE_LIMIT 0xffffffff

#घोषणा स_रखो_io(d,c,sz)     _स_रखो_io(d,c,sz)
#घोषणा स_नकल_fromio(d,s,sz) _स_नकल_fromio(d,s,sz)
#घोषणा स_नकल_toio(d,s,sz)   _स_नकल_toio(d,s,sz)

/*
 * Bus number may be embedded in the higher bits of the physical address.
 * This is why we have no bus number argument to ioremap().
 */
व्योम __iomem *ioremap(phys_addr_t offset, माप_प्रकार size);
व्योम iounmap(अस्थिर व्योम __iomem *addr);

#समावेश <यंत्र-generic/पन.स>

अटल अंतरभूत व्योम _स_रखो_io(अस्थिर व्योम __iomem *dst,
                              पूर्णांक c, __kernel_माप_प्रकार n)
अणु
	अस्थिर व्योम __iomem *d = dst;

	जबतक (n--) अणु
		ग_लिखोb(c, d);
		d++;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम _स_नकल_fromio(व्योम *dst, स्थिर अस्थिर व्योम __iomem *src,
                                  __kernel_माप_प्रकार n)
अणु
	अक्षर *d = dst;

	जबतक (n--) अणु
		अक्षर पंचांगp = पढ़ोb(src);
		*d++ = पंचांगp;
		src++;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम _स_नकल_toio(अस्थिर व्योम __iomem *dst, स्थिर व्योम *src,
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

/*
 * SBus accessors.
 *
 * SBus has only one, memory mapped, I/O space.
 * We करो not need to flip bytes क्रम SBus of course.
 */
अटल अंतरभूत u8 sbus_पढ़ोb(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस *(__क्रमce अस्थिर u8 *)addr;
पूर्ण

अटल अंतरभूत u16 sbus_पढ़ोw(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस *(__क्रमce अस्थिर u16 *)addr;
पूर्ण

अटल अंतरभूत u32 sbus_पढ़ोl(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस *(__क्रमce अस्थिर u32 *)addr;
पूर्ण

अटल अंतरभूत व्योम sbus_ग_लिखोb(u8 b, अस्थिर व्योम __iomem *addr)
अणु
	*(__क्रमce अस्थिर u8 *)addr = b;
पूर्ण

अटल अंतरभूत व्योम sbus_ग_लिखोw(u16 w, अस्थिर व्योम __iomem *addr)
अणु
	*(__क्रमce अस्थिर u16 *)addr = w;
पूर्ण

अटल अंतरभूत व्योम sbus_ग_लिखोl(u32 l, अस्थिर व्योम __iomem *addr)
अणु
	*(__क्रमce अस्थिर u32 *)addr = l;
पूर्ण

अटल अंतरभूत व्योम sbus_स_रखो_io(अस्थिर व्योम __iomem *__dst, पूर्णांक c,
                                  __kernel_माप_प्रकार n)
अणु
	जबतक(n--) अणु
		sbus_ग_लिखोb(c, __dst);
		__dst++;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम sbus_स_नकल_fromio(व्योम *dst,
                                      स्थिर अस्थिर व्योम __iomem *src,
                                      __kernel_माप_प्रकार n)
अणु
	अक्षर *d = dst;

	जबतक (n--) अणु
		अक्षर पंचांगp = sbus_पढ़ोb(src);
		*d++ = पंचांगp;
		src++;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम sbus_स_नकल_toio(अस्थिर व्योम __iomem *dst,
                                    स्थिर व्योम *src,
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

/* Create a भव mapping cookie क्रम an IO port range */
व्योम __iomem *ioport_map(अचिन्हित दीर्घ port, अचिन्हित पूर्णांक nr);
व्योम ioport_unmap(व्योम __iomem *);

/* Create a भव mapping cookie क्रम a PCI BAR (memory or IO) */
काष्ठा pci_dev;
व्योम pci_iounmap(काष्ठा pci_dev *dev, व्योम __iomem *);

अटल अंतरभूत पूर्णांक sbus_can_dma_64bit(व्योम)
अणु
	वापस 0; /* actually, sparc_cpu_model==sun4d */
पूर्ण
अटल अंतरभूत पूर्णांक sbus_can_burst64(व्योम)
अणु
	वापस 0; /* actually, sparc_cpu_model==sun4d */
पूर्ण
काष्ठा device;
व्योम sbus_set_sbus64(काष्ठा device *, पूर्णांक);

#घोषणा __ARCH_HAS_NO_PAGE_ZERO_MAPPED		1


#पूर्ण_अगर /* !(__SPARC_IO_H) */
