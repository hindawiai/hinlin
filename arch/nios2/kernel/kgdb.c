<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Nios2 KGDB support
 *
 * Copyright (C) 2015 Altera Corporation
 * Copyright (C) 2011 Tobias Klauser <tklauser@distanz.ch>
 *
 * Based on the code posted by Kazuyasu on the Altera Forum at:
 * http://www.alteraक्रमum.com/क्रमum/showpost.php?p=77003&postcount=20
 */
#समावेश <linux/ptrace.h>
#समावेश <linux/kgdb.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/पन.स>

अटल पूर्णांक रुको_क्रम_remote_debugger;

काष्ठा dbg_reg_def_t dbg_reg_def[DBG_MAX_REG_NUM] =
अणु
	अणु "zero", GDB_SIZखातापूर्ण_REG, -1 पूर्ण,
	अणु "at", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r1) पूर्ण,
	अणु "r2", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r2) पूर्ण,
	अणु "r3", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r3) पूर्ण,
	अणु "r4", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r4) पूर्ण,
	अणु "r5", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r5) पूर्ण,
	अणु "r6", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r6) पूर्ण,
	अणु "r7", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r7) पूर्ण,
	अणु "r8", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r8) पूर्ण,
	अणु "r9", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r9) पूर्ण,
	अणु "r10", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r10) पूर्ण,
	अणु "r11", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r11) पूर्ण,
	अणु "r12", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r12) पूर्ण,
	अणु "r13", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r13) पूर्ण,
	अणु "r14", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r14) पूर्ण,
	अणु "r15", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, r15) पूर्ण,
	अणु "r16", GDB_SIZखातापूर्ण_REG, -1 पूर्ण,
	अणु "r17", GDB_SIZखातापूर्ण_REG, -1 पूर्ण,
	अणु "r18", GDB_SIZखातापूर्ण_REG, -1 पूर्ण,
	अणु "r19", GDB_SIZखातापूर्ण_REG, -1 पूर्ण,
	अणु "r20", GDB_SIZखातापूर्ण_REG, -1 पूर्ण,
	अणु "r21", GDB_SIZखातापूर्ण_REG, -1 पूर्ण,
	अणु "r22", GDB_SIZखातापूर्ण_REG, -1 पूर्ण,
	अणु "r23", GDB_SIZखातापूर्ण_REG, -1 पूर्ण,
	अणु "et", GDB_SIZखातापूर्ण_REG, -1 पूर्ण,
	अणु "bt", GDB_SIZखातापूर्ण_REG, -1 पूर्ण,
	अणु "gp", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, gp) पूर्ण,
	अणु "sp", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, sp) पूर्ण,
	अणु "fp", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, fp) पूर्ण,
	अणु "ea", GDB_SIZखातापूर्ण_REG, -1 पूर्ण,
	अणु "ba", GDB_SIZखातापूर्ण_REG, -1 पूर्ण,
	अणु "ra", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, ra) पूर्ण,
	अणु "pc", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, ea) पूर्ण,
	अणु "status", GDB_SIZखातापूर्ण_REG, -1 पूर्ण,
	अणु "estatus", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, estatus) पूर्ण,
	अणु "bstatus", GDB_SIZखातापूर्ण_REG, -1 पूर्ण,
	अणु "ienable", GDB_SIZखातापूर्ण_REG, -1 पूर्ण,
	अणु "ipending", GDB_SIZखातापूर्ण_REG, -1पूर्ण,
	अणु "cpuid", GDB_SIZखातापूर्ण_REG, -1 पूर्ण,
	अणु "ctl6", GDB_SIZखातापूर्ण_REG, -1 पूर्ण,
	अणु "exception", GDB_SIZखातापूर्ण_REG, -1 पूर्ण,
	अणु "pteaddr", GDB_SIZखातापूर्ण_REG, -1 पूर्ण,
	अणु "tlbacc", GDB_SIZखातापूर्ण_REG, -1 पूर्ण,
	अणु "tlbmisc", GDB_SIZखातापूर्ण_REG, -1 पूर्ण,
	अणु "eccinj", GDB_SIZखातापूर्ण_REG, -1 पूर्ण,
	अणु "badaddr", GDB_SIZखातापूर्ण_REG, -1 पूर्ण,
	अणु "config", GDB_SIZखातापूर्ण_REG, -1 पूर्ण,
	अणु "mpubase", GDB_SIZखातापूर्ण_REG, -1 पूर्ण,
	अणु "mpuacc", GDB_SIZखातापूर्ण_REG, -1 पूर्ण,
पूर्ण;

अक्षर *dbg_get_reg(पूर्णांक regno, व्योम *mem, काष्ठा pt_regs *regs)
अणु
	अगर (regno >= DBG_MAX_REG_NUM || regno < 0)
		वापस शून्य;

	अगर (dbg_reg_def[regno].offset != -1)
		स_नकल(mem, (व्योम *)regs + dbg_reg_def[regno].offset,
		       dbg_reg_def[regno].size);
	अन्यथा
		स_रखो(mem, 0, dbg_reg_def[regno].size);

	वापस dbg_reg_def[regno].name;
पूर्ण

पूर्णांक dbg_set_reg(पूर्णांक regno, व्योम *mem, काष्ठा pt_regs *regs)
अणु
	अगर (regno >= DBG_MAX_REG_NUM || regno < 0)
		वापस -EINVAL;

	अगर (dbg_reg_def[regno].offset != -1)
		स_नकल((व्योम *)regs + dbg_reg_def[regno].offset, mem,
		       dbg_reg_def[regno].size);

	वापस 0;
पूर्ण

व्योम sleeping_thपढ़ो_to_gdb_regs(अचिन्हित दीर्घ *gdb_regs, काष्ठा task_काष्ठा *p)
अणु
	स_रखो((अक्षर *)gdb_regs, 0, NUMREGBYTES);
	gdb_regs[GDB_SP] = p->thपढ़ो.kregs->sp;
	gdb_regs[GDB_PC] = p->thपढ़ो.kregs->ea;
पूर्ण

व्योम kgdb_arch_set_pc(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc)
अणु
	regs->ea = pc;
पूर्ण

पूर्णांक kgdb_arch_handle_exception(पूर्णांक vector, पूर्णांक signo, पूर्णांक err_code,
				अक्षर *remcom_in_buffer, अक्षर *remcom_out_buffer,
				काष्ठा pt_regs *regs)
अणु
	अक्षर *ptr;
	अचिन्हित दीर्घ addr;

	चयन (remcom_in_buffer[0]) अणु
	हाल 's':
	हाल 'c':
		/* handle the optional parameters */
		ptr = &remcom_in_buffer[1];
		अगर (kgdb_hex2दीर्घ(&ptr, &addr))
			regs->ea = addr;

		वापस 0;
	पूर्ण

	वापस -1; /* this means that we करो not want to निकास from the handler */
पूर्ण

यंत्रlinkage व्योम kgdb_अवरोधpoपूर्णांक_c(काष्ठा pt_regs *regs)
अणु
	/*
	 * The अवरोधpoपूर्णांक entry code has moved the PC on by 4 bytes, so we must
	 * move it back.  This could be करोne on the host but we करो it here
	 */
	अगर (!रुको_क्रम_remote_debugger)
		regs->ea -= 4;
	अन्यथा	/* pass the first trap 30 code */
		रुको_क्रम_remote_debugger = 0;

	kgdb_handle_exception(30, SIGTRAP, 0, regs);
पूर्ण

पूर्णांक kgdb_arch_init(व्योम)
अणु
	रुको_क्रम_remote_debugger = 1;
	वापस 0;
पूर्ण

व्योम kgdb_arch_निकास(व्योम)
अणु
	/* Nothing to करो */
पूर्ण

स्थिर काष्ठा kgdb_arch arch_kgdb_ops = अणु
	/* Breakpoपूर्णांक inकाष्ठाion: trap 30 */
	.gdb_bpt_instr = अणु 0xba, 0x6f, 0x3b, 0x00 पूर्ण,
पूर्ण;
