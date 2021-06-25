<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Checksumming functions क्रम IP, TCP, UDP and so on
 *
 * Authors:	Jorge Cwik, <jorge@laser.satlink.net>
 *		Arnt Gulbअक्रमsen, <agulbra@nvg.unit.no>
 *		Borrows very liberally from tcp.c and ip.c, see those
 *		files क्रम more names.
 */

#अगर_अघोषित _CHECKSUM_H
#घोषणा _CHECKSUM_H

#समावेश <linux/त्रुटिसं.स>
#समावेश <यंत्र/types.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/checksum.h>

#अगर_अघोषित _HAVE_ARCH_COPY_AND_CSUM_FROM_USER
अटल अंतरभूत
__wsum csum_and_copy_from_user (स्थिर व्योम __user *src, व्योम *dst,
				      पूर्णांक len)
अणु
	अगर (copy_from_user(dst, src, len))
		वापस 0;
	वापस csum_partial(dst, len, ~0U);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित HAVE_CSUM_COPY_USER
अटल __अंतरभूत__ __wsum csum_and_copy_to_user
(स्थिर व्योम *src, व्योम __user *dst, पूर्णांक len)
अणु
	__wsum sum = csum_partial(src, len, ~0U);

	अगर (copy_to_user(dst, src, len) == 0)
		वापस sum;
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित _HAVE_ARCH_CSUM_AND_COPY
अटल अंतरभूत __wsum
csum_partial_copy_nocheck(स्थिर व्योम *src, व्योम *dst, पूर्णांक len)
अणु
	स_नकल(dst, src, len);
	वापस csum_partial(dst, len, 0);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित HAVE_ARCH_CSUM_ADD
अटल अंतरभूत __wsum csum_add(__wsum csum, __wsum addend)
अणु
	u32 res = (__क्रमce u32)csum;
	res += (__क्रमce u32)addend;
	वापस (__क्रमce __wsum)(res + (res < (__क्रमce u32)addend));
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत __wsum csum_sub(__wsum csum, __wsum addend)
अणु
	वापस csum_add(csum, ~addend);
पूर्ण

अटल अंतरभूत __sum16 csum16_add(__sum16 csum, __be16 addend)
अणु
	u16 res = (__क्रमce u16)csum;

	res += (__क्रमce u16)addend;
	वापस (__क्रमce __sum16)(res + (res < (__क्रमce u16)addend));
पूर्ण

अटल अंतरभूत __sum16 csum16_sub(__sum16 csum, __be16 addend)
अणु
	वापस csum16_add(csum, ~addend);
पूर्ण

अटल अंतरभूत __wsum
csum_block_add(__wsum csum, __wsum csum2, पूर्णांक offset)
अणु
	u32 sum = (__क्रमce u32)csum2;

	/* rotate sum to align it with a 16b boundary */
	अगर (offset & 1)
		sum = ror32(sum, 8);

	वापस csum_add(csum, (__क्रमce __wsum)sum);
पूर्ण

अटल अंतरभूत __wsum
csum_block_add_ext(__wsum csum, __wsum csum2, पूर्णांक offset, पूर्णांक len)
अणु
	वापस csum_block_add(csum, csum2, offset);
पूर्ण

अटल अंतरभूत __wsum
csum_block_sub(__wsum csum, __wsum csum2, पूर्णांक offset)
अणु
	वापस csum_block_add(csum, ~csum2, offset);
पूर्ण

अटल अंतरभूत __wsum csum_unfold(__sum16 n)
अणु
	वापस (__क्रमce __wsum)n;
पूर्ण

अटल अंतरभूत __wsum csum_partial_ext(स्थिर व्योम *buff, पूर्णांक len, __wsum sum)
अणु
	वापस csum_partial(buff, len, sum);
पूर्ण

#घोषणा CSUM_MANGLED_0 ((__क्रमce __sum16)0xffff)

अटल अंतरभूत व्योम csum_replace_by_dअगरf(__sum16 *sum, __wsum dअगरf)
अणु
	*sum = csum_fold(csum_add(dअगरf, ~csum_unfold(*sum)));
पूर्ण

अटल अंतरभूत व्योम csum_replace4(__sum16 *sum, __be32 from, __be32 to)
अणु
	__wsum पंचांगp = csum_sub(~csum_unfold(*sum), (__क्रमce __wsum)from);

	*sum = csum_fold(csum_add(पंचांगp, (__क्रमce __wsum)to));
पूर्ण

/* Implements RFC 1624 (Incremental Internet Checksum)
 * 3. Discussion states :
 *     HC' = ~(~HC + ~m + m')
 *  m : old value of a 16bit field
 *  m' : new value of a 16bit field
 */
अटल अंतरभूत व्योम csum_replace2(__sum16 *sum, __be16 old, __be16 new)
अणु
	*sum = ~csum16_add(csum16_sub(~(*sum), old), new);
पूर्ण

काष्ठा sk_buff;
व्योम inet_proto_csum_replace4(__sum16 *sum, काष्ठा sk_buff *skb,
			      __be32 from, __be32 to, bool pseuकरोhdr);
व्योम inet_proto_csum_replace16(__sum16 *sum, काष्ठा sk_buff *skb,
			       स्थिर __be32 *from, स्थिर __be32 *to,
			       bool pseuकरोhdr);
व्योम inet_proto_csum_replace_by_dअगरf(__sum16 *sum, काष्ठा sk_buff *skb,
				     __wsum dअगरf, bool pseuकरोhdr);

अटल अंतरभूत व्योम inet_proto_csum_replace2(__sum16 *sum, काष्ठा sk_buff *skb,
					    __be16 from, __be16 to,
					    bool pseuकरोhdr)
अणु
	inet_proto_csum_replace4(sum, skb, (__क्रमce __be32)from,
				 (__क्रमce __be32)to, pseuकरोhdr);
पूर्ण

अटल अंतरभूत __wsum remcsum_adjust(व्योम *ptr, __wsum csum,
				    पूर्णांक start, पूर्णांक offset)
अणु
	__sum16 *psum = (__sum16 *)(ptr + offset);
	__wsum delta;

	/* Subtract out checksum up to start */
	csum = csum_sub(csum, csum_partial(ptr, start, 0));

	/* Set derived checksum in packet */
	delta = csum_sub((__क्रमce __wsum)csum_fold(csum),
			 (__क्रमce __wsum)*psum);
	*psum = csum_fold(csum);

	वापस delta;
पूर्ण

अटल अंतरभूत व्योम remcsum_unadjust(__sum16 *psum, __wsum delta)
अणु
	*psum = csum_fold(csum_sub(delta, (__क्रमce __wsum)*psum));
पूर्ण

#पूर्ण_अगर
