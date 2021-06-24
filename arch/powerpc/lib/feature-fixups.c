<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2001 Ben. Herrenschmidt (benh@kernel.crashing.org)
 *
 *  Modअगरications क्रम ppc64:
 *      Copyright (C) 2003 Dave Engebretsen <engebret@us.ibm.com>
 *
 *  Copyright 2008 Michael Ellerman, IBM Corporation.
 */

#समावेश <linux/types.h>
#समावेश <linux/jump_label.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/stop_machine.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/code-patching.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/security_features.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/inst.h>

काष्ठा fixup_entry अणु
	अचिन्हित दीर्घ	mask;
	अचिन्हित दीर्घ	value;
	दीर्घ		start_off;
	दीर्घ		end_off;
	दीर्घ		alt_start_off;
	दीर्घ		alt_end_off;
पूर्ण;

अटल काष्ठा ppc_inst *calc_addr(काष्ठा fixup_entry *fcur, दीर्घ offset)
अणु
	/*
	 * We store the offset to the code as a negative offset from
	 * the start of the alt_entry, to support the VDSO. This
	 * routine converts that back पूर्णांकo an actual address.
	 */
	वापस (काष्ठा ppc_inst *)((अचिन्हित दीर्घ)fcur + offset);
पूर्ण

अटल पूर्णांक patch_alt_inकाष्ठाion(काष्ठा ppc_inst *src, काष्ठा ppc_inst *dest,
				 काष्ठा ppc_inst *alt_start, काष्ठा ppc_inst *alt_end)
अणु
	पूर्णांक err;
	काष्ठा ppc_inst instr;

	instr = ppc_inst_पढ़ो(src);

	अगर (instr_is_relative_branch(*src)) अणु
		काष्ठा ppc_inst *target = (काष्ठा ppc_inst *)branch_target(src);

		/* Branch within the section करोesn't need translating */
		अगर (target < alt_start || target > alt_end) अणु
			err = translate_branch(&instr, dest, src);
			अगर (err)
				वापस 1;
		पूर्ण
	पूर्ण

	raw_patch_inकाष्ठाion(dest, instr);

	वापस 0;
पूर्ण

अटल पूर्णांक patch_feature_section(अचिन्हित दीर्घ value, काष्ठा fixup_entry *fcur)
अणु
	काष्ठा ppc_inst *start, *end, *alt_start, *alt_end, *src, *dest, nop;

	start = calc_addr(fcur, fcur->start_off);
	end = calc_addr(fcur, fcur->end_off);
	alt_start = calc_addr(fcur, fcur->alt_start_off);
	alt_end = calc_addr(fcur, fcur->alt_end_off);

	अगर ((alt_end - alt_start) > (end - start))
		वापस 1;

	अगर ((value & fcur->mask) == fcur->value)
		वापस 0;

	src = alt_start;
	dest = start;

	क्रम (; src < alt_end; src = ppc_inst_next(src, src),
			      dest = ppc_inst_next(dest, dest)) अणु
		अगर (patch_alt_inकाष्ठाion(src, dest, alt_start, alt_end))
			वापस 1;
	पूर्ण

	nop = ppc_inst(PPC_INST_NOP);
	क्रम (; dest < end; dest = ppc_inst_next(dest, &nop))
		raw_patch_inकाष्ठाion(dest, nop);

	वापस 0;
पूर्ण

व्योम करो_feature_fixups(अचिन्हित दीर्घ value, व्योम *fixup_start, व्योम *fixup_end)
अणु
	काष्ठा fixup_entry *fcur, *fend;

	fcur = fixup_start;
	fend = fixup_end;

	क्रम (; fcur < fend; fcur++) अणु
		अगर (patch_feature_section(value, fcur)) अणु
			WARN_ON(1);
			prपूर्णांकk("Unable to patch feature section at %p - %p" \
				" with %p - %p\n",
				calc_addr(fcur, fcur->start_off),
				calc_addr(fcur, fcur->end_off),
				calc_addr(fcur, fcur->alt_start_off),
				calc_addr(fcur, fcur->alt_end_off));
		पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PPC_BOOK3S_64
अटल व्योम करो_stf_entry_barrier_fixups(क्रमागत stf_barrier_type types)
अणु
	अचिन्हित पूर्णांक instrs[3], *dest;
	दीर्घ *start, *end;
	पूर्णांक i;

	start = PTRRELOC(&__start___stf_entry_barrier_fixup);
	end = PTRRELOC(&__stop___stf_entry_barrier_fixup);

	instrs[0] = 0x60000000; /* nop */
	instrs[1] = 0x60000000; /* nop */
	instrs[2] = 0x60000000; /* nop */

	i = 0;
	अगर (types & STF_BARRIER_FALLBACK) अणु
		instrs[i++] = 0x7d4802a6; /* mflr r10		*/
		instrs[i++] = 0x60000000; /* branch patched below */
		instrs[i++] = 0x7d4803a6; /* mtlr r10		*/
	पूर्ण अन्यथा अगर (types & STF_BARRIER_EIEIO) अणु
		instrs[i++] = 0x7e0006ac; /* eieio + bit 6 hपूर्णांक */
	पूर्ण अन्यथा अगर (types & STF_BARRIER_SYNC_ORI) अणु
		instrs[i++] = 0x7c0004ac; /* hwsync		*/
		instrs[i++] = 0xe94d0000; /* ld r10,0(r13)	*/
		instrs[i++] = 0x63ff0000; /* ori 31,31,0 speculation barrier */
	पूर्ण

	क्रम (i = 0; start < end; start++, i++) अणु
		dest = (व्योम *)start + *start;

		pr_devel("patching dest %lx\n", (अचिन्हित दीर्घ)dest);

		// See comment in करो_entry_flush_fixups() RE order of patching
		अगर (types & STF_BARRIER_FALLBACK) अणु
			patch_inकाष्ठाion((काष्ठा ppc_inst *)dest, ppc_inst(instrs[0]));
			patch_inकाष्ठाion((काष्ठा ppc_inst *)(dest + 2), ppc_inst(instrs[2]));
			patch_branch((काष्ठा ppc_inst *)(dest + 1),
				     (अचिन्हित दीर्घ)&stf_barrier_fallback, BRANCH_SET_LINK);
		पूर्ण अन्यथा अणु
			patch_inकाष्ठाion((काष्ठा ppc_inst *)(dest + 1), ppc_inst(instrs[1]));
			patch_inकाष्ठाion((काष्ठा ppc_inst *)(dest + 2), ppc_inst(instrs[2]));
			patch_inकाष्ठाion((काष्ठा ppc_inst *)dest, ppc_inst(instrs[0]));
		पूर्ण
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "stf-barrier: patched %d entry locations (%s barrier)\n", i,
		(types == STF_BARRIER_NONE)                  ? "no" :
		(types == STF_BARRIER_FALLBACK)              ? "fallback" :
		(types == STF_BARRIER_EIEIO)                 ? "eieio" :
		(types == (STF_BARRIER_SYNC_ORI))            ? "hwsync"
		                                           : "unknown");
पूर्ण

अटल व्योम करो_stf_निकास_barrier_fixups(क्रमागत stf_barrier_type types)
अणु
	अचिन्हित पूर्णांक instrs[6], *dest;
	दीर्घ *start, *end;
	पूर्णांक i;

	start = PTRRELOC(&__start___stf_निकास_barrier_fixup);
	end = PTRRELOC(&__stop___stf_निकास_barrier_fixup);

	instrs[0] = 0x60000000; /* nop */
	instrs[1] = 0x60000000; /* nop */
	instrs[2] = 0x60000000; /* nop */
	instrs[3] = 0x60000000; /* nop */
	instrs[4] = 0x60000000; /* nop */
	instrs[5] = 0x60000000; /* nop */

	i = 0;
	अगर (types & STF_BARRIER_FALLBACK || types & STF_BARRIER_SYNC_ORI) अणु
		अगर (cpu_has_feature(CPU_FTR_HVMODE)) अणु
			instrs[i++] = 0x7db14ba6; /* mtspr 0x131, r13 (HSPRG1) */
			instrs[i++] = 0x7db04aa6; /* mfspr r13, 0x130 (HSPRG0) */
		पूर्ण अन्यथा अणु
			instrs[i++] = 0x7db243a6; /* mtsprg 2,r13	*/
			instrs[i++] = 0x7db142a6; /* mfsprg r13,1    */
	        पूर्ण
		instrs[i++] = 0x7c0004ac; /* hwsync		*/
		instrs[i++] = 0xe9ad0000; /* ld r13,0(r13)	*/
		instrs[i++] = 0x63ff0000; /* ori 31,31,0 speculation barrier */
		अगर (cpu_has_feature(CPU_FTR_HVMODE)) अणु
			instrs[i++] = 0x7db14aa6; /* mfspr r13, 0x131 (HSPRG1) */
		पूर्ण अन्यथा अणु
			instrs[i++] = 0x7db242a6; /* mfsprg r13,2 */
		पूर्ण
	पूर्ण अन्यथा अगर (types & STF_BARRIER_EIEIO) अणु
		instrs[i++] = 0x7e0006ac; /* eieio + bit 6 hपूर्णांक */
	पूर्ण

	क्रम (i = 0; start < end; start++, i++) अणु
		dest = (व्योम *)start + *start;

		pr_devel("patching dest %lx\n", (अचिन्हित दीर्घ)dest);

		patch_inकाष्ठाion((काष्ठा ppc_inst *)dest, ppc_inst(instrs[0]));
		patch_inकाष्ठाion((काष्ठा ppc_inst *)(dest + 1), ppc_inst(instrs[1]));
		patch_inकाष्ठाion((काष्ठा ppc_inst *)(dest + 2), ppc_inst(instrs[2]));
		patch_inकाष्ठाion((काष्ठा ppc_inst *)(dest + 3), ppc_inst(instrs[3]));
		patch_inकाष्ठाion((काष्ठा ppc_inst *)(dest + 4), ppc_inst(instrs[4]));
		patch_inकाष्ठाion((काष्ठा ppc_inst *)(dest + 5), ppc_inst(instrs[5]));
	पूर्ण
	prपूर्णांकk(KERN_DEBUG "stf-barrier: patched %d exit locations (%s barrier)\n", i,
		(types == STF_BARRIER_NONE)                  ? "no" :
		(types == STF_BARRIER_FALLBACK)              ? "fallback" :
		(types == STF_BARRIER_EIEIO)                 ? "eieio" :
		(types == (STF_BARRIER_SYNC_ORI))            ? "hwsync"
		                                           : "unknown");
पूर्ण

अटल पूर्णांक __करो_stf_barrier_fixups(व्योम *data)
अणु
	क्रमागत stf_barrier_type *types = data;

	करो_stf_entry_barrier_fixups(*types);
	करो_stf_निकास_barrier_fixups(*types);

	वापस 0;
पूर्ण

व्योम करो_stf_barrier_fixups(क्रमागत stf_barrier_type types)
अणु
	/*
	 * The call to the fallback entry flush, and the fallback/sync-ori निकास
	 * flush can not be safely patched in/out जबतक other CPUs are executing
	 * them. So call __करो_stf_barrier_fixups() on one CPU जबतक all other CPUs
	 * spin in the stop machine core with पूर्णांकerrupts hard disabled.
	 */
	stop_machine(__करो_stf_barrier_fixups, &types, शून्य);
पूर्ण

व्योम करो_uaccess_flush_fixups(क्रमागत l1d_flush_type types)
अणु
	अचिन्हित पूर्णांक instrs[4], *dest;
	दीर्घ *start, *end;
	पूर्णांक i;

	start = PTRRELOC(&__start___uaccess_flush_fixup);
	end = PTRRELOC(&__stop___uaccess_flush_fixup);

	instrs[0] = 0x60000000; /* nop */
	instrs[1] = 0x60000000; /* nop */
	instrs[2] = 0x60000000; /* nop */
	instrs[3] = 0x4e800020; /* blr */

	i = 0;
	अगर (types == L1D_FLUSH_FALLBACK) अणु
		instrs[3] = 0x60000000; /* nop */
		/* fallthrough to fallback flush */
	पूर्ण

	अगर (types & L1D_FLUSH_ORI) अणु
		instrs[i++] = 0x63ff0000; /* ori 31,31,0 speculation barrier */
		instrs[i++] = 0x63de0000; /* ori 30,30,0 L1d flush*/
	पूर्ण

	अगर (types & L1D_FLUSH_MTTRIG)
		instrs[i++] = 0x7c12dba6; /* mtspr TRIG2,r0 (SPR #882) */

	क्रम (i = 0; start < end; start++, i++) अणु
		dest = (व्योम *)start + *start;

		pr_devel("patching dest %lx\n", (अचिन्हित दीर्घ)dest);

		patch_inकाष्ठाion((काष्ठा ppc_inst *)dest, ppc_inst(instrs[0]));

		patch_inकाष्ठाion((काष्ठा ppc_inst *)(dest + 1), ppc_inst(instrs[1]));
		patch_inकाष्ठाion((काष्ठा ppc_inst *)(dest + 2), ppc_inst(instrs[2]));
		patch_inकाष्ठाion((काष्ठा ppc_inst *)(dest + 3), ppc_inst(instrs[3]));
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "uaccess-flush: patched %d locations (%s flush)\n", i,
		(types == L1D_FLUSH_NONE)       ? "no" :
		(types == L1D_FLUSH_FALLBACK)   ? "fallback displacement" :
		(types &  L1D_FLUSH_ORI)        ? (types & L1D_FLUSH_MTTRIG)
							? "ori+mttrig type"
							: "ori type" :
		(types &  L1D_FLUSH_MTTRIG)     ? "mttrig type"
						: "unknown");
पूर्ण

अटल पूर्णांक __करो_entry_flush_fixups(व्योम *data)
अणु
	क्रमागत l1d_flush_type types = *(क्रमागत l1d_flush_type *)data;
	अचिन्हित पूर्णांक instrs[3], *dest;
	दीर्घ *start, *end;
	पूर्णांक i;

	instrs[0] = 0x60000000; /* nop */
	instrs[1] = 0x60000000; /* nop */
	instrs[2] = 0x60000000; /* nop */

	i = 0;
	अगर (types == L1D_FLUSH_FALLBACK) अणु
		instrs[i++] = 0x7d4802a6; /* mflr r10		*/
		instrs[i++] = 0x60000000; /* branch patched below */
		instrs[i++] = 0x7d4803a6; /* mtlr r10		*/
	पूर्ण

	अगर (types & L1D_FLUSH_ORI) अणु
		instrs[i++] = 0x63ff0000; /* ori 31,31,0 speculation barrier */
		instrs[i++] = 0x63de0000; /* ori 30,30,0 L1d flush*/
	पूर्ण

	अगर (types & L1D_FLUSH_MTTRIG)
		instrs[i++] = 0x7c12dba6; /* mtspr TRIG2,r0 (SPR #882) */

	/*
	 * If we're patching in or out the fallback flush we need to be careful about the
	 * order in which we patch inकाष्ठाions. That's because it's possible we could
	 * take a page fault after patching one inकाष्ठाion, so the sequence of
	 * inकाष्ठाions must be safe even in a half patched state.
	 *
	 * To make that work, when patching in the fallback flush we patch in this order:
	 *  - the mflr		(dest)
	 *  - the mtlr		(dest + 2)
	 *  - the branch	(dest + 1)
	 *
	 * That ensures the sequence is safe to execute at any poपूर्णांक. In contrast अगर we
	 * patch the mtlr last, it's possible we could वापस from the branch and not
	 * restore LR, leading to a crash later.
	 *
	 * When patching out the fallback flush (either with nops or another flush type),
	 * we patch in this order:
	 *  - the branch	(dest + 1)
	 *  - the mtlr		(dest + 2)
	 *  - the mflr		(dest)
	 *
	 * Note we are रक्षित by stop_machine() from other CPUs executing the code in a
	 * semi-patched state.
	 */

	start = PTRRELOC(&__start___entry_flush_fixup);
	end = PTRRELOC(&__stop___entry_flush_fixup);
	क्रम (i = 0; start < end; start++, i++) अणु
		dest = (व्योम *)start + *start;

		pr_devel("patching dest %lx\n", (अचिन्हित दीर्घ)dest);

		अगर (types == L1D_FLUSH_FALLBACK) अणु
			patch_inकाष्ठाion((काष्ठा ppc_inst *)dest, ppc_inst(instrs[0]));
			patch_inकाष्ठाion((काष्ठा ppc_inst *)(dest + 2), ppc_inst(instrs[2]));
			patch_branch((काष्ठा ppc_inst *)(dest + 1),
				     (अचिन्हित दीर्घ)&entry_flush_fallback, BRANCH_SET_LINK);
		पूर्ण अन्यथा अणु
			patch_inकाष्ठाion((काष्ठा ppc_inst *)(dest + 1), ppc_inst(instrs[1]));
			patch_inकाष्ठाion((काष्ठा ppc_inst *)(dest + 2), ppc_inst(instrs[2]));
			patch_inकाष्ठाion((काष्ठा ppc_inst *)dest, ppc_inst(instrs[0]));
		पूर्ण
	पूर्ण

	start = PTRRELOC(&__start___scv_entry_flush_fixup);
	end = PTRRELOC(&__stop___scv_entry_flush_fixup);
	क्रम (; start < end; start++, i++) अणु
		dest = (व्योम *)start + *start;

		pr_devel("patching dest %lx\n", (अचिन्हित दीर्घ)dest);

		अगर (types == L1D_FLUSH_FALLBACK) अणु
			patch_inकाष्ठाion((काष्ठा ppc_inst *)dest, ppc_inst(instrs[0]));
			patch_inकाष्ठाion((काष्ठा ppc_inst *)(dest + 2), ppc_inst(instrs[2]));
			patch_branch((काष्ठा ppc_inst *)(dest + 1),
				     (अचिन्हित दीर्घ)&scv_entry_flush_fallback, BRANCH_SET_LINK);
		पूर्ण अन्यथा अणु
			patch_inकाष्ठाion((काष्ठा ppc_inst *)(dest + 1), ppc_inst(instrs[1]));
			patch_inकाष्ठाion((काष्ठा ppc_inst *)(dest + 2), ppc_inst(instrs[2]));
			patch_inकाष्ठाion((काष्ठा ppc_inst *)dest, ppc_inst(instrs[0]));
		पूर्ण
	पूर्ण


	prपूर्णांकk(KERN_DEBUG "entry-flush: patched %d locations (%s flush)\n", i,
		(types == L1D_FLUSH_NONE)       ? "no" :
		(types == L1D_FLUSH_FALLBACK)   ? "fallback displacement" :
		(types &  L1D_FLUSH_ORI)        ? (types & L1D_FLUSH_MTTRIG)
							? "ori+mttrig type"
							: "ori type" :
		(types &  L1D_FLUSH_MTTRIG)     ? "mttrig type"
						: "unknown");

	वापस 0;
पूर्ण

व्योम करो_entry_flush_fixups(क्रमागत l1d_flush_type types)
अणु
	/*
	 * The call to the fallback flush can not be safely patched in/out जबतक
	 * other CPUs are executing it. So call __करो_entry_flush_fixups() on one
	 * CPU जबतक all other CPUs spin in the stop machine core with पूर्णांकerrupts
	 * hard disabled.
	 */
	stop_machine(__करो_entry_flush_fixups, &types, शून्य);
पूर्ण

व्योम करो_rfi_flush_fixups(क्रमागत l1d_flush_type types)
अणु
	अचिन्हित पूर्णांक instrs[3], *dest;
	दीर्घ *start, *end;
	पूर्णांक i;

	start = PTRRELOC(&__start___rfi_flush_fixup);
	end = PTRRELOC(&__stop___rfi_flush_fixup);

	instrs[0] = 0x60000000; /* nop */
	instrs[1] = 0x60000000; /* nop */
	instrs[2] = 0x60000000; /* nop */

	अगर (types & L1D_FLUSH_FALLBACK)
		/* b .+16 to fallback flush */
		instrs[0] = 0x48000010;

	i = 0;
	अगर (types & L1D_FLUSH_ORI) अणु
		instrs[i++] = 0x63ff0000; /* ori 31,31,0 speculation barrier */
		instrs[i++] = 0x63de0000; /* ori 30,30,0 L1d flush*/
	पूर्ण

	अगर (types & L1D_FLUSH_MTTRIG)
		instrs[i++] = 0x7c12dba6; /* mtspr TRIG2,r0 (SPR #882) */

	क्रम (i = 0; start < end; start++, i++) अणु
		dest = (व्योम *)start + *start;

		pr_devel("patching dest %lx\n", (अचिन्हित दीर्घ)dest);

		patch_inकाष्ठाion((काष्ठा ppc_inst *)dest, ppc_inst(instrs[0]));
		patch_inकाष्ठाion((काष्ठा ppc_inst *)(dest + 1), ppc_inst(instrs[1]));
		patch_inकाष्ठाion((काष्ठा ppc_inst *)(dest + 2), ppc_inst(instrs[2]));
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "rfi-flush: patched %d locations (%s flush)\n", i,
		(types == L1D_FLUSH_NONE)       ? "no" :
		(types == L1D_FLUSH_FALLBACK)   ? "fallback displacement" :
		(types &  L1D_FLUSH_ORI)        ? (types & L1D_FLUSH_MTTRIG)
							? "ori+mttrig type"
							: "ori type" :
		(types &  L1D_FLUSH_MTTRIG)     ? "mttrig type"
						: "unknown");
पूर्ण

व्योम करो_barrier_nospec_fixups_range(bool enable, व्योम *fixup_start, व्योम *fixup_end)
अणु
	अचिन्हित पूर्णांक instr, *dest;
	दीर्घ *start, *end;
	पूर्णांक i;

	start = fixup_start;
	end = fixup_end;

	instr = 0x60000000; /* nop */

	अगर (enable) अणु
		pr_info("barrier-nospec: using ORI speculation barrier\n");
		instr = 0x63ff0000; /* ori 31,31,0 speculation barrier */
	पूर्ण

	क्रम (i = 0; start < end; start++, i++) अणु
		dest = (व्योम *)start + *start;

		pr_devel("patching dest %lx\n", (अचिन्हित दीर्घ)dest);
		patch_inकाष्ठाion((काष्ठा ppc_inst *)dest, ppc_inst(instr));
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "barrier-nospec: patched %d locations\n", i);
पूर्ण

#पूर्ण_अगर /* CONFIG_PPC_BOOK3S_64 */

#अगर_घोषित CONFIG_PPC_BARRIER_NOSPEC
व्योम करो_barrier_nospec_fixups(bool enable)
अणु
	व्योम *start, *end;

	start = PTRRELOC(&__start___barrier_nospec_fixup);
	end = PTRRELOC(&__stop___barrier_nospec_fixup);

	करो_barrier_nospec_fixups_range(enable, start, end);
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_BARRIER_NOSPEC */

#अगर_घोषित CONFIG_PPC_FSL_BOOK3E
व्योम करो_barrier_nospec_fixups_range(bool enable, व्योम *fixup_start, व्योम *fixup_end)
अणु
	अचिन्हित पूर्णांक instr[2], *dest;
	दीर्घ *start, *end;
	पूर्णांक i;

	start = fixup_start;
	end = fixup_end;

	instr[0] = PPC_INST_NOP;
	instr[1] = PPC_INST_NOP;

	अगर (enable) अणु
		pr_info("barrier-nospec: using isync; sync as speculation barrier\n");
		instr[0] = PPC_INST_ISYNC;
		instr[1] = PPC_INST_SYNC;
	पूर्ण

	क्रम (i = 0; start < end; start++, i++) अणु
		dest = (व्योम *)start + *start;

		pr_devel("patching dest %lx\n", (अचिन्हित दीर्घ)dest);
		patch_inकाष्ठाion((काष्ठा ppc_inst *)dest, ppc_inst(instr[0]));
		patch_inकाष्ठाion((काष्ठा ppc_inst *)(dest + 1), ppc_inst(instr[1]));
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "barrier-nospec: patched %d locations\n", i);
पूर्ण

अटल व्योम patch_btb_flush_section(दीर्घ *curr)
अणु
	अचिन्हित पूर्णांक *start, *end;

	start = (व्योम *)curr + *curr;
	end = (व्योम *)curr + *(curr + 1);
	क्रम (; start < end; start++) अणु
		pr_devel("patching dest %lx\n", (अचिन्हित दीर्घ)start);
		patch_inकाष्ठाion((काष्ठा ppc_inst *)start, ppc_inst(PPC_INST_NOP));
	पूर्ण
पूर्ण

व्योम करो_btb_flush_fixups(व्योम)
अणु
	दीर्घ *start, *end;

	start = PTRRELOC(&__start__btb_flush_fixup);
	end = PTRRELOC(&__stop__btb_flush_fixup);

	क्रम (; start < end; start += 2)
		patch_btb_flush_section(start);
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_FSL_BOOK3E */

व्योम करो_lwsync_fixups(अचिन्हित दीर्घ value, व्योम *fixup_start, व्योम *fixup_end)
अणु
	दीर्घ *start, *end;
	काष्ठा ppc_inst *dest;

	अगर (!(value & CPU_FTR_LWSYNC))
		वापस ;

	start = fixup_start;
	end = fixup_end;

	क्रम (; start < end; start++) अणु
		dest = (व्योम *)start + *start;
		raw_patch_inकाष्ठाion(dest, ppc_inst(PPC_INST_LWSYNC));
	पूर्ण
पूर्ण

अटल व्योम करो_final_fixups(व्योम)
अणु
#अगर defined(CONFIG_PPC64) && defined(CONFIG_RELOCATABLE)
	काष्ठा ppc_inst inst, *src, *dest, *end;

	अगर (PHYSICAL_START == 0)
		वापस;

	src = (काष्ठा ppc_inst *)(KERNELBASE + PHYSICAL_START);
	dest = (काष्ठा ppc_inst *)KERNELBASE;
	end = (व्योम *)src + (__end_पूर्णांकerrupts - _stext);

	जबतक (src < end) अणु
		inst = ppc_inst_पढ़ो(src);
		raw_patch_inकाष्ठाion(dest, inst);
		src = ppc_inst_next(src, src);
		dest = ppc_inst_next(dest, dest);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल अचिन्हित दीर्घ __initdata saved_cpu_features;
अटल अचिन्हित पूर्णांक __initdata saved_mmu_features;
#अगर_घोषित CONFIG_PPC64
अटल अचिन्हित दीर्घ __initdata saved_firmware_features;
#पूर्ण_अगर

व्योम __init apply_feature_fixups(व्योम)
अणु
	काष्ठा cpu_spec *spec = PTRRELOC(*PTRRELOC(&cur_cpu_spec));

	*PTRRELOC(&saved_cpu_features) = spec->cpu_features;
	*PTRRELOC(&saved_mmu_features) = spec->mmu_features;

	/*
	 * Apply the CPU-specअगरic and firmware specअगरic fixups to kernel text
	 * (nop out sections not relevant to this CPU or this firmware).
	 */
	करो_feature_fixups(spec->cpu_features,
			  PTRRELOC(&__start___ftr_fixup),
			  PTRRELOC(&__stop___ftr_fixup));

	करो_feature_fixups(spec->mmu_features,
			  PTRRELOC(&__start___mmu_ftr_fixup),
			  PTRRELOC(&__stop___mmu_ftr_fixup));

	करो_lwsync_fixups(spec->cpu_features,
			 PTRRELOC(&__start___lwsync_fixup),
			 PTRRELOC(&__stop___lwsync_fixup));

#अगर_घोषित CONFIG_PPC64
	saved_firmware_features = घातerpc_firmware_features;
	करो_feature_fixups(घातerpc_firmware_features,
			  &__start___fw_ftr_fixup, &__stop___fw_ftr_fixup);
#पूर्ण_अगर
	करो_final_fixups();
पूर्ण

व्योम __init setup_feature_keys(व्योम)
अणु
	/*
	 * Initialise jump label. This causes all the cpu/mmu_has_feature()
	 * checks to take on their correct polarity based on the current set of
	 * CPU/MMU features.
	 */
	jump_label_init();
	cpu_feature_keys_init();
	mmu_feature_keys_init();
पूर्ण

अटल पूर्णांक __init check_features(व्योम)
अणु
	WARN(saved_cpu_features != cur_cpu_spec->cpu_features,
	     "CPU features changed after feature patching!\n");
	WARN(saved_mmu_features != cur_cpu_spec->mmu_features,
	     "MMU features changed after feature patching!\n");
#अगर_घोषित CONFIG_PPC64
	WARN(saved_firmware_features != घातerpc_firmware_features,
	     "Firmware features changed after feature patching!\n");
#पूर्ण_अगर

	वापस 0;
पूर्ण
late_initcall(check_features);

#अगर_घोषित CONFIG_FTR_FIXUP_SELFTEST

#घोषणा check(x)	\
	अगर (!(x)) prपूर्णांकk("feature-fixups: test failed at line %d\n", __LINE__);

/* This must be after the text it fixes up, vmlinux.lds.S enक्रमces that aपंचांग */
अटल काष्ठा fixup_entry fixup;

अटल दीर्घ calc_offset(काष्ठा fixup_entry *entry, अचिन्हित पूर्णांक *p)
अणु
	वापस (अचिन्हित दीर्घ)p - (अचिन्हित दीर्घ)entry;
पूर्ण

अटल व्योम test_basic_patching(व्योम)
अणु
	बाह्य अचिन्हित पूर्णांक ftr_fixup_test1[];
	बाह्य अचिन्हित पूर्णांक end_ftr_fixup_test1[];
	बाह्य अचिन्हित पूर्णांक ftr_fixup_test1_orig[];
	बाह्य अचिन्हित पूर्णांक ftr_fixup_test1_expected[];
	पूर्णांक size = 4 * (end_ftr_fixup_test1 - ftr_fixup_test1);

	fixup.value = fixup.mask = 8;
	fixup.start_off = calc_offset(&fixup, ftr_fixup_test1 + 1);
	fixup.end_off = calc_offset(&fixup, ftr_fixup_test1 + 2);
	fixup.alt_start_off = fixup.alt_end_off = 0;

	/* Sanity check */
	check(स_भेद(ftr_fixup_test1, ftr_fixup_test1_orig, size) == 0);

	/* Check we करोn't patch अगर the value matches */
	patch_feature_section(8, &fixup);
	check(स_भेद(ftr_fixup_test1, ftr_fixup_test1_orig, size) == 0);

	/* Check we करो patch अगर the value करोesn't match */
	patch_feature_section(0, &fixup);
	check(स_भेद(ftr_fixup_test1, ftr_fixup_test1_expected, size) == 0);

	/* Check we करो patch अगर the mask करोesn't match */
	स_नकल(ftr_fixup_test1, ftr_fixup_test1_orig, size);
	check(स_भेद(ftr_fixup_test1, ftr_fixup_test1_orig, size) == 0);
	patch_feature_section(~8, &fixup);
	check(स_भेद(ftr_fixup_test1, ftr_fixup_test1_expected, size) == 0);
पूर्ण

अटल व्योम test_alternative_patching(व्योम)
अणु
	बाह्य अचिन्हित पूर्णांक ftr_fixup_test2[];
	बाह्य अचिन्हित पूर्णांक end_ftr_fixup_test2[];
	बाह्य अचिन्हित पूर्णांक ftr_fixup_test2_orig[];
	बाह्य अचिन्हित पूर्णांक ftr_fixup_test2_alt[];
	बाह्य अचिन्हित पूर्णांक ftr_fixup_test2_expected[];
	पूर्णांक size = 4 * (end_ftr_fixup_test2 - ftr_fixup_test2);

	fixup.value = fixup.mask = 0xF;
	fixup.start_off = calc_offset(&fixup, ftr_fixup_test2 + 1);
	fixup.end_off = calc_offset(&fixup, ftr_fixup_test2 + 2);
	fixup.alt_start_off = calc_offset(&fixup, ftr_fixup_test2_alt);
	fixup.alt_end_off = calc_offset(&fixup, ftr_fixup_test2_alt + 1);

	/* Sanity check */
	check(स_भेद(ftr_fixup_test2, ftr_fixup_test2_orig, size) == 0);

	/* Check we करोn't patch अगर the value matches */
	patch_feature_section(0xF, &fixup);
	check(स_भेद(ftr_fixup_test2, ftr_fixup_test2_orig, size) == 0);

	/* Check we करो patch अगर the value करोesn't match */
	patch_feature_section(0, &fixup);
	check(स_भेद(ftr_fixup_test2, ftr_fixup_test2_expected, size) == 0);

	/* Check we करो patch अगर the mask करोesn't match */
	स_नकल(ftr_fixup_test2, ftr_fixup_test2_orig, size);
	check(स_भेद(ftr_fixup_test2, ftr_fixup_test2_orig, size) == 0);
	patch_feature_section(~0xF, &fixup);
	check(स_भेद(ftr_fixup_test2, ftr_fixup_test2_expected, size) == 0);
पूर्ण

अटल व्योम test_alternative_हाल_too_big(व्योम)
अणु
	बाह्य अचिन्हित पूर्णांक ftr_fixup_test3[];
	बाह्य अचिन्हित पूर्णांक end_ftr_fixup_test3[];
	बाह्य अचिन्हित पूर्णांक ftr_fixup_test3_orig[];
	बाह्य अचिन्हित पूर्णांक ftr_fixup_test3_alt[];
	पूर्णांक size = 4 * (end_ftr_fixup_test3 - ftr_fixup_test3);

	fixup.value = fixup.mask = 0xC;
	fixup.start_off = calc_offset(&fixup, ftr_fixup_test3 + 1);
	fixup.end_off = calc_offset(&fixup, ftr_fixup_test3 + 2);
	fixup.alt_start_off = calc_offset(&fixup, ftr_fixup_test3_alt);
	fixup.alt_end_off = calc_offset(&fixup, ftr_fixup_test3_alt + 2);

	/* Sanity check */
	check(स_भेद(ftr_fixup_test3, ftr_fixup_test3_orig, size) == 0);

	/* Expect nothing to be patched, and the error वापसed to us */
	check(patch_feature_section(0xF, &fixup) == 1);
	check(स_भेद(ftr_fixup_test3, ftr_fixup_test3_orig, size) == 0);
	check(patch_feature_section(0, &fixup) == 1);
	check(स_भेद(ftr_fixup_test3, ftr_fixup_test3_orig, size) == 0);
	check(patch_feature_section(~0xF, &fixup) == 1);
	check(स_भेद(ftr_fixup_test3, ftr_fixup_test3_orig, size) == 0);
पूर्ण

अटल व्योम test_alternative_हाल_too_small(व्योम)
अणु
	बाह्य अचिन्हित पूर्णांक ftr_fixup_test4[];
	बाह्य अचिन्हित पूर्णांक end_ftr_fixup_test4[];
	बाह्य अचिन्हित पूर्णांक ftr_fixup_test4_orig[];
	बाह्य अचिन्हित पूर्णांक ftr_fixup_test4_alt[];
	बाह्य अचिन्हित पूर्णांक ftr_fixup_test4_expected[];
	पूर्णांक size = 4 * (end_ftr_fixup_test4 - ftr_fixup_test4);
	अचिन्हित दीर्घ flag;

	/* Check a high-bit flag */
	flag = 1UL << ((माप(अचिन्हित दीर्घ) - 1) * 8);
	fixup.value = fixup.mask = flag;
	fixup.start_off = calc_offset(&fixup, ftr_fixup_test4 + 1);
	fixup.end_off = calc_offset(&fixup, ftr_fixup_test4 + 5);
	fixup.alt_start_off = calc_offset(&fixup, ftr_fixup_test4_alt);
	fixup.alt_end_off = calc_offset(&fixup, ftr_fixup_test4_alt + 2);

	/* Sanity check */
	check(स_भेद(ftr_fixup_test4, ftr_fixup_test4_orig, size) == 0);

	/* Check we करोn't patch अगर the value matches */
	patch_feature_section(flag, &fixup);
	check(स_भेद(ftr_fixup_test4, ftr_fixup_test4_orig, size) == 0);

	/* Check we करो patch अगर the value करोesn't match */
	patch_feature_section(0, &fixup);
	check(स_भेद(ftr_fixup_test4, ftr_fixup_test4_expected, size) == 0);

	/* Check we करो patch अगर the mask करोesn't match */
	स_नकल(ftr_fixup_test4, ftr_fixup_test4_orig, size);
	check(स_भेद(ftr_fixup_test4, ftr_fixup_test4_orig, size) == 0);
	patch_feature_section(~flag, &fixup);
	check(स_भेद(ftr_fixup_test4, ftr_fixup_test4_expected, size) == 0);
पूर्ण

अटल व्योम test_alternative_हाल_with_branch(व्योम)
अणु
	बाह्य अचिन्हित पूर्णांक ftr_fixup_test5[];
	बाह्य अचिन्हित पूर्णांक end_ftr_fixup_test5[];
	बाह्य अचिन्हित पूर्णांक ftr_fixup_test5_expected[];
	पूर्णांक size = 4 * (end_ftr_fixup_test5 - ftr_fixup_test5);

	check(स_भेद(ftr_fixup_test5, ftr_fixup_test5_expected, size) == 0);
पूर्ण

अटल व्योम test_alternative_हाल_with_बाह्यal_branch(व्योम)
अणु
	बाह्य अचिन्हित पूर्णांक ftr_fixup_test6[];
	बाह्य अचिन्हित पूर्णांक end_ftr_fixup_test6[];
	बाह्य अचिन्हित पूर्णांक ftr_fixup_test6_expected[];
	पूर्णांक size = 4 * (end_ftr_fixup_test6 - ftr_fixup_test6);

	check(स_भेद(ftr_fixup_test6, ftr_fixup_test6_expected, size) == 0);
पूर्ण

अटल व्योम test_alternative_हाल_with_branch_to_end(व्योम)
अणु
	बाह्य अचिन्हित पूर्णांक ftr_fixup_test7[];
	बाह्य अचिन्हित पूर्णांक end_ftr_fixup_test7[];
	बाह्य अचिन्हित पूर्णांक ftr_fixup_test7_expected[];
	पूर्णांक size = 4 * (end_ftr_fixup_test7 - ftr_fixup_test7);

	check(स_भेद(ftr_fixup_test7, ftr_fixup_test7_expected, size) == 0);
पूर्ण

अटल व्योम test_cpu_macros(व्योम)
अणु
	बाह्य u8 ftr_fixup_test_FTR_macros[];
	बाह्य u8 ftr_fixup_test_FTR_macros_expected[];
	अचिन्हित दीर्घ size = ftr_fixup_test_FTR_macros_expected -
			     ftr_fixup_test_FTR_macros;

	/* The fixups have alपढ़ोy been करोne क्रम us during boot */
	check(स_भेद(ftr_fixup_test_FTR_macros,
		     ftr_fixup_test_FTR_macros_expected, size) == 0);
पूर्ण

अटल व्योम test_fw_macros(व्योम)
अणु
#अगर_घोषित CONFIG_PPC64
	बाह्य u8 ftr_fixup_test_FW_FTR_macros[];
	बाह्य u8 ftr_fixup_test_FW_FTR_macros_expected[];
	अचिन्हित दीर्घ size = ftr_fixup_test_FW_FTR_macros_expected -
			     ftr_fixup_test_FW_FTR_macros;

	/* The fixups have alपढ़ोy been करोne क्रम us during boot */
	check(स_भेद(ftr_fixup_test_FW_FTR_macros,
		     ftr_fixup_test_FW_FTR_macros_expected, size) == 0);
#पूर्ण_अगर
पूर्ण

अटल व्योम test_lwsync_macros(व्योम)
अणु
	बाह्य u8 lwsync_fixup_test[];
	बाह्य u8 end_lwsync_fixup_test[];
	बाह्य u8 lwsync_fixup_test_expected_LWSYNC[];
	बाह्य u8 lwsync_fixup_test_expected_SYNC[];
	अचिन्हित दीर्घ size = end_lwsync_fixup_test -
			     lwsync_fixup_test;

	/* The fixups have alपढ़ोy been करोne क्रम us during boot */
	अगर (cur_cpu_spec->cpu_features & CPU_FTR_LWSYNC) अणु
		check(स_भेद(lwsync_fixup_test,
			     lwsync_fixup_test_expected_LWSYNC, size) == 0);
	पूर्ण अन्यथा अणु
		check(स_भेद(lwsync_fixup_test,
			     lwsync_fixup_test_expected_SYNC, size) == 0);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PPC64
अटल व्योम __init test_prefix_patching(व्योम)
अणु
	बाह्य अचिन्हित पूर्णांक ftr_fixup_prefix1[];
	बाह्य अचिन्हित पूर्णांक end_ftr_fixup_prefix1[];
	बाह्य अचिन्हित पूर्णांक ftr_fixup_prefix1_orig[];
	बाह्य अचिन्हित पूर्णांक ftr_fixup_prefix1_expected[];
	पूर्णांक size = माप(अचिन्हित पूर्णांक) * (end_ftr_fixup_prefix1 - ftr_fixup_prefix1);

	fixup.value = fixup.mask = 8;
	fixup.start_off = calc_offset(&fixup, ftr_fixup_prefix1 + 1);
	fixup.end_off = calc_offset(&fixup, ftr_fixup_prefix1 + 3);
	fixup.alt_start_off = fixup.alt_end_off = 0;

	/* Sanity check */
	check(स_भेद(ftr_fixup_prefix1, ftr_fixup_prefix1_orig, size) == 0);

	patch_feature_section(0, &fixup);
	check(स_भेद(ftr_fixup_prefix1, ftr_fixup_prefix1_expected, size) == 0);
	check(स_भेद(ftr_fixup_prefix1, ftr_fixup_prefix1_orig, size) != 0);
पूर्ण

अटल व्योम __init test_prefix_alt_patching(व्योम)
अणु
	बाह्य अचिन्हित पूर्णांक ftr_fixup_prefix2[];
	बाह्य अचिन्हित पूर्णांक end_ftr_fixup_prefix2[];
	बाह्य अचिन्हित पूर्णांक ftr_fixup_prefix2_orig[];
	बाह्य अचिन्हित पूर्णांक ftr_fixup_prefix2_expected[];
	बाह्य अचिन्हित पूर्णांक ftr_fixup_prefix2_alt[];
	पूर्णांक size = माप(अचिन्हित पूर्णांक) * (end_ftr_fixup_prefix2 - ftr_fixup_prefix2);

	fixup.value = fixup.mask = 8;
	fixup.start_off = calc_offset(&fixup, ftr_fixup_prefix2 + 1);
	fixup.end_off = calc_offset(&fixup, ftr_fixup_prefix2 + 3);
	fixup.alt_start_off = calc_offset(&fixup, ftr_fixup_prefix2_alt);
	fixup.alt_end_off = calc_offset(&fixup, ftr_fixup_prefix2_alt + 2);
	/* Sanity check */
	check(स_भेद(ftr_fixup_prefix2, ftr_fixup_prefix2_orig, size) == 0);

	patch_feature_section(0, &fixup);
	check(स_भेद(ftr_fixup_prefix2, ftr_fixup_prefix2_expected, size) == 0);
	check(स_भेद(ftr_fixup_prefix2, ftr_fixup_prefix2_orig, size) != 0);
पूर्ण

अटल व्योम __init test_prefix_word_alt_patching(व्योम)
अणु
	बाह्य अचिन्हित पूर्णांक ftr_fixup_prefix3[];
	बाह्य अचिन्हित पूर्णांक end_ftr_fixup_prefix3[];
	बाह्य अचिन्हित पूर्णांक ftr_fixup_prefix3_orig[];
	बाह्य अचिन्हित पूर्णांक ftr_fixup_prefix3_expected[];
	बाह्य अचिन्हित पूर्णांक ftr_fixup_prefix3_alt[];
	पूर्णांक size = माप(अचिन्हित पूर्णांक) * (end_ftr_fixup_prefix3 - ftr_fixup_prefix3);

	fixup.value = fixup.mask = 8;
	fixup.start_off = calc_offset(&fixup, ftr_fixup_prefix3 + 1);
	fixup.end_off = calc_offset(&fixup, ftr_fixup_prefix3 + 4);
	fixup.alt_start_off = calc_offset(&fixup, ftr_fixup_prefix3_alt);
	fixup.alt_end_off = calc_offset(&fixup, ftr_fixup_prefix3_alt + 3);
	/* Sanity check */
	check(स_भेद(ftr_fixup_prefix3, ftr_fixup_prefix3_orig, size) == 0);

	patch_feature_section(0, &fixup);
	check(स_भेद(ftr_fixup_prefix3, ftr_fixup_prefix3_expected, size) == 0);
	patch_feature_section(0, &fixup);
	check(स_भेद(ftr_fixup_prefix3, ftr_fixup_prefix3_orig, size) != 0);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम test_prefix_patching(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम test_prefix_alt_patching(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम test_prefix_word_alt_patching(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_PPC64 */

अटल पूर्णांक __init test_feature_fixups(व्योम)
अणु
	prपूर्णांकk(KERN_DEBUG "Running feature fixup self-tests ...\n");

	test_basic_patching();
	test_alternative_patching();
	test_alternative_हाल_too_big();
	test_alternative_हाल_too_small();
	test_alternative_हाल_with_branch();
	test_alternative_हाल_with_बाह्यal_branch();
	test_alternative_हाल_with_branch_to_end();
	test_cpu_macros();
	test_fw_macros();
	test_lwsync_macros();
	test_prefix_patching();
	test_prefix_alt_patching();
	test_prefix_word_alt_patching();

	वापस 0;
पूर्ण
late_initcall(test_feature_fixups);

#पूर्ण_अगर /* CONFIG_FTR_FIXUP_SELFTEST */
