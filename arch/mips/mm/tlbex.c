<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Synthesize TLB refill handlers at runसमय.
 *
 * Copyright (C) 2004, 2005, 2006, 2008	 Thiemo Seufer
 * Copyright (C) 2005, 2007, 2008, 2009	 Maciej W. Rozycki
 * Copyright (C) 2006  Ralf Baechle (ralf@linux-mips.org)
 * Copyright (C) 2008, 2009 Cavium Networks, Inc.
 * Copyright (C) 2011  MIPS Technologies, Inc.
 *
 * ... and the days got worse and worse and now you see
 * I've gone completely out of my mind.
 *
 * They're coming to take me a away haha
 * they're coming to take me a away hoho hihi haha
 * to the funny farm where code is beautअगरul all the समय ...
 *
 * (Conकरोlences to Napoleon XIV)
 */

#समावेश <linux/bug.h>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/smp.h>
#समावेश <linux/माला.स>
#समावेश <linux/cache.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cpu-type.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/war.h>
#समावेश <यंत्र/uयंत्र.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/tlbex.h>

अटल पूर्णांक mips_xpa_disabled;

अटल पूर्णांक __init xpa_disable(अक्षर *s)
अणु
	mips_xpa_disabled = 1;

	वापस 1;
पूर्ण

__setup("noxpa", xpa_disable);

/*
 * TLB load/store/modअगरy handlers.
 *
 * Only the fastpath माला_लो synthesized at runसमय, the slowpath क्रम
 * करो_page_fault reमुख्यs normal यंत्र.
 */
बाह्य व्योम tlb_करो_page_fault_0(व्योम);
बाह्य व्योम tlb_करो_page_fault_1(व्योम);

काष्ठा work_रेजिस्टरs अणु
	पूर्णांक r1;
	पूर्णांक r2;
	पूर्णांक r3;
पूर्ण;

काष्ठा tlb_reg_save अणु
	अचिन्हित दीर्घ a;
	अचिन्हित दीर्घ b;
पूर्ण ____cacheline_aligned_in_smp;

अटल काष्ठा tlb_reg_save handler_reg_save[NR_CPUS];

अटल अंतरभूत पूर्णांक r45k_bvahwbug(व्योम)
अणु
	/* XXX: We should probe क्रम the presence of this bug, but we करोn't. */
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक r4k_250MHZhwbug(व्योम)
अणु
	/* XXX: We should probe क्रम the presence of this bug, but we करोn't. */
	वापस 0;
पूर्ण

बाह्य पूर्णांक sb1250_m3_workaround_needed(व्योम);

अटल अंतरभूत पूर्णांक __maybe_unused bcm1250_m3_war(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_SB1_PASS_2_WORKAROUNDS))
		वापस sb1250_m3_workaround_needed();
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक __maybe_unused r10000_llsc_war(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_WAR_R10000_LLSC);
पूर्ण

अटल पूर्णांक use_bbit_insns(व्योम)
अणु
	चयन (current_cpu_type()) अणु
	हाल CPU_CAVIUM_OCTEON:
	हाल CPU_CAVIUM_OCTEON_PLUS:
	हाल CPU_CAVIUM_OCTEON2:
	हाल CPU_CAVIUM_OCTEON3:
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक use_lwx_insns(व्योम)
अणु
	चयन (current_cpu_type()) अणु
	हाल CPU_CAVIUM_OCTEON2:
	हाल CPU_CAVIUM_OCTEON3:
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण
#अगर defined(CONFIG_CAVIUM_OCTEON_CVMSEG_SIZE) && \
    CONFIG_CAVIUM_OCTEON_CVMSEG_SIZE > 0
अटल bool scratchpad_available(व्योम)
अणु
	वापस true;
पूर्ण
अटल पूर्णांक scratchpad_offset(पूर्णांक i)
अणु
	/*
	 * CVMSEG starts at address -32768 and extends क्रम
	 * CAVIUM_OCTEON_CVMSEG_SIZE 128 byte cache lines.
	 */
	i += 1; /* Kernel use starts at the top and works करोwn. */
	वापस CONFIG_CAVIUM_OCTEON_CVMSEG_SIZE * 128 - (8 * i) - 32768;
पूर्ण
#अन्यथा
अटल bool scratchpad_available(व्योम)
अणु
	वापस false;
पूर्ण
अटल पूर्णांक scratchpad_offset(पूर्णांक i)
अणु
	BUG();
	/* Really unreachable, but evidently some GCC want this. */
	वापस 0;
पूर्ण
#पूर्ण_अगर
/*
 * Found by experiment: At least some revisions of the 4kc throw under
 * some circumstances a machine check exception, triggered by invalid
 * values in the index रेजिस्टर.  Delaying the tlbp inकाष्ठाion until
 * after the next branch,  plus adding an additional nop in front of
 * tlbwi/tlbwr aव्योमs the invalid index रेजिस्टर values. Nobody knows
 * why; it's not an issue caused by the core RTL.
 *
 */
अटल पूर्णांक m4kc_tlbp_war(व्योम)
अणु
	वापस current_cpu_type() == CPU_4KC;
पूर्ण

/* Handle labels (which must be positive पूर्णांकegers). */
क्रमागत label_id अणु
	label_second_part = 1,
	label_leave,
	label_vदो_स्मृति,
	label_vदो_स्मृति_करोne,
	label_tlbw_hazard_0,
	label_split = label_tlbw_hazard_0 + 8,
	label_tlbl_goaround1,
	label_tlbl_goaround2,
	label_nopage_tlbl,
	label_nopage_tlbs,
	label_nopage_tlbm,
	label_smp_pgtable_change,
	label_r3000_ग_लिखो_probe_fail,
	label_large_segbits_fault,
#अगर_घोषित CONFIG_MIPS_HUGE_TLB_SUPPORT
	label_tlb_huge_update,
#पूर्ण_अगर
पूर्ण;

UASM_L_LA(_second_part)
UASM_L_LA(_leave)
UASM_L_LA(_vदो_स्मृति)
UASM_L_LA(_vदो_स्मृति_करोne)
/* _tlbw_hazard_x is handled dअगरferently.  */
UASM_L_LA(_split)
UASM_L_LA(_tlbl_goaround1)
UASM_L_LA(_tlbl_goaround2)
UASM_L_LA(_nopage_tlbl)
UASM_L_LA(_nopage_tlbs)
UASM_L_LA(_nopage_tlbm)
UASM_L_LA(_smp_pgtable_change)
UASM_L_LA(_r3000_ग_लिखो_probe_fail)
UASM_L_LA(_large_segbits_fault)
#अगर_घोषित CONFIG_MIPS_HUGE_TLB_SUPPORT
UASM_L_LA(_tlb_huge_update)
#पूर्ण_अगर

अटल पूर्णांक hazard_instance;

अटल व्योम uयंत्र_bgezl_hazard(u32 **p, काष्ठा uयंत्र_reloc **r, पूर्णांक instance)
अणु
	चयन (instance) अणु
	हाल 0 ... 7:
		uयंत्र_il_bgezl(p, r, 0, label_tlbw_hazard_0 + instance);
		वापस;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल व्योम uयंत्र_bgezl_label(काष्ठा uयंत्र_label **l, u32 **p, पूर्णांक instance)
अणु
	चयन (instance) अणु
	हाल 0 ... 7:
		uयंत्र_build_label(l, *p, label_tlbw_hazard_0 + instance);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

/*
 * pgtable bits are asचिन्हित dynamically depending on processor feature
 * and अटलally based on kernel configuration.  This spits out the actual
 * values the kernel is using.	Required to make sense from disassembled
 * TLB exception handlers.
 */
अटल व्योम output_pgtable_bits_defines(व्योम)
अणु
#घोषणा pr_define(fmt, ...)					\
	pr_debug("#define " fmt, ##__VA_ARGS__)

	pr_debug("#include <asm/asm.h>\n");
	pr_debug("#include <asm/regdef.h>\n");
	pr_debug("\n");

	pr_define("_PAGE_PRESENT_SHIFT %d\n", _PAGE_PRESENT_SHIFT);
	pr_define("_PAGE_NO_READ_SHIFT %d\n", _PAGE_NO_READ_SHIFT);
	pr_define("_PAGE_WRITE_SHIFT %d\n", _PAGE_WRITE_SHIFT);
	pr_define("_PAGE_ACCESSED_SHIFT %d\n", _PAGE_ACCESSED_SHIFT);
	pr_define("_PAGE_MODIFIED_SHIFT %d\n", _PAGE_MODIFIED_SHIFT);
#अगर_घोषित CONFIG_MIPS_HUGE_TLB_SUPPORT
	pr_define("_PAGE_HUGE_SHIFT %d\n", _PAGE_HUGE_SHIFT);
#पूर्ण_अगर
#अगर_घोषित _PAGE_NO_EXEC_SHIFT
	अगर (cpu_has_rixi)
		pr_define("_PAGE_NO_EXEC_SHIFT %d\n", _PAGE_NO_EXEC_SHIFT);
#पूर्ण_अगर
	pr_define("_PAGE_GLOBAL_SHIFT %d\n", _PAGE_GLOBAL_SHIFT);
	pr_define("_PAGE_VALID_SHIFT %d\n", _PAGE_VALID_SHIFT);
	pr_define("_PAGE_DIRTY_SHIFT %d\n", _PAGE_सूचीTY_SHIFT);
	pr_define("_PFN_SHIFT %d\n", _PFN_SHIFT);
	pr_debug("\n");
पूर्ण

अटल अंतरभूत व्योम dump_handler(स्थिर अक्षर *symbol, स्थिर व्योम *start, स्थिर व्योम *end)
अणु
	अचिन्हित पूर्णांक count = (end - start) / माप(u32);
	स्थिर u32 *handler = start;
	पूर्णांक i;

	pr_debug("LEAF(%s)\n", symbol);

	pr_debug("\t.set push\n");
	pr_debug("\t.set noreorder\n");

	क्रम (i = 0; i < count; i++)
		pr_debug("\t.word\t0x%08x\t\t# %p\n", handler[i], &handler[i]);

	pr_debug("\t.set\tpop\n");

	pr_debug("\tEND(%s)\n", symbol);
पूर्ण

/* The only general purpose रेजिस्टरs allowed in TLB handlers. */
#घोषणा K0		26
#घोषणा K1		27

/* Some CP0 रेजिस्टरs */
#घोषणा C0_INDEX	0, 0
#घोषणा C0_ENTRYLO0	2, 0
#घोषणा C0_TCBIND	2, 2
#घोषणा C0_ENTRYLO1	3, 0
#घोषणा C0_CONTEXT	4, 0
#घोषणा C0_PAGEMASK	5, 0
#घोषणा C0_PWBASE	5, 5
#घोषणा C0_PWFIELD	5, 6
#घोषणा C0_PWSIZE	5, 7
#घोषणा C0_PWCTL	6, 6
#घोषणा C0_BADVADDR	8, 0
#घोषणा C0_PGD		9, 7
#घोषणा C0_ENTRYHI	10, 0
#घोषणा C0_EPC		14, 0
#घोषणा C0_XCONTEXT	20, 0

#अगर_घोषित CONFIG_64BIT
# define GET_CONTEXT(buf, reg) UASM_i_MFC0(buf, reg, C0_XCONTEXT)
#अन्यथा
# define GET_CONTEXT(buf, reg) UASM_i_MFC0(buf, reg, C0_CONTEXT)
#पूर्ण_अगर

/* The worst हाल length of the handler is around 18 inकाष्ठाions क्रम
 * R3000-style TLBs and up to 63 inकाष्ठाions क्रम R4000-style TLBs.
 * Maximum space available is 32 inकाष्ठाions क्रम R3000 and 64
 * inकाष्ठाions क्रम R4000.
 *
 * We deliberately chose a buffer size of 128, so we won't scribble
 * over anything important on overflow beक्रमe we panic.
 */
अटल u32 tlb_handler[128];

/* simply assume worst हाल size क्रम labels and relocs */
अटल काष्ठा uयंत्र_label labels[128];
अटल काष्ठा uयंत्र_reloc relocs[128];

अटल पूर्णांक check_क्रम_high_segbits;
अटल bool fill_includes_sw_bits;

अटल अचिन्हित पूर्णांक kscratch_used_mask;

अटल अंतरभूत पूर्णांक __maybe_unused c0_kscratch(व्योम)
अणु
	चयन (current_cpu_type()) अणु
	हाल CPU_XLP:
	हाल CPU_XLR:
		वापस 22;
	शेष:
		वापस 31;
	पूर्ण
पूर्ण

अटल पूर्णांक allocate_kscratch(व्योम)
अणु
	पूर्णांक r;
	अचिन्हित पूर्णांक a = cpu_data[0].kscratch_mask & ~kscratch_used_mask;

	r = ffs(a);

	अगर (r == 0)
		वापस -1;

	r--; /* make it zero based */

	kscratch_used_mask |= (1 << r);

	वापस r;
पूर्ण

अटल पूर्णांक scratch_reg;
पूर्णांक pgd_reg;
EXPORT_SYMBOL_GPL(pgd_reg);
क्रमागत vदो_स्मृति64_mode अणुnot_refill, refill_scratch, refill_noscratchपूर्ण;

अटल काष्ठा work_रेजिस्टरs build_get_work_रेजिस्टरs(u32 **p)
अणु
	काष्ठा work_रेजिस्टरs r;

	अगर (scratch_reg >= 0) अणु
		/* Save in CPU local C0_KScratch? */
		UASM_i_MTC0(p, 1, c0_kscratch(), scratch_reg);
		r.r1 = K0;
		r.r2 = K1;
		r.r3 = 1;
		वापस r;
	पूर्ण

	अगर (num_possible_cpus() > 1) अणु
		/* Get smp_processor_id */
		UASM_i_CPUID_MFC0(p, K0, SMP_CPUID_REG);
		UASM_i_SRL_SAFE(p, K0, K0, SMP_CPUID_REGSHIFT);

		/* handler_reg_save index in K0 */
		UASM_i_SLL(p, K0, K0, ilog2(माप(काष्ठा tlb_reg_save)));

		UASM_i_LA(p, K1, (दीर्घ)&handler_reg_save);
		UASM_i_ADDU(p, K0, K0, K1);
	पूर्ण अन्यथा अणु
		UASM_i_LA(p, K0, (दीर्घ)&handler_reg_save);
	पूर्ण
	/* K0 now poपूर्णांकs to save area, save $1 and $2  */
	UASM_i_SW(p, 1, दुरत्व(काष्ठा tlb_reg_save, a), K0);
	UASM_i_SW(p, 2, दुरत्व(काष्ठा tlb_reg_save, b), K0);

	r.r1 = K1;
	r.r2 = 1;
	r.r3 = 2;
	वापस r;
पूर्ण

अटल व्योम build_restore_work_रेजिस्टरs(u32 **p)
अणु
	अगर (scratch_reg >= 0) अणु
		uयंत्र_i_ehb(p);
		UASM_i_MFC0(p, 1, c0_kscratch(), scratch_reg);
		वापस;
	पूर्ण
	/* K0 alपढ़ोy poपूर्णांकs to save area, restore $1 and $2  */
	UASM_i_LW(p, 1, दुरत्व(काष्ठा tlb_reg_save, a), K0);
	UASM_i_LW(p, 2, दुरत्व(काष्ठा tlb_reg_save, b), K0);
पूर्ण

#अगर_अघोषित CONFIG_MIPS_PGD_C0_CONTEXT

/*
 * CONFIG_MIPS_PGD_C0_CONTEXT implies 64 bit and lack of pgd_current,
 * we cannot करो r3000 under these circumstances.
 *
 * The R3000 TLB handler is simple.
 */
अटल व्योम build_r3000_tlb_refill_handler(व्योम)
अणु
	दीर्घ pgdc = (दीर्घ)pgd_current;
	u32 *p;

	स_रखो(tlb_handler, 0, माप(tlb_handler));
	p = tlb_handler;

	uयंत्र_i_mfc0(&p, K0, C0_BADVADDR);
	uयंत्र_i_lui(&p, K1, uयंत्र_rel_hi(pgdc)); /* cp0 delay */
	uयंत्र_i_lw(&p, K1, uयंत्र_rel_lo(pgdc), K1);
	uयंत्र_i_srl(&p, K0, K0, 22); /* load delay */
	uयंत्र_i_sll(&p, K0, K0, 2);
	uयंत्र_i_addu(&p, K1, K1, K0);
	uयंत्र_i_mfc0(&p, K0, C0_CONTEXT);
	uयंत्र_i_lw(&p, K1, 0, K1); /* cp0 delay */
	uयंत्र_i_andi(&p, K0, K0, 0xffc); /* load delay */
	uयंत्र_i_addu(&p, K1, K1, K0);
	uयंत्र_i_lw(&p, K0, 0, K1);
	uयंत्र_i_nop(&p); /* load delay */
	uयंत्र_i_mtc0(&p, K0, C0_ENTRYLO0);
	uयंत्र_i_mfc0(&p, K1, C0_EPC); /* cp0 delay */
	uयंत्र_i_tlbwr(&p); /* cp0 delay */
	uयंत्र_i_jr(&p, K1);
	uयंत्र_i_rfe(&p); /* branch delay */

	अगर (p > tlb_handler + 32)
		panic("TLB refill handler space exceeded");

	pr_debug("Wrote TLB refill handler (%u instructions).\n",
		 (अचिन्हित पूर्णांक)(p - tlb_handler));

	स_नकल((व्योम *)ebase, tlb_handler, 0x80);
	local_flush_icache_range(ebase, ebase + 0x80);
	dump_handler("r3000_tlb_refill", (u32 *)ebase, (u32 *)(ebase + 0x80));
पूर्ण
#पूर्ण_अगर /* CONFIG_MIPS_PGD_C0_CONTEXT */

/*
 * The R4000 TLB handler is much more complicated. We have two
 * consecutive handler areas with 32 inकाष्ठाions space each.
 * Since they aren't used at the same समय, we can overflow in the
 * other one.To keep things simple, we first assume linear space,
 * then we relocate it to the final handler layout as needed.
 */
अटल u32 final_handler[64];

/*
 * Hazards
 *
 * From the IDT errata क्रम the QED RM5230 (Nevada), processor revision 1.0:
 * 2. A timing hazard exists क्रम the TLBP inकाष्ठाion.
 *
 *	stalling_inकाष्ठाion
 *	TLBP
 *
 * The JTLB is being पढ़ो क्रम the TLBP throughout the stall generated by the
 * previous inकाष्ठाion. This is not really correct as the stalling inकाष्ठाion
 * can modअगरy the address used to access the JTLB.  The failure symptom is that
 * the TLBP inकाष्ठाion will use an address created क्रम the stalling inकाष्ठाion
 * and not the address held in C0_ENHI and thus report the wrong results.
 *
 * The software work-around is to not allow the inकाष्ठाion preceding the TLBP
 * to stall - make it an NOP or some other inकाष्ठाion guaranteed not to stall.
 *
 * Errata 2 will not be fixed.	This errata is also on the R5000.
 *
 * As अगर we MIPS hackers wouldn't know how to nop pipelines happy ...
 */
अटल व्योम __maybe_unused build_tlb_probe_entry(u32 **p)
अणु
	चयन (current_cpu_type()) अणु
	/* Found by experiment: R4600 v2.0/R4700 needs this, too.  */
	हाल CPU_R4600:
	हाल CPU_R4700:
	हाल CPU_R5000:
	हाल CPU_NEVADA:
		uयंत्र_i_nop(p);
		uयंत्र_i_tlbp(p);
		अवरोध;

	शेष:
		uयंत्र_i_tlbp(p);
		अवरोध;
	पूर्ण
पूर्ण

व्योम build_tlb_ग_लिखो_entry(u32 **p, काष्ठा uयंत्र_label **l,
			   काष्ठा uयंत्र_reloc **r,
			   क्रमागत tlb_ग_लिखो_entry wmode)
अणु
	व्योम(*tlbw)(u32 **) = शून्य;

	चयन (wmode) अणु
	हाल tlb_अक्रमom: tlbw = uयंत्र_i_tlbwr; अवरोध;
	हाल tlb_indexed: tlbw = uयंत्र_i_tlbwi; अवरोध;
	पूर्ण

	अगर (cpu_has_mips_r2_r6) अणु
		अगर (cpu_has_mips_r2_exec_hazard)
			uयंत्र_i_ehb(p);
		tlbw(p);
		वापस;
	पूर्ण

	चयन (current_cpu_type()) अणु
	हाल CPU_R4000PC:
	हाल CPU_R4000SC:
	हाल CPU_R4000MC:
	हाल CPU_R4400PC:
	हाल CPU_R4400SC:
	हाल CPU_R4400MC:
		/*
		 * This branch uses up a mtc0 hazard nop slot and saves
		 * two nops after the tlbw inकाष्ठाion.
		 */
		uयंत्र_bgezl_hazard(p, r, hazard_instance);
		tlbw(p);
		uयंत्र_bgezl_label(l, p, hazard_instance);
		hazard_instance++;
		uयंत्र_i_nop(p);
		अवरोध;

	हाल CPU_R4600:
	हाल CPU_R4700:
		uयंत्र_i_nop(p);
		tlbw(p);
		uयंत्र_i_nop(p);
		अवरोध;

	हाल CPU_R5000:
	हाल CPU_NEVADA:
		uयंत्र_i_nop(p); /* QED specअगरies 2 nops hazard */
		uयंत्र_i_nop(p); /* QED specअगरies 2 nops hazard */
		tlbw(p);
		अवरोध;

	हाल CPU_R4300:
	हाल CPU_5KC:
	हाल CPU_TX49XX:
	हाल CPU_PR4450:
	हाल CPU_XLR:
		uयंत्र_i_nop(p);
		tlbw(p);
		अवरोध;

	हाल CPU_R10000:
	हाल CPU_R12000:
	हाल CPU_R14000:
	हाल CPU_R16000:
	हाल CPU_4KC:
	हाल CPU_4KEC:
	हाल CPU_M14KC:
	हाल CPU_M14KEC:
	हाल CPU_SB1:
	हाल CPU_SB1A:
	हाल CPU_4KSC:
	हाल CPU_20KC:
	हाल CPU_25KF:
	हाल CPU_BMIPS32:
	हाल CPU_BMIPS3300:
	हाल CPU_BMIPS4350:
	हाल CPU_BMIPS4380:
	हाल CPU_BMIPS5000:
	हाल CPU_LOONGSON2EF:
	हाल CPU_LOONGSON64:
	हाल CPU_R5500:
		अगर (m4kc_tlbp_war())
			uयंत्र_i_nop(p);
		fallthrough;
	हाल CPU_ALCHEMY:
		tlbw(p);
		अवरोध;

	हाल CPU_RM7000:
		uयंत्र_i_nop(p);
		uयंत्र_i_nop(p);
		uयंत्र_i_nop(p);
		uयंत्र_i_nop(p);
		tlbw(p);
		अवरोध;

	हाल CPU_VR4111:
	हाल CPU_VR4121:
	हाल CPU_VR4122:
	हाल CPU_VR4181:
	हाल CPU_VR4181A:
		uयंत्र_i_nop(p);
		uयंत्र_i_nop(p);
		tlbw(p);
		uयंत्र_i_nop(p);
		uयंत्र_i_nop(p);
		अवरोध;

	हाल CPU_VR4131:
	हाल CPU_VR4133:
		uयंत्र_i_nop(p);
		uयंत्र_i_nop(p);
		tlbw(p);
		अवरोध;

	हाल CPU_XBURST:
		tlbw(p);
		uयंत्र_i_nop(p);
		अवरोध;

	शेष:
		panic("No TLB refill handler yet (CPU type: %d)",
		      current_cpu_type());
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(build_tlb_ग_लिखो_entry);

अटल __maybe_unused व्योम build_convert_pte_to_entrylo(u32 **p,
							अचिन्हित पूर्णांक reg)
अणु
	अगर (_PAGE_GLOBAL_SHIFT == 0) अणु
		/* pte_t is alपढ़ोy in EntryLo क्रमmat */
		वापस;
	पूर्ण

	अगर (cpu_has_rixi && !!_PAGE_NO_EXEC) अणु
		अगर (fill_includes_sw_bits) अणु
			UASM_i_ROTR(p, reg, reg, ilog2(_PAGE_GLOBAL));
		पूर्ण अन्यथा अणु
			UASM_i_SRL(p, reg, reg, ilog2(_PAGE_NO_EXEC));
			UASM_i_ROTR(p, reg, reg,
				    ilog2(_PAGE_GLOBAL) - ilog2(_PAGE_NO_EXEC));
		पूर्ण
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_PHYS_ADDR_T_64BIT
		uयंत्र_i_dsrl_safe(p, reg, reg, ilog2(_PAGE_GLOBAL));
#अन्यथा
		UASM_i_SRL(p, reg, reg, ilog2(_PAGE_GLOBAL));
#पूर्ण_अगर
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_MIPS_HUGE_TLB_SUPPORT

अटल व्योम build_restore_pagemask(u32 **p, काष्ठा uयंत्र_reloc **r,
				   अचिन्हित पूर्णांक पंचांगp, क्रमागत label_id lid,
				   पूर्णांक restore_scratch)
अणु
	अगर (restore_scratch) अणु
		/*
		 * Ensure the MFC0 below observes the value written to the
		 * KScratch रेजिस्टर by the prior MTC0.
		 */
		अगर (scratch_reg >= 0)
			uयंत्र_i_ehb(p);

		/* Reset शेष page size */
		अगर (PM_DEFAULT_MASK >> 16) अणु
			uयंत्र_i_lui(p, पंचांगp, PM_DEFAULT_MASK >> 16);
			uयंत्र_i_ori(p, पंचांगp, पंचांगp, PM_DEFAULT_MASK & 0xffff);
			uयंत्र_i_mtc0(p, पंचांगp, C0_PAGEMASK);
			uयंत्र_il_b(p, r, lid);
		पूर्ण अन्यथा अगर (PM_DEFAULT_MASK) अणु
			uयंत्र_i_ori(p, पंचांगp, 0, PM_DEFAULT_MASK);
			uयंत्र_i_mtc0(p, पंचांगp, C0_PAGEMASK);
			uयंत्र_il_b(p, r, lid);
		पूर्ण अन्यथा अणु
			uयंत्र_i_mtc0(p, 0, C0_PAGEMASK);
			uयंत्र_il_b(p, r, lid);
		पूर्ण
		अगर (scratch_reg >= 0)
			UASM_i_MFC0(p, 1, c0_kscratch(), scratch_reg);
		अन्यथा
			UASM_i_LW(p, 1, scratchpad_offset(0), 0);
	पूर्ण अन्यथा अणु
		/* Reset शेष page size */
		अगर (PM_DEFAULT_MASK >> 16) अणु
			uयंत्र_i_lui(p, पंचांगp, PM_DEFAULT_MASK >> 16);
			uयंत्र_i_ori(p, पंचांगp, पंचांगp, PM_DEFAULT_MASK & 0xffff);
			uयंत्र_il_b(p, r, lid);
			uयंत्र_i_mtc0(p, पंचांगp, C0_PAGEMASK);
		पूर्ण अन्यथा अगर (PM_DEFAULT_MASK) अणु
			uयंत्र_i_ori(p, पंचांगp, 0, PM_DEFAULT_MASK);
			uयंत्र_il_b(p, r, lid);
			uयंत्र_i_mtc0(p, पंचांगp, C0_PAGEMASK);
		पूर्ण अन्यथा अणु
			uयंत्र_il_b(p, r, lid);
			uयंत्र_i_mtc0(p, 0, C0_PAGEMASK);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम build_huge_tlb_ग_लिखो_entry(u32 **p, काष्ठा uयंत्र_label **l,
				       काष्ठा uयंत्र_reloc **r,
				       अचिन्हित पूर्णांक पंचांगp,
				       क्रमागत tlb_ग_लिखो_entry wmode,
				       पूर्णांक restore_scratch)
अणु
	/* Set huge page tlb entry size */
	uयंत्र_i_lui(p, पंचांगp, PM_HUGE_MASK >> 16);
	uयंत्र_i_ori(p, पंचांगp, पंचांगp, PM_HUGE_MASK & 0xffff);
	uयंत्र_i_mtc0(p, पंचांगp, C0_PAGEMASK);

	build_tlb_ग_लिखो_entry(p, l, r, wmode);

	build_restore_pagemask(p, r, पंचांगp, label_leave, restore_scratch);
पूर्ण

/*
 * Check अगर Huge PTE is present, अगर so then jump to LABEL.
 */
अटल व्योम
build_is_huge_pte(u32 **p, काष्ठा uयंत्र_reloc **r, अचिन्हित पूर्णांक पंचांगp,
		  अचिन्हित पूर्णांक pmd, पूर्णांक lid)
अणु
	UASM_i_LW(p, पंचांगp, 0, pmd);
	अगर (use_bbit_insns()) अणु
		uयंत्र_il_bbit1(p, r, पंचांगp, ilog2(_PAGE_HUGE), lid);
	पूर्ण अन्यथा अणु
		uयंत्र_i_andi(p, पंचांगp, पंचांगp, _PAGE_HUGE);
		uयंत्र_il_bnez(p, r, पंचांगp, lid);
	पूर्ण
पूर्ण

अटल व्योम build_huge_update_entries(u32 **p, अचिन्हित पूर्णांक pte,
				      अचिन्हित पूर्णांक पंचांगp)
अणु
	पूर्णांक small_sequence;

	/*
	 * A huge PTE describes an area the size of the
	 * configured huge page size. This is twice the
	 * of the large TLB entry size we पूर्णांकend to use.
	 * A TLB entry half the size of the configured
	 * huge page size is configured पूर्णांकo entrylo0
	 * and entrylo1 to cover the contiguous huge PTE
	 * address space.
	 */
	small_sequence = (HPAGE_SIZE >> 7) < 0x10000;

	/* We can clobber पंचांगp.	It isn't used after this.*/
	अगर (!small_sequence)
		uयंत्र_i_lui(p, पंचांगp, HPAGE_SIZE >> (7 + 16));

	build_convert_pte_to_entrylo(p, pte);
	UASM_i_MTC0(p, pte, C0_ENTRYLO0); /* load it */
	/* convert to entrylo1 */
	अगर (small_sequence)
		UASM_i_ADDIU(p, pte, pte, HPAGE_SIZE >> 7);
	अन्यथा
		UASM_i_ADDU(p, pte, pte, पंचांगp);

	UASM_i_MTC0(p, pte, C0_ENTRYLO1); /* load it */
पूर्ण

अटल व्योम build_huge_handler_tail(u32 **p, काष्ठा uयंत्र_reloc **r,
				    काष्ठा uयंत्र_label **l,
				    अचिन्हित पूर्णांक pte,
				    अचिन्हित पूर्णांक ptr,
				    अचिन्हित पूर्णांक flush)
अणु
#अगर_घोषित CONFIG_SMP
	UASM_i_SC(p, pte, 0, ptr);
	uयंत्र_il_beqz(p, r, pte, label_tlb_huge_update);
	UASM_i_LW(p, pte, 0, ptr); /* Needed because SC समाप्तed our PTE */
#अन्यथा
	UASM_i_SW(p, pte, 0, ptr);
#पूर्ण_अगर
	अगर (cpu_has_ftlb && flush) अणु
		BUG_ON(!cpu_has_tlbinv);

		UASM_i_MFC0(p, ptr, C0_ENTRYHI);
		uयंत्र_i_ori(p, ptr, ptr, MIPS_ENTRYHI_EHINV);
		UASM_i_MTC0(p, ptr, C0_ENTRYHI);
		build_tlb_ग_लिखो_entry(p, l, r, tlb_indexed);

		uयंत्र_i_xori(p, ptr, ptr, MIPS_ENTRYHI_EHINV);
		UASM_i_MTC0(p, ptr, C0_ENTRYHI);
		build_huge_update_entries(p, pte, ptr);
		build_huge_tlb_ग_लिखो_entry(p, l, r, pte, tlb_अक्रमom, 0);

		वापस;
	पूर्ण

	build_huge_update_entries(p, pte, ptr);
	build_huge_tlb_ग_लिखो_entry(p, l, r, pte, tlb_indexed, 0);
पूर्ण
#पूर्ण_अगर /* CONFIG_MIPS_HUGE_TLB_SUPPORT */

#अगर_घोषित CONFIG_64BIT
/*
 * TMP and PTR are scratch.
 * TMP will be clobbered, PTR will hold the pmd entry.
 */
व्योम build_get_pmde64(u32 **p, काष्ठा uयंत्र_label **l, काष्ठा uयंत्र_reloc **r,
		      अचिन्हित पूर्णांक पंचांगp, अचिन्हित पूर्णांक ptr)
अणु
#अगर_अघोषित CONFIG_MIPS_PGD_C0_CONTEXT
	दीर्घ pgdc = (दीर्घ)pgd_current;
#पूर्ण_अगर
	/*
	 * The vदो_स्मृति handling is not in the hotpath.
	 */
	uयंत्र_i_dmfc0(p, पंचांगp, C0_BADVADDR);

	अगर (check_क्रम_high_segbits) अणु
		/*
		 * The kernel currently implicitely assumes that the
		 * MIPS SEGBITS parameter क्रम the processor is
		 * (PGसूची_SHIFT+PGसूची_BITS) or less, and will never
		 * allocate भव addresses outside the maximum
		 * range क्रम SEGBITS = (PGसूची_SHIFT+PGसूची_BITS). But
		 * that करोesn't prevent user code from accessing the
		 * higher xuseg addresses.  Here, we make sure that
		 * everything but the lower xuseg addresses goes करोwn
		 * the module_alloc/vदो_स्मृति path.
		 */
		uयंत्र_i_dsrl_safe(p, ptr, पंचांगp, PGसूची_SHIFT + PGD_ORDER + PAGE_SHIFT - 3);
		uयंत्र_il_bnez(p, r, ptr, label_vदो_स्मृति);
	पूर्ण अन्यथा अणु
		uयंत्र_il_bltz(p, r, पंचांगp, label_vदो_स्मृति);
	पूर्ण
	/* No uयंत्र_i_nop needed here, since the next insn करोesn't touch TMP. */

	अगर (pgd_reg != -1) अणु
		/* pgd is in pgd_reg */
		अगर (cpu_has_ldpte)
			UASM_i_MFC0(p, ptr, C0_PWBASE);
		अन्यथा
			UASM_i_MFC0(p, ptr, c0_kscratch(), pgd_reg);
	पूर्ण अन्यथा अणु
#अगर defined(CONFIG_MIPS_PGD_C0_CONTEXT)
		/*
		 * &pgd << 11 stored in CONTEXT [23..63].
		 */
		UASM_i_MFC0(p, ptr, C0_CONTEXT);

		/* Clear lower 23 bits of context. */
		uयंत्र_i_dins(p, ptr, 0, 0, 23);

		/* insert bit[63:59] of CAC_BASE पूर्णांकo bit[11:6] of ptr */
		uयंत्र_i_ori(p, ptr, ptr, ((u64)(CAC_BASE) >> 53));
		uयंत्र_i_drotr(p, ptr, ptr, 11);
#या_अगर defined(CONFIG_SMP)
		UASM_i_CPUID_MFC0(p, ptr, SMP_CPUID_REG);
		uयंत्र_i_dsrl_safe(p, ptr, ptr, SMP_CPUID_PTRSHIFT);
		UASM_i_LA_mostly(p, पंचांगp, pgdc);
		uयंत्र_i_daddu(p, ptr, ptr, पंचांगp);
		uयंत्र_i_dmfc0(p, पंचांगp, C0_BADVADDR);
		uयंत्र_i_ld(p, ptr, uयंत्र_rel_lo(pgdc), ptr);
#अन्यथा
		UASM_i_LA_mostly(p, ptr, pgdc);
		uयंत्र_i_ld(p, ptr, uयंत्र_rel_lo(pgdc), ptr);
#पूर्ण_अगर
	पूर्ण

	uयंत्र_l_vदो_स्मृति_करोne(l, *p);

	/* get pgd offset in bytes */
	uयंत्र_i_dsrl_safe(p, पंचांगp, पंचांगp, PGसूची_SHIFT - 3);

	uयंत्र_i_andi(p, पंचांगp, पंचांगp, (PTRS_PER_PGD - 1)<<3);
	uयंत्र_i_daddu(p, ptr, ptr, पंचांगp); /* add in pgd offset */
#अगर_अघोषित __PAGETABLE_PUD_FOLDED
	uयंत्र_i_dmfc0(p, पंचांगp, C0_BADVADDR); /* get faulting address */
	uयंत्र_i_ld(p, ptr, 0, ptr); /* get pud poपूर्णांकer */
	uयंत्र_i_dsrl_safe(p, पंचांगp, पंचांगp, PUD_SHIFT - 3); /* get pud offset in bytes */
	uयंत्र_i_andi(p, पंचांगp, पंचांगp, (PTRS_PER_PUD - 1) << 3);
	uयंत्र_i_daddu(p, ptr, ptr, पंचांगp); /* add in pud offset */
#पूर्ण_अगर
#अगर_अघोषित __PAGETABLE_PMD_FOLDED
	uयंत्र_i_dmfc0(p, पंचांगp, C0_BADVADDR); /* get faulting address */
	uयंत्र_i_ld(p, ptr, 0, ptr); /* get pmd poपूर्णांकer */
	uयंत्र_i_dsrl_safe(p, पंचांगp, पंचांगp, PMD_SHIFT-3); /* get pmd offset in bytes */
	uयंत्र_i_andi(p, पंचांगp, पंचांगp, (PTRS_PER_PMD - 1)<<3);
	uयंत्र_i_daddu(p, ptr, ptr, पंचांगp); /* add in pmd offset */
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL_GPL(build_get_pmde64);

/*
 * BVADDR is the faulting address, PTR is scratch.
 * PTR will hold the pgd क्रम vदो_स्मृति.
 */
अटल व्योम
build_get_pgd_vदो_स्मृति64(u32 **p, काष्ठा uयंत्र_label **l, काष्ठा uयंत्र_reloc **r,
			अचिन्हित पूर्णांक bvaddr, अचिन्हित पूर्णांक ptr,
			क्रमागत vदो_स्मृति64_mode mode)
अणु
	दीर्घ swpd = (दीर्घ)swapper_pg_dir;
	पूर्णांक single_insn_swpd;
	पूर्णांक did_vदो_स्मृति_branch = 0;

	single_insn_swpd = uयंत्र_in_compat_space_p(swpd) && !uयंत्र_rel_lo(swpd);

	uयंत्र_l_vदो_स्मृति(l, *p);

	अगर (mode != not_refill && check_क्रम_high_segbits) अणु
		अगर (single_insn_swpd) अणु
			uयंत्र_il_bltz(p, r, bvaddr, label_vदो_स्मृति_करोne);
			uयंत्र_i_lui(p, ptr, uयंत्र_rel_hi(swpd));
			did_vदो_स्मृति_branch = 1;
			/* fall through */
		पूर्ण अन्यथा अणु
			uयंत्र_il_bgez(p, r, bvaddr, label_large_segbits_fault);
		पूर्ण
	पूर्ण
	अगर (!did_vदो_स्मृति_branch) अणु
		अगर (single_insn_swpd) अणु
			uयंत्र_il_b(p, r, label_vदो_स्मृति_करोne);
			uयंत्र_i_lui(p, ptr, uयंत्र_rel_hi(swpd));
		पूर्ण अन्यथा अणु
			UASM_i_LA_mostly(p, ptr, swpd);
			uयंत्र_il_b(p, r, label_vदो_स्मृति_करोne);
			अगर (uयंत्र_in_compat_space_p(swpd))
				uयंत्र_i_addiu(p, ptr, ptr, uयंत्र_rel_lo(swpd));
			अन्यथा
				uयंत्र_i_daddiu(p, ptr, ptr, uयंत्र_rel_lo(swpd));
		पूर्ण
	पूर्ण
	अगर (mode != not_refill && check_क्रम_high_segbits) अणु
		uयंत्र_l_large_segbits_fault(l, *p);

		अगर (mode == refill_scratch && scratch_reg >= 0)
			uयंत्र_i_ehb(p);

		/*
		 * We get here अगर we are an xsseg address, or अगर we are
		 * an xuseg address above (PGसूची_SHIFT+PGसूची_BITS) boundary.
		 *
		 * Ignoring xsseg (assume disabled so would generate
		 * (address errors?), the only reमुख्यing possibility
		 * is the upper xuseg addresses.  On processors with
		 * TLB_SEGBITS <= PGसूची_SHIFT+PGसूची_BITS, these
		 * addresses would have taken an address error. We try
		 * to mimic that here by taking a load/istream page
		 * fault.
		 */
		अगर (IS_ENABLED(CONFIG_CPU_LOONGSON3_WORKAROUNDS))
			uयंत्र_i_sync(p, 0);
		UASM_i_LA(p, ptr, (अचिन्हित दीर्घ)tlb_करो_page_fault_0);
		uयंत्र_i_jr(p, ptr);

		अगर (mode == refill_scratch) अणु
			अगर (scratch_reg >= 0)
				UASM_i_MFC0(p, 1, c0_kscratch(), scratch_reg);
			अन्यथा
				UASM_i_LW(p, 1, scratchpad_offset(0), 0);
		पूर्ण अन्यथा अणु
			uयंत्र_i_nop(p);
		पूर्ण
	पूर्ण
पूर्ण

#अन्यथा /* !CONFIG_64BIT */

/*
 * TMP and PTR are scratch.
 * TMP will be clobbered, PTR will hold the pgd entry.
 */
व्योम build_get_pgde32(u32 **p, अचिन्हित पूर्णांक पंचांगp, अचिन्हित पूर्णांक ptr)
अणु
	अगर (pgd_reg != -1) अणु
		/* pgd is in pgd_reg */
		uयंत्र_i_mfc0(p, ptr, c0_kscratch(), pgd_reg);
		uयंत्र_i_mfc0(p, पंचांगp, C0_BADVADDR); /* get faulting address */
	पूर्ण अन्यथा अणु
		दीर्घ pgdc = (दीर्घ)pgd_current;

		/* 32 bit SMP has smp_processor_id() stored in CONTEXT. */
#अगर_घोषित CONFIG_SMP
		uयंत्र_i_mfc0(p, ptr, SMP_CPUID_REG);
		UASM_i_LA_mostly(p, पंचांगp, pgdc);
		uयंत्र_i_srl(p, ptr, ptr, SMP_CPUID_PTRSHIFT);
		uयंत्र_i_addu(p, ptr, पंचांगp, ptr);
#अन्यथा
		UASM_i_LA_mostly(p, ptr, pgdc);
#पूर्ण_अगर
		uयंत्र_i_mfc0(p, पंचांगp, C0_BADVADDR); /* get faulting address */
		uयंत्र_i_lw(p, ptr, uयंत्र_rel_lo(pgdc), ptr);
	पूर्ण
	uयंत्र_i_srl(p, पंचांगp, पंचांगp, PGसूची_SHIFT); /* get pgd only bits */
	uयंत्र_i_sll(p, पंचांगp, पंचांगp, PGD_T_LOG2);
	uयंत्र_i_addu(p, ptr, ptr, पंचांगp); /* add in pgd offset */
पूर्ण
EXPORT_SYMBOL_GPL(build_get_pgde32);

#पूर्ण_अगर /* !CONFIG_64BIT */

अटल व्योम build_adjust_context(u32 **p, अचिन्हित पूर्णांक ctx)
अणु
	अचिन्हित पूर्णांक shअगरt = 4 - (PTE_T_LOG2 + 1) + PAGE_SHIFT - 12;
	अचिन्हित पूर्णांक mask = (PTRS_PER_PTE / 2 - 1) << (PTE_T_LOG2 + 1);

	चयन (current_cpu_type()) अणु
	हाल CPU_VR41XX:
	हाल CPU_VR4111:
	हाल CPU_VR4121:
	हाल CPU_VR4122:
	हाल CPU_VR4131:
	हाल CPU_VR4181:
	हाल CPU_VR4181A:
	हाल CPU_VR4133:
		shअगरt += 2;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	अगर (shअगरt)
		UASM_i_SRL(p, ctx, ctx, shअगरt);
	uयंत्र_i_andi(p, ctx, ctx, mask);
पूर्ण

व्योम build_get_ptep(u32 **p, अचिन्हित पूर्णांक पंचांगp, अचिन्हित पूर्णांक ptr)
अणु
	/*
	 * Bug workaround क्रम the Nevada. It seems as अगर under certain
	 * circumstances the move from cp0_context might produce a
	 * bogus result when the mfc0 inकाष्ठाion and its consumer are
	 * in a dअगरferent cacheline or a load inकाष्ठाion, probably any
	 * memory reference, is between them.
	 */
	चयन (current_cpu_type()) अणु
	हाल CPU_NEVADA:
		UASM_i_LW(p, ptr, 0, ptr);
		GET_CONTEXT(p, पंचांगp); /* get context reg */
		अवरोध;

	शेष:
		GET_CONTEXT(p, पंचांगp); /* get context reg */
		UASM_i_LW(p, ptr, 0, ptr);
		अवरोध;
	पूर्ण

	build_adjust_context(p, पंचांगp);
	UASM_i_ADDU(p, ptr, ptr, पंचांगp); /* add in offset */
पूर्ण
EXPORT_SYMBOL_GPL(build_get_ptep);

व्योम build_update_entries(u32 **p, अचिन्हित पूर्णांक पंचांगp, अचिन्हित पूर्णांक ptep)
अणु
	पूर्णांक pte_off_even = 0;
	पूर्णांक pte_off_odd = माप(pte_t);

#अगर defined(CONFIG_CPU_MIPS32) && defined(CONFIG_PHYS_ADDR_T_64BIT)
	/* The low 32 bits of EntryLo is stored in pte_high */
	pte_off_even += दुरत्व(pte_t, pte_high);
	pte_off_odd += दुरत्व(pte_t, pte_high);
#पूर्ण_अगर

	अगर (IS_ENABLED(CONFIG_XPA)) अणु
		uयंत्र_i_lw(p, पंचांगp, pte_off_even, ptep); /* even pte */
		UASM_i_ROTR(p, पंचांगp, पंचांगp, ilog2(_PAGE_GLOBAL));
		UASM_i_MTC0(p, पंचांगp, C0_ENTRYLO0);

		अगर (cpu_has_xpa && !mips_xpa_disabled) अणु
			uयंत्र_i_lw(p, पंचांगp, 0, ptep);
			uयंत्र_i_ext(p, पंचांगp, पंचांगp, 0, 24);
			uयंत्र_i_mthc0(p, पंचांगp, C0_ENTRYLO0);
		पूर्ण

		uयंत्र_i_lw(p, पंचांगp, pte_off_odd, ptep); /* odd pte */
		UASM_i_ROTR(p, पंचांगp, पंचांगp, ilog2(_PAGE_GLOBAL));
		UASM_i_MTC0(p, पंचांगp, C0_ENTRYLO1);

		अगर (cpu_has_xpa && !mips_xpa_disabled) अणु
			uयंत्र_i_lw(p, पंचांगp, माप(pte_t), ptep);
			uयंत्र_i_ext(p, पंचांगp, पंचांगp, 0, 24);
			uयंत्र_i_mthc0(p, पंचांगp, C0_ENTRYLO1);
		पूर्ण
		वापस;
	पूर्ण

	UASM_i_LW(p, पंचांगp, pte_off_even, ptep); /* get even pte */
	UASM_i_LW(p, ptep, pte_off_odd, ptep); /* get odd pte */
	अगर (r45k_bvahwbug())
		build_tlb_probe_entry(p);
	build_convert_pte_to_entrylo(p, पंचांगp);
	अगर (r4k_250MHZhwbug())
		UASM_i_MTC0(p, 0, C0_ENTRYLO0);
	UASM_i_MTC0(p, पंचांगp, C0_ENTRYLO0); /* load it */
	build_convert_pte_to_entrylo(p, ptep);
	अगर (r45k_bvahwbug())
		uयंत्र_i_mfc0(p, पंचांगp, C0_INDEX);
	अगर (r4k_250MHZhwbug())
		UASM_i_MTC0(p, 0, C0_ENTRYLO1);
	UASM_i_MTC0(p, ptep, C0_ENTRYLO1); /* load it */
पूर्ण
EXPORT_SYMBOL_GPL(build_update_entries);

काष्ठा mips_huge_tlb_info अणु
	पूर्णांक huge_pte;
	पूर्णांक restore_scratch;
	bool need_reload_pte;
पूर्ण;

अटल काष्ठा mips_huge_tlb_info
build_fast_tlb_refill_handler (u32 **p, काष्ठा uयंत्र_label **l,
			       काष्ठा uयंत्र_reloc **r, अचिन्हित पूर्णांक पंचांगp,
			       अचिन्हित पूर्णांक ptr, पूर्णांक c0_scratch_reg)
अणु
	काष्ठा mips_huge_tlb_info rv;
	अचिन्हित पूर्णांक even, odd;
	पूर्णांक vदो_स्मृति_branch_delay_filled = 0;
	स्थिर पूर्णांक scratch = 1; /* Our extra working रेजिस्टर */

	rv.huge_pte = scratch;
	rv.restore_scratch = 0;
	rv.need_reload_pte = false;

	अगर (check_क्रम_high_segbits) अणु
		UASM_i_MFC0(p, पंचांगp, C0_BADVADDR);

		अगर (pgd_reg != -1)
			UASM_i_MFC0(p, ptr, c0_kscratch(), pgd_reg);
		अन्यथा
			UASM_i_MFC0(p, ptr, C0_CONTEXT);

		अगर (c0_scratch_reg >= 0)
			UASM_i_MTC0(p, scratch, c0_kscratch(), c0_scratch_reg);
		अन्यथा
			UASM_i_SW(p, scratch, scratchpad_offset(0), 0);

		uयंत्र_i_dsrl_safe(p, scratch, पंचांगp,
				 PGसूची_SHIFT + PGD_ORDER + PAGE_SHIFT - 3);
		uयंत्र_il_bnez(p, r, scratch, label_vदो_स्मृति);

		अगर (pgd_reg == -1) अणु
			vदो_स्मृति_branch_delay_filled = 1;
			/* Clear lower 23 bits of context. */
			uयंत्र_i_dins(p, ptr, 0, 0, 23);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (pgd_reg != -1)
			UASM_i_MFC0(p, ptr, c0_kscratch(), pgd_reg);
		अन्यथा
			UASM_i_MFC0(p, ptr, C0_CONTEXT);

		UASM_i_MFC0(p, पंचांगp, C0_BADVADDR);

		अगर (c0_scratch_reg >= 0)
			UASM_i_MTC0(p, scratch, c0_kscratch(), c0_scratch_reg);
		अन्यथा
			UASM_i_SW(p, scratch, scratchpad_offset(0), 0);

		अगर (pgd_reg == -1)
			/* Clear lower 23 bits of context. */
			uयंत्र_i_dins(p, ptr, 0, 0, 23);

		uयंत्र_il_bltz(p, r, पंचांगp, label_vदो_स्मृति);
	पूर्ण

	अगर (pgd_reg == -1) अणु
		vदो_स्मृति_branch_delay_filled = 1;
		/* insert bit[63:59] of CAC_BASE पूर्णांकo bit[11:6] of ptr */
		uयंत्र_i_ori(p, ptr, ptr, ((u64)(CAC_BASE) >> 53));

		uयंत्र_i_drotr(p, ptr, ptr, 11);
	पूर्ण

#अगर_घोषित __PAGETABLE_PMD_FOLDED
#घोषणा LOC_PTEP scratch
#अन्यथा
#घोषणा LOC_PTEP ptr
#पूर्ण_अगर

	अगर (!vदो_स्मृति_branch_delay_filled)
		/* get pgd offset in bytes */
		uयंत्र_i_dsrl_safe(p, scratch, पंचांगp, PGसूची_SHIFT - 3);

	uयंत्र_l_vदो_स्मृति_करोne(l, *p);

	/*
	 *			   पंचांगp		ptr
	 * fall-through हाल =	 badvaddr  *pgd_current
	 * vदो_स्मृति हाल	     =	 badvaddr  swapper_pg_dir
	 */

	अगर (vदो_स्मृति_branch_delay_filled)
		/* get pgd offset in bytes */
		uयंत्र_i_dsrl_safe(p, scratch, पंचांगp, PGसूची_SHIFT - 3);

#अगर_घोषित __PAGETABLE_PMD_FOLDED
	GET_CONTEXT(p, पंचांगp); /* get context reg */
#पूर्ण_अगर
	uयंत्र_i_andi(p, scratch, scratch, (PTRS_PER_PGD - 1) << 3);

	अगर (use_lwx_insns()) अणु
		UASM_i_LWX(p, LOC_PTEP, scratch, ptr);
	पूर्ण अन्यथा अणु
		uयंत्र_i_daddu(p, ptr, ptr, scratch); /* add in pgd offset */
		uयंत्र_i_ld(p, LOC_PTEP, 0, ptr); /* get pmd poपूर्णांकer */
	पूर्ण

#अगर_अघोषित __PAGETABLE_PUD_FOLDED
	/* get pud offset in bytes */
	uयंत्र_i_dsrl_safe(p, scratch, पंचांगp, PUD_SHIFT - 3);
	uयंत्र_i_andi(p, scratch, scratch, (PTRS_PER_PUD - 1) << 3);

	अगर (use_lwx_insns()) अणु
		UASM_i_LWX(p, ptr, scratch, ptr);
	पूर्ण अन्यथा अणु
		uयंत्र_i_daddu(p, ptr, ptr, scratch); /* add in pmd offset */
		UASM_i_LW(p, ptr, 0, ptr);
	पूर्ण
	/* ptr contains a poपूर्णांकer to PMD entry */
	/* पंचांगp contains the address */
#पूर्ण_अगर

#अगर_अघोषित __PAGETABLE_PMD_FOLDED
	/* get pmd offset in bytes */
	uयंत्र_i_dsrl_safe(p, scratch, पंचांगp, PMD_SHIFT - 3);
	uयंत्र_i_andi(p, scratch, scratch, (PTRS_PER_PMD - 1) << 3);
	GET_CONTEXT(p, पंचांगp); /* get context reg */

	अगर (use_lwx_insns()) अणु
		UASM_i_LWX(p, scratch, scratch, ptr);
	पूर्ण अन्यथा अणु
		uयंत्र_i_daddu(p, ptr, ptr, scratch); /* add in pmd offset */
		UASM_i_LW(p, scratch, 0, ptr);
	पूर्ण
#पूर्ण_अगर
	/* Adjust the context during the load latency. */
	build_adjust_context(p, पंचांगp);

#अगर_घोषित CONFIG_MIPS_HUGE_TLB_SUPPORT
	uयंत्र_il_bbit1(p, r, scratch, ilog2(_PAGE_HUGE), label_tlb_huge_update);
	/*
	 * The in the LWX हाल we करोn't want to करो the load in the
	 * delay slot.	It cannot issue in the same cycle and may be
	 * speculative and unneeded.
	 */
	अगर (use_lwx_insns())
		uयंत्र_i_nop(p);
#पूर्ण_अगर /* CONFIG_MIPS_HUGE_TLB_SUPPORT */


	/* build_update_entries */
	अगर (use_lwx_insns()) अणु
		even = ptr;
		odd = पंचांगp;
		UASM_i_LWX(p, even, scratch, पंचांगp);
		UASM_i_ADDIU(p, पंचांगp, पंचांगp, माप(pte_t));
		UASM_i_LWX(p, odd, scratch, पंचांगp);
	पूर्ण अन्यथा अणु
		UASM_i_ADDU(p, ptr, scratch, पंचांगp); /* add in offset */
		even = पंचांगp;
		odd = ptr;
		UASM_i_LW(p, even, 0, ptr); /* get even pte */
		UASM_i_LW(p, odd, माप(pte_t), ptr); /* get odd pte */
	पूर्ण
	अगर (cpu_has_rixi) अणु
		uयंत्र_i_drotr(p, even, even, ilog2(_PAGE_GLOBAL));
		UASM_i_MTC0(p, even, C0_ENTRYLO0); /* load it */
		uयंत्र_i_drotr(p, odd, odd, ilog2(_PAGE_GLOBAL));
	पूर्ण अन्यथा अणु
		uयंत्र_i_dsrl_safe(p, even, even, ilog2(_PAGE_GLOBAL));
		UASM_i_MTC0(p, even, C0_ENTRYLO0); /* load it */
		uयंत्र_i_dsrl_safe(p, odd, odd, ilog2(_PAGE_GLOBAL));
	पूर्ण
	UASM_i_MTC0(p, odd, C0_ENTRYLO1); /* load it */

	अगर (c0_scratch_reg >= 0) अणु
		uयंत्र_i_ehb(p);
		UASM_i_MFC0(p, scratch, c0_kscratch(), c0_scratch_reg);
		build_tlb_ग_लिखो_entry(p, l, r, tlb_अक्रमom);
		uयंत्र_l_leave(l, *p);
		rv.restore_scratch = 1;
	पूर्ण अन्यथा अगर (PAGE_SHIFT == 14 || PAGE_SHIFT == 13)  अणु
		build_tlb_ग_लिखो_entry(p, l, r, tlb_अक्रमom);
		uयंत्र_l_leave(l, *p);
		UASM_i_LW(p, scratch, scratchpad_offset(0), 0);
	पूर्ण अन्यथा अणु
		UASM_i_LW(p, scratch, scratchpad_offset(0), 0);
		build_tlb_ग_लिखो_entry(p, l, r, tlb_अक्रमom);
		uयंत्र_l_leave(l, *p);
		rv.restore_scratch = 1;
	पूर्ण

	uयंत्र_i_eret(p); /* वापस from trap */

	वापस rv;
पूर्ण

/*
 * For a 64-bit kernel, we are using the 64-bit XTLB refill exception
 * because EXL == 0.  If we wrap, we can also use the 32 inकाष्ठाion
 * slots beक्रमe the XTLB refill exception handler which beदीर्घ to the
 * unused TLB refill exception.
 */
#घोषणा MIPS64_REFILL_INSNS 32

अटल व्योम build_r4000_tlb_refill_handler(व्योम)
अणु
	u32 *p = tlb_handler;
	काष्ठा uयंत्र_label *l = labels;
	काष्ठा uयंत्र_reloc *r = relocs;
	u32 *f;
	अचिन्हित पूर्णांक final_len;
	काष्ठा mips_huge_tlb_info htlb_info __maybe_unused;
	क्रमागत vदो_स्मृति64_mode vदो_स्मृति_mode __maybe_unused;

	स_रखो(tlb_handler, 0, माप(tlb_handler));
	स_रखो(labels, 0, माप(labels));
	स_रखो(relocs, 0, माप(relocs));
	स_रखो(final_handler, 0, माप(final_handler));

	अगर (IS_ENABLED(CONFIG_64BIT) && (scratch_reg >= 0 || scratchpad_available()) && use_bbit_insns()) अणु
		htlb_info = build_fast_tlb_refill_handler(&p, &l, &r, K0, K1,
							  scratch_reg);
		vदो_स्मृति_mode = refill_scratch;
	पूर्ण अन्यथा अणु
		htlb_info.huge_pte = K0;
		htlb_info.restore_scratch = 0;
		htlb_info.need_reload_pte = true;
		vदो_स्मृति_mode = refill_noscratch;
		/*
		 * create the plain linear handler
		 */
		अगर (bcm1250_m3_war()) अणु
			अचिन्हित पूर्णांक segbits = 44;

			uयंत्र_i_dmfc0(&p, K0, C0_BADVADDR);
			uयंत्र_i_dmfc0(&p, K1, C0_ENTRYHI);
			uयंत्र_i_xor(&p, K0, K0, K1);
			uयंत्र_i_dsrl_safe(&p, K1, K0, 62);
			uयंत्र_i_dsrl_safe(&p, K0, K0, 12 + 1);
			uयंत्र_i_dsll_safe(&p, K0, K0, 64 + 12 + 1 - segbits);
			uयंत्र_i_or(&p, K0, K0, K1);
			uयंत्र_il_bnez(&p, &r, K0, label_leave);
			/* No need क्रम uयंत्र_i_nop */
		पूर्ण

#अगर_घोषित CONFIG_64BIT
		build_get_pmde64(&p, &l, &r, K0, K1); /* get pmd in K1 */
#अन्यथा
		build_get_pgde32(&p, K0, K1); /* get pgd in K1 */
#पूर्ण_अगर

#अगर_घोषित CONFIG_MIPS_HUGE_TLB_SUPPORT
		build_is_huge_pte(&p, &r, K0, K1, label_tlb_huge_update);
#पूर्ण_अगर

		build_get_ptep(&p, K0, K1);
		build_update_entries(&p, K0, K1);
		build_tlb_ग_लिखो_entry(&p, &l, &r, tlb_अक्रमom);
		uयंत्र_l_leave(&l, p);
		uयंत्र_i_eret(&p); /* वापस from trap */
	पूर्ण
#अगर_घोषित CONFIG_MIPS_HUGE_TLB_SUPPORT
	uयंत्र_l_tlb_huge_update(&l, p);
	अगर (htlb_info.need_reload_pte)
		UASM_i_LW(&p, htlb_info.huge_pte, 0, K1);
	build_huge_update_entries(&p, htlb_info.huge_pte, K1);
	build_huge_tlb_ग_लिखो_entry(&p, &l, &r, K0, tlb_अक्रमom,
				   htlb_info.restore_scratch);
#पूर्ण_अगर

#अगर_घोषित CONFIG_64BIT
	build_get_pgd_vदो_स्मृति64(&p, &l, &r, K0, K1, vदो_स्मृति_mode);
#पूर्ण_अगर

	/*
	 * Overflow check: For the 64bit handler, we need at least one
	 * मुक्त inकाष्ठाion slot क्रम the wrap-around branch. In worst
	 * हाल, अगर the पूर्णांकended insertion poपूर्णांक is a delay slot, we
	 * need three, with the second nop'ed and the third being
	 * unused.
	 */
	चयन (boot_cpu_type()) अणु
	शेष:
		अगर (माप(दीर्घ) == 4) अणु
	हाल CPU_LOONGSON2EF:
		/* Loongson2 ebase is dअगरferent than r4k, we have more space */
			अगर ((p - tlb_handler) > 64)
				panic("TLB refill handler space exceeded");
			/*
			 * Now fold the handler in the TLB refill handler space.
			 */
			f = final_handler;
			/* Simplest हाल, just copy the handler. */
			uयंत्र_copy_handler(relocs, labels, tlb_handler, p, f);
			final_len = p - tlb_handler;
			अवरोध;
		पूर्ण अन्यथा अणु
			अगर (((p - tlb_handler) > (MIPS64_REFILL_INSNS * 2) - 1)
			    || (((p - tlb_handler) > (MIPS64_REFILL_INSNS * 2) - 3)
				&& uयंत्र_insn_has_bdelay(relocs,
							tlb_handler + MIPS64_REFILL_INSNS - 3)))
				panic("TLB refill handler space exceeded");
			/*
			 * Now fold the handler in the TLB refill handler space.
			 */
			f = final_handler + MIPS64_REFILL_INSNS;
			अगर ((p - tlb_handler) <= MIPS64_REFILL_INSNS) अणु
				/* Just copy the handler. */
				uयंत्र_copy_handler(relocs, labels, tlb_handler, p, f);
				final_len = p - tlb_handler;
			पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_MIPS_HUGE_TLB_SUPPORT
				स्थिर क्रमागत label_id ls = label_tlb_huge_update;
#अन्यथा
				स्थिर क्रमागत label_id ls = label_vदो_स्मृति;
#पूर्ण_अगर
				u32 *split;
				पूर्णांक ov = 0;
				पूर्णांक i;

				क्रम (i = 0; i < ARRAY_SIZE(labels) && labels[i].lab != ls; i++)
					;
				BUG_ON(i == ARRAY_SIZE(labels));
				split = labels[i].addr;

				/*
				 * See अगर we have overflown one way or the other.
				 */
				अगर (split > tlb_handler + MIPS64_REFILL_INSNS ||
				    split < p - MIPS64_REFILL_INSNS)
					ov = 1;

				अगर (ov) अणु
					/*
					 * Split two inकाष्ठाions beक्रमe the end.  One
					 * क्रम the branch and one क्रम the inकाष्ठाion
					 * in the delay slot.
					 */
					split = tlb_handler + MIPS64_REFILL_INSNS - 2;

					/*
					 * If the branch would fall in a delay slot,
					 * we must back up an additional inकाष्ठाion
					 * so that it is no दीर्घer in a delay slot.
					 */
					अगर (uयंत्र_insn_has_bdelay(relocs, split - 1))
						split--;
				पूर्ण
				/* Copy first part of the handler. */
				uयंत्र_copy_handler(relocs, labels, tlb_handler, split, f);
				f += split - tlb_handler;

				अगर (ov) अणु
					/* Insert branch. */
					uयंत्र_l_split(&l, final_handler);
					uयंत्र_il_b(&f, &r, label_split);
					अगर (uयंत्र_insn_has_bdelay(relocs, split))
						uयंत्र_i_nop(&f);
					अन्यथा अणु
						uयंत्र_copy_handler(relocs, labels,
								  split, split + 1, f);
						uयंत्र_move_labels(labels, f, f + 1, -1);
						f++;
						split++;
					पूर्ण
				पूर्ण

				/* Copy the rest of the handler. */
				uयंत्र_copy_handler(relocs, labels, split, p, final_handler);
				final_len = (f - (final_handler + MIPS64_REFILL_INSNS)) +
					    (p - split);
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण

	uयंत्र_resolve_relocs(relocs, labels);
	pr_debug("Wrote TLB refill handler (%u instructions).\n",
		 final_len);

	स_नकल((व्योम *)ebase, final_handler, 0x100);
	local_flush_icache_range(ebase, ebase + 0x100);
	dump_handler("r4000_tlb_refill", (u32 *)ebase, (u32 *)(ebase + 0x100));
पूर्ण

अटल व्योम setup_pw(व्योम)
अणु
	अचिन्हित पूर्णांक pwctl;
	अचिन्हित दीर्घ pgd_i, pgd_w;
#अगर_अघोषित __PAGETABLE_PMD_FOLDED
	अचिन्हित दीर्घ pmd_i, pmd_w;
#पूर्ण_अगर
	अचिन्हित दीर्घ pt_i, pt_w;
	अचिन्हित दीर्घ pte_i, pte_w;
#अगर_घोषित CONFIG_MIPS_HUGE_TLB_SUPPORT
	अचिन्हित दीर्घ psn;

	psn = ilog2(_PAGE_HUGE);     /* bit used to indicate huge page */
#पूर्ण_अगर
	pgd_i = PGसूची_SHIFT;  /* 1st level PGD */
#अगर_अघोषित __PAGETABLE_PMD_FOLDED
	pgd_w = PGसूची_SHIFT - PMD_SHIFT + PGD_ORDER;

	pmd_i = PMD_SHIFT;    /* 2nd level PMD */
	pmd_w = PMD_SHIFT - PAGE_SHIFT;
#अन्यथा
	pgd_w = PGसूची_SHIFT - PAGE_SHIFT + PGD_ORDER;
#पूर्ण_अगर

	pt_i  = PAGE_SHIFT;    /* 3rd level PTE */
	pt_w  = PAGE_SHIFT - 3;

	pte_i = ilog2(_PAGE_GLOBAL);
	pte_w = 0;
	pwctl = 1 << 30; /* Set PWDirExt */

#अगर_अघोषित __PAGETABLE_PMD_FOLDED
	ग_लिखो_c0_pwfield(pgd_i << 24 | pmd_i << 12 | pt_i << 6 | pte_i);
	ग_लिखो_c0_pwsize(1 << 30 | pgd_w << 24 | pmd_w << 12 | pt_w << 6 | pte_w);
#अन्यथा
	ग_लिखो_c0_pwfield(pgd_i << 24 | pt_i << 6 | pte_i);
	ग_लिखो_c0_pwsize(1 << 30 | pgd_w << 24 | pt_w << 6 | pte_w);
#पूर्ण_अगर

#अगर_घोषित CONFIG_MIPS_HUGE_TLB_SUPPORT
	pwctl |= (1 << 6 | psn);
#पूर्ण_अगर
	ग_लिखो_c0_pwctl(pwctl);
	ग_लिखो_c0_kpgd((दीर्घ)swapper_pg_dir);
	kscratch_used_mask |= (1 << 7); /* KScratch6 is used क्रम KPGD */
पूर्ण

अटल व्योम build_loongson3_tlb_refill_handler(व्योम)
अणु
	u32 *p = tlb_handler;
	काष्ठा uयंत्र_label *l = labels;
	काष्ठा uयंत्र_reloc *r = relocs;

	स_रखो(labels, 0, माप(labels));
	स_रखो(relocs, 0, माप(relocs));
	स_रखो(tlb_handler, 0, माप(tlb_handler));

	अगर (check_क्रम_high_segbits) अणु
		uयंत्र_i_dmfc0(&p, K0, C0_BADVADDR);
		uयंत्र_i_dsrl_safe(&p, K1, K0, PGसूची_SHIFT + PGD_ORDER + PAGE_SHIFT - 3);
		uयंत्र_il_beqz(&p, &r, K1, label_vदो_स्मृति);
		uयंत्र_i_nop(&p);

		uयंत्र_il_bgez(&p, &r, K0, label_large_segbits_fault);
		uयंत्र_i_nop(&p);
		uयंत्र_l_vदो_स्मृति(&l, p);
	पूर्ण

	uयंत्र_i_dmfc0(&p, K1, C0_PGD);

	uयंत्र_i_lddir(&p, K0, K1, 3);  /* global page dir */
#अगर_अघोषित __PAGETABLE_PMD_FOLDED
	uयंत्र_i_lddir(&p, K1, K0, 1);  /* middle page dir */
#पूर्ण_अगर
	uयंत्र_i_ldpte(&p, K1, 0);      /* even */
	uयंत्र_i_ldpte(&p, K1, 1);      /* odd */
	uयंत्र_i_tlbwr(&p);

	/* restore page mask */
	अगर (PM_DEFAULT_MASK >> 16) अणु
		uयंत्र_i_lui(&p, K0, PM_DEFAULT_MASK >> 16);
		uयंत्र_i_ori(&p, K0, K0, PM_DEFAULT_MASK & 0xffff);
		uयंत्र_i_mtc0(&p, K0, C0_PAGEMASK);
	पूर्ण अन्यथा अगर (PM_DEFAULT_MASK) अणु
		uयंत्र_i_ori(&p, K0, 0, PM_DEFAULT_MASK);
		uयंत्र_i_mtc0(&p, K0, C0_PAGEMASK);
	पूर्ण अन्यथा अणु
		uयंत्र_i_mtc0(&p, 0, C0_PAGEMASK);
	पूर्ण

	uयंत्र_i_eret(&p);

	अगर (check_क्रम_high_segbits) अणु
		uयंत्र_l_large_segbits_fault(&l, p);
		UASM_i_LA(&p, K1, (अचिन्हित दीर्घ)tlb_करो_page_fault_0);
		uयंत्र_i_jr(&p, K1);
		uयंत्र_i_nop(&p);
	पूर्ण

	uयंत्र_resolve_relocs(relocs, labels);
	स_नकल((व्योम *)(ebase + 0x80), tlb_handler, 0x80);
	local_flush_icache_range(ebase + 0x80, ebase + 0x100);
	dump_handler("loongson3_tlb_refill",
		     (u32 *)(ebase + 0x80), (u32 *)(ebase + 0x100));
पूर्ण

अटल व्योम build_setup_pgd(व्योम)
अणु
	स्थिर पूर्णांक a0 = 4;
	स्थिर पूर्णांक __maybe_unused a1 = 5;
	स्थिर पूर्णांक __maybe_unused a2 = 6;
	u32 *p = (u32 *)msk_isa16_mode((uदीर्घ)tlbmiss_handler_setup_pgd);
#अगर_अघोषित CONFIG_MIPS_PGD_C0_CONTEXT
	दीर्घ pgdc = (दीर्घ)pgd_current;
#पूर्ण_अगर

	स_रखो(p, 0, tlbmiss_handler_setup_pgd_end - (अक्षर *)p);
	स_रखो(labels, 0, माप(labels));
	स_रखो(relocs, 0, माप(relocs));
	pgd_reg = allocate_kscratch();
#अगर_घोषित CONFIG_MIPS_PGD_C0_CONTEXT
	अगर (pgd_reg == -1) अणु
		काष्ठा uयंत्र_label *l = labels;
		काष्ठा uयंत्र_reloc *r = relocs;

		/* PGD << 11 in c0_Context */
		/*
		 * If it is a ckseg0 address, convert to a physical
		 * address.  Shअगरting right by 29 and adding 4 will
		 * result in zero क्रम these addresses.
		 *
		 */
		UASM_i_SRA(&p, a1, a0, 29);
		UASM_i_ADDIU(&p, a1, a1, 4);
		uयंत्र_il_bnez(&p, &r, a1, label_tlbl_goaround1);
		uयंत्र_i_nop(&p);
		uयंत्र_i_dinsm(&p, a0, 0, 29, 64 - 29);
		uयंत्र_l_tlbl_goaround1(&l, p);
		UASM_i_SLL(&p, a0, a0, 11);
		UASM_i_MTC0(&p, a0, C0_CONTEXT);
		uयंत्र_i_jr(&p, 31);
		uयंत्र_i_ehb(&p);
	पूर्ण अन्यथा अणु
		/* PGD in c0_KScratch */
		अगर (cpu_has_ldpte)
			UASM_i_MTC0(&p, a0, C0_PWBASE);
		अन्यथा
			UASM_i_MTC0(&p, a0, c0_kscratch(), pgd_reg);
		uयंत्र_i_jr(&p, 31);
		uयंत्र_i_ehb(&p);
	पूर्ण
#अन्यथा
#अगर_घोषित CONFIG_SMP
	/* Save PGD to pgd_current[smp_processor_id()] */
	UASM_i_CPUID_MFC0(&p, a1, SMP_CPUID_REG);
	UASM_i_SRL_SAFE(&p, a1, a1, SMP_CPUID_PTRSHIFT);
	UASM_i_LA_mostly(&p, a2, pgdc);
	UASM_i_ADDU(&p, a2, a2, a1);
	UASM_i_SW(&p, a0, uयंत्र_rel_lo(pgdc), a2);
#अन्यथा
	UASM_i_LA_mostly(&p, a2, pgdc);
	UASM_i_SW(&p, a0, uयंत्र_rel_lo(pgdc), a2);
#पूर्ण_अगर /* SMP */

	/* अगर pgd_reg is allocated, save PGD also to scratch रेजिस्टर */
	अगर (pgd_reg != -1) अणु
		UASM_i_MTC0(&p, a0, c0_kscratch(), pgd_reg);
		uयंत्र_i_jr(&p, 31);
		uयंत्र_i_ehb(&p);
	पूर्ण अन्यथा अणु
		uयंत्र_i_jr(&p, 31);
		uयंत्र_i_nop(&p);
	पूर्ण
#पूर्ण_अगर
	अगर (p >= (u32 *)tlbmiss_handler_setup_pgd_end)
		panic("tlbmiss_handler_setup_pgd space exceeded");

	uयंत्र_resolve_relocs(relocs, labels);
	pr_debug("Wrote tlbmiss_handler_setup_pgd (%u instructions).\n",
		 (अचिन्हित पूर्णांक)(p - (u32 *)tlbmiss_handler_setup_pgd));

	dump_handler("tlbmiss_handler", tlbmiss_handler_setup_pgd,
					tlbmiss_handler_setup_pgd_end);
पूर्ण

अटल व्योम
iPTE_LW(u32 **p, अचिन्हित पूर्णांक pte, अचिन्हित पूर्णांक ptr)
अणु
#अगर_घोषित CONFIG_SMP
	अगर (IS_ENABLED(CONFIG_CPU_LOONGSON3_WORKAROUNDS))
		uयंत्र_i_sync(p, 0);
# अगरdef CONFIG_PHYS_ADDR_T_64BIT
	अगर (cpu_has_64bits)
		uयंत्र_i_lld(p, pte, 0, ptr);
	अन्यथा
# endअगर
		UASM_i_LL(p, pte, 0, ptr);
#अन्यथा
# अगरdef CONFIG_PHYS_ADDR_T_64BIT
	अगर (cpu_has_64bits)
		uयंत्र_i_ld(p, pte, 0, ptr);
	अन्यथा
# endअगर
		UASM_i_LW(p, pte, 0, ptr);
#पूर्ण_अगर
पूर्ण

अटल व्योम
iPTE_SW(u32 **p, काष्ठा uयंत्र_reloc **r, अचिन्हित पूर्णांक pte, अचिन्हित पूर्णांक ptr,
	अचिन्हित पूर्णांक mode, अचिन्हित पूर्णांक scratch)
अणु
	अचिन्हित पूर्णांक hwmode = mode & (_PAGE_VALID | _PAGE_सूचीTY);
	अचिन्हित पूर्णांक swmode = mode & ~hwmode;

	अगर (IS_ENABLED(CONFIG_XPA) && !cpu_has_64bits) अणु
		uयंत्र_i_lui(p, scratch, swmode >> 16);
		uयंत्र_i_or(p, pte, pte, scratch);
		BUG_ON(swmode & 0xffff);
	पूर्ण अन्यथा अणु
		uयंत्र_i_ori(p, pte, pte, mode);
	पूर्ण

#अगर_घोषित CONFIG_SMP
# अगरdef CONFIG_PHYS_ADDR_T_64BIT
	अगर (cpu_has_64bits)
		uयंत्र_i_scd(p, pte, 0, ptr);
	अन्यथा
# endअगर
		UASM_i_SC(p, pte, 0, ptr);

	अगर (r10000_llsc_war())
		uयंत्र_il_beqzl(p, r, pte, label_smp_pgtable_change);
	अन्यथा
		uयंत्र_il_beqz(p, r, pte, label_smp_pgtable_change);

# अगरdef CONFIG_PHYS_ADDR_T_64BIT
	अगर (!cpu_has_64bits) अणु
		/* no uयंत्र_i_nop needed */
		uयंत्र_i_ll(p, pte, माप(pte_t) / 2, ptr);
		uयंत्र_i_ori(p, pte, pte, hwmode);
		BUG_ON(hwmode & ~0xffff);
		uयंत्र_i_sc(p, pte, माप(pte_t) / 2, ptr);
		uयंत्र_il_beqz(p, r, pte, label_smp_pgtable_change);
		/* no uयंत्र_i_nop needed */
		uयंत्र_i_lw(p, pte, 0, ptr);
	पूर्ण अन्यथा
		uयंत्र_i_nop(p);
# अन्यथा
	uयंत्र_i_nop(p);
# endअगर
#अन्यथा
# अगरdef CONFIG_PHYS_ADDR_T_64BIT
	अगर (cpu_has_64bits)
		uयंत्र_i_sd(p, pte, 0, ptr);
	अन्यथा
# endअगर
		UASM_i_SW(p, pte, 0, ptr);

# अगरdef CONFIG_PHYS_ADDR_T_64BIT
	अगर (!cpu_has_64bits) अणु
		uयंत्र_i_lw(p, pte, माप(pte_t) / 2, ptr);
		uयंत्र_i_ori(p, pte, pte, hwmode);
		BUG_ON(hwmode & ~0xffff);
		uयंत्र_i_sw(p, pte, माप(pte_t) / 2, ptr);
		uयंत्र_i_lw(p, pte, 0, ptr);
	पूर्ण
# endअगर
#पूर्ण_अगर
पूर्ण

/*
 * Check अगर PTE is present, अगर not then jump to LABEL. PTR poपूर्णांकs to
 * the page table where this PTE is located, PTE will be re-loaded
 * with it's original value.
 */
अटल व्योम
build_pte_present(u32 **p, काष्ठा uयंत्र_reloc **r,
		  पूर्णांक pte, पूर्णांक ptr, पूर्णांक scratch, क्रमागत label_id lid)
अणु
	पूर्णांक t = scratch >= 0 ? scratch : pte;
	पूर्णांक cur = pte;

	अगर (cpu_has_rixi) अणु
		अगर (use_bbit_insns()) अणु
			uयंत्र_il_bbit0(p, r, pte, ilog2(_PAGE_PRESENT), lid);
			uयंत्र_i_nop(p);
		पूर्ण अन्यथा अणु
			अगर (_PAGE_PRESENT_SHIFT) अणु
				uयंत्र_i_srl(p, t, cur, _PAGE_PRESENT_SHIFT);
				cur = t;
			पूर्ण
			uयंत्र_i_andi(p, t, cur, 1);
			uयंत्र_il_beqz(p, r, t, lid);
			अगर (pte == t)
				/* You lose the SMP race :-(*/
				iPTE_LW(p, pte, ptr);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (_PAGE_PRESENT_SHIFT) अणु
			uयंत्र_i_srl(p, t, cur, _PAGE_PRESENT_SHIFT);
			cur = t;
		पूर्ण
		uयंत्र_i_andi(p, t, cur,
			(_PAGE_PRESENT | _PAGE_NO_READ) >> _PAGE_PRESENT_SHIFT);
		uयंत्र_i_xori(p, t, t, _PAGE_PRESENT >> _PAGE_PRESENT_SHIFT);
		uयंत्र_il_bnez(p, r, t, lid);
		अगर (pte == t)
			/* You lose the SMP race :-(*/
			iPTE_LW(p, pte, ptr);
	पूर्ण
पूर्ण

/* Make PTE valid, store result in PTR. */
अटल व्योम
build_make_valid(u32 **p, काष्ठा uयंत्र_reloc **r, अचिन्हित पूर्णांक pte,
		 अचिन्हित पूर्णांक ptr, अचिन्हित पूर्णांक scratch)
अणु
	अचिन्हित पूर्णांक mode = _PAGE_VALID | _PAGE_ACCESSED;

	iPTE_SW(p, r, pte, ptr, mode, scratch);
पूर्ण

/*
 * Check अगर PTE can be written to, अगर not branch to LABEL. Regardless
 * restore PTE with value from PTR when करोne.
 */
अटल व्योम
build_pte_writable(u32 **p, काष्ठा uयंत्र_reloc **r,
		   अचिन्हित पूर्णांक pte, अचिन्हित पूर्णांक ptr, पूर्णांक scratch,
		   क्रमागत label_id lid)
अणु
	पूर्णांक t = scratch >= 0 ? scratch : pte;
	पूर्णांक cur = pte;

	अगर (_PAGE_PRESENT_SHIFT) अणु
		uयंत्र_i_srl(p, t, cur, _PAGE_PRESENT_SHIFT);
		cur = t;
	पूर्ण
	uयंत्र_i_andi(p, t, cur,
		    (_PAGE_PRESENT | _PAGE_WRITE) >> _PAGE_PRESENT_SHIFT);
	uयंत्र_i_xori(p, t, t,
		    (_PAGE_PRESENT | _PAGE_WRITE) >> _PAGE_PRESENT_SHIFT);
	uयंत्र_il_bnez(p, r, t, lid);
	अगर (pte == t)
		/* You lose the SMP race :-(*/
		iPTE_LW(p, pte, ptr);
	अन्यथा
		uयंत्र_i_nop(p);
पूर्ण

/* Make PTE writable, update software status bits as well, then store
 * at PTR.
 */
अटल व्योम
build_make_ग_लिखो(u32 **p, काष्ठा uयंत्र_reloc **r, अचिन्हित पूर्णांक pte,
		 अचिन्हित पूर्णांक ptr, अचिन्हित पूर्णांक scratch)
अणु
	अचिन्हित पूर्णांक mode = (_PAGE_ACCESSED | _PAGE_MODIFIED | _PAGE_VALID
			     | _PAGE_सूचीTY);

	iPTE_SW(p, r, pte, ptr, mode, scratch);
पूर्ण

/*
 * Check अगर PTE can be modअगरied, अगर not branch to LABEL. Regardless
 * restore PTE with value from PTR when करोne.
 */
अटल व्योम
build_pte_modअगरiable(u32 **p, काष्ठा uयंत्र_reloc **r,
		     अचिन्हित पूर्णांक pte, अचिन्हित पूर्णांक ptr, पूर्णांक scratch,
		     क्रमागत label_id lid)
अणु
	अगर (use_bbit_insns()) अणु
		uयंत्र_il_bbit0(p, r, pte, ilog2(_PAGE_WRITE), lid);
		uयंत्र_i_nop(p);
	पूर्ण अन्यथा अणु
		पूर्णांक t = scratch >= 0 ? scratch : pte;
		uयंत्र_i_srl(p, t, pte, _PAGE_WRITE_SHIFT);
		uयंत्र_i_andi(p, t, t, 1);
		uयंत्र_il_beqz(p, r, t, lid);
		अगर (pte == t)
			/* You lose the SMP race :-(*/
			iPTE_LW(p, pte, ptr);
	पूर्ण
पूर्ण

#अगर_अघोषित CONFIG_MIPS_PGD_C0_CONTEXT


/*
 * R3000 style TLB load/store/modअगरy handlers.
 */

/*
 * This places the pte पूर्णांकo ENTRYLO0 and ग_लिखोs it with tlbwi.
 * Then it वापसs.
 */
अटल व्योम
build_r3000_pte_reload_tlbwi(u32 **p, अचिन्हित पूर्णांक pte, अचिन्हित पूर्णांक पंचांगp)
अणु
	uयंत्र_i_mtc0(p, pte, C0_ENTRYLO0); /* cp0 delay */
	uयंत्र_i_mfc0(p, पंचांगp, C0_EPC); /* cp0 delay */
	uयंत्र_i_tlbwi(p);
	uयंत्र_i_jr(p, पंचांगp);
	uयंत्र_i_rfe(p); /* branch delay */
पूर्ण

/*
 * This places the pte पूर्णांकo ENTRYLO0 and ग_लिखोs it with tlbwi
 * or tlbwr as appropriate.  This is because the index रेजिस्टर
 * may have the probe fail bit set as a result of a trap on a
 * kseg2 access, i.e. without refill.  Then it वापसs.
 */
अटल व्योम
build_r3000_tlb_reload_ग_लिखो(u32 **p, काष्ठा uयंत्र_label **l,
			     काष्ठा uयंत्र_reloc **r, अचिन्हित पूर्णांक pte,
			     अचिन्हित पूर्णांक पंचांगp)
अणु
	uयंत्र_i_mfc0(p, पंचांगp, C0_INDEX);
	uयंत्र_i_mtc0(p, pte, C0_ENTRYLO0); /* cp0 delay */
	uयंत्र_il_bltz(p, r, पंचांगp, label_r3000_ग_लिखो_probe_fail); /* cp0 delay */
	uयंत्र_i_mfc0(p, पंचांगp, C0_EPC); /* branch delay */
	uयंत्र_i_tlbwi(p); /* cp0 delay */
	uयंत्र_i_jr(p, पंचांगp);
	uयंत्र_i_rfe(p); /* branch delay */
	uयंत्र_l_r3000_ग_लिखो_probe_fail(l, *p);
	uयंत्र_i_tlbwr(p); /* cp0 delay */
	uयंत्र_i_jr(p, पंचांगp);
	uयंत्र_i_rfe(p); /* branch delay */
पूर्ण

अटल व्योम
build_r3000_tlbchange_handler_head(u32 **p, अचिन्हित पूर्णांक pte,
				   अचिन्हित पूर्णांक ptr)
अणु
	दीर्घ pgdc = (दीर्घ)pgd_current;

	uयंत्र_i_mfc0(p, pte, C0_BADVADDR);
	uयंत्र_i_lui(p, ptr, uयंत्र_rel_hi(pgdc)); /* cp0 delay */
	uयंत्र_i_lw(p, ptr, uयंत्र_rel_lo(pgdc), ptr);
	uयंत्र_i_srl(p, pte, pte, 22); /* load delay */
	uयंत्र_i_sll(p, pte, pte, 2);
	uयंत्र_i_addu(p, ptr, ptr, pte);
	uयंत्र_i_mfc0(p, pte, C0_CONTEXT);
	uयंत्र_i_lw(p, ptr, 0, ptr); /* cp0 delay */
	uयंत्र_i_andi(p, pte, pte, 0xffc); /* load delay */
	uयंत्र_i_addu(p, ptr, ptr, pte);
	uयंत्र_i_lw(p, pte, 0, ptr);
	uयंत्र_i_tlbp(p); /* load delay */
पूर्ण

अटल व्योम build_r3000_tlb_load_handler(व्योम)
अणु
	u32 *p = (u32 *)handle_tlbl;
	काष्ठा uयंत्र_label *l = labels;
	काष्ठा uयंत्र_reloc *r = relocs;

	स_रखो(p, 0, handle_tlbl_end - (अक्षर *)p);
	स_रखो(labels, 0, माप(labels));
	स_रखो(relocs, 0, माप(relocs));

	build_r3000_tlbchange_handler_head(&p, K0, K1);
	build_pte_present(&p, &r, K0, K1, -1, label_nopage_tlbl);
	uयंत्र_i_nop(&p); /* load delay */
	build_make_valid(&p, &r, K0, K1, -1);
	build_r3000_tlb_reload_ग_लिखो(&p, &l, &r, K0, K1);

	uयंत्र_l_nopage_tlbl(&l, p);
	uयंत्र_i_j(&p, (अचिन्हित दीर्घ)tlb_करो_page_fault_0 & 0x0fffffff);
	uयंत्र_i_nop(&p);

	अगर (p >= (u32 *)handle_tlbl_end)
		panic("TLB load handler fastpath space exceeded");

	uयंत्र_resolve_relocs(relocs, labels);
	pr_debug("Wrote TLB load handler fastpath (%u instructions).\n",
		 (अचिन्हित पूर्णांक)(p - (u32 *)handle_tlbl));

	dump_handler("r3000_tlb_load", handle_tlbl, handle_tlbl_end);
पूर्ण

अटल व्योम build_r3000_tlb_store_handler(व्योम)
अणु
	u32 *p = (u32 *)handle_tlbs;
	काष्ठा uयंत्र_label *l = labels;
	काष्ठा uयंत्र_reloc *r = relocs;

	स_रखो(p, 0, handle_tlbs_end - (अक्षर *)p);
	स_रखो(labels, 0, माप(labels));
	स_रखो(relocs, 0, माप(relocs));

	build_r3000_tlbchange_handler_head(&p, K0, K1);
	build_pte_writable(&p, &r, K0, K1, -1, label_nopage_tlbs);
	uयंत्र_i_nop(&p); /* load delay */
	build_make_ग_लिखो(&p, &r, K0, K1, -1);
	build_r3000_tlb_reload_ग_लिखो(&p, &l, &r, K0, K1);

	uयंत्र_l_nopage_tlbs(&l, p);
	uयंत्र_i_j(&p, (अचिन्हित दीर्घ)tlb_करो_page_fault_1 & 0x0fffffff);
	uयंत्र_i_nop(&p);

	अगर (p >= (u32 *)handle_tlbs_end)
		panic("TLB store handler fastpath space exceeded");

	uयंत्र_resolve_relocs(relocs, labels);
	pr_debug("Wrote TLB store handler fastpath (%u instructions).\n",
		 (अचिन्हित पूर्णांक)(p - (u32 *)handle_tlbs));

	dump_handler("r3000_tlb_store", handle_tlbs, handle_tlbs_end);
पूर्ण

अटल व्योम build_r3000_tlb_modअगरy_handler(व्योम)
अणु
	u32 *p = (u32 *)handle_tlbm;
	काष्ठा uयंत्र_label *l = labels;
	काष्ठा uयंत्र_reloc *r = relocs;

	स_रखो(p, 0, handle_tlbm_end - (अक्षर *)p);
	स_रखो(labels, 0, माप(labels));
	स_रखो(relocs, 0, माप(relocs));

	build_r3000_tlbchange_handler_head(&p, K0, K1);
	build_pte_modअगरiable(&p, &r, K0, K1,  -1, label_nopage_tlbm);
	uयंत्र_i_nop(&p); /* load delay */
	build_make_ग_लिखो(&p, &r, K0, K1, -1);
	build_r3000_pte_reload_tlbwi(&p, K0, K1);

	uयंत्र_l_nopage_tlbm(&l, p);
	uयंत्र_i_j(&p, (अचिन्हित दीर्घ)tlb_करो_page_fault_1 & 0x0fffffff);
	uयंत्र_i_nop(&p);

	अगर (p >= (u32 *)handle_tlbm_end)
		panic("TLB modify handler fastpath space exceeded");

	uयंत्र_resolve_relocs(relocs, labels);
	pr_debug("Wrote TLB modify handler fastpath (%u instructions).\n",
		 (अचिन्हित पूर्णांक)(p - (u32 *)handle_tlbm));

	dump_handler("r3000_tlb_modify", handle_tlbm, handle_tlbm_end);
पूर्ण
#पूर्ण_अगर /* CONFIG_MIPS_PGD_C0_CONTEXT */

अटल bool cpu_has_tlbex_tlbp_race(व्योम)
अणु
	/*
	 * When a Hardware Table Walker is running it can replace TLB entries
	 * at any समय, leading to a race between it & the CPU.
	 */
	अगर (cpu_has_htw)
		वापस true;

	/*
	 * If the CPU shares FTLB RAM with its siblings then our entry may be
	 * replaced at any समय by a sibling perक्रमming a ग_लिखो to the FTLB.
	 */
	अगर (cpu_has_shared_ftlb_ram)
		वापस true;

	/* In all other हालs there ought to be no race condition to handle */
	वापस false;
पूर्ण

/*
 * R4000 style TLB load/store/modअगरy handlers.
 */
अटल काष्ठा work_रेजिस्टरs
build_r4000_tlbchange_handler_head(u32 **p, काष्ठा uयंत्र_label **l,
				   काष्ठा uयंत्र_reloc **r)
अणु
	काष्ठा work_रेजिस्टरs wr = build_get_work_रेजिस्टरs(p);

#अगर_घोषित CONFIG_64BIT
	build_get_pmde64(p, l, r, wr.r1, wr.r2); /* get pmd in ptr */
#अन्यथा
	build_get_pgde32(p, wr.r1, wr.r2); /* get pgd in ptr */
#पूर्ण_अगर

#अगर_घोषित CONFIG_MIPS_HUGE_TLB_SUPPORT
	/*
	 * For huge tlb entries, pmd करोesn't contain an address but
	 * instead contains the tlb pte. Check the PAGE_HUGE bit and
	 * see अगर we need to jump to huge tlb processing.
	 */
	build_is_huge_pte(p, r, wr.r1, wr.r2, label_tlb_huge_update);
#पूर्ण_अगर

	UASM_i_MFC0(p, wr.r1, C0_BADVADDR);
	UASM_i_LW(p, wr.r2, 0, wr.r2);
	UASM_i_SRL(p, wr.r1, wr.r1, PAGE_SHIFT + PTE_ORDER - PTE_T_LOG2);
	uयंत्र_i_andi(p, wr.r1, wr.r1, (PTRS_PER_PTE - 1) << PTE_T_LOG2);
	UASM_i_ADDU(p, wr.r2, wr.r2, wr.r1);

#अगर_घोषित CONFIG_SMP
	uयंत्र_l_smp_pgtable_change(l, *p);
#पूर्ण_अगर
	iPTE_LW(p, wr.r1, wr.r2); /* get even pte */
	अगर (!m4kc_tlbp_war()) अणु
		build_tlb_probe_entry(p);
		अगर (cpu_has_tlbex_tlbp_race()) अणु
			/* race condition happens, leaving */
			uयंत्र_i_ehb(p);
			uयंत्र_i_mfc0(p, wr.r3, C0_INDEX);
			uयंत्र_il_bltz(p, r, wr.r3, label_leave);
			uयंत्र_i_nop(p);
		पूर्ण
	पूर्ण
	वापस wr;
पूर्ण

अटल व्योम
build_r4000_tlbchange_handler_tail(u32 **p, काष्ठा uयंत्र_label **l,
				   काष्ठा uयंत्र_reloc **r, अचिन्हित पूर्णांक पंचांगp,
				   अचिन्हित पूर्णांक ptr)
अणु
	uयंत्र_i_ori(p, ptr, ptr, माप(pte_t));
	uयंत्र_i_xori(p, ptr, ptr, माप(pte_t));
	build_update_entries(p, पंचांगp, ptr);
	build_tlb_ग_लिखो_entry(p, l, r, tlb_indexed);
	uयंत्र_l_leave(l, *p);
	build_restore_work_रेजिस्टरs(p);
	uयंत्र_i_eret(p); /* वापस from trap */

#अगर_घोषित CONFIG_64BIT
	build_get_pgd_vदो_स्मृति64(p, l, r, पंचांगp, ptr, not_refill);
#पूर्ण_अगर
पूर्ण

अटल व्योम build_r4000_tlb_load_handler(व्योम)
अणु
	u32 *p = (u32 *)msk_isa16_mode((uदीर्घ)handle_tlbl);
	काष्ठा uयंत्र_label *l = labels;
	काष्ठा uयंत्र_reloc *r = relocs;
	काष्ठा work_रेजिस्टरs wr;

	स_रखो(p, 0, handle_tlbl_end - (अक्षर *)p);
	स_रखो(labels, 0, माप(labels));
	स_रखो(relocs, 0, माप(relocs));

	अगर (bcm1250_m3_war()) अणु
		अचिन्हित पूर्णांक segbits = 44;

		uयंत्र_i_dmfc0(&p, K0, C0_BADVADDR);
		uयंत्र_i_dmfc0(&p, K1, C0_ENTRYHI);
		uयंत्र_i_xor(&p, K0, K0, K1);
		uयंत्र_i_dsrl_safe(&p, K1, K0, 62);
		uयंत्र_i_dsrl_safe(&p, K0, K0, 12 + 1);
		uयंत्र_i_dsll_safe(&p, K0, K0, 64 + 12 + 1 - segbits);
		uयंत्र_i_or(&p, K0, K0, K1);
		uयंत्र_il_bnez(&p, &r, K0, label_leave);
		/* No need क्रम uयंत्र_i_nop */
	पूर्ण

	wr = build_r4000_tlbchange_handler_head(&p, &l, &r);
	build_pte_present(&p, &r, wr.r1, wr.r2, wr.r3, label_nopage_tlbl);
	अगर (m4kc_tlbp_war())
		build_tlb_probe_entry(&p);

	अगर (cpu_has_rixi && !cpu_has_rixiex) अणु
		/*
		 * If the page is not _PAGE_VALID, RI or XI could not
		 * have triggered it.  Skip the expensive test..
		 */
		अगर (use_bbit_insns()) अणु
			uयंत्र_il_bbit0(&p, &r, wr.r1, ilog2(_PAGE_VALID),
				      label_tlbl_goaround1);
		पूर्ण अन्यथा अणु
			uयंत्र_i_andi(&p, wr.r3, wr.r1, _PAGE_VALID);
			uयंत्र_il_beqz(&p, &r, wr.r3, label_tlbl_goaround1);
		पूर्ण
		uयंत्र_i_nop(&p);

		/*
		 * Warn अगर something may race with us & replace the TLB entry
		 * beक्रमe we पढ़ो it here. Everything with such races should
		 * also have dedicated RiXi exception handlers, so this
		 * shouldn't be hit.
		 */
		WARN(cpu_has_tlbex_tlbp_race(), "Unhandled race in RiXi path");

		uयंत्र_i_tlbr(&p);

		चयन (current_cpu_type()) अणु
		शेष:
			अगर (cpu_has_mips_r2_exec_hazard) अणु
				uयंत्र_i_ehb(&p);

		हाल CPU_CAVIUM_OCTEON:
		हाल CPU_CAVIUM_OCTEON_PLUS:
		हाल CPU_CAVIUM_OCTEON2:
				अवरोध;
			पूर्ण
		पूर्ण

		/* Examine  entrylo 0 or 1 based on ptr. */
		अगर (use_bbit_insns()) अणु
			uयंत्र_i_bbit0(&p, wr.r2, ilog2(माप(pte_t)), 8);
		पूर्ण अन्यथा अणु
			uयंत्र_i_andi(&p, wr.r3, wr.r2, माप(pte_t));
			uयंत्र_i_beqz(&p, wr.r3, 8);
		पूर्ण
		/* load it in the delay slot*/
		UASM_i_MFC0(&p, wr.r3, C0_ENTRYLO0);
		/* load it अगर ptr is odd */
		UASM_i_MFC0(&p, wr.r3, C0_ENTRYLO1);
		/*
		 * If the entryLo (now in wr.r3) is valid (bit 1), RI or
		 * XI must have triggered it.
		 */
		अगर (use_bbit_insns()) अणु
			uयंत्र_il_bbit1(&p, &r, wr.r3, 1, label_nopage_tlbl);
			uयंत्र_i_nop(&p);
			uयंत्र_l_tlbl_goaround1(&l, p);
		पूर्ण अन्यथा अणु
			uयंत्र_i_andi(&p, wr.r3, wr.r3, 2);
			uयंत्र_il_bnez(&p, &r, wr.r3, label_nopage_tlbl);
			uयंत्र_i_nop(&p);
		पूर्ण
		uयंत्र_l_tlbl_goaround1(&l, p);
	पूर्ण
	build_make_valid(&p, &r, wr.r1, wr.r2, wr.r3);
	build_r4000_tlbchange_handler_tail(&p, &l, &r, wr.r1, wr.r2);

#अगर_घोषित CONFIG_MIPS_HUGE_TLB_SUPPORT
	/*
	 * This is the entry poपूर्णांक when build_r4000_tlbchange_handler_head
	 * spots a huge page.
	 */
	uयंत्र_l_tlb_huge_update(&l, p);
	iPTE_LW(&p, wr.r1, wr.r2);
	build_pte_present(&p, &r, wr.r1, wr.r2, wr.r3, label_nopage_tlbl);
	build_tlb_probe_entry(&p);

	अगर (cpu_has_rixi && !cpu_has_rixiex) अणु
		/*
		 * If the page is not _PAGE_VALID, RI or XI could not
		 * have triggered it.  Skip the expensive test..
		 */
		अगर (use_bbit_insns()) अणु
			uयंत्र_il_bbit0(&p, &r, wr.r1, ilog2(_PAGE_VALID),
				      label_tlbl_goaround2);
		पूर्ण अन्यथा अणु
			uयंत्र_i_andi(&p, wr.r3, wr.r1, _PAGE_VALID);
			uयंत्र_il_beqz(&p, &r, wr.r3, label_tlbl_goaround2);
		पूर्ण
		uयंत्र_i_nop(&p);

		/*
		 * Warn अगर something may race with us & replace the TLB entry
		 * beक्रमe we पढ़ो it here. Everything with such races should
		 * also have dedicated RiXi exception handlers, so this
		 * shouldn't be hit.
		 */
		WARN(cpu_has_tlbex_tlbp_race(), "Unhandled race in RiXi path");

		uयंत्र_i_tlbr(&p);

		चयन (current_cpu_type()) अणु
		शेष:
			अगर (cpu_has_mips_r2_exec_hazard) अणु
				uयंत्र_i_ehb(&p);

		हाल CPU_CAVIUM_OCTEON:
		हाल CPU_CAVIUM_OCTEON_PLUS:
		हाल CPU_CAVIUM_OCTEON2:
				अवरोध;
			पूर्ण
		पूर्ण

		/* Examine  entrylo 0 or 1 based on ptr. */
		अगर (use_bbit_insns()) अणु
			uयंत्र_i_bbit0(&p, wr.r2, ilog2(माप(pte_t)), 8);
		पूर्ण अन्यथा अणु
			uयंत्र_i_andi(&p, wr.r3, wr.r2, माप(pte_t));
			uयंत्र_i_beqz(&p, wr.r3, 8);
		पूर्ण
		/* load it in the delay slot*/
		UASM_i_MFC0(&p, wr.r3, C0_ENTRYLO0);
		/* load it अगर ptr is odd */
		UASM_i_MFC0(&p, wr.r3, C0_ENTRYLO1);
		/*
		 * If the entryLo (now in wr.r3) is valid (bit 1), RI or
		 * XI must have triggered it.
		 */
		अगर (use_bbit_insns()) अणु
			uयंत्र_il_bbit0(&p, &r, wr.r3, 1, label_tlbl_goaround2);
		पूर्ण अन्यथा अणु
			uयंत्र_i_andi(&p, wr.r3, wr.r3, 2);
			uयंत्र_il_beqz(&p, &r, wr.r3, label_tlbl_goaround2);
		पूर्ण
		अगर (PM_DEFAULT_MASK == 0)
			uयंत्र_i_nop(&p);
		/*
		 * We clobbered C0_PAGEMASK, restore it.  On the other branch
		 * it is restored in build_huge_tlb_ग_लिखो_entry.
		 */
		build_restore_pagemask(&p, &r, wr.r3, label_nopage_tlbl, 0);

		uयंत्र_l_tlbl_goaround2(&l, p);
	पूर्ण
	uयंत्र_i_ori(&p, wr.r1, wr.r1, (_PAGE_ACCESSED | _PAGE_VALID));
	build_huge_handler_tail(&p, &r, &l, wr.r1, wr.r2, 1);
#पूर्ण_अगर

	uयंत्र_l_nopage_tlbl(&l, p);
	अगर (IS_ENABLED(CONFIG_CPU_LOONGSON3_WORKAROUNDS))
		uयंत्र_i_sync(&p, 0);
	build_restore_work_रेजिस्टरs(&p);
#अगर_घोषित CONFIG_CPU_MICROMIPS
	अगर ((अचिन्हित दीर्घ)tlb_करो_page_fault_0 & 1) अणु
		uयंत्र_i_lui(&p, K0, uयंत्र_rel_hi((दीर्घ)tlb_करो_page_fault_0));
		uयंत्र_i_addiu(&p, K0, K0, uयंत्र_rel_lo((दीर्घ)tlb_करो_page_fault_0));
		uयंत्र_i_jr(&p, K0);
	पूर्ण अन्यथा
#पूर्ण_अगर
	uयंत्र_i_j(&p, (अचिन्हित दीर्घ)tlb_करो_page_fault_0 & 0x0fffffff);
	uयंत्र_i_nop(&p);

	अगर (p >= (u32 *)handle_tlbl_end)
		panic("TLB load handler fastpath space exceeded");

	uयंत्र_resolve_relocs(relocs, labels);
	pr_debug("Wrote TLB load handler fastpath (%u instructions).\n",
		 (अचिन्हित पूर्णांक)(p - (u32 *)handle_tlbl));

	dump_handler("r4000_tlb_load", handle_tlbl, handle_tlbl_end);
पूर्ण

अटल व्योम build_r4000_tlb_store_handler(व्योम)
अणु
	u32 *p = (u32 *)msk_isa16_mode((uदीर्घ)handle_tlbs);
	काष्ठा uयंत्र_label *l = labels;
	काष्ठा uयंत्र_reloc *r = relocs;
	काष्ठा work_रेजिस्टरs wr;

	स_रखो(p, 0, handle_tlbs_end - (अक्षर *)p);
	स_रखो(labels, 0, माप(labels));
	स_रखो(relocs, 0, माप(relocs));

	wr = build_r4000_tlbchange_handler_head(&p, &l, &r);
	build_pte_writable(&p, &r, wr.r1, wr.r2, wr.r3, label_nopage_tlbs);
	अगर (m4kc_tlbp_war())
		build_tlb_probe_entry(&p);
	build_make_ग_लिखो(&p, &r, wr.r1, wr.r2, wr.r3);
	build_r4000_tlbchange_handler_tail(&p, &l, &r, wr.r1, wr.r2);

#अगर_घोषित CONFIG_MIPS_HUGE_TLB_SUPPORT
	/*
	 * This is the entry poपूर्णांक when
	 * build_r4000_tlbchange_handler_head spots a huge page.
	 */
	uयंत्र_l_tlb_huge_update(&l, p);
	iPTE_LW(&p, wr.r1, wr.r2);
	build_pte_writable(&p, &r, wr.r1, wr.r2, wr.r3, label_nopage_tlbs);
	build_tlb_probe_entry(&p);
	uयंत्र_i_ori(&p, wr.r1, wr.r1,
		   _PAGE_ACCESSED | _PAGE_MODIFIED | _PAGE_VALID | _PAGE_सूचीTY);
	build_huge_handler_tail(&p, &r, &l, wr.r1, wr.r2, 1);
#पूर्ण_अगर

	uयंत्र_l_nopage_tlbs(&l, p);
	अगर (IS_ENABLED(CONFIG_CPU_LOONGSON3_WORKAROUNDS))
		uयंत्र_i_sync(&p, 0);
	build_restore_work_रेजिस्टरs(&p);
#अगर_घोषित CONFIG_CPU_MICROMIPS
	अगर ((अचिन्हित दीर्घ)tlb_करो_page_fault_1 & 1) अणु
		uयंत्र_i_lui(&p, K0, uयंत्र_rel_hi((दीर्घ)tlb_करो_page_fault_1));
		uयंत्र_i_addiu(&p, K0, K0, uयंत्र_rel_lo((दीर्घ)tlb_करो_page_fault_1));
		uयंत्र_i_jr(&p, K0);
	पूर्ण अन्यथा
#पूर्ण_अगर
	uयंत्र_i_j(&p, (अचिन्हित दीर्घ)tlb_करो_page_fault_1 & 0x0fffffff);
	uयंत्र_i_nop(&p);

	अगर (p >= (u32 *)handle_tlbs_end)
		panic("TLB store handler fastpath space exceeded");

	uयंत्र_resolve_relocs(relocs, labels);
	pr_debug("Wrote TLB store handler fastpath (%u instructions).\n",
		 (अचिन्हित पूर्णांक)(p - (u32 *)handle_tlbs));

	dump_handler("r4000_tlb_store", handle_tlbs, handle_tlbs_end);
पूर्ण

अटल व्योम build_r4000_tlb_modअगरy_handler(व्योम)
अणु
	u32 *p = (u32 *)msk_isa16_mode((uदीर्घ)handle_tlbm);
	काष्ठा uयंत्र_label *l = labels;
	काष्ठा uयंत्र_reloc *r = relocs;
	काष्ठा work_रेजिस्टरs wr;

	स_रखो(p, 0, handle_tlbm_end - (अक्षर *)p);
	स_रखो(labels, 0, माप(labels));
	स_रखो(relocs, 0, माप(relocs));

	wr = build_r4000_tlbchange_handler_head(&p, &l, &r);
	build_pte_modअगरiable(&p, &r, wr.r1, wr.r2, wr.r3, label_nopage_tlbm);
	अगर (m4kc_tlbp_war())
		build_tlb_probe_entry(&p);
	/* Present and writable bits set, set accessed and dirty bits. */
	build_make_ग_लिखो(&p, &r, wr.r1, wr.r2, wr.r3);
	build_r4000_tlbchange_handler_tail(&p, &l, &r, wr.r1, wr.r2);

#अगर_घोषित CONFIG_MIPS_HUGE_TLB_SUPPORT
	/*
	 * This is the entry poपूर्णांक when
	 * build_r4000_tlbchange_handler_head spots a huge page.
	 */
	uयंत्र_l_tlb_huge_update(&l, p);
	iPTE_LW(&p, wr.r1, wr.r2);
	build_pte_modअगरiable(&p, &r, wr.r1, wr.r2,  wr.r3, label_nopage_tlbm);
	build_tlb_probe_entry(&p);
	uयंत्र_i_ori(&p, wr.r1, wr.r1,
		   _PAGE_ACCESSED | _PAGE_MODIFIED | _PAGE_VALID | _PAGE_सूचीTY);
	build_huge_handler_tail(&p, &r, &l, wr.r1, wr.r2, 0);
#पूर्ण_अगर

	uयंत्र_l_nopage_tlbm(&l, p);
	अगर (IS_ENABLED(CONFIG_CPU_LOONGSON3_WORKAROUNDS))
		uयंत्र_i_sync(&p, 0);
	build_restore_work_रेजिस्टरs(&p);
#अगर_घोषित CONFIG_CPU_MICROMIPS
	अगर ((अचिन्हित दीर्घ)tlb_करो_page_fault_1 & 1) अणु
		uयंत्र_i_lui(&p, K0, uयंत्र_rel_hi((दीर्घ)tlb_करो_page_fault_1));
		uयंत्र_i_addiu(&p, K0, K0, uयंत्र_rel_lo((दीर्घ)tlb_करो_page_fault_1));
		uयंत्र_i_jr(&p, K0);
	पूर्ण अन्यथा
#पूर्ण_अगर
	uयंत्र_i_j(&p, (अचिन्हित दीर्घ)tlb_करो_page_fault_1 & 0x0fffffff);
	uयंत्र_i_nop(&p);

	अगर (p >= (u32 *)handle_tlbm_end)
		panic("TLB modify handler fastpath space exceeded");

	uयंत्र_resolve_relocs(relocs, labels);
	pr_debug("Wrote TLB modify handler fastpath (%u instructions).\n",
		 (अचिन्हित पूर्णांक)(p - (u32 *)handle_tlbm));

	dump_handler("r4000_tlb_modify", handle_tlbm, handle_tlbm_end);
पूर्ण

अटल व्योम flush_tlb_handlers(व्योम)
अणु
	local_flush_icache_range((अचिन्हित दीर्घ)handle_tlbl,
			   (अचिन्हित दीर्घ)handle_tlbl_end);
	local_flush_icache_range((अचिन्हित दीर्घ)handle_tlbs,
			   (अचिन्हित दीर्घ)handle_tlbs_end);
	local_flush_icache_range((अचिन्हित दीर्घ)handle_tlbm,
			   (अचिन्हित दीर्घ)handle_tlbm_end);
	local_flush_icache_range((अचिन्हित दीर्घ)tlbmiss_handler_setup_pgd,
			   (अचिन्हित दीर्घ)tlbmiss_handler_setup_pgd_end);
पूर्ण

अटल व्योम prपूर्णांक_htw_config(व्योम)
अणु
	अचिन्हित दीर्घ config;
	अचिन्हित पूर्णांक pwctl;
	स्थिर पूर्णांक field = 2 * माप(अचिन्हित दीर्घ);

	config = पढ़ो_c0_pwfield();
	pr_debug("PWField (0x%0*lx): GDI: 0x%02lx  UDI: 0x%02lx  MDI: 0x%02lx  PTI: 0x%02lx  PTEI: 0x%02lx\n",
		field, config,
		(config & MIPS_PWFIELD_GDI_MASK) >> MIPS_PWFIELD_GDI_SHIFT,
		(config & MIPS_PWFIELD_UDI_MASK) >> MIPS_PWFIELD_UDI_SHIFT,
		(config & MIPS_PWFIELD_MDI_MASK) >> MIPS_PWFIELD_MDI_SHIFT,
		(config & MIPS_PWFIELD_PTI_MASK) >> MIPS_PWFIELD_PTI_SHIFT,
		(config & MIPS_PWFIELD_PTEI_MASK) >> MIPS_PWFIELD_PTEI_SHIFT);

	config = पढ़ो_c0_pwsize();
	pr_debug("PWSize  (0x%0*lx): PS: 0x%lx  GDW: 0x%02lx  UDW: 0x%02lx  MDW: 0x%02lx  PTW: 0x%02lx  PTEW: 0x%02lx\n",
		field, config,
		(config & MIPS_PWSIZE_PS_MASK) >> MIPS_PWSIZE_PS_SHIFT,
		(config & MIPS_PWSIZE_GDW_MASK) >> MIPS_PWSIZE_GDW_SHIFT,
		(config & MIPS_PWSIZE_UDW_MASK) >> MIPS_PWSIZE_UDW_SHIFT,
		(config & MIPS_PWSIZE_MDW_MASK) >> MIPS_PWSIZE_MDW_SHIFT,
		(config & MIPS_PWSIZE_PTW_MASK) >> MIPS_PWSIZE_PTW_SHIFT,
		(config & MIPS_PWSIZE_PTEW_MASK) >> MIPS_PWSIZE_PTEW_SHIFT);

	pwctl = पढ़ो_c0_pwctl();
	pr_debug("PWCtl   (0x%x): PWEn: 0x%x  XK: 0x%x  XS: 0x%x  XU: 0x%x  DPH: 0x%x  HugePg: 0x%x  Psn: 0x%x\n",
		pwctl,
		(pwctl & MIPS_PWCTL_PWEN_MASK) >> MIPS_PWCTL_PWEN_SHIFT,
		(pwctl & MIPS_PWCTL_XK_MASK) >> MIPS_PWCTL_XK_SHIFT,
		(pwctl & MIPS_PWCTL_XS_MASK) >> MIPS_PWCTL_XS_SHIFT,
		(pwctl & MIPS_PWCTL_XU_MASK) >> MIPS_PWCTL_XU_SHIFT,
		(pwctl & MIPS_PWCTL_DPH_MASK) >> MIPS_PWCTL_DPH_SHIFT,
		(pwctl & MIPS_PWCTL_HUGEPG_MASK) >> MIPS_PWCTL_HUGEPG_SHIFT,
		(pwctl & MIPS_PWCTL_PSN_MASK) >> MIPS_PWCTL_PSN_SHIFT);
पूर्ण

अटल व्योम config_htw_params(व्योम)
अणु
	अचिन्हित दीर्घ pwfield, pwsize, ptei;
	अचिन्हित पूर्णांक config;

	/*
	 * We are using 2-level page tables, so we only need to
	 * setup GDW and PTW appropriately. UDW and MDW will reमुख्य 0.
	 * The शेष value of GDI/UDI/MDI/PTI is 0xc. It is illegal to
	 * ग_लिखो values less than 0xc in these fields because the entire
	 * ग_लिखो will be dropped. As a result of which, we must preserve
	 * the original reset values and overग_लिखो only what we really want.
	 */

	pwfield = पढ़ो_c0_pwfield();
	/* re-initialize the GDI field */
	pwfield &= ~MIPS_PWFIELD_GDI_MASK;
	pwfield |= PGसूची_SHIFT << MIPS_PWFIELD_GDI_SHIFT;
	/* re-initialize the PTI field including the even/odd bit */
	pwfield &= ~MIPS_PWFIELD_PTI_MASK;
	pwfield |= PAGE_SHIFT << MIPS_PWFIELD_PTI_SHIFT;
	अगर (CONFIG_PGTABLE_LEVELS >= 3) अणु
		pwfield &= ~MIPS_PWFIELD_MDI_MASK;
		pwfield |= PMD_SHIFT << MIPS_PWFIELD_MDI_SHIFT;
	पूर्ण
	/* Set the PTEI right shअगरt */
	ptei = _PAGE_GLOBAL_SHIFT << MIPS_PWFIELD_PTEI_SHIFT;
	pwfield |= ptei;
	ग_लिखो_c0_pwfield(pwfield);
	/* Check whether the PTEI value is supported */
	back_to_back_c0_hazard();
	pwfield = पढ़ो_c0_pwfield();
	अगर (((pwfield & MIPS_PWFIELD_PTEI_MASK) << MIPS_PWFIELD_PTEI_SHIFT)
		!= ptei) अणु
		pr_warn("Unsupported PTEI field value: 0x%lx. HTW will not be enabled",
			ptei);
		/*
		 * Drop option to aव्योम HTW being enabled via another path
		 * (eg htw_reset())
		 */
		current_cpu_data.options &= ~MIPS_CPU_HTW;
		वापस;
	पूर्ण

	pwsize = ilog2(PTRS_PER_PGD) << MIPS_PWSIZE_GDW_SHIFT;
	pwsize |= ilog2(PTRS_PER_PTE) << MIPS_PWSIZE_PTW_SHIFT;
	अगर (CONFIG_PGTABLE_LEVELS >= 3)
		pwsize |= ilog2(PTRS_PER_PMD) << MIPS_PWSIZE_MDW_SHIFT;

	/* Set poपूर्णांकer size to size of directory poपूर्णांकers */
	अगर (IS_ENABLED(CONFIG_64BIT))
		pwsize |= MIPS_PWSIZE_PS_MASK;
	/* PTEs may be multiple poपूर्णांकers दीर्घ (e.g. with XPA) */
	pwsize |= ((PTE_T_LOG2 - PGD_T_LOG2) << MIPS_PWSIZE_PTEW_SHIFT)
			& MIPS_PWSIZE_PTEW_MASK;

	ग_लिखो_c0_pwsize(pwsize);

	/* Make sure everything is set beक्रमe we enable the HTW */
	back_to_back_c0_hazard();

	/*
	 * Enable HTW (and only क्रम XUSeg on 64-bit), and disable the rest of
	 * the pwctl fields.
	 */
	config = 1 << MIPS_PWCTL_PWEN_SHIFT;
	अगर (IS_ENABLED(CONFIG_64BIT))
		config |= MIPS_PWCTL_XU_MASK;
	ग_लिखो_c0_pwctl(config);
	pr_info("Hardware Page Table Walker enabled\n");

	prपूर्णांक_htw_config();
पूर्ण

अटल व्योम config_xpa_params(व्योम)
अणु
#अगर_घोषित CONFIG_XPA
	अचिन्हित पूर्णांक pagegrain;

	अगर (mips_xpa_disabled) अणु
		pr_info("Extended Physical Addressing (XPA) disabled\n");
		वापस;
	पूर्ण

	pagegrain = पढ़ो_c0_pagegrain();
	ग_लिखो_c0_pagegrain(pagegrain | PG_ELPA);
	back_to_back_c0_hazard();
	pagegrain = पढ़ो_c0_pagegrain();

	अगर (pagegrain & PG_ELPA)
		pr_info("Extended Physical Addressing (XPA) enabled\n");
	अन्यथा
		panic("Extended Physical Addressing (XPA) disabled");
#पूर्ण_अगर
पूर्ण

अटल व्योम check_pabits(व्योम)
अणु
	अचिन्हित दीर्घ entry;
	अचिन्हित pabits, fillbits;

	अगर (!cpu_has_rixi || !_PAGE_NO_EXEC) अणु
		/*
		 * We'll only be making use of the fact that we can rotate bits
		 * पूर्णांकo the fill अगर the CPU supports RIXI, so करोn't bother
		 * probing this क्रम CPUs which करोn't.
		 */
		वापस;
	पूर्ण

	ग_लिखो_c0_entrylo0(~0ul);
	back_to_back_c0_hazard();
	entry = पढ़ो_c0_entrylo0();

	/* clear all non-PFN bits */
	entry &= ~((1 << MIPS_ENTRYLO_PFN_SHIFT) - 1);
	entry &= ~(MIPS_ENTRYLO_RI | MIPS_ENTRYLO_XI);

	/* find a lower bound on PABITS, and upper bound on fill bits */
	pabits = fls_दीर्घ(entry) + 6;
	fillbits = max_t(पूर्णांक, (पूर्णांक)BITS_PER_LONG - pabits, 0);

	/* minus the RI & XI bits */
	fillbits -= min_t(अचिन्हित, fillbits, 2);

	अगर (fillbits >= ilog2(_PAGE_NO_EXEC))
		fill_includes_sw_bits = true;

	pr_debug("Entry* registers contain %u fill bits\n", fillbits);
पूर्ण

व्योम build_tlb_refill_handler(व्योम)
अणु
	/*
	 * The refill handler is generated per-CPU, multi-node प्रणालीs
	 * may have local storage क्रम it. The other handlers are only
	 * needed once.
	 */
	अटल पूर्णांक run_once = 0;

	अगर (IS_ENABLED(CONFIG_XPA) && !cpu_has_rixi)
		panic("Kernels supporting XPA currently require CPUs with RIXI");

	output_pgtable_bits_defines();
	check_pabits();

#अगर_घोषित CONFIG_64BIT
	check_क्रम_high_segbits = current_cpu_data.vmbits > (PGसूची_SHIFT + PGD_ORDER + PAGE_SHIFT - 3);
#पूर्ण_अगर

	अगर (cpu_has_3kex) अणु
#अगर_अघोषित CONFIG_MIPS_PGD_C0_CONTEXT
		अगर (!run_once) अणु
			build_setup_pgd();
			build_r3000_tlb_refill_handler();
			build_r3000_tlb_load_handler();
			build_r3000_tlb_store_handler();
			build_r3000_tlb_modअगरy_handler();
			flush_tlb_handlers();
			run_once++;
		पूर्ण
#अन्यथा
		panic("No R3000 TLB refill handler");
#पूर्ण_अगर
		वापस;
	पूर्ण

	अगर (cpu_has_ldpte)
		setup_pw();

	अगर (!run_once) अणु
		scratch_reg = allocate_kscratch();
		build_setup_pgd();
		build_r4000_tlb_load_handler();
		build_r4000_tlb_store_handler();
		build_r4000_tlb_modअगरy_handler();
		अगर (cpu_has_ldpte)
			build_loongson3_tlb_refill_handler();
		अन्यथा
			build_r4000_tlb_refill_handler();
		flush_tlb_handlers();
		run_once++;
	पूर्ण
	अगर (cpu_has_xpa)
		config_xpa_params();
	अगर (cpu_has_htw)
		config_htw_params();
पूर्ण
