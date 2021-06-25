<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * csum_partial_copy - करो IP checksumming and copy
 *
 * (C) Copyright 1996 Linus Torvalds
 * accelerated versions (and 21264 assembly versions ) contributed by
 *	Rick Gorton	<rick.gorton@alpha-processor.com>
 *
 * Don't look at this too closely - you'll go mad. The things
 * we करो क्रम perक्रमmance..
 */

#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/uaccess.h>
#समावेश <net/checksum.h>


#घोषणा ldq_u(x,y) \
__यंत्र__ __अस्थिर__("ldq_u %0,%1":"=r" (x):"m" (*(स्थिर अचिन्हित दीर्घ *)(y)))

#घोषणा stq_u(x,y) \
__यंत्र__ __अस्थिर__("stq_u %1,%0":"=m" (*(अचिन्हित दीर्घ *)(y)):"r" (x))

#घोषणा extql(x,y,z) \
__यंत्र__ __अस्थिर__("extql %1,%2,%0":"=r" (z):"r" (x),"r" (y))

#घोषणा extqh(x,y,z) \
__यंत्र__ __अस्थिर__("extqh %1,%2,%0":"=r" (z):"r" (x),"r" (y))

#घोषणा mskql(x,y,z) \
__यंत्र__ __अस्थिर__("mskql %1,%2,%0":"=r" (z):"r" (x),"r" (y))

#घोषणा mskqh(x,y,z) \
__यंत्र__ __अस्थिर__("mskqh %1,%2,%0":"=r" (z):"r" (x),"r" (y))

#घोषणा insql(x,y,z) \
__यंत्र__ __अस्थिर__("insql %1,%2,%0":"=r" (z):"r" (x),"r" (y))

#घोषणा insqh(x,y,z) \
__यंत्र__ __अस्थिर__("insqh %1,%2,%0":"=r" (z):"r" (x),"r" (y))

#घोषणा __get_word(insn,x,ptr)				\
(अणु							\
	दीर्घ __guu_err;					\
	__यंत्र__ __अस्थिर__(				\
	"1:	"#insn" %0,%2\n"			\
	"2:\n"						\
	EXC(1b,2b,%0,%1)				\
		: "=r"(x), "=r"(__guu_err)		\
		: "m"(__m(ptr)), "1"(0));		\
	__guu_err;					\
पूर्ण)

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
 * Ok. This isn't fun, but this is the EASY हाल.
 */
अटल अंतरभूत अचिन्हित दीर्घ
csum_partial_cfu_aligned(स्थिर अचिन्हित दीर्घ __user *src, अचिन्हित दीर्घ *dst,
			 दीर्घ len)
अणु
	अचिन्हित दीर्घ checksum = ~0U;
	अचिन्हित दीर्घ carry = 0;

	जबतक (len >= 0) अणु
		अचिन्हित दीर्घ word;
		अगर (__get_word(ldq, word, src))
			वापस 0;
		checksum += carry;
		src++;
		checksum += word;
		len -= 8;
		carry = checksum < word;
		*dst = word;
		dst++;
	पूर्ण
	len += 8;
	checksum += carry;
	अगर (len) अणु
		अचिन्हित दीर्घ word, पंचांगp;
		अगर (__get_word(ldq, word, src))
			वापस 0;
		पंचांगp = *dst;
		mskql(word, len, word);
		checksum += word;
		mskqh(पंचांगp, len, पंचांगp);
		carry = checksum < word;
		*dst = word | पंचांगp;
		checksum += carry;
	पूर्ण
	वापस checksum;
पूर्ण

/*
 * This is even less fun, but this is still reasonably
 * easy.
 */
अटल अंतरभूत अचिन्हित दीर्घ
csum_partial_cfu_dest_aligned(स्थिर अचिन्हित दीर्घ __user *src,
			      अचिन्हित दीर्घ *dst,
			      अचिन्हित दीर्घ soff,
			      दीर्घ len)
अणु
	अचिन्हित दीर्घ first;
	अचिन्हित दीर्घ word, carry;
	अचिन्हित दीर्घ lastsrc = 7+len+(अचिन्हित दीर्घ)src;
	अचिन्हित दीर्घ checksum = ~0U;

	अगर (__get_word(ldq_u, first,src))
		वापस 0;
	carry = 0;
	जबतक (len >= 0) अणु
		अचिन्हित दीर्घ second;

		अगर (__get_word(ldq_u, second, src+1))
			वापस 0;
		extql(first, soff, word);
		len -= 8;
		src++;
		extqh(second, soff, first);
		checksum += carry;
		word |= first;
		first = second;
		checksum += word;
		*dst = word;
		dst++;
		carry = checksum < word;
	पूर्ण
	len += 8;
	checksum += carry;
	अगर (len) अणु
		अचिन्हित दीर्घ पंचांगp;
		अचिन्हित दीर्घ second;
		अगर (__get_word(ldq_u, second, lastsrc))
			वापस 0;
		पंचांगp = *dst;
		extql(first, soff, word);
		extqh(second, soff, first);
		word |= first;
		mskql(word, len, word);
		checksum += word;
		mskqh(पंचांगp, len, पंचांगp);
		carry = checksum < word;
		*dst = word | पंचांगp;
		checksum += carry;
	पूर्ण
	वापस checksum;
पूर्ण

/*
 * This is slightly less fun than the above..
 */
अटल अंतरभूत अचिन्हित दीर्घ
csum_partial_cfu_src_aligned(स्थिर अचिन्हित दीर्घ __user *src,
			     अचिन्हित दीर्घ *dst,
			     अचिन्हित दीर्घ करोff,
			     दीर्घ len,
			     अचिन्हित दीर्घ partial_dest)
अणु
	अचिन्हित दीर्घ carry = 0;
	अचिन्हित दीर्घ word;
	अचिन्हित दीर्घ second_dest;
	अचिन्हित दीर्घ checksum = ~0U;

	mskql(partial_dest, करोff, partial_dest);
	जबतक (len >= 0) अणु
		अगर (__get_word(ldq, word, src))
			वापस 0;
		len -= 8;
		insql(word, करोff, second_dest);
		checksum += carry;
		stq_u(partial_dest | second_dest, dst);
		src++;
		checksum += word;
		insqh(word, करोff, partial_dest);
		carry = checksum < word;
		dst++;
	पूर्ण
	len += 8;
	अगर (len) अणु
		checksum += carry;
		अगर (__get_word(ldq, word, src))
			वापस 0;
		mskql(word, len, word);
		len -= 8;
		checksum += word;
		insql(word, करोff, second_dest);
		len += करोff;
		carry = checksum < word;
		partial_dest |= second_dest;
		अगर (len >= 0) अणु
			stq_u(partial_dest, dst);
			अगर (!len) जाओ out;
			dst++;
			insqh(word, करोff, partial_dest);
		पूर्ण
		करोff = len;
	पूर्ण
	ldq_u(second_dest, dst);
	mskqh(second_dest, करोff, second_dest);
	stq_u(partial_dest | second_dest, dst);
out:
	checksum += carry;
	वापस checksum;
पूर्ण

/*
 * This is so totally un-fun that it's frightening. Don't
 * look at this too बंदly, you'll go blind.
 */
अटल अंतरभूत अचिन्हित दीर्घ
csum_partial_cfu_unaligned(स्थिर अचिन्हित दीर्घ __user * src,
			   अचिन्हित दीर्घ * dst,
			   अचिन्हित दीर्घ soff, अचिन्हित दीर्घ करोff,
			   दीर्घ len, अचिन्हित दीर्घ partial_dest)
अणु
	अचिन्हित दीर्घ carry = 0;
	अचिन्हित दीर्घ first;
	अचिन्हित दीर्घ lastsrc;
	अचिन्हित दीर्घ checksum = ~0U;

	अगर (__get_word(ldq_u, first, src))
		वापस 0;
	lastsrc = 7+len+(अचिन्हित दीर्घ)src;
	mskql(partial_dest, करोff, partial_dest);
	जबतक (len >= 0) अणु
		अचिन्हित दीर्घ second, word;
		अचिन्हित दीर्घ second_dest;

		अगर (__get_word(ldq_u, second, src+1))
			वापस 0;
		extql(first, soff, word);
		checksum += carry;
		len -= 8;
		extqh(second, soff, first);
		src++;
		word |= first;
		first = second;
		insql(word, करोff, second_dest);
		checksum += word;
		stq_u(partial_dest | second_dest, dst);
		carry = checksum < word;
		insqh(word, करोff, partial_dest);
		dst++;
	पूर्ण
	len += करोff;
	checksum += carry;
	अगर (len >= 0) अणु
		अचिन्हित दीर्घ second, word;
		अचिन्हित दीर्घ second_dest;

		अगर (__get_word(ldq_u, second, lastsrc))
			वापस 0;
		extql(first, soff, word);
		extqh(second, soff, first);
		word |= first;
		first = second;
		mskql(word, len-करोff, word);
		checksum += word;
		insql(word, करोff, second_dest);
		carry = checksum < word;
		stq_u(partial_dest | second_dest, dst);
		अगर (len) अणु
			ldq_u(second_dest, dst+1);
			insqh(word, करोff, partial_dest);
			mskqh(second_dest, len, second_dest);
			stq_u(partial_dest | second_dest, dst+1);
		पूर्ण
		checksum += carry;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ second, word;
		अचिन्हित दीर्घ second_dest;

		अगर (__get_word(ldq_u, second, lastsrc))
			वापस 0;
		extql(first, soff, word);
		extqh(second, soff, first);
		word |= first;
		ldq_u(second_dest, dst);
		mskql(word, len-करोff, word);
		checksum += word;
		mskqh(second_dest, len, second_dest);
		carry = checksum < word;
		insql(word, करोff, word);
		stq_u(partial_dest | word | second_dest, dst);
		checksum += carry;
	पूर्ण
	वापस checksum;
पूर्ण

अटल __wsum __csum_and_copy(स्थिर व्योम __user *src, व्योम *dst, पूर्णांक len)
अणु
	अचिन्हित दीर्घ soff = 7 & (अचिन्हित दीर्घ) src;
	अचिन्हित दीर्घ करोff = 7 & (अचिन्हित दीर्घ) dst;
	अचिन्हित दीर्घ checksum;

	अगर (!करोff) अणु
		अगर (!soff)
			checksum = csum_partial_cfu_aligned(
				(स्थिर अचिन्हित दीर्घ __user *) src,
				(अचिन्हित दीर्घ *) dst, len-8);
		अन्यथा
			checksum = csum_partial_cfu_dest_aligned(
				(स्थिर अचिन्हित दीर्घ __user *) src,
				(अचिन्हित दीर्घ *) dst,
				soff, len-8);
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ partial_dest;
		ldq_u(partial_dest, dst);
		अगर (!soff)
			checksum = csum_partial_cfu_src_aligned(
				(स्थिर अचिन्हित दीर्घ __user *) src,
				(अचिन्हित दीर्घ *) dst,
				करोff, len-8, partial_dest);
		अन्यथा
			checksum = csum_partial_cfu_unaligned(
				(स्थिर अचिन्हित दीर्घ __user *) src,
				(अचिन्हित दीर्घ *) dst,
				soff, करोff, len-8, partial_dest);
	पूर्ण
	वापस (__क्रमce __wsum)from64to16 (checksum);
पूर्ण

__wsum
csum_and_copy_from_user(स्थिर व्योम __user *src, व्योम *dst, पूर्णांक len)
अणु
	अगर (!access_ok(src, len))
		वापस 0;
	वापस __csum_and_copy(src, dst, len);
पूर्ण
EXPORT_SYMBOL(csum_and_copy_from_user);

__wsum
csum_partial_copy_nocheck(स्थिर व्योम *src, व्योम *dst, पूर्णांक len)
अणु
	वापस __csum_and_copy((__क्रमce स्थिर व्योम __user *)src,
						dst, len);
पूर्ण
EXPORT_SYMBOL(csum_partial_copy_nocheck);
