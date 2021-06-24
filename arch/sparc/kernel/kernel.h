<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SPARC_KERNEL_H
#घोषणा __SPARC_KERNEL_H

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ftrace.h>

#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/head.h>
#समावेश <यंत्र/पन.स>

/* cpu.c */
बाह्य स्थिर अक्षर *sparc_pmu_type;
बाह्य अचिन्हित पूर्णांक fsr_storage;
बाह्य पूर्णांक ncpus_probed;

/* processअणु_32,_64पूर्ण.c */
यंत्रlinkage दीर्घ sparc_clone(काष्ठा pt_regs *regs);
यंत्रlinkage दीर्घ sparc_विभाजन(काष्ठा pt_regs *regs);
यंत्रlinkage दीर्घ sparc_vविभाजन(काष्ठा pt_regs *regs);

#अगर_घोषित CONFIG_SPARC64
/* setup_64.c */
काष्ठा seq_file;
व्योम cpucap_info(काष्ठा seq_file *);

अटल अंतरभूत अचिन्हित दीर्घ kimage_addr_to_ra(स्थिर व्योम *p)
अणु
	अचिन्हित दीर्घ val = (अचिन्हित दीर्घ) p;

	वापस kern_base + (val - KERNBASE);
पूर्ण

/* sys_sparc_64.c */
यंत्रlinkage दीर्घ sys_kern_features(व्योम);

/* unaligned_64.c */
यंत्रlinkage व्योम kernel_unaligned_trap(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक insn);
पूर्णांक handle_popc(u32 insn, काष्ठा pt_regs *regs);
व्योम handle_lddfmna(काष्ठा pt_regs *regs, अचिन्हित दीर्घ sfar, अचिन्हित दीर्घ sfsr);
व्योम handle_stdfmna(काष्ठा pt_regs *regs, अचिन्हित दीर्घ sfar, अचिन्हित दीर्घ sfsr);

/* smp_64.c */
व्योम __irq_entry smp_call_function_client(पूर्णांक irq, काष्ठा pt_regs *regs);
व्योम __irq_entry smp_call_function_single_client(पूर्णांक irq, काष्ठा pt_regs *regs);
व्योम __irq_entry smp_penguin_jailcell(पूर्णांक irq, काष्ठा pt_regs *regs);
व्योम __irq_entry smp_receive_संकेत_client(पूर्णांक irq, काष्ठा pt_regs *regs);

/* kgdb_64.c */
व्योम __irq_entry smp_kgdb_capture_client(पूर्णांक irq, काष्ठा pt_regs *regs);

/* pci.c */
#अगर_घोषित CONFIG_PCI
पूर्णांक ali_sound_dma_hack(काष्ठा device *dev, u64 device_mask);
#अन्यथा
#घोषणा ali_sound_dma_hack(dev, mask)	(0)
#पूर्ण_अगर

/* संकेत32.c */
व्योम करो_sigवापस32(काष्ठा pt_regs *regs);
यंत्रlinkage व्योम करो_rt_sigवापस32(काष्ठा pt_regs *regs);
व्योम करो_संकेत32(काष्ठा pt_regs * regs);
यंत्रlinkage पूर्णांक करो_sys32_sigstack(u32 u_ssptr, u32 u_ossptr, अचिन्हित दीर्घ sp);

/* समय_64.c */
व्योम __init समय_init_early(व्योम);

/* compat_audit.c */
बाह्य अचिन्हित पूर्णांक sparc32_dir_class[];
बाह्य अचिन्हित पूर्णांक sparc32_chattr_class[];
बाह्य अचिन्हित पूर्णांक sparc32_ग_लिखो_class[];
बाह्य अचिन्हित पूर्णांक sparc32_पढ़ो_class[];
बाह्य अचिन्हित पूर्णांक sparc32_संकेत_class[];
पूर्णांक sparc32_classअगरy_syscall(अचिन्हित पूर्णांक syscall);
#पूर्ण_अगर

#अगर_घोषित CONFIG_SPARC32
/* setup_32.c */
काष्ठा linux_romvec;
व्योम sparc32_start_kernel(काष्ठा linux_romvec *rp);

/* cpu.c */
व्योम cpu_probe(व्योम);

/* traps_32.c */
व्योम handle_hw_भागzero(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc,
                       अचिन्हित दीर्घ npc, अचिन्हित दीर्घ psr);
/* irq_32.c */
बाह्य काष्ठा irqaction अटल_irqaction[];
बाह्य पूर्णांक अटल_irq_count;
बाह्य spinlock_t irq_action_lock;

व्योम unexpected_irq(पूर्णांक irq, व्योम *dev_id, काष्ठा pt_regs * regs);
व्योम init_IRQ(व्योम);

/* sun4m_irq.c */
व्योम sun4m_init_IRQ(व्योम);
व्योम sun4m_unmask_profile_irq(व्योम);
व्योम sun4m_clear_profile_irq(पूर्णांक cpu);

/* sun4m_smp.c */
व्योम sun4m_cpu_pre_starting(व्योम *arg);
व्योम sun4m_cpu_pre_online(व्योम *arg);
व्योम __init smp4m_boot_cpus(व्योम);
पूर्णांक smp4m_boot_one_cpu(पूर्णांक i, काष्ठा task_काष्ठा *idle);
व्योम __init smp4m_smp_करोne(व्योम);
व्योम smp4m_cross_call_irq(व्योम);
व्योम smp4m_percpu_समयr_पूर्णांकerrupt(काष्ठा pt_regs *regs);

/* sun4d_irq.c */
बाह्य spinlock_t sun4d_imsk_lock;

व्योम sun4d_init_IRQ(व्योम);
पूर्णांक sun4d_request_irq(अचिन्हित पूर्णांक irq,
                      irq_handler_t handler,
                      अचिन्हित दीर्घ irqflags,
                      स्थिर अक्षर *devname, व्योम *dev_id);
पूर्णांक show_sun4d_पूर्णांकerrupts(काष्ठा seq_file *, व्योम *);
व्योम sun4d_distribute_irqs(व्योम);
व्योम sun4d_मुक्त_irq(अचिन्हित पूर्णांक irq, व्योम *dev_id);

/* sun4d_smp.c */
व्योम sun4d_cpu_pre_starting(व्योम *arg);
व्योम sun4d_cpu_pre_online(व्योम *arg);
व्योम __init smp4d_boot_cpus(व्योम);
पूर्णांक smp4d_boot_one_cpu(पूर्णांक i, काष्ठा task_काष्ठा *idle);
व्योम __init smp4d_smp_करोne(व्योम);
व्योम smp4d_cross_call_irq(व्योम);
व्योम smp4d_percpu_समयr_पूर्णांकerrupt(काष्ठा pt_regs *regs);

/* leon_smp.c */
व्योम leon_cpu_pre_starting(व्योम *arg);
व्योम leon_cpu_pre_online(व्योम *arg);
व्योम leonsmp_ipi_पूर्णांकerrupt(व्योम);
व्योम leon_cross_call_irq(व्योम);

/* head_32.S */
बाह्य अचिन्हित पूर्णांक t_nmi[];
बाह्य अचिन्हित पूर्णांक linux_trap_ipi15_sun4d[];
बाह्य अचिन्हित पूर्णांक linux_trap_ipi15_sun4m[];

बाह्य काष्ठा tt_entry trapbase;
बाह्य काष्ठा tt_entry trapbase_cpu1;
बाह्य काष्ठा tt_entry trapbase_cpu2;
बाह्य काष्ठा tt_entry trapbase_cpu3;

बाह्य अक्षर cputypval[];

/* entry.S */
बाह्य अचिन्हित दीर्घ lvl14_save[4];
बाह्य अचिन्हित पूर्णांक real_irq_entry[];
बाह्य अचिन्हित पूर्णांक smp4d_ticker[];
बाह्य अचिन्हित पूर्णांक patchme_maybe_smp_msg[];

व्योम floppy_hardपूर्णांक(व्योम);

/* trampoline_32.S */
बाह्य अचिन्हित दीर्घ sun4m_cpu_startup;
बाह्य अचिन्हित दीर्घ sun4d_cpu_startup;

/* संकेत_32.c */
यंत्रlinkage व्योम करो_sigवापस(काष्ठा pt_regs *regs);
यंत्रlinkage व्योम करो_rt_sigवापस(काष्ठा pt_regs *regs);
व्योम करो_notअगरy_resume(काष्ठा pt_regs *regs, अचिन्हित दीर्घ orig_i0,
                      अचिन्हित दीर्घ thपढ़ो_info_flags);
यंत्रlinkage पूर्णांक करो_sys_sigstack(काष्ठा sigstack __user *ssptr,
                               काष्ठा sigstack __user *ossptr,
                               अचिन्हित दीर्घ sp);

/* ptrace_32.c */
यंत्रlinkage पूर्णांक syscall_trace(काष्ठा pt_regs *regs, पूर्णांक syscall_निकास_p);

/* unaligned_32.c */
यंत्रlinkage व्योम kernel_unaligned_trap(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक insn);
यंत्रlinkage व्योम user_unaligned_trap(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक insn);

/* winकरोws.c */
व्योम try_to_clear_winकरोw_buffer(काष्ठा pt_regs *regs, पूर्णांक who);

/* auxio_32.c */
व्योम __init auxio_probe(व्योम);
व्योम __init auxio_घातer_probe(व्योम);

/* pcic.c */
बाह्य व्योम __iomem *pcic_regs;
व्योम pcic_nmi(अचिन्हित पूर्णांक pend, काष्ठा pt_regs *regs);

/* समय_32.c */
व्योम __init समय_init(व्योम);

#अन्यथा /* CONFIG_SPARC32 */
#पूर्ण_अगर /* CONFIG_SPARC32 */
#पूर्ण_अगर /* !(__SPARC_KERNEL_H) */
