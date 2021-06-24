<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This is क्रम all the tests related to copy_to_user() and copy_from_user()
 * hardening.
 */
#समावेश "lkdtm.h"
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/mman.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/cacheflush.h>

/*
 * Many of the tests here end up using स्थिर sizes, but those would
 * normally be ignored by hardened usercopy, so क्रमce the compiler
 * पूर्णांकo choosing the non-स्थिर path to make sure we trigger the
 * hardened usercopy checks by added "unconst" to all the स्थिर copies,
 * and making sure "cache_size" isn't optimized पूर्णांकo a स्थिर.
 */
अटल अस्थिर माप_प्रकार unस्थिर;
अटल अस्थिर माप_प्रकार cache_size = 1024;
अटल काष्ठा kmem_cache *whitelist_cache;

अटल स्थिर अचिन्हित अक्षर test_text[] = "This is a test.\n";

/*
 * Instead of adding -Wno-वापस-local-addr, just pass the stack address
 * through a function to obfuscate it from the compiler.
 */
अटल noअंतरभूत अचिन्हित अक्षर *trick_compiler(अचिन्हित अक्षर *stack)
अणु
	वापस stack + 0;
पूर्ण

अटल noअंतरभूत अचिन्हित अक्षर *करो_usercopy_stack_callee(पूर्णांक value)
अणु
	अचिन्हित अक्षर buf[32];
	पूर्णांक i;

	/* Exercise stack to aव्योम everything living in रेजिस्टरs. */
	क्रम (i = 0; i < माप(buf); i++) अणु
		buf[i] = value & 0xff;
	पूर्ण

	वापस trick_compiler(buf);
पूर्ण

अटल noअंतरभूत व्योम करो_usercopy_stack(bool to_user, bool bad_frame)
अणु
	अचिन्हित दीर्घ user_addr;
	अचिन्हित अक्षर good_stack[32];
	अचिन्हित अक्षर *bad_stack;
	पूर्णांक i;

	/* Exercise stack to aव्योम everything living in रेजिस्टरs. */
	क्रम (i = 0; i < माप(good_stack); i++)
		good_stack[i] = test_text[i % माप(test_text)];

	/* This is a poपूर्णांकer to outside our current stack frame. */
	अगर (bad_frame) अणु
		bad_stack = करो_usercopy_stack_callee((uपूर्णांकptr_t)&bad_stack);
	पूर्ण अन्यथा अणु
		/* Put start address just inside stack. */
		bad_stack = task_stack_page(current) + THREAD_SIZE;
		bad_stack -= माप(अचिन्हित दीर्घ);
	पूर्ण

	user_addr = vm_mmap(शून्य, 0, PAGE_SIZE,
			    PROT_READ | PROT_WRITE | PROT_EXEC,
			    MAP_ANONYMOUS | MAP_PRIVATE, 0);
	अगर (user_addr >= TASK_SIZE) अणु
		pr_warn("Failed to allocate user memory\n");
		वापस;
	पूर्ण

	अगर (to_user) अणु
		pr_info("attempting good copy_to_user of local stack\n");
		अगर (copy_to_user((व्योम __user *)user_addr, good_stack,
				 unस्थिर + माप(good_stack))) अणु
			pr_warn("copy_to_user failed unexpectedly?!\n");
			जाओ मुक्त_user;
		पूर्ण

		pr_info("attempting bad copy_to_user of distant stack\n");
		अगर (copy_to_user((व्योम __user *)user_addr, bad_stack,
				 unस्थिर + माप(good_stack))) अणु
			pr_warn("copy_to_user failed, but lacked Oops\n");
			जाओ मुक्त_user;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * There isn't a safe way to not be रक्षित by usercopy
		 * अगर we're going to write to another thread's stack.
		 */
		अगर (!bad_frame)
			जाओ मुक्त_user;

		pr_info("attempting good copy_from_user of local stack\n");
		अगर (copy_from_user(good_stack, (व्योम __user *)user_addr,
				   unस्थिर + माप(good_stack))) अणु
			pr_warn("copy_from_user failed unexpectedly?!\n");
			जाओ मुक्त_user;
		पूर्ण

		pr_info("attempting bad copy_from_user of distant stack\n");
		अगर (copy_from_user(bad_stack, (व्योम __user *)user_addr,
				   unस्थिर + माप(good_stack))) अणु
			pr_warn("copy_from_user failed, but lacked Oops\n");
			जाओ मुक्त_user;
		पूर्ण
	पूर्ण

मुक्त_user:
	vm_munmap(user_addr, PAGE_SIZE);
पूर्ण

/*
 * This checks क्रम whole-object size validation with hardened usercopy,
 * with or without usercopy whitelisting.
 */
अटल व्योम करो_usercopy_heap_size(bool to_user)
अणु
	अचिन्हित दीर्घ user_addr;
	अचिन्हित अक्षर *one, *two;
	व्योम __user *test_user_addr;
	व्योम *test_kern_addr;
	माप_प्रकार size = unस्थिर + 1024;

	one = kदो_स्मृति(size, GFP_KERNEL);
	two = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!one || !two) अणु
		pr_warn("Failed to allocate kernel memory\n");
		जाओ मुक्त_kernel;
	पूर्ण

	user_addr = vm_mmap(शून्य, 0, PAGE_SIZE,
			    PROT_READ | PROT_WRITE | PROT_EXEC,
			    MAP_ANONYMOUS | MAP_PRIVATE, 0);
	अगर (user_addr >= TASK_SIZE) अणु
		pr_warn("Failed to allocate user memory\n");
		जाओ मुक्त_kernel;
	पूर्ण

	स_रखो(one, 'A', size);
	स_रखो(two, 'B', size);

	test_user_addr = (व्योम __user *)(user_addr + 16);
	test_kern_addr = one + 16;

	अगर (to_user) अणु
		pr_info("attempting good copy_to_user of correct size\n");
		अगर (copy_to_user(test_user_addr, test_kern_addr, size / 2)) अणु
			pr_warn("copy_to_user failed unexpectedly?!\n");
			जाओ मुक्त_user;
		पूर्ण

		pr_info("attempting bad copy_to_user of too large size\n");
		अगर (copy_to_user(test_user_addr, test_kern_addr, size)) अणु
			pr_warn("copy_to_user failed, but lacked Oops\n");
			जाओ मुक्त_user;
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_info("attempting good copy_from_user of correct size\n");
		अगर (copy_from_user(test_kern_addr, test_user_addr, size / 2)) अणु
			pr_warn("copy_from_user failed unexpectedly?!\n");
			जाओ मुक्त_user;
		पूर्ण

		pr_info("attempting bad copy_from_user of too large size\n");
		अगर (copy_from_user(test_kern_addr, test_user_addr, size)) अणु
			pr_warn("copy_from_user failed, but lacked Oops\n");
			जाओ मुक्त_user;
		पूर्ण
	पूर्ण

मुक्त_user:
	vm_munmap(user_addr, PAGE_SIZE);
मुक्त_kernel:
	kमुक्त(one);
	kमुक्त(two);
पूर्ण

/*
 * This checks क्रम the specअगरic whitelist winकरोw within an object. If this
 * test passes, then करो_usercopy_heap_size() tests will pass too.
 */
अटल व्योम करो_usercopy_heap_whitelist(bool to_user)
अणु
	अचिन्हित दीर्घ user_alloc;
	अचिन्हित अक्षर *buf = शून्य;
	अचिन्हित अक्षर __user *user_addr;
	माप_प्रकार offset, size;

	/* Make sure cache was prepared. */
	अगर (!whitelist_cache) अणु
		pr_warn("Failed to allocate kernel cache\n");
		वापस;
	पूर्ण

	/*
	 * Allocate a buffer with a whitelisted winकरोw in the buffer.
	 */
	buf = kmem_cache_alloc(whitelist_cache, GFP_KERNEL);
	अगर (!buf) अणु
		pr_warn("Failed to allocate buffer from whitelist cache\n");
		जाओ मुक्त_alloc;
	पूर्ण

	/* Allocate user memory we'll poke at. */
	user_alloc = vm_mmap(शून्य, 0, PAGE_SIZE,
			    PROT_READ | PROT_WRITE | PROT_EXEC,
			    MAP_ANONYMOUS | MAP_PRIVATE, 0);
	अगर (user_alloc >= TASK_SIZE) अणु
		pr_warn("Failed to allocate user memory\n");
		जाओ मुक्त_alloc;
	पूर्ण
	user_addr = (व्योम __user *)user_alloc;

	स_रखो(buf, 'B', cache_size);

	/* Whitelisted winकरोw in buffer, from kmem_cache_create_usercopy. */
	offset = (cache_size / 4) + unस्थिर;
	size = (cache_size / 16) + unस्थिर;

	अगर (to_user) अणु
		pr_info("attempting good copy_to_user inside whitelist\n");
		अगर (copy_to_user(user_addr, buf + offset, size)) अणु
			pr_warn("copy_to_user failed unexpectedly?!\n");
			जाओ मुक्त_user;
		पूर्ण

		pr_info("attempting bad copy_to_user outside whitelist\n");
		अगर (copy_to_user(user_addr, buf + offset - 1, size)) अणु
			pr_warn("copy_to_user failed, but lacked Oops\n");
			जाओ मुक्त_user;
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_info("attempting good copy_from_user inside whitelist\n");
		अगर (copy_from_user(buf + offset, user_addr, size)) अणु
			pr_warn("copy_from_user failed unexpectedly?!\n");
			जाओ मुक्त_user;
		पूर्ण

		pr_info("attempting bad copy_from_user outside whitelist\n");
		अगर (copy_from_user(buf + offset - 1, user_addr, size)) अणु
			pr_warn("copy_from_user failed, but lacked Oops\n");
			जाओ मुक्त_user;
		पूर्ण
	पूर्ण

मुक्त_user:
	vm_munmap(user_alloc, PAGE_SIZE);
मुक्त_alloc:
	अगर (buf)
		kmem_cache_मुक्त(whitelist_cache, buf);
पूर्ण

/* Callable tests. */
व्योम lkdपंचांग_USERCOPY_HEAP_SIZE_TO(व्योम)
अणु
	करो_usercopy_heap_size(true);
पूर्ण

व्योम lkdपंचांग_USERCOPY_HEAP_SIZE_FROM(व्योम)
अणु
	करो_usercopy_heap_size(false);
पूर्ण

व्योम lkdपंचांग_USERCOPY_HEAP_WHITELIST_TO(व्योम)
अणु
	करो_usercopy_heap_whitelist(true);
पूर्ण

व्योम lkdपंचांग_USERCOPY_HEAP_WHITELIST_FROM(व्योम)
अणु
	करो_usercopy_heap_whitelist(false);
पूर्ण

व्योम lkdपंचांग_USERCOPY_STACK_FRAME_TO(व्योम)
अणु
	करो_usercopy_stack(true, true);
पूर्ण

व्योम lkdपंचांग_USERCOPY_STACK_FRAME_FROM(व्योम)
अणु
	करो_usercopy_stack(false, true);
पूर्ण

व्योम lkdपंचांग_USERCOPY_STACK_BEYOND(व्योम)
अणु
	करो_usercopy_stack(true, false);
पूर्ण

व्योम lkdपंचांग_USERCOPY_KERNEL(व्योम)
अणु
	अचिन्हित दीर्घ user_addr;

	user_addr = vm_mmap(शून्य, 0, PAGE_SIZE,
			    PROT_READ | PROT_WRITE | PROT_EXEC,
			    MAP_ANONYMOUS | MAP_PRIVATE, 0);
	अगर (user_addr >= TASK_SIZE) अणु
		pr_warn("Failed to allocate user memory\n");
		वापस;
	पूर्ण

	pr_info("attempting good copy_to_user from kernel rodata: %px\n",
		test_text);
	अगर (copy_to_user((व्योम __user *)user_addr, test_text,
			 unस्थिर + माप(test_text))) अणु
		pr_warn("copy_to_user failed unexpectedly?!\n");
		जाओ मुक्त_user;
	पूर्ण

	pr_info("attempting bad copy_to_user from kernel text: %px\n",
		vm_mmap);
	अगर (copy_to_user((व्योम __user *)user_addr, function_nocfi(vm_mmap),
			 unस्थिर + PAGE_SIZE)) अणु
		pr_warn("copy_to_user failed, but lacked Oops\n");
		जाओ मुक्त_user;
	पूर्ण
	pr_err("FAIL: survived bad copy_to_user()\n");

मुक्त_user:
	vm_munmap(user_addr, PAGE_SIZE);
पूर्ण

व्योम __init lkdपंचांग_usercopy_init(व्योम)
अणु
	/* Prepare cache that lacks SLAB_USERCOPY flag. */
	whitelist_cache =
		kmem_cache_create_usercopy("lkdtm-usercopy", cache_size,
					   0, 0,
					   cache_size / 4,
					   cache_size / 16,
					   शून्य);
पूर्ण

व्योम __निकास lkdपंचांग_usercopy_निकास(व्योम)
अणु
	kmem_cache_destroy(whitelist_cache);
पूर्ण
