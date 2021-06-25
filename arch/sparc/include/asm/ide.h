<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* ide.h: SPARC PCI specअगरic IDE glue.
 *
 * Copyright (C) 1997  David S. Miller (davem@davemloft.net)
 * Copyright (C) 1998  Eddie C. Dost   (ecd@skynet.be)
 * Adaptation from sparc64 version to sparc by Pete Zaitcev.
 */

#अगर_अघोषित _SPARC_IDE_H
#घोषणा _SPARC_IDE_H

#अगर_घोषित __KERNEL__

#समावेश <यंत्र/पन.स>
#अगर_घोषित CONFIG_SPARC64
#समावेश <यंत्र/spitfire.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/page.h>
#अन्यथा
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/psr.h>
#पूर्ण_अगर

#घोषणा __ide_insl(data_reg, buffer, wcount) \
	__ide_insw(data_reg, buffer, (wcount)<<1)
#घोषणा __ide_outsl(data_reg, buffer, wcount) \
	__ide_outsw(data_reg, buffer, (wcount)<<1)

/* On sparc, I/O ports and MMIO रेजिस्टरs are accessed identically.  */
#घोषणा __ide_mm_insw	__ide_insw
#घोषणा __ide_mm_insl	__ide_insl
#घोषणा __ide_mm_outsw	__ide_outsw
#घोषणा __ide_mm_outsl	__ide_outsl

अटल अंतरभूत व्योम __ide_insw(व्योम __iomem *port, व्योम *dst, u32 count)
अणु
#अगर defined(CONFIG_SPARC64) && defined(DCACHE_ALIASING_POSSIBLE)
	अचिन्हित दीर्घ end = (अचिन्हित दीर्घ)dst + (count << 1);
#पूर्ण_अगर
	u16 *ps = dst;
	u32 *pi;

	अगर(((अचिन्हित दीर्घ)ps) & 0x2) अणु
		*ps++ = __raw_पढ़ोw(port);
		count--;
	पूर्ण
	pi = (u32 *)ps;
	जबतक(count >= 2) अणु
		u32 w;

		w  = __raw_पढ़ोw(port) << 16;
		w |= __raw_पढ़ोw(port);
		*pi++ = w;
		count -= 2;
	पूर्ण
	ps = (u16 *)pi;
	अगर(count)
		*ps++ = __raw_पढ़ोw(port);

#अगर defined(CONFIG_SPARC64) && defined(DCACHE_ALIASING_POSSIBLE)
	__flush_dcache_range((अचिन्हित दीर्घ)dst, end);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम __ide_outsw(व्योम __iomem *port, स्थिर व्योम *src, u32 count)
अणु
#अगर defined(CONFIG_SPARC64) && defined(DCACHE_ALIASING_POSSIBLE)
	अचिन्हित दीर्घ end = (अचिन्हित दीर्घ)src + (count << 1);
#पूर्ण_अगर
	स्थिर u16 *ps = src;
	स्थिर u32 *pi;

	अगर(((अचिन्हित दीर्घ)src) & 0x2) अणु
		__raw_ग_लिखोw(*ps++, port);
		count--;
	पूर्ण
	pi = (स्थिर u32 *)ps;
	जबतक(count >= 2) अणु
		u32 w;

		w = *pi++;
		__raw_ग_लिखोw((w >> 16), port);
		__raw_ग_लिखोw(w, port);
		count -= 2;
	पूर्ण
	ps = (स्थिर u16 *)pi;
	अगर(count)
		__raw_ग_लिखोw(*ps, port);

#अगर defined(CONFIG_SPARC64) && defined(DCACHE_ALIASING_POSSIBLE)
	__flush_dcache_range((अचिन्हित दीर्घ)src, end);
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* _SPARC_IDE_H */
