<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AMD Memory Encryption Support
 *
 * Copyright (C) 2019 SUSE
 *
 * Author: Joerg Roedel <jroedel@suse.de>
 */

#घोषणा pr_fmt(fmt)	"SEV-ES: " fmt

#समावेश <linux/sched/debug.h>	/* For show_regs() */
#समावेश <linux/percpu-defs.h>
#समावेश <linux/mem_encrypt.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/set_memory.h>
#समावेश <linux/memblock.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/cpu_entry_area.h>
#समावेश <यंत्र/stacktrace.h>
#समावेश <यंत्र/sev.h>
#समावेश <यंत्र/insn-eval.h>
#समावेश <यंत्र/fpu/पूर्णांकernal.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/realmode.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/svm.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/cpu.h>

#घोषणा DR7_RESET_VALUE        0x400

/* For early boot hypervisor communication in SEV-ES enabled guests */
अटल काष्ठा ghcb boot_ghcb_page __bss_decrypted __aligned(PAGE_SIZE);

/*
 * Needs to be in the .data section because we need it शून्य beक्रमe bss is
 * cleared
 */
अटल काष्ठा ghcb __initdata *boot_ghcb;

/* #VC handler runसमय per-CPU data */
काष्ठा sev_es_runसमय_data अणु
	काष्ठा ghcb ghcb_page;

	/* Physical storage क्रम the per-CPU IST stack of the #VC handler */
	अक्षर ist_stack[EXCEPTION_STKSZ] __aligned(PAGE_SIZE);

	/*
	 * Physical storage क्रम the per-CPU fall-back stack of the #VC handler.
	 * The fall-back stack is used when it is not safe to चयन back to the
	 * पूर्णांकerrupted stack in the #VC entry code.
	 */
	अक्षर fallback_stack[EXCEPTION_STKSZ] __aligned(PAGE_SIZE);

	/*
	 * Reserve one page per CPU as backup storage क्रम the unencrypted GHCB.
	 * It is needed when an NMI happens जबतक the #VC handler uses the real
	 * GHCB, and the NMI handler itself is causing another #VC exception. In
	 * that हाल the GHCB content of the first handler needs to be backed up
	 * and restored.
	 */
	काष्ठा ghcb backup_ghcb;

	/*
	 * Mark the per-cpu GHCBs as in-use to detect nested #VC exceptions.
	 * There is no need क्रम it to be atomic, because nothing is written to
	 * the GHCB between the पढ़ो and the ग_लिखो of ghcb_active. So it is safe
	 * to use it when a nested #VC exception happens beक्रमe the ग_लिखो.
	 *
	 * This is necessary क्रम example in the #VC->NMI->#VC हाल when the NMI
	 * happens जबतक the first #VC handler uses the GHCB. When the NMI code
	 * उठाओs a second #VC handler it might overग_लिखो the contents of the
	 * GHCB written by the first handler. To aव्योम this the content of the
	 * GHCB is saved and restored when the GHCB is detected to be in use
	 * alपढ़ोy.
	 */
	bool ghcb_active;
	bool backup_ghcb_active;

	/*
	 * Cached DR7 value - ग_लिखो it on DR7 ग_लिखोs and वापस it on पढ़ोs.
	 * That value will never make it to the real hardware DR7 as debugging
	 * is currently unsupported in SEV-ES guests.
	 */
	अचिन्हित दीर्घ dr7;
पूर्ण;

काष्ठा ghcb_state अणु
	काष्ठा ghcb *ghcb;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा sev_es_runसमय_data*, runसमय_data);
DEFINE_STATIC_KEY_FALSE(sev_es_enable_key);

/* Needed in vc_early_क्रमward_exception */
व्योम करो_early_exception(काष्ठा pt_regs *regs, पूर्णांक trapnr);

अटल व्योम __init setup_vc_stacks(पूर्णांक cpu)
अणु
	काष्ठा sev_es_runसमय_data *data;
	काष्ठा cpu_entry_area *cea;
	अचिन्हित दीर्घ vaddr;
	phys_addr_t pa;

	data = per_cpu(runसमय_data, cpu);
	cea  = get_cpu_entry_area(cpu);

	/* Map #VC IST stack */
	vaddr = CEA_ESTACK_BOT(&cea->estacks, VC);
	pa    = __pa(data->ist_stack);
	cea_set_pte((व्योम *)vaddr, pa, PAGE_KERNEL);

	/* Map VC fall-back stack */
	vaddr = CEA_ESTACK_BOT(&cea->estacks, VC2);
	pa    = __pa(data->fallback_stack);
	cea_set_pte((व्योम *)vaddr, pa, PAGE_KERNEL);
पूर्ण

अटल __always_अंतरभूत bool on_vc_stack(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ sp = regs->sp;

	/* User-mode RSP is not trusted */
	अगर (user_mode(regs))
		वापस false;

	/* SYSCALL gap still has user-mode RSP */
	अगर (ip_within_syscall_gap(regs))
		वापस false;

	वापस ((sp >= __this_cpu_ist_bottom_va(VC)) && (sp < __this_cpu_ist_top_va(VC)));
पूर्ण

/*
 * This function handles the हाल when an NMI is उठाओd in the #VC
 * exception handler entry code, beक्रमe the #VC handler has चयनed off
 * its IST stack. In this हाल, the IST entry क्रम #VC must be adjusted,
 * so that any nested #VC exception will not overग_लिखो the stack
 * contents of the पूर्णांकerrupted #VC handler.
 *
 * The IST entry is adjusted unconditionally so that it can be also be
 * unconditionally adjusted back in __sev_es_ist_निकास(). Otherwise a
 * nested sev_es_ist_निकास() call may adjust back the IST entry too
 * early.
 *
 * The __sev_es_ist_enter() and __sev_es_ist_निकास() functions always run
 * on the NMI IST stack, as they are only called from NMI handling code
 * right now.
 */
व्योम noinstr __sev_es_ist_enter(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ old_ist, new_ist;

	/* Read old IST entry */
	new_ist = old_ist = __this_cpu_पढ़ो(cpu_tss_rw.x86_tss.ist[IST_INDEX_VC]);

	/*
	 * If NMI happened जबतक on the #VC IST stack, set the new IST
	 * value below regs->sp, so that the पूर्णांकerrupted stack frame is
	 * not overwritten by subsequent #VC exceptions.
	 */
	अगर (on_vc_stack(regs))
		new_ist = regs->sp;

	/*
	 * Reserve additional 8 bytes and store old IST value so this
	 * adjusपंचांगent can be unrolled in __sev_es_ist_निकास().
	 */
	new_ist -= माप(old_ist);
	*(अचिन्हित दीर्घ *)new_ist = old_ist;

	/* Set new IST entry */
	this_cpu_ग_लिखो(cpu_tss_rw.x86_tss.ist[IST_INDEX_VC], new_ist);
पूर्ण

व्योम noinstr __sev_es_ist_निकास(व्योम)
अणु
	अचिन्हित दीर्घ ist;

	/* Read IST entry */
	ist = __this_cpu_पढ़ो(cpu_tss_rw.x86_tss.ist[IST_INDEX_VC]);

	अगर (WARN_ON(ist == __this_cpu_ist_top_va(VC)))
		वापस;

	/* Read back old IST entry and ग_लिखो it to the TSS */
	this_cpu_ग_लिखो(cpu_tss_rw.x86_tss.ist[IST_INDEX_VC], *(अचिन्हित दीर्घ *)ist);
पूर्ण

अटल __always_अंतरभूत काष्ठा ghcb *sev_es_get_ghcb(काष्ठा ghcb_state *state)
अणु
	काष्ठा sev_es_runसमय_data *data;
	काष्ठा ghcb *ghcb;

	data = this_cpu_पढ़ो(runसमय_data);
	ghcb = &data->ghcb_page;

	अगर (unlikely(data->ghcb_active)) अणु
		/* GHCB is alपढ़ोy in use - save its contents */

		अगर (unlikely(data->backup_ghcb_active)) अणु
			/*
			 * Backup-GHCB is also alपढ़ोy in use. There is no way
			 * to जारी here so just समाप्त the machine. To make
			 * panic() work, mark GHCBs inactive so that messages
			 * can be prपूर्णांकed out.
			 */
			data->ghcb_active        = false;
			data->backup_ghcb_active = false;

			panic("Unable to handle #VC exception! GHCB and Backup GHCB are already in use");
		पूर्ण

		/* Mark backup_ghcb active beक्रमe writing to it */
		data->backup_ghcb_active = true;

		state->ghcb = &data->backup_ghcb;

		/* Backup GHCB content */
		*state->ghcb = *ghcb;
	पूर्ण अन्यथा अणु
		state->ghcb = शून्य;
		data->ghcb_active = true;
	पूर्ण

	वापस ghcb;
पूर्ण

/* Needed in vc_early_क्रमward_exception */
व्योम करो_early_exception(काष्ठा pt_regs *regs, पूर्णांक trapnr);

अटल अंतरभूत u64 sev_es_rd_ghcb_msr(व्योम)
अणु
	वापस __rdmsr(MSR_AMD64_SEV_ES_GHCB);
पूर्ण

अटल __always_अंतरभूत व्योम sev_es_wr_ghcb_msr(u64 val)
अणु
	u32 low, high;

	low  = (u32)(val);
	high = (u32)(val >> 32);

	native_wrmsr(MSR_AMD64_SEV_ES_GHCB, low, high);
पूर्ण

अटल पूर्णांक vc_fetch_insn_kernel(काष्ठा es_em_ctxt *ctxt,
				अचिन्हित अक्षर *buffer)
अणु
	वापस copy_from_kernel_nofault(buffer, (अचिन्हित अक्षर *)ctxt->regs->ip, MAX_INSN_SIZE);
पूर्ण

अटल क्रमागत es_result __vc_decode_user_insn(काष्ठा es_em_ctxt *ctxt)
अणु
	अक्षर buffer[MAX_INSN_SIZE];
	पूर्णांक res;

	res = insn_fetch_from_user_inatomic(ctxt->regs, buffer);
	अगर (!res) अणु
		ctxt->fi.vector     = X86_TRAP_PF;
		ctxt->fi.error_code = X86_PF_INSTR | X86_PF_USER;
		ctxt->fi.cr2        = ctxt->regs->ip;
		वापस ES_EXCEPTION;
	पूर्ण

	अगर (!insn_decode_from_regs(&ctxt->insn, ctxt->regs, buffer, res))
		वापस ES_DECODE_FAILED;

	अगर (ctxt->insn.immediate.got)
		वापस ES_OK;
	अन्यथा
		वापस ES_DECODE_FAILED;
पूर्ण

अटल क्रमागत es_result __vc_decode_kern_insn(काष्ठा es_em_ctxt *ctxt)
अणु
	अक्षर buffer[MAX_INSN_SIZE];
	पूर्णांक res, ret;

	res = vc_fetch_insn_kernel(ctxt, buffer);
	अगर (res) अणु
		ctxt->fi.vector     = X86_TRAP_PF;
		ctxt->fi.error_code = X86_PF_INSTR;
		ctxt->fi.cr2        = ctxt->regs->ip;
		वापस ES_EXCEPTION;
	पूर्ण

	ret = insn_decode(&ctxt->insn, buffer, MAX_INSN_SIZE, INSN_MODE_64);
	अगर (ret < 0)
		वापस ES_DECODE_FAILED;
	अन्यथा
		वापस ES_OK;
पूर्ण

अटल क्रमागत es_result vc_decode_insn(काष्ठा es_em_ctxt *ctxt)
अणु
	अगर (user_mode(ctxt->regs))
		वापस __vc_decode_user_insn(ctxt);
	अन्यथा
		वापस __vc_decode_kern_insn(ctxt);
पूर्ण

अटल क्रमागत es_result vc_ग_लिखो_mem(काष्ठा es_em_ctxt *ctxt,
				   अक्षर *dst, अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ error_code = X86_PF_PROT | X86_PF_WRITE;
	अक्षर __user *target = (अक्षर __user *)dst;
	u64 d8;
	u32 d4;
	u16 d2;
	u8  d1;

	/*
	 * This function uses __put_user() independent of whether kernel or user
	 * memory is accessed. This works fine because __put_user() करोes no
	 * sanity checks of the poपूर्णांकer being accessed. All that it करोes is
	 * to report when the access failed.
	 *
	 * Also, this function runs in atomic context, so __put_user() is not
	 * allowed to sleep. The page-fault handler detects that it is running
	 * in atomic context and will not try to take mmap_sem and handle the
	 * fault, so additional pagefault_enable()/disable() calls are not
	 * needed.
	 *
	 * The access can't be करोne via copy_to_user() here because
	 * vc_ग_लिखो_mem() must not use string inकाष्ठाions to access unsafe
	 * memory. The reason is that MOVS is emulated by the #VC handler by
	 * splitting the move up पूर्णांकo a पढ़ो and a ग_लिखो and taking a nested #VC
	 * exception on whatever of them is the MMIO access. Using string
	 * inकाष्ठाions here would cause infinite nesting.
	 */
	चयन (size) अणु
	हाल 1:
		स_नकल(&d1, buf, 1);
		अगर (__put_user(d1, target))
			जाओ fault;
		अवरोध;
	हाल 2:
		स_नकल(&d2, buf, 2);
		अगर (__put_user(d2, target))
			जाओ fault;
		अवरोध;
	हाल 4:
		स_नकल(&d4, buf, 4);
		अगर (__put_user(d4, target))
			जाओ fault;
		अवरोध;
	हाल 8:
		स_नकल(&d8, buf, 8);
		अगर (__put_user(d8, target))
			जाओ fault;
		अवरोध;
	शेष:
		WARN_ONCE(1, "%s: Invalid size: %zu\n", __func__, size);
		वापस ES_UNSUPPORTED;
	पूर्ण

	वापस ES_OK;

fault:
	अगर (user_mode(ctxt->regs))
		error_code |= X86_PF_USER;

	ctxt->fi.vector = X86_TRAP_PF;
	ctxt->fi.error_code = error_code;
	ctxt->fi.cr2 = (अचिन्हित दीर्घ)dst;

	वापस ES_EXCEPTION;
पूर्ण

अटल क्रमागत es_result vc_पढ़ो_mem(काष्ठा es_em_ctxt *ctxt,
				  अक्षर *src, अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ error_code = X86_PF_PROT;
	अक्षर __user *s = (अक्षर __user *)src;
	u64 d8;
	u32 d4;
	u16 d2;
	u8  d1;

	/*
	 * This function uses __get_user() independent of whether kernel or user
	 * memory is accessed. This works fine because __get_user() करोes no
	 * sanity checks of the poपूर्णांकer being accessed. All that it करोes is
	 * to report when the access failed.
	 *
	 * Also, this function runs in atomic context, so __get_user() is not
	 * allowed to sleep. The page-fault handler detects that it is running
	 * in atomic context and will not try to take mmap_sem and handle the
	 * fault, so additional pagefault_enable()/disable() calls are not
	 * needed.
	 *
	 * The access can't be करोne via copy_from_user() here because
	 * vc_पढ़ो_mem() must not use string inकाष्ठाions to access unsafe
	 * memory. The reason is that MOVS is emulated by the #VC handler by
	 * splitting the move up पूर्णांकo a पढ़ो and a ग_लिखो and taking a nested #VC
	 * exception on whatever of them is the MMIO access. Using string
	 * inकाष्ठाions here would cause infinite nesting.
	 */
	चयन (size) अणु
	हाल 1:
		अगर (__get_user(d1, s))
			जाओ fault;
		स_नकल(buf, &d1, 1);
		अवरोध;
	हाल 2:
		अगर (__get_user(d2, s))
			जाओ fault;
		स_नकल(buf, &d2, 2);
		अवरोध;
	हाल 4:
		अगर (__get_user(d4, s))
			जाओ fault;
		स_नकल(buf, &d4, 4);
		अवरोध;
	हाल 8:
		अगर (__get_user(d8, s))
			जाओ fault;
		स_नकल(buf, &d8, 8);
		अवरोध;
	शेष:
		WARN_ONCE(1, "%s: Invalid size: %zu\n", __func__, size);
		वापस ES_UNSUPPORTED;
	पूर्ण

	वापस ES_OK;

fault:
	अगर (user_mode(ctxt->regs))
		error_code |= X86_PF_USER;

	ctxt->fi.vector = X86_TRAP_PF;
	ctxt->fi.error_code = error_code;
	ctxt->fi.cr2 = (अचिन्हित दीर्घ)src;

	वापस ES_EXCEPTION;
पूर्ण

अटल क्रमागत es_result vc_slow_virt_to_phys(काष्ठा ghcb *ghcb, काष्ठा es_em_ctxt *ctxt,
					   अचिन्हित दीर्घ vaddr, phys_addr_t *paddr)
अणु
	अचिन्हित दीर्घ va = (अचिन्हित दीर्घ)vaddr;
	अचिन्हित पूर्णांक level;
	phys_addr_t pa;
	pgd_t *pgd;
	pte_t *pte;

	pgd = __va(पढ़ो_cr3_pa());
	pgd = &pgd[pgd_index(va)];
	pte = lookup_address_in_pgd(pgd, va, &level);
	अगर (!pte) अणु
		ctxt->fi.vector     = X86_TRAP_PF;
		ctxt->fi.cr2        = vaddr;
		ctxt->fi.error_code = 0;

		अगर (user_mode(ctxt->regs))
			ctxt->fi.error_code |= X86_PF_USER;

		वापस ES_EXCEPTION;
	पूर्ण

	अगर (WARN_ON_ONCE(pte_val(*pte) & _PAGE_ENC))
		/* Emulated MMIO to/from encrypted memory not supported */
		वापस ES_UNSUPPORTED;

	pa = (phys_addr_t)pte_pfn(*pte) << PAGE_SHIFT;
	pa |= va & ~page_level_mask(level);

	*paddr = pa;

	वापस ES_OK;
पूर्ण

/* Include code shared with pre-decompression boot stage */
#समावेश "sev-shared.c"

अटल __always_अंतरभूत व्योम sev_es_put_ghcb(काष्ठा ghcb_state *state)
अणु
	काष्ठा sev_es_runसमय_data *data;
	काष्ठा ghcb *ghcb;

	data = this_cpu_पढ़ो(runसमय_data);
	ghcb = &data->ghcb_page;

	अगर (state->ghcb) अणु
		/* Restore GHCB from Backup */
		*ghcb = *state->ghcb;
		data->backup_ghcb_active = false;
		state->ghcb = शून्य;
	पूर्ण अन्यथा अणु
		/*
		 * Invalidate the GHCB so a VMGEXIT inकाष्ठाion issued
		 * from userspace won't appear to be valid.
		 */
		vc_ghcb_invalidate(ghcb);
		data->ghcb_active = false;
	पूर्ण
पूर्ण

व्योम noinstr __sev_es_nmi_complete(व्योम)
अणु
	काष्ठा ghcb_state state;
	काष्ठा ghcb *ghcb;

	ghcb = sev_es_get_ghcb(&state);

	vc_ghcb_invalidate(ghcb);
	ghcb_set_sw_निकास_code(ghcb, SVM_VMGEXIT_NMI_COMPLETE);
	ghcb_set_sw_निकास_info_1(ghcb, 0);
	ghcb_set_sw_निकास_info_2(ghcb, 0);

	sev_es_wr_ghcb_msr(__pa_nodebug(ghcb));
	VMGEXIT();

	sev_es_put_ghcb(&state);
पूर्ण

अटल u64 get_jump_table_addr(व्योम)
अणु
	काष्ठा ghcb_state state;
	अचिन्हित दीर्घ flags;
	काष्ठा ghcb *ghcb;
	u64 ret = 0;

	local_irq_save(flags);

	ghcb = sev_es_get_ghcb(&state);

	vc_ghcb_invalidate(ghcb);
	ghcb_set_sw_निकास_code(ghcb, SVM_VMGEXIT_AP_JUMP_TABLE);
	ghcb_set_sw_निकास_info_1(ghcb, SVM_VMGEXIT_GET_AP_JUMP_TABLE);
	ghcb_set_sw_निकास_info_2(ghcb, 0);

	sev_es_wr_ghcb_msr(__pa(ghcb));
	VMGEXIT();

	अगर (ghcb_sw_निकास_info_1_is_valid(ghcb) &&
	    ghcb_sw_निकास_info_2_is_valid(ghcb))
		ret = ghcb->save.sw_निकास_info_2;

	sev_es_put_ghcb(&state);

	local_irq_restore(flags);

	वापस ret;
पूर्ण

पूर्णांक sev_es_setup_ap_jump_table(काष्ठा real_mode_header *rmh)
अणु
	u16 startup_cs, startup_ip;
	phys_addr_t jump_table_pa;
	u64 jump_table_addr;
	u16 __iomem *jump_table;

	jump_table_addr = get_jump_table_addr();

	/* On UP guests there is no jump table so this is not a failure */
	अगर (!jump_table_addr)
		वापस 0;

	/* Check अगर AP Jump Table is page-aligned */
	अगर (jump_table_addr & ~PAGE_MASK)
		वापस -EINVAL;

	jump_table_pa = jump_table_addr & PAGE_MASK;

	startup_cs = (u16)(rmh->trampoline_start >> 4);
	startup_ip = (u16)(rmh->sev_es_trampoline_start -
			   rmh->trampoline_start);

	jump_table = ioremap_encrypted(jump_table_pa, PAGE_SIZE);
	अगर (!jump_table)
		वापस -EIO;

	ग_लिखोw(startup_ip, &jump_table[0]);
	ग_लिखोw(startup_cs, &jump_table[1]);

	iounmap(jump_table);

	वापस 0;
पूर्ण

/*
 * This is needed by the OVMF UEFI firmware which will use whatever it finds in
 * the GHCB MSR as its GHCB to talk to the hypervisor. So make sure the per-cpu
 * runसमय GHCBs used by the kernel are also mapped in the EFI page-table.
 */
पूर्णांक __init sev_es_efi_map_ghcbs(pgd_t *pgd)
अणु
	काष्ठा sev_es_runसमय_data *data;
	अचिन्हित दीर्घ address, pflags;
	पूर्णांक cpu;
	u64 pfn;

	अगर (!sev_es_active())
		वापस 0;

	pflags = _PAGE_NX | _PAGE_RW;

	क्रम_each_possible_cpu(cpu) अणु
		data = per_cpu(runसमय_data, cpu);

		address = __pa(&data->ghcb_page);
		pfn = address >> PAGE_SHIFT;

		अगर (kernel_map_pages_in_pgd(pgd, pfn, address, 1, pflags))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल क्रमागत es_result vc_handle_msr(काष्ठा ghcb *ghcb, काष्ठा es_em_ctxt *ctxt)
अणु
	काष्ठा pt_regs *regs = ctxt->regs;
	क्रमागत es_result ret;
	u64 निकास_info_1;

	/* Is it a WRMSR? */
	निकास_info_1 = (ctxt->insn.opcode.bytes[1] == 0x30) ? 1 : 0;

	ghcb_set_rcx(ghcb, regs->cx);
	अगर (निकास_info_1) अणु
		ghcb_set_rax(ghcb, regs->ax);
		ghcb_set_rdx(ghcb, regs->dx);
	पूर्ण

	ret = sev_es_ghcb_hv_call(ghcb, ctxt, SVM_EXIT_MSR, निकास_info_1, 0);

	अगर ((ret == ES_OK) && (!निकास_info_1)) अणु
		regs->ax = ghcb->save.rax;
		regs->dx = ghcb->save.rdx;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * This function runs on the first #VC exception after the kernel
 * चयनed to भव addresses.
 */
अटल bool __init sev_es_setup_ghcb(व्योम)
अणु
	/* First make sure the hypervisor talks a supported protocol. */
	अगर (!sev_es_negotiate_protocol())
		वापस false;

	/*
	 * Clear the boot_ghcb. The first exception comes in beक्रमe the bss
	 * section is cleared.
	 */
	स_रखो(&boot_ghcb_page, 0, PAGE_SIZE);

	/* Alright - Make the boot-ghcb खुला */
	boot_ghcb = &boot_ghcb_page;

	वापस true;
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल व्योम sev_es_ap_hlt_loop(व्योम)
अणु
	काष्ठा ghcb_state state;
	काष्ठा ghcb *ghcb;

	ghcb = sev_es_get_ghcb(&state);

	जबतक (true) अणु
		vc_ghcb_invalidate(ghcb);
		ghcb_set_sw_निकास_code(ghcb, SVM_VMGEXIT_AP_HLT_LOOP);
		ghcb_set_sw_निकास_info_1(ghcb, 0);
		ghcb_set_sw_निकास_info_2(ghcb, 0);

		sev_es_wr_ghcb_msr(__pa(ghcb));
		VMGEXIT();

		/* Wakeup संकेत? */
		अगर (ghcb_sw_निकास_info_2_is_valid(ghcb) &&
		    ghcb->save.sw_निकास_info_2)
			अवरोध;
	पूर्ण

	sev_es_put_ghcb(&state);
पूर्ण

/*
 * Play_dead handler when running under SEV-ES. This is needed because
 * the hypervisor can't deliver an SIPI request to restart the AP.
 * Instead the kernel has to issue a VMGEXIT to halt the VCPU until the
 * hypervisor wakes it up again.
 */
अटल व्योम sev_es_play_dead(व्योम)
अणु
	play_dead_common();

	/* IRQs now disabled */

	sev_es_ap_hlt_loop();

	/*
	 * If we get here, the VCPU was woken up again. Jump to CPU
	 * startup code to get it back online.
	 */
	start_cpu0();
पूर्ण
#अन्यथा  /* CONFIG_HOTPLUG_CPU */
#घोषणा sev_es_play_dead	native_play_dead
#पूर्ण_अगर /* CONFIG_HOTPLUG_CPU */

#अगर_घोषित CONFIG_SMP
अटल व्योम __init sev_es_setup_play_dead(व्योम)
अणु
	smp_ops.play_dead = sev_es_play_dead;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम sev_es_setup_play_dead(व्योम) अणु पूर्ण
#पूर्ण_अगर

अटल व्योम __init alloc_runसमय_data(पूर्णांक cpu)
अणु
	काष्ठा sev_es_runसमय_data *data;

	data = memblock_alloc(माप(*data), PAGE_SIZE);
	अगर (!data)
		panic("Can't allocate SEV-ES runtime data");

	per_cpu(runसमय_data, cpu) = data;
पूर्ण

अटल व्योम __init init_ghcb(पूर्णांक cpu)
अणु
	काष्ठा sev_es_runसमय_data *data;
	पूर्णांक err;

	data = per_cpu(runसमय_data, cpu);

	err = early_set_memory_decrypted((अचिन्हित दीर्घ)&data->ghcb_page,
					 माप(data->ghcb_page));
	अगर (err)
		panic("Can't map GHCBs unencrypted");

	स_रखो(&data->ghcb_page, 0, माप(data->ghcb_page));

	data->ghcb_active = false;
	data->backup_ghcb_active = false;
पूर्ण

व्योम __init sev_es_init_vc_handling(व्योम)
अणु
	पूर्णांक cpu;

	BUILD_BUG_ON(दुरत्व(काष्ठा sev_es_runसमय_data, ghcb_page) % PAGE_SIZE);

	अगर (!sev_es_active())
		वापस;

	अगर (!sev_es_check_cpu_features())
		panic("SEV-ES CPU Features missing");

	/* Enable SEV-ES special handling */
	अटल_branch_enable(&sev_es_enable_key);

	/* Initialize per-cpu GHCB pages */
	क्रम_each_possible_cpu(cpu) अणु
		alloc_runसमय_data(cpu);
		init_ghcb(cpu);
		setup_vc_stacks(cpu);
	पूर्ण

	sev_es_setup_play_dead();

	/* Secondary CPUs use the runसमय #VC handler */
	initial_vc_handler = (अचिन्हित दीर्घ)safe_stack_exc_vmm_communication;
पूर्ण

अटल व्योम __init vc_early_क्रमward_exception(काष्ठा es_em_ctxt *ctxt)
अणु
	पूर्णांक trapnr = ctxt->fi.vector;

	अगर (trapnr == X86_TRAP_PF)
		native_ग_लिखो_cr2(ctxt->fi.cr2);

	ctxt->regs->orig_ax = ctxt->fi.error_code;
	करो_early_exception(ctxt->regs, trapnr);
पूर्ण

अटल दीर्घ *vc_insn_get_reg(काष्ठा es_em_ctxt *ctxt)
अणु
	दीर्घ *reg_array;
	पूर्णांक offset;

	reg_array = (दीर्घ *)ctxt->regs;
	offset    = insn_get_modrm_reg_off(&ctxt->insn, ctxt->regs);

	अगर (offset < 0)
		वापस शून्य;

	offset /= माप(दीर्घ);

	वापस reg_array + offset;
पूर्ण

अटल दीर्घ *vc_insn_get_rm(काष्ठा es_em_ctxt *ctxt)
अणु
	दीर्घ *reg_array;
	पूर्णांक offset;

	reg_array = (दीर्घ *)ctxt->regs;
	offset    = insn_get_modrm_rm_off(&ctxt->insn, ctxt->regs);

	अगर (offset < 0)
		वापस शून्य;

	offset /= माप(दीर्घ);

	वापस reg_array + offset;
पूर्ण
अटल क्रमागत es_result vc_करो_mmio(काष्ठा ghcb *ghcb, काष्ठा es_em_ctxt *ctxt,
				 अचिन्हित पूर्णांक bytes, bool पढ़ो)
अणु
	u64 निकास_code, निकास_info_1, निकास_info_2;
	अचिन्हित दीर्घ ghcb_pa = __pa(ghcb);
	क्रमागत es_result res;
	phys_addr_t paddr;
	व्योम __user *ref;

	ref = insn_get_addr_ref(&ctxt->insn, ctxt->regs);
	अगर (ref == (व्योम __user *)-1L)
		वापस ES_UNSUPPORTED;

	निकास_code = पढ़ो ? SVM_VMGEXIT_MMIO_READ : SVM_VMGEXIT_MMIO_WRITE;

	res = vc_slow_virt_to_phys(ghcb, ctxt, (अचिन्हित दीर्घ)ref, &paddr);
	अगर (res != ES_OK) अणु
		अगर (res == ES_EXCEPTION && !पढ़ो)
			ctxt->fi.error_code |= X86_PF_WRITE;

		वापस res;
	पूर्ण

	निकास_info_1 = paddr;
	/* Can never be greater than 8 */
	निकास_info_2 = bytes;

	ghcb_set_sw_scratch(ghcb, ghcb_pa + दुरत्व(काष्ठा ghcb, shared_buffer));

	वापस sev_es_ghcb_hv_call(ghcb, ctxt, निकास_code, निकास_info_1, निकास_info_2);
पूर्ण

अटल क्रमागत es_result vc_handle_mmio_twobyte_ops(काष्ठा ghcb *ghcb,
						 काष्ठा es_em_ctxt *ctxt)
अणु
	काष्ठा insn *insn = &ctxt->insn;
	अचिन्हित पूर्णांक bytes = 0;
	क्रमागत es_result ret;
	पूर्णांक sign_byte;
	दीर्घ *reg_data;

	चयन (insn->opcode.bytes[1]) अणु
		/* MMIO Read w/ zero-extension */
	हाल 0xb6:
		bytes = 1;
		fallthrough;
	हाल 0xb7:
		अगर (!bytes)
			bytes = 2;

		ret = vc_करो_mmio(ghcb, ctxt, bytes, true);
		अगर (ret)
			अवरोध;

		/* Zero extend based on opeअक्रम size */
		reg_data = vc_insn_get_reg(ctxt);
		अगर (!reg_data)
			वापस ES_DECODE_FAILED;

		स_रखो(reg_data, 0, insn->opnd_bytes);

		स_नकल(reg_data, ghcb->shared_buffer, bytes);
		अवरोध;

		/* MMIO Read w/ sign-extension */
	हाल 0xbe:
		bytes = 1;
		fallthrough;
	हाल 0xbf:
		अगर (!bytes)
			bytes = 2;

		ret = vc_करो_mmio(ghcb, ctxt, bytes, true);
		अगर (ret)
			अवरोध;

		/* Sign extend based on opeअक्रम size */
		reg_data = vc_insn_get_reg(ctxt);
		अगर (!reg_data)
			वापस ES_DECODE_FAILED;

		अगर (bytes == 1) अणु
			u8 *val = (u8 *)ghcb->shared_buffer;

			sign_byte = (*val & 0x80) ? 0xff : 0x00;
		पूर्ण अन्यथा अणु
			u16 *val = (u16 *)ghcb->shared_buffer;

			sign_byte = (*val & 0x8000) ? 0xff : 0x00;
		पूर्ण
		स_रखो(reg_data, sign_byte, insn->opnd_bytes);

		स_नकल(reg_data, ghcb->shared_buffer, bytes);
		अवरोध;

	शेष:
		ret = ES_UNSUPPORTED;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * The MOVS inकाष्ठाion has two memory opeअक्रमs, which उठाओs the
 * problem that it is not known whether the access to the source or the
 * destination caused the #VC exception (and hence whether an MMIO पढ़ो
 * or ग_लिखो operation needs to be emulated).
 *
 * Instead of playing games with walking page-tables and trying to guess
 * whether the source or destination is an MMIO range, split the move
 * पूर्णांकo two operations, a पढ़ो and a ग_लिखो with only one memory opeअक्रम.
 * This will cause a nested #VC exception on the MMIO address which can
 * then be handled.
 *
 * This implementation has the benefit that it also supports MOVS where
 * source _and_ destination are MMIO regions.
 *
 * It will slow MOVS on MMIO करोwn a lot, but in SEV-ES guests it is a
 * rare operation. If it turns out to be a perक्रमmance problem the split
 * operations can be moved to स_नकल_fromio() and स_नकल_toio().
 */
अटल क्रमागत es_result vc_handle_mmio_movs(काष्ठा es_em_ctxt *ctxt,
					  अचिन्हित पूर्णांक bytes)
अणु
	अचिन्हित दीर्घ ds_base, es_base;
	अचिन्हित अक्षर *src, *dst;
	अचिन्हित अक्षर buffer[8];
	क्रमागत es_result ret;
	bool rep;
	पूर्णांक off;

	ds_base = insn_get_seg_base(ctxt->regs, INAT_SEG_REG_DS);
	es_base = insn_get_seg_base(ctxt->regs, INAT_SEG_REG_ES);

	अगर (ds_base == -1L || es_base == -1L) अणु
		ctxt->fi.vector = X86_TRAP_GP;
		ctxt->fi.error_code = 0;
		वापस ES_EXCEPTION;
	पूर्ण

	src = ds_base + (अचिन्हित अक्षर *)ctxt->regs->si;
	dst = es_base + (अचिन्हित अक्षर *)ctxt->regs->di;

	ret = vc_पढ़ो_mem(ctxt, src, buffer, bytes);
	अगर (ret != ES_OK)
		वापस ret;

	ret = vc_ग_लिखो_mem(ctxt, dst, buffer, bytes);
	अगर (ret != ES_OK)
		वापस ret;

	अगर (ctxt->regs->flags & X86_EFLAGS_DF)
		off = -bytes;
	अन्यथा
		off =  bytes;

	ctxt->regs->si += off;
	ctxt->regs->di += off;

	rep = insn_has_rep_prefix(&ctxt->insn);
	अगर (rep)
		ctxt->regs->cx -= 1;

	अगर (!rep || ctxt->regs->cx == 0)
		वापस ES_OK;
	अन्यथा
		वापस ES_RETRY;
पूर्ण

अटल क्रमागत es_result vc_handle_mmio(काष्ठा ghcb *ghcb,
				     काष्ठा es_em_ctxt *ctxt)
अणु
	काष्ठा insn *insn = &ctxt->insn;
	अचिन्हित पूर्णांक bytes = 0;
	क्रमागत es_result ret;
	दीर्घ *reg_data;

	चयन (insn->opcode.bytes[0]) अणु
	/* MMIO Write */
	हाल 0x88:
		bytes = 1;
		fallthrough;
	हाल 0x89:
		अगर (!bytes)
			bytes = insn->opnd_bytes;

		reg_data = vc_insn_get_reg(ctxt);
		अगर (!reg_data)
			वापस ES_DECODE_FAILED;

		स_नकल(ghcb->shared_buffer, reg_data, bytes);

		ret = vc_करो_mmio(ghcb, ctxt, bytes, false);
		अवरोध;

	हाल 0xc6:
		bytes = 1;
		fallthrough;
	हाल 0xc7:
		अगर (!bytes)
			bytes = insn->opnd_bytes;

		स_नकल(ghcb->shared_buffer, insn->immediate1.bytes, bytes);

		ret = vc_करो_mmio(ghcb, ctxt, bytes, false);
		अवरोध;

		/* MMIO Read */
	हाल 0x8a:
		bytes = 1;
		fallthrough;
	हाल 0x8b:
		अगर (!bytes)
			bytes = insn->opnd_bytes;

		ret = vc_करो_mmio(ghcb, ctxt, bytes, true);
		अगर (ret)
			अवरोध;

		reg_data = vc_insn_get_reg(ctxt);
		अगर (!reg_data)
			वापस ES_DECODE_FAILED;

		/* Zero-extend क्रम 32-bit operation */
		अगर (bytes == 4)
			*reg_data = 0;

		स_नकल(reg_data, ghcb->shared_buffer, bytes);
		अवरोध;

		/* MOVS inकाष्ठाion */
	हाल 0xa4:
		bytes = 1;
		fallthrough;
	हाल 0xa5:
		अगर (!bytes)
			bytes = insn->opnd_bytes;

		ret = vc_handle_mmio_movs(ctxt, bytes);
		अवरोध;
		/* Two-Byte Opcodes */
	हाल 0x0f:
		ret = vc_handle_mmio_twobyte_ops(ghcb, ctxt);
		अवरोध;
	शेष:
		ret = ES_UNSUPPORTED;
	पूर्ण

	वापस ret;
पूर्ण

अटल क्रमागत es_result vc_handle_dr7_ग_लिखो(काष्ठा ghcb *ghcb,
					  काष्ठा es_em_ctxt *ctxt)
अणु
	काष्ठा sev_es_runसमय_data *data = this_cpu_पढ़ो(runसमय_data);
	दीर्घ val, *reg = vc_insn_get_rm(ctxt);
	क्रमागत es_result ret;

	अगर (!reg)
		वापस ES_DECODE_FAILED;

	val = *reg;

	/* Upper 32 bits must be written as zeroes */
	अगर (val >> 32) अणु
		ctxt->fi.vector = X86_TRAP_GP;
		ctxt->fi.error_code = 0;
		वापस ES_EXCEPTION;
	पूर्ण

	/* Clear out other reserved bits and set bit 10 */
	val = (val & 0xffff23ffL) | BIT(10);

	/* Early non-zero ग_लिखोs to DR7 are not supported */
	अगर (!data && (val & ~DR7_RESET_VALUE))
		वापस ES_UNSUPPORTED;

	/* Using a value of 0 क्रम ExitInfo1 means RAX holds the value */
	ghcb_set_rax(ghcb, val);
	ret = sev_es_ghcb_hv_call(ghcb, ctxt, SVM_EXIT_WRITE_DR7, 0, 0);
	अगर (ret != ES_OK)
		वापस ret;

	अगर (data)
		data->dr7 = val;

	वापस ES_OK;
पूर्ण

अटल क्रमागत es_result vc_handle_dr7_पढ़ो(काष्ठा ghcb *ghcb,
					 काष्ठा es_em_ctxt *ctxt)
अणु
	काष्ठा sev_es_runसमय_data *data = this_cpu_पढ़ो(runसमय_data);
	दीर्घ *reg = vc_insn_get_rm(ctxt);

	अगर (!reg)
		वापस ES_DECODE_FAILED;

	अगर (data)
		*reg = data->dr7;
	अन्यथा
		*reg = DR7_RESET_VALUE;

	वापस ES_OK;
पूर्ण

अटल क्रमागत es_result vc_handle_wbinvd(काष्ठा ghcb *ghcb,
				       काष्ठा es_em_ctxt *ctxt)
अणु
	वापस sev_es_ghcb_hv_call(ghcb, ctxt, SVM_EXIT_WBINVD, 0, 0);
पूर्ण

अटल क्रमागत es_result vc_handle_rdpmc(काष्ठा ghcb *ghcb, काष्ठा es_em_ctxt *ctxt)
अणु
	क्रमागत es_result ret;

	ghcb_set_rcx(ghcb, ctxt->regs->cx);

	ret = sev_es_ghcb_hv_call(ghcb, ctxt, SVM_EXIT_RDPMC, 0, 0);
	अगर (ret != ES_OK)
		वापस ret;

	अगर (!(ghcb_rax_is_valid(ghcb) && ghcb_rdx_is_valid(ghcb)))
		वापस ES_VMM_ERROR;

	ctxt->regs->ax = ghcb->save.rax;
	ctxt->regs->dx = ghcb->save.rdx;

	वापस ES_OK;
पूर्ण

अटल क्रमागत es_result vc_handle_monitor(काष्ठा ghcb *ghcb,
					काष्ठा es_em_ctxt *ctxt)
अणु
	/*
	 * Treat it as a NOP and करो not leak a physical address to the
	 * hypervisor.
	 */
	वापस ES_OK;
पूर्ण

अटल क्रमागत es_result vc_handle_mरुको(काष्ठा ghcb *ghcb,
				      काष्ठा es_em_ctxt *ctxt)
अणु
	/* Treat the same as MONITOR/MONITORX */
	वापस ES_OK;
पूर्ण

अटल क्रमागत es_result vc_handle_vmmcall(काष्ठा ghcb *ghcb,
					काष्ठा es_em_ctxt *ctxt)
अणु
	क्रमागत es_result ret;

	ghcb_set_rax(ghcb, ctxt->regs->ax);
	ghcb_set_cpl(ghcb, user_mode(ctxt->regs) ? 3 : 0);

	अगर (x86_platक्रमm.hyper.sev_es_hcall_prepare)
		x86_platक्रमm.hyper.sev_es_hcall_prepare(ghcb, ctxt->regs);

	ret = sev_es_ghcb_hv_call(ghcb, ctxt, SVM_EXIT_VMMCALL, 0, 0);
	अगर (ret != ES_OK)
		वापस ret;

	अगर (!ghcb_rax_is_valid(ghcb))
		वापस ES_VMM_ERROR;

	ctxt->regs->ax = ghcb->save.rax;

	/*
	 * Call sev_es_hcall_finish() after regs->ax is alपढ़ोy set.
	 * This allows the hypervisor handler to overग_लिखो it again अगर
	 * necessary.
	 */
	अगर (x86_platक्रमm.hyper.sev_es_hcall_finish &&
	    !x86_platक्रमm.hyper.sev_es_hcall_finish(ghcb, ctxt->regs))
		वापस ES_VMM_ERROR;

	वापस ES_OK;
पूर्ण

अटल क्रमागत es_result vc_handle_trap_ac(काष्ठा ghcb *ghcb,
					काष्ठा es_em_ctxt *ctxt)
अणु
	/*
	 * Calling ecx_alignment_check() directly करोes not work, because it
	 * enables IRQs and the GHCB is active. Forward the exception and call
	 * it later from vc_क्रमward_exception().
	 */
	ctxt->fi.vector = X86_TRAP_AC;
	ctxt->fi.error_code = 0;
	वापस ES_EXCEPTION;
पूर्ण

अटल __always_अंतरभूत व्योम vc_handle_trap_db(काष्ठा pt_regs *regs)
अणु
	अगर (user_mode(regs))
		noist_exc_debug(regs);
	अन्यथा
		exc_debug(regs);
पूर्ण

अटल क्रमागत es_result vc_handle_निकासcode(काष्ठा es_em_ctxt *ctxt,
					 काष्ठा ghcb *ghcb,
					 अचिन्हित दीर्घ निकास_code)
अणु
	क्रमागत es_result result;

	चयन (निकास_code) अणु
	हाल SVM_EXIT_READ_DR7:
		result = vc_handle_dr7_पढ़ो(ghcb, ctxt);
		अवरोध;
	हाल SVM_EXIT_WRITE_DR7:
		result = vc_handle_dr7_ग_लिखो(ghcb, ctxt);
		अवरोध;
	हाल SVM_EXIT_EXCP_BASE + X86_TRAP_AC:
		result = vc_handle_trap_ac(ghcb, ctxt);
		अवरोध;
	हाल SVM_EXIT_RDTSC:
	हाल SVM_EXIT_RDTSCP:
		result = vc_handle_rdtsc(ghcb, ctxt, निकास_code);
		अवरोध;
	हाल SVM_EXIT_RDPMC:
		result = vc_handle_rdpmc(ghcb, ctxt);
		अवरोध;
	हाल SVM_EXIT_INVD:
		pr_err_ratelimited("#VC exception for INVD??? Seriously???\n");
		result = ES_UNSUPPORTED;
		अवरोध;
	हाल SVM_EXIT_CPUID:
		result = vc_handle_cpuid(ghcb, ctxt);
		अवरोध;
	हाल SVM_EXIT_IOIO:
		result = vc_handle_ioio(ghcb, ctxt);
		अवरोध;
	हाल SVM_EXIT_MSR:
		result = vc_handle_msr(ghcb, ctxt);
		अवरोध;
	हाल SVM_EXIT_VMMCALL:
		result = vc_handle_vmmcall(ghcb, ctxt);
		अवरोध;
	हाल SVM_EXIT_WBINVD:
		result = vc_handle_wbinvd(ghcb, ctxt);
		अवरोध;
	हाल SVM_EXIT_MONITOR:
		result = vc_handle_monitor(ghcb, ctxt);
		अवरोध;
	हाल SVM_EXIT_MWAIT:
		result = vc_handle_mरुको(ghcb, ctxt);
		अवरोध;
	हाल SVM_EXIT_NPF:
		result = vc_handle_mmio(ghcb, ctxt);
		अवरोध;
	शेष:
		/*
		 * Unexpected #VC exception
		 */
		result = ES_UNSUPPORTED;
	पूर्ण

	वापस result;
पूर्ण

अटल __always_अंतरभूत व्योम vc_क्रमward_exception(काष्ठा es_em_ctxt *ctxt)
अणु
	दीर्घ error_code = ctxt->fi.error_code;
	पूर्णांक trapnr = ctxt->fi.vector;

	ctxt->regs->orig_ax = ctxt->fi.error_code;

	चयन (trapnr) अणु
	हाल X86_TRAP_GP:
		exc_general_protection(ctxt->regs, error_code);
		अवरोध;
	हाल X86_TRAP_UD:
		exc_invalid_op(ctxt->regs);
		अवरोध;
	हाल X86_TRAP_PF:
		ग_लिखो_cr2(ctxt->fi.cr2);
		exc_page_fault(ctxt->regs, error_code);
		अवरोध;
	हाल X86_TRAP_AC:
		exc_alignment_check(ctxt->regs, error_code);
		अवरोध;
	शेष:
		pr_emerg("Unsupported exception in #VC instruction emulation - can't continue\n");
		BUG();
	पूर्ण
पूर्ण

अटल __always_अंतरभूत bool on_vc_fallback_stack(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ sp = (अचिन्हित दीर्घ)regs;

	वापस (sp >= __this_cpu_ist_bottom_va(VC2) && sp < __this_cpu_ist_top_va(VC2));
पूर्ण

/*
 * Main #VC exception handler. It is called when the entry code was able to
 * चयन off the IST to a safe kernel stack.
 *
 * With the current implementation it is always possible to चयन to a safe
 * stack because #VC exceptions only happen at known places, like पूर्णांकercepted
 * inकाष्ठाions or accesses to MMIO areas/IO ports. They can also happen with
 * code instrumentation when the hypervisor पूर्णांकercepts #DB, but the critical
 * paths are क्रमbidden to be instrumented, so #DB exceptions currently also
 * only happen in safe places.
 */
DEFINE_IDTENTRY_VC_SAFE_STACK(exc_vmm_communication)
अणु
	irqentry_state_t irq_state;
	काष्ठा ghcb_state state;
	काष्ठा es_em_ctxt ctxt;
	क्रमागत es_result result;
	काष्ठा ghcb *ghcb;

	/*
	 * Handle #DB beक्रमe calling पूर्णांकo !noinstr code to aव्योम recursive #DB.
	 */
	अगर (error_code == SVM_EXIT_EXCP_BASE + X86_TRAP_DB) अणु
		vc_handle_trap_db(regs);
		वापस;
	पूर्ण

	irq_state = irqentry_nmi_enter(regs);
	lockdep_निश्चित_irqs_disabled();
	instrumentation_begin();

	/*
	 * This is invoked through an पूर्णांकerrupt gate, so IRQs are disabled. The
	 * code below might walk page-tables क्रम user or kernel addresses, so
	 * keep the IRQs disabled to protect us against concurrent TLB flushes.
	 */

	ghcb = sev_es_get_ghcb(&state);

	vc_ghcb_invalidate(ghcb);
	result = vc_init_em_ctxt(&ctxt, regs, error_code);

	अगर (result == ES_OK)
		result = vc_handle_निकासcode(&ctxt, ghcb, error_code);

	sev_es_put_ghcb(&state);

	/* Done - now check the result */
	चयन (result) अणु
	हाल ES_OK:
		vc_finish_insn(&ctxt);
		अवरोध;
	हाल ES_UNSUPPORTED:
		pr_err_ratelimited("Unsupported exit-code 0x%02lx in early #VC exception (IP: 0x%lx)\n",
				   error_code, regs->ip);
		जाओ fail;
	हाल ES_VMM_ERROR:
		pr_err_ratelimited("Failure in communication with VMM (exit-code 0x%02lx IP: 0x%lx)\n",
				   error_code, regs->ip);
		जाओ fail;
	हाल ES_DECODE_FAILED:
		pr_err_ratelimited("Failed to decode instruction (exit-code 0x%02lx IP: 0x%lx)\n",
				   error_code, regs->ip);
		जाओ fail;
	हाल ES_EXCEPTION:
		vc_क्रमward_exception(&ctxt);
		अवरोध;
	हाल ES_RETRY:
		/* Nothing to करो */
		अवरोध;
	शेष:
		pr_emerg("Unknown result in %s():%d\n", __func__, result);
		/*
		 * Emulating the inकाष्ठाion which caused the #VC exception
		 * failed - can't जारी so prपूर्णांक debug inक्रमmation
		 */
		BUG();
	पूर्ण

out:
	instrumentation_end();
	irqentry_nmi_निकास(regs, irq_state);

	वापस;

fail:
	अगर (user_mode(regs)) अणु
		/*
		 * Do not समाप्त the machine अगर user-space triggered the
		 * exception. Send SIGBUS instead and let user-space deal with
		 * it.
		 */
		क्रमce_sig_fault(SIGBUS, BUS_OBJERR, (व्योम __user *)0);
	पूर्ण अन्यथा अणु
		pr_emerg("PANIC: Unhandled #VC exception in kernel space (result=%d)\n",
			 result);

		/* Show some debug info */
		show_regs(regs);

		/* Ask hypervisor to sev_es_terminate */
		sev_es_terminate(GHCB_SEV_ES_REASON_GENERAL_REQUEST);

		/* If that fails and we get here - just panic */
		panic("Returned from Terminate-Request to Hypervisor\n");
	पूर्ण

	जाओ out;
पूर्ण

/* This handler runs on the #VC fall-back stack. It can cause further #VC exceptions */
DEFINE_IDTENTRY_VC_IST(exc_vmm_communication)
अणु
	instrumentation_begin();
	panic("Can't handle #VC exception from unsupported context\n");
	instrumentation_end();
पूर्ण

DEFINE_IDTENTRY_VC(exc_vmm_communication)
अणु
	अगर (likely(!on_vc_fallback_stack(regs)))
		safe_stack_exc_vmm_communication(regs, error_code);
	अन्यथा
		ist_exc_vmm_communication(regs, error_code);
पूर्ण

bool __init handle_vc_boot_ghcb(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ निकास_code = regs->orig_ax;
	काष्ठा es_em_ctxt ctxt;
	क्रमागत es_result result;

	/* Do initial setup or terminate the guest */
	अगर (unlikely(boot_ghcb == शून्य && !sev_es_setup_ghcb()))
		sev_es_terminate(GHCB_SEV_ES_REASON_GENERAL_REQUEST);

	vc_ghcb_invalidate(boot_ghcb);

	result = vc_init_em_ctxt(&ctxt, regs, निकास_code);
	अगर (result == ES_OK)
		result = vc_handle_निकासcode(&ctxt, boot_ghcb, निकास_code);

	/* Done - now check the result */
	चयन (result) अणु
	हाल ES_OK:
		vc_finish_insn(&ctxt);
		अवरोध;
	हाल ES_UNSUPPORTED:
		early_prपूर्णांकk("PANIC: Unsupported exit-code 0x%02lx in early #VC exception (IP: 0x%lx)\n",
				निकास_code, regs->ip);
		जाओ fail;
	हाल ES_VMM_ERROR:
		early_prपूर्णांकk("PANIC: Failure in communication with VMM (exit-code 0x%02lx IP: 0x%lx)\n",
				निकास_code, regs->ip);
		जाओ fail;
	हाल ES_DECODE_FAILED:
		early_prपूर्णांकk("PANIC: Failed to decode instruction (exit-code 0x%02lx IP: 0x%lx)\n",
				निकास_code, regs->ip);
		जाओ fail;
	हाल ES_EXCEPTION:
		vc_early_क्रमward_exception(&ctxt);
		अवरोध;
	हाल ES_RETRY:
		/* Nothing to करो */
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	वापस true;

fail:
	show_regs(regs);

	जबतक (true)
		halt();
पूर्ण
