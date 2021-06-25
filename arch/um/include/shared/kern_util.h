<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#अगर_अघोषित __KERN_UTIL_H__
#घोषणा __KERN_UTIL_H__

#समावेश <sysdep/ptrace.h>
#समावेश <sysdep/faultinfo.h>

काष्ठा siginfo;

बाह्य पूर्णांक uml_निकासcode;

बाह्य पूर्णांक ncpus;
बाह्य पूर्णांक kदो_स्मृति_ok;

#घोषणा UML_ROUND_UP(addr) \
	((((अचिन्हित दीर्घ) addr) + PAGE_SIZE - 1) & PAGE_MASK)

बाह्य अचिन्हित दीर्घ alloc_stack(पूर्णांक order, पूर्णांक atomic);
बाह्य व्योम मुक्त_stack(अचिन्हित दीर्घ stack, पूर्णांक order);

काष्ठा pt_regs;
बाह्य व्योम करो_संकेत(काष्ठा pt_regs *regs);
बाह्य व्योम पूर्णांकerrupt_end(व्योम);
बाह्य व्योम relay_संकेत(पूर्णांक sig, काष्ठा siginfo *si, काष्ठा uml_pt_regs *regs);

बाह्य अचिन्हित दीर्घ segv(काष्ठा faultinfo fi, अचिन्हित दीर्घ ip,
			  पूर्णांक is_user, काष्ठा uml_pt_regs *regs);
बाह्य पूर्णांक handle_page_fault(अचिन्हित दीर्घ address, अचिन्हित दीर्घ ip,
			     पूर्णांक is_ग_लिखो, पूर्णांक is_user, पूर्णांक *code_out);

बाह्य अचिन्हित पूर्णांक करो_IRQ(पूर्णांक irq, काष्ठा uml_pt_regs *regs);
बाह्य पूर्णांक smp_sigio_handler(व्योम);
बाह्य व्योम initial_thपढ़ो_cb(व्योम (*proc)(व्योम *), व्योम *arg);
बाह्य पूर्णांक is_syscall(अचिन्हित दीर्घ addr);

बाह्य व्योम समयr_handler(पूर्णांक sig, काष्ठा siginfo *unused_si, काष्ठा uml_pt_regs *regs);

बाह्य व्योम uml_pm_wake(व्योम);

बाह्य पूर्णांक start_uml(व्योम);
बाह्य व्योम paging_init(व्योम);

बाह्य व्योम uml_cleanup(व्योम);
बाह्य व्योम करो_uml_निकासcalls(व्योम);

/*
 * Are we disallowed to sleep? Used to choose between GFP_KERNEL and
 * GFP_ATOMIC.
 */
बाह्य पूर्णांक __cant_sleep(व्योम);
बाह्य पूर्णांक get_current_pid(व्योम);
बाह्य पूर्णांक copy_from_user_proc(व्योम *to, व्योम *from, पूर्णांक size);
बाह्य पूर्णांक cpu(व्योम);
बाह्य अक्षर *uml_strdup(स्थिर अक्षर *string);

बाह्य अचिन्हित दीर्घ to_irq_stack(अचिन्हित दीर्घ *mask_out);
बाह्य अचिन्हित दीर्घ from_irq_stack(पूर्णांक nested);

बाह्य व्योम syscall_trace(काष्ठा uml_pt_regs *regs, पूर्णांक entryनिकास);
बाह्य पूर्णांक singlestepping(व्योम *t);

बाह्य व्योम segv_handler(पूर्णांक sig, काष्ठा siginfo *unused_si, काष्ठा uml_pt_regs *regs);
बाह्य व्योम bus_handler(पूर्णांक sig, काष्ठा siginfo *si, काष्ठा uml_pt_regs *regs);
बाह्य व्योम winch(पूर्णांक sig, काष्ठा siginfo *unused_si, काष्ठा uml_pt_regs *regs);
बाह्य व्योम fatal_sigsegv(व्योम) __attribute__ ((noवापस));

व्योम um_idle_sleep(व्योम);

#पूर्ण_अगर
