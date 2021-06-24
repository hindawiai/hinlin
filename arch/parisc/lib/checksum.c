<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		MIPS specअगरic IP/TCP/UDP checksumming routines
 *
 * Authors:	Ralf Baechle, <ralf@walकरोrf-gmbh.de>
 *		Lots of code moved from tcp.c and ip.c; see those files
 *		क्रम more names.
 */
#समावेश <linux/module.h>
#समावेश <linux/types.h>

#समावेश <net/checksum.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/माला.स>
#समावेश <linux/uaccess.h>

#घोषणा addc(_t,_r)                     \
	__यंत्र__ __अस्थिर__ (          \
"       add             %0, %1, %0\n"   \
"       addc            %0, %%r0, %0\n" \
	: "=r"(_t)                      \
	: "r"(_r), "0"(_t));

अटल अंतरभूत अचिन्हित लघु from32to16(अचिन्हित पूर्णांक x)
अणु
	/* 32 bits --> 16 bits + carry */
	x = (x & 0xffff) + (x >> 16);
	/* 16 bits + carry --> 16 bits including carry */
	x = (x & 0xffff) + (x >> 16);
	वापस (अचिन्हित लघु)x;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक करो_csum(स्थिर अचिन्हित अक्षर * buff, पूर्णांक len)
अणु
	पूर्णांक odd, count;
	अचिन्हित पूर्णांक result = 0;

	अगर (len <= 0)
		जाओ out;
	odd = 1 & (अचिन्हित दीर्घ) buff;
	अगर (odd) अणु
		result = be16_to_cpu(*buff);
		len--;
		buff++;
	पूर्ण
	count = len >> 1;		/* nr of 16-bit words.. */
	अगर (count) अणु
		अगर (2 & (अचिन्हित दीर्घ) buff) अणु
			result += *(अचिन्हित लघु *) buff;
			count--;
			len -= 2;
			buff += 2;
		पूर्ण
		count >>= 1;		/* nr of 32-bit words.. */
		अगर (count) अणु
			जबतक (count >= 4) अणु
				अचिन्हित पूर्णांक r1, r2, r3, r4;
				r1 = *(अचिन्हित पूर्णांक *)(buff + 0);
				r2 = *(अचिन्हित पूर्णांक *)(buff + 4);
				r3 = *(अचिन्हित पूर्णांक *)(buff + 8);
				r4 = *(अचिन्हित पूर्णांक *)(buff + 12);
				addc(result, r1);
				addc(result, r2);
				addc(result, r3);
				addc(result, r4);
				count -= 4;
				buff += 16;
			पूर्ण
			जबतक (count) अणु
				अचिन्हित पूर्णांक w = *(अचिन्हित पूर्णांक *) buff;
				count--;
				buff += 4;
				addc(result, w);
			पूर्ण
			result = (result & 0xffff) + (result >> 16);
		पूर्ण
		अगर (len & 2) अणु
			result += *(अचिन्हित लघु *) buff;
			buff += 2;
		पूर्ण
	पूर्ण
	अगर (len & 1)
		result += le16_to_cpu(*buff);
	result = from32to16(result);
	अगर (odd)
		result = swab16(result);
out:
	वापस result;
पूर्ण

/*
 * computes a partial checksum, e.g. क्रम TCP/UDP fragments
 */
/*
 * why bother folding?
 */
__wsum csum_partial(स्थिर व्योम *buff, पूर्णांक len, __wsum sum)
अणु
	अचिन्हित पूर्णांक result = करो_csum(buff, len);
	addc(result, sum);
	वापस (__क्रमce __wsum)from32to16(result);
पूर्ण

EXPORT_SYMBOL(csum_partial);
