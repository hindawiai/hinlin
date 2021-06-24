<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * unaligned.c: Unaligned load/store trap handling with special
 *              हालs क्रम the kernel to करो them more quickly.
 *
 * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)
 * Copyright (C) 1996 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 */


#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/mm.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/processor.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/smp.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/extable.h>

#समावेश <यंत्र/setup.h>

#समावेश "kernel.h"

क्रमागत direction अणु
	load,    /* ld, ldd, ldh, ldsh */
	store,   /* st, std, sth, stsh */
	both,    /* Swap, ldstub, etc. */
	fpload,
	fpstore,
	invalid,
पूर्ण;

अटल अंतरभूत क्रमागत direction decode_direction(अचिन्हित पूर्णांक insn)
अणु
	अचिन्हित दीर्घ पंचांगp = (insn >> 21) & 1;

	अगर(!पंचांगp)
		वापस load;
	अन्यथा अणु
		अगर(((insn>>19)&0x3f) == 15)
			वापस both;
		अन्यथा
			वापस store;
	पूर्ण
पूर्ण

/* 8 = द्विगुन-word, 4 = word, 2 = half-word */
अटल अंतरभूत पूर्णांक decode_access_size(अचिन्हित पूर्णांक insn)
अणु
	insn = (insn >> 19) & 3;

	अगर(!insn)
		वापस 4;
	अन्यथा अगर(insn == 3)
		वापस 8;
	अन्यथा अगर(insn == 2)
		वापस 2;
	अन्यथा अणु
		prपूर्णांकk("Impossible unaligned trap. insn=%08x\n", insn);
		die_अगर_kernel("Byte sized unaligned access?!?!", current->thपढ़ो.kregs);
		वापस 4; /* just to keep gcc happy. */
	पूर्ण
पूर्ण

/* 0x400000 = चिन्हित, 0 = अचिन्हित */
अटल अंतरभूत पूर्णांक decode_चिन्हितness(अचिन्हित पूर्णांक insn)
अणु
	वापस (insn & 0x400000);
पूर्ण

अटल अंतरभूत व्योम maybe_flush_winकरोws(अचिन्हित पूर्णांक rs1, अचिन्हित पूर्णांक rs2,
				       अचिन्हित पूर्णांक rd)
अणु
	अगर(rs2 >= 16 || rs1 >= 16 || rd >= 16) अणु
		/* Wheee... */
		__यंत्र__ __अस्थिर__("save %sp, -0x40, %sp\n\t"
				     "save %sp, -0x40, %sp\n\t"
				     "save %sp, -0x40, %sp\n\t"
				     "save %sp, -0x40, %sp\n\t"
				     "save %sp, -0x40, %sp\n\t"
				     "save %sp, -0x40, %sp\n\t"
				     "save %sp, -0x40, %sp\n\t"
				     "restore; restore; restore; restore;\n\t"
				     "restore; restore; restore;\n\t");
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक sign_extend_imm13(पूर्णांक imm)
अणु
	वापस imm << 19 >> 19;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ fetch_reg(अचिन्हित पूर्णांक reg, काष्ठा pt_regs *regs)
अणु
	काष्ठा reg_winकरोw32 *win;

	अगर(reg < 16)
		वापस (!reg ? 0 : regs->u_regs[reg]);

	/* Ho hum, the slightly complicated हाल. */
	win = (काष्ठा reg_winकरोw32 *) regs->u_regs[UREG_FP];
	वापस win->locals[reg - 16]; /* yes, I know what this करोes... */
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ safe_fetch_reg(अचिन्हित पूर्णांक reg, काष्ठा pt_regs *regs)
अणु
	काष्ठा reg_winकरोw32 __user *win;
	अचिन्हित दीर्घ ret;

	अगर (reg < 16)
		वापस (!reg ? 0 : regs->u_regs[reg]);

	/* Ho hum, the slightly complicated हाल. */
	win = (काष्ठा reg_winकरोw32 __user *) regs->u_regs[UREG_FP];

	अगर ((अचिन्हित दीर्घ)win & 3)
		वापस -1;

	अगर (get_user(ret, &win->locals[reg - 16]))
		वापस -1;

	वापस ret;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ *fetch_reg_addr(अचिन्हित पूर्णांक reg, काष्ठा pt_regs *regs)
अणु
	काष्ठा reg_winकरोw32 *win;

	अगर(reg < 16)
		वापस &regs->u_regs[reg];
	win = (काष्ठा reg_winकरोw32 *) regs->u_regs[UREG_FP];
	वापस &win->locals[reg - 16];
पूर्ण

अटल अचिन्हित दीर्घ compute_effective_address(काष्ठा pt_regs *regs,
					       अचिन्हित पूर्णांक insn)
अणु
	अचिन्हित पूर्णांक rs1 = (insn >> 14) & 0x1f;
	अचिन्हित पूर्णांक rs2 = insn & 0x1f;
	अचिन्हित पूर्णांक rd = (insn >> 25) & 0x1f;

	अगर(insn & 0x2000) अणु
		maybe_flush_winकरोws(rs1, 0, rd);
		वापस (fetch_reg(rs1, regs) + sign_extend_imm13(insn));
	पूर्ण अन्यथा अणु
		maybe_flush_winकरोws(rs1, rs2, rd);
		वापस (fetch_reg(rs1, regs) + fetch_reg(rs2, regs));
	पूर्ण
पूर्ण

अचिन्हित दीर्घ safe_compute_effective_address(काष्ठा pt_regs *regs,
					     अचिन्हित पूर्णांक insn)
अणु
	अचिन्हित पूर्णांक rs1 = (insn >> 14) & 0x1f;
	अचिन्हित पूर्णांक rs2 = insn & 0x1f;
	अचिन्हित पूर्णांक rd = (insn >> 25) & 0x1f;

	अगर(insn & 0x2000) अणु
		maybe_flush_winकरोws(rs1, 0, rd);
		वापस (safe_fetch_reg(rs1, regs) + sign_extend_imm13(insn));
	पूर्ण अन्यथा अणु
		maybe_flush_winकरोws(rs1, rs2, rd);
		वापस (safe_fetch_reg(rs1, regs) + safe_fetch_reg(rs2, regs));
	पूर्ण
पूर्ण

/* This is just to make gcc think panic करोes वापस... */
अटल व्योम unaligned_panic(अक्षर *str)
अणु
	panic("%s", str);
पूर्ण

/* una_यंत्र.S */
बाह्य पूर्णांक करो_पूर्णांक_load(अचिन्हित दीर्घ *dest_reg, पूर्णांक size,
		       अचिन्हित दीर्घ *saddr, पूर्णांक is_चिन्हित);
बाह्य पूर्णांक __करो_पूर्णांक_store(अचिन्हित दीर्घ *dst_addr, पूर्णांक size,
			  अचिन्हित दीर्घ *src_val);

अटल पूर्णांक करो_पूर्णांक_store(पूर्णांक reg_num, पूर्णांक size, अचिन्हित दीर्घ *dst_addr,
			काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ zero[2] = अणु 0, 0 पूर्ण;
	अचिन्हित दीर्घ *src_val;

	अगर (reg_num)
		src_val = fetch_reg_addr(reg_num, regs);
	अन्यथा अणु
		src_val = &zero[0];
		अगर (size == 8)
			zero[1] = fetch_reg(1, regs);
	पूर्ण
	वापस __करो_पूर्णांक_store(dst_addr, size, src_val);
पूर्ण

बाह्य व्योम smp_capture(व्योम);
बाह्य व्योम smp_release(व्योम);

अटल अंतरभूत व्योम advance(काष्ठा pt_regs *regs)
अणु
	regs->pc   = regs->npc;
	regs->npc += 4;
पूर्ण

अटल अंतरभूत पूर्णांक भग्नing_poपूर्णांक_load_or_store_p(अचिन्हित पूर्णांक insn)
अणु
	वापस (insn >> 24) & 1;
पूर्ण

अटल अंतरभूत पूर्णांक ok_क्रम_kernel(अचिन्हित पूर्णांक insn)
अणु
	वापस !भग्नing_poपूर्णांक_load_or_store_p(insn);
पूर्ण

अटल व्योम kernel_mna_trap_fault(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक insn)
अणु
	स्थिर काष्ठा exception_table_entry *entry;

	entry = search_exception_tables(regs->pc);
	अगर (!entry) अणु
		अचिन्हित दीर्घ address = compute_effective_address(regs, insn);
        	अगर(address < PAGE_SIZE) अणु
                	prपूर्णांकk(KERN_ALERT "Unable to handle kernel NULL pointer dereference in mna handler");
        	पूर्ण अन्यथा
                	prपूर्णांकk(KERN_ALERT "Unable to handle kernel paging request in mna handler");
	        prपूर्णांकk(KERN_ALERT " at virtual address %08lx\n",address);
		prपूर्णांकk(KERN_ALERT "current->{mm,active_mm}->context = %08lx\n",
			(current->mm ? current->mm->context :
			current->active_mm->context));
		prपूर्णांकk(KERN_ALERT "current->{mm,active_mm}->pgd = %08lx\n",
			(current->mm ? (अचिन्हित दीर्घ) current->mm->pgd :
			(अचिन्हित दीर्घ) current->active_mm->pgd));
	        die_अगर_kernel("Oops", regs);
		/* Not reached */
	पूर्ण
	regs->pc = entry->fixup;
	regs->npc = regs->pc + 4;
पूर्ण

यंत्रlinkage व्योम kernel_unaligned_trap(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक insn)
अणु
	क्रमागत direction dir = decode_direction(insn);
	पूर्णांक size = decode_access_size(insn);

	अगर(!ok_क्रम_kernel(insn) || dir == both) अणु
		prपूर्णांकk("Unsupported unaligned load/store trap for kernel at <%08lx>.\n",
		       regs->pc);
		unaligned_panic("Wheee. Kernel does fpu/atomic unaligned load/store.");
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ addr = compute_effective_address(regs, insn);
		पूर्णांक err;

		perf_sw_event(PERF_COUNT_SW_ALIGNMENT_FAULTS, 1, regs, addr);
		चयन (dir) अणु
		हाल load:
			err = करो_पूर्णांक_load(fetch_reg_addr(((insn>>25)&0x1f),
							 regs),
					  size, (अचिन्हित दीर्घ *) addr,
					  decode_चिन्हितness(insn));
			अवरोध;

		हाल store:
			err = करो_पूर्णांक_store(((insn>>25)&0x1f), size,
					   (अचिन्हित दीर्घ *) addr, regs);
			अवरोध;
		शेष:
			panic("Impossible kernel unaligned trap.");
			/* Not reached... */
		पूर्ण
		अगर (err)
			kernel_mna_trap_fault(regs, insn);
		अन्यथा
			advance(regs);
	पूर्ण
पूर्ण

यंत्रlinkage व्योम user_unaligned_trap(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक insn)
अणु
	send_sig_fault(SIGBUS, BUS_ADRALN,
		       (व्योम __user *)safe_compute_effective_address(regs, insn),
		       0, current);
पूर्ण
