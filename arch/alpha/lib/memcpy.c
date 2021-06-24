<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/alpha/lib/स_नकल.c
 *
 *  Copyright (C) 1995  Linus Torvalds
 */

/*
 * This is a reasonably optimized स_नकल() routine.
 */

/*
 * Note that the C code is written to be optimized पूर्णांकo good assembly. However,
 * at this poपूर्णांक gcc is unable to sanely compile "if (n >= 0)", resulting in a
 * explicit compare against 0 (instead of just using the proper "blt reg, xx" or
 * "bge reg, xx"). I hope alpha-gcc will be fixed to notice this eventually..
 */

#समावेश <linux/types.h>
#समावेश <linux/export.h>

/*
 * This should be करोne in one go with ldq_u*2/mask/stq_u. Do it
 * with a macro so that we can fix it up later..
 */
#घोषणा ALIGN_DEST_TO8_UP(d,s,n) \
	जबतक (d & 7) अणु \
		अगर (n <= 0) वापस; \
		n--; \
		*(अक्षर *) d = *(अक्षर *) s; \
		d++; s++; \
	पूर्ण
#घोषणा ALIGN_DEST_TO8_DN(d,s,n) \
	जबतक (d & 7) अणु \
		अगर (n <= 0) वापस; \
		n--; \
		d--; s--; \
		*(अक्षर *) d = *(अक्षर *) s; \
	पूर्ण

/*
 * This should similarly be करोne with ldq_u*2/mask/stq. The destination
 * is aligned, but we करोn't fill in a full quad-word
 */
#घोषणा DO_REST_UP(d,s,n) \
	जबतक (n > 0) अणु \
		n--; \
		*(अक्षर *) d = *(अक्षर *) s; \
		d++; s++; \
	पूर्ण
#घोषणा DO_REST_DN(d,s,n) \
	जबतक (n > 0) अणु \
		n--; \
		d--; s--; \
		*(अक्षर *) d = *(अक्षर *) s; \
	पूर्ण

/*
 * This should be करोne with ldq/mask/stq. The source and destination are
 * aligned, but we करोn't fill in a full quad-word
 */
#घोषणा DO_REST_ALIGNED_UP(d,s,n) DO_REST_UP(d,s,n)
#घोषणा DO_REST_ALIGNED_DN(d,s,n) DO_REST_DN(d,s,n)

/*
 * This करोes unaligned memory copies. We want to aव्योम storing to
 * an unaligned address, as that would करो a पढ़ो-modअगरy-ग_लिखो cycle.
 * We also want to aव्योम द्विगुन-पढ़ोing the unaligned पढ़ोs.
 *
 * Note the ordering to try to aव्योम load (and address generation) latencies.
 */
अटल अंतरभूत व्योम __स_नकल_unaligned_up (अचिन्हित दीर्घ d, अचिन्हित दीर्घ s,
					  दीर्घ n)
अणु
	ALIGN_DEST_TO8_UP(d,s,n);
	n -= 8;			/* to aव्योम compare against 8 in the loop */
	अगर (n >= 0) अणु
		अचिन्हित दीर्घ low_word, high_word;
		__यंत्र__("ldq_u %0,%1":"=r" (low_word):"m" (*(अचिन्हित दीर्घ *) s));
		करो अणु
			अचिन्हित दीर्घ पंचांगp;
			__यंत्र__("ldq_u %0,%1":"=r" (high_word):"m" (*(अचिन्हित दीर्घ *)(s+8)));
			n -= 8;
			__यंत्र__("extql %1,%2,%0"
				:"=r" (low_word)
				:"r" (low_word), "r" (s));
			__यंत्र__("extqh %1,%2,%0"
				:"=r" (पंचांगp)
				:"r" (high_word), "r" (s));
			s += 8;
			*(अचिन्हित दीर्घ *) d = low_word | पंचांगp;
			d += 8;
			low_word = high_word;
		पूर्ण जबतक (n >= 0);
	पूर्ण
	n += 8;
	DO_REST_UP(d,s,n);
पूर्ण

अटल अंतरभूत व्योम __स_नकल_unaligned_dn (अचिन्हित दीर्घ d, अचिन्हित दीर्घ s,
					  दीर्घ n)
अणु
	/* I करोn't understand AXP assembler well enough क्रम this. -Tim */
	s += n;
	d += n;
	जबतक (n--)
		* (अक्षर *) --d = * (अक्षर *) --s;
पूर्ण

/*
 * Hmm.. Strange. The __यंत्र__ here is there to make gcc use an पूर्णांकeger रेजिस्टर
 * क्रम the load-store. I करोn't know why, but it would seem that using a भग्नing
 * poपूर्णांक रेजिस्टर क्रम the move seems to slow things करोwn (very small dअगरference,
 * though).
 *
 * Note the ordering to try to aव्योम load (and address generation) latencies.
 */
अटल अंतरभूत व्योम __स_नकल_aligned_up (अचिन्हित दीर्घ d, अचिन्हित दीर्घ s,
					दीर्घ n)
अणु
	ALIGN_DEST_TO8_UP(d,s,n);
	n -= 8;
	जबतक (n >= 0) अणु
		अचिन्हित दीर्घ पंचांगp;
		__यंत्र__("ldq %0,%1":"=r" (पंचांगp):"m" (*(अचिन्हित दीर्घ *) s));
		n -= 8;
		s += 8;
		*(अचिन्हित दीर्घ *) d = पंचांगp;
		d += 8;
	पूर्ण
	n += 8;
	DO_REST_ALIGNED_UP(d,s,n);
पूर्ण
अटल अंतरभूत व्योम __स_नकल_aligned_dn (अचिन्हित दीर्घ d, अचिन्हित दीर्घ s,
					दीर्घ n)
अणु
	s += n;
	d += n;
	ALIGN_DEST_TO8_DN(d,s,n);
	n -= 8;
	जबतक (n >= 0) अणु
		अचिन्हित दीर्घ पंचांगp;
		s -= 8;
		__यंत्र__("ldq %0,%1":"=r" (पंचांगp):"m" (*(अचिन्हित दीर्घ *) s));
		n -= 8;
		d -= 8;
		*(अचिन्हित दीर्घ *) d = पंचांगp;
	पूर्ण
	n += 8;
	DO_REST_ALIGNED_DN(d,s,n);
पूर्ण

व्योम * स_नकल(व्योम * dest, स्थिर व्योम *src, माप_प्रकार n)
अणु
	अगर (!(((अचिन्हित दीर्घ) dest ^ (अचिन्हित दीर्घ) src) & 7)) अणु
		__स_नकल_aligned_up ((अचिन्हित दीर्घ) dest, (अचिन्हित दीर्घ) src,
				     n);
		वापस dest;
	पूर्ण
	__स_नकल_unaligned_up ((अचिन्हित दीर्घ) dest, (अचिन्हित दीर्घ) src, n);
	वापस dest;
पूर्ण
EXPORT_SYMBOL(स_नकल);
