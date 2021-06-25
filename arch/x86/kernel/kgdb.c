<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 */

/*
 * Copyright (C) 2004 Amit S. Kale <amitkale@linsyssoft.com>
 * Copyright (C) 2000-2001 VERITAS Software Corporation.
 * Copyright (C) 2002 Andi Kleen, SuSE Lअसल
 * Copyright (C) 2004 LinSysSoft Technologies Pvt. Ltd.
 * Copyright (C) 2007 MontaVista Software, Inc.
 * Copyright (C) 2007-2008 Jason Wessel, Wind River Systems, Inc.
 */
/****************************************************************************
 *  Contributor:     Lake Stevens Instrument Division$
 *  Written by:      Glenn Engel $
 *  Updated by:	     Amit Kale<akale@veritas.com>
 *  Updated by:	     Tom Rini <trini@kernel.crashing.org>
 *  Updated by:	     Jason Wessel <jason.wessel@windriver.com>
 *  Modअगरied क्रम 386 by Jim Kingकरोn, Cygnus Support.
 *  Original kgdb, compatibility with 2.1.xx kernel by
 *  David Grothe <dave@gcom.com>
 *  Integrated पूर्णांकo 2.2.5 kernel by Tigran Aivazian <tigran@sco.com>
 *  X86_64 changes from Andi Kleen's patch merged by Jim Houston
 */
#समावेश <linux/spinlock.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/kgdb.h>
#समावेश <linux/smp.h>
#समावेश <linux/nmi.h>
#समावेश <linux/hw_अवरोधpoपूर्णांक.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/memory.h>

#समावेश <यंत्र/text-patching.h>
#समावेश <यंत्र/debugreg.h>
#समावेश <यंत्र/apicdef.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/nmi.h>
#समावेश <यंत्र/चयन_to.h>

काष्ठा dbg_reg_def_t dbg_reg_def[DBG_MAX_REG_NUM] =
अणु
#अगर_घोषित CONFIG_X86_32
	अणु "ax", 4, दुरत्व(काष्ठा pt_regs, ax) पूर्ण,
	अणु "cx", 4, दुरत्व(काष्ठा pt_regs, cx) पूर्ण,
	अणु "dx", 4, दुरत्व(काष्ठा pt_regs, dx) पूर्ण,
	अणु "bx", 4, दुरत्व(काष्ठा pt_regs, bx) पूर्ण,
	अणु "sp", 4, दुरत्व(काष्ठा pt_regs, sp) पूर्ण,
	अणु "bp", 4, दुरत्व(काष्ठा pt_regs, bp) पूर्ण,
	अणु "si", 4, दुरत्व(काष्ठा pt_regs, si) पूर्ण,
	अणु "di", 4, दुरत्व(काष्ठा pt_regs, di) पूर्ण,
	अणु "ip", 4, दुरत्व(काष्ठा pt_regs, ip) पूर्ण,
	अणु "flags", 4, दुरत्व(काष्ठा pt_regs, flags) पूर्ण,
	अणु "cs", 4, दुरत्व(काष्ठा pt_regs, cs) पूर्ण,
	अणु "ss", 4, दुरत्व(काष्ठा pt_regs, ss) पूर्ण,
	अणु "ds", 4, दुरत्व(काष्ठा pt_regs, ds) पूर्ण,
	अणु "es", 4, दुरत्व(काष्ठा pt_regs, es) पूर्ण,
#अन्यथा
	अणु "ax", 8, दुरत्व(काष्ठा pt_regs, ax) पूर्ण,
	अणु "bx", 8, दुरत्व(काष्ठा pt_regs, bx) पूर्ण,
	अणु "cx", 8, दुरत्व(काष्ठा pt_regs, cx) पूर्ण,
	अणु "dx", 8, दुरत्व(काष्ठा pt_regs, dx) पूर्ण,
	अणु "si", 8, दुरत्व(काष्ठा pt_regs, si) पूर्ण,
	अणु "di", 8, दुरत्व(काष्ठा pt_regs, di) पूर्ण,
	अणु "bp", 8, दुरत्व(काष्ठा pt_regs, bp) पूर्ण,
	अणु "sp", 8, दुरत्व(काष्ठा pt_regs, sp) पूर्ण,
	अणु "r8", 8, दुरत्व(काष्ठा pt_regs, r8) पूर्ण,
	अणु "r9", 8, दुरत्व(काष्ठा pt_regs, r9) पूर्ण,
	अणु "r10", 8, दुरत्व(काष्ठा pt_regs, r10) पूर्ण,
	अणु "r11", 8, दुरत्व(काष्ठा pt_regs, r11) पूर्ण,
	अणु "r12", 8, दुरत्व(काष्ठा pt_regs, r12) पूर्ण,
	अणु "r13", 8, दुरत्व(काष्ठा pt_regs, r13) पूर्ण,
	अणु "r14", 8, दुरत्व(काष्ठा pt_regs, r14) पूर्ण,
	अणु "r15", 8, दुरत्व(काष्ठा pt_regs, r15) पूर्ण,
	अणु "ip", 8, दुरत्व(काष्ठा pt_regs, ip) पूर्ण,
	अणु "flags", 4, दुरत्व(काष्ठा pt_regs, flags) पूर्ण,
	अणु "cs", 4, दुरत्व(काष्ठा pt_regs, cs) पूर्ण,
	अणु "ss", 4, दुरत्व(काष्ठा pt_regs, ss) पूर्ण,
	अणु "ds", 4, -1 पूर्ण,
	अणु "es", 4, -1 पूर्ण,
#पूर्ण_अगर
	अणु "fs", 4, -1 पूर्ण,
	अणु "gs", 4, -1 पूर्ण,
पूर्ण;

पूर्णांक dbg_set_reg(पूर्णांक regno, व्योम *mem, काष्ठा pt_regs *regs)
अणु
	अगर (
#अगर_घोषित CONFIG_X86_32
	    regno == GDB_SS || regno == GDB_FS || regno == GDB_GS ||
#पूर्ण_अगर
	    regno == GDB_SP || regno == GDB_ORIG_AX)
		वापस 0;

	अगर (dbg_reg_def[regno].offset != -1)
		स_नकल((व्योम *)regs + dbg_reg_def[regno].offset, mem,
		       dbg_reg_def[regno].size);
	वापस 0;
पूर्ण

अक्षर *dbg_get_reg(पूर्णांक regno, व्योम *mem, काष्ठा pt_regs *regs)
अणु
	अगर (regno == GDB_ORIG_AX) अणु
		स_नकल(mem, &regs->orig_ax, माप(regs->orig_ax));
		वापस "orig_ax";
	पूर्ण
	अगर (regno >= DBG_MAX_REG_NUM || regno < 0)
		वापस शून्य;

	अगर (dbg_reg_def[regno].offset != -1)
		स_नकल(mem, (व्योम *)regs + dbg_reg_def[regno].offset,
		       dbg_reg_def[regno].size);

#अगर_घोषित CONFIG_X86_32
	चयन (regno) अणु
	हाल GDB_GS:
	हाल GDB_FS:
		*(अचिन्हित दीर्घ *)mem = 0xFFFF;
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	वापस dbg_reg_def[regno].name;
पूर्ण

/**
 *	sleeping_thपढ़ो_to_gdb_regs - Convert ptrace regs to GDB regs
 *	@gdb_regs: A poपूर्णांकer to hold the रेजिस्टरs in the order GDB wants.
 *	@p: The &काष्ठा task_काष्ठा of the desired process.
 *
 *	Convert the रेजिस्टर values of the sleeping process in @p to
 *	the क्रमmat that GDB expects.
 *	This function is called when kgdb करोes not have access to the
 *	&काष्ठा pt_regs and thereक्रमe it should fill the gdb रेजिस्टरs
 *	@gdb_regs with what has	been saved in &काष्ठा thपढ़ो_काष्ठा
 *	thपढ़ो field during चयन_to.
 */
व्योम sleeping_thपढ़ो_to_gdb_regs(अचिन्हित दीर्घ *gdb_regs, काष्ठा task_काष्ठा *p)
अणु
#अगर_अघोषित CONFIG_X86_32
	u32 *gdb_regs32 = (u32 *)gdb_regs;
#पूर्ण_अगर
	gdb_regs[GDB_AX]	= 0;
	gdb_regs[GDB_BX]	= 0;
	gdb_regs[GDB_CX]	= 0;
	gdb_regs[GDB_DX]	= 0;
	gdb_regs[GDB_SI]	= 0;
	gdb_regs[GDB_DI]	= 0;
	gdb_regs[GDB_BP]	= ((काष्ठा inactive_task_frame *)p->thपढ़ो.sp)->bp;
#अगर_घोषित CONFIG_X86_32
	gdb_regs[GDB_DS]	= __KERNEL_DS;
	gdb_regs[GDB_ES]	= __KERNEL_DS;
	gdb_regs[GDB_PS]	= 0;
	gdb_regs[GDB_CS]	= __KERNEL_CS;
	gdb_regs[GDB_SS]	= __KERNEL_DS;
	gdb_regs[GDB_FS]	= 0xFFFF;
	gdb_regs[GDB_GS]	= 0xFFFF;
#अन्यथा
	gdb_regs32[GDB_PS]	= 0;
	gdb_regs32[GDB_CS]	= __KERNEL_CS;
	gdb_regs32[GDB_SS]	= __KERNEL_DS;
	gdb_regs[GDB_R8]	= 0;
	gdb_regs[GDB_R9]	= 0;
	gdb_regs[GDB_R10]	= 0;
	gdb_regs[GDB_R11]	= 0;
	gdb_regs[GDB_R12]	= 0;
	gdb_regs[GDB_R13]	= 0;
	gdb_regs[GDB_R14]	= 0;
	gdb_regs[GDB_R15]	= 0;
#पूर्ण_अगर
	gdb_regs[GDB_PC]	= 0;
	gdb_regs[GDB_SP]	= p->thपढ़ो.sp;
पूर्ण

अटल काष्ठा hw_अवरोधpoपूर्णांक अणु
	अचिन्हित		enabled;
	अचिन्हित दीर्घ		addr;
	पूर्णांक			len;
	पूर्णांक			type;
	काष्ठा perf_event	* __percpu *pev;
पूर्ण अवरोधinfo[HBP_NUM];

अटल अचिन्हित दीर्घ early_dr7;

अटल व्योम kgdb_correct_hw_अवरोध(व्योम)
अणु
	पूर्णांक अवरोधno;

	क्रम (अवरोधno = 0; अवरोधno < HBP_NUM; अवरोधno++) अणु
		काष्ठा perf_event *bp;
		काष्ठा arch_hw_अवरोधpoपूर्णांक *info;
		पूर्णांक val;
		पूर्णांक cpu = raw_smp_processor_id();
		अगर (!अवरोधinfo[अवरोधno].enabled)
			जारी;
		अगर (dbg_is_early) अणु
			set_debugreg(अवरोधinfo[अवरोधno].addr, अवरोधno);
			early_dr7 |= encode_dr7(अवरोधno,
						अवरोधinfo[अवरोधno].len,
						अवरोधinfo[अवरोधno].type);
			set_debugreg(early_dr7, 7);
			जारी;
		पूर्ण
		bp = *per_cpu_ptr(अवरोधinfo[अवरोधno].pev, cpu);
		info = counter_arch_bp(bp);
		अगर (bp->attr.disabled != 1)
			जारी;
		bp->attr.bp_addr = अवरोधinfo[अवरोधno].addr;
		bp->attr.bp_len = अवरोधinfo[अवरोधno].len;
		bp->attr.bp_type = अवरोधinfo[अवरोधno].type;
		info->address = अवरोधinfo[अवरोधno].addr;
		info->len = अवरोधinfo[अवरोधno].len;
		info->type = अवरोधinfo[अवरोधno].type;
		val = arch_install_hw_अवरोधpoपूर्णांक(bp);
		अगर (!val)
			bp->attr.disabled = 0;
	पूर्ण
	अगर (!dbg_is_early)
		hw_अवरोधpoपूर्णांक_restore();
पूर्ण

अटल पूर्णांक hw_अवरोध_reserve_slot(पूर्णांक अवरोधno)
अणु
	पूर्णांक cpu;
	पूर्णांक cnt = 0;
	काष्ठा perf_event **pevent;

	अगर (dbg_is_early)
		वापस 0;

	क्रम_each_online_cpu(cpu) अणु
		cnt++;
		pevent = per_cpu_ptr(अवरोधinfo[अवरोधno].pev, cpu);
		अगर (dbg_reserve_bp_slot(*pevent))
			जाओ fail;
	पूर्ण

	वापस 0;

fail:
	क्रम_each_online_cpu(cpu) अणु
		cnt--;
		अगर (!cnt)
			अवरोध;
		pevent = per_cpu_ptr(अवरोधinfo[अवरोधno].pev, cpu);
		dbg_release_bp_slot(*pevent);
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक hw_अवरोध_release_slot(पूर्णांक अवरोधno)
अणु
	काष्ठा perf_event **pevent;
	पूर्णांक cpu;

	अगर (dbg_is_early)
		वापस 0;

	क्रम_each_online_cpu(cpu) अणु
		pevent = per_cpu_ptr(अवरोधinfo[अवरोधno].pev, cpu);
		अगर (dbg_release_bp_slot(*pevent))
			/*
			 * The debugger is responsible क्रम handing the retry on
			 * हटाओ failure.
			 */
			वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
kgdb_हटाओ_hw_अवरोध(अचिन्हित दीर्घ addr, पूर्णांक len, क्रमागत kgdb_bptype bptype)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < HBP_NUM; i++)
		अगर (अवरोधinfo[i].addr == addr && अवरोधinfo[i].enabled)
			अवरोध;
	अगर (i == HBP_NUM)
		वापस -1;

	अगर (hw_अवरोध_release_slot(i)) अणु
		prपूर्णांकk(KERN_ERR "Cannot remove hw breakpoint at %lx\n", addr);
		वापस -1;
	पूर्ण
	अवरोधinfo[i].enabled = 0;

	वापस 0;
पूर्ण

अटल व्योम kgdb_हटाओ_all_hw_अवरोध(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक cpu = raw_smp_processor_id();
	काष्ठा perf_event *bp;

	क्रम (i = 0; i < HBP_NUM; i++) अणु
		अगर (!अवरोधinfo[i].enabled)
			जारी;
		bp = *per_cpu_ptr(अवरोधinfo[i].pev, cpu);
		अगर (!bp->attr.disabled) अणु
			arch_uninstall_hw_अवरोधpoपूर्णांक(bp);
			bp->attr.disabled = 1;
			जारी;
		पूर्ण
		अगर (dbg_is_early)
			early_dr7 &= ~encode_dr7(i, अवरोधinfo[i].len,
						 अवरोधinfo[i].type);
		अन्यथा अगर (hw_अवरोध_release_slot(i))
			prपूर्णांकk(KERN_ERR "KGDB: hw bpt remove failed %lx\n",
			       अवरोधinfo[i].addr);
		अवरोधinfo[i].enabled = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक
kgdb_set_hw_अवरोध(अचिन्हित दीर्घ addr, पूर्णांक len, क्रमागत kgdb_bptype bptype)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < HBP_NUM; i++)
		अगर (!अवरोधinfo[i].enabled)
			अवरोध;
	अगर (i == HBP_NUM)
		वापस -1;

	चयन (bptype) अणु
	हाल BP_HARDWARE_BREAKPOINT:
		len = 1;
		अवरोधinfo[i].type = X86_BREAKPOINT_EXECUTE;
		अवरोध;
	हाल BP_WRITE_WATCHPOINT:
		अवरोधinfo[i].type = X86_BREAKPOINT_WRITE;
		अवरोध;
	हाल BP_ACCESS_WATCHPOINT:
		अवरोधinfo[i].type = X86_BREAKPOINT_RW;
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण
	चयन (len) अणु
	हाल 1:
		अवरोधinfo[i].len = X86_BREAKPOINT_LEN_1;
		अवरोध;
	हाल 2:
		अवरोधinfo[i].len = X86_BREAKPOINT_LEN_2;
		अवरोध;
	हाल 4:
		अवरोधinfo[i].len = X86_BREAKPOINT_LEN_4;
		अवरोध;
#अगर_घोषित CONFIG_X86_64
	हाल 8:
		अवरोधinfo[i].len = X86_BREAKPOINT_LEN_8;
		अवरोध;
#पूर्ण_अगर
	शेष:
		वापस -1;
	पूर्ण
	अवरोधinfo[i].addr = addr;
	अगर (hw_अवरोध_reserve_slot(i)) अणु
		अवरोधinfo[i].addr = 0;
		वापस -1;
	पूर्ण
	अवरोधinfo[i].enabled = 1;

	वापस 0;
पूर्ण

/**
 *	kgdb_disable_hw_debug - Disable hardware debugging जबतक we in kgdb.
 *	@regs: Current &काष्ठा pt_regs.
 *
 *	This function will be called अगर the particular architecture must
 *	disable hardware debugging जबतक it is processing gdb packets or
 *	handling exception.
 */
अटल व्योम kgdb_disable_hw_debug(काष्ठा pt_regs *regs)
अणु
	पूर्णांक i;
	पूर्णांक cpu = raw_smp_processor_id();
	काष्ठा perf_event *bp;

	/* Disable hardware debugging जबतक we are in kgdb: */
	set_debugreg(0UL, 7);
	क्रम (i = 0; i < HBP_NUM; i++) अणु
		अगर (!अवरोधinfo[i].enabled)
			जारी;
		अगर (dbg_is_early) अणु
			early_dr7 &= ~encode_dr7(i, अवरोधinfo[i].len,
						 अवरोधinfo[i].type);
			जारी;
		पूर्ण
		bp = *per_cpu_ptr(अवरोधinfo[i].pev, cpu);
		अगर (bp->attr.disabled == 1)
			जारी;
		arch_uninstall_hw_अवरोधpoपूर्णांक(bp);
		bp->attr.disabled = 1;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_SMP
/**
 *	kgdb_roundup_cpus - Get other CPUs पूर्णांकo a holding pattern
 *
 *	On SMP प्रणालीs, we need to get the attention of the other CPUs
 *	and get them be in a known state.  This should करो what is needed
 *	to get the other CPUs to call kgdb_रुको(). Note that on some arches,
 *	the NMI approach is not used क्रम rounding up all the CPUs. For example,
 *	in हाल of MIPS, smp_call_function() is used to roundup CPUs.
 *
 *	On non-SMP प्रणालीs, this is not called.
 */
व्योम kgdb_roundup_cpus(व्योम)
अणु
	apic_send_IPI_allbutself(NMI_VECTOR);
पूर्ण
#पूर्ण_अगर

/**
 *	kgdb_arch_handle_exception - Handle architecture specअगरic GDB packets.
 *	@e_vector: The error vector of the exception that happened.
 *	@signo: The संकेत number of the exception that happened.
 *	@err_code: The error code of the exception that happened.
 *	@remcomInBuffer: The buffer of the packet we have पढ़ो.
 *	@remcomOutBuffer: The buffer of %BUFMAX bytes to ग_लिखो a packet पूर्णांकo.
 *	@linux_regs: The &काष्ठा pt_regs of the current process.
 *
 *	This function MUST handle the 'c' and 's' command packets,
 *	as well packets to set / हटाओ a hardware अवरोधpoपूर्णांक, अगर used.
 *	If there are additional packets which the hardware needs to handle,
 *	they are handled here.  The code should वापस -1 अगर it wants to
 *	process more packets, and a %0 or %1 अगर it wants to निकास from the
 *	kgdb callback.
 */
पूर्णांक kgdb_arch_handle_exception(पूर्णांक e_vector, पूर्णांक signo, पूर्णांक err_code,
			       अक्षर *remcomInBuffer, अक्षर *remcomOutBuffer,
			       काष्ठा pt_regs *linux_regs)
अणु
	अचिन्हित दीर्घ addr;
	अक्षर *ptr;

	चयन (remcomInBuffer[0]) अणु
	हाल 'c':
	हाल 's':
		/* try to पढ़ो optional parameter, pc unchanged अगर no parm */
		ptr = &remcomInBuffer[1];
		अगर (kgdb_hex2दीर्घ(&ptr, &addr))
			linux_regs->ip = addr;
		fallthrough;
	हाल 'D':
	हाल 'k':
		/* clear the trace bit */
		linux_regs->flags &= ~X86_EFLAGS_TF;
		atomic_set(&kgdb_cpu_करोing_single_step, -1);

		/* set the trace bit अगर we're stepping */
		अगर (remcomInBuffer[0] == 's') अणु
			linux_regs->flags |= X86_EFLAGS_TF;
			atomic_set(&kgdb_cpu_करोing_single_step,
				   raw_smp_processor_id());
		पूर्ण

		वापस 0;
	पूर्ण

	/* this means that we करो not want to निकास from the handler: */
	वापस -1;
पूर्ण

अटल अंतरभूत पूर्णांक
single_step_cont(काष्ठा pt_regs *regs, काष्ठा die_args *args)
अणु
	/*
	 * Single step exception from kernel space to user space so
	 * eat the exception and जारी the process:
	 */
	prपूर्णांकk(KERN_ERR "KGDB: trap/step from kernel to user space, "
			"resuming...\n");
	kgdb_arch_handle_exception(args->trapnr, args->signr,
				   args->err, "c", "", regs);
	/*
	 * Reset the BS bit in dr6 (poपूर्णांकed by args->err) to
	 * denote completion of processing
	 */
	(*(अचिन्हित दीर्घ *)ERR_PTR(args->err)) &= ~DR_STEP;

	वापस NOTIFY_STOP;
पूर्ण

अटल DECLARE_BITMAP(was_in_debug_nmi, NR_CPUS);

अटल पूर्णांक kgdb_nmi_handler(अचिन्हित पूर्णांक cmd, काष्ठा pt_regs *regs)
अणु
	पूर्णांक cpu;

	चयन (cmd) अणु
	हाल NMI_LOCAL:
		अगर (atomic_पढ़ो(&kgdb_active) != -1) अणु
			/* KGDB CPU roundup */
			cpu = raw_smp_processor_id();
			kgdb_nmicallback(cpu, regs);
			set_bit(cpu, was_in_debug_nmi);
			touch_nmi_watchकरोg();

			वापस NMI_HANDLED;
		पूर्ण
		अवरोध;

	हाल NMI_UNKNOWN:
		cpu = raw_smp_processor_id();

		अगर (__test_and_clear_bit(cpu, was_in_debug_nmi))
			वापस NMI_HANDLED;

		अवरोध;
	शेष:
		/* करो nothing */
		अवरोध;
	पूर्ण
	वापस NMI_DONE;
पूर्ण

अटल पूर्णांक __kgdb_notअगरy(काष्ठा die_args *args, अचिन्हित दीर्घ cmd)
अणु
	काष्ठा pt_regs *regs = args->regs;

	चयन (cmd) अणु
	हाल DIE_DEBUG:
		अगर (atomic_पढ़ो(&kgdb_cpu_करोing_single_step) != -1) अणु
			अगर (user_mode(regs))
				वापस single_step_cont(regs, args);
			अवरोध;
		पूर्ण अन्यथा अगर (test_thपढ़ो_flag(TIF_SINGLESTEP))
			/* This means a user thपढ़ो is single stepping
			 * a प्रणाली call which should be ignored
			 */
			वापस NOTIFY_DONE;
		fallthrough;
	शेष:
		अगर (user_mode(regs))
			वापस NOTIFY_DONE;
	पूर्ण

	अगर (kgdb_handle_exception(args->trapnr, args->signr, cmd, regs))
		वापस NOTIFY_DONE;

	/* Must touch watchकरोg beक्रमe वापस to normal operation */
	touch_nmi_watchकरोg();
	वापस NOTIFY_STOP;
पूर्ण

पूर्णांक kgdb_ll_trap(पूर्णांक cmd, स्थिर अक्षर *str,
		 काष्ठा pt_regs *regs, दीर्घ err, पूर्णांक trap, पूर्णांक sig)
अणु
	काष्ठा die_args args = अणु
		.regs	= regs,
		.str	= str,
		.err	= err,
		.trapnr	= trap,
		.signr	= sig,

	पूर्ण;

	अगर (!kgdb_io_module_रेजिस्टरed)
		वापस NOTIFY_DONE;

	वापस __kgdb_notअगरy(&args, cmd);
पूर्ण

अटल पूर्णांक
kgdb_notअगरy(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ cmd, व्योम *ptr)
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
पूर्ण;

/**
 *	kgdb_arch_init - Perक्रमm any architecture specअगरic initialization.
 *
 *	This function will handle the initialization of any architecture
 *	specअगरic callbacks.
 */
पूर्णांक kgdb_arch_init(व्योम)
अणु
	पूर्णांक retval;

	retval = रेजिस्टर_die_notअगरier(&kgdb_notअगरier);
	अगर (retval)
		जाओ out;

	retval = रेजिस्टर_nmi_handler(NMI_LOCAL, kgdb_nmi_handler,
					0, "kgdb");
	अगर (retval)
		जाओ out1;

	retval = रेजिस्टर_nmi_handler(NMI_UNKNOWN, kgdb_nmi_handler,
					0, "kgdb");

	अगर (retval)
		जाओ out2;

	वापस retval;

out2:
	unरेजिस्टर_nmi_handler(NMI_LOCAL, "kgdb");
out1:
	unरेजिस्टर_die_notअगरier(&kgdb_notअगरier);
out:
	वापस retval;
पूर्ण

अटल व्योम kgdb_hw_overflow_handler(काष्ठा perf_event *event,
		काष्ठा perf_sample_data *data, काष्ठा pt_regs *regs)
अणु
	काष्ठा task_काष्ठा *tsk = current;
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
		अगर (अवरोधinfo[i].enabled)
			tsk->thपढ़ो.भव_dr6 |= (DR_TRAP0 << i);
	पूर्ण
पूर्ण

व्योम kgdb_arch_late(व्योम)
अणु
	पूर्णांक i, cpu;
	काष्ठा perf_event_attr attr;
	काष्ठा perf_event **pevent;

	/*
	 * Pre-allocate the hw अवरोधpoपूर्णांक inकाष्ठाions in the non-atomic
	 * portion of kgdb because this operation requires mutexs to
	 * complete.
	 */
	hw_अवरोधpoपूर्णांक_init(&attr);
	attr.bp_addr = (अचिन्हित दीर्घ)kgdb_arch_init;
	attr.bp_len = HW_BREAKPOINT_LEN_1;
	attr.bp_type = HW_BREAKPOINT_W;
	attr.disabled = 1;
	क्रम (i = 0; i < HBP_NUM; i++) अणु
		अगर (अवरोधinfo[i].pev)
			जारी;
		अवरोधinfo[i].pev = रेजिस्टर_wide_hw_अवरोधpoपूर्णांक(&attr, शून्य, शून्य);
		अगर (IS_ERR((व्योम * __क्रमce)अवरोधinfo[i].pev)) अणु
			prपूर्णांकk(KERN_ERR "kgdb: Could not allocate hw"
			       "breakpoints\nDisabling the kernel debugger\n");
			अवरोधinfo[i].pev = शून्य;
			kgdb_arch_निकास();
			वापस;
		पूर्ण
		क्रम_each_online_cpu(cpu) अणु
			pevent = per_cpu_ptr(अवरोधinfo[i].pev, cpu);
			pevent[0]->hw.sample_period = 1;
			pevent[0]->overflow_handler = kgdb_hw_overflow_handler;
			अगर (pevent[0]->destroy != शून्य) अणु
				pevent[0]->destroy = शून्य;
				release_bp_slot(*pevent);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/**
 *	kgdb_arch_निकास - Perक्रमm any architecture specअगरic uninitalization.
 *
 *	This function will handle the uninitalization of any architecture
 *	specअगरic callbacks, क्रम dynamic registration and unregistration.
 */
व्योम kgdb_arch_निकास(व्योम)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < 4; i++) अणु
		अगर (अवरोधinfo[i].pev) अणु
			unरेजिस्टर_wide_hw_अवरोधpoपूर्णांक(अवरोधinfo[i].pev);
			अवरोधinfo[i].pev = शून्य;
		पूर्ण
	पूर्ण
	unरेजिस्टर_nmi_handler(NMI_UNKNOWN, "kgdb");
	unरेजिस्टर_nmi_handler(NMI_LOCAL, "kgdb");
	unरेजिस्टर_die_notअगरier(&kgdb_notअगरier);
पूर्ण

/**
 *
 *	kgdb_skipexception - Bail out of KGDB when we've been triggered.
 *	@exception: Exception vector number
 *	@regs: Current &काष्ठा pt_regs.
 *
 *	On some architectures we need to skip a अवरोधpoपूर्णांक exception when
 *	it occurs after a अवरोधpoपूर्णांक has been हटाओd.
 *
 * Skip an पूर्णांक3 exception when it occurs after a अवरोधpoपूर्णांक has been
 * हटाओd. Backtrack eip by 1 since the पूर्णांक3 would have caused it to
 * increment by 1.
 */
पूर्णांक kgdb_skipexception(पूर्णांक exception, काष्ठा pt_regs *regs)
अणु
	अगर (exception == 3 && kgdb_isहटाओdअवरोध(regs->ip - 1)) अणु
		regs->ip -= 1;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अचिन्हित दीर्घ kgdb_arch_pc(पूर्णांक exception, काष्ठा pt_regs *regs)
अणु
	अगर (exception == 3)
		वापस inकाष्ठाion_poपूर्णांकer(regs) - 1;
	वापस inकाष्ठाion_poपूर्णांकer(regs);
पूर्ण

व्योम kgdb_arch_set_pc(काष्ठा pt_regs *regs, अचिन्हित दीर्घ ip)
अणु
	regs->ip = ip;
पूर्ण

पूर्णांक kgdb_arch_set_अवरोधpoपूर्णांक(काष्ठा kgdb_bkpt *bpt)
अणु
	पूर्णांक err;

	bpt->type = BP_BREAKPOINT;
	err = copy_from_kernel_nofault(bpt->saved_instr, (अक्षर *)bpt->bpt_addr,
				BREAK_INSTR_SIZE);
	अगर (err)
		वापस err;
	err = copy_to_kernel_nofault((अक्षर *)bpt->bpt_addr,
				 arch_kgdb_ops.gdb_bpt_instr, BREAK_INSTR_SIZE);
	अगर (!err)
		वापस err;
	/*
	 * It is safe to call text_poke_kgdb() because normal kernel execution
	 * is stopped on all cores, so दीर्घ as the text_mutex is not locked.
	 */
	अगर (mutex_is_locked(&text_mutex))
		वापस -EBUSY;
	text_poke_kgdb((व्योम *)bpt->bpt_addr, arch_kgdb_ops.gdb_bpt_instr,
		       BREAK_INSTR_SIZE);
	bpt->type = BP_POKE_BREAKPOINT;

	वापस 0;
पूर्ण

पूर्णांक kgdb_arch_हटाओ_अवरोधpoपूर्णांक(काष्ठा kgdb_bkpt *bpt)
अणु
	अगर (bpt->type != BP_POKE_BREAKPOINT)
		जाओ knl_ग_लिखो;
	/*
	 * It is safe to call text_poke_kgdb() because normal kernel execution
	 * is stopped on all cores, so दीर्घ as the text_mutex is not locked.
	 */
	अगर (mutex_is_locked(&text_mutex))
		जाओ knl_ग_लिखो;
	text_poke_kgdb((व्योम *)bpt->bpt_addr, bpt->saved_instr,
		       BREAK_INSTR_SIZE);
	वापस 0;

knl_ग_लिखो:
	वापस copy_to_kernel_nofault((अक्षर *)bpt->bpt_addr,
				  (अक्षर *)bpt->saved_instr, BREAK_INSTR_SIZE);
पूर्ण

स्थिर काष्ठा kgdb_arch arch_kgdb_ops = अणु
	/* Breakpoपूर्णांक inकाष्ठाion: */
	.gdb_bpt_instr		= अणु 0xcc पूर्ण,
	.flags			= KGDB_HW_BREAKPOINT,
	.set_hw_अवरोधpoपूर्णांक	= kgdb_set_hw_अवरोध,
	.हटाओ_hw_अवरोधpoपूर्णांक	= kgdb_हटाओ_hw_अवरोध,
	.disable_hw_अवरोध	= kgdb_disable_hw_debug,
	.हटाओ_all_hw_अवरोध	= kgdb_हटाओ_all_hw_अवरोध,
	.correct_hw_अवरोध	= kgdb_correct_hw_अवरोध,
पूर्ण;
