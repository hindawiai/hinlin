<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/export.h>
#समावेश <linux/preempt.h>
#समावेश <linux/smp.h>
#समावेश <linux/completion.h>
#समावेश <यंत्र/msr.h>

अटल व्योम __rdmsr_on_cpu(व्योम *info)
अणु
	काष्ठा msr_info *rv = info;
	काष्ठा msr *reg;
	पूर्णांक this_cpu = raw_smp_processor_id();

	अगर (rv->msrs)
		reg = per_cpu_ptr(rv->msrs, this_cpu);
	अन्यथा
		reg = &rv->reg;

	rdmsr(rv->msr_no, reg->l, reg->h);
पूर्ण

अटल व्योम __wrmsr_on_cpu(व्योम *info)
अणु
	काष्ठा msr_info *rv = info;
	काष्ठा msr *reg;
	पूर्णांक this_cpu = raw_smp_processor_id();

	अगर (rv->msrs)
		reg = per_cpu_ptr(rv->msrs, this_cpu);
	अन्यथा
		reg = &rv->reg;

	wrmsr(rv->msr_no, reg->l, reg->h);
पूर्ण

पूर्णांक rdmsr_on_cpu(अचिन्हित पूर्णांक cpu, u32 msr_no, u32 *l, u32 *h)
अणु
	पूर्णांक err;
	काष्ठा msr_info rv;

	स_रखो(&rv, 0, माप(rv));

	rv.msr_no = msr_no;
	err = smp_call_function_single(cpu, __rdmsr_on_cpu, &rv, 1);
	*l = rv.reg.l;
	*h = rv.reg.h;

	वापस err;
पूर्ण
EXPORT_SYMBOL(rdmsr_on_cpu);

पूर्णांक rdmsrl_on_cpu(अचिन्हित पूर्णांक cpu, u32 msr_no, u64 *q)
अणु
	पूर्णांक err;
	काष्ठा msr_info rv;

	स_रखो(&rv, 0, माप(rv));

	rv.msr_no = msr_no;
	err = smp_call_function_single(cpu, __rdmsr_on_cpu, &rv, 1);
	*q = rv.reg.q;

	वापस err;
पूर्ण
EXPORT_SYMBOL(rdmsrl_on_cpu);

पूर्णांक wrmsr_on_cpu(अचिन्हित पूर्णांक cpu, u32 msr_no, u32 l, u32 h)
अणु
	पूर्णांक err;
	काष्ठा msr_info rv;

	स_रखो(&rv, 0, माप(rv));

	rv.msr_no = msr_no;
	rv.reg.l = l;
	rv.reg.h = h;
	err = smp_call_function_single(cpu, __wrmsr_on_cpu, &rv, 1);

	वापस err;
पूर्ण
EXPORT_SYMBOL(wrmsr_on_cpu);

पूर्णांक wrmsrl_on_cpu(अचिन्हित पूर्णांक cpu, u32 msr_no, u64 q)
अणु
	पूर्णांक err;
	काष्ठा msr_info rv;

	स_रखो(&rv, 0, माप(rv));

	rv.msr_no = msr_no;
	rv.reg.q = q;

	err = smp_call_function_single(cpu, __wrmsr_on_cpu, &rv, 1);

	वापस err;
पूर्ण
EXPORT_SYMBOL(wrmsrl_on_cpu);

अटल व्योम __rwmsr_on_cpus(स्थिर काष्ठा cpumask *mask, u32 msr_no,
			    काष्ठा msr *msrs,
			    व्योम (*msr_func) (व्योम *info))
अणु
	काष्ठा msr_info rv;
	पूर्णांक this_cpu;

	स_रखो(&rv, 0, माप(rv));

	rv.msrs	  = msrs;
	rv.msr_no = msr_no;

	this_cpu = get_cpu();

	अगर (cpumask_test_cpu(this_cpu, mask))
		msr_func(&rv);

	smp_call_function_many(mask, msr_func, &rv, 1);
	put_cpu();
पूर्ण

/* rdmsr on a bunch of CPUs
 *
 * @mask:       which CPUs
 * @msr_no:     which MSR
 * @msrs:       array of MSR values
 *
 */
व्योम rdmsr_on_cpus(स्थिर काष्ठा cpumask *mask, u32 msr_no, काष्ठा msr *msrs)
अणु
	__rwmsr_on_cpus(mask, msr_no, msrs, __rdmsr_on_cpu);
पूर्ण
EXPORT_SYMBOL(rdmsr_on_cpus);

/*
 * wrmsr on a bunch of CPUs
 *
 * @mask:       which CPUs
 * @msr_no:     which MSR
 * @msrs:       array of MSR values
 *
 */
व्योम wrmsr_on_cpus(स्थिर काष्ठा cpumask *mask, u32 msr_no, काष्ठा msr *msrs)
अणु
	__rwmsr_on_cpus(mask, msr_no, msrs, __wrmsr_on_cpu);
पूर्ण
EXPORT_SYMBOL(wrmsr_on_cpus);

काष्ठा msr_info_completion अणु
	काष्ठा msr_info		msr;
	काष्ठा completion	करोne;
पूर्ण;

/* These "safe" variants are slower and should be used when the target MSR
   may not actually exist. */
अटल व्योम __rdmsr_safe_on_cpu(व्योम *info)
अणु
	काष्ठा msr_info_completion *rv = info;

	rv->msr.err = rdmsr_safe(rv->msr.msr_no, &rv->msr.reg.l, &rv->msr.reg.h);
	complete(&rv->करोne);
पूर्ण

अटल व्योम __wrmsr_safe_on_cpu(व्योम *info)
अणु
	काष्ठा msr_info *rv = info;

	rv->err = wrmsr_safe(rv->msr_no, rv->reg.l, rv->reg.h);
पूर्ण

पूर्णांक rdmsr_safe_on_cpu(अचिन्हित पूर्णांक cpu, u32 msr_no, u32 *l, u32 *h)
अणु
	काष्ठा msr_info_completion rv;
	call_single_data_t csd;
	पूर्णांक err;

	INIT_CSD(&csd, __rdmsr_safe_on_cpu, &rv);

	स_रखो(&rv, 0, माप(rv));
	init_completion(&rv.करोne);
	rv.msr.msr_no = msr_no;

	err = smp_call_function_single_async(cpu, &csd);
	अगर (!err) अणु
		रुको_क्रम_completion(&rv.करोne);
		err = rv.msr.err;
	पूर्ण
	*l = rv.msr.reg.l;
	*h = rv.msr.reg.h;

	वापस err;
पूर्ण
EXPORT_SYMBOL(rdmsr_safe_on_cpu);

पूर्णांक wrmsr_safe_on_cpu(अचिन्हित पूर्णांक cpu, u32 msr_no, u32 l, u32 h)
अणु
	पूर्णांक err;
	काष्ठा msr_info rv;

	स_रखो(&rv, 0, माप(rv));

	rv.msr_no = msr_no;
	rv.reg.l = l;
	rv.reg.h = h;
	err = smp_call_function_single(cpu, __wrmsr_safe_on_cpu, &rv, 1);

	वापस err ? err : rv.err;
पूर्ण
EXPORT_SYMBOL(wrmsr_safe_on_cpu);

पूर्णांक wrmsrl_safe_on_cpu(अचिन्हित पूर्णांक cpu, u32 msr_no, u64 q)
अणु
	पूर्णांक err;
	काष्ठा msr_info rv;

	स_रखो(&rv, 0, माप(rv));

	rv.msr_no = msr_no;
	rv.reg.q = q;

	err = smp_call_function_single(cpu, __wrmsr_safe_on_cpu, &rv, 1);

	वापस err ? err : rv.err;
पूर्ण
EXPORT_SYMBOL(wrmsrl_safe_on_cpu);

पूर्णांक rdmsrl_safe_on_cpu(अचिन्हित पूर्णांक cpu, u32 msr_no, u64 *q)
अणु
	u32 low, high;
	पूर्णांक err;

	err = rdmsr_safe_on_cpu(cpu, msr_no, &low, &high);
	*q = (u64)high << 32 | low;

	वापस err;
पूर्ण
EXPORT_SYMBOL(rdmsrl_safe_on_cpu);

/*
 * These variants are signअगरicantly slower, but allows control over
 * the entire 32-bit GPR set.
 */
अटल व्योम __rdmsr_safe_regs_on_cpu(व्योम *info)
अणु
	काष्ठा msr_regs_info *rv = info;

	rv->err = rdmsr_safe_regs(rv->regs);
पूर्ण

अटल व्योम __wrmsr_safe_regs_on_cpu(व्योम *info)
अणु
	काष्ठा msr_regs_info *rv = info;

	rv->err = wrmsr_safe_regs(rv->regs);
पूर्ण

पूर्णांक rdmsr_safe_regs_on_cpu(अचिन्हित पूर्णांक cpu, u32 regs[8])
अणु
	पूर्णांक err;
	काष्ठा msr_regs_info rv;

	rv.regs   = regs;
	rv.err    = -EIO;
	err = smp_call_function_single(cpu, __rdmsr_safe_regs_on_cpu, &rv, 1);

	वापस err ? err : rv.err;
पूर्ण
EXPORT_SYMBOL(rdmsr_safe_regs_on_cpu);

पूर्णांक wrmsr_safe_regs_on_cpu(अचिन्हित पूर्णांक cpu, u32 regs[8])
अणु
	पूर्णांक err;
	काष्ठा msr_regs_info rv;

	rv.regs = regs;
	rv.err  = -EIO;
	err = smp_call_function_single(cpu, __wrmsr_safe_regs_on_cpu, &rv, 1);

	वापस err ? err : rv.err;
पूर्ण
EXPORT_SYMBOL(wrmsr_safe_regs_on_cpu);
