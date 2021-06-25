<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * FP/SIMD context चयनing and fault handling
 *
 * Copyright (C) 2012 ARM Ltd.
 * Author: Catalin Marinas <catalin.marinas@arm.com>
 */

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/bitops.h>
#समावेश <linux/bottom_half.h>
#समावेश <linux/bug.h>
#समावेश <linux/cache.h>
#समावेश <linux/compat.h>
#समावेश <linux/compiler.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpu_pm.h>
#समावेश <linux/kernel.h>
#समावेश <linux/linkage.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/init.h>
#समावेश <linux/percpu.h>
#समावेश <linux/prctl.h>
#समावेश <linux/preempt.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/sysctl.h>
#समावेश <linux/swab.h>

#समावेश <यंत्र/esr.h>
#समावेश <यंत्र/exception.h>
#समावेश <यंत्र/fpsimd.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/neon.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/simd.h>
#समावेश <यंत्र/sigcontext.h>
#समावेश <यंत्र/sysreg.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/virt.h>

#घोषणा FPEXC_IOF	(1 << 0)
#घोषणा FPEXC_DZF	(1 << 1)
#घोषणा FPEXC_OFF	(1 << 2)
#घोषणा FPEXC_UFF	(1 << 3)
#घोषणा FPEXC_IXF	(1 << 4)
#घोषणा FPEXC_IDF	(1 << 7)

/*
 * (Note: in this discussion, statements about FPSIMD apply equally to SVE.)
 *
 * In order to reduce the number of बार the FPSIMD state is needlessly saved
 * and restored, we need to keep track of two things:
 * (a) क्रम each task, we need to remember which CPU was the last one to have
 *     the task's FPSIMD state loaded पूर्णांकo its FPSIMD रेजिस्टरs;
 * (b) क्रम each CPU, we need to remember which task's userland FPSIMD state has
 *     been loaded पूर्णांकo its FPSIMD रेजिस्टरs most recently, or whether it has
 *     been used to perक्रमm kernel mode NEON in the meanसमय.
 *
 * For (a), we add a fpsimd_cpu field to thपढ़ो_काष्ठा, which माला_लो updated to
 * the id of the current CPU every समय the state is loaded onto a CPU. For (b),
 * we add the per-cpu variable 'fpsimd_last_state' (below), which contains the
 * address of the userland FPSIMD state of the task that was loaded onto the CPU
 * the most recently, or शून्य अगर kernel mode NEON has been perक्रमmed after that.
 *
 * With this in place, we no दीर्घer have to restore the next FPSIMD state right
 * when चयनing between tasks. Instead, we can defer this check to userland
 * resume, at which समय we verअगरy whether the CPU's fpsimd_last_state and the
 * task's fpsimd_cpu are still mutually in sync. If this is the हाल, we
 * can omit the FPSIMD restore.
 *
 * As an optimization, we use the thपढ़ो_info flag TIF_FOREIGN_FPSTATE to
 * indicate whether or not the userland FPSIMD state of the current task is
 * present in the रेजिस्टरs. The flag is set unless the FPSIMD रेजिस्टरs of this
 * CPU currently contain the most recent userland FPSIMD state of the current
 * task.
 *
 * In order to allow softirq handlers to use FPSIMD, kernel_neon_begin() may
 * save the task's FPSIMD context back to task_काष्ठा from softirq context.
 * To prevent this from racing with the manipulation of the task's FPSIMD state
 * from task context and thereby corrupting the state, it is necessary to
 * protect any manipulation of a task's fpsimd_state or TIF_FOREIGN_FPSTATE
 * flag with अणु, __पूर्णget_cpu_fpsimd_context(). This will still allow softirqs to
 * run but prevent them to use FPSIMD.
 *
 * For a certain task, the sequence may look something like this:
 * - the task माला_लो scheduled in; अगर both the task's fpsimd_cpu field
 *   contains the id of the current CPU, and the CPU's fpsimd_last_state per-cpu
 *   variable poपूर्णांकs to the task's fpsimd_state, the TIF_FOREIGN_FPSTATE flag is
 *   cleared, otherwise it is set;
 *
 * - the task वापसs to userland; अगर TIF_FOREIGN_FPSTATE is set, the task's
 *   userland FPSIMD state is copied from memory to the रेजिस्टरs, the task's
 *   fpsimd_cpu field is set to the id of the current CPU, the current
 *   CPU's fpsimd_last_state pointer is set to this task's fpsimd_state and the
 *   TIF_FOREIGN_FPSTATE flag is cleared;
 *
 * - the task executes an ordinary syscall; upon वापस to userland, the
 *   TIF_FOREIGN_FPSTATE flag will still be cleared, so no FPSIMD state is
 *   restored;
 *
 * - the task executes a syscall which executes some NEON inकाष्ठाions; this is
 *   preceded by a call to kernel_neon_begin(), which copies the task's FPSIMD
 *   रेजिस्टर contents to memory, clears the fpsimd_last_state per-cpu variable
 *   and sets the TIF_FOREIGN_FPSTATE flag;
 *
 * - the task माला_लो preempted after kernel_neon_end() is called; as we have not
 *   वापसed from the 2nd syscall yet, TIF_FOREIGN_FPSTATE is still set so
 *   whatever is in the FPSIMD रेजिस्टरs is not saved to memory, but discarded.
 */
काष्ठा fpsimd_last_state_काष्ठा अणु
	काष्ठा user_fpsimd_state *st;
	व्योम *sve_state;
	अचिन्हित पूर्णांक sve_vl;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा fpsimd_last_state_काष्ठा, fpsimd_last_state);

/* Default VL क्रम tasks that करोn't set it explicitly: */
अटल पूर्णांक __sve_शेष_vl = -1;

अटल पूर्णांक get_sve_शेष_vl(व्योम)
अणु
	वापस READ_ONCE(__sve_शेष_vl);
पूर्ण

#अगर_घोषित CONFIG_ARM64_SVE

अटल व्योम set_sve_शेष_vl(पूर्णांक val)
अणु
	WRITE_ONCE(__sve_शेष_vl, val);
पूर्ण

/* Maximum supported vector length across all CPUs (initially poisoned) */
पूर्णांक __ro_after_init sve_max_vl = SVE_VL_MIN;
पूर्णांक __ro_after_init sve_max_भवisable_vl = SVE_VL_MIN;

/*
 * Set of available vector lengths,
 * where length vq encoded as bit __vq_to_bit(vq):
 */
__ro_after_init DECLARE_BITMAP(sve_vq_map, SVE_VQ_MAX);
/* Set of vector lengths present on at least one cpu: */
अटल __ro_after_init DECLARE_BITMAP(sve_vq_partial_map, SVE_VQ_MAX);

अटल व्योम __percpu *efi_sve_state;

#अन्यथा /* ! CONFIG_ARM64_SVE */

/* Dummy declaration क्रम code that will be optimised out: */
बाह्य __ro_after_init DECLARE_BITMAP(sve_vq_map, SVE_VQ_MAX);
बाह्य __ro_after_init DECLARE_BITMAP(sve_vq_partial_map, SVE_VQ_MAX);
बाह्य व्योम __percpu *efi_sve_state;

#पूर्ण_अगर /* ! CONFIG_ARM64_SVE */

DEFINE_PER_CPU(bool, fpsimd_context_busy);
EXPORT_PER_CPU_SYMBOL(fpsimd_context_busy);

अटल व्योम __get_cpu_fpsimd_context(व्योम)
अणु
	bool busy = __this_cpu_xchg(fpsimd_context_busy, true);

	WARN_ON(busy);
पूर्ण

/*
 * Claim ownership of the CPU FPSIMD context क्रम use by the calling context.
 *
 * The caller may मुक्तly manipulate the FPSIMD context metadata until
 * put_cpu_fpsimd_context() is called.
 *
 * The द्विगुन-underscore version must only be called अगर you know the task
 * can't be preempted.
 */
अटल व्योम get_cpu_fpsimd_context(व्योम)
अणु
	local_bh_disable();
	__get_cpu_fpsimd_context();
पूर्ण

अटल व्योम __put_cpu_fpsimd_context(व्योम)
अणु
	bool busy = __this_cpu_xchg(fpsimd_context_busy, false);

	WARN_ON(!busy); /* No matching get_cpu_fpsimd_context()? */
पूर्ण

/*
 * Release the CPU FPSIMD context.
 *
 * Must be called from a context in which get_cpu_fpsimd_context() was
 * previously called, with no call to put_cpu_fpsimd_context() in the
 * meanसमय.
 */
अटल व्योम put_cpu_fpsimd_context(व्योम)
अणु
	__put_cpu_fpsimd_context();
	local_bh_enable();
पूर्ण

अटल bool have_cpu_fpsimd_context(व्योम)
अणु
	वापस !preemptible() && __this_cpu_पढ़ो(fpsimd_context_busy);
पूर्ण

/*
 * Call __sve_मुक्त() directly only अगर you know task can't be scheduled
 * or preempted.
 */
अटल व्योम __sve_मुक्त(काष्ठा task_काष्ठा *task)
अणु
	kमुक्त(task->thपढ़ो.sve_state);
	task->thपढ़ो.sve_state = शून्य;
पूर्ण

अटल व्योम sve_मुक्त(काष्ठा task_काष्ठा *task)
अणु
	WARN_ON(test_tsk_thपढ़ो_flag(task, TIF_SVE));

	__sve_मुक्त(task);
पूर्ण

/*
 * TIF_SVE controls whether a task can use SVE without trapping जबतक
 * in userspace, and also the way a task's FPSIMD/SVE state is stored
 * in thपढ़ो_काष्ठा.
 *
 * The kernel uses this flag to track whether a user task is actively
 * using SVE, and thereक्रमe whether full SVE रेजिस्टर state needs to
 * be tracked.  If not, the cheaper FPSIMD context handling code can
 * be used instead of the more costly SVE equivalents.
 *
 *  * TIF_SVE set:
 *
 *    The task can execute SVE inकाष्ठाions जबतक in userspace without
 *    trapping to the kernel.
 *
 *    When stored, Z0-Z31 (incorporating Vn in bits[127:0] or the
 *    corresponding Zn), P0-P15 and FFR are encoded in in
 *    task->thपढ़ो.sve_state, क्रमmatted appropriately क्रम vector
 *    length task->thपढ़ो.sve_vl.
 *
 *    task->thपढ़ो.sve_state must poपूर्णांक to a valid buffer at least
 *    sve_state_size(task) bytes in size.
 *
 *    During any syscall, the kernel may optionally clear TIF_SVE and
 *    discard the vector state except क्रम the FPSIMD subset.
 *
 *  * TIF_SVE clear:
 *
 *    An attempt by the user task to execute an SVE inकाष्ठाion causes
 *    करो_sve_acc() to be called, which करोes some preparation and then
 *    sets TIF_SVE.
 *
 *    When stored, FPSIMD रेजिस्टरs V0-V31 are encoded in
 *    task->thपढ़ो.uw.fpsimd_state; bits [max : 128] क्रम each of Z0-Z31 are
 *    logically zero but not stored anywhere; P0-P15 and FFR are not
 *    stored and have unspecअगरied values from userspace's poपूर्णांक of
 *    view.  For hygiene purposes, the kernel zeroes them on next use,
 *    but userspace is discouraged from relying on this.
 *
 *    task->thपढ़ो.sve_state करोes not need to be non-शून्य, valid or any
 *    particular size: it must not be dereferenced.
 *
 *  * FPSR and FPCR are always stored in task->thपढ़ो.uw.fpsimd_state
 *    irrespective of whether TIF_SVE is clear or set, since these are
 *    not vector length dependent.
 */

/*
 * Update current's FPSIMD/SVE रेजिस्टरs from thपढ़ो_काष्ठा.
 *
 * This function should be called only when the FPSIMD/SVE state in
 * thपढ़ो_काष्ठा is known to be up to date, when preparing to enter
 * userspace.
 */
अटल व्योम task_fpsimd_load(व्योम)
अणु
	WARN_ON(!प्रणाली_supports_fpsimd());
	WARN_ON(!have_cpu_fpsimd_context());

	अगर (IS_ENABLED(CONFIG_ARM64_SVE) && test_thपढ़ो_flag(TIF_SVE))
		sve_load_state(sve_pffr(&current->thपढ़ो),
			       &current->thपढ़ो.uw.fpsimd_state.fpsr,
			       sve_vq_from_vl(current->thपढ़ो.sve_vl) - 1);
	अन्यथा
		fpsimd_load_state(&current->thपढ़ो.uw.fpsimd_state);
पूर्ण

/*
 * Ensure FPSIMD/SVE storage in memory क्रम the loaded context is up to
 * date with respect to the CPU रेजिस्टरs.
 */
अटल व्योम fpsimd_save(व्योम)
अणु
	काष्ठा fpsimd_last_state_काष्ठा स्थिर *last =
		this_cpu_ptr(&fpsimd_last_state);
	/* set by fpsimd_bind_task_to_cpu() or fpsimd_bind_state_to_cpu() */

	WARN_ON(!प्रणाली_supports_fpsimd());
	WARN_ON(!have_cpu_fpsimd_context());

	अगर (!test_thपढ़ो_flag(TIF_FOREIGN_FPSTATE)) अणु
		अगर (IS_ENABLED(CONFIG_ARM64_SVE) &&
		    test_thपढ़ो_flag(TIF_SVE)) अणु
			अगर (WARN_ON(sve_get_vl() != last->sve_vl)) अणु
				/*
				 * Can't save the user regs, so current would
				 * re-enter user with corrupt state.
				 * There's no way to recover, so समाप्त it:
				 */
				क्रमce_संकेत_inject(SIGKILL, SI_KERNEL, 0, 0);
				वापस;
			पूर्ण

			sve_save_state((अक्षर *)last->sve_state +
						sve_ffr_offset(last->sve_vl),
				       &last->st->fpsr);
		पूर्ण अन्यथा
			fpsimd_save_state(last->st);
	पूर्ण
पूर्ण

/*
 * All vector length selection from userspace comes through here.
 * We're on a slow path, so some sanity-checks are included.
 * If things go wrong there's a bug somewhere, but try to fall back to a
 * safe choice.
 */
अटल अचिन्हित पूर्णांक find_supported_vector_length(अचिन्हित पूर्णांक vl)
अणु
	पूर्णांक bit;
	पूर्णांक max_vl = sve_max_vl;

	अगर (WARN_ON(!sve_vl_valid(vl)))
		vl = SVE_VL_MIN;

	अगर (WARN_ON(!sve_vl_valid(max_vl)))
		max_vl = SVE_VL_MIN;

	अगर (vl > max_vl)
		vl = max_vl;

	bit = find_next_bit(sve_vq_map, SVE_VQ_MAX,
			    __vq_to_bit(sve_vq_from_vl(vl)));
	वापस sve_vl_from_vq(__bit_to_vq(bit));
पूर्ण

#अगर defined(CONFIG_ARM64_SVE) && defined(CONFIG_SYSCTL)

अटल पूर्णांक sve_proc_करो_शेष_vl(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
				  व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक ret;
	पूर्णांक vl = get_sve_शेष_vl();
	काष्ठा ctl_table पंचांगp_table = अणु
		.data = &vl,
		.maxlen = माप(vl),
	पूर्ण;

	ret = proc_करोपूर्णांकvec(&पंचांगp_table, ग_लिखो, buffer, lenp, ppos);
	अगर (ret || !ग_लिखो)
		वापस ret;

	/* Writing -1 has the special meaning "set to max": */
	अगर (vl == -1)
		vl = sve_max_vl;

	अगर (!sve_vl_valid(vl))
		वापस -EINVAL;

	set_sve_शेष_vl(find_supported_vector_length(vl));
	वापस 0;
पूर्ण

अटल काष्ठा ctl_table sve_शेष_vl_table[] = अणु
	अणु
		.procname	= "sve_default_vector_length",
		.mode		= 0644,
		.proc_handler	= sve_proc_करो_शेष_vl,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक __init sve_sysctl_init(व्योम)
अणु
	अगर (प्रणाली_supports_sve())
		अगर (!रेजिस्टर_sysctl("abi", sve_शेष_vl_table))
			वापस -EINVAL;

	वापस 0;
पूर्ण

#अन्यथा /* ! (CONFIG_ARM64_SVE && CONFIG_SYSCTL) */
अटल पूर्णांक __init sve_sysctl_init(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर /* ! (CONFIG_ARM64_SVE && CONFIG_SYSCTL) */

#घोषणा ZREG(sve_state, vq, n) ((अक्षर *)(sve_state) +		\
	(SVE_SIG_ZREG_OFFSET(vq, n) - SVE_SIG_REGS_OFFSET))

#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
अटल __uपूर्णांक128_t arm64_cpu_to_le128(__uपूर्णांक128_t x)
अणु
	u64 a = swab64(x);
	u64 b = swab64(x >> 64);

	वापस ((__uपूर्णांक128_t)a << 64) | b;
पूर्ण
#अन्यथा
अटल __uपूर्णांक128_t arm64_cpu_to_le128(__uपूर्णांक128_t x)
अणु
	वापस x;
पूर्ण
#पूर्ण_अगर

#घोषणा arm64_le128_to_cpu(x) arm64_cpu_to_le128(x)

अटल व्योम __fpsimd_to_sve(व्योम *sst, काष्ठा user_fpsimd_state स्थिर *fst,
			    अचिन्हित पूर्णांक vq)
अणु
	अचिन्हित पूर्णांक i;
	__uपूर्णांक128_t *p;

	क्रम (i = 0; i < SVE_NUM_ZREGS; ++i) अणु
		p = (__uपूर्णांक128_t *)ZREG(sst, vq, i);
		*p = arm64_cpu_to_le128(fst->vregs[i]);
	पूर्ण
पूर्ण

/*
 * Transfer the FPSIMD state in task->thपढ़ो.uw.fpsimd_state to
 * task->thपढ़ो.sve_state.
 *
 * Task can be a non-runnable task, or current.  In the latter हाल,
 * the caller must have ownership of the cpu FPSIMD context beक्रमe calling
 * this function.
 * task->thपढ़ो.sve_state must poपूर्णांक to at least sve_state_size(task)
 * bytes of allocated kernel memory.
 * task->thपढ़ो.uw.fpsimd_state must be up to date beक्रमe calling this
 * function.
 */
अटल व्योम fpsimd_to_sve(काष्ठा task_काष्ठा *task)
अणु
	अचिन्हित पूर्णांक vq;
	व्योम *sst = task->thपढ़ो.sve_state;
	काष्ठा user_fpsimd_state स्थिर *fst = &task->thपढ़ो.uw.fpsimd_state;

	अगर (!प्रणाली_supports_sve())
		वापस;

	vq = sve_vq_from_vl(task->thपढ़ो.sve_vl);
	__fpsimd_to_sve(sst, fst, vq);
पूर्ण

/*
 * Transfer the SVE state in task->thपढ़ो.sve_state to
 * task->thपढ़ो.uw.fpsimd_state.
 *
 * Task can be a non-runnable task, or current.  In the latter हाल,
 * the caller must have ownership of the cpu FPSIMD context beक्रमe calling
 * this function.
 * task->thपढ़ो.sve_state must poपूर्णांक to at least sve_state_size(task)
 * bytes of allocated kernel memory.
 * task->thपढ़ो.sve_state must be up to date beक्रमe calling this function.
 */
अटल व्योम sve_to_fpsimd(काष्ठा task_काष्ठा *task)
अणु
	अचिन्हित पूर्णांक vq;
	व्योम स्थिर *sst = task->thपढ़ो.sve_state;
	काष्ठा user_fpsimd_state *fst = &task->thपढ़ो.uw.fpsimd_state;
	अचिन्हित पूर्णांक i;
	__uपूर्णांक128_t स्थिर *p;

	अगर (!प्रणाली_supports_sve())
		वापस;

	vq = sve_vq_from_vl(task->thपढ़ो.sve_vl);
	क्रम (i = 0; i < SVE_NUM_ZREGS; ++i) अणु
		p = (__uपूर्णांक128_t स्थिर *)ZREG(sst, vq, i);
		fst->vregs[i] = arm64_le128_to_cpu(*p);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_ARM64_SVE

/*
 * Return how many bytes of memory are required to store the full SVE
 * state क्रम task, given task's currently configured vector length.
 */
माप_प्रकार sve_state_size(काष्ठा task_काष्ठा स्थिर *task)
अणु
	वापस SVE_SIG_REGS_SIZE(sve_vq_from_vl(task->thपढ़ो.sve_vl));
पूर्ण

/*
 * Ensure that task->thपढ़ो.sve_state is allocated and sufficiently large.
 *
 * This function should be used only in preparation क्रम replacing
 * task->thपढ़ो.sve_state with new data.  The memory is always zeroed
 * here to prevent stale data from showing through: this is करोne in
 * the पूर्णांकerest of testability and predictability: except in the
 * करो_sve_acc() हाल, there is no ABI requirement to hide stale data
 * written previously be task.
 */
व्योम sve_alloc(काष्ठा task_काष्ठा *task)
अणु
	अगर (task->thपढ़ो.sve_state) अणु
		स_रखो(task->thपढ़ो.sve_state, 0, sve_state_size(current));
		वापस;
	पूर्ण

	/* This is a small allocation (maximum ~8KB) and Should Not Fail. */
	task->thपढ़ो.sve_state =
		kzalloc(sve_state_size(task), GFP_KERNEL);

	/*
	 * If future SVE revisions can have larger vectors though,
	 * this may cease to be true:
	 */
	BUG_ON(!task->thपढ़ो.sve_state);
पूर्ण


/*
 * Ensure that task->thपढ़ो.sve_state is up to date with respect to
 * the user task, irrespective of when SVE is in use or not.
 *
 * This should only be called by ptrace.  task must be non-runnable.
 * task->thपढ़ो.sve_state must poपूर्णांक to at least sve_state_size(task)
 * bytes of allocated kernel memory.
 */
व्योम fpsimd_sync_to_sve(काष्ठा task_काष्ठा *task)
अणु
	अगर (!test_tsk_thपढ़ो_flag(task, TIF_SVE))
		fpsimd_to_sve(task);
पूर्ण

/*
 * Ensure that task->thपढ़ो.uw.fpsimd_state is up to date with respect to
 * the user task, irrespective of whether SVE is in use or not.
 *
 * This should only be called by ptrace.  task must be non-runnable.
 * task->thपढ़ो.sve_state must poपूर्णांक to at least sve_state_size(task)
 * bytes of allocated kernel memory.
 */
व्योम sve_sync_to_fpsimd(काष्ठा task_काष्ठा *task)
अणु
	अगर (test_tsk_thपढ़ो_flag(task, TIF_SVE))
		sve_to_fpsimd(task);
पूर्ण

/*
 * Ensure that task->thपढ़ो.sve_state is up to date with respect to
 * the task->thपढ़ो.uw.fpsimd_state.
 *
 * This should only be called by ptrace to merge new FPSIMD रेजिस्टर
 * values पूर्णांकo a task क्रम which SVE is currently active.
 * task must be non-runnable.
 * task->thपढ़ो.sve_state must poपूर्णांक to at least sve_state_size(task)
 * bytes of allocated kernel memory.
 * task->thपढ़ो.uw.fpsimd_state must alपढ़ोy have been initialised with
 * the new FPSIMD रेजिस्टर values to be merged in.
 */
व्योम sve_sync_from_fpsimd_zeropad(काष्ठा task_काष्ठा *task)
अणु
	अचिन्हित पूर्णांक vq;
	व्योम *sst = task->thपढ़ो.sve_state;
	काष्ठा user_fpsimd_state स्थिर *fst = &task->thपढ़ो.uw.fpsimd_state;

	अगर (!test_tsk_thपढ़ो_flag(task, TIF_SVE))
		वापस;

	vq = sve_vq_from_vl(task->thपढ़ो.sve_vl);

	स_रखो(sst, 0, SVE_SIG_REGS_SIZE(vq));
	__fpsimd_to_sve(sst, fst, vq);
पूर्ण

पूर्णांक sve_set_vector_length(काष्ठा task_काष्ठा *task,
			  अचिन्हित दीर्घ vl, अचिन्हित दीर्घ flags)
अणु
	अगर (flags & ~(अचिन्हित दीर्घ)(PR_SVE_VL_INHERIT |
				     PR_SVE_SET_VL_ONEXEC))
		वापस -EINVAL;

	अगर (!sve_vl_valid(vl))
		वापस -EINVAL;

	/*
	 * Clamp to the maximum vector length that VL-agnostic SVE code can
	 * work with.  A flag may be asचिन्हित in the future to allow setting
	 * of larger vector lengths without confusing older software.
	 */
	अगर (vl > SVE_VL_ARCH_MAX)
		vl = SVE_VL_ARCH_MAX;

	vl = find_supported_vector_length(vl);

	अगर (flags & (PR_SVE_VL_INHERIT |
		     PR_SVE_SET_VL_ONEXEC))
		task->thपढ़ो.sve_vl_onexec = vl;
	अन्यथा
		/* Reset VL to प्रणाली शेष on next exec: */
		task->thपढ़ो.sve_vl_onexec = 0;

	/* Only actually set the VL अगर not deferred: */
	अगर (flags & PR_SVE_SET_VL_ONEXEC)
		जाओ out;

	अगर (vl == task->thपढ़ो.sve_vl)
		जाओ out;

	/*
	 * To ensure the FPSIMD bits of the SVE vector रेजिस्टरs are preserved,
	 * ग_लिखो any live रेजिस्टर state back to task_काष्ठा, and convert to a
	 * non-SVE thपढ़ो.
	 */
	अगर (task == current) अणु
		get_cpu_fpsimd_context();

		fpsimd_save();
	पूर्ण

	fpsimd_flush_task_state(task);
	अगर (test_and_clear_tsk_thपढ़ो_flag(task, TIF_SVE))
		sve_to_fpsimd(task);

	अगर (task == current)
		put_cpu_fpsimd_context();

	/*
	 * Force पुनः_स्मृतिation of task SVE state to the correct size
	 * on next use:
	 */
	sve_मुक्त(task);

	task->thपढ़ो.sve_vl = vl;

out:
	update_tsk_thपढ़ो_flag(task, TIF_SVE_VL_INHERIT,
			       flags & PR_SVE_VL_INHERIT);

	वापस 0;
पूर्ण

/*
 * Encode the current vector length and flags क्रम वापस.
 * This is only required क्रम prctl(): ptrace has separate fields
 *
 * flags are as क्रम sve_set_vector_length().
 */
अटल पूर्णांक sve_prctl_status(अचिन्हित दीर्घ flags)
अणु
	पूर्णांक ret;

	अगर (flags & PR_SVE_SET_VL_ONEXEC)
		ret = current->thपढ़ो.sve_vl_onexec;
	अन्यथा
		ret = current->thपढ़ो.sve_vl;

	अगर (test_thपढ़ो_flag(TIF_SVE_VL_INHERIT))
		ret |= PR_SVE_VL_INHERIT;

	वापस ret;
पूर्ण

/* PR_SVE_SET_VL */
पूर्णांक sve_set_current_vl(अचिन्हित दीर्घ arg)
अणु
	अचिन्हित दीर्घ vl, flags;
	पूर्णांक ret;

	vl = arg & PR_SVE_VL_LEN_MASK;
	flags = arg & ~vl;

	अगर (!प्रणाली_supports_sve() || is_compat_task())
		वापस -EINVAL;

	ret = sve_set_vector_length(current, vl, flags);
	अगर (ret)
		वापस ret;

	वापस sve_prctl_status(flags);
पूर्ण

/* PR_SVE_GET_VL */
पूर्णांक sve_get_current_vl(व्योम)
अणु
	अगर (!प्रणाली_supports_sve() || is_compat_task())
		वापस -EINVAL;

	वापस sve_prctl_status(0);
पूर्ण

अटल व्योम sve_probe_vqs(DECLARE_BITMAP(map, SVE_VQ_MAX))
अणु
	अचिन्हित पूर्णांक vq, vl;
	अचिन्हित दीर्घ zcr;

	biपंचांगap_zero(map, SVE_VQ_MAX);

	zcr = ZCR_ELx_LEN_MASK;
	zcr = पढ़ो_sysreg_s(SYS_ZCR_EL1) & ~zcr;

	क्रम (vq = SVE_VQ_MAX; vq >= SVE_VQ_MIN; --vq) अणु
		ग_लिखो_sysreg_s(zcr | (vq - 1), SYS_ZCR_EL1); /* self-syncing */
		vl = sve_get_vl();
		vq = sve_vq_from_vl(vl); /* skip पूर्णांकervening lengths */
		set_bit(__vq_to_bit(vq), map);
	पूर्ण
पूर्ण

/*
 * Initialise the set of known supported VQs क्रम the boot CPU.
 * This is called during kernel boot, beक्रमe secondary CPUs are brought up.
 */
व्योम __init sve_init_vq_map(व्योम)
अणु
	sve_probe_vqs(sve_vq_map);
	biपंचांगap_copy(sve_vq_partial_map, sve_vq_map, SVE_VQ_MAX);
पूर्ण

/*
 * If we haven't committed to the set of supported VQs yet, filter out
 * those not supported by the current CPU.
 * This function is called during the bring-up of early secondary CPUs only.
 */
व्योम sve_update_vq_map(व्योम)
अणु
	DECLARE_BITMAP(पंचांगp_map, SVE_VQ_MAX);

	sve_probe_vqs(पंचांगp_map);
	biपंचांगap_and(sve_vq_map, sve_vq_map, पंचांगp_map, SVE_VQ_MAX);
	biपंचांगap_or(sve_vq_partial_map, sve_vq_partial_map, पंचांगp_map, SVE_VQ_MAX);
पूर्ण

/*
 * Check whether the current CPU supports all VQs in the committed set.
 * This function is called during the bring-up of late secondary CPUs only.
 */
पूर्णांक sve_verअगरy_vq_map(व्योम)
अणु
	DECLARE_BITMAP(पंचांगp_map, SVE_VQ_MAX);
	अचिन्हित दीर्घ b;

	sve_probe_vqs(पंचांगp_map);

	biपंचांगap_complement(पंचांगp_map, पंचांगp_map, SVE_VQ_MAX);
	अगर (biपंचांगap_पूर्णांकersects(पंचांगp_map, sve_vq_map, SVE_VQ_MAX)) अणु
		pr_warn("SVE: cpu%d: Required vector length(s) missing\n",
			smp_processor_id());
		वापस -EINVAL;
	पूर्ण

	अगर (!IS_ENABLED(CONFIG_KVM) || !is_hyp_mode_available())
		वापस 0;

	/*
	 * For KVM, it is necessary to ensure that this CPU करोesn't
	 * support any vector length that guests may have probed as
	 * unsupported.
	 */

	/* Recover the set of supported VQs: */
	biपंचांगap_complement(पंचांगp_map, पंचांगp_map, SVE_VQ_MAX);
	/* Find VQs supported that are not globally supported: */
	biपंचांगap_andnot(पंचांगp_map, पंचांगp_map, sve_vq_map, SVE_VQ_MAX);

	/* Find the lowest such VQ, अगर any: */
	b = find_last_bit(पंचांगp_map, SVE_VQ_MAX);
	अगर (b >= SVE_VQ_MAX)
		वापस 0; /* no mismatches */

	/*
	 * Mismatches above sve_max_भवisable_vl are fine, since
	 * no guest is allowed to configure ZCR_EL2.LEN to exceed this:
	 */
	अगर (sve_vl_from_vq(__bit_to_vq(b)) <= sve_max_भवisable_vl) अणु
		pr_warn("SVE: cpu%d: Unsupported vector length(s) present\n",
			smp_processor_id());
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __init sve_efi_setup(व्योम)
अणु
	अगर (!IS_ENABLED(CONFIG_EFI))
		वापस;

	/*
	 * alloc_percpu() warns and prपूर्णांकs a backtrace अगर this goes wrong.
	 * This is evidence of a crippled प्रणाली and we are वापसing व्योम,
	 * so no attempt is made to handle this situation here.
	 */
	अगर (!sve_vl_valid(sve_max_vl))
		जाओ fail;

	efi_sve_state = __alloc_percpu(
		SVE_SIG_REGS_SIZE(sve_vq_from_vl(sve_max_vl)), SVE_VQ_BYTES);
	अगर (!efi_sve_state)
		जाओ fail;

	वापस;

fail:
	panic("Cannot allocate percpu memory for EFI SVE save/restore");
पूर्ण

/*
 * Enable SVE क्रम EL1.
 * Intended क्रम use by the cpufeatures code during CPU boot.
 */
व्योम sve_kernel_enable(स्थिर काष्ठा arm64_cpu_capabilities *__always_unused p)
अणु
	ग_लिखो_sysreg(पढ़ो_sysreg(CPACR_EL1) | CPACR_EL1_ZEN_EL1EN, CPACR_EL1);
	isb();
पूर्ण

/*
 * Read the pseuकरो-ZCR used by cpufeatures to identअगरy the supported SVE
 * vector length.
 *
 * Use only अगर SVE is present.
 * This function clobbers the SVE vector length.
 */
u64 पढ़ो_zcr_features(व्योम)
अणु
	u64 zcr;
	अचिन्हित पूर्णांक vq_max;

	/*
	 * Set the maximum possible VL, and ग_लिखो zeroes to all other
	 * bits to see अगर they stick.
	 */
	sve_kernel_enable(शून्य);
	ग_लिखो_sysreg_s(ZCR_ELx_LEN_MASK, SYS_ZCR_EL1);

	zcr = पढ़ो_sysreg_s(SYS_ZCR_EL1);
	zcr &= ~(u64)ZCR_ELx_LEN_MASK; /* find sticky 1s outside LEN field */
	vq_max = sve_vq_from_vl(sve_get_vl());
	zcr |= vq_max - 1; /* set LEN field to maximum effective value */

	वापस zcr;
पूर्ण

व्योम __init sve_setup(व्योम)
अणु
	u64 zcr;
	DECLARE_BITMAP(पंचांगp_map, SVE_VQ_MAX);
	अचिन्हित दीर्घ b;

	अगर (!प्रणाली_supports_sve())
		वापस;

	/*
	 * The SVE architecture mandates support क्रम 128-bit vectors,
	 * so sve_vq_map must have at least SVE_VQ_MIN set.
	 * If something went wrong, at least try to patch it up:
	 */
	अगर (WARN_ON(!test_bit(__vq_to_bit(SVE_VQ_MIN), sve_vq_map)))
		set_bit(__vq_to_bit(SVE_VQ_MIN), sve_vq_map);

	zcr = पढ़ो_sanitised_ftr_reg(SYS_ZCR_EL1);
	sve_max_vl = sve_vl_from_vq((zcr & ZCR_ELx_LEN_MASK) + 1);

	/*
	 * Sanity-check that the max VL we determined through CPU features
	 * corresponds properly to sve_vq_map.  If not, करो our best:
	 */
	अगर (WARN_ON(sve_max_vl != find_supported_vector_length(sve_max_vl)))
		sve_max_vl = find_supported_vector_length(sve_max_vl);

	/*
	 * For the शेष VL, pick the maximum supported value <= 64.
	 * VL == 64 is guaranteed not to grow the संकेत frame.
	 */
	set_sve_शेष_vl(find_supported_vector_length(64));

	biपंचांगap_andnot(पंचांगp_map, sve_vq_partial_map, sve_vq_map,
		      SVE_VQ_MAX);

	b = find_last_bit(पंचांगp_map, SVE_VQ_MAX);
	अगर (b >= SVE_VQ_MAX)
		/* No non-भवisable VLs found */
		sve_max_भवisable_vl = SVE_VQ_MAX;
	अन्यथा अगर (WARN_ON(b == SVE_VQ_MAX - 1))
		/* No भवisable VLs?  This is architecturally क्रमbidden. */
		sve_max_भवisable_vl = SVE_VQ_MIN;
	अन्यथा /* b + 1 < SVE_VQ_MAX */
		sve_max_भवisable_vl = sve_vl_from_vq(__bit_to_vq(b + 1));

	अगर (sve_max_भवisable_vl > sve_max_vl)
		sve_max_भवisable_vl = sve_max_vl;

	pr_info("SVE: maximum available vector length %u bytes per vector\n",
		sve_max_vl);
	pr_info("SVE: default vector length %u bytes per vector\n",
		get_sve_शेष_vl());

	/* KVM decides whether to support mismatched प्रणालीs. Just warn here: */
	अगर (sve_max_भवisable_vl < sve_max_vl)
		pr_warn("SVE: unvirtualisable vector lengths present\n");

	sve_efi_setup();
पूर्ण

/*
 * Called from the put_task_काष्ठा() path, which cannot get here
 * unless dead_task is really dead and not schedulable.
 */
व्योम fpsimd_release_task(काष्ठा task_काष्ठा *dead_task)
अणु
	__sve_मुक्त(dead_task);
पूर्ण

#पूर्ण_अगर /* CONFIG_ARM64_SVE */

/*
 * Trapped SVE access
 *
 * Storage is allocated क्रम the full SVE state, the current FPSIMD
 * रेजिस्टर contents are migrated across, and the access trap is
 * disabled.
 *
 * TIF_SVE should be clear on entry: otherwise, fpsimd_restore_current_state()
 * would have disabled the SVE access trap क्रम userspace during
 * ret_to_user, making an SVE access trap impossible in that हाल.
 */
व्योम करो_sve_acc(अचिन्हित पूर्णांक esr, काष्ठा pt_regs *regs)
अणु
	/* Even अगर we chose not to use SVE, the hardware could still trap: */
	अगर (unlikely(!प्रणाली_supports_sve()) || WARN_ON(is_compat_task())) अणु
		क्रमce_संकेत_inject(संक_अवैध, ILL_ILLOPC, regs->pc, 0);
		वापस;
	पूर्ण

	sve_alloc(current);

	get_cpu_fpsimd_context();

	अगर (test_and_set_thपढ़ो_flag(TIF_SVE))
		WARN_ON(1); /* SVE access shouldn't have trapped */

	/*
	 * Convert the FPSIMD state to SVE, zeroing all the state that
	 * is not shared with FPSIMD. If (as is likely) the current
	 * state is live in the रेजिस्टरs then करो this there and
	 * update our metadata क्रम the current task including
	 * disabling the trap, otherwise update our in-memory copy.
	 */
	अगर (!test_thपढ़ो_flag(TIF_FOREIGN_FPSTATE)) अणु
		sve_set_vq(sve_vq_from_vl(current->thपढ़ो.sve_vl) - 1);
		sve_flush_live();
		fpsimd_bind_task_to_cpu();
	पूर्ण अन्यथा अणु
		fpsimd_to_sve(current);
	पूर्ण

	put_cpu_fpsimd_context();
पूर्ण

/*
 * Trapped FP/ASIMD access.
 */
व्योम करो_fpsimd_acc(अचिन्हित पूर्णांक esr, काष्ठा pt_regs *regs)
अणु
	/* TODO: implement lazy context saving/restoring */
	WARN_ON(1);
पूर्ण

/*
 * Raise a संक_भ_त्रुटि क्रम the current process.
 */
व्योम करो_fpsimd_exc(अचिन्हित पूर्णांक esr, काष्ठा pt_regs *regs)
अणु
	अचिन्हित पूर्णांक si_code = FPE_FLTUNK;

	अगर (esr & ESR_ELx_FP_EXC_TFV) अणु
		अगर (esr & FPEXC_IOF)
			si_code = FPE_FLTINV;
		अन्यथा अगर (esr & FPEXC_DZF)
			si_code = FPE_FLTDIV;
		अन्यथा अगर (esr & FPEXC_OFF)
			si_code = FPE_FLTOVF;
		अन्यथा अगर (esr & FPEXC_UFF)
			si_code = FPE_FLTUND;
		अन्यथा अगर (esr & FPEXC_IXF)
			si_code = FPE_FLTRES;
	पूर्ण

	send_sig_fault(संक_भ_त्रुटि, si_code,
		       (व्योम __user *)inकाष्ठाion_poपूर्णांकer(regs),
		       current);
पूर्ण

व्योम fpsimd_thपढ़ो_चयन(काष्ठा task_काष्ठा *next)
अणु
	bool wrong_task, wrong_cpu;

	अगर (!प्रणाली_supports_fpsimd())
		वापस;

	__get_cpu_fpsimd_context();

	/* Save unsaved fpsimd state, अगर any: */
	fpsimd_save();

	/*
	 * Fix up TIF_FOREIGN_FPSTATE to correctly describe next's
	 * state.  For kernel thपढ़ोs, FPSIMD रेजिस्टरs are never loaded
	 * and wrong_task and wrong_cpu will always be true.
	 */
	wrong_task = __this_cpu_पढ़ो(fpsimd_last_state.st) !=
					&next->thपढ़ो.uw.fpsimd_state;
	wrong_cpu = next->thपढ़ो.fpsimd_cpu != smp_processor_id();

	update_tsk_thपढ़ो_flag(next, TIF_FOREIGN_FPSTATE,
			       wrong_task || wrong_cpu);

	__put_cpu_fpsimd_context();
पूर्ण

व्योम fpsimd_flush_thपढ़ो(व्योम)
अणु
	पूर्णांक vl, supported_vl;

	अगर (!प्रणाली_supports_fpsimd())
		वापस;

	get_cpu_fpsimd_context();

	fpsimd_flush_task_state(current);
	स_रखो(&current->thपढ़ो.uw.fpsimd_state, 0,
	       माप(current->thपढ़ो.uw.fpsimd_state));

	अगर (प्रणाली_supports_sve()) अणु
		clear_thपढ़ो_flag(TIF_SVE);
		sve_मुक्त(current);

		/*
		 * Reset the task vector length as required.
		 * This is where we ensure that all user tasks have a valid
		 * vector length configured: no kernel task can become a user
		 * task without an exec and hence a call to this function.
		 * By the समय the first call to this function is made, all
		 * early hardware probing is complete, so __sve_शेष_vl
		 * should be valid.
		 * If a bug causes this to go wrong, we make some noise and
		 * try to fudge thपढ़ो.sve_vl to a safe value here.
		 */
		vl = current->thपढ़ो.sve_vl_onexec ?
			current->thपढ़ो.sve_vl_onexec : get_sve_शेष_vl();

		अगर (WARN_ON(!sve_vl_valid(vl)))
			vl = SVE_VL_MIN;

		supported_vl = find_supported_vector_length(vl);
		अगर (WARN_ON(supported_vl != vl))
			vl = supported_vl;

		current->thपढ़ो.sve_vl = vl;

		/*
		 * If the task is not set to inherit, ensure that the vector
		 * length will be reset by a subsequent exec:
		 */
		अगर (!test_thपढ़ो_flag(TIF_SVE_VL_INHERIT))
			current->thपढ़ो.sve_vl_onexec = 0;
	पूर्ण

	put_cpu_fpsimd_context();
पूर्ण

/*
 * Save the userland FPSIMD state of 'current' to memory, but only अगर the state
 * currently held in the रेजिस्टरs करोes in fact beदीर्घ to 'current'
 */
व्योम fpsimd_preserve_current_state(व्योम)
अणु
	अगर (!प्रणाली_supports_fpsimd())
		वापस;

	get_cpu_fpsimd_context();
	fpsimd_save();
	put_cpu_fpsimd_context();
पूर्ण

/*
 * Like fpsimd_preserve_current_state(), but ensure that
 * current->thपढ़ो.uw.fpsimd_state is updated so that it can be copied to
 * the संकेत frame.
 */
व्योम fpsimd_संकेत_preserve_current_state(व्योम)
अणु
	fpsimd_preserve_current_state();
	अगर (test_thपढ़ो_flag(TIF_SVE))
		sve_to_fpsimd(current);
पूर्ण

/*
 * Associate current's FPSIMD context with this cpu
 * The caller must have ownership of the cpu FPSIMD context beक्रमe calling
 * this function.
 */
व्योम fpsimd_bind_task_to_cpu(व्योम)
अणु
	काष्ठा fpsimd_last_state_काष्ठा *last =
		this_cpu_ptr(&fpsimd_last_state);

	WARN_ON(!प्रणाली_supports_fpsimd());
	last->st = &current->thपढ़ो.uw.fpsimd_state;
	last->sve_state = current->thपढ़ो.sve_state;
	last->sve_vl = current->thपढ़ो.sve_vl;
	current->thपढ़ो.fpsimd_cpu = smp_processor_id();

	अगर (प्रणाली_supports_sve()) अणु
		/* Toggle SVE trapping क्रम userspace अगर needed */
		अगर (test_thपढ़ो_flag(TIF_SVE))
			sve_user_enable();
		अन्यथा
			sve_user_disable();

		/* Serialised by exception वापस to user */
	पूर्ण
पूर्ण

व्योम fpsimd_bind_state_to_cpu(काष्ठा user_fpsimd_state *st, व्योम *sve_state,
			      अचिन्हित पूर्णांक sve_vl)
अणु
	काष्ठा fpsimd_last_state_काष्ठा *last =
		this_cpu_ptr(&fpsimd_last_state);

	WARN_ON(!प्रणाली_supports_fpsimd());
	WARN_ON(!in_softirq() && !irqs_disabled());

	last->st = st;
	last->sve_state = sve_state;
	last->sve_vl = sve_vl;
पूर्ण

/*
 * Load the userland FPSIMD state of 'current' from memory, but only अगर the
 * FPSIMD state alपढ़ोy held in the रेजिस्टरs is /not/ the most recent FPSIMD
 * state of 'current'
 */
व्योम fpsimd_restore_current_state(व्योम)
अणु
	/*
	 * For the tasks that were created beक्रमe we detected the असलence of
	 * FP/SIMD, the TIF_FOREIGN_FPSTATE could be set via fpsimd_thपढ़ो_चयन(),
	 * e.g, init. This could be then inherited by the children processes.
	 * If we later detect that the प्रणाली करोesn't support FP/SIMD,
	 * we must clear the flag क्रम  all the tasks to indicate that the
	 * FPSTATE is clean (as we can't have one) to aव्योम looping क्रम ever in
	 * करो_notअगरy_resume().
	 */
	अगर (!प्रणाली_supports_fpsimd()) अणु
		clear_thपढ़ो_flag(TIF_FOREIGN_FPSTATE);
		वापस;
	पूर्ण

	get_cpu_fpsimd_context();

	अगर (test_and_clear_thपढ़ो_flag(TIF_FOREIGN_FPSTATE)) अणु
		task_fpsimd_load();
		fpsimd_bind_task_to_cpu();
	पूर्ण

	put_cpu_fpsimd_context();
पूर्ण

/*
 * Load an updated userland FPSIMD state क्रम 'current' from memory and set the
 * flag that indicates that the FPSIMD रेजिस्टर contents are the most recent
 * FPSIMD state of 'current'
 */
व्योम fpsimd_update_current_state(काष्ठा user_fpsimd_state स्थिर *state)
अणु
	अगर (WARN_ON(!प्रणाली_supports_fpsimd()))
		वापस;

	get_cpu_fpsimd_context();

	current->thपढ़ो.uw.fpsimd_state = *state;
	अगर (test_thपढ़ो_flag(TIF_SVE))
		fpsimd_to_sve(current);

	task_fpsimd_load();
	fpsimd_bind_task_to_cpu();

	clear_thपढ़ो_flag(TIF_FOREIGN_FPSTATE);

	put_cpu_fpsimd_context();
पूर्ण

/*
 * Invalidate live CPU copies of task t's FPSIMD state
 *
 * This function may be called with preemption enabled.  The barrier()
 * ensures that the assignment to fpsimd_cpu is visible to any
 * preemption/softirq that could race with set_tsk_thपढ़ो_flag(), so
 * that TIF_FOREIGN_FPSTATE cannot be spuriously re-cleared.
 *
 * The final barrier ensures that TIF_FOREIGN_FPSTATE is seen set by any
 * subsequent code.
 */
व्योम fpsimd_flush_task_state(काष्ठा task_काष्ठा *t)
अणु
	t->thपढ़ो.fpsimd_cpu = NR_CPUS;
	/*
	 * If we करोn't support fpsimd, bail out after we have
	 * reset the fpsimd_cpu क्रम this task and clear the
	 * FPSTATE.
	 */
	अगर (!प्रणाली_supports_fpsimd())
		वापस;
	barrier();
	set_tsk_thपढ़ो_flag(t, TIF_FOREIGN_FPSTATE);

	barrier();
पूर्ण

/*
 * Invalidate any task's FPSIMD state that is present on this cpu.
 * The FPSIMD context should be acquired with get_cpu_fpsimd_context()
 * beक्रमe calling this function.
 */
अटल व्योम fpsimd_flush_cpu_state(व्योम)
अणु
	WARN_ON(!प्रणाली_supports_fpsimd());
	__this_cpu_ग_लिखो(fpsimd_last_state.st, शून्य);
	set_thपढ़ो_flag(TIF_FOREIGN_FPSTATE);
पूर्ण

/*
 * Save the FPSIMD state to memory and invalidate cpu view.
 * This function must be called with preemption disabled.
 */
व्योम fpsimd_save_and_flush_cpu_state(व्योम)
अणु
	अगर (!प्रणाली_supports_fpsimd())
		वापस;
	WARN_ON(preemptible());
	__get_cpu_fpsimd_context();
	fpsimd_save();
	fpsimd_flush_cpu_state();
	__put_cpu_fpsimd_context();
पूर्ण

#अगर_घोषित CONFIG_KERNEL_MODE_NEON

/*
 * Kernel-side NEON support functions
 */

/*
 * kernel_neon_begin(): obtain the CPU FPSIMD रेजिस्टरs क्रम use by the calling
 * context
 *
 * Must not be called unless may_use_simd() वापसs true.
 * Task context in the FPSIMD रेजिस्टरs is saved back to memory as necessary.
 *
 * A matching call to kernel_neon_end() must be made beक्रमe वापसing from the
 * calling context.
 *
 * The caller may मुक्तly use the FPSIMD रेजिस्टरs until kernel_neon_end() is
 * called.
 */
व्योम kernel_neon_begin(व्योम)
अणु
	अगर (WARN_ON(!प्रणाली_supports_fpsimd()))
		वापस;

	BUG_ON(!may_use_simd());

	get_cpu_fpsimd_context();

	/* Save unsaved fpsimd state, अगर any: */
	fpsimd_save();

	/* Invalidate any task state reमुख्यing in the fpsimd regs: */
	fpsimd_flush_cpu_state();
पूर्ण
EXPORT_SYMBOL(kernel_neon_begin);

/*
 * kernel_neon_end(): give the CPU FPSIMD रेजिस्टरs back to the current task
 *
 * Must be called from a context in which kernel_neon_begin() was previously
 * called, with no call to kernel_neon_end() in the meanसमय.
 *
 * The caller must not use the FPSIMD रेजिस्टरs after this function is called,
 * unless kernel_neon_begin() is called again in the meanसमय.
 */
व्योम kernel_neon_end(व्योम)
अणु
	अगर (!प्रणाली_supports_fpsimd())
		वापस;

	put_cpu_fpsimd_context();
पूर्ण
EXPORT_SYMBOL(kernel_neon_end);

#अगर_घोषित CONFIG_EFI

अटल DEFINE_PER_CPU(काष्ठा user_fpsimd_state, efi_fpsimd_state);
अटल DEFINE_PER_CPU(bool, efi_fpsimd_state_used);
अटल DEFINE_PER_CPU(bool, efi_sve_state_used);

/*
 * EFI runसमय services support functions
 *
 * The ABI क्रम EFI runसमय services allows EFI to use FPSIMD during the call.
 * This means that क्रम EFI (and only क्रम EFI), we have to assume that FPSIMD
 * is always used rather than being an optional accelerator.
 *
 * These functions provide the necessary support क्रम ensuring FPSIMD
 * save/restore in the contexts from which EFI is used.
 *
 * Do not use them क्रम any other purpose -- अगर tempted to करो so, you are
 * either करोing something wrong or you need to propose some refactoring.
 */

/*
 * __efi_fpsimd_begin(): prepare FPSIMD क्रम making an EFI runसमय services call
 */
व्योम __efi_fpsimd_begin(व्योम)
अणु
	अगर (!प्रणाली_supports_fpsimd())
		वापस;

	WARN_ON(preemptible());

	अगर (may_use_simd()) अणु
		kernel_neon_begin();
	पूर्ण अन्यथा अणु
		/*
		 * If !efi_sve_state, SVE can't be in use yet and doesn't need
		 * preserving:
		 */
		अगर (प्रणाली_supports_sve() && likely(efi_sve_state)) अणु
			अक्षर *sve_state = this_cpu_ptr(efi_sve_state);

			__this_cpu_ग_लिखो(efi_sve_state_used, true);

			sve_save_state(sve_state + sve_ffr_offset(sve_max_vl),
				       &this_cpu_ptr(&efi_fpsimd_state)->fpsr);
		पूर्ण अन्यथा अणु
			fpsimd_save_state(this_cpu_ptr(&efi_fpsimd_state));
		पूर्ण

		__this_cpu_ग_लिखो(efi_fpsimd_state_used, true);
	पूर्ण
पूर्ण

/*
 * __efi_fpsimd_end(): clean up FPSIMD after an EFI runसमय services call
 */
व्योम __efi_fpsimd_end(व्योम)
अणु
	अगर (!प्रणाली_supports_fpsimd())
		वापस;

	अगर (!__this_cpu_xchg(efi_fpsimd_state_used, false)) अणु
		kernel_neon_end();
	पूर्ण अन्यथा अणु
		अगर (प्रणाली_supports_sve() &&
		    likely(__this_cpu_पढ़ो(efi_sve_state_used))) अणु
			अक्षर स्थिर *sve_state = this_cpu_ptr(efi_sve_state);

			sve_load_state(sve_state + sve_ffr_offset(sve_max_vl),
				       &this_cpu_ptr(&efi_fpsimd_state)->fpsr,
				       sve_vq_from_vl(sve_get_vl()) - 1);

			__this_cpu_ग_लिखो(efi_sve_state_used, false);
		पूर्ण अन्यथा अणु
			fpsimd_load_state(this_cpu_ptr(&efi_fpsimd_state));
		पूर्ण
	पूर्ण
पूर्ण

#पूर्ण_अगर /* CONFIG_EFI */

#पूर्ण_अगर /* CONFIG_KERNEL_MODE_NEON */

#अगर_घोषित CONFIG_CPU_PM
अटल पूर्णांक fpsimd_cpu_pm_notअगरier(काष्ठा notअगरier_block *self,
				  अचिन्हित दीर्घ cmd, व्योम *v)
अणु
	चयन (cmd) अणु
	हाल CPU_PM_ENTER:
		fpsimd_save_and_flush_cpu_state();
		अवरोध;
	हाल CPU_PM_EXIT:
		अवरोध;
	हाल CPU_PM_ENTER_FAILED:
	शेष:
		वापस NOTIFY_DONE;
	पूर्ण
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block fpsimd_cpu_pm_notअगरier_block = अणु
	.notअगरier_call = fpsimd_cpu_pm_notअगरier,
पूर्ण;

अटल व्योम __init fpsimd_pm_init(व्योम)
अणु
	cpu_pm_रेजिस्टर_notअगरier(&fpsimd_cpu_pm_notअगरier_block);
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम fpsimd_pm_init(व्योम) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_CPU_PM */

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल पूर्णांक fpsimd_cpu_dead(अचिन्हित पूर्णांक cpu)
अणु
	per_cpu(fpsimd_last_state.st, cpu) = शून्य;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम fpsimd_hotplug_init(व्योम)
अणु
	cpuhp_setup_state_nocalls(CPUHP_ARM64_FPSIMD_DEAD, "arm64/fpsimd:dead",
				  शून्य, fpsimd_cpu_dead);
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम fpsimd_hotplug_init(व्योम) अणु पूर्ण
#पूर्ण_अगर

/*
 * FP/SIMD support code initialisation.
 */
अटल पूर्णांक __init fpsimd_init(व्योम)
अणु
	अगर (cpu_have_named_feature(FP)) अणु
		fpsimd_pm_init();
		fpsimd_hotplug_init();
	पूर्ण अन्यथा अणु
		pr_notice("Floating-point is not implemented\n");
	पूर्ण

	अगर (!cpu_have_named_feature(ASIMD))
		pr_notice("Advanced SIMD is not implemented\n");

	वापस sve_sysctl_init();
पूर्ण
core_initcall(fpsimd_init);
