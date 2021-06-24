<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PeeCeeI.c: The emerging standard...
 *
 * Copyright (C) 1997 David S. Miller (davem@caip.rutgers.edu)
 */

#समावेश <linux/module.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/byteorder.h>

व्योम outsb(अचिन्हित दीर्घ __addr, स्थिर व्योम *src, अचिन्हित दीर्घ count)
अणु
	व्योम __iomem *addr = (व्योम __iomem *) __addr;
	स्थिर u8 *p = src;

	जबतक (count--)
		__raw_ग_लिखोb(*p++, addr);
पूर्ण
EXPORT_SYMBOL(outsb);

व्योम outsw(अचिन्हित दीर्घ __addr, स्थिर व्योम *src, अचिन्हित दीर्घ count)
अणु
	व्योम __iomem *addr = (व्योम __iomem *) __addr;

	जबतक (count--) अणु
		__raw_ग_लिखोw(*(u16 *)src, addr);
		src += माप(u16);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(outsw);

व्योम outsl(अचिन्हित दीर्घ __addr, स्थिर व्योम *src, अचिन्हित दीर्घ count)
अणु
	व्योम __iomem *addr = (व्योम __iomem *) __addr;
	u32 l, l2;

	अगर (!count)
		वापस;

	चयन (((अचिन्हित दीर्घ)src) & 0x3) अणु
	हाल 0x0:
		/* src is naturally aligned */
		जबतक (count--) अणु
			__raw_ग_लिखोl(*(u32 *)src, addr);
			src += माप(u32);
		पूर्ण
		अवरोध;
	हाल 0x2:
		/* 2-byte alignment */
		जबतक (count--) अणु
			l = (*(u16 *)src) << 16;
			l |= *(u16 *)(src + माप(u16));
			__raw_ग_लिखोl(l, addr);
			src += माप(u32);
		पूर्ण
		अवरोध;
	हाल 0x1:
		/* Hold three bytes in l each समय, grab a byte from l2 */
		l = (*(u8 *)src) << 24;
		l |= (*(u16 *)(src + माप(u8))) << 8;
		src += माप(u8) + माप(u16);
		जबतक (count--) अणु
			l2 = *(u32 *)src;
			l |= (l2 >> 24);
			__raw_ग_लिखोl(l, addr);
			l = l2 << 8;
			src += माप(u32);
		पूर्ण
		अवरोध;
	हाल 0x3:
		/* Hold a byte in l each समय, grab 3 bytes from l2 */
		l = (*(u8 *)src) << 24;
		src += माप(u8);
		जबतक (count--) अणु
			l2 = *(u32 *)src;
			l |= (l2 >> 8);
			__raw_ग_लिखोl(l, addr);
			l = l2 << 24;
			src += माप(u32);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(outsl);

व्योम insb(अचिन्हित दीर्घ __addr, व्योम *dst, अचिन्हित दीर्घ count)
अणु
	व्योम __iomem *addr = (व्योम __iomem *) __addr;

	अगर (count) अणु
		u32 *pi;
		u8 *pb = dst;

		जबतक ((((अचिन्हित दीर्घ)pb) & 0x3) && count--)
			*pb++ = __raw_पढ़ोb(addr);
		pi = (u32 *)pb;
		जबतक (count >= 4) अणु
			u32 w;

			w  = (__raw_पढ़ोb(addr) << 24);
			w |= (__raw_पढ़ोb(addr) << 16);
			w |= (__raw_पढ़ोb(addr) << 8);
			w |= (__raw_पढ़ोb(addr) << 0);
			*pi++ = w;
			count -= 4;
		पूर्ण
		pb = (u8 *)pi;
		जबतक (count--)
			*pb++ = __raw_पढ़ोb(addr);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(insb);

व्योम insw(अचिन्हित दीर्घ __addr, व्योम *dst, अचिन्हित दीर्घ count)
अणु
	व्योम __iomem *addr = (व्योम __iomem *) __addr;

	अगर (count) अणु
		u16 *ps = dst;
		u32 *pi;

		अगर (((अचिन्हित दीर्घ)ps) & 0x2) अणु
			*ps++ = __raw_पढ़ोw(addr);
			count--;
		पूर्ण
		pi = (u32 *)ps;
		जबतक (count >= 2) अणु
			u32 w;

			w  = __raw_पढ़ोw(addr) << 16;
			w |= __raw_पढ़ोw(addr) << 0;
			*pi++ = w;
			count -= 2;
		पूर्ण
		ps = (u16 *)pi;
		अगर (count)
			*ps = __raw_पढ़ोw(addr);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(insw);

व्योम insl(अचिन्हित दीर्घ __addr, व्योम *dst, अचिन्हित दीर्घ count)
अणु
	व्योम __iomem *addr = (व्योम __iomem *) __addr;

	अगर (count) अणु
		अगर ((((अचिन्हित दीर्घ)dst) & 0x3) == 0) अणु
			u32 *pi = dst;
			जबतक (count--)
				*pi++ = __raw_पढ़ोl(addr);
		पूर्ण अन्यथा अणु
			u32 l = 0, l2, *pi;
			u16 *ps;
			u8 *pb;

			चयन (((अचिन्हित दीर्घ)dst) & 3) अणु
			हाल 0x2:
				ps = dst;
				count -= 1;
				l = __raw_पढ़ोl(addr);
				*ps++ = l;
				pi = (u32 *)ps;
				जबतक (count--) अणु
					l2 = __raw_पढ़ोl(addr);
					*pi++ = (l << 16) | (l2 >> 16);
					l = l2;
				पूर्ण
				ps = (u16 *)pi;
				*ps = l;
				अवरोध;

			हाल 0x1:
				pb = dst;
				count -= 1;
				l = __raw_पढ़ोl(addr);
				*pb++ = l >> 24;
				ps = (u16 *)pb;
				*ps++ = ((l >> 8) & 0xffff);
				pi = (u32 *)ps;
				जबतक (count--) अणु
					l2 = __raw_पढ़ोl(addr);
					*pi++ = (l << 24) | (l2 >> 8);
					l = l2;
				पूर्ण
				pb = (u8 *)pi;
				*pb = l;
				अवरोध;

			हाल 0x3:
				pb = (u8 *)dst;
				count -= 1;
				l = __raw_पढ़ोl(addr);
				*pb++ = l >> 24;
				pi = (u32 *)pb;
				जबतक (count--) अणु
					l2 = __raw_पढ़ोl(addr);
					*pi++ = (l << 8) | (l2 >> 24);
					l = l2;
				पूर्ण
				ps = (u16 *)pi;
				*ps++ = ((l >> 8) & 0xffff);
				pb = (u8 *)ps;
				*pb = l;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(insl);

