<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Linux Socket Filter Data Structures
 */
#अगर_अघोषित __LINUX_FILTER_H__
#घोषणा __LINUX_FILTER_H__

#समावेश <मानकतर्क.स>

#समावेश <linux/atomic.h>
#समावेश <linux/refcount.h>
#समावेश <linux/compat.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/linkage.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/sched.h>
#समावेश <linux/capability.h>
#समावेश <linux/set_memory.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/sockptr.h>
#समावेश <crypto/sha1.h>
#समावेश <linux/u64_stats_sync.h>

#समावेश <net/sch_generic.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <uapi/linux/filter.h>
#समावेश <uapi/linux/bpf.h>

काष्ठा sk_buff;
काष्ठा sock;
काष्ठा seccomp_data;
काष्ठा bpf_prog_aux;
काष्ठा xdp_rxq_info;
काष्ठा xdp_buff;
काष्ठा sock_reuseport;
काष्ठा ctl_table;
काष्ठा ctl_table_header;

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
#घोषणा BPF_REG_TMP	BPF_REG_2	/* scratch reg */
#घोषणा BPF_REG_D	BPF_REG_8	/* data, callee-saved */
#घोषणा BPF_REG_H	BPF_REG_9	/* hlen, callee-saved */

/* Kernel hidden auxiliary/helper रेजिस्टर. */
#घोषणा BPF_REG_AX		MAX_BPF_REG
#घोषणा MAX_BPF_EXT_REG		(MAX_BPF_REG + 1)
#घोषणा MAX_BPF_JIT_REG		MAX_BPF_EXT_REG

/* unused opcode to mark special call to bpf_tail_call() helper */
#घोषणा BPF_TAIL_CALL	0xf0

/* unused opcode to mark special load inकाष्ठाion. Same as BPF_ABS */
#घोषणा BPF_PROBE_MEM	0x20

/* unused opcode to mark call to पूर्णांकerpreter with arguments */
#घोषणा BPF_CALL_ARGS	0xe0

/* As per nm, we expose JITed images as text (code) section क्रम
 * kallsyms. That way, tools like perf can find it to match
 * addresses.
 */
#घोषणा BPF_SYM_ELF_TYPE	't'

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

/* Special क्रमm of mov32, used क्रम करोing explicit zero extension on dst. */
#घोषणा BPF_ZEXT_REG(DST)					\
	((काष्ठा bpf_insn) अणु					\
		.code  = BPF_ALU | BPF_MOV | BPF_X,		\
		.dst_reg = DST,					\
		.src_reg = DST,					\
		.off   = 0,					\
		.imm   = 1 पूर्ण)

अटल अंतरभूत bool insn_is_zext(स्थिर काष्ठा bpf_insn *insn)
अणु
	वापस insn->code == (BPF_ALU | BPF_MOV | BPF_X) && insn->imm == 1;
पूर्ण

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

/* pseuकरो BPF_LD_IMM64 insn used to refer to process-local map_fd */
#घोषणा BPF_LD_MAP_FD(DST, MAP_FD)				\
	BPF_LD_IMM64_RAW(DST, BPF_PSEUDO_MAP_FD, MAP_FD)

/* Short क्रमm of mov based on type, BPF_X: dst_reg = src_reg, BPF_K: dst_reg = imm32 */

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

/* Conditional jumps against immediates, अगर (dst_reg 'op' imm32) जाओ pc + off16 */

#घोषणा BPF_JMP_IMM(OP, DST, IMM, OFF)				\
	((काष्ठा bpf_insn) अणु					\
		.code  = BPF_JMP | BPF_OP(OP) | BPF_K,		\
		.dst_reg = DST,					\
		.src_reg = 0,					\
		.off   = OFF,					\
		.imm   = IMM पूर्ण)

/* Like BPF_JMP_REG, but with 32-bit wide opeअक्रमs क्रम comparison. */

#घोषणा BPF_JMP32_REG(OP, DST, SRC, OFF)			\
	((काष्ठा bpf_insn) अणु					\
		.code  = BPF_JMP32 | BPF_OP(OP) | BPF_X,	\
		.dst_reg = DST,					\
		.src_reg = SRC,					\
		.off   = OFF,					\
		.imm   = 0 पूर्ण)

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

/* Relative call */

#घोषणा BPF_CALL_REL(TGT)					\
	((काष्ठा bpf_insn) अणु					\
		.code  = BPF_JMP | BPF_CALL,			\
		.dst_reg = 0,					\
		.src_reg = BPF_PSEUDO_CALL,			\
		.off   = 0,					\
		.imm   = TGT पूर्ण)

/* Function call */

#घोषणा BPF_CAST_CALL(x)					\
		((u64 (*)(u64, u64, u64, u64, u64))(x))

#घोषणा BPF_EMIT_CALL(FUNC)					\
	((काष्ठा bpf_insn) अणु					\
		.code  = BPF_JMP | BPF_CALL,			\
		.dst_reg = 0,					\
		.src_reg = 0,					\
		.off   = 0,					\
		.imm   = ((FUNC) - __bpf_call_base) पूर्ण)

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

/* Internal classic blocks क्रम direct assignment */

#घोषणा __BPF_STMT(CODE, K)					\
	((काष्ठा sock_filter) BPF_STMT(CODE, K))

#घोषणा __BPF_JUMP(CODE, K, JT, JF)				\
	((काष्ठा sock_filter) BPF_JUMP(CODE, K, JT, JF))

#घोषणा bytes_to_bpf_size(bytes)				\
(अणु								\
	पूर्णांक bpf_size = -EINVAL;					\
								\
	अगर (bytes == माप(u8))				\
		bpf_size = BPF_B;				\
	अन्यथा अगर (bytes == माप(u16))				\
		bpf_size = BPF_H;				\
	अन्यथा अगर (bytes == माप(u32))				\
		bpf_size = BPF_W;				\
	अन्यथा अगर (bytes == माप(u64))				\
		bpf_size = BPF_DW;				\
								\
	bpf_size;						\
पूर्ण)

#घोषणा bpf_माप_प्रकारo_bytes(bpf_size)				\
(अणु								\
	पूर्णांक bytes = -EINVAL;					\
								\
	अगर (bpf_size == BPF_B)					\
		bytes = माप(u8);				\
	अन्यथा अगर (bpf_size == BPF_H)				\
		bytes = माप(u16);				\
	अन्यथा अगर (bpf_size == BPF_W)				\
		bytes = माप(u32);				\
	अन्यथा अगर (bpf_size == BPF_DW)				\
		bytes = माप(u64);				\
								\
	bytes;							\
पूर्ण)

#घोषणा BPF_SIZखातापूर्ण(type)					\
	(अणु							\
		स्थिर पूर्णांक __size = bytes_to_bpf_size(माप(type)); \
		BUILD_BUG_ON(__size < 0);			\
		__size;						\
	पूर्ण)

#घोषणा BPF_FIELD_SIZखातापूर्ण(type, field)				\
	(अणु							\
		स्थिर पूर्णांक __size = bytes_to_bpf_size(माप_field(type, field)); \
		BUILD_BUG_ON(__size < 0);			\
		__size;						\
	पूर्ण)

#घोषणा BPF_LDST_BYTES(insn)					\
	(अणु							\
		स्थिर पूर्णांक __size = bpf_माप_प्रकारo_bytes(BPF_SIZE((insn)->code)); \
		WARN_ON(__size < 0);				\
		__size;						\
	पूर्ण)

#घोषणा __BPF_MAP_0(m, v, ...) v
#घोषणा __BPF_MAP_1(m, v, t, a, ...) m(t, a)
#घोषणा __BPF_MAP_2(m, v, t, a, ...) m(t, a), __BPF_MAP_1(m, v, __VA_ARGS__)
#घोषणा __BPF_MAP_3(m, v, t, a, ...) m(t, a), __BPF_MAP_2(m, v, __VA_ARGS__)
#घोषणा __BPF_MAP_4(m, v, t, a, ...) m(t, a), __BPF_MAP_3(m, v, __VA_ARGS__)
#घोषणा __BPF_MAP_5(m, v, t, a, ...) m(t, a), __BPF_MAP_4(m, v, __VA_ARGS__)

#घोषणा __BPF_REG_0(...) __BPF_PAD(5)
#घोषणा __BPF_REG_1(...) __BPF_MAP(1, __VA_ARGS__), __BPF_PAD(4)
#घोषणा __BPF_REG_2(...) __BPF_MAP(2, __VA_ARGS__), __BPF_PAD(3)
#घोषणा __BPF_REG_3(...) __BPF_MAP(3, __VA_ARGS__), __BPF_PAD(2)
#घोषणा __BPF_REG_4(...) __BPF_MAP(4, __VA_ARGS__), __BPF_PAD(1)
#घोषणा __BPF_REG_5(...) __BPF_MAP(5, __VA_ARGS__)

#घोषणा __BPF_MAP(n, ...) __BPF_MAP_##n(__VA_ARGS__)
#घोषणा __BPF_REG(n, ...) __BPF_REG_##n(__VA_ARGS__)

#घोषणा __BPF_CAST(t, a)						       \
	(__क्रमce t)							       \
	(__क्रमce							       \
	 typeof(__builtin_choose_expr(माप(t) == माप(अचिन्हित दीर्घ),      \
				      (अचिन्हित दीर्घ)0, (t)0))) a
#घोषणा __BPF_V व्योम
#घोषणा __BPF_N

#घोषणा __BPF_DECL_ARGS(t, a) t   a
#घोषणा __BPF_DECL_REGS(t, a) u64 a

#घोषणा __BPF_PAD(n)							       \
	__BPF_MAP(n, __BPF_DECL_ARGS, __BPF_N, u64, __ur_1, u64, __ur_2,       \
		  u64, __ur_3, u64, __ur_4, u64, __ur_5)

#घोषणा BPF_CALL_x(x, name, ...)					       \
	अटल __always_अंतरभूत						       \
	u64 ____##name(__BPF_MAP(x, __BPF_DECL_ARGS, __BPF_V, __VA_ARGS__));   \
	प्रकार u64 (*btf_##name)(__BPF_MAP(x, __BPF_DECL_ARGS, __BPF_V, __VA_ARGS__)); \
	u64 name(__BPF_REG(x, __BPF_DECL_REGS, __BPF_N, __VA_ARGS__));	       \
	u64 name(__BPF_REG(x, __BPF_DECL_REGS, __BPF_N, __VA_ARGS__))	       \
	अणु								       \
		वापस ((btf_##name)____##name)(__BPF_MAP(x,__BPF_CAST,__BPF_N,__VA_ARGS__));\
	पूर्ण								       \
	अटल __always_अंतरभूत						       \
	u64 ____##name(__BPF_MAP(x, __BPF_DECL_ARGS, __BPF_V, __VA_ARGS__))

#घोषणा BPF_CALL_0(name, ...)	BPF_CALL_x(0, name, __VA_ARGS__)
#घोषणा BPF_CALL_1(name, ...)	BPF_CALL_x(1, name, __VA_ARGS__)
#घोषणा BPF_CALL_2(name, ...)	BPF_CALL_x(2, name, __VA_ARGS__)
#घोषणा BPF_CALL_3(name, ...)	BPF_CALL_x(3, name, __VA_ARGS__)
#घोषणा BPF_CALL_4(name, ...)	BPF_CALL_x(4, name, __VA_ARGS__)
#घोषणा BPF_CALL_5(name, ...)	BPF_CALL_x(5, name, __VA_ARGS__)

#घोषणा bpf_ctx_range(TYPE, MEMBER)						\
	दुरत्व(TYPE, MEMBER) ... दुरत्वend(TYPE, MEMBER) - 1
#घोषणा bpf_ctx_range_till(TYPE, MEMBER1, MEMBER2)				\
	दुरत्व(TYPE, MEMBER1) ... दुरत्वend(TYPE, MEMBER2) - 1
#अगर BITS_PER_LONG == 64
# define bpf_ctx_range_ptr(TYPE, MEMBER)					\
	दुरत्व(TYPE, MEMBER) ... दुरत्वend(TYPE, MEMBER) - 1
#अन्यथा
# define bpf_ctx_range_ptr(TYPE, MEMBER)					\
	दुरत्व(TYPE, MEMBER) ... दुरत्व(TYPE, MEMBER) + 8 - 1
#पूर्ण_अगर /* BITS_PER_LONG == 64 */

#घोषणा bpf_target_off(TYPE, MEMBER, SIZE, PTR_SIZE)				\
	(अणु									\
		BUILD_BUG_ON(माप_field(TYPE, MEMBER) != (SIZE));		\
		*(PTR_SIZE) = (SIZE);						\
		दुरत्व(TYPE, MEMBER);						\
	पूर्ण)

/* A काष्ठा sock_filter is architecture independent. */
काष्ठा compat_sock_fprog अणु
	u16		len;
	compat_uptr_t	filter;	/* काष्ठा sock_filter * */
पूर्ण;

काष्ठा sock_fprog_kern अणु
	u16			len;
	काष्ठा sock_filter	*filter;
पूर्ण;

/* Some arches need द्विगुनword alignment क्रम their inकाष्ठाions and/or data */
#घोषणा BPF_IMAGE_ALIGNMENT 8

काष्ठा bpf_binary_header अणु
	u32 pages;
	u8 image[] __aligned(BPF_IMAGE_ALIGNMENT);
पूर्ण;

काष्ठा bpf_prog_stats अणु
	u64 cnt;
	u64 nsecs;
	u64 misses;
	काष्ठा u64_stats_sync syncp;
पूर्ण __aligned(2 * माप(u64));

काष्ठा bpf_prog अणु
	u16			pages;		/* Number of allocated pages */
	u16			jited:1,	/* Is our filter JIT'ed? */
				jit_requested:1,/* archs need to JIT the prog */
				gpl_compatible:1, /* Is filter GPL compatible? */
				cb_access:1,	/* Is control block accessed? */
				dst_needed:1,	/* Do we need dst entry? */
				blinded:1,	/* Was blinded */
				is_func:1,	/* program is a bpf function */
				kprobe_override:1, /* Do we override a kprobe? */
				has_callchain_buf:1, /* callchain buffer allocated? */
				enक्रमce_expected_attach_type:1, /* Enक्रमce expected_attach_type checking at attach समय */
				call_get_stack:1; /* Do we call bpf_get_stack() or bpf_get_stackid() */
	क्रमागत bpf_prog_type	type;		/* Type of BPF program */
	क्रमागत bpf_attach_type	expected_attach_type; /* For some prog types */
	u32			len;		/* Number of filter blocks */
	u32			jited_len;	/* Size of jited insns in bytes */
	u8			tag[BPF_TAG_SIZE];
	काष्ठा bpf_prog_stats __percpu *stats;
	पूर्णांक __percpu		*active;
	अचिन्हित पूर्णांक		(*bpf_func)(स्थिर व्योम *ctx,
					    स्थिर काष्ठा bpf_insn *insn);
	काष्ठा bpf_prog_aux	*aux;		/* Auxiliary fields */
	काष्ठा sock_fprog_kern	*orig_prog;	/* Original BPF program */
	/* Inकाष्ठाions क्रम पूर्णांकerpreter */
	काष्ठा sock_filter	insns[0];
	काष्ठा bpf_insn		insnsi[];
पूर्ण;

काष्ठा sk_filter अणु
	refcount_t	refcnt;
	काष्ठा rcu_head	rcu;
	काष्ठा bpf_prog	*prog;
पूर्ण;

DECLARE_STATIC_KEY_FALSE(bpf_stats_enabled_key);

#घोषणा __BPF_PROG_RUN(prog, ctx, dfunc)	(अणु			\
	u32 __ret;							\
	cant_migrate();							\
	अगर (अटल_branch_unlikely(&bpf_stats_enabled_key)) अणु		\
		काष्ठा bpf_prog_stats *__stats;				\
		u64 __start = sched_घड़ी();				\
		__ret = dfunc(ctx, (prog)->insnsi, (prog)->bpf_func);	\
		__stats = this_cpu_ptr(prog->stats);			\
		u64_stats_update_begin(&__stats->syncp);		\
		__stats->cnt++;						\
		__stats->nsecs += sched_घड़ी() - __start;		\
		u64_stats_update_end(&__stats->syncp);			\
	पूर्ण अन्यथा अणु							\
		__ret = dfunc(ctx, (prog)->insnsi, (prog)->bpf_func);	\
	पूर्ण								\
	__ret; पूर्ण)

#घोषणा BPF_PROG_RUN(prog, ctx)						\
	__BPF_PROG_RUN(prog, ctx, bpf_dispatcher_nop_func)

/*
 * Use in preemptible and thereक्रमe migratable context to make sure that
 * the execution of the BPF program runs on one CPU.
 *
 * This uses migrate_disable/enable() explicitly to करोcument that the
 * invocation of a BPF program करोes not require reentrancy protection
 * against a BPF program which is invoked from a preempting task.
 *
 * For non RT enabled kernels migrate_disable/enable() maps to
 * preempt_disable/enable(), i.e. it disables also preemption.
 */
अटल अंतरभूत u32 bpf_prog_run_pin_on_cpu(स्थिर काष्ठा bpf_prog *prog,
					  स्थिर व्योम *ctx)
अणु
	u32 ret;

	migrate_disable();
	ret = __BPF_PROG_RUN(prog, ctx, bpf_dispatcher_nop_func);
	migrate_enable();
	वापस ret;
पूर्ण

#घोषणा BPF_SKB_CB_LEN QDISC_CB_PRIV_LEN

काष्ठा bpf_skb_data_end अणु
	काष्ठा qdisc_skb_cb qdisc_cb;
	व्योम *data_meta;
	व्योम *data_end;
पूर्ण;

काष्ठा bpf_nh_params अणु
	u32 nh_family;
	जोड़ अणु
		u32 ipv4_nh;
		काष्ठा in6_addr ipv6_nh;
	पूर्ण;
पूर्ण;

काष्ठा bpf_redirect_info अणु
	u32 flags;
	u32 tgt_index;
	व्योम *tgt_value;
	u32 map_id;
	क्रमागत bpf_map_type map_type;
	u32 kern_flags;
	काष्ठा bpf_nh_params nh;
पूर्ण;

DECLARE_PER_CPU(काष्ठा bpf_redirect_info, bpf_redirect_info);

/* flags क्रम bpf_redirect_info kern_flags */
#घोषणा BPF_RI_F_RF_NO_सूचीECT	BIT(0)	/* no napi_direct on वापस_frame */

/* Compute the linear packet data range [data, data_end) which
 * will be accessed by various program types (cls_bpf, act_bpf,
 * lwt, ...). Subप्रणालीs allowing direct data access must (!)
 * ensure that cb[] area can be written to when BPF program is
 * invoked (otherwise cb[] save/restore is necessary).
 */
अटल अंतरभूत व्योम bpf_compute_data_poपूर्णांकers(काष्ठा sk_buff *skb)
अणु
	काष्ठा bpf_skb_data_end *cb = (काष्ठा bpf_skb_data_end *)skb->cb;

	BUILD_BUG_ON(माप(*cb) > माप_field(काष्ठा sk_buff, cb));
	cb->data_meta = skb->data - skb_metadata_len(skb);
	cb->data_end  = skb->data + skb_headlen(skb);
पूर्ण

/* Similar to bpf_compute_data_poपूर्णांकers(), except that save orginal
 * data in cb->data and cb->meta_data क्रम restore.
 */
अटल अंतरभूत व्योम bpf_compute_and_save_data_end(
	काष्ठा sk_buff *skb, व्योम **saved_data_end)
अणु
	काष्ठा bpf_skb_data_end *cb = (काष्ठा bpf_skb_data_end *)skb->cb;

	*saved_data_end = cb->data_end;
	cb->data_end  = skb->data + skb_headlen(skb);
पूर्ण

/* Restore data saved by bpf_compute_data_poपूर्णांकers(). */
अटल अंतरभूत व्योम bpf_restore_data_end(
	काष्ठा sk_buff *skb, व्योम *saved_data_end)
अणु
	काष्ठा bpf_skb_data_end *cb = (काष्ठा bpf_skb_data_end *)skb->cb;

	cb->data_end = saved_data_end;
पूर्ण

अटल अंतरभूत u8 *bpf_skb_cb(काष्ठा sk_buff *skb)
अणु
	/* eBPF programs may पढ़ो/ग_लिखो skb->cb[] area to transfer meta
	 * data between tail calls. Since this also needs to work with
	 * tc, that scratch memory is mapped to qdisc_skb_cb's data area.
	 *
	 * In some socket filter हालs, the cb unक्रमtunately needs to be
	 * saved/restored so that protocol specअगरic skb->cb[] data won't
	 * be lost. In any हाल, due to unpriviledged eBPF programs
	 * attached to sockets, we need to clear the bpf_skb_cb() area
	 * to not leak previous contents to user space.
	 */
	BUILD_BUG_ON(माप_field(काष्ठा __sk_buff, cb) != BPF_SKB_CB_LEN);
	BUILD_BUG_ON(माप_field(काष्ठा __sk_buff, cb) !=
		     माप_field(काष्ठा qdisc_skb_cb, data));

	वापस qdisc_skb_cb(skb)->data;
पूर्ण

/* Must be invoked with migration disabled */
अटल अंतरभूत u32 __bpf_prog_run_save_cb(स्थिर काष्ठा bpf_prog *prog,
					 काष्ठा sk_buff *skb)
अणु
	u8 *cb_data = bpf_skb_cb(skb);
	u8 cb_saved[BPF_SKB_CB_LEN];
	u32 res;

	अगर (unlikely(prog->cb_access)) अणु
		स_नकल(cb_saved, cb_data, माप(cb_saved));
		स_रखो(cb_data, 0, माप(cb_saved));
	पूर्ण

	res = BPF_PROG_RUN(prog, skb);

	अगर (unlikely(prog->cb_access))
		स_नकल(cb_data, cb_saved, माप(cb_saved));

	वापस res;
पूर्ण

अटल अंतरभूत u32 bpf_prog_run_save_cb(स्थिर काष्ठा bpf_prog *prog,
				       काष्ठा sk_buff *skb)
अणु
	u32 res;

	migrate_disable();
	res = __bpf_prog_run_save_cb(prog, skb);
	migrate_enable();
	वापस res;
पूर्ण

अटल अंतरभूत u32 bpf_prog_run_clear_cb(स्थिर काष्ठा bpf_prog *prog,
					काष्ठा sk_buff *skb)
अणु
	u8 *cb_data = bpf_skb_cb(skb);
	u32 res;

	अगर (unlikely(prog->cb_access))
		स_रखो(cb_data, 0, BPF_SKB_CB_LEN);

	res = bpf_prog_run_pin_on_cpu(prog, skb);
	वापस res;
पूर्ण

DECLARE_BPF_DISPATCHER(xdp)

अटल __always_अंतरभूत u32 bpf_prog_run_xdp(स्थिर काष्ठा bpf_prog *prog,
					    काष्ठा xdp_buff *xdp)
अणु
	/* Caller needs to hold rcu_पढ़ो_lock() (!), otherwise program
	 * can be released जबतक still running, or map elements could be
	 * मुक्तd early जबतक still having concurrent users. XDP fastpath
	 * alपढ़ोy takes rcu_पढ़ो_lock() when fetching the program, so
	 * it's not necessary here anymore.
	 */
	वापस __BPF_PROG_RUN(prog, xdp, BPF_DISPATCHER_FUNC(xdp));
पूर्ण

व्योम bpf_prog_change_xdp(काष्ठा bpf_prog *prev_prog, काष्ठा bpf_prog *prog);

अटल अंतरभूत u32 bpf_prog_insn_size(स्थिर काष्ठा bpf_prog *prog)
अणु
	वापस prog->len * माप(काष्ठा bpf_insn);
पूर्ण

अटल अंतरभूत u32 bpf_prog_tag_scratch_size(स्थिर काष्ठा bpf_prog *prog)
अणु
	वापस round_up(bpf_prog_insn_size(prog) +
			माप(__be64) + 1, SHA1_BLOCK_SIZE);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक bpf_prog_size(अचिन्हित पूर्णांक proglen)
अणु
	वापस max(माप(काष्ठा bpf_prog),
		   दुरत्व(काष्ठा bpf_prog, insns[proglen]));
पूर्ण

अटल अंतरभूत bool bpf_prog_was_classic(स्थिर काष्ठा bpf_prog *prog)
अणु
	/* When classic BPF programs have been loaded and the arch
	 * करोes not have a classic BPF JIT (anymore), they have been
	 * converted via bpf_migrate_filter() to eBPF and thus always
	 * have an unspec program type.
	 */
	वापस prog->type == BPF_PROG_TYPE_UNSPEC;
पूर्ण

अटल अंतरभूत u32 bpf_ctx_off_adjust_machine(u32 size)
अणु
	स्थिर u32 size_machine = माप(अचिन्हित दीर्घ);

	अगर (size > size_machine && size % size_machine == 0)
		size = size_machine;

	वापस size;
पूर्ण

अटल अंतरभूत bool
bpf_ctx_narrow_access_ok(u32 off, u32 size, u32 size_शेष)
अणु
	वापस size <= size_शेष && (size & (size - 1)) == 0;
पूर्ण

अटल अंतरभूत u8
bpf_ctx_narrow_access_offset(u32 off, u32 size, u32 size_शेष)
अणु
	u8 access_off = off & (size_शेष - 1);

#अगर_घोषित __LITTLE_ENDIAN
	वापस access_off;
#अन्यथा
	वापस size_शेष - (access_off + size);
#पूर्ण_अगर
पूर्ण

#घोषणा bpf_ctx_wide_access_ok(off, size, type, field)			\
	(size == माप(__u64) &&					\
	off >= दुरत्व(type, field) &&					\
	off + माप(__u64) <= दुरत्वend(type, field) &&		\
	off % माप(__u64) == 0)

#घोषणा bpf_classic_proglen(fprog) (fprog->len * माप(fprog->filter[0]))

अटल अंतरभूत व्योम bpf_prog_lock_ro(काष्ठा bpf_prog *fp)
अणु
#अगर_अघोषित CONFIG_BPF_JIT_ALWAYS_ON
	अगर (!fp->jited) अणु
		set_vm_flush_reset_perms(fp);
		set_memory_ro((अचिन्हित दीर्घ)fp, fp->pages);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम bpf_jit_binary_lock_ro(काष्ठा bpf_binary_header *hdr)
अणु
	set_vm_flush_reset_perms(hdr);
	set_memory_ro((अचिन्हित दीर्घ)hdr, hdr->pages);
	set_memory_x((अचिन्हित दीर्घ)hdr, hdr->pages);
पूर्ण

अटल अंतरभूत काष्ठा bpf_binary_header *
bpf_jit_binary_hdr(स्थिर काष्ठा bpf_prog *fp)
अणु
	अचिन्हित दीर्घ real_start = (अचिन्हित दीर्घ)fp->bpf_func;
	अचिन्हित दीर्घ addr = real_start & PAGE_MASK;

	वापस (व्योम *)addr;
पूर्ण

पूर्णांक sk_filter_trim_cap(काष्ठा sock *sk, काष्ठा sk_buff *skb, अचिन्हित पूर्णांक cap);
अटल अंतरभूत पूर्णांक sk_filter(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	वापस sk_filter_trim_cap(sk, skb, 1);
पूर्ण

काष्ठा bpf_prog *bpf_prog_select_runसमय(काष्ठा bpf_prog *fp, पूर्णांक *err);
व्योम bpf_prog_मुक्त(काष्ठा bpf_prog *fp);

bool bpf_opcode_in_insntable(u8 code);

व्योम bpf_prog_मुक्त_linfo(काष्ठा bpf_prog *prog);
व्योम bpf_prog_fill_jited_linfo(काष्ठा bpf_prog *prog,
			       स्थिर u32 *insn_to_jit_off);
पूर्णांक bpf_prog_alloc_jited_linfo(काष्ठा bpf_prog *prog);
व्योम bpf_prog_jit_attempt_करोne(काष्ठा bpf_prog *prog);

काष्ठा bpf_prog *bpf_prog_alloc(अचिन्हित पूर्णांक size, gfp_t gfp_extra_flags);
काष्ठा bpf_prog *bpf_prog_alloc_no_stats(अचिन्हित पूर्णांक size, gfp_t gfp_extra_flags);
काष्ठा bpf_prog *bpf_prog_पुनः_स्मृति(काष्ठा bpf_prog *fp_old, अचिन्हित पूर्णांक size,
				  gfp_t gfp_extra_flags);
व्योम __bpf_prog_मुक्त(काष्ठा bpf_prog *fp);

अटल अंतरभूत व्योम bpf_prog_unlock_मुक्त(काष्ठा bpf_prog *fp)
अणु
	__bpf_prog_मुक्त(fp);
पूर्ण

प्रकार पूर्णांक (*bpf_aux_classic_check_t)(काष्ठा sock_filter *filter,
				       अचिन्हित पूर्णांक flen);

पूर्णांक bpf_prog_create(काष्ठा bpf_prog **pfp, काष्ठा sock_fprog_kern *fprog);
पूर्णांक bpf_prog_create_from_user(काष्ठा bpf_prog **pfp, काष्ठा sock_fprog *fprog,
			      bpf_aux_classic_check_t trans, bool save_orig);
व्योम bpf_prog_destroy(काष्ठा bpf_prog *fp);

पूर्णांक sk_attach_filter(काष्ठा sock_fprog *fprog, काष्ठा sock *sk);
पूर्णांक sk_attach_bpf(u32 ufd, काष्ठा sock *sk);
पूर्णांक sk_reuseport_attach_filter(काष्ठा sock_fprog *fprog, काष्ठा sock *sk);
पूर्णांक sk_reuseport_attach_bpf(u32 ufd, काष्ठा sock *sk);
व्योम sk_reuseport_prog_मुक्त(काष्ठा bpf_prog *prog);
पूर्णांक sk_detach_filter(काष्ठा sock *sk);
पूर्णांक sk_get_filter(काष्ठा sock *sk, काष्ठा sock_filter __user *filter,
		  अचिन्हित पूर्णांक len);

bool sk_filter_अक्षरge(काष्ठा sock *sk, काष्ठा sk_filter *fp);
व्योम sk_filter_unअक्षरge(काष्ठा sock *sk, काष्ठा sk_filter *fp);

u64 __bpf_call_base(u64 r1, u64 r2, u64 r3, u64 r4, u64 r5);
#घोषणा __bpf_call_base_args \
	((u64 (*)(u64, u64, u64, u64, u64, स्थिर काष्ठा bpf_insn *)) \
	 (व्योम *)__bpf_call_base)

काष्ठा bpf_prog *bpf_पूर्णांक_jit_compile(काष्ठा bpf_prog *prog);
व्योम bpf_jit_compile(काष्ठा bpf_prog *prog);
bool bpf_jit_needs_zext(व्योम);
bool bpf_jit_supports_kfunc_call(व्योम);
bool bpf_helper_changes_pkt_data(व्योम *func);

अटल अंतरभूत bool bpf_dump_raw_ok(स्थिर काष्ठा cred *cred)
अणु
	/* Reस्थिरruction of call-sites is dependent on kallsyms,
	 * thus make dump the same restriction.
	 */
	वापस kallsyms_show_value(cred);
पूर्ण

काष्ठा bpf_prog *bpf_patch_insn_single(काष्ठा bpf_prog *prog, u32 off,
				       स्थिर काष्ठा bpf_insn *patch, u32 len);
पूर्णांक bpf_हटाओ_insns(काष्ठा bpf_prog *prog, u32 off, u32 cnt);

व्योम bpf_clear_redirect_map(काष्ठा bpf_map *map);

अटल अंतरभूत bool xdp_वापस_frame_no_direct(व्योम)
अणु
	काष्ठा bpf_redirect_info *ri = this_cpu_ptr(&bpf_redirect_info);

	वापस ri->kern_flags & BPF_RI_F_RF_NO_सूचीECT;
पूर्ण

अटल अंतरभूत व्योम xdp_set_वापस_frame_no_direct(व्योम)
अणु
	काष्ठा bpf_redirect_info *ri = this_cpu_ptr(&bpf_redirect_info);

	ri->kern_flags |= BPF_RI_F_RF_NO_सूचीECT;
पूर्ण

अटल अंतरभूत व्योम xdp_clear_वापस_frame_no_direct(व्योम)
अणु
	काष्ठा bpf_redirect_info *ri = this_cpu_ptr(&bpf_redirect_info);

	ri->kern_flags &= ~BPF_RI_F_RF_NO_सूचीECT;
पूर्ण

अटल अंतरभूत पूर्णांक xdp_ok_fwd_dev(स्थिर काष्ठा net_device *fwd,
				 अचिन्हित पूर्णांक pktlen)
अणु
	अचिन्हित पूर्णांक len;

	अगर (unlikely(!(fwd->flags & IFF_UP)))
		वापस -ENETDOWN;

	len = fwd->mtu + fwd->hard_header_len + VLAN_HLEN;
	अगर (pktlen > len)
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

/* The pair of xdp_करो_redirect and xdp_करो_flush MUST be called in the
 * same cpu context. Further क्रम best results no more than a single map
 * क्रम the करो_redirect/करो_flush pair should be used. This limitation is
 * because we only track one map and क्रमce a flush when the map changes.
 * This करोes not appear to be a real limitation क्रम existing software.
 */
पूर्णांक xdp_करो_generic_redirect(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
			    काष्ठा xdp_buff *xdp, काष्ठा bpf_prog *prog);
पूर्णांक xdp_करो_redirect(काष्ठा net_device *dev,
		    काष्ठा xdp_buff *xdp,
		    काष्ठा bpf_prog *prog);
व्योम xdp_करो_flush(व्योम);

/* The xdp_करो_flush_map() helper has been नामd to drop the _map suffix, as
 * it is no दीर्घer only flushing maps. Keep this define क्रम compatibility
 * until all drivers are updated - करो not use xdp_करो_flush_map() in new code!
 */
#घोषणा xdp_करो_flush_map xdp_करो_flush

व्योम bpf_warn_invalid_xdp_action(u32 act);

#अगर_घोषित CONFIG_INET
काष्ठा sock *bpf_run_sk_reuseport(काष्ठा sock_reuseport *reuse, काष्ठा sock *sk,
				  काष्ठा bpf_prog *prog, काष्ठा sk_buff *skb,
				  u32 hash);
#अन्यथा
अटल अंतरभूत काष्ठा sock *
bpf_run_sk_reuseport(काष्ठा sock_reuseport *reuse, काष्ठा sock *sk,
		     काष्ठा bpf_prog *prog, काष्ठा sk_buff *skb,
		     u32 hash)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_BPF_JIT
बाह्य पूर्णांक bpf_jit_enable;
बाह्य पूर्णांक bpf_jit_harden;
बाह्य पूर्णांक bpf_jit_kallsyms;
बाह्य दीर्घ bpf_jit_limit;

प्रकार व्योम (*bpf_jit_fill_hole_t)(व्योम *area, अचिन्हित पूर्णांक size);

काष्ठा bpf_binary_header *
bpf_jit_binary_alloc(अचिन्हित पूर्णांक proglen, u8 **image_ptr,
		     अचिन्हित पूर्णांक alignment,
		     bpf_jit_fill_hole_t bpf_fill_ill_insns);
व्योम bpf_jit_binary_मुक्त(काष्ठा bpf_binary_header *hdr);
u64 bpf_jit_alloc_exec_limit(व्योम);
व्योम *bpf_jit_alloc_exec(अचिन्हित दीर्घ size);
व्योम bpf_jit_मुक्त_exec(व्योम *addr);
व्योम bpf_jit_मुक्त(काष्ठा bpf_prog *fp);

पूर्णांक bpf_jit_add_poke_descriptor(काष्ठा bpf_prog *prog,
				काष्ठा bpf_jit_poke_descriptor *poke);

पूर्णांक bpf_jit_get_func_addr(स्थिर काष्ठा bpf_prog *prog,
			  स्थिर काष्ठा bpf_insn *insn, bool extra_pass,
			  u64 *func_addr, bool *func_addr_fixed);

काष्ठा bpf_prog *bpf_jit_blind_स्थिरants(काष्ठा bpf_prog *fp);
व्योम bpf_jit_prog_release_other(काष्ठा bpf_prog *fp, काष्ठा bpf_prog *fp_other);

अटल अंतरभूत व्योम bpf_jit_dump(अचिन्हित पूर्णांक flen, अचिन्हित पूर्णांक proglen,
				u32 pass, व्योम *image)
अणु
	pr_err("flen=%u proglen=%u pass=%u image=%pK from=%s pid=%d\n", flen,
	       proglen, pass, image, current->comm, task_pid_nr(current));

	अगर (image)
		prपूर्णांक_hex_dump(KERN_ERR, "JIT code: ", DUMP_PREFIX_OFFSET,
			       16, 1, image, proglen, false);
पूर्ण

अटल अंतरभूत bool bpf_jit_is_ebpf(व्योम)
अणु
# अगरdef CONFIG_HAVE_EBPF_JIT
	वापस true;
# अन्यथा
	वापस false;
# endअगर
पूर्ण

अटल अंतरभूत bool ebpf_jit_enabled(व्योम)
अणु
	वापस bpf_jit_enable && bpf_jit_is_ebpf();
पूर्ण

अटल अंतरभूत bool bpf_prog_ebpf_jited(स्थिर काष्ठा bpf_prog *fp)
अणु
	वापस fp->jited && bpf_jit_is_ebpf();
पूर्ण

अटल अंतरभूत bool bpf_jit_blinding_enabled(काष्ठा bpf_prog *prog)
अणु
	/* These are the prerequisites, should someone ever have the
	 * idea to call blinding outside of them, we make sure to
	 * bail out.
	 */
	अगर (!bpf_jit_is_ebpf())
		वापस false;
	अगर (!prog->jit_requested)
		वापस false;
	अगर (!bpf_jit_harden)
		वापस false;
	अगर (bpf_jit_harden == 1 && capable(CAP_SYS_ADMIN))
		वापस false;

	वापस true;
पूर्ण

अटल अंतरभूत bool bpf_jit_kallsyms_enabled(व्योम)
अणु
	/* There are a couple of corner हालs where kallsyms should
	 * not be enabled f.e. on hardening.
	 */
	अगर (bpf_jit_harden)
		वापस false;
	अगर (!bpf_jit_kallsyms)
		वापस false;
	अगर (bpf_jit_kallsyms == 1)
		वापस true;

	वापस false;
पूर्ण

स्थिर अक्षर *__bpf_address_lookup(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ *size,
				 अचिन्हित दीर्घ *off, अक्षर *sym);
bool is_bpf_text_address(अचिन्हित दीर्घ addr);
पूर्णांक bpf_get_kallsym(अचिन्हित पूर्णांक symnum, अचिन्हित दीर्घ *value, अक्षर *type,
		    अक्षर *sym);

अटल अंतरभूत स्थिर अक्षर *
bpf_address_lookup(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ *size,
		   अचिन्हित दीर्घ *off, अक्षर **modname, अक्षर *sym)
अणु
	स्थिर अक्षर *ret = __bpf_address_lookup(addr, size, off, sym);

	अगर (ret && modname)
		*modname = शून्य;
	वापस ret;
पूर्ण

व्योम bpf_prog_kallsyms_add(काष्ठा bpf_prog *fp);
व्योम bpf_prog_kallsyms_del(काष्ठा bpf_prog *fp);

#अन्यथा /* CONFIG_BPF_JIT */

अटल अंतरभूत bool ebpf_jit_enabled(व्योम)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool bpf_jit_blinding_enabled(काष्ठा bpf_prog *prog)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool bpf_prog_ebpf_jited(स्थिर काष्ठा bpf_prog *fp)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक
bpf_jit_add_poke_descriptor(काष्ठा bpf_prog *prog,
			    काष्ठा bpf_jit_poke_descriptor *poke)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत व्योम bpf_jit_मुक्त(काष्ठा bpf_prog *fp)
अणु
	bpf_prog_unlock_मुक्त(fp);
पूर्ण

अटल अंतरभूत bool bpf_jit_kallsyms_enabled(व्योम)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *
__bpf_address_lookup(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ *size,
		     अचिन्हित दीर्घ *off, अक्षर *sym)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत bool is_bpf_text_address(अचिन्हित दीर्घ addr)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक bpf_get_kallsym(अचिन्हित पूर्णांक symnum, अचिन्हित दीर्घ *value,
				  अक्षर *type, अक्षर *sym)
अणु
	वापस -दुस्फल;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *
bpf_address_lookup(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ *size,
		   अचिन्हित दीर्घ *off, अक्षर **modname, अक्षर *sym)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम bpf_prog_kallsyms_add(काष्ठा bpf_prog *fp)
अणु
पूर्ण

अटल अंतरभूत व्योम bpf_prog_kallsyms_del(काष्ठा bpf_prog *fp)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_BPF_JIT */

व्योम bpf_prog_kallsyms_del_all(काष्ठा bpf_prog *fp);

#घोषणा BPF_ANC		BIT(15)

अटल अंतरभूत bool bpf_needs_clear_a(स्थिर काष्ठा sock_filter *first)
अणु
	चयन (first->code) अणु
	हाल BPF_RET | BPF_K:
	हाल BPF_LD | BPF_W | BPF_LEN:
		वापस false;

	हाल BPF_LD | BPF_W | BPF_ABS:
	हाल BPF_LD | BPF_H | BPF_ABS:
	हाल BPF_LD | BPF_B | BPF_ABS:
		अगर (first->k == SKF_AD_OFF + SKF_AD_ALU_XOR_X)
			वापस true;
		वापस false;

	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल अंतरभूत u16 bpf_anc_helper(स्थिर काष्ठा sock_filter *ftest)
अणु
	BUG_ON(ftest->code & BPF_ANC);

	चयन (ftest->code) अणु
	हाल BPF_LD | BPF_W | BPF_ABS:
	हाल BPF_LD | BPF_H | BPF_ABS:
	हाल BPF_LD | BPF_B | BPF_ABS:
#घोषणा BPF_ANCILLARY(CODE)	हाल SKF_AD_OFF + SKF_AD_##CODE:	\
				वापस BPF_ANC | SKF_AD_##CODE
		चयन (ftest->k) अणु
		BPF_ANCILLARY(PROTOCOL);
		BPF_ANCILLARY(PKTTYPE);
		BPF_ANCILLARY(IFINDEX);
		BPF_ANCILLARY(NLATTR);
		BPF_ANCILLARY(NLATTR_NEST);
		BPF_ANCILLARY(MARK);
		BPF_ANCILLARY(QUEUE);
		BPF_ANCILLARY(HATYPE);
		BPF_ANCILLARY(RXHASH);
		BPF_ANCILLARY(CPU);
		BPF_ANCILLARY(ALU_XOR_X);
		BPF_ANCILLARY(VLAN_TAG);
		BPF_ANCILLARY(VLAN_TAG_PRESENT);
		BPF_ANCILLARY(PAY_OFFSET);
		BPF_ANCILLARY(RANDOM);
		BPF_ANCILLARY(VLAN_TPID);
		पूर्ण
		fallthrough;
	शेष:
		वापस ftest->code;
	पूर्ण
पूर्ण

व्योम *bpf_पूर्णांकernal_load_poपूर्णांकer_neg_helper(स्थिर काष्ठा sk_buff *skb,
					   पूर्णांक k, अचिन्हित पूर्णांक size);

अटल अंतरभूत पूर्णांक bpf_tell_extensions(व्योम)
अणु
	वापस SKF_AD_MAX;
पूर्ण

काष्ठा bpf_sock_addr_kern अणु
	काष्ठा sock *sk;
	काष्ठा sockaddr *uaddr;
	/* Temporary "register" to make indirect stores to nested काष्ठाures
	 * defined above. We need three रेजिस्टरs to make such a store, but
	 * only two (src and dst) are available at convert_ctx_access समय
	 */
	u64 पंचांगp_reg;
	व्योम *t_ctx;	/* Attach type specअगरic context. */
पूर्ण;

काष्ठा bpf_sock_ops_kern अणु
	काष्ठा	sock *sk;
	जोड़ अणु
		u32 args[4];
		u32 reply;
		u32 replyदीर्घ[4];
	पूर्ण;
	काष्ठा sk_buff	*syn_skb;
	काष्ठा sk_buff	*skb;
	व्योम	*skb_data_end;
	u8	op;
	u8	is_fullsock;
	u8	reमुख्यing_opt_len;
	u64	temp;			/* temp and everything after is not
					 * initialized to 0 beक्रमe calling
					 * the BPF program. New fields that
					 * should be initialized to 0 should
					 * be inserted beक्रमe temp.
					 * temp is scratch storage used by
					 * sock_ops_convert_ctx_access
					 * as temporary storage of a रेजिस्टर.
					 */
पूर्ण;

काष्ठा bpf_sysctl_kern अणु
	काष्ठा ctl_table_header *head;
	काष्ठा ctl_table *table;
	व्योम *cur_val;
	माप_प्रकार cur_len;
	व्योम *new_val;
	माप_प्रकार new_len;
	पूर्णांक new_updated;
	पूर्णांक ग_लिखो;
	loff_t *ppos;
	/* Temporary "register" क्रम indirect stores to ppos. */
	u64 पंचांगp_reg;
पूर्ण;

#घोषणा BPF_SOCKOPT_KERN_BUF_SIZE	32
काष्ठा bpf_sockopt_buf अणु
	u8		data[BPF_SOCKOPT_KERN_BUF_SIZE];
पूर्ण;

काष्ठा bpf_sockopt_kern अणु
	काष्ठा sock	*sk;
	u8		*optval;
	u8		*optval_end;
	s32		level;
	s32		optname;
	s32		optlen;
	s32		retval;
पूर्ण;

पूर्णांक copy_bpf_fprog_from_user(काष्ठा sock_fprog *dst, sockptr_t src, पूर्णांक len);

काष्ठा bpf_sk_lookup_kern अणु
	u16		family;
	u16		protocol;
	__be16		sport;
	u16		dport;
	काष्ठा अणु
		__be32 saddr;
		__be32 daddr;
	पूर्ण v4;
	काष्ठा अणु
		स्थिर काष्ठा in6_addr *saddr;
		स्थिर काष्ठा in6_addr *daddr;
	पूर्ण v6;
	काष्ठा sock	*selected_sk;
	bool		no_reuseport;
पूर्ण;

बाह्य काष्ठा अटल_key_false bpf_sk_lookup_enabled;

/* Runners क्रम BPF_SK_LOOKUP programs to invoke on socket lookup.
 *
 * Allowed वापस values क्रम a BPF SK_LOOKUP program are SK_PASS and
 * SK_DROP. Their meaning is as follows:
 *
 *  SK_PASS && ctx.selected_sk != शून्य: use selected_sk as lookup result
 *  SK_PASS && ctx.selected_sk == शून्य: जारी to htable-based socket lookup
 *  SK_DROP                           : terminate lookup with -ECONNREFUSED
 *
 * This macro aggregates वापस values and selected sockets from
 * multiple BPF programs according to following rules in order:
 *
 *  1. If any program वापसed SK_PASS and a non-शून्य ctx.selected_sk,
 *     macro result is SK_PASS and last ctx.selected_sk is used.
 *  2. If any program वापसed SK_DROP वापस value,
 *     macro result is SK_DROP.
 *  3. Otherwise result is SK_PASS and ctx.selected_sk is शून्य.
 *
 * Caller must ensure that the prog array is non-शून्य, and that the
 * array as well as the programs it contains reमुख्य valid.
 */
#घोषणा BPF_PROG_SK_LOOKUP_RUN_ARRAY(array, ctx, func)			\
	(अणु								\
		काष्ठा bpf_sk_lookup_kern *_ctx = &(ctx);		\
		काष्ठा bpf_prog_array_item *_item;			\
		काष्ठा sock *_selected_sk = शून्य;			\
		bool _no_reuseport = false;				\
		काष्ठा bpf_prog *_prog;					\
		bool _all_pass = true;					\
		u32 _ret;						\
									\
		migrate_disable();					\
		_item = &(array)->items[0];				\
		जबतक ((_prog = READ_ONCE(_item->prog))) अणु		\
			/* restore most recent selection */		\
			_ctx->selected_sk = _selected_sk;		\
			_ctx->no_reuseport = _no_reuseport;		\
									\
			_ret = func(_prog, _ctx);			\
			अगर (_ret == SK_PASS && _ctx->selected_sk) अणु	\
				/* remember last non-शून्य socket */	\
				_selected_sk = _ctx->selected_sk;	\
				_no_reuseport = _ctx->no_reuseport;	\
			पूर्ण अन्यथा अगर (_ret == SK_DROP && _all_pass) अणु	\
				_all_pass = false;			\
			पूर्ण						\
			_item++;					\
		पूर्ण							\
		_ctx->selected_sk = _selected_sk;			\
		_ctx->no_reuseport = _no_reuseport;			\
		migrate_enable();					\
		_all_pass || _selected_sk ? SK_PASS : SK_DROP;		\
	 पूर्ण)

अटल अंतरभूत bool bpf_sk_lookup_run_v4(काष्ठा net *net, पूर्णांक protocol,
					स्थिर __be32 saddr, स्थिर __be16 sport,
					स्थिर __be32 daddr, स्थिर u16 dport,
					काष्ठा sock **psk)
अणु
	काष्ठा bpf_prog_array *run_array;
	काष्ठा sock *selected_sk = शून्य;
	bool no_reuseport = false;

	rcu_पढ़ो_lock();
	run_array = rcu_dereference(net->bpf.run_array[NETNS_BPF_SK_LOOKUP]);
	अगर (run_array) अणु
		काष्ठा bpf_sk_lookup_kern ctx = अणु
			.family		= AF_INET,
			.protocol	= protocol,
			.v4.saddr	= saddr,
			.v4.daddr	= daddr,
			.sport		= sport,
			.dport		= dport,
		पूर्ण;
		u32 act;

		act = BPF_PROG_SK_LOOKUP_RUN_ARRAY(run_array, ctx, BPF_PROG_RUN);
		अगर (act == SK_PASS) अणु
			selected_sk = ctx.selected_sk;
			no_reuseport = ctx.no_reuseport;
		पूर्ण अन्यथा अणु
			selected_sk = ERR_PTR(-ECONNREFUSED);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	*psk = selected_sk;
	वापस no_reuseport;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल अंतरभूत bool bpf_sk_lookup_run_v6(काष्ठा net *net, पूर्णांक protocol,
					स्थिर काष्ठा in6_addr *saddr,
					स्थिर __be16 sport,
					स्थिर काष्ठा in6_addr *daddr,
					स्थिर u16 dport,
					काष्ठा sock **psk)
अणु
	काष्ठा bpf_prog_array *run_array;
	काष्ठा sock *selected_sk = शून्य;
	bool no_reuseport = false;

	rcu_पढ़ो_lock();
	run_array = rcu_dereference(net->bpf.run_array[NETNS_BPF_SK_LOOKUP]);
	अगर (run_array) अणु
		काष्ठा bpf_sk_lookup_kern ctx = अणु
			.family		= AF_INET6,
			.protocol	= protocol,
			.v6.saddr	= saddr,
			.v6.daddr	= daddr,
			.sport		= sport,
			.dport		= dport,
		पूर्ण;
		u32 act;

		act = BPF_PROG_SK_LOOKUP_RUN_ARRAY(run_array, ctx, BPF_PROG_RUN);
		अगर (act == SK_PASS) अणु
			selected_sk = ctx.selected_sk;
			no_reuseport = ctx.no_reuseport;
		पूर्ण अन्यथा अणु
			selected_sk = ERR_PTR(-ECONNREFUSED);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	*psk = selected_sk;
	वापस no_reuseport;
पूर्ण
#पूर्ण_अगर /* IS_ENABLED(CONFIG_IPV6) */

अटल __always_अंतरभूत पूर्णांक __bpf_xdp_redirect_map(काष्ठा bpf_map *map, u32 अगरindex, u64 flags,
						  व्योम *lookup_elem(काष्ठा bpf_map *map, u32 key))
अणु
	काष्ठा bpf_redirect_info *ri = this_cpu_ptr(&bpf_redirect_info);

	/* Lower bits of the flags are used as वापस code on lookup failure */
	अगर (unlikely(flags > XDP_TX))
		वापस XDP_ABORTED;

	ri->tgt_value = lookup_elem(map, अगरindex);
	अगर (unlikely(!ri->tgt_value)) अणु
		/* If the lookup fails we want to clear out the state in the
		 * redirect_info काष्ठा completely, so that अगर an eBPF program
		 * perक्रमms multiple lookups, the last one always takes
		 * precedence.
		 */
		ri->map_id = पूर्णांक_उच्च; /* Valid map id idr range: [1,पूर्णांक_उच्च[ */
		ri->map_type = BPF_MAP_TYPE_UNSPEC;
		वापस flags;
	पूर्ण

	ri->tgt_index = अगरindex;
	ri->map_id = map->id;
	ri->map_type = map->map_type;

	वापस XDP_REसूचीECT;
पूर्ण

#पूर्ण_अगर /* __LINUX_FILTER_H__ */
