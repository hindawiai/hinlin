<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    Copyright IBM Corp. 2004, 2011
 *    Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>,
 *		 Holger Smolinski <Holger.Smolinski@de.ibm.com>,
 *		 Thomas Spatzier <tspat@de.ibm.com>,
 *
 * This file contains पूर्णांकerrupt related functions.
 */

#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/profile.h>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/cpu.h>
#समावेश <linux/irq.h>
#समावेश <linux/entry-common.h>
#समावेश <यंत्र/irq_regs.h>
#समावेश <यंत्र/cpuसमय.स>
#समावेश <यंत्र/lowcore.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/hw_irq.h>
#समावेश <यंत्र/stacktrace.h>
#समावेश <यंत्र/softirq_stack.h>
#समावेश "entry.h"

DEFINE_PER_CPU_SHARED_ALIGNED(काष्ठा irq_stat, irq_stat);
EXPORT_PER_CPU_SYMBOL_GPL(irq_stat);

काष्ठा irq_class अणु
	पूर्णांक irq;
	अक्षर *name;
	अक्षर *desc;
पूर्ण;

/*
 * The list of "main" irq classes on s390. This is the list of पूर्णांकerrupts
 * that appear both in /proc/stat ("intr" line) and /proc/पूर्णांकerrupts.
 * Historically only बाह्यal and I/O पूर्णांकerrupts have been part of /proc/stat.
 * We can't add the split बाह्यal and I/O sub classes since the first field
 * in the "intr" line in /proc/stat is supposed to be the sum of all other
 * fields.
 * Since the बाह्यal and I/O पूर्णांकerrupt fields are alपढ़ोy sums we would end
 * up with having a sum which accounts each पूर्णांकerrupt twice.
 */
अटल स्थिर काष्ठा irq_class irqclass_मुख्य_desc[NR_IRQS_BASE] = अणु
	अणु.irq = EXT_INTERRUPT,	.name = "EXT"पूर्ण,
	अणु.irq = IO_INTERRUPT,	.name = "I/O"पूर्ण,
	अणु.irq = THIN_INTERRUPT, .name = "AIO"पूर्ण,
पूर्ण;

/*
 * The list of split बाह्यal and I/O पूर्णांकerrupts that appear only in
 * /proc/पूर्णांकerrupts.
 * In addition this list contains non बाह्यal / I/O events like NMIs.
 */
अटल स्थिर काष्ठा irq_class irqclass_sub_desc[] = अणु
	अणु.irq = IRQEXT_CLK, .name = "CLK", .desc = "[EXT] Clock Comparator"पूर्ण,
	अणु.irq = IRQEXT_EXC, .name = "EXC", .desc = "[EXT] External Call"पूर्ण,
	अणु.irq = IRQEXT_EMS, .name = "EMS", .desc = "[EXT] Emergency Signal"पूर्ण,
	अणु.irq = IRQEXT_TMR, .name = "TMR", .desc = "[EXT] CPU Timer"पूर्ण,
	अणु.irq = IRQEXT_TLA, .name = "TAL", .desc = "[EXT] Timing Alert"पूर्ण,
	अणु.irq = IRQEXT_PFL, .name = "PFL", .desc = "[EXT] Pseudo Page Fault"पूर्ण,
	अणु.irq = IRQEXT_DSD, .name = "DSD", .desc = "[EXT] DASD Diag"पूर्ण,
	अणु.irq = IRQEXT_VRT, .name = "VRT", .desc = "[EXT] Virtio"पूर्ण,
	अणु.irq = IRQEXT_SCP, .name = "SCP", .desc = "[EXT] Service Call"पूर्ण,
	अणु.irq = IRQEXT_IUC, .name = "IUC", .desc = "[EXT] IUCV"पूर्ण,
	अणु.irq = IRQEXT_CMS, .name = "CMS", .desc = "[EXT] CPU-Measurement: Sampling"पूर्ण,
	अणु.irq = IRQEXT_CMC, .name = "CMC", .desc = "[EXT] CPU-Measurement: Counter"पूर्ण,
	अणु.irq = IRQEXT_FTP, .name = "FTP", .desc = "[EXT] HMC FTP Service"पूर्ण,
	अणु.irq = IRQIO_CIO,  .name = "CIO", .desc = "[I/O] Common I/O Layer Interrupt"पूर्ण,
	अणु.irq = IRQIO_DAS,  .name = "DAS", .desc = "[I/O] DASD"पूर्ण,
	अणु.irq = IRQIO_C15,  .name = "C15", .desc = "[I/O] 3215"पूर्ण,
	अणु.irq = IRQIO_C70,  .name = "C70", .desc = "[I/O] 3270"पूर्ण,
	अणु.irq = IRQIO_TAP,  .name = "TAP", .desc = "[I/O] Tape"पूर्ण,
	अणु.irq = IRQIO_VMR,  .name = "VMR", .desc = "[I/O] Unit Record Devices"पूर्ण,
	अणु.irq = IRQIO_LCS,  .name = "LCS", .desc = "[I/O] LCS"पूर्ण,
	अणु.irq = IRQIO_CTC,  .name = "CTC", .desc = "[I/O] CTC"पूर्ण,
	अणु.irq = IRQIO_ADM,  .name = "ADM", .desc = "[I/O] EADM Subchannel"पूर्ण,
	अणु.irq = IRQIO_CSC,  .name = "CSC", .desc = "[I/O] CHSC Subchannel"पूर्ण,
	अणु.irq = IRQIO_VIR,  .name = "VIR", .desc = "[I/O] Virtual I/O Devices"पूर्ण,
	अणु.irq = IRQIO_QAI,  .name = "QAI", .desc = "[AIO] QDIO Adapter Interrupt"पूर्ण,
	अणु.irq = IRQIO_APB,  .name = "APB", .desc = "[AIO] AP Bus"पूर्ण,
	अणु.irq = IRQIO_PCF,  .name = "PCF", .desc = "[AIO] PCI Floating Interrupt"पूर्ण,
	अणु.irq = IRQIO_PCD,  .name = "PCD", .desc = "[AIO] PCI Directed Interrupt"पूर्ण,
	अणु.irq = IRQIO_MSI,  .name = "MSI", .desc = "[AIO] MSI Interrupt"पूर्ण,
	अणु.irq = IRQIO_VAI,  .name = "VAI", .desc = "[AIO] Virtual I/O Devices AI"पूर्ण,
	अणु.irq = IRQIO_GAL,  .name = "GAL", .desc = "[AIO] GIB Alert"पूर्ण,
	अणु.irq = NMI_NMI,    .name = "NMI", .desc = "[NMI] Machine Check"पूर्ण,
	अणु.irq = CPU_RST,    .name = "RST", .desc = "[CPU] CPU Restart"पूर्ण,
पूर्ण;

अटल व्योम करो_IRQ(काष्ठा pt_regs *regs, पूर्णांक irq)
अणु
	अगर (tod_after_eq(S390_lowcore.पूर्णांक_घड़ी,
			 S390_lowcore.घड़ी_comparator))
		/* Serve समयr पूर्णांकerrupts first. */
		घड़ी_comparator_work();
	generic_handle_irq(irq);
पूर्ण

अटल पूर्णांक on_async_stack(व्योम)
अणु
	अचिन्हित दीर्घ frame = current_frame_address();

	वापस !!!((S390_lowcore.async_stack - frame) >> (PAGE_SHIFT + THREAD_SIZE_ORDER));
पूर्ण

अटल व्योम करो_irq_async(काष्ठा pt_regs *regs, पूर्णांक irq)
अणु
	अगर (on_async_stack())
		करो_IRQ(regs, irq);
	अन्यथा
		CALL_ON_STACK(करो_IRQ, S390_lowcore.async_stack, 2, regs, irq);
पूर्ण

अटल पूर्णांक irq_pending(काष्ठा pt_regs *regs)
अणु
	पूर्णांक cc;

	यंत्र अस्थिर("tpi 0\n"
		     "ipm %0" : "=d" (cc) : : "cc");
	वापस cc >> 28;
पूर्ण

व्योम noinstr करो_io_irq(काष्ठा pt_regs *regs)
अणु
	irqentry_state_t state = irqentry_enter(regs);
	काष्ठा pt_regs *old_regs = set_irq_regs(regs);
	पूर्णांक from_idle;

	irq_enter();

	अगर (user_mode(regs))
		update_समयr_sys();

	from_idle = !user_mode(regs) && regs->psw.addr == (अचिन्हित दीर्घ)psw_idle_निकास;
	अगर (from_idle)
		account_idle_समय_irq();

	करो अणु
		स_नकल(&regs->पूर्णांक_code, &S390_lowcore.subchannel_id, 12);
		अगर (S390_lowcore.io_पूर्णांक_word & BIT(31))
			करो_irq_async(regs, THIN_INTERRUPT);
		अन्यथा
			करो_irq_async(regs, IO_INTERRUPT);
	पूर्ण जबतक (MACHINE_IS_LPAR && irq_pending(regs));

	irq_निकास();
	set_irq_regs(old_regs);
	irqentry_निकास(regs, state);

	अगर (from_idle)
		regs->psw.mask &= ~(PSW_MASK_EXT | PSW_MASK_IO | PSW_MASK_WAIT);
पूर्ण

व्योम noinstr करो_ext_irq(काष्ठा pt_regs *regs)
अणु
	irqentry_state_t state = irqentry_enter(regs);
	काष्ठा pt_regs *old_regs = set_irq_regs(regs);
	पूर्णांक from_idle;

	irq_enter();

	अगर (user_mode(regs))
		update_समयr_sys();

	स_नकल(&regs->पूर्णांक_code, &S390_lowcore.ext_cpu_addr, 4);
	regs->पूर्णांक_parm = S390_lowcore.ext_params;
	regs->पूर्णांक_parm_दीर्घ = S390_lowcore.ext_params2;

	from_idle = !user_mode(regs) && regs->psw.addr == (अचिन्हित दीर्घ)psw_idle_निकास;
	अगर (from_idle)
		account_idle_समय_irq();

	करो_irq_async(regs, EXT_INTERRUPT);

	irq_निकास();
	set_irq_regs(old_regs);
	irqentry_निकास(regs, state);

	अगर (from_idle)
		regs->psw.mask &= ~(PSW_MASK_EXT | PSW_MASK_IO | PSW_MASK_WAIT);
पूर्ण

अटल व्योम show_msi_पूर्णांकerrupt(काष्ठा seq_file *p, पूर्णांक irq)
अणु
	काष्ठा irq_desc *desc;
	अचिन्हित दीर्घ flags;
	पूर्णांक cpu;

	irq_lock_sparse();
	desc = irq_to_desc(irq);
	अगर (!desc)
		जाओ out;

	raw_spin_lock_irqsave(&desc->lock, flags);
	seq_म_लिखो(p, "%3d: ", irq);
	क्रम_each_online_cpu(cpu)
		seq_म_लिखो(p, "%10u ", irq_desc_kstat_cpu(desc, cpu));

	अगर (desc->irq_data.chip)
		seq_म_लिखो(p, " %8s", desc->irq_data.chip->name);

	अगर (desc->action)
		seq_म_लिखो(p, "  %s", desc->action->name);

	seq_अ_दो(p, '\n');
	raw_spin_unlock_irqrestore(&desc->lock, flags);
out:
	irq_unlock_sparse();
पूर्ण

/*
 * show_पूर्णांकerrupts is needed by /proc/पूर्णांकerrupts.
 */
पूर्णांक show_पूर्णांकerrupts(काष्ठा seq_file *p, व्योम *v)
अणु
	पूर्णांक index = *(loff_t *) v;
	पूर्णांक cpu, irq;

	get_online_cpus();
	अगर (index == 0) अणु
		seq_माला_दो(p, "           ");
		क्रम_each_online_cpu(cpu)
			seq_म_लिखो(p, "CPU%-8d", cpu);
		seq_अ_दो(p, '\n');
	पूर्ण
	अगर (index < NR_IRQS_BASE) अणु
		seq_म_लिखो(p, "%s: ", irqclass_मुख्य_desc[index].name);
		irq = irqclass_मुख्य_desc[index].irq;
		क्रम_each_online_cpu(cpu)
			seq_म_लिखो(p, "%10u ", kstat_irqs_cpu(irq, cpu));
		seq_अ_दो(p, '\n');
		जाओ out;
	पूर्ण
	अगर (index < nr_irqs) अणु
		show_msi_पूर्णांकerrupt(p, index);
		जाओ out;
	पूर्ण
	क्रम (index = 0; index < NR_ARCH_IRQS; index++) अणु
		seq_म_लिखो(p, "%s: ", irqclass_sub_desc[index].name);
		irq = irqclass_sub_desc[index].irq;
		क्रम_each_online_cpu(cpu)
			seq_म_लिखो(p, "%10u ",
				   per_cpu(irq_stat, cpu).irqs[irq]);
		अगर (irqclass_sub_desc[index].desc)
			seq_म_लिखो(p, "  %s", irqclass_sub_desc[index].desc);
		seq_अ_दो(p, '\n');
	पूर्ण
out:
	put_online_cpus();
	वापस 0;
पूर्ण

अचिन्हित पूर्णांक arch_dynirq_lower_bound(अचिन्हित पूर्णांक from)
अणु
	वापस from < NR_IRQS_BASE ? NR_IRQS_BASE : from;
पूर्ण

/*
 * Switch to the asynchronous पूर्णांकerrupt stack क्रम softirq execution.
 */
व्योम करो_softirq_own_stack(व्योम)
अणु
	अचिन्हित दीर्घ old, new;

	old = current_stack_poपूर्णांकer();
	/* Check against async. stack address range. */
	new = S390_lowcore.async_stack;
	अगर (((new - old) >> (PAGE_SHIFT + THREAD_SIZE_ORDER)) != 0) अणु
		CALL_ON_STACK(__करो_softirq, new, 0);
	पूर्ण अन्यथा अणु
		/* We are alपढ़ोy on the async stack. */
		__करो_softirq();
	पूर्ण
पूर्ण

/*
 * ext_पूर्णांक_hash[index] is the list head क्रम all बाह्यal पूर्णांकerrupts that hash
 * to this index.
 */
अटल काष्ठा hlist_head ext_पूर्णांक_hash[32] ____cacheline_aligned;

काष्ठा ext_पूर्णांक_info अणु
	ext_पूर्णांक_handler_t handler;
	काष्ठा hlist_node entry;
	काष्ठा rcu_head rcu;
	u16 code;
पूर्ण;

/* ext_पूर्णांक_hash_lock protects the handler lists क्रम बाह्यal पूर्णांकerrupts */
अटल DEFINE_SPINLOCK(ext_पूर्णांक_hash_lock);

अटल अंतरभूत पूर्णांक ext_hash(u16 code)
अणु
	BUILD_BUG_ON(!is_घातer_of_2(ARRAY_SIZE(ext_पूर्णांक_hash)));

	वापस (code + (code >> 9)) & (ARRAY_SIZE(ext_पूर्णांक_hash) - 1);
पूर्ण

पूर्णांक रेजिस्टर_बाह्यal_irq(u16 code, ext_पूर्णांक_handler_t handler)
अणु
	काष्ठा ext_पूर्णांक_info *p;
	अचिन्हित दीर्घ flags;
	पूर्णांक index;

	p = kदो_स्मृति(माप(*p), GFP_ATOMIC);
	अगर (!p)
		वापस -ENOMEM;
	p->code = code;
	p->handler = handler;
	index = ext_hash(code);

	spin_lock_irqsave(&ext_पूर्णांक_hash_lock, flags);
	hlist_add_head_rcu(&p->entry, &ext_पूर्णांक_hash[index]);
	spin_unlock_irqrestore(&ext_पूर्णांक_hash_lock, flags);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_बाह्यal_irq);

पूर्णांक unरेजिस्टर_बाह्यal_irq(u16 code, ext_पूर्णांक_handler_t handler)
अणु
	काष्ठा ext_पूर्णांक_info *p;
	अचिन्हित दीर्घ flags;
	पूर्णांक index = ext_hash(code);

	spin_lock_irqsave(&ext_पूर्णांक_hash_lock, flags);
	hlist_क्रम_each_entry_rcu(p, &ext_पूर्णांक_hash[index], entry) अणु
		अगर (p->code == code && p->handler == handler) अणु
			hlist_del_rcu(&p->entry);
			kमुक्त_rcu(p, rcu);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&ext_पूर्णांक_hash_lock, flags);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_बाह्यal_irq);

अटल irqवापस_t करो_ext_पूर्णांकerrupt(पूर्णांक irq, व्योम *dummy)
अणु
	काष्ठा pt_regs *regs = get_irq_regs();
	काष्ठा ext_code ext_code;
	काष्ठा ext_पूर्णांक_info *p;
	पूर्णांक index;

	ext_code = *(काष्ठा ext_code *) &regs->पूर्णांक_code;
	अगर (ext_code.code != EXT_IRQ_CLK_COMP)
		set_cpu_flag(CIF_NOHZ_DELAY);

	index = ext_hash(ext_code.code);
	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(p, &ext_पूर्णांक_hash[index], entry) अणु
		अगर (unlikely(p->code != ext_code.code))
			जारी;
		p->handler(ext_code, regs->पूर्णांक_parm, regs->पूर्णांक_parm_दीर्घ);
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम __init init_ext_पूर्णांकerrupts(व्योम)
अणु
	पूर्णांक idx;

	क्रम (idx = 0; idx < ARRAY_SIZE(ext_पूर्णांक_hash); idx++)
		INIT_HLIST_HEAD(&ext_पूर्णांक_hash[idx]);

	irq_set_chip_and_handler(EXT_INTERRUPT,
				 &dummy_irq_chip, handle_percpu_irq);
	अगर (request_irq(EXT_INTERRUPT, करो_ext_पूर्णांकerrupt, 0, "EXT", शून्य))
		panic("Failed to register EXT interrupt\n");
पूर्ण

व्योम __init init_IRQ(व्योम)
अणु
	BUILD_BUG_ON(ARRAY_SIZE(irqclass_sub_desc) != NR_ARCH_IRQS);
	init_cio_पूर्णांकerrupts();
	init_airq_पूर्णांकerrupts();
	init_ext_पूर्णांकerrupts();
पूर्ण

अटल DEFINE_SPINLOCK(irq_subclass_lock);
अटल अचिन्हित अक्षर irq_subclass_refcount[64];

व्योम irq_subclass_रेजिस्टर(क्रमागत irq_subclass subclass)
अणु
	spin_lock(&irq_subclass_lock);
	अगर (!irq_subclass_refcount[subclass])
		ctl_set_bit(0, subclass);
	irq_subclass_refcount[subclass]++;
	spin_unlock(&irq_subclass_lock);
पूर्ण
EXPORT_SYMBOL(irq_subclass_रेजिस्टर);

व्योम irq_subclass_unरेजिस्टर(क्रमागत irq_subclass subclass)
अणु
	spin_lock(&irq_subclass_lock);
	irq_subclass_refcount[subclass]--;
	अगर (!irq_subclass_refcount[subclass])
		ctl_clear_bit(0, subclass);
	spin_unlock(&irq_subclass_lock);
पूर्ण
EXPORT_SYMBOL(irq_subclass_unरेजिस्टर);
