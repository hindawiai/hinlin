<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright (C) 2019-2020 Arm Ltd.

#समावेश <linux/compiler.h>
#समावेश <linux/kasan-checks.h>
#समावेश <linux/kernel.h>

#समावेश <net/checksum.h>

/* Looks dumb, but generates nice-ish code */
अटल u64 accumulate(u64 sum, u64 data)
अणु
	__uपूर्णांक128_t पंचांगp = (__uपूर्णांक128_t)sum + data;
	वापस पंचांगp + (पंचांगp >> 64);
पूर्ण

/*
 * We over-पढ़ो the buffer and this makes KASAN unhappy. Instead, disable
 * instrumentation and call kasan explicitly.
 */
अचिन्हित पूर्णांक __no_sanitize_address करो_csum(स्थिर अचिन्हित अक्षर *buff, पूर्णांक len)
अणु
	अचिन्हित पूर्णांक offset, shअगरt, sum;
	स्थिर u64 *ptr;
	u64 data, sum64 = 0;

	अगर (unlikely(len == 0))
		वापस 0;

	offset = (अचिन्हित दीर्घ)buff & 7;
	/*
	 * This is to all पूर्णांकents and purposes safe, since rounding करोwn cannot
	 * result in a dअगरferent page or cache line being accessed, and @buff
	 * should असलolutely not be poपूर्णांकing to anything पढ़ो-sensitive. We करो,
	 * however, have to be careful not to piss off KASAN, which means using
	 * unchecked पढ़ोs to accommodate the head and tail, क्रम which we'll
	 * compensate with an explicit check up-front.
	 */
	kasan_check_पढ़ो(buff, len);
	ptr = (u64 *)(buff - offset);
	len = len + offset - 8;

	/*
	 * Head: zero out any excess leading bytes. Shअगरting back by the same
	 * amount should be at least as fast as any other way of handling the
	 * odd/even alignment, and means we can ignore it until the very end.
	 */
	shअगरt = offset * 8;
	data = *ptr++;
#अगर_घोषित __LITTLE_ENDIAN
	data = (data >> shअगरt) << shअगरt;
#अन्यथा
	data = (data << shअगरt) >> shअगरt;
#पूर्ण_अगर

	/*
	 * Body: straightक्रमward aligned loads from here on (the paired loads
	 * underlying the quadword type still only need dword alignment). The
	 * मुख्य loop strictly excludes the tail, so the second loop will always
	 * run at least once.
	 */
	जबतक (unlikely(len > 64)) अणु
		__uपूर्णांक128_t पंचांगp1, पंचांगp2, पंचांगp3, पंचांगp4;

		पंचांगp1 = *(__uपूर्णांक128_t *)ptr;
		पंचांगp2 = *(__uपूर्णांक128_t *)(ptr + 2);
		पंचांगp3 = *(__uपूर्णांक128_t *)(ptr + 4);
		पंचांगp4 = *(__uपूर्णांक128_t *)(ptr + 6);

		len -= 64;
		ptr += 8;

		/* This is the "don't dump the carry flag into a GPR" idiom */
		पंचांगp1 += (पंचांगp1 >> 64) | (पंचांगp1 << 64);
		पंचांगp2 += (पंचांगp2 >> 64) | (पंचांगp2 << 64);
		पंचांगp3 += (पंचांगp3 >> 64) | (पंचांगp3 << 64);
		पंचांगp4 += (पंचांगp4 >> 64) | (पंचांगp4 << 64);
		पंचांगp1 = ((पंचांगp1 >> 64) << 64) | (पंचांगp2 >> 64);
		पंचांगp1 += (पंचांगp1 >> 64) | (पंचांगp1 << 64);
		पंचांगp3 = ((पंचांगp3 >> 64) << 64) | (पंचांगp4 >> 64);
		पंचांगp3 += (पंचांगp3 >> 64) | (पंचांगp3 << 64);
		पंचांगp1 = ((पंचांगp1 >> 64) << 64) | (पंचांगp3 >> 64);
		पंचांगp1 += (पंचांगp1 >> 64) | (पंचांगp1 << 64);
		पंचांगp1 = ((पंचांगp1 >> 64) << 64) | sum64;
		पंचांगp1 += (पंचांगp1 >> 64) | (पंचांगp1 << 64);
		sum64 = पंचांगp1 >> 64;
	पूर्ण
	जबतक (len > 8) अणु
		__uपूर्णांक128_t पंचांगp;

		sum64 = accumulate(sum64, data);
		पंचांगp = *(__uपूर्णांक128_t *)ptr;

		len -= 16;
		ptr += 2;

#अगर_घोषित __LITTLE_ENDIAN
		data = पंचांगp >> 64;
		sum64 = accumulate(sum64, पंचांगp);
#अन्यथा
		data = पंचांगp;
		sum64 = accumulate(sum64, पंचांगp >> 64);
#पूर्ण_अगर
	पूर्ण
	अगर (len > 0) अणु
		sum64 = accumulate(sum64, data);
		data = *ptr;
		len -= 8;
	पूर्ण
	/*
	 * Tail: zero any over-पढ़ो bytes similarly to the head, again
	 * preserving odd/even alignment.
	 */
	shअगरt = len * -8;
#अगर_घोषित __LITTLE_ENDIAN
	data = (data << shअगरt) >> shअगरt;
#अन्यथा
	data = (data >> shअगरt) << shअगरt;
#पूर्ण_अगर
	sum64 = accumulate(sum64, data);

	/* Finally, folding */
	sum64 += (sum64 >> 32) | (sum64 << 32);
	sum = sum64 >> 32;
	sum += (sum >> 16) | (sum << 16);
	अगर (offset & 1)
		वापस (u16)swab32(sum);

	वापस sum >> 16;
पूर्ण

__sum16 csum_ipv6_magic(स्थिर काष्ठा in6_addr *saddr,
			स्थिर काष्ठा in6_addr *daddr,
			__u32 len, __u8 proto, __wsum csum)
अणु
	__uपूर्णांक128_t src, dst;
	u64 sum = (__क्रमce u64)csum;

	src = *(स्थिर __uपूर्णांक128_t *)saddr->s6_addr;
	dst = *(स्थिर __uपूर्णांक128_t *)daddr->s6_addr;

	sum += (__क्रमce u32)htonl(len);
#अगर_घोषित __LITTLE_ENDIAN
	sum += (u32)proto << 24;
#अन्यथा
	sum += proto;
#पूर्ण_अगर
	src += (src >> 64) | (src << 64);
	dst += (dst >> 64) | (dst << 64);

	sum = accumulate(sum, src >> 64);
	sum = accumulate(sum, dst >> 64);

	sum += ((sum >> 32) | (sum << 32));
	वापस csum_fold((__क्रमce __wsum)(sum >> 32));
पूर्ण
EXPORT_SYMBOL(csum_ipv6_magic);
