<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1992 Ross Biro
 * Copyright (C) Linus Torvalds
 * Copyright (C) 1994, 95, 96, 97, 98, 2000 Ralf Baechle
 * Copyright (C) 1996 David S. Miller
 * Kevin D. Kissell, kevink@mips.com and Carsten Langgaard, carstenl@mips.com
 * Copyright (C) 1999 MIPS Technologies, Inc.
 * Copyright (C) 2000 Ulf Carlsson
 *
 * At this समय Linux/MIPS64 only supports syscall tracing, even क्रम 32-bit
 * binaries.
 */
#समावेश <linux/compiler.h>
#समावेश <linux/context_tracking.h>
#समावेश <linux/elf.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/mm.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/regset.h>
#समावेश <linux/smp.h>
#समावेश <linux/security.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/tracehook.h>
#समावेश <linux/audit.h>
#समावेश <linux/seccomp.h>
#समावेश <linux/ftrace.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/cpu-info.h>
#समावेश <यंत्र/dsp.h>
#समावेश <यंत्र/fpu.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/mipsmtregs.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/syscall.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/reg.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/syscalls.h>

/*
 * Called by kernel/ptrace.c when detaching..
 *
 * Make sure single step bits etc are not set.
 */
व्योम ptrace_disable(काष्ठा task_काष्ठा *child)
अणु
	/* Don't load the watchpoपूर्णांक रेजिस्टरs क्रम the ex-child. */
	clear_tsk_thपढ़ो_flag(child, TIF_LOAD_WATCH);
पूर्ण

/*
 * Read a general रेजिस्टर set.	 We always use the 64-bit क्रमmat, even
 * क्रम 32-bit kernels and क्रम 32-bit processes on a 64-bit kernel.
 * Registers are sign extended to fill the available space.
 */
पूर्णांक ptrace_getregs(काष्ठा task_काष्ठा *child, काष्ठा user_pt_regs __user *data)
अणु
	काष्ठा pt_regs *regs;
	पूर्णांक i;

	अगर (!access_ok(data, 38 * 8))
		वापस -EIO;

	regs = task_pt_regs(child);

	क्रम (i = 0; i < 32; i++)
		__put_user((दीर्घ)regs->regs[i], (__s64 __user *)&data->regs[i]);
	__put_user((दीर्घ)regs->lo, (__s64 __user *)&data->lo);
	__put_user((दीर्घ)regs->hi, (__s64 __user *)&data->hi);
	__put_user((दीर्घ)regs->cp0_epc, (__s64 __user *)&data->cp0_epc);
	__put_user((दीर्घ)regs->cp0_badvaddr, (__s64 __user *)&data->cp0_badvaddr);
	__put_user((दीर्घ)regs->cp0_status, (__s64 __user *)&data->cp0_status);
	__put_user((दीर्घ)regs->cp0_cause, (__s64 __user *)&data->cp0_cause);

	वापस 0;
पूर्ण

/*
 * Write a general रेजिस्टर set.  As क्रम PTRACE_GETREGS, we always use
 * the 64-bit क्रमmat.  On a 32-bit kernel only the lower order half
 * (according to endianness) will be used.
 */
पूर्णांक ptrace_setregs(काष्ठा task_काष्ठा *child, काष्ठा user_pt_regs __user *data)
अणु
	काष्ठा pt_regs *regs;
	पूर्णांक i;

	अगर (!access_ok(data, 38 * 8))
		वापस -EIO;

	regs = task_pt_regs(child);

	क्रम (i = 0; i < 32; i++)
		__get_user(regs->regs[i], (__s64 __user *)&data->regs[i]);
	__get_user(regs->lo, (__s64 __user *)&data->lo);
	__get_user(regs->hi, (__s64 __user *)&data->hi);
	__get_user(regs->cp0_epc, (__s64 __user *)&data->cp0_epc);

	/* badvaddr, status, and cause may not be written.  */

	/* System call number may have been changed */
	mips_syscall_update_nr(child, regs);

	वापस 0;
पूर्ण

पूर्णांक ptrace_get_watch_regs(काष्ठा task_काष्ठा *child,
			  काष्ठा pt_watch_regs __user *addr)
अणु
	क्रमागत pt_watch_style style;
	पूर्णांक i;

	अगर (!cpu_has_watch || boot_cpu_data.watch_reg_use_cnt == 0)
		वापस -EIO;
	अगर (!access_ok(addr, माप(काष्ठा pt_watch_regs)))
		वापस -EIO;

#अगर_घोषित CONFIG_32BIT
	style = pt_watch_style_mips32;
#घोषणा WATCH_STYLE mips32
#अन्यथा
	style = pt_watch_style_mips64;
#घोषणा WATCH_STYLE mips64
#पूर्ण_अगर

	__put_user(style, &addr->style);
	__put_user(boot_cpu_data.watch_reg_use_cnt,
		   &addr->WATCH_STYLE.num_valid);
	क्रम (i = 0; i < boot_cpu_data.watch_reg_use_cnt; i++) अणु
		__put_user(child->thपढ़ो.watch.mips3264.watchlo[i],
			   &addr->WATCH_STYLE.watchlo[i]);
		__put_user(child->thपढ़ो.watch.mips3264.watchhi[i] &
				(MIPS_WATCHHI_MASK | MIPS_WATCHHI_IRW),
			   &addr->WATCH_STYLE.watchhi[i]);
		__put_user(boot_cpu_data.watch_reg_masks[i],
			   &addr->WATCH_STYLE.watch_masks[i]);
	पूर्ण
	क्रम (; i < 8; i++) अणु
		__put_user(0, &addr->WATCH_STYLE.watchlo[i]);
		__put_user(0, &addr->WATCH_STYLE.watchhi[i]);
		__put_user(0, &addr->WATCH_STYLE.watch_masks[i]);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ptrace_set_watch_regs(काष्ठा task_काष्ठा *child,
			  काष्ठा pt_watch_regs __user *addr)
अणु
	पूर्णांक i;
	पूर्णांक watch_active = 0;
	अचिन्हित दीर्घ lt[NUM_WATCH_REGS];
	u16 ht[NUM_WATCH_REGS];

	अगर (!cpu_has_watch || boot_cpu_data.watch_reg_use_cnt == 0)
		वापस -EIO;
	अगर (!access_ok(addr, माप(काष्ठा pt_watch_regs)))
		वापस -EIO;
	/* Check the values. */
	क्रम (i = 0; i < boot_cpu_data.watch_reg_use_cnt; i++) अणु
		__get_user(lt[i], &addr->WATCH_STYLE.watchlo[i]);
#अगर_घोषित CONFIG_32BIT
		अगर (lt[i] & __UA_LIMIT)
			वापस -EINVAL;
#अन्यथा
		अगर (test_tsk_thपढ़ो_flag(child, TIF_32BIT_ADDR)) अणु
			अगर (lt[i] & 0xffffffff80000000UL)
				वापस -EINVAL;
		पूर्ण अन्यथा अणु
			अगर (lt[i] & __UA_LIMIT)
				वापस -EINVAL;
		पूर्ण
#पूर्ण_अगर
		__get_user(ht[i], &addr->WATCH_STYLE.watchhi[i]);
		अगर (ht[i] & ~MIPS_WATCHHI_MASK)
			वापस -EINVAL;
	पूर्ण
	/* Install them. */
	क्रम (i = 0; i < boot_cpu_data.watch_reg_use_cnt; i++) अणु
		अगर (lt[i] & MIPS_WATCHLO_IRW)
			watch_active = 1;
		child->thपढ़ो.watch.mips3264.watchlo[i] = lt[i];
		/* Set the G bit. */
		child->thपढ़ो.watch.mips3264.watchhi[i] = ht[i];
	पूर्ण

	अगर (watch_active)
		set_tsk_thपढ़ो_flag(child, TIF_LOAD_WATCH);
	अन्यथा
		clear_tsk_thपढ़ो_flag(child, TIF_LOAD_WATCH);

	वापस 0;
पूर्ण

/* regset get/set implementations */

#अगर defined(CONFIG_32BIT) || defined(CONFIG_MIPS32_O32)

अटल पूर्णांक gpr32_get(काष्ठा task_काष्ठा *target,
		     स्थिर काष्ठा user_regset *regset,
		     काष्ठा membuf to)
अणु
	काष्ठा pt_regs *regs = task_pt_regs(target);
	u32 uregs[ELF_NGREG] = अणुपूर्ण;

	mips_dump_regs32(uregs, regs);
	वापस membuf_ग_लिखो(&to, uregs, माप(uregs));
पूर्ण

अटल पूर्णांक gpr32_set(काष्ठा task_काष्ठा *target,
		     स्थिर काष्ठा user_regset *regset,
		     अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		     स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	काष्ठा pt_regs *regs = task_pt_regs(target);
	u32 uregs[ELF_NGREG];
	अचिन्हित start, num_regs, i;
	पूर्णांक err;

	start = pos / माप(u32);
	num_regs = count / माप(u32);

	अगर (start + num_regs > ELF_NGREG)
		वापस -EIO;

	err = user_regset_copyin(&pos, &count, &kbuf, &ubuf, uregs, 0,
				 माप(uregs));
	अगर (err)
		वापस err;

	क्रम (i = start; i < num_regs; i++) अणु
		/*
		 * Cast all values to चिन्हित here so that अगर this is a 64-bit
		 * kernel, the supplied 32-bit values will be sign extended.
		 */
		चयन (i) अणु
		हाल MIPS32_EF_R1 ... MIPS32_EF_R25:
			/* k0/k1 are ignored. */
		हाल MIPS32_EF_R28 ... MIPS32_EF_R31:
			regs->regs[i - MIPS32_EF_R0] = (s32)uregs[i];
			अवरोध;
		हाल MIPS32_EF_LO:
			regs->lo = (s32)uregs[i];
			अवरोध;
		हाल MIPS32_EF_HI:
			regs->hi = (s32)uregs[i];
			अवरोध;
		हाल MIPS32_EF_CP0_EPC:
			regs->cp0_epc = (s32)uregs[i];
			अवरोध;
		पूर्ण
	पूर्ण

	/* System call number may have been changed */
	mips_syscall_update_nr(target, regs);

	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_32BIT || CONFIG_MIPS32_O32 */

#अगर_घोषित CONFIG_64BIT

अटल पूर्णांक gpr64_get(काष्ठा task_काष्ठा *target,
		     स्थिर काष्ठा user_regset *regset,
		     काष्ठा membuf to)
अणु
	काष्ठा pt_regs *regs = task_pt_regs(target);
	u64 uregs[ELF_NGREG] = अणुपूर्ण;

	mips_dump_regs64(uregs, regs);
	वापस membuf_ग_लिखो(&to, uregs, माप(uregs));
पूर्ण

अटल पूर्णांक gpr64_set(काष्ठा task_काष्ठा *target,
		     स्थिर काष्ठा user_regset *regset,
		     अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		     स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	काष्ठा pt_regs *regs = task_pt_regs(target);
	u64 uregs[ELF_NGREG];
	अचिन्हित start, num_regs, i;
	पूर्णांक err;

	start = pos / माप(u64);
	num_regs = count / माप(u64);

	अगर (start + num_regs > ELF_NGREG)
		वापस -EIO;

	err = user_regset_copyin(&pos, &count, &kbuf, &ubuf, uregs, 0,
				 माप(uregs));
	अगर (err)
		वापस err;

	क्रम (i = start; i < num_regs; i++) अणु
		चयन (i) अणु
		हाल MIPS64_EF_R1 ... MIPS64_EF_R25:
			/* k0/k1 are ignored. */
		हाल MIPS64_EF_R28 ... MIPS64_EF_R31:
			regs->regs[i - MIPS64_EF_R0] = uregs[i];
			अवरोध;
		हाल MIPS64_EF_LO:
			regs->lo = uregs[i];
			अवरोध;
		हाल MIPS64_EF_HI:
			regs->hi = uregs[i];
			अवरोध;
		हाल MIPS64_EF_CP0_EPC:
			regs->cp0_epc = uregs[i];
			अवरोध;
		पूर्ण
	पूर्ण

	/* System call number may have been changed */
	mips_syscall_update_nr(target, regs);

	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_64BIT */


#अगर_घोषित CONFIG_MIPS_FP_SUPPORT

/*
 * Poke at FCSR according to its mask.  Set the Cause bits even
 * अगर a corresponding Enable bit is set.  This will be noticed at
 * the समय the thपढ़ो is चयनed to and संक_भ_त्रुटि thrown accordingly.
 */
अटल व्योम ptrace_setfcr31(काष्ठा task_काष्ठा *child, u32 value)
अणु
	u32 fcr31;
	u32 mask;

	fcr31 = child->thपढ़ो.fpu.fcr31;
	mask = boot_cpu_data.fpu_msk31;
	child->thपढ़ो.fpu.fcr31 = (value & ~mask) | (fcr31 & mask);
पूर्ण

पूर्णांक ptrace_getfpregs(काष्ठा task_काष्ठा *child, __u32 __user *data)
अणु
	पूर्णांक i;

	अगर (!access_ok(data, 33 * 8))
		वापस -EIO;

	अगर (tsk_used_math(child)) अणु
		जोड़ fpureg *fregs = get_fpu_regs(child);
		क्रम (i = 0; i < 32; i++)
			__put_user(get_fpr64(&fregs[i], 0),
				   i + (__u64 __user *)data);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < 32; i++)
			__put_user((__u64) -1, i + (__u64 __user *) data);
	पूर्ण

	__put_user(child->thपढ़ो.fpu.fcr31, data + 64);
	__put_user(boot_cpu_data.fpu_id, data + 65);

	वापस 0;
पूर्ण

पूर्णांक ptrace_setfpregs(काष्ठा task_काष्ठा *child, __u32 __user *data)
अणु
	जोड़ fpureg *fregs;
	u64 fpr_val;
	u32 value;
	पूर्णांक i;

	अगर (!access_ok(data, 33 * 8))
		वापस -EIO;

	init_fp_ctx(child);
	fregs = get_fpu_regs(child);

	क्रम (i = 0; i < 32; i++) अणु
		__get_user(fpr_val, i + (__u64 __user *)data);
		set_fpr64(&fregs[i], 0, fpr_val);
	पूर्ण

	__get_user(value, data + 64);
	ptrace_setfcr31(child, value);

	/* FIR may not be written.  */

	वापस 0;
पूर्ण

/*
 * Copy the भग्नing-poपूर्णांक context to the supplied NT_PRFPREG buffer,
 * !CONFIG_CPU_HAS_MSA variant.  FP context's general रेजिस्टर slots
 * correspond 1:1 to buffer slots.  Only general रेजिस्टरs are copied.
 */
अटल व्योम fpr_get_fpa(काष्ठा task_काष्ठा *target,
		       काष्ठा membuf *to)
अणु
	membuf_ग_लिखो(to, &target->thपढ़ो.fpu,
			NUM_FPU_REGS * माप(elf_fpreg_t));
पूर्ण

/*
 * Copy the भग्नing-poपूर्णांक context to the supplied NT_PRFPREG buffer,
 * CONFIG_CPU_HAS_MSA variant.  Only lower 64 bits of FP context's
 * general रेजिस्टर slots are copied to buffer slots.  Only general
 * रेजिस्टरs are copied.
 */
अटल व्योम fpr_get_msa(काष्ठा task_काष्ठा *target, काष्ठा membuf *to)
अणु
	अचिन्हित पूर्णांक i;

	BUILD_BUG_ON(माप(u64) != माप(elf_fpreg_t));
	क्रम (i = 0; i < NUM_FPU_REGS; i++)
		membuf_store(to, get_fpr64(&target->thपढ़ो.fpu.fpr[i], 0));
पूर्ण

/*
 * Copy the भग्नing-poपूर्णांक context to the supplied NT_PRFPREG buffer.
 * Choose the appropriate helper क्रम general रेजिस्टरs, and then copy
 * the FCSR and FIR रेजिस्टरs separately.
 */
अटल पूर्णांक fpr_get(काष्ठा task_काष्ठा *target,
		   स्थिर काष्ठा user_regset *regset,
		   काष्ठा membuf to)
अणु
	अगर (माप(target->thपढ़ो.fpu.fpr[0]) == माप(elf_fpreg_t))
		fpr_get_fpa(target, &to);
	अन्यथा
		fpr_get_msa(target, &to);

	membuf_ग_लिखो(&to, &target->thपढ़ो.fpu.fcr31, माप(u32));
	membuf_ग_लिखो(&to, &boot_cpu_data.fpu_id, माप(u32));
	वापस 0;
पूर्ण

/*
 * Copy the supplied NT_PRFPREG buffer to the भग्नing-poपूर्णांक context,
 * !CONFIG_CPU_HAS_MSA variant.   Buffer slots correspond 1:1 to FP
 * context's general रेजिस्टर slots.  Only general रेजिस्टरs are copied.
 */
अटल पूर्णांक fpr_set_fpa(काष्ठा task_काष्ठा *target,
		       अचिन्हित पूर्णांक *pos, अचिन्हित पूर्णांक *count,
		       स्थिर व्योम **kbuf, स्थिर व्योम __user **ubuf)
अणु
	वापस user_regset_copyin(pos, count, kbuf, ubuf,
				  &target->thपढ़ो.fpu,
				  0, NUM_FPU_REGS * माप(elf_fpreg_t));
पूर्ण

/*
 * Copy the supplied NT_PRFPREG buffer to the भग्नing-poपूर्णांक context,
 * CONFIG_CPU_HAS_MSA variant.  Buffer slots are copied to lower 64
 * bits only of FP context's general रेजिस्टर slots.  Only general
 * रेजिस्टरs are copied.
 */
अटल पूर्णांक fpr_set_msa(काष्ठा task_काष्ठा *target,
		       अचिन्हित पूर्णांक *pos, अचिन्हित पूर्णांक *count,
		       स्थिर व्योम **kbuf, स्थिर व्योम __user **ubuf)
अणु
	अचिन्हित पूर्णांक i;
	u64 fpr_val;
	पूर्णांक err;

	BUILD_BUG_ON(माप(fpr_val) != माप(elf_fpreg_t));
	क्रम (i = 0; i < NUM_FPU_REGS && *count > 0; i++) अणु
		err = user_regset_copyin(pos, count, kbuf, ubuf,
					 &fpr_val, i * माप(elf_fpreg_t),
					 (i + 1) * माप(elf_fpreg_t));
		अगर (err)
			वापस err;
		set_fpr64(&target->thपढ़ो.fpu.fpr[i], 0, fpr_val);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Copy the supplied NT_PRFPREG buffer to the भग्नing-poपूर्णांक context.
 * Choose the appropriate helper क्रम general रेजिस्टरs, and then copy
 * the FCSR रेजिस्टर separately.  Ignore the incoming FIR रेजिस्टर
 * contents though, as the रेजिस्टर is पढ़ो-only.
 *
 * We optimize क्रम the हाल where `count % माप(elf_fpreg_t) == 0',
 * which is supposed to have been guaranteed by the kernel beक्रमe
 * calling us, e.g. in `ptrace_regset'.  We enक्रमce that requirement,
 * so that we can safely aव्योम preinitializing temporaries क्रम
 * partial रेजिस्टर ग_लिखोs.
 */
अटल पूर्णांक fpr_set(काष्ठा task_काष्ठा *target,
		   स्थिर काष्ठा user_regset *regset,
		   अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		   स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	स्थिर पूर्णांक fcr31_pos = NUM_FPU_REGS * माप(elf_fpreg_t);
	स्थिर पूर्णांक fir_pos = fcr31_pos + माप(u32);
	u32 fcr31;
	पूर्णांक err;

	BUG_ON(count % माप(elf_fpreg_t));

	अगर (pos + count > माप(elf_fpregset_t))
		वापस -EIO;

	init_fp_ctx(target);

	अगर (माप(target->thपढ़ो.fpu.fpr[0]) == माप(elf_fpreg_t))
		err = fpr_set_fpa(target, &pos, &count, &kbuf, &ubuf);
	अन्यथा
		err = fpr_set_msa(target, &pos, &count, &kbuf, &ubuf);
	अगर (err)
		वापस err;

	अगर (count > 0) अणु
		err = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
					 &fcr31,
					 fcr31_pos, fcr31_pos + माप(u32));
		अगर (err)
			वापस err;

		ptrace_setfcr31(target, fcr31);
	पूर्ण

	अगर (count > 0)
		err = user_regset_copyin_ignore(&pos, &count, &kbuf, &ubuf,
						fir_pos,
						fir_pos + माप(u32));

	वापस err;
पूर्ण

/* Copy the FP mode setting to the supplied NT_MIPS_FP_MODE buffer.  */
अटल पूर्णांक fp_mode_get(काष्ठा task_काष्ठा *target,
		       स्थिर काष्ठा user_regset *regset,
		       काष्ठा membuf to)
अणु
	वापस membuf_store(&to, (पूर्णांक)mips_get_process_fp_mode(target));
पूर्ण

/*
 * Copy the supplied NT_MIPS_FP_MODE buffer to the FP mode setting.
 *
 * We optimize क्रम the हाल where `count % माप(पूर्णांक) == 0', which
 * is supposed to have been guaranteed by the kernel beक्रमe calling
 * us, e.g. in `ptrace_regset'.  We enक्रमce that requirement, so
 * that we can safely aव्योम preinitializing temporaries क्रम partial
 * mode ग_लिखोs.
 */
अटल पूर्णांक fp_mode_set(काष्ठा task_काष्ठा *target,
		       स्थिर काष्ठा user_regset *regset,
		       अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		       स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	पूर्णांक fp_mode;
	पूर्णांक err;

	BUG_ON(count % माप(पूर्णांक));

	अगर (pos + count > माप(fp_mode))
		वापस -EIO;

	err = user_regset_copyin(&pos, &count, &kbuf, &ubuf, &fp_mode, 0,
				 माप(fp_mode));
	अगर (err)
		वापस err;

	अगर (count > 0)
		err = mips_set_process_fp_mode(target, fp_mode);

	वापस err;
पूर्ण

#पूर्ण_अगर /* CONFIG_MIPS_FP_SUPPORT */

#अगर_घोषित CONFIG_CPU_HAS_MSA

काष्ठा msa_control_regs अणु
	अचिन्हित पूर्णांक fir;
	अचिन्हित पूर्णांक fcsr;
	अचिन्हित पूर्णांक msair;
	अचिन्हित पूर्णांक msacsr;
पूर्ण;

अटल व्योम copy_pad_fprs(काष्ठा task_काष्ठा *target,
			 स्थिर काष्ठा user_regset *regset,
			 काष्ठा membuf *to,
			 अचिन्हित पूर्णांक live_sz)
अणु
	पूर्णांक i, j;
	अचिन्हित दीर्घ दीर्घ fill = ~0ull;
	अचिन्हित पूर्णांक cp_sz, pad_sz;

	cp_sz = min(regset->size, live_sz);
	pad_sz = regset->size - cp_sz;
	WARN_ON(pad_sz % माप(fill));

	क्रम (i = 0; i < NUM_FPU_REGS; i++) अणु
		membuf_ग_लिखो(to, &target->thपढ़ो.fpu.fpr[i], cp_sz);
		क्रम (j = 0; j < (pad_sz / माप(fill)); j++)
			membuf_store(to, fill);
	पूर्ण
पूर्ण

अटल पूर्णांक msa_get(काष्ठा task_काष्ठा *target,
		   स्थिर काष्ठा user_regset *regset,
		   काष्ठा membuf to)
अणु
	स्थिर अचिन्हित पूर्णांक wr_size = NUM_FPU_REGS * regset->size;
	स्थिर काष्ठा msa_control_regs ctrl_regs = अणु
		.fir = boot_cpu_data.fpu_id,
		.fcsr = target->thपढ़ो.fpu.fcr31,
		.msair = boot_cpu_data.msa_id,
		.msacsr = target->thपढ़ो.fpu.msacsr,
	पूर्ण;

	अगर (!tsk_used_math(target)) अणु
		/* The task hasn't used FP or MSA, fill with 0xff */
		copy_pad_fprs(target, regset, &to, 0);
	पूर्ण अन्यथा अगर (!test_tsk_thपढ़ो_flag(target, TIF_MSA_CTX_LIVE)) अणु
		/* Copy scalar FP context, fill the rest with 0xff */
		copy_pad_fprs(target, regset, &to, 8);
	पूर्ण अन्यथा अगर (माप(target->thपढ़ो.fpu.fpr[0]) == regset->size) अणु
		/* Trivially copy the vector रेजिस्टरs */
		membuf_ग_लिखो(&to, &target->thपढ़ो.fpu.fpr, wr_size);
	पूर्ण अन्यथा अणु
		/* Copy as much context as possible, fill the rest with 0xff */
		copy_pad_fprs(target, regset, &to,
				माप(target->thपढ़ो.fpu.fpr[0]));
	पूर्ण

	वापस membuf_ग_लिखो(&to, &ctrl_regs, माप(ctrl_regs));
पूर्ण

अटल पूर्णांक msa_set(काष्ठा task_काष्ठा *target,
		   स्थिर काष्ठा user_regset *regset,
		   अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		   स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	स्थिर अचिन्हित पूर्णांक wr_size = NUM_FPU_REGS * regset->size;
	काष्ठा msa_control_regs ctrl_regs;
	अचिन्हित पूर्णांक cp_sz;
	पूर्णांक i, err, start;

	init_fp_ctx(target);

	अगर (माप(target->thपढ़ो.fpu.fpr[0]) == regset->size) अणु
		/* Trivially copy the vector रेजिस्टरs */
		err = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
					 &target->thपढ़ो.fpu.fpr,
					 0, wr_size);
	पूर्ण अन्यथा अणु
		/* Copy as much context as possible */
		cp_sz = min_t(अचिन्हित पूर्णांक, regset->size,
			      माप(target->thपढ़ो.fpu.fpr[0]));

		i = start = err = 0;
		क्रम (; i < NUM_FPU_REGS; i++, start += regset->size) अणु
			err |= user_regset_copyin(&pos, &count, &kbuf, &ubuf,
						  &target->thपढ़ो.fpu.fpr[i],
						  start, start + cp_sz);
		पूर्ण
	पूर्ण

	अगर (!err)
		err = user_regset_copyin(&pos, &count, &kbuf, &ubuf, &ctrl_regs,
					 wr_size, wr_size + माप(ctrl_regs));
	अगर (!err) अणु
		target->thपढ़ो.fpu.fcr31 = ctrl_regs.fcsr & ~FPU_CSR_ALL_X;
		target->thपढ़ो.fpu.msacsr = ctrl_regs.msacsr & ~MSA_CSR_CAUSEF;
	पूर्ण

	वापस err;
पूर्ण

#पूर्ण_अगर /* CONFIG_CPU_HAS_MSA */

#अगर defined(CONFIG_32BIT) || defined(CONFIG_MIPS32_O32)

/*
 * Copy the DSP context to the supplied 32-bit NT_MIPS_DSP buffer.
 */
अटल पूर्णांक dsp32_get(काष्ठा task_काष्ठा *target,
		     स्थिर काष्ठा user_regset *regset,
		     काष्ठा membuf to)
अणु
	u32 dspregs[NUM_DSP_REGS + 1];
	अचिन्हित पूर्णांक i;

	BUG_ON(to.left % माप(u32));

	अगर (!cpu_has_dsp)
		वापस -EIO;

	क्रम (i = 0; i < NUM_DSP_REGS; i++)
		dspregs[i] = target->thपढ़ो.dsp.dspr[i];
	dspregs[NUM_DSP_REGS] = target->thपढ़ो.dsp.dspcontrol;
	वापस membuf_ग_लिखो(&to, dspregs, माप(dspregs));
पूर्ण

/*
 * Copy the supplied 32-bit NT_MIPS_DSP buffer to the DSP context.
 */
अटल पूर्णांक dsp32_set(काष्ठा task_काष्ठा *target,
		     स्थिर काष्ठा user_regset *regset,
		     अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		     स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	अचिन्हित पूर्णांक start, num_regs, i;
	u32 dspregs[NUM_DSP_REGS + 1];
	पूर्णांक err;

	BUG_ON(count % माप(u32));

	अगर (!cpu_has_dsp)
		वापस -EIO;

	start = pos / माप(u32);
	num_regs = count / माप(u32);

	अगर (start + num_regs > NUM_DSP_REGS + 1)
		वापस -EIO;

	err = user_regset_copyin(&pos, &count, &kbuf, &ubuf, dspregs, 0,
				 माप(dspregs));
	अगर (err)
		वापस err;

	क्रम (i = start; i < num_regs; i++)
		चयन (i) अणु
		हाल 0 ... NUM_DSP_REGS - 1:
			target->thपढ़ो.dsp.dspr[i] = (s32)dspregs[i];
			अवरोध;
		हाल NUM_DSP_REGS:
			target->thपढ़ो.dsp.dspcontrol = (s32)dspregs[i];
			अवरोध;
		पूर्ण

	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_32BIT || CONFIG_MIPS32_O32 */

#अगर_घोषित CONFIG_64BIT

/*
 * Copy the DSP context to the supplied 64-bit NT_MIPS_DSP buffer.
 */
अटल पूर्णांक dsp64_get(काष्ठा task_काष्ठा *target,
		     स्थिर काष्ठा user_regset *regset,
		     काष्ठा membuf to)
अणु
	u64 dspregs[NUM_DSP_REGS + 1];
	अचिन्हित पूर्णांक i;

	BUG_ON(to.left % माप(u64));

	अगर (!cpu_has_dsp)
		वापस -EIO;

	क्रम (i = 0; i < NUM_DSP_REGS; i++)
		dspregs[i] = target->thपढ़ो.dsp.dspr[i];
	dspregs[NUM_DSP_REGS] = target->thपढ़ो.dsp.dspcontrol;
	वापस membuf_ग_लिखो(&to, dspregs, माप(dspregs));
पूर्ण

/*
 * Copy the supplied 64-bit NT_MIPS_DSP buffer to the DSP context.
 */
अटल पूर्णांक dsp64_set(काष्ठा task_काष्ठा *target,
		     स्थिर काष्ठा user_regset *regset,
		     अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		     स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	अचिन्हित पूर्णांक start, num_regs, i;
	u64 dspregs[NUM_DSP_REGS + 1];
	पूर्णांक err;

	BUG_ON(count % माप(u64));

	अगर (!cpu_has_dsp)
		वापस -EIO;

	start = pos / माप(u64);
	num_regs = count / माप(u64);

	अगर (start + num_regs > NUM_DSP_REGS + 1)
		वापस -EIO;

	err = user_regset_copyin(&pos, &count, &kbuf, &ubuf, dspregs, 0,
				 माप(dspregs));
	अगर (err)
		वापस err;

	क्रम (i = start; i < num_regs; i++)
		चयन (i) अणु
		हाल 0 ... NUM_DSP_REGS - 1:
			target->thपढ़ो.dsp.dspr[i] = dspregs[i];
			अवरोध;
		हाल NUM_DSP_REGS:
			target->thपढ़ो.dsp.dspcontrol = dspregs[i];
			अवरोध;
		पूर्ण

	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_64BIT */

/*
 * Determine whether the DSP context is present.
 */
अटल पूर्णांक dsp_active(काष्ठा task_काष्ठा *target,
		      स्थिर काष्ठा user_regset *regset)
अणु
	वापस cpu_has_dsp ? NUM_DSP_REGS + 1 : -ENODEV;
पूर्ण

क्रमागत mips_regset अणु
	REGSET_GPR,
	REGSET_DSP,
#अगर_घोषित CONFIG_MIPS_FP_SUPPORT
	REGSET_FPR,
	REGSET_FP_MODE,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CPU_HAS_MSA
	REGSET_MSA,
#पूर्ण_अगर
पूर्ण;

काष्ठा pt_regs_offset अणु
	स्थिर अक्षर *name;
	पूर्णांक offset;
पूर्ण;

#घोषणा REG_OFFSET_NAME(reg, r) अणु					\
	.name = #reg,							\
	.offset = दुरत्व(काष्ठा pt_regs, r)				\
पूर्ण

#घोषणा REG_OFFSET_END अणु						\
	.name = शून्य,							\
	.offset = 0							\
पूर्ण

अटल स्थिर काष्ठा pt_regs_offset regoffset_table[] = अणु
	REG_OFFSET_NAME(r0, regs[0]),
	REG_OFFSET_NAME(r1, regs[1]),
	REG_OFFSET_NAME(r2, regs[2]),
	REG_OFFSET_NAME(r3, regs[3]),
	REG_OFFSET_NAME(r4, regs[4]),
	REG_OFFSET_NAME(r5, regs[5]),
	REG_OFFSET_NAME(r6, regs[6]),
	REG_OFFSET_NAME(r7, regs[7]),
	REG_OFFSET_NAME(r8, regs[8]),
	REG_OFFSET_NAME(r9, regs[9]),
	REG_OFFSET_NAME(r10, regs[10]),
	REG_OFFSET_NAME(r11, regs[11]),
	REG_OFFSET_NAME(r12, regs[12]),
	REG_OFFSET_NAME(r13, regs[13]),
	REG_OFFSET_NAME(r14, regs[14]),
	REG_OFFSET_NAME(r15, regs[15]),
	REG_OFFSET_NAME(r16, regs[16]),
	REG_OFFSET_NAME(r17, regs[17]),
	REG_OFFSET_NAME(r18, regs[18]),
	REG_OFFSET_NAME(r19, regs[19]),
	REG_OFFSET_NAME(r20, regs[20]),
	REG_OFFSET_NAME(r21, regs[21]),
	REG_OFFSET_NAME(r22, regs[22]),
	REG_OFFSET_NAME(r23, regs[23]),
	REG_OFFSET_NAME(r24, regs[24]),
	REG_OFFSET_NAME(r25, regs[25]),
	REG_OFFSET_NAME(r26, regs[26]),
	REG_OFFSET_NAME(r27, regs[27]),
	REG_OFFSET_NAME(r28, regs[28]),
	REG_OFFSET_NAME(r29, regs[29]),
	REG_OFFSET_NAME(r30, regs[30]),
	REG_OFFSET_NAME(r31, regs[31]),
	REG_OFFSET_NAME(c0_status, cp0_status),
	REG_OFFSET_NAME(hi, hi),
	REG_OFFSET_NAME(lo, lo),
#अगर_घोषित CONFIG_CPU_HAS_SMARTMIPS
	REG_OFFSET_NAME(acx, acx),
#पूर्ण_अगर
	REG_OFFSET_NAME(c0_badvaddr, cp0_badvaddr),
	REG_OFFSET_NAME(c0_cause, cp0_cause),
	REG_OFFSET_NAME(c0_epc, cp0_epc),
#अगर_घोषित CONFIG_CPU_CAVIUM_OCTEON
	REG_OFFSET_NAME(mpl0, mpl[0]),
	REG_OFFSET_NAME(mpl1, mpl[1]),
	REG_OFFSET_NAME(mpl2, mpl[2]),
	REG_OFFSET_NAME(mtp0, mtp[0]),
	REG_OFFSET_NAME(mtp1, mtp[1]),
	REG_OFFSET_NAME(mtp2, mtp[2]),
#पूर्ण_अगर
	REG_OFFSET_END,
पूर्ण;

/**
 * regs_query_रेजिस्टर_offset() - query रेजिस्टर offset from its name
 * @name:       the name of a रेजिस्टर
 *
 * regs_query_रेजिस्टर_offset() वापसs the offset of a रेजिस्टर in काष्ठा
 * pt_regs from its name. If the name is invalid, this वापसs -EINVAL;
 */
पूर्णांक regs_query_रेजिस्टर_offset(स्थिर अक्षर *name)
अणु
        स्थिर काष्ठा pt_regs_offset *roff;
        क्रम (roff = regoffset_table; roff->name != शून्य; roff++)
                अगर (!म_भेद(roff->name, name))
                        वापस roff->offset;
        वापस -EINVAL;
पूर्ण

#अगर defined(CONFIG_32BIT) || defined(CONFIG_MIPS32_O32)

अटल स्थिर काष्ठा user_regset mips_regsets[] = अणु
	[REGSET_GPR] = अणु
		.core_note_type	= NT_PRSTATUS,
		.n		= ELF_NGREG,
		.size		= माप(अचिन्हित पूर्णांक),
		.align		= माप(अचिन्हित पूर्णांक),
		.regset_get		= gpr32_get,
		.set		= gpr32_set,
	पूर्ण,
	[REGSET_DSP] = अणु
		.core_note_type	= NT_MIPS_DSP,
		.n		= NUM_DSP_REGS + 1,
		.size		= माप(u32),
		.align		= माप(u32),
		.regset_get		= dsp32_get,
		.set		= dsp32_set,
		.active		= dsp_active,
	पूर्ण,
#अगर_घोषित CONFIG_MIPS_FP_SUPPORT
	[REGSET_FPR] = अणु
		.core_note_type	= NT_PRFPREG,
		.n		= ELF_NFPREG,
		.size		= माप(elf_fpreg_t),
		.align		= माप(elf_fpreg_t),
		.regset_get		= fpr_get,
		.set		= fpr_set,
	पूर्ण,
	[REGSET_FP_MODE] = अणु
		.core_note_type	= NT_MIPS_FP_MODE,
		.n		= 1,
		.size		= माप(पूर्णांक),
		.align		= माप(पूर्णांक),
		.regset_get		= fp_mode_get,
		.set		= fp_mode_set,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CPU_HAS_MSA
	[REGSET_MSA] = अणु
		.core_note_type	= NT_MIPS_MSA,
		.n		= NUM_FPU_REGS + 1,
		.size		= 16,
		.align		= 16,
		.regset_get		= msa_get,
		.set		= msa_set,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा user_regset_view user_mips_view = अणु
	.name		= "mips",
	.e_machine	= ELF_ARCH,
	.ei_osabi	= ELF_OSABI,
	.regsets	= mips_regsets,
	.n		= ARRAY_SIZE(mips_regsets),
पूर्ण;

#पूर्ण_अगर /* CONFIG_32BIT || CONFIG_MIPS32_O32 */

#अगर_घोषित CONFIG_64BIT

अटल स्थिर काष्ठा user_regset mips64_regsets[] = अणु
	[REGSET_GPR] = अणु
		.core_note_type	= NT_PRSTATUS,
		.n		= ELF_NGREG,
		.size		= माप(अचिन्हित दीर्घ),
		.align		= माप(अचिन्हित दीर्घ),
		.regset_get		= gpr64_get,
		.set		= gpr64_set,
	पूर्ण,
	[REGSET_DSP] = अणु
		.core_note_type	= NT_MIPS_DSP,
		.n		= NUM_DSP_REGS + 1,
		.size		= माप(u64),
		.align		= माप(u64),
		.regset_get		= dsp64_get,
		.set		= dsp64_set,
		.active		= dsp_active,
	पूर्ण,
#अगर_घोषित CONFIG_MIPS_FP_SUPPORT
	[REGSET_FP_MODE] = अणु
		.core_note_type	= NT_MIPS_FP_MODE,
		.n		= 1,
		.size		= माप(पूर्णांक),
		.align		= माप(पूर्णांक),
		.regset_get		= fp_mode_get,
		.set		= fp_mode_set,
	पूर्ण,
	[REGSET_FPR] = अणु
		.core_note_type	= NT_PRFPREG,
		.n		= ELF_NFPREG,
		.size		= माप(elf_fpreg_t),
		.align		= माप(elf_fpreg_t),
		.regset_get		= fpr_get,
		.set		= fpr_set,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CPU_HAS_MSA
	[REGSET_MSA] = अणु
		.core_note_type	= NT_MIPS_MSA,
		.n		= NUM_FPU_REGS + 1,
		.size		= 16,
		.align		= 16,
		.regset_get		= msa_get,
		.set		= msa_set,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा user_regset_view user_mips64_view = अणु
	.name		= "mips64",
	.e_machine	= ELF_ARCH,
	.ei_osabi	= ELF_OSABI,
	.regsets	= mips64_regsets,
	.n		= ARRAY_SIZE(mips64_regsets),
पूर्ण;

#अगर_घोषित CONFIG_MIPS32_N32

अटल स्थिर काष्ठा user_regset_view user_mipsn32_view = अणु
	.name		= "mipsn32",
	.e_flags	= EF_MIPS_ABI2,
	.e_machine	= ELF_ARCH,
	.ei_osabi	= ELF_OSABI,
	.regsets	= mips64_regsets,
	.n		= ARRAY_SIZE(mips64_regsets),
पूर्ण;

#पूर्ण_अगर /* CONFIG_MIPS32_N32 */

#पूर्ण_अगर /* CONFIG_64BIT */

स्थिर काष्ठा user_regset_view *task_user_regset_view(काष्ठा task_काष्ठा *task)
अणु
#अगर_घोषित CONFIG_32BIT
	वापस &user_mips_view;
#अन्यथा
#अगर_घोषित CONFIG_MIPS32_O32
	अगर (test_tsk_thपढ़ो_flag(task, TIF_32BIT_REGS))
		वापस &user_mips_view;
#पूर्ण_अगर
#अगर_घोषित CONFIG_MIPS32_N32
	अगर (test_tsk_thपढ़ो_flag(task, TIF_32BIT_ADDR))
		वापस &user_mipsn32_view;
#पूर्ण_अगर
	वापस &user_mips64_view;
#पूर्ण_अगर
पूर्ण

दीर्घ arch_ptrace(काष्ठा task_काष्ठा *child, दीर्घ request,
		 अचिन्हित दीर्घ addr, अचिन्हित दीर्घ data)
अणु
	पूर्णांक ret;
	व्योम __user *addrp = (व्योम __user *) addr;
	व्योम __user *datavp = (व्योम __user *) data;
	अचिन्हित दीर्घ __user *datalp = (व्योम __user *) data;

	चयन (request) अणु
	/* when I and D space are separate, these will need to be fixed. */
	हाल PTRACE_PEEKTEXT: /* पढ़ो word at location addr. */
	हाल PTRACE_PEEKDATA:
		ret = generic_ptrace_peekdata(child, addr, data);
		अवरोध;

	/* Read the word at location addr in the USER area. */
	हाल PTRACE_PEEKUSR: अणु
		काष्ठा pt_regs *regs;
		अचिन्हित दीर्घ पंचांगp = 0;

		regs = task_pt_regs(child);
		ret = 0;  /* Default वापस value. */

		चयन (addr) अणु
		हाल 0 ... 31:
			पंचांगp = regs->regs[addr];
			अवरोध;
#अगर_घोषित CONFIG_MIPS_FP_SUPPORT
		हाल FPR_BASE ... FPR_BASE + 31: अणु
			जोड़ fpureg *fregs;

			अगर (!tsk_used_math(child)) अणु
				/* FP not yet used */
				पंचांगp = -1;
				अवरोध;
			पूर्ण
			fregs = get_fpu_regs(child);

#अगर_घोषित CONFIG_32BIT
			अगर (test_tsk_thपढ़ो_flag(child, TIF_32BIT_FPREGS)) अणु
				/*
				 * The odd रेजिस्टरs are actually the high
				 * order bits of the values stored in the even
				 * रेजिस्टरs.
				 */
				पंचांगp = get_fpr32(&fregs[(addr & ~1) - FPR_BASE],
						addr & 1);
				अवरोध;
			पूर्ण
#पूर्ण_अगर
			पंचांगp = get_fpr64(&fregs[addr - FPR_BASE], 0);
			अवरोध;
		पूर्ण
		हाल FPC_CSR:
			पंचांगp = child->thपढ़ो.fpu.fcr31;
			अवरोध;
		हाल FPC_EIR:
			/* implementation / version रेजिस्टर */
			पंचांगp = boot_cpu_data.fpu_id;
			अवरोध;
#पूर्ण_अगर
		हाल PC:
			पंचांगp = regs->cp0_epc;
			अवरोध;
		हाल CAUSE:
			पंचांगp = regs->cp0_cause;
			अवरोध;
		हाल BADVADDR:
			पंचांगp = regs->cp0_badvaddr;
			अवरोध;
		हाल MMHI:
			पंचांगp = regs->hi;
			अवरोध;
		हाल MMLO:
			पंचांगp = regs->lo;
			अवरोध;
#अगर_घोषित CONFIG_CPU_HAS_SMARTMIPS
		हाल ACX:
			पंचांगp = regs->acx;
			अवरोध;
#पूर्ण_अगर
		हाल DSP_BASE ... DSP_BASE + 5: अणु
			dspreg_t *dregs;

			अगर (!cpu_has_dsp) अणु
				पंचांगp = 0;
				ret = -EIO;
				जाओ out;
			पूर्ण
			dregs = __get_dsp_regs(child);
			पंचांगp = dregs[addr - DSP_BASE];
			अवरोध;
		पूर्ण
		हाल DSP_CONTROL:
			अगर (!cpu_has_dsp) अणु
				पंचांगp = 0;
				ret = -EIO;
				जाओ out;
			पूर्ण
			पंचांगp = child->thपढ़ो.dsp.dspcontrol;
			अवरोध;
		शेष:
			पंचांगp = 0;
			ret = -EIO;
			जाओ out;
		पूर्ण
		ret = put_user(पंचांगp, datalp);
		अवरोध;
	पूर्ण

	/* when I and D space are separate, this will have to be fixed. */
	हाल PTRACE_POKETEXT: /* ग_लिखो the word at location addr. */
	हाल PTRACE_POKEDATA:
		ret = generic_ptrace_pokedata(child, addr, data);
		अवरोध;

	हाल PTRACE_POKEUSR: अणु
		काष्ठा pt_regs *regs;
		ret = 0;
		regs = task_pt_regs(child);

		चयन (addr) अणु
		हाल 0 ... 31:
			regs->regs[addr] = data;
			/* System call number may have been changed */
			अगर (addr == 2)
				mips_syscall_update_nr(child, regs);
			अन्यथा अगर (addr == 4 &&
				 mips_syscall_is_indirect(child, regs))
				mips_syscall_update_nr(child, regs);
			अवरोध;
#अगर_घोषित CONFIG_MIPS_FP_SUPPORT
		हाल FPR_BASE ... FPR_BASE + 31: अणु
			जोड़ fpureg *fregs = get_fpu_regs(child);

			init_fp_ctx(child);
#अगर_घोषित CONFIG_32BIT
			अगर (test_tsk_thपढ़ो_flag(child, TIF_32BIT_FPREGS)) अणु
				/*
				 * The odd रेजिस्टरs are actually the high
				 * order bits of the values stored in the even
				 * रेजिस्टरs.
				 */
				set_fpr32(&fregs[(addr & ~1) - FPR_BASE],
					  addr & 1, data);
				अवरोध;
			पूर्ण
#पूर्ण_अगर
			set_fpr64(&fregs[addr - FPR_BASE], 0, data);
			अवरोध;
		पूर्ण
		हाल FPC_CSR:
			init_fp_ctx(child);
			ptrace_setfcr31(child, data);
			अवरोध;
#पूर्ण_अगर
		हाल PC:
			regs->cp0_epc = data;
			अवरोध;
		हाल MMHI:
			regs->hi = data;
			अवरोध;
		हाल MMLO:
			regs->lo = data;
			अवरोध;
#अगर_घोषित CONFIG_CPU_HAS_SMARTMIPS
		हाल ACX:
			regs->acx = data;
			अवरोध;
#पूर्ण_अगर
		हाल DSP_BASE ... DSP_BASE + 5: अणु
			dspreg_t *dregs;

			अगर (!cpu_has_dsp) अणु
				ret = -EIO;
				अवरोध;
			पूर्ण

			dregs = __get_dsp_regs(child);
			dregs[addr - DSP_BASE] = data;
			अवरोध;
		पूर्ण
		हाल DSP_CONTROL:
			अगर (!cpu_has_dsp) अणु
				ret = -EIO;
				अवरोध;
			पूर्ण
			child->thपढ़ो.dsp.dspcontrol = data;
			अवरोध;
		शेष:
			/* The rest are not allowed. */
			ret = -EIO;
			अवरोध;
		पूर्ण
		अवरोध;
		पूर्ण

	हाल PTRACE_GETREGS:
		ret = ptrace_getregs(child, datavp);
		अवरोध;

	हाल PTRACE_SETREGS:
		ret = ptrace_setregs(child, datavp);
		अवरोध;

#अगर_घोषित CONFIG_MIPS_FP_SUPPORT
	हाल PTRACE_GETFPREGS:
		ret = ptrace_getfpregs(child, datavp);
		अवरोध;

	हाल PTRACE_SETFPREGS:
		ret = ptrace_setfpregs(child, datavp);
		अवरोध;
#पूर्ण_अगर
	हाल PTRACE_GET_THREAD_AREA:
		ret = put_user(task_thपढ़ो_info(child)->tp_value, datalp);
		अवरोध;

	हाल PTRACE_GET_WATCH_REGS:
		ret = ptrace_get_watch_regs(child, addrp);
		अवरोध;

	हाल PTRACE_SET_WATCH_REGS:
		ret = ptrace_set_watch_regs(child, addrp);
		अवरोध;

	शेष:
		ret = ptrace_request(child, request, addr, data);
		अवरोध;
	पूर्ण
 out:
	वापस ret;
पूर्ण

/*
 * Notअगरication of प्रणाली call entry/निकास
 * - triggered by current->work.syscall_trace
 */
यंत्रlinkage दीर्घ syscall_trace_enter(काष्ठा pt_regs *regs, दीर्घ syscall)
अणु
	user_निकास();

	current_thपढ़ो_info()->syscall = syscall;

	अगर (test_thपढ़ो_flag(TIF_SYSCALL_TRACE)) अणु
		अगर (tracehook_report_syscall_entry(regs))
			वापस -1;
		syscall = current_thपढ़ो_info()->syscall;
	पूर्ण

#अगर_घोषित CONFIG_SECCOMP
	अगर (unlikely(test_thपढ़ो_flag(TIF_SECCOMP))) अणु
		पूर्णांक ret, i;
		काष्ठा seccomp_data sd;
		अचिन्हित दीर्घ args[6];

		sd.nr = syscall;
		sd.arch = syscall_get_arch(current);
		syscall_get_arguments(current, regs, args);
		क्रम (i = 0; i < 6; i++)
			sd.args[i] = args[i];
		sd.inकाष्ठाion_poपूर्णांकer = KSTK_EIP(current);

		ret = __secure_computing(&sd);
		अगर (ret == -1)
			वापस ret;
		syscall = current_thपढ़ो_info()->syscall;
	पूर्ण
#पूर्ण_अगर

	अगर (unlikely(test_thपढ़ो_flag(TIF_SYSCALL_TRACEPOINT)))
		trace_sys_enter(regs, regs->regs[2]);

	audit_syscall_entry(syscall, regs->regs[4], regs->regs[5],
			    regs->regs[6], regs->regs[7]);

	/*
	 * Negative syscall numbers are mistaken क्रम rejected syscalls, but
	 * won't have had the वापस value set appropriately, so we करो so now.
	 */
	अगर (syscall < 0)
		syscall_set_वापस_value(current, regs, -ENOSYS, 0);
	वापस syscall;
पूर्ण

/*
 * Notअगरication of प्रणाली call entry/निकास
 * - triggered by current->work.syscall_trace
 */
यंत्रlinkage व्योम syscall_trace_leave(काष्ठा pt_regs *regs)
अणु
        /*
	 * We may come here right after calling schedule_user()
	 * or करो_notअगरy_resume(), in which हाल we can be in RCU
	 * user mode.
	 */
	user_निकास();

	audit_syscall_निकास(regs);

	अगर (unlikely(test_thपढ़ो_flag(TIF_SYSCALL_TRACEPOINT)))
		trace_sys_निकास(regs, regs_वापस_value(regs));

	अगर (test_thपढ़ो_flag(TIF_SYSCALL_TRACE))
		tracehook_report_syscall_निकास(regs, 0);

	user_enter();
पूर्ण
