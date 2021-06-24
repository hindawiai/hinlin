<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2002, 2003 Andi Kleen, SuSE Lअसल.
 *
 * Wrappers of assembly checksum functions क्रम x86-64.
 */
#समावेश <यंत्र/checksum.h>
#समावेश <linux/export.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/smap.h>

/**
 * csum_and_copy_from_user - Copy and checksum from user space.
 * @src: source address (user space)
 * @dst: destination address
 * @len: number of bytes to be copied.
 * @isum: initial sum that is added पूर्णांकo the result (32bit unfolded)
 * @errp: set to -EFAULT क्रम an bad source address.
 *
 * Returns an 32bit unfolded checksum of the buffer.
 * src and dst are best aligned to 64bits.
 */
__wsum
csum_and_copy_from_user(स्थिर व्योम __user *src, व्योम *dst, पूर्णांक len)
अणु
	__wsum sum;

	might_sleep();
	अगर (!user_access_begin(src, len))
		वापस 0;
	sum = csum_partial_copy_generic((__क्रमce स्थिर व्योम *)src, dst, len);
	user_access_end();
	वापस sum;
पूर्ण
EXPORT_SYMBOL(csum_and_copy_from_user);

/**
 * csum_and_copy_to_user - Copy and checksum to user space.
 * @src: source address
 * @dst: destination address (user space)
 * @len: number of bytes to be copied.
 * @isum: initial sum that is added पूर्णांकo the result (32bit unfolded)
 * @errp: set to -EFAULT क्रम an bad destination address.
 *
 * Returns an 32bit unfolded checksum of the buffer.
 * src and dst are best aligned to 64bits.
 */
__wsum
csum_and_copy_to_user(स्थिर व्योम *src, व्योम __user *dst, पूर्णांक len)
अणु
	__wsum sum;

	might_sleep();
	अगर (!user_access_begin(dst, len))
		वापस 0;
	sum = csum_partial_copy_generic(src, (व्योम __क्रमce *)dst, len);
	user_access_end();
	वापस sum;
पूर्ण
EXPORT_SYMBOL(csum_and_copy_to_user);

/**
 * csum_partial_copy_nocheck - Copy and checksum.
 * @src: source address
 * @dst: destination address
 * @len: number of bytes to be copied.
 * @sum: initial sum that is added पूर्णांकo the result (32bit unfolded)
 *
 * Returns an 32bit unfolded checksum of the buffer.
 */
__wsum
csum_partial_copy_nocheck(स्थिर व्योम *src, व्योम *dst, पूर्णांक len)
अणु
	वापस csum_partial_copy_generic(src, dst, len);
पूर्ण
EXPORT_SYMBOL(csum_partial_copy_nocheck);

__sum16 csum_ipv6_magic(स्थिर काष्ठा in6_addr *saddr,
			स्थिर काष्ठा in6_addr *daddr,
			__u32 len, __u8 proto, __wsum sum)
अणु
	__u64 rest, sum64;

	rest = (__क्रमce __u64)htonl(len) + (__क्रमce __u64)htons(proto) +
		(__क्रमce __u64)sum;

	यंत्र("	addq (%[saddr]),%[sum]\n"
	    "	adcq 8(%[saddr]),%[sum]\n"
	    "	adcq (%[daddr]),%[sum]\n"
	    "	adcq 8(%[daddr]),%[sum]\n"
	    "	adcq $0,%[sum]\n"

	    : [sum] "=r" (sum64)
	    : "[sum]" (rest), [saddr] "r" (saddr), [daddr] "r" (daddr));

	वापस csum_fold(
	       (__क्रमce __wsum)add32_with_carry(sum64 & 0xffffffff, sum64>>32));
पूर्ण
EXPORT_SYMBOL(csum_ipv6_magic);
