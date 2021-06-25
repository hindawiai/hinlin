<शैली गुरु>
/* SPDX-License-Identअगरier: LGPL-2.1 OR MIT */

/*
 * RSEQ_SIG uses the trap4 inकाष्ठाion. As Linux करोes not make use of the
 * access-रेजिस्टर mode nor the linkage stack this inकाष्ठाion will always
 * cause a special-operation exception (the trap-enabled bit in the DUCT
 * is and will stay 0). The inकाष्ठाion pattern is
 *	b2 ff 0f ff	trap4	4095(%r0)
 */
#घोषणा RSEQ_SIG	0xB2FF0FFF

#घोषणा rseq_smp_mb()	__यंत्र__ __अस्थिर__ ("bcr 15,0" ::: "memory")
#घोषणा rseq_smp_rmb()	rseq_smp_mb()
#घोषणा rseq_smp_wmb()	rseq_smp_mb()

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

#अगर_घोषित __s390x__

#घोषणा LONG_L			"lg"
#घोषणा LONG_S			"stg"
#घोषणा LONG_LT_R		"ltgr"
#घोषणा LONG_CMP		"cg"
#घोषणा LONG_CMP_R		"cgr"
#घोषणा LONG_ADDI		"aghi"
#घोषणा LONG_ADD_R		"agr"

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

#या_अगर __s390__

#घोषणा __RSEQ_ASM_DEFINE_TABLE(label, version, flags,			\
				start_ip, post_commit_offset, पात_ip)	\
		".pushsection __rseq_cs, \"aw\"\n\t"			\
		".balign 32\n\t"					\
		__rseq_str(label) ":\n\t"				\
		".long " __rseq_str(version) ", " __rseq_str(flags) "\n\t" \
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
#घोषणा RSEQ_ASM_DEFINE_EXIT_POINT(start_ip, निकास_ip)			\
		".pushsection __rseq_exit_point_array, \"aw\"\n\t"	\
		".long 0x0, " __rseq_str(start_ip) ", 0x0, " __rseq_str(निकास_ip) "\n\t" \
		".popsection\n\t"

#घोषणा LONG_L			"l"
#घोषणा LONG_S			"st"
#घोषणा LONG_LT_R		"ltr"
#घोषणा LONG_CMP		"c"
#घोषणा LONG_CMP_R		"cr"
#घोषणा LONG_ADDI		"ahi"
#घोषणा LONG_ADD_R		"ar"

#पूर्ण_अगर

#घोषणा RSEQ_ASM_DEFINE_TABLE(label, start_ip, post_commit_ip, पात_ip) \
	__RSEQ_ASM_DEFINE_TABLE(label, 0x0, 0x0, start_ip,		\
				(post_commit_ip - start_ip), पात_ip)

#घोषणा RSEQ_ASM_STORE_RSEQ_CS(label, cs_label, rseq_cs)		\
		RSEQ_INJECT_ASM(1)					\
		"larl %%r0, " __rseq_str(cs_label) "\n\t"		\
		LONG_S " %%r0, %[" __rseq_str(rseq_cs) "]\n\t"		\
		__rseq_str(label) ":\n\t"

#घोषणा RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, label)		\
		RSEQ_INJECT_ASM(2)					\
		"c %[" __rseq_str(cpu_id) "], %[" __rseq_str(current_cpu_id) "]\n\t" \
		"jnz " __rseq_str(label) "\n\t"

#घोषणा RSEQ_ASM_DEFINE_ABORT(label, tearकरोwn, पात_label)		\
		".pushsection __rseq_failure, \"ax\"\n\t"		\
		".long " __rseq_str(RSEQ_SIG) "\n\t"			\
		__rseq_str(label) ":\n\t"				\
		tearकरोwn						\
		"jg %l[" __rseq_str(पात_label) "]\n\t"		\
		".popsection\n\t"

#घोषणा RSEQ_ASM_DEFINE_CMPFAIL(label, tearकरोwn, cmpfail_label)		\
		".pushsection __rseq_failure, \"ax\"\n\t"		\
		__rseq_str(label) ":\n\t"				\
		tearकरोwn						\
		"jg %l[" __rseq_str(cmpfail_label) "]\n\t"		\
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
		RSEQ_ASM_STORE_RSEQ_CS(1, 3b, rseq_cs)
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, 4f)
		RSEQ_INJECT_ASM(3)
		LONG_CMP " %[expect], %[v]\n\t"
		"jnz %l[cmpfail]\n\t"
		RSEQ_INJECT_ASM(4)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, %l[error1])
		LONG_CMP " %[expect], %[v]\n\t"
		"jnz %l[error2]\n\t"
#पूर्ण_अगर
		/* final store */
		LONG_S " %[newv], %[v]\n\t"
		"2:\n\t"
		RSEQ_INJECT_ASM(5)
		RSEQ_ASM_DEFINE_ABORT(4, "", पात)
		: /* gcc यंत्र जाओ करोes not allow outमाला_दो */
		: [cpu_id]		"r" (cpu),
		  [current_cpu_id]	"m" (__rseq_abi.cpu_id),
		  [rseq_cs]		"m" (__rseq_abi.rseq_cs),
		  [v]			"m" (*v),
		  [expect]		"r" (expect),
		  [newv]		"r" (newv)
		  RSEQ_INJECT_INPUT
		: "memory", "cc", "r0"
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
		RSEQ_ASM_STORE_RSEQ_CS(1, 3b, rseq_cs)
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, 4f)
		RSEQ_INJECT_ASM(3)
		LONG_L " %%r1, %[v]\n\t"
		LONG_CMP_R " %%r1, %[expectnot]\n\t"
		"je %l[cmpfail]\n\t"
		RSEQ_INJECT_ASM(4)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, %l[error1])
		LONG_L " %%r1, %[v]\n\t"
		LONG_CMP_R " %%r1, %[expectnot]\n\t"
		"je %l[error2]\n\t"
#पूर्ण_अगर
		LONG_S " %%r1, %[load]\n\t"
		LONG_ADD_R " %%r1, %[voffp]\n\t"
		LONG_L " %%r1, 0(%%r1)\n\t"
		/* final store */
		LONG_S " %%r1, %[v]\n\t"
		"2:\n\t"
		RSEQ_INJECT_ASM(5)
		RSEQ_ASM_DEFINE_ABORT(4, "", पात)
		: /* gcc यंत्र जाओ करोes not allow outमाला_दो */
		: [cpu_id]		"r" (cpu),
		  [current_cpu_id]	"m" (__rseq_abi.cpu_id),
		  [rseq_cs]		"m" (__rseq_abi.rseq_cs),
		  /* final store input */
		  [v]			"m" (*v),
		  [expectnot]		"r" (expectnot),
		  [voffp]		"r" (voffp),
		  [load]		"m" (*load)
		  RSEQ_INJECT_INPUT
		: "memory", "cc", "r0", "r1"
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
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, 4f)
		RSEQ_INJECT_ASM(3)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, %l[error1])
#पूर्ण_अगर
		LONG_L " %%r0, %[v]\n\t"
		LONG_ADD_R " %%r0, %[count]\n\t"
		/* final store */
		LONG_S " %%r0, %[v]\n\t"
		"2:\n\t"
		RSEQ_INJECT_ASM(4)
		RSEQ_ASM_DEFINE_ABORT(4, "", पात)
		: /* gcc यंत्र जाओ करोes not allow outमाला_दो */
		: [cpu_id]		"r" (cpu),
		  [current_cpu_id]	"m" (__rseq_abi.cpu_id),
		  [rseq_cs]		"m" (__rseq_abi.rseq_cs),
		  /* final store input */
		  [v]			"m" (*v),
		  [count]		"r" (count)
		  RSEQ_INJECT_INPUT
		: "memory", "cc", "r0"
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
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, 4f)
		RSEQ_INJECT_ASM(3)
		LONG_CMP " %[expect], %[v]\n\t"
		"jnz %l[cmpfail]\n\t"
		RSEQ_INJECT_ASM(4)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, %l[error1])
		LONG_CMP " %[expect], %[v]\n\t"
		"jnz %l[error2]\n\t"
#पूर्ण_अगर
		/* try store */
		LONG_S " %[newv2], %[v2]\n\t"
		RSEQ_INJECT_ASM(5)
		/* final store */
		LONG_S " %[newv], %[v]\n\t"
		"2:\n\t"
		RSEQ_INJECT_ASM(6)
		RSEQ_ASM_DEFINE_ABORT(4, "", पात)
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
		: "memory", "cc", "r0"
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

/* s390 is TSO. */
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
		RSEQ_ASM_STORE_RSEQ_CS(1, 3b, rseq_cs)
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, 4f)
		RSEQ_INJECT_ASM(3)
		LONG_CMP " %[expect], %[v]\n\t"
		"jnz %l[cmpfail]\n\t"
		RSEQ_INJECT_ASM(4)
		LONG_CMP " %[expect2], %[v2]\n\t"
		"jnz %l[cmpfail]\n\t"
		RSEQ_INJECT_ASM(5)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, %l[error1])
		LONG_CMP " %[expect], %[v]\n\t"
		"jnz %l[error2]\n\t"
		LONG_CMP " %[expect2], %[v2]\n\t"
		"jnz %l[error3]\n\t"
#पूर्ण_अगर
		/* final store */
		LONG_S " %[newv], %[v]\n\t"
		"2:\n\t"
		RSEQ_INJECT_ASM(6)
		RSEQ_ASM_DEFINE_ABORT(4, "", पात)
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
		: "memory", "cc", "r0"
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
		LONG_S " %[src], %[rseq_scratch0]\n\t"
		LONG_S " %[dst], %[rseq_scratch1]\n\t"
		LONG_S " %[len], %[rseq_scratch2]\n\t"
		/* Start rseq by storing table entry poपूर्णांकer पूर्णांकo rseq_cs. */
		RSEQ_ASM_STORE_RSEQ_CS(1, 3b, rseq_cs)
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, 4f)
		RSEQ_INJECT_ASM(3)
		LONG_CMP " %[expect], %[v]\n\t"
		"jnz 5f\n\t"
		RSEQ_INJECT_ASM(4)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, 6f)
		LONG_CMP " %[expect], %[v]\n\t"
		"jnz 7f\n\t"
#पूर्ण_अगर
		/* try स_नकल */
		LONG_LT_R " %[len], %[len]\n\t"
		"jz 333f\n\t"
		"222:\n\t"
		"ic %%r0,0(%[src])\n\t"
		"stc %%r0,0(%[dst])\n\t"
		LONG_ADDI " %[src], 1\n\t"
		LONG_ADDI " %[dst], 1\n\t"
		LONG_ADDI " %[len], -1\n\t"
		"jnz 222b\n\t"
		"333:\n\t"
		RSEQ_INJECT_ASM(5)
		/* final store */
		LONG_S " %[newv], %[v]\n\t"
		"2:\n\t"
		RSEQ_INJECT_ASM(6)
		/* tearकरोwn */
		LONG_L " %[len], %[rseq_scratch2]\n\t"
		LONG_L " %[dst], %[rseq_scratch1]\n\t"
		LONG_L " %[src], %[rseq_scratch0]\n\t"
		RSEQ_ASM_DEFINE_ABORT(4,
			LONG_L " %[len], %[rseq_scratch2]\n\t"
			LONG_L " %[dst], %[rseq_scratch1]\n\t"
			LONG_L " %[src], %[rseq_scratch0]\n\t",
			पात)
		RSEQ_ASM_DEFINE_CMPFAIL(5,
			LONG_L " %[len], %[rseq_scratch2]\n\t"
			LONG_L " %[dst], %[rseq_scratch1]\n\t"
			LONG_L " %[src], %[rseq_scratch0]\n\t",
			cmpfail)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_DEFINE_CMPFAIL(6,
			LONG_L " %[len], %[rseq_scratch2]\n\t"
			LONG_L " %[dst], %[rseq_scratch1]\n\t"
			LONG_L " %[src], %[rseq_scratch0]\n\t",
			error1)
		RSEQ_ASM_DEFINE_CMPFAIL(7,
			LONG_L " %[len], %[rseq_scratch2]\n\t"
			LONG_L " %[dst], %[rseq_scratch1]\n\t"
			LONG_L " %[src], %[rseq_scratch0]\n\t",
			error2)
#पूर्ण_अगर
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
		  [len]			"r" (len),
		  [rseq_scratch0]	"m" (rseq_scratch[0]),
		  [rseq_scratch1]	"m" (rseq_scratch[1]),
		  [rseq_scratch2]	"m" (rseq_scratch[2])
		  RSEQ_INJECT_INPUT
		: "memory", "cc", "r0"
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

/* s390 is TSO. */
अटल अंतरभूत __attribute__((always_अंतरभूत))
पूर्णांक rseq_cmpeqv_tryस_नकल_storev_release(पूर्णांकptr_t *v, पूर्णांकptr_t expect,
					 व्योम *dst, व्योम *src, माप_प्रकार len,
					 पूर्णांकptr_t newv, पूर्णांक cpu)
अणु
	वापस rseq_cmpeqv_tryस_नकल_storev(v, expect, dst, src, len,
					    newv, cpu);
पूर्ण
#पूर्ण_अगर /* !RSEQ_SKIP_FASTPATH */
