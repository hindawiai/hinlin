<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 * Author: Andrey Ryabinin <a.ryabinin@samsung.com>
 */

#घोषणा pr_fmt(fmt) "kasan test: %s " fmt, __func__

#समावेश <linux/mman.h>
#समावेश <linux/module.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

#समावेश "../mm/kasan/kasan.h"

#घोषणा OOB_TAG_OFF (IS_ENABLED(CONFIG_KASAN_GENERIC) ? 0 : KASAN_GRANULE_SIZE)

अटल noअंतरभूत व्योम __init copy_user_test(व्योम)
अणु
	अक्षर *kmem;
	अक्षर __user *usermem;
	माप_प्रकार size = 10;
	पूर्णांक __maybe_unused unused;

	kmem = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!kmem)
		वापस;

	usermem = (अक्षर __user *)vm_mmap(शून्य, 0, PAGE_SIZE,
			    PROT_READ | PROT_WRITE | PROT_EXEC,
			    MAP_ANONYMOUS | MAP_PRIVATE, 0);
	अगर (IS_ERR(usermem)) अणु
		pr_err("Failed to allocate user memory\n");
		kमुक्त(kmem);
		वापस;
	पूर्ण

	pr_info("out-of-bounds in copy_from_user()\n");
	unused = copy_from_user(kmem, usermem, size + 1 + OOB_TAG_OFF);

	pr_info("out-of-bounds in copy_to_user()\n");
	unused = copy_to_user(usermem, kmem, size + 1 + OOB_TAG_OFF);

	pr_info("out-of-bounds in __copy_from_user()\n");
	unused = __copy_from_user(kmem, usermem, size + 1 + OOB_TAG_OFF);

	pr_info("out-of-bounds in __copy_to_user()\n");
	unused = __copy_to_user(usermem, kmem, size + 1 + OOB_TAG_OFF);

	pr_info("out-of-bounds in __copy_from_user_inatomic()\n");
	unused = __copy_from_user_inatomic(kmem, usermem, size + 1 + OOB_TAG_OFF);

	pr_info("out-of-bounds in __copy_to_user_inatomic()\n");
	unused = __copy_to_user_inatomic(usermem, kmem, size + 1 + OOB_TAG_OFF);

	pr_info("out-of-bounds in strncpy_from_user()\n");
	unused = म_नकलन_from_user(kmem, usermem, size + 1 + OOB_TAG_OFF);

	vm_munmap((अचिन्हित दीर्घ)usermem, PAGE_SIZE);
	kमुक्त(kmem);
पूर्ण

अटल काष्ठा kasan_rcu_info अणु
	पूर्णांक i;
	काष्ठा rcu_head rcu;
पूर्ण *global_rcu_ptr;

अटल noअंतरभूत व्योम __init kasan_rcu_reclaim(काष्ठा rcu_head *rp)
अणु
	काष्ठा kasan_rcu_info *fp = container_of(rp,
						काष्ठा kasan_rcu_info, rcu);

	kमुक्त(fp);
	fp->i = 1;
पूर्ण

अटल noअंतरभूत व्योम __init kasan_rcu_uaf(व्योम)
अणु
	काष्ठा kasan_rcu_info *ptr;

	pr_info("use-after-free in kasan_rcu_reclaim\n");
	ptr = kदो_स्मृति(माप(काष्ठा kasan_rcu_info), GFP_KERNEL);
	अगर (!ptr) अणु
		pr_err("Allocation failed\n");
		वापस;
	पूर्ण

	global_rcu_ptr = rcu_dereference_रक्षित(ptr, शून्य);
	call_rcu(&global_rcu_ptr->rcu, kasan_rcu_reclaim);
पूर्ण

अटल noअंतरभूत व्योम __init kasan_workqueue_work(काष्ठा work_काष्ठा *work)
अणु
	kमुक्त(work);
पूर्ण

अटल noअंतरभूत व्योम __init kasan_workqueue_uaf(व्योम)
अणु
	काष्ठा workqueue_काष्ठा *workqueue;
	काष्ठा work_काष्ठा *work;

	workqueue = create_workqueue("kasan_wq_test");
	अगर (!workqueue) अणु
		pr_err("Allocation failed\n");
		वापस;
	पूर्ण
	work = kदो_स्मृति(माप(काष्ठा work_काष्ठा), GFP_KERNEL);
	अगर (!work) अणु
		pr_err("Allocation failed\n");
		वापस;
	पूर्ण

	INIT_WORK(work, kasan_workqueue_work);
	queue_work(workqueue, work);
	destroy_workqueue(workqueue);

	pr_info("use-after-free on workqueue\n");
	((अस्थिर काष्ठा work_काष्ठा *)work)->data;
पूर्ण

अटल पूर्णांक __init test_kasan_module_init(व्योम)
अणु
	/*
	 * Temporarily enable multi-shot mode. Otherwise, KASAN would only
	 * report the first detected bug and panic the kernel अगर panic_on_warn
	 * is enabled.
	 */
	bool multishot = kasan_save_enable_multi_shot();

	copy_user_test();
	kasan_rcu_uaf();
	kasan_workqueue_uaf();

	kasan_restore_multi_shot(multishot);
	वापस -EAGAIN;
पूर्ण

module_init(test_kasan_module_init);
MODULE_LICENSE("GPL");
