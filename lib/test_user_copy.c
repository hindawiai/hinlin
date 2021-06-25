<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Kernel module क्रम testing copy_to/from_user infraकाष्ठाure.
 *
 * Copyright 2013 Google Inc. All Rights Reserved
 *
 * Authors:
 *      Kees Cook       <keescook@chromium.org>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/mman.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/vदो_स्मृति.h>

/*
 * Several 32-bit architectures support 64-bit अणुget,putपूर्ण_user() calls.
 * As there करोesn't appear to be anything that can safely determine
 * their capability at compile-समय, we just have to opt-out certain archs.
 */
#अगर BITS_PER_LONG == 64 || (!(defined(CONFIG_ARM) && !defined(MMU)) && \
			    !defined(CONFIG_M68K) &&		\
			    !defined(CONFIG_MICROBLAZE) &&	\
			    !defined(CONFIG_NIOS2) &&		\
			    !defined(CONFIG_PPC32) &&		\
			    !defined(CONFIG_SUPERH))
# define TEST_U64
#पूर्ण_अगर

#घोषणा test(condition, msg, ...)					\
(अणु									\
	पूर्णांक cond = (condition);						\
	अगर (cond)							\
		pr_warn("[%d] " msg "\n", __LINE__, ##__VA_ARGS__);	\
	cond;								\
पूर्ण)

अटल bool is_zeroed(व्योम *from, माप_प्रकार size)
अणु
	वापस स_प्रथम_inv(from, 0x0, size) == शून्य;
पूर्ण

अटल पूर्णांक test_check_nonzero_user(अक्षर *kmem, अक्षर __user *umem, माप_प्रकार size)
अणु
	पूर्णांक ret = 0;
	माप_प्रकार start, end, i, zero_start, zero_end;

	अगर (test(size < 2 * PAGE_SIZE, "buffer too small"))
		वापस -EINVAL;

	/*
	 * We want to cross a page boundary to exercise the code more
	 * effectively. We also करोn't want to make the size we scan too large,
	 * otherwise the test can take a दीर्घ समय and cause soft lockups. So
	 * scan a 1024 byte region across the page boundary.
	 */
	size = 1024;
	start = PAGE_SIZE - (size / 2);

	kmem += start;
	umem += start;

	zero_start = size / 4;
	zero_end = size - zero_start;

	/*
	 * We conduct a series of check_nonzero_user() tests on a block of
	 * memory with the following byte-pattern (trying every possible
	 * [start,end] pair):
	 *
	 *   [ 00 ff 00 ff ... 00 00 00 00 ... ff 00 ff 00 ]
	 *
	 * And we verअगरy that check_nonzero_user() acts identically to
	 * स_प्रथम_inv().
	 */

	स_रखो(kmem, 0x0, size);
	क्रम (i = 1; i < zero_start; i += 2)
		kmem[i] = 0xff;
	क्रम (i = zero_end; i < size; i += 2)
		kmem[i] = 0xff;

	ret |= test(copy_to_user(umem, kmem, size),
		    "legitimate copy_to_user failed");

	क्रम (start = 0; start <= size; start++) अणु
		क्रम (end = start; end <= size; end++) अणु
			माप_प्रकार len = end - start;
			पूर्णांक retval = check_zeroed_user(umem + start, len);
			पूर्णांक expected = is_zeroed(kmem + start, len);

			ret |= test(retval != expected,
				    "check_nonzero_user(=%d) != memchr_inv(=%d) mismatch (start=%zu, end=%zu)",
				    retval, expected, start, end);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक test_copy_काष्ठा_from_user(अक्षर *kmem, अक्षर __user *umem,
				      माप_प्रकार size)
अणु
	पूर्णांक ret = 0;
	अक्षर *umem_src = शून्य, *expected = शून्य;
	माप_प्रकार ksize, usize;

	umem_src = kदो_स्मृति(size, GFP_KERNEL);
	ret = test(umem_src == शून्य, "kmalloc failed");
	अगर (ret)
		जाओ out_मुक्त;

	expected = kदो_स्मृति(size, GFP_KERNEL);
	ret = test(expected == शून्य, "kmalloc failed");
	अगर (ret)
		जाओ out_मुक्त;

	/* Fill umem with a fixed byte pattern. */
	स_रखो(umem_src, 0x3e, size);
	ret |= test(copy_to_user(umem, umem_src, size),
		    "legitimate copy_to_user failed");

	/* Check basic हाल -- (usize == ksize). */
	ksize = size;
	usize = size;

	स_नकल(expected, umem_src, ksize);

	स_रखो(kmem, 0x0, size);
	ret |= test(copy_काष्ठा_from_user(kmem, ksize, umem, usize),
		    "copy_struct_from_user(usize == ksize) failed");
	ret |= test(स_भेद(kmem, expected, ksize),
		    "copy_struct_from_user(usize == ksize) gives unexpected copy");

	/* Old userspace हाल -- (usize < ksize). */
	ksize = size;
	usize = size / 2;

	स_नकल(expected, umem_src, usize);
	स_रखो(expected + usize, 0x0, ksize - usize);

	स_रखो(kmem, 0x0, size);
	ret |= test(copy_काष्ठा_from_user(kmem, ksize, umem, usize),
		    "copy_struct_from_user(usize < ksize) failed");
	ret |= test(स_भेद(kmem, expected, ksize),
		    "copy_struct_from_user(usize < ksize) gives unexpected copy");

	/* New userspace (-E2BIG) हाल -- (usize > ksize). */
	ksize = size / 2;
	usize = size;

	स_रखो(kmem, 0x0, size);
	ret |= test(copy_काष्ठा_from_user(kmem, ksize, umem, usize) != -E2BIG,
		    "copy_struct_from_user(usize > ksize) didn't give E2BIG");

	/* New userspace (success) हाल -- (usize > ksize). */
	ksize = size / 2;
	usize = size;

	स_नकल(expected, umem_src, ksize);
	ret |= test(clear_user(umem + ksize, usize - ksize),
		    "legitimate clear_user failed");

	स_रखो(kmem, 0x0, size);
	ret |= test(copy_काष्ठा_from_user(kmem, ksize, umem, usize),
		    "copy_struct_from_user(usize > ksize) failed");
	ret |= test(स_भेद(kmem, expected, ksize),
		    "copy_struct_from_user(usize > ksize) gives unexpected copy");

out_मुक्त:
	kमुक्त(expected);
	kमुक्त(umem_src);
	वापस ret;
पूर्ण

अटल पूर्णांक __init test_user_copy_init(व्योम)
अणु
	पूर्णांक ret = 0;
	अक्षर *kmem;
	अक्षर __user *usermem;
	अक्षर *bad_usermem;
	अचिन्हित दीर्घ user_addr;
	u8 val_u8;
	u16 val_u16;
	u32 val_u32;
#अगर_घोषित TEST_U64
	u64 val_u64;
#पूर्ण_अगर

	kmem = kदो_स्मृति(PAGE_SIZE * 2, GFP_KERNEL);
	अगर (!kmem)
		वापस -ENOMEM;

	user_addr = vm_mmap(शून्य, 0, PAGE_SIZE * 2,
			    PROT_READ | PROT_WRITE | PROT_EXEC,
			    MAP_ANONYMOUS | MAP_PRIVATE, 0);
	अगर (user_addr >= (अचिन्हित दीर्घ)(TASK_SIZE)) अणु
		pr_warn("Failed to allocate user memory\n");
		kमुक्त(kmem);
		वापस -ENOMEM;
	पूर्ण

	usermem = (अक्षर __user *)user_addr;
	bad_usermem = (अक्षर *)user_addr;

	/*
	 * Legitimate usage: none of these copies should fail.
	 */
	स_रखो(kmem, 0x3a, PAGE_SIZE * 2);
	ret |= test(copy_to_user(usermem, kmem, PAGE_SIZE),
		    "legitimate copy_to_user failed");
	स_रखो(kmem, 0x0, PAGE_SIZE);
	ret |= test(copy_from_user(kmem, usermem, PAGE_SIZE),
		    "legitimate copy_from_user failed");
	ret |= test(स_भेद(kmem, kmem + PAGE_SIZE, PAGE_SIZE),
		    "legitimate usercopy failed to copy data");

#घोषणा test_legit(size, check)						  \
	करो अणु								  \
		val_##size = check;					  \
		ret |= test(put_user(val_##size, (size __user *)usermem), \
		    "legitimate put_user (" #size ") failed");		  \
		val_##size = 0;						  \
		ret |= test(get_user(val_##size, (size __user *)usermem), \
		    "legitimate get_user (" #size ") failed");		  \
		ret |= test(val_##size != check,			  \
		    "legitimate get_user (" #size ") failed to do copy"); \
		अगर (val_##size != check) अणु				  \
			pr_info("0x%llx != 0x%llx\n",			  \
				(अचिन्हित दीर्घ दीर्घ)val_##size,		  \
				(अचिन्हित दीर्घ दीर्घ)check);		  \
		पूर्ण							  \
	पूर्ण जबतक (0)

	test_legit(u8,  0x5a);
	test_legit(u16, 0x5a5b);
	test_legit(u32, 0x5a5b5c5d);
#अगर_घोषित TEST_U64
	test_legit(u64, 0x5a5b5c5d6a6b6c6d);
#पूर्ण_अगर
#अघोषित test_legit

	/* Test usage of check_nonzero_user(). */
	ret |= test_check_nonzero_user(kmem, usermem, 2 * PAGE_SIZE);
	/* Test usage of copy_काष्ठा_from_user(). */
	ret |= test_copy_काष्ठा_from_user(kmem, usermem, 2 * PAGE_SIZE);

	/*
	 * Invalid usage: none of these copies should succeed.
	 */

	/* Prepare kernel memory with check values. */
	स_रखो(kmem, 0x5a, PAGE_SIZE);
	स_रखो(kmem + PAGE_SIZE, 0, PAGE_SIZE);

	/* Reject kernel-to-kernel copies through copy_from_user(). */
	ret |= test(!copy_from_user(kmem, (अक्षर __user *)(kmem + PAGE_SIZE),
				    PAGE_SIZE),
		    "illegal all-kernel copy_from_user passed");

	/* Destination half of buffer should have been zeroed. */
	ret |= test(स_भेद(kmem + PAGE_SIZE, kmem, PAGE_SIZE),
		    "zeroing failure for illegal all-kernel copy_from_user");

#अगर 0
	/*
	 * When running with SMAP/PAN/etc, this will Oops the kernel
	 * due to the zeroing of userspace memory on failure. This needs
	 * to be tested in LKDTM instead, since this test module करोes not
	 * expect to explode.
	 */
	ret |= test(!copy_from_user(bad_usermem, (अक्षर __user *)kmem,
				    PAGE_SIZE),
		    "illegal reversed copy_from_user passed");
#पूर्ण_अगर
	ret |= test(!copy_to_user((अक्षर __user *)kmem, kmem + PAGE_SIZE,
				  PAGE_SIZE),
		    "illegal all-kernel copy_to_user passed");
	ret |= test(!copy_to_user((अक्षर __user *)kmem, bad_usermem,
				  PAGE_SIZE),
		    "illegal reversed copy_to_user passed");

#घोषणा test_illegal(size, check)					    \
	करो अणु								    \
		val_##size = (check);					    \
		ret |= test(!get_user(val_##size, (size __user *)kmem),	    \
		    "illegal get_user (" #size ") passed");		    \
		ret |= test(val_##size != (size)0,			    \
		    "zeroing failure for illegal get_user (" #size ")");    \
		अगर (val_##size != (size)0) अणु				    \
			pr_info("0x%llx != 0\n",			    \
				(अचिन्हित दीर्घ दीर्घ)val_##size);	    \
		पूर्ण							    \
		ret |= test(!put_user(val_##size, (size __user *)kmem),	    \
		    "illegal put_user (" #size ") passed");		    \
	पूर्ण जबतक (0)

	test_illegal(u8,  0x5a);
	test_illegal(u16, 0x5a5b);
	test_illegal(u32, 0x5a5b5c5d);
#अगर_घोषित TEST_U64
	test_illegal(u64, 0x5a5b5c5d6a6b6c6d);
#पूर्ण_अगर
#अघोषित test_illegal

	vm_munmap(user_addr, PAGE_SIZE * 2);
	kमुक्त(kmem);

	अगर (ret == 0) अणु
		pr_info("tests passed.\n");
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

module_init(test_user_copy_init);

अटल व्योम __निकास test_user_copy_निकास(व्योम)
अणु
	pr_info("unloaded.\n");
पूर्ण

module_निकास(test_user_copy_निकास);

MODULE_AUTHOR("Kees Cook <keescook@chromium.org>");
MODULE_LICENSE("GPL");
