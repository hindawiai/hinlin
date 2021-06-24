<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Alpha IO and memory functions.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/module.h>
#समावेश <यंत्र/पन.स>

/* Out-of-line versions of the i/o routines that redirect पूर्णांकo the 
   platक्रमm-specअगरic version.  Note that "platform-specific" may mean
   "generic", which bumps through the machine vector.  */

अचिन्हित पूर्णांक
ioपढ़ो8(स्थिर व्योम __iomem *addr)
अणु
	अचिन्हित पूर्णांक ret;
	mb();
	ret = IO_CONCAT(__IO_PREFIX,ioपढ़ो8)(addr);
	mb();
	वापस ret;
पूर्ण

अचिन्हित पूर्णांक ioपढ़ो16(स्थिर व्योम __iomem *addr)
अणु
	अचिन्हित पूर्णांक ret;
	mb();
	ret = IO_CONCAT(__IO_PREFIX,ioपढ़ो16)(addr);
	mb();
	वापस ret;
पूर्ण

अचिन्हित पूर्णांक ioपढ़ो32(स्थिर व्योम __iomem *addr)
अणु
	अचिन्हित पूर्णांक ret;
	mb();
	ret = IO_CONCAT(__IO_PREFIX,ioपढ़ो32)(addr);
	mb();
	वापस ret;
पूर्ण

व्योम ioग_लिखो8(u8 b, व्योम __iomem *addr)
अणु
	mb();
	IO_CONCAT(__IO_PREFIX,ioग_लिखो8)(b, addr);
पूर्ण

व्योम ioग_लिखो16(u16 b, व्योम __iomem *addr)
अणु
	mb();
	IO_CONCAT(__IO_PREFIX,ioग_लिखो16)(b, addr);
पूर्ण

व्योम ioग_लिखो32(u32 b, व्योम __iomem *addr)
अणु
	mb();
	IO_CONCAT(__IO_PREFIX,ioग_लिखो32)(b, addr);
पूर्ण

EXPORT_SYMBOL(ioपढ़ो8);
EXPORT_SYMBOL(ioपढ़ो16);
EXPORT_SYMBOL(ioपढ़ो32);
EXPORT_SYMBOL(ioग_लिखो8);
EXPORT_SYMBOL(ioग_लिखो16);
EXPORT_SYMBOL(ioग_लिखो32);

u8 inb(अचिन्हित दीर्घ port)
अणु
	वापस ioपढ़ो8(ioport_map(port, 1));
पूर्ण

u16 inw(अचिन्हित दीर्घ port)
अणु
	वापस ioपढ़ो16(ioport_map(port, 2));
पूर्ण

u32 inl(अचिन्हित दीर्घ port)
अणु
	वापस ioपढ़ो32(ioport_map(port, 4));
पूर्ण

व्योम outb(u8 b, अचिन्हित दीर्घ port)
अणु
	ioग_लिखो8(b, ioport_map(port, 1));
पूर्ण

व्योम outw(u16 b, अचिन्हित दीर्घ port)
अणु
	ioग_लिखो16(b, ioport_map(port, 2));
पूर्ण

व्योम outl(u32 b, अचिन्हित दीर्घ port)
अणु
	ioग_लिखो32(b, ioport_map(port, 4));
पूर्ण

EXPORT_SYMBOL(inb);
EXPORT_SYMBOL(inw);
EXPORT_SYMBOL(inl);
EXPORT_SYMBOL(outb);
EXPORT_SYMBOL(outw);
EXPORT_SYMBOL(outl);

u8 __raw_पढ़ोb(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस IO_CONCAT(__IO_PREFIX,पढ़ोb)(addr);
पूर्ण

u16 __raw_पढ़ोw(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस IO_CONCAT(__IO_PREFIX,पढ़ोw)(addr);
पूर्ण

u32 __raw_पढ़ोl(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस IO_CONCAT(__IO_PREFIX,पढ़ोl)(addr);
पूर्ण

u64 __raw_पढ़ोq(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस IO_CONCAT(__IO_PREFIX,पढ़ोq)(addr);
पूर्ण

व्योम __raw_ग_लिखोb(u8 b, अस्थिर व्योम __iomem *addr)
अणु
	IO_CONCAT(__IO_PREFIX,ग_लिखोb)(b, addr);
पूर्ण

व्योम __raw_ग_लिखोw(u16 b, अस्थिर व्योम __iomem *addr)
अणु
	IO_CONCAT(__IO_PREFIX,ग_लिखोw)(b, addr);
पूर्ण

व्योम __raw_ग_लिखोl(u32 b, अस्थिर व्योम __iomem *addr)
अणु
	IO_CONCAT(__IO_PREFIX,ग_लिखोl)(b, addr);
पूर्ण

व्योम __raw_ग_लिखोq(u64 b, अस्थिर व्योम __iomem *addr)
अणु
	IO_CONCAT(__IO_PREFIX,ग_लिखोq)(b, addr);
पूर्ण

EXPORT_SYMBOL(__raw_पढ़ोb); 
EXPORT_SYMBOL(__raw_पढ़ोw); 
EXPORT_SYMBOL(__raw_पढ़ोl); 
EXPORT_SYMBOL(__raw_पढ़ोq); 
EXPORT_SYMBOL(__raw_ग_लिखोb); 
EXPORT_SYMBOL(__raw_ग_लिखोw); 
EXPORT_SYMBOL(__raw_ग_लिखोl); 
EXPORT_SYMBOL(__raw_ग_लिखोq); 

u8 पढ़ोb(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u8 ret;
	mb();
	ret = __raw_पढ़ोb(addr);
	mb();
	वापस ret;
पूर्ण

u16 पढ़ोw(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u16 ret;
	mb();
	ret = __raw_पढ़ोw(addr);
	mb();
	वापस ret;
पूर्ण

u32 पढ़ोl(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u32 ret;
	mb();
	ret = __raw_पढ़ोl(addr);
	mb();
	वापस ret;
पूर्ण

u64 पढ़ोq(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u64 ret;
	mb();
	ret = __raw_पढ़ोq(addr);
	mb();
	वापस ret;
पूर्ण

व्योम ग_लिखोb(u8 b, अस्थिर व्योम __iomem *addr)
अणु
	mb();
	__raw_ग_लिखोb(b, addr);
पूर्ण

व्योम ग_लिखोw(u16 b, अस्थिर व्योम __iomem *addr)
अणु
	mb();
	__raw_ग_लिखोw(b, addr);
पूर्ण

व्योम ग_लिखोl(u32 b, अस्थिर व्योम __iomem *addr)
अणु
	mb();
	__raw_ग_लिखोl(b, addr);
पूर्ण

व्योम ग_लिखोq(u64 b, अस्थिर व्योम __iomem *addr)
अणु
	mb();
	__raw_ग_लिखोq(b, addr);
पूर्ण

EXPORT_SYMBOL(पढ़ोb);
EXPORT_SYMBOL(पढ़ोw);
EXPORT_SYMBOL(पढ़ोl);
EXPORT_SYMBOL(पढ़ोq);
EXPORT_SYMBOL(ग_लिखोb);
EXPORT_SYMBOL(ग_लिखोw);
EXPORT_SYMBOL(ग_लिखोl);
EXPORT_SYMBOL(ग_लिखोq);

/*
 * The _relaxed functions must be ordered w.r.t. each other, but they करोn't
 * have to be ordered w.r.t. other memory accesses.
 */
u8 पढ़ोb_relaxed(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	mb();
	वापस __raw_पढ़ोb(addr);
पूर्ण

u16 पढ़ोw_relaxed(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	mb();
	वापस __raw_पढ़ोw(addr);
पूर्ण

u32 पढ़ोl_relaxed(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	mb();
	वापस __raw_पढ़ोl(addr);
पूर्ण

u64 पढ़ोq_relaxed(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	mb();
	वापस __raw_पढ़ोq(addr);
पूर्ण

EXPORT_SYMBOL(पढ़ोb_relaxed);
EXPORT_SYMBOL(पढ़ोw_relaxed);
EXPORT_SYMBOL(पढ़ोl_relaxed);
EXPORT_SYMBOL(पढ़ोq_relaxed);

/*
 * Read COUNT 8-bit bytes from port PORT पूर्णांकo memory starting at SRC.
 */
व्योम ioपढ़ो8_rep(स्थिर व्योम __iomem *port, व्योम *dst, अचिन्हित दीर्घ count)
अणु
	जबतक ((अचिन्हित दीर्घ)dst & 0x3) अणु
		अगर (!count)
			वापस;
		count--;
		*(अचिन्हित अक्षर *)dst = ioपढ़ो8(port);
		dst += 1;
	पूर्ण

	जबतक (count >= 4) अणु
		अचिन्हित पूर्णांक w;
		count -= 4;
		w = ioपढ़ो8(port);
		w |= ioपढ़ो8(port) << 8;
		w |= ioपढ़ो8(port) << 16;
		w |= ioपढ़ो8(port) << 24;
		*(अचिन्हित पूर्णांक *)dst = w;
		dst += 4;
	पूर्ण

	जबतक (count) अणु
		--count;
		*(अचिन्हित अक्षर *)dst = ioपढ़ो8(port);
		dst += 1;
	पूर्ण
पूर्ण

व्योम insb(अचिन्हित दीर्घ port, व्योम *dst, अचिन्हित दीर्घ count)
अणु
	ioपढ़ो8_rep(ioport_map(port, 1), dst, count);
पूर्ण

EXPORT_SYMBOL(ioपढ़ो8_rep);
EXPORT_SYMBOL(insb);

/*
 * Read COUNT 16-bit words from port PORT पूर्णांकo memory starting at
 * SRC.  SRC must be at least लघु aligned.  This is used by the
 * IDE driver to पढ़ो disk sectors.  Perक्रमmance is important, but
 * the पूर्णांकerfaces seems to be slow: just using the अंतरभूतd version
 * of the inw() अवरोधs things.
 */
व्योम ioपढ़ो16_rep(स्थिर व्योम __iomem *port, व्योम *dst, अचिन्हित दीर्घ count)
अणु
	अगर (unlikely((अचिन्हित दीर्घ)dst & 0x3)) अणु
		अगर (!count)
			वापस;
		BUG_ON((अचिन्हित दीर्घ)dst & 0x1);
		count--;
		*(अचिन्हित लघु *)dst = ioपढ़ो16(port);
		dst += 2;
	पूर्ण

	जबतक (count >= 2) अणु
		अचिन्हित पूर्णांक w;
		count -= 2;
		w = ioपढ़ो16(port);
		w |= ioपढ़ो16(port) << 16;
		*(अचिन्हित पूर्णांक *)dst = w;
		dst += 4;
	पूर्ण

	अगर (count) अणु
		*(अचिन्हित लघु*)dst = ioपढ़ो16(port);
	पूर्ण
पूर्ण

व्योम insw(अचिन्हित दीर्घ port, व्योम *dst, अचिन्हित दीर्घ count)
अणु
	ioपढ़ो16_rep(ioport_map(port, 2), dst, count);
पूर्ण

EXPORT_SYMBOL(ioपढ़ो16_rep);
EXPORT_SYMBOL(insw);


/*
 * Read COUNT 32-bit words from port PORT पूर्णांकo memory starting at
 * SRC. Now works with any alignment in SRC. Perक्रमmance is important,
 * but the पूर्णांकerfaces seems to be slow: just using the अंतरभूतd version
 * of the inl() अवरोधs things.
 */
व्योम ioपढ़ो32_rep(स्थिर व्योम __iomem *port, व्योम *dst, अचिन्हित दीर्घ count)
अणु
	अगर (unlikely((अचिन्हित दीर्घ)dst & 0x3)) अणु
		जबतक (count--) अणु
			काष्ठा S अणु पूर्णांक x __attribute__((packed)); पूर्ण;
			((काष्ठा S *)dst)->x = ioपढ़ो32(port);
			dst += 4;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Buffer 32-bit aligned.  */
		जबतक (count--) अणु
			*(अचिन्हित पूर्णांक *)dst = ioपढ़ो32(port);
			dst += 4;
		पूर्ण
	पूर्ण
पूर्ण

व्योम insl(अचिन्हित दीर्घ port, व्योम *dst, अचिन्हित दीर्घ count)
अणु
	ioपढ़ो32_rep(ioport_map(port, 4), dst, count);
पूर्ण

EXPORT_SYMBOL(ioपढ़ो32_rep);
EXPORT_SYMBOL(insl);


/*
 * Like insb but in the opposite direction.
 * Don't worry as much about करोing aligned memory transfers:
 * करोing byte पढ़ोs the "slow" way isn't nearly as slow as
 * करोing byte ग_लिखोs the slow way (no r-m-w cycle).
 */
व्योम ioग_लिखो8_rep(व्योम __iomem *port, स्थिर व्योम *xsrc, अचिन्हित दीर्घ count)
अणु
	स्थिर अचिन्हित अक्षर *src = xsrc;
	जबतक (count--)
		ioग_लिखो8(*src++, port);
पूर्ण

व्योम outsb(अचिन्हित दीर्घ port, स्थिर व्योम *src, अचिन्हित दीर्घ count)
अणु
	ioग_लिखो8_rep(ioport_map(port, 1), src, count);
पूर्ण

EXPORT_SYMBOL(ioग_लिखो8_rep);
EXPORT_SYMBOL(outsb);


/*
 * Like insw but in the opposite direction.  This is used by the IDE
 * driver to ग_लिखो disk sectors.  Perक्रमmance is important, but the
 * पूर्णांकerfaces seems to be slow: just using the अंतरभूतd version of the
 * outw() अवरोधs things.
 */
व्योम ioग_लिखो16_rep(व्योम __iomem *port, स्थिर व्योम *src, अचिन्हित दीर्घ count)
अणु
	अगर (unlikely((अचिन्हित दीर्घ)src & 0x3)) अणु
		अगर (!count)
			वापस;
		BUG_ON((अचिन्हित दीर्घ)src & 0x1);
		ioग_लिखो16(*(अचिन्हित लघु *)src, port);
		src += 2;
		--count;
	पूर्ण

	जबतक (count >= 2) अणु
		अचिन्हित पूर्णांक w;
		count -= 2;
		w = *(अचिन्हित पूर्णांक *)src;
		src += 4;
		ioग_लिखो16(w >>  0, port);
		ioग_लिखो16(w >> 16, port);
	पूर्ण

	अगर (count) अणु
		ioग_लिखो16(*(अचिन्हित लघु *)src, port);
	पूर्ण
पूर्ण

व्योम outsw(अचिन्हित दीर्घ port, स्थिर व्योम *src, अचिन्हित दीर्घ count)
अणु
	ioग_लिखो16_rep(ioport_map(port, 2), src, count);
पूर्ण

EXPORT_SYMBOL(ioग_लिखो16_rep);
EXPORT_SYMBOL(outsw);


/*
 * Like insl but in the opposite direction.  This is used by the IDE
 * driver to ग_लिखो disk sectors.  Works with any alignment in SRC.
 * Perक्रमmance is important, but the पूर्णांकerfaces seems to be slow:
 * just using the अंतरभूतd version of the outl() अवरोधs things.
 */
व्योम ioग_लिखो32_rep(व्योम __iomem *port, स्थिर व्योम *src, अचिन्हित दीर्घ count)
अणु
	अगर (unlikely((अचिन्हित दीर्घ)src & 0x3)) अणु
		जबतक (count--) अणु
			काष्ठा S अणु पूर्णांक x __attribute__((packed)); पूर्ण;
			ioग_लिखो32(((काष्ठा S *)src)->x, port);
			src += 4;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Buffer 32-bit aligned.  */
		जबतक (count--) अणु
			ioग_लिखो32(*(अचिन्हित पूर्णांक *)src, port);
			src += 4;
		पूर्ण
	पूर्ण
पूर्ण

व्योम outsl(अचिन्हित दीर्घ port, स्थिर व्योम *src, अचिन्हित दीर्घ count)
अणु
	ioग_लिखो32_rep(ioport_map(port, 4), src, count);
पूर्ण

EXPORT_SYMBOL(ioग_लिखो32_rep);
EXPORT_SYMBOL(outsl);


/*
 * Copy data from IO memory space to "real" memory space.
 * This needs to be optimized.
 */
व्योम स_नकल_fromio(व्योम *to, स्थिर अस्थिर व्योम __iomem *from, दीर्घ count)
अणु
	/* Optimize co-aligned transfers.  Everything अन्यथा माला_लो handled
	   a byte at a समय. */

	अगर (count >= 8 && ((u64)to & 7) == ((u64)from & 7)) अणु
		count -= 8;
		करो अणु
			*(u64 *)to = __raw_पढ़ोq(from);
			count -= 8;
			to += 8;
			from += 8;
		पूर्ण जबतक (count >= 0);
		count += 8;
	पूर्ण

	अगर (count >= 4 && ((u64)to & 3) == ((u64)from & 3)) अणु
		count -= 4;
		करो अणु
			*(u32 *)to = __raw_पढ़ोl(from);
			count -= 4;
			to += 4;
			from += 4;
		पूर्ण जबतक (count >= 0);
		count += 4;
	पूर्ण

	अगर (count >= 2 && ((u64)to & 1) == ((u64)from & 1)) अणु
		count -= 2;
		करो अणु
			*(u16 *)to = __raw_पढ़ोw(from);
			count -= 2;
			to += 2;
			from += 2;
		पूर्ण जबतक (count >= 0);
		count += 2;
	पूर्ण

	जबतक (count > 0) अणु
		*(u8 *) to = __raw_पढ़ोb(from);
		count--;
		to++;
		from++;
	पूर्ण
	mb();
पूर्ण

EXPORT_SYMBOL(स_नकल_fromio);


/*
 * Copy data from "real" memory space to IO memory space.
 * This needs to be optimized.
 */
व्योम स_नकल_toio(अस्थिर व्योम __iomem *to, स्थिर व्योम *from, दीर्घ count)
अणु
	/* Optimize co-aligned transfers.  Everything अन्यथा माला_लो handled
	   a byte at a समय. */
	/* FIXME -- align FROM.  */

	अगर (count >= 8 && ((u64)to & 7) == ((u64)from & 7)) अणु
		count -= 8;
		करो अणु
			__raw_ग_लिखोq(*(स्थिर u64 *)from, to);
			count -= 8;
			to += 8;
			from += 8;
		पूर्ण जबतक (count >= 0);
		count += 8;
	पूर्ण

	अगर (count >= 4 && ((u64)to & 3) == ((u64)from & 3)) अणु
		count -= 4;
		करो अणु
			__raw_ग_लिखोl(*(स्थिर u32 *)from, to);
			count -= 4;
			to += 4;
			from += 4;
		पूर्ण जबतक (count >= 0);
		count += 4;
	पूर्ण

	अगर (count >= 2 && ((u64)to & 1) == ((u64)from & 1)) अणु
		count -= 2;
		करो अणु
			__raw_ग_लिखोw(*(स्थिर u16 *)from, to);
			count -= 2;
			to += 2;
			from += 2;
		पूर्ण जबतक (count >= 0);
		count += 2;
	पूर्ण

	जबतक (count > 0) अणु
		__raw_ग_लिखोb(*(स्थिर u8 *) from, to);
		count--;
		to++;
		from++;
	पूर्ण
	mb();
पूर्ण

EXPORT_SYMBOL(स_नकल_toio);


/*
 * "memset" on IO memory space.
 */
व्योम _स_रखो_c_io(अस्थिर व्योम __iomem *to, अचिन्हित दीर्घ c, दीर्घ count)
अणु
	/* Handle any initial odd byte */
	अगर (count > 0 && ((u64)to & 1)) अणु
		__raw_ग_लिखोb(c, to);
		to++;
		count--;
	पूर्ण

	/* Handle any initial odd halfword */
	अगर (count >= 2 && ((u64)to & 2)) अणु
		__raw_ग_लिखोw(c, to);
		to += 2;
		count -= 2;
	पूर्ण

	/* Handle any initial odd word */
	अगर (count >= 4 && ((u64)to & 4)) अणु
		__raw_ग_लिखोl(c, to);
		to += 4;
		count -= 4;
	पूर्ण

	/* Handle all full-sized quadwords: we're aligned
	   (or have a small count) */
	count -= 8;
	अगर (count >= 0) अणु
		करो अणु
			__raw_ग_लिखोq(c, to);
			to += 8;
			count -= 8;
		पूर्ण जबतक (count >= 0);
	पूर्ण
	count += 8;

	/* The tail is word-aligned अगर we still have count >= 4 */
	अगर (count >= 4) अणु
		__raw_ग_लिखोl(c, to);
		to += 4;
		count -= 4;
	पूर्ण

	/* The tail is half-word aligned अगर we have count >= 2 */
	अगर (count >= 2) अणु
		__raw_ग_लिखोw(c, to);
		to += 2;
		count -= 2;
	पूर्ण

	/* And finally, one last byte.. */
	अगर (count) अणु
		__raw_ग_लिखोb(c, to);
	पूर्ण
	mb();
पूर्ण

EXPORT_SYMBOL(_स_रखो_c_io);

/* A version of स_नकल used by the vga console routines to move data around
   arbitrarily between screen and मुख्य memory.  */

व्योम
scr_स_नकलw(u16 *d, स्थिर u16 *s, अचिन्हित पूर्णांक count)
अणु
	स्थिर u16 __iomem *ios = (स्थिर u16 __iomem *) s;
	u16 __iomem *iod = (u16 __iomem *) d;
	पूर्णांक s_isio = __is_ioaddr(s);
	पूर्णांक d_isio = __is_ioaddr(d);

	अगर (s_isio) अणु
		अगर (d_isio) अणु
			/* FIXME: Should handle unaligned ops and
			   operation widening.  */

			count /= 2;
			जबतक (count--) अणु
				u16 पंचांगp = __raw_पढ़ोw(ios++);
				__raw_ग_लिखोw(पंचांगp, iod++);
			पूर्ण
		पूर्ण
		अन्यथा
			स_नकल_fromio(d, ios, count);
	पूर्ण अन्यथा अणु
		अगर (d_isio)
			स_नकल_toio(iod, s, count);
		अन्यथा
			स_नकल(d, s, count);
	पूर्ण
पूर्ण

EXPORT_SYMBOL(scr_स_नकलw);

व्योम __iomem *ioport_map(अचिन्हित दीर्घ port, अचिन्हित पूर्णांक size)
अणु
	वापस IO_CONCAT(__IO_PREFIX,ioporपंचांगap) (port);
पूर्ण

व्योम ioport_unmap(व्योम __iomem *addr)
अणु
पूर्ण

EXPORT_SYMBOL(ioport_map);
EXPORT_SYMBOL(ioport_unmap);
