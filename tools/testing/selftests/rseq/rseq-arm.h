<शैली गुरु>
/* SPDX-License-Identअगरier: LGPL-2.1 OR MIT */
/*
 * rseq-arm.h
 *
 * (C) Copyright 2016-2018 - Mathieu Desnoyers <mathieu.desnoyers@efficios.com>
 */

/*
 * - ARM little endian
 *
 * RSEQ_SIG uses the udf A32 inकाष्ठाion with an uncommon immediate opeअक्रम
 * value 0x5de3. This traps अगर user-space reaches this inकाष्ठाion by mistake,
 * and the uncommon opeअक्रम ensures the kernel करोes not move the inकाष्ठाion
 * poपूर्णांकer to attacker-controlled code on rseq पात.
 *
 * The inकाष्ठाion pattern in the A32 inकाष्ठाion set is:
 *
 * e7f5def3    udf    #24035    ; 0x5de3
 *
 * This translates to the following inकाष्ठाion pattern in the T16 inकाष्ठाion
 * set:
 *
 * little endian:
 * def3        udf    #243      ; 0xf3
 * e7f5        b.n    <7f5>
 *
 * - ARMv6+ big endian (BE8):
 *
 * ARMv6+ -mbig-endian generates mixed endianness code vs data: little-endian
 * code and big-endian data. The data value of the signature needs to have its
 * byte order reversed to generate the trap inकाष्ठाion:
 *
 * Data: 0xf3def5e7
 *
 * Translates to this A32 inकाष्ठाion pattern:
 *
 * e7f5def3    udf    #24035    ; 0x5de3
 *
 * Translates to this T16 inकाष्ठाion pattern:
 *
 * def3        udf    #243      ; 0xf3
 * e7f5        b.n    <7f5>
 *
 * - Prior to ARMv6 big endian (BE32):
 *
 * Prior to ARMv6, -mbig-endian generates big-endian code and data
 * (which match), so the endianness of the data representation of the
 * signature should not be reversed. However, the choice between BE32
 * and BE8 is करोne by the linker, so we cannot know whether code and
 * data endianness will be mixed beक्रमe the linker is invoked. So rather
 * than try to play tricks with the linker, the rseq signature is simply
 * data (not a trap inकाष्ठाion) prior to ARMv6 on big endian. This is
 * why the signature is expressed as data (.word) rather than as
 * inकाष्ठाion (.inst) in assembler.
 */

#अगर_घोषित __ARMEB__
#घोषणा RSEQ_SIG    0xf3def5e7      /* udf    #24035    ; 0x5de3 (ARMv6+) */
#अन्यथा
#घोषणा RSEQ_SIG    0xe7f5def3      /* udf    #24035    ; 0x5de3 */
#पूर्ण_अगर

#घोषणा rseq_smp_mb()	__यंत्र__ __अस्थिर__ ("dmb" ::: "memory", "cc")
#घोषणा rseq_smp_rmb()	__यंत्र__ __अस्थिर__ ("dmb" ::: "memory", "cc")
#घोषणा rseq_smp_wmb()	__यंत्र__ __अस्थिर__ ("dmb" ::: "memory", "cc")

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

#घोषणा __RSEQ_ASM_DEFINE_TABLE(label, version, flags, start_ip,	\
				post_commit_offset, पात_ip)		\
		".pushsection __rseq_cs, \"aw\"\n\t"			\
		".balign 32\n\t"					\
		__rseq_str(label) ":\n\t"					\
		".word " __rseq_str(version) ", " __rseq_str(flags) "\n\t" \
		".word " __rseq_str(start_ip) ", 0x0, " __rseq_str(post_commit_offset) ", 0x0, " __rseq_str(पात_ip) ", 0x0\n\t" \
		".popsection\n\t"					\
		".pushsection __rseq_cs_ptr_array, \"aw\"\n\t"		\
		".word " __rseq_str(label) "b, 0x0\n\t"			\
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
		".word " __rseq_str(start_ip) ", 0x0, " __rseq_str(निकास_ip) ", 0x0\n\t" \
		".popsection\n\t"

#घोषणा RSEQ_ASM_STORE_RSEQ_CS(label, cs_label, rseq_cs)		\
		RSEQ_INJECT_ASM(1)					\
		"adr r0, " __rseq_str(cs_label) "\n\t"			\
		"str r0, %[" __rseq_str(rseq_cs) "]\n\t"		\
		__rseq_str(label) ":\n\t"

#घोषणा RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, label)		\
		RSEQ_INJECT_ASM(2)					\
		"ldr r0, %[" __rseq_str(current_cpu_id) "]\n\t"	\
		"cmp %[" __rseq_str(cpu_id) "], r0\n\t"		\
		"bne " __rseq_str(label) "\n\t"

#घोषणा __RSEQ_ASM_DEFINE_ABORT(table_label, label, tearकरोwn,		\
				पात_label, version, flags,		\
				start_ip, post_commit_offset, पात_ip)	\
		".balign 32\n\t"					\
		__rseq_str(table_label) ":\n\t"				\
		".word " __rseq_str(version) ", " __rseq_str(flags) "\n\t" \
		".word " __rseq_str(start_ip) ", 0x0, " __rseq_str(post_commit_offset) ", 0x0, " __rseq_str(पात_ip) ", 0x0\n\t" \
		".word " __rseq_str(RSEQ_SIG) "\n\t"			\
		__rseq_str(label) ":\n\t"				\
		tearकरोwn						\
		"b %l[" __rseq_str(पात_label) "]\n\t"

#घोषणा RSEQ_ASM_DEFINE_ABORT(table_label, label, tearकरोwn, पात_label, \
			      start_ip, post_commit_ip, पात_ip)	\
	__RSEQ_ASM_DEFINE_ABORT(table_label, label, tearकरोwn,		\
				पात_label, 0x0, 0x0, start_ip,	\
				(post_commit_ip - start_ip), पात_ip)

#घोषणा RSEQ_ASM_DEFINE_CMPFAIL(label, tearकरोwn, cmpfail_label)		\
		__rseq_str(label) ":\n\t"				\
		tearकरोwn						\
		"b %l[" __rseq_str(cmpfail_label) "]\n\t"

#घोषणा rseq_workaround_gcc_यंत्र_size_guess()	__यंत्र__ __अस्थिर__("")

अटल अंतरभूत __attribute__((always_अंतरभूत))
पूर्णांक rseq_cmpeqv_storev(पूर्णांकptr_t *v, पूर्णांकptr_t expect, पूर्णांकptr_t newv, पूर्णांक cpu)
अणु
	RSEQ_INJECT_C(9)

	rseq_workaround_gcc_यंत्र_size_guess();
	__यंत्र__ __अस्थिर__ जाओ (
		RSEQ_ASM_DEFINE_TABLE(9, 1f, 2f, 4f) /* start, commit, पात */
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[cmpfail])
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error1])
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error2])
#पूर्ण_अगर
		/* Start rseq by storing table entry poपूर्णांकer पूर्णांकo rseq_cs. */
		RSEQ_ASM_STORE_RSEQ_CS(1, 3f, rseq_cs)
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, 4f)
		RSEQ_INJECT_ASM(3)
		"ldr r0, %[v]\n\t"
		"cmp %[expect], r0\n\t"
		"bne %l[cmpfail]\n\t"
		RSEQ_INJECT_ASM(4)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, %l[error1])
		"ldr r0, %[v]\n\t"
		"cmp %[expect], r0\n\t"
		"bne %l[error2]\n\t"
#पूर्ण_अगर
		/* final store */
		"str %[newv], %[v]\n\t"
		"2:\n\t"
		RSEQ_INJECT_ASM(5)
		"b 5f\n\t"
		RSEQ_ASM_DEFINE_ABORT(3, 4, "", पात, 1b, 2b, 4f)
		"5:\n\t"
		: /* gcc यंत्र जाओ करोes not allow outमाला_दो */
		: [cpu_id]		"r" (cpu),
		  [current_cpu_id]	"m" (__rseq_abi.cpu_id),
		  [rseq_cs]		"m" (__rseq_abi.rseq_cs),
		  [v]			"m" (*v),
		  [expect]		"r" (expect),
		  [newv]		"r" (newv)
		  RSEQ_INJECT_INPUT
		: "r0", "memory", "cc"
		  RSEQ_INJECT_CLOBBER
		: पात, cmpfail
#अगर_घोषित RSEQ_COMPARE_TWICE
		  , error1, error2
#पूर्ण_अगर
	);
	rseq_workaround_gcc_यंत्र_size_guess();
	वापस 0;
पात:
	rseq_workaround_gcc_यंत्र_size_guess();
	RSEQ_INJECT_FAILED
	वापस -1;
cmpfail:
	rseq_workaround_gcc_यंत्र_size_guess();
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

	rseq_workaround_gcc_यंत्र_size_guess();
	__यंत्र__ __अस्थिर__ जाओ (
		RSEQ_ASM_DEFINE_TABLE(9, 1f, 2f, 4f) /* start, commit, पात */
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[cmpfail])
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error1])
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error2])
#पूर्ण_अगर
		/* Start rseq by storing table entry poपूर्णांकer पूर्णांकo rseq_cs. */
		RSEQ_ASM_STORE_RSEQ_CS(1, 3f, rseq_cs)
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, 4f)
		RSEQ_INJECT_ASM(3)
		"ldr r0, %[v]\n\t"
		"cmp %[expectnot], r0\n\t"
		"beq %l[cmpfail]\n\t"
		RSEQ_INJECT_ASM(4)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, %l[error1])
		"ldr r0, %[v]\n\t"
		"cmp %[expectnot], r0\n\t"
		"beq %l[error2]\n\t"
#पूर्ण_अगर
		"str r0, %[load]\n\t"
		"add r0, %[voffp]\n\t"
		"ldr r0, [r0]\n\t"
		/* final store */
		"str r0, %[v]\n\t"
		"2:\n\t"
		RSEQ_INJECT_ASM(5)
		"b 5f\n\t"
		RSEQ_ASM_DEFINE_ABORT(3, 4, "", पात, 1b, 2b, 4f)
		"5:\n\t"
		: /* gcc यंत्र जाओ करोes not allow outमाला_दो */
		: [cpu_id]		"r" (cpu),
		  [current_cpu_id]	"m" (__rseq_abi.cpu_id),
		  [rseq_cs]		"m" (__rseq_abi.rseq_cs),
		  /* final store input */
		  [v]			"m" (*v),
		  [expectnot]		"r" (expectnot),
		  [voffp]		"Ir" (voffp),
		  [load]		"m" (*load)
		  RSEQ_INJECT_INPUT
		: "r0", "memory", "cc"
		  RSEQ_INJECT_CLOBBER
		: पात, cmpfail
#अगर_घोषित RSEQ_COMPARE_TWICE
		  , error1, error2
#पूर्ण_अगर
	);
	rseq_workaround_gcc_यंत्र_size_guess();
	वापस 0;
पात:
	rseq_workaround_gcc_यंत्र_size_guess();
	RSEQ_INJECT_FAILED
	वापस -1;
cmpfail:
	rseq_workaround_gcc_यंत्र_size_guess();
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

	rseq_workaround_gcc_यंत्र_size_guess();
	__यंत्र__ __अस्थिर__ जाओ (
		RSEQ_ASM_DEFINE_TABLE(9, 1f, 2f, 4f) /* start, commit, पात */
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error1])
#पूर्ण_अगर
		/* Start rseq by storing table entry poपूर्णांकer पूर्णांकo rseq_cs. */
		RSEQ_ASM_STORE_RSEQ_CS(1, 3f, rseq_cs)
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, 4f)
		RSEQ_INJECT_ASM(3)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, %l[error1])
#पूर्ण_अगर
		"ldr r0, %[v]\n\t"
		"add r0, %[count]\n\t"
		/* final store */
		"str r0, %[v]\n\t"
		"2:\n\t"
		RSEQ_INJECT_ASM(4)
		"b 5f\n\t"
		RSEQ_ASM_DEFINE_ABORT(3, 4, "", पात, 1b, 2b, 4f)
		"5:\n\t"
		: /* gcc यंत्र जाओ करोes not allow outमाला_दो */
		: [cpu_id]		"r" (cpu),
		  [current_cpu_id]	"m" (__rseq_abi.cpu_id),
		  [rseq_cs]		"m" (__rseq_abi.rseq_cs),
		  [v]			"m" (*v),
		  [count]		"Ir" (count)
		  RSEQ_INJECT_INPUT
		: "r0", "memory", "cc"
		  RSEQ_INJECT_CLOBBER
		: पात
#अगर_घोषित RSEQ_COMPARE_TWICE
		  , error1
#पूर्ण_अगर
	);
	rseq_workaround_gcc_यंत्र_size_guess();
	वापस 0;
पात:
	rseq_workaround_gcc_यंत्र_size_guess();
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

	rseq_workaround_gcc_यंत्र_size_guess();
	__यंत्र__ __अस्थिर__ जाओ (
		RSEQ_ASM_DEFINE_TABLE(9, 1f, 2f, 4f) /* start, commit, पात */
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[cmpfail])
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error1])
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error2])
#पूर्ण_अगर
		/* Start rseq by storing table entry poपूर्णांकer पूर्णांकo rseq_cs. */
		RSEQ_ASM_STORE_RSEQ_CS(1, 3f, rseq_cs)
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, 4f)
		RSEQ_INJECT_ASM(3)
		"ldr r0, %[v]\n\t"
		"cmp %[expect], r0\n\t"
		"bne %l[cmpfail]\n\t"
		RSEQ_INJECT_ASM(4)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, %l[error1])
		"ldr r0, %[v]\n\t"
		"cmp %[expect], r0\n\t"
		"bne %l[error2]\n\t"
#पूर्ण_अगर
		/* try store */
		"str %[newv2], %[v2]\n\t"
		RSEQ_INJECT_ASM(5)
		/* final store */
		"str %[newv], %[v]\n\t"
		"2:\n\t"
		RSEQ_INJECT_ASM(6)
		"b 5f\n\t"
		RSEQ_ASM_DEFINE_ABORT(3, 4, "", पात, 1b, 2b, 4f)
		"5:\n\t"
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
		: "r0", "memory", "cc"
		  RSEQ_INJECT_CLOBBER
		: पात, cmpfail
#अगर_घोषित RSEQ_COMPARE_TWICE
		  , error1, error2
#पूर्ण_अगर
	);
	rseq_workaround_gcc_यंत्र_size_guess();
	वापस 0;
पात:
	rseq_workaround_gcc_यंत्र_size_guess();
	RSEQ_INJECT_FAILED
	वापस -1;
cmpfail:
	rseq_workaround_gcc_यंत्र_size_guess();
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

	rseq_workaround_gcc_यंत्र_size_guess();
	__यंत्र__ __अस्थिर__ जाओ (
		RSEQ_ASM_DEFINE_TABLE(9, 1f, 2f, 4f) /* start, commit, पात */
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[cmpfail])
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error1])
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error2])
#पूर्ण_अगर
		/* Start rseq by storing table entry poपूर्णांकer पूर्णांकo rseq_cs. */
		RSEQ_ASM_STORE_RSEQ_CS(1, 3f, rseq_cs)
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, 4f)
		RSEQ_INJECT_ASM(3)
		"ldr r0, %[v]\n\t"
		"cmp %[expect], r0\n\t"
		"bne %l[cmpfail]\n\t"
		RSEQ_INJECT_ASM(4)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, %l[error1])
		"ldr r0, %[v]\n\t"
		"cmp %[expect], r0\n\t"
		"bne %l[error2]\n\t"
#पूर्ण_अगर
		/* try store */
		"str %[newv2], %[v2]\n\t"
		RSEQ_INJECT_ASM(5)
		"dmb\n\t"	/* full mb provides store-release */
		/* final store */
		"str %[newv], %[v]\n\t"
		"2:\n\t"
		RSEQ_INJECT_ASM(6)
		"b 5f\n\t"
		RSEQ_ASM_DEFINE_ABORT(3, 4, "", पात, 1b, 2b, 4f)
		"5:\n\t"
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
		: "r0", "memory", "cc"
		  RSEQ_INJECT_CLOBBER
		: पात, cmpfail
#अगर_घोषित RSEQ_COMPARE_TWICE
		  , error1, error2
#पूर्ण_अगर
	);
	rseq_workaround_gcc_यंत्र_size_guess();
	वापस 0;
पात:
	rseq_workaround_gcc_यंत्र_size_guess();
	RSEQ_INJECT_FAILED
	वापस -1;
cmpfail:
	rseq_workaround_gcc_यंत्र_size_guess();
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

	rseq_workaround_gcc_यंत्र_size_guess();
	__यंत्र__ __अस्थिर__ जाओ (
		RSEQ_ASM_DEFINE_TABLE(9, 1f, 2f, 4f) /* start, commit, पात */
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[cmpfail])
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error1])
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error2])
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error3])
#पूर्ण_अगर
		/* Start rseq by storing table entry poपूर्णांकer पूर्णांकo rseq_cs. */
		RSEQ_ASM_STORE_RSEQ_CS(1, 3f, rseq_cs)
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, 4f)
		RSEQ_INJECT_ASM(3)
		"ldr r0, %[v]\n\t"
		"cmp %[expect], r0\n\t"
		"bne %l[cmpfail]\n\t"
		RSEQ_INJECT_ASM(4)
		"ldr r0, %[v2]\n\t"
		"cmp %[expect2], r0\n\t"
		"bne %l[cmpfail]\n\t"
		RSEQ_INJECT_ASM(5)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, %l[error1])
		"ldr r0, %[v]\n\t"
		"cmp %[expect], r0\n\t"
		"bne %l[error2]\n\t"
		"ldr r0, %[v2]\n\t"
		"cmp %[expect2], r0\n\t"
		"bne %l[error3]\n\t"
#पूर्ण_अगर
		/* final store */
		"str %[newv], %[v]\n\t"
		"2:\n\t"
		RSEQ_INJECT_ASM(6)
		"b 5f\n\t"
		RSEQ_ASM_DEFINE_ABORT(3, 4, "", पात, 1b, 2b, 4f)
		"5:\n\t"
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
		: "r0", "memory", "cc"
		  RSEQ_INJECT_CLOBBER
		: पात, cmpfail
#अगर_घोषित RSEQ_COMPARE_TWICE
		  , error1, error2, error3
#पूर्ण_अगर
	);
	rseq_workaround_gcc_यंत्र_size_guess();
	वापस 0;
पात:
	rseq_workaround_gcc_यंत्र_size_guess();
	RSEQ_INJECT_FAILED
	वापस -1;
cmpfail:
	rseq_workaround_gcc_यंत्र_size_guess();
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
	uपूर्णांक32_t rseq_scratch[3];

	RSEQ_INJECT_C(9)

	rseq_workaround_gcc_यंत्र_size_guess();
	__यंत्र__ __अस्थिर__ जाओ (
		RSEQ_ASM_DEFINE_TABLE(9, 1f, 2f, 4f) /* start, commit, पात */
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[cmpfail])
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error1])
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error2])
#पूर्ण_अगर
		"str %[src], %[rseq_scratch0]\n\t"
		"str %[dst], %[rseq_scratch1]\n\t"
		"str %[len], %[rseq_scratch2]\n\t"
		/* Start rseq by storing table entry poपूर्णांकer पूर्णांकo rseq_cs. */
		RSEQ_ASM_STORE_RSEQ_CS(1, 3f, rseq_cs)
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, 4f)
		RSEQ_INJECT_ASM(3)
		"ldr r0, %[v]\n\t"
		"cmp %[expect], r0\n\t"
		"bne 5f\n\t"
		RSEQ_INJECT_ASM(4)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, 6f)
		"ldr r0, %[v]\n\t"
		"cmp %[expect], r0\n\t"
		"bne 7f\n\t"
#पूर्ण_अगर
		/* try स_नकल */
		"cmp %[len], #0\n\t" \
		"beq 333f\n\t" \
		"222:\n\t" \
		"ldrb %%r0, [%[src]]\n\t" \
		"strb %%r0, [%[dst]]\n\t" \
		"adds %[src], #1\n\t" \
		"adds %[dst], #1\n\t" \
		"subs %[len], #1\n\t" \
		"bne 222b\n\t" \
		"333:\n\t" \
		RSEQ_INJECT_ASM(5)
		/* final store */
		"str %[newv], %[v]\n\t"
		"2:\n\t"
		RSEQ_INJECT_ASM(6)
		/* tearकरोwn */
		"ldr %[len], %[rseq_scratch2]\n\t"
		"ldr %[dst], %[rseq_scratch1]\n\t"
		"ldr %[src], %[rseq_scratch0]\n\t"
		"b 8f\n\t"
		RSEQ_ASM_DEFINE_ABORT(3, 4,
				      /* tearकरोwn */
				      "ldr %[len], %[rseq_scratch2]\n\t"
				      "ldr %[dst], %[rseq_scratch1]\n\t"
				      "ldr %[src], %[rseq_scratch0]\n\t",
				      पात, 1b, 2b, 4f)
		RSEQ_ASM_DEFINE_CMPFAIL(5,
					/* tearकरोwn */
					"ldr %[len], %[rseq_scratch2]\n\t"
					"ldr %[dst], %[rseq_scratch1]\n\t"
					"ldr %[src], %[rseq_scratch0]\n\t",
					cmpfail)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_DEFINE_CMPFAIL(6,
					/* tearकरोwn */
					"ldr %[len], %[rseq_scratch2]\n\t"
					"ldr %[dst], %[rseq_scratch1]\n\t"
					"ldr %[src], %[rseq_scratch0]\n\t",
					error1)
		RSEQ_ASM_DEFINE_CMPFAIL(7,
					/* tearकरोwn */
					"ldr %[len], %[rseq_scratch2]\n\t"
					"ldr %[dst], %[rseq_scratch1]\n\t"
					"ldr %[src], %[rseq_scratch0]\n\t",
					error2)
#पूर्ण_अगर
		"8:\n\t"
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
		: "r0", "memory", "cc"
		  RSEQ_INJECT_CLOBBER
		: पात, cmpfail
#अगर_घोषित RSEQ_COMPARE_TWICE
		  , error1, error2
#पूर्ण_अगर
	);
	rseq_workaround_gcc_यंत्र_size_guess();
	वापस 0;
पात:
	rseq_workaround_gcc_यंत्र_size_guess();
	RSEQ_INJECT_FAILED
	वापस -1;
cmpfail:
	rseq_workaround_gcc_यंत्र_size_guess();
	वापस 1;
#अगर_घोषित RSEQ_COMPARE_TWICE
error1:
	rseq_workaround_gcc_यंत्र_size_guess();
	rseq_bug("cpu_id comparison failed");
error2:
	rseq_workaround_gcc_यंत्र_size_guess();
	rseq_bug("expected value comparison failed");
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत __attribute__((always_अंतरभूत))
पूर्णांक rseq_cmpeqv_tryस_नकल_storev_release(पूर्णांकptr_t *v, पूर्णांकptr_t expect,
					 व्योम *dst, व्योम *src, माप_प्रकार len,
					 पूर्णांकptr_t newv, पूर्णांक cpu)
अणु
	uपूर्णांक32_t rseq_scratch[3];

	RSEQ_INJECT_C(9)

	rseq_workaround_gcc_यंत्र_size_guess();
	__यंत्र__ __अस्थिर__ जाओ (
		RSEQ_ASM_DEFINE_TABLE(9, 1f, 2f, 4f) /* start, commit, पात */
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[cmpfail])
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error1])
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error2])
#पूर्ण_अगर
		"str %[src], %[rseq_scratch0]\n\t"
		"str %[dst], %[rseq_scratch1]\n\t"
		"str %[len], %[rseq_scratch2]\n\t"
		/* Start rseq by storing table entry poपूर्णांकer पूर्णांकo rseq_cs. */
		RSEQ_ASM_STORE_RSEQ_CS(1, 3f, rseq_cs)
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, 4f)
		RSEQ_INJECT_ASM(3)
		"ldr r0, %[v]\n\t"
		"cmp %[expect], r0\n\t"
		"bne 5f\n\t"
		RSEQ_INJECT_ASM(4)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, 6f)
		"ldr r0, %[v]\n\t"
		"cmp %[expect], r0\n\t"
		"bne 7f\n\t"
#पूर्ण_अगर
		/* try स_नकल */
		"cmp %[len], #0\n\t" \
		"beq 333f\n\t" \
		"222:\n\t" \
		"ldrb %%r0, [%[src]]\n\t" \
		"strb %%r0, [%[dst]]\n\t" \
		"adds %[src], #1\n\t" \
		"adds %[dst], #1\n\t" \
		"subs %[len], #1\n\t" \
		"bne 222b\n\t" \
		"333:\n\t" \
		RSEQ_INJECT_ASM(5)
		"dmb\n\t"	/* full mb provides store-release */
		/* final store */
		"str %[newv], %[v]\n\t"
		"2:\n\t"
		RSEQ_INJECT_ASM(6)
		/* tearकरोwn */
		"ldr %[len], %[rseq_scratch2]\n\t"
		"ldr %[dst], %[rseq_scratch1]\n\t"
		"ldr %[src], %[rseq_scratch0]\n\t"
		"b 8f\n\t"
		RSEQ_ASM_DEFINE_ABORT(3, 4,
				      /* tearकरोwn */
				      "ldr %[len], %[rseq_scratch2]\n\t"
				      "ldr %[dst], %[rseq_scratch1]\n\t"
				      "ldr %[src], %[rseq_scratch0]\n\t",
				      पात, 1b, 2b, 4f)
		RSEQ_ASM_DEFINE_CMPFAIL(5,
					/* tearकरोwn */
					"ldr %[len], %[rseq_scratch2]\n\t"
					"ldr %[dst], %[rseq_scratch1]\n\t"
					"ldr %[src], %[rseq_scratch0]\n\t",
					cmpfail)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_DEFINE_CMPFAIL(6,
					/* tearकरोwn */
					"ldr %[len], %[rseq_scratch2]\n\t"
					"ldr %[dst], %[rseq_scratch1]\n\t"
					"ldr %[src], %[rseq_scratch0]\n\t",
					error1)
		RSEQ_ASM_DEFINE_CMPFAIL(7,
					/* tearकरोwn */
					"ldr %[len], %[rseq_scratch2]\n\t"
					"ldr %[dst], %[rseq_scratch1]\n\t"
					"ldr %[src], %[rseq_scratch0]\n\t",
					error2)
#पूर्ण_अगर
		"8:\n\t"
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
		: "r0", "memory", "cc"
		  RSEQ_INJECT_CLOBBER
		: पात, cmpfail
#अगर_घोषित RSEQ_COMPARE_TWICE
		  , error1, error2
#पूर्ण_अगर
	);
	rseq_workaround_gcc_यंत्र_size_guess();
	वापस 0;
पात:
	rseq_workaround_gcc_यंत्र_size_guess();
	RSEQ_INJECT_FAILED
	वापस -1;
cmpfail:
	rseq_workaround_gcc_यंत्र_size_guess();
	वापस 1;
#अगर_घोषित RSEQ_COMPARE_TWICE
error1:
	rseq_workaround_gcc_यंत्र_size_guess();
	rseq_bug("cpu_id comparison failed");
error2:
	rseq_workaround_gcc_यंत्र_size_guess();
	rseq_bug("expected value comparison failed");
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* !RSEQ_SKIP_FASTPATH */
