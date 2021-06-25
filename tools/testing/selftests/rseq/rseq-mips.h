<शैली गुरु>
/* SPDX-License-Identअगरier: LGPL-2.1 OR MIT */
/*
 * Author: Paul Burton <paul.burton@mips.com>
 * (C) Copyright 2018 MIPS Tech LLC
 *
 * Based on rseq-arm.h:
 * (C) Copyright 2016-2018 - Mathieu Desnoyers <mathieu.desnoyers@efficios.com>
 */

/*
 * RSEQ_SIG uses the अवरोध inकाष्ठाion. The inकाष्ठाion pattern is:
 *
 * On MIPS:
 *	0350000d        अवरोध     0x350
 *
 * On nanoMIPS:
 *      00100350        अवरोध     0x350
 *
 * On microMIPS:
 *      0000d407        अवरोध     0x350
 *
 * For nanoMIPS32 and microMIPS, the inकाष्ठाion stream is encoded as 16-bit
 * halfwords, so the signature halfwords need to be swapped accordingly क्रम
 * little-endian.
 */
#अगर defined(__nanomips__)
# अगरdef __MIPSEL__
#  define RSEQ_SIG	0x03500010
# अन्यथा
#  define RSEQ_SIG	0x00100350
# endअगर
#या_अगर defined(__mips_micromips)
# अगरdef __MIPSEL__
#  define RSEQ_SIG	0xd4070000
# अन्यथा
#  define RSEQ_SIG	0x0000d407
# endअगर
#या_अगर defined(__mips__)
# define RSEQ_SIG	0x0350000d
#अन्यथा
/* Unknown MIPS architecture. */
#पूर्ण_अगर

#घोषणा rseq_smp_mb()	__यंत्र__ __अस्थिर__ ("sync" ::: "memory")
#घोषणा rseq_smp_rmb()	rseq_smp_mb()
#घोषणा rseq_smp_wmb()	rseq_smp_mb()

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

#अगर _MIPS_SZLONG == 64
# define LONG			".dword"
# define LONG_LA		"dla"
# define LONG_L			"ld"
# define LONG_S			"sd"
# define LONG_ADDI		"daddiu"
# define U32_U64_PAD(x)		x
#या_अगर _MIPS_SZLONG == 32
# define LONG			".word"
# define LONG_LA		"la"
# define LONG_L			"lw"
# define LONG_S			"sw"
# define LONG_ADDI		"addiu"
# अगरdef __BIG_ENDIAN
#  define U32_U64_PAD(x)	"0x0, " x
# अन्यथा
#  define U32_U64_PAD(x)	x ", 0x0"
# endअगर
#अन्यथा
# error unsupported _MIPS_SZLONG
#पूर्ण_अगर

#घोषणा __RSEQ_ASM_DEFINE_TABLE(label, version, flags, start_ip, \
				post_commit_offset, पात_ip) \
		".pushsection __rseq_cs, \"aw\"\n\t" \
		".balign 32\n\t" \
		__rseq_str(label) ":\n\t"					\
		".word " __rseq_str(version) ", " __rseq_str(flags) "\n\t" \
		LONG " " U32_U64_PAD(__rseq_str(start_ip)) "\n\t" \
		LONG " " U32_U64_PAD(__rseq_str(post_commit_offset)) "\n\t" \
		LONG " " U32_U64_PAD(__rseq_str(पात_ip)) "\n\t" \
		".popsection\n\t" \
		".pushsection __rseq_cs_ptr_array, \"aw\"\n\t" \
		LONG " " U32_U64_PAD(__rseq_str(label) "b") "\n\t" \
		".popsection\n\t"

#घोषणा RSEQ_ASM_DEFINE_TABLE(label, start_ip, post_commit_ip, पात_ip) \
	__RSEQ_ASM_DEFINE_TABLE(label, 0x0, 0x0, start_ip, \
				(post_commit_ip - start_ip), पात_ip)

/*
 * Exit poपूर्णांकs of a rseq critical section consist of all inकाष्ठाions outside
 * of the critical section where a critical section can either branch to or
 * reach through the normal course of its execution. The पात IP and the
 * post-commit IP are alपढ़ोy part of the __rseq_cs section and should not be
 * explicitly defined as additional निकास poपूर्णांकs. Knowing all निकास poपूर्णांकs is
 * useful to assist debuggers stepping over the critical section.
 */
#घोषणा RSEQ_ASM_DEFINE_EXIT_POINT(start_ip, निकास_ip) \
		".pushsection __rseq_exit_point_array, \"aw\"\n\t" \
		LONG " " U32_U64_PAD(__rseq_str(start_ip)) "\n\t" \
		LONG " " U32_U64_PAD(__rseq_str(निकास_ip)) "\n\t" \
		".popsection\n\t"

#घोषणा RSEQ_ASM_STORE_RSEQ_CS(label, cs_label, rseq_cs) \
		RSEQ_INJECT_ASM(1) \
		LONG_LA " $4, " __rseq_str(cs_label) "\n\t" \
		LONG_S  " $4, %[" __rseq_str(rseq_cs) "]\n\t" \
		__rseq_str(label) ":\n\t"

#घोषणा RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, label) \
		RSEQ_INJECT_ASM(2) \
		"lw  $4, %[" __rseq_str(current_cpu_id) "]\n\t" \
		"bne $4, %[" __rseq_str(cpu_id) "], " __rseq_str(label) "\n\t"

#घोषणा __RSEQ_ASM_DEFINE_ABORT(table_label, label, tearकरोwn, \
				पात_label, version, flags, \
				start_ip, post_commit_offset, पात_ip) \
		".balign 32\n\t" \
		__rseq_str(table_label) ":\n\t" \
		".word " __rseq_str(version) ", " __rseq_str(flags) "\n\t" \
		LONG " " U32_U64_PAD(__rseq_str(start_ip)) "\n\t" \
		LONG " " U32_U64_PAD(__rseq_str(post_commit_offset)) "\n\t" \
		LONG " " U32_U64_PAD(__rseq_str(पात_ip)) "\n\t" \
		".word " __rseq_str(RSEQ_SIG) "\n\t" \
		__rseq_str(label) ":\n\t" \
		tearकरोwn \
		"b %l[" __rseq_str(पात_label) "]\n\t"

#घोषणा RSEQ_ASM_DEFINE_ABORT(table_label, label, tearकरोwn, पात_label, \
			      start_ip, post_commit_ip, पात_ip) \
	__RSEQ_ASM_DEFINE_ABORT(table_label, label, tearकरोwn, \
				पात_label, 0x0, 0x0, start_ip, \
				(post_commit_ip - start_ip), पात_ip)

#घोषणा RSEQ_ASM_DEFINE_CMPFAIL(label, tearकरोwn, cmpfail_label) \
		__rseq_str(label) ":\n\t" \
		tearकरोwn \
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
		LONG_L " $4, %[v]\n\t"
		"bne $4, %[expect], %l[cmpfail]\n\t"
		RSEQ_INJECT_ASM(4)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, %l[error1])
		LONG_L " $4, %[v]\n\t"
		"bne $4, %[expect], %l[error2]\n\t"
#पूर्ण_अगर
		/* final store */
		LONG_S " %[newv], %[v]\n\t"
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
		: "$4", "memory"
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
		LONG_L " $4, %[v]\n\t"
		"beq $4, %[expectnot], %l[cmpfail]\n\t"
		RSEQ_INJECT_ASM(4)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, %l[error1])
		LONG_L " $4, %[v]\n\t"
		"beq $4, %[expectnot], %l[error2]\n\t"
#पूर्ण_अगर
		LONG_S " $4, %[load]\n\t"
		LONG_ADDI " $4, %[voffp]\n\t"
		LONG_L " $4, 0($4)\n\t"
		/* final store */
		LONG_S " $4, %[v]\n\t"
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
		: "$4", "memory"
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
		LONG_L " $4, %[v]\n\t"
		LONG_ADDI " $4, %[count]\n\t"
		/* final store */
		LONG_S " $4, %[v]\n\t"
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
		: "$4", "memory"
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
		LONG_L " $4, %[v]\n\t"
		"bne $4, %[expect], %l[cmpfail]\n\t"
		RSEQ_INJECT_ASM(4)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, %l[error1])
		LONG_L " $4, %[v]\n\t"
		"bne $4, %[expect], %l[error2]\n\t"
#पूर्ण_अगर
		/* try store */
		LONG_S " %[newv2], %[v2]\n\t"
		RSEQ_INJECT_ASM(5)
		/* final store */
		LONG_S " %[newv], %[v]\n\t"
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
		: "$4", "memory"
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
		LONG_L " $4, %[v]\n\t"
		"bne $4, %[expect], %l[cmpfail]\n\t"
		RSEQ_INJECT_ASM(4)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, %l[error1])
		LONG_L " $4, %[v]\n\t"
		"bne $4, %[expect], %l[error2]\n\t"
#पूर्ण_अगर
		/* try store */
		LONG_S " %[newv2], %[v2]\n\t"
		RSEQ_INJECT_ASM(5)
		"sync\n\t"	/* full sync provides store-release */
		/* final store */
		LONG_S " %[newv], %[v]\n\t"
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
		: "$4", "memory"
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
		LONG_L " $4, %[v]\n\t"
		"bne $4, %[expect], %l[cmpfail]\n\t"
		RSEQ_INJECT_ASM(4)
		LONG_L " $4, %[v2]\n\t"
		"bne $4, %[expect2], %l[cmpfail]\n\t"
		RSEQ_INJECT_ASM(5)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, %l[error1])
		LONG_L " $4, %[v]\n\t"
		"bne $4, %[expect], %l[error2]\n\t"
		LONG_L " $4, %[v2]\n\t"
		"bne $4, %[expect2], %l[error3]\n\t"
#पूर्ण_अगर
		/* final store */
		LONG_S " %[newv], %[v]\n\t"
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
		: "$4", "memory"
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
	uपूर्णांकptr_t rseq_scratch[3];

	RSEQ_INJECT_C(9)

	rseq_workaround_gcc_यंत्र_size_guess();
	__यंत्र__ __अस्थिर__ जाओ (
		RSEQ_ASM_DEFINE_TABLE(9, 1f, 2f, 4f) /* start, commit, पात */
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[cmpfail])
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error1])
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error2])
#पूर्ण_अगर
		LONG_S " %[src], %[rseq_scratch0]\n\t"
		LONG_S "  %[dst], %[rseq_scratch1]\n\t"
		LONG_S " %[len], %[rseq_scratch2]\n\t"
		/* Start rseq by storing table entry poपूर्णांकer पूर्णांकo rseq_cs. */
		RSEQ_ASM_STORE_RSEQ_CS(1, 3f, rseq_cs)
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, 4f)
		RSEQ_INJECT_ASM(3)
		LONG_L " $4, %[v]\n\t"
		"bne $4, %[expect], 5f\n\t"
		RSEQ_INJECT_ASM(4)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, 6f)
		LONG_L " $4, %[v]\n\t"
		"bne $4, %[expect], 7f\n\t"
#पूर्ण_अगर
		/* try स_नकल */
		"beqz %[len], 333f\n\t" \
		"222:\n\t" \
		"lb   $4, 0(%[src])\n\t" \
		"sb   $4, 0(%[dst])\n\t" \
		LONG_ADDI " %[src], 1\n\t" \
		LONG_ADDI " %[dst], 1\n\t" \
		LONG_ADDI " %[len], -1\n\t" \
		"bnez %[len], 222b\n\t" \
		"333:\n\t" \
		RSEQ_INJECT_ASM(5)
		/* final store */
		LONG_S " %[newv], %[v]\n\t"
		"2:\n\t"
		RSEQ_INJECT_ASM(6)
		/* tearकरोwn */
		LONG_L " %[len], %[rseq_scratch2]\n\t"
		LONG_L " %[dst], %[rseq_scratch1]\n\t"
		LONG_L " %[src], %[rseq_scratch0]\n\t"
		"b 8f\n\t"
		RSEQ_ASM_DEFINE_ABORT(3, 4,
				      /* tearकरोwn */
				      LONG_L " %[len], %[rseq_scratch2]\n\t"
				      LONG_L " %[dst], %[rseq_scratch1]\n\t"
				      LONG_L " %[src], %[rseq_scratch0]\n\t",
				      पात, 1b, 2b, 4f)
		RSEQ_ASM_DEFINE_CMPFAIL(5,
					/* tearकरोwn */
					LONG_L " %[len], %[rseq_scratch2]\n\t"
					LONG_L " %[dst], %[rseq_scratch1]\n\t"
					LONG_L " %[src], %[rseq_scratch0]\n\t",
					cmpfail)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_DEFINE_CMPFAIL(6,
					/* tearकरोwn */
					LONG_L " %[len], %[rseq_scratch2]\n\t"
					LONG_L " %[dst], %[rseq_scratch1]\n\t"
					LONG_L " %[src], %[rseq_scratch0]\n\t",
					error1)
		RSEQ_ASM_DEFINE_CMPFAIL(7,
					/* tearकरोwn */
					LONG_L " %[len], %[rseq_scratch2]\n\t"
					LONG_L " %[dst], %[rseq_scratch1]\n\t"
					LONG_L " %[src], %[rseq_scratch0]\n\t",
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
		: "$4", "memory"
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
	uपूर्णांकptr_t rseq_scratch[3];

	RSEQ_INJECT_C(9)

	rseq_workaround_gcc_यंत्र_size_guess();
	__यंत्र__ __अस्थिर__ जाओ (
		RSEQ_ASM_DEFINE_TABLE(9, 1f, 2f, 4f) /* start, commit, पात */
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[cmpfail])
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error1])
		RSEQ_ASM_DEFINE_EXIT_POINT(1f, %l[error2])
#पूर्ण_अगर
		LONG_S " %[src], %[rseq_scratch0]\n\t"
		LONG_S " %[dst], %[rseq_scratch1]\n\t"
		LONG_S " %[len], %[rseq_scratch2]\n\t"
		/* Start rseq by storing table entry poपूर्णांकer पूर्णांकo rseq_cs. */
		RSEQ_ASM_STORE_RSEQ_CS(1, 3f, rseq_cs)
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, 4f)
		RSEQ_INJECT_ASM(3)
		LONG_L " $4, %[v]\n\t"
		"bne $4, %[expect], 5f\n\t"
		RSEQ_INJECT_ASM(4)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_CMP_CPU_ID(cpu_id, current_cpu_id, 6f)
		LONG_L " $4, %[v]\n\t"
		"bne $4, %[expect], 7f\n\t"
#पूर्ण_अगर
		/* try स_नकल */
		"beqz %[len], 333f\n\t" \
		"222:\n\t" \
		"lb   $4, 0(%[src])\n\t" \
		"sb   $4, 0(%[dst])\n\t" \
		LONG_ADDI " %[src], 1\n\t" \
		LONG_ADDI " %[dst], 1\n\t" \
		LONG_ADDI " %[len], -1\n\t" \
		"bnez %[len], 222b\n\t" \
		"333:\n\t" \
		RSEQ_INJECT_ASM(5)
		"sync\n\t"	/* full sync provides store-release */
		/* final store */
		LONG_S " %[newv], %[v]\n\t"
		"2:\n\t"
		RSEQ_INJECT_ASM(6)
		/* tearकरोwn */
		LONG_L " %[len], %[rseq_scratch2]\n\t"
		LONG_L " %[dst], %[rseq_scratch1]\n\t"
		LONG_L " %[src], %[rseq_scratch0]\n\t"
		"b 8f\n\t"
		RSEQ_ASM_DEFINE_ABORT(3, 4,
				      /* tearकरोwn */
				      LONG_L " %[len], %[rseq_scratch2]\n\t"
				      LONG_L " %[dst], %[rseq_scratch1]\n\t"
				      LONG_L " %[src], %[rseq_scratch0]\n\t",
				      पात, 1b, 2b, 4f)
		RSEQ_ASM_DEFINE_CMPFAIL(5,
					/* tearकरोwn */
					LONG_L " %[len], %[rseq_scratch2]\n\t"
					LONG_L " %[dst], %[rseq_scratch1]\n\t"
					LONG_L " %[src], %[rseq_scratch0]\n\t",
					cmpfail)
#अगर_घोषित RSEQ_COMPARE_TWICE
		RSEQ_ASM_DEFINE_CMPFAIL(6,
					/* tearकरोwn */
					LONG_L " %[len], %[rseq_scratch2]\n\t"
					LONG_L " %[dst], %[rseq_scratch1]\n\t"
					LONG_L " %[src], %[rseq_scratch0]\n\t",
					error1)
		RSEQ_ASM_DEFINE_CMPFAIL(7,
					/* tearकरोwn */
					LONG_L " %[len], %[rseq_scratch2]\n\t"
					LONG_L " %[dst], %[rseq_scratch1]\n\t"
					LONG_L " %[src], %[rseq_scratch0]\n\t",
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
		: "$4", "memory"
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
