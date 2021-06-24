<शैली गुरु>
/*
 * umip.c Emulation क्रम inकाष्ठाion रक्षित by the User-Mode Inकाष्ठाion
 * Prevention feature
 *
 * Copyright (c) 2017, Intel Corporation.
 * Ricarकरो Neri <ricarकरो.neri-calderon@linux.पूर्णांकel.com>
 */

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/umip.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/insn.h>
#समावेश <यंत्र/insn-eval.h>
#समावेश <linux/ratelimit.h>

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) "umip: " fmt

/** DOC: Emulation क्रम User-Mode Inकाष्ठाion Prevention (UMIP)
 *
 * User-Mode Inकाष्ठाion Prevention is a security feature present in recent
 * x86 processors that, when enabled, prevents a group of inकाष्ठाions (SGDT,
 * SIDT, SLDT, SMSW and STR) from being run in user mode by issuing a general
 * protection fault अगर the inकाष्ठाion is executed with CPL > 0.
 *
 * Rather than relaying to the user space the general protection fault caused by
 * the UMIP-रक्षित inकाष्ठाions (in the क्रमm of a संक_अंश संकेत), it can be
 * trapped and emulate the result of such inकाष्ठाions to provide dummy values.
 * This allows to both conserve the current kernel behavior and not reveal the
 * प्रणाली resources that UMIP पूर्णांकends to protect (i.e., the locations of the
 * global descriptor and पूर्णांकerrupt descriptor tables, the segment selectors of
 * the local descriptor table, the value of the task state रेजिस्टर and the
 * contents of the CR0 रेजिस्टर).
 *
 * This emulation is needed because certain applications (e.g., WineHQ and
 * DOSEMU2) rely on this subset of inकाष्ठाions to function.
 *
 * The inकाष्ठाions रक्षित by UMIP can be split in two groups. Those which
 * वापस a kernel memory address (SGDT and SIDT) and those which वापस a
 * value (SLDT, STR and SMSW).
 *
 * For the inकाष्ठाions that वापस a kernel memory address, applications
 * such as WineHQ rely on the result being located in the kernel memory space,
 * not the actual location of the table. The result is emulated as a hard-coded
 * value that, lies बंद to the top of the kernel memory. The limit क्रम the GDT
 * and the IDT are set to zero.
 *
 * The inकाष्ठाion SMSW is emulated to वापस the value that the रेजिस्टर CR0
 * has at boot समय as set in the head_32.
 * SLDT and STR are emulated to वापस the values that the kernel programmatically
 * assigns:
 * - SLDT वापसs (GDT_ENTRY_LDT * 8) अगर an LDT has been set, 0 अगर not.
 * - STR वापसs (GDT_ENTRY_TSS * 8).
 *
 * Emulation is provided क्रम both 32-bit and 64-bit processes.
 *
 * Care is taken to appropriately emulate the results when segmentation is
 * used. That is, rather than relying on USER_DS and USER_CS, the function
 * insn_get_addr_ref() inspects the segment descriptor poपूर्णांकed by the
 * रेजिस्टरs in pt_regs. This ensures that we correctly obtain the segment
 * base address and the address and opeअक्रम sizes even अगर the user space
 * application uses a local descriptor table.
 */

#घोषणा UMIP_DUMMY_GDT_BASE 0xfffffffffffe0000ULL
#घोषणा UMIP_DUMMY_IDT_BASE 0xffffffffffff0000ULL

/*
 * The SGDT and SIDT inकाष्ठाions store the contents of the global descriptor
 * table and पूर्णांकerrupt table रेजिस्टरs, respectively. The destination is a
 * memory opeअक्रम of X+2 bytes. X bytes are used to store the base address of
 * the table and 2 bytes are used to store the limit. In 32-bit processes X
 * has a value of 4, in 64-bit processes X has a value of 8.
 */
#घोषणा UMIP_GDT_IDT_BASE_SIZE_64BIT 8
#घोषणा UMIP_GDT_IDT_BASE_SIZE_32BIT 4
#घोषणा UMIP_GDT_IDT_LIMIT_SIZE 2

#घोषणा	UMIP_INST_SGDT	0	/* 0F 01 /0 */
#घोषणा	UMIP_INST_SIDT	1	/* 0F 01 /1 */
#घोषणा	UMIP_INST_SMSW	2	/* 0F 01 /4 */
#घोषणा	UMIP_INST_SLDT  3       /* 0F 00 /0 */
#घोषणा	UMIP_INST_STR   4       /* 0F 00 /1 */

अटल स्थिर अक्षर * स्थिर umip_insns[5] = अणु
	[UMIP_INST_SGDT] = "SGDT",
	[UMIP_INST_SIDT] = "SIDT",
	[UMIP_INST_SMSW] = "SMSW",
	[UMIP_INST_SLDT] = "SLDT",
	[UMIP_INST_STR] = "STR",
पूर्ण;

#घोषणा umip_pr_err(regs, fmt, ...) \
	umip_prपूर्णांकk(regs, KERN_ERR, fmt, ##__VA_ARGS__)
#घोषणा umip_pr_warn(regs, fmt, ...) \
	umip_prपूर्णांकk(regs, KERN_WARNING, fmt,  ##__VA_ARGS__)

/**
 * umip_prपूर्णांकk() - Prपूर्णांक a rate-limited message
 * @regs:	Register set with the context in which the warning is prपूर्णांकed
 * @log_level:	Kernel log level to prपूर्णांक the message
 * @fmt:	The text string to prपूर्णांक
 *
 * Prपूर्णांक the text contained in @fmt. The prपूर्णांक rate is limited to bursts of 5
 * messages every two minutes. The purpose of this customized version of
 * prपूर्णांकk() is to prपूर्णांक messages when user space processes use any of the
 * UMIP-रक्षित inकाष्ठाions. Thus, the prपूर्णांकed text is prepended with the
 * task name and process ID number of the current task as well as the
 * inकाष्ठाion and stack poपूर्णांकers in @regs as seen when entering kernel mode.
 *
 * Returns:
 *
 * None.
 */
अटल __म_लिखो(3, 4)
व्योम umip_prपूर्णांकk(स्थिर काष्ठा pt_regs *regs, स्थिर अक्षर *log_level,
		 स्थिर अक्षर *fmt, ...)
अणु
	/* Bursts of 5 messages every two minutes */
	अटल DEFINE_RATELIMIT_STATE(ratelimit, 2 * 60 * HZ, 5);
	काष्ठा task_काष्ठा *tsk = current;
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	अगर (!__ratelimit(&ratelimit))
		वापस;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	prपूर्णांकk("%s" pr_fmt("%s[%d] ip:%lx sp:%lx: %pV"), log_level, tsk->comm,
	       task_pid_nr(tsk), regs->ip, regs->sp, &vaf);
	बहु_पूर्ण(args);
पूर्ण

/**
 * identअगरy_insn() - Identअगरy a UMIP-रक्षित inकाष्ठाion
 * @insn:	Inकाष्ठाion काष्ठाure with opcode and ModRM byte.
 *
 * From the opcode and ModRM.reg in @insn identअगरy, अगर any, a UMIP-रक्षित
 * inकाष्ठाion that can be emulated.
 *
 * Returns:
 *
 * On success, a स्थिरant identअगरying a specअगरic UMIP-रक्षित inकाष्ठाion that
 * can be emulated.
 *
 * -EINVAL on error or when not an UMIP-रक्षित inकाष्ठाion that can be
 * emulated.
 */
अटल पूर्णांक identअगरy_insn(काष्ठा insn *insn)
अणु
	/* By getting modrm we also get the opcode. */
	insn_get_modrm(insn);

	अगर (!insn->modrm.nbytes)
		वापस -EINVAL;

	/* All the inकाष्ठाions of पूर्णांकerest start with 0x0f. */
	अगर (insn->opcode.bytes[0] != 0xf)
		वापस -EINVAL;

	अगर (insn->opcode.bytes[1] == 0x1) अणु
		चयन (X86_MODRM_REG(insn->modrm.value)) अणु
		हाल 0:
			वापस UMIP_INST_SGDT;
		हाल 1:
			वापस UMIP_INST_SIDT;
		हाल 4:
			वापस UMIP_INST_SMSW;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (insn->opcode.bytes[1] == 0x0) अणु
		अगर (X86_MODRM_REG(insn->modrm.value) == 0)
			वापस UMIP_INST_SLDT;
		अन्यथा अगर (X86_MODRM_REG(insn->modrm.value) == 1)
			वापस UMIP_INST_STR;
		अन्यथा
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
पूर्ण

/**
 * emulate_umip_insn() - Emulate UMIP inकाष्ठाions and वापस dummy values
 * @insn:	Inकाष्ठाion काष्ठाure with opeअक्रमs
 * @umip_inst:	A स्थिरant indicating the inकाष्ठाion to emulate
 * @data:	Buffer पूर्णांकo which the dummy result is stored
 * @data_size:	Size of the emulated result
 * @x86_64:	true अगर process is 64-bit, false otherwise
 *
 * Emulate an inकाष्ठाion रक्षित by UMIP and provide a dummy result. The
 * result of the emulation is saved in @data. The size of the results depends
 * on both the inकाष्ठाion and type of opeअक्रम (रेजिस्टर vs memory address).
 * The size of the result is updated in @data_size. Caller is responsible
 * of providing a @data buffer of at least UMIP_GDT_IDT_BASE_SIZE +
 * UMIP_GDT_IDT_LIMIT_SIZE bytes.
 *
 * Returns:
 *
 * 0 on success, -EINVAL on error जबतक emulating.
 */
अटल पूर्णांक emulate_umip_insn(काष्ठा insn *insn, पूर्णांक umip_inst,
			     अचिन्हित अक्षर *data, पूर्णांक *data_size, bool x86_64)
अणु
	अगर (!data || !data_size || !insn)
		वापस -EINVAL;
	/*
	 * These two inकाष्ठाions वापस the base address and limit of the
	 * global and पूर्णांकerrupt descriptor table, respectively. According to the
	 * Intel Software Development manual, the base address can be 24-bit,
	 * 32-bit or 64-bit. Limit is always 16-bit. If the opeअक्रम size is
	 * 16-bit, the वापसed value of the base address is supposed to be a
	 * zero-extended 24-byte number. However, it seems that a 32-byte number
	 * is always वापसed irrespective of the opeअक्रम size.
	 */
	अगर (umip_inst == UMIP_INST_SGDT || umip_inst == UMIP_INST_SIDT) अणु
		u64 dummy_base_addr;
		u16 dummy_limit = 0;

		/* SGDT and SIDT करो not use रेजिस्टरs opeअक्रमs. */
		अगर (X86_MODRM_MOD(insn->modrm.value) == 3)
			वापस -EINVAL;

		अगर (umip_inst == UMIP_INST_SGDT)
			dummy_base_addr = UMIP_DUMMY_GDT_BASE;
		अन्यथा
			dummy_base_addr = UMIP_DUMMY_IDT_BASE;

		/*
		 * 64-bit processes use the entire dummy base address.
		 * 32-bit processes use the lower 32 bits of the base address.
		 * dummy_base_addr is always 64 bits, but we स_नकल the correct
		 * number of bytes from it to the destination.
		 */
		अगर (x86_64)
			*data_size = UMIP_GDT_IDT_BASE_SIZE_64BIT;
		अन्यथा
			*data_size = UMIP_GDT_IDT_BASE_SIZE_32BIT;

		स_नकल(data + 2, &dummy_base_addr, *data_size);

		*data_size += UMIP_GDT_IDT_LIMIT_SIZE;
		स_नकल(data, &dummy_limit, UMIP_GDT_IDT_LIMIT_SIZE);

	पूर्ण अन्यथा अगर (umip_inst == UMIP_INST_SMSW || umip_inst == UMIP_INST_SLDT ||
		   umip_inst == UMIP_INST_STR) अणु
		अचिन्हित दीर्घ dummy_value;

		अगर (umip_inst == UMIP_INST_SMSW) अणु
			dummy_value = CR0_STATE;
		पूर्ण अन्यथा अगर (umip_inst == UMIP_INST_STR) अणु
			dummy_value = GDT_ENTRY_TSS * 8;
		पूर्ण अन्यथा अगर (umip_inst == UMIP_INST_SLDT) अणु
#अगर_घोषित CONFIG_MODIFY_LDT_SYSCALL
			करोwn_पढ़ो(&current->mm->context.ldt_usr_sem);
			अगर (current->mm->context.ldt)
				dummy_value = GDT_ENTRY_LDT * 8;
			अन्यथा
				dummy_value = 0;
			up_पढ़ो(&current->mm->context.ldt_usr_sem);
#अन्यथा
			dummy_value = 0;
#पूर्ण_अगर
		पूर्ण

		/*
		 * For these 3 inकाष्ठाions, the number
		 * of bytes to be copied in the result buffer is determined
		 * by whether the opeअक्रम is a रेजिस्टर or a memory location.
		 * If opeअक्रम is a रेजिस्टर, वापस as many bytes as the opeअक्रम
		 * size. If opeअक्रम is memory, वापस only the two least
		 * signअगरicant bytes.
		 */
		अगर (X86_MODRM_MOD(insn->modrm.value) == 3)
			*data_size = insn->opnd_bytes;
		अन्यथा
			*data_size = 2;

		स_नकल(data, &dummy_value, *data_size);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * क्रमce_sig_info_umip_fault() - Force a संक_अंश with SEGV_MAPERR
 * @addr:	Address that caused the संकेत
 * @regs:	Register set containing the inकाष्ठाion poपूर्णांकer
 *
 * Force a संक_अंश संकेत with SEGV_MAPERR as the error code. This function is
 * पूर्णांकended to be used to provide a segmentation fault when the result of the
 * UMIP emulation could not be copied to the user space memory.
 *
 * Returns: none
 */
अटल व्योम क्रमce_sig_info_umip_fault(व्योम __user *addr, काष्ठा pt_regs *regs)
अणु
	काष्ठा task_काष्ठा *tsk = current;

	tsk->thपढ़ो.cr2		= (अचिन्हित दीर्घ)addr;
	tsk->thपढ़ो.error_code	= X86_PF_USER | X86_PF_WRITE;
	tsk->thपढ़ो.trap_nr	= X86_TRAP_PF;

	क्रमce_sig_fault(संक_अंश, SEGV_MAPERR, addr);

	अगर (!(show_unhandled_संकेतs && unhandled_संकेत(tsk, संक_अंश)))
		वापस;

	umip_pr_err(regs, "segfault in emulation. error%x\n",
		    X86_PF_USER | X86_PF_WRITE);
पूर्ण

/**
 * fixup_umip_exception() - Fixup a general protection fault caused by UMIP
 * @regs:	Registers as saved when entering the #GP handler
 *
 * The inकाष्ठाions SGDT, SIDT, STR, SMSW and SLDT cause a general protection
 * fault अगर executed with CPL > 0 (i.e., from user space). This function fixes
 * the exception up and provides dummy results क्रम SGDT, SIDT and SMSW; STR
 * and SLDT are not fixed up.
 *
 * If opeअक्रमs are memory addresses, results are copied to user-space memory as
 * indicated by the inकाष्ठाion poपूर्णांकed by eIP using the रेजिस्टरs indicated in
 * the inकाष्ठाion opeअक्रमs. If opeअक्रमs are रेजिस्टरs, results are copied पूर्णांकo
 * the context that was saved when entering kernel mode.
 *
 * Returns:
 *
 * True अगर emulation was successful; false अगर not.
 */
bool fixup_umip_exception(काष्ठा pt_regs *regs)
अणु
	पूर्णांक nr_copied, reg_offset, dummy_data_size, umip_inst;
	/* 10 bytes is the maximum size of the result of UMIP inकाष्ठाions */
	अचिन्हित अक्षर dummy_data[10] = अणु 0 पूर्ण;
	अचिन्हित अक्षर buf[MAX_INSN_SIZE];
	अचिन्हित दीर्घ *reg_addr;
	व्योम __user *uaddr;
	काष्ठा insn insn;

	अगर (!regs)
		वापस false;

	nr_copied = insn_fetch_from_user(regs, buf);

	/*
	 * The insn_fetch_from_user above could have failed अगर user code
	 * is रक्षित by a memory protection key. Give up on emulation
	 * in such a हाल.  Should we issue a page fault?
	 */
	अगर (!nr_copied)
		वापस false;

	अगर (!insn_decode_from_regs(&insn, regs, buf, nr_copied))
		वापस false;

	umip_inst = identअगरy_insn(&insn);
	अगर (umip_inst < 0)
		वापस false;

	umip_pr_warn(regs, "%s instruction cannot be used by applications.\n",
			umip_insns[umip_inst]);

	umip_pr_warn(regs, "For now, expensive software emulation returns the result.\n");

	अगर (emulate_umip_insn(&insn, umip_inst, dummy_data, &dummy_data_size,
			      user_64bit_mode(regs)))
		वापस false;

	/*
	 * If opeअक्रम is a रेजिस्टर, ग_लिखो result to the copy of the रेजिस्टर
	 * value that was pushed to the stack when entering पूर्णांकo kernel mode.
	 * Upon निकास, the value we ग_लिखो will be restored to the actual hardware
	 * रेजिस्टर.
	 */
	अगर (X86_MODRM_MOD(insn.modrm.value) == 3) अणु
		reg_offset = insn_get_modrm_rm_off(&insn, regs);

		/*
		 * Negative values are usually errors. In memory addressing,
		 * the exception is -गलत_तर्क. Since we expect a रेजिस्टर opeअक्रम,
		 * all negative values are errors.
		 */
		अगर (reg_offset < 0)
			वापस false;

		reg_addr = (अचिन्हित दीर्घ *)((अचिन्हित दीर्घ)regs + reg_offset);
		स_नकल(reg_addr, dummy_data, dummy_data_size);
	पूर्ण अन्यथा अणु
		uaddr = insn_get_addr_ref(&insn, regs);
		अगर ((अचिन्हित दीर्घ)uaddr == -1L)
			वापस false;

		nr_copied = copy_to_user(uaddr, dummy_data, dummy_data_size);
		अगर (nr_copied  > 0) अणु
			/*
			 * If copy fails, send a संकेत and tell caller that
			 * fault was fixed up.
			 */
			क्रमce_sig_info_umip_fault(uaddr, regs);
			वापस true;
		पूर्ण
	पूर्ण

	/* increase IP to let the program keep going */
	regs->ip += insn.length;
	वापस true;
पूर्ण
