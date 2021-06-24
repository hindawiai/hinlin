<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  linux/include/यंत्र-parisc/ide.h
 *
 *  Copyright (C) 1994-1996  Linus Torvalds & authors
 */

/*
 *  This file contains the PARISC architecture specअगरic IDE code.
 */

#अगर_अघोषित __ASM_PARISC_IDE_H
#घोषणा __ASM_PARISC_IDE_H

#अगर_घोषित __KERNEL__

/* Generic I/O and MEMIO string operations.  */

#घोषणा __ide_insw	insw
#घोषणा __ide_insl	insl
#घोषणा __ide_outsw	outsw
#घोषणा __ide_outsl	outsl

अटल __अंतरभूत__ व्योम __ide_mm_insw(व्योम __iomem *port, व्योम *addr, u32 count)
अणु
	जबतक (count--) अणु
		*(u16 *)addr = __raw_पढ़ोw(port);
		addr += 2;
	पूर्ण
पूर्ण

अटल __अंतरभूत__ व्योम __ide_mm_insl(व्योम __iomem *port, व्योम *addr, u32 count)
अणु
	जबतक (count--) अणु
		*(u32 *)addr = __raw_पढ़ोl(port);
		addr += 4;
	पूर्ण
पूर्ण

अटल __अंतरभूत__ व्योम __ide_mm_outsw(व्योम __iomem *port, व्योम *addr, u32 count)
अणु
	जबतक (count--) अणु
		__raw_ग_लिखोw(*(u16 *)addr, port);
		addr += 2;
	पूर्ण
पूर्ण

अटल __अंतरभूत__ व्योम __ide_mm_outsl(व्योम __iomem *port, व्योम *addr, u32 count)
अणु
	जबतक (count--) अणु
		__raw_ग_लिखोl(*(u32 *)addr, port);
		addr += 4;
	पूर्ण
पूर्ण

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* __ASM_PARISC_IDE_H */
