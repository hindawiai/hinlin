<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */

#अगर_अघोषित __ASM_KGDB_H_
#घोषणा __ASM_KGDB_H_

#अगर_घोषित __KERNEL__

#घोषणा GDB_SIZखातापूर्ण_REG माप(अचिन्हित दीर्घ)

#घोषणा DBG_MAX_REG_NUM (36)
#घोषणा NUMREGBYTES ((DBG_MAX_REG_NUM) * GDB_SIZखातापूर्ण_REG)
#घोषणा CACHE_FLUSH_IS_SAFE     1
#घोषणा BUFMAX                  2048
#अगर_घोषित CONFIG_RISCV_ISA_C
#घोषणा BREAK_INSTR_SIZE	2
#अन्यथा
#घोषणा BREAK_INSTR_SIZE	4
#पूर्ण_अगर

#अगर_अघोषित	__ASSEMBLY__

बाह्य अचिन्हित दीर्घ kgdb_compiled_अवरोध;

अटल अंतरभूत व्योम arch_kgdb_अवरोधpoपूर्णांक(व्योम)
अणु
	यंत्र(".global kgdb_compiled_break\n"
	    ".option norvc\n"
	    "kgdb_compiled_break: ebreak\n"
	    ".option rvc\n");
पूर्ण

#पूर्ण_अगर /* !__ASSEMBLY__ */

#घोषणा DBG_REG_ZERO "zero"
#घोषणा DBG_REG_RA "ra"
#घोषणा DBG_REG_SP "sp"
#घोषणा DBG_REG_GP "gp"
#घोषणा DBG_REG_TP "tp"
#घोषणा DBG_REG_T0 "t0"
#घोषणा DBG_REG_T1 "t1"
#घोषणा DBG_REG_T2 "t2"
#घोषणा DBG_REG_FP "fp"
#घोषणा DBG_REG_S1 "s1"
#घोषणा DBG_REG_A0 "a0"
#घोषणा DBG_REG_A1 "a1"
#घोषणा DBG_REG_A2 "a2"
#घोषणा DBG_REG_A3 "a3"
#घोषणा DBG_REG_A4 "a4"
#घोषणा DBG_REG_A5 "a5"
#घोषणा DBG_REG_A6 "a6"
#घोषणा DBG_REG_A7 "a7"
#घोषणा DBG_REG_S2 "s2"
#घोषणा DBG_REG_S3 "s3"
#घोषणा DBG_REG_S4 "s4"
#घोषणा DBG_REG_S5 "s5"
#घोषणा DBG_REG_S6 "s6"
#घोषणा DBG_REG_S7 "s7"
#घोषणा DBG_REG_S8 "s8"
#घोषणा DBG_REG_S9 "s9"
#घोषणा DBG_REG_S10 "s10"
#घोषणा DBG_REG_S11 "s11"
#घोषणा DBG_REG_T3 "t3"
#घोषणा DBG_REG_T4 "t4"
#घोषणा DBG_REG_T5 "t5"
#घोषणा DBG_REG_T6 "t6"
#घोषणा DBG_REG_EPC "pc"
#घोषणा DBG_REG_STATUS "sstatus"
#घोषणा DBG_REG_BADADDR "stval"
#घोषणा DBG_REG_CAUSE "scause"

#घोषणा DBG_REG_ZERO_OFF 0
#घोषणा DBG_REG_RA_OFF 1
#घोषणा DBG_REG_SP_OFF 2
#घोषणा DBG_REG_GP_OFF 3
#घोषणा DBG_REG_TP_OFF 4
#घोषणा DBG_REG_T0_OFF 5
#घोषणा DBG_REG_T1_OFF 6
#घोषणा DBG_REG_T2_OFF 7
#घोषणा DBG_REG_FP_OFF 8
#घोषणा DBG_REG_S1_OFF 9
#घोषणा DBG_REG_A0_OFF 10
#घोषणा DBG_REG_A1_OFF 11
#घोषणा DBG_REG_A2_OFF 12
#घोषणा DBG_REG_A3_OFF 13
#घोषणा DBG_REG_A4_OFF 14
#घोषणा DBG_REG_A5_OFF 15
#घोषणा DBG_REG_A6_OFF 16
#घोषणा DBG_REG_A7_OFF 17
#घोषणा DBG_REG_S2_OFF 18
#घोषणा DBG_REG_S3_OFF 19
#घोषणा DBG_REG_S4_OFF 20
#घोषणा DBG_REG_S5_OFF 21
#घोषणा DBG_REG_S6_OFF 22
#घोषणा DBG_REG_S7_OFF 23
#घोषणा DBG_REG_S8_OFF 24
#घोषणा DBG_REG_S9_OFF 25
#घोषणा DBG_REG_S10_OFF 26
#घोषणा DBG_REG_S11_OFF 27
#घोषणा DBG_REG_T3_OFF 28
#घोषणा DBG_REG_T4_OFF 29
#घोषणा DBG_REG_T5_OFF 30
#घोषणा DBG_REG_T6_OFF 31
#घोषणा DBG_REG_EPC_OFF 32
#घोषणा DBG_REG_STATUS_OFF 33
#घोषणा DBG_REG_BADADDR_OFF 34
#घोषणा DBG_REG_CAUSE_OFF 35

बाह्य स्थिर अक्षर riscv_gdb_stub_feature[64];

#घोषणा kgdb_arch_gdb_stub_feature riscv_gdb_stub_feature

#पूर्ण_अगर
#पूर्ण_अगर
