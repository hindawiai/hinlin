<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PA-RISC KGDB support
 *
 * Copyright (c) 2019 Sven Schnelle <svens@stackframe.org>
 *
 */

#समावेश <linux/kgdb.h>
#समावेश <linux/माला.स>
#समावेश <linux/sched.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/patch.h>
#समावेश <यंत्र/cacheflush.h>

स्थिर काष्ठा kgdb_arch arch_kgdb_ops = अणु
	.gdb_bpt_instr = अणु 0x03, 0xff, 0xa0, 0x1f पूर्ण
पूर्ण;

अटल पूर्णांक __kgdb_notअगरy(काष्ठा die_args *args, अचिन्हित दीर्घ cmd)
अणु
	काष्ठा pt_regs *regs = args->regs;

	अगर (kgdb_handle_exception(1, args->signr, cmd, regs))
		वापस NOTIFY_DONE;
	वापस NOTIFY_STOP;
पूर्ण

अटल पूर्णांक kgdb_notअगरy(काष्ठा notअगरier_block *self,
		       अचिन्हित दीर्घ cmd, व्योम *ptr)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	local_irq_save(flags);
	ret = __kgdb_notअगरy(ptr, cmd);
	local_irq_restore(flags);

	वापस ret;
पूर्ण

अटल काष्ठा notअगरier_block kgdb_notअगरier = अणु
	.notअगरier_call	= kgdb_notअगरy,
	.priority	= -पूर्णांक_उच्च,
पूर्ण;

पूर्णांक kgdb_arch_init(व्योम)
अणु
	वापस रेजिस्टर_die_notअगरier(&kgdb_notअगरier);
पूर्ण

व्योम kgdb_arch_निकास(व्योम)
अणु
	unरेजिस्टर_die_notअगरier(&kgdb_notअगरier);
पूर्ण

व्योम pt_regs_to_gdb_regs(अचिन्हित दीर्घ *gdb_regs, काष्ठा pt_regs *regs)
अणु
	काष्ठा parisc_gdb_regs *gr = (काष्ठा parisc_gdb_regs *)gdb_regs;

	स_रखो(gr, 0, माप(काष्ठा parisc_gdb_regs));

	स_नकल(gr->gpr, regs->gr, माप(gr->gpr));
	स_नकल(gr->fr, regs->fr, माप(gr->fr));

	gr->sr0 = regs->sr[0];
	gr->sr1 = regs->sr[1];
	gr->sr2 = regs->sr[2];
	gr->sr3 = regs->sr[3];
	gr->sr4 = regs->sr[4];
	gr->sr5 = regs->sr[5];
	gr->sr6 = regs->sr[6];
	gr->sr7 = regs->sr[7];

	gr->sar = regs->sar;
	gr->iir = regs->iir;
	gr->isr = regs->isr;
	gr->ior = regs->ior;
	gr->ipsw = regs->ipsw;
	gr->cr27 = regs->cr27;

	gr->iaoq_f = regs->iaoq[0];
	gr->iasq_f = regs->iasq[0];

	gr->iaoq_b = regs->iaoq[1];
	gr->iasq_b = regs->iasq[1];
पूर्ण

व्योम gdb_regs_to_pt_regs(अचिन्हित दीर्घ *gdb_regs, काष्ठा pt_regs *regs)
अणु
	काष्ठा parisc_gdb_regs *gr = (काष्ठा parisc_gdb_regs *)gdb_regs;


	स_नकल(regs->gr, gr->gpr, माप(regs->gr));
	स_नकल(regs->fr, gr->fr, माप(regs->fr));

	regs->sr[0] = gr->sr0;
	regs->sr[1] = gr->sr1;
	regs->sr[2] = gr->sr2;
	regs->sr[3] = gr->sr3;
	regs->sr[4] = gr->sr4;
	regs->sr[5] = gr->sr5;
	regs->sr[6] = gr->sr6;
	regs->sr[7] = gr->sr7;

	regs->sar = gr->sar;
	regs->iir = gr->iir;
	regs->isr = gr->isr;
	regs->ior = gr->ior;
	regs->ipsw = gr->ipsw;
	regs->cr27 = gr->cr27;

	regs->iaoq[0] = gr->iaoq_f;
	regs->iasq[0] = gr->iasq_f;

	regs->iaoq[1] = gr->iaoq_b;
	regs->iasq[1] = gr->iasq_b;
पूर्ण

व्योम sleeping_thपढ़ो_to_gdb_regs(अचिन्हित दीर्घ *gdb_regs,
				काष्ठा task_काष्ठा *task)
अणु
	काष्ठा pt_regs *regs = task_pt_regs(task);
	अचिन्हित दीर्घ gr30, iaoq;

	gr30 = regs->gr[30];
	iaoq = regs->iaoq[0];

	regs->gr[30] = regs->ksp;
	regs->iaoq[0] = regs->kpc;
	pt_regs_to_gdb_regs(gdb_regs, regs);

	regs->gr[30] = gr30;
	regs->iaoq[0] = iaoq;

पूर्ण

अटल व्योम step_inकाष्ठाion_queue(काष्ठा pt_regs *regs)
अणु
	regs->iaoq[0] = regs->iaoq[1];
	regs->iaoq[1] += 4;
पूर्ण

व्योम kgdb_arch_set_pc(काष्ठा pt_regs *regs, अचिन्हित दीर्घ ip)
अणु
	regs->iaoq[0] = ip;
	regs->iaoq[1] = ip + 4;
पूर्ण

पूर्णांक kgdb_arch_set_अवरोधpoपूर्णांक(काष्ठा kgdb_bkpt *bpt)
अणु
	पूर्णांक ret = copy_from_kernel_nofault(bpt->saved_instr,
			(अक्षर *)bpt->bpt_addr, BREAK_INSTR_SIZE);
	अगर (ret)
		वापस ret;

	__patch_text((व्योम *)bpt->bpt_addr,
			*(अचिन्हित पूर्णांक *)&arch_kgdb_ops.gdb_bpt_instr);
	वापस ret;
पूर्ण

पूर्णांक kgdb_arch_हटाओ_अवरोधpoपूर्णांक(काष्ठा kgdb_bkpt *bpt)
अणु
	__patch_text((व्योम *)bpt->bpt_addr, *(अचिन्हित पूर्णांक *)&bpt->saved_instr);
	वापस 0;
पूर्ण

पूर्णांक kgdb_arch_handle_exception(पूर्णांक trap, पूर्णांक signo,
		पूर्णांक err_code, अक्षर *inbuf, अक्षर *outbuf,
		काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ addr;
	अक्षर *p = inbuf + 1;

	चयन (inbuf[0]) अणु
	हाल 'D':
	हाल 'c':
	हाल 'k':
		kgdb_contthपढ़ो = शून्य;
		kgdb_single_step = 0;

		अगर (kgdb_hex2दीर्घ(&p, &addr))
			kgdb_arch_set_pc(regs, addr);
		अन्यथा अगर (trap == 9 && regs->iir ==
				PARISC_KGDB_COMPILED_BREAK_INSN)
			step_inकाष्ठाion_queue(regs);
		वापस 0;
	हाल 's':
		kgdb_single_step = 1;
		अगर (kgdb_hex2दीर्घ(&p, &addr)) अणु
			kgdb_arch_set_pc(regs, addr);
		पूर्ण अन्यथा अगर (trap == 9 && regs->iir ==
				PARISC_KGDB_COMPILED_BREAK_INSN) अणु
			step_inकाष्ठाion_queue(regs);
			mtctl(-1, 0);
		पूर्ण अन्यथा अणु
			mtctl(0, 0);
		पूर्ण
		regs->gr[0] |= PSW_R;
		वापस 0;

	पूर्ण
	वापस -1;
पूर्ण
