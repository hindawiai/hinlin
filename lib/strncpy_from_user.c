<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/compiler.h>
#समावेश <linux/export.h>
#समावेश <linux/fault-inject-usercopy.h>
#समावेश <linux/kasan-checks.h>
#समावेश <linux/thपढ़ो_info.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mm.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/word-at-a-समय.स>

#अगर_घोषित CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
#घोषणा IS_UNALIGNED(src, dst)	0
#अन्यथा
#घोषणा IS_UNALIGNED(src, dst)	\
	(((दीर्घ) dst | (दीर्घ) src) & (माप(दीर्घ) - 1))
#पूर्ण_अगर

/*
 * Do a म_नकलन, वापस length of string without final '\0'.
 * 'count' is the user-supplied count (return 'count' अगर we
 * hit it), 'max' is the address space maximum (and we वापस
 * -EFAULT अगर we hit it).
 */
अटल अंतरभूत दीर्घ करो_म_नकलन_from_user(अक्षर *dst, स्थिर अक्षर __user *src,
					अचिन्हित दीर्घ count, अचिन्हित दीर्घ max)
अणु
	स्थिर काष्ठा word_at_a_समय स्थिरants = WORD_AT_A_TIME_CONSTANTS;
	अचिन्हित दीर्घ res = 0;

	अगर (IS_UNALIGNED(src, dst))
		जाओ byte_at_a_समय;

	जबतक (max >= माप(अचिन्हित दीर्घ)) अणु
		अचिन्हित दीर्घ c, data, mask;

		/* Fall back to byte-at-a-समय अगर we get a page fault */
		unsafe_get_user(c, (अचिन्हित दीर्घ __user *)(src+res), byte_at_a_समय);

		/*
		 * Note that we mask out the bytes following the NUL. This is
		 * important to करो because string oblivious code may पढ़ो past
		 * the NUL. For those routines, we करोn't want to give them
		 * potentially अक्रमom bytes after the NUL in `src`.
		 *
		 * One example of such code is BPF map keys. BPF treats map keys
		 * as an opaque set of bytes. Without the post-NUL mask, any BPF
		 * maps keyed by strings वापसed from म_नकलन_from_user() may
		 * have multiple entries क्रम semantically identical strings.
		 */
		अगर (has_zero(c, &data, &स्थिरants)) अणु
			data = prep_zero_mask(c, data, &स्थिरants);
			data = create_zero_mask(data);
			mask = zero_bytemask(data);
			*(अचिन्हित दीर्घ *)(dst+res) = c & mask;
			वापस res + find_zero(data);
		पूर्ण

		*(अचिन्हित दीर्घ *)(dst+res) = c;

		res += माप(अचिन्हित दीर्घ);
		max -= माप(अचिन्हित दीर्घ);
	पूर्ण

byte_at_a_समय:
	जबतक (max) अणु
		अक्षर c;

		unsafe_get_user(c,src+res, efault);
		dst[res] = c;
		अगर (!c)
			वापस res;
		res++;
		max--;
	पूर्ण

	/*
	 * Uhhuh. We hit 'max'. But was that the user-specअगरied maximum
	 * too? If so, that's ok - we got as much as the user asked क्रम.
	 */
	अगर (res >= count)
		वापस res;

	/*
	 * Nope: we hit the address space limit, and we still had more
	 * अक्षरacters the caller would have wanted. That's an EFAULT.
	 */
efault:
	वापस -EFAULT;
पूर्ण

/**
 * म_नकलन_from_user: - Copy a NUL terminated string from userspace.
 * @dst:   Destination address, in kernel space.  This buffer must be at
 *         least @count bytes दीर्घ.
 * @src:   Source address, in user space.
 * @count: Maximum number of bytes to copy, including the trailing NUL.
 *
 * Copies a NUL-terminated string from userspace to kernel space.
 *
 * On success, वापसs the length of the string (not including the trailing
 * NUL).
 *
 * If access to userspace fails, वापसs -EFAULT (some data may have been
 * copied).
 *
 * If @count is smaller than the length of the string, copies @count bytes
 * and वापसs @count.
 */
दीर्घ म_नकलन_from_user(अक्षर *dst, स्थिर अक्षर __user *src, दीर्घ count)
अणु
	अचिन्हित दीर्घ max_addr, src_addr;

	might_fault();
	अगर (should_fail_usercopy())
		वापस -EFAULT;
	अगर (unlikely(count <= 0))
		वापस 0;

	max_addr = user_addr_max();
	src_addr = (अचिन्हित दीर्घ)untagged_addr(src);
	अगर (likely(src_addr < max_addr)) अणु
		अचिन्हित दीर्घ max = max_addr - src_addr;
		दीर्घ retval;

		/*
		 * Truncate 'max' to the user-specअगरied limit, so that
		 * we only have one limit we need to check in the loop
		 */
		अगर (max > count)
			max = count;

		kasan_check_ग_लिखो(dst, count);
		check_object_size(dst, count, false);
		अगर (user_पढ़ो_access_begin(src, max)) अणु
			retval = करो_म_नकलन_from_user(dst, src, count, max);
			user_पढ़ो_access_end();
			वापस retval;
		पूर्ण
	पूर्ण
	वापस -EFAULT;
पूर्ण
EXPORT_SYMBOL(म_नकलन_from_user);
