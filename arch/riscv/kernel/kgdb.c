<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 SiFive
 */

#समावेश <linux/ptrace.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/bug.h>
#समावेश <linux/kgdb.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/माला.स>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/gdb_xml.h>
#समावेश <यंत्र/parse_यंत्र.h>

क्रमागत अणु
	NOT_KGDB_BREAK = 0,
	KGDB_SW_BREAK,
	KGDB_COMPILED_BREAK,
	KGDB_SW_SINGLE_STEP
पूर्ण;

अटल अचिन्हित दीर्घ stepped_address;
अटल अचिन्हित पूर्णांक stepped_opcode;

#अगर __riscv_xlen == 32
/* C.JAL is an RV32C-only inकाष्ठाion */
DECLARE_INSN(c_jal, MATCH_C_JAL, MASK_C_JAL)
#अन्यथा
#घोषणा is_c_jal_insn(opcode) 0
#पूर्ण_अगर
DECLARE_INSN(jalr, MATCH_JALR, MASK_JALR)
DECLARE_INSN(jal, MATCH_JAL, MASK_JAL)
DECLARE_INSN(c_jr, MATCH_C_JR, MASK_C_JR)
DECLARE_INSN(c_jalr, MATCH_C_JALR, MASK_C_JALR)
DECLARE_INSN(c_j, MATCH_C_J, MASK_C_J)
DECLARE_INSN(beq, MATCH_BEQ, MASK_BEQ)
DECLARE_INSN(bne, MATCH_BNE, MASK_BNE)
DECLARE_INSN(blt, MATCH_BLT, MASK_BLT)
DECLARE_INSN(bge, MATCH_BGE, MASK_BGE)
DECLARE_INSN(bltu, MATCH_BLTU, MASK_BLTU)
DECLARE_INSN(bgeu, MATCH_BGEU, MASK_BGEU)
DECLARE_INSN(c_beqz, MATCH_C_BEQZ, MASK_C_BEQZ)
DECLARE_INSN(c_bnez, MATCH_C_BNEZ, MASK_C_BNEZ)
DECLARE_INSN(sret, MATCH_SRET, MASK_SRET)

अटल पूर्णांक decode_रेजिस्टर_index(अचिन्हित दीर्घ opcode, पूर्णांक offset)
अणु
	वापस (opcode >> offset) & 0x1F;
पूर्ण

अटल पूर्णांक decode_रेजिस्टर_index_लघु(अचिन्हित दीर्घ opcode, पूर्णांक offset)
अणु
	वापस ((opcode >> offset) & 0x7) + 8;
पूर्ण

/* Calculate the new address क्रम after a step */
अटल पूर्णांक get_step_address(काष्ठा pt_regs *regs, अचिन्हित दीर्घ *next_addr)
अणु
	अचिन्हित दीर्घ pc = regs->epc;
	अचिन्हित दीर्घ *regs_ptr = (अचिन्हित दीर्घ *)regs;
	अचिन्हित पूर्णांक rs1_num, rs2_num;
	पूर्णांक op_code;

	अगर (get_kernel_nofault(op_code, (व्योम *)pc))
		वापस -EINVAL;
	अगर ((op_code & __INSN_LENGTH_MASK) != __INSN_LENGTH_GE_32) अणु
		अगर (is_c_jalr_insn(op_code) || is_c_jr_insn(op_code)) अणु
			rs1_num = decode_रेजिस्टर_index(op_code, RVC_C2_RS1_OPOFF);
			*next_addr = regs_ptr[rs1_num];
		पूर्ण अन्यथा अगर (is_c_j_insn(op_code) || is_c_jal_insn(op_code)) अणु
			*next_addr = EXTRACT_RVC_J_IMM(op_code) + pc;
		पूर्ण अन्यथा अगर (is_c_beqz_insn(op_code)) अणु
			rs1_num = decode_रेजिस्टर_index_लघु(op_code,
							      RVC_C1_RS1_OPOFF);
			अगर (!rs1_num || regs_ptr[rs1_num] == 0)
				*next_addr = EXTRACT_RVC_B_IMM(op_code) + pc;
			अन्यथा
				*next_addr = pc + 2;
		पूर्ण अन्यथा अगर (is_c_bnez_insn(op_code)) अणु
			rs1_num =
			    decode_रेजिस्टर_index_लघु(op_code, RVC_C1_RS1_OPOFF);
			अगर (rs1_num && regs_ptr[rs1_num] != 0)
				*next_addr = EXTRACT_RVC_B_IMM(op_code) + pc;
			अन्यथा
				*next_addr = pc + 2;
		पूर्ण अन्यथा अणु
			*next_addr = pc + 2;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((op_code & __INSN_OPCODE_MASK) == __INSN_BRANCH_OPCODE) अणु
			bool result = false;
			दीर्घ imm = EXTRACT_BTYPE_IMM(op_code);
			अचिन्हित दीर्घ rs1_val = 0, rs2_val = 0;

			rs1_num = decode_रेजिस्टर_index(op_code, RVG_RS1_OPOFF);
			rs2_num = decode_रेजिस्टर_index(op_code, RVG_RS2_OPOFF);
			अगर (rs1_num)
				rs1_val = regs_ptr[rs1_num];
			अगर (rs2_num)
				rs2_val = regs_ptr[rs2_num];

			अगर (is_beq_insn(op_code))
				result = (rs1_val == rs2_val) ? true : false;
			अन्यथा अगर (is_bne_insn(op_code))
				result = (rs1_val != rs2_val) ? true : false;
			अन्यथा अगर (is_blt_insn(op_code))
				result =
				    ((दीर्घ)rs1_val <
				     (दीर्घ)rs2_val) ? true : false;
			अन्यथा अगर (is_bge_insn(op_code))
				result =
				    ((दीर्घ)rs1_val >=
				     (दीर्घ)rs2_val) ? true : false;
			अन्यथा अगर (is_bltu_insn(op_code))
				result = (rs1_val < rs2_val) ? true : false;
			अन्यथा अगर (is_bgeu_insn(op_code))
				result = (rs1_val >= rs2_val) ? true : false;
			अगर (result)
				*next_addr = imm + pc;
			अन्यथा
				*next_addr = pc + 4;
		पूर्ण अन्यथा अगर (is_jal_insn(op_code)) अणु
			*next_addr = EXTRACT_JTYPE_IMM(op_code) + pc;
		पूर्ण अन्यथा अगर (is_jalr_insn(op_code)) अणु
			rs1_num = decode_रेजिस्टर_index(op_code, RVG_RS1_OPOFF);
			अगर (rs1_num)
				*next_addr = ((अचिन्हित दीर्घ *)regs)[rs1_num];
			*next_addr += EXTRACT_ITYPE_IMM(op_code);
		पूर्ण अन्यथा अगर (is_sret_insn(op_code)) अणु
			*next_addr = pc;
		पूर्ण अन्यथा अणु
			*next_addr = pc + 4;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक करो_single_step(काष्ठा pt_regs *regs)
अणु
	/* Determine where the target inकाष्ठाion will send us to */
	अचिन्हित दीर्घ addr = 0;
	पूर्णांक error = get_step_address(regs, &addr);

	अगर (error)
		वापस error;

	/* Store the op code in the stepped address */
	error = get_kernel_nofault(stepped_opcode, (व्योम *)addr);
	अगर (error)
		वापस error;

	stepped_address = addr;

	/* Replace the op code with the अवरोध inकाष्ठाion */
	error = copy_to_kernel_nofault((व्योम *)stepped_address,
				   arch_kgdb_ops.gdb_bpt_instr,
				   BREAK_INSTR_SIZE);
	/* Flush and वापस */
	अगर (!error) अणु
		flush_icache_range(addr, addr + BREAK_INSTR_SIZE);
		kgdb_single_step = 1;
		atomic_set(&kgdb_cpu_करोing_single_step,
			   raw_smp_processor_id());
	पूर्ण अन्यथा अणु
		stepped_address = 0;
		stepped_opcode = 0;
	पूर्ण
	वापस error;
पूर्ण

/* Unकरो a single step */
अटल व्योम unकरो_single_step(काष्ठा pt_regs *regs)
अणु
	अगर (stepped_opcode != 0) अणु
		copy_to_kernel_nofault((व्योम *)stepped_address,
				   (व्योम *)&stepped_opcode, BREAK_INSTR_SIZE);
		flush_icache_range(stepped_address,
				   stepped_address + BREAK_INSTR_SIZE);
	पूर्ण
	stepped_address = 0;
	stepped_opcode = 0;
	kgdb_single_step = 0;
	atomic_set(&kgdb_cpu_करोing_single_step, -1);
पूर्ण

काष्ठा dbg_reg_def_t dbg_reg_def[DBG_MAX_REG_NUM] = अणु
	अणुDBG_REG_ZERO, GDB_SIZखातापूर्ण_REG, -1पूर्ण,
	अणुDBG_REG_RA, GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, ra)पूर्ण,
	अणुDBG_REG_SP, GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, sp)पूर्ण,
	अणुDBG_REG_GP, GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, gp)पूर्ण,
	अणुDBG_REG_TP, GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, tp)पूर्ण,
	अणुDBG_REG_T0, GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, t0)पूर्ण,
	अणुDBG_REG_T1, GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, t1)पूर्ण,
	अणुDBG_REG_T2, GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, t2)पूर्ण,
	अणुDBG_REG_FP, GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, s0)पूर्ण,
	अणुDBG_REG_S1, GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, a1)पूर्ण,
	अणुDBG_REG_A0, GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, a0)पूर्ण,
	अणुDBG_REG_A1, GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, a1)पूर्ण,
	अणुDBG_REG_A2, GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, a2)पूर्ण,
	अणुDBG_REG_A3, GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, a3)पूर्ण,
	अणुDBG_REG_A4, GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, a4)पूर्ण,
	अणुDBG_REG_A5, GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, a5)पूर्ण,
	अणुDBG_REG_A6, GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, a6)पूर्ण,
	अणुDBG_REG_A7, GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, a7)पूर्ण,
	अणुDBG_REG_S2, GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, s2)पूर्ण,
	अणुDBG_REG_S3, GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, s3)पूर्ण,
	अणुDBG_REG_S4, GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, s4)पूर्ण,
	अणुDBG_REG_S5, GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, s5)पूर्ण,
	अणुDBG_REG_S6, GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, s6)पूर्ण,
	अणुDBG_REG_S7, GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, s7)पूर्ण,
	अणुDBG_REG_S8, GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, s8)पूर्ण,
	अणुDBG_REG_S9, GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, s9)पूर्ण,
	अणुDBG_REG_S10, GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, s10)पूर्ण,
	अणुDBG_REG_S11, GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, s11)पूर्ण,
	अणुDBG_REG_T3, GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, t3)पूर्ण,
	अणुDBG_REG_T4, GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, t4)पूर्ण,
	अणुDBG_REG_T5, GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, t5)पूर्ण,
	अणुDBG_REG_T6, GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, t6)पूर्ण,
	अणुDBG_REG_EPC, GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, epc)पूर्ण,
	अणुDBG_REG_STATUS, GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, status)पूर्ण,
	अणुDBG_REG_BADADDR, GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, badaddr)पूर्ण,
	अणुDBG_REG_CAUSE, GDB_SIZखातापूर्ण_REG, दुरत्व(काष्ठा pt_regs, cause)पूर्ण,
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

व्योम
sleeping_thपढ़ो_to_gdb_regs(अचिन्हित दीर्घ *gdb_regs, काष्ठा task_काष्ठा *task)
अणु
	/* Initialize to zero */
	स_रखो((अक्षर *)gdb_regs, 0, NUMREGBYTES);

	gdb_regs[DBG_REG_SP_OFF] = task->thपढ़ो.sp;
	gdb_regs[DBG_REG_FP_OFF] = task->thपढ़ो.s[0];
	gdb_regs[DBG_REG_S1_OFF] = task->thपढ़ो.s[1];
	gdb_regs[DBG_REG_S2_OFF] = task->thपढ़ो.s[2];
	gdb_regs[DBG_REG_S3_OFF] = task->thपढ़ो.s[3];
	gdb_regs[DBG_REG_S4_OFF] = task->thपढ़ो.s[4];
	gdb_regs[DBG_REG_S5_OFF] = task->thपढ़ो.s[5];
	gdb_regs[DBG_REG_S6_OFF] = task->thपढ़ो.s[6];
	gdb_regs[DBG_REG_S7_OFF] = task->thपढ़ो.s[7];
	gdb_regs[DBG_REG_S8_OFF] = task->thपढ़ो.s[8];
	gdb_regs[DBG_REG_S9_OFF] = task->thपढ़ो.s[10];
	gdb_regs[DBG_REG_S10_OFF] = task->thपढ़ो.s[11];
	gdb_regs[DBG_REG_EPC_OFF] = task->thपढ़ो.ra;
पूर्ण

व्योम kgdb_arch_set_pc(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc)
अणु
	regs->epc = pc;
पूर्ण

व्योम kgdb_arch_handle_qxfer_pkt(अक्षर *remcom_in_buffer,
				अक्षर *remcom_out_buffer)
अणु
	अगर (!म_भेदन(remcom_in_buffer, gdb_xfer_पढ़ो_target,
		     माप(gdb_xfer_पढ़ो_target)))
		म_नकल(remcom_out_buffer, riscv_gdb_stub_target_desc);
	अन्यथा अगर (!म_भेदन(remcom_in_buffer, gdb_xfer_पढ़ो_cpuxml,
			  माप(gdb_xfer_पढ़ो_cpuxml)))
		म_नकल(remcom_out_buffer, riscv_gdb_stub_cpuxml);
पूर्ण

अटल अंतरभूत व्योम kgdb_arch_update_addr(काष्ठा pt_regs *regs,
					 अक्षर *remcom_in_buffer)
अणु
	अचिन्हित दीर्घ addr;
	अक्षर *ptr;

	ptr = &remcom_in_buffer[1];
	अगर (kgdb_hex2दीर्घ(&ptr, &addr))
		regs->epc = addr;
पूर्ण

पूर्णांक kgdb_arch_handle_exception(पूर्णांक vector, पूर्णांक signo, पूर्णांक err_code,
			       अक्षर *remcom_in_buffer, अक्षर *remcom_out_buffer,
			       काष्ठा pt_regs *regs)
अणु
	पूर्णांक err = 0;

	unकरो_single_step(regs);

	चयन (remcom_in_buffer[0]) अणु
	हाल 'c':
	हाल 'D':
	हाल 'k':
		अगर (remcom_in_buffer[0] == 'c')
			kgdb_arch_update_addr(regs, remcom_in_buffer);
		अवरोध;
	हाल 's':
		kgdb_arch_update_addr(regs, remcom_in_buffer);
		err = करो_single_step(regs);
		अवरोध;
	शेष:
		err = -1;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक kgdb_riscv_kgdbअवरोध(अचिन्हित दीर्घ addr)
अणु
	अगर (stepped_address == addr)
		वापस KGDB_SW_SINGLE_STEP;
	अगर (atomic_पढ़ो(&kgdb_setting_अवरोधpoपूर्णांक))
		अगर (addr == (अचिन्हित दीर्घ)&kgdb_compiled_अवरोध)
			वापस KGDB_COMPILED_BREAK;

	वापस kgdb_has_hit_अवरोध(addr);
पूर्ण

अटल पूर्णांक kgdb_riscv_notअगरy(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ cmd,
			     व्योम *ptr)
अणु
	काष्ठा die_args *args = (काष्ठा die_args *)ptr;
	काष्ठा pt_regs *regs = args->regs;
	अचिन्हित दीर्घ flags;
	पूर्णांक type;

	अगर (user_mode(regs))
		वापस NOTIFY_DONE;

	type = kgdb_riscv_kgdbअवरोध(regs->epc);
	अगर (type == NOT_KGDB_BREAK && cmd == DIE_TRAP)
		वापस NOTIFY_DONE;

	local_irq_save(flags);

	अगर (kgdb_handle_exception(type == KGDB_SW_SINGLE_STEP ? 0 : 1,
				  args->signr, cmd, regs))
		वापस NOTIFY_DONE;

	अगर (type == KGDB_COMPILED_BREAK)
		regs->epc += 4;

	local_irq_restore(flags);

	वापस NOTIFY_STOP;
पूर्ण

अटल काष्ठा notअगरier_block kgdb_notअगरier = अणु
	.notअगरier_call = kgdb_riscv_notअगरy,
पूर्ण;

पूर्णांक kgdb_arch_init(व्योम)
अणु
	रेजिस्टर_die_notअगरier(&kgdb_notअगरier);

	वापस 0;
पूर्ण

व्योम kgdb_arch_निकास(व्योम)
अणु
	unरेजिस्टर_die_notअगरier(&kgdb_notअगरier);
पूर्ण

/*
 * Global data
 */
#अगर_घोषित CONFIG_RISCV_ISA_C
स्थिर काष्ठा kgdb_arch arch_kgdb_ops = अणु
	.gdb_bpt_instr = अणु0x02, 0x90पूर्ण,	/* c.eअवरोध */
पूर्ण;
#अन्यथा
स्थिर काष्ठा kgdb_arch arch_kgdb_ops = अणु
	.gdb_bpt_instr = अणु0x73, 0x00, 0x10, 0x00पूर्ण,	/* eअवरोध */
पूर्ण;
#पूर्ण_अगर
