<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/parisc/lib/io.c
 *
 * Copyright (c) Matthew Wilcox 2001 क्रम Hewlett-Packard
 * Copyright (c) Ranकरोlph Chung 2001 <tausq@debian.org>
 *
 * IO accessing functions which shouldn't be inlined because they're too big
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/पन.स>

/* Copies a block of memory to a device in an efficient manner.
 * Assumes the device can cope with 32-bit transfers.  If it can't,
 * करोn't use this function.
 */
व्योम स_नकल_toio(अस्थिर व्योम __iomem *dst, स्थिर व्योम *src, पूर्णांक count)
अणु
	अगर (((अचिन्हित दीर्घ)dst & 3) != ((अचिन्हित दीर्घ)src & 3))
		जाओ bytecopy;
	जबतक ((अचिन्हित दीर्घ)dst & 3) अणु
		ग_लिखोb(*(अक्षर *)src, dst++);
		src++;
		count--;
	पूर्ण
	जबतक (count > 3) अणु
		__raw_ग_लिखोl(*(u32 *)src, dst);
		src += 4;
		dst += 4;
		count -= 4;
	पूर्ण
 bytecopy:
	जबतक (count--) अणु
		ग_लिखोb(*(अक्षर *)src, dst++);
		src++;
	पूर्ण
पूर्ण

/*
** Copies a block of memory from a device in an efficient manner.
** Assumes the device can cope with 32-bit transfers.  If it can't,
** करोn't use this function.
**
** CR16 counts on C3000 पढ़ोing 256 bytes from Symbios 896 RAM:
**	27341/64    = 427 cyc per पूर्णांक
**	61311/128   = 478 cyc per लघु
**	122637/256  = 479 cyc per byte
** Ergo bus latencies करोminant (not transfer size).
**      Minimize total number of transfers at cost of CPU cycles.
**	TODO: only look at src alignment and adjust the stores to dest.
*/
व्योम स_नकल_fromio(व्योम *dst, स्थिर अस्थिर व्योम __iomem *src, पूर्णांक count)
अणु
	/* first compare alignment of src/dst */ 
	अगर ( (((अचिन्हित दीर्घ)dst ^ (अचिन्हित दीर्घ)src) & 1) || (count < 2) )
		जाओ bytecopy;

	अगर ( (((अचिन्हित दीर्घ)dst ^ (अचिन्हित दीर्घ)src) & 2) || (count < 4) )
		जाओ लघुcopy;

	/* Then check क्रम misaligned start address */
	अगर ((अचिन्हित दीर्घ)src & 1) अणु
		*(u8 *)dst = पढ़ोb(src);
		src++;
		dst++;
		count--;
		अगर (count < 2) जाओ bytecopy;
	पूर्ण

	अगर ((अचिन्हित दीर्घ)src & 2) अणु
		*(u16 *)dst = __raw_पढ़ोw(src);
		src += 2;
		dst += 2;
		count -= 2;
	पूर्ण

	जबतक (count > 3) अणु
		*(u32 *)dst = __raw_पढ़ोl(src);
		dst += 4;
		src += 4;
		count -= 4;
	पूर्ण

 लघुcopy:
	जबतक (count > 1) अणु
		*(u16 *)dst = __raw_पढ़ोw(src);
		src += 2;
		dst += 2;
		count -= 2;
	पूर्ण

 bytecopy:
	जबतक (count--) अणु
		*(अक्षर *)dst = पढ़ोb(src);
		src++;
		dst++;
	पूर्ण
पूर्ण

/* Sets a block of memory on a device to a given value.
 * Assumes the device can cope with 32-bit transfers.  If it can't,
 * करोn't use this function.
 */
व्योम स_रखो_io(अस्थिर व्योम __iomem *addr, अचिन्हित अक्षर val, पूर्णांक count)
अणु
	u32 val32 = (val << 24) | (val << 16) | (val << 8) | val;
	जबतक ((अचिन्हित दीर्घ)addr & 3) अणु
		ग_लिखोb(val, addr++);
		count--;
	पूर्ण
	जबतक (count > 3) अणु
		__raw_ग_लिखोl(val32, addr);
		addr += 4;
		count -= 4;
	पूर्ण
	जबतक (count--) अणु
		ग_लिखोb(val, addr++);
	पूर्ण
पूर्ण

/*
 * Read COUNT 8-bit bytes from port PORT पूर्णांकo memory starting at
 * SRC.
 */
व्योम insb (अचिन्हित दीर्घ port, व्योम *dst, अचिन्हित दीर्घ count)
अणु
	अचिन्हित अक्षर *p;

	p = (अचिन्हित अक्षर *)dst;

	जबतक (((अचिन्हित दीर्घ)p) & 0x3) अणु
		अगर (!count)
			वापस;
		count--;
		*p = inb(port);
		p++;
	पूर्ण

	जबतक (count >= 4) अणु
		अचिन्हित पूर्णांक w;
		count -= 4;
		w = inb(port) << 24;
		w |= inb(port) << 16;
		w |= inb(port) << 8;
		w |= inb(port);
		*(अचिन्हित पूर्णांक *) p = w;
		p += 4;
	पूर्ण

	जबतक (count) अणु
		--count;
		*p = inb(port);
		p++;
	पूर्ण
पूर्ण


/*
 * Read COUNT 16-bit words from port PORT पूर्णांकo memory starting at
 * SRC.  SRC must be at least लघु aligned.  This is used by the
 * IDE driver to पढ़ो disk sectors.  Perक्रमmance is important, but
 * the पूर्णांकerfaces seems to be slow: just using the अंतरभूतd version
 * of the inw() अवरोधs things.
 */
व्योम insw (अचिन्हित दीर्घ port, व्योम *dst, अचिन्हित दीर्घ count)
अणु
	अचिन्हित पूर्णांक l = 0, l2;
	अचिन्हित अक्षर *p;

	p = (अचिन्हित अक्षर *)dst;
	
	अगर (!count)
		वापस;
	
	चयन (((अचिन्हित दीर्घ)p) & 0x3)
	अणु
	 हाल 0x00:			/* Buffer 32-bit aligned */
		जबतक (count>=2) अणु
			
			count -= 2;
			l = cpu_to_le16(inw(port)) << 16;
			l |= cpu_to_le16(inw(port));
			*(अचिन्हित पूर्णांक *)p = l;
			p += 4;
		पूर्ण
		अगर (count) अणु
			*(अचिन्हित लघु *)p = cpu_to_le16(inw(port));
		पूर्ण
		अवरोध;
	
	 हाल 0x02:			/* Buffer 16-bit aligned */
		*(अचिन्हित लघु *)p = cpu_to_le16(inw(port));
		p += 2;
		count--;
		जबतक (count>=2) अणु
			
			count -= 2;
			l = cpu_to_le16(inw(port)) << 16;
			l |= cpu_to_le16(inw(port));
			*(अचिन्हित पूर्णांक *)p = l;
			p += 4;
		पूर्ण
		अगर (count) अणु
			*(अचिन्हित लघु *)p = cpu_to_le16(inw(port));
		पूर्ण
		अवरोध;
		
	 हाल 0x01:			/* Buffer 8-bit aligned */
	 हाल 0x03:
		/* I करोn't bother with 32bit transfers
		 * in this हाल, 16bit will have to करो -- DE */
		--count;
		
		l = cpu_to_le16(inw(port));
		*p = l >> 8;
		p++;
		जबतक (count--)
		अणु
			l2 = cpu_to_le16(inw(port));
			*(अचिन्हित लघु *)p = (l & 0xff) << 8 | (l2 >> 8);
			p += 2;
			l = l2;
		पूर्ण
		*p = l & 0xff;
		अवरोध;
	पूर्ण
पूर्ण



/*
 * Read COUNT 32-bit words from port PORT पूर्णांकo memory starting at
 * SRC. Now works with any alignment in SRC. Perक्रमmance is important,
 * but the पूर्णांकerfaces seems to be slow: just using the अंतरभूतd version
 * of the inl() अवरोधs things.
 */
व्योम insl (अचिन्हित दीर्घ port, व्योम *dst, अचिन्हित दीर्घ count)
अणु
	अचिन्हित पूर्णांक l = 0, l2;
	अचिन्हित अक्षर *p;

	p = (अचिन्हित अक्षर *)dst;
	
	अगर (!count)
		वापस;
	
	चयन (((अचिन्हित दीर्घ) dst) & 0x3)
	अणु
	 हाल 0x00:			/* Buffer 32-bit aligned */
		जबतक (count--)
		अणु
			*(अचिन्हित पूर्णांक *)p = cpu_to_le32(inl(port));
			p += 4;
		पूर्ण
		अवरोध;
	
	 हाल 0x02:			/* Buffer 16-bit aligned */
		--count;
		
		l = cpu_to_le32(inl(port));
		*(अचिन्हित लघु *)p = l >> 16;
		p += 2;
		
		जबतक (count--)
		अणु
			l2 = cpu_to_le32(inl(port));
			*(अचिन्हित पूर्णांक *)p = (l & 0xffff) << 16 | (l2 >> 16);
			p += 4;
			l = l2;
		पूर्ण
		*(अचिन्हित लघु *)p = l & 0xffff;
		अवरोध;
	 हाल 0x01:			/* Buffer 8-bit aligned */
		--count;
		
		l = cpu_to_le32(inl(port));
		*(अचिन्हित अक्षर *)p = l >> 24;
		p++;
		*(अचिन्हित लघु *)p = (l >> 8) & 0xffff;
		p += 2;
		जबतक (count--)
		अणु
			l2 = cpu_to_le32(inl(port));
			*(अचिन्हित पूर्णांक *)p = (l & 0xff) << 24 | (l2 >> 8);
			p += 4;
			l = l2;
		पूर्ण
		*p = l & 0xff;
		अवरोध;
	 हाल 0x03:			/* Buffer 8-bit aligned */
		--count;
		
		l = cpu_to_le32(inl(port));
		*p = l >> 24;
		p++;
		जबतक (count--)
		अणु
			l2 = cpu_to_le32(inl(port));
			*(अचिन्हित पूर्णांक *)p = (l & 0xffffff) << 8 | l2 >> 24;
			p += 4;
			l = l2;
		पूर्ण
		*(अचिन्हित लघु *)p = (l >> 8) & 0xffff;
		p += 2;
		*p = l & 0xff;
		अवरोध;
	पूर्ण
पूर्ण


/*
 * Like insb but in the opposite direction.
 * Don't worry as much about करोing aligned memory transfers:
 * करोing byte पढ़ोs the "slow" way isn't nearly as slow as
 * करोing byte ग_लिखोs the slow way (no r-m-w cycle).
 */
व्योम outsb(अचिन्हित दीर्घ port, स्थिर व्योम * src, अचिन्हित दीर्घ count)
अणु
	स्थिर अचिन्हित अक्षर *p;

	p = (स्थिर अचिन्हित अक्षर *)src;
	जबतक (count) अणु
		count--;
		outb(*p, port);
		p++;
	पूर्ण
पूर्ण

/*
 * Like insw but in the opposite direction.  This is used by the IDE
 * driver to ग_लिखो disk sectors.  Perक्रमmance is important, but the
 * पूर्णांकerfaces seems to be slow: just using the अंतरभूतd version of the
 * outw() अवरोधs things.
 */
व्योम outsw (अचिन्हित दीर्घ port, स्थिर व्योम *src, अचिन्हित दीर्घ count)
अणु
	अचिन्हित पूर्णांक l = 0, l2;
	स्थिर अचिन्हित अक्षर *p;

	p = (स्थिर अचिन्हित अक्षर *)src;
	
	अगर (!count)
		वापस;
	
	चयन (((अचिन्हित दीर्घ)p) & 0x3)
	अणु
	 हाल 0x00:			/* Buffer 32-bit aligned */
		जबतक (count>=2) अणु
			count -= 2;
			l = *(अचिन्हित पूर्णांक *)p;
			p += 4;
			outw(le16_to_cpu(l >> 16), port);
			outw(le16_to_cpu(l & 0xffff), port);
		पूर्ण
		अगर (count) अणु
			outw(le16_to_cpu(*(अचिन्हित लघु*)p), port);
		पूर्ण
		अवरोध;
	
	 हाल 0x02:			/* Buffer 16-bit aligned */
		
		outw(le16_to_cpu(*(अचिन्हित लघु*)p), port);
		p += 2;
		count--;
		
		जबतक (count>=2) अणु
			count -= 2;
			l = *(अचिन्हित पूर्णांक *)p;
			p += 4;
			outw(le16_to_cpu(l >> 16), port);
			outw(le16_to_cpu(l & 0xffff), port);
		पूर्ण
		अगर (count) अणु
			outw(le16_to_cpu(*(अचिन्हित लघु *)p), port);
		पूर्ण
		अवरोध;
		
	 हाल 0x01:			/* Buffer 8-bit aligned */	
		/* I करोn't bother with 32bit transfers
		 * in this हाल, 16bit will have to करो -- DE */
		
		l  = *p << 8;
		p++;
		count--;
		जबतक (count)
		अणु
			count--;
			l2 = *(अचिन्हित लघु *)p;
			p += 2;
			outw(le16_to_cpu(l | l2 >> 8), port);
		        l = l2 << 8;
		पूर्ण
		l2 = *(अचिन्हित अक्षर *)p;
		outw (le16_to_cpu(l | l2>>8), port);
		अवरोध;
	
	पूर्ण
पूर्ण


/*
 * Like insl but in the opposite direction.  This is used by the IDE
 * driver to ग_लिखो disk sectors.  Works with any alignment in SRC.
 *  Perक्रमmance is important, but the पूर्णांकerfaces seems to be slow:
 * just using the अंतरभूतd version of the outl() अवरोधs things.
 */
व्योम outsl (अचिन्हित दीर्घ port, स्थिर व्योम *src, अचिन्हित दीर्घ count)
अणु
	अचिन्हित पूर्णांक l = 0, l2;
	स्थिर अचिन्हित अक्षर *p;

	p = (स्थिर अचिन्हित अक्षर *)src;
	
	अगर (!count)
		वापस;
	
	चयन (((अचिन्हित दीर्घ)p) & 0x3)
	अणु
	 हाल 0x00:			/* Buffer 32-bit aligned */
		जबतक (count--)
		अणु
			outl(le32_to_cpu(*(अचिन्हित पूर्णांक *)p), port);
			p += 4;
		पूर्ण
		अवरोध;
	
	 हाल 0x02:			/* Buffer 16-bit aligned */
		--count;
		
		l = *(अचिन्हित लघु *)p;
		p += 2;
		
		जबतक (count--)
		अणु
			l2 = *(अचिन्हित पूर्णांक *)p;
			p += 4;
			outl (le32_to_cpu(l << 16 | l2 >> 16), port);
			l = l2;
		पूर्ण
		l2 = *(अचिन्हित लघु *)p;
		outl (le32_to_cpu(l << 16 | l2), port);
		अवरोध;
	 हाल 0x01:			/* Buffer 8-bit aligned */
		--count;

		l = *p << 24;
		p++;
		l |= *(अचिन्हित लघु *)p << 8;
		p += 2;

		जबतक (count--)
		अणु
			l2 = *(अचिन्हित पूर्णांक *)p;
			p += 4;
			outl (le32_to_cpu(l | l2 >> 24), port);
			l = l2 << 8;
		पूर्ण
		l2 = *p;
		outl (le32_to_cpu(l | l2), port);
		अवरोध;
	 हाल 0x03:			/* Buffer 8-bit aligned */
		--count;
		
		l = *p << 24;
		p++;

		जबतक (count--)
		अणु
			l2 = *(अचिन्हित पूर्णांक *)p;
			p += 4;
			outl (le32_to_cpu(l | l2 >> 8), port);
			l = l2 << 24;
		पूर्ण
		l2 = *(अचिन्हित लघु *)p << 16;
		p += 2;
		l2 |= *p;
		outl (le32_to_cpu(l | l2), port);
		अवरोध;
	पूर्ण
पूर्ण

EXPORT_SYMBOL(insb);
EXPORT_SYMBOL(insw);
EXPORT_SYMBOL(insl);
EXPORT_SYMBOL(outsb);
EXPORT_SYMBOL(outsw);
EXPORT_SYMBOL(outsl);
