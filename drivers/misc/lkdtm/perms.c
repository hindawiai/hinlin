<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This is क्रम all the tests related to validating kernel memory
 * permissions: non-executable regions, non-writable regions, and
 * even non-पढ़ोable regions.
 */
#समावेश "lkdtm.h"
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mman.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/cacheflush.h>

/* Whether or not to fill the target memory area with करो_nothing(). */
#घोषणा CODE_WRITE	true
#घोषणा CODE_AS_IS	false

/* How many bytes to copy to be sure we've copied enough of करो_nothing(). */
#घोषणा EXEC_SIZE 64

/* This is non-स्थिर, so it will end up in the .data section. */
अटल u8 data_area[EXEC_SIZE];

/* This is cost, so it will end up in the .rodata section. */
अटल स्थिर अचिन्हित दीर्घ rodata = 0xAA55AA55;

/* This is marked __ro_after_init, so it should ultimately be .rodata. */
अटल अचिन्हित दीर्घ ro_after_init __ro_after_init = 0x55AA5500;

/*
 * This just वापसs to the caller. It is deचिन्हित to be copied पूर्णांकo
 * non-executable memory regions.
 */
अटल व्योम करो_nothing(व्योम)
अणु
	वापस;
पूर्ण

/* Must immediately follow करो_nothing क्रम size calculuations to work out. */
अटल व्योम करो_overwritten(व्योम)
अणु
	pr_info("do_overwritten wasn't overwritten!\n");
	वापस;
पूर्ण

अटल noअंतरभूत व्योम execute_location(व्योम *dst, bool ग_लिखो)
अणु
	व्योम (*func)(व्योम) = dst;

	pr_info("attempting ok execution at %px\n", करो_nothing);
	करो_nothing();

	अगर (ग_लिखो == CODE_WRITE) अणु
		स_नकल(dst, करो_nothing, EXEC_SIZE);
		flush_icache_range((अचिन्हित दीर्घ)dst,
				   (अचिन्हित दीर्घ)dst + EXEC_SIZE);
	पूर्ण
	pr_info("attempting bad execution at %px\n", func);
	func();
	pr_err("FAIL: func returned\n");
पूर्ण

अटल व्योम execute_user_location(व्योम *dst)
अणु
	पूर्णांक copied;

	/* Intentionally crossing kernel/user memory boundary. */
	व्योम (*func)(व्योम) = dst;

	pr_info("attempting ok execution at %px\n", करो_nothing);
	करो_nothing();

	copied = access_process_vm(current, (अचिन्हित दीर्घ)dst, करो_nothing,
				   EXEC_SIZE, FOLL_WRITE);
	अगर (copied < EXEC_SIZE)
		वापस;
	pr_info("attempting bad execution at %px\n", func);
	func();
	pr_err("FAIL: func returned\n");
पूर्ण

व्योम lkdपंचांग_WRITE_RO(व्योम)
अणु
	/* Explicitly cast away "const" क्रम the test and make अस्थिर. */
	अस्थिर अचिन्हित दीर्घ *ptr = (अचिन्हित दीर्घ *)&rodata;

	pr_info("attempting bad rodata write at %px\n", ptr);
	*ptr ^= 0xabcd1234;
	pr_err("FAIL: survived bad write\n");
पूर्ण

व्योम lkdपंचांग_WRITE_RO_AFTER_INIT(व्योम)
अणु
	अस्थिर अचिन्हित दीर्घ *ptr = &ro_after_init;

	/*
	 * Verअगरy we were written to during init. Since an Oops
	 * is considered a "success", a failure is to just skip the
	 * real test.
	 */
	अगर ((*ptr & 0xAA) != 0xAA) अणु
		pr_info("%p was NOT written during init!?\n", ptr);
		वापस;
	पूर्ण

	pr_info("attempting bad ro_after_init write at %px\n", ptr);
	*ptr ^= 0xabcd1234;
	pr_err("FAIL: survived bad write\n");
पूर्ण

व्योम lkdपंचांग_WRITE_KERN(व्योम)
अणु
	माप_प्रकार size;
	अस्थिर अचिन्हित अक्षर *ptr;

	size = (अचिन्हित दीर्घ)करो_overwritten - (अचिन्हित दीर्घ)करो_nothing;
	ptr = (अचिन्हित अक्षर *)करो_overwritten;

	pr_info("attempting bad %zu byte write at %px\n", size, ptr);
	स_नकल((व्योम *)ptr, (अचिन्हित अक्षर *)करो_nothing, size);
	flush_icache_range((अचिन्हित दीर्घ)ptr, (अचिन्हित दीर्घ)(ptr + size));
	pr_err("FAIL: survived bad write\n");

	करो_overwritten();
पूर्ण

व्योम lkdपंचांग_EXEC_DATA(व्योम)
अणु
	execute_location(data_area, CODE_WRITE);
पूर्ण

व्योम lkdपंचांग_EXEC_STACK(व्योम)
अणु
	u8 stack_area[EXEC_SIZE];
	execute_location(stack_area, CODE_WRITE);
पूर्ण

व्योम lkdपंचांग_EXEC_KMALLOC(व्योम)
अणु
	u32 *kदो_स्मृति_area = kदो_स्मृति(EXEC_SIZE, GFP_KERNEL);
	execute_location(kदो_स्मृति_area, CODE_WRITE);
	kमुक्त(kदो_स्मृति_area);
पूर्ण

व्योम lkdपंचांग_EXEC_VMALLOC(व्योम)
अणु
	u32 *vदो_स्मृति_area = vदो_स्मृति(EXEC_SIZE);
	execute_location(vदो_स्मृति_area, CODE_WRITE);
	vमुक्त(vदो_स्मृति_area);
पूर्ण

व्योम lkdपंचांग_EXEC_RODATA(व्योम)
अणु
	execute_location(lkdपंचांग_rodata_करो_nothing, CODE_AS_IS);
पूर्ण

व्योम lkdपंचांग_EXEC_USERSPACE(व्योम)
अणु
	अचिन्हित दीर्घ user_addr;

	user_addr = vm_mmap(शून्य, 0, PAGE_SIZE,
			    PROT_READ | PROT_WRITE | PROT_EXEC,
			    MAP_ANONYMOUS | MAP_PRIVATE, 0);
	अगर (user_addr >= TASK_SIZE) अणु
		pr_warn("Failed to allocate user memory\n");
		वापस;
	पूर्ण
	execute_user_location((व्योम *)user_addr);
	vm_munmap(user_addr, PAGE_SIZE);
पूर्ण

व्योम lkdपंचांग_EXEC_शून्य(व्योम)
अणु
	execute_location(शून्य, CODE_AS_IS);
पूर्ण

व्योम lkdपंचांग_ACCESS_USERSPACE(व्योम)
अणु
	अचिन्हित दीर्घ user_addr, पंचांगp = 0;
	अचिन्हित दीर्घ *ptr;

	user_addr = vm_mmap(शून्य, 0, PAGE_SIZE,
			    PROT_READ | PROT_WRITE | PROT_EXEC,
			    MAP_ANONYMOUS | MAP_PRIVATE, 0);
	अगर (user_addr >= TASK_SIZE) अणु
		pr_warn("Failed to allocate user memory\n");
		वापस;
	पूर्ण

	अगर (copy_to_user((व्योम __user *)user_addr, &पंचांगp, माप(पंचांगp))) अणु
		pr_warn("copy_to_user failed\n");
		vm_munmap(user_addr, PAGE_SIZE);
		वापस;
	पूर्ण

	ptr = (अचिन्हित दीर्घ *)user_addr;

	pr_info("attempting bad read at %px\n", ptr);
	पंचांगp = *ptr;
	पंचांगp += 0xc0dec0de;
	pr_err("FAIL: survived bad read\n");

	pr_info("attempting bad write at %px\n", ptr);
	*ptr = पंचांगp;
	pr_err("FAIL: survived bad write\n");

	vm_munmap(user_addr, PAGE_SIZE);
पूर्ण

व्योम lkdपंचांग_ACCESS_शून्य(व्योम)
अणु
	अचिन्हित दीर्घ पंचांगp;
	अस्थिर अचिन्हित दीर्घ *ptr = (अचिन्हित दीर्घ *)शून्य;

	pr_info("attempting bad read at %px\n", ptr);
	पंचांगp = *ptr;
	पंचांगp += 0xc0dec0de;
	pr_err("FAIL: survived bad read\n");

	pr_info("attempting bad write at %px\n", ptr);
	*ptr = पंचांगp;
	pr_err("FAIL: survived bad write\n");
पूर्ण

व्योम __init lkdपंचांग_perms_init(व्योम)
अणु
	/* Make sure we can ग_लिखो to __ro_after_init values during __init */
	ro_after_init |= 0xAA;
पूर्ण
