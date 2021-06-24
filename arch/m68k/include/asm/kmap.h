<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _KMAP_H
#घोषणा _KMAP_H

#अगर_घोषित CONFIG_MMU

#घोषणा ARCH_HAS_IOREMAP_WT

/* Values क्रम nocacheflag and cmode */
#घोषणा IOMAP_FULL_CACHING		0
#घोषणा IOMAP_NOCACHE_SER		1
#घोषणा IOMAP_NOCACHE_NONSER		2
#घोषणा IOMAP_WRITETHROUGH		3

/*
 * These functions exported by arch/m68k/mm/kmap.c.
 * Only needed on MMU enabled प्रणालीs.
 */
बाह्य व्योम __iomem *__ioremap(अचिन्हित दीर्घ physaddr, अचिन्हित दीर्घ size,
			       पूर्णांक cacheflag);
#घोषणा iounmap iounmap
बाह्य व्योम iounmap(व्योम __iomem *addr);

#घोषणा ioremap ioremap
अटल अंतरभूत व्योम __iomem *ioremap(अचिन्हित दीर्घ physaddr, अचिन्हित दीर्घ size)
अणु
	वापस __ioremap(physaddr, size, IOMAP_NOCACHE_SER);
पूर्ण

#घोषणा ioremap_uc ioremap
#घोषणा ioremap_wt ioremap_wt
अटल अंतरभूत व्योम __iomem *ioremap_wt(अचिन्हित दीर्घ physaddr,
				       अचिन्हित दीर्घ size)
अणु
	वापस __ioremap(physaddr, size, IOMAP_WRITETHROUGH);
पूर्ण

#घोषणा स_रखो_io स_रखो_io
अटल अंतरभूत व्योम स_रखो_io(अस्थिर व्योम __iomem *addr, अचिन्हित अक्षर val,
			     पूर्णांक count)
अणु
	__builtin_स_रखो((व्योम __क्रमce *) addr, val, count);
पूर्ण

#घोषणा स_नकल_fromio स_नकल_fromio
अटल अंतरभूत व्योम स_नकल_fromio(व्योम *dst, स्थिर अस्थिर व्योम __iomem *src,
				 पूर्णांक count)
अणु
	__builtin_स_नकल(dst, (व्योम __क्रमce *) src, count);
पूर्ण

#घोषणा स_नकल_toio स_नकल_toio
अटल अंतरभूत व्योम स_नकल_toio(अस्थिर व्योम __iomem *dst, स्थिर व्योम *src,
			       पूर्णांक count)
अणु
	__builtin_स_नकल((व्योम __क्रमce *) dst, src, count);
पूर्ण

#पूर्ण_अगर /* CONFIG_MMU */

#घोषणा ioport_map ioport_map
अटल अंतरभूत व्योम __iomem *ioport_map(अचिन्हित दीर्घ port, अचिन्हित पूर्णांक nr)
अणु
	वापस (व्योम __iomem *) port;
पूर्ण

#घोषणा ioport_unmap ioport_unmap
अटल अंतरभूत व्योम ioport_unmap(व्योम __iomem *p)
अणु
पूर्ण

#पूर्ण_अगर /* _KMAP_H */
