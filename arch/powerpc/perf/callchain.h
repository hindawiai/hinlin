<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _POWERPC_PERF_CALLCHAIN_H
#घोषणा _POWERPC_PERF_CALLCHAIN_H

पूर्णांक पढ़ो_user_stack_slow(स्थिर व्योम __user *ptr, व्योम *buf, पूर्णांक nb);
व्योम perf_callchain_user_64(काष्ठा perf_callchain_entry_ctx *entry,
			    काष्ठा pt_regs *regs);
व्योम perf_callchain_user_32(काष्ठा perf_callchain_entry_ctx *entry,
			    काष्ठा pt_regs *regs);

अटल अंतरभूत bool invalid_user_sp(अचिन्हित दीर्घ sp)
अणु
	अचिन्हित दीर्घ mask = is_32bit_task() ? 3 : 7;
	अचिन्हित दीर्घ top = STACK_TOP - (is_32bit_task() ? 16 : 32);

	वापस (!sp || (sp & mask) || (sp > top));
पूर्ण

/*
 * On 32-bit we just access the address and let hash_page create a
 * HPTE अगर necessary, so there is no need to fall back to पढ़ोing
 * the page tables.  Since this is called at पूर्णांकerrupt level,
 * करो_page_fault() won't treat a DSI as a page fault.
 */
अटल अंतरभूत पूर्णांक __पढ़ो_user_stack(स्थिर व्योम __user *ptr, व्योम *ret,
				    माप_प्रकार size)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)ptr;
	पूर्णांक rc;

	अगर (addr > TASK_SIZE - size || (addr & (size - 1)))
		वापस -EFAULT;

	rc = copy_from_user_nofault(ret, ptr, size);

	अगर (IS_ENABLED(CONFIG_PPC64) && !radix_enabled() && rc)
		वापस पढ़ो_user_stack_slow(ptr, ret, size);

	वापस rc;
पूर्ण

#पूर्ण_अगर /* _POWERPC_PERF_CALLCHAIN_H */
