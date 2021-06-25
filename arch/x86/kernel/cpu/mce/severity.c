<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MCE grading rules.
 * Copyright 2008, 2009 Intel Corporation.
 *
 * Author: Andi Kleen
 */
#समावेश <linux/kernel.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/init.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/mce.h>
#समावेश <यंत्र/पूर्णांकel-family.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/insn.h>
#समावेश <यंत्र/insn-eval.h>

#समावेश "internal.h"

/*
 * Grade an mce by severity. In general the most severe ones are processed
 * first. Since there are quite a lot of combinations test the bits in a
 * table-driven way. The rules are simply processed in order, first
 * match wins.
 *
 * Note this is only used क्रम machine check exceptions, the corrected
 * errors use much simpler rules. The exceptions still check क्रम the corrected
 * errors, but only to leave them alone क्रम the CMCI handler (except क्रम
 * panic situations)
 */

क्रमागत context अणु IN_KERNEL = 1, IN_USER = 2, IN_KERNEL_RECOV = 3 पूर्ण;
क्रमागत ser अणु SER_REQUIRED = 1, NO_SER = 2 पूर्ण;
क्रमागत exception अणु EXCP_CONTEXT = 1, NO_EXCP = 2 पूर्ण;

अटल काष्ठा severity अणु
	u64 mask;
	u64 result;
	अचिन्हित अक्षर sev;
	अचिन्हित अक्षर mcgmask;
	अचिन्हित अक्षर mcgres;
	अचिन्हित अक्षर ser;
	अचिन्हित अक्षर context;
	अचिन्हित अक्षर excp;
	अचिन्हित अक्षर covered;
	अचिन्हित अक्षर cpu_model;
	अचिन्हित अक्षर cpu_minstepping;
	अचिन्हित अक्षर bank_lo, bank_hi;
	अक्षर *msg;
पूर्ण severities[] = अणु
#घोषणा MCESEV(s, m, c...) अणु .sev = MCE_ ## s ## _SEVERITY, .msg = m, ## c पूर्ण
#घोषणा BANK_RANGE(l, h) .bank_lo = l, .bank_hi = h
#घोषणा MODEL_STEPPING(m, s) .cpu_model = m, .cpu_minstepping = s
#घोषणा  KERNEL		.context = IN_KERNEL
#घोषणा  USER		.context = IN_USER
#घोषणा  KERNEL_RECOV	.context = IN_KERNEL_RECOV
#घोषणा  SER		.ser = SER_REQUIRED
#घोषणा  NOSER		.ser = NO_SER
#घोषणा  EXCP		.excp = EXCP_CONTEXT
#घोषणा  NOEXCP		.excp = NO_EXCP
#घोषणा  BITCLR(x)	.mask = x, .result = 0
#घोषणा  BITSET(x)	.mask = x, .result = x
#घोषणा  MCGMASK(x, y)	.mcgmask = x, .mcgres = y
#घोषणा  MASK(x, y)	.mask = x, .result = y
#घोषणा MCI_UC_S (MCI_STATUS_UC|MCI_STATUS_S)
#घोषणा MCI_UC_AR (MCI_STATUS_UC|MCI_STATUS_AR)
#घोषणा MCI_UC_SAR (MCI_STATUS_UC|MCI_STATUS_S|MCI_STATUS_AR)
#घोषणा	MCI_ADDR (MCI_STATUS_ADDRV|MCI_STATUS_MISCV)

	MCESEV(
		NO, "Invalid",
		BITCLR(MCI_STATUS_VAL)
		),
	MCESEV(
		NO, "Not enabled",
		EXCP, BITCLR(MCI_STATUS_EN)
		),
	MCESEV(
		PANIC, "Processor context corrupt",
		BITSET(MCI_STATUS_PCC)
		),
	/* When MCIP is not set something is very confused */
	MCESEV(
		PANIC, "MCIP not set in MCA handler",
		EXCP, MCGMASK(MCG_STATUS_MCIP, 0)
		),
	/* Neither वापस not error IP -- no chance to recover -> PANIC */
	MCESEV(
		PANIC, "Neither restart nor error IP",
		EXCP, MCGMASK(MCG_STATUS_RIPV|MCG_STATUS_EIPV, 0)
		),
	MCESEV(
		PANIC, "In kernel and no restart IP",
		EXCP, KERNEL, MCGMASK(MCG_STATUS_RIPV, 0)
		),
	MCESEV(
		PANIC, "In kernel and no restart IP",
		EXCP, KERNEL_RECOV, MCGMASK(MCG_STATUS_RIPV, 0)
		),
	MCESEV(
		KEEP, "Corrected error",
		NOSER, BITCLR(MCI_STATUS_UC)
		),
	/*
	 * known AO MCACODs reported via MCE or CMC:
	 *
	 * SRAO could be संकेतed either via a machine check exception or
	 * CMCI with the corresponding bit S 1 or 0. So we करोn't need to
	 * check bit S क्रम SRAO.
	 */
	MCESEV(
		AO, "Action optional: memory scrubbing error",
		SER, MASK(MCI_UC_AR|MCACOD_SCRUBMSK, MCI_STATUS_UC|MCACOD_SCRUB)
		),
	MCESEV(
		AO, "Action optional: last level cache writeback error",
		SER, MASK(MCI_UC_AR|MCACOD, MCI_STATUS_UC|MCACOD_L3WB)
		),
	/*
	 * Quirk क्रम Skylake/Cascade Lake. Patrol scrubber may be configured
	 * to report uncorrected errors using CMCI with a special signature.
	 * UC=0, MSCOD=0x0010, MCACOD=binary(000X 0000 1100 XXXX) reported
	 * in one of the memory controller banks.
	 * Set severity to "AO" क्रम same action as normal patrol scrub error.
	 */
	MCESEV(
		AO, "Uncorrected Patrol Scrub Error",
		SER, MASK(MCI_STATUS_UC|MCI_ADDR|0xffffeff0, MCI_ADDR|0x001000c0),
		MODEL_STEPPING(INTEL_FAM6_SKYLAKE_X, 4), BANK_RANGE(13, 18)
	),

	/* ignore OVER क्रम UCNA */
	MCESEV(
		UCNA, "Uncorrected no action required",
		SER, MASK(MCI_UC_SAR, MCI_STATUS_UC)
		),
	MCESEV(
		PANIC, "Illegal combination (UCNA with AR=1)",
		SER,
		MASK(MCI_STATUS_OVER|MCI_UC_SAR, MCI_STATUS_UC|MCI_STATUS_AR)
		),
	MCESEV(
		KEEP, "Non signaled machine check",
		SER, BITCLR(MCI_STATUS_S)
		),

	MCESEV(
		PANIC, "Action required with lost events",
		SER, BITSET(MCI_STATUS_OVER|MCI_UC_SAR)
		),

	/* known AR MCACODs: */
#अगर_घोषित	CONFIG_MEMORY_FAILURE
	MCESEV(
		KEEP, "Action required but unaffected thread is continuable",
		SER, MASK(MCI_STATUS_OVER|MCI_UC_SAR|MCI_ADDR, MCI_UC_SAR|MCI_ADDR),
		MCGMASK(MCG_STATUS_RIPV|MCG_STATUS_EIPV, MCG_STATUS_RIPV)
		),
	MCESEV(
		AR, "Action required: data load in error recoverable area of kernel",
		SER, MASK(MCI_STATUS_OVER|MCI_UC_SAR|MCI_ADDR|MCACOD, MCI_UC_SAR|MCI_ADDR|MCACOD_DATA),
		KERNEL_RECOV
		),
	MCESEV(
		AR, "Action required: data load error in a user process",
		SER, MASK(MCI_STATUS_OVER|MCI_UC_SAR|MCI_ADDR|MCACOD, MCI_UC_SAR|MCI_ADDR|MCACOD_DATA),
		USER
		),
	MCESEV(
		AR, "Action required: instruction fetch error in a user process",
		SER, MASK(MCI_STATUS_OVER|MCI_UC_SAR|MCI_ADDR|MCACOD, MCI_UC_SAR|MCI_ADDR|MCACOD_INSTR),
		USER
		),
	MCESEV(
		PANIC, "Data load in unrecoverable area of kernel",
		SER, MASK(MCI_STATUS_OVER|MCI_UC_SAR|MCI_ADDR|MCACOD, MCI_UC_SAR|MCI_ADDR|MCACOD_DATA),
		KERNEL
		),
	MCESEV(
		PANIC, "Instruction fetch error in kernel",
		SER, MASK(MCI_STATUS_OVER|MCI_UC_SAR|MCI_ADDR|MCACOD, MCI_UC_SAR|MCI_ADDR|MCACOD_INSTR),
		KERNEL
		),
#पूर्ण_अगर
	MCESEV(
		PANIC, "Action required: unknown MCACOD",
		SER, MASK(MCI_STATUS_OVER|MCI_UC_SAR, MCI_UC_SAR)
		),

	MCESEV(
		SOME, "Action optional: unknown MCACOD",
		SER, MASK(MCI_STATUS_OVER|MCI_UC_SAR, MCI_UC_S)
		),
	MCESEV(
		SOME, "Action optional with lost events",
		SER, MASK(MCI_STATUS_OVER|MCI_UC_SAR, MCI_STATUS_OVER|MCI_UC_S)
		),

	MCESEV(
		PANIC, "Overflowed uncorrected",
		BITSET(MCI_STATUS_OVER|MCI_STATUS_UC)
		),
	MCESEV(
		UC, "Uncorrected",
		BITSET(MCI_STATUS_UC)
		),
	MCESEV(
		SOME, "No match",
		BITSET(0)
		)	/* always matches. keep at end */
पूर्ण;

#घोषणा mc_recoverable(mcg) (((mcg) & (MCG_STATUS_RIPV|MCG_STATUS_EIPV)) == \
				(MCG_STATUS_RIPV|MCG_STATUS_EIPV))

अटल bool is_copy_from_user(काष्ठा pt_regs *regs)
अणु
	u8 insn_buf[MAX_INSN_SIZE];
	अचिन्हित दीर्घ addr;
	काष्ठा insn insn;
	पूर्णांक ret;

	अगर (copy_from_kernel_nofault(insn_buf, (व्योम *)regs->ip, MAX_INSN_SIZE))
		वापस false;

	ret = insn_decode_kernel(&insn, insn_buf);
	अगर (ret < 0)
		वापस false;

	चयन (insn.opcode.value) अणु
	/* MOV mem,reg */
	हाल 0x8A: हाल 0x8B:
	/* MOVZ mem,reg */
	हाल 0xB60F: हाल 0xB70F:
		addr = (अचिन्हित दीर्घ)insn_get_addr_ref(&insn, regs);
		अवरोध;
	/* REP MOVS */
	हाल 0xA4: हाल 0xA5:
		addr = regs->si;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	अगर (fault_in_kernel_space(addr))
		वापस false;

	current->mce_vaddr = (व्योम __user *)addr;

	वापस true;
पूर्ण

/*
 * If mcgstatus indicated that ip/cs on the stack were
 * no good, then "m->cs" will be zero and we will have
 * to assume the worst हाल (IN_KERNEL) as we actually
 * have no idea what we were executing when the machine
 * check hit.
 * If we करो have a good "m->cs" (or a faked one in the
 * हाल we were executing in VM86 mode) we can use it to
 * distinguish an exception taken in user from from one
 * taken in the kernel.
 */
अटल पूर्णांक error_context(काष्ठा mce *m, काष्ठा pt_regs *regs)
अणु
	क्रमागत handler_type t;

	अगर ((m->cs & 3) == 3)
		वापस IN_USER;
	अगर (!mc_recoverable(m->mcgstatus))
		वापस IN_KERNEL;

	t = ex_get_fault_handler_type(m->ip);
	अगर (t == EX_HANDLER_FAULT) अणु
		m->kflags |= MCE_IN_KERNEL_RECOV;
		वापस IN_KERNEL_RECOV;
	पूर्ण
	अगर (t == EX_HANDLER_UACCESS && regs && is_copy_from_user(regs)) अणु
		m->kflags |= MCE_IN_KERNEL_RECOV;
		m->kflags |= MCE_IN_KERNEL_COPYIN;
		वापस IN_KERNEL_RECOV;
	पूर्ण

	वापस IN_KERNEL;
पूर्ण

अटल पूर्णांक mce_severity_amd_smca(काष्ठा mce *m, क्रमागत context err_ctx)
अणु
	u32 addr = MSR_AMD64_SMCA_MCx_CONFIG(m->bank);
	u32 low, high;

	/*
	 * We need to look at the following bits:
	 * - "succor" bit (data poisoning support), and
	 * - TCC bit (Task Context Corrupt)
	 * in MCi_STATUS to determine error severity.
	 */
	अगर (!mce_flags.succor)
		वापस MCE_PANIC_SEVERITY;

	अगर (rdmsr_safe(addr, &low, &high))
		वापस MCE_PANIC_SEVERITY;

	/* TCC (Task context corrupt). If set and अगर IN_KERNEL, panic. */
	अगर ((low & MCI_CONFIG_MCAX) &&
	    (m->status & MCI_STATUS_TCC) &&
	    (err_ctx == IN_KERNEL))
		वापस MCE_PANIC_SEVERITY;

	 /* ...otherwise invoke hwpoison handler. */
	वापस MCE_AR_SEVERITY;
पूर्ण

/*
 * See AMD Error Scope Hierarchy table in a newer BKDG. For example
 * 49125_15h_Models_30h-3Fh_BKDG.pdf, section "RAS Features"
 */
अटल पूर्णांक mce_severity_amd(काष्ठा mce *m, काष्ठा pt_regs *regs, पूर्णांक tolerant,
			    अक्षर **msg, bool is_excp)
अणु
	क्रमागत context ctx = error_context(m, regs);

	/* Processor Context Corrupt, no need to fumble too much, die! */
	अगर (m->status & MCI_STATUS_PCC)
		वापस MCE_PANIC_SEVERITY;

	अगर (m->status & MCI_STATUS_UC) अणु

		अगर (ctx == IN_KERNEL)
			वापस MCE_PANIC_SEVERITY;

		/*
		 * On older प्रणालीs where overflow_recov flag is not present, we
		 * should simply panic अगर an error overflow occurs. If
		 * overflow_recov flag is present and set, then software can try
		 * to at least समाप्त process to proदीर्घ प्रणाली operation.
		 */
		अगर (mce_flags.overflow_recov) अणु
			अगर (mce_flags.smca)
				वापस mce_severity_amd_smca(m, ctx);

			/* समाप्त current process */
			वापस MCE_AR_SEVERITY;
		पूर्ण अन्यथा अणु
			/* at least one error was not logged */
			अगर (m->status & MCI_STATUS_OVER)
				वापस MCE_PANIC_SEVERITY;
		पूर्ण

		/*
		 * For any other हाल, वापस MCE_UC_SEVERITY so that we log the
		 * error and निकास #MC handler.
		 */
		वापस MCE_UC_SEVERITY;
	पूर्ण

	/*
	 * deferred error: poll handler catches these and adds to mce_ring so
	 * memory-failure can take recovery actions.
	 */
	अगर (m->status & MCI_STATUS_DEFERRED)
		वापस MCE_DEFERRED_SEVERITY;

	/*
	 * corrected error: poll handler catches these and passes responsibility
	 * of decoding the error to EDAC
	 */
	वापस MCE_KEEP_SEVERITY;
पूर्ण

अटल पूर्णांक mce_severity_पूर्णांकel(काष्ठा mce *m, काष्ठा pt_regs *regs,
			      पूर्णांक tolerant, अक्षर **msg, bool is_excp)
अणु
	क्रमागत exception excp = (is_excp ? EXCP_CONTEXT : NO_EXCP);
	क्रमागत context ctx = error_context(m, regs);
	काष्ठा severity *s;

	क्रम (s = severities;; s++) अणु
		अगर ((m->status & s->mask) != s->result)
			जारी;
		अगर ((m->mcgstatus & s->mcgmask) != s->mcgres)
			जारी;
		अगर (s->ser == SER_REQUIRED && !mca_cfg.ser)
			जारी;
		अगर (s->ser == NO_SER && mca_cfg.ser)
			जारी;
		अगर (s->context && ctx != s->context)
			जारी;
		अगर (s->excp && excp != s->excp)
			जारी;
		अगर (s->cpu_model && boot_cpu_data.x86_model != s->cpu_model)
			जारी;
		अगर (s->cpu_minstepping && boot_cpu_data.x86_stepping < s->cpu_minstepping)
			जारी;
		अगर (s->bank_lo && (m->bank < s->bank_lo || m->bank > s->bank_hi))
			जारी;
		अगर (msg)
			*msg = s->msg;
		s->covered = 1;
		अगर (s->sev >= MCE_UC_SEVERITY && ctx == IN_KERNEL) अणु
			अगर (tolerant < 1)
				वापस MCE_PANIC_SEVERITY;
		पूर्ण
		वापस s->sev;
	पूर्ण
पूर्ण

/* Default to mce_severity_पूर्णांकel */
पूर्णांक (*mce_severity)(काष्ठा mce *m, काष्ठा pt_regs *regs, पूर्णांक tolerant, अक्षर **msg, bool is_excp) =
		    mce_severity_पूर्णांकel;

व्योम __init mcheck_venकरोr_init_severity(व्योम)
अणु
	अगर (boot_cpu_data.x86_venकरोr == X86_VENDOR_AMD ||
	    boot_cpu_data.x86_venकरोr == X86_VENDOR_HYGON)
		mce_severity = mce_severity_amd;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल व्योम *s_start(काष्ठा seq_file *f, loff_t *pos)
अणु
	अगर (*pos >= ARRAY_SIZE(severities))
		वापस शून्य;
	वापस &severities[*pos];
पूर्ण

अटल व्योम *s_next(काष्ठा seq_file *f, व्योम *data, loff_t *pos)
अणु
	अगर (++(*pos) >= ARRAY_SIZE(severities))
		वापस शून्य;
	वापस &severities[*pos];
पूर्ण

अटल व्योम s_stop(काष्ठा seq_file *f, व्योम *data)
अणु
पूर्ण

अटल पूर्णांक s_show(काष्ठा seq_file *f, व्योम *data)
अणु
	काष्ठा severity *ser = data;
	seq_म_लिखो(f, "%d\t%s\n", ser->covered, ser->msg);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations severities_seq_ops = अणु
	.start	= s_start,
	.next	= s_next,
	.stop	= s_stop,
	.show	= s_show,
पूर्ण;

अटल पूर्णांक severities_coverage_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस seq_खोलो(file, &severities_seq_ops);
पूर्ण

अटल sमाप_प्रकार severities_coverage_ग_लिखो(काष्ठा file *file,
					 स्थिर अक्षर __user *ubuf,
					 माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < ARRAY_SIZE(severities); i++)
		severities[i].covered = 0;
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations severities_coverage_fops = अणु
	.खोलो		= severities_coverage_खोलो,
	.release	= seq_release,
	.पढ़ो		= seq_पढ़ो,
	.ग_लिखो		= severities_coverage_ग_लिखो,
	.llseek		= seq_lseek,
पूर्ण;

अटल पूर्णांक __init severities_debugfs_init(व्योम)
अणु
	काष्ठा dentry *dmce;

	dmce = mce_get_debugfs_dir();

	debugfs_create_file("severities-coverage", 0444, dmce, शून्य,
			    &severities_coverage_fops);
	वापस 0;
पूर्ण
late_initcall(severities_debugfs_init);
#पूर्ण_अगर /* CONFIG_DEBUG_FS */
