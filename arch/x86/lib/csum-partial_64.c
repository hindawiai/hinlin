<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/x86_64/lib/csum-partial.c
 *
 * This file contains network checksum routines that are better करोne
 * in an architecture-specअगरic manner due to speed.
 */
 
#समावेश <linux/compiler.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/checksum.h>

अटल अंतरभूत अचिन्हित लघु from32to16(अचिन्हित a) 
अणु
	अचिन्हित लघु b = a >> 16; 
	यंत्र("addw %w2,%w0\n\t"
	    "adcw $0,%w0\n" 
	    : "=r" (b)
	    : "0" (b), "r" (a));
	वापस b;
पूर्ण

/*
 * Do a 64-bit checksum on an arbitrary memory area.
 * Returns a 32bit checksum.
 *
 * This isn't as समय critical as it used to be because many NICs
 * करो hardware checksumming these days.
 * 
 * Things tried and found to not make it faster:
 * Manual Prefetching
 * Unrolling to an 128 bytes inner loop.
 * Using पूर्णांकerleaving with more रेजिस्टरs to अवरोध the carry chains.
 */
अटल अचिन्हित करो_csum(स्थिर अचिन्हित अक्षर *buff, अचिन्हित len)
अणु
	अचिन्हित odd, count;
	अचिन्हित दीर्घ result = 0;

	अगर (unlikely(len == 0))
		वापस result; 
	odd = 1 & (अचिन्हित दीर्घ) buff;
	अगर (unlikely(odd)) अणु
		result = *buff << 8;
		len--;
		buff++;
	पूर्ण
	count = len >> 1;		/* nr of 16-bit words.. */
	अगर (count) अणु
		अगर (2 & (अचिन्हित दीर्घ) buff) अणु
			result += *(अचिन्हित लघु *)buff;
			count--;
			len -= 2;
			buff += 2;
		पूर्ण
		count >>= 1;		/* nr of 32-bit words.. */
		अगर (count) अणु
			अचिन्हित दीर्घ zero;
			अचिन्हित count64;
			अगर (4 & (अचिन्हित दीर्घ) buff) अणु
				result += *(अचिन्हित पूर्णांक *) buff;
				count--;
				len -= 4;
				buff += 4;
			पूर्ण
			count >>= 1;	/* nr of 64-bit words.. */

			/* मुख्य loop using 64byte blocks */
			zero = 0;
			count64 = count >> 3;
			जबतक (count64) अणु 
				यंत्र("addq 0*8(%[src]),%[res]\n\t"
				    "adcq 1*8(%[src]),%[res]\n\t"
				    "adcq 2*8(%[src]),%[res]\n\t"
				    "adcq 3*8(%[src]),%[res]\n\t"
				    "adcq 4*8(%[src]),%[res]\n\t"
				    "adcq 5*8(%[src]),%[res]\n\t"
				    "adcq 6*8(%[src]),%[res]\n\t"
				    "adcq 7*8(%[src]),%[res]\n\t"
				    "adcq %[zero],%[res]"
				    : [res] "=r" (result)
				    : [src] "r" (buff), [zero] "r" (zero),
				    "[res]" (result));
				buff += 64;
				count64--;
			पूर्ण

			/* last up to 7 8byte blocks */
			count %= 8; 
			जबतक (count) अणु 
				यंत्र("addq %1,%0\n\t"
				    "adcq %2,%0\n" 
					    : "=r" (result)
				    : "m" (*(अचिन्हित दीर्घ *)buff), 
				    "r" (zero),  "0" (result));
				--count; 
				buff += 8;
			पूर्ण
			result = add32_with_carry(result>>32,
						  result&0xffffffff); 

			अगर (len & 4) अणु
				result += *(अचिन्हित पूर्णांक *) buff;
				buff += 4;
			पूर्ण
		पूर्ण
		अगर (len & 2) अणु
			result += *(अचिन्हित लघु *) buff;
			buff += 2;
		पूर्ण
	पूर्ण
	अगर (len & 1)
		result += *buff;
	result = add32_with_carry(result>>32, result & 0xffffffff); 
	अगर (unlikely(odd)) अणु 
		result = from32to16(result);
		result = ((result >> 8) & 0xff) | ((result & 0xff) << 8);
	पूर्ण
	वापस result;
पूर्ण

/*
 * computes the checksum of a memory block at buff, length len,
 * and adds in "sum" (32-bit)
 *
 * वापसs a 32-bit number suitable क्रम feeding पूर्णांकo itself
 * or csum_tcpudp_magic
 *
 * this function must be called with even lengths, except
 * क्रम the last fragment, which may be odd
 *
 * it's best to have buff aligned on a 64-bit boundary
 */
__wsum csum_partial(स्थिर व्योम *buff, पूर्णांक len, __wsum sum)
अणु
	वापस (__क्रमce __wsum)add32_with_carry(करो_csum(buff, len),
						(__क्रमce u32)sum);
पूर्ण
EXPORT_SYMBOL(csum_partial);

/*
 * this routine is used क्रम miscellaneous IP-like checksums, मुख्यly
 * in icmp.c
 */
__sum16 ip_compute_csum(स्थिर व्योम *buff, पूर्णांक len)
अणु
	वापस csum_fold(csum_partial(buff,len,0));
पूर्ण
EXPORT_SYMBOL(ip_compute_csum);

