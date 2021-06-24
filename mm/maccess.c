<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Access kernel or user memory without faulting.
 */
#समावेश <linux/export.h>
#समावेश <linux/mm.h>
#समावेश <linux/uaccess.h>

bool __weak copy_from_kernel_nofault_allowed(स्थिर व्योम *unsafe_src,
		माप_प्रकार size)
अणु
	वापस true;
पूर्ण

#अगर_घोषित HAVE_GET_KERNEL_NOFAULT

#घोषणा copy_from_kernel_nofault_loop(dst, src, len, type, err_label)	\
	जबतक (len >= माप(type)) अणु					\
		__get_kernel_nofault(dst, src, type, err_label);		\
		dst += माप(type);					\
		src += माप(type);					\
		len -= माप(type);					\
	पूर्ण

दीर्घ copy_from_kernel_nofault(व्योम *dst, स्थिर व्योम *src, माप_प्रकार size)
अणु
	अगर (!copy_from_kernel_nofault_allowed(src, size))
		वापस -दुस्फल;

	pagefault_disable();
	copy_from_kernel_nofault_loop(dst, src, size, u64, Efault);
	copy_from_kernel_nofault_loop(dst, src, size, u32, Efault);
	copy_from_kernel_nofault_loop(dst, src, size, u16, Efault);
	copy_from_kernel_nofault_loop(dst, src, size, u8, Efault);
	pagefault_enable();
	वापस 0;
Efault:
	pagefault_enable();
	वापस -EFAULT;
पूर्ण
EXPORT_SYMBOL_GPL(copy_from_kernel_nofault);

#घोषणा copy_to_kernel_nofault_loop(dst, src, len, type, err_label)	\
	जबतक (len >= माप(type)) अणु					\
		__put_kernel_nofault(dst, src, type, err_label);		\
		dst += माप(type);					\
		src += माप(type);					\
		len -= माप(type);					\
	पूर्ण

दीर्घ copy_to_kernel_nofault(व्योम *dst, स्थिर व्योम *src, माप_प्रकार size)
अणु
	pagefault_disable();
	copy_to_kernel_nofault_loop(dst, src, size, u64, Efault);
	copy_to_kernel_nofault_loop(dst, src, size, u32, Efault);
	copy_to_kernel_nofault_loop(dst, src, size, u16, Efault);
	copy_to_kernel_nofault_loop(dst, src, size, u8, Efault);
	pagefault_enable();
	वापस 0;
Efault:
	pagefault_enable();
	वापस -EFAULT;
पूर्ण

दीर्घ म_नकलन_from_kernel_nofault(अक्षर *dst, स्थिर व्योम *unsafe_addr, दीर्घ count)
अणु
	स्थिर व्योम *src = unsafe_addr;

	अगर (unlikely(count <= 0))
		वापस 0;
	अगर (!copy_from_kernel_nofault_allowed(unsafe_addr, count))
		वापस -दुस्फल;

	pagefault_disable();
	करो अणु
		__get_kernel_nofault(dst, src, u8, Efault);
		dst++;
		src++;
	पूर्ण जबतक (dst[-1] && src - unsafe_addr < count);
	pagefault_enable();

	dst[-1] = '\0';
	वापस src - unsafe_addr;
Efault:
	pagefault_enable();
	dst[-1] = '\0';
	वापस -EFAULT;
पूर्ण
#अन्यथा /* HAVE_GET_KERNEL_NOFAULT */
/**
 * copy_from_kernel_nofault(): safely attempt to पढ़ो from kernel-space
 * @dst: poपूर्णांकer to the buffer that shall take the data
 * @src: address to पढ़ो from
 * @size: size of the data chunk
 *
 * Safely पढ़ो from kernel address @src to the buffer at @dst.  If a kernel
 * fault happens, handle that and वापस -EFAULT.  If @src is not a valid kernel
 * address, वापस -दुस्फल.
 *
 * We ensure that the copy_from_user is executed in atomic context so that
 * करो_page_fault() करोesn't attempt to take mmap_lock.  This makes
 * copy_from_kernel_nofault() suitable क्रम use within regions where the caller
 * alपढ़ोy holds mmap_lock, or other locks which nest inside mmap_lock.
 */
दीर्घ copy_from_kernel_nofault(व्योम *dst, स्थिर व्योम *src, माप_प्रकार size)
अणु
	दीर्घ ret;
	mm_segment_t old_fs = get_fs();

	अगर (!copy_from_kernel_nofault_allowed(src, size))
		वापस -दुस्फल;

	set_fs(KERNEL_DS);
	pagefault_disable();
	ret = __copy_from_user_inatomic(dst, (__क्रमce स्थिर व्योम __user *)src,
			size);
	pagefault_enable();
	set_fs(old_fs);

	अगर (ret)
		वापस -EFAULT;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(copy_from_kernel_nofault);

/**
 * copy_to_kernel_nofault(): safely attempt to ग_लिखो to a location
 * @dst: address to ग_लिखो to
 * @src: poपूर्णांकer to the data that shall be written
 * @size: size of the data chunk
 *
 * Safely ग_लिखो to address @dst from the buffer at @src.  If a kernel fault
 * happens, handle that and वापस -EFAULT.
 */
दीर्घ copy_to_kernel_nofault(व्योम *dst, स्थिर व्योम *src, माप_प्रकार size)
अणु
	दीर्घ ret;
	mm_segment_t old_fs = get_fs();

	set_fs(KERNEL_DS);
	pagefault_disable();
	ret = __copy_to_user_inatomic((__क्रमce व्योम __user *)dst, src, size);
	pagefault_enable();
	set_fs(old_fs);

	अगर (ret)
		वापस -EFAULT;
	वापस 0;
पूर्ण

/**
 * म_नकलन_from_kernel_nofault: - Copy a NUL terminated string from unsafe
 *				 address.
 * @dst:   Destination address, in kernel space.  This buffer must be at
 *         least @count bytes दीर्घ.
 * @unsafe_addr: Unsafe address.
 * @count: Maximum number of bytes to copy, including the trailing NUL.
 *
 * Copies a NUL-terminated string from unsafe address to kernel buffer.
 *
 * On success, वापसs the length of the string INCLUDING the trailing NUL.
 *
 * If access fails, वापसs -EFAULT (some data may have been copied and the
 * trailing NUL added).  If @unsafe_addr is not a valid kernel address, वापस
 * -दुस्फल.
 *
 * If @count is smaller than the length of the string, copies @count-1 bytes,
 * sets the last byte of @dst buffer to NUL and वापसs @count.
 */
दीर्घ म_नकलन_from_kernel_nofault(अक्षर *dst, स्थिर व्योम *unsafe_addr, दीर्घ count)
अणु
	mm_segment_t old_fs = get_fs();
	स्थिर व्योम *src = unsafe_addr;
	दीर्घ ret;

	अगर (unlikely(count <= 0))
		वापस 0;
	अगर (!copy_from_kernel_nofault_allowed(unsafe_addr, count))
		वापस -दुस्फल;

	set_fs(KERNEL_DS);
	pagefault_disable();

	करो अणु
		ret = __get_user(*dst++, (स्थिर अक्षर __user __क्रमce *)src++);
	पूर्ण जबतक (dst[-1] && ret == 0 && src - unsafe_addr < count);

	dst[-1] = '\0';
	pagefault_enable();
	set_fs(old_fs);

	वापस ret ? -EFAULT : src - unsafe_addr;
पूर्ण
#पूर्ण_अगर /* HAVE_GET_KERNEL_NOFAULT */

/**
 * copy_from_user_nofault(): safely attempt to पढ़ो from a user-space location
 * @dst: poपूर्णांकer to the buffer that shall take the data
 * @src: address to पढ़ो from. This must be a user address.
 * @size: size of the data chunk
 *
 * Safely पढ़ो from user address @src to the buffer at @dst. If a kernel fault
 * happens, handle that and वापस -EFAULT.
 */
दीर्घ copy_from_user_nofault(व्योम *dst, स्थिर व्योम __user *src, माप_प्रकार size)
अणु
	दीर्घ ret = -EFAULT;
	mm_segment_t old_fs = क्रमce_uaccess_begin();

	अगर (access_ok(src, size)) अणु
		pagefault_disable();
		ret = __copy_from_user_inatomic(dst, src, size);
		pagefault_enable();
	पूर्ण
	क्रमce_uaccess_end(old_fs);

	अगर (ret)
		वापस -EFAULT;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(copy_from_user_nofault);

/**
 * copy_to_user_nofault(): safely attempt to ग_लिखो to a user-space location
 * @dst: address to ग_लिखो to
 * @src: poपूर्णांकer to the data that shall be written
 * @size: size of the data chunk
 *
 * Safely ग_लिखो to address @dst from the buffer at @src.  If a kernel fault
 * happens, handle that and वापस -EFAULT.
 */
दीर्घ copy_to_user_nofault(व्योम __user *dst, स्थिर व्योम *src, माप_प्रकार size)
अणु
	दीर्घ ret = -EFAULT;
	mm_segment_t old_fs = क्रमce_uaccess_begin();

	अगर (access_ok(dst, size)) अणु
		pagefault_disable();
		ret = __copy_to_user_inatomic(dst, src, size);
		pagefault_enable();
	पूर्ण
	क्रमce_uaccess_end(old_fs);

	अगर (ret)
		वापस -EFAULT;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(copy_to_user_nofault);

/**
 * म_नकलन_from_user_nofault: - Copy a NUL terminated string from unsafe user
 *				address.
 * @dst:   Destination address, in kernel space.  This buffer must be at
 *         least @count bytes दीर्घ.
 * @unsafe_addr: Unsafe user address.
 * @count: Maximum number of bytes to copy, including the trailing NUL.
 *
 * Copies a NUL-terminated string from unsafe user address to kernel buffer.
 *
 * On success, वापसs the length of the string INCLUDING the trailing NUL.
 *
 * If access fails, वापसs -EFAULT (some data may have been copied
 * and the trailing NUL added).
 *
 * If @count is smaller than the length of the string, copies @count-1 bytes,
 * sets the last byte of @dst buffer to NUL and वापसs @count.
 */
दीर्घ म_नकलन_from_user_nofault(अक्षर *dst, स्थिर व्योम __user *unsafe_addr,
			      दीर्घ count)
अणु
	mm_segment_t old_fs;
	दीर्घ ret;

	अगर (unlikely(count <= 0))
		वापस 0;

	old_fs = क्रमce_uaccess_begin();
	pagefault_disable();
	ret = म_नकलन_from_user(dst, unsafe_addr, count);
	pagefault_enable();
	क्रमce_uaccess_end(old_fs);

	अगर (ret >= count) अणु
		ret = count;
		dst[ret - 1] = '\0';
	पूर्ण अन्यथा अगर (ret > 0) अणु
		ret++;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * strnlen_user_nofault: - Get the size of a user string INCLUDING final NUL.
 * @unsafe_addr: The string to measure.
 * @count: Maximum count (including NUL)
 *
 * Get the size of a NUL-terminated string in user space without pagefault.
 *
 * Returns the size of the string INCLUDING the terminating NUL.
 *
 * If the string is too दीर्घ, वापसs a number larger than @count. User
 * has to check the वापस value against "> count".
 * On exception (or invalid count), वापसs 0.
 *
 * Unlike strnlen_user, this can be used from IRQ handler etc. because
 * it disables pagefaults.
 */
दीर्घ strnlen_user_nofault(स्थिर व्योम __user *unsafe_addr, दीर्घ count)
अणु
	mm_segment_t old_fs;
	पूर्णांक ret;

	old_fs = क्रमce_uaccess_begin();
	pagefault_disable();
	ret = strnlen_user(unsafe_addr, count);
	pagefault_enable();
	क्रमce_uaccess_end(old_fs);

	वापस ret;
पूर्ण
