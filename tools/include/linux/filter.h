<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Linux Socket Filter Data Structures
 */
#अगर_अघोषित __TOOLS_LINUX_FILTER_H
#घोषणा __TOOLS_LINUX_FILTER_H

#समावेश <linux/bpf.h>

/* ArgX, context and stack frame poपूर्णांकer रेजिस्टर positions. Note,
 * Arg1, Arg2, Arg3, etc are used as argument mappings of function
 * calls in BPF_CALL inकाष्ठाion.
 */
#घोषणा BPF_REG_ARG1	BPF_REG_1
#घोषणा BPF_REG_ARG2	BPF_REG_2
#घोषणा BPF_REG_ARG3	BPF_REG_3
#घोषणा BPF_REG_ARG4	BPF_REG_4
#घोषणा BPF_REG_ARG5	BPF_REG_5
#घोषणा BPF_REG_CTX	BPF_REG_6
#घोषणा BPF_REG_FP	BPF_REG_10

/* Additional रेजिस्टर mappings क्रम converted user programs. */
#घोषणा BPF_REG_A	BPF_REG_0
#घोषणा BPF_REG_X	BPF_REG_7
#घोषणा BPF_REG_TMP	BPF_REG_8

/* BPF program can access up to 512 bytes of stack space. */
#घोषणा MAX_BPF_STACK	512

/* Helper macros क्रम filter block array initializers. */

/* ALU ops on रेजिस्टरs, bpf_add|sub|...: dst_reg += src_reg */

#घोषणा BPF_ALU64_REG(OP, DST, SRC)				\
	((काष्ठा bpf_insn) अणु					\
		.code  = BPF_ALU64 | BPF_OP(OP) | BPF_X,	\
		.dst_reg = DST,					\
		.src_reg = SRC,					\
		.off   = 0,					\
		.imm   = 0 पूर्ण)

#घोषणा BPF_ALU32_REG(OP, DST, SRC)				\
	((काष्ठा bpf_insn) अणु					\
		.code  = BPF_ALU | BPF_OP(OP) | BPF_X,		\
		.dst_reg = DST,					\
		.src_reg = SRC,					\
		.off   = 0,					\
		.imm   = 0 पूर्ण)

/* ALU ops on immediates, bpf_add|sub|...: dst_reg += imm32 */

#घोषणा BPF_ALU64_IMM(OP, DST, IMM)				\
	((काष्ठा bpf_insn) अणु					\
		.code  = BPF_ALU64 | BPF_OP(OP) | BPF_K,	\
		.dst_reg = DST,					\
		.src_reg = 0,					\
		.off   = 0,					\
		.imm   = IMM पूर्ण)

#घोषणा BPF_ALU32_IMM(OP, DST, IMM)				\
	((काष्ठा bpf_insn) अणु					\
		.code  = BPF_ALU | BPF_OP(OP) | BPF_K,		\
		.dst_reg = DST,					\
		.src_reg = 0,					\
		.off   = 0,					\
		.imm   = IMM पूर्ण)

/* Endianess conversion, cpu_to_अणुl,bपूर्णe(), अणुl,bपूर्णe_to_cpu() */

#घोषणा BPF_ENDIAN(TYPE, DST, LEN)				\
	((काष्ठा bpf_insn) अणु					\
		.code  = BPF_ALU | BPF_END | BPF_SRC(TYPE),	\
		.dst_reg = DST,					\
		.src_reg = 0,					\
		.off   = 0,					\
		.imm   = LEN पूर्ण)

/* Short क्रमm of mov, dst_reg = src_reg */

#घोषणा BPF_MOV64_REG(DST, SRC)					\
	((काष्ठा bpf_insn) अणु					\
		.code  = BPF_ALU64 | BPF_MOV | BPF_X,		\
		.dst_reg = DST,					\
		.src_reg = SRC,					\
		.off   = 0,					\
		.imm   = 0 पूर्ण)

#घोषणा BPF_MOV32_REG(DST, SRC)					\
	((काष्ठा bpf_insn) अणु					\
		.code  = BPF_ALU | BPF_MOV | BPF_X,		\
		.dst_reg = DST,					\
		.src_reg = SRC,					\
		.off   = 0,					\
		.imm   = 0 पूर्ण)

/* Short क्रमm of mov, dst_reg = imm32 */

#घोषणा BPF_MOV64_IMM(DST, IMM)					\
	((काष्ठा bpf_insn) अणु					\
		.code  = BPF_ALU64 | BPF_MOV | BPF_K,		\
		.dst_reg = DST,					\
		.src_reg = 0,					\
		.off   = 0,					\
		.imm   = IMM पूर्ण)

#घोषणा BPF_MOV32_IMM(DST, IMM)					\
	((काष्ठा bpf_insn) अणु					\
		.code  = BPF_ALU | BPF_MOV | BPF_K,		\
		.dst_reg = DST,					\
		.src_reg = 0,					\
		.off   = 0,					\
		.imm   = IMM पूर्ण)

/* Short क्रमm of mov based on type,  BPF_X: dst_reg = src_reg, BPF_K: dst_reg = imm32 */

#घोषणा BPF_MOV64_RAW(TYPE, DST, SRC, IMM)			\
	((काष्ठा bpf_insn) अणु					\
		.code  = BPF_ALU64 | BPF_MOV | BPF_SRC(TYPE),	\
		.dst_reg = DST,					\
		.src_reg = SRC,					\
		.off   = 0,					\
		.imm   = IMM पूर्ण)

#घोषणा BPF_MOV32_RAW(TYPE, DST, SRC, IMM)			\
	((काष्ठा bpf_insn) अणु					\
		.code  = BPF_ALU | BPF_MOV | BPF_SRC(TYPE),	\
		.dst_reg = DST,					\
		.src_reg = SRC,					\
		.off   = 0,					\
		.imm   = IMM पूर्ण)

/* Direct packet access, R0 = *(uपूर्णांक *) (skb->data + imm32) */

#घोषणा BPF_LD_ABS(SIZE, IMM)					\
	((काष्ठा bpf_insn) अणु					\
		.code  = BPF_LD | BPF_SIZE(SIZE) | BPF_ABS,	\
		.dst_reg = 0,					\
		.src_reg = 0,					\
		.off   = 0,					\
		.imm   = IMM पूर्ण)

/* Indirect packet access, R0 = *(uपूर्णांक *) (skb->data + src_reg + imm32) */

#घोषणा BPF_LD_IND(SIZE, SRC, IMM)				\
	((काष्ठा bpf_insn) अणु					\
		.code  = BPF_LD | BPF_SIZE(SIZE) | BPF_IND,	\
		.dst_reg = 0,					\
		.src_reg = SRC,					\
		.off   = 0,					\
		.imm   = IMM पूर्ण)

/* Memory load, dst_reg = *(uपूर्णांक *) (src_reg + off16) */

#घोषणा BPF_LDX_MEM(SIZE, DST, SRC, OFF)			\
	((काष्ठा bpf_insn) अणु					\
		.code  = BPF_LDX | BPF_SIZE(SIZE) | BPF_MEM,	\
		.dst_reg = DST,					\
		.src_reg = SRC,					\
		.off   = OFF,					\
		.imm   = 0 पूर्ण)

/* Memory store, *(uपूर्णांक *) (dst_reg + off16) = src_reg */

#घोषणा BPF_STX_MEM(SIZE, DST, SRC, OFF)			\
	((काष्ठा bpf_insn) अणु					\
		.code  = BPF_STX | BPF_SIZE(SIZE) | BPF_MEM,	\
		.dst_reg = DST,					\
		.src_reg = SRC,					\
		.off   = OFF,					\
		.imm   = 0 पूर्ण)

/*
 * Atomic operations:
 *
 *   BPF_ADD                  *(uपूर्णांक *) (dst_reg + off16) += src_reg
 *   BPF_AND                  *(uपूर्णांक *) (dst_reg + off16) &= src_reg
 *   BPF_OR                   *(uपूर्णांक *) (dst_reg + off16) |= src_reg
 *   BPF_XOR                  *(uपूर्णांक *) (dst_reg + off16) ^= src_reg
 *   BPF_ADD | BPF_FETCH      src_reg = atomic_fetch_add(dst_reg + off16, src_reg);
 *   BPF_AND | BPF_FETCH      src_reg = atomic_fetch_and(dst_reg + off16, src_reg);
 *   BPF_OR | BPF_FETCH       src_reg = atomic_fetch_or(dst_reg + off16, src_reg);
 *   BPF_XOR | BPF_FETCH      src_reg = atomic_fetch_xor(dst_reg + off16, src_reg);
 *   BPF_XCHG                 src_reg = atomic_xchg(dst_reg + off16, src_reg)
 *   BPF_CMPXCHG              r0 = atomic_cmpxchg(dst_reg + off16, r0, src_reg)
 */

#घोषणा BPF_ATOMIC_OP(SIZE, OP, DST, SRC, OFF)			\
	((काष्ठा bpf_insn) अणु					\
		.code  = BPF_STX | BPF_SIZE(SIZE) | BPF_ATOMIC,	\
		.dst_reg = DST,					\
		.src_reg = SRC,					\
		.off   = OFF,					\
		.imm   = OP पूर्ण)

/* Legacy alias */
#घोषणा BPF_STX_XADD(SIZE, DST, SRC, OFF) BPF_ATOMIC_OP(SIZE, BPF_ADD, DST, SRC, OFF)

/* Memory store, *(uपूर्णांक *) (dst_reg + off16) = imm32 */

#घोषणा BPF_ST_MEM(SIZE, DST, OFF, IMM)				\
	((काष्ठा bpf_insn) अणु					\
		.code  = BPF_ST | BPF_SIZE(SIZE) | BPF_MEM,	\
		.dst_reg = DST,					\
		.src_reg = 0,					\
		.off   = OFF,					\
		.imm   = IMM पूर्ण)

/* Conditional jumps against रेजिस्टरs, अगर (dst_reg 'op' src_reg) जाओ pc + off16 */

#घोषणा BPF_JMP_REG(OP, DST, SRC, OFF)				\
	((काष्ठा bpf_insn) अणु					\
		.code  = BPF_JMP | BPF_OP(OP) | BPF_X,		\
		.dst_reg = DST,					\
		.src_reg = SRC,					\
		.off   = OFF,					\
		.imm   = 0 पूर्ण)

/* Like BPF_JMP_REG, but with 32-bit wide opeअक्रमs क्रम comparison. */

#घोषणा BPF_JMP32_REG(OP, DST, SRC, OFF)			\
	((काष्ठा bpf_insn) अणु					\
		.code  = BPF_JMP32 | BPF_OP(OP) | BPF_X,	\
		.dst_reg = DST,					\
		.src_reg = SRC,					\
		.off   = OFF,					\
		.imm   = 0 पूर्ण)

/* Conditional jumps against immediates, अगर (dst_reg 'op' imm32) जाओ pc + off16 */

#घोषणा BPF_JMP_IMM(OP, DST, IMM, OFF)				\
	((काष्ठा bpf_insn) अणु					\
		.code  = BPF_JMP | BPF_OP(OP) | BPF_K,		\
		.dst_reg = DST,					\
		.src_reg = 0,					\
		.off   = OFF,					\
		.imm   = IMM पूर्ण)

/* Like BPF_JMP_IMM, but with 32-bit wide opeअक्रमs क्रम comparison. */

#घोषणा BPF_JMP32_IMM(OP, DST, IMM, OFF)			\
	((काष्ठा bpf_insn) अणु					\
		.code  = BPF_JMP32 | BPF_OP(OP) | BPF_K,	\
		.dst_reg = DST,					\
		.src_reg = 0,					\
		.off   = OFF,					\
		.imm   = IMM पूर्ण)

/* Unconditional jumps, जाओ pc + off16 */

#घोषणा BPF_JMP_A(OFF)						\
	((काष्ठा bpf_insn) अणु					\
		.code  = BPF_JMP | BPF_JA,			\
		.dst_reg = 0,					\
		.src_reg = 0,					\
		.off   = OFF,					\
		.imm   = 0 पूर्ण)

/* Function call */

#घोषणा BPF_EMIT_CALL(FUNC)					\
	((काष्ठा bpf_insn) अणु					\
		.code  = BPF_JMP | BPF_CALL,			\
		.dst_reg = 0,					\
		.src_reg = 0,					\
		.off   = 0,					\
		.imm   = ((FUNC) - BPF_FUNC_unspec) पूर्ण)

/* Raw code statement block */

#घोषणा BPF_RAW_INSN(CODE, DST, SRC, OFF, IMM)			\
	((काष्ठा bpf_insn) अणु					\
		.code  = CODE,					\
		.dst_reg = DST,					\
		.src_reg = SRC,					\
		.off   = OFF,					\
		.imm   = IMM पूर्ण)

/* BPF_LD_IMM64 macro encodes single 'load 64-bit immediate' insn */

#घोषणा BPF_LD_IMM64(DST, IMM)					\
	BPF_LD_IMM64_RAW(DST, 0, IMM)

#घोषणा BPF_LD_IMM64_RAW(DST, SRC, IMM)				\
	((काष्ठा bpf_insn) अणु					\
		.code  = BPF_LD | BPF_DW | BPF_IMM,		\
		.dst_reg = DST,					\
		.src_reg = SRC,					\
		.off   = 0,					\
		.imm   = (__u32) (IMM) पूर्ण),			\
	((काष्ठा bpf_insn) अणु					\
		.code  = 0, /* zero is reserved opcode */	\
		.dst_reg = 0,					\
		.src_reg = 0,					\
		.off   = 0,					\
		.imm   = ((__u64) (IMM)) >> 32 पूर्ण)

#घोषणा BPF_LD_IMM64_RAW_FULL(DST, SRC, OFF1, OFF2, IMM1, IMM2)	\
	((काष्ठा bpf_insn) अणु					\
		.code  = BPF_LD | BPF_DW | BPF_IMM,		\
		.dst_reg = DST,					\
		.src_reg = SRC,					\
		.off   = OFF1,					\
		.imm   = IMM1 पूर्ण),				\
	((काष्ठा bpf_insn) अणु					\
		.code  = 0, /* zero is reserved opcode */	\
		.dst_reg = 0,					\
		.src_reg = 0,					\
		.off   = OFF2,					\
		.imm   = IMM2 पूर्ण)

/* pseuकरो BPF_LD_IMM64 insn used to refer to process-local map_fd */

#घोषणा BPF_LD_MAP_FD(DST, MAP_FD)				\
	BPF_LD_IMM64_RAW_FULL(DST, BPF_PSEUDO_MAP_FD, 0, 0,	\
			      MAP_FD, 0)

#घोषणा BPF_LD_MAP_VALUE(DST, MAP_FD, VALUE_OFF)		\
	BPF_LD_IMM64_RAW_FULL(DST, BPF_PSEUDO_MAP_VALUE, 0, 0,	\
			      MAP_FD, VALUE_OFF)

/* Relative call */

#घोषणा BPF_CALL_REL(TGT)					\
	((काष्ठा bpf_insn) अणु					\
		.code  = BPF_JMP | BPF_CALL,			\
		.dst_reg = 0,					\
		.src_reg = BPF_PSEUDO_CALL,			\
		.off   = 0,					\
		.imm   = TGT पूर्ण)

/* Program निकास */

#घोषणा BPF_EXIT_INSN()						\
	((काष्ठा bpf_insn) अणु					\
		.code  = BPF_JMP | BPF_EXIT,			\
		.dst_reg = 0,					\
		.src_reg = 0,					\
		.off   = 0,					\
		.imm   = 0 पूर्ण)

#पूर्ण_अगर /* __TOOLS_LINUX_FILTER_H */
