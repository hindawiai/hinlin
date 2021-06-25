<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ALPHA_CACHEFLUSH_H
#घोषणा _ALPHA_CACHEFLUSH_H

#समावेश <linux/mm.h>

/* Note that the following two definitions are _highly_ dependent
   on the contexts in which they are used in the kernel.  I personally
   think it is criminal how loosely defined these macros are.  */

/* We need to flush the kernel's icache after loading modules.  The
   only other use of this macro is in load_aout_पूर्णांकerp which is not
   used on Alpha. 

   Note that this definition should *not* be used क्रम userspace
   icache flushing.  While functional, it is _way_ overसमाप्त.  The
   icache is tagged with ASNs and it suffices to allocate a new ASN
   क्रम the process.  */
#अगर_अघोषित CONFIG_SMP
#घोषणा flush_icache_range(start, end)		imb()
#अन्यथा
#घोषणा flush_icache_range(start, end)		smp_imb()
बाह्य व्योम smp_imb(व्योम);
#पूर्ण_अगर

/* We need to flush the userspace icache after setting अवरोधpoपूर्णांकs in
   ptrace.

   Instead of indiscriminately using imb, take advantage of the fact
   that icache entries are tagged with the ASN and load a new mm context.  */
/* ??? Ought to use this in arch/alpha/kernel/संकेत.c too.  */

#अगर_अघोषित CONFIG_SMP
#समावेश <linux/sched.h>

बाह्य व्योम __load_new_mm_context(काष्ठा mm_काष्ठा *);
अटल अंतरभूत व्योम
flush_icache_user_page(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page,
			अचिन्हित दीर्घ addr, पूर्णांक len)
अणु
	अगर (vma->vm_flags & VM_EXEC) अणु
		काष्ठा mm_काष्ठा *mm = vma->vm_mm;
		अगर (current->active_mm == mm)
			__load_new_mm_context(mm);
		अन्यथा
			mm->context[smp_processor_id()] = 0;
	पूर्ण
पूर्ण
#घोषणा flush_icache_user_page flush_icache_user_page
#अन्यथा /* CONFIG_SMP */
बाह्य व्योम flush_icache_user_page(काष्ठा vm_area_काष्ठा *vma,
		काष्ठा page *page, अचिन्हित दीर्घ addr, पूर्णांक len);
#घोषणा flush_icache_user_page flush_icache_user_page
#पूर्ण_अगर /* CONFIG_SMP */

/* This is used only in __करो_fault and करो_swap_page.  */
#घोषणा flush_icache_page(vma, page) \
	flush_icache_user_page((vma), (page), 0, 0)

#समावेश <यंत्र-generic/cacheflush.h>

#पूर्ण_अगर /* _ALPHA_CACHEFLUSH_H */
