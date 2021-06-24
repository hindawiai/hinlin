<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2016 ARM Ltd.
 */
#अगर_अघोषित __ASM_CHECKSUM_H
#घोषणा __ASM_CHECKSUM_H

#समावेश <linux/in6.h>

#घोषणा _HAVE_ARCH_IPV6_CSUM
__sum16 csum_ipv6_magic(स्थिर काष्ठा in6_addr *saddr,
			स्थिर काष्ठा in6_addr *daddr,
			__u32 len, __u8 proto, __wsum sum);

अटल अंतरभूत __sum16 csum_fold(__wsum csum)
अणु
	u32 sum = (__क्रमce u32)csum;
	sum += (sum >> 16) | (sum << 16);
	वापस ~(__क्रमce __sum16)(sum >> 16);
पूर्ण
#घोषणा csum_fold csum_fold

अटल अंतरभूत __sum16 ip_fast_csum(स्थिर व्योम *iph, अचिन्हित पूर्णांक ihl)
अणु
	__uपूर्णांक128_t पंचांगp;
	u64 sum;
	पूर्णांक n = ihl; /* we want it चिन्हित */

	पंचांगp = *(स्थिर __uपूर्णांक128_t *)iph;
	iph += 16;
	n -= 4;
	पंचांगp += ((पंचांगp >> 64) | (पंचांगp << 64));
	sum = पंचांगp >> 64;
	करो अणु
		sum += *(स्थिर u32 *)iph;
		iph += 4;
	पूर्ण जबतक (--n > 0);

	sum += ((sum >> 32) | (sum << 32));
	वापस csum_fold((__क्रमce __wsum)(sum >> 32));
पूर्ण
#घोषणा ip_fast_csum ip_fast_csum

बाह्य अचिन्हित पूर्णांक करो_csum(स्थिर अचिन्हित अक्षर *buff, पूर्णांक len);
#घोषणा करो_csum करो_csum

#समावेश <यंत्र-generic/checksum.h>

#पूर्ण_अगर	/* __ASM_CHECKSUM_H */
