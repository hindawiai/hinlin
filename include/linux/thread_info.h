<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* thपढ़ो_info.h: common low-level thपढ़ो inक्रमmation accessors
 *
 * Copyright (C) 2002  David Howells (dhowells@redhat.com)
 * - Incorporating suggestions made by Linus Torvalds
 */

#अगर_अघोषित _LINUX_THREAD_INFO_H
#घोषणा _LINUX_THREAD_INFO_H

#समावेश <linux/types.h>
#समावेश <linux/bug.h>
#समावेश <linux/restart_block.h>
#समावेश <linux/त्रुटिसं.स>

#अगर_घोषित CONFIG_THREAD_INFO_IN_TASK
/*
 * For CONFIG_THREAD_INFO_IN_TASK kernels we need <यंत्र/current.h> क्रम the
 * definition of current, but क्रम !CONFIG_THREAD_INFO_IN_TASK kernels,
 * including <यंत्र/current.h> can cause a circular dependency on some platक्रमms.
 */
#समावेश <यंत्र/current.h>
#घोषणा current_thपढ़ो_info() ((काष्ठा thपढ़ो_info *)current)
#पूर्ण_अगर

#समावेश <linux/bitops.h>

/*
 * For per-arch arch_within_stack_frames() implementations, defined in
 * यंत्र/thपढ़ो_info.h.
 */
क्रमागत अणु
	BAD_STACK = -1,
	NOT_STACK = 0,
	GOOD_FRAME,
	GOOD_STACK,
पूर्ण;

#अगर_घोषित CONFIG_GENERIC_ENTRY
क्रमागत syscall_work_bit अणु
	SYSCALL_WORK_BIT_SECCOMP,
	SYSCALL_WORK_BIT_SYSCALL_TRACEPOINT,
	SYSCALL_WORK_BIT_SYSCALL_TRACE,
	SYSCALL_WORK_BIT_SYSCALL_EMU,
	SYSCALL_WORK_BIT_SYSCALL_AUDIT,
	SYSCALL_WORK_BIT_SYSCALL_USER_DISPATCH,
	SYSCALL_WORK_BIT_SYSCALL_EXIT_TRAP,
पूर्ण;

#घोषणा SYSCALL_WORK_SECCOMP		BIT(SYSCALL_WORK_BIT_SECCOMP)
#घोषणा SYSCALL_WORK_SYSCALL_TRACEPOINT	BIT(SYSCALL_WORK_BIT_SYSCALL_TRACEPOINT)
#घोषणा SYSCALL_WORK_SYSCALL_TRACE	BIT(SYSCALL_WORK_BIT_SYSCALL_TRACE)
#घोषणा SYSCALL_WORK_SYSCALL_EMU	BIT(SYSCALL_WORK_BIT_SYSCALL_EMU)
#घोषणा SYSCALL_WORK_SYSCALL_AUDIT	BIT(SYSCALL_WORK_BIT_SYSCALL_AUDIT)
#घोषणा SYSCALL_WORK_SYSCALL_USER_DISPATCH BIT(SYSCALL_WORK_BIT_SYSCALL_USER_DISPATCH)
#घोषणा SYSCALL_WORK_SYSCALL_EXIT_TRAP	BIT(SYSCALL_WORK_BIT_SYSCALL_EXIT_TRAP)
#पूर्ण_अगर

#समावेश <यंत्र/thपढ़ो_info.h>

#अगर_घोषित __KERNEL__

#अगर_अघोषित arch_set_restart_data
#घोषणा arch_set_restart_data(restart) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

अटल अंतरभूत दीर्घ set_restart_fn(काष्ठा restart_block *restart,
					दीर्घ (*fn)(काष्ठा restart_block *))
अणु
	restart->fn = fn;
	arch_set_restart_data(restart);
	वापस -ERESTART_RESTARTBLOCK;
पूर्ण

#अगर_अघोषित THREAD_ALIGN
#घोषणा THREAD_ALIGN	THREAD_SIZE
#पूर्ण_अगर

#घोषणा THREADINFO_GFP		(GFP_KERNEL_ACCOUNT | __GFP_ZERO)

/*
 * flag set/clear/test wrappers
 * - pass TIF_xxxx स्थिरants to these functions
 */

अटल अंतरभूत व्योम set_ti_thपढ़ो_flag(काष्ठा thपढ़ो_info *ti, पूर्णांक flag)
अणु
	set_bit(flag, (अचिन्हित दीर्घ *)&ti->flags);
पूर्ण

अटल अंतरभूत व्योम clear_ti_thपढ़ो_flag(काष्ठा thपढ़ो_info *ti, पूर्णांक flag)
अणु
	clear_bit(flag, (अचिन्हित दीर्घ *)&ti->flags);
पूर्ण

अटल अंतरभूत व्योम update_ti_thपढ़ो_flag(काष्ठा thपढ़ो_info *ti, पूर्णांक flag,
					 bool value)
अणु
	अगर (value)
		set_ti_thपढ़ो_flag(ti, flag);
	अन्यथा
		clear_ti_thपढ़ो_flag(ti, flag);
पूर्ण

अटल अंतरभूत पूर्णांक test_and_set_ti_thपढ़ो_flag(काष्ठा thपढ़ो_info *ti, पूर्णांक flag)
अणु
	वापस test_and_set_bit(flag, (अचिन्हित दीर्घ *)&ti->flags);
पूर्ण

अटल अंतरभूत पूर्णांक test_and_clear_ti_thपढ़ो_flag(काष्ठा thपढ़ो_info *ti, पूर्णांक flag)
अणु
	वापस test_and_clear_bit(flag, (अचिन्हित दीर्घ *)&ti->flags);
पूर्ण

अटल अंतरभूत पूर्णांक test_ti_thपढ़ो_flag(काष्ठा thपढ़ो_info *ti, पूर्णांक flag)
अणु
	वापस test_bit(flag, (अचिन्हित दीर्घ *)&ti->flags);
पूर्ण

#घोषणा set_thपढ़ो_flag(flag) \
	set_ti_thपढ़ो_flag(current_thपढ़ो_info(), flag)
#घोषणा clear_thपढ़ो_flag(flag) \
	clear_ti_thपढ़ो_flag(current_thपढ़ो_info(), flag)
#घोषणा update_thपढ़ो_flag(flag, value) \
	update_ti_thपढ़ो_flag(current_thपढ़ो_info(), flag, value)
#घोषणा test_and_set_thपढ़ो_flag(flag) \
	test_and_set_ti_thपढ़ो_flag(current_thपढ़ो_info(), flag)
#घोषणा test_and_clear_thपढ़ो_flag(flag) \
	test_and_clear_ti_thपढ़ो_flag(current_thपढ़ो_info(), flag)
#घोषणा test_thपढ़ो_flag(flag) \
	test_ti_thपढ़ो_flag(current_thपढ़ो_info(), flag)

#अगर_घोषित CONFIG_GENERIC_ENTRY
#घोषणा set_syscall_work(fl) \
	set_bit(SYSCALL_WORK_BIT_##fl, &current_thपढ़ो_info()->syscall_work)
#घोषणा test_syscall_work(fl) \
	test_bit(SYSCALL_WORK_BIT_##fl, &current_thपढ़ो_info()->syscall_work)
#घोषणा clear_syscall_work(fl) \
	clear_bit(SYSCALL_WORK_BIT_##fl, &current_thपढ़ो_info()->syscall_work)

#घोषणा set_task_syscall_work(t, fl) \
	set_bit(SYSCALL_WORK_BIT_##fl, &task_thपढ़ो_info(t)->syscall_work)
#घोषणा test_task_syscall_work(t, fl) \
	test_bit(SYSCALL_WORK_BIT_##fl, &task_thपढ़ो_info(t)->syscall_work)
#घोषणा clear_task_syscall_work(t, fl) \
	clear_bit(SYSCALL_WORK_BIT_##fl, &task_thपढ़ो_info(t)->syscall_work)

#अन्यथा /* CONFIG_GENERIC_ENTRY */

#घोषणा set_syscall_work(fl)						\
	set_ti_thपढ़ो_flag(current_thपढ़ो_info(), TIF_##fl)
#घोषणा test_syscall_work(fl) \
	test_ti_thपढ़ो_flag(current_thपढ़ो_info(), TIF_##fl)
#घोषणा clear_syscall_work(fl) \
	clear_ti_thपढ़ो_flag(current_thपढ़ो_info(), TIF_##fl)

#घोषणा set_task_syscall_work(t, fl) \
	set_ti_thपढ़ो_flag(task_thपढ़ो_info(t), TIF_##fl)
#घोषणा test_task_syscall_work(t, fl) \
	test_ti_thपढ़ो_flag(task_thपढ़ो_info(t), TIF_##fl)
#घोषणा clear_task_syscall_work(t, fl) \
	clear_ti_thपढ़ो_flag(task_thपढ़ो_info(t), TIF_##fl)
#पूर्ण_अगर /* !CONFIG_GENERIC_ENTRY */

#घोषणा tअगर_need_resched() test_thपढ़ो_flag(TIF_NEED_RESCHED)

#अगर_अघोषित CONFIG_HAVE_ARCH_WITHIN_STACK_FRAMES
अटल अंतरभूत पूर्णांक arch_within_stack_frames(स्थिर व्योम * स्थिर stack,
					   स्थिर व्योम * स्थिर stackend,
					   स्थिर व्योम *obj, अचिन्हित दीर्घ len)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_HARDENED_USERCOPY
बाह्य व्योम __check_object_size(स्थिर व्योम *ptr, अचिन्हित दीर्घ n,
					bool to_user);

अटल __always_अंतरभूत व्योम check_object_size(स्थिर व्योम *ptr, अचिन्हित दीर्घ n,
					      bool to_user)
अणु
	अगर (!__builtin_स्थिरant_p(n))
		__check_object_size(ptr, n, to_user);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम check_object_size(स्थिर व्योम *ptr, अचिन्हित दीर्घ n,
				     bool to_user)
अणु पूर्ण
#पूर्ण_अगर /* CONFIG_HARDENED_USERCOPY */

बाह्य व्योम __compileसमय_error("copy source size is too small")
__bad_copy_from(व्योम);
बाह्य व्योम __compileसमय_error("copy destination size is too small")
__bad_copy_to(व्योम);

अटल अंतरभूत व्योम copy_overflow(पूर्णांक size, अचिन्हित दीर्घ count)
अणु
	WARN(1, "Buffer overflow detected (%d < %lu)!\n", size, count);
पूर्ण

अटल __always_अंतरभूत __must_check bool
check_copy_size(स्थिर व्योम *addr, माप_प्रकार bytes, bool is_source)
अणु
	पूर्णांक sz = __compileसमय_object_size(addr);
	अगर (unlikely(sz >= 0 && sz < bytes)) अणु
		अगर (!__builtin_स्थिरant_p(bytes))
			copy_overflow(sz, bytes);
		अन्यथा अगर (is_source)
			__bad_copy_from();
		अन्यथा
			__bad_copy_to();
		वापस false;
	पूर्ण
	अगर (WARN_ON_ONCE(bytes > पूर्णांक_उच्च))
		वापस false;
	check_object_size(addr, bytes, is_source);
	वापस true;
पूर्ण

#अगर_अघोषित arch_setup_new_exec
अटल अंतरभूत व्योम arch_setup_new_exec(व्योम) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर	/* __KERNEL__ */

#पूर्ण_अगर /* _LINUX_THREAD_INFO_H */
