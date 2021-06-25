<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Kernel Probes (KProbes)
 *
 * Copyright (C) IBM Corporation, 2002, 2004
 *
 * 2002-Oct	Created by Vamsi Krishna S <vamsi_krishna@in.ibm.com> Kernel
 *		Probes initial implementation ( includes contributions from
 *		Rusty Russell).
 * 2004-July	Suparna Bhattaअक्षरya <suparna@in.ibm.com> added jumper probes
 *		पूर्णांकerface to access function arguments.
 * 2004-Oct	Jim Keniston <jkenisto@us.ibm.com> and Prasanna S Panchamukhi
 *		<prasanna@in.ibm.com> adapted क्रम x86_64 from i386.
 * 2005-Mar	Roland McGrath <roland@redhat.com>
 *		Fixed to handle %rip-relative addressing mode correctly.
 * 2005-May	Hien Nguyen <hien@us.ibm.com>, Jim Keniston
 *		<jkenisto@us.ibm.com> and Prasanna S Panchamukhi
 *		<prasanna@in.ibm.com> added function-वापस probes.
 * 2005-May	Rusty Lynch <rusty.lynch@पूर्णांकel.com>
 *		Added function वापस probes functionality
 * 2006-Feb	Masami Hiramatsu <hiramatu@sdl.hitachi.co.jp> added
 *		kprobe-booster and kretprobe-booster क्रम i386.
 * 2007-Dec	Masami Hiramatsu <mhiramat@redhat.com> added kprobe-booster
 *		and kretprobe-booster क्रम x86-64
 * 2007-Dec	Masami Hiramatsu <mhiramat@redhat.com>, Arjan van de Ven
 *		<arjan@infradead.org> and Jim Keniston <jkenisto@us.ibm.com>
 *		unअगरied x86 kprobes code.
 */
#समावेश <linux/kprobes.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/preempt.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/extable.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/kasan.h>
#समावेश <linux/moduleloader.h>
#समावेश <linux/objtool.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/text-patching.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/desc.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/insn.h>
#समावेश <यंत्र/debugreg.h>
#समावेश <यंत्र/set_memory.h>

#समावेश "common.h"

DEFINE_PER_CPU(काष्ठा kprobe *, current_kprobe) = शून्य;
DEFINE_PER_CPU(काष्ठा kprobe_ctlblk, kprobe_ctlblk);

#घोषणा stack_addr(regs) ((अचिन्हित दीर्घ *)regs->sp)

#घोषणा W(row, b0, b1, b2, b3, b4, b5, b6, b7, b8, b9, ba, bb, bc, bd, be, bf)\
	(((b0##UL << 0x0)|(b1##UL << 0x1)|(b2##UL << 0x2)|(b3##UL << 0x3) |   \
	  (b4##UL << 0x4)|(b5##UL << 0x5)|(b6##UL << 0x6)|(b7##UL << 0x7) |   \
	  (b8##UL << 0x8)|(b9##UL << 0x9)|(ba##UL << 0xa)|(bb##UL << 0xb) |   \
	  (bc##UL << 0xc)|(bd##UL << 0xd)|(be##UL << 0xe)|(bf##UL << 0xf))    \
	 << (row % 32))
	/*
	 * Undefined/reserved opcodes, conditional jump, Opcode Extension
	 * Groups, and some special opcodes can not boost.
	 * This is non-स्थिर and अस्थिर to keep gcc from अटलally
	 * optimizing it out, as variable_test_bit makes gcc think only
	 * *(अचिन्हित दीर्घ*) is used.
	 */
अटल अस्थिर u32 twobyte_is_boostable[256 / 32] = अणु
	/*      0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f          */
	/*      ----------------------------------------------          */
	W(0x00, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0) | /* 00 */
	W(0x10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1) , /* 10 */
	W(0x20, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) | /* 20 */
	W(0x30, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) , /* 30 */
	W(0x40, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) | /* 40 */
	W(0x50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) , /* 50 */
	W(0x60, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1) | /* 60 */
	W(0x70, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1) , /* 70 */
	W(0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) | /* 80 */
	W(0x90, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) , /* 90 */
	W(0xa0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1) | /* a0 */
	W(0xb0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1) , /* b0 */
	W(0xc0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1) | /* c0 */
	W(0xd0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1) , /* d0 */
	W(0xe0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1) | /* e0 */
	W(0xf0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0)   /* f0 */
	/*      -----------------------------------------------         */
	/*      0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f          */
पूर्ण;
#अघोषित W

काष्ठा kretprobe_blackpoपूर्णांक kretprobe_blacklist[] = अणु
	अणु"__switch_to", पूर्ण, /* This function चयनes only current task, but
			      करोesn't चयन kernel stack.*/
	अणुशून्य, शून्यपूर्ण	/* Terminator */
पूर्ण;

स्थिर पूर्णांक kretprobe_blacklist_size = ARRAY_SIZE(kretprobe_blacklist);

अटल nokprobe_अंतरभूत व्योम
__synthesize_relative_insn(व्योम *dest, व्योम *from, व्योम *to, u8 op)
अणु
	काष्ठा __arch_relative_insn अणु
		u8 op;
		s32 raddr;
	पूर्ण __packed *insn;

	insn = (काष्ठा __arch_relative_insn *)dest;
	insn->raddr = (s32)((दीर्घ)(to) - ((दीर्घ)(from) + 5));
	insn->op = op;
पूर्ण

/* Insert a jump inकाष्ठाion at address 'from', which jumps to address 'to'.*/
व्योम synthesize_reljump(व्योम *dest, व्योम *from, व्योम *to)
अणु
	__synthesize_relative_insn(dest, from, to, JMP32_INSN_OPCODE);
पूर्ण
NOKPROBE_SYMBOL(synthesize_reljump);

/* Insert a call inकाष्ठाion at address 'from', which calls address 'to'.*/
व्योम synthesize_relcall(व्योम *dest, व्योम *from, व्योम *to)
अणु
	__synthesize_relative_insn(dest, from, to, CALL_INSN_OPCODE);
पूर्ण
NOKPROBE_SYMBOL(synthesize_relcall);

/*
 * Returns non-zero अगर INSN is boostable.
 * RIP relative inकाष्ठाions are adjusted at copying समय in 64 bits mode
 */
पूर्णांक can_boost(काष्ठा insn *insn, व्योम *addr)
अणु
	kprobe_opcode_t opcode;
	insn_byte_t prefix;
	पूर्णांक i;

	अगर (search_exception_tables((अचिन्हित दीर्घ)addr))
		वापस 0;	/* Page fault may occur on this address. */

	/* 2nd-byte opcode */
	अगर (insn->opcode.nbytes == 2)
		वापस test_bit(insn->opcode.bytes[1],
				(अचिन्हित दीर्घ *)twobyte_is_boostable);

	अगर (insn->opcode.nbytes != 1)
		वापस 0;

	क्रम_each_insn_prefix(insn, i, prefix) अणु
		insn_attr_t attr;

		attr = inat_get_opcode_attribute(prefix);
		/* Can't boost Address-size override prefix and CS override prefix */
		अगर (prefix == 0x2e || inat_is_address_size_prefix(attr))
			वापस 0;
	पूर्ण

	opcode = insn->opcode.bytes[0];

	चयन (opcode) अणु
	हाल 0x62:		/* bound */
	हाल 0x70 ... 0x7f:	/* Conditional jumps */
	हाल 0x9a:		/* Call far */
	हाल 0xc0 ... 0xc1:	/* Grp2 */
	हाल 0xcc ... 0xce:	/* software exceptions */
	हाल 0xd0 ... 0xd3:	/* Grp2 */
	हाल 0xd6:		/* (UD) */
	हाल 0xd8 ... 0xdf:	/* ESC */
	हाल 0xe0 ... 0xe3:	/* LOOP*, JCXZ */
	हाल 0xe8 ... 0xe9:	/* near Call, JMP */
	हाल 0xeb:		/* Short JMP */
	हाल 0xf0 ... 0xf4:	/* LOCK/REP, HLT */
	हाल 0xf6 ... 0xf7:	/* Grp3 */
	हाल 0xfe:		/* Grp4 */
		/* ... are not boostable */
		वापस 0;
	हाल 0xff:		/* Grp5 */
		/* Only indirect jmp is boostable */
		वापस X86_MODRM_REG(insn->modrm.bytes[0]) == 4;
	शेष:
		वापस 1;
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ
__recover_probed_insn(kprobe_opcode_t *buf, अचिन्हित दीर्घ addr)
अणु
	काष्ठा kprobe *kp;
	अचिन्हित दीर्घ faddr;

	kp = get_kprobe((व्योम *)addr);
	faddr = ftrace_location(addr);
	/*
	 * Addresses inside the ftrace location are refused by
	 * arch_check_ftrace_location(). Something went terribly wrong
	 * अगर such an address is checked here.
	 */
	अगर (WARN_ON(faddr && faddr != addr))
		वापस 0UL;
	/*
	 * Use the current code अगर it is not modअगरied by Kprobe
	 * and it cannot be modअगरied by ftrace.
	 */
	अगर (!kp && !faddr)
		वापस addr;

	/*
	 * Basically, kp->ainsn.insn has an original inकाष्ठाion.
	 * However, RIP-relative inकाष्ठाion can not करो single-stepping
	 * at dअगरferent place, __copy_inकाष्ठाion() tweaks the displacement of
	 * that inकाष्ठाion. In that हाल, we can't recover the inकाष्ठाion
	 * from the kp->ainsn.insn.
	 *
	 * On the other hand, in हाल on normal Kprobe, kp->opcode has a copy
	 * of the first byte of the probed inकाष्ठाion, which is overwritten
	 * by पूर्णांक3. And the inकाष्ठाion at kp->addr is not modअगरied by kprobes
	 * except क्रम the first byte, we can recover the original inकाष्ठाion
	 * from it and kp->opcode.
	 *
	 * In हाल of Kprobes using ftrace, we करो not have a copy of
	 * the original inकाष्ठाion. In fact, the ftrace location might
	 * be modअगरied at anyसमय and even could be in an inconsistent state.
	 * Fortunately, we know that the original code is the ideal 5-byte
	 * दीर्घ NOP.
	 */
	अगर (copy_from_kernel_nofault(buf, (व्योम *)addr,
		MAX_INSN_SIZE * माप(kprobe_opcode_t)))
		वापस 0UL;

	अगर (faddr)
		स_नकल(buf, x86_nops[5], 5);
	अन्यथा
		buf[0] = kp->opcode;
	वापस (अचिन्हित दीर्घ)buf;
पूर्ण

/*
 * Recover the probed inकाष्ठाion at addr क्रम further analysis.
 * Caller must lock kprobes by kprobe_mutex, or disable preemption
 * क्रम preventing to release referencing kprobes.
 * Returns zero अगर the inकाष्ठाion can not get recovered (or access failed).
 */
अचिन्हित दीर्घ recover_probed_inकाष्ठाion(kprobe_opcode_t *buf, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ __addr;

	__addr = __recover_optprobed_insn(buf, addr);
	अगर (__addr != addr)
		वापस __addr;

	वापस __recover_probed_insn(buf, addr);
पूर्ण

/* Check अगर paddr is at an inकाष्ठाion boundary */
अटल पूर्णांक can_probe(अचिन्हित दीर्घ paddr)
अणु
	अचिन्हित दीर्घ addr, __addr, offset = 0;
	काष्ठा insn insn;
	kprobe_opcode_t buf[MAX_INSN_SIZE];

	अगर (!kallsyms_lookup_size_offset(paddr, शून्य, &offset))
		वापस 0;

	/* Decode inकाष्ठाions */
	addr = paddr - offset;
	जबतक (addr < paddr) अणु
		पूर्णांक ret;

		/*
		 * Check अगर the inकाष्ठाion has been modअगरied by another
		 * kprobe, in which हाल we replace the अवरोधpoपूर्णांक by the
		 * original inकाष्ठाion in our buffer.
		 * Also, jump optimization will change the अवरोधpoपूर्णांक to
		 * relative-jump. Since the relative-jump itself is
		 * normally used, we just go through अगर there is no kprobe.
		 */
		__addr = recover_probed_inकाष्ठाion(buf, addr);
		अगर (!__addr)
			वापस 0;

		ret = insn_decode_kernel(&insn, (व्योम *)__addr);
		अगर (ret < 0)
			वापस 0;

		/*
		 * Another debugging subप्रणाली might insert this अवरोधpoपूर्णांक.
		 * In that हाल, we can't recover it.
		 */
		अगर (insn.opcode.bytes[0] == INT3_INSN_OPCODE)
			वापस 0;
		addr += insn.length;
	पूर्ण

	वापस (addr == paddr);
पूर्ण

/*
 * Copy an inकाष्ठाion with recovering modअगरied inकाष्ठाion by kprobes
 * and adjust the displacement अगर the inकाष्ठाion uses the %rip-relative
 * addressing mode. Note that since @real will be the final place of copied
 * inकाष्ठाion, displacement must be adjust by @real, not @dest.
 * This वापसs the length of copied inकाष्ठाion, or 0 अगर it has an error.
 */
पूर्णांक __copy_inकाष्ठाion(u8 *dest, u8 *src, u8 *real, काष्ठा insn *insn)
अणु
	kprobe_opcode_t buf[MAX_INSN_SIZE];
	अचिन्हित दीर्घ recovered_insn = recover_probed_inकाष्ठाion(buf, (अचिन्हित दीर्घ)src);
	पूर्णांक ret;

	अगर (!recovered_insn || !insn)
		वापस 0;

	/* This can access kernel text अगर given address is not recovered */
	अगर (copy_from_kernel_nofault(dest, (व्योम *)recovered_insn,
			MAX_INSN_SIZE))
		वापस 0;

	ret = insn_decode_kernel(insn, dest);
	अगर (ret < 0)
		वापस 0;

	/* We can not probe क्रमce emulate prefixed inकाष्ठाion */
	अगर (insn_has_emulate_prefix(insn))
		वापस 0;

	/* Another subप्रणाली माला_दो a अवरोधpoपूर्णांक, failed to recover */
	अगर (insn->opcode.bytes[0] == INT3_INSN_OPCODE)
		वापस 0;

	/* We should not singlestep on the exception masking inकाष्ठाions */
	अगर (insn_masking_exception(insn))
		वापस 0;

#अगर_घोषित CONFIG_X86_64
	/* Only x86_64 has RIP relative inकाष्ठाions */
	अगर (insn_rip_relative(insn)) अणु
		s64 newdisp;
		u8 *disp;
		/*
		 * The copied inकाष्ठाion uses the %rip-relative addressing
		 * mode.  Adjust the displacement क्रम the dअगरference between
		 * the original location of this inकाष्ठाion and the location
		 * of the copy that will actually be run.  The tricky bit here
		 * is making sure that the sign extension happens correctly in
		 * this calculation, since we need a चिन्हित 32-bit result to
		 * be sign-extended to 64 bits when it's added to the %rip
		 * value and yield the same 64-bit result that the sign-
		 * extension of the original चिन्हित 32-bit displacement would
		 * have given.
		 */
		newdisp = (u8 *) src + (s64) insn->displacement.value
			  - (u8 *) real;
		अगर ((s64) (s32) newdisp != newdisp) अणु
			pr_err("Kprobes error: new displacement does not fit into s32 (%llx)\n", newdisp);
			वापस 0;
		पूर्ण
		disp = (u8 *) dest + insn_offset_displacement(insn);
		*(s32 *) disp = (s32) newdisp;
	पूर्ण
#पूर्ण_अगर
	वापस insn->length;
पूर्ण

/* Prepare reljump or पूर्णांक3 right after inकाष्ठाion */
अटल पूर्णांक prepare_singlestep(kprobe_opcode_t *buf, काष्ठा kprobe *p,
			      काष्ठा insn *insn)
अणु
	पूर्णांक len = insn->length;

	अगर (!IS_ENABLED(CONFIG_PREEMPTION) &&
	    !p->post_handler && can_boost(insn, p->addr) &&
	    MAX_INSN_SIZE - len >= JMP32_INSN_SIZE) अणु
		/*
		 * These inकाष्ठाions can be executed directly अगर it
		 * jumps back to correct address.
		 */
		synthesize_reljump(buf + len, p->ainsn.insn + len,
				   p->addr + insn->length);
		len += JMP32_INSN_SIZE;
		p->ainsn.boostable = 1;
	पूर्ण अन्यथा अणु
		/* Otherwise, put an पूर्णांक3 क्रम trapping singlestep */
		अगर (MAX_INSN_SIZE - len < INT3_INSN_SIZE)
			वापस -ENOSPC;

		buf[len] = INT3_INSN_OPCODE;
		len += INT3_INSN_SIZE;
	पूर्ण

	वापस len;
पूर्ण

/* Make page to RO mode when allocate it */
व्योम *alloc_insn_page(व्योम)
अणु
	व्योम *page;

	page = module_alloc(PAGE_SIZE);
	अगर (!page)
		वापस शून्य;

	set_vm_flush_reset_perms(page);
	/*
	 * First make the page पढ़ो-only, and only then make it executable to
	 * prevent it from being W+X in between.
	 */
	set_memory_ro((अचिन्हित दीर्घ)page, 1);

	/*
	 * TODO: Once additional kernel code protection mechanisms are set, ensure
	 * that the page was not maliciously altered and it is still zeroed.
	 */
	set_memory_x((अचिन्हित दीर्घ)page, 1);

	वापस page;
पूर्ण

/* Recover page to RW mode beक्रमe releasing it */
व्योम मुक्त_insn_page(व्योम *page)
अणु
	module_memमुक्त(page);
पूर्ण

/* Kprobe x86 inकाष्ठाion emulation - only regs->ip or IF flag modअगरiers */

अटल व्योम kprobe_emulate_अगरmodअगरiers(काष्ठा kprobe *p, काष्ठा pt_regs *regs)
अणु
	चयन (p->ainsn.opcode) अणु
	हाल 0xfa:	/* cli */
		regs->flags &= ~(X86_EFLAGS_IF);
		अवरोध;
	हाल 0xfb:	/* sti */
		regs->flags |= X86_EFLAGS_IF;
		अवरोध;
	हाल 0x9c:	/* pushf */
		पूर्णांक3_emulate_push(regs, regs->flags);
		अवरोध;
	हाल 0x9d:	/* popf */
		regs->flags = पूर्णांक3_emulate_pop(regs);
		अवरोध;
	पूर्ण
	regs->ip = regs->ip - INT3_INSN_SIZE + p->ainsn.size;
पूर्ण
NOKPROBE_SYMBOL(kprobe_emulate_अगरmodअगरiers);

अटल व्योम kprobe_emulate_ret(काष्ठा kprobe *p, काष्ठा pt_regs *regs)
अणु
	पूर्णांक3_emulate_ret(regs);
पूर्ण
NOKPROBE_SYMBOL(kprobe_emulate_ret);

अटल व्योम kprobe_emulate_call(काष्ठा kprobe *p, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ func = regs->ip - INT3_INSN_SIZE + p->ainsn.size;

	func += p->ainsn.rel32;
	पूर्णांक3_emulate_call(regs, func);
पूर्ण
NOKPROBE_SYMBOL(kprobe_emulate_call);

अटल nokprobe_अंतरभूत
व्योम __kprobe_emulate_jmp(काष्ठा kprobe *p, काष्ठा pt_regs *regs, bool cond)
अणु
	अचिन्हित दीर्घ ip = regs->ip - INT3_INSN_SIZE + p->ainsn.size;

	अगर (cond)
		ip += p->ainsn.rel32;
	पूर्णांक3_emulate_jmp(regs, ip);
पूर्ण

अटल व्योम kprobe_emulate_jmp(काष्ठा kprobe *p, काष्ठा pt_regs *regs)
अणु
	__kprobe_emulate_jmp(p, regs, true);
पूर्ण
NOKPROBE_SYMBOL(kprobe_emulate_jmp);

अटल स्थिर अचिन्हित दीर्घ jcc_mask[6] = अणु
	[0] = X86_EFLAGS_OF,
	[1] = X86_EFLAGS_CF,
	[2] = X86_EFLAGS_ZF,
	[3] = X86_EFLAGS_CF | X86_EFLAGS_ZF,
	[4] = X86_EFLAGS_SF,
	[5] = X86_EFLAGS_PF,
पूर्ण;

अटल व्योम kprobe_emulate_jcc(काष्ठा kprobe *p, काष्ठा pt_regs *regs)
अणु
	bool invert = p->ainsn.jcc.type & 1;
	bool match;

	अगर (p->ainsn.jcc.type < 0xc) अणु
		match = regs->flags & jcc_mask[p->ainsn.jcc.type >> 1];
	पूर्ण अन्यथा अणु
		match = ((regs->flags & X86_EFLAGS_SF) >> X86_EFLAGS_SF_BIT) ^
			((regs->flags & X86_EFLAGS_OF) >> X86_EFLAGS_OF_BIT);
		अगर (p->ainsn.jcc.type >= 0xe)
			match = match && (regs->flags & X86_EFLAGS_ZF);
	पूर्ण
	__kprobe_emulate_jmp(p, regs, (match && !invert) || (!match && invert));
पूर्ण
NOKPROBE_SYMBOL(kprobe_emulate_jcc);

अटल व्योम kprobe_emulate_loop(काष्ठा kprobe *p, काष्ठा pt_regs *regs)
अणु
	bool match;

	अगर (p->ainsn.loop.type != 3) अणु	/* LOOP* */
		अगर (p->ainsn.loop.asize == 32)
			match = ((*(u32 *)&regs->cx)--) != 0;
#अगर_घोषित CONFIG_X86_64
		अन्यथा अगर (p->ainsn.loop.asize == 64)
			match = ((*(u64 *)&regs->cx)--) != 0;
#पूर्ण_अगर
		अन्यथा
			match = ((*(u16 *)&regs->cx)--) != 0;
	पूर्ण अन्यथा अणु			/* JCXZ */
		अगर (p->ainsn.loop.asize == 32)
			match = *(u32 *)(&regs->cx) == 0;
#अगर_घोषित CONFIG_X86_64
		अन्यथा अगर (p->ainsn.loop.asize == 64)
			match = *(u64 *)(&regs->cx) == 0;
#पूर्ण_अगर
		अन्यथा
			match = *(u16 *)(&regs->cx) == 0;
	पूर्ण

	अगर (p->ainsn.loop.type == 0)	/* LOOPNE */
		match = match && !(regs->flags & X86_EFLAGS_ZF);
	अन्यथा अगर (p->ainsn.loop.type == 1)	/* LOOPE */
		match = match && (regs->flags & X86_EFLAGS_ZF);

	__kprobe_emulate_jmp(p, regs, match);
पूर्ण
NOKPROBE_SYMBOL(kprobe_emulate_loop);

अटल स्थिर पूर्णांक addrmode_regoffs[] = अणु
	दुरत्व(काष्ठा pt_regs, ax),
	दुरत्व(काष्ठा pt_regs, cx),
	दुरत्व(काष्ठा pt_regs, dx),
	दुरत्व(काष्ठा pt_regs, bx),
	दुरत्व(काष्ठा pt_regs, sp),
	दुरत्व(काष्ठा pt_regs, bp),
	दुरत्व(काष्ठा pt_regs, si),
	दुरत्व(काष्ठा pt_regs, di),
#अगर_घोषित CONFIG_X86_64
	दुरत्व(काष्ठा pt_regs, r8),
	दुरत्व(काष्ठा pt_regs, r9),
	दुरत्व(काष्ठा pt_regs, r10),
	दुरत्व(काष्ठा pt_regs, r11),
	दुरत्व(काष्ठा pt_regs, r12),
	दुरत्व(काष्ठा pt_regs, r13),
	दुरत्व(काष्ठा pt_regs, r14),
	दुरत्व(काष्ठा pt_regs, r15),
#पूर्ण_अगर
पूर्ण;

अटल व्योम kprobe_emulate_call_indirect(काष्ठा kprobe *p, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ offs = addrmode_regoffs[p->ainsn.indirect.reg];

	पूर्णांक3_emulate_call(regs, regs_get_रेजिस्टर(regs, offs));
पूर्ण
NOKPROBE_SYMBOL(kprobe_emulate_call_indirect);

अटल व्योम kprobe_emulate_jmp_indirect(काष्ठा kprobe *p, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ offs = addrmode_regoffs[p->ainsn.indirect.reg];

	पूर्णांक3_emulate_jmp(regs, regs_get_रेजिस्टर(regs, offs));
पूर्ण
NOKPROBE_SYMBOL(kprobe_emulate_jmp_indirect);

अटल पूर्णांक prepare_emulation(काष्ठा kprobe *p, काष्ठा insn *insn)
अणु
	insn_byte_t opcode = insn->opcode.bytes[0];

	चयन (opcode) अणु
	हाल 0xfa:		/* cli */
	हाल 0xfb:		/* sti */
	हाल 0x9c:		/* pushfl */
	हाल 0x9d:		/* popf/popfd */
		/*
		 * IF modअगरiers must be emulated since it will enable पूर्णांकerrupt जबतक
		 * पूर्णांक3 single stepping.
		 */
		p->ainsn.emulate_op = kprobe_emulate_अगरmodअगरiers;
		p->ainsn.opcode = opcode;
		अवरोध;
	हाल 0xc2:	/* ret/lret */
	हाल 0xc3:
	हाल 0xca:
	हाल 0xcb:
		p->ainsn.emulate_op = kprobe_emulate_ret;
		अवरोध;
	हाल 0x9a:	/* far call असलolute -- segment is not supported */
	हाल 0xea:	/* far jmp असलolute -- segment is not supported */
	हाल 0xcc:	/* पूर्णांक3 */
	हाल 0xcf:	/* iret -- in-kernel IRET is not supported */
		वापस -EOPNOTSUPP;
		अवरोध;
	हाल 0xe8:	/* near call relative */
		p->ainsn.emulate_op = kprobe_emulate_call;
		अगर (insn->immediate.nbytes == 2)
			p->ainsn.rel32 = *(s16 *)&insn->immediate.value;
		अन्यथा
			p->ainsn.rel32 = *(s32 *)&insn->immediate.value;
		अवरोध;
	हाल 0xeb:	/* लघु jump relative */
	हाल 0xe9:	/* near jump relative */
		p->ainsn.emulate_op = kprobe_emulate_jmp;
		अगर (insn->immediate.nbytes == 1)
			p->ainsn.rel32 = *(s8 *)&insn->immediate.value;
		अन्यथा अगर (insn->immediate.nbytes == 2)
			p->ainsn.rel32 = *(s16 *)&insn->immediate.value;
		अन्यथा
			p->ainsn.rel32 = *(s32 *)&insn->immediate.value;
		अवरोध;
	हाल 0x70 ... 0x7f:
		/* 1 byte conditional jump */
		p->ainsn.emulate_op = kprobe_emulate_jcc;
		p->ainsn.jcc.type = opcode & 0xf;
		p->ainsn.rel32 = *(अक्षर *)insn->immediate.bytes;
		अवरोध;
	हाल 0x0f:
		opcode = insn->opcode.bytes[1];
		अगर ((opcode & 0xf0) == 0x80) अणु
			/* 2 bytes Conditional Jump */
			p->ainsn.emulate_op = kprobe_emulate_jcc;
			p->ainsn.jcc.type = opcode & 0xf;
			अगर (insn->immediate.nbytes == 2)
				p->ainsn.rel32 = *(s16 *)&insn->immediate.value;
			अन्यथा
				p->ainsn.rel32 = *(s32 *)&insn->immediate.value;
		पूर्ण अन्यथा अगर (opcode == 0x01 &&
			   X86_MODRM_REG(insn->modrm.bytes[0]) == 0 &&
			   X86_MODRM_MOD(insn->modrm.bytes[0]) == 3) अणु
			/* VM extensions - not supported */
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
	हाल 0xe0:	/* Loop NZ */
	हाल 0xe1:	/* Loop */
	हाल 0xe2:	/* Loop */
	हाल 0xe3:	/* J*CXZ */
		p->ainsn.emulate_op = kprobe_emulate_loop;
		p->ainsn.loop.type = opcode & 0x3;
		p->ainsn.loop.asize = insn->addr_bytes * 8;
		p->ainsn.rel32 = *(s8 *)&insn->immediate.value;
		अवरोध;
	हाल 0xff:
		/*
		 * Since the 0xff is an extended group opcode, the inकाष्ठाion
		 * is determined by the MOD/RM byte.
		 */
		opcode = insn->modrm.bytes[0];
		अगर ((opcode & 0x30) == 0x10) अणु
			अगर ((opcode & 0x8) == 0x8)
				वापस -EOPNOTSUPP;	/* far call */
			/* call असलolute, indirect */
			p->ainsn.emulate_op = kprobe_emulate_call_indirect;
		पूर्ण अन्यथा अगर ((opcode & 0x30) == 0x20) अणु
			अगर ((opcode & 0x8) == 0x8)
				वापस -EOPNOTSUPP;	/* far jmp */
			/* jmp near असलolute indirect */
			p->ainsn.emulate_op = kprobe_emulate_jmp_indirect;
		पूर्ण अन्यथा
			अवरोध;

		अगर (insn->addr_bytes != माप(अचिन्हित दीर्घ))
			वापस -EOPNOTSUPP;	/* Don't support dअगरfernt size */
		अगर (X86_MODRM_MOD(opcode) != 3)
			वापस -EOPNOTSUPP;	/* TODO: support memory addressing */

		p->ainsn.indirect.reg = X86_MODRM_RM(opcode);
#अगर_घोषित CONFIG_X86_64
		अगर (X86_REX_B(insn->rex_prefix.value))
			p->ainsn.indirect.reg += 8;
#पूर्ण_अगर
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	p->ainsn.size = insn->length;

	वापस 0;
पूर्ण

अटल पूर्णांक arch_copy_kprobe(काष्ठा kprobe *p)
अणु
	काष्ठा insn insn;
	kprobe_opcode_t buf[MAX_INSN_SIZE];
	पूर्णांक ret, len;

	/* Copy an inकाष्ठाion with recovering अगर other optprobe modअगरies it.*/
	len = __copy_inकाष्ठाion(buf, p->addr, p->ainsn.insn, &insn);
	अगर (!len)
		वापस -EINVAL;

	/* Analyze the opcode and setup emulate functions */
	ret = prepare_emulation(p, &insn);
	अगर (ret < 0)
		वापस ret;

	/* Add पूर्णांक3 क्रम single-step or booster jmp */
	len = prepare_singlestep(buf, p, &insn);
	अगर (len < 0)
		वापस len;

	/* Also, displacement change करोesn't affect the first byte */
	p->opcode = buf[0];

	p->ainsn.tp_len = len;
	perf_event_text_poke(p->ainsn.insn, शून्य, 0, buf, len);

	/* OK, ग_लिखो back the inकाष्ठाion(s) पूर्णांकo ROX insn buffer */
	text_poke(p->ainsn.insn, buf, len);

	वापस 0;
पूर्ण

पूर्णांक arch_prepare_kprobe(काष्ठा kprobe *p)
अणु
	पूर्णांक ret;

	अगर (alternatives_text_reserved(p->addr, p->addr))
		वापस -EINVAL;

	अगर (!can_probe((अचिन्हित दीर्घ)p->addr))
		वापस -EILSEQ;

	स_रखो(&p->ainsn, 0, माप(p->ainsn));

	/* insn: must be on special executable page on x86. */
	p->ainsn.insn = get_insn_slot();
	अगर (!p->ainsn.insn)
		वापस -ENOMEM;

	ret = arch_copy_kprobe(p);
	अगर (ret) अणु
		मुक्त_insn_slot(p->ainsn.insn, 0);
		p->ainsn.insn = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

व्योम arch_arm_kprobe(काष्ठा kprobe *p)
अणु
	u8 पूर्णांक3 = INT3_INSN_OPCODE;

	text_poke(p->addr, &पूर्णांक3, 1);
	text_poke_sync();
	perf_event_text_poke(p->addr, &p->opcode, 1, &पूर्णांक3, 1);
पूर्ण

व्योम arch_disarm_kprobe(काष्ठा kprobe *p)
अणु
	u8 पूर्णांक3 = INT3_INSN_OPCODE;

	perf_event_text_poke(p->addr, &पूर्णांक3, 1, &p->opcode, 1);
	text_poke(p->addr, &p->opcode, 1);
	text_poke_sync();
पूर्ण

व्योम arch_हटाओ_kprobe(काष्ठा kprobe *p)
अणु
	अगर (p->ainsn.insn) अणु
		/* Record the perf event beक्रमe मुक्तing the slot */
		perf_event_text_poke(p->ainsn.insn, p->ainsn.insn,
				     p->ainsn.tp_len, शून्य, 0);
		मुक्त_insn_slot(p->ainsn.insn, p->ainsn.boostable);
		p->ainsn.insn = शून्य;
	पूर्ण
पूर्ण

अटल nokprobe_अंतरभूत व्योम
save_previous_kprobe(काष्ठा kprobe_ctlblk *kcb)
अणु
	kcb->prev_kprobe.kp = kprobe_running();
	kcb->prev_kprobe.status = kcb->kprobe_status;
	kcb->prev_kprobe.old_flags = kcb->kprobe_old_flags;
	kcb->prev_kprobe.saved_flags = kcb->kprobe_saved_flags;
पूर्ण

अटल nokprobe_अंतरभूत व्योम
restore_previous_kprobe(काष्ठा kprobe_ctlblk *kcb)
अणु
	__this_cpu_ग_लिखो(current_kprobe, kcb->prev_kprobe.kp);
	kcb->kprobe_status = kcb->prev_kprobe.status;
	kcb->kprobe_old_flags = kcb->prev_kprobe.old_flags;
	kcb->kprobe_saved_flags = kcb->prev_kprobe.saved_flags;
पूर्ण

अटल nokprobe_अंतरभूत व्योम
set_current_kprobe(काष्ठा kprobe *p, काष्ठा pt_regs *regs,
		   काष्ठा kprobe_ctlblk *kcb)
अणु
	__this_cpu_ग_लिखो(current_kprobe, p);
	kcb->kprobe_saved_flags = kcb->kprobe_old_flags
		= (regs->flags & X86_EFLAGS_IF);
पूर्ण

व्योम arch_prepare_kretprobe(काष्ठा kretprobe_instance *ri, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ *sara = stack_addr(regs);

	ri->ret_addr = (kprobe_opcode_t *) *sara;
	ri->fp = sara;

	/* Replace the वापस addr with trampoline addr */
	*sara = (अचिन्हित दीर्घ) &kretprobe_trampoline;
पूर्ण
NOKPROBE_SYMBOL(arch_prepare_kretprobe);

अटल व्योम kprobe_post_process(काष्ठा kprobe *cur, काष्ठा pt_regs *regs,
			       काष्ठा kprobe_ctlblk *kcb)
अणु
	अगर ((kcb->kprobe_status != KPROBE_REENTER) && cur->post_handler) अणु
		kcb->kprobe_status = KPROBE_HIT_SSDONE;
		cur->post_handler(cur, regs, 0);
	पूर्ण

	/* Restore back the original saved kprobes variables and जारी. */
	अगर (kcb->kprobe_status == KPROBE_REENTER)
		restore_previous_kprobe(kcb);
	अन्यथा
		reset_current_kprobe();
पूर्ण
NOKPROBE_SYMBOL(kprobe_post_process);

अटल व्योम setup_singlestep(काष्ठा kprobe *p, काष्ठा pt_regs *regs,
			     काष्ठा kprobe_ctlblk *kcb, पूर्णांक reenter)
अणु
	अगर (setup_detour_execution(p, regs, reenter))
		वापस;

#अगर !defined(CONFIG_PREEMPTION)
	अगर (p->ainsn.boostable) अणु
		/* Boost up -- we can execute copied inकाष्ठाions directly */
		अगर (!reenter)
			reset_current_kprobe();
		/*
		 * Reentering boosted probe करोesn't reset current_kprobe,
		 * nor set current_kprobe, because it करोesn't use single
		 * stepping.
		 */
		regs->ip = (अचिन्हित दीर्घ)p->ainsn.insn;
		वापस;
	पूर्ण
#पूर्ण_अगर
	अगर (reenter) अणु
		save_previous_kprobe(kcb);
		set_current_kprobe(p, regs, kcb);
		kcb->kprobe_status = KPROBE_REENTER;
	पूर्ण अन्यथा
		kcb->kprobe_status = KPROBE_HIT_SS;

	अगर (p->ainsn.emulate_op) अणु
		p->ainsn.emulate_op(p, regs);
		kprobe_post_process(p, regs, kcb);
		वापस;
	पूर्ण

	/* Disable पूर्णांकerrupt, and set ip रेजिस्टर on trampoline */
	regs->flags &= ~X86_EFLAGS_IF;
	regs->ip = (अचिन्हित दीर्घ)p->ainsn.insn;
पूर्ण
NOKPROBE_SYMBOL(setup_singlestep);

/*
 * Called after single-stepping.  p->addr is the address of the
 * inकाष्ठाion whose first byte has been replaced by the "int3"
 * inकाष्ठाion.  To aव्योम the SMP problems that can occur when we
 * temporarily put back the original opcode to single-step, we
 * single-stepped a copy of the inकाष्ठाion.  The address of this
 * copy is p->ainsn.insn. We also करोesn't use trap, but "int3" again
 * right after the copied inकाष्ठाion.
 * Dअगरferent from the trap single-step, "int3" single-step can not
 * handle the inकाष्ठाion which changes the ip रेजिस्टर, e.g. jmp,
 * call, conditional jmp, and the inकाष्ठाions which changes the IF
 * flags because पूर्णांकerrupt must be disabled around the single-stepping.
 * Such inकाष्ठाions are software emulated, but others are single-stepped
 * using "int3".
 *
 * When the 2nd "int3" handled, the regs->ip and regs->flags needs to
 * be adjusted, so that we can resume execution on correct code.
 */
अटल व्योम resume_singlestep(काष्ठा kprobe *p, काष्ठा pt_regs *regs,
			      काष्ठा kprobe_ctlblk *kcb)
अणु
	अचिन्हित दीर्घ copy_ip = (अचिन्हित दीर्घ)p->ainsn.insn;
	अचिन्हित दीर्घ orig_ip = (अचिन्हित दीर्घ)p->addr;

	/* Restore saved पूर्णांकerrupt flag and ip रेजिस्टर */
	regs->flags |= kcb->kprobe_saved_flags;
	/* Note that regs->ip is executed पूर्णांक3 so must be a step back */
	regs->ip += (orig_ip - copy_ip) - INT3_INSN_SIZE;
पूर्ण
NOKPROBE_SYMBOL(resume_singlestep);

/*
 * We have reentered the kprobe_handler(), since another probe was hit जबतक
 * within the handler. We save the original kprobes variables and just single
 * step on the inकाष्ठाion of the new probe without calling any user handlers.
 */
अटल पूर्णांक reenter_kprobe(काष्ठा kprobe *p, काष्ठा pt_regs *regs,
			  काष्ठा kprobe_ctlblk *kcb)
अणु
	चयन (kcb->kprobe_status) अणु
	हाल KPROBE_HIT_SSDONE:
	हाल KPROBE_HIT_ACTIVE:
	हाल KPROBE_HIT_SS:
		kprobes_inc_nmissed_count(p);
		setup_singlestep(p, regs, kcb, 1);
		अवरोध;
	हाल KPROBE_REENTER:
		/* A probe has been hit in the codepath leading up to, or just
		 * after, single-stepping of a probed inकाष्ठाion. This entire
		 * codepath should strictly reside in .kprobes.text section.
		 * Raise a BUG or we'll जारी in an endless reentering loop
		 * and eventually a stack overflow.
		 */
		pr_err("Unrecoverable kprobe detected.\n");
		dump_kprobe(p);
		BUG();
	शेष:
		/* impossible हालs */
		WARN_ON(1);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण
NOKPROBE_SYMBOL(reenter_kprobe);

अटल nokprobe_अंतरभूत पूर्णांक kprobe_is_ss(काष्ठा kprobe_ctlblk *kcb)
अणु
	वापस (kcb->kprobe_status == KPROBE_HIT_SS ||
		kcb->kprobe_status == KPROBE_REENTER);
पूर्ण

/*
 * Interrupts are disabled on entry as trap3 is an पूर्णांकerrupt gate and they
 * reमुख्य disabled throughout this function.
 */
पूर्णांक kprobe_पूर्णांक3_handler(काष्ठा pt_regs *regs)
अणु
	kprobe_opcode_t *addr;
	काष्ठा kprobe *p;
	काष्ठा kprobe_ctlblk *kcb;

	अगर (user_mode(regs))
		वापस 0;

	addr = (kprobe_opcode_t *)(regs->ip - माप(kprobe_opcode_t));
	/*
	 * We करोn't want to be preempted क्रम the entire duration of kprobe
	 * processing. Since पूर्णांक3 and debug trap disables irqs and we clear
	 * IF जबतक singlestepping, it must be no preemptible.
	 */

	kcb = get_kprobe_ctlblk();
	p = get_kprobe(addr);

	अगर (p) अणु
		अगर (kprobe_running()) अणु
			अगर (reenter_kprobe(p, regs, kcb))
				वापस 1;
		पूर्ण अन्यथा अणु
			set_current_kprobe(p, regs, kcb);
			kcb->kprobe_status = KPROBE_HIT_ACTIVE;

			/*
			 * If we have no pre-handler or it वापसed 0, we
			 * जारी with normal processing.  If we have a
			 * pre-handler and it वापसed non-zero, that means
			 * user handler setup रेजिस्टरs to निकास to another
			 * inकाष्ठाion, we must skip the single stepping.
			 */
			अगर (!p->pre_handler || !p->pre_handler(p, regs))
				setup_singlestep(p, regs, kcb, 0);
			अन्यथा
				reset_current_kprobe();
			वापस 1;
		पूर्ण
	पूर्ण अन्यथा अगर (kprobe_is_ss(kcb)) अणु
		p = kprobe_running();
		अगर ((अचिन्हित दीर्घ)p->ainsn.insn < regs->ip &&
		    (अचिन्हित दीर्घ)p->ainsn.insn + MAX_INSN_SIZE > regs->ip) अणु
			/* Most provably this is the second पूर्णांक3 क्रम singlestep */
			resume_singlestep(p, regs, kcb);
			kprobe_post_process(p, regs, kcb);
			वापस 1;
		पूर्ण
	पूर्ण

	अगर (*addr != INT3_INSN_OPCODE) अणु
		/*
		 * The अवरोधpoपूर्णांक inकाष्ठाion was हटाओd right
		 * after we hit it.  Another cpu has हटाओd
		 * either a probepoपूर्णांक or a debugger अवरोधpoपूर्णांक
		 * at this address.  In either हाल, no further
		 * handling of this पूर्णांकerrupt is appropriate.
		 * Back up over the (now missing) पूर्णांक3 and run
		 * the original inकाष्ठाion.
		 */
		regs->ip = (अचिन्हित दीर्घ)addr;
		वापस 1;
	पूर्ण /* अन्यथा: not a kprobe fault; let the kernel handle it */

	वापस 0;
पूर्ण
NOKPROBE_SYMBOL(kprobe_पूर्णांक3_handler);

/*
 * When a retprobed function वापसs, this code saves रेजिस्टरs and
 * calls trampoline_handler() runs, which calls the kretprobe's handler.
 */
यंत्र(
	".text\n"
	".global kretprobe_trampoline\n"
	".type kretprobe_trampoline, @function\n"
	"kretprobe_trampoline:\n"
	/* We करोn't bother saving the ss रेजिस्टर */
#अगर_घोषित CONFIG_X86_64
	"	pushq %rsp\n"
	"	pushfq\n"
	SAVE_REGS_STRING
	"	movq %rsp, %rdi\n"
	"	call trampoline_handler\n"
	/* Replace saved sp with true वापस address. */
	"	movq %rax, 19*8(%rsp)\n"
	RESTORE_REGS_STRING
	"	popfq\n"
#अन्यथा
	"	pushl %esp\n"
	"	pushfl\n"
	SAVE_REGS_STRING
	"	movl %esp, %eax\n"
	"	call trampoline_handler\n"
	/* Replace saved sp with true वापस address. */
	"	movl %eax, 15*4(%esp)\n"
	RESTORE_REGS_STRING
	"	popfl\n"
#पूर्ण_अगर
	"	ret\n"
	".size kretprobe_trampoline, .-kretprobe_trampoline\n"
);
NOKPROBE_SYMBOL(kretprobe_trampoline);
STACK_FRAME_NON_STANDARD(kretprobe_trampoline);


/*
 * Called from kretprobe_trampoline
 */
__used __visible व्योम *trampoline_handler(काष्ठा pt_regs *regs)
अणु
	/* fixup रेजिस्टरs */
	regs->cs = __KERNEL_CS;
#अगर_घोषित CONFIG_X86_32
	regs->gs = 0;
#पूर्ण_अगर
	regs->ip = (अचिन्हित दीर्घ)&kretprobe_trampoline;
	regs->orig_ax = ~0UL;

	वापस (व्योम *)kretprobe_trampoline_handler(regs, &kretprobe_trampoline, &regs->sp);
पूर्ण
NOKPROBE_SYMBOL(trampoline_handler);

पूर्णांक kprobe_fault_handler(काष्ठा pt_regs *regs, पूर्णांक trapnr)
अणु
	काष्ठा kprobe *cur = kprobe_running();
	काष्ठा kprobe_ctlblk *kcb = get_kprobe_ctlblk();

	अगर (unlikely(regs->ip == (अचिन्हित दीर्घ)cur->ainsn.insn)) अणु
		/* This must happen on single-stepping */
		WARN_ON(kcb->kprobe_status != KPROBE_HIT_SS &&
			kcb->kprobe_status != KPROBE_REENTER);
		/*
		 * We are here because the inकाष्ठाion being single
		 * stepped caused a page fault. We reset the current
		 * kprobe and the ip poपूर्णांकs back to the probe address
		 * and allow the page fault handler to जारी as a
		 * normal page fault.
		 */
		regs->ip = (अचिन्हित दीर्घ)cur->addr;

		/*
		 * If the IF flag was set beक्रमe the kprobe hit,
		 * करोn't touch it:
		 */
		regs->flags |= kcb->kprobe_old_flags;

		अगर (kcb->kprobe_status == KPROBE_REENTER)
			restore_previous_kprobe(kcb);
		अन्यथा
			reset_current_kprobe();
	पूर्ण अन्यथा अगर (kcb->kprobe_status == KPROBE_HIT_ACTIVE ||
		   kcb->kprobe_status == KPROBE_HIT_SSDONE) अणु
		/*
		 * We increment the nmissed count क्रम accounting,
		 * we can also use npre/npostfault count क्रम accounting
		 * these specअगरic fault हालs.
		 */
		kprobes_inc_nmissed_count(cur);

		/*
		 * We come here because inकाष्ठाions in the pre/post
		 * handler caused the page_fault, this could happen
		 * अगर handler tries to access user space by
		 * copy_from_user(), get_user() etc. Let the
		 * user-specअगरied handler try to fix it first.
		 */
		अगर (cur->fault_handler && cur->fault_handler(cur, regs, trapnr))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण
NOKPROBE_SYMBOL(kprobe_fault_handler);

पूर्णांक __init arch_populate_kprobe_blacklist(व्योम)
अणु
	वापस kprobe_add_area_blacklist((अचिन्हित दीर्घ)__entry_text_start,
					 (अचिन्हित दीर्घ)__entry_text_end);
पूर्ण

पूर्णांक __init arch_init_kprobes(व्योम)
अणु
	वापस 0;
पूर्ण

पूर्णांक arch_trampoline_kprobe(काष्ठा kprobe *p)
अणु
	वापस 0;
पूर्ण
