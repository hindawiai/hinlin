<शैली गुरु>
/*
 * Licensed under the GPL
 */

#अगर_अघोषित __UM_SYSDEP_CHECKSUM_H
#घोषणा __UM_SYSDEP_CHECKSUM_H

अटल अंतरभूत __sum16 ip_compute_csum(स्थिर व्योम *buff, पूर्णांक len)
अणु
    वापस csum_fold (csum_partial(buff, len, 0));
पूर्ण

#घोषणा _HAVE_ARCH_IPV6_CSUM
अटल __अंतरभूत__ __sum16 csum_ipv6_magic(स्थिर काष्ठा in6_addr *saddr,
					  स्थिर काष्ठा in6_addr *daddr,
					  __u32 len, __u8 proto,
					  __wsum sum)
अणु
	__यंत्र__(
		"addl 0(%1), %0		;\n"
		"adcl 4(%1), %0		;\n"
		"adcl 8(%1), %0		;\n"
		"adcl 12(%1), %0	;\n"
		"adcl 0(%2), %0		;\n"
		"adcl 4(%2), %0		;\n"
		"adcl 8(%2), %0		;\n"
		"adcl 12(%2), %0	;\n"
		"adcl %3, %0		;\n"
		"adcl %4, %0		;\n"
		"adcl $0, %0		;\n"
		: "=&r" (sum)
		: "r" (saddr), "r" (daddr),
		  "r"(htonl(len)), "r"(htonl(proto)), "0"(sum));

	वापस csum_fold(sum);
पूर्ण

#पूर्ण_अगर
