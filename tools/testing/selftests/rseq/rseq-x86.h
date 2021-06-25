<शैली गुरु>
/* SPDX-License-Identअगरier: LGPL-2.1 OR MIT */
/*
 * rseq-x86.h
 *
 * (C) Copyright 2016-2018 - Mathieu Desnoyers <mathieu.desnoyers@efficios.com>
 */

#समावेश <मानक_निवेशt.h>

/*
 * RSEQ_SIG is used with the following reserved undefined inकाष्ठाions, which
 * trap in user-space:
 *
 * x86-32:    0f b9 3d 53 30 05 53      ud1    0x53053053,%edi
 * x86-64:    0f b9 3d 53 30 05 53      ud1    0x53053053(%rip),%edi
 */
#घोषणा RSEQ_SIG	0x53053053

/*
 * Due to a compiler optimization bug in gcc-8 with यंत्र जाओ and TLS यंत्र input
 * opeअक्रमs, we cannot use "m" input opeअक्रमs, and rather pass the __rseq_abi
 * address through a "r" input opeअक्रम.
 */

/* Offset of cpu_id and rseq_cs fields in काष्ठा rseq. */
#घोषणा RSEQ_CPU_ID_OFFSET	4
#घोषणा RSEQ_CS_OFFSET		8

#अगर_घोषित __x86_64__

#घोषणा rseq_smp_mb()	\
	__यंत्र__ __अस्थिर__ ("lock; addl $0,-128(%%rsp)" ::: "memory", "cc")
#घोषणा rseq_smp_rmb()	rseq_barrier()
#घोषणा rseq_smp_wmb()	rseq_barrier()

#घोषणा rseq_smp_load_acquire(p)					\
__extension__ (अणु							\
	__typeof(*p) ____p1 = RSEQ_READ_ONCE(*p);			\
	rseq_barrier();							\
	____p1;								\
पूर्ण)

#घोषणा rseq_smp_acquire__after_ctrl_dep()	rseq_smp_rmb()

#घोषणा rseq_smp_store_release(p, v)					\
करो अणु									\
	rseq_barrier();							\
	RSEQ_WRITE_ONCE(*p, v);						\
पूर्ण जबतक (0)

#अगर_घोषित RSEQ_SKIP_FASTPATH
#समावेश "rseq-skip.h"
#अन्यथा /* !RSEQ_SKIP_FASTPATH */

#घोषणा __RSEQ_ASM_DEFINE_TABLE(label, version, flags,			\
				start_ip, post_commit_offset, पात_ip)	\
		".pushsection __rseq_cs, \"aw\"\n\t"			\
		".balign 32\n\t"					\
		__rseq_str(label) ":\n\t"				\
		".long " __rseq_str(version) ", " __rseq_str(flags) "\n\t" \
		".quad " __rseq_str(start_ip) ", " __rseq_str(post_commit_offset) ", " __rseq_str(पात_ip) "\n\t" \
		".popsection\n\t"					\
		".pushsection __rseq_cs_ptr_array, \"aw\"\n\t"		\
		".quad " __rseq_str(label) "b\n\t"			\
		".popsection\n\t"


#घोषणा RSEQ_ASM_DEFINE_TABLE(label, start_ip, post_commit_ip, पात_ip) \
	__RSEQ_ASM_DEFINE_TABLE(label, 0x0, 0x0, start_ip,		\
				(post_commit_ip - start_ip), पात_ip)

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

#घोषणा RSEQ_ASM_STORE_RSEQ_CS(label, cs_label, rseq_cs)		\
		RSEQ_INJECT_ASM(1)					\
		"leaq " __rseq_str(cs_label) "(%%rip), %%rax\n\t"	\
		"movq %%rax, " __rseq_str(rseq_cs) "\n\t"		\
		__rseq_str(label) ":\n\t"

#घोषणा RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, label)		\
		RSEQ_INJECT_ASM(2)					\
		"cmpl %[" __rseq_str(cpu_id) "], " __rseq_str(current_cpu_id) "\n\t" \
		"jnz " __rseq_str(label) "\n\t"

#घोषणा RSEQ_ASM_DEFINE_ABORT(label, tearकरोwn, पात_label)		\
		".pushsection __rseq_failure, \"ax\"\n\t"		\
		/* Disassembler-मित्रly signature: ud1 <sig>(%rip),%edi. */ \
		".byte 0x0f, 0xb9, 0x3d\n\t"				\
		".long " __rseq_str(RSEQ_SIG) "\n\t"			\
		__rseq_str(label) ":\n\t"				\
		tearकरोwn						\
		"jmp %l[" __rseq_str(पात_label) "]\n\t"		\
		".popsection\n\t"

#घोषणा RSEQ_ASM_DEFINE_CMPFAIL(label, tearकरोwn, cmpfail_label)		\
		".pushsection __rseq_failure, \"ax\"\n\t"		\
		__rseq_str(label) ":\n\t"				\
		tearकरोwn						\
		"jmp %l[" __rseq_str(cmpfail_label) "]\n\t"		\
		".popsection\n\t"

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
		RSEQ_ASM_STORE_RSEQ_CS(1, 3b, RSEQ_CS_OFFSET(%[rseq_abi]))
		RSEQ_ASM_CMP_CPU_ID(cpu_id, RSEQ_CPU_ID_OFFSET(%[rseq_abi]), 4f)
		RSEQ_INJECT_ASM(3)
		"cmpq %[v], %[expect]\n\t"
		"jnz %l[cmpfail]\n\t"
		RSEQ_INJECT_ASM(4)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, RSEQ_CPU_ID_OFFSET(%[rseq_abi]), %l[error1])
		"cmpq %[v], %[expect]\n\t"
		"jnz %l[error2]\n\t"
#पूर्ण_अगर
		/* final store */
		"movq %[newv], %[v]\n\t"
		"2:\n\t"
		RSEQ_INJECT_ASM(5)
		RSEQ_ASM_DEFINE_ABORT(4, "", पात)
		: /* gcc यंत्र जाओ करोes not allow outमाला_दो */
		: [cpu_id]		"r" (cpu),
		  [rseq_abi]		"r" (&__rseq_abi),
		  [v]			"m" (*v),
		  [expect]		"r" (expect),
		  [newv]		"r" (newv)
		: "memory", "cc", "rax"
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

/*
 * Compare @v against @expectnot. When it करोes _not_ match, load @v
 * पूर्णांकo @load, and store the content of *@v + voffp पूर्णांकo @v.
 */
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
		RSEQ_ASM_STORE_RSEQ_CS(1, 3b, RSEQ_CS_OFFSET(%[rseq_abi]))
		RSEQ_ASM_CMP_CPU_ID(cpu_id, RSEQ_CPU_ID_OFFSET(%[rseq_abi]), 4f)
		RSEQ_INJECT_ASM(3)
		"movq %[v], %%rbx\n\t"
		"cmpq %%rbx, %[expectnot]\n\t"
		"je %l[cmpfail]\n\t"
		RSEQ_INJECT_ASM(4)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, RSEQ_CPU_ID_OFFSET(%[rseq_abi]), %l[error1])
		"movq %[v], %%rbx\n\t"
		"cmpq %%rbx, %[expectnot]\n\t"
		"je %l[error2]\n\t"
#पूर्ण_अगर
		"movq %%rbx, %[load]\n\t"
		"addq %[voffp], %%rbx\n\t"
		"movq (%%rbx), %%rbx\n\t"
		/* final store */
		"movq %%rbx, %[v]\n\t"
		"2:\n\t"
		RSEQ_INJECT_ASM(5)
		RSEQ_ASM_DEFINE_ABORT(4, "", पात)
		: /* gcc यंत्र जाओ करोes not allow outमाला_दो */
		: [cpu_id]		"r" (cpu),
		  [rseq_abi]		"r" (&__rseq_abi),
		  /* final store input */
		  [v]			"m" (*v),
		  [expectnot]		"r" (expectnot),
		  [voffp]		"er" (voffp),
		  [load]		"m" (*load)
		: "memory", "cc", "rax", "rbx"
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
		RSEQ_ASM_STORE_RSEQ_CS(1, 3b, RSEQ_CS_OFFSET(%[rseq_abi]))
		RSEQ_ASM_CMP_CPU_ID(cpu_id, RSEQ_CPU_ID_OFFSET(%[rseq_abi]), 4f)
		RSEQ_INJECT_ASM(3)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, RSEQ_CPU_ID_OFFSET(%[rseq_abi]), %l[error1])
#पूर्ण_अगर
		/* final store */
		"addq %[count], %[v]\n\t"
		"2:\n\t"
		RSEQ_INJECT_ASM(4)
		RSEQ_ASM_DEFINE_ABORT(4, "", पात)
		: /* gcc यंत्र जाओ करोes not allow outमाला_दो */
		: [cpu_id]		"r" (cpu),
		  [rseq_abi]		"r" (&__rseq_abi),
		  /* final store input */
		  [v]			"m" (*v),
		  [count]		"er" (count)
		: "memory", "cc", "rax"
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

#घोषणा RSEQ_ARCH_HAS_OFFSET_DEREF_ADDV

/*
 *   pval = *(ptr+off)
 *  *pval += inc;
 */
अटल अंतरभूत __attribute__((always_अंतरभूत))
पूर्णांक rseq_offset_deref_addv(पूर्णांकptr_t *ptr, off_t off, पूर्णांकptr_t inc, पूर्णांक cpu)
अणु
	RSEQ_INJECT_C(9)

	__यंत्र__ __अस्थिर__ जाओ (
		RSEQ_ASM_DEFINE_TABLE(3, 1f, 2f, 4f) /* start, commit, पात */
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error1])
#पूर्ण_अगर
		/* Start rseq by storing table entry poपूर्णांकer पूर्णांकo rseq_cs. */
		RSEQ_ASM_STORE_RSEQ_CS(1, 3b, RSEQ_CS_OFFSET(%[rseq_abi]))
		RSEQ_ASM_CMP_CPU_ID(cpu_id, RSEQ_CPU_ID_OFFSET(%[rseq_abi]), 4f)
		RSEQ_INJECT_ASM(3)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, RSEQ_CPU_ID_OFFSET(%[rseq_abi]), %l[error1])
#पूर्ण_अगर
		/* get p+v */
		"movq %[ptr], %%rbx\n\t"
		"addq %[off], %%rbx\n\t"
		/* get pv */
		"movq (%%rbx), %%rcx\n\t"
		/* *pv += inc */
		"addq %[inc], (%%rcx)\n\t"
		"2:\n\t"
		RSEQ_INJECT_ASM(4)
		RSEQ_ASM_DEFINE_ABORT(4, "", पात)
		: /* gcc यंत्र जाओ करोes not allow outमाला_दो */
		: [cpu_id]		"r" (cpu),
		  [rseq_abi]		"r" (&__rseq_abi),
		  /* final store input */
		  [ptr]			"m" (*ptr),
		  [off]			"er" (off),
		  [inc]			"er" (inc)
		: "memory", "cc", "rax", "rbx", "rcx"
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
		RSEQ_ASM_STORE_RSEQ_CS(1, 3b, RSEQ_CS_OFFSET(%[rseq_abi]))
		RSEQ_ASM_CMP_CPU_ID(cpu_id, RSEQ_CPU_ID_OFFSET(%[rseq_abi]), 4f)
		RSEQ_INJECT_ASM(3)
		"cmpq %[v], %[expect]\n\t"
		"jnz %l[cmpfail]\n\t"
		RSEQ_INJECT_ASM(4)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, RSEQ_CPU_ID_OFFSET(%[rseq_abi]), %l[error1])
		"cmpq %[v], %[expect]\n\t"
		"jnz %l[error2]\n\t"
#पूर्ण_अगर
		/* try store */
		"movq %[newv2], %[v2]\n\t"
		RSEQ_INJECT_ASM(5)
		/* final store */
		"movq %[newv], %[v]\n\t"
		"2:\n\t"
		RSEQ_INJECT_ASM(6)
		RSEQ_ASM_DEFINE_ABORT(4, "", पात)
		: /* gcc यंत्र जाओ करोes not allow outमाला_दो */
		: [cpu_id]		"r" (cpu),
		  [rseq_abi]		"r" (&__rseq_abi),
		  /* try store input */
		  [v2]			"m" (*v2),
		  [newv2]		"r" (newv2),
		  /* final store input */
		  [v]			"m" (*v),
		  [expect]		"r" (expect),
		  [newv]		"r" (newv)
		: "memory", "cc", "rax"
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

/* x86-64 is TSO. */
अटल अंतरभूत __attribute__((always_अंतरभूत))
पूर्णांक rseq_cmpeqv_trystorev_storev_release(पूर्णांकptr_t *v, पूर्णांकptr_t expect,
					 पूर्णांकptr_t *v2, पूर्णांकptr_t newv2,
					 पूर्णांकptr_t newv, पूर्णांक cpu)
अणु
	वापस rseq_cmpeqv_trystorev_storev(v, expect, v2, newv2, newv, cpu);
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
		RSEQ_ASM_STORE_RSEQ_CS(1, 3b, RSEQ_CS_OFFSET(%[rseq_abi]))
		RSEQ_ASM_CMP_CPU_ID(cpu_id, RSEQ_CPU_ID_OFFSET(%[rseq_abi]), 4f)
		RSEQ_INJECT_ASM(3)
		"cmpq %[v], %[expect]\n\t"
		"jnz %l[cmpfail]\n\t"
		RSEQ_INJECT_ASM(4)
		"cmpq %[v2], %[expect2]\n\t"
		"jnz %l[cmpfail]\n\t"
		RSEQ_INJECT_ASM(5)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, RSEQ_CPU_ID_OFFSET(%[rseq_abi]), %l[error1])
		"cmpq %[v], %[expect]\n\t"
		"jnz %l[error2]\n\t"
		"cmpq %[v2], %[expect2]\n\t"
		"jnz %l[error3]\n\t"
#पूर्ण_अगर
		/* final store */
		"movq %[newv], %[v]\n\t"
		"2:\n\t"
		RSEQ_INJECT_ASM(6)
		RSEQ_ASM_DEFINE_ABORT(4, "", पात)
		: /* gcc यंत्र जाओ करोes not allow outमाला_दो */
		: [cpu_id]		"r" (cpu),
		  [rseq_abi]		"r" (&__rseq_abi),
		  /* cmp2 input */
		  [v2]			"m" (*v2),
		  [expect2]		"r" (expect2),
		  /* final store input */
		  [v]			"m" (*v),
		  [expect]		"r" (expect),
		  [newv]		"r" (newv)
		: "memory", "cc", "rax"
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
	uपूर्णांक64_t rseq_scratch[3];

	RSEQ_INJECT_C(9)

	__यंत्र__ __अस्थिर__ जाओ (
		RSEQ_ASM_DEFINE_TABLE(3, 1f, 2f, 4f) /* start, commit, पात */
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[cmpfail])
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error1])
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error2])
#पूर्ण_अगर
		"movq %[src], %[rseq_scratch0]\n\t"
		"movq %[dst], %[rseq_scratch1]\n\t"
		"movq %[len], %[rseq_scratch2]\n\t"
		/* Start rseq by storing table entry poपूर्णांकer पूर्णांकo rseq_cs. */
		RSEQ_ASM_STORE_RSEQ_CS(1, 3b, RSEQ_CS_OFFSET(%[rseq_abi]))
		RSEQ_ASM_CMP_CPU_ID(cpu_id, RSEQ_CPU_ID_OFFSET(%[rseq_abi]), 4f)
		RSEQ_INJECT_ASM(3)
		"cmpq %[v], %[expect]\n\t"
		"jnz 5f\n\t"
		RSEQ_INJECT_ASM(4)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, RSEQ_CPU_ID_OFFSET(%[rseq_abi]), 6f)
		"cmpq %[v], %[expect]\n\t"
		"jnz 7f\n\t"
#पूर्ण_अगर
		/* try स_नकल */
		"test %[len], %[len]\n\t" \
		"jz 333f\n\t" \
		"222:\n\t" \
		"movb (%[src]), %%al\n\t" \
		"movb %%al, (%[dst])\n\t" \
		"inc %[src]\n\t" \
		"inc %[dst]\n\t" \
		"dec %[len]\n\t" \
		"jnz 222b\n\t" \
		"333:\n\t" \
		RSEQ_INJECT_ASM(5)
		/* final store */
		"movq %[newv], %[v]\n\t"
		"2:\n\t"
		RSEQ_INJECT_ASM(6)
		/* tearकरोwn */
		"movq %[rseq_scratch2], %[len]\n\t"
		"movq %[rseq_scratch1], %[dst]\n\t"
		"movq %[rseq_scratch0], %[src]\n\t"
		RSEQ_ASM_DEFINE_ABORT(4,
			"movq %[rseq_scratch2], %[len]\n\t"
			"movq %[rseq_scratch1], %[dst]\n\t"
			"movq %[rseq_scratch0], %[src]\n\t",
			पात)
		RSEQ_ASM_DEFINE_CMPFAIL(5,
			"movq %[rseq_scratch2], %[len]\n\t"
			"movq %[rseq_scratch1], %[dst]\n\t"
			"movq %[rseq_scratch0], %[src]\n\t",
			cmpfail)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_DEFINE_CMPFAIL(6,
			"movq %[rseq_scratch2], %[len]\n\t"
			"movq %[rseq_scratch1], %[dst]\n\t"
			"movq %[rseq_scratch0], %[src]\n\t",
			error1)
		RSEQ_ASM_DEFINE_CMPFAIL(7,
			"movq %[rseq_scratch2], %[len]\n\t"
			"movq %[rseq_scratch1], %[dst]\n\t"
			"movq %[rseq_scratch0], %[src]\n\t",
			error2)
#पूर्ण_अगर
		: /* gcc यंत्र जाओ करोes not allow outमाला_दो */
		: [cpu_id]		"r" (cpu),
		  [rseq_abi]		"r" (&__rseq_abi),
		  /* final store input */
		  [v]			"m" (*v),
		  [expect]		"r" (expect),
		  [newv]		"r" (newv),
		  /* try स_नकल input */
		  [dst]			"r" (dst),
		  [src]			"r" (src),
		  [len]			"r" (len),
		  [rseq_scratch0]	"m" (rseq_scratch[0]),
		  [rseq_scratch1]	"m" (rseq_scratch[1]),
		  [rseq_scratch2]	"m" (rseq_scratch[2])
		: "memory", "cc", "rax"
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

/* x86-64 is TSO. */
अटल अंतरभूत __attribute__((always_अंतरभूत))
पूर्णांक rseq_cmpeqv_tryस_नकल_storev_release(पूर्णांकptr_t *v, पूर्णांकptr_t expect,
					 व्योम *dst, व्योम *src, माप_प्रकार len,
					 पूर्णांकptr_t newv, पूर्णांक cpu)
अणु
	वापस rseq_cmpeqv_tryस_नकल_storev(v, expect, dst, src, len,
					    newv, cpu);
पूर्ण

#पूर्ण_अगर /* !RSEQ_SKIP_FASTPATH */

#या_अगर __i386__

#घोषणा rseq_smp_mb()	\
	__यंत्र__ __अस्थिर__ ("lock; addl $0,-128(%%esp)" ::: "memory", "cc")
#घोषणा rseq_smp_rmb()	\
	__यंत्र__ __अस्थिर__ ("lock; addl $0,-128(%%esp)" ::: "memory", "cc")
#घोषणा rseq_smp_wmb()	\
	__यंत्र__ __अस्थिर__ ("lock; addl $0,-128(%%esp)" ::: "memory", "cc")

#घोषणा rseq_smp_load_acquire(p)					\
__extension__ (अणु							\
	__typeof(*p) ____p1 = RSEQ_READ_ONCE(*p);			\
	rseq_smp_mb();							\
	____p1;								\
पूर्ण)

#घोषणा rseq_smp_acquire__after_ctrl_dep()	rseq_smp_rmb()

#घोषणा rseq_smp_store_release(p, v)					\
करो अणु									\
	rseq_smp_mb();							\
	RSEQ_WRITE_ONCE(*p, v);						\
पूर्ण जबतक (0)

#अगर_घोषित RSEQ_SKIP_FASTPATH
#समावेश "rseq-skip.h"
#अन्यथा /* !RSEQ_SKIP_FASTPATH */

/*
 * Use eax as scratch रेजिस्टर and take memory opeअक्रमs as input to
 * lessen रेजिस्टर pressure. Especially needed when compiling in O0.
 */
#घोषणा __RSEQ_ASM_DEFINE_TABLE(label, version, flags,			\
				start_ip, post_commit_offset, पात_ip)	\
		".pushsection __rseq_cs, \"aw\"\n\t"			\
		".balign 32\n\t"					\
		__rseq_str(label) ":\n\t"				\
		".long " __rseq_str(version) ", " __rseq_str(flags) "\n\t" \
		".long " __rseq_str(start_ip) ", 0x0, " __rseq_str(post_commit_offset) ", 0x0, " __rseq_str(पात_ip) ", 0x0\n\t" \
		".popsection\n\t"					\
		".pushsection __rseq_cs_ptr_array, \"aw\"\n\t"		\
		".long " __rseq_str(label) "b, 0x0\n\t"			\
		".popsection\n\t"

#घोषणा RSEQ_ASM_DEFINE_TABLE(label, start_ip, post_commit_ip, पात_ip) \
	__RSEQ_ASM_DEFINE_TABLE(label, 0x0, 0x0, start_ip,		\
				(post_commit_ip - start_ip), पात_ip)

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
		".long " __rseq_str(start_ip) ", 0x0, " __rseq_str(निकास_ip) ", 0x0\n\t" \
		".popsection\n\t"

#घोषणा RSEQ_ASM_STORE_RSEQ_CS(label, cs_label, rseq_cs)		\
		RSEQ_INJECT_ASM(1)					\
		"movl $" __rseq_str(cs_label) ", " __rseq_str(rseq_cs) "\n\t"	\
		__rseq_str(label) ":\n\t"

#घोषणा RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, label)		\
		RSEQ_INJECT_ASM(2)					\
		"cmpl %[" __rseq_str(cpu_id) "], " __rseq_str(current_cpu_id) "\n\t" \
		"jnz " __rseq_str(label) "\n\t"

#घोषणा RSEQ_ASM_DEFINE_ABORT(label, tearकरोwn, पात_label)		\
		".pushsection __rseq_failure, \"ax\"\n\t"		\
		/* Disassembler-मित्रly signature: ud1 <sig>,%edi. */	\
		".byte 0x0f, 0xb9, 0x3d\n\t"				\
		".long " __rseq_str(RSEQ_SIG) "\n\t"			\
		__rseq_str(label) ":\n\t"				\
		tearकरोwn						\
		"jmp %l[" __rseq_str(पात_label) "]\n\t"		\
		".popsection\n\t"

#घोषणा RSEQ_ASM_DEFINE_CMPFAIL(label, tearकरोwn, cmpfail_label)		\
		".pushsection __rseq_failure, \"ax\"\n\t"		\
		__rseq_str(label) ":\n\t"				\
		tearकरोwn						\
		"jmp %l[" __rseq_str(cmpfail_label) "]\n\t"		\
		".popsection\n\t"

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
		RSEQ_ASM_STORE_RSEQ_CS(1, 3b, RSEQ_CS_OFFSET(%[rseq_abi]))
		RSEQ_ASM_CMP_CPU_ID(cpu_id, RSEQ_CPU_ID_OFFSET(%[rseq_abi]), 4f)
		RSEQ_INJECT_ASM(3)
		"cmpl %[v], %[expect]\n\t"
		"jnz %l[cmpfail]\n\t"
		RSEQ_INJECT_ASM(4)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, RSEQ_CPU_ID_OFFSET(%[rseq_abi]), %l[error1])
		"cmpl %[v], %[expect]\n\t"
		"jnz %l[error2]\n\t"
#पूर्ण_अगर
		/* final store */
		"movl %[newv], %[v]\n\t"
		"2:\n\t"
		RSEQ_INJECT_ASM(5)
		RSEQ_ASM_DEFINE_ABORT(4, "", पात)
		: /* gcc यंत्र जाओ करोes not allow outमाला_दो */
		: [cpu_id]		"r" (cpu),
		  [rseq_abi]		"r" (&__rseq_abi),
		  [v]			"m" (*v),
		  [expect]		"r" (expect),
		  [newv]		"r" (newv)
		: "memory", "cc", "eax"
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

/*
 * Compare @v against @expectnot. When it करोes _not_ match, load @v
 * पूर्णांकo @load, and store the content of *@v + voffp पूर्णांकo @v.
 */
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
		RSEQ_ASM_STORE_RSEQ_CS(1, 3b, RSEQ_CS_OFFSET(%[rseq_abi]))
		RSEQ_ASM_CMP_CPU_ID(cpu_id, RSEQ_CPU_ID_OFFSET(%[rseq_abi]), 4f)
		RSEQ_INJECT_ASM(3)
		"movl %[v], %%ebx\n\t"
		"cmpl %%ebx, %[expectnot]\n\t"
		"je %l[cmpfail]\n\t"
		RSEQ_INJECT_ASM(4)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, RSEQ_CPU_ID_OFFSET(%[rseq_abi]), %l[error1])
		"movl %[v], %%ebx\n\t"
		"cmpl %%ebx, %[expectnot]\n\t"
		"je %l[error2]\n\t"
#पूर्ण_अगर
		"movl %%ebx, %[load]\n\t"
		"addl %[voffp], %%ebx\n\t"
		"movl (%%ebx), %%ebx\n\t"
		/* final store */
		"movl %%ebx, %[v]\n\t"
		"2:\n\t"
		RSEQ_INJECT_ASM(5)
		RSEQ_ASM_DEFINE_ABORT(4, "", पात)
		: /* gcc यंत्र जाओ करोes not allow outमाला_दो */
		: [cpu_id]		"r" (cpu),
		  [rseq_abi]		"r" (&__rseq_abi),
		  /* final store input */
		  [v]			"m" (*v),
		  [expectnot]		"r" (expectnot),
		  [voffp]		"ir" (voffp),
		  [load]		"m" (*load)
		: "memory", "cc", "eax", "ebx"
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
		RSEQ_ASM_STORE_RSEQ_CS(1, 3b, RSEQ_CS_OFFSET(%[rseq_abi]))
		RSEQ_ASM_CMP_CPU_ID(cpu_id, RSEQ_CPU_ID_OFFSET(%[rseq_abi]), 4f)
		RSEQ_INJECT_ASM(3)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, RSEQ_CPU_ID_OFFSET(%[rseq_abi]), %l[error1])
#पूर्ण_अगर
		/* final store */
		"addl %[count], %[v]\n\t"
		"2:\n\t"
		RSEQ_INJECT_ASM(4)
		RSEQ_ASM_DEFINE_ABORT(4, "", पात)
		: /* gcc यंत्र जाओ करोes not allow outमाला_दो */
		: [cpu_id]		"r" (cpu),
		  [rseq_abi]		"r" (&__rseq_abi),
		  /* final store input */
		  [v]			"m" (*v),
		  [count]		"ir" (count)
		: "memory", "cc", "eax"
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
		RSEQ_ASM_STORE_RSEQ_CS(1, 3b, RSEQ_CS_OFFSET(%[rseq_abi]))
		RSEQ_ASM_CMP_CPU_ID(cpu_id, RSEQ_CPU_ID_OFFSET(%[rseq_abi]), 4f)
		RSEQ_INJECT_ASM(3)
		"cmpl %[v], %[expect]\n\t"
		"jnz %l[cmpfail]\n\t"
		RSEQ_INJECT_ASM(4)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, RSEQ_CPU_ID_OFFSET(%[rseq_abi]), %l[error1])
		"cmpl %[v], %[expect]\n\t"
		"jnz %l[error2]\n\t"
#पूर्ण_अगर
		/* try store */
		"movl %[newv2], %%eax\n\t"
		"movl %%eax, %[v2]\n\t"
		RSEQ_INJECT_ASM(5)
		/* final store */
		"movl %[newv], %[v]\n\t"
		"2:\n\t"
		RSEQ_INJECT_ASM(6)
		RSEQ_ASM_DEFINE_ABORT(4, "", पात)
		: /* gcc यंत्र जाओ करोes not allow outमाला_दो */
		: [cpu_id]		"r" (cpu),
		  [rseq_abi]		"r" (&__rseq_abi),
		  /* try store input */
		  [v2]			"m" (*v2),
		  [newv2]		"m" (newv2),
		  /* final store input */
		  [v]			"m" (*v),
		  [expect]		"r" (expect),
		  [newv]		"r" (newv)
		: "memory", "cc", "eax"
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
		RSEQ_ASM_STORE_RSEQ_CS(1, 3b, RSEQ_CS_OFFSET(%[rseq_abi]))
		RSEQ_ASM_CMP_CPU_ID(cpu_id, RSEQ_CPU_ID_OFFSET(%[rseq_abi]), 4f)
		RSEQ_INJECT_ASM(3)
		"movl %[expect], %%eax\n\t"
		"cmpl %[v], %%eax\n\t"
		"jnz %l[cmpfail]\n\t"
		RSEQ_INJECT_ASM(4)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, RSEQ_CPU_ID_OFFSET(%[rseq_abi]), %l[error1])
		"movl %[expect], %%eax\n\t"
		"cmpl %[v], %%eax\n\t"
		"jnz %l[error2]\n\t"
#पूर्ण_अगर
		/* try store */
		"movl %[newv2], %[v2]\n\t"
		RSEQ_INJECT_ASM(5)
		"lock; addl $0,-128(%%esp)\n\t"
		/* final store */
		"movl %[newv], %[v]\n\t"
		"2:\n\t"
		RSEQ_INJECT_ASM(6)
		RSEQ_ASM_DEFINE_ABORT(4, "", पात)
		: /* gcc यंत्र जाओ करोes not allow outमाला_दो */
		: [cpu_id]		"r" (cpu),
		  [rseq_abi]		"r" (&__rseq_abi),
		  /* try store input */
		  [v2]			"m" (*v2),
		  [newv2]		"r" (newv2),
		  /* final store input */
		  [v]			"m" (*v),
		  [expect]		"m" (expect),
		  [newv]		"r" (newv)
		: "memory", "cc", "eax"
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
		RSEQ_ASM_STORE_RSEQ_CS(1, 3b, RSEQ_CS_OFFSET(%[rseq_abi]))
		RSEQ_ASM_CMP_CPU_ID(cpu_id, RSEQ_CPU_ID_OFFSET(%[rseq_abi]), 4f)
		RSEQ_INJECT_ASM(3)
		"cmpl %[v], %[expect]\n\t"
		"jnz %l[cmpfail]\n\t"
		RSEQ_INJECT_ASM(4)
		"cmpl %[expect2], %[v2]\n\t"
		"jnz %l[cmpfail]\n\t"
		RSEQ_INJECT_ASM(5)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, RSEQ_CPU_ID_OFFSET(%[rseq_abi]), %l[error1])
		"cmpl %[v], %[expect]\n\t"
		"jnz %l[error2]\n\t"
		"cmpl %[expect2], %[v2]\n\t"
		"jnz %l[error3]\n\t"
#पूर्ण_अगर
		"movl %[newv], %%eax\n\t"
		/* final store */
		"movl %%eax, %[v]\n\t"
		"2:\n\t"
		RSEQ_INJECT_ASM(6)
		RSEQ_ASM_DEFINE_ABORT(4, "", पात)
		: /* gcc यंत्र जाओ करोes not allow outमाला_दो */
		: [cpu_id]		"r" (cpu),
		  [rseq_abi]		"r" (&__rseq_abi),
		  /* cmp2 input */
		  [v2]			"m" (*v2),
		  [expect2]		"r" (expect2),
		  /* final store input */
		  [v]			"m" (*v),
		  [expect]		"r" (expect),
		  [newv]		"m" (newv)
		: "memory", "cc", "eax"
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

/* TODO: implement a faster स_नकल. */
अटल अंतरभूत __attribute__((always_अंतरभूत))
पूर्णांक rseq_cmpeqv_tryस_नकल_storev(पूर्णांकptr_t *v, पूर्णांकptr_t expect,
				 व्योम *dst, व्योम *src, माप_प्रकार len,
				 पूर्णांकptr_t newv, पूर्णांक cpu)
अणु
	uपूर्णांक32_t rseq_scratch[3];

	RSEQ_INJECT_C(9)

	__यंत्र__ __अस्थिर__ जाओ (
		RSEQ_ASM_DEFINE_TABLE(3, 1f, 2f, 4f) /* start, commit, पात */
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[cmpfail])
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error1])
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error2])
#पूर्ण_अगर
		"movl %[src], %[rseq_scratch0]\n\t"
		"movl %[dst], %[rseq_scratch1]\n\t"
		"movl %[len], %[rseq_scratch2]\n\t"
		/* Start rseq by storing table entry poपूर्णांकer पूर्णांकo rseq_cs. */
		RSEQ_ASM_STORE_RSEQ_CS(1, 3b, RSEQ_CS_OFFSET(%[rseq_abi]))
		RSEQ_ASM_CMP_CPU_ID(cpu_id, RSEQ_CPU_ID_OFFSET(%[rseq_abi]), 4f)
		RSEQ_INJECT_ASM(3)
		"movl %[expect], %%eax\n\t"
		"cmpl %%eax, %[v]\n\t"
		"jnz 5f\n\t"
		RSEQ_INJECT_ASM(4)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, RSEQ_CPU_ID_OFFSET(%[rseq_abi]), 6f)
		"movl %[expect], %%eax\n\t"
		"cmpl %%eax, %[v]\n\t"
		"jnz 7f\n\t"
#पूर्ण_अगर
		/* try स_नकल */
		"test %[len], %[len]\n\t" \
		"jz 333f\n\t" \
		"222:\n\t" \
		"movb (%[src]), %%al\n\t" \
		"movb %%al, (%[dst])\n\t" \
		"inc %[src]\n\t" \
		"inc %[dst]\n\t" \
		"dec %[len]\n\t" \
		"jnz 222b\n\t" \
		"333:\n\t" \
		RSEQ_INJECT_ASM(5)
		"movl %[newv], %%eax\n\t"
		/* final store */
		"movl %%eax, %[v]\n\t"
		"2:\n\t"
		RSEQ_INJECT_ASM(6)
		/* tearकरोwn */
		"movl %[rseq_scratch2], %[len]\n\t"
		"movl %[rseq_scratch1], %[dst]\n\t"
		"movl %[rseq_scratch0], %[src]\n\t"
		RSEQ_ASM_DEFINE_ABORT(4,
			"movl %[rseq_scratch2], %[len]\n\t"
			"movl %[rseq_scratch1], %[dst]\n\t"
			"movl %[rseq_scratch0], %[src]\n\t",
			पात)
		RSEQ_ASM_DEFINE_CMPFAIL(5,
			"movl %[rseq_scratch2], %[len]\n\t"
			"movl %[rseq_scratch1], %[dst]\n\t"
			"movl %[rseq_scratch0], %[src]\n\t",
			cmpfail)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_DEFINE_CMPFAIL(6,
			"movl %[rseq_scratch2], %[len]\n\t"
			"movl %[rseq_scratch1], %[dst]\n\t"
			"movl %[rseq_scratch0], %[src]\n\t",
			error1)
		RSEQ_ASM_DEFINE_CMPFAIL(7,
			"movl %[rseq_scratch2], %[len]\n\t"
			"movl %[rseq_scratch1], %[dst]\n\t"
			"movl %[rseq_scratch0], %[src]\n\t",
			error2)
#पूर्ण_अगर
		: /* gcc यंत्र जाओ करोes not allow outमाला_दो */
		: [cpu_id]		"r" (cpu),
		  [rseq_abi]		"r" (&__rseq_abi),
		  /* final store input */
		  [v]			"m" (*v),
		  [expect]		"m" (expect),
		  [newv]		"m" (newv),
		  /* try स_नकल input */
		  [dst]			"r" (dst),
		  [src]			"r" (src),
		  [len]			"r" (len),
		  [rseq_scratch0]	"m" (rseq_scratch[0]),
		  [rseq_scratch1]	"m" (rseq_scratch[1]),
		  [rseq_scratch2]	"m" (rseq_scratch[2])
		: "memory", "cc", "eax"
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

/* TODO: implement a faster स_नकल. */
अटल अंतरभूत __attribute__((always_अंतरभूत))
पूर्णांक rseq_cmpeqv_tryस_नकल_storev_release(पूर्णांकptr_t *v, पूर्णांकptr_t expect,
					 व्योम *dst, व्योम *src, माप_प्रकार len,
					 पूर्णांकptr_t newv, पूर्णांक cpu)
अणु
	uपूर्णांक32_t rseq_scratch[3];

	RSEQ_INJECT_C(9)

	__यंत्र__ __अस्थिर__ जाओ (
		RSEQ_ASM_DEFINE_TABLE(3, 1f, 2f, 4f) /* start, commit, पात */
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[cmpfail])
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error1])
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error2])
#पूर्ण_अगर
		"movl %[src], %[rseq_scratch0]\n\t"
		"movl %[dst], %[rseq_scratch1]\n\t"
		"movl %[len], %[rseq_scratch2]\n\t"
		/* Start rseq by storing table entry poपूर्णांकer पूर्णांकo rseq_cs. */
		RSEQ_ASM_STORE_RSEQ_CS(1, 3b, RSEQ_CS_OFFSET(%[rseq_abi]))
		RSEQ_ASM_CMP_CPU_ID(cpu_id, RSEQ_CPU_ID_OFFSET(%[rseq_abi]), 4f)
		RSEQ_INJECT_ASM(3)
		"movl %[expect], %%eax\n\t"
		"cmpl %%eax, %[v]\n\t"
		"jnz 5f\n\t"
		RSEQ_INJECT_ASM(4)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, RSEQ_CPU_ID_OFFSET(%[rseq_abi]), 6f)
		"movl %[expect], %%eax\n\t"
		"cmpl %%eax, %[v]\n\t"
		"jnz 7f\n\t"
#पूर्ण_अगर
		/* try स_नकल */
		"test %[len], %[len]\n\t" \
		"jz 333f\n\t" \
		"222:\n\t" \
		"movb (%[src]), %%al\n\t" \
		"movb %%al, (%[dst])\n\t" \
		"inc %[src]\n\t" \
		"inc %[dst]\n\t" \
		"dec %[len]\n\t" \
		"jnz 222b\n\t" \
		"333:\n\t" \
		RSEQ_INJECT_ASM(5)
		"lock; addl $0,-128(%%esp)\n\t"
		"movl %[newv], %%eax\n\t"
		/* final store */
		"movl %%eax, %[v]\n\t"
		"2:\n\t"
		RSEQ_INJECT_ASM(6)
		/* tearकरोwn */
		"movl %[rseq_scratch2], %[len]\n\t"
		"movl %[rseq_scratch1], %[dst]\n\t"
		"movl %[rseq_scratch0], %[src]\n\t"
		RSEQ_ASM_DEFINE_ABORT(4,
			"movl %[rseq_scratch2], %[len]\n\t"
			"movl %[rseq_scratch1], %[dst]\n\t"
			"movl %[rseq_scratch0], %[src]\n\t",
			पात)
		RSEQ_ASM_DEFINE_CMPFAIL(5,
			"movl %[rseq_scratch2], %[len]\n\t"
			"movl %[rseq_scratch1], %[dst]\n\t"
			"movl %[rseq_scratch0], %[src]\n\t",
			cmpfail)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_DEFINE_CMPFAIL(6,
			"movl %[rseq_scratch2], %[len]\n\t"
			"movl %[rseq_scratch1], %[dst]\n\t"
			"movl %[rseq_scratch0], %[src]\n\t",
			error1)
		RSEQ_ASM_DEFINE_CMPFAIL(7,
			"movl %[rseq_scratch2], %[len]\n\t"
			"movl %[rseq_scratch1], %[dst]\n\t"
			"movl %[rseq_scratch0], %[src]\n\t",
			error2)
#पूर्ण_अगर
		: /* gcc यंत्र जाओ करोes not allow outमाला_दो */
		: [cpu_id]		"r" (cpu),
		  [rseq_abi]		"r" (&__rseq_abi),
		  /* final store input */
		  [v]			"m" (*v),
		  [expect]		"m" (expect),
		  [newv]		"m" (newv),
		  /* try स_नकल input */
		  [dst]			"r" (dst),
		  [src]			"r" (src),
		  [len]			"r" (len),
		  [rseq_scratch0]	"m" (rseq_scratch[0]),
		  [rseq_scratch1]	"m" (rseq_scratch[1]),
		  [rseq_scratch2]	"m" (rseq_scratch[2])
		: "memory", "cc", "eax"
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

#पूर्ण_अगर /* !RSEQ_SKIP_FASTPATH */

#पूर्ण_अगर
