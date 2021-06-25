<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/iomap.c
 *
 * Copyright (C) 2000  Niibe Yutaka
 * Copyright (C) 2005 - 2007 Paul Mundt
 */
#समावेश <linux/module.h>
#समावेश <linux/पन.स>

अचिन्हित पूर्णांक ioपढ़ो8(स्थिर व्योम __iomem *addr)
अणु
	वापस पढ़ोb(addr);
पूर्ण
EXPORT_SYMBOL(ioपढ़ो8);

अचिन्हित पूर्णांक ioपढ़ो16(स्थिर व्योम __iomem *addr)
अणु
	वापस पढ़ोw(addr);
पूर्ण
EXPORT_SYMBOL(ioपढ़ो16);

अचिन्हित पूर्णांक ioपढ़ो16be(स्थिर व्योम __iomem *addr)
अणु
	वापस be16_to_cpu(__raw_पढ़ोw(addr));
पूर्ण
EXPORT_SYMBOL(ioपढ़ो16be);

अचिन्हित पूर्णांक ioपढ़ो32(स्थिर व्योम __iomem *addr)
अणु
	वापस पढ़ोl(addr);
पूर्ण
EXPORT_SYMBOL(ioपढ़ो32);

अचिन्हित पूर्णांक ioपढ़ो32be(स्थिर व्योम __iomem *addr)
अणु
	वापस be32_to_cpu(__raw_पढ़ोl(addr));
पूर्ण
EXPORT_SYMBOL(ioपढ़ो32be);

व्योम ioग_लिखो8(u8 val, व्योम __iomem *addr)
अणु
	ग_लिखोb(val, addr);
पूर्ण
EXPORT_SYMBOL(ioग_लिखो8);

व्योम ioग_लिखो16(u16 val, व्योम __iomem *addr)
अणु
	ग_लिखोw(val, addr);
पूर्ण
EXPORT_SYMBOL(ioग_लिखो16);

व्योम ioग_लिखो16be(u16 val, व्योम __iomem *addr)
अणु
	__raw_ग_लिखोw(cpu_to_be16(val), addr);
पूर्ण
EXPORT_SYMBOL(ioग_लिखो16be);

व्योम ioग_लिखो32(u32 val, व्योम __iomem *addr)
अणु
	ग_लिखोl(val, addr);
पूर्ण
EXPORT_SYMBOL(ioग_लिखो32);

व्योम ioग_लिखो32be(u32 val, व्योम __iomem *addr)
अणु
	__raw_ग_लिखोl(cpu_to_be32(val), addr);
पूर्ण
EXPORT_SYMBOL(ioग_लिखो32be);

/*
 * These are the "repeat MMIO read/write" functions.
 * Note the "__raw" accesses, since we करोn't want to
 * convert to CPU byte order. We ग_लिखो in "IO byte
 * order" (we also करोn't have IO barriers).
 */
अटल अंतरभूत व्योम mmio_insb(स्थिर व्योम __iomem *addr, u8 *dst, पूर्णांक count)
अणु
	जबतक (--count >= 0) अणु
		u8 data = __raw_पढ़ोb(addr);
		*dst = data;
		dst++;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम mmio_insw(स्थिर व्योम __iomem *addr, u16 *dst, पूर्णांक count)
अणु
	जबतक (--count >= 0) अणु
		u16 data = __raw_पढ़ोw(addr);
		*dst = data;
		dst++;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम mmio_insl(स्थिर व्योम __iomem *addr, u32 *dst, पूर्णांक count)
अणु
	जबतक (--count >= 0) अणु
		u32 data = __raw_पढ़ोl(addr);
		*dst = data;
		dst++;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम mmio_outsb(व्योम __iomem *addr, स्थिर u8 *src, पूर्णांक count)
अणु
	जबतक (--count >= 0) अणु
		__raw_ग_लिखोb(*src, addr);
		src++;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम mmio_outsw(व्योम __iomem *addr, स्थिर u16 *src, पूर्णांक count)
अणु
	जबतक (--count >= 0) अणु
		__raw_ग_लिखोw(*src, addr);
		src++;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम mmio_outsl(व्योम __iomem *addr, स्थिर u32 *src, पूर्णांक count)
अणु
	जबतक (--count >= 0) अणु
		__raw_ग_लिखोl(*src, addr);
		src++;
	पूर्ण
पूर्ण

व्योम ioपढ़ो8_rep(स्थिर व्योम __iomem *addr, व्योम *dst, अचिन्हित दीर्घ count)
अणु
	mmio_insb(addr, dst, count);
पूर्ण
EXPORT_SYMBOL(ioपढ़ो8_rep);

व्योम ioपढ़ो16_rep(स्थिर व्योम __iomem *addr, व्योम *dst, अचिन्हित दीर्घ count)
अणु
	mmio_insw(addr, dst, count);
पूर्ण
EXPORT_SYMBOL(ioपढ़ो16_rep);

व्योम ioपढ़ो32_rep(स्थिर व्योम __iomem *addr, व्योम *dst, अचिन्हित दीर्घ count)
अणु
	mmio_insl(addr, dst, count);
पूर्ण
EXPORT_SYMBOL(ioपढ़ो32_rep);

व्योम ioग_लिखो8_rep(व्योम __iomem *addr, स्थिर व्योम *src, अचिन्हित दीर्घ count)
अणु
	mmio_outsb(addr, src, count);
पूर्ण
EXPORT_SYMBOL(ioग_लिखो8_rep);

व्योम ioग_लिखो16_rep(व्योम __iomem *addr, स्थिर व्योम *src, अचिन्हित दीर्घ count)
अणु
	mmio_outsw(addr, src, count);
पूर्ण
EXPORT_SYMBOL(ioग_लिखो16_rep);

व्योम ioग_लिखो32_rep(व्योम __iomem *addr, स्थिर व्योम *src, अचिन्हित दीर्घ count)
अणु
	mmio_outsl(addr, src, count);
पूर्ण
EXPORT_SYMBOL(ioग_लिखो32_rep);
