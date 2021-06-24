<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Code क्रम replacing ftrace calls with jumps.
 *
 * Copyright (C) 2007-2008 Steven Rostedt <srostedt@redhat.com>
 *
 * Thanks goes out to P.A. Semi, Inc क्रम supplying me with a PPC64 box.
 *
 * Added function graph tracer code, taken from x86 that was written
 * by Frederic Weisbecker, and ported to PPC by Steven Rostedt.
 *
 */

#घोषणा pr_fmt(fmt) "ftrace-powerpc: " fmt

#समावेश <linux/spinlock.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/module.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/percpu.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>

#समावेश <यंत्र/यंत्र-prototypes.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/code-patching.h>
#समावेश <यंत्र/ftrace.h>
#समावेश <यंत्र/syscall.h>
#समावेश <यंत्र/inst.h>


#अगर_घोषित CONFIG_DYNAMIC_FTRACE

/*
 * We generally only have a single दीर्घ_branch tramp and at most 2 or 3 plt
 * tramps generated. But, we करोn't use the plt tramps currently. We also allot
 * 2 tramps after .text and .init.text. So, we only end up with around 3 usable
 * tramps in total. Set aside 8 just to be sure.
 */
#घोषणा	NUM_FTRACE_TRAMPS	8
अटल अचिन्हित दीर्घ ftrace_tramps[NUM_FTRACE_TRAMPS];

अटल काष्ठा ppc_inst
ftrace_call_replace(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ addr, पूर्णांक link)
अणु
	काष्ठा ppc_inst op;

	addr = ppc_function_entry((व्योम *)addr);

	/* अगर (link) set op to 'bl' else 'b' */
	create_branch(&op, (काष्ठा ppc_inst *)ip, addr, link ? 1 : 0);

	वापस op;
पूर्ण

अटल पूर्णांक
ftrace_modअगरy_code(अचिन्हित दीर्घ ip, काष्ठा ppc_inst old, काष्ठा ppc_inst new)
अणु
	काष्ठा ppc_inst replaced;

	/*
	 * Note:
	 * We are paranoid about modअगरying text, as अगर a bug was to happen, it
	 * could cause us to पढ़ो or ग_लिखो to someplace that could cause harm.
	 * Carefully पढ़ो and modअगरy the code with probe_kernel_*(), and make
	 * sure what we पढ़ो is what we expected it to be beक्रमe modअगरying it.
	 */

	/* पढ़ो the text we want to modअगरy */
	अगर (copy_inst_from_kernel_nofault(&replaced, (व्योम *)ip))
		वापस -EFAULT;

	/* Make sure it is what we expect it to be */
	अगर (!ppc_inst_equal(replaced, old)) अणु
		pr_err("%p: replaced (%s) != old (%s)",
		(व्योम *)ip, ppc_inst_as_str(replaced), ppc_inst_as_str(old));
		वापस -EINVAL;
	पूर्ण

	/* replace the text with the new text */
	अगर (patch_inकाष्ठाion((काष्ठा ppc_inst *)ip, new))
		वापस -EPERM;

	वापस 0;
पूर्ण

/*
 * Helper functions that are the same क्रम both PPC64 and PPC32.
 */
अटल पूर्णांक test_24bit_addr(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ addr)
अणु
	काष्ठा ppc_inst op;
	addr = ppc_function_entry((व्योम *)addr);

	/* use the create_branch to verअगरy that this offset can be branched */
	वापस create_branch(&op, (काष्ठा ppc_inst *)ip, addr, 0) == 0;
पूर्ण

अटल पूर्णांक is_bl_op(काष्ठा ppc_inst op)
अणु
	वापस (ppc_inst_val(op) & 0xfc000003) == 0x48000001;
पूर्ण

अटल पूर्णांक is_b_op(काष्ठा ppc_inst op)
अणु
	वापस (ppc_inst_val(op) & 0xfc000003) == 0x48000000;
पूर्ण

अटल अचिन्हित दीर्घ find_bl_target(अचिन्हित दीर्घ ip, काष्ठा ppc_inst op)
अणु
	पूर्णांक offset;

	offset = (ppc_inst_val(op) & 0x03fffffc);
	/* make it चिन्हित */
	अगर (offset & 0x02000000)
		offset |= 0xfe000000;

	वापस ip + (दीर्घ)offset;
पूर्ण

#अगर_घोषित CONFIG_MODULES
#अगर_घोषित CONFIG_PPC64
अटल पूर्णांक
__ftrace_make_nop(काष्ठा module *mod,
		  काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ entry, ptr, tramp;
	अचिन्हित दीर्घ ip = rec->ip;
	काष्ठा ppc_inst op, pop;

	/* पढ़ो where this goes */
	अगर (copy_inst_from_kernel_nofault(&op, (व्योम *)ip)) अणु
		pr_err("Fetching opcode failed.\n");
		वापस -EFAULT;
	पूर्ण

	/* Make sure that that this is still a 24bit jump */
	अगर (!is_bl_op(op)) अणु
		pr_err("Not expected bl: opcode is %s\n", ppc_inst_as_str(op));
		वापस -EINVAL;
	पूर्ण

	/* lets find where the poपूर्णांकer goes */
	tramp = find_bl_target(ip, op);

	pr_devel("ip:%lx jumps to %lx", ip, tramp);

	अगर (module_trampoline_target(mod, tramp, &ptr)) अणु
		pr_err("Failed to get trampoline target\n");
		वापस -EFAULT;
	पूर्ण

	pr_devel("trampoline target %lx", ptr);

	entry = ppc_global_function_entry((व्योम *)addr);
	/* This should match what was called */
	अगर (ptr != entry) अणु
		pr_err("addr %lx does not match expected %lx\n", ptr, entry);
		वापस -EINVAL;
	पूर्ण

#अगर_घोषित CONFIG_MPROखाता_KERNEL
	/* When using -mkernel_profile there is no load to jump over */
	pop = ppc_inst(PPC_INST_NOP);

	अगर (copy_inst_from_kernel_nofault(&op, (व्योम *)(ip - 4))) अणु
		pr_err("Fetching instruction at %lx failed.\n", ip - 4);
		वापस -EFAULT;
	पूर्ण

	/* We expect either a mflr r0, or a std r0, LRSAVE(r1) */
	अगर (!ppc_inst_equal(op, ppc_inst(PPC_INST_MFLR)) &&
	    !ppc_inst_equal(op, ppc_inst(PPC_INST_STD_LR))) अणु
		pr_err("Unexpected instruction %s around bl _mcount\n",
		       ppc_inst_as_str(op));
		वापस -EINVAL;
	पूर्ण
#अन्यथा
	/*
	 * Our original call site looks like:
	 *
	 * bl <tramp>
	 * ld r2,XX(r1)
	 *
	 * Milton Miller poपूर्णांकed out that we can not simply nop the branch.
	 * If a task was preempted when calling a trace function, the nops
	 * will हटाओ the way to restore the TOC in r2 and the r2 TOC will
	 * get corrupted.
	 *
	 * Use a b +8 to jump over the load.
	 */

	pop = ppc_inst(PPC_INST_BRANCH | 8);	/* b +8 */

	/*
	 * Check what is in the next inकाष्ठाion. We can see ld r2,40(r1), but
	 * on first pass after boot we will see mflr r0.
	 */
	अगर (copy_inst_from_kernel_nofault(&op, (व्योम *)(ip + 4))) अणु
		pr_err("Fetching op failed.\n");
		वापस -EFAULT;
	पूर्ण

	अगर (!ppc_inst_equal(op,  ppc_inst(PPC_INST_LD_TOC))) अणु
		pr_err("Expected %08x found %s\n", PPC_INST_LD_TOC, ppc_inst_as_str(op));
		वापस -EINVAL;
	पूर्ण
#पूर्ण_अगर /* CONFIG_MPROखाता_KERNEL */

	अगर (patch_inकाष्ठाion((काष्ठा ppc_inst *)ip, pop)) अणु
		pr_err("Patching NOP failed.\n");
		वापस -EPERM;
	पूर्ण

	वापस 0;
पूर्ण

#अन्यथा /* !PPC64 */
अटल पूर्णांक
__ftrace_make_nop(काष्ठा module *mod,
		  काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ addr)
अणु
	काष्ठा ppc_inst op;
	अचिन्हित पूर्णांक jmp[4];
	अचिन्हित दीर्घ ip = rec->ip;
	अचिन्हित दीर्घ tramp;

	अगर (copy_from_kernel_nofault(&op, (व्योम *)ip, MCOUNT_INSN_SIZE))
		वापस -EFAULT;

	/* Make sure that that this is still a 24bit jump */
	अगर (!is_bl_op(op)) अणु
		pr_err("Not expected bl: opcode is %s\n", ppc_inst_as_str(op));
		वापस -EINVAL;
	पूर्ण

	/* lets find where the poपूर्णांकer goes */
	tramp = find_bl_target(ip, op);

	/*
	 * On PPC32 the trampoline looks like:
	 *  0x3d, 0x80, 0x00, 0x00  lis r12,sym@ha
	 *  0x39, 0x8c, 0x00, 0x00  addi r12,r12,sym@l
	 *  0x7d, 0x89, 0x03, 0xa6  mtctr r12
	 *  0x4e, 0x80, 0x04, 0x20  bctr
	 */

	pr_devel("ip:%lx jumps to %lx", ip, tramp);

	/* Find where the trampoline jumps to */
	अगर (copy_from_kernel_nofault(jmp, (व्योम *)tramp, माप(jmp))) अणु
		pr_err("Failed to read %lx\n", tramp);
		वापस -EFAULT;
	पूर्ण

	pr_devel(" %08x %08x ", jmp[0], jmp[1]);

	/* verअगरy that this is what we expect it to be */
	अगर (((jmp[0] & 0xffff0000) != 0x3d800000) ||
	    ((jmp[1] & 0xffff0000) != 0x398c0000) ||
	    (jmp[2] != 0x7d8903a6) ||
	    (jmp[3] != 0x4e800420)) अणु
		pr_err("Not a trampoline\n");
		वापस -EINVAL;
	पूर्ण

	tramp = (jmp[1] & 0xffff) |
		((jmp[0] & 0xffff) << 16);
	अगर (tramp & 0x8000)
		tramp -= 0x10000;

	pr_devel(" %lx ", tramp);

	अगर (tramp != addr) अणु
		pr_err("Trampoline location %08lx does not match addr\n",
		       tramp);
		वापस -EINVAL;
	पूर्ण

	op = ppc_inst(PPC_INST_NOP);

	अगर (patch_inकाष्ठाion((काष्ठा ppc_inst *)ip, op))
		वापस -EPERM;

	वापस 0;
पूर्ण
#पूर्ण_अगर /* PPC64 */
#पूर्ण_अगर /* CONFIG_MODULES */

अटल अचिन्हित दीर्घ find_ftrace_tramp(अचिन्हित दीर्घ ip)
अणु
	पूर्णांक i;
	काष्ठा ppc_inst instr;

	/*
	 * We have the compiler generated दीर्घ_branch tramps at the end
	 * and we prefer those
	 */
	क्रम (i = NUM_FTRACE_TRAMPS - 1; i >= 0; i--)
		अगर (!ftrace_tramps[i])
			जारी;
		अन्यथा अगर (create_branch(&instr, (व्योम *)ip,
				       ftrace_tramps[i], 0) == 0)
			वापस ftrace_tramps[i];

	वापस 0;
पूर्ण

अटल पूर्णांक add_ftrace_tramp(अचिन्हित दीर्घ tramp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_FTRACE_TRAMPS; i++)
		अगर (!ftrace_tramps[i]) अणु
			ftrace_tramps[i] = tramp;
			वापस 0;
		पूर्ण

	वापस -1;
पूर्ण

/*
 * If this is a compiler generated दीर्घ_branch trampoline (essentially, a
 * trampoline that has a branch to _mcount()), we re-ग_लिखो the branch to
 * instead go to ftrace_[regs_]caller() and note करोwn the location of this
 * trampoline.
 */
अटल पूर्णांक setup_mcount_compiler_tramp(अचिन्हित दीर्घ tramp)
अणु
	पूर्णांक i;
	काष्ठा ppc_inst op;
	अचिन्हित दीर्घ ptr;
	काष्ठा ppc_inst instr;
	अटल अचिन्हित दीर्घ ftrace_plt_tramps[NUM_FTRACE_TRAMPS];

	/* Is this a known दीर्घ jump tramp? */
	क्रम (i = 0; i < NUM_FTRACE_TRAMPS; i++)
		अगर (!ftrace_tramps[i])
			अवरोध;
		अन्यथा अगर (ftrace_tramps[i] == tramp)
			वापस 0;

	/* Is this a known plt tramp? */
	क्रम (i = 0; i < NUM_FTRACE_TRAMPS; i++)
		अगर (!ftrace_plt_tramps[i])
			अवरोध;
		अन्यथा अगर (ftrace_plt_tramps[i] == tramp)
			वापस -1;

	/* New trampoline -- पढ़ो where this goes */
	अगर (copy_inst_from_kernel_nofault(&op, (व्योम *)tramp)) अणु
		pr_debug("Fetching opcode failed.\n");
		वापस -1;
	पूर्ण

	/* Is this a 24 bit branch? */
	अगर (!is_b_op(op)) अणु
		pr_debug("Trampoline is not a long branch tramp.\n");
		वापस -1;
	पूर्ण

	/* lets find where the poपूर्णांकer goes */
	ptr = find_bl_target(tramp, op);

	अगर (ptr != ppc_global_function_entry((व्योम *)_mcount)) अणु
		pr_debug("Trampoline target %p is not _mcount\n", (व्योम *)ptr);
		वापस -1;
	पूर्ण

	/* Let's re-ग_लिखो the tramp to go to ftrace_[regs_]caller */
#अगर_घोषित CONFIG_DYNAMIC_FTRACE_WITH_REGS
	ptr = ppc_global_function_entry((व्योम *)ftrace_regs_caller);
#अन्यथा
	ptr = ppc_global_function_entry((व्योम *)ftrace_caller);
#पूर्ण_अगर
	अगर (create_branch(&instr, (व्योम *)tramp, ptr, 0)) अणु
		pr_debug("%ps is not reachable from existing mcount tramp\n",
				(व्योम *)ptr);
		वापस -1;
	पूर्ण

	अगर (patch_branch((काष्ठा ppc_inst *)tramp, ptr, 0)) अणु
		pr_debug("REL24 out of range!\n");
		वापस -1;
	पूर्ण

	अगर (add_ftrace_tramp(tramp)) अणु
		pr_debug("No tramp locations left\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __ftrace_make_nop_kernel(काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ tramp, ip = rec->ip;
	काष्ठा ppc_inst op;

	/* Read where this goes */
	अगर (copy_inst_from_kernel_nofault(&op, (व्योम *)ip)) अणु
		pr_err("Fetching opcode failed.\n");
		वापस -EFAULT;
	पूर्ण

	/* Make sure that that this is still a 24bit jump */
	अगर (!is_bl_op(op)) अणु
		pr_err("Not expected bl: opcode is %s\n", ppc_inst_as_str(op));
		वापस -EINVAL;
	पूर्ण

	/* Let's find where the poपूर्णांकer goes */
	tramp = find_bl_target(ip, op);

	pr_devel("ip:%lx jumps to %lx", ip, tramp);

	अगर (setup_mcount_compiler_tramp(tramp)) अणु
		/* Are other trampolines reachable? */
		अगर (!find_ftrace_tramp(ip)) अणु
			pr_err("No ftrace trampolines reachable from %ps\n",
					(व्योम *)ip);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (patch_inकाष्ठाion((काष्ठा ppc_inst *)ip, ppc_inst(PPC_INST_NOP))) अणु
		pr_err("Patching NOP failed.\n");
		वापस -EPERM;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ftrace_make_nop(काष्ठा module *mod,
		    काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ ip = rec->ip;
	काष्ठा ppc_inst old, new;

	/*
	 * If the calling address is more that 24 bits away,
	 * then we had to use a trampoline to make the call.
	 * Otherwise just update the call site.
	 */
	अगर (test_24bit_addr(ip, addr)) अणु
		/* within range */
		old = ftrace_call_replace(ip, addr, 1);
		new = ppc_inst(PPC_INST_NOP);
		वापस ftrace_modअगरy_code(ip, old, new);
	पूर्ण अन्यथा अगर (core_kernel_text(ip))
		वापस __ftrace_make_nop_kernel(rec, addr);

#अगर_घोषित CONFIG_MODULES
	/*
	 * Out of range jumps are called from modules.
	 * We should either alपढ़ोy have a poपूर्णांकer to the module
	 * or it has been passed in.
	 */
	अगर (!rec->arch.mod) अणु
		अगर (!mod) अणु
			pr_err("No module loaded addr=%lx\n", addr);
			वापस -EFAULT;
		पूर्ण
		rec->arch.mod = mod;
	पूर्ण अन्यथा अगर (mod) अणु
		अगर (mod != rec->arch.mod) अणु
			pr_err("Record mod %p not equal to passed in mod %p\n",
			       rec->arch.mod, mod);
			वापस -EINVAL;
		पूर्ण
		/* nothing to करो अगर mod == rec->arch.mod */
	पूर्ण अन्यथा
		mod = rec->arch.mod;

	वापस __ftrace_make_nop(mod, rec, addr);
#अन्यथा
	/* We should not get here without modules */
	वापस -EINVAL;
#पूर्ण_अगर /* CONFIG_MODULES */
पूर्ण

#अगर_घोषित CONFIG_MODULES
#अगर_घोषित CONFIG_PPC64
/*
 * Examine the existing inकाष्ठाions क्रम __ftrace_make_call.
 * They should effectively be a NOP, and follow क्रमmal स्थिरraपूर्णांकs,
 * depending on the ABI. Return false अगर they करोn't.
 */
#अगर_अघोषित CONFIG_MPROखाता_KERNEL
अटल पूर्णांक
expected_nop_sequence(व्योम *ip, काष्ठा ppc_inst op0, काष्ठा ppc_inst op1)
अणु
	/*
	 * We expect to see:
	 *
	 * b +8
	 * ld r2,XX(r1)
	 *
	 * The load offset is dअगरferent depending on the ABI. For simplicity
	 * just mask it out when करोing the compare.
	 */
	अगर (!ppc_inst_equal(op0, ppc_inst(0x48000008)) ||
	    (ppc_inst_val(op1) & 0xffff0000) != 0xe8410000)
		वापस 0;
	वापस 1;
पूर्ण
#अन्यथा
अटल पूर्णांक
expected_nop_sequence(व्योम *ip, काष्ठा ppc_inst op0, काष्ठा ppc_inst op1)
अणु
	/* look क्रम patched "NOP" on ppc64 with -mprofile-kernel */
	अगर (!ppc_inst_equal(op0, ppc_inst(PPC_INST_NOP)))
		वापस 0;
	वापस 1;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक
__ftrace_make_call(काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ addr)
अणु
	काष्ठा ppc_inst op[2];
	काष्ठा ppc_inst instr;
	व्योम *ip = (व्योम *)rec->ip;
	अचिन्हित दीर्घ entry, ptr, tramp;
	काष्ठा module *mod = rec->arch.mod;

	/* पढ़ो where this goes */
	अगर (copy_inst_from_kernel_nofault(op, ip))
		वापस -EFAULT;

	अगर (copy_inst_from_kernel_nofault(op + 1, ip + 4))
		वापस -EFAULT;

	अगर (!expected_nop_sequence(ip, op[0], op[1])) अणु
		pr_err("Unexpected call sequence at %p: %s %s\n",
		ip, ppc_inst_as_str(op[0]), ppc_inst_as_str(op[1]));
		वापस -EINVAL;
	पूर्ण

	/* If we never set up ftrace trampoline(s), then bail */
#अगर_घोषित CONFIG_DYNAMIC_FTRACE_WITH_REGS
	अगर (!mod->arch.tramp || !mod->arch.tramp_regs) अणु
#अन्यथा
	अगर (!mod->arch.tramp) अणु
#पूर्ण_अगर
		pr_err("No ftrace trampoline\n");
		वापस -EINVAL;
	पूर्ण

#अगर_घोषित CONFIG_DYNAMIC_FTRACE_WITH_REGS
	अगर (rec->flags & FTRACE_FL_REGS)
		tramp = mod->arch.tramp_regs;
	अन्यथा
#पूर्ण_अगर
		tramp = mod->arch.tramp;

	अगर (module_trampoline_target(mod, tramp, &ptr)) अणु
		pr_err("Failed to get trampoline target\n");
		वापस -EFAULT;
	पूर्ण

	pr_devel("trampoline target %lx", ptr);

	entry = ppc_global_function_entry((व्योम *)addr);
	/* This should match what was called */
	अगर (ptr != entry) अणु
		pr_err("addr %lx does not match expected %lx\n", ptr, entry);
		वापस -EINVAL;
	पूर्ण

	/* Ensure branch is within 24 bits */
	अगर (create_branch(&instr, ip, tramp, BRANCH_SET_LINK)) अणु
		pr_err("Branch out of range\n");
		वापस -EINVAL;
	पूर्ण

	अगर (patch_branch(ip, tramp, BRANCH_SET_LINK)) अणु
		pr_err("REL24 out of range!\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

#अन्यथा  /* !CONFIG_PPC64: */
अटल पूर्णांक
__ftrace_make_call(काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ addr)
अणु
	पूर्णांक err;
	काष्ठा ppc_inst op;
	अचिन्हित दीर्घ ip = rec->ip;

	/* पढ़ो where this goes */
	अगर (copy_inst_from_kernel_nofault(&op, (व्योम *)ip))
		वापस -EFAULT;

	/* It should be poपूर्णांकing to a nop */
	अगर (!ppc_inst_equal(op,  ppc_inst(PPC_INST_NOP))) अणु
		pr_err("Expected NOP but have %s\n", ppc_inst_as_str(op));
		वापस -EINVAL;
	पूर्ण

	/* If we never set up a trampoline to ftrace_caller, then bail */
	अगर (!rec->arch.mod->arch.tramp) अणु
		pr_err("No ftrace trampoline\n");
		वापस -EINVAL;
	पूर्ण

	/* create the branch to the trampoline */
	err = create_branch(&op, (काष्ठा ppc_inst *)ip,
			    rec->arch.mod->arch.tramp, BRANCH_SET_LINK);
	अगर (err) अणु
		pr_err("REL24 out of range!\n");
		वापस -EINVAL;
	पूर्ण

	pr_devel("write to %lx\n", rec->ip);

	अगर (patch_inकाष्ठाion((काष्ठा ppc_inst *)ip, op))
		वापस -EPERM;

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC64 */
#पूर्ण_अगर /* CONFIG_MODULES */

अटल पूर्णांक __ftrace_make_call_kernel(काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ addr)
अणु
	काष्ठा ppc_inst op;
	व्योम *ip = (व्योम *)rec->ip;
	अचिन्हित दीर्घ tramp, entry, ptr;

	/* Make sure we're being asked to patch branch to a known ftrace addr */
	entry = ppc_global_function_entry((व्योम *)ftrace_caller);
	ptr = ppc_global_function_entry((व्योम *)addr);

	अगर (ptr != entry) अणु
#अगर_घोषित CONFIG_DYNAMIC_FTRACE_WITH_REGS
		entry = ppc_global_function_entry((व्योम *)ftrace_regs_caller);
		अगर (ptr != entry) अणु
#पूर्ण_अगर
			pr_err("Unknown ftrace addr to patch: %ps\n", (व्योम *)ptr);
			वापस -EINVAL;
#अगर_घोषित CONFIG_DYNAMIC_FTRACE_WITH_REGS
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	/* Make sure we have a nop */
	अगर (copy_inst_from_kernel_nofault(&op, ip)) अणु
		pr_err("Unable to read ftrace location %p\n", ip);
		वापस -EFAULT;
	पूर्ण

	अगर (!ppc_inst_equal(op, ppc_inst(PPC_INST_NOP))) अणु
		pr_err("Unexpected call sequence at %p: %s\n", ip, ppc_inst_as_str(op));
		वापस -EINVAL;
	पूर्ण

	tramp = find_ftrace_tramp((अचिन्हित दीर्घ)ip);
	अगर (!tramp) अणु
		pr_err("No ftrace trampolines reachable from %ps\n", ip);
		वापस -EINVAL;
	पूर्ण

	अगर (patch_branch(ip, tramp, BRANCH_SET_LINK)) अणु
		pr_err("Error patching branch to ftrace tramp!\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ftrace_make_call(काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ ip = rec->ip;
	काष्ठा ppc_inst old, new;

	/*
	 * If the calling address is more that 24 bits away,
	 * then we had to use a trampoline to make the call.
	 * Otherwise just update the call site.
	 */
	अगर (test_24bit_addr(ip, addr)) अणु
		/* within range */
		old = ppc_inst(PPC_INST_NOP);
		new = ftrace_call_replace(ip, addr, 1);
		वापस ftrace_modअगरy_code(ip, old, new);
	पूर्ण अन्यथा अगर (core_kernel_text(ip))
		वापस __ftrace_make_call_kernel(rec, addr);

#अगर_घोषित CONFIG_MODULES
	/*
	 * Out of range jumps are called from modules.
	 * Being that we are converting from nop, it had better
	 * alपढ़ोy have a module defined.
	 */
	अगर (!rec->arch.mod) अणु
		pr_err("No module loaded\n");
		वापस -EINVAL;
	पूर्ण

	वापस __ftrace_make_call(rec, addr);
#अन्यथा
	/* We should not get here without modules */
	वापस -EINVAL;
#पूर्ण_अगर /* CONFIG_MODULES */
पूर्ण

#अगर_घोषित CONFIG_DYNAMIC_FTRACE_WITH_REGS
#अगर_घोषित CONFIG_MODULES
अटल पूर्णांक
__ftrace_modअगरy_call(काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ old_addr,
					अचिन्हित दीर्घ addr)
अणु
	काष्ठा ppc_inst op;
	अचिन्हित दीर्घ ip = rec->ip;
	अचिन्हित दीर्घ entry, ptr, tramp;
	काष्ठा module *mod = rec->arch.mod;

	/* If we never set up ftrace trampolines, then bail */
	अगर (!mod->arch.tramp || !mod->arch.tramp_regs) अणु
		pr_err("No ftrace trampoline\n");
		वापस -EINVAL;
	पूर्ण

	/* पढ़ो where this goes */
	अगर (copy_inst_from_kernel_nofault(&op, (व्योम *)ip)) अणु
		pr_err("Fetching opcode failed.\n");
		वापस -EFAULT;
	पूर्ण

	/* Make sure that that this is still a 24bit jump */
	अगर (!is_bl_op(op)) अणु
		pr_err("Not expected bl: opcode is %s\n", ppc_inst_as_str(op));
		वापस -EINVAL;
	पूर्ण

	/* lets find where the poपूर्णांकer goes */
	tramp = find_bl_target(ip, op);
	entry = ppc_global_function_entry((व्योम *)old_addr);

	pr_devel("ip:%lx jumps to %lx", ip, tramp);

	अगर (tramp != entry) अणु
		/* old_addr is not within range, so we must have used a trampoline */
		अगर (module_trampoline_target(mod, tramp, &ptr)) अणु
			pr_err("Failed to get trampoline target\n");
			वापस -EFAULT;
		पूर्ण

		pr_devel("trampoline target %lx", ptr);

		/* This should match what was called */
		अगर (ptr != entry) अणु
			pr_err("addr %lx does not match expected %lx\n", ptr, entry);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* The new target may be within range */
	अगर (test_24bit_addr(ip, addr)) अणु
		/* within range */
		अगर (patch_branch((काष्ठा ppc_inst *)ip, addr, BRANCH_SET_LINK)) अणु
			pr_err("REL24 out of range!\n");
			वापस -EINVAL;
		पूर्ण

		वापस 0;
	पूर्ण

	अगर (rec->flags & FTRACE_FL_REGS)
		tramp = mod->arch.tramp_regs;
	अन्यथा
		tramp = mod->arch.tramp;

	अगर (module_trampoline_target(mod, tramp, &ptr)) अणु
		pr_err("Failed to get trampoline target\n");
		वापस -EFAULT;
	पूर्ण

	pr_devel("trampoline target %lx", ptr);

	entry = ppc_global_function_entry((व्योम *)addr);
	/* This should match what was called */
	अगर (ptr != entry) अणु
		pr_err("addr %lx does not match expected %lx\n", ptr, entry);
		वापस -EINVAL;
	पूर्ण

	/* Ensure branch is within 24 bits */
	अगर (create_branch(&op, (काष्ठा ppc_inst *)ip, tramp, BRANCH_SET_LINK)) अणु
		pr_err("Branch out of range\n");
		वापस -EINVAL;
	पूर्ण

	अगर (patch_branch((काष्ठा ppc_inst *)ip, tramp, BRANCH_SET_LINK)) अणु
		pr_err("REL24 out of range!\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

पूर्णांक ftrace_modअगरy_call(काष्ठा dyn_ftrace *rec, अचिन्हित दीर्घ old_addr,
			अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ ip = rec->ip;
	काष्ठा ppc_inst old, new;

	/*
	 * If the calling address is more that 24 bits away,
	 * then we had to use a trampoline to make the call.
	 * Otherwise just update the call site.
	 */
	अगर (test_24bit_addr(ip, addr) && test_24bit_addr(ip, old_addr)) अणु
		/* within range */
		old = ftrace_call_replace(ip, old_addr, 1);
		new = ftrace_call_replace(ip, addr, 1);
		वापस ftrace_modअगरy_code(ip, old, new);
	पूर्ण अन्यथा अगर (core_kernel_text(ip)) अणु
		/*
		 * We always patch out of range locations to go to the regs
		 * variant, so there is nothing to करो here
		 */
		वापस 0;
	पूर्ण

#अगर_घोषित CONFIG_MODULES
	/*
	 * Out of range jumps are called from modules.
	 */
	अगर (!rec->arch.mod) अणु
		pr_err("No module loaded\n");
		वापस -EINVAL;
	पूर्ण

	वापस __ftrace_modअगरy_call(rec, old_addr, addr);
#अन्यथा
	/* We should not get here without modules */
	वापस -EINVAL;
#पूर्ण_अगर /* CONFIG_MODULES */
पूर्ण
#पूर्ण_अगर

पूर्णांक ftrace_update_ftrace_func(ftrace_func_t func)
अणु
	अचिन्हित दीर्घ ip = (अचिन्हित दीर्घ)(&ftrace_call);
	काष्ठा ppc_inst old, new;
	पूर्णांक ret;

	old = ppc_inst_पढ़ो((काष्ठा ppc_inst *)&ftrace_call);
	new = ftrace_call_replace(ip, (अचिन्हित दीर्घ)func, 1);
	ret = ftrace_modअगरy_code(ip, old, new);

#अगर_घोषित CONFIG_DYNAMIC_FTRACE_WITH_REGS
	/* Also update the regs callback function */
	अगर (!ret) अणु
		ip = (अचिन्हित दीर्घ)(&ftrace_regs_call);
		old = ppc_inst_पढ़ो((काष्ठा ppc_inst *)&ftrace_regs_call);
		new = ftrace_call_replace(ip, (अचिन्हित दीर्घ)func, 1);
		ret = ftrace_modअगरy_code(ip, old, new);
	पूर्ण
#पूर्ण_अगर

	वापस ret;
पूर्ण

/*
 * Use the शेष ftrace_modअगरy_all_code, but without
 * stop_machine().
 */
व्योम arch_ftrace_update_code(पूर्णांक command)
अणु
	ftrace_modअगरy_all_code(command);
पूर्ण

#अगर_घोषित CONFIG_PPC64
#घोषणा PACATOC दुरत्व(काष्ठा paca_काष्ठा, kernel_toc)

बाह्य अचिन्हित पूर्णांक ftrace_tramp_text[], ftrace_tramp_init[];

पूर्णांक __init ftrace_dyn_arch_init(व्योम)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक *tramp[] = अणु ftrace_tramp_text, ftrace_tramp_init पूर्ण;
	u32 stub_insns[] = अणु
		0xe98d0000 | PACATOC,	/* ld      r12,PACATOC(r13)	*/
		0x3d8c0000,		/* addis   r12,r12,<high>	*/
		0x398c0000,		/* addi    r12,r12,<low>	*/
		0x7d8903a6,		/* mtctr   r12			*/
		0x4e800420,		/* bctr				*/
	पूर्ण;
#अगर_घोषित CONFIG_DYNAMIC_FTRACE_WITH_REGS
	अचिन्हित दीर्घ addr = ppc_global_function_entry((व्योम *)ftrace_regs_caller);
#अन्यथा
	अचिन्हित दीर्घ addr = ppc_global_function_entry((व्योम *)ftrace_caller);
#पूर्ण_अगर
	दीर्घ reladdr = addr - kernel_toc_addr();

	अगर (reladdr > 0x7FFFFFFF || reladdr < -(0x80000000L)) अणु
		pr_err("Address of %ps out of range of kernel_toc.\n",
				(व्योम *)addr);
		वापस -1;
	पूर्ण

	क्रम (i = 0; i < 2; i++) अणु
		स_नकल(tramp[i], stub_insns, माप(stub_insns));
		tramp[i][1] |= PPC_HA(reladdr);
		tramp[i][2] |= PPC_LO(reladdr);
		add_ftrace_tramp((अचिन्हित दीर्घ)tramp[i]);
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
पूर्णांक __init ftrace_dyn_arch_init(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_DYNAMIC_FTRACE */

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER

बाह्य व्योम ftrace_graph_call(व्योम);
बाह्य व्योम ftrace_graph_stub(व्योम);

पूर्णांक ftrace_enable_ftrace_graph_caller(व्योम)
अणु
	अचिन्हित दीर्घ ip = (अचिन्हित दीर्घ)(&ftrace_graph_call);
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)(&ftrace_graph_caller);
	अचिन्हित दीर्घ stub = (अचिन्हित दीर्घ)(&ftrace_graph_stub);
	काष्ठा ppc_inst old, new;

	old = ftrace_call_replace(ip, stub, 0);
	new = ftrace_call_replace(ip, addr, 0);

	वापस ftrace_modअगरy_code(ip, old, new);
पूर्ण

पूर्णांक ftrace_disable_ftrace_graph_caller(व्योम)
अणु
	अचिन्हित दीर्घ ip = (अचिन्हित दीर्घ)(&ftrace_graph_call);
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)(&ftrace_graph_caller);
	अचिन्हित दीर्घ stub = (अचिन्हित दीर्घ)(&ftrace_graph_stub);
	काष्ठा ppc_inst old, new;

	old = ftrace_call_replace(ip, addr, 0);
	new = ftrace_call_replace(ip, stub, 0);

	वापस ftrace_modअगरy_code(ip, old, new);
पूर्ण

/*
 * Hook the वापस address and push it in the stack of वापस addrs
 * in current thपढ़ो info. Return the address we want to भागert to.
 */
अचिन्हित दीर्घ prepare_ftrace_वापस(अचिन्हित दीर्घ parent, अचिन्हित दीर्घ ip,
						अचिन्हित दीर्घ sp)
अणु
	अचिन्हित दीर्घ वापस_hooker;

	अगर (unlikely(ftrace_graph_is_dead()))
		जाओ out;

	अगर (unlikely(atomic_पढ़ो(&current->tracing_graph_छोड़ो)))
		जाओ out;

	वापस_hooker = ppc_function_entry(वापस_to_handler);

	अगर (!function_graph_enter(parent, ip, 0, (अचिन्हित दीर्घ *)sp))
		parent = वापस_hooker;
out:
	वापस parent;
पूर्ण
#पूर्ण_अगर /* CONFIG_FUNCTION_GRAPH_TRACER */

#अगर_घोषित PPC64_ELF_ABI_v1
अक्षर *arch_ftrace_match_adjust(अक्षर *str, स्थिर अक्षर *search)
अणु
	अगर (str[0] == '.' && search[0] != '.')
		वापस str + 1;
	अन्यथा
		वापस str;
पूर्ण
#पूर्ण_अगर /* PPC64_ELF_ABI_v1 */
