<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#समावेश <linux/ptrace.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/fs.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/file.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/debug.h>

#समावेश <यंत्र/arcregs.h>
#समावेश <यंत्र/irqflags.h>

#घोषणा ARC_PATH_MAX	256

अटल noअंतरभूत व्योम prपूर्णांक_regs_scratch(काष्ठा pt_regs *regs)
अणु
	pr_cont("BTA: 0x%08lx\n SP: 0x%08lx  FP: 0x%08lx BLK: %pS\n",
		regs->bta, regs->sp, regs->fp, (व्योम *)regs->blink);
	pr_cont("LPS: 0x%08lx\tLPE: 0x%08lx\tLPC: 0x%08lx\n",
		regs->lp_start, regs->lp_end, regs->lp_count);

	pr_info("r00: 0x%08lx\tr01: 0x%08lx\tr02: 0x%08lx\n"	\
		"r03: 0x%08lx\tr04: 0x%08lx\tr05: 0x%08lx\n"	\
		"r06: 0x%08lx\tr07: 0x%08lx\tr08: 0x%08lx\n"	\
		"r09: 0x%08lx\tr10: 0x%08lx\tr11: 0x%08lx\n"	\
		"r12: 0x%08lx\t",
		regs->r0, regs->r1, regs->r2,
		regs->r3, regs->r4, regs->r5,
		regs->r6, regs->r7, regs->r8,
		regs->r9, regs->r10, regs->r11,
		regs->r12);
पूर्ण

अटल व्योम prपूर्णांक_regs_callee(काष्ठा callee_regs *regs)
अणु
	pr_cont("r13: 0x%08lx\tr14: 0x%08lx\n"			\
		"r15: 0x%08lx\tr16: 0x%08lx\tr17: 0x%08lx\n"	\
		"r18: 0x%08lx\tr19: 0x%08lx\tr20: 0x%08lx\n"	\
		"r21: 0x%08lx\tr22: 0x%08lx\tr23: 0x%08lx\n"	\
		"r24: 0x%08lx\tr25: 0x%08lx\n",
		regs->r13, regs->r14,
		regs->r15, regs->r16, regs->r17,
		regs->r18, regs->r19, regs->r20,
		regs->r21, regs->r22, regs->r23,
		regs->r24, regs->r25);
पूर्ण

अटल व्योम prपूर्णांक_task_path_n_nm(काष्ठा task_काष्ठा *tsk)
अणु
	अक्षर *path_nm = शून्य;
	काष्ठा mm_काष्ठा *mm;
	काष्ठा file *exe_file;
	अक्षर buf[ARC_PATH_MAX];

	mm = get_task_mm(tsk);
	अगर (!mm)
		जाओ करोne;

	exe_file = get_mm_exe_file(mm);
	mmput(mm);

	अगर (exe_file) अणु
		path_nm = file_path(exe_file, buf, ARC_PATH_MAX-1);
		fput(exe_file);
	पूर्ण

करोne:
	pr_info("Path: %s\n", !IS_ERR(path_nm) ? path_nm : "?");
पूर्ण

अटल व्योम show_faulting_vma(अचिन्हित दीर्घ address)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा mm_काष्ठा *active_mm = current->active_mm;

	/* can't use print_vma_addr() yet as it doesn't check क्रम
	 * non-inclusive vma
	 */
	mmap_पढ़ो_lock(active_mm);
	vma = find_vma(active_mm, address);

	/* check against the find_vma( ) behaviour which वापसs the next VMA
	 * अगर the container VMA is not found
	 */
	अगर (vma && (vma->vm_start <= address)) अणु
		अक्षर buf[ARC_PATH_MAX];
		अक्षर *nm = "?";

		अगर (vma->vm_file) अणु
			nm = file_path(vma->vm_file, buf, ARC_PATH_MAX-1);
			अगर (IS_ERR(nm))
				nm = "?";
		पूर्ण
		pr_info("  @off 0x%lx in [%s]  VMA: 0x%08lx to 0x%08lx\n",
			vma->vm_start < TASK_UNMAPPED_BASE ?
				address : address - vma->vm_start,
			nm, vma->vm_start, vma->vm_end);
	पूर्ण अन्यथा
		pr_info("    @No matching VMA found\n");

	mmap_पढ़ो_unlock(active_mm);
पूर्ण

अटल व्योम show_ecr_verbose(काष्ठा pt_regs *regs)
अणु
	अचिन्हित पूर्णांक vec, cause_code;
	अचिन्हित दीर्घ address;

	/* For Data fault, this is data address not inकाष्ठाion addr */
	address = current->thपढ़ो.fault_address;

	vec = regs->ecr_vec;
	cause_code = regs->ecr_cause;

	/* For DTLB Miss or ProtV, display the memory involved too */
	अगर (vec == ECR_V_DTLB_MISS) अणु
		pr_cont("Invalid %s @ 0x%08lx by insn @ %pS\n",
		       (cause_code == 0x01) ? "Read" :
		       ((cause_code == 0x02) ? "Write" : "EX"),
		       address, (व्योम *)regs->ret);
	पूर्ण अन्यथा अगर (vec == ECR_V_ITLB_MISS) अणु
		pr_cont("Insn could not be fetched\n");
	पूर्ण अन्यथा अगर (vec == ECR_V_MACH_CHK) अणु
		pr_cont("Machine Check (%s)\n", (cause_code == 0x0) ?
					"Double Fault" : "Other Fatal Err");

	पूर्ण अन्यथा अगर (vec == ECR_V_PROTV) अणु
		अगर (cause_code == ECR_C_PROTV_INST_FETCH)
			pr_cont("Execute from Non-exec Page\n");
		अन्यथा अगर (cause_code == ECR_C_PROTV_MISALIG_DATA &&
		         IS_ENABLED(CONFIG_ISA_ARCOMPACT))
			pr_cont("Misaligned r/w from 0x%08lx\n", address);
		अन्यथा
			pr_cont("%s access not allowed on page\n",
				(cause_code == 0x01) ? "Read" :
				((cause_code == 0x02) ? "Write" : "EX"));
	पूर्ण अन्यथा अगर (vec == ECR_V_INSN_ERR) अणु
		pr_cont("Illegal Insn\n");
#अगर_घोषित CONFIG_ISA_ARCV2
	पूर्ण अन्यथा अगर (vec == ECR_V_MEM_ERR) अणु
		अगर (cause_code == 0x00)
			pr_cont("Bus Error from Insn Mem\n");
		अन्यथा अगर (cause_code == 0x10)
			pr_cont("Bus Error from Data Mem\n");
		अन्यथा
			pr_cont("Bus Error, check PRM\n");
	पूर्ण अन्यथा अगर (vec == ECR_V_MISALIGN) अणु
		pr_cont("Misaligned r/w from 0x%08lx\n", address);
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (vec == ECR_V_TRAP) अणु
		अगर (regs->ecr_param == 5)
			pr_cont("gcc generated __builtin_trap\n");
	पूर्ण अन्यथा अणु
		pr_cont("Check Programmer's Manual\n");
	पूर्ण
पूर्ण

/************************************************************************
 *  API called by rest of kernel
 ***********************************************************************/

व्योम show_regs(काष्ठा pt_regs *regs)
अणु
	काष्ठा task_काष्ठा *tsk = current;
	काष्ठा callee_regs *cregs = (काष्ठा callee_regs *)tsk->thपढ़ो.callee_reg;

	/*
	 * generic code calls us with preemption disabled, but some calls
	 * here could sleep, so re-enable to aव्योम lockdep splat
	 */
	preempt_enable();

	prपूर्णांक_task_path_n_nm(tsk);
	show_regs_prपूर्णांक_info(KERN_INFO);

	show_ecr_verbose(regs);

	अगर (user_mode(regs))
		show_faulting_vma(regs->ret); /* faulting code, not data */

	pr_info("ECR: 0x%08lx EFA: 0x%08lx ERET: 0x%08lx\nSTAT: 0x%08lx",
		regs->event, current->thपढ़ो.fault_address, regs->ret,
		regs->status32);

#घोषणा STS_BIT(r, bit)	r->status32 & STATUS_##bit##_MASK ? #bit" " : ""

#अगर_घोषित CONFIG_ISA_ARCOMPACT
	pr_cont(" [%2s%2s%2s%2s%2s%2s%2s]",
			(regs->status32 & STATUS_U_MASK) ? "U " : "K ",
			STS_BIT(regs, DE), STS_BIT(regs, AE),
			STS_BIT(regs, A2), STS_BIT(regs, A1),
			STS_BIT(regs, E2), STS_BIT(regs, E1));
#अन्यथा
	pr_cont(" [%2s%2s%2s%2s]   ",
			STS_BIT(regs, IE),
			(regs->status32 & STATUS_U_MASK) ? "U " : "K ",
			STS_BIT(regs, DE), STS_BIT(regs, AE));
#पूर्ण_अगर

	prपूर्णांक_regs_scratch(regs);
	अगर (cregs)
		prपूर्णांक_regs_callee(cregs);

	preempt_disable();
पूर्ण

व्योम show_kernel_fault_diag(स्थिर अक्षर *str, काष्ठा pt_regs *regs,
			    अचिन्हित दीर्घ address)
अणु
	current->thपढ़ो.fault_address = address;

	/* Show fault description */
	pr_info("\n%s\n", str);

	/* Caller and Callee regs */
	show_regs(regs);

	/* Show stack trace अगर this Fatality happened in kernel mode */
	अगर (!user_mode(regs))
		show_stacktrace(current, regs, KERN_DEFAULT);
पूर्ण
