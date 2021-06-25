<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/mm.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/word-at-a-समय.स>

/*
 * Do a strnlen, वापस length of string *with* final '\0'.
 * 'count' is the user-supplied count, while 'max' is the
 * address space maximum.
 *
 * Return 0 क्रम exceptions (which includes hitting the address
 * space maximum), or 'count+1' अगर hitting the user-supplied
 * maximum count.
 *
 * NOTE! We can someबार overshoot the user-supplied maximum
 * अगर it fits in a aligned 'long'. The caller needs to check
 * the वापस value against "> max".
 */
अटल अंतरभूत दीर्घ करो_strnlen_user(स्थिर अक्षर __user *src, अचिन्हित दीर्घ count, अचिन्हित दीर्घ max)
अणु
	स्थिर काष्ठा word_at_a_समय स्थिरants = WORD_AT_A_TIME_CONSTANTS;
	अचिन्हित दीर्घ align, res = 0;
	अचिन्हित दीर्घ c;

	/*
	 * Do everything aligned. But that means that we
	 * need to also expand the maximum..
	 */
	align = (माप(अचिन्हित दीर्घ) - 1) & (अचिन्हित दीर्घ)src;
	src -= align;
	max += align;

	unsafe_get_user(c, (अचिन्हित दीर्घ __user *)src, efault);
	c |= aligned_byte_mask(align);

	क्रम (;;) अणु
		अचिन्हित दीर्घ data;
		अगर (has_zero(c, &data, &स्थिरants)) अणु
			data = prep_zero_mask(c, data, &स्थिरants);
			data = create_zero_mask(data);
			वापस res + find_zero(data) + 1 - align;
		पूर्ण
		res += माप(अचिन्हित दीर्घ);
		/* We alपढ़ोy handled 'unsigned long' bytes. Did we करो it all ? */
		अगर (unlikely(max <= माप(अचिन्हित दीर्घ)))
			अवरोध;
		max -= माप(अचिन्हित दीर्घ);
		unsafe_get_user(c, (अचिन्हित दीर्घ __user *)(src+res), efault);
	पूर्ण
	res -= align;

	/*
	 * Uhhuh. We hit 'max'. But was that the user-specअगरied maximum
	 * too? If so, वापस the marker क्रम "too long".
	 */
	अगर (res >= count)
		वापस count+1;

	/*
	 * Nope: we hit the address space limit, and we still had more
	 * अक्षरacters the caller would have wanted. That's 0.
	 */
efault:
	वापस 0;
पूर्ण

/**
 * strnlen_user: - Get the size of a user string INCLUDING final NUL.
 * @str: The string to measure.
 * @count: Maximum count (including NUL अक्षरacter)
 *
 * Context: User context only. This function may sleep अगर pagefaults are
 *          enabled.
 *
 * Get the size of a NUL-terminated string in user space.
 *
 * Returns the size of the string INCLUDING the terminating NUL.
 * If the string is too दीर्घ, वापसs a number larger than @count. User
 * has to check the वापस value against "> count".
 * On exception (or invalid count), वापसs 0.
 *
 * NOTE! You should basically never use this function. There is
 * almost never any valid हाल क्रम using the length of a user space
 * string, since the string can be changed at any समय by other
 * thपढ़ोs. Use "strncpy_from_user()" instead to get a stable copy
 * of the string.
 */
दीर्घ strnlen_user(स्थिर अक्षर __user *str, दीर्घ count)
अणु
	अचिन्हित दीर्घ max_addr, src_addr;

	अगर (unlikely(count <= 0))
		वापस 0;

	max_addr = user_addr_max();
	src_addr = (अचिन्हित दीर्घ)untagged_addr(str);
	अगर (likely(src_addr < max_addr)) अणु
		अचिन्हित दीर्घ max = max_addr - src_addr;
		दीर्घ retval;

		/*
		 * Truncate 'max' to the user-specअगरied limit, so that
		 * we only have one limit we need to check in the loop
		 */
		अगर (max > count)
			max = count;

		अगर (user_पढ़ो_access_begin(str, max)) अणु
			retval = करो_strnlen_user(str, count, max);
			user_पढ़ो_access_end();
			वापस retval;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(strnlen_user);
