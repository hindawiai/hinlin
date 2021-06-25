<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * iomap.c - Implement iomap पूर्णांकerface क्रम PA-RISC
 * Copyright (c) 2004 Matthew Wilcox
 */

#समावेश <linux/ioport.h>
#समावेश <linux/pci.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/पन.स>

/*
 * The iomap space on 32-bit PA-RISC is पूर्णांकended to look like this:
 * 00000000-7fffffff भव mapped IO
 * 80000000-8fffffff ISA/EISA port space that can't be भवly mapped
 * 90000000-9fffffff Dino port space
 * a0000000-afffffff Astro port space
 * b0000000-bfffffff PAT port space
 * c0000000-cfffffff non-swapped memory IO
 * f0000000-ffffffff legacy IO memory poपूर्णांकers
 *
 * For the moment, here's what it looks like:
 * 80000000-8fffffff All ISA/EISA port space
 * f0000000-ffffffff legacy IO memory poपूर्णांकers
 *
 * On 64-bit, everything is extended, so:
 * 8000000000000000-8fffffffffffffff All ISA/EISA port space
 * f000000000000000-ffffffffffffffff legacy IO memory poपूर्णांकers
 */

/*
 * Technically, this should be 'अगर (VMALLOC_START < addr < VMALLOC_END),
 * but that's slow and we know it'll be within the first 2GB.
 */
#अगर_घोषित CONFIG_64BIT
#घोषणा INसूचीECT_ADDR(addr)	(((अचिन्हित दीर्घ)(addr) & 1UL<<63) != 0)
#घोषणा ADDR_TO_REGION(addr)    (((अचिन्हित दीर्घ)addr >> 60) & 7)
#घोषणा IOPORT_MAP_BASE		(8UL << 60)
#अन्यथा
#घोषणा INसूचीECT_ADDR(addr)     (((अचिन्हित दीर्घ)(addr) & 1UL<<31) != 0)
#घोषणा ADDR_TO_REGION(addr)    (((अचिन्हित दीर्घ)addr >> 28) & 7)
#घोषणा IOPORT_MAP_BASE		(8UL << 28)
#पूर्ण_अगर

काष्ठा iomap_ops अणु
	अचिन्हित पूर्णांक (*पढ़ो8)(स्थिर व्योम __iomem *);
	अचिन्हित पूर्णांक (*पढ़ो16)(स्थिर व्योम __iomem *);
	अचिन्हित पूर्णांक (*पढ़ो16be)(स्थिर व्योम __iomem *);
	अचिन्हित पूर्णांक (*पढ़ो32)(स्थिर व्योम __iomem *);
	अचिन्हित पूर्णांक (*पढ़ो32be)(स्थिर व्योम __iomem *);
	u64 (*पढ़ो64)(स्थिर व्योम __iomem *);
	u64 (*पढ़ो64be)(स्थिर व्योम __iomem *);
	व्योम (*ग_लिखो8)(u8, व्योम __iomem *);
	व्योम (*ग_लिखो16)(u16, व्योम __iomem *);
	व्योम (*ग_लिखो16be)(u16, व्योम __iomem *);
	व्योम (*ग_लिखो32)(u32, व्योम __iomem *);
	व्योम (*ग_लिखो32be)(u32, व्योम __iomem *);
	व्योम (*ग_लिखो64)(u64, व्योम __iomem *);
	व्योम (*ग_लिखो64be)(u64, व्योम __iomem *);
	व्योम (*पढ़ो8r)(स्थिर व्योम __iomem *, व्योम *, अचिन्हित दीर्घ);
	व्योम (*पढ़ो16r)(स्थिर व्योम __iomem *, व्योम *, अचिन्हित दीर्घ);
	व्योम (*पढ़ो32r)(स्थिर व्योम __iomem *, व्योम *, अचिन्हित दीर्घ);
	व्योम (*ग_लिखो8r)(व्योम __iomem *, स्थिर व्योम *, अचिन्हित दीर्घ);
	व्योम (*ग_लिखो16r)(व्योम __iomem *, स्थिर व्योम *, अचिन्हित दीर्घ);
	व्योम (*ग_लिखो32r)(व्योम __iomem *, स्थिर व्योम *, अचिन्हित दीर्घ);
पूर्ण;

/* Generic ioport ops.  To be replaced later by specअगरic dino/elroy/wax code */

#घोषणा ADDR2PORT(addr) ((अचिन्हित दीर्घ __क्रमce)(addr) & 0xffffff)

अटल अचिन्हित पूर्णांक ioport_पढ़ो8(स्थिर व्योम __iomem *addr)
अणु
	वापस inb(ADDR2PORT(addr));
पूर्ण

अटल अचिन्हित पूर्णांक ioport_पढ़ो16(स्थिर व्योम __iomem *addr)
अणु
	वापस inw(ADDR2PORT(addr));
पूर्ण

अटल अचिन्हित पूर्णांक ioport_पढ़ो32(स्थिर व्योम __iomem *addr)
अणु
	वापस inl(ADDR2PORT(addr));
पूर्ण

अटल व्योम ioport_ग_लिखो8(u8 datum, व्योम __iomem *addr)
अणु
	outb(datum, ADDR2PORT(addr));
पूर्ण

अटल व्योम ioport_ग_लिखो16(u16 datum, व्योम __iomem *addr)
अणु
	outw(datum, ADDR2PORT(addr));
पूर्ण

अटल व्योम ioport_ग_लिखो32(u32 datum, व्योम __iomem *addr)
अणु
	outl(datum, ADDR2PORT(addr));
पूर्ण

अटल व्योम ioport_पढ़ो8r(स्थिर व्योम __iomem *addr, व्योम *dst, अचिन्हित दीर्घ count)
अणु
	insb(ADDR2PORT(addr), dst, count);
पूर्ण

अटल व्योम ioport_पढ़ो16r(स्थिर व्योम __iomem *addr, व्योम *dst, अचिन्हित दीर्घ count)
अणु
	insw(ADDR2PORT(addr), dst, count);
पूर्ण

अटल व्योम ioport_पढ़ो32r(स्थिर व्योम __iomem *addr, व्योम *dst, अचिन्हित दीर्घ count)
अणु
	insl(ADDR2PORT(addr), dst, count);
पूर्ण

अटल व्योम ioport_ग_लिखो8r(व्योम __iomem *addr, स्थिर व्योम *s, अचिन्हित दीर्घ n)
अणु
	outsb(ADDR2PORT(addr), s, n);
पूर्ण

अटल व्योम ioport_ग_लिखो16r(व्योम __iomem *addr, स्थिर व्योम *s, अचिन्हित दीर्घ n)
अणु
	outsw(ADDR2PORT(addr), s, n);
पूर्ण

अटल व्योम ioport_ग_लिखो32r(व्योम __iomem *addr, स्थिर व्योम *s, अचिन्हित दीर्घ n)
अणु
	outsl(ADDR2PORT(addr), s, n);
पूर्ण

अटल स्थिर काष्ठा iomap_ops ioport_ops = अणु
	.पढ़ो8 = ioport_पढ़ो8,
	.पढ़ो16 = ioport_पढ़ो16,
	.पढ़ो16be = ioport_पढ़ो16,
	.पढ़ो32 = ioport_पढ़ो32,
	.पढ़ो32be = ioport_पढ़ो32,
	.ग_लिखो8 = ioport_ग_लिखो8,
	.ग_लिखो16 = ioport_ग_लिखो16,
	.ग_लिखो16be = ioport_ग_लिखो16,
	.ग_लिखो32 = ioport_ग_लिखो32,
	.ग_लिखो32be = ioport_ग_लिखो32,
	.पढ़ो8r = ioport_पढ़ो8r,
	.पढ़ो16r = ioport_पढ़ो16r,
	.पढ़ो32r = ioport_पढ़ो32r,
	.ग_लिखो8r = ioport_ग_लिखो8r,
	.ग_लिखो16r = ioport_ग_लिखो16r,
	.ग_लिखो32r = ioport_ग_लिखो32r,
पूर्ण;

/* Legacy I/O memory ops */

अटल अचिन्हित पूर्णांक iomem_पढ़ो8(स्थिर व्योम __iomem *addr)
अणु
	वापस पढ़ोb(addr);
पूर्ण

अटल अचिन्हित पूर्णांक iomem_पढ़ो16(स्थिर व्योम __iomem *addr)
अणु
	वापस पढ़ोw(addr);
पूर्ण

अटल अचिन्हित पूर्णांक iomem_पढ़ो16be(स्थिर व्योम __iomem *addr)
अणु
	वापस __raw_पढ़ोw(addr);
पूर्ण

अटल अचिन्हित पूर्णांक iomem_पढ़ो32(स्थिर व्योम __iomem *addr)
अणु
	वापस पढ़ोl(addr);
पूर्ण

अटल अचिन्हित पूर्णांक iomem_पढ़ो32be(स्थिर व्योम __iomem *addr)
अणु
	वापस __raw_पढ़ोl(addr);
पूर्ण

अटल u64 iomem_पढ़ो64(स्थिर व्योम __iomem *addr)
अणु
	वापस पढ़ोq(addr);
पूर्ण

अटल u64 iomem_पढ़ो64be(स्थिर व्योम __iomem *addr)
अणु
	वापस __raw_पढ़ोq(addr);
पूर्ण

अटल व्योम iomem_ग_लिखो8(u8 datum, व्योम __iomem *addr)
अणु
	ग_लिखोb(datum, addr);
पूर्ण

अटल व्योम iomem_ग_लिखो16(u16 datum, व्योम __iomem *addr)
अणु
	ग_लिखोw(datum, addr);
पूर्ण

अटल व्योम iomem_ग_लिखो16be(u16 datum, व्योम __iomem *addr)
अणु
	__raw_ग_लिखोw(datum, addr);
पूर्ण

अटल व्योम iomem_ग_लिखो32(u32 datum, व्योम __iomem *addr)
अणु
	ग_लिखोl(datum, addr);
पूर्ण

अटल व्योम iomem_ग_लिखो32be(u32 datum, व्योम __iomem *addr)
अणु
	__raw_ग_लिखोl(datum, addr);
पूर्ण

अटल व्योम iomem_ग_लिखो64(u64 datum, व्योम __iomem *addr)
अणु
	ग_लिखोl(datum, addr);
पूर्ण

अटल व्योम iomem_ग_लिखो64be(u64 datum, व्योम __iomem *addr)
अणु
	__raw_ग_लिखोl(datum, addr);
पूर्ण

अटल व्योम iomem_पढ़ो8r(स्थिर व्योम __iomem *addr, व्योम *dst, अचिन्हित दीर्घ count)
अणु
	जबतक (count--) अणु
		*(u8 *)dst = __raw_पढ़ोb(addr);
		dst++;
	पूर्ण
पूर्ण

अटल व्योम iomem_पढ़ो16r(स्थिर व्योम __iomem *addr, व्योम *dst, अचिन्हित दीर्घ count)
अणु
	जबतक (count--) अणु
		*(u16 *)dst = __raw_पढ़ोw(addr);
		dst += 2;
	पूर्ण
पूर्ण

अटल व्योम iomem_पढ़ो32r(स्थिर व्योम __iomem *addr, व्योम *dst, अचिन्हित दीर्घ count)
अणु
	जबतक (count--) अणु
		*(u32 *)dst = __raw_पढ़ोl(addr);
		dst += 4;
	पूर्ण
पूर्ण

अटल व्योम iomem_ग_लिखो8r(व्योम __iomem *addr, स्थिर व्योम *s, अचिन्हित दीर्घ n)
अणु
	जबतक (n--) अणु
		__raw_ग_लिखोb(*(u8 *)s, addr);
		s++;
	पूर्ण
पूर्ण

अटल व्योम iomem_ग_लिखो16r(व्योम __iomem *addr, स्थिर व्योम *s, अचिन्हित दीर्घ n)
अणु
	जबतक (n--) अणु
		__raw_ग_लिखोw(*(u16 *)s, addr);
		s += 2;
	पूर्ण
पूर्ण

अटल व्योम iomem_ग_लिखो32r(व्योम __iomem *addr, स्थिर व्योम *s, अचिन्हित दीर्घ n)
अणु
	जबतक (n--) अणु
		__raw_ग_लिखोl(*(u32 *)s, addr);
		s += 4;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iomap_ops iomem_ops = अणु
	.पढ़ो8 = iomem_पढ़ो8,
	.पढ़ो16 = iomem_पढ़ो16,
	.पढ़ो16be = iomem_पढ़ो16be,
	.पढ़ो32 = iomem_पढ़ो32,
	.पढ़ो32be = iomem_पढ़ो32be,
	.पढ़ो64 = iomem_पढ़ो64,
	.पढ़ो64be = iomem_पढ़ो64be,
	.ग_लिखो8 = iomem_ग_लिखो8,
	.ग_लिखो16 = iomem_ग_लिखो16,
	.ग_लिखो16be = iomem_ग_लिखो16be,
	.ग_लिखो32 = iomem_ग_लिखो32,
	.ग_लिखो32be = iomem_ग_लिखो32be,
	.ग_लिखो64 = iomem_ग_लिखो64,
	.ग_लिखो64be = iomem_ग_लिखो64be,
	.पढ़ो8r = iomem_पढ़ो8r,
	.पढ़ो16r = iomem_पढ़ो16r,
	.पढ़ो32r = iomem_पढ़ो32r,
	.ग_लिखो8r = iomem_ग_लिखो8r,
	.ग_लिखो16r = iomem_ग_लिखो16r,
	.ग_लिखो32r = iomem_ग_लिखो32r,
पूर्ण;

अटल स्थिर काष्ठा iomap_ops *iomap_ops[8] = अणु
	[0] = &ioport_ops,
	[7] = &iomem_ops
पूर्ण;


अचिन्हित पूर्णांक ioपढ़ो8(स्थिर व्योम __iomem *addr)
अणु
	अगर (unlikely(INसूचीECT_ADDR(addr)))
		वापस iomap_ops[ADDR_TO_REGION(addr)]->पढ़ो8(addr);
	वापस *((u8 *)addr);
पूर्ण

अचिन्हित पूर्णांक ioपढ़ो16(स्थिर व्योम __iomem *addr)
अणु
	अगर (unlikely(INसूचीECT_ADDR(addr)))
		वापस iomap_ops[ADDR_TO_REGION(addr)]->पढ़ो16(addr);
	वापस le16_to_cpup((u16 *)addr);
पूर्ण

अचिन्हित पूर्णांक ioपढ़ो16be(स्थिर व्योम __iomem *addr)
अणु
	अगर (unlikely(INसूचीECT_ADDR(addr)))
		वापस iomap_ops[ADDR_TO_REGION(addr)]->पढ़ो16be(addr);
	वापस *((u16 *)addr);
पूर्ण

अचिन्हित पूर्णांक ioपढ़ो32(स्थिर व्योम __iomem *addr)
अणु
	अगर (unlikely(INसूचीECT_ADDR(addr)))
		वापस iomap_ops[ADDR_TO_REGION(addr)]->पढ़ो32(addr);
	वापस le32_to_cpup((u32 *)addr);
पूर्ण

अचिन्हित पूर्णांक ioपढ़ो32be(स्थिर व्योम __iomem *addr)
अणु
	अगर (unlikely(INसूचीECT_ADDR(addr)))
		वापस iomap_ops[ADDR_TO_REGION(addr)]->पढ़ो32be(addr);
	वापस *((u32 *)addr);
पूर्ण

u64 ioपढ़ो64(स्थिर व्योम __iomem *addr)
अणु
	अगर (unlikely(INसूचीECT_ADDR(addr)))
		वापस iomap_ops[ADDR_TO_REGION(addr)]->पढ़ो64(addr);
	वापस le64_to_cpup((u64 *)addr);
पूर्ण

u64 ioपढ़ो64be(स्थिर व्योम __iomem *addr)
अणु
	अगर (unlikely(INसूचीECT_ADDR(addr)))
		वापस iomap_ops[ADDR_TO_REGION(addr)]->पढ़ो64be(addr);
	वापस *((u64 *)addr);
पूर्ण

u64 ioपढ़ो64_hi_lo(स्थिर व्योम __iomem *addr)
अणु
	u32 low, high;

	high = ioपढ़ो32(addr + माप(u32));
	low = ioपढ़ो32(addr);

	वापस low + ((u64)high << 32);
पूर्ण

व्योम ioग_लिखो8(u8 datum, व्योम __iomem *addr)
अणु
	अगर (unlikely(INसूचीECT_ADDR(addr))) अणु
		iomap_ops[ADDR_TO_REGION(addr)]->ग_लिखो8(datum, addr);
	पूर्ण अन्यथा अणु
		*((u8 *)addr) = datum;
	पूर्ण
पूर्ण

व्योम ioग_लिखो16(u16 datum, व्योम __iomem *addr)
अणु
	अगर (unlikely(INसूचीECT_ADDR(addr))) अणु
		iomap_ops[ADDR_TO_REGION(addr)]->ग_लिखो16(datum, addr);
	पूर्ण अन्यथा अणु
		*((u16 *)addr) = cpu_to_le16(datum);
	पूर्ण
पूर्ण

व्योम ioग_लिखो16be(u16 datum, व्योम __iomem *addr)
अणु
	अगर (unlikely(INसूचीECT_ADDR(addr))) अणु
		iomap_ops[ADDR_TO_REGION(addr)]->ग_लिखो16be(datum, addr);
	पूर्ण अन्यथा अणु
		*((u16 *)addr) = datum;
	पूर्ण
पूर्ण

व्योम ioग_लिखो32(u32 datum, व्योम __iomem *addr)
अणु
	अगर (unlikely(INसूचीECT_ADDR(addr))) अणु
		iomap_ops[ADDR_TO_REGION(addr)]->ग_लिखो32(datum, addr);
	पूर्ण अन्यथा अणु
		*((u32 *)addr) = cpu_to_le32(datum);
	पूर्ण
पूर्ण

व्योम ioग_लिखो32be(u32 datum, व्योम __iomem *addr)
अणु
	अगर (unlikely(INसूचीECT_ADDR(addr))) अणु
		iomap_ops[ADDR_TO_REGION(addr)]->ग_लिखो32be(datum, addr);
	पूर्ण अन्यथा अणु
		*((u32 *)addr) = datum;
	पूर्ण
पूर्ण

व्योम ioग_लिखो64(u64 datum, व्योम __iomem *addr)
अणु
	अगर (unlikely(INसूचीECT_ADDR(addr))) अणु
		iomap_ops[ADDR_TO_REGION(addr)]->ग_लिखो64(datum, addr);
	पूर्ण अन्यथा अणु
		*((u64 *)addr) = cpu_to_le64(datum);
	पूर्ण
पूर्ण

व्योम ioग_लिखो64be(u64 datum, व्योम __iomem *addr)
अणु
	अगर (unlikely(INसूचीECT_ADDR(addr))) अणु
		iomap_ops[ADDR_TO_REGION(addr)]->ग_लिखो64be(datum, addr);
	पूर्ण अन्यथा अणु
		*((u64 *)addr) = datum;
	पूर्ण
पूर्ण

व्योम ioग_लिखो64_hi_lo(u64 val, व्योम __iomem *addr)
अणु
	ioग_लिखो32(val >> 32, addr + माप(u32));
	ioग_लिखो32(val, addr);
पूर्ण

/* Repeating पूर्णांकerfaces */

व्योम ioपढ़ो8_rep(स्थिर व्योम __iomem *addr, व्योम *dst, अचिन्हित दीर्घ count)
अणु
	अगर (unlikely(INसूचीECT_ADDR(addr))) अणु
		iomap_ops[ADDR_TO_REGION(addr)]->पढ़ो8r(addr, dst, count);
	पूर्ण अन्यथा अणु
		जबतक (count--) अणु
			*(u8 *)dst = *(u8 *)addr;
			dst++;
		पूर्ण
	पूर्ण
पूर्ण

व्योम ioपढ़ो16_rep(स्थिर व्योम __iomem *addr, व्योम *dst, अचिन्हित दीर्घ count)
अणु
	अगर (unlikely(INसूचीECT_ADDR(addr))) अणु
		iomap_ops[ADDR_TO_REGION(addr)]->पढ़ो16r(addr, dst, count);
	पूर्ण अन्यथा अणु
		जबतक (count--) अणु
			*(u16 *)dst = *(u16 *)addr;
			dst += 2;
		पूर्ण
	पूर्ण
पूर्ण

व्योम ioपढ़ो32_rep(स्थिर व्योम __iomem *addr, व्योम *dst, अचिन्हित दीर्घ count)
अणु
	अगर (unlikely(INसूचीECT_ADDR(addr))) अणु
		iomap_ops[ADDR_TO_REGION(addr)]->पढ़ो32r(addr, dst, count);
	पूर्ण अन्यथा अणु
		जबतक (count--) अणु
			*(u32 *)dst = *(u32 *)addr;
			dst += 4;
		पूर्ण
	पूर्ण
पूर्ण

व्योम ioग_लिखो8_rep(व्योम __iomem *addr, स्थिर व्योम *src, अचिन्हित दीर्घ count)
अणु
	अगर (unlikely(INसूचीECT_ADDR(addr))) अणु
		iomap_ops[ADDR_TO_REGION(addr)]->ग_लिखो8r(addr, src, count);
	पूर्ण अन्यथा अणु
		जबतक (count--) अणु
			*(u8 *)addr = *(u8 *)src;
			src++;
		पूर्ण
	पूर्ण
पूर्ण

व्योम ioग_लिखो16_rep(व्योम __iomem *addr, स्थिर व्योम *src, अचिन्हित दीर्घ count)
अणु
	अगर (unlikely(INसूचीECT_ADDR(addr))) अणु
		iomap_ops[ADDR_TO_REGION(addr)]->ग_लिखो16r(addr, src, count);
	पूर्ण अन्यथा अणु
		जबतक (count--) अणु
			*(u16 *)addr = *(u16 *)src;
			src += 2;
		पूर्ण
	पूर्ण
पूर्ण

व्योम ioग_लिखो32_rep(व्योम __iomem *addr, स्थिर व्योम *src, अचिन्हित दीर्घ count)
अणु
	अगर (unlikely(INसूचीECT_ADDR(addr))) अणु
		iomap_ops[ADDR_TO_REGION(addr)]->ग_लिखो32r(addr, src, count);
	पूर्ण अन्यथा अणु
		जबतक (count--) अणु
			*(u32 *)addr = *(u32 *)src;
			src += 4;
		पूर्ण
	पूर्ण
पूर्ण

/* Mapping पूर्णांकerfaces */

व्योम __iomem *ioport_map(अचिन्हित दीर्घ port, अचिन्हित पूर्णांक nr)
अणु
	वापस (व्योम __iomem *)(IOPORT_MAP_BASE | port);
पूर्ण

व्योम ioport_unmap(व्योम __iomem *addr)
अणु
	अगर (!INसूचीECT_ADDR(addr)) अणु
		iounmap(addr);
	पूर्ण
पूर्ण

व्योम pci_iounmap(काष्ठा pci_dev *dev, व्योम __iomem * addr)
अणु
	अगर (!INसूचीECT_ADDR(addr)) अणु
		iounmap(addr);
	पूर्ण
पूर्ण

EXPORT_SYMBOL(ioपढ़ो8);
EXPORT_SYMBOL(ioपढ़ो16);
EXPORT_SYMBOL(ioपढ़ो16be);
EXPORT_SYMBOL(ioपढ़ो32);
EXPORT_SYMBOL(ioपढ़ो32be);
EXPORT_SYMBOL(ioपढ़ो64);
EXPORT_SYMBOL(ioपढ़ो64be);
EXPORT_SYMBOL(ioपढ़ो64_hi_lo);
EXPORT_SYMBOL(ioग_लिखो8);
EXPORT_SYMBOL(ioग_लिखो16);
EXPORT_SYMBOL(ioग_लिखो16be);
EXPORT_SYMBOL(ioग_लिखो32);
EXPORT_SYMBOL(ioग_लिखो32be);
EXPORT_SYMBOL(ioग_लिखो64);
EXPORT_SYMBOL(ioग_लिखो64be);
EXPORT_SYMBOL(ioग_लिखो64_hi_lo);
EXPORT_SYMBOL(ioपढ़ो8_rep);
EXPORT_SYMBOL(ioपढ़ो16_rep);
EXPORT_SYMBOL(ioपढ़ो32_rep);
EXPORT_SYMBOL(ioग_लिखो8_rep);
EXPORT_SYMBOL(ioग_लिखो16_rep);
EXPORT_SYMBOL(ioग_लिखो32_rep);
EXPORT_SYMBOL(ioport_map);
EXPORT_SYMBOL(ioport_unmap);
EXPORT_SYMBOL(pci_iounmap);
