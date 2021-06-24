<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Hangzhou C-SKY Microप्रणालीs co.,ltd.

#समावेश <linux/kernel.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/ptrace.h>

अटल पूर्णांक align_kern_enable = 1;
अटल पूर्णांक align_usr_enable = 1;
अटल पूर्णांक align_kern_count = 0;
अटल पूर्णांक align_usr_count = 0;

अटल अंतरभूत uपूर्णांक32_t get_ptreg(काष्ठा pt_regs *regs, uपूर्णांक32_t rx)
अणु
	वापस rx == 15 ? regs->lr : *((uपूर्णांक32_t *)&(regs->a0) - 2 + rx);
पूर्ण

अटल अंतरभूत व्योम put_ptreg(काष्ठा pt_regs *regs, uपूर्णांक32_t rx, uपूर्णांक32_t val)
अणु
	अगर (rx == 15)
		regs->lr = val;
	अन्यथा
		*((uपूर्णांक32_t *)&(regs->a0) - 2 + rx) = val;
पूर्ण

/*
 * Get byte-value from addr and set it to *valp.
 *
 * Success: वापस 0
 * Failure: वापस 1
 */
अटल पूर्णांक ldb_यंत्र(uपूर्णांक32_t addr, uपूर्णांक32_t *valp)
अणु
	uपूर्णांक32_t val;
	पूर्णांक err;

	यंत्र अस्थिर (
		"movi	%0, 0\n"
		"1:\n"
		"ldb	%1, (%2)\n"
		"br	3f\n"
		"2:\n"
		"movi	%0, 1\n"
		"br	3f\n"
		".section __ex_table,\"a\"\n"
		".align 2\n"
		".long	1b, 2b\n"
		".previous\n"
		"3:\n"
		: "=&r"(err), "=r"(val)
		: "r" (addr)
	);

	*valp = val;

	वापस err;
पूर्ण

/*
 * Put byte-value to addr.
 *
 * Success: वापस 0
 * Failure: वापस 1
 */
अटल पूर्णांक stb_यंत्र(uपूर्णांक32_t addr, uपूर्णांक32_t val)
अणु
	पूर्णांक err;

	यंत्र अस्थिर (
		"movi	%0, 0\n"
		"1:\n"
		"stb	%1, (%2)\n"
		"br	3f\n"
		"2:\n"
		"movi	%0, 1\n"
		"br	3f\n"
		".section __ex_table,\"a\"\n"
		".align 2\n"
		".long	1b, 2b\n"
		".previous\n"
		"3:\n"
		: "=&r"(err)
		: "r"(val), "r" (addr)
	);

	वापस err;
पूर्ण

/*
 * Get half-word from [rx + imm]
 *
 * Success: वापस 0
 * Failure: वापस 1
 */
अटल पूर्णांक ldh_c(काष्ठा pt_regs *regs, uपूर्णांक32_t rz, uपूर्णांक32_t addr)
अणु
	uपूर्णांक32_t byte0, byte1;

	अगर (ldb_यंत्र(addr, &byte0))
		वापस 1;
	addr += 1;
	अगर (ldb_यंत्र(addr, &byte1))
		वापस 1;

	byte0 |= byte1 << 8;
	put_ptreg(regs, rz, byte0);

	वापस 0;
पूर्ण

/*
 * Store half-word to [rx + imm]
 *
 * Success: वापस 0
 * Failure: वापस 1
 */
अटल पूर्णांक sth_c(काष्ठा pt_regs *regs, uपूर्णांक32_t rz, uपूर्णांक32_t addr)
अणु
	uपूर्णांक32_t byte0, byte1;

	byte0 = byte1 = get_ptreg(regs, rz);

	byte0 &= 0xff;

	अगर (stb_यंत्र(addr, byte0))
		वापस 1;

	addr += 1;
	byte1 = (byte1 >> 8) & 0xff;
	अगर (stb_यंत्र(addr, byte1))
		वापस 1;

	वापस 0;
पूर्ण

/*
 * Get word from [rx + imm]
 *
 * Success: वापस 0
 * Failure: वापस 1
 */
अटल पूर्णांक ldw_c(काष्ठा pt_regs *regs, uपूर्णांक32_t rz, uपूर्णांक32_t addr)
अणु
	uपूर्णांक32_t byte0, byte1, byte2, byte3;

	अगर (ldb_यंत्र(addr, &byte0))
		वापस 1;

	addr += 1;
	अगर (ldb_यंत्र(addr, &byte1))
		वापस 1;

	addr += 1;
	अगर (ldb_यंत्र(addr, &byte2))
		वापस 1;

	addr += 1;
	अगर (ldb_यंत्र(addr, &byte3))
		वापस 1;

	byte0 |= byte1 << 8;
	byte0 |= byte2 << 16;
	byte0 |= byte3 << 24;

	put_ptreg(regs, rz, byte0);

	वापस 0;
पूर्ण

/*
 * Store word to [rx + imm]
 *
 * Success: वापस 0
 * Failure: वापस 1
 */
अटल पूर्णांक stw_c(काष्ठा pt_regs *regs, uपूर्णांक32_t rz, uपूर्णांक32_t addr)
अणु
	uपूर्णांक32_t byte0, byte1, byte2, byte3;

	byte0 = byte1 = byte2 = byte3 = get_ptreg(regs, rz);

	byte0 &= 0xff;

	अगर (stb_यंत्र(addr, byte0))
		वापस 1;

	addr += 1;
	byte1 = (byte1 >> 8) & 0xff;
	अगर (stb_यंत्र(addr, byte1))
		वापस 1;

	addr += 1;
	byte2 = (byte2 >> 16) & 0xff;
	अगर (stb_यंत्र(addr, byte2))
		वापस 1;

	addr += 1;
	byte3 = (byte3 >> 24) & 0xff;
	अगर (stb_यंत्र(addr, byte3))
		वापस 1;

	वापस 0;
पूर्ण

बाह्य पूर्णांक fixup_exception(काष्ठा pt_regs *regs);

#घोषणा OP_LDH 0xc000
#घोषणा OP_STH 0xd000
#घोषणा OP_LDW 0x8000
#घोषणा OP_STW 0x9000

व्योम csky_alignment(काष्ठा pt_regs *regs)
अणु
	पूर्णांक ret;
	uपूर्णांक16_t पंचांगp;
	uपूर्णांक32_t opcode = 0;
	uपूर्णांक32_t rx     = 0;
	uपूर्णांक32_t rz     = 0;
	uपूर्णांक32_t imm    = 0;
	uपूर्णांक32_t addr   = 0;

	अगर (!user_mode(regs))
		जाओ kernel_area;

	अगर (!align_usr_enable) अणु
		pr_err("%s user disabled.\n", __func__);
		जाओ bad_area;
	पूर्ण

	align_usr_count++;

	ret = get_user(पंचांगp, (uपूर्णांक16_t *)inकाष्ठाion_poपूर्णांकer(regs));
	अगर (ret) अणु
		pr_err("%s get_user failed.\n", __func__);
		जाओ bad_area;
	पूर्ण

	जाओ good_area;

kernel_area:
	अगर (!align_kern_enable) अणु
		pr_err("%s kernel disabled.\n", __func__);
		जाओ bad_area;
	पूर्ण

	align_kern_count++;

	पंचांगp = *(uपूर्णांक16_t *)inकाष्ठाion_poपूर्णांकer(regs);

good_area:
	opcode = (uपूर्णांक32_t)पंचांगp;

	rx  = opcode & 0xf;
	imm = (opcode >> 4) & 0xf;
	rz  = (opcode >> 8) & 0xf;
	opcode &= 0xf000;

	अगर (rx == 0 || rx == 1 || rz == 0 || rz == 1)
		जाओ bad_area;

	चयन (opcode) अणु
	हाल OP_LDH:
		addr = get_ptreg(regs, rx) + (imm << 1);
		ret = ldh_c(regs, rz, addr);
		अवरोध;
	हाल OP_LDW:
		addr = get_ptreg(regs, rx) + (imm << 2);
		ret = ldw_c(regs, rz, addr);
		अवरोध;
	हाल OP_STH:
		addr = get_ptreg(regs, rx) + (imm << 1);
		ret = sth_c(regs, rz, addr);
		अवरोध;
	हाल OP_STW:
		addr = get_ptreg(regs, rx) + (imm << 2);
		ret = stw_c(regs, rz, addr);
		अवरोध;
	पूर्ण

	अगर (ret)
		जाओ bad_area;

	regs->pc += 2;

	वापस;

bad_area:
	अगर (!user_mode(regs)) अणु
		अगर (fixup_exception(regs))
			वापस;

		bust_spinlocks(1);
		pr_alert("%s opcode: %x, rz: %d, rx: %d, imm: %d, addr: %x.\n",
				__func__, opcode, rz, rx, imm, addr);
		show_regs(regs);
		bust_spinlocks(0);
		करो_निकास(SIGKILL);
	पूर्ण

	क्रमce_sig_fault(SIGBUS, BUS_ADRALN, (व्योम __user *)addr);
पूर्ण

अटल काष्ठा ctl_table alignment_tbl[5] = अणु
	अणु
		.procname = "kernel_enable",
		.data = &align_kern_enable,
		.maxlen = माप(align_kern_enable),
		.mode = 0666,
		.proc_handler = &proc_करोपूर्णांकvec
	पूर्ण,
	अणु
		.procname = "user_enable",
		.data = &align_usr_enable,
		.maxlen = माप(align_usr_enable),
		.mode = 0666,
		.proc_handler = &proc_करोपूर्णांकvec
	पूर्ण,
	अणु
		.procname = "kernel_count",
		.data = &align_kern_count,
		.maxlen = माप(align_kern_count),
		.mode = 0666,
		.proc_handler = &proc_करोपूर्णांकvec
	पूर्ण,
	अणु
		.procname = "user_count",
		.data = &align_usr_count,
		.maxlen = माप(align_usr_count),
		.mode = 0666,
		.proc_handler = &proc_करोपूर्णांकvec
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा ctl_table sysctl_table[2] = अणु
	अणु
	 .procname = "csky_alignment",
	 .mode = 0555,
	 .child = alignment_tblपूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा ctl_path sysctl_path[2] = अणु
	अणु.procname = "csky"पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक __init csky_alignment_init(व्योम)
अणु
	रेजिस्टर_sysctl_paths(sysctl_path, sysctl_table);
	वापस 0;
पूर्ण

arch_initcall(csky_alignment_init);
