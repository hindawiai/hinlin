<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/bitops.h>
#समावेश <linux/fault-inject-usercopy.h>
#समावेश <linux/instrumented.h>
#समावेश <linux/uaccess.h>

/* out-of-line parts */

#अगर_अघोषित INLINE_COPY_FROM_USER
अचिन्हित दीर्घ _copy_from_user(व्योम *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ n)
अणु
	अचिन्हित दीर्घ res = n;
	might_fault();
	अगर (!should_fail_usercopy() && likely(access_ok(from, n))) अणु
		instrument_copy_from_user(to, from, n);
		res = raw_copy_from_user(to, from, n);
	पूर्ण
	अगर (unlikely(res))
		स_रखो(to + (n - res), 0, res);
	वापस res;
पूर्ण
EXPORT_SYMBOL(_copy_from_user);
#पूर्ण_अगर

#अगर_अघोषित INLINE_COPY_TO_USER
अचिन्हित दीर्घ _copy_to_user(व्योम __user *to, स्थिर व्योम *from, अचिन्हित दीर्घ n)
अणु
	might_fault();
	अगर (should_fail_usercopy())
		वापस n;
	अगर (likely(access_ok(to, n))) अणु
		instrument_copy_to_user(to, from, n);
		n = raw_copy_to_user(to, from, n);
	पूर्ण
	वापस n;
पूर्ण
EXPORT_SYMBOL(_copy_to_user);
#पूर्ण_अगर

/**
 * check_zeroed_user: check अगर a userspace buffer only contains zero bytes
 * @from: Source address, in userspace.
 * @size: Size of buffer.
 *
 * This is effectively लघुhand क्रम "memchr_inv(from, 0, size) == NULL" क्रम
 * userspace addresses (and is more efficient because we करोn't care where the
 * first non-zero byte is).
 *
 * Returns:
 *  * 0: There were non-zero bytes present in the buffer.
 *  * 1: The buffer was full of zero bytes.
 *  * -EFAULT: access to userspace failed.
 */
पूर्णांक check_zeroed_user(स्थिर व्योम __user *from, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ val;
	uपूर्णांकptr_t align = (uपूर्णांकptr_t) from % माप(अचिन्हित दीर्घ);

	अगर (unlikely(size == 0))
		वापस 1;

	from -= align;
	size += align;

	अगर (!user_पढ़ो_access_begin(from, size))
		वापस -EFAULT;

	unsafe_get_user(val, (अचिन्हित दीर्घ __user *) from, err_fault);
	अगर (align)
		val &= ~aligned_byte_mask(align);

	जबतक (size > माप(अचिन्हित दीर्घ)) अणु
		अगर (unlikely(val))
			जाओ करोne;

		from += माप(अचिन्हित दीर्घ);
		size -= माप(अचिन्हित दीर्घ);

		unsafe_get_user(val, (अचिन्हित दीर्घ __user *) from, err_fault);
	पूर्ण

	अगर (size < माप(अचिन्हित दीर्घ))
		val &= aligned_byte_mask(size);

करोne:
	user_पढ़ो_access_end();
	वापस (val == 0);
err_fault:
	user_पढ़ो_access_end();
	वापस -EFAULT;
पूर्ण
EXPORT_SYMBOL(check_zeroed_user);
