<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * 'traps.c' handles hardware traps and faults after we have saved some
 * state in 'entry.S'.
 *
 *  SuperH version: Copyright (C) 1999 Niibe Yutaka
 *                  Copyright (C) 2000 Philipp Rumpf
 *                  Copyright (C) 2000 David Howells
 *                  Copyright (C) 2002 - 2010 Paul Mundt
 */
#समावेश <linux/kernel.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/पन.स>
#समावेश <linux/bug.h>
#समावेश <linux/debug_locks.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/sysfs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/sched/task_stack.h>

#समावेश <यंत्र/alignment.h>
#समावेश <यंत्र/fpu.h>
#समावेश <यंत्र/kprobes.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/bl_bit.h>

#अगर_घोषित CONFIG_CPU_SH2
# define TRAP_RESERVED_INST	4
# define TRAP_ILLEGAL_SLOT_INST	6
# define TRAP_ADDRESS_ERROR	9
# अगरdef CONFIG_CPU_SH2A
#  define TRAP_UBC		12
#  define TRAP_FPU_ERROR	13
#  define TRAP_DIVZERO_ERROR	17
#  define TRAP_DIVOVF_ERROR	18
# endअगर
#अन्यथा
#घोषणा TRAP_RESERVED_INST	12
#घोषणा TRAP_ILLEGAL_SLOT_INST	13
#पूर्ण_अगर

अटल अंतरभूत व्योम sign_extend(अचिन्हित पूर्णांक count, अचिन्हित अक्षर *dst)
अणु
#अगर_घोषित __LITTLE_ENDIAN__
	अगर ((count == 1) && dst[0] & 0x80) अणु
		dst[1] = 0xff;
		dst[2] = 0xff;
		dst[3] = 0xff;
	पूर्ण
	अगर ((count == 2) && dst[1] & 0x80) अणु
		dst[2] = 0xff;
		dst[3] = 0xff;
	पूर्ण
#अन्यथा
	अगर ((count == 1) && dst[3] & 0x80) अणु
		dst[2] = 0xff;
		dst[1] = 0xff;
		dst[0] = 0xff;
	पूर्ण
	अगर ((count == 2) && dst[2] & 0x80) अणु
		dst[1] = 0xff;
		dst[0] = 0xff;
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल काष्ठा mem_access user_mem_access = अणु
	copy_from_user,
	copy_to_user,
पूर्ण;

/*
 * handle an inकाष्ठाion that करोes an unaligned memory access by emulating the
 * desired behaviour
 * - note that PC _may not_ poपूर्णांक to the faulting inकाष्ठाion
 *   (अगर that inकाष्ठाion is in a branch delay slot)
 * - वापस 0 अगर emulation okay, -EFAULT on existential error
 */
अटल पूर्णांक handle_unaligned_ins(insn_माप_प्रकार inकाष्ठाion, काष्ठा pt_regs *regs,
				काष्ठा mem_access *ma)
अणु
	पूर्णांक ret, index, count;
	अचिन्हित दीर्घ *rm, *rn;
	अचिन्हित अक्षर *src, *dst;
	अचिन्हित अक्षर __user *srcu, *dstu;

	index = (inकाष्ठाion>>8)&15;	/* 0x0F00 */
	rn = &regs->regs[index];

	index = (inकाष्ठाion>>4)&15;	/* 0x00F0 */
	rm = &regs->regs[index];

	count = 1<<(inकाष्ठाion&3);

	चयन (count) अणु
	हाल 1: inc_unaligned_byte_access(); अवरोध;
	हाल 2: inc_unaligned_word_access(); अवरोध;
	हाल 4: inc_unaligned_dword_access(); अवरोध;
	हाल 8: inc_unaligned_multi_access(); अवरोध;
	पूर्ण

	ret = -EFAULT;
	चयन (inकाष्ठाion>>12) अणु
	हाल 0: /* mov.[bwl] to/from memory via r0+rn */
		अगर (inकाष्ठाion & 8) अणु
			/* from memory */
			srcu = (अचिन्हित अक्षर __user *)*rm;
			srcu += regs->regs[0];
			dst = (अचिन्हित अक्षर *)rn;
			*(अचिन्हित दीर्घ *)dst = 0;

#अगर !defined(__LITTLE_ENDIAN__)
			dst += 4-count;
#पूर्ण_अगर
			अगर (ma->from(dst, srcu, count))
				जाओ fetch_fault;

			sign_extend(count, dst);
		पूर्ण अन्यथा अणु
			/* to memory */
			src = (अचिन्हित अक्षर *)rm;
#अगर !defined(__LITTLE_ENDIAN__)
			src += 4-count;
#पूर्ण_अगर
			dstu = (अचिन्हित अक्षर __user *)*rn;
			dstu += regs->regs[0];

			अगर (ma->to(dstu, src, count))
				जाओ fetch_fault;
		पूर्ण
		ret = 0;
		अवरोध;

	हाल 1: /* mov.l Rm,@(disp,Rn) */
		src = (अचिन्हित अक्षर*) rm;
		dstu = (अचिन्हित अक्षर __user *)*rn;
		dstu += (inकाष्ठाion&0x000F)<<2;

		अगर (ma->to(dstu, src, 4))
			जाओ fetch_fault;
		ret = 0;
		अवरोध;

	हाल 2: /* mov.[bwl] to memory, possibly with pre-decrement */
		अगर (inकाष्ठाion & 4)
			*rn -= count;
		src = (अचिन्हित अक्षर*) rm;
		dstu = (अचिन्हित अक्षर __user *)*rn;
#अगर !defined(__LITTLE_ENDIAN__)
		src += 4-count;
#पूर्ण_अगर
		अगर (ma->to(dstu, src, count))
			जाओ fetch_fault;
		ret = 0;
		अवरोध;

	हाल 5: /* mov.l @(disp,Rm),Rn */
		srcu = (अचिन्हित अक्षर __user *)*rm;
		srcu += (inकाष्ठाion & 0x000F) << 2;
		dst = (अचिन्हित अक्षर *)rn;
		*(अचिन्हित दीर्घ *)dst = 0;

		अगर (ma->from(dst, srcu, 4))
			जाओ fetch_fault;
		ret = 0;
		अवरोध;

	हाल 6:	/* mov.[bwl] from memory, possibly with post-increment */
		srcu = (अचिन्हित अक्षर __user *)*rm;
		अगर (inकाष्ठाion & 4)
			*rm += count;
		dst = (अचिन्हित अक्षर*) rn;
		*(अचिन्हित दीर्घ*)dst = 0;

#अगर !defined(__LITTLE_ENDIAN__)
		dst += 4-count;
#पूर्ण_अगर
		अगर (ma->from(dst, srcu, count))
			जाओ fetch_fault;
		sign_extend(count, dst);
		ret = 0;
		अवरोध;

	हाल 8:
		चयन ((inकाष्ठाion&0xFF00)>>8) अणु
		हाल 0x81: /* mov.w R0,@(disp,Rn) */
			src = (अचिन्हित अक्षर *) &regs->regs[0];
#अगर !defined(__LITTLE_ENDIAN__)
			src += 2;
#पूर्ण_अगर
			dstu = (अचिन्हित अक्षर __user *)*rm; /* called Rn in the spec */
			dstu += (inकाष्ठाion & 0x000F) << 1;

			अगर (ma->to(dstu, src, 2))
				जाओ fetch_fault;
			ret = 0;
			अवरोध;

		हाल 0x85: /* mov.w @(disp,Rm),R0 */
			srcu = (अचिन्हित अक्षर __user *)*rm;
			srcu += (inकाष्ठाion & 0x000F) << 1;
			dst = (अचिन्हित अक्षर *) &regs->regs[0];
			*(अचिन्हित दीर्घ *)dst = 0;

#अगर !defined(__LITTLE_ENDIAN__)
			dst += 2;
#पूर्ण_अगर
			अगर (ma->from(dst, srcu, 2))
				जाओ fetch_fault;
			sign_extend(2, dst);
			ret = 0;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल 9: /* mov.w @(disp,PC),Rn */
		srcu = (अचिन्हित अक्षर __user *)regs->pc;
		srcu += 4;
		srcu += (inकाष्ठाion & 0x00FF) << 1;
		dst = (अचिन्हित अक्षर *)rn;
		*(अचिन्हित दीर्घ *)dst = 0;

#अगर !defined(__LITTLE_ENDIAN__)
		dst += 2;
#पूर्ण_अगर

		अगर (ma->from(dst, srcu, 2))
			जाओ fetch_fault;
		sign_extend(2, dst);
		ret = 0;
		अवरोध;

	हाल 0xd: /* mov.l @(disp,PC),Rn */
		srcu = (अचिन्हित अक्षर __user *)(regs->pc & ~0x3);
		srcu += 4;
		srcu += (inकाष्ठाion & 0x00FF) << 2;
		dst = (अचिन्हित अक्षर *)rn;
		*(अचिन्हित दीर्घ *)dst = 0;

		अगर (ma->from(dst, srcu, 4))
			जाओ fetch_fault;
		ret = 0;
		अवरोध;
	पूर्ण
	वापस ret;

 fetch_fault:
	/* Argh. Address not only misaligned but also non-existent.
	 * Raise an EFAULT and see अगर it's trapped
	 */
	die_अगर_no_fixup("Fault in unaligned fixup", regs, 0);
	वापस -EFAULT;
पूर्ण

/*
 * emulate the inकाष्ठाion in the delay slot
 * - fetches the inकाष्ठाion from PC+2
 */
अटल अंतरभूत पूर्णांक handle_delayslot(काष्ठा pt_regs *regs,
				   insn_माप_प्रकार old_inकाष्ठाion,
				   काष्ठा mem_access *ma)
अणु
	insn_माप_प्रकार inकाष्ठाion;
	व्योम __user *addr = (व्योम __user *)(regs->pc +
		inकाष्ठाion_size(old_inकाष्ठाion));

	अगर (copy_from_user(&inकाष्ठाion, addr, माप(inकाष्ठाion))) अणु
		/* the inकाष्ठाion-fetch faulted */
		अगर (user_mode(regs))
			वापस -EFAULT;

		/* kernel */
		die("delay-slot-insn faulting in handle_unaligned_delayslot",
		    regs, 0);
	पूर्ण

	वापस handle_unaligned_ins(inकाष्ठाion, regs, ma);
पूर्ण

/*
 * handle an inकाष्ठाion that करोes an unaligned memory access
 * - have to be careful of branch delay-slot inकाष्ठाions that fault
 *  SH3:
 *   - अगर the branch would be taken PC poपूर्णांकs to the branch
 *   - अगर the branch would not be taken, PC poपूर्णांकs to delay-slot
 *  SH4:
 *   - PC always poपूर्णांकs to delayed branch
 * - वापस 0 अगर handled, -EFAULT अगर failed (may not वापस अगर in kernel)
 */

/* Macros to determine offset from current PC क्रम branch inकाष्ठाions */
/* Explicit type coercion is used to क्रमce sign extension where needed */
#घोषणा SH_PC_8BIT_OFFSET(instr) ((((चिन्हित अक्षर)(instr))*2) + 4)
#घोषणा SH_PC_12BIT_OFFSET(instr) ((((चिन्हित लघु)(instr<<4))>>3) + 4)

पूर्णांक handle_unaligned_access(insn_माप_प्रकार inकाष्ठाion, काष्ठा pt_regs *regs,
			    काष्ठा mem_access *ma, पूर्णांक expected,
			    अचिन्हित दीर्घ address)
अणु
	u_पूर्णांक rm;
	पूर्णांक ret, index;

	/*
	 * XXX: We can't handle mixed 16/32-bit inकाष्ठाions yet
	 */
	अगर (inकाष्ठाion_size(inकाष्ठाion) != 2)
		वापस -EINVAL;

	index = (inकाष्ठाion>>8)&15;	/* 0x0F00 */
	rm = regs->regs[index];

	/*
	 * Log the unexpected fixups, and then pass them on to perf.
	 *
	 * We पूर्णांकentionally करोn't report the expected हालs to perf as
	 * otherwise the trapped I/O हाल will skew the results too much
	 * to be useful.
	 */
	अगर (!expected) अणु
		unaligned_fixups_notअगरy(current, inकाष्ठाion, regs);
		perf_sw_event(PERF_COUNT_SW_ALIGNMENT_FAULTS, 1,
			      regs, address);
	पूर्ण

	ret = -EFAULT;
	चयन (inकाष्ठाion&0xF000) अणु
	हाल 0x0000:
		अगर (inकाष्ठाion==0x000B) अणु
			/* rts */
			ret = handle_delayslot(regs, inकाष्ठाion, ma);
			अगर (ret==0)
				regs->pc = regs->pr;
		पूर्ण
		अन्यथा अगर ((inकाष्ठाion&0x00FF)==0x0023) अणु
			/* braf @Rm */
			ret = handle_delayslot(regs, inकाष्ठाion, ma);
			अगर (ret==0)
				regs->pc += rm + 4;
		पूर्ण
		अन्यथा अगर ((inकाष्ठाion&0x00FF)==0x0003) अणु
			/* bsrf @Rm */
			ret = handle_delayslot(regs, inकाष्ठाion, ma);
			अगर (ret==0) अणु
				regs->pr = regs->pc + 4;
				regs->pc += rm + 4;
			पूर्ण
		पूर्ण
		अन्यथा अणु
			/* mov.[bwl] to/from memory via r0+rn */
			जाओ simple;
		पूर्ण
		अवरोध;

	हाल 0x1000: /* mov.l Rm,@(disp,Rn) */
		जाओ simple;

	हाल 0x2000: /* mov.[bwl] to memory, possibly with pre-decrement */
		जाओ simple;

	हाल 0x4000:
		अगर ((inकाष्ठाion&0x00FF)==0x002B) अणु
			/* jmp @Rm */
			ret = handle_delayslot(regs, inकाष्ठाion, ma);
			अगर (ret==0)
				regs->pc = rm;
		पूर्ण
		अन्यथा अगर ((inकाष्ठाion&0x00FF)==0x000B) अणु
			/* jsr @Rm */
			ret = handle_delayslot(regs, inकाष्ठाion, ma);
			अगर (ret==0) अणु
				regs->pr = regs->pc + 4;
				regs->pc = rm;
			पूर्ण
		पूर्ण
		अन्यथा अणु
			/* mov.[bwl] to/from memory via r0+rn */
			जाओ simple;
		पूर्ण
		अवरोध;

	हाल 0x5000: /* mov.l @(disp,Rm),Rn */
		जाओ simple;

	हाल 0x6000: /* mov.[bwl] from memory, possibly with post-increment */
		जाओ simple;

	हाल 0x8000: /* bf lab, bf/s lab, bt lab, bt/s lab */
		चयन (inकाष्ठाion&0x0F00) अणु
		हाल 0x0100: /* mov.w R0,@(disp,Rm) */
			जाओ simple;
		हाल 0x0500: /* mov.w @(disp,Rm),R0 */
			जाओ simple;
		हाल 0x0B00: /* bf   lab - no delayslot*/
			ret = 0;
			अवरोध;
		हाल 0x0F00: /* bf/s lab */
			ret = handle_delayslot(regs, inकाष्ठाion, ma);
			अगर (ret==0) अणु
#अगर defined(CONFIG_CPU_SH4) || defined(CONFIG_SH7705_CACHE_32KB)
				अगर ((regs->sr & 0x00000001) != 0)
					regs->pc += 4; /* next after slot */
				अन्यथा
#पूर्ण_अगर
					regs->pc += SH_PC_8BIT_OFFSET(inकाष्ठाion);
			पूर्ण
			अवरोध;
		हाल 0x0900: /* bt   lab - no delayslot */
			ret = 0;
			अवरोध;
		हाल 0x0D00: /* bt/s lab */
			ret = handle_delayslot(regs, inकाष्ठाion, ma);
			अगर (ret==0) अणु
#अगर defined(CONFIG_CPU_SH4) || defined(CONFIG_SH7705_CACHE_32KB)
				अगर ((regs->sr & 0x00000001) == 0)
					regs->pc += 4; /* next after slot */
				अन्यथा
#पूर्ण_अगर
					regs->pc += SH_PC_8BIT_OFFSET(inकाष्ठाion);
			पूर्ण
			अवरोध;
		पूर्ण
		अवरोध;

	हाल 0x9000: /* mov.w @(disp,Rm),Rn */
		जाओ simple;

	हाल 0xA000: /* bra label */
		ret = handle_delayslot(regs, inकाष्ठाion, ma);
		अगर (ret==0)
			regs->pc += SH_PC_12BIT_OFFSET(inकाष्ठाion);
		अवरोध;

	हाल 0xB000: /* bsr label */
		ret = handle_delayslot(regs, inकाष्ठाion, ma);
		अगर (ret==0) अणु
			regs->pr = regs->pc + 4;
			regs->pc += SH_PC_12BIT_OFFSET(inकाष्ठाion);
		पूर्ण
		अवरोध;

	हाल 0xD000: /* mov.l @(disp,Rm),Rn */
		जाओ simple;
	पूर्ण
	वापस ret;

	/* handle non-delay-slot inकाष्ठाion */
 simple:
	ret = handle_unaligned_ins(inकाष्ठाion, regs, ma);
	अगर (ret==0)
		regs->pc += inकाष्ठाion_size(inकाष्ठाion);
	वापस ret;
पूर्ण

/*
 * Handle various address error exceptions:
 *  - inकाष्ठाion address error:
 *       misaligned PC
 *       PC >= 0x80000000 in user mode
 *  - data address error (पढ़ो and ग_लिखो)
 *       misaligned data access
 *       access to >= 0x80000000 is user mode
 * Unक्रमtuntaly we can't distinguish between inकाष्ठाion address error
 * and data address errors caused by पढ़ो accesses.
 */
यंत्रlinkage व्योम करो_address_error(काष्ठा pt_regs *regs,
				 अचिन्हित दीर्घ ग_लिखोaccess,
				 अचिन्हित दीर्घ address)
अणु
	अचिन्हित दीर्घ error_code = 0;
	mm_segment_t oldfs;
	insn_माप_प्रकार inकाष्ठाion;
	पूर्णांक पंचांगp;

	/* Intentional अगरdef */
#अगर_घोषित CONFIG_CPU_HAS_SR_RB
	error_code = lookup_exception_vector();
#पूर्ण_अगर

	अगर (user_mode(regs)) अणु
		पूर्णांक si_code = BUS_ADRERR;
		अचिन्हित पूर्णांक user_action;

		local_irq_enable();
		inc_unaligned_user_access();

		oldfs = क्रमce_uaccess_begin();
		अगर (copy_from_user(&inकाष्ठाion, (insn_माप_प्रकार *)(regs->pc & ~1),
				   माप(inकाष्ठाion))) अणु
			क्रमce_uaccess_end(oldfs);
			जाओ uspace_segv;
		पूर्ण
		क्रमce_uaccess_end(oldfs);

		/* shout about userspace fixups */
		unaligned_fixups_notअगरy(current, inकाष्ठाion, regs);

		user_action = unaligned_user_action();
		अगर (user_action & UM_FIXUP)
			जाओ fixup;
		अगर (user_action & UM_SIGNAL)
			जाओ uspace_segv;
		अन्यथा अणु
			/* ignore */
			regs->pc += inकाष्ठाion_size(inकाष्ठाion);
			वापस;
		पूर्ण

fixup:
		/* bad PC is not something we can fix */
		अगर (regs->pc & 1) अणु
			si_code = BUS_ADRALN;
			जाओ uspace_segv;
		पूर्ण

		oldfs = क्रमce_uaccess_begin();
		पंचांगp = handle_unaligned_access(inकाष्ठाion, regs,
					      &user_mem_access, 0,
					      address);
		क्रमce_uaccess_end(oldfs);

		अगर (पंचांगp == 0)
			वापस; /* sorted */
uspace_segv:
		prपूर्णांकk(KERN_NOTICE "Sending SIGBUS to \"%s\" due to unaligned "
		       "access (PC %lx PR %lx)\n", current->comm, regs->pc,
		       regs->pr);

		क्रमce_sig_fault(SIGBUS, si_code, (व्योम __user *)address);
	पूर्ण अन्यथा अणु
		inc_unaligned_kernel_access();

		अगर (regs->pc & 1)
			die("unaligned program counter", regs, error_code);

		set_fs(KERNEL_DS);
		अगर (copy_from_user(&inकाष्ठाion, (व्योम __user *)(regs->pc),
				   माप(inकाष्ठाion))) अणु
			/* Argh. Fault on the inकाष्ठाion itself.
			   This should never happen non-SMP
			*/
			set_fs(oldfs);
			die("insn faulting in do_address_error", regs, 0);
		पूर्ण

		unaligned_fixups_notअगरy(current, inकाष्ठाion, regs);

		handle_unaligned_access(inकाष्ठाion, regs, &user_mem_access,
					0, address);
		set_fs(oldfs);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_SH_DSP
/*
 *	SH-DSP support gerg@snapgear.com.
 */
पूर्णांक is_dsp_inst(काष्ठा pt_regs *regs)
अणु
	अचिन्हित लघु inst = 0;

	/*
	 * Safe guard अगर DSP mode is alपढ़ोy enabled or we're lacking
	 * the DSP altogether.
	 */
	अगर (!(current_cpu_data.flags & CPU_HAS_DSP) || (regs->sr & SR_DSP))
		वापस 0;

	get_user(inst, ((अचिन्हित लघु *) regs->pc));

	inst &= 0xf000;

	/* Check क्रम any type of DSP or support inकाष्ठाion */
	अगर ((inst == 0xf000) || (inst == 0x4000))
		वापस 1;

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा is_dsp_inst(regs)	(0)
#पूर्ण_अगर /* CONFIG_SH_DSP */

#अगर_घोषित CONFIG_CPU_SH2A
यंत्रlinkage व्योम करो_भागide_error(अचिन्हित दीर्घ r4)
अणु
	पूर्णांक code;

	चयन (r4) अणु
	हाल TRAP_DIVZERO_ERROR:
		code = FPE_INTDIV;
		अवरोध;
	हाल TRAP_DIVOVF_ERROR:
		code = FPE_INTOVF;
		अवरोध;
	शेष:
		/* Let gcc know unhandled हालs करोn't make it past here */
		वापस;
	पूर्ण
	क्रमce_sig_fault(संक_भ_त्रुटि, code, शून्य);
पूर्ण
#पूर्ण_अगर

यंत्रlinkage व्योम करो_reserved_inst(व्योम)
अणु
	काष्ठा pt_regs *regs = current_pt_regs();
	अचिन्हित दीर्घ error_code;

#अगर_घोषित CONFIG_SH_FPU_EMU
	अचिन्हित लघु inst = 0;
	पूर्णांक err;

	get_user(inst, (अचिन्हित लघु*)regs->pc);

	err = करो_fpu_inst(inst, regs);
	अगर (!err) अणु
		regs->pc += inकाष्ठाion_size(inst);
		वापस;
	पूर्ण
	/* not a FPU inst. */
#पूर्ण_अगर

#अगर_घोषित CONFIG_SH_DSP
	/* Check अगर it's a DSP inकाष्ठाion */
	अगर (is_dsp_inst(regs)) अणु
		/* Enable DSP mode, and restart inकाष्ठाion. */
		regs->sr |= SR_DSP;
		/* Save DSP mode */
		current->thपढ़ो.dsp_status.status |= SR_DSP;
		वापस;
	पूर्ण
#पूर्ण_अगर

	error_code = lookup_exception_vector();

	local_irq_enable();
	क्रमce_sig(संक_अवैध);
	die_अगर_no_fixup("reserved instruction", regs, error_code);
पूर्ण

#अगर_घोषित CONFIG_SH_FPU_EMU
अटल पूर्णांक emulate_branch(अचिन्हित लघु inst, काष्ठा pt_regs *regs)
अणु
	/*
	 * bfs: 8fxx: PC+=d*2+4;
	 * bts: 8dxx: PC+=d*2+4;
	 * bra: axxx: PC+=D*2+4;
	 * bsr: bxxx: PC+=D*2+4  after PR=PC+4;
	 * braf:0x23: PC+=Rn*2+4;
	 * bsrf:0x03: PC+=Rn*2+4 after PR=PC+4;
	 * jmp: 4x2b: PC=Rn;
	 * jsr: 4x0b: PC=Rn      after PR=PC+4;
	 * rts: 000b: PC=PR;
	 */
	अगर (((inst & 0xf000) == 0xb000)  ||	/* bsr */
	    ((inst & 0xf0ff) == 0x0003)  ||	/* bsrf */
	    ((inst & 0xf0ff) == 0x400b))	/* jsr */
		regs->pr = regs->pc + 4;

	अगर ((inst & 0xfd00) == 0x8d00) अणु	/* bfs, bts */
		regs->pc += SH_PC_8BIT_OFFSET(inst);
		वापस 0;
	पूर्ण

	अगर ((inst & 0xe000) == 0xa000) अणु	/* bra, bsr */
		regs->pc += SH_PC_12BIT_OFFSET(inst);
		वापस 0;
	पूर्ण

	अगर ((inst & 0xf0df) == 0x0003) अणु	/* braf, bsrf */
		regs->pc += regs->regs[(inst & 0x0f00) >> 8] + 4;
		वापस 0;
	पूर्ण

	अगर ((inst & 0xf0df) == 0x400b) अणु	/* jmp, jsr */
		regs->pc = regs->regs[(inst & 0x0f00) >> 8];
		वापस 0;
	पूर्ण

	अगर ((inst & 0xffff) == 0x000b) अणु	/* rts */
		regs->pc = regs->pr;
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण
#पूर्ण_अगर

यंत्रlinkage व्योम करो_illegal_slot_inst(व्योम)
अणु
	काष्ठा pt_regs *regs = current_pt_regs();
	अचिन्हित दीर्घ inst;

	अगर (kprobe_handle_illslot(regs->pc) == 0)
		वापस;

#अगर_घोषित CONFIG_SH_FPU_EMU
	get_user(inst, (अचिन्हित लघु *)regs->pc + 1);
	अगर (!करो_fpu_inst(inst, regs)) अणु
		get_user(inst, (अचिन्हित लघु *)regs->pc);
		अगर (!emulate_branch(inst, regs))
			वापस;
		/* fault in branch.*/
	पूर्ण
	/* not a FPU inst. */
#पूर्ण_अगर

	inst = lookup_exception_vector();

	local_irq_enable();
	क्रमce_sig(संक_अवैध);
	die_अगर_no_fixup("illegal slot instruction", regs, inst);
पूर्ण

यंत्रlinkage व्योम करो_exception_error(व्योम)
अणु
	दीर्घ ex;

	ex = lookup_exception_vector();
	die_अगर_kernel("exception", current_pt_regs(), ex);
पूर्ण

व्योम per_cpu_trap_init(व्योम)
अणु
	बाह्य व्योम *vbr_base;

	/* NOTE: The VBR value should be at P1
	   (or P2, virtural "fixed" address space).
	   It's definitely should not in physical address.  */

	यंत्र अस्थिर("ldc	%0, vbr"
		     : /* no output */
		     : "r" (&vbr_base)
		     : "memory");

	/* disable exception blocking now when the vbr has been setup */
	clear_bl_bit();
पूर्ण

व्योम *set_exception_table_vec(अचिन्हित पूर्णांक vec, व्योम *handler)
अणु
	बाह्य व्योम *exception_handling_table[];
	व्योम *old_handler;

	old_handler = exception_handling_table[vec];
	exception_handling_table[vec] = handler;
	वापस old_handler;
पूर्ण

व्योम __init trap_init(व्योम)
अणु
	set_exception_table_vec(TRAP_RESERVED_INST, करो_reserved_inst);
	set_exception_table_vec(TRAP_ILLEGAL_SLOT_INST, करो_illegal_slot_inst);

#अगर defined(CONFIG_CPU_SH4) && !defined(CONFIG_SH_FPU) || \
    defined(CONFIG_SH_FPU_EMU)
	/*
	 * For SH-4 lacking an FPU, treat भग्नing poपूर्णांक inकाष्ठाions as
	 * reserved. They'll be handled in the math-emu हाल, or faulted on
	 * otherwise.
	 */
	set_exception_table_evt(0x800, करो_reserved_inst);
	set_exception_table_evt(0x820, करो_illegal_slot_inst);
#या_अगर defined(CONFIG_SH_FPU)
	set_exception_table_evt(0x800, fpu_state_restore_trap_handler);
	set_exception_table_evt(0x820, fpu_state_restore_trap_handler);
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_SH2
	set_exception_table_vec(TRAP_ADDRESS_ERROR, address_error_trap_handler);
#पूर्ण_अगर
#अगर_घोषित CONFIG_CPU_SH2A
	set_exception_table_vec(TRAP_DIVZERO_ERROR, करो_भागide_error);
	set_exception_table_vec(TRAP_DIVOVF_ERROR, करो_भागide_error);
#अगर_घोषित CONFIG_SH_FPU
	set_exception_table_vec(TRAP_FPU_ERROR, fpu_error_trap_handler);
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित TRAP_UBC
	set_exception_table_vec(TRAP_UBC, अवरोधpoपूर्णांक_trap_handler);
#पूर्ण_अगर
पूर्ण
