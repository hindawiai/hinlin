<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_M68K_ZORRO_H
#घोषणा _ASM_M68K_ZORRO_H

#समावेश <यंत्र/raw_पन.स>
#समावेश <यंत्र/kmap.h>

#घोषणा z_पढ़ोb raw_inb
#घोषणा z_पढ़ोw raw_inw
#घोषणा z_पढ़ोl raw_inl

#घोषणा z_ग_लिखोb raw_outb
#घोषणा z_ग_लिखोw raw_outw
#घोषणा z_ग_लिखोl raw_outl

#घोषणा z_स_रखो_io(a,b,c)	स_रखो((व्योम *)(a),(b),(c))
#घोषणा z_स_नकल_fromio(a,b,c)	स_नकल((a),(व्योम *)(b),(c))
#घोषणा z_स_नकल_toio(a,b,c)	स_नकल((व्योम *)(a),(b),(c))

अटल अंतरभूत व्योम __iomem *z_remap_nocache_ser(अचिन्हित दीर्घ physaddr,
					अचिन्हित दीर्घ size)
अणु
	वापस __ioremap(physaddr, size, IOMAP_NOCACHE_SER);
पूर्ण

अटल अंतरभूत व्योम __iomem *z_remap_nocache_nonser(अचिन्हित दीर्घ physaddr,
					   अचिन्हित दीर्घ size)
अणु
	वापस __ioremap(physaddr, size, IOMAP_NOCACHE_NONSER);
पूर्ण

अटल अंतरभूत व्योम __iomem *z_remap_ग_लिखोthrough(अचिन्हित दीर्घ physaddr,
					 अचिन्हित दीर्घ size)
अणु
	वापस __ioremap(physaddr, size, IOMAP_WRITETHROUGH);
पूर्ण
अटल अंतरभूत व्योम __iomem *z_remap_fullcache(अचिन्हित दीर्घ physaddr,
				      अचिन्हित दीर्घ size)
अणु
	वापस __ioremap(physaddr, size, IOMAP_FULL_CACHING);
पूर्ण

#घोषणा z_unmap iounmap
#घोषणा z_iounmap iounmap
#घोषणा z_ioremap z_remap_nocache_ser

#पूर्ण_अगर /* _ASM_M68K_ZORRO_H */
