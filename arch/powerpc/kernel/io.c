<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * I/O string operations
 *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)
 *    Copyright (C) 2006 IBM Corporation
 *
 * Largely rewritten by Cort Dougan (cort@cs.nmt.edu)
 * and Paul Mackerras.
 *
 * Adapted क्रम iSeries by Mike Corrigan (mikejc@us.ibm.com)
 * PPC64 updates by Dave Engebretsen (engebret@us.ibm.com)
 *
 * Rewritten in C by Stephen Rothwell.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/compiler.h>
#समावेश <linux/export.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/bug.h>

/* See definition in पन.स */
bool isa_io_special;

व्योम _insb(स्थिर अस्थिर u8 __iomem *port, व्योम *buf, दीर्घ count)
अणु
	u8 *tbuf = buf;
	u8 पंचांगp;

	अगर (unlikely(count <= 0))
		वापस;
	यंत्र अस्थिर("sync");
	करो अणु
		पंचांगp = *port;
		eieio();
		*tbuf++ = पंचांगp;
	पूर्ण जबतक (--count != 0);
	यंत्र अस्थिर("twi 0,%0,0; isync" : : "r" (पंचांगp));
पूर्ण
EXPORT_SYMBOL(_insb);

व्योम _outsb(अस्थिर u8 __iomem *port, स्थिर व्योम *buf, दीर्घ count)
अणु
	स्थिर u8 *tbuf = buf;

	अगर (unlikely(count <= 0))
		वापस;
	यंत्र अस्थिर("sync");
	करो अणु
		*port = *tbuf++;
	पूर्ण जबतक (--count != 0);
	यंत्र अस्थिर("sync");
पूर्ण
EXPORT_SYMBOL(_outsb);

व्योम _insw_ns(स्थिर अस्थिर u16 __iomem *port, व्योम *buf, दीर्घ count)
अणु
	u16 *tbuf = buf;
	u16 पंचांगp;

	अगर (unlikely(count <= 0))
		वापस;
	यंत्र अस्थिर("sync");
	करो अणु
		पंचांगp = *port;
		eieio();
		*tbuf++ = पंचांगp;
	पूर्ण जबतक (--count != 0);
	यंत्र अस्थिर("twi 0,%0,0; isync" : : "r" (पंचांगp));
पूर्ण
EXPORT_SYMBOL(_insw_ns);

व्योम _outsw_ns(अस्थिर u16 __iomem *port, स्थिर व्योम *buf, दीर्घ count)
अणु
	स्थिर u16 *tbuf = buf;

	अगर (unlikely(count <= 0))
		वापस;
	यंत्र अस्थिर("sync");
	करो अणु
		*port = *tbuf++;
	पूर्ण जबतक (--count != 0);
	यंत्र अस्थिर("sync");
पूर्ण
EXPORT_SYMBOL(_outsw_ns);

व्योम _insl_ns(स्थिर अस्थिर u32 __iomem *port, व्योम *buf, दीर्घ count)
अणु
	u32 *tbuf = buf;
	u32 पंचांगp;

	अगर (unlikely(count <= 0))
		वापस;
	यंत्र अस्थिर("sync");
	करो अणु
		पंचांगp = *port;
		eieio();
		*tbuf++ = पंचांगp;
	पूर्ण जबतक (--count != 0);
	यंत्र अस्थिर("twi 0,%0,0; isync" : : "r" (पंचांगp));
पूर्ण
EXPORT_SYMBOL(_insl_ns);

व्योम _outsl_ns(अस्थिर u32 __iomem *port, स्थिर व्योम *buf, दीर्घ count)
अणु
	स्थिर u32 *tbuf = buf;

	अगर (unlikely(count <= 0))
		वापस;
	यंत्र अस्थिर("sync");
	करो अणु
		*port = *tbuf++;
	पूर्ण जबतक (--count != 0);
	यंत्र अस्थिर("sync");
पूर्ण
EXPORT_SYMBOL(_outsl_ns);

#घोषणा IO_CHECK_ALIGN(v,a) ((((अचिन्हित दीर्घ)(v)) & ((a) - 1)) == 0)

notrace व्योम
_स_रखो_io(अस्थिर व्योम __iomem *addr, पूर्णांक c, अचिन्हित दीर्घ n)
अणु
	व्योम *p = (व्योम __क्रमce *)addr;
	u32 lc = c;
	lc |= lc << 8;
	lc |= lc << 16;

	__यंत्र__ __अस्थिर__ ("sync" : : : "memory");
	जबतक(n && !IO_CHECK_ALIGN(p, 4)) अणु
		*((अस्थिर u8 *)p) = c;
		p++;
		n--;
	पूर्ण
	जबतक(n >= 4) अणु
		*((अस्थिर u32 *)p) = lc;
		p += 4;
		n -= 4;
	पूर्ण
	जबतक(n) अणु
		*((अस्थिर u8 *)p) = c;
		p++;
		n--;
	पूर्ण
	__यंत्र__ __अस्थिर__ ("sync" : : : "memory");
पूर्ण
EXPORT_SYMBOL(_स_रखो_io);

व्योम _स_नकल_fromio(व्योम *dest, स्थिर अस्थिर व्योम __iomem *src,
		    अचिन्हित दीर्घ n)
अणु
	व्योम *vsrc = (व्योम __क्रमce *) src;

	__यंत्र__ __अस्थिर__ ("sync" : : : "memory");
	जबतक(n && (!IO_CHECK_ALIGN(vsrc, 4) || !IO_CHECK_ALIGN(dest, 4))) अणु
		*((u8 *)dest) = *((अस्थिर u8 *)vsrc);
		eieio();
		vsrc++;
		dest++;
		n--;
	पूर्ण
	जबतक(n >= 4) अणु
		*((u32 *)dest) = *((अस्थिर u32 *)vsrc);
		eieio();
		vsrc += 4;
		dest += 4;
		n -= 4;
	पूर्ण
	जबतक(n) अणु
		*((u8 *)dest) = *((अस्थिर u8 *)vsrc);
		eieio();
		vsrc++;
		dest++;
		n--;
	पूर्ण
	__यंत्र__ __अस्थिर__ ("sync" : : : "memory");
पूर्ण
EXPORT_SYMBOL(_स_नकल_fromio);

व्योम _स_नकल_toio(अस्थिर व्योम __iomem *dest, स्थिर व्योम *src, अचिन्हित दीर्घ n)
अणु
	व्योम *vdest = (व्योम __क्रमce *) dest;

	__यंत्र__ __अस्थिर__ ("sync" : : : "memory");
	जबतक(n && (!IO_CHECK_ALIGN(vdest, 4) || !IO_CHECK_ALIGN(src, 4))) अणु
		*((अस्थिर u8 *)vdest) = *((u8 *)src);
		src++;
		vdest++;
		n--;
	पूर्ण
	जबतक(n >= 4) अणु
		*((अस्थिर u32 *)vdest) = *((अस्थिर u32 *)src);
		src += 4;
		vdest += 4;
		n-=4;
	पूर्ण
	जबतक(n) अणु
		*((अस्थिर u8 *)vdest) = *((u8 *)src);
		src++;
		vdest++;
		n--;
	पूर्ण
	__यंत्र__ __अस्थिर__ ("sync" : : : "memory");
पूर्ण
EXPORT_SYMBOL(_स_नकल_toio);
