<शैली गुरु>
/*
 * User address space access functions.
 *
 *  For licencing details see kernel-base/COPYING
 */

#समावेश <linux/uaccess.h>
#समावेश <linux/export.h>

#समावेश <यंत्र/tlbflush.h>

/**
 * copy_from_user_nmi - NMI safe copy from user
 * @to:		Poपूर्णांकer to the destination buffer
 * @from:	Poपूर्णांकer to a user space address of the current task
 * @n:		Number of bytes to copy
 *
 * Returns: The number of not copied bytes. 0 is success, i.e. all bytes copied
 *
 * Contrary to other copy_from_user() variants this function can be called
 * from NMI context. Despite the name it is not restricted to be called
 * from NMI context. It is safe to be called from any other context as
 * well. It disables pagefaults across the copy which means a fault will
 * पात the copy.
 *
 * For NMI context invocations this relies on the nested NMI work to allow
 * atomic faults from the NMI path; the nested NMI paths are careful to
 * preserve CR2.
 */
अचिन्हित दीर्घ
copy_from_user_nmi(व्योम *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ n)
अणु
	अचिन्हित दीर्घ ret;

	अगर (__range_not_ok(from, n, TASK_SIZE))
		वापस n;

	अगर (!nmi_uaccess_okay())
		वापस n;

	/*
	 * Even though this function is typically called from NMI/IRQ context
	 * disable pagefaults so that its behaviour is consistent even when
	 * called from other contexts.
	 */
	pagefault_disable();
	ret = __copy_from_user_inatomic(to, from, n);
	pagefault_enable();

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(copy_from_user_nmi);
