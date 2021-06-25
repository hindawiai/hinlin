<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 1999, 2000  Niibe Yutaka
 */
#अगर_अघोषित __ASM_SH_PTRACE_H
#घोषणा __ASM_SH_PTRACE_H


#समावेश <linux/stringअगरy.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/thपढ़ो_info.h>
#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/page.h>
#समावेश <uapi/यंत्र/ptrace.h>

#घोषणा user_mode(regs)			(((regs)->sr & 0x40000000)==0)
#घोषणा kernel_stack_poपूर्णांकer(_regs)	((अचिन्हित दीर्घ)(_regs)->regs[15])

अटल अंतरभूत अचिन्हित दीर्घ inकाष्ठाion_poपूर्णांकer(काष्ठा pt_regs *regs)
अणु
	वापस regs->pc;
पूर्ण
अटल अंतरभूत व्योम inकाष्ठाion_poपूर्णांकer_set(काष्ठा pt_regs *regs,
		अचिन्हित दीर्घ val)
अणु
	regs->pc = val;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ frame_poपूर्णांकer(काष्ठा pt_regs *regs)
अणु
	वापस regs->regs[14];
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ user_stack_poपूर्णांकer(काष्ठा pt_regs *regs)
अणु
	वापस regs->regs[15];
पूर्ण

अटल अंतरभूत व्योम user_stack_poपूर्णांकer_set(काष्ठा pt_regs *regs,
		अचिन्हित दीर्घ val)
अणु
	regs->regs[15] = val;
पूर्ण

#घोषणा arch_has_single_step()	(1)

/*
 * kprobe-based event tracer support
 */
काष्ठा pt_regs_offset अणु
	स्थिर अक्षर *name;
	पूर्णांक offset;
पूर्ण;

#घोषणा REG_OFFSET_NAME(r) अणु.name = #r, .offset = दुरत्व(काष्ठा pt_regs, r)पूर्ण
#घोषणा REGS_OFFSET_NAME(num)	\
	अणु.name = __stringअगरy(r##num), .offset = दुरत्व(काष्ठा pt_regs, regs[num])पूर्ण
#घोषणा TREGS_OFFSET_NAME(num)	\
	अणु.name = __stringअगरy(tr##num), .offset = दुरत्व(काष्ठा pt_regs, tregs[num])पूर्ण
#घोषणा REG_OFFSET_END अणु.name = शून्य, .offset = 0पूर्ण

/* Query offset/name of रेजिस्टर from its name/offset */
बाह्य पूर्णांक regs_query_रेजिस्टर_offset(स्थिर अक्षर *name);
बाह्य स्थिर अक्षर *regs_query_रेजिस्टर_name(अचिन्हित पूर्णांक offset);

बाह्य स्थिर काष्ठा pt_regs_offset regoffset_table[];

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
	वापस ((addr & ~(THREAD_SIZE - 1))  ==
		(kernel_stack_poपूर्णांकer(regs) & ~(THREAD_SIZE - 1)));
पूर्ण

/**
 * regs_get_kernel_stack_nth() - get Nth entry of the stack
 * @regs:	pt_regs which contains kernel stack poपूर्णांकer.
 * @n:		stack entry number.
 *
 * regs_get_kernel_stack_nth() वापसs @n th entry of the kernel stack which
 * is specअगरied by @regs. If the @n th entry is NOT in the kernel stack,
 * this वापसs 0.
 */
अटल अंतरभूत अचिन्हित दीर्घ regs_get_kernel_stack_nth(काष्ठा pt_regs *regs,
						      अचिन्हित पूर्णांक n)
अणु
	अचिन्हित दीर्घ *addr = (अचिन्हित दीर्घ *)kernel_stack_poपूर्णांकer(regs);
	addr += n;
	अगर (regs_within_kernel_stack(regs, (अचिन्हित दीर्घ)addr))
		वापस *addr;
	अन्यथा
		वापस 0;
पूर्ण

काष्ठा perf_event;
काष्ठा perf_sample_data;

बाह्य व्योम ptrace_triggered(काष्ठा perf_event *bp,
		      काष्ठा perf_sample_data *data, काष्ठा pt_regs *regs);

#घोषणा task_pt_regs(task) \
	((काष्ठा pt_regs *) (task_stack_page(task) + THREAD_SIZE) - 1)

अटल अंतरभूत अचिन्हित दीर्घ profile_pc(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ pc = regs->pc;

	अगर (virt_addr_uncached(pc))
		वापस CAC_ADDR(pc);

	वापस pc;
पूर्ण

#पूर्ण_अगर /* __ASM_SH_PTRACE_H */
