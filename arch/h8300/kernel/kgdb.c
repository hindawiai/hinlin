<शैली गुरु>
/*
 * H8/300 KGDB support
 *
 * Copyright (C) 2015 Yoshinori Sato <ysato@users.sourceक्रमge.jp>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/ptrace.h>
#समावेश <linux/kgdb.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/पन.स>

काष्ठा dbg_reg_def_t dbg_reg_def[DBG_MAX_REG_NUM] = अणु
	अणु "er0", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, er0) पूर्ण,
	अणु "er1", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, er1) पूर्ण,
	अणु "er2", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, er2) पूर्ण,
	अणु "er3", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, er3) पूर्ण,
	अणु "er4", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, er4) पूर्ण,
	अणु "er5", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, er5) पूर्ण,
	अणु "er6", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, er6) पूर्ण,
	अणु "sp", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, sp) पूर्ण,
	अणु "ccr", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, ccr) पूर्ण,
	अणु "pc", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, pc) पूर्ण,
	अणु "cycles", GDB_SIZखातापूर्ण_REG, -1 पूर्ण,
#अगर defined(CONFIG_CPU_H8S)
	अणु "exr", GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, exr) पूर्ण,
#पूर्ण_अगर
	अणु "tick", GDB_SIZखातापूर्ण_REG, -1 पूर्ण,
	अणु "inst", GDB_SIZखातापूर्ण_REG, -1 पूर्ण,
पूर्ण;

अक्षर *dbg_get_reg(पूर्णांक regno, व्योम *mem, काष्ठा pt_regs *regs)
अणु
	अगर (regno >= DBG_MAX_REG_NUM || regno < 0)
		वापस शून्य;

	चयन (regno) अणु
	हाल GDB_CCR:
#अगर defined(CONFIG_CPU_H8S)
	हाल GDB_EXR:
#पूर्ण_अगर
		*(u32 *)mem = *(u16 *)((व्योम *)regs +
				       dbg_reg_def[regno].offset);
		अवरोध;
	शेष:
		अगर (dbg_reg_def[regno].offset >= 0)
			स_नकल(mem, (व्योम *)regs + dbg_reg_def[regno].offset,
			       dbg_reg_def[regno].size);
		अन्यथा
			स_रखो(mem, 0, dbg_reg_def[regno].size);
		अवरोध;
	पूर्ण
	वापस dbg_reg_def[regno].name;
पूर्ण

पूर्णांक dbg_set_reg(पूर्णांक regno, व्योम *mem, काष्ठा pt_regs *regs)
अणु
	अगर (regno >= DBG_MAX_REG_NUM || regno < 0)
		वापस -EINVAL;

	चयन (regno) अणु
	हाल GDB_CCR:
#अगर defined(CONFIG_CPU_H8S)
	हाल GDB_EXR:
#पूर्ण_अगर
		*(u16 *)((व्योम *)regs +
			 dbg_reg_def[regno].offset) = *(u32 *)mem;
		अवरोध;
	शेष:
		स_नकल((व्योम *)regs + dbg_reg_def[regno].offset, mem,
		       dbg_reg_def[regno].size);
	पूर्ण
	वापस 0;
पूर्ण

यंत्रlinkage व्योम h8300_kgdb_trap(काष्ठा pt_regs *regs)
अणु
	regs->pc &= 0x00ffffff;
	अगर (kgdb_handle_exception(10, SIGTRAP, 0, regs))
		वापस;
	अगर (*(u16 *)(regs->pc) == *(u16 *)&arch_kgdb_ops.gdb_bpt_instr)
		regs->pc += BREAK_INSTR_SIZE;
	regs->pc |= regs->ccr << 24;
पूर्ण

व्योम sleeping_thपढ़ो_to_gdb_regs(अचिन्हित दीर्घ *gdb_regs, काष्ठा task_काष्ठा *p)
अणु
	स_रखो((अक्षर *)gdb_regs, 0, NUMREGBYTES);
	gdb_regs[GDB_SP] = p->thपढ़ो.ksp;
	gdb_regs[GDB_PC] = KSTK_EIP(p);
पूर्ण

व्योम kgdb_arch_set_pc(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc)
अणु
	regs->pc = pc;
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
			regs->pc = addr;

		वापस 0;
	पूर्ण

	वापस -1; /* this means that we करो not want to निकास from the handler */
पूर्ण

पूर्णांक kgdb_arch_init(व्योम)
अणु
	वापस 0;
पूर्ण

व्योम kgdb_arch_निकास(व्योम)
अणु
	/* Nothing to करो */
पूर्ण

स्थिर काष्ठा kgdb_arch arch_kgdb_ops = अणु
	/* Breakpoपूर्णांक inकाष्ठाion: trapa #2 */
	.gdb_bpt_instr = अणु 0x57, 0x20 पूर्ण,
पूर्ण;
