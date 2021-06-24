<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1994 - 1999, 2000 by Ralf Baechle and others.
 * Copyright (C) 2005, 2006 by Ralf Baechle (ralf@linux-mips.org)
 * Copyright (C) 1999, 2000 Silicon Graphics, Inc.
 * Copyright (C) 2004 Thiemo Seufer
 * Copyright (C) 2013  Imagination Technologies Ltd.
 */
#समावेश <linux/cpu.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/kernel.h>
#समावेश <linux/nmi.h>
#समावेश <linux/personality.h>
#समावेश <linux/prctl.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task_stack.h>

#समावेश <यंत्र/abi.h>
#समावेश <यंत्र/यंत्र.h>
#समावेश <यंत्र/dsemul.h>
#समावेश <यंत्र/dsp.h>
#समावेश <यंत्र/exec.h>
#समावेश <यंत्र/fpu.h>
#समावेश <यंत्र/inst.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/irq_regs.h>
#समावेश <यंत्र/isadep.h>
#समावेश <यंत्र/msa.h>
#समावेश <यंत्र/mips-cps.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/stacktrace.h>

#अगर_घोषित CONFIG_HOTPLUG_CPU
व्योम arch_cpu_idle_dead(व्योम)
अणु
	play_dead();
पूर्ण
#पूर्ण_अगर

यंत्रlinkage व्योम ret_from_विभाजन(व्योम);
यंत्रlinkage व्योम ret_from_kernel_thपढ़ो(व्योम);

व्योम start_thपढ़ो(काष्ठा pt_regs * regs, अचिन्हित दीर्घ pc, अचिन्हित दीर्घ sp)
अणु
	अचिन्हित दीर्घ status;

	/* New thपढ़ो loses kernel privileges. */
	status = regs->cp0_status & ~(ST0_CU0|ST0_CU1|ST0_CU2|ST0_FR|KU_MASK);
	status |= KU_USER;
	regs->cp0_status = status;
	lose_fpu(0);
	clear_thपढ़ो_flag(TIF_MSA_CTX_LIVE);
	clear_used_math();
#अगर_घोषित CONFIG_MIPS_FP_SUPPORT
	atomic_set(&current->thपढ़ो.bd_emu_frame, BD_EMUFRAME_NONE);
#पूर्ण_अगर
	init_dsp();
	regs->cp0_epc = pc;
	regs->regs[29] = sp;
पूर्ण

व्योम निकास_thपढ़ो(काष्ठा task_काष्ठा *tsk)
अणु
	/*
	 * User thपढ़ोs may have allocated a delay slot emulation frame.
	 * If so, clean up that allocation.
	 */
	अगर (!(current->flags & PF_KTHREAD))
		dsemul_thपढ़ो_cleanup(tsk);
पूर्ण

पूर्णांक arch_dup_task_काष्ठा(काष्ठा task_काष्ठा *dst, काष्ठा task_काष्ठा *src)
अणु
	/*
	 * Save any process state which is live in hardware रेजिस्टरs to the
	 * parent context prior to duplication. This prevents the new child
	 * state becoming stale अगर the parent is preempted beक्रमe copy_thपढ़ो()
	 * माला_लो a chance to save the parent's live hardware रेजिस्टरs to the
	 * child context.
	 */
	preempt_disable();

	अगर (is_msa_enabled())
		save_msa(current);
	अन्यथा अगर (is_fpu_owner())
		_save_fp(current);

	save_dsp(current);

	preempt_enable();

	*dst = *src;
	वापस 0;
पूर्ण

/*
 * Copy architecture-specअगरic thपढ़ो state
 */
पूर्णांक copy_thपढ़ो(अचिन्हित दीर्घ clone_flags, अचिन्हित दीर्घ usp,
		अचिन्हित दीर्घ kthपढ़ो_arg, काष्ठा task_काष्ठा *p,
		अचिन्हित दीर्घ tls)
अणु
	काष्ठा thपढ़ो_info *ti = task_thपढ़ो_info(p);
	काष्ठा pt_regs *childregs, *regs = current_pt_regs();
	अचिन्हित दीर्घ childksp;

	childksp = (अचिन्हित दीर्घ)task_stack_page(p) + THREAD_SIZE - 32;

	/* set up new TSS. */
	childregs = (काष्ठा pt_regs *) childksp - 1;
	/*  Put the stack after the काष्ठा pt_regs.  */
	childksp = (अचिन्हित दीर्घ) childregs;
	p->thपढ़ो.cp0_status = (पढ़ो_c0_status() & ~(ST0_CU2|ST0_CU1)) | ST0_KERNEL_CUMASK;
	अगर (unlikely(p->flags & (PF_KTHREAD | PF_IO_WORKER))) अणु
		/* kernel thपढ़ो */
		अचिन्हित दीर्घ status = p->thपढ़ो.cp0_status;
		स_रखो(childregs, 0, माप(काष्ठा pt_regs));
		p->thपढ़ो.reg16 = usp; /* fn */
		p->thपढ़ो.reg17 = kthपढ़ो_arg;
		p->thपढ़ो.reg29 = childksp;
		p->thपढ़ो.reg31 = (अचिन्हित दीर्घ) ret_from_kernel_thपढ़ो;
#अगर defined(CONFIG_CPU_R3000) || defined(CONFIG_CPU_TX39XX)
		status = (status & ~(ST0_KUP | ST0_IEP | ST0_IEC)) |
			 ((status & (ST0_KUC | ST0_IEC)) << 2);
#अन्यथा
		status |= ST0_EXL;
#पूर्ण_अगर
		childregs->cp0_status = status;
		वापस 0;
	पूर्ण

	/* user thपढ़ो */
	*childregs = *regs;
	childregs->regs[7] = 0; /* Clear error flag */
	childregs->regs[2] = 0; /* Child माला_लो zero as वापस value */
	अगर (usp)
		childregs->regs[29] = usp;

	p->thपढ़ो.reg29 = (अचिन्हित दीर्घ) childregs;
	p->thपढ़ो.reg31 = (अचिन्हित दीर्घ) ret_from_विभाजन;

	/*
	 * New tasks lose permission to use the fpu. This accelerates context
	 * चयनing क्रम most programs since they करोn't use the fpu.
	 */
	childregs->cp0_status &= ~(ST0_CU2|ST0_CU1);

	clear_tsk_thपढ़ो_flag(p, TIF_USEDFPU);
	clear_tsk_thपढ़ो_flag(p, TIF_USEDMSA);
	clear_tsk_thपढ़ो_flag(p, TIF_MSA_CTX_LIVE);

#अगर_घोषित CONFIG_MIPS_MT_FPAFF
	clear_tsk_thपढ़ो_flag(p, TIF_FPUBOUND);
#पूर्ण_अगर /* CONFIG_MIPS_MT_FPAFF */

#अगर_घोषित CONFIG_MIPS_FP_SUPPORT
	atomic_set(&p->thपढ़ो.bd_emu_frame, BD_EMUFRAME_NONE);
#पूर्ण_अगर

	अगर (clone_flags & CLONE_SETTLS)
		ti->tp_value = tls;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_STACKPROTECTOR
#समावेश <linux/stackprotector.h>
अचिन्हित दीर्घ __stack_chk_guard __पढ़ो_mostly;
EXPORT_SYMBOL(__stack_chk_guard);
#पूर्ण_अगर

काष्ठा mips_frame_info अणु
	व्योम		*func;
	अचिन्हित दीर्घ	func_size;
	पूर्णांक		frame_size;
	पूर्णांक		pc_offset;
पूर्ण;

#घोषणा J_TARGET(pc,target)	\
		(((अचिन्हित दीर्घ)(pc) & 0xf0000000) | ((target) << 2))

अटल अंतरभूत पूर्णांक is_jr_ra_ins(जोड़ mips_inकाष्ठाion *ip)
अणु
#अगर_घोषित CONFIG_CPU_MICROMIPS
	/*
	 * jr16 ra
	 * jr ra
	 */
	अगर (mm_insn_16bit(ip->word >> 16)) अणु
		अगर (ip->mm16_r5_क्रमmat.opcode == mm_pool16c_op &&
		    ip->mm16_r5_क्रमmat.rt == mm_jr16_op &&
		    ip->mm16_r5_क्रमmat.imm == 31)
			वापस 1;
		वापस 0;
	पूर्ण

	अगर (ip->r_क्रमmat.opcode == mm_pool32a_op &&
	    ip->r_क्रमmat.func == mm_pool32axf_op &&
	    ((ip->u_क्रमmat.uimmediate >> 6) & GENMASK(9, 0)) == mm_jalr_op &&
	    ip->r_क्रमmat.rt == 31)
		वापस 1;
	वापस 0;
#अन्यथा
	अगर (ip->r_क्रमmat.opcode == spec_op &&
	    ip->r_क्रमmat.func == jr_op &&
	    ip->r_क्रमmat.rs == 31)
		वापस 1;
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक is_ra_save_ins(जोड़ mips_inकाष्ठाion *ip, पूर्णांक *poff)
अणु
#अगर_घोषित CONFIG_CPU_MICROMIPS
	/*
	 * swsp ra,offset
	 * swm16 reglist,offset(sp)
	 * swm32 reglist,offset(sp)
	 * sw32 ra,offset(sp)
	 * jradiussp - NOT SUPPORTED
	 *
	 * microMIPS is way more fun...
	 */
	अगर (mm_insn_16bit(ip->word >> 16)) अणु
		चयन (ip->mm16_r5_क्रमmat.opcode) अणु
		हाल mm_swsp16_op:
			अगर (ip->mm16_r5_क्रमmat.rt != 31)
				वापस 0;

			*poff = ip->mm16_r5_क्रमmat.imm;
			*poff = (*poff << 2) / माप(uदीर्घ);
			वापस 1;

		हाल mm_pool16c_op:
			चयन (ip->mm16_m_क्रमmat.func) अणु
			हाल mm_swm16_op:
				*poff = ip->mm16_m_क्रमmat.imm;
				*poff += 1 + ip->mm16_m_क्रमmat.rlist;
				*poff = (*poff << 2) / माप(uदीर्घ);
				वापस 1;

			शेष:
				वापस 0;
			पूर्ण

		शेष:
			वापस 0;
		पूर्ण
	पूर्ण

	चयन (ip->i_क्रमmat.opcode) अणु
	हाल mm_sw32_op:
		अगर (ip->i_क्रमmat.rs != 29)
			वापस 0;
		अगर (ip->i_क्रमmat.rt != 31)
			वापस 0;

		*poff = ip->i_क्रमmat.simmediate / माप(uदीर्घ);
		वापस 1;

	हाल mm_pool32b_op:
		चयन (ip->mm_m_क्रमmat.func) अणु
		हाल mm_swm32_func:
			अगर (ip->mm_m_क्रमmat.rd < 0x10)
				वापस 0;
			अगर (ip->mm_m_क्रमmat.base != 29)
				वापस 0;

			*poff = ip->mm_m_क्रमmat.simmediate;
			*poff += (ip->mm_m_क्रमmat.rd & 0xf) * माप(u32);
			*poff /= माप(uदीर्घ);
			वापस 1;
		शेष:
			वापस 0;
		पूर्ण

	शेष:
		वापस 0;
	पूर्ण
#अन्यथा
	/* sw / sd $ra, offset($sp) */
	अगर ((ip->i_क्रमmat.opcode == sw_op || ip->i_क्रमmat.opcode == sd_op) &&
		ip->i_क्रमmat.rs == 29 && ip->i_क्रमmat.rt == 31) अणु
		*poff = ip->i_क्रमmat.simmediate / माप(uदीर्घ);
		वापस 1;
	पूर्ण
#अगर_घोषित CONFIG_CPU_LOONGSON64
	अगर ((ip->loongson3_lswc2_क्रमmat.opcode == swc2_op) &&
		      (ip->loongson3_lswc2_क्रमmat.ls == 1) &&
		      (ip->loongson3_lswc2_क्रमmat.fr == 0) &&
		      (ip->loongson3_lswc2_क्रमmat.base == 29)) अणु
		अगर (ip->loongson3_lswc2_क्रमmat.rt == 31) अणु
			*poff = ip->loongson3_lswc2_क्रमmat.offset << 1;
			वापस 1;
		पूर्ण
		अगर (ip->loongson3_lswc2_क्रमmat.rq == 31) अणु
			*poff = (ip->loongson3_lswc2_क्रमmat.offset << 1) + 1;
			वापस 1;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक is_jump_ins(जोड़ mips_inकाष्ठाion *ip)
अणु
#अगर_घोषित CONFIG_CPU_MICROMIPS
	/*
	 * jr16,jrc,jalr16,jalr16
	 * jal
	 * jalr/jr,jalr.hb/jr.hb,jalrs,jalrs.hb
	 * jraddiusp - NOT SUPPORTED
	 *
	 * microMIPS is kind of more fun...
	 */
	अगर (mm_insn_16bit(ip->word >> 16)) अणु
		अगर ((ip->mm16_r5_क्रमmat.opcode == mm_pool16c_op &&
		    (ip->mm16_r5_क्रमmat.rt & mm_jr16_op) == mm_jr16_op))
			वापस 1;
		वापस 0;
	पूर्ण

	अगर (ip->j_क्रमmat.opcode == mm_j32_op)
		वापस 1;
	अगर (ip->j_क्रमmat.opcode == mm_jal32_op)
		वापस 1;
	अगर (ip->r_क्रमmat.opcode != mm_pool32a_op ||
			ip->r_क्रमmat.func != mm_pool32axf_op)
		वापस 0;
	वापस ((ip->u_क्रमmat.uimmediate >> 6) & mm_jalr_op) == mm_jalr_op;
#अन्यथा
	अगर (ip->j_क्रमmat.opcode == j_op)
		वापस 1;
	अगर (ip->j_क्रमmat.opcode == jal_op)
		वापस 1;
	अगर (ip->r_क्रमmat.opcode != spec_op)
		वापस 0;
	वापस ip->r_क्रमmat.func == jalr_op || ip->r_क्रमmat.func == jr_op;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक is_sp_move_ins(जोड़ mips_inकाष्ठाion *ip, पूर्णांक *frame_size)
अणु
#अगर_घोषित CONFIG_CPU_MICROMIPS
	अचिन्हित लघु पंचांगp;

	/*
	 * addiusp -imm
	 * addius5 sp,-imm
	 * addiu32 sp,sp,-imm
	 * jradiussp - NOT SUPPORTED
	 *
	 * microMIPS is not more fun...
	 */
	अगर (mm_insn_16bit(ip->word >> 16)) अणु
		अगर (ip->mm16_r3_क्रमmat.opcode == mm_pool16d_op &&
		    ip->mm16_r3_क्रमmat.simmediate & mm_addiusp_func) अणु
			पंचांगp = ip->mm_b0_क्रमmat.simmediate >> 1;
			पंचांगp = ((पंचांगp & 0x1ff) ^ 0x100) - 0x100;
			अगर ((पंचांगp + 2) < 4) /* 0x0,0x1,0x1fe,0x1ff are special */
				पंचांगp ^= 0x100;
			*frame_size = -(चिन्हित लघु)(पंचांगp << 2);
			वापस 1;
		पूर्ण
		अगर (ip->mm16_r5_क्रमmat.opcode == mm_pool16d_op &&
		    ip->mm16_r5_क्रमmat.rt == 29) अणु
			पंचांगp = ip->mm16_r5_क्रमmat.imm >> 1;
			*frame_size = -(चिन्हित लघु)(पंचांगp & 0xf);
			वापस 1;
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (ip->mm_i_क्रमmat.opcode == mm_addiu32_op &&
	    ip->mm_i_क्रमmat.rt == 29 && ip->mm_i_क्रमmat.rs == 29) अणु
		*frame_size = -ip->i_क्रमmat.simmediate;
		वापस 1;
	पूर्ण
#अन्यथा
	/* addiu/daddiu sp,sp,-imm */
	अगर (ip->i_क्रमmat.rs != 29 || ip->i_क्रमmat.rt != 29)
		वापस 0;

	अगर (ip->i_क्रमmat.opcode == addiu_op ||
	    ip->i_क्रमmat.opcode == daddiu_op) अणु
		*frame_size = -ip->i_क्रमmat.simmediate;
		वापस 1;
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक get_frame_info(काष्ठा mips_frame_info *info)
अणु
	bool is_mmips = IS_ENABLED(CONFIG_CPU_MICROMIPS);
	जोड़ mips_inकाष्ठाion insn, *ip, *ip_end;
	अचिन्हित पूर्णांक last_insn_size = 0;
	bool saw_jump = false;

	info->pc_offset = -1;
	info->frame_size = 0;

	ip = (व्योम *)msk_isa16_mode((uदीर्घ)info->func);
	अगर (!ip)
		जाओ err;

	ip_end = (व्योम *)ip + (info->func_size ? info->func_size : 512);

	जबतक (ip < ip_end) अणु
		ip = (व्योम *)ip + last_insn_size;

		अगर (is_mmips && mm_insn_16bit(ip->halfword[0])) अणु
			insn.word = ip->halfword[0] << 16;
			last_insn_size = 2;
		पूर्ण अन्यथा अगर (is_mmips) अणु
			insn.word = ip->halfword[0] << 16 | ip->halfword[1];
			last_insn_size = 4;
		पूर्ण अन्यथा अणु
			insn.word = ip->word;
			last_insn_size = 4;
		पूर्ण

		अगर (is_jr_ra_ins(ip)) अणु
			अवरोध;
		पूर्ण अन्यथा अगर (!info->frame_size) अणु
			is_sp_move_ins(&insn, &info->frame_size);
			जारी;
		पूर्ण अन्यथा अगर (!saw_jump && is_jump_ins(ip)) अणु
			/*
			 * If we see a jump inकाष्ठाion, we are finished
			 * with the frame save.
			 *
			 * Some functions can have a लघुcut वापस at
			 * the beginning of the function, so करोn't start
			 * looking क्रम jump inकाष्ठाion until we see the
			 * frame setup.
			 *
			 * The RA save inकाष्ठाion can get put पूर्णांकo the
			 * delay slot of the jump inकाष्ठाion, so look
			 * at the next inकाष्ठाion, too.
			 */
			saw_jump = true;
			जारी;
		पूर्ण
		अगर (info->pc_offset == -1 &&
		    is_ra_save_ins(&insn, &info->pc_offset))
			अवरोध;
		अगर (saw_jump)
			अवरोध;
	पूर्ण
	अगर (info->frame_size && info->pc_offset >= 0) /* nested */
		वापस 0;
	अगर (info->pc_offset < 0) /* leaf */
		वापस 1;
	/* prologue seems bogus... */
err:
	वापस -1;
पूर्ण

अटल काष्ठा mips_frame_info schedule_mfi __पढ़ो_mostly;

#अगर_घोषित CONFIG_KALLSYMS
अटल अचिन्हित दीर्घ get___schedule_addr(व्योम)
अणु
	वापस kallsyms_lookup_name("__schedule");
पूर्ण
#अन्यथा
अटल अचिन्हित दीर्घ get___schedule_addr(व्योम)
अणु
	जोड़ mips_inकाष्ठाion *ip = (व्योम *)schedule;
	पूर्णांक max_insns = 8;
	पूर्णांक i;

	क्रम (i = 0; i < max_insns; i++, ip++) अणु
		अगर (ip->j_क्रमmat.opcode == j_op)
			वापस J_TARGET(ip, ip->j_क्रमmat.target);
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init frame_info_init(व्योम)
अणु
	अचिन्हित दीर्घ size = 0;
#अगर_घोषित CONFIG_KALLSYMS
	अचिन्हित दीर्घ ofs;
#पूर्ण_अगर
	अचिन्हित दीर्घ addr;

	addr = get___schedule_addr();
	अगर (!addr)
		addr = (अचिन्हित दीर्घ)schedule;

#अगर_घोषित CONFIG_KALLSYMS
	kallsyms_lookup_size_offset(addr, &size, &ofs);
#पूर्ण_अगर
	schedule_mfi.func = (व्योम *)addr;
	schedule_mfi.func_size = size;

	get_frame_info(&schedule_mfi);

	/*
	 * Without schedule() frame info, result given by
	 * thपढ़ो_saved_pc() and get_wchan() are not reliable.
	 */
	अगर (schedule_mfi.pc_offset < 0)
		prपूर्णांकk("Can't analyze schedule() prologue at %p\n", schedule);

	वापस 0;
पूर्ण

arch_initcall(frame_info_init);

/*
 * Return saved PC of a blocked thपढ़ो.
 */
अटल अचिन्हित दीर्घ thपढ़ो_saved_pc(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा thपढ़ो_काष्ठा *t = &tsk->thपढ़ो;

	/* New born processes are a special हाल */
	अगर (t->reg31 == (अचिन्हित दीर्घ) ret_from_विभाजन)
		वापस t->reg31;
	अगर (schedule_mfi.pc_offset < 0)
		वापस 0;
	वापस ((अचिन्हित दीर्घ *)t->reg29)[schedule_mfi.pc_offset];
पूर्ण


#अगर_घोषित CONFIG_KALLSYMS
/* generic stack unwinding function */
अचिन्हित दीर्घ notrace unwind_stack_by_address(अचिन्हित दीर्घ stack_page,
					      अचिन्हित दीर्घ *sp,
					      अचिन्हित दीर्घ pc,
					      अचिन्हित दीर्घ *ra)
अणु
	अचिन्हित दीर्घ low, high, irq_stack_high;
	काष्ठा mips_frame_info info;
	अचिन्हित दीर्घ size, ofs;
	काष्ठा pt_regs *regs;
	पूर्णांक leaf;

	अगर (!stack_page)
		वापस 0;

	/*
	 * IRQ stacks start at IRQ_STACK_START
	 * task stacks at THREAD_SIZE - 32
	 */
	low = stack_page;
	अगर (!preemptible() && on_irq_stack(raw_smp_processor_id(), *sp)) अणु
		high = stack_page + IRQ_STACK_START;
		irq_stack_high = high;
	पूर्ण अन्यथा अणु
		high = stack_page + THREAD_SIZE - 32;
		irq_stack_high = 0;
	पूर्ण

	/*
	 * If we reached the top of the पूर्णांकerrupt stack, start unwinding
	 * the पूर्णांकerrupted task stack.
	 */
	अगर (unlikely(*sp == irq_stack_high)) अणु
		अचिन्हित दीर्घ task_sp = *(अचिन्हित दीर्घ *)*sp;

		/*
		 * Check that the poपूर्णांकer saved in the IRQ stack head poपूर्णांकs to
		 * something within the stack of the current task
		 */
		अगर (!object_is_on_stack((व्योम *)task_sp))
			वापस 0;

		/*
		 * Follow poपूर्णांकer to tasks kernel stack frame where पूर्णांकerrupted
		 * state was saved.
		 */
		regs = (काष्ठा pt_regs *)task_sp;
		pc = regs->cp0_epc;
		अगर (!user_mode(regs) && __kernel_text_address(pc)) अणु
			*sp = regs->regs[29];
			*ra = regs->regs[31];
			वापस pc;
		पूर्ण
		वापस 0;
	पूर्ण
	अगर (!kallsyms_lookup_size_offset(pc, &size, &ofs))
		वापस 0;
	/*
	 * Return ra अगर an exception occurred at the first inकाष्ठाion
	 */
	अगर (unlikely(ofs == 0)) अणु
		pc = *ra;
		*ra = 0;
		वापस pc;
	पूर्ण

	info.func = (व्योम *)(pc - ofs);
	info.func_size = ofs;	/* analyze from start to ofs */
	leaf = get_frame_info(&info);
	अगर (leaf < 0)
		वापस 0;

	अगर (*sp < low || *sp + info.frame_size > high)
		वापस 0;

	अगर (leaf)
		/*
		 * For some extreme हालs, get_frame_info() can
		 * consider wrongly a nested function as a leaf
		 * one. In that हालs aव्योम to वापस always the
		 * same value.
		 */
		pc = pc != *ra ? *ra : 0;
	अन्यथा
		pc = ((अचिन्हित दीर्घ *)(*sp))[info.pc_offset];

	*sp += info.frame_size;
	*ra = 0;
	वापस __kernel_text_address(pc) ? pc : 0;
पूर्ण
EXPORT_SYMBOL(unwind_stack_by_address);

/* used by show_backtrace() */
अचिन्हित दीर्घ unwind_stack(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ *sp,
			   अचिन्हित दीर्घ pc, अचिन्हित दीर्घ *ra)
अणु
	अचिन्हित दीर्घ stack_page = 0;
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		अगर (on_irq_stack(cpu, *sp)) अणु
			stack_page = (अचिन्हित दीर्घ)irq_stack[cpu];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!stack_page)
		stack_page = (अचिन्हित दीर्घ)task_stack_page(task);

	वापस unwind_stack_by_address(stack_page, sp, pc, ra);
पूर्ण
#पूर्ण_अगर

/*
 * get_wchan - a मुख्यtenance nighपंचांगare^W^Wpain in the ass ...
 */
अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *task)
अणु
	अचिन्हित दीर्घ pc = 0;
#अगर_घोषित CONFIG_KALLSYMS
	अचिन्हित दीर्घ sp;
	अचिन्हित दीर्घ ra = 0;
#पूर्ण_अगर

	अगर (!task || task == current || task->state == TASK_RUNNING)
		जाओ out;
	अगर (!task_stack_page(task))
		जाओ out;

	pc = thपढ़ो_saved_pc(task);

#अगर_घोषित CONFIG_KALLSYMS
	sp = task->thपढ़ो.reg29 + schedule_mfi.frame_size;

	जबतक (in_sched_functions(pc))
		pc = unwind_stack(task, &sp, pc, &ra);
#पूर्ण_अगर

out:
	वापस pc;
पूर्ण

अचिन्हित दीर्घ mips_stack_top(व्योम)
अणु
	अचिन्हित दीर्घ top = TASK_SIZE & PAGE_MASK;

	अगर (IS_ENABLED(CONFIG_MIPS_FP_SUPPORT)) अणु
		/* One page क्रम branch delay slot "emulation" */
		top -= PAGE_SIZE;
	पूर्ण

	/* Space क्रम the VDSO, data page & GIC user page */
	top -= PAGE_ALIGN(current->thपढ़ो.abi->vdso->size);
	top -= PAGE_SIZE;
	top -= mips_gic_present() ? PAGE_SIZE : 0;

	/* Space क्रम cache colour alignment */
	अगर (cpu_has_dc_aliases)
		top -= shm_align_mask + 1;

	/* Space to अक्रमomize the VDSO base */
	अगर (current->flags & PF_RANDOMIZE)
		top -= VDSO_RANDOMIZE_SIZE;

	वापस top;
पूर्ण

/*
 * Don't क्रमget that the stack poपूर्णांकer must be aligned on a 8 bytes
 * boundary क्रम 32-bits ABI and 16 bytes क्रम 64-bits ABI.
 */
अचिन्हित दीर्घ arch_align_stack(अचिन्हित दीर्घ sp)
अणु
	अगर (!(current->personality & ADDR_NO_RANDOMIZE) && अक्रमomize_va_space)
		sp -= get_अक्रमom_पूर्णांक() & ~PAGE_MASK;

	वापस sp & ALMASK;
पूर्ण

अटल काष्ठा cpumask backtrace_csd_busy;

अटल व्योम handle_backtrace(व्योम *info)
अणु
	nmi_cpu_backtrace(get_irq_regs());
	cpumask_clear_cpu(smp_processor_id(), &backtrace_csd_busy);
पूर्ण

अटल DEFINE_PER_CPU(call_single_data_t, backtrace_csd) =
	CSD_INIT(handle_backtrace, शून्य);

अटल व्योम उठाओ_backtrace(cpumask_t *mask)
अणु
	call_single_data_t *csd;
	पूर्णांक cpu;

	क्रम_each_cpu(cpu, mask) अणु
		/*
		 * If we previously sent an IPI to the target CPU & it hasn't
		 * cleared its bit in the busy cpumask then it didn't handle
		 * our previous IPI & it's not safe क्रम us to reuse the
		 * call_single_data_t.
		 */
		अगर (cpumask_test_and_set_cpu(cpu, &backtrace_csd_busy)) अणु
			pr_warn("Unable to send backtrace IPI to CPU%u - perhaps it hung?\n",
				cpu);
			जारी;
		पूर्ण

		csd = &per_cpu(backtrace_csd, cpu);
		smp_call_function_single_async(cpu, csd);
	पूर्ण
पूर्ण

व्योम arch_trigger_cpumask_backtrace(स्थिर cpumask_t *mask, bool exclude_self)
अणु
	nmi_trigger_cpumask_backtrace(mask, exclude_self, उठाओ_backtrace);
पूर्ण

पूर्णांक mips_get_process_fp_mode(काष्ठा task_काष्ठा *task)
अणु
	पूर्णांक value = 0;

	अगर (!test_tsk_thपढ़ो_flag(task, TIF_32BIT_FPREGS))
		value |= PR_FP_MODE_FR;
	अगर (test_tsk_thपढ़ो_flag(task, TIF_HYBRID_FPREGS))
		value |= PR_FP_MODE_FRE;

	वापस value;
पूर्ण

अटल दीर्घ prepare_क्रम_fp_mode_चयन(व्योम *unused)
अणु
	/*
	 * This is icky, but we use this to simply ensure that all CPUs have
	 * context चयनed, regardless of whether they were previously running
	 * kernel or user code. This ensures that no CPU that a mode-चयनing
	 * program may execute on keeps its FPU enabled (& in the old mode)
	 * throughout the mode चयन.
	 */
	वापस 0;
पूर्ण

पूर्णांक mips_set_process_fp_mode(काष्ठा task_काष्ठा *task, अचिन्हित पूर्णांक value)
अणु
	स्थिर अचिन्हित पूर्णांक known_bits = PR_FP_MODE_FR | PR_FP_MODE_FRE;
	काष्ठा task_काष्ठा *t;
	काष्ठा cpumask process_cpus;
	पूर्णांक cpu;

	/* If nothing to change, वापस right away, successfully.  */
	अगर (value == mips_get_process_fp_mode(task))
		वापस 0;

	/* Only accept a mode change अगर 64-bit FP enabled क्रम o32.  */
	अगर (!IS_ENABLED(CONFIG_MIPS_O32_FP64_SUPPORT))
		वापस -EOPNOTSUPP;

	/* And only क्रम o32 tasks.  */
	अगर (IS_ENABLED(CONFIG_64BIT) && !test_thपढ़ो_flag(TIF_32BIT_REGS))
		वापस -EOPNOTSUPP;

	/* Check the value is valid */
	अगर (value & ~known_bits)
		वापस -EOPNOTSUPP;

	/* Setting FRE without FR is not supported.  */
	अगर ((value & (PR_FP_MODE_FR | PR_FP_MODE_FRE)) == PR_FP_MODE_FRE)
		वापस -EOPNOTSUPP;

	/* Aव्योम inadvertently triggering emulation */
	अगर ((value & PR_FP_MODE_FR) && raw_cpu_has_fpu &&
	    !(raw_current_cpu_data.fpu_id & MIPS_FPIR_F64))
		वापस -EOPNOTSUPP;
	अगर ((value & PR_FP_MODE_FRE) && raw_cpu_has_fpu && !cpu_has_fre)
		वापस -EOPNOTSUPP;

	/* FR = 0 not supported in MIPS R6 */
	अगर (!(value & PR_FP_MODE_FR) && raw_cpu_has_fpu && cpu_has_mips_r6)
		वापस -EOPNOTSUPP;

	/* Indicate the new FP mode in each thपढ़ो */
	क्रम_each_thपढ़ो(task, t) अणु
		/* Update desired FP रेजिस्टर width */
		अगर (value & PR_FP_MODE_FR) अणु
			clear_tsk_thपढ़ो_flag(t, TIF_32BIT_FPREGS);
		पूर्ण अन्यथा अणु
			set_tsk_thपढ़ो_flag(t, TIF_32BIT_FPREGS);
			clear_tsk_thपढ़ो_flag(t, TIF_MSA_CTX_LIVE);
		पूर्ण

		/* Update desired FP single layout */
		अगर (value & PR_FP_MODE_FRE)
			set_tsk_thपढ़ो_flag(t, TIF_HYBRID_FPREGS);
		अन्यथा
			clear_tsk_thपढ़ो_flag(t, TIF_HYBRID_FPREGS);
	पूर्ण

	/*
	 * We need to ensure that all thपढ़ोs in the process have चयनed mode
	 * beक्रमe वापसing, in order to allow userland to not worry about
	 * races. We can करो this by क्रमcing all CPUs that any thपढ़ो in the
	 * process may be running on to schedule something अन्यथा - in this हाल
	 * prepare_क्रम_fp_mode_चयन().
	 *
	 * We begin by generating a mask of all CPUs that any thपढ़ो in the
	 * process may be running on.
	 */
	cpumask_clear(&process_cpus);
	क्रम_each_thपढ़ो(task, t)
		cpumask_set_cpu(task_cpu(t), &process_cpus);

	/*
	 * Now we schedule prepare_क्रम_fp_mode_चयन() on each of those CPUs.
	 *
	 * The CPUs may have rescheduled alपढ़ोy since we चयनed mode or
	 * generated the cpumask, but that करोesn't matter. If the task in this
	 * process is scheduled out then our scheduling
	 * prepare_क्रम_fp_mode_चयन() will simply be redundant. If it's
	 * scheduled in then it will alपढ़ोy have picked up the new FP mode
	 * whilst करोing so.
	 */
	get_online_cpus();
	क्रम_each_cpu_and(cpu, &process_cpus, cpu_online_mask)
		work_on_cpu(cpu, prepare_क्रम_fp_mode_चयन, शून्य);
	put_online_cpus();

	वापस 0;
पूर्ण

#अगर defined(CONFIG_32BIT) || defined(CONFIG_MIPS32_O32)
व्योम mips_dump_regs32(u32 *uregs, स्थिर काष्ठा pt_regs *regs)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = MIPS32_EF_R1; i <= MIPS32_EF_R31; i++) अणु
		/* k0/k1 are copied as zero. */
		अगर (i == MIPS32_EF_R26 || i == MIPS32_EF_R27)
			uregs[i] = 0;
		अन्यथा
			uregs[i] = regs->regs[i - MIPS32_EF_R0];
	पूर्ण

	uregs[MIPS32_EF_LO] = regs->lo;
	uregs[MIPS32_EF_HI] = regs->hi;
	uregs[MIPS32_EF_CP0_EPC] = regs->cp0_epc;
	uregs[MIPS32_EF_CP0_BADVADDR] = regs->cp0_badvaddr;
	uregs[MIPS32_EF_CP0_STATUS] = regs->cp0_status;
	uregs[MIPS32_EF_CP0_CAUSE] = regs->cp0_cause;
पूर्ण
#पूर्ण_अगर /* CONFIG_32BIT || CONFIG_MIPS32_O32 */

#अगर_घोषित CONFIG_64BIT
व्योम mips_dump_regs64(u64 *uregs, स्थिर काष्ठा pt_regs *regs)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = MIPS64_EF_R1; i <= MIPS64_EF_R31; i++) अणु
		/* k0/k1 are copied as zero. */
		अगर (i == MIPS64_EF_R26 || i == MIPS64_EF_R27)
			uregs[i] = 0;
		अन्यथा
			uregs[i] = regs->regs[i - MIPS64_EF_R0];
	पूर्ण

	uregs[MIPS64_EF_LO] = regs->lo;
	uregs[MIPS64_EF_HI] = regs->hi;
	uregs[MIPS64_EF_CP0_EPC] = regs->cp0_epc;
	uregs[MIPS64_EF_CP0_BADVADDR] = regs->cp0_badvaddr;
	uregs[MIPS64_EF_CP0_STATUS] = regs->cp0_status;
	uregs[MIPS64_EF_CP0_CAUSE] = regs->cp0_cause;
पूर्ण
#पूर्ण_अगर /* CONFIG_64BIT */
