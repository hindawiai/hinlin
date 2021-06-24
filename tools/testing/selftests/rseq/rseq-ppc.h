<शैली गुरु>
/* SPDX-License-Identअगरier: LGPL-2.1 OR MIT */
/*
 * rseq-ppc.h
 *
 * (C) Copyright 2016-2018 - Mathieu Desnoyers <mathieu.desnoyers@efficios.com>
 * (C) Copyright 2016-2018 - Boqun Feng <boqun.feng@gmail.com>
 */

/*
 * RSEQ_SIG is used with the following trap inकाष्ठाion:
 *
 * घातerpc-be:    0f e5 00 0b           twui   r5,11
 * घातerpc64-le:  0b 00 e5 0f           twui   r5,11
 * घातerpc64-be:  0f e5 00 0b           twui   r5,11
 */

#घोषणा RSEQ_SIG	0x0fe5000b

#घोषणा rseq_smp_mb()		__यंत्र__ __अस्थिर__ ("sync"	::: "memory", "cc")
#घोषणा rseq_smp_lwsync()	__यंत्र__ __अस्थिर__ ("lwsync"	::: "memory", "cc")
#घोषणा rseq_smp_rmb()		rseq_smp_lwsync()
#घोषणा rseq_smp_wmb()		rseq_smp_lwsync()

#घोषणा rseq_smp_load_acquire(p)					\
__extension__ (अणु							\
	__typeof(*p) ____p1 = RSEQ_READ_ONCE(*p);			\
	rseq_smp_lwsync();						\
	____p1;								\
पूर्ण)

#घोषणा rseq_smp_acquire__after_ctrl_dep()	rseq_smp_lwsync()

#घोषणा rseq_smp_store_release(p, v)					\
करो अणु									\
	rseq_smp_lwsync();						\
	RSEQ_WRITE_ONCE(*p, v);						\
पूर्ण जबतक (0)

#अगर_घोषित RSEQ_SKIP_FASTPATH
#समावेश "rseq-skip.h"
#अन्यथा /* !RSEQ_SKIP_FASTPATH */

/*
 * The __rseq_cs_ptr_array and __rseq_cs sections can be used by debuggers to
 * better handle single-stepping through the restartable critical sections.
 */

#अगर_घोषित __PPC64__

#घोषणा STORE_WORD	"std "
#घोषणा LOAD_WORD	"ld "
#घोषणा LOADX_WORD	"ldx "
#घोषणा CMP_WORD	"cmpd "

#घोषणा __RSEQ_ASM_DEFINE_TABLE(label, version, flags,				\
			start_ip, post_commit_offset, पात_ip)			\
		".pushsection __rseq_cs, \"aw\"\n\t"				\
		".balign 32\n\t"						\
		__rseq_str(label) ":\n\t"					\
		".long " __rseq_str(version) ", " __rseq_str(flags) "\n\t"	\
		".quad " __rseq_str(start_ip) ", " __rseq_str(post_commit_offset) ", " __rseq_str(पात_ip) "\n\t" \
		".popsection\n\t"						\
		".pushsection __rseq_cs_ptr_array, \"aw\"\n\t"			\
		".quad " __rseq_str(label) "b\n\t"				\
		".popsection\n\t"

#घोषणा RSEQ_ASM_STORE_RSEQ_CS(label, cs_label, rseq_cs)			\
		RSEQ_INJECT_ASM(1)						\
		"lis %%r17, (" __rseq_str(cs_label) ")@highest\n\t"		\
		"ori %%r17, %%r17, (" __rseq_str(cs_label) ")@higher\n\t"	\
		"rldicr %%r17, %%r17, 32, 31\n\t"				\
		"oris %%r17, %%r17, (" __rseq_str(cs_label) ")@high\n\t"	\
		"ori %%r17, %%r17, (" __rseq_str(cs_label) ")@l\n\t"		\
		"std %%r17, %[" __rseq_str(rseq_cs) "]\n\t"			\
		__rseq_str(label) ":\n\t"

/*
 * Exit poपूर्णांकs of a rseq critical section consist of all inकाष्ठाions outside
 * of the critical section where a critical section can either branch to or
 * reach through the normal course of its execution. The पात IP and the
 * post-commit IP are alपढ़ोy part of the __rseq_cs section and should not be
 * explicitly defined as additional निकास poपूर्णांकs. Knowing all निकास poपूर्णांकs is
 * useful to assist debuggers stepping over the critical section.
 */
#घोषणा RSEQ_ASM_DEFINE_EXIT_POINT(start_ip, निकास_ip)			\
		".pushsection __rseq_exit_point_array, \"aw\"\n\t"	\
		".quad " __rseq_str(start_ip) ", " __rseq_str(निकास_ip) "\n\t" \
		".popsection\n\t"

#अन्यथा /* #अगर_घोषित __PPC64__ */

#घोषणा STORE_WORD	"stw "
#घोषणा LOAD_WORD	"lwz "
#घोषणा LOADX_WORD	"lwzx "
#घोषणा CMP_WORD	"cmpw "

#घोषणा __RSEQ_ASM_DEFINE_TABLE(label, version, flags,				\
			start_ip, post_commit_offset, पात_ip)			\
		".pushsection __rseq_cs, \"aw\"\n\t"				\
		".balign 32\n\t"						\
		__rseq_str(label) ":\n\t"					\
		".long " __rseq_str(version) ", " __rseq_str(flags) "\n\t"	\
		/* 32-bit only supported on BE */				\
		".long 0x0, " __rseq_str(start_ip) ", 0x0, " __rseq_str(post_commit_offset) ", 0x0, " __rseq_str(पात_ip) "\n\t" \
		".popsection\n\t"					\
		".pushsection __rseq_cs_ptr_array, \"aw\"\n\t"		\
		".long 0x0, " __rseq_str(label) "b\n\t"			\
		".popsection\n\t"

/*
 * Exit poपूर्णांकs of a rseq critical section consist of all inकाष्ठाions outside
 * of the critical section where a critical section can either branch to or
 * reach through the normal course of its execution. The पात IP and the
 * post-commit IP are alपढ़ोy part of the __rseq_cs section and should not be
 * explicitly defined as additional निकास poपूर्णांकs. Knowing all निकास poपूर्णांकs is
 * useful to assist debuggers stepping over the critical section.
 */
#घोषणा RSEQ_ASM_DEFINE_EXIT_POINT(start_ip, निकास_ip)				\
		".pushsection __rseq_exit_point_array, \"aw\"\n\t"		\
		/* 32-bit only supported on BE */				\
		".long 0x0, " __rseq_str(start_ip) ", 0x0, " __rseq_str(निकास_ip) "\n\t"	\
		".popsection\n\t"

#घोषणा RSEQ_ASM_STORE_RSEQ_CS(label, cs_label, rseq_cs)			\
		RSEQ_INJECT_ASM(1)						\
		"lis %%r17, (" __rseq_str(cs_label) ")@ha\n\t"			\
		"addi %%r17, %%r17, (" __rseq_str(cs_label) ")@l\n\t"		\
		"stw %%r17, %[" __rseq_str(rseq_cs) "]\n\t"			\
		__rseq_str(label) ":\n\t"

#पूर्ण_अगर /* #अगर_घोषित __PPC64__ */

#घोषणा RSEQ_ASM_DEFINE_TABLE(label, start_ip, post_commit_ip, पात_ip)	\
		__RSEQ_ASM_DEFINE_TABLE(label, 0x0, 0x0, start_ip,		\
					(post_commit_ip - start_ip), पात_ip)

#घोषणा RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, label)			\
		RSEQ_INJECT_ASM(2)						\
		"lwz %%r17, %[" __rseq_str(current_cpu_id) "]\n\t"		\
		"cmpw cr7, %[" __rseq_str(cpu_id) "], %%r17\n\t"		\
		"bne- cr7, " __rseq_str(label) "\n\t"

#घोषणा RSEQ_ASM_DEFINE_ABORT(label, पात_label)				\
		".pushsection __rseq_failure, \"ax\"\n\t"			\
		".long " __rseq_str(RSEQ_SIG) "\n\t"				\
		__rseq_str(label) ":\n\t"					\
		"b %l[" __rseq_str(पात_label) "]\n\t"				\
		".popsection\n\t"

/*
 * RSEQ_ASM_OPs: यंत्र operations क्रम rseq
 * 	RSEQ_ASM_OP_R_*: has hard-code रेजिस्टरs in it
 * 	RSEQ_ASM_OP_* (अन्यथा): करोesn't have hard-code रेजिस्टरs(unless cr7)
 */
#घोषणा RSEQ_ASM_OP_CMPEQ(var, expect, label)					\
		LOAD_WORD "%%r17, %[" __rseq_str(var) "]\n\t"			\
		CMP_WORD "cr7, %%r17, %[" __rseq_str(expect) "]\n\t"		\
		"bne- cr7, " __rseq_str(label) "\n\t"

#घोषणा RSEQ_ASM_OP_CMPNE(var, expectnot, label)				\
		LOAD_WORD "%%r17, %[" __rseq_str(var) "]\n\t"			\
		CMP_WORD "cr7, %%r17, %[" __rseq_str(expectnot) "]\n\t"		\
		"beq- cr7, " __rseq_str(label) "\n\t"

#घोषणा RSEQ_ASM_OP_STORE(value, var)						\
		STORE_WORD "%[" __rseq_str(value) "], %[" __rseq_str(var) "]\n\t"

/* Load @var to r17 */
#घोषणा RSEQ_ASM_OP_R_LOAD(var)							\
		LOAD_WORD "%%r17, %[" __rseq_str(var) "]\n\t"

/* Store r17 to @var */
#घोषणा RSEQ_ASM_OP_R_STORE(var)						\
		STORE_WORD "%%r17, %[" __rseq_str(var) "]\n\t"

/* Add @count to r17 */
#घोषणा RSEQ_ASM_OP_R_ADD(count)						\
		"add %%r17, %[" __rseq_str(count) "], %%r17\n\t"

/* Load (r17 + voffp) to r17 */
#घोषणा RSEQ_ASM_OP_R_LOADX(voffp)						\
		LOADX_WORD "%%r17, %[" __rseq_str(voffp) "], %%r17\n\t"

/* TODO: implement a faster स_नकल. */
#घोषणा RSEQ_ASM_OP_R_MEMCPY() \
		"cmpdi %%r19, 0\n\t" \
		"beq 333f\n\t" \
		"addi %%r20, %%r20, -1\n\t" \
		"addi %%r21, %%r21, -1\n\t" \
		"222:\n\t" \
		"lbzu %%r18, 1(%%r20)\n\t" \
		"stbu %%r18, 1(%%r21)\n\t" \
		"addi %%r19, %%r19, -1\n\t" \
		"cmpdi %%r19, 0\n\t" \
		"bne 222b\n\t" \
		"333:\n\t" \

#घोषणा RSEQ_ASM_OP_R_FINAL_STORE(var, post_commit_label)			\
		STORE_WORD "%%r17, %[" __rseq_str(var) "]\n\t"			\
		__rseq_str(post_commit_label) ":\n\t"

#घोषणा RSEQ_ASM_OP_FINAL_STORE(value, var, post_commit_label)			\
		STORE_WORD "%[" __rseq_str(value) "], %[" __rseq_str(var) "]\n\t" \
		__rseq_str(post_commit_label) ":\n\t"

अटल अंतरभूत __attribute__((always_अंतरभूत))
पूर्णांक rseq_cmpeqv_storev(पूर्णांकptr_t *v, पूर्णांकptr_t expect, पूर्णांकptr_t newv, पूर्णांक cpu)
अणु
	RSEQ_INJECT_C(9)

	__यंत्र__ __अस्थिर__ जाओ (
		RSEQ_ASM_DEFINE_TABLE(3, 1f, 2f, 4f) /* start, commit, पात */
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[cmpfail])
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error1])
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error2])
#पूर्ण_अगर
		/* Start rseq by storing table entry poपूर्णांकer पूर्णांकo rseq_cs. */
		RSEQ_ASM_STORE_RSEQ_CS(1, 3b, rseq_cs)
		/* cmp cpuid */
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, 4f)
		RSEQ_INJECT_ASM(3)
		/* cmp @v equal to @expect */
		RSEQ_ASM_OP_CMPEQ(v, expect, %l[cmpfail])
		RSEQ_INJECT_ASM(4)
#अगर_घोषित RSEQ_COMPARE_TWICE
		/* cmp cpuid */
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, %l[error1])
		/* cmp @v equal to @expect */
		RSEQ_ASM_OP_CMPEQ(v, expect, %l[error2])
#पूर्ण_अगर
		/* final store */
		RSEQ_ASM_OP_FINAL_STORE(newv, v, 2)
		RSEQ_INJECT_ASM(5)
		RSEQ_ASM_DEFINE_ABORT(4, पात)
		: /* gcc यंत्र जाओ करोes not allow outमाला_दो */
		: [cpu_id]		"r" (cpu),
		  [current_cpu_id]	"m" (__rseq_abi.cpu_id),
		  [rseq_cs]		"m" (__rseq_abi.rseq_cs),
		  [v]			"m" (*v),
		  [expect]		"r" (expect),
		  [newv]		"r" (newv)
		  RSEQ_INJECT_INPUT
		: "memory", "cc", "r17"
		  RSEQ_INJECT_CLOBBER
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
		RSEQ_ASM_DEFINE_TABLE(3, 1f, 2f, 4f) /* start, commit, पात */
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[cmpfail])
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error1])
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error2])
#पूर्ण_अगर
		/* Start rseq by storing table entry poपूर्णांकer पूर्णांकo rseq_cs. */
		RSEQ_ASM_STORE_RSEQ_CS(1, 3b, rseq_cs)
		/* cmp cpuid */
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, 4f)
		RSEQ_INJECT_ASM(3)
		/* cmp @v not equal to @expectnot */
		RSEQ_ASM_OP_CMPNE(v, expectnot, %l[cmpfail])
		RSEQ_INJECT_ASM(4)
#अगर_घोषित RSEQ_COMPARE_TWICE
		/* cmp cpuid */
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, %l[error1])
		/* cmp @v not equal to @expectnot */
		RSEQ_ASM_OP_CMPNE(v, expectnot, %l[error2])
#पूर्ण_अगर
		/* load the value of @v */
		RSEQ_ASM_OP_R_LOAD(v)
		/* store it in @load */
		RSEQ_ASM_OP_R_STORE(load)
		/* dereference voffp(v) */
		RSEQ_ASM_OP_R_LOADX(voffp)
		/* final store the value at voffp(v) */
		RSEQ_ASM_OP_R_FINAL_STORE(v, 2)
		RSEQ_INJECT_ASM(5)
		RSEQ_ASM_DEFINE_ABORT(4, पात)
		: /* gcc यंत्र जाओ करोes not allow outमाला_दो */
		: [cpu_id]		"r" (cpu),
		  [current_cpu_id]	"m" (__rseq_abi.cpu_id),
		  [rseq_cs]		"m" (__rseq_abi.rseq_cs),
		  /* final store input */
		  [v]			"m" (*v),
		  [expectnot]		"r" (expectnot),
		  [voffp]		"b" (voffp),
		  [load]		"m" (*load)
		  RSEQ_INJECT_INPUT
		: "memory", "cc", "r17"
		  RSEQ_INJECT_CLOBBER
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
		RSEQ_ASM_DEFINE_TABLE(3, 1f, 2f, 4f) /* start, commit, पात */
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error1])
#पूर्ण_अगर
		/* Start rseq by storing table entry poपूर्णांकer पूर्णांकo rseq_cs. */
		RSEQ_ASM_STORE_RSEQ_CS(1, 3b, rseq_cs)
		/* cmp cpuid */
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, 4f)
		RSEQ_INJECT_ASM(3)
#अगर_घोषित RSEQ_COMPARE_TWICE
		/* cmp cpuid */
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, %l[error1])
#पूर्ण_अगर
		/* load the value of @v */
		RSEQ_ASM_OP_R_LOAD(v)
		/* add @count to it */
		RSEQ_ASM_OP_R_ADD(count)
		/* final store */
		RSEQ_ASM_OP_R_FINAL_STORE(v, 2)
		RSEQ_INJECT_ASM(4)
		RSEQ_ASM_DEFINE_ABORT(4, पात)
		: /* gcc यंत्र जाओ करोes not allow outमाला_दो */
		: [cpu_id]		"r" (cpu),
		  [current_cpu_id]	"m" (__rseq_abi.cpu_id),
		  [rseq_cs]		"m" (__rseq_abi.rseq_cs),
		  /* final store input */
		  [v]			"m" (*v),
		  [count]		"r" (count)
		  RSEQ_INJECT_INPUT
		: "memory", "cc", "r17"
		  RSEQ_INJECT_CLOBBER
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
		RSEQ_ASM_DEFINE_TABLE(3, 1f, 2f, 4f) /* start, commit, पात */
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[cmpfail])
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error1])
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error2])
#पूर्ण_अगर
		/* Start rseq by storing table entry poपूर्णांकer पूर्णांकo rseq_cs. */
		RSEQ_ASM_STORE_RSEQ_CS(1, 3b, rseq_cs)
		/* cmp cpuid */
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, 4f)
		RSEQ_INJECT_ASM(3)
		/* cmp @v equal to @expect */
		RSEQ_ASM_OP_CMPEQ(v, expect, %l[cmpfail])
		RSEQ_INJECT_ASM(4)
#अगर_घोषित RSEQ_COMPARE_TWICE
		/* cmp cpuid */
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, %l[error1])
		/* cmp @v equal to @expect */
		RSEQ_ASM_OP_CMPEQ(v, expect, %l[error2])
#पूर्ण_अगर
		/* try store */
		RSEQ_ASM_OP_STORE(newv2, v2)
		RSEQ_INJECT_ASM(5)
		/* final store */
		RSEQ_ASM_OP_FINAL_STORE(newv, v, 2)
		RSEQ_INJECT_ASM(6)
		RSEQ_ASM_DEFINE_ABORT(4, पात)
		: /* gcc यंत्र जाओ करोes not allow outमाला_दो */
		: [cpu_id]		"r" (cpu),
		  [current_cpu_id]	"m" (__rseq_abi.cpu_id),
		  [rseq_cs]		"m" (__rseq_abi.rseq_cs),
		  /* try store input */
		  [v2]			"m" (*v2),
		  [newv2]		"r" (newv2),
		  /* final store input */
		  [v]			"m" (*v),
		  [expect]		"r" (expect),
		  [newv]		"r" (newv)
		  RSEQ_INJECT_INPUT
		: "memory", "cc", "r17"
		  RSEQ_INJECT_CLOBBER
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
		RSEQ_ASM_DEFINE_TABLE(3, 1f, 2f, 4f) /* start, commit, पात */
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[cmpfail])
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error1])
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error2])
#पूर्ण_अगर
		/* Start rseq by storing table entry poपूर्णांकer पूर्णांकo rseq_cs. */
		RSEQ_ASM_STORE_RSEQ_CS(1, 3b, rseq_cs)
		/* cmp cpuid */
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, 4f)
		RSEQ_INJECT_ASM(3)
		/* cmp @v equal to @expect */
		RSEQ_ASM_OP_CMPEQ(v, expect, %l[cmpfail])
		RSEQ_INJECT_ASM(4)
#अगर_घोषित RSEQ_COMPARE_TWICE
		/* cmp cpuid */
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, %l[error1])
		/* cmp @v equal to @expect */
		RSEQ_ASM_OP_CMPEQ(v, expect, %l[error2])
#पूर्ण_अगर
		/* try store */
		RSEQ_ASM_OP_STORE(newv2, v2)
		RSEQ_INJECT_ASM(5)
		/* क्रम 'release' */
		"lwsync\n\t"
		/* final store */
		RSEQ_ASM_OP_FINAL_STORE(newv, v, 2)
		RSEQ_INJECT_ASM(6)
		RSEQ_ASM_DEFINE_ABORT(4, पात)
		: /* gcc यंत्र जाओ करोes not allow outमाला_दो */
		: [cpu_id]		"r" (cpu),
		  [current_cpu_id]	"m" (__rseq_abi.cpu_id),
		  [rseq_cs]		"m" (__rseq_abi.rseq_cs),
		  /* try store input */
		  [v2]			"m" (*v2),
		  [newv2]		"r" (newv2),
		  /* final store input */
		  [v]			"m" (*v),
		  [expect]		"r" (expect),
		  [newv]		"r" (newv)
		  RSEQ_INJECT_INPUT
		: "memory", "cc", "r17"
		  RSEQ_INJECT_CLOBBER
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
		RSEQ_ASM_DEFINE_TABLE(3, 1f, 2f, 4f) /* start, commit, पात */
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[cmpfail])
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error1])
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error2])
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error3])
#पूर्ण_अगर
		/* Start rseq by storing table entry poपूर्णांकer पूर्णांकo rseq_cs. */
		RSEQ_ASM_STORE_RSEQ_CS(1, 3b, rseq_cs)
		/* cmp cpuid */
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, 4f)
		RSEQ_INJECT_ASM(3)
		/* cmp @v equal to @expect */
		RSEQ_ASM_OP_CMPEQ(v, expect, %l[cmpfail])
		RSEQ_INJECT_ASM(4)
		/* cmp @v2 equal to @expct2 */
		RSEQ_ASM_OP_CMPEQ(v2, expect2, %l[cmpfail])
		RSEQ_INJECT_ASM(5)
#अगर_घोषित RSEQ_COMPARE_TWICE
		/* cmp cpuid */
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, %l[error1])
		/* cmp @v equal to @expect */
		RSEQ_ASM_OP_CMPEQ(v, expect, %l[error2])
		/* cmp @v2 equal to @expct2 */
		RSEQ_ASM_OP_CMPEQ(v2, expect2, %l[error3])
#पूर्ण_अगर
		/* final store */
		RSEQ_ASM_OP_FINAL_STORE(newv, v, 2)
		RSEQ_INJECT_ASM(6)
		RSEQ_ASM_DEFINE_ABORT(4, पात)
		: /* gcc यंत्र जाओ करोes not allow outमाला_दो */
		: [cpu_id]		"r" (cpu),
		  [current_cpu_id]	"m" (__rseq_abi.cpu_id),
		  [rseq_cs]		"m" (__rseq_abi.rseq_cs),
		  /* cmp2 input */
		  [v2]			"m" (*v2),
		  [expect2]		"r" (expect2),
		  /* final store input */
		  [v]			"m" (*v),
		  [expect]		"r" (expect),
		  [newv]		"r" (newv)
		  RSEQ_INJECT_INPUT
		: "memory", "cc", "r17"
		  RSEQ_INJECT_CLOBBER
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
	rseq_bug("1st expected value comparison failed");
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
		RSEQ_ASM_DEFINE_TABLE(3, 1f, 2f, 4f) /* start, commit, पात */
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[cmpfail])
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error1])
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error2])
#पूर्ण_अगर
		/* setup क्रम mempcy */
		"mr %%r19, %[len]\n\t"
		"mr %%r20, %[src]\n\t"
		"mr %%r21, %[dst]\n\t"
		/* Start rseq by storing table entry poपूर्णांकer पूर्णांकo rseq_cs. */
		RSEQ_ASM_STORE_RSEQ_CS(1, 3b, rseq_cs)
		/* cmp cpuid */
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, 4f)
		RSEQ_INJECT_ASM(3)
		/* cmp @v equal to @expect */
		RSEQ_ASM_OP_CMPEQ(v, expect, %l[cmpfail])
		RSEQ_INJECT_ASM(4)
#अगर_घोषित RSEQ_COMPARE_TWICE
		/* cmp cpuid */
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, %l[error1])
		/* cmp @v equal to @expect */
		RSEQ_ASM_OP_CMPEQ(v, expect, %l[error2])
#पूर्ण_अगर
		/* try स_नकल */
		RSEQ_ASM_OP_R_MEMCPY()
		RSEQ_INJECT_ASM(5)
		/* final store */
		RSEQ_ASM_OP_FINAL_STORE(newv, v, 2)
		RSEQ_INJECT_ASM(6)
		/* tearकरोwn */
		RSEQ_ASM_DEFINE_ABORT(4, पात)
		: /* gcc यंत्र जाओ करोes not allow outमाला_दो */
		: [cpu_id]		"r" (cpu),
		  [current_cpu_id]	"m" (__rseq_abi.cpu_id),
		  [rseq_cs]		"m" (__rseq_abi.rseq_cs),
		  /* final store input */
		  [v]			"m" (*v),
		  [expect]		"r" (expect),
		  [newv]		"r" (newv),
		  /* try स_नकल input */
		  [dst]			"r" (dst),
		  [src]			"r" (src),
		  [len]			"r" (len)
		  RSEQ_INJECT_INPUT
		: "memory", "cc", "r17", "r18", "r19", "r20", "r21"
		  RSEQ_INJECT_CLOBBER
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
		RSEQ_ASM_DEFINE_TABLE(3, 1f, 2f, 4f) /* start, commit, पात */
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[cmpfail])
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error1])
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error2])
#पूर्ण_अगर
		/* setup क्रम mempcy */
		"mr %%r19, %[len]\n\t"
		"mr %%r20, %[src]\n\t"
		"mr %%r21, %[dst]\n\t"
		/* Start rseq by storing table entry poपूर्णांकer पूर्णांकo rseq_cs. */
		RSEQ_ASM_STORE_RSEQ_CS(1, 3b, rseq_cs)
		/* cmp cpuid */
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, 4f)
		RSEQ_INJECT_ASM(3)
		/* cmp @v equal to @expect */
		RSEQ_ASM_OP_CMPEQ(v, expect, %l[cmpfail])
		RSEQ_INJECT_ASM(4)
#अगर_घोषित RSEQ_COMPARE_TWICE
		/* cmp cpuid */
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, %l[error1])
		/* cmp @v equal to @expect */
		RSEQ_ASM_OP_CMPEQ(v, expect, %l[error2])
#पूर्ण_अगर
		/* try स_नकल */
		RSEQ_ASM_OP_R_MEMCPY()
		RSEQ_INJECT_ASM(5)
		/* क्रम 'release' */
		"lwsync\n\t"
		/* final store */
		RSEQ_ASM_OP_FINAL_STORE(newv, v, 2)
		RSEQ_INJECT_ASM(6)
		/* tearकरोwn */
		RSEQ_ASM_DEFINE_ABORT(4, पात)
		: /* gcc यंत्र जाओ करोes not allow outमाला_दो */
		: [cpu_id]		"r" (cpu),
		  [current_cpu_id]	"m" (__rseq_abi.cpu_id),
		  [rseq_cs]		"m" (__rseq_abi.rseq_cs),
		  /* final store input */
		  [v]			"m" (*v),
		  [expect]		"r" (expect),
		  [newv]		"r" (newv),
		  /* try स_नकल input */
		  [dst]			"r" (dst),
		  [src]			"r" (src),
		  [len]			"r" (len)
		  RSEQ_INJECT_INPUT
		: "memory", "cc", "r17", "r18", "r19", "r20", "r21"
		  RSEQ_INJECT_CLOBBER
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

#अघोषित STORE_WORD
#अघोषित LOAD_WORD
#अघोषित LOADX_WORD
#अघोषित CMP_WORD

#पूर्ण_अगर /* !RSEQ_SKIP_FASTPATH */
