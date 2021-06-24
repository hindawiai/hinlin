<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Generic I/O and MEMIO string operations.  */

#घोषणा __ide_insw	insw
#घोषणा __ide_insl	insl
#घोषणा __ide_outsw	outsw
#घोषणा __ide_outsl	outsl

अटल __अंतरभूत__ व्योम __ide_mm_insw(व्योम __iomem *port, व्योम *addr, u32 count)
अणु
	जबतक (count--) अणु
		*(u16 *)addr = पढ़ोw(port);
		addr += 2;
	पूर्ण
पूर्ण

अटल __अंतरभूत__ व्योम __ide_mm_insl(व्योम __iomem *port, व्योम *addr, u32 count)
अणु
	जबतक (count--) अणु
		*(u32 *)addr = पढ़ोl(port);
		addr += 4;
	पूर्ण
पूर्ण

अटल __अंतरभूत__ व्योम __ide_mm_outsw(व्योम __iomem *port, व्योम *addr, u32 count)
अणु
	जबतक (count--) अणु
		ग_लिखोw(*(u16 *)addr, port);
		addr += 2;
	पूर्ण
पूर्ण

अटल __अंतरभूत__ व्योम __ide_mm_outsl(व्योम __iomem * port, व्योम *addr, u32 count)
अणु
	जबतक (count--) अणु
		ग_लिखोl(*(u32 *)addr, port);
		addr += 4;
	पूर्ण
पूर्ण
