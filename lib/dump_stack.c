<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Provide a शेष dump_stack() function क्रम architectures
 * which करोn't implement their own.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/smp.h>
#समावेश <linux/atomic.h>
#समावेश <linux/kexec.h>
#समावेश <linux/utsname.h>
#समावेश <linux/stop_machine.h>

अटल अक्षर dump_stack_arch_desc_str[128];

/**
 * dump_stack_set_arch_desc - set arch-specअगरic str to show with task dumps
 * @fmt: म_लिखो-style क्रमmat string
 * @...: arguments क्रम the क्रमmat string
 *
 * The configured string will be prपूर्णांकed right after utsname during task
 * dumps.  Usually used to add arch-specअगरic प्रणाली identअगरiers.  If an
 * arch wants to make use of such an ID string, it should initialize this
 * as soon as possible during boot.
 */
व्योम __init dump_stack_set_arch_desc(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vsnम_लिखो(dump_stack_arch_desc_str, माप(dump_stack_arch_desc_str),
		  fmt, args);
	बहु_पूर्ण(args);
पूर्ण

/**
 * dump_stack_prपूर्णांक_info - prपूर्णांक generic debug info क्रम dump_stack()
 * @log_lvl: log level
 *
 * Arch-specअगरic dump_stack() implementations can use this function to
 * prपूर्णांक out the same debug inक्रमmation as the generic dump_stack().
 */
व्योम dump_stack_prपूर्णांक_info(स्थिर अक्षर *log_lvl)
अणु
	prपूर्णांकk("%sCPU: %d PID: %d Comm: %.20s %s%s %s %.*s\n",
	       log_lvl, raw_smp_processor_id(), current->pid, current->comm,
	       kexec_crash_loaded() ? "Kdump: loaded " : "",
	       prपूर्णांक_taपूर्णांकed(),
	       init_utsname()->release,
	       (पूर्णांक)म_खोज(init_utsname()->version, " "),
	       init_utsname()->version);

	अगर (dump_stack_arch_desc_str[0] != '\0')
		prपूर्णांकk("%sHardware name: %s\n",
		       log_lvl, dump_stack_arch_desc_str);

	prपूर्णांक_worker_info(log_lvl, current);
	prपूर्णांक_stop_info(log_lvl, current);
पूर्ण

/**
 * show_regs_prपूर्णांक_info - prपूर्णांक generic debug info क्रम show_regs()
 * @log_lvl: log level
 *
 * show_regs() implementations can use this function to prपूर्णांक out generic
 * debug inक्रमmation.
 */
व्योम show_regs_prपूर्णांक_info(स्थिर अक्षर *log_lvl)
अणु
	dump_stack_prपूर्णांक_info(log_lvl);
पूर्ण

अटल व्योम __dump_stack(व्योम)
अणु
	dump_stack_prपूर्णांक_info(KERN_DEFAULT);
	show_stack(शून्य, शून्य, KERN_DEFAULT);
पूर्ण

/**
 * dump_stack - dump the current task inक्रमmation and its stack trace
 *
 * Architectures can override this implementation by implementing its own.
 */
#अगर_घोषित CONFIG_SMP
अटल atomic_t dump_lock = ATOMIC_INIT(-1);

यंत्रlinkage __visible व्योम dump_stack(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक was_locked;
	पूर्णांक old;
	पूर्णांक cpu;

	/*
	 * Permit this cpu to perक्रमm nested stack dumps जबतक serialising
	 * against other CPUs
	 */
retry:
	local_irq_save(flags);
	cpu = smp_processor_id();
	old = atomic_cmpxchg(&dump_lock, -1, cpu);
	अगर (old == -1) अणु
		was_locked = 0;
	पूर्ण अन्यथा अगर (old == cpu) अणु
		was_locked = 1;
	पूर्ण अन्यथा अणु
		local_irq_restore(flags);
		/*
		 * Wait क्रम the lock to release beक्रमe jumping to
		 * atomic_cmpxchg() in order to mitigate the thundering herd
		 * problem.
		 */
		करो अणु cpu_relax(); पूर्ण जबतक (atomic_पढ़ो(&dump_lock) != -1);
		जाओ retry;
	पूर्ण

	__dump_stack();

	अगर (!was_locked)
		atomic_set(&dump_lock, -1);

	local_irq_restore(flags);
पूर्ण
#अन्यथा
यंत्रlinkage __visible व्योम dump_stack(व्योम)
अणु
	__dump_stack();
पूर्ण
#पूर्ण_अगर
EXPORT_SYMBOL(dump_stack);
