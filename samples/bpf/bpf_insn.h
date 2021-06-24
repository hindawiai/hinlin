<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* eBPF inकाष्ठाion mini library */
#अगर_अघोषित __BPF_INSN_H
#घोषणा __BPF_INSN_H

काष्ठा bpf_insn;

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

#अगर_अघोषित BPF_PSEUDO_MAP_FD
# define BPF_PSEUDO_MAP_FD	1
#पूर्ण_अगर

/* pseuकरो BPF_LD_IMM64 insn used to refer to process-local map_fd */
#घोषणा BPF_LD_MAP_FD(DST, MAP_FD)				\
	BPF_LD_IMM64_RAW(DST, BPF_PSEUDO_MAP_FD, MAP_FD)


/* Direct packet access, R0 = *(uपूर्णांक *) (skb->data + imm32) */

#घोषणा BPF_LD_ABS(SIZE, IMM)					\
	((काष्ठा bpf_insn) अणु					\
		.code  = BPF_LD | BPF_SIZE(SIZE) | BPF_ABS,	\
		.dst_reg = 0,					\
		.src_reg = 0,					\
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

/* Raw code statement block */

#घोषणा BPF_RAW_INSN(CODE, DST, SRC, OFF, IMM)			\
	((काष्ठा bpf_insn) अणु					\
		.code  = CODE,					\
		.dst_reg = DST,					\
		.src_reg = SRC,					\
		.off   = OFF,					\
		.imm   = IMM पूर्ण)

/* Program निकास */

#घोषणा BPF_EXIT_INSN()						\
	((काष्ठा bpf_insn) अणु					\
		.code  = BPF_JMP | BPF_EXIT,			\
		.dst_reg = 0,					\
		.src_reg = 0,					\
		.off   = 0,					\
		.imm   = 0 पूर्ण)

#पूर्ण_अगर
