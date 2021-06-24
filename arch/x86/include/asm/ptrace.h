<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_PTRACE_H
#घोषणा _ASM_X86_PTRACE_H

#समावेश <यंत्र/segment.h>
#समावेश <यंत्र/page_types.h>
#समावेश <uapi/यंत्र/ptrace.h>

#अगर_अघोषित __ASSEMBLY__
#अगर_घोषित __i386__

काष्ठा pt_regs अणु
	/*
	 * NB: 32-bit x86 CPUs are inconsistent as what happens in the
	 * following हालs (where %seg represents a segment रेजिस्टर):
	 *
	 * - pushl %seg: some करो a 16-bit ग_लिखो and leave the high
	 *   bits alone
	 * - movl %seg, [mem]: some करो a 16-bit ग_लिखो despite the movl
	 * - IDT entry: some (e.g. 486) will leave the high bits of CS
	 *   and (अगर applicable) SS undefined.
	 *
	 * Fortunately, x86-32 करोesn't पढ़ो the high bits on POP or IRET,
	 * so we can just treat all of the segment रेजिस्टरs as 16-bit
	 * values.
	 */
	अचिन्हित दीर्घ bx;
	अचिन्हित दीर्घ cx;
	अचिन्हित दीर्घ dx;
	अचिन्हित दीर्घ si;
	अचिन्हित दीर्घ di;
	अचिन्हित दीर्घ bp;
	अचिन्हित दीर्घ ax;
	अचिन्हित लघु ds;
	अचिन्हित लघु __dsh;
	अचिन्हित लघु es;
	अचिन्हित लघु __esh;
	अचिन्हित लघु fs;
	अचिन्हित लघु __fsh;
	/*
	 * On पूर्णांकerrupt, gs and __gsh store the vector number.  They never
	 * store gs any more.
	 */
	अचिन्हित लघु gs;
	अचिन्हित लघु __gsh;
	/* On पूर्णांकerrupt, this is the error code. */
	अचिन्हित दीर्घ orig_ax;
	अचिन्हित दीर्घ ip;
	अचिन्हित लघु cs;
	अचिन्हित लघु __csh;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ sp;
	अचिन्हित लघु ss;
	अचिन्हित लघु __ssh;
पूर्ण;

#अन्यथा /* __i386__ */

काष्ठा pt_regs अणु
/*
 * C ABI says these regs are callee-preserved. They aren't saved on kernel entry
 * unless syscall needs a complete, fully filled "struct pt_regs".
 */
	अचिन्हित दीर्घ r15;
	अचिन्हित दीर्घ r14;
	अचिन्हित दीर्घ r13;
	अचिन्हित दीर्घ r12;
	अचिन्हित दीर्घ bp;
	अचिन्हित दीर्घ bx;
/* These regs are callee-clobbered. Always saved on kernel entry. */
	अचिन्हित दीर्घ r11;
	अचिन्हित दीर्घ r10;
	अचिन्हित दीर्घ r9;
	अचिन्हित दीर्घ r8;
	अचिन्हित दीर्घ ax;
	अचिन्हित दीर्घ cx;
	अचिन्हित दीर्घ dx;
	अचिन्हित दीर्घ si;
	अचिन्हित दीर्घ di;
/*
 * On syscall entry, this is syscall#. On CPU exception, this is error code.
 * On hw पूर्णांकerrupt, it's IRQ number:
 */
	अचिन्हित दीर्घ orig_ax;
/* Return frame क्रम iretq */
	अचिन्हित दीर्घ ip;
	अचिन्हित दीर्घ cs;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ sp;
	अचिन्हित दीर्घ ss;
/* top of stack page */
पूर्ण;

#पूर्ण_अगर /* !__i386__ */

#अगर_घोषित CONFIG_PARAVIRT
#समावेश <यंत्र/paravirt_types.h>
#पूर्ण_अगर

#समावेश <यंत्र/proto.h>

काष्ठा cpuinfo_x86;
काष्ठा task_काष्ठा;

बाह्य अचिन्हित दीर्घ profile_pc(काष्ठा pt_regs *regs);

बाह्य अचिन्हित दीर्घ
convert_ip_to_linear(काष्ठा task_काष्ठा *child, काष्ठा pt_regs *regs);
बाह्य व्योम send_sigtrap(काष्ठा pt_regs *regs, पूर्णांक error_code, पूर्णांक si_code);


अटल अंतरभूत अचिन्हित दीर्घ regs_वापस_value(काष्ठा pt_regs *regs)
अणु
	वापस regs->ax;
पूर्ण

अटल अंतरभूत व्योम regs_set_वापस_value(काष्ठा pt_regs *regs, अचिन्हित दीर्घ rc)
अणु
	regs->ax = rc;
पूर्ण

/*
 * user_mode(regs) determines whether a रेजिस्टर set came from user
 * mode.  On x86_32, this is true अगर V8086 mode was enabled OR अगर the
 * रेजिस्टर set was from रक्षित mode with RPL-3 CS value.  This
 * tricky test checks that with one comparison.
 *
 * On x86_64, vm86 mode is mercअगरully nonexistent, and we करोn't need
 * the extra check.
 */
अटल __always_अंतरभूत पूर्णांक user_mode(काष्ठा pt_regs *regs)
अणु
#अगर_घोषित CONFIG_X86_32
	वापस ((regs->cs & SEGMENT_RPL_MASK) | (regs->flags & X86_VM_MASK)) >= USER_RPL;
#अन्यथा
	वापस !!(regs->cs & 3);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक v8086_mode(काष्ठा pt_regs *regs)
अणु
#अगर_घोषित CONFIG_X86_32
	वापस (regs->flags & X86_VM_MASK);
#अन्यथा
	वापस 0;	/* No V86 mode support in दीर्घ mode */
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत bool user_64bit_mode(काष्ठा pt_regs *regs)
अणु
#अगर_घोषित CONFIG_X86_64
#अगर_अघोषित CONFIG_PARAVIRT_XXL
	/*
	 * On non-paravirt प्रणालीs, this is the only दीर्घ mode CPL 3
	 * selector.  We करो not allow दीर्घ mode selectors in the LDT.
	 */
	वापस regs->cs == __USER_CS;
#अन्यथा
	/* Headers are too twisted क्रम this to go in paravirt.h. */
	वापस regs->cs == __USER_CS || regs->cs == pv_info.extra_user_64bit_cs;
#पूर्ण_अगर
#अन्यथा /* !CONFIG_X86_64 */
	वापस false;
#पूर्ण_अगर
पूर्ण

/*
 * Determine whether the रेजिस्टर set came from any context that is running in
 * 64-bit mode.
 */
अटल अंतरभूत bool any_64bit_mode(काष्ठा pt_regs *regs)
अणु
#अगर_घोषित CONFIG_X86_64
	वापस !user_mode(regs) || user_64bit_mode(regs);
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_X86_64
#घोषणा current_user_stack_poपूर्णांकer()	current_pt_regs()->sp
#घोषणा compat_user_stack_poपूर्णांकer()	current_pt_regs()->sp

अटल अंतरभूत bool ip_within_syscall_gap(काष्ठा pt_regs *regs)
अणु
	bool ret = (regs->ip >= (अचिन्हित दीर्घ)entry_SYSCALL_64 &&
		    regs->ip <  (अचिन्हित दीर्घ)entry_SYSCALL_64_safe_stack);

#अगर_घोषित CONFIG_IA32_EMULATION
	ret = ret || (regs->ip >= (अचिन्हित दीर्घ)entry_SYSCALL_compat &&
		      regs->ip <  (अचिन्हित दीर्घ)entry_SYSCALL_compat_safe_stack);
#पूर्ण_अगर

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत अचिन्हित दीर्घ kernel_stack_poपूर्णांकer(काष्ठा pt_regs *regs)
अणु
	वापस regs->sp;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ inकाष्ठाion_poपूर्णांकer(काष्ठा pt_regs *regs)
अणु
	वापस regs->ip;
पूर्ण

अटल अंतरभूत व्योम inकाष्ठाion_poपूर्णांकer_set(काष्ठा pt_regs *regs,
		अचिन्हित दीर्घ val)
अणु
	regs->ip = val;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ frame_poपूर्णांकer(काष्ठा pt_regs *regs)
अणु
	वापस regs->bp;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ user_stack_poपूर्णांकer(काष्ठा pt_regs *regs)
अणु
	वापस regs->sp;
पूर्ण

अटल अंतरभूत व्योम user_stack_poपूर्णांकer_set(काष्ठा pt_regs *regs,
		अचिन्हित दीर्घ val)
अणु
	regs->sp = val;
पूर्ण

अटल __always_अंतरभूत bool regs_irqs_disabled(काष्ठा pt_regs *regs)
अणु
	वापस !(regs->flags & X86_EFLAGS_IF);
पूर्ण

/* Query offset/name of रेजिस्टर from its name/offset */
बाह्य पूर्णांक regs_query_रेजिस्टर_offset(स्थिर अक्षर *name);
बाह्य स्थिर अक्षर *regs_query_रेजिस्टर_name(अचिन्हित पूर्णांक offset);
#घोषणा MAX_REG_OFFSET (दुरत्व(काष्ठा pt_regs, ss))

/**
 * regs_get_रेजिस्टर() - get रेजिस्टर value from its offset
 * @regs:	pt_regs from which रेजिस्टर value is gotten.
 * @offset:	offset number of the रेजिस्टर.
 *
 * regs_get_रेजिस्टर वापसs the value of a रेजिस्टर. The @offset is the
 * offset of the रेजिस्टर in काष्ठा pt_regs address which specअगरied by @regs.
 * If @offset is bigger than MAX_REG_OFFSET, this वापसs 0.
 */
अटल अंतरभूत अचिन्हित दीर्घ regs_get_रेजिस्टर(काष्ठा pt_regs *regs,
					      अचिन्हित पूर्णांक offset)
अणु
	अगर (unlikely(offset > MAX_REG_OFFSET))
		वापस 0;
#अगर_घोषित CONFIG_X86_32
	/* The selector fields are 16-bit. */
	अगर (offset == दुरत्व(काष्ठा pt_regs, cs) ||
	    offset == दुरत्व(काष्ठा pt_regs, ss) ||
	    offset == दुरत्व(काष्ठा pt_regs, ds) ||
	    offset == दुरत्व(काष्ठा pt_regs, es) ||
	    offset == दुरत्व(काष्ठा pt_regs, fs) ||
	    offset == दुरत्व(काष्ठा pt_regs, gs)) अणु
		वापस *(u16 *)((अचिन्हित दीर्घ)regs + offset);

	पूर्ण
#पूर्ण_अगर
	वापस *(अचिन्हित दीर्घ *)((अचिन्हित दीर्घ)regs + offset);
पूर्ण

/**
 * regs_within_kernel_stack() - check the address in the stack
 * @regs:	pt_regs which contains kernel stack poपूर्णांकer.
 * @addr:	address which is checked.
 *
 * regs_within_kernel_stack() checks @addr is within the kernel stack page(s).
 * If @addr is within the kernel stack, it वापसs true. If not, वापसs false.
 */
अटल अंतरभूत पूर्णांक regs_within_kernel_stack(काष्ठा pt_regs *regs,
					   अचिन्हित दीर्घ addr)
अणु
	वापस ((addr & ~(THREAD_SIZE - 1)) == (regs->sp & ~(THREAD_SIZE - 1)));
पूर्ण

/**
 * regs_get_kernel_stack_nth_addr() - get the address of the Nth entry on stack
 * @regs:	pt_regs which contains kernel stack poपूर्णांकer.
 * @n:		stack entry number.
 *
 * regs_get_kernel_stack_nth() वापसs the address of the @n th entry of the
 * kernel stack which is specअगरied by @regs. If the @n th entry is NOT in
 * the kernel stack, this वापसs शून्य.
 */
अटल अंतरभूत अचिन्हित दीर्घ *regs_get_kernel_stack_nth_addr(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक n)
अणु
	अचिन्हित दीर्घ *addr = (अचिन्हित दीर्घ *)regs->sp;

	addr += n;
	अगर (regs_within_kernel_stack(regs, (अचिन्हित दीर्घ)addr))
		वापस addr;
	अन्यथा
		वापस शून्य;
पूर्ण

/* To aव्योम include hell, we can't include uaccess.h */
बाह्य दीर्घ copy_from_kernel_nofault(व्योम *dst, स्थिर व्योम *src, माप_प्रकार size);

/**
 * regs_get_kernel_stack_nth() - get Nth entry of the stack
 * @regs:	pt_regs which contains kernel stack poपूर्णांकer.
 * @n:		stack entry number.
 *
 * regs_get_kernel_stack_nth() वापसs @n th entry of the kernel stack which
 * is specअगरied by @regs. If the @n th entry is NOT in the kernel stack
 * this वापसs 0.
 */
अटल अंतरभूत अचिन्हित दीर्घ regs_get_kernel_stack_nth(काष्ठा pt_regs *regs,
						      अचिन्हित पूर्णांक n)
अणु
	अचिन्हित दीर्घ *addr;
	अचिन्हित दीर्घ val;
	दीर्घ ret;

	addr = regs_get_kernel_stack_nth_addr(regs, n);
	अगर (addr) अणु
		ret = copy_from_kernel_nofault(&val, addr, माप(val));
		अगर (!ret)
			वापस val;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * regs_get_kernel_argument() - get Nth function argument in kernel
 * @regs:	pt_regs of that context
 * @n:		function argument number (start from 0)
 *
 * regs_get_argument() वापसs @n th argument of the function call.
 * Note that this chooses most probably assignment, in some हाल
 * it can be incorrect.
 * This is expected to be called from kprobes or ftrace with regs
 * where the top of stack is the वापस address.
 */
अटल अंतरभूत अचिन्हित दीर्घ regs_get_kernel_argument(काष्ठा pt_regs *regs,
						     अचिन्हित पूर्णांक n)
अणु
	अटल स्थिर अचिन्हित पूर्णांक argument_offs[] = अणु
#अगर_घोषित __i386__
		दुरत्व(काष्ठा pt_regs, ax),
		दुरत्व(काष्ठा pt_regs, dx),
		दुरत्व(काष्ठा pt_regs, cx),
#घोषणा NR_REG_ARGUMENTS 3
#अन्यथा
		दुरत्व(काष्ठा pt_regs, di),
		दुरत्व(काष्ठा pt_regs, si),
		दुरत्व(काष्ठा pt_regs, dx),
		दुरत्व(काष्ठा pt_regs, cx),
		दुरत्व(काष्ठा pt_regs, r8),
		दुरत्व(काष्ठा pt_regs, r9),
#घोषणा NR_REG_ARGUMENTS 6
#पूर्ण_अगर
	पूर्ण;

	अगर (n >= NR_REG_ARGUMENTS) अणु
		n -= NR_REG_ARGUMENTS - 1;
		वापस regs_get_kernel_stack_nth(regs, n);
	पूर्ण अन्यथा
		वापस regs_get_रेजिस्टर(regs, argument_offs[n]);
पूर्ण

#घोषणा arch_has_single_step()	(1)
#अगर_घोषित CONFIG_X86_DEBUGCTLMSR
#घोषणा arch_has_block_step()	(1)
#अन्यथा
#घोषणा arch_has_block_step()	(boot_cpu_data.x86 >= 6)
#पूर्ण_अगर

#घोषणा ARCH_HAS_USER_SINGLE_STEP_REPORT

काष्ठा user_desc;
बाह्य पूर्णांक करो_get_thपढ़ो_area(काष्ठा task_काष्ठा *p, पूर्णांक idx,
			      काष्ठा user_desc __user *info);
बाह्य पूर्णांक करो_set_thपढ़ो_area(काष्ठा task_काष्ठा *p, पूर्णांक idx,
			      काष्ठा user_desc __user *info, पूर्णांक can_allocate);

#अगर_घोषित CONFIG_X86_64
# define करो_set_thपढ़ो_area_64(p, s, t)	करो_arch_prctl_64(p, s, t)
#अन्यथा
# define करो_set_thपढ़ो_area_64(p, s, t)	(0)
#पूर्ण_अगर

#पूर्ण_अगर /* !__ASSEMBLY__ */
#पूर्ण_अगर /* _ASM_X86_PTRACE_H */
