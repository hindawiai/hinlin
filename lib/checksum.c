<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		IP/TCP/UDP checksumming routines
 *
 * Authors:	Jorge Cwik, <jorge@laser.satlink.net>
 *		Arnt Gulbअक्रमsen, <agulbra@nvg.unit.no>
 *		Tom May, <ftom@netcom.com>
 *		Andreas Schwab, <schwab@issan.inक्रमmatik.uni-करोrपंचांगund.de>
 *		Lots of code moved from tcp.c and ip.c; see those files
 *		क्रम more names.
 *
 * 03/02/96	Jes Sorensen, Andreas Schwab, Roman Hodek:
 *		Fixed some nasty bugs, causing some horrible crashes.
 *		A: At some poपूर्णांकs, the sum (%0) was used as
 *		length-counter instead of the length counter
 *		(%1). Thanks to Roman Hodek क्रम poपूर्णांकing this out.
 *		B: GCC seems to mess up अगर one uses too many
 *		data-रेजिस्टरs to hold input values and one tries to
 *		specअगरy d0 and d1 as scratch रेजिस्टरs. Letting gcc
 *		choose these रेजिस्टरs itself solves the problem.
 */

/* Revised by Kenneth Albanowski क्रम m68knommu. Basic problem: unaligned access
 समाप्तs, so most of the assembly has to go. */

#समावेश <linux/export.h>
#समावेश <net/checksum.h>

#समावेश <यंत्र/byteorder.h>

#अगर_अघोषित करो_csum
अटल अंतरभूत अचिन्हित लघु from32to16(अचिन्हित पूर्णांक x)
अणु
	/* add up 16-bit and 16-bit क्रम 16+c bit */
	x = (x & 0xffff) + (x >> 16);
	/* add up carry.. */
	x = (x & 0xffff) + (x >> 16);
	वापस x;
पूर्ण

अटल अचिन्हित पूर्णांक करो_csum(स्थिर अचिन्हित अक्षर *buff, पूर्णांक len)
अणु
	पूर्णांक odd;
	अचिन्हित पूर्णांक result = 0;

	अगर (len <= 0)
		जाओ out;
	odd = 1 & (अचिन्हित दीर्घ) buff;
	अगर (odd) अणु
#अगर_घोषित __LITTLE_ENDIAN
		result += (*buff << 8);
#अन्यथा
		result = *buff;
#पूर्ण_अगर
		len--;
		buff++;
	पूर्ण
	अगर (len >= 2) अणु
		अगर (2 & (अचिन्हित दीर्घ) buff) अणु
			result += *(अचिन्हित लघु *) buff;
			len -= 2;
			buff += 2;
		पूर्ण
		अगर (len >= 4) अणु
			स्थिर अचिन्हित अक्षर *end = buff + ((अचिन्हित)len & ~3);
			अचिन्हित पूर्णांक carry = 0;
			करो अणु
				अचिन्हित पूर्णांक w = *(अचिन्हित पूर्णांक *) buff;
				buff += 4;
				result += carry;
				result += w;
				carry = (w > result);
			पूर्ण जबतक (buff < end);
			result += carry;
			result = (result & 0xffff) + (result >> 16);
		पूर्ण
		अगर (len & 2) अणु
			result += *(अचिन्हित लघु *) buff;
			buff += 2;
		पूर्ण
	पूर्ण
	अगर (len & 1)
#अगर_घोषित __LITTLE_ENDIAN
		result += *buff;
#अन्यथा
		result += (*buff << 8);
#पूर्ण_अगर
	result = from32to16(result);
	अगर (odd)
		result = ((result >> 8) & 0xff) | ((result & 0xff) << 8);
out:
	वापस result;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित ip_fast_csum
/*
 *	This is a version of ip_compute_csum() optimized क्रम IP headers,
 *	which always checksum on 4 octet boundaries.
 */
__sum16 ip_fast_csum(स्थिर व्योम *iph, अचिन्हित पूर्णांक ihl)
अणु
	वापस (__क्रमce __sum16)~करो_csum(iph, ihl*4);
पूर्ण
EXPORT_SYMBOL(ip_fast_csum);
#पूर्ण_अगर

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
 * it's best to have buff aligned on a 32-bit boundary
 */
__wsum csum_partial(स्थिर व्योम *buff, पूर्णांक len, __wsum wsum)
अणु
	अचिन्हित पूर्णांक sum = (__क्रमce अचिन्हित पूर्णांक)wsum;
	अचिन्हित पूर्णांक result = करो_csum(buff, len);

	/* add in old sum, and carry.. */
	result += sum;
	अगर (sum > result)
		result += 1;
	वापस (__क्रमce __wsum)result;
पूर्ण
EXPORT_SYMBOL(csum_partial);

/*
 * this routine is used क्रम miscellaneous IP-like checksums, मुख्यly
 * in icmp.c
 */
__sum16 ip_compute_csum(स्थिर व्योम *buff, पूर्णांक len)
अणु
	वापस (__क्रमce __sum16)~करो_csum(buff, len);
पूर्ण
EXPORT_SYMBOL(ip_compute_csum);

#अगर_अघोषित csum_tcpudp_nofold
अटल अंतरभूत u32 from64to32(u64 x)
अणु
	/* add up 32-bit and 32-bit क्रम 32+c bit */
	x = (x & 0xffffffff) + (x >> 32);
	/* add up carry.. */
	x = (x & 0xffffffff) + (x >> 32);
	वापस (u32)x;
पूर्ण

__wsum csum_tcpudp_nofold(__be32 saddr, __be32 daddr,
			  __u32 len, __u8 proto, __wsum sum)
अणु
	अचिन्हित दीर्घ दीर्घ s = (__क्रमce u32)sum;

	s += (__क्रमce u32)saddr;
	s += (__क्रमce u32)daddr;
#अगर_घोषित __BIG_ENDIAN
	s += proto + len;
#अन्यथा
	s += (proto + len) << 8;
#पूर्ण_अगर
	वापस (__क्रमce __wsum)from64to32(s);
पूर्ण
EXPORT_SYMBOL(csum_tcpudp_nofold);
#पूर्ण_अगर
