<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Network checksum routines
 *
 * Copyright (C) 1999, 2003 Hewlett-Packard Co
 *	Stephane Eranian <eranian@hpl.hp.com>
 *
 * Most of the code coming from arch/alpha/lib/checksum.c
 *
 * This file contains network checksum routines that are better करोne
 * in an architecture-specअगरic manner due to speed..
 */

#समावेश <linux/module.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/byteorder.h>

अटल अंतरभूत अचिन्हित लघु
from64to16 (अचिन्हित दीर्घ x)
अणु
	/* add up 32-bit words क्रम 33 bits */
	x = (x & 0xffffffff) + (x >> 32);
	/* add up 16-bit and 17-bit words क्रम 17+c bits */
	x = (x & 0xffff) + (x >> 16);
	/* add up 16-bit and 2-bit क्रम 16+c bit */
	x = (x & 0xffff) + (x >> 16);
	/* add up carry.. */
	x = (x & 0xffff) + (x >> 16);
	वापस x;
पूर्ण

/*
 * computes the checksum of the TCP/UDP pseuकरो-header
 * वापसs a 16-bit checksum, alपढ़ोy complemented.
 */
__sum16
csum_tcpudp_magic(__be32 saddr, __be32 daddr, __u32 len,
		  __u8 proto, __wsum sum)
अणु
	वापस (__क्रमce __sum16)~from64to16(
		(__क्रमce u64)saddr + (__क्रमce u64)daddr +
		(__क्रमce u64)sum + ((len + proto) << 8));
पूर्ण

EXPORT_SYMBOL(csum_tcpudp_magic);

__wsum
csum_tcpudp_nofold(__be32 saddr, __be32 daddr, __u32 len,
		   __u8 proto, __wsum sum)
अणु
	अचिन्हित दीर्घ result;

	result = (__क्रमce u64)saddr + (__क्रमce u64)daddr +
		 (__क्रमce u64)sum + ((len + proto) << 8);

	/* Fold करोwn to 32-bits so we करोn't lose in the प्रकार-less network stack.  */
	/* 64 to 33 */
	result = (result & 0xffffffff) + (result >> 32);
	/* 33 to 32 */
	result = (result & 0xffffffff) + (result >> 32);
	वापस (__क्रमce __wsum)result;
पूर्ण
EXPORT_SYMBOL(csum_tcpudp_nofold);

बाह्य अचिन्हित दीर्घ करो_csum (स्थिर अचिन्हित अक्षर *, दीर्घ);

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
	u64 result = करो_csum(buff, len);

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
__sum16 ip_compute_csum (स्थिर व्योम *buff, पूर्णांक len)
अणु
	वापस (__क्रमce __sum16)~करो_csum(buff,len);
पूर्ण

EXPORT_SYMBOL(ip_compute_csum);
