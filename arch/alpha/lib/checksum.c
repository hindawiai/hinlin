<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/alpha/lib/checksum.c
 *
 * This file contains network checksum routines that are better करोne
 * in an architecture-specअगरic manner due to speed..
 * Comments in other versions indicate that the algorithms are from RFC1071
 *
 * accelerated versions (and 21264 assembly versions ) contributed by
 *	Rick Gorton	<rick.gorton@alpha-processor.com>
 */
 
#समावेश <linux/module.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/byteorder.h>

अटल अंतरभूत अचिन्हित लघु from64to16(अचिन्हित दीर्घ x)
अणु
	/* Using extract inकाष्ठाions is a bit more efficient
	   than the original shअगरt/biपंचांगask version.  */

	जोड़ अणु
		अचिन्हित दीर्घ	ul;
		अचिन्हित पूर्णांक	ui[2];
		अचिन्हित लघु	us[4];
	पूर्ण in_v, पंचांगp_v, out_v;

	in_v.ul = x;
	पंचांगp_v.ul = (अचिन्हित दीर्घ) in_v.ui[0] + (अचिन्हित दीर्घ) in_v.ui[1];

	/* Since the bits of पंचांगp_v.sh[3] are going to always be zero,
	   we करोn't have to bother to add that in.  */
	out_v.ul = (अचिन्हित दीर्घ) पंचांगp_v.us[0] + (अचिन्हित दीर्घ) पंचांगp_v.us[1]
			+ (अचिन्हित दीर्घ) पंचांगp_v.us[2];

	/* Similarly, out_v.us[2] is always zero क्रम the final add.  */
	वापस out_v.us[0] + out_v.us[1];
पूर्ण

/*
 * computes the checksum of the TCP/UDP pseuकरो-header
 * वापसs a 16-bit checksum, alपढ़ोy complemented.
 */
__sum16 csum_tcpudp_magic(__be32 saddr, __be32 daddr,
			  __u32 len, __u8 proto, __wsum sum)
अणु
	वापस (__क्रमce __sum16)~from64to16(
		(__क्रमce u64)saddr + (__क्रमce u64)daddr +
		(__क्रमce u64)sum + ((len + proto) << 8));
पूर्ण
EXPORT_SYMBOL(csum_tcpudp_magic);

__wsum csum_tcpudp_nofold(__be32 saddr, __be32 daddr,
			  __u32 len, __u8 proto, __wsum sum)
अणु
	अचिन्हित दीर्घ result;

	result = (__क्रमce u64)saddr + (__क्रमce u64)daddr +
		 (__क्रमce u64)sum + ((len + proto) << 8);

	/* Fold करोwn to 32-bits so we करोn't lose in the प्रकार-less 
	   network stack.  */
	/* 64 to 33 */
	result = (result & 0xffffffff) + (result >> 32);
	/* 33 to 32 */
	result = (result & 0xffffffff) + (result >> 32);
	वापस (__क्रमce __wsum)result;
पूर्ण
EXPORT_SYMBOL(csum_tcpudp_nofold);

/*
 * Do a 64-bit checksum on an arbitrary memory area..
 *
 * This isn't a great routine, but it's not _horrible_ either. The
 * inner loop could be unrolled a bit further, and there are better
 * ways to करो the carry, but this is reasonable.
 */
अटल अंतरभूत अचिन्हित दीर्घ करो_csum(स्थिर अचिन्हित अक्षर * buff, पूर्णांक len)
अणु
	पूर्णांक odd, count;
	अचिन्हित दीर्घ result = 0;

	अगर (len <= 0)
		जाओ out;
	odd = 1 & (अचिन्हित दीर्घ) buff;
	अगर (odd) अणु
		result = *buff << 8;
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
			अगर (4 & (अचिन्हित दीर्घ) buff) अणु
				result += *(अचिन्हित पूर्णांक *) buff;
				count--;
				len -= 4;
				buff += 4;
			पूर्ण
			count >>= 1;	/* nr of 64-bit words.. */
			अगर (count) अणु
				अचिन्हित दीर्घ carry = 0;
				करो अणु
					अचिन्हित दीर्घ w = *(अचिन्हित दीर्घ *) buff;
					count--;
					buff += 8;
					result += carry;
					result += w;
					carry = (w > result);
				पूर्ण जबतक (count);
				result += carry;
				result = (result & 0xffffffff) + (result >> 32);
			पूर्ण
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
	result = from64to16(result);
	अगर (odd)
		result = ((result >> 8) & 0xff) | ((result & 0xff) << 8);
out:
	वापस result;
पूर्ण

/*
 *	This is a version of ip_compute_csum() optimized क्रम IP headers,
 *	which always checksum on 4 octet boundaries.
 */
__sum16 ip_fast_csum(स्थिर व्योम *iph, अचिन्हित पूर्णांक ihl)
अणु
	वापस (__क्रमce __sum16)~करो_csum(iph,ihl*4);
पूर्ण
EXPORT_SYMBOL(ip_fast_csum);

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
__wsum csum_partial(स्थिर व्योम *buff, पूर्णांक len, __wsum sum)
अणु
	अचिन्हित दीर्घ result = करो_csum(buff, len);

	/* add in old sum, and carry.. */
	result += (__क्रमce u32)sum;
	/* 32+c bits -> 32 bits */
	result = (result & 0xffffffff) + (result >> 32);
	वापस (__क्रमce __wsum)result;
पूर्ण

EXPORT_SYMBOL(csum_partial);

/*
 * this routine is used क्रम miscellaneous IP-like checksums, मुख्यly
 * in icmp.c
 */
__sum16 ip_compute_csum(स्थिर व्योम *buff, पूर्णांक len)
अणु
	वापस (__क्रमce __sum16)~from64to16(करो_csum(buff,len));
पूर्ण
EXPORT_SYMBOL(ip_compute_csum);
