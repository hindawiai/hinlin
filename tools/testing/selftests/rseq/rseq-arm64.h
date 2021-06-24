<शैली गुरु>
/* SPDX-License-Identअगरier: LGPL-2.1 OR MIT */
/*
 * rseq-arm64.h
 *
 * (C) Copyright 2016-2018 - Mathieu Desnoyers <mathieu.desnoyers@efficios.com>
 * (C) Copyright 2018 - Will Deacon <will.deacon@arm.com>
 */

/*
 * aarch64 -mbig-endian generates mixed endianness code vs data:
 * little-endian code and big-endian data. Ensure the RSEQ_SIG signature
 * matches code endianness.
 */
#घोषणा RSEQ_SIG_CODE	0xd428bc00	/* BRK #0x45E0.  */

#अगर_घोषित __AARCH64EB__
#घोषणा RSEQ_SIG_DATA	0x00bc28d4	/* BRK #0x45E0.  */
#अन्यथा
#घोषणा RSEQ_SIG_DATA	RSEQ_SIG_CODE
#पूर्ण_अगर

#घोषणा RSEQ_SIG	RSEQ_SIG_DATA

#घोषणा rseq_smp_mb()	__यंत्र__ __अस्थिर__ ("dmb ish" ::: "memory")
#घोषणा rseq_smp_rmb()	__यंत्र__ __अस्थिर__ ("dmb ishld" ::: "memory")
#घोषणा rseq_smp_wmb()	__यंत्र__ __अस्थिर__ ("dmb ishst" ::: "memory")

#घोषणा rseq_smp_load_acquire(p)						\
__extension__ (अणु								\
	__typeof(*p) ____p1;							\
	चयन (माप(*p)) अणु							\
	हाल 1:									\
		यंत्र अस्थिर ("ldarb %w0, %1"					\
			: "=r" (*(__u8 *)p)					\
			: "Q" (*p) : "memory");					\
		अवरोध;								\
	हाल 2:									\
		यंत्र अस्थिर ("ldarh %w0, %1"					\
			: "=r" (*(__u16 *)p)					\
			: "Q" (*p) : "memory");					\
		अवरोध;								\
	हाल 4:									\
		यंत्र अस्थिर ("ldar %w0, %1"					\
			: "=r" (*(__u32 *)p)					\
			: "Q" (*p) : "memory");					\
		अवरोध;								\
	हाल 8:									\
		यंत्र अस्थिर ("ldar %0, %1"					\
			: "=r" (*(__u64 *)p)					\
			: "Q" (*p) : "memory");					\
		अवरोध;								\
	पूर्ण									\
	____p1;									\
पूर्ण)

#घोषणा rseq_smp_acquire__after_ctrl_dep()	rseq_smp_rmb()

#घोषणा rseq_smp_store_release(p, v)						\
करो अणु										\
	चयन (माप(*p)) अणु							\
	हाल 1:									\
		यंत्र अस्थिर ("stlrb %w1, %0"					\
				: "=Q" (*p)					\
				: "r" ((__u8)v)					\
				: "memory");					\
		अवरोध;								\
	हाल 2:									\
		यंत्र अस्थिर ("stlrh %w1, %0"					\
				: "=Q" (*p)					\
				: "r" ((__u16)v)				\
				: "memory");					\
		अवरोध;								\
	हाल 4:									\
		यंत्र अस्थिर ("stlr %w1, %0"					\
				: "=Q" (*p)					\
				: "r" ((__u32)v)				\
				: "memory");					\
		अवरोध;								\
	हाल 8:									\
		यंत्र अस्थिर ("stlr %1, %0"					\
				: "=Q" (*p)					\
				: "r" ((__u64)v)				\
				: "memory");					\
		अवरोध;								\
	पूर्ण									\
पूर्ण जबतक (0)

#अगर_घोषित RSEQ_SKIP_FASTPATH
#समावेश "rseq-skip.h"
#अन्यथा /* !RSEQ_SKIP_FASTPATH */

#घोषणा RSEQ_ASM_TMP_REG32	"w15"
#घोषणा RSEQ_ASM_TMP_REG	"x15"
#घोषणा RSEQ_ASM_TMP_REG_2	"x14"

#घोषणा __RSEQ_ASM_DEFINE_TABLE(label, version, flags, start_ip,		\
				post_commit_offset, पात_ip)			\
	"	.pushsection	__rseq_cs, \"aw\"\n"				\
	"	.balign	32\n"							\
	__rseq_str(label) ":\n"							\
	"	.long	" __rseq_str(version) ", " __rseq_str(flags) "\n"	\
	"	.quad	" __rseq_str(start_ip) ", "				\
			  __rseq_str(post_commit_offset) ", "			\
			  __rseq_str(पात_ip) "\n"				\
	"	.popsection\n\t"						\
	"	.pushsection __rseq_cs_ptr_array, \"aw\"\n"				\
	"	.quad " __rseq_str(label) "b\n"					\
	"	.popsection\n"

#घोषणा RSEQ_ASM_DEFINE_TABLE(label, start_ip, post_commit_ip, पात_ip)	\
	__RSEQ_ASM_DEFINE_TABLE(label, 0x0, 0x0, start_ip,			\
				(post_commit_ip - start_ip), पात_ip)

/*
 * Exit poपूर्णांकs of a rseq critical section consist of all inकाष्ठाions outside
 * of the critical section where a critical section can either branch to or
 * reach through the normal course of its execution. The पात IP and the
 * post-commit IP are alपढ़ोy part of the __rseq_cs section and should not be
 * explicitly defined as additional निकास poपूर्णांकs. Knowing all निकास poपूर्णांकs is
 * useful to assist debuggers stepping over the critical section.
 */
#घोषणा RSEQ_ASM_DEFINE_EXIT_POINT(start_ip, निकास_ip)				\
	"	.pushsection __rseq_exit_point_array, \"aw\"\n"			\
	"	.quad " __rseq_str(start_ip) ", " __rseq_str(निकास_ip) "\n"	\
	"	.popsection\n"

#घोषणा RSEQ_ASM_STORE_RSEQ_CS(label, cs_label, rseq_cs)			\
	RSEQ_INJECT_ASM(1)							\
	"	adrp	" RSEQ_ASM_TMP_REG ", " __rseq_str(cs_label) "\n"	\
	"	add	" RSEQ_ASM_TMP_REG ", " RSEQ_ASM_TMP_REG		\
			", :lo12:" __rseq_str(cs_label) "\n"			\
	"	str	" RSEQ_ASM_TMP_REG ", %[" __rseq_str(rseq_cs) "]\n"	\
	__rseq_str(label) ":\n"

#घोषणा RSEQ_ASM_DEFINE_ABORT(label, पात_label)				\
	"	b	222f\n"							\
	"	.inst 	"	__rseq_str(RSEQ_SIG_CODE) "\n"			\
	__rseq_str(label) ":\n"							\
	"	b	%l[" __rseq_str(पात_label) "]\n"			\
	"222:\n"

#घोषणा RSEQ_ASM_OP_STORE(value, var)						\
	"	str	%[" __rseq_str(value) "], %[" __rseq_str(var) "]\n"

#घोषणा RSEQ_ASM_OP_STORE_RELEASE(value, var)					\
	"	stlr	%[" __rseq_str(value) "], %[" __rseq_str(var) "]\n"

#घोषणा RSEQ_ASM_OP_FINAL_STORE(value, var, post_commit_label)			\
	RSEQ_ASM_OP_STORE(value, var)						\
	__rseq_str(post_commit_label) ":\n"

#घोषणा RSEQ_ASM_OP_FINAL_STORE_RELEASE(value, var, post_commit_label)		\
	RSEQ_ASM_OP_STORE_RELEASE(value, var)					\
	__rseq_str(post_commit_label) ":\n"

#घोषणा RSEQ_ASM_OP_CMPEQ(var, expect, label)					\
	"	ldr	" RSEQ_ASM_TMP_REG ", %[" __rseq_str(var) "]\n"		\
	"	sub	" RSEQ_ASM_TMP_REG ", " RSEQ_ASM_TMP_REG		\
			", %[" __rseq_str(expect) "]\n"				\
	"	cbnz	" RSEQ_ASM_TMP_REG ", " __rseq_str(label) "\n"

#घोषणा RSEQ_ASM_OP_CMPEQ32(var, expect, label)					\
	"	ldr	" RSEQ_ASM_TMP_REG32 ", %[" __rseq_str(var) "]\n"	\
	"	sub	" RSEQ_ASM_TMP_REG32 ", " RSEQ_ASM_TMP_REG32		\
			", %w[" __rseq_str(expect) "]\n"			\
	"	cbnz	" RSEQ_ASM_TMP_REG32 ", " __rseq_str(label) "\n"

#घोषणा RSEQ_ASM_OP_CMPNE(var, expect, label)					\
	"	ldr	" RSEQ_ASM_TMP_REG ", %[" __rseq_str(var) "]\n"		\
	"	sub	" RSEQ_ASM_TMP_REG ", " RSEQ_ASM_TMP_REG		\
			", %[" __rseq_str(expect) "]\n"				\
	"	cbz	" RSEQ_ASM_TMP_REG ", " __rseq_str(label) "\n"

#घोषणा RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, label)			\
	RSEQ_INJECT_ASM(2)							\
	RSEQ_ASM_OP_CMPEQ32(current_cpu_id, cpu_id, label)

#घोषणा RSEQ_ASM_OP_R_LOAD(var)							\
	"	ldr	" RSEQ_ASM_TMP_REG ", %[" __rseq_str(var) "]\n"

#घोषणा RSEQ_ASM_OP_R_STORE(var)						\
	"	str	" RSEQ_ASM_TMP_REG ", %[" __rseq_str(var) "]\n"

#घोषणा RSEQ_ASM_OP_R_LOAD_OFF(offset)						\
	"	ldr	" RSEQ_ASM_TMP_REG ", [" RSEQ_ASM_TMP_REG		\
			", %[" __rseq_str(offset) "]]\n"

#घोषणा RSEQ_ASM_OP_R_ADD(count)						\
	"	add	" RSEQ_ASM_TMP_REG ", " RSEQ_ASM_TMP_REG		\
			", %[" __rseq_str(count) "]\n"

#घोषणा RSEQ_ASM_OP_R_FINAL_STORE(var, post_commit_label)			\
	"	str	" RSEQ_ASM_TMP_REG ", %[" __rseq_str(var) "]\n"		\
	__rseq_str(post_commit_label) ":\n"

#घोषणा RSEQ_ASM_OP_R_BAD_MEMCPY(dst, src, len)					\
	"	cbz	%[" __rseq_str(len) "], 333f\n"				\
	"	mov	" RSEQ_ASM_TMP_REG_2 ", %[" __rseq_str(len) "]\n"	\
	"222:	sub	" RSEQ_ASM_TMP_REG_2 ", " RSEQ_ASM_TMP_REG_2 ", #1\n"	\
	"	ldrb	" RSEQ_ASM_TMP_REG32 ", [%[" __rseq_str(src) "]"	\
			", " RSEQ_ASM_TMP_REG_2 "]\n"				\
	"	strb	" RSEQ_ASM_TMP_REG32 ", [%[" __rseq_str(dst) "]"	\
			", " RSEQ_ASM_TMP_REG_2 "]\n"				\
	"	cbnz	" RSEQ_ASM_TMP_REG_2 ", 222b\n"				\
	"333:\n"

अटल अंतरभूत __attribute__((always_अंतरभूत))
पूर्णांक rseq_cmpeqv_storev(पूर्णांकptr_t *v, पूर्णांकptr_t expect, पूर्णांकptr_t newv, पूर्णांक cpu)
अणु
	RSEQ_INJECT_C(9)

	__यंत्र__ __अस्थिर__ जाओ (
		RSEQ_ASM_DEFINE_TABLE(1, 2f, 3f, 4f)
		RSEQ_ASM_DEFINE_EXIT_POINT(2f, %l[cmpfail])
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_DEFINE_EXIT_POINT(2f, %l[error1])
		RSEQ_ASM_DEFINE_EXIT_POINT(2f, %l[error2])
#पूर्ण_अगर
		RSEQ_ASM_STORE_RSEQ_CS(2, 1b, rseq_cs)
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, 4f)
		RSEQ_INJECT_ASM(3)
		RSEQ_ASM_OP_CMPEQ(v, expect, %l[cmpfail])
		RSEQ_INJECT_ASM(4)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, %l[error1])
		RSEQ_ASM_OP_CMPEQ(v, expect, %l[error2])
#पूर्ण_अगर
		RSEQ_ASM_OP_FINAL_STORE(newv, v, 3)
		RSEQ_INJECT_ASM(5)
		RSEQ_ASM_DEFINE_ABORT(4, पात)
		: /* gcc यंत्र जाओ करोes not allow outमाला_दो */
		: [cpu_id]		"r" (cpu),
		  [current_cpu_id]	"Qo" (__rseq_abi.cpu_id),
		  [rseq_cs]		"m" (__rseq_abi.rseq_cs),
		  [v]			"Qo" (*v),
		  [expect]		"r" (expect),
		  [newv]		"r" (newv)
		  RSEQ_INJECT_INPUT
		: "memory", RSEQ_ASM_TMP_REG
		: पात, cmpfail
#अगर_घोषित RSEQ_COMPARE_TWICE
		  , error1, error2
#पूर्ण_अगर
	);

	वापस 0;
पात:
	RSEQ_INJECT_FAILED
	वापस -1;
cmpfail:
	वापस 1;
#अगर_घोषित RSEQ_COMPARE_TWICE
error1:
	rseq_bug("cpu_id comparison failed");
error2:
	rseq_bug("expected value comparison failed");
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत __attribute__((always_अंतरभूत))
पूर्णांक rseq_cmpnev_storeoffp_load(पूर्णांकptr_t *v, पूर्णांकptr_t expectnot,
			       off_t voffp, पूर्णांकptr_t *load, पूर्णांक cpu)
अणु
	RSEQ_INJECT_C(9)

	__यंत्र__ __अस्थिर__ जाओ (
		RSEQ_ASM_DEFINE_TABLE(1, 2f, 3f, 4f)
		RSEQ_ASM_DEFINE_EXIT_POINT(2f, %l[cmpfail])
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_DEFINE_EXIT_POINT(2f, %l[error1])
		RSEQ_ASM_DEFINE_EXIT_POINT(2f, %l[error2])
#पूर्ण_अगर
		RSEQ_ASM_STORE_RSEQ_CS(2, 1b, rseq_cs)
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, 4f)
		RSEQ_INJECT_ASM(3)
		RSEQ_ASM_OP_CMPNE(v, expectnot, %l[cmpfail])
		RSEQ_INJECT_ASM(4)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, %l[error1])
		RSEQ_ASM_OP_CMPNE(v, expectnot, %l[error2])
#पूर्ण_अगर
		RSEQ_ASM_OP_R_LOAD(v)
		RSEQ_ASM_OP_R_STORE(load)
		RSEQ_ASM_OP_R_LOAD_OFF(voffp)
		RSEQ_ASM_OP_R_FINAL_STORE(v, 3)
		RSEQ_INJECT_ASM(5)
		RSEQ_ASM_DEFINE_ABORT(4, पात)
		: /* gcc यंत्र जाओ करोes not allow outमाला_दो */
		: [cpu_id]		"r" (cpu),
		  [current_cpu_id]	"Qo" (__rseq_abi.cpu_id),
		  [rseq_cs]		"m" (__rseq_abi.rseq_cs),
		  [v]			"Qo" (*v),
		  [expectnot]		"r" (expectnot),
		  [load]		"Qo" (*load),
		  [voffp]		"r" (voffp)
		  RSEQ_INJECT_INPUT
		: "memory", RSEQ_ASM_TMP_REG
		: पात, cmpfail
#अगर_घोषित RSEQ_COMPARE_TWICE
		  , error1, error2
#पूर्ण_अगर
	);
	वापस 0;
पात:
	RSEQ_INJECT_FAILED
	वापस -1;
cmpfail:
	वापस 1;
#अगर_घोषित RSEQ_COMPARE_TWICE
error1:
	rseq_bug("cpu_id comparison failed");
error2:
	rseq_bug("expected value comparison failed");
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत __attribute__((always_अंतरभूत))
पूर्णांक rseq_addv(पूर्णांकptr_t *v, पूर्णांकptr_t count, पूर्णांक cpu)
अणु
	RSEQ_INJECT_C(9)

	__यंत्र__ __अस्थिर__ जाओ (
		RSEQ_ASM_DEFINE_TABLE(1, 2f, 3f, 4f)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_DEFINE_EXIT_POINT(2f, %l[error1])
#पूर्ण_अगर
		RSEQ_ASM_STORE_RSEQ_CS(2, 1b, rseq_cs)
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, 4f)
		RSEQ_INJECT_ASM(3)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, %l[error1])
#पूर्ण_अगर
		RSEQ_ASM_OP_R_LOAD(v)
		RSEQ_ASM_OP_R_ADD(count)
		RSEQ_ASM_OP_R_FINAL_STORE(v, 3)
		RSEQ_INJECT_ASM(4)
		RSEQ_ASM_DEFINE_ABORT(4, पात)
		: /* gcc यंत्र जाओ करोes not allow outमाला_दो */
		: [cpu_id]		"r" (cpu),
		  [current_cpu_id]	"Qo" (__rseq_abi.cpu_id),
		  [rseq_cs]		"m" (__rseq_abi.rseq_cs),
		  [v]			"Qo" (*v),
		  [count]		"r" (count)
		  RSEQ_INJECT_INPUT
		: "memory", RSEQ_ASM_TMP_REG
		: पात
#अगर_घोषित RSEQ_COMPARE_TWICE
		  , error1
#पूर्ण_अगर
	);
	वापस 0;
पात:
	RSEQ_INJECT_FAILED
	वापस -1;
#अगर_घोषित RSEQ_COMPARE_TWICE
error1:
	rseq_bug("cpu_id comparison failed");
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत __attribute__((always_अंतरभूत))
पूर्णांक rseq_cmpeqv_trystorev_storev(पूर्णांकptr_t *v, पूर्णांकptr_t expect,
				 पूर्णांकptr_t *v2, पूर्णांकptr_t newv2,
				 पूर्णांकptr_t newv, पूर्णांक cpu)
अणु
	RSEQ_INJECT_C(9)

	__यंत्र__ __अस्थिर__ जाओ (
		RSEQ_ASM_DEFINE_TABLE(1, 2f, 3f, 4f)
		RSEQ_ASM_DEFINE_EXIT_POINT(2f, %l[cmpfail])
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_DEFINE_EXIT_POINT(2f, %l[error1])
		RSEQ_ASM_DEFINE_EXIT_POINT(2f, %l[error2])
#पूर्ण_अगर
		RSEQ_ASM_STORE_RSEQ_CS(2, 1b, rseq_cs)
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, 4f)
		RSEQ_INJECT_ASM(3)
		RSEQ_ASM_OP_CMPEQ(v, expect, %l[cmpfail])
		RSEQ_INJECT_ASM(4)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, %l[error1])
		RSEQ_ASM_OP_CMPEQ(v, expect, %l[error2])
#पूर्ण_अगर
		RSEQ_ASM_OP_STORE(newv2, v2)
		RSEQ_INJECT_ASM(5)
		RSEQ_ASM_OP_FINAL_STORE(newv, v, 3)
		RSEQ_INJECT_ASM(6)
		RSEQ_ASM_DEFINE_ABORT(4, पात)
		: /* gcc यंत्र जाओ करोes not allow outमाला_दो */
		: [cpu_id]		"r" (cpu),
		  [current_cpu_id]	"Qo" (__rseq_abi.cpu_id),
		  [rseq_cs]		"m" (__rseq_abi.rseq_cs),
		  [expect]		"r" (expect),
		  [v]			"Qo" (*v),
		  [newv]		"r" (newv),
		  [v2]			"Qo" (*v2),
		  [newv2]		"r" (newv2)
		  RSEQ_INJECT_INPUT
		: "memory", RSEQ_ASM_TMP_REG
		: पात, cmpfail
#अगर_घोषित RSEQ_COMPARE_TWICE
		  , error1, error2
#पूर्ण_अगर
	);

	वापस 0;
पात:
	RSEQ_INJECT_FAILED
	वापस -1;
cmpfail:
	वापस 1;
#अगर_घोषित RSEQ_COMPARE_TWICE
error1:
	rseq_bug("cpu_id comparison failed");
error2:
	rseq_bug("expected value comparison failed");
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत __attribute__((always_अंतरभूत))
पूर्णांक rseq_cmpeqv_trystorev_storev_release(पूर्णांकptr_t *v, पूर्णांकptr_t expect,
					 पूर्णांकptr_t *v2, पूर्णांकptr_t newv2,
					 पूर्णांकptr_t newv, पूर्णांक cpu)
अणु
	RSEQ_INJECT_C(9)

	__यंत्र__ __अस्थिर__ जाओ (
		RSEQ_ASM_DEFINE_TABLE(1, 2f, 3f, 4f)
		RSEQ_ASM_DEFINE_EXIT_POINT(2f, %l[cmpfail])
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_DEFINE_EXIT_POINT(2f, %l[error1])
		RSEQ_ASM_DEFINE_EXIT_POINT(2f, %l[error2])
#पूर्ण_अगर
		RSEQ_ASM_STORE_RSEQ_CS(2, 1b, rseq_cs)
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, 4f)
		RSEQ_INJECT_ASM(3)
		RSEQ_ASM_OP_CMPEQ(v, expect, %l[cmpfail])
		RSEQ_INJECT_ASM(4)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, %l[error1])
		RSEQ_ASM_OP_CMPEQ(v, expect, %l[error2])
#पूर्ण_अगर
		RSEQ_ASM_OP_STORE(newv2, v2)
		RSEQ_INJECT_ASM(5)
		RSEQ_ASM_OP_FINAL_STORE_RELEASE(newv, v, 3)
		RSEQ_INJECT_ASM(6)
		RSEQ_ASM_DEFINE_ABORT(4, पात)
		: /* gcc यंत्र जाओ करोes not allow outमाला_दो */
		: [cpu_id]		"r" (cpu),
		  [current_cpu_id]	"Qo" (__rseq_abi.cpu_id),
		  [rseq_cs]		"m" (__rseq_abi.rseq_cs),
		  [expect]		"r" (expect),
		  [v]			"Qo" (*v),
		  [newv]		"r" (newv),
		  [v2]			"Qo" (*v2),
		  [newv2]		"r" (newv2)
		  RSEQ_INJECT_INPUT
		: "memory", RSEQ_ASM_TMP_REG
		: पात, cmpfail
#अगर_घोषित RSEQ_COMPARE_TWICE
		  , error1, error2
#पूर्ण_अगर
	);

	वापस 0;
पात:
	RSEQ_INJECT_FAILED
	वापस -1;
cmpfail:
	वापस 1;
#अगर_घोषित RSEQ_COMPARE_TWICE
error1:
	rseq_bug("cpu_id comparison failed");
error2:
	rseq_bug("expected value comparison failed");
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत __attribute__((always_अंतरभूत))
पूर्णांक rseq_cmpeqv_cmpeqv_storev(पूर्णांकptr_t *v, पूर्णांकptr_t expect,
			      पूर्णांकptr_t *v2, पूर्णांकptr_t expect2,
			      पूर्णांकptr_t newv, पूर्णांक cpu)
अणु
	RSEQ_INJECT_C(9)

	__यंत्र__ __अस्थिर__ जाओ (
		RSEQ_ASM_DEFINE_TABLE(1, 2f, 3f, 4f)
		RSEQ_ASM_DEFINE_EXIT_POINT(2f, %l[cmpfail])
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_DEFINE_EXIT_POINT(2f, %l[error1])
		RSEQ_ASM_DEFINE_EXIT_POINT(2f, %l[error2])
		RSEQ_ASM_DEFINE_EXIT_POINT(2f, %l[error3])
#पूर्ण_अगर
		RSEQ_ASM_STORE_RSEQ_CS(2, 1b, rseq_cs)
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, 4f)
		RSEQ_INJECT_ASM(3)
		RSEQ_ASM_OP_CMPEQ(v, expect, %l[cmpfail])
		RSEQ_INJECT_ASM(4)
		RSEQ_ASM_OP_CMPEQ(v2, expect2, %l[cmpfail])
		RSEQ_INJECT_ASM(5)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, %l[error1])
		RSEQ_ASM_OP_CMPEQ(v, expect, %l[error2])
		RSEQ_ASM_OP_CMPEQ(v2, expect2, %l[error3])
#पूर्ण_अगर
		RSEQ_ASM_OP_FINAL_STORE(newv, v, 3)
		RSEQ_INJECT_ASM(6)
		RSEQ_ASM_DEFINE_ABORT(4, पात)
		: /* gcc यंत्र जाओ करोes not allow outमाला_दो */
		: [cpu_id]		"r" (cpu),
		  [current_cpu_id]	"Qo" (__rseq_abi.cpu_id),
		  [rseq_cs]		"m" (__rseq_abi.rseq_cs),
		  [v]			"Qo" (*v),
		  [expect]		"r" (expect),
		  [v2]			"Qo" (*v2),
		  [expect2]		"r" (expect2),
		  [newv]		"r" (newv)
		  RSEQ_INJECT_INPUT
		: "memory", RSEQ_ASM_TMP_REG
		: पात, cmpfail
#अगर_घोषित RSEQ_COMPARE_TWICE
		  , error1, error2, error3
#पूर्ण_अगर
	);

	वापस 0;
पात:
	RSEQ_INJECT_FAILED
	वापस -1;
cmpfail:
	वापस 1;
#अगर_घोषित RSEQ_COMPARE_TWICE
error1:
	rseq_bug("cpu_id comparison failed");
error2:
	rseq_bug("expected value comparison failed");
error3:
	rseq_bug("2nd expected value comparison failed");
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत __attribute__((always_अंतरभूत))
पूर्णांक rseq_cmpeqv_tryस_नकल_storev(पूर्णांकptr_t *v, पूर्णांकptr_t expect,
				 व्योम *dst, व्योम *src, माप_प्रकार len,
				 पूर्णांकptr_t newv, पूर्णांक cpu)
अणु
	RSEQ_INJECT_C(9)

	__यंत्र__ __अस्थिर__ जाओ (
		RSEQ_ASM_DEFINE_TABLE(1, 2f, 3f, 4f)
		RSEQ_ASM_DEFINE_EXIT_POINT(2f, %l[cmpfail])
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_DEFINE_EXIT_POINT(2f, %l[error1])
		RSEQ_ASM_DEFINE_EXIT_POINT(2f, %l[error2])
#पूर्ण_अगर
		RSEQ_ASM_STORE_RSEQ_CS(2, 1b, rseq_cs)
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, 4f)
		RSEQ_INJECT_ASM(3)
		RSEQ_ASM_OP_CMPEQ(v, expect, %l[cmpfail])
		RSEQ_INJECT_ASM(4)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, %l[error1])
		RSEQ_ASM_OP_CMPEQ(v, expect, %l[error2])
#पूर्ण_अगर
		RSEQ_ASM_OP_R_BAD_MEMCPY(dst, src, len)
		RSEQ_INJECT_ASM(5)
		RSEQ_ASM_OP_FINAL_STORE(newv, v, 3)
		RSEQ_INJECT_ASM(6)
		RSEQ_ASM_DEFINE_ABORT(4, पात)
		: /* gcc यंत्र जाओ करोes not allow outमाला_दो */
		: [cpu_id]		"r" (cpu),
		  [current_cpu_id]	"Qo" (__rseq_abi.cpu_id),
		  [rseq_cs]		"m" (__rseq_abi.rseq_cs),
		  [expect]		"r" (expect),
		  [v]			"Qo" (*v),
		  [newv]		"r" (newv),
		  [dst]			"r" (dst),
		  [src]			"r" (src),
		  [len]			"r" (len)
		  RSEQ_INJECT_INPUT
		: "memory", RSEQ_ASM_TMP_REG, RSEQ_ASM_TMP_REG_2
		: पात, cmpfail
#अगर_घोषित RSEQ_COMPARE_TWICE
		  , error1, error2
#पूर्ण_अगर
	);

	वापस 0;
पात:
	RSEQ_INJECT_FAILED
	वापस -1;
cmpfail:
	वापस 1;
#अगर_घोषित RSEQ_COMPARE_TWICE
error1:
	rseq_bug("cpu_id comparison failed");
error2:
	rseq_bug("expected value comparison failed");
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत __attribute__((always_अंतरभूत))
पूर्णांक rseq_cmpeqv_tryस_नकल_storev_release(पूर्णांकptr_t *v, पूर्णांकptr_t expect,
					 व्योम *dst, व्योम *src, माप_प्रकार len,
					 पूर्णांकptr_t newv, पूर्णांक cpu)
अणु
	RSEQ_INJECT_C(9)

	__यंत्र__ __अस्थिर__ जाओ (
		RSEQ_ASM_DEFINE_TABLE(1, 2f, 3f, 4f)
		RSEQ_ASM_DEFINE_EXIT_POINT(2f, %l[cmpfail])
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_DEFINE_EXIT_POINT(2f, %l[error1])
		RSEQ_ASM_DEFINE_EXIT_POINT(2f, %l[error2])
#पूर्ण_अगर
		RSEQ_ASM_STORE_RSEQ_CS(2, 1b, rseq_cs)
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, 4f)
		RSEQ_INJECT_ASM(3)
		RSEQ_ASM_OP_CMPEQ(v, expect, %l[cmpfail])
		RSEQ_INJECT_ASM(4)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, %l[error1])
		RSEQ_ASM_OP_CMPEQ(v, expect, %l[error2])
#पूर्ण_अगर
		RSEQ_ASM_OP_R_BAD_MEMCPY(dst, src, len)
		RSEQ_INJECT_ASM(5)
		RSEQ_ASM_OP_FINAL_STORE_RELEASE(newv, v, 3)
		RSEQ_INJECT_ASM(6)
		RSEQ_ASM_DEFINE_ABORT(4, पात)
		: /* gcc यंत्र जाओ करोes not allow outमाला_दो */
		: [cpu_id]		"r" (cpu),
		  [current_cpu_id]	"Qo" (__rseq_abi.cpu_id),
		  [rseq_cs]		"m" (__rseq_abi.rseq_cs),
		  [expect]		"r" (expect),
		  [v]			"Qo" (*v),
		  [newv]		"r" (newv),
		  [dst]			"r" (dst),
		  [src]			"r" (src),
		  [len]			"r" (len)
		  RSEQ_INJECT_INPUT
		: "memory", RSEQ_ASM_TMP_REG, RSEQ_ASM_TMP_REG_2
		: पात, cmpfail
#अगर_घोषित RSEQ_COMPARE_TWICE
		  , error1, error2
#पूर्ण_अगर
	);

	वापस 0;
पात:
	RSEQ_INJECT_FAILED
	वापस -1;
cmpfail:
	वापस 1;
#अगर_घोषित RSEQ_COMPARE_TWICE
error1:
	rseq_bug("cpu_id comparison failed");
error2:
	rseq_bug("expected value comparison failed");
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* !RSEQ_SKIP_FASTPATH */
