<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _ASM_POWERPC_CHECKSUM_H
#घोषणा _ASM_POWERPC_CHECKSUM_H
#अगर_घोषित __KERNEL__

/*
 */

#समावेश <linux/bitops.h>
#समावेश <linux/in6.h>
/*
 * Computes the checksum of a memory block at src, length len,
 * and adds in "sum" (32-bit), जबतक copying the block to dst.
 * If an access exception occurs on src or dst, it stores -EFAULT
 * to *src_err or *dst_err respectively (अगर that poपूर्णांकer is not
 * शून्य), and, क्रम an error on src, zeroes the rest of dst.
 *
 * Like csum_partial, this must be called with even lengths,
 * except क्रम the last fragment.
 */
बाह्य __wsum csum_partial_copy_generic(स्थिर व्योम *src, व्योम *dst, पूर्णांक len);

#घोषणा _HAVE_ARCH_COPY_AND_CSUM_FROM_USER
बाह्य __wsum csum_and_copy_from_user(स्थिर व्योम __user *src, व्योम *dst,
				      पूर्णांक len);
#घोषणा HAVE_CSUM_COPY_USER
बाह्य __wsum csum_and_copy_to_user(स्थिर व्योम *src, व्योम __user *dst,
				    पूर्णांक len);

#घोषणा _HAVE_ARCH_CSUM_AND_COPY
#घोषणा csum_partial_copy_nocheck(src, dst, len)   \
        csum_partial_copy_generic((src), (dst), (len))


/*
 * turns a 32-bit partial checksum (e.g. from csum_partial) पूर्णांकo a
 * 1's complement 16-bit checksum.
 */
अटल अंतरभूत __sum16 csum_fold(__wsum sum)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	/* swap the two 16-bit halves of sum */
	__यंत्र__("rlwinm %0,%1,16,0,31" : "=r" (पंचांगp) : "r" (sum));
	/* अगर there is a carry from adding the two 16-bit halves,
	   it will carry from the lower half पूर्णांकo the upper half,
	   giving us the correct sum in the upper half. */
	वापस (__क्रमce __sum16)(~((__क्रमce u32)sum + पंचांगp) >> 16);
पूर्ण

अटल अंतरभूत u32 from64to32(u64 x)
अणु
	वापस (x + ror64(x, 32)) >> 32;
पूर्ण

अटल अंतरभूत __wsum csum_tcpudp_nofold(__be32 saddr, __be32 daddr, __u32 len,
					__u8 proto, __wsum sum)
अणु
#अगर_घोषित __घातerpc64__
	u64 s = (__क्रमce u32)sum;

	s += (__क्रमce u32)saddr;
	s += (__क्रमce u32)daddr;
#अगर_घोषित __BIG_ENDIAN__
	s += proto + len;
#अन्यथा
	s += (proto + len) << 8;
#पूर्ण_अगर
	वापस (__क्रमce __wsum) from64to32(s);
#अन्यथा
    __यंत्र__("\न\
	addc %0,%0,%1 \न\
	adde %0,%0,%2 \न\
	adde %0,%0,%3 \न\
	addze %0,%0 \न\
	"
	: "=r" (sum)
	: "r" (daddr), "r"(saddr), "r"(proto + len), "0"(sum));
	वापस sum;
#पूर्ण_अगर
पूर्ण

/*
 * computes the checksum of the TCP/UDP pseuकरो-header
 * वापसs a 16-bit checksum, alपढ़ोy complemented
 */
अटल अंतरभूत __sum16 csum_tcpudp_magic(__be32 saddr, __be32 daddr, __u32 len,
					__u8 proto, __wsum sum)
अणु
	वापस csum_fold(csum_tcpudp_nofold(saddr, daddr, len, proto, sum));
पूर्ण

#घोषणा HAVE_ARCH_CSUM_ADD
अटल अंतरभूत __wsum csum_add(__wsum csum, __wsum addend)
अणु
#अगर_घोषित __घातerpc64__
	u64 res = (__क्रमce u64)csum;
#पूर्ण_अगर
	अगर (__builtin_स्थिरant_p(csum) && csum == 0)
		वापस addend;
	अगर (__builtin_स्थिरant_p(addend) && addend == 0)
		वापस csum;

#अगर_घोषित __घातerpc64__
	res += (__क्रमce u64)addend;
	वापस (__क्रमce __wsum)((u32)res + (res >> 32));
#अन्यथा
	यंत्र("addc %0,%0,%1;"
	    "addze %0,%0;"
	    : "+r" (csum) : "r" (addend) : "xer");
	वापस csum;
#पूर्ण_अगर
पूर्ण

/*
 * This is a version of ip_compute_csum() optimized क्रम IP headers,
 * which always checksum on 4 octet boundaries.  ihl is the number
 * of 32-bit words and is always >= 5.
 */
अटल अंतरभूत __wsum ip_fast_csum_nofold(स्थिर व्योम *iph, अचिन्हित पूर्णांक ihl)
अणु
	स्थिर u32 *ptr = (स्थिर u32 *)iph + 1;
#अगर_घोषित __घातerpc64__
	अचिन्हित पूर्णांक i;
	u64 s = *(स्थिर u32 *)iph;

	क्रम (i = 0; i < ihl - 1; i++, ptr++)
		s += *ptr;
	वापस (__क्रमce __wsum)from64to32(s);
#अन्यथा
	__wsum sum, पंचांगp;

	यंत्र("mtctr %3;"
	    "addc %0,%4,%5;"
	    "1: lwzu %1, 4(%2);"
	    "adde %0,%0,%1;"
	    "bdnz 1b;"
	    "addze %0,%0;"
	    : "=r" (sum), "=r" (पंचांगp), "+b" (ptr)
	    : "r" (ihl - 2), "r" (*(स्थिर u32 *)iph), "r" (*ptr)
	    : "ctr", "xer", "memory");

	वापस sum;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत __sum16 ip_fast_csum(स्थिर व्योम *iph, अचिन्हित पूर्णांक ihl)
अणु
	वापस csum_fold(ip_fast_csum_nofold(iph, ihl));
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
 * it's best to have buff aligned on a 32-bit boundary
 */
__wsum __csum_partial(स्थिर व्योम *buff, पूर्णांक len, __wsum sum);

अटल __always_अंतरभूत __wsum csum_partial(स्थिर व्योम *buff, पूर्णांक len, __wsum sum)
अणु
	अगर (__builtin_स्थिरant_p(len) && len <= 16 && (len & 1) == 0) अणु
		अगर (len == 2)
			sum = csum_add(sum, (__क्रमce __wsum)*(स्थिर u16 *)buff);
		अगर (len >= 4)
			sum = csum_add(sum, (__क्रमce __wsum)*(स्थिर u32 *)buff);
		अगर (len == 6)
			sum = csum_add(sum, (__क्रमce __wsum)
					    *(स्थिर u16 *)(buff + 4));
		अगर (len >= 8)
			sum = csum_add(sum, (__क्रमce __wsum)
					    *(स्थिर u32 *)(buff + 4));
		अगर (len == 10)
			sum = csum_add(sum, (__क्रमce __wsum)
					    *(स्थिर u16 *)(buff + 8));
		अगर (len >= 12)
			sum = csum_add(sum, (__क्रमce __wsum)
					    *(स्थिर u32 *)(buff + 8));
		अगर (len == 14)
			sum = csum_add(sum, (__क्रमce __wsum)
					    *(स्थिर u16 *)(buff + 12));
		अगर (len >= 16)
			sum = csum_add(sum, (__क्रमce __wsum)
					    *(स्थिर u32 *)(buff + 12));
	पूर्ण अन्यथा अगर (__builtin_स्थिरant_p(len) && (len & 3) == 0) अणु
		sum = csum_add(sum, ip_fast_csum_nofold(buff, len >> 2));
	पूर्ण अन्यथा अणु
		sum = __csum_partial(buff, len, sum);
	पूर्ण
	वापस sum;
पूर्ण

/*
 * this routine is used क्रम miscellaneous IP-like checksums, मुख्यly
 * in icmp.c
 */
अटल अंतरभूत __sum16 ip_compute_csum(स्थिर व्योम *buff, पूर्णांक len)
अणु
	वापस csum_fold(csum_partial(buff, len, 0));
पूर्ण

#घोषणा _HAVE_ARCH_IPV6_CSUM
__sum16 csum_ipv6_magic(स्थिर काष्ठा in6_addr *saddr,
			स्थिर काष्ठा in6_addr *daddr,
			__u32 len, __u8 proto, __wsum sum);

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर
