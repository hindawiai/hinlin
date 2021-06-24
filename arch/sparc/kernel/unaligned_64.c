<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * unaligned.c: Unaligned load/store trap handling with special
 *              हालs क्रम the kernel to करो them more quickly.
 *
 * Copyright (C) 1996,2008 David S. Miller (davem@davemloft.net)
 * Copyright (C) 1996,1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 */


#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/extable.h>
#समावेश <यंत्र/asi.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/pstate.h>
#समावेश <यंत्र/processor.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/smp.h>
#समावेश <linux/bitops.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/context_tracking.h>
#समावेश <यंत्र/fpumacro.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/setup.h>

#समावेश "entry.h"
#समावेश "kernel.h"

क्रमागत direction अणु
	load,    /* ld, ldd, ldh, ldsh */
	store,   /* st, std, sth, stsh */
	both,    /* Swap, ldstub, cas, ... */
	fpld,
	fpst,
	invalid,
पूर्ण;

अटल अंतरभूत क्रमागत direction decode_direction(अचिन्हित पूर्णांक insn)
अणु
	अचिन्हित दीर्घ पंचांगp = (insn >> 21) & 1;

	अगर (!पंचांगp)
		वापस load;
	अन्यथा अणु
		चयन ((insn>>19)&0xf) अणु
		हाल 15: /* swap* */
			वापस both;
		शेष:
			वापस store;
		पूर्ण
	पूर्ण
पूर्ण

/* 16 = द्विगुन-word, 8 = extra-word, 4 = word, 2 = half-word */
अटल अंतरभूत पूर्णांक decode_access_size(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक insn)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	पंचांगp = ((insn >> 19) & 0xf);
	अगर (पंचांगp == 11 || पंचांगp == 14) /* ldx/stx */
		वापस 8;
	पंचांगp &= 3;
	अगर (!पंचांगp)
		वापस 4;
	अन्यथा अगर (पंचांगp == 3)
		वापस 16;	/* ldd/std - Although it is actually 8 */
	अन्यथा अगर (पंचांगp == 2)
		वापस 2;
	अन्यथा अणु
		prपूर्णांकk("Impossible unaligned trap. insn=%08x\n", insn);
		die_अगर_kernel("Byte sized unaligned access?!?!", regs);

		/* GCC should never warn that control reaches the end
		 * of this function without वापसing a value because
		 * die_अगर_kernel() is marked with attribute 'noreturn'.
		 * Alas, some versions करो...
		 */

		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक decode_asi(अचिन्हित पूर्णांक insn, काष्ठा pt_regs *regs)
अणु
	अगर (insn & 0x800000) अणु
		अगर (insn & 0x2000)
			वापस (अचिन्हित अक्षर)(regs->tstate >> 24);	/* %asi */
		अन्यथा
			वापस (अचिन्हित अक्षर)(insn >> 5);		/* imm_asi */
	पूर्ण अन्यथा
		वापस ASI_P;
पूर्ण

/* 0x400000 = चिन्हित, 0 = अचिन्हित */
अटल अंतरभूत पूर्णांक decode_चिन्हितness(अचिन्हित पूर्णांक insn)
अणु
	वापस (insn & 0x400000);
पूर्ण

अटल अंतरभूत व्योम maybe_flush_winकरोws(अचिन्हित पूर्णांक rs1, अचिन्हित पूर्णांक rs2,
				       अचिन्हित पूर्णांक rd, पूर्णांक from_kernel)
अणु
	अगर (rs2 >= 16 || rs1 >= 16 || rd >= 16) अणु
		अगर (from_kernel != 0)
			__यंत्र__ __अस्थिर__("flushw");
		अन्यथा
			flushw_user();
	पूर्ण
पूर्ण

अटल अंतरभूत दीर्घ sign_extend_imm13(दीर्घ imm)
अणु
	वापस imm << 51 >> 51;
पूर्ण

अटल अचिन्हित दीर्घ fetch_reg(अचिन्हित पूर्णांक reg, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ value, fp;
	
	अगर (reg < 16)
		वापस (!reg ? 0 : regs->u_regs[reg]);

	fp = regs->u_regs[UREG_FP];

	अगर (regs->tstate & TSTATE_PRIV) अणु
		काष्ठा reg_winकरोw *win;
		win = (काष्ठा reg_winकरोw *)(fp + STACK_BIAS);
		value = win->locals[reg - 16];
	पूर्ण अन्यथा अगर (!test_thपढ़ो_64bit_stack(fp)) अणु
		काष्ठा reg_winकरोw32 __user *win32;
		win32 = (काष्ठा reg_winकरोw32 __user *)((अचिन्हित दीर्घ)((u32)fp));
		get_user(value, &win32->locals[reg - 16]);
	पूर्ण अन्यथा अणु
		काष्ठा reg_winकरोw __user *win;
		win = (काष्ठा reg_winकरोw __user *)(fp + STACK_BIAS);
		get_user(value, &win->locals[reg - 16]);
	पूर्ण
	वापस value;
पूर्ण

अटल अचिन्हित दीर्घ *fetch_reg_addr(अचिन्हित पूर्णांक reg, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ fp;

	अगर (reg < 16)
		वापस &regs->u_regs[reg];

	fp = regs->u_regs[UREG_FP];

	अगर (regs->tstate & TSTATE_PRIV) अणु
		काष्ठा reg_winकरोw *win;
		win = (काष्ठा reg_winकरोw *)(fp + STACK_BIAS);
		वापस &win->locals[reg - 16];
	पूर्ण अन्यथा अगर (!test_thपढ़ो_64bit_stack(fp)) अणु
		काष्ठा reg_winकरोw32 *win32;
		win32 = (काष्ठा reg_winकरोw32 *)((अचिन्हित दीर्घ)((u32)fp));
		वापस (अचिन्हित दीर्घ *)&win32->locals[reg - 16];
	पूर्ण अन्यथा अणु
		काष्ठा reg_winकरोw *win;
		win = (काष्ठा reg_winकरोw *)(fp + STACK_BIAS);
		वापस &win->locals[reg - 16];
	पूर्ण
पूर्ण

अचिन्हित दीर्घ compute_effective_address(काष्ठा pt_regs *regs,
					अचिन्हित पूर्णांक insn, अचिन्हित पूर्णांक rd)
अणु
	पूर्णांक from_kernel = (regs->tstate & TSTATE_PRIV) != 0;
	अचिन्हित पूर्णांक rs1 = (insn >> 14) & 0x1f;
	अचिन्हित पूर्णांक rs2 = insn & 0x1f;
	अचिन्हित दीर्घ addr;

	अगर (insn & 0x2000) अणु
		maybe_flush_winकरोws(rs1, 0, rd, from_kernel);
		addr = (fetch_reg(rs1, regs) + sign_extend_imm13(insn));
	पूर्ण अन्यथा अणु
		maybe_flush_winकरोws(rs1, rs2, rd, from_kernel);
		addr = (fetch_reg(rs1, regs) + fetch_reg(rs2, regs));
	पूर्ण

	अगर (!from_kernel && test_thपढ़ो_flag(TIF_32BIT))
		addr &= 0xffffffff;

	वापस addr;
पूर्ण

/* This is just to make gcc think die_अगर_kernel करोes वापस... */
अटल व्योम __used unaligned_panic(अक्षर *str, काष्ठा pt_regs *regs)
अणु
	die_अगर_kernel(str, regs);
पूर्ण

बाह्य पूर्णांक करो_पूर्णांक_load(अचिन्हित दीर्घ *dest_reg, पूर्णांक size,
		       अचिन्हित दीर्घ *saddr, पूर्णांक is_चिन्हित, पूर्णांक asi);
	
बाह्य पूर्णांक __करो_पूर्णांक_store(अचिन्हित दीर्घ *dst_addr, पूर्णांक size,
			  अचिन्हित दीर्घ src_val, पूर्णांक asi);

अटल अंतरभूत पूर्णांक करो_पूर्णांक_store(पूर्णांक reg_num, पूर्णांक size, अचिन्हित दीर्घ *dst_addr,
			       काष्ठा pt_regs *regs, पूर्णांक asi, पूर्णांक orig_asi)
अणु
	अचिन्हित दीर्घ zero = 0;
	अचिन्हित दीर्घ *src_val_p = &zero;
	अचिन्हित दीर्घ src_val;

	अगर (size == 16) अणु
		size = 8;
		zero = (((दीर्घ)(reg_num ?
		        (अचिन्हित पूर्णांक)fetch_reg(reg_num, regs) : 0)) << 32) |
			(अचिन्हित पूर्णांक)fetch_reg(reg_num + 1, regs);
	पूर्ण अन्यथा अगर (reg_num) अणु
		src_val_p = fetch_reg_addr(reg_num, regs);
	पूर्ण
	src_val = *src_val_p;
	अगर (unlikely(asi != orig_asi)) अणु
		चयन (size) अणु
		हाल 2:
			src_val = swab16(src_val);
			अवरोध;
		हाल 4:
			src_val = swab32(src_val);
			अवरोध;
		हाल 8:
			src_val = swab64(src_val);
			अवरोध;
		हाल 16:
		शेष:
			BUG();
			अवरोध;
		पूर्ण
	पूर्ण
	वापस __करो_पूर्णांक_store(dst_addr, size, src_val, asi);
पूर्ण

अटल अंतरभूत व्योम advance(काष्ठा pt_regs *regs)
अणु
	regs->tpc   = regs->tnpc;
	regs->tnpc += 4;
	अगर (test_thपढ़ो_flag(TIF_32BIT)) अणु
		regs->tpc &= 0xffffffff;
		regs->tnpc &= 0xffffffff;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक भग्नing_poपूर्णांक_load_or_store_p(अचिन्हित पूर्णांक insn)
अणु
	वापस (insn >> 24) & 1;
पूर्ण

अटल अंतरभूत पूर्णांक ok_क्रम_kernel(अचिन्हित पूर्णांक insn)
अणु
	वापस !भग्नing_poपूर्णांक_load_or_store_p(insn);
पूर्ण

अटल व्योम kernel_mna_trap_fault(पूर्णांक fixup_tstate_asi)
अणु
	काष्ठा pt_regs *regs = current_thपढ़ो_info()->kern_una_regs;
	अचिन्हित पूर्णांक insn = current_thपढ़ो_info()->kern_una_insn;
	स्थिर काष्ठा exception_table_entry *entry;

	entry = search_exception_tables(regs->tpc);
	अगर (!entry) अणु
		अचिन्हित दीर्घ address;

		address = compute_effective_address(regs, insn,
						    ((insn >> 25) & 0x1f));
        	अगर (address < PAGE_SIZE) अणु
                	prपूर्णांकk(KERN_ALERT "Unable to handle kernel NULL "
			       "pointer dereference in mna handler");
        	पूर्ण अन्यथा
                	prपूर्णांकk(KERN_ALERT "Unable to handle kernel paging "
			       "request in mna handler");
	        prपूर्णांकk(KERN_ALERT " at virtual address %016lx\n",address);
		prपूर्णांकk(KERN_ALERT "current->{active_,}mm->context = %016lx\n",
			(current->mm ? CTX_HWBITS(current->mm->context) :
			CTX_HWBITS(current->active_mm->context)));
		prपूर्णांकk(KERN_ALERT "current->{active_,}mm->pgd = %016lx\n",
			(current->mm ? (अचिन्हित दीर्घ) current->mm->pgd :
			(अचिन्हित दीर्घ) current->active_mm->pgd));
	        die_अगर_kernel("Oops", regs);
		/* Not reached */
	पूर्ण
	regs->tpc = entry->fixup;
	regs->tnpc = regs->tpc + 4;

	अगर (fixup_tstate_asi) अणु
		regs->tstate &= ~TSTATE_ASI;
		regs->tstate |= (ASI_AIUS << 24UL);
	पूर्ण
पूर्ण

अटल व्योम log_unaligned(काष्ठा pt_regs *regs)
अणु
	अटल DEFINE_RATELIMIT_STATE(ratelimit, 5 * HZ, 5);

	अगर (__ratelimit(&ratelimit)) अणु
		prपूर्णांकk("Kernel unaligned access at TPC[%lx] %pS\n",
		       regs->tpc, (व्योम *) regs->tpc);
	पूर्ण
पूर्ण

यंत्रlinkage व्योम kernel_unaligned_trap(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक insn)
अणु
	क्रमागत direction dir = decode_direction(insn);
	पूर्णांक size = decode_access_size(regs, insn);
	पूर्णांक orig_asi, asi;

	current_thपढ़ो_info()->kern_una_regs = regs;
	current_thपढ़ो_info()->kern_una_insn = insn;

	orig_asi = asi = decode_asi(insn, regs);

	/* If this is a अणुget,putपूर्ण_user() on an unaligned userspace poपूर्णांकer,
	 * just संकेत a fault and करो not log the event.
	 */
	अगर (asi == ASI_AIUS) अणु
		kernel_mna_trap_fault(0);
		वापस;
	पूर्ण

	log_unaligned(regs);

	अगर (!ok_क्रम_kernel(insn) || dir == both) अणु
		prपूर्णांकk("Unsupported unaligned load/store trap for kernel "
		       "at <%016lx>.\n", regs->tpc);
		unaligned_panic("Kernel does fpu/atomic "
				"unaligned load/store.", regs);

		kernel_mna_trap_fault(0);
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ addr, *reg_addr;
		पूर्णांक err;

		addr = compute_effective_address(regs, insn,
						 ((insn >> 25) & 0x1f));
		perf_sw_event(PERF_COUNT_SW_ALIGNMENT_FAULTS, 1, regs, addr);
		चयन (asi) अणु
		हाल ASI_NL:
		हाल ASI_AIUPL:
		हाल ASI_AIUSL:
		हाल ASI_PL:
		हाल ASI_SL:
		हाल ASI_PNFL:
		हाल ASI_SNFL:
			asi &= ~0x08;
			अवरोध;
		पूर्ण
		चयन (dir) अणु
		हाल load:
			reg_addr = fetch_reg_addr(((insn>>25)&0x1f), regs);
			err = करो_पूर्णांक_load(reg_addr, size,
					  (अचिन्हित दीर्घ *) addr,
					  decode_चिन्हितness(insn), asi);
			अगर (likely(!err) && unlikely(asi != orig_asi)) अणु
				अचिन्हित दीर्घ val_in = *reg_addr;
				चयन (size) अणु
				हाल 2:
					val_in = swab16(val_in);
					अवरोध;
				हाल 4:
					val_in = swab32(val_in);
					अवरोध;
				हाल 8:
					val_in = swab64(val_in);
					अवरोध;
				हाल 16:
				शेष:
					BUG();
					अवरोध;
				पूर्ण
				*reg_addr = val_in;
			पूर्ण
			अवरोध;

		हाल store:
			err = करो_पूर्णांक_store(((insn>>25)&0x1f), size,
					   (अचिन्हित दीर्घ *) addr, regs,
					   asi, orig_asi);
			अवरोध;

		शेष:
			panic("Impossible kernel unaligned trap.");
			/* Not reached... */
		पूर्ण
		अगर (unlikely(err))
			kernel_mna_trap_fault(1);
		अन्यथा
			advance(regs);
	पूर्ण
पूर्ण

पूर्णांक handle_popc(u32 insn, काष्ठा pt_regs *regs)
अणु
	पूर्णांक from_kernel = (regs->tstate & TSTATE_PRIV) != 0;
	पूर्णांक ret, rd = ((insn >> 25) & 0x1f);
	u64 value;
	                        
	perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS, 1, regs, 0);
	अगर (insn & 0x2000) अणु
		maybe_flush_winकरोws(0, 0, rd, from_kernel);
		value = sign_extend_imm13(insn);
	पूर्ण अन्यथा अणु
		maybe_flush_winकरोws(0, insn & 0x1f, rd, from_kernel);
		value = fetch_reg(insn & 0x1f, regs);
	पूर्ण
	ret = hweight64(value);
	अगर (rd < 16) अणु
		अगर (rd)
			regs->u_regs[rd] = ret;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ fp = regs->u_regs[UREG_FP];

		अगर (!test_thपढ़ो_64bit_stack(fp)) अणु
			काष्ठा reg_winकरोw32 __user *win32;
			win32 = (काष्ठा reg_winकरोw32 __user *)((अचिन्हित दीर्घ)((u32)fp));
			put_user(ret, &win32->locals[rd - 16]);
		पूर्ण अन्यथा अणु
			काष्ठा reg_winकरोw __user *win;
			win = (काष्ठा reg_winकरोw __user *)(fp + STACK_BIAS);
			put_user(ret, &win->locals[rd - 16]);
		पूर्ण
	पूर्ण
	advance(regs);
	वापस 1;
पूर्ण

बाह्य व्योम करो_fpother(काष्ठा pt_regs *regs);
बाह्य व्योम करो_privact(काष्ठा pt_regs *regs);
बाह्य व्योम sun4v_data_access_exception(काष्ठा pt_regs *regs,
					अचिन्हित दीर्घ addr,
					अचिन्हित दीर्घ type_ctx);

पूर्णांक handle_ldf_stq(u32 insn, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ addr = compute_effective_address(regs, insn, 0);
	पूर्णांक freg;
	काष्ठा fpustate *f = FPUSTATE;
	पूर्णांक asi = decode_asi(insn, regs);
	पूर्णांक flag;

	perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS, 1, regs, 0);

	save_and_clear_fpu();
	current_thपढ़ो_info()->xfsr[0] &= ~0x1c000;
	अगर (insn & 0x200000) अणु
		/* STQ */
		u64 first = 0, second = 0;
		
		freg = ((insn >> 25) & 0x1e) | ((insn >> 20) & 0x20);
		flag = (freg < 32) ? FPRS_DL : FPRS_DU;
		अगर (freg & 3) अणु
			current_thपढ़ो_info()->xfsr[0] |= (6 << 14) /* invalid_fp_रेजिस्टर */;
			करो_fpother(regs);
			वापस 0;
		पूर्ण
		अगर (current_thपढ़ो_info()->fpsaved[0] & flag) अणु
			first = *(u64 *)&f->regs[freg];
			second = *(u64 *)&f->regs[freg+2];
		पूर्ण
		अगर (asi < 0x80) अणु
			करो_privact(regs);
			वापस 1;
		पूर्ण
		चयन (asi) अणु
		हाल ASI_P:
		हाल ASI_S: अवरोध;
		हाल ASI_PL:
		हाल ASI_SL: 
			अणु
				/* Need to convert endians */
				u64 पंचांगp = __swab64p(&first);
				
				first = __swab64p(&second);
				second = पंचांगp;
				अवरोध;
			पूर्ण
		शेष:
			अगर (tlb_type == hypervisor)
				sun4v_data_access_exception(regs, addr, 0);
			अन्यथा
				spitfire_data_access_exception(regs, 0, addr);
			वापस 1;
		पूर्ण
		अगर (put_user (first >> 32, (u32 __user *)addr) ||
		    __put_user ((u32)first, (u32 __user *)(addr + 4)) ||
		    __put_user (second >> 32, (u32 __user *)(addr + 8)) ||
		    __put_user ((u32)second, (u32 __user *)(addr + 12))) अणु
			अगर (tlb_type == hypervisor)
				sun4v_data_access_exception(regs, addr, 0);
			अन्यथा
				spitfire_data_access_exception(regs, 0, addr);
		    	वापस 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* LDF, LDDF, LDQF */
		u32 data[4] __attribute__ ((aligned(8)));
		पूर्णांक size, i;
		पूर्णांक err;

		अगर (asi < 0x80) अणु
			करो_privact(regs);
			वापस 1;
		पूर्ण अन्यथा अगर (asi > ASI_SNFL) अणु
			अगर (tlb_type == hypervisor)
				sun4v_data_access_exception(regs, addr, 0);
			अन्यथा
				spitfire_data_access_exception(regs, 0, addr);
			वापस 1;
		पूर्ण
		चयन (insn & 0x180000) अणु
		हाल 0x000000: size = 1; अवरोध;
		हाल 0x100000: size = 4; अवरोध;
		शेष: size = 2; अवरोध;
		पूर्ण
		अगर (size == 1)
			freg = (insn >> 25) & 0x1f;
		अन्यथा
			freg = ((insn >> 25) & 0x1e) | ((insn >> 20) & 0x20);
		flag = (freg < 32) ? FPRS_DL : FPRS_DU;

		क्रम (i = 0; i < size; i++)
			data[i] = 0;
		
		err = get_user (data[0], (u32 __user *) addr);
		अगर (!err) अणु
			क्रम (i = 1; i < size; i++)
				err |= __get_user (data[i], (u32 __user *)(addr + 4*i));
		पूर्ण
		अगर (err && !(asi & 0x2 /* NF */)) अणु
			अगर (tlb_type == hypervisor)
				sun4v_data_access_exception(regs, addr, 0);
			अन्यथा
				spitfire_data_access_exception(regs, 0, addr);
			वापस 1;
		पूर्ण
		अगर (asi & 0x8) /* Little */ अणु
			u64 पंचांगp;

			चयन (size) अणु
			हाल 1: data[0] = le32_to_cpup(data + 0); अवरोध;
			शेष:*(u64 *)(data + 0) = le64_to_cpup((u64 *)(data + 0));
				अवरोध;
			हाल 4: पंचांगp = le64_to_cpup((u64 *)(data + 0));
				*(u64 *)(data + 0) = le64_to_cpup((u64 *)(data + 2));
				*(u64 *)(data + 2) = पंचांगp;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!(current_thपढ़ो_info()->fpsaved[0] & FPRS_FEF)) अणु
			current_thपढ़ो_info()->fpsaved[0] = FPRS_FEF;
			current_thपढ़ो_info()->gsr[0] = 0;
		पूर्ण
		अगर (!(current_thपढ़ो_info()->fpsaved[0] & flag)) अणु
			अगर (freg < 32)
				स_रखो(f->regs, 0, 32*माप(u32));
			अन्यथा
				स_रखो(f->regs+32, 0, 32*माप(u32));
		पूर्ण
		स_नकल(f->regs + freg, data, size * 4);
		current_thपढ़ो_info()->fpsaved[0] |= flag;
	पूर्ण
	advance(regs);
	वापस 1;
पूर्ण

व्योम handle_ld_nf(u32 insn, काष्ठा pt_regs *regs)
अणु
	पूर्णांक rd = ((insn >> 25) & 0x1f);
	पूर्णांक from_kernel = (regs->tstate & TSTATE_PRIV) != 0;
	अचिन्हित दीर्घ *reg;
	                        
	perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS, 1, regs, 0);

	maybe_flush_winकरोws(0, 0, rd, from_kernel);
	reg = fetch_reg_addr(rd, regs);
	अगर (from_kernel || rd < 16) अणु
		reg[0] = 0;
		अगर ((insn & 0x780000) == 0x180000)
			reg[1] = 0;
	पूर्ण अन्यथा अगर (!test_thपढ़ो_64bit_stack(regs->u_regs[UREG_FP])) अणु
		put_user(0, (पूर्णांक __user *) reg);
		अगर ((insn & 0x780000) == 0x180000)
			put_user(0, ((पूर्णांक __user *) reg) + 1);
	पूर्ण अन्यथा अणु
		put_user(0, (अचिन्हित दीर्घ __user *) reg);
		अगर ((insn & 0x780000) == 0x180000)
			put_user(0, (अचिन्हित दीर्घ __user *) reg + 1);
	पूर्ण
	advance(regs);
पूर्ण

व्योम handle_lddfmna(काष्ठा pt_regs *regs, अचिन्हित दीर्घ sfar, अचिन्हित दीर्घ sfsr)
अणु
	क्रमागत ctx_state prev_state = exception_enter();
	अचिन्हित दीर्घ pc = regs->tpc;
	अचिन्हित दीर्घ tstate = regs->tstate;
	u32 insn;
	u64 value;
	u8 freg;
	पूर्णांक flag;
	काष्ठा fpustate *f = FPUSTATE;

	अगर (tstate & TSTATE_PRIV)
		die_अगर_kernel("lddfmna from kernel", regs);
	perf_sw_event(PERF_COUNT_SW_ALIGNMENT_FAULTS, 1, regs, sfar);
	अगर (test_thपढ़ो_flag(TIF_32BIT))
		pc = (u32)pc;
	अगर (get_user(insn, (u32 __user *) pc) != -EFAULT) अणु
		पूर्णांक asi = decode_asi(insn, regs);
		u32 first, second;
		पूर्णांक err;

		अगर ((asi > ASI_SNFL) ||
		    (asi < ASI_P))
			जाओ daex;
		first = second = 0;
		err = get_user(first, (u32 __user *)sfar);
		अगर (!err)
			err = get_user(second, (u32 __user *)(sfar + 4));
		अगर (err) अणु
			अगर (!(asi & 0x2))
				जाओ daex;
			first = second = 0;
		पूर्ण
		save_and_clear_fpu();
		freg = ((insn >> 25) & 0x1e) | ((insn >> 20) & 0x20);
		value = (((u64)first) << 32) | second;
		अगर (asi & 0x8) /* Little */
			value = __swab64p(&value);
		flag = (freg < 32) ? FPRS_DL : FPRS_DU;
		अगर (!(current_thपढ़ो_info()->fpsaved[0] & FPRS_FEF)) अणु
			current_thपढ़ो_info()->fpsaved[0] = FPRS_FEF;
			current_thपढ़ो_info()->gsr[0] = 0;
		पूर्ण
		अगर (!(current_thपढ़ो_info()->fpsaved[0] & flag)) अणु
			अगर (freg < 32)
				स_रखो(f->regs, 0, 32*माप(u32));
			अन्यथा
				स_रखो(f->regs+32, 0, 32*माप(u32));
		पूर्ण
		*(u64 *)(f->regs + freg) = value;
		current_thपढ़ो_info()->fpsaved[0] |= flag;
	पूर्ण अन्यथा अणु
daex:
		अगर (tlb_type == hypervisor)
			sun4v_data_access_exception(regs, sfar, sfsr);
		अन्यथा
			spitfire_data_access_exception(regs, sfsr, sfar);
		जाओ out;
	पूर्ण
	advance(regs);
out:
	exception_निकास(prev_state);
पूर्ण

व्योम handle_stdfmna(काष्ठा pt_regs *regs, अचिन्हित दीर्घ sfar, अचिन्हित दीर्घ sfsr)
अणु
	क्रमागत ctx_state prev_state = exception_enter();
	अचिन्हित दीर्घ pc = regs->tpc;
	अचिन्हित दीर्घ tstate = regs->tstate;
	u32 insn;
	u64 value;
	u8 freg;
	पूर्णांक flag;
	काष्ठा fpustate *f = FPUSTATE;

	अगर (tstate & TSTATE_PRIV)
		die_अगर_kernel("stdfmna from kernel", regs);
	perf_sw_event(PERF_COUNT_SW_ALIGNMENT_FAULTS, 1, regs, sfar);
	अगर (test_thपढ़ो_flag(TIF_32BIT))
		pc = (u32)pc;
	अगर (get_user(insn, (u32 __user *) pc) != -EFAULT) अणु
		पूर्णांक asi = decode_asi(insn, regs);
		freg = ((insn >> 25) & 0x1e) | ((insn >> 20) & 0x20);
		value = 0;
		flag = (freg < 32) ? FPRS_DL : FPRS_DU;
		अगर ((asi > ASI_SNFL) ||
		    (asi < ASI_P))
			जाओ daex;
		save_and_clear_fpu();
		अगर (current_thपढ़ो_info()->fpsaved[0] & flag)
			value = *(u64 *)&f->regs[freg];
		चयन (asi) अणु
		हाल ASI_P:
		हाल ASI_S: अवरोध;
		हाल ASI_PL:
		हाल ASI_SL: 
			value = __swab64p(&value); अवरोध;
		शेष: जाओ daex;
		पूर्ण
		अगर (put_user (value >> 32, (u32 __user *) sfar) ||
		    __put_user ((u32)value, (u32 __user *)(sfar + 4)))
			जाओ daex;
	पूर्ण अन्यथा अणु
daex:
		अगर (tlb_type == hypervisor)
			sun4v_data_access_exception(regs, sfar, sfsr);
		अन्यथा
			spitfire_data_access_exception(regs, sfsr, sfar);
		जाओ out;
	पूर्ण
	advance(regs);
out:
	exception_निकास(prev_state);
पूर्ण
